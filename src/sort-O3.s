	.file	"sort.c"
	.text
	.p2align 4
	.globl	sort
	.type	sort, @function
sort:
.LFB0:
	.cfi_startproc
	endbr64
	testl	%edx, %edx
	jle	.L1
	leaq	15(%rsi), %rax
	leal	-1(%rdx), %r8d
	subq	%rdi, %rax
	cmpq	$30, %rax
	jbe	.L3
	cmpl	$3, %r8d
	jbe	.L3
	movl	%edx, %ecx
	xorl	%eax, %eax
	shrl	%ecx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L4:
	movdqu	(%rdi,%rax), %xmm2
	movups	%xmm2, (%rsi,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L4
	movl	%edx, %eax
	andl	$-2, %eax
	testb	$1, %dl
	je	.L7
	movq	(%rdi,%rax,8), %rcx
	movq	%rcx, (%rsi,%rax,8)
.L7:
	leaq	8(%rsi,%r8,8), %r8
	xorl	%r9d, %r9d
	.p2align 4,,10
	.p2align 3
.L8:
	movq	%rsi, %rax
	.p2align 4,,10
	.p2align 3
.L10:
	movq	(%rax), %rdi
	movq	8(%rax), %rcx
	cmpq	%rcx, %rdi
	jle	.L9
	movq	%rcx, %xmm0
	movq	%rdi, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movups	%xmm0, (%rax)
.L9:
	addq	$8, %rax
	cmpq	%r8, %rax
	jne	.L10
	addl	$1, %r9d
	cmpl	%r9d, %edx
	jne	.L8
.L1:
	ret
.L3:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L6:
	movq	(%rdi,%rax,8), %rcx
	movq	%rcx, (%rsi,%rax,8)
	movq	%rax, %rcx
	addq	$1, %rax
	cmpq	%r8, %rcx
	jne	.L6
	jmp	.L7
	.cfi_endproc
.LFE0:
	.size	sort, .-sort
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
