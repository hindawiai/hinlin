<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2020 Google LLC
 *
 * This driver serves as the receiver of cros_ec PD host events.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_data/cros_usbpd_notअगरy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRV_NAME "cros-usbpd-notify"
#घोषणा DRV_NAME_PLAT_ACPI "cros-usbpd-notify-acpi"
#घोषणा ACPI_DRV_NAME "GOOG0003"

अटल BLOCKING_NOTIFIER_HEAD(cros_usbpd_notअगरier_list);

काष्ठा cros_usbpd_notअगरy_data अणु
	काष्ठा device *dev;
	काष्ठा cros_ec_device *ec;
	काष्ठा notअगरier_block nb;
पूर्ण;

/**
 * cros_usbpd_रेजिस्टर_notअगरy - Register a notअगरier callback क्रम PD events.
 * @nb: Notअगरier block poपूर्णांकer to रेजिस्टर
 *
 * On ACPI platक्रमms this corresponds to host events on the ECPD
 * "GOOG0003" ACPI device. On non-ACPI platक्रमms this will filter mkbp events
 * क्रम USB PD events.
 *
 * Return: 0 on success or negative error code.
 */
पूर्णांक cros_usbpd_रेजिस्टर_notअगरy(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&cros_usbpd_notअगरier_list,
						nb);
पूर्ण
EXPORT_SYMBOL_GPL(cros_usbpd_रेजिस्टर_notअगरy);

/**
 * cros_usbpd_unरेजिस्टर_notअगरy - Unरेजिस्टर notअगरier callback क्रम PD events.
 * @nb: Notअगरier block poपूर्णांकer to unरेजिस्टर
 *
 * Unरेजिस्टर a notअगरier callback that was previously रेजिस्टरed with
 * cros_usbpd_रेजिस्टर_notअगरy().
 */
