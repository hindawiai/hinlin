<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MP2629 battery अक्षरger driver
 *
 * Copyright 2020 Monolithic Power Systems, Inc
 *
 * Author: Saravanan Sekar <sravanhome@gmail.com>
 */

#समावेश <linux/bits.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/mp2629.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>

#घोषणा MP2629_REG_INPUT_ILIM		0x00
#घोषणा MP2629_REG_INPUT_VLIM		0x01
#घोषणा MP2629_REG_CHARGE_CTRL		0x04
#घोषणा MP2629_REG_CHARGE_ILIM		0x05
#घोषणा MP2629_REG_PRECHARGE		0x06
#घोषणा MP2629_REG_TERM_CURRENT		0x06
#घोषणा MP2629_REG_CHARGE_VLIM		0x07
#घोषणा MP2629_REG_TIMER_CTRL		0x08
#घोषणा MP2629_REG_IMPEDANCE_COMP	0x09
#घोषणा MP2629_REG_INTERRUPT		0x0b
#घोषणा MP2629_REG_STATUS		0x0c
#घोषणा MP2629_REG_FAULT		0x0d

#घोषणा MP2629_MASK_INPUT_TYPE		GENMASK(7, 5)
#घोषणा MP2629_MASK_CHARGE_TYPE		GENMASK(4, 3)
#घोषणा MP2629_MASK_CHARGE_CTRL		GENMASK(5, 4)
#घोषणा MP2629_MASK_WDOG_CTRL		GENMASK(5, 4)
#घोषणा MP2629_MASK_IMPEDANCE		GENMASK(7, 4)

#घोषणा MP2629_INPUTSOURCE_CHANGE	GENMASK(7, 5)
#घोषणा MP2629_CHARGING_CHANGE		GENMASK(4, 3)
#घोषणा MP2629_FAULT_BATTERY		BIT(3)
#घोषणा MP2629_FAULT_THERMAL		BIT(4)
#घोषणा MP2629_FAULT_INPUT		BIT(5)
#घोषणा MP2629_FAULT_OTG		BIT(6)

#घोषणा MP2629_MAX_BATT_CAPACITY	100

#घोषणा MP2629_PROPS(_idx, _min, _max, _step)		\
	[_idx] = अणु					\
		.min	= _min,				\
		.max	= _max,				\
		.step	= _step,			\
पूर्ण

क्रमागत mp2629_source_type अणु
	MP2629_SOURCE_TYPE_NO_INPUT,
	MP2629_SOURCE_TYPE_NON_STD,
	MP2629_SOURCE_TYPE_SDP,
	MP2629_SOURCE_TYPE_CDP,
	MP2629_SOURCE_TYPE_DCP,
	MP2629_SOURCE_TYPE_OTG = 7,
पूर्ण;

क्रमागत mp2629_field अणु
	INPUT_ILIM,
	INPUT_VLIM,
	CHARGE_ILIM,
	CHARGE_VLIM,
	PRECHARGE,
	TERM_CURRENT,
	MP2629_MAX_FIELD
पूर्ण;

काष्ठा mp2629_अक्षरger अणु
	काष्ठा device *dev;
	पूर्णांक status;
	पूर्णांक fault;

	काष्ठा regmap *regmap;
	काष्ठा regmap_field *regmap_fields[MP2629_MAX_FIELD];
	काष्ठा mutex lock;
	काष्ठा घातer_supply *usb;
	काष्ठा घातer_supply *battery;
	काष्ठा iio_channel *iiochan[MP2629_ADC_CHAN_END];
पूर्ण;

काष्ठा mp2629_prop अणु
	पूर्णांक reg;
	पूर्णांक mask;
	पूर्णांक min;
	पूर्णांक max;
	पूर्णांक step;
	पूर्णांक shअगरt;
पूर्ण;

अटल क्रमागत घातer_supply_usb_type mp2629_usb_types[] = अणु
	POWER_SUPPLY_USB_TYPE_SDP,
	POWER_SUPPLY_USB_TYPE_DCP,
	POWER_SUPPLY_USB_TYPE_CDP,
	POWER_SUPPLY_USB_TYPE_PD_DRP,
	POWER_SUPPLY_USB_TYPE_UNKNOWN
पूर्ण;

अटल क्रमागत घातer_supply_property mp2629_अक्षरger_usb_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_USB_TYPE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT,
पूर्ण;

अटल क्रमागत घातer_supply_property mp2629_अक्षरger_bat_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_PRECHARGE_CURRENT,
	POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
