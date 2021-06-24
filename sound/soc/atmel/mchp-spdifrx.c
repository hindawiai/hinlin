<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Driver क्रम Microchip S/PDIF RX Controller
//
// Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
//
// Author: Codrin Ciubotariu <codrin.ciubotariu@microchip.com>

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spinlock.h>

#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

/*
 * ---- S/PDIF Receiver Controller Register map ----
 */
#घोषणा SPDIFRX_CR			0x00	/* Control Register */
#घोषणा SPDIFRX_MR			0x04	/* Mode Register */

#घोषणा SPDIFRX_IER			0x10	/* Interrupt Enable Register */
#घोषणा SPDIFRX_IDR			0x14	/* Interrupt Disable Register */
#घोषणा SPDIFRX_IMR			0x18	/* Interrupt Mask Register */
#घोषणा SPDIFRX_ISR			0x1c	/* Interrupt Status Register */
#घोषणा SPDIFRX_RSR			0x20	/* Status Register */
#घोषणा SPDIFRX_RHR			0x24	/* Holding Register */

#घोषणा SPDIFRX_CHSR(channel, reg)	\
	(0x30 + (channel) * 0x30 + (reg) * 4)	/* Channel x Status Registers */

#घोषणा SPDIFRX_CHUD(channel, reg)	\
	(0x48 + (channel) * 0x30 + (reg) * 4)	/* Channel x User Data Registers */

#घोषणा SPDIFRX_WPMR			0xE4	/* Write Protection Mode Register */
#घोषणा SPDIFRX_WPSR			0xE8	/* Write Protection Status Register */

#घोषणा SPDIFRX_VERSION			0xFC	/* Version Register */

/*
 * ---- Control Register (Write-only) ----
 */
#घोषणा SPDIFRX_CR_SWRST		BIT(0)	/* Software Reset */

/*
 * ---- Mode Register (Read/Write) ----
 */
/* Receive Enable */
#घोषणा SPDIFRX_MR_RXEN_MASK		GENMASK(0, 0)
#घोषणा SPDIFRX_MR_RXEN_DISABLE		(0 << 0)	/* SPDIF Receiver Disabled */
#घोषणा SPDIFRX_MR_RXEN_ENABLE		(1 << 0)	/* SPDIF Receiver Enabled */

/* Validity Bit Mode */
#घोषणा SPDIFRX_MR_VBMODE_MASK		GENAMSK(1, 1)
#घोषणा SPDIFRX_MR_VBMODE_ALWAYS_LOAD \
	(0 << 1)	/* Load sample regardles of validity bit value */
#घोषणा SPDIFRX_MR_VBMODE_DISCARD_IF_VB1 \
	(1 << 1)	/* Load sample only अगर validity bit is 0 */

/* Data Word Endian Mode */
#घोषणा SPDIFRX_MR_ENDIAN_MASK		GENMASK(2, 2)
#घोषणा SPDIFRX_MR_ENDIAN_LITTLE	(0 << 2)	/* Little Endian Mode */
#घोषणा SPDIFRX_MR_ENDIAN_BIG		(1 << 2)	/* Big Endian Mode */

/* Parity Bit Mode */
#घोषणा SPDIFRX_MR_PBMODE_MASK		GENMASK(3, 3)
#घोषणा SPDIFRX_MR_PBMODE_PARCHECK	(0 << 3)	/* Parity Check Enabled */
#घोषणा SPDIFRX_MR_PBMODE_NOPARCHECK	(1 << 3)	/* Parity Check Disabled */

/* Sample Data Width */
#घोषणा SPDIFRX_MR_DATAWIDTH_MASK	GENMASK(5, 4)
#घोषणा SPDIFRX_MR_DATAWIDTH(width) \
	(((6 - (width) / 4) << 4) & SPDIFRX_MR_DATAWIDTH_MASK)

/* Packed Data Mode in Receive Holding Register */
#घोषणा SPDIFRX_MR_PACK_MASK		GENMASK(7, 7)
#घोषणा SPDIFRX_MR_PACK_DISABLED	(0 << 7)
#घोषणा SPDIFRX_MR_PACK_ENABLED		(1 << 7)

