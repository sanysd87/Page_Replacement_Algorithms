#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>    //stronger than queue
#include <algorithm>
#include <sstream>

std::vector<int> parseInput(const std::string& input) {     //function that parese the input and turns string into a vector of integers
    std::vector<int> pages;     //the vector "page" being declared
    std::stringstream ss(input);    
    int number;
    while (ss >> number) {      //ss >> number checks for the integers
        pages.push_back(number);    //push in the vector
        if (ss.peek() == ',')       //checks for commas to ignore
            ss.ignore();
    }
    return pages;
}

int FIFO_function(const std::vector<int>& pages, int frame_count) {      //Function that stimulate FIFO page replacement
    std::deque<int> frames;     //deque is used for easy removal 
    int page_faults = 0;        //defines page_faults as an integer
    for (int page : pages) {    //for the amount of pages
        auto it = std::find(frames.begin(), frames.end(), page);       //Check if the page is already in one of the frames as per the requirement of FIFO
        if (it == frames.end()) {
            //Page fault
            page_faults++;      //increments page fault
            if (frames.size() == frame_count) {
                frames.pop_front();     //pops/remove the oldes page
            }
            frames.push_back(page);  //Add new page
            std::cout << "Page fault (" << page << ") - Frames: ";
            for (int frame : frames) std::cout << frame << " ";
            std::cout << "Faults: " << page_faults << std::endl;
        }
    }
    return page_faults;
}

int LRU_function(const std::vector<int>& pages, int frame_count) {       //Function that stimulates LRU page replacement
    std::list<int> frames;      //Using list to maintain the order of LRU and because it is easy to remove from both ends
    std::unordered_map<int, std::list<int>::iterator> map; // Map to find pages quickly

    int page_faults = 0;

    for (int page : pages) {
        if (map.find(page) == map.end()) {      //if page == end then page fault
            page_faults++;      //increments page_fault
            if (frames.size() == frame_count) {
                int last = frames.back();
                frames.pop_back();
                map.erase(last);
            }
            frames.push_front(page);
            map[page] = frames.begin();
        }
        else {
            frames.erase(map[page]);        //Moves a recently accessed page to the front if it's already in memory.
            frames.push_front(page);        //Inserts the most recently used page at the front.
            map[page] = frames.begin();
        }
        //print order as per the example output
        std::cout << "Page fault (" << page << ") - Frames: ";
        for (int f : frames) std::cout << f << " ";
        std::cout << "Faults: " << page_faults << std::endl;
    }
    return page_faults;
}

int Optimal_function(const std::vector<int>& pages, int frame_count) {      //function that stimulates optimal page replacement 
    std::vector<int> frames;
    int page_faults = 0;
    for (size_t i = 0; i < pages.size(); i++) {
        int page = pages[i];
        auto iter = std::find(frames.begin(), frames.end(), page);
        if (iter == frames.end()) {     //Page fault
            page_faults++;
            if (frames.size() < frame_count) {
                frames.push_back(page);
            }
            else {
                //The two variables below determines which frame to replace based on future use
                int farthest = -1;
                int idx = -1;
                for (int j = 0; j < frame_count; j++) {
                    //std::distance() calculates how far in the future a frame will next be used.
                    int next_use = std::distance(pages.begin() + i, std::find(pages.begin() + i, pages.end(), frames[j]));
                    if (next_use > farthest) {      //This if condition finds the page that won't be used for the longest time and replaces it.
                        farthest = next_use;
                        idx = j;
                    }
                }
                frames[idx] = page;
            }
            //order of print statements as per sample output
            std::cout << "Page fault (" << page << ") - Frames: ";
            for (int f : frames) std::cout << f << " ";
            std::cout << "Faults: " << page_faults << std::endl;
        }
    }
    return page_faults;
}

int main() {
    std::string input = "1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5";       //numbers in the sample example
    int frame_count = 4;
    std::vector<int> pages = parseInput(input);     //declaring vector and calline parseInput function

    std::cout << "Simulating FIFO Algorithm:\n";
    int fifo_faults = FIFO_function(pages, frame_count);
    std::cout << "Total Page Faults for FIFO: " << fifo_faults << "\n";

    std::cout << "Simulating LRU Algorithm:\n";
    int lru_faults = LRU_function(pages, frame_count);
    std::cout << "Total Page Faults for LRU: " << lru_faults << "\n";

    std::cout << "Simulating Optimal Algorithm:\n";
    int optimal_faults = Optimal_function(pages, frame_count);
    std::cout << "Total Page Faults for Optimal: " << optimal_faults << "\n";

    return 0;
}