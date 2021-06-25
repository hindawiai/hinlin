<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Freescale i.MX7ULP LPSPI driver
//
// Copyright 2016 Freescale Semiconductor, Inc.
// Copyright 2018 NXP Semiconductors

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/dma-imx.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/types.h>

#घोषणा DRIVER_NAME "fsl_lpspi"

#घोषणा FSL_LPSPI_RPM_TIMEOUT 50 /* 50ms */

/* The maximum bytes that edma can transfer once.*/
#घोषणा FSL_LPSPI_MAX_EDMA_BYTES  ((1 << 15) - 1)

/* i.MX7ULP LPSPI रेजिस्टरs */
#घोषणा IMX7ULP_VERID	0x0
#घोषणा IMX7ULP_PARAM	0x4
#घोषणा IMX7ULP_CR	0x10
#घोषणा IMX7ULP_SR	0x14
#घोषणा IMX7ULP_IER	0x18
#घोषणा IMX7ULP_DER	0x1c
#घोषणा IMX7ULP_CFGR0	0x20
#घोषणा IMX7ULP_CFGR1	0x24
#घोषणा IMX7ULP_DMR0	0x30
#घोषणा IMX7ULP_DMR1	0x34
#घोषणा IMX7ULP_CCR	0x40
#घोषणा IMX7ULP_FCR	0x58
#घोषणा IMX7ULP_FSR	0x5c
#घोषणा IMX7ULP_TCR	0x60
#घोषणा IMX7ULP_TDR	0x64
#घोषणा IMX7ULP_RSR	0x70
#घोषणा IMX7ULP_RDR	0x74

/* General control रेजिस्टर field define */
#घोषणा CR_RRF		BIT(9)
#घोषणा CR_RTF		BIT(8)
#घोषणा CR_RST		BIT(1)
#घोषणा CR_MEN		BIT(0)
#घोषणा SR_MBF		BIT(24)
#घोषणा SR_TCF		BIT(10)
#घोषणा SR_FCF		BIT(9)
#घोषणा SR_RDF		BIT(1)
#घोषणा SR_TDF		BIT(0)
#घोषणा IER_TCIE	BIT(10)
#घोषणा IER_FCIE	BIT(9)
#घोषणा IER_RDIE	BIT(1)
#घोषणा IER_TDIE	BIT(0)
#घोषणा DER_RDDE	BIT(1)
#घोषणा DER_TDDE	BIT(0)
#घोषणा CFGR1_PCSCFG	BIT(27)
#घोषणा CFGR1_PINCFG	(BIT(24)|BIT(25))
#घोषणा CFGR1_PCSPOL	BIT(8)
#घोषणा CFGR1_NOSTALL	BIT(3)
#घोषणा CFGR1_MASTER	BIT(0)
#घोषणा FSR_TXCOUNT	(0xFF)
#घोषणा RSR_RXEMPTY	BIT(1)
#घोषणा TCR_CPOL	BIT(31)
#घोषणा TCR_CPHA	BIT(30)
#घोषणा TCR_CONT	BIT(21)
#घोषणा TCR_CONTC	BIT(20)
#घोषणा TCR_RXMSK	BIT(19)
#घोषणा TCR_TXMSK	BIT(18)

काष्ठा lpspi_config अणु
	u8 bpw;
	u8 chip_select;
	u8 prescale;
	u16 mode;
	u32 speed_hz;
पूर्ण;

काष्ठा fsl_lpspi_data अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	अचिन्हित दीर्घ base_phys;
	काष्ठा clk *clk_ipg;
	काष्ठा clk *clk_per;
	bool is_slave;
	bool is_only_cs1;
	bool is_first_byte;

	व्योम *rx_buf;
	स्थिर व्योम *tx_buf;
	व्योम (*tx)(काष्ठा fsl_lpspi_data *);
	व्योम (*rx)(काष्ठा fsl_lpspi_data *);

	u32 reमुख्य;
	u8 watermark;
	u8 txfअगरosize;
	u8 rxfअगरosize;

	काष्ठा lpspi_config config;
	काष्ठा completion xfer_करोne;

	bool slave_पातed;

	/* DMA */
	bool usedma;
	काष्ठा completion dma_rx_completion;
	काष्ठा completion dma_tx_completion;
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_lpspi_dt_ids[] = अणु
	अणु .compatible = "fsl,imx7ulp-spi", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_lpspi_dt_ids);

