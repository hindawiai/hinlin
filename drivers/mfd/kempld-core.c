<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kontron PLD MFD core driver
 *
 * Copyright (c) 2010-2013 Kontron Europe GmbH
 * Author: Michael Brunner <michael.brunner@kontron.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/kempld.h>
#समावेश <linux/module.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/acpi.h>

#घोषणा MAX_ID_LEN 4
अटल अक्षर क्रमce_device_id[MAX_ID_LEN + 1] = "";
module_param_string(क्रमce_device_id, क्रमce_device_id,
		    माप(क्रमce_device_id), 0);
MODULE_PARM_DESC(क्रमce_device_id, "Override detected product");

/*
 * Get hardware mutex to block firmware from accessing the pld.
 * It is possible क्रम the firmware may hold the mutex क्रम an extended length of
 * समय. This function will block until access has been granted.
 */
अटल व्योम kempld_get_hardware_mutex(काष्ठा kempld_device_data *pld)
अणु
	/* The mutex bit will पढ़ो 1 until access has been granted */
	जबतक (ioपढ़ो8(pld->io_index) & KEMPLD_MUTEX_KEY)
		usleep_range(1000, 3000);
पूर्ण

अटल व्योम kempld_release_hardware_mutex(काष्ठा kempld_device_data *pld)
अणु
	/* The harware mutex is released when 1 is written to the mutex bit. */
	ioग_लिखो8(KEMPLD_MUTEX_KEY, pld->io_index);
पूर्ण

अटल पूर्णांक kempld_get_info_generic(काष्ठा kempld_device_data *pld)
अणु
	u16 version;
	u8 spec;

	kempld_get_mutex(pld);

	version = kempld_पढ़ो16(pld, KEMPLD_VERSION);
	spec = kempld_पढ़ो8(pld, KEMPLD_SPEC);
	pld->info.buildnr = kempld_पढ़ो16(pld, KEMPLD_BUILDNR);

	pld->info.minor = KEMPLD_VERSION_GET_MINOR(version);
	pld->info.major = KEMPLD_VERSION_GET_MAJOR(version);
	pld->info.number = KEMPLD_VERSION_GET_NUMBER(version);
	pld->info.type = KEMPLD_VERSION_GET_TYPE(version);

	अगर (spec == 0xff) अणु
		pld->info.spec_minor = 0;
		pld->info.spec_major = 1;
	पूर्ण अन्यथा अणु
		pld->info.spec_minor = KEMPLD_SPEC_GET_MINOR(spec);
		pld->info.spec_major = KEMPLD_SPEC_GET_MAJOR(spec);
	पूर्ण

	अगर (pld->info.spec_major > 0)
		pld->feature_mask = kempld_पढ़ो16(pld, KEMPLD_FEATURE);
	अन्यथा
		pld->feature_mask = 0;

	kempld_release_mutex(pld);

	वापस 0;
पूर्ण

क्रमागत kempld_cells अणु
	KEMPLD_I2C = 0,
	KEMPLD_WDT,
	KEMPLD_GPIO,
	KEMPLD_UART,
पूर्ण;

अटल स्थिर अक्षर *kempld_dev_names[] = अणु
	[KEMPLD_I2C] = "kempld-i2c",
	[KEMPLD_WDT] = "kempld-wdt",
	[KEMPLD_GPIO] = "kempld-gpio",
	[KEMPLD_UART] = "kempld-uart",
पूर्ण;

#घोषणा KEMPLD_MAX_DEVS	ARRAY_SIZE(kempld_dev_names)

