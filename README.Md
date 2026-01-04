## Overview

Log Analyzer is a **command-line log analysis tool written in C** that processes large log files efficiently using a **streaming design**.
It reads log files line-by-line, classifies log levels, aggregates repeated error messages, and produces a concise summary report.

This project is intentionally built as a **core engine** that can later be reused by a graphical interface without modifying the analysis logic.

Version **v1.0** represents a **feature-complete, tested, and frozen CLI tool**.

---

## What This Tool Does (v1.0)

### 1. Streaming Log File Processing

- Reads log files **line by line**
- Does **not** load the entire file into memory
- Suitable for **very large log files**

This ensures:

- Low memory usage
- Stable performance
- No risk of memory exhaustion

---

### 2. Log Level Classification

The analyzer recognizes and counts the following log levels:

- `INFO`
- `WARN`
- `ERROR`

Each valid log entry contributes to:

- Total line count
- Individual severity counters

Invalid or malformed lines are **safely ignored** without crashing.

---

### 3. Error Message Aggregation

- Error messages are grouped by **exact message text**
- Duplicate errors are counted
- Each unique error message stores:

  - Message text
  - Number of occurrences

This allows the tool to highlight **recurring problems**, not just raw error volume.

---

### 4. Top-N Error Reporting

- Displays the **most frequent error messages**
- Supports configurable limits via CLI flags
- Errors are sorted by occurrence count (descending)

This helps identify **root causes**, not noise.

---

### 5. Robust Command-Line Interface

The CLI supports:

- File path input
- Optional flags:

  - `--errors-only`
  - `--top-errors N`
  - `--help`
  - `--version`

The program validates arguments and exits cleanly on invalid input.

---

### 6. Defensive Parsing & Error Handling

- Missing files are handled gracefully
- Empty files do not cause failures
- Invalid log lines are ignored safely
- No segmentation faults under normal or edge-case inputs

This makes the tool **safe to run on unknown logs**.

---

## Internal Architecture (v1.0)

The project follows a **modular C design** with strict separation of responsibilities:

### Core Modules

- **File Reader**

  - Streams log lines from disk

- **Parser**

  - Converts raw log lines into structured entries

- **Analyzer**

  - Maintains counters and aggregates errors

- **Reporter**

  - Formats and prints final output

Each module is isolated through headers and does **one job only**.

---

### Build System

- Uses a Makefile
- Compiles each source file independently
- Produces a single CLI executable: `loganalyzer`

---

## Features (v1.0)

- Streaming log file analysis
- INFO / WARN / ERROR classification
- Error aggregation by message text
- Top-N most frequent errors
- Robust CLI argument parsing
- Safe handling of malformed input
- Stable performance on large files
- Windows-compatible command-line tool

---

## Non-Goals (v1.0)

The following are **intentionally excluded** from this version:

- No graphical user interface (GUI)
- No JSON or machine-readable output
- No multithreading
- No log file modification or writing
- No real-time log monitoring

These exclusions are deliberate to keep the core engine **simple, stable, and reusable**.

---

## Version Freeze Statement

This project is now frozen as:

**`loganalyzer v1.0 (CLI)`**

From this point forward:

- Only bug fixes are allowed
- No refactoring of working code
- No new features added
- Core analysis logic remains unchanged

Any future development (such as a GUI) will be built **on top of this engine**, not inside it.

---

## Intended Next Phase (Not Part of v1.0)

- Graphical user interface using a separate front-end layer
- Reuse of the existing C engine without modification

---

## Summary

Version **v1.0** represents a **complete, stable, and tested CLI log analysis tool** written in standard C.
It demonstrates real-world systems programming concepts including modular design, safe memory usage, and defensive input handling.

---

### ✅ CLI Phase: COMPLETE

### 🔒 Status: FROZEN

---

## Features (v1.0)

- Streaming log file analysis
- INFO / WARN / ERROR classification
- Error aggregation by message
- Top-N most frequent errors
- Robust CLI argument parsing
- Handles large log files safely
- Windows-compatible CLI tool

## Non-Goals (v1.0)

- No GUI
- No JSON output
- No multithreading
- No log file modification
