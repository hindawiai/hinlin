<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2021 Pengutronix, Oleksij Rempel <kernel@pengutronix.de>
 */

#समावेश <linux/counter.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा INTERRUPT_CNT_NAME "interrupt-cnt"

काष्ठा पूर्णांकerrupt_cnt_priv अणु
	atomic_t count;
	काष्ठा counter_device counter;
	काष्ठा gpio_desc *gpio;
	पूर्णांक irq;
	bool enabled;
	काष्ठा counter_संकेत संकेतs;
	काष्ठा counter_synapse synapses;
	काष्ठा counter_count cnts;
पूर्ण;

अटल irqवापस_t पूर्णांकerrupt_cnt_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा पूर्णांकerrupt_cnt_priv *priv = dev_id;

	atomic_inc(&priv->count);

	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार पूर्णांकerrupt_cnt_enable_पढ़ो(काष्ठा counter_device *counter,
					 काष्ठा counter_count *count,
					 व्योम *निजी, अक्षर *buf)
अणु
	काष्ठा पूर्णांकerrupt_cnt_priv *priv = counter->priv;

	वापस sysfs_emit(buf, "%d\n", priv->enabled);
पूर्ण

अटल sमाप_प्रकार पूर्णांकerrupt_cnt_enable_ग_लिखो(काष्ठा counter_device *counter,
					  काष्ठा counter_count *count,
					  व्योम *निजी, स्थिर अक्षर *buf,
					  माप_प्रकार len)
अणु
	काष्ठा पूर्णांकerrupt_cnt_priv *priv = counter->priv;
	bool enable;
	sमाप_प्रकार ret;

	ret = kstrtobool(buf, &enable);
	अगर (ret)
		वापस ret;

	अगर (priv->enabled == enable)
		वापस len;

	अगर (enable) अणु
		priv->enabled = true;
		enable_irq(priv->irq);
	पूर्ण अन्यथा अणु
		disable_irq(priv->irq);
		priv->enabled = false;
	पूर्ण

	वापस len;
पूर्ण

अटल स्थिर काष्ठा counter_count_ext पूर्णांकerrupt_cnt_ext[] = अणु
	अणु
		.name = "enable",
		.पढ़ो = पूर्णांकerrupt_cnt_enable_पढ़ो,
		.ग_लिखो = पूर्णांकerrupt_cnt_enable_ग_लिखो,
	पूर्ण,
पूर्ण;

अटल क्रमागत counter_synapse_action पूर्णांकerrupt_cnt_synapse_actionss[] = अणु
	COUNTER_SYNAPSE_ACTION_RISING_EDGE,
पूर्ण;

अटल पूर्णांक पूर्णांकerrupt_cnt_action_get(काष्ठा counter_device *counter,
				    काष्ठा counter_count *count,
				    काष्ठा counter_synapse *synapse,
				    माप_प्रकार *action)
अणु
	*action = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकerrupt_cnt_पढ़ो(काष्ठा counter_device *counter,
			      काष्ठा counter_count *count, अचिन्हित दीर्घ *val)
अणु
	काष्ठा पूर्णांकerrupt_cnt_priv *priv = counter->priv;

	*val = atomic_पढ़ो(&priv->count);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकerrupt_cnt_ग_लिखो(काष्ठा counter_device *counter,
			       काष्ठा counter_count *count,
			       स्थिर अचिन्हित दीर्घ val)
अणु
	काष्ठा पूर्णांकerrupt_cnt_priv *priv = counter->priv;

	atomic_set(&priv->count, val);

	वापस 0;
पूर्ण

अटल क्रमागत counter_count_function पूर्णांकerrupt_cnt_functions[] = अणु
	COUNTER_COUNT_FUNCTION_INCREASE,
पूर्ण;

अटल पूर्णांक पूर्णांकerrupt_cnt_function_get(काष्ठा counter_device *counter,
				      काष्ठा counter_count *count,
				      माप_प्रकार *function)
अणु
	*function = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकerrupt_cnt_संकेत_पढ़ो(काष्ठा counter_device *counter,
				     काष्ठा counter_संकेत *संकेत,
				     क्रमागत counter_संकेत_value *val)
