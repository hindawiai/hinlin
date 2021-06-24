<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ak4118.c  --  Asahi Kasei ALSA Soc Audio driver
 *
 * Copyright 2018 DEVIALET
 */

#समावेश <linux/i2c.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <sound/asoundef.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

#घोषणा AK4118_REG_CLK_PWR_CTL		0x00
#घोषणा AK4118_REG_FORMAT_CTL		0x01
#घोषणा AK4118_REG_IO_CTL0		0x02
#घोषणा AK4118_REG_IO_CTL1		0x03
#घोषणा AK4118_REG_INT0_MASK		0x04
#घोषणा AK4118_REG_INT1_MASK		0x05
#घोषणा AK4118_REG_RCV_STATUS0		0x06
#घोषणा AK4118_REG_RCV_STATUS1		0x07
#घोषणा AK4118_REG_RXCHAN_STATUS0	0x08
#घोषणा AK4118_REG_RXCHAN_STATUS1	0x09
#घोषणा AK4118_REG_RXCHAN_STATUS2	0x0a
#घोषणा AK4118_REG_RXCHAN_STATUS3	0x0b
#घोषणा AK4118_REG_RXCHAN_STATUS4	0x0c
#घोषणा AK4118_REG_TXCHAN_STATUS0	0x0d
#घोषणा AK4118_REG_TXCHAN_STATUS1	0x0e
#घोषणा AK4118_REG_TXCHAN_STATUS2	0x0f
#घोषणा AK4118_REG_TXCHAN_STATUS3	0x10
#घोषणा AK4118_REG_TXCHAN_STATUS4	0x11
#घोषणा AK4118_REG_BURST_PREAMB_PC0	0x12
#घोषणा AK4118_REG_BURST_PREAMB_PC1	0x13
#घोषणा AK4118_REG_BURST_PREAMB_PD0	0x14
#घोषणा AK4118_REG_BURST_PREAMB_PD1	0x15
#घोषणा AK4118_REG_QSUB_CTL		0x16
#घोषणा AK4118_REG_QSUB_TRACK		0x17
#घोषणा AK4118_REG_QSUB_INDEX		0x18
#घोषणा AK4118_REG_QSUB_MIN		0x19
#घोषणा AK4118_REG_QSUB_SEC		0x1a
#घोषणा AK4118_REG_QSUB_FRAME		0x1b
#घोषणा AK4118_REG_QSUB_ZERO		0x1c
#घोषणा AK4118_REG_QSUB_ABS_MIN		0x1d
#घोषणा AK4118_REG_QSUB_ABS_SEC		0x1e
#घोषणा AK4118_REG_QSUB_ABS_FRAME	0x1f
#घोषणा AK4118_REG_GPE			0x20
#घोषणा AK4118_REG_GPDR			0x21
#घोषणा AK4118_REG_GPSCR		0x22
#घोषणा AK4118_REG_GPLR			0x23
#घोषणा AK4118_REG_DAT_MASK_DTS		0x24
#घोषणा AK4118_REG_RX_DETECT		0x25
#घोषणा AK4118_REG_STC_DAT_DETECT	0x26
#घोषणा AK4118_REG_RXCHAN_STATUS5	0x27
#घोषणा AK4118_REG_TXCHAN_STATUS5	0x28
#घोषणा AK4118_REG_MAX			0x29

#घोषणा AK4118_REG_FORMAT_CTL_DIF0	(1 << 4)
#घोषणा AK4118_REG_FORMAT_CTL_DIF1	(1 << 5)
#घोषणा AK4118_REG_FORMAT_CTL_DIF2	(1 << 6)

