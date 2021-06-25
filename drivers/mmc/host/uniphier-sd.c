<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2017-2018 Socionext Inc.
//   Author: Masahiro Yamada <yamada.masahiro@socionext.com>

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश "tmio_mmc.h"

#घोषणा   UNIPHIER_SD_CLK_CTL_DIV1024		BIT(16)
#घोषणा   UNIPHIER_SD_CLK_CTL_DIV1		BIT(10)
#घोषणा   UNIPHIER_SD_CLKCTL_OFFEN		BIT(9)  // स्वतः SDCLK stop
#घोषणा UNIPHIER_SD_CC_EXT_MODE		0x1b0
#घोषणा   UNIPHIER_SD_CC_EXT_MODE_DMA		BIT(1)
#घोषणा UNIPHIER_SD_HOST_MODE		0x1c8
#घोषणा UNIPHIER_SD_VOLT		0x1e4
#घोषणा   UNIPHIER_SD_VOLT_MASK			GENMASK(1, 0)
#घोषणा   UNIPHIER_SD_VOLT_OFF			0
#घोषणा   UNIPHIER_SD_VOLT_330			1	// 3.3V संकेत
#घोषणा   UNIPHIER_SD_VOLT_180			2	// 1.8V संकेत
#घोषणा UNIPHIER_SD_DMA_MODE		0x410
#घोषणा   UNIPHIER_SD_DMA_MODE_सूची_MASK		GENMASK(17, 16)
#घोषणा   UNIPHIER_SD_DMA_MODE_सूची_TO_DEV	0
#घोषणा   UNIPHIER_SD_DMA_MODE_सूची_FROM_DEV	1
#घोषणा   UNIPHIER_SD_DMA_MODE_WIDTH_MASK	GENMASK(5, 4)
#घोषणा   UNIPHIER_SD_DMA_MODE_WIDTH_8		0
#घोषणा   UNIPHIER_SD_DMA_MODE_WIDTH_16		1
#घोषणा   UNIPHIER_SD_DMA_MODE_WIDTH_32		2
#घोषणा   UNIPHIER_SD_DMA_MODE_WIDTH_64		3
#घोषणा   UNIPHIER_SD_DMA_MODE_ADDR_INC		BIT(0)	// 1: inc, 0: fixed
#घोषणा UNIPHIER_SD_DMA_CTL		0x414
#घोषणा   UNIPHIER_SD_DMA_CTL_START	BIT(0)	// start DMA (स्वतः cleared)
#घोषणा UNIPHIER_SD_DMA_RST		0x418
#घोषणा   UNIPHIER_SD_DMA_RST_CH1	BIT(9)
#घोषणा   UNIPHIER_SD_DMA_RST_CH0	BIT(8)
#घोषणा UNIPHIER_SD_DMA_ADDR_L		0x440
#घोषणा UNIPHIER_SD_DMA_ADDR_H		0x444

/*
 * IP is extended to support various features: built-in DMA engine,
 * 1/1024 भागisor, etc.
 */
#घोषणा UNIPHIER_SD_CAP_EXTENDED_IP		BIT(0)
/* RX channel of the built-in DMA controller is broken (Pro5) */
#घोषणा UNIPHIER_SD_CAP_BROKEN_DMA_RX		BIT(1)

काष्ठा uniphier_sd_priv अणु
	काष्ठा पंचांगio_mmc_data पंचांगio_data;
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pinstate_uhs;
	काष्ठा clk *clk;
	काष्ठा reset_control *rst;
	काष्ठा reset_control *rst_br;
	काष्ठा reset_control *rst_hw;
	काष्ठा dma_chan *chan;
	क्रमागत dma_data_direction dma_dir;
	अचिन्हित दीर्घ clk_rate;
	अचिन्हित दीर्घ caps;
पूर्ण;

अटल व्योम *uniphier_sd_priv(काष्ठा पंचांगio_mmc_host *host)
अणु
	वापस container_of(host->pdata, काष्ठा uniphier_sd_priv, पंचांगio_data);
