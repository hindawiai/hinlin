<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IMG I2S output controller driver
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

#घोषणा IMG_I2S_OUT_TX_FIFO			0x0

#घोषणा IMG_I2S_OUT_CTL				0x4
#घोषणा IMG_I2S_OUT_CTL_DATA_EN_MASK		BIT(24)
#घोषणा IMG_I2S_OUT_CTL_ACTIVE_CHAN_MASK	0xffe000
#घोषणा IMG_I2S_OUT_CTL_ACTIVE_CHAN_SHIFT	13
#घोषणा IMG_I2S_OUT_CTL_FRM_SIZE_MASK		BIT(8)
#घोषणा IMG_I2S_OUT_CTL_MASTER_MASK		BIT(6)
#घोषणा IMG_I2S_OUT_CTL_CLK_MASK		BIT(5)
#घोषणा IMG_I2S_OUT_CTL_CLK_EN_MASK		BIT(4)
#घोषणा IMG_I2S_OUT_CTL_FRM_CLK_POL_MASK	BIT(3)
#घोषणा IMG_I2S_OUT_CTL_BCLK_POL_MASK		BIT(2)
#घोषणा IMG_I2S_OUT_CTL_ME_MASK			BIT(0)

#घोषणा IMG_I2S_OUT_CH_CTL			0x4
#घोषणा IMG_I2S_OUT_CHAN_CTL_CH_MASK		BIT(11)
#घोषणा IMG_I2S_OUT_CHAN_CTL_LT_MASK		BIT(10)
#घोषणा IMG_I2S_OUT_CHAN_CTL_FMT_MASK		0xf0
#घोषणा IMG_I2S_OUT_CHAN_CTL_FMT_SHIFT		4
#घोषणा IMG_I2S_OUT_CHAN_CTL_JUST_MASK		BIT(3)
#घोषणा IMG_I2S_OUT_CHAN_CTL_CLKT_MASK		BIT(1)
#घोषणा IMG_I2S_OUT_CHAN_CTL_ME_MASK		BIT(0)

#घोषणा IMG_I2S_OUT_CH_STRIDE			0x20

काष्ठा img_i2s_out अणु
	व्योम __iomem *base;
	काष्ठा clk *clk_sys;
	काष्ठा clk *clk_ref;
	काष्ठा snd_dmaengine_dai_dma_data dma_data;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक max_i2s_chan;
	व्योम __iomem *channel_base;
	bool क्रमce_clk_active;
	अचिन्हित पूर्णांक active_channels;
	काष्ठा reset_control *rst;
	काष्ठा snd_soc_dai_driver dai_driver;
	u32 suspend_ctl;
	u32 *suspend_ch_ctl;
पूर्ण;

अटल पूर्णांक img_i2s_out_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_i2s_out *i2s = dev_get_drvdata(dev);

	clk_disable_unprepare(i2s->clk_ref);
	clk_disable_unprepare(i2s->clk_sys);

	वापस 0;
पूर्ण

