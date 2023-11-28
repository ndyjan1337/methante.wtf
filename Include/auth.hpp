#include <string>
#include <sstream>
#include <windows.h>
#include <curl/curl.h>
#include "nlohmann/json.hpp"
#include "utils.hpp"
#include <vxlib.h>

using json = nlohmann::json;



size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string executeRequest(const std::string& url, const std::string& postData = "") {
    VL_VIRTUALIZATION_BEGIN;
    std::string response;
    std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl(curl_easy_init(), curl_easy_cleanup);

    if (curl) {
        curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
        if (!postData.empty()) {
            curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDS, postData.c_str());
        }
        curl_easy_setopt(curl.get(), CURLOPT_VERBOSE, 0);
        curl_easy_setopt(curl.get(), CURLOPT_SSL_VERIFYHOST, 1);
        curl_easy_setopt(curl.get(), CURLOPT_SSL_VERIFYPEER, 1);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, writeCallback);

        CURLcode result = curl_easy_perform(curl.get());
        if (result != CURLE_OK) {
            response = "";
        }
    }
    return response;
    VL_VIRTUALIZATION_END;
}

bool authenticate(std::string username, std::string password) {
     VL_VIRTUALIZATION_BEGIN; 

    std::string request = "username=" + username + "&password=" + password + "&hwid=" + FingerPrintComputer();

    std::string response = executeRequest("https://methane.wtf/auth.php?type=login", request);

    std::cout << "Encrypted: " << response << std::endl;
    std::cout << "Decrypted: " << xorEncrypt(response) << std::endl;

    auto json = json::parse(xorEncrypt(response));
    if (json["value"] == 104) {
        std::string id = json["content"];


        return true;
    }
    else {
        return false;
    }
    VL_VIRTUALIZATION_END;
}
