#include <iostream>
#include <fstream>

void open_file();
void close_file();
bool get_next_line();
int move_count_p1();
int move_count_p2();
int main();

//Stores the file data
std::ifstream file{};
//Stores the data in the line
std::string direction{""};
int magnitude{0};

void open_file() {

    if(file.is_open()) {
        file.close();
    }

    file.open("dive_log.txt");

    if( !(file.is_open()) ) {
        std::cout << "[ERROR]: Could not open file." << std::endl;
    }
}

void close_file() {
    file.close();
}

bool get_next_line() {
    if(file >> direction >> magnitude) {
        return true;
    } else {
        return false;
    }
}

int move_count_p1() {
    //No negatives in text file

    int depth{0};
    int horizontal_pos{0};

    while(get_next_line()) {

        std::cout << direction << " " << magnitude << std::endl;

        if(direction == "down") {
            depth += magnitude;
        } else if(direction == "up") {
            depth -= magnitude;
        } else if(direction == "forward") {
            horizontal_pos += magnitude;
        } else {
            std::cout << "[ERROR]: No direction specified." << std::endl;
        }
    }
    return (horizontal_pos * depth);
}

int move_count_p2() {

    int depth{0};
    int horizontal_pos{0};
    int aim{0};

    while(get_next_line()) {

        std::cout << direction << " " << magnitude << std::endl;

        if(direction == "down") {
            aim += magnitude;
        } else if(direction == "up") {
            aim -= magnitude;
        } else if(direction == "forward") {
            horizontal_pos += magnitude;
            depth = depth + (aim * magnitude);
        } else {
            std::cout << "[ERROR]: No direction specified." << std::endl;
        }
    }

    return (horizontal_pos * depth);
}

int main() {

    open_file();

    int final_count{move_count_p2()};

    std::cout << std::endl << "Final count: " << final_count << std::endl;

    close_file();

    return 0;
}