<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Serial port driver क्रम NXP LPC18xx/43xx UART
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * Based on 8250_mtk.c:
 * Copyright (c) 2014 MunकरोReader S.L.
 * Matthias Brugger <matthias.bgg@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "8250.h"

/* Additional LPC18xx/43xx 8250 रेजिस्टरs and bits */
#घोषणा LPC18XX_UART_RS485CTRL		(0x04c / माप(u32))
#घोषणा  LPC18XX_UART_RS485CTRL_NMMEN	BIT(0)
#घोषणा  LPC18XX_UART_RS485CTRL_DCTRL	BIT(4)
#घोषणा  LPC18XX_UART_RS485CTRL_OINV	BIT(5)
#घोषणा LPC18XX_UART_RS485DLY		(0x054 / माप(u32))
#घोषणा LPC18XX_UART_RS485DLY_MAX	255

काष्ठा lpc18xx_uart_data अणु
	काष्ठा uart_8250_dma dma;
	काष्ठा clk *clk_uart;
	काष्ठा clk *clk_reg;
	पूर्णांक line;
पूर्ण;

अटल पूर्णांक lpc18xx_rs485_config(काष्ठा uart_port *port,
				काष्ठा serial_rs485 *rs485)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	u32 rs485_ctrl_reg = 0;
	u32 rs485_dly_reg = 0;
	अचिन्हित baud_clk;

	अगर (rs485->flags & SER_RS485_ENABLED)
		स_रखो(rs485->padding, 0, माप(rs485->padding));
	अन्यथा
		स_रखो(rs485, 0, माप(*rs485));

	rs485->flags &= SER_RS485_ENABLED | SER_RS485_RTS_ON_SEND |
			SER_RS485_RTS_AFTER_SEND;

	अगर (rs485->flags & SER_RS485_ENABLED) अणु
		rs485_ctrl_reg |= LPC18XX_UART_RS485CTRL_NMMEN |
				  LPC18XX_UART_RS485CTRL_DCTRL;

		अगर (rs485->flags & SER_RS485_RTS_ON_SEND) अणु
			rs485_ctrl_reg |= LPC18XX_UART_RS485CTRL_OINV;
			rs485->flags &= ~SER_RS485_RTS_AFTER_SEND;
		पूर्ण अन्यथा अणु
			rs485->flags |= SER_RS485_RTS_AFTER_SEND;
		पूर्ण
	पूर्ण

	अगर (rs485->delay_rts_after_send) अणु
		baud_clk = port->uartclk / up->dl_पढ़ो(up);
		rs485_dly_reg = DIV_ROUND_UP(rs485->delay_rts_after_send
						* baud_clk, MSEC_PER_SEC);

		अगर (rs485_dly_reg > LPC18XX_UART_RS485DLY_MAX)
			rs485_dly_reg = LPC18XX_UART_RS485DLY_MAX;

		/* Calculate the resulting delay in ms */
		rs485->delay_rts_after_send = (rs485_dly_reg * MSEC_PER_SEC)
						/ baud_clk;
	पूर्ण

	/* Delay RTS beक्रमe send not supported */
	rs485->delay_rts_beक्रमe_send = 0;

	serial_out(up, LPC18XX_UART_RS485CTRL, rs485_ctrl_reg);
	serial_out(up, LPC18XX_UART_RS485DLY, rs485_dly_reg);

	port->rs485 = *rs485;

	वापस 0;
पूर्ण

अटल व्योम lpc18xx_uart_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	/*
	 * For DMA mode one must ensure that the UART_FCR_DMA_SELECT
	 * bit is set when FIFO is enabled. Even अगर DMA is not used
	 * setting this bit करोesn't seem to affect anything.
	 */
	अगर (offset == UART_FCR && (value & UART_FCR_ENABLE_FIFO))
		value |= UART_FCR_DMA_SELECT;

	offset = offset << p->regshअगरt;
	ग_लिखोl(value, p->membase + offset);
पूर्ण

अटल पूर्णांक lpc18xx_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc18xx_uart_data *data;
	काष्ठा uart_8250_port uart;
	काष्ठा resource *res;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "memory resource not found");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&uart, 0, माप(uart));

	uart.port.membase = devm_ioremap(&pdev->dev, res->start,
					 resource_size(res));
	अगर (!uart.port.membase)
		वापस -ENOMEM;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->clk_uart = devm_clk_get(&pdev->dev, "uartclk");
	अगर (IS_ERR(data->clk_uart)) अणु
		dev_err(&pdev->dev, "uart clock not found\n");
		वापस PTR_ERR(data->clk_uart);
	पूर्ण

	data->clk_reg = devm_clk_get(&pdev->dev, "reg");
	अगर (IS_ERR(data->clk_reg)) अणु
		dev_err(&pdev->dev, "reg clock not found\n");
		वापस PTR_ERR(data->clk_reg);
	पूर्ण

	ret = clk_prepare_enable(data->clk_reg);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable reg clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(data->clk_uart);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable uart clock\n");
		जाओ dis_clk_reg;
	पूर्ण

	ret = of_alias_get_id(pdev->dev.of_node, "serial");
	अगर (ret >= 0)
		uart.port.line = ret;

	data->dma.rx_param = data;
	data->dma.tx_param = data;

	spin_lock_init(&uart.port.lock);
	uart.port.dev = &pdev->dev;
	uart.port.irq = irq;
	uart.port.iotype = UPIO_MEM32;
	uart.port.mapbase = res->start;
	uart.port.regshअगरt = 2;
	uart.port.type = PORT_16550A;
	uart.port.flags = UPF_FIXED_PORT | UPF_FIXED_TYPE | UPF_SKIP_TEST;
	uart.port.uartclk = clk_get_rate(data->clk_uart);
	uart.port.निजी_data = data;
	uart.port.rs485_config = lpc18xx_rs485_config;
	uart.port.serial_out = lpc18xx_uart_serial_out;

	uart.dma = &data->dma;
	uart.dma->rxconf.src_maxburst = 1;
	uart.dma->txconf.dst_maxburst = 1;

	ret = serial8250_रेजिस्टर_8250_port(&uart);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "unable to register 8250 port\n");
		जाओ dis_uart_clk;
	पूर्ण

	data->line = ret;
	platक्रमm_set_drvdata(pdev, data);

	वापस 0;

dis_uart_clk:
	clk_disable_unprepare(data->clk_uart);
dis_clk_reg:
	clk_disable_unprepare(data->clk_reg);
	वापस ret;
पूर्ण

अटल पूर्णांक lpc18xx_serial_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc18xx_uart_data *data = platक्रमm_get_drvdata(pdev);

	serial8250_unरेजिस्टर_port(data->line);
	clk_disable_unprepare(data->clk_uart);
	clk_disable_unprepare(data->clk_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_serial_match[] = अणु
	अणु .compatible = "nxp,lpc1850-uart" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc18xx_serial_match);

अटल काष्ठा platक्रमm_driver lpc18xx_serial_driver = अणु
	.probe  = lpc18xx_serial_probe,
	.हटाओ = lpc18xx_serial_हटाओ,
	.driver = अणु
		.name = "lpc18xx-uart",
		.of_match_table = lpc18xx_serial_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lpc18xx_serial_driver);

MODULE_AUTHOR("Joachim Eastwood <manabian@gmail.com>");
MODULE_DESCRIPTION("Serial port driver NXP LPC18xx/43xx devices");
MODULE_LICENSE("GPL v2");
