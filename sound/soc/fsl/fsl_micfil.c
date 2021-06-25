<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright 2018 NXP

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kobject.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/core.h>

#समावेश "fsl_micfil.h"
#समावेश "imx-pcm.h"

#घोषणा FSL_MICFIL_RATES		SNDRV_PCM_RATE_8000_48000
#घोषणा FSL_MICFIL_FORMATS		(SNDRV_PCM_FMTBIT_S16_LE)

काष्ठा fsl_micfil अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा fsl_micfil_soc_data *soc;
	काष्ठा clk *busclk;
	काष्ठा clk *mclk;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_rx;
	अचिन्हित पूर्णांक dataline;
	अक्षर name[32];
	पूर्णांक irq[MICFIL_IRQ_LINES];
	अचिन्हित पूर्णांक mclk_streams;
	पूर्णांक quality;	/*QUALITY 2-0 bits */
	bool slave_mode;
	पूर्णांक channel_gain[8];
पूर्ण;

काष्ठा fsl_micfil_soc_data अणु
	अचिन्हित पूर्णांक fअगरos;
	अचिन्हित पूर्णांक fअगरo_depth;
	अचिन्हित पूर्णांक dataline;
	bool imx;
पूर्ण;

अटल काष्ठा fsl_micfil_soc_data fsl_micfil_imx8mm = अणु
	.imx = true,
	.fअगरos = 8,
	.fअगरo_depth = 8,
	.dataline =  0xf,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_micfil_dt_ids[] = अणु
	अणु .compatible = "fsl,imx8mm-micfil", .data = &fsl_micfil_imx8mm पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_micfil_dt_ids);

/* Table 5. Quality Modes
 * Medium	0 0 0
 * High		0 0 1
 * Very Low 2	1 0 0
 * Very Low 1	1 0 1
 * Very Low 0	1 1 0
 * Low		1 1 1
 */
अटल स्थिर अक्षर * स्थिर micfil_quality_select_texts[] = अणु
	"Medium", "High",
	"N/A", "N/A",
	"VLow2", "VLow1",
	"VLow0", "Low",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत fsl_micfil_quality_क्रमागत =
	SOC_ENUM_SINGLE(REG_MICFIL_CTRL2,
			MICFIL_CTRL2_QSEL_SHIFT,
			ARRAY_SIZE(micfil_quality_select_texts),
			micfil_quality_select_texts);

अटल DECLARE_TLV_DB_SCALE(gain_tlv, 0, 100, 0);

अटल स्थिर काष्ठा snd_kcontrol_new fsl_micfil_snd_controls[] = अणु
	SOC_SINGLE_SX_TLV("CH0 Volume", REG_MICFIL_OUT_CTRL,
			  MICFIL_OUTGAIN_CHX_SHIFT(0), 0xF, 0x7, gain_tlv),
	SOC_SINGLE_SX_TLV("CH1 Volume", REG_MICFIL_OUT_CTRL,
			  MICFIL_OUTGAIN_CHX_SHIFT(1), 0xF, 0x7, gain_tlv),
	SOC_SINGLE_SX_TLV("CH2 Volume", REG_MICFIL_OUT_CTRL,
			  MICFIL_OUTGAIN_CHX_SHIFT(2), 0xF, 0x7, gain_tlv),
	SOC_SINGLE_SX_TLV("CH3 Volume", REG_MICFIL_OUT_CTRL,
			  MICFIL_OUTGAIN_CHX_SHIFT(3), 0xF, 0x7, gain_tlv),
	SOC_SINGLE_SX_TLV("CH4 Volume", REG_MICFIL_OUT_CTRL,
			  MICFIL_OUTGAIN_CHX_SHIFT(4), 0xF, 0x7, gain_tlv),
	SOC_SINGLE_SX_TLV("CH5 Volume", REG_MICFIL_OUT_CTRL,
			  MICFIL_OUTGAIN_CHX_SHIFT(5), 0xF, 0x7, gain_tlv),
	SOC_SINGLE_SX_TLV("CH6 Volume", REG_MICFIL_OUT_CTRL,
			  MICFIL_OUTGAIN_CHX_SHIFT(6), 0xF, 0x7, gain_tlv),
	SOC_SINGLE_SX_TLV("CH7 Volume", REG_MICFIL_OUT_CTRL,
			  MICFIL_OUTGAIN_CHX_SHIFT(7), 0xF, 0x7, gain_tlv),
	SOC_ENUM_EXT("MICFIL Quality Select",
		     fsl_micfil_quality_क्रमागत,
		     snd_soc_get_क्रमागत_द्विगुन, snd_soc_put_क्रमागत_द्विगुन),