#घोषणा LPSPI_BUF_RX(type)						\
अटल व्योम fsl_lpspi_buf_rx_##type(काष्ठा fsl_lpspi_data *fsl_lpspi)	\
अणु									\
	अचिन्हित पूर्णांक val = पढ़ोl(fsl_lpspi->base + IMX7ULP_RDR);	\
									\
	अगर (fsl_lpspi->rx_buf) अणु					\
		*(type *)fsl_lpspi->rx_buf = val;			\
		fsl_lpspi->rx_buf += माप(type);                      \
	पूर्ण								\
पूर्ण

#घोषणा LPSPI_BUF_TX(type)						\
अटल व्योम fsl_lpspi_buf_tx_##type(काष्ठा fsl_lpspi_data *fsl_lpspi)	\
अणु									\
	type val = 0;							\
									\
	अगर (fsl_lpspi->tx_buf) अणु					\
		val = *(type *)fsl_lpspi->tx_buf;			\
		fsl_lpspi->tx_buf += माप(type);			\
	पूर्ण								\
									\
	fsl_lpspi->reमुख्य -= माप(type);				\
	ग_लिखोl(val, fsl_lpspi->base + IMX7ULP_TDR);			\
पूर्ण

LPSPI_BUF_RX(u8)
LPSPI_BUF_TX(u8)
LPSPI_BUF_RX(u16)
LPSPI_BUF_TX(u16)
LPSPI_BUF_RX(u32)
LPSPI_BUF_TX(u32)

अटल व्योम fsl_lpspi_पूर्णांकctrl(काष्ठा fsl_lpspi_data *fsl_lpspi,
			      अचिन्हित पूर्णांक enable)
अणु
	ग_लिखोl(enable, fsl_lpspi->base + IMX7ULP_IER);
पूर्ण

अटल पूर्णांक fsl_lpspi_bytes_per_word(स्थिर पूर्णांक bpw)
अणु
	वापस DIV_ROUND_UP(bpw, BITS_PER_BYTE);
पूर्ण

अटल bool fsl_lpspi_can_dma(काष्ठा spi_controller *controller,
			      काष्ठा spi_device *spi,
			      काष्ठा spi_transfer *transfer)
अणु
	अचिन्हित पूर्णांक bytes_per_word;

	अगर (!controller->dma_rx)
		वापस false;

	bytes_per_word = fsl_lpspi_bytes_per_word(transfer->bits_per_word);

	चयन (bytes_per_word) अणु
	हाल 1:
	हाल 2:
	हाल 4:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक lpspi_prepare_xfer_hardware(काष्ठा spi_controller *controller)
