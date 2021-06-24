<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2009 Samsung Electronics Co., Ltd.
//      Jaswinder Singh <jassi.brar@samsung.com>

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>

#समावेश <linux/platक्रमm_data/spi-s3c64xx.h>

#घोषणा MAX_SPI_PORTS		6
#घोषणा S3C64XX_SPI_QUIRK_POLL		(1 << 0)
#घोषणा S3C64XX_SPI_QUIRK_CS_AUTO	(1 << 1)
#घोषणा AUTOSUSPEND_TIMEOUT	2000

/* Registers and bit-fields */

#घोषणा S3C64XX_SPI_CH_CFG		0x00
#घोषणा S3C64XX_SPI_CLK_CFG		0x04
#घोषणा S3C64XX_SPI_MODE_CFG		0x08
#घोषणा S3C64XX_SPI_CS_REG		0x0C
#घोषणा S3C64XX_SPI_INT_EN		0x10
#घोषणा S3C64XX_SPI_STATUS		0x14
#घोषणा S3C64XX_SPI_TX_DATA		0x18
#घोषणा S3C64XX_SPI_RX_DATA		0x1C
#घोषणा S3C64XX_SPI_PACKET_CNT		0x20
#घोषणा S3C64XX_SPI_PENDING_CLR		0x24
#घोषणा S3C64XX_SPI_SWAP_CFG		0x28
#घोषणा S3C64XX_SPI_FB_CLK		0x2C

#घोषणा S3C64XX_SPI_CH_HS_EN		(1<<6)	/* High Speed Enable */
#घोषणा S3C64XX_SPI_CH_SW_RST		(1<<5)
#घोषणा S3C64XX_SPI_CH_SLAVE		(1<<4)
#घोषणा S3C64XX_SPI_CPOL_L		(1<<3)
#घोषणा S3C64XX_SPI_CPHA_B		(1<<2)
#घोषणा S3C64XX_SPI_CH_RXCH_ON		(1<<1)
#घोषणा S3C64XX_SPI_CH_TXCH_ON		(1<<0)

#घोषणा S3C64XX_SPI_CLKSEL_SRCMSK	(3<<9)
#घोषणा S3C64XX_SPI_CLKSEL_SRCSHFT	9
#घोषणा S3C64XX_SPI_ENCLK_ENABLE	(1<<8)
#घोषणा S3C64XX_SPI_PSR_MASK		0xff

#घोषणा S3C64XX_SPI_MODE_CH_TSZ_BYTE		(0<<29)
#घोषणा S3C64XX_SPI_MODE_CH_TSZ_HALFWORD	(1<<29)
#घोषणा S3C64XX_SPI_MODE_CH_TSZ_WORD		(2<<29)
#घोषणा S3C64XX_SPI_MODE_CH_TSZ_MASK		(3<<29)
#घोषणा S3C64XX_SPI_MODE_BUS_TSZ_BYTE		(0<<17)
#घोषणा S3C64XX_SPI_MODE_BUS_TSZ_HALFWORD	(1<<17)
#घोषणा S3C64XX_SPI_MODE_BUS_TSZ_WORD		(2<<17)
#घोषणा S3C64XX_SPI_MODE_BUS_TSZ_MASK		(3<<17)
#घोषणा S3C64XX_SPI_MODE_RXDMA_ON		(1<<2)
#घोषणा S3C64XX_SPI_MODE_TXDMA_ON		(1<<1)
#घोषणा S3C64XX_SPI_MODE_4BURST			(1<<0)

#घोषणा S3C64XX_SPI_CS_NSC_CNT_2		(2<<4)
#घोषणा S3C64XX_SPI_CS_AUTO			(1<<1)
#घोषणा S3C64XX_SPI_CS_SIG_INACT		(1<<0)

#घोषणा S3C64XX_SPI_INT_TRAILING_EN		(1<<6)
#घोषणा S3C64XX_SPI_INT_RX_OVERRUN_EN		(1<<5)
#घोषणा S3C64XX_SPI_INT_RX_UNDERRUN_EN		(1<<4)
#घोषणा S3C64XX_SPI_INT_TX_OVERRUN_EN		(1<<3)
#घोषणा S3C64XX_SPI_INT_TX_UNDERRUN_EN		(1<<2)
#घोषणा S3C64XX_SPI_INT_RX_FIFORDY_EN		(1<<1)
#घोषणा S3C64XX_SPI_INT_TX_FIFORDY_EN		(1<<0)

#घोषणा S3C64XX_SPI_ST_RX_OVERRUN_ERR		(1<<5)
#घोषणा S3C64XX_SPI_ST_RX_UNDERRUN_ERR		(1<<4)
#घोषणा S3C64XX_SPI_ST_TX_OVERRUN_ERR		(1<<3)
#घोषणा S3C64XX_SPI_ST_TX_UNDERRUN_ERR		(1<<2)
#घोषणा S3C64XX_SPI_ST_RX_FIFORDY		(1<<1)
#घोषणा S3C64XX_SPI_ST_TX_FIFORDY		(1<<0)

#घोषणा S3C64XX_SPI_PACKET_CNT_EN		(1<<16)

#घोषणा S3C64XX_SPI_PND_TX_UNDERRUN_CLR		(1<<4)
#घोषणा S3C64XX_SPI_PND_TX_OVERRUN_CLR		(1<<3)
#घोषणा S3C64XX_SPI_PND_RX_UNDERRUN_CLR		(1<<2)
#घोषणा S3C64XX_SPI_PND_RX_OVERRUN_CLR		(1<<1)
#घोषणा S3C64XX_SPI_PND_TRAILING_CLR		(1<<0)

#घोषणा S3C64XX_SPI_SWAP_RX_HALF_WORD		(1<<7)
#घोषणा S3C64XX_SPI_SWAP_RX_BYTE		(1<<6)
#घोषणा S3C64XX_SPI_SWAP_RX_BIT			(1<<5)
#घोषणा S3C64XX_SPI_SWAP_RX_EN			(1<<4)
#घोषणा S3C64XX_SPI_SWAP_TX_HALF_WORD		(1<<3)
#घोषणा S3C64XX_SPI_SWAP_TX_BYTE		(1<<2)
#घोषणा S3C64XX_SPI_SWAP_TX_BIT			(1<<1)
#घोषणा S3C64XX_SPI_SWAP_TX_EN			(1<<0)

#घोषणा S3C64XX_SPI_FBCLK_MSK			(3<<0)

#घोषणा FIFO_LVL_MASK(i) ((i)->port_conf->fअगरo_lvl_mask[i->port_id])
#घोषणा S3C64XX_SPI_ST_TX_DONE(v, i) (((v) & \
				(1 << (i)->port_conf->tx_st_करोne)) ? 1 : 0)
#घोषणा TX_FIFO_LVL(v, i) (((v) >> 6) & FIFO_LVL_MASK(i))
#घोषणा RX_FIFO_LVL(v, i) (((v) >> (i)->port_conf->rx_lvl_offset) & \
					FIFO_LVL_MASK(i))

#घोषणा S3C64XX_SPI_MAX_TRAILCNT	0x3ff
#घोषणा S3C64XX_SPI_TRAILCNT_OFF	19

#घोषणा S3C64XX_SPI_TRAILCNT		S3C64XX_SPI_MAX_TRAILCNT

#घोषणा msecs_to_loops(t) (loops_per_jअगरfy / 1000 * HZ * t)
#घोषणा is_polling(x)	(x->port_conf->quirks & S3C64XX_SPI_QUIRK_POLL)

#घोषणा RXBUSY    (1<<2)
#घोषणा TXBUSY    (1<<3)

काष्ठा s3c64xx_spi_dma_data अणु
	काष्ठा dma_chan *ch;
	dma_cookie_t cookie;
	क्रमागत dma_transfer_direction direction;
पूर्ण;

