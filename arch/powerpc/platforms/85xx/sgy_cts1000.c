<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Servergy CTS-1000 Setup
 *
 * Maपूर्णांकained by Ben Collins <ben.c@servergy.com>
 *
 * Copyright 2012 by Servergy, Inc.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/reboot.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/machdep.h>

अटल काष्ठा device_node *halt_node;

अटल स्थिर काष्ठा of_device_id child_match[] = अणु
	अणु
		.compatible = "sgy,gpio-halt",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम gpio_halt_wfn(काष्ठा work_काष्ठा *work)
अणु
	/* Likely wont वापस */
	orderly_घातeroff(true);
पूर्ण
अटल DECLARE_WORK(gpio_halt_wq, gpio_halt_wfn);

अटल व्योम __noवापस gpio_halt_cb(व्योम)
अणु
	क्रमागत of_gpio_flags flags;
	पूर्णांक trigger, gpio;

	अगर (!halt_node)
		panic("No reset GPIO information was provided in DT\n");

	gpio = of_get_gpio_flags(halt_node, 0, &flags);

	अगर (!gpio_is_valid(gpio))
		panic("Provided GPIO is invalid\n");

	trigger = (flags == OF_GPIO_ACTIVE_LOW);

	prपूर्णांकk(KERN_INFO "gpio-halt: triggering GPIO.\n");

	/* Probably wont वापस */
	gpio_set_value(gpio, trigger);

	panic("Halt failed\n");
पूर्ण

/* This IRQ means someone pressed the घातer button and it is रुकोing क्रम us
 * to handle the shutकरोwn/घातeroff. */
अटल irqवापस_t gpio_halt_irq(पूर्णांक irq, व्योम *__data)
अणु
	prपूर्णांकk(KERN_INFO "gpio-halt: shutdown due to power button IRQ.\n");
	schedule_work(&gpio_halt_wq);

        वापस IRQ_HANDLED;
पूर्ण;

अटल पूर्णांक gpio_halt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	क्रमागत of_gpio_flags flags;
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक gpio, err, irq;
	पूर्णांक trigger;

	अगर (!node)
		वापस -ENODEV;

	/* If there's no matching child, this isn't really an error */
	halt_node = of_find_matching_node(node, child_match);
	अगर (!halt_node)
		वापस 0;

	/* Technically we could just पढ़ो the first one, but punish
	 * DT ग_लिखोrs क्रम invalid क्रमm. */
	अगर (of_gpio_count(halt_node) != 1)
		वापस -EINVAL;

	/* Get the gpio number relative to the dynamic base. */
	gpio = of_get_gpio_flags(halt_node, 0, &flags);
	अगर (!gpio_is_valid(gpio))
		वापस -EINVAL;

	err = gpio_request(gpio, "gpio-halt");
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "gpio-halt: error requesting GPIO %d.\n",
		       gpio);
		halt_node = शून्य;
		वापस err;
	पूर्ण

	trigger = (flags == OF_GPIO_ACTIVE_LOW);

	gpio_direction_output(gpio, !trigger);

	/* Now get the IRQ which tells us when the घातer button is hit */
	irq = irq_of_parse_and_map(halt_node, 0);
	err = request_irq(irq, gpio_halt_irq, IRQF_TRIGGER_RISING |
			  IRQF_TRIGGER_FALLING, "gpio-halt", halt_node);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "gpio-halt: error requesting IRQ %d for "
		       "GPIO %d.\n", irq, gpio);
		gpio_मुक्त(gpio);
		halt_node = शून्य;
		वापस err;
	पूर्ण

	/* Register our halt function */
	ppc_md.halt = gpio_halt_cb;
	pm_घातer_off = gpio_halt_cb;

	prपूर्णांकk(KERN_INFO "gpio-halt: registered GPIO %d (%d trigger, %d"
	       " irq).\n", gpio, trigger, irq);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_halt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (halt_node) अणु
		पूर्णांक gpio = of_get_gpio(halt_node, 0);
		पूर्णांक irq = irq_of_parse_and_map(halt_node, 0);

		मुक्त_irq(irq, halt_node);

		ppc_md.halt = शून्य;
		pm_घातer_off = शून्य;

		gpio_मुक्त(gpio);

		halt_node = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gpio_halt_match[] = अणु
	/* We match on the gpio bus itself and scan the children since they
	 * wont be matched against us. We know the bus wont match until it
	 * has been रेजिस्टरed too. */
	अणु
		.compatible = "fsl,qoriq-gpio",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_halt_match);

अटल काष्ठा platक्रमm_driver gpio_halt_driver = अणु
	.driver = अणु
		.name		= "gpio-halt",
		.of_match_table = gpio_halt_match,
	पूर्ण,
	.probe		= gpio_halt_probe,
	.हटाओ		= gpio_halt_हटाओ,
पूर्ण;

module_platक्रमm_driver(gpio_halt_driver);

MODULE_DESCRIPTION("Driver to support GPIO triggered system halt for Servergy CTS-1000 Systems.");
MODULE_VERSION("1.0");
MODULE_AUTHOR("Ben Collins <ben.c@servergy.com>");
MODULE_LICENSE("GPL");
