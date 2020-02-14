
#include <stdexcept>
#include <functional>

namespace {

const int randomRange = 2;  // Give me a number between 0 nd 2
const int errorInt = 0;     // Stop every time the number is 0

int getRandom() {
    return random() % randomRange ;
}

template<typename T>
T testFunction(const std::function<T()>& fn) {
    auto num = getRandom();
    for (int i{0}; i < 5; ++i) {
        if (num == errorInt)
            return fn();
    }
}

// exit by throwing a int
void exitwithIntException() {
    testFunction<void>([]() -> void {
        throw -2;
    });
}

// exit by throwing n run time error
void exitWithStdException() {
    testFunction<void>([]() -> void {
        throw std::runtime_error("Exception!");
    });
}

// exit with a void return
void exitWithReturn() {
    testFunction<void> ([]()-> void {
        return;
    });
}

// exit with  C-style int error code
int exitWithErrorCode() {
    testFunction<int> ([]() -> int {
        return -1;
    });

    return 0;
}

}