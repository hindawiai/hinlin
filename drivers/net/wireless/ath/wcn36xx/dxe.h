<शैली गुरु>
/*
 * Copyright (c) 2013 Eugene Krasnikov <k.eugene.e@gmail.com>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित _DXE_H_
#घोषणा _DXE_H_

#समावेश "wcn36xx.h"

/*
TX_LOW	= DMA0
TX_HIGH	= DMA4
RX_LOW	= DMA1
RX_HIGH	= DMA3
H2H_TEST_RX_TX = DMA2
*/

/* DXE रेजिस्टरs */
#घोषणा WCN36XX_DXE_MEM_REG			0

#घोषणा WCN36XX_CCU_DXE_INT_SELECT_RIVA		0x310
#घोषणा WCN36XX_CCU_DXE_INT_SELECT_PRONTO	0x10dc

/* Descriptor valid */
#घोषणा WCN36xx_DXE_CTRL_VLD		BIT(0)
/* End of packet */
#घोषणा WCN36xx_DXE_CTRL_EOP		BIT(3)
/* BD handling bit */
#घोषणा WCN36xx_DXE_CTRL_BDH		BIT(4)
/* Source is a queue */
#घोषणा WCN36xx_DXE_CTRL_SIQ		BIT(5)
/* Destination is a queue */
#घोषणा WCN36xx_DXE_CTRL_DIQ		BIT(6)
/* Poपूर्णांकer address is a queue */
#घोषणा WCN36xx_DXE_CTRL_PIQ		BIT(7)
/* Release PDU when करोne */
#घोषणा WCN36xx_DXE_CTRL_PDU_REL	BIT(8)
/* STOP channel processing */
#घोषणा WCN36xx_DXE_CTRL_STOP		BIT(16)
/* INT on descriptor करोne */
#घोषणा WCN36xx_DXE_CTRL_INT		BIT(17)
/* Endian byte swap enable */
#घोषणा WCN36xx_DXE_CTRL_SWAP		BIT(20)
/* Master endianness */
#घोषणा WCN36xx_DXE_CTRL_ENDIANNESS	BIT(21)

/* Transfer type */
#घोषणा WCN36xx_DXE_CTRL_XTYPE_SHIFT 1
#घोषणा WCN36xx_DXE_CTRL_XTYPE_MASK GENMASK(2, WCN36xx_DXE_CTRL_XTYPE_SHIFT)
#घोषणा WCN36xx_DXE_CTRL_XTYPE_SET(x)	((x) << WCN36xx_DXE_CTRL_XTYPE_SHIFT)

/* BMU Threshold select */
#घोषणा WCN36xx_DXE_CTRL_BTHLD_SEL_SHIFT 9
#घोषणा WCN36xx_DXE_CTRL_BTHLD_SEL_MASK GENMASK(12, WCN36xx_DXE_CTRL_BTHLD_SEL_SHIFT)
#घोषणा WCN36xx_DXE_CTRL_BTHLD_SEL_SET(x) ((x) << WCN36xx_DXE_CTRL_BTHLD_SEL_SHIFT)

/* Priority */
#घोषणा WCN36xx_DXE_CTRL_PRIO_SHIFT 13
#घोषणा WCN36xx_DXE_CTRL_PRIO_MASK GENMASK(15, WCN36xx_DXE_CTRL_PRIO_SHIFT)
#घोषणा WCN36xx_DXE_CTRL_PRIO_SET(x) ((x) << WCN36xx_DXE_CTRL_PRIO_SHIFT)

/* BD Template index */
#घोषणा WCN36xx_DXE_CTRL_BDT_IDX_SHIFT 18
#घोषणा WCN36xx_DXE_CTRL_BDT_IDX_MASK GENMASK(19, WCN36xx_DXE_CTRL_BDT_IDX_SHIFT)
#घोषणा WCN36xx_DXE_CTRL_BDT_IDX_SET(x) ((x) << WCN36xx_DXE_CTRL_BDT_IDX_SHIFT)

