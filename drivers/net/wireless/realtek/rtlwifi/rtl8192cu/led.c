<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../usb.h"
#समावेश "reg.h"
#समावेश "led.h"

अटल व्योम _rtl92cu_init_led(काष्ठा ieee80211_hw *hw,
			      काष्ठा rtl_led *pled, क्रमागत rtl_led_pin ledpin)
अणु
	pled->hw = hw;
	pled->ledpin = ledpin;
	pled->leकरोn = false;
पूर्ण

अटल व्योम rtl92cu_deinit_led(काष्ठा rtl_led *pled)
अणु
पूर्ण

व्योम rtl92cu_sw_led_on(काष्ठा ieee80211_hw *hw, काष्ठा rtl_led *pled)
अणु
	u8 ledcfg;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_LED, DBG_LOUD, "LedAddr:%X ledpin=%d\n",
		REG_LEDCFG2, pled->ledpin);
	ledcfg = rtl_पढ़ो_byte(rtlpriv, REG_LEDCFG2);
	चयन (pled->ledpin) अणु
	हाल LED_PIN_GPIO0:
		अवरोध;
	हाल LED_PIN_LED0:
		rtl_ग_लिखो_byte(rtlpriv,
			       REG_LEDCFG2, (ledcfg & 0xf0) | BIT(5) | BIT(6));
		अवरोध;
	हाल LED_PIN_LED1:
		rtl_ग_लिखो_byte(rtlpriv, REG_LEDCFG2, (ledcfg & 0x0f) | BIT(5));
		अवरोध;
	शेष:
		pr_err("switch case %#x not processed\n",
		       pled->ledpin);
		अवरोध;
	पूर्ण
	pled->leकरोn = true;
पूर्ण

व्योम rtl92cu_sw_led_off(काष्ठा ieee80211_hw *hw, काष्ठा rtl_led *pled)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 ledcfg;

	rtl_dbg(rtlpriv, COMP_LED, DBG_LOUD, "LedAddr:%X ledpin=%d\n",
		REG_LEDCFG2, pled->ledpin);
	ledcfg = rtl_पढ़ो_byte(rtlpriv, REG_LEDCFG2);
	चयन (pled->ledpin) अणु
	हाल LED_PIN_GPIO0:
		अवरोध;
	हाल LED_PIN_LED0:
		ledcfg &= 0xf0;
		अगर (rtlpriv->ledctl.led_खोलोdrain)
			rtl_ग_लिखो_byte(rtlpriv, REG_LEDCFG2,
				       (ledcfg | BIT(1) | BIT(5) | BIT(6)));
		अन्यथा
			rtl_ग_लिखो_byte(rtlpriv, REG_LEDCFG2,
				       (ledcfg | BIT(3) | BIT(5) | BIT(6)));
		अवरोध;
	हाल LED_PIN_LED1:
		ledcfg &= 0x0f;
		rtl_ग_लिखो_byte(rtlpriv, REG_LEDCFG2, (ledcfg | BIT(3)));
		अवरोध;
	शेष:
		pr_err("switch case %#x not processed\n",
		       pled->ledpin);
		अवरोध;
	पूर्ण
	pled->leकरोn = false;
पूर्ण

व्योम rtl92cu_init_sw_leds(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	_rtl92cu_init_led(hw, &rtlpriv->ledctl.sw_led0, LED_PIN_LED0);
	_rtl92cu_init_led(hw, &rtlpriv->ledctl.sw_led1, LED_PIN_LED1);
पूर्ण

व्योम rtl92cu_deinit_sw_leds(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl92cu_deinit_led(&rtlpriv->ledctl.sw_led0);
	rtl92cu_deinit_led(&rtlpriv->ledctl.sw_led1);
पूर्ण

अटल व्योम _rtl92cu_sw_led_control(काष्ठा ieee80211_hw *hw,
				    क्रमागत led_ctl_mode ledaction)
अणु
पूर्ण

व्योम rtl92cu_led_control(काष्ठा ieee80211_hw *hw,
			क्रमागत led_ctl_mode ledaction)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	अगर ((ppsc->rfoff_reason > RF_CHANGE_BY_PS) &&
	    (ledaction == LED_CTL_TX ||
	     ledaction == LED_CTL_RX ||
	     ledaction == LED_CTL_SITE_SURVEY ||
	     ledaction == LED_CTL_LINK ||
	     ledaction == LED_CTL_NO_LINK ||
	     ledaction == LED_CTL_START_TO_LINK ||
	     ledaction == LED_CTL_POWER_ON)) अणु
		वापस;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_LED, DBG_LOUD, "ledaction %d\n", ledaction);
	_rtl92cu_sw_led_control(hw, ledaction);
पूर्ण
