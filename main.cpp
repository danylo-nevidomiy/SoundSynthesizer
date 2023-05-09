#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <bitset>
#include <algorithm>
#include <string.h>

#include "wavsynthesizer.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc == 3){//check input arguments
        std::string infile = argv[1], outfile = argv[2];
        WAVSynthesizer s;
        s.process(infile, outfile);
        std::cout << "Synthesis completed!" << std::endl;
    }else{//output of the help section
            std::cout << "SoundSynthesizer: usage [input file name] [output file name]" << std::endl;
            std::cout << "Input file format:" << std::endl;
            std::cout << "\tFirst line: [sample rate]" << std::endl;
            std::cout << "\tNext lines: [frequency: Hz] [durtion: Sec]" << std::endl;
            std::cout << "Output file format:" << std::endl;
            std::cout << "\t WAV audio file" << std::endl;
    }

    return 0;
}


