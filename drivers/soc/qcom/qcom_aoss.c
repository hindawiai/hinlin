<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019, Linaro Ltd
 */
#समावेश <dt-bindings/घातer/qcom-aoss-qmp.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/thermal.h>
#समावेश <linux/slab.h>

#घोषणा QMP_DESC_MAGIC			0x0
#घोषणा QMP_DESC_VERSION		0x4
#घोषणा QMP_DESC_FEATURES		0x8

/* AOP-side offsets */
#घोषणा QMP_DESC_UCORE_LINK_STATE	0xc
#घोषणा QMP_DESC_UCORE_LINK_STATE_ACK	0x10
#घोषणा QMP_DESC_UCORE_CH_STATE		0x14
#घोषणा QMP_DESC_UCORE_CH_STATE_ACK	0x18
#घोषणा QMP_DESC_UCORE_MBOX_SIZE	0x1c
#घोषणा QMP_DESC_UCORE_MBOX_OFFSET	0x20

/* Linux-side offsets */
#घोषणा QMP_DESC_MCORE_LINK_STATE	0x24
#घोषणा QMP_DESC_MCORE_LINK_STATE_ACK	0x28
#घोषणा QMP_DESC_MCORE_CH_STATE		0x2c
#घोषणा QMP_DESC_MCORE_CH_STATE_ACK	0x30
#घोषणा QMP_DESC_MCORE_MBOX_SIZE	0x34
#घोषणा QMP_DESC_MCORE_MBOX_OFFSET	0x38

#घोषणा QMP_STATE_UP			GENMASK(15, 0)
#घोषणा QMP_STATE_DOWN			GENMASK(31, 16)

#घोषणा QMP_MAGIC			0x4d41494c /* mail */
#घोषणा QMP_VERSION			1

/* 64 bytes is enough to store the requests and provides padding to 4 bytes */
#घोषणा QMP_MSG_LEN			64

#घोषणा QMP_NUM_COOLING_RESOURCES	2

अटल bool qmp_cdev_max_state = 1;

काष्ठा qmp_cooling_device अणु
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा qmp *qmp;
	अक्षर *name;
	bool state;
पूर्ण;

/**
 * काष्ठा qmp - driver state क्रम QMP implementation
 * @msgram: iomem referencing the message RAM used क्रम communication
 * @dev: reference to QMP device
 * @mbox_client: mailbox client used to ring the करोorbell on transmit
 * @mbox_chan: mailbox channel used to ring the करोorbell on transmit
 * @offset: offset within @msgram where messages should be written
 * @size: maximum size of the messages to be transmitted
 * @event: रुको_queue क्रम synchronization with the IRQ
 * @tx_lock: provides synchronization between multiple callers of qmp_send()
 * @qdss_clk: QDSS घड़ी hw काष्ठा
 * @pd_data: genpd data
 * @cooling_devs: thermal cooling devices
 */
काष्ठा qmp अणु
	व्योम __iomem *msgram;
	काष्ठा device *dev;

	काष्ठा mbox_client mbox_client;
	काष्ठा mbox_chan *mbox_chan;

	माप_प्रकार offset;
	माप_प्रकार size;

	रुको_queue_head_t event;

	काष्ठा mutex tx_lock;

	काष्ठा clk_hw qdss_clk;
	काष्ठा genpd_onecell_data pd_data;
	काष्ठा qmp_cooling_device *cooling_devs;
पूर्ण;

काष्ठा qmp_pd अणु
	काष्ठा qmp *qmp;
	काष्ठा generic_pm_करोमुख्य pd;
पूर्ण;

#घोषणा to_qmp_pd_resource(res) container_of(res, काष्ठा qmp_pd, pd)

अटल व्योम qmp_kick(काष्ठा qmp *qmp)
अणु
	mbox_send_message(qmp->mbox_chan, शून्य);
	mbox_client_txकरोne(qmp->mbox_chan, 0);
पूर्ण

अटल bool qmp_magic_valid(काष्ठा qmp *qmp)
अणु
	वापस पढ़ोl(qmp->msgram + QMP_DESC_MAGIC) == QMP_MAGIC;
पूर्ण

अटल bool qmp_link_acked(काष्ठा qmp *qmp)
अणु
	वापस पढ़ोl(qmp->msgram + QMP_DESC_MCORE_LINK_STATE_ACK) == QMP_STATE_UP;
पूर्ण

अटल bool qmp_mcore_channel_acked(काष्ठा qmp *qmp)
अणु
	वापस पढ़ोl(qmp->msgram + QMP_DESC_MCORE_CH_STATE_ACK) == QMP_STATE_UP;
पूर्ण

