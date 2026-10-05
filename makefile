CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SDLFLAGS = $(shell pkg-config --cflags --libs sdl3)

SOURCES = \
    src/main.cc \
    src/graphics/framebuffer.cc \
    src/graphics/window.cc \
    src/graphics/renderer.cc \
    src/events/events.cc \
    src/graphics/renderer3d.cc \
    src/graphics/rasterizer.cc \
    src/input/input.cc \
    src/time/time.cc \
    src/camera/camera.cc \
    src/tools/obj_loader.cc

build/physics: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o build/physics $(SDLFLAGS)

clean:
	rm -f build/physics

run: build/physics
	./build/physics	