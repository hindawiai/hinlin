<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_IRQ_STACK_H
#घोषणा _ASM_X86_IRQ_STACK_H

#समावेश <linux/ptrace.h>

#समावेश <यंत्र/processor.h>

#अगर_घोषित CONFIG_X86_64

/*
 * Macro to अंतरभूत चयनing to an पूर्णांकerrupt stack and invoking function
 * calls from there. The following rules apply:
 *
 * - Ordering:
 *
 *   1. Write the stack poपूर्णांकer पूर्णांकo the top most place of the irq
 *	stack. This ensures that the various unwinders can link back to the
 *	original stack.
 *
 *   2. Switch the stack poपूर्णांकer to the top of the irq stack.
 *
 *   3. Invoke whatever needs to be करोne (@यंत्र_call argument)
 *
 *   4. Pop the original stack poपूर्णांकer from the top of the irq stack
 *	which brings it back to the original stack where it left off.
 *
 * - Function invocation:
 *
 *   To allow flexible usage of the macro, the actual function code including
 *   the store of the arguments in the call ABI रेजिस्टरs is handed in via
 *   the @यंत्र_call argument.
 *
 * - Local variables:
 *
 *   @tos:
 *	The @tos variable holds a poपूर्णांकer to the top of the irq stack and
 *	_must_ be allocated in a non-callee saved रेजिस्टर as this is a
 *	restriction coming from objtool.
 *
 *	Note, that (tos) is both in input and output स्थिरraपूर्णांकs to ensure
 *	that the compiler करोes not assume that R11 is left untouched in
 *	हाल this macro is used in some place where the per cpu पूर्णांकerrupt
 *	stack poपूर्णांकer is used again afterwards
 *
 * - Function arguments:
 *	The function argument(s), अगर any, have to be defined in रेजिस्टर
 *	variables at the place where this is invoked. Storing the
 *	argument(s) in the proper रेजिस्टर(s) is part of the @यंत्र_call
 *
 * - Constraपूर्णांकs:
 *
 *   The स्थिरraपूर्णांकs have to be करोne very carefully because the compiler
 *   करोes not know about the assembly call.
 *
 *   output:
 *     As करोcumented alपढ़ोy above the @tos variable is required to be in
 *     the output स्थिरraपूर्णांकs to make the compiler aware that R11 cannot be
 *     reused after the यंत्र() statement.
 *
 *     For builds with CONFIG_UNWIND_FRAME_POINTER ASM_CALL_CONSTRAINT is
 *     required as well as this prevents certain creative GCC variants from
 *     misplacing the ASM code.
 *
 *  input:
 *    - func:
 *	  Immediate, which tells the compiler that the function is referenced.
 *
 *    - tos:
 *	  Register. The actual रेजिस्टर is defined by the variable declaration.
 *
 *    - function arguments:
 *	  The स्थिरraपूर्णांकs are handed in via the 'argconstr' argument list. They
 *	  describe the रेजिस्टर arguments which are used in @यंत्र_call.
 *
 *  clobbers:
 *     Function calls can clobber anything except the callee-saved
 *     रेजिस्टरs. Tell the compiler.
 */
#घोषणा call_on_irqstack(func, यंत्र_call, argस्थिरr...)			\
अणु									\
	रेजिस्टर व्योम *tos यंत्र("r11");					\
									\
	tos = ((व्योम *)__this_cpu_पढ़ो(hardirq_stack_ptr));		\
									\
	यंत्र_अंतरभूत अस्थिर(						\
	"movq	%%rsp, (%[tos])				\n"		\
	"movq	%[tos], %%rsp				\n"		\
									\
	यंत्र_call							\
									\
	"popq	%%rsp					\n"		\
									\
	: "+r" (tos), ASM_CALL_CONSTRAINT				\
	: [__func] "i" (func), [tos] "r" (tos) argस्थिरr		\
	: "cc", "rax", "rcx", "rdx", "rsi", "rdi", "r8", "r9", "r10",	\
	  "memory"							\
	);								\
पूर्ण

/* Macros to निश्चित type correctness क्रम run_*_on_irqstack macros */
#घोषणा निश्चित_function_type(func, proto)				\
	अटल_निश्चित(__builtin_types_compatible_p(typeof(&func), proto))

#घोषणा निश्चित_arg_type(arg, proto)					\
	अटल_निश्चित(__builtin_types_compatible_p(typeof(arg), proto))

/*
 * Macro to invoke प्रणाली vector and device पूर्णांकerrupt C handlers.
 */
