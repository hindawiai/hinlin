<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale SPI controller driver.
 *
 * Maपूर्णांकainer: Kumar Gala
 *
 * Copyright (C) 2006 Polycom, Inc.
 * Copyright 2010 Freescale Semiconductor, Inc.
 *
 * CPM SPI and QE buffer descriptors mode support:
 * Copyright (c) 2009  MontaVista Software, Inc.
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * GRLIB support:
 * Copyright (c) 2012 Aeroflex Gaisler AB.
 * Author: Andreas Larsson <andreas@gaisler.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/types.h>

#अगर_घोषित CONFIG_FSL_SOC
#समावेश <sysdev/fsl_soc.h>
#पूर्ण_अगर

/* Specअगरic to the MPC8306/MPC8309 */
#घोषणा IMMR_SPI_CS_OFFSET 0x14c
#घोषणा SPI_BOOT_SEL_BIT   0x80000000

#समावेश "spi-fsl-lib.h"
#समावेश "spi-fsl-cpm.h"
#समावेश "spi-fsl-spi.h"

#घोषणा TYPE_FSL	0
#घोषणा TYPE_GRLIB	1

काष्ठा fsl_spi_match_data अणु
	पूर्णांक type;
पूर्ण;

अटल काष्ठा fsl_spi_match_data of_fsl_spi_fsl_config = अणु
	.type = TYPE_FSL,
पूर्ण;

अटल काष्ठा fsl_spi_match_data of_fsl_spi_grlib_config = अणु
	.type = TYPE_GRLIB,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_fsl_spi_match[] = अणु
	अणु
		.compatible = "fsl,spi",
		.data = &of_fsl_spi_fsl_config,
	पूर्ण,
	अणु
		.compatible = "aeroflexgaisler,spictrl",
		.data = &of_fsl_spi_grlib_config,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_fsl_spi_match);

अटल पूर्णांक fsl_spi_get_type(काष्ठा device *dev)
अणु
	स्थिर काष्ठा of_device_id *match;

	अगर (dev->of_node) अणु
		match = of_match_node(of_fsl_spi_match, dev->of_node);
		अगर (match && match->data)
			वापस ((काष्ठा fsl_spi_match_data *)match->data)->type;
	पूर्ण
	वापस TYPE_FSL;
पूर्ण

अटल व्योम fsl_spi_change_mode(काष्ठा spi_device *spi)
अणु
	काष्ठा mpc8xxx_spi *mspi = spi_master_get_devdata(spi->master);
	काष्ठा spi_mpc8xxx_cs *cs = spi->controller_state;
	काष्ठा fsl_spi_reg __iomem *reg_base = mspi->reg_base;
	__be32 __iomem *mode = &reg_base->mode;
	अचिन्हित दीर्घ flags;

	अगर (cs->hw_mode == mpc8xxx_spi_पढ़ो_reg(mode))
		वापस;

	/* Turn off IRQs locally to minimize समय that SPI is disabled. */
	local_irq_save(flags);

	/* Turn off SPI unit prior changing mode */
	mpc8xxx_spi_ग_लिखो_reg(mode, cs->hw_mode & ~SPMODE_ENABLE);

	/* When in CPM mode, we need to reinit tx and rx. */
	अगर (mspi->flags & SPI_CPM_MODE) अणु
		fsl_spi_cpm_reinit_txrx(mspi);
	पूर्ण
	mpc8xxx_spi_ग_लिखो_reg(mode, cs->hw_mode);
	local_irq_restore(flags);
पूर्ण

अटल व्योम fsl_spi_chipselect(काष्ठा spi_device *spi, पूर्णांक value)
अणु
	काष्ठा mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(spi->master);
	काष्ठा fsl_spi_platक्रमm_data *pdata;
	काष्ठा spi_mpc8xxx_cs	*cs = spi->controller_state;

	pdata = spi->dev.parent->parent->platक्रमm_data;

	अगर (value == BITBANG_CS_INACTIVE) अणु
		अगर (pdata->cs_control)
			pdata->cs_control(spi, false);
	पूर्ण

	अगर (value == BITBANG_CS_ACTIVE) अणु
		mpc8xxx_spi->rx_shअगरt = cs->rx_shअगरt;
		mpc8xxx_spi->tx_shअगरt = cs->tx_shअगरt;
		mpc8xxx_spi->get_rx = cs->get_rx;
		mpc8xxx_spi->get_tx = cs->get_tx;

		fsl_spi_change_mode(spi);

		अगर (pdata->cs_control)
			pdata->cs_control(spi, true);
	पूर्ण
