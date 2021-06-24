<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 ST Ericsson.
 *
 * Power supply driver क्रम ST Ericsson pm2xxx_अक्षरger अक्षरger
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/pm2301_अक्षरger.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm.h>

#समावेश "ab8500-bm.h"
#समावेश "ab8500-chargalg.h"
#समावेश "pm2301_charger.h"

#घोषणा to_pm2xxx_अक्षरger_ac_device_info(x) container_of((x), \
		काष्ठा pm2xxx_अक्षरger, ac_chg)
#घोषणा SLEEP_MIN		50
#घोषणा SLEEP_MAX		100
#घोषणा PM2XXX_AUTOSUSPEND_DELAY 500

अटल पूर्णांक pm2xxx_पूर्णांकerrupt_रेजिस्टरs[] = अणु
	PM2XXX_REG_INT1,
	PM2XXX_REG_INT2,
	PM2XXX_REG_INT3,
	PM2XXX_REG_INT4,
	PM2XXX_REG_INT5,
	PM2XXX_REG_INT6,
पूर्ण;

अटल क्रमागत घातer_supply_property pm2xxx_अक्षरger_ac_props[] = अणु
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
पूर्ण;

अटल पूर्णांक pm2xxx_अक्षरger_voltage_map[] = अणु
	3500,
	3525,
	3550,
	3575,
	3600,
	3625,
	3650,
	3675,
	3700,
	3725,
	3750,
	3775,
	3800,
	3825,
	3850,
	3875,
	3900,
	3925,
	3950,
	3975,
	4000,
	4025,
	4050,
	4075,
	4100,
	4125,
	4150,
	4175,
	4200,
	4225,
	4250,
	4275,
	4300,
पूर्ण;

अटल पूर्णांक pm2xxx_अक्षरger_current_map[] = अणु
	200,
	200,
	400,
	600,
	800,
	1000,
	1200,
	1400,
	1600,
	1800,
	2000,
	2200,
	2400,
	2600,
	2800,
	3000,
पूर्ण;

अटल व्योम set_lpn_pin(काष्ठा pm2xxx_अक्षरger *pm2)
अणु
	अगर (!pm2->ac.अक्षरger_connected && gpio_is_valid(pm2->lpn_pin)) अणु
		gpio_set_value(pm2->lpn_pin, 1);
		usleep_range(SLEEP_MIN, SLEEP_MAX);
	पूर्ण
पूर्ण

अटल व्योम clear_lpn_pin(काष्ठा pm2xxx_अक्षरger *pm2)
अणु
	अगर (!pm2->ac.अक्षरger_connected && gpio_is_valid(pm2->lpn_pin))
		gpio_set_value(pm2->lpn_pin, 0);
पूर्ण

