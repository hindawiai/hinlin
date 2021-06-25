<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * CEC driver क्रम ChromeOS Embedded Controller
 *
 * Copyright (c) 2018 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/pci.h>
#समावेश <linux/cec.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <media/cec.h>
#समावेश <media/cec-notअगरier.h>

#घोषणा DRV_NAME	"cros-ec-cec"

/**
 * काष्ठा cros_ec_cec - Driver data क्रम EC CEC
 *
 * @cros_ec: Poपूर्णांकer to EC device
 * @notअगरier: Notअगरier info क्रम responding to EC events
 * @adap: CEC adapter
 * @notअगरy: CEC notअगरier poपूर्णांकer
 * @rx_msg: storage क्रम a received message
 */
काष्ठा cros_ec_cec अणु
	काष्ठा cros_ec_device *cros_ec;
	काष्ठा notअगरier_block notअगरier;
	काष्ठा cec_adapter *adap;
	काष्ठा cec_notअगरier *notअगरy;
	काष्ठा cec_msg rx_msg;
पूर्ण;

अटल व्योम handle_cec_message(काष्ठा cros_ec_cec *cros_ec_cec)
अणु
	काष्ठा cros_ec_device *cros_ec = cros_ec_cec->cros_ec;
	uपूर्णांक8_t *cec_message = cros_ec->event_data.data.cec_message;
	अचिन्हित पूर्णांक len = cros_ec->event_size;

	cros_ec_cec->rx_msg.len = len;
	स_नकल(cros_ec_cec->rx_msg.msg, cec_message, len);

	cec_received_msg(cros_ec_cec->adap, &cros_ec_cec->rx_msg);
पूर्ण

अटल व्योम handle_cec_event(काष्ठा cros_ec_cec *cros_ec_cec)
अणु
	काष्ठा cros_ec_device *cros_ec = cros_ec_cec->cros_ec;
	uपूर्णांक32_t events = cros_ec->event_data.data.cec_events;

	अगर (events & EC_MKBP_CEC_SEND_OK)
		cec_transmit_attempt_करोne(cros_ec_cec->adap,
					  CEC_TX_STATUS_OK);

	/* FW takes care of all retries, tell core to aव्योम more retries */
	अगर (events & EC_MKBP_CEC_SEND_FAILED)
		cec_transmit_attempt_करोne(cros_ec_cec->adap,
					  CEC_TX_STATUS_MAX_RETRIES |
					  CEC_TX_STATUS_NACK);
पूर्ण

अटल पूर्णांक cros_ec_cec_event(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ queued_during_suspend,
			     व्योम *_notअगरy)
अणु
	काष्ठा cros_ec_cec *cros_ec_cec;
	काष्ठा cros_ec_device *cros_ec;

	cros_ec_cec = container_of(nb, काष्ठा cros_ec_cec, notअगरier);
	cros_ec = cros_ec_cec->cros_ec;

	अगर (cros_ec->event_data.event_type == EC_MKBP_EVENT_CEC_EVENT) अणु
		handle_cec_event(cros_ec_cec);
		वापस NOTIFY_OK;
	पूर्ण

	अगर (cros_ec->event_data.event_type == EC_MKBP_EVENT_CEC_MESSAGE) अणु
		handle_cec_message(cros_ec_cec);
		वापस NOTIFY_OK;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक cros_ec_cec_set_log_addr(काष्ठा cec_adapter *adap, u8 logical_addr)
