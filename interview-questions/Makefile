# Define the compiler
CC = /opt/clang+llvm/clang+llvm-17.0.6/bin/clang++

# Define dynamic paths
SDKPATH = $(shell xcrun --show-sdk-path)
LIBPATH = $(SDKPATH)/usr/lib

# Define compiler flags with dynamic paths
CFLAGS = -Wall -std=c++20 -isysroot $(SDKPATH) -L$(LIBPATH)

CXXFLAGS = -Wall -std=c++20 -isysroot $(SDKPATH) -L$(LIBPATH)

# Determine the directory containing the Makefile
MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))

# Define source files
SRCS = mapred.cpp

# Define object files and target executable location
OBJDIR = $(MAKEFILE_DIR)bin/obj
BINDIR = $(MAKEFILE_DIR)bin
TARGET = $(BINDIR)/$(basename $(firstword $(SRCS)))  # Target derived from the first source file

# Define object files
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))

# Create directories if they do not exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJDIR) $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS)

# Compile source files to object files
$(OBJDIR)/%.o: $(MAKEFILE_DIR)%.cpp | $(OBJDIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(MAKEFILE_DIR)bin

# Build and run the executable
run: $(TARGET)
	./$(TARGET)

# Dynamic Makefile invocation
invoke:
	make -f $(MAKEFILE_DIR)Makefile $(MAKECMDGOALS)
