<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * nvec_घातer: घातer supply driver क्रम a NVIDIA compliant embedded controller
 *
 * Copyright (C) 2011 The AC100 Kernel Team <ac100@lists.launchpad.net>
 *
 * Authors:  Ilya Petrov <ilya.muromec@gmail.com>
 *           Marc Dietrich <marvin24@gmx.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>

#समावेश "nvec.h"

#घोषणा GET_SYSTEM_STATUS 0x00

काष्ठा nvec_घातer अणु
	काष्ठा notअगरier_block notअगरier;
	काष्ठा delayed_work poller;
	काष्ठा nvec_chip *nvec;
	पूर्णांक on;
	पूर्णांक bat_present;
	पूर्णांक bat_status;
	पूर्णांक bat_voltage_now;
	पूर्णांक bat_current_now;
	पूर्णांक bat_current_avg;
	पूर्णांक समय_reमुख्य;
	पूर्णांक अक्षरge_full_design;
	पूर्णांक अक्षरge_last_full;
	पूर्णांक critical_capacity;
	पूर्णांक capacity_reमुख्य;
	पूर्णांक bat_temperature;
	पूर्णांक bat_cap;
	पूर्णांक bat_type_क्रमागत;
	अक्षर bat_manu[30];
	अक्षर bat_model[30];
	अक्षर bat_type[30];
पूर्ण;

क्रमागत अणु
	SLOT_STATUS,
	VOLTAGE,
	TIME_REMAINING,
	CURRENT,
	AVERAGE_CURRENT,
	AVERAGING_TIME_INTERVAL,
	CAPACITY_REMAINING,
	LAST_FULL_CHARGE_CAPACITY,
	DESIGN_CAPACITY,
	CRITICAL_CAPACITY,
	TEMPERATURE,
	MANUFACTURER,
	MODEL,
	TYPE,
पूर्ण;

क्रमागत अणु
	AC,
	BAT,
पूर्ण;

काष्ठा bat_response अणु
	u8 event_type;
	u8 length;
	u8 sub_type;
	u8 status;
	/* payload */
	जोड़ अणु
		अक्षर plc[30];
		u16 plu;
		s16 pls;
	पूर्ण;
पूर्ण;

अटल काष्ठा घातer_supply *nvec_bat_psy;
अटल काष्ठा घातer_supply *nvec_psy;

अटल पूर्णांक nvec_घातer_notअगरier(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ event_type, व्योम *data)
अणु
	काष्ठा nvec_घातer *घातer =
	    container_of(nb, काष्ठा nvec_घातer, notअगरier);
	काष्ठा bat_response *res = data;

	अगर (event_type != NVEC_SYS)
		वापस NOTIFY_DONE;

	अगर (res->sub_type == 0) अणु
		अगर (घातer->on != res->plu) अणु
			घातer->on = res->plu;
			घातer_supply_changed(nvec_psy);
		पूर्ण
		वापस NOTIFY_STOP;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल स्थिर पूर्णांक bat_init[] = अणु
	LAST_FULL_CHARGE_CAPACITY, DESIGN_CAPACITY, CRITICAL_CAPACITY,
	MANUFACTURER, MODEL, TYPE,
पूर्ण;

अटल व्योम get_bat_mfg_data(काष्ठा nvec_घातer *घातer)
अणु
	पूर्णांक i;
	अक्षर buf[] = अणु NVEC_BAT, SLOT_STATUS पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(bat_init); i++) अणु
		buf[1] = bat_init[i];
		nvec_ग_लिखो_async(घातer->nvec, buf, 2);
	पूर्ण
पूर्ण

