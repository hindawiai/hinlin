<शैली गुरु>
/*
 * Copyright तऊ 2007 Anton Vorontsov <cbou@mail.ru>
 * Copyright तऊ 2007 Eugeny Boger <eugenyboger@dgap.mipt.ru>
 *
 * Author: Eugeny Boger <eugenyboger@dgap.mipt.ru>
 *
 * Use consistent with the GNU GPL is permitted,
 * provided that this copyright notice is
 * preserved in its entirety in all copies and derived works.
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/apm-emulation.h>


#घोषणा PSY_PROP(psy, prop, val) (घातer_supply_get_property(psy, \
			 POWER_SUPPLY_PROP_##prop, val))

#घोषणा _MPSY_PROP(prop, val) (घातer_supply_get_property(मुख्य_battery, \
							 prop, val))

#घोषणा MPSY_PROP(prop, val) _MPSY_PROP(POWER_SUPPLY_PROP_##prop, val)

अटल DEFINE_MUTEX(apm_mutex);
अटल काष्ठा घातer_supply *मुख्य_battery;

क्रमागत apm_source अणु
	SOURCE_ENERGY,
	SOURCE_CHARGE,
	SOURCE_VOLTAGE,
पूर्ण;

काष्ठा find_bat_param अणु
	काष्ठा घातer_supply *मुख्य;
	काष्ठा घातer_supply *bat;
	काष्ठा घातer_supply *max_अक्षरge_bat;
	काष्ठा घातer_supply *max_energy_bat;
	जोड़ घातer_supply_propval full;
	पूर्णांक max_अक्षरge;
	पूर्णांक max_energy;
पूर्ण;

अटल पूर्णांक __find_मुख्य_battery(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा find_bat_param *bp = (काष्ठा find_bat_param *)data;

	bp->bat = dev_get_drvdata(dev);

	अगर (bp->bat->desc->use_क्रम_apm) अणु
		/* nice, we explicitly asked to report this battery. */
		bp->मुख्य = bp->bat;
		वापस 1;
	पूर्ण

	अगर (!PSY_PROP(bp->bat, CHARGE_FULL_DESIGN, &bp->full) ||
			!PSY_PROP(bp->bat, CHARGE_FULL, &bp->full)) अणु
		अगर (bp->full.पूर्णांकval > bp->max_अक्षरge) अणु
			bp->max_अक्षरge_bat = bp->bat;
			bp->max_अक्षरge = bp->full.पूर्णांकval;
		पूर्ण
	पूर्ण अन्यथा अगर (!PSY_PROP(bp->bat, ENERGY_FULL_DESIGN, &bp->full) ||
			!PSY_PROP(bp->bat, ENERGY_FULL, &bp->full)) अणु
		अगर (bp->full.पूर्णांकval > bp->max_energy) अणु
			bp->max_energy_bat = bp->bat;
			bp->max_energy = bp->full.पूर्णांकval;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम find_मुख्य_battery(व्योम)
अणु
	काष्ठा find_bat_param bp;
	पूर्णांक error;

	स_रखो(&bp, 0, माप(काष्ठा find_bat_param));
	मुख्य_battery = शून्य;
	bp.मुख्य = मुख्य_battery;

	error = class_क्रम_each_device(घातer_supply_class, शून्य, &bp,
				      __find_मुख्य_battery);
	अगर (error) अणु
		मुख्य_battery = bp.मुख्य;
		वापस;
	पूर्ण

	अगर ((bp.max_energy_bat && bp.max_अक्षरge_bat) &&
			(bp.max_energy_bat != bp.max_अक्षरge_bat)) अणु
		/* try guess battery with more capacity */
		अगर (!PSY_PROP(bp.max_अक्षरge_bat, VOLTAGE_MAX_DESIGN,
			      &bp.full)) अणु
			अगर (bp.max_energy > bp.max_अक्षरge * bp.full.पूर्णांकval)
				मुख्य_battery = bp.max_energy_bat;
			अन्यथा
				मुख्य_battery = bp.max_अक्षरge_bat;
		पूर्ण अन्यथा अगर (!PSY_PROP(bp.max_energy_bat, VOLTAGE_MAX_DESIGN,
								  &bp.full)) अणु
			अगर (bp.max_अक्षरge > bp.max_energy / bp.full.पूर्णांकval)
				मुख्य_battery = bp.max_अक्षरge_bat;
			अन्यथा
				मुख्य_battery = bp.max_energy_bat;
		पूर्ण अन्यथा अणु
			/* give up, choice any */
			मुख्य_battery = bp.max_energy_bat;
		पूर्ण
	पूर्ण अन्यथा अगर (bp.max_अक्षरge_bat) अणु
		मुख्य_battery = bp.max_अक्षरge_bat;
	पूर्ण अन्यथा अगर (bp.max_energy_bat) अणु
		मुख्य_battery = bp.max_energy_bat;
	पूर्ण अन्यथा अणु
		/* give up, try the last अगर any */
		मुख्य_battery = bp.bat;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_calculate_समय(पूर्णांक status, क्रमागत apm_source source)
