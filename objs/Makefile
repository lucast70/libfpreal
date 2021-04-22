objects=$(OBJSDIR)/$(wildcard *.o)

all: lib

lib:
	@echo "================================="
	@echo "Linking "$(LIBNAME).$(SOEXT).$(LIBMAJOR).$(LIBMINOR).$(LIBPATCH) 
	@echo "================================="
	$(CXX) $(LDFLAGS) *.o -o $(LIBNAME).$(SOEXT).$(LIBMAJOR).$(LIBMINOR).$(LIBPATCH) $(LIBS) 
	ln -s $(LIBNAME).$(SOEXT).$(LIBMAJOR).$(LIBMINOR).$(LIBPATCH)  $(LIBNAME).$(SOEXT)
	mv lib*.$(SOEXT)* ../lib
clean:
	rm -f *.o so_locations lib$(PRJNAME)*.so*