अटल पूर्णांक pm2xxx_reg_पढ़ो(काष्ठा pm2xxx_अक्षरger *pm2, पूर्णांक reg, u8 *val)
अणु
	पूर्णांक ret;

	/* wake up the device */
	pm_runसमय_get_sync(pm2->dev);

	ret = i2c_smbus_पढ़ो_i2c_block_data(pm2->config.pm2xxx_i2c, reg,
				1, val);
	अगर (ret < 0)
		dev_err(pm2->dev, "Error reading register at 0x%x\n", reg);
	अन्यथा
		ret = 0;

	pm_runसमय_put_sync(pm2->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक pm2xxx_reg_ग_लिखो(काष्ठा pm2xxx_अक्षरger *pm2, पूर्णांक reg, u8 val)
अणु
	पूर्णांक ret;

	/* wake up the device */
	pm_runसमय_get_sync(pm2->dev);

	ret = i2c_smbus_ग_लिखो_i2c_block_data(pm2->config.pm2xxx_i2c, reg,
				1, &val);
	अगर (ret < 0)
		dev_err(pm2->dev, "Error writing register at 0x%x\n", reg);
	अन्यथा
		ret = 0;

	pm_runसमय_put_sync(pm2->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरging_enable_mngt(काष्ठा pm2xxx_अक्षरger *pm2)
अणु
	पूर्णांक ret;

	/* Enable अक्षरging */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_CTRL_REG2,
			(PM2XXX_CH_AUTO_RESUME_EN | PM2XXX_CHARGER_ENA));

	वापस ret;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरging_disable_mngt(काष्ठा pm2xxx_अक्षरger *pm2)
अणु
	पूर्णांक ret;

	/* Disable SW EOC ctrl */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_SW_CTRL_REG, PM2XXX_SWCTRL_HW);
	अगर (ret < 0) अणु
		dev_err(pm2->dev, "%s pm2xxx write failed\n", __func__);
		वापस ret;
	पूर्ण

	/* Disable अक्षरging */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_CTRL_REG2,
			(PM2XXX_CH_AUTO_RESUME_DIS | PM2XXX_CHARGER_DIS));
	अगर (ret < 0) अणु
		dev_err(pm2->dev, "%s pm2xxx write failed\n", __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_batt_therm_mngt(काष्ठा pm2xxx_अक्षरger *pm2, पूर्णांक val)
अणु
	queue_work(pm2->अक्षरger_wq, &pm2->check_मुख्य_thermal_prot_work);

	वापस 0;
पूर्ण


अटल पूर्णांक pm2xxx_अक्षरger_die_therm_mngt(काष्ठा pm2xxx_अक्षरger *pm2, पूर्णांक val)
अणु
	queue_work(pm2->अक्षरger_wq, &pm2->check_मुख्य_thermal_prot_work);

	वापस 0;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_ovv_mngt(काष्ठा pm2xxx_अक्षरger *pm2, पूर्णांक val)
अणु
	dev_err(pm2->dev, "Overvoltage detected\n");
	pm2->flags.ovv = true;
	घातer_supply_changed(pm2->ac_chg.psy);

	/* Schedule a new HW failure check */
	queue_delayed_work(pm2->अक्षरger_wq, &pm2->check_hw_failure_work, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_wd_exp_mngt(काष्ठा pm2xxx_अक्षरger *pm2, पूर्णांक val)
अणु
	dev_dbg(pm2->dev , "20 minutes watchdog expired\n");

	pm2->ac.wd_expired = true;
	घातer_supply_changed(pm2->ac_chg.psy);

	वापस 0;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_vbat_lsig_mngt(काष्ठा pm2xxx_अक्षरger *pm2, पूर्णांक val)
अणु
	पूर्णांक ret;

	चयन (val) अणु
	हाल PM2XXX_INT1_ITVBATLOWR:
		dev_dbg(pm2->dev, "VBAT grows above VBAT_LOW level\n");
		/* Enable SW EOC ctrl */
		ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_SW_CTRL_REG,
							PM2XXX_SWCTRL_SW);
		अगर (ret < 0) अणु
			dev_err(pm2->dev, "%s pm2xxx write failed\n", __func__);
			वापस ret;
		पूर्ण
		अवरोध;

	हाल PM2XXX_INT1_ITVBATLOWF:
		dev_dbg(pm2->dev, "VBAT drops below VBAT_LOW level\n");
		/* Disable SW EOC ctrl */
		ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_SW_CTRL_REG,
							PM2XXX_SWCTRL_HW);
		अगर (ret < 0) अणु
			dev_err(pm2->dev, "%s pm2xxx write failed\n", __func__);
			वापस ret;
		पूर्ण
		अवरोध;

	शेष:
		dev_err(pm2->dev, "Unknown VBAT level\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_bat_disc_mngt(काष्ठा pm2xxx_अक्षरger *pm2, पूर्णांक val)
अणु
	dev_dbg(pm2->dev, "battery disconnected\n");

	वापस 0;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_detection(काष्ठा pm2xxx_अक्षरger *pm2, u8 *val)
अणु
	पूर्णांक ret;

	ret = pm2xxx_reg_पढ़ो(pm2, PM2XXX_SRCE_REG_INT2, val);

	अगर (ret < 0) अणु
		dev_err(pm2->dev, "Charger detection failed\n");
		जाओ out;
	पूर्ण

	*val &= (PM2XXX_INT2_S_ITVPWR1PLUG | PM2XXX_INT2_S_ITVPWR2PLUG);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_itv_pwr_plug_mngt(काष्ठा pm2xxx_अक्षरger *pm2, पूर्णांक val)
अणु

	पूर्णांक ret;
	u8 पढ़ो_val;

	/*
	 * Since we can't be sure that the events are received
	 * synchronously, we have the check अगर the मुख्य अक्षरger is
	 * connected by पढ़ोing the पूर्णांकerrupt source रेजिस्टर.
	 */
	ret = pm2xxx_अक्षरger_detection(pm2, &पढ़ो_val);

	अगर ((ret == 0) && पढ़ो_val) अणु
		pm2->ac.अक्षरger_connected = 1;
		pm2->ac_conn = true;
		queue_work(pm2->अक्षरger_wq, &pm2->ac_work);
	पूर्ण


	वापस ret;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_itv_pwr_unplug_mngt(काष्ठा pm2xxx_अक्षरger *pm2,
								पूर्णांक val)
अणु
	pm2->ac.अक्षरger_connected = 0;
	queue_work(pm2->अक्षरger_wq, &pm2->ac_work);

	वापस 0;
पूर्ण

अटल पूर्णांक pm2_पूर्णांक_reg0(व्योम *pm2_data, पूर्णांक val)
अणु
	काष्ठा pm2xxx_अक्षरger *pm2 = pm2_data;
	पूर्णांक ret = 0;

	अगर (val & PM2XXX_INT1_ITVBATLOWR) अणु
		ret = pm2xxx_अक्षरger_vbat_lsig_mngt(pm2,
						PM2XXX_INT1_ITVBATLOWR);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (val & PM2XXX_INT1_ITVBATLOWF) अणु
		ret = pm2xxx_अक्षरger_vbat_lsig_mngt(pm2,
						PM2XXX_INT1_ITVBATLOWF);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (val & PM2XXX_INT1_ITVBATDISCONNECT) अणु
		ret = pm2xxx_अक्षरger_bat_disc_mngt(pm2,
				PM2XXX_INT1_ITVBATDISCONNECT);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक pm2_पूर्णांक_reg1(व्योम *pm2_data, पूर्णांक val)
अणु
	काष्ठा pm2xxx_अक्षरger *pm2 = pm2_data;
	पूर्णांक ret = 0;

	अगर (val & (PM2XXX_INT2_ITVPWR1PLUG | PM2XXX_INT2_ITVPWR2PLUG)) अणु
		dev_dbg(pm2->dev , "Main charger plugged\n");
		ret = pm2xxx_अक्षरger_itv_pwr_plug_mngt(pm2, val &
			(PM2XXX_INT2_ITVPWR1PLUG | PM2XXX_INT2_ITVPWR2PLUG));
	पूर्ण

	अगर (val &
		(PM2XXX_INT2_ITVPWR1UNPLUG | PM2XXX_INT2_ITVPWR2UNPLUG)) अणु
		dev_dbg(pm2->dev , "Main charger unplugged\n");
		ret = pm2xxx_अक्षरger_itv_pwr_unplug_mngt(pm2, val &
						(PM2XXX_INT2_ITVPWR1UNPLUG |
						PM2XXX_INT2_ITVPWR2UNPLUG));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pm2_पूर्णांक_reg2(व्योम *pm2_data, पूर्णांक val)
अणु
	काष्ठा pm2xxx_अक्षरger *pm2 = pm2_data;
	पूर्णांक ret = 0;

	अगर (val & PM2XXX_INT3_ITAUTOTIMEOUTWD)
		ret = pm2xxx_अक्षरger_wd_exp_mngt(pm2, val);

	अगर (val & (PM2XXX_INT3_ITCHPRECHARGEWD |
				PM2XXX_INT3_ITCHCCWD | PM2XXX_INT3_ITCHCVWD)) अणु
		dev_dbg(pm2->dev,
			"Watchdog occurred for precharge, CC and CV charge\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pm2_पूर्णांक_reg3(व्योम *pm2_data, पूर्णांक val)
अणु
	काष्ठा pm2xxx_अक्षरger *pm2 = pm2_data;
	पूर्णांक ret = 0;

	अगर (val & (PM2XXX_INT4_ITCHARGINGON)) अणु
		dev_dbg(pm2->dev ,
			"charging operation has started\n");
	पूर्ण

	अगर (val & (PM2XXX_INT4_ITVRESUME)) अणु
		dev_dbg(pm2->dev,
			"battery discharged down to VResume threshold\n");
	पूर्ण

	अगर (val & (PM2XXX_INT4_ITBATTFULL)) अणु
		dev_dbg(pm2->dev , "battery fully detected\n");
	पूर्ण

	अगर (val & (PM2XXX_INT4_ITCVPHASE)) अणु
		dev_dbg(pm2->dev, "CV phase enter with 0.5C charging\n");
	पूर्ण

	अगर (val & (PM2XXX_INT4_ITVPWR2OVV | PM2XXX_INT4_ITVPWR1OVV)) अणु
		pm2->failure_हाल = VPWR_OVV;
		ret = pm2xxx_अक्षरger_ovv_mngt(pm2, val &
			(PM2XXX_INT4_ITVPWR2OVV | PM2XXX_INT4_ITVPWR1OVV));
		dev_dbg(pm2->dev, "VPWR/VSYSTEM overvoltage detected\n");
	पूर्ण

	अगर (val & (PM2XXX_INT4_S_ITBATTEMPCOLD |
				PM2XXX_INT4_S_ITBATTEMPHOT)) अणु
		ret = pm2xxx_अक्षरger_batt_therm_mngt(pm2, val &
			(PM2XXX_INT4_S_ITBATTEMPCOLD |
			PM2XXX_INT4_S_ITBATTEMPHOT));
		dev_dbg(pm2->dev, "BTEMP is too Low/High\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pm2_पूर्णांक_reg4(व्योम *pm2_data, पूर्णांक val)
अणु
	काष्ठा pm2xxx_अक्षरger *pm2 = pm2_data;
	पूर्णांक ret = 0;

	अगर (val & PM2XXX_INT5_ITVSYSTEMOVV) अणु
		pm2->failure_हाल = VSYSTEM_OVV;
		ret = pm2xxx_अक्षरger_ovv_mngt(pm2, val &
						PM2XXX_INT5_ITVSYSTEMOVV);
		dev_dbg(pm2->dev, "VSYSTEM overvoltage detected\n");
	पूर्ण

	अगर (val & (PM2XXX_INT5_ITTHERMALWARNINGFALL |
				PM2XXX_INT5_ITTHERMALWARNINGRISE |
				PM2XXX_INT5_ITTHERMALSHUTDOWNFALL |
				PM2XXX_INT5_ITTHERMALSHUTDOWNRISE)) अणु
		dev_dbg(pm2->dev, "BTEMP die temperature is too Low/High\n");
		ret = pm2xxx_अक्षरger_die_therm_mngt(pm2, val &
			(PM2XXX_INT5_ITTHERMALWARNINGFALL |
			PM2XXX_INT5_ITTHERMALWARNINGRISE |
			PM2XXX_INT5_ITTHERMALSHUTDOWNFALL |
			PM2XXX_INT5_ITTHERMALSHUTDOWNRISE));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pm2_पूर्णांक_reg5(व्योम *pm2_data, पूर्णांक val)
अणु
	काष्ठा pm2xxx_अक्षरger *pm2 = pm2_data;

	अगर (val & (PM2XXX_INT6_ITVPWR2DROP | PM2XXX_INT6_ITVPWR1DROP)) अणु
		dev_dbg(pm2->dev, "VMPWR drop to VBAT level\n");
	पूर्ण

	अगर (val & (PM2XXX_INT6_ITVPWR2VALIDRISE |
			PM2XXX_INT6_ITVPWR1VALIDRISE |
			PM2XXX_INT6_ITVPWR2VALIDFALL |
			PM2XXX_INT6_ITVPWR1VALIDFALL)) अणु
		dev_dbg(pm2->dev, "Falling/Rising edge on WPWR1/2\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t  pm2xxx_irq_पूर्णांक(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm2xxx_अक्षरger *pm2 = data;
	काष्ठा pm2xxx_पूर्णांकerrupts *पूर्णांकerrupt = pm2->pm2_पूर्णांक;
	पूर्णांक i;

	/* wake up the device */
	pm_runसमय_get_sync(pm2->dev);

	करो अणु
		क्रम (i = 0; i < PM2XXX_NUM_INT_REG; i++) अणु
			pm2xxx_reg_पढ़ो(pm2,
				pm2xxx_पूर्णांकerrupt_रेजिस्टरs[i],
				&(पूर्णांकerrupt->reg[i]));

			अगर (पूर्णांकerrupt->reg[i] > 0)
				पूर्णांकerrupt->handler[i](pm2, पूर्णांकerrupt->reg[i]);
		पूर्ण
	पूर्ण जबतक (gpio_get_value(pm2->pdata->gpio_irq_number) == 0);

	pm_runसमय_mark_last_busy(pm2->dev);
	pm_runसमय_put_स्वतःsuspend(pm2->dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_get_ac_cv(काष्ठा pm2xxx_अक्षरger *pm2)
अणु
	पूर्णांक ret = 0;
	u8 val;

	अगर (pm2->ac.अक्षरger_connected && pm2->ac.अक्षरger_online) अणु

		ret = pm2xxx_reg_पढ़ो(pm2, PM2XXX_SRCE_REG_INT4, &val);
		अगर (ret < 0) अणु
			dev_err(pm2->dev, "%s pm2xxx read failed\n", __func__);
			जाओ out;
		पूर्ण

		अगर (val & PM2XXX_INT4_S_ITCVPHASE)
			ret = PM2XXX_CONST_VOLT;
		अन्यथा
			ret = PM2XXX_CONST_CURR;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक pm2xxx_current_to_regval(पूर्णांक curr)
अणु
	पूर्णांक i;

	अगर (curr < pm2xxx_अक्षरger_current_map[0])
		वापस 0;

	क्रम (i = 1; i < ARRAY_SIZE(pm2xxx_अक्षरger_current_map); i++) अणु
		अगर (curr < pm2xxx_अक्षरger_current_map[i])
			वापस (i - 1);
	पूर्ण

	i = ARRAY_SIZE(pm2xxx_अक्षरger_current_map) - 1;
	अगर (curr == pm2xxx_अक्षरger_current_map[i])
		वापस i;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक pm2xxx_voltage_to_regval(पूर्णांक curr)
अणु
	पूर्णांक i;

	अगर (curr < pm2xxx_अक्षरger_voltage_map[0])
		वापस 0;

	क्रम (i = 1; i < ARRAY_SIZE(pm2xxx_अक्षरger_voltage_map); i++) अणु
		अगर (curr < pm2xxx_अक्षरger_voltage_map[i])
			वापस i - 1;
	पूर्ण

	i = ARRAY_SIZE(pm2xxx_अक्षरger_voltage_map) - 1;
	अगर (curr == pm2xxx_अक्षरger_voltage_map[i])
		वापस i;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_update_अक्षरger_current(काष्ठा ux500_अक्षरger *अक्षरger,
		पूर्णांक ich_out)
अणु
	पूर्णांक ret;
	पूर्णांक curr_index;
	काष्ठा pm2xxx_अक्षरger *pm2;
	u8 val;

	अगर (अक्षरger->psy->desc->type == POWER_SUPPLY_TYPE_MAINS)
		pm2 = to_pm2xxx_अक्षरger_ac_device_info(अक्षरger);
	अन्यथा
		वापस -ENXIO;

	curr_index = pm2xxx_current_to_regval(ich_out);
	अगर (curr_index < 0) अणु
		dev_err(pm2->dev,
			"Charger current too high, charging not started\n");
		वापस -ENXIO;
	पूर्ण

	ret = pm2xxx_reg_पढ़ो(pm2, PM2XXX_BATT_CTRL_REG6, &val);
	अगर (ret >= 0) अणु
		val &= ~PM2XXX_सूची_CH_CC_CURRENT_MASK;
		val |= curr_index;
		ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_CTRL_REG6, val);
		अगर (ret < 0) अणु
			dev_err(pm2->dev,
				"%s write failed\n", __func__);
		पूर्ण
	पूर्ण
	अन्यथा
		dev_err(pm2->dev, "%s read failed\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_ac_get_property(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	काष्ठा pm2xxx_अक्षरger *pm2;

	pm2 = to_pm2xxx_अक्षरger_ac_device_info(psy_to_ux500_अक्षरger(psy));

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_HEALTH:
		अगर (pm2->flags.मुख्यextchnotok)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		अन्यथा अगर (pm2->ac.wd_expired)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_DEAD;
		अन्यथा अगर (pm2->flags.मुख्य_thermal_prot)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		अन्यथा अगर (pm2->flags.ovv)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = pm2->ac.अक्षरger_online;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = pm2->ac.अक्षरger_connected;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		pm2->ac.cv_active = pm2xxx_अक्षरger_get_ac_cv(pm2);
		val->पूर्णांकval = pm2->ac.cv_active;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरging_init(काष्ठा pm2xxx_अक्षरger *pm2)
अणु
	पूर्णांक ret = 0;

	/* enable CC and CV watchकरोg */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_CTRL_REG3,
		(PM2XXX_CH_WD_CV_PHASE_60MIN | PM2XXX_CH_WD_CC_PHASE_60MIN));
	अगर( ret < 0)
		वापस ret;

	/* enable preअक्षरge watchकरोg */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_CTRL_REG4,
					PM2XXX_CH_WD_PRECH_PHASE_60MIN);

	/* Disable स्वतः समयout */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_CTRL_REG5,
					PM2XXX_CH_WD_AUTO_TIMEOUT_20MIN);

	/*
     * EOC current level = 100mA
	 * Preअक्षरge current level = 100mA
	 * CC current level = 1000mA
	 */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_CTRL_REG6,
		(PM2XXX_सूची_CH_CC_CURRENT_1000MA |
		PM2XXX_CH_PRECH_CURRENT_100MA |
		PM2XXX_CH_EOC_CURRENT_100MA));

	/*
     * reअक्षरge threshold = 3.8V
	 * Preअक्षरge to CC threshold = 2.9V
	 */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_CTRL_REG7,
		(PM2XXX_CH_PRECH_VOL_2_9 | PM2XXX_CH_VRESUME_VOL_3_8));

	/* भग्न voltage अक्षरger level = 4.2V */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_CTRL_REG8,
		PM2XXX_CH_VOLT_4_2);

	/* Voltage drop between VBAT and VSYS in HW अक्षरging = 300mV */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_CTRL_REG9,
		(PM2XXX_CH_150MV_DROP_300MV | PM2XXX_CHARCHING_INFO_DIS |
		PM2XXX_CH_CC_REDUCED_CURRENT_IDENT |
		PM2XXX_CH_CC_MODEDROP_DIS));

	/* Input अक्षरger level of over voltage = 10V */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_INP_VOLT_VPWR2,
					PM2XXX_VPWR2_OVV_10);
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_INP_VOLT_VPWR1,
					PM2XXX_VPWR1_OVV_10);

	/* Input अक्षरger drop */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_INP_DROP_VPWR2,
		(PM2XXX_VPWR2_HW_OPT_DIS | PM2XXX_VPWR2_VALID_DIS |
		PM2XXX_VPWR2_DROP_DIS));
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_INP_DROP_VPWR1,
		(PM2XXX_VPWR1_HW_OPT_DIS | PM2XXX_VPWR1_VALID_DIS |
		PM2XXX_VPWR1_DROP_DIS));

	/* Disable battery low monitoring */
	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_LOW_LEV_COMP_REG,
		PM2XXX_VBAT_LOW_MONITORING_ENA);

	वापस ret;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_ac_en(काष्ठा ux500_अक्षरger *अक्षरger,
	पूर्णांक enable, पूर्णांक vset, पूर्णांक iset)
