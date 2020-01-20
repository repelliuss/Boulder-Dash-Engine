#COMPILER
CC := gcc

#SOURCE DIRECTORY
SRCDIR := src/

#BUILD DIRECTORY
BUILDDIR := build/

#COMPILER FLAGS
CFLAGS := -Iinclude -O0

#LIBRARY FLAGS
LDFLAGS := -Wl,--disable-new-dtags,-rpath=./lib/ -L./lib/ -ltinfo -lreadline -lpng16 -lwebp -lSDL2 -lSDL2_image-2.0 -lSDL2_image -lSDL2_ttf -lSDL2_mixer-2.0 -lSDL2_mixer

#Finding Source Files
SRCS := $(wildcard $(SRCDIR)*.c)

#Generating Object Files
OBJS := $(SRCS:$(SRCDIR)%.c=$(BUILDDIR)%.o)

DEPS = $(OBJS:.o=.d)

#Executable Name
EXEC := BoulderDash

#Recipe
$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(BUILDDIR)%.o: $(SRCDIR)%.c dir
	$(CC) -c $(CFLAGS)  $< -o $@
	$(CC) -MM $(CFLAGS)  $< > $(BUILDDIR)$*.d

.PHONY: dir
dir:
	mkdir -p $(BUILDDIR)

-include $(DEPS)	

#Cleaning Recipe

.PHONY: clean
clean:
	rm -f $(EXEC) $(BUILDDIR)*.o $(BUILDDIR)*.d
