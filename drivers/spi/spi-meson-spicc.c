<शैली गुरु>
/*
 * Driver क्रम Amlogic Meson SPI communication controller (SPICC)
 *
 * Copyright (C) BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 *
 * SPDX-License-Identअगरier: GPL-2.0+
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reset.h>

/*
 * The Meson SPICC controller could support DMA based transfers, but is not
 * implemented by the venकरोr code, and जबतक having the रेजिस्टरs करोcumentation
 * it has never worked on the GXL Hardware.
 * The PIO mode is the only mode implemented, and due to badly deचिन्हित HW :
 * - all transfers are cutted in 16 words burst because the FIFO hangs on
 *   TX underflow, and there is no TX "Half-Empty" पूर्णांकerrupt, so we go by
 *   FIFO max size chunk only
 * - CS management is dumb, and goes UP between every burst, so is really a
 *   "Data Valid" संकेत than a Chip Select, GPIO link should be used instead
 *   to have a CS go करोwn over the full transfer
 */

#घोषणा SPICC_MAX_BURST	128

/* Register Map */
#घोषणा SPICC_RXDATA	0x00

#घोषणा SPICC_TXDATA	0x04

#घोषणा SPICC_CONREG	0x08
#घोषणा SPICC_ENABLE		BIT(0)
#घोषणा SPICC_MODE_MASTER	BIT(1)
#घोषणा SPICC_XCH		BIT(2)
#घोषणा SPICC_SMC		BIT(3)
#घोषणा SPICC_POL		BIT(4)
#घोषणा SPICC_PHA		BIT(5)
#घोषणा SPICC_SSCTL		BIT(6)
#घोषणा SPICC_SSPOL		BIT(7)
#घोषणा SPICC_DRCTL_MASK	GENMASK(9, 8)
#घोषणा SPICC_DRCTL_IGNORE	0
#घोषणा SPICC_DRCTL_FALLING	1
#घोषणा SPICC_DRCTL_LOWLEVEL	2
#घोषणा SPICC_CS_MASK		GENMASK(13, 12)
#घोषणा SPICC_DATARATE_MASK	GENMASK(18, 16)
#घोषणा SPICC_DATARATE_DIV4	0
#घोषणा SPICC_DATARATE_DIV8	1
#घोषणा SPICC_DATARATE_DIV16	2
#घोषणा SPICC_DATARATE_DIV32	3
#घोषणा SPICC_BITLENGTH_MASK	GENMASK(24, 19)
#घोषणा SPICC_BURSTLENGTH_MASK	GENMASK(31, 25)

#घोषणा SPICC_INTREG	0x0c
#घोषणा SPICC_TE_EN	BIT(0) /* TX FIFO Empty Interrupt */
#घोषणा SPICC_TH_EN	BIT(1) /* TX FIFO Half-Full Interrupt */
#घोषणा SPICC_TF_EN	BIT(2) /* TX FIFO Full Interrupt */
#घोषणा SPICC_RR_EN	BIT(3) /* RX FIFO Ready Interrupt */
#घोषणा SPICC_RH_EN	BIT(4) /* RX FIFO Half-Full Interrupt */
#घोषणा SPICC_RF_EN	BIT(5) /* RX FIFO Full Interrupt */
#घोषणा SPICC_RO_EN	BIT(6) /* RX FIFO Overflow Interrupt */
#घोषणा SPICC_TC_EN	BIT(7) /* Transfert Complete Interrupt */

#घोषणा SPICC_DMAREG	0x10
#घोषणा SPICC_DMA_ENABLE		BIT(0)
#घोषणा SPICC_TXFIFO_THRESHOLD_MASK	GENMASK(5, 1)
#घोषणा SPICC_RXFIFO_THRESHOLD_MASK	GENMASK(10, 6)
#घोषणा SPICC_READ_BURST_MASK		GENMASK(14, 11)
#घोषणा SPICC_WRITE_BURST_MASK		GENMASK(18, 15)
#घोषणा SPICC_DMA_URGENT		BIT(19)
#घोषणा SPICC_DMA_THREADID_MASK		GENMASK(25, 20)
#घोषणा SPICC_DMA_BURSTNUM_MASK		GENMASK(31, 26)

