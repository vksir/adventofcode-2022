package main

import (
	"aoc/util"
	"bufio"
	"fmt"
	"regexp"
	"strings"
)

type Item struct {
	min    int
	max    int
	letter string
	passwd string
}

type Data struct {
	items []Item
}

func NewData(filename string) *Data {
	var d Data
	d.read(filename)
	return &d
}

func (d *Data) read(filename string) {
	r := util.NewReader(filename)
	defer r.Close()

	pattern := regexp.MustCompile(`(\d+)-(\d+) (.): (.+)`)

	scanner := bufio.NewScanner(r)
	for scanner.Scan() {
		res := pattern.FindStringSubmatch(scanner.Text())
		d.items = append(d.items, Item{
			min:    util.Atoi(res[1]),
			max:    util.Atoi(res[2]),
			letter: res[3],
			passwd: res[4],
		})
	}
}

type Solve1 struct {
	data *Data
}

func NewSolve1(d *Data) *Solve1 {
	return &Solve1{d}
}

func (s *Solve1) Run() int {
	valid := 0
	for _, item := range s.data.items {
		count := strings.Count(item.passwd, item.letter)
		if count >= item.min && count <= item.max {
			valid++
		}
	}
	return valid
}

type Solve2 struct {
	data *Data
}

func NewSolve2(d *Data) *Solve2 {
	return &Solve2{d}
}

func (s *Solve2) Run() int {
	valid := 0
	for _, item := range s.data.items {
		item.min--
		item.max--
		if (item.min >= 0 && item.min < len(item.passwd) && item.passwd[item.min:item.min+1] == item.letter) !=
			(item.max >= 0 && item.max < len(item.passwd) && item.passwd[item.max:item.max+1] == item.letter) {
			valid++
		}
	}
	return valid
}

func main() {
	data := NewData("input.txt")
	util.TimeIt(func() {
		fmt.Println("Part1:", NewSolve1(data).Run())
		fmt.Println("Part2:", NewSolve2(data).Run())
	})
}