/* Start of Block Bit Mode */
#घोषणा SPDIFRX_MR_SBMODE_MASK		GENMASK(8, 8)
#घोषणा SPDIFRX_MR_SBMODE_ALWAYS_LOAD	(0 << 8)
#घोषणा SPDIFRX_MR_SBMODE_DISCARD	(1 << 8)

/* Consecutive Preamble Error Threshold Automatic Restart */
#घोषणा SPDIFRX_MR_AUTORST_MASK			GENMASK(24, 24)
#घोषणा SPDIFRX_MR_AUTORST_NOACTION		(0 << 24)
#घोषणा SPDIFRX_MR_AUTORST_UNLOCK_ON_PRE_ERR	(1 << 24)

/*
 * ---- Interrupt Enable/Disable/Mask/Status Register (Write/Read-only) ----
 */
#घोषणा SPDIFRX_IR_RXRDY			BIT(0)
#घोषणा SPDIFRX_IR_LOCKED			BIT(1)
#घोषणा SPDIFRX_IR_LOSS				BIT(2)
#घोषणा SPDIFRX_IR_BLOCKEND			BIT(3)
#घोषणा SPDIFRX_IR_SFE				BIT(4)
#घोषणा SPDIFRX_IR_PAR_ERR			BIT(5)
#घोषणा SPDIFRX_IR_OVERRUN			BIT(6)
#घोषणा SPDIFRX_IR_RXFULL			BIT(7)
#घोषणा SPDIFRX_IR_CSC(ch)			BIT((ch) + 8)
#घोषणा SPDIFRX_IR_SECE				BIT(10)
#घोषणा SPDIFRX_IR_BLOCKST			BIT(11)
#घोषणा SPDIFRX_IR_NRZ_ERR			BIT(12)
#घोषणा SPDIFRX_IR_PRE_ERR			BIT(13)
#घोषणा SPDIFRX_IR_CP_ERR			BIT(14)

/*
 * ---- Receiver Status Register (Read/Write) ----
 */
/* Enable Status */
#घोषणा SPDIFRX_RSR_ULOCK			BIT(0)
#घोषणा SPDIFRX_RSR_BADF			BIT(1)
#घोषणा SPDIFRX_RSR_LOWF			BIT(2)
#घोषणा SPDIFRX_RSR_NOSIGNAL			BIT(3)
#घोषणा SPDIFRX_RSR_IFS_MASK			GENMASK(27, 16)
#घोषणा SPDIFRX_RSR_IFS(reg)			\
	(((reg) & SPDIFRX_RSR_IFS_MASK) >> 16)

/*
 *  ---- Version Register (Read-only) ----
 */
#घोषणा SPDIFRX_VERSION_MASK		GENMASK(11, 0)
#घोषणा SPDIFRX_VERSION_MFN_MASK	GENMASK(18, 16)
#घोषणा SPDIFRX_VERSION_MFN(reg)	(((reg) & SPDIFRX_VERSION_MFN_MASK) >> 16)

