<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control. LM87 sensor
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
#समावेश <यंत्र/pmac_low_i2c.h>

#समावेश "windfarm.h"

#घोषणा VERSION "1.0"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(args...)	prपूर्णांकk(args)
#अन्यथा
#घोषणा DBG(args...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

काष्ठा wf_lm87_sensor अणु
	काष्ठा i2c_client	*i2c;
	काष्ठा wf_sensor	sens;
पूर्ण;
#घोषणा wf_to_lm87(c) container_of(c, काष्ठा wf_lm87_sensor, sens)


अटल पूर्णांक wf_lm87_पढ़ो_reg(काष्ठा i2c_client *chip, पूर्णांक reg)
अणु
	पूर्णांक rc, tries = 0;
	u8 buf;

	क्रम (;;) अणु
		/* Set address */
		buf = (u8)reg;
		rc = i2c_master_send(chip, &buf, 1);
		अगर (rc <= 0)
			जाओ error;
		rc = i2c_master_recv(chip, &buf, 1);
		अगर (rc <= 0)
			जाओ error;
		वापस (पूर्णांक)buf;
	error:
		DBG("wf_lm87: Error reading LM87, retrying...\n");
		अगर (++tries > 10) अणु
			prपूर्णांकk(KERN_ERR "wf_lm87: Error reading LM87 !\n");
			वापस -EIO;
		पूर्ण
		msleep(10);
	पूर्ण
पूर्ण

अटल पूर्णांक wf_lm87_get(काष्ठा wf_sensor *sr, s32 *value)
अणु
	काष्ठा wf_lm87_sensor *lm = sr->priv;
	s32 temp;

	अगर (lm->i2c == शून्य)
		वापस -ENODEV;

#घोषणा LM87_INT_TEMP		0x27

	/* Read temperature रेजिस्टर */
	temp = wf_lm87_पढ़ो_reg(lm->i2c, LM87_INT_TEMP);
	अगर (temp < 0)
		वापस temp;
	*value = temp << 16;

	वापस 0;
पूर्ण

अटल व्योम wf_lm87_release(काष्ठा wf_sensor *sr)
अणु
	काष्ठा wf_lm87_sensor *lm = wf_to_lm87(sr);

	kमुक्त(lm);
पूर्ण

अटल स्थिर काष्ठा wf_sensor_ops wf_lm87_ops = अणु
	.get_value	= wf_lm87_get,
	.release	= wf_lm87_release,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक wf_lm87_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु	
	काष्ठा wf_lm87_sensor *lm;
	स्थिर अक्षर *name = शून्य, *loc;
	काष्ठा device_node *np = शून्य;
	पूर्णांक rc;

	/*
	 * The lm87 contains a whole pile of sensors, additionally,
	 * the Xserve G5 has several lm87's. However, क्रम now we only
	 * care about the पूर्णांकernal temperature sensor
	 */
	क्रम_each_child_of_node(client->dev.of_node, np) अणु
		अगर (!of_node_name_eq(np, "int-temp"))
			जारी;
		loc = of_get_property(np, "location", शून्य);
		अगर (!loc)
			जारी;
		अगर (म_माला(loc, "DIMM"))
			name = "dimms-temp";
		अन्यथा अगर (म_माला(loc, "Processors"))
			name = "between-cpus-temp";
		अगर (name) अणु
			of_node_put(np);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!name) अणु
		pr_warn("wf_lm87: Unsupported sensor %pOF\n",
			client->dev.of_node);
		वापस -ENODEV;
	पूर्ण

	lm = kzalloc(माप(काष्ठा wf_lm87_sensor), GFP_KERNEL);
	अगर (lm == शून्य)
		वापस -ENODEV;

	lm->i2c = client;
	lm->sens.name = name;
	lm->sens.ops = &wf_lm87_ops;
	lm->sens.priv = lm;
	i2c_set_clientdata(client, lm);

	rc = wf_रेजिस्टर_sensor(&lm->sens);
	अगर (rc)
		kमुक्त(lm);
	वापस rc;
पूर्ण

अटल पूर्णांक wf_lm87_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा wf_lm87_sensor *lm = i2c_get_clientdata(client);

	/* Mark client detached */
	lm->i2c = शून्य;

	/* release sensor */
	wf_unरेजिस्टर_sensor(&lm->sens);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wf_lm87_id[] = अणु
	अणु "MAC,lm87cimt", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wf_lm87_id);

अटल स्थिर काष्ठा of_device_id wf_lm87_of_id[] = अणु
	अणु .compatible = "lm87cimt", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wf_lm87_of_id);

अटल काष्ठा i2c_driver wf_lm87_driver = अणु
	.driver = अणु
		.name	= "wf_lm87",
		.of_match_table = wf_lm87_of_id,
	पूर्ण,
	.probe		= wf_lm87_probe,
	.हटाओ		= wf_lm87_हटाओ,
	.id_table	= wf_lm87_id,
पूर्ण;

अटल पूर्णांक __init wf_lm87_sensor_init(व्योम)
अणु
	/* We only support this on the Xserve */
	अगर (!of_machine_is_compatible("RackMac3,1"))
		वापस -ENODEV;

	वापस i2c_add_driver(&wf_lm87_driver);
पूर्ण

अटल व्योम __निकास wf_lm87_sensor_निकास(व्योम)
अणु
	i2c_del_driver(&wf_lm87_driver);
पूर्ण


module_init(wf_lm87_sensor_init);
module_निकास(wf_lm87_sensor_निकास);

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("LM87 sensor objects for PowerMacs thermal control");
MODULE_LICENSE("GPL");

