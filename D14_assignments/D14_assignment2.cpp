#include <iostream>
#include <bitset>


struct field{

    unsigned left:3;
    unsigned right:3;
    unsigned rear:3;
    unsigned front:3;
    unsigned speed:4;
    field():left(0),right(0),rear(0),front(0),speed(0){}
};

bool FetchData(field &_data, size_t _input[5]){

    // Calculate speed...
    size_t temp_dec = (_input[0]/20);
    // ...convert to binary...
    std::bitset<8> temp_bitset (temp_dec);
    // ...and put into datastructure
    _data.speed = (unsigned)temp_bitset.to_ulong();

    // Calculate front
    temp_dec = (_input[1]/150);
    // ...convert to binary...
    temp_bitset = (temp_dec);
    // ...and put into datastructure
    _data.front = (unsigned)temp_bitset.to_ulong();

    // Calculate rear
    temp_dec = (_input[2]/150);
    // ...convert to binary...
    temp_bitset = (temp_dec);
    // ...and put into datastructure
    _data.rear = (unsigned)temp_bitset.to_ulong();

    // Calculate right
    temp_dec = (_input[3]/150);
    // ...convert to binary...
    temp_bitset = (temp_dec);
    // ...and put into datastructure
    _data.right = (unsigned)temp_bitset.to_ulong();

    // Calculate left
    temp_dec = (_input[4]/150);
    // ...convert to binary...
    temp_bitset = (temp_dec);
    // ...and put into datastructure
    _data.left = (unsigned)temp_bitset.to_ulong();


    return true;
}


bool PositionData(field &_data, uint16_t &_bits){

    _bits = (_data.speed << 12) | (_data.front << 9) | (_data.rear << 6) | (_data.right << 3) | _data.left;    

    return true;
}


int main(){

    field my_data;
    uint16_t my_bits = 0;
    size_t input[5] = {220,750,150,450,450};

    std::cout << "Input data:" << std::endl;
    std::cout << "Speed: " << input[0] << std::endl;
    std::cout << "Front: " << input[1] << std::endl;
    std::cout << "Rear: " << input[2] << std::endl;
    std::cout << "Right: " << input[3] << std::endl;
    std::cout << "Left: " << input[4] << std::endl;
    
    FetchData(my_data, input);

    PositionData(my_data, my_bits);

    std::cout << "Encoded data: " << (std::bitset<16>) my_bits << std::endl;

    return 0;
}

