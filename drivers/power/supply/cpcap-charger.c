<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Motorola CPCAP PMIC battery अक्षरger driver
 *
 * Copyright (C) 2017 Tony Lindgren <tony@atomide.com>
 *
 * Rewritten क्रम Linux घातer framework with some parts based on
 * on earlier driver found in the Motorola Linux kernel:
 *
 * Copyright (C) 2009-2010 Motorola, Inc.
 */

#समावेश <linux/atomic.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/usb/phy_companion.h>
#समावेश <linux/phy/omap_usb.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/mfd/motorola-cpcap.h>

/*
 * CPCAP_REG_CRM रेजिस्टर bits. For करोcumentation of somewhat similar hardware,
 * see NXP "MC13783 Power Management and Audio Circuit Users's Guide"
 * MC13783UG.pdf chapter "8.5 Battery Interface Register Summary". The रेजिस्टरs
 * and values क्रम CPCAP are dअगरferent, but some of the पूर्णांकernal components seem
 * similar. Also see the Motorola Linux kernel cpcap-regbits.h. CPCAP_REG_CHRGR_1
 * bits that seem to describe the CRM रेजिस्टर.
 */
#घोषणा CPCAP_REG_CRM_UNUSED_641_15	BIT(15)	/* 641 = रेजिस्टर number */
#घोषणा CPCAP_REG_CRM_UNUSED_641_14	BIT(14)	/* 641 = रेजिस्टर number */
#घोषणा CPCAP_REG_CRM_CHRG_LED_EN	BIT(13)	/* Charger LED */
#घोषणा CPCAP_REG_CRM_RVRSMODE		BIT(12)	/* USB VBUS output enable */
#घोषणा CPCAP_REG_CRM_ICHRG_TR1		BIT(11)	/* Trickle अक्षरge current */
#घोषणा CPCAP_REG_CRM_ICHRG_TR0		BIT(10)
#घोषणा CPCAP_REG_CRM_FET_OVRD		BIT(9)	/* 0 = hardware, 1 = FET_CTRL */
#घोषणा CPCAP_REG_CRM_FET_CTRL		BIT(8)	/* BPFET 1 अगर FET_OVRD set */
#घोषणा CPCAP_REG_CRM_VCHRG3		BIT(7)	/* Charge voltage bits */
#घोषणा CPCAP_REG_CRM_VCHRG2		BIT(6)
#घोषणा CPCAP_REG_CRM_VCHRG1		BIT(5)
#घोषणा CPCAP_REG_CRM_VCHRG0		BIT(4)
#घोषणा CPCAP_REG_CRM_ICHRG3		BIT(3)	/* Charge current bits */
#घोषणा CPCAP_REG_CRM_ICHRG2		BIT(2)
#घोषणा CPCAP_REG_CRM_ICHRG1		BIT(1)
#घोषणा CPCAP_REG_CRM_ICHRG0		BIT(0)

/* CPCAP_REG_CRM trickle अक्षरge voltages */
#घोषणा CPCAP_REG_CRM_TR(val)		(((val) & 0x3) << 10)
#घोषणा CPCAP_REG_CRM_TR_0A00		CPCAP_REG_CRM_TR(0x0)
#घोषणा CPCAP_REG_CRM_TR_0A24		CPCAP_REG_CRM_TR(0x1)
#घोषणा CPCAP_REG_CRM_TR_0A48		CPCAP_REG_CRM_TR(0x2)
#घोषणा CPCAP_REG_CRM_TR_0A72		CPCAP_REG_CRM_TR(0x4)

/*
 * CPCAP_REG_CRM अक्षरge voltages based on the ADC channel 1 values.
 * Note that these रेजिस्टर bits करोn't match MC13783UG.pdf VCHRG
 * रेजिस्टर bits.
 */
