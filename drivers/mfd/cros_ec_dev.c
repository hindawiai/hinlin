<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cros_ec_dev - expose the Chrome OS Embedded Controller to user-space
 *
 * Copyright (C) 2014 Google, Inc.
 */

#समावेश <linux/kconfig.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/cros_ec_अक्षरdev.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/slab.h>

#घोषणा DRV_NAME "cros-ec-dev"

अटल काष्ठा class cros_class = अणु
	.owner          = THIS_MODULE,
	.name           = "chromeos",
पूर्ण;

/**
 * काष्ठा cros_feature_to_name - CrOS feature id to name/लघु description.
 * @id: The feature identअगरier.
 * @name: Device name associated with the feature id.
 * @desc: Short name that will be displayed.
 */
काष्ठा cros_feature_to_name अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *desc;
पूर्ण;

/**
 * काष्ठा cros_feature_to_cells - CrOS feature id to mfd cells association.
 * @id: The feature identअगरier.
 * @mfd_cells: Poपूर्णांकer to the array of mfd cells that needs to be added.
 * @num_cells: Number of mfd cells पूर्णांकo the array.
 */
काष्ठा cros_feature_to_cells अणु
	अचिन्हित पूर्णांक id;
	स्थिर काष्ठा mfd_cell *mfd_cells;
	अचिन्हित पूर्णांक num_cells;
पूर्ण;

अटल स्थिर काष्ठा cros_feature_to_name cros_mcu_devices[] = अणु
	अणु
		.id	= EC_FEATURE_FINGERPRINT,
		.name	= CROS_EC_DEV_FP_NAME,
		.desc	= "Fingerprint",
	पूर्ण,
	अणु
		.id	= EC_FEATURE_ISH,
		.name	= CROS_EC_DEV_ISH_NAME,
		.desc	= "Integrated Sensor Hub",
	पूर्ण,
	अणु
		.id	= EC_FEATURE_SCP,
		.name	= CROS_EC_DEV_SCP_NAME,
		.desc	= "System Control Processor",
	पूर्ण,
	अणु
		.id	= EC_FEATURE_TOUCHPAD,
		.name	= CROS_EC_DEV_TP_NAME,
		.desc	= "Touchpad",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cros_ec_cec_cells[] = अणु
	अणु .name = "cros-ec-cec", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cros_ec_rtc_cells[] = अणु
	अणु .name = "cros-ec-rtc", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cros_ec_sensorhub_cells[] = अणु
	अणु .name = "cros-ec-sensorhub", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cros_usbpd_अक्षरger_cells[] = अणु
	अणु .name = "cros-usbpd-charger", पूर्ण,
	अणु .name = "cros-usbpd-logger", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cros_usbpd_notअगरy_cells[] = अणु
	अणु .name = "cros-usbpd-notify", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cros_feature_to_cells cros_subdevices[] = अणु
	अणु
		.id		= EC_FEATURE_CEC,
		.mfd_cells	= cros_ec_cec_cells,
		.num_cells	= ARRAY_SIZE(cros_ec_cec_cells),
	पूर्ण,
	अणु
		.id		= EC_FEATURE_RTC,
		.mfd_cells	= cros_ec_rtc_cells,
		.num_cells	= ARRAY_SIZE(cros_ec_rtc_cells),
	पूर्ण,
	अणु
		.id		= EC_FEATURE_USB_PD,
		.mfd_cells	= cros_usbpd_अक्षरger_cells,
		.num_cells	= ARRAY_SIZE(cros_usbpd_अक्षरger_cells),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cros_ec_platक्रमm_cells[] = अणु
	अणु .name = "cros-ec-chardev", पूर्ण,
	अणु .name = "cros-ec-debugfs", पूर्ण,
	अणु .name = "cros-ec-lightbar", पूर्ण,
	अणु .name = "cros-ec-sysfs", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cros_ec_vbc_cells[] = अणु
	अणु .name = "cros-ec-vbc", पूर्ण
पूर्ण;

अटल व्योम cros_ec_class_release(काष्ठा device *dev)
अणु
	kमुक्त(to_cros_ec_dev(dev));
पूर्ण

