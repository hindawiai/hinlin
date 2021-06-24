<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  STM32 ALSA SoC Digital Audio Interface (I2S) driver.
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author(s): Olivier Moysan <olivier.moysan@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/spinlock.h>

#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>

#घोषणा STM32_I2S_CR1_REG	0x0
#घोषणा STM32_I2S_CFG1_REG	0x08
#घोषणा STM32_I2S_CFG2_REG	0x0C
#घोषणा STM32_I2S_IER_REG	0x10
#घोषणा STM32_I2S_SR_REG	0x14
#घोषणा STM32_I2S_IFCR_REG	0x18
#घोषणा STM32_I2S_TXDR_REG	0X20
#घोषणा STM32_I2S_RXDR_REG	0x30
#घोषणा STM32_I2S_CGFR_REG	0X50
#घोषणा STM32_I2S_HWCFGR_REG	0x3F0
#घोषणा STM32_I2S_VERR_REG	0x3F4
#घोषणा STM32_I2S_IPIDR_REG	0x3F8
#घोषणा STM32_I2S_SIDR_REG	0x3FC

/* Bit definition क्रम SPI2S_CR1 रेजिस्टर */
#घोषणा I2S_CR1_SPE		BIT(0)
#घोषणा I2S_CR1_CSTART		BIT(9)
#घोषणा I2S_CR1_CSUSP		BIT(10)
#घोषणा I2S_CR1_HDसूची		BIT(11)
#घोषणा I2S_CR1_SSI		BIT(12)
#घोषणा I2S_CR1_CRC33_17	BIT(13)
#घोषणा I2S_CR1_RCRCI		BIT(14)
#घोषणा I2S_CR1_TCRCI		BIT(15)

/* Bit definition क्रम SPI_CFG2 रेजिस्टर */
#घोषणा I2S_CFG2_IOSWP_SHIFT	15
#घोषणा I2S_CFG2_IOSWP		BIT(I2S_CFG2_IOSWP_SHIFT)
#घोषणा I2S_CFG2_LSBFRST	BIT(23)
#घोषणा I2S_CFG2_AFCNTR		BIT(31)

/* Bit definition क्रम SPI_CFG1 रेजिस्टर */
#घोषणा I2S_CFG1_FTHVL_SHIFT	5
#घोषणा I2S_CFG1_FTHVL_MASK	GENMASK(8, I2S_CFG1_FTHVL_SHIFT)
#घोषणा I2S_CFG1_FTHVL_SET(x)	((x) << I2S_CFG1_FTHVL_SHIFT)

#घोषणा I2S_CFG1_TXDMAEN	BIT(15)
#घोषणा I2S_CFG1_RXDMAEN	BIT(14)

/* Bit definition क्रम SPI2S_IER रेजिस्टर */
#घोषणा I2S_IER_RXPIE		BIT(0)
#घोषणा I2S_IER_TXPIE		BIT(1)
#घोषणा I2S_IER_DPXPIE		BIT(2)
#घोषणा I2S_IER_EOTIE		BIT(3)
#घोषणा I2S_IER_TXTFIE		BIT(4)
#घोषणा I2S_IER_UDRIE		BIT(5)
#घोषणा I2S_IER_OVRIE		BIT(6)
#घोषणा I2S_IER_CRCEIE		BIT(7)
#घोषणा I2S_IER_TIFREIE		BIT(8)
#घोषणा I2S_IER_MODFIE		BIT(9)
#घोषणा I2S_IER_TSERFIE		BIT(10)

/* Bit definition क्रम SPI2S_SR रेजिस्टर */
#घोषणा I2S_SR_RXP		BIT(0)
#घोषणा I2S_SR_TXP		BIT(1)
#घोषणा I2S_SR_DPXP		BIT(2)
#घोषणा I2S_SR_EOT		BIT(3)
#घोषणा I2S_SR_TXTF		BIT(4)
#घोषणा I2S_SR_UDR		BIT(5)
#घोषणा I2S_SR_OVR		BIT(6)
#घोषणा I2S_SR_CRCERR		BIT(7)
#घोषणा I2S_SR_TIFRE		BIT(8)
#घोषणा I2S_SR_MODF		BIT(9)
#घोषणा I2S_SR_TSERF		BIT(10)
#घोषणा I2S_SR_SUSP		BIT(11)
#घोषणा I2S_SR_TXC		BIT(12)
#घोषणा I2S_SR_RXPLVL		GENMASK(14, 13)
#घोषणा I2S_SR_RXWNE		BIT(15)

#घोषणा I2S_SR_MASK		GENMASK(15, 0)

/* Bit definition क्रम SPI_IFCR रेजिस्टर */
#घोषणा I2S_IFCR_EOTC		BIT(3)
#घोषणा I2S_IFCR_TXTFC		BIT(4)
#घोषणा I2S_IFCR_UDRC		BIT(5)
#घोषणा I2S_IFCR_OVRC		BIT(6)
#घोषणा I2S_IFCR_CRCEC		BIT(7)
#घोषणा I2S_IFCR_TIFREC		BIT(8)
#घोषणा I2S_IFCR_MODFC		BIT(9)
#घोषणा I2S_IFCR_TSERFC		BIT(10)
#घोषणा I2S_IFCR_SUSPC		BIT(11)

#घोषणा I2S_IFCR_MASK		GENMASK(11, 3)

/* Bit definition क्रम SPI_I2SCGFR रेजिस्टर */
#घोषणा I2S_CGFR_I2SMOD		BIT(0)

#घोषणा I2S_CGFR_I2SCFG_SHIFT	1
#घोषणा I2S_CGFR_I2SCFG_MASK	GENMASK(3, I2S_CGFR_I2SCFG_SHIFT)
#घोषणा I2S_CGFR_I2SCFG_SET(x)	((x) << I2S_CGFR_I2SCFG_SHIFT)

