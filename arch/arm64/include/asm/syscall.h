<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_SYSCALL_H
#घोषणा __ASM_SYSCALL_H

#समावेश <uapi/linux/audit.h>
#समावेश <linux/compat.h>
#समावेश <linux/err.h>

प्रकार दीर्घ (*syscall_fn_t)(स्थिर काष्ठा pt_regs *regs);

बाह्य स्थिर syscall_fn_t sys_call_table[];

#अगर_घोषित CONFIG_COMPAT
बाह्य स्थिर syscall_fn_t compat_sys_call_table[];
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक syscall_get_nr(काष्ठा task_काष्ठा *task,
				 काष्ठा pt_regs *regs)
अणु
	वापस regs->syscallno;
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	regs->regs[0] = regs->orig_x0;
पूर्ण


अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ error = regs->regs[0];

	अगर (is_compat_thपढ़ो(task_thपढ़ो_info(task)))
		error = sign_extend64(error, 31);

	वापस IS_ERR_VALUE(error) ? error : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs->regs[0];
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	अगर (error)
		val = error;

	अगर (is_compat_thपढ़ो(task_thपढ़ो_info(task)))
		val = lower_32_bits(val);

	regs->regs[0] = val;
पूर्ण

#घोषणा SYSCALL_MAX_ARGS 6

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	args[0] = regs->orig_x0;
	args++;

	स_नकल(args, &regs->regs[1], 5 * माप(args[0]));
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 स्थिर अचिन्हित दीर्घ *args)
अणु
	regs->orig_x0 = args[0];
	args++;

	स_नकल(&regs->regs[1], args, 5 * माप(args[0]));
पूर्ण

/*
 * We करोn't care about endianness (__AUDIT_ARCH_LE bit) here because
 * AArch64 has the same प्रणाली calls both on little- and big- endian.
 */
अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	अगर (is_compat_thपढ़ो(task_thपढ़ो_info(task)))
		वापस AUDIT_ARCH_ARM;

	वापस AUDIT_ARCH_AARCH64;
पूर्ण

#पूर्ण_अगर	/* __ASM_SYSCALL_H */
