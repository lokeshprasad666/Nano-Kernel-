#include "screen.h"
#include "scheduler.h"

void prime_generator ( int );

void system_monitor();
void memory_manager();
void task_processor();
void io_handler();

void kernel_main()
{
	process_t p1, p2, p3, p4;

	screen_init();	
	scheduler_init();
	
	print("=== NANO KERNEL v1.0 ===");
	println();
	print("Initializing system processes...");
	println();
	
	process_create((int*)system_monitor, &p1);
	process_create((int*)memory_manager, &p2);
	process_create((int*)task_processor, &p3);
	process_create((int*)io_handler, &p4);
	
	print("System ready. Starting multitasking demo...");
	println();
	println();
	
	prime_generator(15);
	
	println();
	print("Entering multitasking mode...");
	println();
	
	while (1) {};
}

void system_monitor () {
	print("System Monitor: ");
	
	while (1) {
		asm volatile("mov $0x1001, %eax");
	}
}

void memory_manager () {
	print("Memory Manager: ");
	
	while (1) {
		asm volatile("mov $0x2002, %eax");
	}
}

void task_processor () {
	print("Task Processor: ");
	
	while (1) {
		asm volatile("mov $0x3003, %eax");
	}
}

void io_handler () {
	print("I/O Handler: ");
	
	while (1) {
		asm volatile("mov $0x4004, %eax");
	}
}

void prime_generator(int n) {
	int count = 0;
	int num = 2;
	
	print("Prime sequence: ");
	
	while (count < n) {
		int is_prime = 1;
		
		for (int i = 2; i * i <= num; i++) {
			if (num % i == 0) {
				is_prime = 0;
				break;
			}
		}
		
		if (is_prime) {
			printi(num);
			print(" ");
			count++;
		}
		num++;
	}
	
	println();
	return;
}

void interrupt_handler (int interrupt_number) {
	// println();
	// print( "Interrupt received ");
	// printi(interrupt_number);

	return;
}
