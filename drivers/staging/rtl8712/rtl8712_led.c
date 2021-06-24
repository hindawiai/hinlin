<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl8712_led.c
 *
 * Copyright(c) 2007 - 2010  Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#समावेश "drv_types.h"

/*===========================================================================
 *	Constant.
 *===========================================================================

 *
 * Default LED behavior.
 */
#घोषणा LED_BLINK_NORMAL_INTERVAL	100
#घोषणा LED_BLINK_SLOWLY_INTERVAL	200
#घोषणा LED_BLINK_LONG_INTERVAL	400

#घोषणा LED_BLINK_NO_LINK_INTERVAL_ALPHA	1000
#घोषणा LED_BLINK_LINK_INTERVAL_ALPHA		500
#घोषणा LED_BLINK_SCAN_INTERVAL_ALPHA		180
#घोषणा LED_BLINK_FASTER_INTERVAL_ALPHA		50
#घोषणा LED_BLINK_WPS_SUCCESS_INTERVAL_ALPHA	5000

/*===========================================================================
 * LED object.
 *===========================================================================
 */
क्रमागत _LED_STATE_871x अणु
	LED_UNKNOWN = 0,
	LED_STATE_ON = 1,
	LED_STATE_OFF = 2,
	LED_BLINK_NORMAL = 3,
	LED_BLINK_SLOWLY = 4,
	LED_POWER_ON_BLINK = 5,
	LED_SCAN_BLINK = 6, /* LED is blinking during scanning period,
			     * the # of बार to blink is depend on समय
			     * क्रम scanning.
			     */
	LED_NO_LINK_BLINK = 7, /* LED is blinking during no link state. */
	LED_BLINK_StartToBlink = 8,/* Customized क्रम Sercomm Prपूर्णांकer
				    * Server हाल
				    */
	LED_BLINK_WPS = 9,	/* LED is blinkg during WPS communication */
	LED_TXRX_BLINK = 10,
	LED_BLINK_WPS_STOP = 11,	/*क्रम ALPHA */
	LED_BLINK_WPS_STOP_OVERLAP = 12,	/*क्रम BELKIN */
पूर्ण;

/*===========================================================================
 *	Prototype of रक्षित function.
 *===========================================================================
 */
अटल व्योम BlinkTimerCallback(काष्ठा समयr_list *t);

अटल व्योम BlinkWorkItemCallback(काष्ठा work_काष्ठा *work);
/*===========================================================================
 * LED_819xUsb routines.
 *===========================================================================
 *
 *
 *
 *	Description:
 *		Initialize an LED_871x object.
 */
अटल व्योम InitLed871x(काष्ठा _adapter *padapter, काष्ठा LED_871x *pLed,
			क्रमागत LED_PIN_871x	LedPin)
अणु
	pLed->padapter = padapter;
	pLed->LedPin = LedPin;
	pLed->CurrLedState = LED_STATE_OFF;
	pLed->bLedOn = false;
	pLed->bLedBlinkInProgress = false;
	pLed->BlinkTimes = 0;
	pLed->BlinkingLedState = LED_UNKNOWN;
	समयr_setup(&pLed->BlinkTimer, BlinkTimerCallback, 0);
	INIT_WORK(&pLed->BlinkWorkItem, BlinkWorkItemCallback);
पूर्ण

/*
 *	Description:
 *		DeInitialize an LED_871x object.
 */
अटल व्योम DeInitLed871x(काष्ठा LED_871x *pLed)
अणु
	del_समयr_sync(&pLed->BlinkTimer);
	/* We should reset bLedBlinkInProgress अगर we cancel
	 * the LedControlTimer,
	 */
	pLed->bLedBlinkInProgress = false;
पूर्ण

/*
 *	Description:
 *		Turn on LED according to LedPin specअगरied.
 */
अटल व्योम SwLedOn(काष्ठा _adapter *padapter, काष्ठा LED_871x *pLed)
अणु
	u8	LedCfg;

	अगर (padapter->surprise_हटाओd || padapter->driver_stopped)
		वापस;
	LedCfg = r8712_पढ़ो8(padapter, LEDCFG);
	चयन (pLed->LedPin) अणु
	हाल LED_PIN_GPIO0:
		अवरोध;
	हाल LED_PIN_LED0:
		/* SW control led0 on.*/
		r8712_ग_लिखो8(padapter, LEDCFG, LedCfg & 0xf0);
		अवरोध;
	हाल LED_PIN_LED1:
		/* SW control led1 on.*/
		r8712_ग_लिखो8(padapter, LEDCFG, LedCfg & 0x0f);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	pLed->bLedOn = true;
पूर्ण

/*
 *	Description:
 *		Turn off LED according to LedPin specअगरied.
 */
अटल व्योम SwLedOff(काष्ठा _adapter *padapter, काष्ठा LED_871x *pLed)
अणु
	u8	LedCfg;

	अगर (padapter->surprise_हटाओd || padapter->driver_stopped)
		वापस;
	LedCfg = r8712_पढ़ो8(padapter, LEDCFG);
	चयन (pLed->LedPin) अणु
	हाल LED_PIN_GPIO0:
		अवरोध;
	हाल LED_PIN_LED0:
		LedCfg &= 0xf0; /* Set to software control.*/
		r8712_ग_लिखो8(padapter, LEDCFG, (LedCfg | BIT(3)));
		अवरोध;
	हाल LED_PIN_LED1:
		LedCfg &= 0x0f; /* Set to software control.*/
		r8712_ग_लिखो8(padapter, LEDCFG, (LedCfg | BIT(7)));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	pLed->bLedOn = false;
पूर्ण

/*===========================================================================
 * Interface to manipulate LED objects.
 *===========================================================================
 *
 *	Description:
 *		Initialize all LED_871x objects.
 */
