<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Driver क्रम Microchip S/PDIF TX Controller
//
// Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
//
// Author: Codrin Ciubotariu <codrin.ciubotariu@microchip.com>

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>

#समावेश <sound/asoundef.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

/*
 * ---- S/PDIF Transmitter Controller Register map ----
 */
#घोषणा SPDIFTX_CR			0x00	/* Control Register */
#घोषणा SPDIFTX_MR			0x04	/* Mode Register */
#घोषणा SPDIFTX_CDR			0x0C	/* Common Data Register */

#घोषणा SPDIFTX_IER			0x14	/* Interrupt Enable Register */
#घोषणा SPDIFTX_IDR			0x18	/* Interrupt Disable Register */
#घोषणा SPDIFTX_IMR			0x1C	/* Interrupt Mask Register */
#घोषणा SPDIFTX_ISR			0x20	/* Interrupt Status Register */

#घोषणा SPDIFTX_CH1UD(reg)	(0x50 + (reg) * 4)	/* User Data 1 Register x */
#घोषणा SPDIFTX_CH1S(reg)	(0x80 + (reg) * 4)	/* Channel Status 1 Register x */

#घोषणा SPDIFTX_VERSION			0xF0

/*
 * ---- Control Register (Write-only) ----
 */
#घोषणा SPDIFTX_CR_SWRST		BIT(0)	/* Software Reset */
#घोषणा SPDIFTX_CR_FCLR			BIT(1)	/* FIFO clear */

/*
 * ---- Mode Register (Read/Write) ----
 */
/* Transmit Enable */
#घोषणा SPDIFTX_MR_TXEN_MASK		GENMASK(0, 0)
#घोषणा SPDIFTX_MR_TXEN_DISABLE		(0 << 0)
#घोषणा SPDIFTX_MR_TXEN_ENABLE		(1 << 0)

/* Multichannel Transfer */
#घोषणा SPDIFTX_MR_MULTICH_MASK		GENAMSK(1, 1)
#घोषणा SPDIFTX_MR_MULTICH_MONO		(0 << 1)
#घोषणा SPDIFTX_MR_MULTICH_DUAL		(1 << 1)

/* Data Word Endian Mode */
#घोषणा SPDIFTX_MR_ENDIAN_MASK		GENMASK(2, 2)
#घोषणा SPDIFTX_MR_ENDIAN_LITTLE	(0 << 2)
#घोषणा SPDIFTX_MR_ENDIAN_BIG		(1 << 2)

/* Data Justअगरication */
#घोषणा SPDIFTX_MR_JUSTIFY_MASK		GENMASK(3, 3)
#घोषणा SPDIFTX_MR_JUSTIFY_LSB		(0 << 3)
#घोषणा SPDIFTX_MR_JUSTIFY_MSB		(1 << 3)

/* Common Audio Register Transfer Mode */
#घोषणा SPDIFTX_MR_CMODE_MASK			GENMASK(5, 4)
#घोषणा SPDIFTX_MR_CMODE_INDEX_ACCESS		(0 << 4)
#घोषणा SPDIFTX_MR_CMODE_TOGGLE_ACCESS		(1 << 4)
#घोषणा SPDIFTX_MR_CMODE_INTERLVD_ACCESS	(2 << 4)

/* Valid Bits per Sample */
#घोषणा SPDIFTX_MR_VBPS_MASK		GENMASK(13, 8)
#घोषणा SPDIFTX_MR_VBPS(bps)		(((bps) << 8) & SPDIFTX_MR_VBPS_MASK)

/* Chunk Size */
#घोषणा SPDIFTX_MR_CHUNK_MASK		GENMASK(19, 16)
#घोषणा SPDIFTX_MR_CHUNK(size)		(((size) << 16) & SPDIFTX_MR_CHUNK_MASK)

/* Validity Bits क्रम Channels 1 and 2 */
#घोषणा SPDIFTX_MR_VALID1			BIT(24)
#घोषणा SPDIFTX_MR_VALID2			BIT(25)

/* Disable Null Frame on underrrun */
#घोषणा SPDIFTX_MR_DNFR_MASK		GENMASK(27, 27)
#घोषणा SPDIFTX_MR_DNFR_INVALID		(0 << 27)
#घोषणा SPDIFTX_MR_DNFR_VALID		(1 << 27)