पूर्ण

अटल व्योम fsl_spi_qe_cpu_set_shअगरts(u32 *rx_shअगरt, u32 *tx_shअगरt,
				      पूर्णांक bits_per_word, पूर्णांक msb_first)
अणु
	*rx_shअगरt = 0;
	*tx_shअगरt = 0;
	अगर (msb_first) अणु
		अगर (bits_per_word <= 8) अणु
			*rx_shअगरt = 16;
			*tx_shअगरt = 24;
		पूर्ण अन्यथा अगर (bits_per_word <= 16) अणु
			*rx_shअगरt = 16;
			*tx_shअगरt = 16;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bits_per_word <= 8)
			*rx_shअगरt = 8;
	पूर्ण
पूर्ण

अटल व्योम fsl_spi_grlib_set_shअगरts(u32 *rx_shअगरt, u32 *tx_shअगरt,
				     पूर्णांक bits_per_word, पूर्णांक msb_first)
अणु
	*rx_shअगरt = 0;
	*tx_shअगरt = 0;
	अगर (bits_per_word <= 16) अणु
		अगर (msb_first) अणु
			*rx_shअगरt = 16; /* LSB in bit 16 */
			*tx_shअगरt = 32 - bits_per_word; /* MSB in bit 31 */
		पूर्ण अन्यथा अणु
			*rx_shअगरt = 16 - bits_per_word; /* MSB in bit 15 */
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mspi_apply_cpu_mode_quirks(काष्ठा spi_mpc8xxx_cs *cs,
				काष्ठा spi_device *spi,
				काष्ठा mpc8xxx_spi *mpc8xxx_spi,
				पूर्णांक bits_per_word)
अणु
	cs->rx_shअगरt = 0;
	cs->tx_shअगरt = 0;
	अगर (bits_per_word <= 8) अणु
		cs->get_rx = mpc8xxx_spi_rx_buf_u8;
		cs->get_tx = mpc8xxx_spi_tx_buf_u8;
	पूर्ण अन्यथा अगर (bits_per_word <= 16) अणु
		cs->get_rx = mpc8xxx_spi_rx_buf_u16;
		cs->get_tx = mpc8xxx_spi_tx_buf_u16;
	पूर्ण अन्यथा अगर (bits_per_word <= 32) अणु
		cs->get_rx = mpc8xxx_spi_rx_buf_u32;
		cs->get_tx = mpc8xxx_spi_tx_buf_u32;
	पूर्ण अन्यथा
		वापस -EINVAL;

	अगर (mpc8xxx_spi->set_shअगरts)
		mpc8xxx_spi->set_shअगरts(&cs->rx_shअगरt, &cs->tx_shअगरt,
					bits_per_word,
					!(spi->mode & SPI_LSB_FIRST));

	mpc8xxx_spi->rx_shअगरt = cs->rx_shअगरt;
	mpc8xxx_spi->tx_shअगरt = cs->tx_shअगरt;
	mpc8xxx_spi->get_rx = cs->get_rx;
	mpc8xxx_spi->get_tx = cs->get_tx;

	वापस bits_per_word;
पूर्ण

अटल पूर्णांक mspi_apply_qe_mode_quirks(काष्ठा spi_mpc8xxx_cs *cs,
				काष्ठा spi_device *spi,
				पूर्णांक bits_per_word)
अणु
	/* QE uses Little Endian क्रम words > 8
	 * so transक्रमm all words > 8 पूर्णांकo 8 bits
	 * Unक्रमtnatly that करोesn't work क्रम LSB so
	 * reject these क्रम now */
	/* Note: 32 bits word, LSB works अगरf
	 * tfcr/rfcr is set to CPMFCR_GBL */
	अगर (spi->mode & SPI_LSB_FIRST &&
	    bits_per_word > 8)
		वापस -EINVAL;
	अगर (bits_per_word > 8)
		वापस 8; /* pretend its 8 bits */
	वापस bits_per_word;
