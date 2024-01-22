EXEC = koda.out

CC = gcc
CFLAGS = -g -I./src

SRCDIR = src
OBJDIR = obj

rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CFILES := $(call rwildcard, $(SRCDIR), *.c)
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CFILES))

all: $(OBJS) link

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ mkdir -m 777 -p $(@D)
	$(CC) $(CFLAGS) -Isrc -c $^ -o $@

link: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(EXEC)

run:
	./koda.out ./examples/main.kd