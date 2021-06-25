<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MTD primitives क्रम XIP support
 *
 * Author:	Nicolas Pitre
 * Created:	Nov 2, 2004
 * Copyright:	(C) 2004 MontaVista Software, Inc.
 *
 * This XIP support क्रम MTD has been loosely inspired
 * by an earlier patch authored by David Woodhouse.
 */

#अगर_अघोषित __LINUX_MTD_XIP_H__
#घोषणा __LINUX_MTD_XIP_H__


#अगर_घोषित CONFIG_MTD_XIP

/*
 * We really करोn't want gcc to guess anything.
 * We असलolutely _need_ proper inlining.
 */
#समावेश <linux/compiler.h>

/*
 * Function that are modअगरying the flash state away from array mode must
 * obviously not be running from flash.  The __xipram is thereक्रमe marking
 * those functions so they get relocated to ram.
 */
#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा __xipram noअंतरभूत __section(".xiptext")
#पूर्ण_अगर

/*
 * Each architecture has to provide the following macros.  They must access
 * the hardware directly and not rely on any other (XIP) functions since they
 * won't be available when used (flash not in array mode).
 *
 * xip_irqpending()
 *
 * 	वापस non zero when any hardware पूर्णांकerrupt is pending.
 *
 * xip_currसमय()
 *
 * 	वापस a platक्रमm specअगरic समय reference to be used with
 * 	xip_elapsed_since().
 *
 * xip_elapsed_since(x)
 *
 * 	वापस in usecs the elapsed समयbetween now and the reference x as
 * 	वापसed by xip_currसमय().
 *
 * 	note 1: conversion to usec can be approximated, as दीर्घ as the
 * 		वापसed value is <= the real elapsed समय.
 * 	note 2: this should be able to cope with a few seconds without
 * 		overflowing.
 *
 * xip_iprefetch()
 *
 *      Macro to fill inकाष्ठाion prefetch
 *	e.g. a series of nops:  यंत्र अस्थिर (".rep 8; nop; .endr");
 */

#समावेश <यंत्र/mtd-xip.h>

#अगर_अघोषित xip_irqpending

#warning "missing IRQ and timer primitives for XIP MTD support"
#warning "some of the XIP MTD support code will be disabled"
#warning "your system will therefore be unresponsive when writing or erasing flash"

#घोषणा xip_irqpending()	(0)
#घोषणा xip_currसमय()		(0)
#घोषणा xip_elapsed_since(x)	(0)

#पूर्ण_अगर

#अगर_अघोषित xip_iprefetch
#घोषणा xip_iprefetch()		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * xip_cpu_idle() is used when रुकोing क्रम a delay equal or larger than
 * the प्रणाली समयr tick period.  This should put the CPU पूर्णांकo idle mode
 * to save घातer and to be woken up only when some पूर्णांकerrupts are pending.
 * This should not rely upon standard kernel code.
 */
#अगर_अघोषित xip_cpu_idle
#घोषणा xip_cpu_idle()  करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_MTD_XIP */

#अगर_अघोषित __xipram
#घोषणा __xipram
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_MTD_XIP_H__ */
