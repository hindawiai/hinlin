<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control. AD7417 sensors
 *
 * Copyright 2012 Benjamin Herrenschmidt, IBM Corp.
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <linux/i2c.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sections.h>

#समावेश "windfarm.h"
#समावेश "windfarm_mpu.h"

#घोषणा VERSION "1.0"

काष्ठा wf_ad7417_priv अणु
	काष्ठा kref		ref;
	काष्ठा i2c_client	*i2c;
	u8			config;
	u8			cpu;
	स्थिर काष्ठा mpu_data	*mpu;
	काष्ठा wf_sensor	sensors[5];
	काष्ठा mutex		lock;
पूर्ण;

अटल पूर्णांक wf_ad7417_temp_get(काष्ठा wf_sensor *sr, s32 *value)
अणु
	काष्ठा wf_ad7417_priv *pv = sr->priv;
	u8 buf[2];
	s16 raw;
	पूर्णांक rc;

	*value = 0;
	mutex_lock(&pv->lock);

	/* Read temp रेजिस्टर */
	buf[0] = 0;
	rc = i2c_master_send(pv->i2c, buf, 1);
	अगर (rc < 0)
		जाओ error;
	rc = i2c_master_recv(pv->i2c, buf, 2);
	अगर (rc < 0)
		जाओ error;

	/* Read a a 16-bit चिन्हित value */
	raw = be16_to_cpup((__le16 *)buf);

	/* Convert 8.8-bit to 16.16 fixed poपूर्णांक */
	*value = ((s32)raw) << 8;

	mutex_unlock(&pv->lock);
	वापस 0;

error:
	mutex_unlock(&pv->lock);
	वापस -1;
पूर्ण

/*
 * Scaling factors क्रम the AD7417 ADC converters (except
 * क्रम the CPU diode which is obtained from the EEPROM).
 * Those values are obtained from the property list of
 * the darwin driver
 */
#घोषणा ADC_12V_CURRENT_SCALE	0x0320	/* _AD2 */
#घोषणा ADC_CPU_VOLTAGE_SCALE	0x00a0	/* _AD3 */
#घोषणा ADC_CPU_CURRENT_SCALE	0x1f40	/* _AD4 */

अटल व्योम wf_ad7417_adc_convert(काष्ठा wf_ad7417_priv *pv,
				  पूर्णांक chan, s32 raw, s32 *value)
अणु
	चयन(chan) अणु
	हाल 1: /* Diode */
		*value = (raw * (s32)pv->mpu->mdiode +
			((s32)pv->mpu->bdiode << 12)) >> 2;
		अवरोध;
	हाल 2: /* 12v current */
		*value = raw * ADC_12V_CURRENT_SCALE;
		अवरोध;
	हाल 3: /* core voltage */
		*value = raw * ADC_CPU_VOLTAGE_SCALE;
		अवरोध;
	हाल 4: /* core current */
		*value = raw * ADC_CPU_CURRENT_SCALE;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक wf_ad7417_adc_get(काष्ठा wf_sensor *sr, s32 *value)
अणु
	काष्ठा wf_ad7417_priv *pv = sr->priv;
	पूर्णांक chan = sr - pv->sensors;
	पूर्णांक i, rc;
	u8 buf[2];
	u16 raw;

	*value = 0;
	mutex_lock(&pv->lock);
	क्रम (i = 0; i < 10; i++) अणु
		/* Set channel */
		buf[0] = 1;
		buf[1] = (pv->config & 0x1f) | (chan << 5);
		rc = i2c_master_send(pv->i2c, buf, 2);
		अगर (rc < 0)
			जाओ error;

		/* Wait क्रम conversion */
		msleep(1);

		/* Switch to data रेजिस्टर */
		buf[0] = 4;
		rc = i2c_master_send(pv->i2c, buf, 1);
		अगर (rc < 0)
			जाओ error;

		/* Read result */
		rc = i2c_master_recv(pv->i2c, buf, 2);
		अगर (rc < 0)
			जाओ error;

		/* Read a a 16-bit चिन्हित value */
		raw = be16_to_cpup((__le16 *)buf) >> 6;
		wf_ad7417_adc_convert(pv, chan, raw, value);

		dev_vdbg(&pv->i2c->dev, "ADC chan %d [%s]"
			 " raw value: 0x%x, conv to: 0x%08x\n",
			 chan, sr->name, raw, *value);

		mutex_unlock(&pv->lock);
		वापस 0;

	error:
		dev_dbg(&pv->i2c->dev,
			  "Error reading ADC, try %d...\n", i);
		अगर (i < 9)
			msleep(10);
	पूर्ण
	mutex_unlock(&pv->lock);
	वापस -1;