पूर्ण

अटल व्योम uniphier_sd_dma_endisable(काष्ठा पंचांगio_mmc_host *host, पूर्णांक enable)
अणु
	sd_ctrl_ग_लिखो16(host, CTL_DMA_ENABLE, enable ? DMA_ENABLE_DMASDRW : 0);
पूर्ण

/* बाह्यal DMA engine */
अटल व्योम uniphier_sd_बाह्यal_dma_issue(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा पंचांगio_mmc_host *host = from_tasklet(host, t, dma_issue);
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);

	uniphier_sd_dma_endisable(host, 1);
	dma_async_issue_pending(priv->chan);
पूर्ण

अटल व्योम uniphier_sd_बाह्यal_dma_callback(व्योम *param,
					स्थिर काष्ठा dmaengine_result *result)
अणु
	काष्ठा पंचांगio_mmc_host *host = param;
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);
	अचिन्हित दीर्घ flags;

	dma_unmap_sg(mmc_dev(host->mmc), host->sg_ptr, host->sg_len,
		     priv->dma_dir);

	spin_lock_irqsave(&host->lock, flags);

	अगर (result->result == DMA_TRANS_NOERROR) अणु
		/*
		 * When the बाह्यal DMA engine is enabled, strangely enough,
		 * the DATAEND flag can be निश्चितed even अगर the DMA engine has
		 * not been kicked yet.  Enable the TMIO_STAT_DATAEND irq only
		 * after we make sure the DMA engine finishes the transfer,
		 * hence, in this callback.
		 */
		पंचांगio_mmc_enable_mmc_irqs(host, TMIO_STAT_DATAEND);
	पूर्ण अन्यथा अणु
		host->data->error = -ETIMEDOUT;
		पंचांगio_mmc_करो_data_irq(host);
	पूर्ण

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम uniphier_sd_बाह्यal_dma_start(काष्ठा पंचांगio_mmc_host *host,
					   काष्ठा mmc_data *data)
अणु
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);
	क्रमागत dma_transfer_direction dma_tx_dir;
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;
	पूर्णांक sg_len;

	अगर (!priv->chan)
		जाओ क्रमce_pio;

	अगर (data->flags & MMC_DATA_READ) अणु
		priv->dma_dir = DMA_FROM_DEVICE;
		dma_tx_dir = DMA_DEV_TO_MEM;
	पूर्ण अन्यथा अणु
		priv->dma_dir = DMA_TO_DEVICE;
		dma_tx_dir = DMA_MEM_TO_DEV;
	पूर्ण

	sg_len = dma_map_sg(mmc_dev(host->mmc), host->sg_ptr, host->sg_len,
			    priv->dma_dir);
	अगर (sg_len == 0)
		जाओ क्रमce_pio;

	desc = dmaengine_prep_slave_sg(priv->chan, host->sg_ptr, sg_len,
				       dma_tx_dir, DMA_CTRL_ACK);
	अगर (!desc)
		जाओ unmap_sg;

	desc->callback_result = uniphier_sd_बाह्यal_dma_callback;
	desc->callback_param = host;

	cookie = dmaengine_submit(desc);
	अगर (cookie < 0)
		जाओ unmap_sg;

	host->dma_on = true;

	वापस;

unmap_sg:
	dma_unmap_sg(mmc_dev(host->mmc), host->sg_ptr, host->sg_len,
		     priv->dma_dir);
क्रमce_pio:
	uniphier_sd_dma_endisable(host, 0);
पूर्ण

अटल व्योम uniphier_sd_बाह्यal_dma_enable(काष्ठा पंचांगio_mmc_host *host,
					    bool enable)
अणु
पूर्ण

अटल व्योम uniphier_sd_बाह्यal_dma_request(काष्ठा पंचांगio_mmc_host *host,
					     काष्ठा पंचांगio_mmc_data *pdata)
अणु
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);
	काष्ठा dma_chan *chan;

	chan = dma_request_chan(mmc_dev(host->mmc), "rx-tx");
	अगर (IS_ERR(chan)) अणु
		dev_warn(mmc_dev(host->mmc),
			 "failed to request DMA channel. falling back to PIO\n");
		वापस;	/* just use PIO even क्रम -EPROBE_DEFER */
	पूर्ण

	/* this driver uses a single channel क्रम both RX an TX */
	priv->chan = chan;
	host->chan_rx = chan;
	host->chan_tx = chan;

	tasklet_setup(&host->dma_issue, uniphier_sd_बाह्यal_dma_issue);
पूर्ण

अटल व्योम uniphier_sd_बाह्यal_dma_release(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);

	अगर (priv->chan)
		dma_release_channel(priv->chan);
पूर्ण

अटल व्योम uniphier_sd_बाह्यal_dma_पात(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);

	uniphier_sd_dma_endisable(host, 0);

	अगर (priv->chan)
		dmaengine_terminate_sync(priv->chan);
पूर्ण

अटल व्योम uniphier_sd_बाह्यal_dma_dataend(काष्ठा पंचांगio_mmc_host *host)
अणु
	uniphier_sd_dma_endisable(host, 0);

	पंचांगio_mmc_करो_data_irq(host);
पूर्ण

अटल स्थिर काष्ठा पंचांगio_mmc_dma_ops uniphier_sd_बाह्यal_dma_ops = अणु
	.start = uniphier_sd_बाह्यal_dma_start,
	.enable = uniphier_sd_बाह्यal_dma_enable,
	.request = uniphier_sd_बाह्यal_dma_request,
	.release = uniphier_sd_बाह्यal_dma_release,
	.पात = uniphier_sd_बाह्यal_dma_पात,
	.dataend = uniphier_sd_बाह्यal_dma_dataend,
पूर्ण;

अटल व्योम uniphier_sd_पूर्णांकernal_dma_issue(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा पंचांगio_mmc_host *host = from_tasklet(host, t, dma_issue);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	पंचांगio_mmc_enable_mmc_irqs(host, TMIO_STAT_DATAEND);
	spin_unlock_irqrestore(&host->lock, flags);

	uniphier_sd_dma_endisable(host, 1);
	ग_लिखोl(UNIPHIER_SD_DMA_CTL_START, host->ctl + UNIPHIER_SD_DMA_CTL);
पूर्ण

अटल व्योम uniphier_sd_पूर्णांकernal_dma_start(काष्ठा पंचांगio_mmc_host *host,
					   काष्ठा mmc_data *data)
अणु
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);
	काष्ठा scatterlist *sg = host->sg_ptr;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक dma_mode_dir;
	u32 dma_mode;
	पूर्णांक sg_len;

	अगर ((data->flags & MMC_DATA_READ) && !host->chan_rx)
		जाओ क्रमce_pio;

	अगर (WARN_ON(host->sg_len != 1))
		जाओ क्रमce_pio;

	अगर (!IS_ALIGNED(sg->offset, 8))
		जाओ क्रमce_pio;

	अगर (data->flags & MMC_DATA_READ) अणु
		priv->dma_dir = DMA_FROM_DEVICE;
		dma_mode_dir = UNIPHIER_SD_DMA_MODE_सूची_FROM_DEV;
	पूर्ण अन्यथा अणु
		priv->dma_dir = DMA_TO_DEVICE;
		dma_mode_dir = UNIPHIER_SD_DMA_MODE_सूची_TO_DEV;
	पूर्ण

	sg_len = dma_map_sg(mmc_dev(host->mmc), sg, 1, priv->dma_dir);
	अगर (sg_len == 0)
		जाओ क्रमce_pio;

	dma_mode = FIELD_PREP(UNIPHIER_SD_DMA_MODE_सूची_MASK, dma_mode_dir);
	dma_mode |= FIELD_PREP(UNIPHIER_SD_DMA_MODE_WIDTH_MASK,
			       UNIPHIER_SD_DMA_MODE_WIDTH_64);
	dma_mode |= UNIPHIER_SD_DMA_MODE_ADDR_INC;

	ग_लिखोl(dma_mode, host->ctl + UNIPHIER_SD_DMA_MODE);

	dma_addr = sg_dma_address(data->sg);
	ग_लिखोl(lower_32_bits(dma_addr), host->ctl + UNIPHIER_SD_DMA_ADDR_L);
	ग_लिखोl(upper_32_bits(dma_addr), host->ctl + UNIPHIER_SD_DMA_ADDR_H);

	host->dma_on = true;

	वापस;
