<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/hardware/iomd.h
 *
 *  Copyright (C) 1999 Russell King
 *
 *  This file contains inक्रमmation out the IOMD ASIC used in the
 *  Acorn RiscPC and subsequently पूर्णांकegrated पूर्णांकo the CLPS7500 chips.
 */
#अगर_अघोषित __ASMARM_HARDWARE_IOMD_H
#घोषणा __ASMARM_HARDWARE_IOMD_H


#अगर_अघोषित __ASSEMBLY__

/*
 * We use __raw_base variants here so that we give the compiler the
 * chance to keep IOC_BASE in a रेजिस्टर.
 */
#घोषणा iomd_पढ़ोb(off)		__raw_पढ़ोb(IOMD_BASE + (off))
#घोषणा iomd_पढ़ोl(off)		__raw_पढ़ोl(IOMD_BASE + (off))
#घोषणा iomd_ग_लिखोb(val,off)	__raw_ग_लिखोb(val, IOMD_BASE + (off))
#घोषणा iomd_ग_लिखोl(val,off)	__raw_ग_लिखोl(val, IOMD_BASE + (off))

#पूर्ण_अगर

#घोषणा IOMD_CONTROL	(0x000)
#घोषणा IOMD_KARTTX	(0x004)
#घोषणा IOMD_KARTRX	(0x004)
#घोषणा IOMD_KCTRL	(0x008)

#घोषणा IOMD_IRQSTATA	(0x010)
#घोषणा IOMD_IRQREQA	(0x014)
#घोषणा IOMD_IRQCLRA	(0x014)
#घोषणा IOMD_IRQMASKA	(0x018)

#घोषणा IOMD_IRQSTATB	(0x020)
#घोषणा IOMD_IRQREQB	(0x024)
#घोषणा IOMD_IRQMASKB	(0x028)

#घोषणा IOMD_FIQSTAT	(0x030)
#घोषणा IOMD_FIQREQ	(0x034)
#घोषणा IOMD_FIQMASK	(0x038)

#घोषणा IOMD_T0CNTL	(0x040)
#घोषणा IOMD_T0LTCHL	(0x040)
#घोषणा IOMD_T0CNTH	(0x044)
#घोषणा IOMD_T0LTCHH	(0x044)
#घोषणा IOMD_T0GO	(0x048)
#घोषणा IOMD_T0LATCH	(0x04c)

#घोषणा IOMD_T1CNTL	(0x050)
#घोषणा IOMD_T1LTCHL	(0x050)
#घोषणा IOMD_T1CNTH	(0x054)
#घोषणा IOMD_T1LTCHH	(0x054)
#घोषणा IOMD_T1GO	(0x058)
#घोषणा IOMD_T1LATCH	(0x05c)

#घोषणा IOMD_ROMCR0	(0x080)
#घोषणा IOMD_ROMCR1	(0x084)
#अगर_घोषित CONFIG_ARCH_RPC
#घोषणा IOMD_DRAMCR	(0x088)
#पूर्ण_अगर
#घोषणा IOMD_REFCR	(0x08C)

#घोषणा IOMD_FSIZE	(0x090)
#घोषणा IOMD_ID0	(0x094)
#घोषणा IOMD_ID1	(0x098)
#घोषणा IOMD_VERSION	(0x09C)

#अगर_घोषित CONFIG_ARCH_RPC
#घोषणा IOMD_MOUSEX	(0x0A0)
#घोषणा IOMD_MOUSEY	(0x0A4)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_RPC
#घोषणा IOMD_DMATCR	(0x0C0)
#पूर्ण_अगर
#घोषणा IOMD_IOTCR	(0x0C4)
#घोषणा IOMD_ECTCR	(0x0C8)
#अगर_घोषित CONFIG_ARCH_RPC
#घोषणा IOMD_DMAEXT	(0x0CC)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_RPC
#घोषणा DMA_EXT_IO0	1
#घोषणा DMA_EXT_IO1	2
#घोषणा DMA_EXT_IO2	4
#घोषणा DMA_EXT_IO3	8

