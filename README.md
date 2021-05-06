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


#### Parameters: e, f, b, q, p
For clarity, some parameters of the parameters mentioned above will be fixed: 

* e = 2048
* f = 8
* b = 256

Since we ask the user how many processes to create, q is not fixed.

The number of pages p will be equal to the number of processes q chosen by the user since 
each process will have its own page table for the basic method.



> There are three architectural parameters that characterize a virtual memory system and hence the architecture of the MMU.

> P is the number of address bits used for the page offset in both virtual and physical addresses. V is the number of address bits used for the virtual page number. And M is the number of address bits used for the physical page number. All the other parameters, listed on the right, are derived from these three parameters.

![page\_map\_arithmetic](https://github.com/hofergabriel/MMU/blob/main/images/page_map_arithmetic.png)

```
/********************************************//**
 *    8 bits in the page offset 
 *    4 bits for virtual pages
 *    3 bits for physical pages
 * 
 *    based on the example in the
 *    MIT OpenCourseWare slides
 ***********************************************/
const int v = 4;
const int m = 3;
const int p = 8;
```



#### Benefits of Virtual Memory 

Why should operating systems support virtual memory?

* Provide a separate, isolated memory space for applications that isn't shared with other 
applications.
* Isolated memory can help increase security 
* Creating arbitrarily large memory addresses that may or may not exist in actual memory

#### What are segmentation and pages? 

In order for different processes to have their own memory, we need to partition or divide or split the 
memory into smaller pieces. This is what is known as **segmentation**.

The range of virtual addresses is partitioned/divided into smaller chunks called **pages**.

Physical memory is divided into smaller pieces called **frames**.

Moverover, an address in virtual memory belongs to a unique **page**, and this address
also has an offset in that page that tells us where the address is relative to the beginning
of the page.

#### What is a page table? 

Essentially, a page table is used to map virtual addresses to physical addresses. 

#### Translating Virtual Addresses to Physical Addresses

This project will be based on implementing the model for virtual memory detailed and explained 
in the MIT Opencourseware [slides](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-004-computation-structures-spring-2017/c16/c16s1/)

> Here’s an example of the MMU in action. To make things simple, assume that the virtual address is 12 bits, consisting of an 8-bit page offset and a 4-bit virtual page number. So there are 2^4 = 16 virtual pages. The physical address is 11 bits, divided into the same 8-bit page offset and a 3-bit physical page number. So there are  2^3 = 8 physical pages.

![example\_virtual\_to\_physical\_translation](https://github.com/hofergabriel/MMU/blob/main/images/example_virtual_to_physical_translation.png)

![virtual\_memory\_the\_CS\_view](https://github.com/hofergabriel/MMU/blob/main/images/virtual_memory_the_CS_view.png)


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




#### Implementation Details

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

#### Markdown Guide
<https://www.markdownguide.org/basic-syntax/>








