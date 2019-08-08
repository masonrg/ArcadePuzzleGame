#pragma once

#include <iostream>

#if DEBUG==1
#define LOG(x) std::cout << (x) << std::endl
#define LOG_ERROR(hdr, msg) std::cout << (hdr) << ": " << (msg) << std::endl;
#else
#define LOG(x) 
#define LOG_ERROR(x)
#define LOG_SDL_ERROR()
#endif