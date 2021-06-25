<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DesignWare HDMI audio driver
 *
 * Written and tested against the Designware HDMI Tx found in iMX6.
 */
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <drm/bridge/dw_hdmi.h>
#समावेश <drm/drm_edid.h>

#समावेश <sound/asoundef.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_drm_eld.h>
#समावेश <sound/pcm_iec958.h>

#समावेश "dw-hdmi-audio.h"

#घोषणा DRIVER_NAME "dw-hdmi-ahb-audio"

/* Provide some bits rather than bit offsets */
क्रमागत अणु
	HDMI_AHB_DMA_CONF0_SW_FIFO_RST = BIT(7),
	HDMI_AHB_DMA_CONF0_EN_HLOCK = BIT(3),
	HDMI_AHB_DMA_START_START = BIT(0),
	HDMI_AHB_DMA_STOP_STOP = BIT(0),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_ERROR = BIT(5),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_LOST = BIT(4),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_RETRY = BIT(3),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_DONE = BIT(2),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_BUFFFULL = BIT(1),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_BUFFEMPTY = BIT(0),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_ALL =
		HDMI_IH_MUTE_AHBDMAAUD_STAT0_ERROR |
		HDMI_IH_MUTE_AHBDMAAUD_STAT0_LOST |
		HDMI_IH_MUTE_AHBDMAAUD_STAT0_RETRY |
		HDMI_IH_MUTE_AHBDMAAUD_STAT0_DONE |
		HDMI_IH_MUTE_AHBDMAAUD_STAT0_BUFFFULL |
		HDMI_IH_MUTE_AHBDMAAUD_STAT0_BUFFEMPTY,
	HDMI_IH_AHBDMAAUD_STAT0_ERROR = BIT(5),
	HDMI_IH_AHBDMAAUD_STAT0_LOST = BIT(4),
	HDMI_IH_AHBDMAAUD_STAT0_RETRY = BIT(3),
	HDMI_IH_AHBDMAAUD_STAT0_DONE = BIT(2),
	HDMI_IH_AHBDMAAUD_STAT0_BUFFFULL = BIT(1),
	HDMI_IH_AHBDMAAUD_STAT0_BUFFEMPTY = BIT(0),
	HDMI_IH_AHBDMAAUD_STAT0_ALL =
		HDMI_IH_AHBDMAAUD_STAT0_ERROR |
		HDMI_IH_AHBDMAAUD_STAT0_LOST |
		HDMI_IH_AHBDMAAUD_STAT0_RETRY |
		HDMI_IH_AHBDMAAUD_STAT0_DONE |
		HDMI_IH_AHBDMAAUD_STAT0_BUFFFULL |
		HDMI_IH_AHBDMAAUD_STAT0_BUFFEMPTY,
	HDMI_AHB_DMA_CONF0_INCR16 = 2 << 1,
	HDMI_AHB_DMA_CONF0_INCR8 = 1 << 1,
	HDMI_AHB_DMA_CONF0_INCR4 = 0,
	HDMI_AHB_DMA_CONF0_BURST_MODE = BIT(0),
	HDMI_AHB_DMA_MASK_DONE = BIT(7),

	HDMI_REVISION_ID = 0x0001,
	HDMI_IH_AHBDMAAUD_STAT0 = 0x0109,
	HDMI_IH_MUTE_AHBDMAAUD_STAT0 = 0x0189,
	HDMI_AHB_DMA_CONF0 = 0x3600,
	HDMI_AHB_DMA_START = 0x3601,
	HDMI_AHB_DMA_STOP = 0x3602,
	HDMI_AHB_DMA_THRSLD = 0x3603,
	HDMI_AHB_DMA_STRADDR0 = 0x3604,
	HDMI_AHB_DMA_STPADDR0 = 0x3608,
	HDMI_AHB_DMA_MASK = 0x3614,
	HDMI_AHB_DMA_POL = 0x3615,
	HDMI_AHB_DMA_CONF1 = 0x3616,
	HDMI_AHB_DMA_BUFFPOL = 0x361a,
पूर्ण;

