<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Xilinx ASoC I2S audio support
//
// Copyright (C) 2018 Xilinx, Inc.
//
// Author: Praveen Vuppala <praveenv@xilinx.com>
// Author: Maruthi Srinivas Bayyavarapu <maruthis@xilinx.com>

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#घोषणा DRV_NAME "xlnx_i2s"

#घोषणा I2S_CORE_CTRL_OFFSET		0x08
#घोषणा I2S_I2STIM_OFFSET		0x20
#घोषणा I2S_CH0_OFFSET			0x30
#घोषणा I2S_I2STIM_VALID_MASK		GENMASK(7, 0)

अटल पूर्णांक xlnx_i2s_set_sclkout_भाग(काष्ठा snd_soc_dai *cpu_dai,
				    पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	व्योम __iomem *base = snd_soc_dai_get_drvdata(cpu_dai);

	अगर (!भाग || (भाग & ~I2S_I2STIM_VALID_MASK))
		वापस -EINVAL;

	ग_लिखोl(भाग, base + I2S_I2STIM_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक xlnx_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params,
			      काष्ठा snd_soc_dai *i2s_dai)
अणु
	u32 reg_off, chan_id;
	व्योम __iomem *base = snd_soc_dai_get_drvdata(i2s_dai);

	chan_id = params_channels(params) / 2;

	जबतक (chan_id > 0) अणु
		reg_off = I2S_CH0_OFFSET + ((chan_id - 1) * 4);
		ग_लिखोl(chan_id, base + reg_off);
		chan_id--;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlnx_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			    काष्ठा snd_soc_dai *i2s_dai)
अणु
	व्योम __iomem *base = snd_soc_dai_get_drvdata(i2s_dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ग_लिखोl(1, base + I2S_CORE_CTRL_OFFSET);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ग_लिखोl(0, base + I2S_CORE_CTRL_OFFSET);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops xlnx_i2s_dai_ops = अणु
	.trigger = xlnx_i2s_trigger,
	.set_clkभाग = xlnx_i2s_set_sclkout_भाग,
	.hw_params = xlnx_i2s_hw_params
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver xlnx_i2s_component = अणु
	.name = DRV_NAME,
पूर्ण;

अटल स्थिर काष्ठा of_device_id xlnx_i2s_of_match[] = अणु
	अणु .compatible = "xlnx,i2s-transmitter-1.0", पूर्ण,
	अणु .compatible = "xlnx,i2s-receiver-1.0", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xlnx_i2s_of_match);

अटल पूर्णांक xlnx_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *base;
	काष्ठा snd_soc_dai_driver *dai_drv;
	पूर्णांक ret;
	u32 ch, क्रमmat, data_width;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;

	dai_drv = devm_kzalloc(&pdev->dev, माप(*dai_drv), GFP_KERNEL);
	अगर (!dai_drv)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	ret = of_property_पढ़ो_u32(node, "xlnx,num-channels", &ch);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot get supported channels\n");
		वापस ret;
	पूर्ण
	ch = ch * 2;

	ret = of_property_पढ़ो_u32(node, "xlnx,dwidth", &data_width);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot get data width\n");
		वापस ret;
	पूर्ण
	चयन (data_width) अणु
	हाल 16:
		क्रमmat = SNDRV_PCM_FMTBIT_S16_LE;
		अवरोध;
	हाल 24:
		क्रमmat = SNDRV_PCM_FMTBIT_S24_LE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (of_device_is_compatible(node, "xlnx,i2s-transmitter-1.0")) अणु
		dai_drv->name = "xlnx_i2s_playback";
		dai_drv->playback.stream_name = "Playback";
		dai_drv->playback.क्रमmats = क्रमmat;
		dai_drv->playback.channels_min = ch;
		dai_drv->playback.channels_max = ch;
		dai_drv->playback.rates	= SNDRV_PCM_RATE_8000_192000;
		dai_drv->ops = &xlnx_i2s_dai_ops;
	पूर्ण अन्यथा अगर (of_device_is_compatible(node, "xlnx,i2s-receiver-1.0")) अणु
		dai_drv->name = "xlnx_i2s_capture";
		dai_drv->capture.stream_name = "Capture";
		dai_drv->capture.क्रमmats = क्रमmat;
		dai_drv->capture.channels_min = ch;
		dai_drv->capture.channels_max = ch;
		dai_drv->capture.rates = SNDRV_PCM_RATE_8000_192000;
		dai_drv->ops = &xlnx_i2s_dai_ops;
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	dev_set_drvdata(&pdev->dev, base);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &xlnx_i2s_component,
					      dai_drv, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "i2s component registration failed\n");
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "%s DAI registered\n", dai_drv->name);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver xlnx_i2s_aud_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = xlnx_i2s_of_match,
	पूर्ण,
	.probe = xlnx_i2s_probe,
पूर्ण;

module_platक्रमm_driver(xlnx_i2s_aud_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Praveen Vuppala  <praveenv@xilinx.com>");
MODULE_AUTHOR("Maruthi Srinivas Bayyavarapu <maruthis@xilinx.com>");
