<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2020 NXP
 */

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>

#घोषणा URTX0 0x40 /* Transmitter Register */
#घोषणा UTS_TXFULL (1<<4) /* TxFIFO full */
#घोषणा IMX21_UTS 0xb4 /* UART Test Register on all other i.mx*/

अटल व्योम imx_uart_console_early_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	जबतक (पढ़ोl_relaxed(port->membase + IMX21_UTS) & UTS_TXFULL)
		cpu_relax();

	ग_लिखोl_relaxed(ch, port->membase + URTX0);
पूर्ण

अटल व्योम imx_uart_console_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s,
					 अचिन्हित count)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, count, imx_uart_console_early_अक्षर_दो);
पूर्ण

अटल पूर्णांक __init
imx_console_early_setup(काष्ठा earlycon_device *dev, स्थिर अक्षर *opt)
अणु
	अगर (!dev->port.membase)
		वापस -ENODEV;

	dev->con->ग_लिखो = imx_uart_console_early_ग_लिखो;

	वापस 0;
पूर्ण
OF_EARLYCON_DECLARE(ec_imx6q, "fsl,imx6q-uart", imx_console_early_setup);
OF_EARLYCON_DECLARE(ec_imx21, "fsl,imx21-uart", imx_console_early_setup);

MODULE_AUTHOR("NXP");
MODULE_DESCRIPTION("IMX earlycon driver");
MODULE_LICENSE("GPL");