#घोषणा SPICC_STATREG	0x14
#घोषणा SPICC_TE	BIT(0) /* TX FIFO Empty Interrupt */
#घोषणा SPICC_TH	BIT(1) /* TX FIFO Half-Full Interrupt */
#घोषणा SPICC_TF	BIT(2) /* TX FIFO Full Interrupt */
#घोषणा SPICC_RR	BIT(3) /* RX FIFO Ready Interrupt */
#घोषणा SPICC_RH	BIT(4) /* RX FIFO Half-Full Interrupt */
#घोषणा SPICC_RF	BIT(5) /* RX FIFO Full Interrupt */
#घोषणा SPICC_RO	BIT(6) /* RX FIFO Overflow Interrupt */
#घोषणा SPICC_TC	BIT(7) /* Transfert Complete Interrupt */

#घोषणा SPICC_PERIODREG	0x18
#घोषणा SPICC_PERIOD	GENMASK(14, 0)	/* Wait cycles */

#घोषणा SPICC_TESTREG	0x1c
#घोषणा SPICC_TXCNT_MASK	GENMASK(4, 0)	/* TX FIFO Counter */
#घोषणा SPICC_RXCNT_MASK	GENMASK(9, 5)	/* RX FIFO Counter */
#घोषणा SPICC_SMSTATUS_MASK	GENMASK(12, 10)	/* State Machine Status */
#घोषणा SPICC_LBC_RO		BIT(13)	/* Loop Back Control Read-Only */
#घोषणा SPICC_LBC_W1		BIT(14) /* Loop Back Control Write-Only */
#घोषणा SPICC_SWAP_RO		BIT(14) /* RX FIFO Data Swap Read-Only */
#घोषणा SPICC_SWAP_W1		BIT(15) /* RX FIFO Data Swap Write-Only */
#घोषणा SPICC_DLYCTL_RO_MASK	GENMASK(20, 15) /* Delay Control Read-Only */
#घोषणा SPICC_MO_DELAY_MASK	GENMASK(17, 16) /* Master Output Delay */
#घोषणा SPICC_MO_NO_DELAY	0
#घोषणा SPICC_MO_DELAY_1_CYCLE	1
#घोषणा SPICC_MO_DELAY_2_CYCLE	2
#घोषणा SPICC_MO_DELAY_3_CYCLE	3
#घोषणा SPICC_MI_DELAY_MASK	GENMASK(19, 18) /* Master Input Delay */
#घोषणा SPICC_MI_NO_DELAY	0
#घोषणा SPICC_MI_DELAY_1_CYCLE	1
#घोषणा SPICC_MI_DELAY_2_CYCLE	2
#घोषणा SPICC_MI_DELAY_3_CYCLE	3
#घोषणा SPICC_MI_CAP_DELAY_MASK	GENMASK(21, 20) /* Master Capture Delay */
#घोषणा SPICC_CAP_AHEAD_2_CYCLE	0
#घोषणा SPICC_CAP_AHEAD_1_CYCLE	1
#घोषणा SPICC_CAP_NO_DELAY	2
#घोषणा SPICC_CAP_DELAY_1_CYCLE	3
#घोषणा SPICC_FIFORST_RO_MASK	GENMASK(22, 21) /* FIFO Softreset Read-Only */
#घोषणा SPICC_FIFORST_W1_MASK	GENMASK(23, 22) /* FIFO Softreset Write-Only */

#घोषणा SPICC_DRADDR	0x20	/* Read Address of DMA */

#घोषणा SPICC_DWADDR	0x24	/* Write Address of DMA */

#घोषणा SPICC_ENH_CTL0	0x38	/* Enhanced Feature */
#घोषणा SPICC_ENH_CLK_CS_DELAY_MASK	GENMASK(15, 0)
#घोषणा SPICC_ENH_DATARATE_MASK		GENMASK(23, 16)
#घोषणा SPICC_ENH_DATARATE_EN		BIT(24)
#घोषणा SPICC_ENH_MOSI_OEN		BIT(25)
#घोषणा SPICC_ENH_CLK_OEN		BIT(26)
#घोषणा SPICC_ENH_CS_OEN		BIT(27)
#घोषणा SPICC_ENH_CLK_CS_DELAY_EN	BIT(28)
#घोषणा SPICC_ENH_MAIN_CLK_AO		BIT(29)

#घोषणा ग_लिखोl_bits_relaxed(mask, val, addr) \
	ग_लिखोl_relaxed((पढ़ोl_relaxed(addr) & ~(mask)) | (val), addr)

