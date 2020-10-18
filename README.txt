Anna Kurach

Task description:
Client/Server application to get Mouse activity on remote HOST.
- client has to store mouse coordinate each 500ms
- client has to store mouse clicks
- client has to send mouse activities to the server
- server has to save activities to the file in real time

Server log file will look like:
100x920 RMK (Right Mouse click)
200x50
47x650 LMK (Left Mouse click)

##Instruction for building:
1. Clone repo to the project folder.
2. Open the Server folder.
3. Run in Visual Studio.
4. Open Developer Command Prompt
5. Run command
nmake -f Makefile
6. Run the Server.exe.
7. Open the Client folder.
8. Run in Visual Studio.
9. Open Developer Command Prompt.
10. Run command
nmake -f Makefile
11. Run the Client.exe
