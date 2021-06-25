<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000_REGS_H_
#घोषणा _E1000_REGS_H_

#घोषणा E1000_CTRL	0x00000 /* Device Control - RW */
#घोषणा E1000_STATUS	0x00008 /* Device Status - RO */
#घोषणा E1000_ITR	0x000C4 /* Interrupt Throttling Rate - RW */
#घोषणा E1000_EICR	0x01580 /* Ext. Interrupt Cause Read - R/clr */
#घोषणा E1000_EITR(_n)	(0x01680 + (0x4 * (_n)))
#घोषणा E1000_EICS	0x01520 /* Ext. Interrupt Cause Set - W0 */
#घोषणा E1000_EIMS	0x01524 /* Ext. Interrupt Mask Set/Read - RW */
#घोषणा E1000_EIMC	0x01528 /* Ext. Interrupt Mask Clear - WO */
#घोषणा E1000_EIAC	0x0152C /* Ext. Interrupt Auto Clear - RW */
#घोषणा E1000_EIAM	0x01530 /* Ext. Interrupt Ack Auto Clear Mask - RW */
#घोषणा E1000_IVAR0	0x01700 /* Interrupt Vector Allocation (array) - RW */
#घोषणा E1000_IVAR_MISC	0x01740 /* IVAR क्रम "other" causes - RW */

/* Convenience macros
 *
 * Note: "_n" is the queue number of the रेजिस्टर to be written to.
 *
 * Example usage:
 * E1000_RDBAL_REG(current_rx_queue)
 */
#घोषणा E1000_RDBAL(_n)	((_n) < 4 ? (0x02800 + ((_n) * 0x100)) : \
			 (0x0C000 + ((_n) * 0x40)))
#घोषणा E1000_RDBAH(_n)	((_n) < 4 ? (0x02804 + ((_n) * 0x100)) : \
			 (0x0C004 + ((_n) * 0x40)))
#घोषणा E1000_RDLEN(_n)	((_n) < 4 ? (0x02808 + ((_n) * 0x100)) : \
			 (0x0C008 + ((_n) * 0x40)))
#घोषणा E1000_SRRCTL(_n)	((_n) < 4 ? (0x0280C + ((_n) * 0x100)) : \
				 (0x0C00C + ((_n) * 0x40)))
#घोषणा E1000_RDH(_n)	((_n) < 4 ? (0x02810 + ((_n) * 0x100)) : \
			 (0x0C010 + ((_n) * 0x40)))
#घोषणा E1000_RDT(_n)	((_n) < 4 ? (0x02818 + ((_n) * 0x100)) : \
			 (0x0C018 + ((_n) * 0x40)))
#घोषणा E1000_RXDCTL(_n)	((_n) < 4 ? (0x02828 + ((_n) * 0x100)) : \
				 (0x0C028 + ((_n) * 0x40)))
#घोषणा E1000_TDBAL(_n)	((_n) < 4 ? (0x03800 + ((_n) * 0x100)) : \
			 (0x0E000 + ((_n) * 0x40)))
#घोषणा E1000_TDBAH(_n)	((_n) < 4 ? (0x03804 + ((_n) * 0x100)) : \
			 (0x0E004 + ((_n) * 0x40)))
#घोषणा E1000_TDLEN(_n)	((_n) < 4 ? (0x03808 + ((_n) * 0x100)) : \
			 (0x0E008 + ((_n) * 0x40)))
#घोषणा E1000_TDH(_n)	((_n) < 4 ? (0x03810 + ((_n) * 0x100)) : \
			 (0x0E010 + ((_n) * 0x40)))
#घोषणा E1000_TDT(_n)	((_n) < 4 ? (0x03818 + ((_n) * 0x100)) : \
			 (0x0E018 + ((_n) * 0x40)))
#घोषणा E1000_TXDCTL(_n)	((_n) < 4 ? (0x03828 + ((_n) * 0x100)) : \
				 (0x0E028 + ((_n) * 0x40)))
#घोषणा E1000_DCA_TXCTRL(_n)	(0x03814 + (_n << 8))
#घोषणा E1000_DCA_RXCTRL(_n)	(0x02814 + (_n << 8))
#घोषणा E1000_RAL(_i)	(((_i) <= 15) ? (0x05400 + ((_i) * 8)) : \
			 (0x054E0 + ((_i - 16) * 8)))
#घोषणा E1000_RAH(_i)	(((_i) <= 15) ? (0x05404 + ((_i) * 8)) : \
			 (0x054E4 + ((_i - 16) * 8)))

/* Statistics रेजिस्टरs */
#घोषणा E1000_VFGPRC	0x00F10
#घोषणा E1000_VFGORC	0x00F18
#घोषणा E1000_VFMPRC	0x00F3C
#घोषणा E1000_VFGPTC	0x00F14
#घोषणा E1000_VFGOTC	0x00F34
#घोषणा E1000_VFGOTLBC	0x00F50
#घोषणा E1000_VFGPTLBC	0x00F44
#घोषणा E1000_VFGORLBC	0x00F48
#घोषणा E1000_VFGPRLBC	0x00F40

/* These act per VF so an array मित्रly macro is used */
#घोषणा E1000_V2PMAILBOX(_n)	(0x00C40 + (4 * (_n)))
#घोषणा E1000_VMBMEM(_n)	(0x00800 + (64 * (_n)))

/* Define macros क्रम handling रेजिस्टरs */
#घोषणा er32(reg)	पढ़ोl(hw->hw_addr + E1000_##reg)
#घोषणा ew32(reg, val)	ग_लिखोl((val), hw->hw_addr +  E1000_##reg)
#घोषणा array_er32(reg, offset) \
	पढ़ोl(hw->hw_addr + E1000_##reg + (offset << 2))
#घोषणा array_ew32(reg, offset, val) \
	ग_लिखोl((val), hw->hw_addr +  E1000_##reg + (offset << 2))
#घोषणा e1e_flush()	er32(STATUS)

#पूर्ण_अगर
