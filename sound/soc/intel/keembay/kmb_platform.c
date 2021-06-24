<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright (C) 2020 Intel Corporation.
//
// Intel KeemBay Platक्रमm driver.
//

#समावेश <linux/bitrev.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "kmb_platform.h"

#घोषणा PERIODS_MIN		2
#घोषणा PERIODS_MAX		48
#घोषणा PERIOD_BYTES_MIN	4096
#घोषणा BUFFER_BYTES_MAX	(PERIODS_MAX * PERIOD_BYTES_MIN)
#घोषणा TDM_OPERATION		5
#घोषणा I2S_OPERATION		0
#घोषणा DATA_WIDTH_CONFIG_BIT	6
#घोषणा TDM_CHANNEL_CONFIG_BIT	3

अटल स्थिर काष्ठा snd_pcm_hardware kmb_pcm_hardware = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_BATCH |
		SNDRV_PCM_INFO_BLOCK_TRANSFER,
	.rates = SNDRV_PCM_RATE_8000 |
		 SNDRV_PCM_RATE_16000 |
		 SNDRV_PCM_RATE_48000,
	.rate_min = 8000,
	.rate_max = 48000,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
		   SNDRV_PCM_FMTBIT_S24_LE |
		   SNDRV_PCM_FMTBIT_S32_LE |
		   SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE,
	.channels_min = 2,
	.channels_max = 2,
	.buffer_bytes_max = BUFFER_BYTES_MAX,
	.period_bytes_min = PERIOD_BYTES_MIN,
	.period_bytes_max = BUFFER_BYTES_MAX / PERIODS_MIN,
	.periods_min = PERIODS_MIN,
	.periods_max = PERIODS_MAX,
	.fअगरo_size = 16,
पूर्ण;

/*
 * Convert to ADV7511 HDMI hardware क्रमmat.
 * ADV7511 HDMI chip need parity bit replaced by block start bit and
 * with the preamble bits left out.
 * ALSA IEC958 subframe क्रमmat:
 * bit 0-3  = preamble (0x8 = block start)
 *     4-7  = AUX (=0)
 *     8-27 = audio data (without AUX अगर 24bit sample)
 *     28   = validity
 *     29   = user data
 *     30   = channel status
 *     31   = parity
 *
 * ADV7511 IEC958 subframe क्रमmat:
 * bit 0-23  = audio data
 *     24    = validity
 *     25    = user data
 *     26    = channel status
 *     27    = block start
 *     28-31 = 0
 * MSB to LSB bit reverse by software as hardware not supporting it.
 */
अटल व्योम hdmi_reक्रमmat_iec958(काष्ठा snd_pcm_runसमय *runसमय,
				 काष्ठा kmb_i2s_info *kmb_i2s,
				 अचिन्हित पूर्णांक tx_ptr)
अणु
	u32(*buf)[2] = (व्योम *)runसमय->dma_area;
	अचिन्हित दीर्घ temp;
	u32 i, j, sample;

	क्रम (i = 0; i < kmb_i2s->fअगरo_th; i++) अणु
		j = 0;
		करो अणु
			temp = buf[tx_ptr][j];
			/* Replace parity with block start*/
			assign_bit(31, &temp, (BIT(3) & temp));
			sample = bitrev32(temp);
			buf[tx_ptr][j] = sample << 4;
			j++;
		पूर्ण जबतक (j < 2);
		tx_ptr++;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक kmb_pcm_tx_fn(काष्ठा kmb_i2s_info *kmb_i2s,
				  काष्ठा snd_pcm_runसमय *runसमय,
				  अचिन्हित पूर्णांक tx_ptr, bool *period_elapsed)
