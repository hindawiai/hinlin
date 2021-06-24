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
#अगर_अघोषित __RTL8712_GP_BITDEF_H__
#घोषणा __RTL8712_GP_BITDEF_H__

/*GPIO_CTRL*/
#घोषणा	_GPIO_MOD_MSK			0xFF000000
#घोषणा	_GPIO_MOD_SHT			24
#घोषणा	_GPIO_IO_SEL_MSK		0x00FF0000
#घोषणा	_GPIO_IO_SEL_SHT		16
#घोषणा	_GPIO_OUT_MSK			0x0000FF00
#घोषणा	_GPIO_OUT_SHT			8
#घोषणा	_GPIO_IN_MSK			0x000000FF
#घोषणा	_GPIO_IN_SHT			0

/*SYS_PINMUX_CFG*/
#घोषणा	_GPIOSEL_MSK			0x0003
#घोषणा	_GPIOSEL_SHT			0

/*LED_CFG*/
#घोषणा _LED1SV				BIT(7)
#घोषणा _LED1CM_MSK			0x0070
#घोषणा _LED1CM_SHT			4
#घोषणा _LED0SV				BIT(3)
#घोषणा _LED0CM_MSK			0x0007
#घोषणा _LED0CM_SHT			0

/*PHY_REG*/
#घोषणा _HST_RDRDY_SHT			0
#घोषणा _HST_RDRDY_MSK			0xFF
#घोषणा _HST_RDRDY			BIT(_HST_RDRDY_SHT)
#घोषणा _CPU_WTBUSY_SHT			1
#घोषणा _CPU_WTBUSY_MSK			0xFF
#घोषणा _CPU_WTBUSY			BIT(_CPU_WTBUSY_SHT)

/* 11. General Purpose Registers   (Offset: 0x02E0 - 0x02FF)*/

/*       8192S GPIO Config Setting (offset 0x2F1, 1 byte)*/

/*----------------------------------------------------------------------------*/

#घोषणा		GPIOMUX_EN	BIT(3)	/* When this bit is set to "1",
					 * GPIO PINs will चयन to MAC
					 * GPIO Function
					 */
#घोषणा		GPIOSEL_GPIO	0	/* UART or JTAG or pure GPIO*/
#घोषणा		GPIOSEL_PHYDBG	1	/* PHYDBG*/
#घोषणा		GPIOSEL_BT	2	/* BT_coex*/
#घोषणा		GPIOSEL_WLANDBG	3	/* WLANDBG*/
#घोषणा		GPIOSEL_GPIO_MASK	(~(BIT(0) | BIT(1)))
/* HW Radio OFF चयन (GPIO BIT) */
#घोषणा		HAL_8192S_HW_GPIO_OFF_BIT	BIT(3)
#घोषणा		HAL_8192S_HW_GPIO_OFF_MASK	0xF7
#घोषणा		HAL_8192S_HW_GPIO_WPS_BIT	BIT(4)

#पूर्ण_अगर	/*__RTL8712_GP_BITDEF_H__*/

