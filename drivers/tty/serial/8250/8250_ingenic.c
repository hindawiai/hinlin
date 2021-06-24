<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2010 Lars-Peter Clausen <lars@metafoo.de>
 * Copyright (C) 2015 Imagination Technologies
 *
 * Ingenic SoC UART support
 */

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/पन.स>
#समावेश <linux/libfdt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>

#समावेश "8250.h"

/** ingenic_uart_config: SOC specअगरic config data. */
काष्ठा ingenic_uart_config अणु
	पूर्णांक tx_loadsz;
	पूर्णांक fअगरosize;
पूर्ण;

काष्ठा ingenic_uart_data अणु
	काष्ठा clk	*clk_module;
	काष्ठा clk	*clk_baud;
	पूर्णांक		line;
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match[];

#घोषणा UART_FCR_UME	BIT(4)

#घोषणा UART_MCR_MDCE	BIT(7)
#घोषणा UART_MCR_FCM	BIT(6)

अटल काष्ठा earlycon_device *early_device;

अटल uपूर्णांक8_t early_in(काष्ठा uart_port *port, पूर्णांक offset)
अणु
	वापस पढ़ोl(port->membase + (offset << 2));
पूर्ण

अटल व्योम early_out(काष्ठा uart_port *port, पूर्णांक offset, uपूर्णांक8_t value)
अणु
	ग_लिखोl(value, port->membase + (offset << 2));
पूर्ण

अटल व्योम ingenic_early_console_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	uपूर्णांक8_t lsr;

	करो अणु
		lsr = early_in(port, UART_LSR);
	पूर्ण जबतक ((lsr & UART_LSR_TEMT) == 0);

	early_out(port, UART_TX, c);
पूर्ण

अटल व्योम ingenic_early_console_ग_लिखो(काष्ठा console *console,
					      स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	uart_console_ग_लिखो(&early_device->port, s, count,
			   ingenic_early_console_अ_दो);
पूर्ण

अटल व्योम __init ingenic_early_console_setup_घड़ी(काष्ठा earlycon_device *dev)
अणु
	व्योम *fdt = initial_boot_params;
	स्थिर __be32 *prop;
	पूर्णांक offset;

	offset = fdt_path_offset(fdt, "/ext");
	अगर (offset < 0)
		वापस;

	prop = fdt_getprop(fdt, offset, "clock-frequency", शून्य);
	अगर (!prop)
		वापस;

	dev->port.uartclk = be32_to_cpup(prop);
पूर्ण

अटल पूर्णांक __init ingenic_early_console_setup(काष्ठा earlycon_device *dev,
					      स्थिर अक्षर *opt)
अणु
	काष्ठा uart_port *port = &dev->port;
	अचिन्हित पूर्णांक भागisor;
	पूर्णांक baud = 115200;

	अगर (!dev->port.membase)
		वापस -ENODEV;

	अगर (opt) अणु
		अचिन्हित पूर्णांक parity, bits, flow; /* unused क्रम now */

		uart_parse_options(opt, &baud, &parity, &bits, &flow);
	पूर्ण

	ingenic_early_console_setup_घड़ी(dev);

	अगर (dev->baud)
		baud = dev->baud;
	भागisor = DIV_ROUND_CLOSEST(port->uartclk, 16 * baud);

	early_out(port, UART_IER, 0);
	early_out(port, UART_LCR, UART_LCR_DLAB | UART_LCR_WLEN8);
	early_out(port, UART_DLL, 0);
	early_out(port, UART_DLM, 0);
	early_out(port, UART_LCR, UART_LCR_WLEN8);
	early_out(port, UART_FCR, UART_FCR_UME | UART_FCR_CLEAR_XMIT |
			UART_FCR_CLEAR_RCVR | UART_FCR_ENABLE_FIFO);
	early_out(port, UART_MCR, UART_MCR_RTS | UART_MCR_DTR);

	early_out(port, UART_LCR, UART_LCR_DLAB | UART_LCR_WLEN8);
	early_out(port, UART_DLL, भागisor & 0xff);
	early_out(port, UART_DLM, (भागisor >> 8) & 0xff);
	early_out(port, UART_LCR, UART_LCR_WLEN8);

	early_device = dev;
	dev->con->ग_लिखो = ingenic_early_console_ग_लिखो;

	वापस 0;
पूर्ण

OF_EARLYCON_DECLARE(jz4740_uart, "ingenic,jz4740-uart",
		    ingenic_early_console_setup);

OF_EARLYCON_DECLARE(jz4770_uart, "ingenic,jz4770-uart",
		    ingenic_early_console_setup);

OF_EARLYCON_DECLARE(jz4775_uart, "ingenic,jz4775-uart",
		    ingenic_early_console_setup);

OF_EARLYCON_DECLARE(jz4780_uart, "ingenic,jz4780-uart",
		    ingenic_early_console_setup);

OF_EARLYCON_DECLARE(x1000_uart, "ingenic,x1000-uart",
		    ingenic_early_console_setup);

अटल व्योम ingenic_uart_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	पूर्णांक ier;

	चयन (offset) अणु
	हाल UART_FCR:
		/* UART module enable */
		value |= UART_FCR_UME;
		अवरोध;

	हाल UART_IER:
		/*
		 * Enable receive समयout पूर्णांकerrupt with the receive line
		 * status पूर्णांकerrupt.
		 */
		value |= (value & 0x4) << 2;
		अवरोध;

	हाल UART_MCR:
		/*
		 * If we have enabled modem status IRQs we should enable
		 * modem mode.
		 */
		ier = p->serial_in(p, UART_IER);

		अगर (ier & UART_IER_MSI)
			value |= UART_MCR_MDCE | UART_MCR_FCM;
		अन्यथा
			value &= ~(UART_MCR_MDCE | UART_MCR_FCM);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	ग_लिखोb(value, p->membase + (offset << p->regshअगरt));
पूर्ण

अटल अचिन्हित पूर्णांक ingenic_uart_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक value;

	value = पढ़ोb(p->membase + (offset << p->regshअगरt));

	/* Hide non-16550 compliant bits from higher levels */
	चयन (offset) अणु
	हाल UART_FCR:
		value &= ~UART_FCR_UME;
		अवरोध;

	हाल UART_MCR:
		value &= ~(UART_MCR_MDCE | UART_MCR_FCM);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस value;
पूर्ण

अटल पूर्णांक ingenic_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_8250_port uart = अणुपूर्ण;
	काष्ठा ingenic_uart_data *data;
	स्थिर काष्ठा ingenic_uart_config *cdata;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा resource *regs;
	पूर्णांक irq, err, line;

	match = of_match_device(of_match, &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "Error: No device match found\n");
		वापस -ENODEV;
	पूर्ण
	cdata = match->data;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs) अणु
		dev_err(&pdev->dev, "no registers defined\n");
		वापस -EINVAL;
	पूर्ण

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	spin_lock_init(&uart.port.lock);
	uart.port.type = PORT_16550A;
	uart.port.flags = UPF_SKIP_TEST | UPF_IOREMAP | UPF_FIXED_TYPE;
	uart.port.iotype = UPIO_MEM;
	uart.port.mapbase = regs->start;
	uart.port.regshअगरt = 2;
	uart.port.serial_out = ingenic_uart_serial_out;
	uart.port.serial_in = ingenic_uart_serial_in;
	uart.port.irq = irq;
	uart.port.dev = &pdev->dev;
	uart.port.fअगरosize = cdata->fअगरosize;
	uart.tx_loadsz = cdata->tx_loadsz;
	uart.capabilities = UART_CAP_FIFO | UART_CAP_RTOIE;

	/* Check क्रम a fixed line number */
	line = of_alias_get_id(pdev->dev.of_node, "serial");
	अगर (line >= 0)
		uart.port.line = line;

	uart.port.membase = devm_ioremap(&pdev->dev, regs->start,
					 resource_size(regs));
	अगर (!uart.port.membase)
		वापस -ENOMEM;

	data->clk_module = devm_clk_get(&pdev->dev, "module");
	अगर (IS_ERR(data->clk_module))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(data->clk_module),
				     "unable to get module clock\n");

	data->clk_baud = devm_clk_get(&pdev->dev, "baud");
	अगर (IS_ERR(data->clk_baud))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(data->clk_baud),
				     "unable to get baud clock\n");

	err = clk_prepare_enable(data->clk_module);
	अगर (err) अणु
		dev_err(&pdev->dev, "could not enable module clock: %d\n", err);
		जाओ out;
	पूर्ण

	err = clk_prepare_enable(data->clk_baud);
	अगर (err) अणु
		dev_err(&pdev->dev, "could not enable baud clock: %d\n", err);
		जाओ out_disable_moduleclk;
	पूर्ण
	uart.port.uartclk = clk_get_rate(data->clk_baud);

	data->line = serial8250_रेजिस्टर_8250_port(&uart);
	अगर (data->line < 0) अणु
		err = data->line;
		जाओ out_disable_baudclk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);
	वापस 0;