#घोषणा call_on_irqstack_cond(func, regs, यंत्र_call, स्थिरr, c_args...)	\
अणु									\
	/*								\
	 * User mode entry and पूर्णांकerrupt on the irq stack करो not	\
	 * चयन stacks. If from user mode the task stack is empty.	\
	 */								\
	अगर (user_mode(regs) || __this_cpu_पढ़ो(hardirq_stack_inuse)) अणु	\
		irq_enter_rcu();					\
		func(c_args);						\
		irq_निकास_rcu();						\
	पूर्ण अन्यथा अणु							\
		/*							\
		 * Mark the irq stack inuse _beक्रमe_ and unmark _after_	\
		 * चयनing stacks. Interrupts are disabled in both	\
		 * places. Invoke the stack चयन macro with the call	\
		 * sequence which matches the above direct invocation.	\
		 */							\
		__this_cpu_ग_लिखो(hardirq_stack_inuse, true);		\
		call_on_irqstack(func, यंत्र_call, स्थिरr);		\
		__this_cpu_ग_लिखो(hardirq_stack_inuse, false);		\
	पूर्ण								\
पूर्ण

/*
 * Function call sequence क्रम __call_on_irqstack() क्रम प्रणाली vectors.
 *
 * Note that irq_enter_rcu() and irq_निकास_rcu() करो not use the input
 * mechanism because these functions are global and cannot be optimized out
 * when compiling a particular source file which uses one of these macros.
 *
 * The argument (regs) करोes not need to be pushed or stashed in a callee
 * saved रेजिस्टर to be safe vs. the irq_enter_rcu() call because the
 * clobbers alपढ़ोy prevent the compiler from storing it in a callee
 * clobbered रेजिस्टर. As the compiler has to preserve @regs क्रम the final
 * call to idtentry_निकास() anyway, it's likely that it करोes not cause extra
 * efक्रमt क्रम this यंत्र magic.
 */
#घोषणा ASM_CALL_SYSVEC							\
	"call irq_enter_rcu				\n"		\
	"movq	%[arg1], %%rdi				\n"		\
	"call %P[__func]				\n"		\
	"call irq_exit_rcu				\n"

#घोषणा SYSVEC_CONSTRAINTS	, [arg1] "r" (regs)

#घोषणा run_sysvec_on_irqstack_cond(func, regs)				\
अणु									\
	निश्चित_function_type(func, व्योम (*)(काष्ठा pt_regs *));		\
	निश्चित_arg_type(regs, काष्ठा pt_regs *);			\
									\
	call_on_irqstack_cond(func, regs, ASM_CALL_SYSVEC,		\
			      SYSVEC_CONSTRAINTS, regs);		\
पूर्ण

/*
 * As in ASM_CALL_SYSVEC above the clobbers क्रमce the compiler to store
 * @regs and @vector in callee saved रेजिस्टरs.
 */
#घोषणा ASM_CALL_IRQ							\
	"call irq_enter_rcu				\n"		\
	"movq	%[arg1], %%rdi				\n"		\
	"movl	%[arg2], %%esi				\n"		\
	"call %P[__func]				\n"		\
	"call irq_exit_rcu				\n"

#घोषणा IRQ_CONSTRAINTS	, [arg1] "r" (regs), [arg2] "r" (vector)

#घोषणा run_irq_on_irqstack_cond(func, regs, vector)			\
अणु									\
	निश्चित_function_type(func, व्योम (*)(काष्ठा pt_regs *, u32));	\
	निश्चित_arg_type(regs, काष्ठा pt_regs *);			\
	निश्चित_arg_type(vector, u32);					\
									\
	call_on_irqstack_cond(func, regs, ASM_CALL_IRQ,			\
			      IRQ_CONSTRAINTS, regs, vector);		\
पूर्ण

#घोषणा ASM_CALL_SOFTIRQ						\
	"call %P[__func]				\n"

/*
 * Macro to invoke __करो_softirq on the irq stack. This is only called from
 * task context when bottom halves are about to be reenabled and soft
 * पूर्णांकerrupts are pending to be processed. The पूर्णांकerrupt stack cannot be in
 * use here.
 */
#घोषणा करो_softirq_own_stack()						\
अणु									\
	__this_cpu_ग_लिखो(hardirq_stack_inuse, true);			\
	call_on_irqstack(__करो_softirq, ASM_CALL_SOFTIRQ);		\
	__this_cpu_ग_लिखो(hardirq_stack_inuse, false);			\
पूर्ण

#अन्यथा /* CONFIG_X86_64 */
/* System vector handlers always run on the stack they पूर्णांकerrupted. */
#घोषणा run_sysvec_on_irqstack_cond(func, regs)				\
अणु									\
	irq_enter_rcu();						\
	func(regs);							\
	irq_निकास_rcu();							\
पूर्ण

/* Switches to the irq stack within func() */
#घोषणा run_irq_on_irqstack_cond(func, regs, vector)			\
अणु									\
	irq_enter_rcu();						\
	func(regs, vector);						\
	irq_निकास_rcu();							\
पूर्ण

#पूर्ण_अगर /* !CONFIG_X86_64 */

#पूर्ण_अगर
