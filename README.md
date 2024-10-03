# Philosophers

This project is an implementation of the classic **Dining Philosophers Problem**, designed to explore multithreading and synchronization in C. The challenge is to manage multiple philosophers sharing forks in a way that avoids deadlock, starvation, and race conditions, using pthreads and mutexes.

## Table of Contents

- [Overview](#overview)
- [How It Works](#how-it-works)
- [Installation](#installation)
- [Usage](#usage)
- [Philosophers' Behavior](#philosophers-behavior)
- [Memory Management](#memory-management)

## Overview

The **Dining Philosophers Problem** involves philosophers who alternate between thinking, eating, and sleeping. Each philosopher requires two forks to eat, but there are fewer forks than philosophers, which leads to potential concurrency issues. This project focuses on solving the problem while ensuring that:

- No philosopher starves.
- There is no deadlock.
- Synchronization is handled efficiently.

## How It Works

The problem simulates philosophers sitting at a table, alternating between eating, thinking, and sleeping. Each philosopher must pick up two forks to eat, but only one fork is placed between each pair of philosophers. The program uses mutexes to synchronize the fork access and avoid deadlocks.

Each philosopher is represented as a separate thread, and a mutex is assigned to each fork. When a philosopher wants to eat, they attempt to lock both forks (mutexes) to prevent other philosophers from using them at the same time.

## Installation

To compile and run the project, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/msolinsk/philo.git
    cd philo
    ```

2. Compile the project:
    ```bash
    make
    ```

3. Run the program:
    ```bash
    ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
    ```

### Example:
```bash
./philo 5 800 200 200
```
This example runs the simulation with 5 philosophers, where each philosopher dies if they don’t eat within 800ms, spends 200ms eating, and 200ms sleeping.

## Usage
The program takes the following arguments:

number_of_philosophers - How many philosophers (and forks) there are.
time_to_die - Time (in milliseconds) a philosopher can survive without eating.
time_to_eat - Time (in milliseconds) it takes for a philosopher to eat.
time_to_sleep - Time (in milliseconds) a philosopher spends sleeping.
[number_of_times_each_philosopher_must_eat] (optional) - Number of times each philosopher must eat before the simulation ends. If not provided, the simulation runs indefinitely.
If the arguments are invalid or if the number of philosophers is less than 1, the program will return an error.

## Philosophers' Behavior
Each philosopher follows this routine:

Thinking: The philosopher thinks about life (or anything else) before trying to eat.
Eating: The philosopher picks up two forks (mutexes), one from their left and one from their right, and starts eating.
Sleeping: After eating, the philosopher puts down both forks and goes to sleep.
If a philosopher fails to pick up both forks within a certain time frame (time to die), they will die, and the simulation will end.

## Memory Management
The project ensures proper memory allocation and deallocation. Valgrind was used to check for memory leaks and threading issues.
