<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  arch/arm/mach-footbridge/include/mach/isa-dma.h
 *
 *  Architecture DMA routines
 *
 *  Copyright (C) 1998,1999 Russell King
 *  Copyright (C) 1998,1999 Philip Blundell
 */
#अगर_अघोषित __ASM_ARCH_DMA_H
#घोषणा __ASM_ARCH_DMA_H

/*
 * The 21285 has two पूर्णांकernal DMA channels; we call these 8 and 9.
 * On CATS hardware we have an additional eight ISA dma channels
 * numbered 0..7.
 */
#घोषणा _ISA_DMA(x)		(0+(x))
#घोषणा _DC21285_DMA(x)		(8+(x))

#घोषणा MAX_DMA_CHANNELS	10

#घोषणा DMA_FLOPPY		_ISA_DMA(2)
#घोषणा DMA_ISA_CASCADE		_ISA_DMA(4)

#पूर्ण_अगर /* _ASM_ARCH_DMA_H */
