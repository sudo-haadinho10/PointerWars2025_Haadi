#Compiler to use
CC = gcc

# Compiler flags:
#  -Wall: Enable all warning messages
#  -Wextra: Enable extra warning flags
#  -Werror: Convert warnings to errors
#  -g: Include debugging information

CFLAGS = -Wall -Wextra -Werror -I. -L.

# Compiler Optimization:
#  -O3: optimization
#  -g: Include debugging information 

COMPILER_OPTIMIZATIONS = -O3 -g

# Target executable name
TARGET = linkedlist_output2.out

#Source files
SRCS= linked_list.c queue.c

#Object files (replace .c with .o)
#OBJS = $(SRCS:.c=.o)

#Object files
#LINKED_LIST_OBJECT_FILES = linked_list.o

#Specify what to test
#
FUNCTIONAL_TEST_COMPILER_DEFINES := -DTEST_LINKED_LIST -DTEST_QUEUE

# Functional testing support
FUNCTIONAL_TEST_SOURCE_FILES := linked_list_test_program.c
#FUNCTIONAL_TEST_OBJECT_FILES := linked_list_test_program_official.o

# Default rule to build the target
all: $(TARGET)

#Link object files to create the executable

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(COMPILER_OPTIMIZATIONS) $(FUNCTIONAL_TEST_COMPILER_DEFINES) -o $(TARGET) $(FUNCTIONAL_TEST_SOURCE_FILES) $(SRCS) 

#Clean up build files
clean:
	rm -f $(TARGET)
