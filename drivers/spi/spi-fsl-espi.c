<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale eSPI controller driver.
 *
 * Copyright 2010 Freescale Semiconductor, Inc.
 */
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sysdev/fsl_soc.h>

/* eSPI Controller रेजिस्टरs */
#घोषणा ESPI_SPMODE	0x00	/* eSPI mode रेजिस्टर */
#घोषणा ESPI_SPIE	0x04	/* eSPI event रेजिस्टर */
#घोषणा ESPI_SPIM	0x08	/* eSPI mask रेजिस्टर */
#घोषणा ESPI_SPCOM	0x0c	/* eSPI command रेजिस्टर */
#घोषणा ESPI_SPITF	0x10	/* eSPI transmit FIFO access रेजिस्टर*/
#घोषणा ESPI_SPIRF	0x14	/* eSPI receive FIFO access रेजिस्टर*/
#घोषणा ESPI_SPMODE0	0x20	/* eSPI cs0 mode रेजिस्टर */

#घोषणा ESPI_SPMODEx(x)	(ESPI_SPMODE0 + (x) * 4)

/* eSPI Controller mode रेजिस्टर definitions */
#घोषणा SPMODE_ENABLE		BIT(31)
#घोषणा SPMODE_LOOP		BIT(30)
#घोषणा SPMODE_TXTHR(x)		((x) << 8)
#घोषणा SPMODE_RXTHR(x)		((x) << 0)

/* eSPI Controller CS mode रेजिस्टर definitions */
#घोषणा CSMODE_CI_INACTIVEHIGH	BIT(31)
#घोषणा CSMODE_CP_BEGIN_EDGECLK	BIT(30)
#घोषणा CSMODE_REV		BIT(29)
#घोषणा CSMODE_DIV16		BIT(28)
#घोषणा CSMODE_PM(x)		((x) << 24)
#घोषणा CSMODE_POL_1		BIT(20)
#घोषणा CSMODE_LEN(x)		((x) << 16)
#घोषणा CSMODE_BEF(x)		((x) << 12)
#घोषणा CSMODE_AFT(x)		((x) << 8)
#घोषणा CSMODE_CG(x)		((x) << 3)

#घोषणा FSL_ESPI_FIFO_SIZE	32
#घोषणा FSL_ESPI_RXTHR		15

/* Default mode/csmode क्रम eSPI controller */
#घोषणा SPMODE_INIT_VAL (SPMODE_TXTHR(4) | SPMODE_RXTHR(FSL_ESPI_RXTHR))
#घोषणा CSMODE_INIT_VAL (CSMODE_POL_1 | CSMODE_BEF(0) \
		| CSMODE_AFT(0) | CSMODE_CG(1))

/* SPIE रेजिस्टर values */
#घोषणा SPIE_RXCNT(reg)     ((reg >> 24) & 0x3F)
#घोषणा SPIE_TXCNT(reg)     ((reg >> 16) & 0x3F)
#घोषणा	SPIE_TXE		BIT(15)	/* TX FIFO empty */
#घोषणा	SPIE_DON		BIT(14)	/* TX करोne */
#घोषणा	SPIE_RXT		BIT(13)	/* RX FIFO threshold */
#घोषणा	SPIE_RXF		BIT(12)	/* RX FIFO full */
#घोषणा	SPIE_TXT		BIT(11)	/* TX FIFO threshold*/
#घोषणा	SPIE_RNE		BIT(9)	/* RX FIFO not empty */
#घोषणा	SPIE_TNF		BIT(8)	/* TX FIFO not full */

/* SPIM रेजिस्टर values */
#घोषणा	SPIM_TXE		BIT(15)	/* TX FIFO empty */
#घोषणा	SPIM_DON		BIT(14)	/* TX करोne */
#घोषणा	SPIM_RXT		BIT(13)	/* RX FIFO threshold */
#घोषणा	SPIM_RXF		BIT(12)	/* RX FIFO full */
#घोषणा	SPIM_TXT		BIT(11)	/* TX FIFO threshold*/
#घोषणा	SPIM_RNE		BIT(9)	/* RX FIFO not empty */
#घोषणा	SPIM_TNF		BIT(8)	/* TX FIFO not full */

