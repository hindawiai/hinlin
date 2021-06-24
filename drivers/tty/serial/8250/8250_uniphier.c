<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2015 Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "8250.h"

/*
 * This hardware is similar to 8250, but its रेजिस्टर map is a bit dअगरferent:
 *   - MMIO32 (regshअगरt = 2)
 *   - FCR is not at 2, but 3
 *   - LCR and MCR are not at 3 and 4, they share 4
 *   - No SCR (Instead, CHAR can be used as a scratch रेजिस्टर)
 *   - Divisor latch at 9, no भागisor latch access bit
 */

#घोषणा UNIPHIER_UART_REGSHIFT		2

/* bit[15:8] = CHAR, bit[7:0] = FCR */
#घोषणा UNIPHIER_UART_CHAR_FCR		(3 << (UNIPHIER_UART_REGSHIFT))
/* bit[15:8] = LCR, bit[7:0] = MCR */
#घोषणा UNIPHIER_UART_LCR_MCR		(4 << (UNIPHIER_UART_REGSHIFT))
/* Divisor Latch Register */
#घोषणा UNIPHIER_UART_DLR		(9 << (UNIPHIER_UART_REGSHIFT))

काष्ठा uniphier8250_priv अणु
	पूर्णांक line;
	काष्ठा clk *clk;
	spinlock_t atomic_ग_लिखो_lock;
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
अटल पूर्णांक __init uniphier_early_console_setup(काष्ठा earlycon_device *device,
					       स्थिर अक्षर *options)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	/* This hardware always expects MMIO32 रेजिस्टर पूर्णांकerface. */
	device->port.iotype = UPIO_MEM32;
	device->port.regshअगरt = UNIPHIER_UART_REGSHIFT;

	/*
	 * Do not touch the भागisor रेजिस्टर in early_serial8250_setup();
	 * we assume it has been initialized by a boot loader.
	 */
	device->baud = 0;

	वापस early_serial8250_setup(device, options);
पूर्ण
OF_EARLYCON_DECLARE(uniphier, "socionext,uniphier-uart",
		    uniphier_early_console_setup);
#पूर्ण_अगर

/*
 * The रेजिस्टर map is slightly dअगरferent from that of 8250.
 * IO callbacks must be overridden क्रम correct access to FCR, LCR, MCR and SCR.
 */
अटल अचिन्हित पूर्णांक uniphier_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक valshअगरt = 0;

	चयन (offset) अणु
	हाल UART_SCR:
		/* No SCR क्रम this hardware.  Use CHAR as a scratch रेजिस्टर */
		valshअगरt = 8;
		offset = UNIPHIER_UART_CHAR_FCR;
		अवरोध;
	हाल UART_LCR:
		valshअगरt = 8;
		fallthrough;
	हाल UART_MCR:
		offset = UNIPHIER_UART_LCR_MCR;
		अवरोध;
	शेष:
		offset <<= UNIPHIER_UART_REGSHIFT;
		अवरोध;
	पूर्ण

	/*
	 * The वापस value must be masked with 0xff because some रेजिस्टरs
	 * share the same offset that must be accessed by 32-bit ग_लिखो/पढ़ो.
	 * 8 or 16 bit access to this hardware result in unexpected behavior.
	 */
	वापस (पढ़ोl(p->membase + offset) >> valshअगरt) & 0xff;
पूर्ण

अटल व्योम uniphier_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक valshअगरt = 0;
	bool normal = false;

	चयन (offset) अणु
	हाल UART_SCR:
		/* No SCR क्रम this hardware.  Use CHAR as a scratch रेजिस्टर */
		valshअगरt = 8;
		fallthrough;
	हाल UART_FCR:
		offset = UNIPHIER_UART_CHAR_FCR;
		अवरोध;
	हाल UART_LCR:
		valshअगरt = 8;
		/* Divisor latch access bit करोes not exist. */
		value &= ~UART_LCR_DLAB;
		fallthrough;
	हाल UART_MCR:
		offset = UNIPHIER_UART_LCR_MCR;
		अवरोध;
	शेष:
		offset <<= UNIPHIER_UART_REGSHIFT;
		normal = true;
		अवरोध;
	पूर्ण

	अगर (normal) अणु
		ग_लिखोl(value, p->membase + offset);
	पूर्ण अन्यथा अणु
		/*
		 * Special हाल: two रेजिस्टरs share the same address that
		 * must be 32-bit accessed.  As this is not दीर्घer atomic safe,
		 * take a lock just in हाल.
		 */
		काष्ठा uniphier8250_priv *priv = p->निजी_data;
		अचिन्हित दीर्घ flags;
		u32 पंचांगp;

		spin_lock_irqsave(&priv->atomic_ग_लिखो_lock, flags);
		पंचांगp = पढ़ोl(p->membase + offset);
		पंचांगp &= ~(0xff << valshअगरt);
		पंचांगp |= value << valshअगरt;
		ग_लिखोl(पंचांगp, p->membase + offset);
		spin_unlock_irqrestore(&priv->atomic_ग_लिखो_lock, flags);
	पूर्ण
