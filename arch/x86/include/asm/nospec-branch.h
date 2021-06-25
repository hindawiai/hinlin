<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_X86_NOSPEC_BRANCH_H_
#घोषणा _ASM_X86_NOSPEC_BRANCH_H_

#समावेश <linux/अटल_key.h>
#समावेश <linux/objtool.h>

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/cpufeatures.h>
#समावेश <यंत्र/msr-index.h>
#समावेश <यंत्र/unwind_hपूर्णांकs.h>

/*
 * Fill the CPU वापस stack buffer.
 *
 * Each entry in the RSB, अगर used क्रम a speculative 'ret', contains an
 * infinite 'pause; lfence; jmp' loop to capture speculative execution.
 *
 * This is required in various हालs क्रम retpoline and IBRS-based
 * mitigations क्रम the Spectre variant 2 vulnerability. Someबार to
 * eliminate potentially bogus entries from the RSB, and someबार
 * purely to ensure that it करोesn't get empty, which on some CPUs would
 * allow predictions from other (unwanted!) sources to be used.
 *
 * We define a CPP macro such that it can be used from both .S files and
 * अंतरभूत assembly. It's possible to करो a .macro and then include that
 * from C via यंत्र(".include <asm/nospec-branch.h>") but let's not go there.
 */

#घोषणा RSB_CLEAR_LOOPS		32	/* To क्रमcibly overग_लिखो all entries */

/*
 * Google experimented with loop-unrolling and this turned out to be
 * the optimal version - two calls, each with their own speculation
 * trap should their वापस address end up getting used, in a loop.
 */
#घोषणा __FILL_RETURN_BUFFER(reg, nr, sp)	\
	mov	$(nr/2), reg;			\
771:						\
	ANNOTATE_INTRA_FUNCTION_CALL;		\
	call	772f;				\
773:	/* speculation trap */			\
	UNWIND_HINT_EMPTY;			\
	छोड़ो;					\
	lfence;					\
	jmp	773b;				\
772:						\
	ANNOTATE_INTRA_FUNCTION_CALL;		\
	call	774f;				\
775:	/* speculation trap */			\
	UNWIND_HINT_EMPTY;			\
	छोड़ो;					\
	lfence;					\
	jmp	775b;				\
774:						\
	add	$(BITS_PER_LONG/8) * 2, sp;	\
	dec	reg;				\
	jnz	771b;

#अगर_घोषित __ASSEMBLY__

/*
 * This should be used immediately beक्रमe an indirect jump/call. It tells
 * objtool the subsequent indirect jump/call is vouched safe क्रम retpoline
 * builds.
 */
.macro ANNOTATE_RETPOLINE_SAFE
	.Lannotate_\@:
	.pushsection .discard.retpoline_safe
	_ASM_PTR .Lannotate_\@
	.popsection
.endm

/*
 * JMP_NOSPEC and CALL_NOSPEC macros can be used instead of a simple
 * indirect jmp/call which may be susceptible to the Spectre variant 2
 * attack.
 */
.macro JMP_NOSPEC reg:req
#अगर_घोषित CONFIG_RETPOLINE
	ALTERNATIVE_2 __stringअगरy(ANNOTATE_RETPOLINE_SAFE; jmp *%\लeg), \
		      __stringअगरy(jmp __x86_indirect_thunk_\लeg), X86_FEATURE_RETPOLINE, \
		      __stringअगरy(lfence; ANNOTATE_RETPOLINE_SAFE; jmp *%\लeg), X86_FEATURE_RETPOLINE_AMD
#अन्यथा
	jmp	*%\लeg
#पूर्ण_अगर
.endm

.macro CALL_NOSPEC reg:req
#अगर_घोषित CONFIG_RETPOLINE
	ALTERNATIVE_2 __stringअगरy(ANNOTATE_RETPOLINE_SAFE; call *%\लeg), \
		      __stringअगरy(call __x86_indirect_thunk_\लeg), X86_FEATURE_RETPOLINE, \
		      __stringअगरy(lfence; ANNOTATE_RETPOLINE_SAFE; call *%\लeg), X86_FEATURE_RETPOLINE_AMD
#अन्यथा
	call	*%\लeg
#पूर्ण_अगर
.endm

 /*
  * A simpler FILL_RETURN_BUFFER macro. Don't make people use the CPP
  * monstrosity above, manually.
  */
.macro FILL_RETURN_BUFFER reg:req nr:req ftr:req
#अगर_घोषित CONFIG_RETPOLINE
	ALTERNATIVE "jmp .Lskip_rsb_\@", "", \पtr
	__FILL_RETURN_BUFFER(\लeg,\नr,%_ASM_SP)
.Lskip_rsb_\@:
#पूर्ण_अगर
.endm

#अन्यथा /* __ASSEMBLY__ */

#घोषणा ANNOTATE_RETPOLINE_SAFE					\
	"999:\n\t"						\
	".pushsection .discard.retpoline_safe\n\t"		\
	_ASM_PTR " 999b\n\t"					\
	".popsection\n\t"

#अगर_घोषित CONFIG_RETPOLINE
#अगर_घोषित CONFIG_X86_64