/* SPCOM रेजिस्टर values */
#घोषणा SPCOM_CS(x)		((x) << 30)
#घोषणा SPCOM_DO		BIT(28) /* Dual output */
#घोषणा SPCOM_TO		BIT(27) /* TX only */
#घोषणा SPCOM_RXSKIP(x)		((x) << 16)
#घोषणा SPCOM_TRANLEN(x)	((x) << 0)

#घोषणा	SPCOM_TRANLEN_MAX	0x10000	/* Max transaction length */

#घोषणा AUTOSUSPEND_TIMEOUT 2000

काष्ठा fsl_espi अणु
	काष्ठा device *dev;
	व्योम __iomem *reg_base;

	काष्ठा list_head *m_transfers;
	काष्ठा spi_transfer *tx_t;
	अचिन्हित पूर्णांक tx_pos;
	bool tx_करोne;
	काष्ठा spi_transfer *rx_t;
	अचिन्हित पूर्णांक rx_pos;
	bool rx_करोne;

	bool swab;
	अचिन्हित पूर्णांक rxskip;

	spinlock_t lock;

	u32 spibrg;             /* SPIBRG input घड़ी */

	काष्ठा completion करोne;
पूर्ण;

काष्ठा fsl_espi_cs अणु
	u32 hw_mode;
पूर्ण;

अटल अंतरभूत u32 fsl_espi_पढ़ो_reg(काष्ठा fsl_espi *espi, पूर्णांक offset)
अणु
	वापस ioपढ़ो32be(espi->reg_base + offset);
पूर्ण

अटल अंतरभूत u16 fsl_espi_पढ़ो_reg16(काष्ठा fsl_espi *espi, पूर्णांक offset)
अणु
	वापस ioपढ़ो16be(espi->reg_base + offset);
पूर्ण

अटल अंतरभूत u8 fsl_espi_पढ़ो_reg8(काष्ठा fsl_espi *espi, पूर्णांक offset)
अणु
	वापस ioपढ़ो8(espi->reg_base + offset);
पूर्ण

अटल अंतरभूत व्योम fsl_espi_ग_लिखो_reg(काष्ठा fsl_espi *espi, पूर्णांक offset,
				      u32 val)
अणु
	ioग_लिखो32be(val, espi->reg_base + offset);
पूर्ण

अटल अंतरभूत व्योम fsl_espi_ग_लिखो_reg16(काष्ठा fsl_espi *espi, पूर्णांक offset,
					u16 val)
अणु
	ioग_लिखो16be(val, espi->reg_base + offset);
पूर्ण

अटल अंतरभूत व्योम fsl_espi_ग_लिखो_reg8(काष्ठा fsl_espi *espi, पूर्णांक offset,
				       u8 val)
अणु
	ioग_लिखो8(val, espi->reg_base + offset);
पूर्ण

