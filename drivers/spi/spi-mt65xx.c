<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 * Author: Leilk Liu <leilk.liu@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/spi-mt65xx.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/dma-mapping.h>

#घोषणा SPI_CFG0_REG                      0x0000
#घोषणा SPI_CFG1_REG                      0x0004
#घोषणा SPI_TX_SRC_REG                    0x0008
#घोषणा SPI_RX_DST_REG                    0x000c
#घोषणा SPI_TX_DATA_REG                   0x0010
#घोषणा SPI_RX_DATA_REG                   0x0014
#घोषणा SPI_CMD_REG                       0x0018
#घोषणा SPI_STATUS0_REG                   0x001c
#घोषणा SPI_PAD_SEL_REG                   0x0024
#घोषणा SPI_CFG2_REG                      0x0028
#घोषणा SPI_TX_SRC_REG_64                 0x002c
#घोषणा SPI_RX_DST_REG_64                 0x0030

#घोषणा SPI_CFG0_SCK_HIGH_OFFSET          0
#घोषणा SPI_CFG0_SCK_LOW_OFFSET           8
#घोषणा SPI_CFG0_CS_HOLD_OFFSET           16
#घोषणा SPI_CFG0_CS_SETUP_OFFSET          24
#घोषणा SPI_ADJUST_CFG0_CS_HOLD_OFFSET    0
#घोषणा SPI_ADJUST_CFG0_CS_SETUP_OFFSET   16

#घोषणा SPI_CFG1_CS_IDLE_OFFSET           0
#घोषणा SPI_CFG1_PACKET_LOOP_OFFSET       8
#घोषणा SPI_CFG1_PACKET_LENGTH_OFFSET     16
#घोषणा SPI_CFG1_GET_TICK_DLY_OFFSET      30

#घोषणा SPI_CFG1_CS_IDLE_MASK             0xff
#घोषणा SPI_CFG1_PACKET_LOOP_MASK         0xff00
#घोषणा SPI_CFG1_PACKET_LENGTH_MASK       0x3ff0000
#घोषणा SPI_CFG2_SCK_HIGH_OFFSET          0
#घोषणा SPI_CFG2_SCK_LOW_OFFSET           16

#घोषणा SPI_CMD_ACT                  BIT(0)
#घोषणा SPI_CMD_RESUME               BIT(1)
#घोषणा SPI_CMD_RST                  BIT(2)
#घोषणा SPI_CMD_PAUSE_EN             BIT(4)
#घोषणा SPI_CMD_DEASSERT             BIT(5)
#घोषणा SPI_CMD_SAMPLE_SEL           BIT(6)
#घोषणा SPI_CMD_CS_POL               BIT(7)
#घोषणा SPI_CMD_CPHA                 BIT(8)
#घोषणा SPI_CMD_CPOL                 BIT(9)
#घोषणा SPI_CMD_RX_DMA               BIT(10)
#घोषणा SPI_CMD_TX_DMA               BIT(11)
#घोषणा SPI_CMD_TXMSBF               BIT(12)
#घोषणा SPI_CMD_RXMSBF               BIT(13)
#घोषणा SPI_CMD_RX_ENDIAN            BIT(14)
#घोषणा SPI_CMD_TX_ENDIAN            BIT(15)
#घोषणा SPI_CMD_FINISH_IE            BIT(16)
#घोषणा SPI_CMD_PAUSE_IE             BIT(17)

#घोषणा MT8173_SPI_MAX_PAD_SEL 3

#घोषणा MTK_SPI_PAUSE_INT_STATUS 0x2

#घोषणा MTK_SPI_IDLE 0
#घोषणा MTK_SPI_PAUSED 1

#घोषणा MTK_SPI_MAX_FIFO_SIZE 32U
#घोषणा MTK_SPI_PACKET_SIZE 1024
#घोषणा MTK_SPI_32BITS_MASK  (0xffffffff)

#घोषणा DMA_ADDR_EXT_BITS (36)
#घोषणा DMA_ADDR_DEF_BITS (32)

काष्ठा mtk_spi_compatible अणु
	bool need_pad_sel;
	/* Must explicitly send dummy Tx bytes to करो Rx only transfer */
	bool must_tx;
	/* some IC design adjust cfg रेजिस्टर to enhance समय accuracy */
	bool enhance_timing;
	/* some IC support DMA addr extension */
	bool dma_ext;
पूर्ण;