/* Transfer types: */
/* Host to host */
#घोषणा WCN36xx_DXE_XTYPE_H2H (0)
/* Host to BMU */
#घोषणा WCN36xx_DXE_XTYPE_H2B (2)
/* BMU to host */
#घोषणा WCN36xx_DXE_XTYPE_B2H (3)

#घोषणा WCN36XX_DXE_CTRL_TX_L	(WCN36xx_DXE_CTRL_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
	WCN36xx_DXE_CTRL_DIQ | WCN36xx_DXE_CTRL_BTHLD_SEL_SET(5) | \
	WCN36xx_DXE_CTRL_PRIO_SET(4) | WCN36xx_DXE_CTRL_INT | \
	WCN36xx_DXE_CTRL_SWAP | WCN36xx_DXE_CTRL_ENDIANNESS)

#घोषणा WCN36XX_DXE_CTRL_TX_H	 (WCN36xx_DXE_CTRL_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
	WCN36xx_DXE_CTRL_DIQ | WCN36xx_DXE_CTRL_BTHLD_SEL_SET(7) | \
	WCN36xx_DXE_CTRL_PRIO_SET(6) | WCN36xx_DXE_CTRL_INT | \
	WCN36xx_DXE_CTRL_SWAP | WCN36xx_DXE_CTRL_ENDIANNESS)

#घोषणा WCN36XX_DXE_CTRL_RX_L	(WCN36xx_DXE_CTRL_VLD | \
	WCN36xx_DXE_CTRL_XTYPE_SET(WCN36xx_DXE_XTYPE_B2H) | \
	WCN36xx_DXE_CTRL_EOP | WCN36xx_DXE_CTRL_SIQ | \
	WCN36xx_DXE_CTRL_PDU_REL | WCN36xx_DXE_CTRL_BTHLD_SEL_SET(6) | \
	WCN36xx_DXE_CTRL_PRIO_SET(5) | WCN36xx_DXE_CTRL_INT | \
	WCN36xx_DXE_CTRL_SWAP)

#घोषणा WCN36XX_DXE_CTRL_RX_H	(WCN36xx_DXE_CTRL_VLD | \
	WCN36xx_DXE_CTRL_XTYPE_SET(WCN36xx_DXE_XTYPE_B2H) | \
	WCN36xx_DXE_CTRL_EOP | WCN36xx_DXE_CTRL_SIQ | \
	WCN36xx_DXE_CTRL_PDU_REL |  WCN36xx_DXE_CTRL_BTHLD_SEL_SET(8) | \
	WCN36xx_DXE_CTRL_PRIO_SET(6) | WCN36xx_DXE_CTRL_INT | \
	WCN36xx_DXE_CTRL_SWAP)

#घोषणा WCN36XX_DXE_CTRL_TX_H_BD	(WCN36xx_DXE_CTRL_VLD | \
	WCN36xx_DXE_CTRL_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
	WCN36xx_DXE_CTRL_DIQ | WCN36xx_DXE_CTRL_BTHLD_SEL_SET(7) | \
	WCN36xx_DXE_CTRL_PRIO_SET(6) | WCN36xx_DXE_CTRL_SWAP | \
	WCN36xx_DXE_CTRL_ENDIANNESS)

#घोषणा WCN36XX_DXE_CTRL_TX_H_SKB	(WCN36xx_DXE_CTRL_VLD | \
	WCN36xx_DXE_CTRL_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
	WCN36xx_DXE_CTRL_EOP | WCN36xx_DXE_CTRL_DIQ | \
	WCN36xx_DXE_CTRL_BTHLD_SEL_SET(7) | WCN36xx_DXE_CTRL_PRIO_SET(6) | \
	WCN36xx_DXE_CTRL_INT | WCN36xx_DXE_CTRL_SWAP | \
	WCN36xx_DXE_CTRL_ENDIANNESS)

#घोषणा WCN36XX_DXE_CTRL_TX_L_BD	 (WCN36xx_DXE_CTRL_VLD | \
	WCN36xx_DXE_CTRL_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
	WCN36xx_DXE_CTRL_DIQ | WCN36xx_DXE_CTRL_BTHLD_SEL_SET(5) | \
	WCN36xx_DXE_CTRL_PRIO_SET(4) | WCN36xx_DXE_CTRL_SWAP | \
	WCN36xx_DXE_CTRL_ENDIANNESS)

