<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SGI IOC3 8250 UART driver
 *
 * Copyright (C) 2019 Thomas Bogenकरोerfer <tbogenकरोerfer@suse.de>
 *
 * based on code Copyright (C) 2005 Stanislaw Skowronek <skylark@unaligned.org>
 *               Copyright (C) 2014 Joshua Kinard <kumba@gentoo.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश "8250.h"

#घोषणा IOC3_UARTCLK (22000000 / 3)

काष्ठा ioc3_8250_data अणु
	पूर्णांक line;
पूर्ण;

अटल अचिन्हित पूर्णांक ioc3_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	वापस पढ़ोb(p->membase + (offset ^ 3));
पूर्ण

अटल व्योम ioc3_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	ग_लिखोb(value, p->membase + (offset ^ 3));
पूर्ण

अटल पूर्णांक serial8250_ioc3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ioc3_8250_data *data;
	काष्ठा uart_8250_port up;
	काष्ठा resource *r;
	व्योम __iomem *membase;
	पूर्णांक irq, line;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r)
		वापस -ENODEV;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	membase = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (!membase)
		वापस -ENOMEM;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		irq = 0; /* no पूर्णांकerrupt -> use polling */

	/* Register serial ports with 8250.c */
	स_रखो(&up, 0, माप(काष्ठा uart_8250_port));
	up.port.iotype = UPIO_MEM;
	up.port.uartclk = IOC3_UARTCLK;
	up.port.type = PORT_16550A;
	up.port.irq = irq;
	up.port.flags = (UPF_BOOT_AUTOCONF | UPF_SHARE_IRQ);
	up.port.dev = &pdev->dev;
	up.port.membase = membase;
	up.port.mapbase = r->start;
	up.port.serial_in = ioc3_serial_in;
	up.port.serial_out = ioc3_serial_out;
	line = serial8250_रेजिस्टर_8250_port(&up);
	अगर (line < 0)
		वापस line;

	platक्रमm_set_drvdata(pdev, data);
	वापस 0;
पूर्ण

अटल पूर्णांक serial8250_ioc3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ioc3_8250_data *data = platक्रमm_get_drvdata(pdev);

	serial8250_unरेजिस्टर_port(data->line);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver serial8250_ioc3_driver = अणु
	.probe  = serial8250_ioc3_probe,
	.हटाओ = serial8250_ioc3_हटाओ,
	.driver = अणु
		.name = "ioc3-serial8250",
	पूर्ण
पूर्ण;

module_platक्रमm_driver(serial8250_ioc3_driver);

MODULE_AUTHOR("Thomas Bogendoerfer <tbogendoerfer@suse.de>");
MODULE_DESCRIPTION("SGI IOC3 8250 UART driver");
MODULE_LICENSE("GPL");
