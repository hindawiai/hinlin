<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC I2S (McBSP) Audio Layer क्रम TI DAVINCI processor
 *
 * Author:      Vladimir Barinov, <vbarinov@embeddedalley.com>
 * Copyright:   (C) 2007 MontaVista Software, Inc., <source@mvista.com>
 *
 * DT support	(c) 2016 Petr Kulhavy, Barix AG <petr@barix.com>
 *		based on davinci-mcasp.c DT support
 *
 * TODO:
 * on DA850 implement HW FIFOs instead of DMA पूर्णांकo DXR and DRR रेजिस्टरs
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_data/davinci_asp.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "edma-pcm.h"
#समावेश "davinci-i2s.h"

#घोषणा DRV_NAME "davinci-i2s"

/*
 * NOTE:  terminology here is confusing.
 *
 *  - This driver supports the "Audio Serial Port" (ASP),
 *    found on dm6446, dm355, and other DaVinci chips.
 *
 *  - But it labels it a "Multi-channel Buffered Serial Port"
 *    (McBSP) as on older chips like the dm642 ... which was
 *    backward-compatible, possibly explaining that confusion.
 *
 *  - OMAP chips have a controller called McBSP, which is
 *    incompatible with the DaVinci flavor of McBSP.
 *
 *  - Newer DaVinci chips have a controller called McASP,
 *    incompatible with ASP and with either McBSP.
 *
 * In लघु:  this uses ASP to implement I2S, not McBSP.
 * And it won't be the only DaVinci implemention of I2S.
 */
#घोषणा DAVINCI_MCBSP_DRR_REG	0x00
#घोषणा DAVINCI_MCBSP_DXR_REG	0x04
#घोषणा DAVINCI_MCBSP_SPCR_REG	0x08
#घोषणा DAVINCI_MCBSP_RCR_REG	0x0c
#घोषणा DAVINCI_MCBSP_XCR_REG	0x10
#घोषणा DAVINCI_MCBSP_SRGR_REG	0x14
#घोषणा DAVINCI_MCBSP_PCR_REG	0x24

#घोषणा DAVINCI_MCBSP_SPCR_RRST		(1 << 0)
#घोषणा DAVINCI_MCBSP_SPCR_RINTM(v)	((v) << 4)
#घोषणा DAVINCI_MCBSP_SPCR_XRST		(1 << 16)
#घोषणा DAVINCI_MCBSP_SPCR_XINTM(v)	((v) << 20)
#घोषणा DAVINCI_MCBSP_SPCR_GRST		(1 << 22)
#घोषणा DAVINCI_MCBSP_SPCR_FRST		(1 << 23)
#घोषणा DAVINCI_MCBSP_SPCR_FREE		(1 << 25)

#घोषणा DAVINCI_MCBSP_RCR_RWDLEN1(v)	((v) << 5)
#घोषणा DAVINCI_MCBSP_RCR_RFRLEN1(v)	((v) << 8)
#घोषणा DAVINCI_MCBSP_RCR_RDATDLY(v)	((v) << 16)
#घोषणा DAVINCI_MCBSP_RCR_RFIG		(1 << 18)
#घोषणा DAVINCI_MCBSP_RCR_RWDLEN2(v)	((v) << 21)
#घोषणा DAVINCI_MCBSP_RCR_RFRLEN2(v)	((v) << 24)
#घोषणा DAVINCI_MCBSP_RCR_RPHASE	BIT(31)

#घोषणा DAVINCI_MCBSP_XCR_XWDLEN1(v)	((v) << 5)
#घोषणा DAVINCI_MCBSP_XCR_XFRLEN1(v)	((v) << 8)
#घोषणा DAVINCI_MCBSP_XCR_XDATDLY(v)	((v) << 16)
#घोषणा DAVINCI_MCBSP_XCR_XFIG		(1 << 18)
#घोषणा DAVINCI_MCBSP_XCR_XWDLEN2(v)	((v) << 21)
#घोषणा DAVINCI_MCBSP_XCR_XFRLEN2(v)	((v) << 24)
#घोषणा DAVINCI_MCBSP_XCR_XPHASE	BIT(31)