अटल पूर्णांक ec_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक retval = -ENOMEM;
	काष्ठा device_node *node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cros_ec_platक्रमm *ec_platक्रमm = dev_get_platdata(dev);
	काष्ठा cros_ec_dev *ec = kzalloc(माप(*ec), GFP_KERNEL);
	पूर्णांक i;

	अगर (!ec)
		वापस retval;

	dev_set_drvdata(dev, ec);
	ec->ec_dev = dev_get_drvdata(dev->parent);
	ec->dev = dev;
	ec->cmd_offset = ec_platक्रमm->cmd_offset;
	ec->features[0] = -1U; /* Not cached yet */
	ec->features[1] = -1U; /* Not cached yet */
	device_initialize(&ec->class_dev);

	क्रम (i = 0; i < ARRAY_SIZE(cros_mcu_devices); i++) अणु
		/*
		 * Check whether this is actually a dedicated MCU rather
		 * than an standard EC.
		 */
		अगर (cros_ec_check_features(ec, cros_mcu_devices[i].id)) अणु
			dev_info(dev, "CrOS %s MCU detected\n",
				 cros_mcu_devices[i].desc);
			/*
			 * Help userspace dअगरferentiating ECs from other MCU,
			 * regardless of the probing order.
			 */
			ec_platक्रमm->ec_name = cros_mcu_devices[i].name;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Add the class device
	 */
	ec->class_dev.class = &cros_class;
	ec->class_dev.parent = dev;
	ec->class_dev.release = cros_ec_class_release;

	retval = dev_set_name(&ec->class_dev, "%s", ec_platक्रमm->ec_name);
	अगर (retval) अणु
		dev_err(dev, "dev_set_name failed => %d\n", retval);
		जाओ failed;
	पूर्ण

	retval = device_add(&ec->class_dev);
	अगर (retval)
		जाओ failed;

	/* check whether this EC is a sensor hub. */
	अगर (cros_ec_get_sensor_count(ec) > 0) अणु
		retval = mfd_add_hotplug_devices(ec->dev,
				cros_ec_sensorhub_cells,
				ARRAY_SIZE(cros_ec_sensorhub_cells));
		अगर (retval)
			dev_err(ec->dev, "failed to add %s subdevice: %d\n",
				cros_ec_sensorhub_cells->name, retval);
	पूर्ण

	/*
	 * The following subdevices can be detected by sending the
	 * EC_FEATURE_GET_CMD Embedded Controller device.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(cros_subdevices); i++) अणु
		अगर (cros_ec_check_features(ec, cros_subdevices[i].id)) अणु
			retval = mfd_add_hotplug_devices(ec->dev,
						cros_subdevices[i].mfd_cells,
						cros_subdevices[i].num_cells);
			अगर (retval)
				dev_err(ec->dev,
					"failed to add %s subdevice: %d\n",
					cros_subdevices[i].mfd_cells->name,
					retval);
		पूर्ण
	पूर्ण

	/*
	 * The PD notअगरier driver cell is separate since it only needs to be
	 * explicitly added on platक्रमms that करोn't have the PD notअगरier ACPI
	 * device entry defined.
	 */
	अगर (IS_ENABLED(CONFIG_OF) && ec->ec_dev->dev->of_node) अणु
		अगर (cros_ec_check_features(ec, EC_FEATURE_USB_PD)) अणु
			retval = mfd_add_hotplug_devices(ec->dev,
					cros_usbpd_notअगरy_cells,
					ARRAY_SIZE(cros_usbpd_notअगरy_cells));
			अगर (retval)
				dev_err(ec->dev,
					"failed to add PD notify devices: %d\n",
					retval);
		पूर्ण
	पूर्ण

	/*
	 * The following subdevices cannot be detected by sending the
	 * EC_FEATURE_GET_CMD to the Embedded Controller device.
	 */
	retval = mfd_add_hotplug_devices(ec->dev, cros_ec_platक्रमm_cells,
					 ARRAY_SIZE(cros_ec_platक्रमm_cells));
	अगर (retval)
		dev_warn(ec->dev,
			 "failed to add cros-ec platform devices: %d\n",
			 retval);

	/* Check whether this EC instance has a VBC NVRAM */
	node = ec->ec_dev->dev->of_node;
	अगर (of_property_पढ़ो_bool(node, "google,has-vbc-nvram")) अणु
		retval = mfd_add_hotplug_devices(ec->dev, cros_ec_vbc_cells,
						ARRAY_SIZE(cros_ec_vbc_cells));
		अगर (retval)
			dev_warn(ec->dev, "failed to add VBC devices: %d\n",
				 retval);
	पूर्ण

	वापस 0;

failed:
	put_device(&ec->class_dev);
	वापस retval;
पूर्ण

अटल पूर्णांक ec_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_dev *ec = dev_get_drvdata(&pdev->dev);

	mfd_हटाओ_devices(ec->dev);
	device_unरेजिस्टर(&ec->class_dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id cros_ec_id[] = अणु
	अणु DRV_NAME, 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, cros_ec_id);

अटल काष्ठा platक्रमm_driver cros_ec_dev_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.id_table = cros_ec_id,
	.probe = ec_device_probe,
	.हटाओ = ec_device_हटाओ,
पूर्ण;

अटल पूर्णांक __init cros_ec_dev_init(व्योम)
अणु
	पूर्णांक ret;

	ret  = class_रेजिस्टर(&cros_class);
	अगर (ret) अणु
		pr_err(CROS_EC_DEV_NAME ": failed to register device class\n");
		वापस ret;
	पूर्ण

	/* Register the driver */
	ret = platक्रमm_driver_रेजिस्टर(&cros_ec_dev_driver);
	अगर (ret < 0) अणु
		pr_warn(CROS_EC_DEV_NAME ": can't register driver: %d\n", ret);
		जाओ failed_devreg;
	पूर्ण
	वापस 0;

failed_devreg:
	class_unरेजिस्टर(&cros_class);
	वापस ret;
पूर्ण

अटल व्योम __निकास cros_ec_dev_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&cros_ec_dev_driver);
	class_unरेजिस्टर(&cros_class);
पूर्ण

module_init(cros_ec_dev_init);
module_निकास(cros_ec_dev_निकास);

MODULE_ALIAS("platform:" DRV_NAME);
MODULE_AUTHOR("Bill Richardson <wfrichar@chromium.org>");
MODULE_DESCRIPTION("Userspace interface to the Chrome OS Embedded Controller");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
