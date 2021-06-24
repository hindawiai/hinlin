<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/console.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#घोषणा TCU_MBOX_BYTE(i, x)			((x) << (i * 8))
#घोषणा TCU_MBOX_BYTE_V(x, i)			(((x) >> (i * 8)) & 0xff)
#घोषणा TCU_MBOX_NUM_BYTES(x)			((x) << 24)
#घोषणा TCU_MBOX_NUM_BYTES_V(x)			(((x) >> 24) & 0x3)

काष्ठा tegra_tcu अणु
	काष्ठा uart_driver driver;
#अगर IS_ENABLED(CONFIG_SERIAL_TEGRA_TCU_CONSOLE)
	काष्ठा console console;
#पूर्ण_अगर
	काष्ठा uart_port port;

	काष्ठा mbox_client tx_client, rx_client;
	काष्ठा mbox_chan *tx, *rx;
पूर्ण;

अटल अचिन्हित पूर्णांक tegra_tcu_uart_tx_empty(काष्ठा uart_port *port)
अणु
	वापस TIOCSER_TEMT;
पूर्ण

अटल व्योम tegra_tcu_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
पूर्ण

अटल अचिन्हित पूर्णांक tegra_tcu_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम tegra_tcu_uart_stop_tx(काष्ठा uart_port *port)
अणु
पूर्ण

अटल व्योम tegra_tcu_ग_लिखो_one(काष्ठा tegra_tcu *tcu, u32 value,
				अचिन्हित पूर्णांक count)
अणु
	व्योम *msg;

	value |= TCU_MBOX_NUM_BYTES(count);
	msg = (व्योम *)(अचिन्हित दीर्घ)value;
	mbox_send_message(tcu->tx, msg);
	mbox_flush(tcu->tx, 1000);
पूर्ण

अटल व्योम tegra_tcu_ग_लिखो(काष्ठा tegra_tcu *tcu, स्थिर अक्षर *s,
			    अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक written = 0, i = 0;
	bool insert_nl = false;
	u32 value = 0;

	जबतक (i < count) अणु
		अगर (insert_nl) अणु
			value |= TCU_MBOX_BYTE(written++, '\n');
			insert_nl = false;
			i++;
		पूर्ण अन्यथा अगर (s[i] == '\n') अणु
			value |= TCU_MBOX_BYTE(written++, '\r');
			insert_nl = true;
		पूर्ण अन्यथा अणु
			value |= TCU_MBOX_BYTE(written++, s[i++]);
		पूर्ण

		अगर (written == 3) अणु
			tegra_tcu_ग_लिखो_one(tcu, value, 3);
			value = written = 0;
		पूर्ण
	पूर्ण

	अगर (written)
		tegra_tcu_ग_लिखो_one(tcu, value, written);
पूर्ण

अटल व्योम tegra_tcu_uart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा tegra_tcu *tcu = port->निजी_data;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित दीर्घ count;

	क्रम (;;) अणु
		count = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);
		अगर (!count)
			अवरोध;

		tegra_tcu_ग_लिखो(tcu, &xmit->buf[xmit->tail], count);
		xmit->tail = (xmit->tail + count) & (UART_XMIT_SIZE - 1);
	पूर्ण

	uart_ग_लिखो_wakeup(port);
पूर्ण

अटल व्योम tegra_tcu_uart_stop_rx(काष्ठा uart_port *port)
अणु
पूर्ण

अटल व्योम tegra_tcu_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक ctl)
अणु
पूर्ण

