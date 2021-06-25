<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery अक्षरger driver क्रम Dialog Semiconductor DA9030
 *
 * Copyright (C) 2008 Compulab, Ltd.
 * 	Mike Rapoport <mike@compulab.co.il>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mfd/da903x.h>

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/notअगरier.h>

#घोषणा DA9030_FAULT_LOG		0x0a
#घोषणा DA9030_FAULT_LOG_OVER_TEMP	(1 << 7)
#घोषणा DA9030_FAULT_LOG_VBAT_OVER	(1 << 4)

#घोषणा DA9030_CHARGE_CONTROL		0x28
#घोषणा DA9030_CHRG_CHARGER_ENABLE	(1 << 7)

#घोषणा DA9030_ADC_MAN_CONTROL		0x30
#घोषणा DA9030_ADC_TBATREF_ENABLE	(1 << 5)
#घोषणा DA9030_ADC_LDO_INT_ENABLE	(1 << 4)

#घोषणा DA9030_ADC_AUTO_CONTROL		0x31
#घोषणा DA9030_ADC_TBAT_ENABLE		(1 << 5)
#घोषणा DA9030_ADC_VBAT_IN_TXON		(1 << 4)
#घोषणा DA9030_ADC_VCH_ENABLE		(1 << 3)
#घोषणा DA9030_ADC_ICH_ENABLE		(1 << 2)
#घोषणा DA9030_ADC_VBAT_ENABLE		(1 << 1)
#घोषणा DA9030_ADC_AUTO_SLEEP_ENABLE	(1 << 0)

#घोषणा DA9030_VBATMON		0x32
#घोषणा DA9030_VBATMONTXON	0x33
#घोषणा DA9030_TBATHIGHP	0x34
#घोषणा DA9030_TBATHIGHN	0x35
#घोषणा DA9030_TBATLOW		0x36

#घोषणा DA9030_VBAT_RES		0x41
#घोषणा DA9030_VBATMIN_RES	0x42
#घोषणा DA9030_VBATMINTXON_RES	0x43
#घोषणा DA9030_ICHMAX_RES	0x44
#घोषणा DA9030_ICHMIN_RES	0x45
#घोषणा DA9030_ICHAVERAGE_RES	0x46
#घोषणा DA9030_VCHMAX_RES	0x47
#घोषणा DA9030_VCHMIN_RES	0x48
#घोषणा DA9030_TBAT_RES		0x49

काष्ठा da9030_adc_res अणु
	uपूर्णांक8_t vbat_res;
	uपूर्णांक8_t vbaपंचांगin_res;
	uपूर्णांक8_t vbaपंचांगपूर्णांकxon;
	uपूर्णांक8_t ichmax_res;
	uपूर्णांक8_t ichmin_res;
	uपूर्णांक8_t ichaverage_res;
	uपूर्णांक8_t vchmax_res;
	uपूर्णांक8_t vchmin_res;
	uपूर्णांक8_t tbat_res;
	uपूर्णांक8_t adc_in4_res;
	uपूर्णांक8_t adc_in5_res;
पूर्ण;

काष्ठा da9030_battery_thresholds अणु
	पूर्णांक tbat_low;
	पूर्णांक tbat_high;
	पूर्णांक tbat_restart;

	पूर्णांक vbat_low;
	पूर्णांक vbat_crit;
	पूर्णांक vbat_अक्षरge_start;
	पूर्णांक vbat_अक्षरge_stop;
	पूर्णांक vbat_अक्षरge_restart;

	पूर्णांक vअक्षरge_min;
	पूर्णांक vअक्षरge_max;
पूर्ण;

