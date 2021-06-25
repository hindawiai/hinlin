<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 1999, 2000  Niibe Yutaka
 */
#अगर_अघोषित _UAPI__ASM_SH_PTRACE_H
#घोषणा _UAPI__ASM_SH_PTRACE_H


#घोषणा PTRACE_GETREGS		12	/* General रेजिस्टरs */
#घोषणा PTRACE_SETREGS		13

#घोषणा PTRACE_GETFPREGS	14	/* FPU रेजिस्टरs */
#घोषणा PTRACE_SETFPREGS	15

#घोषणा PTRACE_GETFDPIC		31	/* get the ELF fdpic loadmap address */

#घोषणा PTRACE_GETFDPIC_EXEC	0	/* [addr] request the executable loadmap */
#घोषणा PTRACE_GETFDPIC_INTERP	1	/* [addr] request the पूर्णांकerpreter loadmap */

#घोषणा	PTRACE_GETDSPREGS	55	/* DSP रेजिस्टरs */
#घोषणा	PTRACE_SETDSPREGS	56

#घोषणा PT_TEXT_END_ADDR	240
#घोषणा PT_TEXT_ADDR		244	/* &(काष्ठा user)->start_code */
#घोषणा PT_DATA_ADDR		248	/* &(काष्ठा user)->start_data */
#घोषणा PT_TEXT_LEN		252

#समावेश <यंत्र/ptrace_32.h>

#पूर्ण_अगर /* _UAPI__ASM_SH_PTRACE_H */
