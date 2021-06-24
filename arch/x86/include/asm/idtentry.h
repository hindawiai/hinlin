<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_IDTENTRY_H
#घोषणा _ASM_X86_IDTENTRY_H

/* Interrupts/Exceptions */
#समावेश <यंत्र/trapnr.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/entry-common.h>
#समावेश <linux/hardirq.h>

#समावेश <यंत्र/irq_stack.h>

/**
 * DECLARE_IDTENTRY - Declare functions क्रम simple IDT entry poपूर्णांकs
 *		      No error code pushed by hardware
 * @vector:	Vector number (ignored क्रम C)
 * @func:	Function name of the entry poपूर्णांक
 *
 * Declares three functions:
 * - The ASM entry poपूर्णांक: यंत्र_##func
 * - The XEN PV trap entry poपूर्णांक: xen_##func (maybe unused)
 * - The C handler called from the ASM entry poपूर्णांक
 *
 * Note: This is the C variant of DECLARE_IDTENTRY(). As the name says it
 * declares the entry poपूर्णांकs क्रम usage in C code. There is an ASM variant
 * as well which is used to emit the entry stubs in entry_32/64.S.
 */
#घोषणा DECLARE_IDTENTRY(vector, func)					\
	यंत्रlinkage व्योम यंत्र_##func(व्योम);				\
	यंत्रlinkage व्योम xen_यंत्र_##func(व्योम);				\
	__visible व्योम func(काष्ठा pt_regs *regs)

/**
 * DEFINE_IDTENTRY - Emit code क्रम simple IDT entry poपूर्णांकs
 * @func:	Function name of the entry poपूर्णांक
 *
 * @func is called from ASM entry code with पूर्णांकerrupts disabled.
 *
 * The macro is written so it acts as function definition. Append the
 * body with a pair of curly brackets.
 *
 * irqentry_enter() contains common code which has to be invoked beक्रमe
 * arbitrary code in the body. irqentry_निकास() contains common code
 * which has to run beक्रमe वापसing to the low level assembly code.
 */
#घोषणा DEFINE_IDTENTRY(func)						\
अटल __always_अंतरभूत व्योम __##func(काष्ठा pt_regs *regs);		\
									\
__visible noinstr व्योम func(काष्ठा pt_regs *regs)			\
अणु									\
	irqentry_state_t state = irqentry_enter(regs);			\
									\
	instrumentation_begin();					\
	__##func (regs);						\
	instrumentation_end();						\
	irqentry_निकास(regs, state);					\
पूर्ण									\
									\
अटल __always_अंतरभूत व्योम __##func(काष्ठा pt_regs *regs)

/* Special हाल क्रम 32bit IRET 'trap' */
#घोषणा DECLARE_IDTENTRY_SW	DECLARE_IDTENTRY
#घोषणा DEFINE_IDTENTRY_SW	DEFINE_IDTENTRY

/**
 * DECLARE_IDTENTRY_ERRORCODE - Declare functions क्रम simple IDT entry poपूर्णांकs
 *				Error code pushed by hardware
 * @vector:	Vector number (ignored क्रम C)
 * @func:	Function name of the entry poपूर्णांक
 *
 * Declares three functions:
 * - The ASM entry poपूर्णांक: यंत्र_##func
 * - The XEN PV trap entry poपूर्णांक: xen_##func (maybe unused)
 * - The C handler called from the ASM entry poपूर्णांक
 *
 * Same as DECLARE_IDTENTRY, but has an extra error_code argument क्रम the
 * C-handler.
 */
#घोषणा DECLARE_IDTENTRY_ERRORCODE(vector, func)			\
	यंत्रlinkage व्योम यंत्र_##func(व्योम);				\
	यंत्रlinkage व्योम xen_यंत्र_##func(व्योम);				\
	__visible व्योम func(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code)

/**
 * DEFINE_IDTENTRY_ERRORCODE - Emit code क्रम simple IDT entry poपूर्णांकs
 *			       Error code pushed by hardware
 * @func:	Function name of the entry poपूर्णांक
 *
 * Same as DEFINE_IDTENTRY, but has an extra error_code argument
 */
#घोषणा DEFINE_IDTENTRY_ERRORCODE(func)					\
अटल __always_अंतरभूत व्योम __##func(काष्ठा pt_regs *regs,		\
				     अचिन्हित दीर्घ error_code);		\
									\
