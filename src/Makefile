objects=$(patsubst %.cpp,%,$(wildcard *.cpp))

all: $(objects)

$(objects):
	@echo "================================="
	@echo "Building " $@.cpp 
	@echo "================================="
	$(CXX) -I../include $(CXXFLAGS) $(CPPFLAGS) -c $@.cpp
	mv $@.o ../$(OBJS)
        
clean:
	rm -f *.o *~        
	
	