काष्ठा ak4118_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *reset;
	काष्ठा gpio_desc *irq;
	काष्ठा snd_soc_component *component;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष ak4118_reg_शेषs[] = अणु
	अणुAK4118_REG_CLK_PWR_CTL,	0x43पूर्ण,
	अणुAK4118_REG_FORMAT_CTL,		0x6aपूर्ण,
	अणुAK4118_REG_IO_CTL0,		0x88पूर्ण,
	अणुAK4118_REG_IO_CTL1,		0x48पूर्ण,
	अणुAK4118_REG_INT0_MASK,		0xeeपूर्ण,
	अणुAK4118_REG_INT1_MASK,		0xb5पूर्ण,
	अणुAK4118_REG_RCV_STATUS0,	0x00पूर्ण,
	अणुAK4118_REG_RCV_STATUS1,	0x10पूर्ण,
	अणुAK4118_REG_TXCHAN_STATUS0,	0x00पूर्ण,
	अणुAK4118_REG_TXCHAN_STATUS1,	0x00पूर्ण,
	अणुAK4118_REG_TXCHAN_STATUS2,	0x00पूर्ण,
	अणुAK4118_REG_TXCHAN_STATUS3,	0x00पूर्ण,
	अणुAK4118_REG_TXCHAN_STATUS4,	0x00पूर्ण,
	अणुAK4118_REG_GPE,		0x77पूर्ण,
	अणुAK4118_REG_GPDR,		0x00पूर्ण,
	अणुAK4118_REG_GPSCR,		0x00पूर्ण,
	अणुAK4118_REG_GPLR,		0x00पूर्ण,
	अणुAK4118_REG_DAT_MASK_DTS,	0x3fपूर्ण,
	अणुAK4118_REG_RX_DETECT,		0x00पूर्ण,
	अणुAK4118_REG_STC_DAT_DETECT,	0x00पूर्ण,
	अणुAK4118_REG_TXCHAN_STATUS5,	0x00पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ak4118_input_select_txt[] = अणु
	"RX0", "RX1", "RX2", "RX3", "RX4", "RX5", "RX6", "RX7",
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(ak4118_insel_क्रमागत, AK4118_REG_IO_CTL1, 0x0,
			    ak4118_input_select_txt);

अटल स्थिर काष्ठा snd_kcontrol_new ak4118_input_mux_controls =
	SOC_DAPM_ENUM("Input Select", ak4118_insel_क्रमागत);

अटल स्थिर अक्षर * स्थिर ak4118_iec958_fs_txt[] = अणु
	"44100", "48000", "32000", "22050", "11025", "24000", "16000", "88200",
	"8000", "96000", "64000", "176400", "192000",
पूर्ण;

अटल स्थिर पूर्णांक ak4118_iec958_fs_val[] = अणु
	0x0, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xE,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(ak4118_iec958_fs_क्रमागत, AK4118_REG_RCV_STATUS1,
				  0x4, 0x4, ak4118_iec958_fs_txt,
				  ak4118_iec958_fs_val);

अटल काष्ठा snd_kcontrol_new ak4118_iec958_controls[] = अणु
	SOC_SINGLE("IEC958 Parity Errors", AK4118_REG_RCV_STATUS0, 0, 1, 0),
	SOC_SINGLE("IEC958 No Audio", AK4118_REG_RCV_STATUS0, 1, 1, 0),
	SOC_SINGLE("IEC958 PLL Lock", AK4118_REG_RCV_STATUS0, 4, 1, 1),
	SOC_SINGLE("IEC958 Non PCM", AK4118_REG_RCV_STATUS0, 6, 1, 0),
	SOC_ENUM("IEC958 Sampling Freq", ak4118_iec958_fs_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ak4118_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("INRX0"),
	SND_SOC_DAPM_INPUT("INRX1"),
	SND_SOC_DAPM_INPUT("INRX2"),
	SND_SOC_DAPM_INPUT("INRX3"),
	SND_SOC_DAPM_INPUT("INRX4"),
	SND_SOC_DAPM_INPUT("INRX5"),
	SND_SOC_DAPM_INPUT("INRX6"),
	SND_SOC_DAPM_INPUT("INRX7"),
	SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0,
			 &ak4118_input_mux_controls),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ak4118_dapm_routes[] = अणु
	अणु"Input Mux", "RX0", "INRX0"पूर्ण,
	अणु"Input Mux", "RX1", "INRX1"पूर्ण,
	अणु"Input Mux", "RX2", "INRX2"पूर्ण,
	अणु"Input Mux", "RX3", "INRX3"पूर्ण,
	अणु"Input Mux", "RX4", "INRX4"पूर्ण,
	अणु"Input Mux", "RX5", "INRX5"पूर्ण,
	अणु"Input Mux", "RX6", "INRX6"पूर्ण,
	अणु"Input Mux", "RX7", "INRX7"पूर्ण,
