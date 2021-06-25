<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2004-2007 Freescale Semiconductor, Inc. All Rights Reserved.
// Copyright (C) 2008 Juergen Beisert

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
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/types.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/property.h>

#समावेश <linux/platक्रमm_data/dma-imx.h>

#घोषणा DRIVER_NAME "spi_imx"

अटल bool use_dma = true;
module_param(use_dma, bool, 0644);
MODULE_PARM_DESC(use_dma, "Enable usage of DMA when available (default)");

#घोषणा MXC_RPM_TIMEOUT		2000 /* 2000ms */

#घोषणा MXC_CSPIRXDATA		0x00
#घोषणा MXC_CSPITXDATA		0x04
#घोषणा MXC_CSPICTRL		0x08
#घोषणा MXC_CSPIINT		0x0c
#घोषणा MXC_RESET		0x1c

/* generic defines to असलtract from the dअगरferent रेजिस्टर layouts */
#घोषणा MXC_INT_RR	(1 << 0) /* Receive data पढ़ोy पूर्णांकerrupt */
#घोषणा MXC_INT_TE	(1 << 1) /* Transmit FIFO empty पूर्णांकerrupt */
#घोषणा MXC_INT_RDR	BIT(4) /* Receive date threshold पूर्णांकerrupt */

/* The maximum bytes that a sdma BD can transfer. */
#घोषणा MAX_SDMA_BD_BYTES (1 << 15)
#घोषणा MX51_ECSPI_CTRL_MAX_BURST	512
/* The maximum bytes that IMX53_ECSPI can transfer in slave mode.*/
#घोषणा MX53_MAX_TRANSFER_BYTES		512

क्रमागत spi_imx_devtype अणु
	IMX1_CSPI,
	IMX21_CSPI,
	IMX27_CSPI,
	IMX31_CSPI,
	IMX35_CSPI,	/* CSPI on all i.mx except above */
	IMX51_ECSPI,	/* ECSPI on i.mx51 */
	IMX53_ECSPI,	/* ECSPI on i.mx53 and later */
पूर्ण;

काष्ठा spi_imx_data;

काष्ठा spi_imx_devtype_data अणु
	व्योम (*पूर्णांकctrl)(काष्ठा spi_imx_data *, पूर्णांक);
	पूर्णांक (*prepare_message)(काष्ठा spi_imx_data *, काष्ठा spi_message *);
	पूर्णांक (*prepare_transfer)(काष्ठा spi_imx_data *, काष्ठा spi_device *);
	व्योम (*trigger)(काष्ठा spi_imx_data *);
	पूर्णांक (*rx_available)(काष्ठा spi_imx_data *);
	व्योम (*reset)(काष्ठा spi_imx_data *);
	व्योम (*setup_wml)(काष्ठा spi_imx_data *);
	व्योम (*disable)(काष्ठा spi_imx_data *);
	व्योम (*disable_dma)(काष्ठा spi_imx_data *);
	bool has_dmamode;
	bool has_slavemode;
	अचिन्हित पूर्णांक fअगरo_size;
	bool dynamic_burst;
	क्रमागत spi_imx_devtype devtype;
पूर्ण;

काष्ठा spi_imx_data अणु
	काष्ठा spi_bitbang bitbang;
	काष्ठा device *dev;

	काष्ठा completion xfer_करोne;
	व्योम __iomem *base;
	अचिन्हित दीर्घ base_phys;

	काष्ठा clk *clk_per;
	काष्ठा clk *clk_ipg;
	अचिन्हित दीर्घ spi_clk;
	अचिन्हित पूर्णांक spi_bus_clk;

	अचिन्हित पूर्णांक bits_per_word;
	अचिन्हित पूर्णांक spi_drctl;

	अचिन्हित पूर्णांक count, reमुख्यder;
	व्योम (*tx)(काष्ठा spi_imx_data *);
	व्योम (*rx)(काष्ठा spi_imx_data *);
	व्योम *rx_buf;
	स्थिर व्योम *tx_buf;
	अचिन्हित पूर्णांक txfअगरo; /* number of words pushed in tx FIFO */
	अचिन्हित पूर्णांक dynamic_burst;

	/* Slave mode */
	bool slave_mode;
	bool slave_पातed;
	अचिन्हित पूर्णांक slave_burst;

	/* DMA */
	bool usedma;
	u32 wml;
	काष्ठा completion dma_rx_completion;
	काष्ठा completion dma_tx_completion;

	स्थिर काष्ठा spi_imx_devtype_data *devtype_data;
पूर्ण;

अटल अंतरभूत पूर्णांक is_imx27_cspi(काष्ठा spi_imx_data *d)
अणु
	वापस d->devtype_data->devtype == IMX27_CSPI;
पूर्ण

अटल अंतरभूत पूर्णांक is_imx35_cspi(काष्ठा spi_imx_data *d)
अणु
	वापस d->devtype_data->devtype == IMX35_CSPI;
पूर्ण

अटल अंतरभूत पूर्णांक is_imx51_ecspi(काष्ठा spi_imx_data *d)
अणु
	वापस d->devtype_data->devtype == IMX51_ECSPI;
पूर्ण

अटल अंतरभूत पूर्णांक is_imx53_ecspi(काष्ठा spi_imx_data *d)
अणु
	वापस d->devtype_data->devtype == IMX53_ECSPI;
पूर्ण

#घोषणा MXC_SPI_BUF_RX(type)						\
अटल व्योम spi_imx_buf_rx_##type(काष्ठा spi_imx_data *spi_imx)		\
अणु									\
	अचिन्हित पूर्णांक val = पढ़ोl(spi_imx->base + MXC_CSPIRXDATA);	\
									\
	अगर (spi_imx->rx_buf) अणु						\
		*(type *)spi_imx->rx_buf = val;				\
		spi_imx->rx_buf += माप(type);			\
	पूर्ण								\
									\
	spi_imx->reमुख्यder -= माप(type);				\
पूर्ण

#घोषणा MXC_SPI_BUF_TX(type)						\
अटल व्योम spi_imx_buf_tx_##type(काष्ठा spi_imx_data *spi_imx)		\
अणु									\
	type val = 0;							\
									\
	अगर (spi_imx->tx_buf) अणु						\
		val = *(type *)spi_imx->tx_buf;				\
		spi_imx->tx_buf += माप(type);			\
	पूर्ण								\
									\
	spi_imx->count -= माप(type);					\
									\
	ग_लिखोl(val, spi_imx->base + MXC_CSPITXDATA);			\
पूर्ण

MXC_SPI_BUF_RX(u8)
MXC_SPI_BUF_TX(u8)
MXC_SPI_BUF_RX(u16)
MXC_SPI_BUF_TX(u16)
MXC_SPI_BUF_RX(u32)
MXC_SPI_BUF_TX(u32)

/* First entry is reserved, second entry is valid only अगर SDHC_SPIEN is set
 * (which is currently not the हाल in this driver)
 */
अटल पूर्णांक mxc_clkभागs[] = अणु0, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192,
	256, 384, 512, 768, 1024पूर्ण;

/* MX21, MX27 */
अटल अचिन्हित पूर्णांक spi_imx_clkभाग_1(अचिन्हित पूर्णांक fin,
		अचिन्हित पूर्णांक fspi, अचिन्हित पूर्णांक max, अचिन्हित पूर्णांक *fres)
अणु
	पूर्णांक i;

	क्रम (i = 2; i < max; i++)
		अगर (fspi * mxc_clkभागs[i] >= fin)
			अवरोध;

	*fres = fin / mxc_clkभागs[i];
	वापस i;
पूर्ण

/* MX1, MX31, MX35, MX51 CSPI */
अटल अचिन्हित पूर्णांक spi_imx_clkभाग_2(अचिन्हित पूर्णांक fin,
		अचिन्हित पूर्णांक fspi, अचिन्हित पूर्णांक *fres)
अणु
	पूर्णांक i, भाग = 4;

	क्रम (i = 0; i < 7; i++) अणु
		अगर (fspi * भाग >= fin)
			जाओ out;
		भाग <<= 1;
	पूर्ण

out:
	*fres = fin / भाग;
	वापस i;
पूर्ण

अटल पूर्णांक spi_imx_bytes_per_word(स्थिर पूर्णांक bits_per_word)
अणु
	अगर (bits_per_word <= 8)
		वापस 1;
	अन्यथा अगर (bits_per_word <= 16)
		वापस 2;
	अन्यथा
		वापस 4;
पूर्ण

अटल bool spi_imx_can_dma(काष्ठा spi_master *master, काष्ठा spi_device *spi,
			 काष्ठा spi_transfer *transfer)
अणु
	काष्ठा spi_imx_data *spi_imx = spi_master_get_devdata(master);

	अगर (!use_dma || master->fallback)
		वापस false;

	अगर (!master->dma_rx)
		वापस false;

	अगर (spi_imx->slave_mode)
		वापस false;

	अगर (transfer->len < spi_imx->devtype_data->fअगरo_size)
		वापस false;

	spi_imx->dynamic_burst = 0;

	वापस true;
