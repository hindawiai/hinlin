<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश <drv_types.h>
#समावेश "rtw_led.h"

/*  */
/*	Description: */
/*		Callback function of LED BlinkTimer, */
/*		it just schedules to corresponding BlinkWorkItem/led_blink_hdl */
/*  */
अटल व्योम BlinkTimerCallback(काष्ठा समयr_list *t)
अणु
	काष्ठा LED_871x *pLed = from_समयr(pLed, t, BlinkTimer);
	काष्ठा adapter *padapter = pLed->padapter;

	अगर (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		वापस;

	schedule_work(&pLed->BlinkWorkItem);
पूर्ण

/*  */
/*	Description: */
/*		Callback function of LED BlinkWorkItem. */
/*  */
व्योम BlinkWorkItemCallback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा LED_871x *pLed = container_of(work, काष्ठा LED_871x,
						BlinkWorkItem);

	blink_handler(pLed);
पूर्ण

/*  */
/*	Description: */
/*		Reset status of LED_871x object. */
/*  */
व्योम ResetLedStatus(काष्ठा LED_871x *pLed)
अणु
	pLed->CurrLedState = RTW_LED_OFF; /*  Current LED state. */
	pLed->bLedOn = false; /*  true अगर LED is ON, false अगर LED is OFF. */

	pLed->bLedBlinkInProgress = false; /*  true अगर it is blinking, false o.w.. */
	pLed->bLedWPSBlinkInProgress = false;

	pLed->BlinkTimes = 0; /*  Number of बार to toggle led state क्रम blinking. */
	pLed->BlinkingLedState = LED_UNKNOWN; /*  Next state क्रम blinking, either RTW_LED_ON or RTW_LED_OFF are. */

	pLed->bLedNoLinkBlinkInProgress = false;
	pLed->bLedLinkBlinkInProgress = false;
	pLed->bLedScanBlinkInProgress = false;
पूर्ण

/*Description: */
/*		Initialize an LED_871x object. */
व्योम InitLed871x(काष्ठा adapter *padapter, काष्ठा LED_871x *pLed)
अणु
	pLed->padapter = padapter;

	ResetLedStatus(pLed);

	समयr_setup(&pLed->BlinkTimer, BlinkTimerCallback, 0);

	INIT_WORK(&pLed->BlinkWorkItem, BlinkWorkItemCallback);
पूर्ण

/*  */
/*	Description: */
/*		DeInitialize an LED_871x object. */
/*  */
व्योम DeInitLed871x(काष्ठा LED_871x *pLed)
अणु
	cancel_work_sync(&pLed->BlinkWorkItem);
	del_समयr_sync(&pLed->BlinkTimer);
	ResetLedStatus(pLed);
पूर्ण

/*  */
/*	Description: */
/*		Implementation of LED blinking behavior. */
/*		It toggle off LED and schedule corresponding समयr अगर necessary. */
/*  */

अटल व्योम SwLedBlink1(काष्ठा LED_871x *pLed)
अणु
	काष्ठा adapter *padapter = pLed->padapter;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	/*  Change LED according to BlinkingLedState specअगरied. */
	अगर (pLed->BlinkingLedState == RTW_LED_ON) अणु
		sw_led_on(padapter, pLed);
		RT_TRACE(_module_rtl8712_led_c_, _drv_info_,
			 ("Blinktimes (%d): turn on\n", pLed->BlinkTimes));
	पूर्ण अन्यथा अणु
		sw_led_off(padapter, pLed);
		RT_TRACE(_module_rtl8712_led_c_, _drv_info_,
			 ("Blinktimes (%d): turn off\n", pLed->BlinkTimes));
	पूर्ण

	अगर (padapter->pwrctrlpriv.rf_pwrstate != rf_on) अणु
		sw_led_off(padapter, pLed);
		ResetLedStatus(pLed);
		वापस;
	पूर्ण

	चयन (pLed->CurrLedState) अणु
	हाल LED_BLINK_SLOWLY:
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = RTW_LED_OFF;
		अन्यथा
			pLed->BlinkingLedState = RTW_LED_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_BLINK_NORMAL:
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = RTW_LED_OFF;
		अन्यथा
			pLed->BlinkingLedState = RTW_LED_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_LINK_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_BLINK_SCAN:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0) अणु
			अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->bLedLinkBlinkInProgress = true;
				pLed->CurrLedState = LED_BLINK_NORMAL;
				अगर (pLed->bLedOn)
					pLed->BlinkingLedState = RTW_LED_OFF;
				अन्यथा
					pLed->BlinkingLedState = RTW_LED_ON;
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_LINK_INTERVAL_ALPHA));
				RT_TRACE(_module_rtl8712_led_c_, _drv_info_, ("CurrLedState %d\n", pLed->CurrLedState));
			पूर्ण अन्यथा अगर (!check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->bLedNoLinkBlinkInProgress = true;
				pLed->CurrLedState = LED_BLINK_SLOWLY;
				अगर (pLed->bLedOn)
					pLed->BlinkingLedState = RTW_LED_OFF;
				अन्यथा
					pLed->BlinkingLedState = RTW_LED_ON;
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
				RT_TRACE(_module_rtl8712_led_c_, _drv_info_, ("CurrLedState %d\n", pLed->CurrLedState));
			पूर्ण
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = RTW_LED_OFF;
			अन्यथा
				pLed->BlinkingLedState = RTW_LED_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_BLINK_TXRX:
		pLed->BlinkTimes--;
		अगर (pLed->BlinkTimes == 0) अणु
			अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->bLedLinkBlinkInProgress = true;
				pLed->CurrLedState = LED_BLINK_NORMAL;
				अगर (pLed->bLedOn)
					pLed->BlinkingLedState = RTW_LED_OFF;
				अन्यथा
					pLed->BlinkingLedState = RTW_LED_ON;
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_LINK_INTERVAL_ALPHA));
				RT_TRACE(_module_rtl8712_led_c_, _drv_info_, ("CurrLedState %d\n", pLed->CurrLedState));
			पूर्ण अन्यथा अगर (!check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				pLed->bLedNoLinkBlinkInProgress = true;
				pLed->CurrLedState = LED_BLINK_SLOWLY;
				अगर (pLed->bLedOn)
					pLed->BlinkingLedState = RTW_LED_OFF;
				अन्यथा
					pLed->BlinkingLedState = RTW_LED_ON;
				mod_समयr(&pLed->BlinkTimer, jअगरfies +
					  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
				RT_TRACE(_module_rtl8712_led_c_, _drv_info_, ("CurrLedState %d\n", pLed->CurrLedState));
			पूर्ण
			pLed->bLedBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = RTW_LED_OFF;
			अन्यथा
				pLed->BlinkingLedState = RTW_LED_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	हाल LED_BLINK_WPS:
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = RTW_LED_OFF;
		अन्यथा
			pLed->BlinkingLedState = RTW_LED_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_BLINK_WPS_STOP:	/* WPS success */
		अगर (pLed->BlinkingLedState != RTW_LED_ON) अणु
			pLed->bLedLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_NORMAL;
			अगर (pLed->bLedOn)
				pLed->BlinkingLedState = RTW_LED_OFF;
			अन्यथा
				pLed->BlinkingLedState = RTW_LED_ON;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_LINK_INTERVAL_ALPHA));
			RT_TRACE(_module_rtl8712_led_c_, _drv_info_, ("CurrLedState %d\n", pLed->CurrLedState));

			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण अन्यथा अणु
			pLed->BlinkingLedState = RTW_LED_OFF;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_WPS_SUCCESS_INTERVAL_ALPHA));
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

 /* ALPHA, added by chiyoko, 20090106 */