क्रमce_pio:
	uniphier_sd_dma_endisable(host, 0);
पूर्ण

अटल व्योम uniphier_sd_पूर्णांकernal_dma_enable(काष्ठा पंचांगio_mmc_host *host,
					    bool enable)
अणु
पूर्ण

अटल व्योम uniphier_sd_पूर्णांकernal_dma_request(काष्ठा पंचांगio_mmc_host *host,
					     काष्ठा पंचांगio_mmc_data *pdata)
अणु
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);

	/*
	 * Due to a hardware bug, Pro5 cannot use DMA क्रम RX.
	 * We can still use DMA क्रम TX, but PIO क्रम RX.
	 */
	अगर (!(priv->caps & UNIPHIER_SD_CAP_BROKEN_DMA_RX))
		host->chan_rx = (व्योम *)0xdeadbeaf;

	host->chan_tx = (व्योम *)0xdeadbeaf;

	tasklet_setup(&host->dma_issue, uniphier_sd_पूर्णांकernal_dma_issue);
पूर्ण

अटल व्योम uniphier_sd_पूर्णांकernal_dma_release(काष्ठा पंचांगio_mmc_host *host)
अणु
	/* Each value is set to zero to assume "disabling" each DMA */
	host->chan_rx = शून्य;
	host->chan_tx = शून्य;
पूर्ण

अटल व्योम uniphier_sd_पूर्णांकernal_dma_पात(काष्ठा पंचांगio_mmc_host *host)
अणु
	u32 पंचांगp;

	uniphier_sd_dma_endisable(host, 0);

	पंचांगp = पढ़ोl(host->ctl + UNIPHIER_SD_DMA_RST);
	पंचांगp &= ~(UNIPHIER_SD_DMA_RST_CH1 | UNIPHIER_SD_DMA_RST_CH0);
	ग_लिखोl(पंचांगp, host->ctl + UNIPHIER_SD_DMA_RST);

	पंचांगp |= UNIPHIER_SD_DMA_RST_CH1 | UNIPHIER_SD_DMA_RST_CH0;
	ग_लिखोl(पंचांगp, host->ctl + UNIPHIER_SD_DMA_RST);
पूर्ण

अटल व्योम uniphier_sd_पूर्णांकernal_dma_dataend(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);

	uniphier_sd_dma_endisable(host, 0);
	dma_unmap_sg(mmc_dev(host->mmc), host->sg_ptr, 1, priv->dma_dir);

	पंचांगio_mmc_करो_data_irq(host);
पूर्ण

अटल स्थिर काष्ठा पंचांगio_mmc_dma_ops uniphier_sd_पूर्णांकernal_dma_ops = अणु
	.start = uniphier_sd_पूर्णांकernal_dma_start,
	.enable = uniphier_sd_पूर्णांकernal_dma_enable,
	.request = uniphier_sd_पूर्णांकernal_dma_request,
	.release = uniphier_sd_पूर्णांकernal_dma_release,
	.पात = uniphier_sd_पूर्णांकernal_dma_पात,
	.dataend = uniphier_sd_पूर्णांकernal_dma_dataend,
पूर्ण;

