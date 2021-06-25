<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_ARC_UNWIND_H
#घोषणा _ASM_ARC_UNWIND_H

#अगर_घोषित CONFIG_ARC_DW2_UNWIND

#समावेश <linux/sched.h>

काष्ठा arc700_regs अणु
	अचिन्हित दीर्घ r0;
	अचिन्हित दीर्घ r1;
	अचिन्हित दीर्घ r2;
	अचिन्हित दीर्घ r3;
	अचिन्हित दीर्घ r4;
	अचिन्हित दीर्घ r5;
	अचिन्हित दीर्घ r6;
	अचिन्हित दीर्घ r7;
	अचिन्हित दीर्घ r8;
	अचिन्हित दीर्घ r9;
	अचिन्हित दीर्घ r10;
	अचिन्हित दीर्घ r11;
	अचिन्हित दीर्घ r12;
	अचिन्हित दीर्घ r13;
	अचिन्हित दीर्घ r14;
	अचिन्हित दीर्घ r15;
	अचिन्हित दीर्घ r16;
	अचिन्हित दीर्घ r17;
	अचिन्हित दीर्घ r18;
	अचिन्हित दीर्घ r19;
	अचिन्हित दीर्घ r20;
	अचिन्हित दीर्घ r21;
	अचिन्हित दीर्घ r22;
	अचिन्हित दीर्घ r23;
	अचिन्हित दीर्घ r24;
	अचिन्हित दीर्घ r25;
	अचिन्हित दीर्घ r26;
	अचिन्हित दीर्घ r27;	/* fp */
	अचिन्हित दीर्घ r28;	/* sp */
	अचिन्हित दीर्घ r29;
	अचिन्हित दीर्घ r30;
	अचिन्हित दीर्घ r31;	/* blink */
	अचिन्हित दीर्घ r63;	/* pc */
पूर्ण;

काष्ठा unwind_frame_info अणु
	काष्ठा arc700_regs regs;
	काष्ठा task_काष्ठा *task;
	अचिन्हित call_frame:1;
पूर्ण;

#घोषणा UNW_PC(frame)		((frame)->regs.r63)
#घोषणा UNW_SP(frame)		((frame)->regs.r28)
#घोषणा UNW_BLINK(frame)	((frame)->regs.r31)

/* Rajesh FIXME */
#अगर_घोषित CONFIG_FRAME_POINTER
#घोषणा UNW_FP(frame)		((frame)->regs.r27)
#घोषणा FRAME_RETADDR_OFFSET	4
#घोषणा FRAME_LINK_OFFSET	0
#घोषणा STACK_BOTTOM_UNW(tsk)	STACK_LIMIT((tsk)->thपढ़ो.ksp)
#घोषणा STACK_TOP_UNW(tsk)	((tsk)->thपढ़ो.ksp)
#अन्यथा
#घोषणा UNW_FP(frame)		((व्योम)(frame), 0)
#पूर्ण_अगर

#घोषणा STACK_LIMIT(ptr)	(((ptr) - 1) & ~(THREAD_SIZE - 1))

#घोषणा UNW_REGISTER_INFO \
	PTREGS_INFO(r0), \
	PTREGS_INFO(r1), \
	PTREGS_INFO(r2), \
	PTREGS_INFO(r3), \
	PTREGS_INFO(r4), \
	PTREGS_INFO(r5), \
	PTREGS_INFO(r6), \
	PTREGS_INFO(r7), \
	PTREGS_INFO(r8), \
	PTREGS_INFO(r9), \
	PTREGS_INFO(r10), \
	PTREGS_INFO(r11), \
	PTREGS_INFO(r12), \
	PTREGS_INFO(r13), \
	PTREGS_INFO(r14), \
	PTREGS_INFO(r15), \
	PTREGS_INFO(r16), \
	PTREGS_INFO(r17), \
	PTREGS_INFO(r18), \
	PTREGS_INFO(r19), \
	PTREGS_INFO(r20), \
	PTREGS_INFO(r21), \
	PTREGS_INFO(r22), \
	PTREGS_INFO(r23), \
	PTREGS_INFO(r24), \
	PTREGS_INFO(r25), \
	PTREGS_INFO(r26), \
	PTREGS_INFO(r27), \
	PTREGS_INFO(r28), \
	PTREGS_INFO(r29), \
	PTREGS_INFO(r30), \
	PTREGS_INFO(r31), \
	PTREGS_INFO(r63)

#घोषणा UNW_DEFAULT_RA(raItem, dataAlign) \
	((raItem).where == Memory && !((raItem).value * (dataAlign) + 4))

बाह्य पूर्णांक arc_unwind(काष्ठा unwind_frame_info *frame);
बाह्य व्योम arc_unwind_init(व्योम);
बाह्य व्योम *unwind_add_table(काष्ठा module *module, स्थिर व्योम *table_start,
			      अचिन्हित दीर्घ table_size);
बाह्य व्योम unwind_हटाओ_table(व्योम *handle, पूर्णांक init_only);

अटल अंतरभूत पूर्णांक
arch_unwind_init_running(काष्ठा unwind_frame_info *info,
			 पूर्णांक (*callback) (काष्ठा unwind_frame_info *info,
					  व्योम *arg),
			 व्योम *arg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक arch_unw_user_mode(स्थिर काष्ठा unwind_frame_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम arch_unw_init_blocked(काष्ठा unwind_frame_info *info)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम arch_unw_init_frame_info(काष्ठा unwind_frame_info *info,
					    काष्ठा pt_regs *regs)
अणु
	वापस;
पूर्ण

#अन्यथा

#घोषणा UNW_PC(frame) ((व्योम)(frame), 0)
#घोषणा UNW_SP(frame) ((व्योम)(frame), 0)
#घोषणा UNW_FP(frame) ((व्योम)(frame), 0)

अटल अंतरभूत व्योम arc_unwind_init(व्योम)
अणु
पूर्ण

#घोषणा unwind_add_table(a, b, c)
#घोषणा unwind_हटाओ_table(a, b)

#पूर्ण_अगर /* CONFIG_ARC_DW2_UNWIND */

#पूर्ण_अगर /* _ASM_ARC_UNWIND_H */
