<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Xilinx ASoC audio क्रमmatter support
//
// Copyright (C) 2018 Xilinx, Inc.
//
// Author: Maruthi Srinivas Bayyavarapu <maruthis@xilinx.com>

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sizes.h>

#समावेश <sound/asoundef.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>

#घोषणा DRV_NAME "xlnx_formatter_pcm"

#घोषणा XLNX_S2MM_OFFSET	0
#घोषणा XLNX_MM2S_OFFSET	0x100

#घोषणा XLNX_AUD_CORE_CONFIG	0x4
#घोषणा XLNX_AUD_CTRL		0x10
#घोषणा XLNX_AUD_STS		0x14

#घोषणा AUD_CTRL_RESET_MASK	BIT(1)
#घोषणा AUD_CFG_MM2S_MASK	BIT(15)
#घोषणा AUD_CFG_S2MM_MASK	BIT(31)

#घोषणा XLNX_AUD_FS_MULTIPLIER	0x18
#घोषणा XLNX_AUD_PERIOD_CONFIG	0x1C
#घोषणा XLNX_AUD_BUFF_ADDR_LSB	0x20
#घोषणा XLNX_AUD_BUFF_ADDR_MSB	0x24
#घोषणा XLNX_AUD_XFER_COUNT	0x28
#घोषणा XLNX_AUD_CH_STS_START	0x2C
#घोषणा XLNX_BYTES_PER_CH	0x44

#घोषणा AUD_STS_IOC_IRQ_MASK	BIT(31)
#घोषणा AUD_STS_CH_STS_MASK	BIT(29)
#घोषणा AUD_CTRL_IOC_IRQ_MASK	BIT(13)
#घोषणा AUD_CTRL_TOUT_IRQ_MASK	BIT(14)
#घोषणा AUD_CTRL_DMA_EN_MASK	BIT(0)

#घोषणा CFG_MM2S_CH_MASK	GENMASK(11, 8)
#घोषणा CFG_MM2S_CH_SHIFT	8
#घोषणा CFG_MM2S_XFER_MASK	GENMASK(14, 13)
#घोषणा CFG_MM2S_XFER_SHIFT	13
#घोषणा CFG_MM2S_PKG_MASK	BIT(12)

#घोषणा CFG_S2MM_CH_MASK	GENMASK(27, 24)
#घोषणा CFG_S2MM_CH_SHIFT	24
#घोषणा CFG_S2MM_XFER_MASK	GENMASK(30, 29)
#घोषणा CFG_S2MM_XFER_SHIFT	29
#घोषणा CFG_S2MM_PKG_MASK	BIT(28)

#घोषणा AUD_CTRL_DATA_WIDTH_SHIFT	16
#घोषणा AUD_CTRL_ACTIVE_CH_SHIFT	19
#घोषणा PERIOD_CFG_PERIODS_SHIFT	16

#घोषणा PERIODS_MIN		2
#घोषणा PERIODS_MAX		6
#घोषणा PERIOD_BYTES_MIN	192
#घोषणा PERIOD_BYTES_MAX	(50 * 1024)
#घोषणा XLNX_PARAM_UNKNOWN	0

क्रमागत bit_depth अणु
	BIT_DEPTH_8,
	BIT_DEPTH_16,
	BIT_DEPTH_20,
	BIT_DEPTH_24,
	BIT_DEPTH_32,
पूर्ण;

काष्ठा xlnx_pcm_drv_data अणु
	व्योम __iomem *mmio;
	bool s2mm_presence;
	bool mm2s_presence;
	पूर्णांक s2mm_irq;
	पूर्णांक mm2s_irq;
	काष्ठा snd_pcm_substream *play_stream;
	काष्ठा snd_pcm_substream *capture_stream;
	काष्ठा clk *axi_clk;
पूर्ण;

/*
 * काष्ठा xlnx_pcm_stream_param - stream configuration
 * @mmio: base address offset
 * @पूर्णांकerleaved: audio channels arrangement in buffer
 * @xfer_mode: data क्रमmatting mode during transfer
 * @ch_limit: Maximum channels supported
 * @buffer_size: stream ring buffer size
 */
