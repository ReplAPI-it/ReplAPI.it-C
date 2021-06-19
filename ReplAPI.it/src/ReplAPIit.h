#pragma once

#ifdef WIN32
  #define ReplAPIit_EXPORT __declspec(dllexport)
#else
  #define ReplAPIit_EXPORT
#endif

ReplAPIit_EXPORT void ReplAPIit();

namespace lib {
    int main();
}