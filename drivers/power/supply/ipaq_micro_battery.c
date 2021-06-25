<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * h3xxx aपंचांगel micro companion support, battery subdevice
 * based on previous kernel 2.4 version
 * Author : Alessandro Gardich <gremlin@gremlin.it>
 * Author : Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/ipaq-micro.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/workqueue.h>

#घोषणा BATT_PERIOD 100000 /* 100 seconds in milliseconds */

#घोषणा MICRO_BATT_CHEM_ALKALINE	0x01
#घोषणा MICRO_BATT_CHEM_NICD		0x02
#घोषणा MICRO_BATT_CHEM_NIMH		0x03
#घोषणा MICRO_BATT_CHEM_LION		0x04
#घोषणा MICRO_BATT_CHEM_LIPOLY		0x05
#घोषणा MICRO_BATT_CHEM_NOT_INSTALLED	0x06
#घोषणा MICRO_BATT_CHEM_UNKNOWN		0xff

#घोषणा MICRO_BATT_STATUS_HIGH		0x01
#घोषणा MICRO_BATT_STATUS_LOW		0x02
#घोषणा MICRO_BATT_STATUS_CRITICAL	0x04
#घोषणा MICRO_BATT_STATUS_CHARGING	0x08
#घोषणा MICRO_BATT_STATUS_CHARGEMAIN	0x10
#घोषणा MICRO_BATT_STATUS_DEAD		0x20 /* Battery will not अक्षरge */
#घोषणा MICRO_BATT_STATUS_NOTINSTALLED	0x20 /* For expansion pack batteries */
#घोषणा MICRO_BATT_STATUS_FULL		0x40 /* Battery fully अक्षरged */
#घोषणा MICRO_BATT_STATUS_NOBATTERY	0x80
#घोषणा MICRO_BATT_STATUS_UNKNOWN	0xff

काष्ठा micro_battery अणु
	काष्ठा ipaq_micro *micro;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा delayed_work update;
	u8 ac;
	u8 chemistry;
	अचिन्हित पूर्णांक voltage;
	u16 temperature;
	u8 flag;
पूर्ण;

अटल व्योम micro_battery_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा micro_battery *mb = container_of(work,
				काष्ठा micro_battery, update.work);
	काष्ठा ipaq_micro_msg msg_battery = अणु
		.id = MSG_BATTERY,
	पूर्ण;
	काष्ठा ipaq_micro_msg msg_sensor = अणु
		.id = MSG_THERMAL_SENSOR,
	पूर्ण;

	/* First send battery message */
	ipaq_micro_tx_msg_sync(mb->micro, &msg_battery);
	अगर (msg_battery.rx_len < 4)
		pr_info("ERROR");

	/*
	 * Returned message क्रमmat:
	 * byte 0:   0x00 = Not plugged in
	 *           0x01 = AC adapter plugged in
	 * byte 1:   chemistry
	 * byte 2:   voltage LSB
	 * byte 3:   voltage MSB
	 * byte 4:   flags
	 * byte 5-9: same क्रम battery 2
	 */
	mb->ac = msg_battery.rx_data[0];
	mb->chemistry = msg_battery.rx_data[1];
	mb->voltage = ((((अचिन्हित लघु)msg_battery.rx_data[3] << 8) +
			msg_battery.rx_data[2]) * 5000L) * 1000 / 1024;
	mb->flag = msg_battery.rx_data[4];

	अगर (msg_battery.rx_len == 9)
		pr_debug("second battery ignored\n");

	/* Then पढ़ो the sensor */
	ipaq_micro_tx_msg_sync(mb->micro, &msg_sensor);
	mb->temperature = msg_sensor.rx_data[1] << 8 | msg_sensor.rx_data[0];

	queue_delayed_work(mb->wq, &mb->update, msecs_to_jअगरfies(BATT_PERIOD));
पूर्ण

अटल पूर्णांक get_capacity(काष्ठा घातer_supply *b)
अणु
	काष्ठा micro_battery *mb = dev_get_drvdata(b->dev.parent);

	चयन (mb->flag & 0x07) अणु
	हाल MICRO_BATT_STATUS_HIGH:
		वापस 100;
		अवरोध;
	हाल MICRO_BATT_STATUS_LOW:
		वापस 50;
		अवरोध;
	हाल MICRO_BATT_STATUS_CRITICAL:
		वापस 5;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक get_status(काष्ठा घातer_supply *b)
अणु
	काष्ठा micro_battery *mb = dev_get_drvdata(b->dev.parent);

	अगर (mb->flag == MICRO_BATT_STATUS_UNKNOWN)
		वापस POWER_SUPPLY_STATUS_UNKNOWN;

	अगर (mb->flag & MICRO_BATT_STATUS_FULL)
		वापस POWER_SUPPLY_STATUS_FULL;

	अगर ((mb->flag & MICRO_BATT_STATUS_CHARGING) ||
		(mb->flag & MICRO_BATT_STATUS_CHARGEMAIN))
		वापस POWER_SUPPLY_STATUS_CHARGING;

	वापस POWER_SUPPLY_STATUS_DISCHARGING;
पूर्ण

