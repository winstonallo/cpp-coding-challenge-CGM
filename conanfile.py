from conan import ConanFile
from conan.tools.cmake import cmake_layout


class CGM(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("cli/2.2.0")

    def layout(self):
        cmake_layout(self)