व्योम r8712_InitSwLeds(काष्ठा _adapter *padapter)
अणु
	काष्ठा led_priv	*pledpriv = &padapter->ledpriv;

	pledpriv->LedControlHandler = LedControl871x;
	InitLed871x(padapter, &pledpriv->SwLed0, LED_PIN_LED0);
	InitLed871x(padapter, &pledpriv->SwLed1, LED_PIN_LED1);
पूर्ण

/*	Description:
 *		DeInitialize all LED_819xUsb objects.
 */
व्योम r8712_DeInitSwLeds(काष्ठा _adapter *padapter)
अणु
	काष्ठा led_priv	*ledpriv = &padapter->ledpriv;

	DeInitLed871x(&ledpriv->SwLed0);
	DeInitLed871x(&ledpriv->SwLed1);
पूर्ण

/*	Description:
 *		Implementation of LED blinking behavior.
 *		It toggle off LED and schedule corresponding समयr अगर necessary.
 */
अटल व्योम SwLedBlink(काष्ठा LED_871x *pLed)
अणु
	काष्ठा _adapter *padapter = pLed->padapter;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	u8 bStopBlinking = false;

	/* Change LED according to BlinkingLedState specअगरied. */
	अगर (pLed->BlinkingLedState == LED_STATE_ON)
		SwLedOn(padapter, pLed);
	अन्यथा
		SwLedOff(padapter, pLed);
	/* Determine अगर we shall change LED state again. */
	pLed->BlinkTimes--;
	चयन (pLed->CurrLedState) अणु
	हाल LED_BLINK_NORMAL:
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अवरोध;
	हाल LED_BLINK_StartToBlink:
		अगर (check_fwstate(pmlmepriv, _FW_LINKED) &&
		    (pmlmepriv->fw_state & WIFI_STATION_STATE))
			bStopBlinking = true;
		अगर (check_fwstate(pmlmepriv, _FW_LINKED) &&
		    ((pmlmepriv->fw_state & WIFI_ADHOC_STATE) ||
		    (pmlmepriv->fw_state & WIFI_ADHOC_MASTER_STATE)))
			bStopBlinking = true;
		अन्यथा अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अवरोध;
	हाल LED_BLINK_WPS:
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अवरोध;
	शेष:
		bStopBlinking = true;
		अवरोध;
	पूर्ण
	अगर (bStopBlinking) अणु
		अगर (check_fwstate(pmlmepriv, _FW_LINKED) &&
		    !pLed->bLedOn)
			SwLedOn(padapter, pLed);
		अन्यथा अगर (check_fwstate(pmlmepriv, _FW_LINKED) &&  pLed->bLedOn)
			SwLedOff(padapter, pLed);
		pLed->BlinkTimes = 0;
		pLed->bLedBlinkInProgress = false;
	पूर्ण अन्यथा अणु
		/* Assign LED state to toggle. */
		अगर (pLed->BlinkingLedState == LED_STATE_ON)
			pLed->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed->BlinkingLedState = LED_STATE_ON;

		/* Schedule a समयr to toggle LED state. */
		चयन (pLed->CurrLedState) अणु
		हाल LED_BLINK_NORMAL:
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_NORMAL_INTERVAL));
			अवरोध;
		हाल LED_BLINK_SLOWLY:
		हाल LED_BLINK_StartToBlink:
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SLOWLY_INTERVAL));
			अवरोध;
		हाल LED_BLINK_WPS:
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_LONG_INTERVAL));
			अवरोध;
		शेष:
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SLOWLY_INTERVAL));
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम SwLedBlink1(काष्ठा LED_871x *pLed)
अणु
	काष्ठा _adapter *padapter = pLed->padapter;
	काष्ठा led_priv *ledpriv = &padapter->ledpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा eeprom_priv *peeprompriv = &padapter->eeprompriv;
	काष्ठा LED_871x *pLed1 = &ledpriv->SwLed1;
	u8 bStopBlinking = false;

	अगर (peeprompriv->CustomerID == RT_CID_819x_CAMEO)
		pLed = &ledpriv->SwLed1;
	/* Change LED according to BlinkingLedState specअगरied. */
	अगर (pLed->BlinkingLedState == LED_STATE_ON)
		SwLedOn(padapter, pLed);
	अन्यथा
		SwLedOff(padapter, pLed);
	अगर (peeprompriv->CustomerID == RT_CID_DEFAULT) अणु
		अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
			अगर (!pLed1->bSWLedCtrl) अणु
				SwLedOn(padapter, pLed1);
				pLed1->bSWLedCtrl = true;
			पूर्ण अन्यथा अगर (!pLed1->bLedOn) अणु
				SwLedOn(padapter, pLed1);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!pLed1->bSWLedCtrl) अणु
				SwLedOff(padapter, pLed1);
				pLed1->bSWLedCtrl = true;
			पूर्ण अन्यथा अगर (pLed1->bLedOn) अणु
				SwLedOff(padapter, pLed1);
			पूर्ण
		पूर्ण
	पूर्ण
	चयन (pLed->CurrLedState) अणु
	हाल LED_BLINK_SLOWLY:
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_BLINK_NORMAL:
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_LINK_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_SCAN_BLINK:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अगर (bStopBlinking) अणु
			अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->bLedLinkBlinkInProgress = true;
				pLed->CurrLedState = LED_BLINK_NORMAL;
				अगर (pLed->bLedOn)
					pLed->BlinkingLedState = LED_STATE_OFF;
				अन्यथा
					pLed->BlinkingLedState = LED_STATE_ON;
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_LINK_INTERVAL_ALPHA));
			पूर्ण अन्यथा अगर (!check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->bLedNoLinkBlinkInProgress = true;
				pLed->CurrLedState = LED_BLINK_SLOWLY;
				अगर (pLed->bLedOn)
					pLed->BlinkingLedState = LED_STATE_OFF;
				अन्यथा
					pLed->BlinkingLedState = LED_STATE_ON;
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
			पूर्ण
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_TXRX_BLINK:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अगर (bStopBlinking) अणु
			अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->bLedLinkBlinkInProgress = true;
				pLed->CurrLedState = LED_BLINK_NORMAL;
				अगर (pLed->bLedOn)
					pLed->BlinkingLedState = LED_STATE_OFF;
				अन्यथा
					pLed->BlinkingLedState = LED_STATE_ON;
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_LINK_INTERVAL_ALPHA));
			पूर्ण अन्यथा अगर (!check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->bLedNoLinkBlinkInProgress = true;
				pLed->CurrLedState = LED_BLINK_SLOWLY;
				अगर (pLed->bLedOn)
					pLed->BlinkingLedState = LED_STATE_OFF;
				अन्यथा
					pLed->BlinkingLedState = LED_STATE_ON;
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
			पूर्ण
			pLed->BlinkTimes = 0;
			pLed->bLedBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_BLINK_WPS:
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_BLINK_WPS_STOP:	/* WPS success */
		अगर (pLed->BlinkingLedState == LED_STATE_ON) अणु
			pLed->BlinkingLedState = LED_STATE_OFF;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_WPS_SUCCESS_INTERVAL_ALPHA));
			bStopBlinking = false;
		पूर्ण अन्यथा अणु
			bStopBlinking = true;
		पूर्ण
		अगर (bStopBlinking) अणु
			pLed->bLedLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_NORMAL;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_LINK_INTERVAL_ALPHA));
		पूर्ण
		pLed->bLedWPSBlinkInProgress = false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम SwLedBlink2(काष्ठा LED_871x *pLed)