अटल bool qmp_ucore_channel_up(काष्ठा qmp *qmp)
अणु
	वापस पढ़ोl(qmp->msgram + QMP_DESC_UCORE_CH_STATE) == QMP_STATE_UP;
पूर्ण

अटल पूर्णांक qmp_खोलो(काष्ठा qmp *qmp)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (!qmp_magic_valid(qmp)) अणु
		dev_err(qmp->dev, "QMP magic doesn't match\n");
		वापस -EINVAL;
	पूर्ण

	val = पढ़ोl(qmp->msgram + QMP_DESC_VERSION);
	अगर (val != QMP_VERSION) अणु
		dev_err(qmp->dev, "unsupported QMP version %d\n", val);
		वापस -EINVAL;
	पूर्ण

	qmp->offset = पढ़ोl(qmp->msgram + QMP_DESC_MCORE_MBOX_OFFSET);
	qmp->size = पढ़ोl(qmp->msgram + QMP_DESC_MCORE_MBOX_SIZE);
	अगर (!qmp->size) अणु
		dev_err(qmp->dev, "invalid mailbox size\n");
		वापस -EINVAL;
	पूर्ण

	/* Ack remote core's link state */
	val = पढ़ोl(qmp->msgram + QMP_DESC_UCORE_LINK_STATE);
	ग_लिखोl(val, qmp->msgram + QMP_DESC_UCORE_LINK_STATE_ACK);

	/* Set local core's link state to up */
	ग_लिखोl(QMP_STATE_UP, qmp->msgram + QMP_DESC_MCORE_LINK_STATE);

	qmp_kick(qmp);

	ret = रुको_event_समयout(qmp->event, qmp_link_acked(qmp), HZ);
	अगर (!ret) अणु
		dev_err(qmp->dev, "ucore didn't ack link\n");
		जाओ समयout_बंद_link;
	पूर्ण

	ग_लिखोl(QMP_STATE_UP, qmp->msgram + QMP_DESC_MCORE_CH_STATE);

	qmp_kick(qmp);

	ret = रुको_event_समयout(qmp->event, qmp_ucore_channel_up(qmp), HZ);
	अगर (!ret) अणु
		dev_err(qmp->dev, "ucore didn't open channel\n");
		जाओ समयout_बंद_channel;
	पूर्ण

	/* Ack remote core's channel state */
	ग_लिखोl(QMP_STATE_UP, qmp->msgram + QMP_DESC_UCORE_CH_STATE_ACK);

	qmp_kick(qmp);

	ret = रुको_event_समयout(qmp->event, qmp_mcore_channel_acked(qmp), HZ);
	अगर (!ret) अणु
		dev_err(qmp->dev, "ucore didn't ack channel\n");
		जाओ समयout_बंद_channel;
	पूर्ण

	वापस 0;

समयout_बंद_channel:
	ग_लिखोl(QMP_STATE_DOWN, qmp->msgram + QMP_DESC_MCORE_CH_STATE);

समयout_बंद_link:
	ग_लिखोl(QMP_STATE_DOWN, qmp->msgram + QMP_DESC_MCORE_LINK_STATE);
	qmp_kick(qmp);

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम qmp_बंद(काष्ठा qmp *qmp)
अणु
	ग_लिखोl(QMP_STATE_DOWN, qmp->msgram + QMP_DESC_MCORE_CH_STATE);
	ग_लिखोl(QMP_STATE_DOWN, qmp->msgram + QMP_DESC_MCORE_LINK_STATE);
	qmp_kick(qmp);
पूर्ण

अटल irqवापस_t qmp_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qmp *qmp = data;

	wake_up_all(&qmp->event);

	वापस IRQ_HANDLED;
पूर्ण

अटल bool qmp_message_empty(काष्ठा qmp *qmp)
अणु
	वापस पढ़ोl(qmp->msgram + qmp->offset) == 0;
पूर्ण

/**
 * qmp_send() - send a message to the AOSS
 * @qmp: qmp context
 * @data: message to be sent
 * @len: length of the message
 *
 * Transmit @data to AOSS and रुको क्रम the AOSS to acknowledge the message.
 * @len must be a multiple of 4 and not दीर्घer than the mailbox size. Access is
 * synchronized by this implementation.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure
 */
