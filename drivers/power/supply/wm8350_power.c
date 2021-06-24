<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery driver क्रम wm8350 PMIC
 *
 * Copyright 2007, 2008 Wolfson Microelectronics PLC.
 *
 * Based on OLPC Battery Driver
 *
 * Copyright 2006  David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mfd/wm8350/supply.h>
#समावेश <linux/mfd/wm8350/core.h>
#समावेश <linux/mfd/wm8350/comparator.h>

अटल पूर्णांक wm8350_पढ़ो_battery_uvolts(काष्ठा wm8350 *wm8350)
अणु
	वापस wm8350_पढ़ो_auxadc(wm8350, WM8350_AUXADC_BATT, 0, 0)
		* WM8350_AUX_COEFF;
पूर्ण

अटल पूर्णांक wm8350_पढ़ो_line_uvolts(काष्ठा wm8350 *wm8350)
अणु
	वापस wm8350_पढ़ो_auxadc(wm8350, WM8350_AUXADC_LINE, 0, 0)
		* WM8350_AUX_COEFF;
पूर्ण

अटल पूर्णांक wm8350_पढ़ो_usb_uvolts(काष्ठा wm8350 *wm8350)
अणु
	वापस wm8350_पढ़ो_auxadc(wm8350, WM8350_AUXADC_USB, 0, 0)
		* WM8350_AUX_COEFF;
पूर्ण

#घोषणा WM8350_BATT_SUPPLY	1
#घोषणा WM8350_USB_SUPPLY	2
#घोषणा WM8350_LINE_SUPPLY	4

अटल अंतरभूत पूर्णांक wm8350_अक्षरge_समय_min(काष्ठा wm8350 *wm8350, पूर्णांक min)
अणु
	अगर (!wm8350->घातer.rev_g_coeff)
		वापस (((min - 30) / 15) & 0xf) << 8;
	अन्यथा
		वापस (((min - 30) / 30) & 0xf) << 8;
पूर्ण

अटल पूर्णांक wm8350_get_supplies(काष्ठा wm8350 *wm8350)
अणु
	u16 sm, ov, co, chrg;
	पूर्णांक supplies = 0;

	sm = wm8350_reg_पढ़ो(wm8350, WM8350_STATE_MACHINE_STATUS);
	ov = wm8350_reg_पढ़ो(wm8350, WM8350_MISC_OVERRIDES);
	co = wm8350_reg_पढ़ो(wm8350, WM8350_COMPARATOR_OVERRIDES);
	chrg = wm8350_reg_पढ़ो(wm8350, WM8350_BATTERY_CHARGER_CONTROL_2);

	/* USB_SM */
	sm = (sm & WM8350_USB_SM_MASK) >> WM8350_USB_SM_SHIFT;

	/* CHG_ISEL */
	chrg &= WM8350_CHG_ISEL_MASK;

	/* If the USB state machine is active then we're using that with or
	 * without battery, otherwise check क्रम wall supply */
	अगर (((sm == WM8350_USB_SM_100_SLV) ||
	     (sm == WM8350_USB_SM_500_SLV) ||
	     (sm == WM8350_USB_SM_STDBY_SLV))
	    && !(ov & WM8350_USB_LIMIT_OVRDE))
		supplies = WM8350_USB_SUPPLY;
	अन्यथा अगर (((sm == WM8350_USB_SM_100_SLV) ||
		  (sm == WM8350_USB_SM_500_SLV) ||
		  (sm == WM8350_USB_SM_STDBY_SLV))
		 && (ov & WM8350_USB_LIMIT_OVRDE) && (chrg == 0))
		supplies = WM8350_USB_SUPPLY | WM8350_BATT_SUPPLY;
	अन्यथा अगर (co & WM8350_WALL_FB_OVRDE)
		supplies = WM8350_LINE_SUPPLY;
	अन्यथा
		supplies = WM8350_BATT_SUPPLY;

	वापस supplies;
पूर्ण

