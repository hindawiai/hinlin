<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx Zynq MPSoC Power Management
 *
 *  Copyright (C) 2014-2019 Xilinx, Inc.
 *
 *  Davorin Mista <davorin.mista@aggios.com>
 *  Jolly Shah <jollys@xilinx.com>
 *  Rajan Vaja <rajan.vaja@xilinx.com>
 */

#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/suspend.h>

#समावेश <linux/firmware/xlnx-zynqmp.h>
#समावेश <linux/mailbox/zynqmp-ipi-message.h>

/**
 * काष्ठा zynqmp_pm_work_काष्ठा - Wrapper क्रम काष्ठा work_काष्ठा
 * @callback_work:	Work काष्ठाure
 * @args:		Callback arguments
 */
काष्ठा zynqmp_pm_work_काष्ठा अणु
	काष्ठा work_काष्ठा callback_work;
	u32 args[CB_ARG_CNT];
पूर्ण;

अटल काष्ठा zynqmp_pm_work_काष्ठा *zynqmp_pm_init_suspend_work;
अटल काष्ठा mbox_chan *rx_chan;

क्रमागत pm_suspend_mode अणु
	PM_SUSPEND_MODE_FIRST = 0,
	PM_SUSPEND_MODE_STD = PM_SUSPEND_MODE_FIRST,
	PM_SUSPEND_MODE_POWER_OFF,
पूर्ण;

#घोषणा PM_SUSPEND_MODE_FIRST	PM_SUSPEND_MODE_STD

अटल स्थिर अक्षर *स्थिर suspend_modes[] = अणु
	[PM_SUSPEND_MODE_STD] = "standard",
	[PM_SUSPEND_MODE_POWER_OFF] = "power-off",
पूर्ण;

अटल क्रमागत pm_suspend_mode suspend_mode = PM_SUSPEND_MODE_STD;

क्रमागत pm_api_cb_id अणु
	PM_INIT_SUSPEND_CB = 30,
	PM_ACKNOWLEDGE_CB,
	PM_NOTIFY_CB,
पूर्ण;

अटल व्योम zynqmp_pm_get_callback_data(u32 *buf)
अणु
	zynqmp_pm_invoke_fn(GET_CALLBACK_DATA, 0, 0, 0, 0, buf);
पूर्ण

अटल irqवापस_t zynqmp_pm_isr(पूर्णांक irq, व्योम *data)
अणु
	u32 payload[CB_PAYLOAD_SIZE];

	zynqmp_pm_get_callback_data(payload);

	/* First element is callback API ID, others are callback arguments */
	अगर (payload[0] == PM_INIT_SUSPEND_CB) अणु
		चयन (payload[1]) अणु
		हाल SUSPEND_SYSTEM_SHUTDOWN:
			orderly_घातeroff(true);
			अवरोध;
		हाल SUSPEND_POWER_REQUEST:
			pm_suspend(PM_SUSPEND_MEM);
			अवरोध;
		शेष:
			pr_err("%s Unsupported InitSuspendCb reason "
				"code %d\n", __func__, payload[1]);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ipi_receive_callback(काष्ठा mbox_client *cl, व्योम *data)
अणु
	काष्ठा zynqmp_ipi_message *msg = (काष्ठा zynqmp_ipi_message *)data;
	u32 payload[CB_PAYLOAD_SIZE];
	पूर्णांक ret;

	स_नकल(payload, msg->data, माप(msg->len));
	/* First element is callback API ID, others are callback arguments */
	अगर (payload[0] == PM_INIT_SUSPEND_CB) अणु
		अगर (work_pending(&zynqmp_pm_init_suspend_work->callback_work))
			वापस;

		/* Copy callback arguments पूर्णांकo work's काष्ठाure */
		स_नकल(zynqmp_pm_init_suspend_work->args, &payload[1],
		       माप(zynqmp_pm_init_suspend_work->args));

		queue_work(प्रणाली_unbound_wq,
			   &zynqmp_pm_init_suspend_work->callback_work);

		/* Send शून्य message to mbox controller to ack the message */
		ret = mbox_send_message(rx_chan, शून्य);
		अगर (ret)
			pr_err("IPI ack failed. Error %d\n", ret);
	पूर्ण
पूर्ण

/**
 * zynqmp_pm_init_suspend_work_fn - Initialize suspend
 * @work:	Poपूर्णांकer to work_काष्ठा
 *
 * Bottom-half of PM callback IRQ handler.
 */
