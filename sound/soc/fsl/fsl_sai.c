<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Freescale ALSA SoC Digital Audio Interface (SAI) driver.
//
// Copyright 2012-2015 Freescale Semiconductor, Inc.

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>

#समावेश "fsl_sai.h"
#समावेश "imx-pcm.h"

#घोषणा FSL_SAI_FLAGS (FSL_SAI_CSR_SEIE |\
		       FSL_SAI_CSR_FEIE)

अटल स्थिर अचिन्हित पूर्णांक fsl_sai_rates[] = अणु
	8000, 11025, 12000, 16000, 22050,
	24000, 32000, 44100, 48000, 64000,
	88200, 96000, 176400, 192000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list fsl_sai_rate_स्थिरraपूर्णांकs = अणु
	.count = ARRAY_SIZE(fsl_sai_rates),
	.list = fsl_sai_rates,
पूर्ण;

/**
 * fsl_sai_dir_is_synced - Check अगर stream is synced by the opposite stream
 *
 * SAI supports synchronous mode using bit/frame घड़ीs of either Transmitter's
 * or Receiver's क्रम both streams. This function is used to check अगर घड़ीs of
 * the stream's are synced by the opposite stream.
 *
 * @sai: SAI context
 * @dir: stream direction
 */
अटल अंतरभूत bool fsl_sai_dir_is_synced(काष्ठा fsl_sai *sai, पूर्णांक dir)
अणु
	पूर्णांक adir = (dir == TX) ? RX : TX;

	/* current dir in async mode जबतक opposite dir in sync mode */
	वापस !sai->synchronous[dir] && sai->synchronous[adir];
पूर्ण

अटल irqवापस_t fsl_sai_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा fsl_sai *sai = (काष्ठा fsl_sai *)devid;
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;
	काष्ठा device *dev = &sai->pdev->dev;
	u32 flags, xcsr, mask;
	bool irq_none = true;

	/*
	 * Both IRQ status bits and IRQ mask bits are in the xCSR but
	 * dअगरferent shअगरts. And we here create a mask only क्रम those
	 * IRQs that we activated.
	 */
	mask = (FSL_SAI_FLAGS >> FSL_SAI_CSR_xIE_SHIFT) << FSL_SAI_CSR_xF_SHIFT;

	/* Tx IRQ */
	regmap_पढ़ो(sai->regmap, FSL_SAI_TCSR(ofs), &xcsr);
	flags = xcsr & mask;

	अगर (flags)
		irq_none = false;
	अन्यथा
		जाओ irq_rx;

	अगर (flags & FSL_SAI_CSR_WSF)
		dev_dbg(dev, "isr: Start of Tx word detected\n");

	अगर (flags & FSL_SAI_CSR_SEF)
		dev_dbg(dev, "isr: Tx Frame sync error detected\n");

	अगर (flags & FSL_SAI_CSR_FEF) अणु
		dev_dbg(dev, "isr: Transmit underrun detected\n");
		/* FIFO reset क्रम safety */
		xcsr |= FSL_SAI_CSR_FR;
	पूर्ण

	अगर (flags & FSL_SAI_CSR_FWF)
		dev_dbg(dev, "isr: Enabled transmit FIFO is empty\n");

	अगर (flags & FSL_SAI_CSR_FRF)
		dev_dbg(dev, "isr: Transmit FIFO watermark has been reached\n");

	flags &= FSL_SAI_CSR_xF_W_MASK;
	xcsr &= ~FSL_SAI_CSR_xF_MASK;

	अगर (flags)
		regmap_ग_लिखो(sai->regmap, FSL_SAI_TCSR(ofs), flags | xcsr);

irq_rx:
	/* Rx IRQ */
	regmap_पढ़ो(sai->regmap, FSL_SAI_RCSR(ofs), &xcsr);
	flags = xcsr & mask;

	अगर (flags)
		irq_none = false;
	अन्यथा
		जाओ out;

	अगर (flags & FSL_SAI_CSR_WSF)
		dev_dbg(dev, "isr: Start of Rx word detected\n");

	अगर (flags & FSL_SAI_CSR_SEF)
		dev_dbg(dev, "isr: Rx Frame sync error detected\n");

	अगर (flags & FSL_SAI_CSR_FEF) अणु
		dev_dbg(dev, "isr: Receive overflow detected\n");
		/* FIFO reset क्रम safety */
		xcsr |= FSL_SAI_CSR_FR;
	पूर्ण

	अगर (flags & FSL_SAI_CSR_FWF)
		dev_dbg(dev, "isr: Enabled receive FIFO is full\n");

	अगर (flags & FSL_SAI_CSR_FRF)
		dev_dbg(dev, "isr: Receive FIFO watermark has been reached\n");

	flags &= FSL_SAI_CSR_xF_W_MASK;
	xcsr &= ~FSL_SAI_CSR_xF_MASK;

	अगर (flags)
		regmap_ग_लिखो(sai->regmap, FSL_SAI_RCSR(ofs), flags | xcsr);

