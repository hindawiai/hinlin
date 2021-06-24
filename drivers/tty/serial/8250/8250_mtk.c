<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Mediatek 8250 driver.
 *
 * Copyright (c) 2014 MunकरोReader S.L.
 * Author: Matthias Brugger <matthias.bgg@gmail.com>
 */
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/console.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#समावेश "8250.h"

#घोषणा MTK_UART_HIGHS		0x09	/* Highspeed रेजिस्टर */
#घोषणा MTK_UART_SAMPLE_COUNT	0x0a	/* Sample count रेजिस्टर */
#घोषणा MTK_UART_SAMPLE_POINT	0x0b	/* Sample poपूर्णांक रेजिस्टर */
#घोषणा MTK_UART_RATE_FIX	0x0d	/* UART Rate Fix Register */
#घोषणा MTK_UART_ESCAPE_DAT	0x10	/* Escape Character रेजिस्टर */
#घोषणा MTK_UART_ESCAPE_EN	0x11	/* Escape Enable रेजिस्टर */
#घोषणा MTK_UART_DMA_EN		0x13	/* DMA Enable रेजिस्टर */
#घोषणा MTK_UART_RXTRI_AD	0x14	/* RX Trigger address */
#घोषणा MTK_UART_FRACDIV_L	0x15	/* Fractional भागider LSB address */
#घोषणा MTK_UART_FRACDIV_M	0x16	/* Fractional भागider MSB address */
#घोषणा MTK_UART_DEBUG0	0x18
#घोषणा MTK_UART_IER_XOFFI	0x20	/* Enable XOFF अक्षरacter पूर्णांकerrupt */
#घोषणा MTK_UART_IER_RTSI	0x40	/* Enable RTS Modem status पूर्णांकerrupt */
#घोषणा MTK_UART_IER_CTSI	0x80	/* Enable CTS Modem status पूर्णांकerrupt */

#घोषणा MTK_UART_EFR_EN		0x10	/* Enable enhancement feature */
#घोषणा MTK_UART_EFR_RTS	0x40	/* Enable hardware rx flow control */
#घोषणा MTK_UART_EFR_CTS	0x80	/* Enable hardware tx flow control */
#घोषणा MTK_UART_EFR_NO_SW_FC	0x0	/* no sw flow control */
#घोषणा MTK_UART_EFR_XON1_XOFF1	0xa	/* XON1/XOFF1 as sw flow control */
#घोषणा MTK_UART_EFR_XON2_XOFF2	0x5	/* XON2/XOFF2 as sw flow control */
#घोषणा MTK_UART_EFR_SW_FC_MASK	0xf	/* Enable CTS Modem status पूर्णांकerrupt */
#घोषणा MTK_UART_EFR_HW_FC	(MTK_UART_EFR_RTS | MTK_UART_EFR_CTS)
#घोषणा MTK_UART_DMA_EN_TX	0x2
#घोषणा MTK_UART_DMA_EN_RX	0x5

#घोषणा MTK_UART_ESCAPE_CHAR	0x77	/* Escape अक्षर added under sw fc */
#घोषणा MTK_UART_RX_SIZE	0x8000
#घोषणा MTK_UART_TX_TRIGGER	1
#घोषणा MTK_UART_RX_TRIGGER	MTK_UART_RX_SIZE

#अगर_घोषित CONFIG_SERIAL_8250_DMA
क्रमागत dma_rx_status अणु
	DMA_RX_START = 0,
	DMA_RX_RUNNING = 1,
	DMA_RX_SHUTDOWN = 2,
पूर्ण;
#पूर्ण_अगर

काष्ठा mtk8250_data अणु
	पूर्णांक			line;
	अचिन्हित पूर्णांक		rx_pos;
	अचिन्हित पूर्णांक		clk_count;
	काष्ठा clk		*uart_clk;
	काष्ठा clk		*bus_clk;
	काष्ठा uart_8250_dma	*dma;
#अगर_घोषित CONFIG_SERIAL_8250_DMA
	क्रमागत dma_rx_status	rx_status;
#पूर्ण_अगर
	पूर्णांक			rx_wakeup_irq;
पूर्ण;

