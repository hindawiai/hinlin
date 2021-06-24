<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ALSA SoC Audio Layer - S3C PCM-Controller driver
//
// Copyright (c) 2009 Samsung Electronics Co. Ltd
// Author: Jaswinder Singh <jassisinghbrar@gmail.com>
// based upon I2S drivers by Ben Dooks.

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>

#समावेश <linux/platक्रमm_data/asoc-s3c.h>

#समावेश "dma.h"
#समावेश "pcm.h"

/*Register Offsets */
#घोषणा S3C_PCM_CTL		0x00
#घोषणा S3C_PCM_CLKCTL		0x04
#घोषणा S3C_PCM_TXFIFO		0x08
#घोषणा S3C_PCM_RXFIFO		0x0C
#घोषणा S3C_PCM_IRQCTL		0x10
#घोषणा S3C_PCM_IRQSTAT		0x14
#घोषणा S3C_PCM_FIFOSTAT	0x18
#घोषणा S3C_PCM_CLRINT		0x20

/* PCM_CTL Bit-Fields */
#घोषणा S3C_PCM_CTL_TXDIPSTICK_MASK	0x3f
#घोषणा S3C_PCM_CTL_TXDIPSTICK_SHIFT	13
#घोषणा S3C_PCM_CTL_RXDIPSTICK_MASK	0x3f
#घोषणा S3C_PCM_CTL_RXDIPSTICK_SHIFT	7
#घोषणा S3C_PCM_CTL_TXDMA_EN		(0x1 << 6)
#घोषणा S3C_PCM_CTL_RXDMA_EN		(0x1 << 5)
#घोषणा S3C_PCM_CTL_TXMSB_AFTER_FSYNC	(0x1 << 4)
#घोषणा S3C_PCM_CTL_RXMSB_AFTER_FSYNC	(0x1 << 3)
#घोषणा S3C_PCM_CTL_TXFIFO_EN		(0x1 << 2)
#घोषणा S3C_PCM_CTL_RXFIFO_EN		(0x1 << 1)
#घोषणा S3C_PCM_CTL_ENABLE		(0x1 << 0)

/* PCM_CLKCTL Bit-Fields */
#घोषणा S3C_PCM_CLKCTL_SERCLK_EN	(0x1 << 19)
#घोषणा S3C_PCM_CLKCTL_SERCLKSEL_PCLK	(0x1 << 18)
#घोषणा S3C_PCM_CLKCTL_SCLKDIV_MASK	0x1ff
#घोषणा S3C_PCM_CLKCTL_SYNCDIV_MASK	0x1ff
#घोषणा S3C_PCM_CLKCTL_SCLKDIV_SHIFT	9
#घोषणा S3C_PCM_CLKCTL_SYNCDIV_SHIFT	0

/* PCM_TXFIFO Bit-Fields */
#घोषणा S3C_PCM_TXFIFO_DVALID	(0x1 << 16)
#घोषणा S3C_PCM_TXFIFO_DATA_MSK	(0xffff << 0)

/* PCM_RXFIFO Bit-Fields */
#घोषणा S3C_PCM_RXFIFO_DVALID	(0x1 << 16)
#घोषणा S3C_PCM_RXFIFO_DATA_MSK	(0xffff << 0)

/* PCM_IRQCTL Bit-Fields */
#घोषणा S3C_PCM_IRQCTL_IRQEN		(0x1 << 14)
#घोषणा S3C_PCM_IRQCTL_WRDEN		(0x1 << 12)
#घोषणा S3C_PCM_IRQCTL_TXEMPTYEN	(0x1 << 11)
#घोषणा S3C_PCM_IRQCTL_TXALMSTEMPTYEN	(0x1 << 10)
#घोषणा S3C_PCM_IRQCTL_TXFULLEN		(0x1 << 9)
#घोषणा S3C_PCM_IRQCTL_TXALMSTFULLEN	(0x1 << 8)
#घोषणा S3C_PCM_IRQCTL_TXSTARVEN	(0x1 << 7)
#घोषणा S3C_PCM_IRQCTL_TXERROVRFLEN	(0x1 << 6)
#घोषणा S3C_PCM_IRQCTL_RXEMPTEN		(0x1 << 5)
#घोषणा S3C_PCM_IRQCTL_RXALMSTEMPTEN	(0x1 << 4)
#घोषणा S3C_PCM_IRQCTL_RXFULLEN		(0x1 << 3)
#घोषणा S3C_PCM_IRQCTL_RXALMSTFULLEN	(0x1 << 2)
#घोषणा S3C_PCM_IRQCTL_RXSTARVEN	(0x1 << 1)
#घोषणा S3C_PCM_IRQCTL_RXERROVRFLEN	(0x1 << 0)

