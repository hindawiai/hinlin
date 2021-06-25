<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Serial Sound Interface (I2S) support क्रम SH7760/SH7780
//
// Copyright (c) 2007 Manuel Lauss <mano@roarinelk.homelinux.net>
//
// करोnt क्रमget to set IPSEL/OMSEL रेजिस्टर bits (in your board code) to
// enable SSI output pins!

/*
 * LIMITATIONS:
 *	The SSI unit has only one physical data line, so full duplex is
 *	impossible.  This can be remedied  on the  SH7760 by  using the
 *	other SSI unit क्रम recording; however the SH7780 has only 1 SSI
 *	unit, and its pins are shared with the AC97 unit,  among others.
 *
 * FEATURES:
 *	The SSI features "compressed mode": in this mode it continuously
 *	streams PCM data over the I2S lines and uses LRCK as a handshake
 *	संकेत.  Can be used to send compressed data (AC3/DTS) to a DSP.
 *	The number of bits sent over the wire in a frame can be adjusted
 *	and can be independent from the actual sample bit depth. This is
 *	useful to support TDM mode codecs like the AD1939 which have a
 *	fixed TDM slot size, regardless of sample resolution.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <यंत्र/पन.स>

#घोषणा SSICR	0x00
#घोषणा SSISR	0x04

#घोषणा CR_DMAEN	(1 << 28)
#घोषणा CR_CHNL_SHIFT	22
#घोषणा CR_CHNL_MASK	(3 << CR_CHNL_SHIFT)
#घोषणा CR_DWL_SHIFT	19
#घोषणा CR_DWL_MASK	(7 << CR_DWL_SHIFT)
#घोषणा CR_SWL_SHIFT	16
#घोषणा CR_SWL_MASK	(7 << CR_SWL_SHIFT)
#घोषणा CR_SCK_MASTER	(1 << 15)	/* bitघड़ी master bit */
#घोषणा CR_SWS_MASTER	(1 << 14)	/* wordselect master bit */
#घोषणा CR_SCKP		(1 << 13)	/* I2Sघड़ी polarity */
#घोषणा CR_SWSP		(1 << 12)	/* LRCK polarity */
#घोषणा CR_SPDP		(1 << 11)
#घोषणा CR_SDTA		(1 << 10)	/* i2s alignment (msb/lsb) */
#घोषणा CR_PDTA		(1 << 9)	/* fअगरo data alignment */
#घोषणा CR_DEL		(1 << 8)	/* delay data by 1 i2sclk */
#घोषणा CR_BREN		(1 << 7)	/* घड़ी gating in burst mode */
#घोषणा CR_CKDIV_SHIFT	4
#घोषणा CR_CKDIV_MASK	(7 << CR_CKDIV_SHIFT)	/* bitघड़ी भागider */
#घोषणा CR_MUTE		(1 << 3)	/* SSI mute */
#घोषणा CR_CPEN		(1 << 2)	/* compressed mode */
#घोषणा CR_TRMD		(1 << 1)	/* transmit/receive select */
#घोषणा CR_EN		(1 << 0)	/* enable SSI */

#घोषणा SSIREG(reg)	(*(अचिन्हित दीर्घ *)(ssi->mmio + (reg)))

काष्ठा ssi_priv अणु
	अचिन्हित दीर्घ mmio;
	अचिन्हित दीर्घ sysclk;
	पूर्णांक inuse;
पूर्ण ssi_cpu_data[] = अणु
#अगर defined(CONFIG_CPU_SUBTYPE_SH7760)
	अणु
		.mmio	= 0xFE680000,
	पूर्ण,
	अणु
		.mmio	= 0xFE690000,
	पूर्ण,
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7780)
	अणु
		.mmio	= 0xFFE70000,
	पूर्ण,
#अन्यथा
#त्रुटि "Unsupported SuperH SoC"
#पूर्ण_अगर
पूर्ण;

/*
 * track usage of the SSI; it is simplex-only so prevent attempts of
 * concurrent playback + capture. FIXME: any locking required?
 */