अटल bool mchp_spdअगरrx_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SPDIFRX_MR:
	हाल SPDIFRX_IMR:
	हाल SPDIFRX_ISR:
	हाल SPDIFRX_RSR:
	हाल SPDIFRX_CHSR(0, 0):
	हाल SPDIFRX_CHSR(0, 1):
	हाल SPDIFRX_CHSR(0, 2):
	हाल SPDIFRX_CHSR(0, 3):
	हाल SPDIFRX_CHSR(0, 4):
	हाल SPDIFRX_CHSR(0, 5):
	हाल SPDIFRX_CHUD(0, 0):
	हाल SPDIFRX_CHUD(0, 1):
	हाल SPDIFRX_CHUD(0, 2):
	हाल SPDIFRX_CHUD(0, 3):
	हाल SPDIFRX_CHUD(0, 4):
	हाल SPDIFRX_CHUD(0, 5):
	हाल SPDIFRX_CHSR(1, 0):
	हाल SPDIFRX_CHSR(1, 1):
	हाल SPDIFRX_CHSR(1, 2):
	हाल SPDIFRX_CHSR(1, 3):
	हाल SPDIFRX_CHSR(1, 4):
	हाल SPDIFRX_CHSR(1, 5):
	हाल SPDIFRX_CHUD(1, 0):
	हाल SPDIFRX_CHUD(1, 1):
	हाल SPDIFRX_CHUD(1, 2):
	हाल SPDIFRX_CHUD(1, 3):
	हाल SPDIFRX_CHUD(1, 4):
	हाल SPDIFRX_CHUD(1, 5):
	हाल SPDIFRX_WPMR:
	हाल SPDIFRX_WPSR:
	हाल SPDIFRX_VERSION:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool mchp_spdअगरrx_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SPDIFRX_CR:
	हाल SPDIFRX_MR:
	हाल SPDIFRX_IER:
	हाल SPDIFRX_IDR:
	हाल SPDIFRX_WPMR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool mchp_spdअगरrx_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SPDIFRX_ISR:
	हाल SPDIFRX_RHR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config mchp_spdअगरrx_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = SPDIFRX_VERSION,
	.पढ़ोable_reg = mchp_spdअगरrx_पढ़ोable_reg,
	.ग_लिखोable_reg = mchp_spdअगरrx_ग_लिखोable_reg,
	.precious_reg = mchp_spdअगरrx_precious_reg,
पूर्ण;

#घोषणा SPDIFRX_GCLK_RATIO_MIN	(12 * 64)

#घोषणा SPDIFRX_CS_BITS		192
#घोषणा SPDIFRX_UD_BITS		192

#घोषणा SPDIFRX_CHANNELS	2

काष्ठा mchp_spdअगरrx_ch_stat अणु
	अचिन्हित अक्षर data[SPDIFRX_CS_BITS / 8];
	काष्ठा completion करोne;
पूर्ण;

काष्ठा mchp_spdअगरrx_user_data अणु
	अचिन्हित अक्षर data[SPDIFRX_UD_BITS / 8];
	काष्ठा completion करोne;
	spinlock_t lock;	/* protect access to user data */
पूर्ण;

काष्ठा mchp_spdअगरrx_mixer_control अणु
		काष्ठा mchp_spdअगरrx_ch_stat ch_stat[SPDIFRX_CHANNELS];
		काष्ठा mchp_spdअगरrx_user_data user_data[SPDIFRX_CHANNELS];
		bool ulock;
		bool badf;
		bool संकेत;
पूर्ण;

काष्ठा mchp_spdअगरrx_dev अणु
	काष्ठा snd_dmaengine_dai_dma_data	capture;
	काष्ठा mchp_spdअगरrx_mixer_control	control;
	spinlock_t				blockend_lock;	/* protect access to blockend_refcount */
	पूर्णांक					blockend_refcount;
	काष्ठा device				*dev;
	काष्ठा regmap				*regmap;
	काष्ठा clk				*pclk;
	काष्ठा clk				*gclk;
	अचिन्हित पूर्णांक				fmt;
	अचिन्हित पूर्णांक				gclk_enabled:1;
पूर्ण;

अटल व्योम mchp_spdअगरrx_channel_status_पढ़ो(काष्ठा mchp_spdअगरrx_dev *dev,
					     पूर्णांक channel)
अणु
	काष्ठा mchp_spdअगरrx_mixer_control *ctrl = &dev->control;
	u8 *ch_stat = &ctrl->ch_stat[channel].data[0];
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ctrl->ch_stat[channel].data) / 4; i++) अणु
		regmap_पढ़ो(dev->regmap, SPDIFRX_CHSR(channel, i), &val);
		*ch_stat++ = val & 0xFF;
		*ch_stat++ = (val >> 8) & 0xFF;
		*ch_stat++ = (val >> 16) & 0xFF;
		*ch_stat++ = (val >> 24) & 0xFF;
	पूर्ण
पूर्ण

अटल व्योम mchp_spdअगरrx_channel_user_data_पढ़ो(काष्ठा mchp_spdअगरrx_dev *dev,
						पूर्णांक channel)
अणु
	काष्ठा mchp_spdअगरrx_mixer_control *ctrl = &dev->control;
	u8 *user_data = &ctrl->user_data[channel].data[0];
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ctrl->user_data[channel].data) / 4; i++) अणु
		regmap_पढ़ो(dev->regmap, SPDIFRX_CHUD(channel, i), &val);
		*user_data++ = val & 0xFF;
		*user_data++ = (val >> 8) & 0xFF;
		*user_data++ = (val >> 16) & 0xFF;
		*user_data++ = (val >> 24) & 0xFF;
	पूर्ण
पूर्ण

/* called from non-atomic context only */
अटल व्योम mchp_spdअगरrx_isr_blockend_en(काष्ठा mchp_spdअगरrx_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->blockend_lock, flags);
	dev->blockend_refcount++;
	/* करोn't enable BLOCKEND interrupt if it's alपढ़ोy enabled */
	अगर (dev->blockend_refcount == 1)
		regmap_ग_लिखो(dev->regmap, SPDIFRX_IER, SPDIFRX_IR_BLOCKEND);
	spin_unlock_irqrestore(&dev->blockend_lock, flags);
पूर्ण

/* called from atomic context only */
अटल व्योम mchp_spdअगरrx_isr_blockend_dis(काष्ठा mchp_spdअगरrx_dev *dev)
अणु
	spin_lock(&dev->blockend_lock);
	dev->blockend_refcount--;
	/* करोn't enable BLOCKEND interrupt if it's alपढ़ोy enabled */
	अगर (dev->blockend_refcount == 0)
		regmap_ग_लिखो(dev->regmap, SPDIFRX_IDR, SPDIFRX_IR_BLOCKEND);
	spin_unlock(&dev->blockend_lock);
पूर्ण

