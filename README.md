# Smart Home Simulation (Object-Oriented Programming in C++)

A comprehensive, performance-driven C++ application simulating a Smart Home ecosystem. This project serves as a practical implementation of advanced Object-Oriented Programming (OOP) concepts, demonstrating robust architecture, hierarchy design, and dynamic polymorphism.

## Key Features
* **Advanced OOP Hierarchy:** Implemented a deep inheritance structure (`Device` -> `Electronics` -> `SmartLight`/`Termostat`) leveraging pure virtual functions and abstraction.
* **Polymorphism & Dynamic Binding:** Utilized `virtual` methods and `override` specifiers to execute runtime behaviors dynamically across collections of different smart devices.
* **Safe Downcasting:** Integrated safe type conversion using RTTI (`dynamic_cast`) to enable user controls specific to certain device subclasses (e.g., modifying brightness exclusively on `SmartLight`).
* **Method Overloading:** Implemented function overloading within the `User` class to handle context-specific operations seamlessly based on provided arguments.
* **Memory & Resource Management:** Managed memory structures with explicit cleanup routines and destructors to guarantee a leak-free lifecycle for dynamically allocated objects.

## Tech Stack & Concepts
* **Language:** Modern C++
* **Core OOP:** Inheritance, Polymorphism, Encapsulation, Method Overloading, Abstract Classes (`pure virtual`)
* **Data Structures:** Standard Template Library (`std::vector`)
* **Type Management:** Run-Time Type Information (RTTI), `dynamic_cast`
