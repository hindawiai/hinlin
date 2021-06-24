<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IMG I2S input controller driver
 *
 * Copyright (C) 2015 Imagination Technologies Ltd.
 *
 * Author: Damien Horsley <Damien.Horsley@imgtec.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <sound/core.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#घोषणा IMG_I2S_IN_RX_FIFO			0x0

#घोषणा IMG_I2S_IN_CTL				0x4
#घोषणा IMG_I2S_IN_CTL_ACTIVE_CHAN_MASK		0xfffffffc
#घोषणा IMG_I2S_IN_CTL_ACTIVE_CH_SHIFT		2
#घोषणा IMG_I2S_IN_CTL_16PACK_MASK		BIT(1)
#घोषणा IMG_I2S_IN_CTL_ME_MASK			BIT(0)

#घोषणा IMG_I2S_IN_CH_CTL			0x4
#घोषणा IMG_I2S_IN_CH_CTL_CCDEL_MASK		0x38000
#घोषणा IMG_I2S_IN_CH_CTL_CCDEL_SHIFT		15
#घोषणा IMG_I2S_IN_CH_CTL_FEN_MASK		BIT(14)
#घोषणा IMG_I2S_IN_CH_CTL_FMODE_MASK		BIT(13)
#घोषणा IMG_I2S_IN_CH_CTL_16PACK_MASK		BIT(12)
#घोषणा IMG_I2S_IN_CH_CTL_JUST_MASK		BIT(10)
#घोषणा IMG_I2S_IN_CH_CTL_PACKH_MASK		BIT(9)
#घोषणा IMG_I2S_IN_CH_CTL_CLK_TRANS_MASK	BIT(8)
#घोषणा IMG_I2S_IN_CH_CTL_BLKP_MASK		BIT(7)
#घोषणा IMG_I2S_IN_CH_CTL_FIFO_FLUSH_MASK	BIT(6)
#घोषणा IMG_I2S_IN_CH_CTL_LRD_MASK		BIT(3)
#घोषणा IMG_I2S_IN_CH_CTL_FW_MASK		BIT(2)
#घोषणा IMG_I2S_IN_CH_CTL_SW_MASK		BIT(1)
#घोषणा IMG_I2S_IN_CH_CTL_ME_MASK		BIT(0)

#घोषणा IMG_I2S_IN_CH_STRIDE			0x20

काष्ठा img_i2s_in अणु
	व्योम __iomem *base;
	काष्ठा clk *clk_sys;
	काष्ठा snd_dmaengine_dai_dma_data dma_data;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक max_i2s_chan;
	व्योम __iomem *channel_base;
	अचिन्हित पूर्णांक active_channels;
	काष्ठा snd_soc_dai_driver dai_driver;
	u32 suspend_ctl;
	u32 *suspend_ch_ctl;
पूर्ण;

अटल पूर्णांक img_i2s_in_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_i2s_in *i2s = dev_get_drvdata(dev);

	clk_disable_unprepare(i2s->clk_sys);

	वापस 0;
पूर्ण

