<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Apple Motion Sensor driver (I2C variant)
 *
 * Copyright (C) 2005 Stelian Pop (stelian@popies.net)
 * Copyright (C) 2006 Michael Hanselmann (linux-kernel@hansmi.ch)
 *
 * Clean room implementation based on the reverse engineered Mac OS X driver by
 * Johannes Berg <johannes@sipsolutions.net>, करोcumentation available at
 * http://johannes.sipsolutions.net/PowerBook/Apple_Motion_Sensor_Specअगरication
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

#समावेश "ams.h"

/* AMS रेजिस्टरs */
#घोषणा AMS_COMMAND	0x00	/* command रेजिस्टर */
#घोषणा AMS_STATUS	0x01	/* status रेजिस्टर */
#घोषणा AMS_CTRL1	0x02	/* पढ़ो control 1 (number of values) */
#घोषणा AMS_CTRL2	0x03	/* पढ़ो control 2 (offset?) */
#घोषणा AMS_CTRL3	0x04	/* पढ़ो control 3 (size of each value?) */
#घोषणा AMS_DATA1	0x05	/* पढ़ो data 1 */
#घोषणा AMS_DATA2	0x06	/* पढ़ो data 2 */
#घोषणा AMS_DATA3	0x07	/* पढ़ो data 3 */
#घोषणा AMS_DATA4	0x08	/* पढ़ो data 4 */
#घोषणा AMS_DATAX	0x20	/* data X */
#घोषणा AMS_DATAY	0x21	/* data Y */
#घोषणा AMS_DATAZ	0x22	/* data Z */
#घोषणा AMS_FREEFALL	0x24	/* मुक्तfall पूर्णांक control */
#घोषणा AMS_SHOCK	0x25	/* shock पूर्णांक control */
#घोषणा AMS_SENSLOW	0x26	/* sensitivity low limit */
#घोषणा AMS_SENSHIGH	0x27	/* sensitivity high limit */
#घोषणा AMS_CTRLX	0x28	/* control X */
#घोषणा AMS_CTRLY	0x29	/* control Y */
#घोषणा AMS_CTRLZ	0x2A	/* control Z */
#घोषणा AMS_UNKNOWN1	0x2B	/* unknown 1 */
#घोषणा AMS_UNKNOWN2	0x2C	/* unknown 2 */
#घोषणा AMS_UNKNOWN3	0x2D	/* unknown 3 */
#घोषणा AMS_VENDOR	0x2E	/* venकरोr */

/* AMS commands - use with the AMS_COMMAND रेजिस्टर */
क्रमागत ams_i2c_cmd अणु
	AMS_CMD_NOOP = 0,
	AMS_CMD_VERSION,
	AMS_CMD_READMEM,
	AMS_CMD_WRITEMEM,
	AMS_CMD_ERASEMEM,
	AMS_CMD_READEE,
	AMS_CMD_WRITEEE,
	AMS_CMD_RESET,
	AMS_CMD_START,
पूर्ण;

अटल पूर्णांक ams_i2c_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id);
अटल पूर्णांक ams_i2c_हटाओ(काष्ठा i2c_client *client);

अटल स्थिर काष्ठा i2c_device_id ams_id[] = अणु
	अणु "MAC,accelerometer_1", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ams_id);

अटल काष्ठा i2c_driver ams_i2c_driver = अणु
	.driver = अणु
		.name   = "ams",
	पूर्ण,
	.probe          = ams_i2c_probe,
	.हटाओ         = ams_i2c_हटाओ,
	.id_table       = ams_id,
पूर्ण;