पूर्ण

अटल व्योम wf_ad7417_release(काष्ठा kref *ref)
अणु
	काष्ठा wf_ad7417_priv *pv = container_of(ref,
						 काष्ठा wf_ad7417_priv, ref);
	kमुक्त(pv);
पूर्ण

अटल व्योम wf_ad7417_sensor_release(काष्ठा wf_sensor *sr)
अणु
	काष्ठा wf_ad7417_priv *pv = sr->priv;

	kमुक्त(sr->name);
	kref_put(&pv->ref, wf_ad7417_release);
पूर्ण

अटल स्थिर काष्ठा wf_sensor_ops wf_ad7417_temp_ops = अणु
	.get_value	= wf_ad7417_temp_get,
	.release	= wf_ad7417_sensor_release,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा wf_sensor_ops wf_ad7417_adc_ops = अणु
	.get_value	= wf_ad7417_adc_get,
	.release	= wf_ad7417_sensor_release,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम wf_ad7417_add_sensor(काष्ठा wf_ad7417_priv *pv,
				 पूर्णांक index, स्थिर अक्षर *name,
				 स्थिर काष्ठा wf_sensor_ops *ops)
अणु
	pv->sensors[index].name = kaप्र_लिखो(GFP_KERNEL, "%s-%d", name, pv->cpu);
	pv->sensors[index].priv = pv;
	pv->sensors[index].ops = ops;
	अगर (!wf_रेजिस्टर_sensor(&pv->sensors[index]))
		kref_get(&pv->ref);
पूर्ण

अटल व्योम wf_ad7417_init_chip(काष्ठा wf_ad7417_priv *pv)
अणु
	पूर्णांक rc;
	u8 buf[2];
	u8 config = 0;

	/*
	 * Read ADC the configuration रेजिस्टर and cache it. We
	 * also make sure Config2 contains proper values, I've seen
	 * हालs where we got stale grabage in there, thus preventing
	 * proper पढ़ोing of conv. values
	 */

	/* Clear Config2 */
	buf[0] = 5;
	buf[1] = 0;
	i2c_master_send(pv->i2c, buf, 2);

	/* Read & cache Config1 */
	buf[0] = 1;
	rc = i2c_master_send(pv->i2c, buf, 1);
	अगर (rc > 0) अणु
		rc = i2c_master_recv(pv->i2c, buf, 1);
		अगर (rc > 0) अणु
			config = buf[0];

			dev_dbg(&pv->i2c->dev, "ADC config reg: %02x\n",
				config);

			/* Disable shutकरोwn mode */
			config &= 0xfe;
			buf[0] = 1;
			buf[1] = config;
			rc = i2c_master_send(pv->i2c, buf, 2);
		पूर्ण
	पूर्ण
	अगर (rc <= 0)
		dev_err(&pv->i2c->dev, "Error reading ADC config\n");

	pv->config = config;
पूर्ण

