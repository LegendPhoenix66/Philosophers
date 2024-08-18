# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Header file
HEADER = philo/philosophers.h

# Source directory
SRCDIR = philo

# Source files for the mandatory part
SRC = $(wildcard $(SRCDIR)/*.c)

# Name of the executable
NAME = philo

# Subfolder for object files
OBJDIR = obj

# Subfolder for the executable
BUILDDIR = build

# Object files for the mandatory part
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

# Rule for creating the library
all: $(BUILDDIR)/$(NAME)

# Rule to create the object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule to create the build directory if it doesn't exist
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Rule to build the object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the executable
$(BUILDDIR)/$(NAME): $(OBJS) | $(BUILDDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Clean rule
clean:
	rm -rf $(OBJDIR)

# Full clean rule
fclean: clean
	rm -rf $(BUILDDIR)

# Rebuild rule
re: fclean all