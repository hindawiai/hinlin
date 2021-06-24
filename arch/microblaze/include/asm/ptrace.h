<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */
#अगर_अघोषित _ASM_MICROBLAZE_PTRACE_H
#घोषणा _ASM_MICROBLAZE_PTRACE_H

#समावेश <uapi/यंत्र/ptrace.h>

#अगर_अघोषित __ASSEMBLY__
#घोषणा kernel_mode(regs)		((regs)->pt_mode)
#घोषणा user_mode(regs)			(!kernel_mode(regs))

#घोषणा inकाष्ठाion_poपूर्णांकer(regs)	((regs)->pc)
#घोषणा profile_pc(regs)		inकाष्ठाion_poपूर्णांकer(regs)
#घोषणा user_stack_poपूर्णांकer(regs)	((regs)->r1)

अटल अंतरभूत दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस regs->r3;
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_MICROBLAZE_PTRACE_H */
