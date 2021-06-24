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
#अगर_अघोषित __RTL8712_EDCASETTING_BITDEF_H__
#घोषणा __RTL8712_EDCASETTING_BITDEF_H__

/*EDCAPARAM*/
#घोषणा	_TXOPLIMIT_MSK		0xFFFF0000
#घोषणा	_TXOPLIMIT_SHT		16
#घोषणा	_ECWIN_MSK		0x0000FF00
#घोषणा	_ECWIN_SHT		8
#घोषणा	_AIFS_MSK		0x000000FF
#घोषणा	_AIFS_SHT		0

/*BCNTCFG*/
#घोषणा	_BCNECW_MSK		0xFF00
#घोषणा	_BCNECW_SHT		8
#घोषणा	_BCNIFS_MSK		0x00FF
#घोषणा	_BCNIFS_SHT		0

/*CWRR*/
#घोषणा	_CWRR_MSK		0x03FF

/*ACMAVG*/
#घोषणा	_AVG_TIME_UP		BIT(3)
#घोषणा	_AVGPERIOD_MSK		0x03

/*ACMHWCTRL*/
#घोषणा	_VOQ_ACM_STATUS		BIT(6)
#घोषणा	_VIQ_ACM_STATUS		BIT(5)
#घोषणा	_BEQ_ACM_STATUS		BIT(4)
#घोषणा	_VOQ_ACM_EN		BIT(3)
#घोषणा	_VIQ_ACM_EN		BIT(2)
#घोषणा	_BEQ_ACM_EN		BIT(1)
#घोषणा	_ACMHWEN		BIT(0)

/*VO_ADMTIME*/
#घोषणा	_VO_ACM_RUT		BIT(18)
#घोषणा	_VO_ADMTIME_MSK		0x0003FFF

/*VI_ADMTIME*/
#घोषणा	_VI_ACM_RUT		BIT(18)
#घोषणा	_VI_ADMTIME_MSK		0x0003FFF

/*BE_ADMTIME*/
#घोषणा	_BE_ACM_RUT		BIT(18)
#घोषणा	_BE_ADMTIME_MSK		0x0003FFF

/*Retry limit reg*/
#घोषणा	_SRL_MSK		0xFF00
#घोषणा	_SRL_SHT		8
#घोषणा	_LRL_MSK		0x00FF
#घोषणा	_LRL_SHT		0

#पूर्ण_अगर /* __RTL8712_EDCASETTING_BITDEF_H__*/
