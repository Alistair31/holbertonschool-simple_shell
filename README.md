<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Alistair/holbertonschool-simple_shell">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h1>Simple Shell</h1>
  <p>A minimal Unix-like shell written in C that reads commands, resolves paths, and executes programs.</p>

  <!-- BADGES -->
  <p align="center">
    <a href="https://github.com/Handroc"><img src="https://img.shields.io/badge/github-Handroc-blue?logo=github&style=for-the-badge"></a>
    <a href="https://github.com/Alistair31/holbertonschool-simple_shell/graphs/contributors"><img src="https://img.shields.io/github/contributors/Alistair31/holbertonschool-simple_shell.svg?style=for-the-badge" alt="Contributors"></a>
    <a href="https://github.com/Alistair31"><img src="https://img.shields.io/badge/github-Alistair31-blue?logo=github&style=for-the-badge"></a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary><h2>Table of Contents</h2></summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a>
    <li><a href="#built-with">Built With</a></li>
    <li><a href="#component-summary">Component Summary</a></li>
    <li><a href="#flowchart">Flowchart</a></l
    <li><a href="#getting-started">Getting Started</a>
    <li><a href="#prerequisites">Prerequisites</a></li>
    <li><a href="#installation">Installation</a></li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<u>## About The Project

The simple shell is a minimal Unix-like shell in C. It reads user input, resolves executable paths, and spawns processes to run commands.  
The shell supports a small subset of POSIX shell behavior, focused on process creation and simple argument handling.  
The implementation is intentionally compact and educational. It is suitable for learning how shells interact with the operating system via `fork`, `execve`, and related system calls.

<p align="right">(<a href="#simple-shell">back to top</a>)</p>

<u>## Built With

<div align="center">
  
