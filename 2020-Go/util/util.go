package util

import (
	"fmt"
	"golang.org/x/exp/constraints"
	"os"
	"path"
	"runtime"
	"strconv"
	"strings"
	"time"
)

func ReadInput(filename string) string {
	c, err := os.ReadFile(getInputPath(filename))
	if err != nil {
		panic(err)
	}
	return strings.ReplaceAll(string(c), "\r\n", "\n")
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

func MustAtoi(s string) int {
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

func Max[T constraints.Ordered](first T, others ...T) T {
	for _, i := range others {
		if i > first {
			first = i
		}
	}
	return first
}