out:
	अगर (irq_none)
		वापस IRQ_NONE;
	अन्यथा
		वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fsl_sai_set_dai_tdm_slot(काष्ठा snd_soc_dai *cpu_dai, u32 tx_mask,
				u32 rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);

	sai->slots = slots;
	sai->slot_width = slot_width;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_sai_set_dai_bclk_ratio(काष्ठा snd_soc_dai *dai,
				      अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा fsl_sai *sai = snd_soc_dai_get_drvdata(dai);

	sai->bclk_ratio = ratio;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_sai_set_dai_sysclk_tr(काष्ठा snd_soc_dai *cpu_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक fsl_dir)
अणु
	काष्ठा fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;
	bool tx = fsl_dir == FSL_FMT_TRANSMITTER;
	u32 val_cr2 = 0;

	चयन (clk_id) अणु
	हाल FSL_SAI_CLK_BUS:
		val_cr2 |= FSL_SAI_CR2_MSEL_BUS;
		अवरोध;
	हाल FSL_SAI_CLK_MAST1:
		val_cr2 |= FSL_SAI_CR2_MSEL_MCLK1;
		अवरोध;
	हाल FSL_SAI_CLK_MAST2:
		val_cr2 |= FSL_SAI_CR2_MSEL_MCLK2;
		अवरोध;
	हाल FSL_SAI_CLK_MAST3:
		val_cr2 |= FSL_SAI_CR2_MSEL_MCLK3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(sai->regmap, FSL_SAI_xCR2(tx, ofs),
			   FSL_SAI_CR2_MSEL_MASK, val_cr2);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_sai_set_dai_sysclk(काष्ठा snd_soc_dai *cpu_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	पूर्णांक ret;

	अगर (dir == SND_SOC_CLOCK_IN)
		वापस 0;

	ret = fsl_sai_set_dai_sysclk_tr(cpu_dai, clk_id, freq,
					FSL_FMT_TRANSMITTER);
	अगर (ret) अणु
		dev_err(cpu_dai->dev, "Cannot set tx sysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = fsl_sai_set_dai_sysclk_tr(cpu_dai, clk_id, freq,
					FSL_FMT_RECEIVER);
	अगर (ret)
		dev_err(cpu_dai->dev, "Cannot set rx sysclk: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_sai_set_dai_fmt_tr(काष्ठा snd_soc_dai *cpu_dai,
				अचिन्हित पूर्णांक fmt, पूर्णांक fsl_dir)
अणु
	काष्ठा fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;
	bool tx = fsl_dir == FSL_FMT_TRANSMITTER;
	u32 val_cr2 = 0, val_cr4 = 0;

	अगर (!sai->is_lsb_first)
		val_cr4 |= FSL_SAI_CR4_MF;

	/* DAI mode */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		/*
		 * Frame low, 1clk beक्रमe data, one word length क्रम frame sync,
		 * frame sync starts one serial घड़ी cycle earlier,
		 * that is, together with the last bit of the previous
		 * data word.
		 */
		val_cr2 |= FSL_SAI_CR2_BCP;
		val_cr4 |= FSL_SAI_CR4_FSE | FSL_SAI_CR4_FSP;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		/*
		 * Frame high, one word length क्रम frame sync,
		 * frame sync निश्चितs with the first bit of the frame.
		 */
		val_cr2 |= FSL_SAI_CR2_BCP;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		/*
		 * Frame high, 1clk beक्रमe data, one bit क्रम frame sync,
		 * frame sync starts one serial घड़ी cycle earlier,
		 * that is, together with the last bit of the previous
		 * data word.
		 */
		val_cr2 |= FSL_SAI_CR2_BCP;
		val_cr4 |= FSL_SAI_CR4_FSE;
		sai->is_dsp_mode = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		/*
		 * Frame high, one bit क्रम frame sync,
		 * frame sync निश्चितs with the first bit of the frame.
		 */
		val_cr2 |= FSL_SAI_CR2_BCP;
		sai->is_dsp_mode = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		/* To be करोne */
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* DAI घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_IF:
		/* Invert both घड़ीs */
		val_cr2 ^= FSL_SAI_CR2_BCP;
		val_cr4 ^= FSL_SAI_CR4_FSP;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		/* Invert bit घड़ी */
		val_cr2 ^= FSL_SAI_CR2_BCP;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		/* Invert frame घड़ी */
		val_cr4 ^= FSL_SAI_CR4_FSP;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
		/* Nothing to करो क्रम both normal हालs */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* DAI घड़ी master masks */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		val_cr2 |= FSL_SAI_CR2_BCD_MSTR;
		val_cr4 |= FSL_SAI_CR4_FSD_MSTR;
		sai->is_slave_mode = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		sai->is_slave_mode = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		val_cr2 |= FSL_SAI_CR2_BCD_MSTR;
		sai->is_slave_mode = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		val_cr4 |= FSL_SAI_CR4_FSD_MSTR;
		sai->is_slave_mode = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(sai->regmap, FSL_SAI_xCR2(tx, ofs),
			   FSL_SAI_CR2_BCP | FSL_SAI_CR2_BCD_MSTR, val_cr2);
	regmap_update_bits(sai->regmap, FSL_SAI_xCR4(tx, ofs),
			   FSL_SAI_CR4_MF | FSL_SAI_CR4_FSE |
			   FSL_SAI_CR4_FSP | FSL_SAI_CR4_FSD_MSTR, val_cr4);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_sai_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai, अचिन्हित पूर्णांक fmt)
अणु
	पूर्णांक ret;

	ret = fsl_sai_set_dai_fmt_tr(cpu_dai, fmt, FSL_FMT_TRANSMITTER);
	अगर (ret) अणु
		dev_err(cpu_dai->dev, "Cannot set tx format: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = fsl_sai_set_dai_fmt_tr(cpu_dai, fmt, FSL_FMT_RECEIVER);
	अगर (ret)
		dev_err(cpu_dai->dev, "Cannot set rx format: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_sai_set_bclk(काष्ठा snd_soc_dai *dai, bool tx, u32 freq)
अणु
	काष्ठा fsl_sai *sai = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;
	अचिन्हित दीर्घ clk_rate;
	u32 saveभाग = 0, ratio, savesub = freq;
	पूर्णांक adir = tx ? RX : TX;
	पूर्णांक dir = tx ? TX : RX;
	u32 id;
	पूर्णांक ret = 0;

	/* Don't apply to slave mode */
	अगर (sai->is_slave_mode)
		वापस 0;

	/*
	 * There is no poपूर्णांक in polling MCLK0 अगर it is identical to MCLK1.
	 * And given that MQS use हाल has to use MCLK1 though two घड़ीs
	 * are the same, we simply skip MCLK0 and start to find from MCLK1.
	 */
	id = sai->soc_data->mclk0_is_mclk1 ? 1 : 0;

	क्रम (; id < FSL_SAI_MCLK_MAX; id++) अणु
		clk_rate = clk_get_rate(sai->mclk_clk[id]);
		अगर (!clk_rate)
			जारी;

		ratio = clk_rate / freq;

		ret = clk_rate - ratio * freq;

		/*
		 * Drop the source that can not be
		 * भागided पूर्णांकo the required rate.
		 */
		अगर (ret != 0 && clk_rate / ret < 1000)
			जारी;

		dev_dbg(dai->dev,
			"ratio %d for freq %dHz based on clock %ldHz\n",
			ratio, freq, clk_rate);

		अगर (ratio % 2 == 0 && ratio >= 2 && ratio <= 512)
			ratio /= 2;
		अन्यथा
			जारी;

		अगर (ret < savesub) अणु
			saveभाग = ratio;
			sai->mclk_id[tx] = id;
			savesub = ret;
		पूर्ण

		अगर (ret == 0)
			अवरोध;
	पूर्ण

	अगर (saveभाग == 0) अणु
		dev_err(dai->dev, "failed to derive required %cx rate: %d\n",
				tx ? 'T' : 'R', freq);
		वापस -EINVAL;
	पूर्ण

	/*
	 * 1) For Asynchronous mode, we must set RCR2 रेजिस्टर क्रम capture, and
	 *    set TCR2 रेजिस्टर क्रम playback.
	 * 2) For Tx sync with Rx घड़ी, we must set RCR2 रेजिस्टर क्रम playback
	 *    and capture.
	 * 3) For Rx sync with Tx घड़ी, we must set TCR2 रेजिस्टर क्रम playback
	 *    and capture.
	 * 4) For Tx and Rx are both Synchronous with another SAI, we just
	 *    ignore it.
	 */
	अगर (fsl_sai_dir_is_synced(sai, adir)) अणु
		regmap_update_bits(sai->regmap, FSL_SAI_xCR2(!tx, ofs),
				   FSL_SAI_CR2_MSEL_MASK,
				   FSL_SAI_CR2_MSEL(sai->mclk_id[tx]));
		regmap_update_bits(sai->regmap, FSL_SAI_xCR2(!tx, ofs),
				   FSL_SAI_CR2_DIV_MASK, saveभाग - 1);
	पूर्ण अन्यथा अगर (!sai->synchronous[dir]) अणु
		regmap_update_bits(sai->regmap, FSL_SAI_xCR2(tx, ofs),
				   FSL_SAI_CR2_MSEL_MASK,
				   FSL_SAI_CR2_MSEL(sai->mclk_id[tx]));
		regmap_update_bits(sai->regmap, FSL_SAI_xCR2(tx, ofs),
				   FSL_SAI_CR2_DIV_MASK, saveभाग - 1);
	पूर्ण

	dev_dbg(dai->dev, "best fit: clock id=%d, div=%d, deviation =%d\n",
			sai->mclk_id[tx], saveभाग, savesub);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_sai_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	अचिन्हित पूर्णांक channels = params_channels(params);
	u32 word_width = params_width(params);
	u32 val_cr4 = 0, val_cr5 = 0;
	u32 slots = (channels == 1) ? 2 : channels;
	u32 slot_width = word_width;
	पूर्णांक adir = tx ? RX : TX;
	u32 pins;
	पूर्णांक ret;

	अगर (sai->slots)
		slots = sai->slots;

	अगर (sai->slot_width)
		slot_width = sai->slot_width;

	pins = DIV_ROUND_UP(channels, slots);

	अगर (!sai->is_slave_mode) अणु
		अगर (sai->bclk_ratio)
			ret = fsl_sai_set_bclk(cpu_dai, tx,
					       sai->bclk_ratio *
					       params_rate(params));
		अन्यथा
			ret = fsl_sai_set_bclk(cpu_dai, tx,
					       slots * slot_width *
					       params_rate(params));
		अगर (ret)
			वापस ret;

		/* Do not enable the घड़ी अगर it is alपढ़ोy enabled */
		अगर (!(sai->mclk_streams & BIT(substream->stream))) अणु
			ret = clk_prepare_enable(sai->mclk_clk[sai->mclk_id[tx]]);
			अगर (ret)
				वापस ret;

			sai->mclk_streams |= BIT(substream->stream);
		पूर्ण
	पूर्ण

	अगर (!sai->is_dsp_mode)
		val_cr4 |= FSL_SAI_CR4_SYWD(slot_width);

	val_cr5 |= FSL_SAI_CR5_WNW(slot_width);
	val_cr5 |= FSL_SAI_CR5_W0W(slot_width);

	अगर (sai->is_lsb_first)
		val_cr5 |= FSL_SAI_CR5_FBT(0);
	अन्यथा
		val_cr5 |= FSL_SAI_CR5_FBT(word_width - 1);

	val_cr4 |= FSL_SAI_CR4_FRSZ(slots);

	/* Set to output mode to aव्योम tri-stated data pins */
	अगर (tx)
		val_cr4 |= FSL_SAI_CR4_CHMOD;

	/*
	 * For SAI master mode, when Tx(Rx) sync with Rx(Tx) घड़ी, Rx(Tx) will
	 * generate bclk and frame घड़ी क्रम Tx(Rx), we should set RCR4(TCR4),
	 * RCR5(TCR5) क्रम playback(capture), or there will be sync error.
	 */

	अगर (!sai->is_slave_mode && fsl_sai_dir_is_synced(sai, adir)) अणु
		regmap_update_bits(sai->regmap, FSL_SAI_xCR4(!tx, ofs),
				   FSL_SAI_CR4_SYWD_MASK | FSL_SAI_CR4_FRSZ_MASK |
				   FSL_SAI_CR4_CHMOD_MASK,
				   val_cr4);
		regmap_update_bits(sai->regmap, FSL_SAI_xCR5(!tx, ofs),
				   FSL_SAI_CR5_WNW_MASK | FSL_SAI_CR5_W0W_MASK |
				   FSL_SAI_CR5_FBT_MASK, val_cr5);
	पूर्ण

	regmap_update_bits(sai->regmap, FSL_SAI_xCR3(tx, ofs),
			   FSL_SAI_CR3_TRCE_MASK,
			   FSL_SAI_CR3_TRCE((1 << pins) - 1));
	regmap_update_bits(sai->regmap, FSL_SAI_xCR4(tx, ofs),
			   FSL_SAI_CR4_SYWD_MASK | FSL_SAI_CR4_FRSZ_MASK |
			   FSL_SAI_CR4_CHMOD_MASK,
			   val_cr4);
	regmap_update_bits(sai->regmap, FSL_SAI_xCR5(tx, ofs),
			   FSL_SAI_CR5_WNW_MASK | FSL_SAI_CR5_W0W_MASK |
			   FSL_SAI_CR5_FBT_MASK, val_cr5);
	regmap_ग_लिखो(sai->regmap, FSL_SAI_xMR(tx),
		     ~0UL - ((1 << min(channels, slots)) - 1));

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_sai_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;

	regmap_update_bits(sai->regmap, FSL_SAI_xCR3(tx, ofs),
			   FSL_SAI_CR3_TRCE_MASK, 0);

	अगर (!sai->is_slave_mode &&
			sai->mclk_streams & BIT(substream->stream)) अणु
		clk_disable_unprepare(sai->mclk_clk[sai->mclk_id[tx]]);
		sai->mclk_streams &= ~BIT(substream->stream);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fsl_sai_config_disable(काष्ठा fsl_sai *sai, पूर्णांक dir)
अणु
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;
	bool tx = dir == TX;
	u32 xcsr, count = 100;

	regmap_update_bits(sai->regmap, FSL_SAI_xCSR(tx, ofs),
			   FSL_SAI_CSR_TERE, 0);

	/* TERE will reमुख्य set till the end of current frame */
	करो अणु
		udelay(10);
		regmap_पढ़ो(sai->regmap, FSL_SAI_xCSR(tx, ofs), &xcsr);
	पूर्ण जबतक (--count && xcsr & FSL_SAI_CSR_TERE);

	regmap_update_bits(sai->regmap, FSL_SAI_xCSR(tx, ofs),
			   FSL_SAI_CSR_FR, FSL_SAI_CSR_FR);

	/*
	 * For sai master mode, after several खोलो/बंद sai,
	 * there will be no frame घड़ी, and can't recover
	 * anymore. Add software reset to fix this issue.
	 * This is a hardware bug, and will be fix in the
	 * next sai version.
	 */
	अगर (!sai->is_slave_mode) अणु
		/* Software Reset */
		regmap_ग_लिखो(sai->regmap, FSL_SAI_xCSR(tx, ofs), FSL_SAI_CSR_SR);
		/* Clear SR bit to finish the reset */
		regmap_ग_लिखो(sai->regmap, FSL_SAI_xCSR(tx, ofs), 0);
	पूर्ण
पूर्ण

अटल पूर्णांक fsl_sai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
		काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;

	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	पूर्णांक adir = tx ? RX : TX;
	पूर्णांक dir = tx ? TX : RX;
	u32 xcsr;

	/*
	 * Asynchronous mode: Clear SYNC क्रम both Tx and Rx.
	 * Rx sync with Tx घड़ीs: Clear SYNC क्रम Tx, set it क्रम Rx.
	 * Tx sync with Rx घड़ीs: Clear SYNC क्रम Rx, set it क्रम Tx.
	 */
	regmap_update_bits(sai->regmap, FSL_SAI_TCR2(ofs), FSL_SAI_CR2_SYNC,
			   sai->synchronous[TX] ? FSL_SAI_CR2_SYNC : 0);
	regmap_update_bits(sai->regmap, FSL_SAI_RCR2(ofs), FSL_SAI_CR2_SYNC,
			   sai->synchronous[RX] ? FSL_SAI_CR2_SYNC : 0);

	/*
	 * It is recommended that the transmitter is the last enabled
	 * and the first disabled.
	 */
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		regmap_update_bits(sai->regmap, FSL_SAI_xCSR(tx, ofs),
				   FSL_SAI_CSR_FRDE, FSL_SAI_CSR_FRDE);

		regmap_update_bits(sai->regmap, FSL_SAI_xCSR(tx, ofs),
				   FSL_SAI_CSR_TERE, FSL_SAI_CSR_TERE);
		/*
		 * Enable the opposite direction क्रम synchronous mode
		 * 1. Tx sync with Rx: only set RE क्रम Rx; set TE & RE क्रम Tx
		 * 2. Rx sync with Tx: only set TE क्रम Tx; set RE & TE क्रम Rx
		 *
		 * RM recommends to enable RE after TE क्रम हाल 1 and to enable
		 * TE after RE क्रम हाल 2, but we here may not always guarantee
		 * that happens: "arecord 1.wav; aplay 2.wav" in हाल 1 enables
		 * TE after RE, which is against what RM recommends but should
		 * be safe to करो, judging by years of testing results.
		 */
		अगर (fsl_sai_dir_is_synced(sai, adir))
			regmap_update_bits(sai->regmap, FSL_SAI_xCSR((!tx), ofs),
					   FSL_SAI_CSR_TERE, FSL_SAI_CSR_TERE);

		regmap_update_bits(sai->regmap, FSL_SAI_xCSR(tx, ofs),
				   FSL_SAI_CSR_xIE_MASK, FSL_SAI_FLAGS);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		regmap_update_bits(sai->regmap, FSL_SAI_xCSR(tx, ofs),
				   FSL_SAI_CSR_FRDE, 0);
		regmap_update_bits(sai->regmap, FSL_SAI_xCSR(tx, ofs),
				   FSL_SAI_CSR_xIE_MASK, 0);

		/* Check अगर the opposite FRDE is also disabled */
		regmap_पढ़ो(sai->regmap, FSL_SAI_xCSR(!tx, ofs), &xcsr);

		/*
		 * If opposite stream provides घड़ीs क्रम synchronous mode and
		 * it is inactive, disable it beक्रमe disabling the current one
		 */
		अगर (fsl_sai_dir_is_synced(sai, adir) && !(xcsr & FSL_SAI_CSR_FRDE))
			fsl_sai_config_disable(sai, adir);

		/*
		 * Disable current stream अगर either of:
		 * 1. current stream करोesn't provide घड़ीs क्रम synchronous mode
		 * 2. current stream provides घड़ीs क्रम synchronous mode but no
		 *    more stream is active.
		 */
		अगर (!fsl_sai_dir_is_synced(sai, dir) || !(xcsr & FSL_SAI_CSR_FRDE))
			fsl_sai_config_disable(sai, dir);

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_sai_startup(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	पूर्णांक ret;

	/*
	 * EDMA controller needs period size to be a multiple of
	 * tx/rx maxburst
	 */
	अगर (sai->soc_data->use_edma)
		snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
					   SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					   tx ? sai->dma_params_tx.maxburst :
					   sai->dma_params_rx.maxburst);

	ret = snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &fsl_sai_rate_स्थिरraपूर्णांकs);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops fsl_sai_pcm_dai_ops = अणु
	.set_bclk_ratio	= fsl_sai_set_dai_bclk_ratio,
	.set_sysclk	= fsl_sai_set_dai_sysclk,
	.set_fmt	= fsl_sai_set_dai_fmt,
	.set_tdm_slot	= fsl_sai_set_dai_tdm_slot,
	.hw_params	= fsl_sai_hw_params,
	.hw_मुक्त	= fsl_sai_hw_मुक्त,
	.trigger	= fsl_sai_trigger,
	.startup	= fsl_sai_startup,
पूर्ण;

अटल पूर्णांक fsl_sai_dai_probe(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा fsl_sai *sai = dev_get_drvdata(cpu_dai->dev);
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;

	/* Software Reset क्रम both Tx and Rx */
	regmap_ग_लिखो(sai->regmap, FSL_SAI_TCSR(ofs), FSL_SAI_CSR_SR);
	regmap_ग_लिखो(sai->regmap, FSL_SAI_RCSR(ofs), FSL_SAI_CSR_SR);
	/* Clear SR bit to finish the reset */
	regmap_ग_लिखो(sai->regmap, FSL_SAI_TCSR(ofs), 0);
	regmap_ग_लिखो(sai->regmap, FSL_SAI_RCSR(ofs), 0);

	regmap_update_bits(sai->regmap, FSL_SAI_TCR1(ofs),
			   FSL_SAI_CR1_RFW_MASK(sai->soc_data->fअगरo_depth),
			   sai->soc_data->fअगरo_depth - FSL_SAI_MAXBURST_TX);
	regmap_update_bits(sai->regmap, FSL_SAI_RCR1(ofs),
			   FSL_SAI_CR1_RFW_MASK(sai->soc_data->fअगरo_depth),
			   FSL_SAI_MAXBURST_RX - 1);

	snd_soc_dai_init_dma_data(cpu_dai, &sai->dma_params_tx,
				&sai->dma_params_rx);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver fsl_sai_dai_ढाँचा = अणु
	.probe = fsl_sai_dai_probe,
	.playback = अणु
		.stream_name = "CPU-Playback",
		.channels_min = 1,
		.channels_max = 32,
		.rate_min = 8000,
		.rate_max = 192000,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = FSL_SAI_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "CPU-Capture",
		.channels_min = 1,
		.channels_max = 32,
		.rate_min = 8000,
		.rate_max = 192000,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = FSL_SAI_FORMATS,
	पूर्ण,
	.ops = &fsl_sai_pcm_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver fsl_component = अणु
	.name           = "fsl-sai",
पूर्ण;

अटल काष्ठा reg_शेष fsl_sai_reg_शेषs_ofs0[] = अणु
	अणुFSL_SAI_TCR1(0), 0पूर्ण,
	अणुFSL_SAI_TCR2(0), 0पूर्ण,
	अणुFSL_SAI_TCR3(0), 0पूर्ण,
	अणुFSL_SAI_TCR4(0), 0पूर्ण,
	अणुFSL_SAI_TCR5(0), 0पूर्ण,
	अणुFSL_SAI_TDR0, 0पूर्ण,
	अणुFSL_SAI_TDR1, 0पूर्ण,
	अणुFSL_SAI_TDR2, 0पूर्ण,
	अणुFSL_SAI_TDR3, 0पूर्ण,
	अणुFSL_SAI_TDR4, 0पूर्ण,
	अणुFSL_SAI_TDR5, 0पूर्ण,
	अणुFSL_SAI_TDR6, 0पूर्ण,
	अणुFSL_SAI_TDR7, 0पूर्ण,
	अणुFSL_SAI_TMR, 0पूर्ण,
	अणुFSL_SAI_RCR1(0), 0पूर्ण,
	अणुFSL_SAI_RCR2(0), 0पूर्ण,
	अणुFSL_SAI_RCR3(0), 0पूर्ण,
	अणुFSL_SAI_RCR4(0), 0पूर्ण,
	अणुFSL_SAI_RCR5(0), 0पूर्ण,
	अणुFSL_SAI_RMR, 0पूर्ण,
पूर्ण;

अटल काष्ठा reg_शेष fsl_sai_reg_शेषs_ofs8[] = अणु
	अणुFSL_SAI_TCR1(8), 0पूर्ण,
	अणुFSL_SAI_TCR2(8), 0पूर्ण,
	अणुFSL_SAI_TCR3(8), 0पूर्ण,
	अणुFSL_SAI_TCR4(8), 0पूर्ण,
	अणुFSL_SAI_TCR5(8), 0पूर्ण,
	अणुFSL_SAI_TDR0, 0पूर्ण,
	अणुFSL_SAI_TDR1, 0पूर्ण,
	अणुFSL_SAI_TDR2, 0पूर्ण,
	अणुFSL_SAI_TDR3, 0पूर्ण,
	अणुFSL_SAI_TDR4, 0पूर्ण,
	अणुFSL_SAI_TDR5, 0पूर्ण,
	अणुFSL_SAI_TDR6, 0पूर्ण,
	अणुFSL_SAI_TDR7, 0पूर्ण,
	अणुFSL_SAI_TMR, 0पूर्ण,
	अणुFSL_SAI_RCR1(8), 0पूर्ण,
	अणुFSL_SAI_RCR2(8), 0पूर्ण,
	अणुFSL_SAI_RCR3(8), 0पूर्ण,
	अणुFSL_SAI_RCR4(8), 0पूर्ण,
	अणुFSL_SAI_RCR5(8), 0पूर्ण,
	अणुFSL_SAI_RMR, 0पूर्ण,
	अणुFSL_SAI_MCTL, 0पूर्ण,
	अणुFSL_SAI_MDIV, 0पूर्ण,
पूर्ण;

अटल bool fsl_sai_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा fsl_sai *sai = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;

	अगर (reg >= FSL_SAI_TCSR(ofs) && reg <= FSL_SAI_TCR5(ofs))
		वापस true;

	अगर (reg >= FSL_SAI_RCSR(ofs) && reg <= FSL_SAI_RCR5(ofs))
		वापस true;

	चयन (reg) अणु
	हाल FSL_SAI_TFR0:
	हाल FSL_SAI_TFR1:
	हाल FSL_SAI_TFR2:
	हाल FSL_SAI_TFR3:
	हाल FSL_SAI_TFR4:
	हाल FSL_SAI_TFR5:
	हाल FSL_SAI_TFR6:
	हाल FSL_SAI_TFR7:
	हाल FSL_SAI_TMR:
	हाल FSL_SAI_RDR0:
	हाल FSL_SAI_RDR1:
	हाल FSL_SAI_RDR2:
	हाल FSL_SAI_RDR3:
	हाल FSL_SAI_RDR4:
	हाल FSL_SAI_RDR5:
	हाल FSL_SAI_RDR6:
	हाल FSL_SAI_RDR7:
	हाल FSL_SAI_RFR0:
	हाल FSL_SAI_RFR1:
	हाल FSL_SAI_RFR2:
	हाल FSL_SAI_RFR3:
	हाल FSL_SAI_RFR4:
	हाल FSL_SAI_RFR5:
	हाल FSL_SAI_RFR6:
	हाल FSL_SAI_RFR7:
	हाल FSL_SAI_RMR:
	हाल FSL_SAI_MCTL:
	हाल FSL_SAI_MDIV:
	हाल FSL_SAI_VERID:
	हाल FSL_SAI_PARAM:
	हाल FSL_SAI_TTCTN:
	हाल FSL_SAI_RTCTN:
	हाल FSL_SAI_TTCTL:
	हाल FSL_SAI_TBCTN:
	हाल FSL_SAI_TTCAP:
	हाल FSL_SAI_RTCTL:
	हाल FSL_SAI_RBCTN:
	हाल FSL_SAI_RTCAP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_sai_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा fsl_sai *sai = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;

	अगर (reg == FSL_SAI_TCSR(ofs) || reg == FSL_SAI_RCSR(ofs))
		वापस true;

	/* Set VERID and PARAM be अस्थिर क्रम पढ़ोing value in probe */
	अगर (ofs == 8 && (reg == FSL_SAI_VERID || reg == FSL_SAI_PARAM))
		वापस true;

	चयन (reg) अणु
	हाल FSL_SAI_TFR0:
	हाल FSL_SAI_TFR1:
	हाल FSL_SAI_TFR2:
	हाल FSL_SAI_TFR3:
	हाल FSL_SAI_TFR4:
	हाल FSL_SAI_TFR5:
	हाल FSL_SAI_TFR6:
	हाल FSL_SAI_TFR7:
	हाल FSL_SAI_RFR0:
	हाल FSL_SAI_RFR1:
	हाल FSL_SAI_RFR2:
	हाल FSL_SAI_RFR3:
	हाल FSL_SAI_RFR4:
	हाल FSL_SAI_RFR5:
	हाल FSL_SAI_RFR6:
	हाल FSL_SAI_RFR7:
	हाल FSL_SAI_RDR0:
	हाल FSL_SAI_RDR1:
	हाल FSL_SAI_RDR2:
	हाल FSL_SAI_RDR3:
	हाल FSL_SAI_RDR4:
	हाल FSL_SAI_RDR5:
	हाल FSL_SAI_RDR6:
	हाल FSL_SAI_RDR7:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_sai_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा fsl_sai *sai = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;

	अगर (reg >= FSL_SAI_TCSR(ofs) && reg <= FSL_SAI_TCR5(ofs))
		वापस true;

	अगर (reg >= FSL_SAI_RCSR(ofs) && reg <= FSL_SAI_RCR5(ofs))
		वापस true;

	चयन (reg) अणु
	हाल FSL_SAI_TDR0:
	हाल FSL_SAI_TDR1:
	हाल FSL_SAI_TDR2:
	हाल FSL_SAI_TDR3:
	हाल FSL_SAI_TDR4:
	हाल FSL_SAI_TDR5:
	हाल FSL_SAI_TDR6:
	हाल FSL_SAI_TDR7:
	हाल FSL_SAI_TMR:
	हाल FSL_SAI_RMR:
	हाल FSL_SAI_MCTL:
	हाल FSL_SAI_MDIV:
	हाल FSL_SAI_TTCTL:
	हाल FSL_SAI_RTCTL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा regmap_config fsl_sai_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.fast_io = true,

	.max_रेजिस्टर = FSL_SAI_RMR,
	.reg_शेषs = fsl_sai_reg_शेषs_ofs0,
	.num_reg_शेषs = ARRAY_SIZE(fsl_sai_reg_शेषs_ofs0),
	.पढ़ोable_reg = fsl_sai_पढ़ोable_reg,
	.अस्थिर_reg = fsl_sai_अस्थिर_reg,
	.ग_लिखोable_reg = fsl_sai_ग_लिखोable_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक fsl_sai_check_version(काष्ठा device *dev)
अणु
	काष्ठा fsl_sai *sai = dev_get_drvdata(dev);
	अचिन्हित अक्षर ofs = sai->soc_data->reg_offset;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (FSL_SAI_TCSR(ofs) == FSL_SAI_VERID)
		वापस 0;

	ret = regmap_पढ़ो(sai->regmap, FSL_SAI_VERID, &val);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(dev, "VERID: 0x%016X\n", val);

	sai->verid.major = (val & FSL_SAI_VERID_MAJOR_MASK) >>
			   FSL_SAI_VERID_MAJOR_SHIFT;
	sai->verid.minor = (val & FSL_SAI_VERID_MINOR_MASK) >>
			   FSL_SAI_VERID_MINOR_SHIFT;
	sai->verid.feature = val & FSL_SAI_VERID_FEATURE_MASK;

	ret = regmap_पढ़ो(sai->regmap, FSL_SAI_PARAM, &val);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(dev, "PARAM: 0x%016X\n", val);

	/* Max slots per frame, घातer of 2 */
	sai->param.slot_num = 1 <<
		((val & FSL_SAI_PARAM_SPF_MASK) >> FSL_SAI_PARAM_SPF_SHIFT);

	/* Words per fअगरo, घातer of 2 */
	sai->param.fअगरo_depth = 1 <<
		((val & FSL_SAI_PARAM_WPF_MASK) >> FSL_SAI_PARAM_WPF_SHIFT);

	/* Number of datalines implemented */
	sai->param.dataline = val & FSL_SAI_PARAM_DLN_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_sai_runसमय_suspend(काष्ठा device *dev);
अटल पूर्णांक fsl_sai_runसमय_resume(काष्ठा device *dev);

अटल पूर्णांक fsl_sai_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा fsl_sai *sai;
	काष्ठा regmap *gpr;
	काष्ठा resource *res;
	व्योम __iomem *base;
	अक्षर पंचांगp[8];
	पूर्णांक irq, ret, i;
	पूर्णांक index;

	sai = devm_kzalloc(&pdev->dev, माप(*sai), GFP_KERNEL);
	अगर (!sai)
		वापस -ENOMEM;

	sai->pdev = pdev;
	sai->soc_data = of_device_get_match_data(&pdev->dev);

	sai->is_lsb_first = of_property_पढ़ो_bool(np, "lsb-first");

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	अगर (sai->soc_data->reg_offset == 8) अणु
		fsl_sai_regmap_config.reg_शेषs = fsl_sai_reg_शेषs_ofs8;
		fsl_sai_regmap_config.max_रेजिस्टर = FSL_SAI_MDIV;
		fsl_sai_regmap_config.num_reg_शेषs =
			ARRAY_SIZE(fsl_sai_reg_शेषs_ofs8);
	पूर्ण

	sai->regmap = devm_regmap_init_mmio(&pdev->dev, base, &fsl_sai_regmap_config);
	अगर (IS_ERR(sai->regmap)) अणु
		dev_err(&pdev->dev, "regmap init failed\n");
		वापस PTR_ERR(sai->regmap);
	पूर्ण

	sai->bus_clk = devm_clk_get(&pdev->dev, "bus");
	/* Compatible with old DTB हालs */
	अगर (IS_ERR(sai->bus_clk) && PTR_ERR(sai->bus_clk) != -EPROBE_DEFER)
		sai->bus_clk = devm_clk_get(&pdev->dev, "sai");
	अगर (IS_ERR(sai->bus_clk)) अणु
		dev_err(&pdev->dev, "failed to get bus clock: %ld\n",
				PTR_ERR(sai->bus_clk));
		/* -EPROBE_DEFER */
		वापस PTR_ERR(sai->bus_clk);
	पूर्ण

	क्रम (i = 1; i < FSL_SAI_MCLK_MAX; i++) अणु
		प्र_लिखो(पंचांगp, "mclk%d", i);
		sai->mclk_clk[i] = devm_clk_get(&pdev->dev, पंचांगp);
		अगर (IS_ERR(sai->mclk_clk[i])) अणु
			dev_err(&pdev->dev, "failed to get mclk%d clock: %ld\n",
					i + 1, PTR_ERR(sai->mclk_clk[i]));
			sai->mclk_clk[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (sai->soc_data->mclk0_is_mclk1)
		sai->mclk_clk[0] = sai->mclk_clk[1];
	अन्यथा
		sai->mclk_clk[0] = sai->bus_clk;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, fsl_sai_isr, IRQF_SHARED,
			       np->name, sai);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to claim irq %u\n", irq);
		वापस ret;
	पूर्ण

	स_नकल(&sai->cpu_dai_drv, &fsl_sai_dai_ढाँचा,
	       माप(fsl_sai_dai_ढाँचा));

	/* Sync Tx with Rx as शेष by following old DT binding */
	sai->synchronous[RX] = true;
	sai->synchronous[TX] = false;
	sai->cpu_dai_drv.symmetric_rate = 1;
	sai->cpu_dai_drv.symmetric_channels = 1;
	sai->cpu_dai_drv.symmetric_sample_bits = 1;

	अगर (of_find_property(np, "fsl,sai-synchronous-rx", शून्य) &&
	    of_find_property(np, "fsl,sai-asynchronous", शून्य)) अणु
		/* error out अगर both synchronous and asynchronous are present */
		dev_err(&pdev->dev, "invalid binding for synchronous mode\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_find_property(np, "fsl,sai-synchronous-rx", शून्य)) अणु
		/* Sync Rx with Tx */
		sai->synchronous[RX] = false;
		sai->synchronous[TX] = true;
	पूर्ण अन्यथा अगर (of_find_property(np, "fsl,sai-asynchronous", शून्य)) अणु
		/* Discard all settings क्रम asynchronous mode */
		sai->synchronous[RX] = false;
		sai->synchronous[TX] = false;
		sai->cpu_dai_drv.symmetric_rate = 0;
		sai->cpu_dai_drv.symmetric_channels = 0;
		sai->cpu_dai_drv.symmetric_sample_bits = 0;
	पूर्ण

	अगर (of_find_property(np, "fsl,sai-mclk-direction-output", शून्य) &&
	    of_device_is_compatible(np, "fsl,imx6ul-sai")) अणु
		gpr = syscon_regmap_lookup_by_compatible("fsl,imx6ul-iomuxc-gpr");
		अगर (IS_ERR(gpr)) अणु
			dev_err(&pdev->dev, "cannot find iomuxc registers\n");
			वापस PTR_ERR(gpr);
		पूर्ण

		index = of_alias_get_id(np, "sai");
		अगर (index < 0)
			वापस index;

		regmap_update_bits(gpr, IOMUXC_GPR1, MCLK_सूची(index),
				   MCLK_सूची(index));
	पूर्ण

	sai->dma_params_rx.addr = res->start + FSL_SAI_RDR0;
	sai->dma_params_tx.addr = res->start + FSL_SAI_TDR0;
	sai->dma_params_rx.maxburst = FSL_SAI_MAXBURST_RX;
	sai->dma_params_tx.maxburst = FSL_SAI_MAXBURST_TX;

	platक्रमm_set_drvdata(pdev, sai);
	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = fsl_sai_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		जाओ err_pm_get_sync;
	पूर्ण

	/* Get sai version */
	ret = fsl_sai_check_version(&pdev->dev);
	अगर (ret < 0)
		dev_warn(&pdev->dev, "Error reading SAI version: %d\n", ret);

	/* Select MCLK direction */
	अगर (of_find_property(np, "fsl,sai-mclk-direction-output", शून्य) &&
	    sai->verid.major >= 3 && sai->verid.minor >= 1) अणु
		regmap_update_bits(sai->regmap, FSL_SAI_MCTL,
				   FSL_SAI_MCTL_MCLK_EN, FSL_SAI_MCTL_MCLK_EN);
	पूर्ण

	ret = pm_runसमय_put_sync(&pdev->dev);
	अगर (ret < 0)
		जाओ err_pm_get_sync;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &fsl_component,
					      &sai->cpu_dai_drv, 1);
	अगर (ret)
		जाओ err_pm_get_sync;

	अगर (sai->soc_data->use_imx_pcm) अणु
		ret = imx_pcm_dma_init(pdev, IMX_SAI_DMABUF_SIZE);
		अगर (ret)
			जाओ err_pm_get_sync;
	पूर्ण अन्यथा अणु
		ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
		अगर (ret)
			जाओ err_pm_get_sync;
	पूर्ण

	वापस ret;

err_pm_get_sync:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		fsl_sai_runसमय_suspend(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_sai_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		fsl_sai_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fsl_sai_soc_data fsl_sai_vf610_data = अणु
	.use_imx_pcm = false,
	.use_edma = false,
	.fअगरo_depth = 32,
	.reg_offset = 0,
	.mclk0_is_mclk1 = false,
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा fsl_sai_soc_data fsl_sai_imx6sx_data = अणु
	.use_imx_pcm = true,
	.use_edma = false,
	.fअगरo_depth = 32,
	.reg_offset = 0,
	.mclk0_is_mclk1 = true,
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा fsl_sai_soc_data fsl_sai_imx7ulp_data = अणु
	.use_imx_pcm = true,
	.use_edma = false,
	.fअगरo_depth = 16,
	.reg_offset = 8,
	.mclk0_is_mclk1 = false,
	.flags = PMQOS_CPU_LATENCY,
पूर्ण;

अटल स्थिर काष्ठा fsl_sai_soc_data fsl_sai_imx8mq_data = अणु
	.use_imx_pcm = true,
	.use_edma = false,
	.fअगरo_depth = 128,
	.reg_offset = 8,
	.mclk0_is_mclk1 = false,
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा fsl_sai_soc_data fsl_sai_imx8qm_data = अणु
	.use_imx_pcm = true,
	.use_edma = true,
	.fअगरo_depth = 64,
	.reg_offset = 0,
	.mclk0_is_mclk1 = false,
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_sai_ids[] = अणु
	अणु .compatible = "fsl,vf610-sai", .data = &fsl_sai_vf610_data पूर्ण,
	अणु .compatible = "fsl,imx6sx-sai", .data = &fsl_sai_imx6sx_data पूर्ण,
	अणु .compatible = "fsl,imx6ul-sai", .data = &fsl_sai_imx6sx_data पूर्ण,
	अणु .compatible = "fsl,imx7ulp-sai", .data = &fsl_sai_imx7ulp_data पूर्ण,
	अणु .compatible = "fsl,imx8mq-sai", .data = &fsl_sai_imx8mq_data पूर्ण,
	अणु .compatible = "fsl,imx8qm-sai", .data = &fsl_sai_imx8qm_data पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_sai_ids);

अटल पूर्णांक fsl_sai_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_sai *sai = dev_get_drvdata(dev);

	अगर (sai->mclk_streams & BIT(SNDRV_PCM_STREAM_CAPTURE))
		clk_disable_unprepare(sai->mclk_clk[sai->mclk_id[0]]);

	अगर (sai->mclk_streams & BIT(SNDRV_PCM_STREAM_PLAYBACK))
		clk_disable_unprepare(sai->mclk_clk[sai->mclk_id[1]]);

	clk_disable_unprepare(sai->bus_clk);

	अगर (sai->soc_data->flags & PMQOS_CPU_LATENCY)
		cpu_latency_qos_हटाओ_request(&sai->pm_qos_req);

	regcache_cache_only(sai->regmap, true);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_sai_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_sai *sai = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ofs = sai->soc_data->reg_offset;
	पूर्णांक ret;

	ret = clk_prepare_enable(sai->bus_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable bus clock: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (sai->mclk_streams & BIT(SNDRV_PCM_STREAM_PLAYBACK)) अणु
		ret = clk_prepare_enable(sai->mclk_clk[sai->mclk_id[1]]);
		अगर (ret)
			जाओ disable_bus_clk;
	पूर्ण

	अगर (sai->mclk_streams & BIT(SNDRV_PCM_STREAM_CAPTURE)) अणु
		ret = clk_prepare_enable(sai->mclk_clk[sai->mclk_id[0]]);
		अगर (ret)
			जाओ disable_tx_clk;
	पूर्ण

	अगर (sai->soc_data->flags & PMQOS_CPU_LATENCY)
		cpu_latency_qos_add_request(&sai->pm_qos_req, 0);

	regcache_cache_only(sai->regmap, false);
	regcache_mark_dirty(sai->regmap);
	regmap_ग_लिखो(sai->regmap, FSL_SAI_TCSR(ofs), FSL_SAI_CSR_SR);
	regmap_ग_लिखो(sai->regmap, FSL_SAI_RCSR(ofs), FSL_SAI_CSR_SR);
	usleep_range(1000, 2000);
	regmap_ग_लिखो(sai->regmap, FSL_SAI_TCSR(ofs), 0);
	regmap_ग_लिखो(sai->regmap, FSL_SAI_RCSR(ofs), 0);

	ret = regcache_sync(sai->regmap);
	अगर (ret)
		जाओ disable_rx_clk;

	वापस 0;

disable_rx_clk:
	अगर (sai->mclk_streams & BIT(SNDRV_PCM_STREAM_CAPTURE))
		clk_disable_unprepare(sai->mclk_clk[sai->mclk_id[0]]);
disable_tx_clk:
	अगर (sai->mclk_streams & BIT(SNDRV_PCM_STREAM_PLAYBACK))
		clk_disable_unprepare(sai->mclk_clk[sai->mclk_id[1]]);
disable_bus_clk:
	clk_disable_unprepare(sai->bus_clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fsl_sai_pm_ops = अणु
	SET_RUNTIME_PM_OPS(fsl_sai_runसमय_suspend,
			   fsl_sai_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_sai_driver = अणु
	.probe = fsl_sai_probe,
	.हटाओ = fsl_sai_हटाओ,
	.driver = अणु
		.name = "fsl-sai",
		.pm = &fsl_sai_pm_ops,
		.of_match_table = fsl_sai_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(fsl_sai_driver);

MODULE_DESCRIPTION("Freescale Soc SAI Interface");
MODULE_AUTHOR("Xiubo Li, <Li.Xiubo@freescale.com>");
MODULE_ALIAS("platform:fsl-sai");
MODULE_LICENSE("GPL");