अणु
	काष्ठा fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(controller);
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(fsl_lpspi->dev);
	अगर (ret < 0) अणु
		dev_err(fsl_lpspi->dev, "failed to enable clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpspi_unprepare_xfer_hardware(काष्ठा spi_controller *controller)
अणु
	काष्ठा fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(controller);

	pm_runसमय_mark_last_busy(fsl_lpspi->dev);
	pm_runसमय_put_स्वतःsuspend(fsl_lpspi->dev);

	वापस 0;
पूर्ण

अटल व्योम fsl_lpspi_ग_लिखो_tx_fअगरo(काष्ठा fsl_lpspi_data *fsl_lpspi)
अणु
	u8 txfअगरo_cnt;
	u32 temp;

	txfअगरo_cnt = पढ़ोl(fsl_lpspi->base + IMX7ULP_FSR) & 0xff;

	जबतक (txfअगरo_cnt < fsl_lpspi->txfअगरosize) अणु
		अगर (!fsl_lpspi->reमुख्य)
			अवरोध;
		fsl_lpspi->tx(fsl_lpspi);
		txfअगरo_cnt++;
	पूर्ण

	अगर (txfअगरo_cnt < fsl_lpspi->txfअगरosize) अणु
		अगर (!fsl_lpspi->is_slave) अणु
			temp = पढ़ोl(fsl_lpspi->base + IMX7ULP_TCR);
			temp &= ~TCR_CONTC;
			ग_लिखोl(temp, fsl_lpspi->base + IMX7ULP_TCR);
		पूर्ण

		fsl_lpspi_पूर्णांकctrl(fsl_lpspi, IER_FCIE);
	पूर्ण अन्यथा
		fsl_lpspi_पूर्णांकctrl(fsl_lpspi, IER_TDIE);
पूर्ण

अटल व्योम fsl_lpspi_पढ़ो_rx_fअगरo(काष्ठा fsl_lpspi_data *fsl_lpspi)
अणु
	जबतक (!(पढ़ोl(fsl_lpspi->base + IMX7ULP_RSR) & RSR_RXEMPTY))
		fsl_lpspi->rx(fsl_lpspi);
पूर्ण

अटल व्योम fsl_lpspi_set_cmd(काष्ठा fsl_lpspi_data *fsl_lpspi)
अणु
	u32 temp = 0;

	temp |= fsl_lpspi->config.bpw - 1;
	temp |= (fsl_lpspi->config.mode & 0x3) << 30;
	temp |= (fsl_lpspi->config.chip_select & 0x3) << 24;
	अगर (!fsl_lpspi->is_slave) अणु
		temp |= fsl_lpspi->config.prescale << 27;
		/*
		 * Set TCR_CONT will keep SS निश्चितed after current transfer.
		 * For the first transfer, clear TCR_CONTC to निश्चित SS.
		 * For subsequent transfer, set TCR_CONTC to keep SS निश्चितed.
		 */
		अगर (!fsl_lpspi->usedma) अणु
			temp |= TCR_CONT;
			अगर (fsl_lpspi->is_first_byte)
				temp &= ~TCR_CONTC;
			अन्यथा
				temp |= TCR_CONTC;
		पूर्ण
	पूर्ण
	ग_लिखोl(temp, fsl_lpspi->base + IMX7ULP_TCR);

	dev_dbg(fsl_lpspi->dev, "TCR=0x%x\n", temp);
पूर्ण

अटल व्योम fsl_lpspi_set_watermark(काष्ठा fsl_lpspi_data *fsl_lpspi)
अणु
	u32 temp;

	अगर (!fsl_lpspi->usedma)
		temp = fsl_lpspi->watermark >> 1 |
		       (fsl_lpspi->watermark >> 1) << 16;
	अन्यथा
		temp = fsl_lpspi->watermark >> 1;

	ग_लिखोl(temp, fsl_lpspi->base + IMX7ULP_FCR);

	dev_dbg(fsl_lpspi->dev, "FCR=0x%x\n", temp);
पूर्ण

अटल पूर्णांक fsl_lpspi_set_bitrate(काष्ठा fsl_lpspi_data *fsl_lpspi)
अणु
	काष्ठा lpspi_config config = fsl_lpspi->config;
	अचिन्हित पूर्णांक perclk_rate, scद_भाग;
	u8 prescale;

	perclk_rate = clk_get_rate(fsl_lpspi->clk_per);

	अगर (config.speed_hz > perclk_rate / 2) अणु
		dev_err(fsl_lpspi->dev,
		      "per-clk should be at least two times of transfer speed");
		वापस -EINVAL;
	पूर्ण

	क्रम (prescale = 0; prescale < 8; prescale++) अणु
		scद_भाग = perclk_rate / config.speed_hz / (1 << prescale) - 2;
		अगर (scद_भाग < 256) अणु
			fsl_lpspi->config.prescale = prescale;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (scद_भाग >= 256)
		वापस -EINVAL;

	ग_लिखोl(scद_भाग | (scद_भाग << 8) | ((scद_भाग >> 1) << 16),
					fsl_lpspi->base + IMX7ULP_CCR);

	dev_dbg(fsl_lpspi->dev, "perclk=%d, speed=%d, prescale=%d, scldiv=%d\n",
		perclk_rate, config.speed_hz, prescale, scद_भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_lpspi_dma_configure(काष्ठा spi_controller *controller)
अणु
	पूर्णांक ret;
	क्रमागत dma_slave_buswidth buswidth;
	काष्ठा dma_slave_config rx = अणुपूर्ण, tx = अणुपूर्ण;
	काष्ठा fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(controller);

	चयन (fsl_lpspi_bytes_per_word(fsl_lpspi->config.bpw)) अणु
	हाल 4:
		buswidth = DMA_SLAVE_BUSWIDTH_4_BYTES;
		अवरोध;
	हाल 2:
		buswidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
		अवरोध;
	हाल 1:
		buswidth = DMA_SLAVE_BUSWIDTH_1_BYTE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	tx.direction = DMA_MEM_TO_DEV;
	tx.dst_addr = fsl_lpspi->base_phys + IMX7ULP_TDR;
	tx.dst_addr_width = buswidth;
	tx.dst_maxburst = 1;
	ret = dmaengine_slave_config(controller->dma_tx, &tx);
	अगर (ret) अणु
		dev_err(fsl_lpspi->dev, "TX dma configuration failed with %d\n",
			ret);
		वापस ret;
	पूर्ण

	rx.direction = DMA_DEV_TO_MEM;
	rx.src_addr = fsl_lpspi->base_phys + IMX7ULP_RDR;
	rx.src_addr_width = buswidth;
	rx.src_maxburst = 1;
	ret = dmaengine_slave_config(controller->dma_rx, &rx);
	अगर (ret) अणु
		dev_err(fsl_lpspi->dev, "RX dma configuration failed with %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_lpspi_config(काष्ठा fsl_lpspi_data *fsl_lpspi)
अणु
	u32 temp;
	पूर्णांक ret;

	अगर (!fsl_lpspi->is_slave) अणु
		ret = fsl_lpspi_set_bitrate(fsl_lpspi);
		अगर (ret)
			वापस ret;
	पूर्ण

	fsl_lpspi_set_watermark(fsl_lpspi);

	अगर (!fsl_lpspi->is_slave)
		temp = CFGR1_MASTER;
	अन्यथा
		temp = CFGR1_PINCFG;
	अगर (fsl_lpspi->config.mode & SPI_CS_HIGH)
		temp |= CFGR1_PCSPOL;
	ग_लिखोl(temp, fsl_lpspi->base + IMX7ULP_CFGR1);

	temp = पढ़ोl(fsl_lpspi->base + IMX7ULP_CR);
	temp |= CR_RRF | CR_RTF | CR_MEN;
	ग_लिखोl(temp, fsl_lpspi->base + IMX7ULP_CR);

	temp = 0;
	अगर (fsl_lpspi->usedma)
		temp = DER_TDDE | DER_RDDE;
	ग_लिखोl(temp, fsl_lpspi->base + IMX7ULP_DER);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_lpspi_setup_transfer(काष्ठा spi_controller *controller,
				     काष्ठा spi_device *spi,
				     काष्ठा spi_transfer *t)
अणु
	काष्ठा fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(spi->controller);

	अगर (t == शून्य)
		वापस -EINVAL;

	fsl_lpspi->config.mode = spi->mode;
	fsl_lpspi->config.bpw = t->bits_per_word;
	fsl_lpspi->config.speed_hz = t->speed_hz;
	अगर (fsl_lpspi->is_only_cs1)
		fsl_lpspi->config.chip_select = 1;
	अन्यथा
		fsl_lpspi->config.chip_select = spi->chip_select;

	अगर (!fsl_lpspi->config.speed_hz)
		fsl_lpspi->config.speed_hz = spi->max_speed_hz;
	अगर (!fsl_lpspi->config.bpw)
		fsl_lpspi->config.bpw = spi->bits_per_word;

	/* Initialize the functions क्रम transfer */
	अगर (fsl_lpspi->config.bpw <= 8) अणु
		fsl_lpspi->rx = fsl_lpspi_buf_rx_u8;
		fsl_lpspi->tx = fsl_lpspi_buf_tx_u8;
	पूर्ण अन्यथा अगर (fsl_lpspi->config.bpw <= 16) अणु
		fsl_lpspi->rx = fsl_lpspi_buf_rx_u16;
		fsl_lpspi->tx = fsl_lpspi_buf_tx_u16;
	पूर्ण अन्यथा अणु
		fsl_lpspi->rx = fsl_lpspi_buf_rx_u32;
		fsl_lpspi->tx = fsl_lpspi_buf_tx_u32;
	पूर्ण

	अगर (t->len <= fsl_lpspi->txfअगरosize)
		fsl_lpspi->watermark = t->len;
	अन्यथा
		fsl_lpspi->watermark = fsl_lpspi->txfअगरosize;

	अगर (fsl_lpspi_can_dma(controller, spi, t))
		fsl_lpspi->usedma = true;
	अन्यथा
		fsl_lpspi->usedma = false;

	वापस fsl_lpspi_config(fsl_lpspi);
पूर्ण

अटल पूर्णांक fsl_lpspi_slave_पात(काष्ठा spi_controller *controller)
अणु
	काष्ठा fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(controller);

	fsl_lpspi->slave_पातed = true;
	अगर (!fsl_lpspi->usedma)
		complete(&fsl_lpspi->xfer_करोne);
	अन्यथा अणु
		complete(&fsl_lpspi->dma_tx_completion);
		complete(&fsl_lpspi->dma_rx_completion);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_lpspi_रुको_क्रम_completion(काष्ठा spi_controller *controller)
अणु
	काष्ठा fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(controller);

	अगर (fsl_lpspi->is_slave) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&fsl_lpspi->xfer_करोne) ||
			fsl_lpspi->slave_पातed) अणु
			dev_dbg(fsl_lpspi->dev, "interrupted\n");
			वापस -EINTR;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!रुको_क्रम_completion_समयout(&fsl_lpspi->xfer_करोne, HZ)) अणु
			dev_dbg(fsl_lpspi->dev, "wait for completion timeout\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_lpspi_reset(काष्ठा fsl_lpspi_data *fsl_lpspi)
अणु
	u32 temp;

	अगर (!fsl_lpspi->usedma) अणु
		/* Disable all पूर्णांकerrupt */
		fsl_lpspi_पूर्णांकctrl(fsl_lpspi, 0);
	पूर्ण

	/* W1C क्रम all flags in SR */
	temp = 0x3F << 8;
	ग_लिखोl(temp, fsl_lpspi->base + IMX7ULP_SR);

	/* Clear FIFO and disable module */
	temp = CR_RRF | CR_RTF;
	ग_लिखोl(temp, fsl_lpspi->base + IMX7ULP_CR);

	वापस 0;
पूर्ण

अटल व्योम fsl_lpspi_dma_rx_callback(व्योम *cookie)
अणु
	काष्ठा fsl_lpspi_data *fsl_lpspi = (काष्ठा fsl_lpspi_data *)cookie;

	complete(&fsl_lpspi->dma_rx_completion);
पूर्ण

अटल व्योम fsl_lpspi_dma_tx_callback(व्योम *cookie)
अणु
	काष्ठा fsl_lpspi_data *fsl_lpspi = (काष्ठा fsl_lpspi_data *)cookie;

	complete(&fsl_lpspi->dma_tx_completion);
पूर्ण

अटल पूर्णांक fsl_lpspi_calculate_समयout(काष्ठा fsl_lpspi_data *fsl_lpspi,
				       पूर्णांक size)
अणु
	अचिन्हित दीर्घ समयout = 0;

	/* Time with actual data transfer and CS change delay related to HW */
	समयout = (8 + 4) * size / fsl_lpspi->config.speed_hz;

	/* Add extra second क्रम scheduler related activities */
	समयout += 1;

	/* Double calculated समयout */
	वापस msecs_to_jअगरfies(2 * समयout * MSEC_PER_SEC);
पूर्ण

अटल पूर्णांक fsl_lpspi_dma_transfer(काष्ठा spi_controller *controller,
				काष्ठा fsl_lpspi_data *fsl_lpspi,
				काष्ठा spi_transfer *transfer)
अणु
	काष्ठा dma_async_tx_descriptor *desc_tx, *desc_rx;
	अचिन्हित दीर्घ transfer_समयout;
	अचिन्हित दीर्घ समयout;
	काष्ठा sg_table *tx = &transfer->tx_sg, *rx = &transfer->rx_sg;
	पूर्णांक ret;

	ret = fsl_lpspi_dma_configure(controller);
	अगर (ret)
		वापस ret;

	desc_rx = dmaengine_prep_slave_sg(controller->dma_rx,
				rx->sgl, rx->nents, DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc_rx)
		वापस -EINVAL;

	desc_rx->callback = fsl_lpspi_dma_rx_callback;
	desc_rx->callback_param = (व्योम *)fsl_lpspi;
	dmaengine_submit(desc_rx);
	reinit_completion(&fsl_lpspi->dma_rx_completion);
	dma_async_issue_pending(controller->dma_rx);

	desc_tx = dmaengine_prep_slave_sg(controller->dma_tx,
				tx->sgl, tx->nents, DMA_MEM_TO_DEV,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc_tx) अणु
		dmaengine_terminate_all(controller->dma_tx);
		वापस -EINVAL;
	पूर्ण

	desc_tx->callback = fsl_lpspi_dma_tx_callback;
	desc_tx->callback_param = (व्योम *)fsl_lpspi;
	dmaengine_submit(desc_tx);
	reinit_completion(&fsl_lpspi->dma_tx_completion);
	dma_async_issue_pending(controller->dma_tx);

	fsl_lpspi->slave_पातed = false;

	अगर (!fsl_lpspi->is_slave) अणु
		transfer_समयout = fsl_lpspi_calculate_समयout(fsl_lpspi,
							       transfer->len);

		/* Wait eDMA to finish the data transfer.*/
		समयout = रुको_क्रम_completion_समयout(&fsl_lpspi->dma_tx_completion,
						      transfer_समयout);
		अगर (!समयout) अणु
			dev_err(fsl_lpspi->dev, "I/O Error in DMA TX\n");
			dmaengine_terminate_all(controller->dma_tx);
			dmaengine_terminate_all(controller->dma_rx);
			fsl_lpspi_reset(fsl_lpspi);
			वापस -ETIMEDOUT;
		पूर्ण

		समयout = रुको_क्रम_completion_समयout(&fsl_lpspi->dma_rx_completion,
						      transfer_समयout);
		अगर (!समयout) अणु
			dev_err(fsl_lpspi->dev, "I/O Error in DMA RX\n");
			dmaengine_terminate_all(controller->dma_tx);
			dmaengine_terminate_all(controller->dma_rx);
			fsl_lpspi_reset(fsl_lpspi);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&fsl_lpspi->dma_tx_completion) ||
			fsl_lpspi->slave_पातed) अणु
			dev_dbg(fsl_lpspi->dev,
				"I/O Error in DMA TX interrupted\n");
			dmaengine_terminate_all(controller->dma_tx);
			dmaengine_terminate_all(controller->dma_rx);
			fsl_lpspi_reset(fsl_lpspi);
			वापस -EINTR;
		पूर्ण

		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&fsl_lpspi->dma_rx_completion) ||
			fsl_lpspi->slave_पातed) अणु
			dev_dbg(fsl_lpspi->dev,
				"I/O Error in DMA RX interrupted\n");
			dmaengine_terminate_all(controller->dma_tx);
			dmaengine_terminate_all(controller->dma_rx);
			fsl_lpspi_reset(fsl_lpspi);
			वापस -EINTR;
		पूर्ण
	पूर्ण

	fsl_lpspi_reset(fsl_lpspi);

	वापस 0;
