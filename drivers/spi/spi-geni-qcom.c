<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017-2018, The Linux foundation. All rights reserved.

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/qcom-geni-se.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spinlock.h>

/* SPI SE specअगरic रेजिस्टरs and respective रेजिस्टर fields */
#घोषणा SE_SPI_CPHA		0x224
#घोषणा CPHA			BIT(0)

#घोषणा SE_SPI_LOOPBACK		0x22c
#घोषणा LOOPBACK_ENABLE		0x1
#घोषणा NORMAL_MODE		0x0
#घोषणा LOOPBACK_MSK		GENMASK(1, 0)

#घोषणा SE_SPI_CPOL		0x230
#घोषणा CPOL			BIT(2)

#घोषणा SE_SPI_DEMUX_OUTPUT_INV	0x24c
#घोषणा CS_DEMUX_OUTPUT_INV_MSK	GENMASK(3, 0)

#घोषणा SE_SPI_DEMUX_SEL	0x250
#घोषणा CS_DEMUX_OUTPUT_SEL	GENMASK(3, 0)

#घोषणा SE_SPI_TRANS_CFG	0x25c
#घोषणा CS_TOGGLE		BIT(0)

#घोषणा SE_SPI_WORD_LEN		0x268
#घोषणा WORD_LEN_MSK		GENMASK(9, 0)
#घोषणा MIN_WORD_LEN		4

#घोषणा SE_SPI_TX_TRANS_LEN	0x26c
#घोषणा SE_SPI_RX_TRANS_LEN	0x270
#घोषणा TRANS_LEN_MSK		GENMASK(23, 0)

#घोषणा SE_SPI_PRE_POST_CMD_DLY	0x274

#घोषणा SE_SPI_DELAY_COUNTERS	0x278
#घोषणा SPI_INTER_WORDS_DELAY_MSK	GENMASK(9, 0)
#घोषणा SPI_CS_CLK_DELAY_MSK		GENMASK(19, 10)
#घोषणा SPI_CS_CLK_DELAY_SHFT		10

/* M_CMD OP codes क्रम SPI */
#घोषणा SPI_TX_ONLY		1
#घोषणा SPI_RX_ONLY		2
#घोषणा SPI_TX_RX		7
#घोषणा SPI_CS_ASSERT		8
#घोषणा SPI_CS_DEASSERT		9
#घोषणा SPI_SCK_ONLY		10
/* M_CMD params क्रम SPI */
#घोषणा SPI_PRE_CMD_DELAY	BIT(0)
#घोषणा TIMESTAMP_BEFORE	BIT(1)
#घोषणा FRAGMENTATION		BIT(2)
#घोषणा TIMESTAMP_AFTER		BIT(3)
#घोषणा POST_CMD_DELAY		BIT(4)

काष्ठा spi_geni_master अणु
	काष्ठा geni_se se;
	काष्ठा device *dev;
	u32 tx_fअगरo_depth;
	u32 fअगरo_width_bits;
	u32 tx_wm;
	u32 last_mode;
	अचिन्हित दीर्घ cur_speed_hz;
	अचिन्हित दीर्घ cur_sclk_hz;
	अचिन्हित पूर्णांक cur_bits_per_word;
	अचिन्हित पूर्णांक tx_rem_bytes;
	अचिन्हित पूर्णांक rx_rem_bytes;
	स्थिर काष्ठा spi_transfer *cur_xfer;
	काष्ठा completion cs_करोne;
	काष्ठा completion cancel_करोne;
	काष्ठा completion पात_करोne;
	अचिन्हित पूर्णांक oversampling;
	spinlock_t lock;
	पूर्णांक irq;
	bool cs_flag;
	bool पात_failed;
पूर्ण;

अटल पूर्णांक get_spi_clk_cfg(अचिन्हित पूर्णांक speed_hz,
			काष्ठा spi_geni_master *mas,
			अचिन्हित पूर्णांक *clk_idx,
			अचिन्हित पूर्णांक *clk_भाग)