/* flow control mode */
क्रमागत अणु
	MTK_UART_FC_NONE,
	MTK_UART_FC_SW,
	MTK_UART_FC_HW,
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_8250_DMA
अटल व्योम mtk8250_rx_dma(काष्ठा uart_8250_port *up);

अटल व्योम mtk8250_dma_rx_complete(व्योम *param)
अणु
	काष्ठा uart_8250_port *up = param;
	काष्ठा uart_8250_dma *dma = up->dma;
	काष्ठा mtk8250_data *data = up->port.निजी_data;
	काष्ठा tty_port *tty_port = &up->port.state->port;
	काष्ठा dma_tx_state state;
	पूर्णांक copied, total, cnt;
	अचिन्हित अक्षर *ptr;

	अगर (data->rx_status == DMA_RX_SHUTDOWN)
		वापस;

	dmaengine_tx_status(dma->rxchan, dma->rx_cookie, &state);
	total = dma->rx_size - state.residue;
	cnt = total;

	अगर ((data->rx_pos + cnt) > dma->rx_size)
		cnt = dma->rx_size - data->rx_pos;

	ptr = (अचिन्हित अक्षर *)(data->rx_pos + dma->rx_buf);
	copied = tty_insert_flip_string(tty_port, ptr, cnt);
	data->rx_pos += cnt;

	अगर (total > cnt) अणु
		ptr = (अचिन्हित अक्षर *)(dma->rx_buf);
		cnt = total - cnt;
		copied += tty_insert_flip_string(tty_port, ptr, cnt);
		data->rx_pos = cnt;
	पूर्ण

	up->port.icount.rx += copied;

	tty_flip_buffer_push(tty_port);

	mtk8250_rx_dma(up);
पूर्ण

अटल व्योम mtk8250_rx_dma(काष्ठा uart_8250_port *up)
अणु
	काष्ठा uart_8250_dma *dma = up->dma;
	काष्ठा dma_async_tx_descriptor	*desc;

	desc = dmaengine_prep_slave_single(dma->rxchan, dma->rx_addr,
					   dma->rx_size, DMA_DEV_TO_MEM,
					   DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		pr_err("failed to prepare rx slave single\n");
		वापस;
	पूर्ण

	desc->callback = mtk8250_dma_rx_complete;
	desc->callback_param = up;

	dma->rx_cookie = dmaengine_submit(desc);

	dma_async_issue_pending(dma->rxchan);
पूर्ण

अटल व्योम mtk8250_dma_enable(काष्ठा uart_8250_port *up)
अणु
	काष्ठा uart_8250_dma *dma = up->dma;
	काष्ठा mtk8250_data *data = up->port.निजी_data;
	पूर्णांक lcr = serial_in(up, UART_LCR);

	अगर (data->rx_status != DMA_RX_START)
		वापस;

	dma->rxconf.src_port_winकरोw_size	= dma->rx_size;
	dma->rxconf.src_addr				= dma->rx_addr;

	dma->txconf.dst_port_winकरोw_size	= UART_XMIT_SIZE;
	dma->txconf.dst_addr				= dma->tx_addr;

	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_RCVR |
		UART_FCR_CLEAR_XMIT);
	serial_out(up, MTK_UART_DMA_EN,
		   MTK_UART_DMA_EN_RX | MTK_UART_DMA_EN_TX);

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, UART_EFR_ECB);
	serial_out(up, UART_LCR, lcr);

	अगर (dmaengine_slave_config(dma->rxchan, &dma->rxconf) != 0)
		pr_err("failed to configure rx dma channel\n");
	अगर (dmaengine_slave_config(dma->txchan, &dma->txconf) != 0)
		pr_err("failed to configure tx dma channel\n");

	data->rx_status = DMA_RX_RUNNING;
	data->rx_pos = 0;
	mtk8250_rx_dma(up);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mtk8250_startup(काष्ठा uart_port *port)
अणु
#अगर_घोषित CONFIG_SERIAL_8250_DMA
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	काष्ठा mtk8250_data *data = port->निजी_data;

	/* disable DMA क्रम console */
	अगर (uart_console(port))
		up->dma = शून्य;

	अगर (up->dma) अणु
		data->rx_status = DMA_RX_START;
		uart_circ_clear(&port->state->xmit);
	पूर्ण
