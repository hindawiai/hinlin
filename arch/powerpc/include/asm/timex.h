<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_TIMEX_H
#घोषणा _ASM_POWERPC_TIMEX_H

#अगर_घोषित __KERNEL__

/*
 * PowerPC architecture समयx specअगरications
 */

#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/vdso/समयbase.h>

#घोषणा CLOCK_TICK_RATE	1024000 /* Underlying HZ */

प्रकार अचिन्हित दीर्घ cycles_t;

अटल अंतरभूत cycles_t get_cycles(व्योम)
अणु
	वापस mftb();
पूर्ण

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_POWERPC_TIMEX_H */