अटल पूर्णांक nvec_घातer_bat_notअगरier(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ event_type, व्योम *data)
अणु
	काष्ठा nvec_घातer *घातer =
	    container_of(nb, काष्ठा nvec_घातer, notअगरier);
	काष्ठा bat_response *res = data;
	पूर्णांक status_changed = 0;

	अगर (event_type != NVEC_BAT)
		वापस NOTIFY_DONE;

	चयन (res->sub_type) अणु
	हाल SLOT_STATUS:
		अगर (res->plc[0] & 1) अणु
			अगर (घातer->bat_present == 0) अणु
				status_changed = 1;
				get_bat_mfg_data(घातer);
			पूर्ण

			घातer->bat_present = 1;

			चयन ((res->plc[0] >> 1) & 3) अणु
			हाल 0:
				घातer->bat_status =
				    POWER_SUPPLY_STATUS_NOT_CHARGING;
				अवरोध;
			हाल 1:
				घातer->bat_status =
				    POWER_SUPPLY_STATUS_CHARGING;
				अवरोध;
			हाल 2:
				घातer->bat_status =
				    POWER_SUPPLY_STATUS_DISCHARGING;
				अवरोध;
			शेष:
				घातer->bat_status = POWER_SUPPLY_STATUS_UNKNOWN;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (घातer->bat_present == 1)
				status_changed = 1;

			घातer->bat_present = 0;
			घातer->bat_status = POWER_SUPPLY_STATUS_UNKNOWN;
		पूर्ण
		घातer->bat_cap = res->plc[1];
		अगर (status_changed)
			घातer_supply_changed(nvec_bat_psy);
		अवरोध;
	हाल VOLTAGE:
		घातer->bat_voltage_now = res->plu * 1000;
		अवरोध;
	हाल TIME_REMAINING:
		घातer->समय_reमुख्य = res->plu * 3600;
		अवरोध;
	हाल CURRENT:
		घातer->bat_current_now = res->pls * 1000;
		अवरोध;
	हाल AVERAGE_CURRENT:
		घातer->bat_current_avg = res->pls * 1000;
		अवरोध;
	हाल CAPACITY_REMAINING:
		घातer->capacity_reमुख्य = res->plu * 1000;
		अवरोध;
	हाल LAST_FULL_CHARGE_CAPACITY:
		घातer->अक्षरge_last_full = res->plu * 1000;
		अवरोध;
	हाल DESIGN_CAPACITY:
		घातer->अक्षरge_full_design = res->plu * 1000;
		अवरोध;
	हाल CRITICAL_CAPACITY:
		घातer->critical_capacity = res->plu * 1000;
		अवरोध;
	हाल TEMPERATURE:
		घातer->bat_temperature = res->plu - 2732;
		अवरोध;
	हाल MANUFACTURER:
		स_नकल(घातer->bat_manu, &res->plc, res->length - 2);
		घातer->bat_model[res->length - 2] = '\0';
		अवरोध;
	हाल MODEL:
		स_नकल(घातer->bat_model, &res->plc, res->length - 2);
		घातer->bat_model[res->length - 2] = '\0';
		अवरोध;
	हाल TYPE:
		स_नकल(घातer->bat_type, &res->plc, res->length - 2);
		घातer->bat_type[res->length - 2] = '\0';
		/*
		 * This dअगरfers a little from the spec fill in more अगर you find
		 * some.
		 */
		अगर (!म_भेदन(घातer->bat_type, "Li", 30))
			घातer->bat_type_क्रमागत = POWER_SUPPLY_TECHNOLOGY_LION;
		अन्यथा
			घातer->bat_type_क्रमागत = POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
		अवरोध;
	शेष:
		वापस NOTIFY_STOP;
	पूर्ण

	वापस NOTIFY_STOP;
पूर्ण

अटल पूर्णांक nvec_घातer_get_property(काष्ठा घातer_supply *psy,
				   क्रमागत घातer_supply_property psp,
				   जोड़ घातer_supply_propval *val)
