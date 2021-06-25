<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8712_SPEC_H__
#घोषणा __RTL8712_SPEC_H__

#घोषणा RTL8712_IOBASE_TXPKT		0x10200000	/*IOBASE_TXPKT*/
#घोषणा RTL8712_IOBASE_RXPKT		0x10210000	/*IOBASE_RXPKT*/
#घोषणा RTL8712_IOBASE_RXCMD		0x10220000	/*IOBASE_RXCMD*/
#घोषणा RTL8712_IOBASE_TXSTATUS		0x10230000	/*IOBASE_TXSTATUS*/
#घोषणा RTL8712_IOBASE_RXSTATUS		0x10240000	/*IOBASE_RXSTATUS*/
#घोषणा RTL8712_IOBASE_IOREG		0x10250000	/*IOBASE_IOREG ADDR*/
#घोषणा RTL8712_IOBASE_SCHEDULER	0x10260000	/*IOBASE_SCHEDULE*/

#घोषणा RTL8712_IOBASE_TRXDMA		0x10270000	/*IOBASE_TRXDMA*/
#घोषणा RTL8712_IOBASE_TXLLT		0x10280000	/*IOBASE_TXLLT*/
#घोषणा RTL8712_IOBASE_WMAC		0x10290000	/*IOBASE_WMAC*/
#घोषणा RTL8712_IOBASE_FW2HW		0x102A0000	/*IOBASE_FW2HW*/
#घोषणा RTL8712_IOBASE_ACCESS_PHYREG	0x102B0000	/*IOBASE_ACCESS_PHYREG*/

#घोषणा RTL8712_IOBASE_FF	0x10300000 /*IOBASE_FIFO 0x1031000~0x103AFFFF*/


/*IOREG Offset क्रम 8712*/
#घोषणा RTL8712_SYSCFG_		RTL8712_IOBASE_IOREG
#घोषणा RTL8712_CMDCTRL_	(RTL8712_IOBASE_IOREG + 0x40)
#घोषणा RTL8712_MACIDSETTING_	(RTL8712_IOBASE_IOREG + 0x50)
#घोषणा RTL8712_TIMECTRL_	(RTL8712_IOBASE_IOREG + 0x80)
#घोषणा RTL8712_FIFOCTRL_	(RTL8712_IOBASE_IOREG + 0xA0)
#घोषणा RTL8712_RATECTRL_	(RTL8712_IOBASE_IOREG + 0x160)
#घोषणा RTL8712_EDCASETTING_	(RTL8712_IOBASE_IOREG + 0x1D0)
#घोषणा RTL8712_WMAC_		(RTL8712_IOBASE_IOREG + 0x200)
#घोषणा RTL8712_SECURITY_	(RTL8712_IOBASE_IOREG + 0x240)
#घोषणा RTL8712_POWERSAVE_	(RTL8712_IOBASE_IOREG + 0x260)
#घोषणा RTL8712_GP_		(RTL8712_IOBASE_IOREG + 0x2E0)
#घोषणा RTL8712_INTERRUPT_	(RTL8712_IOBASE_IOREG + 0x300)
#घोषणा RTL8712_DEBUGCTRL_	(RTL8712_IOBASE_IOREG + 0x310)
#घोषणा RTL8712_OFFLOAD_	(RTL8712_IOBASE_IOREG + 0x2D0)


/*FIFO क्रम 8712*/
#घोषणा RTL8712_DMA_BCNQ	(RTL8712_IOBASE_FF + 0x10000)
#घोषणा RTL8712_DMA_MGTQ	(RTL8712_IOBASE_FF + 0x20000)
#घोषणा RTL8712_DMA_BMCQ	(RTL8712_IOBASE_FF + 0x30000)
#घोषणा RTL8712_DMA_VOQ		(RTL8712_IOBASE_FF + 0x40000)
#घोषणा RTL8712_DMA_VIQ		(RTL8712_IOBASE_FF + 0x50000)
#घोषणा RTL8712_DMA_BEQ		(RTL8712_IOBASE_FF + 0x60000)
#घोषणा RTL8712_DMA_BKQ		(RTL8712_IOBASE_FF + 0x70000)
#घोषणा RTL8712_DMA_RX0FF	(RTL8712_IOBASE_FF + 0x80000)
#घोषणा RTL8712_DMA_H2CCMD	(RTL8712_IOBASE_FF + 0x90000)
#घोषणा RTL8712_DMA_C2HCMD	(RTL8712_IOBASE_FF + 0xA0000)


/*------------------------------*/

/*BIT 16 15*/
#घोषणा	DID_SDIO_LOCAL			0	/* 0 0*/
#घोषणा	DID_WLAN_IOREG			1	/* 0 1*/
#घोषणा	DID_WLAN_FIFO			3	/* 1 1*/
#घोषणा   DID_UNDEFINE				(-1)

#घोषणा CMD_ADDR_MAPPING_SHIFT		2	/*SDIO CMD ADDR MAPPING,
						 *shअगरt 2 bit क्रम match
						 * offset[14:2]
						 */

/*Offset क्रम SDIO LOCAL*/
#घोषणा	OFFSET_SDIO_LOCAL				0x0FFF

/*Offset क्रम WLAN IOREG*/
#घोषणा OFFSET_WLAN_IOREG				0x0FFF

/*Offset क्रम WLAN FIFO*/
#घोषणा	OFFSET_TX_BCNQ				0x0300
#घोषणा	OFFSET_TX_HIQ					0x0310
#घोषणा	OFFSET_TX_CMDQ				0x0320
#घोषणा	OFFSET_TX_MGTQ				0x0330
#घोषणा	OFFSET_TX_HCCAQ				0x0340
#घोषणा	OFFSET_TX_VOQ					0x0350
#घोषणा	OFFSET_TX_VIQ					0x0360
#घोषणा	OFFSET_TX_BEQ					0x0370
#घोषणा	OFFSET_TX_BKQ					0x0380
#घोषणा	OFFSET_RX_RX0FFQ				0x0390
#घोषणा	OFFSET_RX_C2HFFQ				0x03A0

#घोषणा	BK_QID_01	1
#घोषणा	BK_QID_02	2
#घोषणा	BE_QID_01	0
#घोषणा	BE_QID_02	3
#घोषणा	VI_QID_01	4
#घोषणा	VI_QID_02	5
#घोषणा	VO_QID_01	6
#घोषणा	VO_QID_02	7
#घोषणा	HCCA_QID_01	8
#घोषणा	HCCA_QID_02	9
#घोषणा	HCCA_QID_03	10
#घोषणा	HCCA_QID_04	11
#घोषणा	HCCA_QID_05	12
#घोषणा	HCCA_QID_06	13
#घोषणा	HCCA_QID_07	14
#घोषणा	HCCA_QID_08	15
#घोषणा	HI_QID		17
#घोषणा	CMD_QID	19
#घोषणा	MGT_QID	18
#घोषणा	BCN_QID	16

#समावेश "rtl8712_regdef.h"

#समावेश "rtl8712_bitdef.h"

#समावेश "basic_types.h"

#पूर्ण_अगर /* __RTL8712_SPEC_H__ */

