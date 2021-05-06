### Memory Management Unit (MMU)
Author: Gabriel Hofer  
Date: May 2, 2021  

### The Purpose of Virtual Memory 
Operating System support virtual memory for the following reasons: 
* Applications can have their own separate or isolated chunk of memory that can't be accessed by other applications.
applications.
* Memory isolation increases security 
* It is possible to create arbitrarily large memory addresses that may or may not exist in actual memory

### What is Segmentation and Paging? 
In order for different processes to have their own memory, memory needs to be partitioned or divided into smaller pieces. This is called **segmentation**.
The range of virtual addresses is partitioned/divided into smaller chunks called **pages**.
Physical memory is divided into smaller pieces called **frames**.
Moverover, an address in virtual memory belongs to a unique **page**, and this address
also has an offset in that page that tells us where the address is relative to the beginning
of the page.

### What is a page table? 
Essentially, a page table is used to map virtual addresses to physical addresses. 

### MIT OpenCourseWare slides
This project's simulation of virtual memory and paging was implemented based
on the information presented in MIT's OpenCoursWare [slides](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-004-computation-structures-spring-2017/c16/c16s1/).

> There are three architectural parameters that characterize a virtual memory system and hence the architecture of the MMU.

> P is the number of address bits used for the page offset in both virtual and physical addresses. V is the number of address bits used for the virtual page number. And M is the number of address bits used for the physical page number. All the other parameters, listed on the right, are derived from these three parameters.

```
/********************************************//**
 *    8 bits in the page offset 
 *    4 bits for virtual pages
 *    3 bits for physical pages
 * 
 *    based on the example in the
 *    MIT OpenCourseWare slides
 ***********************************************/
const int p = 8;
const int v = 4;
const int m = 3;
```
As we can see in the code, p, v and m are constant integers. So every time that the program runs, p has the vale of 8, v has the value of 4, and m has the value of 3. This can be changed in the future to let the user choose values for these variables, but I kept them constant to make explaining the implementation easier.

![page\_map\_arithmetic](https://github.com/hofergabriel/MMU/blob/main/images/page_map_arithmetic.png)

Based on the slide above we calculate the following for our simulation: 

* (v+p) = 12 bits in virtual address
* (m+p) = 11 bits in physical address
* 2^v = 16 virtual pages
* 2^m = 8 physical pages
* 2^p = 256 bytes per physical page
* 2^(v+p) = 4096 bytes in virtual memory
* 2^(v+m) = 2048 bytes in physical memory

This slide illustrates the size of our page map, virtual memory, and physical memory.

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








