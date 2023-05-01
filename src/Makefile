clang_path	= ../materials/build/scripts/
DIRS		= ./cat ./grep ./common
SOURCES 	:= $(shell find $(DIRS) -name '*.c')
SOURCES		+= $(shell find $(DIRS) -name '*.h')
all: clear build_all
clear:
	clear
clean:
	cd ./cat && make clean
	cd ./grep && make clean
	rm -rf .clang-format
s21_cat:
	cd ./cat && make
s21_grep:
	cd ./grep && make
docker:
	cd ../materials/build; sh ./run2.sh
testing:
	cd ./cat && make testing
	cd ./grep && make testing
clang: clear
	clang-format -style=Google -n $(SOURCES)
clang_replace: clear
	clang-format -style=Google -i $(SOURCES)
build_all: s21_cat s21_grep