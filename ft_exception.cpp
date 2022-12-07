#include "ft_exception.h"
#include <sstream>


FTESTING_NS_BEGIN

exception_t::exception_t(const std::string& msg, const char *file, unsigned long line)
: msg(msg), file(file), line(line)
{
}

const char* exception_t::what() const throw()
{
    std::stringstream ss;
    ss << msg << ", file: " << file << ", line: " << line << "\n";

    msg = ss.str();
    return msg.c_str();    
}

FTESTING_NS_END