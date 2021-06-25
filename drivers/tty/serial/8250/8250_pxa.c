<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  drivers/tty/serial/8250/8250_pxa.c -- driver क्रम PXA on-board UARTS
 *  Copyright:	(C) 2013 Sergei Ianovich <ynvich@gmail.com>
 *
 *  replaces drivers/serial/pxa.c by Nicolas Pitre
 *  Created:	Feb 20, 2003
 *  Copyright:	(C) 2003 Monta Vista Software, Inc.
 *
 *  Based on drivers/serial/8250.c by Russell King.
 */

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "8250.h"

काष्ठा pxa8250_data अणु
	पूर्णांक			line;
	काष्ठा clk		*clk;
पूर्ण;

अटल पूर्णांक __maybe_unused serial_pxa_suspend(काष्ठा device *dev)
अणु
	काष्ठा pxa8250_data *data = dev_get_drvdata(dev);

	serial8250_suspend_port(data->line);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused serial_pxa_resume(काष्ठा device *dev)
अणु
	काष्ठा pxa8250_data *data = dev_get_drvdata(dev);

	serial8250_resume_port(data->line);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops serial_pxa_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(serial_pxa_suspend, serial_pxa_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id serial_pxa_dt_ids[] = अणु
	अणु .compatible = "mrvl,pxa-uart", पूर्ण,
	अणु .compatible = "mrvl,mmp-uart", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, serial_pxa_dt_ids);

/* Uart भागisor latch ग_लिखो */
अटल व्योम serial_pxa_dl_ग_लिखो(काष्ठा uart_8250_port *up, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक dll;

	serial_out(up, UART_DLL, value & 0xff);
	/*
	 * work around Erratum #74 according to Marvel(R) PXA270M Processor
	 * Specअगरication Update (April 19, 2010)
	 */
	dll = serial_in(up, UART_DLL);
	WARN_ON(dll != (value & 0xff));

	serial_out(up, UART_DLM, value >> 8 & 0xff);
पूर्ण


अटल व्योम serial_pxa_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
	      अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा pxa8250_data *data = port->निजी_data;

	अगर (!state)
		clk_prepare_enable(data->clk);
	अन्यथा
		clk_disable_unprepare(data->clk);
पूर्ण

अटल पूर्णांक serial_pxa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_8250_port uart = अणुपूर्ण;
	काष्ठा pxa8250_data *data;
	काष्ठा resource *mmres;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	mmres = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mmres)
		वापस -ENODEV;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(data->clk))
		वापस PTR_ERR(data->clk);

	ret = clk_prepare(data->clk);
	अगर (ret)
		वापस ret;

	ret = of_alias_get_id(pdev->dev.of_node, "serial");
	अगर (ret >= 0)
		uart.port.line = ret;

	uart.port.type = PORT_XSCALE;
	uart.port.iotype = UPIO_MEM32;
	uart.port.mapbase = mmres->start;
	uart.port.regshअगरt = 2;
	uart.port.irq = irq;
	uart.port.fअगरosize = 64;
	uart.port.flags = UPF_IOREMAP | UPF_SKIP_TEST | UPF_FIXED_TYPE;
	uart.port.dev = &pdev->dev;
	uart.port.uartclk = clk_get_rate(data->clk);
	uart.port.pm = serial_pxa_pm;
	uart.port.निजी_data = data;
	uart.dl_ग_लिखो = serial_pxa_dl_ग_लिखो;

	ret = serial8250_रेजिस्टर_8250_port(&uart);
	अगर (ret < 0)
		जाओ err_clk;

	data->line = ret;

	platक्रमm_set_drvdata(pdev, data);

	वापस 0;

 err_clk:
	clk_unprepare(data->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक serial_pxa_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa8250_data *data = platक्रमm_get_drvdata(pdev);

	serial8250_unरेजिस्टर_port(data->line);

	clk_unprepare(data->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver serial_pxa_driver = अणु
	.probe          = serial_pxa_probe,
	.हटाओ         = serial_pxa_हटाओ,

	.driver		= अणु
		.name	= "pxa2xx-uart",
		.pm	= &serial_pxa_pm_ops,
		.of_match_table = serial_pxa_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(serial_pxa_driver);

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
अटल पूर्णांक __init early_serial_pxa_setup(काष्ठा earlycon_device *device,
				  स्थिर अक्षर *options)
अणु
	काष्ठा uart_port *port = &device->port;

	अगर (!(device->port.membase || device->port.iobase))
		वापस -ENODEV;

	port->regshअगरt = 2;
	वापस early_serial8250_setup(device, शून्य);
पूर्ण
OF_EARLYCON_DECLARE(early_pxa, "mrvl,pxa-uart", early_serial_pxa_setup);
#पूर्ण_अगर

MODULE_AUTHOR("Sergei Ianovich");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa2xx-uart");
