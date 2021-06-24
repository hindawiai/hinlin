<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 STMicroelectronics
 *
 * I2C master mode controller driver, used in STMicroelectronics devices.
 *
 * Author: Maxime Coquelin <maxime.coquelin@st.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>

/* SSC रेजिस्टरs */
#घोषणा SSC_BRG				0x000
#घोषणा SSC_TBUF			0x004
#घोषणा SSC_RBUF			0x008
#घोषणा SSC_CTL				0x00C
#घोषणा SSC_IEN				0x010
#घोषणा SSC_STA				0x014
#घोषणा SSC_I2C				0x018
#घोषणा SSC_SLAD			0x01C
#घोषणा SSC_REP_START_HOLD		0x020
#घोषणा SSC_START_HOLD			0x024
#घोषणा SSC_REP_START_SETUP		0x028
#घोषणा SSC_DATA_SETUP			0x02C
#घोषणा SSC_STOP_SETUP			0x030
#घोषणा SSC_BUS_FREE			0x034
#घोषणा SSC_TX_FSTAT			0x038
#घोषणा SSC_RX_FSTAT			0x03C
#घोषणा SSC_PRE_SCALER_BRG		0x040
#घोषणा SSC_CLR				0x080
#घोषणा SSC_NOISE_SUPP_WIDTH		0x100
#घोषणा SSC_PRSCALER			0x104
#घोषणा SSC_NOISE_SUPP_WIDTH_DATAOUT	0x108
#घोषणा SSC_PRSCALER_DATAOUT		0x10c

/* SSC Control */
#घोषणा SSC_CTL_DATA_WIDTH_9		0x8
#घोषणा SSC_CTL_DATA_WIDTH_MSK		0xf
#घोषणा SSC_CTL_BM			0xf
#घोषणा SSC_CTL_HB			BIT(4)
#घोषणा SSC_CTL_PH			BIT(5)
#घोषणा SSC_CTL_PO			BIT(6)
#घोषणा SSC_CTL_SR			BIT(7)
#घोषणा SSC_CTL_MS			BIT(8)
#घोषणा SSC_CTL_EN			BIT(9)
#घोषणा SSC_CTL_LPB			BIT(10)
#घोषणा SSC_CTL_EN_TX_FIFO		BIT(11)
#घोषणा SSC_CTL_EN_RX_FIFO		BIT(12)
#घोषणा SSC_CTL_EN_CLST_RX		BIT(13)

/* SSC Interrupt Enable */
#घोषणा SSC_IEN_RIEN			BIT(0)
#घोषणा SSC_IEN_TIEN			BIT(1)
#घोषणा SSC_IEN_TEEN			BIT(2)
#घोषणा SSC_IEN_REEN			BIT(3)
#घोषणा SSC_IEN_PEEN			BIT(4)
#घोषणा SSC_IEN_AASEN			BIT(6)
#घोषणा SSC_IEN_STOPEN			BIT(7)
#घोषणा SSC_IEN_ARBLEN			BIT(8)
#घोषणा SSC_IEN_NACKEN			BIT(10)
#घोषणा SSC_IEN_REPSTRTEN		BIT(11)
#घोषणा SSC_IEN_TX_FIFO_HALF		BIT(12)
#घोषणा SSC_IEN_RX_FIFO_HALF_FULL	BIT(14)

/* SSC Status */
#घोषणा SSC_STA_RIR			BIT(0)
#घोषणा SSC_STA_TIR			BIT(1)
#घोषणा SSC_STA_TE			BIT(2)
#घोषणा SSC_STA_RE			BIT(3)
#घोषणा SSC_STA_PE			BIT(4)
#घोषणा SSC_STA_CLST			BIT(5)
#घोषणा SSC_STA_AAS			BIT(6)
#घोषणा SSC_STA_STOP			BIT(7)
#घोषणा SSC_STA_ARBL			BIT(8)
#घोषणा SSC_STA_BUSY			BIT(9)
#घोषणा SSC_STA_NACK			BIT(10)
#घोषणा SSC_STA_REPSTRT			BIT(11)
#घोषणा SSC_STA_TX_FIFO_HALF		BIT(12)
#घोषणा SSC_STA_TX_FIFO_FULL		BIT(13)
#घोषणा SSC_STA_RX_FIFO_HALF		BIT(14)

