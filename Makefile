# ---------- Project ----------
PROJECT := game

# ---------- Paths ----------
SRC_DIR   := src
BUILD_DIR := build

# ---------- Tools ----------
CXX := g++

# SDL2 + SDL2_image via pkg-config
PKGS := sdl2 SDL2_image

# ---------- Flags ----------
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2 -g \
            $(shell pkg-config --cflags $(PKGS))
LDFLAGS  := $(shell pkg-config --libs $(PKGS))

# Auto-discover sources
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# ---------- Targets ----------
.PHONY: all run clean
all: $(PROJECT)

run: all
	./$(PROJECT)

clean:
	rm -rf $(BUILD_DIR) $(PROJECT)

# Link final exe in project root
$(PROJECT): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile with dependency gen
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Create build dir if missing
$(BUILD_DIR):
	mkdir -p $@

# Include auto-generated .d files
-include $(DEPS)

# ---------- Notes ----------
# If pkg-config isn't available, you can use:
# CXXFLAGS += $(shell sdl2-config --cflags)
# LDFLAGS  += $(shell sdl2-config --libs) -lSDL2_image

