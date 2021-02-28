	.file	"mergesort.cpp"
	.text
	.globl	_Z9mergesortPiS_ii
	.type	_Z9mergesortPiS_ii, @function
_Z9mergesortPiS_ii:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -52(%rbp)
	movl	%ecx, -56(%rbp)
	movl	-52(%rbp), %eax
	cmpl	-56(%rbp), %eax
	jge	.L10
	movl	-56(%rbp), %eax
	subl	-52(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, %edx
	movl	-52(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %ecx
	movl	-52(%rbp), %edx
	movq	-48(%rbp), %rsi
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_Z9mergesortPiS_ii
	movl	-4(%rbp), %eax
	leal	1(%rax), %edi
	movl	-56(%rbp), %edx
	movq	-48(%rbp), %rsi
	movq	-40(%rbp), %rax
	movl	%edx, %ecx
	movl	%edi, %edx
	movq	%rax, %rdi
	call	_Z9mergesortPiS_ii
	movl	-52(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	movl	-52(%rbp), %eax
	movl	%eax, -12(%rbp)
.L7:
	movl	-12(%rbp), %eax
	cmpl	-56(%rbp), %eax
	jg	.L3
	movl	-20(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jg	.L4
	movl	-16(%rbp), %eax
	cmpl	-56(%rbp), %eax
	jg	.L5
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	-40(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jg	.L4
.L5:
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	-12(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-48(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	addl	$1, -20(%rbp)
	jmp	.L6
.L4:
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	-12(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-48(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	addl	$1, -16(%rbp)
.L6:
	addl	$1, -12(%rbp)
	jmp	.L7
.L3:
	movl	-52(%rbp), %eax
	movl	%eax, -8(%rbp)
.L9:
	movl	-8(%rbp), %eax
	cmpl	-56(%rbp), %eax
	jg	.L10
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-40(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	addl	$1, -8(%rbp)
	jmp	.L9
.L10:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z9mergesortPiS_ii, .-_Z9mergesortPiS_ii
	.ident	"GCC: (Ubuntu 8.3.0-6ubuntu1) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
