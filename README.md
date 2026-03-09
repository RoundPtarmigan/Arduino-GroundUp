This is a "bare metal" development project for Arduino Uno R3 (using an AVR microprosessor).

My main goal with this project is to continue improving as an embedded developer during a job search.
Because I worked primarily on large, well-developed programs using RTOSs in my last position, a bare metal approach on a well-known microprocessor allows me to fill in more low-level embedded knowledge.

As this is a personal development project, I approach design with a focus on learning. I test different approaches to design to see what works and what doesn't (and more importantly learn WHY this is the case).
I also avoid using outside hardware abstraction libraries (beyond what is included in the avr-gcc toolchain) with the goal of accruing low-level knowledge as I work through sub-projects. As a result, the code in this repository code varies and does not always represent how I'd tackle a problem in practice.

Basic Info:

Language: C

Compiler: avr-gcc

Bootloader: optiboot

AVR Flash Toolchain: AVRDUDE