काष्ठा dw_hdmi_channel_conf अणु
	u8 conf1;
	u8 ca;
पूर्ण;

/*
 * The शेष mapping of ALSA channels to HDMI channels and speaker
 * allocation bits.  Note that we can't करो channel remapping here -
 * channels must be in the same order.
 *
 * Mappings क्रम alsa-lib pcm/surround*.conf files:
 *
 *		Front	Sur4.0	Sur4.1	Sur5.0	Sur5.1	Sur7.1
 * Channels	2	4	6	6	6	8
 *
 * Our mapping from ALSA channel to CEA686D speaker name and HDMI channel:
 *
 *				Number of ALSA channels
 * ALSA Channel	2	3	4	5	6	7	8
 * 0		FL:0	=	=	=	=	=	=
 * 1		FR:1	=	=	=	=	=	=
 * 2			FC:3	RL:4	LFE:2	=	=	=
 * 3				RR:5	RL:4	FC:3	=	=
 * 4					RR:5	RL:4	=	=
 * 5						RR:5	=	=
 * 6							RC:6	=
 * 7							RLC/FRC	RLC/FRC
 */
अटल काष्ठा dw_hdmi_channel_conf शेष_hdmi_channel_config[7] = अणु
	अणु 0x03, 0x00 पूर्ण,	/* FL,FR */
	अणु 0x0b, 0x02 पूर्ण,	/* FL,FR,FC */
	अणु 0x33, 0x08 पूर्ण,	/* FL,FR,RL,RR */
	अणु 0x37, 0x09 पूर्ण,	/* FL,FR,LFE,RL,RR */
	अणु 0x3f, 0x0b पूर्ण,	/* FL,FR,LFE,FC,RL,RR */
	अणु 0x7f, 0x0f पूर्ण,	/* FL,FR,LFE,FC,RL,RR,RC */
	अणु 0xff, 0x13 पूर्ण,	/* FL,FR,LFE,FC,RL,RR,[FR]RC,[FR]LC */
पूर्ण;

काष्ठा snd_dw_hdmi अणु
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	spinlock_t lock;
	काष्ठा dw_hdmi_audio_data data;
	काष्ठा snd_pcm_substream *substream;
	व्योम (*reक्रमmat)(काष्ठा snd_dw_hdmi *, माप_प्रकार, माप_प्रकार);
	व्योम *buf_src;
	व्योम *buf_dst;
	dma_addr_t buf_addr;
	अचिन्हित buf_offset;
	अचिन्हित buf_period;
	अचिन्हित buf_size;
	अचिन्हित channels;
	u8 revision;
	u8 iec_offset;
	u8 cs[192][8];
पूर्ण;

अटल व्योम dw_hdmi_ग_लिखोl(u32 val, व्योम __iomem *ptr)
अणु
	ग_लिखोb_relaxed(val, ptr);
	ग_लिखोb_relaxed(val >> 8, ptr + 1);
	ग_लिखोb_relaxed(val >> 16, ptr + 2);
	ग_लिखोb_relaxed(val >> 24, ptr + 3);
पूर्ण

/*
 * Convert to hardware क्रमmat: The userspace buffer contains IEC958 samples,
 * with the PCUV bits in bits 31..28 and audio samples in bits 27..4.  We
 * need these to be in bits 27..24, with the IEC B bit in bit 28, and audio
 * samples in 23..0.
 *
 * Default preamble in bits 3..0: 8 = block start, 4 = even 2 = odd
 *
 * Ideally, we could करो with having the data properly क्रमmatted in userspace.
 */
अटल व्योम dw_hdmi_reक्रमmat_iec958(काष्ठा snd_dw_hdmi *dw,
	माप_प्रकार offset, माप_प्रकार bytes)
अणु
	u32 *src = dw->buf_src + offset;
	u32 *dst = dw->buf_dst + offset;
	u32 *end = dw->buf_src + offset + bytes;

	करो अणु
		u32 b, sample = *src++;

		b = (sample & 8) << (28 - 3);

		sample >>= 4;

		*dst++ = sample | b;
	पूर्ण जबतक (src < end);
