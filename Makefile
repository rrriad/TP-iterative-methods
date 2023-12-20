##########################################
# Makefile for TP1 Code                 #
#                                      #
# Author: T. Dufaud                    #
##########################################

# Compiler and options
CC=gcc
OPTC=-fPIC -march=native

# Directories
TPDIR=.
TPDIRSRC=$(TPDIR)/src
BINDIR=$(TPDIR)/bin

# Libraries and include directories
# Update LIBS with your libraries
LIBS=-lm 
INCL=-I $(TPDIR)/include -I/usr/include

# Object files
OBJLIB=lib_poisson1D.o
OBJITER=tp_poisson1D_iter.o

# Targets
all: $(BINDIR)/tpPoisson1D_iter

# Compile lib_poisson1D.o
$(OBJLIB): $(TPDIRSRC)/lib_poisson1D.c
	$(CC) $(OPTC) -c $(INCL) $< -o $@

# Compile tp_poisson1D_iter.o
$(OBJITER): $(TPDIRSRC)/tp_poisson1D_iter.c
	$(CC) $(OPTC) -c $(INCL) $< -o $@

# Linking
$(BINDIR)/tpPoisson1D_iter: $(OBJLIB) $(OBJITER)
	$(CC) -o $@ $(OPTC) $^ $(LIBS)

# Run the tpPoisson1D_iter target
run_tpPoisson1D_iter: $(BINDIR)/tpPoisson1D_iter
	$<

# Clean up object files and executables
clean:
	rm -f *.o $(BINDIR)/*

