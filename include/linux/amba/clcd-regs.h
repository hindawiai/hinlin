<शैली गुरु>
/*
 * David A Rusling
 *
 * Copyright (C) 2001 ARM Limited
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित AMBA_CLCD_REGS_H
#घोषणा AMBA_CLCD_REGS_H

/*
 * CLCD Controller Internal Register addresses
 */
#घोषणा CLCD_TIM0		0x00000000
#घोषणा CLCD_TIM1 		0x00000004
#घोषणा CLCD_TIM2 		0x00000008
#घोषणा CLCD_TIM3 		0x0000000c
#घोषणा CLCD_UBAS 		0x00000010
#घोषणा CLCD_LBAS 		0x00000014

#घोषणा CLCD_PL110_IENB		0x00000018
#घोषणा CLCD_PL110_CNTL		0x0000001c
#घोषणा CLCD_PL110_STAT		0x00000020
#घोषणा CLCD_PL110_INTR 	0x00000024
#घोषणा CLCD_PL110_UCUR		0x00000028
#घोषणा CLCD_PL110_LCUR		0x0000002C

#घोषणा CLCD_PL111_CNTL		0x00000018
#घोषणा CLCD_PL111_IENB		0x0000001c
#घोषणा CLCD_PL111_RIS		0x00000020
#घोषणा CLCD_PL111_MIS		0x00000024
#घोषणा CLCD_PL111_ICR		0x00000028
#घोषणा CLCD_PL111_UCUR		0x0000002c
#घोषणा CLCD_PL111_LCUR		0x00000030

#घोषणा CLCD_PALL 		0x00000200
#घोषणा CLCD_PALETTE		0x00000200

#घोषणा TIM2_PCD_LO_MASK	GENMASK(4, 0)
#घोषणा TIM2_PCD_LO_BITS	5
#घोषणा TIM2_CLKSEL		(1 << 5)
#घोषणा TIM2_ACB_MASK		GENMASK(10, 6)
#घोषणा TIM2_IVS		(1 << 11)
#घोषणा TIM2_IHS		(1 << 12)
#घोषणा TIM2_IPC		(1 << 13)
#घोषणा TIM2_IOE		(1 << 14)
#घोषणा TIM2_BCD		(1 << 26)
#घोषणा TIM2_PCD_HI_MASK	GENMASK(31, 27)
#घोषणा TIM2_PCD_HI_BITS	5
#घोषणा TIM2_PCD_HI_SHIFT	27

#घोषणा CNTL_LCDEN		(1 << 0)
#घोषणा CNTL_LCDBPP1		(0 << 1)
#घोषणा CNTL_LCDBPP2		(1 << 1)
#घोषणा CNTL_LCDBPP4		(2 << 1)
#घोषणा CNTL_LCDBPP8		(3 << 1)
#घोषणा CNTL_LCDBPP16		(4 << 1)
#घोषणा CNTL_LCDBPP16_565	(6 << 1)
#घोषणा CNTL_LCDBPP16_444	(7 << 1)
#घोषणा CNTL_LCDBPP24		(5 << 1)
#घोषणा CNTL_LCDBW		(1 << 4)
#घोषणा CNTL_LCDTFT		(1 << 5)
#घोषणा CNTL_LCDMONO8		(1 << 6)
#घोषणा CNTL_LCDDUAL		(1 << 7)
#घोषणा CNTL_BGR		(1 << 8)
#घोषणा CNTL_BEBO		(1 << 9)
#घोषणा CNTL_BEPO		(1 << 10)
#घोषणा CNTL_LCDPWR		(1 << 11)
#घोषणा CNTL_LCDVCOMP(x)	((x) << 12)
#घोषणा CNTL_LDMAFIFOTIME	(1 << 15)
#घोषणा CNTL_WATERMARK		(1 << 16)

/* ST Microelectronics variant bits */
#घोषणा CNTL_ST_1XBPP_444	0x0
#घोषणा CNTL_ST_1XBPP_5551	(1 << 17)
#घोषणा CNTL_ST_1XBPP_565	(1 << 18)
#घोषणा CNTL_ST_CDWID_12	0x0
#घोषणा CNTL_ST_CDWID_16	(1 << 19)
#घोषणा CNTL_ST_CDWID_18	(1 << 20)
#घोषणा CNTL_ST_CDWID_24	((1 << 19)|(1 << 20))
#घोषणा CNTL_ST_CEAEN		(1 << 21)
#घोषणा CNTL_ST_LCDBPP24_PACKED	(6 << 1)

#पूर्ण_अगर /* AMBA_CLCD_REGS_H */
