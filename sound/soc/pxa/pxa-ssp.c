<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pxa-ssp.c  --  ALSA Soc Audio Layer
 *
 * Copyright 2005,2008 Wolfson Microelectronics PLC.
 * Author: Liam Girdwood
 *         Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *
 * TODO:
 *  o Test network mode क्रम > 16bit sample size
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/pxa2xx_ssp.h>
#समावेश <linux/of.h>
#समावेश <linux/dmaengine.h>

#समावेश <यंत्र/irq.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/pxa2xx-lib.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "pxa-ssp.h"

/*
 * SSP audio निजी data
 */
काष्ठा ssp_priv अणु
	काष्ठा ssp_device *ssp;
	काष्ठा clk *extclk;
	अचिन्हित दीर्घ ssp_clk;
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक dai_fmt;
	अचिन्हित पूर्णांक configured_dai_fmt;
#अगर_घोषित CONFIG_PM
	uपूर्णांक32_t	cr0;
	uपूर्णांक32_t	cr1;
	uपूर्णांक32_t	to;
	uपूर्णांक32_t	psp;
#पूर्ण_अगर
पूर्ण;

अटल व्योम dump_रेजिस्टरs(काष्ठा ssp_device *ssp)
अणु
	dev_dbg(ssp->dev, "SSCR0 0x%08x SSCR1 0x%08x SSTO 0x%08x\n",
		 pxa_ssp_पढ़ो_reg(ssp, SSCR0), pxa_ssp_पढ़ो_reg(ssp, SSCR1),
		 pxa_ssp_पढ़ो_reg(ssp, SSTO));

	dev_dbg(ssp->dev, "SSPSP 0x%08x SSSR 0x%08x SSACD 0x%08x\n",
		 pxa_ssp_पढ़ो_reg(ssp, SSPSP), pxa_ssp_पढ़ो_reg(ssp, SSSR),
		 pxa_ssp_पढ़ो_reg(ssp, SSACD));
पूर्ण

अटल व्योम pxa_ssp_enable(काष्ठा ssp_device *ssp)
अणु
	uपूर्णांक32_t sscr0;

	sscr0 = __raw_पढ़ोl(ssp->mmio_base + SSCR0) | SSCR0_SSE;
	__raw_ग_लिखोl(sscr0, ssp->mmio_base + SSCR0);
पूर्ण

अटल व्योम pxa_ssp_disable(काष्ठा ssp_device *ssp)
अणु
	uपूर्णांक32_t sscr0;

	sscr0 = __raw_पढ़ोl(ssp->mmio_base + SSCR0) & ~SSCR0_SSE;
	__raw_ग_लिखोl(sscr0, ssp->mmio_base + SSCR0);
पूर्ण

अटल व्योम pxa_ssp_set_dma_params(काष्ठा ssp_device *ssp, पूर्णांक width4,
			पूर्णांक out, काष्ठा snd_dmaengine_dai_dma_data *dma)
अणु
	dma->addr_width = width4 ? DMA_SLAVE_BUSWIDTH_4_BYTES :
				   DMA_SLAVE_BUSWIDTH_2_BYTES;
	dma->maxburst = 16;
	dma->addr = ssp->phys_base + SSDR;
पूर्ण

अटल पूर्णांक pxa_ssp_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा ssp_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा ssp_device *ssp = priv->ssp;
	काष्ठा snd_dmaengine_dai_dma_data *dma;
	पूर्णांक ret = 0;

	अगर (!snd_soc_dai_active(cpu_dai)) अणु
		clk_prepare_enable(ssp->clk);
		pxa_ssp_disable(ssp);
	पूर्ण

	clk_prepare_enable(priv->extclk);

	dma = kzalloc(माप(काष्ठा snd_dmaengine_dai_dma_data), GFP_KERNEL);
	अगर (!dma)
		वापस -ENOMEM;
	dma->chan_name = substream->stream == SNDRV_PCM_STREAM_PLAYBACK ?
		"tx" : "rx";

	snd_soc_dai_set_dma_data(cpu_dai, substream, dma);

	वापस ret;