out_disable_baudclk:
	clk_disable_unprepare(data->clk_baud);
out_disable_moduleclk:
	clk_disable_unprepare(data->clk_module);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ingenic_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ingenic_uart_data *data = platक्रमm_get_drvdata(pdev);

	serial8250_unरेजिस्टर_port(data->line);
	clk_disable_unprepare(data->clk_module);
	clk_disable_unprepare(data->clk_baud);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ingenic_uart_config jz4740_uart_config = अणु
	.tx_loadsz = 8,
	.fअगरosize = 16,
पूर्ण;

अटल स्थिर काष्ठा ingenic_uart_config jz4760_uart_config = अणु
	.tx_loadsz = 16,
	.fअगरosize = 32,
पूर्ण;

अटल स्थिर काष्ठा ingenic_uart_config jz4780_uart_config = अणु
	.tx_loadsz = 32,
	.fअगरosize = 64,
पूर्ण;

अटल स्थिर काष्ठा ingenic_uart_config x1000_uart_config = अणु
	.tx_loadsz = 32,
	.fअगरosize = 64,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match[] = अणु
	अणु .compatible = "ingenic,jz4740-uart", .data = &jz4740_uart_config पूर्ण,
	अणु .compatible = "ingenic,jz4760-uart", .data = &jz4760_uart_config पूर्ण,
	अणु .compatible = "ingenic,jz4770-uart", .data = &jz4760_uart_config पूर्ण,
	अणु .compatible = "ingenic,jz4775-uart", .data = &jz4760_uart_config पूर्ण,
	अणु .compatible = "ingenic,jz4780-uart", .data = &jz4780_uart_config पूर्ण,
	अणु .compatible = "ingenic,x1000-uart", .data = &x1000_uart_config पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_match);

अटल काष्ठा platक्रमm_driver ingenic_uart_platक्रमm_driver = अणु
	.driver = अणु
		.name		= "ingenic-uart",
		.of_match_table	= of_match,
	पूर्ण,
	.probe			= ingenic_uart_probe,
	.हटाओ			= ingenic_uart_हटाओ,
पूर्ण;

module_platक्रमm_driver(ingenic_uart_platक्रमm_driver);

MODULE_AUTHOR("Paul Burton");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Ingenic SoC UART driver");
