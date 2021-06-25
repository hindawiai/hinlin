<शैली गुरु>
/*
 * cirrus.h 1.4 1999/10/25 20:03:34
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License
 * at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License क्रम the specअगरic language governing rights and
 * limitations under the License. 
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License version 2 (the "GPL"), in which
 * हाल the provisions of the GPL are applicable instead of the
 * above.  If you wish to allow the use of your version of this file
 * only under the terms of the GPL and not to allow others to use
 * your version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice and
 * other provisions required by the GPL.  If you करो not delete the
 * provisions above, a recipient may use your version of this file
 * under either the MPL or the GPL.
 */

#अगर_अघोषित _LINUX_CIRRUS_H
#घोषणा _LINUX_CIRRUS_H

#घोषणा PD67_MISC_CTL_1		0x16	/* Misc control 1 */
#घोषणा PD67_FIFO_CTL		0x17	/* FIFO control */
#घोषणा PD67_MISC_CTL_2		0x1E	/* Misc control 2 */
#घोषणा PD67_CHIP_INFO		0x1f	/* Chip inक्रमmation */
#घोषणा PD67_ATA_CTL		0x026	/* 6730: ATA control */
#घोषणा PD67_EXT_INDEX		0x2e	/* Extension index */
#घोषणा PD67_EXT_DATA		0x2f	/* Extension data */

/* PD6722 extension रेजिस्टरs -- indexed in PD67_EXT_INDEX */
#घोषणा PD67_DATA_MASK0		0x01	/* Data mask 0 */
#घोषणा PD67_DATA_MASK1		0x02	/* Data mask 1 */
#घोषणा PD67_DMA_CTL		0x03	/* DMA control */

/* PD6730 extension रेजिस्टरs -- indexed in PD67_EXT_INDEX */
#घोषणा PD67_EXT_CTL_1		0x03	/* Extension control 1 */
#घोषणा PD67_MEM_PAGE(n)	((n)+5)	/* PCI winकरोw bits 31:24 */
#घोषणा PD67_EXTERN_DATA	0x0a
#घोषणा PD67_MISC_CTL_3		0x25
#घोषणा PD67_SMB_PWR_CTL	0x26

/* I/O winकरोw address offset */
#घोषणा PD67_IO_OFF(w)		(0x36+((w)<<1))

/* Timing रेजिस्टर sets */
#घोषणा PD67_TIME_SETUP(n)	(0x3a + 3*(n))
#घोषणा PD67_TIME_CMD(n)	(0x3b + 3*(n))
#घोषणा PD67_TIME_RECOV(n)	(0x3c + 3*(n))

/* Flags क्रम PD67_MISC_CTL_1 */
#घोषणा PD67_MC1_5V_DET		0x01	/* 5v detect */
#घोषणा PD67_MC1_MEDIA_ENA	0x01	/* 6730: Mulसमयdia enable */
#घोषणा PD67_MC1_VCC_3V		0x02	/* 3.3v Vcc */
#घोषणा PD67_MC1_PULSE_MGMT	0x04
#घोषणा PD67_MC1_PULSE_IRQ	0x08
#घोषणा PD67_MC1_SPKR_ENA	0x10
#घोषणा PD67_MC1_INPACK_ENA	0x80

/* Flags क्रम PD67_FIFO_CTL */
#घोषणा PD67_FIFO_EMPTY		0x80

/* Flags क्रम PD67_MISC_CTL_2 */
#घोषणा PD67_MC2_FREQ_BYPASS	0x01
#घोषणा PD67_MC2_DYNAMIC_MODE	0x02
#घोषणा PD67_MC2_SUSPEND	0x04
#घोषणा PD67_MC2_5V_CORE	0x08
#घोषणा PD67_MC2_LED_ENA	0x10	/* IRQ 12 is LED enable */
#घोषणा PD67_MC2_FAST_PCI	0x10	/* 6729: PCI bus > 25 MHz */
#घोषणा PD67_MC2_3STATE_BIT7	0x20	/* Floppy change bit */
#घोषणा PD67_MC2_DMA_MODE	0x40
#घोषणा PD67_MC2_IRQ15_RI	0x80	/* IRQ 15 is ring enable */

