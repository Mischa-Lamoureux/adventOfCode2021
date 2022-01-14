#include <iostream>
#include <bitset>
#include <fstream>

void open_file();
void close_file();
void jump_to_top();
int get_next_line();
int power_consumption();
int life_support();
int main();

//Stores the file data
std::ifstream file{};
//Stores the data in the line
std::string line{};

void open_file() {

    if(file.is_open()) {
        file.close();
    }

    file.open("binary_log.txt");

    if( !(file.is_open()) ) {
        std::cout << "[ERROR]: Could not open file." << std::endl;
    }
}

void close_file() {
    file.close();
}

void jump_to_top() {
    file.clear();
    file.seekg(0);
}

int get_next_line() {
    if (getline(file, line)) {
        //Convert binary string to int
        int temp{stoi(line, 0, 2)};
        return temp;
    } else {
        jump_to_top();
        return -1;
    }
}

int power_consumption() {

    //power_consumption = gamma_rate * epsilon_rate

    //Use not operator to invert gamma and epsilon (since they're are opposite of each other)

    //Make a dynamic mask (use bitshift operators?)

    //0b100000000000
    int mask{0b100000000000};
    int gamma_rate{0b0};
    int epsilon_rate{0b0};

    //Calculating gamma rate
    for(int i{0}; i < 12; ++i) {

        int line_value{get_next_line()};
        int common_ones{0};
        int common_zeros{0};

        while(line_value != -1) {
            if(line_value & mask) {
                ++common_ones;
            } else {
                ++common_zeros;
            }
            line_value = get_next_line();
        }
        if(common_ones > common_zeros) {
            gamma_rate = gamma_rate | mask;
        } else if(common_zeros > common_ones) {
            epsilon_rate = epsilon_rate | mask;
        }
        mask >>= 1;
    }

    std::cout << "gamma_rate: " << gamma_rate << std::endl;
    std::cout << "epsilon_rate: " << epsilon_rate << std::endl;

    return (gamma_rate * epsilon_rate);
}

int life_support() {

    //Oxygen generator rating:
        //Find the most common value in the current bit
        //position and delete all other values

    int mask{0b10000};
    int storage[8]{};
    int line_value{get_next_line()};
    int common_ones{0};
    int common_zeros{0};
    std::size_t index{0};

    while(line_value != -1) {
        if(line_value & mask) {
            ++common_ones;
        } else {
            ++common_zeros;
        }
        line_value = get_next_line();
    }
    //If there are more common ones OR as common
    if(common_ones >= common_zeros) {
        //Keep all entries with only 1s

        jump_to_top();
        line_value = get_next_line();

        while(line_value != -1) {

            //If matching, store that entry in an array
            if(line_value & mask) {
                storage[index] = line_value;
                ++index;
            }
            line_value = get_next_line();
        }
    } else if(common_zeros > common_ones) {
        //Keep all entries with only 0s
        
        jump_to_top();
        line_value = get_next_line();

        while(line_value != -1) {
            
            if( !(line_value & mask) ) {
                storage[index] = line_value;
                ++index;
            }
            line_value = get_next_line();
        }
    }

    return 0;
}

int main() {

    open_file();

    int power{power_consumption()};

    std::cout << std::endl << "Power consumption: " << power << std::endl;

    // int i{0};

    // int temp{get_next_line()};

    // while(temp != -1) {
    //     std::cout << "#: " << std::bitset<16>(temp) << std::endl;
    //     temp = get_next_line();
    // }

    // while(true) {
        
    //     if(i == 15) {
    //         break;
    //     }

    //     std::cout << get_next_line() << std::endl;

    //     ++i;
    // }



    // int mask{0b100000000000};

    // //1, 2, 4, 8

    // for(int i{0}; i < 12; ++i) {

    //     std::cout << mask << std::endl;
    //     mask >>= 1;
    // }

    close_file();

    return 0;
}