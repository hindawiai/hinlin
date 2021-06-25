<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery class driver क्रम Apple PMU
 *
 *	Copyright तऊ 2006  David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <linux/slab.h>

अटल काष्ठा pmu_battery_dev अणु
	काष्ठा घातer_supply *bat;
	काष्ठा घातer_supply_desc bat_desc;
	काष्ठा pmu_battery_info *pbi;
	अक्षर name[16];
	पूर्णांक propval;
पूर्ण *pbats[PMU_MAX_BATTERIES];

#घोषणा to_pmu_battery_dev(x) घातer_supply_get_drvdata(x)

/*********************************************************************
 *		Power
 *********************************************************************/

अटल पूर्णांक pmu_get_ac_prop(काष्ठा घातer_supply *psy,
			   क्रमागत घातer_supply_property psp,
			   जोड़ घातer_supply_propval *val)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = (!!(pmu_घातer_flags & PMU_PWR_AC_PRESENT)) ||
			      (pmu_battery_count == 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property pmu_ac_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc pmu_ac_desc = अणु
	.name = "pmu-ac",
	.type = POWER_SUPPLY_TYPE_MAINS,
	.properties = pmu_ac_props,
	.num_properties = ARRAY_SIZE(pmu_ac_props),
	.get_property = pmu_get_ac_prop,
पूर्ण;

अटल काष्ठा घातer_supply *pmu_ac;

/*********************************************************************
 *		Battery properties
 *********************************************************************/

अटल अक्षर *pmu_batt_types[] = अणु
	"Smart", "Comet", "Hooper", "Unknown"
पूर्ण;

अटल अक्षर *pmu_bat_get_model_name(काष्ठा pmu_battery_info *pbi)
अणु
	चयन (pbi->flags & PMU_BATT_TYPE_MASK) अणु
	हाल PMU_BATT_TYPE_SMART:
		वापस pmu_batt_types[0];
	हाल PMU_BATT_TYPE_COMET:
		वापस pmu_batt_types[1];
	हाल PMU_BATT_TYPE_HOOPER:
		वापस pmu_batt_types[2];
	शेष: अवरोध;
	पूर्ण
	वापस pmu_batt_types[3];
पूर्ण

अटल पूर्णांक pmu_bat_get_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा pmu_battery_dev *pbat = to_pmu_battery_dev(psy);
	काष्ठा pmu_battery_info *pbi = pbat->pbi;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (pbi->flags & PMU_BATT_CHARGING)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा अगर (pmu_घातer_flags & PMU_PWR_AC_PRESENT)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = !!(pbi->flags & PMU_BATT_PRESENT);
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = pmu_bat_get_model_name(pbi);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ENERGY_AVG:
		val->पूर्णांकval = pbi->अक्षरge     * 1000; /* mWh -> तगWh */
		अवरोध;
	हाल POWER_SUPPLY_PROP_ENERGY_FULL:
		val->पूर्णांकval = pbi->max_अक्षरge * 1000; /* mWh -> तगWh */
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		val->पूर्णांकval = pbi->amperage   * 1000; /* mA -> तगA */
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		val->पूर्णांकval = pbi->voltage    * 1000; /* mV -> तगV */
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG:
		val->पूर्णांकval = pbi->समय_reमुख्यing;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property pmu_bat_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_ENERGY_AVG,
	POWER_SUPPLY_PROP_ENERGY_FULL,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG,
पूर्ण;

/*********************************************************************
 *		Initialisation
 *********************************************************************/

अटल काष्ठा platक्रमm_device *bat_pdev;

अटल पूर्णांक __init pmu_bat_init(व्योम)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	bat_pdev = platक्रमm_device_रेजिस्टर_simple("pmu-battery",
						   0, शून्य, 0);
	अगर (IS_ERR(bat_pdev)) अणु
		ret = PTR_ERR(bat_pdev);
		जाओ pdev_रेजिस्टर_failed;
	पूर्ण

	pmu_ac = घातer_supply_रेजिस्टर(&bat_pdev->dev, &pmu_ac_desc, शून्य);
	अगर (IS_ERR(pmu_ac)) अणु
		ret = PTR_ERR(pmu_ac);
		जाओ ac_रेजिस्टर_failed;
	पूर्ण

	क्रम (i = 0; i < pmu_battery_count; i++) अणु
		काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
		काष्ठा pmu_battery_dev *pbat = kzalloc(माप(*pbat),
						       GFP_KERNEL);
		अगर (!pbat)
			अवरोध;

		प्र_लिखो(pbat->name, "PMU_battery_%d", i);
		pbat->bat_desc.name = pbat->name;
		pbat->bat_desc.properties = pmu_bat_props;
		pbat->bat_desc.num_properties = ARRAY_SIZE(pmu_bat_props);
		pbat->bat_desc.get_property = pmu_bat_get_property;
		pbat->pbi = &pmu_batteries[i];
		psy_cfg.drv_data = pbat;

		pbat->bat = घातer_supply_रेजिस्टर(&bat_pdev->dev,
						  &pbat->bat_desc,
						  &psy_cfg);
		अगर (IS_ERR(pbat->bat)) अणु
			ret = PTR_ERR(pbat->bat);
			kमुक्त(pbat);
			जाओ battery_रेजिस्टर_failed;
		पूर्ण
		pbats[i] = pbat;
	पूर्ण

	जाओ success;

battery_रेजिस्टर_failed:
	जबतक (i--) अणु
		अगर (!pbats[i])
			जारी;
		घातer_supply_unरेजिस्टर(pbats[i]->bat);
		kमुक्त(pbats[i]);
	पूर्ण
	घातer_supply_unरेजिस्टर(pmu_ac);
ac_रेजिस्टर_failed:
	platक्रमm_device_unरेजिस्टर(bat_pdev);
pdev_रेजिस्टर_failed:
success:
	वापस ret;
पूर्ण

अटल व्योम __निकास pmu_bat_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PMU_MAX_BATTERIES; i++) अणु
		अगर (!pbats[i])
			जारी;
		घातer_supply_unरेजिस्टर(pbats[i]->bat);
		kमुक्त(pbats[i]);
	पूर्ण
	घातer_supply_unरेजिस्टर(pmu_ac);
	platक्रमm_device_unरेजिस्टर(bat_pdev);
पूर्ण

module_init(pmu_bat_init);
module_निकास(pmu_bat_निकास);

MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PMU battery driver");