#घोषणा I2S_CGFR_I2SSTD_SHIFT	4
#घोषणा I2S_CGFR_I2SSTD_MASK	GENMASK(5, I2S_CGFR_I2SSTD_SHIFT)
#घोषणा I2S_CGFR_I2SSTD_SET(x)	((x) << I2S_CGFR_I2SSTD_SHIFT)

#घोषणा I2S_CGFR_PCMSYNC	BIT(7)

#घोषणा I2S_CGFR_DATLEN_SHIFT	8
#घोषणा I2S_CGFR_DATLEN_MASK	GENMASK(9, I2S_CGFR_DATLEN_SHIFT)
#घोषणा I2S_CGFR_DATLEN_SET(x)	((x) << I2S_CGFR_DATLEN_SHIFT)

#घोषणा I2S_CGFR_CHLEN_SHIFT	10
#घोषणा I2S_CGFR_CHLEN		BIT(I2S_CGFR_CHLEN_SHIFT)
#घोषणा I2S_CGFR_CKPOL		BIT(11)
#घोषणा I2S_CGFR_FIXCH		BIT(12)
#घोषणा I2S_CGFR_WSINV		BIT(13)
#घोषणा I2S_CGFR_DATFMT		BIT(14)

#घोषणा I2S_CGFR_I2SDIV_SHIFT	16
#घोषणा I2S_CGFR_I2SDIV_BIT_H	23
#घोषणा I2S_CGFR_I2SDIV_MASK	GENMASK(I2S_CGFR_I2SDIV_BIT_H,\
				I2S_CGFR_I2SDIV_SHIFT)
#घोषणा I2S_CGFR_I2SDIV_SET(x)	((x) << I2S_CGFR_I2SDIV_SHIFT)
#घोषणा	I2S_CGFR_I2SDIV_MAX	((1 << (I2S_CGFR_I2SDIV_BIT_H -\
				I2S_CGFR_I2SDIV_SHIFT)) - 1)

#घोषणा I2S_CGFR_ODD_SHIFT	24
#घोषणा I2S_CGFR_ODD		BIT(I2S_CGFR_ODD_SHIFT)
#घोषणा I2S_CGFR_MCKOE		BIT(25)

/* Registers below apply to I2S version 1.1 and more */

/* Bit definition क्रम SPI_HWCFGR रेजिस्टर */
#घोषणा I2S_HWCFGR_I2S_SUPPORT_MASK	GENMASK(15, 12)

/* Bit definition क्रम SPI_VERR रेजिस्टर */
#घोषणा I2S_VERR_MIN_MASK	GENMASK(3, 0)
#घोषणा I2S_VERR_MAJ_MASK	GENMASK(7, 4)

/* Bit definition क्रम SPI_IPIDR रेजिस्टर */
#घोषणा I2S_IPIDR_ID_MASK	GENMASK(31, 0)

/* Bit definition क्रम SPI_SIDR रेजिस्टर */
#घोषणा I2S_SIDR_ID_MASK	GENMASK(31, 0)

#घोषणा I2S_IPIDR_NUMBER	0x00130022

क्रमागत i2s_master_mode अणु
	I2S_MS_NOT_SET,
	I2S_MS_MASTER,
	I2S_MS_SLAVE,
पूर्ण;

क्रमागत i2s_mode अणु
	I2S_I2SMOD_TX_SLAVE,
	I2S_I2SMOD_RX_SLAVE,
	I2S_I2SMOD_TX_MASTER,
	I2S_I2SMOD_RX_MASTER,
	I2S_I2SMOD_FD_SLAVE,
	I2S_I2SMOD_FD_MASTER,
पूर्ण;

क्रमागत i2s_fअगरo_th अणु
	I2S_FIFO_TH_NONE,
	I2S_FIFO_TH_ONE_QUARTER,
	I2S_FIFO_TH_HALF,
	I2S_FIFO_TH_THREE_QUARTER,
	I2S_FIFO_TH_FULL,
पूर्ण;

क्रमागत i2s_std अणु
	I2S_STD_I2S,
	I2S_STD_LEFT_J,
	I2S_STD_RIGHT_J,
	I2S_STD_DSP,
पूर्ण;

क्रमागत i2s_datlen अणु
	I2S_I2SMOD_DATLEN_16,
	I2S_I2SMOD_DATLEN_24,
	I2S_I2SMOD_DATLEN_32,
पूर्ण;

#घोषणा STM32_I2S_FIFO_SIZE		16

#घोषणा STM32_I2S_IS_MASTER(x)		((x)->ms_flg == I2S_MS_MASTER)
#घोषणा STM32_I2S_IS_SLAVE(x)		((x)->ms_flg == I2S_MS_SLAVE)

#घोषणा STM32_I2S_NAME_LEN		32
#घोषणा STM32_I2S_RATE_11K		11025

/**
 * काष्ठा sपंचांग32_i2s_data - निजी data of I2S
 * @regmap_conf: I2S रेजिस्टर map configuration poपूर्णांकer
 * @regmap: I2S रेजिस्टर map poपूर्णांकer
 * @pdev: device data poपूर्णांकer
 * @dai_drv: DAI driver poपूर्णांकer
 * @dma_data_tx: dma configuration data क्रम tx channel
 * @dma_data_rx: dma configuration data क्रम tx channel
 * @substream: PCM substream data poपूर्णांकer
 * @i2sclk: kernel घड़ी feeding the I2S घड़ी generator
 * @i2smclk: master घड़ी from I2S mclk provider
 * @pclk: peripheral घड़ी driving bus पूर्णांकerface
 * @x8kclk: I2S parent घड़ी क्रम sampling frequencies multiple of 8kHz
 * @x11kclk: I2S parent घड़ी क्रम sampling frequencies multiple of 11kHz
 * @base:  mmio रेजिस्टर base भव address
 * @phys_addr: I2S रेजिस्टरs physical base address
 * @lock_fd: lock to manage race conditions in full duplex mode
 * @irq_lock: prevent race condition with IRQ
 * @mclk_rate: master घड़ी frequency (Hz)
 * @fmt: DAI protocol
 * @भागider: prescaler भागision ratio
 * @भाग: prescaler भाग field
 * @odd: prescaler odd field
 * @refcount: keep count of खोलोed streams on I2S
 * @ms_flg: master mode flag.
 */