व्योम cros_usbpd_unरेजिस्टर_notअगरy(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&cros_usbpd_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(cros_usbpd_unरेजिस्टर_notअगरy);

/**
 * cros_ec_pd_command - Send a command to the EC.
 *
 * @ec_dev: EC device
 * @command: EC command
 * @outdata: EC command output data
 * @outsize: Size of outdata
 * @indata: EC command input data
 * @insize: Size of indata
 *
 * Return: >= 0 on success, negative error number on failure.
 */
अटल पूर्णांक cros_ec_pd_command(काष्ठा cros_ec_device *ec_dev,
			      पूर्णांक command,
			      uपूर्णांक8_t *outdata,
			      पूर्णांक outsize,
			      uपूर्णांक8_t *indata,
			      पूर्णांक insize)
अणु
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = kzalloc(माप(*msg) + max(insize, outsize), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->command = command;
	msg->outsize = outsize;
	msg->insize = insize;

	अगर (outsize)
		स_नकल(msg->data, outdata, outsize);

	ret = cros_ec_cmd_xfer_status(ec_dev, msg);
	अगर (ret < 0)
		जाओ error;

	अगर (insize)
		स_नकल(indata, msg->data, insize);
error:
	kमुक्त(msg);
	वापस ret;
पूर्ण

अटल व्योम cros_usbpd_get_event_and_notअगरy(काष्ठा device  *dev,
					    काष्ठा cros_ec_device *ec_dev)
अणु
	काष्ठा ec_response_host_event_status host_event_status;
	u32 event = 0;
	पूर्णांक ret;

	/*
	 * We still send a 0 event out to older devices which करोn't
	 * have the updated device heirarchy.
	 */
	अगर (!ec_dev) अणु
		dev_dbg(dev,
			"EC device inaccessible; sending 0 event status.\n");
		जाओ send_notअगरy;
	पूर्ण

	/* Check क्रम PD host events on EC. */
	ret = cros_ec_pd_command(ec_dev, EC_CMD_PD_HOST_EVENT_STATUS,
				 शून्य, 0,
				 (uपूर्णांक8_t *)&host_event_status,
				 माप(host_event_status));
	अगर (ret < 0) अणु
		dev_warn(dev, "Can't get host event status (err: %d)\n", ret);
		जाओ send_notअगरy;
	पूर्ण

	event = host_event_status.status;

send_notअगरy:
	blocking_notअगरier_call_chain(&cros_usbpd_notअगरier_list, event, शून्य);
पूर्ण

#अगर_घोषित CONFIG_ACPI

अटल व्योम cros_usbpd_notअगरy_acpi(acpi_handle device, u32 event, व्योम *data)
अणु
	काष्ठा cros_usbpd_notअगरy_data *pdnotअगरy = data;

	cros_usbpd_get_event_and_notअगरy(pdnotअगरy->dev, pdnotअगरy->ec);
पूर्ण

अटल पूर्णांक cros_usbpd_notअगरy_probe_acpi(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_usbpd_notअगरy_data *pdnotअगरy;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा acpi_device *adev;
	काष्ठा cros_ec_device *ec_dev;
	acpi_status status;

	adev = ACPI_COMPANION(dev);

	pdnotअगरy = devm_kzalloc(dev, माप(*pdnotअगरy), GFP_KERNEL);
	अगर (!pdnotअगरy)
		वापस -ENOMEM;

	/* Get the EC device poपूर्णांकer needed to talk to the EC. */
	ec_dev = dev_get_drvdata(dev->parent);
	अगर (!ec_dev) अणु
		/*
		 * We जारी even क्रम older devices which करोn't have the
		 * correct device heirarchy, namely, GOOG0003 is a child
		 * of GOOG0004.
		 */
		dev_warn(dev, "Couldn't get Chrome EC device pointer.\n");
	पूर्ण

	pdnotअगरy->dev = dev;
	pdnotअगरy->ec = ec_dev;

	status = acpi_install_notअगरy_handler(adev->handle,
					     ACPI_ALL_NOTIFY,
					     cros_usbpd_notअगरy_acpi,
					     pdnotअगरy);
	अगर (ACPI_FAILURE(status)) अणु
		dev_warn(dev, "Failed to register notify handler %08x\n",
			 status);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_usbpd_notअगरy_हटाओ_acpi(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);

	acpi_हटाओ_notअगरy_handler(adev->handle, ACPI_ALL_NOTIFY,
				   cros_usbpd_notअगरy_acpi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id cros_usbpd_notअगरy_acpi_device_ids[] = अणु
	अणु ACPI_DRV_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cros_usbpd_notअगरy_acpi_device_ids);

अटल काष्ठा platक्रमm_driver cros_usbpd_notअगरy_acpi_driver = अणु
	.driver = अणु
		.name = DRV_NAME_PLAT_ACPI,
		.acpi_match_table = cros_usbpd_notअगरy_acpi_device_ids,
	पूर्ण,
	.probe = cros_usbpd_notअगरy_probe_acpi,
	.हटाओ = cros_usbpd_notअगरy_हटाओ_acpi,
पूर्ण;

#पूर्ण_अगर /* CONFIG_ACPI */

अटल पूर्णांक cros_usbpd_notअगरy_plat(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ queued_during_suspend,
				  व्योम *data)
अणु
	काष्ठा cros_usbpd_notअगरy_data *pdnotअगरy = container_of(nb,
			काष्ठा cros_usbpd_notअगरy_data, nb);
	काष्ठा cros_ec_device *ec_dev = (काष्ठा cros_ec_device *)data;
	u32 host_event = cros_ec_get_host_event(ec_dev);

	अगर (!host_event)
		वापस NOTIFY_DONE;

	अगर (host_event & (EC_HOST_EVENT_MASK(EC_HOST_EVENT_PD_MCU) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_USB_MUX))) अणु
		cros_usbpd_get_event_and_notअगरy(pdnotअगरy->dev, ec_dev);
		वापस NOTIFY_OK;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक cros_usbpd_notअगरy_probe_plat(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cros_ec_dev *ecdev = dev_get_drvdata(dev->parent);
	काष्ठा cros_usbpd_notअगरy_data *pdnotअगरy;
	पूर्णांक ret;

	pdnotअगरy = devm_kzalloc(dev, माप(*pdnotअगरy), GFP_KERNEL);
	अगर (!pdnotअगरy)
		वापस -ENOMEM;

	pdnotअगरy->dev = dev;
	pdnotअगरy->ec = ecdev->ec_dev;
	pdnotअगरy->nb.notअगरier_call = cros_usbpd_notअगरy_plat;

	dev_set_drvdata(dev, pdnotअगरy);

	ret = blocking_notअगरier_chain_रेजिस्टर(&ecdev->ec_dev->event_notअगरier,
					       &pdnotअगरy->nb);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register notifier\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_usbpd_notअगरy_हटाओ_plat(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cros_ec_dev *ecdev = dev_get_drvdata(dev->parent);
	काष्ठा cros_usbpd_notअगरy_data *pdnotअगरy =
		(काष्ठा cros_usbpd_notअगरy_data *)dev_get_drvdata(dev);

	blocking_notअगरier_chain_unरेजिस्टर(&ecdev->ec_dev->event_notअगरier,
					   &pdnotअगरy->nb);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cros_usbpd_notअगरy_plat_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.probe = cros_usbpd_notअगरy_probe_plat,
	.हटाओ = cros_usbpd_notअगरy_हटाओ_plat,
पूर्ण;

अटल पूर्णांक __init cros_usbpd_notअगरy_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&cros_usbpd_notअगरy_plat_driver);
	अगर (ret < 0)
		वापस ret;

#अगर_घोषित CONFIG_ACPI
	platक्रमm_driver_रेजिस्टर(&cros_usbpd_notअगरy_acpi_driver);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __निकास cros_usbpd_notअगरy_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_ACPI
	platक्रमm_driver_unरेजिस्टर(&cros_usbpd_notअगरy_acpi_driver);
#पूर्ण_अगर
	platक्रमm_driver_unरेजिस्टर(&cros_usbpd_notअगरy_plat_driver);
पूर्ण

module_init(cros_usbpd_notअगरy_init);
module_निकास(cros_usbpd_notअगरy_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ChromeOS power delivery notifier device");
MODULE_AUTHOR("Jon Flatley <jflat@chromium.org>");
MODULE_ALIAS("platform:" DRV_NAME);
