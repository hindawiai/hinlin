<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PARAVIRT_TYPES_H
#घोषणा _ASM_X86_PARAVIRT_TYPES_H

/* Biपंचांगask of what can be clobbered: usually at least eax. */
#घोषणा CLBR_EAX  (1 << 0)
#घोषणा CLBR_ECX  (1 << 1)
#घोषणा CLBR_EDX  (1 << 2)
#घोषणा CLBR_EDI  (1 << 3)

#अगर_घोषित CONFIG_X86_32
/* CLBR_ANY should match all regs platक्रमm has. For i386, that's just it */
#घोषणा CLBR_ANY  ((1 << 4) - 1)

#घोषणा CLBR_ARG_REGS	(CLBR_EAX | CLBR_EDX | CLBR_ECX)
#घोषणा CLBR_RET_REG	(CLBR_EAX | CLBR_EDX)
#अन्यथा
#घोषणा CLBR_RAX  CLBR_EAX
#घोषणा CLBR_RCX  CLBR_ECX
#घोषणा CLBR_RDX  CLBR_EDX
#घोषणा CLBR_RDI  CLBR_EDI
#घोषणा CLBR_RSI  (1 << 4)
#घोषणा CLBR_R8   (1 << 5)
#घोषणा CLBR_R9   (1 << 6)
#घोषणा CLBR_R10  (1 << 7)
#घोषणा CLBR_R11  (1 << 8)

#घोषणा CLBR_ANY  ((1 << 9) - 1)

#घोषणा CLBR_ARG_REGS	(CLBR_RDI | CLBR_RSI | CLBR_RDX | \
			 CLBR_RCX | CLBR_R8 | CLBR_R9)
#घोषणा CLBR_RET_REG	(CLBR_RAX)

#पूर्ण_अगर /* X86_64 */

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/desc_defs.h>
#समावेश <यंत्र/pgtable_types.h>
#समावेश <यंत्र/nospec-branch.h>

काष्ठा page;
काष्ठा thपढ़ो_काष्ठा;
काष्ठा desc_ptr;
काष्ठा tss_काष्ठा;
काष्ठा mm_काष्ठा;
काष्ठा desc_काष्ठा;
काष्ठा task_काष्ठा;
काष्ठा cpumask;
काष्ठा flush_tlb_info;
काष्ठा mmu_gather;
काष्ठा vm_area_काष्ठा;

/*
 * Wrapper type क्रम poपूर्णांकers to code which uses the non-standard
 * calling convention.  See PV_CALL_SAVE_REGS_THUNK below.
 */
काष्ठा paravirt_callee_save अणु
	व्योम *func;
पूर्ण;

/* general info */
काष्ठा pv_info अणु
#अगर_घोषित CONFIG_PARAVIRT_XXL
	u16 extra_user_64bit_cs;  /* __USER_CS अगर none */
#पूर्ण_अगर

	स्थिर अक्षर *name;
पूर्ण;

#अगर_घोषित CONFIG_PARAVIRT_XXL
काष्ठा pv_lazy_ops अणु
	/* Set deferred update mode, used क्रम batching operations. */
	व्योम (*enter)(व्योम);
	व्योम (*leave)(व्योम);
	व्योम (*flush)(व्योम);
पूर्ण __no_अक्रमomize_layout;
#पूर्ण_अगर

काष्ठा pv_cpu_ops अणु
	/* hooks क्रम various privileged inकाष्ठाions */
	व्योम (*io_delay)(व्योम);