अणु
	अचिन्हित दीर्घ sclk_freq;
	अचिन्हित पूर्णांक actual_hz;
	पूर्णांक ret;

	ret = geni_se_clk_freq_match(&mas->se,
				speed_hz * mas->oversampling,
				clk_idx, &sclk_freq, false);
	अगर (ret) अणु
		dev_err(mas->dev, "Failed(%d) to find src clk for %dHz\n",
							ret, speed_hz);
		वापस ret;
	पूर्ण

	*clk_भाग = DIV_ROUND_UP(sclk_freq, mas->oversampling * speed_hz);
	actual_hz = sclk_freq / (mas->oversampling * *clk_भाग);

	dev_dbg(mas->dev, "req %u=>%u sclk %lu, idx %d, div %d\n", speed_hz,
				actual_hz, sclk_freq, *clk_idx, *clk_भाग);
	ret = dev_pm_opp_set_rate(mas->dev, sclk_freq);
	अगर (ret)
		dev_err(mas->dev, "dev_pm_opp_set_rate failed %d\n", ret);
	अन्यथा
		mas->cur_sclk_hz = sclk_freq;

	वापस ret;
पूर्ण

अटल व्योम handle_fअगरo_समयout(काष्ठा spi_master *spi,
				काष्ठा spi_message *msg)
अणु
	काष्ठा spi_geni_master *mas = spi_master_get_devdata(spi);
	अचिन्हित दीर्घ समय_left;
	काष्ठा geni_se *se = &mas->se;

	spin_lock_irq(&mas->lock);
	reinit_completion(&mas->cancel_करोne);
	ग_लिखोl(0, se->base + SE_GENI_TX_WATERMARK_REG);
	mas->cur_xfer = शून्य;
	geni_se_cancel_m_cmd(se);
	spin_unlock_irq(&mas->lock);

	समय_left = रुको_क्रम_completion_समयout(&mas->cancel_करोne, HZ);
	अगर (समय_left)
		वापस;

	spin_lock_irq(&mas->lock);
	reinit_completion(&mas->पात_करोne);
	geni_se_पात_m_cmd(se);
	spin_unlock_irq(&mas->lock);

	समय_left = रुको_क्रम_completion_समयout(&mas->पात_करोne, HZ);
	अगर (!समय_left) अणु
		dev_err(mas->dev, "Failed to cancel/abort m_cmd\n");

		/*
		 * No need क्रम a lock since SPI core has a lock and we never
		 * access this from an पूर्णांकerrupt.
		 */
		mas->पात_failed = true;
	पूर्ण
पूर्ण

अटल bool spi_geni_is_पात_still_pending(काष्ठा spi_geni_master *mas)
अणु
	काष्ठा geni_se *se = &mas->se;
	u32 m_irq, m_irq_en;

	अगर (!mas->पात_failed)
		वापस false;

	/*
	 * The only known हाल where a transfer बार out and then a cancel
	 * बार out then an पात बार out is अगर something is blocking our
	 * पूर्णांकerrupt handler from running.  Aव्योम starting any new transfers
	 * until that sorts itself out.
	 */
	spin_lock_irq(&mas->lock);
	m_irq = पढ़ोl(se->base + SE_GENI_M_IRQ_STATUS);
	m_irq_en = पढ़ोl(se->base + SE_GENI_M_IRQ_EN);
	spin_unlock_irq(&mas->lock);

	अगर (m_irq & m_irq_en) अणु
		dev_err(mas->dev, "Interrupts pending after abort: %#010x\n",
			m_irq & m_irq_en);
		वापस true;
	पूर्ण

	/*
	 * If we're here the problem resolved itself so no need to check more
	 * on future transfers.
	 */
	mas->पात_failed = false;

	वापस false;
पूर्ण

अटल व्योम spi_geni_set_cs(काष्ठा spi_device *slv, bool set_flag)
अणु
	काष्ठा spi_geni_master *mas = spi_master_get_devdata(slv->master);
	काष्ठा spi_master *spi = dev_get_drvdata(mas->dev);
	काष्ठा geni_se *se = &mas->se;
	अचिन्हित दीर्घ समय_left;

	अगर (!(slv->mode & SPI_CS_HIGH))
		set_flag = !set_flag;

	अगर (set_flag == mas->cs_flag)
		वापस;

	pm_runसमय_get_sync(mas->dev);

	अगर (spi_geni_is_पात_still_pending(mas)) अणु
		dev_err(mas->dev, "Can't set chip select\n");
		जाओ निकास;
	पूर्ण

	spin_lock_irq(&mas->lock);
	अगर (mas->cur_xfer) अणु
		dev_err(mas->dev, "Can't set CS when prev xfer running\n");
		spin_unlock_irq(&mas->lock);
		जाओ निकास;
	पूर्ण

	mas->cs_flag = set_flag;
	reinit_completion(&mas->cs_करोne);
	अगर (set_flag)
		geni_se_setup_m_cmd(se, SPI_CS_ASSERT, 0);
	अन्यथा
		geni_se_setup_m_cmd(se, SPI_CS_DEASSERT, 0);
	spin_unlock_irq(&mas->lock);

	समय_left = रुको_क्रम_completion_समयout(&mas->cs_करोne, HZ);
	अगर (!समय_left) अणु
		dev_warn(mas->dev, "Timeout setting chip select\n");
		handle_fअगरo_समयout(spi, शून्य);
	पूर्ण

