#include <iostream>
#include "obfuscator.hpp"
#include "meta_random.hpp"

using namespace std;
using namespace snowapril;

int main(void) {

    cout << OBFUSCATE("snowapril") << endl;
    cout << OBFUSCATE("sinjihng") << endl;
    cout << OBFUSCATE("sinbaram") << endl;
    cout << OBFUSCATE("pusan") << endl;
    cout << OBFUSCATE("national") << endl;
    cout << OBFUSCATE("university") << endl;

    return 0;
}