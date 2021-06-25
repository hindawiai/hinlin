<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Serial Port driver क्रम Open Firmware platक्रमm devices
 *
 *    Copyright (C) 2006 Arnd Bergmann <arnd@arndb.de>, IBM Corp.
 */
#समावेश <linux/console.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/clk.h>
#समावेश <linux/reset.h>

#समावेश "8250.h"

काष्ठा of_serial_info अणु
	काष्ठा clk *clk;
	काष्ठा reset_control *rst;
	पूर्णांक type;
	पूर्णांक line;
पूर्ण;

/*
 * Fill a काष्ठा uart_port क्रम a given device node
 */
अटल पूर्णांक of_platक्रमm_serial_setup(काष्ठा platक्रमm_device *ofdev,
			पूर्णांक type, काष्ठा uart_8250_port *up,
			काष्ठा of_serial_info *info)
अणु
	काष्ठा resource resource;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा uart_port *port = &up->port;
	u32 clk, spd, prop;
	पूर्णांक ret, irq;

	स_रखो(port, 0, माप *port);

	pm_runसमय_enable(&ofdev->dev);
	pm_runसमय_get_sync(&ofdev->dev);

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &clk)) अणु

		/* Get clk rate through clk driver अगर present */
		info->clk = devm_clk_get(&ofdev->dev, शून्य);
		अगर (IS_ERR(info->clk)) अणु
			ret = PTR_ERR(info->clk);
			अगर (ret != -EPROBE_DEFER)
				dev_warn(&ofdev->dev,
					 "failed to get clock: %d\n", ret);
			जाओ err_pmrunसमय;
		पूर्ण

		ret = clk_prepare_enable(info->clk);
		अगर (ret < 0)
			जाओ err_pmrunसमय;

		clk = clk_get_rate(info->clk);
	पूर्ण
	/* If current-speed was set, then try not to change it. */
	अगर (of_property_पढ़ो_u32(np, "current-speed", &spd) == 0)
		port->custom_भागisor = clk / (16 * spd);

	ret = of_address_to_resource(np, 0, &resource);
	अगर (ret) अणु
		dev_warn(&ofdev->dev, "invalid address\n");
		जाओ err_unprepare;
	पूर्ण

	port->flags = UPF_SHARE_IRQ | UPF_BOOT_AUTOCONF | UPF_FIXED_PORT |
				  UPF_FIXED_TYPE;
	spin_lock_init(&port->lock);

	अगर (resource_type(&resource) == IORESOURCE_IO) अणु
		port->iotype = UPIO_PORT;
		port->iobase = resource.start;
	पूर्ण अन्यथा अणु
		port->mapbase = resource.start;
		port->mapsize = resource_size(&resource);

		/* Check क्रम shअगरted address mapping */
		अगर (of_property_पढ़ो_u32(np, "reg-offset", &prop) == 0)
			port->mapbase += prop;

		port->iotype = UPIO_MEM;
		अगर (of_property_पढ़ो_u32(np, "reg-io-width", &prop) == 0) अणु
			चयन (prop) अणु
			हाल 1:
				port->iotype = UPIO_MEM;
				अवरोध;
			हाल 2:
				port->iotype = UPIO_MEM16;
				अवरोध;
			हाल 4:
				port->iotype = of_device_is_big_endian(np) ?
					       UPIO_MEM32BE : UPIO_MEM32;
				अवरोध;
			शेष:
				dev_warn(&ofdev->dev, "unsupported reg-io-width (%d)\n",
					 prop);
				ret = -EINVAL;
				जाओ err_unprepare;
			पूर्ण
		पूर्ण
		port->flags |= UPF_IOREMAP;
	पूर्ण

	/* Compatibility with the deprecated pxa driver and 8250_pxa drivers. */
	अगर (of_device_is_compatible(np, "mrvl,mmp-uart"))
		port->regshअगरt = 2;

	/* Check क्रम रेजिस्टरs offset within the devices address range */
	अगर (of_property_पढ़ो_u32(np, "reg-shift", &prop) == 0)
		port->regshअगरt = prop;

	/* Check क्रम fअगरo size */
	अगर (of_property_पढ़ो_u32(np, "fifo-size", &prop) == 0)
		port->fअगरosize = prop;

	/* Check क्रम a fixed line number */
	ret = of_alias_get_id(np, "serial");
	अगर (ret >= 0)
		port->line = ret;

	irq = of_irq_get(np, 0);
	अगर (irq < 0) अणु
		अगर (irq == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ err_unprepare;
		पूर्ण
		/* IRQ support not mandatory */
		irq = 0;
	पूर्ण

	port->irq = irq;

	info->rst = devm_reset_control_get_optional_shared(&ofdev->dev, शून्य);
	अगर (IS_ERR(info->rst)) अणु
		ret = PTR_ERR(info->rst);
		जाओ err_unprepare;
	पूर्ण

	ret = reset_control_deनिश्चित(info->rst);
	अगर (ret)
		जाओ err_unprepare;

	port->type = type;
	port->uartclk = clk;

	अगर (of_property_पढ़ो_bool(np, "no-loopback-test"))
		port->flags |= UPF_SKIP_TEST;

	port->dev = &ofdev->dev;
	port->rs485_config = serial8250_em485_config;
	up->rs485_start_tx = serial8250_em485_start_tx;
	up->rs485_stop_tx = serial8250_em485_stop_tx;

	चयन (type) अणु
	हाल PORT_RT2880:
		port->iotype = UPIO_AU;
		अवरोध;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_SERIAL_8250_FSL) &&
	    (of_device_is_compatible(np, "fsl,ns16550") ||
	     of_device_is_compatible(np, "fsl,16550-FIFO64"))) अणु
		port->handle_irq = fsl8250_handle_irq;
		port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_8250_CONSOLE);
	पूर्ण

	वापस 0;