#घोषणा DAVINCI_MCBSP_SRGR_FWID(v)	((v) << 8)
#घोषणा DAVINCI_MCBSP_SRGR_FPER(v)	((v) << 16)
#घोषणा DAVINCI_MCBSP_SRGR_FSGM		(1 << 28)
#घोषणा DAVINCI_MCBSP_SRGR_CLKSM	BIT(29)

#घोषणा DAVINCI_MCBSP_PCR_CLKRP		(1 << 0)
#घोषणा DAVINCI_MCBSP_PCR_CLKXP		(1 << 1)
#घोषणा DAVINCI_MCBSP_PCR_FSRP		(1 << 2)
#घोषणा DAVINCI_MCBSP_PCR_FSXP		(1 << 3)
#घोषणा DAVINCI_MCBSP_PCR_SCLKME	(1 << 7)
#घोषणा DAVINCI_MCBSP_PCR_CLKRM		(1 << 8)
#घोषणा DAVINCI_MCBSP_PCR_CLKXM		(1 << 9)
#घोषणा DAVINCI_MCBSP_PCR_FSRM		(1 << 10)
#घोषणा DAVINCI_MCBSP_PCR_FSXM		(1 << 11)

क्रमागत अणु
	DAVINCI_MCBSP_WORD_8 = 0,
	DAVINCI_MCBSP_WORD_12,
	DAVINCI_MCBSP_WORD_16,
	DAVINCI_MCBSP_WORD_20,
	DAVINCI_MCBSP_WORD_24,
	DAVINCI_MCBSP_WORD_32,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर data_type[SNDRV_PCM_FORMAT_S32_LE + 1] = अणु
	[SNDRV_PCM_FORMAT_S8]		= 1,
	[SNDRV_PCM_FORMAT_S16_LE]	= 2,
	[SNDRV_PCM_FORMAT_S32_LE]	= 4,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर asp_word_length[SNDRV_PCM_FORMAT_S32_LE + 1] = अणु
	[SNDRV_PCM_FORMAT_S8]		= DAVINCI_MCBSP_WORD_8,
	[SNDRV_PCM_FORMAT_S16_LE]	= DAVINCI_MCBSP_WORD_16,
	[SNDRV_PCM_FORMAT_S32_LE]	= DAVINCI_MCBSP_WORD_32,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर द्विगुन_fmt[SNDRV_PCM_FORMAT_S32_LE + 1] = अणु
	[SNDRV_PCM_FORMAT_S8]		= SNDRV_PCM_FORMAT_S16_LE,
	[SNDRV_PCM_FORMAT_S16_LE]	= SNDRV_PCM_FORMAT_S32_LE,
पूर्ण;

काष्ठा davinci_mcbsp_dev अणु
	काष्ठा device *dev;
	काष्ठा snd_dmaengine_dai_dma_data dma_data[2];
	पूर्णांक dma_request[2];
	व्योम __iomem			*base;
#घोषणा MOD_DSP_A	0
#घोषणा MOD_DSP_B	1
	पूर्णांक				mode;
	u32				pcr;
	काष्ठा clk			*clk;
	/*
	 * Combining both channels पूर्णांकo 1 element will at least द्विगुन the
	 * amount of समय between servicing the dma channel, increase
	 * effiency, and reduce the chance of overrun/underrun. But,
	 * it will result in the left & right channels being swapped.
	 *
	 * If relabeling the left and right channels is not possible,
	 * you may want to let the codec know to swap them back.
	 *
	 * It may allow x10 the amount of समय to service dma requests,
	 * अगर the codec is master and is using an unnecessarily fast bit घड़ी
	 * (ie. tlvaic23b), independent of the sample rate. So, having an
	 * entire frame at once means it can be serviced at the sample rate
	 * instead of the bit घड़ी rate.
	 *
	 * In the now unlikely हाल that an underrun still
	 * occurs, both the left and right samples will be repeated
	 * so that no pops are heard, and the left and right channels
	 * won't end up being swapped because of the underrun.
	 */
	अचिन्हित enable_channel_combine:1;

	अचिन्हित पूर्णांक fmt;
	पूर्णांक clk_भाग;
	पूर्णांक clk_input_pin;
	bool i2s_accurate_sck;
