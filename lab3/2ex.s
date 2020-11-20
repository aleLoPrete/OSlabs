	.file	"2ex.c"
	.text
	.section	.rodata
.LC0:
	.string	"\n%d->%d\n"
	.align 8
.LC1:
	.string	"\n Hi I am a leaf!\n My pid is= %d, my parent is %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movl	$0, -28(%rbp)
	movl	$2, -24(%rbp)
	movl	$1, -20(%rbp)
	movl	$0, -32(%rbp)
	movl	$0, -36(%rbp)
	jmp	.L2
.L7:
	call	fork@PLT
	movl	%eax, -28(%rbp)
	cmpl	$0, -28(%rbp)
	jne	.L3
	addl	$1, -32(%rbp)
.L3:
	cmpl	$0, -28(%rbp)
	je	.L4
	call	getpid@PLT
	movl	%eax, %esi
	movq	stdout(%rip), %rax
	movl	-28(%rbp), %edx
	movl	%edx, %ecx
	movl	%esi, %edx
	leaq	.LC0(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	call	fork@PLT
	movl	%eax, -28(%rbp)
	cmpl	$0, -28(%rbp)
	jne	.L5
	addl	$1, -32(%rbp)
.L5:
	cmpl	$0, -28(%rbp)
	je	.L4
	call	getpid@PLT
	movl	%eax, %esi
	movq	stdout(%rip), %rax
	movl	-28(%rbp), %edx
	movl	%edx, %ecx
	movl	%esi, %edx
	leaq	.LC0(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	jmp	.L6
.L4:
	addl	$1, -36(%rbp)
.L2:
	movl	-36(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L7
.L6:
	cmpl	$1, -32(%rbp)
	jle	.L8
	call	getppid@PLT
	movl	%eax, %ebx
	call	getpid@PLT
	movl	%eax, %edx
	movq	stdout(%rip), %rax
	movl	%ebx, %ecx
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
.L8:
	movl	$30, %edi
	call	sleep@PLT
	call	getpid@PLT
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
