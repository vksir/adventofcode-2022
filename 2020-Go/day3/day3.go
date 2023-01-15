package main

import (
	"aoc/util"
	"bufio"
	"fmt"
)

const (
	TREE = "#"
)

type Slope struct {
	x int
	y int
}

type Data struct {
	lines []string
}

func NewData(filename string) *Data {
	var d Data
	d.read(filename)
	return &d
}

func (d *Data) read(filename string) {
	r := util.NewReader(filename)
	defer r.Close()

	scanner := bufio.NewScanner(r)
	for scanner.Scan() {
		d.lines = append(d.lines, scanner.Text())
	}
}

type Solve1 struct {
	data *Data
}

func NewSolve1(d *Data) *Solve1 {
	return &Solve1{d}
}

func (s *Solve1) Run(slope *Slope) int {
	x := 0
	y := 0
	hit := 0
	for y < len(s.data.lines) {
		x = x % len(s.data.lines[0])
		if s.data.lines[y][x:x+1] == TREE {
			hit++
		}
		x += slope.x
		y += slope.y
	}
	return hit
}

type Solve2 struct {
	s *Solve1
}

func NewSolve2(s *Solve1) *Solve2 {
	return &Solve2{s}
}

func (s *Solve2) Run() int {
	slopes := []Slope{
		{1, 1},
		{3, 1},
		{5, 1},
		{7, 1},
		{1, 2},
	}
	res := 1
	for _, slope := range slopes {
		res *= s.s.Run(&slope)
	}
	return res
}

func main() {
	data := NewData("input.txt")
	util.TimeIt(func() {
		fmt.Println("Part1:", NewSolve1(data).Run(&Slope{3, 1}))
		fmt.Println("Part2:", NewSolve2(NewSolve1(data)).Run())
	})
}