निकास:
	pm_runसमय_put(mas->dev);
पूर्ण

अटल व्योम spi_setup_word_len(काष्ठा spi_geni_master *mas, u16 mode,
					अचिन्हित पूर्णांक bits_per_word)
अणु
	अचिन्हित पूर्णांक pack_words;
	bool msb_first = (mode & SPI_LSB_FIRST) ? false : true;
	काष्ठा geni_se *se = &mas->se;
	u32 word_len;

	/*
	 * If bits_per_word isn't a byte aligned value, set the packing to be
	 * 1 SPI word per FIFO word.
	 */
	अगर (!(mas->fअगरo_width_bits % bits_per_word))
		pack_words = mas->fअगरo_width_bits / bits_per_word;
	अन्यथा
		pack_words = 1;
	geni_se_config_packing(&mas->se, bits_per_word, pack_words, msb_first,
								true, true);
	word_len = (bits_per_word - MIN_WORD_LEN) & WORD_LEN_MSK;
	ग_लिखोl(word_len, se->base + SE_SPI_WORD_LEN);
पूर्ण

अटल पूर्णांक geni_spi_set_घड़ी_and_bw(काष्ठा spi_geni_master *mas,
					अचिन्हित दीर्घ clk_hz)
अणु
	u32 clk_sel, m_clk_cfg, idx, भाग;
	काष्ठा geni_se *se = &mas->se;
	पूर्णांक ret;

	अगर (clk_hz == mas->cur_speed_hz)
		वापस 0;

	ret = get_spi_clk_cfg(clk_hz, mas, &idx, &भाग);
	अगर (ret) अणु
		dev_err(mas->dev, "Err setting clk to %lu: %d\n", clk_hz, ret);
		वापस ret;
	पूर्ण

	/*
	 * SPI core घड़ी माला_लो configured with the requested frequency
	 * or the frequency बंदr to the requested frequency.
	 * For that reason requested frequency is stored in the
	 * cur_speed_hz and referred in the consecutive transfer instead
	 * of calling clk_get_rate() API.
	 */
	mas->cur_speed_hz = clk_hz;

	clk_sel = idx & CLK_SEL_MSK;
	m_clk_cfg = (भाग << CLK_DIV_SHFT) | SER_CLK_EN;
	ग_लिखोl(clk_sel, se->base + SE_GENI_CLK_SEL);
	ग_लिखोl(m_clk_cfg, se->base + GENI_SER_M_CLK_CFG);

	/* Set BW quota क्रम CPU as driver supports FIFO mode only. */
	se->icc_paths[CPU_TO_GENI].avg_bw = Bps_to_icc(mas->cur_speed_hz);
	ret = geni_icc_set_bw(se);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक setup_fअगरo_params(काष्ठा spi_device *spi_slv,
					काष्ठा spi_master *spi)
