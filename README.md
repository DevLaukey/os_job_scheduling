# os_job_scheduling
*Efficiently allocate and schedule tasks with precision*

![C](https://img.shields.io/badge/language-C-blue)

## Built with the tools and technologies:
![C](https://img.shields.io/badge/language-C-blue)

## Table of Contents
- [Overview](#overview)
  - [Why os_job_scheduling?](#why-os_job_scheduling)
  - [Core Features](#core-features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Overview
`os_job_scheduling` is a project aimed at implementing efficient scheduling algorithms used in operating systems to allocate tasks and manage resources. The goal of this project is to provide an educational resource and a practical tool for developers and students to understand and work with different job scheduling strategies.

### Why os_job_scheduling?
Scheduling is a core function of an operating system that involves allocating CPU time to processes and tasks. This project helps to:
- Visualize and simulate scheduling algorithms for educational purposes.
- Provide a framework to understand the intricacies of job scheduling.
- Enhance problem-solving skills by offering hands-on experience with task scheduling techniques.

### Core Features
- 📅 **Task Scheduling Algorithms:** Implementations of multiple job scheduling algorithms such as FCFS (First Come First Serve), SJF (Shortest Job First), and Round Robin.
- 📊 **Performance Evaluation:** Compare and analyze the efficiency of different scheduling algorithms.
- 🎯 **Modular Design:** Easily extendable to include more scheduling techniques.

## Getting Started
Follow these instructions to set up the project on your local machine.

### Prerequisites
Ensure you have the following installed:
- GCC (GNU Compiler Collection)

### Installation
Clone the repository and compile the code:
```bash
git clone https://github.com/devlaukey/os_job_scheduling.git
cd os_job_scheduling
gcc -o scheduler main.c scheduler.c -I.
```

### Usage
Run the compiled scheduler to simulate a scheduling algorithm:
```bash
./scheduler
```
Provide the necessary inputs as prompted to observe scheduling behavior.

### Testing
Execute the test suite to verify functionalities:
```bash
gcc -o test_scheduler test_scheduler.c scheduler.c -I.
./test_scheduler
```

## Contributing
Thank you for considering contributing to `os_job_scheduling`! Please fork the repository and submit PRs with changes. Ensure your code follows the existing style and conventions of the project.

## License
This project is currently not licensed. If you wish to use or distribute it, please contact the repository owner.

## Contact
For any queries or feedback, please reach out to [victor.mburu.mwaura@gmail.com](mailto:victor.mburu.mwaura@gmail.com).
```
