<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 ARM Ltd.
 */
#अगर_अघोषित __ASM_VDSO_CP15_H
#घोषणा __ASM_VDSO_CP15_H

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_CPU_CP15

#समावेश <linux/stringअगरy.h>

#घोषणा __ACCESS_CP15(CRn, Op1, CRm, Op2)	\
	"mrc", "mcr", __stringअगरy(p15, Op1, %0, CRn, CRm, Op2), u32
#घोषणा __ACCESS_CP15_64(Op1, CRm)		\
	"mrrc", "mcrr", __stringअगरy(p15, Op1, %Q0, %R0, CRm), u64

#घोषणा __पढ़ो_sysreg(r, w, c, t) (अणु				\
	t __val;						\
	यंत्र अस्थिर(r " " c : "=r" (__val));			\
	__val;							\
पूर्ण)
#घोषणा पढ़ो_sysreg(...)		__पढ़ो_sysreg(__VA_ARGS__)

#घोषणा __ग_लिखो_sysreg(v, r, w, c, t)	यंत्र अस्थिर(w " " c : : "r" ((t)(v)))
#घोषणा ग_लिखो_sysreg(v, ...)		__ग_लिखो_sysreg(v, __VA_ARGS__)

#घोषणा BPIALL				__ACCESS_CP15(c7, 0, c5, 6)
#घोषणा ICIALLU				__ACCESS_CP15(c7, 0, c5, 0)

#घोषणा CNTVCT				__ACCESS_CP15_64(1, c14)

#पूर्ण_अगर /* CONFIG_CPU_CP15 */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_CP15_H */
