<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IMG SPDIF output controller driver
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

#घोषणा IMG_SPDIF_OUT_TX_FIFO		0x0

#घोषणा IMG_SPDIF_OUT_CTL		0x4
#घोषणा IMG_SPDIF_OUT_CTL_FS_MASK	BIT(4)
#घोषणा IMG_SPDIF_OUT_CTL_CLK_MASK	BIT(2)
#घोषणा IMG_SPDIF_OUT_CTL_SRT_MASK	BIT(0)

#घोषणा IMG_SPDIF_OUT_CSL		0x14

#घोषणा IMG_SPDIF_OUT_CSH_UV		0x18
#घोषणा IMG_SPDIF_OUT_CSH_UV_CSH_SHIFT	0
#घोषणा IMG_SPDIF_OUT_CSH_UV_CSH_MASK	0xff

काष्ठा img_spdअगर_out अणु
	spinlock_t lock;
	व्योम __iomem *base;
	काष्ठा clk *clk_sys;
	काष्ठा clk *clk_ref;
	काष्ठा snd_dmaengine_dai_dma_data dma_data;
	काष्ठा device *dev;
	काष्ठा reset_control *rst;
	u32 suspend_ctl;
	u32 suspend_csl;
	u32 suspend_csh;
पूर्ण;

अटल पूर्णांक img_spdअगर_out_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_spdअगर_out *spdअगर = dev_get_drvdata(dev);

	clk_disable_unprepare(spdअगर->clk_ref);
	clk_disable_unprepare(spdअगर->clk_sys);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_out_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा img_spdअगर_out *spdअगर = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(spdअगर->clk_sys);
	अगर (ret) अणु
		dev_err(dev, "clk_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(spdअगर->clk_ref);
	अगर (ret) अणु
		dev_err(dev, "clk_enable failed: %d\n", ret);
		clk_disable_unprepare(spdअगर->clk_sys);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम img_spdअगर_out_ग_लिखोl(काष्ठा img_spdअगर_out *spdअगर, u32 val,
				u32 reg)
अणु
	ग_लिखोl(val, spdअगर->base + reg);
पूर्ण

अटल अंतरभूत u32 img_spdअगर_out_पढ़ोl(काष्ठा img_spdअगर_out *spdअगर, u32 reg)
अणु
	वापस पढ़ोl(spdअगर->base + reg);
पूर्ण

अटल व्योम img_spdअगर_out_reset(काष्ठा img_spdअगर_out *spdअगर)
अणु
	u32 ctl, status_low, status_high;

	ctl = img_spdअगर_out_पढ़ोl(spdअगर, IMG_SPDIF_OUT_CTL) &
			~IMG_SPDIF_OUT_CTL_SRT_MASK;
	status_low = img_spdअगर_out_पढ़ोl(spdअगर, IMG_SPDIF_OUT_CSL);
	status_high = img_spdअगर_out_पढ़ोl(spdअगर, IMG_SPDIF_OUT_CSH_UV);

	reset_control_निश्चित(spdअगर->rst);
	reset_control_deनिश्चित(spdअगर->rst);

	img_spdअगर_out_ग_लिखोl(spdअगर, ctl, IMG_SPDIF_OUT_CTL);
	img_spdअगर_out_ग_लिखोl(spdअगर, status_low, IMG_SPDIF_OUT_CSL);
	img_spdअगर_out_ग_लिखोl(spdअगर, status_high, IMG_SPDIF_OUT_CSH_UV);
पूर्ण

अटल पूर्णांक img_spdअगर_out_info(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_out_get_status_mask(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0xff;
	ucontrol->value.iec958.status[3] = 0xff;
	ucontrol->value.iec958.status[4] = 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_out_get_status(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा img_spdअगर_out *spdअगर = snd_soc_dai_get_drvdata(cpu_dai);
	u32 reg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spdअगर->lock, flags);

	reg = img_spdअगर_out_पढ़ोl(spdअगर, IMG_SPDIF_OUT_CSL);
	ucontrol->value.iec958.status[0] = reg & 0xff;
	ucontrol->value.iec958.status[1] = (reg >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (reg >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (reg >> 24) & 0xff;

	reg = img_spdअगर_out_पढ़ोl(spdअगर, IMG_SPDIF_OUT_CSH_UV);
	ucontrol->value.iec958.status[4] =
		(reg & IMG_SPDIF_OUT_CSH_UV_CSH_MASK) >>
		IMG_SPDIF_OUT_CSH_UV_CSH_SHIFT;

	spin_unlock_irqrestore(&spdअगर->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_out_set_status(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा img_spdअगर_out *spdअगर = snd_soc_dai_get_drvdata(cpu_dai);
	u32 reg;
	अचिन्हित दीर्घ flags;

	reg = ((u32)ucontrol->value.iec958.status[3] << 24);
	reg |= ((u32)ucontrol->value.iec958.status[2] << 16);
	reg |= ((u32)ucontrol->value.iec958.status[1] << 8);
	reg |= (u32)ucontrol->value.iec958.status[0];

	spin_lock_irqsave(&spdअगर->lock, flags);

	img_spdअगर_out_ग_लिखोl(spdअगर, reg, IMG_SPDIF_OUT_CSL);

	reg = img_spdअगर_out_पढ़ोl(spdअगर, IMG_SPDIF_OUT_CSH_UV);
	reg &= ~IMG_SPDIF_OUT_CSH_UV_CSH_MASK;
	reg |= (u32)ucontrol->value.iec958.status[4] <<
			IMG_SPDIF_OUT_CSH_UV_CSH_SHIFT;
	img_spdअगर_out_ग_लिखोl(spdअगर, reg, IMG_SPDIF_OUT_CSH_UV);

	spin_unlock_irqrestore(&spdअगर->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा snd_kcontrol_new img_spdअगर_out_controls[] = अणु
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, MASK),
		.info = img_spdअगर_out_info,
		.get = img_spdअगर_out_get_status_mask
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
		.info = img_spdअगर_out_info,
		.get = img_spdअगर_out_get_status,
		.put = img_spdअगर_out_set_status
	पूर्ण
पूर्ण;

अटल पूर्णांक img_spdअगर_out_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_spdअगर_out *spdअगर = snd_soc_dai_get_drvdata(dai);
	u32 reg;
	अचिन्हित दीर्घ flags;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		reg = img_spdअगर_out_पढ़ोl(spdअगर, IMG_SPDIF_OUT_CTL);
		reg |= IMG_SPDIF_OUT_CTL_SRT_MASK;
		img_spdअगर_out_ग_लिखोl(spdअगर, reg, IMG_SPDIF_OUT_CTL);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		spin_lock_irqsave(&spdअगर->lock, flags);
		img_spdअगर_out_reset(spdअगर);
		spin_unlock_irqrestore(&spdअगर->lock, flags);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_out_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_spdअगर_out *spdअगर = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक channels;
	दीर्घ pre_भाग_a, pre_भाग_b, dअगरf_a, dअगरf_b, rate, clk_rate;
	u32 reg;
	snd_pcm_क्रमmat_t क्रमmat;

	rate = params_rate(params);
	क्रमmat = params_क्रमmat(params);
	channels = params_channels(params);

	dev_dbg(spdअगर->dev, "hw_params rate %ld channels %u format %u\n",
			rate, channels, क्रमmat);

	अगर (क्रमmat != SNDRV_PCM_FORMAT_S32_LE)
		वापस -EINVAL;

	अगर (channels != 2)
		वापस -EINVAL;

	pre_भाग_a = clk_round_rate(spdअगर->clk_ref, rate * 256);
	अगर (pre_भाग_a < 0)
		वापस pre_भाग_a;
	pre_भाग_b = clk_round_rate(spdअगर->clk_ref, rate * 384);
	अगर (pre_भाग_b < 0)
		वापस pre_भाग_b;

	dअगरf_a = असल((pre_भाग_a / 256) - rate);
	dअगरf_b = असल((pre_भाग_b / 384) - rate);

	/* If dअगरfs are equal, use lower घड़ी rate */
	अगर (dअगरf_a > dअगरf_b)
		clk_set_rate(spdअगर->clk_ref, pre_भाग_b);
	अन्यथा
		clk_set_rate(spdअगर->clk_ref, pre_भाग_a);

	/*
	 * Another driver (eg machine driver) may have rejected the above
	 * change. Get the current rate and set the रेजिस्टर bit according to
	 * the new min dअगरf
	 */
	clk_rate = clk_get_rate(spdअगर->clk_ref);

	dअगरf_a = असल((clk_rate / 256) - rate);
	dअगरf_b = असल((clk_rate / 384) - rate);

	reg = img_spdअगर_out_पढ़ोl(spdअगर, IMG_SPDIF_OUT_CTL);
	अगर (dअगरf_a <= dअगरf_b)
		reg &= ~IMG_SPDIF_OUT_CTL_CLK_MASK;
	अन्यथा
		reg |= IMG_SPDIF_OUT_CTL_CLK_MASK;
	img_spdअगर_out_ग_लिखोl(spdअगर, reg, IMG_SPDIF_OUT_CTL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops img_spdअगर_out_dai_ops = अणु
	.trigger = img_spdअगर_out_trigger,
	.hw_params = img_spdअगर_out_hw_params
पूर्ण;

अटल पूर्णांक img_spdअगर_out_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_spdअगर_out *spdअगर = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &spdअगर->dma_data, शून्य);

	snd_soc_add_dai_controls(dai, img_spdअगर_out_controls,
			ARRAY_SIZE(img_spdअगर_out_controls));

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver img_spdअगर_out_dai = अणु
	.probe = img_spdअगर_out_dai_probe,
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE
	पूर्ण,
	.ops = &img_spdअगर_out_dai_ops
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver img_spdअगर_out_component = अणु
	.name = "img-spdif-out"
पूर्ण;

अटल पूर्णांक img_spdअगर_out_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा img_spdअगर_out *spdअगर;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक ret;
	काष्ठा device *dev = &pdev->dev;

	spdअगर = devm_kzalloc(&pdev->dev, माप(*spdअगर), GFP_KERNEL);
	अगर (!spdअगर)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, spdअगर);

	spdअगर->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	spdअगर->base = base;

	spdअगर->rst = devm_reset_control_get_exclusive(&pdev->dev, "rst");
	अगर (IS_ERR(spdअगर->rst)) अणु
		अगर (PTR_ERR(spdअगर->rst) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "No top level reset found\n");
		वापस PTR_ERR(spdअगर->rst);
	पूर्ण

	spdअगर->clk_sys = devm_clk_get(&pdev->dev, "sys");
	अगर (IS_ERR(spdअगर->clk_sys)) अणु
		अगर (PTR_ERR(spdअगर->clk_sys) != -EPROBE_DEFER)
			dev_err(dev, "Failed to acquire clock 'sys'\n");
		वापस PTR_ERR(spdअगर->clk_sys);
	पूर्ण

	spdअगर->clk_ref = devm_clk_get(&pdev->dev, "ref");
	अगर (IS_ERR(spdअगर->clk_ref)) अणु
		अगर (PTR_ERR(spdअगर->clk_ref) != -EPROBE_DEFER)
			dev_err(dev, "Failed to acquire clock 'ref'\n");
		वापस PTR_ERR(spdअगर->clk_ref);
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = img_spdअगर_out_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		जाओ err_suspend;
	पूर्ण

	img_spdअगर_out_ग_लिखोl(spdअगर, IMG_SPDIF_OUT_CTL_FS_MASK,
			     IMG_SPDIF_OUT_CTL);

	img_spdअगर_out_reset(spdअगर);
	pm_runसमय_put(&pdev->dev);

	spin_lock_init(&spdअगर->lock);

	spdअगर->dma_data.addr = res->start + IMG_SPDIF_OUT_TX_FIFO;
	spdअगर->dma_data.addr_width = 4;
	spdअगर->dma_data.maxburst = 4;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&img_spdअगर_out_component,
			&img_spdअगर_out_dai, 1);
	अगर (ret)
		जाओ err_suspend;

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (ret)
		जाओ err_suspend;

	dev_dbg(&pdev->dev, "Probe successful\n");

	वापस 0;

err_suspend:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		img_spdअगर_out_runसमय_suspend(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक img_spdअगर_out_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		img_spdअगर_out_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक img_spdअगर_out_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_spdअगर_out *spdअगर = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (pm_runसमय_status_suspended(dev)) अणु
		ret = img_spdअगर_out_runसमय_resume(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	spdअगर->suspend_ctl = img_spdअगर_out_पढ़ोl(spdअगर, IMG_SPDIF_OUT_CTL);
	spdअगर->suspend_csl = img_spdअगर_out_पढ़ोl(spdअगर, IMG_SPDIF_OUT_CSL);
	spdअगर->suspend_csh = img_spdअगर_out_पढ़ोl(spdअगर, IMG_SPDIF_OUT_CSH_UV);

	img_spdअगर_out_runसमय_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_out_resume(काष्ठा device *dev)
अणु
	काष्ठा img_spdअगर_out *spdअगर = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = img_spdअगर_out_runसमय_resume(dev);
	अगर (ret)
		वापस ret;

	img_spdअगर_out_ग_लिखोl(spdअगर, spdअगर->suspend_ctl, IMG_SPDIF_OUT_CTL);
	img_spdअगर_out_ग_लिखोl(spdअगर, spdअगर->suspend_csl, IMG_SPDIF_OUT_CSL);
	img_spdअगर_out_ग_लिखोl(spdअगर, spdअगर->suspend_csh, IMG_SPDIF_OUT_CSH_UV);

	अगर (pm_runसमय_status_suspended(dev))
		img_spdअगर_out_runसमय_suspend(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल स्थिर काष्ठा of_device_id img_spdअगर_out_of_match[] = अणु
	अणु .compatible = "img,spdif-out" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, img_spdअगर_out_of_match);

अटल स्थिर काष्ठा dev_pm_ops img_spdअगर_out_pm_ops = अणु
	SET_RUNTIME_PM_OPS(img_spdअगर_out_runसमय_suspend,
			   img_spdअगर_out_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(img_spdअगर_out_suspend, img_spdअगर_out_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver img_spdअगर_out_driver = अणु
	.driver = अणु
		.name = "img-spdif-out",
		.of_match_table = img_spdअगर_out_of_match,
		.pm = &img_spdअगर_out_pm_ops
	पूर्ण,
	.probe = img_spdअगर_out_probe,
	.हटाओ = img_spdअगर_out_dev_हटाओ
पूर्ण;
module_platक्रमm_driver(img_spdअगर_out_driver);

MODULE_AUTHOR("Damien Horsley <Damien.Horsley@imgtec.com>");
MODULE_DESCRIPTION("IMG SPDIF Output driver");
MODULE_LICENSE("GPL v2");