पूर्ण;

अटल अंतरभूत व्योम davinci_mcbsp_ग_लिखो_reg(काष्ठा davinci_mcbsp_dev *dev,
					   पूर्णांक reg, u32 val)
अणु
	__raw_ग_लिखोl(val, dev->base + reg);
पूर्ण

अटल अंतरभूत u32 davinci_mcbsp_पढ़ो_reg(काष्ठा davinci_mcbsp_dev *dev, पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(dev->base + reg);
पूर्ण

अटल व्योम toggle_घड़ी(काष्ठा davinci_mcbsp_dev *dev, पूर्णांक playback)
अणु
	u32 m = playback ? DAVINCI_MCBSP_PCR_CLKXP : DAVINCI_MCBSP_PCR_CLKRP;
	/* The घड़ी needs to toggle to complete reset.
	 * So, fake it by toggling the clk polarity.
	 */
	davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_PCR_REG, dev->pcr ^ m);
	davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_PCR_REG, dev->pcr);
पूर्ण

अटल व्योम davinci_mcbsp_start(काष्ठा davinci_mcbsp_dev *dev,
		काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	u32 spcr;
	u32 mask = playback ? DAVINCI_MCBSP_SPCR_XRST : DAVINCI_MCBSP_SPCR_RRST;

	/* Enable transmitter or receiver */
	spcr = davinci_mcbsp_पढ़ो_reg(dev, DAVINCI_MCBSP_SPCR_REG);
	spcr |= mask;

	अगर (dev->pcr & (DAVINCI_MCBSP_PCR_FSXM | DAVINCI_MCBSP_PCR_FSRM)) अणु
		/* Start frame sync */
		spcr |= DAVINCI_MCBSP_SPCR_FRST;
	पूर्ण
	davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_SPCR_REG, spcr);
पूर्ण

अटल व्योम davinci_mcbsp_stop(काष्ठा davinci_mcbsp_dev *dev, पूर्णांक playback)
अणु
	u32 spcr;

	/* Reset transmitter/receiver and sample rate/frame sync generators */
	spcr = davinci_mcbsp_पढ़ो_reg(dev, DAVINCI_MCBSP_SPCR_REG);
	spcr &= ~(DAVINCI_MCBSP_SPCR_GRST | DAVINCI_MCBSP_SPCR_FRST);
	spcr &= playback ? ~DAVINCI_MCBSP_SPCR_XRST : ~DAVINCI_MCBSP_SPCR_RRST;
	davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_SPCR_REG, spcr);
	toggle_घड़ी(dev, playback);
पूर्ण

#घोषणा DEFAULT_BITPERSAMPLE	16

