<शैली गुरु>
/*
 * tcic.h 1.13 1999/10/25 20:03:34
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

#अगर_अघोषित _LINUX_TCIC_H
#घोषणा _LINUX_TCIC_H

#घोषणा TCIC_BASE		0x240

/* offsets of रेजिस्टरs from TCIC_BASE */
#घोषणा TCIC_DATA		0x00
#घोषणा TCIC_ADDR		0x02
#घोषणा TCIC_SCTRL		0x06
#घोषणा TCIC_SSTAT		0x07
#घोषणा TCIC_MODE		0x08
#घोषणा TCIC_PWR		0x09
#घोषणा TCIC_EDC		0x0A
#घोषणा TCIC_ICSR		0x0C
#घोषणा TCIC_IENA		0x0D
#घोषणा TCIC_AUX		0x0E

#घोषणा TCIC_SS_SHFT		12
#घोषणा TCIC_SS_MASK		0x7000

/* Flags क्रम TCIC_ADDR */
#घोषणा TCIC_ADR2_REG		0x8000
#घोषणा TCIC_ADR2_INDREG	0x0800

#घोषणा TCIC_ADDR_REG		0x80000000
#घोषणा TCIC_ADDR_SS_SHFT	(TCIC_SS_SHFT+16)
#घोषणा TCIC_ADDR_SS_MASK	(TCIC_SS_MASK<<16)
#घोषणा TCIC_ADDR_INDREG	0x08000000
#घोषणा TCIC_ADDR_IO		0x04000000
#घोषणा TCIC_ADDR_MASK		0x03ffffff

/* Flags क्रम TCIC_SCTRL */
#घोषणा TCIC_SCTRL_ENA		0x01
#घोषणा TCIC_SCTRL_INCMODE	0x18
#घोषणा TCIC_SCTRL_INCMODE_HOLD	0x00
#घोषणा TCIC_SCTRL_INCMODE_WORD	0x08
#घोषणा TCIC_SCTRL_INCMODE_REG	0x10
#घोषणा TCIC_SCTRL_INCMODE_AUTO	0x18
#घोषणा TCIC_SCTRL_EDCSUM	0x20
#घोषणा TCIC_SCTRL_RESET	0x80

/* Flags क्रम TCIC_SSTAT */
#घोषणा TCIC_SSTAT_6US		0x01
#घोषणा TCIC_SSTAT_10US		0x02
#घोषणा TCIC_SSTAT_PROGTIME	0x04
#घोषणा TCIC_SSTAT_LBAT1	0x08
#घोषणा TCIC_SSTAT_LBAT2	0x10
#घोषणा TCIC_SSTAT_RDY		0x20	/* Inverted */
#घोषणा TCIC_SSTAT_WP		0x40
#घोषणा TCIC_SSTAT_CD		0x80	/* Card detect */

/* Flags क्रम TCIC_MODE */
#घोषणा TCIC_MODE_PGMMASK	0x1f
#घोषणा TCIC_MODE_NORMAL	0x00
#घोषणा TCIC_MODE_PGMWR		0x01
#घोषणा TCIC_MODE_PGMRD		0x02
#घोषणा TCIC_MODE_PGMCE		0x04
#घोषणा TCIC_MODE_PGMDBW	0x08
#घोषणा TCIC_MODE_PGMWORD	0x10
#घोषणा TCIC_MODE_AUXSEL_MASK	0xe0

/* Registers accessed through TCIC_AUX, by setting TCIC_MODE */
#घोषणा TCIC_AUX_TCTL		(0<<5)
#घोषणा TCIC_AUX_PCTL		(1<<5)
#घोषणा TCIC_AUX_WCTL		(2<<5)
#घोषणा TCIC_AUX_EXTERN		(3<<5)
#घोषणा TCIC_AUX_PDATA		(4<<5)
#घोषणा TCIC_AUX_SYSCFG		(5<<5)
#घोषणा TCIC_AUX_ILOCK		(6<<5)
#घोषणा TCIC_AUX_TEST		(7<<5)

/* Flags क्रम TCIC_PWR */
#घोषणा TCIC_PWR_VCC(sock)	(0x01<<(sock))
#घोषणा TCIC_PWR_VCC_MASK	0x03
#घोषणा TCIC_PWR_VPP(sock)	(0x08<<(sock))
#घोषणा TCIC_PWR_VPP_MASK	0x18
#घोषणा TCIC_PWR_CLIMENA	0x40
#घोषणा TCIC_PWR_CLIMSTAT	0x80

