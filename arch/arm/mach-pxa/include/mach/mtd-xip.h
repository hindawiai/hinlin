<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MTD primitives क्रम XIP support. Architecture specअगरic functions
 *
 * Do not include this file directly. It's included from linux/mtd/xip.h
 * 
 * Author:	Nicolas Pitre
 * Created:	Nov 2, 2004
 * Copyright:	(C) 2004 MontaVista Software, Inc.
 */

#अगर_अघोषित __ARCH_PXA_MTD_XIP_H__
#घोषणा __ARCH_PXA_MTD_XIP_H__

#समावेश <mach/regs-ost.h>

/* restored July 2017, this did not build since 2011! */

#घोषणा ICIP			io_p2v(0x40d00000)
#घोषणा ICMR			io_p2v(0x40d00004)
#घोषणा xip_irqpending()	(पढ़ोl(ICIP) & पढ़ोl(ICMR))

/* we sample OSCR and convert desired delta to usec (1/4 ~= 1000000/3686400) */
#घोषणा xip_currसमय()		पढ़ोl(OSCR)
#घोषणा xip_elapsed_since(x)	(चिन्हित)((पढ़ोl(OSCR) - (x)) / 4)

/*
 * xip_cpu_idle() is used when रुकोing क्रम a delay equal or larger than
 * the प्रणाली समयr tick period.  This should put the CPU पूर्णांकo idle mode
 * to save घातer and to be woken up only when some पूर्णांकerrupts are pending.
 * As above, this should not rely upon standard kernel code.
 */

#घोषणा xip_cpu_idle()  यंत्र अस्थिर ("mcr p14, 0, %0, c7, c0, 0" :: "r" (1))

#पूर्ण_अगर /* __ARCH_PXA_MTD_XIP_H__ */
