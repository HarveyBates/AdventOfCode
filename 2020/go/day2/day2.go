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
	var valid int = 0
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
	fmt.Println("Part 1: ", valid)
}


func SolveTwo(rows []string){
	var posOne int
	var posTwo  int
	var letter byte
	var chars string
	var count int = 0
	for _, row := range rows {
		for index, val := range strings.Split(row, " ") {
			if (index == 0) {
				minMax := strings.Split(val, "-")
				posOne, _ = strconv.Atoi(minMax[0])
				posTwo , _ = strconv.Atoi(minMax[1])
			} else if (index == 1) {
				letter = val[0]
			} else if (index == 2) {
				chars = val
			}
		}

		if(byte(chars[posOne - 1]) == letter && byte(chars[posTwo - 1]) != letter) {
			count++
		}
		if(byte(chars[posOne - 1]) != letter && byte(chars[posTwo - 1]) == letter) {
			count++
		}
			
 	}
	fmt.Println("Part 2: ", count)
}



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

	SolveTwo(rows)

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

}
