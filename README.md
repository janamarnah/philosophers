*This project has been created as part of the 42 curriculum by jalamarn*


# philosophers
## Description
**philosophers** is a concurrency project developed in C, based on the classic **Dining Philosophers Problem** formulated by Edsger Dijkstra.  
The goal of the project is to simulate a group of philosophers sitting around a table who alternate between eating, sleeping, and thinking, while sharing a limited number of forks, all without any philosopher starving to death, and while respecting strict timing rules.
This project introduces fundamental concepts of:
- Thread and process management
- Mutexes and semaphores
- Data race prevention
- Deadlock avoidance
- Precise time handling
- Argument parsing and validation
Each philosopher needs two forks to eat, and forks are shared between neighbors. The challenge is to coordinate access to these shared resources so the simulation runs correctly and safely in parallel.

Arguments:
Argument                    Description
number_of_philosophers      Number of philosophers, and also the number of forks
time_to_die                 Time (ms) a philosopher can go without eating before dying
time_to_eat                 Time (ms) it takes a philosopher to eat
time_to_sleep               Time (ms) a philosopher spends sleeping
meals_required              Simulation stops once every philosopher has eaten this many times

Features:
- One thread per philosopher (mandatory), one process per philosopher (bonus)
- Forks protected by mutexes (mandatory) / semaphores (bonus)
- Death detection reported within 10 ms
- Optional stop condition based on a required number of meals
- Timestamped state logging to the terminal
- Deadlock avoidance through fork-order and timing strategies
- Error handling for invalid arguments
- No data races and no memory leaks


## Instructions
### Requirements
- **Operating System:** Linux or macOS  
- **Compiler:** `gcc`
- **Libraries:** pthread (standard, no external library needed)
### Compilation
To compile the program, use the provided Makefile. 
Simply run:
`make`

This will generate the executable philo in the current directory.
For the bonus part (processes and semaphores):

`make bonus`

This will generate the executable philo_bonus.
### Installation
No external library needs to be installed. The project only relies on the **pthread** library, which is available by default on Linux and macOS systems used at 42. A standard C toolchain (`gcc` and `make`) is all that is required.
### Execution
Run the program with the required arguments:
`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_required]`

Examples:

`./philo 5 800 200 200` //
`./philo 5 800 200 200 7`//
`./philo 1 800 200 200`

The state of each philosopher is printed to the terminal in the following format:

`timestamp_in_ms X has taken a fork`
`timestamp_in_ms X is eating`
`timestamp_in_ms X is sleeping`
`timestamp_in_ms X is thinking`
`timestamp_in_ms X died`



## Resources
### Documentation
- https://en.wikipedia.org/wiki/Dining_philosophers_problem
- https://hpc-tutorials.llnl.gov/posix/
- https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
### AI Usage
AI was used strictly as a development aid and not as a substitute for implementing the project logic. It was used in the following ways:
- Helping understand the theory behind the problem, such as deadlock conditions and the difference between mutexes and semaphores
- Assisting in identifying and debugging data races and memory leaks, as well as ensuring proper cleanup and thread/process termination
- Reasoning about timing edge cases used to test the simulation
- Supporting the writing, structuring, and clarification of this README file