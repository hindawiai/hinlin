<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IMG parallel output controller driver
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

#घोषणा IMG_PRL_OUT_TX_FIFO		0

#घोषणा IMG_PRL_OUT_CTL			0x4
#घोषणा IMG_PRL_OUT_CTL_CH_MASK		BIT(4)
#घोषणा IMG_PRL_OUT_CTL_PACKH_MASK	BIT(3)
#घोषणा IMG_PRL_OUT_CTL_EDGE_MASK	BIT(2)
#घोषणा IMG_PRL_OUT_CTL_ME_MASK		BIT(1)
#घोषणा IMG_PRL_OUT_CTL_SRST_MASK	BIT(0)

काष्ठा img_prl_out अणु
	व्योम __iomem *base;
	काष्ठा clk *clk_sys;
	काष्ठा clk *clk_ref;
	काष्ठा snd_dmaengine_dai_dma_data dma_data;
	काष्ठा device *dev;
	काष्ठा reset_control *rst;
पूर्ण;

अटल पूर्णांक img_prl_out_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_prl_out *prl = dev_get_drvdata(dev);

	clk_disable_unprepare(prl->clk_ref);

	वापस 0;
पूर्ण

अटल पूर्णांक img_prl_out_resume(काष्ठा device *dev)
अणु
	काष्ठा img_prl_out *prl = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(prl->clk_ref);
	अगर (ret) अणु
		dev_err(dev, "clk_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम img_prl_out_ग_लिखोl(काष्ठा img_prl_out *prl,
				u32 val, u32 reg)
अणु
	ग_लिखोl(val, prl->base + reg);
पूर्ण

अटल अंतरभूत u32 img_prl_out_पढ़ोl(काष्ठा img_prl_out *prl, u32 reg)
अणु
	वापस पढ़ोl(prl->base + reg);
पूर्ण

अटल व्योम img_prl_out_reset(काष्ठा img_prl_out *prl)
अणु
	u32 ctl;

	ctl = img_prl_out_पढ़ोl(prl, IMG_PRL_OUT_CTL) &
			~IMG_PRL_OUT_CTL_ME_MASK;

	reset_control_निश्चित(prl->rst);
	reset_control_deनिश्चित(prl->rst);

	img_prl_out_ग_लिखोl(prl, ctl, IMG_PRL_OUT_CTL);
पूर्ण

अटल पूर्णांक img_prl_out_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_prl_out *prl = snd_soc_dai_get_drvdata(dai);
	u32 reg;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		reg = img_prl_out_पढ़ोl(prl, IMG_PRL_OUT_CTL);
		reg |= IMG_PRL_OUT_CTL_ME_MASK;
		img_prl_out_ग_लिखोl(prl, reg, IMG_PRL_OUT_CTL);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		img_prl_out_reset(prl);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक img_prl_out_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_prl_out *prl = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक rate, channels;
	u32 reg, control_set = 0;

	rate = params_rate(params);
	channels = params_channels(params);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S32_LE:
		control_set |= IMG_PRL_OUT_CTL_PACKH_MASK;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (channels != 2)
		वापस -EINVAL;

	clk_set_rate(prl->clk_ref, rate * 256);

	reg = img_prl_out_पढ़ोl(prl, IMG_PRL_OUT_CTL);
	reg = (reg & ~IMG_PRL_OUT_CTL_PACKH_MASK) | control_set;
	img_prl_out_ग_लिखोl(prl, reg, IMG_PRL_OUT_CTL);

	वापस 0;
पूर्ण