काष्ठा xlnx_pcm_stream_param अणु
	व्योम __iomem *mmio;
	bool पूर्णांकerleaved;
	u32 xfer_mode;
	u32 ch_limit;
	u64 buffer_size;
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware xlnx_pcm_hardware = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_BATCH | SNDRV_PCM_INFO_PAUSE |
		SNDRV_PCM_INFO_RESUME,
	.क्रमmats = SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE |
		   SNDRV_PCM_FMTBIT_S24_LE,
	.channels_min = 2,
	.channels_max = 2,
	.rates = SNDRV_PCM_RATE_8000_192000,
	.rate_min = 8000,
	.rate_max = 192000,
	.buffer_bytes_max = PERIODS_MAX * PERIOD_BYTES_MAX,
	.period_bytes_min = PERIOD_BYTES_MIN,
	.period_bytes_max = PERIOD_BYTES_MAX,
	.periods_min = PERIODS_MIN,
	.periods_max = PERIODS_MAX,
पूर्ण;

क्रमागत अणु
	AES_TO_AES,
	AES_TO_PCM,
	PCM_TO_PCM,
	PCM_TO_AES
पूर्ण;

अटल व्योम xlnx_parse_aes_params(u32 chsts_reg1_val, u32 chsts_reg2_val,
				  काष्ठा device *dev)
अणु
	u32 padded, srate, bit_depth, status[2];

	अगर (chsts_reg1_val & IEC958_AES0_PROFESSIONAL) अणु
		status[0] = chsts_reg1_val & 0xff;
		status[1] = (chsts_reg1_val >> 16) & 0xff;

		चयन (status[0] & IEC958_AES0_PRO_FS) अणु
		हाल IEC958_AES0_PRO_FS_44100:
			srate = 44100;
			अवरोध;
		हाल IEC958_AES0_PRO_FS_48000:
			srate = 48000;
			अवरोध;
		हाल IEC958_AES0_PRO_FS_32000:
			srate = 32000;
			अवरोध;
		हाल IEC958_AES0_PRO_FS_NOTID:
		शेष:
			srate = XLNX_PARAM_UNKNOWN;
			अवरोध;
		पूर्ण

		चयन (status[1] & IEC958_AES2_PRO_SBITS) अणु
		हाल IEC958_AES2_PRO_WORDLEN_NOTID:
		हाल IEC958_AES2_PRO_SBITS_20:
			padded = 0;
			अवरोध;
		हाल IEC958_AES2_PRO_SBITS_24:
			padded = 4;
			अवरोध;
		शेष:
			bit_depth = XLNX_PARAM_UNKNOWN;
			जाओ log_params;
		पूर्ण

		चयन (status[1] & IEC958_AES2_PRO_WORDLEN) अणु
		हाल IEC958_AES2_PRO_WORDLEN_20_16:
			bit_depth = 16 + padded;
			अवरोध;
		हाल IEC958_AES2_PRO_WORDLEN_22_18:
			bit_depth = 18 + padded;
			अवरोध;
		हाल IEC958_AES2_PRO_WORDLEN_23_19:
			bit_depth = 19 + padded;
			अवरोध;
		हाल IEC958_AES2_PRO_WORDLEN_24_20:
			bit_depth = 20 + padded;
			अवरोध;
		हाल IEC958_AES2_PRO_WORDLEN_NOTID:
		शेष:
			bit_depth = XLNX_PARAM_UNKNOWN;
			अवरोध;
		पूर्ण

	पूर्ण अन्यथा अणु
		status[0] = (chsts_reg1_val >> 24) & 0xff;
		status[1] = chsts_reg2_val & 0xff;

		चयन (status[0] & IEC958_AES3_CON_FS) अणु
		हाल IEC958_AES3_CON_FS_44100:
			srate = 44100;
			अवरोध;
		हाल IEC958_AES3_CON_FS_48000:
			srate = 48000;
			अवरोध;
		हाल IEC958_AES3_CON_FS_32000:
			srate = 32000;
			अवरोध;
		शेष:
			srate = XLNX_PARAM_UNKNOWN;
			अवरोध;
		पूर्ण

		अगर (status[1] & IEC958_AES4_CON_MAX_WORDLEN_24)
			padded = 4;
		अन्यथा
			padded = 0;

		चयन (status[1] & IEC958_AES4_CON_WORDLEN) अणु
		हाल IEC958_AES4_CON_WORDLEN_20_16:
			bit_depth = 16 + padded;
			अवरोध;
		हाल IEC958_AES4_CON_WORDLEN_22_18:
			bit_depth = 18 + padded;
			अवरोध;
		हाल IEC958_AES4_CON_WORDLEN_23_19:
			bit_depth = 19 + padded;
			अवरोध;
		हाल IEC958_AES4_CON_WORDLEN_24_20:
			bit_depth = 20 + padded;
			अवरोध;
		हाल IEC958_AES4_CON_WORDLEN_21_17:
			bit_depth = 17 + padded;
			अवरोध;
		हाल IEC958_AES4_CON_WORDLEN_NOTID:
		शेष:
			bit_depth = XLNX_PARAM_UNKNOWN;
			अवरोध;
		पूर्ण
	पूर्ण