अणु
	काष्ठा spi_geni_master *mas = spi_master_get_devdata(spi);
	काष्ठा geni_se *se = &mas->se;
	u32 loopback_cfg = 0, cpol = 0, cpha = 0, demux_output_inv = 0;
	u32 demux_sel;

	अगर (mas->last_mode != spi_slv->mode) अणु
		अगर (spi_slv->mode & SPI_LOOP)
			loopback_cfg = LOOPBACK_ENABLE;

		अगर (spi_slv->mode & SPI_CPOL)
			cpol = CPOL;

		अगर (spi_slv->mode & SPI_CPHA)
			cpha = CPHA;

		अगर (spi_slv->mode & SPI_CS_HIGH)
			demux_output_inv = BIT(spi_slv->chip_select);

		demux_sel = spi_slv->chip_select;
		mas->cur_bits_per_word = spi_slv->bits_per_word;

		spi_setup_word_len(mas, spi_slv->mode, spi_slv->bits_per_word);
		ग_लिखोl(loopback_cfg, se->base + SE_SPI_LOOPBACK);
		ग_लिखोl(demux_sel, se->base + SE_SPI_DEMUX_SEL);
		ग_लिखोl(cpha, se->base + SE_SPI_CPHA);
		ग_लिखोl(cpol, se->base + SE_SPI_CPOL);
		ग_लिखोl(demux_output_inv, se->base + SE_SPI_DEMUX_OUTPUT_INV);

		mas->last_mode = spi_slv->mode;
	पूर्ण

	वापस geni_spi_set_घड़ी_and_bw(mas, spi_slv->max_speed_hz);
पूर्ण

अटल पूर्णांक spi_geni_prepare_message(काष्ठा spi_master *spi,
					काष्ठा spi_message *spi_msg)
