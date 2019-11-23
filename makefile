SRCDIR = ./src
TESTDIR = ./test
BUILDDIR = ./build

IDIR = ./src
_DEPS = matrix_utilities.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = ./obj
_OBJ = matrix_utilities.o test-library.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

CC = gcc
CFLAGS = -std=gnu99 -g -O2 -Wformat -Werror=format-security -Wdate-time \
	 -I$(IDIR) 

LIBS = -lm 

test: $(OBJ) $(ODIR)/test-library.o
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ $^ $(LIBS)

# Source files
$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC)  $(CFLAGS) -c -o $@ $<

$(ODIR)/%.o: $(TESTDIR)/test-library.c $(DEPS)
	$(CC)  $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean: 
	rm -f $(ODIR)/*.o 
	rm -f $(BUILDDIR)/*