काष्ठा sपंचांग32_i2s_data अणु
	स्थिर काष्ठा regmap_config *regmap_conf;
	काष्ठा regmap *regmap;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा snd_soc_dai_driver *dai_drv;
	काष्ठा snd_dmaengine_dai_dma_data dma_data_tx;
	काष्ठा snd_dmaengine_dai_dma_data dma_data_rx;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा clk *i2sclk;
	काष्ठा clk *i2smclk;
	काष्ठा clk *pclk;
	काष्ठा clk *x8kclk;
	काष्ठा clk *x11kclk;
	व्योम __iomem *base;
	dma_addr_t phys_addr;
	spinlock_t lock_fd; /* Manage race conditions क्रम full duplex */
	spinlock_t irq_lock; /* used to prevent race condition with IRQ */
	अचिन्हित पूर्णांक mclk_rate;
	अचिन्हित पूर्णांक fmt;
	अचिन्हित पूर्णांक भागider;
	अचिन्हित पूर्णांक भाग;
	bool odd;
	पूर्णांक refcount;
	पूर्णांक ms_flg;
पूर्ण;

काष्ठा sपंचांग32_i2smclk_data अणु
	काष्ठा clk_hw hw;
	अचिन्हित दीर्घ freq;
	काष्ठा sपंचांग32_i2s_data *i2s_data;
पूर्ण;

#घोषणा to_mclk_data(_hw) container_of(_hw, काष्ठा sपंचांग32_i2smclk_data, hw)

अटल पूर्णांक sपंचांग32_i2s_calc_clk_भाग(काष्ठा sपंचांग32_i2s_data *i2s,
				  अचिन्हित दीर्घ input_rate,
				  अचिन्हित दीर्घ output_rate)
अणु
	अचिन्हित पूर्णांक ratio, भाग, भागider = 1;
	bool odd;

	ratio = DIV_ROUND_CLOSEST(input_rate, output_rate);

	/* Check the parity of the भागider */
	odd = ratio & 0x1;

	/* Compute the भाग prescaler */
	भाग = ratio >> 1;

	/* If भाग is 0 actual भागider is 1 */
	अगर (भाग) अणु
		भागider = ((2 * भाग) + odd);
		dev_dbg(&i2s->pdev->dev, "Divider: 2*%d(div)+%d(odd) = %d\n",
			भाग, odd, भागider);
	पूर्ण

	/* Division by three is not allowed by I2S prescaler */
	अगर ((भाग == 1 && odd) || भाग > I2S_CGFR_I2SDIV_MAX) अणु
		dev_err(&i2s->pdev->dev, "Wrong divider setting\n");
		वापस -EINVAL;
	पूर्ण

	अगर (input_rate % भागider)
		dev_dbg(&i2s->pdev->dev,
			"Rate not accurate. requested (%ld), actual (%ld)\n",
			output_rate, input_rate / भागider);

	i2s->भाग = भाग;
	i2s->odd = odd;
	i2s->भागider = भागider;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_set_clk_भाग(काष्ठा sपंचांग32_i2s_data *i2s)
अणु
	u32 cgfr, cgfr_mask;

	cgfr = I2S_CGFR_I2SDIV_SET(i2s->भाग) | (i2s->odd << I2S_CGFR_ODD_SHIFT);
	cgfr_mask = I2S_CGFR_I2SDIV_MASK | I2S_CGFR_ODD;

	वापस regmap_update_bits(i2s->regmap, STM32_I2S_CGFR_REG,
				  cgfr_mask, cgfr);
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_set_parent_घड़ी(काष्ठा sपंचांग32_i2s_data *i2s,
				      अचिन्हित पूर्णांक rate)
अणु
	काष्ठा platक्रमm_device *pdev = i2s->pdev;
	काष्ठा clk *parent_clk;
	पूर्णांक ret;

	अगर (!(rate % STM32_I2S_RATE_11K))
		parent_clk = i2s->x11kclk;
	अन्यथा
		parent_clk = i2s->x8kclk;

	ret = clk_set_parent(i2s->i2sclk, parent_clk);
	अगर (ret)
		dev_err(&pdev->dev,
			"Error %d setting i2sclk parent clock\n", ret);

	वापस ret;
पूर्ण

अटल दीर्घ sपंचांग32_i2smclk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *prate)
अणु
	काष्ठा sपंचांग32_i2smclk_data *mclk = to_mclk_data(hw);
	काष्ठा sपंचांग32_i2s_data *i2s = mclk->i2s_data;
	पूर्णांक ret;

	ret = sपंचांग32_i2s_calc_clk_भाग(i2s, *prate, rate);
	अगर (ret)
		वापस ret;

	mclk->freq = *prate / i2s->भागider;

	वापस mclk->freq;
पूर्ण

अटल अचिन्हित दीर्घ sपंचांग32_i2smclk_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sपंचांग32_i2smclk_data *mclk = to_mclk_data(hw);

	वापस mclk->freq;
पूर्ण

अटल पूर्णांक sपंचांग32_i2smclk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sपंचांग32_i2smclk_data *mclk = to_mclk_data(hw);
	काष्ठा sपंचांग32_i2s_data *i2s = mclk->i2s_data;
	पूर्णांक ret;

	ret = sपंचांग32_i2s_calc_clk_भाग(i2s, parent_rate, rate);
	अगर (ret)
		वापस ret;

	ret = sपंचांग32_i2s_set_clk_भाग(i2s);
	अगर (ret)
		वापस ret;

	mclk->freq = rate;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_i2smclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_i2smclk_data *mclk = to_mclk_data(hw);
	काष्ठा sपंचांग32_i2s_data *i2s = mclk->i2s_data;

	dev_dbg(&i2s->pdev->dev, "Enable master clock\n");

	वापस regmap_update_bits(i2s->regmap, STM32_I2S_CGFR_REG,
				    I2S_CGFR_MCKOE, I2S_CGFR_MCKOE);