अणु
	पूर्णांक ret;
	पूर्णांक volt_index;
	पूर्णांक curr_index;
	u8 val;

	काष्ठा pm2xxx_अक्षरger *pm2 = to_pm2xxx_अक्षरger_ac_device_info(अक्षरger);

	अगर (enable) अणु
		अगर (!pm2->ac.अक्षरger_connected) अणु
			dev_dbg(pm2->dev, "AC charger not connected\n");
			वापस -ENXIO;
		पूर्ण

		dev_dbg(pm2->dev, "Enable AC: %dmV %dmA\n", vset, iset);
		अगर (!pm2->vddadc_en_ac) अणु
			ret = regulator_enable(pm2->regu);
			अगर (ret)
				dev_warn(pm2->dev,
					"Failed to enable vddadc regulator\n");
			अन्यथा
				pm2->vddadc_en_ac = true;
		पूर्ण

		ret = pm2xxx_अक्षरging_init(pm2);
		अगर (ret < 0) अणु
			dev_err(pm2->dev, "%s charging init failed\n",
					__func__);
			जाओ error_occured;
		पूर्ण

		volt_index = pm2xxx_voltage_to_regval(vset);
		curr_index = pm2xxx_current_to_regval(iset);

		अगर (volt_index < 0 || curr_index < 0) अणु
			dev_err(pm2->dev,
				"Charger voltage or current too high, "
				"charging not started\n");
			वापस -ENXIO;
		पूर्ण

		ret = pm2xxx_reg_पढ़ो(pm2, PM2XXX_BATT_CTRL_REG8, &val);
		अगर (ret < 0) अणु
			dev_err(pm2->dev, "%s pm2xxx read failed\n", __func__);
			जाओ error_occured;
		पूर्ण
		val &= ~PM2XXX_CH_VOLT_MASK;
		val |= volt_index;
		ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_CTRL_REG8, val);
		अगर (ret < 0) अणु
			dev_err(pm2->dev, "%s pm2xxx write failed\n", __func__);
			जाओ error_occured;
		पूर्ण

		ret = pm2xxx_reg_पढ़ो(pm2, PM2XXX_BATT_CTRL_REG6, &val);
		अगर (ret < 0) अणु
			dev_err(pm2->dev, "%s pm2xxx read failed\n", __func__);
			जाओ error_occured;
		पूर्ण
		val &= ~PM2XXX_सूची_CH_CC_CURRENT_MASK;
		val |= curr_index;
		ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_CTRL_REG6, val);
		अगर (ret < 0) अणु
			dev_err(pm2->dev, "%s pm2xxx write failed\n", __func__);
			जाओ error_occured;
		पूर्ण

		अगर (!pm2->bat->enable_overshoot) अणु
			ret = pm2xxx_reg_पढ़ो(pm2, PM2XXX_LED_CTRL_REG, &val);
			अगर (ret < 0) अणु
				dev_err(pm2->dev, "%s pm2xxx read failed\n",
								__func__);
				जाओ error_occured;
			पूर्ण
			val |= PM2XXX_ANTI_OVERSHOOT_EN;
			ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_LED_CTRL_REG, val);
			अगर (ret < 0) अणु
				dev_err(pm2->dev, "%s pm2xxx write failed\n",
								__func__);
				जाओ error_occured;
			पूर्ण
		पूर्ण

		ret = pm2xxx_अक्षरging_enable_mngt(pm2);
		अगर (ret < 0) अणु
			dev_err(pm2->dev, "Failed to enable"
						"pm2xxx ac charger\n");
			जाओ error_occured;
		पूर्ण

		pm2->ac.अक्षरger_online = 1;
	पूर्ण अन्यथा अणु
		pm2->ac.अक्षरger_online = 0;
		pm2->ac.wd_expired = false;

		/* Disable regulator अगर enabled */
		अगर (pm2->vddadc_en_ac) अणु
			regulator_disable(pm2->regu);
			pm2->vddadc_en_ac = false;
		पूर्ण

		ret = pm2xxx_अक्षरging_disable_mngt(pm2);
		अगर (ret < 0) अणु
			dev_err(pm2->dev, "failed to disable"
						"pm2xxx ac charger\n");
			जाओ error_occured;
		पूर्ण

		dev_dbg(pm2->dev, "PM2301: " "Disabled AC charging\n");
	पूर्ण
	घातer_supply_changed(pm2->ac_chg.psy);