/**
 * काष्ठा s3c64xx_spi_port_config - SPI Controller hardware info
 * @fअगरo_lvl_mask: Bit-mask क्रम अणुTX|RXपूर्ण_FIFO_LVL bits in SPI_STATUS रेजिस्टर.
 * @rx_lvl_offset: Bit offset of RX_FIFO_LVL bits in SPI_STATUS regiter.
 * @tx_st_करोne: Bit offset of TX_DONE bit in SPI_STATUS regiter.
 * @quirks: Biपंचांगask of known quirks
 * @high_speed: True, अगर the controller supports HIGH_SPEED_EN bit.
 * @clk_from_cmu: True, अगर the controller करोes not include a घड़ी mux and
 *	prescaler unit.
 * @clk_ioclk: True अगर घड़ी is present on this device
 *
 * The Samsung s3c64xx SPI controller are used on various Samsung SoC's but
 * dअगरfer in some aspects such as the size of the fअगरo and spi bus घड़ी
 * setup. Such dअगरferences are specअगरied to the driver using this काष्ठाure
 * which is provided as driver data to the driver.
 */
काष्ठा s3c64xx_spi_port_config अणु
	पूर्णांक	fअगरo_lvl_mask[MAX_SPI_PORTS];
	पूर्णांक	rx_lvl_offset;
	पूर्णांक	tx_st_करोne;
	पूर्णांक	quirks;
	bool	high_speed;
	bool	clk_from_cmu;
	bool	clk_ioclk;
पूर्ण;

/**
 * काष्ठा s3c64xx_spi_driver_data - Runसमय info holder क्रम SPI driver.
 * @clk: Poपूर्णांकer to the spi घड़ी.
 * @src_clk: Poपूर्णांकer to the घड़ी used to generate SPI संकेतs.
 * @ioclk: Poपूर्णांकer to the i/o घड़ी between master and slave
 * @pdev: Poपूर्णांकer to device's platक्रमm device data
 * @master: Poपूर्णांकer to the SPI Protocol master.
 * @cntrlr_info: Platक्रमm specअगरic data क्रम the controller this driver manages.
 * @lock: Controller specअगरic lock.
 * @state: Set of FLAGS to indicate status.
 * @sfr_start: BUS address of SPI controller regs.
 * @regs: Poपूर्णांकer to ioremap'ed controller रेजिस्टरs.
 * @xfer_completion: To indicate completion of xfer task.
 * @cur_mode: Stores the active configuration of the controller.
 * @cur_bpw: Stores the active bits per word settings.
 * @cur_speed: Current घड़ी speed
 * @rx_dma: Local receive DMA data (e.g. chan and direction)
 * @tx_dma: Local transmit DMA data (e.g. chan and direction)
 * @port_conf: Local SPI port configuartion data
 * @port_id: Port identअगरication number
 */
काष्ठा s3c64xx_spi_driver_data अणु
	व्योम __iomem                    *regs;
	काष्ठा clk                      *clk;
	काष्ठा clk                      *src_clk;
	काष्ठा clk                      *ioclk;
	काष्ठा platक्रमm_device          *pdev;
	काष्ठा spi_master               *master;
	काष्ठा s3c64xx_spi_info         *cntrlr_info;
	spinlock_t                      lock;
	अचिन्हित दीर्घ                   sfr_start;
	काष्ठा completion               xfer_completion;
	अचिन्हित                        state;
	अचिन्हित                        cur_mode, cur_bpw;
	अचिन्हित                        cur_speed;
	काष्ठा s3c64xx_spi_dma_data	rx_dma;
	काष्ठा s3c64xx_spi_dma_data	tx_dma;
	स्थिर काष्ठा s3c64xx_spi_port_config	*port_conf;
	अचिन्हित पूर्णांक			port_id;
पूर्ण;

अटल व्योम s3c64xx_flush_fअगरo(काष्ठा s3c64xx_spi_driver_data *sdd)
अणु
	व्योम __iomem *regs = sdd->regs;
	अचिन्हित दीर्घ loops;
	u32 val;

	ग_लिखोl(0, regs + S3C64XX_SPI_PACKET_CNT);

	val = पढ़ोl(regs + S3C64XX_SPI_CH_CFG);
	val &= ~(S3C64XX_SPI_CH_RXCH_ON | S3C64XX_SPI_CH_TXCH_ON);
	ग_लिखोl(val, regs + S3C64XX_SPI_CH_CFG);

	val = पढ़ोl(regs + S3C64XX_SPI_CH_CFG);
	val |= S3C64XX_SPI_CH_SW_RST;
	val &= ~S3C64XX_SPI_CH_HS_EN;
	ग_लिखोl(val, regs + S3C64XX_SPI_CH_CFG);

	/* Flush TxFIFO*/
	loops = msecs_to_loops(1);
	करो अणु
		val = पढ़ोl(regs + S3C64XX_SPI_STATUS);
	पूर्ण जबतक (TX_FIFO_LVL(val, sdd) && loops--);

	अगर (loops == 0)
		dev_warn(&sdd->pdev->dev, "Timed out flushing TX FIFO\n");

	/* Flush RxFIFO*/
	loops = msecs_to_loops(1);
	करो अणु
		val = पढ़ोl(regs + S3C64XX_SPI_STATUS);
		अगर (RX_FIFO_LVL(val, sdd))
			पढ़ोl(regs + S3C64XX_SPI_RX_DATA);
		अन्यथा
			अवरोध;
	पूर्ण जबतक (loops--);

	अगर (loops == 0)
		dev_warn(&sdd->pdev->dev, "Timed out flushing RX FIFO\n");

	val = पढ़ोl(regs + S3C64XX_SPI_CH_CFG);
	val &= ~S3C64XX_SPI_CH_SW_RST;
	ग_लिखोl(val, regs + S3C64XX_SPI_CH_CFG);

	val = पढ़ोl(regs + S3C64XX_SPI_MODE_CFG);
	val &= ~(S3C64XX_SPI_MODE_TXDMA_ON | S3C64XX_SPI_MODE_RXDMA_ON);
	ग_लिखोl(val, regs + S3C64XX_SPI_MODE_CFG);
पूर्ण

अटल व्योम s3c64xx_spi_dmacb(व्योम *data)
अणु
	काष्ठा s3c64xx_spi_driver_data *sdd;
	काष्ठा s3c64xx_spi_dma_data *dma = data;
	अचिन्हित दीर्घ flags;

	अगर (dma->direction == DMA_DEV_TO_MEM)
		sdd = container_of(data,
			काष्ठा s3c64xx_spi_driver_data, rx_dma);
	अन्यथा
		sdd = container_of(data,
			काष्ठा s3c64xx_spi_driver_data, tx_dma);

	spin_lock_irqsave(&sdd->lock, flags);

	अगर (dma->direction == DMA_DEV_TO_MEM) अणु
		sdd->state &= ~RXBUSY;
		अगर (!(sdd->state & TXBUSY))
			complete(&sdd->xfer_completion);
	पूर्ण अन्यथा अणु
		sdd->state &= ~TXBUSY;
		अगर (!(sdd->state & RXBUSY))
			complete(&sdd->xfer_completion);
	पूर्ण

	spin_unlock_irqrestore(&sdd->lock, flags);
पूर्ण

अटल पूर्णांक prepare_dma(काष्ठा s3c64xx_spi_dma_data *dma,
			काष्ठा sg_table *sgt)
