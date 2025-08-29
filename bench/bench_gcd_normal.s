	.file	"bench_gcd.c"
	.text
	.globl	ar_gcdu
	.type	ar_gcdu, @function
ar_gcdu:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	jmp	.L2
.L3:
	movq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	divq	-32(%rbp)
	movq	%rdx, -32(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
.L2:
	cmpq	$0, -32(%rbp)
	jne	.L3
	movq	-24(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	ar_gcdu, .-ar_gcdu
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$3, %esi
	movl	$15, %edi
	call	ar_gcdu
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.1.1 20250425"
	.section	.note.GNU-stack,"",@progbits