पूर्ण

अटल व्योम sपंचांग32_i2smclk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_i2smclk_data *mclk = to_mclk_data(hw);
	काष्ठा sपंचांग32_i2s_data *i2s = mclk->i2s_data;

	dev_dbg(&i2s->pdev->dev, "Disable master clock\n");

	regmap_update_bits(i2s->regmap, STM32_I2S_CGFR_REG, I2S_CGFR_MCKOE, 0);
पूर्ण

अटल स्थिर काष्ठा clk_ops mclk_ops = अणु
	.enable = sपंचांग32_i2smclk_enable,
	.disable = sपंचांग32_i2smclk_disable,
	.recalc_rate = sपंचांग32_i2smclk_recalc_rate,
	.round_rate = sपंचांग32_i2smclk_round_rate,
	.set_rate = sपंचांग32_i2smclk_set_rate,
पूर्ण;

अटल पूर्णांक sपंचांग32_i2s_add_mclk_provider(काष्ठा sपंचांग32_i2s_data *i2s)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा sपंचांग32_i2smclk_data *mclk;
	काष्ठा device *dev = &i2s->pdev->dev;
	स्थिर अक्षर *pname = __clk_get_name(i2s->i2sclk);
	अक्षर *mclk_name, *p, *s = (अक्षर *)pname;
	पूर्णांक ret, i = 0;

	mclk = devm_kzalloc(dev, माप(*mclk), GFP_KERNEL);
	अगर (!mclk)
		वापस -ENOMEM;

	mclk_name = devm_kसुस्मृति(dev, माप(अक्षर),
				 STM32_I2S_NAME_LEN, GFP_KERNEL);
	अगर (!mclk_name)
		वापस -ENOMEM;

	/*
	 * Forge mclk घड़ी name from parent घड़ी name and suffix.
	 * String after "_" अक्षर is stripped in parent name.
	 */
	p = mclk_name;
	जबतक (*s && *s != '_' && (i < (STM32_I2S_NAME_LEN - 7))) अणु
		*p++ = *s++;
		i++;
	पूर्ण
	म_जोड़ो(p, "_mclk");

	mclk->hw.init = CLK_HW_INIT(mclk_name, pname, &mclk_ops, 0);
	mclk->i2s_data = i2s;
	hw = &mclk->hw;

	dev_dbg(dev, "Register master clock %s\n", mclk_name);
	ret = devm_clk_hw_रेजिस्टर(&i2s->pdev->dev, hw);
	अगर (ret) अणु
		dev_err(dev, "mclk register fails with error %d\n", ret);
		वापस ret;
	पूर्ण
	i2s->i2smclk = hw->clk;

	/* रेजिस्टर mclk provider */
	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get, hw);
पूर्ण