अणु
	काष्ठा s3c64xx_spi_driver_data *sdd;
	काष्ठा dma_slave_config config;
	काष्ठा dma_async_tx_descriptor *desc;
	पूर्णांक ret;

	स_रखो(&config, 0, माप(config));

	अगर (dma->direction == DMA_DEV_TO_MEM) अणु
		sdd = container_of((व्योम *)dma,
			काष्ठा s3c64xx_spi_driver_data, rx_dma);
		config.direction = dma->direction;
		config.src_addr = sdd->sfr_start + S3C64XX_SPI_RX_DATA;
		config.src_addr_width = sdd->cur_bpw / 8;
		config.src_maxburst = 1;
		dmaengine_slave_config(dma->ch, &config);
	पूर्ण अन्यथा अणु
		sdd = container_of((व्योम *)dma,
			काष्ठा s3c64xx_spi_driver_data, tx_dma);
		config.direction = dma->direction;
		config.dst_addr = sdd->sfr_start + S3C64XX_SPI_TX_DATA;
		config.dst_addr_width = sdd->cur_bpw / 8;
		config.dst_maxburst = 1;
		dmaengine_slave_config(dma->ch, &config);
	पूर्ण

	desc = dmaengine_prep_slave_sg(dma->ch, sgt->sgl, sgt->nents,
				       dma->direction, DMA_PREP_INTERRUPT);
	अगर (!desc) अणु
		dev_err(&sdd->pdev->dev, "unable to prepare %s scatterlist",
			dma->direction == DMA_DEV_TO_MEM ? "rx" : "tx");
		वापस -ENOMEM;
	पूर्ण

	desc->callback = s3c64xx_spi_dmacb;
	desc->callback_param = dma;

	dma->cookie = dmaengine_submit(desc);
	ret = dma_submit_error(dma->cookie);
	अगर (ret) अणु
		dev_err(&sdd->pdev->dev, "DMA submission failed");
		वापस -EIO;
	पूर्ण

	dma_async_issue_pending(dma->ch);
	वापस 0;
पूर्ण

अटल व्योम s3c64xx_spi_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा s3c64xx_spi_driver_data *sdd =
					spi_master_get_devdata(spi->master);

	अगर (sdd->cntrlr_info->no_cs)
		वापस;

	अगर (enable) अणु
		अगर (!(sdd->port_conf->quirks & S3C64XX_SPI_QUIRK_CS_AUTO)) अणु
			ग_लिखोl(0, sdd->regs + S3C64XX_SPI_CS_REG);
		पूर्ण अन्यथा अणु
			u32 ssel = पढ़ोl(sdd->regs + S3C64XX_SPI_CS_REG);

			ssel |= (S3C64XX_SPI_CS_AUTO |
						S3C64XX_SPI_CS_NSC_CNT_2);
			ग_लिखोl(ssel, sdd->regs + S3C64XX_SPI_CS_REG);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(sdd->port_conf->quirks & S3C64XX_SPI_QUIRK_CS_AUTO))
			ग_लिखोl(S3C64XX_SPI_CS_SIG_INACT,
			       sdd->regs + S3C64XX_SPI_CS_REG);
	पूर्ण
पूर्ण

अटल पूर्णांक s3c64xx_spi_prepare_transfer(काष्ठा spi_master *spi)
अणु
	काष्ठा s3c64xx_spi_driver_data *sdd = spi_master_get_devdata(spi);

	अगर (is_polling(sdd))
		वापस 0;

	spi->dma_rx = sdd->rx_dma.ch;
	spi->dma_tx = sdd->tx_dma.ch;

	वापस 0;
पूर्ण

अटल bool s3c64xx_spi_can_dma(काष्ठा spi_master *master,
				काष्ठा spi_device *spi,
				काष्ठा spi_transfer *xfer)
अणु
	काष्ठा s3c64xx_spi_driver_data *sdd = spi_master_get_devdata(master);

	वापस xfer->len > (FIFO_LVL_MASK(sdd) >> 1) + 1;
पूर्ण

अटल पूर्णांक s3c64xx_enable_datapath(काष्ठा s3c64xx_spi_driver_data *sdd,
				    काष्ठा spi_transfer *xfer, पूर्णांक dma_mode)
अणु
	व्योम __iomem *regs = sdd->regs;
	u32 modecfg, chcfg;
	पूर्णांक ret = 0;

	modecfg = पढ़ोl(regs + S3C64XX_SPI_MODE_CFG);
	modecfg &= ~(S3C64XX_SPI_MODE_TXDMA_ON | S3C64XX_SPI_MODE_RXDMA_ON);

	chcfg = पढ़ोl(regs + S3C64XX_SPI_CH_CFG);
	chcfg &= ~S3C64XX_SPI_CH_TXCH_ON;

	अगर (dma_mode) अणु
		chcfg &= ~S3C64XX_SPI_CH_RXCH_ON;
	पूर्ण अन्यथा अणु
		/* Always shअगरt in data in FIFO, even अगर xfer is Tx only,
		 * this helps setting PCKT_CNT value क्रम generating घड़ीs
		 * as exactly needed.
		 */
		chcfg |= S3C64XX_SPI_CH_RXCH_ON;
		ग_लिखोl(((xfer->len * 8 / sdd->cur_bpw) & 0xffff)
					| S3C64XX_SPI_PACKET_CNT_EN,
					regs + S3C64XX_SPI_PACKET_CNT);
	पूर्ण

	अगर (xfer->tx_buf != शून्य) अणु
		sdd->state |= TXBUSY;
		chcfg |= S3C64XX_SPI_CH_TXCH_ON;
		अगर (dma_mode) अणु
			modecfg |= S3C64XX_SPI_MODE_TXDMA_ON;
			ret = prepare_dma(&sdd->tx_dma, &xfer->tx_sg);
		पूर्ण अन्यथा अणु
			चयन (sdd->cur_bpw) अणु
			हाल 32:
				ioग_लिखो32_rep(regs + S3C64XX_SPI_TX_DATA,
					xfer->tx_buf, xfer->len / 4);
				अवरोध;
			हाल 16:
				ioग_लिखो16_rep(regs + S3C64XX_SPI_TX_DATA,
					xfer->tx_buf, xfer->len / 2);
				अवरोध;
			शेष:
				ioग_लिखो8_rep(regs + S3C64XX_SPI_TX_DATA,
					xfer->tx_buf, xfer->len);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (xfer->rx_buf != शून्य) अणु
		sdd->state |= RXBUSY;

		अगर (sdd->port_conf->high_speed && sdd->cur_speed >= 30000000UL
					&& !(sdd->cur_mode & SPI_CPHA))
			chcfg |= S3C64XX_SPI_CH_HS_EN;

		अगर (dma_mode) अणु
			modecfg |= S3C64XX_SPI_MODE_RXDMA_ON;
			chcfg |= S3C64XX_SPI_CH_RXCH_ON;
			ग_लिखोl(((xfer->len * 8 / sdd->cur_bpw) & 0xffff)
					| S3C64XX_SPI_PACKET_CNT_EN,
					regs + S3C64XX_SPI_PACKET_CNT);
			ret = prepare_dma(&sdd->rx_dma, &xfer->rx_sg);
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस ret;

	ग_लिखोl(modecfg, regs + S3C64XX_SPI_MODE_CFG);
	ग_लिखोl(chcfg, regs + S3C64XX_SPI_CH_CFG);

	वापस 0;
पूर्ण

अटल u32 s3c64xx_spi_रुको_क्रम_समयout(काष्ठा s3c64xx_spi_driver_data *sdd,
					पूर्णांक समयout_ms)
अणु
	व्योम __iomem *regs = sdd->regs;
	अचिन्हित दीर्घ val = 1;
	u32 status;

	/* max fअगरo depth available */
	u32 max_fअगरo = (FIFO_LVL_MASK(sdd) >> 1) + 1;

	अगर (समयout_ms)
		val = msecs_to_loops(समयout_ms);

	करो अणु
		status = पढ़ोl(regs + S3C64XX_SPI_STATUS);
	पूर्ण जबतक (RX_FIFO_LVL(status, sdd) < max_fअगरo && --val);

	/* वापस the actual received data length */
	वापस RX_FIFO_LVL(status, sdd);
पूर्ण

अटल पूर्णांक s3c64xx_रुको_क्रम_dma(काष्ठा s3c64xx_spi_driver_data *sdd,
				काष्ठा spi_transfer *xfer)