पूर्ण

/*
 * This hardware करोes not have the भागisor latch access bit.
 * The भागisor latch रेजिस्टर exists at dअगरferent address.
 * Override dl_पढ़ो/ग_लिखो callbacks.
 */
अटल पूर्णांक uniphier_serial_dl_पढ़ो(काष्ठा uart_8250_port *up)
अणु
	वापस पढ़ोl(up->port.membase + UNIPHIER_UART_DLR);
पूर्ण

अटल व्योम uniphier_serial_dl_ग_लिखो(काष्ठा uart_8250_port *up, पूर्णांक value)
अणु
	ग_लिखोl(value, up->port.membase + UNIPHIER_UART_DLR);
पूर्ण

अटल पूर्णांक uniphier_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uart_8250_port up;
	काष्ठा uniphier8250_priv *priv;
	काष्ठा resource *regs;
	व्योम __iomem *membase;
	पूर्णांक irq;
	पूर्णांक ret;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs) अणु
		dev_err(dev, "failed to get memory resource\n");
		वापस -EINVAL;
	पूर्ण

	membase = devm_ioremap(dev, regs->start, resource_size(regs));
	अगर (!membase)
		वापस -ENOMEM;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	स_रखो(&up, 0, माप(up));

	ret = of_alias_get_id(dev->of_node, "serial");
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get alias id\n");
		वापस ret;
	पूर्ण
	up.port.line = ret;

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to get clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	up.port.uartclk = clk_get_rate(priv->clk);

	spin_lock_init(&priv->atomic_ग_लिखो_lock);

	up.port.dev = dev;
	up.port.निजी_data = priv;
	up.port.mapbase = regs->start;
	up.port.mapsize = resource_size(regs);
	up.port.membase = membase;
	up.port.irq = irq;

	up.port.type = PORT_16550A;
	up.port.iotype = UPIO_MEM32;
	up.port.fअगरosize = 64;
	up.port.regshअगरt = UNIPHIER_UART_REGSHIFT;
	up.port.flags = UPF_FIXED_PORT | UPF_FIXED_TYPE;
	up.capabilities = UART_CAP_FIFO;

	अगर (of_property_पढ़ो_bool(dev->of_node, "auto-flow-control"))
		up.capabilities |= UART_CAP_AFE;

	up.port.serial_in = uniphier_serial_in;
	up.port.serial_out = uniphier_serial_out;
	up.dl_पढ़ो = uniphier_serial_dl_पढ़ो;
	up.dl_ग_लिखो = uniphier_serial_dl_ग_लिखो;

	ret = serial8250_रेजिस्टर_8250_port(&up);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register 8250 port\n");
		clk_disable_unprepare(priv->clk);
		वापस ret;
	पूर्ण
	priv->line = ret;

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier8250_priv *priv = platक्रमm_get_drvdata(pdev);

	serial8250_unरेजिस्टर_port(priv->line);
	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused uniphier_uart_suspend(काष्ठा device *dev)
अणु
	काष्ठा uniphier8250_priv *priv = dev_get_drvdata(dev);
	काष्ठा uart_8250_port *up = serial8250_get_port(priv->line);

	serial8250_suspend_port(priv->line);

	अगर (!uart_console(&up->port) || console_suspend_enabled)
		clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused uniphier_uart_resume(काष्ठा device *dev)
अणु
	काष्ठा uniphier8250_priv *priv = dev_get_drvdata(dev);
	काष्ठा uart_8250_port *up = serial8250_get_port(priv->line);
	पूर्णांक ret;

	अगर (!uart_console(&up->port) || console_suspend_enabled) अणु
		ret = clk_prepare_enable(priv->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	serial8250_resume_port(priv->line);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops uniphier_uart_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(uniphier_uart_suspend, uniphier_uart_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_uart_match[] = अणु
	अणु .compatible = "socionext,uniphier-uart" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_uart_match);

अटल काष्ठा platक्रमm_driver uniphier_uart_platक्रमm_driver = अणु
	.probe		= uniphier_uart_probe,
	.हटाओ		= uniphier_uart_हटाओ,
	.driver = अणु
		.name	= "uniphier-uart",
		.of_match_table = uniphier_uart_match,
		.pm = &uniphier_uart_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_uart_platक्रमm_driver);

MODULE_AUTHOR("Masahiro Yamada <yamada.masahiro@socionext.com>");
MODULE_DESCRIPTION("UniPhier UART driver");
MODULE_LICENSE("GPL");
