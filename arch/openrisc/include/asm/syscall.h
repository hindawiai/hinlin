<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_SYSCALL_H__
#घोषणा __ASM_OPENRISC_SYSCALL_H__

#समावेश <uapi/linux/audit.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>

अटल अंतरभूत पूर्णांक
syscall_get_nr(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस regs->orig_gpr11;
पूर्ण

अटल अंतरभूत व्योम
syscall_rollback(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	regs->gpr[11] = regs->orig_gpr11;
पूर्ण

अटल अंतरभूत दीर्घ
syscall_get_error(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस IS_ERR_VALUE(regs->gpr[11]) ? regs->gpr[11] : 0;
पूर्ण

अटल अंतरभूत दीर्घ
syscall_get_वापस_value(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस regs->gpr[11];
पूर्ण

अटल अंतरभूत व्योम
syscall_set_वापस_value(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
			 पूर्णांक error, दीर्घ val)
अणु
	regs->gpr[11] = (दीर्घ) error ?: val;
पूर्ण

अटल अंतरभूत व्योम
syscall_get_arguments(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
		      अचिन्हित दीर्घ *args)
अणु
	स_नकल(args, &regs->gpr[3], 6 * माप(args[0]));
पूर्ण

अटल अंतरभूत व्योम
syscall_set_arguments(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
		      स्थिर अचिन्हित दीर्घ *args)
अणु
	स_नकल(&regs->gpr[3], args, 6 * माप(args[0]));
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	वापस AUDIT_ARCH_OPENRISC;
पूर्ण
#पूर्ण_अगर
