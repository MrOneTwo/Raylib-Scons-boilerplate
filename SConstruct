AddOption('--toolchain', dest='toolchain', choices=['mingw', 'gnu', 'cl'],
          default='mingw', help='Toolchain Specification')

env = Environment(
    CXXFLAGS = ['-std=c++11', '-g', '-fpermissive', '-Wno-narrowing'],
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


# THIS ONE SHOULD EXPAND env
#env_MINGW = env.Clone(tools = ['mingw'])
env_MINGW = Environment(
    tools = ['mingw'],
    #CXXFLAGS = ['-std=c++11', '-g', '-fpermissive', '-Wno-narrowing', '-E'],
    CXXFLAGS = ['-std=c++11', '-g', '-fpermissive', '-Wno-narrowing'],
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

# THIS ONE SHOULD EXPAND env
env_CL = Environment(
    CXXFLAGS = ['-std=c++11', '-g', '-fpermissive'],
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

if GetOption('toolchain') == 'mingw':
    env_MINGW.Object(target='./obj/main.o', source='./src/main.cpp')

    env_MINGW.Program( \
        target='./build/main' , \
        source=[ \
        './obj/main.o' \
        ] \
    )
elif GetOption('toolchain') == 'cl':
    env_CL.Object(target='./obj/main.o', source='./src/main.cpp')

    env_CL.Program( \
        target='./build/main' , \
        source=[ \
        './obj/main.o' \
        ] \
    )