#अगर_घोषित CONFIG_PARAVIRT_XXL
	अचिन्हित दीर्घ (*get_debugreg)(पूर्णांक regno);
	व्योम (*set_debugreg)(पूर्णांक regno, अचिन्हित दीर्घ value);

	अचिन्हित दीर्घ (*पढ़ो_cr0)(व्योम);
	व्योम (*ग_लिखो_cr0)(अचिन्हित दीर्घ);

	व्योम (*ग_लिखो_cr4)(अचिन्हित दीर्घ);

	/* Segment descriptor handling */
	व्योम (*load_tr_desc)(व्योम);
	व्योम (*load_gdt)(स्थिर काष्ठा desc_ptr *);
	व्योम (*load_idt)(स्थिर काष्ठा desc_ptr *);
	व्योम (*set_ldt)(स्थिर व्योम *desc, अचिन्हित entries);
	अचिन्हित दीर्घ (*store_tr)(व्योम);
	व्योम (*load_tls)(काष्ठा thपढ़ो_काष्ठा *t, अचिन्हित पूर्णांक cpu);
	व्योम (*load_gs_index)(अचिन्हित पूर्णांक idx);
	व्योम (*ग_लिखो_ldt_entry)(काष्ठा desc_काष्ठा *ldt, पूर्णांक entrynum,
				स्थिर व्योम *desc);
	व्योम (*ग_लिखो_gdt_entry)(काष्ठा desc_काष्ठा *,
				पूर्णांक entrynum, स्थिर व्योम *desc, पूर्णांक size);
	व्योम (*ग_लिखो_idt_entry)(gate_desc *,
				पूर्णांक entrynum, स्थिर gate_desc *gate);
	व्योम (*alloc_ldt)(काष्ठा desc_काष्ठा *ldt, अचिन्हित entries);
	व्योम (*मुक्त_ldt)(काष्ठा desc_काष्ठा *ldt, अचिन्हित entries);

	व्योम (*load_sp0)(अचिन्हित दीर्घ sp0);

#अगर_घोषित CONFIG_X86_IOPL_IOPERM
	व्योम (*invalidate_io_biपंचांगap)(व्योम);
	व्योम (*update_io_biपंचांगap)(व्योम);
#पूर्ण_अगर

	व्योम (*wbinvd)(व्योम);

	/* cpuid emulation, mostly so that caps bits can be disabled */
	व्योम (*cpuid)(अचिन्हित पूर्णांक *eax, अचिन्हित पूर्णांक *ebx,
		      अचिन्हित पूर्णांक *ecx, अचिन्हित पूर्णांक *edx);

	/* Unsafe MSR operations.  These will warn or panic on failure. */
	u64 (*पढ़ो_msr)(अचिन्हित पूर्णांक msr);
	व्योम (*ग_लिखो_msr)(अचिन्हित पूर्णांक msr, अचिन्हित low, अचिन्हित high);

	/*
	 * Safe MSR operations.
	 * पढ़ो sets err to 0 or -EIO.  ग_लिखो वापसs 0 or -EIO.
	 */
	u64 (*पढ़ो_msr_safe)(अचिन्हित पूर्णांक msr, पूर्णांक *err);
	पूर्णांक (*ग_लिखो_msr_safe)(अचिन्हित पूर्णांक msr, अचिन्हित low, अचिन्हित high);

	u64 (*पढ़ो_pmc)(पूर्णांक counter);

	व्योम (*start_context_चयन)(काष्ठा task_काष्ठा *prev);
	व्योम (*end_context_चयन)(काष्ठा task_काष्ठा *next);
#पूर्ण_अगर
पूर्ण __no_अक्रमomize_layout;

काष्ठा pv_irq_ops अणु
#अगर_घोषित CONFIG_PARAVIRT_XXL
	/*
	 * Get/set पूर्णांकerrupt state.  save_fl is expected to use X86_EFLAGS_IF;
	 * all other bits वापसed from save_fl are undefined.
	 *
	 * NOTE: These functions callers expect the callee to preserve
	 * more रेजिस्टरs than the standard C calling convention.
	 */
	काष्ठा paravirt_callee_save save_fl;
	काष्ठा paravirt_callee_save irq_disable;
	काष्ठा paravirt_callee_save irq_enable;

	व्योम (*safe_halt)(व्योम);
	व्योम (*halt)(व्योम);
#पूर्ण_अगर
पूर्ण __no_अक्रमomize_layout;

