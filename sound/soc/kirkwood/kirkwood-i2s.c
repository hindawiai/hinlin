<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * kirkwood-i2s.c
 *
 * (c) 2010 Arnaud Patard <apatard@mandriva.com>
 * (c) 2010 Arnaud Patard <arnaud.patard@rtp-net.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/mbus.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <linux/platक्रमm_data/asoc-kirkwood.h>
#समावेश <linux/of.h>

#समावेश "kirkwood.h"

#घोषणा KIRKWOOD_I2S_FORMATS \
	(SNDRV_PCM_FMTBIT_S16_LE | \
	 SNDRV_PCM_FMTBIT_S24_LE | \
	 SNDRV_PCM_FMTBIT_S32_LE)

#घोषणा KIRKWOOD_SPDIF_FORMATS \
	(SNDRV_PCM_FMTBIT_S16_LE | \
	 SNDRV_PCM_FMTBIT_S24_LE)

अटल पूर्णांक kirkwood_i2s_set_fmt(काष्ठा snd_soc_dai *cpu_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा kirkwood_dma_data *priv = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ value;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_RIGHT_J:
		mask = KIRKWOOD_I2S_CTL_RJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		mask = KIRKWOOD_I2S_CTL_LJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		mask = KIRKWOOD_I2S_CTL_I2S;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Set same क्रमmat क्रम playback and record
	 * This aव्योमs some troubles.
	 */
	value = पढ़ोl(priv->io+KIRKWOOD_I2S_PLAYCTL);
	value &= ~KIRKWOOD_I2S_CTL_JUST_MASK;
	value |= mask;
	ग_लिखोl(value, priv->io+KIRKWOOD_I2S_PLAYCTL);

	value = पढ़ोl(priv->io+KIRKWOOD_I2S_RECCTL);
	value &= ~KIRKWOOD_I2S_CTL_JUST_MASK;
	value |= mask;
	ग_लिखोl(value, priv->io+KIRKWOOD_I2S_RECCTL);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम kirkwood_set_dco(व्योम __iomem *io, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ value;

	value = KIRKWOOD_DCO_CTL_OFFSET_0;
	चयन (rate) अणु
	शेष:
	हाल 44100:
		value |= KIRKWOOD_DCO_CTL_FREQ_11;
		अवरोध;
	हाल 48000:
		value |= KIRKWOOD_DCO_CTL_FREQ_12;
		अवरोध;
	हाल 96000:
		value |= KIRKWOOD_DCO_CTL_FREQ_24;
		अवरोध;
	पूर्ण
	ग_लिखोl(value, io + KIRKWOOD_DCO_CTL);

	/* रुको क्रम dco locked */
	करो अणु
		cpu_relax();
		value = पढ़ोl(io + KIRKWOOD_DCO_SPCR_STATUS);
		value &= KIRKWOOD_DCO_SPCR_STATUS_DCO_LOCK;
	पूर्ण जबतक (value == 0);
पूर्ण

अटल व्योम kirkwood_set_rate(काष्ठा snd_soc_dai *dai,
	काष्ठा kirkwood_dma_data *priv, अचिन्हित दीर्घ rate)
अणु
	uपूर्णांक32_t clks_ctrl;

	अगर (IS_ERR(priv->extclk)) अणु
		/* use पूर्णांकernal dco क्रम the supported rates
		 * defined in kirkwood_i2s_dai */
		dev_dbg(dai->dev, "%s: dco set rate = %lu\n",
			__func__, rate);
		kirkwood_set_dco(priv->io, rate);

		clks_ctrl = KIRKWOOD_MCLK_SOURCE_DCO;
	पूर्ण अन्यथा अणु
		/* use the बाह्यal घड़ी क्रम the other rates
		 * defined in kirkwood_i2s_dai_extclk */
		dev_dbg(dai->dev, "%s: extclk set rate = %lu -> %lu\n",
			__func__, rate, 256 * rate);
		clk_set_rate(priv->extclk, 256 * rate);

		clks_ctrl = KIRKWOOD_MCLK_SOURCE_EXTCLK;
	पूर्ण
	ग_लिखोl(clks_ctrl, priv->io + KIRKWOOD_CLOCKS_CTRL);
पूर्ण

अटल पूर्णांक kirkwood_i2s_startup(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा kirkwood_dma_data *priv = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_set_dma_data(dai, substream, priv);
	वापस 0;
पूर्ण

अटल पूर्णांक kirkwood_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा kirkwood_dma_data *priv = snd_soc_dai_get_drvdata(dai);
	uपूर्णांक32_t ctl_play, ctl_rec;
	अचिन्हित पूर्णांक i2s_reg;
	अचिन्हित दीर्घ i2s_value;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		i2s_reg = KIRKWOOD_I2S_PLAYCTL;
	पूर्ण अन्यथा अणु
		i2s_reg = KIRKWOOD_I2S_RECCTL;
	पूर्ण

	kirkwood_set_rate(dai, priv, params_rate(params));

	i2s_value = पढ़ोl(priv->io+i2s_reg);
	i2s_value &= ~KIRKWOOD_I2S_CTL_SIZE_MASK;

	/*
	 * Size settings in play/rec i2s control regs and play/rec control
	 * regs must be the same.
	 */
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		i2s_value |= KIRKWOOD_I2S_CTL_SIZE_16;
		ctl_play = KIRKWOOD_PLAYCTL_SIZE_16_C |
			   KIRKWOOD_PLAYCTL_I2S_EN |
			   KIRKWOOD_PLAYCTL_SPDIF_EN;
		ctl_rec = KIRKWOOD_RECCTL_SIZE_16_C |
			  KIRKWOOD_RECCTL_I2S_EN |
			  KIRKWOOD_RECCTL_SPDIF_EN;
		अवरोध;
	/*
	 * करोesn't work... S20_3LE != kirkwood 20bit क्रमmat ?
	 *
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		i2s_value |= KIRKWOOD_I2S_CTL_SIZE_20;
		ctl_play = KIRKWOOD_PLAYCTL_SIZE_20 |
			   KIRKWOOD_PLAYCTL_I2S_EN;
		ctl_rec = KIRKWOOD_RECCTL_SIZE_20 |
			  KIRKWOOD_RECCTL_I2S_EN;
		अवरोध;
	*/
	हाल SNDRV_PCM_FORMAT_S24_LE:
		i2s_value |= KIRKWOOD_I2S_CTL_SIZE_24;
		ctl_play = KIRKWOOD_PLAYCTL_SIZE_24 |
			   KIRKWOOD_PLAYCTL_I2S_EN |
			   KIRKWOOD_PLAYCTL_SPDIF_EN;
		ctl_rec = KIRKWOOD_RECCTL_SIZE_24 |
			  KIRKWOOD_RECCTL_I2S_EN |
			  KIRKWOOD_RECCTL_SPDIF_EN;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		i2s_value |= KIRKWOOD_I2S_CTL_SIZE_32;
		ctl_play = KIRKWOOD_PLAYCTL_SIZE_32 |
			   KIRKWOOD_PLAYCTL_I2S_EN;
		ctl_rec = KIRKWOOD_RECCTL_SIZE_32 |
			  KIRKWOOD_RECCTL_I2S_EN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (params_channels(params) == 1)
			ctl_play |= KIRKWOOD_PLAYCTL_MONO_BOTH;
		अन्यथा
			ctl_play |= KIRKWOOD_PLAYCTL_MONO_OFF;

		priv->ctl_play &= ~(KIRKWOOD_PLAYCTL_MONO_MASK |
				    KIRKWOOD_PLAYCTL_ENABLE_MASK |
				    KIRKWOOD_PLAYCTL_SIZE_MASK);
		priv->ctl_play |= ctl_play;
	पूर्ण अन्यथा अणु
		priv->ctl_rec &= ~(KIRKWOOD_RECCTL_ENABLE_MASK |
				   KIRKWOOD_RECCTL_SIZE_MASK);
		priv->ctl_rec |= ctl_rec;
	पूर्ण

	ग_लिखोl(i2s_value, priv->io+i2s_reg);

	वापस 0;
पूर्ण

अटल अचिन्हित kirkwood_i2s_play_mute(अचिन्हित ctl)
अणु
	अगर (!(ctl & KIRKWOOD_PLAYCTL_I2S_EN))
		ctl |= KIRKWOOD_PLAYCTL_I2S_MUTE;
	अगर (!(ctl & KIRKWOOD_PLAYCTL_SPDIF_EN))
		ctl |= KIRKWOOD_PLAYCTL_SPDIF_MUTE;
	वापस ctl;
पूर्ण

अटल पूर्णांक kirkwood_i2s_play_trigger(काष्ठा snd_pcm_substream *substream,
				पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा kirkwood_dma_data *priv = snd_soc_dai_get_drvdata(dai);
	uपूर्णांक32_t ctl, value;

	ctl = पढ़ोl(priv->io + KIRKWOOD_PLAYCTL);
	अगर ((ctl & KIRKWOOD_PLAYCTL_ENABLE_MASK) == 0) अणु
		अचिन्हित समयout = 5000;
		/*
		 * The Armada510 spec says that अगर we enter छोड़ो mode, the
		 * busy bit must be पढ़ो back as clear _twice_.  Make sure
		 * we respect that otherwise we get DMA underruns.
		 */
		करो अणु
			value = ctl;
			ctl = पढ़ोl(priv->io + KIRKWOOD_PLAYCTL);
			अगर (!((ctl | value) & KIRKWOOD_PLAYCTL_PLAY_BUSY))
				अवरोध;
			udelay(1);
		पूर्ण जबतक (समयout--);

		अगर ((ctl | value) & KIRKWOOD_PLAYCTL_PLAY_BUSY)
			dev_notice(dai->dev, "timed out waiting for busy to deassert: %08x\n",
				   ctl);
	पूर्ण

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		/* configure */
		ctl = priv->ctl_play;
		अगर (dai->id == 0)
			ctl &= ~KIRKWOOD_PLAYCTL_SPDIF_EN;	/* i2s */
		अन्यथा
			ctl &= ~KIRKWOOD_PLAYCTL_I2S_EN;	/* spdअगर */
		ctl = kirkwood_i2s_play_mute(ctl);
		value = ctl & ~KIRKWOOD_PLAYCTL_ENABLE_MASK;
		ग_लिखोl(value, priv->io + KIRKWOOD_PLAYCTL);

		/* enable पूर्णांकerrupts */
		अगर (!runसमय->no_period_wakeup) अणु
			value = पढ़ोl(priv->io + KIRKWOOD_INT_MASK);
			value |= KIRKWOOD_INT_CAUSE_PLAY_BYTES;
			ग_लिखोl(value, priv->io + KIRKWOOD_INT_MASK);
		पूर्ण

		/* enable playback */
		ग_लिखोl(ctl, priv->io + KIRKWOOD_PLAYCTL);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		/* stop audio, disable पूर्णांकerrupts */
		ctl |= KIRKWOOD_PLAYCTL_PAUSE | KIRKWOOD_PLAYCTL_I2S_MUTE |
				KIRKWOOD_PLAYCTL_SPDIF_MUTE;
		ग_लिखोl(ctl, priv->io + KIRKWOOD_PLAYCTL);

		value = पढ़ोl(priv->io + KIRKWOOD_INT_MASK);
		value &= ~KIRKWOOD_INT_CAUSE_PLAY_BYTES;
		ग_लिखोl(value, priv->io + KIRKWOOD_INT_MASK);

		/* disable all playbacks */
		ctl &= ~KIRKWOOD_PLAYCTL_ENABLE_MASK;
		ग_लिखोl(ctl, priv->io + KIRKWOOD_PLAYCTL);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		ctl |= KIRKWOOD_PLAYCTL_PAUSE | KIRKWOOD_PLAYCTL_I2S_MUTE |
				KIRKWOOD_PLAYCTL_SPDIF_MUTE;
		ग_लिखोl(ctl, priv->io + KIRKWOOD_PLAYCTL);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ctl &= ~(KIRKWOOD_PLAYCTL_PAUSE | KIRKWOOD_PLAYCTL_I2S_MUTE |
				KIRKWOOD_PLAYCTL_SPDIF_MUTE);
		ctl = kirkwood_i2s_play_mute(ctl);
		ग_लिखोl(ctl, priv->io + KIRKWOOD_PLAYCTL);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kirkwood_i2s_rec_trigger(काष्ठा snd_pcm_substream *substream,
				पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा kirkwood_dma_data *priv = snd_soc_dai_get_drvdata(dai);
	uपूर्णांक32_t ctl, value;

	value = पढ़ोl(priv->io + KIRKWOOD_RECCTL);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		/* configure */
		ctl = priv->ctl_rec;
		अगर (dai->id == 0)
			ctl &= ~KIRKWOOD_RECCTL_SPDIF_EN;	/* i2s */
		अन्यथा
			ctl &= ~KIRKWOOD_RECCTL_I2S_EN;		/* spdअगर */

		value = ctl & ~KIRKWOOD_RECCTL_ENABLE_MASK;
		ग_लिखोl(value, priv->io + KIRKWOOD_RECCTL);

		/* enable पूर्णांकerrupts */
		value = पढ़ोl(priv->io + KIRKWOOD_INT_MASK);
		value |= KIRKWOOD_INT_CAUSE_REC_BYTES;
		ग_लिखोl(value, priv->io + KIRKWOOD_INT_MASK);

		/* enable record */
		ग_लिखोl(ctl, priv->io + KIRKWOOD_RECCTL);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		/* stop audio, disable पूर्णांकerrupts */
		value = पढ़ोl(priv->io + KIRKWOOD_RECCTL);
		value |= KIRKWOOD_RECCTL_PAUSE | KIRKWOOD_RECCTL_MUTE;
		ग_लिखोl(value, priv->io + KIRKWOOD_RECCTL);

		value = पढ़ोl(priv->io + KIRKWOOD_INT_MASK);
		value &= ~KIRKWOOD_INT_CAUSE_REC_BYTES;
		ग_लिखोl(value, priv->io + KIRKWOOD_INT_MASK);

		/* disable all records */
		value = पढ़ोl(priv->io + KIRKWOOD_RECCTL);
		value &= ~KIRKWOOD_RECCTL_ENABLE_MASK;
		ग_लिखोl(value, priv->io + KIRKWOOD_RECCTL);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		value = पढ़ोl(priv->io + KIRKWOOD_RECCTL);
		value |= KIRKWOOD_RECCTL_PAUSE | KIRKWOOD_RECCTL_MUTE;
		ग_लिखोl(value, priv->io + KIRKWOOD_RECCTL);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		value = पढ़ोl(priv->io + KIRKWOOD_RECCTL);
		value &= ~(KIRKWOOD_RECCTL_PAUSE | KIRKWOOD_RECCTL_MUTE);
		ग_लिखोl(value, priv->io + KIRKWOOD_RECCTL);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kirkwood_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस kirkwood_i2s_play_trigger(substream, cmd, dai);
	अन्यथा
		वापस kirkwood_i2s_rec_trigger(substream, cmd, dai);

	वापस 0;
पूर्ण

अटल पूर्णांक kirkwood_i2s_init(काष्ठा kirkwood_dma_data *priv)
अणु
	अचिन्हित दीर्घ value;
	अचिन्हित पूर्णांक reg_data;

	/* put प्रणाली in a "safe" state : */
	/* disable audio पूर्णांकerrupts */
	ग_लिखोl(0xffffffff, priv->io + KIRKWOOD_INT_CAUSE);
	ग_लिखोl(0, priv->io + KIRKWOOD_INT_MASK);

	reg_data = पढ़ोl(priv->io + 0x1200);
	reg_data &= (~(0x333FF8));
	reg_data |= 0x111D18;
	ग_लिखोl(reg_data, priv->io + 0x1200);

	msleep(500);

	reg_data = पढ़ोl(priv->io + 0x1200);
	reg_data &= (~(0x333FF8));
	reg_data |= 0x111D18;
	ग_लिखोl(reg_data, priv->io + 0x1200);

	/* disable playback/record */
	value = पढ़ोl(priv->io + KIRKWOOD_PLAYCTL);
	value &= ~KIRKWOOD_PLAYCTL_ENABLE_MASK;
	ग_लिखोl(value, priv->io + KIRKWOOD_PLAYCTL);

	value = पढ़ोl(priv->io + KIRKWOOD_RECCTL);
	value &= ~KIRKWOOD_RECCTL_ENABLE_MASK;
	ग_लिखोl(value, priv->io + KIRKWOOD_RECCTL);

	वापस 0;

पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops kirkwood_i2s_dai_ops = अणु
	.startup	= kirkwood_i2s_startup,
	.trigger	= kirkwood_i2s_trigger,
	.hw_params      = kirkwood_i2s_hw_params,
	.set_fmt        = kirkwood_i2s_set_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver kirkwood_i2s_dai[2] = अणु
    अणु
	.name = "i2s",
	.id = 0,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |
				SNDRV_PCM_RATE_96000,
		.क्रमmats = KIRKWOOD_I2S_FORMATS,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |
				SNDRV_PCM_RATE_96000,
		.क्रमmats = KIRKWOOD_I2S_FORMATS,
	पूर्ण,
	.ops = &kirkwood_i2s_dai_ops,
    पूर्ण,
    अणु
	.name = "spdif",
	.id = 1,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |
				SNDRV_PCM_RATE_96000,
		.क्रमmats = KIRKWOOD_SPDIF_FORMATS,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |
				SNDRV_PCM_RATE_96000,
		.क्रमmats = KIRKWOOD_SPDIF_FORMATS,
	पूर्ण,
	.ops = &kirkwood_i2s_dai_ops,
    पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver kirkwood_i2s_dai_extclk[2] = अणु
    अणु
	.name = "i2s",
	.id = 0,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min = 5512,
		.rate_max = 192000,
		.क्रमmats = KIRKWOOD_I2S_FORMATS,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min = 5512,
		.rate_max = 192000,
		.क्रमmats = KIRKWOOD_I2S_FORMATS,
	पूर्ण,
	.ops = &kirkwood_i2s_dai_ops,
    पूर्ण,
    अणु
	.name = "spdif",
	.id = 1,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min = 5512,
		.rate_max = 192000,
		.क्रमmats = KIRKWOOD_SPDIF_FORMATS,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min = 5512,
		.rate_max = 192000,
		.क्रमmats = KIRKWOOD_SPDIF_FORMATS,
	पूर्ण,
	.ops = &kirkwood_i2s_dai_ops,
    पूर्ण,
पूर्ण;

अटल पूर्णांक kirkwood_i2s_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kirkwood_asoc_platक्रमm_data *data = pdev->dev.platक्रमm_data;
	काष्ठा snd_soc_dai_driver *soc_dai = kirkwood_i2s_dai;
	काष्ठा kirkwood_dma_data *priv;
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक err;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(&pdev->dev, priv);

	priv->io = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->io))
		वापस PTR_ERR(priv->io);

	priv->irq = platक्रमm_get_irq(pdev, 0);
	अगर (priv->irq < 0)
		वापस priv->irq;

	अगर (np) अणु
		priv->burst = 128;		/* might be 32 or 128 */
	पूर्ण अन्यथा अगर (data) अणु
		priv->burst = data->burst;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "no DT nor platform data ?!\n");
		वापस -EINVAL;
	पूर्ण

	priv->clk = devm_clk_get(&pdev->dev, np ? "internal" : शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(&pdev->dev, "no clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	priv->extclk = devm_clk_get(&pdev->dev, "extclk");
	अगर (IS_ERR(priv->extclk)) अणु
		अगर (PTR_ERR(priv->extclk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अणु
		अगर (clk_is_match(priv->extclk, priv->clk)) अणु
			devm_clk_put(&pdev->dev, priv->extclk);
			priv->extclk = ERR_PTR(-EINVAL);
		पूर्ण अन्यथा अणु
			dev_info(&pdev->dev, "found external clock\n");
			clk_prepare_enable(priv->extclk);
			soc_dai = kirkwood_i2s_dai_extclk;
		पूर्ण
	पूर्ण

	err = clk_prepare_enable(priv->clk);
	अगर (err < 0)
		वापस err;

	/* Some sensible शेषs - this reflects the घातerup values */
	priv->ctl_play = KIRKWOOD_PLAYCTL_SIZE_24;
	priv->ctl_rec = KIRKWOOD_RECCTL_SIZE_24;

	/* Select the burst size */
	अगर (priv->burst == 32) अणु
		priv->ctl_play |= KIRKWOOD_PLAYCTL_BURST_32;
		priv->ctl_rec |= KIRKWOOD_RECCTL_BURST_32;
	पूर्ण अन्यथा अणु
		priv->ctl_play |= KIRKWOOD_PLAYCTL_BURST_128;
		priv->ctl_rec |= KIRKWOOD_RECCTL_BURST_128;
	पूर्ण

	err = snd_soc_रेजिस्टर_component(&pdev->dev, &kirkwood_soc_component,
					 soc_dai, 2);
	अगर (err) अणु
		dev_err(&pdev->dev, "snd_soc_register_component failed\n");
		जाओ err_component;
	पूर्ण

	kirkwood_i2s_init(priv);

	वापस 0;

 err_component:
	अगर (!IS_ERR(priv->extclk))
		clk_disable_unprepare(priv->extclk);
	clk_disable_unprepare(priv->clk);

	वापस err;
पूर्ण

अटल पूर्णांक kirkwood_i2s_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kirkwood_dma_data *priv = dev_get_drvdata(&pdev->dev);

	snd_soc_unरेजिस्टर_component(&pdev->dev);
	अगर (!IS_ERR(priv->extclk))
		clk_disable_unprepare(priv->extclk);
	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mvebu_audio_of_match[] = अणु
	अणु .compatible = "marvell,kirkwood-audio" पूर्ण,
	अणु .compatible = "marvell,dove-audio" पूर्ण,
	अणु .compatible = "marvell,armada370-audio" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mvebu_audio_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver kirkwood_i2s_driver = अणु
	.probe  = kirkwood_i2s_dev_probe,
	.हटाओ = kirkwood_i2s_dev_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(mvebu_audio_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(kirkwood_i2s_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Arnaud Patard, <arnaud.patard@rtp-net.org>");
MODULE_DESCRIPTION("Kirkwood I2S SoC Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mvebu-audio");
