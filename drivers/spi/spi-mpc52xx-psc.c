<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC52xx PSC in SPI mode driver.
 *
 * Maपूर्णांकainer: Dragos Carp
 *
 * Copyright (C) 2006 TOPTICA Photonics AG.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/completion.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/mpc52xx.h>
#समावेश <यंत्र/mpc52xx_psc.h>

#घोषणा MCLK 20000000 /* PSC port MClk in hz */

काष्ठा mpc52xx_psc_spi अणु
	/* fsl_spi_platक्रमm data */
	व्योम (*cs_control)(काष्ठा spi_device *spi, bool on);
	u32 sysclk;

	/* driver पूर्णांकernal data */
	काष्ठा mpc52xx_psc __iomem *psc;
	काष्ठा mpc52xx_psc_fअगरo __iomem *fअगरo;
	अचिन्हित पूर्णांक irq;
	u8 bits_per_word;
	u8 busy;

	काष्ठा work_काष्ठा work;

	काष्ठा list_head queue;
	spinlock_t lock;

	काष्ठा completion करोne;
पूर्ण;

/* controller state */
काष्ठा mpc52xx_psc_spi_cs अणु
	पूर्णांक bits_per_word;
	पूर्णांक speed_hz;
पूर्ण;

/* set घड़ी freq, घड़ी ramp, bits per work
 * अगर t is शून्य then reset the values to the शेष values
 */
अटल पूर्णांक mpc52xx_psc_spi_transfer_setup(काष्ठा spi_device *spi,
		काष्ठा spi_transfer *t)
अणु
	काष्ठा mpc52xx_psc_spi_cs *cs = spi->controller_state;

	cs->speed_hz = (t && t->speed_hz)
			? t->speed_hz : spi->max_speed_hz;
	cs->bits_per_word = (t && t->bits_per_word)
			? t->bits_per_word : spi->bits_per_word;
	cs->bits_per_word = ((cs->bits_per_word + 7) / 8) * 8;
	वापस 0;
पूर्ण

अटल व्योम mpc52xx_psc_spi_activate_cs(काष्ठा spi_device *spi)
अणु
	काष्ठा mpc52xx_psc_spi_cs *cs = spi->controller_state;
	काष्ठा mpc52xx_psc_spi *mps = spi_master_get_devdata(spi->master);
	काष्ठा mpc52xx_psc __iomem *psc = mps->psc;
	u32 sicr;
	u16 ccr;

	sicr = in_be32(&psc->sicr);

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
	out_be32(&psc->sicr, sicr);

	/* Set घड़ी frequency and bits per word
	 * Because psc->ccr is defined as 16bit रेजिस्टर instead of 32bit
	 * just set the lower byte of BitClkDiv
	 */
	ccr = in_be16((u16 __iomem *)&psc->ccr);
	ccr &= 0xFF00;
	अगर (cs->speed_hz)
		ccr |= (MCLK / cs->speed_hz - 1) & 0xFF;
	अन्यथा /* by शेष SPI Clk 1MHz */
		ccr |= (MCLK / 1000000 - 1) & 0xFF;
	out_be16((u16 __iomem *)&psc->ccr, ccr);
	mps->bits_per_word = cs->bits_per_word;

	अगर (mps->cs_control)
		mps->cs_control(spi, (spi->mode & SPI_CS_HIGH) ? 1 : 0);
पूर्ण

अटल व्योम mpc52xx_psc_spi_deactivate_cs(काष्ठा spi_device *spi)
अणु
	काष्ठा mpc52xx_psc_spi *mps = spi_master_get_devdata(spi->master);

	अगर (mps->cs_control)
		mps->cs_control(spi, (spi->mode & SPI_CS_HIGH) ? 0 : 1);
पूर्ण

#घोषणा MPC52xx_PSC_बफ_मानE (MPC52xx_PSC_RFNUM_MASK + 1)
/* wake up when 80% fअगरo full */
#घोषणा MPC52xx_PSC_RFALARM (MPC52xx_PSC_बफ_मानE * 20 / 100)

अटल पूर्णांक mpc52xx_psc_spi_transfer_rxtx(काष्ठा spi_device *spi,
						काष्ठा spi_transfer *t)
अणु
	काष्ठा mpc52xx_psc_spi *mps = spi_master_get_devdata(spi->master);
	काष्ठा mpc52xx_psc __iomem *psc = mps->psc;
	काष्ठा mpc52xx_psc_fअगरo __iomem *fअगरo = mps->fअगरo;
	अचिन्हित rb = 0;	/* number of bytes receieved */
	अचिन्हित sb = 0;	/* number of bytes sent */
	अचिन्हित अक्षर *rx_buf = (अचिन्हित अक्षर *)t->rx_buf;
	अचिन्हित अक्षर *tx_buf = (अचिन्हित अक्षर *)t->tx_buf;
	अचिन्हित rfalarm;
	अचिन्हित send_at_once = MPC52xx_PSC_बफ_मानE;
	अचिन्हित recv_at_once;
	पूर्णांक last_block = 0;

	अगर (!t->tx_buf && !t->rx_buf && t->len)
		वापस -EINVAL;

	/* enable transmiter/receiver */
	out_8(&psc->command, MPC52xx_PSC_TX_ENABLE | MPC52xx_PSC_RX_ENABLE);
	जबतक (rb < t->len) अणु
		अगर (t->len - rb > MPC52xx_PSC_बफ_मानE) अणु
			rfalarm = MPC52xx_PSC_RFALARM;
			last_block = 0;
		पूर्ण अन्यथा अणु
			send_at_once = t->len - sb;
			rfalarm = MPC52xx_PSC_बफ_मानE - (t->len - rb);
			last_block = 1;
		पूर्ण

		dev_dbg(&spi->dev, "send %d bytes...\n", send_at_once);
		क्रम (; send_at_once; sb++, send_at_once--) अणु
			/* set खातापूर्ण flag beक्रमe the last word is sent */
			अगर (send_at_once == 1 && last_block)
				out_8(&psc->ircr2, 0x01);

			अगर (tx_buf)
				out_8(&psc->mpc52xx_psc_buffer_8, tx_buf[sb]);
			अन्यथा
				out_8(&psc->mpc52xx_psc_buffer_8, 0);
		पूर्ण


		/* enable पूर्णांकerrupts and रुको क्रम wake up
		 * अगर just one byte is expected the Rx FIFO genererates no
		 * FFULL पूर्णांकerrupt, so activate the RxRDY पूर्णांकerrupt
		 */
		out_8(&psc->command, MPC52xx_PSC_SEL_MODE_REG_1);
		अगर (t->len - rb == 1) अणु
			out_8(&psc->mode, 0);
		पूर्ण अन्यथा अणु
			out_8(&psc->mode, MPC52xx_PSC_MODE_FFULL);
			out_be16(&fअगरo->rfalarm, rfalarm);
		पूर्ण
		out_be16(&psc->mpc52xx_psc_imr, MPC52xx_PSC_IMR_RXRDY);
		रुको_क्रम_completion(&mps->करोne);
		recv_at_once = in_be16(&fअगरo->rfnum);
		dev_dbg(&spi->dev, "%d bytes received\n", recv_at_once);

		send_at_once = recv_at_once;
		अगर (rx_buf) अणु
			क्रम (; recv_at_once; rb++, recv_at_once--)
				rx_buf[rb] = in_8(&psc->mpc52xx_psc_buffer_8);
		पूर्ण अन्यथा अणु
			क्रम (; recv_at_once; rb++, recv_at_once--)
				in_8(&psc->mpc52xx_psc_buffer_8);
		पूर्ण
	पूर्ण
	/* disable transmiter/receiver */
	out_8(&psc->command, MPC52xx_PSC_TX_DISABLE | MPC52xx_PSC_RX_DISABLE);

	वापस 0;
पूर्ण

अटल व्योम mpc52xx_psc_spi_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mpc52xx_psc_spi *mps =
		container_of(work, काष्ठा mpc52xx_psc_spi, work);

	spin_lock_irq(&mps->lock);
	mps->busy = 1;
	जबतक (!list_empty(&mps->queue)) अणु
		काष्ठा spi_message *m;
		काष्ठा spi_device *spi;
		काष्ठा spi_transfer *t = शून्य;
		अचिन्हित cs_change;
		पूर्णांक status;

		m = container_of(mps->queue.next, काष्ठा spi_message, queue);
		list_del_init(&m->queue);
		spin_unlock_irq(&mps->lock);

		spi = m->spi;
		cs_change = 1;
		status = 0;
		list_क्रम_each_entry (t, &m->transfers, transfer_list) अणु
			अगर (t->bits_per_word || t->speed_hz) अणु
				status = mpc52xx_psc_spi_transfer_setup(spi, t);
				अगर (status < 0)
					अवरोध;
			पूर्ण

			अगर (cs_change)
				mpc52xx_psc_spi_activate_cs(spi);
			cs_change = t->cs_change;

			status = mpc52xx_psc_spi_transfer_rxtx(spi, t);
			अगर (status)
				अवरोध;
			m->actual_length += t->len;

			spi_transfer_delay_exec(t);

			अगर (cs_change)
				mpc52xx_psc_spi_deactivate_cs(spi);
		पूर्ण

		m->status = status;
		अगर (m->complete)
			m->complete(m->context);

		अगर (status || !cs_change)
			mpc52xx_psc_spi_deactivate_cs(spi);

		mpc52xx_psc_spi_transfer_setup(spi, शून्य);

		spin_lock_irq(&mps->lock);
	पूर्ण
	mps->busy = 0;
	spin_unlock_irq(&mps->lock);
पूर्ण