अणु
	व्योम __iomem *regs = sdd->regs;
	अचिन्हित दीर्घ val;
	u32 status;
	पूर्णांक ms;

	/* millisecs to xfer 'len' bytes @ 'cur_speed' */
	ms = xfer->len * 8 * 1000 / sdd->cur_speed;
	ms += 30;               /* some tolerance */
	ms = max(ms, 100);      /* minimum समयout */

	val = msecs_to_jअगरfies(ms) + 10;
	val = रुको_क्रम_completion_समयout(&sdd->xfer_completion, val);

	/*
	 * If the previous xfer was completed within समयout, then
	 * proceed further अन्यथा वापस -EIO.
	 * DmaTx वापसs after simply writing data in the FIFO,
	 * w/o रुकोing क्रम real transmission on the bus to finish.
	 * DmaRx वापसs only after Dma पढ़ो data from FIFO which
	 * needs bus transmission to finish, so we करोn't worry अगर
	 * Xfer involved Rx(with or without Tx).
	 */
	अगर (val && !xfer->rx_buf) अणु
		val = msecs_to_loops(10);
		status = पढ़ोl(regs + S3C64XX_SPI_STATUS);
		जबतक ((TX_FIFO_LVL(status, sdd)
			|| !S3C64XX_SPI_ST_TX_DONE(status, sdd))
		       && --val) अणु
			cpu_relax();
			status = पढ़ोl(regs + S3C64XX_SPI_STATUS);
		पूर्ण

	पूर्ण

	/* If समयd out जबतक checking rx/tx status वापस error */
	अगर (!val)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक s3c64xx_रुको_क्रम_pio(काष्ठा s3c64xx_spi_driver_data *sdd,
				काष्ठा spi_transfer *xfer)
अणु
	व्योम __iomem *regs = sdd->regs;
	अचिन्हित दीर्घ val;
	u32 status;
	पूर्णांक loops;
	u32 cpy_len;
	u8 *buf;
	पूर्णांक ms;

	/* millisecs to xfer 'len' bytes @ 'cur_speed' */
	ms = xfer->len * 8 * 1000 / sdd->cur_speed;
	ms += 10; /* some tolerance */

	val = msecs_to_loops(ms);
	करो अणु
		status = पढ़ोl(regs + S3C64XX_SPI_STATUS);
	पूर्ण जबतक (RX_FIFO_LVL(status, sdd) < xfer->len && --val);

	अगर (!val)
		वापस -EIO;

	/* If it was only Tx */
	अगर (!xfer->rx_buf) अणु
		sdd->state &= ~TXBUSY;
		वापस 0;
	पूर्ण

	/*
	 * If the receive length is bigger than the controller fअगरo
	 * size, calculate the loops and पढ़ो the fअगरo as many बार.
	 * loops = length / max fअगरo size (calculated by using the
	 * fअगरo mask).
	 * For any size less than the fअगरo size the below code is
	 * executed atleast once.
	 */
	loops = xfer->len / ((FIFO_LVL_MASK(sdd) >> 1) + 1);
	buf = xfer->rx_buf;
	करो अणु
		/* रुको क्रम data to be received in the fअगरo */
		cpy_len = s3c64xx_spi_रुको_क्रम_समयout(sdd,
						       (loops ? ms : 0));

		चयन (sdd->cur_bpw) अणु
		हाल 32:
			ioपढ़ो32_rep(regs + S3C64XX_SPI_RX_DATA,
				     buf, cpy_len / 4);
			अवरोध;
		हाल 16:
			ioपढ़ो16_rep(regs + S3C64XX_SPI_RX_DATA,
				     buf, cpy_len / 2);
			अवरोध;
		शेष:
			ioपढ़ो8_rep(regs + S3C64XX_SPI_RX_DATA,
				    buf, cpy_len);
			अवरोध;
		पूर्ण

		buf = buf + cpy_len;
	पूर्ण जबतक (loops--);
	sdd->state &= ~RXBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक s3c64xx_spi_config(काष्ठा s3c64xx_spi_driver_data *sdd)
अणु
	व्योम __iomem *regs = sdd->regs;
	पूर्णांक ret;
	u32 val;

	/* Disable Clock */
	अगर (!sdd->port_conf->clk_from_cmu) अणु
		val = पढ़ोl(regs + S3C64XX_SPI_CLK_CFG);
		val &= ~S3C64XX_SPI_ENCLK_ENABLE;
		ग_लिखोl(val, regs + S3C64XX_SPI_CLK_CFG);
	पूर्ण

	/* Set Polarity and Phase */
	val = पढ़ोl(regs + S3C64XX_SPI_CH_CFG);
	val &= ~(S3C64XX_SPI_CH_SLAVE |
			S3C64XX_SPI_CPOL_L |
			S3C64XX_SPI_CPHA_B);

	अगर (sdd->cur_mode & SPI_CPOL)
		val |= S3C64XX_SPI_CPOL_L;

	अगर (sdd->cur_mode & SPI_CPHA)
		val |= S3C64XX_SPI_CPHA_B;

	ग_लिखोl(val, regs + S3C64XX_SPI_CH_CFG);

	/* Set Channel & DMA Mode */
	val = पढ़ोl(regs + S3C64XX_SPI_MODE_CFG);
	val &= ~(S3C64XX_SPI_MODE_BUS_TSZ_MASK
			| S3C64XX_SPI_MODE_CH_TSZ_MASK);

	चयन (sdd->cur_bpw) अणु
	हाल 32:
		val |= S3C64XX_SPI_MODE_BUS_TSZ_WORD;
		val |= S3C64XX_SPI_MODE_CH_TSZ_WORD;
		अवरोध;
	हाल 16:
		val |= S3C64XX_SPI_MODE_BUS_TSZ_HALFWORD;
		val |= S3C64XX_SPI_MODE_CH_TSZ_HALFWORD;
		अवरोध;
	शेष:
		val |= S3C64XX_SPI_MODE_BUS_TSZ_BYTE;
		val |= S3C64XX_SPI_MODE_CH_TSZ_BYTE;
		अवरोध;
	पूर्ण

	ग_लिखोl(val, regs + S3C64XX_SPI_MODE_CFG);

	अगर (sdd->port_conf->clk_from_cmu) अणु
		/* The src_clk घड़ी is भागided पूर्णांकernally by 2 */
		ret = clk_set_rate(sdd->src_clk, sdd->cur_speed * 2);
		अगर (ret)
			वापस ret;
		sdd->cur_speed = clk_get_rate(sdd->src_clk) / 2;
	पूर्ण अन्यथा अणु
		/* Configure Clock */
		val = पढ़ोl(regs + S3C64XX_SPI_CLK_CFG);
		val &= ~S3C64XX_SPI_PSR_MASK;
		val |= ((clk_get_rate(sdd->src_clk) / sdd->cur_speed / 2 - 1)
				& S3C64XX_SPI_PSR_MASK);
		ग_लिखोl(val, regs + S3C64XX_SPI_CLK_CFG);

		/* Enable Clock */
		val = पढ़ोl(regs + S3C64XX_SPI_CLK_CFG);
		val |= S3C64XX_SPI_ENCLK_ENABLE;
		ग_लिखोl(val, regs + S3C64XX_SPI_CLK_CFG);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा XFER_DMAADDR_INVALID DMA_BIT_MASK(32)

अटल पूर्णांक s3c64xx_spi_prepare_message(काष्ठा spi_master *master,
				       काष्ठा spi_message *msg)
अणु
	काष्ठा s3c64xx_spi_driver_data *sdd = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = msg->spi;
	काष्ठा s3c64xx_spi_csinfo *cs = spi->controller_data;

	/* Configure feedback delay */
	ग_लिखोl(cs->fb_delay & 0x3, sdd->regs + S3C64XX_SPI_FB_CLK);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c64xx_spi_transfer_one(काष्ठा spi_master *master,
				    काष्ठा spi_device *spi,
				    काष्ठा spi_transfer *xfer)