पूर्ण

अटल पूर्णांक fsl_spi_setup_transfer(काष्ठा spi_device *spi,
					काष्ठा spi_transfer *t)
अणु
	काष्ठा mpc8xxx_spi *mpc8xxx_spi;
	पूर्णांक bits_per_word = 0;
	u8 pm;
	u32 hz = 0;
	काष्ठा spi_mpc8xxx_cs	*cs = spi->controller_state;

	mpc8xxx_spi = spi_master_get_devdata(spi->master);

	अगर (t) अणु
		bits_per_word = t->bits_per_word;
		hz = t->speed_hz;
	पूर्ण

	/* spi_transfer level calls that work per-word */
	अगर (!bits_per_word)
		bits_per_word = spi->bits_per_word;

	अगर (!hz)
		hz = spi->max_speed_hz;

	अगर (!(mpc8xxx_spi->flags & SPI_CPM_MODE))
		bits_per_word = mspi_apply_cpu_mode_quirks(cs, spi,
							   mpc8xxx_spi,
							   bits_per_word);
	अन्यथा अगर (mpc8xxx_spi->flags & SPI_QE)
		bits_per_word = mspi_apply_qe_mode_quirks(cs, spi,
							  bits_per_word);

	अगर (bits_per_word < 0)
		वापस bits_per_word;

	अगर (bits_per_word == 32)
		bits_per_word = 0;
	अन्यथा
		bits_per_word = bits_per_word - 1;

	/* mask out bits we are going to set */
	cs->hw_mode &= ~(SPMODE_LEN(0xF) | SPMODE_DIV16
				  | SPMODE_PM(0xF));

	cs->hw_mode |= SPMODE_LEN(bits_per_word);

	अगर ((mpc8xxx_spi->spibrg / hz) > 64) अणु
		cs->hw_mode |= SPMODE_DIV16;
		pm = (mpc8xxx_spi->spibrg - 1) / (hz * 64) + 1;
		WARN_ONCE(pm > 16,
			  "%s: Requested speed is too low: %d Hz. Will use %d Hz instead.\n",
			  dev_name(&spi->dev), hz, mpc8xxx_spi->spibrg / 1024);
		अगर (pm > 16)
			pm = 16;
	पूर्ण अन्यथा अणु
		pm = (mpc8xxx_spi->spibrg - 1) / (hz * 4) + 1;
	पूर्ण
	अगर (pm)
		pm--;

	cs->hw_mode |= SPMODE_PM(pm);

	fsl_spi_change_mode(spi);
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_spi_cpu_bufs(काष्ठा mpc8xxx_spi *mspi,
				काष्ठा spi_transfer *t, अचिन्हित पूर्णांक len)
अणु
	u32 word;
	काष्ठा fsl_spi_reg __iomem *reg_base = mspi->reg_base;

	mspi->count = len;

	/* enable rx पूर्णांकs */
	mpc8xxx_spi_ग_लिखो_reg(&reg_base->mask, SPIM_NE);

	/* transmit word */
	word = mspi->get_tx(mspi);
	mpc8xxx_spi_ग_लिखो_reg(&reg_base->transmit, word);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_spi_bufs(काष्ठा spi_device *spi, काष्ठा spi_transfer *t,
			    bool is_dma_mapped)
