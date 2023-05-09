#ifndef WAVWRITER_H
#define WAVWRITER_H

#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>

class WAVSynthesizer
{
    //constants for wav file header
    constexpr static uint32_t deafult_samplerate = 44100;
    constexpr static uint16_t deafult_audioformat = 1;//PCM format
    constexpr static uint32_t deafult_numchannels = 1;//mono sound
    constexpr static uint32_t deafult_bitspersample = 16;
    constexpr static uint32_t deafult_duration = 0;// 0 sec

    constexpr static uint32_t deafult_sunchunk1size = 16;

    constexpr static char riff[4] = {'R', 'I', 'F', 'F'};
    uint32_t chunksize; //variables calculated taking into account data parameters
    constexpr static char format[4] = {'W', 'A', 'V', 'E'};
    constexpr static char subchunk1ID[4] = {'f', 'm', 't', ' '};
    uint32_t subchunk1size = deafult_sunchunk1size;
    uint16_t audioformat;
    uint16_t numchannels;
    uint32_t samplerate;
    uint32_t byterate;
    uint16_t blockalign;
    uint16_t bitspersample;
    constexpr static char subchunk2ID[4] = {'d', 'a', 't', 'a'};
    uint32_t subchunk2size;
    uint32_t duration = deafult_duration;
public:
    WAVSynthesizer(const uint32_t samplerate = deafult_samplerate, const uint16_t audioformat = deafult_audioformat,
                   const uint16_t numchannels = deafult_numchannels, const uint16_t bitspersample = deafult_bitspersample);
    void process(const std::string &fromfile, const std::string &tofile);
private:

    void writeHeader(std::ofstream &output);

    //functions to write variables of different types to a file
    template<typename T>
    void writeToFile(std::ofstream &ofs, const T &value)
    {
        ofs.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    void writeToFile(std::ofstream &ofs, const char &value)
    {
        ofs.put(value);
    }

    template<const int len>
    void writeToFile(std::ofstream &ofs, char(&value)[len])
    {
        ofs.write(value, len);
    }
};

#endif // WAVWRITER_H