/* PCM_IRQSTAT Bit-Fields */
#घोषणा S3C_PCM_IRQSTAT_IRQPND		(0x1 << 13)
#घोषणा S3C_PCM_IRQSTAT_WRD_XFER	(0x1 << 12)
#घोषणा S3C_PCM_IRQSTAT_TXEMPTY		(0x1 << 11)
#घोषणा S3C_PCM_IRQSTAT_TXALMSTEMPTY	(0x1 << 10)
#घोषणा S3C_PCM_IRQSTAT_TXFULL		(0x1 << 9)
#घोषणा S3C_PCM_IRQSTAT_TXALMSTFULL	(0x1 << 8)
#घोषणा S3C_PCM_IRQSTAT_TXSTARV		(0x1 << 7)
#घोषणा S3C_PCM_IRQSTAT_TXERROVRFL	(0x1 << 6)
#घोषणा S3C_PCM_IRQSTAT_RXEMPT		(0x1 << 5)
#घोषणा S3C_PCM_IRQSTAT_RXALMSTEMPT	(0x1 << 4)
#घोषणा S3C_PCM_IRQSTAT_RXFULL		(0x1 << 3)
#घोषणा S3C_PCM_IRQSTAT_RXALMSTFULL	(0x1 << 2)
#घोषणा S3C_PCM_IRQSTAT_RXSTARV		(0x1 << 1)
#घोषणा S3C_PCM_IRQSTAT_RXERROVRFL	(0x1 << 0)

/* PCM_FIFOSTAT Bit-Fields */
#घोषणा S3C_PCM_FIFOSTAT_TXCNT_MSK		(0x3f << 14)
#घोषणा S3C_PCM_FIFOSTAT_TXFIFOEMPTY		(0x1 << 13)
#घोषणा S3C_PCM_FIFOSTAT_TXFIFOALMSTEMPTY	(0x1 << 12)
#घोषणा S3C_PCM_FIFOSTAT_TXFIFOFULL		(0x1 << 11)
#घोषणा S3C_PCM_FIFOSTAT_TXFIFOALMSTFULL	(0x1 << 10)
#घोषणा S3C_PCM_FIFOSTAT_RXCNT_MSK		(0x3f << 4)
#घोषणा S3C_PCM_FIFOSTAT_RXFIFOEMPTY		(0x1 << 3)
#घोषणा S3C_PCM_FIFOSTAT_RXFIFOALMSTEMPTY	(0x1 << 2)
#घोषणा S3C_PCM_FIFOSTAT_RXFIFOFULL		(0x1 << 1)
#घोषणा S3C_PCM_FIFOSTAT_RXFIFOALMSTFULL	(0x1 << 0)

/**
 * काष्ठा s3c_pcm_info - S3C PCM Controller inक्रमmation
 * @lock: Spin lock
 * @dev: The parent device passed to use from the probe.
 * @regs: The poपूर्णांकer to the device रेजिस्टर block.
 * @sclk_per_fs: number of sclk per frame sync
 * @idleclk: Whether to keep PCMSCLK enabled even when idle (no active xfer)
 * @pclk: the PCLK_PCM (pcm) घड़ी poपूर्णांकer
 * @cclk: the SCLK_AUDIO (audio-bus) घड़ी poपूर्णांकer
 * @dma_playback: DMA inक्रमmation क्रम playback channel.
 * @dma_capture: DMA inक्रमmation क्रम capture channel.
 */