अटल पूर्णांक kempld_रेजिस्टर_cells_generic(काष्ठा kempld_device_data *pld)
अणु
	काष्ठा mfd_cell devs[KEMPLD_MAX_DEVS] = अणुपूर्ण;
	पूर्णांक i = 0;

	अगर (pld->feature_mask & KEMPLD_FEATURE_BIT_I2C)
		devs[i++].name = kempld_dev_names[KEMPLD_I2C];

	अगर (pld->feature_mask & KEMPLD_FEATURE_BIT_WATCHDOG)
		devs[i++].name = kempld_dev_names[KEMPLD_WDT];

	अगर (pld->feature_mask & KEMPLD_FEATURE_BIT_GPIO)
		devs[i++].name = kempld_dev_names[KEMPLD_GPIO];

	अगर (pld->feature_mask & KEMPLD_FEATURE_MASK_UART)
		devs[i++].name = kempld_dev_names[KEMPLD_UART];

	वापस mfd_add_devices(pld->dev, -1, devs, i, शून्य, 0, शून्य);
पूर्ण

अटल काष्ठा resource kempld_ioresource = अणु
	.start	= KEMPLD_IOINDEX,
	.end	= KEMPLD_IODATA,
	.flags	= IORESOURCE_IO,
पूर्ण;

अटल स्थिर काष्ठा kempld_platक्रमm_data kempld_platक्रमm_data_generic = अणु
	.pld_घड़ी		= KEMPLD_CLK,
	.ioresource		= &kempld_ioresource,
	.get_hardware_mutex	= kempld_get_hardware_mutex,
	.release_hardware_mutex	= kempld_release_hardware_mutex,
	.get_info		= kempld_get_info_generic,
	.रेजिस्टर_cells		= kempld_रेजिस्टर_cells_generic,
पूर्ण;

अटल काष्ठा platक्रमm_device *kempld_pdev;

