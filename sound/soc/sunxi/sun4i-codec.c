<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 Emilio Lथकpez <emilio@elopez.com.ar>
 * Copyright 2014 Jon Smirl <jonsmirl@gmail.com>
 * Copyright 2015 Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 * Copyright 2015 Adam Sampson <ats@offog.org>
 * Copyright 2016 Chen-Yu Tsai <wens@csie.org>
 *
 * Based on the Allwinner SDK driver, released under the GPL.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/initval.h>
#समावेश <sound/dmaengine_pcm.h>

/* Codec DAC digital controls and FIFO रेजिस्टरs */
#घोषणा SUN4I_CODEC_DAC_DPC			(0x00)
#घोषणा SUN4I_CODEC_DAC_DPC_EN_DA			(31)
#घोषणा SUN4I_CODEC_DAC_DPC_DVOL			(12)
#घोषणा SUN4I_CODEC_DAC_FIFOC			(0x04)
#घोषणा SUN4I_CODEC_DAC_FIFOC_DAC_FS			(29)
#घोषणा SUN4I_CODEC_DAC_FIFOC_FIR_VERSION		(28)
#घोषणा SUN4I_CODEC_DAC_FIFOC_SEND_LASAT		(26)
#घोषणा SUN4I_CODEC_DAC_FIFOC_TX_FIFO_MODE		(24)
#घोषणा SUN4I_CODEC_DAC_FIFOC_DRQ_CLR_CNT		(21)
#घोषणा SUN4I_CODEC_DAC_FIFOC_TX_TRIG_LEVEL		(8)
#घोषणा SUN4I_CODEC_DAC_FIFOC_MONO_EN			(6)
#घोषणा SUN4I_CODEC_DAC_FIFOC_TX_SAMPLE_BITS		(5)
#घोषणा SUN4I_CODEC_DAC_FIFOC_DAC_DRQ_EN		(4)
#घोषणा SUN4I_CODEC_DAC_FIFOC_FIFO_FLUSH		(0)
#घोषणा SUN4I_CODEC_DAC_FIFOS			(0x08)
#घोषणा SUN4I_CODEC_DAC_TXDATA			(0x0c)

/* Codec DAC side analog संकेत controls */
#घोषणा SUN4I_CODEC_DAC_ACTL			(0x10)
#घोषणा SUN4I_CODEC_DAC_ACTL_DACAENR			(31)
#घोषणा SUN4I_CODEC_DAC_ACTL_DACAENL			(30)
#घोषणा SUN4I_CODEC_DAC_ACTL_MIXEN			(29)
#घोषणा SUN4I_CODEC_DAC_ACTL_LNG			(26)
#घोषणा SUN4I_CODEC_DAC_ACTL_FMG			(23)
#घोषणा SUN4I_CODEC_DAC_ACTL_MICG			(20)
#घोषणा SUN4I_CODEC_DAC_ACTL_LLNS			(19)
#घोषणा SUN4I_CODEC_DAC_ACTL_RLNS			(18)
#घोषणा SUN4I_CODEC_DAC_ACTL_LFMS			(17)
#घोषणा SUN4I_CODEC_DAC_ACTL_RFMS			(16)
#घोषणा SUN4I_CODEC_DAC_ACTL_LDACLMIXS			(15)
#घोषणा SUN4I_CODEC_DAC_ACTL_RDACRMIXS			(14)
#घोषणा SUN4I_CODEC_DAC_ACTL_LDACRMIXS			(13)
#घोषणा SUN4I_CODEC_DAC_ACTL_MIC1LS			(12)
#घोषणा SUN4I_CODEC_DAC_ACTL_MIC1RS			(11)
#घोषणा SUN4I_CODEC_DAC_ACTL_MIC2LS			(10)
#घोषणा SUN4I_CODEC_DAC_ACTL_MIC2RS			(9)
#घोषणा SUN4I_CODEC_DAC_ACTL_DACPAS			(8)
#घोषणा SUN4I_CODEC_DAC_ACTL_MIXPAS			(7)
#घोषणा SUN4I_CODEC_DAC_ACTL_PA_MUTE			(6)
#घोषणा SUN4I_CODEC_DAC_ACTL_PA_VOL			(0)
#घोषणा SUN4I_CODEC_DAC_TUNE			(0x14)
#घोषणा SUN4I_CODEC_DAC_DEBUG			(0x18)

/* Codec ADC digital controls and FIFO रेजिस्टरs */
#घोषणा SUN4I_CODEC_ADC_FIFOC			(0x1c)
#घोषणा SUN4I_CODEC_ADC_FIFOC_ADC_FS			(29)
#घोषणा SUN4I_CODEC_ADC_FIFOC_EN_AD			(28)
#घोषणा SUN4I_CODEC_ADC_FIFOC_RX_FIFO_MODE		(24)
#घोषणा SUN4I_CODEC_ADC_FIFOC_RX_TRIG_LEVEL		(8)
#घोषणा SUN4I_CODEC_ADC_FIFOC_MONO_EN			(7)
#घोषणा SUN4I_CODEC_ADC_FIFOC_RX_SAMPLE_BITS		(6)
#घोषणा SUN4I_CODEC_ADC_FIFOC_ADC_DRQ_EN		(4)
#घोषणा SUN4I_CODEC_ADC_FIFOC_FIFO_FLUSH		(0)
#घोषणा SUN4I_CODEC_ADC_FIFOS			(0x20)
#घोषणा SUN4I_CODEC_ADC_RXDATA			(0x24)

/* Codec ADC side analog संकेत controls */
#घोषणा SUN4I_CODEC_ADC_ACTL			(0x28)
#घोषणा SUN4I_CODEC_ADC_ACTL_ADC_R_EN			(31)
#घोषणा SUN4I_CODEC_ADC_ACTL_ADC_L_EN			(30)
#घोषणा SUN4I_CODEC_ADC_ACTL_PREG1EN			(29)
#घोषणा SUN4I_CODEC_ADC_ACTL_PREG2EN			(28)
#घोषणा SUN4I_CODEC_ADC_ACTL_VMICEN			(27)
#घोषणा SUN4I_CODEC_ADC_ACTL_PREG1			(25)
#घोषणा SUN4I_CODEC_ADC_ACTL_PREG2			(23)
#घोषणा SUN4I_CODEC_ADC_ACTL_VADCG			(20)
#घोषणा SUN4I_CODEC_ADC_ACTL_ADCIS			(17)
#घोषणा SUN4I_CODEC_ADC_ACTL_LNPREG			(13)
#घोषणा SUN4I_CODEC_ADC_ACTL_PA_EN			(4)
#घोषणा SUN4I_CODEC_ADC_ACTL_DDE			(3)
#घोषणा SUN4I_CODEC_ADC_DEBUG			(0x2c)

/* FIFO counters */
#घोषणा SUN4I_CODEC_DAC_TXCNT			(0x30)
#घोषणा SUN4I_CODEC_ADC_RXCNT			(0x34)

/* Calibration रेजिस्टर (sun7i only) */
#घोषणा SUN7I_CODEC_AC_DAC_CAL			(0x38)

/* Microphone controls (sun7i only) */
#घोषणा SUN7I_CODEC_AC_MIC_PHONE_CAL		(0x3c)

#घोषणा SUN7I_CODEC_AC_MIC_PHONE_CAL_PREG1		(29)
#घोषणा SUN7I_CODEC_AC_MIC_PHONE_CAL_PREG2		(26)

/*
 * sun6i specअगरic रेजिस्टरs
 *
 * sun6i shares the same digital control and FIFO रेजिस्टरs as sun4i,
 * but only the DAC digital controls are at the same offset. The others
 * have been moved around to accommodate extra analog controls.
 */

/* Codec DAC digital controls and FIFO रेजिस्टरs */
#घोषणा SUN6I_CODEC_ADC_FIFOC			(0x10)
#घोषणा SUN6I_CODEC_ADC_FIFOC_EN_AD			(28)
#घोषणा SUN6I_CODEC_ADC_FIFOS			(0x14)
#घोषणा SUN6I_CODEC_ADC_RXDATA			(0x18)

/* Output mixer and gain controls */
#घोषणा SUN6I_CODEC_OM_DACA_CTRL		(0x20)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_DACAREN		(31)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_DACALEN		(30)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_RMIXEN			(29)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_LMIXEN			(28)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_RMIX_MIC1		(23)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_RMIX_MIC2		(22)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_RMIX_PHONE		(21)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_RMIX_PHONEP		(20)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_RMIX_LINEINR		(19)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_RMIX_DACR		(18)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_RMIX_DACL		(17)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_LMIX_MIC1		(16)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_LMIX_MIC2		(15)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_LMIX_PHONE		(14)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_LMIX_PHONEN		(13)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_LMIX_LINEINL		(12)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_LMIX_DACL		(11)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_LMIX_DACR		(10)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_RHPIS			(9)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_LHPIS			(8)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_RHPPAMUTE		(7)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_LHPPAMUTE		(6)
#घोषणा SUN6I_CODEC_OM_DACA_CTRL_HPVOL			(0)
#घोषणा SUN6I_CODEC_OM_PA_CTRL			(0x24)
#घोषणा SUN6I_CODEC_OM_PA_CTRL_HPPAEN			(31)
#घोषणा SUN6I_CODEC_OM_PA_CTRL_HPCOM_CTL		(29)
#घोषणा SUN6I_CODEC_OM_PA_CTRL_COMPTEN			(28)
#घोषणा SUN6I_CODEC_OM_PA_CTRL_MIC1G			(15)
#घोषणा SUN6I_CODEC_OM_PA_CTRL_MIC2G			(12)
#घोषणा SUN6I_CODEC_OM_PA_CTRL_LINEING			(9)
#घोषणा SUN6I_CODEC_OM_PA_CTRL_PHONEG			(6)
#घोषणा SUN6I_CODEC_OM_PA_CTRL_PHONEPG			(3)
#घोषणा SUN6I_CODEC_OM_PA_CTRL_PHONENG			(0)

/* Microphone, line out and phone out controls */
#घोषणा SUN6I_CODEC_MIC_CTRL			(0x28)
#घोषणा SUN6I_CODEC_MIC_CTRL_HBIASEN			(31)
#घोषणा SUN6I_CODEC_MIC_CTRL_MBIASEN			(30)
#घोषणा SUN6I_CODEC_MIC_CTRL_MIC1AMPEN			(28)
#घोषणा SUN6I_CODEC_MIC_CTRL_MIC1BOOST			(25)
#घोषणा SUN6I_CODEC_MIC_CTRL_MIC2AMPEN			(24)
#घोषणा SUN6I_CODEC_MIC_CTRL_MIC2BOOST			(21)
#घोषणा SUN6I_CODEC_MIC_CTRL_MIC2SLT			(20)
#घोषणा SUN6I_CODEC_MIC_CTRL_LINEOUTLEN			(19)
#घोषणा SUN6I_CODEC_MIC_CTRL_LINEOUTREN			(18)
#घोषणा SUN6I_CODEC_MIC_CTRL_LINEOUTLSRC		(17)
#घोषणा SUN6I_CODEC_MIC_CTRL_LINEOUTRSRC		(16)
#घोषणा SUN6I_CODEC_MIC_CTRL_LINEOUTVC			(11)
#घोषणा SUN6I_CODEC_MIC_CTRL_PHONEPREG			(8)

