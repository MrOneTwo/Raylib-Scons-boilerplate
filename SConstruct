AddOption('--toolchain', dest='toolchain', choices=['mingw', 'gnu', 'cl'],
          default='mingw', help='Toolchain Specification')

# CPPFLAGS are for both cpp and c - preprocessor options
# CCFLAGS are for both cpp and c - general options
# CXXFLAGS are for cpp
# CFLAGS are for C

env = Environment(
    CPPPATH = ['./libs/raylib/include'],
    LIBPATH = ['./libs/raylib/libs/win32/mingw32'],
    LIBS = [  \
    'raylib'  \
    , 'glfw3' \
    , 'opengl32' \
    , 'gdi32' \
    , 'openal32' \
    , 'winmm' \
    ]
)


# MINGW BUILDING
env_MINGW = env.Clone(tools = ['mingw'])
env_MINGW.Replace(CCFLAGS = ['-fdiagnostics-color=always'])  # turning off /nologo
env_MINGW.Replace(CC = 'gcc')
env_MINGW.Replace(CXX = 'g++')
env_MINGW.Replace(CXXFLAGS = ['-std=c++11', '-g', '-fpermissive', '-Wno-narrowing'])

# MSVSC BUILDING
env_CL = env.Clone()
env_CL.Replace(CCFLAGS = [''])  # turning off /nologo
env_CL.Replace(LIBPATH = ['./libs/raylib/libs/win32/msvc'])
#env_CL.Replace(LINKFLAGS = ['/VERBOSE'])


if GetOption('toolchain') == 'mingw':
    #print(env_MINGW.Dump())
    env_MINGW.Object(target='./obj/main.o', source='./src/main.c')

    env_MINGW.Program( \
        target='./build/main' , \
        source=[ \
        './obj/main.o' \
        ] \
    )
elif GetOption('toolchain') == 'cl':
    #print(env_CL.Dump())
    env_CL.Object(target='./obj/main.o', source='./src/main.c')

    env_CL.Program( \
        target='./build/main' , \
        source=[ \
        './obj/main.o' \
        ] \
    )
