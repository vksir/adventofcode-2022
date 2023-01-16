package main

import (
	"aoc/util"
	"fmt"
	"sort"
	"strings"
)

const (
	front = "F"
	back  = "B"
	left  = "L"
	right = "R"
)

type Data struct {
	lines []string
}

func NewData(filename string) *Data {
	var d Data
	d.parse(util.ReadInput(filename))
	return &d
}

func (d *Data) parse(content string) {
	for _, line := range strings.Split(content, "\n") {
		d.lines = append(d.lines, line)
	}
}

type Solve1 struct {
	data *Data
}

func NewSolve1(d *Data) *Solve1 {
	return &Solve1{d}
}

func (s *Solve1) Run() int {
	ids := getAllIds(s.data.lines)
	return util.Max(ids[0], ids[1:]...)
}

type Solve2 struct {
	data *Data
}

func NewSolve2(d *Data) *Solve2 {
	return &Solve2{d}
}

func (s *Solve2) Run() int {
	ids := getAllIds(s.data.lines)
	sort.Ints(ids)
	var myIds []int
	for i, id := range ids {
		if i+1 < len(ids) && ids[i+1] == id+2 {
			myIds = append(myIds, id+1)
		}
	}
	util.Assert(len(myIds) == 1)
	return myIds[0]
}

func getAllIds(lines []string) []int {
	var ids []int
	for _, line := range lines {
		rowA := 0
		rowB := 128
		for _, f := range line[:7] {
			rowA, rowB = getArea(rowA, rowB, string(f))
		}
		colA := 0
		colB := 8
		for _, f := range line[7:] {
			colA, colB = getArea(colA, colB, string(f))
		}
		util.Assert(rowA+1 == rowB && colA+1 == colB)
		ids = append(ids, rowA*8+colA)
	}
	return ids
}

func getArea(a, b int, f string) (int, int) {
	util.Assert((a+b)%2 == 0)
	if f == front || f == left {
		return a, (a + b) / 2
	} else if f == back || f == right {
		return (a + b) / 2, b
	} else {
		panic("Invalid flag")
	}
}

func main() {
	data := NewData("input.txt")
	util.TimeIt(func() {
		fmt.Println("Part1:", NewSolve1(data).Run())
		fmt.Println("Part2:", NewSolve2(data).Run())
	})
}
