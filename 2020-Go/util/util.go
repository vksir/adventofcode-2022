package util

import (
	"fmt"
	"os"
	"path"
	"runtime"
	"strconv"
	"strings"
	"time"
)

type Reader struct {
	*os.File
}

func NewReader(filename string) *Reader {
	file, err := os.Open(getInputPath(filename))
	if err != nil {
		panic(err)
	}
	return &Reader{file}
}

func (f *Reader) Close() {
	err := f.File.Close()
	if err != nil {
		panic(err)
	}
}

func ReadInputLines(filename string) []string {
	c, err := os.ReadFile(getInputPath(filename))
	if err != nil {
		panic(err)
	}
	return strings.Split(string(c), "\n")
}

func getInputPath(filename string) string {
	_, p, _, _ := runtime.Caller(2)
	return path.Join(path.Dir(p), filename)
}

func TimeIt(f func()) {
	t := time.Now()
	f()
	fmt.Printf("Cost: %dms\n", time.Since(t).Milliseconds())
}

func Atoi(s string) int {
	num, err := strconv.Atoi(s)
	if err != nil {
		panic(err)
	}
	return num
}

func Assert(b bool) {
	if !b {
		panic("Assert failed")
	}
}
