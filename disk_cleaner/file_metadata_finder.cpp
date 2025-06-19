#include<iostream>
#include<filesystem>
#include<chrono>
#include<iomanip>
#include<string>
#include<map>
#include <sstream>
#include<algorithm>

using namespace std;

map<string, string> find_file_metadata(string path)
{
	/*replace(path.begin(), path.end(), '\\', '/');

	if (path.rfind("C:", 0) == 0)
        	path.replace(0, 2, "/mnt/c");
	else if (path.rfind("D:", 0) == 0)
                path.replace(0, 2, "/mnt/d");
	if (path.rfind("E:", 0) == 0)
                path.replace(0, 2, "/mnt/e");
    	*/
	filesystem::path filePath(path);

       // cout << "Checking: " << filePath << "\n";

	//cout << "path: " << path << endl;

	if(!filesystem::exists(filePath))
	{
		cerr << "File {" << path << "} not found.\n";
		return {};
	}
	map<string, string> ans;
	ans["path"] = path;
	ans["parent_directory"] = filePath.parent_path().string();
	uintmax_t size = filesystem::file_size(filePath);
	ans["file_size"] = to_string(size);
	
	auto ftime = filesystem::last_write_time(filePath);
	auto stime = chrono::time_point_cast<chrono::system_clock::duration>(
        	ftime - filesystem::file_time_type::clock::now() + chrono::system_clock::now()
    	);
    	time_t cftime = chrono::system_clock::to_time_t(stime);

	ostringstream oss;
	oss << put_time(localtime(&cftime), "%F %T");
	string lastModifiedStr = oss.str();

	ans["last_modified"] = lastModifiedStr;

	return ans;
}

void check_if_file_large(string path)
{
	auto x = find_file_metadata(path);
	if(stoi(x["file_size"]) >= 500000000)
	{
		for(const auto &pair: x){
			cout << "\n" << pair.first << " : " << pair.second << endl;
		}
	}
}
