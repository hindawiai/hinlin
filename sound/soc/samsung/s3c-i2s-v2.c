<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// ALSA Soc Audio Layer - I2S core क्रम newer Samsung SoCs.
//
// Copyright (c) 2006 Wolfson Microelectronics PLC.
//	Graeme Gregory graeme.gregory@wolfsonmicro.com
//	linux@wolfsonmicro.com
//
// Copyright (c) 2008, 2007, 2004-2005 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>

#समावेश "regs-i2s-v2.h"
#समावेश "s3c-i2s-v2.h"

#अघोषित S3C_IIS_V2_SUPPORTED

#अगर defined(CONFIG_CPU_S3C2412) \
	|| defined(CONFIG_ARCH_S3C64XX) || defined(CONFIG_CPU_S5PV210)
#घोषणा S3C_IIS_V2_SUPPORTED
#पूर्ण_अगर

#अगर_अघोषित S3C_IIS_V2_SUPPORTED
#त्रुटि Unsupported CPU model
#पूर्ण_अगर

#घोषणा S3C2412_I2S_DEBUG_CON 0

अटल अंतरभूत काष्ठा s3c_i2sv2_info *to_info(काष्ठा snd_soc_dai *cpu_dai)
अणु
	वापस snd_soc_dai_get_drvdata(cpu_dai);
पूर्ण

#घोषणा bit_set(v, b) (((v) & (b)) ? 1 : 0)

#अगर S3C2412_I2S_DEBUG_CON
अटल व्योम dbg_showcon(स्थिर अक्षर *fn, u32 con)
अणु
	prपूर्णांकk(KERN_DEBUG "%s: LRI=%d, TXFEMPT=%d, RXFEMPT=%d, TXFFULL=%d, RXFFULL=%d\n", fn,
	       bit_set(con, S3C2412_IISCON_LRINDEX),
	       bit_set(con, S3C2412_IISCON_TXFIFO_EMPTY),
	       bit_set(con, S3C2412_IISCON_RXFIFO_EMPTY),
	       bit_set(con, S3C2412_IISCON_TXFIFO_FULL),
	       bit_set(con, S3C2412_IISCON_RXFIFO_FULL));

	prपूर्णांकk(KERN_DEBUG "%s: PAUSE: TXDMA=%d, RXDMA=%d, TXCH=%d, RXCH=%d\n",
	       fn,
	       bit_set(con, S3C2412_IISCON_TXDMA_PAUSE),
	       bit_set(con, S3C2412_IISCON_RXDMA_PAUSE),
	       bit_set(con, S3C2412_IISCON_TXCH_PAUSE),
	       bit_set(con, S3C2412_IISCON_RXCH_PAUSE));
	prपूर्णांकk(KERN_DEBUG "%s: ACTIVE: TXDMA=%d, RXDMA=%d, IIS=%d\n", fn,
	       bit_set(con, S3C2412_IISCON_TXDMA_ACTIVE),
	       bit_set(con, S3C2412_IISCON_RXDMA_ACTIVE),
	       bit_set(con, S3C2412_IISCON_IIS_ACTIVE));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dbg_showcon(स्थिर अक्षर *fn, u32 con)
अणु
पूर्ण
#पूर्ण_अगर

