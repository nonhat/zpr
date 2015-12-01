env_test = Environment(
                CPPDEFINES=[],
                LIBS=['SDL2', 'GL'],
                CXXFLAGS="-std=c++0x"
                )
env_test.Program('Birds', ["Boxing/algebra.cpp", "Boxing/Boxing.cpp", "Boxing/test.cpp"])

env_lib = Environment(
                CPPPATH=['/usr/include/python3.5m'],
                CPPDEFINES=[],
                LIBS=['boost_python3'],
                CXXFLAGS="-std=c++0x"
                )

env_lib.SharedLibrary('birdsDjango/gameworld', ["Boxing/algebra.cpp", "Boxing/Boxing.cpp", "Model/gameworld.cpp", "Model/python.cpp"])