अटल पूर्णांक img_i2s_out_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा img_i2s_out *i2s = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(i2s->clk_sys);
	अगर (ret) अणु
		dev_err(dev, "clk_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(i2s->clk_ref);
	अगर (ret) अणु
		dev_err(dev, "clk_enable failed: %d\n", ret);
		clk_disable_unprepare(i2s->clk_sys);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम img_i2s_out_ग_लिखोl(काष्ठा img_i2s_out *i2s, u32 val,
					u32 reg)
अणु
	ग_लिखोl(val, i2s->base + reg);
पूर्ण

अटल अंतरभूत u32 img_i2s_out_पढ़ोl(काष्ठा img_i2s_out *i2s, u32 reg)
अणु
	वापस पढ़ोl(i2s->base + reg);
पूर्ण

अटल अंतरभूत व्योम img_i2s_out_ch_ग_लिखोl(काष्ठा img_i2s_out *i2s,
					u32 chan, u32 val, u32 reg)
अणु
	ग_लिखोl(val, i2s->channel_base + (chan * IMG_I2S_OUT_CH_STRIDE) + reg);
पूर्ण

अटल अंतरभूत u32 img_i2s_out_ch_पढ़ोl(काष्ठा img_i2s_out *i2s, u32 chan,
					u32 reg)
अणु
	वापस पढ़ोl(i2s->channel_base + (chan * IMG_I2S_OUT_CH_STRIDE) + reg);
पूर्ण

अटल अंतरभूत व्योम img_i2s_out_ch_disable(काष्ठा img_i2s_out *i2s, u32 chan)
अणु
	u32 reg;

	reg = img_i2s_out_ch_पढ़ोl(i2s, chan, IMG_I2S_OUT_CH_CTL);
	reg &= ~IMG_I2S_OUT_CHAN_CTL_ME_MASK;
	img_i2s_out_ch_ग_लिखोl(i2s, chan, reg, IMG_I2S_OUT_CH_CTL);
पूर्ण

अटल अंतरभूत व्योम img_i2s_out_ch_enable(काष्ठा img_i2s_out *i2s, u32 chan)
अणु
	u32 reg;

	reg = img_i2s_out_ch_पढ़ोl(i2s, chan, IMG_I2S_OUT_CH_CTL);
	reg |= IMG_I2S_OUT_CHAN_CTL_ME_MASK;
	img_i2s_out_ch_ग_लिखोl(i2s, chan, reg, IMG_I2S_OUT_CH_CTL);
पूर्ण

अटल अंतरभूत व्योम img_i2s_out_disable(काष्ठा img_i2s_out *i2s)
अणु
	u32 reg;

	reg = img_i2s_out_पढ़ोl(i2s, IMG_I2S_OUT_CTL);
	reg &= ~IMG_I2S_OUT_CTL_ME_MASK;
	img_i2s_out_ग_लिखोl(i2s, reg, IMG_I2S_OUT_CTL);
पूर्ण

अटल अंतरभूत व्योम img_i2s_out_enable(काष्ठा img_i2s_out *i2s)
अणु
	u32 reg;

	reg = img_i2s_out_पढ़ोl(i2s, IMG_I2S_OUT_CTL);
	reg |= IMG_I2S_OUT_CTL_ME_MASK;
	img_i2s_out_ग_लिखोl(i2s, reg, IMG_I2S_OUT_CTL);
पूर्ण

अटल व्योम img_i2s_out_reset(काष्ठा img_i2s_out *i2s)
अणु
	पूर्णांक i;
	u32 core_ctl, chan_ctl;

	core_ctl = img_i2s_out_पढ़ोl(i2s, IMG_I2S_OUT_CTL) &
			~IMG_I2S_OUT_CTL_ME_MASK &
			~IMG_I2S_OUT_CTL_DATA_EN_MASK;

	अगर (!i2s->क्रमce_clk_active)
		core_ctl &= ~IMG_I2S_OUT_CTL_CLK_EN_MASK;

	chan_ctl = img_i2s_out_ch_पढ़ोl(i2s, 0, IMG_I2S_OUT_CH_CTL) &
			~IMG_I2S_OUT_CHAN_CTL_ME_MASK;

	reset_control_निश्चित(i2s->rst);
	reset_control_deनिश्चित(i2s->rst);

	क्रम (i = 0; i < i2s->max_i2s_chan; i++)
		img_i2s_out_ch_ग_लिखोl(i2s, i, chan_ctl, IMG_I2S_OUT_CH_CTL);

	क्रम (i = 0; i < i2s->active_channels; i++)
		img_i2s_out_ch_enable(i2s, i);

	img_i2s_out_ग_लिखोl(i2s, core_ctl, IMG_I2S_OUT_CTL);
	img_i2s_out_enable(i2s);
पूर्ण

अटल पूर्णांक img_i2s_out_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_i2s_out *i2s = snd_soc_dai_get_drvdata(dai);
	u32 reg;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		reg = img_i2s_out_पढ़ोl(i2s, IMG_I2S_OUT_CTL);
		अगर (!i2s->क्रमce_clk_active)
			reg |= IMG_I2S_OUT_CTL_CLK_EN_MASK;
		reg |= IMG_I2S_OUT_CTL_DATA_EN_MASK;
		img_i2s_out_ग_लिखोl(i2s, reg, IMG_I2S_OUT_CTL);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		img_i2s_out_reset(i2s);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक img_i2s_out_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_i2s_out *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक channels, i2s_channels;
	दीर्घ pre_भाग_a, pre_भाग_b, dअगरf_a, dअगरf_b, rate, clk_rate;
	पूर्णांक i;
	u32 reg, control_mask, control_set = 0;
	snd_pcm_क्रमmat_t क्रमmat;

	rate = params_rate(params);
	क्रमmat = params_क्रमmat(params);
	channels = params_channels(params);
	i2s_channels = channels / 2;

	अगर (क्रमmat != SNDRV_PCM_FORMAT_S32_LE)
		वापस -EINVAL;

	अगर ((channels < 2) ||
	    (channels > (i2s->max_i2s_chan * 2)) ||
	    (channels % 2))
		वापस -EINVAL;

	pre_भाग_a = clk_round_rate(i2s->clk_ref, rate * 256);
	अगर (pre_भाग_a < 0)
		वापस pre_भाग_a;
	pre_भाग_b = clk_round_rate(i2s->clk_ref, rate * 384);
	अगर (pre_भाग_b < 0)
		वापस pre_भाग_b;

	dअगरf_a = असल((pre_भाग_a / 256) - rate);
	dअगरf_b = असल((pre_भाग_b / 384) - rate);

	/* If dअगरfs are equal, use lower घड़ी rate */
	अगर (dअगरf_a > dअगरf_b)
		clk_set_rate(i2s->clk_ref, pre_भाग_b);
	अन्यथा
		clk_set_rate(i2s->clk_ref, pre_भाग_a);

	/*
	 * Another driver (eg alsa machine driver) may have rejected the above
	 * change. Get the current rate and set the रेजिस्टर bit according to
	 * the new minimum dअगरf
	 */
	clk_rate = clk_get_rate(i2s->clk_ref);

	dअगरf_a = असल((clk_rate / 256) - rate);
	dअगरf_b = असल((clk_rate / 384) - rate);

	अगर (dअगरf_a > dअगरf_b)
		control_set |= IMG_I2S_OUT_CTL_CLK_MASK;

	control_set |= ((i2s_channels - 1) <<
		       IMG_I2S_OUT_CTL_ACTIVE_CHAN_SHIFT) &
		       IMG_I2S_OUT_CTL_ACTIVE_CHAN_MASK;

	control_mask = IMG_I2S_OUT_CTL_CLK_MASK |
		       IMG_I2S_OUT_CTL_ACTIVE_CHAN_MASK;

	img_i2s_out_disable(i2s);

	reg = img_i2s_out_पढ़ोl(i2s, IMG_I2S_OUT_CTL);
	reg = (reg & ~control_mask) | control_set;
	img_i2s_out_ग_लिखोl(i2s, reg, IMG_I2S_OUT_CTL);

	क्रम (i = 0; i < i2s_channels; i++)
		img_i2s_out_ch_enable(i2s, i);

	क्रम (; i < i2s->max_i2s_chan; i++)
		img_i2s_out_ch_disable(i2s, i);

	img_i2s_out_enable(i2s);

	i2s->active_channels = i2s_channels;

	वापस 0;
पूर्ण

अटल पूर्णांक img_i2s_out_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा img_i2s_out *i2s = snd_soc_dai_get_drvdata(dai);
	पूर्णांक i, ret;
	bool क्रमce_clk_active;
	u32 chan_control_mask, control_mask, chan_control_set = 0;
	u32 reg, control_set = 0;

	क्रमce_clk_active = ((fmt & SND_SOC_DAIFMT_CLOCK_MASK) ==
			SND_SOC_DAIFMT_CONT);

	अगर (क्रमce_clk_active)
		control_set |= IMG_I2S_OUT_CTL_CLK_EN_MASK;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		control_set |= IMG_I2S_OUT_CTL_MASTER_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		control_set |= IMG_I2S_OUT_CTL_BCLK_POL_MASK;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		control_set |= IMG_I2S_OUT_CTL_BCLK_POL_MASK;
		control_set |= IMG_I2S_OUT_CTL_FRM_CLK_POL_MASK;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		control_set |= IMG_I2S_OUT_CTL_FRM_CLK_POL_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		chan_control_set |= IMG_I2S_OUT_CHAN_CTL_CLKT_MASK;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	control_mask = IMG_I2S_OUT_CTL_CLK_EN_MASK |
		       IMG_I2S_OUT_CTL_MASTER_MASK |
		       IMG_I2S_OUT_CTL_BCLK_POL_MASK |
		       IMG_I2S_OUT_CTL_FRM_CLK_POL_MASK;

	chan_control_mask = IMG_I2S_OUT_CHAN_CTL_CLKT_MASK;

	ret = pm_runसमय_get_sync(i2s->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(i2s->dev);
		वापस ret;
	पूर्ण

	img_i2s_out_disable(i2s);

	reg = img_i2s_out_पढ़ोl(i2s, IMG_I2S_OUT_CTL);
	reg = (reg & ~control_mask) | control_set;
	img_i2s_out_ग_लिखोl(i2s, reg, IMG_I2S_OUT_CTL);

	क्रम (i = 0; i < i2s->active_channels; i++)
		img_i2s_out_ch_disable(i2s, i);

	क्रम (i = 0; i < i2s->max_i2s_chan; i++) अणु
		reg = img_i2s_out_ch_पढ़ोl(i2s, i, IMG_I2S_OUT_CH_CTL);
		reg = (reg & ~chan_control_mask) | chan_control_set;
		img_i2s_out_ch_ग_लिखोl(i2s, i, reg, IMG_I2S_OUT_CH_CTL);
	पूर्ण

	क्रम (i = 0; i < i2s->active_channels; i++)
		img_i2s_out_ch_enable(i2s, i);

	img_i2s_out_enable(i2s);
	pm_runसमय_put(i2s->dev);

	i2s->क्रमce_clk_active = क्रमce_clk_active;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops img_i2s_out_dai_ops = अणु
	.trigger = img_i2s_out_trigger,
	.hw_params = img_i2s_out_hw_params,
	.set_fmt = img_i2s_out_set_fmt
पूर्ण;

अटल पूर्णांक img_i2s_out_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_i2s_out *i2s = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &i2s->dma_data, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver img_i2s_out_component = अणु
	.name = "img-i2s-out"
पूर्ण;

अटल पूर्णांक img_i2s_out_dma_prepare_slave_config(काष्ठा snd_pcm_substream *st,
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

	sc->dst_addr = dma_data->addr;
	sc->dst_addr_width = dma_data->addr_width;
	sc->dst_maxburst = 4 * i2s_channels;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_dmaengine_pcm_config img_i2s_out_dma_config = अणु
	.prepare_slave_config = img_i2s_out_dma_prepare_slave_config
पूर्ण;

अटल पूर्णांक img_i2s_out_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा img_i2s_out *i2s;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक max_i2s_chan_घात_2;
	u32 reg;
	काष्ठा device *dev = &pdev->dev;

	i2s = devm_kzalloc(&pdev->dev, माप(*i2s), GFP_KERNEL);
	अगर (!i2s)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, i2s);

	i2s->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	i2s->base = base;

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "img,i2s-channels",
			&i2s->max_i2s_chan)) अणु
		dev_err(&pdev->dev, "No img,i2s-channels property\n");
		वापस -EINVAL;
	पूर्ण

	max_i2s_chan_घात_2 = 1 << get_count_order(i2s->max_i2s_chan);

	i2s->channel_base = base + (max_i2s_chan_घात_2 * 0x20);

	i2s->rst = devm_reset_control_get_exclusive(&pdev->dev, "rst");
	अगर (IS_ERR(i2s->rst)) अणु
		अगर (PTR_ERR(i2s->rst) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "No top level reset found\n");
		वापस PTR_ERR(i2s->rst);
	पूर्ण

	i2s->clk_sys = devm_clk_get(&pdev->dev, "sys");
	अगर (IS_ERR(i2s->clk_sys)) अणु
		अगर (PTR_ERR(i2s->clk_sys) != -EPROBE_DEFER)
			dev_err(dev, "Failed to acquire clock 'sys'\n");
		वापस PTR_ERR(i2s->clk_sys);
	पूर्ण

	i2s->clk_ref = devm_clk_get(&pdev->dev, "ref");
	अगर (IS_ERR(i2s->clk_ref)) अणु
		अगर (PTR_ERR(i2s->clk_ref) != -EPROBE_DEFER)
			dev_err(dev, "Failed to acquire clock 'ref'\n");
		वापस PTR_ERR(i2s->clk_ref);
	पूर्ण

	i2s->suspend_ch_ctl = devm_kसुस्मृति(dev,
		i2s->max_i2s_chan, माप(*i2s->suspend_ch_ctl), GFP_KERNEL);
	अगर (!i2s->suspend_ch_ctl)
		वापस -ENOMEM;

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = img_i2s_out_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		जाओ err_suspend;
	पूर्ण

	reg = IMG_I2S_OUT_CTL_FRM_SIZE_MASK;
	img_i2s_out_ग_लिखोl(i2s, reg, IMG_I2S_OUT_CTL);

	reg = IMG_I2S_OUT_CHAN_CTL_JUST_MASK |
		IMG_I2S_OUT_CHAN_CTL_LT_MASK |
		IMG_I2S_OUT_CHAN_CTL_CH_MASK |
		(8 << IMG_I2S_OUT_CHAN_CTL_FMT_SHIFT);

	क्रम (i = 0; i < i2s->max_i2s_chan; i++)
		img_i2s_out_ch_ग_लिखोl(i2s, i, reg, IMG_I2S_OUT_CH_CTL);

	img_i2s_out_reset(i2s);
	pm_runसमय_put(&pdev->dev);

	i2s->active_channels = 1;
	i2s->dma_data.addr = res->start + IMG_I2S_OUT_TX_FIFO;
	i2s->dma_data.addr_width = 4;
	i2s->dma_data.maxburst = 4;

	i2s->dai_driver.probe = img_i2s_out_dai_probe;
	i2s->dai_driver.playback.channels_min = 2;
	i2s->dai_driver.playback.channels_max = i2s->max_i2s_chan * 2;
	i2s->dai_driver.playback.rates = SNDRV_PCM_RATE_8000_192000;
	i2s->dai_driver.playback.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE;
	i2s->dai_driver.ops = &img_i2s_out_dai_ops;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&img_i2s_out_component, &i2s->dai_driver, 1);
	अगर (ret)
		जाओ err_suspend;

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev,
			&img_i2s_out_dma_config, 0);
	अगर (ret)
		जाओ err_suspend;

	वापस 0;