अणु
	पूर्णांक ret;
	काष्ठा spi_geni_master *mas = spi_master_get_devdata(spi);

	अगर (spi_geni_is_पात_still_pending(mas))
		वापस -EBUSY;

	ret = setup_fअगरo_params(spi_msg->spi, spi);
	अगर (ret)
		dev_err(mas->dev, "Couldn't select mode %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक spi_geni_init(काष्ठा spi_geni_master *mas)
अणु
	काष्ठा geni_se *se = &mas->se;
	अचिन्हित पूर्णांक proto, major, minor, ver;
	u32 spi_tx_cfg;

	pm_runसमय_get_sync(mas->dev);

	proto = geni_se_पढ़ो_proto(se);
	अगर (proto != GENI_SE_SPI) अणु
		dev_err(mas->dev, "Invalid proto %d\n", proto);
		pm_runसमय_put(mas->dev);
		वापस -ENXIO;
	पूर्ण
	mas->tx_fअगरo_depth = geni_se_get_tx_fअगरo_depth(se);

	/* Width of Tx and Rx FIFO is same */
	mas->fअगरo_width_bits = geni_se_get_tx_fअगरo_width(se);

	/*
	 * Hardware programming guide suggests to configure
	 * RX FIFO RFR level to fअगरo_depth-2.
	 */
	geni_se_init(se, mas->tx_fअगरo_depth - 3, mas->tx_fअगरo_depth - 2);
	/* Transmit an entire FIFO worth of data per IRQ */
	mas->tx_wm = 1;
	ver = geni_se_get_qup_hw_version(se);
	major = GENI_SE_VERSION_MAJOR(ver);
	minor = GENI_SE_VERSION_MINOR(ver);

	अगर (major == 1 && minor == 0)
		mas->oversampling = 2;
	अन्यथा
		mas->oversampling = 1;

	geni_se_select_mode(se, GENI_SE_FIFO);

	/* We always control CS manually */
	spi_tx_cfg = पढ़ोl(se->base + SE_SPI_TRANS_CFG);
	spi_tx_cfg &= ~CS_TOGGLE;
	ग_लिखोl(spi_tx_cfg, se->base + SE_SPI_TRANS_CFG);

	pm_runसमय_put(mas->dev);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक geni_byte_per_fअगरo_word(काष्ठा spi_geni_master *mas)
अणु
	/*
	 * Calculate how many bytes we'll put in each FIFO word.  If the
	 * transfer words करोn't pack cleanly into a FIFO word we'll just put
	 * one transfer word in each FIFO word.  If they करो pack we'll pack 'em.
	 */
	अगर (mas->fअगरo_width_bits % mas->cur_bits_per_word)
		वापस roundup_घात_of_two(DIV_ROUND_UP(mas->cur_bits_per_word,
						       BITS_PER_BYTE));

	वापस mas->fअगरo_width_bits / BITS_PER_BYTE;
पूर्ण

अटल bool geni_spi_handle_tx(काष्ठा spi_geni_master *mas)
अणु
	काष्ठा geni_se *se = &mas->se;
	अचिन्हित पूर्णांक max_bytes;
	स्थिर u8 *tx_buf;
	अचिन्हित पूर्णांक bytes_per_fअगरo_word = geni_byte_per_fअगरo_word(mas);
	अचिन्हित पूर्णांक i = 0;

	/* Stop the watermark IRQ अगर nothing to send */
	अगर (!mas->cur_xfer) अणु
		ग_लिखोl(0, se->base + SE_GENI_TX_WATERMARK_REG);
		वापस false;
	पूर्ण

	max_bytes = (mas->tx_fअगरo_depth - mas->tx_wm) * bytes_per_fअगरo_word;
	अगर (mas->tx_rem_bytes < max_bytes)
		max_bytes = mas->tx_rem_bytes;

	tx_buf = mas->cur_xfer->tx_buf + mas->cur_xfer->len - mas->tx_rem_bytes;
	जबतक (i < max_bytes) अणु
		अचिन्हित पूर्णांक j;
		अचिन्हित पूर्णांक bytes_to_ग_लिखो;
		u32 fअगरo_word = 0;
		u8 *fअगरo_byte = (u8 *)&fअगरo_word;

		bytes_to_ग_लिखो = min(bytes_per_fअगरo_word, max_bytes - i);
		क्रम (j = 0; j < bytes_to_ग_लिखो; j++)
			fअगरo_byte[j] = tx_buf[i++];
		ioग_लिखो32_rep(se->base + SE_GENI_TX_FIFOn, &fअगरo_word, 1);
	पूर्ण
	mas->tx_rem_bytes -= max_bytes;
	अगर (!mas->tx_rem_bytes) अणु
		ग_लिखोl(0, se->base + SE_GENI_TX_WATERMARK_REG);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम geni_spi_handle_rx(काष्ठा spi_geni_master *mas)
अणु
	काष्ठा geni_se *se = &mas->se;
	u32 rx_fअगरo_status;
	अचिन्हित पूर्णांक rx_bytes;
	अचिन्हित पूर्णांक rx_last_byte_valid;
	u8 *rx_buf;
	अचिन्हित पूर्णांक bytes_per_fअगरo_word = geni_byte_per_fअगरo_word(mas);
	अचिन्हित पूर्णांक i = 0;

	rx_fअगरo_status = पढ़ोl(se->base + SE_GENI_RX_FIFO_STATUS);
	rx_bytes = (rx_fअगरo_status & RX_FIFO_WC_MSK) * bytes_per_fअगरo_word;
	अगर (rx_fअगरo_status & RX_LAST) अणु
		rx_last_byte_valid = rx_fअगरo_status & RX_LAST_BYTE_VALID_MSK;
		rx_last_byte_valid >>= RX_LAST_BYTE_VALID_SHFT;
		अगर (rx_last_byte_valid && rx_last_byte_valid < 4)
			rx_bytes -= bytes_per_fअगरo_word - rx_last_byte_valid;
	पूर्ण

	/* Clear out the FIFO and bail अगर nowhere to put it */
	अगर (!mas->cur_xfer) अणु
		क्रम (i = 0; i < DIV_ROUND_UP(rx_bytes, bytes_per_fअगरo_word); i++)
			पढ़ोl(se->base + SE_GENI_RX_FIFOn);
		वापस;
	पूर्ण

	अगर (mas->rx_rem_bytes < rx_bytes)
		rx_bytes = mas->rx_rem_bytes;

	rx_buf = mas->cur_xfer->rx_buf + mas->cur_xfer->len - mas->rx_rem_bytes;
	जबतक (i < rx_bytes) अणु
		u32 fअगरo_word = 0;
		u8 *fअगरo_byte = (u8 *)&fअगरo_word;
		अचिन्हित पूर्णांक bytes_to_पढ़ो;
		अचिन्हित पूर्णांक j;

		bytes_to_पढ़ो = min(bytes_per_fअगरo_word, rx_bytes - i);
		ioपढ़ो32_rep(se->base + SE_GENI_RX_FIFOn, &fअगरo_word, 1);
		क्रम (j = 0; j < bytes_to_पढ़ो; j++)
			rx_buf[i++] = fअगरo_byte[j];
	पूर्ण
	mas->rx_rem_bytes -= rx_bytes;
पूर्ण

अटल व्योम setup_fअगरo_xfer(काष्ठा spi_transfer *xfer,
				काष्ठा spi_geni_master *mas,
				u16 mode, काष्ठा spi_master *spi)
अणु
	u32 m_cmd = 0;
	u32 len;
	काष्ठा geni_se *se = &mas->se;
	पूर्णांक ret;

	/*
	 * Ensure that our पूर्णांकerrupt handler isn't still running from some
	 * prior command beक्रमe we start messing with the hardware behind
	 * its back.  We करोn't need to _keep_ the lock here since we're only
	 * worried about racing with out पूर्णांकerrupt handler.  The SPI core
	 * alपढ़ोy handles making sure that we're not trying to करो two
	 * transfers at once or setting a chip select and करोing a transfer
	 * concurrently.
	 *
	 * NOTE: we actually _can't_ hold the lock here because possibly we
	 * might call clk_set_rate() which needs to be able to sleep.
	 */
	spin_lock_irq(&mas->lock);
	spin_unlock_irq(&mas->lock);

	अगर (xfer->bits_per_word != mas->cur_bits_per_word) अणु
		spi_setup_word_len(mas, mode, xfer->bits_per_word);
		mas->cur_bits_per_word = xfer->bits_per_word;
	पूर्ण

	/* Speed and bits per word can be overridden per transfer */
	ret = geni_spi_set_घड़ी_and_bw(mas, xfer->speed_hz);
	अगर (ret)
		वापस;

	mas->tx_rem_bytes = 0;
	mas->rx_rem_bytes = 0;

	अगर (!(mas->cur_bits_per_word % MIN_WORD_LEN))
		len = xfer->len * BITS_PER_BYTE / mas->cur_bits_per_word;
	अन्यथा
		len = xfer->len / (mas->cur_bits_per_word / BITS_PER_BYTE + 1);
	len &= TRANS_LEN_MSK;

	mas->cur_xfer = xfer;
	अगर (xfer->tx_buf) अणु
		m_cmd |= SPI_TX_ONLY;
		mas->tx_rem_bytes = xfer->len;
		ग_लिखोl(len, se->base + SE_SPI_TX_TRANS_LEN);
	पूर्ण

	अगर (xfer->rx_buf) अणु
		m_cmd |= SPI_RX_ONLY;
		ग_लिखोl(len, se->base + SE_SPI_RX_TRANS_LEN);
		mas->rx_rem_bytes = xfer->len;
	पूर्ण

	/*
	 * Lock around right beक्रमe we start the transfer since our
	 * पूर्णांकerrupt could come in at any समय now.
	 */
	spin_lock_irq(&mas->lock);
	geni_se_setup_m_cmd(se, m_cmd, FRAGMENTATION);

	/*
	 * TX_WATERMARK_REG should be set after SPI configuration and
	 * setting up GENI SE engine, as driver starts data transfer
	 * क्रम the watermark पूर्णांकerrupt.
	 */
	अगर (m_cmd & SPI_TX_ONLY) अणु
		अगर (geni_spi_handle_tx(mas))
			ग_लिखोl(mas->tx_wm, se->base + SE_GENI_TX_WATERMARK_REG);
	पूर्ण
	spin_unlock_irq(&mas->lock);
पूर्ण

अटल पूर्णांक spi_geni_transfer_one(काष्ठा spi_master *spi,
				काष्ठा spi_device *slv,
				काष्ठा spi_transfer *xfer)
अणु
	काष्ठा spi_geni_master *mas = spi_master_get_devdata(spi);

	अगर (spi_geni_is_पात_still_pending(mas))
		वापस -EBUSY;

	/* Terminate and वापस success क्रम 0 byte length transfer */
	अगर (!xfer->len)
		वापस 0;

	setup_fअगरo_xfer(xfer, mas, slv->mode, spi);
	वापस 1;
पूर्ण

अटल irqवापस_t geni_spi_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा spi_master *spi = data;
	काष्ठा spi_geni_master *mas = spi_master_get_devdata(spi);
	काष्ठा geni_se *se = &mas->se;
	u32 m_irq;

	m_irq = पढ़ोl(se->base + SE_GENI_M_IRQ_STATUS);
	अगर (!m_irq)
		वापस IRQ_NONE;

	अगर (m_irq & (M_CMD_OVERRUN_EN | M_ILLEGAL_CMD_EN | M_CMD_FAILURE_EN |
		     M_RX_FIFO_RD_ERR_EN | M_RX_FIFO_WR_ERR_EN |
		     M_TX_FIFO_RD_ERR_EN | M_TX_FIFO_WR_ERR_EN))
		dev_warn(mas->dev, "Unexpected IRQ err status %#010x\n", m_irq);

	spin_lock(&mas->lock);

	अगर ((m_irq & M_RX_FIFO_WATERMARK_EN) || (m_irq & M_RX_FIFO_LAST_EN))
		geni_spi_handle_rx(mas);

	अगर (m_irq & M_TX_FIFO_WATERMARK_EN)
		geni_spi_handle_tx(mas);

	अगर (m_irq & M_CMD_DONE_EN) अणु
		अगर (mas->cur_xfer) अणु
			spi_finalize_current_transfer(spi);
			mas->cur_xfer = शून्य;
			/*
			 * If this happens, then a CMD_DONE came beक्रमe all the
			 * Tx buffer bytes were sent out. This is unusual, log
			 * this condition and disable the WM पूर्णांकerrupt to
			 * prevent the प्रणाली from stalling due an पूर्णांकerrupt
			 * storm.
			 *
			 * If this happens when all Rx bytes haven't been
			 * received, log the condition. The only known समय
			 * this can happen is अगर bits_per_word != 8 and some
			 * रेजिस्टरs that expect xfer lengths in num spi_words
			 * weren't written correctly.
			 */
			अगर (mas->tx_rem_bytes) अणु
				ग_लिखोl(0, se->base + SE_GENI_TX_WATERMARK_REG);
				dev_err(mas->dev, "Premature done. tx_rem = %d bpw%d\n",
					mas->tx_rem_bytes, mas->cur_bits_per_word);
			पूर्ण
			अगर (mas->rx_rem_bytes)
				dev_err(mas->dev, "Premature done. rx_rem = %d bpw%d\n",
					mas->rx_rem_bytes, mas->cur_bits_per_word);
		पूर्ण अन्यथा अणु
			complete(&mas->cs_करोne);
		पूर्ण
	पूर्ण

	अगर (m_irq & M_CMD_CANCEL_EN)
		complete(&mas->cancel_करोne);
	अगर (m_irq & M_CMD_ABORT_EN)
		complete(&mas->पात_करोne);

	/*
	 * It's safe or a good idea to Ack all of our our पूर्णांकerrupts at the
	 * end of the function. Specअगरically:
	 * - M_CMD_DONE_EN / M_RX_FIFO_LAST_EN: Edge triggered पूर्णांकerrupts and
	 *   clearing Acks. Clearing at the end relies on nobody अन्यथा having
	 *   started a new transfer yet or अन्यथा we could be clearing _their_
	 *   करोne bit, but everyone grअसल the spinlock beक्रमe starting a new
	 *   transfer.
	 * - M_RX_FIFO_WATERMARK_EN / M_TX_FIFO_WATERMARK_EN: These appear
	 *   to be "latched level" पूर्णांकerrupts so it's important to clear them
	 *   _after_ you've handled the condition and always safe to करो so
	 *   since they'll re-assert if they're still happening.
	 */
	ग_लिखोl(m_irq, se->base + SE_GENI_M_IRQ_CLEAR);

	spin_unlock(&mas->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक spi_geni_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, irq;
	काष्ठा spi_master *spi;
	काष्ठा spi_geni_master *mas;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा device *dev = &pdev->dev;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	clk = devm_clk_get(dev, "se");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	spi = devm_spi_alloc_master(dev, माप(*mas));
	अगर (!spi)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, spi);
	mas = spi_master_get_devdata(spi);
	mas->irq = irq;
	mas->dev = dev;
	mas->se.dev = dev;
	mas->se.wrapper = dev_get_drvdata(dev->parent);
	mas->se.base = base;
	mas->se.clk = clk;

	ret = devm_pm_opp_set_clkname(&pdev->dev, "se");
	अगर (ret)
		वापस ret;
	/* OPP table is optional */
	ret = devm_pm_opp_of_add_table(&pdev->dev);
	अगर (ret && ret != -ENODEV) अणु
		dev_err(&pdev->dev, "invalid OPP table in device tree\n");
		वापस ret;
	पूर्ण

	spi->bus_num = -1;
	spi->dev.of_node = dev->of_node;
	spi->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LOOP | SPI_CS_HIGH;
	spi->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 32);
	spi->num_chipselect = 4;
	spi->max_speed_hz = 50000000;
	spi->prepare_message = spi_geni_prepare_message;
	spi->transfer_one = spi_geni_transfer_one;
	spi->स्वतः_runसमय_pm = true;
	spi->handle_err = handle_fअगरo_समयout;
	spi->set_cs = spi_geni_set_cs;
	spi->use_gpio_descriptors = true;

	init_completion(&mas->cs_करोne);
	init_completion(&mas->cancel_करोne);
	init_completion(&mas->पात_करोne);
	spin_lock_init(&mas->lock);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 250);
	pm_runसमय_enable(dev);

	ret = geni_icc_get(&mas->se, शून्य);
	अगर (ret)
		जाओ spi_geni_probe_runसमय_disable;
	/* Set the bus quota to a reasonable value क्रम रेजिस्टर access */
	mas->se.icc_paths[GENI_TO_CORE].avg_bw = Bps_to_icc(CORE_2X_50_MHZ);
	mas->se.icc_paths[CPU_TO_GENI].avg_bw = GENI_DEFAULT_BW;

	ret = geni_icc_set_bw(&mas->se);
	अगर (ret)
		जाओ spi_geni_probe_runसमय_disable;

	ret = spi_geni_init(mas);
	अगर (ret)
		जाओ spi_geni_probe_runसमय_disable;

	ret = request_irq(mas->irq, geni_spi_isr, 0, dev_name(dev), spi);
	अगर (ret)
		जाओ spi_geni_probe_runसमय_disable;

	ret = spi_रेजिस्टर_master(spi);
	अगर (ret)
		जाओ spi_geni_probe_मुक्त_irq;

	वापस 0;
