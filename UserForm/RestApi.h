#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "vendor/json.hpp"
#include "User.h"
#include <curl/curl.h>
namespace rest {
    using json = nlohmann::json;
    class RestApi
    {
    public:
        RestApi();
        ~RestApi();
        const std::string getToken();
        const std::vector<User> getUsers(const int page, const int count);
        bool postNewUser(const  User newUser);
        const std::vector<std::string> getPositions();
        int getPage();


    private:
        void ShowError(const std::string message);
        static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userptr);

        std::string sendRequest(const  std::string request);
        std::string sendPostRequest(const  User newUser);

        CURL* curl;
        int total_pages = 0;
        const  std::string url = "https://frontend-test-assignment-api.abz.agency/api/v1/";


    };

}
