# Server Surfer

This game is made using Qt framework and C++ language. To be able to build the game properly, please make sure that you have Qt framework of version 4.8.2 or above, a working C++ compiler, and have resolved the dependencies that will be listed below.

**Dependencies :**
- libcurl library
  - The documentation for libcurl library can be found [here](https://curl.haxx.se/libcurl/).

- nmap
  - The documentation for libcurl library can be found [here](https://nmap.org/).
  - For Ubuntu  : ```sudo apt install nmap```
  - For Debian  : ```sudo apt-get install nmap```
  - For Arch    : ```sudo pacman -S nmap```
  - For Fedora  : ```sudo dnf install nmap```
  - For OpenSUSE: ```zypper install nmap```
  - ```sudo snap install nmap``` can also be used for those that have snap.
  
**Building Instruction for Qt Creator :**
1. Resolve all depencencies listed above and make sure that you have Qt framework of version 4.8.2 or above and a working C++ compiler in your environment.
2. Using Qt Creator, open the project by selecting server_surfer.pro.
3. Run the application from Qt creator by simply clicking the run button.

**Building Instruction for Command Line :**
1. Navigate to server-surfer directory.
2. Use ```qmake server-surfer.pro``` which will generate a Makefile for you.
3. Use ```make``` to build the application.
4. Use ```server-surfer*``` to run the application.

**Usage :**

Server Surfer is intended to be a game to help players get more familiar with how the internet works and to be more aware of security. The way that the game itself work is very simple:
1. You start at a certain server by entering whatever URL you want in the starting screen.
2. Once the game start, you will have the option to move to different servers. These options are based on links that are found from your current server. For example, if you are currently in news.ycombinator.com and there is a link to reddit.com, you will be able to move to reddit.com.
3. Once you run out of moves, reached a server with no links, or moved to an invalid URL, the game will end and you will get a score proportional to the geographic distance you have travelled from your starting server to your last server.

**Learning from this Game :**

To get the most out of this game, please be sure to regularly read the information box of servers that you have travelled to and to use the extra features that allow you to scan servers. By doing this, you will be able to familiarize yourself with the structure of internet (how much servers are on cloud, how much servers use load balancers), the structure of webpages (how webpages have subdomains and subdirectories and what these imply), and the security of various webpages (broken access control for sensitive directories, open ports that can be attacked).