/* SSC I2C Control */
#घोषणा SSC_I2C_I2CM			BIT(0)
#घोषणा SSC_I2C_STRTG			BIT(1)
#घोषणा SSC_I2C_STOPG			BIT(2)
#घोषणा SSC_I2C_ACKG			BIT(3)
#घोषणा SSC_I2C_AD10			BIT(4)
#घोषणा SSC_I2C_TXENB			BIT(5)
#घोषणा SSC_I2C_REPSTRTG		BIT(11)
#घोषणा SSC_I2C_SLAVE_DISABLE		BIT(12)

/* SSC Tx FIFO Status */
#घोषणा SSC_TX_FSTAT_STATUS		0x07

/* SSC Rx FIFO Status */
#घोषणा SSC_RX_FSTAT_STATUS		0x07

/* SSC Clear bit operation */
#घोषणा SSC_CLR_SSCAAS			BIT(6)
#घोषणा SSC_CLR_SSCSTOP			BIT(7)
#घोषणा SSC_CLR_SSCARBL			BIT(8)
#घोषणा SSC_CLR_NACK			BIT(10)
#घोषणा SSC_CLR_REPSTRT			BIT(11)

/* SSC Clock Prescaler */
#घोषणा SSC_PRSC_VALUE			0x0f


#घोषणा SSC_TXFIFO_SIZE			0x8
#घोषणा SSC_RXFIFO_SIZE			0x8

क्रमागत st_i2c_mode अणु
	I2C_MODE_STANDARD,
	I2C_MODE_FAST,
	I2C_MODE_END,
पूर्ण;

/**
 * काष्ठा st_i2c_timings - per-Mode tuning parameters
 * @rate: I2C bus rate
 * @rep_start_hold: I2C repeated start hold समय requirement
 * @rep_start_setup: I2C repeated start set up समय requirement
 * @start_hold: I2C start hold समय requirement
 * @data_setup_समय: I2C data set up समय requirement
 * @stop_setup_समय: I2C stop set up समय requirement
 * @bus_मुक्त_समय: I2C bus मुक्त समय requirement
 * @sda_pulse_min_limit: I2C SDA pulse mini width limit
 */
काष्ठा st_i2c_timings अणु
	u32 rate;
	u32 rep_start_hold;
	u32 rep_start_setup;
	u32 start_hold;
	u32 data_setup_समय;
	u32 stop_setup_समय;
	u32 bus_मुक्त_समय;
	u32 sda_pulse_min_limit;
पूर्ण;

/**
 * काष्ठा st_i2c_client - client specअगरic data
 * @addr: 8-bit slave addr, including r/w bit
 * @count: number of bytes to be transfered
 * @xfered: number of bytes alपढ़ोy transferred
 * @buf: data buffer
 * @result: result of the transfer
 * @stop: last I2C msg to be sent, i.e. STOP to be generated
 */
काष्ठा st_i2c_client अणु
	u8	addr;
	u32	count;
	u32	xfered;
	u8	*buf;
	पूर्णांक	result;
	bool	stop;
पूर्ण;

/**
 * काष्ठा st_i2c_dev - निजी data of the controller
 * @adap: I2C adapter क्रम this controller
 * @dev: device क्रम this controller
 * @base: भव memory area
 * @complete: completion of I2C message
 * @irq: पूर्णांकerrupt line क्रम th controller
 * @clk: hw ssc block घड़ी
 * @mode: I2C mode of the controller. Standard or Fast only supported
 * @scl_min_width_us: SCL line minimum pulse width in us
 * @sda_min_width_us: SDA line minimum pulse width in us
 * @client: I2C transfert inक्रमmation
 * @busy: I2C transfer on-going
 */
काष्ठा st_i2c_dev अणु
	काष्ठा i2c_adapter	adap;
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	काष्ठा completion	complete;
	पूर्णांक			irq;
	काष्ठा clk		*clk;
	पूर्णांक			mode;
	u32			scl_min_width_us;
	u32			sda_min_width_us;
	काष्ठा st_i2c_client	client;
	bool			busy;
पूर्ण;

अटल अंतरभूत व्योम st_i2c_set_bits(व्योम __iomem *reg, u32 mask)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) | mask, reg);
पूर्ण

अटल अंतरभूत व्योम st_i2c_clr_bits(व्योम __iomem *reg, u32 mask)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) & ~mask, reg);
पूर्ण

/*
 * From I2C Specअगरications v0.5.
 *
 * All the values below have +10% margin added to be
 * compatible with some out-of-spec devices,
 * like HDMI link of the Toshiba 19AV600 TV.
 */
