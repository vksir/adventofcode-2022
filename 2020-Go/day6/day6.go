package main

import (
	"aoc/util"
	"fmt"
	"github.com/emirpasic/gods/sets/hashset"
	"strings"
)

type Data struct {
	groups [][]string
}

func NewData(filename string) *Data {
	var d Data
	d.parse(util.ReadInput(filename))
	return &d
}

func (d *Data) parse(content string) {
	content = strings.ReplaceAll(content, "\n\n", "[SEP]")
	rawGroups := strings.Split(content, "[SEP]")
	for _, rawGroup := range rawGroups {
		d.groups = append(d.groups, strings.Split(rawGroup, "\n"))
	}
}

type Solve1 struct {
	data *Data
}

func NewSolve1(d *Data) *Solve1 {
	return &Solve1{d}
}

func (s *Solve1) Run() int {
	sum := 0
	for _, group := range s.data.groups {
		p := hashset.New()
		for _, person := range group {
			for _, ans := range person {
				p.Add(string(ans))
			}
		}
		sum += p.Size()
	}
	return sum
}

type Solve2 struct {
	data *Data
}

func NewSolve2(d *Data) *Solve2 {
	return &Solve2{d}
}

func (s *Solve2) Run() int {
	sum := 0
	for _, group := range s.data.groups {
		var persons []*hashset.Set
		for _, person := range group {
			p := hashset.New()
			for _, ans := range person {
				p.Add(string(ans))
			}
			persons = append(persons, p)
		}
		sameAns := persons[0]
		for _, person := range persons[1:] {
			sameAns = sameAns.Intersection(person)
		}
		sum += sameAns.Size()
	}
	return sum
}

func main() {
	data := NewData("input.txt")
	util.TimeIt(func() {
		fmt.Println("Part1:", NewSolve1(data).Run())
		fmt.Println("Part2:", NewSolve2(data).Run())
	})
}