काष्ठा meson_spicc_data अणु
	अचिन्हित पूर्णांक			max_speed_hz;
	अचिन्हित पूर्णांक			min_speed_hz;
	अचिन्हित पूर्णांक			fअगरo_size;
	bool				has_oen;
	bool				has_enhance_clk_भाग;
	bool				has_pclk;
पूर्ण;

काष्ठा meson_spicc_device अणु
	काष्ठा spi_master		*master;
	काष्ठा platक्रमm_device		*pdev;
	व्योम __iomem			*base;
	काष्ठा clk			*core;
	काष्ठा clk			*pclk;
	काष्ठा clk			*clk;
	काष्ठा spi_message		*message;
	काष्ठा spi_transfer		*xfer;
	स्थिर काष्ठा meson_spicc_data	*data;
	u8				*tx_buf;
	u8				*rx_buf;
	अचिन्हित पूर्णांक			bytes_per_word;
	अचिन्हित दीर्घ			tx_reमुख्य;
	अचिन्हित दीर्घ			rx_reमुख्य;
	अचिन्हित दीर्घ			xfer_reमुख्य;
पूर्ण;

अटल व्योम meson_spicc_oen_enable(काष्ठा meson_spicc_device *spicc)
अणु
	u32 conf;

	अगर (!spicc->data->has_oen)
		वापस;

	conf = पढ़ोl_relaxed(spicc->base + SPICC_ENH_CTL0) |
		SPICC_ENH_MOSI_OEN | SPICC_ENH_CLK_OEN | SPICC_ENH_CS_OEN;

	ग_लिखोl_relaxed(conf, spicc->base + SPICC_ENH_CTL0);
पूर्ण

अटल अंतरभूत bool meson_spicc_txfull(काष्ठा meson_spicc_device *spicc)
अणु
	वापस !!FIELD_GET(SPICC_TF,
			   पढ़ोl_relaxed(spicc->base + SPICC_STATREG));
पूर्ण

अटल अंतरभूत bool meson_spicc_rxपढ़ोy(काष्ठा meson_spicc_device *spicc)
अणु
	वापस FIELD_GET(SPICC_RH | SPICC_RR | SPICC_RF,
			 पढ़ोl_relaxed(spicc->base + SPICC_STATREG));
पूर्ण

अटल अंतरभूत u32 meson_spicc_pull_data(काष्ठा meson_spicc_device *spicc)
अणु
	अचिन्हित पूर्णांक bytes = spicc->bytes_per_word;
	अचिन्हित पूर्णांक byte_shअगरt = 0;
	u32 data = 0;
	u8 byte;

	जबतक (bytes--) अणु
		byte = *spicc->tx_buf++;
		data |= (byte & 0xff) << byte_shअगरt;
		byte_shअगरt += 8;
	पूर्ण

	spicc->tx_reमुख्य--;
	वापस data;
पूर्ण

अटल अंतरभूत व्योम meson_spicc_push_data(काष्ठा meson_spicc_device *spicc,
					 u32 data)
अणु
	अचिन्हित पूर्णांक bytes = spicc->bytes_per_word;
	अचिन्हित पूर्णांक byte_shअगरt = 0;
	u8 byte;

	जबतक (bytes--) अणु
		byte = (data >> byte_shअगरt) & 0xff;
		*spicc->rx_buf++ = byte;
		byte_shअगरt += 8;
	पूर्ण

	spicc->rx_reमुख्य--;
पूर्ण

अटल अंतरभूत व्योम meson_spicc_rx(काष्ठा meson_spicc_device *spicc)
अणु
	/* Empty RX FIFO */
	जबतक (spicc->rx_reमुख्य &&
	       meson_spicc_rxपढ़ोy(spicc))
		meson_spicc_push_data(spicc,
				पढ़ोl_relaxed(spicc->base + SPICC_RXDATA));
पूर्ण

अटल अंतरभूत व्योम meson_spicc_tx(काष्ठा meson_spicc_device *spicc)
अणु
	/* Fill Up TX FIFO */
	जबतक (spicc->tx_reमुख्य &&
	       !meson_spicc_txfull(spicc))
		ग_लिखोl_relaxed(meson_spicc_pull_data(spicc),
			       spicc->base + SPICC_TXDATA);
पूर्ण