[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![VS Code](https://img.shields.io/badge/VS%20Code-007ACC?style=for-the-badge&logo=visualstudiocode&logoColor=white)](https://code.visualstudio.com/)

</div>
This shell relies on standard POSIX APIs and a C toolchain. You can build and run it on most Unix-like systems.  

<p align="right">(<a href="#simple-shell">back to top</a>)</p>

<u>## Component Summary

This table lists core files and their responsibilities. Each file encapsulates a focused part of the shell behavior.

| File           | Key Function  | Description                                             |
| -------------- | ------------- | ------------------------------------------------------- |
| `simple_shell.c` | `main`, `command` | Entry point; reads input and handles command execution |
| `bunchwords.c`   | `bunchwords`      | Reads a line, prompts user, and returns token array     |
| `split_words.c`  | `split_words`     | Splits a string into individual words                   |
| `shellpath.c`    | `shellpath`       | Searches standard paths to locate executable commands   |

<p align="right">(<a href="#simple-shell">back to top</a>)</p>

<u>## Flowchart

This section shows the high-level control flow and how user input becomes a running process. The flowchart highlights input handling, built-in commands, error paths, and cleanup.

```mermaid
flowchart TD
    Start((Start)) --> CheckTTY[Detect interactive mode]
    CheckTTY --> LoopStart[[Shell loop start]]

    LoopStart --> PromptCheck{Interactive mode}
    PromptCheck -- Yes --> ShowPrompt[Print prompt]
    PromptCheck -- No --> SkipPrompt[Skip prompt]

    ShowPrompt --> ReadLine[Read line from stdin]
    SkipPrompt --> ReadLine[Read line from stdin]

    ReadLine --> EOFCheck{EOF or read error}
    EOFCheck -- Yes --> EOFExit[Print newline and exit loop]
    EOFExit --> End((Exit shell))
    EOFCheck -- No --> EmptyLineCheck{Line empty after trimming newline}

    EmptyLineCheck -- Yes --> IgnoreEmpty[Free buffer and continue]
    IgnoreEmpty --> LoopStart

    EmptyLineCheck -- No --> Tokenize[Split line into argument array]
    Tokenize --> FirstArgCheck{First argument exists}
    FirstArgCheck -- No --> FreeEmptyArgs[Free empty array]
    FreeEmptyArgs --> LoopStart

    FirstArgCheck -- Yes --> BuiltinExitCheck{First argument is exit}
    BuiltinExitCheck -- Yes --> FreeExitArgs[Free args and exit shell]
    FreeExitArgs --> End

    BuiltinExitCheck -- No --> ResolvePath[Call shellpath to resolve command]
    ResolvePath --> PathFound{Executable path found}
    PathFound -- No --> PathError[Print error and free args]
    PathError --> LoopStart

    PathFound -- Yes --> ForkCall[Call fork]
    ForkCall --> ForkFailed{Fork failed}
    ForkFailed -- Yes --> ForkError[Print error and free resources]
    ForkError --> LoopStart

    ForkFailed -- No --> InChildOrParent{Child or parent process}
    InChildOrParent -- Child --> ExecCmd[Child calls execve]
    ExecCmd --> ExecFail[On failure, print error and terminate child]

    InChildOrParent -- Parent --> WaitChild[Parent waits for child to finish]
    WaitChild --> CleanupParent[Free resolved path and args]
    CleanupParent --> LoopStart
```

- The main loop reads user input, handles interactive prompts, and detects EOF.
- Empty input lines are ignored after freeing temporary buffers.
- The `exit` token is treated as a built-in and terminates the shell.
- External commands go through path resolution, forking, execution, waiting, and cleanup.

<p align="right">(<a href="#simple-shell">back to top</a>)</p>

<!-- GETTING STARTED -->
<u>## Getting Started

This section explains how to set up the simple shell locally. You will clone the repository, build the binary with a C compiler, and run it from your terminal.

<u>### Prerequisites</u>

You need a POSIX-like environment and a working C toolchain. Most Linux distributions and macOS systems already provide what you need.

- A C compiler such as `gcc`:

  ```bash
  gcc --version
  ```

- Standard build tools and headers for your platform.
- A terminal emulator and basic command-line familiarity. We used VScode

<p align="right">(<a href="#simple-shell">back to top</a>)</p>

<u>### Installation

Follow these steps to download, compile, and run the shell. All commands should run in your terminal.

1. Clone the repository:

   ```bash
   git clone https://github.com/Alistair31/holbertonschool-simple_shell.git
   cd holbertonschool-simple_shell
   ```

2. Compile the sources into a single executable:

   ```bash
   gcc -Wall -Werror -Wextra -pedantic *.c -o simple_shell
   ```
   
3. Run the shell from the build directory:

   ```bash
   ./simple_shell
   ```

4. Optionally add the build directory to your `PATH`:

   ```bash
   export PATH="$PWD:$PATH"
   ```

<p align="right">(<a href="#simple-shell">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage

This shell reads commands from standard input, resolves their paths, and executes them in child processes. It supports both interactive and non-interactive modes.

- In interactive mode, you see a `$ ` prompt and can type commands.
- In non-interactive mode, the shell reads commands from a pipe or file.
- The `exit` command terminates the shell and frees all allocated memory.
- Any other token is treated as a program name to execute with optional arguments.

Example interactive session:

```bash
./simple_shell
$ ls
simple_shell  simple_shell.c  shellpath.c  bunchwords.c  split_words.c
$ echo Hello world
Hello world
$ exit
```
<img src="interactive_test.gif" alt="interactive" width="1000">

Example of non interactive test:

On your own terminal you can use in a non interactive way this simple shell.  
Type echo "executable" | ./simple_shell and it would execute it without entering in the simple shell

<img src="non_interactive_test.gif" alt="non_interactive" width="1000">

As you can see it can execute some command 

For a visual overview of the runtime behavior, refer to the detailed flowchart in the [Flowchart](#flowchart) section. That diagram shows how the shell handles prompts, input lines, built-ins, external commands, and errors.

<p align="right">(<a href="#simple-shell">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap

<p align="right">(<a href="#simple-shell">back to top</a>)</p>

<!-- CONTACT -->
## Contact

See AUTHOR.TXT file  

<p align="right">(<a href="#simple-shell">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Use this section to credit resources or people that helped the project. You can list tutorials, documentation, or mentors here.

- [![Mermaid](https://img.shields.io/badge/Mermaid-ff4f81?style=for-the-badge)](https://mermaid.js.org/)&nbsp;&nbsp;&nbsp;&nbsp;For the [Flowchart](#flowchart) diagram
- [![Asciinema](https://img.shields.io/badge/Asciinema-000000?style=for-the-badge&logo=asciinema&logoColor=red)](https://asciinema.org/)&nbsp;&nbsp;&nbsp;&nbsp;For the demo (GIFs) in the [Usage](#usage) section

<p align="right">(<a href="#readme-top">back to top</a>)</p>