#घोषणा CPCAP_REG_CRM_VCHRG(val)	(((val) & 0xf) << 4)
#घोषणा CPCAP_REG_CRM_VCHRG_3V80	CPCAP_REG_CRM_VCHRG(0x0)
#घोषणा CPCAP_REG_CRM_VCHRG_4V10	CPCAP_REG_CRM_VCHRG(0x1)
#घोषणा CPCAP_REG_CRM_VCHRG_4V12	CPCAP_REG_CRM_VCHRG(0x2)
#घोषणा CPCAP_REG_CRM_VCHRG_4V15	CPCAP_REG_CRM_VCHRG(0x3)
#घोषणा CPCAP_REG_CRM_VCHRG_4V17	CPCAP_REG_CRM_VCHRG(0x4)
#घोषणा CPCAP_REG_CRM_VCHRG_4V20	CPCAP_REG_CRM_VCHRG(0x5)
#घोषणा CPCAP_REG_CRM_VCHRG_4V23	CPCAP_REG_CRM_VCHRG(0x6)
#घोषणा CPCAP_REG_CRM_VCHRG_4V25	CPCAP_REG_CRM_VCHRG(0x7)
#घोषणा CPCAP_REG_CRM_VCHRG_4V27	CPCAP_REG_CRM_VCHRG(0x8)
#घोषणा CPCAP_REG_CRM_VCHRG_4V30	CPCAP_REG_CRM_VCHRG(0x9)
#घोषणा CPCAP_REG_CRM_VCHRG_4V33	CPCAP_REG_CRM_VCHRG(0xa)
#घोषणा CPCAP_REG_CRM_VCHRG_4V35	CPCAP_REG_CRM_VCHRG(0xb)
#घोषणा CPCAP_REG_CRM_VCHRG_4V38	CPCAP_REG_CRM_VCHRG(0xc)
#घोषणा CPCAP_REG_CRM_VCHRG_4V40	CPCAP_REG_CRM_VCHRG(0xd)
#घोषणा CPCAP_REG_CRM_VCHRG_4V42	CPCAP_REG_CRM_VCHRG(0xe)
#घोषणा CPCAP_REG_CRM_VCHRG_4V44	CPCAP_REG_CRM_VCHRG(0xf)

/*
 * CPCAP_REG_CRM अक्षरge currents. These seem to match MC13783UG.pdf
 * values in "Table 8-3. Charge Path Regulator Current Limit
 * Characteristics" क्रम the nominal values.
 *
 * Except 70mA and 1.596A and unlimited, these are simply 88.7mA / step.
 */
#घोषणा CPCAP_REG_CRM_ICHRG(val)	(((val) & 0xf) << 0)
#घोषणा CPCAP_REG_CRM_ICHRG_0A000	CPCAP_REG_CRM_ICHRG(0x0)
#घोषणा CPCAP_REG_CRM_ICHRG_0A070	CPCAP_REG_CRM_ICHRG(0x1)
#घोषणा CPCAP_REG_CRM_ICHRG_0A177	CPCAP_REG_CRM_ICHRG(0x2)
#घोषणा CPCAP_REG_CRM_ICHRG_0A266	CPCAP_REG_CRM_ICHRG(0x3)
#घोषणा CPCAP_REG_CRM_ICHRG_0A355	CPCAP_REG_CRM_ICHRG(0x4)
#घोषणा CPCAP_REG_CRM_ICHRG_0A443	CPCAP_REG_CRM_ICHRG(0x5)
#घोषणा CPCAP_REG_CRM_ICHRG_0A532	CPCAP_REG_CRM_ICHRG(0x6)
#घोषणा CPCAP_REG_CRM_ICHRG_0A621	CPCAP_REG_CRM_ICHRG(0x7)
#घोषणा CPCAP_REG_CRM_ICHRG_0A709	CPCAP_REG_CRM_ICHRG(0x8)
#घोषणा CPCAP_REG_CRM_ICHRG_0A798	CPCAP_REG_CRM_ICHRG(0x9)
#घोषणा CPCAP_REG_CRM_ICHRG_0A886	CPCAP_REG_CRM_ICHRG(0xa)
#घोषणा CPCAP_REG_CRM_ICHRG_0A975	CPCAP_REG_CRM_ICHRG(0xb)
#घोषणा CPCAP_REG_CRM_ICHRG_1A064	CPCAP_REG_CRM_ICHRG(0xc)
#घोषणा CPCAP_REG_CRM_ICHRG_1A152	CPCAP_REG_CRM_ICHRG(0xd)
#घोषणा CPCAP_REG_CRM_ICHRG_1A596	CPCAP_REG_CRM_ICHRG(0xe)
#घोषणा CPCAP_REG_CRM_ICHRG_NO_LIMIT	CPCAP_REG_CRM_ICHRG(0xf)

/* CPCAP_REG_VUSBC रेजिस्टर bits needed क्रम VBUS */
#घोषणा CPCAP_BIT_VBUS_SWITCH		BIT(0)	/* VBUS boost to 5V */

क्रमागत अणु
	CPCAP_CHARGER_IIO_BATTDET,
	CPCAP_CHARGER_IIO_VOLTAGE,
	CPCAP_CHARGER_IIO_VBUS,
	CPCAP_CHARGER_IIO_CHRG_CURRENT,
	CPCAP_CHARGER_IIO_BATT_CURRENT,
	CPCAP_CHARGER_IIO_NR,
पूर्ण;