अटल पूर्णांक micro_batt_get_property(काष्ठा घातer_supply *b,
					क्रमागत घातer_supply_property psp,
					जोड़ घातer_supply_propval *val)
अणु
	काष्ठा micro_battery *mb = dev_get_drvdata(b->dev.parent);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		चयन (mb->chemistry) अणु
		हाल MICRO_BATT_CHEM_NICD:
			val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_NiCd;
			अवरोध;
		हाल MICRO_BATT_CHEM_NIMH:
			val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_NiMH;
			अवरोध;
		हाल MICRO_BATT_CHEM_LION:
			val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
			अवरोध;
		हाल MICRO_BATT_CHEM_LIPOLY:
			val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LIPO;
			अवरोध;
		शेष:
			val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = get_status(b);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->पूर्णांकval = 4700000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = get_capacity(b);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = mb->temperature;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = mb->voltage;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक micro_ac_get_property(काष्ठा घातer_supply *b,
				 क्रमागत घातer_supply_property psp,
				 जोड़ घातer_supply_propval *val)
अणु
	काष्ठा micro_battery *mb = dev_get_drvdata(b->dev.parent);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = mb->ac;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property micro_batt_घातer_props[] = अणु
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc micro_batt_घातer_desc = अणु
	.name			= "main-battery",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= micro_batt_घातer_props,
	.num_properties		= ARRAY_SIZE(micro_batt_घातer_props),
	.get_property		= micro_batt_get_property,
	.use_क्रम_apm		= 1,
पूर्ण;

अटल क्रमागत घातer_supply_property micro_ac_घातer_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc micro_ac_घातer_desc = अणु
	.name			= "ac",
	.type			= POWER_SUPPLY_TYPE_MAINS,
	.properties		= micro_ac_घातer_props,
	.num_properties		= ARRAY_SIZE(micro_ac_घातer_props),
	.get_property		= micro_ac_get_property,
पूर्ण;

अटल काष्ठा घातer_supply *micro_batt_घातer, *micro_ac_घातer;

अटल पूर्णांक micro_batt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा micro_battery *mb;
	पूर्णांक ret;

	mb = devm_kzalloc(&pdev->dev, माप(*mb), GFP_KERNEL);
	अगर (!mb)
		वापस -ENOMEM;

	mb->micro = dev_get_drvdata(pdev->dev.parent);
	mb->wq = alloc_workqueue("ipaq-battery-wq", WQ_MEM_RECLAIM, 0);
	अगर (!mb->wq)
		वापस -ENOMEM;

	INIT_DELAYED_WORK(&mb->update, micro_battery_work);
	platक्रमm_set_drvdata(pdev, mb);
	queue_delayed_work(mb->wq, &mb->update, 1);

	micro_batt_घातer = घातer_supply_रेजिस्टर(&pdev->dev,
						 &micro_batt_घातer_desc, शून्य);
	अगर (IS_ERR(micro_batt_घातer)) अणु
		ret = PTR_ERR(micro_batt_घातer);
		जाओ batt_err;
	पूर्ण

	micro_ac_घातer = घातer_supply_रेजिस्टर(&pdev->dev,
					       &micro_ac_घातer_desc, शून्य);
	अगर (IS_ERR(micro_ac_घातer)) अणु
		ret = PTR_ERR(micro_ac_घातer);
		जाओ ac_err;
	पूर्ण

	dev_info(&pdev->dev, "iPAQ micro battery driver\n");
	वापस 0;

ac_err:
	घातer_supply_unरेजिस्टर(micro_batt_घातer);
batt_err:
	cancel_delayed_work_sync(&mb->update);
	destroy_workqueue(mb->wq);
	वापस ret;
पूर्ण

अटल पूर्णांक micro_batt_हटाओ(काष्ठा platक्रमm_device *pdev)

अणु
	काष्ठा micro_battery *mb = platक्रमm_get_drvdata(pdev);

	घातer_supply_unरेजिस्टर(micro_ac_घातer);
	घातer_supply_unरेजिस्टर(micro_batt_घातer);
	cancel_delayed_work_sync(&mb->update);
	destroy_workqueue(mb->wq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused micro_batt_suspend(काष्ठा device *dev)
अणु
	काष्ठा micro_battery *mb = dev_get_drvdata(dev);

	cancel_delayed_work_sync(&mb->update);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused micro_batt_resume(काष्ठा device *dev)
अणु
	काष्ठा micro_battery *mb = dev_get_drvdata(dev);

	queue_delayed_work(mb->wq, &mb->update, msecs_to_jअगरfies(BATT_PERIOD));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops micro_batt_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(micro_batt_suspend, micro_batt_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver micro_batt_device_driver = अणु
	.driver		= अणु
		.name	= "ipaq-micro-battery",
		.pm	= &micro_batt_dev_pm_ops,
	पूर्ण,
	.probe		= micro_batt_probe,
	.हटाओ		= micro_batt_हटाओ,
पूर्ण;
module_platक्रमm_driver(micro_batt_device_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("driver for iPAQ Atmel micro battery");
MODULE_ALIAS("platform:ipaq-micro-battery");
