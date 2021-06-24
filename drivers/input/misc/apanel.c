<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Fujitsu Lअगरebook Application Panel button drive
 *
 *  Copyright (C) 2007 Stephen Hemminger <shemminger@linux-foundation.org>
 *  Copyright (C) 2001-2003 Jochen Eisinger <jochen@penguin-breeder.org>
 *
 * Many Fujitsu Lअगरebook laptops have a small panel of buttons that are
 * accessible via the i2c/smbus पूर्णांकerface. This driver polls those
 * buttons and generates input events.
 *
 * For more details see:
 *	http://apanel.sourceक्रमge.net/tech.php
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/input.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>

#घोषणा APANEL_NAME	"Fujitsu Application Panel"
#घोषणा APANEL		"apanel"

/* How often we poll keys - msecs */
#घोषणा POLL_INTERVAL_DEFAULT	1000

/* Magic स्थिरants in BIOS that tell about buttons */
क्रमागत apanel_devid अणु
	APANEL_DEV_NONE	  = 0,
	APANEL_DEV_APPBTN = 1,
	APANEL_DEV_CDBTN  = 2,
	APANEL_DEV_LCD	  = 3,
	APANEL_DEV_LED	  = 4,

	APANEL_DEV_MAX,
पूर्ण;

क्रमागत apanel_chip अणु
	CHIP_NONE    = 0,
	CHIP_OZ992C  = 1,
	CHIP_OZ163T  = 2,
	CHIP_OZ711M3 = 4,
पूर्ण;

/* Result of BIOS snooping/probing -- what features are supported */
अटल क्रमागत apanel_chip device_chip[APANEL_DEV_MAX];

#घोषणा MAX_PANEL_KEYS	12

काष्ठा apanel अणु
	काष्ठा input_dev *idev;
	काष्ठा i2c_client *client;
	अचिन्हित लघु keymap[MAX_PANEL_KEYS];
	u16 nkeys;
	काष्ठा led_classdev mail_led;
पूर्ण;

अटल स्थिर अचिन्हित लघु apanel_keymap[MAX_PANEL_KEYS] = अणु
	[0] = KEY_MAIL,
	[1] = KEY_WWW,
	[2] = KEY_PROG2,
	[3] = KEY_PROG1,

	[8] = KEY_FORWARD,
	[9] = KEY_REWIND,
	[10] = KEY_STOPCD,
	[11] = KEY_PLAYPAUSE,
पूर्ण;

अटल व्योम report_key(काष्ठा input_dev *input, अचिन्हित keycode)
अणु
	dev_dbg(input->dev.parent, "report key %#x\n", keycode);
	input_report_key(input, keycode, 1);
	input_sync(input);

	input_report_key(input, keycode, 0);
	input_sync(input);
पूर्ण

/* Poll क्रम key changes
 *
 * Read Application keys via SMI
 *  A (0x4), B (0x8), Internet (0x2), Email (0x1).
 *
 * CD keys:
 * Forward (0x100), Rewind (0x200), Stop (0x400), Pause (0x800)
 */
अटल व्योम apanel_poll(काष्ठा input_dev *idev)
अणु
	काष्ठा apanel *ap = input_get_drvdata(idev);
	u8 cmd = device_chip[APANEL_DEV_APPBTN] == CHIP_OZ992C ? 0 : 8;
	s32 data;
	पूर्णांक i;

	data = i2c_smbus_पढ़ो_word_data(ap->client, cmd);
	अगर (data < 0)
		वापस;	/* ignore errors (due to ACPI??) */

	/* ग_लिखो back to clear latch */
	i2c_smbus_ग_लिखो_word_data(ap->client, cmd, 0);

	अगर (!data)
		वापस;

	dev_dbg(&idev->dev, APANEL ": data %#x\n", data);
	क्रम (i = 0; i < idev->keycodemax; i++)
		अगर ((1u << i) & data)
			report_key(idev, ap->keymap[i]);
पूर्ण

अटल पूर्णांक mail_led_set(काष्ठा led_classdev *led,
			 क्रमागत led_brightness value)
अणु
	काष्ठा apanel *ap = container_of(led, काष्ठा apanel, mail_led);
	u16 led_bits = value != LED_OFF ? 0x8000 : 0x0000;

	वापस i2c_smbus_ग_लिखो_word_data(ap->client, 0x10, led_bits);
पूर्ण

