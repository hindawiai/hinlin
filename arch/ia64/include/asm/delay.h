<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_DELAY_H
#घोषणा _ASM_IA64_DELAY_H

/*
 * Delay routines using a pre-computed "cycles/usec" value.
 *
 * Copyright (C) 1998, 1999 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 1999 Asit Mallick <asit.k.mallick@पूर्णांकel.com>
 * Copyright (C) 1999 Don Dugger <करोn.dugger@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/compiler.h>

#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <यंत्र/processor.h>

अटल __अंतरभूत__ व्योम
ia64_set_iपंचांग (अचिन्हित दीर्घ val)
अणु
	ia64_setreg(_IA64_REG_CR_ITM, val);
	ia64_srlz_d();
पूर्ण

अटल __अंतरभूत__ अचिन्हित दीर्घ
ia64_get_iपंचांग (व्योम)
अणु
	अचिन्हित दीर्घ result;

	result = ia64_getreg(_IA64_REG_CR_ITM);
	ia64_srlz_d();
	वापस result;
पूर्ण

अटल __अंतरभूत__ व्योम
ia64_set_itv (अचिन्हित दीर्घ val)
अणु
	ia64_setreg(_IA64_REG_CR_ITV, val);
	ia64_srlz_d();
पूर्ण

अटल __अंतरभूत__ अचिन्हित दीर्घ
ia64_get_itv (व्योम)
अणु
	वापस ia64_getreg(_IA64_REG_CR_ITV);
पूर्ण

अटल __अंतरभूत__ व्योम
ia64_set_itc (अचिन्हित दीर्घ val)
अणु
	ia64_setreg(_IA64_REG_AR_ITC, val);
	ia64_srlz_d();
पूर्ण

अटल __अंतरभूत__ अचिन्हित दीर्घ
ia64_get_itc (व्योम)
अणु
	अचिन्हित दीर्घ result;

	result = ia64_getreg(_IA64_REG_AR_ITC);
	ia64_barrier();
#अगर_घोषित CONFIG_ITANIUM
	जबतक (unlikely((__s32) result == -1)) अणु
		result = ia64_getreg(_IA64_REG_AR_ITC);
		ia64_barrier();
	पूर्ण
#पूर्ण_अगर
	वापस result;
पूर्ण

बाह्य व्योम ia64_delay_loop (अचिन्हित दीर्घ loops);

अटल __अंतरभूत__ व्योम
__delay (अचिन्हित दीर्घ loops)
अणु
	अगर (unlikely(loops < 1))
		वापस;

	ia64_delay_loop (loops - 1);
पूर्ण

बाह्य व्योम udelay (अचिन्हित दीर्घ usecs);

#पूर्ण_अगर /* _ASM_IA64_DELAY_H */