अणु
	काष्ठा s3c64xx_spi_driver_data *sdd = spi_master_get_devdata(master);
	स्थिर अचिन्हित पूर्णांक fअगरo_len = (FIFO_LVL_MASK(sdd) >> 1) + 1;
	स्थिर व्योम *tx_buf = शून्य;
	व्योम *rx_buf = शून्य;
	पूर्णांक target_len = 0, origin_len = 0;
	पूर्णांक use_dma = 0;
	पूर्णांक status;
	u32 speed;
	u8 bpw;
	अचिन्हित दीर्घ flags;

	reinit_completion(&sdd->xfer_completion);

	/* Only BPW and Speed may change across transfers */
	bpw = xfer->bits_per_word;
	speed = xfer->speed_hz;

	अगर (bpw != sdd->cur_bpw || speed != sdd->cur_speed) अणु
		sdd->cur_bpw = bpw;
		sdd->cur_speed = speed;
		sdd->cur_mode = spi->mode;
		status = s3c64xx_spi_config(sdd);
		अगर (status)
			वापस status;
	पूर्ण

	अगर (!is_polling(sdd) && (xfer->len > fअगरo_len) &&
	    sdd->rx_dma.ch && sdd->tx_dma.ch) अणु
		use_dma = 1;

	पूर्ण अन्यथा अगर (is_polling(sdd) && xfer->len > fअगरo_len) अणु
		tx_buf = xfer->tx_buf;
		rx_buf = xfer->rx_buf;
		origin_len = xfer->len;

		target_len = xfer->len;
		अगर (xfer->len > fअगरo_len)
			xfer->len = fअगरo_len;
	पूर्ण

	करो अणु
		spin_lock_irqsave(&sdd->lock, flags);

		/* Pending only which is to be करोne */
		sdd->state &= ~RXBUSY;
		sdd->state &= ~TXBUSY;

		/* Start the संकेतs */
		s3c64xx_spi_set_cs(spi, true);

		status = s3c64xx_enable_datapath(sdd, xfer, use_dma);

		spin_unlock_irqrestore(&sdd->lock, flags);

		अगर (status) अणु
			dev_err(&spi->dev, "failed to enable data path for transfer: %d\n", status);
			अवरोध;
		पूर्ण

		अगर (use_dma)
			status = s3c64xx_रुको_क्रम_dma(sdd, xfer);
		अन्यथा
			status = s3c64xx_रुको_क्रम_pio(sdd, xfer);

		अगर (status) अणु
			dev_err(&spi->dev,
				"I/O Error: rx-%d tx-%d rx-%c tx-%c len-%d dma-%d res-(%d)\n",
				xfer->rx_buf ? 1 : 0, xfer->tx_buf ? 1 : 0,
				(sdd->state & RXBUSY) ? 'f' : 'p',
				(sdd->state & TXBUSY) ? 'f' : 'p',
				xfer->len, use_dma ? 1 : 0, status);

			अगर (use_dma) अणु
				काष्ठा dma_tx_state s;

				अगर (xfer->tx_buf && (sdd->state & TXBUSY)) अणु
					dmaengine_छोड़ो(sdd->tx_dma.ch);
					dmaengine_tx_status(sdd->tx_dma.ch, sdd->tx_dma.cookie, &s);
					dmaengine_terminate_all(sdd->tx_dma.ch);
					dev_err(&spi->dev, "TX residue: %d\n", s.residue);

				पूर्ण
				अगर (xfer->rx_buf && (sdd->state & RXBUSY)) अणु
					dmaengine_छोड़ो(sdd->rx_dma.ch);
					dmaengine_tx_status(sdd->rx_dma.ch, sdd->rx_dma.cookie, &s);
					dmaengine_terminate_all(sdd->rx_dma.ch);
					dev_err(&spi->dev, "RX residue: %d\n", s.residue);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			s3c64xx_flush_fअगरo(sdd);
		पूर्ण
		अगर (target_len > 0) अणु
			target_len -= xfer->len;

			अगर (xfer->tx_buf)
				xfer->tx_buf += xfer->len;

			अगर (xfer->rx_buf)
				xfer->rx_buf += xfer->len;

			अगर (target_len > fअगरo_len)
				xfer->len = fअगरo_len;
			अन्यथा
				xfer->len = target_len;
		पूर्ण
	पूर्ण जबतक (target_len > 0);

	अगर (origin_len) अणु
		/* Restore original xfer buffers and length */
		xfer->tx_buf = tx_buf;
		xfer->rx_buf = rx_buf;
		xfer->len = origin_len;
	पूर्ण

	वापस status;
पूर्ण

अटल काष्ठा s3c64xx_spi_csinfo *s3c64xx_get_slave_ctrldata(
				काष्ठा spi_device *spi)
