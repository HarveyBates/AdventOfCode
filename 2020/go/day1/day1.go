package main

import (
	"fmt"
	"bufio"
	"log"
	"os"
	"strconv"
)


func SolveOne(nums []int) int {
	for _, x := range nums {
		for _, y := range nums {
			if (x + y) == 2020 {
				return x * y
			}
		}
	}
	return 0
}


func SolveTwo(nums []int) int {
	for _, x := range nums {
		for _, y := range nums {
			for _, z := range nums {
				if (x + y + z) == 2020 {
					return x * y * z
				}
			}
		}
	}
	return 0
}



func main() {
	file, err := os.Open("../../input_day1.txt")

	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	var nums []int
	for scanner.Scan() {
		row, _ := strconv.Atoi(scanner.Text())
		nums = append(nums, row)
	}

	answerOne := SolveOne(nums)
	fmt.Println(answerOne)

	answerTwo := SolveTwo(nums)
	fmt.Println(answerTwo)

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

}
