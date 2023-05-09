#include "wavsynthesizer.h"

//classs constructor
WAVSynthesizer::WAVSynthesizer(const uint32_t samplerate, const uint16_t audioformat, const uint16_t numchannels, const uint16_t bitspersample)
    : samplerate(samplerate), audioformat(audioformat), numchannels(numchannels), bitspersample(bitspersample)
{

}

//sound synthesizer
void WAVSynthesizer::process(const std::string &fromfile, const std::string &tofile)
{
    std::ifstream input;
    input.open(fromfile);
    if(input.good()){
        std::ofstream output;
        output.open(tofile, std::ios::binary);
        writeHeader(output);
        input >> samplerate;
        srand(time(NULL));
        double frequency, duration;
        while(input >> frequency >> duration){
            this->duration+=duration;
            int noise_length = samplerate/frequency;
            int samples_length = samplerate*duration;
            double samples[samples_length];
            for(int i=0;i<noise_length;i++){//white noise generator
                samples[i] = (std::rand()%2000)/1000-1;
            }
            for(int i=noise_length+1;i<samples_length;i++){//sound sythesis
                samples[i] = (samples[i - noise_length] + samples[i - noise_length - 1]) / 2;
            }
            int16_t result;
            for(int i=0;i<samples_length;i++){//sound format and write to file
                result = samples[i]*INT16_MAX;
                writeToFile(output, result);
            }
        }
        output.seekp(0);
        writeHeader(output);
        output.close();
    }
    input.close();
}
//wzv file header writer
void WAVSynthesizer::writeHeader(std::ofstream &output)
{
    subchunk2size = (samplerate*duration*numchannels*bitspersample)/8;
    chunksize = subchunk2size+36;
    byterate = (samplerate*bitspersample*numchannels)/8;
    blockalign = (bitspersample*numchannels)/8;

    writeToFile(output, riff);
    writeToFile(output, chunksize);
    writeToFile(output, format);
    writeToFile(output, subchunk1ID);
    writeToFile(output, subchunk1size);
    writeToFile(output, audioformat);
    writeToFile(output, numchannels);
    writeToFile(output, samplerate);
    writeToFile(output, byterate);
    writeToFile(output, blockalign);
    writeToFile(output, bitspersample);
    writeToFile(output, subchunk2ID);
    writeToFile(output, subchunk2size);
}
