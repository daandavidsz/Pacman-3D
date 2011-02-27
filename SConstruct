env = Environment(CCFLAGS='-Wall -Wno-unused-parameter -Wno-switch -lglut -lGLU -lGL `Magick++-config --cppflags --cxxflags --ldflags --libs`')

list = []
list.extend(Glob('*.cpp'))
list.extend(Glob('actor/*.cpp'))
list.extend(Glob('object/*.cpp'))
list.extend(Glob('bonus/*.cpp'))

env.Program('pacman', list)