अटल पूर्णांक uniphier_sd_clk_enable(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);
	काष्ठा mmc_host *mmc = host->mmc;
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	ret = clk_set_rate(priv->clk, अच_दीर्घ_उच्च);
	अगर (ret)
		जाओ disable_clk;

	priv->clk_rate = clk_get_rate(priv->clk);

	/* If max-frequency property is set, use it. */
	अगर (!mmc->f_max)
		mmc->f_max = priv->clk_rate;

	/*
	 * 1/512 is the finest भागisor in the original IP.  Newer versions
	 * also supports 1/1024 भागisor. (UniPhier-specअगरic extension)
	 */
	अगर (priv->caps & UNIPHIER_SD_CAP_EXTENDED_IP)
		mmc->f_min = priv->clk_rate / 1024;
	अन्यथा
		mmc->f_min = priv->clk_rate / 512;

	ret = reset_control_deनिश्चित(priv->rst);
	अगर (ret)
		जाओ disable_clk;

	ret = reset_control_deनिश्चित(priv->rst_br);
	अगर (ret)
		जाओ निश्चित_rst;

	वापस 0;

निश्चित_rst:
	reset_control_निश्चित(priv->rst);
disable_clk:
	clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल व्योम uniphier_sd_clk_disable(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);

	reset_control_निश्चित(priv->rst_br);
	reset_control_निश्चित(priv->rst);
	clk_disable_unprepare(priv->clk);
पूर्ण

अटल व्योम uniphier_sd_hw_reset(काष्ठा mmc_host *mmc)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);

	reset_control_निश्चित(priv->rst_hw);
	/* For eMMC, minimum is 1us but give it 9us क्रम good measure */
	udelay(9);
	reset_control_deनिश्चित(priv->rst_hw);
	/* For eMMC, minimum is 200us but give it 300us क्रम good measure */
	usleep_range(300, 1000);
पूर्ण

अटल व्योम uniphier_sd_set_घड़ी(काष्ठा पंचांगio_mmc_host *host,
				  अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);
	अचिन्हित दीर्घ भागisor;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(host->ctl + (CTL_SD_CARD_CLK_CTL << 1));

	/* stop the घड़ी beक्रमe changing its rate to aव्योम a glitch संकेत */
	पंचांगp &= ~CLK_CTL_SCLKEN;
	ग_लिखोl(पंचांगp, host->ctl + (CTL_SD_CARD_CLK_CTL << 1));

	अगर (घड़ी == 0)
		वापस;

	पंचांगp &= ~UNIPHIER_SD_CLK_CTL_DIV1024;
	पंचांगp &= ~UNIPHIER_SD_CLK_CTL_DIV1;
	पंचांगp &= ~CLK_CTL_DIV_MASK;

	भागisor = priv->clk_rate / घड़ी;

	/*
	 * In the original IP, bit[7:0] represents the भागisor.
	 * bit7 set: 1/512, ... bit0 set:1/4, all bits clear: 1/2
	 *
	 * The IP करोes not define a way to achieve 1/1.  For UniPhier variants,
	 * bit10 is used क्रम 1/1.  Newer versions of UniPhier variants use
	 * bit16 क्रम 1/1024.
	 */
	अगर (भागisor <= 1)
		पंचांगp |= UNIPHIER_SD_CLK_CTL_DIV1;
	अन्यथा अगर (priv->caps & UNIPHIER_SD_CAP_EXTENDED_IP && भागisor > 512)
		पंचांगp |= UNIPHIER_SD_CLK_CTL_DIV1024;
	अन्यथा
		पंचांगp |= roundup_घात_of_two(भागisor) >> 2;

	ग_लिखोl(पंचांगp, host->ctl + (CTL_SD_CARD_CLK_CTL << 1));

	पंचांगp |= CLK_CTL_SCLKEN;
	ग_लिखोl(पंचांगp, host->ctl + (CTL_SD_CARD_CLK_CTL << 1));
पूर्ण