#घोषणा IOMD_IO0CURA	(0x100)
#घोषणा IOMD_IO0ENDA	(0x104)
#घोषणा IOMD_IO0CURB	(0x108)
#घोषणा IOMD_IO0ENDB	(0x10C)
#घोषणा IOMD_IO0CR	(0x110)
#घोषणा IOMD_IO0ST	(0x114)

#घोषणा IOMD_IO1CURA	(0x120)
#घोषणा IOMD_IO1ENDA	(0x124)
#घोषणा IOMD_IO1CURB	(0x128)
#घोषणा IOMD_IO1ENDB	(0x12C)
#घोषणा IOMD_IO1CR	(0x130)
#घोषणा IOMD_IO1ST	(0x134)

#घोषणा IOMD_IO2CURA	(0x140)
#घोषणा IOMD_IO2ENDA	(0x144)
#घोषणा IOMD_IO2CURB	(0x148)
#घोषणा IOMD_IO2ENDB	(0x14C)
#घोषणा IOMD_IO2CR	(0x150)
#घोषणा IOMD_IO2ST	(0x154)

#घोषणा IOMD_IO3CURA	(0x160)
#घोषणा IOMD_IO3ENDA	(0x164)
#घोषणा IOMD_IO3CURB	(0x168)
#घोषणा IOMD_IO3ENDB	(0x16C)
#घोषणा IOMD_IO3CR	(0x170)
#घोषणा IOMD_IO3ST	(0x174)
#पूर्ण_अगर

#घोषणा IOMD_SD0CURA	(0x180)
#घोषणा IOMD_SD0ENDA	(0x184)
#घोषणा IOMD_SD0CURB	(0x188)
#घोषणा IOMD_SD0ENDB	(0x18C)
#घोषणा IOMD_SD0CR	(0x190)
#घोषणा IOMD_SD0ST	(0x194)

#अगर_घोषित CONFIG_ARCH_RPC
#घोषणा IOMD_SD1CURA	(0x1A0)
#घोषणा IOMD_SD1ENDA	(0x1A4)
#घोषणा IOMD_SD1CURB	(0x1A8)
#घोषणा IOMD_SD1ENDB	(0x1AC)
#घोषणा IOMD_SD1CR	(0x1B0)
#घोषणा IOMD_SD1ST	(0x1B4)
#पूर्ण_अगर

#घोषणा IOMD_CURSCUR	(0x1C0)
#घोषणा IOMD_CURSINIT	(0x1C4)

#घोषणा IOMD_VIDCUR	(0x1D0)
#घोषणा IOMD_VIDEND	(0x1D4)
#घोषणा IOMD_VIDSTART	(0x1D8)
#घोषणा IOMD_VIDINIT	(0x1DC)
#घोषणा IOMD_VIDCR	(0x1E0)

#घोषणा IOMD_DMASTAT	(0x1F0)
#घोषणा IOMD_DMAREQ	(0x1F4)
#घोषणा IOMD_DMAMASK	(0x1F8)

#घोषणा DMA_END_S	(1 << 31)
#घोषणा DMA_END_L	(1 << 30)

#घोषणा DMA_CR_C	0x80
#घोषणा DMA_CR_D	0x40
#घोषणा DMA_CR_E	0x20

#घोषणा DMA_ST_OFL	4
#घोषणा DMA_ST_INT	2
#घोषणा DMA_ST_AB	1

/*
 * DMA (MEMC) compatibility
 */
#घोषणा HALF_SAM	vram_half_sam
#घोषणा VDMA_ALIGNMENT	(HALF_SAM * 2)
#घोषणा VDMA_XFERSIZE	(HALF_SAM)
#घोषणा VDMA_INIT	IOMD_VIDINIT
#घोषणा VDMA_START	IOMD_VIDSTART
#घोषणा VDMA_END	IOMD_VIDEND

#अगर_अघोषित __ASSEMBLY__
बाह्य अचिन्हित पूर्णांक vram_half_sam;
#घोषणा video_set_dma(start,end,offset)				\
करो अणु								\
	outl (SCREEN_START + start, VDMA_START);		\
	outl (SCREEN_START + end - VDMA_XFERSIZE, VDMA_END);	\
	अगर (offset >= end - VDMA_XFERSIZE)			\
		offset |= 0x40000000;				\
	outl (SCREEN_START + offset, VDMA_INIT);		\
पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर
