<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2011-2017, The Linux Foundation. All rights reserved.
// Copyright (c) 2018, Linaro Limited

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/pcm.h>
#समावेश <linux/spinlock.h>
#समावेश <sound/compress_driver.h>
#समावेश <यंत्र/dma.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_device.h>
#समावेश <sound/pcm_params.h>
#समावेश "q6asm.h"
#समावेश "q6routing.h"
#समावेश "q6dsp-errno.h"

#घोषणा DRV_NAME	"q6asm-fe-dai"

#घोषणा PLAYBACK_MIN_NUM_PERIODS    2
#घोषणा PLAYBACK_MAX_NUM_PERIODS   8
#घोषणा PLAYBACK_MAX_PERIOD_SIZE    65536
#घोषणा PLAYBACK_MIN_PERIOD_SIZE    128
#घोषणा CAPTURE_MIN_NUM_PERIODS     2
#घोषणा CAPTURE_MAX_NUM_PERIODS     8
#घोषणा CAPTURE_MAX_PERIOD_SIZE     4096
#घोषणा CAPTURE_MIN_PERIOD_SIZE     320
#घोषणा SID_MASK_DEFAULT	0xF

/* Default values used अगर user space करोes not set */
#घोषणा COMPR_PLAYBACK_MIN_FRAGMENT_SIZE (8 * 1024)
#घोषणा COMPR_PLAYBACK_MAX_FRAGMENT_SIZE (128 * 1024)
#घोषणा COMPR_PLAYBACK_MIN_NUM_FRAGMENTS (4)
#घोषणा COMPR_PLAYBACK_MAX_NUM_FRAGMENTS (16 * 4)

#घोषणा ALAC_CH_LAYOUT_MONO   ((101 << 16) | 1)
#घोषणा ALAC_CH_LAYOUT_STEREO ((101 << 16) | 2)

क्रमागत stream_state अणु
	Q6ASM_STREAM_IDLE = 0,
	Q6ASM_STREAM_STOPPED,
	Q6ASM_STREAM_RUNNING,
पूर्ण;

काष्ठा q6यंत्र_dai_rtd अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_compr_stream *cstream;
	काष्ठा snd_codec codec;
	काष्ठा snd_dma_buffer dma_buffer;
	spinlock_t lock;
	phys_addr_t phys;
	अचिन्हित पूर्णांक pcm_size;
	अचिन्हित पूर्णांक pcm_count;
	अचिन्हित पूर्णांक pcm_irq_pos;       /* IRQ position */
	अचिन्हित पूर्णांक periods;
	अचिन्हित पूर्णांक bytes_sent;
	अचिन्हित पूर्णांक bytes_received;
	अचिन्हित पूर्णांक copied_total;
	uपूर्णांक16_t bits_per_sample;
	uपूर्णांक16_t source; /* Encoding source bit mask */
	काष्ठा audio_client *audio_client;
	uपूर्णांक32_t next_track_stream_id;
	bool next_track;
	uपूर्णांक32_t stream_id;
	uपूर्णांक16_t session_id;
	क्रमागत stream_state state;
	uपूर्णांक32_t initial_samples_drop;
	uपूर्णांक32_t trailing_samples_drop;
	bool notअगरy_on_drain;
पूर्ण;

काष्ठा q6यंत्र_dai_data अणु
	काष्ठा snd_soc_dai_driver *dais;
	पूर्णांक num_dais;
	दीर्घ दीर्घ पूर्णांक sid;
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware q6यंत्र_dai_hardware_capture = अणु
	.info =                 (SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_BATCH |
				SNDRV_PCM_INFO_BLOCK_TRANSFER |
				SNDRV_PCM_INFO_MMAP_VALID |
				SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME),
	.क्रमmats =              (SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_S24_LE),
	.rates =                SNDRV_PCM_RATE_8000_48000,
	.rate_min =             8000,
	.rate_max =             48000,
	.channels_min =         1,
	.channels_max =         4,
	.buffer_bytes_max =     CAPTURE_MAX_NUM_PERIODS *
				CAPTURE_MAX_PERIOD_SIZE,
	.period_bytes_min =	CAPTURE_MIN_PERIOD_SIZE,
	.period_bytes_max =     CAPTURE_MAX_PERIOD_SIZE,
	.periods_min =          CAPTURE_MIN_NUM_PERIODS,
	.periods_max =          CAPTURE_MAX_NUM_PERIODS,
	.fअगरo_size =            0,
पूर्ण;

अटल काष्ठा snd_pcm_hardware q6यंत्र_dai_hardware_playback = अणु
	.info =                 (SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_BATCH |
				SNDRV_PCM_INFO_BLOCK_TRANSFER |
				SNDRV_PCM_INFO_MMAP_VALID |
				SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME),
	.क्रमmats =              (SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_S24_LE),
	.rates =                SNDRV_PCM_RATE_8000_192000,
	.rate_min =             8000,
	.rate_max =             192000,
	.channels_min =         1,
	.channels_max =         8,
	.buffer_bytes_max =     (PLAYBACK_MAX_NUM_PERIODS *
				PLAYBACK_MAX_PERIOD_SIZE),
	.period_bytes_min =	PLAYBACK_MIN_PERIOD_SIZE,
	.period_bytes_max =     PLAYBACK_MAX_PERIOD_SIZE,
	.periods_min =          PLAYBACK_MIN_NUM_PERIODS,
	.periods_max =          PLAYBACK_MAX_NUM_PERIODS,
	.fअगरo_size =            0,
पूर्ण;

#घोषणा Q6ASM_FEDAI_DRIVER(num) अणु \
		.playback = अणु						\
			.stream_name = "MultiMedia"#num" Playback",	\
			.rates = (SNDRV_PCM_RATE_8000_192000|		\
					SNDRV_PCM_RATE_KNOT),		\
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE |		\
					SNDRV_PCM_FMTBIT_S24_LE),	\
			.channels_min = 1,				\
			.channels_max = 8,				\
			.rate_min =     8000,				\
			.rate_max =	192000,				\
		पूर्ण,							\
		.capture = अणु						\
			.stream_name = "MultiMedia"#num" Capture",	\
			.rates = (SNDRV_PCM_RATE_8000_48000|		\
					SNDRV_PCM_RATE_KNOT),		\
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE |		\
				    SNDRV_PCM_FMTBIT_S24_LE),		\
			.channels_min = 1,				\
			.channels_max = 4,				\
			.rate_min =     8000,				\
			.rate_max =	48000,				\
		पूर्ण,							\
		.name = "MultiMedia"#num,				\
		.id = MSM_FRONTEND_DAI_MULTIMEDIA##num,			\
	पूर्ण

/* Conventional and unconventional sample rate supported */
अटल अचिन्हित पूर्णांक supported_sample_rates[] = अणु
	8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000,
	88200, 96000, 176400, 192000
पूर्ण;

अटल काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_sample_rates = अणु
	.count = ARRAY_SIZE(supported_sample_rates),
	.list = supported_sample_rates,
	.mask = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_compr_codec_caps q6यंत्र_compr_caps = अणु
	.num_descriptors = 1,
	.descriptor[0].max_ch = 2,
	.descriptor[0].sample_rates = अणु	8000, 11025, 12000, 16000, 22050,
					24000, 32000, 44100, 48000, 88200,
					96000, 176400, 192000 पूर्ण,
	.descriptor[0].num_sample_rates = 13,
	.descriptor[0].bit_rate[0] = 320,
	.descriptor[0].bit_rate[1] = 128,
	.descriptor[0].num_bitrates = 2,
	.descriptor[0].profiles = 0,
	.descriptor[0].modes = SND_AUDIOCHANMODE_MP3_STEREO,
	.descriptor[0].क्रमmats = 0,
पूर्ण;

अटल व्योम event_handler(uपूर्णांक32_t opcode, uपूर्णांक32_t token,
			  व्योम *payload, व्योम *priv)
अणु
	काष्ठा q6यंत्र_dai_rtd *prtd = priv;
	काष्ठा snd_pcm_substream *substream = prtd->substream;

	चयन (opcode) अणु
	हाल ASM_CLIENT_EVENT_CMD_RUN_DONE:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			q6यंत्र_ग_लिखो_async(prtd->audio_client, prtd->stream_id,
				   prtd->pcm_count, 0, 0, 0);
		अवरोध;
	हाल ASM_CLIENT_EVENT_CMD_EOS_DONE:
		prtd->state = Q6ASM_STREAM_STOPPED;
		अवरोध;
	हाल ASM_CLIENT_EVENT_DATA_WRITE_DONE: अणु
		prtd->pcm_irq_pos += prtd->pcm_count;
		snd_pcm_period_elapsed(substream);
		अगर (prtd->state == Q6ASM_STREAM_RUNNING)
			q6यंत्र_ग_लिखो_async(prtd->audio_client, prtd->stream_id,
					   prtd->pcm_count, 0, 0, 0);

		अवरोध;
		पूर्ण
	हाल ASM_CLIENT_EVENT_DATA_READ_DONE:
		prtd->pcm_irq_pos += prtd->pcm_count;
		snd_pcm_period_elapsed(substream);
		अगर (prtd->state == Q6ASM_STREAM_RUNNING)
			q6यंत्र_पढ़ो(prtd->audio_client, prtd->stream_id);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक q6यंत्र_dai_prepare(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *soc_prtd = asoc_substream_to_rtd(substream);
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;
	काष्ठा q6यंत्र_dai_data *pdata;
	काष्ठा device *dev = component->dev;
	पूर्णांक ret, i;

	pdata = snd_soc_component_get_drvdata(component);
	अगर (!pdata)
		वापस -EINVAL;

	अगर (!prtd || !prtd->audio_client) अणु
		dev_err(dev, "%s: private data null or audio client freed\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	prtd->pcm_count = snd_pcm_lib_period_bytes(substream);
	prtd->pcm_irq_pos = 0;
	/* rate and channels are sent to audio driver */
	अगर (prtd->state) अणु
		/* clear the previous setup अगर any  */
		q6यंत्र_cmd(prtd->audio_client, prtd->stream_id, CMD_CLOSE);
		q6यंत्र_unmap_memory_regions(substream->stream,
					   prtd->audio_client);
		q6routing_stream_बंद(soc_prtd->dai_link->id,
					 substream->stream);
	पूर्ण

	ret = q6यंत्र_map_memory_regions(substream->stream, prtd->audio_client,
				       prtd->phys,
				       (prtd->pcm_size / prtd->periods),
				       prtd->periods);

	अगर (ret < 0) अणु
		dev_err(dev, "Audio Start: Buffer Allocation failed rc = %d\n",
							ret);
		वापस -ENOMEM;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ret = q6यंत्र_खोलो_ग_लिखो(prtd->audio_client, prtd->stream_id,
				       FORMAT_LINEAR_PCM,
				       0, prtd->bits_per_sample, false);
	पूर्ण अन्यथा अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		ret = q6यंत्र_खोलो_पढ़ो(prtd->audio_client, prtd->stream_id,
				      FORMAT_LINEAR_PCM,
				      prtd->bits_per_sample);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(dev, "%s: q6asm_open_write failed\n", __func__);
		q6यंत्र_audio_client_मुक्त(prtd->audio_client);
		prtd->audio_client = शून्य;
		वापस -ENOMEM;
	पूर्ण

	prtd->session_id = q6यंत्र_get_session_id(prtd->audio_client);
	ret = q6routing_stream_खोलो(soc_prtd->dai_link->id, LEGACY_PCM_MODE,
			      prtd->session_id, substream->stream);
	अगर (ret) अणु
		dev_err(dev, "%s: stream reg failed ret:%d\n", __func__, ret);
		वापस ret;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ret = q6यंत्र_media_क्रमmat_block_multi_ch_pcm(
				prtd->audio_client, prtd->stream_id,
				runसमय->rate, runसमय->channels, शून्य,
				prtd->bits_per_sample);
	पूर्ण अन्यथा अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		ret = q6यंत्र_enc_cfg_blk_pcm_क्रमmat_support(prtd->audio_client,
							   prtd->stream_id,
							   runसमय->rate,
							   runसमय->channels,
							   prtd->bits_per_sample);

		/* Queue the buffers */
		क्रम (i = 0; i < runसमय->periods; i++)
			q6यंत्र_पढ़ो(prtd->audio_client, prtd->stream_id);

	पूर्ण
	अगर (ret < 0)
		dev_info(dev, "%s: CMD Format block failed\n", __func__);

	prtd->state = Q6ASM_STREAM_RUNNING;

	वापस 0;
पूर्ण

अटल पूर्णांक q6यंत्र_dai_trigger(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = q6यंत्र_run_noरुको(prtd->audio_client, prtd->stream_id,
				       0, 0, 0);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		prtd->state = Q6ASM_STREAM_STOPPED;
		ret = q6यंत्र_cmd_noरुको(prtd->audio_client, prtd->stream_id,
				       CMD_EOS);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = q6यंत्र_cmd_noरुको(prtd->audio_client, prtd->stream_id,
				       CMD_PAUSE);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक q6यंत्र_dai_खोलो(काष्ठा snd_soc_component *component,
			  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *soc_prtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(soc_prtd, 0);
	काष्ठा q6यंत्र_dai_rtd *prtd;
	काष्ठा q6यंत्र_dai_data *pdata;
	काष्ठा device *dev = component->dev;
	पूर्णांक ret = 0;
	पूर्णांक stream_id;

	stream_id = cpu_dai->driver->id;

	pdata = snd_soc_component_get_drvdata(component);
	अगर (!pdata) अणु
		dev_err(dev, "Drv data not found ..\n");
		वापस -EINVAL;
	पूर्ण

	prtd = kzalloc(माप(काष्ठा q6यंत्र_dai_rtd), GFP_KERNEL);
	अगर (prtd == शून्य)
		वापस -ENOMEM;

	prtd->substream = substream;
	prtd->audio_client = q6यंत्र_audio_client_alloc(dev,
				(q6यंत्र_cb)event_handler, prtd, stream_id,
				LEGACY_PCM_MODE);
	अगर (IS_ERR(prtd->audio_client)) अणु
		dev_info(dev, "%s: Could not allocate memory\n", __func__);
		ret = PTR_ERR(prtd->audio_client);
		kमुक्त(prtd);
		वापस ret;
	पूर्ण

	/* DSP expects stream id from 1 */
	prtd->stream_id = 1;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		runसमय->hw = q6यंत्र_dai_hardware_playback;
	अन्यथा अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		runसमय->hw = q6यंत्र_dai_hardware_capture;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE,
				&स्थिरraपूर्णांकs_sample_rates);
	अगर (ret < 0)
		dev_info(dev, "snd_pcm_hw_constraint_list failed\n");
	/* Ensure that buffer size is a multiple of period size */
	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0)
		dev_info(dev, "snd_pcm_hw_constraint_integer failed\n");

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ret = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
			SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
			PLAYBACK_MIN_NUM_PERIODS * PLAYBACK_MIN_PERIOD_SIZE,
			PLAYBACK_MAX_NUM_PERIODS * PLAYBACK_MAX_PERIOD_SIZE);
		अगर (ret < 0) अणु
			dev_err(dev, "constraint for buffer bytes min max ret = %d\n",
				ret);
		पूर्ण
	पूर्ण

	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
		SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 32);
	अगर (ret < 0) अणु
		dev_err(dev, "constraint for period bytes step ret = %d\n",
								ret);
	पूर्ण
	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
		SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 32);
	अगर (ret < 0) अणु
		dev_err(dev, "constraint for buffer bytes step ret = %d\n",
								ret);
	पूर्ण

	runसमय->निजी_data = prtd;

	snd_soc_set_runसमय_hwparams(substream, &q6यंत्र_dai_hardware_playback);

	runसमय->dma_bytes = q6यंत्र_dai_hardware_playback.buffer_bytes_max;


	अगर (pdata->sid < 0)
		prtd->phys = substream->dma_buffer.addr;
	अन्यथा
		prtd->phys = substream->dma_buffer.addr | (pdata->sid << 32);

	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);

	वापस 0;