पूर्ण;

अटल काष्ठा mp2629_prop props[] = अणु
	MP2629_PROPS(INPUT_ILIM, 100000, 3250000, 50000),
	MP2629_PROPS(INPUT_VLIM, 3800000, 5300000, 100000),
	MP2629_PROPS(CHARGE_ILIM, 320000, 4520000, 40000),
	MP2629_PROPS(CHARGE_VLIM, 3400000, 4670000, 10000),
	MP2629_PROPS(PRECHARGE, 120000, 720000, 40000),
	MP2629_PROPS(TERM_CURRENT, 80000, 680000, 40000),
पूर्ण;

अटल स्थिर काष्ठा reg_field mp2629_reg_fields[] = अणु
	[INPUT_ILIM]	= REG_FIELD(MP2629_REG_INPUT_ILIM, 0, 5),
	[INPUT_VLIM]	= REG_FIELD(MP2629_REG_INPUT_VLIM, 0, 3),
	[CHARGE_ILIM]	= REG_FIELD(MP2629_REG_CHARGE_ILIM, 0, 6),
	[CHARGE_VLIM]	= REG_FIELD(MP2629_REG_CHARGE_VLIM, 1, 7),
	[PRECHARGE]	= REG_FIELD(MP2629_REG_PRECHARGE, 4, 7),
	[TERM_CURRENT]	= REG_FIELD(MP2629_REG_TERM_CURRENT, 0, 3),
पूर्ण;

अटल अक्षर *adc_chan_name[] = अणु
	"mp2629-batt-volt",
	"mp2629-system-volt",
	"mp2629-input-volt",
	"mp2629-batt-current",
	"mp2629-input-current",
पूर्ण;