अटल पूर्णांक davinci_i2s_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai,
				   अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा davinci_mcbsp_dev *dev = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित पूर्णांक pcr;
	अचिन्हित पूर्णांक srgr;
	bool inv_fs = false;
	/* Attention srgr is updated by hw_params! */
	srgr = DAVINCI_MCBSP_SRGR_FSGM |
		DAVINCI_MCBSP_SRGR_FPER(DEFAULT_BITPERSAMPLE * 2 - 1) |
		DAVINCI_MCBSP_SRGR_FWID(DEFAULT_BITPERSAMPLE - 1);

	dev->fmt = fmt;
	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* cpu is master */
		pcr = DAVINCI_MCBSP_PCR_FSXM |
			DAVINCI_MCBSP_PCR_FSRM |
			DAVINCI_MCBSP_PCR_CLKXM |
			DAVINCI_MCBSP_PCR_CLKRM;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		pcr = DAVINCI_MCBSP_PCR_FSRM | DAVINCI_MCBSP_PCR_FSXM;
		/*
		 * Selection of the घड़ी input pin that is the
		 * input क्रम the Sample Rate Generator.
		 * McBSP FSR and FSX are driven by the Sample Rate
		 * Generator.
		 */
		चयन (dev->clk_input_pin) अणु
		हाल MCBSP_CLKS:
			pcr |= DAVINCI_MCBSP_PCR_CLKXM |
				DAVINCI_MCBSP_PCR_CLKRM;
			अवरोध;
		हाल MCBSP_CLKR:
			pcr |= DAVINCI_MCBSP_PCR_SCLKME;
			अवरोध;
		शेष:
			dev_err(dev->dev, "bad clk_input_pin\n");
			वापस -EINVAL;
		पूर्ण

		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* codec is master */
		pcr = 0;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s:bad master\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		/* Davinci करोesn't support TRUE I2S, but some codecs will have
		 * the left and right channels contiguous. This allows
		 * dsp_a mode to be used with an inverted normal frame clk.
		 * If your codec is master and करोes not have contiguous
		 * channels, then you will have sound on only one channel.
		 * Try using a dअगरferent mode, or codec as slave.
		 *
		 * The TLV320AIC33 is an example of a codec where this works.
		 * It has a variable bit घड़ी frequency allowing it to have
		 * valid data on every bit घड़ी.
		 *
		 * The TLV320AIC23 is an example of a codec where this करोes not
		 * work. It has a fixed bit घड़ी frequency with progressively
		 * more empty bit घड़ी slots between channels as the sample
		 * rate is lowered.
		 */
		inv_fs = true;
		fallthrough;
	हाल SND_SOC_DAIFMT_DSP_A:
		dev->mode = MOD_DSP_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		dev->mode = MOD_DSP_B;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s:bad format\n", __func__);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		/* CLKRP Receive घड़ी polarity,
		 *	1 - sampled on rising edge of CLKR
		 *	valid on rising edge
		 * CLKXP Transmit घड़ी polarity,
		 *	1 - घड़ीed on falling edge of CLKX
		 *	valid on rising edge
		 * FSRP  Receive frame sync pol, 0 - active high
		 * FSXP  Transmit frame sync pol, 0 - active high
		 */
		pcr |= (DAVINCI_MCBSP_PCR_CLKXP | DAVINCI_MCBSP_PCR_CLKRP);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		/* CLKRP Receive घड़ी polarity,
		 *	0 - sampled on falling edge of CLKR
		 *	valid on falling edge
		 * CLKXP Transmit घड़ी polarity,
		 *	0 - घड़ीed on rising edge of CLKX
		 *	valid on falling edge
		 * FSRP  Receive frame sync pol, 1 - active low
		 * FSXP  Transmit frame sync pol, 1 - active low
		 */
		pcr |= (DAVINCI_MCBSP_PCR_FSXP | DAVINCI_MCBSP_PCR_FSRP);
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		/* CLKRP Receive घड़ी polarity,
		 *	1 - sampled on rising edge of CLKR
		 *	valid on rising edge
		 * CLKXP Transmit घड़ी polarity,
		 *	1 - घड़ीed on falling edge of CLKX
		 *	valid on rising edge
		 * FSRP  Receive frame sync pol, 1 - active low
		 * FSXP  Transmit frame sync pol, 1 - active low
		 */
		pcr |= (DAVINCI_MCBSP_PCR_CLKXP | DAVINCI_MCBSP_PCR_CLKRP |
			DAVINCI_MCBSP_PCR_FSXP | DAVINCI_MCBSP_PCR_FSRP);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		/* CLKRP Receive घड़ी polarity,
		 *	0 - sampled on falling edge of CLKR
		 *	valid on falling edge
		 * CLKXP Transmit घड़ी polarity,
		 *	0 - घड़ीed on rising edge of CLKX
		 *	valid on falling edge
		 * FSRP  Receive frame sync pol, 0 - active high
		 * FSXP  Transmit frame sync pol, 0 - active high
		 */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (inv_fs == true)
		pcr ^= (DAVINCI_MCBSP_PCR_FSXP | DAVINCI_MCBSP_PCR_FSRP);
	davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_SRGR_REG, srgr);
	dev->pcr = pcr;
	davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_PCR_REG, pcr);
	वापस 0;
