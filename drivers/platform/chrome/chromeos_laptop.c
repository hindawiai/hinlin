<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Driver to instantiate Chromebook i2c/smbus devices.
//
// Copyright (C) 2012 Google, Inc.
// Author: Benson Leung <bleung@chromium.org>

#घोषणा pr_fmt(fmt)		KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

#घोषणा ATMEL_TP_I2C_ADDR	0x4b
#घोषणा ATMEL_TP_I2C_BL_ADDR	0x25
#घोषणा ATMEL_TS_I2C_ADDR	0x4a
#घोषणा ATMEL_TS_I2C_BL_ADDR	0x26
#घोषणा CYAPA_TP_I2C_ADDR	0x67
#घोषणा ELAN_TP_I2C_ADDR	0x15
#घोषणा ISL_ALS_I2C_ADDR	0x44
#घोषणा TAOS_ALS_I2C_ADDR	0x29

अटल स्थिर अक्षर *i2c_adapter_names[] = अणु
	"SMBus I801 adapter",
	"i915 gmbus vga",
	"i915 gmbus panel",
	"Synopsys DesignWare I2C adapter",
पूर्ण;

/* Keep this क्रमागत consistent with i2c_adapter_names */
क्रमागत i2c_adapter_type अणु
	I2C_ADAPTER_SMBUS = 0,
	I2C_ADAPTER_VGADDC,
	I2C_ADAPTER_PANEL,
	I2C_ADAPTER_DESIGNWARE,
पूर्ण;

काष्ठा i2c_peripheral अणु
	काष्ठा i2c_board_info board_info;
	अचिन्हित लघु alt_addr;

	स्थिर अक्षर *dmi_name;
	अचिन्हित दीर्घ irqflags;
	काष्ठा resource irq_resource;

	क्रमागत i2c_adapter_type type;
	u32 pci_devid;

	स्थिर काष्ठा property_entry *properties;

	काष्ठा i2c_client *client;
पूर्ण;

काष्ठा acpi_peripheral अणु
	अक्षर hid[ACPI_ID_LEN];
	काष्ठा software_node swnode;
	काष्ठा i2c_client *client;
पूर्ण;

काष्ठा chromeos_laptop अणु
	/*
	 * Note that we can't mark this poपूर्णांकer as स्थिर because
	 * i2c_new_scanned_device() changes passed in I2C board info, so.
	 */
	काष्ठा i2c_peripheral *i2c_peripherals;
	अचिन्हित पूर्णांक num_i2c_peripherals;

	काष्ठा acpi_peripheral *acpi_peripherals;
	अचिन्हित पूर्णांक num_acpi_peripherals;
पूर्ण;

अटल स्थिर काष्ठा chromeos_laptop *cros_laptop;

अटल काष्ठा i2c_client *
chromes_laptop_instantiate_i2c_device(काष्ठा i2c_adapter *adapter,
				      काष्ठा i2c_board_info *info,
				      अचिन्हित लघु alt_addr)
अणु
	स्थिर अचिन्हित लघु addr_list[] = अणु info->addr, I2C_CLIENT_END पूर्ण;
	काष्ठा i2c_client *client;

	/*
	 * Add the i2c device. If we can't detect it at the primary
	 * address we scan secondary addresses. In any हाल the client
	 * काष्ठाure माला_लो asचिन्हित primary address.
	 */
	client = i2c_new_scanned_device(adapter, info, addr_list, शून्य);
	अगर (IS_ERR(client) && alt_addr) अणु
		काष्ठा i2c_board_info dummy_info = अणु
			I2C_BOARD_INFO("dummy", info->addr),
		पूर्ण;
		स्थिर अचिन्हित लघु alt_addr_list[] = अणु
			alt_addr, I2C_CLIENT_END
		पूर्ण;
		काष्ठा i2c_client *dummy;

		dummy = i2c_new_scanned_device(adapter, &dummy_info,
					       alt_addr_list, शून्य);
		अगर (!IS_ERR(dummy)) अणु
			pr_debug("%d-%02x is probed at %02x\n",
				 adapter->nr, info->addr, dummy->addr);
			i2c_unरेजिस्टर_device(dummy);
			client = i2c_new_client_device(adapter, info);
		पूर्ण
	पूर्ण

	अगर (IS_ERR(client)) अणु
		client = शून्य;
		pr_debug("failed to register device %d-%02x\n",
			 adapter->nr, info->addr);
	पूर्ण अन्यथा अणु
		pr_debug("added i2c device %d-%02x\n",
			 adapter->nr, info->addr);
	पूर्ण

	वापस client;