पूर्ण

अटल व्योम fsl_lpspi_dma_निकास(काष्ठा spi_controller *controller)
अणु
	अगर (controller->dma_rx) अणु
		dma_release_channel(controller->dma_rx);
		controller->dma_rx = शून्य;
	पूर्ण

	अगर (controller->dma_tx) अणु
		dma_release_channel(controller->dma_tx);
		controller->dma_tx = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक fsl_lpspi_dma_init(काष्ठा device *dev,
			      काष्ठा fsl_lpspi_data *fsl_lpspi,
			      काष्ठा spi_controller *controller)
अणु
	पूर्णांक ret;

	/* Prepare क्रम TX DMA: */
	controller->dma_tx = dma_request_chan(dev, "tx");
	अगर (IS_ERR(controller->dma_tx)) अणु
		ret = PTR_ERR(controller->dma_tx);
		dev_dbg(dev, "can't get the TX DMA channel, error %d!\n", ret);
		controller->dma_tx = शून्य;
		जाओ err;
	पूर्ण

	/* Prepare क्रम RX DMA: */
	controller->dma_rx = dma_request_chan(dev, "rx");
	अगर (IS_ERR(controller->dma_rx)) अणु
		ret = PTR_ERR(controller->dma_rx);
		dev_dbg(dev, "can't get the RX DMA channel, error %d\n", ret);
		controller->dma_rx = शून्य;
		जाओ err;
	पूर्ण

	init_completion(&fsl_lpspi->dma_rx_completion);
	init_completion(&fsl_lpspi->dma_tx_completion);
	controller->can_dma = fsl_lpspi_can_dma;
	controller->max_dma_len = FSL_LPSPI_MAX_EDMA_BYTES;

	वापस 0;