#घोषणा WCN36XX_DXE_CTRL_TX_L_SKB	(WCN36xx_DXE_CTRL_VLD | \
	WCN36xx_DXE_CTRL_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
	WCN36xx_DXE_CTRL_EOP | WCN36xx_DXE_CTRL_DIQ | \
	WCN36xx_DXE_CTRL_BTHLD_SEL_SET(5) | WCN36xx_DXE_CTRL_PRIO_SET(4) | \
	WCN36xx_DXE_CTRL_INT | WCN36xx_DXE_CTRL_SWAP | \
	WCN36xx_DXE_CTRL_ENDIANNESS)

/* TODO This must calculated properly but not hardcoded */
#घोषणा WCN36XX_DXE_WQ_TX_L			0x17
#घोषणा WCN36XX_DXE_WQ_TX_H			0x17
#घोषणा WCN36XX_DXE_WQ_RX_L			0xB
#घोषणा WCN36XX_DXE_WQ_RX_H			0x4

/* Channel enable or restart */
#घोषणा WCN36xx_DXE_CH_CTRL_EN			BIT(0)
/* End of packet bit */
#घोषणा WCN36xx_DXE_CH_CTRL_EOP			BIT(3)
/* BD Handling bit */
#घोषणा WCN36xx_DXE_CH_CTRL_BDH			BIT(4)
/* Source is queue */
#घोषणा WCN36xx_DXE_CH_CTRL_SIQ			BIT(5)
/* Destination is queue */
#घोषणा WCN36xx_DXE_CH_CTRL_DIQ			BIT(6)
/* Poपूर्णांकer descriptor is queue */
#घोषणा WCN36xx_DXE_CH_CTRL_PIQ			BIT(7)
/* Relase PDU when करोne */
#घोषणा WCN36xx_DXE_CH_CTRL_PDU_REL		BIT(8)
/* Stop channel processing */
#घोषणा WCN36xx_DXE_CH_CTRL_STOP		BIT(16)
/* Enable बाह्यal descriptor पूर्णांकerrupt */
#घोषणा WCN36xx_DXE_CH_CTRL_INE_ED		BIT(17)
/* Enable channel पूर्णांकerrupt on errors */
#घोषणा WCN36xx_DXE_CH_CTRL_INE_ERR		BIT(18)
/* Enable Channel पूर्णांकerrupt when करोne */
#घोषणा WCN36xx_DXE_CH_CTRL_INE_DONE	BIT(19)
/* External descriptor enable */
#घोषणा WCN36xx_DXE_CH_CTRL_EDEN		BIT(20)
/* Wait क्रम valid bit */
#घोषणा WCN36xx_DXE_CH_CTRL_EDVEN		BIT(21)
/* Endianness is little endian*/
#घोषणा WCN36xx_DXE_CH_CTRL_ENDIANNESS	BIT(26)
/* Abort transfer */
#घोषणा WCN36xx_DXE_CH_CTRL_ABORT		BIT(27)
/* Long descriptor क्रमmat */
#घोषणा WCN36xx_DXE_CH_CTRL_DFMT		BIT(28)
/* Endian byte swap enable */
#घोषणा WCN36xx_DXE_CH_CTRL_SWAP		BIT(31)

/* Transfer type */
#घोषणा WCN36xx_DXE_CH_CTRL_XTYPE_SHIFT 1
#घोषणा WCN36xx_DXE_CH_CTRL_XTYPE_MASK GENMASK(2, WCN36xx_DXE_CH_CTRL_XTYPE_SHIFT)
#घोषणा WCN36xx_DXE_CH_CTRL_XTYPE_SET(x)	((x) << WCN36xx_DXE_CH_CTRL_XTYPE_SHIFT)