अटल पूर्णांक img_prl_out_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा img_prl_out *prl = snd_soc_dai_get_drvdata(dai);
	u32 reg, control_set = 0;
	पूर्णांक ret;

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		control_set |= IMG_PRL_OUT_CTL_EDGE_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = pm_runसमय_get_sync(prl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(prl->dev);
		वापस ret;
	पूर्ण

	reg = img_prl_out_पढ़ोl(prl, IMG_PRL_OUT_CTL);
	reg = (reg & ~IMG_PRL_OUT_CTL_EDGE_MASK) | control_set;
	img_prl_out_ग_लिखोl(prl, reg, IMG_PRL_OUT_CTL);
	pm_runसमय_put(prl->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops img_prl_out_dai_ops = अणु
	.trigger = img_prl_out_trigger,
	.hw_params = img_prl_out_hw_params,
	.set_fmt = img_prl_out_set_fmt
पूर्ण;

अटल पूर्णांक img_prl_out_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_prl_out *prl = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &prl->dma_data, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver img_prl_out_dai = अणु
	.probe = img_prl_out_dai_probe,
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S24_LE
	पूर्ण,
	.ops = &img_prl_out_dai_ops
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver img_prl_out_component = अणु
	.name = "img-prl-out"
पूर्ण;

अटल पूर्णांक img_prl_out_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा img_prl_out *prl;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक ret;
	काष्ठा device *dev = &pdev->dev;

	prl = devm_kzalloc(&pdev->dev, माप(*prl), GFP_KERNEL);
	अगर (!prl)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, prl);

	prl->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	prl->base = base;

	prl->rst = devm_reset_control_get_exclusive(&pdev->dev, "rst");
	अगर (IS_ERR(prl->rst)) अणु
		अगर (PTR_ERR(prl->rst) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "No top level reset found\n");
		वापस PTR_ERR(prl->rst);
	पूर्ण

	prl->clk_sys = devm_clk_get(&pdev->dev, "sys");
	अगर (IS_ERR(prl->clk_sys)) अणु
		अगर (PTR_ERR(prl->clk_sys) != -EPROBE_DEFER)
			dev_err(dev, "Failed to acquire clock 'sys'\n");
		वापस PTR_ERR(prl->clk_sys);
	पूर्ण

	prl->clk_ref = devm_clk_get(&pdev->dev, "ref");
	अगर (IS_ERR(prl->clk_ref)) अणु
		अगर (PTR_ERR(prl->clk_ref) != -EPROBE_DEFER)
			dev_err(dev, "Failed to acquire clock 'ref'\n");
		वापस PTR_ERR(prl->clk_ref);
	पूर्ण

	ret = clk_prepare_enable(prl->clk_sys);
	अगर (ret)
		वापस ret;

	img_prl_out_ग_लिखोl(prl, IMG_PRL_OUT_CTL_EDGE_MASK, IMG_PRL_OUT_CTL);
	img_prl_out_reset(prl);

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = img_prl_out_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण

	prl->dma_data.addr = res->start + IMG_PRL_OUT_TX_FIFO;
	prl->dma_data.addr_width = 4;
	prl->dma_data.maxburst = 4;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&img_prl_out_component,
			&img_prl_out_dai, 1);
	अगर (ret)
		जाओ err_suspend;

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (ret)
		जाओ err_suspend;

	वापस 0;

err_suspend:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		img_prl_out_suspend(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(prl->clk_sys);

	वापस ret;
पूर्ण

अटल पूर्णांक img_prl_out_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा img_prl_out *prl = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		img_prl_out_suspend(&pdev->dev);

	clk_disable_unprepare(prl->clk_sys);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id img_prl_out_of_match[] = अणु
	अणु .compatible = "img,parallel-out" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, img_prl_out_of_match);

अटल स्थिर काष्ठा dev_pm_ops img_prl_out_pm_ops = अणु
	SET_RUNTIME_PM_OPS(img_prl_out_suspend,
			   img_prl_out_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver img_prl_out_driver = अणु
	.driver = अणु
		.name = "img-parallel-out",
		.of_match_table = img_prl_out_of_match,
		.pm = &img_prl_out_pm_ops
	पूर्ण,
	.probe = img_prl_out_probe,
	.हटाओ = img_prl_out_dev_हटाओ
पूर्ण;
module_platक्रमm_driver(img_prl_out_driver);

MODULE_AUTHOR("Damien Horsley <Damien.Horsley@imgtec.com>");
MODULE_DESCRIPTION("IMG Parallel Output Driver");
MODULE_LICENSE("GPL v2");