पूर्ण

अटल u32 parity(u32 sample)
अणु
	sample ^= sample >> 16;
	sample ^= sample >> 8;
	sample ^= sample >> 4;
	sample ^= sample >> 2;
	sample ^= sample >> 1;
	वापस (sample & 1) << 27;
पूर्ण

अटल व्योम dw_hdmi_reक्रमmat_s24(काष्ठा snd_dw_hdmi *dw,
	माप_प्रकार offset, माप_प्रकार bytes)
अणु
	u32 *src = dw->buf_src + offset;
	u32 *dst = dw->buf_dst + offset;
	u32 *end = dw->buf_src + offset + bytes;

	करो अणु
		अचिन्हित i;
		u8 *cs;

		cs = dw->cs[dw->iec_offset++];
		अगर (dw->iec_offset >= 192)
			dw->iec_offset = 0;

		i = dw->channels;
		करो अणु
			u32 sample = *src++;

			sample &= ~0xff000000;
			sample |= *cs++ << 24;
			sample |= parity(sample & ~0xf8000000);

			*dst++ = sample;
		पूर्ण जबतक (--i);
	पूर्ण जबतक (src < end);
पूर्ण

अटल व्योम dw_hdmi_create_cs(काष्ठा snd_dw_hdmi *dw,
	काष्ठा snd_pcm_runसमय *runसमय)
अणु
	u8 cs[4];
	अचिन्हित ch, i, j;

	snd_pcm_create_iec958_consumer(runसमय, cs, माप(cs));

	स_रखो(dw->cs, 0, माप(dw->cs));

	क्रम (ch = 0; ch < 8; ch++) अणु
		cs[2] &= ~IEC958_AES2_CON_CHANNEL;
		cs[2] |= (ch + 1) << 4;

		क्रम (i = 0; i < ARRAY_SIZE(cs); i++) अणु
			अचिन्हित c = cs[i];

			क्रम (j = 0; j < 8; j++, c >>= 1)
				dw->cs[i * 8 + j][ch] = (c & 1) << 2;
		पूर्ण
	पूर्ण
	dw->cs[0][0] |= BIT(4);
पूर्ण

अटल व्योम dw_hdmi_start_dma(काष्ठा snd_dw_hdmi *dw)
अणु
	व्योम __iomem *base = dw->data.base;
	अचिन्हित offset = dw->buf_offset;
	अचिन्हित period = dw->buf_period;
	u32 start, stop;

	dw->reक्रमmat(dw, offset, period);

	/* Clear all irqs beक्रमe enabling irqs and starting DMA */
	ग_लिखोb_relaxed(HDMI_IH_AHBDMAAUD_STAT0_ALL,
		       base + HDMI_IH_AHBDMAAUD_STAT0);

	start = dw->buf_addr + offset;
	stop = start + period - 1;

	/* Setup the hardware start/stop addresses */
	dw_hdmi_ग_लिखोl(start, base + HDMI_AHB_DMA_STRADDR0);
	dw_hdmi_ग_लिखोl(stop, base + HDMI_AHB_DMA_STPADDR0);

	ग_लिखोb_relaxed((u8)~HDMI_AHB_DMA_MASK_DONE, base + HDMI_AHB_DMA_MASK);
	ग_लिखोb(HDMI_AHB_DMA_START_START, base + HDMI_AHB_DMA_START);

	offset += period;
	अगर (offset >= dw->buf_size)
		offset = 0;
	dw->buf_offset = offset;
पूर्ण

अटल व्योम dw_hdmi_stop_dma(काष्ठा snd_dw_hdmi *dw)
अणु
	/* Disable पूर्णांकerrupts beक्रमe disabling DMA */
	ग_लिखोb_relaxed(~0, dw->data.base + HDMI_AHB_DMA_MASK);
	ग_लिखोb_relaxed(HDMI_AHB_DMA_STOP_STOP, dw->data.base + HDMI_AHB_DMA_STOP);
पूर्ण