अटल पूर्णांक wm8350_अक्षरger_config(काष्ठा wm8350 *wm8350,
				 काष्ठा wm8350_अक्षरger_policy *policy)
अणु
	u16 reg, eoc_mA, fast_limit_mA;

	अगर (!policy) अणु
		dev_warn(wm8350->dev,
			 "No charger policy, charger not configured.\n");
		वापस -EINVAL;
	पूर्ण

	/* make sure USB fast अक्षरge current is not > 500mA */
	अगर (policy->fast_limit_USB_mA > 500) अणु
		dev_err(wm8350->dev, "USB fast charge > 500mA\n");
		वापस -EINVAL;
	पूर्ण

	eoc_mA = WM8350_CHG_EOC_mA(policy->eoc_mA);

	wm8350_reg_unlock(wm8350);

	reg = wm8350_reg_पढ़ो(wm8350, WM8350_BATTERY_CHARGER_CONTROL_1)
		& WM8350_CHG_ENA_R168;
	wm8350_reg_ग_लिखो(wm8350, WM8350_BATTERY_CHARGER_CONTROL_1,
			 reg | eoc_mA | policy->trickle_start_mV |
			 WM8350_CHG_TRICKLE_TEMP_CHOKE |
			 WM8350_CHG_TRICKLE_USB_CHOKE |
			 WM8350_CHG_FAST_USB_THROTTLE);

	अगर (wm8350_get_supplies(wm8350) & WM8350_USB_SUPPLY) अणु
		fast_limit_mA =
			WM8350_CHG_FAST_LIMIT_mA(policy->fast_limit_USB_mA);
		wm8350_reg_ग_लिखो(wm8350, WM8350_BATTERY_CHARGER_CONTROL_2,
			    policy->अक्षरge_mV | policy->trickle_अक्षरge_USB_mA |
			    fast_limit_mA | wm8350_अक्षरge_समय_min(wm8350,
						policy->अक्षरge_समयout));

	पूर्ण अन्यथा अणु
		fast_limit_mA =
			WM8350_CHG_FAST_LIMIT_mA(policy->fast_limit_mA);
		wm8350_reg_ग_लिखो(wm8350, WM8350_BATTERY_CHARGER_CONTROL_2,
			    policy->अक्षरge_mV | policy->trickle_अक्षरge_mA |
			    fast_limit_mA | wm8350_अक्षरge_समय_min(wm8350,
						policy->अक्षरge_समयout));
	पूर्ण

	wm8350_reg_lock(wm8350);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_batt_status(काष्ठा wm8350 *wm8350)
अणु
	u16 state;

	state = wm8350_reg_पढ़ो(wm8350, WM8350_BATTERY_CHARGER_CONTROL_2);
	state &= WM8350_CHG_STS_MASK;

	चयन (state) अणु
	हाल WM8350_CHG_STS_OFF:
		वापस POWER_SUPPLY_STATUS_DISCHARGING;

	हाल WM8350_CHG_STS_TRICKLE:
	हाल WM8350_CHG_STS_FAST:
		वापस POWER_SUPPLY_STATUS_CHARGING;

	शेष:
		वापस POWER_SUPPLY_STATUS_UNKNOWN;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार अक्षरger_state_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(dev);
	अक्षर *अक्षरge;
	पूर्णांक state;

	state = wm8350_reg_पढ़ो(wm8350, WM8350_BATTERY_CHARGER_CONTROL_2) &
	    WM8350_CHG_STS_MASK;
	चयन (state) अणु
	हाल WM8350_CHG_STS_OFF:
		अक्षरge = "Charger Off";
		अवरोध;
	हाल WM8350_CHG_STS_TRICKLE:
		अक्षरge = "Trickle Charging";
		अवरोध;
	हाल WM8350_CHG_STS_FAST:
		अक्षरge = "Fast Charging";
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", अक्षरge);
पूर्ण

अटल DEVICE_ATTR_RO(अक्षरger_state);

