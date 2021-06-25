<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5677-spi.c  --  RT5677 ALSA SoC audio codec driver
 *
 * Copyright 2013 Realtek Semiconductor Corp.
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/clk.h>
#समावेश <linux/firmware.h>
#समावेश <linux/acpi.h>

#समावेश <sound/soc.h>

#समावेश "rt5677.h"
#समावेश "rt5677-spi.h"

#घोषणा DRV_NAME "rt5677spi"

#घोषणा RT5677_SPI_BURST_LEN	240
#घोषणा RT5677_SPI_HEADER	5
#घोषणा RT5677_SPI_FREQ		6000000

/* The AddressPhase and DataPhase of SPI commands are MSB first on the wire.
 * DataPhase word size of 16-bit commands is 2 bytes.
 * DataPhase word size of 32-bit commands is 4 bytes.
 * DataPhase word size of burst commands is 8 bytes.
 * The DSP CPU is little-endian.
 */
#घोषणा RT5677_SPI_WRITE_BURST	0x5
#घोषणा RT5677_SPI_READ_BURST	0x4
#घोषणा RT5677_SPI_WRITE_32	0x3
#घोषणा RT5677_SPI_READ_32	0x2
#घोषणा RT5677_SPI_WRITE_16	0x1
#घोषणा RT5677_SPI_READ_16	0x0

#घोषणा RT5677_BUF_BYTES_TOTAL		0x20000
#घोषणा RT5677_MIC_BUF_ADDR		0x60030000
#घोषणा RT5677_MODEL_ADDR		0x5FFC9800
#घोषणा RT5677_MIC_BUF_BYTES		((u32)(RT5677_BUF_BYTES_TOTAL - \
					माप(u32)))
#घोषणा RT5677_MIC_BUF_FIRST_READ_SIZE	0x10000

अटल काष्ठा spi_device *g_spi;
अटल DEFINE_MUTEX(spi_mutex);

काष्ठा rt5677_dsp अणु
	काष्ठा device *dev;
	काष्ठा delayed_work copy_work;
	काष्ठा mutex dma_lock;
	काष्ठा snd_pcm_substream *substream;
	माप_प्रकार dma_offset;	/* zero-based offset पूर्णांकo runसमय->dma_area */
	माप_प्रकार avail_bytes;	/* number of new bytes since last period */
	u32 mic_पढ़ो_offset;	/* zero-based offset पूर्णांकo DSP's mic buffer */
	bool new_hotword;	/* a new hotword is fired */
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware rt5677_spi_pcm_hardware = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_INTERLEAVED,
	.क्रमmats		= SNDRV_PCM_FMTBIT_S16_LE,
	.period_bytes_min	= PAGE_SIZE,
	.period_bytes_max	= RT5677_BUF_BYTES_TOTAL / 8,
	.periods_min		= 8,
	.periods_max		= 8,
	.channels_min		= 1,
	.channels_max		= 1,
	.buffer_bytes_max	= RT5677_BUF_BYTES_TOTAL,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5677_spi_dai = अणु
	/* The DAI name "rt5677-dsp-cpu-dai" is not used. The actual DAI name
	 * रेजिस्टरed with ASoC is the name of the device "spi-RT5677AA:00",
	 * because we only have one DAI. See snd_soc_रेजिस्टर_dais().
	 */
	.name = "rt5677-dsp-cpu-dai",
	.id = 0,
	.capture = अणु
		.stream_name = "DSP Capture",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_16000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण;

/* PCM क्रम streaming audio from the DSP buffer */
अटल पूर्णांक rt5677_spi_pcm_खोलो(
		काष्ठा snd_soc_component *component,
		काष्ठा snd_pcm_substream *substream)