/* Turn on or off the transmission path. */
अटल व्योम s3c2412_snd_txctrl(काष्ठा s3c_i2sv2_info *i2s, पूर्णांक on)
अणु
	व्योम __iomem *regs = i2s->regs;
	u32 fic, con, mod;

	pr_debug("%s(%d)\n", __func__, on);

	fic = पढ़ोl(regs + S3C2412_IISFIC);
	con = पढ़ोl(regs + S3C2412_IISCON);
	mod = पढ़ोl(regs + S3C2412_IISMOD);

	pr_debug("%s: IIS: CON=%x MOD=%x FIC=%x\n", __func__, con, mod, fic);

	अगर (on) अणु
		con |= S3C2412_IISCON_TXDMA_ACTIVE | S3C2412_IISCON_IIS_ACTIVE;
		con &= ~S3C2412_IISCON_TXDMA_PAUSE;
		con &= ~S3C2412_IISCON_TXCH_PAUSE;

		चयन (mod & S3C2412_IISMOD_MODE_MASK) अणु
		हाल S3C2412_IISMOD_MODE_TXONLY:
		हाल S3C2412_IISMOD_MODE_TXRX:
			/* करो nothing, we are in the right mode */
			अवरोध;

		हाल S3C2412_IISMOD_MODE_RXONLY:
			mod &= ~S3C2412_IISMOD_MODE_MASK;
			mod |= S3C2412_IISMOD_MODE_TXRX;
			अवरोध;

		शेष:
			dev_err(i2s->dev, "TXEN: Invalid MODE %x in IISMOD\n",
				mod & S3C2412_IISMOD_MODE_MASK);
			अवरोध;
		पूर्ण

		ग_लिखोl(con, regs + S3C2412_IISCON);
		ग_लिखोl(mod, regs + S3C2412_IISMOD);
	पूर्ण अन्यथा अणु
		/* Note, we करो not have any indication that the FIFO problems
		 * tha the S3C2410/2440 had apply here, so we should be able
		 * to disable the DMA and TX without resetting the FIFOS.
		 */

		con |=  S3C2412_IISCON_TXDMA_PAUSE;
		con |=  S3C2412_IISCON_TXCH_PAUSE;
		con &= ~S3C2412_IISCON_TXDMA_ACTIVE;

		चयन (mod & S3C2412_IISMOD_MODE_MASK) अणु
		हाल S3C2412_IISMOD_MODE_TXRX:
			mod &= ~S3C2412_IISMOD_MODE_MASK;
			mod |= S3C2412_IISMOD_MODE_RXONLY;
			अवरोध;

		हाल S3C2412_IISMOD_MODE_TXONLY:
			mod &= ~S3C2412_IISMOD_MODE_MASK;
			con &= ~S3C2412_IISCON_IIS_ACTIVE;
			अवरोध;

		शेष:
			dev_err(i2s->dev, "TXDIS: Invalid MODE %x in IISMOD\n",
				mod & S3C2412_IISMOD_MODE_MASK);
			अवरोध;
		पूर्ण

		ग_लिखोl(mod, regs + S3C2412_IISMOD);
		ग_लिखोl(con, regs + S3C2412_IISCON);
	पूर्ण

	fic = पढ़ोl(regs + S3C2412_IISFIC);
	dbg_showcon(__func__, con);
	pr_debug("%s: IIS: CON=%x MOD=%x FIC=%x\n", __func__, con, mod, fic);
पूर्ण

अटल व्योम s3c2412_snd_rxctrl(काष्ठा s3c_i2sv2_info *i2s, पूर्णांक on)
अणु
	व्योम __iomem *regs = i2s->regs;
	u32 fic, con, mod;

	pr_debug("%s(%d)\n", __func__, on);

	fic = पढ़ोl(regs + S3C2412_IISFIC);
	con = पढ़ोl(regs + S3C2412_IISCON);
	mod = पढ़ोl(regs + S3C2412_IISMOD);

	pr_debug("%s: IIS: CON=%x MOD=%x FIC=%x\n", __func__, con, mod, fic);

	अगर (on) अणु
		con |= S3C2412_IISCON_RXDMA_ACTIVE | S3C2412_IISCON_IIS_ACTIVE;
		con &= ~S3C2412_IISCON_RXDMA_PAUSE;
		con &= ~S3C2412_IISCON_RXCH_PAUSE;

		चयन (mod & S3C2412_IISMOD_MODE_MASK) अणु
		हाल S3C2412_IISMOD_MODE_TXRX:
		हाल S3C2412_IISMOD_MODE_RXONLY:
			/* करो nothing, we are in the right mode */
			अवरोध;

		हाल S3C2412_IISMOD_MODE_TXONLY:
			mod &= ~S3C2412_IISMOD_MODE_MASK;
			mod |= S3C2412_IISMOD_MODE_TXRX;
			अवरोध;

		शेष:
			dev_err(i2s->dev, "RXEN: Invalid MODE %x in IISMOD\n",
				mod & S3C2412_IISMOD_MODE_MASK);
		पूर्ण

		ग_लिखोl(mod, regs + S3C2412_IISMOD);
		ग_लिखोl(con, regs + S3C2412_IISCON);
	पूर्ण अन्यथा अणु
		/* See txctrl notes on FIFOs. */

		con &= ~S3C2412_IISCON_RXDMA_ACTIVE;
		con |=  S3C2412_IISCON_RXDMA_PAUSE;
		con |=  S3C2412_IISCON_RXCH_PAUSE;

		चयन (mod & S3C2412_IISMOD_MODE_MASK) अणु
		हाल S3C2412_IISMOD_MODE_RXONLY:
			con &= ~S3C2412_IISCON_IIS_ACTIVE;
			mod &= ~S3C2412_IISMOD_MODE_MASK;
			अवरोध;

		हाल S3C2412_IISMOD_MODE_TXRX:
			mod &= ~S3C2412_IISMOD_MODE_MASK;
			mod |= S3C2412_IISMOD_MODE_TXONLY;
			अवरोध;

		शेष:
			dev_err(i2s->dev, "RXDIS: Invalid MODE %x in IISMOD\n",
				mod & S3C2412_IISMOD_MODE_MASK);
		पूर्ण

		ग_लिखोl(con, regs + S3C2412_IISCON);
		ग_लिखोl(mod, regs + S3C2412_IISMOD);
	पूर्ण

	fic = पढ़ोl(regs + S3C2412_IISFIC);
	pr_debug("%s: IIS: CON=%x MOD=%x FIC=%x\n", __func__, con, mod, fic);