अटल irqवापस_t mchp_spdअगर_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mchp_spdअगरrx_dev *dev = dev_id;
	काष्ठा mchp_spdअगरrx_mixer_control *ctrl = &dev->control;
	u32 sr, imr, pending, idr = 0;
	irqवापस_t ret = IRQ_NONE;
	पूर्णांक ch;

	regmap_पढ़ो(dev->regmap, SPDIFRX_ISR, &sr);
	regmap_पढ़ो(dev->regmap, SPDIFRX_IMR, &imr);
	pending = sr & imr;
	dev_dbg(dev->dev, "ISR: %#x, IMR: %#x, pending: %#x\n", sr, imr,
		pending);

	अगर (!pending)
		वापस IRQ_NONE;

	अगर (pending & SPDIFRX_IR_BLOCKEND) अणु
		क्रम (ch = 0; ch < SPDIFRX_CHANNELS; ch++) अणु
			spin_lock(&ctrl->user_data[ch].lock);
			mchp_spdअगरrx_channel_user_data_पढ़ो(dev, ch);
			spin_unlock(&ctrl->user_data[ch].lock);

			complete(&ctrl->user_data[ch].करोne);
		पूर्ण
		mchp_spdअगरrx_isr_blockend_dis(dev);
		ret = IRQ_HANDLED;
	पूर्ण

	क्रम (ch = 0; ch < SPDIFRX_CHANNELS; ch++) अणु
		अगर (pending & SPDIFRX_IR_CSC(ch)) अणु
			mchp_spdअगरrx_channel_status_पढ़ो(dev, ch);
			complete(&ctrl->ch_stat[ch].करोne);
			idr |= SPDIFRX_IR_CSC(ch);
			ret = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	अगर (pending & SPDIFRX_IR_OVERRUN) अणु
		dev_warn(dev->dev, "Overrun detected\n");
		ret = IRQ_HANDLED;
	पूर्ण

	regmap_ग_लिखो(dev->regmap, SPDIFRX_IDR, idr);

	वापस ret;
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);
	u32 mr;
	पूर्णांक running;
	पूर्णांक ret;

	regmap_पढ़ो(dev->regmap, SPDIFRX_MR, &mr);
	running = !!(mr & SPDIFRX_MR_RXEN_ENABLE);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (!running) अणु
			mr &= ~SPDIFRX_MR_RXEN_MASK;
			mr |= SPDIFRX_MR_RXEN_ENABLE;
			/* enable overrun पूर्णांकerrupts */
			regmap_ग_लिखो(dev->regmap, SPDIFRX_IER,
				     SPDIFRX_IR_OVERRUN);
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (running) अणु
			mr &= ~SPDIFRX_MR_RXEN_MASK;
			mr |= SPDIFRX_MR_RXEN_DISABLE;
			/* disable overrun पूर्णांकerrupts */
			regmap_ग_लिखो(dev->regmap, SPDIFRX_IDR,
				     SPDIFRX_IR_OVERRUN);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap, SPDIFRX_MR, mr);
	अगर (ret) अणु
		dev_err(dev->dev, "unable to enable/disable RX: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);
	u32 mr;
	पूर्णांक ret;

	dev_dbg(dev->dev, "%s() rate=%u format=%#x width=%u channels=%u\n",
		__func__, params_rate(params), params_क्रमmat(params),
		params_width(params), params_channels(params));

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		dev_err(dev->dev, "Playback is not supported\n");
		वापस -EINVAL;
	पूर्ण

	regmap_पढ़ो(dev->regmap, SPDIFRX_MR, &mr);

	अगर (mr & SPDIFRX_MR_RXEN_ENABLE) अणु
		dev_err(dev->dev, "PCM already running\n");
		वापस -EBUSY;
	पूर्ण

	अगर (params_channels(params) != SPDIFRX_CHANNELS) अणु
		dev_err(dev->dev, "unsupported number of channels: %d\n",
			params_channels(params));
		वापस -EINVAL;
	पूर्ण

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_BE:
	हाल SNDRV_PCM_FORMAT_S20_3BE:
	हाल SNDRV_PCM_FORMAT_S24_3BE:
	हाल SNDRV_PCM_FORMAT_S24_BE:
		mr |= SPDIFRX_MR_ENDIAN_BIG;
		fallthrough;
	हाल SNDRV_PCM_FORMAT_S16_LE:
	हाल SNDRV_PCM_FORMAT_S20_3LE:
	हाल SNDRV_PCM_FORMAT_S24_3LE:
	हाल SNDRV_PCM_FORMAT_S24_LE:
		mr |= SPDIFRX_MR_DATAWIDTH(params_width(params));
		अवरोध;
	शेष:
		dev_err(dev->dev, "unsupported PCM format: %d\n",
			params_क्रमmat(params));
		वापस -EINVAL;
	पूर्ण

	अगर (dev->gclk_enabled) अणु
		clk_disable_unprepare(dev->gclk);
		dev->gclk_enabled = 0;
	पूर्ण
	ret = clk_set_min_rate(dev->gclk, params_rate(params) *
					  SPDIFRX_GCLK_RATIO_MIN + 1);
	अगर (ret) अणु
		dev_err(dev->dev,
			"unable to set gclk min rate: rate %u * ratio %u + 1\n",
			params_rate(params), SPDIFRX_GCLK_RATIO_MIN);
		वापस ret;
	पूर्ण
	ret = clk_prepare_enable(dev->gclk);
	अगर (ret) अणु
		dev_err(dev->dev, "unable to enable gclk: %d\n", ret);
		वापस ret;
	पूर्ण
	dev->gclk_enabled = 1;

	dev_dbg(dev->dev, "GCLK range min set to %d\n",
		params_rate(params) * SPDIFRX_GCLK_RATIO_MIN + 1);

	वापस regmap_ग_लिखो(dev->regmap, SPDIFRX_MR, mr);
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);

	अगर (dev->gclk_enabled) अणु
		clk_disable_unprepare(dev->gclk);
		dev->gclk_enabled = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mchp_spdअगरrx_dai_ops = अणु
	.trigger	= mchp_spdअगरrx_trigger,
	.hw_params	= mchp_spdअगरrx_hw_params,
	.hw_मुक्त	= mchp_spdअगरrx_hw_मुक्त,
पूर्ण;

