<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * CoreChip-sz SR9700 one chip USB 1.1 Ethernet Devices
 *
 * Author : Liu Junliang <liujunliang_ljl@163.com>
 */

#अगर_अघोषित _SR9700_H
#घोषणा	_SR9700_H

/* sr9700 spec. रेजिस्टर table on Linux platक्रमm */

/* Network Control Reg */
#घोषणा	SR_NCR			0x00
#घोषणा		NCR_RST			(1 << 0)
#घोषणा		NCR_LBK			(3 << 1)
#घोषणा		NCR_FDX			(1 << 3)
#घोषणा		NCR_WAKEEN		(1 << 6)
/* Network Status Reg */
#घोषणा	SR_NSR			0x01
#घोषणा		NSR_RXRDY		(1 << 0)
#घोषणा		NSR_RXOV		(1 << 1)
#घोषणा		NSR_TX1END		(1 << 2)
#घोषणा		NSR_TX2END		(1 << 3)
#घोषणा		NSR_TXFULL		(1 << 4)
#घोषणा		NSR_WAKEST		(1 << 5)
#घोषणा		NSR_LINKST		(1 << 6)
#घोषणा		NSR_SPEED		(1 << 7)
/* Tx Control Reg */
#घोषणा	SR_TCR			0x02
#घोषणा		TCR_CRC_DIS		(1 << 1)
#घोषणा		TCR_PAD_DIS		(1 << 2)
#घोषणा		TCR_LC_CARE		(1 << 3)
#घोषणा		TCR_CRS_CARE	(1 << 4)
#घोषणा		TCR_EXCECM		(1 << 5)
#घोषणा		TCR_LF_EN		(1 << 6)
/* Tx Status Reg क्रम Packet Index 1 */
#घोषणा	SR_TSR1		0x03
#घोषणा		TSR1_EC			(1 << 2)
#घोषणा		TSR1_COL		(1 << 3)
#घोषणा		TSR1_LC			(1 << 4)
#घोषणा		TSR1_NC			(1 << 5)
#घोषणा		TSR1_LOC		(1 << 6)
#घोषणा		TSR1_TLF		(1 << 7)
/* Tx Status Reg क्रम Packet Index 2 */
#घोषणा	SR_TSR2		0x04
#घोषणा		TSR2_EC			(1 << 2)
#घोषणा		TSR2_COL		(1 << 3)
#घोषणा		TSR2_LC			(1 << 4)
#घोषणा		TSR2_NC			(1 << 5)
#घोषणा		TSR2_LOC		(1 << 6)
#घोषणा		TSR2_TLF		(1 << 7)
/* Rx Control Reg*/
#घोषणा	SR_RCR			0x05
#घोषणा		RCR_RXEN		(1 << 0)
#घोषणा		RCR_PRMSC		(1 << 1)
#घोषणा		RCR_RUNT		(1 << 2)
#घोषणा		RCR_ALL			(1 << 3)
#घोषणा		RCR_DIS_CRC		(1 << 4)
#घोषणा		RCR_DIS_LONG	(1 << 5)
/* Rx Status Reg */
#घोषणा	SR_RSR			0x06
#घोषणा		RSR_AE			(1 << 2)
#घोषणा		RSR_MF			(1 << 6)
#घोषणा		RSR_RF			(1 << 7)
/* Rx Overflow Counter Reg */
#घोषणा	SR_ROCR		0x07
#घोषणा		ROCR_ROC		(0x7F << 0)
#घोषणा		ROCR_RXFU		(1 << 7)
/* Back Pressure Threshold Reg */
#घोषणा	SR_BPTR		0x08
#घोषणा		BPTR_JPT		(0x0F << 0)
#घोषणा		BPTR_BPHW		(0x0F << 4)
/* Flow Control Threshold Reg */
#घोषणा	SR_FCTR		0x09
#घोषणा		FCTR_LWOT		(0x0F << 0)
#घोषणा		FCTR_HWOT		(0x0F << 4)
/* rx/tx Flow Control Reg */
#घोषणा	SR_FCR			0x0A
#घोषणा		FCR_FLCE		(1 << 0)
#घोषणा		FCR_BKPA		(1 << 4)
#घोषणा		FCR_TXPEN		(1 << 5)
#घोषणा		FCR_TXPF		(1 << 6)
#घोषणा		FCR_TXP0		(1 << 7)
/* Eeprom & Phy Control Reg */
#घोषणा	SR_EPCR		0x0B
#घोषणा		EPCR_ERRE		(1 << 0)
#घोषणा		EPCR_ERPRW		(1 << 1)
#घोषणा		EPCR_ERPRR		(1 << 2)
#घोषणा		EPCR_EPOS		(1 << 3)
#घोषणा		EPCR_WEP		(1 << 4)
/* Eeprom & Phy Address Reg */
#घोषणा	SR_EPAR		0x0C
#घोषणा		EPAR_EROA		(0x3F << 0)
#घोषणा		EPAR_PHY_ADR_MASK	(0x03 << 6)
#घोषणा		EPAR_PHY_ADR		(0x01 << 6)
/* Eeprom &	Phy Data Reg */
#घोषणा	SR_EPDR		0x0D	/* 0x0D ~ 0x0E क्रम Data Reg Low & High */
/* Wakeup Control Reg */
#घोषणा	SR_WCR			0x0F
#घोषणा		WCR_MAGICST		(1 << 0)
#घोषणा		WCR_LINKST		(1 << 2)
#घोषणा		WCR_MAGICEN		(1 << 3)
#घोषणा		WCR_LINKEN		(1 << 5)
/* Physical Address Reg */
#घोषणा	SR_PAR			0x10	/* 0x10 ~ 0x15 6 bytes क्रम PAR */
/* Multicast Address Reg */
#घोषणा	SR_MAR			0x16	/* 0x16 ~ 0x1D 8 bytes क्रम MAR */
/* 0x1e unused */
/* Phy Reset Reg */
#घोषणा	SR_PRR			0x1F
#घोषणा		PRR_PHY_RST		(1 << 0)
/* Tx sdram Write Poपूर्णांकer Address Low */
#घोषणा	SR_TWPAL		0x20
/* Tx sdram Write Poपूर्णांकer Address High */
#घोषणा	SR_TWPAH		0x21
/* Tx sdram Read Poपूर्णांकer Address Low */
#घोषणा	SR_TRPAL		0x22
/* Tx sdram Read Poपूर्णांकer Address High */
#घोषणा	SR_TRPAH		0x23
/* Rx sdram Write Poपूर्णांकer Address Low */
#घोषणा	SR_RWPAL		0x24
/* Rx sdram Write Poपूर्णांकer Address High */
#घोषणा	SR_RWPAH		0x25
/* Rx sdram Read Poपूर्णांकer Address Low */
#घोषणा	SR_RRPAL		0x26
/* Rx sdram Read Poपूर्णांकer Address High */
#घोषणा	SR_RRPAH		0x27
/* Venकरोr ID रेजिस्टर */
#घोषणा	SR_VID			0x28	/* 0x28 ~ 0x29 2 bytes क्रम VID */
/* Product ID रेजिस्टर */
#घोषणा	SR_PID			0x2A	/* 0x2A ~ 0x2B 2 bytes क्रम PID */
/* CHIP Revision रेजिस्टर */
#घोषणा	SR_CHIPR		0x2C
/* 0x2D --> 0xEF unused */
/* USB Device Address */
#घोषणा	SR_USBDA		0xF0
#घोषणा		USBDA_USBFA		(0x7F << 0)
/* RX packet Counter Reg */
#घोषणा	SR_RXC			0xF1
/* Tx packet Counter & USB Status Reg */
#घोषणा	SR_TXC_USBS		0xF2
#घोषणा		TXC_USBS_TXC0		(1 << 0)
#घोषणा		TXC_USBS_TXC1		(1 << 1)
#घोषणा		TXC_USBS_TXC2		(1 << 2)
#घोषणा		TXC_USBS_EP1RDY		(1 << 5)
#घोषणा		TXC_USBS_SUSFLAG	(1 << 6)
#घोषणा		TXC_USBS_RXFAULT	(1 << 7)
/* USB Control रेजिस्टर */
#घोषणा	SR_USBC			0xF4
#घोषणा		USBC_EP3NAK		(1 << 4)
#घोषणा		USBC_EP3ACK		(1 << 5)

/* Register access commands and flags */
#घोषणा	SR_RD_REGS		0x00
#घोषणा	SR_WR_REGS		0x01
#घोषणा	SR_WR_REG		0x03
#घोषणा	SR_REQ_RD_REG	(USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE)
#घोषणा	SR_REQ_WR_REG	(USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE)

/* parameters */
#घोषणा	SR_SHARE_TIMEOUT	1000
#घोषणा	SR_EEPROM_LEN		256
#घोषणा	SR_MCAST_SIZE		8
#घोषणा	SR_MCAST_ADDR_FLAG	0x80
#घोषणा	SR_MCAST_MAX		64
#घोषणा	SR_TX_OVERHEAD		2	/* 2bytes header */
#घोषणा	SR_RX_OVERHEAD		7	/* 3bytes header + 4crc tail */

#पूर्ण_अगर	/* _SR9700_H */