अणु
	काष्ठा s3c64xx_spi_csinfo *cs;
	काष्ठा device_node *slave_np, *data_np = शून्य;
	u32 fb_delay = 0;

	slave_np = spi->dev.of_node;
	अगर (!slave_np) अणु
		dev_err(&spi->dev, "device node not found\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	data_np = of_get_child_by_name(slave_np, "controller-data");
	अगर (!data_np) अणु
		dev_err(&spi->dev, "child node 'controller-data' not found\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	cs = kzalloc(माप(*cs), GFP_KERNEL);
	अगर (!cs) अणु
		of_node_put(data_np);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	of_property_पढ़ो_u32(data_np, "samsung,spi-feedback-delay", &fb_delay);
	cs->fb_delay = fb_delay;
	of_node_put(data_np);
	वापस cs;
पूर्ण

/*
 * Here we only check the validity of requested configuration
 * and save the configuration in a local data-काष्ठाure.
 * The controller is actually configured only just beक्रमe we
 * get a message to transfer.
 */
अटल पूर्णांक s3c64xx_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा s3c64xx_spi_csinfo *cs = spi->controller_data;
	काष्ठा s3c64xx_spi_driver_data *sdd;
	पूर्णांक err;

	sdd = spi_master_get_devdata(spi->master);
	अगर (spi->dev.of_node) अणु
		cs = s3c64xx_get_slave_ctrldata(spi);
		spi->controller_data = cs;
	पूर्ण अन्यथा अगर (cs) अणु
		/* On non-DT platक्रमms the SPI core will set spi->cs_gpio
		 * to -ENOENT. The GPIO pin used to drive the chip select
		 * is defined by using platक्रमm data so spi->cs_gpio value
		 * has to be override to have the proper GPIO pin number.
		 */
		spi->cs_gpio = cs->line;
	पूर्ण

	अगर (IS_ERR_OR_शून्य(cs)) अणु
		dev_err(&spi->dev, "No CS for SPI(%d)\n", spi->chip_select);
		वापस -ENODEV;
	पूर्ण

	अगर (!spi_get_ctldata(spi)) अणु
		अगर (gpio_is_valid(spi->cs_gpio)) अणु
			err = gpio_request_one(spi->cs_gpio, GPIOF_OUT_INIT_HIGH,
					       dev_name(&spi->dev));
			अगर (err) अणु
				dev_err(&spi->dev,
					"Failed to get /CS gpio [%d]: %d\n",
					spi->cs_gpio, err);
				जाओ err_gpio_req;
			पूर्ण
		पूर्ण

		spi_set_ctldata(spi, cs);
	पूर्ण

	pm_runसमय_get_sync(&sdd->pdev->dev);

	/* Check अगर we can provide the requested rate */
	अगर (!sdd->port_conf->clk_from_cmu) अणु
		u32 psr, speed;

		/* Max possible */
		speed = clk_get_rate(sdd->src_clk) / 2 / (0 + 1);

		अगर (spi->max_speed_hz > speed)
			spi->max_speed_hz = speed;

		psr = clk_get_rate(sdd->src_clk) / 2 / spi->max_speed_hz - 1;
		psr &= S3C64XX_SPI_PSR_MASK;
		अगर (psr == S3C64XX_SPI_PSR_MASK)
			psr--;

		speed = clk_get_rate(sdd->src_clk) / 2 / (psr + 1);
		अगर (spi->max_speed_hz < speed) अणु
			अगर (psr+1 < S3C64XX_SPI_PSR_MASK) अणु
				psr++;
			पूर्ण अन्यथा अणु
				err = -EINVAL;
				जाओ setup_निकास;
			पूर्ण
		पूर्ण

		speed = clk_get_rate(sdd->src_clk) / 2 / (psr + 1);
		अगर (spi->max_speed_hz >= speed) अणु
			spi->max_speed_hz = speed;
		पूर्ण अन्यथा अणु
			dev_err(&spi->dev, "Can't set %dHz transfer speed\n",
				spi->max_speed_hz);
			err = -EINVAL;
			जाओ setup_निकास;
		पूर्ण
	पूर्ण

	pm_runसमय_mark_last_busy(&sdd->pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&sdd->pdev->dev);
	s3c64xx_spi_set_cs(spi, false);

	वापस 0;

setup_निकास:
	pm_runसमय_mark_last_busy(&sdd->pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&sdd->pdev->dev);
	/* setup() वापसs with device de-selected */
	s3c64xx_spi_set_cs(spi, false);

	अगर (gpio_is_valid(spi->cs_gpio))
		gpio_मुक्त(spi->cs_gpio);
	spi_set_ctldata(spi, शून्य);

err_gpio_req:
	अगर (spi->dev.of_node)
		kमुक्त(cs);

	वापस err;
पूर्ण

अटल व्योम s3c64xx_spi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा s3c64xx_spi_csinfo *cs = spi_get_ctldata(spi);

	अगर (gpio_is_valid(spi->cs_gpio)) अणु
		gpio_मुक्त(spi->cs_gpio);
		अगर (spi->dev.of_node)
			kमुक्त(cs);
		अन्यथा अणु
			/* On non-DT platक्रमms, the SPI core sets
			 * spi->cs_gpio to -ENOENT and .setup()
			 * overrides it with the GPIO pin value
			 * passed using platक्रमm data.
			 */
			spi->cs_gpio = -ENOENT;
		पूर्ण
	पूर्ण

	spi_set_ctldata(spi, शून्य);
पूर्ण

अटल irqवापस_t s3c64xx_spi_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा s3c64xx_spi_driver_data *sdd = data;
	काष्ठा spi_master *spi = sdd->master;
	अचिन्हित पूर्णांक val, clr = 0;

	val = पढ़ोl(sdd->regs + S3C64XX_SPI_STATUS);

	अगर (val & S3C64XX_SPI_ST_RX_OVERRUN_ERR) अणु
		clr = S3C64XX_SPI_PND_RX_OVERRUN_CLR;
		dev_err(&spi->dev, "RX overrun\n");
	पूर्ण
	अगर (val & S3C64XX_SPI_ST_RX_UNDERRUN_ERR) अणु
		clr |= S3C64XX_SPI_PND_RX_UNDERRUN_CLR;
		dev_err(&spi->dev, "RX underrun\n");
	पूर्ण
	अगर (val & S3C64XX_SPI_ST_TX_OVERRUN_ERR) अणु
		clr |= S3C64XX_SPI_PND_TX_OVERRUN_CLR;
		dev_err(&spi->dev, "TX overrun\n");
	पूर्ण
	अगर (val & S3C64XX_SPI_ST_TX_UNDERRUN_ERR) अणु
		clr |= S3C64XX_SPI_PND_TX_UNDERRUN_CLR;
		dev_err(&spi->dev, "TX underrun\n");
	पूर्ण

	/* Clear the pending irq by setting and then clearing it */
	ग_लिखोl(clr, sdd->regs + S3C64XX_SPI_PENDING_CLR);
	ग_लिखोl(0, sdd->regs + S3C64XX_SPI_PENDING_CLR);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम s3c64xx_spi_hwinit(काष्ठा s3c64xx_spi_driver_data *sdd)
अणु
	काष्ठा s3c64xx_spi_info *sci = sdd->cntrlr_info;
	व्योम __iomem *regs = sdd->regs;
	अचिन्हित पूर्णांक val;

	sdd->cur_speed = 0;

	अगर (sci->no_cs)
		ग_लिखोl(0, sdd->regs + S3C64XX_SPI_CS_REG);
	अन्यथा अगर (!(sdd->port_conf->quirks & S3C64XX_SPI_QUIRK_CS_AUTO))
		ग_लिखोl(S3C64XX_SPI_CS_SIG_INACT, sdd->regs + S3C64XX_SPI_CS_REG);

	/* Disable Interrupts - we use Polling अगर not DMA mode */
	ग_लिखोl(0, regs + S3C64XX_SPI_INT_EN);

	अगर (!sdd->port_conf->clk_from_cmu)
		ग_लिखोl(sci->src_clk_nr << S3C64XX_SPI_CLKSEL_SRCSHFT,
				regs + S3C64XX_SPI_CLK_CFG);
	ग_लिखोl(0, regs + S3C64XX_SPI_MODE_CFG);
	ग_लिखोl(0, regs + S3C64XX_SPI_PACKET_CNT);

	/* Clear any irq pending bits, should set and clear the bits */
	val = S3C64XX_SPI_PND_RX_OVERRUN_CLR |
		S3C64XX_SPI_PND_RX_UNDERRUN_CLR |
		S3C64XX_SPI_PND_TX_OVERRUN_CLR |
		S3C64XX_SPI_PND_TX_UNDERRUN_CLR;
	ग_लिखोl(val, regs + S3C64XX_SPI_PENDING_CLR);
	ग_लिखोl(0, regs + S3C64XX_SPI_PENDING_CLR);

	ग_लिखोl(0, regs + S3C64XX_SPI_SWAP_CFG);

	val = पढ़ोl(regs + S3C64XX_SPI_MODE_CFG);
	val &= ~S3C64XX_SPI_MODE_4BURST;
	val &= ~(S3C64XX_SPI_MAX_TRAILCNT << S3C64XX_SPI_TRAILCNT_OFF);
	val |= (S3C64XX_SPI_TRAILCNT << S3C64XX_SPI_TRAILCNT_OFF);
	ग_लिखोl(val, regs + S3C64XX_SPI_MODE_CFG);

	s3c64xx_flush_fअगरo(sdd);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा s3c64xx_spi_info *s3c64xx_spi_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा s3c64xx_spi_info *sci;
	u32 temp;

	sci = devm_kzalloc(dev, माप(*sci), GFP_KERNEL);
	अगर (!sci)
		वापस ERR_PTR(-ENOMEM);

	अगर (of_property_पढ़ो_u32(dev->of_node, "samsung,spi-src-clk", &temp)) अणु
		dev_warn(dev, "spi bus clock parent not specified, using clock at index 0 as parent\n");
		sci->src_clk_nr = 0;
	पूर्ण अन्यथा अणु
		sci->src_clk_nr = temp;
	पूर्ण

	अगर (of_property_पढ़ो_u32(dev->of_node, "num-cs", &temp)) अणु
		dev_warn(dev, "number of chip select lines not specified, assuming 1 chip select line\n");
		sci->num_cs = 1;
	पूर्ण अन्यथा अणु
		sci->num_cs = temp;
	पूर्ण

	sci->no_cs = of_property_पढ़ो_bool(dev->of_node, "no-cs-readback");

	वापस sci;
पूर्ण
#अन्यथा
अटल काष्ठा s3c64xx_spi_info *s3c64xx_spi_parse_dt(काष्ठा device *dev)
अणु
	वापस dev_get_platdata(dev);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत स्थिर काष्ठा s3c64xx_spi_port_config *s3c64xx_spi_get_port_config(
						काष्ठा platक्रमm_device *pdev)
अणु
#अगर_घोषित CONFIG_OF
	अगर (pdev->dev.of_node)
		वापस of_device_get_match_data(&pdev->dev);
#पूर्ण_अगर
	वापस (स्थिर काष्ठा s3c64xx_spi_port_config *)platक्रमm_get_device_id(pdev)->driver_data;
पूर्ण

अटल पूर्णांक s3c64xx_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource	*mem_res;
	काष्ठा s3c64xx_spi_driver_data *sdd;
	काष्ठा s3c64xx_spi_info *sci = dev_get_platdata(&pdev->dev);
	काष्ठा spi_master *master;
	पूर्णांक ret, irq;
	अक्षर clk_name[16];

	अगर (!sci && pdev->dev.of_node) अणु
		sci = s3c64xx_spi_parse_dt(&pdev->dev);
		अगर (IS_ERR(sci))
			वापस PTR_ERR(sci);
	पूर्ण

	अगर (!sci) अणु
		dev_err(&pdev->dev, "platform_data missing!\n");
		वापस -ENODEV;
	पूर्ण

	mem_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (mem_res == शून्य) अणु
		dev_err(&pdev->dev, "Unable to get SPI MEM resource\n");
		वापस -ENXIO;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_warn(&pdev->dev, "Failed to get IRQ: %d\n", irq);
		वापस irq;
	पूर्ण

	master = spi_alloc_master(&pdev->dev,
				माप(काष्ठा s3c64xx_spi_driver_data));
	अगर (master == शून्य) अणु
		dev_err(&pdev->dev, "Unable to allocate SPI Master\n");
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, master);

	sdd = spi_master_get_devdata(master);
	sdd->port_conf = s3c64xx_spi_get_port_config(pdev);
	sdd->master = master;
	sdd->cntrlr_info = sci;
	sdd->pdev = pdev;
	sdd->sfr_start = mem_res->start;
	अगर (pdev->dev.of_node) अणु
		ret = of_alias_get_id(pdev->dev.of_node, "spi");
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to get alias id, errno %d\n",
				ret);
			जाओ err_deref_master;
		पूर्ण
		sdd->port_id = ret;
	पूर्ण अन्यथा अणु
		sdd->port_id = pdev->id;
	पूर्ण

	sdd->cur_bpw = 8;

	sdd->tx_dma.direction = DMA_MEM_TO_DEV;
	sdd->rx_dma.direction = DMA_DEV_TO_MEM;

	master->dev.of_node = pdev->dev.of_node;
	master->bus_num = sdd->port_id;
	master->setup = s3c64xx_spi_setup;
	master->cleanup = s3c64xx_spi_cleanup;
	master->prepare_transfer_hardware = s3c64xx_spi_prepare_transfer;
	master->prepare_message = s3c64xx_spi_prepare_message;
	master->transfer_one = s3c64xx_spi_transfer_one;
	master->num_chipselect = sci->num_cs;
	master->dma_alignment = 8;
	master->bits_per_word_mask = SPI_BPW_MASK(32) | SPI_BPW_MASK(16) |
					SPI_BPW_MASK(8);
	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->स्वतः_runसमय_pm = true;
	अगर (!is_polling(sdd))
		master->can_dma = s3c64xx_spi_can_dma;

	sdd->regs = devm_ioremap_resource(&pdev->dev, mem_res);
	अगर (IS_ERR(sdd->regs)) अणु
		ret = PTR_ERR(sdd->regs);
		जाओ err_deref_master;
	पूर्ण

	अगर (sci->cfg_gpio && sci->cfg_gpio()) अणु
		dev_err(&pdev->dev, "Unable to config gpio\n");
		ret = -EBUSY;
		जाओ err_deref_master;
	पूर्ण

	/* Setup घड़ीs */
	sdd->clk = devm_clk_get(&pdev->dev, "spi");
	अगर (IS_ERR(sdd->clk)) अणु
		dev_err(&pdev->dev, "Unable to acquire clock 'spi'\n");
		ret = PTR_ERR(sdd->clk);
		जाओ err_deref_master;
	पूर्ण

	ret = clk_prepare_enable(sdd->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't enable clock 'spi'\n");
		जाओ err_deref_master;
	पूर्ण

	प्र_लिखो(clk_name, "spi_busclk%d", sci->src_clk_nr);
	sdd->src_clk = devm_clk_get(&pdev->dev, clk_name);
	अगर (IS_ERR(sdd->src_clk)) अणु
		dev_err(&pdev->dev,
			"Unable to acquire clock '%s'\n", clk_name);
		ret = PTR_ERR(sdd->src_clk);
		जाओ err_disable_clk;
	पूर्ण

	ret = clk_prepare_enable(sdd->src_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't enable clock '%s'\n", clk_name);
		जाओ err_disable_clk;
	पूर्ण

	अगर (sdd->port_conf->clk_ioclk) अणु
		sdd->ioclk = devm_clk_get(&pdev->dev, "spi_ioclk");
		अगर (IS_ERR(sdd->ioclk)) अणु
			dev_err(&pdev->dev, "Unable to acquire 'ioclk'\n");
			ret = PTR_ERR(sdd->ioclk);
			जाओ err_disable_src_clk;
		पूर्ण

		ret = clk_prepare_enable(sdd->ioclk);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Couldn't enable clock 'ioclk'\n");
			जाओ err_disable_src_clk;
		पूर्ण
	पूर्ण

	अगर (!is_polling(sdd)) अणु
		/* Acquire DMA channels */
		sdd->rx_dma.ch = dma_request_chan(&pdev->dev, "rx");
		अगर (IS_ERR(sdd->rx_dma.ch)) अणु
			dev_err(&pdev->dev, "Failed to get RX DMA channel\n");
			ret = PTR_ERR(sdd->rx_dma.ch);
			जाओ err_disable_io_clk;
		पूर्ण
		sdd->tx_dma.ch = dma_request_chan(&pdev->dev, "tx");
		अगर (IS_ERR(sdd->tx_dma.ch)) अणु
			dev_err(&pdev->dev, "Failed to get TX DMA channel\n");
			ret = PTR_ERR(sdd->tx_dma.ch);
			जाओ err_release_rx_dma;
		पूर्ण
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, AUTOSUSPEND_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	/* Setup Deufult Mode */
	s3c64xx_spi_hwinit(sdd);

	spin_lock_init(&sdd->lock);
	init_completion(&sdd->xfer_completion);

	ret = devm_request_irq(&pdev->dev, irq, s3c64xx_spi_irq, 0,
				"spi-s3c64xx", sdd);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request IRQ %d: %d\n",
			irq, ret);
		जाओ err_pm_put;
	पूर्ण

	ग_लिखोl(S3C64XX_SPI_INT_RX_OVERRUN_EN | S3C64XX_SPI_INT_RX_UNDERRUN_EN |
	       S3C64XX_SPI_INT_TX_OVERRUN_EN | S3C64XX_SPI_INT_TX_UNDERRUN_EN,
	       sdd->regs + S3C64XX_SPI_INT_EN);

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "cannot register SPI master: %d\n", ret);
		जाओ err_pm_put;
	पूर्ण

	dev_dbg(&pdev->dev, "Samsung SoC SPI Driver loaded for Bus SPI-%d with %d Slaves attached\n",
					sdd->port_id, master->num_chipselect);
	dev_dbg(&pdev->dev, "\tIOmem=[%pR]\tFIFO %dbytes\n",
					mem_res, (FIFO_LVL_MASK(sdd) >> 1) + 1);

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस 0;

