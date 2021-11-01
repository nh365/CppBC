#include <iostream>



int main(){
 //   std::string decode_string;
  //  std::string cipher = "OLSSV";
      std::string cipher2 = "VKRIMHZKTIAR";
//      std::string cipher2 = "OLSSV";

//    unsigned int key = 7;
    unsigned int key2 = 19;


    std::cout << "Cipher:" << std::endl;
    for(char c2: cipher2){
        std::cout << c2;
    }
    std::cout << std::endl;
    std::cout << "-----------" << std::endl;
//    std::cout << "Key:" ,key2 << std::endl;

    for(char c3: cipher2){
//        std::cout << c2 << std::endl;
        char a2 = c3 - key2;
//       std::cout << a2 << std::endl;

        if(a2 >= 'A') {
            std::cout << a2;
        } else{
            a2 = a2 + ('Z'-'A' + 1);
            std::cout << a2;
        }
    }
   std::cout << std::endl;
   std::cout << static_cast<int>('Z'-'A') << std::endl;
   std::cout << static_cast<int>("Z"-"A") << std::endl;
}

//            int y = static_cast<int>('Z'-'A');
//            std::cout << static_cast<int>('Z'-'A') << std::endl;
//            std::cout << y << std::endl;
/*    
//    int j = 0;
//    char A > "A"; // Valid statement

/*    std::cout << "Enter the string:" << std::endl;
    std::cin >> decode;
*/

/*    std::cout << "Enter the key:" << std::endl;
    std::cin >> key;
    std::cout << "Cipher:" << std::endl;
    for(char c: cipher){
        std::cout << c;
    }
    std::cout << std::endl;
    std::cout << "-----------" << std::endl;

    for(char c: cipher){
        char a = c - key;
        if(a < 'A') {
            std::cout << a+25;
        } else{
            std::cout << a;

        }
    }
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "-----------" << std::endl;
*/
 //   std::cout << "Enter the second key:" << std::endl;
 //   std::cin >> key2;
 /*   std::cout << "Cipher:" << std::endl;
    for(char c2: cipher2){
        std::cout << c2;
    }
    std::cout << std::endl;
    std::cout << "-----------" << std::endl;
//    std::cout << "Key:" ,key2 << std::endl;

    for(char c2: cipher2){
        char a2 = c2 - key2;
        if(a2 >= 'A') {
            std::cout << a2;

//             std::cout << a2+25 << std::endl;
        } else{
//            char x = a2 + 25;
            char x = a2 + ('A'-'Z');
            std::cout << x;

        }
    }
   std::cout << std::endl;
}
// if (a>='A')
// char aa = 'Z - ('A' - a - 1);

*/





