*This project has been created as part of the 42 curriculum by jsouza.*

# Codexion

## Description

Codexion is a concurrency simulation where multiple coders compete for a limited set of USB dongles in order to compile their quantum code. Each coder is represented by a POSIX thread and must acquire two dongles simultaneously to compile. After compiling, they debug and refactor before attempting to compile again.

The simulation ends either when every coder has compiled the required number of times, or when a coder burns out — meaning they failed to start a new compile within the allowed time window.

The project exercises core concurrency concepts: thread creation and synchronization, mutex-protected shared resources, condition variables, scheduling policies, and precise timing.

## Instructions

### Compilation

```bash
make
```

Compiles the project with `-Wall -Wextra -Werror -pthread` and produces the `codexion` executable.

Other Makefile rules:

```bash
make clean    # removes the executable
make fclean   # removes the executable and all object files
make re       # fclean + all
```

### Execution

```bash
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

All arguments are mandatory. Invalid inputs (negative numbers, non-integers, unknown scheduler) are rejected with an error message.

| Argument | Description |
|---|---|
| `number_of_coders` | Number of coders (and dongles) — integer ≥ 1 |
| `time_to_burnout` | Milliseconds a coder can go without starting a compile before burning out |
| `time_to_compile` | Milliseconds a compile takes (requires two dongles) |
| `time_to_debug` | Milliseconds spent debugging after each compile |
| `time_to_refactor` | Milliseconds spent refactoring after each debug |
| `number_of_compiles_required` | Simulation ends when every coder reaches this compile count |
| `dongle_cooldown` | Milliseconds a dongle must rest after being released before it can be taken again |
| `scheduler` | Arbitration policy: `fifo` or `edf` |

### Example

```bash
./codexion 4 800 100 100 100 3 50 fifo
```

### Expected output format

```
0 1 has taken a dongle
1 1 has taken a dongle
1 1 is compiling
201 1 is debugging
401 1 is refactoring
...
1505 4 burned out
```

---

## Blocking cases handled

### Deadlock prevention

Each coder needs two dongles simultaneously. In a naive implementation where every coder picks up their left dongle first and then waits for the right one, a circular wait forms and the simulation deadlocks. This is one of Coffman's four necessary conditions for deadlock (mutual exclusion, hold and wait, no preemption, circular wait). The scheduling layer prevents this by ensuring that no two adjacent coders are ever granted compile permission at the same time — at most `floor(N/2)` coders compile in any given round, and no two selected coders are neighbours.

### Starvation prevention

Under FIFO scheduling, coders are served in arrival order, ensuring every coder eventually gets a turn. Under EDF, priority is given to the coder whose burnout deadline is closest (`last_compile_start + time_to_burnout`), which directly prevents the most at-risk coder from starving. The scheduling layer guarantees liveness as long as the simulation parameters are feasible.

### Cooldown handling

After a dongle is released, it cannot be taken again until `dongle_cooldown` milliseconds have elapsed. The compile function checks both dongles' cooldown before proceeding and busy-waits in small increments until both are available.

### Precise burnout detection

A dedicated monitor thread (`check_burnout`) continuously iterates over all coders and checks whether any coder has exceeded their burnout deadline. The check is performed under the coder's lock to avoid a race between the burnout detection and a concurrent `last_compile` update. Once burnout is confirmed, the burnout message is printed before releasing the lock, guaranteeing the print happens within the required 10 ms window.

### Log serialization

All `printf` calls that produce simulation output are protected so that messages from concurrent threads never interleave on the same line.

---

## Thread synchronization mechanisms

### `pthread_mutex_t`

- **`coder.lock`** — protects `last_compile`. Held only during the read-modify-write of that field and during burnout detection, never during long sleeps.
- **`dongle.lock`** — protects each dongle's state. Held from the moment a coder takes the dongle until it is released after the compile.
- **`infos->lock`** — protects the scheduler's `ids` array. The moderator holds it while computing the next scheduling round; coders hold it while checking whether their ID has been granted.
- **`infos->moder_lock`** — protects the `counter` field used by the moderator to track how many coders have finished their compile in the current round.
- **`sim.lock`** — protects `continue_sim` and the simulation start flag. Used to coordinate the startup barrier and the stop signal.

### `pthread_cond_t`

- **`infos->cond`** — coders wait on this condition until their ID appears in the scheduler's grant list.
- **`infos->moder_cond`** — the moderator waits on this until enough coders have completed the current round. The burnout thread also broadcasts on it to unblock the moderator when a burnout occurs.
- **`sim.cond`** — used for the startup barrier: coder threads and the moderator wait here until `init` finishes setting up all tables and broadcasts the start signal.

### Race condition prevention

The most critical race is between a coder updating `last_compile` and the burnout thread reading it. Both operations are guarded by `coder.lock`. The burnout print itself happens while the lock is held so that a coder cannot sneak in a compile and print between the burnout decision and the burnout message.

The `continue_sim` flag is read by all threads and written by both the moderator and the burnout thread. Reads and writes near critical transitions are done under `sim.lock` or `coder.lock` as appropriate to prevent torn reads.

---

## Resources

- [POSIX Threads Programming — Blaise Barney, LLNL](https://hpc-tutorials.llnl.gov/posix/)
- [The Linux Programming Interface — Michael Kerrisk](https://man7.org/tlpi/)
- [`pthread_cond_wait` man page](https://man7.org/linux/man-pages/man3/pthread_cond_wait.3.html)
- [`gettimeofday` man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)
- [Coffman conditions — Wikipedia](https://en.wikipedia.org/wiki/Coffman_conditions)
- [Earliest Deadline First scheduling — Wikipedia](https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling)

### AI usage

Claude (claude.ai) was used during this project for the following:

- Diagnosing Valgrind leak reports and identifying missing `pthread_join` calls.
- Discussing the race condition between burnout detection and `last_compile` updates, and the correct placement of mutex locks relative to printf calls.
- Reviewing the Makefile for missing object files in the link rule.

All AI-generated content was reviewed, tested, and adapted before being included in the project.
