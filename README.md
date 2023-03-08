2022/2023 Compilers Coursework
==============================

There are two components to the coursework:

- [*A C compiler*](c_compiler.md), worth 90%. The source language is pre-processed C90, and the target language is RISC-V assembly. The target environment is Ubuntu 22.04, as described in the attached [Dockerfile](Dockerfile). See [here](./c_compiler.md) for the full set of requirements and more information about the testing environment.

- [*Evidence of time-tracking/project management*](management.md), worth 10%. This will be assessed orally at the start of Summer term. See [here](management.md) for more information about this component.

Repositories
============

Each group gets a bare private repository. It is up to you if you want to clone the main specification, or to start from scratch.

Submission
==========

The deadline for submitting your C compiler is **Friday 24 March 2023 at 23:59**. There is no deadline for the project management component; instead, this will be assessed by a short oral viva that will be organised in Summer term.

Submission will be via GitHub (code) and Teams (commit hash), as in the labs.

All submissions will be tested functionally -- there is no expectation for your compiler to *optimise* its input. Moreover, your compiler will only be tested on *valid* inputs, so you do not need to handle faulty inputs in a graceful way.

Changelog
=========

* New for 2022/2023:

    * Target architecture is now RISC-V rather than MIPS, in order to align with the modernised Instruction Architectures half of the module.
    * Instead of Vagrant, Docker is now used for the testing environment (with optional VS Code support).
    * Test scripts are now provided to check your compiler against the set of public tests, without having to write this yourself.
    * The basic compiler framework has been improved to support command line arguments.
    * GitHub Actions can now perform automated testing of your compiler.

Management:
---Milestones----
Week 1: Using Lab 2 took tree and changed adapted it to print to output stream

Week 2: Implement parser and lexer to build tree for expressions, functions and assignments
        All Operators and number only expressions store results in temp registers and return the register number.
Week 3:
