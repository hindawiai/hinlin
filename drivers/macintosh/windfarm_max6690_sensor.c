<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control.  MAX6690 sensor.
 *
 * Copyright (C) 2005 Paul Mackerras, IBM Corp. <paulus@samba.org>
 */
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pmac_low_i2c.h>

#समावेश "windfarm.h"

#घोषणा VERSION "1.0"

/* This currently only exports the बाह्यal temperature sensor,
   since that's all the control loops need. */

/* Some MAX6690 रेजिस्टर numbers */
#घोषणा MAX6690_INTERNAL_TEMP	0
#घोषणा MAX6690_EXTERNAL_TEMP	1

काष्ठा wf_6690_sensor अणु
	काष्ठा i2c_client	*i2c;
	काष्ठा wf_sensor	sens;
पूर्ण;

#घोषणा wf_to_6690(x)	container_of((x), काष्ठा wf_6690_sensor, sens)

अटल पूर्णांक wf_max6690_get(काष्ठा wf_sensor *sr, s32 *value)
अणु
	काष्ठा wf_6690_sensor *max = wf_to_6690(sr);
	s32 data;

	अगर (max->i2c == शून्य)
		वापस -ENODEV;

	/* chip माला_लो initialized by firmware */
	data = i2c_smbus_पढ़ो_byte_data(max->i2c, MAX6690_EXTERNAL_TEMP);
	अगर (data < 0)
		वापस data;
	*value = data << 16;
	वापस 0;
पूर्ण

अटल व्योम wf_max6690_release(काष्ठा wf_sensor *sr)
अणु
	काष्ठा wf_6690_sensor *max = wf_to_6690(sr);

	kमुक्त(max);
पूर्ण

अटल स्थिर काष्ठा wf_sensor_ops wf_max6690_ops = अणु
	.get_value	= wf_max6690_get,
	.release	= wf_max6690_release,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक wf_max6690_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर अक्षर *name, *loc;
	काष्ठा wf_6690_sensor *max;
	पूर्णांक rc;

	loc = of_get_property(client->dev.of_node, "hwsensor-location", शून्य);
	अगर (!loc) अणु
		dev_warn(&client->dev, "Missing hwsensor-location property!\n");
		वापस -ENXIO;
	पूर्ण

	/*
	 * We only expose the बाह्यal temperature रेजिस्टर क्रम
	 * now as this is all we need क्रम our control loops
	 */
	अगर (!म_भेद(loc, "BACKSIDE") || !म_भेद(loc, "SYS CTRLR AMBIENT"))
		name = "backside-temp";
	अन्यथा अगर (!म_भेद(loc, "NB Ambient"))
		name = "north-bridge-temp";
	अन्यथा अगर (!म_भेद(loc, "GPU Ambient"))
		name = "gpu-temp";
	अन्यथा
		वापस -ENXIO;

	max = kzalloc(माप(काष्ठा wf_6690_sensor), GFP_KERNEL);
	अगर (max == शून्य) अणु
		prपूर्णांकk(KERN_ERR "windfarm: Couldn't create MAX6690 sensor: "
		       "no memory\n");
		वापस -ENOMEM;
	पूर्ण

	max->i2c = client;
	max->sens.name = name;
	max->sens.ops = &wf_max6690_ops;
	i2c_set_clientdata(client, max);

	rc = wf_रेजिस्टर_sensor(&max->sens);
	अगर (rc)
		kमुक्त(max);
	वापस rc;
पूर्ण

अटल पूर्णांक wf_max6690_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा wf_6690_sensor *max = i2c_get_clientdata(client);

	max->i2c = शून्य;
	wf_unरेजिस्टर_sensor(&max->sens);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wf_max6690_id[] = अणु
	अणु "MAC,max6690", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wf_max6690_id);

अटल स्थिर काष्ठा of_device_id wf_max6690_of_id[] = अणु
	अणु .compatible = "max6690", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wf_max6690_of_id);

अटल काष्ठा i2c_driver wf_max6690_driver = अणु
	.driver = अणु
		.name		= "wf_max6690",
		.of_match_table = wf_max6690_of_id,
	पूर्ण,
	.probe		= wf_max6690_probe,
	.हटाओ		= wf_max6690_हटाओ,
	.id_table	= wf_max6690_id,
पूर्ण;

module_i2c_driver(wf_max6690_driver);

MODULE_AUTHOR("Paul Mackerras <paulus@samba.org>");
MODULE_DESCRIPTION("MAX6690 sensor objects for PowerMac thermal control");
MODULE_LICENSE("GPL");
