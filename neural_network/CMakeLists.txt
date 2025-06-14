cmake_minimum_required(VERSION 3.22)
project(neural_network CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O2")

add_executable(
	neural_network
	main.cpp
	neuron.cpp
	layer.cpp
	matrix.cpp
	neural_net.cpp
)