अटल काष्ठा st_i2c_timings i2c_timings[] = अणु
	[I2C_MODE_STANDARD] = अणु
		.rate			= I2C_MAX_STANDARD_MODE_FREQ,
		.rep_start_hold		= 4400,
		.rep_start_setup	= 5170,
		.start_hold		= 4400,
		.data_setup_समय	= 275,
		.stop_setup_समय	= 4400,
		.bus_मुक्त_समय		= 5170,
	पूर्ण,
	[I2C_MODE_FAST] = अणु
		.rate			= I2C_MAX_FAST_MODE_FREQ,
		.rep_start_hold		= 660,
		.rep_start_setup	= 660,
		.start_hold		= 660,
		.data_setup_समय	= 110,
		.stop_setup_समय	= 660,
		.bus_मुक्त_समय		= 1430,
	पूर्ण,
पूर्ण;

अटल व्योम st_i2c_flush_rx_fअगरo(काष्ठा st_i2c_dev *i2c_dev)
अणु
	पूर्णांक count, i;

	/*
	 * Counter only counts up to 7 but fअगरo size is 8...
	 * When fअगरo is full, counter is 0 and RIR bit of status रेजिस्टर is
	 * set
	 */
	अगर (पढ़ोl_relaxed(i2c_dev->base + SSC_STA) & SSC_STA_RIR)
		count = SSC_RXFIFO_SIZE;
	अन्यथा
		count = पढ़ोl_relaxed(i2c_dev->base + SSC_RX_FSTAT) &
			SSC_RX_FSTAT_STATUS;

	क्रम (i = 0; i < count; i++)
		पढ़ोl_relaxed(i2c_dev->base + SSC_RBUF);
पूर्ण

अटल व्योम st_i2c_soft_reset(काष्ठा st_i2c_dev *i2c_dev)
अणु
	/*
	 * FIFO needs to be emptied beक्रमe reseting the IP,
	 * अन्यथा the controller उठाओs a BUSY error.
	 */
	st_i2c_flush_rx_fअगरo(i2c_dev);

	st_i2c_set_bits(i2c_dev->base + SSC_CTL, SSC_CTL_SR);
	st_i2c_clr_bits(i2c_dev->base + SSC_CTL, SSC_CTL_SR);
पूर्ण

/**
 * st_i2c_hw_config() - Prepare SSC block, calculate and apply tuning timings
 * @i2c_dev: Controller's निजी data
 */
अटल व्योम st_i2c_hw_config(काष्ठा st_i2c_dev *i2c_dev)
अणु
	अचिन्हित दीर्घ rate;
	u32 val, ns_per_clk;
	काष्ठा st_i2c_timings *t = &i2c_timings[i2c_dev->mode];

	st_i2c_soft_reset(i2c_dev);

	val = SSC_CLR_REPSTRT | SSC_CLR_NACK | SSC_CLR_SSCARBL |
		SSC_CLR_SSCAAS | SSC_CLR_SSCSTOP;
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_CLR);

	/* SSC Control रेजिस्टर setup */
	val = SSC_CTL_PO | SSC_CTL_PH | SSC_CTL_HB | SSC_CTL_DATA_WIDTH_9;
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_CTL);

	rate = clk_get_rate(i2c_dev->clk);
	ns_per_clk = 1000000000 / rate;

	/* Baudrate */
	val = rate / (2 * t->rate);
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_BRG);

	/* Pre-scaler baudrate */
	ग_लिखोl_relaxed(1, i2c_dev->base + SSC_PRE_SCALER_BRG);

	/* Enable I2C mode */
	ग_लिखोl_relaxed(SSC_I2C_I2CM, i2c_dev->base + SSC_I2C);

	/* Repeated start hold समय */
	val = t->rep_start_hold / ns_per_clk;
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_REP_START_HOLD);

	/* Repeated start set up समय */
	val = t->rep_start_setup / ns_per_clk;
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_REP_START_SETUP);

	/* Start hold समय */
	val = t->start_hold / ns_per_clk;
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_START_HOLD);

	/* Data set up समय */
	val = t->data_setup_समय / ns_per_clk;
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_DATA_SETUP);

	/* Stop set up समय */
	val = t->stop_setup_समय / ns_per_clk;
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_STOP_SETUP);

	/* Bus मुक्त समय */
	val = t->bus_मुक्त_समय / ns_per_clk;
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_BUS_FREE);

	/* Prescalers set up */
	val = rate / 10000000;
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_PRSCALER);
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_PRSCALER_DATAOUT);

	/* Noise suppression witdh */
	val = i2c_dev->scl_min_width_us * rate / 100000000;
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_NOISE_SUPP_WIDTH);

	/* Noise suppression max output data delay width */
	val = i2c_dev->sda_min_width_us * rate / 100000000;
	ग_लिखोl_relaxed(val, i2c_dev->base + SSC_NOISE_SUPP_WIDTH_DATAOUT);
