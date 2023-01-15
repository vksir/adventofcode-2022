package main

import (
	"aoc/util"
	"fmt"
	"strings"
)

type Data struct {
	nums []int
}

func NewData(filename string) *Data {
	var d Data
	d.parse(util.ReadInput(filename))
	return &d
}

func (d *Data) parse(content string) {
	for _, line := range strings.Split(content, "\n") {
		d.nums = append(d.nums, util.MustAtoi(line))
	}
}

type Solve1 struct {
	data *Data
}

func NewSolve1(d *Data) *Solve1 {
	return &Solve1{d}
}

func (s *Solve1) Run() int {
	for i, a := range s.data.nums {
		for j, b := range s.data.nums {
			if i != j && a+b == 2020 {
				return a * b
			}
		}
	}
	panic("Result not found")
}

type Solve2 struct {
	data *Data
}

func NewSolve2(d *Data) *Solve2 {
	return &Solve2{d}
}

func (s *Solve2) Run() int {
	for i, a := range s.data.nums {
		for j, b := range s.data.nums {
			for k, c := range s.data.nums {
				if i != j && i != k && j != k && a+b+c == 2020 {
					return a * b * c
				}
			}
		}
	}
	panic("Result not found")
}

func main() {
	data := NewData("input.txt")
	util.TimeIt(func() {
		fmt.Println("Part1:", NewSolve1(data).Run())
		fmt.Println("Part2:", NewSolve2(data).Run())
	})
}