अटल पूर्णांक fsl_espi_check_message(काष्ठा spi_message *m)
अणु
	काष्ठा fsl_espi *espi = spi_master_get_devdata(m->spi->master);
	काष्ठा spi_transfer *t, *first;

	अगर (m->frame_length > SPCOM_TRANLEN_MAX) अणु
		dev_err(espi->dev, "message too long, size is %u bytes\n",
			m->frame_length);
		वापस -EMSGSIZE;
	पूर्ण

	first = list_first_entry(&m->transfers, काष्ठा spi_transfer,
				 transfer_list);

	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		अगर (first->bits_per_word != t->bits_per_word ||
		    first->speed_hz != t->speed_hz) अणु
			dev_err(espi->dev, "bits_per_word/speed_hz should be the same for all transfers\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* ESPI supports MSB-first transfers क्रम word size 8 / 16 only */
	अगर (!(m->spi->mode & SPI_LSB_FIRST) && first->bits_per_word != 8 &&
	    first->bits_per_word != 16) अणु
		dev_err(espi->dev,
			"MSB-first transfer not supported for wordsize %u\n",
			first->bits_per_word);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक fsl_espi_check_rxskip_mode(काष्ठा spi_message *m)
अणु
	काष्ठा spi_transfer *t;
	अचिन्हित पूर्णांक i = 0, rxskip = 0;

	/*
	 * prerequisites क्रम ESPI rxskip mode:
	 * - message has two transfers
	 * - first transfer is a ग_लिखो and second is a पढ़ो
	 *
	 * In addition the current low-level transfer mechanism requires
	 * that the rxskip bytes fit पूर्णांकo the TX FIFO. Else the transfer
	 * would hang because after the first FSL_ESPI_FIFO_SIZE bytes
	 * the TX FIFO isn't re-filled.
	 */
	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		अगर (i == 0) अणु
			अगर (!t->tx_buf || t->rx_buf ||
			    t->len > FSL_ESPI_FIFO_SIZE)
				वापस 0;
			rxskip = t->len;
		पूर्ण अन्यथा अगर (i == 1) अणु
			अगर (t->tx_buf || !t->rx_buf)
				वापस 0;
		पूर्ण
		i++;
	पूर्ण

	वापस i == 2 ? rxskip : 0;
पूर्ण

अटल व्योम fsl_espi_fill_tx_fअगरo(काष्ठा fsl_espi *espi, u32 events)
अणु
	u32 tx_fअगरo_avail;
	अचिन्हित पूर्णांक tx_left;
	स्थिर व्योम *tx_buf;

	/* अगर events is zero transfer has not started and tx fअगरo is empty */
	tx_fअगरo_avail = events ? SPIE_TXCNT(events) :  FSL_ESPI_FIFO_SIZE;
start:
	tx_left = espi->tx_t->len - espi->tx_pos;
	tx_buf = espi->tx_t->tx_buf;
	जबतक (tx_fअगरo_avail >= min(4U, tx_left) && tx_left) अणु
		अगर (tx_left >= 4) अणु
			अगर (!tx_buf)
				fsl_espi_ग_लिखो_reg(espi, ESPI_SPITF, 0);
			अन्यथा अगर (espi->swab)
				fsl_espi_ग_लिखो_reg(espi, ESPI_SPITF,
					swahb32p(tx_buf + espi->tx_pos));
			अन्यथा
				fsl_espi_ग_लिखो_reg(espi, ESPI_SPITF,
					*(u32 *)(tx_buf + espi->tx_pos));
			espi->tx_pos += 4;
			tx_left -= 4;
			tx_fअगरo_avail -= 4;
		पूर्ण अन्यथा अगर (tx_left >= 2 && tx_buf && espi->swab) अणु
			fsl_espi_ग_लिखो_reg16(espi, ESPI_SPITF,
					swab16p(tx_buf + espi->tx_pos));
			espi->tx_pos += 2;
			tx_left -= 2;
			tx_fअगरo_avail -= 2;
		पूर्ण अन्यथा अणु
			अगर (!tx_buf)
				fsl_espi_ग_लिखो_reg8(espi, ESPI_SPITF, 0);
			अन्यथा
				fsl_espi_ग_लिखो_reg8(espi, ESPI_SPITF,
					*(u8 *)(tx_buf + espi->tx_pos));
			espi->tx_pos += 1;
			tx_left -= 1;
			tx_fअगरo_avail -= 1;
		पूर्ण
	पूर्ण

	अगर (!tx_left) अणु
		/* Last transfer finished, in rxskip mode only one is needed */
		अगर (list_is_last(&espi->tx_t->transfer_list,
		    espi->m_transfers) || espi->rxskip) अणु
			espi->tx_करोne = true;
			वापस;
		पूर्ण
		espi->tx_t = list_next_entry(espi->tx_t, transfer_list);
		espi->tx_pos = 0;
		/* जारी with next transfer अगर tx fअगरo is not full */
		अगर (tx_fअगरo_avail)
			जाओ start;
	पूर्ण
पूर्ण

अटल व्योम fsl_espi_पढ़ो_rx_fअगरo(काष्ठा fsl_espi *espi, u32 events)
अणु
	u32 rx_fअगरo_avail = SPIE_RXCNT(events);
	अचिन्हित पूर्णांक rx_left;
	व्योम *rx_buf;

start:
	rx_left = espi->rx_t->len - espi->rx_pos;
	rx_buf = espi->rx_t->rx_buf;
	जबतक (rx_fअगरo_avail >= min(4U, rx_left) && rx_left) अणु
		अगर (rx_left >= 4) अणु
			u32 val = fsl_espi_पढ़ो_reg(espi, ESPI_SPIRF);

			अगर (rx_buf && espi->swab)
				*(u32 *)(rx_buf + espi->rx_pos) = swahb32(val);
			अन्यथा अगर (rx_buf)
				*(u32 *)(rx_buf + espi->rx_pos) = val;
			espi->rx_pos += 4;
			rx_left -= 4;
			rx_fअगरo_avail -= 4;
		पूर्ण अन्यथा अगर (rx_left >= 2 && rx_buf && espi->swab) अणु
			u16 val = fsl_espi_पढ़ो_reg16(espi, ESPI_SPIRF);

			*(u16 *)(rx_buf + espi->rx_pos) = swab16(val);
			espi->rx_pos += 2;
			rx_left -= 2;
			rx_fअगरo_avail -= 2;
		पूर्ण अन्यथा अणु
			u8 val = fsl_espi_पढ़ो_reg8(espi, ESPI_SPIRF);

			अगर (rx_buf)
				*(u8 *)(rx_buf + espi->rx_pos) = val;
			espi->rx_pos += 1;
			rx_left -= 1;
			rx_fअगरo_avail -= 1;
		पूर्ण
	पूर्ण

	अगर (!rx_left) अणु
		अगर (list_is_last(&espi->rx_t->transfer_list,
		    espi->m_transfers)) अणु
			espi->rx_करोne = true;
			वापस;
		पूर्ण
		espi->rx_t = list_next_entry(espi->rx_t, transfer_list);
		espi->rx_pos = 0;
		/* जारी with next transfer अगर rx fअगरo is not empty */
		अगर (rx_fअगरo_avail)
			जाओ start;
	पूर्ण
पूर्ण

अटल व्योम fsl_espi_setup_transfer(काष्ठा spi_device *spi,
					काष्ठा spi_transfer *t)
अणु
	काष्ठा fsl_espi *espi = spi_master_get_devdata(spi->master);
	पूर्णांक bits_per_word = t ? t->bits_per_word : spi->bits_per_word;
	u32 pm, hz = t ? t->speed_hz : spi->max_speed_hz;
	काष्ठा fsl_espi_cs *cs = spi_get_ctldata(spi);
	u32 hw_mode_old = cs->hw_mode;

	/* mask out bits we are going to set */
	cs->hw_mode &= ~(CSMODE_LEN(0xF) | CSMODE_DIV16 | CSMODE_PM(0xF));

	cs->hw_mode |= CSMODE_LEN(bits_per_word - 1);

	pm = DIV_ROUND_UP(espi->spibrg, hz * 4) - 1;

	अगर (pm > 15) अणु
		cs->hw_mode |= CSMODE_DIV16;
		pm = DIV_ROUND_UP(espi->spibrg, hz * 16 * 4) - 1;
	पूर्ण

	cs->hw_mode |= CSMODE_PM(pm);

	/* करोn't write the mode register if the mode doesn't change */
	अगर (cs->hw_mode != hw_mode_old)
		fsl_espi_ग_लिखो_reg(espi, ESPI_SPMODEx(spi->chip_select),
				   cs->hw_mode);
पूर्ण

अटल पूर्णांक fsl_espi_bufs(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा fsl_espi *espi = spi_master_get_devdata(spi->master);
	अचिन्हित पूर्णांक rx_len = t->len;
	u32 mask, spcom;
	पूर्णांक ret;

	reinit_completion(&espi->करोne);

	/* Set SPCOM[CS] and SPCOM[TRANLEN] field */
	spcom = SPCOM_CS(spi->chip_select);
	spcom |= SPCOM_TRANLEN(t->len - 1);

	/* configure RXSKIP mode */
	अगर (espi->rxskip) अणु
		spcom |= SPCOM_RXSKIP(espi->rxskip);
		rx_len = t->len - espi->rxskip;
		अगर (t->rx_nbits == SPI_NBITS_DUAL)
			spcom |= SPCOM_DO;
	पूर्ण

	fsl_espi_ग_लिखो_reg(espi, ESPI_SPCOM, spcom);

	/* enable पूर्णांकerrupts */
	mask = SPIM_DON;
	अगर (rx_len > FSL_ESPI_FIFO_SIZE)
		mask |= SPIM_RXT;
	fsl_espi_ग_लिखो_reg(espi, ESPI_SPIM, mask);

	/* Prevent filling the fअगरo from getting पूर्णांकerrupted */
	spin_lock_irq(&espi->lock);
	fsl_espi_fill_tx_fअगरo(espi, 0);
	spin_unlock_irq(&espi->lock);

	/* Won't hang up क्रमever, SPI bus someबार got lost पूर्णांकerrupts... */
	ret = रुको_क्रम_completion_समयout(&espi->करोne, 2 * HZ);
	अगर (ret == 0)
		dev_err(espi->dev, "Transfer timed out!\n");

	/* disable rx पूर्णांकs */
	fsl_espi_ग_लिखो_reg(espi, ESPI_SPIM, 0);

	वापस ret == 0 ? -ETIMEDOUT : 0;
पूर्ण

अटल पूर्णांक fsl_espi_trans(काष्ठा spi_message *m, काष्ठा spi_transfer *trans)
अणु
	काष्ठा fsl_espi *espi = spi_master_get_devdata(m->spi->master);
	काष्ठा spi_device *spi = m->spi;
	पूर्णांक ret;

	/* In हाल of LSB-first and bits_per_word > 8 byte-swap all words */
	espi->swab = spi->mode & SPI_LSB_FIRST && trans->bits_per_word > 8;

	espi->m_transfers = &m->transfers;
	espi->tx_t = list_first_entry(&m->transfers, काष्ठा spi_transfer,
				      transfer_list);
	espi->tx_pos = 0;
	espi->tx_करोne = false;
	espi->rx_t = list_first_entry(&m->transfers, काष्ठा spi_transfer,
				      transfer_list);
	espi->rx_pos = 0;
	espi->rx_करोne = false;

	espi->rxskip = fsl_espi_check_rxskip_mode(m);
	अगर (trans->rx_nbits == SPI_NBITS_DUAL && !espi->rxskip) अणु
		dev_err(espi->dev, "Dual output mode requires RXSKIP mode!\n");
		वापस -EINVAL;
	पूर्ण

	/* In RXSKIP mode skip first transfer क्रम पढ़ोs */
	अगर (espi->rxskip)
		espi->rx_t = list_next_entry(espi->rx_t, transfer_list);

	fsl_espi_setup_transfer(spi, trans);

	ret = fsl_espi_bufs(spi, trans);

	spi_transfer_delay_exec(trans);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_espi_करो_one_msg(काष्ठा spi_master *master,
			       काष्ठा spi_message *m)
अणु
	अचिन्हित पूर्णांक rx_nbits = 0, delay_nsecs = 0;
	काष्ठा spi_transfer *t, trans = अणुपूर्ण;
	पूर्णांक ret;

	ret = fsl_espi_check_message(m);
	अगर (ret)
		जाओ out;

	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		अचिन्हित पूर्णांक delay = spi_delay_to_ns(&t->delay, t);

		अगर (delay > delay_nsecs)
			delay_nsecs = delay;
		अगर (t->rx_nbits > rx_nbits)
			rx_nbits = t->rx_nbits;
	पूर्ण

	t = list_first_entry(&m->transfers, काष्ठा spi_transfer,
			     transfer_list);

	trans.len = m->frame_length;
	trans.speed_hz = t->speed_hz;
	trans.bits_per_word = t->bits_per_word;
	trans.delay.value = delay_nsecs;
	trans.delay.unit = SPI_DELAY_UNIT_NSECS;
	trans.rx_nbits = rx_nbits;

	अगर (trans.len)
		ret = fsl_espi_trans(m, &trans);

	m->actual_length = ret ? 0 : trans.len;
out:
	अगर (m->status == -EINPROGRESS)
		m->status = ret;

	spi_finalize_current_message(master);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_espi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा fsl_espi *espi;
	u32 loop_mode;
	काष्ठा fsl_espi_cs *cs = spi_get_ctldata(spi);

	अगर (!cs) अणु
		cs = kzalloc(माप(*cs), GFP_KERNEL);
		अगर (!cs)
			वापस -ENOMEM;
		spi_set_ctldata(spi, cs);
	पूर्ण

	espi = spi_master_get_devdata(spi->master);

	pm_runसमय_get_sync(espi->dev);

	cs->hw_mode = fsl_espi_पढ़ो_reg(espi, ESPI_SPMODEx(spi->chip_select));
	/* mask out bits we are going to set */
	cs->hw_mode &= ~(CSMODE_CP_BEGIN_EDGECLK | CSMODE_CI_INACTIVEHIGH
			 | CSMODE_REV);

	अगर (spi->mode & SPI_CPHA)
		cs->hw_mode |= CSMODE_CP_BEGIN_EDGECLK;
	अगर (spi->mode & SPI_CPOL)
		cs->hw_mode |= CSMODE_CI_INACTIVEHIGH;
	अगर (!(spi->mode & SPI_LSB_FIRST))
		cs->hw_mode |= CSMODE_REV;

	/* Handle the loop mode */
	loop_mode = fsl_espi_पढ़ो_reg(espi, ESPI_SPMODE);
	loop_mode &= ~SPMODE_LOOP;
	अगर (spi->mode & SPI_LOOP)
		loop_mode |= SPMODE_LOOP;
	fsl_espi_ग_लिखो_reg(espi, ESPI_SPMODE, loop_mode);

	fsl_espi_setup_transfer(spi, शून्य);

	pm_runसमय_mark_last_busy(espi->dev);
	pm_runसमय_put_स्वतःsuspend(espi->dev);

	वापस 0;
पूर्ण

अटल व्योम fsl_espi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा fsl_espi_cs *cs = spi_get_ctldata(spi);

	kमुक्त(cs);
	spi_set_ctldata(spi, शून्य);
पूर्ण

अटल व्योम fsl_espi_cpu_irq(काष्ठा fsl_espi *espi, u32 events)
अणु
	अगर (!espi->rx_करोne)
		fsl_espi_पढ़ो_rx_fअगरo(espi, events);

	अगर (!espi->tx_करोne)
		fsl_espi_fill_tx_fअगरo(espi, events);

	अगर (!espi->tx_करोne || !espi->rx_करोne)
		वापस;

	/* we're करोne, but check क्रम errors beक्रमe वापसing */
	events = fsl_espi_पढ़ो_reg(espi, ESPI_SPIE);

	अगर (!(events & SPIE_DON))
		dev_err(espi->dev,
			"Transfer done but SPIE_DON isn't set!\n");

	अगर (SPIE_RXCNT(events) || SPIE_TXCNT(events) != FSL_ESPI_FIFO_SIZE) अणु
		dev_err(espi->dev, "Transfer done but rx/tx fifo's aren't empty!\n");
		dev_err(espi->dev, "SPIE_RXCNT = %d, SPIE_TXCNT = %d\n",
			SPIE_RXCNT(events), SPIE_TXCNT(events));
	पूर्ण

	complete(&espi->करोne);
पूर्ण

अटल irqवापस_t fsl_espi_irq(s32 irq, व्योम *context_data)
अणु
	काष्ठा fsl_espi *espi = context_data;
	u32 events, mask;

	spin_lock(&espi->lock);

	/* Get पूर्णांकerrupt events(tx/rx) */
	events = fsl_espi_पढ़ो_reg(espi, ESPI_SPIE);
	mask = fsl_espi_पढ़ो_reg(espi, ESPI_SPIM);
	अगर (!(events & mask)) अणु
		spin_unlock(&espi->lock);
		वापस IRQ_NONE;
	पूर्ण

	dev_vdbg(espi->dev, "%s: events %x\n", __func__, events);

	fsl_espi_cpu_irq(espi, events);

	/* Clear the events */
	fsl_espi_ग_लिखो_reg(espi, ESPI_SPIE, events);

	spin_unlock(&espi->lock);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fsl_espi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा fsl_espi *espi = spi_master_get_devdata(master);
	u32 regval;

	regval = fsl_espi_पढ़ो_reg(espi, ESPI_SPMODE);
	regval &= ~SPMODE_ENABLE;
	fsl_espi_ग_लिखो_reg(espi, ESPI_SPMODE, regval);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_espi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा fsl_espi *espi = spi_master_get_devdata(master);
	u32 regval;

	regval = fsl_espi_पढ़ो_reg(espi, ESPI_SPMODE);
	regval |= SPMODE_ENABLE;
	fsl_espi_ग_लिखो_reg(espi, ESPI_SPMODE, regval);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल माप_प्रकार fsl_espi_max_message_size(काष्ठा spi_device *spi)
अणु
	वापस SPCOM_TRANLEN_MAX;
पूर्ण

अटल व्योम fsl_espi_init_regs(काष्ठा device *dev, bool initial)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा fsl_espi *espi = spi_master_get_devdata(master);
	काष्ठा device_node *nc;
	u32 csmode, cs, prop;
	पूर्णांक ret;

	/* SPI controller initializations */
	fsl_espi_ग_लिखो_reg(espi, ESPI_SPMODE, 0);
	fsl_espi_ग_लिखो_reg(espi, ESPI_SPIM, 0);
	fsl_espi_ग_लिखो_reg(espi, ESPI_SPCOM, 0);
	fsl_espi_ग_लिखो_reg(espi, ESPI_SPIE, 0xffffffff);

	/* Init eSPI CS mode रेजिस्टर */
	क्रम_each_available_child_of_node(master->dev.of_node, nc) अणु
		/* get chip select */
		ret = of_property_पढ़ो_u32(nc, "reg", &cs);
		अगर (ret || cs >= master->num_chipselect)
			जारी;

		csmode = CSMODE_INIT_VAL;

		/* check अगर CSBEF is set in device tree */
		ret = of_property_पढ़ो_u32(nc, "fsl,csbef", &prop);
		अगर (!ret) अणु
			csmode &= ~(CSMODE_BEF(0xf));
			csmode |= CSMODE_BEF(prop);
		पूर्ण

		/* check अगर CSAFT is set in device tree */
		ret = of_property_पढ़ो_u32(nc, "fsl,csaft", &prop);
		अगर (!ret) अणु
			csmode &= ~(CSMODE_AFT(0xf));
			csmode |= CSMODE_AFT(prop);
		पूर्ण

		fsl_espi_ग_लिखो_reg(espi, ESPI_SPMODEx(cs), csmode);

		अगर (initial)
			dev_info(dev, "cs=%u, init_csmode=0x%x\n", cs, csmode);
	पूर्ण

	/* Enable SPI पूर्णांकerface */
	fsl_espi_ग_लिखो_reg(espi, ESPI_SPMODE, SPMODE_INIT_VAL | SPMODE_ENABLE);
पूर्ण

अटल पूर्णांक fsl_espi_probe(काष्ठा device *dev, काष्ठा resource *mem,
			  अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक num_cs)
अणु
	काष्ठा spi_master *master;
	काष्ठा fsl_espi *espi;
	पूर्णांक ret;

	master = spi_alloc_master(dev, माप(काष्ठा fsl_espi));
	अगर (!master)
		वापस -ENOMEM;

	dev_set_drvdata(dev, master);

	master->mode_bits = SPI_RX_DUAL | SPI_CPOL | SPI_CPHA | SPI_CS_HIGH |
			    SPI_LSB_FIRST | SPI_LOOP;
	master->dev.of_node = dev->of_node;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 16);
	master->setup = fsl_espi_setup;
	master->cleanup = fsl_espi_cleanup;
	master->transfer_one_message = fsl_espi_करो_one_msg;
	master->स्वतः_runसमय_pm = true;
	master->max_message_size = fsl_espi_max_message_size;
	master->num_chipselect = num_cs;

	espi = spi_master_get_devdata(master);
	spin_lock_init(&espi->lock);

	espi->dev = dev;
	espi->spibrg = fsl_get_sys_freq();
	अगर (espi->spibrg == -1) अणु
		dev_err(dev, "Can't get sys frequency!\n");
		ret = -EINVAL;
		जाओ err_probe;
	पूर्ण
	/* determined by घड़ी भागider fields DIV16/PM in रेजिस्टर SPMODEx */
	master->min_speed_hz = DIV_ROUND_UP(espi->spibrg, 4 * 16 * 16);
	master->max_speed_hz = DIV_ROUND_UP(espi->spibrg, 4);

	init_completion(&espi->करोne);

	espi->reg_base = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(espi->reg_base)) अणु
		ret = PTR_ERR(espi->reg_base);
		जाओ err_probe;
	पूर्ण

	/* Register क्रम SPI Interrupt */
	ret = devm_request_irq(dev, irq, fsl_espi_irq, 0, "fsl_espi", espi);
	अगर (ret)
		जाओ err_probe;

	fsl_espi_init_regs(dev, true);

	pm_runसमय_set_स्वतःsuspend_delay(dev, AUTOSUSPEND_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	ret = devm_spi_रेजिस्टर_master(dev, master);
	अगर (ret < 0)
		जाओ err_pm;

	dev_info(dev, "irq = %u\n", irq);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;

err_pm:
	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
err_probe:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक of_fsl_espi_get_chipselects(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	u32 num_cs;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "fsl,espi-num-chipselects", &num_cs);
	अगर (ret) अणु
		dev_err(dev, "No 'fsl,espi-num-chipselects' property\n");
		वापस 0;
	पूर्ण

	वापस num_cs;
पूर्ण

अटल पूर्णांक of_fsl_espi_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा resource mem;
	अचिन्हित पूर्णांक irq, num_cs;
	पूर्णांक ret;

	अगर (of_property_पढ़ो_bool(np, "mode")) अणु
		dev_err(dev, "mode property is not supported on ESPI!\n");
		वापस -EINVAL;
	पूर्ण

	num_cs = of_fsl_espi_get_chipselects(dev);
	अगर (!num_cs)
		वापस -EINVAL;

	ret = of_address_to_resource(np, 0, &mem);
	अगर (ret)
		वापस ret;

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq)
		वापस -EINVAL;

	वापस fsl_espi_probe(dev, &mem, irq, num_cs);