काष्ठा da9030_अक्षरger अणु
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply_desc psy_desc;

	काष्ठा device *master;

	काष्ठा da9030_adc_res adc;
	काष्ठा delayed_work work;
	अचिन्हित पूर्णांक पूर्णांकerval;

	काष्ठा घातer_supply_info *battery_info;

	काष्ठा da9030_battery_thresholds thresholds;

	अचिन्हित पूर्णांक अक्षरge_milliamp;
	अचिन्हित पूर्णांक अक्षरge_millivolt;

	/* अक्षरger status */
	bool chdet;
	uपूर्णांक8_t fault;
	पूर्णांक mA;
	पूर्णांक mV;
	bool is_on;

	काष्ठा notअगरier_block nb;

	/* platक्रमm callbacks क्रम battery low and critical events */
	व्योम (*battery_low)(व्योम);
	व्योम (*battery_critical)(व्योम);

	काष्ठा dentry *debug_file;
पूर्ण;

अटल अंतरभूत पूर्णांक da9030_reg_to_mV(पूर्णांक reg)
अणु
	वापस ((reg * 2650) >> 8) + 2650;
पूर्ण

अटल अंतरभूत पूर्णांक da9030_millivolt_to_reg(पूर्णांक mV)
अणु
	वापस ((mV - 2650) << 8) / 2650;
पूर्ण

अटल अंतरभूत पूर्णांक da9030_reg_to_mA(पूर्णांक reg)
अणु
	वापस ((reg * 24000) >> 8) / 15;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक bat_debug_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा da9030_अक्षरger *अक्षरger = s->निजी;

	seq_म_लिखो(s, "charger is %s\n", अक्षरger->is_on ? "on" : "off");
	अगर (अक्षरger->chdet) अणु
		seq_म_लिखो(s, "iset = %dmA, vset = %dmV\n",
			   अक्षरger->mA, अक्षरger->mV);
	पूर्ण

	seq_म_लिखो(s, "vbat_res = %d (%dmV)\n",
		   अक्षरger->adc.vbat_res,
		   da9030_reg_to_mV(अक्षरger->adc.vbat_res));
	seq_म_लिखो(s, "vbatmin_res = %d (%dmV)\n",
		   अक्षरger->adc.vbaपंचांगin_res,
		   da9030_reg_to_mV(अक्षरger->adc.vbaपंचांगin_res));
	seq_म_लिखो(s, "vbatmintxon = %d (%dmV)\n",
		   अक्षरger->adc.vbaपंचांगपूर्णांकxon,
		   da9030_reg_to_mV(अक्षरger->adc.vbaपंचांगपूर्णांकxon));
	seq_म_लिखो(s, "ichmax_res = %d (%dmA)\n",
		   अक्षरger->adc.ichmax_res,
		   da9030_reg_to_mV(अक्षरger->adc.ichmax_res));
	seq_म_लिखो(s, "ichmin_res = %d (%dmA)\n",
		   अक्षरger->adc.ichmin_res,
		   da9030_reg_to_mA(अक्षरger->adc.ichmin_res));
	seq_म_लिखो(s, "ichaverage_res = %d (%dmA)\n",
		   अक्षरger->adc.ichaverage_res,
		   da9030_reg_to_mA(अक्षरger->adc.ichaverage_res));
	seq_म_लिखो(s, "vchmax_res = %d (%dmV)\n",
		   अक्षरger->adc.vchmax_res,
		   da9030_reg_to_mA(अक्षरger->adc.vchmax_res));
	seq_म_लिखो(s, "vchmin_res = %d (%dmV)\n",
		   अक्षरger->adc.vchmin_res,
		   da9030_reg_to_mV(अक्षरger->adc.vchmin_res));

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(bat_debug);

अटल काष्ठा dentry *da9030_bat_create_debugfs(काष्ठा da9030_अक्षरger *अक्षरger)
अणु
	अक्षरger->debug_file = debugfs_create_file("charger", 0666, शून्य,
						  अक्षरger, &bat_debug_fops);
	वापस अक्षरger->debug_file;
पूर्ण

अटल व्योम da9030_bat_हटाओ_debugfs(काष्ठा da9030_अक्षरger *अक्षरger)
अणु
	debugfs_हटाओ(अक्षरger->debug_file);
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा dentry *da9030_bat_create_debugfs(काष्ठा da9030_अक्षरger *अक्षरger)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम da9030_bat_हटाओ_debugfs(काष्ठा da9030_अक्षरger *अक्षरger)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम da9030_पढ़ो_adc(काष्ठा da9030_अक्षरger *अक्षरger,
				   काष्ठा da9030_adc_res *adc)
