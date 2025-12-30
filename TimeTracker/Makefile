CC := gcc
NEW_ENTRY_APPNAME := new_entry

SRCDIR := src
INCDIR := inc
OBJDIR := obj
BINDIR := bin

NEW_ENTRY_SRCS := main.c shared.c
NEW_ENTRY_SRCS := $(addprefix $(SRCDIR)/,$(NEW_ENTRY_SRCS))

NEW_ENTRY_OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(NEW_ENTRY_SRCS))

all: $(BINDIR)/$(NEW_ENTRY_APPNAME)

$(BINDIR)/$(NEW_ENTRY_APPNAME): $(NEW_ENTRY_OBJS)
	@if not exist $(BINDIR) mkdir $(BINDIR)
	$(CC) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	$(CC) -I$(INCDIR) -c $< -o $@