अणु
	काष्ठा cros_ec_cec *cros_ec_cec = adap->priv;
	काष्ठा cros_ec_device *cros_ec = cros_ec_cec->cros_ec;
	काष्ठा अणु
		काष्ठा cros_ec_command msg;
		काष्ठा ec_params_cec_set data;
	पूर्ण __packed msg = अणुपूर्ण;
	पूर्णांक ret;

	msg.msg.command = EC_CMD_CEC_SET;
	msg.msg.outsize = माप(msg.data);
	msg.data.cmd = CEC_CMD_LOGICAL_ADDRESS;
	msg.data.val = logical_addr;

	ret = cros_ec_cmd_xfer_status(cros_ec, &msg.msg);
	अगर (ret < 0) अणु
		dev_err(cros_ec->dev,
			"error setting CEC logical address on EC: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_cec_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				u32 संकेत_मुक्त_समय, काष्ठा cec_msg *cec_msg)
अणु
	काष्ठा cros_ec_cec *cros_ec_cec = adap->priv;
	काष्ठा cros_ec_device *cros_ec = cros_ec_cec->cros_ec;
	काष्ठा अणु
		काष्ठा cros_ec_command msg;
		काष्ठा ec_params_cec_ग_लिखो data;
	पूर्ण __packed msg = अणुपूर्ण;
	पूर्णांक ret;

	msg.msg.command = EC_CMD_CEC_WRITE_MSG;
	msg.msg.outsize = cec_msg->len;
	स_नकल(msg.data.msg, cec_msg->msg, cec_msg->len);

	ret = cros_ec_cmd_xfer_status(cros_ec, &msg.msg);
	अगर (ret < 0) अणु
		dev_err(cros_ec->dev,
			"error writing CEC msg on EC: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा cros_ec_cec *cros_ec_cec = adap->priv;
	काष्ठा cros_ec_device *cros_ec = cros_ec_cec->cros_ec;
	काष्ठा अणु
		काष्ठा cros_ec_command msg;
		काष्ठा ec_params_cec_set data;
	पूर्ण __packed msg = अणुपूर्ण;
	पूर्णांक ret;

	msg.msg.command = EC_CMD_CEC_SET;
	msg.msg.outsize = माप(msg.data);
	msg.data.cmd = CEC_CMD_ENABLE;
	msg.data.val = enable;

	ret = cros_ec_cmd_xfer_status(cros_ec, &msg.msg);
	अगर (ret < 0) अणु
		dev_err(cros_ec->dev,
			"error %sabling CEC on EC: %d\n",
			(enable ? "en" : "dis"), ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops cros_ec_cec_ops = अणु
	.adap_enable = cros_ec_cec_adap_enable,
	.adap_log_addr = cros_ec_cec_set_log_addr,
	.adap_transmit = cros_ec_cec_transmit,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cros_ec_cec_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा cros_ec_cec *cros_ec_cec = dev_get_drvdata(&pdev->dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(cros_ec_cec->cros_ec->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_cec_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा cros_ec_cec *cros_ec_cec = dev_get_drvdata(&pdev->dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(cros_ec_cec->cros_ec->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(cros_ec_cec_pm_ops,
	cros_ec_cec_suspend, cros_ec_cec_resume);

#अगर IS_ENABLED(CONFIG_PCI) && IS_ENABLED(CONFIG_DMI)

/*
 * The Firmware only handles a single CEC पूर्णांकerface tied to a single HDMI
 * connector we specअगरy aदीर्घ with the DRM device name handling the HDMI output
 */

काष्ठा cec_dmi_match अणु
	स्थिर अक्षर *sys_venकरोr;
	स्थिर अक्षर *product_name;
	स्थिर अक्षर *devname;
	स्थिर अक्षर *conn;
पूर्ण;

अटल स्थिर काष्ठा cec_dmi_match cec_dmi_match_table[] = अणु
	/* Google Fizz */
	अणु "Google", "Fizz", "0000:00:02.0", "Port B" पूर्ण,
पूर्ण;

अटल काष्ठा device *cros_ec_cec_find_hdmi_dev(काष्ठा device *dev,
						स्थिर अक्षर **conn)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < ARRAY_SIZE(cec_dmi_match_table) ; ++i) अणु
		स्थिर काष्ठा cec_dmi_match *m = &cec_dmi_match_table[i];

		अगर (dmi_match(DMI_SYS_VENDOR, m->sys_venकरोr) &&
		    dmi_match(DMI_PRODUCT_NAME, m->product_name)) अणु
			काष्ठा device *d;

			/* Find the device, bail out अगर not yet रेजिस्टरed */
			d = bus_find_device_by_name(&pci_bus_type, शून्य,
						    m->devname);
			अगर (!d)
				वापस ERR_PTR(-EPROBE_DEFER);
			put_device(d);
			*conn = m->conn;
			वापस d;
		पूर्ण
	पूर्ण

	/* Hardware support must be added in the cec_dmi_match_table */
	dev_warn(dev, "CEC notifier not configured for this hardware\n");

	वापस ERR_PTR(-ENODEV);
पूर्ण

#अन्यथा

अटल काष्ठा device *cros_ec_cec_find_hdmi_dev(काष्ठा device *dev,
						स्थिर अक्षर **conn)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक cros_ec_cec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा cros_ec_device *cros_ec = ec_dev->ec_dev;
	काष्ठा cros_ec_cec *cros_ec_cec;
	काष्ठा device *hdmi_dev;
	स्थिर अक्षर *conn = शून्य;
	पूर्णांक ret;

	hdmi_dev = cros_ec_cec_find_hdmi_dev(&pdev->dev, &conn);
	अगर (IS_ERR(hdmi_dev))
		वापस PTR_ERR(hdmi_dev);

	cros_ec_cec = devm_kzalloc(&pdev->dev, माप(*cros_ec_cec),
				   GFP_KERNEL);
	अगर (!cros_ec_cec)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, cros_ec_cec);
	cros_ec_cec->cros_ec = cros_ec;

	device_init_wakeup(&pdev->dev, 1);

	cros_ec_cec->adap = cec_allocate_adapter(&cros_ec_cec_ops, cros_ec_cec,
						 DRV_NAME,
						 CEC_CAP_DEFAULTS |
						 CEC_CAP_CONNECTOR_INFO, 1);
	अगर (IS_ERR(cros_ec_cec->adap))
		वापस PTR_ERR(cros_ec_cec->adap);

	cros_ec_cec->notअगरy = cec_notअगरier_cec_adap_रेजिस्टर(hdmi_dev, conn,
							     cros_ec_cec->adap);
	अगर (!cros_ec_cec->notअगरy) अणु
		ret = -ENOMEM;
		जाओ out_probe_adapter;
	पूर्ण

	/* Get CEC events from the EC. */
	cros_ec_cec->notअगरier.notअगरier_call = cros_ec_cec_event;
	ret = blocking_notअगरier_chain_रेजिस्टर(&cros_ec->event_notअगरier,
					       &cros_ec_cec->notअगरier);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register notifier\n");
		जाओ out_probe_notअगरy;
	पूर्ण

	ret = cec_रेजिस्टर_adapter(cros_ec_cec->adap, &pdev->dev);
	अगर (ret < 0)
		जाओ out_probe_notअगरy;

	वापस 0;

out_probe_notअगरy:
	cec_notअगरier_cec_adap_unरेजिस्टर(cros_ec_cec->notअगरy,
					 cros_ec_cec->adap);
out_probe_adapter:
	cec_delete_adapter(cros_ec_cec->adap);
	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_cec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_cec *cros_ec_cec = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	ret = blocking_notअगरier_chain_unरेजिस्टर(
			&cros_ec_cec->cros_ec->event_notअगरier,
			&cros_ec_cec->notअगरier);

	अगर (ret) अणु
		dev_err(dev, "failed to unregister notifier\n");
		वापस ret;
	पूर्ण

	cec_notअगरier_cec_adap_unरेजिस्टर(cros_ec_cec->notअगरy,
					 cros_ec_cec->adap);
	cec_unरेजिस्टर_adapter(cros_ec_cec->adap);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cros_ec_cec_driver = अणु
	.probe = cros_ec_cec_probe,
	.हटाओ  = cros_ec_cec_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.pm = &cros_ec_cec_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cros_ec_cec_driver);

MODULE_DESCRIPTION("CEC driver for ChromeOS ECs");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