err_unprepare:
	clk_disable_unprepare(info->clk);
err_pmrunसमय:
	pm_runसमय_put_sync(&ofdev->dev);
	pm_runसमय_disable(&ofdev->dev);
	वापस ret;
पूर्ण

/*
 * Try to रेजिस्टर a serial port
 */
अटल पूर्णांक of_platक्रमm_serial_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा of_serial_info *info;
	काष्ठा uart_8250_port port8250;
	अचिन्हित पूर्णांक port_type;
	u32 tx_threshold;
	पूर्णांक ret;

	port_type = (अचिन्हित दीर्घ)of_device_get_match_data(&ofdev->dev);
	अगर (port_type == PORT_UNKNOWN)
		वापस -EINVAL;

	अगर (of_property_पढ़ो_bool(ofdev->dev.of_node, "used-by-rtas"))
		वापस -EBUSY;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (info == शून्य)
		वापस -ENOMEM;

	स_रखो(&port8250, 0, माप(port8250));
	ret = of_platक्रमm_serial_setup(ofdev, port_type, &port8250, info);
	अगर (ret)
		जाओ err_मुक्त;

	अगर (port8250.port.fअगरosize)
		port8250.capabilities = UART_CAP_FIFO;

	/* Check क्रम TX FIFO threshold & set tx_loadsz */
	अगर ((of_property_पढ़ो_u32(ofdev->dev.of_node, "tx-threshold",
				  &tx_threshold) == 0) &&
	    (tx_threshold < port8250.port.fअगरosize))
		port8250.tx_loadsz = port8250.port.fअगरosize - tx_threshold;

	अगर (of_property_पढ़ो_bool(ofdev->dev.of_node, "auto-flow-control"))
		port8250.capabilities |= UART_CAP_AFE;

	अगर (of_property_पढ़ो_u32(ofdev->dev.of_node,
			"overrun-throttle-ms",
			&port8250.overrun_backoff_समय_ms) != 0)
		port8250.overrun_backoff_समय_ms = 0;

	ret = serial8250_रेजिस्टर_8250_port(&port8250);
	अगर (ret < 0)
		जाओ err_dispose;

	info->type = port_type;
	info->line = ret;
	platक्रमm_set_drvdata(ofdev, info);
	वापस 0;
err_dispose:
	irq_dispose_mapping(port8250.port.irq);
	pm_runसमय_put_sync(&ofdev->dev);
	pm_runसमय_disable(&ofdev->dev);
	clk_disable_unprepare(info->clk);
err_मुक्त:
	kमुक्त(info);
	वापस ret;
पूर्ण

/*
 * Release a line
 */
