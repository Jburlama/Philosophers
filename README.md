# Philosophers

## Philosophers is a project from the 42 school written in C. It focuses on the fundamentals of threading processes.

In this project, I've learned how to create threads and gained an understanding of how to synchronize them using mutexes.

This project follows the the 42 norm:
* [42 Norms](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf) - Information about 42 code norms. `PDF`



##  POSIX thread (pthread)

For this project, I used the POSIX thread (pthread) API, which is a powerful and widely used library for creating and managing threads in C programs. The pthread API provides a set of functions to create, control, and synchronize threads, enabling parallel execution and efficient use of multi-core processors. Key features include thread creation and termination, and mutexes for mutual exclusion.

## About

This C program provides a practical exploration of the dining philosophers problem. 

Imagine a group of philosophers seated around a table, pondering and dining. each philosopher, represented as a thread, possesses only one fork (mutex) initially. To successfully eat, a philosopher requires access to two forks — one held by themselves and one by their neighboring philosopher. This setup necessitates the coordination of fork sharing among philosophers, ensuring that no deadlock occurs and that all philosophers have the opportunity to dine.
- [Subject](https://github.com/jotavare/philosophers/blob/master/subject/en_subject_philosophers.pdf) `PDF`

### Usage

 - Run make inside the "philo" repository, and the Makefile will compile the binary.

- The program is run with the following arguments:

```bash
./philo [number of philosophers] [time to die] [time to eat] [time to sleep] [times to eat]
```
The last argument, times to eat, is optional.

| Arg | Function | Description |
| :- | :- | :- |
| [arg1] | `number_of_philosophers`                   | 0 - 200|
| [arg2] | `time_to_die`                               | > 60  |
| [arg3] | `time_to_eat`                               | > 60  |
| [arg4] | `time_to_sleep`                             | > 60|
| [arg5] | `number_of_times_each_philosopher_must_eat` | > 0|

