TARGETS=$(patsubst %.cpp,%,$(wildcard *.cpp))

all: clean $(TARGETS)

$(TARGETS):
	@echo "================================="
	@echo "Building " $@.cpp
	@echo "================================="
	$(CXX) $(CXXFLAGS) -I../include $(EXTRAFLAGS) $(CPPFLAGS)  $@.cpp -o $@ -L../lib -l$(PRJNAME) $(LIBS) 

clean:
	rm -f $(TARGETS) 
