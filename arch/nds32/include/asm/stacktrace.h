<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2008-2018 Andes Technology Corporation */

#अगर_अघोषित __ASM_STACKTRACE_H
#घोषणा __ASM_STACKTRACE_H

/* Kernel callchain */
काष्ठा stackframe अणु
	अचिन्हित दीर्घ fp;
	अचिन्हित दीर्घ sp;
	अचिन्हित दीर्घ lp;
पूर्ण;

/*
 * काष्ठा frame_tail: User callchain
 * IMPORTANT:
 * This काष्ठा is used क्रम call-stack walking,
 * the order and types matters.
 * Do not use array, it only stores माप(poपूर्णांकer)
 *
 * The details can refer to arch/arm/kernel/perf_event.c
 */
काष्ठा frame_tail अणु
	अचिन्हित दीर्घ stack_fp;
	अचिन्हित दीर्घ stack_lp;
पूर्ण;

/* For User callchain with optimize क्रम size */
काष्ठा frame_tail_opt_size अणु
	अचिन्हित दीर्घ stack_r6;
	अचिन्हित दीर्घ stack_fp;
	अचिन्हित दीर्घ stack_gp;
	अचिन्हित दीर्घ stack_lp;
पूर्ण;

बाह्य व्योम
get_real_ret_addr(अचिन्हित दीर्घ *addr, काष्ठा task_काष्ठा *tsk, पूर्णांक *graph);

#पूर्ण_अगर /* __ASM_STACKTRACE_H */