log_params:
	अगर (srate != XLNX_PARAM_UNKNOWN)
		dev_info(dev, "sample rate = %d\n", srate);
	अन्यथा
		dev_info(dev, "sample rate = unknown\n");

	अगर (bit_depth != XLNX_PARAM_UNKNOWN)
		dev_info(dev, "bit_depth = %d\n", bit_depth);
	अन्यथा
		dev_info(dev, "bit_depth = unknown\n");
पूर्ण

अटल पूर्णांक xlnx_क्रमmatter_pcm_reset(व्योम __iomem *mmio_base)
अणु
	u32 val, retries = 0;

	val = पढ़ोl(mmio_base + XLNX_AUD_CTRL);
	val |= AUD_CTRL_RESET_MASK;
	ग_लिखोl(val, mmio_base + XLNX_AUD_CTRL);

	val = पढ़ोl(mmio_base + XLNX_AUD_CTRL);
	/* Poll क्रम maximum समयout of approximately 100ms (1 * 100)*/
	जबतक ((val & AUD_CTRL_RESET_MASK) && (retries < 100)) अणु
		mdelay(1);
		retries++;
		val = पढ़ोl(mmio_base + XLNX_AUD_CTRL);
	पूर्ण
	अगर (val & AUD_CTRL_RESET_MASK)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम xlnx_क्रमmatter_disable_irqs(व्योम __iomem *mmio_base, पूर्णांक stream)
अणु
	u32 val;

	val = पढ़ोl(mmio_base + XLNX_AUD_CTRL);
	val &= ~AUD_CTRL_IOC_IRQ_MASK;
	अगर (stream == SNDRV_PCM_STREAM_CAPTURE)
		val &= ~AUD_CTRL_TOUT_IRQ_MASK;

	ग_लिखोl(val, mmio_base + XLNX_AUD_CTRL);
पूर्ण