अटल irqवापस_t sपंचांग32_i2s_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s = (काष्ठा sपंचांग32_i2s_data *)devid;
	काष्ठा platक्रमm_device *pdev = i2s->pdev;
	u32 sr, ier;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	regmap_पढ़ो(i2s->regmap, STM32_I2S_SR_REG, &sr);
	regmap_पढ़ो(i2s->regmap, STM32_I2S_IER_REG, &ier);

	flags = sr & ier;
	अगर (!flags) अणु
		dev_dbg(&pdev->dev, "Spurious IRQ sr=0x%08x, ier=0x%08x\n",
			sr, ier);
		वापस IRQ_NONE;
	पूर्ण

	regmap_ग_लिखो_bits(i2s->regmap, STM32_I2S_IFCR_REG,
			  I2S_IFCR_MASK, flags);

	अगर (flags & I2S_SR_OVR) अणु
		dev_dbg(&pdev->dev, "Overrun\n");
		err = 1;
	पूर्ण

	अगर (flags & I2S_SR_UDR) अणु
		dev_dbg(&pdev->dev, "Underrun\n");
		err = 1;
	पूर्ण

	अगर (flags & I2S_SR_TIFRE)
		dev_dbg(&pdev->dev, "Frame error\n");

	spin_lock(&i2s->irq_lock);
	अगर (err && i2s->substream)
		snd_pcm_stop_xrun(i2s->substream);
	spin_unlock(&i2s->irq_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल bool sपंचांग32_i2s_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STM32_I2S_CR1_REG:
	हाल STM32_I2S_CFG1_REG:
	हाल STM32_I2S_CFG2_REG:
	हाल STM32_I2S_IER_REG:
	हाल STM32_I2S_SR_REG:
	हाल STM32_I2S_RXDR_REG:
	हाल STM32_I2S_CGFR_REG:
	हाल STM32_I2S_HWCFGR_REG:
	हाल STM32_I2S_VERR_REG:
	हाल STM32_I2S_IPIDR_REG:
	हाल STM32_I2S_SIDR_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool sपंचांग32_i2s_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STM32_I2S_SR_REG:
	हाल STM32_I2S_RXDR_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool sपंचांग32_i2s_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STM32_I2S_CR1_REG:
	हाल STM32_I2S_CFG1_REG:
	हाल STM32_I2S_CFG2_REG:
	हाल STM32_I2S_IER_REG:
	हाल STM32_I2S_IFCR_REG:
	हाल STM32_I2S_TXDR_REG:
	हाल STM32_I2S_CGFR_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	u32 cgfr;
	u32 cgfr_mask =  I2S_CGFR_I2SSTD_MASK | I2S_CGFR_CKPOL |
			 I2S_CGFR_WSINV | I2S_CGFR_I2SCFG_MASK;

	dev_dbg(cpu_dai->dev, "fmt %x\n", fmt);

	/*
	 * winv = 0 : शेष behavior (high/low) क्रम all standards
	 * ckpol = 0 क्रम all standards.
	 */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		cgfr = I2S_CGFR_I2SSTD_SET(I2S_STD_I2S);
		अवरोध;
	हाल SND_SOC_DAIFMT_MSB:
		cgfr = I2S_CGFR_I2SSTD_SET(I2S_STD_LEFT_J);
		अवरोध;
	हाल SND_SOC_DAIFMT_LSB:
		cgfr = I2S_CGFR_I2SSTD_SET(I2S_STD_RIGHT_J);
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		cgfr = I2S_CGFR_I2SSTD_SET(I2S_STD_DSP);
		अवरोध;
	/* DSP_B not mapped on I2S PCM दीर्घ क्रमmat. 1 bit offset करोes not fit */
	शेष:
		dev_err(cpu_dai->dev, "Unsupported protocol %#x\n",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	/* DAI घड़ी strobing */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		cgfr |= I2S_CGFR_CKPOL;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		cgfr |= I2S_CGFR_WSINV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		cgfr |= I2S_CGFR_CKPOL;
		cgfr |= I2S_CGFR_WSINV;
		अवरोध;
	शेष:
		dev_err(cpu_dai->dev, "Unsupported strobing %#x\n",
			fmt & SND_SOC_DAIFMT_INV_MASK);
		वापस -EINVAL;
	पूर्ण

	/* DAI घड़ी master masks */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		i2s->ms_flg = I2S_MS_SLAVE;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		i2s->ms_flg = I2S_MS_MASTER;
		अवरोध;
	शेष:
		dev_err(cpu_dai->dev, "Unsupported mode %#x\n",
			fmt & SND_SOC_DAIFMT_MASTER_MASK);
		वापस -EINVAL;
	पूर्ण

	i2s->fmt = fmt;
	वापस regmap_update_bits(i2s->regmap, STM32_I2S_CGFR_REG,
				  cgfr_mask, cgfr);
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_set_sysclk(काष्ठा snd_soc_dai *cpu_dai,
				पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक ret = 0;

	dev_dbg(cpu_dai->dev, "I2S MCLK frequency is %uHz. mode: %s, dir: %s\n",
		freq, STM32_I2S_IS_MASTER(i2s) ? "master" : "slave",
		dir ? "output" : "input");

	/* MCLK generation is available only in master mode */
	अगर (dir == SND_SOC_CLOCK_OUT && STM32_I2S_IS_MASTER(i2s)) अणु
		अगर (!i2s->i2smclk) अणु
			dev_dbg(cpu_dai->dev, "No MCLK registered\n");
			वापस 0;
		पूर्ण

		/* Assume shutकरोwn अगर requested frequency is 0Hz */
		अगर (!freq) अणु
			/* Release mclk rate only अगर rate was actually set */
			अगर (i2s->mclk_rate) अणु
				clk_rate_exclusive_put(i2s->i2smclk);
				i2s->mclk_rate = 0;
			पूर्ण
			वापस regmap_update_bits(i2s->regmap,
						  STM32_I2S_CGFR_REG,
						  I2S_CGFR_MCKOE, 0);
		पूर्ण
		/* If master घड़ी is used, set parent घड़ी now */
		ret = sपंचांग32_i2s_set_parent_घड़ी(i2s, freq);
		अगर (ret)
			वापस ret;
		ret = clk_set_rate_exclusive(i2s->i2smclk, freq);
		अगर (ret) अणु
			dev_err(cpu_dai->dev, "Could not set mclk rate\n");
			वापस ret;
		पूर्ण
		ret = regmap_update_bits(i2s->regmap, STM32_I2S_CGFR_REG,
					 I2S_CGFR_MCKOE, I2S_CGFR_MCKOE);
		अगर (!ret)
			i2s->mclk_rate = freq;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_configure_घड़ी(काष्ठा snd_soc_dai *cpu_dai,
				     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ i2s_घड़ी_rate;
	अचिन्हित पूर्णांक nb_bits, frame_len;
	अचिन्हित पूर्णांक rate = params_rate(params);
	u32 cgfr;
	पूर्णांक ret;

	अगर (!(rate % 11025))
		clk_set_parent(i2s->i2sclk, i2s->x11kclk);
	अन्यथा
		clk_set_parent(i2s->i2sclk, i2s->x8kclk);
	i2s_घड़ी_rate = clk_get_rate(i2s->i2sclk);

	/*
	 * mckl = mclk_ratio x ws
	 *   i2s mode : mclk_ratio = 256
	 *   dsp mode : mclk_ratio = 128
	 *
	 * mclk on
	 *   i2s mode : भाग = i2s_clk / (mclk_ratio * ws)
	 *   dsp mode : भाग = i2s_clk / (mclk_ratio * ws)
	 * mclk off
	 *   i2s mode : भाग = i2s_clk / (nb_bits x ws)
	 *   dsp mode : भाग = i2s_clk / (nb_bits x ws)
	 */
	अगर (i2s->mclk_rate) अणु
		ret = sपंचांग32_i2s_calc_clk_भाग(i2s, i2s_घड़ी_rate,
					     i2s->mclk_rate);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		frame_len = 32;
		अगर ((i2s->fmt & SND_SOC_DAIFMT_FORMAT_MASK) ==
		    SND_SOC_DAIFMT_DSP_A)
			frame_len = 16;

		/* master घड़ी not enabled */
		ret = regmap_पढ़ो(i2s->regmap, STM32_I2S_CGFR_REG, &cgfr);
		अगर (ret < 0)
			वापस ret;

		nb_bits = frame_len * ((cgfr & I2S_CGFR_CHLEN) + 1);
		ret = sपंचांग32_i2s_calc_clk_भाग(i2s, i2s_घड़ी_rate,
					     (nb_bits * rate));
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = sपंचांग32_i2s_set_clk_भाग(i2s);
	अगर (ret < 0)
		वापस ret;

	/* Set bitघड़ी and frameघड़ी to their inactive state */
	वापस regmap_update_bits(i2s->regmap, STM32_I2S_CFG2_REG,
				  I2S_CFG2_AFCNTR, I2S_CFG2_AFCNTR);
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_configure(काष्ठा snd_soc_dai *cpu_dai,
			       काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक क्रमmat = params_width(params);
	u32 cfgr, cfgr_mask, cfg1;
	अचिन्हित पूर्णांक fthlv;
	पूर्णांक ret;

	चयन (क्रमmat) अणु
	हाल 16:
		cfgr = I2S_CGFR_DATLEN_SET(I2S_I2SMOD_DATLEN_16);
		cfgr_mask = I2S_CGFR_DATLEN_MASK | I2S_CGFR_CHLEN;
		अवरोध;
	हाल 32:
		cfgr = I2S_CGFR_DATLEN_SET(I2S_I2SMOD_DATLEN_32) |
					   I2S_CGFR_CHLEN;
		cfgr_mask = I2S_CGFR_DATLEN_MASK | I2S_CGFR_CHLEN;
		अवरोध;
	शेष:
		dev_err(cpu_dai->dev, "Unexpected format %d", क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (STM32_I2S_IS_SLAVE(i2s)) अणु
		cfgr |= I2S_CGFR_I2SCFG_SET(I2S_I2SMOD_FD_SLAVE);

		/* As data length is either 16 or 32 bits, fixch always set */
		cfgr |= I2S_CGFR_FIXCH;
		cfgr_mask |= I2S_CGFR_FIXCH;
	पूर्ण अन्यथा अणु
		cfgr |= I2S_CGFR_I2SCFG_SET(I2S_I2SMOD_FD_MASTER);
	पूर्ण
	cfgr_mask |= I2S_CGFR_I2SCFG_MASK;

	ret = regmap_update_bits(i2s->regmap, STM32_I2S_CGFR_REG,
				 cfgr_mask, cfgr);
	अगर (ret < 0)
		वापस ret;

	fthlv = STM32_I2S_FIFO_SIZE * I2S_FIFO_TH_ONE_QUARTER / 4;
	cfg1 = I2S_CFG1_FTHVL_SET(fthlv - 1);

	वापस regmap_update_bits(i2s->regmap, STM32_I2S_CFG1_REG,
				  I2S_CFG1_FTHVL_MASK, cfg1);
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_startup(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&i2s->irq_lock, flags);
	i2s->substream = substream;
	spin_unlock_irqrestore(&i2s->irq_lock, flags);

	अगर ((i2s->fmt & SND_SOC_DAIFMT_FORMAT_MASK) != SND_SOC_DAIFMT_DSP_A)
		snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
					     SNDRV_PCM_HW_PARAM_CHANNELS, 2);

	ret = clk_prepare_enable(i2s->i2sclk);
	अगर (ret < 0) अणु
		dev_err(cpu_dai->dev, "Failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस regmap_ग_लिखो_bits(i2s->regmap, STM32_I2S_IFCR_REG,
				 I2S_IFCR_MASK, I2S_IFCR_MASK);
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक ret;

	ret = sपंचांग32_i2s_configure(cpu_dai, params, substream);
	अगर (ret < 0) अणु
		dev_err(cpu_dai->dev, "Configuration returned error %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (STM32_I2S_IS_MASTER(i2s))
		ret = sपंचांग32_i2s_configure_घड़ी(cpu_dai, params);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			     काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	bool playback_flg = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	u32 cfg1_mask, ier;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		/* Enable i2s */
		dev_dbg(cpu_dai->dev, "start I2S %s\n",
			playback_flg ? "playback" : "capture");

		cfg1_mask = I2S_CFG1_RXDMAEN | I2S_CFG1_TXDMAEN;
		regmap_update_bits(i2s->regmap, STM32_I2S_CFG1_REG,
				   cfg1_mask, cfg1_mask);

		ret = regmap_update_bits(i2s->regmap, STM32_I2S_CR1_REG,
					 I2S_CR1_SPE, I2S_CR1_SPE);
		अगर (ret < 0) अणु
			dev_err(cpu_dai->dev, "Error %d enabling I2S\n", ret);
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो_bits(i2s->regmap, STM32_I2S_CR1_REG,
					I2S_CR1_CSTART, I2S_CR1_CSTART);
		अगर (ret < 0) अणु
			dev_err(cpu_dai->dev, "Error %d starting I2S\n", ret);
			वापस ret;
		पूर्ण

		regmap_ग_लिखो_bits(i2s->regmap, STM32_I2S_IFCR_REG,
				  I2S_IFCR_MASK, I2S_IFCR_MASK);

		spin_lock(&i2s->lock_fd);
		i2s->refcount++;
		अगर (playback_flg) अणु
			ier = I2S_IER_UDRIE;
		पूर्ण अन्यथा अणु
			ier = I2S_IER_OVRIE;

			अगर (STM32_I2S_IS_MASTER(i2s) && i2s->refcount == 1)
				/* dummy ग_लिखो to gate bus घड़ीs */
				regmap_ग_लिखो(i2s->regmap,
					     STM32_I2S_TXDR_REG, 0);
		पूर्ण
		spin_unlock(&i2s->lock_fd);

		अगर (STM32_I2S_IS_SLAVE(i2s))
			ier |= I2S_IER_TIFREIE;

		regmap_update_bits(i2s->regmap, STM32_I2S_IER_REG, ier, ier);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		dev_dbg(cpu_dai->dev, "stop I2S %s\n",
			playback_flg ? "playback" : "capture");

		अगर (playback_flg)
			regmap_update_bits(i2s->regmap, STM32_I2S_IER_REG,
					   I2S_IER_UDRIE,
					   (अचिन्हित पूर्णांक)~I2S_IER_UDRIE);
		अन्यथा
			regmap_update_bits(i2s->regmap, STM32_I2S_IER_REG,
					   I2S_IER_OVRIE,
					   (अचिन्हित पूर्णांक)~I2S_IER_OVRIE);

		spin_lock(&i2s->lock_fd);
		i2s->refcount--;
		अगर (i2s->refcount) अणु
			spin_unlock(&i2s->lock_fd);
			अवरोध;
		पूर्ण

		ret = regmap_update_bits(i2s->regmap, STM32_I2S_CR1_REG,
					 I2S_CR1_SPE, 0);
		अगर (ret < 0) अणु
			dev_err(cpu_dai->dev, "Error %d disabling I2S\n", ret);
			spin_unlock(&i2s->lock_fd);
			वापस ret;
		पूर्ण
		spin_unlock(&i2s->lock_fd);

		cfg1_mask = I2S_CFG1_RXDMAEN | I2S_CFG1_TXDMAEN;
		regmap_update_bits(i2s->regmap, STM32_I2S_CFG1_REG,
				   cfg1_mask, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ flags;

	clk_disable_unprepare(i2s->i2sclk);

	spin_lock_irqsave(&i2s->irq_lock, flags);
	i2s->substream = शून्य;
	spin_unlock_irqrestore(&i2s->irq_lock, flags);
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_dai_probe(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s = dev_get_drvdata(cpu_dai->dev);
	काष्ठा snd_dmaengine_dai_dma_data *dma_data_tx = &i2s->dma_data_tx;
	काष्ठा snd_dmaengine_dai_dma_data *dma_data_rx = &i2s->dma_data_rx;

	/* Buswidth will be set by framework */
	dma_data_tx->addr_width = DMA_SLAVE_BUSWIDTH_UNDEFINED;
	dma_data_tx->addr = (dma_addr_t)(i2s->phys_addr) + STM32_I2S_TXDR_REG;
	dma_data_tx->maxburst = 1;
	dma_data_rx->addr_width = DMA_SLAVE_BUSWIDTH_UNDEFINED;
	dma_data_rx->addr = (dma_addr_t)(i2s->phys_addr) + STM32_I2S_RXDR_REG;
	dma_data_rx->maxburst = 1;

	snd_soc_dai_init_dma_data(cpu_dai, dma_data_tx, dma_data_rx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config sपंचांग32_h7_i2s_regmap_conf = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = STM32_I2S_SIDR_REG,
	.पढ़ोable_reg = sपंचांग32_i2s_पढ़ोable_reg,
	.अस्थिर_reg = sपंचांग32_i2s_अस्थिर_reg,
	.ग_लिखोable_reg = sपंचांग32_i2s_ग_लिखोable_reg,
	.num_reg_शेषs_raw = STM32_I2S_SIDR_REG / माप(u32) + 1,
	.fast_io = true,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops sपंचांग32_i2s_pcm_dai_ops = अणु
	.set_sysclk	= sपंचांग32_i2s_set_sysclk,
	.set_fmt	= sपंचांग32_i2s_set_dai_fmt,
	.startup	= sपंचांग32_i2s_startup,
	.hw_params	= sपंचांग32_i2s_hw_params,
	.trigger	= sपंचांग32_i2s_trigger,
	.shutकरोwn	= sपंचांग32_i2s_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware sपंचांग32_i2s_pcm_hw = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_MMAP,
	.buffer_bytes_max = 8 * PAGE_SIZE,
	.period_bytes_min = 1024,
	.period_bytes_max = 4 * PAGE_SIZE,
	.periods_min = 2,
	.periods_max = 8,
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config sपंचांग32_i2s_pcm_config = अणु
	.pcm_hardware	= &sपंचांग32_i2s_pcm_hw,
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
	.pपुनः_स्मृति_buffer_size = PAGE_SIZE * 8,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sपंचांग32_i2s_component = अणु
	.name = "stm32-i2s",
पूर्ण;

अटल व्योम sपंचांग32_i2s_dai_init(काष्ठा snd_soc_pcm_stream *stream,
			       अक्षर *stream_name)
अणु
	stream->stream_name = stream_name;
	stream->channels_min = 1;
	stream->channels_max = 2;
	stream->rates = SNDRV_PCM_RATE_8000_192000;
	stream->क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S32_LE;
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_dais_init(काष्ठा platक्रमm_device *pdev,
			       काष्ठा sपंचांग32_i2s_data *i2s)
अणु
	काष्ठा snd_soc_dai_driver *dai_ptr;

	dai_ptr = devm_kzalloc(&pdev->dev, माप(काष्ठा snd_soc_dai_driver),
			       GFP_KERNEL);
	अगर (!dai_ptr)
		वापस -ENOMEM;

	dai_ptr->probe = sपंचांग32_i2s_dai_probe;
	dai_ptr->ops = &sपंचांग32_i2s_pcm_dai_ops;
	dai_ptr->id = 1;
	sपंचांग32_i2s_dai_init(&dai_ptr->playback, "playback");
	sपंचांग32_i2s_dai_init(&dai_ptr->capture, "capture");
	i2s->dai_drv = dai_ptr;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांग32_i2s_ids[] = अणु
	अणु
		.compatible = "st,stm32h7-i2s",
		.data = &sपंचांग32_h7_i2s_regmap_conf
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांग32_i2s_parse_dt(काष्ठा platक्रमm_device *pdev,
			      काष्ठा sपंचांग32_i2s_data *i2s)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा reset_control *rst;
	काष्ठा resource *res;
	पूर्णांक irq, ret;

	अगर (!np)
		वापस -ENODEV;

	of_id = of_match_device(sपंचांग32_i2s_ids, &pdev->dev);
	अगर (of_id)
		i2s->regmap_conf = (स्थिर काष्ठा regmap_config *)of_id->data;
	अन्यथा
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	i2s->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(i2s->base))
		वापस PTR_ERR(i2s->base);

	i2s->phys_addr = res->start;

	/* Get घड़ीs */
	i2s->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(i2s->pclk)) अणु
		अगर (PTR_ERR(i2s->pclk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Could not get pclk: %ld\n",
				PTR_ERR(i2s->pclk));
		वापस PTR_ERR(i2s->pclk);
	पूर्ण

	i2s->i2sclk = devm_clk_get(&pdev->dev, "i2sclk");
	अगर (IS_ERR(i2s->i2sclk)) अणु
		अगर (PTR_ERR(i2s->i2sclk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Could not get i2sclk: %ld\n",
				PTR_ERR(i2s->i2sclk));
		वापस PTR_ERR(i2s->i2sclk);
	पूर्ण

	i2s->x8kclk = devm_clk_get(&pdev->dev, "x8k");
	अगर (IS_ERR(i2s->x8kclk)) अणु
		अगर (PTR_ERR(i2s->x8kclk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Could not get x8k parent clock: %ld\n",
				PTR_ERR(i2s->x8kclk));
		वापस PTR_ERR(i2s->x8kclk);
	पूर्ण

	i2s->x11kclk = devm_clk_get(&pdev->dev, "x11k");
	अगर (IS_ERR(i2s->x11kclk)) अणु
		अगर (PTR_ERR(i2s->x11kclk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Could not get x11k parent clock: %ld\n",
				PTR_ERR(i2s->x11kclk));
		वापस PTR_ERR(i2s->x11kclk);
	पूर्ण

	/* Register mclk provider अगर requested */
	अगर (of_find_property(np, "#clock-cells", शून्य)) अणु
		ret = sपंचांग32_i2s_add_mclk_provider(i2s);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Get irqs */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, sपंचांग32_i2s_isr, IRQF_ONESHOT,
			       dev_name(&pdev->dev), i2s);
	अगर (ret) अणु
		dev_err(&pdev->dev, "irq request returned %d\n", ret);
		वापस ret;
	पूर्ण

	/* Reset */
	rst = devm_reset_control_get_optional_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(rst)) अणु
		अगर (PTR_ERR(rst) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Reset controller error %ld\n",
				PTR_ERR(rst));
		वापस PTR_ERR(rst);
	पूर्ण
	reset_control_निश्चित(rst);
	udelay(2);
	reset_control_deनिश्चित(rst);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	snd_dmaengine_pcm_unरेजिस्टर(&pdev->dev);
	snd_soc_unरेजिस्टर_component(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s;
	u32 val;
	पूर्णांक ret;

	i2s = devm_kzalloc(&pdev->dev, माप(*i2s), GFP_KERNEL);
	अगर (!i2s)
		वापस -ENOMEM;

	i2s->pdev = pdev;
	i2s->ms_flg = I2S_MS_NOT_SET;
	spin_lock_init(&i2s->lock_fd);
	spin_lock_init(&i2s->irq_lock);
	platक्रमm_set_drvdata(pdev, i2s);

	ret = sपंचांग32_i2s_parse_dt(pdev, i2s);
	अगर (ret)
		वापस ret;

	ret = sपंचांग32_i2s_dais_init(pdev, i2s);
	अगर (ret)
		वापस ret;

	i2s->regmap = devm_regmap_init_mmio_clk(&pdev->dev, "pclk",
						i2s->base, i2s->regmap_conf);
	अगर (IS_ERR(i2s->regmap)) अणु
		अगर (PTR_ERR(i2s->regmap) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Regmap init error %ld\n",
				PTR_ERR(i2s->regmap));
		वापस PTR_ERR(i2s->regmap);
	पूर्ण

	ret = snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, &sपंचांग32_i2s_pcm_config, 0);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "PCM DMA register error %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_रेजिस्टर_component(&pdev->dev, &sपंचांग32_i2s_component,
					 i2s->dai_drv, 1);
	अगर (ret) अणु
		snd_dmaengine_pcm_unरेजिस्टर(&pdev->dev);
		वापस ret;
	पूर्ण

	/* Set SPI/I2S in i2s mode */
	ret = regmap_update_bits(i2s->regmap, STM32_I2S_CGFR_REG,
				 I2S_CGFR_I2SMOD, I2S_CGFR_I2SMOD);
	अगर (ret)
		जाओ error;

	ret = regmap_पढ़ो(i2s->regmap, STM32_I2S_IPIDR_REG, &val);
	अगर (ret)
		जाओ error;

	अगर (val == I2S_IPIDR_NUMBER) अणु
		ret = regmap_पढ़ो(i2s->regmap, STM32_I2S_HWCFGR_REG, &val);
		अगर (ret)
			जाओ error;

		अगर (!FIELD_GET(I2S_HWCFGR_I2S_SUPPORT_MASK, val)) अणु
			dev_err(&pdev->dev,
				"Device does not support i2s mode\n");
			ret = -EPERM;
			जाओ error;
		पूर्ण

		ret = regmap_पढ़ो(i2s->regmap, STM32_I2S_VERR_REG, &val);
		अगर (ret)
			जाओ error;

		dev_dbg(&pdev->dev, "I2S version: %lu.%lu registered\n",
			FIELD_GET(I2S_VERR_MAJ_MASK, val),
			FIELD_GET(I2S_VERR_MIN_MASK, val));
	पूर्ण

	वापस ret;

error:
	sपंचांग32_i2s_हटाओ(pdev);

	वापस ret;
पूर्ण

MODULE_DEVICE_TABLE(of, sपंचांग32_i2s_ids);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांग32_i2s_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s = dev_get_drvdata(dev);

	regcache_cache_only(i2s->regmap, true);
	regcache_mark_dirty(i2s->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_i2s_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_i2s_data *i2s = dev_get_drvdata(dev);

	regcache_cache_only(i2s->regmap, false);
	वापस regcache_sync(i2s->regmap);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_i2s_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_i2s_suspend, sपंचांग32_i2s_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver sपंचांग32_i2s_driver = अणु
	.driver = अणु
		.name = "st,stm32-i2s",
		.of_match_table = sपंचांग32_i2s_ids,
		.pm = &sपंचांग32_i2s_pm_ops,
	पूर्ण,
	.probe = sपंचांग32_i2s_probe,
	.हटाओ = sपंचांग32_i2s_हटाओ,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_i2s_driver);

MODULE_DESCRIPTION("STM32 Soc i2s Interface");
MODULE_AUTHOR("Olivier Moysan, <olivier.moysan@st.com>");
MODULE_ALIAS("platform:stm32-i2s");
MODULE_LICENSE("GPL v2");