पूर्ण;


अटल पूर्णांक ak4118_set_dai_fmt_master(काष्ठा ak4118_priv *ak4118,
				     अचिन्हित पूर्णांक क्रमmat)
अणु
	पूर्णांक dअगर;

	चयन (क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		dअगर = AK4118_REG_FORMAT_CTL_DIF0 | AK4118_REG_FORMAT_CTL_DIF2;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		dअगर = AK4118_REG_FORMAT_CTL_DIF0 | AK4118_REG_FORMAT_CTL_DIF1;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		dअगर = AK4118_REG_FORMAT_CTL_DIF2;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस dअगर;
पूर्ण

अटल पूर्णांक ak4118_set_dai_fmt_slave(काष्ठा ak4118_priv *ak4118,
				    अचिन्हित पूर्णांक क्रमmat)
अणु
	पूर्णांक dअगर;

	चयन (क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		dअगर = AK4118_REG_FORMAT_CTL_DIF0 | AK4118_REG_FORMAT_CTL_DIF1 |
		      AK4118_REG_FORMAT_CTL_DIF2;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		dअगर = AK4118_REG_FORMAT_CTL_DIF1 | AK4118_REG_FORMAT_CTL_DIF2;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस dअगर;
पूर्ण

अटल पूर्णांक ak4118_set_dai_fmt(काष्ठा snd_soc_dai *dai,
			      अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4118_priv *ak4118 = snd_soc_component_get_drvdata(component);
	पूर्णांक dअगर;
	पूर्णांक ret = 0;

	चयन (क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* component is master */
		dअगर = ak4118_set_dai_fmt_master(ak4118, क्रमmat);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/*component is slave */
		dअगर = ak4118_set_dai_fmt_slave(ak4118, क्रमmat);
		अवरोध;
	शेष:
		ret = -ENOTSUPP;
		जाओ निकास;
	पूर्ण

	/* क्रमmat not supported */
	अगर (dअगर < 0) अणु
		ret = dअगर;
		जाओ निकास;
	पूर्ण

	ret = regmap_update_bits(ak4118->regmap, AK4118_REG_FORMAT_CTL,
				 AK4118_REG_FORMAT_CTL_DIF0 |
				 AK4118_REG_FORMAT_CTL_DIF1 |
				 AK4118_REG_FORMAT_CTL_DIF2, dअगर);
	अगर (ret < 0)
		जाओ निकास;

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक ak4118_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ak4118_dai_ops = अणु
	.hw_params = ak4118_hw_params,
	.set_fmt   = ak4118_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ak4118_dai = अणु
	.name = "ak4118-hifi",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_32000 |
			 SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |
			 SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 |
			 SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE  |
			   SNDRV_PCM_FMTBIT_S24_3LE |
			   SNDRV_PCM_FMTBIT_S24_LE
	पूर्ण,
	.ops = &ak4118_dai_ops,
पूर्ण;

अटल irqवापस_t ak4118_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ak4118_priv *ak4118 = data;
	काष्ठा snd_soc_component *component = ak4118->component;
	काष्ठा snd_kcontrol_new *kctl_new;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_ctl_elem_id *id;
	अचिन्हित पूर्णांक i;

	अगर (!component)
		वापस IRQ_NONE;

	क्रम (i = 0; i < ARRAY_SIZE(ak4118_iec958_controls); i++) अणु
		kctl_new = &ak4118_iec958_controls[i];
		kctl = snd_soc_card_get_kcontrol(component->card,
						 kctl_new->name);
		अगर (!kctl)
			जारी;
		id = &kctl->id;
		snd_ctl_notअगरy(component->card->snd_card,
			       SNDRV_CTL_EVENT_MASK_VALUE, id);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ak4118_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak4118_priv *ak4118 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	ak4118->component = component;

	/* release reset */
	gpiod_set_value(ak4118->reset, 0);

	/* unmask all पूर्णांक1 sources */
	ret = regmap_ग_लिखो(ak4118->regmap, AK4118_REG_INT1_MASK, 0x00);
	अगर (ret < 0) अणु
		dev_err(component->dev,
			"failed to write regmap 0x%x 0x%x: %d\n",
			AK4118_REG_INT1_MASK, 0x00, ret);
		वापस ret;
	पूर्ण

	/* rx detect enable on all channels */
	ret = regmap_ग_लिखो(ak4118->regmap, AK4118_REG_RX_DETECT, 0xff);
	अगर (ret < 0) अणु
		dev_err(component->dev,
			"failed to write regmap 0x%x 0x%x: %d\n",
			AK4118_REG_RX_DETECT, 0xff, ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_add_component_controls(component, ak4118_iec958_controls,
					 ARRAY_SIZE(ak4118_iec958_controls));
	अगर (ret) अणु
		dev_err(component->dev,
			"failed to add component kcontrols: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ak4118_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak4118_priv *ak4118 = snd_soc_component_get_drvdata(component);

	/* hold reset */
	gpiod_set_value(ak4118->reset, 1);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_drv_ak4118 = अणु
	.probe			= ak4118_probe,
	.हटाओ			= ak4118_हटाओ,
	.dapm_widमाला_लो		= ak4118_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ak4118_dapm_widमाला_लो),
	.dapm_routes		= ak4118_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(ak4118_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ak4118_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.reg_शेषs = ak4118_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(ak4118_reg_शेषs),

	.cache_type = REGCACHE_NONE,
	.max_रेजिस्टर = AK4118_REG_MAX - 1,
पूर्ण;

अटल पूर्णांक ak4118_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ak4118_priv *ak4118;
	पूर्णांक ret;

	ak4118 = devm_kzalloc(&i2c->dev, माप(काष्ठा ak4118_priv),
			      GFP_KERNEL);
	अगर (ak4118 == शून्य)
		वापस -ENOMEM;

	ak4118->regmap = devm_regmap_init_i2c(i2c, &ak4118_regmap);
	अगर (IS_ERR(ak4118->regmap))
		वापस PTR_ERR(ak4118->regmap);

	i2c_set_clientdata(i2c, ak4118);

	ak4118->reset = devm_gpiod_get(&i2c->dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ak4118->reset)) अणु
		ret = PTR_ERR(ak4118->reset);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&i2c->dev, "Failed to get reset: %d\n", ret);
		वापस ret;
	पूर्ण

	ak4118->irq = devm_gpiod_get(&i2c->dev, "irq", GPIOD_IN);
	अगर (IS_ERR(ak4118->irq)) अणु
		ret = PTR_ERR(ak4118->irq);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&i2c->dev, "Failed to get IRQ: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&i2c->dev, gpiod_to_irq(ak4118->irq),
					शून्य, ak4118_irq_handler,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"ak4118-irq", ak4118);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Fail to request_irq: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				&soc_component_drv_ak4118, &ak4118_dai, 1);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ak4118_of_match[] = अणु
	अणु .compatible = "asahi-kasei,ak4118", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ak4118_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id ak4118_id_table[] = अणु
	अणु "ak4118", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ak4118_id_table);

अटल काष्ठा i2c_driver ak4118_i2c_driver = अणु
	.driver  = अणु
		.name = "ak4118",
		.of_match_table = of_match_ptr(ak4118_of_match),
	पूर्ण,
	.id_table = ak4118_id_table,
	.probe  = ak4118_i2c_probe,
पूर्ण;

module_i2c_driver(ak4118_i2c_driver);

MODULE_DESCRIPTION("Asahi Kasei AK4118 ALSA SoC driver");
MODULE_AUTHOR("Adrien Charruel <adrien.charruel@devialet.com>");
MODULE_LICENSE("GPL");