/*
 * Inline यंत्र uses the %V modअगरier which is only in newer GCC
 * which is ensured when CONFIG_RETPOLINE is defined.
 */
# define CALL_NOSPEC						\
	ALTERNATIVE_2(						\
	ANNOTATE_RETPOLINE_SAFE					\
	"call *%[thunk_target]\n",				\
	"call __x86_indirect_thunk_%V[thunk_target]\n",		\
	X86_FEATURE_RETPOLINE,					\
	"lfence;\n"						\
	ANNOTATE_RETPOLINE_SAFE					\
	"call *%[thunk_target]\n",				\
	X86_FEATURE_RETPOLINE_AMD)

# define THUNK_TARGET(addr) [thunk_target] "r" (addr)

#अन्यथा /* CONFIG_X86_32 */
/*
 * For i386 we use the original ret-equivalent retpoline, because
 * otherwise we'll run out of registers. We don't care about CET
 * here, anyway.
 */
# define CALL_NOSPEC						\
	ALTERNATIVE_2(						\
	ANNOTATE_RETPOLINE_SAFE					\
	"call *%[thunk_target]\n",				\
	"       jmp    904f;\n"					\
	"       .align 16\n"					\
	"901:	call   903f;\n"					\
	"902:	pause;\n"					\
	"    	lfence;\n"					\
	"       jmp    902b;\n"					\
	"       .align 16\n"					\
	"903:	lea    4(%%esp), %%esp;\n"			\
	"       pushl  %[thunk_target];\n"			\
	"       ret;\n"						\
	"       .align 16\n"					\
	"904:	call   901b;\n",				\
	X86_FEATURE_RETPOLINE,					\
	"lfence;\n"						\
	ANNOTATE_RETPOLINE_SAFE					\
	"call *%[thunk_target]\n",				\
	X86_FEATURE_RETPOLINE_AMD)

# define THUNK_TARGET(addr) [thunk_target] "rm" (addr)
#पूर्ण_अगर
#अन्यथा /* No retpoline क्रम C / अंतरभूत यंत्र */
# define CALL_NOSPEC "call *%[thunk_target]\n"
# define THUNK_TARGET(addr) [thunk_target] "rm" (addr)
#पूर्ण_अगर

/* The Spectre V2 mitigation variants */
क्रमागत spectre_v2_mitigation अणु
	SPECTRE_V2_NONE,
	SPECTRE_V2_RETPOLINE_GENERIC,
	SPECTRE_V2_RETPOLINE_AMD,
	SPECTRE_V2_IBRS_ENHANCED,
पूर्ण;

/* The indirect branch speculation control variants */
क्रमागत spectre_v2_user_mitigation अणु
	SPECTRE_V2_USER_NONE,
	SPECTRE_V2_USER_STRICT,
	SPECTRE_V2_USER_STRICT_PREFERRED,
	SPECTRE_V2_USER_PRCTL,
	SPECTRE_V2_USER_SECCOMP,
पूर्ण;

/* The Speculative Store Bypass disable variants */
क्रमागत ssb_mitigation अणु
	SPEC_STORE_BYPASS_NONE,
	SPEC_STORE_BYPASS_DISABLE,
	SPEC_STORE_BYPASS_PRCTL,
	SPEC_STORE_BYPASS_SECCOMP,
पूर्ण;

बाह्य अक्षर __indirect_thunk_start[];
बाह्य अक्षर __indirect_thunk_end[];

अटल __always_अंतरभूत
व्योम alternative_msr_ग_लिखो(अचिन्हित पूर्णांक msr, u64 val, अचिन्हित पूर्णांक feature)
अणु
	यंत्र अस्थिर(ALTERNATIVE("", "wrmsr", %c[feature])
		: : "c" (msr),
		    "a" ((u32)val),
		    "d" ((u32)(val >> 32)),
		    [feature] "i" (feature)
		: "memory");
पूर्ण

अटल अंतरभूत व्योम indirect_branch_prediction_barrier(व्योम)
अणु
	u64 val = PRED_CMD_IBPB;

	alternative_msr_ग_लिखो(MSR_IA32_PRED_CMD, val, X86_FEATURE_USE_IBPB);
पूर्ण

/* The Intel SPEC CTRL MSR base value cache */
बाह्य u64 x86_spec_ctrl_base;

/*
 * With retpoline, we must use IBRS to restrict branch prediction
 * beक्रमe calling पूर्णांकo firmware.
 *
 * (Implemented as CPP macros due to header hell.)
 */
#घोषणा firmware_restrict_branch_speculation_start()			\
करो अणु									\
	u64 val = x86_spec_ctrl_base | SPEC_CTRL_IBRS;			\
									\
	preempt_disable();						\
	alternative_msr_ग_लिखो(MSR_IA32_SPEC_CTRL, val,			\
			      X86_FEATURE_USE_IBRS_FW);			\
पूर्ण जबतक (0)

#घोषणा firmware_restrict_branch_speculation_end()			\
करो अणु									\
	u64 val = x86_spec_ctrl_base;					\
									\
	alternative_msr_ग_लिखो(MSR_IA32_SPEC_CTRL, val,			\
			      X86_FEATURE_USE_IBRS_FW);			\
	preempt_enable();						\
