<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8712_POWERSAVE_BITDEF_H__
#घोषणा __RTL8712_POWERSAVE_BITDEF_H__

/*WOWCTRL*/
#घोषणा	_UWF			BIT(3)
#घोषणा	_MAGIC			BIT(2)
#घोषणा	_WOW_EN			BIT(1)
#घोषणा	_PMEN			BIT(0)

/*PSSTATUS*/
#घोषणा	_PSSTATUS_SEL_MSK		0x0F

/*PSSWITCH*/
#घोषणा	_PSSWITCH_ACT			BIT(7)
#घोषणा	_PSSWITCH_SEL_MSK		0x0F
#घोषणा	_PSSWITCH_SEL_SHT		0

/*LPNAV_CTRL*/
#घोषणा	_LPNAV_EN			BIT(31)
#घोषणा	_LPNAV_EARLY_MSK		0x7FFF0000
#घोषणा	_LPNAV_EARLY_SHT		16
#घोषणा	_LPNAV_TH_MSK			0x0000FFFF
#घोषणा	_LPNAV_TH_SHT			0

/*RPWM*/
/*CPWM*/
#घोषणा	_TOGGLING			BIT(7)
#घोषणा	_WWLAN				BIT(3)
#घोषणा	_RPS_ST				BIT(2)
#घोषणा	_WLAN_TRX			BIT(1)
#घोषणा	_SYS_CLK			BIT(0)

#पूर्ण_अगर /* __RTL8712_POWERSAVE_BITDEF_H__*/