/* Flags क्रम PD67_CHIP_INFO */
#घोषणा PD67_INFO_SLOTS		0x20	/* 0 = 1 slot, 1 = 2 slots */
#घोषणा PD67_INFO_CHIP_ID	0xc0
#घोषणा PD67_INFO_REV		0x1c

/* Fields in PD67_TIME_* रेजिस्टरs */
#घोषणा PD67_TIME_SCALE		0xc0
#घोषणा PD67_TIME_SCALE_1	0x00
#घोषणा PD67_TIME_SCALE_16	0x40
#घोषणा PD67_TIME_SCALE_256	0x80
#घोषणा PD67_TIME_SCALE_4096	0xc0
#घोषणा PD67_TIME_MULT		0x3f

/* Fields in PD67_DMA_CTL */
#घोषणा PD67_DMA_MODE		0xc0
#घोषणा PD67_DMA_OFF		0x00
#घोषणा PD67_DMA_DREQ_INPACK	0x40
#घोषणा PD67_DMA_DREQ_WP	0x80
#घोषणा PD67_DMA_DREQ_BVD2	0xc0
#घोषणा PD67_DMA_PULLUP		0x20	/* Disable socket pullups? */

/* Fields in PD67_EXT_CTL_1 */
#घोषणा PD67_EC1_VCC_PWR_LOCK	0x01
#घोषणा PD67_EC1_AUTO_PWR_CLEAR	0x02
#घोषणा PD67_EC1_LED_ENA	0x04
#घोषणा PD67_EC1_INV_CARD_IRQ	0x08
#घोषणा PD67_EC1_INV_MGMT_IRQ	0x10
#घोषणा PD67_EC1_PULLUP_CTL	0x20

/* Fields in PD67_MISC_CTL_3 */
#घोषणा PD67_MC3_IRQ_MASK	0x03
#घोषणा PD67_MC3_IRQ_PCPCI	0x00
#घोषणा PD67_MC3_IRQ_EXTERN	0x01
#घोषणा PD67_MC3_IRQ_PCIWAY	0x02
#घोषणा PD67_MC3_IRQ_PCI	0x03
#घोषणा PD67_MC3_PWR_MASK	0x0c
#घोषणा PD67_MC3_PWR_SERIAL	0x00
#घोषणा PD67_MC3_PWR_TI2202	0x08
#घोषणा PD67_MC3_PWR_SMB	0x0c

/* Register definitions क्रम Cirrus PD6832 PCI-to-CardBus bridge */

/* PD6832 extension रेजिस्टरs -- indexed in PD67_EXT_INDEX */
#घोषणा PD68_EXT_CTL_2			0x0b
#घोषणा PD68_PCI_SPACE			0x22
#घोषणा PD68_PCCARD_SPACE		0x23
#घोषणा PD68_WINDOW_TYPE		0x24
#घोषणा PD68_EXT_CSC			0x2e
#घोषणा PD68_MISC_CTL_4			0x2f
#घोषणा PD68_MISC_CTL_5			0x30
#घोषणा PD68_MISC_CTL_6			0x31

/* Extra flags in PD67_MISC_CTL_3 */
#घोषणा PD68_MC3_HW_SUSP		0x10
#घोषणा PD68_MC3_MM_EXPAND		0x40
#घोषणा PD68_MC3_MM_ARM			0x80

/* Bridge Control Register */
#घोषणा  PD6832_BCR_MGMT_IRQ_ENA	0x0800

/* Socket Number Register */
#घोषणा PD6832_SOCKET_NUMBER		0x004c	/* 8 bit */

#पूर्ण_अगर /* _LINUX_CIRRUS_H */
