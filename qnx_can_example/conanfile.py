import os
import shutil
import subprocess
import re
from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.env import VirtualRunEnv, VirtualBuildEnv
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.scm import Version

required_conan_version = ">=1.53.0"


class E171Conan(ConanFile):
    name = "e171"
    version = "dev"
    settings = "os", "compiler", "build_type", "arch"

    @property
    def _min_cppstd(self):
        return 14

    def configure(self):
        # specify glog options
        self.options["glog"].shared = False
        # specifiy opencv options
        self.options["opencv"].parallel = "openmp"
        self.options["opencv"].shared = False
        self.options["opencv"].with_cuda = False
        self.options["ceres-solver"].use_glog = True
        self.options["proj"].with_tiff = False
        self.options["proj"].with_curl = False

    def requirements(self):
        self.requires("ceres-solver/2.1.0")
        self.requires("glog/0.6.0@transformer/stable", force=True)
        self.requires("opencv/4.5.5@transformer/stable")
        self.requires("eigen/3.4.0")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CMAKE_POLICY_DEFAULT_CMP0077"] = "NEW"
        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()
        tc = VirtualRunEnv(self)
        tc.generate()
        tc = VirtualBuildEnv(self)
        tc.generate(scope="build")