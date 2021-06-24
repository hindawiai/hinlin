<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2009  Matt Fleming
 *
 * Based on:
 *	The x86 implementation - arch/x86/include/यंत्र/stacktrace.h
 */
#अगर_अघोषित _ASM_SH_STACKTRACE_H
#घोषणा _ASM_SH_STACKTRACE_H

/* Generic stack tracer with callbacks */

काष्ठा stacktrace_ops अणु
	व्योम (*address)(व्योम *data, अचिन्हित दीर्घ address, पूर्णांक reliable);
पूर्ण;

व्योम dump_trace(काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs,
		अचिन्हित दीर्घ *stack,
		स्थिर काष्ठा stacktrace_ops *ops, व्योम *data);

#पूर्ण_अगर /* _ASM_SH_STACKTRACE_H */
