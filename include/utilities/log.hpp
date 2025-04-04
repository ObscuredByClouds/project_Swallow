#pragma once

////////////////////////////////////////////////////////////

#define ERROR       (1u << 0)
#define WARNING     (1u << 1)
#define INFO        (1u << 2)
#define DEBUG       (1u << 3)
#define TRACE       (1u << 4)
#define ALL         (ERROR | WARNING | INFO | DEBUG | TRACE)
#define PRODUCTION  (ERROR | WARNING | INFO)
#define CLEAN       (ERROR | INFO)

#ifndef LOG_LEVEL
#define LOG_LEVEL (ALL)
#endif

////////////////////////////////////////////////////////////

#include <iostream>
#include <sys/time.h>
#include <source_location>

namespace himark::log
{

#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define PURPLE  "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#define CLEAR   "\033[0m"

template <typename T, typename... Rest>
inline void log(T&& x, Rest&&... rest)
{
    std::ostream& os = std::clog;

    auto get_date = [](){
        timeval tv;
        gettimeofday(&tv, nullptr);

        char buffer[64];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", localtime(&tv.tv_sec));
        sprintf(buffer + 8, ".%03ld", tv.tv_usec / 1000);

        return std::string(buffer);
    };

    os << '[' << get_date() << "] ";

    os << std::forward<T>(x);
    (os << ... << std::forward<Rest>(rest));

    os << std::flush;
}

template <typename... Args>
inline void error(Args&&... args)
{
    log(RED BOLD "[E] ", std::forward<Args>(args)..., CLEAR, '\n');
}

template <typename... Args>
inline void warning(Args&&... args)
{
    log(YELLOW BOLD "[W] ", std::forward<Args>(args)..., CLEAR, '\n');
}

template <typename... Args>
inline void info(Args&&... args)
{
    log(GREEN BOLD "[I] ",  std::forward<Args>(args)..., CLEAR, '\n');
}

template <typename... Args>
inline void debug(Args&&... args)
{
    log(PURPLE BOLD "[D] ", std::forward<Args>(args)..., CLEAR, '\n');
}

inline auto trace(std::source_location location = std::source_location::current())
{
    static size_t depth = 0;

    struct __stack_frame {
        size_t& depth;

        __stack_frame(size_t& depth, std::source_location location) : depth(depth)
        {
            std::string prefix;

            if (depth != 0)
            {
                std::string branch = "├── ";
                std::string skip = "│   ";
                for (size_t i = 0; i < depth - 1; ++i)
                    prefix += skip;
                prefix += branch;
            }
            depth++;
            log(CYAN BOLD "[T] ", prefix, location.function_name(), CLEAR, '\n');
        }

        ~__stack_frame()
        {
            --depth;
        }
    };
    
    return __stack_frame(depth, location);
}

}

#if (LOG_LEVEL & ERROR)
#define LOG_ERROR(...) himark::log::error("<" __FILE__ ":", __LINE__, "> ", __VA_ARGS__)
#else 
#define LOG_ERROR(...) do {} while(false)
#endif

#define LOG_FATAL(...) do { LOG_ERROR(__VA_ARGS__); exit(1); } while(false)

#if (LOG_LEVEL & WARNING)
#define LOG_WARNING(...) himark::log::warning(__VA_ARGS__)
#else 
#define LOG_WARNING(...) do {} while(false)
#endif

#if (LOG_LEVEL & INFO)
#define LOG_INFO(...) himark::log::info(__VA_ARGS__)
#else 
#define LOG_INFO(...) do {} while(false)
#endif

#if (LOG_LEVEL & DEBUG)
#define LOG_DEBUG(...) himark::log::debug(__VA_ARGS__)
#else
#define LOG_DEBUG(...) do {} while(false)
#endif

#if (LOG_LEVEL & TRACE)
#define LOG_TRACE(...) auto __stack_frame = himark::log::trace(__VA_ARGS__)
#else
#define LOG_TRACE(...) do {} while(false)
#endif