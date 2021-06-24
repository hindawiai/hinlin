<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_ARC_SWITCH_TO_H
#घोषणा _ASM_ARC_SWITCH_TO_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/sched.h>
#समावेश <यंत्र/dsp-impl.h>
#समावेश <यंत्र/fpu.h>

काष्ठा task_काष्ठा *__चयन_to(काष्ठा task_काष्ठा *p, काष्ठा task_काष्ठा *n);

#घोषणा चयन_to(prev, next, last)	\
करो अणु					\
	dsp_save_restore(prev, next);	\
	fpu_save_restore(prev, next);	\
	last = __चयन_to(prev, next);\
	mb();				\
पूर्ण जबतक (0)

#पूर्ण_अगर

#पूर्ण_अगर
