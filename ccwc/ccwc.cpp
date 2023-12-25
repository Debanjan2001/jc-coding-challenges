#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "[Error] Please provide a valid operation and/or a valid filename" << std::endl;
    }
    std::string option = std::string(argv[1]);
    std::string filename = std::string(argv[2]);

    // std::cout<<"Chosen option is "<<option<<std::endl;
    auto counter = [&](std::string &filename, std::string &option)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "ccwc: " << filename << ": No such file or directory" << std::endl;
            exit(0);
        }
        long count = 0;
        if (option == "-c")
        {
            file.seekg(0, std::ios::end);
            count = file.tellg();
        }
        else if (option == "-l")
        {
            std::string line;
            while (std::getline(file, line))
            {
                ++count;
            }
        }
        else if (option == "-m")
        {
            // Read the file content into a string
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            // Convert to wide characters
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring wideContent = converter.from_bytes(content);
            count = wideContent.length();
        }
        else if (option == "-w")
        {
            std::string word;
            while (file >> word)
            {
                ++count;
            }
        }
        else
        {
            std::cerr << "ccwc: Invalid Operation Chosen" << std::endl;
            file.close();
            exit(0);
        }
        file.close();
        return count;
    };

    long count = counter(filename, option);
    std::cout << count << " " << filename << std::endl;
    return 0;
}