अटल पूर्णांक img_i2s_in_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा img_i2s_in *i2s = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(i2s->clk_sys);
	अगर (ret) अणु
		dev_err(dev, "Unable to enable sys clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम img_i2s_in_ग_लिखोl(काष्ठा img_i2s_in *i2s, u32 val, u32 reg)
अणु
	ग_लिखोl(val, i2s->base + reg);
पूर्ण

अटल अंतरभूत u32 img_i2s_in_पढ़ोl(काष्ठा img_i2s_in *i2s, u32 reg)
अणु
	वापस पढ़ोl(i2s->base + reg);
पूर्ण

अटल अंतरभूत व्योम img_i2s_in_ch_ग_लिखोl(काष्ठा img_i2s_in *i2s, u32 chan,
					u32 val, u32 reg)
अणु
	ग_लिखोl(val, i2s->channel_base + (chan * IMG_I2S_IN_CH_STRIDE) + reg);
पूर्ण

अटल अंतरभूत u32 img_i2s_in_ch_पढ़ोl(काष्ठा img_i2s_in *i2s, u32 chan,
					u32 reg)
अणु
	वापस पढ़ोl(i2s->channel_base + (chan * IMG_I2S_IN_CH_STRIDE) + reg);
पूर्ण

अटल अंतरभूत व्योम img_i2s_in_ch_disable(काष्ठा img_i2s_in *i2s, u32 chan)
अणु
	u32 reg;

	reg = img_i2s_in_ch_पढ़ोl(i2s, chan, IMG_I2S_IN_CH_CTL);
	reg &= ~IMG_I2S_IN_CH_CTL_ME_MASK;
	img_i2s_in_ch_ग_लिखोl(i2s, chan, reg, IMG_I2S_IN_CH_CTL);
पूर्ण

अटल अंतरभूत व्योम img_i2s_in_ch_enable(काष्ठा img_i2s_in *i2s, u32 chan)
अणु
	u32 reg;

	reg = img_i2s_in_ch_पढ़ोl(i2s, chan, IMG_I2S_IN_CH_CTL);
	reg |= IMG_I2S_IN_CH_CTL_ME_MASK;
	img_i2s_in_ch_ग_लिखोl(i2s, chan, reg, IMG_I2S_IN_CH_CTL);
पूर्ण

अटल अंतरभूत व्योम img_i2s_in_disable(काष्ठा img_i2s_in *i2s)
अणु
	u32 reg;

	reg = img_i2s_in_पढ़ोl(i2s, IMG_I2S_IN_CTL);
	reg &= ~IMG_I2S_IN_CTL_ME_MASK;
	img_i2s_in_ग_लिखोl(i2s, reg, IMG_I2S_IN_CTL);
पूर्ण

अटल अंतरभूत व्योम img_i2s_in_enable(काष्ठा img_i2s_in *i2s)
अणु
	u32 reg;

	reg = img_i2s_in_पढ़ोl(i2s, IMG_I2S_IN_CTL);
	reg |= IMG_I2S_IN_CTL_ME_MASK;
	img_i2s_in_ग_लिखोl(i2s, reg, IMG_I2S_IN_CTL);
पूर्ण

अटल अंतरभूत व्योम img_i2s_in_flush(काष्ठा img_i2s_in *i2s)
अणु
	पूर्णांक i;
	u32 reg;

	क्रम (i = 0; i < i2s->active_channels; i++) अणु
		reg = img_i2s_in_ch_पढ़ोl(i2s, i, IMG_I2S_IN_CH_CTL);
		reg |= IMG_I2S_IN_CH_CTL_FIFO_FLUSH_MASK;
		img_i2s_in_ch_ग_लिखोl(i2s, i, reg, IMG_I2S_IN_CH_CTL);
		reg &= ~IMG_I2S_IN_CH_CTL_FIFO_FLUSH_MASK;
		img_i2s_in_ch_ग_लिखोl(i2s, i, reg, IMG_I2S_IN_CH_CTL);
	पूर्ण
पूर्ण

अटल पूर्णांक img_i2s_in_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_i2s_in *i2s = snd_soc_dai_get_drvdata(dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		img_i2s_in_enable(i2s);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		img_i2s_in_disable(i2s);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक img_i2s_in_check_rate(काष्ठा img_i2s_in *i2s,
		अचिन्हित पूर्णांक sample_rate, अचिन्हित पूर्णांक frame_size,
		अचिन्हित पूर्णांक *bclk_filter_enable,
		अचिन्हित पूर्णांक *bclk_filter_value)
अणु
	अचिन्हित पूर्णांक bclk_freq, cur_freq;

	bclk_freq = sample_rate * frame_size;

	cur_freq = clk_get_rate(i2s->clk_sys);

	अगर (cur_freq >= bclk_freq * 8) अणु
		*bclk_filter_enable = 1;
		*bclk_filter_value = 0;
	पूर्ण अन्यथा अगर (cur_freq >= bclk_freq * 7) अणु
		*bclk_filter_enable = 1;
		*bclk_filter_value = 1;
	पूर्ण अन्यथा अगर (cur_freq >= bclk_freq * 6) अणु
		*bclk_filter_enable = 0;
		*bclk_filter_value = 0;
	पूर्ण अन्यथा अणु
		dev_err(i2s->dev,
			"Sys clock rate %u insufficient for sample rate %u\n",
			cur_freq, sample_rate);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक img_i2s_in_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_i2s_in *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक rate, channels, i2s_channels, frame_size;
	अचिन्हित पूर्णांक bclk_filter_enable, bclk_filter_value;
	पूर्णांक i, ret = 0;
	u32 reg, control_mask, chan_control_mask;
	u32 control_set = 0, chan_control_set = 0;
	snd_pcm_क्रमmat_t क्रमmat;

	rate = params_rate(params);
	क्रमmat = params_क्रमmat(params);
	channels = params_channels(params);
	i2s_channels = channels / 2;

	चयन (क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S32_LE:
		frame_size = 64;
		chan_control_set |= IMG_I2S_IN_CH_CTL_SW_MASK;
		chan_control_set |= IMG_I2S_IN_CH_CTL_FW_MASK;
		chan_control_set |= IMG_I2S_IN_CH_CTL_PACKH_MASK;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		frame_size = 64;
		chan_control_set |= IMG_I2S_IN_CH_CTL_SW_MASK;
		chan_control_set |= IMG_I2S_IN_CH_CTL_FW_MASK;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		frame_size = 32;
		control_set |= IMG_I2S_IN_CTL_16PACK_MASK;
		chan_control_set |= IMG_I2S_IN_CH_CTL_16PACK_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((channels < 2) ||
	    (channels > (i2s->max_i2s_chan * 2)) ||
	    (channels % 2))
		वापस -EINVAL;

	control_set |= ((i2s_channels - 1) << IMG_I2S_IN_CTL_ACTIVE_CH_SHIFT);

	ret = img_i2s_in_check_rate(i2s, rate, frame_size,
			&bclk_filter_enable, &bclk_filter_value);
	अगर (ret < 0)
		वापस ret;

	अगर (bclk_filter_enable)
		chan_control_set |= IMG_I2S_IN_CH_CTL_FEN_MASK;

	अगर (bclk_filter_value)
		chan_control_set |= IMG_I2S_IN_CH_CTL_FMODE_MASK;

	control_mask = IMG_I2S_IN_CTL_16PACK_MASK |
		       IMG_I2S_IN_CTL_ACTIVE_CHAN_MASK;

	chan_control_mask = IMG_I2S_IN_CH_CTL_16PACK_MASK |
			    IMG_I2S_IN_CH_CTL_FEN_MASK |
			    IMG_I2S_IN_CH_CTL_FMODE_MASK |
			    IMG_I2S_IN_CH_CTL_SW_MASK |
			    IMG_I2S_IN_CH_CTL_FW_MASK |
			    IMG_I2S_IN_CH_CTL_PACKH_MASK;

	reg = img_i2s_in_पढ़ोl(i2s, IMG_I2S_IN_CTL);
	reg = (reg & ~control_mask) | control_set;
	img_i2s_in_ग_लिखोl(i2s, reg, IMG_I2S_IN_CTL);

	क्रम (i = 0; i < i2s->active_channels; i++)
		img_i2s_in_ch_disable(i2s, i);

	क्रम (i = 0; i < i2s->max_i2s_chan; i++) अणु
		reg = img_i2s_in_ch_पढ़ोl(i2s, i, IMG_I2S_IN_CH_CTL);
		reg = (reg & ~chan_control_mask) | chan_control_set;
		img_i2s_in_ch_ग_लिखोl(i2s, i, reg, IMG_I2S_IN_CH_CTL);
	पूर्ण

	i2s->active_channels = i2s_channels;

	img_i2s_in_flush(i2s);

	क्रम (i = 0; i < i2s->active_channels; i++)
		img_i2s_in_ch_enable(i2s, i);

	वापस 0;
पूर्ण

अटल पूर्णांक img_i2s_in_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा img_i2s_in *i2s = snd_soc_dai_get_drvdata(dai);
	पूर्णांक i, ret;
	u32 chan_control_mask, lrd_set = 0, blkp_set = 0, chan_control_set = 0;
	u32 reg;

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		lrd_set |= IMG_I2S_IN_CH_CTL_LRD_MASK;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		lrd_set |= IMG_I2S_IN_CH_CTL_LRD_MASK;
		blkp_set |= IMG_I2S_IN_CH_CTL_BLKP_MASK;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		blkp_set |= IMG_I2S_IN_CH_CTL_BLKP_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		chan_control_set |= IMG_I2S_IN_CH_CTL_CLK_TRANS_MASK;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	chan_control_mask = IMG_I2S_IN_CH_CTL_CLK_TRANS_MASK;

	ret = pm_runसमय_get_sync(i2s->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(i2s->dev);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < i2s->active_channels; i++)
		img_i2s_in_ch_disable(i2s, i);

	/*
	 * BLKP and LRD must be set during separate रेजिस्टर ग_लिखोs
	 */
	क्रम (i = 0; i < i2s->max_i2s_chan; i++) अणु
		reg = img_i2s_in_ch_पढ़ोl(i2s, i, IMG_I2S_IN_CH_CTL);
		reg = (reg & ~chan_control_mask) | chan_control_set;
		img_i2s_in_ch_ग_लिखोl(i2s, i, reg, IMG_I2S_IN_CH_CTL);
		reg = (reg & ~IMG_I2S_IN_CH_CTL_BLKP_MASK) | blkp_set;
		img_i2s_in_ch_ग_लिखोl(i2s, i, reg, IMG_I2S_IN_CH_CTL);
		reg = (reg & ~IMG_I2S_IN_CH_CTL_LRD_MASK) | lrd_set;
		img_i2s_in_ch_ग_लिखोl(i2s, i, reg, IMG_I2S_IN_CH_CTL);
	पूर्ण

	क्रम (i = 0; i < i2s->active_channels; i++)
		img_i2s_in_ch_enable(i2s, i);

	pm_runसमय_put(i2s->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops img_i2s_in_dai_ops = अणु
	.trigger = img_i2s_in_trigger,
	.hw_params = img_i2s_in_hw_params,
	.set_fmt = img_i2s_in_set_fmt
पूर्ण;

अटल पूर्णांक img_i2s_in_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_i2s_in *i2s = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, शून्य, &i2s->dma_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver img_i2s_in_component = अणु
	.name = "img-i2s-in"
पूर्ण;

अटल पूर्णांक img_i2s_in_dma_prepare_slave_config(काष्ठा snd_pcm_substream *st,
	काष्ठा snd_pcm_hw_params *params, काष्ठा dma_slave_config *sc)
अणु
	अचिन्हित पूर्णांक i2s_channels = params_channels(params) / 2;
	काष्ठा snd_soc_pcm_runसमय *rtd = st->निजी_data;
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	पूर्णांक ret;

	dma_data = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), st);

	ret = snd_hwparams_to_dma_slave_config(st, params, sc);
	अगर (ret)
		वापस ret;

	sc->src_addr = dma_data->addr;
	sc->src_addr_width = dma_data->addr_width;
	sc->src_maxburst = 4 * i2s_channels;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_dmaengine_pcm_config img_i2s_in_dma_config = अणु
	.prepare_slave_config = img_i2s_in_dma_prepare_slave_config
पूर्ण;

अटल पूर्णांक img_i2s_in_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा img_i2s_in *i2s;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक ret, i;
	काष्ठा reset_control *rst;
	अचिन्हित पूर्णांक max_i2s_chan_घात_2;
	काष्ठा device *dev = &pdev->dev;

	i2s = devm_kzalloc(dev, माप(*i2s), GFP_KERNEL);
	अगर (!i2s)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, i2s);

	i2s->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	i2s->base = base;

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "img,i2s-channels",
			&i2s->max_i2s_chan)) अणु
		dev_err(dev, "No img,i2s-channels property\n");
		वापस -EINVAL;
	पूर्ण

	max_i2s_chan_घात_2 = 1 << get_count_order(i2s->max_i2s_chan);

	i2s->channel_base = base + (max_i2s_chan_घात_2 * 0x20);

	i2s->clk_sys = devm_clk_get(dev, "sys");
	अगर (IS_ERR(i2s->clk_sys)) अणु
		अगर (PTR_ERR(i2s->clk_sys) != -EPROBE_DEFER)
			dev_err(dev, "Failed to acquire clock 'sys'\n");
		वापस PTR_ERR(i2s->clk_sys);
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = img_i2s_in_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0)
		जाओ err_suspend;

	i2s->active_channels = 1;
	i2s->dma_data.addr = res->start + IMG_I2S_IN_RX_FIFO;
	i2s->dma_data.addr_width = 4;

	i2s->dai_driver.probe = img_i2s_in_dai_probe;
	i2s->dai_driver.capture.channels_min = 2;
	i2s->dai_driver.capture.channels_max = i2s->max_i2s_chan * 2;
	i2s->dai_driver.capture.rates = SNDRV_PCM_RATE_8000_192000;
	i2s->dai_driver.capture.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE |
		SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S16_LE;
	i2s->dai_driver.ops = &img_i2s_in_dai_ops;

	rst = devm_reset_control_get_exclusive(dev, "rst");
	अगर (IS_ERR(rst)) अणु
		अगर (PTR_ERR(rst) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			pm_runसमय_put(&pdev->dev);
			जाओ err_suspend;
		पूर्ण

		dev_dbg(dev, "No top level reset found\n");

		img_i2s_in_disable(i2s);

		क्रम (i = 0; i < i2s->max_i2s_chan; i++)
			img_i2s_in_ch_disable(i2s, i);
	पूर्ण अन्यथा अणु
		reset_control_निश्चित(rst);
		reset_control_deनिश्चित(rst);
	पूर्ण

	img_i2s_in_ग_लिखोl(i2s, 0, IMG_I2S_IN_CTL);

	क्रम (i = 0; i < i2s->max_i2s_chan; i++)
		img_i2s_in_ch_ग_लिखोl(i2s, i,
			(4 << IMG_I2S_IN_CH_CTL_CCDEL_SHIFT) |
			IMG_I2S_IN_CH_CTL_JUST_MASK |
			IMG_I2S_IN_CH_CTL_FW_MASK, IMG_I2S_IN_CH_CTL);

	pm_runसमय_put(&pdev->dev);

	i2s->suspend_ch_ctl = devm_kसुस्मृति(dev,
		i2s->max_i2s_chan, माप(*i2s->suspend_ch_ctl), GFP_KERNEL);
	अगर (!i2s->suspend_ch_ctl) अणु
		ret = -ENOMEM;
		जाओ err_suspend;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(dev, &img_i2s_in_component,
						&i2s->dai_driver, 1);
	अगर (ret)
		जाओ err_suspend;

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(dev, &img_i2s_in_dma_config, 0);
	अगर (ret)
		जाओ err_suspend;

	वापस 0;

err_suspend:
	अगर (!pm_runसमय_enabled(&pdev->dev))
		img_i2s_in_runसमय_suspend(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक img_i2s_in_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		img_i2s_in_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक img_i2s_in_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_i2s_in *i2s = dev_get_drvdata(dev);
	पूर्णांक i, ret;
	u32 reg;

	अगर (pm_runसमय_status_suspended(dev)) अणु
		ret = img_i2s_in_runसमय_resume(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < i2s->max_i2s_chan; i++) अणु
		reg = img_i2s_in_ch_पढ़ोl(i2s, i, IMG_I2S_IN_CH_CTL);
		i2s->suspend_ch_ctl[i] = reg;
	पूर्ण

	i2s->suspend_ctl = img_i2s_in_पढ़ोl(i2s, IMG_I2S_IN_CTL);

	img_i2s_in_runसमय_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक img_i2s_in_resume(काष्ठा device *dev)
अणु
	काष्ठा img_i2s_in *i2s = dev_get_drvdata(dev);
	पूर्णांक i, ret;
	u32 reg;

	ret = img_i2s_in_runसमय_resume(dev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < i2s->max_i2s_chan; i++) अणु
		reg = i2s->suspend_ch_ctl[i];
		img_i2s_in_ch_ग_लिखोl(i2s, i, reg, IMG_I2S_IN_CH_CTL);
	पूर्ण

	img_i2s_in_ग_लिखोl(i2s, i2s->suspend_ctl, IMG_I2S_IN_CTL);

	अगर (pm_runसमय_status_suspended(dev))
		img_i2s_in_runसमय_suspend(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id img_i2s_in_of_match[] = अणु
	अणु .compatible = "img,i2s-in" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, img_i2s_in_of_match);

अटल स्थिर काष्ठा dev_pm_ops img_i2s_in_pm_ops = अणु
	SET_RUNTIME_PM_OPS(img_i2s_in_runसमय_suspend,
			   img_i2s_in_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(img_i2s_in_suspend, img_i2s_in_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver img_i2s_in_driver = अणु
	.driver = अणु
		.name = "img-i2s-in",
		.of_match_table = img_i2s_in_of_match,
		.pm = &img_i2s_in_pm_ops
	पूर्ण,
	.probe = img_i2s_in_probe,
	.हटाओ = img_i2s_in_dev_हटाओ
पूर्ण;
module_platक्रमm_driver(img_i2s_in_driver);

MODULE_AUTHOR("Damien Horsley <Damien.Horsley@imgtec.com>");
MODULE_DESCRIPTION("IMG I2S Input Driver");
MODULE_LICENSE("GPL v2");
