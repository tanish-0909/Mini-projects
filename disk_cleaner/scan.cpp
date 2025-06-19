#include<iostream>
#include<string>
#include<vector>
#include<filesystem>

using namespace std;

void check_if_file_large(string path); 

int main(void)
{
	char drive;
	cout << "Enter which drive (c, d or e): ";
	cin >> drive;

	string root_dir;
	
	try {
		filesystem::recursive_directory_iterator it(root_dir, fs::directory_options::skip_permission_denied);
        	filesystem::recursive_directory_iterator end;
		for (const auto& entry : filesystem::recursive_directory_iterator("/mnt/" + string(1, drive))) {
        		try {
		//		cout << entry.path().string() << "\n";
                		if (filesystem::is_regular_file(entry)) {
                    			//cout << entry.path().string() << "\n";
					string path = entry.path().string();
					check_if_file_large(path);
                		} else {
					cout << ".";
				}
            		} catch (const filesystem::filesystem_error& e) {
				cout << entry << " not accessible\n";
                	// Skip files we can't access
            		}
		//	break;
        	}
    	} catch (const filesystem::filesystem_error& e) {
        	cerr << "Skipping: " << " (" << ec.message() << ")\n";
    	}
}