#घोषणा MCHP_SPDIF_RATES	SNDRV_PCM_RATE_8000_192000

#घोषणा MCHP_SPDIF_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE |	\
				 SNDRV_PCM_FMTBIT_U16_BE |	\
				 SNDRV_PCM_FMTBIT_S20_3LE |	\
				 SNDRV_PCM_FMTBIT_S20_3BE |	\
				 SNDRV_PCM_FMTBIT_S24_3LE |	\
				 SNDRV_PCM_FMTBIT_S24_3BE |	\
				 SNDRV_PCM_FMTBIT_S24_LE |	\
				 SNDRV_PCM_FMTBIT_S24_BE	\
				)

अटल पूर्णांक mchp_spdअगरrx_info(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_cs_get(काष्ठा mchp_spdअगरrx_dev *dev,
			       पूर्णांक channel,
			       काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा mchp_spdअगरrx_mixer_control *ctrl = &dev->control;
	काष्ठा mchp_spdअगरrx_ch_stat *ch_stat = &ctrl->ch_stat[channel];
	पूर्णांक ret;

	regmap_ग_लिखो(dev->regmap, SPDIFRX_IER, SPDIFRX_IR_CSC(channel));
	/* check क्रम new data available */
	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ch_stat->करोne,
							msecs_to_jअगरfies(100));
	/* IP might not be started or valid stream might not be prezent */
	अगर (ret < 0) अणु
		dev_dbg(dev->dev, "channel status for channel %d timeout\n",
			channel);
	पूर्ण

	स_नकल(uvalue->value.iec958.status, ch_stat->data,
	       माप(ch_stat->data));

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_cs1_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);

	वापस mchp_spdअगरrx_cs_get(dev, 0, uvalue);
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_cs2_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);

	वापस mchp_spdअगरrx_cs_get(dev, 1, uvalue);
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_cs_mask(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *uvalue)
अणु
	स_रखो(uvalue->value.iec958.status, 0xff,
	       माप(uvalue->value.iec958.status));

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_subcode_ch_get(काष्ठा mchp_spdअगरrx_dev *dev,
				       पूर्णांक channel,
				       काष्ठा snd_ctl_elem_value *uvalue)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mchp_spdअगरrx_mixer_control *ctrl = &dev->control;
	काष्ठा mchp_spdअगरrx_user_data *user_data = &ctrl->user_data[channel];
	पूर्णांक ret;

	reinit_completion(&user_data->करोne);
	mchp_spdअगरrx_isr_blockend_en(dev);
	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&user_data->करोne,
							msecs_to_jअगरfies(100));
	/* IP might not be started or valid stream might not be prezent */
	अगर (ret <= 0) अणु
		dev_dbg(dev->dev, "user data for channel %d timeout\n",
			channel);
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&user_data->lock, flags);
	स_नकल(uvalue->value.iec958.subcode, user_data->data,
	       माप(user_data->data));
	spin_unlock_irqrestore(&user_data->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_subcode_ch1_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);

	वापस mchp_spdअगरrx_subcode_ch_get(dev, 0, uvalue);
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_subcode_ch2_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);

	वापस mchp_spdअगरrx_subcode_ch_get(dev, 1, uvalue);
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_boolean_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_ulock_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा mchp_spdअगरrx_mixer_control *ctrl = &dev->control;
	u32 val;
	bool ulock_old = ctrl->ulock;

	regmap_पढ़ो(dev->regmap, SPDIFRX_RSR, &val);
	ctrl->ulock = !(val & SPDIFRX_RSR_ULOCK);
	uvalue->value.पूर्णांकeger.value[0] = ctrl->ulock;

	वापस ulock_old != ctrl->ulock;
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_badf_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा mchp_spdअगरrx_mixer_control *ctrl = &dev->control;
	u32 val;
	bool badf_old = ctrl->badf;

	regmap_पढ़ो(dev->regmap, SPDIFRX_RSR, &val);
	ctrl->badf = !!(val & SPDIFRX_RSR_BADF);
	uvalue->value.पूर्णांकeger.value[0] = ctrl->badf;

	वापस badf_old != ctrl->badf;
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_संकेत_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा mchp_spdअगरrx_mixer_control *ctrl = &dev->control;
	u32 val;
	bool संकेत_old = ctrl->संकेत;

	regmap_पढ़ो(dev->regmap, SPDIFRX_RSR, &val);
	ctrl->संकेत = !(val & SPDIFRX_RSR_NOSIGNAL);
	uvalue->value.पूर्णांकeger.value[0] = ctrl->संकेत;

	वापस संकेत_old != ctrl->संकेत;
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_rate_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 192000;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_rate_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);
	u32 val;
	पूर्णांक rate;

	regmap_पढ़ो(dev->regmap, SPDIFRX_RSR, &val);

	/* अगर the receiver is not locked, ISF data is invalid */
	अगर (val & SPDIFRX_RSR_ULOCK || !(val & SPDIFRX_RSR_IFS_MASK)) अणु
		ucontrol->value.पूर्णांकeger.value[0] = 0;
		वापस 0;
	पूर्ण

	rate = clk_get_rate(dev->gclk);

	ucontrol->value.पूर्णांकeger.value[0] = rate / (32 * SPDIFRX_RSR_IFS(val));

	वापस 0;