अणु
	जोड़ घातer_supply_propval full;
	जोड़ घातer_supply_propval empty;
	जोड़ घातer_supply_propval cur;
	जोड़ घातer_supply_propval I;
	क्रमागत घातer_supply_property full_prop;
	क्रमागत घातer_supply_property full_design_prop;
	क्रमागत घातer_supply_property empty_prop;
	क्रमागत घातer_supply_property empty_design_prop;
	क्रमागत घातer_supply_property cur_avg_prop;
	क्रमागत घातer_supply_property cur_now_prop;

	अगर (MPSY_PROP(CURRENT_AVG, &I)) अणु
		/* अगर battery can't report average value, use momentary */
		अगर (MPSY_PROP(CURRENT_NOW, &I))
			वापस -1;
	पूर्ण

	अगर (!I.पूर्णांकval)
		वापस 0;

	चयन (source) अणु
	हाल SOURCE_CHARGE:
		full_prop = POWER_SUPPLY_PROP_CHARGE_FULL;
		full_design_prop = POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN;
		empty_prop = POWER_SUPPLY_PROP_CHARGE_EMPTY;
		empty_design_prop = POWER_SUPPLY_PROP_CHARGE_EMPTY;
		cur_avg_prop = POWER_SUPPLY_PROP_CHARGE_AVG;
		cur_now_prop = POWER_SUPPLY_PROP_CHARGE_NOW;
		अवरोध;
	हाल SOURCE_ENERGY:
		full_prop = POWER_SUPPLY_PROP_ENERGY_FULL;
		full_design_prop = POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN;
		empty_prop = POWER_SUPPLY_PROP_ENERGY_EMPTY;
		empty_design_prop = POWER_SUPPLY_PROP_CHARGE_EMPTY;
		cur_avg_prop = POWER_SUPPLY_PROP_ENERGY_AVG;
		cur_now_prop = POWER_SUPPLY_PROP_ENERGY_NOW;
		अवरोध;
	हाल SOURCE_VOLTAGE:
		full_prop = POWER_SUPPLY_PROP_VOLTAGE_MAX;
		full_design_prop = POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN;
		empty_prop = POWER_SUPPLY_PROP_VOLTAGE_MIN;
		empty_design_prop = POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN;
		cur_avg_prop = POWER_SUPPLY_PROP_VOLTAGE_AVG;
		cur_now_prop = POWER_SUPPLY_PROP_VOLTAGE_NOW;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Unsupported source: %d\n", source);
		वापस -1;
	पूर्ण

	अगर (_MPSY_PROP(full_prop, &full)) अणु
		/* अगर battery can't report this property, use design value */
		अगर (_MPSY_PROP(full_design_prop, &full))
			वापस -1;
	पूर्ण

	अगर (_MPSY_PROP(empty_prop, &empty)) अणु
		/* अगर battery can't report this property, use design value */
		अगर (_MPSY_PROP(empty_design_prop, &empty))
			empty.पूर्णांकval = 0;
	पूर्ण

	अगर (_MPSY_PROP(cur_avg_prop, &cur)) अणु
		/* अगर battery can't report average value, use momentary */
		अगर (_MPSY_PROP(cur_now_prop, &cur))
			वापस -1;
	पूर्ण

	अगर (status == POWER_SUPPLY_STATUS_CHARGING)
		वापस ((cur.पूर्णांकval - full.पूर्णांकval) * 60L) / I.पूर्णांकval;
	अन्यथा
		वापस -((cur.पूर्णांकval - empty.पूर्णांकval) * 60L) / I.पूर्णांकval;