#पूर्ण_अगर
	स_रखो(&port->icount, 0, माप(port->icount));

	वापस serial8250_करो_startup(port);
पूर्ण

अटल व्योम mtk8250_shutकरोwn(काष्ठा uart_port *port)
अणु
#अगर_घोषित CONFIG_SERIAL_8250_DMA
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	काष्ठा mtk8250_data *data = port->निजी_data;

	अगर (up->dma)
		data->rx_status = DMA_RX_SHUTDOWN;
#पूर्ण_अगर

	वापस serial8250_करो_shutकरोwn(port);
पूर्ण

अटल व्योम mtk8250_disable_पूर्णांकrs(काष्ठा uart_8250_port *up, पूर्णांक mask)
अणु
	serial_out(up, UART_IER, serial_in(up, UART_IER) & (~mask));
पूर्ण

अटल व्योम mtk8250_enable_पूर्णांकrs(काष्ठा uart_8250_port *up, पूर्णांक mask)
अणु
	serial_out(up, UART_IER, serial_in(up, UART_IER) | mask);
पूर्ण

अटल व्योम mtk8250_set_flow_ctrl(काष्ठा uart_8250_port *up, पूर्णांक mode)
अणु
	काष्ठा uart_port *port = &up->port;
	पूर्णांक lcr = serial_in(up, UART_LCR);

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, UART_EFR_ECB);
	serial_out(up, UART_LCR, lcr);
	lcr = serial_in(up, UART_LCR);

	चयन (mode) अणु
	हाल MTK_UART_FC_NONE:
		serial_out(up, MTK_UART_ESCAPE_DAT, MTK_UART_ESCAPE_CHAR);
		serial_out(up, MTK_UART_ESCAPE_EN, 0x00);
		serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
		serial_out(up, UART_EFR, serial_in(up, UART_EFR) &
			(~(MTK_UART_EFR_HW_FC | MTK_UART_EFR_SW_FC_MASK)));
		serial_out(up, UART_LCR, lcr);
		mtk8250_disable_पूर्णांकrs(up, MTK_UART_IER_XOFFI |
			MTK_UART_IER_RTSI | MTK_UART_IER_CTSI);
		अवरोध;

	हाल MTK_UART_FC_HW:
		serial_out(up, MTK_UART_ESCAPE_DAT, MTK_UART_ESCAPE_CHAR);
		serial_out(up, MTK_UART_ESCAPE_EN, 0x00);
		serial_out(up, UART_MCR, UART_MCR_RTS);
		serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

		/*enable hw flow control*/
		serial_out(up, UART_EFR, MTK_UART_EFR_HW_FC |
			(serial_in(up, UART_EFR) &
			(~(MTK_UART_EFR_HW_FC | MTK_UART_EFR_SW_FC_MASK))));

		serial_out(up, UART_LCR, lcr);
		mtk8250_disable_पूर्णांकrs(up, MTK_UART_IER_XOFFI);
		mtk8250_enable_पूर्णांकrs(up, MTK_UART_IER_CTSI | MTK_UART_IER_RTSI);
		अवरोध;

	हाल MTK_UART_FC_SW:	/*MTK software flow control */
		serial_out(up, MTK_UART_ESCAPE_DAT, MTK_UART_ESCAPE_CHAR);
		serial_out(up, MTK_UART_ESCAPE_EN, 0x01);
		serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

		/*enable sw flow control */
		serial_out(up, UART_EFR, MTK_UART_EFR_XON1_XOFF1 |
			(serial_in(up, UART_EFR) &
			(~(MTK_UART_EFR_HW_FC | MTK_UART_EFR_SW_FC_MASK))));

		serial_out(up, UART_XON1, START_CHAR(port->state->port.tty));
		serial_out(up, UART_XOFF1, STOP_CHAR(port->state->port.tty));
		serial_out(up, UART_LCR, lcr);
		mtk8250_disable_पूर्णांकrs(up, MTK_UART_IER_CTSI|MTK_UART_IER_RTSI);
		mtk8250_enable_पूर्णांकrs(up, MTK_UART_IER_XOFFI);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mtk8250_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			काष्ठा ktermios *old)
