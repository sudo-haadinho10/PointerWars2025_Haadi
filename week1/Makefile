#Compiler to use
CC = gcc

# Compiler flags:
#  -Wall: Enable all warning messages
#  -Wextra: Enable extra warning flags
#  -Werror: Convert warnings to errors
#  -g: Include debugging information

CFLAGS = -Wall -Wextra -Werror 

# Compiler Optimization:
#  -O3: optimization
#  -g: Include debugging information 

COMPILER_OPTIMIZATIONS = -O3 -g

# Target executable name
TARGET = linkedlist_output.out

#Source files
SRCS= linked_list.c 


#Object files
#LINKED_LIST_OBJECT_FILES = linked_list.o

# Functional testing support
FUNCTIONAL_TEST_SOURCE_FILES := linked_list_test_program_official.c
FUNCTIONAL_TEST_OBJECT_FILES := linked_list_test_program_official.o

# Default rule to build the target
all: $(TARGET)

#Link object files to create the executable

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(COMPILER_OPTIMIZATIONS) -o $(TARGET) $(FUNCTIONAL_TEST_SOURCE_FILES) $(SRCS) 

#Clean up build files
clean:
	rm -f $(FUNCTIONAL_TEST_OBJECT_FILES)
