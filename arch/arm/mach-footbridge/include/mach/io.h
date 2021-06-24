<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-footbridge/include/mach/पन.स
 *
 *  Copyright (C) 1997-1999 Russell King
 *
 *  Modअगरications:
 *   06-12-1997	RMK	Created.
 *   07-04-1999	RMK	Major cleanup
 */
#अगर_अघोषित __ASM_ARM_ARCH_IO_H
#घोषणा __ASM_ARM_ARCH_IO_H

/*
 * Translation of various i/o addresses to host addresses क्रम !CONFIG_MMU
 */
#घोषणा PCIO_BASE       0x7c000000
#घोषणा __io(a)			((व्योम __iomem *)(PCIO_BASE + (a)))

#पूर्ण_अगर
