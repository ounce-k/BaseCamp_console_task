## Anna Kurach

##Task description:
Client/Server application to get Mouse activity on remote HOST.<br/>
- client has to store mouse coordinate each 500ms<br/>
- client has to store mouse clicks<br/>
- client has to send mouse activities to the server<br/>
- server has to save activities to the file in real time<br/>

Server log file will look like:<br/>
100x920 RMK (Right Mouse click)<br/>
200x50<br/>
47x650 LMK (Left Mouse click)<br/>

##Instruction for building:
1. Clone repo to the project folder.
2. Open the Server folder.
3. Run in Visual Studio.
4. Open Developer Command Prompt<br/>
5. Run command<br/>
nmake -f Makefile<br/>
6. Run the Server.exe<br/>
7. Open the Client folder.<br/>
8. Run in Visual Studio.<br/>
9. Open Developer Command Prompt<br/>
10. Run command<br/>
nmake -f Makefile<br/>
11. Run the Client.exe<br/>