अणु
	काष्ठा _adapter *padapter = pLed->padapter;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	u8 bStopBlinking = false;

	/* Change LED according to BlinkingLedState specअगरied. */
	अगर (pLed->BlinkingLedState == LED_STATE_ON)
		SwLedOn(padapter, pLed);
	अन्यथा
		SwLedOff(padapter, pLed);
	चयन (pLed->CurrLedState) अणु
	हाल LED_SCAN_BLINK:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अगर (bStopBlinking) अणु
			अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->CurrLedState = LED_STATE_ON;
				pLed->BlinkingLedState = LED_STATE_ON;
				SwLedOn(padapter, pLed);
			पूर्ण अन्यथा अगर (!check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->CurrLedState = LED_STATE_OFF;
				pLed->BlinkingLedState = LED_STATE_OFF;
				SwLedOff(padapter, pLed);
			पूर्ण
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_TXRX_BLINK:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अगर (bStopBlinking) अणु
			अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->CurrLedState = LED_STATE_ON;
				pLed->BlinkingLedState = LED_STATE_ON;
				SwLedOn(padapter, pLed);
			पूर्ण अन्यथा अगर (!check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->CurrLedState = LED_STATE_OFF;
				pLed->BlinkingLedState = LED_STATE_OFF;
				SwLedOff(padapter, pLed);
			पूर्ण
			pLed->bLedBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम SwLedBlink3(काष्ठा LED_871x *pLed)
अणु
	काष्ठा _adapter *padapter = pLed->padapter;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	u8 bStopBlinking = false;

	/* Change LED according to BlinkingLedState specअगरied. */
	अगर (pLed->BlinkingLedState == LED_STATE_ON)
		SwLedOn(padapter, pLed);
	अन्यथा
		अगर (pLed->CurrLedState != LED_BLINK_WPS_STOP)
			SwLedOff(padapter, pLed);
	चयन (pLed->CurrLedState) अणु
	हाल LED_SCAN_BLINK:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अगर (bStopBlinking) अणु
			अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->CurrLedState = LED_STATE_ON;
				pLed->BlinkingLedState = LED_STATE_ON;
				अगर (!pLed->bLedOn)
					SwLedOn(padapter, pLed);
			पूर्ण अन्यथा अगर (!check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->CurrLedState = LED_STATE_OFF;
				pLed->BlinkingLedState = LED_STATE_OFF;
				अगर (pLed->bLedOn)
					SwLedOff(padapter, pLed);
			पूर्ण
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_TXRX_BLINK:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अगर (bStopBlinking) अणु
			अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->CurrLedState = LED_STATE_ON;
				pLed->BlinkingLedState = LED_STATE_ON;
				अगर (!pLed->bLedOn)
					SwLedOn(padapter, pLed);
			पूर्ण अन्यथा अगर (!check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->CurrLedState = LED_STATE_OFF;
				pLed->BlinkingLedState = LED_STATE_OFF;
				अगर (pLed->bLedOn)
					SwLedOff(padapter, pLed);
			पूर्ण
			pLed->bLedBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_BLINK_WPS:
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_BLINK_WPS_STOP:	/*WPS success*/
		अगर (pLed->BlinkingLedState == LED_STATE_ON) अणु
			pLed->BlinkingLedState = LED_STATE_OFF;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_WPS_SUCCESS_INTERVAL_ALPHA));
			bStopBlinking = false;
		पूर्ण अन्यथा अणु
			bStopBlinking = true;
		पूर्ण
		अगर (bStopBlinking) अणु
			pLed->CurrLedState = LED_STATE_ON;
			pLed->BlinkingLedState = LED_STATE_ON;
			SwLedOn(padapter, pLed);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम SwLedBlink4(काष्ठा LED_871x *pLed)
अणु
	काष्ठा _adapter *padapter = pLed->padapter;
	काष्ठा led_priv	*ledpriv = &padapter->ledpriv;
	काष्ठा LED_871x *pLed1 = &ledpriv->SwLed1;
	u8 bStopBlinking = false;

	/* Change LED according to BlinkingLedState specअगरied. */
	अगर (pLed->BlinkingLedState == LED_STATE_ON)
		SwLedOn(padapter, pLed);
	अन्यथा
		SwLedOff(padapter, pLed);
	अगर (!pLed1->bLedWPSBlinkInProgress &&
	    pLed1->BlinkingLedState == LED_UNKNOWN) अणु
		pLed1->BlinkingLedState = LED_STATE_OFF;
		pLed1->CurrLedState = LED_STATE_OFF;
		SwLedOff(padapter, pLed1);
	पूर्ण
	चयन (pLed->CurrLedState) अणु
	हाल LED_BLINK_SLOWLY:
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_BLINK_StartToBlink:
		अगर (pLed->bLedOn) अणु
			pLed->BlinkingLedState = LED_STATE_OFF;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SLOWLY_INTERVAL));
		पूर्ण अन्यथा अणु
			pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_NORMAL_INTERVAL));
		पूर्ण
		अवरोध;
	हाल LED_SCAN_BLINK:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अगर (bStopBlinking) अणु
			pLed->bLedNoLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_SLOWLY;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_TXRX_BLINK:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अगर (bStopBlinking) अणु
			pLed->bLedNoLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_SLOWLY;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
			pLed->bLedBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_BLINK_WPS:
		अगर (pLed->bLedOn) अणु
			pLed->BlinkingLedState = LED_STATE_OFF;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SLOWLY_INTERVAL));
		पूर्ण अन्यथा अणु
			pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_NORMAL_INTERVAL));
		पूर्ण
		अवरोध;
	हाल LED_BLINK_WPS_STOP:	/*WPS authentication fail*/
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_NORMAL_INTERVAL));
		अवरोध;
	हाल LED_BLINK_WPS_STOP_OVERLAP:	/*WPS session overlap */
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0) अणु
			अगर (pLed->bLedOn)
				pLed->BlinkTimes = 1;
			अन्यथा
				bStopBlinking = true;
		पूर्ण
		अगर (bStopBlinking) अणु
			pLed->BlinkTimes = 10;
			pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_LINK_INTERVAL_ALPHA));
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_NORMAL_INTERVAL));
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम SwLedBlink5(काष्ठा LED_871x *pLed)
अणु
	काष्ठा _adapter *padapter = pLed->padapter;
	u8 bStopBlinking = false;

	/* Change LED according to BlinkingLedState specअगरied. */
	अगर (pLed->BlinkingLedState == LED_STATE_ON)
		SwLedOn(padapter, pLed);
	अन्यथा
		SwLedOff(padapter, pLed);
	चयन (pLed->CurrLedState) अणु
	हाल LED_SCAN_BLINK:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अगर (bStopBlinking) अणु
			pLed->CurrLedState = LED_STATE_ON;
			pLed->BlinkingLedState = LED_STATE_ON;
			अगर (!pLed->bLedOn)
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_TXRX_BLINK:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अगर (bStopBlinking) अणु
			pLed->CurrLedState = LED_STATE_ON;
			pLed->BlinkingLedState = LED_STATE_ON;
			अगर (!pLed->bLedOn)
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
			pLed->bLedBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम SwLedBlink6(काष्ठा LED_871x *pLed)
