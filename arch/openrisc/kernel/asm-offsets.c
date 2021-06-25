<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC यंत्र-offsets.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 *
 * This program is used to generate definitions needed by
 * assembly language modules.
 *
 * We use the technique used in the OSF Mach kernel code:
 * generate यंत्र statements containing #घोषणाs,
 * compile this file to assembler, and then extract the
 * #घोषणाs from the assembly-language output.
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/kbuild.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>

पूर्णांक मुख्य(व्योम)
अणु
	/* offsets पूर्णांकo the task_काष्ठा */
	DEFINE(TASK_STATE, दुरत्व(काष्ठा task_काष्ठा, state));
	DEFINE(TASK_FLAGS, दुरत्व(काष्ठा task_काष्ठा, flags));
	DEFINE(TASK_PTRACE, दुरत्व(काष्ठा task_काष्ठा, ptrace));
	DEFINE(TASK_THREAD, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो));
	DEFINE(TASK_MM, दुरत्व(काष्ठा task_काष्ठा, mm));
	DEFINE(TASK_ACTIVE_MM, दुरत्व(काष्ठा task_काष्ठा, active_mm));

	/* offsets पूर्णांकo thपढ़ो_info */
	DEFINE(TI_TASK, दुरत्व(काष्ठा thपढ़ो_info, task));
	DEFINE(TI_FLAGS, दुरत्व(काष्ठा thपढ़ो_info, flags));
	DEFINE(TI_PREEMPT, दुरत्व(काष्ठा thपढ़ो_info, preempt_count));
	DEFINE(TI_KSP, दुरत्व(काष्ठा thपढ़ो_info, ksp));

	DEFINE(PT_SIZE, माप(काष्ठा pt_regs));

	/* Interrupt रेजिस्टर frame */
	DEFINE(STACK_FRAME_OVERHEAD, STACK_FRAME_OVERHEAD);
	DEFINE(INT_FRAME_SIZE, STACK_FRAME_OVERHEAD + माप(काष्ठा pt_regs));

	DEFINE(NUM_USER_SEGMENTS, TASK_SIZE >> 28);
	वापस 0;
पूर्ण