काष्ठा mtk_spi अणु
	व्योम __iomem *base;
	u32 state;
	पूर्णांक pad_num;
	u32 *pad_sel;
	काष्ठा clk *parent_clk, *sel_clk, *spi_clk;
	काष्ठा spi_transfer *cur_transfer;
	u32 xfer_len;
	u32 num_xfered;
	काष्ठा scatterlist *tx_sgl, *rx_sgl;
	u32 tx_sgl_len, rx_sgl_len;
	स्थिर काष्ठा mtk_spi_compatible *dev_comp;
पूर्ण;

अटल स्थिर काष्ठा mtk_spi_compatible mtk_common_compat;

अटल स्थिर काष्ठा mtk_spi_compatible mt2712_compat = अणु
	.must_tx = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_spi_compatible mt6765_compat = अणु
	.need_pad_sel = true,
	.must_tx = true,
	.enhance_timing = true,
	.dma_ext = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_spi_compatible mt7622_compat = अणु
	.must_tx = true,
	.enhance_timing = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_spi_compatible mt8173_compat = अणु
	.need_pad_sel = true,
	.must_tx = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_spi_compatible mt8183_compat = अणु
	.need_pad_sel = true,
	.must_tx = true,
	.enhance_timing = true,
पूर्ण;

/*
 * A piece of शेष chip info unless the platक्रमm
 * supplies it.
 */
अटल स्थिर काष्ठा mtk_chip_config mtk_शेष_chip_info = अणु
	.sample_sel = 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_spi_of_match[] = अणु
	अणु .compatible = "mediatek,mt2701-spi",
		.data = (व्योम *)&mtk_common_compat,
	पूर्ण,
	अणु .compatible = "mediatek,mt2712-spi",
		.data = (व्योम *)&mt2712_compat,
	पूर्ण,
	अणु .compatible = "mediatek,mt6589-spi",
		.data = (व्योम *)&mtk_common_compat,
	पूर्ण,
	अणु .compatible = "mediatek,mt6765-spi",
		.data = (व्योम *)&mt6765_compat,
	पूर्ण,
	अणु .compatible = "mediatek,mt7622-spi",
		.data = (व्योम *)&mt7622_compat,
	पूर्ण,
	अणु .compatible = "mediatek,mt7629-spi",
		.data = (व्योम *)&mt7622_compat,
	पूर्ण,
	अणु .compatible = "mediatek,mt8135-spi",
		.data = (व्योम *)&mtk_common_compat,
	पूर्ण,
	अणु .compatible = "mediatek,mt8173-spi",
		.data = (व्योम *)&mt8173_compat,
	पूर्ण,
	अणु .compatible = "mediatek,mt8183-spi",
		.data = (व्योम *)&mt8183_compat,
	पूर्ण,
	अणु .compatible = "mediatek,mt8192-spi",
		.data = (व्योम *)&mt6765_compat,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_spi_of_match);

अटल व्योम mtk_spi_reset(काष्ठा mtk_spi *mdata)
अणु
	u32 reg_val;

	/* set the software reset bit in SPI_CMD_REG. */
	reg_val = पढ़ोl(mdata->base + SPI_CMD_REG);
	reg_val |= SPI_CMD_RST;
	ग_लिखोl(reg_val, mdata->base + SPI_CMD_REG);

	reg_val = पढ़ोl(mdata->base + SPI_CMD_REG);
	reg_val &= ~SPI_CMD_RST;
	ग_लिखोl(reg_val, mdata->base + SPI_CMD_REG);
पूर्ण

अटल पूर्णांक mtk_spi_prepare_message(काष्ठा spi_master *master,
				   काष्ठा spi_message *msg)
अणु
	u16 cpha, cpol;
	u32 reg_val;
	काष्ठा spi_device *spi = msg->spi;
	काष्ठा mtk_chip_config *chip_config = spi->controller_data;
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);

	cpha = spi->mode & SPI_CPHA ? 1 : 0;
	cpol = spi->mode & SPI_CPOL ? 1 : 0;

	reg_val = पढ़ोl(mdata->base + SPI_CMD_REG);
	अगर (cpha)
		reg_val |= SPI_CMD_CPHA;
	अन्यथा
		reg_val &= ~SPI_CMD_CPHA;
	अगर (cpol)
		reg_val |= SPI_CMD_CPOL;
	अन्यथा
		reg_val &= ~SPI_CMD_CPOL;

	/* set the mlsbx and mlsbtx */
	अगर (spi->mode & SPI_LSB_FIRST) अणु
		reg_val &= ~SPI_CMD_TXMSBF;
		reg_val &= ~SPI_CMD_RXMSBF;
	पूर्ण अन्यथा अणु
		reg_val |= SPI_CMD_TXMSBF;
		reg_val |= SPI_CMD_RXMSBF;
	पूर्ण

	/* set the tx/rx endian */