पूर्ण;

अटल अंतरभूत पूर्णांक get_pdm_clk(काष्ठा fsl_micfil *micfil,
			      अचिन्हित पूर्णांक rate)
अणु
	u32 ctrl2_reg;
	पूर्णांक qsel, osr;
	पूर्णांक bclk;

	regmap_पढ़ो(micfil->regmap, REG_MICFIL_CTRL2, &ctrl2_reg);
	osr = 16 - ((ctrl2_reg & MICFIL_CTRL2_CICOSR_MASK)
		    >> MICFIL_CTRL2_CICOSR_SHIFT);

	regmap_पढ़ो(micfil->regmap, REG_MICFIL_CTRL2, &ctrl2_reg);
	qsel = ctrl2_reg & MICFIL_CTRL2_QSEL_MASK;

	चयन (qsel) अणु
	हाल MICFIL_HIGH_QUALITY:
		bclk = rate * 8 * osr / 2; /* kfactor = 0.5 */
		अवरोध;
	हाल MICFIL_MEDIUM_QUALITY:
	हाल MICFIL_VLOW0_QUALITY:
		bclk = rate * 4 * osr * 1; /* kfactor = 1 */
		अवरोध;
	हाल MICFIL_LOW_QUALITY:
	हाल MICFIL_VLOW1_QUALITY:
		bclk = rate * 2 * osr * 2; /* kfactor = 2 */
		अवरोध;
	हाल MICFIL_VLOW2_QUALITY:
		bclk = rate * osr * 4; /* kfactor = 4 */
		अवरोध;
	शेष:
		dev_err(&micfil->pdev->dev,
			"Please make sure you select a valid quality.\n");
		bclk = -1;
		अवरोध;
	पूर्ण

	वापस bclk;
पूर्ण

अटल अंतरभूत पूर्णांक get_clk_भाग(काष्ठा fsl_micfil *micfil,
			      अचिन्हित पूर्णांक rate)
अणु
	u32 ctrl2_reg;
	दीर्घ mclk_rate;
	पूर्णांक clk_भाग;

	regmap_पढ़ो(micfil->regmap, REG_MICFIL_CTRL2, &ctrl2_reg);

	mclk_rate = clk_get_rate(micfil->mclk);

	clk_भाग = mclk_rate / (get_pdm_clk(micfil, rate) * 2);

	वापस clk_भाग;
पूर्ण

/* The SRES is a self-negated bit which provides the CPU with the
 * capability to initialize the PDM Interface module through the
 * slave-bus पूर्णांकerface. This bit always पढ़ोs as zero, and this
 * bit is only effective when MDIS is cleared
 */
अटल पूर्णांक fsl_micfil_reset(काष्ठा device *dev)
अणु
	काष्ठा fsl_micfil *micfil = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(micfil->regmap,
				 REG_MICFIL_CTRL1,
				 MICFIL_CTRL1_MDIS_MASK,
				 0);
	अगर (ret) अणु
		dev_err(dev, "failed to clear MDIS bit %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(micfil->regmap,
				 REG_MICFIL_CTRL1,
				 MICFIL_CTRL1_SRES_MASK,
				 MICFIL_CTRL1_SRES);
	अगर (ret) अणु
		dev_err(dev, "failed to reset MICFIL: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_micfil_set_mclk_rate(काष्ठा fsl_micfil *micfil,
				    अचिन्हित पूर्णांक freq)
