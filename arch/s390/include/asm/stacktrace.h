<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_STACKTRACE_H
#घोषणा _ASM_S390_STACKTRACE_H

#समावेश <linux/uaccess.h>
#समावेश <linux/ptrace.h>
#समावेश <यंत्र/चयन_to.h>

क्रमागत stack_type अणु
	STACK_TYPE_UNKNOWN,
	STACK_TYPE_TASK,
	STACK_TYPE_IRQ,
	STACK_TYPE_NODAT,
	STACK_TYPE_RESTART,
	STACK_TYPE_MCCK,
पूर्ण;

काष्ठा stack_info अणु
	क्रमागत stack_type type;
	अचिन्हित दीर्घ begin, end;
पूर्ण;

स्थिर अक्षर *stack_type_name(क्रमागत stack_type type);
पूर्णांक get_stack_info(अचिन्हित दीर्घ sp, काष्ठा task_काष्ठा *task,
		   काष्ठा stack_info *info, अचिन्हित दीर्घ *visit_mask);

अटल अंतरभूत bool on_stack(काष्ठा stack_info *info,
			    अचिन्हित दीर्घ addr, माप_प्रकार len)
अणु
	अगर (info->type == STACK_TYPE_UNKNOWN)
		वापस false;
	अगर (addr + len < addr)
		वापस false;
	वापस addr >= info->begin && addr + len <= info->end;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ get_stack_poपूर्णांकer(काष्ठा task_काष्ठा *task,
						       काष्ठा pt_regs *regs)
अणु
	अगर (regs)
		वापस (अचिन्हित दीर्घ) kernel_stack_poपूर्णांकer(regs);
	अगर (task == current)
		वापस current_stack_poपूर्णांकer();
	वापस (अचिन्हित दीर्घ) task->thपढ़ो.ksp;
पूर्ण

/*
 * Stack layout of a C stack frame.
 */
#अगर_अघोषित __PACK_STACK
काष्ठा stack_frame अणु
	अचिन्हित दीर्घ back_chain;
	अचिन्हित दीर्घ empty1[5];
	अचिन्हित दीर्घ gprs[10];
	अचिन्हित पूर्णांक  empty2[8];
पूर्ण;
#अन्यथा
काष्ठा stack_frame अणु
	अचिन्हित दीर्घ empty1[5];
	अचिन्हित पूर्णांक  empty2[8];
	अचिन्हित दीर्घ gprs[10];
	अचिन्हित दीर्घ back_chain;
पूर्ण;
#पूर्ण_अगर

/*
 * Unlike current_stack_poपूर्णांकer() which simply वापसs current value of %r15
 * current_frame_address() वापसs function stack frame address, which matches
 * %r15 upon function invocation. It may dअगरfer from %r15 later अगर function
 * allocates stack क्रम local variables or new stack frame to call other
 * functions.
 */
#घोषणा current_frame_address()						\
	((अचिन्हित दीर्घ)__builtin_frame_address(0) -			\
	 दुरत्व(काष्ठा stack_frame, back_chain))

#घोषणा CALL_ARGS_0()							\
	रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("2")
#घोषणा CALL_ARGS_1(arg1)						\
	रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("2") = (अचिन्हित दीर्घ)(arg1)
#घोषणा CALL_ARGS_2(arg1, arg2)						\
	CALL_ARGS_1(arg1);						\
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("3") = (अचिन्हित दीर्घ)(arg2)
#घोषणा CALL_ARGS_3(arg1, arg2, arg3)					\
	CALL_ARGS_2(arg1, arg2);					\
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("4") = (अचिन्हित दीर्घ)(arg3)
#घोषणा CALL_ARGS_4(arg1, arg2, arg3, arg4)				\
	CALL_ARGS_3(arg1, arg2, arg3);					\
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("5") = (अचिन्हित दीर्घ)(arg4)
#घोषणा CALL_ARGS_5(arg1, arg2, arg3, arg4, arg5)			\
	CALL_ARGS_4(arg1, arg2, arg3, arg4);				\
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("6") = (अचिन्हित दीर्घ)(arg5)

#घोषणा CALL_FMT_0 "=&d" (r2) :
#घोषणा CALL_FMT_1 "+&d" (r2) :
#घोषणा CALL_FMT_2 CALL_FMT_1 "d" (r3),
#घोषणा CALL_FMT_3 CALL_FMT_2 "d" (r4),
#घोषणा CALL_FMT_4 CALL_FMT_3 "d" (r5),
#घोषणा CALL_FMT_5 CALL_FMT_4 "d" (r6),

#घोषणा CALL_CLOBBER_5 "0", "1", "14", "cc", "memory"
#घोषणा CALL_CLOBBER_4 CALL_CLOBBER_5
#घोषणा CALL_CLOBBER_3 CALL_CLOBBER_4, "5"
#घोषणा CALL_CLOBBER_2 CALL_CLOBBER_3, "4"
#घोषणा CALL_CLOBBER_1 CALL_CLOBBER_2, "3"
#घोषणा CALL_CLOBBER_0 CALL_CLOBBER_1

#घोषणा CALL_ON_STACK(fn, stack, nr, args...)				\
(अणु									\
	अचिन्हित दीर्घ frame = current_frame_address();			\
	CALL_ARGS_##nr(args);						\
	अचिन्हित दीर्घ prev;						\
									\
	यंत्र अस्थिर(							\
		"	la	%[_prev],0(15)\n"			\
		"	lg	15,%[_stack]\n"				\
		"	stg	%[_frame],%[_bc](15)\n"			\
		"	brasl	14,%[_fn]\n"				\
		"	la	15,0(%[_prev])\n"			\
		: [_prev] "=&a" (prev), CALL_FMT_##nr			\
		  [_stack] "R" (stack),					\
		  [_bc] "i" (दुरत्व(काष्ठा stack_frame, back_chain)),	\
		  [_frame] "d" (frame),					\
		  [_fn] "X" (fn) : CALL_CLOBBER_##nr);			\
	r2;								\
पूर्ण)

#घोषणा CALL_ON_STACK_NORETURN(fn, stack)				\
(अणु									\
	यंत्र अस्थिर(							\
		"	la	15,0(%[_stack])\n"			\
		"	xc	%[_bc](8,15),%[_bc](15)\n"		\
		"	brasl	14,%[_fn]\n"				\
		::[_bc] "i" (दुरत्व(काष्ठा stack_frame, back_chain)),	\
		  [_stack] "a" (stack), [_fn] "X" (fn));		\
	BUG();								\
पूर्ण)

#पूर्ण_अगर /* _ASM_S390_STACKTRACE_H */
