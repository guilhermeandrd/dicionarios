#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

    cout << "numero de parametros = " << argc << endl;
    
    for(int i = 0; i < argc; ++i) {
        cout << "argumento [" << i << "] = " << argv[i] << endl;
    } 

    //primeiro parametro

    //segundo - tipo da estrutra a ser utilizada

    //terceiro - string a ser lida

    return 0;
}
