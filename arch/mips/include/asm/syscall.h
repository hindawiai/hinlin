<शैली गुरु>
/*
 * Access to user प्रणाली call parameters and results
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * See यंत्र-generic/syscall.h क्रम descriptions of what we must करो here.
 *
 * Copyright (C) 2012 Ralf Baechle <ralf@linux-mips.org>
 */

#अगर_अघोषित __ASM_MIPS_SYSCALL_H
#घोषणा __ASM_MIPS_SYSCALL_H

#समावेश <linux/compiler.h>
#समावेश <uapi/linux/audit.h>
#समावेश <linux/elf-em.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/unistd.h>

#अगर_अघोषित __NR_syscall /* Only defined अगर _MIPS_SIM == _MIPS_SIM_ABI32 */
#घोषणा __NR_syscall 4000
#पूर्ण_अगर

अटल अंतरभूत bool mips_syscall_is_indirect(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	/* O32 ABI syscall() - Either 64-bit with O32 or 32-bit */
	वापस (IS_ENABLED(CONFIG_32BIT) ||
		test_tsk_thपढ़ो_flag(task, TIF_32BIT_REGS)) &&
		(regs->regs[2] == __NR_syscall);
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_nr(काष्ठा task_काष्ठा *task,
				  काष्ठा pt_regs *regs)
अणु
	वापस current_thपढ़ो_info()->syscall;
पूर्ण

अटल अंतरभूत व्योम mips_syscall_update_nr(काष्ठा task_काष्ठा *task,
					  काष्ठा pt_regs *regs)
अणु
	/*
	 * v0 is the प्रणाली call number, except क्रम O32 ABI syscall(), where it
	 * ends up in a0.
	 */
	अगर (mips_syscall_is_indirect(task, regs))
		task_thपढ़ो_info(task)->syscall = regs->regs[4];
	अन्यथा
		task_thपढ़ो_info(task)->syscall = regs->regs[2];
पूर्ण

अटल अंतरभूत व्योम mips_get_syscall_arg(अचिन्हित दीर्घ *arg,
	काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ usp __maybe_unused = regs->regs[29];

	चयन (n) अणु
	हाल 0: हाल 1: हाल 2: हाल 3:
		*arg = regs->regs[4 + n];

		वापस;

#अगर_घोषित CONFIG_32BIT
	हाल 4: हाल 5: हाल 6: हाल 7:
		get_user(*arg, (पूर्णांक *)usp + n);
		वापस;
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
	हाल 4: हाल 5: हाल 6: हाल 7:
#अगर_घोषित CONFIG_MIPS32_O32
		अगर (test_tsk_thपढ़ो_flag(task, TIF_32BIT_REGS))
			get_user(*arg, (पूर्णांक *)usp + n);
		अन्यथा
#पूर्ण_अगर
			*arg = regs->regs[4 + n];

		वापस;
#पूर्ण_अगर

	शेष:
		BUG();
	पूर्ण

	unreachable();
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	वापस regs->regs[7] ? -regs->regs[2] : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs->regs[2];
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	/* Do nothing */
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	अगर (error) अणु
		regs->regs[2] = -error;
		regs->regs[7] = 1;
	पूर्ण अन्यथा अणु
		regs->regs[2] = val;
		regs->regs[7] = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक n = 6;

	/* O32 ABI syscall() */
	अगर (mips_syscall_is_indirect(task, regs))
		i++;

	जबतक (n--)
		mips_get_syscall_arg(args++, task, regs, i++);
पूर्ण

बाह्य स्थिर अचिन्हित दीर्घ sys_call_table[];
बाह्य स्थिर अचिन्हित दीर्घ sys32_call_table[];
बाह्य स्थिर अचिन्हित दीर्घ sysn32_call_table[];

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक arch = AUDIT_ARCH_MIPS;
#अगर_घोषित CONFIG_64BIT
	अगर (!test_tsk_thपढ़ो_flag(task, TIF_32BIT_REGS)) अणु
		arch |= __AUDIT_ARCH_64BIT;
		/* N32 sets only TIF_32BIT_ADDR */
		अगर (test_tsk_thपढ़ो_flag(task, TIF_32BIT_ADDR))
			arch |= __AUDIT_ARCH_CONVENTION_MIPS64_N32;
	पूर्ण
#पूर्ण_अगर
#अगर defined(__LITTLE_ENDIAN)
	arch |=  __AUDIT_ARCH_LE;
#पूर्ण_अगर
	वापस arch;
पूर्ण

#पूर्ण_अगर	/* __ASM_MIPS_SYSCALL_H */
