package conversion

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

type Converter struct {
	lines []string
}

type RomanSet struct {
	upper string
	mid   string
	lower string
}

var values = map[string]int{"I": 1,
	"V": 5,
	"X": 10,
	"L": 50,
	"C": 100,
	"D": 500,
	"M": 1000,
	"_": 0}

var setUnits = RomanSet{"X", "V", "I"}
var setTens = RomanSet{"C", "L", "X"}
var setHundreds = RomanSet{"M", "D", "C"}

// n := map[string]int{"foo": 1, "bar": 2}
func New(filename string) (*Converter, error) {

	file, err := os.Open(filename)
	if err != nil {
		return nil, fmt.Errorf("Unable to read file %s: %w", filename, err)
	}
	defer file.Close()

	converter := new(Converter)

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		converter.lines = append(converter.lines, scanner.Text())
	}

	return converter, scanner.Err()
}

func (c *Converter) Process() {

	fmt.Printf("--START--\n")
	var arabic = regexp.MustCompile(`^[0-9]+`)
	var roman = regexp.MustCompile(`^[MDCLXVImdclxvi]+`)
	for _, s := range c.lines {
		s = strings.TrimSpace(s)
		res1 := arabic.MatchString(s)
		res2 := roman.MatchString(s)

		if res1 {
			i, _ := strconv.Atoi(s)
			r := c.fromArabicToRoman(i)
			fmt.Printf("%s,%s\n", s, r)
		} else if res2 {
			r := c.fromRomanToArabic(s)
			fmt.Printf("%s,%s\n", s, r)
		} else {
			fmt.Printf("%s,ERROR\n", s)
		}
	}
	fmt.Printf("--END--\n")
}

func (c *Converter) fromRomanToArabic(s string) string {
	x := 0
	s = strings.ToUpper(s)
	s += "_"
	for i := len(s) - 2; i >= 0; i-- {
		// fmt.Printf(" [%d] %s  %d \n", i, string(s[i]), values[string(s[i])])
		lastValue := values[string(s[i+1])]
		thisValue := values[string(s[i])]
		if thisValue < lastValue {
			x -= thisValue
		} else {
			x += thisValue
		}
	}
	return fmt.Sprint(x)
}

func (c *Converter) fromArabicToRoman(i int) string {
	if i < 1 {
		return "ERROR"
	}
	// in := i
	thousands := i / 1000
	i -= thousands * 1000
	hundreds := i / 100
	i -= hundreds * 100
	tens := i / 10
	i -= tens * 10
	units := i

	// fmt.Printf(" %d =  %d %d %d %d\n", in, thousands, hundreds, tens, units)
	roman := strings.Repeat("M", thousands)

	roman += c.getRomanNumeral(hundreds, setHundreds)
	roman += c.getRomanNumeral(tens, setTens)
	roman += c.getRomanNumeral(units, setUnits)

	return roman
}

func (c *Converter) getRomanNumeral(num int, symbols RomanSet) string {
	r := ""
	if num == 9 {
		r += symbols.lower
		r += symbols.upper
	} else if num == 4 {
		r += symbols.lower
		r += symbols.mid
	} else if num >= 5 {
		r += symbols.mid
		r += strings.Repeat(symbols.lower, num-5)
	} else {
		r += strings.Repeat(symbols.lower, num)
	}
	return r
}
