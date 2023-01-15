package main

import (
	"aoc/util"
	"fmt"
	"github.com/emirpasic/gods/sets/hashset"
	"regexp"
	"strconv"
	"strings"
)

type Data struct {
	cards []map[string]string
}

func NewData(filename string) *Data {
	var d Data
	d.parse(util.ReadInput(filename))
	return &d
}

func (d *Data) parse(content string) {
	content = strings.ReplaceAll(content, "\n\n", "[SEP]")
	content = strings.ReplaceAll(content, "\n", " ")
	rawCards := strings.Split(content, "[SEP]")
	pattern := regexp.MustCompile(`(\S*):(\S*)`)
	for _, rawCard := range rawCards {
		results := pattern.FindAllStringSubmatch(rawCard, -1)
		card := make(map[string]string, len(results))
		for _, result := range results {
			card[result[1]] = result[2]
		}
		d.cards = append(d.cards, card)
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
	for _, card := range s.data.cards {
		if validCardKeys(card) {
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
	for _, card := range s.data.cards {
		if validCardKeys(card) && validCardValues(card) {
			valid++
		}
	}
	return valid
}

var requiredKeys = []string{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}
var valueValidators = map[string]func(string) bool{
	"byr": func(v string) bool {
		i, err := strconv.Atoi(v)
		if err != nil {
			return false
		}
		return i >= 1920 && i <= 2002
	},
	"iyr": func(v string) bool {
		i, err := strconv.Atoi(v)
		if err != nil {
			return false
		}
		return i >= 2010 && i <= 2020
	},
	"eyr": func(v string) bool {
		i, err := strconv.Atoi(v)
		if err != nil {
			return false
		}
		return i >= 2020 && i <= 2030
	},
	"hgt": func(v string) bool {
		if strings.Contains(v, "cm") {
			i := util.MustAtoi(strings.ReplaceAll(v, "cm", ""))
			return i >= 150 && i <= 193
		} else if strings.Contains(v, "in") {
			i := util.MustAtoi(strings.ReplaceAll(v, "in", ""))
			return i >= 59 && i <= 76
		} else {
			return false
		}
	},
	"hcl": func(v string) bool {
		pattern := regexp.MustCompile(`#[0-9a-f]{6}`)
		return pattern.MatchString(v)
	},
	"ecl": func(v string) bool {
		values := hashset.New("amb", "blu", "brn", "gry", "grn", "hzl", "oth")
		return values.Contains(v)
	},
	"pid": func(v string) bool {
		_, err := strconv.Atoi(v)
		if err != nil {
			return false
		}
		return len(v) == 9
	},
}

func validCardKeys(c map[string]string) bool {
	for _, k := range requiredKeys {
		if _, in := c[k]; !in {
			return false
		}
	}
	return true
}

func validCardValues(c map[string]string) bool {
	for k, v := range c {
		if validator, ok := valueValidators[k]; ok {
			if !validator(v) {
				return false
			}
		}
	}
	return true
}

func main() {
	data := NewData("input.txt")
	util.TimeIt(func() {
		fmt.Println("Part1:", NewSolve1(data).Run())
		fmt.Println("Part2:", NewSolve2(data).Run())
	})
}
