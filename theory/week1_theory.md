# Module 1 Theory Answers: GitHub Setup & Version Control
*IIT Jammu Summer School 2026 - Coursework*

---

## Q9. Git Command Differences: `git clone` vs. `git fetch` vs. `git pull`

| Command | Definition | What it does | When to use it |
| :--- | :--- | :--- | :--- |
| **`git clone`** | Copies an existing remote repository locally. | Downloads the entire repository (all branches, history, files) and sets up the remote tracking pointers. | Use this **once** at the beginning of a project to copy a codebase from GitHub/GitLab to your local machine. |
| **`git fetch`** | Downloads changes from remote without merging. | Downloads new commits, files, and branches from the remote repository, but does **not** modify your current working branch. | Use when you want to see what your peers have done on remote branches before integrating their code into your local files. |
| **`git pull`** | Downloads and automatically merges changes. | Performs a `git fetch` followed by a `git merge` under the hood. It updates your current local working branch directly with remote commits. | Use when you want to sync your current local branch immediately with the remote server's latest commits. |

---

## Q10. What is a `.gitignore` file?

A `.gitignore` file is a text file placed in the root of a Git repository that specifies patterns of files and directories that Git should ignore (not track). This prevents compiled binaries, private API keys, temporary system files, or IDE configurations from cluttering your repository.

### Sample `.gitignore` for an Arduino Project
```gitignore
# Compiled output files (pre-built binaries and assembly files)
*.hex
*.elf
*.o
*.d
*.bin
*.eep
*.lst
*.map

# OS-specific files (system-generated files)
.DS_Store
Thumbs.db
Desktop.ini

# IDE config folders and build directories (environment/workspace settings)
.vscode/
build/
.history/
.ino.cpp
.settings/
.project
.cproject
```
