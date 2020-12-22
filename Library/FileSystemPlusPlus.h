/*# MIT License
# Forked from https://github.com/FerhatGec/fsplusplus
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#*/

#ifndef FILE_SYSTEM_PLUS_PLUS_H
#define FILE_SYSTEM_PLUS_PLUS_H

#include <cstring>
#include <iostream>
#include <pwd.h>
#include <dirent.h>
#include <fstream>
#include <sys/stat.h>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace fsplusplus {
	static std::string EraseAllSubString(std::string & mainString, const std::string & erase) {
   	 size_t pos = std::string::npos;
   	 while((pos = mainString.find(erase)) != std::string::npos) {
   	     	mainString.erase(pos, erase.length());
   	 }
   		return mainString;
    	}

	static std::string GetCurrentWorkingDir(void) {
  		char buff[FILENAME_MAX];
  		GetCurrentDir( buff, FILENAME_MAX );
  		std::string current_working_dir(buff);
  		return current_working_dir;
	}

	static bool IsExistFile(std::string path) {
    		struct stat buffer;
    		return (stat(path.c_str(), &buffer) == 0);
	}

	static std::string CDFunction(std::string path) {
		return GetCurrentWorkingDir() + path;
	}
	
	static void ReadFile(std::string file) {
        std::string line;
        std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    		
        if(readfile.is_open()) {
        	while (std::getline(readfile, line)) std::cout << line << "\n";
        	
        	readfile.close();
    	} else 
            std::cout << "Unable to open file\n";
    	
    }
    	
    static std::string ReadFileWithReturn(std::string file) {
		std::string line, data;
		
		if(file[0] != '/') {
			file = fsplusplus::GetCurrentWorkingDir() + "/" + file;
		}
		
        std::ifstream readfile(file.c_str());
    	
    	if(readfile.is_open()) {
        	while (std::getline(readfile, line)) data.append(line + "\n");
        	
            readfile.close();
        } else 
        		std::cout << "Unable to open file\n";
		
        return data;
    }
    
    static std::string ReadDirWithReturn(std::string dir) {
	    std::string line, add;
    	std::ifstream readfile(dir.c_str());
    		
		if(readfile.is_open()) {
			while(std::getline(readfile, line)) add.append(line + "\n");

			readfile.close();
		} 

       	return add;
    }
    	
    	
	// Get Between String    
	static void GetBtwString(std::string oStr, std::string sStr1, std::string sStr2, std::string &rStr) {  
    		int start = oStr.find(sStr1);   
    	if (start >= 0) {       
      		std::string tstr = oStr.substr(start + sStr1.length());        
      		int stop = tstr.find(sStr2);      
      		if (stop >1)          
        		rStr = oStr.substr(start + sStr1.length(), stop);
      		else
        		rStr ="error";  
    		}
    		else
       		rStr = "error"; 
	}    
    
    
    static std::string FindStringWithReturn(std::string file, std::string str) {
		std::string line;
		std::ifstream readfile(file.c_str());
    	
		if(readfile.is_open()) {
        	while (std::getline(readfile, line))
				if(strstr(line.c_str(), str.c_str())) return line + "\n";
        	
        		readfile.close();
		}

    		return "null";
    }
    	
    static void ReadFilePath(std::string path) {
		std::string line;
    	std::ifstream readfile(path.c_str());
    	
    	if(readfile.is_open()) {
        	while (std::getline(readfile, line)) {
        		if(line.find("PRETTY_NAME=\"") == 0) {
					GetBtwString(line, "\"", "\"", line);
					
					std::cout << line + "\n";
        		}
        	}
        	readfile.close();
    	} else {
       		std::cout << "Unable to open file\n";
   		}
	}
	
	static std::string ReadOSName() {
		#ifdef __FreeBSD__
			return "FreeBSD";
		#else
    		std::string line;
    		std::ifstream readfile("/etc/os-release");

    		if(readfile.is_open()) {
	        	while (std::getline(readfile, line)) {
	        		if(line.find("PRETTY_NAME=\"") == 0) {
						GetBtwString(line, "\"", "\"", line);
						return line;
	        		}
	        	}

	        	readfile.close();
    		} else {
        		std::cout << "Unable to open file\n";
    		}
		
		return "null";
		#endif	
	}
	
	static void ReadCPU() {
    	std::string line;
		#ifdef __FreeBSD__
    		std::ifstream readfile("/var/run/dmesg.boot");
		#else
		
		std::ifstream readfile("/proc/cpuinfo");	
		#endif    		
		if(readfile.is_open()) {
        	while (std::getline(readfile, line)) {
			#ifdef __FreeBSD__
			if(line.find("CPU: ") == 0) {
				line = EraseAllSubString(line, "CPU: ");
				if(line.length() >= 20) {
					line = line.substr(0, 40);
				}
				
				std::cout << line + "\n";
				return;
        	}
			#else
        		if(line.find("model name	: ") == 0) {
					line = EraseAllSubString(line, "model name	: ");
					std::cout << line + "\n";
					return;
        		}
			#endif
        	}
        	readfile.close();
    	} else {
        	std::cout << "Unable to open file\n";
    	}
	}
	
	static void CreateFile(std::string name, std::string input) {
		std::string path;
    		path.append(GetCurrentWorkingDir());
    		path.append("/");
    		path.append(name);
    		std::ofstream file(path, std::ios::app);
    		file << input;
    		file.close();
	}
	
	static void CreateFileWithoutAppend(std::string name) {
		std::string path;
    		path.append(GetCurrentWorkingDir());
    		path.append("/");
    		path.append(name);
    		std::ofstream file(path);
    		file.close();
	}
}

#endif // FILE_SYSTEM_PLUS_PLUS_H
