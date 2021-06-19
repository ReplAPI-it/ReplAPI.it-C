#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include "./lib/arraylib/arraylib.h"
#include "ReplAPIit.h"

using namespace adaptX;
using json = nlohmann::json;

namespace lib {
int main() {
    cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
                      cpr::Authentication{"user", "pass"},
                      cpr::Parameters{{"anon", "true"}, {"key", "value"}});
    std::cout << r.status_code << "\n"; // 200
    std::cout << r.header["content-type"] << "\n"; // application/json; charset=utf-8
    std::cout << json::parse(r.text) << "\n"; // JSON text string
}
}

void hashMapTest() {
    HashMap<String, String> test;
    test.put(String("test"), String("testing 1 2 3"));
    std::cout << test.get(String("test")).valueOf();
}

void ReplAPIit(){
    #ifdef NDEBUG
    std::cout << "ReplAPI.it/0.1: Hello World Release!" <<std::endl;
    #else
    std::cout << "ReplAPI.it/0.1: Hello World Debug!" <<std::endl;
    #endif
    lib::main();
    hashMapTest();
}
