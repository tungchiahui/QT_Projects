#include <iostream>
#include "QT6TEST/inc/qt6_test.hpp"

using std::cout;

int main(int argc,char **argv) 
{
    qt6_test();
    cout << "666!" << std::endl;
    
    std::cout << "Press Enter to continue...";
    std::cin.get(); // 等待用户按下回车键
    return 0;
}