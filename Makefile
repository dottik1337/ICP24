NESTED_TARGETS= clean run doxygen

all: 
	$(MAKE) -C src

$(NESTED_TARGETS):
	
	cd src && $(MAKE) $@

pack:
	zip -r Archive.zip doc examples src README.txt Makefile
	