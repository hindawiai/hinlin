<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DA9150 Charger Driver
 *
 * Copyright (c) 2014 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/usb/phy.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/mfd/da9150/core.h>
#समावेश <linux/mfd/da9150/रेजिस्टरs.h>

/* Private data */
काष्ठा da9150_अक्षरger अणु
	काष्ठा da9150 *da9150;
	काष्ठा device *dev;

	काष्ठा घातer_supply *usb;
	काष्ठा घातer_supply *battery;
	काष्ठा घातer_supply *supply_online;

	काष्ठा usb_phy *usb_phy;
	काष्ठा notअगरier_block otg_nb;
	काष्ठा work_काष्ठा otg_work;
	अचिन्हित दीर्घ usb_event;

	काष्ठा iio_channel *ibus_chan;
	काष्ठा iio_channel *vbus_chan;
	काष्ठा iio_channel *tjunc_chan;
	काष्ठा iio_channel *vbat_chan;
पूर्ण;

अटल अंतरभूत पूर्णांक da9150_अक्षरger_supply_online(काष्ठा da9150_अक्षरger *अक्षरger,
					       काष्ठा घातer_supply *psy,
					       जोड़ घातer_supply_propval *val)
अणु
	val->पूर्णांकval = (psy == अक्षरger->supply_online) ? 1 : 0;

	वापस 0;
पूर्ण