अणु
	काष्ठा nvec_घातer *घातer = dev_get_drvdata(psy->dev.parent);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = घातer->on;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nvec_battery_get_property(काष्ठा घातer_supply *psy,
				     क्रमागत घातer_supply_property psp,
				     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा nvec_घातer *घातer = dev_get_drvdata(psy->dev.parent);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = घातer->bat_status;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = घातer->bat_cap;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = घातer->bat_present;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = घातer->bat_voltage_now;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		val->पूर्णांकval = घातer->bat_current_now;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		val->पूर्णांकval = घातer->bat_current_avg;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW:
		val->पूर्णांकval = घातer->समय_reमुख्य;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->पूर्णांकval = घातer->अक्षरge_full_design;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		val->पूर्णांकval = घातer->अक्षरge_last_full;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_EMPTY:
		val->पूर्णांकval = घातer->critical_capacity;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		val->पूर्णांकval = घातer->capacity_reमुख्य;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = घातer->bat_temperature;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = घातer->bat_manu;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = घातer->bat_model;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = घातer->bat_type_क्रमागत;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property nvec_घातer_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल क्रमागत घातer_supply_property nvec_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
#अगर_घोषित EC_FULL_DIAG
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
#पूर्ण_अगर
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_EMPTY,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_TECHNOLOGY,
पूर्ण;

अटल अक्षर *nvec_घातer_supplied_to[] = अणु
	"battery",
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc nvec_bat_psy_desc = अणु
	.name = "battery",
	.type = POWER_SUPPLY_TYPE_BATTERY,
	.properties = nvec_battery_props,
	.num_properties = ARRAY_SIZE(nvec_battery_props),
	.get_property = nvec_battery_get_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc nvec_psy_desc = अणु
	.name = "ac",
	.type = POWER_SUPPLY_TYPE_MAINS,
	.properties = nvec_घातer_props,
	.num_properties = ARRAY_SIZE(nvec_घातer_props),
	.get_property = nvec_घातer_get_property,
पूर्ण;

अटल पूर्णांक counter;
अटल स्थिर पूर्णांक bat_iter[] = अणु
	SLOT_STATUS, VOLTAGE, CURRENT, CAPACITY_REMAINING,
#अगर_घोषित EC_FULL_DIAG
	AVERAGE_CURRENT, TEMPERATURE, TIME_REMAINING,
#पूर्ण_अगर
पूर्ण;

अटल व्योम nvec_घातer_poll(काष्ठा work_काष्ठा *work)
अणु
	अक्षर buf[] = अणु NVEC_SYS, GET_SYSTEM_STATUS पूर्ण;
	काष्ठा nvec_घातer *घातer = container_of(work, काष्ठा nvec_घातer,
						poller.work);

	अगर (counter >= ARRAY_SIZE(bat_iter))
		counter = 0;

	/* AC status via sys req */
	nvec_ग_लिखो_async(घातer->nvec, buf, 2);
	msleep(100);

	/*
	 * Select a battery request function via round robin करोing it all at
	 * once seems to overload the घातer supply.
	 */
	buf[0] = NVEC_BAT;
	buf[1] = bat_iter[counter++];
	nvec_ग_लिखो_async(घातer->nvec, buf, 2);

	schedule_delayed_work(to_delayed_work(work), msecs_to_jअगरfies(5000));
पूर्ण;

अटल पूर्णांक nvec_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा घातer_supply **psy;
	स्थिर काष्ठा घातer_supply_desc *psy_desc;
	काष्ठा nvec_घातer *घातer;
	काष्ठा nvec_chip *nvec = dev_get_drvdata(pdev->dev.parent);
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;

	घातer = devm_kzalloc(&pdev->dev, माप(काष्ठा nvec_घातer), GFP_NOWAIT);
	अगर (!घातer)
		वापस -ENOMEM;

	dev_set_drvdata(&pdev->dev, घातer);
	घातer->nvec = nvec;

	चयन (pdev->id) अणु
	हाल AC:
		psy = &nvec_psy;
		psy_desc = &nvec_psy_desc;
		psy_cfg.supplied_to = nvec_घातer_supplied_to;
		psy_cfg.num_supplicants = ARRAY_SIZE(nvec_घातer_supplied_to);

		घातer->notअगरier.notअगरier_call = nvec_घातer_notअगरier;

		INIT_DELAYED_WORK(&घातer->poller, nvec_घातer_poll);
		schedule_delayed_work(&घातer->poller, msecs_to_jअगरfies(5000));
		अवरोध;
	हाल BAT:
		psy = &nvec_bat_psy;
		psy_desc = &nvec_bat_psy_desc;

		घातer->notअगरier.notअगरier_call = nvec_घातer_bat_notअगरier;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	nvec_रेजिस्टर_notअगरier(nvec, &घातer->notअगरier, NVEC_SYS);

	अगर (pdev->id == BAT)
		get_bat_mfg_data(घातer);

	*psy = घातer_supply_रेजिस्टर(&pdev->dev, psy_desc, &psy_cfg);

	वापस PTR_ERR_OR_ZERO(*psy);
पूर्ण

अटल पूर्णांक nvec_घातer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvec_घातer *घातer = platक्रमm_get_drvdata(pdev);

	cancel_delayed_work_sync(&घातer->poller);
	nvec_unरेजिस्टर_notअगरier(घातer->nvec, &घातer->notअगरier);
	चयन (pdev->id) अणु
	हाल AC:
		घातer_supply_unरेजिस्टर(nvec_psy);
		अवरोध;
	हाल BAT:
		घातer_supply_unरेजिस्टर(nvec_bat_psy);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver nvec_घातer_driver = अणु
	.probe = nvec_घातer_probe,
	.हटाओ = nvec_घातer_हटाओ,
	.driver = अणु
		   .name = "nvec-power",
	पूर्ण
पूर्ण;

module_platक्रमm_driver(nvec_घातer_driver);

MODULE_AUTHOR("Ilya Petrov <ilya.muromec@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("NVEC battery and AC driver");
MODULE_ALIAS("platform:nvec-power");
