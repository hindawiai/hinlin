<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2005 Mips Technologies
 * Author: Chris Dearman, chris@mips.com derived from fpu.h
 */
#अगर_अघोषित _ASM_DSP_H
#घोषणा _ASM_DSP_H

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/hazards.h>
#समावेश <यंत्र/mipsregs.h>

#घोषणा DSP_DEFAULT	0x00000000
#घोषणा DSP_MASK	0x3f

#घोषणा __enable_dsp_hazard()						\
करो अणु									\
	यंत्र("_ehb");							\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम __init_dsp(व्योम)
अणु
	mthi1(0);
	mtlo1(0);
	mthi2(0);
	mtlo2(0);
	mthi3(0);
	mtlo3(0);
	wrdsp(DSP_DEFAULT, DSP_MASK);
पूर्ण

अटल अंतरभूत व्योम init_dsp(व्योम)
अणु
	अगर (cpu_has_dsp)
		__init_dsp();
पूर्ण

#घोषणा __save_dsp(tsk)							\
करो अणु									\
	tsk->thपढ़ो.dsp.dspr[0] = mfhi1();				\
	tsk->thपढ़ो.dsp.dspr[1] = mflo1();				\
	tsk->thपढ़ो.dsp.dspr[2] = mfhi2();				\
	tsk->thपढ़ो.dsp.dspr[3] = mflo2();				\
	tsk->thपढ़ो.dsp.dspr[4] = mfhi3();				\
	tsk->thपढ़ो.dsp.dspr[5] = mflo3();				\
	tsk->thपढ़ो.dsp.dspcontrol = rddsp(DSP_MASK);			\
पूर्ण जबतक (0)

#घोषणा save_dsp(tsk)							\
करो अणु									\
	अगर (cpu_has_dsp)						\
		__save_dsp(tsk);					\
पूर्ण जबतक (0)

#घोषणा __restore_dsp(tsk)						\
करो अणु									\
	mthi1(tsk->thपढ़ो.dsp.dspr[0]);					\
	mtlo1(tsk->thपढ़ो.dsp.dspr[1]);					\
	mthi2(tsk->thपढ़ो.dsp.dspr[2]);					\
	mtlo2(tsk->thपढ़ो.dsp.dspr[3]);					\
	mthi3(tsk->thपढ़ो.dsp.dspr[4]);					\
	mtlo3(tsk->thपढ़ो.dsp.dspr[5]);					\
	wrdsp(tsk->thपढ़ो.dsp.dspcontrol, DSP_MASK);			\
पूर्ण जबतक (0)

#घोषणा restore_dsp(tsk)						\
करो अणु									\
	अगर (cpu_has_dsp)						\
		__restore_dsp(tsk);					\
पूर्ण जबतक (0)

#घोषणा __get_dsp_regs(tsk)						\
(अणु									\
	अगर (tsk == current)						\
		__save_dsp(current);					\
									\
	tsk->thपढ़ो.dsp.dspr;						\
पूर्ण)

#पूर्ण_अगर /* _ASM_DSP_H */
