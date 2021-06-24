<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Freescale Semiconductor, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "mxs-saif.h"

#घोषणा MXS_SET_ADDR	0x4
#घोषणा MXS_CLR_ADDR	0x8

अटल काष्ठा mxs_saअगर *mxs_saअगर[2];

/*
 * SAIF is a little dअगरferent with other normal SOC DAIs on घड़ी using.
 *
 * For MXS, two SAIF modules are instantiated on-chip.
 * Each SAIF has a set of घड़ी pins and can be operating in master
 * mode simultaneously अगर they are connected to dअगरferent off-chip codecs.
 * Also, one of the two SAIFs can master or drive the घड़ी pins जबतक the
 * other SAIF, in slave mode, receives घड़ीing from the master SAIF.
 * This also means that both SAIFs must operate at the same sample rate.
 *
 * We असलtract this as each saअगर has a master, the master could be
 * itself or other saअगरs. In the generic saअगर driver, saअगर करोes not need
 * to know the dअगरferent clkmux. Saअगर only needs to know who is its master
 * and operating its master to generate the proper घड़ी rate क्रम it.
 * The master id is provided in mach-specअगरic layer according to dअगरferent
 * clkmux setting.
 */

अटल पूर्णांक mxs_saअगर_set_dai_sysclk(काष्ठा snd_soc_dai *cpu_dai,
			पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा mxs_saअगर *saअगर = snd_soc_dai_get_drvdata(cpu_dai);

	चयन (clk_id) अणु
	हाल MXS_SAIF_MCLK:
		saअगर->mclk = freq;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Since SAIF may work on EXTMASTER mode, IOW, it's working BITCLK&LRCLK
 * is provided by other SAIF, we provide a पूर्णांकerface here to get its master
 * from its master_id.
 * Note that the master could be itself.
 */
अटल अंतरभूत काष्ठा mxs_saअगर *mxs_saअगर_get_master(काष्ठा mxs_saअगर * saअगर)
अणु
	वापस mxs_saअगर[saअगर->master_id];
पूर्ण

/*
 * Set SAIF घड़ी and MCLK
 */
अटल पूर्णांक mxs_saअगर_set_clk(काष्ठा mxs_saअगर *saअगर,
				  अचिन्हित पूर्णांक mclk,
				  अचिन्हित पूर्णांक rate)
अणु
	u32 scr;
	पूर्णांक ret;
	काष्ठा mxs_saअगर *master_saअगर;

	dev_dbg(saअगर->dev, "mclk %d rate %d\n", mclk, rate);

	/* Set master saअगर to generate proper घड़ी */
	master_saअगर = mxs_saअगर_get_master(saअगर);
	अगर (!master_saअगर)
		वापस -EINVAL;

	dev_dbg(saअगर->dev, "master saif%d\n", master_saअगर->id);

	/* Checking अगर can playback and capture simutaneously */
	अगर (master_saअगर->ongoing && rate != master_saअगर->cur_rate) अणु
		dev_err(saअगर->dev,
			"can not change clock, master saif%d(rate %d) is ongoing\n",
			master_saअगर->id, master_saअगर->cur_rate);
		वापस -EINVAL;
	पूर्ण

	scr = __raw_पढ़ोl(master_saअगर->base + SAIF_CTRL);
	scr &= ~BM_SAIF_CTRL_BITCLK_MULT_RATE;
	scr &= ~BM_SAIF_CTRL_BITCLK_BASE_RATE;

	/*
	 * Set SAIF घड़ी
	 *
	 * The SAIF घड़ी should be either 384*fs or 512*fs.
	 * If MCLK is used, the SAIF clk ratio needs to match mclk ratio.
	 *  For 256x, 128x, 64x, and 32x sub-rates, set saअगर clk as 512*fs.
	 *  For 192x, 96x, and 48x sub-rates, set saअगर clk as 384*fs.
	 *
	 * If MCLK is not used, we just set saअगर clk to 512*fs.
	 */
	ret = clk_prepare_enable(master_saअगर->clk);
	अगर (ret)
		वापस ret;

	अगर (master_saअगर->mclk_in_use) अणु
		चयन (mclk / rate) अणु
		हाल 32:
		हाल 64:
		हाल 128:
		हाल 256:
		हाल 512:
			scr &= ~BM_SAIF_CTRL_BITCLK_BASE_RATE;
			ret = clk_set_rate(master_saअगर->clk, 512 * rate);
			अवरोध;
		हाल 48:
		हाल 96:
		हाल 192:
		हाल 384:
			scr |= BM_SAIF_CTRL_BITCLK_BASE_RATE;
			ret = clk_set_rate(master_saअगर->clk, 384 * rate);
			अवरोध;
		शेष:
			/* SAIF MCLK should be a sub-rate of 512x or 384x */
			clk_disable_unprepare(master_saअगर->clk);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = clk_set_rate(master_saअगर->clk, 512 * rate);
		scr &= ~BM_SAIF_CTRL_BITCLK_BASE_RATE;
	पूर्ण

	clk_disable_unprepare(master_saअगर->clk);

	अगर (ret)
		वापस ret;

	master_saअगर->cur_rate = rate;

	अगर (!master_saअगर->mclk_in_use) अणु
		__raw_ग_लिखोl(scr, master_saअगर->base + SAIF_CTRL);
		वापस 0;
	पूर्ण

	/*
	 * Program the over-sample rate क्रम MCLK output
	 *
	 * The available MCLK range is 32x, 48x... 512x. The rate
	 * could be from 8kHz to 192kH.
	 */
	चयन (mclk / rate) अणु
	हाल 32:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(4);
		अवरोध;
	हाल 64:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(3);
		अवरोध;
	हाल 128:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(2);
		अवरोध;
	हाल 256:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(1);
		अवरोध;
	हाल 512:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(0);
		अवरोध;
	हाल 48:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(3);
		अवरोध;
	हाल 96:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(2);
		अवरोध;
	हाल 192:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(1);
		अवरोध;
	हाल 384:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	__raw_ग_लिखोl(scr, master_saअगर->base + SAIF_CTRL);

	वापस 0;
पूर्ण

/*
 * Put and disable MCLK.
 */
पूर्णांक mxs_saअगर_put_mclk(अचिन्हित पूर्णांक saअगर_id)
अणु
	काष्ठा mxs_saअगर *saअगर = mxs_saअगर[saअगर_id];
	u32 stat;

	अगर (!saअगर)
		वापस -EINVAL;

	stat = __raw_पढ़ोl(saअगर->base + SAIF_STAT);
	अगर (stat & BM_SAIF_STAT_BUSY) अणु
		dev_err(saअगर->dev, "error: busy\n");
		वापस -EBUSY;
	पूर्ण

	clk_disable_unprepare(saअगर->clk);

	/* disable MCLK output */
	__raw_ग_लिखोl(BM_SAIF_CTRL_CLKGATE,
		saअगर->base + SAIF_CTRL + MXS_SET_ADDR);
	__raw_ग_लिखोl(BM_SAIF_CTRL_RUN,
		saअगर->base + SAIF_CTRL + MXS_CLR_ADDR);

	saअगर->mclk_in_use = 0;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mxs_saअगर_put_mclk);