अटल अंतरभूत व्योम meson_spicc_setup_burst(काष्ठा meson_spicc_device *spicc)
अणु

	अचिन्हित पूर्णांक burst_len = min_t(अचिन्हित पूर्णांक,
				       spicc->xfer_reमुख्य /
				       spicc->bytes_per_word,
				       spicc->data->fअगरo_size);
	/* Setup Xfer variables */
	spicc->tx_reमुख्य = burst_len;
	spicc->rx_reमुख्य = burst_len;
	spicc->xfer_reमुख्य -= burst_len * spicc->bytes_per_word;

	/* Setup burst length */
	ग_लिखोl_bits_relaxed(SPICC_BURSTLENGTH_MASK,
			FIELD_PREP(SPICC_BURSTLENGTH_MASK,
				burst_len - 1),
			spicc->base + SPICC_CONREG);

	/* Fill TX FIFO */
	meson_spicc_tx(spicc);
पूर्ण

अटल irqवापस_t meson_spicc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा meson_spicc_device *spicc = (व्योम *) data;

	ग_लिखोl_bits_relaxed(SPICC_TC, SPICC_TC, spicc->base + SPICC_STATREG);

	/* Empty RX FIFO */
	meson_spicc_rx(spicc);

	अगर (!spicc->xfer_reमुख्य) अणु
		/* Disable all IRQs */
		ग_लिखोl(0, spicc->base + SPICC_INTREG);

		spi_finalize_current_transfer(spicc->master);

		वापस IRQ_HANDLED;
	पूर्ण

	/* Setup burst */
	meson_spicc_setup_burst(spicc);

	/* Start burst */
	ग_लिखोl_bits_relaxed(SPICC_XCH, SPICC_XCH, spicc->base + SPICC_CONREG);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम meson_spicc_स्वतः_io_delay(काष्ठा meson_spicc_device *spicc)
अणु
	u32 भाग, hz;
	u32 mi_delay, cap_delay;
	u32 conf;

	अगर (spicc->data->has_enhance_clk_भाग) अणु
		भाग = FIELD_GET(SPICC_ENH_DATARATE_MASK,
				पढ़ोl_relaxed(spicc->base + SPICC_ENH_CTL0));
		भाग++;
		भाग <<= 1;
	पूर्ण अन्यथा अणु
		भाग = FIELD_GET(SPICC_DATARATE_MASK,
				पढ़ोl_relaxed(spicc->base + SPICC_CONREG));
		भाग += 2;
		भाग = 1 << भाग;
	पूर्ण

	mi_delay = SPICC_MI_NO_DELAY;
	cap_delay = SPICC_CAP_AHEAD_2_CYCLE;
	hz = clk_get_rate(spicc->clk);

	अगर (hz >= 100000000)
		cap_delay = SPICC_CAP_DELAY_1_CYCLE;
	अन्यथा अगर (hz >= 80000000)
		cap_delay = SPICC_CAP_NO_DELAY;
	अन्यथा अगर (hz >= 40000000)
		cap_delay = SPICC_CAP_AHEAD_1_CYCLE;
	अन्यथा अगर (भाग >= 16)
		mi_delay = SPICC_MI_DELAY_3_CYCLE;
	अन्यथा अगर (भाग >= 8)
		mi_delay = SPICC_MI_DELAY_2_CYCLE;
	अन्यथा अगर (भाग >= 6)
		mi_delay = SPICC_MI_DELAY_1_CYCLE;

	conf = पढ़ोl_relaxed(spicc->base + SPICC_TESTREG);
	conf &= ~(SPICC_MO_DELAY_MASK | SPICC_MI_DELAY_MASK
		  | SPICC_MI_CAP_DELAY_MASK);
	conf |= FIELD_PREP(SPICC_MI_DELAY_MASK, mi_delay);
	conf |= FIELD_PREP(SPICC_MI_CAP_DELAY_MASK, cap_delay);
	ग_लिखोl_relaxed(conf, spicc->base + SPICC_TESTREG);
पूर्ण

अटल व्योम meson_spicc_setup_xfer(काष्ठा meson_spicc_device *spicc,
				   काष्ठा spi_transfer *xfer)