#अगर_घोषित __LITTLE_ENDIAN
	reg_val &= ~SPI_CMD_TX_ENDIAN;
	reg_val &= ~SPI_CMD_RX_ENDIAN;
#अन्यथा
	reg_val |= SPI_CMD_TX_ENDIAN;
	reg_val |= SPI_CMD_RX_ENDIAN;
#पूर्ण_अगर

	अगर (mdata->dev_comp->enhance_timing) अणु
		/* set CS polarity */
		अगर (spi->mode & SPI_CS_HIGH)
			reg_val |= SPI_CMD_CS_POL;
		अन्यथा
			reg_val &= ~SPI_CMD_CS_POL;

		अगर (chip_config->sample_sel)
			reg_val |= SPI_CMD_SAMPLE_SEL;
		अन्यथा
			reg_val &= ~SPI_CMD_SAMPLE_SEL;
	पूर्ण

	/* set finish and छोड़ो पूर्णांकerrupt always enable */
	reg_val |= SPI_CMD_FINISH_IE | SPI_CMD_PAUSE_IE;

	/* disable dma mode */
	reg_val &= ~(SPI_CMD_TX_DMA | SPI_CMD_RX_DMA);

	/* disable deनिश्चित mode */
	reg_val &= ~SPI_CMD_DEASSERT;

	ग_लिखोl(reg_val, mdata->base + SPI_CMD_REG);

	/* pad select */
	अगर (mdata->dev_comp->need_pad_sel)
		ग_लिखोl(mdata->pad_sel[spi->chip_select],
		       mdata->base + SPI_PAD_SEL_REG);

	वापस 0;
पूर्ण

अटल व्योम mtk_spi_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	u32 reg_val;
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(spi->master);

	अगर (spi->mode & SPI_CS_HIGH)
		enable = !enable;

	reg_val = पढ़ोl(mdata->base + SPI_CMD_REG);
	अगर (!enable) अणु
		reg_val |= SPI_CMD_PAUSE_EN;
		ग_लिखोl(reg_val, mdata->base + SPI_CMD_REG);
	पूर्ण अन्यथा अणु
		reg_val &= ~SPI_CMD_PAUSE_EN;
		ग_लिखोl(reg_val, mdata->base + SPI_CMD_REG);
		mdata->state = MTK_SPI_IDLE;
		mtk_spi_reset(mdata);
	पूर्ण
पूर्ण

अटल व्योम mtk_spi_prepare_transfer(काष्ठा spi_master *master,
				     काष्ठा spi_transfer *xfer)
अणु
	u32 spi_clk_hz, भाग, sck_समय, reg_val;
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);

	spi_clk_hz = clk_get_rate(mdata->spi_clk);
	अगर (xfer->speed_hz < spi_clk_hz / 2)
		भाग = DIV_ROUND_UP(spi_clk_hz, xfer->speed_hz);
	अन्यथा
		भाग = 1;

	sck_समय = (भाग + 1) / 2;

	अगर (mdata->dev_comp->enhance_timing) अणु
		reg_val = पढ़ोl(mdata->base + SPI_CFG2_REG);
		reg_val &= ~(0xffff << SPI_CFG2_SCK_HIGH_OFFSET);
		reg_val |= (((sck_समय - 1) & 0xffff)
			   << SPI_CFG2_SCK_HIGH_OFFSET);
		reg_val &= ~(0xffff << SPI_CFG2_SCK_LOW_OFFSET);
		reg_val |= (((sck_समय - 1) & 0xffff)
			   << SPI_CFG2_SCK_LOW_OFFSET);
		ग_लिखोl(reg_val, mdata->base + SPI_CFG2_REG);
	पूर्ण अन्यथा अणु
		reg_val = पढ़ोl(mdata->base + SPI_CFG0_REG);
		reg_val &= ~(0xff << SPI_CFG0_SCK_HIGH_OFFSET);
		reg_val |= (((sck_समय - 1) & 0xff)
			   << SPI_CFG0_SCK_HIGH_OFFSET);
		reg_val &= ~(0xff << SPI_CFG0_SCK_LOW_OFFSET);
		reg_val |= (((sck_समय - 1) & 0xff) << SPI_CFG0_SCK_LOW_OFFSET);
		ग_लिखोl(reg_val, mdata->base + SPI_CFG0_REG);
	पूर्ण
पूर्ण

