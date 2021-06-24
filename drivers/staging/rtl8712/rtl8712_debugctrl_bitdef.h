<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8712_DEBUGCTRL_BITDEF_H__
#घोषणा __RTL8712_DEBUGCTRL_BITDEF_H__

/*BIST*/
#घोषणा	_BIST_RST			BIT(0)

/*LMS*/
#घोषणा	_LMS_MSK			0x03

/*WDG_CTRL*/
#घोषणा	_OVSEL_MSK			0x0600
#घोषणा	_OVSEL_SHT			9
#घोषणा	_WDGCLR				BIT(8)
#घोषणा	_WDGEN_MSK			0x00FF
#घोषणा	_WDGEN_SHT			0

/*INTM*/
#घोषणा	_TXTIMER_MSK		0xF000
#घोषणा	_TXTIMER_SHT		12
#घोषणा	_TXNUM_MSK			0x0F00
#घोषणा	_TXNUM_SHT			8
#घोषणा	_RXTIMER_MSK		0x00F0
#घोषणा	_RXTIMER_SHT		4
#घोषणा	_RXNUM_MSK			0x000F
#घोषणा	_RXNUM_SHT			0

/*FDLOCKTURN0*/
/*FDLOCKTURN1*/
#घोषणा	_TURN1				BIT(0)

/*FDLOCKFLAG0*/
/*FDLOCKFLAG1*/
#घोषणा	_LOCKFLAG1_MSK		0x03

#पूर्ण_अगर /* __RTL8712_DEBUGCTRL_BITDEF_H__ */