अटल पूर्णांक mp2629_पढ़ो_adc(काष्ठा mp2629_अक्षरger *अक्षरger,
			   क्रमागत mp2629_adc_chan ch,
			   जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret;
	पूर्णांक chval;

	ret = iio_पढ़ो_channel_processed(अक्षरger->iiochan[ch], &chval);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = chval * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक mp2629_get_prop(काष्ठा mp2629_अक्षरger *अक्षरger,
			   क्रमागत mp2629_field fld,
			   जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक rval;

	ret = regmap_field_पढ़ो(अक्षरger->regmap_fields[fld], &rval);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = rval * props[fld].step + props[fld].min;

	वापस 0;
पूर्ण

अटल पूर्णांक mp2629_set_prop(काष्ठा mp2629_अक्षरger *अक्षरger,
			   क्रमागत mp2629_field fld,
			   स्थिर जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक rval;

	अगर (val->पूर्णांकval < props[fld].min || val->पूर्णांकval > props[fld].max)
		वापस -EINVAL;

	rval = (val->पूर्णांकval - props[fld].min) / props[fld].step;
	वापस regmap_field_ग_लिखो(अक्षरger->regmap_fields[fld], rval);
पूर्ण

अटल पूर्णांक mp2629_get_battery_capacity(काष्ठा mp2629_अक्षरger *अक्षरger,
				       जोड़ घातer_supply_propval *val)
अणु
	जोड़ घातer_supply_propval vnow, vlim;
	पूर्णांक ret;

	ret = mp2629_पढ़ो_adc(अक्षरger, MP2629_BATT_VOLT, &vnow);
	अगर (ret)
		वापस ret;

	ret = mp2629_get_prop(अक्षरger, CHARGE_VLIM, &vlim);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = (vnow.पूर्णांकval * 100) / vlim.पूर्णांकval;
	val->पूर्णांकval = min(val->पूर्णांकval, MP2629_MAX_BATT_CAPACITY);

	वापस 0;
पूर्ण

अटल पूर्णांक mp2629_अक्षरger_battery_get_prop(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					जोड़ घातer_supply_propval *val)
अणु
	काष्ठा mp2629_अक्षरger *अक्षरger = dev_get_drvdata(psy->dev.parent);
	अचिन्हित पूर्णांक rval;
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = mp2629_पढ़ो_adc(अक्षरger, MP2629_BATT_VOLT, val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = mp2629_पढ़ो_adc(अक्षरger, MP2629_BATT_CURRENT, val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->पूर्णांकval = 4520000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		val->पूर्णांकval = 4670000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = mp2629_get_battery_capacity(अक्षरger, val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		ret = mp2629_get_prop(अक्षरger, TERM_CURRENT, val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		ret = mp2629_get_prop(अक्षरger, PRECHARGE, val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = mp2629_get_prop(अक्षरger, CHARGE_VLIM, val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = mp2629_get_prop(अक्षरger, CHARGE_ILIM, val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_HEALTH:
		अगर (!अक्षरger->fault)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		अगर (MP2629_FAULT_BATTERY & अक्षरger->fault)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		अन्यथा अगर (MP2629_FAULT_THERMAL & अक्षरger->fault)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		अन्यथा अगर (MP2629_FAULT_INPUT & अक्षरger->fault)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		अवरोध;

	हाल POWER_SUPPLY_PROP_STATUS:
		ret = regmap_पढ़ो(अक्षरger->regmap, MP2629_REG_STATUS, &rval);
		अगर (ret)
			अवरोध;

		rval = (rval & MP2629_MASK_CHARGE_TYPE) >> 3;
		चयन (rval) अणु
		हाल 0x00:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
			अवरोध;
		हाल 0x01:
		हाल 0x10:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
			अवरोध;
		हाल 0x11:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		पूर्ण
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = regmap_पढ़ो(अक्षरger->regmap, MP2629_REG_STATUS, &rval);
		अगर (ret)
			अवरोध;

		rval = (rval & MP2629_MASK_CHARGE_TYPE) >> 3;
		चयन (rval) अणु
		हाल 0x00:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_NONE;
			अवरोध;
		हाल 0x01:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
			अवरोध;
		हाल 0x10:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_STANDARD;
			अवरोध;
		शेष:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_UNKNOWN;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mp2629_अक्षरger_battery_set_prop(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा mp2629_अक्षरger *अक्षरger = dev_get_drvdata(psy->dev.parent);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		वापस mp2629_set_prop(अक्षरger, TERM_CURRENT, val);

	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		वापस mp2629_set_prop(अक्षरger, PRECHARGE, val);

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		वापस mp2629_set_prop(अक्षरger, CHARGE_VLIM, val);

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		वापस mp2629_set_prop(अक्षरger, CHARGE_ILIM, val);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mp2629_अक्षरger_usb_get_prop(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा mp2629_अक्षरger *अक्षरger = dev_get_drvdata(psy->dev.parent);
	अचिन्हित पूर्णांक rval;
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = regmap_पढ़ो(अक्षरger->regmap, MP2629_REG_STATUS, &rval);
		अगर (ret)
			अवरोध;

		val->पूर्णांकval = !!(rval & MP2629_MASK_INPUT_TYPE);
		अवरोध;

	हाल POWER_SUPPLY_PROP_USB_TYPE:
		ret = regmap_पढ़ो(अक्षरger->regmap, MP2629_REG_STATUS, &rval);
		अगर (ret)
			अवरोध;

		rval = (rval & MP2629_MASK_INPUT_TYPE) >> 5;
		चयन (rval) अणु
		हाल MP2629_SOURCE_TYPE_SDP:
			val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_SDP;
			अवरोध;
		हाल MP2629_SOURCE_TYPE_CDP:
			val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_CDP;
			अवरोध;
		हाल MP2629_SOURCE_TYPE_DCP:
			val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_DCP;
			अवरोध;
		हाल MP2629_SOURCE_TYPE_OTG:
			val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_PD_DRP;
			अवरोध;
		शेष:
			val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_UNKNOWN;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = mp2629_पढ़ो_adc(अक्षरger, MP2629_INPUT_VOLT, val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = mp2629_पढ़ो_adc(अक्षरger, MP2629_INPUT_CURRENT, val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT:
		ret = mp2629_get_prop(अक्षरger, INPUT_VLIM, val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = mp2629_get_prop(अक्षरger, INPUT_ILIM, val);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mp2629_अक्षरger_usb_set_prop(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा mp2629_अक्षरger *अक्षरger = dev_get_drvdata(psy->dev.parent);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT:
		वापस mp2629_set_prop(अक्षरger, INPUT_VLIM, val);

	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		वापस mp2629_set_prop(अक्षरger, INPUT_ILIM, val);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mp2629_अक्षरger_battery_prop_ग_लिखोable(काष्ठा घातer_supply *psy,
				     क्रमागत घातer_supply_property psp)
अणु
	वापस (psp == POWER_SUPPLY_PROP_PRECHARGE_CURRENT) ||
	       (psp == POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT) ||
	       (psp == POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT) ||
	       (psp == POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE);
पूर्ण

अटल पूर्णांक mp2629_अक्षरger_usb_prop_ग_लिखोable(काष्ठा घातer_supply *psy,
				     क्रमागत घातer_supply_property psp)
अणु
	वापस (psp == POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT) ||
	       (psp == POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT);
पूर्ण

अटल irqवापस_t mp2629_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mp2629_अक्षरger *अक्षरger = dev_id;
	अचिन्हित पूर्णांक rval;
	पूर्णांक ret;

	mutex_lock(&अक्षरger->lock);

	ret = regmap_पढ़ो(अक्षरger->regmap, MP2629_REG_FAULT, &rval);
	अगर (ret)
		जाओ unlock;

	अगर (rval) अणु
		अक्षरger->fault = rval;
		अगर (MP2629_FAULT_BATTERY & rval)
			dev_err(अक्षरger->dev, "Battery fault OVP\n");
		अन्यथा अगर (MP2629_FAULT_THERMAL & rval)
			dev_err(अक्षरger->dev, "Thermal shutdown fault\n");
		अन्यथा अगर (MP2629_FAULT_INPUT & rval)
			dev_err(अक्षरger->dev, "no input or input OVP\n");
		अन्यथा अगर (MP2629_FAULT_OTG & rval)
			dev_err(अक्षरger->dev, "VIN overloaded\n");

		जाओ unlock;
	पूर्ण

	ret = regmap_पढ़ो(अक्षरger->regmap, MP2629_REG_STATUS, &rval);
	अगर (ret)
		जाओ unlock;

	अगर (rval & MP2629_INPUTSOURCE_CHANGE)
		घातer_supply_changed(अक्षरger->usb);
	अन्यथा अगर (rval & MP2629_CHARGING_CHANGE)
		घातer_supply_changed(अक्षरger->battery);

unlock:
	mutex_unlock(&अक्षरger->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc mp2629_usb_desc = अणु
	.name		= "mp2629_usb",
	.type		= POWER_SUPPLY_TYPE_USB,
	.usb_types      = mp2629_usb_types,
	.num_usb_types  = ARRAY_SIZE(mp2629_usb_types),
	.properties	= mp2629_अक्षरger_usb_props,
	.num_properties	= ARRAY_SIZE(mp2629_अक्षरger_usb_props),
	.get_property	= mp2629_अक्षरger_usb_get_prop,
	.set_property	= mp2629_अक्षरger_usb_set_prop,
	.property_is_ग_लिखोable = mp2629_अक्षरger_usb_prop_ग_लिखोable,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc mp2629_battery_desc = अणु
	.name		= "mp2629_battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= mp2629_अक्षरger_bat_props,
	.num_properties	= ARRAY_SIZE(mp2629_अक्षरger_bat_props),
	.get_property	= mp2629_अक्षरger_battery_get_prop,
	.set_property	= mp2629_अक्षरger_battery_set_prop,
	.property_is_ग_लिखोable = mp2629_अक्षरger_battery_prop_ग_लिखोable,
पूर्ण;

अटल sमाप_प्रकार batt_impedance_compensation_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा mp2629_अक्षरger *अक्षरger = dev_get_drvdata(dev->parent);
	अचिन्हित पूर्णांक rval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(अक्षरger->regmap, MP2629_REG_IMPEDANCE_COMP, &rval);
	अगर (ret)
		वापस ret;

	rval = (rval >> 4) * 10;
	वापस प्र_लिखो(buf, "%d mohm\n", rval);
पूर्ण

अटल sमाप_प्रकार batt_impedance_compensation_store(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf,
					    माप_प्रकार count)
अणु
	काष्ठा mp2629_अक्षरger *अक्षरger = dev_get_drvdata(dev->parent);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val > 140)
		वापस -दुस्फल;

	/* multiples of 10 mohm so round off */
	val = val / 10;
	ret = regmap_update_bits(अक्षरger->regmap, MP2629_REG_IMPEDANCE_COMP,
					MP2629_MASK_IMPEDANCE, val << 4);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(batt_impedance_compensation);

अटल काष्ठा attribute *mp2629_अक्षरger_sysfs_attrs[] = अणु
	&dev_attr_batt_impedance_compensation.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(mp2629_अक्षरger_sysfs);

अटल व्योम mp2629_अक्षरger_disable(व्योम *data)
अणु
	काष्ठा mp2629_अक्षरger *अक्षरger = data;

	regmap_update_bits(अक्षरger->regmap, MP2629_REG_CHARGE_CTRL,
					MP2629_MASK_CHARGE_CTRL, 0);
पूर्ण

अटल पूर्णांक mp2629_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mp2629_data *ddata = dev_get_drvdata(dev->parent);
	काष्ठा mp2629_अक्षरger *अक्षरger;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक ret, i, irq;

	अक्षरger = devm_kzalloc(dev, माप(*अक्षरger), GFP_KERNEL);
	अगर (!अक्षरger)
		वापस -ENOMEM;

	अक्षरger->regmap = ddata->regmap;
	अक्षरger->dev = dev;
	platक्रमm_set_drvdata(pdev, अक्षरger);

	irq = platक्रमm_get_irq_optional(to_platक्रमm_device(dev->parent), 0);
	अगर (irq < 0) अणु
		dev_err(dev, "get irq fail: %d\n", irq);
		वापस irq;
	पूर्ण

	क्रम (i = 0; i < MP2629_MAX_FIELD; i++) अणु
		अक्षरger->regmap_fields[i] = devm_regmap_field_alloc(dev,
					अक्षरger->regmap, mp2629_reg_fields[i]);
		अगर (IS_ERR(अक्षरger->regmap_fields[i])) अणु
			dev_err(dev, "regmap field alloc fail %d\n", i);
			वापस PTR_ERR(अक्षरger->regmap_fields[i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MP2629_ADC_CHAN_END; i++) अणु
		अक्षरger->iiochan[i] = devm_iio_channel_get(dev,
							adc_chan_name[i]);
		अगर (IS_ERR(अक्षरger->iiochan[i])) अणु
			dev_err(dev, "iio chan get %s err\n", adc_chan_name[i]);
			वापस PTR_ERR(अक्षरger->iiochan[i]);
		पूर्ण
	पूर्ण

	ret = devm_add_action_or_reset(dev, mp2629_अक्षरger_disable, अक्षरger);
	अगर (ret)
		वापस ret;

	अक्षरger->usb = devm_घातer_supply_रेजिस्टर(dev, &mp2629_usb_desc, शून्य);
	अगर (IS_ERR(अक्षरger->usb)) अणु
		dev_err(dev, "power supply register usb failed\n");
		वापस PTR_ERR(अक्षरger->usb);
	पूर्ण

	psy_cfg.drv_data = अक्षरger;
	psy_cfg.attr_grp = mp2629_अक्षरger_sysfs_groups;
	अक्षरger->battery = devm_घातer_supply_रेजिस्टर(dev,
					 &mp2629_battery_desc, &psy_cfg);
	अगर (IS_ERR(अक्षरger->battery)) अणु
		dev_err(dev, "power supply register battery failed\n");
		वापस PTR_ERR(अक्षरger->battery);
	पूर्ण

	ret = regmap_update_bits(अक्षरger->regmap, MP2629_REG_CHARGE_CTRL,
					MP2629_MASK_CHARGE_CTRL, BIT(4));
	अगर (ret) अणु
		dev_err(dev, "enable charge fail: %d\n", ret);
		वापस ret;
	पूर्ण

	regmap_update_bits(अक्षरger->regmap, MP2629_REG_TIMER_CTRL,
					MP2629_MASK_WDOG_CTRL, 0);

	mutex_init(&अक्षरger->lock);

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,	mp2629_irq_handler,
					IRQF_ONESHOT | IRQF_TRIGGER_RISING,
					"mp2629-charger", अक्षरger);
	अगर (ret) अणु
		dev_err(dev, "failed to request gpio IRQ\n");
		वापस ret;
	पूर्ण

	regmap_update_bits(अक्षरger->regmap, MP2629_REG_INTERRUPT,
				GENMASK(6, 5), BIT(6) | BIT(5));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mp2629_अक्षरger_of_match[] = अणु
	अणु .compatible = "mps,mp2629_charger"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mp2629_अक्षरger_of_match);

अटल काष्ठा platक्रमm_driver mp2629_अक्षरger_driver = अणु
	.driver = अणु
		.name = "mp2629_charger",
		.of_match_table = mp2629_अक्षरger_of_match,
	पूर्ण,
	.probe		= mp2629_अक्षरger_probe,
पूर्ण;
module_platक्रमm_driver(mp2629_अक्षरger_driver);

MODULE_AUTHOR("Saravanan Sekar <sravanhome@gmail.com>");
MODULE_DESCRIPTION("MP2629 Charger driver");
MODULE_LICENSE("GPL");
