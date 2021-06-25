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

#अगर_अघोषित __ARCH_SA1100_MTD_XIP_H__
#घोषणा __ARCH_SA1100_MTD_XIP_H__

#समावेश <mach/hardware.h>

#घोषणा xip_irqpending()	(ICIP & ICMR)

/* we sample OSCR and convert desired delta to usec (1/4 ~= 1000000/3686400) */
#घोषणा xip_currसमय()		पढ़ोl_relaxed(OSCR)
#घोषणा xip_elapsed_since(x)	(चिन्हित)((पढ़ोl_relaxed(OSCR) - (x)) / 4)

#पूर्ण_अगर /* __ARCH_SA1100_MTD_XIP_H__ */