/*
 * Get MCLK and set घड़ी rate, then enable it
 *
 * This पूर्णांकerface is used क्रम codecs who are using MCLK provided
 * by saअगर.
 */
पूर्णांक mxs_saअगर_get_mclk(अचिन्हित पूर्णांक saअगर_id, अचिन्हित पूर्णांक mclk,
					अचिन्हित पूर्णांक rate)
अणु
	काष्ठा mxs_saअगर *saअगर = mxs_saअगर[saअगर_id];
	u32 stat;
	पूर्णांक ret;
	काष्ठा mxs_saअगर *master_saअगर;

	अगर (!saअगर)
		वापस -EINVAL;

	/* Clear Reset */
	__raw_ग_लिखोl(BM_SAIF_CTRL_SFTRST,
		saअगर->base + SAIF_CTRL + MXS_CLR_ADDR);

	/* FIXME: need clear clk gate क्रम रेजिस्टर r/w */
	__raw_ग_लिखोl(BM_SAIF_CTRL_CLKGATE,
		saअगर->base + SAIF_CTRL + MXS_CLR_ADDR);

	master_saअगर = mxs_saअगर_get_master(saअगर);
	अगर (saअगर != master_saअगर) अणु
		dev_err(saअगर->dev, "can not get mclk from a non-master saif\n");
		वापस -EINVAL;
	पूर्ण

	stat = __raw_पढ़ोl(saअगर->base + SAIF_STAT);
	अगर (stat & BM_SAIF_STAT_BUSY) अणु
		dev_err(saअगर->dev, "error: busy\n");
		वापस -EBUSY;
	पूर्ण

	saअगर->mclk_in_use = 1;
	ret = mxs_saअगर_set_clk(saअगर, mclk, rate);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(saअगर->clk);
	अगर (ret)
		वापस ret;

	/* enable MCLK output */
	__raw_ग_लिखोl(BM_SAIF_CTRL_RUN,
		saअगर->base + SAIF_CTRL + MXS_SET_ADDR);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mxs_saअगर_get_mclk);

