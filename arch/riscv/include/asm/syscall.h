<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008-2009 Red Hat, Inc.  All rights reserved.
 * Copyright 2010 Tilera Corporation. All Rights Reserved.
 * Copyright 2015 Regents of the University of Calअगरornia, Berkeley
 *
 * See यंत्र-generic/syscall.h क्रम descriptions of what we must करो here.
 */

#अगर_अघोषित _ASM_RISCV_SYSCALL_H
#घोषणा _ASM_RISCV_SYSCALL_H

#समावेश <uapi/linux/audit.h>
#समावेश <linux/sched.h>
#समावेश <linux/err.h>

/* The array of function poपूर्णांकers क्रम syscalls. */
बाह्य व्योम * स्थिर sys_call_table[];

/*
 * Only the low 32 bits of orig_r0 are meaningful, so we वापस पूर्णांक.
 * This importantly ignores the high bits on 64-bit, so comparisons
 * sign-extend the low 32 bits.
 */
अटल अंतरभूत पूर्णांक syscall_get_nr(काष्ठा task_काष्ठा *task,
				 काष्ठा pt_regs *regs)
अणु
	वापस regs->a7;
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
        regs->a0 = regs->orig_a0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ error = regs->a0;

	वापस IS_ERR_VALUE(error) ? error : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs->a0;
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	regs->a0 = (दीर्घ) error ?: val;
पूर्ण

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	args[0] = regs->orig_a0;
	args++;
	स_नकल(args, &regs->a1, 5 * माप(args[0]));
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 स्थिर अचिन्हित दीर्घ *args)
अणु
	regs->orig_a0 = args[0];
	args++;
	स_नकल(&regs->a1, args, 5 * माप(regs->a1));
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित CONFIG_64BIT
	वापस AUDIT_ARCH_RISCV64;
#अन्यथा
	वापस AUDIT_ARCH_RISCV32;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर	/* _ASM_RISCV_SYSCALL_H */