पूर्ण

अटल पूर्णांक davinci_i2s_dai_set_clkभाग(काष्ठा snd_soc_dai *cpu_dai,
				पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा davinci_mcbsp_dev *dev = snd_soc_dai_get_drvdata(cpu_dai);

	अगर (भाग_id != DAVINCI_MCBSP_CLKGDV)
		वापस -ENODEV;

	dev->clk_भाग = भाग;
	वापस 0;
पूर्ण

अटल पूर्णांक davinci_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा davinci_mcbsp_dev *dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा snd_पूर्णांकerval *i = शून्य;
	पूर्णांक mcbsp_word_length, master;
	अचिन्हित पूर्णांक rcr, xcr, srgr, clk_भाग, freq, framesize;
	u32 spcr;
	snd_pcm_क्रमmat_t fmt;
	अचिन्हित element_cnt = 1;

	/* general line settings */
	spcr = davinci_mcbsp_पढ़ो_reg(dev, DAVINCI_MCBSP_SPCR_REG);
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		spcr |= DAVINCI_MCBSP_SPCR_RINTM(3) | DAVINCI_MCBSP_SPCR_FREE;
		davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_SPCR_REG, spcr);
	पूर्ण अन्यथा अणु
		spcr |= DAVINCI_MCBSP_SPCR_XINTM(3) | DAVINCI_MCBSP_SPCR_FREE;
		davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_SPCR_REG, spcr);
	पूर्ण

	master = dev->fmt & SND_SOC_DAIFMT_MASTER_MASK;
	fmt = params_क्रमmat(params);
	mcbsp_word_length = asp_word_length[fmt];

	चयन (master) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		freq = clk_get_rate(dev->clk);
		srgr = DAVINCI_MCBSP_SRGR_FSGM |
		       DAVINCI_MCBSP_SRGR_CLKSM;
		srgr |= DAVINCI_MCBSP_SRGR_FWID(mcbsp_word_length *
						8 - 1);
		अगर (dev->i2s_accurate_sck) अणु
			clk_भाग = 256;
			करो अणु
				framesize = (freq / (--clk_भाग)) /
				params->rate_num *
					params->rate_den;
			पूर्ण जबतक (((framesize < 33) || (framesize > 4095)) &&
				 (clk_भाग));
			clk_भाग--;
			srgr |= DAVINCI_MCBSP_SRGR_FPER(framesize - 1);
		पूर्ण अन्यथा अणु
			/* symmetric waveक्रमms */
			clk_भाग = freq / (mcbsp_word_length * 16) /
				  params->rate_num * params->rate_den;
			srgr |= DAVINCI_MCBSP_SRGR_FPER(mcbsp_word_length *
							16 - 1);
		पूर्ण
		clk_भाग &= 0xFF;
		srgr |= clk_भाग;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		srgr = DAVINCI_MCBSP_SRGR_FSGM;
		clk_भाग = dev->clk_भाग - 1;
		srgr |= DAVINCI_MCBSP_SRGR_FWID(mcbsp_word_length * 8 - 1);
		srgr |= DAVINCI_MCBSP_SRGR_FPER(mcbsp_word_length * 16 - 1);
		clk_भाग &= 0xFF;
		srgr |= clk_भाग;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* Clock and frame sync given from बाह्यal sources */
		i = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_SAMPLE_BITS);
		srgr = DAVINCI_MCBSP_SRGR_FSGM;
		srgr |= DAVINCI_MCBSP_SRGR_FWID(snd_पूर्णांकerval_value(i) - 1);
		pr_debug("%s - %d  FWID set: re-read srgr = %X\n",
			__func__, __LINE__, snd_पूर्णांकerval_value(i) - 1);

		i = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_FRAME_BITS);
		srgr |= DAVINCI_MCBSP_SRGR_FPER(snd_पूर्णांकerval_value(i) - 1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_SRGR_REG, srgr);

	rcr = DAVINCI_MCBSP_RCR_RFIG;
	xcr = DAVINCI_MCBSP_XCR_XFIG;
	अगर (dev->mode == MOD_DSP_B) अणु
		rcr |= DAVINCI_MCBSP_RCR_RDATDLY(0);
		xcr |= DAVINCI_MCBSP_XCR_XDATDLY(0);
	पूर्ण अन्यथा अणु
		rcr |= DAVINCI_MCBSP_RCR_RDATDLY(1);
		xcr |= DAVINCI_MCBSP_XCR_XDATDLY(1);
	पूर्ण
	/* Determine xfer data type */
	fmt = params_क्रमmat(params);
	अगर ((fmt > SNDRV_PCM_FORMAT_S32_LE) || !data_type[fmt]) अणु
		prपूर्णांकk(KERN_WARNING "davinci-i2s: unsupported PCM format\n");
		वापस -EINVAL;
	पूर्ण

	अगर (params_channels(params) == 2) अणु
		element_cnt = 2;
		अगर (द्विगुन_fmt[fmt] && dev->enable_channel_combine) अणु
			element_cnt = 1;
			fmt = द्विगुन_fmt[fmt];
		पूर्ण
		चयन (master) अणु
		हाल SND_SOC_DAIFMT_CBS_CFS:
		हाल SND_SOC_DAIFMT_CBS_CFM:
			rcr |= DAVINCI_MCBSP_RCR_RFRLEN2(0);
			xcr |= DAVINCI_MCBSP_XCR_XFRLEN2(0);
			rcr |= DAVINCI_MCBSP_RCR_RPHASE;
			xcr |= DAVINCI_MCBSP_XCR_XPHASE;
			अवरोध;
		हाल SND_SOC_DAIFMT_CBM_CFM:
		हाल SND_SOC_DAIFMT_CBM_CFS:
			rcr |= DAVINCI_MCBSP_RCR_RFRLEN2(element_cnt - 1);
			xcr |= DAVINCI_MCBSP_XCR_XFRLEN2(element_cnt - 1);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	mcbsp_word_length = asp_word_length[fmt];

	चयन (master) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
	हाल SND_SOC_DAIFMT_CBS_CFM:
		rcr |= DAVINCI_MCBSP_RCR_RFRLEN1(0);
		xcr |= DAVINCI_MCBSP_XCR_XFRLEN1(0);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
	हाल SND_SOC_DAIFMT_CBM_CFS:
		rcr |= DAVINCI_MCBSP_RCR_RFRLEN1(element_cnt - 1);
		xcr |= DAVINCI_MCBSP_XCR_XFRLEN1(element_cnt - 1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rcr |= DAVINCI_MCBSP_RCR_RWDLEN1(mcbsp_word_length) |
		DAVINCI_MCBSP_RCR_RWDLEN2(mcbsp_word_length);
	xcr |= DAVINCI_MCBSP_XCR_XWDLEN1(mcbsp_word_length) |
		DAVINCI_MCBSP_XCR_XWDLEN2(mcbsp_word_length);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_XCR_REG, xcr);
	अन्यथा
		davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_RCR_REG, rcr);

	pr_debug("%s - %d  srgr=%X\n", __func__, __LINE__, srgr);
	pr_debug("%s - %d  xcr=%X\n", __func__, __LINE__, xcr);
	pr_debug("%s - %d  rcr=%X\n", __func__, __LINE__, rcr);
	वापस 0;
