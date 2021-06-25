<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/jump_label.h>
#समावेश <यंत्र/unwind_hपूर्णांकs.h>
#समावेश <यंत्र/cpufeatures.h>
#समावेश <यंत्र/page_types.h>
#समावेश <यंत्र/percpu.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/processor-flags.h>

/*

 x86 function call convention, 64-bit:
 -------------------------------------
  arguments           |  callee-saved      | extra caller-saved | वापस
 [callee-clobbered]   |                    | [callee-clobbered] |
 ---------------------------------------------------------------------------
 rdi rsi rdx rcx r8-9 | rbx rbp [*] r12-15 | r10-11             | rax, rdx [**]

 ( rsp is obviously invariant across normal function calls. (gcc can 'merge'
   functions when it sees tail-call optimization possibilities) rflags is
   clobbered. Leftover arguments are passed over the stack frame.)

 [*]  In the frame-poपूर्णांकers हाल rbp is fixed to the stack frame.

 [**] क्रम काष्ठा वापस values wider than 64 bits the वापस convention is a
      bit more complex: up to 128 bits width we वापस small काष्ठाures
      straight in rax, rdx. For काष्ठाures larger than that (3 words or
      larger) the caller माला_दो a poपूर्णांकer to an on-stack वापस काष्ठा
      [allocated in the caller's stack frame] पूर्णांकo the first argument - i.e.
      पूर्णांकo rdi. All other arguments shअगरt up by one in this हाल.
      Fortunately this हाल is rare in the kernel.

For 32-bit we have the following conventions - kernel is built with
-mregparm=3 and -freg-काष्ठा-वापस:

 x86 function calling convention, 32-bit:
 ----------------------------------------
  arguments         | callee-saved        | extra caller-saved | वापस
 [callee-clobbered] |                     | [callee-clobbered] |
 -------------------------------------------------------------------------
 eax edx ecx        | ebx edi esi ebp [*] | <none>             | eax, edx [**]

 ( here too esp is obviously invariant across normal function calls. eflags
   is clobbered. Leftover arguments are passed over the stack frame. )

 [*]  In the frame-poपूर्णांकers हाल ebp is fixed to the stack frame.

 [**] We build with -freg-काष्ठा-वापस, which on 32-bit means similar
      semantics as on 64-bit: edx can be used क्रम a second वापस value
      (i.e. covering पूर्णांकeger and काष्ठाure sizes up to 64 bits) - after that
      it माला_लो more complex and more expensive: 3-word or larger काष्ठा वापसs
      get करोne in the caller's frame and the poपूर्णांकer to the वापस काष्ठा goes
      पूर्णांकo regparm0, i.e. eax - the other arguments shअगरt up and the
      function's रेजिस्टर parameters degenerate to regparm=2 in essence.

*/

#अगर_घोषित CONFIG_X86_64

/*
 * 64-bit प्रणाली call stack frame layout defines and helpers,
 * क्रम assembly code:
 */

/* The layout क्रमms the "struct pt_regs" on the stack: */
/*
 * C ABI says these regs are callee-preserved. They aren't saved on kernel entry
 * unless syscall needs a complete, fully filled "struct pt_regs".
 */
#घोषणा R15		0*8
#घोषणा R14		1*8
#घोषणा R13		2*8
#घोषणा R12		3*8
#घोषणा RBP		4*8
#घोषणा RBX		5*8
/* These regs are callee-clobbered. Always saved on kernel entry. */
#घोषणा R11		6*8
#घोषणा R10		7*8
#घोषणा R9		8*8
#घोषणा R8		9*8
#घोषणा RAX		10*8
#घोषणा RCX		11*8
#घोषणा RDX		12*8
#घोषणा RSI		13*8
#घोषणा RDI		14*8
/*
 * On syscall entry, this is syscall#. On CPU exception, this is error code.
 * On hw पूर्णांकerrupt, it's IRQ number:
 */
#घोषणा ORIG_RAX	15*8
/* Return frame क्रम iretq */
#घोषणा RIP		16*8
#घोषणा CS		17*8
#घोषणा EFLAGS		18*8
#घोषणा RSP		19*8
#घोषणा SS		20*8

