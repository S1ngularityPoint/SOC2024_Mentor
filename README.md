# One-Program-To-Outspeed-Them-All
Welcome to our SOC "One Program To Outspeed Them All". Join us as we dwelve deep into the concepts of threads, SIMD (Single Instruction/ Multiple Data), the openCL library and ultimately a fun project to end at a high note :)
Here is the tentative schedule:

## Week 0 : Setting up
- This week will be spent in setting up your coding environment. We recommend WSL as you can code in C/C++ without any hassle once you set up WSL.
- Install wsl : https://learn.microsoft.com/en-us/windows/wsl/install
- Use ubuntu preferrably although pretty much any distribution should be okay (so if you do not have ubuntu don't panic and change your distribution lol you will probably be fine)
- In case you want to try using the manual install (as the default one may not work for everyone), follow this : https://learn.microsoft.com/en-us/windows/wsl/install-manual
- Integrate WSL with visual studio code : https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-vscode
- Install git : https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-git
- Run the following command to install g++, gdb (optional but recommended), make : sudo apt update && sudo apt install g++ gdb make ninja-build rsync zip
- Here are some practice questions. 
## Week 1 : This is the Way
- Familiarise yourself with the threading library threads of C++.
- Understand the concepts of mutual exclusions, race conditions and why locking is necessary (yes it is totally not from a core course of a certain department).
- Use locks and conditional variables in programs yourself and understand why they are necessary.
- Also minimize usage of locks to prioritize speed (not the drug).
## Weeks 2-3 One Instruction to Compute Them all 
- Vectorization as provided by the CPU
- Understand the special registers and the powerful instructions available for our use
- Automatic parallelization and the use of pragma
- Manual parallelization for more power 
## Weeks 4-5 This is where the fun begins
- Introduction to openCL.
## Week 6
- Applications of openCL.
## Weeks 7-8 We are in the Endgame Now
- Either SAT Solver or ML library 