पूर्ण

अटल पूर्णांक st_i2c_recover_bus(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा st_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);
	u32 ctl;

	dev_dbg(i2c_dev->dev, "Trying to recover bus\n");

	/*
	 * SSP IP is dual role SPI/I2C to generate 9 घड़ी pulses
	 * we चयन to SPI node, 9 bit words and ग_लिखो a 0. This
	 * has been validate with a oscilloscope and is easier
	 * than चयनing to GPIO mode.
	 */

	/* Disable पूर्णांकerrupts */
	ग_लिखोl_relaxed(0, i2c_dev->base + SSC_IEN);

	st_i2c_hw_config(i2c_dev);

	ctl = SSC_CTL_EN | SSC_CTL_MS |	SSC_CTL_EN_RX_FIFO | SSC_CTL_EN_TX_FIFO;
	st_i2c_set_bits(i2c_dev->base + SSC_CTL, ctl);

	st_i2c_clr_bits(i2c_dev->base + SSC_I2C, SSC_I2C_I2CM);
	usleep_range(8000, 10000);

	ग_लिखोl_relaxed(0, i2c_dev->base + SSC_TBUF);
	usleep_range(2000, 4000);
	st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_I2CM);

	वापस 0;
पूर्ण

अटल पूर्णांक st_i2c_रुको_मुक्त_bus(काष्ठा st_i2c_dev *i2c_dev)
अणु
	u32 sta;
	पूर्णांक i, ret;

	क्रम (i = 0; i < 10; i++) अणु
		sta = पढ़ोl_relaxed(i2c_dev->base + SSC_STA);
		अगर (!(sta & SSC_STA_BUSY))
			वापस 0;

		usleep_range(2000, 4000);
	पूर्ण

	dev_err(i2c_dev->dev, "bus not free (status = 0x%08x)\n", sta);

	ret = i2c_recover_bus(&i2c_dev->adap);
	अगर (ret) अणु
		dev_err(i2c_dev->dev, "Failed to recover the bus (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस -EBUSY;
पूर्ण

/**
 * st_i2c_ग_लिखो_tx_fअगरo() - Write a byte in the Tx FIFO
 * @i2c_dev: Controller's निजी data
 * @byte: Data to ग_लिखो in the Tx FIFO
 */
अटल अंतरभूत व्योम st_i2c_ग_लिखो_tx_fअगरo(काष्ठा st_i2c_dev *i2c_dev, u8 byte)
अणु
	u16 tbuf = byte << 1;

	ग_लिखोl_relaxed(tbuf | 1, i2c_dev->base + SSC_TBUF);
पूर्ण

/**
 * st_i2c_wr_fill_tx_fअगरo() - Fill the Tx FIFO in ग_लिखो mode
 * @i2c_dev: Controller's निजी data
 *
 * This functions fills the Tx FIFO with I2C transfert buffer when
 * in ग_लिखो mode.
 */
अटल व्योम st_i2c_wr_fill_tx_fअगरo(काष्ठा st_i2c_dev *i2c_dev)
अणु
	काष्ठा st_i2c_client *c = &i2c_dev->client;
	u32 tx_ख_स्थिति, sta;
	पूर्णांक i;

	sta = पढ़ोl_relaxed(i2c_dev->base + SSC_STA);
	अगर (sta & SSC_STA_TX_FIFO_FULL)
		वापस;

	tx_ख_स्थिति = पढ़ोl_relaxed(i2c_dev->base + SSC_TX_FSTAT);
	tx_ख_स्थिति &= SSC_TX_FSTAT_STATUS;

	अगर (c->count < (SSC_TXFIFO_SIZE - tx_ख_स्थिति))
		i = c->count;
	अन्यथा
		i = SSC_TXFIFO_SIZE - tx_ख_स्थिति;

	क्रम (; i > 0; i--, c->count--, c->buf++)
		st_i2c_ग_लिखो_tx_fअगरo(i2c_dev, *c->buf);
पूर्ण

/**
 * st_i2c_rd_fill_tx_fअगरo() - Fill the Tx FIFO in पढ़ो mode
 * @i2c_dev: Controller's निजी data
 * @max: Maximum amount of data to fill पूर्णांकo the Tx FIFO
 *
 * This functions fills the Tx FIFO with fixed pattern when
 * in पढ़ो mode to trigger घड़ी.
 */
अटल व्योम st_i2c_rd_fill_tx_fअगरo(काष्ठा st_i2c_dev *i2c_dev, पूर्णांक max)
अणु
	काष्ठा st_i2c_client *c = &i2c_dev->client;
	u32 tx_ख_स्थिति, sta;
	पूर्णांक i;

	sta = पढ़ोl_relaxed(i2c_dev->base + SSC_STA);
	अगर (sta & SSC_STA_TX_FIFO_FULL)
		वापस;

	tx_ख_स्थिति = पढ़ोl_relaxed(i2c_dev->base + SSC_TX_FSTAT);
	tx_ख_स्थिति &= SSC_TX_FSTAT_STATUS;

	अगर (max < (SSC_TXFIFO_SIZE - tx_ख_स्थिति))
		i = max;
	अन्यथा
		i = SSC_TXFIFO_SIZE - tx_ख_स्थिति;

	क्रम (; i > 0; i--, c->xfered++)
		st_i2c_ग_लिखो_tx_fअगरo(i2c_dev, 0xff);
पूर्ण

अटल व्योम st_i2c_पढ़ो_rx_fअगरo(काष्ठा st_i2c_dev *i2c_dev)
अणु
	काष्ठा st_i2c_client *c = &i2c_dev->client;
	u32 i, sta;
	u16 rbuf;

	sta = पढ़ोl_relaxed(i2c_dev->base + SSC_STA);
	अगर (sta & SSC_STA_RIR) अणु
		i = SSC_RXFIFO_SIZE;
	पूर्ण अन्यथा अणु
		i = पढ़ोl_relaxed(i2c_dev->base + SSC_RX_FSTAT);
		i &= SSC_RX_FSTAT_STATUS;
	पूर्ण

	क्रम (; (i > 0) && (c->count > 0); i--, c->count--) अणु
		rbuf = पढ़ोl_relaxed(i2c_dev->base + SSC_RBUF) >> 1;
		*c->buf++ = (u8)rbuf & 0xff;
	पूर्ण

	अगर (i) अणु
		dev_err(i2c_dev->dev, "Unexpected %d bytes in rx fifo\n", i);
		st_i2c_flush_rx_fअगरo(i2c_dev);
	पूर्ण
पूर्ण

/**
 * st_i2c_terminate_xfer() - Send either STOP or REPSTART condition
 * @i2c_dev: Controller's निजी data
 */
अटल व्योम st_i2c_terminate_xfer(काष्ठा st_i2c_dev *i2c_dev)
अणु
	काष्ठा st_i2c_client *c = &i2c_dev->client;

	st_i2c_clr_bits(i2c_dev->base + SSC_IEN, SSC_IEN_TEEN);
	st_i2c_clr_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STRTG);

	अगर (c->stop) अणु
		st_i2c_set_bits(i2c_dev->base + SSC_IEN, SSC_IEN_STOPEN);
		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STOPG);
	पूर्ण अन्यथा अणु
		st_i2c_set_bits(i2c_dev->base + SSC_IEN, SSC_IEN_REPSTRTEN);
		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_REPSTRTG);
	पूर्ण