अणु
	da903x_पढ़ोs(अक्षरger->master, DA9030_VBAT_RES,
		     माप(*adc), (uपूर्णांक8_t *)adc);
पूर्ण

अटल व्योम da9030_अक्षरger_update_state(काष्ठा da9030_अक्षरger *अक्षरger)
अणु
	uपूर्णांक8_t val;

	da903x_पढ़ो(अक्षरger->master, DA9030_CHARGE_CONTROL, &val);
	अक्षरger->is_on = (val & DA9030_CHRG_CHARGER_ENABLE) ? 1 : 0;
	अक्षरger->mA = ((val >> 3) & 0xf) * 100;
	अक्षरger->mV = (val & 0x7) * 50 + 4000;

	da9030_पढ़ो_adc(अक्षरger, &अक्षरger->adc);
	da903x_पढ़ो(अक्षरger->master, DA9030_FAULT_LOG, &अक्षरger->fault);
	अक्षरger->chdet = da903x_query_status(अक्षरger->master,
						     DA9030_STATUS_CHDET);
पूर्ण

अटल व्योम da9030_set_अक्षरge(काष्ठा da9030_अक्षरger *अक्षरger, पूर्णांक on)
अणु
	uपूर्णांक8_t val;

	अगर (on) अणु
		val = DA9030_CHRG_CHARGER_ENABLE;
		val |= (अक्षरger->अक्षरge_milliamp / 100) << 3;
		val |= (अक्षरger->अक्षरge_millivolt - 4000) / 50;
		अक्षरger->is_on = 1;
	पूर्ण अन्यथा अणु
		val = 0;
		अक्षरger->is_on = 0;
	पूर्ण

	da903x_ग_लिखो(अक्षरger->master, DA9030_CHARGE_CONTROL, val);

	घातer_supply_changed(अक्षरger->psy);
पूर्ण

