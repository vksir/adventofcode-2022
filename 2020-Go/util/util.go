package util

import (
	"fmt"
	"os"
	"path"
	"runtime"
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

func getInputPath(filename string) string {
	_, p, _, _ := runtime.Caller(2)
	return path.Join(path.Dir(p), filename)
}

func TimeIt(f func()) {
	t := time.Now()
	f()
	fmt.Printf("Cost: %dms\n", time.Since(t).Milliseconds())
}