err:
	fsl_lpspi_dma_निकास(controller);
	वापस ret;
पूर्ण

अटल पूर्णांक fsl_lpspi_pio_transfer(काष्ठा spi_controller *controller,
				  काष्ठा spi_transfer *t)
अणु
	काष्ठा fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(controller);
	पूर्णांक ret;

	fsl_lpspi->tx_buf = t->tx_buf;
	fsl_lpspi->rx_buf = t->rx_buf;
	fsl_lpspi->reमुख्य = t->len;

	reinit_completion(&fsl_lpspi->xfer_करोne);
	fsl_lpspi->slave_पातed = false;

	fsl_lpspi_ग_लिखो_tx_fअगरo(fsl_lpspi);

	ret = fsl_lpspi_रुको_क्रम_completion(controller);
	अगर (ret)
		वापस ret;

	fsl_lpspi_reset(fsl_lpspi);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_lpspi_transfer_one(काष्ठा spi_controller *controller,
				  काष्ठा spi_device *spi,
				  काष्ठा spi_transfer *t)
अणु
	काष्ठा fsl_lpspi_data *fsl_lpspi =
					spi_controller_get_devdata(controller);
	पूर्णांक ret;

	fsl_lpspi->is_first_byte = true;
	ret = fsl_lpspi_setup_transfer(controller, spi, t);
	अगर (ret < 0)
		वापस ret;

	fsl_lpspi_set_cmd(fsl_lpspi);
	fsl_lpspi->is_first_byte = false;

	अगर (fsl_lpspi->usedma)
		ret = fsl_lpspi_dma_transfer(controller, fsl_lpspi, t);
	अन्यथा
		ret = fsl_lpspi_pio_transfer(controller, t);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल irqवापस_t fsl_lpspi_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 temp_SR, temp_IER;
	काष्ठा fsl_lpspi_data *fsl_lpspi = dev_id;

	temp_IER = पढ़ोl(fsl_lpspi->base + IMX7ULP_IER);
	fsl_lpspi_पूर्णांकctrl(fsl_lpspi, 0);
	temp_SR = पढ़ोl(fsl_lpspi->base + IMX7ULP_SR);

	fsl_lpspi_पढ़ो_rx_fअगरo(fsl_lpspi);

	अगर ((temp_SR & SR_TDF) && (temp_IER & IER_TDIE)) अणु
		fsl_lpspi_ग_लिखो_tx_fअगरo(fsl_lpspi);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (temp_SR & SR_MBF ||
	    पढ़ोl(fsl_lpspi->base + IMX7ULP_FSR) & FSR_TXCOUNT) अणु
		ग_लिखोl(SR_FCF, fsl_lpspi->base + IMX7ULP_SR);
		fsl_lpspi_पूर्णांकctrl(fsl_lpspi, IER_FCIE);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (temp_SR & SR_FCF && (temp_IER & IER_FCIE)) अणु
		ग_लिखोl(SR_FCF, fsl_lpspi->base + IMX7ULP_SR);
		complete(&fsl_lpspi->xfer_करोne);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fsl_lpspi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *controller = dev_get_drvdata(dev);
	काष्ठा fsl_lpspi_data *fsl_lpspi;
	पूर्णांक ret;

	fsl_lpspi = spi_controller_get_devdata(controller);

	ret = clk_prepare_enable(fsl_lpspi->clk_per);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(fsl_lpspi->clk_ipg);
	अगर (ret) अणु
		clk_disable_unprepare(fsl_lpspi->clk_per);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_lpspi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *controller = dev_get_drvdata(dev);
	काष्ठा fsl_lpspi_data *fsl_lpspi;

	fsl_lpspi = spi_controller_get_devdata(controller);

	clk_disable_unprepare(fsl_lpspi->clk_per);
	clk_disable_unprepare(fsl_lpspi->clk_ipg);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक fsl_lpspi_init_rpm(काष्ठा fsl_lpspi_data *fsl_lpspi)
