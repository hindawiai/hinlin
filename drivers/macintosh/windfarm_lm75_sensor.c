<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control. LM75 sensor
 *
 * (c) Copyright 2005 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/pmac_low_i2c.h>

#समावेश "windfarm.h"

#घोषणा VERSION "1.0"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(args...)	prपूर्णांकk(args)
#अन्यथा
#घोषणा DBG(args...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

काष्ठा wf_lm75_sensor अणु
	पूर्णांक			ds1775 : 1;
	पूर्णांक			inited : 1;
	काष्ठा i2c_client	*i2c;
	काष्ठा wf_sensor	sens;
पूर्ण;
#घोषणा wf_to_lm75(c) container_of(c, काष्ठा wf_lm75_sensor, sens)

अटल पूर्णांक wf_lm75_get(काष्ठा wf_sensor *sr, s32 *value)
अणु
	काष्ठा wf_lm75_sensor *lm = wf_to_lm75(sr);
	s32 data;

	अगर (lm->i2c == शून्य)
		वापस -ENODEV;

	/* Init chip अगर necessary */
	अगर (!lm->inited) अणु
		u8 cfg_new, cfg = (u8)i2c_smbus_पढ़ो_byte_data(lm->i2c, 1);

		DBG("wf_lm75: Initializing %s, cfg was: %02x\n",
		    sr->name, cfg);

		/* clear shutकरोwn bit, keep other settings as left by
		 * the firmware क्रम now
		 */
		cfg_new = cfg & ~0x01;
		i2c_smbus_ग_लिखो_byte_data(lm->i2c, 1, cfg_new);
		lm->inited = 1;

		/* If we just घातered it up, let's रुको 200 ms */
		msleep(200);
	पूर्ण

	/* Read temperature रेजिस्टर */
	data = (s32)le16_to_cpu(i2c_smbus_पढ़ो_word_data(lm->i2c, 0));
	data <<= 8;
	*value = data;

	वापस 0;
पूर्ण

अटल व्योम wf_lm75_release(काष्ठा wf_sensor *sr)
अणु
	काष्ठा wf_lm75_sensor *lm = wf_to_lm75(sr);

	kमुक्त(lm);
पूर्ण

अटल स्थिर काष्ठा wf_sensor_ops wf_lm75_ops = अणु
	.get_value	= wf_lm75_get,
	.release	= wf_lm75_release,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक wf_lm75_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु	
	काष्ठा wf_lm75_sensor *lm;
	पूर्णांक rc, ds1775;
	स्थिर अक्षर *name, *loc;

	अगर (id)
		ds1775 = id->driver_data;
	अन्यथा
		ds1775 = !!of_device_get_match_data(&client->dev);

	DBG("wf_lm75: creating  %s device at address 0x%02x\n",
	    ds1775 ? "ds1775" : "lm75", client->addr);

	loc = of_get_property(client->dev.of_node, "hwsensor-location", शून्य);
	अगर (!loc) अणु
		dev_warn(&client->dev, "Missing hwsensor-location property!\n");
		वापस -ENXIO;
	पूर्ण

	/* Usual rant about sensor names not beeing very consistent in
	 * the device-tree, oh well ...
	 * Add more entries below as you deal with more setups
	 */
	अगर (!म_भेद(loc, "Hard drive") || !म_भेद(loc, "DRIVE BAY"))
		name = "hd-temp";
	अन्यथा अगर (!म_भेद(loc, "Incoming Air Temp"))
		name = "incoming-air-temp";
	अन्यथा अगर (!म_भेद(loc, "ODD Temp"))
		name = "optical-drive-temp";
	अन्यथा अगर (!म_भेद(loc, "HD Temp"))
		name = "hard-drive-temp";
	अन्यथा अगर (!म_भेद(loc, "PCI SLOTS"))
		name = "slots-temp";
	अन्यथा अगर (!म_भेद(loc, "CPU A INLET"))
		name = "cpu-inlet-temp-0";
	अन्यथा अगर (!म_भेद(loc, "CPU B INLET"))
		name = "cpu-inlet-temp-1";
	अन्यथा
		वापस -ENXIO;
 	

	lm = kzalloc(माप(काष्ठा wf_lm75_sensor), GFP_KERNEL);
	अगर (lm == शून्य)
		वापस -ENODEV;

	lm->inited = 0;
	lm->ds1775 = ds1775;
	lm->i2c = client;
	lm->sens.name = name;
	lm->sens.ops = &wf_lm75_ops;
	i2c_set_clientdata(client, lm);

	rc = wf_रेजिस्टर_sensor(&lm->sens);
	अगर (rc)
		kमुक्त(lm);
	वापस rc;
पूर्ण

अटल पूर्णांक wf_lm75_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा wf_lm75_sensor *lm = i2c_get_clientdata(client);

	/* Mark client detached */
	lm->i2c = शून्य;

	/* release sensor */
	wf_unरेजिस्टर_sensor(&lm->sens);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wf_lm75_id[] = अणु
	अणु "MAC,lm75", 0 पूर्ण,
	अणु "MAC,ds1775", 1 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wf_lm75_id);

अटल स्थिर काष्ठा of_device_id wf_lm75_of_id[] = अणु
	अणु .compatible = "lm75", .data = (व्योम *)0पूर्ण,
	अणु .compatible = "ds1775", .data = (व्योम *)1 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wf_lm75_of_id);

अटल काष्ठा i2c_driver wf_lm75_driver = अणु
	.driver = अणु
		.name	= "wf_lm75",
		.of_match_table = wf_lm75_of_id,
	पूर्ण,
	.probe		= wf_lm75_probe,
	.हटाओ		= wf_lm75_हटाओ,
	.id_table	= wf_lm75_id,
पूर्ण;

module_i2c_driver(wf_lm75_driver);

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("LM75 sensor objects for PowerMacs thermal control");
MODULE_LICENSE("GPL");