/* ADC mixer controls */
#घोषणा SUN6I_CODEC_ADC_ACTL			(0x2c)
#घोषणा SUN6I_CODEC_ADC_ACTL_ADCREN			(31)
#घोषणा SUN6I_CODEC_ADC_ACTL_ADCLEN			(30)
#घोषणा SUN6I_CODEC_ADC_ACTL_ADCRG			(27)
#घोषणा SUN6I_CODEC_ADC_ACTL_ADCLG			(24)
#घोषणा SUN6I_CODEC_ADC_ACTL_RADCMIX_MIC1		(13)
#घोषणा SUN6I_CODEC_ADC_ACTL_RADCMIX_MIC2		(12)
#घोषणा SUN6I_CODEC_ADC_ACTL_RADCMIX_PHONE		(11)
#घोषणा SUN6I_CODEC_ADC_ACTL_RADCMIX_PHONEP		(10)
#घोषणा SUN6I_CODEC_ADC_ACTL_RADCMIX_LINEINR		(9)
#घोषणा SUN6I_CODEC_ADC_ACTL_RADCMIX_OMIXR		(8)
#घोषणा SUN6I_CODEC_ADC_ACTL_RADCMIX_OMIXL		(7)
#घोषणा SUN6I_CODEC_ADC_ACTL_LADCMIX_MIC1		(6)
#घोषणा SUN6I_CODEC_ADC_ACTL_LADCMIX_MIC2		(5)
#घोषणा SUN6I_CODEC_ADC_ACTL_LADCMIX_PHONE		(4)
#घोषणा SUN6I_CODEC_ADC_ACTL_LADCMIX_PHONEN		(3)
#घोषणा SUN6I_CODEC_ADC_ACTL_LADCMIX_LINEINL		(2)
#घोषणा SUN6I_CODEC_ADC_ACTL_LADCMIX_OMIXL		(1)
#घोषणा SUN6I_CODEC_ADC_ACTL_LADCMIX_OMIXR		(0)

/* Analog perक्रमmance tuning controls */
#घोषणा SUN6I_CODEC_ADDA_TUNE			(0x30)

/* Calibration controls */
#घोषणा SUN6I_CODEC_CALIBRATION			(0x34)

/* FIFO counters */
#घोषणा SUN6I_CODEC_DAC_TXCNT			(0x40)
#घोषणा SUN6I_CODEC_ADC_RXCNT			(0x44)

/* headset jack detection and button support रेजिस्टरs */
#घोषणा SUN6I_CODEC_HMIC_CTL			(0x50)
#घोषणा SUN6I_CODEC_HMIC_DATA			(0x54)

/* TODO sun6i DAP (Digital Audio Processing) bits */

/* FIFO counters moved on A23 */
#घोषणा SUN8I_A23_CODEC_DAC_TXCNT		(0x1c)
#घोषणा SUN8I_A23_CODEC_ADC_RXCNT		(0x20)

/* TX FIFO moved on H3 */
#घोषणा SUN8I_H3_CODEC_DAC_TXDATA		(0x20)
#घोषणा SUN8I_H3_CODEC_DAC_DBG			(0x48)
#घोषणा SUN8I_H3_CODEC_ADC_DBG			(0x4c)

/* TODO H3 DAP (Digital Audio Processing) bits */

काष्ठा sun4i_codec अणु
	काष्ठा device	*dev;
	काष्ठा regmap	*regmap;
	काष्ठा clk	*clk_apb;
	काष्ठा clk	*clk_module;
	काष्ठा reset_control *rst;
	काष्ठा gpio_desc *gpio_pa;

	/* ADC_FIFOC रेजिस्टर is at dअगरferent offset on dअगरferent SoCs */
	काष्ठा regmap_field *reg_adc_fअगरoc;

	काष्ठा snd_dmaengine_dai_dma_data	capture_dma_data;
	काष्ठा snd_dmaengine_dai_dma_data	playback_dma_data;
पूर्ण;

अटल व्योम sun4i_codec_start_playback(काष्ठा sun4i_codec *scodec)
अणु
	/* Flush TX FIFO */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_FIFO_FLUSH),
			   BIT(SUN4I_CODEC_DAC_FIFOC_FIFO_FLUSH));

	/* Enable DAC DRQ */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_DAC_DRQ_EN),
			   BIT(SUN4I_CODEC_DAC_FIFOC_DAC_DRQ_EN));
पूर्ण

अटल व्योम sun4i_codec_stop_playback(काष्ठा sun4i_codec *scodec)
अणु
	/* Disable DAC DRQ */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_DAC_DRQ_EN),
			   0);
पूर्ण

अटल व्योम sun4i_codec_start_capture(काष्ठा sun4i_codec *scodec)
अणु
	/* Enable ADC DRQ */
	regmap_field_update_bits(scodec->reg_adc_fअगरoc,
				 BIT(SUN4I_CODEC_ADC_FIFOC_ADC_DRQ_EN),
				 BIT(SUN4I_CODEC_ADC_FIFOC_ADC_DRQ_EN));
पूर्ण

अटल व्योम sun4i_codec_stop_capture(काष्ठा sun4i_codec *scodec)
अणु
	/* Disable ADC DRQ */
	regmap_field_update_bits(scodec->reg_adc_fअगरoc,
				 BIT(SUN4I_CODEC_ADC_FIFOC_ADC_DRQ_EN), 0);
पूर्ण

अटल पूर्णांक sun4i_codec_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sun4i_codec *scodec = snd_soc_card_get_drvdata(rtd->card);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			sun4i_codec_start_playback(scodec);
		अन्यथा
			sun4i_codec_start_capture(scodec);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			sun4i_codec_stop_playback(scodec);
		अन्यथा
			sun4i_codec_stop_capture(scodec);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_codec_prepare_capture(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sun4i_codec *scodec = snd_soc_card_get_drvdata(rtd->card);


	/* Flush RX FIFO */
	regmap_field_update_bits(scodec->reg_adc_fअगरoc,
				 BIT(SUN4I_CODEC_ADC_FIFOC_FIFO_FLUSH),
				 BIT(SUN4I_CODEC_ADC_FIFOC_FIFO_FLUSH));


	/* Set RX FIFO trigger level */
	regmap_field_update_bits(scodec->reg_adc_fअगरoc,
				 0xf << SUN4I_CODEC_ADC_FIFOC_RX_TRIG_LEVEL,
				 0x7 << SUN4I_CODEC_ADC_FIFOC_RX_TRIG_LEVEL);

	/*
	 * FIXME: Unकरोcumented in the datasheet, but
	 *        Allwinner's code mentions that it is
	 *        related to microphone gain
	 */
	अगर (of_device_is_compatible(scodec->dev->of_node,
				    "allwinner,sun4i-a10-codec") ||
	    of_device_is_compatible(scodec->dev->of_node,
				    "allwinner,sun7i-a20-codec")) अणु
		regmap_update_bits(scodec->regmap, SUN4I_CODEC_ADC_ACTL,
				   0x3 << 25,
				   0x1 << 25);
	पूर्ण

	अगर (of_device_is_compatible(scodec->dev->of_node,
				    "allwinner,sun7i-a20-codec"))
		/* FIXME: Unकरोcumented bits */
		regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_TUNE,
				   0x3 << 8,
				   0x1 << 8);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_codec_prepare_playback(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sun4i_codec *scodec = snd_soc_card_get_drvdata(rtd->card);
	u32 val;

	/* Flush the TX FIFO */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_FIFO_FLUSH),
			   BIT(SUN4I_CODEC_DAC_FIFOC_FIFO_FLUSH));

	/* Set TX FIFO Empty Trigger Level */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   0x3f << SUN4I_CODEC_DAC_FIFOC_TX_TRIG_LEVEL,
			   0xf << SUN4I_CODEC_DAC_FIFOC_TX_TRIG_LEVEL);

	अगर (substream->runसमय->rate > 32000)
		/* Use 64 bits FIR filter */
		val = 0;
	अन्यथा
		/* Use 32 bits FIR filter */
		val = BIT(SUN4I_CODEC_DAC_FIFOC_FIR_VERSION);

	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_FIR_VERSION),
			   val);

	/* Send zeros when we have an underrun */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_SEND_LASAT),
			   0);

	वापस 0;
पूर्ण;

