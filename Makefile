.PHONY: all build run clean lint

all: run clean

lint:
	@command -v clang-tidy >/dev/null 2>&1
	@clang-tidy day01.cpp -- -I. >/dev/null 2>&1

build: lint
	@mkdir -p build
	@cd build && cmake .. >/dev/null 2>&1 && cmake --build . >/dev/null 2>&1

run: build
	@echo "DAY 1 SOLUTION:"
	@mkdir -p tmp
	@g++ -x c++ day01.cpp -o /tmp/solve >/dev/null 2>&1 && /tmp/solve && rm /tmp/solve
	@echo "DAY 2 SOLUTION:"

clean:
	@rm -rf build