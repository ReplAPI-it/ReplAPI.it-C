from conans import ConanFile, CMake

#####################################################
# Temporarily using nlohmann_json until we can make #
# our own parser                                    #
#####################################################

class ReplAPIItConan(ConanFile):
    name = "ReplAPI.it"
    version = "0.1"
    license = "GPL 3.0"
    author = "<Put your name here> <And your email here>"
    url = "https://github.com/ReplAPI-it/ReplAPI.it-C"
    description = "Wrapper for Repl.it APIs for C++"
    topics = ("replit", "graphql", "api")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake"
    exports_sources = "src/*"
    requires = ("cpr/1.6.2", "nlohmann_json/3.9.1")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="src")
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["ReplAPIit"]