काष्ठा pv_mmu_ops अणु
	/* TLB operations */
	व्योम (*flush_tlb_user)(व्योम);
	व्योम (*flush_tlb_kernel)(व्योम);
	व्योम (*flush_tlb_one_user)(अचिन्हित दीर्घ addr);
	व्योम (*flush_tlb_multi)(स्थिर काष्ठा cpumask *cpus,
				स्थिर काष्ठा flush_tlb_info *info);

	व्योम (*tlb_हटाओ_table)(काष्ठा mmu_gather *tlb, व्योम *table);

	/* Hook क्रम पूर्णांकercepting the deकाष्ठाion of an mm_काष्ठा. */
	व्योम (*निकास_mmap)(काष्ठा mm_काष्ठा *mm);

#अगर_घोषित CONFIG_PARAVIRT_XXL
	काष्ठा paravirt_callee_save पढ़ो_cr2;
	व्योम (*ग_लिखो_cr2)(अचिन्हित दीर्घ);

	अचिन्हित दीर्घ (*पढ़ो_cr3)(व्योम);
	व्योम (*ग_लिखो_cr3)(अचिन्हित दीर्घ);

	/* Hooks क्रम पूर्णांकercepting the creation/use of an mm_काष्ठा. */
	व्योम (*activate_mm)(काष्ठा mm_काष्ठा *prev,
			    काष्ठा mm_काष्ठा *next);
	व्योम (*dup_mmap)(काष्ठा mm_काष्ठा *oldmm,
			 काष्ठा mm_काष्ठा *mm);

	/* Hooks क्रम allocating and मुक्तing a pagetable top-level */
	पूर्णांक  (*pgd_alloc)(काष्ठा mm_काष्ठा *mm);
	व्योम (*pgd_मुक्त)(काष्ठा mm_काष्ठा *mm, pgd_t *pgd);

	/*
	 * Hooks क्रम allocating/releasing pagetable pages when they're
	 * attached to a pagetable
	 */
	व्योम (*alloc_pte)(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn);
	व्योम (*alloc_pmd)(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn);
	व्योम (*alloc_pud)(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn);
	व्योम (*alloc_p4d)(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn);
	व्योम (*release_pte)(अचिन्हित दीर्घ pfn);
	व्योम (*release_pmd)(अचिन्हित दीर्घ pfn);
	व्योम (*release_pud)(अचिन्हित दीर्घ pfn);
	व्योम (*release_p4d)(अचिन्हित दीर्घ pfn);

	/* Pagetable manipulation functions */
	व्योम (*set_pte)(pte_t *ptep, pte_t pteval);
	व्योम (*set_pmd)(pmd_t *pmdp, pmd_t pmdval);

	pte_t (*ptep_modअगरy_prot_start)(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
					pte_t *ptep);
	व्योम (*ptep_modअगरy_prot_commit)(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
					pte_t *ptep, pte_t pte);

	काष्ठा paravirt_callee_save pte_val;
	काष्ठा paravirt_callee_save make_pte;

	काष्ठा paravirt_callee_save pgd_val;
	काष्ठा paravirt_callee_save make_pgd;

	व्योम (*set_pud)(pud_t *pudp, pud_t pudval);

	काष्ठा paravirt_callee_save pmd_val;
	काष्ठा paravirt_callee_save make_pmd;

	काष्ठा paravirt_callee_save pud_val;
	काष्ठा paravirt_callee_save make_pud;

	व्योम (*set_p4d)(p4d_t *p4dp, p4d_t p4dval);

#अगर CONFIG_PGTABLE_LEVELS >= 5
	काष्ठा paravirt_callee_save p4d_val;
	काष्ठा paravirt_callee_save make_p4d;

	व्योम (*set_pgd)(pgd_t *pgdp, pgd_t pgdval);
#पूर्ण_अगर	/* CONFIG_PGTABLE_LEVELS >= 5 */

	काष्ठा pv_lazy_ops lazy_mode;

	/* करोm0 ops */

	/* Someबार the physical address is a pfn, and someबार its
	   an mfn.  We can tell which is which from the index. */
	व्योम (*set_fixmap)(अचिन्हित /* क्रमागत fixed_addresses */ idx,
			   phys_addr_t phys, pgprot_t flags);
