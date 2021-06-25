<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम rfसमाप्त on some Fujitsu-Siemens Amilo laptops.
 * Copyright 2011 Ben Hutchings.
 *
 * Based in part on the fsam7440 driver, which is:
 * Copyright 2005 Alejandro Vidal Mata & Javier Vidal Mata.
 * and on the fsaa1655g driver, which is:
 * Copyright 2006 Martin Veदeधa.
 */

#समावेश <linux/module.h>
#समावेश <linux/dmi.h>
#समावेश <linux/i8042.h>
#समावेश <linux/पन.स>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rfसमाप्त.h>

/*
 * These values were obtained from disassembling and debugging the
 * PM.exe program installed in the Fujitsu-Siemens AMILO A1655G
 */
#घोषणा A1655_WIFI_COMMAND	0x10C5
#घोषणा A1655_WIFI_ON		0x25
#घोषणा A1655_WIFI_OFF		0x45

अटल पूर्णांक amilo_a1655_rfसमाप्त_set_block(व्योम *data, bool blocked)
अणु
	u8 param = blocked ? A1655_WIFI_OFF : A1655_WIFI_ON;
	पूर्णांक rc;

	i8042_lock_chip();
	rc = i8042_command(&param, A1655_WIFI_COMMAND);
	i8042_unlock_chip();
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops amilo_a1655_rfसमाप्त_ops = अणु
	.set_block = amilo_a1655_rfसमाप्त_set_block
पूर्ण;

/*
 * These values were obtained from disassembling the PM.exe program
 * installed in the Fujitsu-Siemens AMILO M 7440
 */
#घोषणा M7440_PORT1		0x118f
#घोषणा M7440_PORT2		0x118e
#घोषणा M7440_RADIO_ON1		0x12
#घोषणा M7440_RADIO_ON2		0x80
#घोषणा M7440_RADIO_OFF1	0x10
#घोषणा M7440_RADIO_OFF2	0x00

अटल पूर्णांक amilo_m7440_rfसमाप्त_set_block(व्योम *data, bool blocked)
अणु
	u8 val1 = blocked ? M7440_RADIO_OFF1 : M7440_RADIO_ON1;
	u8 val2 = blocked ? M7440_RADIO_OFF2 : M7440_RADIO_ON2;

	outb(val1, M7440_PORT1);
	outb(val2, M7440_PORT2);

	/* Check whether the state has changed correctly */
	अगर (inb(M7440_PORT1) != val1 || inb(M7440_PORT2) != val2)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops amilo_m7440_rfसमाप्त_ops = अणु
	.set_block = amilo_m7440_rfसमाप्त_set_block
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id amilo_rfसमाप्त_id_table[] = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_BOARD_NAME, "AMILO A1655"),
		पूर्ण,
		.driver_data = (व्योम *)&amilo_a1655_rfसमाप्त_ops
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_BOARD_NAME, "AMILO L1310"),
		पूर्ण,
		.driver_data = (व्योम *)&amilo_a1655_rfसमाप्त_ops
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_BOARD_NAME, "AMILO M7440"),
		पूर्ण,
		.driver_data = (व्योम *)&amilo_m7440_rfसमाप्त_ops
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *amilo_rfसमाप्त_pdev;
अटल काष्ठा rfसमाप्त *amilo_rfसमाप्त_dev;

अटल पूर्णांक amilo_rfसमाप्त_probe(काष्ठा platक्रमm_device *device)
अणु
	पूर्णांक rc;
	स्थिर काष्ठा dmi_प्रणाली_id *प्रणाली_id =
		dmi_first_match(amilo_rfसमाप्त_id_table);

	अगर (!प्रणाली_id)
		वापस -ENXIO;

	amilo_rfसमाप्त_dev = rfसमाप्त_alloc(KBUILD_MODNAME, &device->dev,
					RFKILL_TYPE_WLAN,
					प्रणाली_id->driver_data, शून्य);
	अगर (!amilo_rfसमाप्त_dev)
		वापस -ENOMEM;

	rc = rfसमाप्त_रेजिस्टर(amilo_rfसमाप्त_dev);
	अगर (rc)
		जाओ fail;

	वापस 0;

fail:
	rfसमाप्त_destroy(amilo_rfसमाप्त_dev);
	वापस rc;
पूर्ण

अटल पूर्णांक amilo_rfसमाप्त_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	rfसमाप्त_unरेजिस्टर(amilo_rfसमाप्त_dev);
	rfसमाप्त_destroy(amilo_rfसमाप्त_dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver amilo_rfसमाप्त_driver = अणु
	.driver = अणु
		.name	= KBUILD_MODNAME,
	पूर्ण,
	.probe	= amilo_rfसमाप्त_probe,
	.हटाओ	= amilo_rfसमाप्त_हटाओ,
पूर्ण;

अटल पूर्णांक __init amilo_rfसमाप्त_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (dmi_first_match(amilo_rfसमाप्त_id_table) == शून्य)
		वापस -ENODEV;

	rc = platक्रमm_driver_रेजिस्टर(&amilo_rfसमाप्त_driver);
	अगर (rc)
		वापस rc;

	amilo_rfसमाप्त_pdev = platक्रमm_device_रेजिस्टर_simple(KBUILD_MODNAME, -1,
							    शून्य, 0);
	अगर (IS_ERR(amilo_rfसमाप्त_pdev)) अणु
		rc = PTR_ERR(amilo_rfसमाप्त_pdev);
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	platक्रमm_driver_unरेजिस्टर(&amilo_rfसमाप्त_driver);
	वापस rc;
पूर्ण

अटल व्योम __निकास amilo_rfसमाप्त_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(amilo_rfसमाप्त_pdev);
	platक्रमm_driver_unरेजिस्टर(&amilo_rfसमाप्त_driver);
पूर्ण

MODULE_AUTHOR("Ben Hutchings <ben@decadent.org.uk>");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(dmi, amilo_rfसमाप्त_id_table);

module_init(amilo_rfसमाप्त_init);
module_निकास(amilo_rfसमाप्त_निकास);