__visible noinstr व्योम func(काष्ठा pt_regs *regs,			\
			    अचिन्हित दीर्घ error_code)			\
अणु									\
	irqentry_state_t state = irqentry_enter(regs);			\
									\
	instrumentation_begin();					\
	__##func (regs, error_code);					\
	instrumentation_end();						\
	irqentry_निकास(regs, state);					\
पूर्ण									\
									\
अटल __always_अंतरभूत व्योम __##func(काष्ठा pt_regs *regs,		\
				     अचिन्हित दीर्घ error_code)

/**
 * DECLARE_IDTENTRY_RAW - Declare functions क्रम raw IDT entry poपूर्णांकs
 *		      No error code pushed by hardware
 * @vector:	Vector number (ignored क्रम C)
 * @func:	Function name of the entry poपूर्णांक
 *
 * Maps to DECLARE_IDTENTRY().
 */
#घोषणा DECLARE_IDTENTRY_RAW(vector, func)				\
	DECLARE_IDTENTRY(vector, func)

/**
 * DEFINE_IDTENTRY_RAW - Emit code क्रम raw IDT entry poपूर्णांकs
 * @func:	Function name of the entry poपूर्णांक
 *
 * @func is called from ASM entry code with पूर्णांकerrupts disabled.
 *
 * The macro is written so it acts as function definition. Append the
 * body with a pair of curly brackets.
 *
 * Contrary to DEFINE_IDTENTRY() this करोes not invoke the
 * idtentry_enter/निकास() helpers beक्रमe and after the body invocation. This
 * needs to be करोne in the body itself अगर applicable. Use अगर extra work
 * is required beक्रमe the enter/निकास() helpers are invoked.
 */
#घोषणा DEFINE_IDTENTRY_RAW(func)					\
__visible noinstr व्योम func(काष्ठा pt_regs *regs)

/**
 * DECLARE_IDTENTRY_RAW_ERRORCODE - Declare functions क्रम raw IDT entry poपूर्णांकs
 *				    Error code pushed by hardware
 * @vector:	Vector number (ignored क्रम C)
 * @func:	Function name of the entry poपूर्णांक
 *
 * Maps to DECLARE_IDTENTRY_ERRORCODE()
 */
#घोषणा DECLARE_IDTENTRY_RAW_ERRORCODE(vector, func)			\
	DECLARE_IDTENTRY_ERRORCODE(vector, func)

/**
 * DEFINE_IDTENTRY_RAW_ERRORCODE - Emit code क्रम raw IDT entry poपूर्णांकs
 * @func:	Function name of the entry poपूर्णांक
 *
 * @func is called from ASM entry code with पूर्णांकerrupts disabled.
 *
 * The macro is written so it acts as function definition. Append the
 * body with a pair of curly brackets.
 *
 * Contrary to DEFINE_IDTENTRY_ERRORCODE() this करोes not invoke the
 * irqentry_enter/निकास() helpers beक्रमe and after the body invocation. This
 * needs to be करोne in the body itself अगर applicable. Use अगर extra work
 * is required beक्रमe the enter/निकास() helpers are invoked.
 */
#घोषणा DEFINE_IDTENTRY_RAW_ERRORCODE(func)				\
__visible noinstr व्योम func(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code)

/**
 * DECLARE_IDTENTRY_IRQ - Declare functions क्रम device पूर्णांकerrupt IDT entry
 *			  poपूर्णांकs (common/spurious)
 * @vector:	Vector number (ignored क्रम C)
 * @func:	Function name of the entry poपूर्णांक
 *
 * Maps to DECLARE_IDTENTRY_ERRORCODE()
 */
#घोषणा DECLARE_IDTENTRY_IRQ(vector, func)				\
	DECLARE_IDTENTRY_ERRORCODE(vector, func)

/**
 * DEFINE_IDTENTRY_IRQ - Emit code क्रम device पूर्णांकerrupt IDT entry poपूर्णांकs
 * @func:	Function name of the entry poपूर्णांक
 *
 * The vector number is pushed by the low level entry stub and handed
 * to the function as error_code argument which needs to be truncated
 * to an u8 because the push is sign extending.
 *
 * irq_enter/निकास_rcu() are invoked beक्रमe the function body and the
 * KVM L1D flush request is set. Stack चयनing to the पूर्णांकerrupt stack
 * has to be करोne in the function body अगर necessary.
 */
