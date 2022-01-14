#include <iostream>
#include <fstream>
#include <string>

void open_file();
void close_file();
int get_next_line();
int detect_increase_p1();
int detect_increase_p2();
int main();

//Stores the file data
std::ifstream file{};
//Stores the data in the line
std::string line{};

void open_file() {

    if(file.is_open()) {
        file.close();
    }

    file.open("depth_log.txt");

    if( !(file.is_open()) ) {
        std::cout << "[ERROR]: Could not open file." << std::endl;
    }
}

void close_file() {
    file.close();
}

int get_next_line() {
    if (getline(file, line)) {
        int line_int{std::stoi(line)};
        return line_int;
    } else {
        return -1;
    }
}

int detect_increase_p1() {

    //First time:
        //Store first entry in a temp var
        //Get second entry
        //Compare second to first

    //temp = 199
    //next = 200 

    //if temp > next

    //temp = 200 (temp)
    //next = 210 (next_line)

    //if

    //temp = 210 (temp)
    //next = 200 (next_line)

    int temp{get_next_line()};
    int next{get_next_line()};
    int increase_count{0};

    while(next != -1) {

        std::cout << temp << " " << next << std::endl;

        if(next > temp) {
            ++increase_count;
        }

        temp = next;
        next = get_next_line();
    }
    return increase_count;
}

int detect_increase_p2() {

    //a = 199 (next)
    //b = 200 (next)
    //c = 208 (next)
    //sum1 = 607

    //a = 200 (b)
    //b = 208 (c)
    //c = 210 (next)
    //sum2 = 618

    //if sum2 > sum 1

    //a = 200 (b)
    //b = 208 (c)
    //c = 210 (next)
    //sum1 = 618

    //a = 208 
    //b = 210
    //c = 200
    //sum2 = 618

    //if sum2 > sum 1

    int a{get_next_line()};
    int b{get_next_line()};
    int c{get_next_line()};
    int increase_count{0};
    int sum1{a + b + c};

    while(c != -1) {

        std::cout << a << " " << b << " " << c << " " << sum1 << std::endl;

        a = b;
        b = c;
        c = get_next_line();
        if(c != -1) {
            int sum2{a + b + c};

            std::cout << a << " " << b << " " << c << " " << sum2 << "\n\n";

            if(sum2 > sum1) {
                ++increase_count;
            }

            sum1 = sum2;
        }
    }
    return increase_count;
}

int main() {

    open_file();

    int num_of_inc{detect_increase_p2()};

    std::cout << std::endl << "Number of increases: " << num_of_inc << std::endl;

    close_file();
}