पूर्ण

#घोषणा MX51_ECSPI_CTRL		0x08
#घोषणा MX51_ECSPI_CTRL_ENABLE		(1 <<  0)
#घोषणा MX51_ECSPI_CTRL_XCH		(1 <<  2)
#घोषणा MX51_ECSPI_CTRL_SMC		(1 << 3)
#घोषणा MX51_ECSPI_CTRL_MODE_MASK	(0xf << 4)
#घोषणा MX51_ECSPI_CTRL_DRCTL(drctl)	((drctl) << 16)
#घोषणा MX51_ECSPI_CTRL_POSTDIV_OFFSET	8
#घोषणा MX51_ECSPI_CTRL_PREDIV_OFFSET	12
#घोषणा MX51_ECSPI_CTRL_CS(cs)		((cs) << 18)
#घोषणा MX51_ECSPI_CTRL_BL_OFFSET	20
#घोषणा MX51_ECSPI_CTRL_BL_MASK		(0xfff << 20)

#घोषणा MX51_ECSPI_CONFIG	0x0c
#घोषणा MX51_ECSPI_CONFIG_SCLKPHA(cs)	(1 << ((cs) +  0))
#घोषणा MX51_ECSPI_CONFIG_SCLKPOL(cs)	(1 << ((cs) +  4))
#घोषणा MX51_ECSPI_CONFIG_SBBCTRL(cs)	(1 << ((cs) +  8))
#घोषणा MX51_ECSPI_CONFIG_SSBPOL(cs)	(1 << ((cs) + 12))
#घोषणा MX51_ECSPI_CONFIG_SCLKCTL(cs)	(1 << ((cs) + 20))

#घोषणा MX51_ECSPI_INT		0x10
#घोषणा MX51_ECSPI_INT_TEEN		(1 <<  0)
#घोषणा MX51_ECSPI_INT_RREN		(1 <<  3)
#घोषणा MX51_ECSPI_INT_RDREN		(1 <<  4)

#घोषणा MX51_ECSPI_DMA		0x14
#घोषणा MX51_ECSPI_DMA_TX_WML(wml)	((wml) & 0x3f)
#घोषणा MX51_ECSPI_DMA_RX_WML(wml)	(((wml) & 0x3f) << 16)
#घोषणा MX51_ECSPI_DMA_RXT_WML(wml)	(((wml) & 0x3f) << 24)

#घोषणा MX51_ECSPI_DMA_TEDEN		(1 << 7)
#घोषणा MX51_ECSPI_DMA_RXDEN		(1 << 23)
#घोषणा MX51_ECSPI_DMA_RXTDEN		(1 << 31)

#घोषणा MX51_ECSPI_STAT		0x18
#घोषणा MX51_ECSPI_STAT_RR		(1 <<  3)

#घोषणा MX51_ECSPI_TESTREG	0x20
#घोषणा MX51_ECSPI_TESTREG_LBC	BIT(31)

अटल व्योम spi_imx_buf_rx_swap_u32(काष्ठा spi_imx_data *spi_imx)
अणु
	अचिन्हित पूर्णांक val = पढ़ोl(spi_imx->base + MXC_CSPIRXDATA);
#अगर_घोषित __LITTLE_ENDIAN
	अचिन्हित पूर्णांक bytes_per_word;
#पूर्ण_अगर

	अगर (spi_imx->rx_buf) अणु
#अगर_घोषित __LITTLE_ENDIAN
		bytes_per_word = spi_imx_bytes_per_word(spi_imx->bits_per_word);
		अगर (bytes_per_word == 1)
			val = cpu_to_be32(val);
		अन्यथा अगर (bytes_per_word == 2)
			val = (val << 16) | (val >> 16);
#पूर्ण_अगर
		*(u32 *)spi_imx->rx_buf = val;
		spi_imx->rx_buf += माप(u32);
	पूर्ण

	spi_imx->reमुख्यder -= माप(u32);
पूर्ण

अटल व्योम spi_imx_buf_rx_swap(काष्ठा spi_imx_data *spi_imx)
अणु
	पूर्णांक unaligned;
	u32 val;

	unaligned = spi_imx->reमुख्यder % 4;

	अगर (!unaligned) अणु
		spi_imx_buf_rx_swap_u32(spi_imx);
		वापस;
	पूर्ण

	अगर (spi_imx_bytes_per_word(spi_imx->bits_per_word) == 2) अणु
		spi_imx_buf_rx_u16(spi_imx);
		वापस;
	पूर्ण

	val = पढ़ोl(spi_imx->base + MXC_CSPIRXDATA);

	जबतक (unaligned--) अणु
		अगर (spi_imx->rx_buf) अणु
			*(u8 *)spi_imx->rx_buf = (val >> (8 * unaligned)) & 0xff;
			spi_imx->rx_buf++;
		पूर्ण
		spi_imx->reमुख्यder--;
	पूर्ण
पूर्ण

अटल व्योम spi_imx_buf_tx_swap_u32(काष्ठा spi_imx_data *spi_imx)
अणु
	u32 val = 0;
#अगर_घोषित __LITTLE_ENDIAN
	अचिन्हित पूर्णांक bytes_per_word;
#पूर्ण_अगर

	अगर (spi_imx->tx_buf) अणु
		val = *(u32 *)spi_imx->tx_buf;
		spi_imx->tx_buf += माप(u32);
	पूर्ण

	spi_imx->count -= माप(u32);
#अगर_घोषित __LITTLE_ENDIAN
	bytes_per_word = spi_imx_bytes_per_word(spi_imx->bits_per_word);

	अगर (bytes_per_word == 1)
		val = cpu_to_be32(val);
	अन्यथा अगर (bytes_per_word == 2)
		val = (val << 16) | (val >> 16);
#पूर्ण_अगर
	ग_लिखोl(val, spi_imx->base + MXC_CSPITXDATA);
पूर्ण

अटल व्योम spi_imx_buf_tx_swap(काष्ठा spi_imx_data *spi_imx)
अणु
	पूर्णांक unaligned;
	u32 val = 0;

	unaligned = spi_imx->count % 4;

	अगर (!unaligned) अणु
		spi_imx_buf_tx_swap_u32(spi_imx);
		वापस;
	पूर्ण

	अगर (spi_imx_bytes_per_word(spi_imx->bits_per_word) == 2) अणु
		spi_imx_buf_tx_u16(spi_imx);
		वापस;
	पूर्ण

	जबतक (unaligned--) अणु
		अगर (spi_imx->tx_buf) अणु
			val |= *(u8 *)spi_imx->tx_buf << (8 * unaligned);
			spi_imx->tx_buf++;
		पूर्ण
		spi_imx->count--;
	पूर्ण

	ग_लिखोl(val, spi_imx->base + MXC_CSPITXDATA);
पूर्ण

अटल व्योम mx53_ecspi_rx_slave(काष्ठा spi_imx_data *spi_imx)
अणु
	u32 val = be32_to_cpu(पढ़ोl(spi_imx->base + MXC_CSPIRXDATA));

	अगर (spi_imx->rx_buf) अणु
		पूर्णांक n_bytes = spi_imx->slave_burst % माप(val);

		अगर (!n_bytes)
			n_bytes = माप(val);

		स_नकल(spi_imx->rx_buf,
		       ((u8 *)&val) + माप(val) - n_bytes, n_bytes);

		spi_imx->rx_buf += n_bytes;
		spi_imx->slave_burst -= n_bytes;
	पूर्ण

	spi_imx->reमुख्यder -= माप(u32);
पूर्ण

अटल व्योम mx53_ecspi_tx_slave(काष्ठा spi_imx_data *spi_imx)
अणु
	u32 val = 0;
	पूर्णांक n_bytes = spi_imx->count % माप(val);

	अगर (!n_bytes)
		n_bytes = माप(val);

	अगर (spi_imx->tx_buf) अणु
		स_नकल(((u8 *)&val) + माप(val) - n_bytes,
		       spi_imx->tx_buf, n_bytes);
		val = cpu_to_be32(val);
		spi_imx->tx_buf += n_bytes;
	पूर्ण

	spi_imx->count -= n_bytes;

	ग_लिखोl(val, spi_imx->base + MXC_CSPITXDATA);
पूर्ण

/* MX51 eCSPI */
अटल अचिन्हित पूर्णांक mx51_ecspi_clkभाग(काष्ठा spi_imx_data *spi_imx,
				      अचिन्हित पूर्णांक fspi, अचिन्हित पूर्णांक *fres)