अणु
	अचिन्हित पूर्णांक period_pos = tx_ptr % runसमय->period_size;
	व्योम __iomem *i2s_base = kmb_i2s->i2s_base;
	व्योम *buf = runसमय->dma_area;
	पूर्णांक i;

	अगर (kmb_i2s->iec958_fmt)
		hdmi_reक्रमmat_iec958(runसमय, kmb_i2s, tx_ptr);

	/* KMB i2s uses two separate L/R FIFO */
	क्रम (i = 0; i < kmb_i2s->fअगरo_th; i++) अणु
		अगर (kmb_i2s->config.data_width == 16) अणु
			ग_लिखोl(((u16(*)[2])buf)[tx_ptr][0], i2s_base + LRBR_LTHR(0));
			ग_लिखोl(((u16(*)[2])buf)[tx_ptr][1], i2s_base + RRBR_RTHR(0));
		पूर्ण अन्यथा अणु
			ग_लिखोl(((u32(*)[2])buf)[tx_ptr][0], i2s_base + LRBR_LTHR(0));
			ग_लिखोl(((u32(*)[2])buf)[tx_ptr][1], i2s_base + RRBR_RTHR(0));
		पूर्ण

		period_pos++;

		अगर (++tx_ptr >= runसमय->buffer_size)
			tx_ptr = 0;
	पूर्ण

	*period_elapsed = period_pos >= runसमय->period_size;

	वापस tx_ptr;
पूर्ण

अटल अचिन्हित पूर्णांक kmb_pcm_rx_fn(काष्ठा kmb_i2s_info *kmb_i2s,
				  काष्ठा snd_pcm_runसमय *runसमय,
				  अचिन्हित पूर्णांक rx_ptr, bool *period_elapsed)
अणु
	अचिन्हित पूर्णांक period_pos = rx_ptr % runसमय->period_size;
	व्योम __iomem *i2s_base = kmb_i2s->i2s_base;
	पूर्णांक chan = kmb_i2s->config.chan_nr;
	व्योम *buf = runसमय->dma_area;
	पूर्णांक i, j;

	/* KMB i2s uses two separate L/R FIFO */
	क्रम (i = 0; i < kmb_i2s->fअगरo_th; i++) अणु
		क्रम (j = 0; j < chan / 2; j++) अणु
			अगर (kmb_i2s->config.data_width == 16) अणु
				((u16 *)buf)[rx_ptr * chan + (j * 2)] =
						पढ़ोl(i2s_base + LRBR_LTHR(j));
				((u16 *)buf)[rx_ptr * chan + ((j * 2) + 1)] =
						पढ़ोl(i2s_base + RRBR_RTHR(j));
			पूर्ण अन्यथा अणु
				((u32 *)buf)[rx_ptr * chan + (j * 2)] =
						पढ़ोl(i2s_base + LRBR_LTHR(j));
				((u32 *)buf)[rx_ptr * chan + ((j * 2) + 1)] =
						पढ़ोl(i2s_base + RRBR_RTHR(j));
			पूर्ण
		पूर्ण
		period_pos++;

		अगर (++rx_ptr >= runसमय->buffer_size)
			rx_ptr = 0;
	पूर्ण

	*period_elapsed = period_pos >= runसमय->period_size;

	वापस rx_ptr;
पूर्ण

अटल अंतरभूत व्योम kmb_i2s_disable_channels(काष्ठा kmb_i2s_info *kmb_i2s,
					    u32 stream)
अणु
	u32 i;

	/* Disable all channels regardless of configuration*/
	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		क्रम (i = 0; i < MAX_ISR; i++)
			ग_लिखोl(0, kmb_i2s->i2s_base + TER(i));
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < MAX_ISR; i++)
			ग_लिखोl(0, kmb_i2s->i2s_base + RER(i));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम kmb_i2s_clear_irqs(काष्ठा kmb_i2s_info *kmb_i2s, u32 stream)
अणु
	काष्ठा i2s_clk_config_data *config = &kmb_i2s->config;
	u32 i;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		क्रम (i = 0; i < config->chan_nr / 2; i++)
			पढ़ोl(kmb_i2s->i2s_base + TOR(i));
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < config->chan_nr / 2; i++)
			पढ़ोl(kmb_i2s->i2s_base + ROR(i));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम kmb_i2s_irq_trigger(काष्ठा kmb_i2s_info *kmb_i2s,
				       u32 stream, पूर्णांक chan_nr, bool trigger)