पूर्ण

/**
 * st_i2c_handle_ग_लिखो() - Handle FIFO empty पूर्णांकerrupt in हाल of ग_लिखो
 * @i2c_dev: Controller's निजी data
 */
अटल व्योम st_i2c_handle_ग_लिखो(काष्ठा st_i2c_dev *i2c_dev)
अणु
	काष्ठा st_i2c_client *c = &i2c_dev->client;

	st_i2c_flush_rx_fअगरo(i2c_dev);

	अगर (!c->count)
		/* End of xfer, send stop or repstart */
		st_i2c_terminate_xfer(i2c_dev);
	अन्यथा
		st_i2c_wr_fill_tx_fअगरo(i2c_dev);
पूर्ण

/**
 * st_i2c_handle_पढ़ो() - Handle FIFO empty पूर्णांकerrupt in हाल of पढ़ो
 * @i2c_dev: Controller's निजी data
 */
अटल व्योम st_i2c_handle_पढ़ो(काष्ठा st_i2c_dev *i2c_dev)
अणु
	काष्ठा st_i2c_client *c = &i2c_dev->client;
	u32 ien;

	/* Trash the address पढ़ो back */
	अगर (!c->xfered) अणु
		पढ़ोl_relaxed(i2c_dev->base + SSC_RBUF);
		st_i2c_clr_bits(i2c_dev->base + SSC_I2C, SSC_I2C_TXENB);
	पूर्ण अन्यथा अणु
		st_i2c_पढ़ो_rx_fअगरo(i2c_dev);
	पूर्ण

	अगर (!c->count) अणु
		/* End of xfer, send stop or repstart */
		st_i2c_terminate_xfer(i2c_dev);
	पूर्ण अन्यथा अगर (c->count == 1) अणु
		/* Penultimate byte to xfer, disable ACK gen. */
		st_i2c_clr_bits(i2c_dev->base + SSC_I2C, SSC_I2C_ACKG);

		/* Last received byte is to be handled by NACK पूर्णांकerrupt */
		ien = SSC_IEN_NACKEN | SSC_IEN_ARBLEN;
		ग_लिखोl_relaxed(ien, i2c_dev->base + SSC_IEN);

		st_i2c_rd_fill_tx_fअगरo(i2c_dev, c->count);
	पूर्ण अन्यथा अणु
		st_i2c_rd_fill_tx_fअगरo(i2c_dev, c->count - 1);
	पूर्ण