#घोषणा SIZखातापूर्ण_PTREGS	21*8

.macro PUSH_AND_CLEAR_REGS rdx=%rdx rax=%rax save_ret=0
	.अगर \save_ret
	pushq	%rsi		/* pt_regs->si */
	movq	8(%rsp), %rsi	/* temporarily store the वापस address in %rsi */
	movq	%rdi, 8(%rsp)	/* pt_regs->di (overwriting original वापस address) */
	.अन्यथा
	pushq   %rdi		/* pt_regs->di */
	pushq   %rsi		/* pt_regs->si */
	.endअगर
	pushq	\लdx		/* pt_regs->dx */
	pushq   %rcx		/* pt_regs->cx */
	pushq   \लax		/* pt_regs->ax */
	pushq   %r8		/* pt_regs->r8 */
	pushq   %r9		/* pt_regs->r9 */
	pushq   %r10		/* pt_regs->r10 */
	pushq   %r11		/* pt_regs->r11 */
	pushq	%rbx		/* pt_regs->rbx */
	pushq	%rbp		/* pt_regs->rbp */
	pushq	%r12		/* pt_regs->r12 */
	pushq	%r13		/* pt_regs->r13 */
	pushq	%r14		/* pt_regs->r14 */
	pushq	%r15		/* pt_regs->r15 */
	UNWIND_HINT_REGS

	.अगर \save_ret
	pushq	%rsi		/* वापस address on top of stack */
	.endअगर

	/*
	 * Sanitize रेजिस्टरs of values that a speculation attack might
	 * otherwise want to exploit. The lower रेजिस्टरs are likely clobbered
	 * well beक्रमe they could be put to use in a speculative execution
	 * gadget.
	 */
	xorl	%edx,  %edx	/* nospec dx  */
	xorl	%ecx,  %ecx	/* nospec cx  */
	xorl	%r8d,  %r8d	/* nospec r8  */
	xorl	%r9d,  %r9d	/* nospec r9  */
	xorl	%r10d, %r10d	/* nospec r10 */
	xorl	%r11d, %r11d	/* nospec r11 */
	xorl	%ebx,  %ebx	/* nospec rbx */
	xorl	%ebp,  %ebp	/* nospec rbp */
	xorl	%r12d, %r12d	/* nospec r12 */
	xorl	%r13d, %r13d	/* nospec r13 */
	xorl	%r14d, %r14d	/* nospec r14 */
	xorl	%r15d, %r15d	/* nospec r15 */

.endm

.macro POP_REGS pop_rdi=1 skip_r11rcx=0
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbp
	popq %rbx
	.अगर \skip_r11rcx
	popq %rsi
	.अन्यथा
	popq %r11
	.endअगर
	popq %r10
	popq %r9
	popq %r8
	popq %rax
	.अगर \skip_r11rcx
	popq %rsi
	.अन्यथा
	popq %rcx
	.endअगर
	popq %rdx
	popq %rsi
	.अगर \pop_rdi
	popq %rdi
	.endअगर
.endm

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION

/*
 * PAGE_TABLE_ISOLATION PGDs are 8k.  Flip bit 12 to चयन between the two
 * halves:
 */
#घोषणा PTI_USER_PGTABLE_BIT		PAGE_SHIFT
#घोषणा PTI_USER_PGTABLE_MASK		(1 << PTI_USER_PGTABLE_BIT)
#घोषणा PTI_USER_PCID_BIT		X86_CR3_PTI_PCID_USER_BIT
#घोषणा PTI_USER_PCID_MASK		(1 << PTI_USER_PCID_BIT)
#घोषणा PTI_USER_PGTABLE_AND_PCID_MASK  (PTI_USER_PCID_MASK | PTI_USER_PGTABLE_MASK)

.macro SET_NOFLUSH_BIT	reg:req
	bts	$X86_CR3_PCID_NOFLUSH_BIT, \लeg
.endm

