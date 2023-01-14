thing_right := $(wildcard day1/*.go)

all: build

build:
	go build -o build/ day*/*.go

execute:
	./build/*.exe

clean:
	rm -rf build

run: build execute clean
