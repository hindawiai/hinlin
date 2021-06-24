<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <media/cec-notअगरier.h>
#समावेश <media/cec-pin.h>

काष्ठा cec_gpio अणु
	काष्ठा cec_adapter	*adap;
	काष्ठा cec_notअगरier	*notअगरier;
	काष्ठा device		*dev;

	काष्ठा gpio_desc	*cec_gpio;
	पूर्णांक			cec_irq;
	bool			cec_is_low;

	काष्ठा gpio_desc	*hpd_gpio;
	पूर्णांक			hpd_irq;
	bool			hpd_is_high;
	kसमय_प्रकार			hpd_ts;

	काष्ठा gpio_desc	*v5_gpio;
	पूर्णांक			v5_irq;
	bool			v5_is_high;
	kसमय_प्रकार			v5_ts;
पूर्ण;

अटल पूर्णांक cec_gpio_पढ़ो(काष्ठा cec_adapter *adap)
अणु
	काष्ठा cec_gpio *cec = cec_get_drvdata(adap);

	अगर (cec->cec_is_low)
		वापस 0;
	वापस gpiod_get_value(cec->cec_gpio);
पूर्ण

अटल व्योम cec_gpio_high(काष्ठा cec_adapter *adap)
अणु
	काष्ठा cec_gpio *cec = cec_get_drvdata(adap);

	अगर (!cec->cec_is_low)
		वापस;
	cec->cec_is_low = false;
	gpiod_set_value(cec->cec_gpio, 1);
पूर्ण

अटल व्योम cec_gpio_low(काष्ठा cec_adapter *adap)
अणु
	काष्ठा cec_gpio *cec = cec_get_drvdata(adap);

	अगर (cec->cec_is_low)
		वापस;
	cec->cec_is_low = true;
	gpiod_set_value(cec->cec_gpio, 0);
पूर्ण

अटल irqवापस_t cec_hpd_gpio_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा cec_gpio *cec = priv;

	cec_queue_pin_hpd_event(cec->adap, cec->hpd_is_high, cec->hpd_ts);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t cec_5v_gpio_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा cec_gpio *cec = priv;
	पूर्णांक val = gpiod_get_value(cec->v5_gpio);
	bool is_high = val > 0;

	अगर (val < 0 || is_high == cec->v5_is_high)
		वापस IRQ_HANDLED;
	cec->v5_ts = kसमय_get();
	cec->v5_is_high = is_high;
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t cec_5v_gpio_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा cec_gpio *cec = priv;

	cec_queue_pin_5v_event(cec->adap, cec->v5_is_high, cec->v5_ts);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t cec_hpd_gpio_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा cec_gpio *cec = priv;
	पूर्णांक val = gpiod_get_value(cec->hpd_gpio);
	bool is_high = val > 0;

	अगर (val < 0 || is_high == cec->hpd_is_high)
		वापस IRQ_HANDLED;
	cec->hpd_ts = kसमय_get();
	cec->hpd_is_high = is_high;
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t cec_gpio_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा cec_gpio *cec = priv;
	पूर्णांक val = gpiod_get_value(cec->cec_gpio);

	अगर (val >= 0)
		cec_pin_changed(cec->adap, val > 0);
	वापस IRQ_HANDLED;
पूर्ण

अटल bool cec_gpio_enable_irq(काष्ठा cec_adapter *adap)
अणु
	काष्ठा cec_gpio *cec = cec_get_drvdata(adap);

	enable_irq(cec->cec_irq);
	वापस true;
पूर्ण

अटल व्योम cec_gpio_disable_irq(काष्ठा cec_adapter *adap)
अणु
	काष्ठा cec_gpio *cec = cec_get_drvdata(adap);

	disable_irq(cec->cec_irq);
पूर्ण

अटल व्योम cec_gpio_status(काष्ठा cec_adapter *adap, काष्ठा seq_file *file)
अणु
	काष्ठा cec_gpio *cec = cec_get_drvdata(adap);

	seq_म_लिखो(file, "mode: %s\n", cec->cec_is_low ? "low-drive" : "read");
	seq_म_लिखो(file, "using irq: %d\n", cec->cec_irq);
	अगर (cec->hpd_gpio)
		seq_म_लिखो(file, "hpd: %s\n",
			   cec->hpd_is_high ? "high" : "low");
	अगर (cec->v5_gpio)
		seq_म_लिखो(file, "5V: %s\n",
			   cec->v5_is_high ? "high" : "low");
पूर्ण

अटल पूर्णांक cec_gpio_पढ़ो_hpd(काष्ठा cec_adapter *adap)
अणु
	काष्ठा cec_gpio *cec = cec_get_drvdata(adap);

	अगर (!cec->hpd_gpio)
		वापस -ENOTTY;
	वापस gpiod_get_value(cec->hpd_gpio);
पूर्ण

अटल पूर्णांक cec_gpio_पढ़ो_5v(काष्ठा cec_adapter *adap)
अणु
	काष्ठा cec_gpio *cec = cec_get_drvdata(adap);

	अगर (!cec->v5_gpio)
		वापस -ENOTTY;
	वापस gpiod_get_value(cec->v5_gpio);
पूर्ण

अटल व्योम cec_gpio_मुक्त(काष्ठा cec_adapter *adap)
अणु
	cec_gpio_disable_irq(adap);
