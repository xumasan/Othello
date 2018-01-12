COMPILER = g++
CFLAGS   = -std=c++11 -Wall
TARGET   = Reversi
OBJDIR   = ../obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR = ..
endif
SOURCES  = $(wildcard *.cxx)
OBJECTS  = $(addprefix $(OBJDIR)/, $(SOURCES:.cxx=.o))
DEPENDS  = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS)
	$(COMPILER) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: %.cxx
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) -o $@ -c $<

all: clean $(TARGET)

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET) ${OBJECTS:.o=.gcda}