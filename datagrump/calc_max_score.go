package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
	"regexp"
	"strconv"
)

var output_folder = flag.String("output-folder", "", "Folder that contains the run-contest outputs")

var max_score = 0.0
var max_filename = ""

func main() {
	flag.Parse()
	if *output_folder == "" {
		fmt.Println("Please provide an output folder")
		return
	}

	if _, err := os.Stat(*output_folder); os.IsNotExist(err) {
		fmt.Println("Invalid order data folder")
		return
	}

	filepath.Walk(*output_folder, func(path string, info os.FileInfo, err error) error {
		if !info.IsDir() {
			fmt.Printf("%s: ", filepath.Base(path))
			content, err := ioutil.ReadFile(path)
			if err != nil {
				fmt.Println("Invalid")
				return nil
			}
			// Get the throughput
			throughput_exp := regexp.MustCompile(`throughput: [0-9.]*`)
			throughput := throughput_exp.Find(content)
			if throughput == nil {
				fmt.Println("Invalid")
				return nil
			}
			throughput = throughput[12:]
			throughput_num, err := strconv.ParseFloat(string(throughput), 64)
			if err != nil {
				fmt.Println("Invalid")
				return nil
			}
			// Get the delay
			delay_exp := regexp.MustCompile(`signal delay: [0-9]*`)
			delay := delay_exp.Find(content)
			if delay == nil {
				fmt.Println("Invalid")
				return nil
			}
			delay = delay[14:]
			delay_num, err := strconv.ParseFloat(string(delay), 64)
			if err != nil {
				fmt.Println("Invalid")
				return nil
			}
			score := throughput_num * 1000 / delay_num
			if score > max_score {
				max_score = score
				max_filename = filepath.Base(path)
			}
			fmt.Println(score)
		}
		return nil
	})
	fmt.Printf("Max score is %2.2f @ %s\n", max_score, max_filename)
}
