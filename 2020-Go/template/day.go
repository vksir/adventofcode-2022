package main

import (
	"aoc/util"
	"fmt"
	"strings"
)

type Data struct {
}

func NewData(filename string) *Data {
	var d Data
	d.parse(util.ReadInput(filename))
	return &d
}

func (d *Data) parse(content string) {
	for _, line := range strings.Split(content, "\n") {
		fmt.Println(line)
	}
}

type Solve1 struct {
	data *Data
}

func NewSolve1(d *Data) *Solve1 {
	return &Solve1{d}
}

func (s *Solve1) Run() int {
	return 0
}

type Solve2 struct {
	data *Data
}

func NewSolve2(d *Data) *Solve2 {
	return &Solve2{d}
}

func (s *Solve2) Run() int {
	return 0
}

func main() {
	data := NewData("input.txt")
	util.TimeIt(func() {
		fmt.Println("Part1:", NewSolve1(data).Run())
		fmt.Println("Part2:", NewSolve2(data).Run())
	})
}
