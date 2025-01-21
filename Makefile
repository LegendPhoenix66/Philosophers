# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

# Header file
HEADER = philo/philosophers.h

# Source directory
SRCDIR = philosopher

# Source files for the mandatory part
SRC = $(wildcard $(SRCDIR)/*.c)

# Name of the executable
NAME = philo

# Subfolder for object files
OBJDIR = obj

# Object files for the mandatory part
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

# Rule for creating the library
all: $(NAME)

# Rule to create the object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule to build the object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the executable
$(NAME): $(OBJS) | $(BUILDDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Clean rule
clean:
	rm -rf $(OBJDIR)

# Full clean rule
fclean: clean
	rm -rf $(BUILDDIR)

# Rebuild rule
re: fclean all