अणु
	काष्ठा mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(spi->master);
	काष्ठा fsl_spi_reg __iomem *reg_base;
	अचिन्हित पूर्णांक len = t->len;
	u8 bits_per_word;
	पूर्णांक ret;

	reg_base = mpc8xxx_spi->reg_base;
	bits_per_word = spi->bits_per_word;
	अगर (t->bits_per_word)
		bits_per_word = t->bits_per_word;

	अगर (bits_per_word > 8) अणु
		/* invalid length? */
		अगर (len & 1)
			वापस -EINVAL;
		len /= 2;
	पूर्ण
	अगर (bits_per_word > 16) अणु
		/* invalid length? */
		अगर (len & 1)
			वापस -EINVAL;
		len /= 2;
	पूर्ण

	mpc8xxx_spi->tx = t->tx_buf;
	mpc8xxx_spi->rx = t->rx_buf;

	reinit_completion(&mpc8xxx_spi->करोne);

	अगर (mpc8xxx_spi->flags & SPI_CPM_MODE)
		ret = fsl_spi_cpm_bufs(mpc8xxx_spi, t, is_dma_mapped);
	अन्यथा
		ret = fsl_spi_cpu_bufs(mpc8xxx_spi, t, len);
	अगर (ret)
		वापस ret;

	रुको_क्रम_completion(&mpc8xxx_spi->करोne);

	/* disable rx पूर्णांकs */
	mpc8xxx_spi_ग_लिखो_reg(&reg_base->mask, 0);

	अगर (mpc8xxx_spi->flags & SPI_CPM_MODE)
		fsl_spi_cpm_bufs_complete(mpc8xxx_spi);

	वापस mpc8xxx_spi->count;
पूर्ण

अटल पूर्णांक fsl_spi_करो_one_msg(काष्ठा spi_master *master,
			      काष्ठा spi_message *m)