/*
 * SAIF DAI क्रमmat configuration.
 * Should only be called when port is inactive.
 */
अटल पूर्णांक mxs_saअगर_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai, अचिन्हित पूर्णांक fmt)
अणु
	u32 scr, stat;
	u32 scr0;
	काष्ठा mxs_saअगर *saअगर = snd_soc_dai_get_drvdata(cpu_dai);

	stat = __raw_पढ़ोl(saअगर->base + SAIF_STAT);
	अगर (stat & BM_SAIF_STAT_BUSY) अणु
		dev_err(cpu_dai->dev, "error: busy\n");
		वापस -EBUSY;
	पूर्ण

	/* If SAIF1 is configured as slave, the clk gate needs to be cleared
	 * beक्रमe the रेजिस्टर can be written.
	 */
	अगर (saअगर->id != saअगर->master_id) अणु
		__raw_ग_लिखोl(BM_SAIF_CTRL_SFTRST,
			saअगर->base + SAIF_CTRL + MXS_CLR_ADDR);
		__raw_ग_लिखोl(BM_SAIF_CTRL_CLKGATE,
			saअगर->base + SAIF_CTRL + MXS_CLR_ADDR);
	पूर्ण

	scr0 = __raw_पढ़ोl(saअगर->base + SAIF_CTRL);
	scr0 = scr0 & ~BM_SAIF_CTRL_BITCLK_EDGE & ~BM_SAIF_CTRL_LRCLK_POLARITY \
		& ~BM_SAIF_CTRL_JUSTIFY & ~BM_SAIF_CTRL_DELAY;
	scr = 0;

	/* DAI mode */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		/* data frame low 1clk beक्रमe data */
		scr |= BM_SAIF_CTRL_DELAY;
		scr &= ~BM_SAIF_CTRL_LRCLK_POLARITY;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		/* data frame high with data */
		scr &= ~BM_SAIF_CTRL_DELAY;
		scr &= ~BM_SAIF_CTRL_LRCLK_POLARITY;
		scr &= ~BM_SAIF_CTRL_JUSTIFY;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* DAI घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_IF:
		scr |= BM_SAIF_CTRL_BITCLK_EDGE;
		scr |= BM_SAIF_CTRL_LRCLK_POLARITY;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		scr |= BM_SAIF_CTRL_BITCLK_EDGE;
		scr &= ~BM_SAIF_CTRL_LRCLK_POLARITY;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		scr &= ~BM_SAIF_CTRL_BITCLK_EDGE;
		scr |= BM_SAIF_CTRL_LRCLK_POLARITY;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
		scr &= ~BM_SAIF_CTRL_BITCLK_EDGE;
		scr &= ~BM_SAIF_CTRL_LRCLK_POLARITY;
		अवरोध;
	पूर्ण

	/*
	 * Note: We simply just support master mode since SAIF TX can only
	 * work as master.
	 * Here the master is relative to codec side.
	 * Saअगर पूर्णांकernally could be slave when working on EXTMASTER mode.
	 * We just hide this to machine driver.
	 */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अगर (saअगर->id == saअगर->master_id)
			scr &= ~BM_SAIF_CTRL_SLAVE_MODE;
		अन्यथा
			scr |= BM_SAIF_CTRL_SLAVE_MODE;

		__raw_ग_लिखोl(scr | scr0, saअगर->base + SAIF_CTRL);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_saअगर_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा mxs_saअगर *saअगर = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक ret;

	/* clear error status to 0 क्रम each re-खोलो */
	saअगर->fअगरo_underrun = 0;
	saअगर->fअगरo_overrun = 0;

	/* Clear Reset क्रम normal operations */
	__raw_ग_लिखोl(BM_SAIF_CTRL_SFTRST,
		saअगर->base + SAIF_CTRL + MXS_CLR_ADDR);

	/* clear घड़ी gate */
	__raw_ग_लिखोl(BM_SAIF_CTRL_CLKGATE,
		saअगर->base + SAIF_CTRL + MXS_CLR_ADDR);

	ret = clk_prepare(saअगर->clk);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम mxs_saअगर_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा mxs_saअगर *saअगर = snd_soc_dai_get_drvdata(cpu_dai);

	clk_unprepare(saअगर->clk);
