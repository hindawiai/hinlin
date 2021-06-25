<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Synopsys DesignWare 8250 driver.
 *
 * Copyright 2011 Picochip, Jamie Iles.
 * Copyright 2013 Intel Corporation
 *
 * The Synopsys DesignWare 8250 has an extra feature whereby it detects अगर the
 * LCR is written whilst busy.  If it is, then a busy detect पूर्णांकerrupt is
 * उठाओd, the LCR needs to be rewritten and the uart status रेजिस्टर पढ़ो.
 */
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <यंत्र/byteorder.h>

#समावेश "8250_dwlib.h"

/* Offsets क्रम the DesignWare specअगरic रेजिस्टरs */
#घोषणा DW_UART_USR	0x1f /* UART Status Register */

/* DesignWare specअगरic रेजिस्टर fields */
#घोषणा DW_UART_MCR_SIRE		BIT(6)

काष्ठा dw8250_data अणु
	काष्ठा dw8250_port_data	data;

	u8			usr_reg;
	पूर्णांक			msr_mask_on;
	पूर्णांक			msr_mask_off;
	काष्ठा clk		*clk;
	काष्ठा clk		*pclk;
	काष्ठा notअगरier_block	clk_notअगरier;
	काष्ठा work_काष्ठा	clk_work;
	काष्ठा reset_control	*rst;

	अचिन्हित पूर्णांक		skip_स्वतःcfg:1;
	अचिन्हित पूर्णांक		uart_16550_compatible:1;
पूर्ण;

अटल अंतरभूत काष्ठा dw8250_data *to_dw8250_data(काष्ठा dw8250_port_data *data)
अणु
	वापस container_of(data, काष्ठा dw8250_data, data);
पूर्ण

अटल अंतरभूत काष्ठा dw8250_data *clk_to_dw8250_data(काष्ठा notअगरier_block *nb)
अणु
	वापस container_of(nb, काष्ठा dw8250_data, clk_notअगरier);
पूर्ण

अटल अंतरभूत काष्ठा dw8250_data *work_to_dw8250_data(काष्ठा work_काष्ठा *work)
अणु
	वापस container_of(work, काष्ठा dw8250_data, clk_work);
पूर्ण