अटल व्योम mtk_spi_setup_packet(काष्ठा spi_master *master)
अणु
	u32 packet_size, packet_loop, reg_val;
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);

	packet_size = min_t(u32, mdata->xfer_len, MTK_SPI_PACKET_SIZE);
	packet_loop = mdata->xfer_len / packet_size;

	reg_val = पढ़ोl(mdata->base + SPI_CFG1_REG);
	reg_val &= ~(SPI_CFG1_PACKET_LENGTH_MASK | SPI_CFG1_PACKET_LOOP_MASK);
	reg_val |= (packet_size - 1) << SPI_CFG1_PACKET_LENGTH_OFFSET;
	reg_val |= (packet_loop - 1) << SPI_CFG1_PACKET_LOOP_OFFSET;
	ग_लिखोl(reg_val, mdata->base + SPI_CFG1_REG);
पूर्ण

अटल व्योम mtk_spi_enable_transfer(काष्ठा spi_master *master)
अणु
	u32 cmd;
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);

	cmd = पढ़ोl(mdata->base + SPI_CMD_REG);
	अगर (mdata->state == MTK_SPI_IDLE)
		cmd |= SPI_CMD_ACT;
	अन्यथा
		cmd |= SPI_CMD_RESUME;
	ग_लिखोl(cmd, mdata->base + SPI_CMD_REG);
पूर्ण

अटल पूर्णांक mtk_spi_get_mult_delta(u32 xfer_len)
अणु
	u32 mult_delta;

	अगर (xfer_len > MTK_SPI_PACKET_SIZE)
		mult_delta = xfer_len % MTK_SPI_PACKET_SIZE;
	अन्यथा
		mult_delta = 0;

	वापस mult_delta;
पूर्ण

अटल व्योम mtk_spi_update_mdata_len(काष्ठा spi_master *master)
अणु
	पूर्णांक mult_delta;
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);

	अगर (mdata->tx_sgl_len && mdata->rx_sgl_len) अणु
		अगर (mdata->tx_sgl_len > mdata->rx_sgl_len) अणु
			mult_delta = mtk_spi_get_mult_delta(mdata->rx_sgl_len);
			mdata->xfer_len = mdata->rx_sgl_len - mult_delta;
			mdata->rx_sgl_len = mult_delta;
			mdata->tx_sgl_len -= mdata->xfer_len;
		पूर्ण अन्यथा अणु
			mult_delta = mtk_spi_get_mult_delta(mdata->tx_sgl_len);
			mdata->xfer_len = mdata->tx_sgl_len - mult_delta;
			mdata->tx_sgl_len = mult_delta;
			mdata->rx_sgl_len -= mdata->xfer_len;
		पूर्ण
	पूर्ण अन्यथा अगर (mdata->tx_sgl_len) अणु
		mult_delta = mtk_spi_get_mult_delta(mdata->tx_sgl_len);
		mdata->xfer_len = mdata->tx_sgl_len - mult_delta;
		mdata->tx_sgl_len = mult_delta;
	पूर्ण अन्यथा अगर (mdata->rx_sgl_len) अणु
		mult_delta = mtk_spi_get_mult_delta(mdata->rx_sgl_len);
		mdata->xfer_len = mdata->rx_sgl_len - mult_delta;
		mdata->rx_sgl_len = mult_delta;
	पूर्ण
पूर्ण

अटल व्योम mtk_spi_setup_dma_addr(काष्ठा spi_master *master,
				   काष्ठा spi_transfer *xfer)
अणु
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);

	अगर (mdata->tx_sgl) अणु
		ग_लिखोl((u32)(xfer->tx_dma & MTK_SPI_32BITS_MASK),
		       mdata->base + SPI_TX_SRC_REG);
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
		अगर (mdata->dev_comp->dma_ext)
			ग_लिखोl((u32)(xfer->tx_dma >> 32),
			       mdata->base + SPI_TX_SRC_REG_64);
#पूर्ण_अगर
	पूर्ण

	अगर (mdata->rx_sgl) अणु
		ग_लिखोl((u32)(xfer->rx_dma & MTK_SPI_32BITS_MASK),
		       mdata->base + SPI_RX_DST_REG);
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
		अगर (mdata->dev_comp->dma_ext)
			ग_लिखोl((u32)(xfer->rx_dma >> 32),
			       mdata->base + SPI_RX_DST_REG_64);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_spi_fअगरo_transfer(काष्ठा spi_master *master,
				 काष्ठा spi_device *spi,
				 काष्ठा spi_transfer *xfer)