काष्ठा s3c_pcm_info अणु
	spinlock_t lock;
	काष्ठा device	*dev;
	व्योम __iomem	*regs;

	अचिन्हित पूर्णांक sclk_per_fs;

	/* Whether to keep PCMSCLK enabled even when idle(no active xfer) */
	अचिन्हित पूर्णांक idleclk;

	काष्ठा clk	*pclk;
	काष्ठा clk	*cclk;

	काष्ठा snd_dmaengine_dai_dma_data *dma_playback;
	काष्ठा snd_dmaengine_dai_dma_data *dma_capture;
पूर्ण;

अटल काष्ठा snd_dmaengine_dai_dma_data s3c_pcm_stereo_out[] = अणु
	[0] = अणु
		.addr_width	= 4,
	पूर्ण,
	[1] = अणु
		.addr_width	= 4,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_dmaengine_dai_dma_data s3c_pcm_stereo_in[] = अणु
	[0] = अणु
		.addr_width	= 4,
	पूर्ण,
	[1] = अणु
		.addr_width	= 4,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c_pcm_info s3c_pcm[2];

अटल व्योम s3c_pcm_snd_txctrl(काष्ठा s3c_pcm_info *pcm, पूर्णांक on)
अणु
	व्योम __iomem *regs = pcm->regs;
	u32 ctl, clkctl;

	clkctl = पढ़ोl(regs + S3C_PCM_CLKCTL);
	ctl = पढ़ोl(regs + S3C_PCM_CTL);
	ctl &= ~(S3C_PCM_CTL_TXDIPSTICK_MASK
			 << S3C_PCM_CTL_TXDIPSTICK_SHIFT);

	अगर (on) अणु
		ctl |= S3C_PCM_CTL_TXDMA_EN;
		ctl |= S3C_PCM_CTL_TXFIFO_EN;
		ctl |= S3C_PCM_CTL_ENABLE;
		ctl |= (0x4<<S3C_PCM_CTL_TXDIPSTICK_SHIFT);
		clkctl |= S3C_PCM_CLKCTL_SERCLK_EN;
	पूर्ण अन्यथा अणु
		ctl &= ~S3C_PCM_CTL_TXDMA_EN;
		ctl &= ~S3C_PCM_CTL_TXFIFO_EN;

		अगर (!(ctl & S3C_PCM_CTL_RXFIFO_EN)) अणु
			ctl &= ~S3C_PCM_CTL_ENABLE;
			अगर (!pcm->idleclk)
				clkctl |= S3C_PCM_CLKCTL_SERCLK_EN;
		पूर्ण
	पूर्ण

	ग_लिखोl(clkctl, regs + S3C_PCM_CLKCTL);
	ग_लिखोl(ctl, regs + S3C_PCM_CTL);
पूर्ण

अटल व्योम s3c_pcm_snd_rxctrl(काष्ठा s3c_pcm_info *pcm, पूर्णांक on)
अणु
	व्योम __iomem *regs = pcm->regs;
	u32 ctl, clkctl;

	ctl = पढ़ोl(regs + S3C_PCM_CTL);
	clkctl = पढ़ोl(regs + S3C_PCM_CLKCTL);
	ctl &= ~(S3C_PCM_CTL_RXDIPSTICK_MASK
			 << S3C_PCM_CTL_RXDIPSTICK_SHIFT);

	अगर (on) अणु
		ctl |= S3C_PCM_CTL_RXDMA_EN;
		ctl |= S3C_PCM_CTL_RXFIFO_EN;
		ctl |= S3C_PCM_CTL_ENABLE;
		ctl |= (0x20<<S3C_PCM_CTL_RXDIPSTICK_SHIFT);
		clkctl |= S3C_PCM_CLKCTL_SERCLK_EN;
	पूर्ण अन्यथा अणु
		ctl &= ~S3C_PCM_CTL_RXDMA_EN;
		ctl &= ~S3C_PCM_CTL_RXFIFO_EN;

		अगर (!(ctl & S3C_PCM_CTL_TXFIFO_EN)) अणु
			ctl &= ~S3C_PCM_CTL_ENABLE;
			अगर (!pcm->idleclk)
				clkctl |= S3C_PCM_CLKCTL_SERCLK_EN;
		पूर्ण
	पूर्ण

	ग_लिखोl(clkctl, regs + S3C_PCM_CLKCTL);
	ग_लिखोl(ctl, regs + S3C_PCM_CTL);
