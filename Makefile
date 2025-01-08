# Makefile

ifeq ($(OS),Windows_NT)
    OS_NAME := Windows
    BUILD_DIR := build/win
    EXE_EXT := .exe
    MKDIR := mkdir $(BUILD_DIR)
    FIND_COMPILER := where
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        OS_NAME := Linux
        BUILD_DIR := build/linux
        EXE_EXT :=
        MKDIR := mkdir -p $(BUILD_DIR)
        FIND_COMPILER := which
    else
        OS_NAME := Unknown
        BUILD_DIR := build
        EXE_EXT :=
        MKDIR := mkdir -p $(BUILD_DIR)
        FIND_COMPILER := which
    endif
endif

define find_compiler
$(shell $(FIND_COMPILER) $(1) 2>nul)
endef

GPP := $(call find_compiler,g++)
CLANGPP := $(call find_compiler,clang++)

ifeq ($(GPP),)
    ifneq ($(CLANGPP),)
        CXX := clang++
    else
        $(error Could not find C++ compiler (g++ or clang++ are required))
    endif
else
    CXX := g++
endif

CXXFLAGS := -std=c++17 -O3 -Wall

SRCS := LinkedList/linked_list.cpp \
        DirectedGraph/graph.cpp \
        test/test.cpp \
        main.cpp

TARGET := lasd$(EXE_EXT)

all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET)
	@echo [COMPILATION] Status: OK
	@echo [COMPILATION] Executable generated in '$(BUILD_DIR)' folder

$(BUILD_DIR):
	$(MKDIR)

$(BUILD_DIR)/$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

clean:
ifeq ($(OS),Windows_NT)
	del /Q /S build\*
	rmdir /S /Q build
else
	rm -rf build
endif

.PHONY: all clean