<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Access to user प्रणाली call parameters and results
 *
 * Copyright (C) 2008 Red Hat, Inc.  All rights reserved.
 *
 * See यंत्र-generic/syscall.h क्रम descriptions of what we must करो here.
 */

#अगर_अघोषित _ASM_SYSCALL_H
#घोषणा _ASM_SYSCALL_H	1

#समावेश <uapi/linux/audit.h>
#समावेश <linux/sched.h>
#समावेश <linux/thपढ़ो_info.h>

/* ftrace syscalls requires exporting the sys_call_table */
बाह्य स्थिर अचिन्हित दीर्घ sys_call_table[];
बाह्य स्थिर अचिन्हित दीर्घ compat_sys_call_table[];

अटल अंतरभूत पूर्णांक syscall_get_nr(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	/*
	 * Note that we are वापसing an पूर्णांक here. That means 0xffffffff, ie.
	 * 32-bit negative 1, will be पूर्णांकerpreted as -1 on a 64-bit kernel.
	 * This is important क्रम seccomp so that compat tasks can set r0 = -1
	 * to reject the syscall.
	 */
	अगर (trap_is_syscall(regs))
		वापस regs->gpr[0];
	अन्यथा
		वापस -1;
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	regs->gpr[3] = regs->orig_gpr3;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	अगर (trap_is_scv(regs)) अणु
		अचिन्हित दीर्घ error = regs->gpr[3];

		वापस IS_ERR_VALUE(error) ? error : 0;
	पूर्ण अन्यथा अणु
		/*
		 * If the प्रणाली call failed,
		 * regs->gpr[3] contains a positive ERRORCODE.
		 */
		वापस (regs->ccr & 0x10000000UL) ? -regs->gpr[3] : 0;
	पूर्ण
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs->gpr[3];
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	अगर (trap_is_scv(regs)) अणु
		regs->gpr[3] = (दीर्घ) error ?: val;
	पूर्ण अन्यथा अणु
		/*
		 * In the general हाल it's not obvious that we must deal with
		 * CCR here, as the syscall निकास path will also करो that क्रम us.
		 * However there are some places, eg. the संकेत code, which
		 * check ccr to decide अगर the value in r3 is actually an error.
		 */
		अगर (error) अणु
			regs->ccr |= 0x10000000L;
			regs->gpr[3] = error;
		पूर्ण अन्यथा अणु
			regs->ccr &= ~0x10000000L;
			regs->gpr[3] = val;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	अचिन्हित दीर्घ val, mask = -1UL;
	अचिन्हित पूर्णांक n = 6;

#अगर_घोषित CONFIG_COMPAT
	अगर (test_tsk_thपढ़ो_flag(task, TIF_32BIT))
		mask = 0xffffffff;
#पूर्ण_अगर
	जबतक (n--) अणु
		अगर (n == 0)
			val = regs->orig_gpr3;
		अन्यथा
			val = regs->gpr[3 + n];

		args[n] = val & mask;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 स्थिर अचिन्हित दीर्घ *args)
अणु
	स_नकल(&regs->gpr[3], args, 6 * माप(args[0]));

	/* Also copy the first argument पूर्णांकo orig_gpr3 */
	regs->orig_gpr3 = args[0];
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक arch;

	अगर (IS_ENABLED(CONFIG_PPC64) && !test_tsk_thपढ़ो_flag(task, TIF_32BIT))
		arch = AUDIT_ARCH_PPC64;
	अन्यथा
		arch = AUDIT_ARCH_PPC;

#अगर_घोषित __LITTLE_ENDIAN__
	arch |= __AUDIT_ARCH_LE;
#पूर्ण_अगर
	वापस arch;
पूर्ण
#पूर्ण_अगर	/* _ASM_SYSCALL_H */