अणु
	अचिन्हित लघु fraction_L_mapping[] = अणु
		0, 1, 0x5, 0x15, 0x55, 0x57, 0x57, 0x77, 0x7F, 0xFF, 0xFF
	पूर्ण;
	अचिन्हित लघु fraction_M_mapping[] = अणु
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 3
	पूर्ण;
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित पूर्णांक baud, quot, fraction;
	अचिन्हित दीर्घ flags;
	पूर्णांक mode;

#अगर_घोषित CONFIG_SERIAL_8250_DMA
	अगर (up->dma) अणु
		अगर (uart_console(port)) अणु
			devm_kमुक्त(up->port.dev, up->dma);
			up->dma = शून्य;
		पूर्ण अन्यथा अणु
			mtk8250_dma_enable(up);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * Store the requested baud rate beक्रमe calling the generic 8250
	 * set_termios method. Standard 8250 port expects bauds to be
	 * no higher than (uartclk / 16) so the baud will be clamped अगर it
	 * माला_लो out of that bound. Mediatek 8250 port supports speed
	 * higher than that, thereक्रमe we'll get original baud rate back
	 * after calling the generic set_termios method and recalculate
	 * the speed later in this method.
	 */
	baud = tty_termios_baud_rate(termios);

	serial8250_करो_set_termios(port, termios, शून्य);

	tty_termios_encode_baud_rate(termios, baud, baud);

	/*
	 * Mediatek UARTs use an extra highspeed रेजिस्टर (MTK_UART_HIGHS)
	 *
	 * We need to recalcualte the quot रेजिस्टर, as the claculation depends
	 * on the vaule in the highspeed रेजिस्टर.
	 *
	 * Some baudrates are not supported by the chip, so we use the next
	 * lower rate supported and update termios c_flag.
	 *
	 * If highspeed रेजिस्टर is set to 3, we need to specअगरy sample count
	 * and sample poपूर्णांक to increase accuracy. If not, we reset the
	 * रेजिस्टरs to their शेष values.
	 */
	baud = uart_get_baud_rate(port, termios, old,
				  port->uartclk / 16 / UART_DIV_MAX,
				  port->uartclk);

	अगर (baud < 115200) अणु
		serial_port_out(port, MTK_UART_HIGHS, 0x0);
		quot = uart_get_भागisor(port, baud);
	पूर्ण अन्यथा अणु
		serial_port_out(port, MTK_UART_HIGHS, 0x3);
		quot = DIV_ROUND_UP(port->uartclk, 256 * baud);
	पूर्ण

	/*
	 * Ok, we're now changing the port state.  Do it with
	 * पूर्णांकerrupts disabled.
	 */
	spin_lock_irqsave(&port->lock, flags);

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	/* set DLAB we have cval saved in up->lcr from the call to the core */
	serial_port_out(port, UART_LCR, up->lcr | UART_LCR_DLAB);
	serial_dl_ग_लिखो(up, quot);

	/* reset DLAB */
	serial_port_out(port, UART_LCR, up->lcr);

	अगर (baud >= 115200) अणु
		अचिन्हित पूर्णांक पंचांगp;

		पंचांगp = (port->uartclk / (baud *  quot)) - 1;
		serial_port_out(port, MTK_UART_SAMPLE_COUNT, पंचांगp);
		serial_port_out(port, MTK_UART_SAMPLE_POINT,
					(पंचांगp >> 1) - 1);

		/*count fraction to set fractoin रेजिस्टर */
		fraction = ((port->uartclk  * 100) / baud / quot) % 100;
		fraction = DIV_ROUND_CLOSEST(fraction, 10);
		serial_port_out(port, MTK_UART_FRACDIV_L,
						fraction_L_mapping[fraction]);
		serial_port_out(port, MTK_UART_FRACDIV_M,
						fraction_M_mapping[fraction]);
	पूर्ण अन्यथा अणु
		serial_port_out(port, MTK_UART_SAMPLE_COUNT, 0x00);
		serial_port_out(port, MTK_UART_SAMPLE_POINT, 0xff);
		serial_port_out(port, MTK_UART_FRACDIV_L, 0x00);
		serial_port_out(port, MTK_UART_FRACDIV_M, 0x00);
	पूर्ण

	अगर ((termios->c_cflag & CRTSCTS) && (!(termios->c_अगरlag & CRTSCTS)))
		mode = MTK_UART_FC_HW;
	अन्यथा अगर (termios->c_अगरlag & CRTSCTS)
		mode = MTK_UART_FC_SW;
	अन्यथा
		mode = MTK_UART_FC_NONE;

	mtk8250_set_flow_ctrl(up, mode);

	अगर (uart_console(port))
		up->port.cons->cflag = termios->c_cflag;

	spin_unlock_irqrestore(&port->lock, flags);
	/* Don't reग_लिखो B0 */
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);
पूर्ण

