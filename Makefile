
vpath %.c src

OBJS            := $(patsubst %.c,%.o,$(notdir $(wildcard src/*.c)))

TESTSDIR        := $(strip tests)

CC              ?= $(strip gcc)

export CP       := $(strip cp -f)
export MKDIR    := $(strip mkdir -p)
export RM       := $(strip rm -f)

export CC       := $(strip $(CC))
export CFLAGS   := $(strip $(CFLAGS) -Wall -Wextra -Wpedantic -O0 -g -ggdb)
export CPPFLAGS := $(strip $(CPPFLAGS) -D_GNU_SOURCE -D_POSIX_C_SOURCE -I include)
export LDFLAGS  := $(strip $(LDFLAGS))
export LIBS     := $(strip $(LIBS) $(LOADLIBES))

TARGET = tail

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS)    -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)

.PHONY: check
check:
	$(MAKE) -C $(TESTSDIR)

.PHONY: clean-tests-dir
clean-tests-dir:
	$(MAKE) -C $(TESTSDIR) clean