अटल पूर्णांक kempld_create_platक्रमm_device(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	स्थिर काष्ठा kempld_platक्रमm_data *pdata = id->driver_data;
	पूर्णांक ret;

	kempld_pdev = platक्रमm_device_alloc("kempld", -1);
	अगर (!kempld_pdev)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(kempld_pdev, pdata, माप(*pdata));
	अगर (ret)
		जाओ err;

	ret = platक्रमm_device_add_resources(kempld_pdev, pdata->ioresource, 1);
	अगर (ret)
		जाओ err;

	ret = platक्रमm_device_add(kempld_pdev);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	platक्रमm_device_put(kempld_pdev);
	वापस ret;
पूर्ण

/**
 * kempld_पढ़ो8 - पढ़ो 8 bit रेजिस्टर
 * @pld: kempld_device_data काष्ठाure describing the PLD
 * @index: रेजिस्टर index on the chip
 *
 * kempld_get_mutex must be called prior to calling this function.
 */
u8 kempld_पढ़ो8(काष्ठा kempld_device_data *pld, u8 index)
अणु
	ioग_लिखो8(index, pld->io_index);
	वापस ioपढ़ो8(pld->io_data);
पूर्ण
EXPORT_SYMBOL_GPL(kempld_पढ़ो8);

/**
 * kempld_ग_लिखो8 - ग_लिखो 8 bit रेजिस्टर
 * @pld: kempld_device_data काष्ठाure describing the PLD
 * @index: रेजिस्टर index on the chip
 * @data: new रेजिस्टर value
 *
 * kempld_get_mutex must be called prior to calling this function.
 */
व्योम kempld_ग_लिखो8(काष्ठा kempld_device_data *pld, u8 index, u8 data)
अणु
	ioग_लिखो8(index, pld->io_index);
	ioग_लिखो8(data, pld->io_data);
पूर्ण
EXPORT_SYMBOL_GPL(kempld_ग_लिखो8);

/**
 * kempld_पढ़ो16 - पढ़ो 16 bit रेजिस्टर
 * @pld: kempld_device_data काष्ठाure describing the PLD
 * @index: रेजिस्टर index on the chip
 *
 * kempld_get_mutex must be called prior to calling this function.
 */
u16 kempld_पढ़ो16(काष्ठा kempld_device_data *pld, u8 index)
अणु
	वापस kempld_पढ़ो8(pld, index) | kempld_पढ़ो8(pld, index + 1) << 8;
पूर्ण
EXPORT_SYMBOL_GPL(kempld_पढ़ो16);

/**
 * kempld_ग_लिखो16 - ग_लिखो 16 bit रेजिस्टर
 * @pld: kempld_device_data काष्ठाure describing the PLD
 * @index: रेजिस्टर index on the chip
 * @data: new रेजिस्टर value
 *
 * kempld_get_mutex must be called prior to calling this function.
 */
व्योम kempld_ग_लिखो16(काष्ठा kempld_device_data *pld, u8 index, u16 data)
अणु
	kempld_ग_लिखो8(pld, index, (u8)data);
	kempld_ग_लिखो8(pld, index + 1, (u8)(data >> 8));
पूर्ण
EXPORT_SYMBOL_GPL(kempld_ग_लिखो16);

/**
 * kempld_पढ़ो32 - पढ़ो 32 bit रेजिस्टर
 * @pld: kempld_device_data काष्ठाure describing the PLD
 * @index: रेजिस्टर index on the chip
 *
 * kempld_get_mutex must be called prior to calling this function.
 */
u32 kempld_पढ़ो32(काष्ठा kempld_device_data *pld, u8 index)
अणु
	वापस kempld_पढ़ो16(pld, index) | kempld_पढ़ो16(pld, index + 2) << 16;
पूर्ण
EXPORT_SYMBOL_GPL(kempld_पढ़ो32);

/**
 * kempld_ग_लिखो32 - ग_लिखो 32 bit रेजिस्टर
 * @pld: kempld_device_data काष्ठाure describing the PLD
 * @index: रेजिस्टर index on the chip
 * @data: new रेजिस्टर value
 *
 * kempld_get_mutex must be called prior to calling this function.
 */
व्योम kempld_ग_लिखो32(काष्ठा kempld_device_data *pld, u8 index, u32 data)
अणु
	kempld_ग_लिखो16(pld, index, (u16)data);
	kempld_ग_लिखो16(pld, index + 2, (u16)(data >> 16));
पूर्ण
EXPORT_SYMBOL_GPL(kempld_ग_लिखो32);

/**
 * kempld_get_mutex - acquire PLD mutex
 * @pld: kempld_device_data काष्ठाure describing the PLD
 */
व्योम kempld_get_mutex(काष्ठा kempld_device_data *pld)
अणु
	स्थिर काष्ठा kempld_platक्रमm_data *pdata = dev_get_platdata(pld->dev);

	mutex_lock(&pld->lock);
	pdata->get_hardware_mutex(pld);
पूर्ण
EXPORT_SYMBOL_GPL(kempld_get_mutex);

/**
 * kempld_release_mutex - release PLD mutex
 * @pld: kempld_device_data काष्ठाure describing the PLD
 */
व्योम kempld_release_mutex(काष्ठा kempld_device_data *pld)
अणु
	स्थिर काष्ठा kempld_platक्रमm_data *pdata = dev_get_platdata(pld->dev);

	pdata->release_hardware_mutex(pld);
	mutex_unlock(&pld->lock);
पूर्ण
EXPORT_SYMBOL_GPL(kempld_release_mutex);

/**
 * kempld_get_info - update device specअगरic inक्रमmation
 * @pld: kempld_device_data काष्ठाure describing the PLD
 *
 * This function calls the configured board specअगरic kempld_get_info_XXXX
 * function which is responsible क्रम gathering inक्रमmation about the specअगरic
 * hardware. The inक्रमmation is then stored within the pld काष्ठाure.
 */
अटल पूर्णांक kempld_get_info(काष्ठा kempld_device_data *pld)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा kempld_platक्रमm_data *pdata = dev_get_platdata(pld->dev);
	अक्षर major, minor;

	ret = pdata->get_info(pld);
	अगर (ret)
		वापस ret;

	/* The Kontron PLD firmware version string has the following क्रमmat:
	 * Pwxy.zzzz
	 *   P:    Fixed
	 *   w:    PLD number    - 1 hex digit
	 *   x:    Major version - 1 alphanumerical digit (0-9A-V)
	 *   y:    Minor version - 1 alphanumerical digit (0-9A-V)
	 *   zzzz: Build number  - 4 zero padded hex digits */

	अगर (pld->info.major < 10)
		major = pld->info.major + '0';
	अन्यथा
		major = (pld->info.major - 10) + 'A';
	अगर (pld->info.minor < 10)
		minor = pld->info.minor + '0';
	अन्यथा
		minor = (pld->info.minor - 10) + 'A';

	ret = scnम_लिखो(pld->info.version, माप(pld->info.version),
			"P%X%c%c.%04X", pld->info.number, major, minor,
			pld->info.buildnr);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * kempld_रेजिस्टर_cells - रेजिस्टर cell drivers
 *
 * This function रेजिस्टरs cell drivers क्रम the detected hardware by calling
 * the configured kempld_रेजिस्टर_cells_XXXX function which is responsible
 * to detect and रेजिस्टर the needed cell drivers.
 */
अटल पूर्णांक kempld_रेजिस्टर_cells(काष्ठा kempld_device_data *pld)
अणु
	स्थिर काष्ठा kempld_platक्रमm_data *pdata = dev_get_platdata(pld->dev);

	वापस pdata->रेजिस्टर_cells(pld);
पूर्ण

अटल स्थिर अक्षर *kempld_get_type_string(काष्ठा kempld_device_data *pld)
अणु
	स्थिर अक्षर *version_type;

	चयन (pld->info.type) अणु
	हाल 0:
		version_type = "release";
		अवरोध;
	हाल 1:
		version_type = "debug";
		अवरोध;
	हाल 2:
		version_type = "custom";
		अवरोध;
	शेष:
		version_type = "unspecified";
		अवरोध;
	पूर्ण

	वापस version_type;
पूर्ण

अटल sमाप_प्रकार kempld_version_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kempld_device_data *pld = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", pld->info.version);
पूर्ण

अटल sमाप_प्रकार kempld_specअगरication_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kempld_device_data *pld = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d.%d\n", pld->info.spec_major,
		       pld->info.spec_minor);
