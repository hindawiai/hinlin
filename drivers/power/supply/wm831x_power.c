<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PMU driver क्रम Wolfson Microelectronics wm831x PMICs
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/phy.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/auxadc.h>
#समावेश <linux/mfd/wm831x/pmu.h>
#समावेश <linux/mfd/wm831x/pdata.h>

काष्ठा wm831x_घातer अणु
	काष्ठा wm831x *wm831x;
	काष्ठा घातer_supply *wall;
	काष्ठा घातer_supply *usb;
	काष्ठा घातer_supply *battery;
	काष्ठा घातer_supply_desc wall_desc;
	काष्ठा घातer_supply_desc usb_desc;
	काष्ठा घातer_supply_desc battery_desc;
	अक्षर wall_name[20];
	अक्षर usb_name[20];
	अक्षर battery_name[20];
	bool have_battery;
	काष्ठा usb_phy *usb_phy;
	काष्ठा notअगरier_block usb_notअगरy;
पूर्ण;

अटल पूर्णांक wm831x_घातer_check_online(काष्ठा wm831x *wm831x, पूर्णांक supply,
				     जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_SYSTEM_STATUS);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & supply)
		val->पूर्णांकval = 1;
	अन्यथा
		val->पूर्णांकval = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_घातer_पढ़ो_voltage(काष्ठा wm831x *wm831x,
				     क्रमागत wm831x_auxadc src,
				     जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret;

	ret = wm831x_auxadc_पढ़ो_uv(wm831x, src);
	अगर (ret >= 0)
		val->पूर्णांकval = ret;

	वापस ret;
पूर्ण

/*********************************************************************
 *		WALL Power
 *********************************************************************/
अटल पूर्णांक wm831x_wall_get_prop(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा wm831x_घातer *wm831x_घातer = dev_get_drvdata(psy->dev.parent);
	काष्ठा wm831x *wm831x = wm831x_घातer->wm831x;
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = wm831x_घातer_check_online(wm831x, WM831X_PWR_WALL, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = wm831x_घातer_पढ़ो_voltage(wm831x, WM831X_AUX_WALL, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property wm831x_wall_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
पूर्ण;

/*********************************************************************
 *		USB Power
 *********************************************************************/
अटल पूर्णांक wm831x_usb_get_prop(काष्ठा घातer_supply *psy,
			       क्रमागत घातer_supply_property psp,
			       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा wm831x_घातer *wm831x_घातer = dev_get_drvdata(psy->dev.parent);
	काष्ठा wm831x *wm831x = wm831x_घातer->wm831x;
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = wm831x_घातer_check_online(wm831x, WM831X_PWR_USB, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = wm831x_घातer_पढ़ो_voltage(wm831x, WM831X_AUX_USB, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property wm831x_usb_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
पूर्ण;

/* In milliamps */
अटल स्थिर अचिन्हित पूर्णांक wm831x_usb_limits[] = अणु
	0,
	2,
	100,
	500,
	900,
	1500,
	1800,
	550,
पूर्ण;

अटल पूर्णांक wm831x_usb_limit_change(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ limit, व्योम *data)
अणु
	काष्ठा wm831x_घातer *wm831x_घातer = container_of(nb,
							 काष्ठा wm831x_घातer,
							 usb_notअगरy);
	अचिन्हित पूर्णांक i, best;

	/* Find the highest supported limit */
	best = 0;
	क्रम (i = 0; i < ARRAY_SIZE(wm831x_usb_limits); i++) अणु
		अगर (limit >= wm831x_usb_limits[i] &&
		    wm831x_usb_limits[best] < wm831x_usb_limits[i])
			best = i;
	पूर्ण

	dev_dbg(wm831x_घातer->wm831x->dev,
		"Limiting USB current to %umA", wm831x_usb_limits[best]);

	wm831x_set_bits(wm831x_घातer->wm831x, WM831X_POWER_STATE,
		        WM831X_USB_ILIM_MASK, best);

	वापस 0;
पूर्ण

/*********************************************************************
 *		Battery properties
 *********************************************************************/

काष्ठा chg_map अणु
	पूर्णांक val;
	पूर्णांक reg_val;
पूर्ण;

अटल काष्ठा chg_map trickle_ilims[] = अणु
	अणु  50, 0 << WM831X_CHG_TRKL_ILIM_SHIFT पूर्ण,
	अणु 100, 1 << WM831X_CHG_TRKL_ILIM_SHIFT पूर्ण,
	अणु 150, 2 << WM831X_CHG_TRKL_ILIM_SHIFT पूर्ण,
	अणु 200, 3 << WM831X_CHG_TRKL_ILIM_SHIFT पूर्ण,
पूर्ण;

अटल काष्ठा chg_map vsels[] = अणु
	अणु 4050, 0 << WM831X_CHG_VSEL_SHIFT पूर्ण,
	अणु 4100, 1 << WM831X_CHG_VSEL_SHIFT पूर्ण,
	अणु 4150, 2 << WM831X_CHG_VSEL_SHIFT पूर्ण,
	अणु 4200, 3 << WM831X_CHG_VSEL_SHIFT पूर्ण,
पूर्ण;

अटल काष्ठा chg_map fast_ilims[] = अणु
	अणु    0,  0 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु   50,  1 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  100,  2 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  150,  3 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  200,  4 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  250,  5 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  300,  6 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  350,  7 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  400,  8 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  450,  9 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  500, 10 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  600, 11 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  700, 12 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  800, 13 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु  900, 14 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
	अणु 1000, 15 << WM831X_CHG_FAST_ILIM_SHIFT पूर्ण,
पूर्ण;

अटल काष्ठा chg_map eoc_iterms[] = अणु
	अणु 20, 0 << WM831X_CHG_ITERM_SHIFT पूर्ण,
	अणु 30, 1 << WM831X_CHG_ITERM_SHIFT पूर्ण,
	अणु 40, 2 << WM831X_CHG_ITERM_SHIFT पूर्ण,
	अणु 50, 3 << WM831X_CHG_ITERM_SHIFT पूर्ण,
	अणु 60, 4 << WM831X_CHG_ITERM_SHIFT पूर्ण,
	अणु 70, 5 << WM831X_CHG_ITERM_SHIFT पूर्ण,
	अणु 80, 6 << WM831X_CHG_ITERM_SHIFT पूर्ण,
	अणु 90, 7 << WM831X_CHG_ITERM_SHIFT पूर्ण,
पूर्ण;

अटल काष्ठा chg_map chg_बार[] = अणु
	अणु  60,  0 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु  90,  1 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 120,  2 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 150,  3 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 180,  4 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 210,  5 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 240,  6 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 270,  7 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 300,  8 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 330,  9 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 360, 10 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 390, 11 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 420, 12 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 450, 13 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 480, 14 << WM831X_CHG_TIME_SHIFT पूर्ण,
	अणु 510, 15 << WM831X_CHG_TIME_SHIFT पूर्ण,
पूर्ण;

अटल व्योम wm831x_battey_apply_config(काष्ठा wm831x *wm831x,
				       काष्ठा chg_map *map, पूर्णांक count, पूर्णांक val,
				       पूर्णांक *reg, स्थिर अक्षर *name,
				       स्थिर अक्षर *units)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		अगर (val == map[i].val)
			अवरोध;
	अगर (i == count) अणु
		dev_err(wm831x->dev, "Invalid %s %d%s\n",
			name, val, units);
	पूर्ण अन्यथा अणु
		*reg |= map[i].reg_val;
		dev_dbg(wm831x->dev, "Set %s of %d%s\n", name, val, units);
	पूर्ण
पूर्ण

अटल व्योम wm831x_config_battery(काष्ठा wm831x *wm831x)
अणु
	काष्ठा wm831x_pdata *wm831x_pdata = wm831x->dev->platक्रमm_data;
	काष्ठा wm831x_battery_pdata *pdata;
	पूर्णांक ret, reg1, reg2;

	अगर (!wm831x_pdata || !wm831x_pdata->battery) अणु
		dev_warn(wm831x->dev,
			 "No battery charger configuration\n");
		वापस;
	पूर्ण

	pdata = wm831x_pdata->battery;

	reg1 = 0;
	reg2 = 0;

	अगर (!pdata->enable) अणु
		dev_info(wm831x->dev, "Battery charger disabled\n");
		वापस;
	पूर्ण

	reg1 |= WM831X_CHG_ENA;
	अगर (pdata->off_mask)
		reg2 |= WM831X_CHG_OFF_MSK;
	अगर (pdata->fast_enable)
		reg1 |= WM831X_CHG_FAST;

	wm831x_battey_apply_config(wm831x, trickle_ilims,
				   ARRAY_SIZE(trickle_ilims),
				   pdata->trickle_ilim, &reg2,
				   "trickle charge current limit", "mA");

	wm831x_battey_apply_config(wm831x, vsels, ARRAY_SIZE(vsels),
				   pdata->vsel, &reg2,
				   "target voltage", "mV");

	wm831x_battey_apply_config(wm831x, fast_ilims, ARRAY_SIZE(fast_ilims),
				   pdata->fast_ilim, &reg2,
				   "fast charge current limit", "mA");

	wm831x_battey_apply_config(wm831x, eoc_iterms, ARRAY_SIZE(eoc_iterms),
				   pdata->eoc_iterm, &reg1,
				   "end of charge current threshold", "mA");

	wm831x_battey_apply_config(wm831x, chg_बार, ARRAY_SIZE(chg_बार),
				   pdata->समयout, &reg2,
				   "charger timeout", "min");

	ret = wm831x_reg_unlock(wm831x);
	अगर (ret != 0) अणु
		dev_err(wm831x->dev, "Failed to unlock registers: %d\n", ret);
		वापस;
	पूर्ण

	ret = wm831x_set_bits(wm831x, WM831X_CHARGER_CONTROL_1,
			      WM831X_CHG_ENA_MASK |
			      WM831X_CHG_FAST_MASK |
			      WM831X_CHG_ITERM_MASK,
			      reg1);
	अगर (ret != 0)
		dev_err(wm831x->dev, "Failed to set charger control 1: %d\n",
			ret);

	ret = wm831x_set_bits(wm831x, WM831X_CHARGER_CONTROL_2,
			      WM831X_CHG_OFF_MSK |
			      WM831X_CHG_TIME_MASK |
			      WM831X_CHG_FAST_ILIM_MASK |
			      WM831X_CHG_TRKL_ILIM_MASK |
			      WM831X_CHG_VSEL_MASK,
			      reg2);
	अगर (ret != 0)
		dev_err(wm831x->dev, "Failed to set charger control 2: %d\n",
			ret);

	wm831x_reg_lock(wm831x);
पूर्ण

अटल पूर्णांक wm831x_bat_check_status(काष्ठा wm831x *wm831x, पूर्णांक *status)
अणु
	पूर्णांक ret;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_SYSTEM_STATUS);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & WM831X_PWR_SRC_BATT) अणु
		*status = POWER_SUPPLY_STATUS_DISCHARGING;
		वापस 0;
	पूर्ण

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_CHARGER_STATUS);
	अगर (ret < 0)
		वापस ret;

	चयन (ret & WM831X_CHG_STATE_MASK) अणु
	हाल WM831X_CHG_STATE_OFF:
		*status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	हाल WM831X_CHG_STATE_TRICKLE:
	हाल WM831X_CHG_STATE_FAST:
		*status = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;

	शेष:
		*status = POWER_SUPPLY_STATUS_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_bat_check_type(काष्ठा wm831x *wm831x, पूर्णांक *type)
अणु
	पूर्णांक ret;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_CHARGER_STATUS);
	अगर (ret < 0)
		वापस ret;

	चयन (ret & WM831X_CHG_STATE_MASK) अणु
	हाल WM831X_CHG_STATE_TRICKLE:
	हाल WM831X_CHG_STATE_TRICKLE_OT:
		*type = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
		अवरोध;
	हाल WM831X_CHG_STATE_FAST:
	हाल WM831X_CHG_STATE_FAST_OT:
		*type = POWER_SUPPLY_CHARGE_TYPE_FAST;
		अवरोध;
	शेष:
		*type = POWER_SUPPLY_CHARGE_TYPE_NONE;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_bat_check_health(काष्ठा wm831x *wm831x, पूर्णांक *health)
अणु
	पूर्णांक ret;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_CHARGER_STATUS);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & WM831X_BATT_HOT_STS) अणु
		*health = POWER_SUPPLY_HEALTH_OVERHEAT;
		वापस 0;
	पूर्ण

	अगर (ret & WM831X_BATT_COLD_STS) अणु
		*health = POWER_SUPPLY_HEALTH_COLD;
		वापस 0;
	पूर्ण

	अगर (ret & WM831X_BATT_OV_STS) अणु
		*health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		वापस 0;
	पूर्ण

	चयन (ret & WM831X_CHG_STATE_MASK) अणु
	हाल WM831X_CHG_STATE_TRICKLE_OT:
	हाल WM831X_CHG_STATE_FAST_OT:
		*health = POWER_SUPPLY_HEALTH_OVERHEAT;
		अवरोध;
	हाल WM831X_CHG_STATE_DEFECTIVE:
		*health = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		अवरोध;
	शेष:
		*health = POWER_SUPPLY_HEALTH_GOOD;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_bat_get_prop(काष्ठा घातer_supply *psy,
			       क्रमागत घातer_supply_property psp,
			       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा wm831x_घातer *wm831x_घातer = dev_get_drvdata(psy->dev.parent);
	काष्ठा wm831x *wm831x = wm831x_घातer->wm831x;
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = wm831x_bat_check_status(wm831x, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = wm831x_घातer_check_online(wm831x, WM831X_PWR_SRC_BATT,
						val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = wm831x_घातer_पढ़ो_voltage(wm831x, WM831X_AUX_BATT, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = wm831x_bat_check_health(wm831x, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = wm831x_bat_check_type(wm831x, &val->पूर्णांकval);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property wm831x_bat_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
पूर्ण;

अटल स्थिर अक्षर *wm831x_bat_irqs[] = अणु
	"BATT HOT",
	"BATT COLD",
	"BATT FAIL",
	"OV",
	"END",
	"TO",
	"MODE",
	"START",
पूर्ण;

अटल irqवापस_t wm831x_bat_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm831x_घातer *wm831x_घातer = data;
	काष्ठा wm831x *wm831x = wm831x_घातer->wm831x;

	dev_dbg(wm831x->dev, "Battery status changed: %d\n", irq);

	/* The battery अक्षरger is स्वतःnomous so we करोn't need to करो
	 * anything except kick user space */
	अगर (wm831x_घातer->have_battery)
		घातer_supply_changed(wm831x_घातer->battery);

	वापस IRQ_HANDLED;
पूर्ण


/*********************************************************************
 *		Initialisation
 *********************************************************************/

अटल irqवापस_t wm831x_syslo_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm831x_घातer *wm831x_घातer = data;
	काष्ठा wm831x *wm831x = wm831x_घातer->wm831x;

	/* Not much we can actually *करो* but tell people क्रम
	 * posterity, we're probably about to run out of घातer. */
	dev_crit(wm831x->dev, "SYSVDD under voltage\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wm831x_pwr_src_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm831x_घातer *wm831x_घातer = data;
	काष्ठा wm831x *wm831x = wm831x_घातer->wm831x;

	dev_dbg(wm831x->dev, "Power source changed\n");

	/* Just notअगरy क्रम everything - little harm in overnotअगरying. */
	अगर (wm831x_घातer->have_battery)
		घातer_supply_changed(wm831x_घातer->battery);
	घातer_supply_changed(wm831x_घातer->usb);
	घातer_supply_changed(wm831x_घातer->wall);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wm831x_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *wm831x_pdata = wm831x->dev->platक्रमm_data;
	काष्ठा wm831x_घातer *घातer;
	पूर्णांक ret, irq, i;

	घातer = devm_kzalloc(&pdev->dev, माप(काष्ठा wm831x_घातer),
			     GFP_KERNEL);
	अगर (घातer == शून्य)
		वापस -ENOMEM;

	घातer->wm831x = wm831x;
	platक्रमm_set_drvdata(pdev, घातer);

	अगर (wm831x_pdata && wm831x_pdata->wm831x_num) अणु
		snम_लिखो(घातer->wall_name, माप(घातer->wall_name),
			 "wm831x-wall.%d", wm831x_pdata->wm831x_num);
		snम_लिखो(घातer->battery_name, माप(घातer->wall_name),
			 "wm831x-battery.%d", wm831x_pdata->wm831x_num);
		snम_लिखो(घातer->usb_name, माप(घातer->wall_name),
			 "wm831x-usb.%d", wm831x_pdata->wm831x_num);
	पूर्ण अन्यथा अणु
		snम_लिखो(घातer->wall_name, माप(घातer->wall_name),
			 "wm831x-wall");
		snम_लिखो(घातer->battery_name, माप(घातer->wall_name),
			 "wm831x-battery");
		snम_लिखो(घातer->usb_name, माप(घातer->wall_name),
			 "wm831x-usb");
	पूर्ण

	/* We ignore configuration failures since we can still पढ़ो back
	 * the status without enabling the अक्षरger.
	 */
	wm831x_config_battery(wm831x);

	घातer->wall_desc.name = घातer->wall_name;
	घातer->wall_desc.type = POWER_SUPPLY_TYPE_MAINS;
	घातer->wall_desc.properties = wm831x_wall_props;
	घातer->wall_desc.num_properties = ARRAY_SIZE(wm831x_wall_props);
	घातer->wall_desc.get_property = wm831x_wall_get_prop;
	घातer->wall = घातer_supply_रेजिस्टर(&pdev->dev, &घातer->wall_desc,
					    शून्य);
	अगर (IS_ERR(घातer->wall)) अणु
		ret = PTR_ERR(घातer->wall);
		जाओ err;
	पूर्ण

	घातer->usb_desc.name = घातer->usb_name,
	घातer->usb_desc.type = POWER_SUPPLY_TYPE_USB;
	घातer->usb_desc.properties = wm831x_usb_props;
	घातer->usb_desc.num_properties = ARRAY_SIZE(wm831x_usb_props);
	घातer->usb_desc.get_property = wm831x_usb_get_prop;
	घातer->usb = घातer_supply_रेजिस्टर(&pdev->dev, &घातer->usb_desc, शून्य);
	अगर (IS_ERR(घातer->usb)) अणु
		ret = PTR_ERR(घातer->usb);
		जाओ err_wall;
	पूर्ण

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_CHARGER_CONTROL_1);
	अगर (ret < 0)
		जाओ err_wall;
	घातer->have_battery = ret & WM831X_CHG_ENA;

	अगर (घातer->have_battery) अणु
		घातer->battery_desc.name = घातer->battery_name;
		घातer->battery_desc.properties = wm831x_bat_props;
		घातer->battery_desc.num_properties = ARRAY_SIZE(wm831x_bat_props);
		घातer->battery_desc.get_property = wm831x_bat_get_prop;
		घातer->battery_desc.use_क्रम_apm = 1;
		घातer->battery = घातer_supply_रेजिस्टर(&pdev->dev,
						       &घातer->battery_desc,
						       शून्य);
		अगर (IS_ERR(घातer->battery)) अणु
			ret = PTR_ERR(घातer->battery);
			जाओ err_usb;
		पूर्ण
	पूर्ण

	irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "SYSLO"));
	ret = request_thपढ़ोed_irq(irq, शून्य, wm831x_syslo_irq,
				   IRQF_TRIGGER_RISING | IRQF_ONESHOT, "System power low",
				   घातer);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request SYSLO IRQ %d: %d\n",
			irq, ret);
		जाओ err_battery;
	पूर्ण

	irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "PWR SRC"));
	ret = request_thपढ़ोed_irq(irq, शून्य, wm831x_pwr_src_irq,
				   IRQF_TRIGGER_RISING | IRQF_ONESHOT, "Power source",
				   घातer);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request PWR SRC IRQ %d: %d\n",
			irq, ret);
		जाओ err_syslo;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm831x_bat_irqs); i++) अणु
		irq = wm831x_irq(wm831x,
				 platक्रमm_get_irq_byname(pdev,
							 wm831x_bat_irqs[i]));
		ret = request_thपढ़ोed_irq(irq, शून्य, wm831x_bat_irq,
					   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					   wm831x_bat_irqs[i],
					   घातer);
		अगर (ret != 0) अणु
			dev_err(&pdev->dev,
				"Failed to request %s IRQ %d: %d\n",
				wm831x_bat_irqs[i], irq, ret);
			जाओ err_bat_irq;
		पूर्ण
	पूर्ण

	घातer->usb_phy = devm_usb_get_phy_by_phandle(&pdev->dev, "phys", 0);
	ret = PTR_ERR_OR_ZERO(घातer->usb_phy);

	चयन (ret) अणु
	हाल 0:
		घातer->usb_notअगरy.notअगरier_call = wm831x_usb_limit_change;
		ret = usb_रेजिस्टर_notअगरier(घातer->usb_phy, &घातer->usb_notअगरy);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Failed to register notifier: %d\n",
				ret);
			जाओ err_bat_irq;
		पूर्ण
		अवरोध;
	हाल -EINVAL:
	हाल -ENODEV:
		/* ignore missing usb-phy, it's optional */
		घातer->usb_phy = शून्य;
		ret = 0;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Failed to find USB phy: %d\n", ret);
		fallthrough;
	हाल -EPROBE_DEFER:
		जाओ err_bat_irq;
	पूर्ण

	वापस ret;

