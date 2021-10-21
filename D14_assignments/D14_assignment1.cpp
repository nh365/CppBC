#include <iostream>
#include <bitset>


struct field{

    unsigned lights:3;
    unsigned doors:4;
    unsigned windows:4;
    unsigned seat_belts:5;
};

int main(){

    field my_data;

    uint16_t input_bitset = 0b1011101001011011;
    uint16_t lights_mask = 0b0000000000000111;
    uint16_t doors_mask = 0b0000000001111000;
    uint16_t windows_mask = 0b0000011110000000;
    uint16_t seat_belts_mask = 0b1111100000000000;
 
    uint8_t front_lights_mask = 0b00000001;
    uint8_t rear_lights_mask = 0b00000010;
    uint8_t break_lights_mask = 0b00000100;

    uint8_t driver_door_mask = 0b00000001;
    uint8_t passenger_door_mask = 0b00000010;
    uint8_t rear_left_door_mask = 0b00000100;
    uint8_t rear_right_door_mask = 0b00001000;

    uint8_t driver_window_mask = 0b00000001;
    uint8_t passenger_window_mask = 0b00000010;
    uint8_t rear_left_window_mask = 0b00000100;
    uint8_t rear_right_window_mask = 0b00001000;

    uint8_t driver_sb_mask = 0b00000001;
    uint8_t passenger_sb_mask = 0b00000010;
    uint8_t rear_left_sb_mask = 0b00000100;
    uint8_t rear_right_sb_mask = 0b00001000;

    size_t lights_shift = 0;
    size_t doors_shift = 3;
    size_t windows_shift = 7;
    size_t seat_belts_shift = 11;             

    // Mask and enter data into field
    my_data.lights = input_bitset & lights_mask;
    my_data.doors = ( input_bitset & doors_mask ) >> doors_shift;
    my_data.windows = ( input_bitset & windows_mask ) >> windows_shift;
    my_data.seat_belts = ( input_bitset & seat_belts_mask ) >> seat_belts_shift;

    // Print data
    (my_data.lights & front_lights_mask) ? std::cout << "Front lights are on." << std::endl : std::cout << "Front lights are off." << std::endl;
    (my_data.lights & rear_lights_mask) ? std::cout << "Rear lights are on." << std::endl : std::cout << "Rear lights are off." << std::endl;
    (my_data.lights & break_lights_mask) ? std::cout << "Break lights are on." << std::endl : std::cout << "Break lights are off." << std::endl;
    (my_data.doors & driver_door_mask) ? std::cout << "Driver door is open." << std::endl : std::cout << "Driver door is closed." << std::endl;
    (my_data.doors & passenger_door_mask) ? std::cout << "Passenger door is open." << std::endl : std::cout << "Passenger door is closed." << std::endl;
    (my_data.doors & rear_left_door_mask) ? std::cout << "Rear left door is open." << std::endl : std::cout << "Rear left door is closed." << std::endl;
    (my_data.doors & rear_right_door_mask) ? std::cout << "Rear right door is open." << std::endl : std::cout << "Rear right door is closed." << std::endl;
    (my_data.windows & driver_window_mask) ? std::cout << "Driver window is open." << std::endl : std::cout << "Driver window is closed." << std::endl;
    (my_data.windows & passenger_window_mask) ? std::cout << "Passenger window is open." << std::endl : std::cout << "Passenger window is closed." << std::endl;
    (my_data.windows & rear_left_window_mask) ? std::cout << "Rear left window is open." << std::endl : std::cout << "Rear left window is closed." << std::endl;
    (my_data.windows & rear_right_window_mask) ? std::cout << "Rear right window is open." << std::endl : std::cout << "Rear right window is closed." << std::endl;
    (my_data.windows & driver_sb_mask) ? std::cout << "Driver seat belt is unbuckled." << std::endl : std::cout << "Driver seat belt is buckled." << std::endl;
    (my_data.windows & passenger_sb_mask) ? std::cout << "Passenger seat belt is unbuckled." << std::endl : std::cout << "Passenger seat belt is buckled." << std::endl;
    (my_data.windows & rear_left_sb_mask) ? std::cout << "Rear left seat belt is unbuckled." << std::endl : std::cout << "Rear left seat belt is buckled." << std::endl;
    (my_data.windows & rear_right_sb_mask) ? std::cout << "Rear right seat belt is unbuckled." << std::endl : std::cout << "Rear right seat belt is buckled." << std::endl;

    std::cout << "Lights: " << (std::bitset<8>) my_data.lights << std::endl;
    std::cout << "Doors: " <<  (std::bitset<8>) my_data.doors << std::endl; 
    std::cout << "Windows: " <<  (std::bitset<8>) my_data.windows << std::endl;
    std::cout << "Seat belts: " <<  (std::bitset<8>) my_data.seat_belts << std::endl;   
    std::cout << "Input bitfield: " <<  (std::bitset<16>) input_bitset << std::endl;   
 
    return 0;
}