पूर्ण

/*
 * Should only be called when port is inactive.
 * although can be called multiple बार by upper layers.
 */
अटल पूर्णांक mxs_saअगर_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा mxs_saअगर *saअगर = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा mxs_saअगर *master_saअगर;
	u32 scr, stat;
	पूर्णांक ret;

	master_saअगर = mxs_saअगर_get_master(saअगर);
	अगर (!master_saअगर)
		वापस -EINVAL;

	/* mclk should alपढ़ोy be set */
	अगर (!saअगर->mclk && saअगर->mclk_in_use) अणु
		dev_err(cpu_dai->dev, "set mclk first\n");
		वापस -EINVAL;
	पूर्ण

	stat = __raw_पढ़ोl(saअगर->base + SAIF_STAT);
	अगर (!saअगर->mclk_in_use && (stat & BM_SAIF_STAT_BUSY)) अणु
		dev_err(cpu_dai->dev, "error: busy\n");
		वापस -EBUSY;
	पूर्ण

	/*
	 * Set saअगर clk based on sample rate.
	 * If mclk is used, we also set mclk, अगर not, saअगर->mclk is
	 * शेष 0, means not used.
	 */
	ret = mxs_saअगर_set_clk(saअगर, saअगर->mclk, params_rate(params));
	अगर (ret) अणु
		dev_err(cpu_dai->dev, "unable to get proper clk\n");
		वापस ret;
	पूर्ण

	अगर (saअगर != master_saअगर) अणु
		/*
		* Set an initial घड़ी rate क्रम the saअगर पूर्णांकernal logic to work
		* properly. This is important when working in EXTMASTER mode
		* that uses the other saअगर's BITCLK&LRCLK but it still needs a
		* basic घड़ी which should be fast enough क्रम the पूर्णांकernal
		* logic.
		*/
		clk_enable(saअगर->clk);
		ret = clk_set_rate(saअगर->clk, 24000000);
		clk_disable(saअगर->clk);
		अगर (ret)
			वापस ret;

		ret = clk_prepare(master_saअगर->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	scr = __raw_पढ़ोl(saअगर->base + SAIF_CTRL);

	scr &= ~BM_SAIF_CTRL_WORD_LENGTH;
	scr &= ~BM_SAIF_CTRL_BITCLK_48XFS_ENABLE;
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		scr |= BF_SAIF_CTRL_WORD_LENGTH(0);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		scr |= BF_SAIF_CTRL_WORD_LENGTH(4);
		scr |= BM_SAIF_CTRL_BITCLK_48XFS_ENABLE;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		scr |= BF_SAIF_CTRL_WORD_LENGTH(8);
		scr |= BM_SAIF_CTRL_BITCLK_48XFS_ENABLE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Tx/Rx config */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		/* enable TX mode */
		scr &= ~BM_SAIF_CTRL_READ_MODE;
	पूर्ण अन्यथा अणु
		/* enable RX mode */
		scr |= BM_SAIF_CTRL_READ_MODE;
	पूर्ण

	__raw_ग_लिखोl(scr, saअगर->base + SAIF_CTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक mxs_saअगर_prepare(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा mxs_saअगर *saअगर = snd_soc_dai_get_drvdata(cpu_dai);

	/* enable FIFO error irqs */
	__raw_ग_लिखोl(BM_SAIF_CTRL_FIFO_ERROR_IRQ_EN,
		saअगर->base + SAIF_CTRL + MXS_SET_ADDR);

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_saअगर_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा mxs_saअगर *saअगर = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा mxs_saअगर *master_saअगर;
	u32 delay;
	पूर्णांक ret;

	master_saअगर = mxs_saअगर_get_master(saअगर);
	अगर (!master_saअगर)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (saअगर->state == MXS_SAIF_STATE_RUNNING)
			वापस 0;

		dev_dbg(cpu_dai->dev, "start\n");

		ret = clk_enable(master_saअगर->clk);
		अगर (ret) अणु
			dev_err(saअगर->dev, "Failed to enable master clock\n");
			वापस ret;
		पूर्ण

		/*
		 * If the saअगर's master is not itself, we also need to enable
		 * itself clk क्रम its पूर्णांकernal basic logic to work.
		 */
		अगर (saअगर != master_saअगर) अणु
			ret = clk_enable(saअगर->clk);
			अगर (ret) अणु
				dev_err(saअगर->dev, "Failed to enable master clock\n");
				clk_disable(master_saअगर->clk);
				वापस ret;
			पूर्ण

			__raw_ग_लिखोl(BM_SAIF_CTRL_RUN,
				saअगर->base + SAIF_CTRL + MXS_SET_ADDR);
		पूर्ण

		अगर (!master_saअगर->mclk_in_use)
			__raw_ग_लिखोl(BM_SAIF_CTRL_RUN,
				master_saअगर->base + SAIF_CTRL + MXS_SET_ADDR);

		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			/*
			 * ग_लिखो data to saअगर data रेजिस्टर to trigger
			 * the transfer.
			 * For 24-bit क्रमmat the 32-bit FIFO रेजिस्टर stores
			 * only one channel, so we need to ग_लिखो twice.
			 * This is also safe क्रम the other non 24-bit क्रमmats.
			 */
			__raw_ग_लिखोl(0, saअगर->base + SAIF_DATA);
			__raw_ग_लिखोl(0, saअगर->base + SAIF_DATA);
		पूर्ण अन्यथा अणु
			/*
			 * पढ़ो data from saअगर data रेजिस्टर to trigger
			 * the receive.
			 * For 24-bit क्रमmat the 32-bit FIFO रेजिस्टर stores
			 * only one channel, so we need to पढ़ो twice.
			 * This is also safe क्रम the other non 24-bit क्रमmats.
			 */
			__raw_पढ़ोl(saअगर->base + SAIF_DATA);
			__raw_पढ़ोl(saअगर->base + SAIF_DATA);
		पूर्ण

		master_saअगर->ongoing = 1;
		saअगर->state = MXS_SAIF_STATE_RUNNING;

		dev_dbg(saअगर->dev, "CTRL 0x%x STAT 0x%x\n",
			__raw_पढ़ोl(saअगर->base + SAIF_CTRL),
			__raw_पढ़ोl(saअगर->base + SAIF_STAT));

		dev_dbg(master_saअगर->dev, "CTRL 0x%x STAT 0x%x\n",
			__raw_पढ़ोl(master_saअगर->base + SAIF_CTRL),
			__raw_पढ़ोl(master_saअगर->base + SAIF_STAT));
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (saअगर->state == MXS_SAIF_STATE_STOPPED)
			वापस 0;

		dev_dbg(cpu_dai->dev, "stop\n");

		/* रुको a जबतक क्रम the current sample to complete */
		delay = USEC_PER_SEC / master_saअगर->cur_rate;

		अगर (!master_saअगर->mclk_in_use) अणु
			__raw_ग_लिखोl(BM_SAIF_CTRL_RUN,
				master_saअगर->base + SAIF_CTRL + MXS_CLR_ADDR);
			udelay(delay);
		पूर्ण
		clk_disable(master_saअगर->clk);

		अगर (saअगर != master_saअगर) अणु
			__raw_ग_लिखोl(BM_SAIF_CTRL_RUN,
				saअगर->base + SAIF_CTRL + MXS_CLR_ADDR);
			udelay(delay);
			clk_disable(saअगर->clk);
		पूर्ण

		master_saअगर->ongoing = 0;
		saअगर->state = MXS_SAIF_STATE_STOPPED;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा MXS_SAIF_RATES		SNDRV_PCM_RATE_8000_192000
#घोषणा MXS_SAIF_FORMATS \
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
	SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops mxs_saअगर_dai_ops = अणु
	.startup = mxs_saअगर_startup,
	.shutकरोwn = mxs_saअगर_shutकरोwn,
	.trigger = mxs_saअगर_trigger,
	.prepare = mxs_saअगर_prepare,
	.hw_params = mxs_saअगर_hw_params,
	.set_sysclk = mxs_saअगर_set_dai_sysclk,
	.set_fmt = mxs_saअगर_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver mxs_saअगर_dai = अणु
	.name = "mxs-saif",
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = MXS_SAIF_RATES,
		.क्रमmats = MXS_SAIF_FORMATS,
	पूर्ण,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = MXS_SAIF_RATES,
		.क्रमmats = MXS_SAIF_FORMATS,
	पूर्ण,
	.ops = &mxs_saअगर_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver mxs_saअगर_component = अणु
	.name		= "mxs-saif",
पूर्ण;

अटल irqवापस_t mxs_saअगर_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mxs_saअगर *saअगर = dev_id;
	अचिन्हित पूर्णांक stat;

	stat = __raw_पढ़ोl(saअगर->base + SAIF_STAT);
	अगर (!(stat & (BM_SAIF_STAT_FIFO_UNDERFLOW_IRQ |
			BM_SAIF_STAT_FIFO_OVERFLOW_IRQ)))
		वापस IRQ_NONE;

	अगर (stat & BM_SAIF_STAT_FIFO_UNDERFLOW_IRQ) अणु
		dev_dbg(saअगर->dev, "underrun!!! %d\n", ++saअगर->fअगरo_underrun);
		__raw_ग_लिखोl(BM_SAIF_STAT_FIFO_UNDERFLOW_IRQ,
				saअगर->base + SAIF_STAT + MXS_CLR_ADDR);
	पूर्ण

	अगर (stat & BM_SAIF_STAT_FIFO_OVERFLOW_IRQ) अणु
		dev_dbg(saअगर->dev, "overrun!!! %d\n", ++saअगर->fअगरo_overrun);
		__raw_ग_लिखोl(BM_SAIF_STAT_FIFO_OVERFLOW_IRQ,
				saअगर->base + SAIF_STAT + MXS_CLR_ADDR);
	पूर्ण

	dev_dbg(saअगर->dev, "SAIF_CTRL %x SAIF_STAT %x\n",
	       __raw_पढ़ोl(saअगर->base + SAIF_CTRL),
	       __raw_पढ़ोl(saअगर->base + SAIF_STAT));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mxs_saअगर_mclk_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxs_saअगर *saअगर = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = clk_रेजिस्टर_भागider(&pdev->dev, "mxs_saif_mclk",
				   __clk_get_name(saअगर->clk), 0,
				   saअगर->base + SAIF_CTRL,
				   BP_SAIF_CTRL_BITCLK_MULT_RATE, 3,
				   0, शून्य);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		अगर (ret == -EEXIST)
			वापस 0;
		dev_err(&pdev->dev, "failed to register mclk: %d\n", ret);
		वापस PTR_ERR(clk);
	पूर्ण

	ret = of_clk_add_provider(np, of_clk_src_simple_get, clk);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_saअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mxs_saअगर *saअगर;
	पूर्णांक irq, ret;
	काष्ठा device_node *master;

	saअगर = devm_kzalloc(&pdev->dev, माप(*saअगर), GFP_KERNEL);
	अगर (!saअगर)
		वापस -ENOMEM;

	ret = of_alias_get_id(np, "saif");
	अगर (ret < 0)
		वापस ret;
	अन्यथा
		saअगर->id = ret;

	अगर (saअगर->id >= ARRAY_SIZE(mxs_saअगर)) अणु
		dev_err(&pdev->dev, "get wrong saif id\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * If there is no "fsl,saif-master" phandle, it's a saअगर
	 * master.  Otherwise, it's a slave and its phandle poपूर्णांकs
	 * to the master.
	 */
	master = of_parse_phandle(np, "fsl,saif-master", 0);
	अगर (!master) अणु
		saअगर->master_id = saअगर->id;
	पूर्ण अन्यथा अणु
		ret = of_alias_get_id(master, "saif");
		अगर (ret < 0)
			वापस ret;
		अन्यथा
			saअगर->master_id = ret;

		अगर (saअगर->master_id >= ARRAY_SIZE(mxs_saअगर)) अणु
			dev_err(&pdev->dev, "get wrong master id\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	mxs_saअगर[saअगर->id] = saअगर;

	saअगर->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(saअगर->clk)) अणु
		ret = PTR_ERR(saअगर->clk);
		dev_err(&pdev->dev, "Cannot get the clock: %d\n",
			ret);
		वापस ret;
	पूर्ण

	saअगर->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(saअगर->base))
		वापस PTR_ERR(saअगर->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	saअगर->dev = &pdev->dev;
	ret = devm_request_irq(&pdev->dev, irq, mxs_saअगर_irq, 0,
			       dev_name(&pdev->dev), saअगर);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request irq\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, saअगर);

	/* We only support saअगर0 being tx and घड़ी master */
	अगर (saअगर->id == 0) अणु
		ret = mxs_saअगर_mclk_init(pdev);
		अगर (ret)
			dev_warn(&pdev->dev, "failed to init clocks\n");
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &mxs_saअगर_component,
					      &mxs_saअगर_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "register DAI failed\n");
		वापस ret;
	पूर्ण

	ret = mxs_pcm_platक्रमm_रेजिस्टर(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "register PCM failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mxs_saअगर_dt_ids[] = अणु
	अणु .compatible = "fsl,imx28-saif", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxs_saअगर_dt_ids);

अटल काष्ठा platक्रमm_driver mxs_saअगर_driver = अणु
	.probe = mxs_saअगर_probe,

	.driver = अणु
		.name = "mxs-saif",
		.of_match_table = mxs_saअगर_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mxs_saअगर_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("MXS ASoC SAIF driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mxs-saif");