पूर्ण

अटल bool chromeos_laptop_match_adapter_devid(काष्ठा device *dev, u32 devid)
अणु
	काष्ठा pci_dev *pdev;

	अगर (!dev_is_pci(dev))
		वापस false;

	pdev = to_pci_dev(dev);
	वापस devid == pci_dev_id(pdev);
पूर्ण

अटल व्योम chromeos_laptop_check_adapter(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा i2c_peripheral *i2c_dev;
	पूर्णांक i;

	क्रम (i = 0; i < cros_laptop->num_i2c_peripherals; i++) अणु
		i2c_dev = &cros_laptop->i2c_peripherals[i];

		/* Skip devices alपढ़ोy created */
		अगर (i2c_dev->client)
			जारी;

		अगर (म_भेदन(adapter->name, i2c_adapter_names[i2c_dev->type],
			    म_माप(i2c_adapter_names[i2c_dev->type])))
			जारी;

		अगर (i2c_dev->pci_devid &&
		    !chromeos_laptop_match_adapter_devid(adapter->dev.parent,
							 i2c_dev->pci_devid)) अणु
			जारी;
		पूर्ण

		i2c_dev->client =
			chromes_laptop_instantiate_i2c_device(adapter,
							&i2c_dev->board_info,
							i2c_dev->alt_addr);
	पूर्ण
पूर्ण

अटल bool chromeos_laptop_adjust_client(काष्ठा i2c_client *client)
अणु
	काष्ठा acpi_peripheral *acpi_dev;
	काष्ठा acpi_device_id acpi_ids[2] = अणु पूर्ण;
	पूर्णांक i;
	पूर्णांक error;

	अगर (!has_acpi_companion(&client->dev))
		वापस false;

	क्रम (i = 0; i < cros_laptop->num_acpi_peripherals; i++) अणु
		acpi_dev = &cros_laptop->acpi_peripherals[i];

		स_नकल(acpi_ids[0].id, acpi_dev->hid, ACPI_ID_LEN);

		अगर (acpi_match_device(acpi_ids, &client->dev)) अणु
			error = device_add_software_node(&client->dev, &acpi_dev->swnode);
			अगर (error) अणु
				dev_err(&client->dev,
					"failed to add properties: %d\n",
					error);
				अवरोध;
			पूर्ण

			acpi_dev->client = client;

			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम chromeos_laptop_detach_i2c_client(काष्ठा i2c_client *client)
अणु
	काष्ठा acpi_peripheral *acpi_dev;
	काष्ठा i2c_peripheral *i2c_dev;
	पूर्णांक i;

	अगर (has_acpi_companion(&client->dev))
		क्रम (i = 0; i < cros_laptop->num_acpi_peripherals; i++) अणु
			acpi_dev = &cros_laptop->acpi_peripherals[i];

			अगर (acpi_dev->client == client) अणु
				acpi_dev->client = शून्य;
				वापस;
			पूर्ण
		पूर्ण
	अन्यथा
		क्रम (i = 0; i < cros_laptop->num_i2c_peripherals; i++) अणु
			i2c_dev = &cros_laptop->i2c_peripherals[i];

			अगर (i2c_dev->client == client) अणु
				i2c_dev->client = शून्य;
				वापस;
			पूर्ण
		पूर्ण
पूर्ण

अटल पूर्णांक chromeos_laptop_i2c_notअगरier_call(काष्ठा notअगरier_block *nb,
					     अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा device *dev = data;

	चयन (action) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		अगर (dev->type == &i2c_adapter_type)
			chromeos_laptop_check_adapter(to_i2c_adapter(dev));
		अन्यथा अगर (dev->type == &i2c_client_type)
			chromeos_laptop_adjust_client(to_i2c_client(dev));
		अवरोध;

	हाल BUS_NOTIFY_REMOVED_DEVICE:
		अगर (dev->type == &i2c_client_type)
			chromeos_laptop_detach_i2c_client(to_i2c_client(dev));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block chromeos_laptop_i2c_notअगरier = अणु
	.notअगरier_call = chromeos_laptop_i2c_notअगरier_call,
पूर्ण;

#घोषणा DECLARE_CROS_LAPTOP(_name)					\
अटल स्थिर काष्ठा chromeos_laptop _name __initस्थिर = अणु		\
	.i2c_peripherals	= _name##_peripherals,			\
	.num_i2c_peripherals	= ARRAY_SIZE(_name##_peripherals),	\
पूर्ण

#घोषणा DECLARE_ACPI_CROS_LAPTOP(_name)					\
अटल स्थिर काष्ठा chromeos_laptop _name __initस्थिर = अणु		\
	.acpi_peripherals	= _name##_peripherals,			\
	.num_acpi_peripherals	= ARRAY_SIZE(_name##_peripherals),	\
पूर्ण

अटल काष्ठा i2c_peripheral samsung_series_5_550_peripherals[] __initdata = अणु
	/* Touchpad. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("cyapa", CYAPA_TP_I2C_ADDR),
			.flags		= I2C_CLIENT_WAKE,
		पूर्ण,
		.dmi_name	= "trackpad",
		.type		= I2C_ADAPTER_SMBUS,
	पूर्ण,
	/* Light Sensor. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("isl29018", ISL_ALS_I2C_ADDR),
		पूर्ण,
		.dmi_name	= "lightsensor",
		.type		= I2C_ADAPTER_SMBUS,
	पूर्ण,
पूर्ण;
DECLARE_CROS_LAPTOP(samsung_series_5_550);

अटल काष्ठा i2c_peripheral samsung_series_5_peripherals[] __initdata = अणु
	/* Light Sensor. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("tsl2583", TAOS_ALS_I2C_ADDR),
		पूर्ण,
		.type		= I2C_ADAPTER_SMBUS,
	पूर्ण,
पूर्ण;
DECLARE_CROS_LAPTOP(samsung_series_5);

अटल स्थिर पूर्णांक chromebook_pixel_tp_keys[] __initस्थिर = अणु
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	BTN_LEFT
पूर्ण;

अटल स्थिर काष्ठा property_entry
chromebook_pixel_trackpad_props[] __initस्थिर = अणु
	PROPERTY_ENTRY_STRING("compatible", "atmel,maxtouch"),
	PROPERTY_ENTRY_U32_ARRAY("linux,gpio-keymap", chromebook_pixel_tp_keys),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा property_entry
chromebook_aपंचांगel_touchscreen_props[] __initस्थिर = अणु
	PROPERTY_ENTRY_STRING("compatible", "atmel,maxtouch"),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_peripheral chromebook_pixel_peripherals[] __initdata = अणु
	/* Touch Screen. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("atmel_mxt_ts",
					ATMEL_TS_I2C_ADDR),
			.flags		= I2C_CLIENT_WAKE,
		पूर्ण,
		.dmi_name	= "touchscreen",
		.irqflags	= IRQF_TRIGGER_FALLING,
		.type		= I2C_ADAPTER_PANEL,
		.alt_addr	= ATMEL_TS_I2C_BL_ADDR,
		.properties	= chromebook_aपंचांगel_touchscreen_props,
	पूर्ण,
	/* Touchpad. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("atmel_mxt_tp",
					ATMEL_TP_I2C_ADDR),
			.flags		= I2C_CLIENT_WAKE,
		पूर्ण,
		.dmi_name	= "trackpad",
		.irqflags	= IRQF_TRIGGER_FALLING,
		.type		= I2C_ADAPTER_VGADDC,
		.alt_addr	= ATMEL_TP_I2C_BL_ADDR,
		.properties	= chromebook_pixel_trackpad_props,
	पूर्ण,
	/* Light Sensor. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("isl29018", ISL_ALS_I2C_ADDR),
		पूर्ण,
		.dmi_name	= "lightsensor",
		.type		= I2C_ADAPTER_PANEL,
	पूर्ण,
पूर्ण;
DECLARE_CROS_LAPTOP(chromebook_pixel);

अटल काष्ठा i2c_peripheral hp_chromebook_14_peripherals[] __initdata = अणु
	/* Touchpad. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("cyapa", CYAPA_TP_I2C_ADDR),
			.flags		= I2C_CLIENT_WAKE,
		पूर्ण,
		.dmi_name	= "trackpad",
		.type		= I2C_ADAPTER_DESIGNWARE,
	पूर्ण,
पूर्ण;
DECLARE_CROS_LAPTOP(hp_chromebook_14);

अटल काष्ठा i2c_peripheral dell_chromebook_11_peripherals[] __initdata = अणु
	/* Touchpad. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("cyapa", CYAPA_TP_I2C_ADDR),
			.flags		= I2C_CLIENT_WAKE,
		पूर्ण,
		.dmi_name	= "trackpad",
		.type		= I2C_ADAPTER_DESIGNWARE,
	पूर्ण,
	/* Elan Touchpad option. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("elan_i2c", ELAN_TP_I2C_ADDR),
			.flags		= I2C_CLIENT_WAKE,
		पूर्ण,
		.dmi_name	= "trackpad",
		.type		= I2C_ADAPTER_DESIGNWARE,
	पूर्ण,
पूर्ण;
DECLARE_CROS_LAPTOP(dell_chromebook_11);

अटल काष्ठा i2c_peripheral toshiba_cb35_peripherals[] __initdata = अणु
	/* Touchpad. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("cyapa", CYAPA_TP_I2C_ADDR),
			.flags		= I2C_CLIENT_WAKE,
		पूर्ण,
		.dmi_name	= "trackpad",
		.type		= I2C_ADAPTER_DESIGNWARE,
	पूर्ण,
पूर्ण;
DECLARE_CROS_LAPTOP(toshiba_cb35);

अटल काष्ठा i2c_peripheral acer_c7_chromebook_peripherals[] __initdata = अणु
	/* Touchpad. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("cyapa", CYAPA_TP_I2C_ADDR),
			.flags		= I2C_CLIENT_WAKE,
		पूर्ण,
		.dmi_name	= "trackpad",
		.type		= I2C_ADAPTER_SMBUS,
	पूर्ण,
पूर्ण;
DECLARE_CROS_LAPTOP(acer_c7_chromebook);

अटल काष्ठा i2c_peripheral acer_ac700_peripherals[] __initdata = अणु
	/* Light Sensor. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("tsl2583", TAOS_ALS_I2C_ADDR),
		पूर्ण,
		.type		= I2C_ADAPTER_SMBUS,
	पूर्ण,
पूर्ण;
DECLARE_CROS_LAPTOP(acer_ac700);

अटल काष्ठा i2c_peripheral acer_c720_peripherals[] __initdata = अणु
	/* Touchscreen. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("atmel_mxt_ts",
					ATMEL_TS_I2C_ADDR),
			.flags		= I2C_CLIENT_WAKE,
		पूर्ण,
		.dmi_name	= "touchscreen",
		.irqflags	= IRQF_TRIGGER_FALLING,
		.type		= I2C_ADAPTER_DESIGNWARE,
		.pci_devid	= PCI_DEVID(0, PCI_DEVFN(0x15, 0x2)),
		.alt_addr	= ATMEL_TS_I2C_BL_ADDR,
		.properties	= chromebook_aपंचांगel_touchscreen_props,
	पूर्ण,
	/* Touchpad. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("cyapa", CYAPA_TP_I2C_ADDR),
			.flags		= I2C_CLIENT_WAKE,
		पूर्ण,
		.dmi_name	= "trackpad",
		.type		= I2C_ADAPTER_DESIGNWARE,
		.pci_devid	= PCI_DEVID(0, PCI_DEVFN(0x15, 0x1)),
	पूर्ण,
	/* Elan Touchpad option. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("elan_i2c", ELAN_TP_I2C_ADDR),
			.flags		= I2C_CLIENT_WAKE,
		पूर्ण,
		.dmi_name	= "trackpad",
		.type		= I2C_ADAPTER_DESIGNWARE,
		.pci_devid	= PCI_DEVID(0, PCI_DEVFN(0x15, 0x1)),
	पूर्ण,
	/* Light Sensor. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("isl29018", ISL_ALS_I2C_ADDR),
		पूर्ण,
		.dmi_name	= "lightsensor",
		.type		= I2C_ADAPTER_DESIGNWARE,
		.pci_devid	= PCI_DEVID(0, PCI_DEVFN(0x15, 0x2)),
	पूर्ण,
पूर्ण;
DECLARE_CROS_LAPTOP(acer_c720);

अटल काष्ठा i2c_peripheral
hp_pavilion_14_chromebook_peripherals[] __initdata = अणु
	/* Touchpad. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("cyapa", CYAPA_TP_I2C_ADDR),
			.flags		= I2C_CLIENT_WAKE,
		पूर्ण,
		.dmi_name	= "trackpad",
		.type		= I2C_ADAPTER_SMBUS,
	पूर्ण,
पूर्ण;
DECLARE_CROS_LAPTOP(hp_pavilion_14_chromebook);

अटल काष्ठा i2c_peripheral cr48_peripherals[] __initdata = अणु
	/* Light Sensor. */
	अणु
		.board_info	= अणु
			I2C_BOARD_INFO("tsl2563", TAOS_ALS_I2C_ADDR),
		पूर्ण,
		.type		= I2C_ADAPTER_SMBUS,
	पूर्ण,
पूर्ण;
DECLARE_CROS_LAPTOP(cr48);

अटल स्थिर u32 samus_touchpad_buttons[] __initस्थिर = अणु
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	BTN_LEFT
पूर्ण;

अटल स्थिर काष्ठा property_entry samus_trackpad_props[] __initस्थिर = अणु
	PROPERTY_ENTRY_STRING("compatible", "atmel,maxtouch"),
	PROPERTY_ENTRY_U32_ARRAY("linux,gpio-keymap", samus_touchpad_buttons),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा acpi_peripheral samus_peripherals[] __initdata = अणु
	/* Touchpad */
	अणु
		.hid		= "ATML0000",
		.swnode		= अणु
			.properties = samus_trackpad_props,
		पूर्ण,
	पूर्ण,
	/* Touchsceen */
	अणु
		.hid		= "ATML0001",
		.swnode		= अणु
			.properties = chromebook_aपंचांगel_touchscreen_props,
		पूर्ण,
	पूर्ण,
पूर्ण;
DECLARE_ACPI_CROS_LAPTOP(samus);

अटल काष्ठा acpi_peripheral generic_aपंचांगel_peripherals[] __initdata = अणु
	/* Touchpad */
	अणु
		.hid		= "ATML0000",
		.swnode		= अणु
			.properties = chromebook_pixel_trackpad_props,
		पूर्ण,
	पूर्ण,
	/* Touchsceen */
	अणु
		.hid		= "ATML0001",
		.swnode		= अणु
			.properties = chromebook_aपंचांगel_touchscreen_props,
		पूर्ण,
	पूर्ण,
पूर्ण;
DECLARE_ACPI_CROS_LAPTOP(generic_aपंचांगel);

अटल स्थिर काष्ठा dmi_प्रणाली_id chromeos_laptop_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "Samsung Series 5 550",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Lumpy"),
		पूर्ण,
		.driver_data = (व्योम *)&samsung_series_5_550,
	पूर्ण,
	अणु
		.ident = "Samsung Series 5",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Alex"),
		पूर्ण,
		.driver_data = (व्योम *)&samsung_series_5,
	पूर्ण,
	अणु
		.ident = "Chromebook Pixel",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Link"),
		पूर्ण,
		.driver_data = (व्योम *)&chromebook_pixel,
	पूर्ण,
	अणु
		.ident = "Wolf",
		.matches = अणु
			DMI_MATCH(DMI_BIOS_VENDOR, "coreboot"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Wolf"),
		पूर्ण,
		.driver_data = (व्योम *)&dell_chromebook_11,
	पूर्ण,
	अणु
		.ident = "HP Chromebook 14",
		.matches = अणु
			DMI_MATCH(DMI_BIOS_VENDOR, "coreboot"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Falco"),
		पूर्ण,
		.driver_data = (व्योम *)&hp_chromebook_14,
	पूर्ण,
	अणु
		.ident = "Toshiba CB35",
		.matches = अणु
			DMI_MATCH(DMI_BIOS_VENDOR, "coreboot"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Leon"),
		पूर्ण,
		.driver_data = (व्योम *)&toshiba_cb35,
	पूर्ण,
	अणु
		.ident = "Acer C7 Chromebook",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Parrot"),
		पूर्ण,
		.driver_data = (व्योम *)&acer_c7_chromebook,
	पूर्ण,
	अणु
		.ident = "Acer AC700",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "ZGB"),
		पूर्ण,
		.driver_data = (व्योम *)&acer_ac700,
	पूर्ण,
	अणु
		.ident = "Acer C720",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Peppy"),
		पूर्ण,
		.driver_data = (व्योम *)&acer_c720,
	पूर्ण,
	अणु
		.ident = "HP Pavilion 14 Chromebook",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Butterfly"),
		पूर्ण,
		.driver_data = (व्योम *)&hp_pavilion_14_chromebook,
	पूर्ण,
	अणु
		.ident = "Cr-48",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Mario"),
		पूर्ण,
		.driver_data = (व्योम *)&cr48,
	पूर्ण,
	/* Devices with peripherals incompletely described in ACPI */
	अणु
		.ident = "Chromebook Pro",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Google"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Caroline"),
		पूर्ण,
		.driver_data = (व्योम *)&samus,
	पूर्ण,
	अणु
		.ident = "Google Pixel 2 (2015)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Samus"),
		पूर्ण,
		.driver_data = (व्योम *)&samus,
	पूर्ण,
	अणु
		.ident = "Samsung Chromebook 3",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Celes"),
		पूर्ण,
		.driver_data = (व्योम *)&samus,
	पूर्ण,
	अणु
		/*
		 * Other Chromebooks with Aपंचांगel touch controllers:
		 * - Winky (touchpad)
		 * - Clapper, Expresso, Rambi, Glimmer (touchscreen)
		 */
		.ident = "Other Chromebook",
		.matches = अणु
			/*
			 * This will match all Google devices, not only devices
			 * with Aपंचांगel, but we will validate that the device
			 * actually has matching peripherals.
			 */
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
		पूर्ण,
		.driver_data = (व्योम *)&generic_aपंचांगel,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, chromeos_laptop_dmi_table);

अटल पूर्णांक __init chromeos_laptop_scan_peripherals(काष्ठा device *dev, व्योम *data)
अणु
	पूर्णांक error;

	अगर (dev->type == &i2c_adapter_type) अणु
		chromeos_laptop_check_adapter(to_i2c_adapter(dev));
	पूर्ण अन्यथा अगर (dev->type == &i2c_client_type) अणु
		अगर (chromeos_laptop_adjust_client(to_i2c_client(dev))) अणु
			/*
			 * Now that we have needed properties re-trigger
			 * driver probe in हाल driver was initialized
			 * earlier and probe failed.
			 */
			error = device_attach(dev);
			अगर (error < 0)
				dev_warn(dev,
					 "%s: device_attach() failed: %d\n",
					 __func__, error);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init chromeos_laptop_get_irq_from_dmi(स्थिर अक्षर *dmi_name)
अणु
	स्थिर काष्ठा dmi_device *dmi_dev;
	स्थिर काष्ठा dmi_dev_onboard *dev_data;

	dmi_dev = dmi_find_device(DMI_DEV_TYPE_DEV_ONBOARD, dmi_name, शून्य);
	अगर (!dmi_dev) अणु
		pr_err("failed to find DMI device '%s'\n", dmi_name);
		वापस -ENOENT;
	पूर्ण

	dev_data = dmi_dev->device_data;
	अगर (!dev_data) अणु
		pr_err("failed to get data from DMI for '%s'\n", dmi_name);
		वापस -EINVAL;
	पूर्ण

	वापस dev_data->instance;
पूर्ण

अटल पूर्णांक __init chromeos_laptop_setup_irq(काष्ठा i2c_peripheral *i2c_dev)
अणु
	पूर्णांक irq;

	अगर (i2c_dev->dmi_name) अणु
		irq = chromeos_laptop_get_irq_from_dmi(i2c_dev->dmi_name);
		अगर (irq < 0)
			वापस irq;

		i2c_dev->irq_resource  = (काष्ठा resource)
			DEFINE_RES_NAMED(irq, 1, शून्य,
					 IORESOURCE_IRQ | i2c_dev->irqflags);
		i2c_dev->board_info.resources = &i2c_dev->irq_resource;
		i2c_dev->board_info.num_resources = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init
chromeos_laptop_prepare_i2c_peripherals(काष्ठा chromeos_laptop *cros_laptop,
					स्थिर काष्ठा chromeos_laptop *src)
अणु
	काष्ठा i2c_peripheral *i2c_dev;
	काष्ठा i2c_board_info *info;
	पूर्णांक i;
	पूर्णांक error;

	अगर (!src->num_i2c_peripherals)
		वापस 0;

	cros_laptop->i2c_peripherals = kmemdup(src->i2c_peripherals,
					       src->num_i2c_peripherals *
						माप(*src->i2c_peripherals),
					       GFP_KERNEL);
	अगर (!cros_laptop->i2c_peripherals)
		वापस -ENOMEM;

	cros_laptop->num_i2c_peripherals = src->num_i2c_peripherals;

	क्रम (i = 0; i < cros_laptop->num_i2c_peripherals; i++) अणु
		i2c_dev = &cros_laptop->i2c_peripherals[i];
		info = &i2c_dev->board_info;

		error = chromeos_laptop_setup_irq(i2c_dev);
		अगर (error)
			जाओ err_out;

		/* Create primary fwnode क्रम the device - copies everything */
		अगर (i2c_dev->properties) अणु
			info->fwnode = fwnode_create_software_node(i2c_dev->properties, शून्य);
			अगर (IS_ERR(info->fwnode)) अणु
				error = PTR_ERR(info->fwnode);
				जाओ err_out;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

err_out:
	जबतक (--i >= 0) अणु
		i2c_dev = &cros_laptop->i2c_peripherals[i];
		info = &i2c_dev->board_info;
		अगर (!IS_ERR_OR_शून्य(info->fwnode))
			fwnode_हटाओ_software_node(info->fwnode);
	पूर्ण
	kमुक्त(cros_laptop->i2c_peripherals);
	वापस error;
पूर्ण

अटल पूर्णांक __init
chromeos_laptop_prepare_acpi_peripherals(काष्ठा chromeos_laptop *cros_laptop,
					स्थिर काष्ठा chromeos_laptop *src)
अणु
	काष्ठा acpi_peripheral *acpi_peripherals;
	काष्ठा acpi_peripheral *acpi_dev;
	स्थिर काष्ठा acpi_peripheral *src_dev;
	पूर्णांक n_peripherals = 0;
	पूर्णांक i;
	पूर्णांक error;

	क्रम (i = 0; i < src->num_acpi_peripherals; i++) अणु
		अगर (acpi_dev_present(src->acpi_peripherals[i].hid, शून्य, -1))
			n_peripherals++;
	पूर्ण

	अगर (!n_peripherals)
		वापस 0;

	acpi_peripherals = kसुस्मृति(n_peripherals,
				   माप(*src->acpi_peripherals),
				   GFP_KERNEL);
	अगर (!acpi_peripherals)
		वापस -ENOMEM;

	acpi_dev = acpi_peripherals;
	क्रम (i = 0; i < src->num_acpi_peripherals; i++) अणु
		src_dev = &src->acpi_peripherals[i];
		अगर (!acpi_dev_present(src_dev->hid, शून्य, -1))
			जारी;

		*acpi_dev = *src_dev;

		/* We need to deep-copy properties */
		अगर (src_dev->swnode.properties) अणु
			acpi_dev->swnode.properties =
				property_entries_dup(src_dev->swnode.properties);
			अगर (IS_ERR(acpi_dev->swnode.properties)) अणु
				error = PTR_ERR(acpi_dev->swnode.properties);
				जाओ err_out;
			पूर्ण
		पूर्ण

		acpi_dev++;
	पूर्ण

	cros_laptop->acpi_peripherals = acpi_peripherals;
	cros_laptop->num_acpi_peripherals = n_peripherals;

	वापस 0;

err_out:
	जबतक (--i >= 0) अणु
		acpi_dev = &acpi_peripherals[i];
		अगर (!IS_ERR_OR_शून्य(acpi_dev->swnode.properties))
			property_entries_मुक्त(acpi_dev->swnode.properties);
	पूर्ण

	kमुक्त(acpi_peripherals);
	वापस error;
पूर्ण

अटल व्योम chromeos_laptop_destroy(स्थिर काष्ठा chromeos_laptop *cros_laptop)
अणु
	स्थिर काष्ठा acpi_peripheral *acpi_dev;
	काष्ठा i2c_peripheral *i2c_dev;
	पूर्णांक i;

	क्रम (i = 0; i < cros_laptop->num_i2c_peripherals; i++) अणु
		i2c_dev = &cros_laptop->i2c_peripherals[i];
		i2c_unरेजिस्टर_device(i2c_dev->client);
	पूर्ण

	क्रम (i = 0; i < cros_laptop->num_acpi_peripherals; i++) अणु
		acpi_dev = &cros_laptop->acpi_peripherals[i];

		अगर (acpi_dev->client)
			device_हटाओ_software_node(&acpi_dev->client->dev);

		property_entries_मुक्त(acpi_dev->swnode.properties);
	पूर्ण

	kमुक्त(cros_laptop->i2c_peripherals);
	kमुक्त(cros_laptop->acpi_peripherals);
	kमुक्त(cros_laptop);
पूर्ण

अटल काष्ठा chromeos_laptop * __init
chromeos_laptop_prepare(स्थिर काष्ठा chromeos_laptop *src)
अणु
	काष्ठा chromeos_laptop *cros_laptop;
	पूर्णांक error;

	cros_laptop = kzalloc(माप(*cros_laptop), GFP_KERNEL);
	अगर (!cros_laptop)
		वापस ERR_PTR(-ENOMEM);

	error = chromeos_laptop_prepare_i2c_peripherals(cros_laptop, src);
	अगर (!error)
		error = chromeos_laptop_prepare_acpi_peripherals(cros_laptop,
								 src);

	अगर (error) अणु
		chromeos_laptop_destroy(cros_laptop);
		वापस ERR_PTR(error);
	पूर्ण

	वापस cros_laptop;
पूर्ण

अटल पूर्णांक __init chromeos_laptop_init(व्योम)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;
	पूर्णांक error;

	dmi_id = dmi_first_match(chromeos_laptop_dmi_table);
	अगर (!dmi_id) अणु
		pr_debug("unsupported system\n");
		वापस -ENODEV;
	पूर्ण

	pr_debug("DMI Matched %s\n", dmi_id->ident);

	cros_laptop = chromeos_laptop_prepare((व्योम *)dmi_id->driver_data);
	अगर (IS_ERR(cros_laptop))
		वापस PTR_ERR(cros_laptop);

	अगर (!cros_laptop->num_i2c_peripherals &&
	    !cros_laptop->num_acpi_peripherals) अणु
		pr_debug("no relevant devices detected\n");
		error = -ENODEV;
		जाओ err_destroy_cros_laptop;
	पूर्ण

	error = bus_रेजिस्टर_notअगरier(&i2c_bus_type,
				      &chromeos_laptop_i2c_notअगरier);
	अगर (error) अणु
		pr_err("failed to register i2c bus notifier: %d\n",
		       error);
		जाओ err_destroy_cros_laptop;
	पूर्ण

	/*
	 * Scan adapters that have been रेजिस्टरed and clients that have
	 * been created beक्रमe we installed the notअगरier to make sure
	 * we करो not miss any devices.
	 */
	i2c_क्रम_each_dev(शून्य, chromeos_laptop_scan_peripherals);

	वापस 0;

err_destroy_cros_laptop:
	chromeos_laptop_destroy(cros_laptop);
	वापस error;
पूर्ण

अटल व्योम __निकास chromeos_laptop_निकास(व्योम)
अणु
	bus_unरेजिस्टर_notअगरier(&i2c_bus_type, &chromeos_laptop_i2c_notअगरier);
	chromeos_laptop_destroy(cros_laptop);
पूर्ण

module_init(chromeos_laptop_init);
module_निकास(chromeos_laptop_निकास);

MODULE_DESCRIPTION("Chrome OS Laptop driver");
MODULE_AUTHOR("Benson Leung <bleung@chromium.org>");
MODULE_LICENSE("GPL");