अणु
	u32 conf, conf_orig;

	/* Read original configuration */
	conf = conf_orig = पढ़ोl_relaxed(spicc->base + SPICC_CONREG);

	/* Setup word width */
	conf &= ~SPICC_BITLENGTH_MASK;
	conf |= FIELD_PREP(SPICC_BITLENGTH_MASK,
			   (spicc->bytes_per_word << 3) - 1);

	/* Ignore अगर unchanged */
	अगर (conf != conf_orig)
		ग_लिखोl_relaxed(conf, spicc->base + SPICC_CONREG);

	clk_set_rate(spicc->clk, xfer->speed_hz);

	meson_spicc_स्वतः_io_delay(spicc);

	ग_लिखोl_relaxed(0, spicc->base + SPICC_DMAREG);
पूर्ण

अटल व्योम meson_spicc_reset_fअगरo(काष्ठा meson_spicc_device *spicc)
अणु
	अगर (spicc->data->has_oen)
		ग_लिखोl_bits_relaxed(SPICC_ENH_MAIN_CLK_AO,
				    SPICC_ENH_MAIN_CLK_AO,
				    spicc->base + SPICC_ENH_CTL0);

	ग_लिखोl_bits_relaxed(SPICC_FIFORST_W1_MASK, SPICC_FIFORST_W1_MASK,
			    spicc->base + SPICC_TESTREG);

	जबतक (meson_spicc_rxपढ़ोy(spicc))
		पढ़ोl_relaxed(spicc->base + SPICC_RXDATA);

	अगर (spicc->data->has_oen)
		ग_लिखोl_bits_relaxed(SPICC_ENH_MAIN_CLK_AO, 0,
				    spicc->base + SPICC_ENH_CTL0);
पूर्ण

अटल पूर्णांक meson_spicc_transfer_one(काष्ठा spi_master *master,
				    काष्ठा spi_device *spi,
				    काष्ठा spi_transfer *xfer)
अणु
	काष्ठा meson_spicc_device *spicc = spi_master_get_devdata(master);

	/* Store current transfer */
	spicc->xfer = xfer;

	/* Setup transfer parameters */
	spicc->tx_buf = (u8 *)xfer->tx_buf;
	spicc->rx_buf = (u8 *)xfer->rx_buf;
	spicc->xfer_reमुख्य = xfer->len;

	/* Pre-calculate word size */
	spicc->bytes_per_word =
	   DIV_ROUND_UP(spicc->xfer->bits_per_word, 8);

	अगर (xfer->len % spicc->bytes_per_word)
		वापस -EINVAL;

	/* Setup transfer parameters */
	meson_spicc_setup_xfer(spicc, xfer);

	meson_spicc_reset_fअगरo(spicc);

	/* Setup burst */
	meson_spicc_setup_burst(spicc);

	/* Start burst */
	ग_लिखोl_bits_relaxed(SPICC_XCH, SPICC_XCH, spicc->base + SPICC_CONREG);

	/* Enable पूर्णांकerrupts */
	ग_लिखोl_relaxed(SPICC_TC_EN, spicc->base + SPICC_INTREG);

	वापस 1;
पूर्ण

अटल पूर्णांक meson_spicc_prepare_message(काष्ठा spi_master *master,
				       काष्ठा spi_message *message)
अणु
	काष्ठा meson_spicc_device *spicc = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = message->spi;
	u32 conf = 0;

	/* Store current message */
	spicc->message = message;

	/* Enable Master */
	conf |= SPICC_ENABLE;
	conf |= SPICC_MODE_MASTER;

	/* SMC = 0 */

	/* Setup transfer mode */
	अगर (spi->mode & SPI_CPOL)
		conf |= SPICC_POL;
	अन्यथा
		conf &= ~SPICC_POL;

	अगर (spi->mode & SPI_CPHA)
		conf |= SPICC_PHA;
	अन्यथा
		conf &= ~SPICC_PHA;

	/* SSCTL = 0 */

	अगर (spi->mode & SPI_CS_HIGH)
		conf |= SPICC_SSPOL;
	अन्यथा
		conf &= ~SPICC_SSPOL;

	अगर (spi->mode & SPI_READY)
		conf |= FIELD_PREP(SPICC_DRCTL_MASK, SPICC_DRCTL_LOWLEVEL);
	अन्यथा
		conf |= FIELD_PREP(SPICC_DRCTL_MASK, SPICC_DRCTL_IGNORE);

	/* Select CS */
	conf |= FIELD_PREP(SPICC_CS_MASK, spi->chip_select);

	/* Default Clock rate core/4 */

	/* Default 8bit word */
	conf |= FIELD_PREP(SPICC_BITLENGTH_MASK, 8 - 1);

	ग_लिखोl_relaxed(conf, spicc->base + SPICC_CONREG);

	/* Setup no रुको cycles by शेष */
	ग_लिखोl_relaxed(0, spicc->base + SPICC_PERIODREG);

	ग_लिखोl_bits_relaxed(SPICC_LBC_W1, 0, spicc->base + SPICC_TESTREG);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_spicc_unprepare_transfer(काष्ठा spi_master *master)
