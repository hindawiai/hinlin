<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <rtl8188e_hal.h>
#समावेश <usb_ops_linux.h>

व्योम sw_led_on(काष्ठा adapter *padapter, काष्ठा LED_871x *pLed)
अणु
	u8 led_cfg;

	अगर (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		वापस;
	led_cfg = usb_पढ़ो8(padapter, REG_LEDCFG2);
	usb_ग_लिखो8(padapter, REG_LEDCFG2, (led_cfg & 0xf0) | BIT(5) | BIT(6));
	pLed->bLedOn = true;
पूर्ण

व्योम sw_led_off(काष्ठा adapter *padapter, काष्ठा LED_871x *pLed)
अणु
	u8 led_cfg;

	अगर (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		जाओ निकास;

	led_cfg = usb_पढ़ो8(padapter, REG_LEDCFG2);/* 0x4E */

	/*  Open-drain arrangement क्रम controlling the LED) */
	led_cfg &= 0x90; /*  Set to software control. */
	usb_ग_लिखो8(padapter, REG_LEDCFG2, (led_cfg | BIT(3)));
	led_cfg = usb_पढ़ो8(padapter, REG_MAC_PINMUX_CFG);
	led_cfg &= 0xFE;
	usb_ग_लिखो8(padapter, REG_MAC_PINMUX_CFG, led_cfg);
निकास:
	pLed->bLedOn = false;
पूर्ण

व्योम rtw_hal_sw_led_init(काष्ठा adapter *padapter)
अणु
	काष्ठा led_priv *pledpriv = &padapter->ledpriv;

	InitLed871x(padapter, &pledpriv->sw_led);
पूर्ण

व्योम rtw_hal_sw_led_deinit(काष्ठा adapter *padapter)
अणु
	काष्ठा led_priv *ledpriv = &padapter->ledpriv;

	DeInitLed871x(&ledpriv->sw_led);
पूर्ण
