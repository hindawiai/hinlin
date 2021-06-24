<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * nokia-modem.c
 *
 * HSI client driver क्रम Nokia N900 modem.
 *
 * Copyright (C) 2014 Sebastian Reichel <sre@kernel.org>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/hsi/hsi.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/hsi/ssi_protocol.h>

अटल अचिन्हित पूर्णांक pm = 1;
module_param(pm, पूर्णांक, 0400);
MODULE_PARM_DESC(pm,
	"Enable power management (0=disabled, 1=userland based [default])");

काष्ठा nokia_modem_gpio अणु
	काष्ठा gpio_desc	*gpio;
	स्थिर अक्षर		*name;
पूर्ण;

काष्ठा nokia_modem_device अणु
	काष्ठा tasklet_काष्ठा	nokia_modem_rst_ind_tasklet;
	पूर्णांक			nokia_modem_rst_ind_irq;
	काष्ठा device		*device;
	काष्ठा nokia_modem_gpio	*gpios;
	पूर्णांक			gpio_amount;
	काष्ठा hsi_client	*ssi_protocol;
	काष्ठा hsi_client	*cmt_speech;
पूर्ण;

अटल व्योम करो_nokia_modem_rst_ind_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा nokia_modem_device *modem = (काष्ठा nokia_modem_device *)data;

	अगर (!modem)
		वापस;

	dev_info(modem->device, "CMT rst line change detected\n");

	अगर (modem->ssi_protocol)
		ssip_reset_event(modem->ssi_protocol);
पूर्ण

अटल irqवापस_t nokia_modem_rst_ind_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nokia_modem_device *modem = (काष्ठा nokia_modem_device *)data;

	tasklet_schedule(&modem->nokia_modem_rst_ind_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम nokia_modem_gpio_unexport(काष्ठा device *dev)
अणु
	काष्ठा nokia_modem_device *modem = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < modem->gpio_amount; i++) अणु
		sysfs_हटाओ_link(&dev->kobj, modem->gpios[i].name);
		gpiod_unexport(modem->gpios[i].gpio);
	पूर्ण
पूर्ण