अणु
	पूर्णांक cnt, reमुख्यder;
	u32 reg_val;
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);

	mdata->cur_transfer = xfer;
	mdata->xfer_len = min(MTK_SPI_MAX_FIFO_SIZE, xfer->len);
	mdata->num_xfered = 0;
	mtk_spi_prepare_transfer(master, xfer);
	mtk_spi_setup_packet(master);

	cnt = xfer->len / 4;
	ioग_लिखो32_rep(mdata->base + SPI_TX_DATA_REG, xfer->tx_buf, cnt);

	reमुख्यder = xfer->len % 4;
	अगर (reमुख्यder > 0) अणु
		reg_val = 0;
		स_नकल(&reg_val, xfer->tx_buf + (cnt * 4), reमुख्यder);
		ग_लिखोl(reg_val, mdata->base + SPI_TX_DATA_REG);
	पूर्ण

	mtk_spi_enable_transfer(master);

	वापस 1;
पूर्ण

अटल पूर्णांक mtk_spi_dma_transfer(काष्ठा spi_master *master,
				काष्ठा spi_device *spi,
				काष्ठा spi_transfer *xfer)
अणु
	पूर्णांक cmd;
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);

	mdata->tx_sgl = शून्य;
	mdata->rx_sgl = शून्य;
	mdata->tx_sgl_len = 0;
	mdata->rx_sgl_len = 0;
	mdata->cur_transfer = xfer;
	mdata->num_xfered = 0;

	mtk_spi_prepare_transfer(master, xfer);

	cmd = पढ़ोl(mdata->base + SPI_CMD_REG);
	अगर (xfer->tx_buf)
		cmd |= SPI_CMD_TX_DMA;
	अगर (xfer->rx_buf)
		cmd |= SPI_CMD_RX_DMA;
	ग_लिखोl(cmd, mdata->base + SPI_CMD_REG);

	अगर (xfer->tx_buf)
		mdata->tx_sgl = xfer->tx_sg.sgl;
	अगर (xfer->rx_buf)
		mdata->rx_sgl = xfer->rx_sg.sgl;

	अगर (mdata->tx_sgl) अणु
		xfer->tx_dma = sg_dma_address(mdata->tx_sgl);
		mdata->tx_sgl_len = sg_dma_len(mdata->tx_sgl);
	पूर्ण
	अगर (mdata->rx_sgl) अणु
		xfer->rx_dma = sg_dma_address(mdata->rx_sgl);
		mdata->rx_sgl_len = sg_dma_len(mdata->rx_sgl);
	पूर्ण

	mtk_spi_update_mdata_len(master);
	mtk_spi_setup_packet(master);
	mtk_spi_setup_dma_addr(master, xfer);
	mtk_spi_enable_transfer(master);

	वापस 1;
पूर्ण

अटल पूर्णांक mtk_spi_transfer_one(काष्ठा spi_master *master,
				काष्ठा spi_device *spi,
				काष्ठा spi_transfer *xfer)
अणु
	अगर (master->can_dma(master, spi, xfer))
		वापस mtk_spi_dma_transfer(master, spi, xfer);
	अन्यथा
		वापस mtk_spi_fअगरo_transfer(master, spi, xfer);
पूर्ण

अटल bool mtk_spi_can_dma(काष्ठा spi_master *master,
			    काष्ठा spi_device *spi,
			    काष्ठा spi_transfer *xfer)
अणु
	/* Buffers क्रम DMA transactions must be 4-byte aligned */
	वापस (xfer->len > MTK_SPI_MAX_FIFO_SIZE &&
		(अचिन्हित दीर्घ)xfer->tx_buf % 4 == 0 &&
		(अचिन्हित दीर्घ)xfer->rx_buf % 4 == 0);
पूर्ण

अटल पूर्णांक mtk_spi_set_hw_cs_timing(काष्ठा spi_device *spi,
				    काष्ठा spi_delay *setup,
				    काष्ठा spi_delay *hold,
				    काष्ठा spi_delay *inactive)