अटल अंतरभूत पूर्णांक dw8250_modअगरy_msr(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा dw8250_data *d = to_dw8250_data(p->निजी_data);

	/* Override any modem control संकेतs अगर needed */
	अगर (offset == UART_MSR) अणु
		value |= d->msr_mask_on;
		value &= ~d->msr_mask_off;
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम dw8250_क्रमce_idle(काष्ठा uart_port *p)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(p);

	serial8250_clear_and_reinit_fअगरos(up);
	(व्योम)p->serial_in(p, UART_RX);
पूर्ण

अटल व्योम dw8250_check_lcr(काष्ठा uart_port *p, पूर्णांक value)
अणु
	व्योम __iomem *offset = p->membase + (UART_LCR << p->regshअगरt);
	पूर्णांक tries = 1000;

	/* Make sure LCR ग_लिखो wasn't ignored */
	जबतक (tries--) अणु
		अचिन्हित पूर्णांक lcr = p->serial_in(p, UART_LCR);

		अगर ((value & ~UART_LCR_SPAR) == (lcr & ~UART_LCR_SPAR))
			वापस;

		dw8250_क्रमce_idle(p);

#अगर_घोषित CONFIG_64BIT
		अगर (p->type == PORT_OCTEON)
			__raw_ग_लिखोq(value & 0xff, offset);
		अन्यथा
#पूर्ण_अगर
		अगर (p->iotype == UPIO_MEM32)
			ग_लिखोl(value, offset);
		अन्यथा अगर (p->iotype == UPIO_MEM32BE)
			ioग_लिखो32be(value, offset);
		अन्यथा
			ग_लिखोb(value, offset);
	पूर्ण
	/*
	 * FIXME: this deadlocks अगर port->lock is alपढ़ोy held
	 * dev_err(p->dev, "Couldn't set LCR to %d\n", value);
	 */
पूर्ण

/* Returns once the transmitter is empty or we run out of retries */
अटल व्योम dw8250_tx_रुको_empty(काष्ठा uart_port *p)
अणु
	अचिन्हित पूर्णांक tries = 20000;
	अचिन्हित पूर्णांक delay_threshold = tries - 1000;
	अचिन्हित पूर्णांक lsr;

	जबतक (tries--) अणु
		lsr = पढ़ोb (p->membase + (UART_LSR << p->regshअगरt));
		अगर (lsr & UART_LSR_TEMT)
			अवरोध;

		/* The device is first given a chance to empty without delay,
		 * to aव्योम slowकरोwns at high bitrates. If after 1000 tries
		 * the buffer has still not emptied, allow more समय क्रम low-
		 * speed links. */
		अगर (tries < delay_threshold)
			udelay (1);
	पूर्ण
पूर्ण

अटल व्योम dw8250_serial_out38x(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा dw8250_data *d = to_dw8250_data(p->निजी_data);

	/* Allow the TX to drain beक्रमe we reconfigure */
	अगर (offset == UART_LCR)
		dw8250_tx_रुको_empty(p);

	ग_लिखोb(value, p->membase + (offset << p->regshअगरt));

	अगर (offset == UART_LCR && !d->uart_16550_compatible)
		dw8250_check_lcr(p, value);
पूर्ण


अटल व्योम dw8250_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा dw8250_data *d = to_dw8250_data(p->निजी_data);

	ग_लिखोb(value, p->membase + (offset << p->regshअगरt));

	अगर (offset == UART_LCR && !d->uart_16550_compatible)
		dw8250_check_lcr(p, value);
पूर्ण

अटल अचिन्हित पूर्णांक dw8250_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक value = पढ़ोb(p->membase + (offset << p->regshअगरt));

	वापस dw8250_modअगरy_msr(p, offset, value);
पूर्ण

#अगर_घोषित CONFIG_64BIT
अटल अचिन्हित पूर्णांक dw8250_serial_inq(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक value;

	value = (u8)__raw_पढ़ोq(p->membase + (offset << p->regshअगरt));

	वापस dw8250_modअगरy_msr(p, offset, value);
पूर्ण

अटल व्योम dw8250_serial_outq(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा dw8250_data *d = to_dw8250_data(p->निजी_data);

	value &= 0xff;
	__raw_ग_लिखोq(value, p->membase + (offset << p->regshअगरt));
	/* Read back to ensure रेजिस्टर ग_लिखो ordering. */
	__raw_पढ़ोq(p->membase + (UART_LCR << p->regshअगरt));

	अगर (offset == UART_LCR && !d->uart_16550_compatible)
		dw8250_check_lcr(p, value);
पूर्ण
#पूर्ण_अगर /* CONFIG_64BIT */

अटल व्योम dw8250_serial_out32(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा dw8250_data *d = to_dw8250_data(p->निजी_data);

	ग_लिखोl(value, p->membase + (offset << p->regshअगरt));

	अगर (offset == UART_LCR && !d->uart_16550_compatible)
		dw8250_check_lcr(p, value);
पूर्ण

अटल अचिन्हित पूर्णांक dw8250_serial_in32(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक value = पढ़ोl(p->membase + (offset << p->regshअगरt));

	वापस dw8250_modअगरy_msr(p, offset, value);
पूर्ण

अटल व्योम dw8250_serial_out32be(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा dw8250_data *d = to_dw8250_data(p->निजी_data);

	ioग_लिखो32be(value, p->membase + (offset << p->regshअगरt));

	अगर (offset == UART_LCR && !d->uart_16550_compatible)
		dw8250_check_lcr(p, value);
पूर्ण

अटल अचिन्हित पूर्णांक dw8250_serial_in32be(काष्ठा uart_port *p, पूर्णांक offset)
अणु
       अचिन्हित पूर्णांक value = ioपढ़ो32be(p->membase + (offset << p->regshअगरt));

       वापस dw8250_modअगरy_msr(p, offset, value);
पूर्ण


अटल पूर्णांक dw8250_handle_irq(काष्ठा uart_port *p)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(p);
	काष्ठा dw8250_data *d = to_dw8250_data(p->निजी_data);
	अचिन्हित पूर्णांक iir = p->serial_in(p, UART_IIR);
	अचिन्हित पूर्णांक status;
	अचिन्हित दीर्घ flags;

	/*
	 * There are ways to get Designware-based UARTs पूर्णांकo a state where
	 * they are निश्चितing UART_IIR_RX_TIMEOUT but there is no actual
	 * data available.  If we see such a हाल then we'll करो a bogus
	 * पढ़ो.  If we करोn't करो this then the "RX TIMEOUT" पूर्णांकerrupt will
	 * fire क्रमever.
	 *
	 * This problem has only been observed so far when not in DMA mode
	 * so we limit the workaround only to non-DMA mode.
	 */
	अगर (!up->dma && ((iir & 0x3f) == UART_IIR_RX_TIMEOUT)) अणु
		spin_lock_irqsave(&p->lock, flags);
		status = p->serial_in(p, UART_LSR);

		अगर (!(status & (UART_LSR_DR | UART_LSR_BI)))
			(व्योम) p->serial_in(p, UART_RX);

		spin_unlock_irqrestore(&p->lock, flags);
	पूर्ण

	अगर (serial8250_handle_irq(p, iir))
		वापस 1;

	अगर ((iir & UART_IIR_BUSY) == UART_IIR_BUSY) अणु
		/* Clear the USR */
		(व्योम)p->serial_in(p, d->usr_reg);

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dw8250_clk_work_cb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dw8250_data *d = work_to_dw8250_data(work);
	काष्ठा uart_8250_port *up;
	अचिन्हित दीर्घ rate;

	rate = clk_get_rate(d->clk);
	अगर (rate <= 0)
		वापस;

	up = serial8250_get_port(d->data.line);

	serial8250_update_uartclk(&up->port, rate);
पूर्ण

अटल पूर्णांक dw8250_clk_notअगरier_cb(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा dw8250_data *d = clk_to_dw8250_data(nb);

	/*
	 * We have no choice but to defer the uartclk update due to two
	 * deadlocks. First one is caused by a recursive mutex lock which
	 * happens when clk_set_rate() is called from dw8250_set_termios().
	 * Second deadlock is more tricky and is caused by an inverted order of
	 * the clk and tty-port mutexes lock. It happens अगर घड़ी rate change
	 * is requested asynchronously जबतक set_termios() is executed between
	 * tty-port mutex lock and clk_set_rate() function invocation and
	 * vise-versa. Anyway अगर we didn't have the reference घड़ी alteration
	 * in the dw8250_set_termios() method we wouldn't have needed this
	 * deferred event handling complication.
	 */
	अगर (event == POST_RATE_CHANGE) अणु
		queue_work(प्रणाली_unbound_wq, &d->clk_work);
		वापस NOTIFY_OK;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम
dw8250_करो_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक old)
अणु
	अगर (!state)
		pm_runसमय_get_sync(port->dev);

	serial8250_करो_pm(port, state, old);

	अगर (state)
		pm_runसमय_put_sync_suspend(port->dev);
पूर्ण

अटल व्योम dw8250_set_termios(काष्ठा uart_port *p, काष्ठा ktermios *termios,
			       काष्ठा ktermios *old)
अणु
	अचिन्हित दीर्घ newrate = tty_termios_baud_rate(termios) * 16;
	काष्ठा dw8250_data *d = to_dw8250_data(p->निजी_data);
	दीर्घ rate;
	पूर्णांक ret;

	clk_disable_unprepare(d->clk);
	rate = clk_round_rate(d->clk, newrate);
	अगर (rate > 0) अणु
		/*
		 * Premilinary set the uartclk to the new घड़ी rate so the
		 * घड़ी update event handler caused by the clk_set_rate()
		 * calling wouldn't actually update the UART भागisor since
		 * we about to करो this anyway.
		 */
		swap(p->uartclk, rate);
		ret = clk_set_rate(d->clk, newrate);
		अगर (ret)
			swap(p->uartclk, rate);
	पूर्ण
	clk_prepare_enable(d->clk);

	p->status &= ~UPSTAT_AUTOCTS;
	अगर (termios->c_cflag & CRTSCTS)
		p->status |= UPSTAT_AUTOCTS;

	serial8250_करो_set_termios(p, termios, old);
पूर्ण

अटल व्योम dw8250_set_ldisc(काष्ठा uart_port *p, काष्ठा ktermios *termios)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(p);
	अचिन्हित पूर्णांक mcr = p->serial_in(p, UART_MCR);

	अगर (up->capabilities & UART_CAP_IRDA) अणु
		अगर (termios->c_line == N_IRDA)
			mcr |= DW_UART_MCR_SIRE;
		अन्यथा
			mcr &= ~DW_UART_MCR_SIRE;

		p->serial_out(p, UART_MCR, mcr);
	पूर्ण
	serial8250_करो_set_ldisc(p, termios);
पूर्ण

/*
 * dw8250_fallback_dma_filter will prevent the UART from getting just any मुक्त
 * channel on platक्रमms that have DMA engines, but करोn't have any channels
 * asचिन्हित to the UART.
 *
 * REVISIT: This is a work around क्रम limitation in the DMA Engine API. Once the
 * core problem is fixed, this function is no दीर्घer needed.
 */
अटल bool dw8250_fallback_dma_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	वापस false;
पूर्ण

अटल bool dw8250_idma_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	वापस param == chan->device->dev;
पूर्ण

अटल व्योम dw8250_quirks(काष्ठा uart_port *p, काष्ठा dw8250_data *data)
अणु
	अगर (p->dev->of_node) अणु
		काष्ठा device_node *np = p->dev->of_node;
		पूर्णांक id;

		/* get index of serial line, अगर found in DT aliases */
		id = of_alias_get_id(np, "serial");
		अगर (id >= 0)
			p->line = id;
#अगर_घोषित CONFIG_64BIT
		अगर (of_device_is_compatible(np, "cavium,octeon-3860-uart")) अणु
			p->serial_in = dw8250_serial_inq;
			p->serial_out = dw8250_serial_outq;
			p->flags = UPF_SKIP_TEST | UPF_SHARE_IRQ | UPF_FIXED_TYPE;
			p->type = PORT_OCTEON;
			data->usr_reg = 0x27;
			data->skip_स्वतःcfg = true;
		पूर्ण
#पूर्ण_अगर
		अगर (of_device_is_big_endian(p->dev->of_node)) अणु
			p->iotype = UPIO_MEM32BE;
			p->serial_in = dw8250_serial_in32be;
			p->serial_out = dw8250_serial_out32be;
		पूर्ण
		अगर (of_device_is_compatible(np, "marvell,armada-38x-uart"))
			p->serial_out = dw8250_serial_out38x;

	पूर्ण अन्यथा अगर (acpi_dev_present("APMC0D08", शून्य, -1)) अणु
		p->iotype = UPIO_MEM32;
		p->regshअगरt = 2;
		p->serial_in = dw8250_serial_in32;
		data->uart_16550_compatible = true;
	पूर्ण

	/* Platक्रमms with iDMA 64-bit */
	अगर (platक्रमm_get_resource_byname(to_platक्रमm_device(p->dev),
					 IORESOURCE_MEM, "lpss_priv")) अणु
		data->data.dma.rx_param = p->dev->parent;
		data->data.dma.tx_param = p->dev->parent;
		data->data.dma.fn = dw8250_idma_filter;
	पूर्ण
पूर्ण

अटल पूर्णांक dw8250_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_8250_port uart = अणुपूर्ण, *up = &uart;
	काष्ठा resource *regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	काष्ठा uart_port *p = &up->port;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw8250_data *data;
	पूर्णांक irq;
	पूर्णांक err;
	u32 val;

	अगर (!regs) अणु
		dev_err(dev, "no registers defined\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	spin_lock_init(&p->lock);
	p->mapbase	= regs->start;
	p->irq		= irq;
	p->handle_irq	= dw8250_handle_irq;
	p->pm		= dw8250_करो_pm;
	p->type		= PORT_8250;
	p->flags	= UPF_SHARE_IRQ | UPF_FIXED_PORT;
	p->dev		= dev;
	p->iotype	= UPIO_MEM;
	p->serial_in	= dw8250_serial_in;
	p->serial_out	= dw8250_serial_out;
	p->set_ldisc	= dw8250_set_ldisc;
	p->set_termios	= dw8250_set_termios;

	p->membase = devm_ioremap(dev, regs->start, resource_size(regs));
	अगर (!p->membase)
		वापस -ENOMEM;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->data.dma.fn = dw8250_fallback_dma_filter;
	data->usr_reg = DW_UART_USR;
	p->निजी_data = &data->data;

	data->uart_16550_compatible = device_property_पढ़ो_bool(dev,
						"snps,uart-16550-compatible");

	err = device_property_पढ़ो_u32(dev, "reg-shift", &val);
	अगर (!err)
		p->regshअगरt = val;

	err = device_property_पढ़ो_u32(dev, "reg-io-width", &val);
	अगर (!err && val == 4) अणु
		p->iotype = UPIO_MEM32;
		p->serial_in = dw8250_serial_in32;
		p->serial_out = dw8250_serial_out32;
	पूर्ण

	अगर (device_property_पढ़ो_bool(dev, "dcd-override")) अणु
		/* Always report DCD as active */
		data->msr_mask_on |= UART_MSR_DCD;
		data->msr_mask_off |= UART_MSR_DDCD;
	पूर्ण

	अगर (device_property_पढ़ो_bool(dev, "dsr-override")) अणु
		/* Always report DSR as active */
		data->msr_mask_on |= UART_MSR_DSR;
		data->msr_mask_off |= UART_MSR_DDSR;
	पूर्ण

	अगर (device_property_पढ़ो_bool(dev, "cts-override")) अणु
		/* Always report CTS as active */
		data->msr_mask_on |= UART_MSR_CTS;
		data->msr_mask_off |= UART_MSR_DCTS;
	पूर्ण

	अगर (device_property_पढ़ो_bool(dev, "ri-override")) अणु
		/* Always report Ring indicator as inactive */
		data->msr_mask_off |= UART_MSR_RI;
		data->msr_mask_off |= UART_MSR_TERI;
	पूर्ण

	/* Always ask क्रम fixed घड़ी rate from a property. */
	device_property_पढ़ो_u32(dev, "clock-frequency", &p->uartclk);

	/* If there is separate baudclk, get the rate from it. */
	data->clk = devm_clk_get_optional(dev, "baudclk");
	अगर (data->clk == शून्य)
		data->clk = devm_clk_get_optional(dev, शून्य);
	अगर (IS_ERR(data->clk))
		वापस PTR_ERR(data->clk);

	INIT_WORK(&data->clk_work, dw8250_clk_work_cb);
	data->clk_notअगरier.notअगरier_call = dw8250_clk_notअगरier_cb;

	err = clk_prepare_enable(data->clk);
	अगर (err)
		dev_warn(dev, "could not enable optional baudclk: %d\n", err);

	अगर (data->clk)
		p->uartclk = clk_get_rate(data->clk);

	/* If no घड़ी rate is defined, fail. */
	अगर (!p->uartclk) अणु
		dev_err(dev, "clock rate not defined\n");
		err = -EINVAL;
		जाओ err_clk;
	पूर्ण

	data->pclk = devm_clk_get_optional(dev, "apb_pclk");
	अगर (IS_ERR(data->pclk)) अणु
		err = PTR_ERR(data->pclk);
		जाओ err_clk;
	पूर्ण

	err = clk_prepare_enable(data->pclk);
	अगर (err) अणु
		dev_err(dev, "could not enable apb_pclk\n");
		जाओ err_clk;
	पूर्ण

	data->rst = devm_reset_control_get_optional_exclusive(dev, शून्य);
	अगर (IS_ERR(data->rst)) अणु
		err = PTR_ERR(data->rst);
		जाओ err_pclk;
	पूर्ण
	reset_control_deनिश्चित(data->rst);

	dw8250_quirks(p, data);

	/* If the Busy Functionality is not implemented, करोn't handle it */
	अगर (data->uart_16550_compatible)
		p->handle_irq = शून्य;

	अगर (!data->skip_स्वतःcfg)
		dw8250_setup_port(p);

	/* If we have a valid fअगरosize, try hooking up DMA */
	अगर (p->fअगरosize) अणु
		data->data.dma.rxconf.src_maxburst = p->fअगरosize / 4;
		data->data.dma.txconf.dst_maxburst = p->fअगरosize / 4;
		up->dma = &data->data.dma;
	पूर्ण

	data->data.line = serial8250_रेजिस्टर_8250_port(up);
	अगर (data->data.line < 0) अणु
		err = data->data.line;
		जाओ err_reset;
	पूर्ण

	/*
	 * Some platक्रमms may provide a reference घड़ी shared between several
	 * devices. In this हाल any घड़ी state change must be known to the
	 * UART port at least post factum.
	 */
	अगर (data->clk) अणु
		err = clk_notअगरier_रेजिस्टर(data->clk, &data->clk_notअगरier);
		अगर (err)
			dev_warn(p->dev, "Failed to set the clock notifier\n");
		अन्यथा
			queue_work(प्रणाली_unbound_wq, &data->clk_work);
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;

err_reset:
	reset_control_निश्चित(data->rst);

err_pclk:
	clk_disable_unprepare(data->pclk);

err_clk:
	clk_disable_unprepare(data->clk);

	वापस err;
पूर्ण

अटल पूर्णांक dw8250_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw8250_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;

	pm_runसमय_get_sync(dev);

	अगर (data->clk) अणु
		clk_notअगरier_unरेजिस्टर(data->clk, &data->clk_notअगरier);

		flush_work(&data->clk_work);
	पूर्ण

	serial8250_unरेजिस्टर_port(data->data.line);

	reset_control_निश्चित(data->rst);

	clk_disable_unprepare(data->pclk);

	clk_disable_unprepare(data->clk);

	pm_runसमय_disable(dev);
	pm_runसमय_put_noidle(dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dw8250_suspend(काष्ठा device *dev)
अणु
	काष्ठा dw8250_data *data = dev_get_drvdata(dev);

	serial8250_suspend_port(data->data.line);

	वापस 0;
पूर्ण

अटल पूर्णांक dw8250_resume(काष्ठा device *dev)
अणु
	काष्ठा dw8250_data *data = dev_get_drvdata(dev);

	serial8250_resume_port(data->data.line);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक dw8250_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dw8250_data *data = dev_get_drvdata(dev);

	clk_disable_unprepare(data->clk);

	clk_disable_unprepare(data->pclk);

	वापस 0;
पूर्ण

अटल पूर्णांक dw8250_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dw8250_data *data = dev_get_drvdata(dev);

	clk_prepare_enable(data->pclk);

	clk_prepare_enable(data->clk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops dw8250_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dw8250_suspend, dw8250_resume)
	SET_RUNTIME_PM_OPS(dw8250_runसमय_suspend, dw8250_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id dw8250_of_match[] = अणु
	अणु .compatible = "snps,dw-apb-uart" पूर्ण,
	अणु .compatible = "cavium,octeon-3860-uart" पूर्ण,
	अणु .compatible = "marvell,armada-38x-uart" पूर्ण,
	अणु .compatible = "renesas,rzn1-uart" पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dw8250_of_match);

अटल स्थिर काष्ठा acpi_device_id dw8250_acpi_match[] = अणु
	अणु "INT33C4", 0 पूर्ण,
	अणु "INT33C5", 0 पूर्ण,
	अणु "INT3434", 0 पूर्ण,
	अणु "INT3435", 0 पूर्ण,
	अणु "80860F0A", 0 पूर्ण,
	अणु "8086228A", 0 पूर्ण,
	अणु "APMC0D08", 0पूर्ण,
	अणु "AMD0020", 0 पूर्ण,
	अणु "AMDI0020", 0 पूर्ण,
	अणु "AMDI0022", 0 पूर्ण,
	अणु "BRCM2032", 0 पूर्ण,
	अणु "HISI0031", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, dw8250_acpi_match);

अटल काष्ठा platक्रमm_driver dw8250_platक्रमm_driver = अणु
	.driver = अणु
		.name		= "dw-apb-uart",
		.pm		= &dw8250_pm_ops,
		.of_match_table	= dw8250_of_match,
		.acpi_match_table = ACPI_PTR(dw8250_acpi_match),
	पूर्ण,
	.probe			= dw8250_probe,
	.हटाओ			= dw8250_हटाओ,
पूर्ण;

module_platक्रमm_driver(dw8250_platक्रमm_driver);

MODULE_AUTHOR("Jamie Iles");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Synopsys DesignWare 8250 serial port driver");
MODULE_ALIAS("platform:dw-apb-uart");