पूर्ण

अटल पूर्णांक davinci_i2s_prepare(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा davinci_mcbsp_dev *dev = snd_soc_dai_get_drvdata(dai);
	पूर्णांक playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	u32 spcr;
	u32 mask = playback ? DAVINCI_MCBSP_SPCR_XRST : DAVINCI_MCBSP_SPCR_RRST;

	davinci_mcbsp_stop(dev, playback);

	spcr = davinci_mcbsp_पढ़ो_reg(dev, DAVINCI_MCBSP_SPCR_REG);
	अगर (spcr & mask) अणु
		/* start off disabled */
		davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_SPCR_REG,
					spcr & ~mask);
		toggle_घड़ी(dev, playback);
	पूर्ण
	अगर (dev->pcr & (DAVINCI_MCBSP_PCR_FSXM | DAVINCI_MCBSP_PCR_FSRM |
			DAVINCI_MCBSP_PCR_CLKXM | DAVINCI_MCBSP_PCR_CLKRM)) अणु
		/* Start the sample generator */
		spcr |= DAVINCI_MCBSP_SPCR_GRST;
		davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_SPCR_REG, spcr);
	पूर्ण

	अगर (playback) अणु
		/* Enable the transmitter */
		spcr = davinci_mcbsp_पढ़ो_reg(dev, DAVINCI_MCBSP_SPCR_REG);
		spcr |= DAVINCI_MCBSP_SPCR_XRST;
		davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_SPCR_REG, spcr);

		/* रुको क्रम any unexpected frame sync error to occur */
		udelay(100);

		/* Disable the transmitter to clear any outstanding XSYNCERR */
		spcr = davinci_mcbsp_पढ़ो_reg(dev, DAVINCI_MCBSP_SPCR_REG);
		spcr &= ~DAVINCI_MCBSP_SPCR_XRST;
		davinci_mcbsp_ग_लिखो_reg(dev, DAVINCI_MCBSP_SPCR_REG, spcr);
		toggle_घड़ी(dev, playback);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा davinci_mcbsp_dev *dev = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret = 0;
	पूर्णांक playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		davinci_mcbsp_start(dev, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		davinci_mcbsp_stop(dev, playback);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम davinci_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा davinci_mcbsp_dev *dev = snd_soc_dai_get_drvdata(dai);
	पूर्णांक playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	davinci_mcbsp_stop(dev, playback);
पूर्ण

#घोषणा DAVINCI_I2S_RATES	SNDRV_PCM_RATE_8000_96000
#घोषणा DAVINCI_I2S_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | \
				 SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops davinci_i2s_dai_ops = अणु
	.shutकरोwn	= davinci_i2s_shutकरोwn,
	.prepare	= davinci_i2s_prepare,
	.trigger	= davinci_i2s_trigger,
	.hw_params	= davinci_i2s_hw_params,
	.set_fmt	= davinci_i2s_set_dai_fmt,
	.set_clkभाग	= davinci_i2s_dai_set_clkभाग,

पूर्ण;

अटल पूर्णांक davinci_i2s_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा davinci_mcbsp_dev *dev = snd_soc_dai_get_drvdata(dai);

	dai->playback_dma_data = &dev->dma_data[SNDRV_PCM_STREAM_PLAYBACK];
	dai->capture_dma_data = &dev->dma_data[SNDRV_PCM_STREAM_CAPTURE];

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver davinci_i2s_dai = अणु
	.probe = davinci_i2s_dai_probe,
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = DAVINCI_I2S_RATES,
		.क्रमmats = DAVINCI_I2S_FORMATS,
	पूर्ण,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = DAVINCI_I2S_RATES,
		.क्रमmats = DAVINCI_I2S_FORMATS,
	पूर्ण,
	.ops = &davinci_i2s_dai_ops,

पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver davinci_i2s_component = अणु
	.name		= DRV_NAME,
पूर्ण;

अटल पूर्णांक davinci_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	काष्ठा davinci_mcbsp_dev *dev;
	काष्ठा resource *mem, *res;
	व्योम __iomem *io_base;
	पूर्णांक *dma;
	पूर्णांक ret;

	mem = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "mpu");
	अगर (!mem) अणु
		dev_warn(&pdev->dev,
			 "\"mpu\" mem resource not found, using index 0\n");
		mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		अगर (!mem) अणु
			dev_err(&pdev->dev, "no mem resource?\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	io_base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(io_base))
		वापस PTR_ERR(io_base);

	dev = devm_kzalloc(&pdev->dev, माप(काष्ठा davinci_mcbsp_dev),
			   GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->base = io_base;

	/* setup DMA, first TX, then RX */
	dma_data = &dev->dma_data[SNDRV_PCM_STREAM_PLAYBACK];
	dma_data->addr = (dma_addr_t)(mem->start + DAVINCI_MCBSP_DXR_REG);

	res = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 0);
	अगर (res) अणु
		dma = &dev->dma_request[SNDRV_PCM_STREAM_PLAYBACK];
		*dma = res->start;
		dma_data->filter_data = dma;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_OF) && pdev->dev.of_node) अणु
		dma_data->filter_data = "tx";
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Missing DMA tx resource\n");
		वापस -ENODEV;
	पूर्ण

	dma_data = &dev->dma_data[SNDRV_PCM_STREAM_CAPTURE];
	dma_data->addr = (dma_addr_t)(mem->start + DAVINCI_MCBSP_DRR_REG);

	res = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 1);
	अगर (res) अणु
		dma = &dev->dma_request[SNDRV_PCM_STREAM_CAPTURE];
		*dma = res->start;
		dma_data->filter_data = dma;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_OF) && pdev->dev.of_node) अणु
		dma_data->filter_data = "rx";
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Missing DMA rx resource\n");
		वापस -ENODEV;
	पूर्ण

	dev->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dev->clk))
		वापस -ENODEV;
	clk_enable(dev->clk);

	dev->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, dev);

	ret = snd_soc_रेजिस्टर_component(&pdev->dev, &davinci_i2s_component,
					 &davinci_i2s_dai, 1);
	अगर (ret != 0)
		जाओ err_release_clk;

	ret = edma_pcm_platक्रमm_रेजिस्टर(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "register PCM failed: %d\n", ret);
		जाओ err_unरेजिस्टर_component;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_component:
	snd_soc_unरेजिस्टर_component(&pdev->dev);
err_release_clk:
	clk_disable(dev->clk);
	clk_put(dev->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक davinci_i2s_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_mcbsp_dev *dev = dev_get_drvdata(&pdev->dev);

	snd_soc_unरेजिस्टर_component(&pdev->dev);

	clk_disable(dev->clk);
	clk_put(dev->clk);
	dev->clk = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id davinci_i2s_match[] __maybe_unused = अणु
	अणु .compatible = "ti,da850-mcbsp" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, davinci_i2s_match);

अटल काष्ठा platक्रमm_driver davinci_mcbsp_driver = अणु
	.probe		= davinci_i2s_probe,
	.हटाओ		= davinci_i2s_हटाओ,
	.driver		= अणु
		.name	= "davinci-mcbsp",
		.of_match_table = of_match_ptr(davinci_i2s_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(davinci_mcbsp_driver);

MODULE_AUTHOR("Vladimir Barinov");
MODULE_DESCRIPTION("TI DAVINCI I2S (McBSP) SoC Interface");
MODULE_LICENSE("GPL");