अटल व्योम zynqmp_pm_init_suspend_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zynqmp_pm_work_काष्ठा *pm_work =
		container_of(work, काष्ठा zynqmp_pm_work_काष्ठा, callback_work);

	अगर (pm_work->args[0] == SUSPEND_SYSTEM_SHUTDOWN) अणु
		orderly_घातeroff(true);
	पूर्ण अन्यथा अगर (pm_work->args[0] == SUSPEND_POWER_REQUEST) अणु
		pm_suspend(PM_SUSPEND_MEM);
	पूर्ण अन्यथा अणु
		pr_err("%s Unsupported InitSuspendCb reason code %d.\n",
		       __func__, pm_work->args[0]);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार suspend_mode_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अक्षर *s = buf;
	पूर्णांक md;

	क्रम (md = PM_SUSPEND_MODE_FIRST; md < ARRAY_SIZE(suspend_modes); md++)
		अगर (suspend_modes[md]) अणु
			अगर (md == suspend_mode)
				s += प्र_लिखो(s, "[%s] ", suspend_modes[md]);
			अन्यथा
				s += प्र_लिखो(s, "%s ", suspend_modes[md]);
		पूर्ण

	/* Convert last space to newline */
	अगर (s != buf)
		*(s - 1) = '\n';
	वापस (s - buf);
पूर्ण

अटल sमाप_प्रकार suspend_mode_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक md, ret = -EINVAL;

	क्रम (md = PM_SUSPEND_MODE_FIRST; md < ARRAY_SIZE(suspend_modes); md++)
		अगर (suspend_modes[md] &&
		    sysfs_streq(suspend_modes[md], buf)) अणु
			ret = 0;
			अवरोध;
		पूर्ण

	अगर (!ret && md != suspend_mode) अणु
		ret = zynqmp_pm_set_suspend_mode(md);
		अगर (likely(!ret))
			suspend_mode = md;
	पूर्ण

	वापस ret ? ret : count;
पूर्ण

अटल DEVICE_ATTR_RW(suspend_mode);

अटल पूर्णांक zynqmp_pm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, irq;
	u32 pm_api_version;
	काष्ठा mbox_client *client;

	zynqmp_pm_init_finalize();
	zynqmp_pm_get_api_version(&pm_api_version);

	/* Check PM API version number */
	अगर (pm_api_version < ZYNQMP_PM_VERSION)
		वापस -ENODEV;

	अगर (of_find_property(pdev->dev.of_node, "mboxes", शून्य)) अणु
		zynqmp_pm_init_suspend_work =
			devm_kzalloc(&pdev->dev,
				     माप(काष्ठा zynqmp_pm_work_काष्ठा),
				     GFP_KERNEL);
		अगर (!zynqmp_pm_init_suspend_work)
			वापस -ENOMEM;

		INIT_WORK(&zynqmp_pm_init_suspend_work->callback_work,
			  zynqmp_pm_init_suspend_work_fn);
		client = devm_kzalloc(&pdev->dev, माप(*client), GFP_KERNEL);
		अगर (!client)
			वापस -ENOMEM;

		client->dev = &pdev->dev;
		client->rx_callback = ipi_receive_callback;

		rx_chan = mbox_request_channel_byname(client, "rx");
		अगर (IS_ERR(rx_chan)) अणु
			dev_err(&pdev->dev, "Failed to request rx channel\n");
			वापस PTR_ERR(rx_chan);
		पूर्ण
	पूर्ण अन्यथा अगर (of_find_property(pdev->dev.of_node, "interrupts", शून्य)) अणु
		irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq <= 0)
			वापस -ENXIO;

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
						zynqmp_pm_isr,
						IRQF_NO_SUSPEND | IRQF_ONESHOT,
						dev_name(&pdev->dev),
						&pdev->dev);
		अगर (ret) अणु
			dev_err(&pdev->dev, "devm_request_threaded_irq '%d' "
					    "failed with %d\n", irq, ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Required property not found in DT node\n");
		वापस -ENOENT;
	पूर्ण

	ret = sysfs_create_file(&pdev->dev.kobj, &dev_attr_suspend_mode.attr);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to create sysfs interface\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zynqmp_pm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	sysfs_हटाओ_file(&pdev->dev.kobj, &dev_attr_suspend_mode.attr);

	अगर (!rx_chan)
		mbox_मुक्त_channel(rx_chan);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pm_of_match[] = अणु
	अणु .compatible = "xlnx,zynqmp-power", पूर्ण,
	अणु /* end of table */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pm_of_match);

अटल काष्ठा platक्रमm_driver zynqmp_pm_platक्रमm_driver = अणु
	.probe = zynqmp_pm_probe,
	.हटाओ = zynqmp_pm_हटाओ,
	.driver = अणु
		.name = "zynqmp_power",
		.of_match_table = pm_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(zynqmp_pm_platक्रमm_driver);
