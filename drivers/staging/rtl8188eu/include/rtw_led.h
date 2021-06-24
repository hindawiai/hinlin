<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_LED_H_
#घोषणा __RTW_LED_H_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>

#घोषणा LED_BLINK_NO_LINK_INTERVAL_ALPHA	1000
#घोषणा LED_BLINK_LINK_INTERVAL_ALPHA		500	/* 500 */
#घोषणा LED_BLINK_SCAN_INTERVAL_ALPHA		180	/* 150 */
#घोषणा LED_BLINK_FASTER_INTERVAL_ALPHA		50
#घोषणा LED_BLINK_WPS_SUCCESS_INTERVAL_ALPHA	5000

क्रमागत LED_CTL_MODE अणु
	LED_CTL_POWER_ON,
	LED_CTL_LINK,
	LED_CTL_NO_LINK,
	LED_CTL_TX,
	LED_CTL_RX,
	LED_CTL_SITE_SURVEY,
	LED_CTL_POWER_OFF,
	LED_CTL_START_TO_LINK,
	LED_CTL_START_WPS,
	LED_CTL_STOP_WPS,
	LED_CTL_START_WPS_BOTTON,
	LED_CTL_STOP_WPS_FAIL
पूर्ण;

क्रमागत LED_STATE_871x अणु
	LED_UNKNOWN,
	RTW_LED_ON,
	RTW_LED_OFF,
	LED_BLINK_NORMAL,
	LED_BLINK_SLOWLY,
	LED_BLINK_POWER_ON,
	LED_BLINK_SCAN,
	LED_BLINK_TXRX,
	LED_BLINK_WPS,
	LED_BLINK_WPS_STOP
पूर्ण;

काष्ठा LED_871x अणु
	काष्ठा adapter *padapter;

	क्रमागत LED_STATE_871x	CurrLedState; /*  Current LED state. */
	क्रमागत LED_STATE_871x	BlinkingLedState; /*  Next state क्रम blinking,
						   * either RTW_LED_ON or RTW_LED_OFF are.
						   */

	u8 bLedOn; /*  true अगर LED is ON, false अगर LED is OFF. */

	u8 bLedBlinkInProgress; /*  true अगर it is blinking, false o.w.. */

	u8 bLedWPSBlinkInProgress;

	u32 BlinkTimes; /*  Number of बार to toggle led state क्रम blinking. */

	काष्ठा समयr_list BlinkTimer; /*  Timer object क्रम led blinking. */

	/*  ALPHA, added by chiyoko, 20090106 */
	u8 bLedNoLinkBlinkInProgress;
	u8 bLedLinkBlinkInProgress;
	u8 bLedScanBlinkInProgress;
	काष्ठा work_काष्ठा BlinkWorkItem; /* Workitem used by BlinkTimer to
					   * manipulate H/W to blink LED.
					   */
पूर्ण;

#घोषणा IS_LED_WPS_BLINKING(_LED_871x)					\
	(((काष्ठा LED_871x *)_LED_871x)->CurrLedState == LED_BLINK_WPS || \
	((काष्ठा LED_871x *)_LED_871x)->CurrLedState == LED_BLINK_WPS_STOP || \
	((काष्ठा LED_871x *)_LED_871x)->bLedWPSBlinkInProgress)

व्योम led_control_8188eu(काष्ठा adapter *padapter, क्रमागत LED_CTL_MODE LedAction);

काष्ठा led_priv अणु
	काष्ठा LED_871x sw_led;
पूर्ण;

व्योम BlinkWorkItemCallback(काष्ठा work_काष्ठा *work);

व्योम ResetLedStatus(काष्ठा LED_871x *pLed);

व्योम InitLed871x(काष्ठा adapter *padapter, काष्ठा LED_871x *pLed);

व्योम DeInitLed871x(काष्ठा LED_871x *pLed);

/* hal... */
व्योम blink_handler(काष्ठा LED_871x *pLed);
व्योम sw_led_on(काष्ठा adapter *padapter, काष्ठा LED_871x *pLed);
व्योम sw_led_off(काष्ठा adapter *padapter, काष्ठा LED_871x *pLed);

#पूर्ण_अगर /* __RTW_LED_H_ */