अणु
	काष्ठा meson_spicc_device *spicc = spi_master_get_devdata(master);

	/* Disable all IRQs */
	ग_लिखोl(0, spicc->base + SPICC_INTREG);

	device_reset_optional(&spicc->pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_spicc_setup(काष्ठा spi_device *spi)
अणु
	अगर (!spi->controller_state)
		spi->controller_state = spi_master_get_devdata(spi->master);

	वापस 0;
पूर्ण

अटल व्योम meson_spicc_cleanup(काष्ठा spi_device *spi)
अणु
	spi->controller_state = शून्य;
पूर्ण

/*
 * The Clock Mux
 *            x-----------------x   x------------x    x------\
 *        |---| घात2 fixed भाग  |---| घात2 भाग   |----|      |
 *        |   x-----------------x   x------------x    |      |
 * src ---|                                           | mux  |-- out
 *        |   x-----------------x   x------------x    |      |
 *        |---| enh fixed भाग   |---| enh भाग    |0---|      |
 *            x-----------------x   x------------x    x------/
 *
 * Clk path क्रम GX series:
 *    src -> घात2 fixed भाग -> घात2 भाग -> out
 *
 * Clk path क्रम AXG series:
 *    src -> घात2 fixed भाग -> घात2 भाग -> mux -> out
 *    src -> enh fixed भाग -> enh भाग -> mux -> out
 *
 * Clk path क्रम G12A series:
 *    pclk -> घात2 fixed भाग -> घात2 भाग -> mux -> out
 *    pclk -> enh fixed भाग -> enh भाग -> mux -> out
 */

अटल पूर्णांक meson_spicc_clk_init(काष्ठा meson_spicc_device *spicc)
अणु
	काष्ठा device *dev = &spicc->pdev->dev;
	काष्ठा clk_fixed_factor *घात2_fixed_भाग, *enh_fixed_भाग;
	काष्ठा clk_भागider *घात2_भाग, *enh_भाग;
	काष्ठा clk_mux *mux;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;
	काष्ठा clk_parent_data parent_data[2];
	अक्षर name[64];

	स_रखो(&init, 0, माप(init));
	स_रखो(&parent_data, 0, माप(parent_data));

	init.parent_data = parent_data;

	/* algorithm क्रम घात2 भाग: rate = freq / 4 / (2 ^ N) */

	घात2_fixed_भाग = devm_kzalloc(dev, माप(*घात2_fixed_भाग), GFP_KERNEL);
	अगर (!घात2_fixed_भाग)
		वापस -ENOMEM;

	snम_लिखो(name, माप(name), "%s#pow2_fixed_div", dev_name(dev));
	init.name = name;
	init.ops = &clk_fixed_factor_ops;
	init.flags = 0;
	अगर (spicc->data->has_pclk)
		parent_data[0].hw = __clk_get_hw(spicc->pclk);
	अन्यथा
		parent_data[0].hw = __clk_get_hw(spicc->core);
	init.num_parents = 1;

	घात2_fixed_भाग->mult = 1,
	घात2_fixed_भाग->भाग = 4,
	घात2_fixed_भाग->hw.init = &init;

	clk = devm_clk_रेजिस्टर(dev, &घात2_fixed_भाग->hw);
	अगर (WARN_ON(IS_ERR(clk)))
		वापस PTR_ERR(clk);

	घात2_भाग = devm_kzalloc(dev, माप(*घात2_भाग), GFP_KERNEL);
	अगर (!घात2_भाग)
		वापस -ENOMEM;

	snम_लिखो(name, माप(name), "%s#pow2_div", dev_name(dev));
	init.name = name;
	init.ops = &clk_भागider_ops;
	init.flags = CLK_SET_RATE_PARENT;
	parent_data[0].hw = &घात2_fixed_भाग->hw;
	init.num_parents = 1;

	घात2_भाग->shअगरt = 16,
	घात2_भाग->width = 3,
	घात2_भाग->flags = CLK_DIVIDER_POWER_OF_TWO,
	घात2_भाग->reg = spicc->base + SPICC_CONREG;
	घात2_भाग->hw.init = &init;

	clk = devm_clk_रेजिस्टर(dev, &घात2_भाग->hw);
	अगर (WARN_ON(IS_ERR(clk)))
		वापस PTR_ERR(clk);

	अगर (!spicc->data->has_enhance_clk_भाग) अणु
		spicc->clk = clk;
		वापस 0;
	पूर्ण

	/* algorithm क्रम enh भाग: rate = freq / 2 / (N + 1) */

	enh_fixed_भाग = devm_kzalloc(dev, माप(*enh_fixed_भाग), GFP_KERNEL);
	अगर (!enh_fixed_भाग)
		वापस -ENOMEM;

	snम_लिखो(name, माप(name), "%s#enh_fixed_div", dev_name(dev));
	init.name = name;
	init.ops = &clk_fixed_factor_ops;
	init.flags = 0;
	अगर (spicc->data->has_pclk)
		parent_data[0].hw = __clk_get_hw(spicc->pclk);
	अन्यथा
		parent_data[0].hw = __clk_get_hw(spicc->core);
	init.num_parents = 1;

	enh_fixed_भाग->mult = 1,
	enh_fixed_भाग->भाग = 2,
	enh_fixed_भाग->hw.init = &init;

	clk = devm_clk_रेजिस्टर(dev, &enh_fixed_भाग->hw);
	अगर (WARN_ON(IS_ERR(clk)))
		वापस PTR_ERR(clk);

	enh_भाग = devm_kzalloc(dev, माप(*enh_भाग), GFP_KERNEL);
	अगर (!enh_भाग)
		वापस -ENOMEM;

	snम_लिखो(name, माप(name), "%s#enh_div", dev_name(dev));
	init.name = name;
	init.ops = &clk_भागider_ops;
	init.flags = CLK_SET_RATE_PARENT;
	parent_data[0].hw = &enh_fixed_भाग->hw;
	init.num_parents = 1;

	enh_भाग->shअगरt	= 16,
	enh_भाग->width	= 8,
	enh_भाग->reg = spicc->base + SPICC_ENH_CTL0;
	enh_भाग->hw.init = &init;

	clk = devm_clk_रेजिस्टर(dev, &enh_भाग->hw);
	अगर (WARN_ON(IS_ERR(clk)))
		वापस PTR_ERR(clk);

	mux = devm_kzalloc(dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस -ENOMEM;

	snम_लिखो(name, माप(name), "%s#sel", dev_name(dev));
	init.name = name;
	init.ops = &clk_mux_ops;
	parent_data[0].hw = &घात2_भाग->hw;
	parent_data[1].hw = &enh_भाग->hw;
	init.num_parents = 2;
	init.flags = CLK_SET_RATE_PARENT;

	mux->mask = 0x1,
	mux->shअगरt = 24,
	mux->reg = spicc->base + SPICC_ENH_CTL0;
	mux->hw.init = &init;

	spicc->clk = devm_clk_रेजिस्टर(dev, &mux->hw);
	अगर (WARN_ON(IS_ERR(spicc->clk)))
		वापस PTR_ERR(spicc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_spicc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा meson_spicc_device *spicc;
	पूर्णांक ret, irq;

	master = spi_alloc_master(&pdev->dev, माप(*spicc));
	अगर (!master) अणु
		dev_err(&pdev->dev, "master allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	spicc = spi_master_get_devdata(master);
	spicc->master = master;

	spicc->data = of_device_get_match_data(&pdev->dev);
	अगर (!spicc->data) अणु
		dev_err(&pdev->dev, "failed to get match data\n");
		ret = -EINVAL;
		जाओ out_master;
	पूर्ण

	spicc->pdev = pdev;
	platक्रमm_set_drvdata(pdev, spicc);

	spicc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(spicc->base)) अणु
		dev_err(&pdev->dev, "io resource mapping failed\n");
		ret = PTR_ERR(spicc->base);
		जाओ out_master;
	पूर्ण

	/* Set master mode and enable controller */
	ग_लिखोl_relaxed(SPICC_ENABLE | SPICC_MODE_MASTER,
		       spicc->base + SPICC_CONREG);

	/* Disable all IRQs */
	ग_लिखोl_relaxed(0, spicc->base + SPICC_INTREG);

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, irq, meson_spicc_irq,
			       0, शून्य, spicc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "irq request failed\n");
		जाओ out_master;
	पूर्ण

	spicc->core = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(spicc->core)) अणु
		dev_err(&pdev->dev, "core clock request failed\n");
		ret = PTR_ERR(spicc->core);
		जाओ out_master;
	पूर्ण

	अगर (spicc->data->has_pclk) अणु
		spicc->pclk = devm_clk_get(&pdev->dev, "pclk");
		अगर (IS_ERR(spicc->pclk)) अणु
			dev_err(&pdev->dev, "pclk clock request failed\n");
			ret = PTR_ERR(spicc->pclk);
			जाओ out_master;
		पूर्ण
	पूर्ण

	ret = clk_prepare_enable(spicc->core);
	अगर (ret) अणु
		dev_err(&pdev->dev, "core clock enable failed\n");
		जाओ out_master;
	पूर्ण

	ret = clk_prepare_enable(spicc->pclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "pclk clock enable failed\n");
		जाओ out_master;
	पूर्ण

	device_reset_optional(&pdev->dev);

	master->num_chipselect = 4;
	master->dev.of_node = pdev->dev.of_node;
	master->mode_bits = SPI_CPHA | SPI_CPOL | SPI_CS_HIGH;
	master->bits_per_word_mask = SPI_BPW_MASK(32) |
				     SPI_BPW_MASK(24) |
				     SPI_BPW_MASK(16) |
				     SPI_BPW_MASK(8);
	master->flags = (SPI_MASTER_MUST_RX | SPI_MASTER_MUST_TX);
	master->min_speed_hz = spicc->data->min_speed_hz;
	master->max_speed_hz = spicc->data->max_speed_hz;
	master->setup = meson_spicc_setup;
	master->cleanup = meson_spicc_cleanup;
	master->prepare_message = meson_spicc_prepare_message;
	master->unprepare_transfer_hardware = meson_spicc_unprepare_transfer;
	master->transfer_one = meson_spicc_transfer_one;
	master->use_gpio_descriptors = true;

	meson_spicc_oen_enable(spicc);

	ret = meson_spicc_clk_init(spicc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "clock registration failed\n");
		जाओ out_master;
	पूर्ण

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "spi master registration failed\n");
		जाओ out_clk;
	पूर्ण

	वापस 0;

