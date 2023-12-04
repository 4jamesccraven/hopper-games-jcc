EXE := brisca.exe
CXX := g++

SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./obj
BINDIR = ./bin

CXXFlags = -I$(INCDIR) -I../.shared_inc -Wall -pedantic

SRC = $(wildcard $(SRCDIR)/*.cpp)
INC = $(wildcard $(INCDIR)/*.h)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all
all: $(BINDIR)/$(EXE)

$(BINDIR)/$(EXE): $(OBJ)
	$(CXX) $(CXXFlags) -o $@ $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFlags) -o $@ -c $<

.PHONY: clean, cleanwin
clean:
	rm -f $(BINDIR)/*.exe $(OBJDIR)/*.o

cleanwin:
	Powershell -Command "Remove-Item .\obj\*.o; Remove-Item .\bin\*.exe"