पूर्ण

अटल काष्ठा snd_kcontrol_new mchp_spdअगरrx_ctrls[] = अणु
	/* Channel status controller */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, DEFAULT)
			" Channel 1",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = mchp_spdअगरrx_info,
		.get = mchp_spdअगरrx_cs1_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, DEFAULT)
			" Channel 2",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = mchp_spdअगरrx_info,
		.get = mchp_spdअगरrx_cs2_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, MASK),
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.info = mchp_spdअगरrx_info,
		.get = mchp_spdअगरrx_cs_mask,
	पूर्ण,
	/* User bits controller */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "IEC958 Subcode Capture Default Channel 1",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = mchp_spdअगरrx_info,
		.get = mchp_spdअगरrx_subcode_ch1_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "IEC958 Subcode Capture Default Channel 2",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = mchp_spdअगरrx_info,
		.get = mchp_spdअगरrx_subcode_ch2_get,
	पूर्ण,
	/* Lock status */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, NONE) "Unlocked",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = mchp_spdअगरrx_boolean_info,
		.get = mchp_spdअगरrx_ulock_get,
	पूर्ण,
	/* Bad क्रमmat */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, NONE)"Bad Format",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = mchp_spdअगरrx_boolean_info,
		.get = mchp_spdअगरrx_badf_get,
	पूर्ण,
	/* Signal */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, NONE) "Signal",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = mchp_spdअगरrx_boolean_info,
		.get = mchp_spdअगरrx_संकेत_get,
	पूर्ण,
	/* Sampling rate */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, NONE) "Rate",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = mchp_spdअगरrx_rate_info,
		.get = mchp_spdअगरrx_rate_get,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mchp_spdअगरrx_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा mchp_spdअगरrx_mixer_control *ctrl = &dev->control;
	पूर्णांक ch;
	पूर्णांक err;

	err = clk_prepare_enable(dev->pclk);
	अगर (err) अणु
		dev_err(dev->dev,
			"failed to enable the peripheral clock: %d\n", err);
		वापस err;
	पूर्ण

	snd_soc_dai_init_dma_data(dai, शून्य, &dev->capture);

	/* Software reset the IP */
	regmap_ग_लिखो(dev->regmap, SPDIFRX_CR, SPDIFRX_CR_SWRST);

	/* Default configuration */
	regmap_ग_लिखो(dev->regmap, SPDIFRX_MR,
		     SPDIFRX_MR_VBMODE_DISCARD_IF_VB1 |
		     SPDIFRX_MR_SBMODE_DISCARD |
		     SPDIFRX_MR_AUTORST_NOACTION |
		     SPDIFRX_MR_PACK_DISABLED);

	dev->blockend_refcount = 0;
	क्रम (ch = 0; ch < SPDIFRX_CHANNELS; ch++) अणु
		init_completion(&ctrl->ch_stat[ch].करोne);
		init_completion(&ctrl->user_data[ch].करोne);
		spin_lock_init(&ctrl->user_data[ch].lock);
	पूर्ण

	/* Add controls */
	snd_soc_add_dai_controls(dai, mchp_spdअगरrx_ctrls,
				 ARRAY_SIZE(mchp_spdअगरrx_ctrls));

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_spdअगरrx_dai_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_spdअगरrx_dev *dev = snd_soc_dai_get_drvdata(dai);

	/* Disable पूर्णांकerrupts */
	regmap_ग_लिखो(dev->regmap, SPDIFRX_IDR, 0xFF);

	clk_disable_unprepare(dev->pclk);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver mchp_spdअगरrx_dai = अणु
	.name = "mchp-spdifrx",
	.probe	= mchp_spdअगरrx_dai_probe,
	.हटाओ	= mchp_spdअगरrx_dai_हटाओ,
	.capture = अणु
		.stream_name = "S/PDIF Capture",
		.channels_min = SPDIFRX_CHANNELS,
		.channels_max = SPDIFRX_CHANNELS,
		.rates = MCHP_SPDIF_RATES,
		.क्रमmats = MCHP_SPDIF_FORMATS,
	पूर्ण,
	.ops = &mchp_spdअगरrx_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver mchp_spdअगरrx_component = अणु
	.name		= "mchp-spdifrx",