अटल पूर्णांक wf_ad7417_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wf_ad7417_priv *pv;
	स्थिर काष्ठा mpu_data *mpu;
	स्थिर अक्षर *loc;
	पूर्णांक cpu_nr;

	loc = of_get_property(client->dev.of_node, "hwsensor-location", शून्य);
	अगर (!loc) अणु
		dev_warn(&client->dev, "Missing hwsensor-location property!\n");
		वापस -ENXIO;
	पूर्ण

	/*
	 * Identअगरy which CPU we beदीर्घ to by looking at the first entry
	 * in the hwsensor-location list
	 */
	अगर (!म_भेदन(loc, "CPU A", 5))
		cpu_nr = 0;
	अन्यथा अगर (!म_भेदन(loc, "CPU B", 5))
		cpu_nr = 1;
	अन्यथा अणु
		pr_err("wf_ad7417: Can't identify location %s\n", loc);
		वापस -ENXIO;
	पूर्ण
	mpu = wf_get_mpu(cpu_nr);
	अगर (!mpu) अणु
		dev_err(&client->dev, "Failed to retrieve MPU data\n");
		वापस -ENXIO;
	पूर्ण

	pv = kzalloc(माप(काष्ठा wf_ad7417_priv), GFP_KERNEL);
	अगर (pv == शून्य)
		वापस -ENODEV;

	kref_init(&pv->ref);
	mutex_init(&pv->lock);
	pv->i2c = client;
	pv->cpu = cpu_nr;
	pv->mpu = mpu;
	dev_set_drvdata(&client->dev, pv);

	/* Initialize the chip */
	wf_ad7417_init_chip(pv);

	/*
	 * We cannot rely on Apple device-tree giving us child
	 * node with the names of the inभागidual sensors so we
	 * just hard code what we know about them
	 */
	wf_ad7417_add_sensor(pv, 0, "cpu-amb-temp", &wf_ad7417_temp_ops);
	wf_ad7417_add_sensor(pv, 1, "cpu-diode-temp", &wf_ad7417_adc_ops);
	wf_ad7417_add_sensor(pv, 2, "cpu-12v-current", &wf_ad7417_adc_ops);
	wf_ad7417_add_sensor(pv, 3, "cpu-voltage", &wf_ad7417_adc_ops);
	wf_ad7417_add_sensor(pv, 4, "cpu-current", &wf_ad7417_adc_ops);

	वापस 0;
पूर्ण

अटल पूर्णांक wf_ad7417_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा wf_ad7417_priv *pv = dev_get_drvdata(&client->dev);
	पूर्णांक i;

	/* Mark client detached */
	pv->i2c = शून्य;

	/* Release sensor */
	क्रम (i = 0; i < 5; i++)
		wf_unरेजिस्टर_sensor(&pv->sensors[i]);

	kref_put(&pv->ref, wf_ad7417_release);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wf_ad7417_id[] = अणु
	अणु "MAC,ad7417", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wf_ad7417_id);

अटल स्थिर काष्ठा of_device_id wf_ad7417_of_id[] = अणु
	अणु .compatible = "ad7417", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wf_ad7417_of_id);

अटल काष्ठा i2c_driver wf_ad7417_driver = अणु
	.driver = अणु
		.name	= "wf_ad7417",
		.of_match_table = wf_ad7417_of_id,
	पूर्ण,
	.probe		= wf_ad7417_probe,
	.हटाओ		= wf_ad7417_हटाओ,
	.id_table	= wf_ad7417_id,
पूर्ण;

अटल पूर्णांक wf_ad7417_init(व्योम)
अणु
	/* This is only supported on these machines */
	अगर (!of_machine_is_compatible("PowerMac7,2") &&
	    !of_machine_is_compatible("PowerMac7,3") &&
	    !of_machine_is_compatible("RackMac3,1"))
		वापस -ENODEV;

	वापस i2c_add_driver(&wf_ad7417_driver);
पूर्ण

अटल व्योम wf_ad7417_निकास(व्योम)
अणु
	i2c_del_driver(&wf_ad7417_driver);
पूर्ण

module_init(wf_ad7417_init);
module_निकास(wf_ad7417_निकास);

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("ad7417 sensor driver for PowerMacs");
MODULE_LICENSE("GPL");