अटल irqवापस_t snd_dw_hdmi_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा snd_dw_hdmi *dw = data;
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित stat;

	stat = पढ़ोb_relaxed(dw->data.base + HDMI_IH_AHBDMAAUD_STAT0);
	अगर (!stat)
		वापस IRQ_NONE;

	ग_लिखोb_relaxed(stat, dw->data.base + HDMI_IH_AHBDMAAUD_STAT0);

	substream = dw->substream;
	अगर (stat & HDMI_IH_AHBDMAAUD_STAT0_DONE && substream) अणु
		snd_pcm_period_elapsed(substream);

		spin_lock(&dw->lock);
		अगर (dw->substream)
			dw_hdmi_start_dma(dw);
		spin_unlock(&dw->lock);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware dw_hdmi_hw = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID,
	.क्रमmats = SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE |
		   SNDRV_PCM_FMTBIT_S24_LE,
	.rates = SNDRV_PCM_RATE_32000 |
		 SNDRV_PCM_RATE_44100 |
		 SNDRV_PCM_RATE_48000 |
		 SNDRV_PCM_RATE_88200 |
		 SNDRV_PCM_RATE_96000 |
		 SNDRV_PCM_RATE_176400 |
		 SNDRV_PCM_RATE_192000,
	.channels_min = 2,
	.channels_max = 8,
	.buffer_bytes_max = 1024 * 1024,
	.period_bytes_min = 256,
	.period_bytes_max = 8192,	/* ERR004323: must limit to 8k */
	.periods_min = 2,
	.periods_max = 16,
	.fअगरo_size = 0,
पूर्ण;

अटल पूर्णांक dw_hdmi_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_dw_hdmi *dw = substream->निजी_data;
	व्योम __iomem *base = dw->data.base;
	पूर्णांक ret;

	runसमय->hw = dw_hdmi_hw;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_eld(runसमय, dw->data.eld);
	अगर (ret < 0)
		वापस ret;

	ret = snd_pcm_limit_hw_rates(runसमय);
	अगर (ret < 0)
		वापस ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0)
		वापस ret;

	/* Limit the buffer size to the size of the pपुनः_स्मृतिated buffer */
	ret = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
					   SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					   0, substream->dma_buffer.bytes);
	अगर (ret < 0)
		वापस ret;

	/* Clear FIFO */
	ग_लिखोb_relaxed(HDMI_AHB_DMA_CONF0_SW_FIFO_RST,
		       base + HDMI_AHB_DMA_CONF0);

	/* Configure पूर्णांकerrupt polarities */
	ग_लिखोb_relaxed(~0, base + HDMI_AHB_DMA_POL);
	ग_लिखोb_relaxed(~0, base + HDMI_AHB_DMA_BUFFPOL);

	/* Keep पूर्णांकerrupts masked, and clear any pending */
	ग_लिखोb_relaxed(~0, base + HDMI_AHB_DMA_MASK);
	ग_लिखोb_relaxed(~0, base + HDMI_IH_AHBDMAAUD_STAT0);

	ret = request_irq(dw->data.irq, snd_dw_hdmi_irq, IRQF_SHARED,
			  "dw-hdmi-audio", dw);
	अगर (ret)
		वापस ret;

	/* Un-mute करोne पूर्णांकerrupt */
	ग_लिखोb_relaxed(HDMI_IH_MUTE_AHBDMAAUD_STAT0_ALL &
		       ~HDMI_IH_MUTE_AHBDMAAUD_STAT0_DONE,
		       base + HDMI_IH_MUTE_AHBDMAAUD_STAT0);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_hdmi_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dw_hdmi *dw = substream->निजी_data;

	/* Mute all पूर्णांकerrupts */
	ग_लिखोb_relaxed(HDMI_IH_MUTE_AHBDMAAUD_STAT0_ALL,
		       dw->data.base + HDMI_IH_MUTE_AHBDMAAUD_STAT0);

	मुक्त_irq(dw->data.irq, dw);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_hdmi_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_lib_मुक्त_vदो_स्मृति_buffer(substream);
पूर्ण