error_occured:
	वापस ret;
पूर्ण

अटल पूर्णांक pm2xxx_अक्षरger_watchकरोg_kick(काष्ठा ux500_अक्षरger *अक्षरger)
अणु
	पूर्णांक ret;
	काष्ठा pm2xxx_अक्षरger *pm2;

	अगर (अक्षरger->psy->desc->type == POWER_SUPPLY_TYPE_MAINS)
		pm2 = to_pm2xxx_अक्षरger_ac_device_info(अक्षरger);
	अन्यथा
		वापस -ENXIO;

	ret = pm2xxx_reg_ग_लिखो(pm2, PM2XXX_BATT_WD_KICK, WD_TIMER);
	अगर (ret)
		dev_err(pm2->dev, "Failed to kick WD!\n");

	वापस ret;
पूर्ण

अटल व्योम pm2xxx_अक्षरger_ac_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pm2xxx_अक्षरger *pm2 = container_of(work,
		काष्ठा pm2xxx_अक्षरger, ac_work);


	घातer_supply_changed(pm2->ac_chg.psy);
	sysfs_notअगरy(&pm2->ac_chg.psy->dev.kobj, शून्य, "present");
पूर्ण;

अटल व्योम pm2xxx_अक्षरger_check_hw_failure_work(काष्ठा work_काष्ठा *work)
अणु
	u8 reg_value;

	काष्ठा pm2xxx_अक्षरger *pm2 = container_of(work,
		काष्ठा pm2xxx_अक्षरger, check_hw_failure_work.work);

	अगर (pm2->flags.ovv) अणु
		pm2xxx_reg_पढ़ो(pm2, PM2XXX_SRCE_REG_INT4, &reg_value);

		अगर (!(reg_value & (PM2XXX_INT4_S_ITVPWR1OVV |
					PM2XXX_INT4_S_ITVPWR2OVV))) अणु
			pm2->flags.ovv = false;
			घातer_supply_changed(pm2->ac_chg.psy);
		पूर्ण
	पूर्ण

	/* If we still have a failure, schedule a new check */
	अगर (pm2->flags.ovv) अणु
		queue_delayed_work(pm2->अक्षरger_wq,
			&pm2->check_hw_failure_work, round_jअगरfies(HZ));
	पूर्ण
