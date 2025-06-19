#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void check_if_file_large(string path); // Assume you defined it somewhere

int main(void)
{
    char drive;
    cout << "Enter which drive (c, d or e): ";
    cin >> drive;
    drive = tolower(drive); // Normalize input

    string root_dir = "/mnt/" + string(1, drive);

    try {
        fs::recursive_directory_iterator it(root_dir, fs::directory_options::skip_permission_denied);
        fs::recursive_directory_iterator end;

        for (; it != end; ++it) {
            std::error_code ec;
            if (fs::is_regular_file(*it, ec)) {
                string path = it->path().string();
                check_if_file_large(path);
            } else {
                cout << ".";
            }

            if (ec) {
                cerr << "Skipping: " << it->path() << " (" << ec.message() << ")\n";
            }
        }
    } catch (const fs::filesystem_error& e) {
        cerr << "Fatal error: " << e.what() << "\n";
    }

    return 0;
}

