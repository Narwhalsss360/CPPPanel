BINARY = PanelController.dll
OBJECTSDIR = obj
INCLUDEDIRS = headers source
SRCDIRS = source

CC = cl
CFLAGS = /Zi /EHsc /nologo $(foreach DIR,$(INCLUDEDIRS),/I"$(DIR)")
LNK = link
LNKFLAGS = /DLL
CPPFILES = $(foreach PATH,$(SRCDIRS),$(wildcard $(PATH)/*.cpp))
OBJECTS = $(addprefix $(OBJECTSDIR)/,$(patsubst %.cpp,%.o,$(CPPFILES)))

all: link

link: $(BINARY)

compile: $(OBJECTS)

$(BINARY): $(OBJECTS)
	@echo Linking...
	@$(LNK) $(LNKFLAGS) $^ /OUT:$@

$(OBJECTSDIR)/%.o: %.cpp
	@if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	@echo Compiling $^
	@$(CC) $(CFLAGS) /c $^ /Fo$@

clean:
	@if exist $(BINARY) del /f /q $(BINARY)
	@if exist *.pdb del /f /q *.pdb
	@if exist $(OBJECTSDIR) rmdir /s /q $(OBJECTSDIR)
