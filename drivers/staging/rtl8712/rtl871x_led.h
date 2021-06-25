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
#अगर_अघोषित __RTL8712_LED_H
#घोषणा __RTL8712_LED_H

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

/*===========================================================================
 * LED customization.
 *===========================================================================
 */
क्रमागत LED_CTL_MODE अणु
	LED_CTL_POWER_ON = 1,
	LED_CTL_LINK = 2,
	LED_CTL_NO_LINK = 3,
	LED_CTL_TX = 4,
	LED_CTL_RX = 5,
	LED_CTL_SITE_SURVEY = 6,
	LED_CTL_POWER_OFF = 7,
	LED_CTL_START_TO_LINK = 8,
	LED_CTL_START_WPS = 9,
	LED_CTL_STOP_WPS = 10,
	LED_CTL_START_WPS_BOTTON = 11,
	LED_CTL_STOP_WPS_FAIL = 12,
	LED_CTL_STOP_WPS_FAIL_OVERLAP = 13,
पूर्ण;

#घोषणा IS_LED_WPS_BLINKING(_LED_871x)	\
	(((काष्ठा LED_871x *)_LED_871x)->CurrLedState == LED_BLINK_WPS \
	|| ((काष्ठा LED_871x *)_LED_871x)->CurrLedState == LED_BLINK_WPS_STOP \
	|| ((काष्ठा LED_871x *)_LED_871x)->bLedWPSBlinkInProgress)

#घोषणा IS_LED_BLINKING(_LED_871x)	\
		(((काष्ठा LED_871x *)_LED_871x)->bLedWPSBlinkInProgress \
		|| ((काष्ठा LED_871x *)_LED_871x)->bLedScanBlinkInProgress)

क्रमागत LED_PIN_871x अणु
	LED_PIN_GPIO0,
	LED_PIN_LED0,
	LED_PIN_LED1
पूर्ण;

/*===========================================================================
 * LED customization.
 *===========================================================================
 */
क्रमागत LED_STRATEGY_871x अणु
	SW_LED_MODE0, /* SW control 1 LED via GPIO0. It is शेष option. */
	SW_LED_MODE1, /* 2 LEDs, through LED0 and LED1. For ALPHA. */
	SW_LED_MODE2, /* SW control 1 LED via GPIO0,
		       * custom क्रम AzWave 8187 minicard.
		       */
	SW_LED_MODE3, /* SW control 1 LED via GPIO0,
		       * customized क्रम Sercomm Prपूर्णांकer Server हाल.
		       */
	SW_LED_MODE4, /*क्रम Edimax / Belkin*/
	SW_LED_MODE5, /*क्रम Sercomm / Belkin*/
	SW_LED_MODE6, /*क्रम WNC / Corega*/
	HW_LED, /* HW control 2 LEDs, LED0 and LED1 (there are 4 dअगरferent
		 * control modes, see MAC.CONFIG1 क्रम details.)
		 */
पूर्ण;

काष्ठा LED_871x अणु
	काष्ठा _adapter		*padapter;
	क्रमागत LED_PIN_871x	LedPin;	/* Implementation क्रम this SW led. */
	u32			CurrLedState; /* Current LED state. */
	u8			bLedOn; /* true अगर LED is ON */
	u8			bSWLedCtrl;
	u8			bLedBlinkInProgress; /*true अगर blinking */
	u8			bLedNoLinkBlinkInProgress;
	u8			bLedLinkBlinkInProgress;
	u8			bLedStartToLinkBlinkInProgress;
	u8			bLedScanBlinkInProgress;
	u8			bLedWPSBlinkInProgress;
	u32			BlinkTimes; /* No. बार to toggle क्रम blink.*/
	u32			BlinkingLedState; /* Next state क्रम blinking,
						   * either LED_ON or OFF.
						   */

	काष्ठा समयr_list	BlinkTimer; /* Timer object क्रम led blinking.*/
	काष्ठा work_काष्ठा	BlinkWorkItem; /* Workitem used by BlinkTimer */
पूर्ण;

काष्ठा led_priv अणु
	/* add क्रम led control */
	काष्ठा LED_871x		SwLed0;
	काष्ठा LED_871x		SwLed1;
	क्रमागत LED_STRATEGY_871x	LedStrategy;
	u8			bRegUseLed;
	व्योम (*LedControlHandler)(काष्ठा _adapter *padapter,
				  क्रमागत LED_CTL_MODE LedAction);
	/* add क्रम led control */
पूर्ण;

/*===========================================================================
 * Interface to manipulate LED objects.
 *===========================================================================
 */
व्योम r8712_InitSwLeds(काष्ठा _adapter *padapter);
व्योम r8712_DeInitSwLeds(काष्ठा _adapter *padapter);
व्योम LedControl871x(काष्ठा _adapter *padapter, क्रमागत LED_CTL_MODE LedAction);

#पूर्ण_अगर