err_suspend:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		img_i2s_out_runसमय_suspend(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक img_i2s_out_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		img_i2s_out_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक img_i2s_out_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_i2s_out *i2s = dev_get_drvdata(dev);
	पूर्णांक i, ret;
	u32 reg;

	अगर (pm_runसमय_status_suspended(dev)) अणु
		ret = img_i2s_out_runसमय_resume(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < i2s->max_i2s_chan; i++) अणु
		reg = img_i2s_out_ch_पढ़ोl(i2s, i, IMG_I2S_OUT_CH_CTL);
		i2s->suspend_ch_ctl[i] = reg;
	पूर्ण

	i2s->suspend_ctl = img_i2s_out_पढ़ोl(i2s, IMG_I2S_OUT_CTL);

	img_i2s_out_runसमय_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक img_i2s_out_resume(काष्ठा device *dev)
अणु
	काष्ठा img_i2s_out *i2s = dev_get_drvdata(dev);
	पूर्णांक i, ret;
	u32 reg;

	ret = img_i2s_out_runसमय_resume(dev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < i2s->max_i2s_chan; i++) अणु
		reg = i2s->suspend_ch_ctl[i];
		img_i2s_out_ch_ग_लिखोl(i2s, i, reg, IMG_I2S_OUT_CH_CTL);
	पूर्ण

	img_i2s_out_ग_लिखोl(i2s, i2s->suspend_ctl, IMG_I2S_OUT_CTL);

	अगर (pm_runसमय_status_suspended(dev))
		img_i2s_out_runसमय_suspend(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id img_i2s_out_of_match[] = अणु
	अणु .compatible = "img,i2s-out" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, img_i2s_out_of_match);

अटल स्थिर काष्ठा dev_pm_ops img_i2s_out_pm_ops = अणु
	SET_RUNTIME_PM_OPS(img_i2s_out_runसमय_suspend,
			   img_i2s_out_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(img_i2s_out_suspend, img_i2s_out_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver img_i2s_out_driver = अणु
	.driver = अणु
		.name = "img-i2s-out",
		.of_match_table = img_i2s_out_of_match,
		.pm = &img_i2s_out_pm_ops
	पूर्ण,
	.probe = img_i2s_out_probe,
	.हटाओ = img_i2s_out_dev_हटाओ
पूर्ण;
module_platक्रमm_driver(img_i2s_out_driver);

MODULE_AUTHOR("Damien Horsley <Damien.Horsley@imgtec.com>");
MODULE_DESCRIPTION("IMG I2S Output Driver");
MODULE_LICENSE("GPL v2");
