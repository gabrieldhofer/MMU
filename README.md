### Memory Management Unit (MMU)
#### Operating Systems Final Exam
#### Author: Gabriel Hofer
#### Date: May 2, 2021

#### TODO
1. print formatted memory map to stdin
2. write tests for code
3. make page tables for multiple processes
4. make an inverted page table 

#### Memory Management
As we saw in CoA, memory is central to the operation of a modern computer system. Memory
consists of a large array of bytes, each with its own address. The CPU fetches instructions from
memory according to the value of the program counter. These instructions may cause additional
loading from and storing to specific memory addresses.
We introduced not only the concept of paging, but also virtual memory. If you decide to this
task you need to inside your dash invoke (you have the option to write this as a dash-function or a
free-standing program that is forked from inside the dash) a simulation of:
1. Paging, using an array of e elements simulating the simulated physical memory divided into
f frames of b bytes. Your simulation will run q processes (the user decides how many
processes), needing p pages. A memory map that keeps track of the frames. Each process
then accesses memory locations using:
    1. Basic method, each process having their own page table (needs to be stored
somewhere), requesting p pages from the physical memory.
    2. Inverted page table, one page table for the system.
2. Page replacement algorithm. You decide which algorithm to use, but it needs to be tied to
your paging algorithm.
    1. How many pages for each process?

#### Terminology used in this Document

**Page**
**Frame** 
**Page number**
**Offset**

#### Markdown Guide
<https://www.markdownguide.org/basic-syntax/>


#### Thinking about Memory 

Why should we use virtual memory?

Some of the benefits of virtual memory: 
* providing a separate or "isolated" memory space for applications that isn't shared with other 
applications.
* isolated memory also leads to increased security 
* creating arbitrarily large memory addresses that may or may not exist in actual memory

[wiki: virtual memory](https://en.wikipedia.org/wiki/Virtual_memory#:~:text=The%20primary%20benefits%20of%20virtual,physically%20available%2C%20using%20the%20technique)

#### What is segmentation and pages? 

In order for different processes to have their own memory, we need to partition or divide or split the 
memory into smaller pieces. This is what is known as **segmentation**.

The range of virtual addresses is partitioned/divided into smaller chunks called **pages**.

Physical memory is divided into smaller pieces called **frames**.

Moverover, an address in virtual memory belongs to a unique **page**, and this address
also has an offset in that page that tells us where the address is relative to the beginning
of the page.

### What is a page table? 

Essentially, a page table is used to map virtual addresses to physical addresses. 



#### What are resident bits and dirty bits? 






#### What is a Page Fault? 


#### Handling Page Faults




#### Thinking about Page Replacement




#### Thinking about how to implement a simulation of virtual memory and paging

In order to simulate virtual memory for multiple processes where either 
* each process had it's own page table
* all processes accessed the same inverted page table (IVT)
I asked myself whether I should use processes or threads. 

**Observation:** In the simulation we want the processes need to access the same physical memory.

Therefore, it makes sense to make a multithreaded program where each thread represents a process
because threads share the same memory while processes created with fork() don't share the same
memory.

Here is the simulation code creating multiple threads, each sharing the same memory. 




#### More Details

* we will be using a 32-bit address space (uint32\_t)



![two\_processes\_osdev](https://github.com/hofergabriel/MMU/blob/main/images/two_processes_osdev.png)


[osdev: Virtual Address Spaces](https://wiki.osdev.org/Paging#Virtual_Address_Spaces)



### Questions

#### How large should your simulated memory be? 

#### How large is the virtual memory of each process? 

#### How to simulate that a process is accessing a memory location? How often? In what order?

#### How to keep track of what memory locations are in use? 

#### What about shared frames? 

#### Are there risk for race conditions? How will you handle it? 

#### How to display all information, what makes sense for the user to see? 

#### Should the user be allowed to decide what information to see? 

#### Should the user be allowed to freeze the simulation at any moment and explore the current state? 

#### Usage

#### Testing








