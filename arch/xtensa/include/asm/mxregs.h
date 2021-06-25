<शैली गुरु>
/*
 * Xtensa MX पूर्णांकerrupt distributor
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 - 2013 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_MXREGS_H
#घोषणा _XTENSA_MXREGS_H

/*
 * RER/WER at, as	Read/ग_लिखो बाह्यal रेजिस्टर
 *	at: value
 *	as: address
 *
 * Address	Value
 * 00nn		0...0p..p	Interrupt Routing, route IRQ n to processor p
 * 01pp		0...0d..d	16 bits (d) 'ored' as single IPI to processor p
 * 0180		0...0m..m	Clear enable specअगरied by mask (m)
 * 0184		0...0m..m	Set enable specअगरied by mask (m)
 * 0190		0...0x..x	8-bit IPI partition रेजिस्टर
 *				VVVVVVVVPPPPUUUUUUUUUUUUUUUUU
 *				V (10-bit) Release/Version
 *				P ( 4-bit) Number of cores - 1
 *				U (18-bit) ID
 * 01a0		i.......i	32-bit ConfigID
 * 0200		0...0m..m	RunStall core 'n'
 * 0220		c		Cache coherency enabled
 */

#घोषणा MIROUT(irq)	(0x000 + (irq))
#घोषणा MIPICAUSE(cpu)	(0x100 + (cpu))
#घोषणा MIPISET(cause)	(0x140 + (cause))
#घोषणा MIENG		0x180
#घोषणा MIENGSET	0x184
#घोषणा MIASG		0x188	/* Read Global Assert Register */
#घोषणा MIASGSET	0x18c	/* Set Global Addert Regiter */
#घोषणा MIPIPART	0x190
#घोषणा SYSCFGID	0x1a0
#घोषणा MPSCORE		0x200
#घोषणा CCON		0x220

#पूर्ण_अगर /* _XTENSA_MXREGS_H */