अटल व्योम SwLedControlMode1(काष्ठा adapter *padapter, क्रमागत LED_CTL_MODE LedAction)
अणु
	काष्ठा led_priv *ledpriv = &padapter->ledpriv;
	काष्ठा LED_871x *pLed = &ledpriv->sw_led;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	चयन (LedAction) अणु
	हाल LED_CTL_POWER_ON:
	हाल LED_CTL_START_TO_LINK:
	हाल LED_CTL_NO_LINK:
		अगर (pLed->bLedNoLinkBlinkInProgress)
			अवरोध;
		अगर (pLed->CurrLedState == LED_BLINK_SCAN ||
		    IS_LED_WPS_BLINKING(pLed))
			वापस;
		अगर (pLed->bLedLinkBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		pLed->bLedNoLinkBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_SLOWLY;
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = RTW_LED_OFF;
		अन्यथा
			pLed->BlinkingLedState = RTW_LED_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_CTL_LINK:
		अगर (pLed->bLedLinkBlinkInProgress)
			अवरोध;
		अगर (pLed->CurrLedState == LED_BLINK_SCAN ||
		    IS_LED_WPS_BLINKING(pLed))
			वापस;
		अगर (pLed->bLedNoLinkBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedNoLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		pLed->bLedLinkBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_NORMAL;
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = RTW_LED_OFF;
		अन्यथा
			pLed->BlinkingLedState = RTW_LED_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_LINK_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_CTL_SITE_SURVEY:
		अगर (pmlmepriv->LinkDetectInfo.bBusyTraffic &&
		    check_fwstate(pmlmepriv, _FW_LINKED))
			अवरोध;
		अगर (pLed->bLedScanBlinkInProgress)
			अवरोध;
		अगर (IS_LED_WPS_BLINKING(pLed))
			वापस;
		अगर (pLed->bLedNoLinkBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedNoLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedLinkBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		pLed->bLedScanBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_SCAN;
		pLed->BlinkTimes = 24;
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = RTW_LED_OFF;
		अन्यथा
			pLed->BlinkingLedState = RTW_LED_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_CTL_TX:
	हाल LED_CTL_RX:
		अगर (pLed->bLedBlinkInProgress)
			अवरोध;
		अगर (pLed->CurrLedState == LED_BLINK_SCAN ||
		    IS_LED_WPS_BLINKING(pLed))
			वापस;
		अगर (pLed->bLedNoLinkBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedNoLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedLinkBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedLinkBlinkInProgress = false;
		पूर्ण
		pLed->bLedBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_TXRX;
		pLed->BlinkTimes = 2;
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = RTW_LED_OFF;
		अन्यथा
			pLed->BlinkingLedState = RTW_LED_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_CTL_START_WPS: /* रुको until xinpin finish */
	हाल LED_CTL_START_WPS_BOTTON:
		अगर (pLed->bLedWPSBlinkInProgress)
			अवरोध;
		अगर (pLed->bLedNoLinkBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedNoLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedLinkBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedScanBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण
		pLed->bLedWPSBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_WPS;
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = RTW_LED_OFF;
		अन्यथा
			pLed->BlinkingLedState = RTW_LED_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_CTL_STOP_WPS:
		अगर (pLed->bLedNoLinkBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedNoLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedLinkBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedScanBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedWPSBlinkInProgress)
			del_समयr_sync(&pLed->BlinkTimer);
		अन्यथा
			pLed->bLedWPSBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_WPS_STOP;
		अगर (pLed->bLedOn) अणु
			pLed->BlinkingLedState = RTW_LED_OFF;
			mod_समयr(&pLed->BlinkTimer, jअगरfies +
				  msecs_to_jअगरfies(LED_BLINK_WPS_SUCCESS_INTERVAL_ALPHA));
		पूर्ण अन्यथा अणु
			pLed->BlinkingLedState = RTW_LED_ON;
			mod_समयr(&pLed->BlinkTimer,
				  jअगरfies + msecs_to_jअगरfies(0));
		पूर्ण
		अवरोध;
	हाल LED_CTL_STOP_WPS_FAIL:
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		pLed->bLedNoLinkBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_SLOWLY;
		अगर (pLed->bLedOn)
			pLed->BlinkingLedState = RTW_LED_OFF;
		अन्यथा
			pLed->BlinkingLedState = RTW_LED_ON;
		mod_समयr(&pLed->BlinkTimer, jअगरfies +
			  msecs_to_jअगरfies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		अवरोध;
	हाल LED_CTL_POWER_OFF:
		pLed->CurrLedState = RTW_LED_OFF;
		pLed->BlinkingLedState = RTW_LED_OFF;
		अगर (pLed->bLedNoLinkBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedNoLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedLinkBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedLinkBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedWPSBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		पूर्ण
		अगर (pLed->bLedScanBlinkInProgress) अणु
			del_समयr_sync(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		पूर्ण
		sw_led_off(padapter, pLed);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	RT_TRACE(_module_rtl8712_led_c_, _drv_info_,
		 ("Led %d\n", pLed->CurrLedState));
पूर्ण

व्योम blink_handler(काष्ठा LED_871x *pLed)
अणु
	काष्ठा adapter *padapter = pLed->padapter;

	अगर (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		वापस;

	SwLedBlink1(pLed);
पूर्ण

व्योम led_control_8188eu(काष्ठा adapter *padapter, क्रमागत LED_CTL_MODE LedAction)
अणु
	अगर (padapter->bSurpriseRemoved || padapter->bDriverStopped ||
	    !padapter->hw_init_completed)
		वापस;

	अगर ((padapter->pwrctrlpriv.rf_pwrstate != rf_on &&
	     padapter->pwrctrlpriv.rfoff_reason > RF_CHANGE_BY_PS) &&
	    (LedAction == LED_CTL_TX || LedAction == LED_CTL_RX ||
	     LedAction == LED_CTL_SITE_SURVEY ||
	     LedAction == LED_CTL_LINK ||
	     LedAction == LED_CTL_NO_LINK ||
	     LedAction == LED_CTL_POWER_ON))
		वापस;

	SwLedControlMode1(padapter, LedAction);
पूर्ण