अटल पूर्णांक qmp_send(काष्ठा qmp *qmp, स्थिर व्योम *data, माप_प्रकार len)
अणु
	दीर्घ समय_left;
	पूर्णांक ret;

	अगर (WARN_ON(len + माप(u32) > qmp->size))
		वापस -EINVAL;

	अगर (WARN_ON(len % माप(u32)))
		वापस -EINVAL;

	mutex_lock(&qmp->tx_lock);

	/* The message RAM only implements 32-bit accesses */
	__ioग_लिखो32_copy(qmp->msgram + qmp->offset + माप(u32),
			 data, len / माप(u32));
	ग_लिखोl(len, qmp->msgram + qmp->offset);

	/* Read back len to confirm data written in message RAM */
	पढ़ोl(qmp->msgram + qmp->offset);
	qmp_kick(qmp);

	समय_left = रुको_event_पूर्णांकerruptible_समयout(qmp->event,
						     qmp_message_empty(qmp), HZ);
	अगर (!समय_left) अणु
		dev_err(qmp->dev, "ucore did not ack channel\n");
		ret = -ETIMEDOUT;

		/* Clear message from buffer */
		ग_लिखोl(0, qmp->msgram + qmp->offset);
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	mutex_unlock(&qmp->tx_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक qmp_qdss_clk_prepare(काष्ठा clk_hw *hw)
अणु
	अटल स्थिर अक्षर buf[QMP_MSG_LEN] = "{class: clock, res: qdss, val: 1}";
	काष्ठा qmp *qmp = container_of(hw, काष्ठा qmp, qdss_clk);

	वापस qmp_send(qmp, buf, माप(buf));
पूर्ण

अटल व्योम qmp_qdss_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	अटल स्थिर अक्षर buf[QMP_MSG_LEN] = "{class: clock, res: qdss, val: 0}";
	काष्ठा qmp *qmp = container_of(hw, काष्ठा qmp, qdss_clk);

	qmp_send(qmp, buf, माप(buf));
पूर्ण

अटल स्थिर काष्ठा clk_ops qmp_qdss_clk_ops = अणु
	.prepare = qmp_qdss_clk_prepare,
	.unprepare = qmp_qdss_clk_unprepare,
पूर्ण;

अटल पूर्णांक qmp_qdss_clk_add(काष्ठा qmp *qmp)
अणु
	अटल स्थिर काष्ठा clk_init_data qdss_init = अणु
		.ops = &qmp_qdss_clk_ops,
		.name = "qdss",
	पूर्ण;
	पूर्णांक ret;

	qmp->qdss_clk.init = &qdss_init;
	ret = clk_hw_रेजिस्टर(qmp->dev, &qmp->qdss_clk);
	अगर (ret < 0) अणु
		dev_err(qmp->dev, "failed to register qdss clock\n");
		वापस ret;
	पूर्ण

	ret = of_clk_add_hw_provider(qmp->dev->of_node, of_clk_hw_simple_get,
				     &qmp->qdss_clk);
	अगर (ret < 0) अणु
		dev_err(qmp->dev, "unable to register of clk hw provider\n");
		clk_hw_unरेजिस्टर(&qmp->qdss_clk);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम qmp_qdss_clk_हटाओ(काष्ठा qmp *qmp)
अणु
	of_clk_del_provider(qmp->dev->of_node);
	clk_hw_unरेजिस्टर(&qmp->qdss_clk);
पूर्ण

अटल पूर्णांक qmp_pd_घातer_toggle(काष्ठा qmp_pd *res, bool enable)
अणु
	अक्षर buf[QMP_MSG_LEN] = अणुपूर्ण;

	snम_लिखो(buf, माप(buf),
		 "{class: image, res: load_state, name: %s, val: %s}",
		 res->pd.name, enable ? "on" : "off");
	वापस qmp_send(res->qmp, buf, माप(buf));
पूर्ण

अटल पूर्णांक qmp_pd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	वापस qmp_pd_घातer_toggle(to_qmp_pd_resource(करोमुख्य), true);
पूर्ण

अटल पूर्णांक qmp_pd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	वापस qmp_pd_घातer_toggle(to_qmp_pd_resource(करोमुख्य), false);
पूर्ण

अटल स्थिर अक्षर * स्थिर sdm845_resources[] = अणु
	[AOSS_QMP_LS_CDSP] = "cdsp",
	[AOSS_QMP_LS_LPASS] = "adsp",
	[AOSS_QMP_LS_MODEM] = "modem",
	[AOSS_QMP_LS_SLPI] = "slpi",
	[AOSS_QMP_LS_SPSS] = "spss",
	[AOSS_QMP_LS_VENUS] = "venus",
पूर्ण;

अटल पूर्णांक qmp_pd_add(काष्ठा qmp *qmp)
अणु
	काष्ठा genpd_onecell_data *data = &qmp->pd_data;
	काष्ठा device *dev = qmp->dev;
	काष्ठा qmp_pd *res;
	माप_प्रकार num = ARRAY_SIZE(sdm845_resources);
	पूर्णांक ret;
	पूर्णांक i;

	res = devm_kसुस्मृति(dev, num, माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस -ENOMEM;

	data->करोमुख्यs = devm_kसुस्मृति(dev, num, माप(*data->करोमुख्यs),
				     GFP_KERNEL);
	अगर (!data->करोमुख्यs)
		वापस -ENOMEM;

	क्रम (i = 0; i < num; i++) अणु
		res[i].qmp = qmp;
		res[i].pd.name = sdm845_resources[i];
		res[i].pd.घातer_on = qmp_pd_घातer_on;
		res[i].pd.घातer_off = qmp_pd_घातer_off;

		ret = pm_genpd_init(&res[i].pd, शून्य, true);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to init genpd\n");
			जाओ unroll_genpds;
		पूर्ण

		data->करोमुख्यs[i] = &res[i].pd;
	पूर्ण

	data->num_करोमुख्यs = i;

	ret = of_genpd_add_provider_onecell(dev->of_node, data);
	अगर (ret < 0)
		जाओ unroll_genpds;

	वापस 0;

unroll_genpds:
	क्रम (i--; i >= 0; i--)
		pm_genpd_हटाओ(data->करोमुख्यs[i]);

	वापस ret;
पूर्ण

अटल व्योम qmp_pd_हटाओ(काष्ठा qmp *qmp)
अणु
	काष्ठा genpd_onecell_data *data = &qmp->pd_data;
	काष्ठा device *dev = qmp->dev;
	पूर्णांक i;

	of_genpd_del_provider(dev->of_node);

	क्रम (i = 0; i < data->num_करोमुख्यs; i++)
		pm_genpd_हटाओ(data->करोमुख्यs[i]);
पूर्ण

अटल पूर्णांक qmp_cdev_get_max_state(काष्ठा thermal_cooling_device *cdev,
				  अचिन्हित दीर्घ *state)
अणु
	*state = qmp_cdev_max_state;
	वापस 0;
पूर्ण

अटल पूर्णांक qmp_cdev_get_cur_state(काष्ठा thermal_cooling_device *cdev,
				  अचिन्हित दीर्घ *state)
अणु
	काष्ठा qmp_cooling_device *qmp_cdev = cdev->devdata;

	*state = qmp_cdev->state;
	वापस 0;
पूर्ण

अटल पूर्णांक qmp_cdev_set_cur_state(काष्ठा thermal_cooling_device *cdev,
				  अचिन्हित दीर्घ state)
अणु
	काष्ठा qmp_cooling_device *qmp_cdev = cdev->devdata;
	अक्षर buf[QMP_MSG_LEN] = अणुपूर्ण;
	bool cdev_state;
	पूर्णांक ret;

	/* Normalize state */
	cdev_state = !!state;

	अगर (qmp_cdev->state == state)
		वापस 0;

	snम_लिखो(buf, माप(buf),
		 "{class: volt_flr, event:zero_temp, res:%s, value:%s}",
			qmp_cdev->name,
			cdev_state ? "on" : "off");

	ret = qmp_send(qmp_cdev->qmp, buf, माप(buf));

	अगर (!ret)
		qmp_cdev->state = cdev_state;

	वापस ret;
पूर्ण

अटल काष्ठा thermal_cooling_device_ops qmp_cooling_device_ops = अणु
	.get_max_state = qmp_cdev_get_max_state,
	.get_cur_state = qmp_cdev_get_cur_state,
	.set_cur_state = qmp_cdev_set_cur_state,
पूर्ण;

अटल पूर्णांक qmp_cooling_device_add(काष्ठा qmp *qmp,
				  काष्ठा qmp_cooling_device *qmp_cdev,
				  काष्ठा device_node *node)
अणु
	अक्षर *cdev_name = (अक्षर *)node->name;

	qmp_cdev->qmp = qmp;
	qmp_cdev->state = !qmp_cdev_max_state;
	qmp_cdev->name = cdev_name;
	qmp_cdev->cdev = devm_thermal_of_cooling_device_रेजिस्टर
				(qmp->dev, node,
				cdev_name,
				qmp_cdev, &qmp_cooling_device_ops);

	अगर (IS_ERR(qmp_cdev->cdev))
		dev_err(qmp->dev, "unable to register %s cooling device\n",
			cdev_name);

	वापस PTR_ERR_OR_ZERO(qmp_cdev->cdev);
पूर्ण

अटल पूर्णांक qmp_cooling_devices_रेजिस्टर(काष्ठा qmp *qmp)
अणु
	काष्ठा device_node *np, *child;
	पूर्णांक count = QMP_NUM_COOLING_RESOURCES;
	पूर्णांक ret;

	np = qmp->dev->of_node;

	qmp->cooling_devs = devm_kसुस्मृति(qmp->dev, count,
					 माप(*qmp->cooling_devs),
					 GFP_KERNEL);

	अगर (!qmp->cooling_devs)
		वापस -ENOMEM;

	क्रम_each_available_child_of_node(np, child) अणु
		अगर (!of_find_property(child, "#cooling-cells", शून्य))
			जारी;
		ret = qmp_cooling_device_add(qmp, &qmp->cooling_devs[count++],
					     child);
		अगर (ret)
			जाओ unroll;
	पूर्ण

	वापस 0;

unroll:
	जबतक (--count >= 0)
		thermal_cooling_device_unरेजिस्टर
			(qmp->cooling_devs[count].cdev);

	वापस ret;
पूर्ण

अटल व्योम qmp_cooling_devices_हटाओ(काष्ठा qmp *qmp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < QMP_NUM_COOLING_RESOURCES; i++)
		thermal_cooling_device_unरेजिस्टर(qmp->cooling_devs[i].cdev);
पूर्ण

अटल पूर्णांक qmp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा qmp *qmp;
	पूर्णांक irq;
	पूर्णांक ret;

	qmp = devm_kzalloc(&pdev->dev, माप(*qmp), GFP_KERNEL);
	अगर (!qmp)
		वापस -ENOMEM;

	qmp->dev = &pdev->dev;
	init_रुकोqueue_head(&qmp->event);
	mutex_init(&qmp->tx_lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	qmp->msgram = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(qmp->msgram))
		वापस PTR_ERR(qmp->msgram);

	qmp->mbox_client.dev = &pdev->dev;
	qmp->mbox_client.knows_txकरोne = true;
	qmp->mbox_chan = mbox_request_channel(&qmp->mbox_client, 0);
	अगर (IS_ERR(qmp->mbox_chan)) अणु
		dev_err(&pdev->dev, "failed to acquire ipc mailbox\n");
		वापस PTR_ERR(qmp->mbox_chan);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, irq, qmp_पूर्णांकr, IRQF_ONESHOT,
			       "aoss-qmp", qmp);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to request interrupt\n");
		जाओ err_मुक्त_mbox;
	पूर्ण

	ret = qmp_खोलो(qmp);
	अगर (ret < 0)
		जाओ err_मुक्त_mbox;

	ret = qmp_qdss_clk_add(qmp);
	अगर (ret)
		जाओ err_बंद_qmp;

	ret = qmp_pd_add(qmp);
	अगर (ret)
		जाओ err_हटाओ_qdss_clk;

	ret = qmp_cooling_devices_रेजिस्टर(qmp);
	अगर (ret)
		dev_err(&pdev->dev, "failed to register aoss cooling devices\n");

	platक्रमm_set_drvdata(pdev, qmp);

	वापस 0;

err_हटाओ_qdss_clk:
	qmp_qdss_clk_हटाओ(qmp);
err_बंद_qmp:
	qmp_बंद(qmp);
err_मुक्त_mbox:
	mbox_मुक्त_channel(qmp->mbox_chan);

	वापस ret;
पूर्ण

अटल पूर्णांक qmp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qmp *qmp = platक्रमm_get_drvdata(pdev);

	qmp_qdss_clk_हटाओ(qmp);
	qmp_pd_हटाओ(qmp);
	qmp_cooling_devices_हटाओ(qmp);

	qmp_बंद(qmp);
	mbox_मुक्त_channel(qmp->mbox_chan);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qmp_dt_match[] = अणु
	अणु .compatible = "qcom,sc7180-aoss-qmp", पूर्ण,
	अणु .compatible = "qcom,sc7280-aoss-qmp", पूर्ण,
	अणु .compatible = "qcom,sdm845-aoss-qmp", पूर्ण,
	अणु .compatible = "qcom,sm8150-aoss-qmp", पूर्ण,
	अणु .compatible = "qcom,sm8250-aoss-qmp", पूर्ण,
	अणु .compatible = "qcom,sm8350-aoss-qmp", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qmp_dt_match);

अटल काष्ठा platक्रमm_driver qmp_driver = अणु
	.driver = अणु
		.name		= "qcom_aoss_qmp",
		.of_match_table	= qmp_dt_match,
	पूर्ण,
	.probe = qmp_probe,
	.हटाओ	= qmp_हटाओ,
पूर्ण;
module_platक्रमm_driver(qmp_driver);

MODULE_DESCRIPTION("Qualcomm AOSS QMP driver");
MODULE_LICENSE("GPL v2");