/* Bytes per Sample */
#घोषणा SPDIFTX_MR_BPS_MASK		GENMASK(29, 28)
#घोषणा SPDIFTX_MR_BPS(bytes) \
	((((bytes) - 1) << 28) & SPDIFTX_MR_BPS_MASK)

/*
 * ---- Interrupt Enable/Disable/Mask/Status Register (Write/Read-only) ----
 */
#घोषणा SPDIFTX_IR_TXRDY		BIT(0)
#घोषणा SPDIFTX_IR_TXEMPTY		BIT(1)
#घोषणा SPDIFTX_IR_TXFULL		BIT(2)
#घोषणा SPDIFTX_IR_TXCHUNK		BIT(3)
#घोषणा SPDIFTX_IR_TXUDR		BIT(4)
#घोषणा SPDIFTX_IR_TXOVR		BIT(5)
#घोषणा SPDIFTX_IR_CSRDY		BIT(6)
#घोषणा SPDIFTX_IR_UDRDY		BIT(7)
#घोषणा SPDIFTX_IR_TXRDYCH(ch)		BIT((ch) + 8)
#घोषणा SPDIFTX_IR_SECE			BIT(10)
#घोषणा SPDIFTX_IR_TXUDRCH(ch)		BIT((ch) + 11)
#घोषणा SPDIFTX_IR_BEND			BIT(13)

अटल bool mchp_spdअगरtx_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SPDIFTX_MR:
	हाल SPDIFTX_IMR:
	हाल SPDIFTX_ISR:
	हाल SPDIFTX_CH1UD(0):
	हाल SPDIFTX_CH1UD(1):
	हाल SPDIFTX_CH1UD(2):
	हाल SPDIFTX_CH1UD(3):
	हाल SPDIFTX_CH1UD(4):
	हाल SPDIFTX_CH1UD(5):
	हाल SPDIFTX_CH1S(0):
	हाल SPDIFTX_CH1S(1):
	हाल SPDIFTX_CH1S(2):
	हाल SPDIFTX_CH1S(3):
	हाल SPDIFTX_CH1S(4):
	हाल SPDIFTX_CH1S(5):
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool mchp_spdअगरtx_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SPDIFTX_CR:
	हाल SPDIFTX_MR:
	हाल SPDIFTX_CDR:
	हाल SPDIFTX_IER:
	हाल SPDIFTX_IDR:
	हाल SPDIFTX_CH1UD(0):
	हाल SPDIFTX_CH1UD(1):
	हाल SPDIFTX_CH1UD(2):
	हाल SPDIFTX_CH1UD(3):
	हाल SPDIFTX_CH1UD(4):
	हाल SPDIFTX_CH1UD(5):
	हाल SPDIFTX_CH1S(0):
	हाल SPDIFTX_CH1S(1):
	हाल SPDIFTX_CH1S(2):
	हाल SPDIFTX_CH1S(3):
	हाल SPDIFTX_CH1S(4):
	हाल SPDIFTX_CH1S(5):
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool mchp_spdअगरtx_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SPDIFTX_CDR:
	हाल SPDIFTX_ISR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config mchp_spdअगरtx_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = SPDIFTX_VERSION,
	.पढ़ोable_reg = mchp_spdअगरtx_पढ़ोable_reg,
	.ग_लिखोable_reg = mchp_spdअगरtx_ग_लिखोable_reg,
	.precious_reg = mchp_spdअगरtx_precious_reg,
पूर्ण;

#घोषणा SPDIFTX_GCLK_RATIO	128

#घोषणा SPDIFTX_CS_BITS		192
#घोषणा SPDIFTX_UD_BITS		192

काष्ठा mchp_spdअगरtx_mixer_control अणु
	अचिन्हित अक्षर				ch_stat[SPDIFTX_CS_BITS / 8];
	अचिन्हित अक्षर				user_data[SPDIFTX_UD_BITS / 8];
	spinlock_t				lock; /* exclusive access to control data */
पूर्ण;

काष्ठा mchp_spdअगरtx_dev अणु
	काष्ठा mchp_spdअगरtx_mixer_control	control;
	काष्ठा snd_dmaengine_dai_dma_data	playback;
	काष्ठा device				*dev;
	काष्ठा regmap				*regmap;
	काष्ठा clk				*pclk;
	काष्ठा clk				*gclk;
	अचिन्हित पूर्णांक				fmt;
	स्थिर काष्ठा mchp_i2s_caps		*caps;
	पूर्णांक					gclk_enabled:1;
