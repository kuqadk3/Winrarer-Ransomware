# WinrarRansomware

- Just for fun lulz
- Hope no one will use it for illegal stuff
- POC code


#What is this? :
- Ransomware
- Create rar archive with some listed extension and password with 32 bits long
- Delete all archived file after archive
- Reboot system
- Move all archived file to desktop
- Create list of archived file
- Added drop to temp folder
- Added anti vmware + anti virtualbox

#TODO : 
- Clean this trash code
- Basicly,i will add some technique like Kovster's method (use ASCII character to prevent user from delete registry key), hmm...
- It will work with 7z
- It will work with Winzip

#Server :
- Added Server to receive key

![alt tag](https://github.com/kuqadk3/Winrarer-Ransomware/blob/master/img/server.gif)

#Critical Process :

-Prevent user from ending process by taskmanager

-It will make process (run as administrator privilliges) become system process (examples : winlogon.exe) and cause bsod if user try end process by task manager

-System process : 

![alt tag](https://github.com/kuqadk3/WinrarRansomware/blob/master/img/systemprocess.PNG)

-BSOD (if user try to end process) :

![alt tag](https://github.com/kuqadk3/WinrarRansomware/blob/master/img/bosd.PNG)

#Disclaimer :

- This only for educational purpose

#Feeling : 

![alt tag](https://github.com/kuqadk3/WinrarRansomware/blob/master/img/bloody_work.gif)

