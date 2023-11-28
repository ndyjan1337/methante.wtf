
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <WinUser.h>

const std::string keyy = "xv%Oa7i2^kGuH#jBqR1KtLwE3yFs0P$DcWnUzg6IZ@JpvYhSoQmVX8Nfr4lTeMdC9bA5!r&J^L+pM6l3!@1Q2#yW8*hFtCp_0iU5<r@o>Zq2[)O7{9qKv}B-Sg^=DyQx.P4fN5g|d3Tt=J?6X/+Z>";

std::string getCPUInfo() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    std::string cpuInfo;
    cpuInfo += std::to_string(sysInfo.dwNumberOfProcessors);
    return cpuInfo;
}

std::string FingerPrintComputer() {
    std::string screen_resolution = std::to_string(GetSystemMetrics(SM_CXSCREEN)) + std::to_string(GetSystemMetrics(SM_CYSCREEN));
    std::string fingerprint = screen_resolution + getCPUInfo();
    return fingerprint;
}


std::string xorEncrypt(const std::string& input) {
    std::string output;
    size_t keyLength = keyy.length();

    for (size_t i = 0; i < input.length(); i++) {
        output += input[i] ^ keyy[i % keyLength];
    }

    return output;
}

