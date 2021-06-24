<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * delay.h: Linux delay routines on the Sparc.
 *
 * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu).
 */

#अगर_अघोषित __SPARC_DELAY_H
#घोषणा __SPARC_DELAY_H

#समावेश <यंत्र/cpudata.h>

अटल अंतरभूत व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	__यंत्र__ __अस्थिर__("cmp %0, 0\n\t"
			     "1: bne 1b\n\t"
			     "subcc %0, 1, %0\n" :
			     "=&r" (loops) :
			     "0" (loops) :
			     "cc");
पूर्ण

/* This is too messy with अंतरभूत यंत्र on the Sparc. */
व्योम __udelay(अचिन्हित दीर्घ usecs, अचिन्हित दीर्घ lpj);
व्योम __ndelay(अचिन्हित दीर्घ nsecs, अचिन्हित दीर्घ lpj);

#अगर_घोषित CONFIG_SMP
#घोषणा __udelay_val	cpu_data(smp_processor_id()).udelay_val
#अन्यथा /* SMP */
#घोषणा __udelay_val	loops_per_jअगरfy
#पूर्ण_अगर /* SMP */
#घोषणा udelay(__usecs)	__udelay(__usecs, __udelay_val)
#घोषणा ndelay(__nsecs)	__ndelay(__nsecs, __udelay_val)

#पूर्ण_अगर /* defined(__SPARC_DELAY_H) */