पूर्ण

अटल पूर्णांक calculate_समय(पूर्णांक status)
अणु
	पूर्णांक समय;

	समय = करो_calculate_समय(status, SOURCE_ENERGY);
	अगर (समय != -1)
		वापस समय;

	समय = करो_calculate_समय(status, SOURCE_CHARGE);
	अगर (समय != -1)
		वापस समय;

	समय = करो_calculate_समय(status, SOURCE_VOLTAGE);
	अगर (समय != -1)
		वापस समय;

	वापस -1;
पूर्ण

अटल पूर्णांक calculate_capacity(क्रमागत apm_source source)
अणु
	क्रमागत घातer_supply_property full_prop, empty_prop;
	क्रमागत घातer_supply_property full_design_prop, empty_design_prop;
	क्रमागत घातer_supply_property now_prop, avg_prop;
	जोड़ घातer_supply_propval empty, full, cur;
	पूर्णांक ret;

	चयन (source) अणु
	हाल SOURCE_CHARGE:
		full_prop = POWER_SUPPLY_PROP_CHARGE_FULL;
		empty_prop = POWER_SUPPLY_PROP_CHARGE_EMPTY;
		full_design_prop = POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN;
		empty_design_prop = POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN;
		now_prop = POWER_SUPPLY_PROP_CHARGE_NOW;
		avg_prop = POWER_SUPPLY_PROP_CHARGE_AVG;
		अवरोध;
	हाल SOURCE_ENERGY:
		full_prop = POWER_SUPPLY_PROP_ENERGY_FULL;
		empty_prop = POWER_SUPPLY_PROP_ENERGY_EMPTY;
		full_design_prop = POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN;
		empty_design_prop = POWER_SUPPLY_PROP_ENERGY_EMPTY_DESIGN;
		now_prop = POWER_SUPPLY_PROP_ENERGY_NOW;
		avg_prop = POWER_SUPPLY_PROP_ENERGY_AVG;
		अवरोध;
	हाल SOURCE_VOLTAGE:
		full_prop = POWER_SUPPLY_PROP_VOLTAGE_MAX;
		empty_prop = POWER_SUPPLY_PROP_VOLTAGE_MIN;
		full_design_prop = POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN;
		empty_design_prop = POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN;
		now_prop = POWER_SUPPLY_PROP_VOLTAGE_NOW;
		avg_prop = POWER_SUPPLY_PROP_VOLTAGE_AVG;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Unsupported source: %d\n", source);
		वापस -1;
	पूर्ण

	अगर (_MPSY_PROP(full_prop, &full)) अणु
		/* अगर battery can't report this property, use design value */
		अगर (_MPSY_PROP(full_design_prop, &full))
			वापस -1;
	पूर्ण

	अगर (_MPSY_PROP(avg_prop, &cur)) अणु
		/* अगर battery can't report average value, use momentary */
		अगर (_MPSY_PROP(now_prop, &cur))
			वापस -1;
	पूर्ण

	अगर (_MPSY_PROP(empty_prop, &empty)) अणु
		/* अगर battery can't report this property, use design value */
		अगर (_MPSY_PROP(empty_design_prop, &empty))
			empty.पूर्णांकval = 0;
	पूर्ण

	अगर (full.पूर्णांकval - empty.पूर्णांकval)
		ret =  ((cur.पूर्णांकval - empty.पूर्णांकval) * 100L) /
		       (full.पूर्णांकval - empty.पूर्णांकval);
	अन्यथा
		वापस -1;

	अगर (ret > 100)
		वापस 100;
	अन्यथा अगर (ret < 0)
		वापस 0;

	वापस ret;
पूर्ण