अटल व्योम uniphier_sd_host_init(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);
	u32 val;

	/*
	 * Connected to 32bit AXI.
	 * This रेजिस्टर holds settings क्रम SoC-specअगरic पूर्णांकernal bus
	 * connection.  What is worse, the रेजिस्टर spec was changed,
	 * अवरोधing the backward compatibility.  Write an appropriate
	 * value depending on a flag associated with a compatible string.
	 */
	अगर (priv->caps & UNIPHIER_SD_CAP_EXTENDED_IP)
		val = 0x00000101;
	अन्यथा
		val = 0x00000000;

	ग_लिखोl(val, host->ctl + UNIPHIER_SD_HOST_MODE);

	val = 0;
	/*
	 * If supported, the controller can स्वतःmatically
	 * enable/disable the घड़ी line to the card.
	 */
	अगर (priv->caps & UNIPHIER_SD_CAP_EXTENDED_IP)
		val |= UNIPHIER_SD_CLKCTL_OFFEN;

	ग_लिखोl(val, host->ctl + (CTL_SD_CARD_CLK_CTL << 1));
पूर्ण

अटल पूर्णांक uniphier_sd_start_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
						   काष्ठा mmc_ios *ios)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);
	काष्ठा uniphier_sd_priv *priv = uniphier_sd_priv(host);
	काष्ठा pinctrl_state *pinstate = शून्य;
	u32 val, पंचांगp;

	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_330:
		val = UNIPHIER_SD_VOLT_330;
		अवरोध;
	हाल MMC_SIGNAL_VOLTAGE_180:
		val = UNIPHIER_SD_VOLT_180;
		pinstate = priv->pinstate_uhs;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	पंचांगp = पढ़ोl(host->ctl + UNIPHIER_SD_VOLT);
	पंचांगp &= ~UNIPHIER_SD_VOLT_MASK;
	पंचांगp |= FIELD_PREP(UNIPHIER_SD_VOLT_MASK, val);
	ग_लिखोl(पंचांगp, host->ctl + UNIPHIER_SD_VOLT);

	अगर (pinstate)
		pinctrl_select_state(priv->pinctrl, pinstate);
	अन्यथा
		pinctrl_select_शेष_state(mmc_dev(mmc));

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_sd_uhs_init(काष्ठा पंचांगio_mmc_host *host,
				काष्ठा uniphier_sd_priv *priv)