पूर्ण

/**
 * st_i2c_isr_thपढ़ो() - Interrupt routine
 * @irq: पूर्णांकerrupt number
 * @data: Controller's निजी data
 */
अटल irqवापस_t st_i2c_isr_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा st_i2c_dev *i2c_dev = data;
	काष्ठा st_i2c_client *c = &i2c_dev->client;
	u32 sta, ien;
	पूर्णांक it;

	ien = पढ़ोl_relaxed(i2c_dev->base + SSC_IEN);
	sta = पढ़ोl_relaxed(i2c_dev->base + SSC_STA);

	/* Use __fls() to check error bits first */
	it = __fls(sta & ien);
	अगर (it < 0) अणु
		dev_dbg(i2c_dev->dev, "spurious it (sta=0x%04x, ien=0x%04x)\n",
				sta, ien);
		वापस IRQ_NONE;
	पूर्ण

	चयन (1 << it) अणु
	हाल SSC_STA_TE:
		अगर (c->addr & I2C_M_RD)
			st_i2c_handle_पढ़ो(i2c_dev);
		अन्यथा
			st_i2c_handle_ग_लिखो(i2c_dev);
		अवरोध;

	हाल SSC_STA_STOP:
	हाल SSC_STA_REPSTRT:
		ग_लिखोl_relaxed(0, i2c_dev->base + SSC_IEN);
		complete(&i2c_dev->complete);
		अवरोध;

	हाल SSC_STA_NACK:
		ग_लिखोl_relaxed(SSC_CLR_NACK, i2c_dev->base + SSC_CLR);

		/* Last received byte handled by NACK पूर्णांकerrupt */
		अगर ((c->addr & I2C_M_RD) && (c->count == 1) && (c->xfered)) अणु
			st_i2c_handle_पढ़ो(i2c_dev);
			अवरोध;
		पूर्ण

		it = SSC_IEN_STOPEN | SSC_IEN_ARBLEN;
		ग_लिखोl_relaxed(it, i2c_dev->base + SSC_IEN);

		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STOPG);
		c->result = -EIO;
		अवरोध;

	हाल SSC_STA_ARBL:
		ग_लिखोl_relaxed(SSC_CLR_SSCARBL, i2c_dev->base + SSC_CLR);

		it = SSC_IEN_STOPEN | SSC_IEN_ARBLEN;
		ग_लिखोl_relaxed(it, i2c_dev->base + SSC_IEN);

		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STOPG);
		c->result = -EAGAIN;
		अवरोध;

	शेष:
		dev_err(i2c_dev->dev,
				"it %d unhandled (sta=0x%04x)\n", it, sta);
	पूर्ण

	/*
	 * Read IEN रेजिस्टर to ensure पूर्णांकerrupt mask ग_लिखो is effective
	 * beक्रमe re-enabling पूर्णांकerrupt at GIC level, and thus aव्योम spurious
	 * पूर्णांकerrupts.
	 */
	पढ़ोl(i2c_dev->base + SSC_IEN);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * st_i2c_xfer_msg() - Transfer a single I2C message
 * @i2c_dev: Controller's निजी data
 * @msg: I2C message to transfer
 * @is_first: first message of the sequence
 * @is_last: last message of the sequence
 */
