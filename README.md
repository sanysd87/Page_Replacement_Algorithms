Project Title: Page Replacement Algorithms

Language: C++

Description: The purpose of this project is to stimulate the three basic algorithms, first in, first out (FIFO), least recently used (LRU), and optimal, to show what is the best algorithm (the one with the least amount of page faults). The program takes in a string of numbers that are comma-separated. It then parses the string and turns the string into a vector of integers. Then, the algorithm functions are called. If you run the program, you will find that optimal is the most optimal. In this project, optimal is the best algorithm, but in reality, it is only theoretically the best as it is not feasible in practical scenarios due to its need for future knowledge of page requests.

When you download the project, you can run it on basically any IDE. Many popular ones are Visual Studio, Visual Studio code, Online IDE, and Online GDB.
If you want to try to put new pages in the page reference string, simply change "std::string input = "1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5";" in line 105 and put or use your own numbers. If you want to change the frame count, simply change the "frame_count" variable in line 106. The functions that stimulate First in, first out (FIFO), Least recently used (LRU), and optimal should not be changed, though, as they already work.