#पूर्ण_अगर
पूर्ण __no_अक्रमomize_layout;

काष्ठा arch_spinlock;
#अगर_घोषित CONFIG_SMP
#समावेश <यंत्र/spinlock_types.h>
#पूर्ण_अगर

काष्ठा qspinlock;

काष्ठा pv_lock_ops अणु
	व्योम (*queued_spin_lock_slowpath)(काष्ठा qspinlock *lock, u32 val);
	काष्ठा paravirt_callee_save queued_spin_unlock;

	व्योम (*रुको)(u8 *ptr, u8 val);
	व्योम (*kick)(पूर्णांक cpu);

	काष्ठा paravirt_callee_save vcpu_is_preempted;
पूर्ण __no_अक्रमomize_layout;

/* This contains all the paravirt काष्ठाures: we get a convenient
 * number क्रम each function using the offset which we use to indicate
 * what to patch. */
काष्ठा paravirt_patch_ढाँचा अणु
	काष्ठा pv_cpu_ops	cpu;
	काष्ठा pv_irq_ops	irq;
	काष्ठा pv_mmu_ops	mmu;
	काष्ठा pv_lock_ops	lock;
पूर्ण __no_अक्रमomize_layout;

बाह्य काष्ठा pv_info pv_info;
बाह्य काष्ठा paravirt_patch_ढाँचा pv_ops;
बाह्य व्योम (*paravirt_iret)(व्योम);

#घोषणा PARAVIRT_PATCH(x)					\
	(दुरत्व(काष्ठा paravirt_patch_ढाँचा, x) / माप(व्योम *))

#घोषणा paravirt_type(op)				\
	[paravirt_typक्रमागत] "i" (PARAVIRT_PATCH(op)),	\
	[paravirt_opptr] "i" (&(pv_ops.op))
#घोषणा paravirt_clobber(clobber)		\
	[paravirt_clobber] "i" (clobber)

/*
 * Generate some code, and mark it as patchable by the
 * apply_paravirt() alternate inकाष्ठाion patcher.
 */
#घोषणा _paravirt_alt(insn_string, type, clobber)	\
	"771:\n\t" insn_string "\n" "772:\n"		\
	".pushsection .parainstructions,\"a\"\n"	\
	_ASM_ALIGN "\n"					\
	_ASM_PTR " 771b\n"				\
	"  .byte " type "\n"				\
	"  .byte 772b-771b\n"				\
	"  .short " clobber "\n"			\
	".popsection\n"

/* Generate patchable code, with the शेष यंत्र parameters. */
#घोषणा paravirt_alt(insn_string)					\
	_paravirt_alt(insn_string, "%c[paravirt_typenum]", "%c[paravirt_clobber]")

/* Simple inकाष्ठाion patching code. */
#घोषणा NATIVE_LABEL(a,x,b) "\n\t.globl " a #x "_" #b "\n" a #x "_" #b ":\n\t"

अचिन्हित पूर्णांक paravirt_patch(u8 type, व्योम *insn_buff, अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक len);

पूर्णांक paravirt_disable_iospace(व्योम);

/*
 * This generates an indirect call based on the operation type number.
 * The type number, computed in PARAVIRT_PATCH, is derived from the
 * offset पूर्णांकo the paravirt_patch_ढाँचा काष्ठाure, and can thereक्रमe be
 * मुक्तly converted back पूर्णांकo a काष्ठाure offset.
 */
#घोषणा PARAVIRT_CALL					\
	ANNOTATE_RETPOLINE_SAFE				\
	"call *%c[paravirt_opptr];"

