<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_STACKTRACE_H
#घोषणा _ASM_STACKTRACE_H

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश <linux/stringअगरy.h>

#अगर_घोषित CONFIG_KALLSYMS
बाह्य पूर्णांक raw_show_trace;
बाह्य अचिन्हित दीर्घ unwind_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *sp,
				  अचिन्हित दीर्घ pc, अचिन्हित दीर्घ *ra);
बाह्य अचिन्हित दीर्घ unwind_stack_by_address(अचिन्हित दीर्घ stack_page,
					     अचिन्हित दीर्घ *sp,
					     अचिन्हित दीर्घ pc,
					     अचिन्हित दीर्घ *ra);
#अन्यथा
#घोषणा raw_show_trace 1
अटल अंतरभूत अचिन्हित दीर्घ unwind_stack(काष्ठा task_काष्ठा *task,
	अचिन्हित दीर्घ *sp, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ *ra)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा STR_PTR_LA    __stringअगरy(PTR_LA)
#घोषणा STR_LONG_S    __stringअगरy(LONG_S)
#घोषणा STR_LONG_L    __stringअगरy(LONG_L)
#घोषणा STR_LONGSIZE  __stringअगरy(LONGSIZE)

#घोषणा STORE_ONE_REG(r) \
    STR_LONG_S   " $" __stringअगरy(r)",("STR_LONGSIZE"*"__stringअगरy(r)")(%1)\n\t"

अटल __always_अंतरभूत व्योम prepare_frametrace(काष्ठा pt_regs *regs)
अणु
#अगर_अघोषित CONFIG_KALLSYMS
	/*
	 * Remove any garbage that may be in regs (specially func
	 * addresses) to aव्योम show_raw_backtrace() to report them
	 */
	स_रखो(regs, 0, माप(*regs));
#पूर्ण_अगर
	__यंत्र__ __अस्थिर__(
		".set push\n\t"
		".set noat\n\t"
		/* Store $1 so we can use it */
		STR_LONG_S " $1,"STR_LONGSIZE"(%1)\n\t"
		/* Store the PC */
		"1: " STR_PTR_LA " $1, 1b\n\t"
		STR_LONG_S " $1,%0\n\t"
		STORE_ONE_REG(2)
		STORE_ONE_REG(3)
		STORE_ONE_REG(4)
		STORE_ONE_REG(5)
		STORE_ONE_REG(6)
		STORE_ONE_REG(7)
		STORE_ONE_REG(8)
		STORE_ONE_REG(9)
		STORE_ONE_REG(10)
		STORE_ONE_REG(11)
		STORE_ONE_REG(12)
		STORE_ONE_REG(13)
		STORE_ONE_REG(14)
		STORE_ONE_REG(15)
		STORE_ONE_REG(16)
		STORE_ONE_REG(17)
		STORE_ONE_REG(18)
		STORE_ONE_REG(19)
		STORE_ONE_REG(20)
		STORE_ONE_REG(21)
		STORE_ONE_REG(22)
		STORE_ONE_REG(23)
		STORE_ONE_REG(24)
		STORE_ONE_REG(25)
		STORE_ONE_REG(26)
		STORE_ONE_REG(27)
		STORE_ONE_REG(28)
		STORE_ONE_REG(29)
		STORE_ONE_REG(30)
		STORE_ONE_REG(31)
		/* Restore $1 */
		STR_LONG_L " $1,"STR_LONGSIZE"(%1)\n\t"
		".set pop\n\t"
		: "=m" (regs->cp0_epc)
		: "r" (regs->regs)
		: "memory");
पूर्ण

#पूर्ण_अगर /* _ASM_STACKTRACE_H */