अणु
	/*
	 * there are two 4-bit भागiders, the pre-भागider भागides by
	 * $pre, the post-भागider by 2^$post
	 */
	अचिन्हित पूर्णांक pre, post;
	अचिन्हित पूर्णांक fin = spi_imx->spi_clk;

	अगर (unlikely(fspi > fin))
		वापस 0;

	post = fls(fin) - fls(fspi);
	अगर (fin > fspi << post)
		post++;

	/* now we have: (fin <= fspi << post) with post being minimal */

	post = max(4U, post) - 4;
	अगर (unlikely(post > 0xf)) अणु
		dev_err(spi_imx->dev, "cannot set clock freq: %u (base freq: %u)\n",
				fspi, fin);
		वापस 0xff;
	पूर्ण

	pre = DIV_ROUND_UP(fin, fspi << post) - 1;

	dev_dbg(spi_imx->dev, "%s: fin: %u, fspi: %u, post: %u, pre: %u\n",
			__func__, fin, fspi, post, pre);

	/* Resulting frequency क्रम the SCLK line. */
	*fres = (fin / (pre + 1)) >> post;

	वापस (pre << MX51_ECSPI_CTRL_PREDIV_OFFSET) |
		(post << MX51_ECSPI_CTRL_POSTDIV_OFFSET);
पूर्ण

अटल व्योम mx51_ecspi_पूर्णांकctrl(काष्ठा spi_imx_data *spi_imx, पूर्णांक enable)
अणु
	अचिन्हित val = 0;

	अगर (enable & MXC_INT_TE)
		val |= MX51_ECSPI_INT_TEEN;

	अगर (enable & MXC_INT_RR)
		val |= MX51_ECSPI_INT_RREN;

	अगर (enable & MXC_INT_RDR)
		val |= MX51_ECSPI_INT_RDREN;

	ग_लिखोl(val, spi_imx->base + MX51_ECSPI_INT);
पूर्ण

अटल व्योम mx51_ecspi_trigger(काष्ठा spi_imx_data *spi_imx)
अणु
	u32 reg;

	reg = पढ़ोl(spi_imx->base + MX51_ECSPI_CTRL);
	reg |= MX51_ECSPI_CTRL_XCH;
	ग_लिखोl(reg, spi_imx->base + MX51_ECSPI_CTRL);
पूर्ण

अटल व्योम mx51_disable_dma(काष्ठा spi_imx_data *spi_imx)
अणु
	ग_लिखोl(0, spi_imx->base + MX51_ECSPI_DMA);
पूर्ण

अटल व्योम mx51_ecspi_disable(काष्ठा spi_imx_data *spi_imx)
अणु
	u32 ctrl;

	ctrl = पढ़ोl(spi_imx->base + MX51_ECSPI_CTRL);
	ctrl &= ~MX51_ECSPI_CTRL_ENABLE;
	ग_लिखोl(ctrl, spi_imx->base + MX51_ECSPI_CTRL);
पूर्ण

अटल पूर्णांक mx51_ecspi_prepare_message(काष्ठा spi_imx_data *spi_imx,
				      काष्ठा spi_message *msg)
अणु
	काष्ठा spi_device *spi = msg->spi;
	u32 ctrl = MX51_ECSPI_CTRL_ENABLE;
	u32 testreg;
	u32 cfg = पढ़ोl(spi_imx->base + MX51_ECSPI_CONFIG);

	/* set Master or Slave mode */
	अगर (spi_imx->slave_mode)
		ctrl &= ~MX51_ECSPI_CTRL_MODE_MASK;
	अन्यथा
		ctrl |= MX51_ECSPI_CTRL_MODE_MASK;

	/*
	 * Enable SPI_RDY handling (falling edge/level triggered).
	 */
	अगर (spi->mode & SPI_READY)
		ctrl |= MX51_ECSPI_CTRL_DRCTL(spi_imx->spi_drctl);

	/* set chip select to use */
	ctrl |= MX51_ECSPI_CTRL_CS(spi->chip_select);

	/*
	 * The ctrl रेजिस्टर must be written first, with the EN bit set other
	 * रेजिस्टरs must not be written to.
	 */
	ग_लिखोl(ctrl, spi_imx->base + MX51_ECSPI_CTRL);

	testreg = पढ़ोl(spi_imx->base + MX51_ECSPI_TESTREG);
	अगर (spi->mode & SPI_LOOP)
		testreg |= MX51_ECSPI_TESTREG_LBC;
	अन्यथा
		testreg &= ~MX51_ECSPI_TESTREG_LBC;
	ग_लिखोl(testreg, spi_imx->base + MX51_ECSPI_TESTREG);

	/*
	 * eCSPI burst completion by Chip Select संकेत in Slave mode
	 * is not functional क्रम imx53 Soc, config SPI burst completed when
	 * BURST_LENGTH + 1 bits are received
	 */
	अगर (spi_imx->slave_mode && is_imx53_ecspi(spi_imx))
		cfg &= ~MX51_ECSPI_CONFIG_SBBCTRL(spi->chip_select);
	अन्यथा
		cfg |= MX51_ECSPI_CONFIG_SBBCTRL(spi->chip_select);

	अगर (spi->mode & SPI_CPHA)
		cfg |= MX51_ECSPI_CONFIG_SCLKPHA(spi->chip_select);
	अन्यथा
		cfg &= ~MX51_ECSPI_CONFIG_SCLKPHA(spi->chip_select);

	अगर (spi->mode & SPI_CPOL) अणु
		cfg |= MX51_ECSPI_CONFIG_SCLKPOL(spi->chip_select);
		cfg |= MX51_ECSPI_CONFIG_SCLKCTL(spi->chip_select);
	पूर्ण अन्यथा अणु
		cfg &= ~MX51_ECSPI_CONFIG_SCLKPOL(spi->chip_select);
		cfg &= ~MX51_ECSPI_CONFIG_SCLKCTL(spi->chip_select);
	पूर्ण

	अगर (spi->mode & SPI_CS_HIGH)
		cfg |= MX51_ECSPI_CONFIG_SSBPOL(spi->chip_select);
	अन्यथा
		cfg &= ~MX51_ECSPI_CONFIG_SSBPOL(spi->chip_select);

	ग_लिखोl(cfg, spi_imx->base + MX51_ECSPI_CONFIG);

	वापस 0;
पूर्ण

अटल पूर्णांक mx51_ecspi_prepare_transfer(काष्ठा spi_imx_data *spi_imx,
				       काष्ठा spi_device *spi)
अणु
	u32 ctrl = पढ़ोl(spi_imx->base + MX51_ECSPI_CTRL);
	u32 clk, delay;

	/* Clear BL field and set the right value */
	ctrl &= ~MX51_ECSPI_CTRL_BL_MASK;
	अगर (spi_imx->slave_mode && is_imx53_ecspi(spi_imx))
		ctrl |= (spi_imx->slave_burst * 8 - 1)
			<< MX51_ECSPI_CTRL_BL_OFFSET;
	अन्यथा
		ctrl |= (spi_imx->bits_per_word - 1)
			<< MX51_ECSPI_CTRL_BL_OFFSET;

	/* set घड़ी speed */
	ctrl &= ~(0xf << MX51_ECSPI_CTRL_POSTDIV_OFFSET |
		  0xf << MX51_ECSPI_CTRL_PREDIV_OFFSET);
	ctrl |= mx51_ecspi_clkभाग(spi_imx, spi_imx->spi_bus_clk, &clk);
	spi_imx->spi_bus_clk = clk;

	अगर (spi_imx->usedma)
		ctrl |= MX51_ECSPI_CTRL_SMC;

	ग_लिखोl(ctrl, spi_imx->base + MX51_ECSPI_CTRL);

	/*
	 * Wait until the changes in the configuration रेजिस्टर CONFIGREG
	 * propagate पूर्णांकo the hardware. It takes exactly one tick of the
	 * SCLK घड़ी, but we will रुको two SCLK घड़ी just to be sure. The
	 * effect of the delay it takes क्रम the hardware to apply changes
	 * is noticable अगर the SCLK घड़ी run very slow. In such a हाल, अगर
	 * the polarity of SCLK should be inverted, the GPIO ChipSelect might
	 * be निश्चितed beक्रमe the SCLK polarity changes, which would disrupt
	 * the SPI communication as the device on the other end would consider
	 * the change of SCLK polarity as a घड़ी tick alपढ़ोy.
	 */
	delay = (2 * 1000000) / clk;
	अगर (likely(delay < 10))	/* SCLK is faster than 100 kHz */
		udelay(delay);
	अन्यथा			/* SCLK is _very_ slow */
		usleep_range(delay, delay + 10);

	वापस 0;
पूर्ण

अटल व्योम mx51_setup_wml(काष्ठा spi_imx_data *spi_imx)
अणु
	/*
	 * Configure the DMA रेजिस्टर: setup the watermark
	 * and enable DMA request.
	 */
	ग_लिखोl(MX51_ECSPI_DMA_RX_WML(spi_imx->wml - 1) |
		MX51_ECSPI_DMA_TX_WML(spi_imx->wml) |
		MX51_ECSPI_DMA_RXT_WML(spi_imx->wml) |
		MX51_ECSPI_DMA_TEDEN | MX51_ECSPI_DMA_RXDEN |
		MX51_ECSPI_DMA_RXTDEN, spi_imx->base + MX51_ECSPI_DMA);
पूर्ण

अटल पूर्णांक mx51_ecspi_rx_available(काष्ठा spi_imx_data *spi_imx)
अणु
	वापस पढ़ोl(spi_imx->base + MX51_ECSPI_STAT) & MX51_ECSPI_STAT_RR;
