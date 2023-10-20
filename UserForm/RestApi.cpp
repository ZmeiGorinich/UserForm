#include "RestApi.h"
namespace rest {
    RestApi::RestApi()
    {
    }
    RestApi::~RestApi()
    {
    }
    const std::string RestApi::getToken()
    {
        std::string response = sendRequest("token");

        if (response.empty())
        {
            return response;
        }
        else
        {
            json data = json::parse(response);

            std::string token = data["token"];

            return token;

        }
    }
    const std::vector<User> RestApi::getUsers(const int page, const int count)
    {
        std::string response = sendRequest("users?page=" + std::to_string(page) + "&count=" + std::to_string(count));

        std::vector<User> result;

        if (response.empty())
        {
            return result;

        }
        else {
            json data = json::parse(response);


            if (data["success"] == "false")
            {
                std::string message = data["message"];

                ShowError(message);

                return result;
            }
            else
            {
                total_pages = data["total_pages"];

                for (auto& usr : data["users"])
                {
                    result.push_back(User(usr["name"], usr["email"], usr["position"], usr["phone"], usr["photo"]));
                }
                return result;

            }
        }


        return result;
    }
    bool RestApi::postNewUser(const User newUser)
    {
        std::string response = sendPostRequest(newUser);

        if (response.empty())
        {
            return 0;
        }
        else
        {
            json data = json::parse(response);

            if (data["success"] == true)
            {
                return 1;
            }
            else
            {
                std::string message = data["message"];

                ShowError(message);
                return 0;
            }
        }


        return 0;
    }
    const std::vector<std::string> RestApi::getPositions()
    {
        std::string response = sendRequest("positions");

        std::vector<std::string> positions;

        if (response.empty())
        {
            return positions;
        }
        else
        {
            json data = json::parse(response);

            if (data["success"] == "false")
            {
                std::string message = data["message"];

                ShowError(message);

                return positions;
            }
            else
            {
                for (auto& position : data["positions"]) {
                    positions.push_back(position["name"]);
                }
                return positions;

            }


        }

    }
    int RestApi::getPage()
    {
        return total_pages;
    }
    void RestApi::ShowError(const std::string message)
    {
        System::String^ S_message = gcnew System::String(message.c_str());
        System::Windows::Forms::MessageBox::Show(S_message, "Error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
    }
    size_t RestApi::WriteCallback(void* contents, size_t size, size_t nmemb, void* userptr)
    {
        size_t total_size = size * nmemb;
        std::string* output = static_cast<std::string*>(userptr);
        output->append(static_cast<char*>(contents), total_size);
        return total_size;
    }
    std::string RestApi::sendRequest(const std::string request)
    {
        CURLcode res;
        std::string response_data;

        curl = curl_easy_init();
        if (curl) {
            // Установка URL для GET-запроса
            curl_easy_setopt(curl, CURLOPT_URL, (url + request).c_str());

            // Настройка функции обратного вызова для записи данных
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

            // Выполнение GET-запроса
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                ShowError("Curl Error: " + std::string(curl_easy_strerror(res)));
            }

            // Очистка ресурсов libcurl
            curl_easy_cleanup(curl);
        }
        else
        {
            ShowError("Error initializing libcurl.");
        }
        return response_data;
    }
    std::string RestApi::sendPostRequest(const User newUser)
    {
        std::string token = "Token: " + getToken();
        std::string request = "users";


        // Initialize libcurl
        curl = curl_easy_init();
        // Check if curl was initialized successfully
        if (!curl) {
            ShowError("Error initializing libcurl.");
        }

        curl_easy_setopt(curl, CURLOPT_URL, (url + request).c_str());

        // Set the request headers
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, token.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Create a form
        curl_mime* form = curl_mime_init(curl);

        // Add fields to the form
        curl_mimepart* part = curl_mime_addpart(form);
        curl_mime_name(part, "name");
        curl_mime_data(part, newUser.getName().c_str(), CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(form);
        curl_mime_name(part, "email");
        curl_mime_data(part, newUser.getEmail().c_str(), CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(form);
        curl_mime_name(part, "phone");
        curl_mime_data(part, newUser.getPhoneNumber().c_str(), CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(form);
        curl_mime_name(part, "position_id");
        curl_mime_data(part, newUser.getPosition().c_str(), CURL_ZERO_TERMINATED);

        // Add the photo (file) to the form
        part = curl_mime_addpart(form);
        curl_mime_name(part, "photo");
        curl_mime_filedata(part, newUser.getPictureLink().c_str()); // Replace with the actual path to your photo file


        // Set the form as the request body
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);

        // Set the callback function to receive the response
        std::string response_data;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            ShowError("Curl Error: " + std::string(curl_easy_strerror(res)));
        }

        // Clean up
        curl_slist_free_all(headers);
        curl_mime_free(form);
        curl_easy_cleanup(curl);

        return response_data;
    }
}