पूर्ण;

अटल अंतरभूत पूर्णांक mchp_spdअगरtx_is_running(काष्ठा mchp_spdअगरtx_dev *dev)
अणु
	u32 mr;

	regmap_पढ़ो(dev->regmap, SPDIFTX_MR, &mr);
	वापस !!(mr & SPDIFTX_MR_TXEN_ENABLE);
पूर्ण

अटल व्योम mchp_spdअगरtx_channel_status_ग_लिखो(काष्ठा mchp_spdअगरtx_dev *dev)
अणु
	काष्ठा mchp_spdअगरtx_mixer_control *ctrl = &dev->control;
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ctrl->ch_stat) / 4; i++) अणु
		val = (ctrl->ch_stat[(i * 4) + 0] << 0) |
		      (ctrl->ch_stat[(i * 4) + 1] << 8) |
		      (ctrl->ch_stat[(i * 4) + 2] << 16) |
		      (ctrl->ch_stat[(i * 4) + 3] << 24);

		regmap_ग_लिखो(dev->regmap, SPDIFTX_CH1S(i), val);
	पूर्ण
पूर्ण

अटल व्योम mchp_spdअगरtx_user_data_ग_लिखो(काष्ठा mchp_spdअगरtx_dev *dev)
अणु
	काष्ठा mchp_spdअगरtx_mixer_control *ctrl = &dev->control;
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ctrl->user_data) / 4; i++) अणु
		val = (ctrl->user_data[(i * 4) + 0] << 0) |
		      (ctrl->user_data[(i * 4) + 1] << 8) |
		      (ctrl->user_data[(i * 4) + 2] << 16) |
		      (ctrl->user_data[(i * 4) + 3] << 24);

		regmap_ग_लिखो(dev->regmap, SPDIFTX_CH1UD(i), val);
	पूर्ण
पूर्ण