/* Flags क्रम TCIC_ICSR */
#घोषणा TCIC_ICSR_CLEAR		0x01
#घोषणा TCIC_ICSR_SET		0x02
#घोषणा TCIC_ICSR_JAM		(TCIC_ICSR_CLEAR|TCIC_ICSR_SET)
#घोषणा TCIC_ICSR_STOPCPU	0x04
#घोषणा TCIC_ICSR_ILOCK		0x08
#घोषणा TCIC_ICSR_PROGTIME	0x10
#घोषणा TCIC_ICSR_ERR		0x20
#घोषणा TCIC_ICSR_CDCHG		0x40
#घोषणा TCIC_ICSR_IOCHK		0x80

/* Flags क्रम TCIC_IENA */
#घोषणा TCIC_IENA_CFG_MASK	0x03
#घोषणा TCIC_IENA_CFG_OFF	0x00	/* disabled */
#घोषणा TCIC_IENA_CFG_OD	0x01	/* active low, खोलो drain */
#घोषणा TCIC_IENA_CFG_LOW	0x02	/* active low, totem pole */
#घोषणा TCIC_IENA_CFG_HIGH	0x03	/* active high, totem pole */
#घोषणा TCIC_IENA_ILOCK		0x08
#घोषणा TCIC_IENA_PROGTIME	0x10
#घोषणा TCIC_IENA_ERR		0x20	/* overcurrent or iochk */
#घोषणा TCIC_IENA_CDCHG		0x40

/* Flags क्रम TCIC_AUX_WCTL */
#घोषणा TCIC_WAIT_COUNT_MASK	0x001f
#घोषणा TCIC_WAIT_ASYNC		0x0020
#घोषणा TCIC_WAIT_SENSE		0x0040
#घोषणा TCIC_WAIT_SRC		0x0080
#घोषणा TCIC_WCTL_WR		0x0100
#घोषणा TCIC_WCTL_RD		0x0200
#घोषणा TCIC_WCTL_CE		0x0400
#घोषणा TCIC_WCTL_LLBAT1	0x0800
#घोषणा TCIC_WCTL_LLBAT2	0x1000
#घोषणा TCIC_WCTL_LRDY		0x2000
#घोषणा TCIC_WCTL_LWP		0x4000
#घोषणा TCIC_WCTL_LCD		0x8000

/* Flags क्रम TCIC_AUX_SYSCFG */
#घोषणा TCIC_SYSCFG_IRQ_MASK	0x000f
#घोषणा TCIC_SYSCFG_MCSFULL	0x0010
#घोषणा TCIC_SYSCFG_IO1723	0x0020
#घोषणा TCIC_SYSCFG_MCSXB	0x0040
#घोषणा TCIC_SYSCFG_ICSXB	0x0080
#घोषणा TCIC_SYSCFG_NOPDN	0x0100
#घोषणा TCIC_SYSCFG_MPSEL_SHFT	9
#घोषणा TCIC_SYSCFG_MPSEL_MASK	0x0e00
#घोषणा TCIC_SYSCFG_MPSENSE	0x2000
#घोषणा TCIC_SYSCFG_AUTOBUSY	0x4000
#घोषणा TCIC_SYSCFG_ACC		0x8000

#घोषणा TCIC_ILOCK_OUT		0x01
#घोषणा TCIC_ILOCK_SENSE	0x02
#घोषणा TCIC_ILOCK_CRESET	0x04
#घोषणा TCIC_ILOCK_CRESENA	0x08
#घोषणा TCIC_ILOCK_CWAIT	0x10
#घोषणा TCIC_ILOCK_CWAITSNS	0x20
#घोषणा TCIC_ILOCK_HOLD_MASK	0xc0
#घोषणा TCIC_ILOCK_HOLD_CCLK	0xc0

#घोषणा TCIC_ILOCKTEST_ID_SH	8
#घोषणा TCIC_ILOCKTEST_ID_MASK	0x7f00
#घोषणा TCIC_ILOCKTEST_MCIC_1	0x8000

#घोषणा TCIC_ID_DB86082		0x02
#घोषणा TCIC_ID_DB86082A	0x03
#घोषणा TCIC_ID_DB86084		0x04
#घोषणा TCIC_ID_DB86084A	0x08
#घोषणा TCIC_ID_DB86072		0x15
#घोषणा TCIC_ID_DB86184		0x14
#घोषणा TCIC_ID_DB86082B	0x17

#घोषणा TCIC_TEST_DIAG		0x8000

/*
 * Indirectly addressed रेजिस्टरs
 */

#घोषणा TCIC_SCF1(sock)	((sock)<<3)
#घोषणा TCIC_SCF2(sock) (((sock)<<3)+2)

