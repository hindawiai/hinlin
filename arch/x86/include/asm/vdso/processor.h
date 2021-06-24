<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 ARM Ltd.
 */
#अगर_अघोषित __ASM_VDSO_PROCESSOR_H
#घोषणा __ASM_VDSO_PROCESSOR_H

#अगर_अघोषित __ASSEMBLY__

/* REP NOP (PAUSE) is a good thing to insert पूर्णांकo busy-रुको loops. */
अटल __always_अंतरभूत व्योम rep_nop(व्योम)
अणु
	यंत्र अस्थिर("rep; nop" ::: "memory");
पूर्ण

अटल __always_अंतरभूत व्योम cpu_relax(व्योम)
अणु
	rep_nop();
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_PROCESSOR_H */
