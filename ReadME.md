# River Problem - Concurrent Simulation

## Overview
This project is a simulation of a classic river crossing problem implemented in C++ using multi-threading and semaphores. In this simulation, two groups – hackers and Microsoft employees – attempt to board a boat under strict synchronization constraints, ensuring safe and concurrent operations.

## Features
- Multi-threading using pthreads
- Synchronization via semaphores (e.g., disla, kalkis, siradaki_hacker, siradaki_microsoft)
- Randomized delays using C++ random library to simulate real-world variability
- Tracking of boat boarding events and total boats sailed
- Optional ticket semaphore to limit the number of boats

## Project Structure
- **main.cpp:** Contains the simulation logic, thread creation, and semaphore usage
- **CMakeLists.txt:** CMake configuration for building the project
- **river-final-v2:** (Binary or related executable file)
- **cmake-build-debug:** Build output directory
- **.idea:** IDE configuration files
- **ReadME.md:** This file

## Build Instructions
To build the project, ensure you have a C++ compiler with C++14 support and CMake installed. Then run the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

## Run Instructions
After building, run the executable (e.g., ./RiverProblem from the build directory). Adjust commands based on your environment if necessary.

## Implementation Details
- The boat capacity is defined as 4 (using the macro N).
- Threads are created for both hacker and Microsoft employee simulations.
- Semaphores are used to enforce synchrony during boarding and departure.
- Random delays simulate the unpredictability in thread scheduling and operations.

## Version
Stable version 21.05.2023

## Future Improvements
- Enhanced logging and error handling
- More flexible simulation parameters
- Additional statistical reporting and user configuration options

## Acknowledgements
Developed by Emir. Special thanks to all contributors who provided insights on solving thread-related challenges.

