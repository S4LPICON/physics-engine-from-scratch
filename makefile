# Compilador y banderas
CXX      := g++
SDLFLAGS := $(shell pkg-config --cflags --libs sdl3)

# Directorios
SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build
TARGET    := $(BUILD_DIR)/physics

# Busca automáticamente todas las subcarpetas dentro de include/ para los #include
INCDIRS  := $(shell find $(INC_DIR) -type d)
CXXFLAGS := -std=c++17 -D_GNU_SOURCE -Wall -Wextra -Wpedantic $(addprefix -I,$(INCDIRS)) -MMD -MP

# Busca automáticamente todos los archivos .cc en src/ y sus subcarpetas
SOURCES := $(shell find $(SRC_DIR) -type f -name '*.cc')
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)
DEPS    := $(OBJECTS:.o=.d)

.PHONY: all clean run

all: $(TARGET)

# Vinculación final
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJECTS) -o $@ $(SDLFLAGS)

# Compilación de cada objeto manteniendo la estructura de subcarpetas
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Incluye los archivos de dependencia (.d) autogenerados
-include $(DEPS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)