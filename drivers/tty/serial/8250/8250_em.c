<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas Emma Mobile 8250 driver
 *
 *  Copyright (C) 2012 Magnus Damm
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>

#समावेश "8250.h"

#घोषणा UART_DLL_EM 9
#घोषणा UART_DLM_EM 10

काष्ठा serial8250_em_priv अणु
	काष्ठा clk *sclk;
	पूर्णांक line;
पूर्ण;

अटल व्योम serial8250_em_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	चयन (offset) अणु
	हाल UART_TX: /* TX @ 0x00 */
		ग_लिखोb(value, p->membase);
		अवरोध;
	हाल UART_FCR: /* FCR @ 0x0c (+1) */
	हाल UART_LCR: /* LCR @ 0x10 (+1) */
	हाल UART_MCR: /* MCR @ 0x14 (+1) */
	हाल UART_SCR: /* SCR @ 0x20 (+1) */
		ग_लिखोl(value, p->membase + ((offset + 1) << 2));
		अवरोध;
	हाल UART_IER: /* IER @ 0x04 */
		value &= 0x0f; /* only 4 valid bits - not Xscale */
		fallthrough;
	हाल UART_DLL_EM: /* DLL @ 0x24 (+9) */
	हाल UART_DLM_EM: /* DLM @ 0x28 (+9) */
		ग_लिखोl(value, p->membase + (offset << 2));
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक serial8250_em_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	चयन (offset) अणु
	हाल UART_RX: /* RX @ 0x00 */
		वापस पढ़ोb(p->membase);
	हाल UART_MCR: /* MCR @ 0x14 (+1) */
	हाल UART_LSR: /* LSR @ 0x18 (+1) */
	हाल UART_MSR: /* MSR @ 0x1c (+1) */
	हाल UART_SCR: /* SCR @ 0x20 (+1) */
		वापस पढ़ोl(p->membase + ((offset + 1) << 2));
	हाल UART_IER: /* IER @ 0x04 */
	हाल UART_IIR: /* IIR @ 0x08 */
	हाल UART_DLL_EM: /* DLL @ 0x24 (+9) */
	हाल UART_DLM_EM: /* DLM @ 0x28 (+9) */
		वापस पढ़ोl(p->membase + (offset << 2));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक serial8250_em_serial_dl_पढ़ो(काष्ठा uart_8250_port *up)
अणु
	वापस serial_in(up, UART_DLL_EM) | serial_in(up, UART_DLM_EM) << 8;
पूर्ण

अटल व्योम serial8250_em_serial_dl_ग_लिखो(काष्ठा uart_8250_port *up, पूर्णांक value)
अणु
	serial_out(up, UART_DLL_EM, value & 0xff);
	serial_out(up, UART_DLM_EM, value >> 8 & 0xff);
पूर्ण

अटल पूर्णांक serial8250_em_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा serial8250_em_priv *priv;
	काष्ठा uart_8250_port up;
	काष्ठा resource *regs;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs) अणु
		dev_err(&pdev->dev, "missing registers\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->sclk = devm_clk_get(&pdev->dev, "sclk");
	अगर (IS_ERR(priv->sclk)) अणु
		dev_err(&pdev->dev, "unable to get clock\n");
		वापस PTR_ERR(priv->sclk);
	पूर्ण

	स_रखो(&up, 0, माप(up));
	up.port.mapbase = regs->start;
	up.port.irq = irq;
	up.port.type = PORT_UNKNOWN;
	up.port.flags = UPF_BOOT_AUTOCONF | UPF_FIXED_PORT | UPF_IOREMAP;
	up.port.dev = &pdev->dev;
	up.port.निजी_data = priv;

	clk_prepare_enable(priv->sclk);
	up.port.uartclk = clk_get_rate(priv->sclk);

	up.port.iotype = UPIO_MEM32;
	up.port.serial_in = serial8250_em_serial_in;
	up.port.serial_out = serial8250_em_serial_out;
	up.dl_पढ़ो = serial8250_em_serial_dl_पढ़ो;
	up.dl_ग_लिखो = serial8250_em_serial_dl_ग_लिखो;

	ret = serial8250_रेजिस्टर_8250_port(&up);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "unable to register 8250 port\n");
		clk_disable_unprepare(priv->sclk);
		वापस ret;
	पूर्ण

	priv->line = ret;
	platक्रमm_set_drvdata(pdev, priv);
	वापस 0;
पूर्ण

अटल पूर्णांक serial8250_em_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा serial8250_em_priv *priv = platक्रमm_get_drvdata(pdev);

	serial8250_unरेजिस्टर_port(priv->line);
	clk_disable_unprepare(priv->sclk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id serial8250_em_dt_ids[] = अणु
	अणु .compatible = "renesas,em-uart", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, serial8250_em_dt_ids);

अटल काष्ठा platक्रमm_driver serial8250_em_platक्रमm_driver = अणु
	.driver = अणु
		.name		= "serial8250-em",
		.of_match_table = serial8250_em_dt_ids,
	पूर्ण,
	.probe			= serial8250_em_probe,
	.हटाओ			= serial8250_em_हटाओ,
पूर्ण;

module_platक्रमm_driver(serial8250_em_platक्रमm_driver);

MODULE_AUTHOR("Magnus Damm");
MODULE_DESCRIPTION("Renesas Emma Mobile 8250 Driver");
MODULE_LICENSE("GPL v2");