अटल पूर्णांक of_platक्रमm_serial_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा of_serial_info *info = platक्रमm_get_drvdata(ofdev);

	serial8250_unरेजिस्टर_port(info->line);

	reset_control_निश्चित(info->rst);
	pm_runसमय_put_sync(&ofdev->dev);
	pm_runसमय_disable(&ofdev->dev);
	clk_disable_unprepare(info->clk);
	kमुक्त(info);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक of_serial_suspend(काष्ठा device *dev)
अणु
	काष्ठा of_serial_info *info = dev_get_drvdata(dev);
	काष्ठा uart_8250_port *port8250 = serial8250_get_port(info->line);
	काष्ठा uart_port *port = &port8250->port;

	serial8250_suspend_port(info->line);

	अगर (!uart_console(port) || console_suspend_enabled) अणु
		pm_runसमय_put_sync(dev);
		clk_disable_unprepare(info->clk);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक of_serial_resume(काष्ठा device *dev)
अणु
	काष्ठा of_serial_info *info = dev_get_drvdata(dev);
	काष्ठा uart_8250_port *port8250 = serial8250_get_port(info->line);
	काष्ठा uart_port *port = &port8250->port;

	अगर (!uart_console(port) || console_suspend_enabled) अणु
		pm_runसमय_get_sync(dev);
		clk_prepare_enable(info->clk);
	पूर्ण

	serial8250_resume_port(info->line);

	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(of_serial_pm_ops, of_serial_suspend, of_serial_resume);

/*
 * A few common types, add more as needed.
 */
अटल स्थिर काष्ठा of_device_id of_platक्रमm_serial_table[] = अणु
	अणु .compatible = "ns8250",   .data = (व्योम *)PORT_8250, पूर्ण,
	अणु .compatible = "ns16450",  .data = (व्योम *)PORT_16450, पूर्ण,
	अणु .compatible = "ns16550a", .data = (व्योम *)PORT_16550A, पूर्ण,
	अणु .compatible = "ns16550",  .data = (व्योम *)PORT_16550, पूर्ण,
	अणु .compatible = "ns16750",  .data = (व्योम *)PORT_16750, पूर्ण,
	अणु .compatible = "ns16850",  .data = (व्योम *)PORT_16850, पूर्ण,
	अणु .compatible = "nxp,lpc3220-uart", .data = (व्योम *)PORT_LPC3220, पूर्ण,
	अणु .compatible = "ralink,rt2880-uart", .data = (व्योम *)PORT_RT2880, पूर्ण,
	अणु .compatible = "intel,xscale-uart", .data = (व्योम *)PORT_XSCALE, पूर्ण,
	अणु .compatible = "altr,16550-FIFO32",
		.data = (व्योम *)PORT_ALTR_16550_F32, पूर्ण,
	अणु .compatible = "altr,16550-FIFO64",
		.data = (व्योम *)PORT_ALTR_16550_F64, पूर्ण,
	अणु .compatible = "altr,16550-FIFO128",
		.data = (व्योम *)PORT_ALTR_16550_F128, पूर्ण,
	अणु .compatible = "mediatek,mtk-btif",
		.data = (व्योम *)PORT_MTK_BTIF, पूर्ण,
	अणु .compatible = "mrvl,mmp-uart",
		.data = (व्योम *)PORT_XSCALE, पूर्ण,
	अणु .compatible = "ti,da830-uart", .data = (व्योम *)PORT_DA830, पूर्ण,
	अणु .compatible = "nuvoton,wpcm450-uart", .data = (व्योम *)PORT_NPCM, पूर्ण,
	अणु .compatible = "nuvoton,npcm750-uart", .data = (व्योम *)PORT_NPCM, पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_platक्रमm_serial_table);

अटल काष्ठा platक्रमm_driver of_platक्रमm_serial_driver = अणु
	.driver = अणु
		.name = "of_serial",
		.of_match_table = of_platक्रमm_serial_table,
		.pm = &of_serial_pm_ops,
	पूर्ण,
	.probe = of_platक्रमm_serial_probe,
	.हटाओ = of_platक्रमm_serial_हटाओ,
पूर्ण;

module_platक्रमm_driver(of_platक्रमm_serial_driver);

MODULE_AUTHOR("Arnd Bergmann <arnd@arndb.de>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Serial Port driver for Open Firmware platform devices");