अटल पूर्णांक ssi_startup(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ssi_priv *ssi = &ssi_cpu_data[dai->id];
	अगर (ssi->inuse) अणु
		pr_debug("ssi: already in use!\n");
		वापस -EBUSY;
	पूर्ण अन्यथा
		ssi->inuse = 1;
	वापस 0;
पूर्ण

अटल व्योम ssi_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ssi_priv *ssi = &ssi_cpu_data[dai->id];

	ssi->inuse = 0;
पूर्ण

अटल पूर्णांक ssi_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
		       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ssi_priv *ssi = &ssi_cpu_data[dai->id];

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		SSIREG(SSICR) |= CR_DMAEN | CR_EN;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		SSIREG(SSICR) &= ~(CR_DMAEN | CR_EN);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *params,
			 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ssi_priv *ssi = &ssi_cpu_data[dai->id];
	अचिन्हित दीर्घ ssicr = SSIREG(SSICR);
	अचिन्हित पूर्णांक bits, channels, swl, recv, i;

	channels = params_channels(params);
	bits = params->msbits;
	recv = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) ? 0 : 1;

	pr_debug("ssi_hw_params() enter\nssicr was    %08lx\n", ssicr);
	pr_debug("bits: %u channels: %u\n", bits, channels);

	ssicr &= ~(CR_TRMD | CR_CHNL_MASK | CR_DWL_MASK | CR_PDTA |
		   CR_SWL_MASK);

	/* direction (send/receive) */
	अगर (!recv)
		ssicr |= CR_TRMD;	/* transmit */

	/* channels */
	अगर ((channels < 2) || (channels > 8) || (channels & 1)) अणु
		pr_debug("ssi: invalid number of channels\n");
		वापस -EINVAL;
	पूर्ण
	ssicr |= ((channels >> 1) - 1) << CR_CHNL_SHIFT;

	/* DATA WORD LENGTH (DWL): databits in audio sample */
	i = 0;
	चयन (bits) अणु
	हाल 32: ++i;
	हाल 24: ++i;
	हाल 22: ++i;
	हाल 20: ++i;
	हाल 18: ++i;
	हाल 16: ++i;
		 ssicr |= i << CR_DWL_SHIFT;
	हाल 8:	 अवरोध;
	शेष:
		pr_debug("ssi: invalid sample width\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * SYSTEM WORD LENGTH: size in bits of half a frame over the I2S
	 * wires. This is usually bits_per_sample x channels/2;  i.e. in
	 * Stereo mode  the SWL equals DWL.  SWL can  be bigger than the
	 * product of (channels_per_slot x samplebits), e.g.  क्रम codecs
	 * like the AD1939 which  only accept 32bit wide TDM slots.  For
	 * "standard" I2S operation we set SWL = chans / 2 * DWL here.
	 * Waiting क्रम ASoC to get TDM support ;-)
	 */
	अगर ((bits > 16) && (bits <= 24)) अणु
		bits = 24;	/* these are padded by the SSI */
		/*ssicr |= CR_PDTA;*/ /* cpu/data endianness ? */
	पूर्ण
	i = 0;
	swl = (bits * channels) / 2;
	चयन (swl) अणु
	हाल 256: ++i;
	हाल 128: ++i;
	हाल 64:  ++i;
	हाल 48:  ++i;
	हाल 32:  ++i;
	हाल 16:  ++i;
		  ssicr |= i << CR_SWL_SHIFT;
	हाल 8:   अवरोध;
	शेष:
		pr_debug("ssi: invalid system word length computed\n");
		वापस -EINVAL;
	पूर्ण

	SSIREG(SSICR) = ssicr;

	pr_debug("ssi_hw_params() leave\nssicr is now %08lx\n", ssicr);
	वापस 0;
पूर्ण

