#include "error.hpp"
#include "tokenizer.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>

static std::unique_ptr<Error> run(std::string_view code) {
    // must return unique pointer, because using polymorphsim.

    auto ret = std::make_unique<ErrorAtLine>(true, "Success!", 1, code);

    // debug code --- to be removed later:
    auto token = Token{NUMBER, code};
    std::cout << std::get<double>(token.get_object()) << "\n";

    return ret;
}

static void run_prompt() {
    std::string line;

    bool running = true;
    while (running) {

        std::cout << "> ";

        if (!std::getline(std::cin, line)) {
            running = false;
            continue;
        }

        const std::unique_ptr<Error> error = run(line);
        if (error->occurred) {
            std::cout << *error;
        }
    }
}

static void run_file(const char* path) {
    std::ifstream f(path);
    if (f.fail()) {
        std::cout << "run_file() failed: " << std::strerror(errno) << "\n";
        return;
    }

    const std::string content((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));

    const std::unique_ptr<Error> error = run(content);
    if (error->occurred) {
        std::cout << *error;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cout << "Usage: lox [script]\n";
    } else if (argc == 2) {
        run_file(argv[1]);
    } else {
        run_prompt();
    }
    return 0;
}