अणु
	snd_soc_set_runसमय_hwparams(substream, &rt5677_spi_pcm_hardware);
	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_spi_pcm_बंद(
		काष्ठा snd_soc_component *component,
		काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *codec_component =
			snd_soc_rtdcom_lookup(rtd, "rt5677");
	काष्ठा rt5677_priv *rt5677 =
			snd_soc_component_get_drvdata(codec_component);
	काष्ठा rt5677_dsp *rt5677_dsp =
			snd_soc_component_get_drvdata(component);

	cancel_delayed_work_sync(&rt5677_dsp->copy_work);
	rt5677->set_dsp_vad(codec_component, false);
	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_spi_hw_params(
		काष्ठा snd_soc_component *component,
		काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा rt5677_dsp *rt5677_dsp =
			snd_soc_component_get_drvdata(component);

	mutex_lock(&rt5677_dsp->dma_lock);
	rt5677_dsp->substream = substream;
	mutex_unlock(&rt5677_dsp->dma_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_spi_hw_मुक्त(
		काष्ठा snd_soc_component *component,
		काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rt5677_dsp *rt5677_dsp =
			snd_soc_component_get_drvdata(component);

	mutex_lock(&rt5677_dsp->dma_lock);
	rt5677_dsp->substream = शून्य;
	mutex_unlock(&rt5677_dsp->dma_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_spi_prepare(
		काष्ठा snd_soc_component *component,
		काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *rt5677_component =
			snd_soc_rtdcom_lookup(rtd, "rt5677");
	काष्ठा rt5677_priv *rt5677 =
			snd_soc_component_get_drvdata(rt5677_component);
	काष्ठा rt5677_dsp *rt5677_dsp =
			snd_soc_component_get_drvdata(component);

	rt5677->set_dsp_vad(rt5677_component, true);
	rt5677_dsp->dma_offset = 0;
	rt5677_dsp->avail_bytes = 0;
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t rt5677_spi_pcm_poपूर्णांकer(
		काष्ठा snd_soc_component *component,
		काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा rt5677_dsp *rt5677_dsp =
			snd_soc_component_get_drvdata(component);

	वापस bytes_to_frames(runसमय, rt5677_dsp->dma_offset);
पूर्ण

अटल पूर्णांक rt5677_spi_mic_ग_लिखो_offset(u32 *mic_ग_लिखो_offset)
अणु
	पूर्णांक ret;
	/* Grab the first 4 bytes that hold the ग_लिखो poपूर्णांकer on the
	 * dsp, and check to make sure that it poपूर्णांकs somewhere inside the
	 * buffer.
	 */
	ret = rt5677_spi_पढ़ो(RT5677_MIC_BUF_ADDR, mic_ग_लिखो_offset,
			माप(u32));
	अगर (ret)
		वापस ret;
	/* Adjust the offset so that it's zero-based */
	*mic_ग_लिखो_offset = *mic_ग_लिखो_offset - माप(u32);
	वापस *mic_ग_लिखो_offset < RT5677_MIC_BUF_BYTES ? 0 : -EFAULT;
पूर्ण

/*
 * Copy one contiguous block of audio samples from the DSP mic buffer to the
 * dma_area of the pcm runसमय. The receiving buffer may wrap around.
 * @begin: start offset of the block to copy, in bytes.
 * @end:   offset of the first byte after the block to copy, must be greater
 *         than or equal to begin.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
अटल पूर्णांक rt5677_spi_copy_block(काष्ठा rt5677_dsp *rt5677_dsp,
		u32 begin, u32 end)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = rt5677_dsp->substream->runसमय;
	माप_प्रकार bytes_per_frame = frames_to_bytes(runसमय, 1);
	माप_प्रकार first_chunk_len, second_chunk_len;
	पूर्णांक ret;

	अगर (begin > end || runसमय->dma_bytes < 2 * bytes_per_frame) अणु
		dev_err(rt5677_dsp->dev,
			"Invalid copy from (%u, %u), dma_area size %zu\n",
			begin, end, runसमय->dma_bytes);
		वापस -EINVAL;
	पूर्ण

	/* The block to copy is empty */
	अगर (begin == end)
		वापस 0;

	/* If the incoming chunk is too big क्रम the receiving buffer, only the
	 * last "receiving buffer size - one frame" bytes are copied.
	 */
	अगर (end - begin > runसमय->dma_bytes - bytes_per_frame)
		begin = end - (runसमय->dma_bytes - bytes_per_frame);

	/* May need to split to two chunks, calculate the size of each */
	first_chunk_len = end - begin;
	second_chunk_len = 0;
	अगर (rt5677_dsp->dma_offset + first_chunk_len > runसमय->dma_bytes) अणु
		/* Receiving buffer wrapped around */
		second_chunk_len = first_chunk_len;
		first_chunk_len = runसमय->dma_bytes - rt5677_dsp->dma_offset;
		second_chunk_len -= first_chunk_len;
	पूर्ण

	/* Copy first chunk */
	ret = rt5677_spi_पढ़ो(RT5677_MIC_BUF_ADDR + माप(u32) + begin,
			runसमय->dma_area + rt5677_dsp->dma_offset,
			first_chunk_len);
	अगर (ret)
		वापस ret;
	rt5677_dsp->dma_offset += first_chunk_len;
	अगर (rt5677_dsp->dma_offset == runसमय->dma_bytes)
		rt5677_dsp->dma_offset = 0;

	/* Copy second chunk */
	अगर (second_chunk_len) अणु
		ret = rt5677_spi_पढ़ो(RT5677_MIC_BUF_ADDR + माप(u32) +
				begin + first_chunk_len, runसमय->dma_area,
				second_chunk_len);
		अगर (!ret)
			rt5677_dsp->dma_offset = second_chunk_len;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Copy a given amount of audio samples from the DSP mic buffer starting at
 * mic_पढ़ो_offset, to the dma_area of the pcm runसमय. The source buffer may
 * wrap around. mic_पढ़ो_offset is updated after successful copy.
 * @amount: amount of samples to copy, in bytes.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
अटल पूर्णांक rt5677_spi_copy(काष्ठा rt5677_dsp *rt5677_dsp, u32 amount)
अणु
	पूर्णांक ret = 0;
	u32 target;

	अगर (amount == 0)
		वापस ret;

	target = rt5677_dsp->mic_पढ़ो_offset + amount;
	/* Copy the first chunk in DSP's mic buffer */
	ret |= rt5677_spi_copy_block(rt5677_dsp, rt5677_dsp->mic_पढ़ो_offset,
			min(target, RT5677_MIC_BUF_BYTES));

	अगर (target >= RT5677_MIC_BUF_BYTES) अणु
		/* Wrap around, copy the second chunk */
		target -= RT5677_MIC_BUF_BYTES;
		ret |= rt5677_spi_copy_block(rt5677_dsp, 0, target);
	पूर्ण

	अगर (!ret)
		rt5677_dsp->mic_पढ़ो_offset = target;
	वापस ret;
पूर्ण

/*
 * A delayed work that streams audio samples from the DSP mic buffer to the
 * dma_area of the pcm runसमय via SPI.
 */
अटल व्योम rt5677_spi_copy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5677_dsp *rt5677_dsp =
		container_of(work, काष्ठा rt5677_dsp, copy_work.work);
	काष्ठा snd_pcm_runसमय *runसमय;
	u32 mic_ग_लिखो_offset;
	माप_प्रकार new_bytes, copy_bytes, period_bytes;
	अचिन्हित पूर्णांक delay;
	पूर्णांक ret = 0;

	/* Ensure runसमय->dma_area buffer करोes not go away जबतक copying. */
	mutex_lock(&rt5677_dsp->dma_lock);
	अगर (!rt5677_dsp->substream) अणु
		dev_err(rt5677_dsp->dev, "No pcm substream\n");
		जाओ करोne;
	पूर्ण

	runसमय = rt5677_dsp->substream->runसमय;

	अगर (rt5677_spi_mic_ग_लिखो_offset(&mic_ग_लिखो_offset)) अणु
		dev_err(rt5677_dsp->dev, "No mic_write_offset\n");
		जाओ करोne;
	पूर्ण

	/* If this is the first समय that we've asked क्रम streaming data after
	 * a hotword is fired, we should start पढ़ोing from the previous 2
	 * seconds of audio from wherever the mic_ग_लिखो_offset is currently.
	 */
	अगर (rt5677_dsp->new_hotword) अणु
		rt5677_dsp->new_hotword = false;
		/* See अगर buffer wraparound happens */
		अगर (mic_ग_लिखो_offset < RT5677_MIC_BUF_FIRST_READ_SIZE)
			rt5677_dsp->mic_पढ़ो_offset = RT5677_MIC_BUF_BYTES -
					(RT5677_MIC_BUF_FIRST_READ_SIZE -
					mic_ग_लिखो_offset);
		अन्यथा
			rt5677_dsp->mic_पढ़ो_offset = mic_ग_लिखो_offset -
					RT5677_MIC_BUF_FIRST_READ_SIZE;
	पूर्ण

	/* Calculate the amount of new samples in bytes */
	अगर (rt5677_dsp->mic_पढ़ो_offset <= mic_ग_लिखो_offset)
		new_bytes = mic_ग_लिखो_offset - rt5677_dsp->mic_पढ़ो_offset;
	अन्यथा
		new_bytes = RT5677_MIC_BUF_BYTES + mic_ग_लिखो_offset
				- rt5677_dsp->mic_पढ़ो_offset;

	/* Copy all new samples from DSP mic buffer, one period at a समय */
	period_bytes = snd_pcm_lib_period_bytes(rt5677_dsp->substream);
	जबतक (new_bytes) अणु
		copy_bytes = min(new_bytes, period_bytes
				- rt5677_dsp->avail_bytes);
		ret = rt5677_spi_copy(rt5677_dsp, copy_bytes);
		अगर (ret) अणु
			dev_err(rt5677_dsp->dev, "Copy failed %d\n", ret);
			जाओ करोne;
		पूर्ण
		rt5677_dsp->avail_bytes += copy_bytes;
		अगर (rt5677_dsp->avail_bytes >= period_bytes) अणु
			snd_pcm_period_elapsed(rt5677_dsp->substream);
			rt5677_dsp->avail_bytes = 0;
		पूर्ण
		new_bytes -= copy_bytes;
	पूर्ण

	delay = bytes_to_frames(runसमय, period_bytes) / (runसमय->rate / 1000);
	schedule_delayed_work(&rt5677_dsp->copy_work, msecs_to_jअगरfies(delay));
करोne:
	mutex_unlock(&rt5677_dsp->dma_lock);
पूर्ण

अटल पूर्णांक rt5677_spi_pcm_new(काष्ठा snd_soc_component *component,
			      काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	snd_pcm_set_managed_buffer_all(rtd->pcm, SNDRV_DMA_TYPE_VMALLOC,
				       शून्य, 0, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_spi_pcm_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5677_dsp *rt5677_dsp;

	rt5677_dsp = devm_kzalloc(component->dev, माप(*rt5677_dsp),
			GFP_KERNEL);
	अगर (!rt5677_dsp)
		वापस -ENOMEM;
	rt5677_dsp->dev = &g_spi->dev;
	mutex_init(&rt5677_dsp->dma_lock);
	INIT_DELAYED_WORK(&rt5677_dsp->copy_work, rt5677_spi_copy_work);

	snd_soc_component_set_drvdata(component, rt5677_dsp);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver rt5677_spi_dai_component = अणु
	.name		= DRV_NAME,
	.probe		= rt5677_spi_pcm_probe,
	.खोलो		= rt5677_spi_pcm_खोलो,
	.बंद		= rt5677_spi_pcm_बंद,
	.hw_params	= rt5677_spi_hw_params,
	.hw_मुक्त	= rt5677_spi_hw_मुक्त,
	.prepare	= rt5677_spi_prepare,
	.poपूर्णांकer	= rt5677_spi_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= rt5677_spi_pcm_new,
पूर्ण;

/* Select a suitable transfer command क्रम the next transfer to ensure
 * the transfer address is always naturally aligned जबतक minimizing
 * the total number of transfers required.
 *
 * 3 transfer commands are available:
 * RT5677_SPI_READ/WRITE_16:	Transfer 2 bytes
 * RT5677_SPI_READ/WRITE_32:	Transfer 4 bytes
 * RT5677_SPI_READ/WRITE_BURST:	Transfer any multiples of 8 bytes
 *
 * Note:
 * 16 Bit ग_लिखोs and पढ़ोs are restricted to the address range
 * 0x18020000 ~ 0x18021000
 *
 * For example, पढ़ोing 256 bytes at 0x60030004 uses the following commands:
 * 0x60030004 RT5677_SPI_READ_32	4 bytes
 * 0x60030008 RT5677_SPI_READ_BURST	240 bytes
 * 0x600300F8 RT5677_SPI_READ_BURST	8 bytes
 * 0x60030100 RT5677_SPI_READ_32	4 bytes
 *
 * Input:
 * @पढ़ो: true क्रम पढ़ो commands; false क्रम ग_लिखो commands
 * @align: alignment of the next transfer address
 * @reमुख्य: number of bytes reमुख्यing to transfer
 *
 * Output:
 * @len: number of bytes to transfer with the selected command
 * Returns the selected command
 */
अटल u8 rt5677_spi_select_cmd(bool पढ़ो, u32 align, u32 reमुख्य, u32 *len)
अणु
	u8 cmd;

	अगर (align == 4 || reमुख्य <= 4) अणु
		cmd = RT5677_SPI_READ_32;
		*len = 4;
	पूर्ण अन्यथा अणु
		cmd = RT5677_SPI_READ_BURST;
		*len = (((reमुख्य - 1) >> 3) + 1) << 3;
		*len = min_t(u32, *len, RT5677_SPI_BURST_LEN);
	पूर्ण
	वापस पढ़ो ? cmd : cmd + 1;
पूर्ण

/* Copy dstlen bytes from src to dst, जबतक reversing byte order क्रम each word.
 * If srclen < dstlen, zeros are padded.
 */
अटल व्योम rt5677_spi_reverse(u8 *dst, u32 dstlen, स्थिर u8 *src, u32 srclen)
अणु
	u32 w, i, si;
	u32 word_size = min_t(u32, dstlen, 8);

	क्रम (w = 0; w < dstlen; w += word_size) अणु
		क्रम (i = 0; i < word_size && i + w < dstlen; i++) अणु
			si = w + word_size - i - 1;
			dst[w + i] = si < srclen ? src[si] : 0;
		पूर्ण
	पूर्ण
पूर्ण

/* Read DSP address space using SPI. addr and len have to be 4-byte aligned. */
पूर्णांक rt5677_spi_पढ़ो(u32 addr, व्योम *rxbuf, माप_प्रकार len)
अणु
	u32 offset;
	पूर्णांक status = 0;
	काष्ठा spi_transfer t[2];
	काष्ठा spi_message m;
	/* +4 bytes is क्रम the DummyPhase following the AddressPhase */
	u8 header[RT5677_SPI_HEADER + 4];
	u8 body[RT5677_SPI_BURST_LEN];
	u8 spi_cmd;
	u8 *cb = rxbuf;

	अगर (!g_spi)
		वापस -ENODEV;

	अगर ((addr & 3) || (len & 3)) अणु
		dev_err(&g_spi->dev, "Bad read align 0x%x(%zu)\n", addr, len);
		वापस -EACCES;
	पूर्ण

	स_रखो(t, 0, माप(t));
	t[0].tx_buf = header;
	t[0].len = माप(header);
	t[0].speed_hz = RT5677_SPI_FREQ;
	t[1].rx_buf = body;
	t[1].speed_hz = RT5677_SPI_FREQ;
	spi_message_init_with_transfers(&m, t, ARRAY_SIZE(t));

	क्रम (offset = 0; offset < len; offset += t[1].len) अणु
		spi_cmd = rt5677_spi_select_cmd(true, (addr + offset) & 7,
				len - offset, &t[1].len);

		/* Conकाष्ठा SPI message header */
		header[0] = spi_cmd;
		header[1] = ((addr + offset) & 0xff000000) >> 24;
		header[2] = ((addr + offset) & 0x00ff0000) >> 16;
		header[3] = ((addr + offset) & 0x0000ff00) >> 8;
		header[4] = ((addr + offset) & 0x000000ff) >> 0;

		mutex_lock(&spi_mutex);
		status |= spi_sync(g_spi, &m);
		mutex_unlock(&spi_mutex);


		/* Copy data back to caller buffer */
		rt5677_spi_reverse(cb + offset, len - offset, body, t[1].len);
	पूर्ण
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(rt5677_spi_पढ़ो);

/* Write DSP address space using SPI. addr has to be 4-byte aligned.
 * If len is not 4-byte aligned, then extra zeros are written at the end
 * as padding.
 */
पूर्णांक rt5677_spi_ग_लिखो(u32 addr, स्थिर व्योम *txbuf, माप_प्रकार len)
अणु
	u32 offset;
	पूर्णांक status = 0;
	काष्ठा spi_transfer t;
	काष्ठा spi_message m;
	/* +1 byte is क्रम the DummyPhase following the DataPhase */
	u8 buf[RT5677_SPI_HEADER + RT5677_SPI_BURST_LEN + 1];
	u8 *body = buf + RT5677_SPI_HEADER;
	u8 spi_cmd;
	स्थिर u8 *cb = txbuf;

	अगर (!g_spi)
		वापस -ENODEV;

	अगर (addr & 3) अणु
		dev_err(&g_spi->dev, "Bad write align 0x%x(%zu)\n", addr, len);
		वापस -EACCES;
	पूर्ण

	स_रखो(&t, 0, माप(t));
	t.tx_buf = buf;
	t.speed_hz = RT5677_SPI_FREQ;
	spi_message_init_with_transfers(&m, &t, 1);

	क्रम (offset = 0; offset < len;) अणु
		spi_cmd = rt5677_spi_select_cmd(false, (addr + offset) & 7,
				len - offset, &t.len);

		/* Conकाष्ठा SPI message header */
		buf[0] = spi_cmd;
		buf[1] = ((addr + offset) & 0xff000000) >> 24;
		buf[2] = ((addr + offset) & 0x00ff0000) >> 16;
		buf[3] = ((addr + offset) & 0x0000ff00) >> 8;
		buf[4] = ((addr + offset) & 0x000000ff) >> 0;

		/* Fetch data from caller buffer */
		rt5677_spi_reverse(body, t.len, cb + offset, len - offset);
		offset += t.len;
		t.len += RT5677_SPI_HEADER + 1;

		mutex_lock(&spi_mutex);
		status |= spi_sync(g_spi, &m);
		mutex_unlock(&spi_mutex);
	पूर्ण
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(rt5677_spi_ग_लिखो);

पूर्णांक rt5677_spi_ग_लिखो_firmware(u32 addr, स्थिर काष्ठा firmware *fw)
अणु
	वापस rt5677_spi_ग_लिखो(addr, fw->data, fw->size);
पूर्ण
EXPORT_SYMBOL_GPL(rt5677_spi_ग_लिखो_firmware);

व्योम rt5677_spi_hotword_detected(व्योम)
अणु
	काष्ठा rt5677_dsp *rt5677_dsp;

	अगर (!g_spi)
		वापस;

	rt5677_dsp = dev_get_drvdata(&g_spi->dev);
	अगर (!rt5677_dsp) अणु
		dev_err(&g_spi->dev, "Can't get rt5677_dsp\n");
		वापस;
	पूर्ण

	mutex_lock(&rt5677_dsp->dma_lock);
	dev_info(rt5677_dsp->dev, "Hotword detected\n");
	rt5677_dsp->new_hotword = true;
	mutex_unlock(&rt5677_dsp->dma_lock);

	schedule_delayed_work(&rt5677_dsp->copy_work, 0);
पूर्ण
EXPORT_SYMBOL_GPL(rt5677_spi_hotword_detected);

अटल पूर्णांक rt5677_spi_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;

	g_spi = spi;

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
					      &rt5677_spi_dai_component,
					      &rt5677_spi_dai, 1);
	अगर (ret < 0)
		dev_err(&spi->dev, "Failed to register component.\n");

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt5677_spi_acpi_id[] = अणु
	अणु "RT5677AA", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt5677_spi_acpi_id);
#पूर्ण_अगर

अटल काष्ठा spi_driver rt5677_spi_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.acpi_match_table = ACPI_PTR(rt5677_spi_acpi_id),
	पूर्ण,
	.probe = rt5677_spi_probe,
पूर्ण;
module_spi_driver(rt5677_spi_driver);

MODULE_DESCRIPTION("ASoC RT5677 SPI driver");
MODULE_AUTHOR("Oder Chiou <oder_chiou@realtek.com>");
MODULE_LICENSE("GPL v2");
