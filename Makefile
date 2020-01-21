#COMPILER
CC := gcc

#SOURCE DIRECTORY
SRCDIR := src/

#BUILD DIRECTORY
BUILDDIR := build/

#COMPILER FLAGS
CFLAGS := -Iinclude -O0

#LIBRARY FLAGS
LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

#Finding Source Files
SRCS := $(wildcard $(SRCDIR)*.c)

#Generating Object Files
OBJS := $(SRCS:$(SRCDIR)%.c=$(BUILDDIR)%.o)

DEPS = $(OBJS:.o=.d)

#Executable Name
EXEC := BoulderDash

#Recipe
.PHONY: $(BUILDDIR)
$(EXEC): $(BUILDDIR) $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(BUILDDIR)%.o: $(SRCDIR)%.c
	$(CC) -c $(CFLAGS)  $< -o $@
	$(CC) -MM $(CFLAGS)  $< > $(BUILDDIR)$*.d

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

-include $(DEPS)	

#Cleaning Recipe

.PHONY: clean
clean:
	rm -f $(EXEC) $(BUILDDIR)*.o $(BUILDDIR)*.d