err_pm_put:
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);

	अगर (!is_polling(sdd))
		dma_release_channel(sdd->tx_dma.ch);
err_release_rx_dma:
	अगर (!is_polling(sdd))
		dma_release_channel(sdd->rx_dma.ch);
err_disable_io_clk:
	clk_disable_unprepare(sdd->ioclk);
err_disable_src_clk:
	clk_disable_unprepare(sdd->src_clk);
err_disable_clk:
	clk_disable_unprepare(sdd->clk);
err_deref_master:
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल पूर्णांक s3c64xx_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा s3c64xx_spi_driver_data *sdd = spi_master_get_devdata(master);

	pm_runसमय_get_sync(&pdev->dev);

	ग_लिखोl(0, sdd->regs + S3C64XX_SPI_INT_EN);

	अगर (!is_polling(sdd)) अणु
		dma_release_channel(sdd->rx_dma.ch);
		dma_release_channel(sdd->tx_dma.ch);
	पूर्ण

	clk_disable_unprepare(sdd->ioclk);

	clk_disable_unprepare(sdd->src_clk);

	clk_disable_unprepare(sdd->clk);

	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक s3c64xx_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा s3c64xx_spi_driver_data *sdd = spi_master_get_devdata(master);

	पूर्णांक ret = spi_master_suspend(master);
	अगर (ret)
		वापस ret;

	ret = pm_runसमय_क्रमce_suspend(dev);
	अगर (ret < 0)
		वापस ret;

	sdd->cur_speed = 0; /* Output Clock is stopped */

	वापस 0;
