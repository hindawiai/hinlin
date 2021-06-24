<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Serial port driver क्रम BCM2835AUX UART
 *
 * Copyright (C) 2016 Martin Sperl <kernel@martin.sperl.org>
 *
 * Based on 8250_lpc18xx.c:
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * The bcm2835aux is capable of RTS स्वतः flow-control, but this driver करोesn't
 * take advantage of it yet.  When adding support, be sure not to enable it
 * simultaneously to rs485.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "8250.h"

#घोषणा BCM2835_AUX_UART_CNTL		8
#घोषणा BCM2835_AUX_UART_CNTL_RXEN	0x01 /* Receiver enable */
#घोषणा BCM2835_AUX_UART_CNTL_TXEN	0x02 /* Transmitter enable */
#घोषणा BCM2835_AUX_UART_CNTL_AUTORTS	0x04 /* RTS set by RX fill level */
#घोषणा BCM2835_AUX_UART_CNTL_AUTOCTS	0x08 /* CTS stops transmitter */
#घोषणा BCM2835_AUX_UART_CNTL_RTS3	0x00 /* RTS set until 3 अक्षरs left */
#घोषणा BCM2835_AUX_UART_CNTL_RTS2	0x10 /* RTS set until 2 अक्षरs left */
#घोषणा BCM2835_AUX_UART_CNTL_RTS1	0x20 /* RTS set until 1 अक्षरs left */
#घोषणा BCM2835_AUX_UART_CNTL_RTS4	0x30 /* RTS set until 4 अक्षरs left */
#घोषणा BCM2835_AUX_UART_CNTL_RTSINV	0x40 /* Invert स्वतः RTS polarity */
#घोषणा BCM2835_AUX_UART_CNTL_CTSINV	0x80 /* Invert स्वतः CTS polarity */

/**
 * काष्ठा bcm2835aux_data - driver निजी data of BCM2835 auxiliary UART
 * @clk: घड़ी producer of the port's uartclk
 * @line: index of the port's serial8250_ports[] entry
 * @cntl: cached copy of CNTL रेजिस्टर
 */
काष्ठा bcm2835aux_data अणु
	काष्ठा clk *clk;
	पूर्णांक line;
	u32 cntl;
पूर्ण;

अटल व्योम bcm2835aux_rs485_start_tx(काष्ठा uart_8250_port *up)
अणु
	अगर (!(up->port.rs485.flags & SER_RS485_RX_DURING_TX)) अणु
		काष्ठा bcm2835aux_data *data = dev_get_drvdata(up->port.dev);

		data->cntl &= ~BCM2835_AUX_UART_CNTL_RXEN;
		serial_out(up, BCM2835_AUX_UART_CNTL, data->cntl);
	पूर्ण

	/*
	 * On the bcm2835aux, the MCR रेजिस्टर contains no other
	 * flags besides RTS.  So no need क्रम a पढ़ो-modअगरy-ग_लिखो.
	 */
	अगर (up->port.rs485.flags & SER_RS485_RTS_ON_SEND)
		serial8250_out_MCR(up, 0);
	अन्यथा
		serial8250_out_MCR(up, UART_MCR_RTS);
पूर्ण

अटल व्योम bcm2835aux_rs485_stop_tx(काष्ठा uart_8250_port *up)
अणु
	अगर (up->port.rs485.flags & SER_RS485_RTS_AFTER_SEND)
		serial8250_out_MCR(up, 0);
	अन्यथा
		serial8250_out_MCR(up, UART_MCR_RTS);

	अगर (!(up->port.rs485.flags & SER_RS485_RX_DURING_TX)) अणु
		काष्ठा bcm2835aux_data *data = dev_get_drvdata(up->port.dev);

		data->cntl |= BCM2835_AUX_UART_CNTL_RXEN;
		serial_out(up, BCM2835_AUX_UART_CNTL, data->cntl);
	पूर्ण
पूर्ण