.macro ADJUST_KERNEL_CR3 reg:req
	ALTERNATIVE "", "SET_NOFLUSH_BIT \reg", X86_FEATURE_PCID
	/* Clear PCID and "PAGE_TABLE_ISOLATION bit", poपूर्णांक CR3 at kernel pagetables: */
	andq    $(~PTI_USER_PGTABLE_AND_PCID_MASK), \लeg
.endm

.macro SWITCH_TO_KERNEL_CR3 scratch_reg:req
	ALTERNATIVE "jmp .Lend_\@", "", X86_FEATURE_PTI
	mov	%cr3, \scratch_reg
	ADJUST_KERNEL_CR3 \scratch_reg
	mov	\scratch_reg, %cr3
.Lend_\@:
.endm

#घोषणा THIS_CPU_user_pcid_flush_mask   \
	PER_CPU_VAR(cpu_tlbstate) + TLB_STATE_user_pcid_flush_mask

.macro SWITCH_TO_USER_CR3_NOSTACK scratch_reg:req scratch_reg2:req
	ALTERNATIVE "jmp .Lend_\@", "", X86_FEATURE_PTI
	mov	%cr3, \scratch_reg

	ALTERNATIVE "jmp .Lwrcr3_\@", "", X86_FEATURE_PCID

	/*
	 * Test अगर the ASID needs a flush.
	 */
	movq	\scratch_reg, \scratch_reg2
	andq	$(0x7FF), \scratch_reg		/* mask ASID */
	bt	\scratch_reg, THIS_CPU_user_pcid_flush_mask
	jnc	.Lnoflush_\@

	/* Flush needed, clear the bit */
	btr	\scratch_reg, THIS_CPU_user_pcid_flush_mask
	movq	\scratch_reg2, \scratch_reg
	jmp	.Lwrcr3_pcid_\@

.Lnoflush_\@:
	movq	\scratch_reg2, \scratch_reg
	SET_NOFLUSH_BIT \scratch_reg

.Lwrcr3_pcid_\@:
	/* Flip the ASID to the user version */
	orq	$(PTI_USER_PCID_MASK), \scratch_reg

.Lwrcr3_\@:
	/* Flip the PGD to the user version */
	orq     $(PTI_USER_PGTABLE_MASK), \scratch_reg
	mov	\scratch_reg, %cr3
.Lend_\@:
.endm

.macro SWITCH_TO_USER_CR3_STACK	scratch_reg:req
	pushq	%rax
	SWITCH_TO_USER_CR3_NOSTACK scratch_reg=\scratch_reg scratch_reg2=%rax
	popq	%rax
.endm

.macro SAVE_AND_SWITCH_TO_KERNEL_CR3 scratch_reg:req save_reg:req
	ALTERNATIVE "jmp .Ldone_\@", "", X86_FEATURE_PTI
	movq	%cr3, \scratch_reg
	movq	\scratch_reg, \save_reg
	/*
	 * Test the user pagetable bit. If set, then the user page tables
	 * are active. If clear CR3 alपढ़ोy has the kernel page table
	 * active.
	 */
	bt	$PTI_USER_PGTABLE_BIT, \scratch_reg
	jnc	.Lकरोne_\@

	ADJUST_KERNEL_CR3 \scratch_reg
	movq	\scratch_reg, %cr3

.Lकरोne_\@:
.endm

.macro RESTORE_CR3 scratch_reg:req save_reg:req
	ALTERNATIVE "jmp .Lend_\@", "", X86_FEATURE_PTI

	ALTERNATIVE "jmp .Lwrcr3_\@", "", X86_FEATURE_PCID

	/*
	 * KERNEL pages can always resume with NOFLUSH as we करो
	 * explicit flushes.
	 */
	bt	$PTI_USER_PGTABLE_BIT, \save_reg
	jnc	.Lnoflush_\@

	/*
	 * Check अगर there's a pending flush for the user ASID we're
	 * about to set.
	 */
	movq	\save_reg, \scratch_reg
	andq	$(0x7FF), \scratch_reg
	bt	\scratch_reg, THIS_CPU_user_pcid_flush_mask
	jnc	.Lnoflush_\@

	btr	\scratch_reg, THIS_CPU_user_pcid_flush_mask
	jmp	.Lwrcr3_\@