/* Charger Properties */
अटल पूर्णांक da9150_अक्षरger_vbus_voltage_now(काष्ठा da9150_अक्षरger *अक्षरger,
					   जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक v_val, ret;

	/* Read processed value - mV units */
	ret = iio_पढ़ो_channel_processed(अक्षरger->vbus_chan, &v_val);
	अगर (ret < 0)
		वापस ret;

	/* Convert voltage to expected uV units */
	val->पूर्णांकval = v_val * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_अक्षरger_ibus_current_avg(काष्ठा da9150_अक्षरger *अक्षरger,
					   जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक i_val, ret;

	/* Read processed value - mA units */
	ret = iio_पढ़ो_channel_processed(अक्षरger->ibus_chan, &i_val);
	अगर (ret < 0)
		वापस ret;

	/* Convert current to expected uA units */
	val->पूर्णांकval = i_val * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_अक्षरger_tjunc_temp(काष्ठा da9150_अक्षरger *अक्षरger,
				     जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक t_val, ret;

	/* Read processed value - 0.001 degrees C units */
	ret = iio_पढ़ो_channel_processed(अक्षरger->tjunc_chan, &t_val);
	अगर (ret < 0)
		वापस ret;

	/* Convert temp to expect 0.1 degrees C units */
	val->पूर्णांकval = t_val / 100;

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property da9150_अक्षरger_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_TEMP,
पूर्ण;

अटल पूर्णांक da9150_अक्षरger_get_prop(काष्ठा घातer_supply *psy,
				   क्रमागत घातer_supply_property psp,
				   जोड़ घातer_supply_propval *val)
अणु
	काष्ठा da9150_अक्षरger *अक्षरger = dev_get_drvdata(psy->dev.parent);
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = da9150_अक्षरger_supply_online(अक्षरger, psy, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = da9150_अक्षरger_vbus_voltage_now(अक्षरger, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = da9150_अक्षरger_ibus_current_avg(अक्षरger, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		ret = da9150_अक्षरger_tjunc_temp(अक्षरger, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* Battery Properties */
अटल पूर्णांक da9150_अक्षरger_battery_status(काष्ठा da9150_अक्षरger *अक्षरger,
					 जोड़ घातer_supply_propval *val)
अणु
	u8 reg;

	/* Check to see अगर battery is disअक्षरging */
	reg = da9150_reg_पढ़ो(अक्षरger->da9150, DA9150_STATUS_H);

	अगर (((reg & DA9150_VBUS_STAT_MASK) == DA9150_VBUS_STAT_OFF) ||
	    ((reg & DA9150_VBUS_STAT_MASK) == DA9150_VBUS_STAT_WAIT)) अणु
		val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;

		वापस 0;
	पूर्ण

	reg = da9150_reg_पढ़ो(अक्षरger->da9150, DA9150_STATUS_J);

	/* Now check क्रम other states */
	चयन (reg & DA9150_CHG_STAT_MASK) अणु
	हाल DA9150_CHG_STAT_ACT:
	हाल DA9150_CHG_STAT_PRE:
	हाल DA9150_CHG_STAT_CC:
	हाल DA9150_CHG_STAT_CV:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	हाल DA9150_CHG_STAT_OFF:
	हाल DA9150_CHG_STAT_SUSP:
	हाल DA9150_CHG_STAT_TEMP:
	हाल DA9150_CHG_STAT_TIME:
	हाल DA9150_CHG_STAT_BAT:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	हाल DA9150_CHG_STAT_FULL:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अवरोध;
	शेष:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_अक्षरger_battery_health(काष्ठा da9150_अक्षरger *अक्षरger,
					 जोड़ घातer_supply_propval *val)
अणु
	u8 reg;

	reg = da9150_reg_पढ़ो(अक्षरger->da9150, DA9150_STATUS_J);

	/* Check अगर temperature limit reached */
	चयन (reg & DA9150_CHG_TEMP_MASK) अणु
	हाल DA9150_CHG_TEMP_UNDER:
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_COLD;
		वापस 0;
	हाल DA9150_CHG_TEMP_OVER:
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	/* Check क्रम other health states */
	चयन (reg & DA9150_CHG_STAT_MASK) अणु
	हाल DA9150_CHG_STAT_ACT:
	हाल DA9150_CHG_STAT_PRE:
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_DEAD;
		अवरोध;
	हाल DA9150_CHG_STAT_TIME:
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		अवरोध;
	शेष:
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_अक्षरger_battery_present(काष्ठा da9150_अक्षरger *अक्षरger,
					  जोड़ घातer_supply_propval *val)
अणु
	u8 reg;

	/* Check अगर battery present or हटाओd */
	reg = da9150_reg_पढ़ो(अक्षरger->da9150, DA9150_STATUS_J);
	अगर ((reg & DA9150_CHG_STAT_MASK) == DA9150_CHG_STAT_BAT)
		val->पूर्णांकval = 0;
	अन्यथा
		val->पूर्णांकval = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_अक्षरger_battery_अक्षरge_type(काष्ठा da9150_अक्षरger *अक्षरger,
					      जोड़ घातer_supply_propval *val)
अणु
	u8 reg;

	reg = da9150_reg_पढ़ो(अक्षरger->da9150, DA9150_STATUS_J);

	चयन (reg & DA9150_CHG_STAT_MASK) अणु
	हाल DA9150_CHG_STAT_CC:
		val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_FAST;
		अवरोध;
	हाल DA9150_CHG_STAT_ACT:
	हाल DA9150_CHG_STAT_PRE:
	हाल DA9150_CHG_STAT_CV:
		val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
		अवरोध;
	शेष:
		val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_NONE;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_अक्षरger_battery_voltage_min(काष्ठा da9150_अक्षरger *अक्षरger,
					      जोड़ घातer_supply_propval *val)
अणु
	u8 reg;

	reg = da9150_reg_पढ़ो(अक्षरger->da9150, DA9150_PPR_CHGCTRL_C);

	/* Value starts at 2500 mV, 50 mV increments, presented in uV */
	val->पूर्णांकval = ((reg & DA9150_CHG_VFAULT_MASK) * 50000) + 2500000;

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_अक्षरger_battery_voltage_now(काष्ठा da9150_अक्षरger *अक्षरger,
					      जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक v_val, ret;

	/* Read processed value - mV units */
	ret = iio_पढ़ो_channel_processed(अक्षरger->vbat_chan, &v_val);
	अगर (ret < 0)
		वापस ret;

	val->पूर्णांकval = v_val * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_अक्षरger_battery_current_max(काष्ठा da9150_अक्षरger *अक्षरger,
					      जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक reg;

	reg = da9150_reg_पढ़ो(अक्षरger->da9150, DA9150_PPR_CHGCTRL_D);

	/* 25mA increments */
	val->पूर्णांकval = reg * 25000;

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_अक्षरger_battery_voltage_max(काष्ठा da9150_अक्षरger *अक्षरger,
					      जोड़ घातer_supply_propval *val)
अणु
	u8 reg;

	reg = da9150_reg_पढ़ो(अक्षरger->da9150, DA9150_PPR_CHGCTRL_B);

	/* Value starts at 3650 mV, 25 mV increments, presented in uV */
	val->पूर्णांकval = ((reg & DA9150_CHG_VBAT_MASK) * 25000) + 3650000;
	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property da9150_अक्षरger_bat_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
पूर्ण;

अटल पूर्णांक da9150_अक्षरger_battery_get_prop(काष्ठा घातer_supply *psy,
					   क्रमागत घातer_supply_property psp,
					   जोड़ घातer_supply_propval *val)
अणु
	काष्ठा da9150_अक्षरger *अक्षरger = dev_get_drvdata(psy->dev.parent);
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = da9150_अक्षरger_battery_status(अक्षरger, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = da9150_अक्षरger_supply_online(अक्षरger, psy, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = da9150_अक्षरger_battery_health(अक्षरger, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		ret = da9150_अक्षरger_battery_present(अक्षरger, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = da9150_अक्षरger_battery_अक्षरge_type(अक्षरger, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		ret = da9150_अक्षरger_battery_voltage_min(अक्षरger, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = da9150_अक्षरger_battery_voltage_now(अक्षरger, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		ret = da9150_अक्षरger_battery_current_max(अक्षरger, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		ret = da9150_अक्षरger_battery_voltage_max(अक्षरger, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t da9150_अक्षरger_chg_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9150_अक्षरger *अक्षरger = data;

	घातer_supply_changed(अक्षरger->battery);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t da9150_अक्षरger_tjunc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9150_अक्षरger *अक्षरger = data;

	/* Nothing we can really करो except report this. */
	dev_crit(अक्षरger->dev, "TJunc over temperature!!!\n");
	घातer_supply_changed(अक्षरger->usb);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t da9150_अक्षरger_vfault_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9150_अक्षरger *अक्षरger = data;

	/* Nothing we can really करो except report this. */
	dev_crit(अक्षरger->dev, "VSYS under voltage!!!\n");
	घातer_supply_changed(अक्षरger->usb);
	घातer_supply_changed(अक्षरger->battery);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t da9150_अक्षरger_vbus_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9150_अक्षरger *अक्षरger = data;
	u8 reg;

	reg = da9150_reg_पढ़ो(अक्षरger->da9150, DA9150_STATUS_H);

	/* Charger plugged in or battery only */
	चयन (reg & DA9150_VBUS_STAT_MASK) अणु
	हाल DA9150_VBUS_STAT_OFF:
	हाल DA9150_VBUS_STAT_WAIT:
		अक्षरger->supply_online = अक्षरger->battery;
		अवरोध;
	हाल DA9150_VBUS_STAT_CHG:
		अक्षरger->supply_online = अक्षरger->usb;
		अवरोध;
	शेष:
		dev_warn(अक्षरger->dev, "Unknown VBUS state - reg = 0x%x\n",
			 reg);
		अक्षरger->supply_online = शून्य;
		अवरोध;
	पूर्ण

	घातer_supply_changed(अक्षरger->usb);
	घातer_supply_changed(अक्षरger->battery);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम da9150_अक्षरger_otg_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा da9150_अक्षरger *अक्षरger =
		container_of(data, काष्ठा da9150_अक्षरger, otg_work);

	चयन (अक्षरger->usb_event) अणु
	हाल USB_EVENT_ID:
		/* Enable OTG Boost */
		da9150_set_bits(अक्षरger->da9150, DA9150_PPR_BKCTRL_A,
				DA9150_VBUS_MODE_MASK, DA9150_VBUS_MODE_OTG);
		अवरोध;
	हाल USB_EVENT_NONE:
		/* Revert to अक्षरge mode */
		घातer_supply_changed(अक्षरger->usb);
		घातer_supply_changed(अक्षरger->battery);
		da9150_set_bits(अक्षरger->da9150, DA9150_PPR_BKCTRL_A,
				DA9150_VBUS_MODE_MASK, DA9150_VBUS_MODE_CHG);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक da9150_अक्षरger_otg_ncb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				  व्योम *priv)
अणु
	काष्ठा da9150_अक्षरger *अक्षरger =
		container_of(nb, काष्ठा da9150_अक्षरger, otg_nb);

	dev_dbg(अक्षरger->dev, "DA9150 OTG notify %lu\n", val);

	अक्षरger->usb_event = val;
	schedule_work(&अक्षरger->otg_work);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक da9150_अक्षरger_रेजिस्टर_irq(काष्ठा platक्रमm_device *pdev,
				       irq_handler_t handler,
				       स्थिर अक्षर *irq_name)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da9150_अक्षरger *अक्षरger = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq_byname(pdev, irq_name);
	अगर (irq < 0) अणु
		dev_err(dev, "Failed to get IRQ CHG_STATUS: %d\n", irq);
		वापस irq;
	पूर्ण

	ret = request_thपढ़ोed_irq(irq, शून्य, handler, IRQF_ONESHOT, irq_name,
				   अक्षरger);
	अगर (ret)
		dev_err(dev, "Failed to request IRQ %d: %d\n", irq, ret);

	वापस ret;
पूर्ण

अटल व्योम da9150_अक्षरger_unरेजिस्टर_irq(काष्ठा platक्रमm_device *pdev,
					  स्थिर अक्षर *irq_name)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da9150_अक्षरger *अक्षरger = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq;

	irq = platक्रमm_get_irq_byname(pdev, irq_name);
	अगर (irq < 0) अणु
		dev_err(dev, "Failed to get IRQ CHG_STATUS: %d\n", irq);
		वापस;
	पूर्ण

	मुक्त_irq(irq, अक्षरger);
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc usb_desc = अणु
	.name		= "da9150-usb",
	.type		= POWER_SUPPLY_TYPE_USB,
	.properties	= da9150_अक्षरger_props,
	.num_properties	= ARRAY_SIZE(da9150_अक्षरger_props),
	.get_property	= da9150_अक्षरger_get_prop,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc battery_desc = अणु
	.name		= "da9150-battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= da9150_अक्षरger_bat_props,
	.num_properties	= ARRAY_SIZE(da9150_अक्षरger_bat_props),
	.get_property	= da9150_अक्षरger_battery_get_prop,
पूर्ण;

अटल पूर्णांक da9150_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da9150 *da9150 = dev_get_drvdata(dev->parent);
	काष्ठा da9150_अक्षरger *अक्षरger;
	u8 reg;
	पूर्णांक ret;

	अक्षरger = devm_kzalloc(dev, माप(काष्ठा da9150_अक्षरger), GFP_KERNEL);
	अगर (!अक्षरger)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, अक्षरger);
	अक्षरger->da9150 = da9150;
	अक्षरger->dev = dev;

	/* Acquire ADC channels */
	अक्षरger->ibus_chan = iio_channel_get(dev, "CHAN_IBUS");
	अगर (IS_ERR(अक्षरger->ibus_chan)) अणु
		ret = PTR_ERR(अक्षरger->ibus_chan);
		जाओ ibus_chan_fail;
	पूर्ण

	अक्षरger->vbus_chan = iio_channel_get(dev, "CHAN_VBUS");
	अगर (IS_ERR(अक्षरger->vbus_chan)) अणु
		ret = PTR_ERR(अक्षरger->vbus_chan);
		जाओ vbus_chan_fail;
	पूर्ण

	अक्षरger->tjunc_chan = iio_channel_get(dev, "CHAN_TJUNC");
	अगर (IS_ERR(अक्षरger->tjunc_chan)) अणु
		ret = PTR_ERR(अक्षरger->tjunc_chan);
		जाओ tjunc_chan_fail;
	पूर्ण

	अक्षरger->vbat_chan = iio_channel_get(dev, "CHAN_VBAT");
	अगर (IS_ERR(अक्षरger->vbat_chan)) अणु
		ret = PTR_ERR(अक्षरger->vbat_chan);
		जाओ vbat_chan_fail;
	पूर्ण

	/* Register घातer supplies */
	अक्षरger->usb = घातer_supply_रेजिस्टर(dev, &usb_desc, शून्य);
	अगर (IS_ERR(अक्षरger->usb)) अणु
		ret = PTR_ERR(अक्षरger->usb);
		जाओ usb_fail;
	पूर्ण

	अक्षरger->battery = घातer_supply_रेजिस्टर(dev, &battery_desc, शून्य);
	अगर (IS_ERR(अक्षरger->battery)) अणु
		ret = PTR_ERR(अक्षरger->battery);
		जाओ battery_fail;
	पूर्ण

	/* Get initial online supply */
	reg = da9150_reg_पढ़ो(da9150, DA9150_STATUS_H);

	चयन (reg & DA9150_VBUS_STAT_MASK) अणु
	हाल DA9150_VBUS_STAT_OFF:
	हाल DA9150_VBUS_STAT_WAIT:
		अक्षरger->supply_online = अक्षरger->battery;
		अवरोध;
	हाल DA9150_VBUS_STAT_CHG:
		अक्षरger->supply_online = अक्षरger->usb;
		अवरोध;
	शेष:
		dev_warn(dev, "Unknown VBUS state - reg = 0x%x\n", reg);
		अक्षरger->supply_online = शून्य;
		अवरोध;
	पूर्ण

	/* Setup OTG reporting & configuration */
	अक्षरger->usb_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);
	अगर (!IS_ERR_OR_शून्य(अक्षरger->usb_phy)) अणु
		INIT_WORK(&अक्षरger->otg_work, da9150_अक्षरger_otg_work);
		अक्षरger->otg_nb.notअगरier_call = da9150_अक्षरger_otg_ncb;
		usb_रेजिस्टर_notअगरier(अक्षरger->usb_phy, &अक्षरger->otg_nb);
	पूर्ण

	/* Register IRQs */
	ret = da9150_अक्षरger_रेजिस्टर_irq(pdev, da9150_अक्षरger_chg_irq,
					  "CHG_STATUS");
	अगर (ret < 0)
		जाओ chg_irq_fail;

	ret = da9150_अक्षरger_रेजिस्टर_irq(pdev, da9150_अक्षरger_tjunc_irq,
					  "CHG_TJUNC");
	अगर (ret < 0)
		जाओ tjunc_irq_fail;

	ret = da9150_अक्षरger_रेजिस्टर_irq(pdev, da9150_अक्षरger_vfault_irq,
					  "CHG_VFAULT");
	अगर (ret < 0)
		जाओ vfault_irq_fail;

	ret = da9150_अक्षरger_रेजिस्टर_irq(pdev, da9150_अक्षरger_vbus_irq,
					  "CHG_VBUS");
	अगर (ret < 0)
		जाओ vbus_irq_fail;

	वापस 0;


vbus_irq_fail:
	da9150_अक्षरger_unरेजिस्टर_irq(pdev, "CHG_VFAULT");
vfault_irq_fail:
	da9150_अक्षरger_unरेजिस्टर_irq(pdev, "CHG_TJUNC");
tjunc_irq_fail:
	da9150_अक्षरger_unरेजिस्टर_irq(pdev, "CHG_STATUS");
chg_irq_fail:
	अगर (!IS_ERR_OR_शून्य(अक्षरger->usb_phy))
		usb_unरेजिस्टर_notअगरier(अक्षरger->usb_phy, &अक्षरger->otg_nb);
battery_fail:
	घातer_supply_unरेजिस्टर(अक्षरger->usb);

usb_fail:
	iio_channel_release(अक्षरger->vbat_chan);

vbat_chan_fail:
	iio_channel_release(अक्षरger->tjunc_chan);

tjunc_chan_fail:
	iio_channel_release(अक्षरger->vbus_chan);

vbus_chan_fail:
	iio_channel_release(अक्षरger->ibus_chan);

ibus_chan_fail:
	वापस ret;
पूर्ण

अटल पूर्णांक da9150_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9150_अक्षरger *अक्षरger = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq;

	/* Make sure IRQs are released beक्रमe unरेजिस्टरing घातer supplies */
	irq = platक्रमm_get_irq_byname(pdev, "CHG_VBUS");
	मुक्त_irq(irq, अक्षरger);

	irq = platक्रमm_get_irq_byname(pdev, "CHG_VFAULT");
	मुक्त_irq(irq, अक्षरger);

	irq = platक्रमm_get_irq_byname(pdev, "CHG_TJUNC");
	मुक्त_irq(irq, अक्षरger);

	irq = platक्रमm_get_irq_byname(pdev, "CHG_STATUS");
	मुक्त_irq(irq, अक्षरger);

	अगर (!IS_ERR_OR_शून्य(अक्षरger->usb_phy))
		usb_unरेजिस्टर_notअगरier(अक्षरger->usb_phy, &अक्षरger->otg_nb);

	घातer_supply_unरेजिस्टर(अक्षरger->battery);
	घातer_supply_unरेजिस्टर(अक्षरger->usb);

	/* Release ADC channels */
	iio_channel_release(अक्षरger->ibus_chan);
	iio_channel_release(अक्षरger->vbus_chan);
	iio_channel_release(अक्षरger->tjunc_chan);
	iio_channel_release(अक्षरger->vbat_chan);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9150_अक्षरger_driver = अणु
	.driver = अणु
		.name = "da9150-charger",
	पूर्ण,
	.probe = da9150_अक्षरger_probe,
	.हटाओ = da9150_अक्षरger_हटाओ,
पूर्ण;

module_platक्रमm_driver(da9150_अक्षरger_driver);

MODULE_DESCRIPTION("Charger Driver for DA9150");
MODULE_AUTHOR("Adam Thomson <Adam.Thomson.Opensource@diasemi.com>");
MODULE_LICENSE("GPL");