/* Channel BMU Threshold select */
#घोषणा WCN36xx_DXE_CH_CTRL_BTHLD_SEL_SHIFT 9
#घोषणा WCN36xx_DXE_CH_CTRL_BTHLD_SEL_MASK GENMASK(12, WCN36xx_DXE_CH_CTRL_BTHLD_SEL_SHIFT)
#घोषणा WCN36xx_DXE_CH_CTRL_BTHLD_SEL_SET(x) ((x) << WCN36xx_DXE_CH_CTRL_BTHLD_SEL_SHIFT)

/* Channel Priority */
#घोषणा WCN36xx_DXE_CH_CTRL_PRIO_SHIFT 13
#घोषणा WCN36xx_DXE_CH_CTRL_PRIO_MASK GENMASK(15, WCN36xx_DXE_CH_CTRL_PRIO_SHIFT)
#घोषणा WCN36xx_DXE_CH_CTRL_PRIO_SET(x) ((x) << WCN36xx_DXE_CH_CTRL_PRIO_SHIFT)

/* Counter select */
#घोषणा WCN36xx_DXE_CH_CTRL_SEL_SHIFT 22
#घोषणा WCN36xx_DXE_CH_CTRL_SEL_MASK GENMASK(25, WCN36xx_DXE_CH_CTRL_SEL_SHIFT)
#घोषणा WCN36xx_DXE_CH_CTRL_SEL_SET(x)	((x) << WCN36xx_DXE_CH_CTRL_SEL_SHIFT)

/* Channel BD ढाँचा index */
#घोषणा WCN36xx_DXE_CH_CTRL_BDT_IDX_SHIFT 29
#घोषणा WCN36xx_DXE_CH_CTRL_BDT_IDX_MASK GENMASK(30, WCN36xx_DXE_CH_CTRL_BDT_IDX_SHIFT)
#घोषणा WCN36xx_DXE_CH_CTRL_BDT_IDX_SET(x)	((x) << WCN36xx_DXE_CH_CTRL_BDT_IDX_SHIFT)

/* DXE शेष control रेजिस्टर values */
#घोषणा WCN36XX_DXE_CH_DEFAULT_CTL_RX_L (WCN36xx_DXE_CH_CTRL_EN | \
		WCN36xx_DXE_CH_CTRL_XTYPE_SET(WCN36xx_DXE_XTYPE_B2H) | \
		WCN36xx_DXE_CH_CTRL_EOP | WCN36xx_DXE_CH_CTRL_SIQ | \
		WCN36xx_DXE_CH_CTRL_PDU_REL | WCN36xx_DXE_CH_CTRL_BTHLD_SEL_SET(6) | \
		WCN36xx_DXE_CH_CTRL_PRIO_SET(5) | WCN36xx_DXE_CH_CTRL_INE_ED | \
		WCN36xx_DXE_CH_CTRL_INE_ERR | WCN36xx_DXE_CH_CTRL_INE_DONE | \
		WCN36xx_DXE_CH_CTRL_EDEN | WCN36xx_DXE_CH_CTRL_EDVEN | \
		WCN36xx_DXE_CH_CTRL_SEL_SET(1) | WCN36xx_DXE_CH_CTRL_ENDIANNESS | \
		WCN36xx_DXE_CH_CTRL_SWAP)

#घोषणा WCN36XX_DXE_CH_DEFAULT_CTL_RX_H (WCN36xx_DXE_CH_CTRL_EN | \
		WCN36xx_DXE_CH_CTRL_XTYPE_SET(WCN36xx_DXE_XTYPE_B2H) | \
		WCN36xx_DXE_CH_CTRL_EOP | WCN36xx_DXE_CH_CTRL_SIQ | \
		WCN36xx_DXE_CH_CTRL_PDU_REL | WCN36xx_DXE_CH_CTRL_BTHLD_SEL_SET(8) | \
		WCN36xx_DXE_CH_CTRL_PRIO_SET(6) | WCN36xx_DXE_CH_CTRL_INE_ED | \
		WCN36xx_DXE_CH_CTRL_INE_ERR | WCN36xx_DXE_CH_CTRL_INE_DONE | \
		WCN36xx_DXE_CH_CTRL_EDEN | WCN36xx_DXE_CH_CTRL_EDVEN | \
		WCN36xx_DXE_CH_CTRL_SEL_SET(3) | WCN36xx_DXE_CH_CTRL_ENDIANNESS | \
		WCN36xx_DXE_CH_CTRL_SWAP)

