	.file	"bench_gcd.c"
	.text
	.p2align 4
	.globl	ar_gcdu
	.type	ar_gcdu, @function
ar_gcdu:
.LFB8:
	.cfi_startproc
	movq	%rdi, %rax
	movq	%rsi, %rdx
	testq	%rsi, %rsi
	je	.L4
	.p2align 4
	.p2align 4
	.p2align 3
.L3:
	movq	%rdx, %rcx
	xorl	%edx, %edx
	divq	%rcx
	movq	%rcx, %rax
	testq	%rdx, %rdx
	jne	.L3
	movq	%rcx, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	movq	%rdi, %rcx
	movq	%rcx, %rax
	ret
	.cfi_endproc
.LFE8:
	.size	ar_gcdu, .-ar_gcdu
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	movl	$3, %eax
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.1.1 20250425"
	.section	.note.GNU-stack,"",@progbits
