<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Core driver क्रम Wilco Embedded Controller
 *
 * Copyright 2018 Google LLC
 *
 * This is the entry poपूर्णांक क्रम the drivers that control the Wilco EC.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/wilco-ec.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "../cros_ec_lpc_mec.h"

#घोषणा DRV_NAME "wilco-ec"

अटल काष्ठा resource *wilco_get_resource(काष्ठा platक्रमm_device *pdev,
					   पूर्णांक index)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, index);
	अगर (!res) अणु
		dev_dbg(dev, "Couldn't find IO resource %d\n", index);
		वापस res;
	पूर्ण

	वापस devm_request_region(dev, res->start, resource_size(res),
				   dev_name(dev));
पूर्ण

अटल पूर्णांक wilco_ec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा wilco_ec_device *ec;
	पूर्णांक ret;

	ec = devm_kzalloc(dev, माप(*ec), GFP_KERNEL);
	अगर (!ec)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ec);
	ec->dev = dev;
	mutex_init(&ec->mailbox_lock);

	ec->data_size = माप(काष्ठा wilco_ec_response) + EC_MAILBOX_DATA_SIZE;
	ec->data_buffer = devm_kzalloc(dev, ec->data_size, GFP_KERNEL);
	अगर (!ec->data_buffer)
		वापस -ENOMEM;

	/* Prepare access to IO regions provided by ACPI */
	ec->io_data = wilco_get_resource(pdev, 0);	/* Host Data */
	ec->io_command = wilco_get_resource(pdev, 1);	/* Host Command */
	ec->io_packet = wilco_get_resource(pdev, 2);	/* MEC EMI */
	अगर (!ec->io_data || !ec->io_command || !ec->io_packet)
		वापस -ENODEV;

	/* Initialize cros_ec रेजिस्टर पूर्णांकerface क्रम communication */
	cros_ec_lpc_mec_init(ec->io_packet->start,
			     ec->io_packet->start + EC_MAILBOX_DATA_SIZE);

	/*
	 * Register a child device that will be found by the debugfs driver.
	 * Ignore failure.
	 */
	ec->debugfs_pdev = platक्रमm_device_रेजिस्टर_data(dev,
							 "wilco-ec-debugfs",
							 PLATFORM_DEVID_AUTO,
							 शून्य, 0);

	/* Register a child device that will be found by the RTC driver. */
	ec->rtc_pdev = platक्रमm_device_रेजिस्टर_data(dev, "rtc-wilco-ec",
						     PLATFORM_DEVID_AUTO,
						     शून्य, 0);
	अगर (IS_ERR(ec->rtc_pdev)) अणु
		dev_err(dev, "Failed to create RTC platform device\n");
		ret = PTR_ERR(ec->rtc_pdev);
		जाओ unरेजिस्टर_debugfs;
	पूर्ण

	/* Set up the keyboard backlight LEDs. */
	ret = wilco_keyboard_leds_init(ec);
	अगर (ret < 0) अणु
		dev_err(dev,
			"Failed to initialize keyboard LEDs: %d\n",
			ret);
		जाओ unरेजिस्टर_rtc;
	पूर्ण

	ret = wilco_ec_add_sysfs(ec);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to create sysfs entries: %d\n", ret);
		जाओ unरेजिस्टर_rtc;
	पूर्ण

	/* Register child device to be found by अक्षरger config driver. */
	ec->अक्षरger_pdev = platक्रमm_device_रेजिस्टर_data(dev, "wilco-charger",
							 PLATFORM_DEVID_AUTO,
							 शून्य, 0);
	अगर (IS_ERR(ec->अक्षरger_pdev)) अणु
		dev_err(dev, "Failed to create charger platform device\n");
		ret = PTR_ERR(ec->अक्षरger_pdev);
		जाओ हटाओ_sysfs;
	पूर्ण

	/* Register child device that will be found by the telemetry driver. */
	ec->telem_pdev = platक्रमm_device_रेजिस्टर_data(dev, "wilco_telem",
						       PLATFORM_DEVID_AUTO,
						       ec, माप(*ec));
	अगर (IS_ERR(ec->telem_pdev)) अणु
		dev_err(dev, "Failed to create telemetry platform device\n");
		ret = PTR_ERR(ec->telem_pdev);
		जाओ unरेजिस्टर_अक्षरge_config;
	पूर्ण

	वापस 0;

unरेजिस्टर_अक्षरge_config:
	platक्रमm_device_unरेजिस्टर(ec->अक्षरger_pdev);
हटाओ_sysfs:
	wilco_ec_हटाओ_sysfs(ec);
unरेजिस्टर_rtc:
	platक्रमm_device_unरेजिस्टर(ec->rtc_pdev);
unरेजिस्टर_debugfs:
	अगर (ec->debugfs_pdev)
		platक्रमm_device_unरेजिस्टर(ec->debugfs_pdev);
	cros_ec_lpc_mec_destroy();
	वापस ret;
पूर्ण

अटल पूर्णांक wilco_ec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wilco_ec_device *ec = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(ec->telem_pdev);
	platक्रमm_device_unरेजिस्टर(ec->अक्षरger_pdev);
	wilco_ec_हटाओ_sysfs(ec);
	platक्रमm_device_unरेजिस्टर(ec->rtc_pdev);
	अगर (ec->debugfs_pdev)
		platक्रमm_device_unरेजिस्टर(ec->debugfs_pdev);

	/* Tearकरोwn cros_ec पूर्णांकerface */
	cros_ec_lpc_mec_destroy();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id wilco_ec_acpi_device_ids[] = अणु
	अणु "GOOG000C", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, wilco_ec_acpi_device_ids);

अटल काष्ठा platक्रमm_driver wilco_ec_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.acpi_match_table = wilco_ec_acpi_device_ids,
	पूर्ण,
	.probe = wilco_ec_probe,
	.हटाओ = wilco_ec_हटाओ,
पूर्ण;

module_platक्रमm_driver(wilco_ec_driver);

MODULE_AUTHOR("Nick Crews <ncrews@chromium.org>");
MODULE_AUTHOR("Duncan Laurie <dlaurie@chromium.org>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ChromeOS Wilco Embedded Controller driver");
MODULE_ALIAS("platform:" DRV_NAME);