#घोषणा WCN36XX_DXE_CH_DEFAULT_CTL_TX_H	(WCN36xx_DXE_CH_CTRL_EN | \
		WCN36xx_DXE_CH_CTRL_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
		WCN36xx_DXE_CH_CTRL_EOP | WCN36xx_DXE_CH_CTRL_DIQ | \
		WCN36xx_DXE_CH_CTRL_PDU_REL | WCN36xx_DXE_CH_CTRL_BTHLD_SEL_SET(7) | \
		WCN36xx_DXE_CH_CTRL_PRIO_SET(6) | WCN36xx_DXE_CH_CTRL_INE_ED | \
		WCN36xx_DXE_CH_CTRL_INE_ERR | WCN36xx_DXE_CH_CTRL_INE_DONE | \
		WCN36xx_DXE_CH_CTRL_EDEN | WCN36xx_DXE_CH_CTRL_EDVEN | \
		WCN36xx_DXE_CH_CTRL_SEL_SET(4) | WCN36xx_DXE_CH_CTRL_ENDIANNESS | \
		WCN36xx_DXE_CH_CTRL_SWAP)

#घोषणा WCN36XX_DXE_CH_DEFAULT_CTL_TX_L (WCN36xx_DXE_CH_CTRL_EN | \
		WCN36xx_DXE_CH_CTRL_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
		WCN36xx_DXE_CH_CTRL_EOP | WCN36xx_DXE_CH_CTRL_DIQ | \
		WCN36xx_DXE_CH_CTRL_PDU_REL | WCN36xx_DXE_CH_CTRL_BTHLD_SEL_SET(5) | \
		WCN36xx_DXE_CH_CTRL_PRIO_SET(4) | WCN36xx_DXE_CH_CTRL_INE_ED | \
		WCN36xx_DXE_CH_CTRL_INE_ERR | WCN36xx_DXE_CH_CTRL_INE_DONE | \
		WCN36xx_DXE_CH_CTRL_EDEN | WCN36xx_DXE_CH_CTRL_EDVEN | \
		WCN36xx_DXE_CH_CTRL_SEL_SET(0) | WCN36xx_DXE_CH_CTRL_ENDIANNESS | \
		WCN36xx_DXE_CH_CTRL_SWAP)

/* Common DXE रेजिस्टरs */
#घोषणा WCN36XX_DXE_MEM_CSR			(WCN36XX_DXE_MEM_REG + 0x00)
#घोषणा WCN36XX_DXE_REG_CSR_RESET		(WCN36XX_DXE_MEM_REG + 0x00)
#घोषणा WCN36XX_DXE_ENCH_ADDR			(WCN36XX_DXE_MEM_REG + 0x04)
#घोषणा WCN36XX_DXE_REG_CH_EN			(WCN36XX_DXE_MEM_REG + 0x08)
#घोषणा WCN36XX_DXE_REG_CH_DONE			(WCN36XX_DXE_MEM_REG + 0x0C)
#घोषणा WCN36XX_DXE_REG_CH_ERR			(WCN36XX_DXE_MEM_REG + 0x10)
#घोषणा WCN36XX_DXE_INT_MASK_REG		(WCN36XX_DXE_MEM_REG + 0x18)
#घोषणा WCN36XX_DXE_INT_SRC_RAW_REG		(WCN36XX_DXE_MEM_REG + 0x20)
	/* #घोषणा WCN36XX_DXE_INT_CH6_MASK	0x00000040 */
	/* #घोषणा WCN36XX_DXE_INT_CH5_MASK	0x00000020 */
	#घोषणा WCN36XX_DXE_INT_CH4_MASK	0x00000010
	#घोषणा WCN36XX_DXE_INT_CH3_MASK	0x00000008
	/* #घोषणा WCN36XX_DXE_INT_CH2_MASK	0x00000004 */
	#घोषणा WCN36XX_DXE_INT_CH1_MASK	0x00000002
	#घोषणा WCN36XX_DXE_INT_CH0_MASK	0x00000001