अटल पूर्णांक sun4i_codec_prepare(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस sun4i_codec_prepare_playback(substream, dai);

	वापस sun4i_codec_prepare_capture(substream, dai);
पूर्ण

अटल अचिन्हित दीर्घ sun4i_codec_get_mod_freq(काष्ठा snd_pcm_hw_params *params)
अणु
	अचिन्हित पूर्णांक rate = params_rate(params);

	चयन (rate) अणु
	हाल 176400:
	हाल 88200:
	हाल 44100:
	हाल 33075:
	हाल 22050:
	हाल 14700:
	हाल 11025:
	हाल 7350:
		वापस 22579200;

	हाल 192000:
	हाल 96000:
	हाल 48000:
	हाल 32000:
	हाल 24000:
	हाल 16000:
	हाल 12000:
	हाल 8000:
		वापस 24576000;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक sun4i_codec_get_hw_rate(काष्ठा snd_pcm_hw_params *params)
अणु
	अचिन्हित पूर्णांक rate = params_rate(params);

	चयन (rate) अणु
	हाल 192000:
	हाल 176400:
		वापस 6;

	हाल 96000:
	हाल 88200:
		वापस 7;

	हाल 48000:
	हाल 44100:
		वापस 0;

	हाल 32000:
	हाल 33075:
		वापस 1;

	हाल 24000:
	हाल 22050:
		वापस 2;

	हाल 16000:
	हाल 14700:
		वापस 3;

	हाल 12000:
	हाल 11025:
		वापस 4;

	हाल 8000:
	हाल 7350:
		वापस 5;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sun4i_codec_hw_params_capture(काष्ठा sun4i_codec *scodec,
					 काष्ठा snd_pcm_hw_params *params,
					 अचिन्हित पूर्णांक hwrate)
अणु
	/* Set ADC sample rate */
	regmap_field_update_bits(scodec->reg_adc_fअगरoc,
				 7 << SUN4I_CODEC_ADC_FIFOC_ADC_FS,
				 hwrate << SUN4I_CODEC_ADC_FIFOC_ADC_FS);

	/* Set the number of channels we want to use */
	अगर (params_channels(params) == 1)
		regmap_field_update_bits(scodec->reg_adc_fअगरoc,
					 BIT(SUN4I_CODEC_ADC_FIFOC_MONO_EN),
					 BIT(SUN4I_CODEC_ADC_FIFOC_MONO_EN));
	अन्यथा
		regmap_field_update_bits(scodec->reg_adc_fअगरoc,
					 BIT(SUN4I_CODEC_ADC_FIFOC_MONO_EN),
					 0);

	/* Set the number of sample bits to either 16 or 24 bits */
	अगर (hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_SAMPLE_BITS)->min == 32) अणु
		regmap_field_update_bits(scodec->reg_adc_fअगरoc,
				   BIT(SUN4I_CODEC_ADC_FIFOC_RX_SAMPLE_BITS),
				   BIT(SUN4I_CODEC_ADC_FIFOC_RX_SAMPLE_BITS));

		regmap_field_update_bits(scodec->reg_adc_fअगरoc,
				   BIT(SUN4I_CODEC_ADC_FIFOC_RX_FIFO_MODE),
				   0);

		scodec->capture_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	पूर्ण अन्यथा अणु
		regmap_field_update_bits(scodec->reg_adc_fअगरoc,
				   BIT(SUN4I_CODEC_ADC_FIFOC_RX_SAMPLE_BITS),
				   0);

		/* Fill most signअगरicant bits with valid data MSB */
		regmap_field_update_bits(scodec->reg_adc_fअगरoc,
				   BIT(SUN4I_CODEC_ADC_FIFOC_RX_FIFO_MODE),
				   BIT(SUN4I_CODEC_ADC_FIFOC_RX_FIFO_MODE));

		scodec->capture_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_codec_hw_params_playback(काष्ठा sun4i_codec *scodec,
					  काष्ठा snd_pcm_hw_params *params,
					  अचिन्हित पूर्णांक hwrate)
अणु
	u32 val;

	/* Set DAC sample rate */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   7 << SUN4I_CODEC_DAC_FIFOC_DAC_FS,
			   hwrate << SUN4I_CODEC_DAC_FIFOC_DAC_FS);

	/* Set the number of channels we want to use */
	अगर (params_channels(params) == 1)
		val = BIT(SUN4I_CODEC_DAC_FIFOC_MONO_EN);
	अन्यथा
		val = 0;

	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_MONO_EN),
			   val);

	/* Set the number of sample bits to either 16 or 24 bits */
	अगर (hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_SAMPLE_BITS)->min == 32) अणु
		regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_SAMPLE_BITS),
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_SAMPLE_BITS));

		/* Set TX FIFO mode to padding the LSBs with 0 */
		regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_FIFO_MODE),
				   0);

		scodec->playback_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	पूर्ण अन्यथा अणु
		regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_SAMPLE_BITS),
				   0);

		/* Set TX FIFO mode to repeat the MSB */
		regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_FIFO_MODE),
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_FIFO_MODE));

		scodec->playback_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_codec_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sun4i_codec *scodec = snd_soc_card_get_drvdata(rtd->card);
	अचिन्हित दीर्घ clk_freq;
	पूर्णांक ret, hwrate;

	clk_freq = sun4i_codec_get_mod_freq(params);
	अगर (!clk_freq)
		वापस -EINVAL;

	ret = clk_set_rate(scodec->clk_module, clk_freq);
	अगर (ret)
		वापस ret;

	hwrate = sun4i_codec_get_hw_rate(params);
	अगर (hwrate < 0)
		वापस hwrate;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस sun4i_codec_hw_params_playback(scodec, params,
						      hwrate);

	वापस sun4i_codec_hw_params_capture(scodec, params,
					     hwrate);
पूर्ण


अटल अचिन्हित पूर्णांक sun4i_codec_src_rates[] = अणु
	8000, 11025, 12000, 16000, 22050, 24000, 32000,
	44100, 48000, 96000, 192000
पूर्ण;


अटल काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list sun4i_codec_स्थिरraपूर्णांकs = अणु
	.count  = ARRAY_SIZE(sun4i_codec_src_rates),
	.list   = sun4i_codec_src_rates,
पूर्ण;


अटल पूर्णांक sun4i_codec_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sun4i_codec *scodec = snd_soc_card_get_drvdata(rtd->card);

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE, &sun4i_codec_स्थिरraपूर्णांकs);

	/*
	 * Stop issuing DRQ when we have room क्रम less than 16 samples
	 * in our TX FIFO
	 */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   3 << SUN4I_CODEC_DAC_FIFOC_DRQ_CLR_CNT,
			   3 << SUN4I_CODEC_DAC_FIFOC_DRQ_CLR_CNT);

	वापस clk_prepare_enable(scodec->clk_module);
पूर्ण

अटल व्योम sun4i_codec_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sun4i_codec *scodec = snd_soc_card_get_drvdata(rtd->card);

	clk_disable_unprepare(scodec->clk_module);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops sun4i_codec_dai_ops = अणु
	.startup	= sun4i_codec_startup,
	.shutकरोwn	= sun4i_codec_shutकरोwn,
	.trigger	= sun4i_codec_trigger,
	.hw_params	= sun4i_codec_hw_params,
	.prepare	= sun4i_codec_prepare,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sun4i_codec_dai = अणु
	.name	= "Codec",
	.ops	= &sun4i_codec_dai_ops,
	.playback = अणु
		.stream_name	= "Codec Playback",
		.channels_min	= 1,
		.channels_max	= 2,
		.rate_min	= 8000,
		.rate_max	= 192000,
		.rates		= SNDRV_PCM_RATE_CONTINUOUS,
		.क्रमmats	= SNDRV_PCM_FMTBIT_S16_LE |
				  SNDRV_PCM_FMTBIT_S32_LE,
		.sig_bits	= 24,
	पूर्ण,
	.capture = अणु
		.stream_name	= "Codec Capture",
		.channels_min	= 1,
		.channels_max	= 2,
		.rate_min	= 8000,
		.rate_max	= 48000,
		.rates		= SNDRV_PCM_RATE_CONTINUOUS,
		.क्रमmats	= SNDRV_PCM_FMTBIT_S16_LE |
				  SNDRV_PCM_FMTBIT_S32_LE,
		.sig_bits	= 24,
	पूर्ण,
पूर्ण;

/*** sun4i Codec ***/
अटल स्थिर काष्ठा snd_kcontrol_new sun4i_codec_pa_mute =
	SOC_DAPM_SINGLE("Switch", SUN4I_CODEC_DAC_ACTL,
			SUN4I_CODEC_DAC_ACTL_PA_MUTE, 1, 0);

अटल DECLARE_TLV_DB_SCALE(sun4i_codec_pa_volume_scale, -6300, 100, 1);
अटल DECLARE_TLV_DB_SCALE(sun4i_codec_linein_loopback_gain_scale, -150, 150,
			    0);
अटल DECLARE_TLV_DB_SCALE(sun4i_codec_linein_preamp_gain_scale, -1200, 300,
			    0);
अटल DECLARE_TLV_DB_SCALE(sun4i_codec_fmin_loopback_gain_scale, -450, 150,
			    0);
अटल DECLARE_TLV_DB_SCALE(sun4i_codec_micin_loopback_gain_scale, -450, 150,
			    0);
अटल DECLARE_TLV_DB_RANGE(sun4i_codec_micin_preamp_gain_scale,
			    0, 0, TLV_DB_SCALE_ITEM(0, 0, 0),
			    1, 7, TLV_DB_SCALE_ITEM(3500, 300, 0));
अटल DECLARE_TLV_DB_RANGE(sun7i_codec_micin_preamp_gain_scale,
			    0, 0, TLV_DB_SCALE_ITEM(0, 0, 0),
			    1, 7, TLV_DB_SCALE_ITEM(2400, 300, 0));