/* Flags क्रम SCF1 */
#घोषणा TCIC_SCF1_IRQ_MASK	0x000f
#घोषणा TCIC_SCF1_IRQ_OFF	0x0000
#घोषणा TCIC_SCF1_IRQOC		0x0010
#घोषणा TCIC_SCF1_PCVT		0x0020
#घोषणा TCIC_SCF1_IRDY		0x0040
#घोषणा TCIC_SCF1_ATA		0x0080
#घोषणा TCIC_SCF1_DMA_SHIFT	8
#घोषणा TCIC_SCF1_DMA_MASK	0x0700
#घोषणा TCIC_SCF1_DMA_OFF	0
#घोषणा TCIC_SCF1_DREQ2		2
#घोषणा TCIC_SCF1_IOSTS		0x0800
#घोषणा TCIC_SCF1_SPKR		0x1000
#घोषणा TCIC_SCF1_FINPACK	0x2000
#घोषणा TCIC_SCF1_DELWR		0x4000
#घोषणा TCIC_SCF1_HD7IDE	0x8000

/* Flags क्रम SCF2 */
#घोषणा TCIC_SCF2_RI		0x0001
#घोषणा TCIC_SCF2_IDBR		0x0002
#घोषणा TCIC_SCF2_MDBR		0x0004
#घोषणा TCIC_SCF2_MLBAT1	0x0008
#घोषणा TCIC_SCF2_MLBAT2	0x0010
#घोषणा TCIC_SCF2_MRDY		0x0020
#घोषणा TCIC_SCF2_MWP		0x0040
#घोषणा TCIC_SCF2_MCD		0x0080
#घोषणा TCIC_SCF2_MALL		0x00f8

/* Indirect addresses क्रम memory winकरोw रेजिस्टरs */
#घोषणा TCIC_MWIN(sock,map)	(0x100+(((map)+((sock)<<2))<<3))
#घोषणा TCIC_MBASE_X		2
#घोषणा TCIC_MMAP_X		4
#घोषणा TCIC_MCTL_X		6

#घोषणा TCIC_MBASE_4K_BIT	0x4000
#घोषणा TCIC_MBASE_HA_SHFT	12
#घोषणा TCIC_MBASE_HA_MASK	0x0fff

#घोषणा TCIC_MMAP_REG		0x8000
#घोषणा TCIC_MMAP_CA_SHFT	12
#घोषणा TCIC_MMAP_CA_MASK	0x3fff

#घोषणा TCIC_MCTL_WSCNT_MASK	0x001f
#घोषणा TCIC_MCTL_WCLK		0x0020
#घोषणा TCIC_MCTL_WCLK_CCLK	0x0000
#घोषणा TCIC_MCTL_WCLK_BCLK	0x0020
#घोषणा TCIC_MCTL_QUIET		0x0040
#घोषणा TCIC_MCTL_WP		0x0080
#घोषणा TCIC_MCTL_ACC		0x0100
#घोषणा TCIC_MCTL_KE		0x0200
#घोषणा TCIC_MCTL_EDC		0x0400
#घोषणा TCIC_MCTL_B8		0x0800
#घोषणा TCIC_MCTL_SS_SHFT	TCIC_SS_SHFT
#घोषणा TCIC_MCTL_SS_MASK	TCIC_SS_MASK
#घोषणा TCIC_MCTL_ENA		0x8000

/* Indirect addresses क्रम I/O winकरोw रेजिस्टरs */
#घोषणा TCIC_IWIN(sock,map)	(0x200+(((map)+((sock)<<1))<<2))
#घोषणा TCIC_IBASE_X		0
#घोषणा TCIC_ICTL_X		2

#घोषणा TCIC_ICTL_WSCNT_MASK	TCIC_MCTL_WSCNT_MASK
#घोषणा TCIC_ICTL_QUIET		TCIC_MCTL_QUIET
#घोषणा TCIC_ICTL_1K		0x0080
#घोषणा TCIC_ICTL_PASS16	0x0100
#घोषणा TCIC_ICTL_ACC		TCIC_MCTL_ACC
#घोषणा TCIC_ICTL_TINY		0x0200
#घोषणा TCIC_ICTL_B16		0x0400
#घोषणा TCIC_ICTL_B8		TCIC_MCTL_B8
#घोषणा TCIC_ICTL_BW_MASK	(TCIC_ICTL_B16|TCIC_ICTL_B8)
#घोषणा TCIC_ICTL_BW_DYN	0
#घोषणा TCIC_ICTL_BW_8		TCIC_ICTL_B8
#घोषणा TCIC_ICTL_BW_16		TCIC_ICTL_B16
#घोषणा TCIC_ICTL_BW_ATA	(TCIC_ICTL_B16|TCIC_ICTL_B8)
#घोषणा TCIC_ICTL_SS_SHFT	TCIC_SS_SHFT
#घोषणा TCIC_ICTL_SS_MASK	TCIC_SS_MASK
#घोषणा TCIC_ICTL_ENA		TCIC_MCTL_ENA

#पूर्ण_अगर /* _LINUX_TCIC_H */