spi_geni_probe_मुक्त_irq:
	मुक्त_irq(mas->irq, spi);
spi_geni_probe_runसमय_disable:
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक spi_geni_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *spi = platक्रमm_get_drvdata(pdev);
	काष्ठा spi_geni_master *mas = spi_master_get_devdata(spi);

	/* Unरेजिस्टर _beक्रमe_ disabling pm_runसमय() so we stop transfers */
	spi_unरेजिस्टर_master(spi);

	मुक्त_irq(mas->irq, spi);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused spi_geni_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *spi = dev_get_drvdata(dev);
	काष्ठा spi_geni_master *mas = spi_master_get_devdata(spi);
	पूर्णांक ret;

	/* Drop the perक्रमmance state vote */
	dev_pm_opp_set_rate(dev, 0);

	ret = geni_se_resources_off(&mas->se);
	अगर (ret)
		वापस ret;

	वापस geni_icc_disable(&mas->se);
पूर्ण

अटल पूर्णांक __maybe_unused spi_geni_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *spi = dev_get_drvdata(dev);
	काष्ठा spi_geni_master *mas = spi_master_get_devdata(spi);
	पूर्णांक ret;

	ret = geni_icc_enable(&mas->se);
	अगर (ret)
		वापस ret;

	ret = geni_se_resources_on(&mas->se);
	अगर (ret)
		वापस ret;

	वापस dev_pm_opp_set_rate(mas->dev, mas->cur_sclk_hz);
पूर्ण

अटल पूर्णांक __maybe_unused spi_geni_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *spi = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = spi_master_suspend(spi);
	अगर (ret)
		वापस ret;

	ret = pm_runसमय_क्रमce_suspend(dev);
	अगर (ret)
		spi_master_resume(spi);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused spi_geni_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *spi = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret)
		वापस ret;

	ret = spi_master_resume(spi);
	अगर (ret)
		pm_runसमय_क्रमce_suspend(dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops spi_geni_pm_ops = अणु
	SET_RUNTIME_PM_OPS(spi_geni_runसमय_suspend,
					spi_geni_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(spi_geni_suspend, spi_geni_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id spi_geni_dt_match[] = अणु
	अणु .compatible = "qcom,geni-spi" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spi_geni_dt_match);

अटल काष्ठा platक्रमm_driver spi_geni_driver = अणु
	.probe  = spi_geni_probe,
	.हटाओ = spi_geni_हटाओ,
	.driver = अणु
		.name = "geni_spi",
		.pm = &spi_geni_pm_ops,
		.of_match_table = spi_geni_dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(spi_geni_driver);

MODULE_DESCRIPTION("SPI driver for GENI based QUP cores");
MODULE_LICENSE("GPL v2");
