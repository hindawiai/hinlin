<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-rpc/include/mach/पन.स
 *
 *  Copyright (C) 1997 Russell King
 *
 * Modअगरications:
 *  06-Dec-1997	RMK	Created.
 */
#अगर_अघोषित __ASM_ARM_ARCH_IO_H
#घोषणा __ASM_ARM_ARCH_IO_H

#समावेश <mach/hardware.h>

#घोषणा IO_SPACE_LIMIT 0xffff

/*
 * We need PC style IO addressing क्रम:
 *  - floppy (at 0x3f2,0x3f4,0x3f5,0x3f7)
 *  - parport (at 0x278-0x27a, 0x27b-0x27f, 0x778-0x77a)
 *  - 8250 serial (only क्रम compile)
 *
 * These peripherals are found in an area of MMIO which looks very much
 * like an ISA bus, but with रेजिस्टरs at the low byte of each word.
 */
#घोषणा __io(a)		(PCIO_BASE + ((a) << 2))

#पूर्ण_अगर