अटल irqवापस_t mchp_spdअगरtx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mchp_spdअगरtx_dev *dev = dev_id;
	काष्ठा mchp_spdअगरtx_mixer_control *ctrl = &dev->control;
	u32 sr, imr, pending, idr = 0;

	regmap_पढ़ो(dev->regmap, SPDIFTX_ISR, &sr);
	regmap_पढ़ो(dev->regmap, SPDIFTX_IMR, &imr);
	pending = sr & imr;

	अगर (!pending)
		वापस IRQ_NONE;

	अगर (pending & SPDIFTX_IR_TXUDR) अणु
		dev_warn(dev->dev, "underflow detected\n");
		idr |= SPDIFTX_IR_TXUDR;
	पूर्ण

	अगर (pending & SPDIFTX_IR_TXOVR) अणु
		dev_warn(dev->dev, "overflow detected\n");
		idr |= SPDIFTX_IR_TXOVR;
	पूर्ण

	अगर (pending & SPDIFTX_IR_UDRDY) अणु
		spin_lock(&ctrl->lock);
		mchp_spdअगरtx_user_data_ग_लिखो(dev);
		spin_unlock(&ctrl->lock);
		idr |= SPDIFTX_IR_UDRDY;
	पूर्ण

	अगर (pending & SPDIFTX_IR_CSRDY) अणु
		spin_lock(&ctrl->lock);
		mchp_spdअगरtx_channel_status_ग_लिखो(dev);
		spin_unlock(&ctrl->lock);
		idr |= SPDIFTX_IR_CSRDY;
	पूर्ण

	regmap_ग_लिखो(dev->regmap, SPDIFTX_IDR, idr);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mchp_spdअगरtx_dai_startup(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_spdअगरtx_dev *dev = snd_soc_dai_get_drvdata(dai);

	/* Software reset the IP */
	regmap_ग_लिखो(dev->regmap, SPDIFTX_CR,
		     SPDIFTX_CR_SWRST | SPDIFTX_CR_FCLR);

	वापस 0;
पूर्ण

अटल व्योम mchp_spdअगरtx_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_spdअगरtx_dev *dev = snd_soc_dai_get_drvdata(dai);

	/* Disable पूर्णांकerrupts */
	regmap_ग_लिखो(dev->regmap, SPDIFTX_IDR, 0xffffffff);
पूर्ण

अटल पूर्णांक mchp_spdअगरtx_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_spdअगरtx_dev *dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा mchp_spdअगरtx_mixer_control *ctrl = &dev->control;
	u32 mr;
	पूर्णांक running;
	पूर्णांक ret;

	/* करो not start/stop जबतक channel status or user data is updated */
	spin_lock(&ctrl->lock);
	regmap_पढ़ो(dev->regmap, SPDIFTX_MR, &mr);
	running = !!(mr & SPDIFTX_MR_TXEN_ENABLE);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (!running) अणु
			mr &= ~SPDIFTX_MR_TXEN_MASK;
			mr |= SPDIFTX_MR_TXEN_ENABLE;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (running) अणु
			mr &= ~SPDIFTX_MR_TXEN_MASK;
			mr |= SPDIFTX_MR_TXEN_DISABLE;
		पूर्ण
		अवरोध;
	शेष:
		spin_unlock(&ctrl->lock);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap, SPDIFTX_MR, mr);
	spin_unlock(&ctrl->lock);
	अगर (ret) अणु
		dev_err(dev->dev, "unable to disable TX: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरtx_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mchp_spdअगरtx_dev *dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा mchp_spdअगरtx_mixer_control *ctrl = &dev->control;
	u32 mr;
	अचिन्हित पूर्णांक bps = params_physical_width(params) / 8;
	पूर्णांक ret;

	dev_dbg(dev->dev, "%s() rate=%u format=%#x width=%u channels=%u\n",
		__func__, params_rate(params), params_क्रमmat(params),
		params_width(params), params_channels(params));

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		dev_err(dev->dev, "Capture is not supported\n");
		वापस -EINVAL;
	पूर्ण

	regmap_पढ़ो(dev->regmap, SPDIFTX_MR, &mr);

	अगर (mr & SPDIFTX_MR_TXEN_ENABLE) अणु
		dev_err(dev->dev, "PCM already running\n");
		वापस -EBUSY;
	पूर्ण

	/* Defaults: Toggle mode, justअगरy to LSB, chunksize 1 */
	mr = SPDIFTX_MR_CMODE_TOGGLE_ACCESS | SPDIFTX_MR_JUSTIFY_LSB;
	dev->playback.maxburst = 1;
	चयन (params_channels(params)) अणु
	हाल 1:
		mr |= SPDIFTX_MR_MULTICH_MONO;
		अवरोध;
	हाल 2:
		mr |= SPDIFTX_MR_MULTICH_DUAL;
		अगर (bps > 2)
			dev->playback.maxburst = 2;
		अवरोध;
	शेष:
		dev_err(dev->dev, "unsupported number of channels: %d\n",
			params_channels(params));
		वापस -EINVAL;
	पूर्ण
	mr |= SPDIFTX_MR_CHUNK(dev->playback.maxburst);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		mr |= SPDIFTX_MR_VBPS(8);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_BE:
		mr |= SPDIFTX_MR_ENDIAN_BIG;
		fallthrough;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		mr |= SPDIFTX_MR_VBPS(16);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S18_3BE:
		mr |= SPDIFTX_MR_ENDIAN_BIG;
		fallthrough;
	हाल SNDRV_PCM_FORMAT_S18_3LE:
		mr |= SPDIFTX_MR_VBPS(18);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3BE:
		mr |= SPDIFTX_MR_ENDIAN_BIG;
		fallthrough;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		mr |= SPDIFTX_MR_VBPS(20);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_3BE:
		mr |= SPDIFTX_MR_ENDIAN_BIG;
		fallthrough;
	हाल SNDRV_PCM_FORMAT_S24_3LE:
		mr |= SPDIFTX_MR_VBPS(24);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_BE:
		mr |= SPDIFTX_MR_ENDIAN_BIG;
		fallthrough;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		mr |= SPDIFTX_MR_VBPS(24);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_BE:
		mr |= SPDIFTX_MR_ENDIAN_BIG;
		fallthrough;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		mr |= SPDIFTX_MR_VBPS(32);
		अवरोध;
	शेष:
		dev_err(dev->dev, "unsupported PCM format: %d\n",
			params_क्रमmat(params));
		वापस -EINVAL;
	पूर्ण

	mr |= SPDIFTX_MR_BPS(bps);

	spin_lock_irqsave(&ctrl->lock, flags);
	ctrl->ch_stat[3] &= ~IEC958_AES3_CON_FS;
	चयन (params_rate(params)) अणु
	हाल 22050:
		ctrl->ch_stat[3] |= IEC958_AES3_CON_FS_22050;
		अवरोध;
	हाल 24000:
		ctrl->ch_stat[3] |= IEC958_AES3_CON_FS_24000;
		अवरोध;
	हाल 32000:
		ctrl->ch_stat[3] |= IEC958_AES3_CON_FS_32000;
		अवरोध;
	हाल 44100:
		ctrl->ch_stat[3] |= IEC958_AES3_CON_FS_44100;
		अवरोध;
	हाल 48000:
		ctrl->ch_stat[3] |= IEC958_AES3_CON_FS_48000;
		अवरोध;
	हाल 88200:
		ctrl->ch_stat[3] |= IEC958_AES3_CON_FS_88200;
		अवरोध;
	हाल 96000:
		ctrl->ch_stat[3] |= IEC958_AES3_CON_FS_96000;
		अवरोध;
	हाल 176400:
		ctrl->ch_stat[3] |= IEC958_AES3_CON_FS_176400;
		अवरोध;
	हाल 192000:
		ctrl->ch_stat[3] |= IEC958_AES3_CON_FS_192000;
		अवरोध;
	हाल 8000:
	हाल 11025:
	हाल 16000:
	हाल 64000:
		ctrl->ch_stat[3] |= IEC958_AES3_CON_FS_NOTID;
		अवरोध;
	शेष:
		dev_err(dev->dev, "unsupported sample frequency: %u\n",
			params_rate(params));
		spin_unlock_irqrestore(&ctrl->lock, flags);
		वापस -EINVAL;
	पूर्ण
	mchp_spdअगरtx_channel_status_ग_लिखो(dev);
	spin_unlock_irqrestore(&ctrl->lock, flags);

	अगर (dev->gclk_enabled) अणु
		clk_disable_unprepare(dev->gclk);
		dev->gclk_enabled = 0;
	पूर्ण
	ret = clk_set_rate(dev->gclk, params_rate(params) *
				      SPDIFTX_GCLK_RATIO);
	अगर (ret) अणु
		dev_err(dev->dev,
			"unable to change gclk rate to: rate %u * ratio %u\n",
			params_rate(params), SPDIFTX_GCLK_RATIO);
		वापस ret;
	पूर्ण
	ret = clk_prepare_enable(dev->gclk);
	अगर (ret) अणु
		dev_err(dev->dev, "unable to enable gclk: %d\n", ret);
		वापस ret;
	पूर्ण
	dev->gclk_enabled = 1;
	dev_dbg(dev->dev, "%s(): GCLK set to %d\n", __func__,
		params_rate(params) * SPDIFTX_GCLK_RATIO);

	/* Enable पूर्णांकerrupts */
	regmap_ग_लिखो(dev->regmap, SPDIFTX_IER,
		     SPDIFTX_IR_TXUDR | SPDIFTX_IR_TXOVR);

	regmap_ग_लिखो(dev->regmap, SPDIFTX_MR, mr);

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरtx_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_spdअगरtx_dev *dev = snd_soc_dai_get_drvdata(dai);

	regmap_ग_लिखो(dev->regmap, SPDIFTX_IDR,
		     SPDIFTX_IR_TXUDR | SPDIFTX_IR_TXOVR);
	अगर (dev->gclk_enabled) अणु
		clk_disable_unprepare(dev->gclk);
		dev->gclk_enabled = 0;
	पूर्ण

	वापस regmap_ग_लिखो(dev->regmap, SPDIFTX_CR,
			    SPDIFTX_CR_SWRST | SPDIFTX_CR_FCLR);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mchp_spdअगरtx_dai_ops = अणु
	.startup	= mchp_spdअगरtx_dai_startup,
	.shutकरोwn	= mchp_spdअगरtx_dai_shutकरोwn,
	.trigger	= mchp_spdअगरtx_trigger,
	.hw_params	= mchp_spdअगरtx_hw_params,
	.hw_मुक्त	= mchp_spdअगरtx_hw_मुक्त,
पूर्ण;

#घोषणा MCHP_SPDIFTX_RATES	SNDRV_PCM_RATE_8000_192000

#घोषणा MCHP_SPDIFTX_FORMATS	(SNDRV_PCM_FMTBIT_S8 |		\
				 SNDRV_PCM_FMTBIT_S16_LE |	\
				 SNDRV_PCM_FMTBIT_U16_BE |	\
				 SNDRV_PCM_FMTBIT_S18_3LE |	\
				 SNDRV_PCM_FMTBIT_S18_3BE |	\
				 SNDRV_PCM_FMTBIT_S20_3LE |	\
				 SNDRV_PCM_FMTBIT_S20_3BE |	\
				 SNDRV_PCM_FMTBIT_S24_3LE |	\
				 SNDRV_PCM_FMTBIT_S24_3BE |	\
				 SNDRV_PCM_FMTBIT_S24_LE |	\
				 SNDRV_PCM_FMTBIT_S24_BE |	\
				 SNDRV_PCM_FMTBIT_S32_LE |	\
				 SNDRV_PCM_FMTBIT_S32_BE	\
				 )