/*
 * These macros are पूर्णांकended to wrap calls through one of the paravirt
 * ops काष्ठाs, so that they can be later identअगरied and patched at
 * runसमय.
 *
 * Normally, a call to a pv_op function is a simple indirect call:
 * (pv_op_काष्ठा.operations)(args...).
 *
 * Unक्रमtunately, this is a relatively slow operation क्रम modern CPUs,
 * because it cannot necessarily determine what the destination
 * address is.  In this हाल, the address is a runसमय स्थिरant, so at
 * the very least we can patch the call to e a simple direct call, or
 * ideally, patch an अंतरभूत implementation पूर्णांकo the callsite.  (Direct
 * calls are essentially मुक्त, because the call and वापस addresses
 * are completely predictable.)
 *
 * For i386, these macros rely on the standard gcc "regparm(3)" calling
 * convention, in which the first three arguments are placed in %eax,
 * %edx, %ecx (in that order), and the reमुख्यing arguments are placed
 * on the stack.  All caller-save रेजिस्टरs (eax,edx,ecx) are expected
 * to be modअगरied (either clobbered or used क्रम वापस values).
 * X86_64, on the other hand, alपढ़ोy specअगरies a रेजिस्टर-based calling
 * conventions, वापसing at %rax, with parameters going on %rdi, %rsi,
 * %rdx, and %rcx. Note that क्रम this reason, x86_64 करोes not need any
 * special handling क्रम dealing with 4 arguments, unlike i386.
 * However, x86_64 also have to clobber all caller saved रेजिस्टरs, which
 * unक्रमtunately, are quite a bit (r8 - r11)
 *
 * The call inकाष्ठाion itself is marked by placing its start address
 * and size पूर्णांकo the .parainकाष्ठाions section, so that
 * apply_paravirt() in arch/i386/kernel/alternative.c can करो the
 * appropriate patching under the control of the backend pv_init_ops
 * implementation.
 *
 * Unक्रमtunately there's no way to get gcc to generate the args setup
 * क्रम the call, and then allow the call itself to be generated by an
 * अंतरभूत यंत्र.  Because of this, we must करो the complete arg setup and
 * वापस value handling from within these macros.  This is fairly
 * cumbersome.
 *
 * There are 5 sets of PVOP_* macros क्रम dealing with 0-4 arguments.
 * It could be extended to more arguments, but there would be little
 * to be gained from that.  For each number of arguments, there are
 * the two VCALL and CALL variants क्रम व्योम and non-व्योम functions.
 *
 * When there is a वापस value, the invoker of the macro must specअगरy
 * the वापस type.  The macro then uses माप() on that type to
 * determine whether its a 32 or 64 bit value, and places the वापस
 * in the right रेजिस्टर(s) (just %eax क्रम 32-bit, and %edx:%eax क्रम
 * 64-bit). For x86_64 machines, it just वापसs at %rax regardless of
 * the वापस value size.
 *
 * 64-bit arguments are passed as a pair of adjacent 32-bit arguments
 * i386 also passes 64-bit arguments as a pair of adjacent 32-bit arguments
 * in low,high order
 *
 * Small काष्ठाures are passed and वापसed in रेजिस्टरs.  The macro
 * calling convention can't directly deal with this, so the wrapper
 * functions must करो this.
 *
 * These PVOP_* macros are only defined within this header.  This
 * means that all uses must be wrapped in अंतरभूत functions.  This also
 * makes sure the incoming and outgoing types are always correct.
 */
#अगर_घोषित CONFIG_X86_32
#घोषणा PVOP_CALL_ARGS							\
	अचिन्हित दीर्घ __eax = __eax, __edx = __edx, __ecx = __ecx;

#घोषणा PVOP_CALL_ARG1(x)		"a" ((अचिन्हित दीर्घ)(x))
#घोषणा PVOP_CALL_ARG2(x)		"d" ((अचिन्हित दीर्घ)(x))
#घोषणा PVOP_CALL_ARG3(x)		"c" ((अचिन्हित दीर्घ)(x))

#घोषणा PVOP_VCALL_CLOBBERS		"=a" (__eax), "=d" (__edx),	\
					"=c" (__ecx)
#घोषणा PVOP_CALL_CLOBBERS		PVOP_VCALL_CLOBBERS