पूर्ण

अटल स्थिर काष्ठा cec_pin_ops cec_gpio_pin_ops = अणु
	.पढ़ो = cec_gpio_पढ़ो,
	.low = cec_gpio_low,
	.high = cec_gpio_high,
	.enable_irq = cec_gpio_enable_irq,
	.disable_irq = cec_gpio_disable_irq,
	.status = cec_gpio_status,
	.मुक्त = cec_gpio_मुक्त,
	.पढ़ो_hpd = cec_gpio_पढ़ो_hpd,
	.पढ़ो_5v = cec_gpio_पढ़ो_5v,
पूर्ण;

अटल पूर्णांक cec_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *hdmi_dev;
	काष्ठा cec_gpio *cec;
	u32 caps = CEC_CAP_DEFAULTS | CEC_CAP_MONITOR_ALL | CEC_CAP_MONITOR_PIN;
	पूर्णांक ret;

	hdmi_dev = cec_notअगरier_parse_hdmi_phandle(dev);
	अगर (PTR_ERR(hdmi_dev) == -EPROBE_DEFER)
		वापस PTR_ERR(hdmi_dev);
	अगर (IS_ERR(hdmi_dev))
		caps |= CEC_CAP_PHYS_ADDR;

	cec = devm_kzalloc(dev, माप(*cec), GFP_KERNEL);
	अगर (!cec)
		वापस -ENOMEM;

	cec->dev = dev;

	cec->cec_gpio = devm_gpiod_get(dev, "cec", GPIOD_OUT_HIGH_OPEN_DRAIN);
	अगर (IS_ERR(cec->cec_gpio))
		वापस PTR_ERR(cec->cec_gpio);
	cec->cec_irq = gpiod_to_irq(cec->cec_gpio);

	cec->hpd_gpio = devm_gpiod_get_optional(dev, "hpd", GPIOD_IN);
	अगर (IS_ERR(cec->hpd_gpio))
		वापस PTR_ERR(cec->hpd_gpio);

	cec->v5_gpio = devm_gpiod_get_optional(dev, "v5", GPIOD_IN);
	अगर (IS_ERR(cec->v5_gpio))
		वापस PTR_ERR(cec->v5_gpio);

	cec->adap = cec_pin_allocate_adapter(&cec_gpio_pin_ops,
					     cec, pdev->name, caps);
	अगर (IS_ERR(cec->adap))
		वापस PTR_ERR(cec->adap);

	ret = devm_request_irq(dev, cec->cec_irq, cec_gpio_irq_handler,
			       IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
			       cec->adap->name, cec);
	अगर (ret)
		जाओ del_adap;

	cec_gpio_disable_irq(cec->adap);

	अगर (cec->hpd_gpio) अणु
		cec->hpd_irq = gpiod_to_irq(cec->hpd_gpio);
		ret = devm_request_thपढ़ोed_irq(dev, cec->hpd_irq,
			cec_hpd_gpio_irq_handler,
			cec_hpd_gpio_irq_handler_thपढ़ो,
			IRQF_ONESHOT |
			IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
			"hpd-gpio", cec);
		अगर (ret)
			जाओ del_adap;
	पूर्ण

	अगर (cec->v5_gpio) अणु
		cec->v5_irq = gpiod_to_irq(cec->v5_gpio);
		ret = devm_request_thपढ़ोed_irq(dev, cec->v5_irq,
			cec_5v_gpio_irq_handler,
			cec_5v_gpio_irq_handler_thपढ़ो,
			IRQF_ONESHOT |
			IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
			"v5-gpio", cec);
		अगर (ret)
			जाओ del_adap;
	पूर्ण

	अगर (!IS_ERR(hdmi_dev)) अणु
		cec->notअगरier = cec_notअगरier_cec_adap_रेजिस्टर(hdmi_dev, शून्य,
							       cec->adap);
		अगर (!cec->notअगरier) अणु
			ret = -ENOMEM;
			जाओ del_adap;
		पूर्ण
	पूर्ण

	ret = cec_रेजिस्टर_adapter(cec->adap, &pdev->dev);
	अगर (ret)
		जाओ unreg_notअगरier;

	platक्रमm_set_drvdata(pdev, cec);
	वापस 0;

unreg_notअगरier:
	cec_notअगरier_cec_adap_unरेजिस्टर(cec->notअगरier, cec->adap);
del_adap:
	cec_delete_adapter(cec->adap);
	वापस ret;
पूर्ण

अटल पूर्णांक cec_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cec_gpio *cec = platक्रमm_get_drvdata(pdev);

	cec_notअगरier_cec_adap_unरेजिस्टर(cec->notअगरier, cec->adap);
	cec_unरेजिस्टर_adapter(cec->adap);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cec_gpio_match[] = अणु
	अणु
		.compatible	= "cec-gpio",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cec_gpio_match);

अटल काष्ठा platक्रमm_driver cec_gpio_pdrv = अणु
	.probe	= cec_gpio_probe,
	.हटाओ = cec_gpio_हटाओ,
	.driver = अणु
		.name		= "cec-gpio",
		.of_match_table	= cec_gpio_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cec_gpio_pdrv);

MODULE_AUTHOR("Hans Verkuil <hans.verkuil@cisco.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("CEC GPIO driver");
