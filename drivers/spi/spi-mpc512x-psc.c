<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC512x PSC in SPI mode driver.
 *
 * Copyright (C) 2007,2008 Freescale Semiconductor Inc.
 * Original port from 52xx driver:
 *	Hongjun Chen <hong-jun.chen@मुक्तscale.com>
 *
 * Fork of mpc52xx_psc_spi.c:
 *	Copyright (C) 2006 TOPTICA Photonics AG., Dragos Carp
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/completion.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/gpपन.स>
#समावेश <यंत्र/mpc52xx_psc.h>

क्रमागत अणु
	TYPE_MPC5121,
	TYPE_MPC5125,
पूर्ण;

/*
 * This macro असलtracts the dअगरferences in the PSC रेजिस्टर layout between
 * MPC5121 (which uses a काष्ठा mpc52xx_psc) and MPC5125 (using mpc5125_psc).
 */
#घोषणा psc_addr(mps, regname) (अणु					\
	व्योम *__ret = शून्य;						\
	चयन (mps->type) अणु						\
	हाल TYPE_MPC5121: अणु						\
			काष्ठा mpc52xx_psc __iomem *psc = mps->psc;	\
			__ret = &psc->regname;				\
		पूर्ण;							\
		अवरोध;							\
	हाल TYPE_MPC5125: अणु						\
			काष्ठा mpc5125_psc __iomem *psc = mps->psc;	\
			__ret = &psc->regname;				\
		पूर्ण;							\
		अवरोध;							\
	पूर्ण								\
	__ret; पूर्ण)

काष्ठा mpc512x_psc_spi अणु
	व्योम (*cs_control)(काष्ठा spi_device *spi, bool on);

	/* driver पूर्णांकernal data */
	पूर्णांक type;
	व्योम __iomem *psc;
	काष्ठा mpc512x_psc_fअगरo __iomem *fअगरo;
	अचिन्हित पूर्णांक irq;
	u8 bits_per_word;
	काष्ठा clk *clk_mclk;
	काष्ठा clk *clk_ipg;
	u32 mclk_rate;

	काष्ठा completion txisrकरोne;
पूर्ण;

/* controller state */
काष्ठा mpc512x_psc_spi_cs अणु
	पूर्णांक bits_per_word;
	पूर्णांक speed_hz;
पूर्ण;

/* set घड़ी freq, घड़ी ramp, bits per work
 * अगर t is शून्य then reset the values to the शेष values
 */
अटल पूर्णांक mpc512x_psc_spi_transfer_setup(काष्ठा spi_device *spi,
					  काष्ठा spi_transfer *t)
अणु
	काष्ठा mpc512x_psc_spi_cs *cs = spi->controller_state;

	cs->speed_hz = (t && t->speed_hz)
	    ? t->speed_hz : spi->max_speed_hz;
	cs->bits_per_word = (t && t->bits_per_word)
	    ? t->bits_per_word : spi->bits_per_word;
	cs->bits_per_word = ((cs->bits_per_word + 7) / 8) * 8;
	वापस 0;
पूर्ण

अटल व्योम mpc512x_psc_spi_activate_cs(काष्ठा spi_device *spi)
अणु
	काष्ठा mpc512x_psc_spi_cs *cs = spi->controller_state;
	काष्ठा mpc512x_psc_spi *mps = spi_master_get_devdata(spi->master);
	u32 sicr;
	u32 ccr;
	पूर्णांक speed;
	u16 bclkभाग;

	sicr = in_be32(psc_addr(mps, sicr));

	/* Set घड़ी phase and polarity */
	अगर (spi->mode & SPI_CPHA)
		sicr |= 0x00001000;
	अन्यथा
		sicr &= ~0x00001000;

	अगर (spi->mode & SPI_CPOL)
		sicr |= 0x00002000;
	अन्यथा
		sicr &= ~0x00002000;

	अगर (spi->mode & SPI_LSB_FIRST)
		sicr |= 0x10000000;
	अन्यथा
		sicr &= ~0x10000000;
	out_be32(psc_addr(mps, sicr), sicr);

	ccr = in_be32(psc_addr(mps, ccr));
	ccr &= 0xFF000000;
	speed = cs->speed_hz;
	अगर (!speed)
		speed = 1000000;	/* शेष 1MHz */
	bclkभाग = (mps->mclk_rate / speed) - 1;

	ccr |= (((bclkभाग & 0xff) << 16) | (((bclkभाग >> 8) & 0xff) << 8));
	out_be32(psc_addr(mps, ccr), ccr);
	mps->bits_per_word = cs->bits_per_word;

	अगर (mps->cs_control && gpio_is_valid(spi->cs_gpio))
		mps->cs_control(spi, (spi->mode & SPI_CS_HIGH) ? 1 : 0);