#घोषणा PVOP_VCALLEE_CLOBBERS		"=a" (__eax), "=d" (__edx)
#घोषणा PVOP_CALLEE_CLOBBERS		PVOP_VCALLEE_CLOBBERS

#घोषणा EXTRA_CLOBBERS
#घोषणा VEXTRA_CLOBBERS
#अन्यथा  /* CONFIG_X86_64 */
/* [re]ax isn't an arg, but the वापस val */
#घोषणा PVOP_CALL_ARGS						\
	अचिन्हित दीर्घ __edi = __edi, __esi = __esi,		\
		__edx = __edx, __ecx = __ecx, __eax = __eax;

#घोषणा PVOP_CALL_ARG1(x)		"D" ((अचिन्हित दीर्घ)(x))
#घोषणा PVOP_CALL_ARG2(x)		"S" ((अचिन्हित दीर्घ)(x))
#घोषणा PVOP_CALL_ARG3(x)		"d" ((अचिन्हित दीर्घ)(x))
#घोषणा PVOP_CALL_ARG4(x)		"c" ((अचिन्हित दीर्घ)(x))

#घोषणा PVOP_VCALL_CLOBBERS	"=D" (__edi),				\
				"=S" (__esi), "=d" (__edx),		\
				"=c" (__ecx)
#घोषणा PVOP_CALL_CLOBBERS	PVOP_VCALL_CLOBBERS, "=a" (__eax)

/* व्योम functions are still allowed [re]ax क्रम scratch */
#घोषणा PVOP_VCALLEE_CLOBBERS	"=a" (__eax)
#घोषणा PVOP_CALLEE_CLOBBERS	PVOP_VCALLEE_CLOBBERS

#घोषणा EXTRA_CLOBBERS	 , "r8", "r9", "r10", "r11"
#घोषणा VEXTRA_CLOBBERS	 , "rax", "r8", "r9", "r10", "r11"
#पूर्ण_अगर	/* CONFIG_X86_32 */

#अगर_घोषित CONFIG_PARAVIRT_DEBUG
#घोषणा PVOP_TEST_शून्य(op)	BUG_ON(pv_ops.op == शून्य)
#अन्यथा
#घोषणा PVOP_TEST_शून्य(op)	((व्योम)pv_ops.op)
#पूर्ण_अगर

#घोषणा PVOP_RETVAL(rettype)						\
	(अणु	अचिन्हित दीर्घ __mask = ~0UL;				\
		BUILD_BUG_ON(माप(rettype) > माप(अचिन्हित दीर्घ));	\
		चयन (माप(rettype)) अणु				\
		हाल 1: __mask =       0xffUL; अवरोध;			\
		हाल 2: __mask =     0xffffUL; अवरोध;			\
		हाल 4: __mask = 0xffffffffUL; अवरोध;			\
		शेष: अवरोध;						\
		पूर्ण							\
		__mask & __eax;						\
	पूर्ण)


#घोषणा ____PVOP_CALL(ret, op, clbr, call_clbr, extra_clbr, ...)	\
	(अणु								\
		PVOP_CALL_ARGS;						\
		PVOP_TEST_शून्य(op);					\
		यंत्र अस्थिर(paravirt_alt(PARAVIRT_CALL)		\
			     : call_clbr, ASM_CALL_CONSTRAINT		\
			     : paravirt_type(op),			\
			       paravirt_clobber(clbr),			\
			       ##__VA_ARGS__				\
			     : "memory", "cc" extra_clbr);		\
		ret;							\
	पूर्ण)

#घोषणा ____PVOP_ALT_CALL(ret, op, alt, cond, clbr, call_clbr,		\
			  extra_clbr, ...)				\
	(अणु								\
		PVOP_CALL_ARGS;						\
		PVOP_TEST_शून्य(op);					\
		यंत्र अस्थिर(ALTERNATIVE(paravirt_alt(PARAVIRT_CALL),	\
					 alt, cond)			\
			     : call_clbr, ASM_CALL_CONSTRAINT		\
			     : paravirt_type(op),			\
			       paravirt_clobber(clbr),			\
			       ##__VA_ARGS__				\
			     : "memory", "cc" extra_clbr);		\
		ret;							\
	पूर्ण)

