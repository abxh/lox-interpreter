#pragma once

#include <ostream>
#include <string_view>

class Error {
public:
    const bool occurred;
    const std::string_view msg;

    Error(bool occurred, std::string_view msg)
        : occurred(occurred)
        , msg(msg){};

    virtual ~Error() = default;

    friend std::ostream& operator<<(std::ostream& os, const Error& error);

    virtual void print(std::ostream& os) const {
        os << this->msg << "\n";
    }
};

class ErrorAtLine : public Error {
public:
    const std::string_view line;
    const int linenr;

    ErrorAtLine(bool occurred, std::string_view msg, int linenr, std::string_view line)
        : Error(occurred, msg)
        , linenr(linenr)
        , line(line){};

    void print(std::ostream& os) const override {
        os << "Line: " << this->linenr << "\n";
        os << "\t" << this->line << "\n";
        os << this->msg << "\n";
    }
};

inline std::ostream& operator<<(std::ostream& os, const Error& error) {
    error.print(os);
    return os;
}