अटल पूर्णांक mchp_spdअगरtx_info(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरtx_cs_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *uvalue)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा mchp_spdअगरtx_dev *dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा mchp_spdअगरtx_mixer_control *ctrl = &dev->control;

	spin_lock_irqsave(&ctrl->lock, flags);
	स_नकल(uvalue->value.iec958.status, ctrl->ch_stat,
	       माप(ctrl->ch_stat));
	spin_unlock_irqrestore(&ctrl->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरtx_cs_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *uvalue)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा mchp_spdअगरtx_dev *dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा mchp_spdअगरtx_mixer_control *ctrl = &dev->control;
	पूर्णांक changed = 0;
	पूर्णांक i;

	spin_lock_irqsave(&ctrl->lock, flags);
	क्रम (i = 0; i < ARRAY_SIZE(ctrl->ch_stat); i++) अणु
		अगर (ctrl->ch_stat[i] != uvalue->value.iec958.status[i])
			changed = 1;
		ctrl->ch_stat[i] = uvalue->value.iec958.status[i];
	पूर्ण

	अगर (changed) अणु
		/* करोn't enable IP जबतक we copy the channel status */
		अगर (mchp_spdअगरtx_is_running(dev)) अणु
			/*
			 * अगर SPDIF is running, रुको क्रम पूर्णांकerrupt to ग_लिखो
			 * channel status
			 */
			regmap_ग_लिखो(dev->regmap, SPDIFTX_IER,
				     SPDIFTX_IR_CSRDY);
		पूर्ण अन्यथा अणु
			mchp_spdअगरtx_channel_status_ग_लिखो(dev);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ctrl->lock, flags);

	वापस changed;
