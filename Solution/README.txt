Anna Kurach

Task description:
Client/Server application to get Mouse activity on remote HOST.
- client has to store mouse coordinate each 500ms
- client has to store mouse clicks
- client has to send mouse activities to the server
- server has to save activities to the file in real time

Project dependencies:
For Windows: cl.exe, MSBuild.exe, CMake.
For Linux: g++, CMake, Make, X11.

Instruction for building server:
1. Clone repo to the project folder.
2. Open the CrossPlatformServer folder.
3. Change to build directory.
4. Call the cmake utility supplying the path to the CMakeLists.txt, run:
	cmake ..
5. For Windows, run:
	msbuild Server.sln
   For Linux, run:
	make

Instruction for building client:
1. Clone repo to your project folder.
2. Open the CrossPlatformClient folder. 
3. Change to build directory.
4. Call the cmake utility supplying the path to the CMakeLists.txt, run:
	cmake ..
5. For Windows, run:
	msbuild Client.sln
   for Linux, run:
	make

To run application:
1. For Windows, run:
	server.exe
   for Linux, run:
	./server
2. For Windows, run:
	client.exe
   for Linux, run:
	./client

Default server IP: 127.0.0.1, port: 12345
Default client IP: 127.0.0.1, port: 12345

Server log file will look like:
100x920 RMK (Right Mouse click)
200x50
47x650 LMK (Left Mouse click)

The screenshots folder contains the examples of running applications.