अटल व्योम da9030_अक्षरger_check_state(काष्ठा da9030_अक्षरger *अक्षरger)
अणु
	da9030_अक्षरger_update_state(अक्षरger);

	/* we wake or boot with बाह्यal घातer on */
	अगर (!अक्षरger->is_on) अणु
		अगर ((अक्षरger->chdet) &&
		    (अक्षरger->adc.vbat_res <
		     अक्षरger->thresholds.vbat_अक्षरge_start)) अणु
			da9030_set_अक्षरge(अक्षरger, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Charger has been pulled out */
		अगर (!अक्षरger->chdet) अणु
			da9030_set_अक्षरge(अक्षरger, 0);
			वापस;
		पूर्ण

		अगर (अक्षरger->adc.vbat_res >=
		    अक्षरger->thresholds.vbat_अक्षरge_stop) अणु
			da9030_set_अक्षरge(अक्षरger, 0);
			da903x_ग_लिखो(अक्षरger->master, DA9030_VBATMON,
				       अक्षरger->thresholds.vbat_अक्षरge_restart);
		पूर्ण अन्यथा अगर (अक्षरger->adc.vbat_res >
			   अक्षरger->thresholds.vbat_low) अणु
			/* we are अक्षरging and passed LOW_THRESH,
			   so upate DA9030 VBAT threshold
			 */
			da903x_ग_लिखो(अक्षरger->master, DA9030_VBATMON,
				     अक्षरger->thresholds.vbat_low);
		पूर्ण
		अगर (अक्षरger->adc.vchmax_res > अक्षरger->thresholds.vअक्षरge_max ||
		    अक्षरger->adc.vchmin_res < अक्षरger->thresholds.vअक्षरge_min ||
		    /* Tempreture पढ़ोings are negative */
		    अक्षरger->adc.tbat_res < अक्षरger->thresholds.tbat_high ||
		    अक्षरger->adc.tbat_res > अक्षरger->thresholds.tbat_low) अणु
			/* disable अक्षरger */
			da9030_set_अक्षरge(अक्षरger, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम da9030_अक्षरging_monitor(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da9030_अक्षरger *अक्षरger;

	अक्षरger = container_of(work, काष्ठा da9030_अक्षरger, work.work);

	da9030_अक्षरger_check_state(अक्षरger);

	/* reschedule क्रम the next समय */
	schedule_delayed_work(&अक्षरger->work, अक्षरger->पूर्णांकerval);
पूर्ण

अटल क्रमागत घातer_supply_property da9030_battery_props[] = अणु
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
पूर्ण;

अटल व्योम da9030_battery_check_status(काष्ठा da9030_अक्षरger *अक्षरger,
				    जोड़ घातer_supply_propval *val)
अणु
	अगर (अक्षरger->chdet) अणु
		अगर (अक्षरger->is_on)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
	पूर्ण अन्यथा अणु
		val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
	पूर्ण
पूर्ण

अटल व्योम da9030_battery_check_health(काष्ठा da9030_अक्षरger *अक्षरger,
				    जोड़ घातer_supply_propval *val)
अणु
	अगर (अक्षरger->fault & DA9030_FAULT_LOG_OVER_TEMP)
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
	अन्यथा अगर (अक्षरger->fault & DA9030_FAULT_LOG_VBAT_OVER)
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	अन्यथा
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
पूर्ण

अटल पूर्णांक da9030_battery_get_property(काष्ठा घातer_supply *psy,
				   क्रमागत घातer_supply_property psp,
				   जोड़ घातer_supply_propval *val)
अणु
	काष्ठा da9030_अक्षरger *अक्षरger = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		da9030_battery_check_status(अक्षरger, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		da9030_battery_check_health(अक्षरger, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = अक्षरger->battery_info->technology;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->पूर्णांकval = अक्षरger->battery_info->voltage_max_design;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->पूर्णांकval = अक्षरger->battery_info->voltage_min_design;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = da9030_reg_to_mV(अक्षरger->adc.vbat_res) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		val->पूर्णांकval =
			da9030_reg_to_mA(अक्षरger->adc.ichaverage_res) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = अक्षरger->battery_info->name;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम da9030_battery_vbat_event(काष्ठा da9030_अक्षरger *अक्षरger)
अणु
	da9030_पढ़ो_adc(अक्षरger, &अक्षरger->adc);

	अगर (अक्षरger->is_on)
		वापस;

	अगर (अक्षरger->adc.vbat_res < अक्षरger->thresholds.vbat_low) अणु
		/* set VBAT threshold क्रम critical */
		da903x_ग_लिखो(अक्षरger->master, DA9030_VBATMON,
			     अक्षरger->thresholds.vbat_crit);
		अगर (अक्षरger->battery_low)
			अक्षरger->battery_low();
	पूर्ण अन्यथा अगर (अक्षरger->adc.vbat_res <
		   अक्षरger->thresholds.vbat_crit) अणु
		/* notअगरy the प्रणाली of battery critical */
		अगर (अक्षरger->battery_critical)
			अक्षरger->battery_critical();
	पूर्ण
पूर्ण

अटल पूर्णांक da9030_battery_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
				व्योम *data)
अणु
	काष्ठा da9030_अक्षरger *अक्षरger =
		container_of(nb, काष्ठा da9030_अक्षरger, nb);

	चयन (event) अणु
	हाल DA9030_EVENT_CHDET:
		cancel_delayed_work_sync(&अक्षरger->work);
		schedule_work(&अक्षरger->work.work);
		अवरोध;
	हाल DA9030_EVENT_VBATMON:
		da9030_battery_vbat_event(अक्षरger);
		अवरोध;
	हाल DA9030_EVENT_CHIOVER:
	हाल DA9030_EVENT_TBAT:
		da9030_set_अक्षरge(अक्षरger, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम da9030_battery_convert_thresholds(काष्ठा da9030_अक्षरger *अक्षरger,
					      काष्ठा da9030_battery_info *pdata)
अणु
	अक्षरger->thresholds.tbat_low = pdata->tbat_low;
	अक्षरger->thresholds.tbat_high = pdata->tbat_high;
	अक्षरger->thresholds.tbat_restart  = pdata->tbat_restart;

	अक्षरger->thresholds.vbat_low =
		da9030_millivolt_to_reg(pdata->vbat_low);
	अक्षरger->thresholds.vbat_crit =
		da9030_millivolt_to_reg(pdata->vbat_crit);
	अक्षरger->thresholds.vbat_अक्षरge_start =
		da9030_millivolt_to_reg(pdata->vbat_अक्षरge_start);
	अक्षरger->thresholds.vbat_अक्षरge_stop =
		da9030_millivolt_to_reg(pdata->vbat_अक्षरge_stop);
	अक्षरger->thresholds.vbat_अक्षरge_restart =
		da9030_millivolt_to_reg(pdata->vbat_अक्षरge_restart);

	अक्षरger->thresholds.vअक्षरge_min =
		da9030_millivolt_to_reg(pdata->vअक्षरge_min);
	अक्षरger->thresholds.vअक्षरge_max =
		da9030_millivolt_to_reg(pdata->vअक्षरge_max);
पूर्ण

अटल व्योम da9030_battery_setup_psy(काष्ठा da9030_अक्षरger *अक्षरger)
अणु
	काष्ठा घातer_supply_desc *psy_desc = &अक्षरger->psy_desc;
	काष्ठा घातer_supply_info *info = अक्षरger->battery_info;

	psy_desc->name = info->name;
	psy_desc->use_क्रम_apm = info->use_क्रम_apm;
	psy_desc->type = POWER_SUPPLY_TYPE_BATTERY;
	psy_desc->get_property = da9030_battery_get_property;

	psy_desc->properties = da9030_battery_props;
	psy_desc->num_properties = ARRAY_SIZE(da9030_battery_props);
पूर्ण;

अटल पूर्णांक da9030_battery_अक्षरger_init(काष्ठा da9030_अक्षरger *अक्षरger)
अणु
	अक्षर v[5];
	पूर्णांक ret;

	v[0] = v[1] = अक्षरger->thresholds.vbat_low;
	v[2] = अक्षरger->thresholds.tbat_high;
	v[3] = अक्षरger->thresholds.tbat_restart;
	v[4] = अक्षरger->thresholds.tbat_low;

	ret = da903x_ग_लिखोs(अक्षरger->master, DA9030_VBATMON, 5, v);
	अगर (ret)
		वापस ret;

	/*
	 * Enable reference voltage supply क्रम ADC from the LDO_INTERNAL
	 * regulator. Must be set beक्रमe ADC measurements can be made.
	 */
	ret = da903x_ग_लिखो(अक्षरger->master, DA9030_ADC_MAN_CONTROL,
			   DA9030_ADC_LDO_INT_ENABLE |
			   DA9030_ADC_TBATREF_ENABLE);
	अगर (ret)
		वापस ret;

	/* enable स्वतः ADC measuremnts */
	वापस da903x_ग_लिखो(अक्षरger->master, DA9030_ADC_AUTO_CONTROL,
			    DA9030_ADC_TBAT_ENABLE | DA9030_ADC_VBAT_IN_TXON |
			    DA9030_ADC_VCH_ENABLE | DA9030_ADC_ICH_ENABLE |
			    DA9030_ADC_VBAT_ENABLE |
			    DA9030_ADC_AUTO_SLEEP_ENABLE);
पूर्ण

अटल पूर्णांक da9030_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9030_अक्षरger *अक्षरger;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा da9030_battery_info *pdata = pdev->dev.platक्रमm_data;
	पूर्णांक ret;

	अगर (pdata == शून्य)
		वापस -EINVAL;

	अगर (pdata->अक्षरge_milliamp >= 1500 ||
	    pdata->अक्षरge_millivolt < 4000 ||
	    pdata->अक्षरge_millivolt > 4350)
		वापस -EINVAL;

	अक्षरger = devm_kzalloc(&pdev->dev, माप(*अक्षरger), GFP_KERNEL);
	अगर (अक्षरger == शून्य)
		वापस -ENOMEM;

	अक्षरger->master = pdev->dev.parent;

	/* 10 seconds between monitor runs unless platक्रमm defines other
	   पूर्णांकerval */
	अक्षरger->पूर्णांकerval = msecs_to_jअगरfies(
		(pdata->baपंचांगon_पूर्णांकerval ? : 10) * 1000);

	अक्षरger->अक्षरge_milliamp = pdata->अक्षरge_milliamp;
	अक्षरger->अक्षरge_millivolt = pdata->अक्षरge_millivolt;
	अक्षरger->battery_info = pdata->battery_info;
	अक्षरger->battery_low = pdata->battery_low;
	अक्षरger->battery_critical = pdata->battery_critical;

	da9030_battery_convert_thresholds(अक्षरger, pdata);

	ret = da9030_battery_अक्षरger_init(अक्षरger);
	अगर (ret)
		जाओ err_अक्षरger_init;

	INIT_DELAYED_WORK(&अक्षरger->work, da9030_अक्षरging_monitor);
	schedule_delayed_work(&अक्षरger->work, अक्षरger->पूर्णांकerval);

	अक्षरger->nb.notअगरier_call = da9030_battery_event;
	ret = da903x_रेजिस्टर_notअगरier(अक्षरger->master, &अक्षरger->nb,
				       DA9030_EVENT_CHDET |
				       DA9030_EVENT_VBATMON |
				       DA9030_EVENT_CHIOVER |
				       DA9030_EVENT_TBAT);
	अगर (ret)
		जाओ err_notअगरier;

	da9030_battery_setup_psy(अक्षरger);
	psy_cfg.drv_data = अक्षरger;
	अक्षरger->psy = घातer_supply_रेजिस्टर(&pdev->dev, &अक्षरger->psy_desc,
					     &psy_cfg);
	अगर (IS_ERR(अक्षरger->psy)) अणु
		ret = PTR_ERR(अक्षरger->psy);
		जाओ err_ps_रेजिस्टर;
	पूर्ण

	अक्षरger->debug_file = da9030_bat_create_debugfs(अक्षरger);
	platक्रमm_set_drvdata(pdev, अक्षरger);
	वापस 0;

err_ps_रेजिस्टर:
	da903x_unरेजिस्टर_notअगरier(अक्षरger->master, &अक्षरger->nb,
				   DA9030_EVENT_CHDET | DA9030_EVENT_VBATMON |
				   DA9030_EVENT_CHIOVER | DA9030_EVENT_TBAT);
err_notअगरier:
	cancel_delayed_work(&अक्षरger->work);

err_अक्षरger_init:
	वापस ret;
पूर्ण

अटल पूर्णांक da9030_battery_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा da9030_अक्षरger *अक्षरger = platक्रमm_get_drvdata(dev);

	da9030_bat_हटाओ_debugfs(अक्षरger);

	da903x_unरेजिस्टर_notअगरier(अक्षरger->master, &अक्षरger->nb,
				   DA9030_EVENT_CHDET | DA9030_EVENT_VBATMON |
				   DA9030_EVENT_CHIOVER | DA9030_EVENT_TBAT);
	cancel_delayed_work_sync(&अक्षरger->work);
	da9030_set_अक्षरge(अक्षरger, 0);
	घातer_supply_unरेजिस्टर(अक्षरger->psy);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da903x_battery_driver = अणु
	.driver	= अणु
		.name	= "da903x-battery",
	पूर्ण,
	.probe = da9030_battery_probe,
	.हटाओ = da9030_battery_हटाओ,
पूर्ण;

module_platक्रमm_driver(da903x_battery_driver);

MODULE_DESCRIPTION("DA9030 battery charger driver");
MODULE_AUTHOR("Mike Rapoport, CompuLab");
MODULE_LICENSE("GPL");