अणु
	काष्ठा device *dev = fsl_lpspi->dev;

	pm_runसमय_enable(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, FSL_LPSPI_RPM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_lpspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_lpspi_data *fsl_lpspi;
	काष्ठा spi_controller *controller;
	काष्ठा resource *res;
	पूर्णांक ret, irq;
	u32 temp;
	bool is_slave;

	is_slave = of_property_पढ़ो_bool((&pdev->dev)->of_node, "spi-slave");
	अगर (is_slave)
		controller = spi_alloc_slave(&pdev->dev,
					माप(काष्ठा fsl_lpspi_data));
	अन्यथा
		controller = spi_alloc_master(&pdev->dev,
					माप(काष्ठा fsl_lpspi_data));

	अगर (!controller)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, controller);

	fsl_lpspi = spi_controller_get_devdata(controller);
	fsl_lpspi->dev = &pdev->dev;
	fsl_lpspi->is_slave = is_slave;
	fsl_lpspi->is_only_cs1 = of_property_पढ़ो_bool((&pdev->dev)->of_node,
						"fsl,spi-only-use-cs1-sel");

	controller->bits_per_word_mask = SPI_BPW_RANGE_MASK(8, 32);
	controller->transfer_one = fsl_lpspi_transfer_one;
	controller->prepare_transfer_hardware = lpspi_prepare_xfer_hardware;
	controller->unprepare_transfer_hardware = lpspi_unprepare_xfer_hardware;
	controller->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	controller->flags = SPI_MASTER_MUST_RX | SPI_MASTER_MUST_TX;
	controller->dev.of_node = pdev->dev.of_node;
	controller->bus_num = pdev->id;
	controller->slave_पात = fsl_lpspi_slave_पात;
	अगर (!fsl_lpspi->is_slave)
		controller->use_gpio_descriptors = true;

	init_completion(&fsl_lpspi->xfer_करोne);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	fsl_lpspi->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(fsl_lpspi->base)) अणु
		ret = PTR_ERR(fsl_lpspi->base);
		जाओ out_controller_put;
	पूर्ण
	fsl_lpspi->base_phys = res->start;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ out_controller_put;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, fsl_lpspi_isr, 0,
			       dev_name(&pdev->dev), fsl_lpspi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't get irq%d: %d\n", irq, ret);
		जाओ out_controller_put;
	पूर्ण

	fsl_lpspi->clk_per = devm_clk_get(&pdev->dev, "per");
	अगर (IS_ERR(fsl_lpspi->clk_per)) अणु
		ret = PTR_ERR(fsl_lpspi->clk_per);
		जाओ out_controller_put;
	पूर्ण

	fsl_lpspi->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(fsl_lpspi->clk_ipg)) अणु
		ret = PTR_ERR(fsl_lpspi->clk_ipg);
		जाओ out_controller_put;
	पूर्ण

	/* enable the घड़ी */
	ret = fsl_lpspi_init_rpm(fsl_lpspi);
	अगर (ret)
		जाओ out_controller_put;

	ret = pm_runसमय_get_sync(fsl_lpspi->dev);
	अगर (ret < 0) अणु
		dev_err(fsl_lpspi->dev, "failed to enable clock\n");
		जाओ out_pm_get;
	पूर्ण

	temp = पढ़ोl(fsl_lpspi->base + IMX7ULP_PARAM);
	fsl_lpspi->txfअगरosize = 1 << (temp & 0x0f);
	fsl_lpspi->rxfअगरosize = 1 << ((temp >> 8) & 0x0f);

	ret = fsl_lpspi_dma_init(&pdev->dev, fsl_lpspi, controller);
	अगर (ret == -EPROBE_DEFER)
		जाओ out_pm_get;

	अगर (ret < 0)
		dev_err(&pdev->dev, "dma setup error %d, use pio\n", ret);

	ret = devm_spi_रेजिस्टर_controller(&pdev->dev, controller);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "spi_register_controller error.\n");
		जाओ out_pm_get;
	पूर्ण

	pm_runसमय_mark_last_busy(fsl_lpspi->dev);
	pm_runसमय_put_स्वतःsuspend(fsl_lpspi->dev);

	वापस 0;