अटल पूर्णांक ssi_set_sysclk(काष्ठा snd_soc_dai *cpu_dai, पूर्णांक clk_id,
			  अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा ssi_priv *ssi = &ssi_cpu_data[cpu_dai->id];

	ssi->sysclk = freq;

	वापस 0;
पूर्ण

/*
 * This भागider is used to generate the SSI_SCK (I2S bitघड़ी) from the
 * घड़ी at the HAC_BIT_CLK ("oversampling clock") pin.
 */
अटल पूर्णांक ssi_set_clkभाग(काष्ठा snd_soc_dai *dai, पूर्णांक did, पूर्णांक भाग)
अणु
	काष्ठा ssi_priv *ssi = &ssi_cpu_data[dai->id];
	अचिन्हित दीर्घ ssicr;
	पूर्णांक i;

	i = 0;
	ssicr = SSIREG(SSICR) & ~CR_CKDIV_MASK;
	चयन (भाग) अणु
	हाल 16: ++i;
	हाल 8:  ++i;
	हाल 4:  ++i;
	हाल 2:  ++i;
		 SSIREG(SSICR) = ssicr | (i << CR_CKDIV_SHIFT);
	हाल 1:  अवरोध;
	शेष:
		pr_debug("ssi: invalid sck divider %d\n", भाग);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा ssi_priv *ssi = &ssi_cpu_data[dai->id];
	अचिन्हित दीर्घ ssicr = SSIREG(SSICR);

	pr_debug("ssi_set_fmt()\nssicr was    0x%08lx\n", ssicr);

	ssicr &= ~(CR_DEL | CR_PDTA | CR_BREN | CR_SWSP | CR_SCKP |
		   CR_SWS_MASTER | CR_SCK_MASTER);

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		ssicr |= CR_DEL | CR_PDTA;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		ssicr |= CR_DEL;
		अवरोध;
	शेष:
		pr_debug("ssi: unsupported format\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_CLOCK_MASK) अणु
	हाल SND_SOC_DAIFMT_CONT:
		अवरोध;
	हाल SND_SOC_DAIFMT_GATED:
		ssicr |= CR_BREN;
		अवरोध;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		ssicr |= CR_SCKP;	/* sample data at low clkedge */
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		ssicr |= CR_SCKP | CR_SWSP;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		ssicr |= CR_SWSP;	/* word select starts low */
		अवरोध;
	शेष:
		pr_debug("ssi: invalid inversion\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		ssicr |= CR_SCK_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		ssicr |= CR_SWS_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		ssicr |= CR_SWS_MASTER | CR_SCK_MASTER;
		अवरोध;
	शेष:
		pr_debug("ssi: invalid master/secondary configuration\n");
		वापस -EINVAL;
	पूर्ण

	SSIREG(SSICR) = ssicr;
	pr_debug("ssi_set_fmt() leave\nssicr is now 0x%08lx\n", ssicr);

	वापस 0;
पूर्ण

/* the SSI depends on an बाह्यal घड़ीsource (at HAC_BIT_CLK) even in
 * Master mode,  so really this is board specअगरic;  the SSI can करो any
 * rate with the right bitclk and भागider settings.
 */
#घोषणा SSI_RATES	\
	SNDRV_PCM_RATE_8000_192000

/* the SSI can करो 8-32 bit samples, with 8 possible channels */
#घोषणा SSI_FMTS	\
	(SNDRV_PCM_FMTBIT_S8      | SNDRV_PCM_FMTBIT_U8      |	\
	 SNDRV_PCM_FMTBIT_S16_LE  | SNDRV_PCM_FMTBIT_U16_LE  |	\
	 SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_U20_3LE |	\
	 SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_U24_3LE |	\
	 SNDRV_PCM_FMTBIT_S32_LE  | SNDRV_PCM_FMTBIT_U32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops ssi_dai_ops = अणु
	.startup	= ssi_startup,
	.shutकरोwn	= ssi_shutकरोwn,
	.trigger	= ssi_trigger,
	.hw_params	= ssi_hw_params,
	.set_sysclk	= ssi_set_sysclk,
	.set_clkभाग	= ssi_set_clkभाग,
	.set_fmt	= ssi_set_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sh4_ssi_dai[] = अणु
अणु
	.name			= "ssi-dai.0",
	.playback = अणु
		.rates		= SSI_RATES,
		.क्रमmats	= SSI_FMTS,
		.channels_min	= 2,
		.channels_max	= 8,
	पूर्ण,
	.capture = अणु
		.rates		= SSI_RATES,
		.क्रमmats	= SSI_FMTS,
		.channels_min	= 2,
		.channels_max	= 8,
	पूर्ण,
	.ops = &ssi_dai_ops,
पूर्ण,
#अगर_घोषित CONFIG_CPU_SUBTYPE_SH7760
अणु
	.name			= "ssi-dai.1",
	.playback = अणु
		.rates		= SSI_RATES,
		.क्रमmats	= SSI_FMTS,
		.channels_min	= 2,
		.channels_max	= 8,
	पूर्ण,
	.capture = अणु
		.rates		= SSI_RATES,
		.क्रमmats	= SSI_FMTS,
		.channels_min	= 2,
		.channels_max	= 8,
	पूर्ण,
	.ops = &ssi_dai_ops,
पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sh4_ssi_component = अणु
	.name		= "sh4-ssi",
पूर्ण;

अटल पूर्णांक sh4_soc_dai_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &sh4_ssi_component,
					       sh4_ssi_dai,
					       ARRAY_SIZE(sh4_ssi_dai));
पूर्ण

अटल काष्ठा platक्रमm_driver sh4_ssi_driver = अणु
	.driver = अणु
			.name = "sh4-ssi-dai",
	पूर्ण,

	.probe = sh4_soc_dai_probe,
पूर्ण;

module_platक्रमm_driver(sh4_ssi_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SuperH onchip SSI (I2S) audio driver");
MODULE_AUTHOR("Manuel Lauss <mano@roarinelk.homelinux.net>");