अटल पूर्णांक tegra_tcu_uart_startup(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम tegra_tcu_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
पूर्ण

अटल व्योम tegra_tcu_uart_set_termios(काष्ठा uart_port *port,
				       काष्ठा ktermios *new,
				       काष्ठा ktermios *old)
अणु
पूर्ण

अटल स्थिर काष्ठा uart_ops tegra_tcu_uart_ops = अणु
	.tx_empty = tegra_tcu_uart_tx_empty,
	.set_mctrl = tegra_tcu_uart_set_mctrl,
	.get_mctrl = tegra_tcu_uart_get_mctrl,
	.stop_tx = tegra_tcu_uart_stop_tx,
	.start_tx = tegra_tcu_uart_start_tx,
	.stop_rx = tegra_tcu_uart_stop_rx,
	.अवरोध_ctl = tegra_tcu_uart_अवरोध_ctl,
	.startup = tegra_tcu_uart_startup,
	.shutकरोwn = tegra_tcu_uart_shutकरोwn,
	.set_termios = tegra_tcu_uart_set_termios,
पूर्ण;

#अगर IS_ENABLED(CONFIG_SERIAL_TEGRA_TCU_CONSOLE)
अटल व्योम tegra_tcu_console_ग_लिखो(काष्ठा console *cons, स्थिर अक्षर *s,
				    अचिन्हित पूर्णांक count)
अणु
	काष्ठा tegra_tcu *tcu = container_of(cons, काष्ठा tegra_tcu, console);

	tegra_tcu_ग_लिखो(tcu, s, count);
पूर्ण

अटल पूर्णांक tegra_tcu_console_setup(काष्ठा console *cons, अक्षर *options)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम tegra_tcu_receive(काष्ठा mbox_client *cl, व्योम *msg)
अणु
	काष्ठा tegra_tcu *tcu = container_of(cl, काष्ठा tegra_tcu, rx_client);
	काष्ठा tty_port *port = &tcu->port.state->port;
	u32 value = (u32)(अचिन्हित दीर्घ)msg;
	अचिन्हित पूर्णांक num_bytes, i;

	num_bytes = TCU_MBOX_NUM_BYTES_V(value);

	क्रम (i = 0; i < num_bytes; i++)
		tty_insert_flip_अक्षर(port, TCU_MBOX_BYTE_V(value, i),
				     TTY_NORMAL);

	tty_flip_buffer_push(port);
पूर्ण

अटल पूर्णांक tegra_tcu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port;
	काष्ठा tegra_tcu *tcu;
	पूर्णांक err;

	tcu = devm_kzalloc(&pdev->dev, माप(*tcu), GFP_KERNEL);
	अगर (!tcu)
		वापस -ENOMEM;

	tcu->tx_client.dev = &pdev->dev;
	tcu->rx_client.dev = &pdev->dev;
	tcu->rx_client.rx_callback = tegra_tcu_receive;

	tcu->tx = mbox_request_channel_byname(&tcu->tx_client, "tx");
	अगर (IS_ERR(tcu->tx)) अणु
		err = PTR_ERR(tcu->tx);
		dev_err(&pdev->dev, "failed to get tx mailbox: %d\n", err);
		वापस err;
	पूर्ण

	tcu->rx = mbox_request_channel_byname(&tcu->rx_client, "rx");
	अगर (IS_ERR(tcu->rx)) अणु
		err = PTR_ERR(tcu->rx);
		dev_err(&pdev->dev, "failed to get rx mailbox: %d\n", err);
		जाओ मुक्त_tx;
	पूर्ण

#अगर IS_ENABLED(CONFIG_SERIAL_TEGRA_TCU_CONSOLE)
	/* setup the console */
	म_नकल(tcu->console.name, "ttyTCU");
	tcu->console.device = uart_console_device;
	tcu->console.flags = CON_PRINTBUFFER | CON_ANYTIME;
	tcu->console.index = -1;
	tcu->console.ग_लिखो = tegra_tcu_console_ग_लिखो;
	tcu->console.setup = tegra_tcu_console_setup;
	tcu->console.data = &tcu->driver;
#पूर्ण_अगर

	/* setup the driver */
	tcu->driver.owner = THIS_MODULE;
	tcu->driver.driver_name = "tegra-tcu";
	tcu->driver.dev_name = "ttyTCU";
#अगर IS_ENABLED(CONFIG_SERIAL_TEGRA_TCU_CONSOLE)
	tcu->driver.cons = &tcu->console;
#पूर्ण_अगर
	tcu->driver.nr = 1;

	err = uart_रेजिस्टर_driver(&tcu->driver);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register UART driver: %d\n",
			err);
		जाओ मुक्त_rx;
	पूर्ण

	/* setup the port */
	port = &tcu->port;
	spin_lock_init(&port->lock);
	port->dev = &pdev->dev;
	port->type = PORT_TEGRA_TCU;
	port->ops = &tegra_tcu_uart_ops;
	port->fअगरosize = 1;
	port->iotype = UPIO_MEM;
	port->flags = UPF_BOOT_AUTOCONF;
	port->निजी_data = tcu;

	err = uart_add_one_port(&tcu->driver, port);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to add UART port: %d\n", err);
		जाओ unरेजिस्टर_uart;
	पूर्ण

	platक्रमm_set_drvdata(pdev, tcu);
#अगर IS_ENABLED(CONFIG_SERIAL_TEGRA_TCU_CONSOLE)
	रेजिस्टर_console(&tcu->console);
#पूर्ण_अगर

	वापस 0;

unरेजिस्टर_uart:
	uart_unरेजिस्टर_driver(&tcu->driver);
मुक्त_rx:
	mbox_मुक्त_channel(tcu->rx);
मुक्त_tx:
	mbox_मुक्त_channel(tcu->tx);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_tcu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_tcu *tcu = platक्रमm_get_drvdata(pdev);

#अगर IS_ENABLED(CONFIG_SERIAL_TEGRA_TCU_CONSOLE)
	unरेजिस्टर_console(&tcu->console);
#पूर्ण_अगर
	uart_हटाओ_one_port(&tcu->driver, &tcu->port);
	uart_unरेजिस्टर_driver(&tcu->driver);
	mbox_मुक्त_channel(tcu->rx);
	mbox_मुक्त_channel(tcu->tx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_tcu_match[] = अणु
	अणु .compatible = "nvidia,tegra194-tcu" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_tcu_match);

अटल काष्ठा platक्रमm_driver tegra_tcu_driver = अणु
	.driver = अणु
		.name = "tegra-tcu",
		.of_match_table = tegra_tcu_match,
	पूर्ण,
	.probe = tegra_tcu_probe,
	.हटाओ = tegra_tcu_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_tcu_driver);

MODULE_AUTHOR("Mikko Perttunen <mperttunen@nvidia.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("NVIDIA Tegra Combined UART driver");