पूर्ण

अटल sमाप_प्रकार kempld_type_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kempld_device_data *pld = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", kempld_get_type_string(pld));
पूर्ण

अटल DEVICE_ATTR(pld_version, S_IRUGO, kempld_version_show, शून्य);
अटल DEVICE_ATTR(pld_specअगरication, S_IRUGO, kempld_specअगरication_show,
		   शून्य);
अटल DEVICE_ATTR(pld_type, S_IRUGO, kempld_type_show, शून्य);

अटल काष्ठा attribute *pld_attributes[] = अणु
	&dev_attr_pld_version.attr,
	&dev_attr_pld_specअगरication.attr,
	&dev_attr_pld_type.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pld_attr_group = अणु
	.attrs = pld_attributes,
पूर्ण;

अटल पूर्णांक kempld_detect_device(काष्ठा kempld_device_data *pld)
अणु
	u8 index_reg;
	पूर्णांक ret;

	mutex_lock(&pld->lock);

	/* Check क्रम empty IO space */
	index_reg = ioपढ़ो8(pld->io_index);
	अगर (index_reg == 0xff && ioपढ़ो8(pld->io_data) == 0xff) अणु
		mutex_unlock(&pld->lock);
		वापस -ENODEV;
	पूर्ण

	/* Release hardware mutex अगर acquired */
	अगर (!(index_reg & KEMPLD_MUTEX_KEY)) अणु
		ioग_लिखो8(KEMPLD_MUTEX_KEY, pld->io_index);
		/* PXT and COMe-cPC2 boards may require a second release */
		ioग_लिखो8(KEMPLD_MUTEX_KEY, pld->io_index);
	पूर्ण

	mutex_unlock(&pld->lock);

	ret = kempld_get_info(pld);
	अगर (ret)
		वापस ret;

	dev_info(pld->dev, "Found Kontron PLD - %s (%s), spec %d.%d\n",
		 pld->info.version, kempld_get_type_string(pld),
		 pld->info.spec_major, pld->info.spec_minor);

	ret = sysfs_create_group(&pld->dev->kobj, &pld_attr_group);
	अगर (ret)
		वापस ret;

	ret = kempld_रेजिस्टर_cells(pld);
	अगर (ret)
		sysfs_हटाओ_group(&pld->dev->kobj, &pld_attr_group);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक kempld_get_acpi_data(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा list_head resource_list;
	काष्ठा resource *resources;
	काष्ठा resource_entry *rentry;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा acpi_device *acpi_dev = ACPI_COMPANION(dev);
	स्थिर काष्ठा kempld_platक्रमm_data *pdata;
	पूर्णांक ret;
	पूर्णांक count;

	pdata = acpi_device_get_match_data(dev);
	ret = platक्रमm_device_add_data(pdev, pdata,
				       माप(काष्ठा kempld_platक्रमm_data));
	अगर (ret)
		वापस ret;

	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(acpi_dev, &resource_list, शून्य, शून्य);
	अगर (ret < 0)
		जाओ out;

	count = ret;

	अगर (count == 0) अणु
		ret = platक्रमm_device_add_resources(pdev, pdata->ioresource, 1);
		जाओ out;
	पूर्ण

	resources = devm_kसुस्मृति(&acpi_dev->dev, count, माप(*resources),
				 GFP_KERNEL);
	अगर (!resources) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	count = 0;
	list_क्रम_each_entry(rentry, &resource_list, node) अणु
		स_नकल(&resources[count], rentry->res,
		       माप(*resources));
		count++;
	पूर्ण
	ret = platक्रमm_device_add_resources(pdev, resources, count);

out:
	acpi_dev_मुक्त_resource_list(&resource_list);

	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक kempld_get_acpi_data(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

अटल पूर्णांक kempld_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा kempld_platक्रमm_data *pdata;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा kempld_device_data *pld;
	काष्ठा resource *ioport;
	पूर्णांक ret;

	अगर (kempld_pdev == शून्य) अणु
		/*
		 * No kempld_pdev device has been रेजिस्टरed in kempld_init,
		 * so we seem to be probing an ACPI platक्रमm device.
		 */
		ret = kempld_get_acpi_data(pdev);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (kempld_pdev != pdev) अणु
		/*
		 * The platक्रमm device we are probing is not the one we
		 * रेजिस्टरed in kempld_init using the DMI table, so this one
		 * comes from ACPI.
		 * As we can only probe one - पात here and use the DMI
		 * based one instead.
		 */
		dev_notice(dev, "platform device exists - not using ACPI\n");
		वापस -ENODEV;
	पूर्ण
	pdata = dev_get_platdata(dev);

	pld = devm_kzalloc(dev, माप(*pld), GFP_KERNEL);
	अगर (!pld)
		वापस -ENOMEM;

	ioport = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!ioport)
		वापस -EINVAL;

	pld->io_base = devm_ioport_map(dev, ioport->start,
					resource_size(ioport));
	अगर (!pld->io_base)
		वापस -ENOMEM;

	pld->io_index = pld->io_base;
	pld->io_data = pld->io_base + 1;
	pld->pld_घड़ी = pdata->pld_घड़ी;
	pld->dev = dev;

	mutex_init(&pld->lock);
	platक्रमm_set_drvdata(pdev, pld);

	वापस kempld_detect_device(pld);
पूर्ण

अटल पूर्णांक kempld_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kempld_device_data *pld = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा kempld_platक्रमm_data *pdata = dev_get_platdata(pld->dev);

	sysfs_हटाओ_group(&pld->dev->kobj, &pld_attr_group);

	mfd_हटाओ_devices(&pdev->dev);
	pdata->release_hardware_mutex(pld);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id kempld_acpi_table[] = अणु
	अणु "KEM0000", (kernel_uदीर्घ_t)&kempld_platक्रमm_data_generic पूर्ण,
	अणु "KEM0001", (kernel_uदीर्घ_t)&kempld_platक्रमm_data_generic पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, kempld_acpi_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver kempld_driver = अणु
	.driver		= अणु
		.name	= "kempld",
		.acpi_match_table = ACPI_PTR(kempld_acpi_table),
	पूर्ण,
	.probe		= kempld_probe,
	.हटाओ		= kempld_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id kempld_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "BBD6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-bBD"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "BBL6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-bBL6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "BDV7",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-bDV7"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "BHL6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-bHL6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "BKL6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-bKL6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "BSL6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-bSL6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CAL6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-cAL"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CBL6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-cBL6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CBW6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-cBW6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CCR2",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-bIP2"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CCR6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-bIP6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CDV7",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-cDV7"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CHL6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-cHL6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CHR2",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "ETXexpress-SC T2"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CHR2",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "ETXe-SC T2"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CHR2",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-bSC2"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CHR6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "ETXexpress-SC T6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CHR6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "ETXe-SC T6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CHR6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-bSC6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CKL6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-cKL6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CNTG",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "ETXexpress-PC"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CNTG",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-bPC2"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CNTX",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "PXT"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CSL6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-cSL6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "CVV6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-cBT"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "FRI2",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BIOS_VERSION, "FRI2"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "FRI2",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Fish River Island II"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "A203",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "KBox A-203"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "M4A1",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-m4AL"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "MAL1",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-mAL10"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "MAPL",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "mITX-APL"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "MBR1",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "ETX-OH"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "MVV1",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-mBT"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "NTC1",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "nanoETXexpress-TT"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "NTC1",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "nETXe-TT"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "NTC1",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-mTT"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "NUP1",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-mCT"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "PAPL",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "pITX-APL"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "SXAL",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "SMARC-sXAL"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "SXAL4",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "SMARC-sXA4"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "UNP1",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "microETXexpress-DC"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "UNP1",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-cDC2"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "UNTG",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "microETXexpress-PC"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "UNTG",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-cPC2"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "UUP6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-cCT6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "UTH6",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "COMe-cTH6"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण, अणु
		.ident = "Q7AL",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Kontron"),
			DMI_MATCH(DMI_BOARD_NAME, "Qseven-Q7AL"),
		पूर्ण,
		.driver_data = (व्योम *)&kempld_platक्रमm_data_generic,
		.callback = kempld_create_platक्रमm_device,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, kempld_dmi_table);

अटल पूर्णांक __init kempld_init(व्योम)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *id;

	अगर (क्रमce_device_id[0]) अणु
		क्रम (id = kempld_dmi_table;
		     id->matches[0].slot != DMI_NONE; id++)
			अगर (म_माला(id->ident, क्रमce_device_id))
				अगर (id->callback && !id->callback(id))
					अवरोध;
		अगर (id->matches[0].slot == DMI_NONE)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		dmi_check_प्रणाली(kempld_dmi_table);
	पूर्ण

	वापस platक्रमm_driver_रेजिस्टर(&kempld_driver);
पूर्ण

अटल व्योम __निकास kempld_निकास(व्योम)
अणु
	अगर (kempld_pdev)
		platक्रमm_device_unरेजिस्टर(kempld_pdev);

	platक्रमm_driver_unरेजिस्टर(&kempld_driver);
पूर्ण

module_init(kempld_init);
module_निकास(kempld_निकास);

MODULE_DESCRIPTION("KEM PLD Core Driver");
MODULE_AUTHOR("Michael Brunner <michael.brunner@kontron.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:kempld-core");