पूर्ण

अटल व्योम mpc512x_psc_spi_deactivate_cs(काष्ठा spi_device *spi)
अणु
	काष्ठा mpc512x_psc_spi *mps = spi_master_get_devdata(spi->master);

	अगर (mps->cs_control && gpio_is_valid(spi->cs_gpio))
		mps->cs_control(spi, (spi->mode & SPI_CS_HIGH) ? 0 : 1);

पूर्ण

/* extract and scale size field in txsz or rxsz */
#घोषणा MPC512x_PSC_FIFO_SZ(sz) ((sz & 0x7ff) << 2);

#घोषणा खातापूर्णBYTE 1

अटल पूर्णांक mpc512x_psc_spi_transfer_rxtx(काष्ठा spi_device *spi,
					 काष्ठा spi_transfer *t)
अणु
	काष्ठा mpc512x_psc_spi *mps = spi_master_get_devdata(spi->master);
	काष्ठा mpc512x_psc_fअगरo __iomem *fअगरo = mps->fअगरo;
	माप_प्रकार tx_len = t->len;
	माप_प्रकार rx_len = t->len;
	u8 *tx_buf = (u8 *)t->tx_buf;
	u8 *rx_buf = (u8 *)t->rx_buf;

	अगर (!tx_buf && !rx_buf && t->len)
		वापस -EINVAL;

	जबतक (rx_len || tx_len) अणु
		माप_प्रकार txcount;
		u8 data;
		माप_प्रकार fअगरosz;
		माप_प्रकार rxcount;
		पूर्णांक rxtries;

		/*
		 * send the TX bytes in as large a chunk as possible
		 * but neither exceed the TX nor the RX FIFOs
		 */
		fअगरosz = MPC512x_PSC_FIFO_SZ(in_be32(&fअगरo->txsz));
		txcount = min(fअगरosz, tx_len);
		fअगरosz = MPC512x_PSC_FIFO_SZ(in_be32(&fअगरo->rxsz));
		fअगरosz -= in_be32(&fअगरo->rxcnt) + 1;
		txcount = min(fअगरosz, txcount);
		अगर (txcount) अणु

			/* fill the TX FIFO */
			जबतक (txcount-- > 0) अणु
				data = tx_buf ? *tx_buf++ : 0;
				अगर (tx_len == खातापूर्णBYTE && t->cs_change)
					setbits32(&fअगरo->txcmd,
						  MPC512x_PSC_FIFO_खातापूर्ण);
				out_8(&fअगरo->txdata_8, data);
				tx_len--;
			पूर्ण

			/* have the ISR trigger when the TX FIFO is empty */
			reinit_completion(&mps->txisrकरोne);
			out_be32(&fअगरo->txisr, MPC512x_PSC_FIFO_EMPTY);
			out_be32(&fअगरo->tximr, MPC512x_PSC_FIFO_EMPTY);
			रुको_क्रम_completion(&mps->txisrकरोne);
		पूर्ण

		/*
		 * consume as much RX data as the FIFO holds, जबतक we
		 * iterate over the transfer's TX data length
		 *
		 * only insist in draining all the reमुख्यing RX bytes
		 * when the TX bytes were exhausted (that's at the very
		 * end of this transfer, not when still iterating over
		 * the transfer's chunks)
		 */
		rxtries = 50;
		करो अणु

			/*
			 * grab whatever was in the FIFO when we started
			 * looking, करोn't bother fetching what was added to
			 * the FIFO जबतक we पढ़ो from it -- we'll वापस
			 * here eventually and prefer sending out reमुख्यing
			 * TX data
			 */
			fअगरosz = in_be32(&fअगरo->rxcnt);
			rxcount = min(fअगरosz, rx_len);
			जबतक (rxcount-- > 0) अणु
				data = in_8(&fअगरo->rxdata_8);
				अगर (rx_buf)
					*rx_buf++ = data;
				rx_len--;
			पूर्ण

			/*
			 * come back later अगर there still is TX data to send,
			 * bail out of the RX drain loop अगर all of the TX data
			 * was sent and all of the RX data was received (i.e.
			 * when the transmission has completed)
			 */
			अगर (tx_len)
				अवरोध;
			अगर (!rx_len)
				अवरोध;

			/*
			 * TX data transmission has completed जबतक RX data
			 * is still pending -- that's a transient situation
			 * which depends on wire speed and specअगरic
			 * hardware implementation details (buffering) yet
			 * should resolve very quickly
			 *
			 * just yield क्रम a moment to not hog the CPU क्रम
			 * too दीर्घ when running SPI at low speed
			 *
			 * the समयout range is rather arbitrary and tries
			 * to balance throughput against प्रणाली load; the
			 * chosen values result in a minimal समयout of 50
			 * बार 10us and thus work at speeds as low as
			 * some 20kbps, जबतक the maximum समयout at the
			 * transfer's end could be 5ms _अगर_ nothing अन्यथा
			 * ticks in the प्रणाली _and_ RX data still wasn't
			 * received, which only occurs in situations that
			 * are exceptional; removing the unpredictability
			 * of the समयout either decreases throughput
			 * (दीर्घer समयouts), or माला_दो more load on the
			 * प्रणाली (fixed लघु समयouts) or requires the
			 * use of a समयout API instead of a counter and an
			 * unknown inner delay
			 */
			usleep_range(10, 100);

		पूर्ण जबतक (--rxtries > 0);
		अगर (!tx_len && rx_len && !rxtries) अणु
			/*
			 * not enough RX bytes even after several retries
			 * and the resulting rather दीर्घ समयout?
			 */
			rxcount = in_be32(&fअगरo->rxcnt);
			dev_warn(&spi->dev,
				 "short xfer, missing %zd RX bytes, FIFO level %zd\n",
				 rx_len, rxcount);
		पूर्ण

		/*
		 * drain and drop RX data which "should not be there" in
		 * the first place, क्रम undisturbed transmission this turns
		 * पूर्णांकo a NOP (except क्रम the FIFO level fetch)
		 */
		अगर (!tx_len && !rx_len) अणु
			जबतक (in_be32(&fअगरo->rxcnt))
				in_8(&fअगरo->rxdata_8);
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mpc512x_psc_spi_msg_xfer(काष्ठा spi_master *master,
				    काष्ठा spi_message *m)