#घोषणा __PVOP_CALL(rettype, op, ...)					\
	____PVOP_CALL(PVOP_RETVAL(rettype), op, CLBR_ANY,		\
		      PVOP_CALL_CLOBBERS, EXTRA_CLOBBERS, ##__VA_ARGS__)

#घोषणा __PVOP_ALT_CALL(rettype, op, alt, cond, ...)			\
	____PVOP_ALT_CALL(PVOP_RETVAL(rettype), op, alt, cond, CLBR_ANY,\
			  PVOP_CALL_CLOBBERS, EXTRA_CLOBBERS,		\
			  ##__VA_ARGS__)

#घोषणा __PVOP_CALLEESAVE(rettype, op, ...)				\
	____PVOP_CALL(PVOP_RETVAL(rettype), op.func, CLBR_RET_REG,	\
		      PVOP_CALLEE_CLOBBERS, , ##__VA_ARGS__)

#घोषणा __PVOP_ALT_CALLEESAVE(rettype, op, alt, cond, ...)		\
	____PVOP_ALT_CALL(PVOP_RETVAL(rettype), op.func, alt, cond,	\
			  CLBR_RET_REG, PVOP_CALLEE_CLOBBERS, , ##__VA_ARGS__)


#घोषणा __PVOP_VCALL(op, ...)						\
	(व्योम)____PVOP_CALL(, op, CLBR_ANY, PVOP_VCALL_CLOBBERS,	\
		       VEXTRA_CLOBBERS, ##__VA_ARGS__)

#घोषणा __PVOP_ALT_VCALL(op, alt, cond, ...)				\
	(व्योम)____PVOP_ALT_CALL(, op, alt, cond, CLBR_ANY,		\
				PVOP_VCALL_CLOBBERS, VEXTRA_CLOBBERS,	\
				##__VA_ARGS__)

#घोषणा __PVOP_VCALLEESAVE(op, ...)					\
	(व्योम)____PVOP_CALL(, op.func, CLBR_RET_REG,			\
			    PVOP_VCALLEE_CLOBBERS, , ##__VA_ARGS__)

#घोषणा __PVOP_ALT_VCALLEESAVE(op, alt, cond, ...)			\
	(व्योम)____PVOP_ALT_CALL(, op.func, alt, cond, CLBR_RET_REG,	\
				PVOP_VCALLEE_CLOBBERS, , ##__VA_ARGS__)


#घोषणा PVOP_CALL0(rettype, op)						\
	__PVOP_CALL(rettype, op)
#घोषणा PVOP_VCALL0(op)							\
	__PVOP_VCALL(op)
#घोषणा PVOP_ALT_CALL0(rettype, op, alt, cond)				\
	__PVOP_ALT_CALL(rettype, op, alt, cond)
#घोषणा PVOP_ALT_VCALL0(op, alt, cond)					\
	__PVOP_ALT_VCALL(op, alt, cond)

#घोषणा PVOP_CALLEE0(rettype, op)					\
	__PVOP_CALLEESAVE(rettype, op)
#घोषणा PVOP_VCALLEE0(op)						\
	__PVOP_VCALLEESAVE(op)
#घोषणा PVOP_ALT_CALLEE0(rettype, op, alt, cond)			\
	__PVOP_ALT_CALLEESAVE(rettype, op, alt, cond)
#घोषणा PVOP_ALT_VCALLEE0(op, alt, cond)				\
	__PVOP_ALT_VCALLEESAVE(op, alt, cond)


#घोषणा PVOP_CALL1(rettype, op, arg1)					\
	__PVOP_CALL(rettype, op, PVOP_CALL_ARG1(arg1))
#घोषणा PVOP_VCALL1(op, arg1)						\
	__PVOP_VCALL(op, PVOP_CALL_ARG1(arg1))
#घोषणा PVOP_ALT_VCALL1(op, arg1, alt, cond)				\
	__PVOP_ALT_VCALL(op, alt, cond, PVOP_CALL_ARG1(arg1))

#घोषणा PVOP_CALLEE1(rettype, op, arg1)					\
	__PVOP_CALLEESAVE(rettype, op, PVOP_CALL_ARG1(arg1))
#घोषणा PVOP_VCALLEE1(op, arg1)						\
	__PVOP_VCALLEESAVE(op, PVOP_CALL_ARG1(arg1))
#घोषणा PVOP_ALT_CALLEE1(rettype, op, arg1, alt, cond)			\
	__PVOP_ALT_CALLEESAVE(rettype, op, alt, cond, PVOP_CALL_ARG1(arg1))
#घोषणा PVOP_ALT_VCALLEE1(op, arg1, alt, cond)				\
	__PVOP_ALT_VCALLEESAVE(op, alt, cond, PVOP_CALL_ARG1(arg1))


#घोषणा PVOP_CALL2(rettype, op, arg1, arg2)				\
	__PVOP_CALL(rettype, op, PVOP_CALL_ARG1(arg1), PVOP_CALL_ARG2(arg2))
#घोषणा PVOP_VCALL2(op, arg1, arg2)					\
	__PVOP_VCALL(op, PVOP_CALL_ARG1(arg1), PVOP_CALL_ARG2(arg2))

#घोषणा PVOP_CALL3(rettype, op, arg1, arg2, arg3)			\
	__PVOP_CALL(rettype, op, PVOP_CALL_ARG1(arg1),			\
		    PVOP_CALL_ARG2(arg2), PVOP_CALL_ARG3(arg3))
#घोषणा PVOP_VCALL3(op, arg1, arg2, arg3)				\
	__PVOP_VCALL(op, PVOP_CALL_ARG1(arg1),				\
		     PVOP_CALL_ARG2(arg2), PVOP_CALL_ARG3(arg3))

#घोषणा PVOP_CALL4(rettype, op, arg1, arg2, arg3, arg4)			\
	__PVOP_CALL(rettype, op,					\
		    PVOP_CALL_ARG1(arg1), PVOP_CALL_ARG2(arg2),		\
		    PVOP_CALL_ARG3(arg3), PVOP_CALL_ARG4(arg4))
#घोषणा PVOP_VCALL4(op, arg1, arg2, arg3, arg4)				\
	__PVOP_VCALL(op, PVOP_CALL_ARG1(arg1), PVOP_CALL_ARG2(arg2),	\
		     PVOP_CALL_ARG3(arg3), PVOP_CALL_ARG4(arg4))

/* Lazy mode क्रम batching updates / context चयन */
क्रमागत paravirt_lazy_mode अणु
	PARAVIRT_LAZY_NONE,
	PARAVIRT_LAZY_MMU,
	PARAVIRT_LAZY_CPU,
पूर्ण;

क्रमागत paravirt_lazy_mode paravirt_get_lazy_mode(व्योम);
व्योम paravirt_start_context_चयन(काष्ठा task_काष्ठा *prev);
व्योम paravirt_end_context_चयन(काष्ठा task_काष्ठा *next);

व्योम paravirt_enter_lazy_mmu(व्योम);
व्योम paravirt_leave_lazy_mmu(व्योम);
व्योम paravirt_flush_lazy_mmu(व्योम);

व्योम _paravirt_nop(व्योम);
u64 _paravirt_ident_64(u64);

#घोषणा paravirt_nop	((व्योम *)_paravirt_nop)

/* These all sit in the .parainकाष्ठाions section to tell us what to patch. */
काष्ठा paravirt_patch_site अणु
	u8 *instr;		/* original inकाष्ठाions */
	u8 type;		/* type of this inकाष्ठाion */
	u8 len;			/* length of original inकाष्ठाion */
पूर्ण;

बाह्य काष्ठा paravirt_patch_site __parainकाष्ठाions[],
	__parainकाष्ठाions_end[];

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर	/* _ASM_X86_PARAVIRT_TYPES_H */
