#include <iostream>
#include <curl/curl.h>  
  
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {  
    ((std::string*)userp)->append((char*)contents, size * nmemb);  
    return size * nmemb;  
}  
  
std::string getAccessToken(const std::string& apiKey, const std::string& secretKey) {  
    CURL *curl;  
    CURLcode res;  
    std::string readBuffer;  
  
    curl_global_init(CURL_GLOBAL_DEFAULT);  
  
    curl = curl_easy_init();  
    if(curl) {  
        struct curl_slist *headers = NULL;  
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");  
  
        std::string url = "https://aip.baidubce.com/oauth/2.0/token";  
        url += "?grant_type=client_credentials&client_id=" + apiKey + "&client_secret=" + secretKey;  
  
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);  
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);  
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);  
  
        res = curl_easy_perform(curl);  
  
        if(res != CURLE_OK) {  
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;  
        }  
  
        curl_slist_free_all(headers);  
        curl_easy_cleanup(curl);  
    }  
  
    curl_global_cleanup();  
  
    return readBuffer;  
}  
  
int main() {  
    const std::string apiKey = "[API Key]"; // 替换为你的API Key  
    const std::string secretKey = "[Secret Key]"; // 替换为你的Secret Key  
  
    std::string accessToken = getAccessToken(apiKey, secretKey);  
    std::cout << "Access Token: " << accessToken << std::endl;  
  
    return 0;  
}