अटल पूर्णांक nokia_modem_gpio_probe(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा nokia_modem_device *modem = dev_get_drvdata(dev);
	पूर्णांक gpio_count, gpio_name_count, i, err;

	gpio_count = of_gpio_count(np);

	अगर (gpio_count < 0) अणु
		dev_err(dev, "missing gpios: %d\n", gpio_count);
		वापस gpio_count;
	पूर्ण

	gpio_name_count = of_property_count_strings(np, "gpio-names");

	अगर (gpio_count != gpio_name_count) अणु
		dev_err(dev, "number of gpios does not equal number of gpio names\n");
		वापस -EINVAL;
	पूर्ण

	modem->gpios = devm_kसुस्मृति(dev, gpio_count, माप(*modem->gpios),
				    GFP_KERNEL);
	अगर (!modem->gpios)
		वापस -ENOMEM;

	modem->gpio_amount = gpio_count;

	क्रम (i = 0; i < gpio_count; i++) अणु
		modem->gpios[i].gpio = devm_gpiod_get_index(dev, शून्य, i,
							    GPIOD_OUT_LOW);
		अगर (IS_ERR(modem->gpios[i].gpio)) अणु
			dev_err(dev, "Could not get gpio %d\n", i);
			वापस PTR_ERR(modem->gpios[i].gpio);
		पूर्ण

		err = of_property_पढ़ो_string_index(np, "gpio-names", i,
						&(modem->gpios[i].name));
		अगर (err) अणु
			dev_err(dev, "Could not get gpio name %d\n", i);
			वापस err;
		पूर्ण

		err = gpiod_export(modem->gpios[i].gpio, 0);
		अगर (err)
			वापस err;

		err = gpiod_export_link(dev, modem->gpios[i].name,
							modem->gpios[i].gpio);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nokia_modem_probe(काष्ठा device *dev)
अणु
	काष्ठा device_node *np;
	काष्ठा nokia_modem_device *modem;
	काष्ठा hsi_client *cl = to_hsi_client(dev);
	काष्ठा hsi_port *port = hsi_get_port(cl);
	पूर्णांक irq, pflags, err;
	काष्ठा hsi_board_info ssip;
	काष्ठा hsi_board_info cmtspeech;

	np = dev->of_node;
	अगर (!np) अणु
		dev_err(dev, "device tree node not found\n");
		वापस -ENXIO;
	पूर्ण

	modem = devm_kzalloc(dev, माप(*modem), GFP_KERNEL);
	अगर (!modem)
		वापस -ENOMEM;

	dev_set_drvdata(dev, modem);
	modem->device = dev;

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		dev_err(dev, "Invalid rst_ind interrupt (%d)\n", irq);
		वापस -EINVAL;
	पूर्ण
	modem->nokia_modem_rst_ind_irq = irq;
	pflags = irq_get_trigger_type(irq);

	tasklet_init(&modem->nokia_modem_rst_ind_tasklet,
			करो_nokia_modem_rst_ind_tasklet, (अचिन्हित दीर्घ)modem);
	err = devm_request_irq(dev, irq, nokia_modem_rst_ind_isr,
				pflags, "modem_rst_ind", modem);
	अगर (err < 0) अणु
		dev_err(dev, "Request rst_ind irq(%d) failed (flags %d)\n",
								irq, pflags);
		वापस err;
	पूर्ण
	enable_irq_wake(irq);

	अगर (pm) अणु
		err = nokia_modem_gpio_probe(dev);
		अगर (err < 0) अणु
			dev_err(dev, "Could not probe GPIOs\n");
			जाओ error1;
		पूर्ण
	पूर्ण

	ssip.name = "ssi-protocol";
	ssip.tx_cfg = cl->tx_cfg;
	ssip.rx_cfg = cl->rx_cfg;
	ssip.platक्रमm_data = शून्य;
	ssip.archdata = शून्य;

	modem->ssi_protocol = hsi_new_client(port, &ssip);
	अगर (!modem->ssi_protocol) अणु
		dev_err(dev, "Could not register ssi-protocol device\n");
		err = -ENOMEM;
		जाओ error2;
	पूर्ण

	err = device_attach(&modem->ssi_protocol->device);
	अगर (err == 0) अणु
		dev_dbg(dev, "Missing ssi-protocol driver\n");
		err = -EPROBE_DEFER;
		जाओ error3;
	पूर्ण अन्यथा अगर (err < 0) अणु
		dev_err(dev, "Could not load ssi-protocol driver (%d)\n", err);
		जाओ error3;
	पूर्ण

	cmtspeech.name = "cmt-speech";
	cmtspeech.tx_cfg = cl->tx_cfg;
	cmtspeech.rx_cfg = cl->rx_cfg;
	cmtspeech.platक्रमm_data = शून्य;
	cmtspeech.archdata = शून्य;

	modem->cmt_speech = hsi_new_client(port, &cmtspeech);
	अगर (!modem->cmt_speech) अणु
		dev_err(dev, "Could not register cmt-speech device\n");
		err = -ENOMEM;
		जाओ error3;
	पूर्ण

	err = device_attach(&modem->cmt_speech->device);
	अगर (err == 0) अणु
		dev_dbg(dev, "Missing cmt-speech driver\n");
		err = -EPROBE_DEFER;
		जाओ error4;
	पूर्ण अन्यथा अगर (err < 0) अणु
		dev_err(dev, "Could not load cmt-speech driver (%d)\n", err);
		जाओ error4;
	पूर्ण

	dev_info(dev, "Registered Nokia HSI modem\n");

	वापस 0;

error4:
	hsi_हटाओ_client(&modem->cmt_speech->device, शून्य);
error3:
	hsi_हटाओ_client(&modem->ssi_protocol->device, शून्य);
error2:
	nokia_modem_gpio_unexport(dev);
error1:
	disable_irq_wake(modem->nokia_modem_rst_ind_irq);
	tasklet_समाप्त(&modem->nokia_modem_rst_ind_tasklet);

	वापस err;
पूर्ण

अटल पूर्णांक nokia_modem_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा nokia_modem_device *modem = dev_get_drvdata(dev);

	अगर (!modem)
		वापस 0;

	अगर (modem->cmt_speech) अणु
		hsi_हटाओ_client(&modem->cmt_speech->device, शून्य);
		modem->cmt_speech = शून्य;
	पूर्ण

	अगर (modem->ssi_protocol) अणु
		hsi_हटाओ_client(&modem->ssi_protocol->device, शून्य);
		modem->ssi_protocol = शून्य;
	पूर्ण

	nokia_modem_gpio_unexport(dev);
	dev_set_drvdata(dev, शून्य);
	disable_irq_wake(modem->nokia_modem_rst_ind_irq);
	tasklet_समाप्त(&modem->nokia_modem_rst_ind_tasklet);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id nokia_modem_of_match[] = अणु
	अणु .compatible = "nokia,n900-modem", पूर्ण,
	अणु .compatible = "nokia,n950-modem", पूर्ण,
	अणु .compatible = "nokia,n9-modem", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, nokia_modem_of_match);
#पूर्ण_अगर

अटल काष्ठा hsi_client_driver nokia_modem_driver = अणु
	.driver = अणु
		.name	= "nokia-modem",
		.owner	= THIS_MODULE,
		.probe	= nokia_modem_probe,
		.हटाओ	= nokia_modem_हटाओ,
		.of_match_table = of_match_ptr(nokia_modem_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init nokia_modem_init(व्योम)
अणु
	वापस hsi_रेजिस्टर_client_driver(&nokia_modem_driver);
पूर्ण
module_init(nokia_modem_init);

अटल व्योम __निकास nokia_modem_निकास(व्योम)
अणु
	hsi_unरेजिस्टर_client_driver(&nokia_modem_driver);
पूर्ण
module_निकास(nokia_modem_निकास);

MODULE_ALIAS("hsi:nokia-modem");
MODULE_AUTHOR("Sebastian Reichel <sre@kernel.org>");
MODULE_DESCRIPTION("HSI driver module for Nokia N900 Modem");
MODULE_LICENSE("GPL");