अटल व्योम apm_battery_apm_get_घातer_status(काष्ठा apm_घातer_info *info)
अणु
	जोड़ घातer_supply_propval status;
	जोड़ घातer_supply_propval capacity, समय_प्रकारo_full, समय_प्रकारo_empty;

	mutex_lock(&apm_mutex);
	find_मुख्य_battery();
	अगर (!मुख्य_battery) अणु
		mutex_unlock(&apm_mutex);
		वापस;
	पूर्ण

	/* status */

	अगर (MPSY_PROP(STATUS, &status))
		status.पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;

	/* ac line status */

	अगर ((status.पूर्णांकval == POWER_SUPPLY_STATUS_CHARGING) ||
	    (status.पूर्णांकval == POWER_SUPPLY_STATUS_NOT_CHARGING) ||
	    (status.पूर्णांकval == POWER_SUPPLY_STATUS_FULL))
		info->ac_line_status = APM_AC_ONLINE;
	अन्यथा
		info->ac_line_status = APM_AC_OFFLINE;

	/* battery lअगरe (i.e. capacity, in percents) */

	अगर (MPSY_PROP(CAPACITY, &capacity) == 0) अणु
		info->battery_lअगरe = capacity.पूर्णांकval;
	पूर्ण अन्यथा अणु
		/* try calculate using energy */
		info->battery_lअगरe = calculate_capacity(SOURCE_ENERGY);
		/* अगर failed try calculate using अक्षरge instead */
		अगर (info->battery_lअगरe == -1)
			info->battery_lअगरe = calculate_capacity(SOURCE_CHARGE);
		अगर (info->battery_lअगरe == -1)
			info->battery_lअगरe = calculate_capacity(SOURCE_VOLTAGE);
	पूर्ण

	/* अक्षरging status */

	अगर (status.पूर्णांकval == POWER_SUPPLY_STATUS_CHARGING) अणु
		info->battery_status = APM_BATTERY_STATUS_CHARGING;
	पूर्ण अन्यथा अणु
		अगर (info->battery_lअगरe > 50)
			info->battery_status = APM_BATTERY_STATUS_HIGH;
		अन्यथा अगर (info->battery_lअगरe > 5)
			info->battery_status = APM_BATTERY_STATUS_LOW;
		अन्यथा
			info->battery_status = APM_BATTERY_STATUS_CRITICAL;
	पूर्ण
	info->battery_flag = info->battery_status;

	/* समय */

	info->units = APM_UNITS_MINS;

	अगर (status.पूर्णांकval == POWER_SUPPLY_STATUS_CHARGING) अणु
		अगर (!MPSY_PROP(TIME_TO_FULL_AVG, &समय_प्रकारo_full) ||
				!MPSY_PROP(TIME_TO_FULL_NOW, &समय_प्रकारo_full))
			info->समय = समय_प्रकारo_full.पूर्णांकval / 60;
		अन्यथा
			info->समय = calculate_समय(status.पूर्णांकval);
	पूर्ण अन्यथा अणु
		अगर (!MPSY_PROP(TIME_TO_EMPTY_AVG, &समय_प्रकारo_empty) ||
			      !MPSY_PROP(TIME_TO_EMPTY_NOW, &समय_प्रकारo_empty))
			info->समय = समय_प्रकारo_empty.पूर्णांकval / 60;
		अन्यथा
			info->समय = calculate_समय(status.पूर्णांकval);
	पूर्ण

	mutex_unlock(&apm_mutex);
पूर्ण

अटल पूर्णांक __init apm_battery_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "APM Battery Driver\n");

	apm_get_घातer_status = apm_battery_apm_get_घातer_status;
	वापस 0;
पूर्ण

अटल व्योम __निकास apm_battery_निकास(व्योम)
अणु
	apm_get_घातer_status = शून्य;
पूर्ण

module_init(apm_battery_init);
module_निकास(apm_battery_निकास);

MODULE_AUTHOR("Eugeny Boger <eugenyboger@dgap.mipt.ru>");
MODULE_DESCRIPTION("APM emulation driver for battery monitoring class");
MODULE_LICENSE("GPL");
