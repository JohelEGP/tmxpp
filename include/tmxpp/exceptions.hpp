#ifndef TMXPP_EXCEPTIONS_HPP
#define TMXPP_EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace tmxpp {

class Exception : public std::exception {
public:
    explicit Exception(std::string what) noexcept;

    const char* what() const noexcept override;

private:
    std::string what_;
};

} // namespace tmxpp

#endif // TMXPP_EXCEPTIONS_HPP