पूर्ण

अटल व्योम mx51_ecspi_reset(काष्ठा spi_imx_data *spi_imx)
अणु
	/* drain receive buffer */
	जबतक (mx51_ecspi_rx_available(spi_imx))
		पढ़ोl(spi_imx->base + MXC_CSPIRXDATA);
पूर्ण

#घोषणा MX31_INTREG_TEEN	(1 << 0)
#घोषणा MX31_INTREG_RREN	(1 << 3)

#घोषणा MX31_CSPICTRL_ENABLE	(1 << 0)
#घोषणा MX31_CSPICTRL_MASTER	(1 << 1)
#घोषणा MX31_CSPICTRL_XCH	(1 << 2)
#घोषणा MX31_CSPICTRL_SMC	(1 << 3)
#घोषणा MX31_CSPICTRL_POL	(1 << 4)
#घोषणा MX31_CSPICTRL_PHA	(1 << 5)
#घोषणा MX31_CSPICTRL_SSCTL	(1 << 6)
#घोषणा MX31_CSPICTRL_SSPOL	(1 << 7)
#घोषणा MX31_CSPICTRL_BC_SHIFT	8
#घोषणा MX35_CSPICTRL_BL_SHIFT	20
#घोषणा MX31_CSPICTRL_CS_SHIFT	24
#घोषणा MX35_CSPICTRL_CS_SHIFT	12
#घोषणा MX31_CSPICTRL_DR_SHIFT	16

#घोषणा MX31_CSPI_DMAREG	0x10
#घोषणा MX31_DMAREG_RH_DEN	(1<<4)
#घोषणा MX31_DMAREG_TH_DEN	(1<<1)

#घोषणा MX31_CSPISTATUS		0x14
#घोषणा MX31_STATUS_RR		(1 << 3)

#घोषणा MX31_CSPI_TESTREG	0x1C
#घोषणा MX31_TEST_LBC		(1 << 14)

/* These functions also work क्रम the i.MX35, but be aware that
 * the i.MX35 has a slightly dअगरferent रेजिस्टर layout क्रम bits
 * we करो not use here.
 */