err_bat_irq:
	--i;
	क्रम (; i >= 0; i--) अणु
		irq = platक्रमm_get_irq_byname(pdev, wm831x_bat_irqs[i]);
		मुक्त_irq(irq, घातer);
	पूर्ण
	irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "PWR SRC"));
	मुक्त_irq(irq, घातer);
err_syslo:
	irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "SYSLO"));
	मुक्त_irq(irq, घातer);
err_battery:
	अगर (घातer->have_battery)
		घातer_supply_unरेजिस्टर(घातer->battery);
err_usb:
	घातer_supply_unरेजिस्टर(घातer->usb);
err_wall:
	घातer_supply_unरेजिस्टर(घातer->wall);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक wm831x_घातer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x_घातer *wm831x_घातer = platक्रमm_get_drvdata(pdev);
	काष्ठा wm831x *wm831x = wm831x_घातer->wm831x;
	पूर्णांक irq, i;

	अगर (wm831x_घातer->usb_phy) अणु
		usb_unरेजिस्टर_notअगरier(wm831x_घातer->usb_phy,
					&wm831x_घातer->usb_notअगरy);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm831x_bat_irqs); i++) अणु
		irq = wm831x_irq(wm831x, 
				 platक्रमm_get_irq_byname(pdev,
							 wm831x_bat_irqs[i]));
		मुक्त_irq(irq, wm831x_घातer);
	पूर्ण

	irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "PWR SRC"));
	मुक्त_irq(irq, wm831x_घातer);

	irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "SYSLO"));
	मुक्त_irq(irq, wm831x_घातer);

	अगर (wm831x_घातer->have_battery)
		घातer_supply_unरेजिस्टर(wm831x_घातer->battery);
	घातer_supply_unरेजिस्टर(wm831x_घातer->wall);
	घातer_supply_unरेजिस्टर(wm831x_घातer->usb);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_घातer_driver = अणु
	.probe = wm831x_घातer_probe,
	.हटाओ = wm831x_घातer_हटाओ,
	.driver = अणु
		.name = "wm831x-power",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wm831x_घातer_driver);

MODULE_DESCRIPTION("Power supply driver for WM831x PMICs");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-power");
