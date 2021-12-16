package main

import (
	"fmt"
	"bufio"
	"log"
	"os"
)


func SolveOne(rows []string) {
	var xPos int = 0
	var nTrees int = 0
	for _, row := range rows{
		if (xPos >= len(row)){
			xPos = xPos - len(row) 
		}
		if (byte(row[xPos]) == byte('#')){
			nTrees++
		}
		xPos += 3
	}
	fmt.Println("Part 1: ", nTrees)
}


func SolveTwo(rows []string) {
	var nTrees int = 0
	var pos int = 0
	xTrav := [5]int{1, 3, 5, 7, 1}
	var multiTrees int = 0
	for idx, x := range xTrav {
		for i := 0; i < len(rows); i++ {
			if (pos >= len(rows[i])){
				pos = pos - len(rows[i]) 
			}
			if (byte(rows[i][pos]) == byte('#')){
				nTrees++
			}
			if (idx == (len(xTrav) - 1)) {
				i++
			}
			pos += x
		}
		if (multiTrees == 0){
			multiTrees = nTrees
		} else {
			multiTrees *= nTrees
		}
		pos = 0
		nTrees = 0
	}
	fmt.Println("Part 2: ", multiTrees)
}


func main() {
	file, err := os.Open("../../input_day3.txt")

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
