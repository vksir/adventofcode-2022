all: build

build:
	$(foreach day, $(wildcard day*/day*.go), go build -o build/ $(day);)

execute:
	$(foreach exe, $(wildcard build/*.exe), echo -e "[Execute] $(exe)\n`./$(exe)`\n";)

clean:
	rm -rf build

run: build execute clean