#घोषणा WCN36XX_DXE_0_INT_CLR			(WCN36XX_DXE_MEM_REG + 0x30)
#घोषणा WCN36XX_DXE_0_INT_ED_CLR		(WCN36XX_DXE_MEM_REG + 0x34)
#घोषणा WCN36XX_DXE_0_INT_DONE_CLR		(WCN36XX_DXE_MEM_REG + 0x38)
#घोषणा WCN36XX_DXE_0_INT_ERR_CLR		(WCN36XX_DXE_MEM_REG + 0x3C)

#घोषणा WCN36XX_CH_STAT_INT_DONE_MASK   0x00008000
#घोषणा WCN36XX_CH_STAT_INT_ERR_MASK    0x00004000
#घोषणा WCN36XX_CH_STAT_INT_ED_MASK     0x00002000

#घोषणा WCN36XX_DXE_0_CH0_STATUS		(WCN36XX_DXE_MEM_REG + 0x404)
#घोषणा WCN36XX_DXE_0_CH1_STATUS		(WCN36XX_DXE_MEM_REG + 0x444)
#घोषणा WCN36XX_DXE_0_CH2_STATUS		(WCN36XX_DXE_MEM_REG + 0x484)
#घोषणा WCN36XX_DXE_0_CH3_STATUS		(WCN36XX_DXE_MEM_REG + 0x4C4)
#घोषणा WCN36XX_DXE_0_CH4_STATUS		(WCN36XX_DXE_MEM_REG + 0x504)

#घोषणा WCN36XX_DXE_REG_RESET			0x5c89

/* Temporary BMU Workqueue 4 */
#घोषणा WCN36XX_DXE_BMU_WQ_RX_LOW		0xB
#घोषणा WCN36XX_DXE_BMU_WQ_RX_HIGH		0x4
/* DMA channel offset */
#घोषणा WCN36XX_DXE_TX_LOW_OFFSET		0x400
#घोषणा WCN36XX_DXE_TX_HIGH_OFFSET		0x500
#घोषणा WCN36XX_DXE_RX_LOW_OFFSET		0x440
#घोषणा WCN36XX_DXE_RX_HIGH_OFFSET		0x4C0

/* Address of the next DXE descriptor */
#घोषणा WCN36XX_DXE_CH_NEXT_DESC_ADDR		0x001C
#घोषणा WCN36XX_DXE_CH_NEXT_DESC_ADDR_TX_L	(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_TX_LOW_OFFSET + \
						 WCN36XX_DXE_CH_NEXT_DESC_ADDR)
#घोषणा WCN36XX_DXE_CH_NEXT_DESC_ADDR_TX_H	(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_TX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_NEXT_DESC_ADDR)
#घोषणा WCN36XX_DXE_CH_NEXT_DESC_ADDR_RX_L	(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_RX_LOW_OFFSET + \
						 WCN36XX_DXE_CH_NEXT_DESC_ADDR)
#घोषणा WCN36XX_DXE_CH_NEXT_DESC_ADDR_RX_H	(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_RX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_NEXT_DESC_ADDR)

/* DXE Descriptor source address */
#घोषणा WCN36XX_DXE_CH_SRC_ADDR			0x000C
#घोषणा WCN36XX_DXE_CH_SRC_ADDR_RX_L		(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_RX_LOW_OFFSET + \
						 WCN36XX_DXE_CH_SRC_ADDR)
#घोषणा WCN36XX_DXE_CH_SRC_ADDR_RX_H		(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_RX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_SRC_ADDR)

/* DXE Descriptor address destination address */
#घोषणा WCN36XX_DXE_CH_DEST_ADDR		0x0014
#घोषणा WCN36XX_DXE_CH_DEST_ADDR_TX_L		(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_TX_LOW_OFFSET + \
						 WCN36XX_DXE_CH_DEST_ADDR)
