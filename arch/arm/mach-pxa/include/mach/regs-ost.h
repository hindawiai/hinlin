<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_REGS_OST_H
#घोषणा __ASM_MACH_REGS_OST_H

#समावेश <mach/hardware.h>

/*
 * OS Timer & Match Registers
 */

#घोषणा OSMR0		io_p2v(0x40A00000)  /* */
#घोषणा OSMR1		io_p2v(0x40A00004)  /* */
#घोषणा OSMR2		io_p2v(0x40A00008)  /* */
#घोषणा OSMR3		io_p2v(0x40A0000C)  /* */
#घोषणा OSMR4		io_p2v(0x40A00080)  /* */
#घोषणा OSCR		io_p2v(0x40A00010)  /* OS Timer Counter Register */
#घोषणा OSCR4		io_p2v(0x40A00040)  /* OS Timer Counter Register */
#घोषणा OMCR4		io_p2v(0x40A000C0)  /* */
#घोषणा OSSR		io_p2v(0x40A00014)  /* OS Timer Status Register */
#घोषणा OWER		io_p2v(0x40A00018)  /* OS Timer Watchकरोg Enable Register */
#घोषणा OIER		io_p2v(0x40A0001C)  /* OS Timer Interrupt Enable Register */

#घोषणा OSSR_M3		(1 << 3)	/* Match status channel 3 */
#घोषणा OSSR_M2		(1 << 2)	/* Match status channel 2 */
#घोषणा OSSR_M1		(1 << 1)	/* Match status channel 1 */
#घोषणा OSSR_M0		(1 << 0)	/* Match status channel 0 */

#घोषणा OWER_WME	(1 << 0)	/* Watchकरोg Match Enable */

#घोषणा OIER_E3		(1 << 3)	/* Interrupt enable channel 3 */
#घोषणा OIER_E2		(1 << 2)	/* Interrupt enable channel 2 */
#घोषणा OIER_E1		(1 << 1)	/* Interrupt enable channel 1 */
#घोषणा OIER_E0		(1 << 0)	/* Interrupt enable channel 0 */

#पूर्ण_अगर /* __ASM_MACH_REGS_OST_H */
