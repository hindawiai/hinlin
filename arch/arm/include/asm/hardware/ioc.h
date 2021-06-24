<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/hardware/ioc.h
 *
 *  Copyright (C) Russell King
 *
 *  Use these macros to पढ़ो/ग_लिखो the IOC.  All it करोes is perक्रमm the actual
 *  पढ़ो/ग_लिखो.
 */
#अगर_अघोषित __ASMARM_HARDWARE_IOC_H
#घोषणा __ASMARM_HARDWARE_IOC_H

#अगर_अघोषित __ASSEMBLY__

/*
 * We use __raw_base variants here so that we give the compiler the
 * chance to keep IOC_BASE in a रेजिस्टर.
 */
#घोषणा ioc_पढ़ोb(off)		__raw_पढ़ोb(IOC_BASE + (off))
#घोषणा ioc_ग_लिखोb(val,off)	__raw_ग_लिखोb(val, IOC_BASE + (off))

#पूर्ण_अगर

#घोषणा IOC_CONTROL	(0x00)
#घोषणा IOC_KARTTX	(0x04)
#घोषणा IOC_KARTRX	(0x04)

#घोषणा IOC_IRQSTATA	(0x10)
#घोषणा IOC_IRQREQA	(0x14)
#घोषणा IOC_IRQCLRA	(0x14)
#घोषणा IOC_IRQMASKA	(0x18)

#घोषणा IOC_IRQSTATB	(0x20)
#घोषणा IOC_IRQREQB	(0x24)
#घोषणा IOC_IRQMASKB	(0x28)

#घोषणा IOC_FIQSTAT	(0x30)
#घोषणा IOC_FIQREQ	(0x34)
#घोषणा IOC_FIQMASK	(0x38)

#घोषणा IOC_T0CNTL	(0x40)
#घोषणा IOC_T0LTCHL	(0x40)
#घोषणा IOC_T0CNTH	(0x44)
#घोषणा IOC_T0LTCHH	(0x44)
#घोषणा IOC_T0GO	(0x48)
#घोषणा IOC_T0LATCH	(0x4c)

#घोषणा IOC_T1CNTL	(0x50)
#घोषणा IOC_T1LTCHL	(0x50)
#घोषणा IOC_T1CNTH	(0x54)
#घोषणा IOC_T1LTCHH	(0x54)
#घोषणा IOC_T1GO	(0x58)
#घोषणा IOC_T1LATCH	(0x5c)

#घोषणा IOC_T2CNTL	(0x60)
#घोषणा IOC_T2LTCHL	(0x60)
#घोषणा IOC_T2CNTH	(0x64)
#घोषणा IOC_T2LTCHH	(0x64)
#घोषणा IOC_T2GO	(0x68)
#घोषणा IOC_T2LATCH	(0x6c)

#घोषणा IOC_T3CNTL	(0x70)
#घोषणा IOC_T3LTCHL	(0x70)
#घोषणा IOC_T3CNTH	(0x74)
#घोषणा IOC_T3LTCHH	(0x74)
#घोषणा IOC_T3GO	(0x78)
#घोषणा IOC_T3LATCH	(0x7c)

#पूर्ण_अगर