पूर्ण

अटल पूर्णांक s3c_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा s3c_pcm_info *pcm = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	अचिन्हित दीर्घ flags;

	dev_dbg(pcm->dev, "Entered %s\n", __func__);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		spin_lock_irqsave(&pcm->lock, flags);

		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			s3c_pcm_snd_rxctrl(pcm, 1);
		अन्यथा
			s3c_pcm_snd_txctrl(pcm, 1);

		spin_unlock_irqrestore(&pcm->lock, flags);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		spin_lock_irqsave(&pcm->lock, flags);

		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			s3c_pcm_snd_rxctrl(pcm, 0);
		अन्यथा
			s3c_pcm_snd_txctrl(pcm, 0);

		spin_unlock_irqrestore(&pcm->lock, flags);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *socdai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा s3c_pcm_info *pcm = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	व्योम __iomem *regs = pcm->regs;
	काष्ठा clk *clk;
	पूर्णांक sclk_भाग, sync_भाग;
	अचिन्हित दीर्घ flags;
	u32 clkctl;

	dev_dbg(pcm->dev, "Entered %s\n", __func__);

	/* Strictly check क्रम sample size */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&pcm->lock, flags);

	/* Get hold of the PCMSOURCE_CLK */
	clkctl = पढ़ोl(regs + S3C_PCM_CLKCTL);
	अगर (clkctl & S3C_PCM_CLKCTL_SERCLKSEL_PCLK)
		clk = pcm->pclk;
	अन्यथा
		clk = pcm->cclk;

	/* Set the SCLK भागider */
	sclk_भाग = clk_get_rate(clk) / pcm->sclk_per_fs /
					params_rate(params) / 2 - 1;

	clkctl &= ~(S3C_PCM_CLKCTL_SCLKDIV_MASK
			<< S3C_PCM_CLKCTL_SCLKDIV_SHIFT);
	clkctl |= ((sclk_भाग & S3C_PCM_CLKCTL_SCLKDIV_MASK)
			<< S3C_PCM_CLKCTL_SCLKDIV_SHIFT);

	/* Set the SYNC भागider */
	sync_भाग = pcm->sclk_per_fs - 1;

	clkctl &= ~(S3C_PCM_CLKCTL_SYNCDIV_MASK
				<< S3C_PCM_CLKCTL_SYNCDIV_SHIFT);
	clkctl |= ((sync_भाग & S3C_PCM_CLKCTL_SYNCDIV_MASK)
				<< S3C_PCM_CLKCTL_SYNCDIV_SHIFT);

	ग_लिखोl(clkctl, regs + S3C_PCM_CLKCTL);

	spin_unlock_irqrestore(&pcm->lock, flags);

	dev_dbg(pcm->dev, "PCMSOURCE_CLK-%lu SCLK=%ufs SCLK_DIV=%d SYNC_DIV=%d\n",
				clk_get_rate(clk), pcm->sclk_per_fs,
				sclk_भाग, sync_भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_pcm_set_fmt(काष्ठा snd_soc_dai *cpu_dai,
			       अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा s3c_pcm_info *pcm = snd_soc_dai_get_drvdata(cpu_dai);
	व्योम __iomem *regs = pcm->regs;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u32 ctl;

	dev_dbg(pcm->dev, "Entered %s\n", __func__);

	spin_lock_irqsave(&pcm->lock, flags);

	ctl = पढ़ोl(regs + S3C_PCM_CTL);

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_NF:
		/* Nothing to करो, IB_NF by शेष */
		अवरोध;
	शेष:
		dev_err(pcm->dev, "Unsupported clock inversion!\n");
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* Nothing to करो, Master by शेष */
		अवरोध;
	शेष:
		dev_err(pcm->dev, "Unsupported master/slave format!\n");
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_CLOCK_MASK) अणु
	हाल SND_SOC_DAIFMT_CONT:
		pcm->idleclk = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_GATED:
		pcm->idleclk = 0;
		अवरोध;
	शेष:
		dev_err(pcm->dev, "Invalid Clock gating request!\n");
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		ctl |= S3C_PCM_CTL_TXMSB_AFTER_FSYNC;
		ctl |= S3C_PCM_CTL_RXMSB_AFTER_FSYNC;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		ctl &= ~S3C_PCM_CTL_TXMSB_AFTER_FSYNC;
		ctl &= ~S3C_PCM_CTL_RXMSB_AFTER_FSYNC;
		अवरोध;
	शेष:
		dev_err(pcm->dev, "Unsupported data format!\n");
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	ग_लिखोl(ctl, regs + S3C_PCM_CTL);

निकास:
	spin_unlock_irqrestore(&pcm->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक s3c_pcm_set_clkभाग(काष्ठा snd_soc_dai *cpu_dai,
						पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा s3c_pcm_info *pcm = snd_soc_dai_get_drvdata(cpu_dai);

	चयन (भाग_id) अणु
	हाल S3C_PCM_SCLK_PER_FS:
		pcm->sclk_per_fs = भाग;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_pcm_set_sysclk(काष्ठा snd_soc_dai *cpu_dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा s3c_pcm_info *pcm = snd_soc_dai_get_drvdata(cpu_dai);
	व्योम __iomem *regs = pcm->regs;
	u32 clkctl = पढ़ोl(regs + S3C_PCM_CLKCTL);

	चयन (clk_id) अणु
	हाल S3C_PCM_CLKSRC_PCLK:
		clkctl |= S3C_PCM_CLKCTL_SERCLKSEL_PCLK;
		अवरोध;

	हाल S3C_PCM_CLKSRC_MUX:
		clkctl &= ~S3C_PCM_CLKCTL_SERCLKSEL_PCLK;

		अगर (clk_get_rate(pcm->cclk) != freq)
			clk_set_rate(pcm->cclk, freq);

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(clkctl, regs + S3C_PCM_CLKCTL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops s3c_pcm_dai_ops = अणु
	.set_sysclk	= s3c_pcm_set_sysclk,
	.set_clkभाग	= s3c_pcm_set_clkभाग,
	.trigger	= s3c_pcm_trigger,
	.hw_params	= s3c_pcm_hw_params,
	.set_fmt	= s3c_pcm_set_fmt,
पूर्ण;

अटल पूर्णांक s3c_pcm_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा s3c_pcm_info *pcm = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, pcm->dma_playback, pcm->dma_capture);

	वापस 0;
पूर्ण

#घोषणा S3C_PCM_RATES  SNDRV_PCM_RATE_8000_96000

#घोषणा S3C_PCM_DAI_DECLARE			\
	.symmetric_rate = 1,					\
	.probe = s3c_pcm_dai_probe,				\
	.ops = &s3c_pcm_dai_ops,				\
	.playback = अणु						\
		.channels_min	= 2,				\
		.channels_max	= 2,				\
		.rates		= S3C_PCM_RATES,		\
		.क्रमmats	= SNDRV_PCM_FMTBIT_S16_LE,	\
	पूर्ण,							\
	.capture = अणु						\
		.channels_min	= 2,				\
		.channels_max	= 2,				\
		.rates		= S3C_PCM_RATES,		\
		.क्रमmats	= SNDRV_PCM_FMTBIT_S16_LE,	\
	पूर्ण

अटल काष्ठा snd_soc_dai_driver s3c_pcm_dai[] = अणु
	[0] = अणु
		.name	= "samsung-pcm.0",
		S3C_PCM_DAI_DECLARE,
	पूर्ण,
	[1] = अणु
		.name	= "samsung-pcm.1",
		S3C_PCM_DAI_DECLARE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver s3c_pcm_component = अणु
	.name		= "s3c-pcm",
पूर्ण;

अटल पूर्णांक s3c_pcm_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c_pcm_info *pcm;
	काष्ठा resource *mem_res;
	काष्ठा s3c_audio_pdata *pcm_pdata;
	dma_filter_fn filter;
	पूर्णांक ret;

	/* Check क्रम valid device index */
	अगर ((pdev->id < 0) || pdev->id >= ARRAY_SIZE(s3c_pcm)) अणु
		dev_err(&pdev->dev, "id %d out of range\n", pdev->id);
		वापस -EINVAL;
	पूर्ण

	pcm_pdata = pdev->dev.platक्रमm_data;

	अगर (pcm_pdata && pcm_pdata->cfg_gpio && pcm_pdata->cfg_gpio(pdev)) अणु
		dev_err(&pdev->dev, "Unable to configure gpio\n");
		वापस -EINVAL;
	पूर्ण

	pcm = &s3c_pcm[pdev->id];
	pcm->dev = &pdev->dev;

	spin_lock_init(&pcm->lock);

	/* Default is 128fs */
	pcm->sclk_per_fs = 128;

	mem_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pcm->regs = devm_ioremap_resource(&pdev->dev, mem_res);
	अगर (IS_ERR(pcm->regs))
		वापस PTR_ERR(pcm->regs);

	pcm->cclk = devm_clk_get(&pdev->dev, "audio-bus");
	अगर (IS_ERR(pcm->cclk)) अणु
		dev_err(&pdev->dev, "failed to get audio-bus clock\n");
		वापस PTR_ERR(pcm->cclk);
	पूर्ण
	ret = clk_prepare_enable(pcm->cclk);
	अगर (ret)
		वापस ret;

	/* record our pcm काष्ठाure क्रम later use in the callbacks */
	dev_set_drvdata(&pdev->dev, pcm);

	pcm->pclk = devm_clk_get(&pdev->dev, "pcm");
	अगर (IS_ERR(pcm->pclk)) अणु
		dev_err(&pdev->dev, "failed to get pcm clock\n");
		ret = PTR_ERR(pcm->pclk);
		जाओ err_dis_cclk;
	पूर्ण
	ret = clk_prepare_enable(pcm->pclk);
	अगर (ret)
		जाओ err_dis_cclk;

	s3c_pcm_stereo_in[pdev->id].addr = mem_res->start + S3C_PCM_RXFIFO;
	s3c_pcm_stereo_out[pdev->id].addr = mem_res->start + S3C_PCM_TXFIFO;

	filter = शून्य;
	अगर (pcm_pdata) अणु
		s3c_pcm_stereo_in[pdev->id].filter_data = pcm_pdata->dma_capture;
		s3c_pcm_stereo_out[pdev->id].filter_data = pcm_pdata->dma_playback;
		filter = pcm_pdata->dma_filter;
	पूर्ण

	pcm->dma_capture = &s3c_pcm_stereo_in[pdev->id];
	pcm->dma_playback = &s3c_pcm_stereo_out[pdev->id];

	ret = samsung_asoc_dma_platक्रमm_रेजिस्टर(&pdev->dev, filter,
						 शून्य, शून्य, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get register DMA: %d\n", ret);
		जाओ err_dis_pclk;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &s3c_pcm_component,
					 &s3c_pcm_dai[pdev->id], 1);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "failed to get register DAI: %d\n", ret);
		जाओ err_dis_pm;
	पूर्ण

	वापस 0;

err_dis_pm:
	pm_runसमय_disable(&pdev->dev);
err_dis_pclk:
	clk_disable_unprepare(pcm->pclk);
err_dis_cclk:
	clk_disable_unprepare(pcm->cclk);
	वापस ret;
पूर्ण

अटल पूर्णांक s3c_pcm_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c_pcm_info *pcm = &s3c_pcm[pdev->id];

	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(pcm->cclk);
	clk_disable_unprepare(pcm->pclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver s3c_pcm_driver = अणु
	.probe  = s3c_pcm_dev_probe,
	.हटाओ = s3c_pcm_dev_हटाओ,
	.driver = अणु
		.name = "samsung-pcm",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(s3c_pcm_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Jaswinder Singh, <jassisinghbrar@gmail.com>");
MODULE_DESCRIPTION("S3C PCM Controller Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:samsung-pcm");