अणु
	u32 i, irq;
	u32 flag;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
		flag = TX_INT_FLAG;
	अन्यथा
		flag = RX_INT_FLAG;

	क्रम (i = 0; i < chan_nr / 2; i++) अणु
		irq = पढ़ोl(kmb_i2s->i2s_base + IMR(i));

		अगर (trigger)
			irq = irq & ~flag;
		अन्यथा
			irq = irq | flag;

		ग_लिखोl(irq, kmb_i2s->i2s_base + IMR(i));
	पूर्ण
पूर्ण

अटल व्योम kmb_pcm_operation(काष्ठा kmb_i2s_info *kmb_i2s, bool playback)
अणु
	काष्ठा snd_pcm_substream *substream;
	bool period_elapsed;
	अचिन्हित पूर्णांक new_ptr;
	अचिन्हित पूर्णांक ptr;

	अगर (playback)
		substream = kmb_i2s->tx_substream;
	अन्यथा
		substream = kmb_i2s->rx_substream;

	अगर (!substream || !snd_pcm_running(substream))
		वापस;

	अगर (playback) अणु
		ptr = kmb_i2s->tx_ptr;
		new_ptr = kmb_pcm_tx_fn(kmb_i2s, substream->runसमय,
					ptr, &period_elapsed);
		cmpxchg(&kmb_i2s->tx_ptr, ptr, new_ptr);
	पूर्ण अन्यथा अणु
		ptr = kmb_i2s->rx_ptr;
		new_ptr = kmb_pcm_rx_fn(kmb_i2s, substream->runसमय,
					ptr, &period_elapsed);
		cmpxchg(&kmb_i2s->rx_ptr, ptr, new_ptr);
	पूर्ण

	अगर (period_elapsed)
		snd_pcm_period_elapsed(substream);
पूर्ण

अटल पूर्णांक kmb_pcm_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा kmb_i2s_info *kmb_i2s;

	kmb_i2s = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	snd_soc_set_runसमय_hwparams(substream, &kmb_pcm_hardware);
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	runसमय->निजी_data = kmb_i2s;

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_pcm_trigger(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा kmb_i2s_info *kmb_i2s = runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			kmb_i2s->tx_ptr = 0;
			kmb_i2s->tx_substream = substream;
		पूर्ण अन्यथा अणु
			kmb_i2s->rx_ptr = 0;
			kmb_i2s->rx_substream = substream;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			kmb_i2s->tx_substream = शून्य;
		अन्यथा
			kmb_i2s->rx_substream = शून्य;
		kmb_i2s->iec958_fmt = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t kmb_i2s_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा kmb_i2s_info *kmb_i2s = dev_id;
	काष्ठा i2s_clk_config_data *config = &kmb_i2s->config;
	irqवापस_t ret = IRQ_NONE;
	u32 tx_enabled = 0;
	u32 isr[4];
	पूर्णांक i;

	क्रम (i = 0; i < config->chan_nr / 2; i++)
		isr[i] = पढ़ोl(kmb_i2s->i2s_base + ISR(i));

	kmb_i2s_clear_irqs(kmb_i2s, SNDRV_PCM_STREAM_PLAYBACK);
	kmb_i2s_clear_irqs(kmb_i2s, SNDRV_PCM_STREAM_CAPTURE);
	/* Only check TX पूर्णांकerrupt अगर TX is active */
	tx_enabled = पढ़ोl(kmb_i2s->i2s_base + ITER);

	/*
	 * Data available. Retrieve samples from FIFO
	 */

	/*
	 * 8 channel audio will have isr[0..2] triggered,
	 * पढ़ोing the specअगरic isr based on the audio configuration,
	 * to aव्योम पढ़ोing the buffers too early.
	 */
	चयन (config->chan_nr) अणु
	हाल 2:
		अगर (isr[0] & ISR_RXDA)
			kmb_pcm_operation(kmb_i2s, false);
		ret = IRQ_HANDLED;
		अवरोध;
	हाल 4:
		अगर (isr[1] & ISR_RXDA)
			kmb_pcm_operation(kmb_i2s, false);
		ret = IRQ_HANDLED;
		अवरोध;
	हाल 8:
		अगर (isr[3] & ISR_RXDA)
			kmb_pcm_operation(kmb_i2s, false);
		ret = IRQ_HANDLED;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < config->chan_nr / 2; i++) अणु
		/*
		 * Check अगर TX fअगरo is empty. If empty fill FIFO with samples
		 */
		अगर ((isr[i] & ISR_TXFE) && tx_enabled) अणु
			kmb_pcm_operation(kmb_i2s, true);
			ret = IRQ_HANDLED;
		पूर्ण

		/* Error Handling: TX */
		अगर (isr[i] & ISR_TXFO) अणु
			dev_dbg(kmb_i2s->dev, "TX overrun (ch_id=%d)\n", i);
			ret = IRQ_HANDLED;
		पूर्ण
		/* Error Handling: RX */
		अगर (isr[i] & ISR_RXFO) अणु
			dev_dbg(kmb_i2s->dev, "RX overrun (ch_id=%d)\n", i);
			ret = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kmb_platक्रमm_pcm_new(काष्ठा snd_soc_component *component,
				काष्ठा snd_soc_pcm_runसमय *soc_runसमय)
