<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-sa1100/include/mach/hardware.h
 *
 * Copyright (C) 1998 Nicolas Pitre <nico@fluxnic.net>
 *
 * This file contains the hardware definitions क्रम SA1100 architecture
 *
 * 2000/05/23 John Dorsey <john+@cs.cmu.edu>
 *      Definitions क्रम SA1111 added.
 */

#अगर_अघोषित __ASM_ARCH_HARDWARE_H
#घोषणा __ASM_ARCH_HARDWARE_H


#घोषणा UNCACHEABLE_ADDR	0xfa050000	/* ICIP */


/*
 * SA1100 पूर्णांकernal I/O mappings
 *
 * We have the following mapping:
 *      phys            virt
 *      80000000        f8000000
 *      90000000        fa000000
 *      a0000000        fc000000
 *      b0000000        fe000000
 */

#घोषणा VIO_BASE        0xf8000000	/* भव start of IO space */
#घोषणा VIO_SHIFT       3		/* x = IO space shrink घातer */
#घोषणा PIO_START       0x80000000	/* physical start of IO space */

#घोषणा io_p2v( x )             \
   IOMEM( (((x)&0x00ffffff) | (((x)&0x30000000)>>VIO_SHIFT)) + VIO_BASE )
#घोषणा io_v2p( x )             \
   ( (((x)&0x00ffffff) | (((x)&(0x30000000>>VIO_SHIFT))<<VIO_SHIFT)) + PIO_START )

#घोषणा __MREG(x)	IOMEM(io_p2v(x))

#अगर_अघोषित __ASSEMBLY__

# define __REG(x)	(*((अस्थिर अचिन्हित दीर्घ __iomem *)io_p2v(x)))
# define __PREG(x)	(io_v2p((अचिन्हित दीर्घ)&(x)))

#अन्यथा

# define __REG(x)	io_p2v(x)
# define __PREG(x)	io_v2p(x)

#पूर्ण_अगर

#समावेश "SA-1100.h"

#पूर्ण_अगर  /* _ASM_ARCH_HARDWARE_H */