पूर्ण

अटल पूर्णांक mchp_spdअगरtx_cs_mask(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *uvalue)
अणु
	स_रखो(uvalue->value.iec958.status, 0xff,
	       माप(uvalue->value.iec958.status));

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरtx_subcode_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा mchp_spdअगरtx_dev *dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा mchp_spdअगरtx_mixer_control *ctrl = &dev->control;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctrl->lock, flags);
	स_नकल(uvalue->value.iec958.subcode, ctrl->user_data,
	       माप(ctrl->user_data));
	spin_unlock_irqrestore(&ctrl->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरtx_subcode_put(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *uvalue)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा mchp_spdअगरtx_dev *dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा mchp_spdअगरtx_mixer_control *ctrl = &dev->control;
	पूर्णांक changed = 0;
	पूर्णांक i;

	spin_lock_irqsave(&ctrl->lock, flags);
	क्रम (i = 0; i < ARRAY_SIZE(ctrl->user_data); i++) अणु
		अगर (ctrl->user_data[i] != uvalue->value.iec958.subcode[i])
			changed = 1;

		ctrl->user_data[i] = uvalue->value.iec958.subcode[i];
	पूर्ण
	अगर (changed) अणु
		अगर (mchp_spdअगरtx_is_running(dev)) अणु
			/*
			 * अगर SPDIF is running, रुको क्रम पूर्णांकerrupt to ग_लिखो
			 * user data
			 */
			regmap_ग_लिखो(dev->regmap, SPDIFTX_IER,
				     SPDIFTX_IR_UDRDY);
		पूर्ण अन्यथा अणु
			mchp_spdअगरtx_user_data_ग_लिखो(dev);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ctrl->lock, flags);

	वापस changed;
पूर्ण