अटल व्योम mx31_पूर्णांकctrl(काष्ठा spi_imx_data *spi_imx, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक val = 0;

	अगर (enable & MXC_INT_TE)
		val |= MX31_INTREG_TEEN;
	अगर (enable & MXC_INT_RR)
		val |= MX31_INTREG_RREN;

	ग_लिखोl(val, spi_imx->base + MXC_CSPIINT);
पूर्ण

अटल व्योम mx31_trigger(काष्ठा spi_imx_data *spi_imx)
अणु
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(spi_imx->base + MXC_CSPICTRL);
	reg |= MX31_CSPICTRL_XCH;
	ग_लिखोl(reg, spi_imx->base + MXC_CSPICTRL);
पूर्ण

अटल पूर्णांक mx31_prepare_message(काष्ठा spi_imx_data *spi_imx,
				काष्ठा spi_message *msg)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mx31_prepare_transfer(काष्ठा spi_imx_data *spi_imx,
				 काष्ठा spi_device *spi)
अणु
	अचिन्हित पूर्णांक reg = MX31_CSPICTRL_ENABLE | MX31_CSPICTRL_MASTER;
	अचिन्हित पूर्णांक clk;

	reg |= spi_imx_clkभाग_2(spi_imx->spi_clk, spi_imx->spi_bus_clk, &clk) <<
		MX31_CSPICTRL_DR_SHIFT;
	spi_imx->spi_bus_clk = clk;

	अगर (is_imx35_cspi(spi_imx)) अणु
		reg |= (spi_imx->bits_per_word - 1) << MX35_CSPICTRL_BL_SHIFT;
		reg |= MX31_CSPICTRL_SSCTL;
	पूर्ण अन्यथा अणु
		reg |= (spi_imx->bits_per_word - 1) << MX31_CSPICTRL_BC_SHIFT;
	पूर्ण

	अगर (spi->mode & SPI_CPHA)
		reg |= MX31_CSPICTRL_PHA;
	अगर (spi->mode & SPI_CPOL)
		reg |= MX31_CSPICTRL_POL;
	अगर (spi->mode & SPI_CS_HIGH)
		reg |= MX31_CSPICTRL_SSPOL;
	अगर (!spi->cs_gpiod)
		reg |= (spi->chip_select) <<
			(is_imx35_cspi(spi_imx) ? MX35_CSPICTRL_CS_SHIFT :
						  MX31_CSPICTRL_CS_SHIFT);

	अगर (spi_imx->usedma)
		reg |= MX31_CSPICTRL_SMC;

	ग_लिखोl(reg, spi_imx->base + MXC_CSPICTRL);

	reg = पढ़ोl(spi_imx->base + MX31_CSPI_TESTREG);
	अगर (spi->mode & SPI_LOOP)
		reg |= MX31_TEST_LBC;
	अन्यथा
		reg &= ~MX31_TEST_LBC;
	ग_लिखोl(reg, spi_imx->base + MX31_CSPI_TESTREG);

	अगर (spi_imx->usedma) अणु
		/*
		 * configure DMA requests when RXFIFO is half full and
		 * when TXFIFO is half empty
		 */
		ग_लिखोl(MX31_DMAREG_RH_DEN | MX31_DMAREG_TH_DEN,
			spi_imx->base + MX31_CSPI_DMAREG);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mx31_rx_available(काष्ठा spi_imx_data *spi_imx)
अणु
	वापस पढ़ोl(spi_imx->base + MX31_CSPISTATUS) & MX31_STATUS_RR;
पूर्ण

अटल व्योम mx31_reset(काष्ठा spi_imx_data *spi_imx)
अणु
	/* drain receive buffer */
	जबतक (पढ़ोl(spi_imx->base + MX31_CSPISTATUS) & MX31_STATUS_RR)
		पढ़ोl(spi_imx->base + MXC_CSPIRXDATA);
पूर्ण

#घोषणा MX21_INTREG_RR		(1 << 4)
#घोषणा MX21_INTREG_TEEN	(1 << 9)
#घोषणा MX21_INTREG_RREN	(1 << 13)

#घोषणा MX21_CSPICTRL_POL	(1 << 5)
#घोषणा MX21_CSPICTRL_PHA	(1 << 6)
#घोषणा MX21_CSPICTRL_SSPOL	(1 << 8)
#घोषणा MX21_CSPICTRL_XCH	(1 << 9)
#घोषणा MX21_CSPICTRL_ENABLE	(1 << 10)
#घोषणा MX21_CSPICTRL_MASTER	(1 << 11)
#घोषणा MX21_CSPICTRL_DR_SHIFT	14
#घोषणा MX21_CSPICTRL_CS_SHIFT	19

अटल व्योम mx21_पूर्णांकctrl(काष्ठा spi_imx_data *spi_imx, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक val = 0;

	अगर (enable & MXC_INT_TE)
		val |= MX21_INTREG_TEEN;
	अगर (enable & MXC_INT_RR)
		val |= MX21_INTREG_RREN;

	ग_लिखोl(val, spi_imx->base + MXC_CSPIINT);
पूर्ण

अटल व्योम mx21_trigger(काष्ठा spi_imx_data *spi_imx)
अणु
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(spi_imx->base + MXC_CSPICTRL);
	reg |= MX21_CSPICTRL_XCH;
	ग_लिखोl(reg, spi_imx->base + MXC_CSPICTRL);
पूर्ण

अटल पूर्णांक mx21_prepare_message(काष्ठा spi_imx_data *spi_imx,
				काष्ठा spi_message *msg)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mx21_prepare_transfer(काष्ठा spi_imx_data *spi_imx,
				 काष्ठा spi_device *spi)
अणु
	अचिन्हित पूर्णांक reg = MX21_CSPICTRL_ENABLE | MX21_CSPICTRL_MASTER;
	अचिन्हित पूर्णांक max = is_imx27_cspi(spi_imx) ? 16 : 18;
	अचिन्हित पूर्णांक clk;

	reg |= spi_imx_clkभाग_1(spi_imx->spi_clk, spi_imx->spi_bus_clk, max, &clk)
		<< MX21_CSPICTRL_DR_SHIFT;
	spi_imx->spi_bus_clk = clk;

	reg |= spi_imx->bits_per_word - 1;

	अगर (spi->mode & SPI_CPHA)
		reg |= MX21_CSPICTRL_PHA;
	अगर (spi->mode & SPI_CPOL)
		reg |= MX21_CSPICTRL_POL;
	अगर (spi->mode & SPI_CS_HIGH)
		reg |= MX21_CSPICTRL_SSPOL;
	अगर (!spi->cs_gpiod)
		reg |= spi->chip_select << MX21_CSPICTRL_CS_SHIFT;

	ग_लिखोl(reg, spi_imx->base + MXC_CSPICTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक mx21_rx_available(काष्ठा spi_imx_data *spi_imx)
अणु
	वापस पढ़ोl(spi_imx->base + MXC_CSPIINT) & MX21_INTREG_RR;
पूर्ण

अटल व्योम mx21_reset(काष्ठा spi_imx_data *spi_imx)
अणु
	ग_लिखोl(1, spi_imx->base + MXC_RESET);
पूर्ण

#घोषणा MX1_INTREG_RR		(1 << 3)
#घोषणा MX1_INTREG_TEEN		(1 << 8)
#घोषणा MX1_INTREG_RREN		(1 << 11)

#घोषणा MX1_CSPICTRL_POL	(1 << 4)
#घोषणा MX1_CSPICTRL_PHA	(1 << 5)
#घोषणा MX1_CSPICTRL_XCH	(1 << 8)
#घोषणा MX1_CSPICTRL_ENABLE	(1 << 9)
#घोषणा MX1_CSPICTRL_MASTER	(1 << 10)
#घोषणा MX1_CSPICTRL_DR_SHIFT	13

अटल व्योम mx1_पूर्णांकctrl(काष्ठा spi_imx_data *spi_imx, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक val = 0;

	अगर (enable & MXC_INT_TE)
		val |= MX1_INTREG_TEEN;
	अगर (enable & MXC_INT_RR)
		val |= MX1_INTREG_RREN;

	ग_लिखोl(val, spi_imx->base + MXC_CSPIINT);
पूर्ण

अटल व्योम mx1_trigger(काष्ठा spi_imx_data *spi_imx)
अणु
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(spi_imx->base + MXC_CSPICTRL);
	reg |= MX1_CSPICTRL_XCH;
	ग_लिखोl(reg, spi_imx->base + MXC_CSPICTRL);
पूर्ण

अटल पूर्णांक mx1_prepare_message(काष्ठा spi_imx_data *spi_imx,
			       काष्ठा spi_message *msg)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mx1_prepare_transfer(काष्ठा spi_imx_data *spi_imx,
				काष्ठा spi_device *spi)
अणु
	अचिन्हित पूर्णांक reg = MX1_CSPICTRL_ENABLE | MX1_CSPICTRL_MASTER;
	अचिन्हित पूर्णांक clk;

	reg |= spi_imx_clkभाग_2(spi_imx->spi_clk, spi_imx->spi_bus_clk, &clk) <<
		MX1_CSPICTRL_DR_SHIFT;
	spi_imx->spi_bus_clk = clk;

	reg |= spi_imx->bits_per_word - 1;

	अगर (spi->mode & SPI_CPHA)
		reg |= MX1_CSPICTRL_PHA;
	अगर (spi->mode & SPI_CPOL)
		reg |= MX1_CSPICTRL_POL;

	ग_लिखोl(reg, spi_imx->base + MXC_CSPICTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक mx1_rx_available(काष्ठा spi_imx_data *spi_imx)
अणु
	वापस पढ़ोl(spi_imx->base + MXC_CSPIINT) & MX1_INTREG_RR;
पूर्ण

अटल व्योम mx1_reset(काष्ठा spi_imx_data *spi_imx)
अणु
	ग_लिखोl(1, spi_imx->base + MXC_RESET);
पूर्ण

अटल काष्ठा spi_imx_devtype_data imx1_cspi_devtype_data = अणु
	.पूर्णांकctrl = mx1_पूर्णांकctrl,
	.prepare_message = mx1_prepare_message,
	.prepare_transfer = mx1_prepare_transfer,
	.trigger = mx1_trigger,
	.rx_available = mx1_rx_available,
	.reset = mx1_reset,
	.fअगरo_size = 8,
	.has_dmamode = false,
	.dynamic_burst = false,
	.has_slavemode = false,
	.devtype = IMX1_CSPI,
पूर्ण;

अटल काष्ठा spi_imx_devtype_data imx21_cspi_devtype_data = अणु
	.पूर्णांकctrl = mx21_पूर्णांकctrl,
	.prepare_message = mx21_prepare_message,
	.prepare_transfer = mx21_prepare_transfer,
	.trigger = mx21_trigger,
	.rx_available = mx21_rx_available,
	.reset = mx21_reset,
	.fअगरo_size = 8,
	.has_dmamode = false,
	.dynamic_burst = false,
	.has_slavemode = false,
	.devtype = IMX21_CSPI,
पूर्ण;

अटल काष्ठा spi_imx_devtype_data imx27_cspi_devtype_data = अणु
	/* i.mx27 cspi shares the functions with i.mx21 one */
	.पूर्णांकctrl = mx21_पूर्णांकctrl,
	.prepare_message = mx21_prepare_message,
	.prepare_transfer = mx21_prepare_transfer,
	.trigger = mx21_trigger,
	.rx_available = mx21_rx_available,
	.reset = mx21_reset,
	.fअगरo_size = 8,
	.has_dmamode = false,
	.dynamic_burst = false,
	.has_slavemode = false,
	.devtype = IMX27_CSPI,
पूर्ण;

अटल काष्ठा spi_imx_devtype_data imx31_cspi_devtype_data = अणु
	.पूर्णांकctrl = mx31_पूर्णांकctrl,
	.prepare_message = mx31_prepare_message,
	.prepare_transfer = mx31_prepare_transfer,
	.trigger = mx31_trigger,
	.rx_available = mx31_rx_available,
	.reset = mx31_reset,
	.fअगरo_size = 8,
	.has_dmamode = false,
	.dynamic_burst = false,
	.has_slavemode = false,
	.devtype = IMX31_CSPI,
पूर्ण;

अटल काष्ठा spi_imx_devtype_data imx35_cspi_devtype_data = अणु
	/* i.mx35 and later cspi shares the functions with i.mx31 one */
	.पूर्णांकctrl = mx31_पूर्णांकctrl,
	.prepare_message = mx31_prepare_message,
	.prepare_transfer = mx31_prepare_transfer,
	.trigger = mx31_trigger,
	.rx_available = mx31_rx_available,
	.reset = mx31_reset,
	.fअगरo_size = 8,
	.has_dmamode = true,
	.dynamic_burst = false,
	.has_slavemode = false,
	.devtype = IMX35_CSPI,
पूर्ण;

अटल काष्ठा spi_imx_devtype_data imx51_ecspi_devtype_data = अणु
	.पूर्णांकctrl = mx51_ecspi_पूर्णांकctrl,
	.prepare_message = mx51_ecspi_prepare_message,
	.prepare_transfer = mx51_ecspi_prepare_transfer,
	.trigger = mx51_ecspi_trigger,
	.rx_available = mx51_ecspi_rx_available,
	.reset = mx51_ecspi_reset,
	.setup_wml = mx51_setup_wml,
	.disable_dma = mx51_disable_dma,
	.fअगरo_size = 64,
	.has_dmamode = true,
	.dynamic_burst = true,
	.has_slavemode = true,
	.disable = mx51_ecspi_disable,
	.devtype = IMX51_ECSPI,
पूर्ण;

अटल काष्ठा spi_imx_devtype_data imx53_ecspi_devtype_data = अणु
	.पूर्णांकctrl = mx51_ecspi_पूर्णांकctrl,
	.prepare_message = mx51_ecspi_prepare_message,
	.prepare_transfer = mx51_ecspi_prepare_transfer,
	.trigger = mx51_ecspi_trigger,
	.rx_available = mx51_ecspi_rx_available,
	.disable_dma = mx51_disable_dma,
	.reset = mx51_ecspi_reset,
	.fअगरo_size = 64,
	.has_dmamode = true,
	.has_slavemode = true,
	.disable = mx51_ecspi_disable,
	.devtype = IMX53_ECSPI,
पूर्ण;

अटल स्थिर काष्ठा of_device_id spi_imx_dt_ids[] = अणु
	अणु .compatible = "fsl,imx1-cspi", .data = &imx1_cspi_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx21-cspi", .data = &imx21_cspi_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx27-cspi", .data = &imx27_cspi_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx31-cspi", .data = &imx31_cspi_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx35-cspi", .data = &imx35_cspi_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx51-ecspi", .data = &imx51_ecspi_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx53-ecspi", .data = &imx53_ecspi_devtype_data, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spi_imx_dt_ids);

अटल व्योम spi_imx_set_burst_len(काष्ठा spi_imx_data *spi_imx, पूर्णांक n_bits)
अणु
	u32 ctrl;

	ctrl = पढ़ोl(spi_imx->base + MX51_ECSPI_CTRL);
	ctrl &= ~MX51_ECSPI_CTRL_BL_MASK;
	ctrl |= ((n_bits - 1) << MX51_ECSPI_CTRL_BL_OFFSET);
	ग_लिखोl(ctrl, spi_imx->base + MX51_ECSPI_CTRL);
पूर्ण

अटल व्योम spi_imx_push(काष्ठा spi_imx_data *spi_imx)
अणु
	अचिन्हित पूर्णांक burst_len, fअगरo_words;

	अगर (spi_imx->dynamic_burst)
		fअगरo_words = 4;
	अन्यथा
		fअगरo_words = spi_imx_bytes_per_word(spi_imx->bits_per_word);
	/*
	 * Reload the FIFO when the reमुख्यing bytes to be transferred in the
	 * current burst is 0. This only applies when bits_per_word is a
	 * multiple of 8.
	 */
	अगर (!spi_imx->reमुख्यder) अणु
		अगर (spi_imx->dynamic_burst) अणु

			/* We need to deal unaligned data first */
			burst_len = spi_imx->count % MX51_ECSPI_CTRL_MAX_BURST;

			अगर (!burst_len)
				burst_len = MX51_ECSPI_CTRL_MAX_BURST;

			spi_imx_set_burst_len(spi_imx, burst_len * 8);

			spi_imx->reमुख्यder = burst_len;
		पूर्ण अन्यथा अणु
			spi_imx->reमुख्यder = fअगरo_words;
		पूर्ण
	पूर्ण

	जबतक (spi_imx->txfअगरo < spi_imx->devtype_data->fअगरo_size) अणु
		अगर (!spi_imx->count)
			अवरोध;
		अगर (spi_imx->dynamic_burst &&
		    spi_imx->txfअगरo >= DIV_ROUND_UP(spi_imx->reमुख्यder,
						     fअगरo_words))
			अवरोध;
		spi_imx->tx(spi_imx);
		spi_imx->txfअगरo++;
	पूर्ण

	अगर (!spi_imx->slave_mode)
		spi_imx->devtype_data->trigger(spi_imx);
पूर्ण

अटल irqवापस_t spi_imx_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_imx_data *spi_imx = dev_id;

	जबतक (spi_imx->txfअगरo &&
	       spi_imx->devtype_data->rx_available(spi_imx)) अणु
		spi_imx->rx(spi_imx);
		spi_imx->txfअगरo--;
	पूर्ण

	अगर (spi_imx->count) अणु
		spi_imx_push(spi_imx);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (spi_imx->txfअगरo) अणु
		/* No data left to push, but still रुकोing क्रम rx data,
		 * enable receive data available पूर्णांकerrupt.
		 */
		spi_imx->devtype_data->पूर्णांकctrl(
				spi_imx, MXC_INT_RR);
		वापस IRQ_HANDLED;
	पूर्ण

	spi_imx->devtype_data->पूर्णांकctrl(spi_imx, 0);
	complete(&spi_imx->xfer_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक spi_imx_dma_configure(काष्ठा spi_master *master)
अणु
	पूर्णांक ret;
	क्रमागत dma_slave_buswidth buswidth;
	काष्ठा dma_slave_config rx = अणुपूर्ण, tx = अणुपूर्ण;
	काष्ठा spi_imx_data *spi_imx = spi_master_get_devdata(master);

	चयन (spi_imx_bytes_per_word(spi_imx->bits_per_word)) अणु
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
	tx.dst_addr = spi_imx->base_phys + MXC_CSPITXDATA;
	tx.dst_addr_width = buswidth;
	tx.dst_maxburst = spi_imx->wml;
	ret = dmaengine_slave_config(master->dma_tx, &tx);
	अगर (ret) अणु
		dev_err(spi_imx->dev, "TX dma configuration failed with %d\n", ret);
		वापस ret;
	पूर्ण

	rx.direction = DMA_DEV_TO_MEM;
	rx.src_addr = spi_imx->base_phys + MXC_CSPIRXDATA;
	rx.src_addr_width = buswidth;
	rx.src_maxburst = spi_imx->wml;
	ret = dmaengine_slave_config(master->dma_rx, &rx);
	अगर (ret) अणु
		dev_err(spi_imx->dev, "RX dma configuration failed with %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spi_imx_setupxfer(काष्ठा spi_device *spi,
				 काष्ठा spi_transfer *t)
अणु
	काष्ठा spi_imx_data *spi_imx = spi_master_get_devdata(spi->master);

	अगर (!t)
		वापस 0;

	अगर (!t->speed_hz) अणु
		अगर (!spi->max_speed_hz) अणु
			dev_err(&spi->dev, "no speed_hz provided!\n");
			वापस -EINVAL;
		पूर्ण
		dev_dbg(&spi->dev, "using spi->max_speed_hz!\n");
		spi_imx->spi_bus_clk = spi->max_speed_hz;
	पूर्ण अन्यथा
		spi_imx->spi_bus_clk = t->speed_hz;

	spi_imx->bits_per_word = t->bits_per_word;

	/*
	 * Initialize the functions क्रम transfer. To transfer non byte-aligned
	 * words, we have to use multiple word-size bursts, we can't use
	 * dynamic_burst in that हाल.
	 */
	अगर (spi_imx->devtype_data->dynamic_burst && !spi_imx->slave_mode &&
	    (spi_imx->bits_per_word == 8 ||
	    spi_imx->bits_per_word == 16 ||
	    spi_imx->bits_per_word == 32)) अणु

		spi_imx->rx = spi_imx_buf_rx_swap;
		spi_imx->tx = spi_imx_buf_tx_swap;
		spi_imx->dynamic_burst = 1;

	पूर्ण अन्यथा अणु
		अगर (spi_imx->bits_per_word <= 8) अणु
			spi_imx->rx = spi_imx_buf_rx_u8;
			spi_imx->tx = spi_imx_buf_tx_u8;
		पूर्ण अन्यथा अगर (spi_imx->bits_per_word <= 16) अणु
			spi_imx->rx = spi_imx_buf_rx_u16;
			spi_imx->tx = spi_imx_buf_tx_u16;
		पूर्ण अन्यथा अणु
			spi_imx->rx = spi_imx_buf_rx_u32;
			spi_imx->tx = spi_imx_buf_tx_u32;
		पूर्ण
		spi_imx->dynamic_burst = 0;
	पूर्ण

	अगर (spi_imx_can_dma(spi_imx->bitbang.master, spi, t))
		spi_imx->usedma = true;
	अन्यथा
		spi_imx->usedma = false;

	अगर (is_imx53_ecspi(spi_imx) && spi_imx->slave_mode) अणु
		spi_imx->rx = mx53_ecspi_rx_slave;
		spi_imx->tx = mx53_ecspi_tx_slave;
		spi_imx->slave_burst = t->len;
	पूर्ण

	spi_imx->devtype_data->prepare_transfer(spi_imx, spi);

	वापस 0;
पूर्ण

अटल व्योम spi_imx_sdma_निकास(काष्ठा spi_imx_data *spi_imx)
अणु
	काष्ठा spi_master *master = spi_imx->bitbang.master;

	अगर (master->dma_rx) अणु
		dma_release_channel(master->dma_rx);
		master->dma_rx = शून्य;
	पूर्ण

	अगर (master->dma_tx) अणु
		dma_release_channel(master->dma_tx);
		master->dma_tx = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक spi_imx_sdma_init(काष्ठा device *dev, काष्ठा spi_imx_data *spi_imx,
			     काष्ठा spi_master *master)
अणु
	पूर्णांक ret;

	/* use pio mode क्रम i.mx6dl chip TKT238285 */
	अगर (of_machine_is_compatible("fsl,imx6dl"))
		वापस 0;

	spi_imx->wml = spi_imx->devtype_data->fअगरo_size / 2;

	/* Prepare क्रम TX DMA: */
	master->dma_tx = dma_request_chan(dev, "tx");
	अगर (IS_ERR(master->dma_tx)) अणु
		ret = PTR_ERR(master->dma_tx);
		dev_dbg(dev, "can't get the TX DMA channel, error %d!\n", ret);
		master->dma_tx = शून्य;
		जाओ err;
	पूर्ण

	/* Prepare क्रम RX : */
	master->dma_rx = dma_request_chan(dev, "rx");
	अगर (IS_ERR(master->dma_rx)) अणु
		ret = PTR_ERR(master->dma_rx);
		dev_dbg(dev, "can't get the RX DMA channel, error %d\n", ret);
		master->dma_rx = शून्य;
		जाओ err;
	पूर्ण

	init_completion(&spi_imx->dma_rx_completion);
	init_completion(&spi_imx->dma_tx_completion);
	master->can_dma = spi_imx_can_dma;
	master->max_dma_len = MAX_SDMA_BD_BYTES;
	spi_imx->bitbang.master->flags = SPI_MASTER_MUST_RX |
					 SPI_MASTER_MUST_TX;

	वापस 0;
err:
	spi_imx_sdma_निकास(spi_imx);
	वापस ret;
पूर्ण

अटल व्योम spi_imx_dma_rx_callback(व्योम *cookie)
अणु
	काष्ठा spi_imx_data *spi_imx = (काष्ठा spi_imx_data *)cookie;

	complete(&spi_imx->dma_rx_completion);
पूर्ण

अटल व्योम spi_imx_dma_tx_callback(व्योम *cookie)
अणु
	काष्ठा spi_imx_data *spi_imx = (काष्ठा spi_imx_data *)cookie;

	complete(&spi_imx->dma_tx_completion);
पूर्ण

अटल पूर्णांक spi_imx_calculate_समयout(काष्ठा spi_imx_data *spi_imx, पूर्णांक size)
अणु
	अचिन्हित दीर्घ समयout = 0;

	/* Time with actual data transfer and CS change delay related to HW */
	समयout = (8 + 4) * size / spi_imx->spi_bus_clk;

	/* Add extra second क्रम scheduler related activities */
	समयout += 1;

	/* Double calculated समयout */
	वापस msecs_to_jअगरfies(2 * समयout * MSEC_PER_SEC);
पूर्ण

अटल पूर्णांक spi_imx_dma_transfer(काष्ठा spi_imx_data *spi_imx,
				काष्ठा spi_transfer *transfer)
अणु
	काष्ठा dma_async_tx_descriptor *desc_tx, *desc_rx;
	अचिन्हित दीर्घ transfer_समयout;
	अचिन्हित दीर्घ समयout;
	काष्ठा spi_master *master = spi_imx->bitbang.master;
	काष्ठा sg_table *tx = &transfer->tx_sg, *rx = &transfer->rx_sg;
	काष्ठा scatterlist *last_sg = sg_last(rx->sgl, rx->nents);
	अचिन्हित पूर्णांक bytes_per_word, i;
	पूर्णांक ret;

	/* Get the right burst length from the last sg to ensure no tail data */
	bytes_per_word = spi_imx_bytes_per_word(transfer->bits_per_word);
	क्रम (i = spi_imx->devtype_data->fअगरo_size / 2; i > 0; i--) अणु
		अगर (!(sg_dma_len(last_sg) % (i * bytes_per_word)))
			अवरोध;
	पूर्ण
	/* Use 1 as wml in हाल no available burst length got */
	अगर (i == 0)
		i = 1;

	spi_imx->wml =  i;

	ret = spi_imx_dma_configure(master);
	अगर (ret)
		जाओ dma_failure_no_start;

	अगर (!spi_imx->devtype_data->setup_wml) अणु
		dev_err(spi_imx->dev, "No setup_wml()?\n");
		ret = -EINVAL;
		जाओ dma_failure_no_start;
	पूर्ण
	spi_imx->devtype_data->setup_wml(spi_imx);

	/*
	 * The TX DMA setup starts the transfer, so make sure RX is configured
	 * beक्रमe TX.
	 */
	desc_rx = dmaengine_prep_slave_sg(master->dma_rx,
				rx->sgl, rx->nents, DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc_rx) अणु
		ret = -EINVAL;
		जाओ dma_failure_no_start;
	पूर्ण

	desc_rx->callback = spi_imx_dma_rx_callback;
	desc_rx->callback_param = (व्योम *)spi_imx;
	dmaengine_submit(desc_rx);
	reinit_completion(&spi_imx->dma_rx_completion);
	dma_async_issue_pending(master->dma_rx);

	desc_tx = dmaengine_prep_slave_sg(master->dma_tx,
				tx->sgl, tx->nents, DMA_MEM_TO_DEV,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc_tx) अणु
		dmaengine_terminate_all(master->dma_tx);
		dmaengine_terminate_all(master->dma_rx);
		वापस -EINVAL;
	पूर्ण

	desc_tx->callback = spi_imx_dma_tx_callback;
	desc_tx->callback_param = (व्योम *)spi_imx;
	dmaengine_submit(desc_tx);
	reinit_completion(&spi_imx->dma_tx_completion);
	dma_async_issue_pending(master->dma_tx);

	transfer_समयout = spi_imx_calculate_समयout(spi_imx, transfer->len);

	/* Wait SDMA to finish the data transfer.*/
	समयout = रुको_क्रम_completion_समयout(&spi_imx->dma_tx_completion,
						transfer_समयout);
	अगर (!समयout) अणु
		dev_err(spi_imx->dev, "I/O Error in DMA TX\n");
		dmaengine_terminate_all(master->dma_tx);
		dmaengine_terminate_all(master->dma_rx);
		वापस -ETIMEDOUT;
	पूर्ण

	समयout = रुको_क्रम_completion_समयout(&spi_imx->dma_rx_completion,
					      transfer_समयout);
	अगर (!समयout) अणु
		dev_err(&master->dev, "I/O Error in DMA RX\n");
		spi_imx->devtype_data->reset(spi_imx);
		dmaengine_terminate_all(master->dma_rx);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस transfer->len;
/* fallback to pio */
dma_failure_no_start:
	transfer->error |= SPI_TRANS_FAIL_NO_START;
	वापस ret;
पूर्ण

अटल पूर्णांक spi_imx_pio_transfer(काष्ठा spi_device *spi,
				काष्ठा spi_transfer *transfer)
अणु
	काष्ठा spi_imx_data *spi_imx = spi_master_get_devdata(spi->master);
	अचिन्हित दीर्घ transfer_समयout;
	अचिन्हित दीर्घ समयout;

	spi_imx->tx_buf = transfer->tx_buf;
	spi_imx->rx_buf = transfer->rx_buf;
	spi_imx->count = transfer->len;
	spi_imx->txfअगरo = 0;
	spi_imx->reमुख्यder = 0;

	reinit_completion(&spi_imx->xfer_करोne);

	spi_imx_push(spi_imx);

	spi_imx->devtype_data->पूर्णांकctrl(spi_imx, MXC_INT_TE);

	transfer_समयout = spi_imx_calculate_समयout(spi_imx, transfer->len);

	समयout = रुको_क्रम_completion_समयout(&spi_imx->xfer_करोne,
					      transfer_समयout);
	अगर (!समयout) अणु
		dev_err(&spi->dev, "I/O Error in PIO\n");
		spi_imx->devtype_data->reset(spi_imx);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस transfer->len;
पूर्ण

अटल पूर्णांक spi_imx_pio_transfer_slave(काष्ठा spi_device *spi,
				      काष्ठा spi_transfer *transfer)
अणु
	काष्ठा spi_imx_data *spi_imx = spi_master_get_devdata(spi->master);
	पूर्णांक ret = transfer->len;

	अगर (is_imx53_ecspi(spi_imx) &&
	    transfer->len > MX53_MAX_TRANSFER_BYTES) अणु
		dev_err(&spi->dev, "Transaction too big, max size is %d bytes\n",
			MX53_MAX_TRANSFER_BYTES);
		वापस -EMSGSIZE;
	पूर्ण

	spi_imx->tx_buf = transfer->tx_buf;
	spi_imx->rx_buf = transfer->rx_buf;
	spi_imx->count = transfer->len;
	spi_imx->txfअगरo = 0;
	spi_imx->reमुख्यder = 0;

	reinit_completion(&spi_imx->xfer_करोne);
	spi_imx->slave_पातed = false;

	spi_imx_push(spi_imx);

	spi_imx->devtype_data->पूर्णांकctrl(spi_imx, MXC_INT_TE | MXC_INT_RDR);

	अगर (रुको_क्रम_completion_पूर्णांकerruptible(&spi_imx->xfer_करोne) ||
	    spi_imx->slave_पातed) अणु
		dev_dbg(&spi->dev, "interrupted\n");
		ret = -EINTR;
	पूर्ण

	/* ecspi has a HW issue when works in Slave mode,
	 * after 64 words writtern to TXFIFO, even TXFIFO becomes empty,
	 * ECSPI_TXDATA keeps shअगरt out the last word data,
	 * so we have to disable ECSPI when in slave mode after the
	 * transfer completes
	 */
	अगर (spi_imx->devtype_data->disable)
		spi_imx->devtype_data->disable(spi_imx);

	वापस ret;
पूर्ण

अटल पूर्णांक spi_imx_transfer(काष्ठा spi_device *spi,
				काष्ठा spi_transfer *transfer)
अणु
	काष्ठा spi_imx_data *spi_imx = spi_master_get_devdata(spi->master);

	transfer->effective_speed_hz = spi_imx->spi_bus_clk;

	/* flush rxfअगरo beक्रमe transfer */
	जबतक (spi_imx->devtype_data->rx_available(spi_imx))
		पढ़ोl(spi_imx->base + MXC_CSPIRXDATA);

	अगर (spi_imx->slave_mode)
		वापस spi_imx_pio_transfer_slave(spi, transfer);

	अगर (spi_imx->usedma)
		वापस spi_imx_dma_transfer(spi_imx, transfer);

	वापस spi_imx_pio_transfer(spi, transfer);
पूर्ण

अटल पूर्णांक spi_imx_setup(काष्ठा spi_device *spi)
अणु
	dev_dbg(&spi->dev, "%s: mode %d, %u bpw, %d hz\n", __func__,
		 spi->mode, spi->bits_per_word, spi->max_speed_hz);

	वापस 0;
पूर्ण

अटल व्योम spi_imx_cleanup(काष्ठा spi_device *spi)
अणु
पूर्ण

अटल पूर्णांक
spi_imx_prepare_message(काष्ठा spi_master *master, काष्ठा spi_message *msg)
अणु
	काष्ठा spi_imx_data *spi_imx = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(spi_imx->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(spi_imx->dev);
		dev_err(spi_imx->dev, "failed to enable clock\n");
		वापस ret;
	पूर्ण

	ret = spi_imx->devtype_data->prepare_message(spi_imx, msg);
	अगर (ret) अणु
		pm_runसमय_mark_last_busy(spi_imx->dev);
		pm_runसमय_put_स्वतःsuspend(spi_imx->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
spi_imx_unprepare_message(काष्ठा spi_master *master, काष्ठा spi_message *msg)
अणु
	काष्ठा spi_imx_data *spi_imx = spi_master_get_devdata(master);

	pm_runसमय_mark_last_busy(spi_imx->dev);
	pm_runसमय_put_स्वतःsuspend(spi_imx->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक spi_imx_slave_पात(काष्ठा spi_master *master)
अणु
	काष्ठा spi_imx_data *spi_imx = spi_master_get_devdata(master);

	spi_imx->slave_पातed = true;
	complete(&spi_imx->xfer_करोne);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_imx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा spi_master *master;
	काष्ठा spi_imx_data *spi_imx;
	काष्ठा resource *res;
	पूर्णांक ret, irq, spi_drctl;
	स्थिर काष्ठा spi_imx_devtype_data *devtype_data =
			of_device_get_match_data(&pdev->dev);
	bool slave_mode;
	u32 val;

	slave_mode = devtype_data->has_slavemode &&
			of_property_पढ़ो_bool(np, "spi-slave");
	अगर (slave_mode)
		master = spi_alloc_slave(&pdev->dev,
					 माप(काष्ठा spi_imx_data));
	अन्यथा
		master = spi_alloc_master(&pdev->dev,
					  माप(काष्ठा spi_imx_data));
	अगर (!master)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32(np, "fsl,spi-rdy-drctl", &spi_drctl);
	अगर ((ret < 0) || (spi_drctl >= 0x3)) अणु
		/* '11' is reserved */
		spi_drctl = 0;
	पूर्ण

	platक्रमm_set_drvdata(pdev, master);

	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(1, 32);
	master->bus_num = np ? -1 : pdev->id;
	master->use_gpio_descriptors = true;

	spi_imx = spi_master_get_devdata(master);
	spi_imx->bitbang.master = master;
	spi_imx->dev = &pdev->dev;
	spi_imx->slave_mode = slave_mode;

	spi_imx->devtype_data = devtype_data;

	/*
	 * Get number of chip selects from device properties. This can be
	 * coming from device tree or boardfiles, अगर it is not defined,
	 * a शेष value of 3 chip selects will be used, as all the legacy
	 * board files have <= 3 chip selects.
	 */
	अगर (!device_property_पढ़ो_u32(&pdev->dev, "num-cs", &val))
		master->num_chipselect = val;
	अन्यथा
		master->num_chipselect = 3;

	spi_imx->bitbang.setup_transfer = spi_imx_setupxfer;
	spi_imx->bitbang.txrx_bufs = spi_imx_transfer;
	spi_imx->bitbang.master->setup = spi_imx_setup;
	spi_imx->bitbang.master->cleanup = spi_imx_cleanup;
	spi_imx->bitbang.master->prepare_message = spi_imx_prepare_message;
	spi_imx->bitbang.master->unprepare_message = spi_imx_unprepare_message;
	spi_imx->bitbang.master->slave_पात = spi_imx_slave_पात;
	spi_imx->bitbang.master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH \
					     | SPI_NO_CS;
	अगर (is_imx35_cspi(spi_imx) || is_imx51_ecspi(spi_imx) ||
	    is_imx53_ecspi(spi_imx))
		spi_imx->bitbang.master->mode_bits |= SPI_LOOP | SPI_READY;

	spi_imx->spi_drctl = spi_drctl;

	init_completion(&spi_imx->xfer_करोne);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	spi_imx->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(spi_imx->base)) अणु
		ret = PTR_ERR(spi_imx->base);
		जाओ out_master_put;
	पूर्ण
	spi_imx->base_phys = res->start;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ out_master_put;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, spi_imx_isr, 0,
			       dev_name(&pdev->dev), spi_imx);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't get irq%d: %d\n", irq, ret);
		जाओ out_master_put;
	पूर्ण

	spi_imx->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(spi_imx->clk_ipg)) अणु
		ret = PTR_ERR(spi_imx->clk_ipg);
		जाओ out_master_put;
	पूर्ण

	spi_imx->clk_per = devm_clk_get(&pdev->dev, "per");
	अगर (IS_ERR(spi_imx->clk_per)) अणु
		ret = PTR_ERR(spi_imx->clk_per);
		जाओ out_master_put;
	पूर्ण

	ret = clk_prepare_enable(spi_imx->clk_per);
	अगर (ret)
		जाओ out_master_put;

	ret = clk_prepare_enable(spi_imx->clk_ipg);
	अगर (ret)
		जाओ out_put_per;

	pm_runसमय_set_स्वतःsuspend_delay(spi_imx->dev, MXC_RPM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(spi_imx->dev);
	pm_runसमय_get_noresume(spi_imx->dev);
	pm_runसमय_set_active(spi_imx->dev);
	pm_runसमय_enable(spi_imx->dev);

	spi_imx->spi_clk = clk_get_rate(spi_imx->clk_per);
	/*
	 * Only validated on i.mx35 and i.mx6 now, can हटाओ the स्थिरraपूर्णांक
	 * अगर validated on other chips.
	 */
	अगर (spi_imx->devtype_data->has_dmamode) अणु
		ret = spi_imx_sdma_init(&pdev->dev, spi_imx, master);
		अगर (ret == -EPROBE_DEFER)
			जाओ out_runसमय_pm_put;

		अगर (ret < 0)
			dev_dbg(&pdev->dev, "dma setup error %d, use pio\n",
				ret);
	पूर्ण

	spi_imx->devtype_data->reset(spi_imx);

	spi_imx->devtype_data->पूर्णांकctrl(spi_imx, 0);

	master->dev.of_node = pdev->dev.of_node;
	ret = spi_bitbang_start(&spi_imx->bitbang);
	अगर (ret) अणु
		dev_err_probe(&pdev->dev, ret, "bitbang start failed\n");
		जाओ out_bitbang_start;
	पूर्ण

	pm_runसमय_mark_last_busy(spi_imx->dev);
	pm_runसमय_put_स्वतःsuspend(spi_imx->dev);

	वापस ret;

out_bitbang_start:
	अगर (spi_imx->devtype_data->has_dmamode)
		spi_imx_sdma_निकास(spi_imx);
out_runसमय_pm_put:
	pm_runसमय_करोnt_use_स्वतःsuspend(spi_imx->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_disable(spi_imx->dev);

	clk_disable_unprepare(spi_imx->clk_ipg);
out_put_per:
	clk_disable_unprepare(spi_imx->clk_per);
out_master_put:
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल पूर्णांक spi_imx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा spi_imx_data *spi_imx = spi_master_get_devdata(master);
	पूर्णांक ret;

	spi_bitbang_stop(&spi_imx->bitbang);

	ret = pm_runसमय_get_sync(spi_imx->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(spi_imx->dev);
		dev_err(spi_imx->dev, "failed to enable clock\n");
		वापस ret;
	पूर्ण

	ग_लिखोl(0, spi_imx->base + MXC_CSPICTRL);

	pm_runसमय_करोnt_use_स्वतःsuspend(spi_imx->dev);
	pm_runसमय_put_sync(spi_imx->dev);
	pm_runसमय_disable(spi_imx->dev);

	spi_imx_sdma_निकास(spi_imx);
	spi_master_put(master);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused spi_imx_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा spi_imx_data *spi_imx;
	पूर्णांक ret;

	spi_imx = spi_master_get_devdata(master);

	ret = clk_prepare_enable(spi_imx->clk_per);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(spi_imx->clk_ipg);
	अगर (ret) अणु
		clk_disable_unprepare(spi_imx->clk_per);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused spi_imx_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा spi_imx_data *spi_imx;

	spi_imx = spi_master_get_devdata(master);

	clk_disable_unprepare(spi_imx->clk_per);
	clk_disable_unprepare(spi_imx->clk_ipg);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused spi_imx_suspend(काष्ठा device *dev)
अणु
	pinctrl_pm_select_sleep_state(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused spi_imx_resume(काष्ठा device *dev)
अणु
	pinctrl_pm_select_शेष_state(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops imx_spi_pm = अणु
	SET_RUNTIME_PM_OPS(spi_imx_runसमय_suspend,
				spi_imx_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(spi_imx_suspend, spi_imx_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver spi_imx_driver = अणु
	.driver = अणु
		   .name = DRIVER_NAME,
		   .of_match_table = spi_imx_dt_ids,
		   .pm = &imx_spi_pm,
	पूर्ण,
	.probe = spi_imx_probe,
	.हटाओ = spi_imx_हटाओ,
पूर्ण;
module_platक्रमm_driver(spi_imx_driver);

MODULE_DESCRIPTION("i.MX SPI Controller driver");
MODULE_AUTHOR("Sascha Hauer, Pengutronix");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
