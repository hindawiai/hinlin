<शैली गुरु>
/*
 * arch/xtensa/platक्रमm/xtavnet/include/platक्रमm/hardware.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2006 Tensilica Inc.
 */

/*
 * This file contains the hardware configuration of the XTAVNET boards.
 */

#समावेश <यंत्र/types.h>

#अगर_अघोषित __XTENSA_XTAVNET_HARDWARE_H
#घोषणा __XTENSA_XTAVNET_HARDWARE_H

/* Default assignment of LX60 devices to बाह्यal पूर्णांकerrupts. */

#अगर_घोषित CONFIG_XTENSA_MX
#घोषणा DUART16552_INTNUM	XCHAL_EXTINT3_NUM
#घोषणा OETH_IRQ		XCHAL_EXTINT4_NUM
#घोषणा C67X00_IRQ		XCHAL_EXTINT8_NUM
#अन्यथा
#घोषणा DUART16552_INTNUM	XCHAL_EXTINT0_NUM
#घोषणा OETH_IRQ		XCHAL_EXTINT1_NUM
#घोषणा C67X00_IRQ		XCHAL_EXTINT5_NUM
#पूर्ण_अगर

/*
 *  Device addresses and parameters.
 */

/* UART */
#घोषणा DUART16552_PADDR	(XCHAL_KIO_PADDR + 0x0D050020)

/* Misc. */
#घोषणा XTFPGA_FPGAREGS_VADDR	IOADDR(0x0D020000)
/* Clock frequency in Hz (पढ़ो-only):  */
#घोषणा XTFPGA_CLKFRQ_VADDR	(XTFPGA_FPGAREGS_VADDR + 0x04)
/* Setting of 8 DIP चयनes:  */
#घोषणा DIP_SWITCHES_VADDR	(XTFPGA_FPGAREGS_VADDR + 0x0C)
/* Software reset (ग_लिखो 0xdead):  */
#घोषणा XTFPGA_SWRST_VADDR	(XTFPGA_FPGAREGS_VADDR + 0x10)

/*  OpenCores Ethernet controller:  */
				/* regs + RX/TX descriptors */
#घोषणा OETH_REGS_PADDR		(XCHAL_KIO_PADDR + 0x0D030000)
#घोषणा OETH_REGS_SIZE		0x1000
#घोषणा OETH_SRAMBUFF_PADDR	(XCHAL_KIO_PADDR + 0x0D800000)

				/* 5*rx buffs + 5*tx buffs */
#घोषणा OETH_SRAMBUFF_SIZE	(5 * 0x600 + 5 * 0x600)

#घोषणा C67X00_PADDR		(XCHAL_KIO_PADDR + 0x0D0D0000)
#घोषणा C67X00_SIZE		0x10

#पूर्ण_अगर /* __XTENSA_XTAVNET_HARDWARE_H */
