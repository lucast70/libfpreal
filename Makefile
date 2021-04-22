PRJNAME=fpreal
EXAMPLES=examples
CTEST=ctest
SRC=src
OBJS=objs

CXXHEADER=$(PRJNAME)xx.h

LIBMAJOR=0
LIBMINOR=0
LIBPATCH=1
LIBNAME=lib$(PRJNAME)
SOEXT=so

OS := $(shell uname)
ARCH := $(shell uname -m)

ifeq ($(CC),)
CC=cc
endif

ifeq ($(CXX),)
CC=c++
endif

ifeq ($(LD),)
LD=$(CC)
endif

ifeq ($(PREFIX),)
PREFIX=/usr/local
endif

ifeq ($(LIBPREFIX),)
LIBPREFIX=$(PREFIX)/lib
endif

ifeq ($(CFLAGS),)
CFLAGS=-O
endif

ifeq ($(CXXFLAGS),)
CFLAGS=-O
endif

ifeq ($(CPPFLAGS),)
CPPFLAGS=-DFPREAL_USE_CONSTEXPR
endif

# ifeq ($(AR),)
# AR=ar
# endif

# ifeq ($(ARFLAGS),)
# ARFLAGS="-crs"
# endif

### Linux
LBITS := $(shell $(CC) $(CFLAGS) -dM -E - </dev/null | grep -q "__LP64__" && echo 64 || echo 32)

ifeq ($(OS),Linux)
EXTRAFLAGS=-Wl,-rpath -Wl,../lib -L../lib
CFLAGS+=-fPIC
CXXFLAGS+=-fPIC
ifeq ($(LDFLAGS),)
LDFLAGS=-shared
endif

ifeq ($(LBITS),64)
LIBPREFIX=$(PREFIX)/lib64
endif

endif

### Solaris
ifeq ($(OS),SunOS)

ifeq ($(CC),gcc)
LDFLAGS+=--shared
ifeq ($(CFLAGS),)
CFLAGS=-fPIC -pthreads -std=gnu99 -Wall
else
CFLAGS+=-fPIC -pthreads -std=gnu99
endif
endif

ifeq ($(CC),cc)
LDFLAGS+=-G
ifeq ($(CFLAGS),)
CFLAGS=-xc99 
else
CFLAGS+=-xc99
endif
endif

endif



export

all:
	@echo "================================="
	@echo "Building for "$(OS)"..."
	@echo "================================="
	mkdir -p lib 
	@$(MAKE) -C $(SRC) -f Makefile	
	@$(MAKE) -C $(OBJS) -f Makefile.static	
	@$(MAKE) -C $(OBJS) -f Makefile
	@$(MAKE) -C $(CTEST) -f Makefile
	@$(MAKE) -C $(EXAMPLES) -f Makefile
	

install: all
	mkdir -p $(LIBPREFIX)
	mkdir -p $(PREFIX)/include
	rm -f $(LIBPREFIX)/$(LIBNAME).$(SOEXT)*
	cp lib/$(LIBNAME).a $(LIBPREFIX)
	cp lib/$(LIBNAME).$(SOEXT).$(LIBMAJOR).$(LIBMINOR).$(LIBPATCH) $(LIBPREFIX)
	ln -s $(LIBPREFIX)/$(LIBNAME).$(SOEXT).$(LIBMAJOR).$(LIBMINOR).$(LIBPATCH) $(LIBPREFIX)/$(LIBNAME).$(SOEXT)
	cp include/$(CXXHEADER) $(PREFIX)/include
clean:
	rm -f lib/*
	@$(MAKE) -C $(SRC) -f Makefile clean
	@$(MAKE) -C $(EXAMPLES) -f Makefile clean
	@$(MAKE) -C $(OBJS) -f Makefile clean
	@$(MAKE) -C $(CTEST) -f Makefile clean
	@$(MAKE) -C $(EXAMPLES) -f Makefile clean
	
