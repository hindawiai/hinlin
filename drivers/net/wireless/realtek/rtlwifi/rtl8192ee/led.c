<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "reg.h"
#समावेश "led.h"

अटल व्योम _rtl92ee_init_led(काष्ठा ieee80211_hw *hw,
			      काष्ठा rtl_led *pled, क्रमागत rtl_led_pin ledpin)
अणु
	pled->hw = hw;
	pled->ledpin = ledpin;
	pled->leकरोn = false;
पूर्ण

व्योम rtl92ee_sw_led_on(काष्ठा ieee80211_hw *hw, काष्ठा rtl_led *pled)
अणु
	u32 ledcfg;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_LED, DBG_LOUD,
		"LedAddr:%X ledpin=%d\n", REG_LEDCFG2, pled->ledpin);

	चयन (pled->ledpin) अणु
	हाल LED_PIN_GPIO0:
		अवरोध;
	हाल LED_PIN_LED0:
		ledcfg = rtl_पढ़ो_dword(rtlpriv , REG_GPIO_PIN_CTRL);
		ledcfg &= ~BIT(13);
		ledcfg |= BIT(21);
		ledcfg &= ~BIT(29);

		rtl_ग_लिखो_dword(rtlpriv, REG_GPIO_PIN_CTRL, ledcfg);

		अवरोध;
	हाल LED_PIN_LED1:

		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n", pled->ledpin);
		अवरोध;
	पूर्ण
	pled->leकरोn = true;
पूर्ण

व्योम rtl92ee_sw_led_off(काष्ठा ieee80211_hw *hw, काष्ठा rtl_led *pled)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 ledcfg;

	rtl_dbg(rtlpriv, COMP_LED, DBG_LOUD,
		"LedAddr:%X ledpin=%d\n", REG_LEDCFG2, pled->ledpin);

	चयन (pled->ledpin) अणु
	हाल LED_PIN_GPIO0:
		अवरोध;
	हाल LED_PIN_LED0:

		ledcfg = rtl_पढ़ो_dword(rtlpriv , REG_GPIO_PIN_CTRL);
		ledcfg |= ~BIT(21);
		ledcfg &= ~BIT(29);
		rtl_ग_लिखो_dword(rtlpriv, REG_GPIO_PIN_CTRL, ledcfg);

		अवरोध;
	हाल LED_PIN_LED1:

		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n", pled->ledpin);
		अवरोध;
	पूर्ण
	pled->leकरोn = false;
पूर्ण

व्योम rtl92ee_init_sw_leds(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	_rtl92ee_init_led(hw, &rtlpriv->ledctl.sw_led0, LED_PIN_LED0);
	_rtl92ee_init_led(hw, &rtlpriv->ledctl.sw_led1, LED_PIN_LED1);
पूर्ण

अटल व्योम _rtl92ee_sw_led_control(काष्ठा ieee80211_hw *hw,
				    क्रमागत led_ctl_mode ledaction)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_led *pled0 = &rtlpriv->ledctl.sw_led0;

	चयन (ledaction) अणु
	हाल LED_CTL_POWER_ON:
	हाल LED_CTL_LINK:
	हाल LED_CTL_NO_LINK:
		rtl92ee_sw_led_on(hw, pled0);
		अवरोध;
	हाल LED_CTL_POWER_OFF:
		rtl92ee_sw_led_off(hw, pled0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl92ee_led_control(काष्ठा ieee80211_hw *hw, क्रमागत led_ctl_mode ledaction)
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
	rtl_dbg(rtlpriv, COMP_LED, DBG_TRACE, "ledaction %d,\n", ledaction);
	_rtl92ee_sw_led_control(hw, ledaction);
पूर्ण