अटल पूर्णांक st_i2c_xfer_msg(काष्ठा st_i2c_dev *i2c_dev, काष्ठा i2c_msg *msg,
			    bool is_first, bool is_last)
अणु
	काष्ठा st_i2c_client *c = &i2c_dev->client;
	u32 ctl, i2c, it;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	c->addr		= i2c_8bit_addr_from_msg(msg);
	c->buf		= msg->buf;
	c->count	= msg->len;
	c->xfered	= 0;
	c->result	= 0;
	c->stop		= is_last;

	reinit_completion(&i2c_dev->complete);

	ctl = SSC_CTL_EN | SSC_CTL_MS |	SSC_CTL_EN_RX_FIFO | SSC_CTL_EN_TX_FIFO;
	st_i2c_set_bits(i2c_dev->base + SSC_CTL, ctl);

	i2c = SSC_I2C_TXENB;
	अगर (c->addr & I2C_M_RD)
		i2c |= SSC_I2C_ACKG;
	st_i2c_set_bits(i2c_dev->base + SSC_I2C, i2c);

	/* Write slave address */
	st_i2c_ग_लिखो_tx_fअगरo(i2c_dev, c->addr);

	/* Pre-fill Tx fअगरo with data in हाल of ग_लिखो */
	अगर (!(c->addr & I2C_M_RD))
		st_i2c_wr_fill_tx_fअगरo(i2c_dev);

	it = SSC_IEN_NACKEN | SSC_IEN_TEEN | SSC_IEN_ARBLEN;
	ग_लिखोl_relaxed(it, i2c_dev->base + SSC_IEN);

	अगर (is_first) अणु
		ret = st_i2c_रुको_मुक्त_bus(i2c_dev);
		अगर (ret)
			वापस ret;

		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STRTG);
	पूर्ण

	समयout = रुको_क्रम_completion_समयout(&i2c_dev->complete,
			i2c_dev->adap.समयout);
	ret = c->result;

	अगर (!समयout) अणु
		dev_err(i2c_dev->dev, "Write to slave 0x%x timed out\n",
				c->addr);
		ret = -ETIMEDOUT;
	पूर्ण

	i2c = SSC_I2C_STOPG | SSC_I2C_REPSTRTG;
	st_i2c_clr_bits(i2c_dev->base + SSC_I2C, i2c);

	ग_लिखोl_relaxed(SSC_CLR_SSCSTOP | SSC_CLR_REPSTRT,
			i2c_dev->base + SSC_CLR);

	वापस ret;
पूर्ण

/**
 * st_i2c_xfer() - Transfer a single I2C message
 * @i2c_adap: Adapter poपूर्णांकer to the controller
 * @msgs: Poपूर्णांकer to data to be written.
 * @num: Number of messages to be executed
 */
