package main

import (
	"aoc/util"
	"fmt"
	"regexp"
	"strings"
)

const (
	yourBag = "shiny gold"
)

type Data struct {
	bagContains map[string]map[string]int
}

func NewData(filename string) *Data {
	d := Data{make(map[string]map[string]int)}
	d.parse(util.ReadInput(filename))
	return &d
}

func (d *Data) parse(content string) {
	keyPattern := regexp.MustCompile(`^(\S+? \S+?) bags?`)
	valuePattern := regexp.MustCompile(`(\d+) (\S+? \S+?) bags?`)

	for _, line := range strings.Split(content, "\n") {
		keyRes := keyPattern.FindStringSubmatch(line)
		valueRes := valuePattern.FindAllStringSubmatch(line, -1)

		contains := make(map[string]int)
		for _, r := range valueRes {
			contains[r[2]] = util.MustAtoi(r[1])
		}
		d.bagContains[keyRes[1]] = contains
	}
}

type Solve1 struct {
	data *Data
	dp   map[string]bool
}

func NewSolve1(d *Data) *Solve1 {
	return &Solve1{d, make(map[string]bool)}
}

func (s *Solve1) Run() (result int) {
	for bag := range s.data.bagContains {
		if s.contain(bag) {
			result++
		}
	}
	return
}

func (s *Solve1) contain(bag string) bool {
	if contain, in := s.dp[bag]; in {
		return contain
	}
	for containBag := range s.data.bagContains[bag] {
		if containBag == yourBag || s.contain(containBag) {
			s.dp[bag] = true
			return true
		}
	}
	s.dp[bag] = false
	return false
}

type Solve2 struct {
	data *Data
	dp   map[string]int
}

func NewSolve2(d *Data) *Solve2 {
	return &Solve2{d, make(map[string]int)}
}

func (s *Solve2) Run() (result int) {
	return s.getContainNum(yourBag)
}

func (s *Solve2) getContainNum(bag string) int {
	if containNum, in := s.dp[bag]; in {
		return containNum
	}
	containNum := 0
	for containBag, num := range s.data.bagContains[bag] {
		containNum += (s.getContainNum(containBag) + 1) * num
	}
	s.dp[bag] = containNum
	return containNum
}

func main() {
	data := NewData("input.txt")
	util.TimeIt(func() {
		fmt.Println("Part1:", NewSolve1(data).Run())
		fmt.Println("Part2:", NewSolve2(data).Run())
	})
}
