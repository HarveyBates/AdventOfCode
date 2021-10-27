package main

import (
	"fmt"
	"bufio"
	"log"
	"os"
	"strings"
	"strconv"
)


func SolveOne(rows []string) {
	var min int
	var max int
	var letter byte
	var chars string
	valid := 0
	for _, row := range rows {
		for index, val := range strings.Split(row, " ") {
			if (index == 0) {
				minMax := strings.Split(val, "-")
				min, _ = strconv.Atoi(minMax[0])
				max, _ = strconv.Atoi(minMax[1])
			} else if (index == 1) {
				letter = val[0]
			} else if (index == 2) {
				chars = val
			}

		}
		count := 0
		for _, char := range chars {
			if (byte(char) == letter) {
				count++
			}
		}
		if (count >= min && count <= max) {
			valid++
		}
	}
	fmt.Println(valid)
}


//func SolveTwo(nums []int) int {
//}



func main() {
	file, err := os.Open("../../input_day2.txt")

	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	var rows []string
	for scanner.Scan() {
		row := scanner.Text()
		rows = append(rows, row)
	}

	SolveOne(rows)
	//fmt.Println(answerOne)

	//answerTwo := SolveTwo(nums)
	//fmt.Println(answerTwo)

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

}
