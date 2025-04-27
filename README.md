# OpenAPT
OpenAPT (Open Accelerated Particle physics Transport code) is an open-source simulation framework for the passage of particles through matter. The code was inspired by the precision of GEANT4 and ease-of-use of OpenMC. The framework is written predominantly in C++/CUDA with a helpful Python API.

## Installation Instructions
Assuming you have CMake version 3.10 or above the installation is fairly simple (tested on MacOS Seqouia and Windows 10 22H2 19045.5737). After cloning and changing into the repository directory,
```mkdir build && cd build```
```cmake ..```

and for Windows users you can use
```cmake --build . --config Release```

and the executable will be located at ```~\Release\OpenAPT.exe```
for MacOS users you can just use,
```make -j [nProcs]```

## Usage
TODO

## Documentation
TODO