अटल irqवापस_t xlnx_mm2s_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	u32 val;
	व्योम __iomem *reg;
	काष्ठा device *dev = arg;
	काष्ठा xlnx_pcm_drv_data *adata = dev_get_drvdata(dev);

	reg = adata->mmio + XLNX_MM2S_OFFSET + XLNX_AUD_STS;
	val = पढ़ोl(reg);
	अगर (val & AUD_STS_IOC_IRQ_MASK) अणु
		ग_लिखोl(val & AUD_STS_IOC_IRQ_MASK, reg);
		अगर (adata->play_stream)
			snd_pcm_period_elapsed(adata->play_stream);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t xlnx_s2mm_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	u32 val;
	व्योम __iomem *reg;
	काष्ठा device *dev = arg;
	काष्ठा xlnx_pcm_drv_data *adata = dev_get_drvdata(dev);

	reg = adata->mmio + XLNX_S2MM_OFFSET + XLNX_AUD_STS;
	val = पढ़ोl(reg);
	अगर (val & AUD_STS_IOC_IRQ_MASK) अणु
		ग_लिखोl(val & AUD_STS_IOC_IRQ_MASK, reg);
		अगर (adata->capture_stream)
			snd_pcm_period_elapsed(adata->capture_stream);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक xlnx_क्रमmatter_pcm_खोलो(काष्ठा snd_soc_component *component,
				   काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;
	u32 val, data_क्रमmat_mode;
	u32 ch_count_mask, ch_count_shअगरt, data_xfer_mode, data_xfer_shअगरt;
	काष्ठा xlnx_pcm_stream_param *stream_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा xlnx_pcm_drv_data *adata = dev_get_drvdata(component->dev);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
	    !adata->mm2s_presence)
		वापस -ENODEV;
	अन्यथा अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE &&
		 !adata->s2mm_presence)
		वापस -ENODEV;

	stream_data = kzalloc(माप(*stream_data), GFP_KERNEL);
	अगर (!stream_data)
		वापस -ENOMEM;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ch_count_mask = CFG_MM2S_CH_MASK;
		ch_count_shअगरt = CFG_MM2S_CH_SHIFT;
		data_xfer_mode = CFG_MM2S_XFER_MASK;
		data_xfer_shअगरt = CFG_MM2S_XFER_SHIFT;
		data_क्रमmat_mode = CFG_MM2S_PKG_MASK;
		stream_data->mmio = adata->mmio + XLNX_MM2S_OFFSET;
		adata->play_stream = substream;

	पूर्ण अन्यथा अणु
		ch_count_mask = CFG_S2MM_CH_MASK;
		ch_count_shअगरt = CFG_S2MM_CH_SHIFT;
		data_xfer_mode = CFG_S2MM_XFER_MASK;
		data_xfer_shअगरt = CFG_S2MM_XFER_SHIFT;
		data_क्रमmat_mode = CFG_S2MM_PKG_MASK;
		stream_data->mmio = adata->mmio + XLNX_S2MM_OFFSET;
		adata->capture_stream = substream;
	पूर्ण

	val = पढ़ोl(adata->mmio + XLNX_AUD_CORE_CONFIG);

	अगर (!(val & data_क्रमmat_mode))
		stream_data->पूर्णांकerleaved = true;

	stream_data->xfer_mode = (val & data_xfer_mode) >> data_xfer_shअगरt;
	stream_data->ch_limit = (val & ch_count_mask) >> ch_count_shअगरt;
	dev_info(component->dev,
		 "stream %d : format = %d mode = %d ch_limit = %d\n",
		 substream->stream, stream_data->पूर्णांकerleaved,
		 stream_data->xfer_mode, stream_data->ch_limit);

	snd_soc_set_runसमय_hwparams(substream, &xlnx_pcm_hardware);
	runसमय->निजी_data = stream_data;

	/* Resize the period size भागisible by 64 */
	err = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 64);
	अगर (err) अणु
		dev_err(component->dev,
			"unable to set constraint on period bytes\n");
		वापस err;
	पूर्ण

	/* enable DMA IOC irq */
	val = पढ़ोl(stream_data->mmio + XLNX_AUD_CTRL);
	val |= AUD_CTRL_IOC_IRQ_MASK;
	ग_लिखोl(val, stream_data->mmio + XLNX_AUD_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक xlnx_क्रमmatter_pcm_बंद(काष्ठा snd_soc_component *component,
				    काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक ret;
	काष्ठा xlnx_pcm_stream_param *stream_data =
			substream->runसमय->निजी_data;

	ret = xlnx_क्रमmatter_pcm_reset(stream_data->mmio);
	अगर (ret) अणु
		dev_err(component->dev, "audio formatter reset failed\n");
		जाओ err_reset;
	पूर्ण
	xlnx_क्रमmatter_disable_irqs(stream_data->mmio, substream->stream);

err_reset:
	kमुक्त(stream_data);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
xlnx_क्रमmatter_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	u32 pos;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा xlnx_pcm_stream_param *stream_data = runसमय->निजी_data;

	pos = पढ़ोl(stream_data->mmio + XLNX_AUD_XFER_COUNT);

	अगर (pos >= stream_data->buffer_size)
		pos = 0;

	वापस bytes_to_frames(runसमय, pos);
पूर्ण

अटल पूर्णांक xlnx_क्रमmatter_pcm_hw_params(काष्ठा snd_soc_component *component,
					काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	u32 low, high, active_ch, val, bytes_per_ch, bits_per_sample;
	u32 aes_reg1_val, aes_reg2_val;
	u64 size;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा xlnx_pcm_stream_param *stream_data = runसमय->निजी_data;

	active_ch = params_channels(params);
	अगर (active_ch > stream_data->ch_limit)
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE &&
	    stream_data->xfer_mode == AES_TO_PCM) अणु
		val = पढ़ोl(stream_data->mmio + XLNX_AUD_STS);
		अगर (val & AUD_STS_CH_STS_MASK) अणु
			aes_reg1_val = पढ़ोl(stream_data->mmio +
					     XLNX_AUD_CH_STS_START);
			aes_reg2_val = पढ़ोl(stream_data->mmio +
					     XLNX_AUD_CH_STS_START + 0x4);

			xlnx_parse_aes_params(aes_reg1_val, aes_reg2_val,
					      component->dev);
		पूर्ण
	पूर्ण

	size = params_buffer_bytes(params);

	stream_data->buffer_size = size;

	low = lower_32_bits(substream->dma_buffer.addr);
	high = upper_32_bits(substream->dma_buffer.addr);
	ग_लिखोl(low, stream_data->mmio + XLNX_AUD_BUFF_ADDR_LSB);
	ग_लिखोl(high, stream_data->mmio + XLNX_AUD_BUFF_ADDR_MSB);

	val = पढ़ोl(stream_data->mmio + XLNX_AUD_CTRL);
	bits_per_sample = params_width(params);
	चयन (bits_per_sample) अणु
	हाल 8:
		val |= (BIT_DEPTH_8 << AUD_CTRL_DATA_WIDTH_SHIFT);
		अवरोध;
	हाल 16:
		val |= (BIT_DEPTH_16 << AUD_CTRL_DATA_WIDTH_SHIFT);
		अवरोध;
	हाल 20:
		val |= (BIT_DEPTH_20 << AUD_CTRL_DATA_WIDTH_SHIFT);
		अवरोध;
	हाल 24:
		val |= (BIT_DEPTH_24 << AUD_CTRL_DATA_WIDTH_SHIFT);
		अवरोध;
	हाल 32:
		val |= (BIT_DEPTH_32 << AUD_CTRL_DATA_WIDTH_SHIFT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val |= active_ch << AUD_CTRL_ACTIVE_CH_SHIFT;
	ग_लिखोl(val, stream_data->mmio + XLNX_AUD_CTRL);

	val = (params_periods(params) << PERIOD_CFG_PERIODS_SHIFT)
		| params_period_bytes(params);
	ग_लिखोl(val, stream_data->mmio + XLNX_AUD_PERIOD_CONFIG);
	bytes_per_ch = DIV_ROUND_UP(params_period_bytes(params), active_ch);
	ग_लिखोl(bytes_per_ch, stream_data->mmio + XLNX_BYTES_PER_CH);

	वापस 0;
पूर्ण

अटल पूर्णांक xlnx_क्रमmatter_pcm_trigger(काष्ठा snd_soc_component *component,
				      काष्ठा snd_pcm_substream *substream,
				      पूर्णांक cmd)
अणु
	u32 val;
	काष्ठा xlnx_pcm_stream_param *stream_data =
			substream->runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		val = पढ़ोl(stream_data->mmio + XLNX_AUD_CTRL);
		val |= AUD_CTRL_DMA_EN_MASK;
		ग_लिखोl(val, stream_data->mmio + XLNX_AUD_CTRL);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		val = पढ़ोl(stream_data->mmio + XLNX_AUD_CTRL);
		val &= ~AUD_CTRL_DMA_EN_MASK;
		ग_लिखोl(val, stream_data->mmio + XLNX_AUD_CTRL);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlnx_क्रमmatter_pcm_new(काष्ठा snd_soc_component *component,
				  काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	snd_pcm_set_managed_buffer_all(rtd->pcm,
			SNDRV_DMA_TYPE_DEV, component->dev,
			xlnx_pcm_hardware.buffer_bytes_max,
			xlnx_pcm_hardware.buffer_bytes_max);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver xlnx_asoc_component = अणु
	.name		= DRV_NAME,
	.खोलो		= xlnx_क्रमmatter_pcm_खोलो,
	.बंद		= xlnx_क्रमmatter_pcm_बंद,
	.hw_params	= xlnx_क्रमmatter_pcm_hw_params,
	.trigger	= xlnx_क्रमmatter_pcm_trigger,
	.poपूर्णांकer	= xlnx_क्रमmatter_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= xlnx_क्रमmatter_pcm_new,
पूर्ण;

अटल पूर्णांक xlnx_क्रमmatter_pcm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	u32 val;
	काष्ठा xlnx_pcm_drv_data *aud_drv_data;
	काष्ठा device *dev = &pdev->dev;

	aud_drv_data = devm_kzalloc(dev, माप(*aud_drv_data), GFP_KERNEL);
	अगर (!aud_drv_data)
		वापस -ENOMEM;

	aud_drv_data->axi_clk = devm_clk_get(dev, "s_axi_lite_aclk");
	अगर (IS_ERR(aud_drv_data->axi_clk)) अणु
		ret = PTR_ERR(aud_drv_data->axi_clk);
		dev_err(dev, "failed to get s_axi_lite_aclk(%d)\n", ret);
		वापस ret;
	पूर्ण
	ret = clk_prepare_enable(aud_drv_data->axi_clk);
	अगर (ret) अणु
		dev_err(dev,
			"failed to enable s_axi_lite_aclk(%d)\n", ret);
		वापस ret;
	पूर्ण

	aud_drv_data->mmio = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(aud_drv_data->mmio)) अणु
		dev_err(dev, "audio formatter ioremap failed\n");
		ret = PTR_ERR(aud_drv_data->mmio);
		जाओ clk_err;
	पूर्ण

	val = पढ़ोl(aud_drv_data->mmio + XLNX_AUD_CORE_CONFIG);
	अगर (val & AUD_CFG_MM2S_MASK) अणु
		aud_drv_data->mm2s_presence = true;
		ret = xlnx_क्रमmatter_pcm_reset(aud_drv_data->mmio +
					       XLNX_MM2S_OFFSET);
		अगर (ret) अणु
			dev_err(dev, "audio formatter reset failed\n");
			जाओ clk_err;
		पूर्ण
		xlnx_क्रमmatter_disable_irqs(aud_drv_data->mmio +
					    XLNX_MM2S_OFFSET,
					    SNDRV_PCM_STREAM_PLAYBACK);

		aud_drv_data->mm2s_irq = platक्रमm_get_irq_byname(pdev,
								 "irq_mm2s");
		अगर (aud_drv_data->mm2s_irq < 0) अणु
			ret = aud_drv_data->mm2s_irq;
			जाओ clk_err;
		पूर्ण
		ret = devm_request_irq(dev, aud_drv_data->mm2s_irq,
				       xlnx_mm2s_irq_handler, 0,
				       "xlnx_formatter_pcm_mm2s_irq", dev);
		अगर (ret) अणु
			dev_err(dev, "xlnx audio mm2s irq request failed\n");
			जाओ clk_err;
		पूर्ण
	पूर्ण
	अगर (val & AUD_CFG_S2MM_MASK) अणु
		aud_drv_data->s2mm_presence = true;
		ret = xlnx_क्रमmatter_pcm_reset(aud_drv_data->mmio +
					       XLNX_S2MM_OFFSET);
		अगर (ret) अणु
			dev_err(dev, "audio formatter reset failed\n");
			जाओ clk_err;
		पूर्ण
		xlnx_क्रमmatter_disable_irqs(aud_drv_data->mmio +
					    XLNX_S2MM_OFFSET,
					    SNDRV_PCM_STREAM_CAPTURE);

		aud_drv_data->s2mm_irq = platक्रमm_get_irq_byname(pdev,
								 "irq_s2mm");
		अगर (aud_drv_data->s2mm_irq < 0) अणु
			ret = aud_drv_data->s2mm_irq;
			जाओ clk_err;
		पूर्ण
		ret = devm_request_irq(dev, aud_drv_data->s2mm_irq,
				       xlnx_s2mm_irq_handler, 0,
				       "xlnx_formatter_pcm_s2mm_irq",
				       dev);
		अगर (ret) अणु
			dev_err(dev, "xlnx audio s2mm irq request failed\n");
			जाओ clk_err;
		पूर्ण
	पूर्ण

	dev_set_drvdata(dev, aud_drv_data);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &xlnx_asoc_component,
					      शून्य, 0);
	अगर (ret) अणु
		dev_err(dev, "pcm platform device register failed\n");
		जाओ clk_err;
	पूर्ण

	वापस 0;

clk_err:
	clk_disable_unprepare(aud_drv_data->axi_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक xlnx_क्रमmatter_pcm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा xlnx_pcm_drv_data *adata = dev_get_drvdata(&pdev->dev);

	अगर (adata->s2mm_presence)
		ret = xlnx_क्रमmatter_pcm_reset(adata->mmio + XLNX_S2MM_OFFSET);

	/* Try MM2S reset, even अगर S2MM  reset fails */
	अगर (adata->mm2s_presence)
		ret = xlnx_क्रमmatter_pcm_reset(adata->mmio + XLNX_MM2S_OFFSET);

	अगर (ret)
		dev_err(&pdev->dev, "audio formatter reset failed\n");

	clk_disable_unprepare(adata->axi_clk);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id xlnx_क्रमmatter_pcm_of_match[] = अणु
	अणु .compatible = "xlnx,audio-formatter-1.0"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xlnx_क्रमmatter_pcm_of_match);

अटल काष्ठा platक्रमm_driver xlnx_क्रमmatter_pcm_driver = अणु
	.probe	= xlnx_क्रमmatter_pcm_probe,
	.हटाओ	= xlnx_क्रमmatter_pcm_हटाओ,
	.driver	= अणु
		.name	= DRV_NAME,
		.of_match_table	= xlnx_क्रमmatter_pcm_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xlnx_क्रमmatter_pcm_driver);
MODULE_AUTHOR("Maruthi Srinivas Bayyavarapu <maruthis@xilinx.com>");
MODULE_LICENSE("GPL v2");