out_pm_get:
	pm_runसमय_करोnt_use_स्वतःsuspend(fsl_lpspi->dev);
	pm_runसमय_put_sync(fsl_lpspi->dev);
	pm_runसमय_disable(fsl_lpspi->dev);
out_controller_put:
	spi_controller_put(controller);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_lpspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *controller = platक्रमm_get_drvdata(pdev);
	काष्ठा fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(controller);

	pm_runसमय_disable(fsl_lpspi->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fsl_lpspi_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	pinctrl_pm_select_sleep_state(dev);
	ret = pm_runसमय_क्रमce_suspend(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused fsl_lpspi_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret) अणु
		dev_err(dev, "Error in resume: %d\n", ret);
		वापस ret;
	पूर्ण

	pinctrl_pm_select_शेष_state(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fsl_lpspi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(fsl_lpspi_runसमय_suspend,
				fsl_lpspi_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(fsl_lpspi_suspend, fsl_lpspi_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_lpspi_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = fsl_lpspi_dt_ids,
		.pm = &fsl_lpspi_pm_ops,
	पूर्ण,
	.probe = fsl_lpspi_probe,
	.हटाओ = fsl_lpspi_हटाओ,
पूर्ण;
module_platक्रमm_driver(fsl_lpspi_driver);

MODULE_DESCRIPTION("LPSPI Controller driver");
MODULE_AUTHOR("Gao Pan <pandy.gao@nxp.com>");
MODULE_LICENSE("GPL");