#घोषणा DEFINE_IDTENTRY_IRQ(func)					\
अटल व्योम __##func(काष्ठा pt_regs *regs, u32 vector);			\
									\
__visible noinstr व्योम func(काष्ठा pt_regs *regs,			\
			    अचिन्हित दीर्घ error_code)			\
अणु									\
	irqentry_state_t state = irqentry_enter(regs);			\
	u32 vector = (u32)(u8)error_code;				\
									\
	instrumentation_begin();					\
	kvm_set_cpu_l1tf_flush_l1d();					\
	run_irq_on_irqstack_cond(__##func, regs, vector);		\
	instrumentation_end();						\
	irqentry_निकास(regs, state);					\
पूर्ण									\
									\
अटल noअंतरभूत व्योम __##func(काष्ठा pt_regs *regs, u32 vector)

/**
 * DECLARE_IDTENTRY_SYSVEC - Declare functions क्रम प्रणाली vector entry poपूर्णांकs
 * @vector:	Vector number (ignored क्रम C)
 * @func:	Function name of the entry poपूर्णांक
 *
 * Declares three functions:
 * - The ASM entry poपूर्णांक: यंत्र_##func
 * - The XEN PV trap entry poपूर्णांक: xen_##func (maybe unused)
 * - The C handler called from the ASM entry poपूर्णांक
 *
 * Maps to DECLARE_IDTENTRY().
 */
#घोषणा DECLARE_IDTENTRY_SYSVEC(vector, func)				\
	DECLARE_IDTENTRY(vector, func)

/**
 * DEFINE_IDTENTRY_SYSVEC - Emit code क्रम प्रणाली vector IDT entry poपूर्णांकs
 * @func:	Function name of the entry poपूर्णांक
 *
 * irqentry_enter/निकास() and irq_enter/निकास_rcu() are invoked beक्रमe the
 * function body. KVM L1D flush request is set.
 *
 * Runs the function on the पूर्णांकerrupt stack अगर the entry hit kernel mode
 */
#घोषणा DEFINE_IDTENTRY_SYSVEC(func)					\
अटल व्योम __##func(काष्ठा pt_regs *regs);				\
									\
__visible noinstr व्योम func(काष्ठा pt_regs *regs)			\
अणु									\
	irqentry_state_t state = irqentry_enter(regs);			\
									\
	instrumentation_begin();					\
	kvm_set_cpu_l1tf_flush_l1d();					\
	run_sysvec_on_irqstack_cond(__##func, regs);			\
	instrumentation_end();						\
	irqentry_निकास(regs, state);					\
पूर्ण									\
									\
अटल noअंतरभूत व्योम __##func(काष्ठा pt_regs *regs)

/**
 * DEFINE_IDTENTRY_SYSVEC_SIMPLE - Emit code क्रम simple प्रणाली vector IDT
 *				   entry poपूर्णांकs
 * @func:	Function name of the entry poपूर्णांक
 *
 * Runs the function on the पूर्णांकerrupted stack. No चयन to IRQ stack and
 * only the minimal __irq_enter/निकास() handling.
 *
 * Only use क्रम 'empty' vectors like reschedule IPI and KVM posted
 * पूर्णांकerrupt vectors.
 */
#घोषणा DEFINE_IDTENTRY_SYSVEC_SIMPLE(func)				\
अटल __always_अंतरभूत व्योम __##func(काष्ठा pt_regs *regs);		\
									\
__visible noinstr व्योम func(काष्ठा pt_regs *regs)			\
अणु									\
	irqentry_state_t state = irqentry_enter(regs);			\
									\
	instrumentation_begin();					\
	__irq_enter_raw();						\
	kvm_set_cpu_l1tf_flush_l1d();					\
	__##func (regs);						\
	__irq_निकास_raw();						\
	instrumentation_end();						\
	irqentry_निकास(regs, state);					\
पूर्ण									\
									\
अटल __always_अंतरभूत व्योम __##func(काष्ठा pt_regs *regs)

/**
 * DECLARE_IDTENTRY_XENCB - Declare functions क्रम XEN HV callback entry poपूर्णांक
 * @vector:	Vector number (ignored क्रम C)
 * @func:	Function name of the entry poपूर्णांक
 *
 * Declares three functions:
 * - The ASM entry poपूर्णांक: यंत्र_##func
 * - The XEN PV trap entry poपूर्णांक: xen_##func (maybe unused)
 * - The C handler called from the ASM entry poपूर्णांक
 *
 * Maps to DECLARE_IDTENTRY(). Distinct entry poपूर्णांक to handle the 32/64-bit
 * dअगरference
 */
#घोषणा DECLARE_IDTENTRY_XENCB(vector, func)				\
	DECLARE_IDTENTRY(vector, func)

#अगर_घोषित CONFIG_X86_64
/**
 * DECLARE_IDTENTRY_IST - Declare functions क्रम IST handling IDT entry poपूर्णांकs
 * @vector:	Vector number (ignored क्रम C)
 * @func:	Function name of the entry poपूर्णांक
 *
 * Maps to DECLARE_IDTENTRY_RAW, but declares also the NOIST C handler
 * which is called from the ASM entry poपूर्णांक on user mode entry
 */
#घोषणा DECLARE_IDTENTRY_IST(vector, func)				\
	DECLARE_IDTENTRY_RAW(vector, func);				\
	__visible व्योम noist_##func(काष्ठा pt_regs *regs)

/**
 * DECLARE_IDTENTRY_VC - Declare functions क्रम the VC entry poपूर्णांक
 * @vector:	Vector number (ignored क्रम C)
 * @func:	Function name of the entry poपूर्णांक
 *
 * Maps to DECLARE_IDTENTRY_RAW_ERRORCODE, but declares also the
 * safe_stack C handler.
 */
#घोषणा DECLARE_IDTENTRY_VC(vector, func)				\
	DECLARE_IDTENTRY_RAW_ERRORCODE(vector, func);			\
	__visible noinstr व्योम ist_##func(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code);	\
	__visible noinstr व्योम safe_stack_##func(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code)

/**
 * DEFINE_IDTENTRY_IST - Emit code क्रम IST entry poपूर्णांकs
 * @func:	Function name of the entry poपूर्णांक
 *
 * Maps to DEFINE_IDTENTRY_RAW
 */
#घोषणा DEFINE_IDTENTRY_IST(func)					\
	DEFINE_IDTENTRY_RAW(func)

/**
 * DEFINE_IDTENTRY_NOIST - Emit code क्रम NOIST entry poपूर्णांकs which
 *			   beदीर्घ to a IST entry poपूर्णांक (MCE, DB)
 * @func:	Function name of the entry poपूर्णांक. Must be the same as
 *		the function name of the corresponding IST variant
 *
 * Maps to DEFINE_IDTENTRY_RAW().
 */
#घोषणा DEFINE_IDTENTRY_NOIST(func)					\
	DEFINE_IDTENTRY_RAW(noist_##func)

/**
 * DECLARE_IDTENTRY_DF - Declare functions क्रम द्विगुन fault
 * @vector:	Vector number (ignored क्रम C)
 * @func:	Function name of the entry poपूर्णांक
 *
 * Maps to DECLARE_IDTENTRY_RAW_ERRORCODE
 */
#घोषणा DECLARE_IDTENTRY_DF(vector, func)				\
	DECLARE_IDTENTRY_RAW_ERRORCODE(vector, func)

/**
 * DEFINE_IDTENTRY_DF - Emit code क्रम द्विगुन fault
 * @func:	Function name of the entry poपूर्णांक
 *
 * Maps to DEFINE_IDTENTRY_RAW_ERRORCODE
 */
#घोषणा DEFINE_IDTENTRY_DF(func)					\
	DEFINE_IDTENTRY_RAW_ERRORCODE(func)

/**
 * DEFINE_IDTENTRY_VC_SAFE_STACK - Emit code क्रम VMM communication handler
				   which runs on a safe stack.
 * @func:	Function name of the entry poपूर्णांक
 *
 * Maps to DEFINE_IDTENTRY_RAW_ERRORCODE
 */
#घोषणा DEFINE_IDTENTRY_VC_SAFE_STACK(func)				\
	DEFINE_IDTENTRY_RAW_ERRORCODE(safe_stack_##func)

/**
 * DEFINE_IDTENTRY_VC_IST - Emit code क्रम VMM communication handler
			    which runs on the VC fall-back stack
 * @func:	Function name of the entry poपूर्णांक
 *
 * Maps to DEFINE_IDTENTRY_RAW_ERRORCODE
 */
#घोषणा DEFINE_IDTENTRY_VC_IST(func)				\
	DEFINE_IDTENTRY_RAW_ERRORCODE(ist_##func)

/**
 * DEFINE_IDTENTRY_VC - Emit code क्रम VMM communication handler
 * @func:	Function name of the entry poपूर्णांक
 *
 * Maps to DEFINE_IDTENTRY_RAW_ERRORCODE
 */
#घोषणा DEFINE_IDTENTRY_VC(func)					\
	DEFINE_IDTENTRY_RAW_ERRORCODE(func)

#अन्यथा	/* CONFIG_X86_64 */

/**
 * DECLARE_IDTENTRY_DF - Declare functions क्रम द्विगुन fault 32bit variant
 * @vector:	Vector number (ignored क्रम C)
 * @func:	Function name of the entry poपूर्णांक
 *
 * Declares two functions:
 * - The ASM entry poपूर्णांक: यंत्र_##func
 * - The C handler called from the C shim
 */
#घोषणा DECLARE_IDTENTRY_DF(vector, func)				\
	यंत्रlinkage व्योम यंत्र_##func(व्योम);				\
	__visible व्योम func(काष्ठा pt_regs *regs,			\
			    अचिन्हित दीर्घ error_code,			\
			    अचिन्हित दीर्घ address)

/**
 * DEFINE_IDTENTRY_DF - Emit code क्रम द्विगुन fault on 32bit
 * @func:	Function name of the entry poपूर्णांक
 *
 * This is called through the द्विगुनfault shim which alपढ़ोy provides
 * cr2 in the address argument.
 */
#घोषणा DEFINE_IDTENTRY_DF(func)					\
__visible noinstr व्योम func(काष्ठा pt_regs *regs,			\
			    अचिन्हित दीर्घ error_code,			\
			    अचिन्हित दीर्घ address)

#पूर्ण_अगर	/* !CONFIG_X86_64 */

/* C-Code mapping */
#घोषणा DECLARE_IDTENTRY_NMI		DECLARE_IDTENTRY_RAW
#घोषणा DEFINE_IDTENTRY_NMI		DEFINE_IDTENTRY_RAW

#अगर_घोषित CONFIG_X86_64
#घोषणा DECLARE_IDTENTRY_MCE		DECLARE_IDTENTRY_IST
#घोषणा DEFINE_IDTENTRY_MCE		DEFINE_IDTENTRY_IST
#घोषणा DEFINE_IDTENTRY_MCE_USER	DEFINE_IDTENTRY_NOIST

#घोषणा DECLARE_IDTENTRY_DEBUG		DECLARE_IDTENTRY_IST
#घोषणा DEFINE_IDTENTRY_DEBUG		DEFINE_IDTENTRY_IST
#घोषणा DEFINE_IDTENTRY_DEBUG_USER	DEFINE_IDTENTRY_NOIST
#पूर्ण_अगर

#अन्यथा /* !__ASSEMBLY__ */

/*
 * The ASM variants क्रम DECLARE_IDTENTRY*() which emit the ASM entry stubs.
 */
#घोषणा DECLARE_IDTENTRY(vector, func)					\
	idtentry vector यंत्र_##func func has_error_code=0

#घोषणा DECLARE_IDTENTRY_ERRORCODE(vector, func)			\
	idtentry vector यंत्र_##func func has_error_code=1

/* Special हाल क्रम 32bit IRET 'trap'. Do not emit ASM code */
#घोषणा DECLARE_IDTENTRY_SW(vector, func)

#घोषणा DECLARE_IDTENTRY_RAW(vector, func)				\
	DECLARE_IDTENTRY(vector, func)

#घोषणा DECLARE_IDTENTRY_RAW_ERRORCODE(vector, func)			\
	DECLARE_IDTENTRY_ERRORCODE(vector, func)

/* Entries क्रम common/spurious (device) पूर्णांकerrupts */
#घोषणा DECLARE_IDTENTRY_IRQ(vector, func)				\
	idtentry_irq vector func

/* System vector entries */
#घोषणा DECLARE_IDTENTRY_SYSVEC(vector, func)				\
	idtentry_sysvec vector func

#अगर_घोषित CONFIG_X86_64
# define DECLARE_IDTENTRY_MCE(vector, func)				\
	idtentry_mce_db vector यंत्र_##func func

# define DECLARE_IDTENTRY_DEBUG(vector, func)				\
	idtentry_mce_db vector यंत्र_##func func

# define DECLARE_IDTENTRY_DF(vector, func)				\
	idtentry_df vector यंत्र_##func func

# define DECLARE_IDTENTRY_XENCB(vector, func)				\
	DECLARE_IDTENTRY(vector, func)

# define DECLARE_IDTENTRY_VC(vector, func)				\
	idtentry_vc vector यंत्र_##func func

#अन्यथा
# define DECLARE_IDTENTRY_MCE(vector, func)				\
	DECLARE_IDTENTRY(vector, func)

/* No ASM emitted क्रम DF as this goes through a C shim */
# define DECLARE_IDTENTRY_DF(vector, func)

/* No ASM emitted क्रम XEN hypervisor callback */
# define DECLARE_IDTENTRY_XENCB(vector, func)

#पूर्ण_अगर

/* No ASM code emitted क्रम NMI */
#घोषणा DECLARE_IDTENTRY_NMI(vector, func)

/*
 * ASM code to emit the common vector entry stubs where each stub is
 * packed पूर्णांकo 8 bytes.
 *
 * Note, that the 'pushq imm8' is emitted via '.byte 0x6a, vector' because
 * GCC treats the local vector variable as अचिन्हित पूर्णांक and would expand
 * all vectors above 0x7F to a 5 byte push. The original code did an
 * adjusपंचांगent of the vector number to be in the चिन्हित byte range to aव्योम
 * this. While clever it's mindboggling counterपूर्णांकuitive and requires the
 * odd conversion back to a real vector number in the C entry poपूर्णांकs. Using
 * .byte achieves the same thing and the only fixup needed in the C entry
 * poपूर्णांक is to mask off the bits above bit 7 because the push is sign
 * extending.
 */
	.align 8
SYM_CODE_START(irq_entries_start)
    vector=FIRST_EXTERNAL_VECTOR
    .rept (FIRST_SYSTEM_VECTOR - FIRST_EXTERNAL_VECTOR)
	UNWIND_HINT_IRET_REGS
0 :
	.byte	0x6a, vector
	jmp	यंत्र_common_पूर्णांकerrupt
	nop
	/* Ensure that the above is 8 bytes max */
	. = 0b + 8
	vector = vector+1
    .endr
SYM_CODE_END(irq_entries_start)

#अगर_घोषित CONFIG_X86_LOCAL_APIC
	.align 8
SYM_CODE_START(spurious_entries_start)
    vector=FIRST_SYSTEM_VECTOR
    .rept (NR_VECTORS - FIRST_SYSTEM_VECTOR)
	UNWIND_HINT_IRET_REGS
0 :
	.byte	0x6a, vector
	jmp	यंत्र_spurious_पूर्णांकerrupt
	nop
	/* Ensure that the above is 8 bytes max */
	. = 0b + 8
	vector = vector+1
    .endr
SYM_CODE_END(spurious_entries_start)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * The actual entry poपूर्णांकs. Note that DECLARE_IDTENTRY*() serves two
 * purposes:
 *  - provide the function declarations when included from C-Code
 *  - emit the ASM stubs when included from entry_32/64.S
 *
 * This aव्योमs duplicate defines and ensures that everything is consistent.
 */

/*
 * Dummy trap number so the low level ASM macro vector number checks करो not
 * match which results in emitting plain IDTENTRY stubs without bells and
 * whistles.
 */
#घोषणा X86_TRAP_OTHER		0xFFFF

/* Simple exception entry poपूर्णांकs. No hardware error code */
DECLARE_IDTENTRY(X86_TRAP_DE,		exc_भागide_error);
DECLARE_IDTENTRY(X86_TRAP_OF,		exc_overflow);
DECLARE_IDTENTRY(X86_TRAP_BR,		exc_bounds);
DECLARE_IDTENTRY(X86_TRAP_NM,		exc_device_not_available);
DECLARE_IDTENTRY(X86_TRAP_OLD_MF,	exc_coproc_segment_overrun);
DECLARE_IDTENTRY(X86_TRAP_SPURIOUS,	exc_spurious_पूर्णांकerrupt_bug);
DECLARE_IDTENTRY(X86_TRAP_MF,		exc_coprocessor_error);
DECLARE_IDTENTRY(X86_TRAP_XF,		exc_simd_coprocessor_error);

/* 32bit software IRET trap. Do not emit ASM code */
DECLARE_IDTENTRY_SW(X86_TRAP_IRET,	iret_error);

/* Simple exception entries with error code pushed by hardware */
DECLARE_IDTENTRY_ERRORCODE(X86_TRAP_TS,	exc_invalid_tss);
DECLARE_IDTENTRY_ERRORCODE(X86_TRAP_NP,	exc_segment_not_present);
DECLARE_IDTENTRY_ERRORCODE(X86_TRAP_SS,	exc_stack_segment);
DECLARE_IDTENTRY_ERRORCODE(X86_TRAP_GP,	exc_general_protection);
DECLARE_IDTENTRY_ERRORCODE(X86_TRAP_AC,	exc_alignment_check);

/* Raw exception entries which need extra work */
DECLARE_IDTENTRY_RAW(X86_TRAP_UD,		exc_invalid_op);
DECLARE_IDTENTRY_RAW(X86_TRAP_BP,		exc_पूर्णांक3);
DECLARE_IDTENTRY_RAW_ERRORCODE(X86_TRAP_PF,	exc_page_fault);

#अगर_घोषित CONFIG_X86_MCE
#अगर_घोषित CONFIG_X86_64
DECLARE_IDTENTRY_MCE(X86_TRAP_MC,	exc_machine_check);
#अन्यथा
DECLARE_IDTENTRY_RAW(X86_TRAP_MC,	exc_machine_check);
#पूर्ण_अगर
#अगर_घोषित CONFIG_XEN_PV
DECLARE_IDTENTRY_RAW(X86_TRAP_MC,	xenpv_exc_machine_check);
#पूर्ण_अगर
#पूर्ण_अगर

/* NMI */

#अगर defined(CONFIG_X86_64) && IS_ENABLED(CONFIG_KVM_INTEL)
/*
 * Special NOIST entry poपूर्णांक क्रम VMX which invokes this on the kernel
 * stack. यंत्र_exc_nmi() requires an IST to work correctly vs. the NMI
 * 'executing' marker.
 *
 * On 32bit this just uses the regular NMI entry poपूर्णांक because 32-bit करोes
 * not have ISTs.
 */
DECLARE_IDTENTRY(X86_TRAP_NMI,		exc_nmi_noist);
#अन्यथा
#घोषणा यंत्र_exc_nmi_noist		यंत्र_exc_nmi
#पूर्ण_अगर

DECLARE_IDTENTRY_NMI(X86_TRAP_NMI,	exc_nmi);
#अगर_घोषित CONFIG_XEN_PV
DECLARE_IDTENTRY_RAW(X86_TRAP_NMI,	xenpv_exc_nmi);
#पूर्ण_अगर

/* #DB */
#अगर_घोषित CONFIG_X86_64
DECLARE_IDTENTRY_DEBUG(X86_TRAP_DB,	exc_debug);
#अन्यथा
DECLARE_IDTENTRY_RAW(X86_TRAP_DB,	exc_debug);
#पूर्ण_अगर
#अगर_घोषित CONFIG_XEN_PV
DECLARE_IDTENTRY_RAW(X86_TRAP_DB,	xenpv_exc_debug);
#पूर्ण_अगर

/* #DF */
DECLARE_IDTENTRY_DF(X86_TRAP_DF,	exc_द्विगुन_fault);
#अगर_घोषित CONFIG_XEN_PV
DECLARE_IDTENTRY_RAW_ERRORCODE(X86_TRAP_DF,	xenpv_exc_द्विगुन_fault);
#पूर्ण_अगर

/* #VC */
#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
DECLARE_IDTENTRY_VC(X86_TRAP_VC,	exc_vmm_communication);
#पूर्ण_अगर

#अगर_घोषित CONFIG_XEN_PV
DECLARE_IDTENTRY_XENCB(X86_TRAP_OTHER,	exc_xen_hypervisor_callback);
DECLARE_IDTENTRY_RAW(X86_TRAP_OTHER,	exc_xen_unknown_trap);
#पूर्ण_अगर

/* Device पूर्णांकerrupts common/spurious */
DECLARE_IDTENTRY_IRQ(X86_TRAP_OTHER,	common_पूर्णांकerrupt);
#अगर_घोषित CONFIG_X86_LOCAL_APIC
DECLARE_IDTENTRY_IRQ(X86_TRAP_OTHER,	spurious_पूर्णांकerrupt);
#पूर्ण_अगर

/* System vector entry poपूर्णांकs */
#अगर_घोषित CONFIG_X86_LOCAL_APIC
DECLARE_IDTENTRY_SYSVEC(ERROR_APIC_VECTOR,		sysvec_error_पूर्णांकerrupt);
DECLARE_IDTENTRY_SYSVEC(SPURIOUS_APIC_VECTOR,		sysvec_spurious_apic_पूर्णांकerrupt);
DECLARE_IDTENTRY_SYSVEC(LOCAL_TIMER_VECTOR,		sysvec_apic_समयr_पूर्णांकerrupt);
DECLARE_IDTENTRY_SYSVEC(X86_PLATFORM_IPI_VECTOR,	sysvec_x86_platक्रमm_ipi);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
DECLARE_IDTENTRY(RESCHEDULE_VECTOR,			sysvec_reschedule_ipi);
DECLARE_IDTENTRY_SYSVEC(IRQ_MOVE_CLEANUP_VECTOR,	sysvec_irq_move_cleanup);
DECLARE_IDTENTRY_SYSVEC(REBOOT_VECTOR,			sysvec_reboot);
DECLARE_IDTENTRY_SYSVEC(CALL_FUNCTION_SINGLE_VECTOR,	sysvec_call_function_single);
DECLARE_IDTENTRY_SYSVEC(CALL_FUNCTION_VECTOR,		sysvec_call_function);
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_LOCAL_APIC
# अगरdef CONFIG_X86_MCE_THRESHOLD
DECLARE_IDTENTRY_SYSVEC(THRESHOLD_APIC_VECTOR,		sysvec_threshold);
# endअगर

# अगरdef CONFIG_X86_MCE_AMD
DECLARE_IDTENTRY_SYSVEC(DEFERRED_ERROR_VECTOR,		sysvec_deferred_error);
# endअगर

# अगरdef CONFIG_X86_THERMAL_VECTOR
DECLARE_IDTENTRY_SYSVEC(THERMAL_APIC_VECTOR,		sysvec_thermal);
# endअगर

# अगरdef CONFIG_IRQ_WORK
DECLARE_IDTENTRY_SYSVEC(IRQ_WORK_VECTOR,		sysvec_irq_work);
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_KVM
DECLARE_IDTENTRY_SYSVEC(POSTED_INTR_VECTOR,		sysvec_kvm_posted_पूर्णांकr_ipi);
DECLARE_IDTENTRY_SYSVEC(POSTED_INTR_WAKEUP_VECTOR,	sysvec_kvm_posted_पूर्णांकr_wakeup_ipi);
DECLARE_IDTENTRY_SYSVEC(POSTED_INTR_NESTED_VECTOR,	sysvec_kvm_posted_पूर्णांकr_nested_ipi);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_HYPERV)
DECLARE_IDTENTRY_SYSVEC(HYPERVISOR_CALLBACK_VECTOR,	sysvec_hyperv_callback);
DECLARE_IDTENTRY_SYSVEC(HYPERV_REENLIGHTENMENT_VECTOR,	sysvec_hyperv_reenlightenment);
DECLARE_IDTENTRY_SYSVEC(HYPERV_STIMER0_VECTOR,	sysvec_hyperv_sसमयr0);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_ACRN_GUEST)
DECLARE_IDTENTRY_SYSVEC(HYPERVISOR_CALLBACK_VECTOR,	sysvec_acrn_hv_callback);
#पूर्ण_अगर

#अगर_घोषित CONFIG_XEN_PVHVM
DECLARE_IDTENTRY_SYSVEC(HYPERVISOR_CALLBACK_VECTOR,	sysvec_xen_hvm_callback);
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_GUEST
DECLARE_IDTENTRY_SYSVEC(HYPERVISOR_CALLBACK_VECTOR,	sysvec_kvm_asyncpf_पूर्णांकerrupt);
#पूर्ण_अगर

#अघोषित X86_TRAP_OTHER

#पूर्ण_अगर