अटल स्थिर काष्ठा snd_kcontrol_new sun4i_codec_controls[] = अणु
	SOC_SINGLE_TLV("Power Amplifier Volume", SUN4I_CODEC_DAC_ACTL,
		       SUN4I_CODEC_DAC_ACTL_PA_VOL, 0x3F, 0,
		       sun4i_codec_pa_volume_scale),
	SOC_SINGLE_TLV("Line Playback Volume", SUN4I_CODEC_DAC_ACTL,
		       SUN4I_CODEC_DAC_ACTL_LNG, 1, 0,
		       sun4i_codec_linein_loopback_gain_scale),
	SOC_SINGLE_TLV("Line Boost Volume", SUN4I_CODEC_ADC_ACTL,
		       SUN4I_CODEC_ADC_ACTL_LNPREG, 7, 0,
		       sun4i_codec_linein_preamp_gain_scale),
	SOC_SINGLE_TLV("FM Playback Volume", SUN4I_CODEC_DAC_ACTL,
		       SUN4I_CODEC_DAC_ACTL_FMG, 3, 0,
		       sun4i_codec_fmin_loopback_gain_scale),
	SOC_SINGLE_TLV("Mic Playback Volume", SUN4I_CODEC_DAC_ACTL,
		       SUN4I_CODEC_DAC_ACTL_MICG, 7, 0,
		       sun4i_codec_micin_loopback_gain_scale),
	SOC_SINGLE_TLV("Mic1 Boost Volume", SUN4I_CODEC_ADC_ACTL,
		       SUN4I_CODEC_ADC_ACTL_PREG1, 3, 0,
		       sun4i_codec_micin_preamp_gain_scale),
	SOC_SINGLE_TLV("Mic2 Boost Volume", SUN4I_CODEC_ADC_ACTL,
		       SUN4I_CODEC_ADC_ACTL_PREG2, 3, 0,
		       sun4i_codec_micin_preamp_gain_scale),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sun7i_codec_controls[] = अणु
	SOC_SINGLE_TLV("Power Amplifier Volume", SUN4I_CODEC_DAC_ACTL,
		       SUN4I_CODEC_DAC_ACTL_PA_VOL, 0x3F, 0,
		       sun4i_codec_pa_volume_scale),
	SOC_SINGLE_TLV("Line Playback Volume", SUN4I_CODEC_DAC_ACTL,
		       SUN4I_CODEC_DAC_ACTL_LNG, 1, 0,
		       sun4i_codec_linein_loopback_gain_scale),
	SOC_SINGLE_TLV("Line Boost Volume", SUN4I_CODEC_ADC_ACTL,
		       SUN4I_CODEC_ADC_ACTL_LNPREG, 7, 0,
		       sun4i_codec_linein_preamp_gain_scale),
	SOC_SINGLE_TLV("FM Playback Volume", SUN4I_CODEC_DAC_ACTL,
		       SUN4I_CODEC_DAC_ACTL_FMG, 3, 0,
		       sun4i_codec_fmin_loopback_gain_scale),
	SOC_SINGLE_TLV("Mic Playback Volume", SUN4I_CODEC_DAC_ACTL,
		       SUN4I_CODEC_DAC_ACTL_MICG, 7, 0,
		       sun4i_codec_micin_loopback_gain_scale),
	SOC_SINGLE_TLV("Mic1 Boost Volume", SUN7I_CODEC_AC_MIC_PHONE_CAL,
		       SUN7I_CODEC_AC_MIC_PHONE_CAL_PREG1, 7, 0,
		       sun7i_codec_micin_preamp_gain_scale),
	SOC_SINGLE_TLV("Mic2 Boost Volume", SUN7I_CODEC_AC_MIC_PHONE_CAL,
		       SUN7I_CODEC_AC_MIC_PHONE_CAL_PREG2, 7, 0,
		       sun7i_codec_micin_preamp_gain_scale),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sun4i_codec_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left Mixer Left DAC Playback Switch",
			SUN4I_CODEC_DAC_ACTL, SUN4I_CODEC_DAC_ACTL_LDACLMIXS,
			1, 0),
	SOC_DAPM_SINGLE("Right Mixer Right DAC Playback Switch",
			SUN4I_CODEC_DAC_ACTL, SUN4I_CODEC_DAC_ACTL_RDACRMIXS,
			1, 0),
	SOC_DAPM_SINGLE("Right Mixer Left DAC Playback Switch",
			SUN4I_CODEC_DAC_ACTL,
			SUN4I_CODEC_DAC_ACTL_LDACRMIXS, 1, 0),
	SOC_DAPM_DOUBLE("Line Playback Switch", SUN4I_CODEC_DAC_ACTL,
			SUN4I_CODEC_DAC_ACTL_LLNS,
			SUN4I_CODEC_DAC_ACTL_RLNS, 1, 0),
	SOC_DAPM_DOUBLE("FM Playback Switch", SUN4I_CODEC_DAC_ACTL,
			SUN4I_CODEC_DAC_ACTL_LFMS,
			SUN4I_CODEC_DAC_ACTL_RFMS, 1, 0),
	SOC_DAPM_DOUBLE("Mic1 Playback Switch", SUN4I_CODEC_DAC_ACTL,
			SUN4I_CODEC_DAC_ACTL_MIC1LS,
			SUN4I_CODEC_DAC_ACTL_MIC1RS, 1, 0),
	SOC_DAPM_DOUBLE("Mic2 Playback Switch", SUN4I_CODEC_DAC_ACTL,
			SUN4I_CODEC_DAC_ACTL_MIC2LS,
			SUN4I_CODEC_DAC_ACTL_MIC2RS, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sun4i_codec_pa_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DAC Playback Switch", SUN4I_CODEC_DAC_ACTL,
			SUN4I_CODEC_DAC_ACTL_DACPAS, 1, 0),
	SOC_DAPM_SINGLE("Mixer Playback Switch", SUN4I_CODEC_DAC_ACTL,
			SUN4I_CODEC_DAC_ACTL_MIXPAS, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun4i_codec_codec_dapm_widमाला_लो[] = अणु
	/* Digital parts of the ADCs */
	SND_SOC_DAPM_SUPPLY("ADC", SUN4I_CODEC_ADC_FIFOC,
			    SUN4I_CODEC_ADC_FIFOC_EN_AD, 0,
			    शून्य, 0),

	/* Digital parts of the DACs */
	SND_SOC_DAPM_SUPPLY("DAC", SUN4I_CODEC_DAC_DPC,
			    SUN4I_CODEC_DAC_DPC_EN_DA, 0,
			    शून्य, 0),

	/* Analog parts of the ADCs */
	SND_SOC_DAPM_ADC("Left ADC", "Codec Capture", SUN4I_CODEC_ADC_ACTL,
			 SUN4I_CODEC_ADC_ACTL_ADC_L_EN, 0),
	SND_SOC_DAPM_ADC("Right ADC", "Codec Capture", SUN4I_CODEC_ADC_ACTL,
			 SUN4I_CODEC_ADC_ACTL_ADC_R_EN, 0),

	/* Analog parts of the DACs */
	SND_SOC_DAPM_DAC("Left DAC", "Codec Playback", SUN4I_CODEC_DAC_ACTL,
			 SUN4I_CODEC_DAC_ACTL_DACAENL, 0),
	SND_SOC_DAPM_DAC("Right DAC", "Codec Playback", SUN4I_CODEC_DAC_ACTL,
			 SUN4I_CODEC_DAC_ACTL_DACAENR, 0),

	/* Mixers */
	SND_SOC_DAPM_MIXER("Left Mixer", SND_SOC_NOPM, 0, 0,
			   sun4i_codec_mixer_controls,
			   ARRAY_SIZE(sun4i_codec_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right Mixer", SND_SOC_NOPM, 0, 0,
			   sun4i_codec_mixer_controls,
			   ARRAY_SIZE(sun4i_codec_mixer_controls)),

	/* Global Mixer Enable */
	SND_SOC_DAPM_SUPPLY("Mixer Enable", SUN4I_CODEC_DAC_ACTL,
			    SUN4I_CODEC_DAC_ACTL_MIXEN, 0, शून्य, 0),

	/* VMIC */
	SND_SOC_DAPM_SUPPLY("VMIC", SUN4I_CODEC_ADC_ACTL,
			    SUN4I_CODEC_ADC_ACTL_VMICEN, 0, शून्य, 0),

	/* Mic Pre-Amplअगरiers */
	SND_SOC_DAPM_PGA("MIC1 Pre-Amplifier", SUN4I_CODEC_ADC_ACTL,
			 SUN4I_CODEC_ADC_ACTL_PREG1EN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MIC2 Pre-Amplifier", SUN4I_CODEC_ADC_ACTL,
			 SUN4I_CODEC_ADC_ACTL_PREG2EN, 0, शून्य, 0),

	/* Power Amplअगरier */
	SND_SOC_DAPM_MIXER("Power Amplifier", SUN4I_CODEC_ADC_ACTL,
			   SUN4I_CODEC_ADC_ACTL_PA_EN, 0,
			   sun4i_codec_pa_mixer_controls,
			   ARRAY_SIZE(sun4i_codec_pa_mixer_controls)),
	SND_SOC_DAPM_SWITCH("Power Amplifier Mute", SND_SOC_NOPM, 0, 0,
			    &sun4i_codec_pa_mute),

	SND_SOC_DAPM_INPUT("Line Right"),
	SND_SOC_DAPM_INPUT("Line Left"),
	SND_SOC_DAPM_INPUT("FM Right"),
	SND_SOC_DAPM_INPUT("FM Left"),
	SND_SOC_DAPM_INPUT("Mic1"),
	SND_SOC_DAPM_INPUT("Mic2"),

	SND_SOC_DAPM_OUTPUT("HP Right"),
	SND_SOC_DAPM_OUTPUT("HP Left"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sun4i_codec_codec_dapm_routes[] = अणु
	/* Left ADC / DAC Routes */
	अणु "Left ADC", शून्य, "ADC" पूर्ण,
	अणु "Left DAC", शून्य, "DAC" पूर्ण,

	/* Right ADC / DAC Routes */
	अणु "Right ADC", शून्य, "ADC" पूर्ण,
	अणु "Right DAC", शून्य, "DAC" पूर्ण,

	/* Right Mixer Routes */
	अणु "Right Mixer", शून्य, "Mixer Enable" पूर्ण,
	अणु "Right Mixer", "Right Mixer Left DAC Playback Switch", "Left DAC" पूर्ण,
	अणु "Right Mixer", "Right Mixer Right DAC Playback Switch", "Right DAC" पूर्ण,
	अणु "Right Mixer", "Line Playback Switch", "Line Right" पूर्ण,
	अणु "Right Mixer", "FM Playback Switch", "FM Right" पूर्ण,
	अणु "Right Mixer", "Mic1 Playback Switch", "MIC1 Pre-Amplifier" पूर्ण,
	अणु "Right Mixer", "Mic2 Playback Switch", "MIC2 Pre-Amplifier" पूर्ण,

	/* Left Mixer Routes */
	अणु "Left Mixer", शून्य, "Mixer Enable" पूर्ण,
	अणु "Left Mixer", "Left Mixer Left DAC Playback Switch", "Left DAC" पूर्ण,
	अणु "Left Mixer", "Line Playback Switch", "Line Left" पूर्ण,
	अणु "Left Mixer", "FM Playback Switch", "FM Left" पूर्ण,
	अणु "Left Mixer", "Mic1 Playback Switch", "MIC1 Pre-Amplifier" पूर्ण,
	अणु "Left Mixer", "Mic2 Playback Switch", "MIC2 Pre-Amplifier" पूर्ण,

	/* Power Amplअगरier Routes */
	अणु "Power Amplifier", "Mixer Playback Switch", "Left Mixer" पूर्ण,
	अणु "Power Amplifier", "Mixer Playback Switch", "Right Mixer" पूर्ण,
	अणु "Power Amplifier", "DAC Playback Switch", "Left DAC" पूर्ण,
	अणु "Power Amplifier", "DAC Playback Switch", "Right DAC" पूर्ण,

	/* Headphone Output Routes */
	अणु "Power Amplifier Mute", "Switch", "Power Amplifier" पूर्ण,
	अणु "HP Right", शून्य, "Power Amplifier Mute" पूर्ण,
	अणु "HP Left", शून्य, "Power Amplifier Mute" पूर्ण,

	/* Mic1 Routes */
	अणु "Left ADC", शून्य, "MIC1 Pre-Amplifier" पूर्ण,
	अणु "Right ADC", शून्य, "MIC1 Pre-Amplifier" पूर्ण,
	अणु "MIC1 Pre-Amplifier", शून्य, "Mic1"पूर्ण,
	अणु "Mic1", शून्य, "VMIC" पूर्ण,

	/* Mic2 Routes */
	अणु "Left ADC", शून्य, "MIC2 Pre-Amplifier" पूर्ण,
	अणु "Right ADC", शून्य, "MIC2 Pre-Amplifier" पूर्ण,
	अणु "MIC2 Pre-Amplifier", शून्य, "Mic2"पूर्ण,
	अणु "Mic2", शून्य, "VMIC" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sun4i_codec_codec = अणु
	.controls		= sun4i_codec_controls,
	.num_controls		= ARRAY_SIZE(sun4i_codec_controls),
	.dapm_widमाला_लो		= sun4i_codec_codec_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(sun4i_codec_codec_dapm_widमाला_लो),
	.dapm_routes		= sun4i_codec_codec_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(sun4i_codec_codec_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sun7i_codec_codec = अणु
	.controls		= sun7i_codec_controls,
	.num_controls		= ARRAY_SIZE(sun7i_codec_controls),
	.dapm_widमाला_लो		= sun4i_codec_codec_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(sun4i_codec_codec_dapm_widमाला_लो),
	.dapm_routes		= sun4i_codec_codec_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(sun4i_codec_codec_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

/*** sun6i Codec ***/

/* mixer controls */
अटल स्थिर काष्ठा snd_kcontrol_new sun6i_codec_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE("DAC Playback Switch",
			SUN6I_CODEC_OM_DACA_CTRL,
			SUN6I_CODEC_OM_DACA_CTRL_LMIX_DACL,
			SUN6I_CODEC_OM_DACA_CTRL_RMIX_DACR, 1, 0),
	SOC_DAPM_DOUBLE("DAC Reversed Playback Switch",
			SUN6I_CODEC_OM_DACA_CTRL,
			SUN6I_CODEC_OM_DACA_CTRL_LMIX_DACR,
			SUN6I_CODEC_OM_DACA_CTRL_RMIX_DACL, 1, 0),
	SOC_DAPM_DOUBLE("Line In Playback Switch",
			SUN6I_CODEC_OM_DACA_CTRL,
			SUN6I_CODEC_OM_DACA_CTRL_LMIX_LINEINL,
			SUN6I_CODEC_OM_DACA_CTRL_RMIX_LINEINR, 1, 0),
	SOC_DAPM_DOUBLE("Mic1 Playback Switch",
			SUN6I_CODEC_OM_DACA_CTRL,
			SUN6I_CODEC_OM_DACA_CTRL_LMIX_MIC1,
			SUN6I_CODEC_OM_DACA_CTRL_RMIX_MIC1, 1, 0),
	SOC_DAPM_DOUBLE("Mic2 Playback Switch",
			SUN6I_CODEC_OM_DACA_CTRL,
			SUN6I_CODEC_OM_DACA_CTRL_LMIX_MIC2,
			SUN6I_CODEC_OM_DACA_CTRL_RMIX_MIC2, 1, 0),
पूर्ण;

/* ADC mixer controls */
अटल स्थिर काष्ठा snd_kcontrol_new sun6i_codec_adc_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE("Mixer Capture Switch",
			SUN6I_CODEC_ADC_ACTL,
			SUN6I_CODEC_ADC_ACTL_LADCMIX_OMIXL,
			SUN6I_CODEC_ADC_ACTL_RADCMIX_OMIXR, 1, 0),
	SOC_DAPM_DOUBLE("Mixer Reversed Capture Switch",
			SUN6I_CODEC_ADC_ACTL,
			SUN6I_CODEC_ADC_ACTL_LADCMIX_OMIXR,
			SUN6I_CODEC_ADC_ACTL_RADCMIX_OMIXL, 1, 0),
	SOC_DAPM_DOUBLE("Line In Capture Switch",
			SUN6I_CODEC_ADC_ACTL,
			SUN6I_CODEC_ADC_ACTL_LADCMIX_LINEINL,
			SUN6I_CODEC_ADC_ACTL_RADCMIX_LINEINR, 1, 0),
	SOC_DAPM_DOUBLE("Mic1 Capture Switch",
			SUN6I_CODEC_ADC_ACTL,
			SUN6I_CODEC_ADC_ACTL_LADCMIX_MIC1,
			SUN6I_CODEC_ADC_ACTL_RADCMIX_MIC1, 1, 0),
	SOC_DAPM_DOUBLE("Mic2 Capture Switch",
			SUN6I_CODEC_ADC_ACTL,
			SUN6I_CODEC_ADC_ACTL_LADCMIX_MIC2,
			SUN6I_CODEC_ADC_ACTL_RADCMIX_MIC2, 1, 0),
पूर्ण;

/* headphone controls */
अटल स्थिर अक्षर * स्थिर sun6i_codec_hp_src_क्रमागत_text[] = अणु
	"DAC", "Mixer",
पूर्ण;

अटल SOC_ENUM_DOUBLE_DECL(sun6i_codec_hp_src_क्रमागत,
			    SUN6I_CODEC_OM_DACA_CTRL,
			    SUN6I_CODEC_OM_DACA_CTRL_LHPIS,
			    SUN6I_CODEC_OM_DACA_CTRL_RHPIS,
			    sun6i_codec_hp_src_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new sun6i_codec_hp_src[] = अणु
	SOC_DAPM_ENUM("Headphone Source Playback Route",
		      sun6i_codec_hp_src_क्रमागत),
पूर्ण;

/* microphone controls */
अटल स्थिर अक्षर * स्थिर sun6i_codec_mic2_src_क्रमागत_text[] = अणु
	"Mic2", "Mic3",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(sun6i_codec_mic2_src_क्रमागत,
			    SUN6I_CODEC_MIC_CTRL,
			    SUN6I_CODEC_MIC_CTRL_MIC2SLT,
			    sun6i_codec_mic2_src_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new sun6i_codec_mic2_src[] = अणु
	SOC_DAPM_ENUM("Mic2 Amplifier Source Route",
		      sun6i_codec_mic2_src_क्रमागत),
पूर्ण;

/* line out controls */
अटल स्थिर अक्षर * स्थिर sun6i_codec_lineout_src_क्रमागत_text[] = अणु
	"Stereo", "Mono Differential",
पूर्ण;

अटल SOC_ENUM_DOUBLE_DECL(sun6i_codec_lineout_src_क्रमागत,
			    SUN6I_CODEC_MIC_CTRL,
			    SUN6I_CODEC_MIC_CTRL_LINEOUTLSRC,
			    SUN6I_CODEC_MIC_CTRL_LINEOUTRSRC,
			    sun6i_codec_lineout_src_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new sun6i_codec_lineout_src[] = अणु
	SOC_DAPM_ENUM("Line Out Source Playback Route",
		      sun6i_codec_lineout_src_क्रमागत),
पूर्ण;

/* volume / mute controls */
अटल स्थिर DECLARE_TLV_DB_SCALE(sun6i_codec_dvol_scale, -7308, 116, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(sun6i_codec_hp_vol_scale, -6300, 100, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(sun6i_codec_out_mixer_pregain_scale,
				  -450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_RANGE(sun6i_codec_lineout_vol_scale,
	0, 1, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 1),
	2, 31, TLV_DB_SCALE_ITEM(-4350, 150, 0),
);
अटल स्थिर DECLARE_TLV_DB_RANGE(sun6i_codec_mic_gain_scale,
	0, 0, TLV_DB_SCALE_ITEM(0, 0, 0),
	1, 7, TLV_DB_SCALE_ITEM(2400, 300, 0),
);

अटल स्थिर काष्ठा snd_kcontrol_new sun6i_codec_codec_widमाला_लो[] = अणु
	SOC_SINGLE_TLV("DAC Playback Volume", SUN4I_CODEC_DAC_DPC,
		       SUN4I_CODEC_DAC_DPC_DVOL, 0x3f, 1,
		       sun6i_codec_dvol_scale),
	SOC_SINGLE_TLV("Headphone Playback Volume",
		       SUN6I_CODEC_OM_DACA_CTRL,
		       SUN6I_CODEC_OM_DACA_CTRL_HPVOL, 0x3f, 0,
		       sun6i_codec_hp_vol_scale),
	SOC_SINGLE_TLV("Line Out Playback Volume",
		       SUN6I_CODEC_MIC_CTRL,
		       SUN6I_CODEC_MIC_CTRL_LINEOUTVC, 0x1f, 0,
		       sun6i_codec_lineout_vol_scale),
	SOC_DOUBLE("Headphone Playback Switch",
		   SUN6I_CODEC_OM_DACA_CTRL,
		   SUN6I_CODEC_OM_DACA_CTRL_LHPPAMUTE,
		   SUN6I_CODEC_OM_DACA_CTRL_RHPPAMUTE, 1, 0),
	SOC_DOUBLE("Line Out Playback Switch",
		   SUN6I_CODEC_MIC_CTRL,
		   SUN6I_CODEC_MIC_CTRL_LINEOUTLEN,
		   SUN6I_CODEC_MIC_CTRL_LINEOUTREN, 1, 0),
	/* Mixer pre-gains */
	SOC_SINGLE_TLV("Line In Playback Volume",
		       SUN6I_CODEC_OM_PA_CTRL, SUN6I_CODEC_OM_PA_CTRL_LINEING,
		       0x7, 0, sun6i_codec_out_mixer_pregain_scale),
	SOC_SINGLE_TLV("Mic1 Playback Volume",
		       SUN6I_CODEC_OM_PA_CTRL, SUN6I_CODEC_OM_PA_CTRL_MIC1G,
		       0x7, 0, sun6i_codec_out_mixer_pregain_scale),
	SOC_SINGLE_TLV("Mic2 Playback Volume",
		       SUN6I_CODEC_OM_PA_CTRL, SUN6I_CODEC_OM_PA_CTRL_MIC2G,
		       0x7, 0, sun6i_codec_out_mixer_pregain_scale),

	/* Microphone Amp boost gains */
	SOC_SINGLE_TLV("Mic1 Boost Volume", SUN6I_CODEC_MIC_CTRL,
		       SUN6I_CODEC_MIC_CTRL_MIC1BOOST, 0x7, 0,
		       sun6i_codec_mic_gain_scale),
	SOC_SINGLE_TLV("Mic2 Boost Volume", SUN6I_CODEC_MIC_CTRL,
		       SUN6I_CODEC_MIC_CTRL_MIC2BOOST, 0x7, 0,
		       sun6i_codec_mic_gain_scale),
	SOC_DOUBLE_TLV("ADC Capture Volume",
		       SUN6I_CODEC_ADC_ACTL, SUN6I_CODEC_ADC_ACTL_ADCLG,
		       SUN6I_CODEC_ADC_ACTL_ADCRG, 0x7, 0,
		       sun6i_codec_out_mixer_pregain_scale),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun6i_codec_codec_dapm_widमाला_लो[] = अणु
	/* Microphone inमाला_दो */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("MIC3"),

	/* Microphone Bias */
	SND_SOC_DAPM_SUPPLY("HBIAS", SUN6I_CODEC_MIC_CTRL,
			    SUN6I_CODEC_MIC_CTRL_HBIASEN, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MBIAS", SUN6I_CODEC_MIC_CTRL,
			    SUN6I_CODEC_MIC_CTRL_MBIASEN, 0, शून्य, 0),

	/* Mic input path */
	SND_SOC_DAPM_MUX("Mic2 Amplifier Source Route",
			 SND_SOC_NOPM, 0, 0, sun6i_codec_mic2_src),
	SND_SOC_DAPM_PGA("Mic1 Amplifier", SUN6I_CODEC_MIC_CTRL,
			 SUN6I_CODEC_MIC_CTRL_MIC1AMPEN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mic2 Amplifier", SUN6I_CODEC_MIC_CTRL,
			 SUN6I_CODEC_MIC_CTRL_MIC2AMPEN, 0, शून्य, 0),

	/* Line In */
	SND_SOC_DAPM_INPUT("LINEIN"),

	/* Digital parts of the ADCs */
	SND_SOC_DAPM_SUPPLY("ADC Enable", SUN6I_CODEC_ADC_FIFOC,
			    SUN6I_CODEC_ADC_FIFOC_EN_AD, 0,
			    शून्य, 0),

	/* Analog parts of the ADCs */
	SND_SOC_DAPM_ADC("Left ADC", "Codec Capture", SUN6I_CODEC_ADC_ACTL,
			 SUN6I_CODEC_ADC_ACTL_ADCLEN, 0),
	SND_SOC_DAPM_ADC("Right ADC", "Codec Capture", SUN6I_CODEC_ADC_ACTL,
			 SUN6I_CODEC_ADC_ACTL_ADCREN, 0),

	/* ADC Mixers */
	SOC_MIXER_ARRAY("Left ADC Mixer", SND_SOC_NOPM, 0, 0,
			sun6i_codec_adc_mixer_controls),
	SOC_MIXER_ARRAY("Right ADC Mixer", SND_SOC_NOPM, 0, 0,
			sun6i_codec_adc_mixer_controls),

	/* Digital parts of the DACs */
	SND_SOC_DAPM_SUPPLY("DAC Enable", SUN4I_CODEC_DAC_DPC,
			    SUN4I_CODEC_DAC_DPC_EN_DA, 0,
			    शून्य, 0),

	/* Analog parts of the DACs */
	SND_SOC_DAPM_DAC("Left DAC", "Codec Playback",
			 SUN6I_CODEC_OM_DACA_CTRL,
			 SUN6I_CODEC_OM_DACA_CTRL_DACALEN, 0),
	SND_SOC_DAPM_DAC("Right DAC", "Codec Playback",
			 SUN6I_CODEC_OM_DACA_CTRL,
			 SUN6I_CODEC_OM_DACA_CTRL_DACAREN, 0),

	/* Mixers */
	SOC_MIXER_ARRAY("Left Mixer", SUN6I_CODEC_OM_DACA_CTRL,
			SUN6I_CODEC_OM_DACA_CTRL_LMIXEN, 0,
			sun6i_codec_mixer_controls),
	SOC_MIXER_ARRAY("Right Mixer", SUN6I_CODEC_OM_DACA_CTRL,
			SUN6I_CODEC_OM_DACA_CTRL_RMIXEN, 0,
			sun6i_codec_mixer_controls),

	/* Headphone output path */
	SND_SOC_DAPM_MUX("Headphone Source Playback Route",
			 SND_SOC_NOPM, 0, 0, sun6i_codec_hp_src),
	SND_SOC_DAPM_OUT_DRV("Headphone Amp", SUN6I_CODEC_OM_PA_CTRL,
			     SUN6I_CODEC_OM_PA_CTRL_HPPAEN, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("HPCOM Protection", SUN6I_CODEC_OM_PA_CTRL,
			    SUN6I_CODEC_OM_PA_CTRL_COMPTEN, 0, शून्य, 0),
	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "HPCOM", SUN6I_CODEC_OM_PA_CTRL,
			 SUN6I_CODEC_OM_PA_CTRL_HPCOM_CTL, 0x3, 0x3, 0),
	SND_SOC_DAPM_OUTPUT("HP"),

	/* Line Out path */
	SND_SOC_DAPM_MUX("Line Out Source Playback Route",
			 SND_SOC_NOPM, 0, 0, sun6i_codec_lineout_src),
	SND_SOC_DAPM_OUTPUT("LINEOUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sun6i_codec_codec_dapm_routes[] = अणु
	/* DAC Routes */
	अणु "Left DAC", शून्य, "DAC Enable" पूर्ण,
	अणु "Right DAC", शून्य, "DAC Enable" पूर्ण,

	/* Microphone Routes */
	अणु "Mic1 Amplifier", शून्य, "MIC1"पूर्ण,
	अणु "Mic2 Amplifier Source Route", "Mic2", "MIC2" पूर्ण,
	अणु "Mic2 Amplifier Source Route", "Mic3", "MIC3" पूर्ण,
	अणु "Mic2 Amplifier", शून्य, "Mic2 Amplifier Source Route"पूर्ण,

	/* Left Mixer Routes */
	अणु "Left Mixer", "DAC Playback Switch", "Left DAC" पूर्ण,
	अणु "Left Mixer", "DAC Reversed Playback Switch", "Right DAC" पूर्ण,
	अणु "Left Mixer", "Line In Playback Switch", "LINEIN" पूर्ण,
	अणु "Left Mixer", "Mic1 Playback Switch", "Mic1 Amplifier" पूर्ण,
	अणु "Left Mixer", "Mic2 Playback Switch", "Mic2 Amplifier" पूर्ण,

	/* Right Mixer Routes */
	अणु "Right Mixer", "DAC Playback Switch", "Right DAC" पूर्ण,
	अणु "Right Mixer", "DAC Reversed Playback Switch", "Left DAC" पूर्ण,
	अणु "Right Mixer", "Line In Playback Switch", "LINEIN" पूर्ण,
	अणु "Right Mixer", "Mic1 Playback Switch", "Mic1 Amplifier" पूर्ण,
	अणु "Right Mixer", "Mic2 Playback Switch", "Mic2 Amplifier" पूर्ण,

	/* Left ADC Mixer Routes */
	अणु "Left ADC Mixer", "Mixer Capture Switch", "Left Mixer" पूर्ण,
	अणु "Left ADC Mixer", "Mixer Reversed Capture Switch", "Right Mixer" पूर्ण,
	अणु "Left ADC Mixer", "Line In Capture Switch", "LINEIN" पूर्ण,
	अणु "Left ADC Mixer", "Mic1 Capture Switch", "Mic1 Amplifier" पूर्ण,
	अणु "Left ADC Mixer", "Mic2 Capture Switch", "Mic2 Amplifier" पूर्ण,

	/* Right ADC Mixer Routes */
	अणु "Right ADC Mixer", "Mixer Capture Switch", "Right Mixer" पूर्ण,
	अणु "Right ADC Mixer", "Mixer Reversed Capture Switch", "Left Mixer" पूर्ण,
	अणु "Right ADC Mixer", "Line In Capture Switch", "LINEIN" पूर्ण,
	अणु "Right ADC Mixer", "Mic1 Capture Switch", "Mic1 Amplifier" पूर्ण,
	अणु "Right ADC Mixer", "Mic2 Capture Switch", "Mic2 Amplifier" पूर्ण,

	/* Headphone Routes */
	अणु "Headphone Source Playback Route", "DAC", "Left DAC" पूर्ण,
	अणु "Headphone Source Playback Route", "DAC", "Right DAC" पूर्ण,
	अणु "Headphone Source Playback Route", "Mixer", "Left Mixer" पूर्ण,
	अणु "Headphone Source Playback Route", "Mixer", "Right Mixer" पूर्ण,
	अणु "Headphone Amp", शून्य, "Headphone Source Playback Route" पूर्ण,
	अणु "HP", शून्य, "Headphone Amp" पूर्ण,
	अणु "HPCOM", शून्य, "HPCOM Protection" पूर्ण,

	/* Line Out Routes */
	अणु "Line Out Source Playback Route", "Stereo", "Left Mixer" पूर्ण,
	अणु "Line Out Source Playback Route", "Stereo", "Right Mixer" पूर्ण,
	अणु "Line Out Source Playback Route", "Mono Differential", "Left Mixer" पूर्ण,
	अणु "Line Out Source Playback Route", "Mono Differential", "Right Mixer" पूर्ण,
	अणु "LINEOUT", शून्य, "Line Out Source Playback Route" पूर्ण,

	/* ADC Routes */
	अणु "Left ADC", शून्य, "ADC Enable" पूर्ण,
	अणु "Right ADC", शून्य, "ADC Enable" पूर्ण,
	अणु "Left ADC", शून्य, "Left ADC Mixer" पूर्ण,
	अणु "Right ADC", शून्य, "Right ADC Mixer" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sun6i_codec_codec = अणु
	.controls		= sun6i_codec_codec_widमाला_लो,
	.num_controls		= ARRAY_SIZE(sun6i_codec_codec_widमाला_लो),
	.dapm_widमाला_लो		= sun6i_codec_codec_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(sun6i_codec_codec_dapm_widमाला_लो),
	.dapm_routes		= sun6i_codec_codec_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(sun6i_codec_codec_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

/* sun8i A23 codec */
अटल स्थिर काष्ठा snd_kcontrol_new sun8i_a23_codec_codec_controls[] = अणु
	SOC_SINGLE_TLV("DAC Playback Volume", SUN4I_CODEC_DAC_DPC,
		       SUN4I_CODEC_DAC_DPC_DVOL, 0x3f, 1,
		       sun6i_codec_dvol_scale),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun8i_a23_codec_codec_widमाला_लो[] = अणु
	/* Digital parts of the ADCs */
	SND_SOC_DAPM_SUPPLY("ADC Enable", SUN6I_CODEC_ADC_FIFOC,
			    SUN6I_CODEC_ADC_FIFOC_EN_AD, 0, शून्य, 0),
	/* Digital parts of the DACs */
	SND_SOC_DAPM_SUPPLY("DAC Enable", SUN4I_CODEC_DAC_DPC,
			    SUN4I_CODEC_DAC_DPC_EN_DA, 0, शून्य, 0),

पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sun8i_a23_codec_codec = अणु
	.controls		= sun8i_a23_codec_codec_controls,
	.num_controls		= ARRAY_SIZE(sun8i_a23_codec_codec_controls),
	.dapm_widमाला_लो		= sun8i_a23_codec_codec_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(sun8i_a23_codec_codec_widमाला_लो),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sun4i_codec_component = अणु
	.name = "sun4i-codec",
पूर्ण;

#घोषणा SUN4I_CODEC_RATES	SNDRV_PCM_RATE_CONTINUOUS
#घोषणा SUN4I_CODEC_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | \
				 SNDRV_PCM_FMTBIT_S32_LE)

अटल पूर्णांक sun4i_codec_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_card *card = snd_soc_dai_get_drvdata(dai);
	काष्ठा sun4i_codec *scodec = snd_soc_card_get_drvdata(card);

	snd_soc_dai_init_dma_data(dai, &scodec->playback_dma_data,
				  &scodec->capture_dma_data);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver dummy_cpu_dai = अणु
	.name	= "sun4i-codec-cpu-dai",
	.probe	= sun4i_codec_dai_probe,
	.playback = अणु
		.stream_name	= "Playback",
		.channels_min	= 1,
		.channels_max	= 2,
		.rates		= SUN4I_CODEC_RATES,
		.क्रमmats	= SUN4I_CODEC_FORMATS,
		.sig_bits	= 24,
	पूर्ण,
	.capture = अणु
		.stream_name	= "Capture",
		.channels_min	= 1,
		.channels_max	= 2,
		.rates 		= SUN4I_CODEC_RATES,
		.क्रमmats 	= SUN4I_CODEC_FORMATS,
		.sig_bits	= 24,
	 पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_link *sun4i_codec_create_link(काष्ठा device *dev,
							पूर्णांक *num_links)
अणु
	काष्ठा snd_soc_dai_link *link = devm_kzalloc(dev, माप(*link),
						     GFP_KERNEL);
	काष्ठा snd_soc_dai_link_component *dlc = devm_kzalloc(dev,
						3 * माप(*dlc), GFP_KERNEL);
	अगर (!link || !dlc)
		वापस शून्य;

	link->cpus	= &dlc[0];
	link->codecs	= &dlc[1];
	link->platक्रमms	= &dlc[2];

	link->num_cpus		= 1;
	link->num_codecs	= 1;
	link->num_platक्रमms	= 1;

	link->name		= "cdc";
	link->stream_name	= "CDC PCM";
	link->codecs->dai_name	= "Codec";
	link->cpus->dai_name	= dev_name(dev);
	link->codecs->name	= dev_name(dev);
	link->platक्रमms->name	= dev_name(dev);
	link->dai_fmt		= SND_SOC_DAIFMT_I2S;

	*num_links = 1;

	वापस link;
पूर्ण;

अटल पूर्णांक sun4i_codec_spk_event(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा sun4i_codec *scodec = snd_soc_card_get_drvdata(w->dapm->card);

	gpiod_set_value_cansleep(scodec->gpio_pa,
				 !!SND_SOC_DAPM_EVENT_ON(event));

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		/*
		 * Need a delay to रुको क्रम DAC to push the data. 700ms seems
		 * to be the best compromise not to feel this delay जबतक
		 * playing a sound.
		 */
		msleep(700);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget sun4i_codec_card_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Speaker", sun4i_codec_spk_event),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sun4i_codec_card_dapm_routes[] = अणु
	अणु "Speaker", शून्य, "HP Right" पूर्ण,
	अणु "Speaker", शून्य, "HP Left" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card *sun4i_codec_create_card(काष्ठा device *dev)
अणु
	काष्ठा snd_soc_card *card;

	card = devm_kzalloc(dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस ERR_PTR(-ENOMEM);

	card->dai_link = sun4i_codec_create_link(dev, &card->num_links);
	अगर (!card->dai_link)
		वापस ERR_PTR(-ENOMEM);

	card->dev		= dev;
	card->owner		= THIS_MODULE;
	card->name		= "sun4i-codec";
	card->dapm_widमाला_लो	= sun4i_codec_card_dapm_widमाला_लो;
	card->num_dapm_widमाला_लो	= ARRAY_SIZE(sun4i_codec_card_dapm_widमाला_लो);
	card->dapm_routes	= sun4i_codec_card_dapm_routes;
	card->num_dapm_routes	= ARRAY_SIZE(sun4i_codec_card_dapm_routes);

	वापस card;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun6i_codec_card_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_LINE("Line In", शून्य),
	SND_SOC_DAPM_LINE("Line Out", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Mic", शून्य),
	SND_SOC_DAPM_SPK("Speaker", sun4i_codec_spk_event),
पूर्ण;

अटल काष्ठा snd_soc_card *sun6i_codec_create_card(काष्ठा device *dev)
अणु
	काष्ठा snd_soc_card *card;
	पूर्णांक ret;

	card = devm_kzalloc(dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस ERR_PTR(-ENOMEM);

	card->dai_link = sun4i_codec_create_link(dev, &card->num_links);
	अगर (!card->dai_link)
		वापस ERR_PTR(-ENOMEM);

	card->dev		= dev;
	card->owner		= THIS_MODULE;
	card->name		= "A31 Audio Codec";
	card->dapm_widमाला_लो	= sun6i_codec_card_dapm_widमाला_लो;
	card->num_dapm_widमाला_लो	= ARRAY_SIZE(sun6i_codec_card_dapm_widमाला_लो);
	card->fully_routed	= true;

	ret = snd_soc_of_parse_audio_routing(card, "allwinner,audio-routing");
	अगर (ret)
		dev_warn(dev, "failed to parse audio-routing: %d\n", ret);

	वापस card;
पूर्ण;

/* Connect digital side enables to analog side widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_route sun8i_codec_card_routes[] = अणु
	/* ADC Routes */
	अणु "Left ADC", शून्य, "ADC Enable" पूर्ण,
	अणु "Right ADC", शून्य, "ADC Enable" पूर्ण,
	अणु "Codec Capture", शून्य, "Left ADC" पूर्ण,
	अणु "Codec Capture", शून्य, "Right ADC" पूर्ण,

	/* DAC Routes */
	अणु "Left DAC", शून्य, "DAC Enable" पूर्ण,
	अणु "Right DAC", शून्य, "DAC Enable" पूर्ण,
	अणु "Left DAC", शून्य, "Codec Playback" पूर्ण,
	अणु "Right DAC", शून्य, "Codec Playback" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_aux_dev aux_dev = अणु
	.dlc = COMP_EMPTY(),
पूर्ण;

अटल काष्ठा snd_soc_card *sun8i_a23_codec_create_card(काष्ठा device *dev)
अणु
	काष्ठा snd_soc_card *card;
	पूर्णांक ret;

	card = devm_kzalloc(dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस ERR_PTR(-ENOMEM);

	aux_dev.dlc.of_node = of_parse_phandle(dev->of_node,
						 "allwinner,codec-analog-controls",
						 0);
	अगर (!aux_dev.dlc.of_node) अणु
		dev_err(dev, "Can't find analog controls for codec.\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	card->dai_link = sun4i_codec_create_link(dev, &card->num_links);
	अगर (!card->dai_link)
		वापस ERR_PTR(-ENOMEM);

	card->dev		= dev;
	card->owner		= THIS_MODULE;
	card->name		= "A23 Audio Codec";
	card->dapm_widमाला_लो	= sun6i_codec_card_dapm_widमाला_लो;
	card->num_dapm_widमाला_लो	= ARRAY_SIZE(sun6i_codec_card_dapm_widमाला_लो);
	card->dapm_routes	= sun8i_codec_card_routes;
	card->num_dapm_routes	= ARRAY_SIZE(sun8i_codec_card_routes);
	card->aux_dev		= &aux_dev;
	card->num_aux_devs	= 1;
	card->fully_routed	= true;

	ret = snd_soc_of_parse_audio_routing(card, "allwinner,audio-routing");
	अगर (ret)
		dev_warn(dev, "failed to parse audio-routing: %d\n", ret);

	वापस card;
पूर्ण;

अटल काष्ठा snd_soc_card *sun8i_h3_codec_create_card(काष्ठा device *dev)
अणु
	काष्ठा snd_soc_card *card;
	पूर्णांक ret;

	card = devm_kzalloc(dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस ERR_PTR(-ENOMEM);

	aux_dev.dlc.of_node = of_parse_phandle(dev->of_node,
						 "allwinner,codec-analog-controls",
						 0);
	अगर (!aux_dev.dlc.of_node) अणु
		dev_err(dev, "Can't find analog controls for codec.\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	card->dai_link = sun4i_codec_create_link(dev, &card->num_links);
	अगर (!card->dai_link)
		वापस ERR_PTR(-ENOMEM);

	card->dev		= dev;
	card->owner		= THIS_MODULE;
	card->name		= "H3 Audio Codec";
	card->dapm_widमाला_लो	= sun6i_codec_card_dapm_widमाला_लो;
	card->num_dapm_widमाला_लो	= ARRAY_SIZE(sun6i_codec_card_dapm_widमाला_लो);
	card->dapm_routes	= sun8i_codec_card_routes;
	card->num_dapm_routes	= ARRAY_SIZE(sun8i_codec_card_routes);
	card->aux_dev		= &aux_dev;
	card->num_aux_devs	= 1;
	card->fully_routed	= true;

	ret = snd_soc_of_parse_audio_routing(card, "allwinner,audio-routing");
	अगर (ret)
		dev_warn(dev, "failed to parse audio-routing: %d\n", ret);

	वापस card;
पूर्ण;

अटल काष्ठा snd_soc_card *sun8i_v3s_codec_create_card(काष्ठा device *dev)
अणु
	काष्ठा snd_soc_card *card;
	पूर्णांक ret;

	card = devm_kzalloc(dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस ERR_PTR(-ENOMEM);

	aux_dev.dlc.of_node = of_parse_phandle(dev->of_node,
						 "allwinner,codec-analog-controls",
						 0);
	अगर (!aux_dev.dlc.of_node) अणु
		dev_err(dev, "Can't find analog controls for codec.\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	card->dai_link = sun4i_codec_create_link(dev, &card->num_links);
	अगर (!card->dai_link)
		वापस ERR_PTR(-ENOMEM);

	card->dev		= dev;
	card->owner		= THIS_MODULE;
	card->name		= "V3s Audio Codec";
	card->dapm_widमाला_लो	= sun6i_codec_card_dapm_widमाला_लो;
	card->num_dapm_widमाला_लो	= ARRAY_SIZE(sun6i_codec_card_dapm_widमाला_लो);
	card->dapm_routes	= sun8i_codec_card_routes;
	card->num_dapm_routes	= ARRAY_SIZE(sun8i_codec_card_routes);
	card->aux_dev		= &aux_dev;
	card->num_aux_devs	= 1;
	card->fully_routed	= true;

	ret = snd_soc_of_parse_audio_routing(card, "allwinner,audio-routing");
	अगर (ret)
		dev_warn(dev, "failed to parse audio-routing: %d\n", ret);

	वापस card;
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun4i_codec_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= SUN4I_CODEC_ADC_RXCNT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun6i_codec_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= SUN6I_CODEC_HMIC_DATA,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun7i_codec_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= SUN7I_CODEC_AC_MIC_PHONE_CAL,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun8i_a23_codec_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= SUN8I_A23_CODEC_ADC_RXCNT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun8i_h3_codec_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= SUN8I_H3_CODEC_ADC_DBG,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun8i_v3s_codec_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= SUN8I_H3_CODEC_ADC_DBG,
पूर्ण;

काष्ठा sun4i_codec_quirks अणु
	स्थिर काष्ठा regmap_config *regmap_config;
	स्थिर काष्ठा snd_soc_component_driver *codec;
	काष्ठा snd_soc_card * (*create_card)(काष्ठा device *dev);
	काष्ठा reg_field reg_adc_fअगरoc;	/* used क्रम regmap_field */
	अचिन्हित पूर्णांक reg_dac_txdata;	/* TX FIFO offset क्रम DMA config */
	अचिन्हित पूर्णांक reg_adc_rxdata;	/* RX FIFO offset क्रम DMA config */
	bool has_reset;
पूर्ण;

अटल स्थिर काष्ठा sun4i_codec_quirks sun4i_codec_quirks = अणु
	.regmap_config	= &sun4i_codec_regmap_config,
	.codec		= &sun4i_codec_codec,
	.create_card	= sun4i_codec_create_card,
	.reg_adc_fअगरoc	= REG_FIELD(SUN4I_CODEC_ADC_FIFOC, 0, 31),
	.reg_dac_txdata	= SUN4I_CODEC_DAC_TXDATA,
	.reg_adc_rxdata	= SUN4I_CODEC_ADC_RXDATA,
पूर्ण;

अटल स्थिर काष्ठा sun4i_codec_quirks sun6i_a31_codec_quirks = अणु
	.regmap_config	= &sun6i_codec_regmap_config,
	.codec		= &sun6i_codec_codec,
	.create_card	= sun6i_codec_create_card,
	.reg_adc_fअगरoc	= REG_FIELD(SUN6I_CODEC_ADC_FIFOC, 0, 31),
	.reg_dac_txdata	= SUN4I_CODEC_DAC_TXDATA,
	.reg_adc_rxdata	= SUN6I_CODEC_ADC_RXDATA,
	.has_reset	= true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_codec_quirks sun7i_codec_quirks = अणु
	.regmap_config	= &sun7i_codec_regmap_config,
	.codec		= &sun7i_codec_codec,
	.create_card	= sun4i_codec_create_card,
	.reg_adc_fअगरoc	= REG_FIELD(SUN4I_CODEC_ADC_FIFOC, 0, 31),
	.reg_dac_txdata	= SUN4I_CODEC_DAC_TXDATA,
	.reg_adc_rxdata	= SUN4I_CODEC_ADC_RXDATA,
पूर्ण;

अटल स्थिर काष्ठा sun4i_codec_quirks sun8i_a23_codec_quirks = अणु
	.regmap_config	= &sun8i_a23_codec_regmap_config,
	.codec		= &sun8i_a23_codec_codec,
	.create_card	= sun8i_a23_codec_create_card,
	.reg_adc_fअगरoc	= REG_FIELD(SUN6I_CODEC_ADC_FIFOC, 0, 31),
	.reg_dac_txdata	= SUN4I_CODEC_DAC_TXDATA,
	.reg_adc_rxdata	= SUN6I_CODEC_ADC_RXDATA,
	.has_reset	= true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_codec_quirks sun8i_h3_codec_quirks = अणु
	.regmap_config	= &sun8i_h3_codec_regmap_config,
	/*
	 * TODO Share the codec काष्ठाure with A23 क्रम now.
	 * This should be split out when adding digital audio
	 * processing support क्रम the H3.
	 */
	.codec		= &sun8i_a23_codec_codec,
	.create_card	= sun8i_h3_codec_create_card,
	.reg_adc_fअगरoc	= REG_FIELD(SUN6I_CODEC_ADC_FIFOC, 0, 31),
	.reg_dac_txdata	= SUN8I_H3_CODEC_DAC_TXDATA,
	.reg_adc_rxdata	= SUN6I_CODEC_ADC_RXDATA,
	.has_reset	= true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_codec_quirks sun8i_v3s_codec_quirks = अणु
	.regmap_config	= &sun8i_v3s_codec_regmap_config,
	/*
	 * TODO The codec काष्ठाure should be split out, like
	 * H3, when adding digital audio processing support.
	 */
	.codec		= &sun8i_a23_codec_codec,
	.create_card	= sun8i_v3s_codec_create_card,
	.reg_adc_fअगरoc	= REG_FIELD(SUN6I_CODEC_ADC_FIFOC, 0, 31),
	.reg_dac_txdata	= SUN8I_H3_CODEC_DAC_TXDATA,
	.reg_adc_rxdata	= SUN6I_CODEC_ADC_RXDATA,
	.has_reset	= true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun4i_codec_of_match[] = अणु
	अणु
		.compatible = "allwinner,sun4i-a10-codec",
		.data = &sun4i_codec_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun6i-a31-codec",
		.data = &sun6i_a31_codec_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun7i-a20-codec",
		.data = &sun7i_codec_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-a23-codec",
		.data = &sun8i_a23_codec_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-h3-codec",
		.data = &sun8i_h3_codec_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-v3s-codec",
		.data = &sun8i_v3s_codec_quirks,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_codec_of_match);

अटल पूर्णांक sun4i_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card;
	काष्ठा sun4i_codec *scodec;
	स्थिर काष्ठा sun4i_codec_quirks *quirks;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक ret;

	scodec = devm_kzalloc(&pdev->dev, माप(*scodec), GFP_KERNEL);
	अगर (!scodec)
		वापस -ENOMEM;

	scodec->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	quirks = of_device_get_match_data(&pdev->dev);
	अगर (quirks == शून्य) अणु
		dev_err(&pdev->dev, "Failed to determine the quirks to use\n");
		वापस -ENODEV;
	पूर्ण

	scodec->regmap = devm_regmap_init_mmio(&pdev->dev, base,
					       quirks->regmap_config);
	अगर (IS_ERR(scodec->regmap)) अणु
		dev_err(&pdev->dev, "Failed to create our regmap\n");
		वापस PTR_ERR(scodec->regmap);
	पूर्ण

	/* Get the घड़ीs from the DT */
	scodec->clk_apb = devm_clk_get(&pdev->dev, "apb");
	अगर (IS_ERR(scodec->clk_apb)) अणु
		dev_err(&pdev->dev, "Failed to get the APB clock\n");
		वापस PTR_ERR(scodec->clk_apb);
	पूर्ण

	scodec->clk_module = devm_clk_get(&pdev->dev, "codec");
	अगर (IS_ERR(scodec->clk_module)) अणु
		dev_err(&pdev->dev, "Failed to get the module clock\n");
		वापस PTR_ERR(scodec->clk_module);
	पूर्ण

	अगर (quirks->has_reset) अणु
		scodec->rst = devm_reset_control_get_exclusive(&pdev->dev,
							       शून्य);
		अगर (IS_ERR(scodec->rst)) अणु
			dev_err(&pdev->dev, "Failed to get reset control\n");
			वापस PTR_ERR(scodec->rst);
		पूर्ण
	पूर्ण

	scodec->gpio_pa = devm_gpiod_get_optional(&pdev->dev, "allwinner,pa",
						  GPIOD_OUT_LOW);
	अगर (IS_ERR(scodec->gpio_pa)) अणु
		ret = PTR_ERR(scodec->gpio_pa);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to get pa gpio: %d\n", ret);
		वापस ret;
	पूर्ण

	/* reg_field setup */
	scodec->reg_adc_fअगरoc = devm_regmap_field_alloc(&pdev->dev,
							scodec->regmap,
							quirks->reg_adc_fअगरoc);
	अगर (IS_ERR(scodec->reg_adc_fअगरoc)) अणु
		ret = PTR_ERR(scodec->reg_adc_fअगरoc);
		dev_err(&pdev->dev, "Failed to create regmap fields: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* Enable the bus घड़ी */
	अगर (clk_prepare_enable(scodec->clk_apb)) अणु
		dev_err(&pdev->dev, "Failed to enable the APB clock\n");
		वापस -EINVAL;
	पूर्ण

	/* Deनिश्चित the reset control */
	अगर (scodec->rst) अणु
		ret = reset_control_deनिश्चित(scodec->rst);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Failed to deassert the reset control\n");
			जाओ err_clk_disable;
		पूर्ण
	पूर्ण

	/* DMA configuration क्रम TX FIFO */
	scodec->playback_dma_data.addr = res->start + quirks->reg_dac_txdata;
	scodec->playback_dma_data.maxburst = 8;
	scodec->playback_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;

	/* DMA configuration क्रम RX FIFO */
	scodec->capture_dma_data.addr = res->start + quirks->reg_adc_rxdata;
	scodec->capture_dma_data.maxburst = 8;
	scodec->capture_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, quirks->codec,
				     &sun4i_codec_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register our codec\n");
		जाओ err_निश्चित_reset;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &sun4i_codec_component,
					      &dummy_cpu_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register our DAI\n");
		जाओ err_निश्चित_reset;
	पूर्ण

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register against DMAEngine\n");
		जाओ err_निश्चित_reset;
	पूर्ण

	card = quirks->create_card(&pdev->dev);
	अगर (IS_ERR(card)) अणु
		ret = PTR_ERR(card);
		dev_err(&pdev->dev, "Failed to create our card\n");
		जाओ err_निश्चित_reset;
	पूर्ण

	snd_soc_card_set_drvdata(card, scodec);

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register our card\n");
		जाओ err_निश्चित_reset;
	पूर्ण

	वापस 0;

err_निश्चित_reset:
	अगर (scodec->rst)
		reset_control_निश्चित(scodec->rst);
err_clk_disable:
	clk_disable_unprepare(scodec->clk_apb);
	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_codec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा sun4i_codec *scodec = snd_soc_card_get_drvdata(card);

	snd_soc_unरेजिस्टर_card(card);
	अगर (scodec->rst)
		reset_control_निश्चित(scodec->rst);
	clk_disable_unprepare(scodec->clk_apb);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sun4i_codec_driver = अणु
	.driver = अणु
		.name = "sun4i-codec",
		.of_match_table = sun4i_codec_of_match,
	पूर्ण,
	.probe = sun4i_codec_probe,
	.हटाओ = sun4i_codec_हटाओ,
पूर्ण;
module_platक्रमm_driver(sun4i_codec_driver);

MODULE_DESCRIPTION("Allwinner A10 codec driver");
MODULE_AUTHOR("Emilio Lथकpez <emilio@elopez.com.ar>");
MODULE_AUTHOR("Jon Smirl <jonsmirl@gmail.com>");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_AUTHOR("Chen-Yu Tsai <wens@csie.org>");
MODULE_LICENSE("GPL");