अणु
	काष्ठा _adapter *padapter = pLed->padapter;
	u8 bStopBlinking = false;

	/* Change LED according to BlinkingLedState specअगरied. */
	अगर (pLed->BlinkingLedState == LED_STATE_ON)
		SwLedOn(padapter, pLed);
	अन्यथा
		SwLedOff(padapter, pLed);
	चयन (pLed->CurrLedState) अणु
	हाल LED_TXRX_BLINK:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		अगर (bStopBlinking) अणु
			pLed->CurrLedState = LED_STATE_ON;
			pLed->BlinkingLedState = LED_STATE_ON;
			अगर (!pLed->bLedOn)
				SwLedOn(padapter, pLed);
			pLed->bLedBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_BLINK_WPS:
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*	Description:
 *		Callback function of LED BlinkTimer,
 *		it just schedules to corresponding BlinkWorkItem.
 */
अटल व्योम BlinkTimerCallback(काष्ठा समयr_list *t)
अणु
	काष्ठा LED_871x  *pLed = from_समयr(pLed, t, BlinkTimer);

	/* This fixed the crash problem on Feकरोra 12 when trying to करो the
	 * insmod;अगरconfig up;rmmod commands.
	 */
	अगर (pLed->padapter->surprise_हटाओd || pLed->padapter->driver_stopped)
		वापस;
	schedule_work(&pLed->BlinkWorkItem);
पूर्ण

/*	Description:
 *		Callback function of LED BlinkWorkItem.
 *		We dispatch actual LED blink action according to LedStrategy.
 */
अटल व्योम BlinkWorkItemCallback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा LED_871x *pLed = container_of(work, काष्ठा LED_871x,
				BlinkWorkItem);
	काष्ठा led_priv	*ledpriv = &pLed->padapter->ledpriv;

	चयन (ledpriv->LedStrategy) अणु
	हाल SW_LED_MODE0:
		SwLedBlink(pLed);
		अवरोध;
	हाल SW_LED_MODE1:
		SwLedBlink1(pLed);
		अवरोध;
	हाल SW_LED_MODE2:
		SwLedBlink2(pLed);
		अवरोध;
	हाल SW_LED_MODE3:
		SwLedBlink3(pLed);
		अवरोध;
	हाल SW_LED_MODE4:
		SwLedBlink4(pLed);
		अवरोध;
	हाल SW_LED_MODE5:
		SwLedBlink5(pLed);
		अवरोध;
	हाल SW_LED_MODE6:
		SwLedBlink6(pLed);
		अवरोध;
	शेष:
		SwLedBlink(pLed);
		अवरोध;
	पूर्ण
पूर्ण

/*============================================================================
 * Default LED behavior.
 *============================================================================
 *
 *	Description:
 *		Implement each led action क्रम SW_LED_MODE0.
 *		This is शेष strategy.
 */

अटल व्योम SwLedControlMode1(काष्ठा _adapter *padapter,
			      क्रमागत LED_CTL_MODE LedAction)
