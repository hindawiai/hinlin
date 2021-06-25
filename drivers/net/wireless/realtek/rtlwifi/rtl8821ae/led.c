<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2010  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "reg.h"
#समावेश "led.h"

अटल व्योम _rtl8821ae_init_led(काष्ठा ieee80211_hw *hw,
				काष्ठा rtl_led *pled,
				क्रमागत rtl_led_pin ledpin)
अणु
	pled->hw = hw;
	pled->ledpin = ledpin;
	pled->leकरोn = false;
पूर्ण

व्योम rtl8821ae_sw_led_on(काष्ठा ieee80211_hw *hw, काष्ठा rtl_led *pled)
अणु
	u8 ledcfg;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_LED, DBG_LOUD,
		"LedAddr:%X ledpin=%d\n", REG_LEDCFG2, pled->ledpin);

	चयन (pled->ledpin) अणु
	हाल LED_PIN_GPIO0:
		अवरोध;
	हाल LED_PIN_LED0:
		ledcfg = rtl_पढ़ो_byte(rtlpriv, REG_LEDCFG2);
		ledcfg &= ~BIT(6);
		rtl_ग_लिखो_byte(rtlpriv,
			       REG_LEDCFG2, (ledcfg & 0xf0) | BIT(5));
		अवरोध;
	हाल LED_PIN_LED1:
		ledcfg = rtl_पढ़ो_byte(rtlpriv, REG_LEDCFG1);
		rtl_ग_लिखो_byte(rtlpriv, REG_LEDCFG1, ledcfg & 0x10);
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n", pled->ledpin);
		अवरोध;
	पूर्ण
	pled->leकरोn = true;
पूर्ण

व्योम rtl8812ae_sw_led_on(काष्ठा ieee80211_hw *hw, काष्ठा rtl_led *pled)
अणु
	u16	ledreg = REG_LEDCFG1;
	u8	ledcfg = 0;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	चयन (pled->ledpin) अणु
	हाल LED_PIN_LED0:
		ledreg = REG_LEDCFG1;
		अवरोध;

	हाल LED_PIN_LED1:
		ledreg = REG_LEDCFG2;
		अवरोध;

	हाल LED_PIN_GPIO0:
	शेष:
		अवरोध;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_LED, DBG_LOUD,
		"In SwLedOn, LedAddr:%X LEDPIN=%d\n",
		ledreg, pled->ledpin);

	ledcfg =  rtl_पढ़ो_byte(rtlpriv, ledreg);
	ledcfg |= BIT(5); /*Set 0x4c[21]*/
	ledcfg &= ~(BIT(7) | BIT(6) | BIT(3) | BIT(2) | BIT(1) | BIT(0));
		/*Clear 0x4c[23:22] and 0x4c[19:16]*/
	rtl_ग_लिखो_byte(rtlpriv, ledreg, ledcfg); /*SW control led0 on.*/
	pled->leकरोn = true;
पूर्ण

व्योम rtl8821ae_sw_led_off(काष्ठा ieee80211_hw *hw, काष्ठा rtl_led *pled)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 ledcfg;

	rtl_dbg(rtlpriv, COMP_LED, DBG_LOUD,
		"LedAddr:%X ledpin=%d\n", REG_LEDCFG2, pled->ledpin);

	ledcfg = rtl_पढ़ो_byte(rtlpriv, REG_LEDCFG2);

	चयन (pled->ledpin) अणु
	हाल LED_PIN_GPIO0:
		अवरोध;
	हाल LED_PIN_LED0:
		ledcfg &= 0xf0;
		अगर (rtlpriv->ledctl.led_खोलोdrain) अणु
			ledcfg &= 0x90; /* Set to software control. */
			rtl_ग_लिखो_byte(rtlpriv, REG_LEDCFG2, (ledcfg|BIT(3)));
			ledcfg = rtl_पढ़ो_byte(rtlpriv, REG_MAC_PINMUX_CFG);
			ledcfg &= 0xFE;
			rtl_ग_लिखो_byte(rtlpriv, REG_MAC_PINMUX_CFG, ledcfg);
		पूर्ण अन्यथा अणु
			ledcfg &= ~BIT(6);
			rtl_ग_लिखो_byte(rtlpriv, REG_LEDCFG2,
				       (ledcfg | BIT(3) | BIT(5)));
		पूर्ण
		अवरोध;
	हाल LED_PIN_LED1:
		ledcfg = rtl_पढ़ो_byte(rtlpriv, REG_LEDCFG1);
		ledcfg &= 0x10; /* Set to software control. */
		rtl_ग_लिखो_byte(rtlpriv, REG_LEDCFG1, ledcfg|BIT(3));
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n", pled->ledpin);
		अवरोध;
	पूर्ण
	pled->leकरोn = false;
पूर्ण

व्योम rtl8812ae_sw_led_off(काष्ठा ieee80211_hw *hw, काष्ठा rtl_led *pled)
अणु
	u16 ledreg = REG_LEDCFG1;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	चयन (pled->ledpin) अणु
	हाल LED_PIN_LED0:
		ledreg = REG_LEDCFG1;
		अवरोध;

	हाल LED_PIN_LED1:
		ledreg = REG_LEDCFG2;
		अवरोध;

	हाल LED_PIN_GPIO0:
	शेष:
		अवरोध;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_LED, DBG_LOUD,
		"In SwLedOff,LedAddr:%X LEDPIN=%d\n",
		ledreg, pled->ledpin);
	/*Open-drain arrangement क्रम controlling the LED*/
	अगर (rtlpriv->ledctl.led_खोलोdrain) अणु
		u8 ledcfg = rtl_पढ़ो_byte(rtlpriv, ledreg);

		ledreg &= 0xd0; /* Set to software control.*/
		rtl_ग_लिखो_byte(rtlpriv, ledreg, (ledcfg | BIT(3)));

		/*Open-drain arrangement*/
		ledcfg = rtl_पढ़ो_byte(rtlpriv, REG_MAC_PINMUX_CFG);
		ledcfg &= 0xFE;/*Set GPIO[8] to input mode*/
		rtl_ग_लिखो_byte(rtlpriv, REG_MAC_PINMUX_CFG, ledcfg);
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_byte(rtlpriv, ledreg, 0x28);
	पूर्ण

	pled->leकरोn = false;
पूर्ण

व्योम rtl8821ae_init_sw_leds(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	_rtl8821ae_init_led(hw, &rtlpriv->ledctl.sw_led0, LED_PIN_LED0);
	_rtl8821ae_init_led(hw, &rtlpriv->ledctl.sw_led1, LED_PIN_LED1);
पूर्ण

अटल व्योम _rtl8821ae_sw_led_control(काष्ठा ieee80211_hw *hw,
				      क्रमागत led_ctl_mode ledaction)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_led *pled0 = &rtlpriv->ledctl.sw_led0;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	चयन (ledaction) अणु
	हाल LED_CTL_POWER_ON:
	हाल LED_CTL_LINK:
	हाल LED_CTL_NO_LINK:
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8812ae_sw_led_on(hw, pled0);
		अन्यथा
			rtl8821ae_sw_led_on(hw, pled0);
		अवरोध;
	हाल LED_CTL_POWER_OFF:
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8812ae_sw_led_off(hw, pled0);
		अन्यथा
			rtl8821ae_sw_led_off(hw, pled0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl8821ae_led_control(काष्ठा ieee80211_hw *hw,
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
	rtl_dbg(rtlpriv, COMP_LED, DBG_LOUD, "ledaction %d,\n",
		ledaction);
	_rtl8821ae_sw_led_control(hw, ledaction);
पूर्ण