अटल irqवापस_t wm8350_अक्षरger_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm8350 *wm8350 = data;
	काष्ठा wm8350_घातer *घातer = &wm8350->घातer;
	काष्ठा wm8350_अक्षरger_policy *policy = घातer->policy;

	चयन (irq - wm8350->irq_base) अणु
	हाल WM8350_IRQ_CHG_BAT_FAIL:
		dev_err(wm8350->dev, "battery failed\n");
		अवरोध;
	हाल WM8350_IRQ_CHG_TO:
		dev_err(wm8350->dev, "charger timeout\n");
		घातer_supply_changed(घातer->battery);
		अवरोध;

	हाल WM8350_IRQ_CHG_BAT_HOT:
	हाल WM8350_IRQ_CHG_BAT_COLD:
	हाल WM8350_IRQ_CHG_START:
	हाल WM8350_IRQ_CHG_END:
		घातer_supply_changed(घातer->battery);
		अवरोध;

	हाल WM8350_IRQ_CHG_FAST_RDY:
		dev_dbg(wm8350->dev, "fast charger ready\n");
		wm8350_अक्षरger_config(wm8350, policy);
		wm8350_reg_unlock(wm8350);
		wm8350_set_bits(wm8350, WM8350_BATTERY_CHARGER_CONTROL_1,
				WM8350_CHG_FAST);
		wm8350_reg_lock(wm8350);
		अवरोध;

	हाल WM8350_IRQ_CHG_VBATT_LT_3P9:
		dev_warn(wm8350->dev, "battery < 3.9V\n");
		अवरोध;
	हाल WM8350_IRQ_CHG_VBATT_LT_3P1:
		dev_warn(wm8350->dev, "battery < 3.1V\n");
		अवरोध;
	हाल WM8350_IRQ_CHG_VBATT_LT_2P85:
		dev_warn(wm8350->dev, "battery < 2.85V\n");
		अवरोध;

		/* Supply change.  We will overnotअगरy but it should करो
		 * no harm. */
	हाल WM8350_IRQ_EXT_USB_FB:
	हाल WM8350_IRQ_EXT_WALL_FB:
		wm8350_अक्षरger_config(wm8350, policy);
		fallthrough;
	हाल WM8350_IRQ_EXT_BAT_FB:
		घातer_supply_changed(घातer->battery);
		घातer_supply_changed(घातer->usb);
		घातer_supply_changed(घातer->ac);
		अवरोध;

	शेष:
		dev_err(wm8350->dev, "Unknown interrupt %d\n", irq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*********************************************************************
 *		AC Power
 *********************************************************************/
अटल पूर्णांक wm8350_ac_get_prop(काष्ठा घातer_supply *psy,
			      क्रमागत घातer_supply_property psp,
			      जोड़ घातer_supply_propval *val)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(psy->dev.parent);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = !!(wm8350_get_supplies(wm8350) &
				 WM8350_LINE_SUPPLY);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = wm8350_पढ़ो_line_uvolts(wm8350);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property wm8350_ac_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
पूर्ण;

/*********************************************************************
 *		USB Power
 *********************************************************************/
अटल पूर्णांक wm8350_usb_get_prop(काष्ठा घातer_supply *psy,
			       क्रमागत घातer_supply_property psp,
			       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(psy->dev.parent);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = !!(wm8350_get_supplies(wm8350) &
				 WM8350_USB_SUPPLY);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = wm8350_पढ़ो_usb_uvolts(wm8350);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property wm8350_usb_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
पूर्ण;

/*********************************************************************
 *		Battery properties
 *********************************************************************/

अटल पूर्णांक wm8350_bat_check_health(काष्ठा wm8350 *wm8350)
अणु
	u16 reg;

	अगर (wm8350_पढ़ो_battery_uvolts(wm8350) < 2850000)
		वापस POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;

	reg = wm8350_reg_पढ़ो(wm8350, WM8350_CHARGER_OVERRIDES);
	अगर (reg & WM8350_CHG_BATT_HOT_OVRDE)
		वापस POWER_SUPPLY_HEALTH_OVERHEAT;

	अगर (reg & WM8350_CHG_BATT_COLD_OVRDE)
		वापस POWER_SUPPLY_HEALTH_COLD;

	वापस POWER_SUPPLY_HEALTH_GOOD;
पूर्ण

अटल पूर्णांक wm8350_bat_get_अक्षरge_type(काष्ठा wm8350 *wm8350)
अणु
	पूर्णांक state;

	state = wm8350_reg_पढ़ो(wm8350, WM8350_BATTERY_CHARGER_CONTROL_2) &
	    WM8350_CHG_STS_MASK;
	चयन (state) अणु
	हाल WM8350_CHG_STS_OFF:
		वापस POWER_SUPPLY_CHARGE_TYPE_NONE;
	हाल WM8350_CHG_STS_TRICKLE:
		वापस POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
	हाल WM8350_CHG_STS_FAST:
		वापस POWER_SUPPLY_CHARGE_TYPE_FAST;
	शेष:
		वापस POWER_SUPPLY_CHARGE_TYPE_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक wm8350_bat_get_property(काष्ठा घातer_supply *psy,
				   क्रमागत घातer_supply_property psp,
				   जोड़ घातer_supply_propval *val)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(psy->dev.parent);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = wm8350_batt_status(wm8350);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = !!(wm8350_get_supplies(wm8350) &
				 WM8350_BATT_SUPPLY);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = wm8350_पढ़ो_battery_uvolts(wm8350);
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		val->पूर्णांकval = wm8350_bat_check_health(wm8350);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		val->पूर्णांकval = wm8350_bat_get_अक्षरge_type(wm8350);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property wm8350_bat_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc wm8350_ac_desc = अणु
	.name		= "wm8350-ac",
	.type		= POWER_SUPPLY_TYPE_MAINS,
	.properties	= wm8350_ac_props,
	.num_properties	= ARRAY_SIZE(wm8350_ac_props),
	.get_property	= wm8350_ac_get_prop,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc wm8350_battery_desc = अणु
	.name		= "wm8350-battery",
	.properties	= wm8350_bat_props,
	.num_properties	= ARRAY_SIZE(wm8350_bat_props),
	.get_property	= wm8350_bat_get_property,
	.use_क्रम_apm	= 1,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc wm8350_usb_desc = अणु
	.name		= "wm8350-usb",
	.type		= POWER_SUPPLY_TYPE_USB,
	.properties	= wm8350_usb_props,
	.num_properties	= ARRAY_SIZE(wm8350_usb_props),
	.get_property	= wm8350_usb_get_prop,
पूर्ण;

/*********************************************************************
 *		Initialisation
 *********************************************************************/

अटल व्योम wm8350_init_अक्षरger(काष्ठा wm8350 *wm8350)
अणु
	/* रेजिस्टर our पूर्णांकerest in अक्षरger events */
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CHG_BAT_HOT,
			    wm8350_अक्षरger_handler, 0, "Battery hot", wm8350);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CHG_BAT_COLD,
			    wm8350_अक्षरger_handler, 0, "Battery cold", wm8350);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CHG_BAT_FAIL,
			    wm8350_अक्षरger_handler, 0, "Battery fail", wm8350);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CHG_TO,
			    wm8350_अक्षरger_handler, 0,
			    "Charger timeout", wm8350);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CHG_END,
			    wm8350_अक्षरger_handler, 0,
			    "Charge end", wm8350);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CHG_START,
			    wm8350_अक्षरger_handler, 0,
			    "Charge start", wm8350);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CHG_FAST_RDY,
			    wm8350_अक्षरger_handler, 0,
			    "Fast charge ready", wm8350);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CHG_VBATT_LT_3P9,
			    wm8350_अक्षरger_handler, 0,
			    "Battery <3.9V", wm8350);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CHG_VBATT_LT_3P1,
			    wm8350_अक्षरger_handler, 0,
			    "Battery <3.1V", wm8350);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CHG_VBATT_LT_2P85,
			    wm8350_अक्षरger_handler, 0,
			    "Battery <2.85V", wm8350);

	/* and supply change events */
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_EXT_USB_FB,
			    wm8350_अक्षरger_handler, 0, "USB", wm8350);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_EXT_WALL_FB,
			    wm8350_अक्षरger_handler, 0, "Wall", wm8350);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_EXT_BAT_FB,
			    wm8350_अक्षरger_handler, 0, "Battery", wm8350);
