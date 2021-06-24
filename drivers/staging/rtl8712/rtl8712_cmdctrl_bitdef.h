<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8712_CMDCTRL_BITDEF_H__
#घोषणा __RTL8712_CMDCTRL_BITDEF_H__

/*
 * 2. Command Control Registers	 (Offset: 0x0040 - 0x004F)
 */
/*--------------------------------------------------------------------------*/
/*       8192S (CMD) command रेजिस्टर bits	(Offset 0x40, 16 bits)*/
/*--------------------------------------------------------------------------*/
#घोषणा		_APSDOFF_STATUS		BIT(15)
#घोषणा		_APSDOFF		BIT(14)
#घोषणा		_BBRSTn			BIT(13)  /*Enable OFDM/CCK*/
#घोषणा		_BB_GLB_RSTn		BIT(12)   /*Enable BB*/
#घोषणा		_SCHEDULE_EN		BIT(10)  /*Enable MAC scheduler*/
#घोषणा		_MACRXEN		BIT(9)
#घोषणा		_MACTXEN		BIT(8)
#घोषणा		_DDMA_EN		BIT(7)  /*FW off load function enable*/
#घोषणा		_FW2HW_EN		BIT(6)  /*MAC every module reset */
#घोषणा		_RXDMA_EN		BIT(5)
#घोषणा		_TXDMA_EN		BIT(4)
#घोषणा		_HCI_RXDMA_EN		BIT(3)
#घोषणा		_HCI_TXDMA_EN		BIT(2)

/*TXPAUSE*/
#घोषणा	_STOPHCCA			BIT(6)
#घोषणा	_STOPHIGH			BIT(5)
#घोषणा	_STOPMGT			BIT(4)
#घोषणा	_STOPVO				BIT(3)
#घोषणा	_STOPVI				BIT(2)
#घोषणा	_STOPBE				BIT(1)
#घोषणा	_STOPBK				BIT(0)

/*TCR*/
#घोषणा	_DISCW				BIT(20)
#घोषणा	_ICV				BIT(19)
#घोषणा	_CFEND_FMT			BIT(17)
#घोषणा	_CRC				BIT(16)
#घोषणा	_FWRDY				BIT(7)
#घोषणा _BASECHG			BIT(6)
#घोषणा	_IMEM_RDY			BIT(5)
#घोषणा _DMEM_CODE_DONE			BIT(4)
#घोषणा _EMEM_CHK_RPT			BIT(3)
#घोषणा _EMEM_CODE_DONE			BIT(2)
#घोषणा _IMEM_CHK_RPT			BIT(1)
#घोषणा _IMEM_CODE_DONE			BIT(0)

#घोषणा	_TXDMA_INIT_VALUE	(_IMEM_CHK_RPT | _EMEM_CHK_RPT)

/*RCR*/
#घोषणा	_ENMBID				BIT(27)
#घोषणा	_APP_PHYST_RXFF			BIT(25)
#घोषणा	_APP_PHYST_STAFF		BIT(24)
#घोषणा	_CBSSID				BIT(23)
#घोषणा	_APWRMGT			BIT(22)
#घोषणा	_ADD3				BIT(21)
#घोषणा	_AMF				BIT(20)
#घोषणा	_ACF				BIT(19)
#घोषणा	_ADF				BIT(18)
#घोषणा	_APP_MIC			BIT(17)
#घोषणा	_APP_ICV			BIT(16)
#घोषणा	_RXFTH_MSK			0x0000E000
#घोषणा	_RXFTH_SHT			13
#घोषणा	_AICV				BIT(12)
#घोषणा	_RXPKTLMT_MSK			0x00000FC0
#घोषणा	_RXPKTLMT_SHT			6
#घोषणा	_ACRC32				BIT(5)
#घोषणा	_AB				BIT(3)
#घोषणा	_AM				BIT(2)
#घोषणा	_APM				BIT(1)
#घोषणा	_AAP				BIT(0)

/*MSR*/
#घोषणा	_NETTYPE_MSK			0x03
#घोषणा	_NETTYPE_SHT			0

/*BT*/
#घोषणा _BTMODE_MSK			0x06
#घोषणा _BTMODE_SHT			1
#घोषणा _ENBT				BIT(0)

/*MBIDCTRL*/
#घोषणा	_ENMBID_MODE			BIT(15)
#घोषणा	_BCNNO_MSK			0x7000
#घोषणा	_BCNNO_SHT			12
#घोषणा	_BCNSPACE_MSK			0x0FFF
#घोषणा	_BCNSPACE_SHT			0


#पूर्ण_अगर /* __RTL8712_CMDCTRL_BITDEF_H__*/