अणु
	माप_प्रकार size = kmb_pcm_hardware.buffer_bytes_max;
	/* Use SNDRV_DMA_TYPE_CONTINUOUS as KMB करोesn't use PCI sg buffer */
	snd_pcm_set_managed_buffer_all(soc_runसमय->pcm,
				       SNDRV_DMA_TYPE_CONTINUOUS,
				       शून्य, size, size);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t kmb_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
					 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा kmb_i2s_info *kmb_i2s = runसमय->निजी_data;
	snd_pcm_uframes_t pos;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		pos = kmb_i2s->tx_ptr;
	अन्यथा
		pos = kmb_i2s->rx_ptr;

	वापस pos < runसमय->buffer_size ? pos : 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver kmb_component = अणु
	.name		= "kmb",
	.pcm_स्थिरruct	= kmb_platक्रमm_pcm_new,
	.खोलो		= kmb_pcm_खोलो,
	.trigger	= kmb_pcm_trigger,
	.poपूर्णांकer	= kmb_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver kmb_component_dma = अणु
	.name		= "kmb",
पूर्ण;

अटल पूर्णांक kmb_probe(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा kmb_i2s_info *kmb_i2s = snd_soc_dai_get_drvdata(cpu_dai);

	अगर (kmb_i2s->use_pio)
		वापस 0;

	snd_soc_dai_init_dma_data(cpu_dai, &kmb_i2s->play_dma_data,
				  &kmb_i2s->capture_dma_data);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम kmb_i2s_enable_dma(काष्ठा kmb_i2s_info *kmb_i2s, u32 stream)
अणु
	u32 dma_reg;

	dma_reg = पढ़ोl(kmb_i2s->i2s_base + I2S_DMACR);
	/* Enable DMA handshake क्रम stream */
	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
		dma_reg |= I2S_DMAEN_TXBLOCK;
	अन्यथा
		dma_reg |= I2S_DMAEN_RXBLOCK;

	ग_लिखोl(dma_reg, kmb_i2s->i2s_base + I2S_DMACR);
पूर्ण

अटल अंतरभूत व्योम kmb_i2s_disable_dma(काष्ठा kmb_i2s_info *kmb_i2s, u32 stream)
अणु
	u32 dma_reg;

	dma_reg = पढ़ोl(kmb_i2s->i2s_base + I2S_DMACR);
	/* Disable DMA handshake क्रम stream */
	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		dma_reg &= ~I2S_DMAEN_TXBLOCK;
		ग_लिखोl(1, kmb_i2s->i2s_base + I2S_RTXDMA);
	पूर्ण अन्यथा अणु
		dma_reg &= ~I2S_DMAEN_RXBLOCK;
		ग_लिखोl(1, kmb_i2s->i2s_base + I2S_RRXDMA);
	पूर्ण
	ग_लिखोl(dma_reg, kmb_i2s->i2s_base + I2S_DMACR);
पूर्ण

अटल व्योम kmb_i2s_start(काष्ठा kmb_i2s_info *kmb_i2s,
			  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा i2s_clk_config_data *config = &kmb_i2s->config;

	/* I2S Programming sequence in Keem_Bay_VPU_DB_v1.1 */
	ग_लिखोl(1, kmb_i2s->i2s_base + IER);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		ग_लिखोl(1, kmb_i2s->i2s_base + ITER);
	अन्यथा
		ग_लिखोl(1, kmb_i2s->i2s_base + IRER);

	अगर (kmb_i2s->use_pio)
		kmb_i2s_irq_trigger(kmb_i2s, substream->stream,
				    config->chan_nr, true);
	अन्यथा
		kmb_i2s_enable_dma(kmb_i2s, substream->stream);

	अगर (kmb_i2s->घड़ी_provider)
		ग_लिखोl(1, kmb_i2s->i2s_base + CER);
	अन्यथा
		ग_लिखोl(0, kmb_i2s->i2s_base + CER);
पूर्ण

अटल व्योम kmb_i2s_stop(काष्ठा kmb_i2s_info *kmb_i2s,
			 काष्ठा snd_pcm_substream *substream)
अणु
	/* I2S Programming sequence in Keem_Bay_VPU_DB_v1.1 */
	kmb_i2s_clear_irqs(kmb_i2s, substream->stream);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		ग_लिखोl(0, kmb_i2s->i2s_base + ITER);
	अन्यथा
		ग_लिखोl(0, kmb_i2s->i2s_base + IRER);

	kmb_i2s_irq_trigger(kmb_i2s, substream->stream, 8, false);

	अगर (!kmb_i2s->active) अणु
		ग_लिखोl(0, kmb_i2s->i2s_base + CER);
		ग_लिखोl(0, kmb_i2s->i2s_base + IER);
	पूर्ण
पूर्ण

अटल व्योम kmb_disable_clk(व्योम *clk)
अणु
	clk_disable_unprepare(clk);
पूर्ण

अटल पूर्णांक kmb_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा kmb_i2s_info *kmb_i2s = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक ret;

	चयन (fmt & SND_SOC_DAIFMT_CLOCK_PROVIDER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBP_CFP:
		kmb_i2s->घड़ी_provider = false;
		ret = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBC_CFC:
		ग_लिखोl(CLOCK_PROVIDER_MODE, kmb_i2s->pss_base + I2S_GEN_CFG_0);

		ret = clk_prepare_enable(kmb_i2s->clk_i2s);
		अगर (ret < 0)
			वापस ret;

		ret = devm_add_action_or_reset(kmb_i2s->dev, kmb_disable_clk,
					       kmb_i2s->clk_i2s);
		अगर (ret)
			वापस ret;

		kmb_i2s->घड़ी_provider = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kmb_dai_trigger(काष्ठा snd_pcm_substream *substream,
			   पूर्णांक cmd, काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा kmb_i2s_info *kmb_i2s  = snd_soc_dai_get_drvdata(cpu_dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		/* Keep track of i2s activity beक्रमe turn off
		 * the i2s पूर्णांकerface
		 */
		kmb_i2s->active++;
		kmb_i2s_start(kmb_i2s, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		kmb_i2s->active--;
		अगर (kmb_i2s->use_pio)
			kmb_i2s_stop(kmb_i2s, substream);
		अवरोध;
	शेष:
		वापस  -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kmb_i2s_config(काष्ठा kmb_i2s_info *kmb_i2s, पूर्णांक stream)
अणु
	काष्ठा i2s_clk_config_data *config = &kmb_i2s->config;
	u32 ch_reg;

	kmb_i2s_disable_channels(kmb_i2s, stream);

	क्रम (ch_reg = 0; ch_reg < config->chan_nr / 2; ch_reg++) अणु
		अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			ग_लिखोl(kmb_i2s->xfer_resolution,
			       kmb_i2s->i2s_base + TCR(ch_reg));

			ग_लिखोl(kmb_i2s->fअगरo_th - 1,
			       kmb_i2s->i2s_base + TFCR(ch_reg));

			ग_लिखोl(1, kmb_i2s->i2s_base + TER(ch_reg));
		पूर्ण अन्यथा अणु
			ग_लिखोl(kmb_i2s->xfer_resolution,
			       kmb_i2s->i2s_base + RCR(ch_reg));

			ग_लिखोl(kmb_i2s->fअगरo_th - 1,
			       kmb_i2s->i2s_base + RFCR(ch_reg));

			ग_लिखोl(1, kmb_i2s->i2s_base + RER(ch_reg));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक kmb_dai_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *hw_params,
			     काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा kmb_i2s_info *kmb_i2s = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा i2s_clk_config_data *config = &kmb_i2s->config;
	u32 ग_लिखो_val;
	पूर्णांक ret;

	चयन (params_क्रमmat(hw_params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		config->data_width = 16;
		kmb_i2s->ccr = 0x00;
		kmb_i2s->xfer_resolution = 0x02;
		kmb_i2s->play_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		kmb_i2s->capture_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		config->data_width = 32;
		kmb_i2s->ccr = 0x14;
		kmb_i2s->xfer_resolution = 0x05;
		kmb_i2s->play_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		kmb_i2s->capture_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE:
		kmb_i2s->iec958_fmt = true;
		fallthrough;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		config->data_width = 32;
		kmb_i2s->ccr = 0x10;
		kmb_i2s->xfer_resolution = 0x05;
		kmb_i2s->play_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		kmb_i2s->capture_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		अवरोध;
	शेष:
		dev_err(kmb_i2s->dev, "kmb: unsupported PCM fmt");
		वापस -EINVAL;
	पूर्ण

	config->chan_nr = params_channels(hw_params);

	चयन (config->chan_nr) अणु
	हाल 8:
	हाल 4:
		/*
		 * Platक्रमm is not capable of providing घड़ीs क्रम
		 * multi channel audio
		 */
		अगर (kmb_i2s->घड़ी_provider)
			वापस -EINVAL;

		ग_लिखो_val = ((config->chan_nr / 2) << TDM_CHANNEL_CONFIG_BIT) |
				(config->data_width << DATA_WIDTH_CONFIG_BIT) |
				TDM_OPERATION;

		ग_लिखोl(ग_लिखो_val, kmb_i2s->pss_base + I2S_GEN_CFG_0);
		अवरोध;
	हाल 2:
		/*
		 * Platक्रमm is only capable of providing घड़ीs need क्रम
		 * 2 channel master mode
		 */
		अगर (!(kmb_i2s->घड़ी_provider))
			वापस -EINVAL;

		ग_लिखो_val = ((config->chan_nr / 2) << TDM_CHANNEL_CONFIG_BIT) |
				(config->data_width << DATA_WIDTH_CONFIG_BIT) |
				CLOCK_PROVIDER_MODE | I2S_OPERATION;

		ग_लिखोl(ग_लिखो_val, kmb_i2s->pss_base + I2S_GEN_CFG_0);
		अवरोध;
	शेष:
		dev_dbg(kmb_i2s->dev, "channel not supported\n");
		वापस -EINVAL;
	पूर्ण

	kmb_i2s_config(kmb_i2s, substream->stream);

	ग_लिखोl(kmb_i2s->ccr, kmb_i2s->i2s_base + CCR);

	config->sample_rate = params_rate(hw_params);

	अगर (kmb_i2s->घड़ी_provider) अणु
		/* Only 2 ch supported in Master mode */
		u32 bitclk = config->sample_rate * config->data_width * 2;

		ret = clk_set_rate(kmb_i2s->clk_i2s, bitclk);
		अगर (ret) अणु
			dev_err(kmb_i2s->dev,
				"Can't set I2S clock rate: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_dai_prepare(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा kmb_i2s_info *kmb_i2s = snd_soc_dai_get_drvdata(cpu_dai);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		ग_लिखोl(1, kmb_i2s->i2s_base + TXFFR);
	अन्यथा
		ग_लिखोl(1, kmb_i2s->i2s_base + RXFFR);

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_dai_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा kmb_i2s_info *kmb_i2s = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;

	अगर (kmb_i2s->use_pio)
		वापस 0;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dma_data = &kmb_i2s->play_dma_data;
	अन्यथा
		dma_data = &kmb_i2s->capture_dma_data;

	snd_soc_dai_set_dma_data(cpu_dai, substream, dma_data);

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_dai_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा kmb_i2s_info *kmb_i2s = snd_soc_dai_get_drvdata(cpu_dai);
	/* I2S Programming sequence in Keem_Bay_VPU_DB_v1.1 */
	अगर (kmb_i2s->use_pio)
		kmb_i2s_clear_irqs(kmb_i2s, substream->stream);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		ग_लिखोl(0, kmb_i2s->i2s_base + ITER);
	अन्यथा
		ग_लिखोl(0, kmb_i2s->i2s_base + IRER);

	अगर (kmb_i2s->use_pio)
		kmb_i2s_irq_trigger(kmb_i2s, substream->stream, 8, false);
	अन्यथा
		kmb_i2s_disable_dma(kmb_i2s, substream->stream);

	अगर (!kmb_i2s->active) अणु
		ग_लिखोl(0, kmb_i2s->i2s_base + CER);
		ग_लिखोl(0, kmb_i2s->i2s_base + IER);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops kmb_dai_ops = अणु
	.startup	= kmb_dai_startup,
	.trigger	= kmb_dai_trigger,
	.hw_params	= kmb_dai_hw_params,
	.hw_मुक्त	= kmb_dai_hw_मुक्त,
	.prepare	= kmb_dai_prepare,
	.set_fmt	= kmb_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver पूर्णांकel_kmb_hdmi_dai[] = अणु
	अणु
		.name = "intel_kmb_hdmi_i2s",
		.playback = अणु
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_48000,
			.rate_min = 48000,
			.rate_max = 48000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE |
				    SNDRV_PCM_FMTBIT_S24_LE |
				    SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE),
		पूर्ण,
		.ops = &kmb_dai_ops,
		.probe = kmb_probe,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver पूर्णांकel_kmb_i2s_dai[] = अणु
	अणु
		.name = "intel_kmb_i2s",
		.playback = अणु
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_48000,
			.rate_min = 8000,
			.rate_max = 48000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S32_LE |
				    SNDRV_PCM_FMTBIT_S24_LE |
				    SNDRV_PCM_FMTBIT_S16_LE),
		पूर्ण,
		.capture = अणु
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_48000,
			.rate_min = 8000,
			.rate_max = 48000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S32_LE |
				    SNDRV_PCM_FMTBIT_S24_LE |
				    SNDRV_PCM_FMTBIT_S16_LE),
		पूर्ण,
		.ops = &kmb_dai_ops,
		.probe = kmb_probe,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver पूर्णांकel_kmb_tdm_dai[] = अणु
	अणु
		.name = "intel_kmb_tdm",
		.capture = अणु
			.channels_min = 4,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_48000,
			.rate_min = 8000,
			.rate_max = 48000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S32_LE |
				    SNDRV_PCM_FMTBIT_S24_LE |
				    SNDRV_PCM_FMTBIT_S16_LE),
		पूर्ण,
		.ops = &kmb_dai_ops,
		.probe = kmb_probe,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id kmb_plat_of_match[] = अणु
	अणु .compatible = "intel,keembay-i2s", .data = &पूर्णांकel_kmb_i2s_daiपूर्ण,
	अणु .compatible = "intel,keembay-hdmi-i2s", .data = &पूर्णांकel_kmb_hdmi_daiपूर्ण,
	अणु .compatible = "intel,keembay-tdm", .data = &पूर्णांकel_kmb_tdm_daiपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक kmb_plat_dai_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा snd_soc_dai_driver *kmb_i2s_dai;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा kmb_i2s_info *kmb_i2s;
	काष्ठा resource *res;
	पूर्णांक ret, irq;
	u32 comp1_reg;

	kmb_i2s = devm_kzalloc(dev, माप(*kmb_i2s), GFP_KERNEL);
	अगर (!kmb_i2s)
		वापस -ENOMEM;

	kmb_i2s_dai = devm_kzalloc(dev, माप(*kmb_i2s_dai), GFP_KERNEL);
	अगर (!kmb_i2s_dai)
		वापस -ENOMEM;

	match = of_match_device(kmb_plat_of_match, &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "Error: No device match found\n");
		वापस -ENODEV;
	पूर्ण
	kmb_i2s_dai = (काष्ठा snd_soc_dai_driver *) match->data;

	/* Prepare the related घड़ीs */
	kmb_i2s->clk_apb = devm_clk_get(dev, "apb_clk");
	अगर (IS_ERR(kmb_i2s->clk_apb)) अणु
		dev_err(dev, "Failed to get apb clock\n");
		वापस PTR_ERR(kmb_i2s->clk_apb);
	पूर्ण

	ret = clk_prepare_enable(kmb_i2s->clk_apb);
	अगर (ret < 0)
		वापस ret;

	ret = devm_add_action_or_reset(dev, kmb_disable_clk, kmb_i2s->clk_apb);
	अगर (ret) अणु
		dev_err(dev, "Failed to add clk_apb reset action\n");
		वापस ret;
	पूर्ण

	kmb_i2s->clk_i2s = devm_clk_get(dev, "osc");
	अगर (IS_ERR(kmb_i2s->clk_i2s)) अणु
		dev_err(dev, "Failed to get osc clock\n");
		वापस PTR_ERR(kmb_i2s->clk_i2s);
	पूर्ण

	kmb_i2s->i2s_base = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &res);
	अगर (IS_ERR(kmb_i2s->i2s_base))
		वापस PTR_ERR(kmb_i2s->i2s_base);

	kmb_i2s->pss_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(kmb_i2s->pss_base))
		वापस PTR_ERR(kmb_i2s->pss_base);

	kmb_i2s->dev = &pdev->dev;

	comp1_reg = पढ़ोl(kmb_i2s->i2s_base + I2S_COMP_PARAM_1);

	kmb_i2s->fअगरo_th = (1 << COMP1_FIFO_DEPTH(comp1_reg)) / 2;

	kmb_i2s->use_pio = !(of_property_पढ़ो_bool(np, "dmas"));

	अगर (kmb_i2s->use_pio) अणु
		irq = platक्रमm_get_irq_optional(pdev, 0);
		अगर (irq > 0) अणु
			ret = devm_request_irq(dev, irq, kmb_i2s_irq_handler, 0,
					       pdev->name, kmb_i2s);
			अगर (ret < 0) अणु
				dev_err(dev, "failed to request irq\n");
				वापस ret;
			पूर्ण
		पूर्ण
		ret = devm_snd_soc_रेजिस्टर_component(dev, &kmb_component,
						      kmb_i2s_dai, 1);
	पूर्ण अन्यथा अणु
		kmb_i2s->play_dma_data.addr = res->start + I2S_TXDMA;
		kmb_i2s->capture_dma_data.addr = res->start + I2S_RXDMA;
		ret = snd_dmaengine_pcm_रेजिस्टर(&pdev->dev,
						 शून्य, 0);
		अगर (ret) अणु
			dev_err(&pdev->dev, "could not register dmaengine: %d\n",
				ret);
			वापस ret;
		पूर्ण
		ret = devm_snd_soc_रेजिस्टर_component(dev, &kmb_component_dma,
						      kmb_i2s_dai, 1);
	पूर्ण

	अगर (ret) अणु
		dev_err(dev, "not able to register dai\n");
		वापस ret;
	पूर्ण

	/* To ensure none of the channels are enabled at boot up */
	kmb_i2s_disable_channels(kmb_i2s, SNDRV_PCM_STREAM_PLAYBACK);
	kmb_i2s_disable_channels(kmb_i2s, SNDRV_PCM_STREAM_CAPTURE);

	dev_set_drvdata(dev, kmb_i2s);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver kmb_plat_dai_driver = अणु
	.driver		= अणु
		.name		= "kmb-plat-dai",
		.of_match_table = kmb_plat_of_match,
	पूर्ण,
	.probe		= kmb_plat_dai_probe,
पूर्ण;

module_platक्रमm_driver(kmb_plat_dai_driver);

MODULE_DESCRIPTION("ASoC Intel KeemBay Platform driver");
MODULE_AUTHOR("Sia Jee Heng <jee.heng.sia@intel.com>");
MODULE_AUTHOR("Sit, Michael Wei Hong <michael.wei.hong.sit@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:kmb_platform");