पूर्ण

अटल व्योम मुक्त_अक्षरger_irq(काष्ठा wm8350 *wm8350)
अणु
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CHG_BAT_HOT, wm8350);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CHG_BAT_COLD, wm8350);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CHG_BAT_FAIL, wm8350);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CHG_TO, wm8350);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CHG_END, wm8350);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CHG_START, wm8350);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CHG_VBATT_LT_3P9, wm8350);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CHG_VBATT_LT_3P1, wm8350);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CHG_VBATT_LT_2P85, wm8350);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_EXT_USB_FB, wm8350);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_EXT_WALL_FB, wm8350);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_EXT_BAT_FB, wm8350);
पूर्ण

अटल पूर्णांक wm8350_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8350 *wm8350 = platक्रमm_get_drvdata(pdev);
	काष्ठा wm8350_घातer *घातer = &wm8350->घातer;
	काष्ठा wm8350_अक्षरger_policy *policy = घातer->policy;
	पूर्णांक ret;

	घातer->ac = घातer_supply_रेजिस्टर(&pdev->dev, &wm8350_ac_desc, शून्य);
	अगर (IS_ERR(घातer->ac))
		वापस PTR_ERR(घातer->ac);

	घातer->battery = घातer_supply_रेजिस्टर(&pdev->dev, &wm8350_battery_desc,
					       शून्य);
	अगर (IS_ERR(घातer->battery)) अणु
		ret = PTR_ERR(घातer->battery);
		जाओ battery_failed;
	पूर्ण

	घातer->usb = घातer_supply_रेजिस्टर(&pdev->dev, &wm8350_usb_desc, शून्य);
	अगर (IS_ERR(घातer->usb)) अणु
		ret = PTR_ERR(घातer->usb);
		जाओ usb_failed;
	पूर्ण

	ret = device_create_file(&pdev->dev, &dev_attr_अक्षरger_state);
	अगर (ret < 0)
		dev_warn(wm8350->dev, "failed to add charge sysfs: %d\n", ret);
	ret = 0;

	wm8350_init_अक्षरger(wm8350);
	अगर (wm8350_अक्षरger_config(wm8350, policy) == 0) अणु
		wm8350_reg_unlock(wm8350);
		wm8350_set_bits(wm8350, WM8350_POWER_MGMT_5, WM8350_CHG_ENA);
		wm8350_reg_lock(wm8350);
	पूर्ण

	वापस ret;

usb_failed:
	घातer_supply_unरेजिस्टर(घातer->battery);
battery_failed:
	घातer_supply_unरेजिस्टर(घातer->ac);

	वापस ret;
पूर्ण

अटल पूर्णांक wm8350_घातer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8350 *wm8350 = platक्रमm_get_drvdata(pdev);
	काष्ठा wm8350_घातer *घातer = &wm8350->घातer;

	मुक्त_अक्षरger_irq(wm8350);
	device_हटाओ_file(&pdev->dev, &dev_attr_अक्षरger_state);
	घातer_supply_unरेजिस्टर(घातer->battery);
	घातer_supply_unरेजिस्टर(घातer->ac);
	घातer_supply_unरेजिस्टर(घातer->usb);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm8350_घातer_driver = अणु
	.probe = wm8350_घातer_probe,
	.हटाओ = wm8350_घातer_हटाओ,
	.driver = अणु
		.name = "wm8350-power",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wm8350_घातer_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Power supply driver for WM8350");
MODULE_ALIAS("platform:wm8350-power");