अटल पूर्णांक mpc52xx_psc_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा mpc52xx_psc_spi *mps = spi_master_get_devdata(spi->master);
	काष्ठा mpc52xx_psc_spi_cs *cs = spi->controller_state;
	अचिन्हित दीर्घ flags;

	अगर (spi->bits_per_word%8)
		वापस -EINVAL;

	अगर (!cs) अणु
		cs = kzalloc(माप *cs, GFP_KERNEL);
		अगर (!cs)
			वापस -ENOMEM;
		spi->controller_state = cs;
	पूर्ण

	cs->bits_per_word = spi->bits_per_word;
	cs->speed_hz = spi->max_speed_hz;

	spin_lock_irqsave(&mps->lock, flags);
	अगर (!mps->busy)
		mpc52xx_psc_spi_deactivate_cs(spi);
	spin_unlock_irqrestore(&mps->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc52xx_psc_spi_transfer(काष्ठा spi_device *spi,
		काष्ठा spi_message *m)
अणु
	काष्ठा mpc52xx_psc_spi *mps = spi_master_get_devdata(spi->master);
	अचिन्हित दीर्घ flags;

	m->actual_length = 0;
	m->status = -EINPROGRESS;

	spin_lock_irqsave(&mps->lock, flags);
	list_add_tail(&m->queue, &mps->queue);
	schedule_work(&mps->work);
	spin_unlock_irqrestore(&mps->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम mpc52xx_psc_spi_cleanup(काष्ठा spi_device *spi)
अणु
	kमुक्त(spi->controller_state);
पूर्ण

अटल पूर्णांक mpc52xx_psc_spi_port_config(पूर्णांक psc_id, काष्ठा mpc52xx_psc_spi *mps)
अणु
	काष्ठा mpc52xx_psc __iomem *psc = mps->psc;
	काष्ठा mpc52xx_psc_fअगरo __iomem *fअगरo = mps->fअगरo;
	u32 mclken_भाग;
	पूर्णांक ret;

	/* शेष sysclk is 512MHz */
	mclken_भाग = (mps->sysclk ? mps->sysclk : 512000000) / MCLK;
	ret = mpc52xx_set_psc_clkभाग(psc_id, mclken_भाग);
	अगर (ret)
		वापस ret;

	/* Reset the PSC पूर्णांकo a known state */
	out_8(&psc->command, MPC52xx_PSC_RST_RX);
	out_8(&psc->command, MPC52xx_PSC_RST_TX);
	out_8(&psc->command, MPC52xx_PSC_TX_DISABLE | MPC52xx_PSC_RX_DISABLE);

	/* Disable पूर्णांकerrupts, पूर्णांकerrupts are based on alarm level */
	out_be16(&psc->mpc52xx_psc_imr, 0);
	out_8(&psc->command, MPC52xx_PSC_SEL_MODE_REG_1);
	out_8(&fअगरo->rfcntl, 0);
	out_8(&psc->mode, MPC52xx_PSC_MODE_FFULL);

	/* Configure 8bit codec mode as a SPI master and use खातापूर्ण flags */
	/* SICR_SIM_CODEC8|SICR_GENCLK|SICR_SPI|SICR_MSTR|SICR_USEखातापूर्ण */
	out_be32(&psc->sicr, 0x0180C800);
	out_be16((u16 __iomem *)&psc->ccr, 0x070F); /* शेष SPI Clk 1MHz */

	/* Set 2ms DTL delay */
	out_8(&psc->ctur, 0x00);
	out_8(&psc->ctlr, 0x84);

	mps->bits_per_word = 8;

	वापस 0;
पूर्ण

अटल irqवापस_t mpc52xx_psc_spi_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mpc52xx_psc_spi *mps = (काष्ठा mpc52xx_psc_spi *)dev_id;
	काष्ठा mpc52xx_psc __iomem *psc = mps->psc;

	/* disable पूर्णांकerrupt and wake up the work queue */
	अगर (in_be16(&psc->mpc52xx_psc_isr) & MPC52xx_PSC_IMR_RXRDY) अणु
		out_be16(&psc->mpc52xx_psc_imr, 0);
		complete(&mps->करोne);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

/* bus_num is used only क्रम the हाल dev->platक्रमm_data == शून्य */
अटल पूर्णांक mpc52xx_psc_spi_करो_probe(काष्ठा device *dev, u32 regaddr,
				u32 size, अचिन्हित पूर्णांक irq, s16 bus_num)
अणु
	काष्ठा fsl_spi_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा mpc52xx_psc_spi *mps;
	काष्ठा spi_master *master;
	पूर्णांक ret;

	master = spi_alloc_master(dev, माप *mps);
	अगर (master == शून्य)
		वापस -ENOMEM;

	dev_set_drvdata(dev, master);
	mps = spi_master_get_devdata(master);

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LSB_FIRST;

	mps->irq = irq;
	अगर (pdata == शून्य) अणु
		dev_warn(dev,
			 "probe called without platform data, no cs_control function will be called\n");
		mps->cs_control = शून्य;
		mps->sysclk = 0;
		master->bus_num = bus_num;
		master->num_chipselect = 255;
	पूर्ण अन्यथा अणु
		mps->cs_control = pdata->cs_control;
		mps->sysclk = pdata->sysclk;
		master->bus_num = pdata->bus_num;
		master->num_chipselect = pdata->max_chipselect;
	पूर्ण
	master->setup = mpc52xx_psc_spi_setup;
	master->transfer = mpc52xx_psc_spi_transfer;
	master->cleanup = mpc52xx_psc_spi_cleanup;
	master->dev.of_node = dev->of_node;

	mps->psc = ioremap(regaddr, size);
	अगर (!mps->psc) अणु
		dev_err(dev, "could not ioremap I/O port range\n");
		ret = -EFAULT;
		जाओ मुक्त_master;
	पूर्ण
	/* On the 5200, fअगरo regs are immediately ajacent to the psc regs */
	mps->fअगरo = ((व्योम __iomem *)mps->psc) + माप(काष्ठा mpc52xx_psc);

	ret = request_irq(mps->irq, mpc52xx_psc_spi_isr, 0, "mpc52xx-psc-spi",
				mps);
	अगर (ret)
		जाओ मुक्त_master;

	ret = mpc52xx_psc_spi_port_config(master->bus_num, mps);
	अगर (ret < 0) अणु
		dev_err(dev, "can't configure PSC! Is it capable of SPI?\n");
		जाओ मुक्त_irq;
	पूर्ण

	spin_lock_init(&mps->lock);
	init_completion(&mps->करोne);
	INIT_WORK(&mps->work, mpc52xx_psc_spi_work);
	INIT_LIST_HEAD(&mps->queue);

	ret = spi_रेजिस्टर_master(master);
	अगर (ret < 0)
		जाओ मुक्त_irq;

	वापस ret;

मुक्त_irq:
	मुक्त_irq(mps->irq, mps);
मुक्त_master:
	अगर (mps->psc)
		iounmap(mps->psc);
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल पूर्णांक mpc52xx_psc_spi_of_probe(काष्ठा platक्रमm_device *op)
अणु
	स्थिर u32 *regaddr_p;
	u64 regaddr64, size64;
	s16 id = -1;

	regaddr_p = of_get_address(op->dev.of_node, 0, &size64, शून्य);
	अगर (!regaddr_p) अणु
		dev_err(&op->dev, "Invalid PSC address\n");
		वापस -EINVAL;
	पूर्ण
	regaddr64 = of_translate_address(op->dev.of_node, regaddr_p);

	/* get PSC id (1..6, used by port_config) */
	अगर (op->dev.platक्रमm_data == शून्य) अणु
		स्थिर u32 *psc_nump;

		psc_nump = of_get_property(op->dev.of_node, "cell-index", शून्य);
		अगर (!psc_nump || *psc_nump > 5) अणु
			dev_err(&op->dev, "Invalid cell-index property\n");
			वापस -EINVAL;
		पूर्ण
		id = *psc_nump + 1;
	पूर्ण

	वापस mpc52xx_psc_spi_करो_probe(&op->dev, (u32)regaddr64, (u32)size64,
				irq_of_parse_and_map(op->dev.of_node, 0), id);
पूर्ण

अटल पूर्णांक mpc52xx_psc_spi_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा spi_master *master = spi_master_get(platक्रमm_get_drvdata(op));
	काष्ठा mpc52xx_psc_spi *mps = spi_master_get_devdata(master);

	flush_work(&mps->work);
	spi_unरेजिस्टर_master(master);
	मुक्त_irq(mps->irq, mps);
	अगर (mps->psc)
		iounmap(mps->psc);
	spi_master_put(master);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc52xx_psc_spi_of_match[] = अणु
	अणु .compatible = "fsl,mpc5200-psc-spi", पूर्ण,
	अणु .compatible = "mpc5200-psc-spi", पूर्ण, /* old */
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, mpc52xx_psc_spi_of_match);

अटल काष्ठा platक्रमm_driver mpc52xx_psc_spi_of_driver = अणु
	.probe = mpc52xx_psc_spi_of_probe,
	.हटाओ = mpc52xx_psc_spi_of_हटाओ,
	.driver = अणु
		.name = "mpc52xx-psc-spi",
		.of_match_table = mpc52xx_psc_spi_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mpc52xx_psc_spi_of_driver);

MODULE_AUTHOR("Dragos Carp");
MODULE_DESCRIPTION("MPC52xx PSC SPI Driver");
MODULE_LICENSE("GPL");