अणु
	काष्ठा पूर्णांकerrupt_cnt_priv *priv = counter->priv;
	पूर्णांक ret;

	अगर (!priv->gpio)
		वापस -EINVAL;

	ret = gpiod_get_value(priv->gpio);
	अगर (ret < 0)
		वापस ret;

	*val = ret ? COUNTER_SIGNAL_HIGH : COUNTER_SIGNAL_LOW;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा counter_ops पूर्णांकerrupt_cnt_ops = अणु
	.action_get = पूर्णांकerrupt_cnt_action_get,
	.count_पढ़ो = पूर्णांकerrupt_cnt_पढ़ो,
	.count_ग_लिखो = पूर्णांकerrupt_cnt_ग_लिखो,
	.function_get = पूर्णांकerrupt_cnt_function_get,
	.संकेत_पढ़ो  = पूर्णांकerrupt_cnt_संकेत_पढ़ो,
पूर्ण;

अटल पूर्णांक पूर्णांकerrupt_cnt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांकerrupt_cnt_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->irq = platक्रमm_get_irq_optional(pdev,  0);
	अगर (priv->irq == -ENXIO)
		priv->irq = 0;
	अन्यथा अगर (priv->irq < 0)
		वापस dev_err_probe(dev, priv->irq, "failed to get IRQ\n");

	priv->gpio = devm_gpiod_get_optional(dev, शून्य, GPIOD_IN);
	अगर (IS_ERR(priv->gpio))
		वापस dev_err_probe(dev, PTR_ERR(priv->gpio), "failed to get GPIO\n");

	अगर (!priv->irq && !priv->gpio) अणु
		dev_err(dev, "IRQ and GPIO are not found. At least one source should be provided\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!priv->irq) अणु
		पूर्णांक irq = gpiod_to_irq(priv->gpio);

		अगर (irq < 0)
			वापस dev_err_probe(dev, irq, "failed to get IRQ from GPIO\n");

		priv->irq = irq;
	पूर्ण

	priv->संकेतs.name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "IRQ %d",
					    priv->irq);
	अगर (!priv->संकेतs.name)
		वापस -ENOMEM;

	priv->counter.संकेतs = &priv->संकेतs;
	priv->counter.num_संकेतs = 1;

	priv->synapses.actions_list = पूर्णांकerrupt_cnt_synapse_actionss;
	priv->synapses.num_actions = ARRAY_SIZE(पूर्णांकerrupt_cnt_synapse_actionss);
	priv->synapses.संकेत = &priv->संकेतs;

	priv->cnts.name = "Channel 0 Count";
	priv->cnts.functions_list = पूर्णांकerrupt_cnt_functions;
	priv->cnts.num_functions = ARRAY_SIZE(पूर्णांकerrupt_cnt_functions);
	priv->cnts.synapses = &priv->synapses;
	priv->cnts.num_synapses = 1;
	priv->cnts.ext = पूर्णांकerrupt_cnt_ext;
	priv->cnts.num_ext = ARRAY_SIZE(पूर्णांकerrupt_cnt_ext);

	priv->counter.priv = priv;
	priv->counter.name = dev_name(dev);
	priv->counter.parent = dev;
	priv->counter.ops = &पूर्णांकerrupt_cnt_ops;
	priv->counter.counts = &priv->cnts;
	priv->counter.num_counts = 1;

	irq_set_status_flags(priv->irq, IRQ_NOAUTOEN);
	ret = devm_request_irq(dev, priv->irq, पूर्णांकerrupt_cnt_isr,
			       IRQF_TRIGGER_RISING | IRQF_NO_THREAD,
			       dev_name(dev), priv);
	अगर (ret)
		वापस ret;

	वापस devm_counter_रेजिस्टर(dev, &priv->counter);
पूर्ण

अटल स्थिर काष्ठा of_device_id पूर्णांकerrupt_cnt_of_match[] = अणु
	अणु .compatible = "interrupt-counter", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, पूर्णांकerrupt_cnt_of_match);

अटल काष्ठा platक्रमm_driver पूर्णांकerrupt_cnt_driver = अणु
	.probe = पूर्णांकerrupt_cnt_probe,
	.driver = अणु
		.name = INTERRUPT_CNT_NAME,
		.of_match_table = पूर्णांकerrupt_cnt_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(पूर्णांकerrupt_cnt_driver);

MODULE_ALIAS("platform:interrupt-counter");
MODULE_AUTHOR("Oleksij Rempel <o.rempel@pengutronix.de>");
MODULE_DESCRIPTION("Interrupt counter driver");
MODULE_LICENSE("GPL v2");
