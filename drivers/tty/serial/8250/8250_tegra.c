<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Serial Port driver क्रम Tegra devices
 *
 *  Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#समावेश "8250.h"

काष्ठा tegra_uart अणु
	काष्ठा clk *clk;
	काष्ठा reset_control *rst;
	पूर्णांक line;
पूर्ण;

अटल व्योम tegra_uart_handle_अवरोध(काष्ठा uart_port *p)
अणु
	अचिन्हित पूर्णांक status, पंचांगout = 10000;

	जबतक (1) अणु
		status = p->serial_in(p, UART_LSR);
		अगर (!(status & (UART_LSR_FIFOE | UART_LSR_BRK_ERROR_BITS)))
			अवरोध;

		p->serial_in(p, UART_RX);

		अगर (--पंचांगout == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_8250_port port8250;
	काष्ठा tegra_uart *uart;
	काष्ठा uart_port *port;
	काष्ठा resource *res;
	पूर्णांक ret;

	uart = devm_kzalloc(&pdev->dev, माप(*uart), GFP_KERNEL);
	अगर (!uart)
		वापस -ENOMEM;

	स_रखो(&port8250, 0, माप(port8250));

	port = &port8250.port;
	spin_lock_init(&port->lock);

	port->flags = UPF_SHARE_IRQ | UPF_BOOT_AUTOCONF | UPF_FIXED_PORT |
		      UPF_FIXED_TYPE;
	port->iotype = UPIO_MEM32;
	port->regshअगरt = 2;
	port->type = PORT_TEGRA;
	port->irqflags |= IRQF_SHARED;
	port->dev = &pdev->dev;
	port->handle_अवरोध = tegra_uart_handle_अवरोध;

	ret = of_alias_get_id(pdev->dev.of_node, "serial");
	अगर (ret >= 0)
		port->line = ret;

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;

	port->irq = ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	port->membase = devm_ioremap(&pdev->dev, res->start,
				     resource_size(res));
	अगर (!port->membase)
		वापस -ENOMEM;

	port->mapbase = res->start;
	port->mapsize = resource_size(res);

	uart->rst = devm_reset_control_get_optional_shared(&pdev->dev, शून्य);
	अगर (IS_ERR(uart->rst))
		वापस PTR_ERR(uart->rst);

	अगर (device_property_पढ़ो_u32(&pdev->dev, "clock-frequency",
				     &port->uartclk)) अणु
		uart->clk = devm_clk_get(&pdev->dev, शून्य);
		अगर (IS_ERR(uart->clk)) अणु
			dev_err(&pdev->dev, "failed to get clock!\n");
			वापस -ENODEV;
		पूर्ण

		ret = clk_prepare_enable(uart->clk);
		अगर (ret < 0)
			वापस ret;

		port->uartclk = clk_get_rate(uart->clk);
	पूर्ण

	ret = reset_control_deनिश्चित(uart->rst);
	अगर (ret)
		जाओ err_clkdisable;

	ret = serial8250_रेजिस्टर_8250_port(&port8250);
	अगर (ret < 0)
		जाओ err_clkdisable;

	platक्रमm_set_drvdata(pdev, uart);
	uart->line = ret;

	वापस 0;

err_clkdisable:
	clk_disable_unprepare(uart->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_uart *uart = platक्रमm_get_drvdata(pdev);

	serial8250_unरेजिस्टर_port(uart->line);
	reset_control_निश्चित(uart->rst);
	clk_disable_unprepare(uart->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tegra_uart_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_uart *uart = dev_get_drvdata(dev);
	काष्ठा uart_8250_port *port8250 = serial8250_get_port(uart->line);
	काष्ठा uart_port *port = &port8250->port;

	serial8250_suspend_port(uart->line);

	अगर (!uart_console(port) || console_suspend_enabled)
		clk_disable_unprepare(uart->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_uart_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_uart *uart = dev_get_drvdata(dev);
	काष्ठा uart_8250_port *port8250 = serial8250_get_port(uart->line);
	काष्ठा uart_port *port = &port8250->port;

	अगर (!uart_console(port) || console_suspend_enabled)
		clk_prepare_enable(uart->clk);

	serial8250_resume_port(uart->line);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tegra_uart_pm_ops, tegra_uart_suspend,
			 tegra_uart_resume);

अटल स्थिर काष्ठा of_device_id tegra_uart_of_match[] = अणु
	अणु .compatible = "nvidia,tegra20-uart", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_uart_of_match);

अटल स्थिर काष्ठा acpi_device_id tegra_uart_acpi_match[] = अणु
	अणु "NVDA0100", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, tegra_uart_acpi_match);

अटल काष्ठा platक्रमm_driver tegra_uart_driver = अणु
	.driver = अणु
		.name = "tegra-uart",
		.pm = &tegra_uart_pm_ops,
		.of_match_table = tegra_uart_of_match,
		.acpi_match_table = ACPI_PTR(tegra_uart_acpi_match),
	पूर्ण,
	.probe = tegra_uart_probe,
	.हटाओ = tegra_uart_हटाओ,
पूर्ण;

module_platक्रमm_driver(tegra_uart_driver);

MODULE_AUTHOR("Jeff Brasen <jbrasen@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra 8250 Driver");
MODULE_LICENSE("GPL v2");