.Lnoflush_\@:
	SET_NOFLUSH_BIT \save_reg

.Lwrcr3_\@:
	/*
	 * The CR3 ग_लिखो could be aव्योमed when not changing its value,
	 * but would require a CR3 पढ़ो *and* a scratch रेजिस्टर.
	 */
	movq	\save_reg, %cr3
.Lend_\@:
.endm

#अन्यथा /* CONFIG_PAGE_TABLE_ISOLATION=n: */

.macro SWITCH_TO_KERNEL_CR3 scratch_reg:req
.endm
.macro SWITCH_TO_USER_CR3_NOSTACK scratch_reg:req scratch_reg2:req
.endm
.macro SWITCH_TO_USER_CR3_STACK scratch_reg:req
.endm
.macro SAVE_AND_SWITCH_TO_KERNEL_CR3 scratch_reg:req save_reg:req
.endm
.macro RESTORE_CR3 scratch_reg:req save_reg:req
.endm

#पूर्ण_अगर

/*
 * Mitigate Spectre v1 क्रम conditional swapgs code paths.
 *
 * FENCE_SWAPGS_USER_ENTRY is used in the user entry swapgs code path, to
 * prevent a speculative swapgs when coming from kernel space.
 *
 * FENCE_SWAPGS_KERNEL_ENTRY is used in the kernel entry non-swapgs code path,
 * to prevent the swapgs from getting speculatively skipped when coming from
 * user space.
 */
.macro FENCE_SWAPGS_USER_ENTRY
	ALTERNATIVE "", "lfence", X86_FEATURE_FENCE_SWAPGS_USER
.endm
.macro FENCE_SWAPGS_KERNEL_ENTRY
	ALTERNATIVE "", "lfence", X86_FEATURE_FENCE_SWAPGS_KERNEL
.endm

.macro STACKLEAK_ERASE_NOCLOBBER
#अगर_घोषित CONFIG_GCC_PLUGIN_STACKLEAK
	PUSH_AND_CLEAR_REGS
	call stackleak_erase
	POP_REGS
#पूर्ण_अगर
.endm

.macro SAVE_AND_SET_GSBASE scratch_reg:req save_reg:req
	rdgsbase \save_reg
	GET_PERCPU_BASE \scratch_reg
	wrgsbase \scratch_reg
.endm

#अन्यथा /* CONFIG_X86_64 */
# undef		UNWIND_HINT_IRET_REGS
# define	UNWIND_HINT_IRET_REGS
#पूर्ण_अगर /* !CONFIG_X86_64 */

.macro STACKLEAK_ERASE
#अगर_घोषित CONFIG_GCC_PLUGIN_STACKLEAK
	call stackleak_erase
#पूर्ण_अगर
.endm

#अगर_घोषित CONFIG_SMP

/*
 * CPU/node NR is loaded from the limit (size) field of a special segment
 * descriptor entry in GDT.
 */
.macro LOAD_CPU_AND_NODE_SEG_LIMIT reg:req
	movq	$__CPUNODE_SEG, \लeg
	lsl	\लeg, \लeg
.endm

/*
 * Fetch the per-CPU GSBASE value क्रम this processor and put it in @reg.
 * We normally use %gs क्रम accessing per-CPU data, but we are setting up
 * %gs here and obviously can not use %gs itself to access per-CPU data.
 *
 * Do not use RDPID, because KVM loads guest's TSC_AUX on vm-entry and
 * may not restore the host's value until the CPU वापसs to userspace.
 * Thus the kernel would consume a guest's TSC_AUX अगर an NMI arrives
 * जबतक running KVM's run loop.
 */
.macro GET_PERCPU_BASE reg:req
	LOAD_CPU_AND_NODE_SEG_LIMIT \लeg
	andq	$VDSO_CPUNODE_MASK, \लeg
	movq	__per_cpu_offset(, \लeg, 8), \लeg
.endm

#अन्यथा

.macro GET_PERCPU_BASE reg:req
	movq	pcpu_unit_offsets(%rip), \लeg
.endm

#पूर्ण_अगर /* CONFIG_SMP */