पूर्ण

अटल व्योम pm2xxx_अक्षरger_check_मुख्य_thermal_prot_work(
	काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	u8 val;

	काष्ठा pm2xxx_अक्षरger *pm2 = container_of(work, काष्ठा pm2xxx_अक्षरger,
					check_मुख्य_thermal_prot_work);

	/* Check अगर die temp warning is still active */
	ret = pm2xxx_reg_पढ़ो(pm2, PM2XXX_SRCE_REG_INT5, &val);
	अगर (ret < 0) अणु
		dev_err(pm2->dev, "%s pm2xxx read failed\n", __func__);
		वापस;
	पूर्ण
	अगर (val & (PM2XXX_INT5_S_ITTHERMALWARNINGRISE
			| PM2XXX_INT5_S_ITTHERMALSHUTDOWNRISE))
		pm2->flags.मुख्य_thermal_prot = true;
	अन्यथा अगर (val & (PM2XXX_INT5_S_ITTHERMALWARNINGFALL
				| PM2XXX_INT5_S_ITTHERMALSHUTDOWNFALL))
		pm2->flags.मुख्य_thermal_prot = false;

	घातer_supply_changed(pm2->ac_chg.psy);
पूर्ण

अटल काष्ठा pm2xxx_पूर्णांकerrupts pm2xxx_पूर्णांक = अणु
	.handler[0] = pm2_पूर्णांक_reg0,
	.handler[1] = pm2_पूर्णांक_reg1,
	.handler[2] = pm2_पूर्णांक_reg2,
	.handler[3] = pm2_पूर्णांक_reg3,
	.handler[4] = pm2_पूर्णांक_reg4,
	.handler[5] = pm2_पूर्णांक_reg5,
पूर्ण;

अटल काष्ठा pm2xxx_irq pm2xxx_अक्षरger_irq[] = अणु
	अणु"PM2XXX_IRQ_INT", pm2xxx_irq_पूर्णांकपूर्ण,
पूर्ण;

अटल पूर्णांक __maybe_unused pm2xxx_wall_अक्षरger_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c_client = to_i2c_client(dev);
	काष्ठा pm2xxx_अक्षरger *pm2;

	pm2 =  (काष्ठा pm2xxx_अक्षरger *)i2c_get_clientdata(i2c_client);
	set_lpn_pin(pm2);

	/* If we still have a HW failure, schedule a new check */
	अगर (pm2->flags.ovv)
		queue_delayed_work(pm2->अक्षरger_wq,
				&pm2->check_hw_failure_work, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pm2xxx_wall_अक्षरger_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c_client = to_i2c_client(dev);
	काष्ठा pm2xxx_अक्षरger *pm2;

	pm2 =  (काष्ठा pm2xxx_अक्षरger *)i2c_get_clientdata(i2c_client);
	clear_lpn_pin(pm2);

	/* Cancel any pending HW failure check */
	अगर (delayed_work_pending(&pm2->check_hw_failure_work))
		cancel_delayed_work(&pm2->check_hw_failure_work);

	flush_work(&pm2->ac_work);
	flush_work(&pm2->check_मुख्य_thermal_prot_work);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pm2xxx_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *pm2xxx_i2c_client = to_i2c_client(dev);
	काष्ठा pm2xxx_अक्षरger *pm2;

	pm2 = (काष्ठा pm2xxx_अक्षरger *)i2c_get_clientdata(pm2xxx_i2c_client);
	clear_lpn_pin(pm2);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pm2xxx_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *pm2xxx_i2c_client = to_i2c_client(dev);
	काष्ठा pm2xxx_अक्षरger *pm2;

	pm2 = (काष्ठा pm2xxx_अक्षरger *)i2c_get_clientdata(pm2xxx_i2c_client);

	अगर (gpio_is_valid(pm2->lpn_pin) && gpio_get_value(pm2->lpn_pin) == 0)
		set_lpn_pin(pm2);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pm2xxx_pm_ops __maybe_unused = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm2xxx_wall_अक्षरger_suspend,
		pm2xxx_wall_अक्षरger_resume)
	SET_RUNTIME_PM_OPS(pm2xxx_runसमय_suspend, pm2xxx_runसमय_resume, शून्य)
पूर्ण;

अटल पूर्णांक pm2xxx_wall_अक्षरger_probe(काष्ठा i2c_client *i2c_client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pm2xxx_platक्रमm_data *pl_data = i2c_client->dev.platक्रमm_data;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा pm2xxx_अक्षरger *pm2;
	पूर्णांक ret = 0;
	u8 val;
	पूर्णांक i;

	अगर (!pl_data) अणु
		dev_err(&i2c_client->dev, "No platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	pm2 = kzalloc(माप(काष्ठा pm2xxx_अक्षरger), GFP_KERNEL);
	अगर (!pm2) अणु
		dev_err(&i2c_client->dev, "pm2xxx_charger allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	/* get parent data */
	pm2->dev = &i2c_client->dev;

	pm2->pm2_पूर्णांक = &pm2xxx_पूर्णांक;

	/* get अक्षरger spcअगरic platक्रमm data */
	अगर (!pl_data->wall_अक्षरger) अणु
		dev_err(pm2->dev, "no charger platform data supplied\n");
		ret = -EINVAL;
		जाओ मुक्त_device_info;
	पूर्ण

	pm2->pdata = pl_data->wall_अक्षरger;

	/* get battery specअगरic platक्रमm data */
	अगर (!pl_data->battery) अणु
		dev_err(pm2->dev, "no battery platform data supplied\n");
		ret = -EINVAL;
		जाओ मुक्त_device_info;
	पूर्ण

	pm2->bat = pl_data->battery;

	अगर (!i2c_check_functionality(i2c_client->adapter,
			I2C_FUNC_SMBUS_BYTE_DATA |
			I2C_FUNC_SMBUS_READ_WORD_DATA)) अणु
		ret = -ENODEV;
		dev_info(pm2->dev, "pm2301 i2c_check_functionality failed\n");
		जाओ मुक्त_device_info;
	पूर्ण

	pm2->config.pm2xxx_i2c = i2c_client;
	pm2->config.pm2xxx_id = (काष्ठा i2c_device_id *) id;
	i2c_set_clientdata(i2c_client, pm2);

	/* AC supply */
	/* घातer_supply base class */
	pm2->ac_chg_desc.name = pm2->pdata->label;
	pm2->ac_chg_desc.type = POWER_SUPPLY_TYPE_MAINS;
	pm2->ac_chg_desc.properties = pm2xxx_अक्षरger_ac_props;
	pm2->ac_chg_desc.num_properties = ARRAY_SIZE(pm2xxx_अक्षरger_ac_props);
	pm2->ac_chg_desc.get_property = pm2xxx_अक्षरger_ac_get_property;

	psy_cfg.supplied_to = pm2->pdata->supplied_to;
	psy_cfg.num_supplicants = pm2->pdata->num_supplicants;
	/* pm2xxx_अक्षरger sub-class */
	pm2->ac_chg.ops.enable = &pm2xxx_अक्षरger_ac_en;
	pm2->ac_chg.ops.kick_wd = &pm2xxx_अक्षरger_watchकरोg_kick;
	pm2->ac_chg.ops.update_curr = &pm2xxx_अक्षरger_update_अक्षरger_current;
	pm2->ac_chg.max_out_volt = pm2xxx_अक्षरger_voltage_map[
		ARRAY_SIZE(pm2xxx_अक्षरger_voltage_map) - 1];
	pm2->ac_chg.max_out_curr = pm2xxx_अक्षरger_current_map[
		ARRAY_SIZE(pm2xxx_अक्षरger_current_map) - 1];
	pm2->ac_chg.wdt_refresh = WD_KICK_INTERVAL;
	pm2->ac_chg.enabled = true;
	pm2->ac_chg.बाह्यal = true;

	/* Create a work queue क्रम the अक्षरger */
	pm2->अक्षरger_wq = alloc_ordered_workqueue("pm2xxx_charger_wq",
						  WQ_MEM_RECLAIM);
	अगर (pm2->अक्षरger_wq == शून्य) अणु
		ret = -ENOMEM;
		dev_err(pm2->dev, "failed to create work queue\n");
		जाओ मुक्त_device_info;
	पूर्ण

	/* Init work क्रम अक्षरger detection */
	INIT_WORK(&pm2->ac_work, pm2xxx_अक्षरger_ac_work);

	/* Init work क्रम checking HW status */
	INIT_WORK(&pm2->check_मुख्य_thermal_prot_work,
		pm2xxx_अक्षरger_check_मुख्य_thermal_prot_work);

	/* Init work क्रम HW failure check */
	INIT_DEFERRABLE_WORK(&pm2->check_hw_failure_work,
		pm2xxx_अक्षरger_check_hw_failure_work);

	/*
	 * VDD ADC supply needs to be enabled from this driver when there
	 * is a अक्षरger connected to aव्योम erroneous BTEMP_HIGH/LOW
	 * पूर्णांकerrupts during अक्षरging
	 */
	pm2->regu = regulator_get(pm2->dev, "vddadc");
	अगर (IS_ERR(pm2->regu)) अणु
		ret = PTR_ERR(pm2->regu);
		dev_err(pm2->dev, "failed to get vddadc regulator\n");
		जाओ मुक्त_अक्षरger_wq;
	पूर्ण

	/* Register AC अक्षरger class */
	pm2->ac_chg.psy = घातer_supply_रेजिस्टर(pm2->dev, &pm2->ac_chg_desc,
						&psy_cfg);
	अगर (IS_ERR(pm2->ac_chg.psy)) अणु
		dev_err(pm2->dev, "failed to register AC charger\n");
		ret = PTR_ERR(pm2->ac_chg.psy);
		जाओ मुक्त_regulator;
	पूर्ण

	/* Register पूर्णांकerrupts */
	ret = request_thपढ़ोed_irq(gpio_to_irq(pm2->pdata->gpio_irq_number),
				शून्य,
				pm2xxx_अक्षरger_irq[0].isr,
				pm2->pdata->irq_type | IRQF_ONESHOT,
				pm2xxx_अक्षरger_irq[0].name, pm2);

	अगर (ret != 0) अणु
		dev_err(pm2->dev, "failed to request %s IRQ %d: %d\n",
		pm2xxx_अक्षरger_irq[0].name,
			gpio_to_irq(pm2->pdata->gpio_irq_number), ret);
		जाओ unरेजिस्टर_pm2xxx_अक्षरger;
	पूर्ण

	ret = pm_runसमय_set_active(pm2->dev);
	अगर (ret)
		dev_err(pm2->dev, "set active Error\n");

	pm_runसमय_enable(pm2->dev);
	pm_runसमय_set_स्वतःsuspend_delay(pm2->dev, PM2XXX_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(pm2->dev);
	pm_runसमय_resume(pm2->dev);

	/* pm पूर्णांकerrupt can wake up प्रणाली */
	ret = enable_irq_wake(gpio_to_irq(pm2->pdata->gpio_irq_number));
	अगर (ret) अणु
		dev_err(pm2->dev, "failed to set irq wake\n");
		जाओ unरेजिस्टर_pm2xxx_पूर्णांकerrupt;
	पूर्ण

	mutex_init(&pm2->lock);

	अगर (gpio_is_valid(pm2->pdata->lpn_gpio)) अणु
		/* get lpn GPIO from platक्रमm data */
		pm2->lpn_pin = pm2->pdata->lpn_gpio;

		/*
		 * Charger detection mechanism requires pulling up the LPN pin
		 * जबतक i2c communication अगर Charger is not connected
		 * LPN pin of PM2301 is GPIO60 of AB9540
		 */
		ret = gpio_request(pm2->lpn_pin, "pm2301_lpm_gpio");

		अगर (ret < 0) अणु
			dev_err(pm2->dev, "pm2301_lpm_gpio request failed\n");
			जाओ disable_pm2_irq_wake;
		पूर्ण
		ret = gpio_direction_output(pm2->lpn_pin, 0);
		अगर (ret < 0) अणु
			dev_err(pm2->dev, "pm2301_lpm_gpio direction failed\n");
			जाओ मुक्त_gpio;
		पूर्ण
		set_lpn_pin(pm2);
	पूर्ण

	/* पढ़ो  पूर्णांकerrupt रेजिस्टरs */
	क्रम (i = 0; i < PM2XXX_NUM_INT_REG; i++)
		pm2xxx_reg_पढ़ो(pm2,
			pm2xxx_पूर्णांकerrupt_रेजिस्टरs[i],
			&val);

	ret = pm2xxx_अक्षरger_detection(pm2, &val);

	अगर ((ret == 0) && val) अणु
		pm2->ac.अक्षरger_connected = 1;
		ab8500_override_turn_on_stat(~AB8500_POW_KEY_1_ON,
					     AB8500_MAIN_CH_DET);
		pm2->ac_conn = true;
		घातer_supply_changed(pm2->ac_chg.psy);
		sysfs_notअगरy(&pm2->ac_chg.psy->dev.kobj, शून्य, "present");
	पूर्ण

	वापस 0;

मुक्त_gpio:
	अगर (gpio_is_valid(pm2->lpn_pin))
		gpio_मुक्त(pm2->lpn_pin);
disable_pm2_irq_wake:
	disable_irq_wake(gpio_to_irq(pm2->pdata->gpio_irq_number));
unरेजिस्टर_pm2xxx_पूर्णांकerrupt:
	/* disable पूर्णांकerrupt */
	मुक्त_irq(gpio_to_irq(pm2->pdata->gpio_irq_number), pm2);
unरेजिस्टर_pm2xxx_अक्षरger:
	/* unरेजिस्टर घातer supply */
	घातer_supply_unरेजिस्टर(pm2->ac_chg.psy);
मुक्त_regulator:
	/* disable the regulator */
	regulator_put(pm2->regu);
मुक्त_अक्षरger_wq:
	destroy_workqueue(pm2->अक्षरger_wq);
मुक्त_device_info:
	kमुक्त(pm2);

	वापस ret;
पूर्ण

अटल पूर्णांक pm2xxx_wall_अक्षरger_हटाओ(काष्ठा i2c_client *i2c_client)
अणु
	काष्ठा pm2xxx_अक्षरger *pm2 = i2c_get_clientdata(i2c_client);

	/* Disable pm_runसमय */
	pm_runसमय_disable(pm2->dev);
	/* Disable AC अक्षरging */
	pm2xxx_अक्षरger_ac_en(&pm2->ac_chg, false, 0, 0);

	/* Disable wake by pm पूर्णांकerrupt */
	disable_irq_wake(gpio_to_irq(pm2->pdata->gpio_irq_number));

	/* Disable पूर्णांकerrupts */
	मुक्त_irq(gpio_to_irq(pm2->pdata->gpio_irq_number), pm2);

	/* Delete the work queue */
	destroy_workqueue(pm2->अक्षरger_wq);

	flush_scheduled_work();

	/* disable the regulator */
	regulator_put(pm2->regu);

	घातer_supply_unरेजिस्टर(pm2->ac_chg.psy);

	अगर (gpio_is_valid(pm2->lpn_pin))
		gpio_मुक्त(pm2->lpn_pin);

	kमुक्त(pm2);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pm2xxx_id[] = अणु
	अणु "pm2301", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, pm2xxx_id);

अटल काष्ठा i2c_driver pm2xxx_अक्षरger_driver = अणु
	.probe = pm2xxx_wall_अक्षरger_probe,
	.हटाओ = pm2xxx_wall_अक्षरger_हटाओ,
	.driver = अणु
		.name = "pm2xxx-wall_charger",
		.pm = IS_ENABLED(CONFIG_PM) ? &pm2xxx_pm_ops : शून्य,
	पूर्ण,
	.id_table = pm2xxx_id,
पूर्ण;

अटल पूर्णांक __init pm2xxx_अक्षरger_init(व्योम)
अणु
	वापस i2c_add_driver(&pm2xxx_अक्षरger_driver);
पूर्ण

अटल व्योम __निकास pm2xxx_अक्षरger_निकास(व्योम)
अणु
	i2c_del_driver(&pm2xxx_अक्षरger_driver);
पूर्ण

device_initcall_sync(pm2xxx_अक्षरger_init);
module_निकास(pm2xxx_अक्षरger_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Rajkumar kasirajan, Olivier Launay");
MODULE_DESCRIPTION("PM2xxx charger management driver");
