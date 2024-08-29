# ft_containers

`ft_containers` is a C++ project aimed at re-implementing several containers from the C++ Standard Template Library (STL). The goal of this project is to deepen the understanding of the internals of commonly used data structures and their associated algorithms. This project is part of the 42 school curriculum and focuses on generic programming, template metaprogramming, and iterator implementations in C++.

## Table of Contents
- [ft\_containers](#ft_containers)
	- [Table of Contents](#table-of-contents)
	- [About the Project](#about-the-project)
	- [Implemented Containers](#implemented-containers)
	- [Features](#features)
	- [Getting Started](#getting-started)
		- [Prerequisites](#prerequisites)
		- [Installation](#installation)

## About the Project

The `ft_containers` project is designed to provide a deep dive into the implementation details of C++ containers. This project will help to understand complex template programming techniques, iterator patterns, and the intricacies of memory management in C++.

## Implemented Containers

The following STL containers are re-implemented in this project:

- **vector**: A dynamic array that can resize itself automatically when an element is added or removed.
- **map**: A sorted associative container that contains key-value pairs with unique keys.
- **stack**: A container adapter providing a LIFO (Last-In, First-Out) data structure.
- **set**: A sorted associative container containing unique objects of a type.
- **other optional containers**: Depending on the scope, you might have additional containers like `list`, `queue`, etc.

## Features

- Complete re-implementation of STL containers using C++98 standard.
- Support for iterators (random access, bidirectional, etc.) and iterator traits.
- Implementation of allocator-aware containers.
- Compatibility with standard algorithms and operations.
- Extensive testing to ensure compatibility with STL behavior.

## Getting Started

### Prerequisites

To build and run the project, you will need:

- **g++** (GCC) version 4.8 or later, or any C++98 compliant compiler.
- **Make** build tool for compiling the project.

### Installation

1. **Clone the repository:**

   ```bash
   git clone https://github.com/4b93f/ft_containers.git
   cd ft_containers
