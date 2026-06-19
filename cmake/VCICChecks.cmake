# =============================================================================
# C++ standard-library and Qt feature checks. Runs at configure time and populates:
# VCIC_CHECKS_PASSED — list of available features VCIC_CHECKS_FAILED — list of missing features
#
# Include after project(), CMAKE_CXX_STANDARD, and find_package(Qt6) are set.
# =============================================================================

include(CheckCXXSourceCompiles)
include(CMakePushCheckState)

set(VCIC_CHECKS_PASSED "")
set(VCIC_CHECKS_FAILED "")

# Compile all checks with the project's C++ standard.
cmake_push_check_state(RESET)
if(MSVC)
    set(CMAKE_REQUIRED_FLAGS "/std:c++${CMAKE_CXX_STANDARD}")
else()
    set(CMAKE_REQUIRED_FLAGS "-std=c++${CMAKE_CXX_STANDARD}")
endif()
set(CMAKE_REQUIRED_QUIET ON)

# Helper — runs a compile check and appends to the pass/fail lists.
macro(VCIC_CXX_CHECK var label code)
    check_cxx_source_compiles("${code}" _VCIC_CHK_${var})
    if(_VCIC_CHK_${var})
        list(APPEND VCIC_CHECKS_PASSED "${label}")
    else()
        list(APPEND VCIC_CHECKS_FAILED "${label}")
    endif()
endmacro()

# =============================================================================
# C++20 — required features for async networking with Qt
# =============================================================================

vcic_cxx_check(
    COROUTINES
    "C++20 coroutines  <coroutine>"
    [[
#include <coroutine>
struct Task {
    struct promise_type {
        Task get_return_object()             { return {}; }
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend()   noexcept { return {}; }
        void return_void()                   noexcept {}
        void unhandled_exception()           noexcept {}
    };
};
Task coro() { co_return; }
int main() { coro(); }
]])

vcic_cxx_check(
    CONCEPTS
    "C++20 concepts     <concepts>"
    [[
#include <concepts>
template<std::integral T>
T add(T a, T b) { return a + b; }
int main() { return add(1, 2) - 3; }
]])

vcic_cxx_check(
    RANGES
    "C++20 ranges        <ranges>"
    [[
#include <ranges>
#include <vector>
int main() {
    std::vector<int> v{1,2,3,4};
    auto even = v | std::views::filter([](int i){ return i % 2 == 0; });
    (void)even;
}
]])

vcic_cxx_check(
    FORMAT
    "C++20 std::format   <format>"
    [[
#include <format>
int main() { auto s = std::format("v={}", 42); (void)s; }
]])

vcic_cxx_check(
    SPAN
    "C++20 std::span     <span>"
    [[
#include <span>
#include <array>
int main() {
    std::array<std::byte, 4> buf{};
    std::span<std::byte> s{buf};
    (void)s;
}
]])

vcic_cxx_check(
    JTHREAD
    "C++20 std::jthread  <stop_token>"
    [[
#include <thread>
#include <stop_token>
int main() {
    std::jthread t([](std::stop_token st) {
        while (!st.stop_requested()) {}
    });
    t.request_stop();
}
]])

vcic_cxx_check(
    LATCH_BARRIER
    "C++20 latch/barrier <latch> <barrier>"
    [[
#include <latch>
#include <barrier>
int main() {
    std::latch   l{1};  l.count_down();
    std::barrier b{1};  b.arrive_and_wait();
}
]])

vcic_cxx_check(
    SEMAPHORE
    "C++20 semaphore     <semaphore>"
    [[
#include <semaphore>
int main() {
    std::counting_semaphore<8> sem{1};
    sem.acquire();
    sem.release();
}
]])

vcic_cxx_check(
    ATOMIC_SHARED_PTR
    "C++20 atomic<shared_ptr>"
    [[
#include <atomic>
#include <memory>
int main() {
    std::atomic<std::shared_ptr<int>> asp{std::make_shared<int>(0)};
    *asp.load() = 1;
}
]])

# =============================================================================
# C++23 — optional quality-of-life features
# =============================================================================

vcic_cxx_check(
    EXPECTED
    "C++23 std::expected <expected>"
    [[
#include <expected>
std::expected<int, int> ok() { return 42; }
int main() { return ok().value() - 42; }
]])

vcic_cxx_check(
    FLAT_MAP
    "C++23 flat_map      <flat_map>"
    [[
#include <flat_map>
int main() {
    std::flat_map<int, int> m{{1, 2}};
    return m[1] - 2;
}
]])

vcic_cxx_check(
    PRINT
    "C++23 std::print     <print>"
    [[
#include <print>
int main() { std::println("ok"); }
]])

cmake_pop_check_state()

# =============================================================================
# Qt6::Network — checked via find_package, not source compilation. Qt handles the platform socket
# abstraction; no POSIX checks needed.
# =============================================================================

# Qt6::Network is mandatory — the project uses QTcpSocket / QUdpSocket.
find_package(Qt6 REQUIRED COMPONENTS Network)
list(APPEND VCIC_CHECKS_PASSED "Qt6::Network (${Qt6_VERSION})  QTcpSocket / QUdpSocket")

# Qt6::NetworkAuth — optional (OAuth2, bearer tokens, etc.)
find_package(Qt6 QUIET COMPONENTS NetworkAuth)
if(Qt6NetworkAuth_FOUND)
    list(APPEND VCIC_CHECKS_PASSED "Qt6::NetworkAuth (${Qt6NetworkAuth_VERSION})  optional")
else()
    list(APPEND VCIC_CHECKS_FAILED "Qt6::NetworkAuth  (not found, optional)")
endif()

# Qt6::WebSockets — optional (WebSocket transport layer)
find_package(Qt6 QUIET COMPONENTS WebSockets)
if(Qt6WebSockets_FOUND)
    list(APPEND VCIC_CHECKS_PASSED "Qt6::WebSockets  (${Qt6WebSockets_VERSION})  optional")
else()
    list(APPEND VCIC_CHECKS_FAILED "Qt6::WebSockets  (not found, optional)")
endif()
