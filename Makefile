##
# @file Makefile
# @author Zdeněk Šťastný (xstast41@stud.fit.vutbr.cz)
# @author Jozef Gallo (xgallo06@stud.fit.vutbr.cz)

EXEC = ICP
PACK_FILE = xgallo06_xstast41.zip

PRO = $(wildcard src/*.pro)
BUILD_DIR = build
DOCS_DIR = doc/html
SRC_DIR = src
EXAMPLES_DIR = examples

.PHONY: all clean run pack doxygen readme_txt

all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && qmake ../$(PRO) && make

clean:
	cd $(BUILD_DIR) && rm -rf * .[!.]*
	rm -rf build-ICP-Desktop-Debug
	rm -rf $(DOCS_DIR)
	rm -f $(PACK_FILE)
	rm -f README.txt

run: all
	./$(BUILD_DIR)/$(EXEC)

doxygen: clean
	doxygen Doxyfile

readme_txt:
	cp README.md README.txt

pack: clean readme_txt
	zip -r $(PACK_FILE) $(SRC_DIR) $(DOCS_DIR) $(EXAMPLES_DIR) Makefile Doxyfile README.txt README.md