पूर्ण

अटल पूर्णांक of_fsl_espi_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	pm_runसमय_disable(&dev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक of_fsl_espi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = spi_master_suspend(master);
	अगर (ret)
		वापस ret;

	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक of_fsl_espi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	पूर्णांक ret;

	fsl_espi_init_regs(dev, false);

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret < 0)
		वापस ret;

	वापस spi_master_resume(master);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops espi_pm = अणु
	SET_RUNTIME_PM_OPS(fsl_espi_runसमय_suspend,
			   fsl_espi_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(of_fsl_espi_suspend, of_fsl_espi_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_fsl_espi_match[] = अणु
	अणु .compatible = "fsl,mpc8536-espi" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_fsl_espi_match);

अटल काष्ठा platक्रमm_driver fsl_espi_driver = अणु
	.driver = अणु
		.name = "fsl_espi",
		.of_match_table = of_fsl_espi_match,
		.pm = &espi_pm,
	पूर्ण,
	.probe		= of_fsl_espi_probe,
	.हटाओ		= of_fsl_espi_हटाओ,
पूर्ण;
module_platक्रमm_driver(fsl_espi_driver);

MODULE_AUTHOR("Mingkai Hu");
MODULE_DESCRIPTION("Enhanced Freescale SPI Driver");
MODULE_LICENSE("GPL");
