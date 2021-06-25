<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Charging control driver क्रम the Wilco EC
 *
 * Copyright 2019 Google LLC
 *
 * See Documentation/ABI/testing/sysfs-class-घातer and
 * Documentation/ABI/testing/sysfs-class-घातer-wilco क्रम userspace पूर्णांकerface
 * and other info.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/wilco-ec.h>
#समावेश <linux/घातer_supply.h>

#घोषणा DRV_NAME "wilco-charger"

/* Property IDs and related EC स्थिरants */
#घोषणा PID_CHARGE_MODE		0x0710
#घोषणा PID_CHARGE_LOWER_LIMIT	0x0711
#घोषणा PID_CHARGE_UPPER_LIMIT	0x0712

क्रमागत अक्षरge_mode अणु
	CHARGE_MODE_STD = 1,	/* Used क्रम Standard */
	CHARGE_MODE_EXP = 2,	/* Express Charge, used क्रम Fast */
	CHARGE_MODE_AC = 3,	/* Mostly AC use, used क्रम Trickle */
	CHARGE_MODE_AUTO = 4,	/* Used क्रम Adaptive */
	CHARGE_MODE_CUSTOM = 5,	/* Used क्रम Custom */
	CHARGE_MODE_LONGLIFE = 6, /* Used क्रम Long Lअगरe */
पूर्ण;

#घोषणा CHARGE_LOWER_LIMIT_MIN	50
#घोषणा CHARGE_LOWER_LIMIT_MAX	95
#घोषणा CHARGE_UPPER_LIMIT_MIN	55
#घोषणा CHARGE_UPPER_LIMIT_MAX	100

/* Convert from POWER_SUPPLY_PROP_CHARGE_TYPE value to the EC's अक्षरge mode */
अटल पूर्णांक psp_val_to_अक्षरge_mode(पूर्णांक psp_val)
अणु
	चयन (psp_val) अणु
	हाल POWER_SUPPLY_CHARGE_TYPE_TRICKLE:
		वापस CHARGE_MODE_AC;
	हाल POWER_SUPPLY_CHARGE_TYPE_FAST:
		वापस CHARGE_MODE_EXP;
	हाल POWER_SUPPLY_CHARGE_TYPE_STANDARD:
		वापस CHARGE_MODE_STD;
	हाल POWER_SUPPLY_CHARGE_TYPE_ADAPTIVE:
		वापस CHARGE_MODE_AUTO;
	हाल POWER_SUPPLY_CHARGE_TYPE_CUSTOM:
		वापस CHARGE_MODE_CUSTOM;
	हाल POWER_SUPPLY_CHARGE_TYPE_LONGLIFE:
		वापस CHARGE_MODE_LONGLIFE;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Convert from EC's अक्षरge mode to POWER_SUPPLY_PROP_CHARGE_TYPE value */
अटल पूर्णांक अक्षरge_mode_to_psp_val(क्रमागत अक्षरge_mode mode)
अणु
	चयन (mode) अणु
	हाल CHARGE_MODE_AC:
		वापस POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
	हाल CHARGE_MODE_EXP:
		वापस POWER_SUPPLY_CHARGE_TYPE_FAST;
	हाल CHARGE_MODE_STD:
		वापस POWER_SUPPLY_CHARGE_TYPE_STANDARD;
	हाल CHARGE_MODE_AUTO:
		वापस POWER_SUPPLY_CHARGE_TYPE_ADAPTIVE;
	हाल CHARGE_MODE_CUSTOM:
		वापस POWER_SUPPLY_CHARGE_TYPE_CUSTOM;
	हाल CHARGE_MODE_LONGLIFE:
		वापस POWER_SUPPLY_CHARGE_TYPE_LONGLIFE;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल क्रमागत घातer_supply_property wilco_अक्षरge_props[] = अणु
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_CHARGE_CONTROL_START_THRESHOLD,
	POWER_SUPPLY_PROP_CHARGE_CONTROL_END_THRESHOLD,
पूर्ण;

अटल पूर्णांक wilco_अक्षरge_get_property(काष्ठा घातer_supply *psy,
				     क्रमागत घातer_supply_property psp,
				     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा wilco_ec_device *ec = घातer_supply_get_drvdata(psy);
	u32 property_id;
	पूर्णांक ret;
	u8 raw;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		property_id = PID_CHARGE_MODE;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_START_THRESHOLD:
		property_id = PID_CHARGE_LOWER_LIMIT;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_END_THRESHOLD:
		property_id = PID_CHARGE_UPPER_LIMIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = wilco_ec_get_byte_property(ec, property_id, &raw);
	अगर (ret < 0)
		वापस ret;
	अगर (property_id == PID_CHARGE_MODE) अणु
		ret = अक्षरge_mode_to_psp_val(raw);
		अगर (ret < 0)
			वापस -EBADMSG;
		raw = ret;
	पूर्ण
	val->पूर्णांकval = raw;

	वापस 0;
पूर्ण

अटल पूर्णांक wilco_अक्षरge_set_property(काष्ठा घातer_supply *psy,
				     क्रमागत घातer_supply_property psp,
				     स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा wilco_ec_device *ec = घातer_supply_get_drvdata(psy);
	पूर्णांक mode;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		mode = psp_val_to_अक्षरge_mode(val->पूर्णांकval);
		अगर (mode < 0)
			वापस -EINVAL;
		वापस wilco_ec_set_byte_property(ec, PID_CHARGE_MODE, mode);
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_START_THRESHOLD:
		अगर (val->पूर्णांकval < CHARGE_LOWER_LIMIT_MIN ||
		    val->पूर्णांकval > CHARGE_LOWER_LIMIT_MAX)
			वापस -EINVAL;
		वापस wilco_ec_set_byte_property(ec, PID_CHARGE_LOWER_LIMIT,
						  val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_END_THRESHOLD:
		अगर (val->पूर्णांकval < CHARGE_UPPER_LIMIT_MIN ||
		    val->पूर्णांकval > CHARGE_UPPER_LIMIT_MAX)
			वापस -EINVAL;
		वापस wilco_ec_set_byte_property(ec, PID_CHARGE_UPPER_LIMIT,
						  val->पूर्णांकval);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक wilco_अक्षरge_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
					      क्रमागत घातer_supply_property psp)
अणु
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc wilco_ps_desc = अणु
	.properties		= wilco_अक्षरge_props,
	.num_properties		= ARRAY_SIZE(wilco_अक्षरge_props),
	.get_property		= wilco_अक्षरge_get_property,
	.set_property		= wilco_अक्षरge_set_property,
	.property_is_ग_लिखोable	= wilco_अक्षरge_property_is_ग_लिखोable,
	.name			= DRV_NAME,
	.type			= POWER_SUPPLY_TYPE_MAINS,
पूर्ण;

अटल पूर्णांक wilco_अक्षरge_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wilco_ec_device *ec = dev_get_drvdata(pdev->dev.parent);
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा घातer_supply *psy;

	psy_cfg.drv_data = ec;
	psy = devm_घातer_supply_रेजिस्टर(&pdev->dev, &wilco_ps_desc, &psy_cfg);

	वापस PTR_ERR_OR_ZERO(psy);
पूर्ण

अटल काष्ठा platक्रमm_driver wilco_अक्षरge_driver = अणु
	.probe	= wilco_अक्षरge_probe,
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(wilco_अक्षरge_driver);

MODULE_ALIAS("platform:" DRV_NAME);
MODULE_AUTHOR("Nick Crews <ncrews@chromium.org>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Wilco EC charge control driver");