अणु
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(spi->master);
	u16 setup_dly, hold_dly, inactive_dly;
	u32 reg_val;

	अगर ((setup && setup->unit != SPI_DELAY_UNIT_SCK) ||
	    (hold && hold->unit != SPI_DELAY_UNIT_SCK) ||
	    (inactive && inactive->unit != SPI_DELAY_UNIT_SCK)) अणु
		dev_err(&spi->dev,
			"Invalid delay unit, should be SPI_DELAY_UNIT_SCK\n");
		वापस -EINVAL;
	पूर्ण

	setup_dly = setup ? setup->value : 1;
	hold_dly = hold ? hold->value : 1;
	inactive_dly = inactive ? inactive->value : 1;

	reg_val = पढ़ोl(mdata->base + SPI_CFG0_REG);
	अगर (mdata->dev_comp->enhance_timing) अणु
		reg_val &= ~(0xffff << SPI_ADJUST_CFG0_CS_HOLD_OFFSET);
		reg_val |= (((hold_dly - 1) & 0xffff)
			   << SPI_ADJUST_CFG0_CS_HOLD_OFFSET);
		reg_val &= ~(0xffff << SPI_ADJUST_CFG0_CS_SETUP_OFFSET);
		reg_val |= (((setup_dly - 1) & 0xffff)
			   << SPI_ADJUST_CFG0_CS_SETUP_OFFSET);
	पूर्ण अन्यथा अणु
		reg_val &= ~(0xff << SPI_CFG0_CS_HOLD_OFFSET);
		reg_val |= (((hold_dly - 1) & 0xff) << SPI_CFG0_CS_HOLD_OFFSET);
		reg_val &= ~(0xff << SPI_CFG0_CS_SETUP_OFFSET);
		reg_val |= (((setup_dly - 1) & 0xff)
			    << SPI_CFG0_CS_SETUP_OFFSET);
	पूर्ण
	ग_लिखोl(reg_val, mdata->base + SPI_CFG0_REG);

	reg_val = पढ़ोl(mdata->base + SPI_CFG1_REG);
	reg_val &= ~SPI_CFG1_CS_IDLE_MASK;
	reg_val |= (((inactive_dly - 1) & 0xff) << SPI_CFG1_CS_IDLE_OFFSET);
	ग_लिखोl(reg_val, mdata->base + SPI_CFG1_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(spi->master);

	अगर (!spi->controller_data)
		spi->controller_data = (व्योम *)&mtk_शेष_chip_info;

	अगर (mdata->dev_comp->need_pad_sel && gpio_is_valid(spi->cs_gpio))
		gpio_direction_output(spi->cs_gpio, !(spi->mode & SPI_CS_HIGH));

	वापस 0;
पूर्ण

अटल irqवापस_t mtk_spi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 cmd, reg_val, cnt, reमुख्यder, len;
	काष्ठा spi_master *master = dev_id;
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);
	काष्ठा spi_transfer *trans = mdata->cur_transfer;

	reg_val = पढ़ोl(mdata->base + SPI_STATUS0_REG);
	अगर (reg_val & MTK_SPI_PAUSE_INT_STATUS)
		mdata->state = MTK_SPI_PAUSED;
	अन्यथा
		mdata->state = MTK_SPI_IDLE;

	अगर (!master->can_dma(master, master->cur_msg->spi, trans)) अणु
		अगर (trans->rx_buf) अणु
			cnt = mdata->xfer_len / 4;
			ioपढ़ो32_rep(mdata->base + SPI_RX_DATA_REG,
				     trans->rx_buf + mdata->num_xfered, cnt);
			reमुख्यder = mdata->xfer_len % 4;
			अगर (reमुख्यder > 0) अणु
				reg_val = पढ़ोl(mdata->base + SPI_RX_DATA_REG);
				स_नकल(trans->rx_buf +
					mdata->num_xfered +
					(cnt * 4),
					&reg_val,
					reमुख्यder);
			पूर्ण
		पूर्ण

		mdata->num_xfered += mdata->xfer_len;
		अगर (mdata->num_xfered == trans->len) अणु
			spi_finalize_current_transfer(master);
			वापस IRQ_HANDLED;
		पूर्ण

		len = trans->len - mdata->num_xfered;
		mdata->xfer_len = min(MTK_SPI_MAX_FIFO_SIZE, len);
		mtk_spi_setup_packet(master);

		cnt = mdata->xfer_len / 4;
		ioग_लिखो32_rep(mdata->base + SPI_TX_DATA_REG,
				trans->tx_buf + mdata->num_xfered, cnt);

		reमुख्यder = mdata->xfer_len % 4;
		अगर (reमुख्यder > 0) अणु
			reg_val = 0;
			स_नकल(&reg_val,
				trans->tx_buf + (cnt * 4) + mdata->num_xfered,
				reमुख्यder);
			ग_लिखोl(reg_val, mdata->base + SPI_TX_DATA_REG);
		पूर्ण

		mtk_spi_enable_transfer(master);

		वापस IRQ_HANDLED;
	पूर्ण

	अगर (mdata->tx_sgl)
		trans->tx_dma += mdata->xfer_len;
	अगर (mdata->rx_sgl)
		trans->rx_dma += mdata->xfer_len;

	अगर (mdata->tx_sgl && (mdata->tx_sgl_len == 0)) अणु
		mdata->tx_sgl = sg_next(mdata->tx_sgl);
		अगर (mdata->tx_sgl) अणु
			trans->tx_dma = sg_dma_address(mdata->tx_sgl);
			mdata->tx_sgl_len = sg_dma_len(mdata->tx_sgl);
		पूर्ण
	पूर्ण
	अगर (mdata->rx_sgl && (mdata->rx_sgl_len == 0)) अणु
		mdata->rx_sgl = sg_next(mdata->rx_sgl);
		अगर (mdata->rx_sgl) अणु
			trans->rx_dma = sg_dma_address(mdata->rx_sgl);
			mdata->rx_sgl_len = sg_dma_len(mdata->rx_sgl);
		पूर्ण
	पूर्ण

	अगर (!mdata->tx_sgl && !mdata->rx_sgl) अणु
		/* spi disable dma */
		cmd = पढ़ोl(mdata->base + SPI_CMD_REG);
		cmd &= ~SPI_CMD_TX_DMA;
		cmd &= ~SPI_CMD_RX_DMA;
		ग_लिखोl(cmd, mdata->base + SPI_CMD_REG);

		spi_finalize_current_transfer(master);
		वापस IRQ_HANDLED;
	पूर्ण

	mtk_spi_update_mdata_len(master);
	mtk_spi_setup_packet(master);
	mtk_spi_setup_dma_addr(master, trans);
	mtk_spi_enable_transfer(master);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mtk_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा mtk_spi *mdata;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक i, irq, ret, addr_bits;

	master = spi_alloc_master(&pdev->dev, माप(*mdata));
	अगर (!master) अणु
		dev_err(&pdev->dev, "failed to alloc spi master\n");
		वापस -ENOMEM;
	पूर्ण

	master->स्वतः_runसमय_pm = true;
	master->dev.of_node = pdev->dev.of_node;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST;

	master->set_cs = mtk_spi_set_cs;
	master->prepare_message = mtk_spi_prepare_message;
	master->transfer_one = mtk_spi_transfer_one;
	master->can_dma = mtk_spi_can_dma;
	master->setup = mtk_spi_setup;
	master->set_cs_timing = mtk_spi_set_hw_cs_timing;

	of_id = of_match_node(mtk_spi_of_match, pdev->dev.of_node);
	अगर (!of_id) अणु
		dev_err(&pdev->dev, "failed to probe of_node\n");
		ret = -EINVAL;
		जाओ err_put_master;
	पूर्ण

	mdata = spi_master_get_devdata(master);
	mdata->dev_comp = of_id->data;

	अगर (mdata->dev_comp->enhance_timing)
		master->mode_bits |= SPI_CS_HIGH;

	अगर (mdata->dev_comp->must_tx)
		master->flags = SPI_MASTER_MUST_TX;

	अगर (mdata->dev_comp->need_pad_sel) अणु
		mdata->pad_num = of_property_count_u32_elems(
			pdev->dev.of_node,
			"mediatek,pad-select");
		अगर (mdata->pad_num < 0) अणु
			dev_err(&pdev->dev,
				"No 'mediatek,pad-select' property\n");
			ret = -EINVAL;
			जाओ err_put_master;
		पूर्ण

		mdata->pad_sel = devm_kदो_स्मृति_array(&pdev->dev, mdata->pad_num,
						    माप(u32), GFP_KERNEL);
		अगर (!mdata->pad_sel) अणु
			ret = -ENOMEM;
			जाओ err_put_master;
		पूर्ण

		क्रम (i = 0; i < mdata->pad_num; i++) अणु
			of_property_पढ़ो_u32_index(pdev->dev.of_node,
						   "mediatek,pad-select",
						   i, &mdata->pad_sel[i]);
			अगर (mdata->pad_sel[i] > MT8173_SPI_MAX_PAD_SEL) अणु
				dev_err(&pdev->dev, "wrong pad-sel[%d]: %u\n",
					i, mdata->pad_sel[i]);
				ret = -EINVAL;
				जाओ err_put_master;
			पूर्ण
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, master);
	mdata->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mdata->base)) अणु
		ret = PTR_ERR(mdata->base);
		जाओ err_put_master;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err_put_master;
	पूर्ण

	अगर (!pdev->dev.dma_mask)
		pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;

	ret = devm_request_irq(&pdev->dev, irq, mtk_spi_पूर्णांकerrupt,
			       IRQF_TRIGGER_NONE, dev_name(&pdev->dev), master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register irq (%d)\n", ret);
		जाओ err_put_master;
	पूर्ण

	mdata->parent_clk = devm_clk_get(&pdev->dev, "parent-clk");
	अगर (IS_ERR(mdata->parent_clk)) अणु
		ret = PTR_ERR(mdata->parent_clk);
		dev_err(&pdev->dev, "failed to get parent-clk: %d\n", ret);
		जाओ err_put_master;
	पूर्ण

	mdata->sel_clk = devm_clk_get(&pdev->dev, "sel-clk");
	अगर (IS_ERR(mdata->sel_clk)) अणु
		ret = PTR_ERR(mdata->sel_clk);
		dev_err(&pdev->dev, "failed to get sel-clk: %d\n", ret);
		जाओ err_put_master;
	पूर्ण

	mdata->spi_clk = devm_clk_get(&pdev->dev, "spi-clk");
	अगर (IS_ERR(mdata->spi_clk)) अणु
		ret = PTR_ERR(mdata->spi_clk);
		dev_err(&pdev->dev, "failed to get spi-clk: %d\n", ret);
		जाओ err_put_master;
	पूर्ण

	ret = clk_prepare_enable(mdata->spi_clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to enable spi_clk (%d)\n", ret);
		जाओ err_put_master;
	पूर्ण

	ret = clk_set_parent(mdata->sel_clk, mdata->parent_clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to clk_set_parent (%d)\n", ret);
		clk_disable_unprepare(mdata->spi_clk);
		जाओ err_put_master;
	पूर्ण

	clk_disable_unprepare(mdata->spi_clk);

	pm_runसमय_enable(&pdev->dev);

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register master (%d)\n", ret);
		जाओ err_disable_runसमय_pm;
	पूर्ण

	अगर (mdata->dev_comp->need_pad_sel) अणु
		अगर (mdata->pad_num != master->num_chipselect) अणु
			dev_err(&pdev->dev,
				"pad_num does not match num_chipselect(%d != %d)\n",
				mdata->pad_num, master->num_chipselect);
			ret = -EINVAL;
			जाओ err_disable_runसमय_pm;
		पूर्ण

		अगर (!master->cs_gpios && master->num_chipselect > 1) अणु
			dev_err(&pdev->dev,
				"cs_gpios not specified and num_chipselect > 1\n");
			ret = -EINVAL;
			जाओ err_disable_runसमय_pm;
		पूर्ण

		अगर (master->cs_gpios) अणु
			क्रम (i = 0; i < master->num_chipselect; i++) अणु
				ret = devm_gpio_request(&pdev->dev,
							master->cs_gpios[i],
							dev_name(&pdev->dev));
				अगर (ret) अणु
					dev_err(&pdev->dev,
						"can't get CS GPIO %i\n", i);
					जाओ err_disable_runसमय_pm;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (mdata->dev_comp->dma_ext)
		addr_bits = DMA_ADDR_EXT_BITS;
	अन्यथा
		addr_bits = DMA_ADDR_DEF_BITS;
	ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(addr_bits));
	अगर (ret)
		dev_notice(&pdev->dev, "SPI dma_set_mask(%d) failed, ret:%d\n",
			   addr_bits, ret);

	वापस 0;

err_disable_runसमय_pm:
	pm_runसमय_disable(&pdev->dev);
err_put_master:
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);

	pm_runसमय_disable(&pdev->dev);

	mtk_spi_reset(mdata);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mtk_spi_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);

	ret = spi_master_suspend(master);
	अगर (ret)
		वापस ret;

	अगर (!pm_runसमय_suspended(dev))
		clk_disable_unprepare(mdata->spi_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_spi_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);

	अगर (!pm_runसमय_suspended(dev)) अणु
		ret = clk_prepare_enable(mdata->spi_clk);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to enable spi_clk (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = spi_master_resume(master);
	अगर (ret < 0)
		clk_disable_unprepare(mdata->spi_clk);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mtk_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);

	clk_disable_unprepare(mdata->spi_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mtk_spi *mdata = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(mdata->spi_clk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable spi_clk (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops mtk_spi_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mtk_spi_suspend, mtk_spi_resume)
	SET_RUNTIME_PM_OPS(mtk_spi_runसमय_suspend,
			   mtk_spi_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_spi_driver = अणु
	.driver = अणु
		.name = "mtk-spi",
		.pm	= &mtk_spi_pm,
		.of_match_table = mtk_spi_of_match,
	पूर्ण,
	.probe = mtk_spi_probe,
	.हटाओ = mtk_spi_हटाओ,
पूर्ण;

module_platक्रमm_driver(mtk_spi_driver);

MODULE_DESCRIPTION("MTK SPI Controller driver");
MODULE_AUTHOR("Leilk Liu <leilk.liu@mediatek.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:mtk-spi");