पूर्ण

#घोषणा msecs_to_loops(t) (loops_per_jअगरfy / 1000 * HZ * t)

/*
 * Wait क्रम the LR संकेत to allow synchronisation to the L/R घड़ी
 * from the codec. May only be needed क्रम slave mode.
 */
अटल पूर्णांक s3c2412_snd_lrsync(काष्ठा s3c_i2sv2_info *i2s)
अणु
	u32 iiscon;
	अचिन्हित दीर्घ loops = msecs_to_loops(5);

	pr_debug("Entered %s\n", __func__);

	जबतक (--loops) अणु
		iiscon = पढ़ोl(i2s->regs + S3C2412_IISCON);
		अगर (iiscon & S3C2412_IISCON_LRINDEX)
			अवरोध;

		cpu_relax();
	पूर्ण

	अगर (!loops) अणु
		prपूर्णांकk(KERN_ERR "%s: timeout\n", __func__);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set S3C2412 I2S DAI क्रमmat
 */
अटल पूर्णांक s3c2412_i2s_set_fmt(काष्ठा snd_soc_dai *cpu_dai,
			       अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा s3c_i2sv2_info *i2s = to_info(cpu_dai);
	u32 iismod;

	pr_debug("Entered %s\n", __func__);

	iismod = पढ़ोl(i2s->regs + S3C2412_IISMOD);
	pr_debug("hw_params r: IISMOD: %x \n", iismod);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		i2s->master = 0;
		iismod |= S3C2412_IISMOD_SLAVE;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		i2s->master = 1;
		iismod &= ~S3C2412_IISMOD_SLAVE;
		अवरोध;
	शेष:
		pr_err("unknown master/slave format\n");
		वापस -EINVAL;
	पूर्ण

	iismod &= ~S3C2412_IISMOD_SDF_MASK;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_RIGHT_J:
		iismod |= S3C2412_IISMOD_LR_RLOW;
		iismod |= S3C2412_IISMOD_SDF_MSB;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		iismod |= S3C2412_IISMOD_LR_RLOW;
		iismod |= S3C2412_IISMOD_SDF_LSB;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		iismod &= ~S3C2412_IISMOD_LR_RLOW;
		iismod |= S3C2412_IISMOD_SDF_IIS;
		अवरोध;
	शेष:
		pr_err("Unknown data format\n");
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(iismod, i2s->regs + S3C2412_IISMOD);
	pr_debug("hw_params w: IISMOD: %x \n", iismod);
	वापस 0;
पूर्ण

अटल पूर्णांक s3c_i2sv2_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा s3c_i2sv2_info *i2s = to_info(dai);
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	u32 iismod;

	pr_debug("Entered %s\n", __func__);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dma_data = i2s->dma_playback;
	अन्यथा
		dma_data = i2s->dma_capture;

	snd_soc_dai_set_dma_data(dai, substream, dma_data);

	/* Working copies of रेजिस्टर */
	iismod = पढ़ोl(i2s->regs + S3C2412_IISMOD);
	pr_debug("%s: r: IISMOD: %x\n", __func__, iismod);

	iismod &= ~S3C64XX_IISMOD_BLC_MASK;
	/* Sample size */
	चयन (params_width(params)) अणु
	हाल 8:
		iismod |= S3C64XX_IISMOD_BLC_8BIT;
		अवरोध;
	हाल 16:
		अवरोध;
	हाल 24:
		iismod |= S3C64XX_IISMOD_BLC_24BIT;
		अवरोध;
	पूर्ण

	ग_लिखोl(iismod, i2s->regs + S3C2412_IISMOD);
	pr_debug("%s: w: IISMOD: %x\n", __func__, iismod);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_i2sv2_set_sysclk(काष्ठा snd_soc_dai *cpu_dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा s3c_i2sv2_info *i2s = to_info(cpu_dai);
	u32 iismod = पढ़ोl(i2s->regs + S3C2412_IISMOD);

	pr_debug("Entered %s\n", __func__);
	pr_debug("%s r: IISMOD: %x\n", __func__, iismod);

	चयन (clk_id) अणु
	हाल S3C_I2SV2_CLKSRC_PCLK:
		iismod &= ~S3C2412_IISMOD_IMS_SYSMUX;
		अवरोध;

	हाल S3C_I2SV2_CLKSRC_AUDIOBUS:
		iismod |= S3C2412_IISMOD_IMS_SYSMUX;
		अवरोध;

	हाल S3C_I2SV2_CLKSRC_CDCLK:
		/* Error अगर controller करोesn't have the CDCLKCON bit */
		अगर (!(i2s->feature & S3C_FEATURE_CDCLKCON))
			वापस -EINVAL;

		चयन (dir) अणु
		हाल SND_SOC_CLOCK_IN:
			iismod |= S3C64XX_IISMOD_CDCLKCON;
			अवरोध;
		हाल SND_SOC_CLOCK_OUT:
			iismod &= ~S3C64XX_IISMOD_CDCLKCON;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(iismod, i2s->regs + S3C2412_IISMOD);
	pr_debug("%s w: IISMOD: %x\n", __func__, iismod);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2412_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा s3c_i2sv2_info *i2s = to_info(asoc_rtd_to_cpu(rtd, 0));
	पूर्णांक capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);
	अचिन्हित दीर्घ irqs;
	पूर्णांक ret = 0;

	pr_debug("Entered %s\n", __func__);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		/* On start, ensure that the FIFOs are cleared and reset. */

		ग_लिखोl(capture ? S3C2412_IISFIC_RXFLUSH : S3C2412_IISFIC_TXFLUSH,
		       i2s->regs + S3C2412_IISFIC);

		/* clear again, just in हाल */
		ग_लिखोl(0x0, i2s->regs + S3C2412_IISFIC);

	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (!i2s->master) अणु
			ret = s3c2412_snd_lrsync(i2s);
			अगर (ret)
				जाओ निकास_err;
		पूर्ण

		local_irq_save(irqs);

		अगर (capture)
			s3c2412_snd_rxctrl(i2s, 1);
		अन्यथा
			s3c2412_snd_txctrl(i2s, 1);

		local_irq_restore(irqs);

		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		local_irq_save(irqs);

		अगर (capture)
			s3c2412_snd_rxctrl(i2s, 0);
		अन्यथा
			s3c2412_snd_txctrl(i2s, 0);

		local_irq_restore(irqs);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

निकास_err:
	वापस ret;
पूर्ण

/*
 * Set S3C2412 Clock भागiders
 */
अटल पूर्णांक s3c2412_i2s_set_clkभाग(काष्ठा snd_soc_dai *cpu_dai,
				  पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा s3c_i2sv2_info *i2s = to_info(cpu_dai);
	u32 reg;

	pr_debug("%s(%p, %d, %d)\n", __func__, cpu_dai, भाग_id, भाग);

	चयन (भाग_id) अणु
	हाल S3C_I2SV2_DIV_BCLK:
		चयन (भाग) अणु
		हाल 16:
			भाग = S3C2412_IISMOD_BCLK_16FS;
			अवरोध;

		हाल 32:
			भाग = S3C2412_IISMOD_BCLK_32FS;
			अवरोध;

		हाल 24:
			भाग = S3C2412_IISMOD_BCLK_24FS;
			अवरोध;

		हाल 48:
			भाग = S3C2412_IISMOD_BCLK_48FS;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण

		reg = पढ़ोl(i2s->regs + S3C2412_IISMOD);
		reg &= ~S3C2412_IISMOD_BCLK_MASK;
		ग_लिखोl(reg | भाग, i2s->regs + S3C2412_IISMOD);

		pr_debug("%s: MOD=%08x\n", __func__, पढ़ोl(i2s->regs + S3C2412_IISMOD));
		अवरोध;

	हाल S3C_I2SV2_DIV_RCLK:
		चयन (भाग) अणु
		हाल 256:
			भाग = S3C2412_IISMOD_RCLK_256FS;
			अवरोध;

		हाल 384:
			भाग = S3C2412_IISMOD_RCLK_384FS;
			अवरोध;

		हाल 512:
			भाग = S3C2412_IISMOD_RCLK_512FS;
			अवरोध;

		हाल 768:
			भाग = S3C2412_IISMOD_RCLK_768FS;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण

		reg = पढ़ोl(i2s->regs + S3C2412_IISMOD);
		reg &= ~S3C2412_IISMOD_RCLK_MASK;
		ग_लिखोl(reg | भाग, i2s->regs + S3C2412_IISMOD);
		pr_debug("%s: MOD=%08x\n", __func__, पढ़ोl(i2s->regs + S3C2412_IISMOD));
		अवरोध;

	हाल S3C_I2SV2_DIV_PRESCALER:
		अगर (भाग >= 0) अणु
			ग_लिखोl((भाग << 8) | S3C2412_IISPSR_PSREN,
			       i2s->regs + S3C2412_IISPSR);
		पूर्ण अन्यथा अणु
			ग_लिखोl(0x0, i2s->regs + S3C2412_IISPSR);
		पूर्ण
		pr_debug("%s: PSR=%08x\n", __func__, पढ़ोl(i2s->regs + S3C2412_IISPSR));
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_sframes_t s3c2412_i2s_delay(काष्ठा snd_pcm_substream *substream,
					   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा s3c_i2sv2_info *i2s = to_info(dai);
	u32 reg = पढ़ोl(i2s->regs + S3C2412_IISFIC);
	snd_pcm_sframes_t delay;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		delay = S3C2412_IISFIC_TXCOUNT(reg);
	अन्यथा
		delay = S3C2412_IISFIC_RXCOUNT(reg);

	वापस delay;
पूर्ण

काष्ठा clk *s3c_i2sv2_get_घड़ी(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा s3c_i2sv2_info *i2s = to_info(cpu_dai);
	u32 iismod = पढ़ोl(i2s->regs + S3C2412_IISMOD);

	अगर (iismod & S3C2412_IISMOD_IMS_SYSMUX)
		वापस i2s->iis_cclk;
	अन्यथा
		वापस i2s->iis_pclk;
पूर्ण
EXPORT_SYMBOL_GPL(s3c_i2sv2_get_घड़ी);

/* शेष table of all avaialable root fs भागisors */
अटल अचिन्हित पूर्णांक iis_fs_tab[] = अणु 256, 512, 384, 768 पूर्ण;

पूर्णांक s3c_i2sv2_iis_calc_rate(काष्ठा s3c_i2sv2_rate_calc *info,
			    अचिन्हित पूर्णांक *fstab,
			    अचिन्हित पूर्णांक rate, काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ clkrate = clk_get_rate(clk);
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक fsclk;
	अचिन्हित पूर्णांक actual;
	अचिन्हित पूर्णांक fs;
	अचिन्हित पूर्णांक fsभाग;
	चिन्हित पूर्णांक deviation = 0;
	अचिन्हित पूर्णांक best_fs = 0;
	अचिन्हित पूर्णांक best_भाग = 0;
	अचिन्हित पूर्णांक best_rate = 0;
	अचिन्हित पूर्णांक best_deviation = पूर्णांक_उच्च;

	pr_debug("Input clock rate %ldHz\n", clkrate);

	अगर (fstab == शून्य)
		fstab = iis_fs_tab;

	क्रम (fs = 0; fs < ARRAY_SIZE(iis_fs_tab); fs++) अणु
		fsभाग = iis_fs_tab[fs];

		fsclk = clkrate / fsभाग;
		भाग = fsclk / rate;

		अगर ((fsclk % rate) > (rate / 2))
			भाग++;

		अगर (भाग <= 1)
			जारी;

		actual = clkrate / (fsभाग * भाग);
		deviation = actual - rate;

		prपूर्णांकk(KERN_DEBUG "%ufs: div %u => result %u, deviation %d\n",
		       fsभाग, भाग, actual, deviation);

		deviation = असल(deviation);

		अगर (deviation < best_deviation) अणु
			best_fs = fsभाग;
			best_भाग = भाग;
			best_rate = actual;
			best_deviation = deviation;
		पूर्ण

		अगर (deviation == 0)
			अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "best: fs=%u, div=%u, rate=%u\n",
	       best_fs, best_भाग, best_rate);

	info->fs_भाग = best_fs;
	info->clk_भाग = best_भाग;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(s3c_i2sv2_iis_calc_rate);

पूर्णांक s3c_i2sv2_probe(काष्ठा snd_soc_dai *dai,
		    काष्ठा s3c_i2sv2_info *i2s)
अणु
	काष्ठा device *dev = dai->dev;
	अचिन्हित पूर्णांक iismod;

	i2s->dev = dev;

	/* record our i2s काष्ठाure क्रम later use in the callbacks */
	snd_soc_dai_set_drvdata(dai, i2s);

	i2s->iis_pclk = clk_get(dev, "iis");
	अगर (IS_ERR(i2s->iis_pclk)) अणु
		dev_err(dev, "failed to get iis_clock\n");
		वापस -ENOENT;
	पूर्ण

	clk_prepare_enable(i2s->iis_pclk);

	/* Mark ourselves as in TXRX mode so we can run through our cleanup
	 * process without warnings. */
	iismod = पढ़ोl(i2s->regs + S3C2412_IISMOD);
	iismod |= S3C2412_IISMOD_MODE_TXRX;
	ग_लिखोl(iismod, i2s->regs + S3C2412_IISMOD);
	s3c2412_snd_txctrl(i2s, 0);
	s3c2412_snd_rxctrl(i2s, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(s3c_i2sv2_probe);

व्योम s3c_i2sv2_cleanup(काष्ठा snd_soc_dai *dai,
		      काष्ठा s3c_i2sv2_info *i2s)
अणु
	clk_disable_unprepare(i2s->iis_pclk);
	clk_put(i2s->iis_pclk);
	i2s->iis_pclk = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(s3c_i2sv2_cleanup);

पूर्णांक s3c_i2sv2_रेजिस्टर_component(काष्ठा device *dev, पूर्णांक id,
			   स्थिर काष्ठा snd_soc_component_driver *cmp_drv,
			   काष्ठा snd_soc_dai_driver *dai_drv)
अणु
	काष्ठा snd_soc_dai_ops *ops = (काष्ठा snd_soc_dai_ops *)dai_drv->ops;

	ops->trigger = s3c2412_i2s_trigger;
	अगर (!ops->hw_params)
		ops->hw_params = s3c_i2sv2_hw_params;
	ops->set_fmt = s3c2412_i2s_set_fmt;
	ops->set_clkभाग = s3c2412_i2s_set_clkभाग;
	ops->set_sysclk = s3c_i2sv2_set_sysclk;

	/* Allow overriding by (क्रम example) IISv4 */
	अगर (!ops->delay)
		ops->delay = s3c2412_i2s_delay;

	वापस devm_snd_soc_रेजिस्टर_component(dev, cmp_drv, dai_drv, 1);
पूर्ण
EXPORT_SYMBOL_GPL(s3c_i2sv2_रेजिस्टर_component);

MODULE_LICENSE("GPL");