अटल पूर्णांक dw_hdmi_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	/* Allocate the PCM runसमय buffer, which is exposed to userspace. */
	वापस snd_pcm_lib_alloc_vदो_स्मृति_buffer(substream,
						params_buffer_bytes(params));
पूर्ण

अटल पूर्णांक dw_hdmi_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_dw_hdmi *dw = substream->निजी_data;
	u8 threshold, conf0, conf1, ca;

	/* Setup as per 3.0.5 FSL 4.1.0 BSP */
	चयन (dw->revision) अणु
	हाल 0x0a:
		conf0 = HDMI_AHB_DMA_CONF0_BURST_MODE |
			HDMI_AHB_DMA_CONF0_INCR4;
		अगर (runसमय->channels == 2)
			threshold = 126;
		अन्यथा
			threshold = 124;
		अवरोध;
	हाल 0x1a:
		conf0 = HDMI_AHB_DMA_CONF0_BURST_MODE |
			HDMI_AHB_DMA_CONF0_INCR8;
		threshold = 128;
		अवरोध;
	शेष:
		/* NOTREACHED */
		वापस -EINVAL;
	पूर्ण

	dw_hdmi_set_sample_rate(dw->data.hdmi, runसमय->rate);

	/* Minimum number of bytes in the fअगरo. */
	runसमय->hw.fअगरo_size = threshold * 32;

	conf0 |= HDMI_AHB_DMA_CONF0_EN_HLOCK;
	conf1 = शेष_hdmi_channel_config[runसमय->channels - 2].conf1;
	ca = शेष_hdmi_channel_config[runसमय->channels - 2].ca;

	ग_लिखोb_relaxed(threshold, dw->data.base + HDMI_AHB_DMA_THRSLD);
	ग_लिखोb_relaxed(conf0, dw->data.base + HDMI_AHB_DMA_CONF0);
	ग_लिखोb_relaxed(conf1, dw->data.base + HDMI_AHB_DMA_CONF1);

	dw_hdmi_set_channel_count(dw->data.hdmi, runसमय->channels);
	dw_hdmi_set_channel_allocation(dw->data.hdmi, ca);

	चयन (runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE:
		dw->reक्रमmat = dw_hdmi_reक्रमmat_iec958;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		dw_hdmi_create_cs(dw, runसमय);
		dw->reक्रमmat = dw_hdmi_reक्रमmat_s24;
		अवरोध;
	पूर्ण
	dw->iec_offset = 0;
	dw->channels = runसमय->channels;
	dw->buf_src  = runसमय->dma_area;
	dw->buf_dst  = substream->dma_buffer.area;
	dw->buf_addr = substream->dma_buffer.addr;
	dw->buf_period = snd_pcm_lib_period_bytes(substream);
	dw->buf_size = snd_pcm_lib_buffer_bytes(substream);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_hdmi_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_dw_hdmi *dw = substream->निजी_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		spin_lock_irqsave(&dw->lock, flags);
		dw->buf_offset = 0;
		dw->substream = substream;
		dw_hdmi_start_dma(dw);
		dw_hdmi_audio_enable(dw->data.hdmi);
		spin_unlock_irqrestore(&dw->lock, flags);
		substream->runसमय->delay = substream->runसमय->period_size;
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		spin_lock_irqsave(&dw->lock, flags);
		dw->substream = शून्य;
		dw_hdmi_stop_dma(dw);
		dw_hdmi_audio_disable(dw->data.hdmi);
		spin_unlock_irqrestore(&dw->lock, flags);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल snd_pcm_uframes_t dw_hdmi_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_dw_hdmi *dw = substream->निजी_data;

	/*
	 * We are unable to report the exact hardware position as
	 * पढ़ोing the 32-bit DMA position using 8-bit पढ़ोs is racy.
	 */
	वापस bytes_to_frames(runसमय, dw->buf_offset);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_dw_hdmi_ops = अणु
	.खोलो = dw_hdmi_खोलो,
	.बंद = dw_hdmi_बंद,
	.ioctl = snd_pcm_lib_ioctl,
	.hw_params = dw_hdmi_hw_params,
	.hw_मुक्त = dw_hdmi_hw_मुक्त,
	.prepare = dw_hdmi_prepare,
	.trigger = dw_hdmi_trigger,
	.poपूर्णांकer = dw_hdmi_poपूर्णांकer,
	.page = snd_pcm_lib_get_vदो_स्मृति_page,
पूर्ण;

अटल पूर्णांक snd_dw_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा dw_hdmi_audio_data *data = pdev->dev.platक्रमm_data;
	काष्ठा device *dev = pdev->dev.parent;
	काष्ठा snd_dw_hdmi *dw;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	अचिन्हित revision;
	पूर्णांक ret;

	ग_लिखोb_relaxed(HDMI_IH_MUTE_AHBDMAAUD_STAT0_ALL,
		       data->base + HDMI_IH_MUTE_AHBDMAAUD_STAT0);
	revision = पढ़ोb_relaxed(data->base + HDMI_REVISION_ID);
	अगर (revision != 0x0a && revision != 0x1a) अणु
		dev_err(dev, "dw-hdmi-audio: unknown revision 0x%02x\n",
			revision);
		वापस -ENXIO;
	पूर्ण

	ret = snd_card_new(dev, SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1,
			      THIS_MODULE, माप(काष्ठा snd_dw_hdmi), &card);
	अगर (ret < 0)
		वापस ret;

	strlcpy(card->driver, DRIVER_NAME, माप(card->driver));
	strlcpy(card->लघुname, "DW-HDMI", माप(card->लघुname));
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s rev 0x%02x, irq %d", card->लघुname, revision,
		 data->irq);

	dw = card->निजी_data;
	dw->card = card;
	dw->data = *data;
	dw->revision = revision;

	spin_lock_init(&dw->lock);

	ret = snd_pcm_new(card, "DW HDMI", 0, 1, 0, &pcm);
	अगर (ret < 0)
		जाओ err;

	dw->pcm = pcm;
	pcm->निजी_data = dw;
	strlcpy(pcm->name, DRIVER_NAME, माप(pcm->name));
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_dw_hdmi_ops);

	/*
	 * To support 8-channel 96kHz audio reliably, we need 512k
	 * to satisfy alsa with our restricted period (ERR004323).
	 */
	snd_pcm_lib_pपुनः_स्मृतिate_pages_क्रम_all(pcm, SNDRV_DMA_TYPE_DEV,
			dev, 128 * 1024, 1024 * 1024);

	ret = snd_card_रेजिस्टर(card);
	अगर (ret < 0)
		जाओ err;

	platक्रमm_set_drvdata(pdev, dw);

	वापस 0;

