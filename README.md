# PopHuaji
## A PopStar-like game developed with Cocos2d-x v4  
### Most of the source code were from [ZeroYang's PopStar Repo](https://github.com/ZeroYang/PopStar)  
### What are the changes:  
* to tramsform the project from using Cocos2d-x v2 to v4;  
* to replace the stars with 'Huaji' memes;  
* to add a BGM;  
### Build for Windows
#### Make sure VS 2019 with *MSVC* and *CMake* is installed.
* Clone this repo: `git clone https://github.com/HQU-gxy/PopHuaji`  
(The following commands are executed in *Developer Command Prompt for VS* unless a discrete CMake is installed.)  
* Create build direction: `mkdir win32-build`
* Generate project configuration files: `cmake .. -A win32`
* Open the solution file *win32-build\poop.sln*
* Set *poop* as startup project (if not)
* Build Solution(`cmake --build .` works as well)
