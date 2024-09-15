# Simple-Signal-Handler
A student exercise designed to explore interrupts in Operating System Design. 

# Signal Handling in C!

## Summary of Signal Handling in C:

- **Signals**: A signal is a limited form of inter-process communication used in Unix-like operating systems. It notifies a process that a specific event has occurred (e.g., `SIGINT` for `Ctrl+C`).
- **Signal Handling**: A signal handler is a function that is invoked when a signal is received by the process. This allows the process to perform custom actions (e.g., cleanup, logging) or ignore certain signals.
- **Common Signals**: Signals include `SIGINT` (interrupt), `SIGTERM` (termination), `SIGKILL` (kill), and more. Some signals can be caught and handled, while others, like `SIGKILL`, cannot.
- **System Calls**:
  - `signal()`: A simple function to catch and handle signals, but with limitations.
  - `sigaction()`: A more robust and flexible system call for setting signal handlers.
- **Reentrancy**: Signal handlers must avoid calling non-reentrant functions, as they may lead to undefined behavior if interrupted.

## Table 1: Common Signals and Their Meanings

| **Signal**  | **Description**                   | **Default Action**        | **Can be Caught?** |
|-------------|-----------------------------------|---------------------------|--------------------|
| `SIGINT`    | Interrupt from keyboard (`Ctrl+C`) | Terminate the process      | Yes                |
| `SIGTERM`   | Termination signal                 | Terminate the process      | Yes                |
| `SIGKILL`   | Kill signal (immediate termination)| Terminate the process      | No                 |
| `SIGQUIT`   | Quit from keyboard (`Ctrl+\`)      | Terminate and core dump    | Yes                |
| `SIGHUP`    | Hangup (terminal closed)           | Terminate the process      | Yes                |
| `SIGALRM`   | Timer signal from `alarm()`        | Terminate the process      | Yes                |
| `SIGCHLD`   | Child process stopped/terminated   | Ignore                     | Yes                |
| `SIGSEGV`   | Invalid memory access              | Terminate and core dump    | No                 |

## Table 2: Important System Calls for Signal Handling

| **Function** | **Purpose**                                                   | **Usage**                                          |
|--------------|---------------------------------------------------------------|----------------------------------------------------|
| `signal()`   | Simple signal handling setup, resets after each signal         | `signal(SIGINT, handler_function);`                |
| `sigaction()`| Robust signal handling setup, persists after each signal       | See the `sigaction()` structure below              |
| `raise()`    | Sends a signal to the calling process                         | `raise(SIGINT);`                                   |
| `kill()`     | Sends a signal to another process by process ID (PID)          | `kill(pid, SIGINT);`                               |
| `pause()`    | Suspends the process until a signal is received                | `pause();`                                         |

## Table 3: The `sigaction` Structure

| **Field**           | **Description**                                                                 |
|---------------------|---------------------------------------------------------------------------------|
| `sa_handler`        | Pointer to the signal handling function (or `SIG_IGN` to ignore the signal)      |
| `sa_mask`           | Set of signals to be blocked while the handler is executing                      |
| `sa_flags`          | Flags to modify signal handling behavior (e.g., `SA_RESTART`, `SA_SIGINFO`)      |
| `sa_sigaction`      | Alternative to `sa_handler` for handling signals with additional information     |

## Best Practices for Signal Handling:
1. **Use `sigaction()` instead of `signal()`**:
   - `sigaction()` provides more control and ensures the handler is not reset after the first signal.
2. **Keep signal handlers simple**:
   - Only perform simple tasks like setting flags or counters. Avoid complex logic and non-reentrant functions (e.g., `printf`, `malloc`).
3. **Use atomic operations**:
   - If a signal handler updates shared variables, use `volatile` or atomic types to avoid race conditions.
4. **Reentrancy**:
   - Avoid calling non-reentrant functions inside signal handlers. These include functions like `malloc()`, `free()`, `printf()`, and `fopen()`.

---