अटल पूर्णांक bcm2835aux_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_8250_port up = अणु पूर्ण;
	काष्ठा bcm2835aux_data *data;
	काष्ठा resource *res;
	पूर्णांक ret;

	/* allocate the custom काष्ठाure */
	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* initialize data */
	up.capabilities = UART_CAP_FIFO | UART_CAP_MINI;
	up.port.dev = &pdev->dev;
	up.port.regshअगरt = 2;
	up.port.type = PORT_16550;
	up.port.iotype = UPIO_MEM;
	up.port.fअगरosize = 8;
	up.port.flags = UPF_SHARE_IRQ | UPF_FIXED_PORT | UPF_FIXED_TYPE |
			UPF_SKIP_TEST | UPF_IOREMAP;
	up.port.rs485_config = serial8250_em485_config;
	up.rs485_start_tx = bcm2835aux_rs485_start_tx;
	up.rs485_stop_tx = bcm2835aux_rs485_stop_tx;

	/* initialize cached copy with घातer-on reset value */
	data->cntl = BCM2835_AUX_UART_CNTL_RXEN | BCM2835_AUX_UART_CNTL_TXEN;

	platक्रमm_set_drvdata(pdev, data);

	/* get the घड़ी - this also enables the HW */
	data->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(data->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(data->clk), "could not get clk\n");

	/* get the पूर्णांकerrupt */
	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;
	up.port.irq = ret;

	/* map the मुख्य रेजिस्टरs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "memory resource not found");
		वापस -EINVAL;
	पूर्ण
	up.port.mapbase = res->start;
	up.port.mapsize = resource_size(res);

	/* Check क्रम a fixed line number */
	ret = of_alias_get_id(pdev->dev.of_node, "serial");
	अगर (ret >= 0)
		up.port.line = ret;

	/* enable the घड़ी as a last step */
	ret = clk_prepare_enable(data->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable uart clock - %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* the HW-घड़ी भागider क्रम bcm2835aux is 8,
	 * but 8250 expects a भागider of 16,
	 * so we have to multiply the actual घड़ी by 2
	 * to get identical baudrates.
	 */
	up.port.uartclk = clk_get_rate(data->clk) * 2;

	/* रेजिस्टर the port */
	ret = serial8250_रेजिस्टर_8250_port(&up);
	अगर (ret < 0) अणु
		dev_err_probe(&pdev->dev, ret, "unable to register 8250 port\n");
		जाओ dis_clk;
	पूर्ण
	data->line = ret;

	वापस 0;

dis_clk:
	clk_disable_unprepare(data->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक bcm2835aux_serial_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835aux_data *data = platक्रमm_get_drvdata(pdev);

	serial8250_unरेजिस्टर_port(data->line);
	clk_disable_unprepare(data->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm2835aux_serial_match[] = अणु
	अणु .compatible = "brcm,bcm2835-aux-uart" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2835aux_serial_match);

अटल काष्ठा platक्रमm_driver bcm2835aux_serial_driver = अणु
	.driver = अणु
		.name = "bcm2835-aux-uart",
		.of_match_table = bcm2835aux_serial_match,
	पूर्ण,
	.probe  = bcm2835aux_serial_probe,
	.हटाओ = bcm2835aux_serial_हटाओ,
पूर्ण;
module_platक्रमm_driver(bcm2835aux_serial_driver);

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE

अटल पूर्णांक __init early_bcm2835aux_setup(काष्ठा earlycon_device *device,
					स्थिर अक्षर *options)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->port.iotype = UPIO_MEM32;
	device->port.regshअगरt = 2;

	वापस early_serial8250_setup(device, शून्य);
पूर्ण

OF_EARLYCON_DECLARE(bcm2835aux, "brcm,bcm2835-aux-uart",
		    early_bcm2835aux_setup);
#पूर्ण_अगर

MODULE_DESCRIPTION("BCM2835 auxiliar UART driver");
MODULE_AUTHOR("Martin Sperl <kernel@martin.sperl.org>");
MODULE_LICENSE("GPL v2");