पूर्ण

अटल पूर्णांक s3c64xx_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा s3c64xx_spi_driver_data *sdd = spi_master_get_devdata(master);
	काष्ठा s3c64xx_spi_info *sci = sdd->cntrlr_info;
	पूर्णांक ret;

	अगर (sci->cfg_gpio)
		sci->cfg_gpio();

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret < 0)
		वापस ret;

	वापस spi_master_resume(master);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक s3c64xx_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा s3c64xx_spi_driver_data *sdd = spi_master_get_devdata(master);

	clk_disable_unprepare(sdd->clk);
	clk_disable_unprepare(sdd->src_clk);
	clk_disable_unprepare(sdd->ioclk);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c64xx_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा s3c64xx_spi_driver_data *sdd = spi_master_get_devdata(master);
	पूर्णांक ret;

	अगर (sdd->port_conf->clk_ioclk) अणु
		ret = clk_prepare_enable(sdd->ioclk);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	ret = clk_prepare_enable(sdd->src_clk);
	अगर (ret != 0)
		जाओ err_disable_ioclk;

	ret = clk_prepare_enable(sdd->clk);
	अगर (ret != 0)
		जाओ err_disable_src_clk;

	s3c64xx_spi_hwinit(sdd);

	ग_लिखोl(S3C64XX_SPI_INT_RX_OVERRUN_EN | S3C64XX_SPI_INT_RX_UNDERRUN_EN |
	       S3C64XX_SPI_INT_TX_OVERRUN_EN | S3C64XX_SPI_INT_TX_UNDERRUN_EN,
	       sdd->regs + S3C64XX_SPI_INT_EN);

	वापस 0;

err_disable_src_clk:
	clk_disable_unprepare(sdd->src_clk);
err_disable_ioclk:
	clk_disable_unprepare(sdd->ioclk);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops s3c64xx_spi_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(s3c64xx_spi_suspend, s3c64xx_spi_resume)
	SET_RUNTIME_PM_OPS(s3c64xx_spi_runसमय_suspend,
			   s3c64xx_spi_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा s3c64xx_spi_port_config s3c2443_spi_port_config = अणु
	.fअगरo_lvl_mask	= अणु 0x7f पूर्ण,
	.rx_lvl_offset	= 13,
	.tx_st_करोne	= 21,
	.high_speed	= true,
पूर्ण;

अटल स्थिर काष्ठा s3c64xx_spi_port_config s3c6410_spi_port_config = अणु
	.fअगरo_lvl_mask	= अणु 0x7f, 0x7F पूर्ण,
	.rx_lvl_offset	= 13,
	.tx_st_करोne	= 21,
पूर्ण;

अटल स्थिर काष्ठा s3c64xx_spi_port_config s5pv210_spi_port_config = अणु
	.fअगरo_lvl_mask	= अणु 0x1ff, 0x7F पूर्ण,
	.rx_lvl_offset	= 15,
	.tx_st_करोne	= 25,
	.high_speed	= true,
पूर्ण;

अटल स्थिर काष्ठा s3c64xx_spi_port_config exynos4_spi_port_config = अणु
	.fअगरo_lvl_mask	= अणु 0x1ff, 0x7F, 0x7F पूर्ण,
	.rx_lvl_offset	= 15,
	.tx_st_करोne	= 25,
	.high_speed	= true,
	.clk_from_cmu	= true,
	.quirks		= S3C64XX_SPI_QUIRK_CS_AUTO,
पूर्ण;

अटल स्थिर काष्ठा s3c64xx_spi_port_config exynos7_spi_port_config = अणु
	.fअगरo_lvl_mask	= अणु 0x1ff, 0x7F, 0x7F, 0x7F, 0x7F, 0x1ffपूर्ण,
	.rx_lvl_offset	= 15,
	.tx_st_करोne	= 25,
	.high_speed	= true,
	.clk_from_cmu	= true,
	.quirks		= S3C64XX_SPI_QUIRK_CS_AUTO,
पूर्ण;

अटल स्थिर काष्ठा s3c64xx_spi_port_config exynos5433_spi_port_config = अणु
	.fअगरo_lvl_mask	= अणु 0x1ff, 0x7f, 0x7f, 0x7f, 0x7f, 0x1ffपूर्ण,
	.rx_lvl_offset	= 15,
	.tx_st_करोne	= 25,
	.high_speed	= true,
	.clk_from_cmu	= true,
	.clk_ioclk	= true,
	.quirks		= S3C64XX_SPI_QUIRK_CS_AUTO,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id s3c64xx_spi_driver_ids[] = अणु
	अणु
		.name		= "s3c2443-spi",
		.driver_data	= (kernel_uदीर्घ_t)&s3c2443_spi_port_config,
	पूर्ण, अणु
		.name		= "s3c6410-spi",
		.driver_data	= (kernel_uदीर्घ_t)&s3c6410_spi_port_config,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id s3c64xx_spi_dt_match[] = अणु
	अणु .compatible = "samsung,s3c2443-spi",
			.data = (व्योम *)&s3c2443_spi_port_config,
	पूर्ण,
	अणु .compatible = "samsung,s3c6410-spi",
			.data = (व्योम *)&s3c6410_spi_port_config,
	पूर्ण,
	अणु .compatible = "samsung,s5pv210-spi",
			.data = (व्योम *)&s5pv210_spi_port_config,
	पूर्ण,
	अणु .compatible = "samsung,exynos4210-spi",
			.data = (व्योम *)&exynos4_spi_port_config,
	पूर्ण,
	अणु .compatible = "samsung,exynos7-spi",
			.data = (व्योम *)&exynos7_spi_port_config,
	पूर्ण,
	अणु .compatible = "samsung,exynos5433-spi",
			.data = (व्योम *)&exynos5433_spi_port_config,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s3c64xx_spi_dt_match);

अटल काष्ठा platक्रमm_driver s3c64xx_spi_driver = अणु
	.driver = अणु
		.name	= "s3c64xx-spi",
		.pm = &s3c64xx_spi_pm,
		.of_match_table = of_match_ptr(s3c64xx_spi_dt_match),
	पूर्ण,
	.probe = s3c64xx_spi_probe,
	.हटाओ = s3c64xx_spi_हटाओ,
	.id_table = s3c64xx_spi_driver_ids,
पूर्ण;
MODULE_ALIAS("platform:s3c64xx-spi");

module_platक्रमm_driver(s3c64xx_spi_driver);

MODULE_AUTHOR("Jaswinder Singh <jassi.brar@samsung.com>");
MODULE_DESCRIPTION("S3C64XX SPI Controller Driver");
MODULE_LICENSE("GPL");