अणु
	priv->pinctrl = devm_pinctrl_get(mmc_dev(host->mmc));
	अगर (IS_ERR(priv->pinctrl))
		वापस PTR_ERR(priv->pinctrl);

	priv->pinstate_uhs = pinctrl_lookup_state(priv->pinctrl, "uhs");
	अगर (IS_ERR(priv->pinstate_uhs))
		वापस PTR_ERR(priv->pinstate_uhs);

	host->ops.start_संकेत_voltage_चयन =
					uniphier_sd_start_संकेत_voltage_चयन;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_sd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_sd_priv *priv;
	काष्ठा पंचांगio_mmc_data *पंचांगio_data;
	काष्ठा पंचांगio_mmc_host *host;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->caps = (अचिन्हित दीर्घ)of_device_get_match_data(dev);

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to get clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	priv->rst = devm_reset_control_get_shared(dev, "host");
	अगर (IS_ERR(priv->rst)) अणु
		dev_err(dev, "failed to get host reset\n");
		वापस PTR_ERR(priv->rst);
	पूर्ण

	/* old version has one more reset */
	अगर (!(priv->caps & UNIPHIER_SD_CAP_EXTENDED_IP)) अणु
		priv->rst_br = devm_reset_control_get_shared(dev, "bridge");
		अगर (IS_ERR(priv->rst_br)) अणु
			dev_err(dev, "failed to get bridge reset\n");
			वापस PTR_ERR(priv->rst_br);
		पूर्ण
	पूर्ण

	पंचांगio_data = &priv->पंचांगio_data;
	पंचांगio_data->flags |= TMIO_MMC_32BIT_DATA_PORT;
	पंचांगio_data->flags |= TMIO_MMC_USE_BUSY_TIMEOUT;

	host = पंचांगio_mmc_host_alloc(pdev, पंचांगio_data);
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	अगर (host->mmc->caps & MMC_CAP_HW_RESET) अणु
		priv->rst_hw = devm_reset_control_get_exclusive(dev, "hw");
		अगर (IS_ERR(priv->rst_hw)) अणु
			dev_err(dev, "failed to get hw reset\n");
			ret = PTR_ERR(priv->rst_hw);
			जाओ मुक्त_host;
		पूर्ण
		host->ops.hw_reset = uniphier_sd_hw_reset;
	पूर्ण

	अगर (host->mmc->caps & MMC_CAP_UHS) अणु
		ret = uniphier_sd_uhs_init(host, priv);
		अगर (ret) अणु
			dev_warn(dev,
				 "failed to setup UHS (error %d).  Disabling UHS.",
				 ret);
			host->mmc->caps &= ~MMC_CAP_UHS;
		पूर्ण
	पूर्ण

	अगर (priv->caps & UNIPHIER_SD_CAP_EXTENDED_IP)
		host->dma_ops = &uniphier_sd_पूर्णांकernal_dma_ops;
	अन्यथा
		host->dma_ops = &uniphier_sd_बाह्यal_dma_ops;

	host->bus_shअगरt = 1;
	host->clk_enable = uniphier_sd_clk_enable;
	host->clk_disable = uniphier_sd_clk_disable;
	host->set_घड़ी = uniphier_sd_set_घड़ी;

	ret = uniphier_sd_clk_enable(host);
	अगर (ret)
		जाओ मुक्त_host;

	uniphier_sd_host_init(host);

	पंचांगio_data->ocr_mask = MMC_VDD_32_33 | MMC_VDD_33_34;
	अगर (host->mmc->caps & MMC_CAP_UHS)
		पंचांगio_data->ocr_mask |= MMC_VDD_165_195;

	पंचांगio_data->max_segs = 1;
	पंचांगio_data->max_blk_count = U16_MAX;

	ret = पंचांगio_mmc_host_probe(host);
	अगर (ret)
		जाओ disable_clk;

	ret = devm_request_irq(dev, irq, पंचांगio_mmc_irq, IRQF_SHARED,
			       dev_name(dev), host);
	अगर (ret)
		जाओ हटाओ_host;

	वापस 0;

हटाओ_host:
	पंचांगio_mmc_host_हटाओ(host);
disable_clk:
	uniphier_sd_clk_disable(host);
मुक्त_host:
	पंचांगio_mmc_host_मुक्त(host);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_sd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पंचांगio_mmc_host *host = platक्रमm_get_drvdata(pdev);

	पंचांगio_mmc_host_हटाओ(host);
	uniphier_sd_clk_disable(host);
	पंचांगio_mmc_host_मुक्त(host);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id uniphier_sd_match[] = अणु
	अणु
		.compatible = "socionext,uniphier-sd-v2.91",
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-sd-v3.1",
		.data = (व्योम *)(UNIPHIER_SD_CAP_EXTENDED_IP |
				 UNIPHIER_SD_CAP_BROKEN_DMA_RX),
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-sd-v3.1.1",
		.data = (व्योम *)UNIPHIER_SD_CAP_EXTENDED_IP,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_sd_match);

अटल काष्ठा platक्रमm_driver uniphier_sd_driver = अणु
	.probe = uniphier_sd_probe,
	.हटाओ = uniphier_sd_हटाओ,
	.driver = अणु
		.name = "uniphier-sd",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = uniphier_sd_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_sd_driver);

MODULE_AUTHOR("Masahiro Yamada <yamada.masahiro@socionext.com>");
MODULE_DESCRIPTION("UniPhier SD/eMMC host controller driver");
MODULE_LICENSE("GPL v2");