काष्ठा cpcap_अक्षरger_ddata अणु
	काष्ठा device *dev;
	काष्ठा regmap *reg;
	काष्ठा list_head irq_list;
	काष्ठा delayed_work detect_work;
	काष्ठा delayed_work vbus_work;
	काष्ठा gpio_desc *gpio[2];		/* gpio_reven0 & 1 */

	काष्ठा iio_channel *channels[CPCAP_CHARGER_IIO_NR];

	काष्ठा घातer_supply *usb;

	काष्ठा phy_companion comparator;	/* For USB VBUS */
	अचिन्हित पूर्णांक vbus_enabled:1;
	अचिन्हित पूर्णांक feeding_vbus:1;
	atomic_t active;

	पूर्णांक status;
	पूर्णांक voltage;
	पूर्णांक limit_current;
पूर्ण;

काष्ठा cpcap_पूर्णांकerrupt_desc अणु
	पूर्णांक irq;
	काष्ठा list_head node;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा cpcap_अक्षरger_पूर्णांकs_state अणु
	bool chrg_det;
	bool rvrs_chrg;
	bool vbusov;

	bool chrg_se1b;
	bool rvrs_mode;
	bool chrgcurr2;
	bool chrgcurr1;
	bool vbusvld;

	bool battdetb;
पूर्ण;

अटल क्रमागत घातer_supply_property cpcap_अक्षरger_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
पूर्ण;

/* No battery always shows temperature of -40000 */
अटल bool cpcap_अक्षरger_battery_found(काष्ठा cpcap_अक्षरger_ddata *ddata)
अणु
	काष्ठा iio_channel *channel;
	पूर्णांक error, temperature;

	channel = ddata->channels[CPCAP_CHARGER_IIO_BATTDET];
	error = iio_पढ़ो_channel_processed(channel, &temperature);
	अगर (error < 0) अणु
		dev_warn(ddata->dev, "%s failed: %i\n", __func__, error);

		वापस false;
	पूर्ण

	वापस temperature > -20000 && temperature < 60000;
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_get_अक्षरge_voltage(काष्ठा cpcap_अक्षरger_ddata *ddata)
अणु
	काष्ठा iio_channel *channel;
	पूर्णांक error, value = 0;

	channel = ddata->channels[CPCAP_CHARGER_IIO_VOLTAGE];
	error = iio_पढ़ो_channel_processed(channel, &value);
	अगर (error < 0) अणु
		dev_warn(ddata->dev, "%s failed: %i\n", __func__, error);

		वापस 0;
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_get_अक्षरge_current(काष्ठा cpcap_अक्षरger_ddata *ddata)
अणु
	काष्ठा iio_channel *channel;
	पूर्णांक error, value = 0;

	channel = ddata->channels[CPCAP_CHARGER_IIO_CHRG_CURRENT];
	error = iio_पढ़ो_channel_processed(channel, &value);
	अगर (error < 0) अणु
		dev_warn(ddata->dev, "%s failed: %i\n", __func__, error);

		वापस 0;
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_get_property(काष्ठा घातer_supply *psy,
				      क्रमागत घातer_supply_property psp,
				      जोड़ घातer_supply_propval *val)
अणु
	काष्ठा cpcap_अक्षरger_ddata *ddata = dev_get_drvdata(psy->dev.parent);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = ddata->status;
		अवरोध;
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		val->पूर्णांकval = ddata->limit_current;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		val->पूर्णांकval = ddata->voltage;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		अगर (ddata->status == POWER_SUPPLY_STATUS_CHARGING)
			val->पूर्णांकval = cpcap_अक्षरger_get_अक्षरge_voltage(ddata) *
				1000;
		अन्यथा
			val->पूर्णांकval = 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		अगर (ddata->status == POWER_SUPPLY_STATUS_CHARGING)
			val->पूर्णांकval = cpcap_अक्षरger_get_अक्षरge_current(ddata) *
				1000;
		अन्यथा
			val->पूर्णांकval = 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = ddata->status == POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_match_voltage(पूर्णांक voltage)
अणु
	चयन (voltage) अणु
	हाल 0 ... 4100000 - 1: वापस 3800000;
	हाल 4100000 ... 4120000 - 1: वापस 4100000;
	हाल 4120000 ... 4150000 - 1: वापस 4120000;
	हाल 4150000 ... 4170000 - 1: वापस 4150000;
	हाल 4170000 ... 4200000 - 1: वापस 4170000;
	हाल 4200000 ... 4230000 - 1: वापस 4200000;
	हाल 4230000 ... 4250000 - 1: वापस 4230000;
	हाल 4250000 ... 4270000 - 1: वापस 4250000;
	हाल 4270000 ... 4300000 - 1: वापस 4270000;
	हाल 4300000 ... 4330000 - 1: वापस 4300000;
	हाल 4330000 ... 4350000 - 1: वापस 4330000;
	हाल 4350000 ... 4380000 - 1: वापस 4350000;
	हाल 4380000 ... 4400000 - 1: वापस 4380000;
	हाल 4400000 ... 4420000 - 1: वापस 4400000;
	हाल 4420000 ... 4440000 - 1: वापस 4420000;
	हाल 4440000: वापस 4440000;
	शेष: वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