अणु
	काष्ठा led_priv *ledpriv = &padapter->ledpriv;
	काष्ठा LED_871x *pLed = &ledpriv->SwLed0;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sitesurvey_ctrl *psitesurveyctrl = &pmlmepriv->sitesurveyctrl;

	अगर (padapter->eeprompriv.CustomerID == RT_CID_819x_CAMEO)
		pLed = &ledpriv->SwLed1;
	चयन (LedAction) अणु
	हाल LED_CTL_START_TO_LINK:
	हाल LED_CTL_NO_LINK:
		अगर (!pLed->bLedNoLinkBlinkInProgress) अणु
			अगर (pLed->CurrLedState == LED_SCAN_BLINK ||
			    IS_LED_WPS_BLINKING(pLed))
				वापस;
			अगर (pLed->bLedLinkBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedLinkBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			pLed->bLedNoLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_SLOWLY;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_LINK:
		अगर (!pLed->bLedLinkBlinkInProgress) अणु
			अगर (pLed->CurrLedState == LED_SCAN_BLINK ||
			    IS_LED_WPS_BLINKING(pLed))
				वापस;
			अगर (pLed->bLedNoLinkBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedNoLinkBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			pLed->bLedLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_NORMAL;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_LINK_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_SITE_SURVEY:
		अगर (psitesurveyctrl->traffic_busy &&
		    check_fwstate(pmlmepriv, _FW_LINKED))
			; /* dummy branch */
		अन्यथा अगर (!pLed->bLedScanBlinkInProgress) अणु
			अगर (IS_LED_WPS_BLINKING(pLed))
				वापस;
			अगर (pLed->bLedNoLinkBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedNoLinkBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedLinkBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedLinkBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			pLed->bLedScanBlinkInProgress = true;
			pLed->CurrLedState = LED_SCAN_BLINK;
			pLed->BlinkTimes = 24;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_TX:
	हाल LED_CTL_RX:
		अगर (!pLed->bLedBlinkInProgress) अणु
			अगर (pLed->CurrLedState == LED_SCAN_BLINK ||
			    IS_LED_WPS_BLINKING(pLed))
				वापस;
			अगर (pLed->bLedNoLinkBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedNoLinkBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedLinkBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedLinkBlinkInProgress = false;
			पूर्ण
			pLed->bLedBlinkInProgress = true;
			pLed->CurrLedState = LED_TXRX_BLINK;
			pLed->BlinkTimes = 2;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;

	हाल LED_CTL_START_WPS: /*रुको until xinpin finish */
	हाल LED_CTL_START_WPS_BOTTON:
		अगर (!pLed->bLedWPSBlinkInProgress) अणु
			अगर (pLed->bLedNoLinkBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedNoLinkBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedLinkBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedLinkBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedScanBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedScanBlinkInProgress = false;
			पूर्ण
			pLed->bLedWPSBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_WPS;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_STOP_WPS:
		अगर (pLed->bLedNoLinkBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedNoLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedLinkBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedScanBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedWPSBlinkInProgress)
			del_समयr(&pLed->BlinkTimer);
		अन्यथा
			pLed->bLedWPSBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_WPS_STOP;
		अगर (pLed->bLedOn) अणु
			pLed->BlinkingLedState = LED_STATE_OFF;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_WPS_SUCCESS_INTERVAL_ALPHA));
		पूर्ण अन्यथा अणु
			pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer,
				  jअगरfies + msecs_to_jअगरfies(0));
		पूर्ण
		अवरोध;
	हाल LED_CTL_STOP_WPS_FAIL:
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		pLed->bLedNoLinkBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_SLOWLY;
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_CTL_POWER_OFF:
		pLed->CurrLedState = LED_STATE_OFF;
		pLed->BlinkingLedState = LED_STATE_OFF;
		अगर (pLed->bLedNoLinkBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedNoLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedLinkBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedScanBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण
		mod_समयr(&pLed->BlinkTimer,
			  jअगरfies + msecs_to_jअगरfies(0));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम SwLedControlMode2(काष्ठा _adapter *padapter,
			      क्रमागत LED_CTL_MODE LedAction)
अणु
	काष्ठा led_priv	 *ledpriv = &padapter->ledpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा LED_871x *pLed = &ledpriv->SwLed0;

	चयन (LedAction) अणु
	हाल LED_CTL_SITE_SURVEY:
		अगर (pmlmepriv->sitesurveyctrl.traffic_busy)
			; /* dummy branch */
		अन्यथा अगर (!pLed->bLedScanBlinkInProgress) अणु
			अगर (IS_LED_WPS_BLINKING(pLed))
				वापस;

			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			pLed->bLedScanBlinkInProgress = true;
			pLed->CurrLedState = LED_SCAN_BLINK;
			pLed->BlinkTimes = 24;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;

	हाल LED_CTL_TX:
	हाल LED_CTL_RX:
		अगर (!pLed->bLedBlinkInProgress &&
		    check_fwstate(pmlmepriv, _FW_LINKED)) अणु
			अगर (pLed->CurrLedState == LED_SCAN_BLINK ||
			    IS_LED_WPS_BLINKING(pLed))
				वापस;
			pLed->bLedBlinkInProgress = true;
			pLed->CurrLedState = LED_TXRX_BLINK;
			pLed->BlinkTimes = 2;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;

	हाल LED_CTL_LINK:
		pLed->CurrLedState = LED_STATE_ON;
		pLed->BlinkingLedState = LED_STATE_ON;
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedScanBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण

		mod_समयr(&pLed->BlinkTimer,
			  jअगरfies + msecs_to_jअगरfies(0));
		अवरोध;

	हाल LED_CTL_START_WPS: /*रुको until xinpin finish*/
	हाल LED_CTL_START_WPS_BOTTON:
		अगर (!pLed->bLedWPSBlinkInProgress) अणु
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedScanBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedScanBlinkInProgress = false;
			पूर्ण
			pLed->bLedWPSBlinkInProgress = true;
			pLed->CurrLedState = LED_STATE_ON;
			pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer,
				  jअगरfies + msecs_to_jअगरfies(0));
		पूर्ण
		अवरोध;

	हाल LED_CTL_STOP_WPS:
		pLed->bLedWPSBlinkInProgress = false;
		pLed->CurrLedState = LED_STATE_ON;
		pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer,
			  jअगरfies + msecs_to_jअगरfies(0));
		अवरोध;

	हाल LED_CTL_STOP_WPS_FAIL:
		pLed->bLedWPSBlinkInProgress = false;
		pLed->CurrLedState = LED_STATE_OFF;
		pLed->BlinkingLedState = LED_STATE_OFF;
		mod_समयr(&pLed->BlinkTimer,
			  jअगरfies + msecs_to_jअगरfies(0));
		अवरोध;

	हाल LED_CTL_START_TO_LINK:
	हाल LED_CTL_NO_LINK:
		अगर (!IS_LED_BLINKING(pLed)) अणु
			pLed->CurrLedState = LED_STATE_OFF;
			pLed->BlinkingLedState = LED_STATE_OFF;
			mod_समयr(&pLed->BlinkTimer,
				  jअगरfies + msecs_to_jअगरfies(0));
		पूर्ण
		अवरोध;
	हाल LED_CTL_POWER_OFF:
		pLed->CurrLedState = LED_STATE_OFF;
		pLed->BlinkingLedState = LED_STATE_OFF;
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedScanBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		mod_समयr(&pLed->BlinkTimer,
			  jअगरfies + msecs_to_jअगरfies(0));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम SwLedControlMode3(काष्ठा _adapter *padapter,
			      क्रमागत LED_CTL_MODE LedAction)
अणु
	काष्ठा led_priv	*ledpriv = &padapter->ledpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा LED_871x *pLed = &ledpriv->SwLed0;

	चयन (LedAction) अणु
	हाल LED_CTL_SITE_SURVEY:
		अगर (pmlmepriv->sitesurveyctrl.traffic_busy)
			; /* dummy branch */
		अन्यथा अगर (!pLed->bLedScanBlinkInProgress) अणु
			अगर (IS_LED_WPS_BLINKING(pLed))
				वापस;
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			pLed->bLedScanBlinkInProgress = true;
			pLed->CurrLedState = LED_SCAN_BLINK;
			pLed->BlinkTimes = 24;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_TX:
	हाल LED_CTL_RX:
		अगर (!pLed->bLedBlinkInProgress &&
		    check_fwstate(pmlmepriv, _FW_LINKED)) अणु
			अगर (pLed->CurrLedState == LED_SCAN_BLINK ||
			    IS_LED_WPS_BLINKING(pLed))
				वापस;
			pLed->bLedBlinkInProgress = true;
			pLed->CurrLedState = LED_TXRX_BLINK;
			pLed->BlinkTimes = 2;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_LINK:
		अगर (IS_LED_WPS_BLINKING(pLed))
			वापस;
		pLed->CurrLedState = LED_STATE_ON;
		pLed->BlinkingLedState = LED_STATE_ON;
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedScanBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण
		mod_समयr(&pLed->BlinkTimer,
			  jअगरfies + msecs_to_jअगरfies(0));
		अवरोध;
	हाल LED_CTL_START_WPS: /* रुको until xinpin finish */
	हाल LED_CTL_START_WPS_BOTTON:
		अगर (!pLed->bLedWPSBlinkInProgress) अणु
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedScanBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedScanBlinkInProgress = false;
			पूर्ण
			pLed->bLedWPSBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_WPS;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_STOP_WPS:
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			pLed->bLedWPSBlinkInProgress = true;
		पूर्ण
		pLed->CurrLedState = LED_BLINK_WPS_STOP;
		अगर (pLed->bLedOn) अणु
			pLed->BlinkingLedState = LED_STATE_OFF;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_WPS_SUCCESS_INTERVAL_ALPHA));
		पूर्ण अन्यथा अणु
			pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer,
				  jअगरfies + msecs_to_jअगरfies(0));
		पूर्ण
		अवरोध;
	हाल LED_CTL_STOP_WPS_FAIL:
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		pLed->CurrLedState = LED_STATE_OFF;
		pLed->BlinkingLedState = LED_STATE_OFF;
		mod_समयr(&pLed->BlinkTimer,
			  jअगरfies + msecs_to_jअगरfies(0));
		अवरोध;
	हाल LED_CTL_START_TO_LINK:
	हाल LED_CTL_NO_LINK:
		अगर (!IS_LED_BLINKING(pLed)) अणु
			pLed->CurrLedState = LED_STATE_OFF;
			pLed->BlinkingLedState = LED_STATE_OFF;
			mod_समयr(&pLed->BlinkTimer,
				  jअगरfies + msecs_to_jअगरfies(0));
		पूर्ण
		अवरोध;
	हाल LED_CTL_POWER_OFF:
		pLed->CurrLedState = LED_STATE_OFF;
		pLed->BlinkingLedState = LED_STATE_OFF;
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedScanBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		mod_समयr(&pLed->BlinkTimer,
			  jअगरfies + msecs_to_jअगरfies(0));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम SwLedControlMode4(काष्ठा _adapter *padapter,
			      क्रमागत LED_CTL_MODE LedAction)
