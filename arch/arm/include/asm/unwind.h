<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/unwind.h
 *
 * Copyright (C) 2008 ARM Limited
 */

#अगर_अघोषित __ASM_UNWIND_H
#घोषणा __ASM_UNWIND_H

#अगर_अघोषित __ASSEMBLY__

/* Unwind reason code according the the ARM EABI करोcuments */
क्रमागत unwind_reason_code अणु
	URC_OK = 0,			/* operation completed successfully */
	URC_CONTINUE_UNWIND = 8,
	URC_FAILURE = 9			/* unspecअगरied failure of some kind */
पूर्ण;

काष्ठा unwind_idx अणु
	अचिन्हित दीर्घ addr_offset;
	अचिन्हित दीर्घ insn;
पूर्ण;

काष्ठा unwind_table अणु
	काष्ठा list_head list;
	स्थिर काष्ठा unwind_idx *start;
	स्थिर काष्ठा unwind_idx *origin;
	स्थिर काष्ठा unwind_idx *stop;
	अचिन्हित दीर्घ begin_addr;
	अचिन्हित दीर्घ end_addr;
पूर्ण;

बाह्य काष्ठा unwind_table *unwind_table_add(अचिन्हित दीर्घ start,
					     अचिन्हित दीर्घ size,
					     अचिन्हित दीर्घ text_addr,
					     अचिन्हित दीर्घ text_size);
बाह्य व्योम unwind_table_del(काष्ठा unwind_table *tab);
बाह्य व्योम unwind_backtrace(काष्ठा pt_regs *regs, काष्ठा task_काष्ठा *tsk,
			     स्थिर अक्षर *loglvl);

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#अगर_घोषित CONFIG_ARM_UNWIND
#घोषणा UNWIND(code...)		code
#अन्यथा
#घोषणा UNWIND(code...)
#पूर्ण_अगर

#पूर्ण_अगर	/* __ASM_UNWIND_H */