अटल काष्ठा snd_kcontrol_new mchp_spdअगरtx_ctrls[] = अणु
	/* Channel status controller */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = mchp_spdअगरtx_info,
		.get = mchp_spdअगरtx_cs_get,
		.put = mchp_spdअगरtx_cs_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, MASK),
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = mchp_spdअगरtx_info,
		.get = mchp_spdअगरtx_cs_mask,
	पूर्ण,
	/* User bits controller */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "IEC958 Subcode Playback Default",
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = mchp_spdअगरtx_info,
		.get = mchp_spdअगरtx_subcode_get,
		.put = mchp_spdअगरtx_subcode_put,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mchp_spdअगरtx_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_spdअगरtx_dev *dev = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	snd_soc_dai_init_dma_data(dai, &dev->playback, शून्य);

	ret = clk_prepare_enable(dev->pclk);
	अगर (ret) अणु
		dev_err(dev->dev,
			"failed to enable the peripheral clock: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Add controls */
	snd_soc_add_dai_controls(dai, mchp_spdअगरtx_ctrls,
				 ARRAY_SIZE(mchp_spdअगरtx_ctrls));

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरtx_dai_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_spdअगरtx_dev *dev = snd_soc_dai_get_drvdata(dai);

	clk_disable_unprepare(dev->pclk);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver mchp_spdअगरtx_dai = अणु
	.name = "mchp-spdiftx",
	.probe	= mchp_spdअगरtx_dai_probe,
	.हटाओ	= mchp_spdअगरtx_dai_हटाओ,
	.playback = अणु
		.stream_name = "S/PDIF Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = MCHP_SPDIFTX_RATES,
		.क्रमmats = MCHP_SPDIFTX_FORMATS,
	पूर्ण,
	.ops = &mchp_spdअगरtx_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver mchp_spdअगरtx_component = अणु
	.name		= "mchp-spdiftx",
पूर्ण;

अटल स्थिर काष्ठा of_device_id mchp_spdअगरtx_dt_ids[] = अणु
	अणु
		.compatible = "microchip,sama7g5-spdiftx",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, mchp_spdअगरtx_dt_ids);
अटल पूर्णांक mchp_spdअगरtx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा mchp_spdअगरtx_dev *dev;
	काष्ठा resource *mem;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	काष्ठा mchp_spdअगरtx_mixer_control *ctrl;
	पूर्णांक irq;
	पूर्णांक err;

	/* Get memory क्रम driver data. */
	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	/* Get hardware capabilities. */
	match = of_match_node(mchp_spdअगरtx_dt_ids, np);
	अगर (match)
		dev->caps = match->data;

	/* Map I/O रेजिस्टरs. */
	base = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &mem);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(&pdev->dev, base,
				       &mchp_spdअगरtx_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Request IRQ */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	err = devm_request_irq(&pdev->dev, irq, mchp_spdअगरtx_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), dev);
	अगर (err)
		वापस err;

	/* Get the peripheral घड़ी */
	dev->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(dev->pclk)) अणु
		err = PTR_ERR(dev->pclk);
		dev_err(&pdev->dev,
			"failed to get the peripheral clock: %d\n", err);
		वापस err;
	पूर्ण

	/* Get the generic घड़ी */
	dev->gclk = devm_clk_get(&pdev->dev, "gclk");
	अगर (IS_ERR(dev->gclk)) अणु
		err = PTR_ERR(dev->gclk);
		dev_err(&pdev->dev,
			"failed to get the PMC generic clock: %d\n", err);
		वापस err;
	पूर्ण

	ctrl = &dev->control;
	spin_lock_init(&ctrl->lock);

	/* Init channel status */
	ctrl->ch_stat[0] = IEC958_AES0_CON_NOT_COPYRIGHT |
			   IEC958_AES0_CON_EMPHASIS_NONE;

	dev->dev = &pdev->dev;
	dev->regmap = regmap;
	platक्रमm_set_drvdata(pdev, dev);

	dev->playback.addr = (dma_addr_t)mem->start + SPDIFTX_CDR;
	dev->playback.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	err = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register PMC: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &mchp_spdअगरtx_component,
					      &mchp_spdअगरtx_dai, 1);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register component: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mchp_spdअगरtx_driver = अणु
	.probe	= mchp_spdअगरtx_probe,
	.driver	= अणु
		.name	= "mchp_spdiftx",
		.of_match_table = of_match_ptr(mchp_spdअगरtx_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mchp_spdअगरtx_driver);

MODULE_AUTHOR("Codrin Ciubotariu <codrin.ciubotariu@microchip.com>");
MODULE_DESCRIPTION("Microchip S/PDIF TX Controller Driver");
MODULE_LICENSE("GPL v2");