err:
	snd_card_मुक्त(card);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_dw_hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_dw_hdmi *dw = platक्रमm_get_drvdata(pdev);

	snd_card_मुक्त(dw->card);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_PM_SLEEP) && defined(IS_NOT_BROKEN)
/*
 * This code is fine, but requires implementation in the dw_hdmi_trigger()
 * method which is currently missing as I have no way to test this.
 */
अटल पूर्णांक snd_dw_hdmi_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_dw_hdmi *dw = dev_get_drvdata(dev);

	snd_घातer_change_state(dw->card, SNDRV_CTL_POWER_D3cold);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_dw_hdmi_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_dw_hdmi *dw = dev_get_drvdata(dev);

	snd_घातer_change_state(dw->card, SNDRV_CTL_POWER_D0);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_dw_hdmi_pm, snd_dw_hdmi_suspend,
			 snd_dw_hdmi_resume);
#घोषणा PM_OPS &snd_dw_hdmi_pm
#अन्यथा
#घोषणा PM_OPS शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver snd_dw_hdmi_driver = अणु
	.probe	= snd_dw_hdmi_probe,
	.हटाओ	= snd_dw_hdmi_हटाओ,
	.driver	= अणु
		.name = DRIVER_NAME,
		.pm = PM_OPS,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(snd_dw_hdmi_driver);

MODULE_AUTHOR("Russell King <rmk+kernel@armlinux.org.uk>");
MODULE_DESCRIPTION("Synopsis Designware HDMI AHB ALSA interface");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