अणु
	काष्ठा device *dev = &micfil->pdev->dev;
	पूर्णांक ret;

	clk_disable_unprepare(micfil->mclk);

	ret = clk_set_rate(micfil->mclk, freq * 1024);
	अगर (ret)
		dev_warn(dev, "failed to set rate (%u): %d\n",
			 freq * 1024, ret);

	clk_prepare_enable(micfil->mclk);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_micfil_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_micfil *micfil = snd_soc_dai_get_drvdata(dai);

	अगर (!micfil) अणु
		dev_err(dai->dev, "micfil dai priv_data not set\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_micfil_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_micfil *micfil = snd_soc_dai_get_drvdata(dai);
	काष्ठा device *dev = &micfil->pdev->dev;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = fsl_micfil_reset(dev);
		अगर (ret) अणु
			dev_err(dev, "failed to soft reset\n");
			वापस ret;
		पूर्ण

		/* DMA Interrupt Selection - DISEL bits
		 * 00 - DMA and IRQ disabled
		 * 01 - DMA req enabled
		 * 10 - IRQ enabled
		 * 11 - reserved
		 */
		ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL1,
					 MICFIL_CTRL1_DISEL_MASK,
					 (1 << MICFIL_CTRL1_DISEL_SHIFT));
		अगर (ret) अणु
			dev_err(dev, "failed to update DISEL bits\n");
			वापस ret;
		पूर्ण

		/* Enable the module */
		ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL1,
					 MICFIL_CTRL1_PDMIEN_MASK,
					 MICFIL_CTRL1_PDMIEN);
		अगर (ret) अणु
			dev_err(dev, "failed to enable the module\n");
			वापस ret;
		पूर्ण

		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		/* Disable the module */
		ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL1,
					 MICFIL_CTRL1_PDMIEN_MASK,
					 0);
		अगर (ret) अणु
			dev_err(dev, "failed to enable the module\n");
			वापस ret;
		पूर्ण

		ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL1,
					 MICFIL_CTRL1_DISEL_MASK,
					 (0 << MICFIL_CTRL1_DISEL_SHIFT));
		अगर (ret) अणु
			dev_err(dev, "failed to update DISEL bits\n");
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_set_घड़ी_params(काष्ठा device *dev, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा fsl_micfil *micfil = dev_get_drvdata(dev);
	पूर्णांक clk_भाग;
	पूर्णांक ret;

	ret = fsl_micfil_set_mclk_rate(micfil, rate);
	अगर (ret < 0)
		dev_err(dev, "failed to set mclk[%lu] to rate %u\n",
			clk_get_rate(micfil->mclk), rate);

	/* set CICOSR */
	ret |= regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL2,
				 MICFIL_CTRL2_CICOSR_MASK,
				 MICFIL_CTRL2_OSR_DEFAULT);
	अगर (ret)
		dev_err(dev, "failed to set CICOSR in reg 0x%X\n",
			REG_MICFIL_CTRL2);

	/* set CLK_DIV */
	clk_भाग = get_clk_भाग(micfil, rate);
	अगर (clk_भाग < 0)
		ret = -EINVAL;

	ret |= regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL2,
				 MICFIL_CTRL2_CLKDIV_MASK, clk_भाग);
	अगर (ret)
		dev_err(dev, "failed to set CLKDIV in reg 0x%X\n",
			REG_MICFIL_CTRL2);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_micfil_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_micfil *micfil = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक rate = params_rate(params);
	काष्ठा device *dev = &micfil->pdev->dev;
	पूर्णांक ret;

	/* 1. Disable the module */
	ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL1,
				 MICFIL_CTRL1_PDMIEN_MASK, 0);
	अगर (ret) अणु
		dev_err(dev, "failed to disable the module\n");
		वापस ret;
	पूर्ण

	/* enable channels */
	ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL1,
				 0xFF, ((1 << channels) - 1));
	अगर (ret) अणु
		dev_err(dev, "failed to enable channels %d, reg 0x%X\n", ret,
			REG_MICFIL_CTRL1);
		वापस ret;
	पूर्ण

	ret = fsl_set_घड़ी_params(dev, rate);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set clock parameters [%d]\n", ret);
		वापस ret;
	पूर्ण

	micfil->dma_params_rx.maxburst = channels * MICFIL_DMA_MAXBURST_RX;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_micfil_set_dai_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				     अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा fsl_micfil *micfil = snd_soc_dai_get_drvdata(dai);
	काष्ठा device *dev = &micfil->pdev->dev;

	पूर्णांक ret;

	अगर (!freq)
		वापस 0;

	ret = fsl_micfil_set_mclk_rate(micfil, freq);
	अगर (ret < 0)
		dev_err(dev, "failed to set mclk[%lu] to rate %u\n",
			clk_get_rate(micfil->mclk), freq);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops fsl_micfil_dai_ops = अणु
	.startup = fsl_micfil_startup,
	.trigger = fsl_micfil_trigger,
	.hw_params = fsl_micfil_hw_params,
	.set_sysclk = fsl_micfil_set_dai_sysclk,