पूर्ण

अटल पूर्णांक q6यंत्र_dai_बंद(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *soc_prtd = asoc_substream_to_rtd(substream);
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;

	अगर (prtd->audio_client) अणु
		अगर (prtd->state)
			q6यंत्र_cmd(prtd->audio_client, prtd->stream_id,
				  CMD_CLOSE);

		q6यंत्र_unmap_memory_regions(substream->stream,
					   prtd->audio_client);
		q6यंत्र_audio_client_मुक्त(prtd->audio_client);
		prtd->audio_client = शून्य;
	पूर्ण
	q6routing_stream_बंद(soc_prtd->dai_link->id,
						substream->stream);
	kमुक्त(prtd);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t q6यंत्र_dai_poपूर्णांकer(काष्ठा snd_soc_component *component,
					   काष्ठा snd_pcm_substream *substream)
अणु

	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;

	अगर (prtd->pcm_irq_pos >= prtd->pcm_size)
		prtd->pcm_irq_pos = 0;

	वापस bytes_to_frames(runसमय, (prtd->pcm_irq_pos));
पूर्ण

अटल पूर्णांक q6यंत्र_dai_mmap(काष्ठा snd_soc_component *component,
			  काष्ठा snd_pcm_substream *substream,
			  काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा device *dev = component->dev;

	वापस dma_mmap_coherent(dev, vma,
			runसमय->dma_area, runसमय->dma_addr,
			runसमय->dma_bytes);
पूर्ण

अटल पूर्णांक q6यंत्र_dai_hw_params(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;

	prtd->pcm_size = params_buffer_bytes(params);
	prtd->periods = params_periods(params);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		prtd->bits_per_sample = 16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		prtd->bits_per_sample = 24;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम compress_event_handler(uपूर्णांक32_t opcode, uपूर्णांक32_t token,
				   व्योम *payload, व्योम *priv)
अणु
	काष्ठा q6यंत्र_dai_rtd *prtd = priv;
	काष्ठा snd_compr_stream *substream = prtd->cstream;
	अचिन्हित दीर्घ flags;
	u32 wflags = 0;
	uपूर्णांक64_t avail;
	uपूर्णांक32_t bytes_written, bytes_to_ग_लिखो;
	bool is_last_buffer = false;

	चयन (opcode) अणु
	हाल ASM_CLIENT_EVENT_CMD_RUN_DONE:
		spin_lock_irqsave(&prtd->lock, flags);
		अगर (!prtd->bytes_sent) अणु
			q6यंत्र_stream_हटाओ_initial_silence(prtd->audio_client,
						    prtd->stream_id,
						    prtd->initial_samples_drop);

			q6यंत्र_ग_लिखो_async(prtd->audio_client, prtd->stream_id,
					  prtd->pcm_count, 0, 0, 0);
			prtd->bytes_sent += prtd->pcm_count;
		पूर्ण

		spin_unlock_irqrestore(&prtd->lock, flags);
		अवरोध;

	हाल ASM_CLIENT_EVENT_CMD_EOS_DONE:
		spin_lock_irqsave(&prtd->lock, flags);
		अगर (prtd->notअगरy_on_drain) अणु
			अगर (substream->partial_drain) अणु
				/*
				 * Close old stream and make it stale, चयन
				 * the active stream now!
				 */
				q6यंत्र_cmd_noरुको(prtd->audio_client,
						 prtd->stream_id,
						 CMD_CLOSE);
				/*
				 * vaild stream ids start from 1, So we are
				 * toggling this between 1 and 2.
				 */
				prtd->stream_id = (prtd->stream_id == 1 ? 2 : 1);
			पूर्ण

			snd_compr_drain_notअगरy(prtd->cstream);
			prtd->notअगरy_on_drain = false;

		पूर्ण अन्यथा अणु
			prtd->state = Q6ASM_STREAM_STOPPED;
		पूर्ण
		spin_unlock_irqrestore(&prtd->lock, flags);
		अवरोध;

	हाल ASM_CLIENT_EVENT_DATA_WRITE_DONE:
		spin_lock_irqsave(&prtd->lock, flags);

		bytes_written = token >> ASM_WRITE_TOKEN_LEN_SHIFT;
		prtd->copied_total += bytes_written;
		snd_compr_fragment_elapsed(substream);

		अगर (prtd->state != Q6ASM_STREAM_RUNNING) अणु
			spin_unlock_irqrestore(&prtd->lock, flags);
			अवरोध;
		पूर्ण

		avail = prtd->bytes_received - prtd->bytes_sent;
		अगर (avail > prtd->pcm_count) अणु
			bytes_to_ग_लिखो = prtd->pcm_count;
		पूर्ण अन्यथा अणु
			अगर (substream->partial_drain || prtd->notअगरy_on_drain)
				is_last_buffer = true;
			bytes_to_ग_लिखो = avail;
		पूर्ण

		अगर (bytes_to_ग_लिखो) अणु
			अगर (substream->partial_drain && is_last_buffer) अणु
				wflags |= ASM_LAST_BUFFER_FLAG;
				q6यंत्र_stream_हटाओ_trailing_silence(prtd->audio_client,
						     prtd->stream_id,
						     prtd->trailing_samples_drop);
			पूर्ण

			q6यंत्र_ग_लिखो_async(prtd->audio_client, prtd->stream_id,
					  bytes_to_ग_लिखो, 0, 0, wflags);

			prtd->bytes_sent += bytes_to_ग_लिखो;
		पूर्ण

		अगर (prtd->notअगरy_on_drain && is_last_buffer)
			q6यंत्र_cmd_noरुको(prtd->audio_client,
					 prtd->stream_id, CMD_EOS);

		spin_unlock_irqrestore(&prtd->lock, flags);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक q6यंत्र_dai_compr_खोलो(काष्ठा snd_soc_component *component,
				काष्ठा snd_compr_stream *stream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = stream->निजी_data;
	काष्ठा snd_compr_runसमय *runसमय = stream->runसमय;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा q6यंत्र_dai_data *pdata;
	काष्ठा device *dev = component->dev;
	काष्ठा q6यंत्र_dai_rtd *prtd;
	पूर्णांक stream_id, size, ret;

	stream_id = cpu_dai->driver->id;
	pdata = snd_soc_component_get_drvdata(component);
	अगर (!pdata) अणु
		dev_err(dev, "Drv data not found ..\n");
		वापस -EINVAL;
	पूर्ण

	prtd = kzalloc(माप(*prtd), GFP_KERNEL);
	अगर (!prtd)
		वापस -ENOMEM;

	/* DSP expects stream id from 1 */
	prtd->stream_id = 1;

	prtd->cstream = stream;
	prtd->audio_client = q6यंत्र_audio_client_alloc(dev,
					(q6यंत्र_cb)compress_event_handler,
					prtd, stream_id, LEGACY_PCM_MODE);
	अगर (IS_ERR(prtd->audio_client)) अणु
		dev_err(dev, "Could not allocate memory\n");
		ret = PTR_ERR(prtd->audio_client);
		जाओ मुक्त_prtd;
	पूर्ण

	size = COMPR_PLAYBACK_MAX_FRAGMENT_SIZE *
			COMPR_PLAYBACK_MAX_NUM_FRAGMENTS;
	ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, dev, size,
				  &prtd->dma_buffer);
	अगर (ret) अणु
		dev_err(dev, "Cannot allocate buffer(s)\n");
		जाओ मुक्त_client;
	पूर्ण

	अगर (pdata->sid < 0)
		prtd->phys = prtd->dma_buffer.addr;
	अन्यथा
		prtd->phys = prtd->dma_buffer.addr | (pdata->sid << 32);

	snd_compr_set_runसमय_buffer(stream, &prtd->dma_buffer);
	spin_lock_init(&prtd->lock);
	runसमय->निजी_data = prtd;

	वापस 0;

मुक्त_client:
	q6यंत्र_audio_client_मुक्त(prtd->audio_client);
मुक्त_prtd:
	kमुक्त(prtd);

	वापस ret;
पूर्ण

अटल पूर्णांक q6यंत्र_dai_compr_मुक्त(काष्ठा snd_soc_component *component,
				काष्ठा snd_compr_stream *stream)
अणु
	काष्ठा snd_compr_runसमय *runसमय = stream->runसमय;
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;
	काष्ठा snd_soc_pcm_runसमय *rtd = stream->निजी_data;

	अगर (prtd->audio_client) अणु
		अगर (prtd->state) अणु
			q6यंत्र_cmd(prtd->audio_client, prtd->stream_id,
				  CMD_CLOSE);
			अगर (prtd->next_track_stream_id) अणु
				q6यंत्र_cmd(prtd->audio_client,
					  prtd->next_track_stream_id,
					  CMD_CLOSE);
			पूर्ण
		पूर्ण

		snd_dma_मुक्त_pages(&prtd->dma_buffer);
		q6यंत्र_unmap_memory_regions(stream->direction,
					   prtd->audio_client);
		q6यंत्र_audio_client_मुक्त(prtd->audio_client);
		prtd->audio_client = शून्य;
	पूर्ण
	q6routing_stream_बंद(rtd->dai_link->id, stream->direction);
	kमुक्त(prtd);

	वापस 0;
पूर्ण

अटल पूर्णांक __q6यंत्र_dai_compr_set_codec_params(काष्ठा snd_soc_component *component,
					      काष्ठा snd_compr_stream *stream,
					      काष्ठा snd_codec *codec,
					      पूर्णांक stream_id)
अणु
	काष्ठा snd_compr_runसमय *runसमय = stream->runसमय;
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;
	काष्ठा q6यंत्र_flac_cfg flac_cfg;
	काष्ठा q6यंत्र_wma_cfg wma_cfg;
	काष्ठा q6यंत्र_alac_cfg alac_cfg;
	काष्ठा q6यंत्र_ape_cfg ape_cfg;
	अचिन्हित पूर्णांक wma_v9 = 0;
	काष्ठा device *dev = component->dev;
	पूर्णांक ret;
	जोड़ snd_codec_options *codec_options;
	काष्ठा snd_dec_flac *flac;
	काष्ठा snd_dec_wma *wma;
	काष्ठा snd_dec_alac *alac;
	काष्ठा snd_dec_ape *ape;

	codec_options = &(prtd->codec.options);

	स_नकल(&prtd->codec, codec, माप(*codec));

	चयन (codec->id) अणु
	हाल SND_AUDIOCODEC_FLAC:

		स_रखो(&flac_cfg, 0x0, माप(काष्ठा q6यंत्र_flac_cfg));
		flac = &codec_options->flac_d;

		flac_cfg.ch_cfg = codec->ch_in;
		flac_cfg.sample_rate = codec->sample_rate;
		flac_cfg.stream_info_present = 1;
		flac_cfg.sample_size = flac->sample_size;
		flac_cfg.min_blk_size = flac->min_blk_size;
		flac_cfg.max_blk_size = flac->max_blk_size;
		flac_cfg.max_frame_size = flac->max_frame_size;
		flac_cfg.min_frame_size = flac->min_frame_size;

		ret = q6यंत्र_stream_media_क्रमmat_block_flac(prtd->audio_client,
							   stream_id,
							   &flac_cfg);
		अगर (ret < 0) अणु
			dev_err(dev, "FLAC CMD Format block failed:%d\n", ret);
			वापस -EIO;
		पूर्ण
		अवरोध;

	हाल SND_AUDIOCODEC_WMA:
		wma = &codec_options->wma_d;

		स_रखो(&wma_cfg, 0x0, माप(काष्ठा q6यंत्र_wma_cfg));

		wma_cfg.sample_rate =  codec->sample_rate;
		wma_cfg.num_channels = codec->ch_in;
		wma_cfg.bytes_per_sec = codec->bit_rate / 8;
		wma_cfg.block_align = codec->align;
		wma_cfg.bits_per_sample = prtd->bits_per_sample;
		wma_cfg.enc_options = wma->encoder_option;
		wma_cfg.adv_enc_options = wma->adv_encoder_option;
		wma_cfg.adv_enc_options2 = wma->adv_encoder_option2;

		अगर (wma_cfg.num_channels == 1)
			wma_cfg.channel_mask = 4; /* Mono Center */
		अन्यथा अगर (wma_cfg.num_channels == 2)
			wma_cfg.channel_mask = 3; /* Stereo FL/FR */
		अन्यथा
			वापस -EINVAL;

		/* check the codec profile */
		चयन (codec->profile) अणु
		हाल SND_AUDIOPROखाता_WMA9:
			wma_cfg.fmtag = 0x161;
			wma_v9 = 1;
			अवरोध;

		हाल SND_AUDIOPROखाता_WMA10:
			wma_cfg.fmtag = 0x166;
			अवरोध;

		हाल SND_AUDIOPROखाता_WMA9_PRO:
			wma_cfg.fmtag = 0x162;
			अवरोध;

		हाल SND_AUDIOPROखाता_WMA9_LOSSLESS:
			wma_cfg.fmtag = 0x163;
			अवरोध;

		हाल SND_AUDIOPROखाता_WMA10_LOSSLESS:
			wma_cfg.fmtag = 0x167;
			अवरोध;

		शेष:
			dev_err(dev, "Unknown WMA profile:%x\n",
				codec->profile);
			वापस -EIO;
		पूर्ण

		अगर (wma_v9)
			ret = q6यंत्र_stream_media_क्रमmat_block_wma_v9(
					prtd->audio_client, stream_id,
					&wma_cfg);
		अन्यथा
			ret = q6यंत्र_stream_media_क्रमmat_block_wma_v10(
					prtd->audio_client, stream_id,
					&wma_cfg);
		अगर (ret < 0) अणु
			dev_err(dev, "WMA9 CMD failed:%d\n", ret);
			वापस -EIO;
		पूर्ण
		अवरोध;

	हाल SND_AUDIOCODEC_ALAC:
		स_रखो(&alac_cfg, 0x0, माप(alac_cfg));
		alac = &codec_options->alac_d;

		alac_cfg.sample_rate = codec->sample_rate;
		alac_cfg.avg_bit_rate = codec->bit_rate;
		alac_cfg.bit_depth = prtd->bits_per_sample;
		alac_cfg.num_channels = codec->ch_in;

		alac_cfg.frame_length = alac->frame_length;
		alac_cfg.pb = alac->pb;
		alac_cfg.mb = alac->mb;
		alac_cfg.kb = alac->kb;
		alac_cfg.max_run = alac->max_run;
		alac_cfg.compatible_version = alac->compatible_version;
		alac_cfg.max_frame_bytes = alac->max_frame_bytes;

		चयन (codec->ch_in) अणु
		हाल 1:
			alac_cfg.channel_layout_tag = ALAC_CH_LAYOUT_MONO;
			अवरोध;
		हाल 2:
			alac_cfg.channel_layout_tag = ALAC_CH_LAYOUT_STEREO;
			अवरोध;
		पूर्ण
		ret = q6यंत्र_stream_media_क्रमmat_block_alac(prtd->audio_client,
							   stream_id,
							   &alac_cfg);
		अगर (ret < 0) अणु
			dev_err(dev, "ALAC CMD Format block failed:%d\n", ret);
			वापस -EIO;
		पूर्ण
		अवरोध;

	हाल SND_AUDIOCODEC_APE:
		स_रखो(&ape_cfg, 0x0, माप(ape_cfg));
		ape = &codec_options->ape_d;

		ape_cfg.sample_rate = codec->sample_rate;
		ape_cfg.num_channels = codec->ch_in;
		ape_cfg.bits_per_sample = prtd->bits_per_sample;

		ape_cfg.compatible_version = ape->compatible_version;
		ape_cfg.compression_level = ape->compression_level;
		ape_cfg.क्रमmat_flags = ape->क्रमmat_flags;
		ape_cfg.blocks_per_frame = ape->blocks_per_frame;
		ape_cfg.final_frame_blocks = ape->final_frame_blocks;
		ape_cfg.total_frames = ape->total_frames;
		ape_cfg.seek_table_present = ape->seek_table_present;

		ret = q6यंत्र_stream_media_क्रमmat_block_ape(prtd->audio_client,
							  stream_id,
							  &ape_cfg);
		अगर (ret < 0) अणु
			dev_err(dev, "APE CMD Format block failed:%d\n", ret);
			वापस -EIO;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक q6यंत्र_dai_compr_set_params(काष्ठा snd_soc_component *component,
				      काष्ठा snd_compr_stream *stream,
				      काष्ठा snd_compr_params *params)
अणु
	काष्ठा snd_compr_runसमय *runसमय = stream->runसमय;
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;
	काष्ठा snd_soc_pcm_runसमय *rtd = stream->निजी_data;
	पूर्णांक dir = stream->direction;
	काष्ठा q6यंत्र_dai_data *pdata;
	काष्ठा device *dev = component->dev;
	पूर्णांक ret;

	pdata = snd_soc_component_get_drvdata(component);
	अगर (!pdata)
		वापस -EINVAL;

	अगर (!prtd || !prtd->audio_client) अणु
		dev_err(dev, "private data null or audio client freed\n");
		वापस -EINVAL;
	पूर्ण

	prtd->periods = runसमय->fragments;
	prtd->pcm_count = runसमय->fragment_size;
	prtd->pcm_size = runसमय->fragments * runसमय->fragment_size;
	prtd->bits_per_sample = 16;

	अगर (dir == SND_COMPRESS_PLAYBACK) अणु
		ret = q6यंत्र_खोलो_ग_लिखो(prtd->audio_client, prtd->stream_id, params->codec.id,
				params->codec.profile, prtd->bits_per_sample,
				true);

		अगर (ret < 0) अणु
			dev_err(dev, "q6asm_open_write failed\n");
			q6यंत्र_audio_client_मुक्त(prtd->audio_client);
			prtd->audio_client = शून्य;
			वापस ret;
		पूर्ण
	पूर्ण

	prtd->session_id = q6यंत्र_get_session_id(prtd->audio_client);
	ret = q6routing_stream_खोलो(rtd->dai_link->id, LEGACY_PCM_MODE,
			      prtd->session_id, dir);
	अगर (ret) अणु
		dev_err(dev, "Stream reg failed ret:%d\n", ret);
		वापस ret;
	पूर्ण

	ret = __q6यंत्र_dai_compr_set_codec_params(component, stream,
						 &params->codec,
						 prtd->stream_id);
	अगर (ret) अणु
		dev_err(dev, "codec param setup failed ret:%d\n", ret);
		वापस ret;
	पूर्ण

	ret = q6यंत्र_map_memory_regions(dir, prtd->audio_client, prtd->phys,
				       (prtd->pcm_size / prtd->periods),
				       prtd->periods);

	अगर (ret < 0) अणु
		dev_err(dev, "Buffer Mapping failed ret:%d\n", ret);
		वापस -ENOMEM;
	पूर्ण

	prtd->state = Q6ASM_STREAM_RUNNING;

	वापस 0;
पूर्ण

अटल पूर्णांक q6यंत्र_dai_compr_set_metadata(काष्ठा snd_soc_component *component,
					काष्ठा snd_compr_stream *stream,
					काष्ठा snd_compr_metadata *metadata)
अणु
	काष्ठा snd_compr_runसमय *runसमय = stream->runसमय;
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;
	पूर्णांक ret = 0;

	चयन (metadata->key) अणु
	हाल SNDRV_COMPRESS_ENCODER_PADDING:
		prtd->trailing_samples_drop = metadata->value[0];
		अवरोध;
	हाल SNDRV_COMPRESS_ENCODER_DELAY:
		prtd->initial_samples_drop = metadata->value[0];
		अगर (prtd->next_track_stream_id) अणु
			ret = q6यंत्र_खोलो_ग_लिखो(prtd->audio_client,
					       prtd->next_track_stream_id,
					       prtd->codec.id,
					       prtd->codec.profile,
					       prtd->bits_per_sample,
				       true);
			अगर (ret < 0) अणु
				dev_err(component->dev, "q6asm_open_write failed\n");
				वापस ret;
			पूर्ण
			ret = __q6यंत्र_dai_compr_set_codec_params(component, stream,
								 &prtd->codec,
								 prtd->next_track_stream_id);
			अगर (ret < 0) अणु
				dev_err(component->dev, "q6asm_open_write failed\n");
				वापस ret;
			पूर्ण

			ret = q6यंत्र_stream_हटाओ_initial_silence(prtd->audio_client,
						    prtd->next_track_stream_id,
						    prtd->initial_samples_drop);
			prtd->next_track_stream_id = 0;

		पूर्ण

		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक q6यंत्र_dai_compr_trigger(काष्ठा snd_soc_component *component,
				   काष्ठा snd_compr_stream *stream, पूर्णांक cmd)
अणु
	काष्ठा snd_compr_runसमय *runसमय = stream->runसमय;
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = q6यंत्र_run_noरुको(prtd->audio_client, prtd->stream_id,
				       0, 0, 0);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		prtd->state = Q6ASM_STREAM_STOPPED;
		ret = q6यंत्र_cmd_noरुको(prtd->audio_client, prtd->stream_id,
				       CMD_EOS);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = q6यंत्र_cmd_noरुको(prtd->audio_client, prtd->stream_id,
				       CMD_PAUSE);
		अवरोध;
	हाल SND_COMPR_TRIGGER_NEXT_TRACK:
		prtd->next_track = true;
		prtd->next_track_stream_id = (prtd->stream_id == 1 ? 2 : 1);
		अवरोध;
	हाल SND_COMPR_TRIGGER_DRAIN:
	हाल SND_COMPR_TRIGGER_PARTIAL_DRAIN:
		prtd->notअगरy_on_drain = true;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक q6यंत्र_dai_compr_poपूर्णांकer(काष्ठा snd_soc_component *component,
				   काष्ठा snd_compr_stream *stream,
				   काष्ठा snd_compr_tstamp *tstamp)
अणु
	काष्ठा snd_compr_runसमय *runसमय = stream->runसमय;
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&prtd->lock, flags);

	tstamp->copied_total = prtd->copied_total;
	tstamp->byte_offset = prtd->copied_total % prtd->pcm_size;

	spin_unlock_irqrestore(&prtd->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक q6यंत्र_compr_copy(काष्ठा snd_soc_component *component,
			    काष्ठा snd_compr_stream *stream, अक्षर __user *buf,
			    माप_प्रकार count)
अणु
	काष्ठा snd_compr_runसमय *runसमय = stream->runसमय;
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;
	अचिन्हित दीर्घ flags;
	u32 wflags = 0;
	पूर्णांक avail, bytes_in_flight = 0;
	व्योम *dstn;
	माप_प्रकार copy;
	u32 app_poपूर्णांकer;
	u32 bytes_received;

	bytes_received = prtd->bytes_received;

	/**
	 * Make sure that next track data poपूर्णांकer is aligned at 32 bit boundary
	 * This is a Mandatory requirement from DSP data buffers alignment
	 */
	अगर (prtd->next_track)
		bytes_received = ALIGN(prtd->bytes_received, prtd->pcm_count);

	app_poपूर्णांकer = bytes_received/prtd->pcm_size;
	app_poपूर्णांकer = bytes_received -  (app_poपूर्णांकer * prtd->pcm_size);
	dstn = prtd->dma_buffer.area + app_poपूर्णांकer;

	अगर (count < prtd->pcm_size - app_poपूर्णांकer) अणु
		अगर (copy_from_user(dstn, buf, count))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		copy = prtd->pcm_size - app_poपूर्णांकer;
		अगर (copy_from_user(dstn, buf, copy))
			वापस -EFAULT;
		अगर (copy_from_user(prtd->dma_buffer.area, buf + copy,
				   count - copy))
			वापस -EFAULT;
	पूर्ण

	spin_lock_irqsave(&prtd->lock, flags);

	bytes_in_flight = prtd->bytes_received - prtd->copied_total;

	अगर (prtd->next_track) अणु
		prtd->next_track = false;
		prtd->copied_total = ALIGN(prtd->copied_total, prtd->pcm_count);
		prtd->bytes_sent = ALIGN(prtd->bytes_sent, prtd->pcm_count);
	पूर्ण

	prtd->bytes_received = bytes_received + count;

	/* Kick off the data to dsp अगर its starving!! */
	अगर (prtd->state == Q6ASM_STREAM_RUNNING && (bytes_in_flight == 0)) अणु
		uपूर्णांक32_t bytes_to_ग_लिखो = prtd->pcm_count;

		avail = prtd->bytes_received - prtd->bytes_sent;

		अगर (avail < prtd->pcm_count)
			bytes_to_ग_लिखो = avail;

		q6यंत्र_ग_लिखो_async(prtd->audio_client, prtd->stream_id,
				  bytes_to_ग_लिखो, 0, 0, wflags);
		prtd->bytes_sent += bytes_to_ग_लिखो;
	पूर्ण

	spin_unlock_irqrestore(&prtd->lock, flags);

	वापस count;
पूर्ण

अटल पूर्णांक q6यंत्र_dai_compr_mmap(काष्ठा snd_soc_component *component,
				काष्ठा snd_compr_stream *stream,
				काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा snd_compr_runसमय *runसमय = stream->runसमय;
	काष्ठा q6यंत्र_dai_rtd *prtd = runसमय->निजी_data;
	काष्ठा device *dev = component->dev;

	वापस dma_mmap_coherent(dev, vma,
			prtd->dma_buffer.area, prtd->dma_buffer.addr,
			prtd->dma_buffer.bytes);
पूर्ण

अटल पूर्णांक q6यंत्र_dai_compr_get_caps(काष्ठा snd_soc_component *component,
				    काष्ठा snd_compr_stream *stream,
				    काष्ठा snd_compr_caps *caps)
अणु
	caps->direction = SND_COMPRESS_PLAYBACK;
	caps->min_fragment_size = COMPR_PLAYBACK_MIN_FRAGMENT_SIZE;
	caps->max_fragment_size = COMPR_PLAYBACK_MAX_FRAGMENT_SIZE;
	caps->min_fragments = COMPR_PLAYBACK_MIN_NUM_FRAGMENTS;
	caps->max_fragments = COMPR_PLAYBACK_MAX_NUM_FRAGMENTS;
	caps->num_codecs = 5;
	caps->codecs[0] = SND_AUDIOCODEC_MP3;
	caps->codecs[1] = SND_AUDIOCODEC_FLAC;
	caps->codecs[2] = SND_AUDIOCODEC_WMA;
	caps->codecs[3] = SND_AUDIOCODEC_ALAC;
	caps->codecs[4] = SND_AUDIOCODEC_APE;

	वापस 0;
पूर्ण

अटल पूर्णांक q6यंत्र_dai_compr_get_codec_caps(काष्ठा snd_soc_component *component,
					  काष्ठा snd_compr_stream *stream,
					  काष्ठा snd_compr_codec_caps *codec)
अणु
	चयन (codec->codec) अणु
	हाल SND_AUDIOCODEC_MP3:
		*codec = q6यंत्र_compr_caps;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_compress_ops q6यंत्र_dai_compress_ops = अणु
	.खोलो		= q6यंत्र_dai_compr_खोलो,
	.मुक्त		= q6यंत्र_dai_compr_मुक्त,
	.set_params	= q6यंत्र_dai_compr_set_params,
	.set_metadata	= q6यंत्र_dai_compr_set_metadata,
	.poपूर्णांकer	= q6यंत्र_dai_compr_poपूर्णांकer,
	.trigger	= q6यंत्र_dai_compr_trigger,
	.get_caps	= q6यंत्र_dai_compr_get_caps,
	.get_codec_caps	= q6यंत्र_dai_compr_get_codec_caps,
	.mmap		= q6यंत्र_dai_compr_mmap,
	.copy		= q6यंत्र_compr_copy,
पूर्ण;

अटल पूर्णांक q6यंत्र_dai_pcm_new(काष्ठा snd_soc_component *component,
			     काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_pcm_substream *psubstream, *csubstream;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	काष्ठा device *dev;
	पूर्णांक size, ret;

	dev = component->dev;
	size = q6यंत्र_dai_hardware_playback.buffer_bytes_max;
	psubstream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
	अगर (psubstream) अणु
		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, dev, size,
					  &psubstream->dma_buffer);
		अगर (ret) अणु
			dev_err(dev, "Cannot allocate buffer(s)\n");
			वापस ret;
		पूर्ण
	पूर्ण

	csubstream = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	अगर (csubstream) अणु
		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, dev, size,
					  &csubstream->dma_buffer);
		अगर (ret) अणु
			dev_err(dev, "Cannot allocate buffer(s)\n");
			अगर (psubstream)
				snd_dma_मुक्त_pages(&psubstream->dma_buffer);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम q6यंत्र_dai_pcm_मुक्त(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcm->streams); i++) अणु
		substream = pcm->streams[i].substream;
		अगर (substream) अणु
			snd_dma_मुक्त_pages(&substream->dma_buffer);
			substream->dma_buffer.area = शून्य;
			substream->dma_buffer.addr = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget q6यंत्र_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("MM_DL1", "MultiMedia1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DL2", "MultiMedia2 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DL3", "MultiMedia3 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DL4", "MultiMedia4 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DL5", "MultiMedia5 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DL6", "MultiMedia6 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DL7", "MultiMedia7 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DL8", "MultiMedia8 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UL1", "MultiMedia1 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UL2", "MultiMedia2 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UL3", "MultiMedia3 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UL4", "MultiMedia4 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UL5", "MultiMedia5 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UL6", "MultiMedia6 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UL7", "MultiMedia7 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UL8", "MultiMedia8 Capture", 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver q6यंत्र_fe_dai_component = अणु
	.name		= DRV_NAME,
	.खोलो		= q6यंत्र_dai_खोलो,
	.hw_params	= q6यंत्र_dai_hw_params,
	.बंद		= q6यंत्र_dai_बंद,
	.prepare	= q6यंत्र_dai_prepare,
	.trigger	= q6यंत्र_dai_trigger,
	.poपूर्णांकer	= q6यंत्र_dai_poपूर्णांकer,
	.mmap		= q6यंत्र_dai_mmap,
	.pcm_स्थिरruct	= q6यंत्र_dai_pcm_new,
	.pcm_deकाष्ठा	= q6यंत्र_dai_pcm_मुक्त,
	.compress_ops	= &q6यंत्र_dai_compress_ops,
	.dapm_widमाला_लो	= q6यंत्र_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(q6यंत्र_dapm_widमाला_लो),
पूर्ण;

अटल काष्ठा snd_soc_dai_driver q6यंत्र_fe_dais_ढाँचा[] = अणु
	Q6ASM_FEDAI_DRIVER(1),
	Q6ASM_FEDAI_DRIVER(2),
	Q6ASM_FEDAI_DRIVER(3),
	Q6ASM_FEDAI_DRIVER(4),
	Q6ASM_FEDAI_DRIVER(5),
	Q6ASM_FEDAI_DRIVER(6),
	Q6ASM_FEDAI_DRIVER(7),
	Q6ASM_FEDAI_DRIVER(8),
पूर्ण;

अटल पूर्णांक of_q6यंत्र_parse_dai_data(काष्ठा device *dev,
				    काष्ठा q6यंत्र_dai_data *pdata)
अणु
	काष्ठा snd_soc_dai_driver *dai_drv;
	काष्ठा snd_soc_pcm_stream empty_stream;
	काष्ठा device_node *node;
	पूर्णांक ret, id, dir, idx = 0;


	pdata->num_dais = of_get_child_count(dev->of_node);
	अगर (!pdata->num_dais) अणु
		dev_err(dev, "No dais found in DT\n");
		वापस -EINVAL;
	पूर्ण

	pdata->dais = devm_kसुस्मृति(dev, pdata->num_dais, माप(*dai_drv),
				   GFP_KERNEL);
	अगर (!pdata->dais)
		वापस -ENOMEM;

	स_रखो(&empty_stream, 0, माप(empty_stream));

	क्रम_each_child_of_node(dev->of_node, node) अणु
		ret = of_property_पढ़ो_u32(node, "reg", &id);
		अगर (ret || id >= MAX_SESSIONS || id < 0) अणु
			dev_err(dev, "valid dai id not found:%d\n", ret);
			जारी;
		पूर्ण

		dai_drv = &pdata->dais[idx++];
		*dai_drv = q6यंत्र_fe_dais_ढाँचा[id];

		ret = of_property_पढ़ो_u32(node, "direction", &dir);
		अगर (ret)
			जारी;

		अगर (dir == Q6ASM_DAI_RX)
			dai_drv->capture = empty_stream;
		अन्यथा अगर (dir == Q6ASM_DAI_TX)
			dai_drv->playback = empty_stream;

		अगर (of_property_पढ़ो_bool(node, "is-compress-dai"))
			dai_drv->compress_new = snd_soc_new_compress;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक q6यंत्र_dai_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा of_phandle_args args;
	काष्ठा q6यंत्र_dai_data *pdata;
	पूर्णांक rc;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	rc = of_parse_phandle_with_fixed_args(node, "iommus", 1, 0, &args);
	अगर (rc < 0)
		pdata->sid = -1;
	अन्यथा
		pdata->sid = args.args[0] & SID_MASK_DEFAULT;

	dev_set_drvdata(dev, pdata);

	rc = of_q6यंत्र_parse_dai_data(dev, pdata);
	अगर (rc)
		वापस rc;

	वापस devm_snd_soc_रेजिस्टर_component(dev, &q6यंत्र_fe_dai_component,
					       pdata->dais, pdata->num_dais);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id q6यंत्र_dai_device_id[] = अणु
	अणु .compatible = "qcom,q6asm-dais" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, q6यंत्र_dai_device_id);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver q6यंत्र_dai_platक्रमm_driver = अणु
	.driver = अणु
		.name = "q6asm-dai",
		.of_match_table = of_match_ptr(q6यंत्र_dai_device_id),
	पूर्ण,
	.probe = q6यंत्र_dai_probe,
पूर्ण;
module_platक्रमm_driver(q6यंत्र_dai_platक्रमm_driver);

MODULE_DESCRIPTION("Q6ASM dai driver");
MODULE_LICENSE("GPL v2");
