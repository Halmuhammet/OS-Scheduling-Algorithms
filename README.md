# CPU Scheduling Algorithms Simulator

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This program simulates how different Operating System scheduling algorithms manage process execution.

## Implemented Algorithms

This simulator implements the following scheduling algorithms:

1. **First Come, First Served (FCFS)** - Non-preemptive algorithm that executes processes in the order they arrive
2. **Round Robin (RR)** - Preemptive algorithm with two variants:
   - RR-10: Uses a time quantum of 10ms
   - RR-40: Uses a time quantum of 40ms
3. **Shortest Process Next (SPN)** - Non-preemptive algorithm that selects the process with the shortest service time
4. **Shortest Remaining Time (SRT)** - Preemptive version of SPN that can interrupt running processes when a shorter one arrives
5. **Highest Response Ratio Next (HRRN)** - Non-preemptive algorithm that selects processes based on (wait_time + service_time)/service_time
6. **Feedback Queue** - Multi-level priority queue system that demotes processes to lower priority queues as they consume CPU time

## Getting Started

### Prerequisites

- C++ compiler with C++11 support (GCC/G++ recommended)
- Standard C++ libraries

### Compilation

```bash
g++ -std=c++11 main.cpp -o cpu_scheduler
```

### Usage

1. Prepare an input file `input.in` with tab-separated values in the format:
   ```
   [Process ID]   [Arrival Time]   [Service Time]
   ```

2. Update the file paths in the code to match your environment:
   ```cpp
   string filepath = "path/to/your/input.in";  // Input file path
   ```

3. Run the compiled program:
   ```bash
   ./cpu_scheduler
   ```

4. Check the output files in the specified directory:
   - fcfs.out
   - rr_10.out
   - rr_40.out
   - spn.out
   - srt.out
   - hrrn.out
   - feedback.out

## Input File Format

The input file should contain tab-separated values with the following format:

```
P1   0   100     # Process P1, arrives at time 0, requires 100ms of CPU time
P2   20  50      # Process P2, arrives at time 20, requires 50ms of CPU time
```

## Output Format

Each output file shows which process is running during each 10ms time quantum. For example:

```
P1    # P1 running from 0-10ms
P1    # P1 running from 10-20ms
P2    # P2 running from 20-30ms
```

## How It Works

1. The program reads process information from an input file
2. Processes are sorted based on arrival time and stored in a ready queue
3. Each scheduling algorithm is applied to the processes
4. The results are written to separate output files

## Implementation Details

- **Data Structure**: Uses `deque<deque<string>>` for process representation and queue management
- **Time Management**: Simulates time in discrete 10ms quanta
- **Sorting Algorithms**: Custom comparator functions for different scheduling criteria
- **Modular Design**: Each scheduling algorithm has its own function for clarity and maintainability

## Code Structure

- `compareServiceTime()` - Comparator for service time sorting
- `compareHighestResponseRatio()` - Comparator for HRRN algorithm
- `compareArrivalTime()` - Comparator for arrival time sorting
- `fcfs()` - First Come, First Served implementation
- `rr10()` - Round Robin with 10ms quantum implementation
- `rr40()` - Round Robin with 40ms quantum implementation
- `spn()` - Shortest Process Next implementation
- `srt()` - Shortest Remaining Time implementation
- `hrrn()` - Highest Response Ratio Next implementation
- `feedback()` - Feedback Queue implementation
- `feedback_helper()` - Helper function for the Feedback Queue algorithm

## Contributing

Contributions are welcome! Here are some ways you can contribute:

- Implement additional scheduling algorithms
- Improve the efficiency of existing implementations
- Add visualization features for the scheduling results
- Create a proper input file validation system

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- This project was created as an educational tool for understanding OS scheduling algorithms
- Inspired by operating systems coursework and textbooks on OS concepts