पूर्ण

अटल व्योम pxa_ssp_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा ssp_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा ssp_device *ssp = priv->ssp;

	अगर (!snd_soc_dai_active(cpu_dai)) अणु
		pxa_ssp_disable(ssp);
		clk_disable_unprepare(ssp->clk);
	पूर्ण

	clk_disable_unprepare(priv->extclk);

	kमुक्त(snd_soc_dai_get_dma_data(cpu_dai, substream));
	snd_soc_dai_set_dma_data(cpu_dai, substream, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक pxa_ssp_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ssp_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा ssp_device *ssp = priv->ssp;

	अगर (!snd_soc_component_active(component))
		clk_prepare_enable(ssp->clk);

	priv->cr0 = __raw_पढ़ोl(ssp->mmio_base + SSCR0);
	priv->cr1 = __raw_पढ़ोl(ssp->mmio_base + SSCR1);
	priv->to  = __raw_पढ़ोl(ssp->mmio_base + SSTO);
	priv->psp = __raw_पढ़ोl(ssp->mmio_base + SSPSP);

	pxa_ssp_disable(ssp);
	clk_disable_unprepare(ssp->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa_ssp_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ssp_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा ssp_device *ssp = priv->ssp;
	uपूर्णांक32_t sssr = SSSR_ROR | SSSR_TUR | SSSR_BCE;

	clk_prepare_enable(ssp->clk);

	__raw_ग_लिखोl(sssr, ssp->mmio_base + SSSR);
	__raw_ग_लिखोl(priv->cr0 & ~SSCR0_SSE, ssp->mmio_base + SSCR0);
	__raw_ग_लिखोl(priv->cr1, ssp->mmio_base + SSCR1);
	__raw_ग_लिखोl(priv->to,  ssp->mmio_base + SSTO);
	__raw_ग_लिखोl(priv->psp, ssp->mmio_base + SSPSP);

	अगर (snd_soc_component_active(component))
		pxa_ssp_enable(ssp);
	अन्यथा
		clk_disable_unprepare(ssp->clk);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा pxa_ssp_suspend	शून्य
#घोषणा pxa_ssp_resume	शून्य
#पूर्ण_अगर

/*
 * ssp_set_clkभाग - set SSP घड़ी भागider
 * @भाग: serial घड़ी rate भागider
 */
अटल व्योम pxa_ssp_set_scr(काष्ठा ssp_device *ssp, u32 भाग)
अणु
	u32 sscr0 = pxa_ssp_पढ़ो_reg(ssp, SSCR0);

	अगर (ssp->type == PXA25x_SSP) अणु
		sscr0 &= ~0x0000ff00;
		sscr0 |= ((भाग - 2)/2) << 8; /* 2..512 */
	पूर्ण अन्यथा अणु
		sscr0 &= ~0x000fff00;
		sscr0 |= (भाग - 1) << 8;     /* 1..4096 */
	पूर्ण
	pxa_ssp_ग_लिखो_reg(ssp, SSCR0, sscr0);
पूर्ण

/*
 * Set the SSP ports SYSCLK.
 */
अटल पूर्णांक pxa_ssp_set_dai_sysclk(काष्ठा snd_soc_dai *cpu_dai,
	पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा ssp_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा ssp_device *ssp = priv->ssp;

	u32 sscr0 = pxa_ssp_पढ़ो_reg(ssp, SSCR0) &
		~(SSCR0_ECS | SSCR0_NCS | SSCR0_MOD | SSCR0_ACS);

	अगर (priv->extclk) अणु
		पूर्णांक ret;

		/*
		 * For DT based boards, अगर an extclk is given, use it
		 * here and configure PXA_SSP_CLK_EXT.
		 */

		ret = clk_set_rate(priv->extclk, freq);
		अगर (ret < 0)
			वापस ret;

		clk_id = PXA_SSP_CLK_EXT;
	पूर्ण

	dev_dbg(ssp->dev,
		"pxa_ssp_set_dai_sysclk id: %d, clk_id %d, freq %u\n",
		cpu_dai->id, clk_id, freq);

	चयन (clk_id) अणु
	हाल PXA_SSP_CLK_NET_PLL:
		sscr0 |= SSCR0_MOD;
		अवरोध;
	हाल PXA_SSP_CLK_PLL:
		/* Internal PLL is fixed */
		अगर (ssp->type == PXA25x_SSP)
			priv->sysclk = 1843200;
		अन्यथा
			priv->sysclk = 13000000;
		अवरोध;
	हाल PXA_SSP_CLK_EXT:
		priv->sysclk = freq;
		sscr0 |= SSCR0_ECS;
		अवरोध;
	हाल PXA_SSP_CLK_NET:
		priv->sysclk = freq;
		sscr0 |= SSCR0_NCS | SSCR0_MOD;
		अवरोध;
	हाल PXA_SSP_CLK_AUDIO:
		priv->sysclk = 0;
		pxa_ssp_set_scr(ssp, 1);
		sscr0 |= SSCR0_ACS;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	/* The SSP घड़ी must be disabled when changing SSP घड़ी mode
	 * on PXA2xx.  On PXA3xx it must be enabled when करोing so. */
	अगर (ssp->type != PXA3xx_SSP)
		clk_disable_unprepare(ssp->clk);
	pxa_ssp_ग_लिखो_reg(ssp, SSCR0, sscr0);
	अगर (ssp->type != PXA3xx_SSP)
		clk_prepare_enable(ssp->clk);

	वापस 0;
पूर्ण

/*
 * Configure the PLL frequency pxa27x and (afaik - pxa320 only)
 */
अटल पूर्णांक pxa_ssp_set_pll(काष्ठा ssp_priv *priv, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा ssp_device *ssp = priv->ssp;
	u32 ssacd = pxa_ssp_पढ़ो_reg(ssp, SSACD) & ~0x70;

	अगर (ssp->type == PXA3xx_SSP)
		pxa_ssp_ग_लिखो_reg(ssp, SSACDD, 0);

	चयन (freq) अणु
	हाल 5622000:
		अवरोध;
	हाल 11345000:
		ssacd |= (0x1 << 4);
		अवरोध;
	हाल 12235000:
		ssacd |= (0x2 << 4);
		अवरोध;
	हाल 14857000:
		ssacd |= (0x3 << 4);
		अवरोध;
	हाल 32842000:
		ssacd |= (0x4 << 4);
		अवरोध;
	हाल 48000000:
		ssacd |= (0x5 << 4);
		अवरोध;
	हाल 0:
		/* Disable */
		अवरोध;

	शेष:
		/* PXA3xx has a घड़ी ditherer which can be used to generate
		 * a wider range of frequencies - calculate a value क्रम it.
		 */
		अगर (ssp->type == PXA3xx_SSP) अणु
			u32 val;
			u64 पंचांगp = 19968;

			पंचांगp *= 1000000;
			करो_भाग(पंचांगp, freq);
			val = पंचांगp;

			val = (val << 16) | 64;
			pxa_ssp_ग_लिखो_reg(ssp, SSACDD, val);

			ssacd |= (0x6 << 4);

			dev_dbg(ssp->dev,
				"Using SSACDD %x to supply %uHz\n",
				val, freq);
			अवरोध;
		पूर्ण

		वापस -EINVAL;
	पूर्ण

	pxa_ssp_ग_लिखो_reg(ssp, SSACD, ssacd);

	वापस 0;
पूर्ण

/*
 * Set the active slots in TDM/Network mode
 */
अटल पूर्णांक pxa_ssp_set_dai_tdm_slot(काष्ठा snd_soc_dai *cpu_dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा ssp_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा ssp_device *ssp = priv->ssp;
	u32 sscr0;

	sscr0 = pxa_ssp_पढ़ो_reg(ssp, SSCR0);
	sscr0 &= ~(SSCR0_MOD | SSCR0_SlotsPerFrm(8) | SSCR0_EDSS | SSCR0_DSS);

	/* set slot width */
	अगर (slot_width > 16)
		sscr0 |= SSCR0_EDSS | SSCR0_DataSize(slot_width - 16);
	अन्यथा
		sscr0 |= SSCR0_DataSize(slot_width);

	अगर (slots > 1) अणु
		/* enable network mode */
		sscr0 |= SSCR0_MOD;

		/* set number of active slots */
		sscr0 |= SSCR0_SlotsPerFrm(slots);

		/* set active slot mask */
		pxa_ssp_ग_लिखो_reg(ssp, SSTSA, tx_mask);
		pxa_ssp_ग_लिखो_reg(ssp, SSRSA, rx_mask);
	पूर्ण
	pxa_ssp_ग_लिखो_reg(ssp, SSCR0, sscr0);

	वापस 0;
पूर्ण

/*
 * Tristate the SSP DAI lines
 */
अटल पूर्णांक pxa_ssp_set_dai_tristate(काष्ठा snd_soc_dai *cpu_dai,
	पूर्णांक tristate)
अणु
	काष्ठा ssp_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा ssp_device *ssp = priv->ssp;
	u32 sscr1;

	sscr1 = pxa_ssp_पढ़ो_reg(ssp, SSCR1);
	अगर (tristate)
		sscr1 &= ~SSCR1_TTE;
	अन्यथा
		sscr1 |= SSCR1_TTE;
	pxa_ssp_ग_लिखो_reg(ssp, SSCR1, sscr1);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa_ssp_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai,
			       अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा ssp_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
	हाल SND_SOC_DAIFMT_CBM_CFS:
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
	हाल SND_SOC_DAIFMT_NB_IF:
	हाल SND_SOC_DAIFMT_IB_IF:
	हाल SND_SOC_DAIFMT_IB_NF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Settings will be applied in hw_params() */
	priv->dai_fmt = fmt;

	वापस 0;
पूर्ण

/*
 * Set up the SSP DAI क्रमmat.
 * The SSP Port must be inactive beक्रमe calling this function as the
 * physical पूर्णांकerface क्रमmat is changed.
 */
अटल पूर्णांक pxa_ssp_configure_dai_fmt(काष्ठा ssp_priv *priv)
अणु
	काष्ठा ssp_device *ssp = priv->ssp;
	u32 sscr0, sscr1, sspsp, scfr;

	/* check अगर we need to change anything at all */
	अगर (priv->configured_dai_fmt == priv->dai_fmt)
		वापस 0;

	/* reset port settings */
	sscr0 = pxa_ssp_पढ़ो_reg(ssp, SSCR0) &
		~(SSCR0_PSP | SSCR0_MOD);
	sscr1 = pxa_ssp_पढ़ो_reg(ssp, SSCR1) &
		~(SSCR1_SCLKसूची | SSCR1_SFRMसूची | SSCR1_SCFR |
		  SSCR1_RWOT | SSCR1_TRAIL | SSCR1_TFT | SSCR1_RFT);
	sspsp = pxa_ssp_पढ़ो_reg(ssp, SSPSP) &
		~(SSPSP_SFRMP | SSPSP_SCMODE(3));

	sscr1 |= SSCR1_RxTresh(8) | SSCR1_TxTresh(7);

	चयन (priv->dai_fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		sscr1 |= SSCR1_SCLKसूची | SSCR1_SFRMसूची | SSCR1_SCFR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		sscr1 |= SSCR1_SCLKसूची | SSCR1_SCFR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (priv->dai_fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		sspsp |= SSPSP_SFRMP;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		sspsp |= SSPSP_SCMODE(2);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		sspsp |= SSPSP_SCMODE(2) | SSPSP_SFRMP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (priv->dai_fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		sscr0 |= SSCR0_PSP;
		sscr1 |= SSCR1_RWOT | SSCR1_TRAIL;
		/* See hw_params() */
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A:
		sspsp |= SSPSP_FSRT;
		fallthrough;
	हाल SND_SOC_DAIFMT_DSP_B:
		sscr0 |= SSCR0_MOD | SSCR0_PSP;
		sscr1 |= SSCR1_TRAIL | SSCR1_RWOT;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	pxa_ssp_ग_लिखो_reg(ssp, SSCR0, sscr0);
	pxa_ssp_ग_लिखो_reg(ssp, SSCR1, sscr1);
	pxa_ssp_ग_लिखो_reg(ssp, SSPSP, sspsp);

	चयन (priv->dai_fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
	हाल SND_SOC_DAIFMT_CBM_CFS:
		scfr = pxa_ssp_पढ़ो_reg(ssp, SSCR1) | SSCR1_SCFR;
		pxa_ssp_ग_लिखो_reg(ssp, SSCR1, scfr);

		जबतक (pxa_ssp_पढ़ो_reg(ssp, SSSR) & SSSR_BSY)
			cpu_relax();
		अवरोध;
	पूर्ण

	dump_रेजिस्टरs(ssp);

	/* Since we are configuring the timings क्रम the क्रमmat by hand
	 * we have to defer some things until hw_params() where we
	 * know parameters like the sample size.
	 */
	priv->configured_dai_fmt = priv->dai_fmt;

	वापस 0;
पूर्ण

काष्ठा pxa_ssp_घड़ी_mode अणु
	पूर्णांक rate;
	पूर्णांक pll;
	u8 acds;
	u8 scdb;
पूर्ण;

अटल स्थिर काष्ठा pxa_ssp_घड़ी_mode pxa_ssp_घड़ी_modes[] = अणु
	अणु .rate =  8000, .pll = 32842000, .acds = SSACD_ACDS_32, .scdb = SSACD_SCDB_4X पूर्ण,
	अणु .rate = 11025, .pll =  5622000, .acds = SSACD_ACDS_4,  .scdb = SSACD_SCDB_4X पूर्ण,
	अणु .rate = 16000, .pll = 32842000, .acds = SSACD_ACDS_16, .scdb = SSACD_SCDB_4X पूर्ण,
	अणु .rate = 22050, .pll =  5622000, .acds = SSACD_ACDS_2,  .scdb = SSACD_SCDB_4X पूर्ण,
	अणु .rate = 44100, .pll = 11345000, .acds = SSACD_ACDS_2,  .scdb = SSACD_SCDB_4X पूर्ण,
	अणु .rate = 48000, .pll = 12235000, .acds = SSACD_ACDS_2,  .scdb = SSACD_SCDB_4X पूर्ण,
	अणु .rate = 96000, .pll = 12235000, .acds = SSACD_ACDS_4,  .scdb = SSACD_SCDB_1X पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Set the SSP audio DMA parameters and sample size.
 * Can be called multiple बार by oss emulation.
 */
अटल पूर्णांक pxa_ssp_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा ssp_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा ssp_device *ssp = priv->ssp;
	पूर्णांक chn = params_channels(params);
	u32 sscr0, sspsp;
	पूर्णांक width = snd_pcm_क्रमmat_physical_width(params_क्रमmat(params));
	पूर्णांक ttsa = pxa_ssp_पढ़ो_reg(ssp, SSTSA) & 0xf;
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	पूर्णांक rate = params_rate(params);
	पूर्णांक bclk = rate * chn * (width / 8);
	पूर्णांक ret;

	dma_data = snd_soc_dai_get_dma_data(cpu_dai, substream);

	/* Network mode with one active slot (ttsa == 1) can be used
	 * to क्रमce 16-bit frame width on the wire (क्रम S16_LE), even
	 * with two channels. Use 16-bit DMA transfers क्रम this हाल.
	 */
	pxa_ssp_set_dma_params(ssp,
		((chn == 2) && (ttsa != 1)) || (width == 32),
		substream->stream == SNDRV_PCM_STREAM_PLAYBACK, dma_data);

	/* we can only change the settings अगर the port is not in use */
	अगर (pxa_ssp_पढ़ो_reg(ssp, SSCR0) & SSCR0_SSE)
		वापस 0;

	ret = pxa_ssp_configure_dai_fmt(priv);
	अगर (ret < 0)
		वापस ret;

	/* clear selected SSP bits */
	sscr0 = pxa_ssp_पढ़ो_reg(ssp, SSCR0) & ~(SSCR0_DSS | SSCR0_EDSS);

	/* bit size */
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		अगर (ssp->type == PXA3xx_SSP)
			sscr0 |= SSCR0_FPCKE;
		sscr0 |= SSCR0_DataSize(16);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		sscr0 |= (SSCR0_EDSS | SSCR0_DataSize(8));
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		sscr0 |= (SSCR0_EDSS | SSCR0_DataSize(16));
		अवरोध;
	पूर्ण
	pxa_ssp_ग_लिखो_reg(ssp, SSCR0, sscr0);

	अगर (sscr0 & SSCR0_ACS) अणु
		ret = pxa_ssp_set_pll(priv, bclk);

		/*
		 * If we were able to generate the bclk directly,
		 * all is fine. Otherwise, look up the बंदst rate
		 * from the table and also set the भागiders.
		 */

		अगर (ret < 0) अणु
			स्थिर काष्ठा pxa_ssp_घड़ी_mode *m;
			पूर्णांक ssacd, acds;

			क्रम (m = pxa_ssp_घड़ी_modes; m->rate; m++) अणु
				अगर (m->rate == rate)
					अवरोध;
			पूर्ण

			अगर (!m->rate)
				वापस -EINVAL;

			acds = m->acds;

			/* The values in the table are क्रम 16 bits */
			अगर (width == 32)
				acds--;

			ret = pxa_ssp_set_pll(priv, bclk);
			अगर (ret < 0)
				वापस ret;

			ssacd = pxa_ssp_पढ़ो_reg(ssp, SSACD);
			ssacd &= ~(SSACD_ACDS(7) | SSACD_SCDB_1X);
			ssacd |= SSACD_ACDS(m->acds);
			ssacd |= m->scdb;
			pxa_ssp_ग_लिखो_reg(ssp, SSACD, ssacd);
		पूर्ण
	पूर्ण अन्यथा अगर (sscr0 & SSCR0_ECS) अणु
		/*
		 * For setups with बाह्यal घड़ीing, the PLL and its भागiers
		 * are not active. Instead, the SCR bits in SSCR0 can be used
		 * to भागide the घड़ी.
		 */
		pxa_ssp_set_scr(ssp, bclk / rate);
	पूर्ण

	चयन (priv->dai_fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	       sspsp = pxa_ssp_पढ़ो_reg(ssp, SSPSP);

		अगर (((priv->sysclk / bclk) == 64) && (width == 16)) अणु
			/* This is a special हाल where the bitclk is 64fs
			 * and we're not dealing with 2*32 bits of audio
			 * samples.
			 *
			 * The SSP values used क्रम that are all found out by
			 * trying and failing a lot; some of the रेजिस्टरs
			 * needed क्रम that mode are only available on PXA3xx.
			 */
			अगर (ssp->type != PXA3xx_SSP)
				वापस -EINVAL;

			sspsp |= SSPSP_SFRMWDTH(width * 2);
			sspsp |= SSPSP_SFRMDLY(width * 4);
			sspsp |= SSPSP_EDMYSTOP(3);
			sspsp |= SSPSP_DMYSTOP(3);
			sspsp |= SSPSP_DMYSTRT(1);
		पूर्ण अन्यथा अणु
			/* The frame width is the width the LRCLK is
			 * निश्चितed क्रम; the delay is expressed in
			 * half cycle units.  We need the extra cycle
			 * because the data starts घड़ीing out one BCLK
			 * after LRCLK changes polarity.
			 */
			sspsp |= SSPSP_SFRMWDTH(width + 1);
			sspsp |= SSPSP_SFRMDLY((width + 1) * 2);
			sspsp |= SSPSP_DMYSTRT(1);
		पूर्ण

		pxa_ssp_ग_लिखो_reg(ssp, SSPSP, sspsp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* When we use a network mode, we always require TDM slots
	 * - complain loudly and fail अगर they've not been set up yet.
	 */
	अगर ((sscr0 & SSCR0_MOD) && !ttsa) अणु
		dev_err(ssp->dev, "No TDM timeslot configured\n");
		वापस -EINVAL;
	पूर्ण

	dump_रेजिस्टरs(ssp);

	वापस 0;
पूर्ण

अटल व्योम pxa_ssp_set_running_bit(काष्ठा snd_pcm_substream *substream,
				    काष्ठा ssp_device *ssp, पूर्णांक value)
अणु
	uपूर्णांक32_t sscr0 = pxa_ssp_पढ़ो_reg(ssp, SSCR0);
	uपूर्णांक32_t sscr1 = pxa_ssp_पढ़ो_reg(ssp, SSCR1);
	uपूर्णांक32_t sspsp = pxa_ssp_पढ़ो_reg(ssp, SSPSP);
	uपूर्णांक32_t sssr = pxa_ssp_पढ़ो_reg(ssp, SSSR);

	अगर (value && (sscr0 & SSCR0_SSE))
		pxa_ssp_ग_लिखो_reg(ssp, SSCR0, sscr0 & ~SSCR0_SSE);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (value)
			sscr1 |= SSCR1_TSRE;
		अन्यथा
			sscr1 &= ~SSCR1_TSRE;
	पूर्ण अन्यथा अणु
		अगर (value)
			sscr1 |= SSCR1_RSRE;
		अन्यथा
			sscr1 &= ~SSCR1_RSRE;
	पूर्ण

	pxa_ssp_ग_लिखो_reg(ssp, SSCR1, sscr1);

	अगर (value) अणु
		pxa_ssp_ग_लिखो_reg(ssp, SSSR, sssr);
		pxa_ssp_ग_लिखो_reg(ssp, SSPSP, sspsp);
		pxa_ssp_ग_लिखो_reg(ssp, SSCR0, sscr0 | SSCR0_SSE);
	पूर्ण
पूर्ण

अटल पूर्णांक pxa_ssp_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			   काष्ठा snd_soc_dai *cpu_dai)
अणु
	पूर्णांक ret = 0;
	काष्ठा ssp_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा ssp_device *ssp = priv->ssp;
	पूर्णांक val;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_RESUME:
		pxa_ssp_enable(ssp);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		pxa_ssp_set_running_bit(substream, ssp, 1);
		val = pxa_ssp_पढ़ो_reg(ssp, SSSR);
		pxa_ssp_ग_लिखो_reg(ssp, SSSR, val);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_START:
		pxa_ssp_set_running_bit(substream, ssp, 1);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		pxa_ssp_set_running_bit(substream, ssp, 0);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		pxa_ssp_disable(ssp);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		pxa_ssp_set_running_bit(substream, ssp, 0);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	dump_रेजिस्टरs(ssp);

	वापस ret;
पूर्ण

अटल पूर्णांक pxa_ssp_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा device *dev = dai->dev;
	काष्ठा ssp_priv *priv;
	पूर्णांक ret;

	priv = kzalloc(माप(काष्ठा ssp_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (dev->of_node) अणु
		काष्ठा device_node *ssp_handle;

		ssp_handle = of_parse_phandle(dev->of_node, "port", 0);
		अगर (!ssp_handle) अणु
			dev_err(dev, "unable to get 'port' phandle\n");
			ret = -ENODEV;
			जाओ err_priv;
		पूर्ण

		priv->ssp = pxa_ssp_request_of(ssp_handle, "SoC audio");
		अगर (priv->ssp == शून्य) अणु
			ret = -ENODEV;
			जाओ err_priv;
		पूर्ण

		priv->extclk = devm_clk_get(dev, "extclk");
		अगर (IS_ERR(priv->extclk)) अणु
			ret = PTR_ERR(priv->extclk);
			अगर (ret == -EPROBE_DEFER)
				वापस ret;

			priv->extclk = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->ssp = pxa_ssp_request(dai->id + 1, "SoC audio");
		अगर (priv->ssp == शून्य) अणु
			ret = -ENODEV;
			जाओ err_priv;
		पूर्ण
	पूर्ण

	priv->dai_fmt = (अचिन्हित पूर्णांक) -1;
	snd_soc_dai_set_drvdata(dai, priv);

	वापस 0;

err_priv:
	kमुक्त(priv);
	वापस ret;
पूर्ण

अटल पूर्णांक pxa_ssp_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ssp_priv *priv = snd_soc_dai_get_drvdata(dai);

	pxa_ssp_मुक्त(priv->ssp);
	kमुक्त(priv);
	वापस 0;
पूर्ण

#घोषणा PXA_SSP_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
			  SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 |	\
			  SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |	\
			  SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_64000 |	\
			  SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000)

#घोषणा PXA_SSP_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops pxa_ssp_dai_ops = अणु
	.startup	= pxa_ssp_startup,
	.shutकरोwn	= pxa_ssp_shutकरोwn,
	.trigger	= pxa_ssp_trigger,
	.hw_params	= pxa_ssp_hw_params,
	.set_sysclk	= pxa_ssp_set_dai_sysclk,
	.set_fmt	= pxa_ssp_set_dai_fmt,
	.set_tdm_slot	= pxa_ssp_set_dai_tdm_slot,
	.set_tristate	= pxa_ssp_set_dai_tristate,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver pxa_ssp_dai = अणु
		.probe = pxa_ssp_probe,
		.हटाओ = pxa_ssp_हटाओ,
		.playback = अणु
			.channels_min = 1,
			.channels_max = 8,
			.rates = PXA_SSP_RATES,
			.क्रमmats = PXA_SSP_FORMATS,
		पूर्ण,
		.capture = अणु
			 .channels_min = 1,
			 .channels_max = 8,
			.rates = PXA_SSP_RATES,
			.क्रमmats = PXA_SSP_FORMATS,
		 पूर्ण,
		.ops = &pxa_ssp_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver pxa_ssp_component = अणु
	.name		= "pxa-ssp",
	.pcm_स्थिरruct	= pxa2xx_soc_pcm_new,
	.pcm_deकाष्ठा	= pxa2xx_soc_pcm_मुक्त,
	.खोलो		= pxa2xx_soc_pcm_खोलो,
	.बंद		= pxa2xx_soc_pcm_बंद,
	.hw_params	= pxa2xx_soc_pcm_hw_params,
	.hw_मुक्त	= pxa2xx_soc_pcm_hw_मुक्त,
	.prepare	= pxa2xx_soc_pcm_prepare,
	.trigger	= pxa2xx_soc_pcm_trigger,
	.poपूर्णांकer	= pxa2xx_soc_pcm_poपूर्णांकer,
	.mmap		= pxa2xx_soc_pcm_mmap,
	.suspend	= pxa_ssp_suspend,
	.resume		= pxa_ssp_resume,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pxa_ssp_of_ids[] = अणु
	अणु .compatible = "mrvl,pxa-ssp-dai" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pxa_ssp_of_ids);
#पूर्ण_अगर

अटल पूर्णांक asoc_ssp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &pxa_ssp_component,
					       &pxa_ssp_dai, 1);
पूर्ण

अटल काष्ठा platक्रमm_driver asoc_ssp_driver = अणु
	.driver = अणु
		.name = "pxa-ssp-dai",
		.of_match_table = of_match_ptr(pxa_ssp_of_ids),
	पूर्ण,

	.probe = asoc_ssp_probe,
पूर्ण;

module_platक्रमm_driver(asoc_ssp_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("PXA SSP/PCM SoC Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa-ssp-dai");