अणु
	काष्ठा led_priv	*ledpriv = &padapter->ledpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा LED_871x *pLed = &ledpriv->SwLed0;
	काष्ठा LED_871x *pLed1 = &ledpriv->SwLed1;

	चयन (LedAction) अणु
	हाल LED_CTL_START_TO_LINK:
		अगर (pLed1->bLedWPSBlinkInProgress) अणु
			pLed1->bLedWPSBlinkInProgress = false;
			del_समयr(&pLed1->BlinkTimer);
			pLed1->BlinkingLedState = LED_STATE_OFF;
			pLed1->CurrLedState = LED_STATE_OFF;
			अगर (pLed1->bLedOn)
				mod_समयr(&pLed->BlinkTimer,
					  jअगरfies + msecs_to_jअगरfies(0));
		पूर्ण
		अगर (!pLed->bLedStartToLinkBlinkInProgress) अणु
			अगर (pLed->CurrLedState == LED_SCAN_BLINK ||
			    IS_LED_WPS_BLINKING(pLed))
				वापस;
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedNoLinkBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedNoLinkBlinkInProgress = false;
			पूर्ण
			pLed->bLedStartToLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_StartToBlink;
			अगर (pLed->bLedOn) अणु
				pLed->BlinkingLedState = LED_STATE_OFF;
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_SLOWLY_INTERVAL));
			पूर्ण अन्यथा अणु
				pLed->BlinkingLedState = LED_STATE_ON;
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_NORMAL_INTERVAL));
			पूर्ण
		पूर्ण
		अवरोध;
	हाल LED_CTL_LINK:
	हाल LED_CTL_NO_LINK:
		/*LED1 settings*/
		अगर (LedAction == LED_CTL_LINK) अणु
			अगर (pLed1->bLedWPSBlinkInProgress) अणु
				pLed1->bLedWPSBlinkInProgress = false;
				del_समयr(&pLed1->BlinkTimer);
				pLed1->BlinkingLedState = LED_STATE_OFF;
				pLed1->CurrLedState = LED_STATE_OFF;
				अगर (pLed1->bLedOn)
					mod_समयr(&pLed->BlinkTimer,
						  jअगरfies + msecs_to_jअगरfies(0));
			पूर्ण
		पूर्ण
		अगर (!pLed->bLedNoLinkBlinkInProgress) अणु
			अगर (pLed->CurrLedState == LED_SCAN_BLINK ||
			    IS_LED_WPS_BLINKING(pLed))
				वापस;
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			pLed->bLedNoLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_SLOWLY;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_SITE_SURVEY:
		अगर (pmlmepriv->sitesurveyctrl.traffic_busy &&
		    check_fwstate(pmlmepriv, _FW_LINKED))
			;
		अन्यथा अगर (!pLed->bLedScanBlinkInProgress) अणु
			अगर (IS_LED_WPS_BLINKING(pLed))
				वापस;
			अगर (pLed->bLedNoLinkBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedNoLinkBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			pLed->bLedScanBlinkInProgress = true;
			pLed->CurrLedState = LED_SCAN_BLINK;
			pLed->BlinkTimes = 24;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_TX:
	हाल LED_CTL_RX:
		अगर (!pLed->bLedBlinkInProgress) अणु
			अगर (pLed->CurrLedState == LED_SCAN_BLINK ||
			    IS_LED_WPS_BLINKING(pLed))
				वापस;
			अगर (pLed->bLedNoLinkBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedNoLinkBlinkInProgress = false;
			पूर्ण
			pLed->bLedBlinkInProgress = true;
			pLed->CurrLedState = LED_TXRX_BLINK;
			pLed->BlinkTimes = 2;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_START_WPS: /*रुको until xinpin finish*/
	हाल LED_CTL_START_WPS_BOTTON:
		अगर (pLed1->bLedWPSBlinkInProgress) अणु
			pLed1->bLedWPSBlinkInProgress = false;
			del_समयr(&pLed1->BlinkTimer);
			pLed1->BlinkingLedState = LED_STATE_OFF;
			pLed1->CurrLedState = LED_STATE_OFF;
			अगर (pLed1->bLedOn)
				mod_समयr(&pLed->BlinkTimer,
					  jअगरfies + msecs_to_jअगरfies(0));
		पूर्ण
		अगर (!pLed->bLedWPSBlinkInProgress) अणु
			अगर (pLed->bLedNoLinkBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedNoLinkBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			अगर (pLed->bLedScanBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedScanBlinkInProgress = false;
			पूर्ण
			pLed->bLedWPSBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_WPS;
			अगर (pLed->bLedOn) अणु
				pLed->BlinkingLedState = LED_STATE_OFF;
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_SLOWLY_INTERVAL));
			पूर्ण अन्यथा अणु
				pLed->BlinkingLedState = LED_STATE_ON;
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_NORMAL_INTERVAL));
			पूर्ण
		पूर्ण
		अवरोध;
	हाल LED_CTL_STOP_WPS:	/*WPS connect success*/
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		pLed->bLedNoLinkBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_SLOWLY;
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_CTL_STOP_WPS_FAIL:	/*WPS authentication fail*/
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		pLed->bLedNoLinkBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_SLOWLY;
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		/*LED1 settings*/
		अगर (pLed1->bLedWPSBlinkInProgress)
			del_समयr(&pLed1->BlinkTimer);
		अन्यथा
			pLed1->bLedWPSBlinkInProgress = true;
		pLed1->CurrLedState = LED_BLINK_WPS_STOP;
		अगर (pLed1->bLedOn)
			pLed1->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed1->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_NORMAL_INTERVAL));
		अवरोध;
	हाल LED_CTL_STOP_WPS_FAIL_OVERLAP:	/*WPS session overlap*/
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		pLed->bLedNoLinkBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_SLOWLY;
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		/*LED1 settings*/
		अगर (pLed1->bLedWPSBlinkInProgress)
			del_समयr(&pLed1->BlinkTimer);
		अन्यथा
			pLed1->bLedWPSBlinkInProgress = true;
		pLed1->CurrLedState = LED_BLINK_WPS_STOP_OVERLAP;
		pLed1->BlinkTimes = 10;
		अगर (pLed1->bLedOn)
			pLed1->BlinkingLedState = LED_STATE_OFF;
		अन्यथा
			pLed1->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_NORMAL_INTERVAL));
		अवरोध;
	हाल LED_CTL_POWER_OFF:
		pLed->CurrLedState = LED_STATE_OFF;
		pLed->BlinkingLedState = LED_STATE_OFF;
		अगर (pLed->bLedNoLinkBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedNoLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedLinkBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedScanBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedStartToLinkBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedStartToLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed1->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed1->BlinkTimer);
			pLed1->bLedWPSBlinkInProgress = false;
		पूर्ण
		pLed1->BlinkingLedState = LED_UNKNOWN;
		SwLedOff(padapter, pLed);
		SwLedOff(padapter, pLed1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम SwLedControlMode5(काष्ठा _adapter *padapter,
			      क्रमागत LED_CTL_MODE LedAction)
अणु
	काष्ठा led_priv	*ledpriv = &padapter->ledpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा LED_871x *pLed = &ledpriv->SwLed0;

	अगर (padapter->eeprompriv.CustomerID == RT_CID_819x_CAMEO)
		pLed = &ledpriv->SwLed1;

	चयन (LedAction) अणु
	हाल LED_CTL_POWER_ON:
	हाल LED_CTL_NO_LINK:
	हाल LED_CTL_LINK:	/* solid blue */
		अगर (pLed->CurrLedState == LED_SCAN_BLINK)
			वापस;
		pLed->CurrLedState = LED_STATE_ON;
		pLed->BlinkingLedState = LED_STATE_ON;
		pLed->bLedBlinkInProgress = false;
		mod_समयr(&pLed->BlinkTimer,
			  jअगरfies + msecs_to_jअगरfies(0));
		अवरोध;
	हाल LED_CTL_SITE_SURVEY:
		अगर (pmlmepriv->sitesurveyctrl.traffic_busy &&
		    check_fwstate(pmlmepriv, _FW_LINKED))
			; /* dummy branch */
		अन्यथा अगर (!pLed->bLedScanBlinkInProgress) अणु
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			pLed->bLedScanBlinkInProgress = true;
			pLed->CurrLedState = LED_SCAN_BLINK;
			pLed->BlinkTimes = 24;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_TX:
	हाल LED_CTL_RX:
		अगर (!pLed->bLedBlinkInProgress) अणु
			अगर (pLed->CurrLedState == LED_SCAN_BLINK)
				वापस;
			pLed->bLedBlinkInProgress = true;
			pLed->CurrLedState = LED_TXRX_BLINK;
			pLed->BlinkTimes = 2;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_POWER_OFF:
		pLed->CurrLedState = LED_STATE_OFF;
		pLed->BlinkingLedState = LED_STATE_OFF;
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		SwLedOff(padapter, pLed);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम SwLedControlMode6(काष्ठा _adapter *padapter,
			      क्रमागत LED_CTL_MODE LedAction)
अणु
	काष्ठा led_priv	*ledpriv = &padapter->ledpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा LED_871x *pLed = &ledpriv->SwLed0;

	चयन (LedAction) अणु
	हाल LED_CTL_POWER_ON:
	हाल LED_CTL_NO_LINK:
	हाल LED_CTL_LINK:	/*solid blue*/
	हाल LED_CTL_SITE_SURVEY:
		अगर (IS_LED_WPS_BLINKING(pLed))
			वापस;
		pLed->CurrLedState = LED_STATE_ON;
		pLed->BlinkingLedState = LED_STATE_ON;
		pLed->bLedBlinkInProgress = false;
		mod_समयr(&pLed->BlinkTimer, jअगरfies + msecs_to_jअगरfies(0));
		अवरोध;
	हाल LED_CTL_TX:
	हाल LED_CTL_RX:
		अगर (!pLed->bLedBlinkInProgress &&
		    check_fwstate(pmlmepriv, _FW_LINKED)) अणु
			अगर (IS_LED_WPS_BLINKING(pLed))
				वापस;
			pLed->bLedBlinkInProgress = true;
			pLed->CurrLedState = LED_TXRX_BLINK;
			pLed->BlinkTimes = 2;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_START_WPS: /*रुको until xinpin finish*/
	हाल LED_CTL_START_WPS_BOTTON:
		अगर (!pLed->bLedWPSBlinkInProgress) अणु
			अगर (pLed->bLedBlinkInProgress) अणु
				del_समयr(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			पूर्ण
			pLed->bLedWPSBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_WPS;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			अन्यथा
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_CTL_STOP_WPS_FAIL:
	हाल LED_CTL_STOP_WPS:
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		pLed->CurrLedState = LED_STATE_ON;
		pLed->BlinkingLedState = LED_STATE_ON;
		mod_समयr(&pLed->BlinkTimer,
			  jअगरfies + msecs_to_jअगरfies(0));
		अवरोध;
	हाल LED_CTL_POWER_OFF:
		pLed->CurrLedState = LED_STATE_OFF;
		pLed->BlinkingLedState = LED_STATE_OFF;
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		SwLedOff(padapter, pLed);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*	Description:
 *		Dispatch LED action according to pHalData->LedStrategy.
 */
व्योम LedControl871x(काष्ठा _adapter *padapter, क्रमागत LED_CTL_MODE LedAction)
अणु
	काष्ठा led_priv	*ledpriv = &padapter->ledpriv;

	अगर (!ledpriv->bRegUseLed)
		वापस;
	चयन (ledpriv->LedStrategy) अणु
	हाल SW_LED_MODE0:
		अवरोध;
	हाल SW_LED_MODE1:
		SwLedControlMode1(padapter, LedAction);
		अवरोध;
	हाल SW_LED_MODE2:
		SwLedControlMode2(padapter, LedAction);
		अवरोध;
	हाल SW_LED_MODE3:
		SwLedControlMode3(padapter, LedAction);
		अवरोध;
	हाल SW_LED_MODE4:
		SwLedControlMode4(padapter, LedAction);
		अवरोध;
	हाल SW_LED_MODE5:
		SwLedControlMode5(padapter, LedAction);
		अवरोध;
	हाल SW_LED_MODE6:
		SwLedControlMode6(padapter, LedAction);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
