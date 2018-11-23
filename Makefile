
override CPPFLAGS	+= --std=c++1z
override CPPFLAGS	+= -MMD -MP
override CPPFLAGS	+= $(shell cat .cxxflags | xargs)
override CPPFLAGS	+= -I./include
override LDFLAGS	+= $(shell cat .ldflags | xargs)
override LDFLAGS	+= -L./lib
override LDLIBS		+= -lsimple_graphical -lsimple_interactive -lsimple_sdlcore -lSDL2main -lSDL2 -lpthread -lnanovg -lGL -lGLEW

SOURCES	:= $(shell echo *.cpp)
TEMPDIR	:= temp
DISTDIR	:= out
TARGET	:= $(DISTDIR)/main
OBJECTS	:= $(SOURCES:%.cpp=$(TEMPDIR)/%.o)
DEPENDS	:= $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) | $(DISTDIR)
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

$(TEMPDIR)/%.o: %.cpp | $(TEMPDIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

$(TEMPDIR):
	@mkdir $@

$(DISTDIR):
	@mkdir $@

clean:
	@rm $(DEPENDS) 2> /dev/null || true
	@rm $(OBJECTS) 2> /dev/null || true
	@rmdir $(TEMPDIR) 2> /dev/null || true
	@echo Temporaries cleaned!

distclean: clean
	@rm $(TARGET) 2> /dev/null || true
	@rmdir $(DISTDIR) 2> /dev/null || true
	@echo All clean!

-include $(DEPENDS)

.PRECIOUS : $(OBJECTS)
.PHONY : clean distclean