अटल s32 ams_i2c_पढ़ो(u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(ams_info.i2c_client, reg);
पूर्ण

अटल पूर्णांक ams_i2c_ग_लिखो(u8 reg, u8 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(ams_info.i2c_client, reg, value);
पूर्ण

अटल पूर्णांक ams_i2c_cmd(क्रमागत ams_i2c_cmd cmd)
अणु
	s32 result;
	पूर्णांक count = 3;

	ams_i2c_ग_लिखो(AMS_COMMAND, cmd);
	msleep(5);

	जबतक (count--) अणु
		result = ams_i2c_पढ़ो(AMS_COMMAND);
		अगर (result == 0 || result & 0x80)
			वापस 0;

		schedule_समयout_unपूर्णांकerruptible(HZ / 20);
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम ams_i2c_set_irq(क्रमागत ams_irq reg, अक्षर enable)
अणु
	अगर (reg & AMS_IRQ_FREEFALL) अणु
		u8 val = ams_i2c_पढ़ो(AMS_CTRLX);
		अगर (enable)
			val |= 0x80;
		अन्यथा
			val &= ~0x80;
		ams_i2c_ग_लिखो(AMS_CTRLX, val);
	पूर्ण

	अगर (reg & AMS_IRQ_SHOCK) अणु
		u8 val = ams_i2c_पढ़ो(AMS_CTRLY);
		अगर (enable)
			val |= 0x80;
		अन्यथा
			val &= ~0x80;
		ams_i2c_ग_लिखो(AMS_CTRLY, val);
	पूर्ण

	अगर (reg & AMS_IRQ_GLOBAL) अणु
		u8 val = ams_i2c_पढ़ो(AMS_CTRLZ);
		अगर (enable)
			val |= 0x80;
		अन्यथा
			val &= ~0x80;
		ams_i2c_ग_लिखो(AMS_CTRLZ, val);
	पूर्ण
पूर्ण

अटल व्योम ams_i2c_clear_irq(क्रमागत ams_irq reg)
अणु
	अगर (reg & AMS_IRQ_FREEFALL)
		ams_i2c_ग_लिखो(AMS_FREEFALL, 0);

	अगर (reg & AMS_IRQ_SHOCK)
		ams_i2c_ग_लिखो(AMS_SHOCK, 0);
पूर्ण

अटल u8 ams_i2c_get_venकरोr(व्योम)
अणु
	वापस ams_i2c_पढ़ो(AMS_VENDOR);
पूर्ण

अटल व्योम ams_i2c_get_xyz(s8 *x, s8 *y, s8 *z)
अणु
	*x = ams_i2c_पढ़ो(AMS_DATAX);
	*y = ams_i2c_पढ़ो(AMS_DATAY);
	*z = ams_i2c_पढ़ो(AMS_DATAZ);
पूर्ण

अटल पूर्णांक ams_i2c_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक vmaj, vmin;
	पूर्णांक result;

	/* There can be only one */
	अगर (unlikely(ams_info.has_device))
		वापस -ENODEV;

	ams_info.i2c_client = client;

	अगर (ams_i2c_cmd(AMS_CMD_RESET)) अणु
		prपूर्णांकk(KERN_INFO "ams: Failed to reset the device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (ams_i2c_cmd(AMS_CMD_START)) अणु
		prपूर्णांकk(KERN_INFO "ams: Failed to start the device\n");
		वापस -ENODEV;
	पूर्ण

	/* get version/venकरोr inक्रमmation */
	ams_i2c_ग_लिखो(AMS_CTRL1, 0x02);
	ams_i2c_ग_लिखो(AMS_CTRL2, 0x85);
	ams_i2c_ग_लिखो(AMS_CTRL3, 0x01);

	ams_i2c_cmd(AMS_CMD_READMEM);

	vmaj = ams_i2c_पढ़ो(AMS_DATA1);
	vmin = ams_i2c_पढ़ो(AMS_DATA2);
	अगर (vmaj != 1 || vmin != 52) अणु
		prपूर्णांकk(KERN_INFO "ams: Incorrect device version (%d.%d)\n",
			vmaj, vmin);
		वापस -ENODEV;
	पूर्ण

	ams_i2c_cmd(AMS_CMD_VERSION);

	vmaj = ams_i2c_पढ़ो(AMS_DATA1);
	vmin = ams_i2c_पढ़ो(AMS_DATA2);
	अगर (vmaj != 0 || vmin != 1) अणु
		prपूर्णांकk(KERN_INFO "ams: Incorrect firmware version (%d.%d)\n",
			vmaj, vmin);
		वापस -ENODEV;
	पूर्ण

	/* Disable पूर्णांकerrupts */
	ams_i2c_set_irq(AMS_IRQ_ALL, 0);

	result = ams_sensor_attach();
	अगर (result < 0)
		वापस result;

	/* Set शेष values */
	ams_i2c_ग_लिखो(AMS_SENSLOW, 0x15);
	ams_i2c_ग_लिखो(AMS_SENSHIGH, 0x60);
	ams_i2c_ग_लिखो(AMS_CTRLX, 0x08);
	ams_i2c_ग_लिखो(AMS_CTRLY, 0x0F);
	ams_i2c_ग_लिखो(AMS_CTRLZ, 0x4F);
	ams_i2c_ग_लिखो(AMS_UNKNOWN1, 0x14);

	/* Clear पूर्णांकerrupts */
	ams_i2c_clear_irq(AMS_IRQ_ALL);

	ams_info.has_device = 1;

	/* Enable पूर्णांकerrupts */
	ams_i2c_set_irq(AMS_IRQ_ALL, 1);

	prपूर्णांकk(KERN_INFO "ams: Found I2C based motion sensor\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ams_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	अगर (ams_info.has_device) अणु
		ams_sensor_detach();

		/* Disable पूर्णांकerrupts */
		ams_i2c_set_irq(AMS_IRQ_ALL, 0);

		/* Clear पूर्णांकerrupts */
		ams_i2c_clear_irq(AMS_IRQ_ALL);

		prपूर्णांकk(KERN_INFO "ams: Unloading\n");

		ams_info.has_device = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ams_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&ams_i2c_driver);
पूर्ण

पूर्णांक __init ams_i2c_init(काष्ठा device_node *np)
अणु
	पूर्णांक result;

	/* Set implementation stuff */
	ams_info.of_node = np;
	ams_info.निकास = ams_i2c_निकास;
	ams_info.get_venकरोr = ams_i2c_get_venकरोr;
	ams_info.get_xyz = ams_i2c_get_xyz;
	ams_info.clear_irq = ams_i2c_clear_irq;
	ams_info.bustype = BUS_I2C;

	result = i2c_add_driver(&ams_i2c_driver);

	वापस result;
पूर्ण