अटल पूर्णांक __maybe_unused mtk8250_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk8250_data *data = dev_get_drvdata(dev);
	काष्ठा uart_8250_port *up = serial8250_get_port(data->line);

	/* रुको until UART in idle status */
	जबतक
		(serial_in(up, MTK_UART_DEBUG0));

	अगर (data->clk_count == 0U) अणु
		dev_dbg(dev, "%s clock count is 0\n", __func__);
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(data->bus_clk);
		data->clk_count--;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk8250_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk8250_data *data = dev_get_drvdata(dev);
	पूर्णांक err;

	अगर (data->clk_count > 0U) अणु
		dev_dbg(dev, "%s clock count is %d\n", __func__,
			data->clk_count);
	पूर्ण अन्यथा अणु
		err = clk_prepare_enable(data->bus_clk);
		अगर (err) अणु
			dev_warn(dev, "Can't enable bus clock\n");
			वापस err;
		पूर्ण
		data->clk_count++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mtk8250_करो_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक old)
अणु
	अगर (!state)
		अगर (!mtk8250_runसमय_resume(port->dev))
			pm_runसमय_get_sync(port->dev);

	serial8250_करो_pm(port, state, old);

	अगर (state)
		अगर (!pm_runसमय_put_sync_suspend(port->dev))
			mtk8250_runसमय_suspend(port->dev);
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_DMA
अटल bool mtk8250_dma_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mtk8250_probe_of(काष्ठा platक्रमm_device *pdev, काष्ठा uart_port *p,
			   काष्ठा mtk8250_data *data)
अणु
#अगर_घोषित CONFIG_SERIAL_8250_DMA
	पूर्णांक dmacnt;
#पूर्ण_अगर

	data->uart_clk = devm_clk_get(&pdev->dev, "baud");
	अगर (IS_ERR(data->uart_clk)) अणु
		/*
		 * For compatibility with older device trees try unnamed
		 * clk when no baud clk can be found.
		 */
		data->uart_clk = devm_clk_get(&pdev->dev, शून्य);
		अगर (IS_ERR(data->uart_clk)) अणु
			dev_warn(&pdev->dev, "Can't get uart clock\n");
			वापस PTR_ERR(data->uart_clk);
		पूर्ण

		वापस 0;
	पूर्ण

	data->bus_clk = devm_clk_get(&pdev->dev, "bus");
	अगर (IS_ERR(data->bus_clk))
		वापस PTR_ERR(data->bus_clk);

	data->dma = शून्य;
#अगर_घोषित CONFIG_SERIAL_8250_DMA
	dmacnt = of_property_count_strings(pdev->dev.of_node, "dma-names");
	अगर (dmacnt == 2) अणु
		data->dma = devm_kzalloc(&pdev->dev, माप(*data->dma),
					 GFP_KERNEL);
		अगर (!data->dma)
			वापस -ENOMEM;

		data->dma->fn = mtk8250_dma_filter;
		data->dma->rx_size = MTK_UART_RX_SIZE;
		data->dma->rxconf.src_maxburst = MTK_UART_RX_TRIGGER;
		data->dma->txconf.dst_maxburst = MTK_UART_TX_TRIGGER;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक mtk8250_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_8250_port uart = अणुपूर्ण;
	काष्ठा mtk8250_data *data;
	काष्ठा resource *regs;
	पूर्णांक irq, err;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs) अणु
		dev_err(&pdev->dev, "no registers defined\n");
		वापस -EINVAL;
	पूर्ण

	uart.port.membase = devm_ioremap(&pdev->dev, regs->start,
					 resource_size(regs));
	अगर (!uart.port.membase)
		वापस -ENOMEM;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->clk_count = 0;

	अगर (pdev->dev.of_node) अणु
		err = mtk8250_probe_of(pdev, &uart.port, data);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा
		वापस -ENODEV;

	spin_lock_init(&uart.port.lock);
	uart.port.mapbase = regs->start;
	uart.port.irq = irq;
	uart.port.pm = mtk8250_करो_pm;
	uart.port.type = PORT_16550;
	uart.port.flags = UPF_BOOT_AUTOCONF | UPF_FIXED_PORT;
	uart.port.dev = &pdev->dev;
	uart.port.iotype = UPIO_MEM32;
	uart.port.regshअगरt = 2;
	uart.port.निजी_data = data;
	uart.port.shutकरोwn = mtk8250_shutकरोwn;
	uart.port.startup = mtk8250_startup;
	uart.port.set_termios = mtk8250_set_termios;
	uart.port.uartclk = clk_get_rate(data->uart_clk);