अटल पूर्णांक st_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा st_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);
	पूर्णांक ret, i;

	i2c_dev->busy = true;

	ret = clk_prepare_enable(i2c_dev->clk);
	अगर (ret) अणु
		dev_err(i2c_dev->dev, "Failed to prepare_enable clock\n");
		वापस ret;
	पूर्ण

	pinctrl_pm_select_शेष_state(i2c_dev->dev);

	st_i2c_hw_config(i2c_dev);

	क्रम (i = 0; (i < num) && !ret; i++)
		ret = st_i2c_xfer_msg(i2c_dev, &msgs[i], i == 0, i == num - 1);

	pinctrl_pm_select_idle_state(i2c_dev->dev);

	clk_disable_unprepare(i2c_dev->clk);

	i2c_dev->busy = false;

	वापस (ret < 0) ? ret : i;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक st_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा st_i2c_dev *i2c_dev = dev_get_drvdata(dev);

	अगर (i2c_dev->busy)
		वापस -EBUSY;

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक st_i2c_resume(काष्ठा device *dev)
अणु
	pinctrl_pm_select_शेष_state(dev);
	/* Go in idle state अगर available */
	pinctrl_pm_select_idle_state(dev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(st_i2c_pm, st_i2c_suspend, st_i2c_resume);
#घोषणा ST_I2C_PM	(&st_i2c_pm)
#अन्यथा
#घोषणा ST_I2C_PM	शून्य
#पूर्ण_अगर

अटल u32 st_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm st_i2c_algo = अणु
	.master_xfer = st_i2c_xfer,
	.functionality = st_i2c_func,
पूर्ण;

अटल काष्ठा i2c_bus_recovery_info st_i2c_recovery_info = अणु
	.recover_bus = st_i2c_recover_bus,
पूर्ण;

अटल पूर्णांक st_i2c_of_get_deglitch(काष्ठा device_node *np,
		काष्ठा st_i2c_dev *i2c_dev)
अणु
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "st,i2c-min-scl-pulse-width-us",
			&i2c_dev->scl_min_width_us);
	अगर ((ret == -ENODATA) || (ret == -EOVERFLOW)) अणु
		dev_err(i2c_dev->dev, "st,i2c-min-scl-pulse-width-us invalid\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "st,i2c-min-sda-pulse-width-us",
			&i2c_dev->sda_min_width_us);
	अगर ((ret == -ENODATA) || (ret == -EOVERFLOW)) अणु
		dev_err(i2c_dev->dev, "st,i2c-min-sda-pulse-width-us invalid\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा st_i2c_dev *i2c_dev;
	काष्ठा resource *res;
	u32 clk_rate;
	काष्ठा i2c_adapter *adap;
	पूर्णांक ret;

	i2c_dev = devm_kzalloc(&pdev->dev, माप(*i2c_dev), GFP_KERNEL);
	अगर (!i2c_dev)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c_dev->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(i2c_dev->base))
		वापस PTR_ERR(i2c_dev->base);

	i2c_dev->irq = irq_of_parse_and_map(np, 0);
	अगर (!i2c_dev->irq) अणु
		dev_err(&pdev->dev, "IRQ missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	i2c_dev->clk = of_clk_get_by_name(np, "ssc");
	अगर (IS_ERR(i2c_dev->clk)) अणु
		dev_err(&pdev->dev, "Unable to request clock\n");
		वापस PTR_ERR(i2c_dev->clk);
	पूर्ण

	i2c_dev->mode = I2C_MODE_STANDARD;
	ret = of_property_पढ़ो_u32(np, "clock-frequency", &clk_rate);
	अगर (!ret && (clk_rate == I2C_MAX_FAST_MODE_FREQ))
		i2c_dev->mode = I2C_MODE_FAST;

	i2c_dev->dev = &pdev->dev;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, i2c_dev->irq,
			शून्य, st_i2c_isr_thपढ़ो,
			IRQF_ONESHOT, pdev->name, i2c_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request irq %i\n", i2c_dev->irq);
		वापस ret;
	पूर्ण

	pinctrl_pm_select_शेष_state(i2c_dev->dev);
	/* In हाल idle state available, select it */
	pinctrl_pm_select_idle_state(i2c_dev->dev);

	ret = st_i2c_of_get_deglitch(np, i2c_dev);
	अगर (ret)
		वापस ret;

	adap = &i2c_dev->adap;
	i2c_set_adapdata(adap, i2c_dev);
	snम_लिखो(adap->name, माप(adap->name), "ST I2C(%pa)", &res->start);
	adap->owner = THIS_MODULE;
	adap->समयout = 2 * HZ;
	adap->retries = 0;
	adap->algo = &st_i2c_algo;
	adap->bus_recovery_info = &st_i2c_recovery_info;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	init_completion(&i2c_dev->complete);

	ret = i2c_add_adapter(adap);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, i2c_dev);

	dev_info(i2c_dev->dev, "%s initialized\n", adap->name);

	वापस 0;
पूर्ण

अटल पूर्णांक st_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा st_i2c_dev *i2c_dev = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c_dev->adap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id st_i2c_match[] = अणु
	अणु .compatible = "st,comms-ssc-i2c", पूर्ण,
	अणु .compatible = "st,comms-ssc4-i2c", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st_i2c_match);

अटल काष्ठा platक्रमm_driver st_i2c_driver = अणु
	.driver = अणु
		.name = "st-i2c",
		.of_match_table = st_i2c_match,
		.pm = ST_I2C_PM,
	पूर्ण,
	.probe = st_i2c_probe,
	.हटाओ = st_i2c_हटाओ,
पूर्ण;

module_platक्रमm_driver(st_i2c_driver);

MODULE_AUTHOR("Maxime Coquelin <maxime.coquelin@st.com>");
MODULE_DESCRIPTION("STMicroelectronics I2C driver");
MODULE_LICENSE("GPL v2");