पूर्ण;

अटल पूर्णांक fsl_micfil_dai_probe(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा fsl_micfil *micfil = dev_get_drvdata(cpu_dai->dev);
	काष्ठा device *dev = cpu_dai->dev;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

	/* set qsel to medium */
	ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL2,
				 MICFIL_CTRL2_QSEL_MASK, MICFIL_MEDIUM_QUALITY);
	अगर (ret) अणु
		dev_err(dev, "failed to set quality mode bits, reg 0x%X\n",
			REG_MICFIL_CTRL2);
		वापस ret;
	पूर्ण

	/* set शेष gain to max_gain */
	regmap_ग_लिखो(micfil->regmap, REG_MICFIL_OUT_CTRL, 0x77777777);
	क्रम (i = 0; i < 8; i++)
		micfil->channel_gain[i] = 0xF;

	snd_soc_dai_init_dma_data(cpu_dai, शून्य,
				  &micfil->dma_params_rx);

	/* FIFO Watermark Control - FIFOWMK*/
	val = MICFIL_FIFO_CTRL_FIFOWMK(micfil->soc->fअगरo_depth) - 1;
	ret = regmap_update_bits(micfil->regmap, REG_MICFIL_FIFO_CTRL,
				 MICFIL_FIFO_CTRL_FIFOWMK_MASK,
				 val);
	अगर (ret) अणु
		dev_err(dev, "failed to set FIFOWMK\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver fsl_micfil_dai = अणु
	.probe = fsl_micfil_dai_probe,
	.capture = अणु
		.stream_name = "CPU-Capture",
		.channels_min = 1,
		.channels_max = 8,
		.rates = FSL_MICFIL_RATES,
		.क्रमmats = FSL_MICFIL_FORMATS,
	पूर्ण,
	.ops = &fsl_micfil_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver fsl_micfil_component = अणु
	.name		= "fsl-micfil-dai",
	.controls       = fsl_micfil_snd_controls,
	.num_controls   = ARRAY_SIZE(fsl_micfil_snd_controls),

पूर्ण;

/* REGMAP */
अटल स्थिर काष्ठा reg_शेष fsl_micfil_reg_शेषs[] = अणु
	अणुREG_MICFIL_CTRL1,		0x00000000पूर्ण,
	अणुREG_MICFIL_CTRL2,		0x00000000पूर्ण,
	अणुREG_MICFIL_STAT,		0x00000000पूर्ण,
	अणुREG_MICFIL_FIFO_CTRL,		0x00000007पूर्ण,
	अणुREG_MICFIL_FIFO_STAT,		0x00000000पूर्ण,
	अणुREG_MICFIL_DATACH0,		0x00000000पूर्ण,
	अणुREG_MICFIL_DATACH1,		0x00000000पूर्ण,
	अणुREG_MICFIL_DATACH2,		0x00000000पूर्ण,
	अणुREG_MICFIL_DATACH3,		0x00000000पूर्ण,
	अणुREG_MICFIL_DATACH4,		0x00000000पूर्ण,
	अणुREG_MICFIL_DATACH5,		0x00000000पूर्ण,
	अणुREG_MICFIL_DATACH6,		0x00000000पूर्ण,
	अणुREG_MICFIL_DATACH7,		0x00000000पूर्ण,
	अणुREG_MICFIL_DC_CTRL,		0x00000000पूर्ण,
	अणुREG_MICFIL_OUT_CTRL,		0x00000000पूर्ण,
	अणुREG_MICFIL_OUT_STAT,		0x00000000पूर्ण,
	अणुREG_MICFIL_VAD0_CTRL1,		0x00000000पूर्ण,
	अणुREG_MICFIL_VAD0_CTRL2,		0x000A0000पूर्ण,
	अणुREG_MICFIL_VAD0_STAT,		0x00000000पूर्ण,
	अणुREG_MICFIL_VAD0_SCONFIG,	0x00000000पूर्ण,
	अणुREG_MICFIL_VAD0_NCONFIG,	0x80000000पूर्ण,
	अणुREG_MICFIL_VAD0_NDATA,		0x00000000पूर्ण,
	अणुREG_MICFIL_VAD0_ZCD,		0x00000004पूर्ण,
पूर्ण;

अटल bool fsl_micfil_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_MICFIL_CTRL1:
	हाल REG_MICFIL_CTRL2:
	हाल REG_MICFIL_STAT:
	हाल REG_MICFIL_FIFO_CTRL:
	हाल REG_MICFIL_FIFO_STAT:
	हाल REG_MICFIL_DATACH0:
	हाल REG_MICFIL_DATACH1:
	हाल REG_MICFIL_DATACH2:
	हाल REG_MICFIL_DATACH3:
	हाल REG_MICFIL_DATACH4:
	हाल REG_MICFIL_DATACH5:
	हाल REG_MICFIL_DATACH6:
	हाल REG_MICFIL_DATACH7:
	हाल REG_MICFIL_DC_CTRL:
	हाल REG_MICFIL_OUT_CTRL:
	हाल REG_MICFIL_OUT_STAT:
	हाल REG_MICFIL_VAD0_CTRL1:
	हाल REG_MICFIL_VAD0_CTRL2:
	हाल REG_MICFIL_VAD0_STAT:
	हाल REG_MICFIL_VAD0_SCONFIG:
	हाल REG_MICFIL_VAD0_NCONFIG:
	हाल REG_MICFIL_VAD0_NDATA:
	हाल REG_MICFIL_VAD0_ZCD:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_micfil_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_MICFIL_CTRL1:
	हाल REG_MICFIL_CTRL2:
	हाल REG_MICFIL_STAT:		/* Write 1 to Clear */
	हाल REG_MICFIL_FIFO_CTRL:
	हाल REG_MICFIL_FIFO_STAT:	/* Write 1 to Clear */
	हाल REG_MICFIL_DC_CTRL:
	हाल REG_MICFIL_OUT_CTRL:
	हाल REG_MICFIL_OUT_STAT:	/* Write 1 to Clear */
	हाल REG_MICFIL_VAD0_CTRL1:
	हाल REG_MICFIL_VAD0_CTRL2:
	हाल REG_MICFIL_VAD0_STAT:	/* Write 1 to Clear */
	हाल REG_MICFIL_VAD0_SCONFIG:
	हाल REG_MICFIL_VAD0_NCONFIG:
	हाल REG_MICFIL_VAD0_ZCD:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_micfil_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_MICFIL_STAT:
	हाल REG_MICFIL_DATACH0:
	हाल REG_MICFIL_DATACH1:
	हाल REG_MICFIL_DATACH2:
	हाल REG_MICFIL_DATACH3:
	हाल REG_MICFIL_DATACH4:
	हाल REG_MICFIL_DATACH5:
	हाल REG_MICFIL_DATACH6:
	हाल REG_MICFIL_DATACH7:
	हाल REG_MICFIL_VAD0_STAT:
	हाल REG_MICFIL_VAD0_NDATA:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config fsl_micfil_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,

	.max_रेजिस्टर = REG_MICFIL_VAD0_ZCD,
	.reg_शेषs = fsl_micfil_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(fsl_micfil_reg_शेषs),
	.पढ़ोable_reg = fsl_micfil_पढ़ोable_reg,
	.अस्थिर_reg = fsl_micfil_अस्थिर_reg,
	.ग_लिखोable_reg = fsl_micfil_ग_लिखोable_reg,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/* END OF REGMAP */

अटल irqवापस_t micfil_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा fsl_micfil *micfil = (काष्ठा fsl_micfil *)devid;
	काष्ठा platक्रमm_device *pdev = micfil->pdev;
	u32 stat_reg;
	u32 fअगरo_stat_reg;
	u32 ctrl1_reg;
	bool dma_enabled;
	पूर्णांक i;

	regmap_पढ़ो(micfil->regmap, REG_MICFIL_STAT, &stat_reg);
	regmap_पढ़ो(micfil->regmap, REG_MICFIL_CTRL1, &ctrl1_reg);
	regmap_पढ़ो(micfil->regmap, REG_MICFIL_FIFO_STAT, &fअगरo_stat_reg);

	dma_enabled = MICFIL_DMA_ENABLED(ctrl1_reg);

	/* Channel 0-7 Output Data Flags */
	क्रम (i = 0; i < MICFIL_OUTPUT_CHANNELS; i++) अणु
		अगर (stat_reg & MICFIL_STAT_CHXF_MASK(i))
			dev_dbg(&pdev->dev,
				"Data available in Data Channel %d\n", i);
		/* अगर DMA is not enabled, field must be written with 1
		 * to clear
		 */
		अगर (!dma_enabled)
			regmap_ग_लिखो_bits(micfil->regmap,
					  REG_MICFIL_STAT,
					  MICFIL_STAT_CHXF_MASK(i),
					  1);
	पूर्ण

	क्रम (i = 0; i < MICFIL_FIFO_NUM; i++) अणु
		अगर (fअगरo_stat_reg & MICFIL_FIFO_STAT_FIFOX_OVER_MASK(i))
			dev_dbg(&pdev->dev,
				"FIFO Overflow Exception flag for channel %d\n",
				i);

		अगर (fअगरo_stat_reg & MICFIL_FIFO_STAT_FIFOX_UNDER_MASK(i))
			dev_dbg(&pdev->dev,
				"FIFO Underflow Exception flag for channel %d\n",
				i);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t micfil_err_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा fsl_micfil *micfil = (काष्ठा fsl_micfil *)devid;
	काष्ठा platक्रमm_device *pdev = micfil->pdev;
	u32 stat_reg;

	regmap_पढ़ो(micfil->regmap, REG_MICFIL_STAT, &stat_reg);

	अगर (stat_reg & MICFIL_STAT_BSY_FIL_MASK)
		dev_dbg(&pdev->dev, "isr: Decimation Filter is running\n");

	अगर (stat_reg & MICFIL_STAT_FIR_RDY_MASK)
		dev_dbg(&pdev->dev, "isr: FIR Filter Data ready\n");

	अगर (stat_reg & MICFIL_STAT_LOWFREQF_MASK) अणु
		dev_dbg(&pdev->dev, "isr: ipg_clk_app is too low\n");
		regmap_ग_लिखो_bits(micfil->regmap, REG_MICFIL_STAT,
				  MICFIL_STAT_LOWFREQF_MASK, 1);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fsl_micfil_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा fsl_micfil *micfil;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक ret, i;
	अचिन्हित दीर्घ irqflag = 0;

	micfil = devm_kzalloc(&pdev->dev, माप(*micfil), GFP_KERNEL);
	अगर (!micfil)
		वापस -ENOMEM;

	micfil->pdev = pdev;
	म_नकलन(micfil->name, np->name, माप(micfil->name) - 1);

	micfil->soc = of_device_get_match_data(&pdev->dev);

	/* ipg_clk is used to control the रेजिस्टरs
	 * ipg_clk_app is used to operate the filter
	 */
	micfil->mclk = devm_clk_get(&pdev->dev, "ipg_clk_app");
	अगर (IS_ERR(micfil->mclk)) अणु
		dev_err(&pdev->dev, "failed to get core clock: %ld\n",
			PTR_ERR(micfil->mclk));
		वापस PTR_ERR(micfil->mclk);
	पूर्ण

	micfil->busclk = devm_clk_get(&pdev->dev, "ipg_clk");
	अगर (IS_ERR(micfil->busclk)) अणु
		dev_err(&pdev->dev, "failed to get ipg clock: %ld\n",
			PTR_ERR(micfil->busclk));
		वापस PTR_ERR(micfil->busclk);
	पूर्ण

	/* init regmap */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	micfil->regmap = devm_regmap_init_mmio(&pdev->dev,
					       regs,
					       &fsl_micfil_regmap_config);
	अगर (IS_ERR(micfil->regmap)) अणु
		dev_err(&pdev->dev, "failed to init MICFIL regmap: %ld\n",
			PTR_ERR(micfil->regmap));
		वापस PTR_ERR(micfil->regmap);
	पूर्ण

	/* dataline mask क्रम RX */
	ret = of_property_पढ़ो_u32_index(np,
					 "fsl,dataline",
					 0,
					 &micfil->dataline);
	अगर (ret)
		micfil->dataline = 1;

	अगर (micfil->dataline & ~micfil->soc->dataline) अणु
		dev_err(&pdev->dev, "dataline setting error, Mask is 0x%X\n",
			micfil->soc->dataline);
		वापस -EINVAL;
	पूर्ण

	/* get IRQs */
	क्रम (i = 0; i < MICFIL_IRQ_LINES; i++) अणु
		micfil->irq[i] = platक्रमm_get_irq(pdev, i);
		dev_err(&pdev->dev, "GET IRQ: %d\n", micfil->irq[i]);
		अगर (micfil->irq[i] < 0)
			वापस micfil->irq[i];
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "fsl,shared-interrupt"))
		irqflag = IRQF_SHARED;

	/* Digital Microphone पूर्णांकerface पूर्णांकerrupt */
	ret = devm_request_irq(&pdev->dev, micfil->irq[0],
			       micfil_isr, irqflag,
			       micfil->name, micfil);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to claim mic interface irq %u\n",
			micfil->irq[0]);
		वापस ret;
	पूर्ण

	/* Digital Microphone पूर्णांकerface error पूर्णांकerrupt */
	ret = devm_request_irq(&pdev->dev, micfil->irq[1],
			       micfil_err_isr, irqflag,
			       micfil->name, micfil);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to claim mic interface error irq %u\n",
			micfil->irq[1]);
		वापस ret;
	पूर्ण

	micfil->dma_params_rx.chan_name = "rx";
	micfil->dma_params_rx.addr = res->start + REG_MICFIL_DATACH0;
	micfil->dma_params_rx.maxburst = MICFIL_DMA_MAXBURST_RX;


	platक्रमm_set_drvdata(pdev, micfil);

	pm_runसमय_enable(&pdev->dev);
	regcache_cache_only(micfil->regmap, true);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &fsl_micfil_component,
					      &fsl_micfil_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register component %s\n",
			fsl_micfil_component.name);
		वापस ret;
	पूर्ण

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (ret)
		dev_err(&pdev->dev, "failed to pcm register\n");

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused fsl_micfil_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_micfil *micfil = dev_get_drvdata(dev);

	regcache_cache_only(micfil->regmap, true);

	clk_disable_unprepare(micfil->mclk);
	clk_disable_unprepare(micfil->busclk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fsl_micfil_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_micfil *micfil = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(micfil->busclk);
	अगर (ret < 0)
		वापस ret;

	ret = clk_prepare_enable(micfil->mclk);
	अगर (ret < 0) अणु
		clk_disable_unprepare(micfil->busclk);
		वापस ret;
	पूर्ण

	regcache_cache_only(micfil->regmap, false);
	regcache_mark_dirty(micfil->regmap);
	regcache_sync(micfil->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fsl_micfil_suspend(काष्ठा device *dev)
अणु
	pm_runसमय_क्रमce_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fsl_micfil_resume(काष्ठा device *dev)
अणु
	pm_runसमय_क्रमce_resume(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fsl_micfil_pm_ops = अणु
	SET_RUNTIME_PM_OPS(fsl_micfil_runसमय_suspend,
			   fsl_micfil_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(fsl_micfil_suspend,
				fsl_micfil_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_micfil_driver = अणु
	.probe = fsl_micfil_probe,
	.driver = अणु
		.name = "fsl-micfil-dai",
		.pm = &fsl_micfil_pm_ops,
		.of_match_table = fsl_micfil_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(fsl_micfil_driver);

MODULE_AUTHOR("Cosmin-Gabriel Samoila <cosmin.samoila@nxp.com>");
MODULE_DESCRIPTION("NXP PDM Microphone Interface (MICFIL) driver");
MODULE_LICENSE("GPL v2");
