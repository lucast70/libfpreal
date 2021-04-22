TARGETS=$(patsubst %.c,%,$(wildcard *.c))

all: clean $(TARGETS)

$(TARGETS):
	@echo "================================="
	@echo "Building " $@.c
	@echo "================================="
	$(CC) $(CFLAGS) -I../include $(EXTRAFLAGS) $(CPPFLAGS)  $@.c -o $@ -L../lib -l$(PRJNAME) $(LIBS) 

clean:
	rm -f $(TARGETS) 