पूर्ण जबतक (0)

DECLARE_STATIC_KEY_FALSE(चयन_to_cond_stibp);
DECLARE_STATIC_KEY_FALSE(चयन_mm_cond_ibpb);
DECLARE_STATIC_KEY_FALSE(चयन_mm_always_ibpb);

DECLARE_STATIC_KEY_FALSE(mds_user_clear);
DECLARE_STATIC_KEY_FALSE(mds_idle_clear);

#समावेश <यंत्र/segment.h>

/**
 * mds_clear_cpu_buffers - Mitigation क्रम MDS and TAA vulnerability
 *
 * This uses the otherwise unused and obsolete VERW inकाष्ठाion in
 * combination with microcode which triggers a CPU buffer flush when the
 * inकाष्ठाion is executed.
 */
अटल __always_अंतरभूत व्योम mds_clear_cpu_buffers(व्योम)
अणु
	अटल स्थिर u16 ds = __KERNEL_DS;

	/*
	 * Has to be the memory-opeअक्रम variant because only that
	 * guarantees the CPU buffer flush functionality according to
	 * करोcumentation. The रेजिस्टर-opeअक्रम variant करोes not.
	 * Works with any segment selector, but a valid writable
	 * data segment is the fastest variant.
	 *
	 * "cc" clobber is required because VERW modअगरies ZF.
	 */
	यंत्र अस्थिर("verw %[ds]" : : [ds] "m" (ds) : "cc");
पूर्ण

/**
 * mds_user_clear_cpu_buffers - Mitigation क्रम MDS and TAA vulnerability
 *
 * Clear CPU buffers अगर the corresponding अटल key is enabled
 */
अटल __always_अंतरभूत व्योम mds_user_clear_cpu_buffers(व्योम)
अणु
	अगर (अटल_branch_likely(&mds_user_clear))
		mds_clear_cpu_buffers();
पूर्ण

/**
 * mds_idle_clear_cpu_buffers - Mitigation क्रम MDS vulnerability
 *
 * Clear CPU buffers अगर the corresponding अटल key is enabled
 */
अटल अंतरभूत व्योम mds_idle_clear_cpu_buffers(व्योम)
अणु
	अगर (अटल_branch_likely(&mds_idle_clear))
		mds_clear_cpu_buffers();
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * Below is used in the eBPF JIT compiler and emits the byte sequence
 * क्रम the following assembly:
 *
 * With retpolines configured:
 *
 *    callq करो_rop
 *  spec_trap:
 *    छोड़ो
 *    lfence
 *    jmp spec_trap
 *  करो_rop:
 *    mov %rcx,(%rsp) क्रम x86_64
 *    mov %edx,(%esp) क्रम x86_32
 *    retq
 *
 * Without retpolines configured:
 *
 *    jmp *%rcx क्रम x86_64
 *    jmp *%edx क्रम x86_32
 */
#अगर_घोषित CONFIG_RETPOLINE
# अगरdef CONFIG_X86_64
#  define RETPOLINE_RCX_BPF_JIT_SIZE	17
#  define RETPOLINE_RCX_BPF_JIT()				\
करो अणु								\
	EMIT1_off32(0xE8, 7);	 /* callq करो_rop */		\
	/* spec_trap: */					\
	EMIT2(0xF3, 0x90);       /* छोड़ो */			\
	EMIT3(0x0F, 0xAE, 0xE8); /* lfence */			\
	EMIT2(0xEB, 0xF9);       /* jmp spec_trap */		\
	/* करो_rop: */						\
	EMIT4(0x48, 0x89, 0x0C, 0x24); /* mov %rcx,(%rsp) */	\
	EMIT1(0xC3);             /* retq */			\
पूर्ण जबतक (0)
# अन्यथा /* !CONFIG_X86_64 */
#  define RETPOLINE_EDX_BPF_JIT()				\
करो अणु								\
	EMIT1_off32(0xE8, 7);	 /* call करो_rop */		\
	/* spec_trap: */					\
	EMIT2(0xF3, 0x90);       /* छोड़ो */			\
	EMIT3(0x0F, 0xAE, 0xE8); /* lfence */			\
	EMIT2(0xEB, 0xF9);       /* jmp spec_trap */		\
	/* करो_rop: */						\
	EMIT3(0x89, 0x14, 0x24); /* mov %edx,(%esp) */		\
	EMIT1(0xC3);             /* ret */			\
पूर्ण जबतक (0)
# endअगर
#अन्यथा /* !CONFIG_RETPOLINE */
# अगरdef CONFIG_X86_64
#  define RETPOLINE_RCX_BPF_JIT_SIZE	2
#  define RETPOLINE_RCX_BPF_JIT()				\
	EMIT2(0xFF, 0xE1);       /* jmp *%rcx */
# अन्यथा /* !CONFIG_X86_64 */
#  define RETPOLINE_EDX_BPF_JIT()				\
	EMIT2(0xFF, 0xE2)        /* jmp *%edx */
# endअगर
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_NOSPEC_BRANCH_H_ */
