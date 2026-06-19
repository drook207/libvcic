# libvcic

A C++20/Qt6 library implementing the ISO 17215 **Video Communication Interface for Cameras (VCIC)** standard.

> **ISO 17215 note:** The standard is copyright-protected and not freely available. This library
> contains no content copied from the standard text (no message IDs, byte layouts, or tables).
> The `V1` concrete classes (`VcicMessageCodecV1`, `VcicDiscoveryServiceV1`) serve as skeletons
> that must be filled in from a legally obtained copy of the standard.

## Architecture

The library is split into four decoupled layers. Transport and protocol encoding are independently
interchangeable, which allows testing without real camera hardware via a `MockTransport`.

```
┌──────────────────────────────────────────────────────────┐
│                GUI Layer  (Qt Widgets/QML)                │
│   MainWindow · CameraListView · ParameterEditorView       │
│   LogConsoleView                                          │
└───────────────────────┬──────────────────────────────────┘
                        │ Signals / Slots
┌───────────────────────▼──────────────────────────────────┐
│            Application / Controller Layer                 │
│   DiscoveryController · CameraSessionController           │
└───────────────────────┬──────────────────────────────────┘
                        │
┌───────────────────────▼──────────────────────────────────┐
│       VCIC Protocol Layer  (ISO 17215 Parts 2 + 3)        │
│   IVcicDiscoveryService · IVcicMessageCodec               │
│   VcicCamera · VcicMessage · VcicCameraInfo               │
└───────────────────────┬──────────────────────────────────┘
                        │
┌───────────────────────▼──────────────────────────────────┐
│        Transport Layer  (ISO 17215 Part 4)                │
│   ITransport · UdpTransport · TcpTransport                │
└──────────────────────────────────────────────────────────┘
```

See [`docs/libvcic.md`](docs/libvcic.md) for the full class diagram and sequence diagrams.

## CMake targets

| Target | Namespace alias | Description |
|--------|----------------|-------------|
| `vcic-transport` | `VCIC::vcic-transport` | Transport layer (`ITransport`, `UdpTransport`, `TcpTransport`) |
| `vcic-protocol` | `VCIC::vcic-protocol` | Protocol layer (codec, discovery, model classes) |

The GUI application (`vcic-gui`) is an optional build artifact and is **not** part of the
installed package.

## Requirements

| Dependency | Minimum version | Notes |
|-----------|----------------|-------|
| CMake | 3.30 | Uses `FILE_SET HEADERS`, `cmake_push_check_state` |
| C++ compiler | GCC 13 / Clang 17 | C++20 required |
| Qt6 | 6.5 | `Core`, `Network`; `Widgets` for GUI |
| Ninja | any | Default generator in all presets |

Optional (auto-detected at configure time):

- `Qt6::NetworkAuth` — OAuth2 / bearer token support
- `Qt6::WebSockets` — WebSocket transport layer
- `Qt6::Widgets` — GUI application (`VCIC_BUILD_GUI=ON`)

## Building

The project ships `CMakePresets.json` with presets for GCC and Clang in
Debug / RelWithDebInfo / Release / Profile configurations.

```sh
# Configure
cmake --preset gcc-debug

# Build
cmake --build --preset gcc-debug

# Run tests
ctest --preset gcc-debug
```

Available configure presets: `gcc-debug`, `gcc-relwithdebug`, `gcc-release`, `gcc-profile`,
`clang-debug`, `clang-relwithdebug`, `clang-release`, `clang-profile`.

All presets write build artifacts to `builds/<compiler>/<type>/` and set
`CMAKE_INSTALL_PREFIX` to `<source>/install/`.

### Build options

| Option | Default | Description |
|--------|---------|-------------|
| `VCIC_BUILD_TESTS` | `ON` | Build unit tests (Google Test) |
| `VCIC_BUILD_GUI` | `OFF` | Build the Qt Widgets GUI application |
| `VCIC_BUILD_BENCHMARKS` | `OFF` | Build microbenchmarks |
| `VCIC_BUILD_EXAMPLES` | `OFF` | Build example applications |
| `VCIC_ENABLE_CLANG_TIDY` | `OFF` | Run clang-tidy during compilation |
| `VCIC_ENABLE_SANITIZERS` | `OFF` | Enable ASan + UBSan |
| `VCIC_ENABLE_COVERAGE` | `OFF` | Enable gcov/lcov instrumentation |
| `VCIC_ENABLE_IPO` | `OFF` | Enable link-time optimisation |
| `VCIC_WARNINGS_AS_ERRORS` | `OFF` | Treat compiler warnings as errors |

```sh
cmake --preset gcc-debug -DVCIC_BUILD_GUI=ON -DVCIC_ENABLE_SANITIZERS=ON
```

### Installing

```sh
cmake --build --preset gcc-release
cmake --install builds/gcc/release
```

Headers are installed to `<prefix>/include/vcic/`, CMake package files to
`<prefix>/lib/cmake/VCIC/`.

## CMake package integration

After installation, downstream projects consume the library with standard CMake:

```cmake
find_package(VCIC REQUIRED)

target_link_libraries(my-app PRIVATE VCIC::vcic-protocol VCIC::vcic-transport)
```

## Project structure

```
libvcic/
├── cmake/                  # CMake modules (options, checks, summary, package config)
├── docs/                   # Architecture documentation
├── gui/                    # Optional Qt Widgets application
├── src/
│   ├── vcic-protocol/      # Protocol layer (CMake target: vcic-protocol)
│   └── vcic-transport/     # Transport layer (CMake target: vcic-transport)
└── tests/                  # Google Test suite with MockTransport
```

## Development

The project uses [pre-commit](https://pre-commit.com) hooks for code quality:

```sh
pip install pre-commit
pre-commit install
pre-commit install --hook-type commit-msg
```

Hooks: `clang-format`, `cmake-format`, `cmake-lint`, `clang-tidy`, `qmlformat`,
conventional commits.

## License

[MIT](LICENSE) — Copyright (c) 2026 Pascal Berndt
