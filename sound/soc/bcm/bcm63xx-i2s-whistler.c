<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
// linux/sound/bcm/bcm63xx-i2s-whistler.c
// BCM63xx whistler i2s driver
// Copyright (c) 2020 Broadcom Corporation
// Author: Kevin-Ke Li <kevin-ke.li@broadcom.com>

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "bcm63xx-i2s.h"

#घोषणा DRV_NAME "brcm-i2s"

अटल bool brcm_i2s_wr_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल I2S_TX_CFG ... I2S_TX_DESC_IFF_LEN:
	हाल I2S_TX_CFG_2 ... I2S_RX_DESC_IFF_LEN:
	हाल I2S_RX_CFG_2 ... I2S_REG_MAX:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool brcm_i2s_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल I2S_TX_CFG ... I2S_REG_MAX:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool brcm_i2s_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल I2S_TX_CFG:
	हाल I2S_TX_IRQ_CTL:
	हाल I2S_TX_DESC_IFF_ADDR:
	हाल I2S_TX_DESC_IFF_LEN:
	हाल I2S_TX_DESC_OFF_ADDR:
	हाल I2S_TX_DESC_OFF_LEN:
	हाल I2S_TX_CFG_2:
	हाल I2S_RX_CFG:
	हाल I2S_RX_IRQ_CTL:
	हाल I2S_RX_DESC_OFF_ADDR:
	हाल I2S_RX_DESC_OFF_LEN:
	हाल I2S_RX_DESC_IFF_LEN:
	हाल I2S_RX_DESC_IFF_ADDR:
	हाल I2S_RX_CFG_2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config brcm_i2s_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = I2S_REG_MAX,
	.ग_लिखोable_reg = brcm_i2s_wr_reg,
	.पढ़ोable_reg = brcm_i2s_rd_reg,
	.अस्थिर_reg = brcm_i2s_अस्थिर_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक bcm63xx_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret = 0;
	काष्ठा bcm_i2s_priv *i2s_priv = snd_soc_dai_get_drvdata(dai);

	ret = clk_set_rate(i2s_priv->i2s_clk, params_rate(params));
	अगर (ret < 0)
		dev_err(i2s_priv->dev,
			"Can't set sample rate, err: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm63xx_i2s_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	अचिन्हित पूर्णांक slavemode;
	काष्ठा bcm_i2s_priv *i2s_priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा regmap *regmap_i2s = i2s_priv->regmap_i2s;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		regmap_update_bits(regmap_i2s, I2S_TX_CFG,
				   I2S_TX_OUT_R | I2S_TX_DATA_ALIGNMENT |
				   I2S_TX_DATA_ENABLE | I2S_TX_CLOCK_ENABLE,
				   I2S_TX_OUT_R | I2S_TX_DATA_ALIGNMENT |
				   I2S_TX_DATA_ENABLE | I2S_TX_CLOCK_ENABLE);
		regmap_ग_लिखो(regmap_i2s, I2S_TX_IRQ_CTL, 0);
		regmap_ग_लिखो(regmap_i2s, I2S_TX_IRQ_IFF_THLD, 0);
		regmap_ग_लिखो(regmap_i2s, I2S_TX_IRQ_OFF_THLD, 1);

		/* TX and RX block each have an independent bit to indicate
		 * अगर it is generating the घड़ी क्रम the I2S bus. The bus
		 * घड़ीs need to be generated from either the TX or RX block,
		 * but not both
		 */
		regmap_पढ़ो(regmap_i2s, I2S_RX_CFG_2, &slavemode);
		अगर (slavemode & I2S_RX_SLAVE_MODE_MASK)
			regmap_update_bits(regmap_i2s, I2S_TX_CFG_2,
					   I2S_TX_SLAVE_MODE_MASK,
					   I2S_TX_MASTER_MODE);
		अन्यथा
			regmap_update_bits(regmap_i2s, I2S_TX_CFG_2,
					   I2S_TX_SLAVE_MODE_MASK,
					   I2S_TX_SLAVE_MODE);
	पूर्ण अन्यथा अणु
		regmap_update_bits(regmap_i2s, I2S_RX_CFG,
				   I2S_RX_IN_R | I2S_RX_DATA_ALIGNMENT |
				   I2S_RX_CLOCK_ENABLE,
				   I2S_RX_IN_R | I2S_RX_DATA_ALIGNMENT |
				   I2S_RX_CLOCK_ENABLE);
		regmap_ग_लिखो(regmap_i2s, I2S_RX_IRQ_CTL, 0);
		regmap_ग_लिखो(regmap_i2s, I2S_RX_IRQ_IFF_THLD, 0);
		regmap_ग_लिखो(regmap_i2s, I2S_RX_IRQ_OFF_THLD, 1);

		regmap_पढ़ो(regmap_i2s, I2S_TX_CFG_2, &slavemode);
		अगर (slavemode & I2S_TX_SLAVE_MODE_MASK)
			regmap_update_bits(regmap_i2s, I2S_RX_CFG_2,
					   I2S_RX_SLAVE_MODE_MASK, 0);
		अन्यथा
			regmap_update_bits(regmap_i2s, I2S_RX_CFG_2,
					   I2S_RX_SLAVE_MODE_MASK,
					   I2S_RX_SLAVE_MODE);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bcm63xx_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	अचिन्हित पूर्णांक enabled, slavemode;
	काष्ठा bcm_i2s_priv *i2s_priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा regmap *regmap_i2s = i2s_priv->regmap_i2s;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		regmap_update_bits(regmap_i2s, I2S_TX_CFG,
				   I2S_TX_OUT_R | I2S_TX_DATA_ALIGNMENT |
				   I2S_TX_DATA_ENABLE | I2S_TX_CLOCK_ENABLE, 0);
		regmap_ग_लिखो(regmap_i2s, I2S_TX_IRQ_CTL, 1);
		regmap_ग_लिखो(regmap_i2s, I2S_TX_IRQ_IFF_THLD, 4);
		regmap_ग_लिखो(regmap_i2s, I2S_TX_IRQ_OFF_THLD, 4);

		regmap_पढ़ो(regmap_i2s, I2S_TX_CFG_2, &slavemode);
		slavemode = slavemode & I2S_TX_SLAVE_MODE_MASK;
		अगर (!slavemode) अणु
			regmap_पढ़ो(regmap_i2s, I2S_RX_CFG, &enabled);
			enabled = enabled & I2S_RX_ENABLE_MASK;
			अगर (enabled)
				regmap_update_bits(regmap_i2s, I2S_RX_CFG_2,
						   I2S_RX_SLAVE_MODE_MASK,
						   I2S_RX_MASTER_MODE);
		पूर्ण
		regmap_update_bits(regmap_i2s, I2S_TX_CFG_2,
				   I2S_TX_SLAVE_MODE_MASK,
				   I2S_TX_SLAVE_MODE);
	पूर्ण अन्यथा अणु
		regmap_update_bits(regmap_i2s, I2S_RX_CFG,
				   I2S_RX_IN_R | I2S_RX_DATA_ALIGNMENT |
				   I2S_RX_CLOCK_ENABLE, 0);
		regmap_ग_लिखो(regmap_i2s, I2S_RX_IRQ_CTL, 1);
		regmap_ग_लिखो(regmap_i2s, I2S_RX_IRQ_IFF_THLD, 4);
		regmap_ग_लिखो(regmap_i2s, I2S_RX_IRQ_OFF_THLD, 4);

		regmap_पढ़ो(regmap_i2s, I2S_RX_CFG_2, &slavemode);
		slavemode = slavemode & I2S_RX_SLAVE_MODE_MASK;
		अगर (!slavemode) अणु
			regmap_पढ़ो(regmap_i2s, I2S_TX_CFG, &enabled);
			enabled = enabled & I2S_TX_ENABLE_MASK;
			अगर (enabled)
				regmap_update_bits(regmap_i2s, I2S_TX_CFG_2,
						   I2S_TX_SLAVE_MODE_MASK,
						   I2S_TX_MASTER_MODE);
		पूर्ण

		regmap_update_bits(regmap_i2s, I2S_RX_CFG_2,
				   I2S_RX_SLAVE_MODE_MASK, I2S_RX_SLAVE_MODE);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops bcm63xx_i2s_dai_ops = अणु
	.startup = bcm63xx_i2s_startup,
	.shutकरोwn = bcm63xx_i2s_shutकरोwn,
	.hw_params = bcm63xx_i2s_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver bcm63xx_i2s_dai = अणु
	.name = DRV_NAME,
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
	.ops = &bcm63xx_i2s_dai_ops,
	.symmetric_rate = 1,
	.symmetric_channels = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver bcm63xx_i2s_component = अणु
	.name = "bcm63xx",
पूर्ण;

अटल पूर्णांक bcm63xx_i2s_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	व्योम __iomem *regs;
	काष्ठा resource *r_mem, *region;
	काष्ठा bcm_i2s_priv *i2s_priv;
	काष्ठा regmap *regmap_i2s;
	काष्ठा clk *i2s_clk;

	i2s_priv = devm_kzalloc(&pdev->dev, माप(*i2s_priv), GFP_KERNEL);
	अगर (!i2s_priv)
		वापस -ENOMEM;

	i2s_clk = devm_clk_get(&pdev->dev, "i2sclk");
	अगर (IS_ERR(i2s_clk)) अणु
		dev_err(&pdev->dev, "%s: cannot get a brcm clock: %ld\n",
					__func__, PTR_ERR(i2s_clk));
		वापस PTR_ERR(i2s_clk);
	पूर्ण

	r_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r_mem) अणु
		dev_err(&pdev->dev, "Unable to get register resource.\n");
		वापस -ENODEV;
	पूर्ण

	region = devm_request_mem_region(&pdev->dev, r_mem->start,
					resource_size(r_mem), DRV_NAME);
	अगर (!region) अणु
		dev_err(&pdev->dev, "Memory region already claimed\n");
		वापस -EBUSY;
	पूर्ण

	regs = devm_ioremap_resource(&pdev->dev, r_mem);
	अगर (IS_ERR(regs)) अणु
		ret = PTR_ERR(regs);
		वापस ret;
	पूर्ण

	regmap_i2s = devm_regmap_init_mmio(&pdev->dev,
					regs, &brcm_i2s_regmap_config);
	अगर (IS_ERR(regmap_i2s))
		वापस PTR_ERR(regmap_i2s);

	regmap_update_bits(regmap_i2s, I2S_MISC_CFG,
			   I2S_PAD_LVL_LOOP_DIS_MASK,
			   I2S_PAD_LVL_LOOP_DIS_ENABLE);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &bcm63xx_i2s_component,
					      &bcm63xx_i2s_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register the dai\n");
		वापस ret;
	पूर्ण

	i2s_priv->dev = &pdev->dev;
	i2s_priv->i2s_clk = i2s_clk;
	i2s_priv->regmap_i2s = regmap_i2s;
	dev_set_drvdata(&pdev->dev, i2s_priv);

	ret = bcm63xx_soc_platक्रमm_probe(pdev, i2s_priv);
	अगर (ret)
		dev_err(&pdev->dev, "failed to register the pcm\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bcm63xx_i2s_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	bcm63xx_soc_platक्रमm_हटाओ(pdev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id snd_soc_bcm_audio_match[] = अणु
	अणु.compatible = "brcm,bcm63xx-i2s"पूर्ण,
	अणु पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver bcm63xx_i2s_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(snd_soc_bcm_audio_match),
	पूर्ण,
	.probe = bcm63xx_i2s_dev_probe,
	.हटाओ = bcm63xx_i2s_dev_हटाओ,
पूर्ण;

module_platक्रमm_driver(bcm63xx_i2s_driver);

MODULE_AUTHOR("Kevin,Li <kevin-ke.li@broadcom.com>");
MODULE_DESCRIPTION("Broadcom DSL XPON ASOC I2S Interface");
MODULE_LICENSE("GPL v2");