अणु
	काष्ठा mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = m->spi;
	काष्ठा spi_transfer *t, *first;
	अचिन्हित पूर्णांक cs_change;
	स्थिर पूर्णांक nsecs = 50;
	पूर्णांक status, last_bpw;

	/*
	 * In CPU mode, optimize large byte transfers to use larger
	 * bits_per_word values to reduce number of पूर्णांकerrupts taken.
	 */
	अगर (!(mpc8xxx_spi->flags & SPI_CPM_MODE)) अणु
		list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
			अगर (t->len < 256 || t->bits_per_word != 8)
				जारी;
			अगर ((t->len & 3) == 0)
				t->bits_per_word = 32;
			अन्यथा अगर ((t->len & 1) == 0)
				t->bits_per_word = 16;
		पूर्ण
	पूर्ण

	/* Don't allow changes अगर CS is active */
	cs_change = 1;
	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		अगर (cs_change)
			first = t;
		cs_change = t->cs_change;
		अगर (first->speed_hz != t->speed_hz) अणु
			dev_err(&spi->dev,
				"speed_hz cannot change while CS is active\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	last_bpw = -1;
	cs_change = 1;
	status = -EINVAL;
	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		अगर (cs_change || last_bpw != t->bits_per_word)
			status = fsl_spi_setup_transfer(spi, t);
		अगर (status < 0)
			अवरोध;
		last_bpw = t->bits_per_word;

		अगर (cs_change) अणु
			fsl_spi_chipselect(spi, BITBANG_CS_ACTIVE);
			ndelay(nsecs);
		पूर्ण
		cs_change = t->cs_change;
		अगर (t->len)
			status = fsl_spi_bufs(spi, t, m->is_dma_mapped);
		अगर (status) अणु
			status = -EMSGSIZE;
			अवरोध;
		पूर्ण
		m->actual_length += t->len;

		spi_transfer_delay_exec(t);

		अगर (cs_change) अणु
			ndelay(nsecs);
			fsl_spi_chipselect(spi, BITBANG_CS_INACTIVE);
			ndelay(nsecs);
		पूर्ण
	पूर्ण

	m->status = status;

	अगर (status || !cs_change) अणु
		ndelay(nsecs);
		fsl_spi_chipselect(spi, BITBANG_CS_INACTIVE);
	पूर्ण

	fsl_spi_setup_transfer(spi, शून्य);
	spi_finalize_current_message(master);
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा mpc8xxx_spi *mpc8xxx_spi;
	काष्ठा fsl_spi_reg __iomem *reg_base;
	bool initial_setup = false;
	पूर्णांक retval;
	u32 hw_mode;
	काष्ठा spi_mpc8xxx_cs *cs = spi_get_ctldata(spi);

	अगर (!spi->max_speed_hz)
		वापस -EINVAL;

	अगर (!cs) अणु
		cs = kzalloc(माप(*cs), GFP_KERNEL);
		अगर (!cs)
			वापस -ENOMEM;
		spi_set_ctldata(spi, cs);
		initial_setup = true;
	पूर्ण
	mpc8xxx_spi = spi_master_get_devdata(spi->master);

	reg_base = mpc8xxx_spi->reg_base;

	hw_mode = cs->hw_mode; /* Save original settings */
	cs->hw_mode = mpc8xxx_spi_पढ़ो_reg(&reg_base->mode);
	/* mask out bits we are going to set */
	cs->hw_mode &= ~(SPMODE_CP_BEGIN_EDGECLK | SPMODE_CI_INACTIVEHIGH
			 | SPMODE_REV | SPMODE_LOOP);

	अगर (spi->mode & SPI_CPHA)
		cs->hw_mode |= SPMODE_CP_BEGIN_EDGECLK;
	अगर (spi->mode & SPI_CPOL)
		cs->hw_mode |= SPMODE_CI_INACTIVEHIGH;
	अगर (!(spi->mode & SPI_LSB_FIRST))
		cs->hw_mode |= SPMODE_REV;
	अगर (spi->mode & SPI_LOOP)
		cs->hw_mode |= SPMODE_LOOP;

	retval = fsl_spi_setup_transfer(spi, शून्य);
	अगर (retval < 0) अणु
		cs->hw_mode = hw_mode; /* Restore settings */
		अगर (initial_setup)
			kमुक्त(cs);
		वापस retval;
	पूर्ण

	/* Initialize chipselect - might be active क्रम SPI_CS_HIGH mode */
	fsl_spi_chipselect(spi, BITBANG_CS_INACTIVE);

	वापस 0;
पूर्ण

अटल व्योम fsl_spi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_mpc8xxx_cs *cs = spi_get_ctldata(spi);

	kमुक्त(cs);
	spi_set_ctldata(spi, शून्य);
पूर्ण

अटल व्योम fsl_spi_cpu_irq(काष्ठा mpc8xxx_spi *mspi, u32 events)
अणु
	काष्ठा fsl_spi_reg __iomem *reg_base = mspi->reg_base;

	/* We need handle RX first */
	अगर (events & SPIE_NE) अणु
		u32 rx_data = mpc8xxx_spi_पढ़ो_reg(&reg_base->receive);

		अगर (mspi->rx)
			mspi->get_rx(rx_data, mspi);
	पूर्ण

	अगर ((events & SPIE_NF) == 0)
		/* spin until TX is करोne */
		जबतक (((events =
			mpc8xxx_spi_पढ़ो_reg(&reg_base->event)) &
						SPIE_NF) == 0)
			cpu_relax();

	/* Clear the events */
	mpc8xxx_spi_ग_लिखो_reg(&reg_base->event, events);

	mspi->count -= 1;
	अगर (mspi->count) अणु
		u32 word = mspi->get_tx(mspi);

		mpc8xxx_spi_ग_लिखो_reg(&reg_base->transmit, word);
	पूर्ण अन्यथा अणु
		complete(&mspi->करोne);
	पूर्ण
पूर्ण

अटल irqवापस_t fsl_spi_irq(s32 irq, व्योम *context_data)
अणु
	काष्ठा mpc8xxx_spi *mspi = context_data;
	irqवापस_t ret = IRQ_NONE;
	u32 events;
	काष्ठा fsl_spi_reg __iomem *reg_base = mspi->reg_base;

	/* Get पूर्णांकerrupt events(tx/rx) */
	events = mpc8xxx_spi_पढ़ो_reg(&reg_base->event);
	अगर (events)
		ret = IRQ_HANDLED;

	dev_dbg(mspi->dev, "%s: events %x\n", __func__, events);

	अगर (mspi->flags & SPI_CPM_MODE)
		fsl_spi_cpm_irq(mspi, events);
	अन्यथा
		fsl_spi_cpu_irq(mspi, events);

	वापस ret;
पूर्ण

अटल व्योम fsl_spi_grlib_cs_control(काष्ठा spi_device *spi, bool on)
अणु
	काष्ठा mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(spi->master);
	काष्ठा fsl_spi_reg __iomem *reg_base = mpc8xxx_spi->reg_base;
	u32 slvsel;
	u16 cs = spi->chip_select;

	अगर (spi->cs_gpiod) अणु
		gpiod_set_value(spi->cs_gpiod, on);
	पूर्ण अन्यथा अगर (cs < mpc8xxx_spi->native_chipselects) अणु
		slvsel = mpc8xxx_spi_पढ़ो_reg(&reg_base->slvsel);
		slvsel = on ? (slvsel | (1 << cs)) : (slvsel & ~(1 << cs));
		mpc8xxx_spi_ग_लिखो_reg(&reg_base->slvsel, slvsel);
	पूर्ण
पूर्ण

अटल व्योम fsl_spi_grlib_probe(काष्ठा device *dev)
अणु
	काष्ठा fsl_spi_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(master);
	काष्ठा fsl_spi_reg __iomem *reg_base = mpc8xxx_spi->reg_base;
	पूर्णांक mbits;
	u32 capabilities;

	capabilities = mpc8xxx_spi_पढ़ो_reg(&reg_base->cap);

	mpc8xxx_spi->set_shअगरts = fsl_spi_grlib_set_shअगरts;
	mbits = SPCAP_MAXWLEN(capabilities);
	अगर (mbits)
		mpc8xxx_spi->max_bits_per_word = mbits + 1;

	mpc8xxx_spi->native_chipselects = 0;
	अगर (SPCAP_SSEN(capabilities)) अणु
		mpc8xxx_spi->native_chipselects = SPCAP_SSSZ(capabilities);
		mpc8xxx_spi_ग_लिखो_reg(&reg_base->slvsel, 0xffffffff);
	पूर्ण
	master->num_chipselect = mpc8xxx_spi->native_chipselects;
	pdata->cs_control = fsl_spi_grlib_cs_control;
पूर्ण

अटल काष्ठा spi_master *fsl_spi_probe(काष्ठा device *dev,
		काष्ठा resource *mem, अचिन्हित पूर्णांक irq)
अणु
	काष्ठा fsl_spi_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा spi_master *master;
	काष्ठा mpc8xxx_spi *mpc8xxx_spi;
	काष्ठा fsl_spi_reg __iomem *reg_base;
	u32 regval;
	पूर्णांक ret = 0;

	master = spi_alloc_master(dev, माप(काष्ठा mpc8xxx_spi));
	अगर (master == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	dev_set_drvdata(dev, master);

	mpc8xxx_spi_probe(dev, mem, irq);

	master->setup = fsl_spi_setup;
	master->cleanup = fsl_spi_cleanup;
	master->transfer_one_message = fsl_spi_करो_one_msg;
	master->use_gpio_descriptors = true;

	mpc8xxx_spi = spi_master_get_devdata(master);
	mpc8xxx_spi->max_bits_per_word = 32;
	mpc8xxx_spi->type = fsl_spi_get_type(dev);

	ret = fsl_spi_cpm_init(mpc8xxx_spi);
	अगर (ret)
		जाओ err_cpm_init;

	mpc8xxx_spi->reg_base = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(mpc8xxx_spi->reg_base)) अणु
		ret = PTR_ERR(mpc8xxx_spi->reg_base);
		जाओ err_probe;
	पूर्ण

	अगर (mpc8xxx_spi->type == TYPE_GRLIB)
		fsl_spi_grlib_probe(dev);

	master->bits_per_word_mask =
		(SPI_BPW_RANGE_MASK(4, 16) | SPI_BPW_MASK(32)) &
		SPI_BPW_RANGE_MASK(1, mpc8xxx_spi->max_bits_per_word);

	अगर (mpc8xxx_spi->flags & SPI_QE_CPU_MODE)
		mpc8xxx_spi->set_shअगरts = fsl_spi_qe_cpu_set_shअगरts;

	अगर (mpc8xxx_spi->set_shअगरts)
		/* 8 bits per word and MSB first */
		mpc8xxx_spi->set_shअगरts(&mpc8xxx_spi->rx_shअगरt,
					&mpc8xxx_spi->tx_shअगरt, 8, 1);

	/* Register क्रम SPI Interrupt */
	ret = devm_request_irq(dev, mpc8xxx_spi->irq, fsl_spi_irq,
			       0, "fsl_spi", mpc8xxx_spi);

	अगर (ret != 0)
		जाओ err_probe;

	reg_base = mpc8xxx_spi->reg_base;

	/* SPI controller initializations */
	mpc8xxx_spi_ग_लिखो_reg(&reg_base->mode, 0);
	mpc8xxx_spi_ग_लिखो_reg(&reg_base->mask, 0);
	mpc8xxx_spi_ग_लिखो_reg(&reg_base->command, 0);
	mpc8xxx_spi_ग_लिखो_reg(&reg_base->event, 0xffffffff);

	/* Enable SPI पूर्णांकerface */
	regval = pdata->initial_spmode | SPMODE_INIT_VAL | SPMODE_ENABLE;
	अगर (mpc8xxx_spi->max_bits_per_word < 8) अणु
		regval &= ~SPMODE_LEN(0xF);
		regval |= SPMODE_LEN(mpc8xxx_spi->max_bits_per_word - 1);
	पूर्ण
	अगर (mpc8xxx_spi->flags & SPI_QE_CPU_MODE)
		regval |= SPMODE_OP;

	mpc8xxx_spi_ग_लिखो_reg(&reg_base->mode, regval);

	ret = devm_spi_रेजिस्टर_master(dev, master);
	अगर (ret < 0)
		जाओ err_probe;

	dev_info(dev, "at 0x%p (irq = %d), %s mode\n", reg_base,
		 mpc8xxx_spi->irq, mpc8xxx_spi_strmode(mpc8xxx_spi->flags));

	वापस master;

err_probe:
	fsl_spi_cpm_मुक्त(mpc8xxx_spi);
err_cpm_init:
	spi_master_put(master);
err:
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम fsl_spi_cs_control(काष्ठा spi_device *spi, bool on)
अणु
	अगर (spi->cs_gpiod) अणु
		gpiod_set_value(spi->cs_gpiod, on);
	पूर्ण अन्यथा अणु
		काष्ठा device *dev = spi->dev.parent->parent;
		काष्ठा fsl_spi_platक्रमm_data *pdata = dev_get_platdata(dev);
		काष्ठा mpc8xxx_spi_probe_info *pinfo = to_of_pinfo(pdata);

		अगर (WARN_ON_ONCE(!pinfo->immr_spi_cs))
			वापस;
		ioग_लिखो32be(on ? 0 : SPI_BOOT_SEL_BIT, pinfo->immr_spi_cs);
	पूर्ण
पूर्ण

अटल पूर्णांक of_fsl_spi_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा spi_master *master;
	काष्ठा resource mem;
	पूर्णांक irq, type;
	पूर्णांक ret;
	bool spisel_boot = false;
#अगर IS_ENABLED(CONFIG_FSL_SOC)
	काष्ठा mpc8xxx_spi_probe_info *pinfo = शून्य;
#पूर्ण_अगर


	ret = of_mpc8xxx_spi_probe(ofdev);
	अगर (ret)
		वापस ret;

	type = fsl_spi_get_type(&ofdev->dev);
	अगर (type == TYPE_FSL) अणु
		काष्ठा fsl_spi_platक्रमm_data *pdata = dev_get_platdata(dev);
#अगर IS_ENABLED(CONFIG_FSL_SOC)
		pinfo = to_of_pinfo(pdata);

		spisel_boot = of_property_पढ़ो_bool(np, "fsl,spisel_boot");
		अगर (spisel_boot) अणु
			pinfo->immr_spi_cs = ioremap(get_immrbase() + IMMR_SPI_CS_OFFSET, 4);
			अगर (!pinfo->immr_spi_cs)
				वापस -ENOMEM;
		पूर्ण
#पूर्ण_अगर
		/*
		 * Handle the हाल where we have one hardwired (always selected)
		 * device on the first "chipselect". Else we let the core code
		 * handle any GPIOs or native chip selects and assign the
		 * appropriate callback क्रम dealing with the CS lines. This isn't
		 * supported on the GRLIB variant.
		 */
		ret = gpiod_count(dev, "cs");
		अगर (ret < 0)
			ret = 0;
		अगर (ret == 0 && !spisel_boot) अणु
			pdata->max_chipselect = 1;
		पूर्ण अन्यथा अणु
			pdata->max_chipselect = ret + spisel_boot;
			pdata->cs_control = fsl_spi_cs_control;
		पूर्ण
	पूर्ण

	ret = of_address_to_resource(np, 0, &mem);
	अगर (ret)
		जाओ unmap_out;

	irq = platक्रमm_get_irq(ofdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ unmap_out;
	पूर्ण

	master = fsl_spi_probe(dev, &mem, irq);

	वापस PTR_ERR_OR_ZERO(master);

unmap_out:
#अगर IS_ENABLED(CONFIG_FSL_SOC)
	अगर (spisel_boot)
		iounmap(pinfo->immr_spi_cs);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल पूर्णांक of_fsl_spi_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(ofdev);
	काष्ठा mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(master);

	fsl_spi_cpm_मुक्त(mpc8xxx_spi);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver of_fsl_spi_driver = अणु
	.driver = अणु
		.name = "fsl_spi",
		.of_match_table = of_fsl_spi_match,
	पूर्ण,
	.probe		= of_fsl_spi_probe,
	.हटाओ		= of_fsl_spi_हटाओ,
पूर्ण;

#अगर_घोषित CONFIG_MPC832x_RDB
/*
 * XXX XXX XXX
 * This is "legacy" platक्रमm driver, was used by the MPC8323E-RDB boards
 * only. The driver should go away soon, since newer MPC8323E-RDB's device
 * tree can work with OpenFirmware driver. But क्रम now we support old trees
 * as well.
 */
अटल पूर्णांक plat_mpc8xxx_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *mem;
	पूर्णांक irq;
	काष्ठा spi_master *master;

	अगर (!dev_get_platdata(&pdev->dev))
		वापस -EINVAL;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mem)
		वापस -EINVAL;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस -EINVAL;

	master = fsl_spi_probe(&pdev->dev, mem, irq);
	वापस PTR_ERR_OR_ZERO(master);
पूर्ण

अटल पूर्णांक plat_mpc8xxx_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(master);

	fsl_spi_cpm_मुक्त(mpc8xxx_spi);

	वापस 0;
पूर्ण

MODULE_ALIAS("platform:mpc8xxx_spi");
अटल काष्ठा platक्रमm_driver mpc8xxx_spi_driver = अणु
	.probe = plat_mpc8xxx_spi_probe,
	.हटाओ = plat_mpc8xxx_spi_हटाओ,
	.driver = अणु
		.name = "mpc8xxx_spi",
	पूर्ण,
पूर्ण;

अटल bool legacy_driver_failed;

अटल व्योम __init legacy_driver_रेजिस्टर(व्योम)
अणु
	legacy_driver_failed = platक्रमm_driver_रेजिस्टर(&mpc8xxx_spi_driver);
पूर्ण

अटल व्योम __निकास legacy_driver_unरेजिस्टर(व्योम)
अणु
	अगर (legacy_driver_failed)
		वापस;
	platक्रमm_driver_unरेजिस्टर(&mpc8xxx_spi_driver);
पूर्ण
#अन्यथा
अटल व्योम __init legacy_driver_रेजिस्टर(व्योम) अणुपूर्ण
अटल व्योम __निकास legacy_driver_unरेजिस्टर(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_MPC832x_RDB */

अटल पूर्णांक __init fsl_spi_init(व्योम)
अणु
	legacy_driver_रेजिस्टर();
	वापस platक्रमm_driver_रेजिस्टर(&of_fsl_spi_driver);
पूर्ण
module_init(fsl_spi_init);

अटल व्योम __निकास fsl_spi_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&of_fsl_spi_driver);
	legacy_driver_unरेजिस्टर();
पूर्ण
module_निकास(fsl_spi_निकास);

MODULE_AUTHOR("Kumar Gala");
MODULE_DESCRIPTION("Simple Freescale SPI Driver");
MODULE_LICENSE("GPL");