#घोषणा WCN36XX_DXE_CH_DEST_ADDR_TX_H		(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_TX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_DEST_ADDR)
#घोषणा WCN36XX_DXE_CH_DEST_ADDR_RX_L		(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_RX_LOW_OFFSET + \
						 WCN36XX_DXE_CH_DEST_ADDR)
#घोषणा WCN36XX_DXE_CH_DEST_ADDR_RX_H		(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_RX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_DEST_ADDR)

/* Interrupt status */
#घोषणा WCN36XX_DXE_CH_STATUS_REG_ADDR		0x0004
#घोषणा WCN36XX_DXE_CH_STATUS_REG_ADDR_TX_L	(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_TX_LOW_OFFSET + \
						 WCN36XX_DXE_CH_STATUS_REG_ADDR)
#घोषणा WCN36XX_DXE_CH_STATUS_REG_ADDR_TX_H	(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_TX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_STATUS_REG_ADDR)
#घोषणा WCN36XX_DXE_CH_STATUS_REG_ADDR_RX_L	(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_RX_LOW_OFFSET + \
						 WCN36XX_DXE_CH_STATUS_REG_ADDR)
#घोषणा WCN36XX_DXE_CH_STATUS_REG_ADDR_RX_H	(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_RX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_STATUS_REG_ADDR)


/* DXE शेष control रेजिस्टर */
#घोषणा WCN36XX_DXE_REG_CTL_RX_L		(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_RX_LOW_OFFSET)
#घोषणा WCN36XX_DXE_REG_CTL_RX_H		(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_RX_HIGH_OFFSET)
#घोषणा WCN36XX_DXE_REG_CTL_TX_H		(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_TX_HIGH_OFFSET)
#घोषणा WCN36XX_DXE_REG_CTL_TX_L		(WCN36XX_DXE_MEM_REG + \
						 WCN36XX_DXE_TX_LOW_OFFSET)

#घोषणा WCN36XX_SMSM_WLAN_TX_ENABLE		0x00000400
#घोषणा WCN36XX_SMSM_WLAN_TX_RINGS_EMPTY	0x00000200


/* Interrupt control channel mask */
#घोषणा WCN36XX_INT_MASK_CHAN_TX_L		0x00000001
#घोषणा WCN36XX_INT_MASK_CHAN_RX_L		0x00000002
#घोषणा WCN36XX_INT_MASK_CHAN_RX_H		0x00000008
#घोषणा WCN36XX_INT_MASK_CHAN_TX_H		0x00000010

#घोषणा WCN36XX_BD_CHUNK_SIZE			128

#घोषणा WCN36XX_PKT_SIZE			0xF20
क्रमागत wcn36xx_dxe_ch_type अणु
	WCN36XX_DXE_CH_TX_L,
	WCN36XX_DXE_CH_TX_H,
	WCN36XX_DXE_CH_RX_L,
	WCN36XX_DXE_CH_RX_H
पूर्ण;

/* amount of descriptors per channel */
क्रमागत wcn36xx_dxe_ch_desc_num अणु
	WCN36XX_DXE_CH_DESC_NUMB_TX_L		= 128,
	WCN36XX_DXE_CH_DESC_NUMB_TX_H		= 10,
	WCN36XX_DXE_CH_DESC_NUMB_RX_L		= 512,
	WCN36XX_DXE_CH_DESC_NUMB_RX_H		= 40
पूर्ण;