#अगर_घोषित CONFIG_SERIAL_8250_DMA
	अगर (data->dma)
		uart.dma = data->dma;
#पूर्ण_अगर

	/* Disable Rate Fix function */
	ग_लिखोl(0x0, uart.port.membase +
			(MTK_UART_RATE_FIX << uart.port.regshअगरt));

	platक्रमm_set_drvdata(pdev, data);

	pm_runसमय_enable(&pdev->dev);
	err = mtk8250_runसमय_resume(&pdev->dev);
	अगर (err)
		जाओ err_pm_disable;

	data->line = serial8250_रेजिस्टर_8250_port(&uart);
	अगर (data->line < 0) अणु
		err = data->line;
		जाओ err_pm_disable;
	पूर्ण

	data->rx_wakeup_irq = platक्रमm_get_irq_optional(pdev, 1);

	वापस 0;

err_pm_disable:
	pm_runसमय_disable(&pdev->dev);

	वापस err;
पूर्ण

अटल पूर्णांक mtk8250_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk8250_data *data = platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(&pdev->dev);

	serial8250_unरेजिस्टर_port(data->line);

	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		mtk8250_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk8250_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk8250_data *data = dev_get_drvdata(dev);
	पूर्णांक irq = data->rx_wakeup_irq;
	पूर्णांक err;

	serial8250_suspend_port(data->line);

	pinctrl_pm_select_sleep_state(dev);
	अगर (irq >= 0) अणु
		err = enable_irq_wake(irq);
		अगर (err) अणु
			dev_err(dev,
				"failed to enable irq wake on IRQ %d: %d\n",
				irq, err);
			pinctrl_pm_select_शेष_state(dev);
			serial8250_resume_port(data->line);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk8250_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk8250_data *data = dev_get_drvdata(dev);
	पूर्णांक irq = data->rx_wakeup_irq;

	अगर (irq >= 0)
		disable_irq_wake(irq);
	pinctrl_pm_select_शेष_state(dev);

	serial8250_resume_port(data->line);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mtk8250_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mtk8250_suspend, mtk8250_resume)
	SET_RUNTIME_PM_OPS(mtk8250_runसमय_suspend, mtk8250_runसमय_resume,
				शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk8250_of_match[] = अणु
	अणु .compatible = "mediatek,mt6577-uart" पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk8250_of_match);

अटल काष्ठा platक्रमm_driver mtk8250_platक्रमm_driver = अणु
	.driver = अणु
		.name		= "mt6577-uart",
		.pm		= &mtk8250_pm_ops,
		.of_match_table	= mtk8250_of_match,
	पूर्ण,
	.probe			= mtk8250_probe,
	.हटाओ			= mtk8250_हटाओ,
पूर्ण;
module_platक्रमm_driver(mtk8250_platक्रमm_driver);

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
अटल पूर्णांक __init early_mtk8250_setup(काष्ठा earlycon_device *device,
					स्थिर अक्षर *options)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->port.iotype = UPIO_MEM32;
	device->port.regshअगरt = 2;

	वापस early_serial8250_setup(device, शून्य);
पूर्ण

OF_EARLYCON_DECLARE(mtk8250, "mediatek,mt6577-uart", early_mtk8250_setup);
#पूर्ण_अगर

MODULE_AUTHOR("Matthias Brugger");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Mediatek 8250 serial port driver");
