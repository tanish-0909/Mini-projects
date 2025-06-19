# Mini projects
This repo is for my c++ based mini projects

1. Snake game: a simple snake game using linux terminal.
    Used the ncurses library for a better UI design specially customized to the linux terminal.
    To run the game: 
    1. sudo apt-get update 
    2. sudo apt-get upgrade
    3. sudo apt-get install libncurses5-dev libncursesw5-dev
    4. download the snake.cpp file and open the directory.
    5. compile the code: g++ snake.cpp -o snake -lncurses
    6. run: ./snake

2. Neural Network.
    1. Implemented an MLP using C++.
    2. Implementation of the Matrix, Neuron, Layer and Neural Network class
    3. used cmake for compilation
    4. To run:- 
        1. clone the repo
        2. navigate to main.py
        3. customize your own neural architecture
        4. set the alpha and the num_epochs
        5. navigate to build directory
        6. enter shell command: "make"
    5. This should print out the architecture, final output and the loss values across all the epochs. 

3. Disk Management.
    1. Developed a WSL based C++ code which uses filesystems to scan your c, d or e drive and returns to you all the files greater than 500000000 bytes (i.e. approx 0.5 GB) along with a progress bar.
    2. download scan2.cpp and file_metadata_finder.cpp both the files and place them in the same folder
    3. Ensure C++ is 17 or above 
    4. Ensure g++ is 7 or above
    5. run (bash): g++ scan2.cpp file_metadata_finder.cpp -o scan
    6. run (bash): ./scan
        //scan.cpp is an old version of the file.