अटल पूर्णांक apanel_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा apanel *ap;
	काष्ठा input_dev *idev;
	u8 cmd = device_chip[APANEL_DEV_APPBTN] == CHIP_OZ992C ? 0 : 8;
	पूर्णांक i, err;

	ap = devm_kzalloc(&client->dev, माप(*ap), GFP_KERNEL);
	अगर (!ap)
		वापस -ENOMEM;

	idev = devm_input_allocate_device(&client->dev);
	अगर (!idev)
		वापस -ENOMEM;

	ap->idev = idev;
	ap->client = client;

	i2c_set_clientdata(client, ap);

	err = i2c_smbus_ग_लिखो_word_data(client, cmd, 0);
	अगर (err) अणु
		dev_warn(&client->dev, "smbus write error %d\n", err);
		वापस err;
	पूर्ण

	input_set_drvdata(idev, ap);

	idev->name = APANEL_NAME " buttons";
	idev->phys = "apanel/input0";
	idev->id.bustype = BUS_HOST;

	स_नकल(ap->keymap, apanel_keymap, माप(apanel_keymap));
	idev->keycode = ap->keymap;
	idev->keycodesize = माप(ap->keymap[0]);
	idev->keycodemax = (device_chip[APANEL_DEV_CDBTN] != CHIP_NONE) ? 12 : 4;

	set_bit(EV_KEY, idev->evbit);
	क्रम (i = 0; i < idev->keycodemax; i++)
		अगर (ap->keymap[i])
			set_bit(ap->keymap[i], idev->keybit);

	err = input_setup_polling(idev, apanel_poll);
	अगर (err)
		वापस err;

	input_set_poll_पूर्णांकerval(idev, POLL_INTERVAL_DEFAULT);

	err = input_रेजिस्टर_device(idev);
	अगर (err)
		वापस err;

	अगर (device_chip[APANEL_DEV_LED] != CHIP_NONE) अणु
		ap->mail_led.name = "mail:blue";
		ap->mail_led.brightness_set_blocking = mail_led_set;
		err = devm_led_classdev_रेजिस्टर(&client->dev, &ap->mail_led);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम apanel_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा apanel *ap = i2c_get_clientdata(client);

	अगर (device_chip[APANEL_DEV_LED] != CHIP_NONE)
		led_set_brightness(&ap->mail_led, LED_OFF);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id apanel_id[] = अणु
	अणु "fujitsu_apanel", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, apanel_id);

अटल काष्ठा i2c_driver apanel_driver = अणु
	.driver = अणु
		.name = APANEL,
	पूर्ण,
	.probe		= apanel_probe,
	.shutकरोwn	= apanel_shutकरोwn,
	.id_table	= apanel_id,
पूर्ण;

/* Scan the प्रणाली ROM क्रम the signature "FJKEYINF" */
अटल __init स्थिर व्योम __iomem *bios_signature(स्थिर व्योम __iomem *bios)
अणु
	sमाप_प्रकार offset;
	स्थिर अचिन्हित अक्षर signature[] = "FJKEYINF";

	क्रम (offset = 0; offset < 0x10000; offset += 0x10) अणु
		अगर (check_signature(bios + offset, signature,
				    माप(signature)-1))
			वापस bios + offset;
	पूर्ण
	pr_notice(APANEL ": Fujitsu BIOS signature '%s' not found...\n",
		  signature);
	वापस शून्य;
पूर्ण

अटल पूर्णांक __init apanel_init(व्योम)
अणु
	व्योम __iomem *bios;
	स्थिर व्योम __iomem *p;
	u8 devno;
	अचिन्हित अक्षर i2c_addr;
	पूर्णांक found = 0;

	bios = ioremap(0xF0000, 0x10000); /* Can't fail */

	p = bios_signature(bios);
	अगर (!p) अणु
		iounmap(bios);
		वापस -ENODEV;
	पूर्ण

	/* just use the first address */
	p += 8;
	i2c_addr = पढ़ोb(p + 3) >> 1;

	क्रम ( ; (devno = पढ़ोb(p)) & 0x7f; p += 4) अणु
		अचिन्हित अक्षर method, slave, chip;

		method = पढ़ोb(p + 1);
		chip = पढ़ोb(p + 2);
		slave = पढ़ोb(p + 3) >> 1;

		अगर (slave != i2c_addr) अणु
			pr_notice(APANEL ": only one SMBus slave "
				  "address supported, skipping device...\n");
			जारी;
		पूर्ण

		/* translate alternative device numbers */
		चयन (devno) अणु
		हाल 6:
			devno = APANEL_DEV_APPBTN;
			अवरोध;
		हाल 7:
			devno = APANEL_DEV_LED;
			अवरोध;
		पूर्ण

		अगर (devno >= APANEL_DEV_MAX)
			pr_notice(APANEL ": unknown device %u found\n", devno);
		अन्यथा अगर (device_chip[devno] != CHIP_NONE)
			pr_warn(APANEL ": duplicate entry for devno %u\n",
				devno);

		अन्यथा अगर (method != 1 && method != 2 && method != 4) अणु
			pr_notice(APANEL ": unknown method %u for devno %u\n",
				  method, devno);
		पूर्ण अन्यथा अणु
			device_chip[devno] = (क्रमागत apanel_chip) chip;
			++found;
		पूर्ण
	पूर्ण
	iounmap(bios);

	अगर (found == 0) अणु
		pr_info(APANEL ": no input devices reported by BIOS\n");
		वापस -EIO;
	पूर्ण

	वापस i2c_add_driver(&apanel_driver);
पूर्ण
module_init(apanel_init);

अटल व्योम __निकास apanel_cleanup(व्योम)
अणु
	i2c_del_driver(&apanel_driver);
पूर्ण
module_निकास(apanel_cleanup);

MODULE_AUTHOR("Stephen Hemminger <shemminger@linux-foundation.org>");
MODULE_DESCRIPTION(APANEL_NAME " driver");
MODULE_LICENSE("GPL");

MODULE_ALIAS("dmi:*:svnFUJITSU:pnLifeBook*:pvr*:rvnFUJITSU:*");
MODULE_ALIAS("dmi:*:svnFUJITSU:pnLifebook*:pvr*:rvnFUJITSU:*");