out_clk:
	clk_disable_unprepare(spicc->core);
	clk_disable_unprepare(spicc->pclk);

out_master:
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_spicc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_spicc_device *spicc = platक्रमm_get_drvdata(pdev);

	/* Disable SPI */
	ग_लिखोl(0, spicc->base + SPICC_CONREG);

	clk_disable_unprepare(spicc->core);
	clk_disable_unprepare(spicc->pclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा meson_spicc_data meson_spicc_gx_data = अणु
	.max_speed_hz		= 30000000,
	.min_speed_hz		= 325000,
	.fअगरo_size		= 16,
पूर्ण;

अटल स्थिर काष्ठा meson_spicc_data meson_spicc_axg_data = अणु
	.max_speed_hz		= 80000000,
	.min_speed_hz		= 325000,
	.fअगरo_size		= 16,
	.has_oen		= true,
	.has_enhance_clk_भाग	= true,
पूर्ण;

अटल स्थिर काष्ठा meson_spicc_data meson_spicc_g12a_data = अणु
	.max_speed_hz		= 166666666,
	.min_speed_hz		= 50000,
	.fअगरo_size		= 15,
	.has_oen		= true,
	.has_enhance_clk_भाग	= true,
	.has_pclk		= true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_spicc_of_match[] = अणु
	अणु
		.compatible	= "amlogic,meson-gx-spicc",
		.data		= &meson_spicc_gx_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-axg-spicc",
		.data		= &meson_spicc_axg_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-g12a-spicc",
		.data		= &meson_spicc_g12a_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_spicc_of_match);

अटल काष्ठा platक्रमm_driver meson_spicc_driver = अणु
	.probe   = meson_spicc_probe,
	.हटाओ  = meson_spicc_हटाओ,
	.driver  = अणु
		.name = "meson-spicc",
		.of_match_table = of_match_ptr(meson_spicc_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_spicc_driver);

MODULE_DESCRIPTION("Meson SPI Communication Controller driver");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_LICENSE("GPL");