/**
 * काष्ठा wcn36xx_dxe_desc - describes descriptor of one DXE buffer
 *
 * @ctrl: is a जोड़ that consists of following bits:
 * जोड़ अणु
 *	u32	valid		:1; //0 = DMA stop, 1 = DMA जारी with this
 *				    //descriptor
 *	u32	transfer_type	:2; //0 = Host to Host space
 *	u32	eop		:1; //End of Packet
 *	u32	bd_handling	:1; //अगर transferType = Host to BMU, then 0
 *				    // means first 128 bytes contain BD, and 1
 *				    // means create new empty BD
 *	u32	siq		:1; // SIQ
 *	u32	diq		:1; // DIQ
 *	u32	pdu_rel		:1; //0 = करोn't release BD and PDUs when करोne,
 *				    // 1 = release them
 *	u32	bthld_sel	:4; //BMU Threshold Select
 *	u32	prio		:3; //Specअगरies the priority level to use क्रम
 *				    // the transfer
 *	u32	stop_channel	:1; //1 = DMA stops processing further, channel
 *				    //requires re-enabling after this
 *	u32	पूर्णांकr		:1; //Interrupt on Descriptor Done
 *	u32	rsvd		:1; //reserved
 *	u32	size		:14;//14 bits used - ignored क्रम BMU transfers,
 *				    //only used क्रम host to host transfers?
 * पूर्ण ctrl;
 */
काष्ठा wcn36xx_dxe_desc अणु
	u32	ctrl;
	u32	fr_len;

	u32	src_addr_l;
	u32	dst_addr_l;
	u32	phy_next_l;
	u32	src_addr_h;
	u32	dst_addr_h;
	u32	phy_next_h;
पूर्ण __packed;

/* DXE Control block */
काष्ठा wcn36xx_dxe_ctl अणु
	काष्ठा wcn36xx_dxe_ctl	*next;
	काष्ठा wcn36xx_dxe_desc	*desc;
	अचिन्हित पूर्णांक		desc_phy_addr;
	पूर्णांक			ctl_blk_order;
	काष्ठा sk_buff		*skb;
	व्योम			*bd_cpu_addr;
	dma_addr_t		bd_phy_addr;
पूर्ण;

काष्ठा wcn36xx_dxe_ch अणु
	spinlock_t			lock;	/* protects head/tail ptrs */
	क्रमागत wcn36xx_dxe_ch_type	ch_type;
	व्योम				*cpu_addr;
	dma_addr_t			dma_addr;
	क्रमागत wcn36xx_dxe_ch_desc_num	desc_num;
	/* DXE control block ring */
	काष्ठा wcn36xx_dxe_ctl		*head_blk_ctl;
	काष्ठा wcn36xx_dxe_ctl		*tail_blk_ctl;

	/* DXE channel specअगरic configs */
	u32				dxe_wq;
	u32				ctrl_bd;
	u32				ctrl_skb;
	u32				reg_ctrl;
	u32				def_ctrl;
पूर्ण;

/* Memory Pool क्रम BD headers */
काष्ठा wcn36xx_dxe_mem_pool अणु
	पूर्णांक		chunk_size;
	व्योम		*virt_addr;
	dma_addr_t	phy_addr;
पूर्ण;

काष्ठा wcn36xx_tx_bd;
काष्ठा wcn36xx_vअगर;
पूर्णांक wcn36xx_dxe_allocate_mem_pools(काष्ठा wcn36xx *wcn);
व्योम wcn36xx_dxe_मुक्त_mem_pools(काष्ठा wcn36xx *wcn);
व्योम wcn36xx_dxe_rx_frame(काष्ठा wcn36xx *wcn);
पूर्णांक wcn36xx_dxe_alloc_ctl_blks(काष्ठा wcn36xx *wcn);
व्योम wcn36xx_dxe_मुक्त_ctl_blks(काष्ठा wcn36xx *wcn);
पूर्णांक wcn36xx_dxe_init(काष्ठा wcn36xx *wcn);
व्योम wcn36xx_dxe_deinit(काष्ठा wcn36xx *wcn);
पूर्णांक wcn36xx_dxe_init_channels(काष्ठा wcn36xx *wcn);
पूर्णांक wcn36xx_dxe_tx_frame(काष्ठा wcn36xx *wcn,
			 काष्ठा wcn36xx_vअगर *vअगर_priv,
			 काष्ठा wcn36xx_tx_bd *bd,
			 काष्ठा sk_buff *skb,
			 bool is_low);
व्योम wcn36xx_dxe_tx_ack_ind(काष्ठा wcn36xx *wcn, u32 status);
#पूर्ण_अगर	/* _DXE_H_ */