पूर्ण;

अटल स्थिर काष्ठा of_device_id mchp_spdअगरrx_dt_ids[] = अणु
	अणु
		.compatible = "microchip,sama7g5-spdifrx",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mchp_spdअगरrx_dt_ids);

अटल पूर्णांक mchp_spdअगरrx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mchp_spdअगरrx_dev *dev;
	काष्ठा resource *mem;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	पूर्णांक irq;
	पूर्णांक err;
	u32 vers;

	/* Get memory क्रम driver data. */
	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	/* Map I/O रेजिस्टरs. */
	base = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &mem);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(&pdev->dev, base,
				       &mchp_spdअगरrx_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Request IRQ. */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	err = devm_request_irq(&pdev->dev, irq, mchp_spdअगर_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), dev);
	अगर (err)
		वापस err;

	/* Get the peripheral घड़ी */
	dev->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(dev->pclk)) अणु
		err = PTR_ERR(dev->pclk);
		dev_err(&pdev->dev, "failed to get the peripheral clock: %d\n",
			err);
		वापस err;
	पूर्ण

	/* Get the generated घड़ी */
	dev->gclk = devm_clk_get(&pdev->dev, "gclk");
	अगर (IS_ERR(dev->gclk)) अणु
		err = PTR_ERR(dev->gclk);
		dev_err(&pdev->dev,
			"failed to get the PMC generated clock: %d\n", err);
		वापस err;
	पूर्ण
	spin_lock_init(&dev->blockend_lock);

	dev->dev = &pdev->dev;
	dev->regmap = regmap;
	platक्रमm_set_drvdata(pdev, dev);

	dev->capture.addr	= (dma_addr_t)mem->start + SPDIFRX_RHR;
	dev->capture.maxburst	= 1;

	err = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register PMC: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &mchp_spdअगरrx_component,
					      &mchp_spdअगरrx_dai, 1);
	अगर (err) अणु
		dev_err(&pdev->dev, "fail to register dai\n");
		वापस err;
	पूर्ण

	regmap_पढ़ो(regmap, SPDIFRX_VERSION, &vers);
	dev_info(&pdev->dev, "hw version: %#lx\n", vers & SPDIFRX_VERSION_MASK);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mchp_spdअगरrx_driver = अणु
	.probe	= mchp_spdअगरrx_probe,
	.driver	= अणु
		.name	= "mchp_spdifrx",
		.of_match_table = of_match_ptr(mchp_spdअगरrx_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mchp_spdअगरrx_driver);

MODULE_AUTHOR("Codrin Ciubotariu <codrin.ciubotariu@microchip.com>");
MODULE_DESCRIPTION("Microchip S/PDIF RX Controller Driver");
MODULE_LICENSE("GPL v2");