अणु
	काष्ठा spi_device *spi;
	अचिन्हित cs_change;
	पूर्णांक status;
	काष्ठा spi_transfer *t;

	spi = m->spi;
	cs_change = 1;
	status = 0;
	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		status = mpc512x_psc_spi_transfer_setup(spi, t);
		अगर (status < 0)
			अवरोध;

		अगर (cs_change)
			mpc512x_psc_spi_activate_cs(spi);
		cs_change = t->cs_change;

		status = mpc512x_psc_spi_transfer_rxtx(spi, t);
		अगर (status)
			अवरोध;
		m->actual_length += t->len;

		spi_transfer_delay_exec(t);

		अगर (cs_change)
			mpc512x_psc_spi_deactivate_cs(spi);
	पूर्ण

	m->status = status;
	अगर (m->complete)
		m->complete(m->context);

	अगर (status || !cs_change)
		mpc512x_psc_spi_deactivate_cs(spi);

	mpc512x_psc_spi_transfer_setup(spi, शून्य);

	spi_finalize_current_message(master);
	वापस status;
पूर्ण

अटल पूर्णांक mpc512x_psc_spi_prep_xfer_hw(काष्ठा spi_master *master)
अणु
	काष्ठा mpc512x_psc_spi *mps = spi_master_get_devdata(master);

	dev_dbg(&master->dev, "%s()\n", __func__);

	/* Zero MR2 */
	in_8(psc_addr(mps, mr2));
	out_8(psc_addr(mps, mr2), 0x0);

	/* enable transmitter/receiver */
	out_8(psc_addr(mps, command), MPC52xx_PSC_TX_ENABLE | MPC52xx_PSC_RX_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc512x_psc_spi_unprep_xfer_hw(काष्ठा spi_master *master)
अणु
	काष्ठा mpc512x_psc_spi *mps = spi_master_get_devdata(master);
	काष्ठा mpc512x_psc_fअगरo __iomem *fअगरo = mps->fअगरo;

	dev_dbg(&master->dev, "%s()\n", __func__);

	/* disable transmitter/receiver and fअगरo पूर्णांकerrupt */
	out_8(psc_addr(mps, command), MPC52xx_PSC_TX_DISABLE | MPC52xx_PSC_RX_DISABLE);
	out_be32(&fअगरo->tximr, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc512x_psc_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा mpc512x_psc_spi_cs *cs = spi->controller_state;
	पूर्णांक ret;

	अगर (spi->bits_per_word % 8)
		वापस -EINVAL;

	अगर (!cs) अणु
		cs = kzalloc(माप *cs, GFP_KERNEL);
		अगर (!cs)
			वापस -ENOMEM;

		अगर (gpio_is_valid(spi->cs_gpio)) अणु
			ret = gpio_request(spi->cs_gpio, dev_name(&spi->dev));
			अगर (ret) अणु
				dev_err(&spi->dev, "can't get CS gpio: %d\n",
					ret);
				kमुक्त(cs);
				वापस ret;
			पूर्ण
			gpio_direction_output(spi->cs_gpio,
					spi->mode & SPI_CS_HIGH ? 0 : 1);
		पूर्ण

		spi->controller_state = cs;
	पूर्ण

	cs->bits_per_word = spi->bits_per_word;
	cs->speed_hz = spi->max_speed_hz;

	वापस 0;
पूर्ण

अटल व्योम mpc512x_psc_spi_cleanup(काष्ठा spi_device *spi)
अणु
	अगर (gpio_is_valid(spi->cs_gpio))
		gpio_मुक्त(spi->cs_gpio);
	kमुक्त(spi->controller_state);
पूर्ण

अटल पूर्णांक mpc512x_psc_spi_port_config(काष्ठा spi_master *master,
				       काष्ठा mpc512x_psc_spi *mps)
अणु
	काष्ठा mpc512x_psc_fअगरo __iomem *fअगरo = mps->fअगरo;
	u32 sicr;
	u32 ccr;
	पूर्णांक speed;
	u16 bclkभाग;

	/* Reset the PSC पूर्णांकo a known state */
	out_8(psc_addr(mps, command), MPC52xx_PSC_RST_RX);
	out_8(psc_addr(mps, command), MPC52xx_PSC_RST_TX);
	out_8(psc_addr(mps, command), MPC52xx_PSC_TX_DISABLE | MPC52xx_PSC_RX_DISABLE);

	/* Disable psc पूर्णांकerrupts all useful पूर्णांकerrupts are in fअगरo */
	out_be16(psc_addr(mps, isr_imr.imr), 0);

	/* Disable fअगरo पूर्णांकerrupts, will be enabled later */
	out_be32(&fअगरo->tximr, 0);
	out_be32(&fअगरo->rximr, 0);

	/* Setup fअगरo slice address and size */
	/*out_be32(&fअगरo->txsz, 0x0fe00004);*/
	/*out_be32(&fअगरo->rxsz, 0x0ff00004);*/

	sicr =	0x01000000 |	/* SIM = 0001 -- 8 bit */
		0x00800000 |	/* GenClk = 1 -- पूर्णांकernal clk */
		0x00008000 |	/* SPI = 1 */
		0x00004000 |	/* MSTR = 1   -- SPI master */
		0x00000800;	/* Useखातापूर्ण = 1 -- SS low until खातापूर्ण */

	out_be32(psc_addr(mps, sicr), sicr);

	ccr = in_be32(psc_addr(mps, ccr));
	ccr &= 0xFF000000;
	speed = 1000000;	/* शेष 1MHz */
	bclkभाग = (mps->mclk_rate / speed) - 1;
	ccr |= (((bclkभाग & 0xff) << 16) | (((bclkभाग >> 8) & 0xff) << 8));
	out_be32(psc_addr(mps, ccr), ccr);

	/* Set 2ms DTL delay */
	out_8(psc_addr(mps, ctur), 0x00);
	out_8(psc_addr(mps, ctlr), 0x82);

	/* we करोn't use the alarms */
	out_be32(&fअगरo->rxalarm, 0xfff);
	out_be32(&fअगरo->txalarm, 0);

	/* Enable FIFO slices क्रम Rx/Tx */
	out_be32(&fअगरo->rxcmd,
		 MPC512x_PSC_FIFO_ENABLE_SLICE | MPC512x_PSC_FIFO_ENABLE_DMA);
	out_be32(&fअगरo->txcmd,
		 MPC512x_PSC_FIFO_ENABLE_SLICE | MPC512x_PSC_FIFO_ENABLE_DMA);

	mps->bits_per_word = 8;

	वापस 0;
पूर्ण

अटल irqवापस_t mpc512x_psc_spi_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mpc512x_psc_spi *mps = (काष्ठा mpc512x_psc_spi *)dev_id;
	काष्ठा mpc512x_psc_fअगरo __iomem *fअगरo = mps->fअगरo;

	/* clear पूर्णांकerrupt and wake up the rx/tx routine */
	अगर (in_be32(&fअगरo->txisr) &
	    in_be32(&fअगरo->tximr) & MPC512x_PSC_FIFO_EMPTY) अणु
		out_be32(&fअगरo->txisr, MPC512x_PSC_FIFO_EMPTY);
		out_be32(&fअगरo->tximr, 0);
		complete(&mps->txisrकरोne);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल व्योम mpc512x_spi_cs_control(काष्ठा spi_device *spi, bool onoff)
अणु
	gpio_set_value(spi->cs_gpio, onoff);
पूर्ण

अटल पूर्णांक mpc512x_psc_spi_करो_probe(काष्ठा device *dev, u32 regaddr,
					      u32 size, अचिन्हित पूर्णांक irq)
अणु
	काष्ठा fsl_spi_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा mpc512x_psc_spi *mps;
	काष्ठा spi_master *master;
	पूर्णांक ret;
	व्योम *tempp;
	काष्ठा clk *clk;

	master = spi_alloc_master(dev, माप *mps);
	अगर (master == शून्य)
		वापस -ENOMEM;

	dev_set_drvdata(dev, master);
	mps = spi_master_get_devdata(master);
	mps->type = (पूर्णांक)of_device_get_match_data(dev);
	mps->irq = irq;

	अगर (pdata == शून्य) अणु
		mps->cs_control = mpc512x_spi_cs_control;
	पूर्ण अन्यथा अणु
		mps->cs_control = pdata->cs_control;
		master->bus_num = pdata->bus_num;
		master->num_chipselect = pdata->max_chipselect;
	पूर्ण

	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LSB_FIRST;
	master->setup = mpc512x_psc_spi_setup;
	master->prepare_transfer_hardware = mpc512x_psc_spi_prep_xfer_hw;
	master->transfer_one_message = mpc512x_psc_spi_msg_xfer;
	master->unprepare_transfer_hardware = mpc512x_psc_spi_unprep_xfer_hw;
	master->cleanup = mpc512x_psc_spi_cleanup;
	master->dev.of_node = dev->of_node;

	tempp = devm_ioremap(dev, regaddr, size);
	अगर (!tempp) अणु
		dev_err(dev, "could not ioremap I/O port range\n");
		ret = -EFAULT;
		जाओ मुक्त_master;
	पूर्ण
	mps->psc = tempp;
	mps->fअगरo =
		(काष्ठा mpc512x_psc_fअगरo *)(tempp + माप(काष्ठा mpc52xx_psc));
	ret = devm_request_irq(dev, mps->irq, mpc512x_psc_spi_isr, IRQF_SHARED,
				"mpc512x-psc-spi", mps);
	अगर (ret)
		जाओ मुक्त_master;
	init_completion(&mps->txisrकरोne);

	clk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ मुक्त_master;
	पूर्ण
	ret = clk_prepare_enable(clk);
	अगर (ret)
		जाओ मुक्त_master;
	mps->clk_mclk = clk;
	mps->mclk_rate = clk_get_rate(clk);

	clk = devm_clk_get(dev, "ipg");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ मुक्त_mclk_घड़ी;
	पूर्ण
	ret = clk_prepare_enable(clk);
	अगर (ret)
		जाओ मुक्त_mclk_घड़ी;
	mps->clk_ipg = clk;

	ret = mpc512x_psc_spi_port_config(master, mps);
	अगर (ret < 0)
		जाओ मुक्त_ipg_घड़ी;

	ret = devm_spi_रेजिस्टर_master(dev, master);
	अगर (ret < 0)
		जाओ मुक्त_ipg_घड़ी;

	वापस ret;

मुक्त_ipg_घड़ी:
	clk_disable_unprepare(mps->clk_ipg);
मुक्त_mclk_घड़ी:
	clk_disable_unprepare(mps->clk_mclk);
मुक्त_master:
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल पूर्णांक mpc512x_psc_spi_करो_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mpc512x_psc_spi *mps = spi_master_get_devdata(master);

	clk_disable_unprepare(mps->clk_mclk);
	clk_disable_unprepare(mps->clk_ipg);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc512x_psc_spi_of_probe(काष्ठा platक्रमm_device *op)
अणु
	स्थिर u32 *regaddr_p;
	u64 regaddr64, size64;

	regaddr_p = of_get_address(op->dev.of_node, 0, &size64, शून्य);
	अगर (!regaddr_p) अणु
		dev_err(&op->dev, "Invalid PSC address\n");
		वापस -EINVAL;
	पूर्ण
	regaddr64 = of_translate_address(op->dev.of_node, regaddr_p);

	वापस mpc512x_psc_spi_करो_probe(&op->dev, (u32) regaddr64, (u32) size64,
				irq_of_parse_and_map(op->dev.of_node, 0));
पूर्ण

अटल पूर्णांक mpc512x_psc_spi_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	वापस mpc512x_psc_spi_करो_हटाओ(&op->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc512x_psc_spi_of_match[] = अणु
	अणु .compatible = "fsl,mpc5121-psc-spi", .data = (व्योम *)TYPE_MPC5121 पूर्ण,
	अणु .compatible = "fsl,mpc5125-psc-spi", .data = (व्योम *)TYPE_MPC5125 पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, mpc512x_psc_spi_of_match);

अटल काष्ठा platक्रमm_driver mpc512x_psc_spi_of_driver = अणु
	.probe = mpc512x_psc_spi_of_probe,
	.हटाओ = mpc512x_psc_spi_of_हटाओ,
	.driver = अणु
		.name = "mpc512x-psc-spi",
		.of_match_table = mpc512x_psc_spi_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mpc512x_psc_spi_of_driver);

MODULE_AUTHOR("John Rigby");
MODULE_DESCRIPTION("MPC512x PSC SPI Driver");
MODULE_LICENSE("GPL");