cpcap_अक्षरger_get_bat_स्थिर_अक्षरge_voltage(काष्ठा cpcap_अक्षरger_ddata *ddata)
अणु
	जोड़ घातer_supply_propval prop;
	काष्ठा घातer_supply *battery;
	पूर्णांक voltage = ddata->voltage;
	पूर्णांक error;

	battery = घातer_supply_get_by_name("battery");
	अगर (battery) अणु
		error = घातer_supply_get_property(battery,
				POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
				&prop);
		अगर (!error)
			voltage = prop.पूर्णांकval;

		घातer_supply_put(battery);
	पूर्ण

	वापस voltage;
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_current_to_regval(पूर्णांक microamp)
अणु
	पूर्णांक miliamp = microamp / 1000;
	पूर्णांक res;

	अगर (miliamp < 0)
		वापस -EINVAL;
	अगर (miliamp < 70)
		वापस CPCAP_REG_CRM_ICHRG(0x0);
	अगर (miliamp < 177)
		वापस CPCAP_REG_CRM_ICHRG(0x1);
	अगर (miliamp >= 1596)
		वापस CPCAP_REG_CRM_ICHRG(0xe);

	res = microamp / 88666;
	अगर (res > 0xd)
		res = 0xd;
	वापस CPCAP_REG_CRM_ICHRG(res);
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_set_property(काष्ठा घातer_supply *psy,
				      क्रमागत घातer_supply_property psp,
				      स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा cpcap_अक्षरger_ddata *ddata = dev_get_drvdata(psy->dev.parent);
	पूर्णांक voltage, batvolt;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		अगर (cpcap_अक्षरger_current_to_regval(val->पूर्णांकval) < 0)
			वापस -EINVAL;
		ddata->limit_current = val->पूर्णांकval;
		schedule_delayed_work(&ddata->detect_work, 0);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		voltage = cpcap_अक्षरger_match_voltage(val->पूर्णांकval);
		batvolt = cpcap_अक्षरger_get_bat_स्थिर_अक्षरge_voltage(ddata);
		अगर (voltage > batvolt)
			voltage = batvolt;
		ddata->voltage = voltage;
		schedule_delayed_work(&ddata->detect_work, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
					       क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम cpcap_अक्षरger_set_cable_path(काष्ठा cpcap_अक्षरger_ddata *ddata,
					 bool enabled)
अणु
	अगर (!ddata->gpio[0])
		वापस;

	gpiod_set_value(ddata->gpio[0], enabled);
पूर्ण

अटल व्योम cpcap_अक्षरger_set_inductive_path(काष्ठा cpcap_अक्षरger_ddata *ddata,
					     bool enabled)
अणु
	अगर (!ddata->gpio[1])
		वापस;

	gpiod_set_value(ddata->gpio[1], enabled);
पूर्ण

अटल व्योम cpcap_अक्षरger_update_state(काष्ठा cpcap_अक्षरger_ddata *ddata,
				       पूर्णांक state)
अणु
	स्थिर अक्षर *status;

	अगर (state > POWER_SUPPLY_STATUS_FULL) अणु
		dev_warn(ddata->dev, "unknown state: %i\n", state);

		वापस;
	पूर्ण

	ddata->status = state;

	चयन (state) अणु
	हाल POWER_SUPPLY_STATUS_DISCHARGING:
		status = "DISCONNECTED";
		अवरोध;
	हाल POWER_SUPPLY_STATUS_NOT_CHARGING:
		status = "DETECTING";
		अवरोध;
	हाल POWER_SUPPLY_STATUS_CHARGING:
		status = "CHARGING";
		अवरोध;
	हाल POWER_SUPPLY_STATUS_FULL:
		status = "DONE";
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	dev_dbg(ddata->dev, "state: %s\n", status);
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_disable(काष्ठा cpcap_अक्षरger_ddata *ddata)
अणु
	पूर्णांक error;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_CRM, 0x3fff,
				   CPCAP_REG_CRM_FET_OVRD |
				   CPCAP_REG_CRM_FET_CTRL);
	अगर (error)
		dev_err(ddata->dev, "%s failed with %i\n", __func__, error);

	वापस error;
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_enable(काष्ठा cpcap_अक्षरger_ddata *ddata,
				पूर्णांक max_voltage, पूर्णांक अक्षरge_current,
				पूर्णांक trickle_current)
अणु
	पूर्णांक error;

	अगर (!max_voltage || !अक्षरge_current)
		वापस -EINVAL;

	dev_dbg(ddata->dev, "enable: %i %i %i\n",
		max_voltage, अक्षरge_current, trickle_current);

	error = regmap_update_bits(ddata->reg, CPCAP_REG_CRM, 0x3fff,
				   CPCAP_REG_CRM_CHRG_LED_EN |
				   trickle_current |
				   CPCAP_REG_CRM_FET_OVRD |
				   CPCAP_REG_CRM_FET_CTRL |
				   max_voltage |
				   अक्षरge_current);
	अगर (error)
		dev_err(ddata->dev, "%s failed with %i\n", __func__, error);

	वापस error;
पूर्ण

अटल bool cpcap_अक्षरger_vbus_valid(काष्ठा cpcap_अक्षरger_ddata *ddata)
अणु
	पूर्णांक error, value = 0;
	काष्ठा iio_channel *channel =
		ddata->channels[CPCAP_CHARGER_IIO_VBUS];

	error = iio_पढ़ो_channel_processed(channel, &value);
	अगर (error >= 0)
		वापस value > 3900;

	dev_err(ddata->dev, "error reading VBUS: %i\n", error);

	वापस false;
पूर्ण

/* VBUS control functions क्रम the USB PHY companion */
अटल व्योम cpcap_अक्षरger_vbus_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cpcap_अक्षरger_ddata *ddata;
	bool vbus = false;
	पूर्णांक error;

	ddata = container_of(work, काष्ठा cpcap_अक्षरger_ddata,
			     vbus_work.work);

	अगर (ddata->vbus_enabled) अणु
		vbus = cpcap_अक्षरger_vbus_valid(ddata);
		अगर (vbus) अणु
			dev_dbg(ddata->dev, "VBUS already provided\n");

			वापस;
		पूर्ण

		ddata->feeding_vbus = true;
		cpcap_अक्षरger_set_cable_path(ddata, false);
		cpcap_अक्षरger_set_inductive_path(ddata, false);

		error = cpcap_अक्षरger_disable(ddata);
		अगर (error)
			जाओ out_err;

		cpcap_अक्षरger_update_state(ddata,
					   POWER_SUPPLY_STATUS_DISCHARGING);

		error = regmap_update_bits(ddata->reg, CPCAP_REG_VUSBC,
					   CPCAP_BIT_VBUS_SWITCH,
					   CPCAP_BIT_VBUS_SWITCH);
		अगर (error)
			जाओ out_err;

		error = regmap_update_bits(ddata->reg, CPCAP_REG_CRM,
					   CPCAP_REG_CRM_RVRSMODE,
					   CPCAP_REG_CRM_RVRSMODE);
		अगर (error)
			जाओ out_err;
	पूर्ण अन्यथा अणु
		error = regmap_update_bits(ddata->reg, CPCAP_REG_VUSBC,
					   CPCAP_BIT_VBUS_SWITCH, 0);
		अगर (error)
			जाओ out_err;

		error = regmap_update_bits(ddata->reg, CPCAP_REG_CRM,
					   CPCAP_REG_CRM_RVRSMODE, 0);
		अगर (error)
			जाओ out_err;

		cpcap_अक्षरger_set_cable_path(ddata, true);
		cpcap_अक्षरger_set_inductive_path(ddata, true);
		ddata->feeding_vbus = false;
	पूर्ण

	वापस;

out_err:
	cpcap_अक्षरger_update_state(ddata, POWER_SUPPLY_STATUS_UNKNOWN);
	dev_err(ddata->dev, "%s could not %s vbus: %i\n", __func__,
		ddata->vbus_enabled ? "enable" : "disable", error);
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_set_vbus(काष्ठा phy_companion *comparator,
				  bool enabled)
अणु
	काष्ठा cpcap_अक्षरger_ddata *ddata =
		container_of(comparator, काष्ठा cpcap_अक्षरger_ddata,
			     comparator);

	ddata->vbus_enabled = enabled;
	schedule_delayed_work(&ddata->vbus_work, 0);

	वापस 0;
पूर्ण

/* Charger पूर्णांकerrupt handling functions */

अटल पूर्णांक cpcap_अक्षरger_get_पूर्णांकs_state(काष्ठा cpcap_अक्षरger_ddata *ddata,
					काष्ठा cpcap_अक्षरger_पूर्णांकs_state *s)
अणु
	पूर्णांक val, error;

	error = regmap_पढ़ो(ddata->reg, CPCAP_REG_INTS1, &val);
	अगर (error)
		वापस error;

	s->chrg_det = val & BIT(13);
	s->rvrs_chrg = val & BIT(12);
	s->vbusov = val & BIT(11);

	error = regmap_पढ़ो(ddata->reg, CPCAP_REG_INTS2, &val);
	अगर (error)
		वापस error;

	s->chrg_se1b = val & BIT(13);
	s->rvrs_mode = val & BIT(6);
	s->chrgcurr2 = val & BIT(5);
	s->chrgcurr1 = val & BIT(4);
	s->vbusvld = val & BIT(3);

	error = regmap_पढ़ो(ddata->reg, CPCAP_REG_INTS4, &val);
	अगर (error)
		वापस error;

	s->battdetb = val & BIT(6);

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_voltage_to_regval(पूर्णांक voltage)
अणु
	पूर्णांक offset;

	चयन (voltage) अणु
	हाल 0 ... 4100000 - 1:
		वापस 0;
	हाल 4100000 ... 4200000 - 1:
		offset = 1;
		अवरोध;
	हाल 4200000 ... 4300000 - 1:
		offset = 0;
		अवरोध;
	हाल 4300000 ... 4380000 - 1:
		offset = -1;
		अवरोध;
	हाल 4380000 ... 4440000:
		offset = -2;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस ((voltage - 4100000) / 20000) + offset;
पूर्ण

अटल व्योम cpcap_अक्षरger_disconnect(काष्ठा cpcap_अक्षरger_ddata *ddata,
				     पूर्णांक state, अचिन्हित दीर्घ delay)
अणु
	पूर्णांक error;

	/* Update battery state beक्रमe disconnecting the अक्षरger */
	चयन (state) अणु
	हाल POWER_SUPPLY_STATUS_DISCHARGING:
	हाल POWER_SUPPLY_STATUS_FULL:
		घातer_supply_changed(ddata->usb);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	error = cpcap_अक्षरger_disable(ddata);
	अगर (error) अणु
		cpcap_अक्षरger_update_state(ddata, POWER_SUPPLY_STATUS_UNKNOWN);
		वापस;
	पूर्ण

	cpcap_अक्षरger_update_state(ddata, state);
	घातer_supply_changed(ddata->usb);
	schedule_delayed_work(&ddata->detect_work, delay);
पूर्ण

अटल व्योम cpcap_usb_detect(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cpcap_अक्षरger_ddata *ddata;
	काष्ठा cpcap_अक्षरger_पूर्णांकs_state s;
	पूर्णांक error, new_state;

	ddata = container_of(work, काष्ठा cpcap_अक्षरger_ddata,
			     detect_work.work);

	error = cpcap_अक्षरger_get_पूर्णांकs_state(ddata, &s);
	अगर (error)
		वापस;

	/* Just init the state अगर a अक्षरger is connected with no chrg_det set */
	अगर (!s.chrg_det && s.chrgcurr1 && s.vbusvld) अणु
		cpcap_अक्षरger_update_state(ddata,
					   POWER_SUPPLY_STATUS_NOT_CHARGING);

		वापस;
	पूर्ण

	/*
	 * If battery voltage is higher than अक्षरge voltage, it may have been
	 * अक्षरged to 4.35V by Android. Try again in 10 minutes.
	 */
	अगर (cpcap_अक्षरger_get_अक्षरge_voltage(ddata) > ddata->voltage) अणु
		cpcap_अक्षरger_disconnect(ddata,
					 POWER_SUPPLY_STATUS_NOT_CHARGING,
					 HZ * 60 * 10);

		वापस;
	पूर्ण

	/* Delay क्रम 80ms to aव्योम vbus bouncing when usb cable is plugged in */
	usleep_range(80000, 120000);

	/* Throttle chrgcurr2 पूर्णांकerrupt क्रम अक्षरger करोne and retry */
	चयन (ddata->status) अणु
	हाल POWER_SUPPLY_STATUS_CHARGING:
		अगर (s.chrgcurr2)
			अवरोध;
		new_state = POWER_SUPPLY_STATUS_FULL;

		अगर (s.chrgcurr1 && s.vbusvld) अणु
			cpcap_अक्षरger_disconnect(ddata, new_state, HZ * 5);
			वापस;
		पूर्ण
		अवरोध;
	हाल POWER_SUPPLY_STATUS_FULL:
		अगर (!s.chrgcurr2)
			अवरोध;
		अगर (s.vbusvld)
			new_state = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अन्यथा
			new_state = POWER_SUPPLY_STATUS_DISCHARGING;

		cpcap_अक्षरger_disconnect(ddata, new_state, HZ * 5);

		वापस;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!ddata->feeding_vbus && cpcap_अक्षरger_vbus_valid(ddata) &&
	    s.chrgcurr1) अणु
		पूर्णांक max_current = 532000;
		पूर्णांक vchrg, ichrg;

		अगर (cpcap_अक्षरger_battery_found(ddata))
			max_current = 1596000;

		अगर (max_current > ddata->limit_current)
			max_current = ddata->limit_current;

		ichrg = cpcap_अक्षरger_current_to_regval(max_current);
		vchrg = cpcap_अक्षरger_voltage_to_regval(ddata->voltage);
		error = cpcap_अक्षरger_enable(ddata,
					     CPCAP_REG_CRM_VCHRG(vchrg),
					     ichrg, 0);
		अगर (error)
			जाओ out_err;
		cpcap_अक्षरger_update_state(ddata,
					   POWER_SUPPLY_STATUS_CHARGING);
	पूर्ण अन्यथा अणु
		error = cpcap_अक्षरger_disable(ddata);
		अगर (error)
			जाओ out_err;
		cpcap_अक्षरger_update_state(ddata,
					   POWER_SUPPLY_STATUS_DISCHARGING);
	पूर्ण

	घातer_supply_changed(ddata->usb);
	वापस;

out_err:
	cpcap_अक्षरger_update_state(ddata, POWER_SUPPLY_STATUS_UNKNOWN);
	dev_err(ddata->dev, "%s failed with %i\n", __func__, error);
पूर्ण

अटल irqवापस_t cpcap_अक्षरger_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cpcap_अक्षरger_ddata *ddata = data;

	अगर (!atomic_पढ़ो(&ddata->active))
		वापस IRQ_NONE;

	schedule_delayed_work(&ddata->detect_work, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cpcap_usb_init_irq(काष्ठा platक्रमm_device *pdev,
			      काष्ठा cpcap_अक्षरger_ddata *ddata,
			      स्थिर अक्षर *name)
अणु
	काष्ठा cpcap_पूर्णांकerrupt_desc *d;
	पूर्णांक irq, error;

	irq = platक्रमm_get_irq_byname(pdev, name);
	अगर (irq < 0)
		वापस -ENODEV;

	error = devm_request_thपढ़ोed_irq(ddata->dev, irq, शून्य,
					  cpcap_अक्षरger_irq_thपढ़ो,
					  IRQF_SHARED | IRQF_ONESHOT,
					  name, ddata);
	अगर (error) अणु
		dev_err(ddata->dev, "could not get irq %s: %i\n",
			name, error);

		वापस error;
	पूर्ण

	d = devm_kzalloc(ddata->dev, माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	d->name = name;
	d->irq = irq;
	list_add(&d->node, &ddata->irq_list);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर cpcap_अक्षरger_irqs[] = अणु
	/* REG_INT_0 */
	"chrg_det", "rvrs_chrg",

	/* REG_INT1 */
	"chrg_se1b", "se0conn", "rvrs_mode", "chrgcurr2", "chrgcurr1", "vbusvld",

	/* REG_INT_3 */
	"battdetb",
पूर्ण;

अटल पूर्णांक cpcap_usb_init_पूर्णांकerrupts(काष्ठा platक्रमm_device *pdev,
				     काष्ठा cpcap_अक्षरger_ddata *ddata)
अणु
	पूर्णांक i, error;

	क्रम (i = 0; i < ARRAY_SIZE(cpcap_अक्षरger_irqs); i++) अणु
		error = cpcap_usb_init_irq(pdev, ddata, cpcap_अक्षरger_irqs[i]);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cpcap_अक्षरger_init_optional_gpios(काष्ठा cpcap_अक्षरger_ddata *ddata)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		ddata->gpio[i] = devm_gpiod_get_index(ddata->dev, "mode",
						      i, GPIOD_OUT_HIGH);
		अगर (IS_ERR(ddata->gpio[i])) अणु
			dev_info(ddata->dev, "no mode change GPIO%i: %li\n",
				 i, PTR_ERR(ddata->gpio[i]));
			ddata->gpio[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_init_iio(काष्ठा cpcap_अक्षरger_ddata *ddata)
अणु
	स्थिर अक्षर * स्थिर names[CPCAP_CHARGER_IIO_NR] = अणु
		"battdetb", "battp", "vbus", "chg_isense", "batti",
	पूर्ण;
	पूर्णांक error, i;

	क्रम (i = 0; i < CPCAP_CHARGER_IIO_NR; i++) अणु
		ddata->channels[i] = devm_iio_channel_get(ddata->dev,
							  names[i]);
		अगर (IS_ERR(ddata->channels[i])) अणु
			error = PTR_ERR(ddata->channels[i]);
			जाओ out_err;
		पूर्ण

		अगर (!ddata->channels[i]->indio_dev) अणु
			error = -ENXIO;
			जाओ out_err;
		पूर्ण
	पूर्ण

	वापस 0;

out_err:
	अगर (error != -EPROBE_DEFER)
		dev_err(ddata->dev, "could not initialize VBUS or ID IIO: %i\n",
			error);

	वापस error;
पूर्ण

अटल अक्षर *cpcap_अक्षरger_supplied_to[] = अणु
	"battery",
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc cpcap_अक्षरger_usb_desc = अणु
	.name		= "usb",
	.type		= POWER_SUPPLY_TYPE_USB,
	.properties	= cpcap_अक्षरger_props,
	.num_properties	= ARRAY_SIZE(cpcap_अक्षरger_props),
	.get_property	= cpcap_अक्षरger_get_property,
	.set_property	= cpcap_अक्षरger_set_property,
	.property_is_ग_लिखोable = cpcap_अक्षरger_property_is_ग_लिखोable,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id cpcap_अक्षरger_id_table[] = अणु
	अणु
		.compatible = "motorola,mapphone-cpcap-charger",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpcap_अक्षरger_id_table);
#पूर्ण_अगर

अटल पूर्णांक cpcap_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpcap_अक्षरger_ddata *ddata;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक error;

	of_id = of_match_device(of_match_ptr(cpcap_अक्षरger_id_table),
				&pdev->dev);
	अगर (!of_id)
		वापस -EINVAL;

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	ddata->dev = &pdev->dev;
	ddata->voltage = 4200000;
	ddata->limit_current = 532000;

	ddata->reg = dev_get_regmap(ddata->dev->parent, शून्य);
	अगर (!ddata->reg)
		वापस -ENODEV;

	INIT_LIST_HEAD(&ddata->irq_list);
	INIT_DELAYED_WORK(&ddata->detect_work, cpcap_usb_detect);
	INIT_DELAYED_WORK(&ddata->vbus_work, cpcap_अक्षरger_vbus_work);
	platक्रमm_set_drvdata(pdev, ddata);

	error = cpcap_अक्षरger_init_iio(ddata);
	अगर (error)
		वापस error;

	atomic_set(&ddata->active, 1);

	psy_cfg.of_node = pdev->dev.of_node;
	psy_cfg.drv_data = ddata;
	psy_cfg.supplied_to = cpcap_अक्षरger_supplied_to;
	psy_cfg.num_supplicants = ARRAY_SIZE(cpcap_अक्षरger_supplied_to),

	ddata->usb = devm_घातer_supply_रेजिस्टर(ddata->dev,
						&cpcap_अक्षरger_usb_desc,
						&psy_cfg);
	अगर (IS_ERR(ddata->usb)) अणु
		error = PTR_ERR(ddata->usb);
		dev_err(ddata->dev, "failed to register USB charger: %i\n",
			error);

		वापस error;
	पूर्ण

	error = cpcap_usb_init_पूर्णांकerrupts(pdev, ddata);
	अगर (error)
		वापस error;

	ddata->comparator.set_vbus = cpcap_अक्षरger_set_vbus;
	error = omap_usb2_set_comparator(&ddata->comparator);
	अगर (error == -ENODEV) अणु
		dev_info(ddata->dev, "charger needs phy, deferring probe\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	cpcap_अक्षरger_init_optional_gpios(ddata);

	schedule_delayed_work(&ddata->detect_work, 0);

	वापस 0;
पूर्ण

अटल व्योम cpcap_अक्षरger_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpcap_अक्षरger_ddata *ddata = platक्रमm_get_drvdata(pdev);
	पूर्णांक error;

	atomic_set(&ddata->active, 0);
	error = omap_usb2_set_comparator(शून्य);
	अगर (error)
		dev_warn(ddata->dev, "could not clear USB comparator: %i\n",
			 error);

	error = cpcap_अक्षरger_disable(ddata);
	अगर (error) अणु
		cpcap_अक्षरger_update_state(ddata, POWER_SUPPLY_STATUS_UNKNOWN);
		dev_warn(ddata->dev, "could not clear charger: %i\n",
			 error);
	पूर्ण
	cpcap_अक्षरger_update_state(ddata, POWER_SUPPLY_STATUS_DISCHARGING);
	cancel_delayed_work_sync(&ddata->vbus_work);
	cancel_delayed_work_sync(&ddata->detect_work);
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cpcap_अक्षरger_shutकरोwn(pdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cpcap_अक्षरger_driver = अणु
	.probe = cpcap_अक्षरger_probe,
	.driver	= अणु
		.name	= "cpcap-charger",
		.of_match_table = of_match_ptr(cpcap_अक्षरger_id_table),
	पूर्ण,
	.shutकरोwn = cpcap_अक्षरger_shutकरोwn,
	.हटाओ	= cpcap_अक्षरger_हटाओ,
पूर्ण;
module_platक्रमm_driver(cpcap_अक्षरger_driver);

MODULE_AUTHOR("Tony Lindgren <tony@atomide.com>");
MODULE_DESCRIPTION("CPCAP Battery Charger Interface driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:cpcap-charger");
