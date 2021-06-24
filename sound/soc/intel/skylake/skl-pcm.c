<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  skl-pcm.c -ASoC HDA Platक्रमm driver file implementing PCM functionality
 *
 *  Copyright (C) 2014-2015 Intel Corp
 *  Author:  Jeeja KP <jeeja.kp@पूर्णांकel.com>
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/delay.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "skl.h"
#समावेश "skl-topology.h"
#समावेश "skl-sst-dsp.h"
#समावेश "skl-sst-ipc.h"

#घोषणा HDA_MONO 1
#घोषणा HDA_STEREO 2
#घोषणा HDA_QUAD 4
#घोषणा HDA_MAX 8

अटल स्थिर काष्ठा snd_pcm_hardware azx_pcm_hw = अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_SYNC_START |
				 SNDRV_PCM_INFO_HAS_WALL_CLOCK | /* legacy */
				 SNDRV_PCM_INFO_HAS_LINK_ATIME |
				 SNDRV_PCM_INFO_NO_PERIOD_WAKEUP),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_S32_LE |
				SNDRV_PCM_FMTBIT_S24_LE,
	.rates =		SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_16000 |
				SNDRV_PCM_RATE_8000,
	.rate_min =		8000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		8,
	.buffer_bytes_max =	AZX_MAX_BUF_SIZE,
	.period_bytes_min =	128,
	.period_bytes_max =	AZX_MAX_BUF_SIZE / 2,
	.periods_min =		2,
	.periods_max =		AZX_MAX_FRAG,
	.fअगरo_size =		0,
पूर्ण;

अटल अंतरभूत
काष्ठा hdac_ext_stream *get_hdac_ext_stream(काष्ठा snd_pcm_substream *substream)
अणु
	वापस substream->runसमय->निजी_data;
पूर्ण

अटल काष्ठा hdac_bus *get_bus_ctx(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdac_ext_stream *stream = get_hdac_ext_stream(substream);
	काष्ठा hdac_stream *hstream = hdac_stream(stream);
	काष्ठा hdac_bus *bus = hstream->bus;
	वापस bus;
पूर्ण

अटल पूर्णांक skl_substream_alloc_pages(काष्ठा hdac_bus *bus,
				 काष्ठा snd_pcm_substream *substream,
				 माप_प्रकार size)
अणु
	काष्ठा hdac_ext_stream *stream = get_hdac_ext_stream(substream);

	hdac_stream(stream)->bufsize = 0;
	hdac_stream(stream)->period_bytes = 0;
	hdac_stream(stream)->क्रमmat_val = 0;

	वापस 0;
पूर्ण

अटल व्योम skl_set_pcm_स्थिरrains(काष्ठा hdac_bus *bus,
				 काष्ठा snd_pcm_runसमय *runसमय)
अणु
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);

	/* aव्योम wrap-around with wall-घड़ी */
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_TIME,
				     20, 178000000);
पूर्ण

अटल क्रमागत hdac_ext_stream_type skl_get_host_stream_type(काष्ठा hdac_bus *bus)
अणु
	अगर (bus->ppcap)
		वापस HDAC_EXT_STREAM_TYPE_HOST;
	अन्यथा
		वापस HDAC_EXT_STREAM_TYPE_COUPLED;
पूर्ण

/*
 * check अगर the stream खोलोed is marked as ignore_suspend by machine, अगर so
 * then enable suspend_active refcount
 *
 * The count supend_active करोes not need lock as it is used in खोलो/बंद
 * and suspend context
 */
अटल व्योम skl_set_suspend_active(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_soc_dai *dai, bool enable)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dai->dev);
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा skl_dev *skl = bus_to_skl(bus);

	w = snd_soc_dai_get_widget(dai, substream->stream);

	अगर (w->ignore_suspend && enable)
		skl->supend_active++;
	अन्यथा अगर (w->ignore_suspend && !enable)
		skl->supend_active--;
पूर्ण

पूर्णांक skl_pcm_host_dma_prepare(काष्ठा device *dev, काष्ठा skl_pipe_params *params)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dev);
	काष्ठा skl_dev *skl = bus_to_skl(bus);
	अचिन्हित पूर्णांक क्रमmat_val;
	काष्ठा hdac_stream *hstream;
	काष्ठा hdac_ext_stream *stream;
	पूर्णांक err;

	hstream = snd_hdac_get_stream(bus, params->stream,
					params->host_dma_id + 1);
	अगर (!hstream)
		वापस -EINVAL;

	stream = stream_to_hdac_ext_stream(hstream);
	snd_hdac_ext_stream_decouple(bus, stream, true);

	क्रमmat_val = snd_hdac_calc_stream_क्रमmat(params->s_freq,
			params->ch, params->क्रमmat, params->host_bps, 0);

	dev_dbg(dev, "format_val=%d, rate=%d, ch=%d, format=%d\n",
		क्रमmat_val, params->s_freq, params->ch, params->क्रमmat);

	snd_hdac_stream_reset(hdac_stream(stream));
	err = snd_hdac_stream_set_params(hdac_stream(stream), क्रमmat_val);
	अगर (err < 0)
		वापस err;

	/*
	 * The recommended SDxFMT programming sequence क्रम BXT
	 * platक्रमms is to couple the stream beक्रमe writing the क्रमmat
	 */
	अगर (IS_BXT(skl->pci)) अणु
		snd_hdac_ext_stream_decouple(bus, stream, false);
		err = snd_hdac_stream_setup(hdac_stream(stream));
		snd_hdac_ext_stream_decouple(bus, stream, true);
	पूर्ण अन्यथा अणु
		err = snd_hdac_stream_setup(hdac_stream(stream));
	पूर्ण

	अगर (err < 0)
		वापस err;

	hdac_stream(stream)->prepared = 1;

	वापस 0;
पूर्ण

पूर्णांक skl_pcm_link_dma_prepare(काष्ठा device *dev, काष्ठा skl_pipe_params *params)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक क्रमmat_val;
	काष्ठा hdac_stream *hstream;
	काष्ठा hdac_ext_stream *stream;
	काष्ठा hdac_ext_link *link;
	अचिन्हित अक्षर stream_tag;

	hstream = snd_hdac_get_stream(bus, params->stream,
					params->link_dma_id + 1);
	अगर (!hstream)
		वापस -EINVAL;

	stream = stream_to_hdac_ext_stream(hstream);
	snd_hdac_ext_stream_decouple(bus, stream, true);
	क्रमmat_val = snd_hdac_calc_stream_क्रमmat(params->s_freq, params->ch,
					params->क्रमmat, params->link_bps, 0);

	dev_dbg(dev, "format_val=%d, rate=%d, ch=%d, format=%d\n",
		क्रमmat_val, params->s_freq, params->ch, params->क्रमmat);

	snd_hdac_ext_link_stream_reset(stream);

	snd_hdac_ext_link_stream_setup(stream, क्रमmat_val);

	stream_tag = hstream->stream_tag;
	अगर (stream->hstream.direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
		list_क्रम_each_entry(link, &bus->hlink_list, list) अणु
			अगर (link->index == params->link_index)
				snd_hdac_ext_link_set_stream_id(link,
								stream_tag);
		पूर्ण
	पूर्ण

	stream->link_prepared = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक skl_pcm_खोलो(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dai->dev);
	काष्ठा hdac_ext_stream *stream;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा skl_dma_params *dma_params;
	काष्ठा skl_dev *skl = get_skl_ctx(dai->dev);
	काष्ठा skl_module_cfg *mconfig;

	dev_dbg(dai->dev, "%s: %s\n", __func__, dai->name);

	stream = snd_hdac_ext_stream_assign(bus, substream,
					skl_get_host_stream_type(bus));
	अगर (stream == शून्य)
		वापस -EBUSY;

	skl_set_pcm_स्थिरrains(bus, runसमय);

	/*
	 * disable WALLCLOCK बारtamps क्रम capture streams
	 * until we figure out how to handle digital inमाला_दो
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		runसमय->hw.info &= ~SNDRV_PCM_INFO_HAS_WALL_CLOCK; /* legacy */
		runसमय->hw.info &= ~SNDRV_PCM_INFO_HAS_LINK_ATIME;
	पूर्ण

	runसमय->निजी_data = stream;

	dma_params = kzalloc(माप(*dma_params), GFP_KERNEL);
	अगर (!dma_params)
		वापस -ENOMEM;

	dma_params->stream_tag = hdac_stream(stream)->stream_tag;
	snd_soc_dai_set_dma_data(dai, substream, dma_params);

	dev_dbg(dai->dev, "stream tag set in dma params=%d\n",
				 dma_params->stream_tag);
	skl_set_suspend_active(substream, dai, true);
	snd_pcm_set_sync(substream);

	mconfig = skl_tplg_fe_get_cpr_module(dai, substream->stream);
	अगर (!mconfig)
		वापस -EINVAL;

	skl_tplg_d0i3_get(skl, mconfig->d0i3_caps);

	वापस 0;
पूर्ण

अटल पूर्णांक skl_pcm_prepare(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा skl_dev *skl = get_skl_ctx(dai->dev);
	काष्ठा skl_module_cfg *mconfig;
	पूर्णांक ret;

	dev_dbg(dai->dev, "%s: %s\n", __func__, dai->name);

	mconfig = skl_tplg_fe_get_cpr_module(dai, substream->stream);

	/*
	 * In हाल of XRUN recovery or in the हाल when the application
	 * calls prepare another समय, reset the FW pipe to clean state
	 */
	अगर (mconfig &&
		(substream->runसमय->status->state == SNDRV_PCM_STATE_XRUN ||
		 mconfig->pipe->state == SKL_PIPE_CREATED ||
		 mconfig->pipe->state == SKL_PIPE_PAUSED)) अणु

		ret = skl_reset_pipe(skl, mconfig->pipe);

		अगर (ret < 0)
			वापस ret;

		ret = skl_pcm_host_dma_prepare(dai->dev,
					mconfig->pipe->p_params);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dai->dev);
	काष्ठा hdac_ext_stream *stream = get_hdac_ext_stream(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा skl_pipe_params p_params = अणु0पूर्ण;
	काष्ठा skl_module_cfg *m_cfg;
	पूर्णांक ret, dma_id;

	dev_dbg(dai->dev, "%s: %s\n", __func__, dai->name);
	ret = skl_substream_alloc_pages(bus, substream,
					  params_buffer_bytes(params));
	अगर (ret < 0)
		वापस ret;

	dev_dbg(dai->dev, "format_val, rate=%d, ch=%d, format=%d\n",
			runसमय->rate, runसमय->channels, runसमय->क्रमmat);

	dma_id = hdac_stream(stream)->stream_tag - 1;
	dev_dbg(dai->dev, "dma_id=%d\n", dma_id);

	p_params.s_fmt = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	p_params.ch = params_channels(params);
	p_params.s_freq = params_rate(params);
	p_params.host_dma_id = dma_id;
	p_params.stream = substream->stream;
	p_params.क्रमmat = params_क्रमmat(params);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		p_params.host_bps = dai->driver->playback.sig_bits;
	अन्यथा
		p_params.host_bps = dai->driver->capture.sig_bits;


	m_cfg = skl_tplg_fe_get_cpr_module(dai, p_params.stream);
	अगर (m_cfg)
		skl_tplg_update_pipe_params(dai->dev, m_cfg, &p_params);

	वापस 0;
पूर्ण

अटल व्योम skl_pcm_बंद(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_ext_stream *stream = get_hdac_ext_stream(substream);
	काष्ठा hdac_bus *bus = dev_get_drvdata(dai->dev);
	काष्ठा skl_dma_params *dma_params = शून्य;
	काष्ठा skl_dev *skl = bus_to_skl(bus);
	काष्ठा skl_module_cfg *mconfig;

	dev_dbg(dai->dev, "%s: %s\n", __func__, dai->name);

	snd_hdac_ext_stream_release(stream, skl_get_host_stream_type(bus));

	dma_params = snd_soc_dai_get_dma_data(dai, substream);
	/*
	 * now we should set this to शून्य as we are मुक्तing by the
	 * dma_params
	 */
	snd_soc_dai_set_dma_data(dai, substream, शून्य);
	skl_set_suspend_active(substream, dai, false);

	/*
	 * check अगर बंद is क्रम "Reference Pin" and set back the
	 * CGCTL.MISCBDCGE अगर disabled by driver
	 */
	अगर (!म_भेदन(dai->name, "Reference Pin", 13) &&
			skl->miscbdcg_disabled) अणु
		skl->enable_miscbdcge(dai->dev, true);
		skl->miscbdcg_disabled = false;
	पूर्ण

	mconfig = skl_tplg_fe_get_cpr_module(dai, substream->stream);
	अगर (mconfig)
		skl_tplg_d0i3_put(skl, mconfig->d0i3_caps);

	kमुक्त(dma_params);
पूर्ण

अटल पूर्णांक skl_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_ext_stream *stream = get_hdac_ext_stream(substream);
	काष्ठा skl_dev *skl = get_skl_ctx(dai->dev);
	काष्ठा skl_module_cfg *mconfig;
	पूर्णांक ret;

	dev_dbg(dai->dev, "%s: %s\n", __func__, dai->name);

	mconfig = skl_tplg_fe_get_cpr_module(dai, substream->stream);

	अगर (mconfig) अणु
		ret = skl_reset_pipe(skl, mconfig->pipe);
		अगर (ret < 0)
			dev_err(dai->dev, "%s:Reset failed ret =%d",
						__func__, ret);
	पूर्ण

	snd_hdac_stream_cleanup(hdac_stream(stream));
	hdac_stream(stream)->prepared = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक skl_be_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा skl_pipe_params p_params = अणु0पूर्ण;

	p_params.s_fmt = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	p_params.ch = params_channels(params);
	p_params.s_freq = params_rate(params);
	p_params.stream = substream->stream;

	वापस skl_tplg_be_update_params(dai, &p_params);
पूर्ण

अटल पूर्णांक skl_decoupled_trigger(काष्ठा snd_pcm_substream *substream,
		पूर्णांक cmd)
अणु
	काष्ठा hdac_bus *bus = get_bus_ctx(substream);
	काष्ठा hdac_ext_stream *stream;
	पूर्णांक start;
	अचिन्हित दीर्घ cookie;
	काष्ठा hdac_stream *hstr;

	stream = get_hdac_ext_stream(substream);
	hstr = hdac_stream(stream);

	अगर (!hstr->prepared)
		वापस -EPIPE;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		start = 1;
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		start = 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&bus->reg_lock, cookie);

	अगर (start) अणु
		snd_hdac_stream_start(hdac_stream(stream), true);
		snd_hdac_stream_समयcounter_init(hstr, 0);
	पूर्ण अन्यथा अणु
		snd_hdac_stream_stop(hdac_stream(stream));
	पूर्ण

	spin_unlock_irqrestore(&bus->reg_lock, cookie);

	वापस 0;
पूर्ण

अटल पूर्णांक skl_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा skl_dev *skl = get_skl_ctx(dai->dev);
	काष्ठा skl_module_cfg *mconfig;
	काष्ठा hdac_bus *bus = get_bus_ctx(substream);
	काष्ठा hdac_ext_stream *stream = get_hdac_ext_stream(substream);
	काष्ठा snd_soc_dapm_widget *w;
	पूर्णांक ret;

	mconfig = skl_tplg_fe_get_cpr_module(dai, substream->stream);
	अगर (!mconfig)
		वापस -EIO;

	w = snd_soc_dai_get_widget(dai, substream->stream);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (!w->ignore_suspend) अणु
			/*
			 * enable DMA Resume enable bit क्रम the stream, set the
			 * dpib & lpib position to resume beक्रमe starting the
			 * DMA
			 */
			snd_hdac_ext_stream_drsm_enable(bus, true,
						hdac_stream(stream)->index);
			snd_hdac_ext_stream_set_dpibr(bus, stream,
							stream->lpib);
			snd_hdac_ext_stream_set_lpib(stream, stream->lpib);
		पूर्ण
		fallthrough;

	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		/*
		 * Start HOST DMA and Start FE Pipe.This is to make sure that
		 * there are no underrun/overrun in the हाल when the FE
		 * pipeline is started but there is a delay in starting the
		 * DMA channel on the host.
		 */
		ret = skl_decoupled_trigger(substream, cmd);
		अगर (ret < 0)
			वापस ret;
		वापस skl_run_pipe(skl, mconfig->pipe);

	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		/*
		 * Stop FE Pipe first and stop DMA. This is to make sure that
		 * there are no underrun/overrun in the हाल अगर there is a delay
		 * between the two operations.
		 */
		ret = skl_stop_pipe(skl, mconfig->pipe);
		अगर (ret < 0)
			वापस ret;

		ret = skl_decoupled_trigger(substream, cmd);
		अगर ((cmd == SNDRV_PCM_TRIGGER_SUSPEND) && !w->ignore_suspend) अणु
			/* save the dpib and lpib positions */
			stream->dpib = पढ़ोl(bus->remap_addr +
					AZX_REG_VS_SDXDPIB_XBASE +
					(AZX_REG_VS_SDXDPIB_XINTERVAL *
					hdac_stream(stream)->index));

			stream->lpib = snd_hdac_stream_get_pos_lpib(
							hdac_stream(stream));
			snd_hdac_ext_stream_decouple(bus, stream, false);
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक skl_link_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dai->dev);
	काष्ठा hdac_ext_stream *link_dev;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा skl_pipe_params p_params = अणु0पूर्ण;
	काष्ठा hdac_ext_link *link;
	पूर्णांक stream_tag;

	link_dev = snd_hdac_ext_stream_assign(bus, substream,
					HDAC_EXT_STREAM_TYPE_LINK);
	अगर (!link_dev)
		वापस -EBUSY;

	snd_soc_dai_set_dma_data(dai, substream, (व्योम *)link_dev);

	link = snd_hdac_ext_bus_get_link(bus, codec_dai->component->name);
	अगर (!link)
		वापस -EINVAL;

	stream_tag = hdac_stream(link_dev)->stream_tag;

	/* set the stream tag in the codec dai dma params  */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		snd_soc_dai_set_tdm_slot(codec_dai, stream_tag, 0, 0, 0);
	अन्यथा
		snd_soc_dai_set_tdm_slot(codec_dai, 0, stream_tag, 0, 0);

	p_params.s_fmt = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	p_params.ch = params_channels(params);
	p_params.s_freq = params_rate(params);
	p_params.stream = substream->stream;
	p_params.link_dma_id = stream_tag - 1;
	p_params.link_index = link->index;
	p_params.क्रमmat = params_क्रमmat(params);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		p_params.link_bps = codec_dai->driver->playback.sig_bits;
	अन्यथा
		p_params.link_bps = codec_dai->driver->capture.sig_bits;

	वापस skl_tplg_be_update_params(dai, &p_params);
पूर्ण

अटल पूर्णांक skl_link_pcm_prepare(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा skl_dev *skl = get_skl_ctx(dai->dev);
	काष्ठा skl_module_cfg *mconfig = शून्य;

	/* In हाल of XRUN recovery, reset the FW pipe to clean state */
	mconfig = skl_tplg_be_get_cpr_module(dai, substream->stream);
	अगर (mconfig && !mconfig->pipe->passthru &&
		(substream->runसमय->status->state == SNDRV_PCM_STATE_XRUN))
		skl_reset_pipe(skl, mconfig->pipe);

	वापस 0;
पूर्ण

अटल पूर्णांक skl_link_pcm_trigger(काष्ठा snd_pcm_substream *substream,
	पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_ext_stream *link_dev =
				snd_soc_dai_get_dma_data(dai, substream);
	काष्ठा hdac_bus *bus = get_bus_ctx(substream);
	काष्ठा hdac_ext_stream *stream = get_hdac_ext_stream(substream);

	dev_dbg(dai->dev, "In %s cmd=%d\n", __func__, cmd);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		snd_hdac_ext_link_stream_start(link_dev);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		snd_hdac_ext_link_stream_clear(link_dev);
		अगर (cmd == SNDRV_PCM_TRIGGER_SUSPEND)
			snd_hdac_ext_stream_decouple(bus, stream, false);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक skl_link_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dai->dev);
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा hdac_ext_stream *link_dev =
				snd_soc_dai_get_dma_data(dai, substream);
	काष्ठा hdac_ext_link *link;
	अचिन्हित अक्षर stream_tag;

	dev_dbg(dai->dev, "%s: %s\n", __func__, dai->name);

	link_dev->link_prepared = 0;

	link = snd_hdac_ext_bus_get_link(bus, asoc_rtd_to_codec(rtd, 0)->component->name);
	अगर (!link)
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		stream_tag = hdac_stream(link_dev)->stream_tag;
		snd_hdac_ext_link_clear_stream_id(link, stream_tag);
	पूर्ण

	snd_hdac_ext_stream_release(link_dev, HDAC_EXT_STREAM_TYPE_LINK);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops skl_pcm_dai_ops = अणु
	.startup = skl_pcm_खोलो,
	.shutकरोwn = skl_pcm_बंद,
	.prepare = skl_pcm_prepare,
	.hw_params = skl_pcm_hw_params,
	.hw_मुक्त = skl_pcm_hw_मुक्त,
	.trigger = skl_pcm_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops skl_dmic_dai_ops = अणु
	.hw_params = skl_be_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops skl_be_ssp_dai_ops = अणु
	.hw_params = skl_be_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops skl_link_dai_ops = अणु
	.prepare = skl_link_pcm_prepare,
	.hw_params = skl_link_hw_params,
	.hw_मुक्त = skl_link_hw_मुक्त,
	.trigger = skl_link_pcm_trigger,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver skl_fe_dai[] = अणु
अणु
	.name = "System Pin",
	.ops = &skl_pcm_dai_ops,
	.playback = अणु
		.stream_name = "System Playback",
		.channels_min = HDA_MONO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_8000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE,
		.sig_bits = 32,
	पूर्ण,
	.capture = अणु
		.stream_name = "System Capture",
		.channels_min = HDA_MONO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_16000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
		.sig_bits = 32,
	पूर्ण,
पूर्ण,
अणु
	.name = "System Pin2",
	.ops = &skl_pcm_dai_ops,
	.playback = अणु
		.stream_name = "Headset Playback",
		.channels_min = HDA_MONO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_16000 |
			SNDRV_PCM_RATE_8000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "Echoref Pin",
	.ops = &skl_pcm_dai_ops,
	.capture = अणु
		.stream_name = "Echoreference Capture",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_16000 |
			SNDRV_PCM_RATE_8000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "Reference Pin",
	.ops = &skl_pcm_dai_ops,
	.capture = अणु
		.stream_name = "Reference Capture",
		.channels_min = HDA_MONO,
		.channels_max = HDA_QUAD,
		.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_16000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
		.sig_bits = 32,
	पूर्ण,
पूर्ण,
अणु
	.name = "Deepbuffer Pin",
	.ops = &skl_pcm_dai_ops,
	.playback = अणु
		.stream_name = "Deepbuffer Playback",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
		.sig_bits = 32,
	पूर्ण,
पूर्ण,
अणु
	.name = "LowLatency Pin",
	.ops = &skl_pcm_dai_ops,
	.playback = अणु
		.stream_name = "Low Latency Playback",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
		.sig_bits = 32,
	पूर्ण,
पूर्ण,
अणु
	.name = "DMIC Pin",
	.ops = &skl_pcm_dai_ops,
	.capture = अणु
		.stream_name = "DMIC Capture",
		.channels_min = HDA_MONO,
		.channels_max = HDA_QUAD,
		.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_16000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
		.sig_bits = 32,
	पूर्ण,
पूर्ण,
अणु
	.name = "HDMI1 Pin",
	.ops = &skl_pcm_dai_ops,
	.playback = अणु
		.stream_name = "HDMI1 Playback",
		.channels_min = HDA_STEREO,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_32000 |	SNDRV_PCM_RATE_44100 |
			SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |
			SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |
			SNDRV_PCM_RATE_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S32_LE,
		.sig_bits = 32,
	पूर्ण,
पूर्ण,
अणु
	.name = "HDMI2 Pin",
	.ops = &skl_pcm_dai_ops,
	.playback = अणु
		.stream_name = "HDMI2 Playback",
		.channels_min = HDA_STEREO,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_32000 |	SNDRV_PCM_RATE_44100 |
			SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |
			SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |
			SNDRV_PCM_RATE_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S32_LE,
		.sig_bits = 32,
	पूर्ण,
पूर्ण,
अणु
	.name = "HDMI3 Pin",
	.ops = &skl_pcm_dai_ops,
	.playback = अणु
		.stream_name = "HDMI3 Playback",
		.channels_min = HDA_STEREO,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_32000 |	SNDRV_PCM_RATE_44100 |
			SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |
			SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |
			SNDRV_PCM_RATE_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S32_LE,
		.sig_bits = 32,
	पूर्ण,
पूर्ण,
पूर्ण;

/* BE CPU  Dais */
अटल काष्ठा snd_soc_dai_driver skl_platक्रमm_dai[] = अणु
अणु
	.name = "SSP0 Pin",
	.ops = &skl_be_ssp_dai_ops,
	.playback = अणु
		.stream_name = "ssp0 Tx",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "ssp0 Rx",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "SSP1 Pin",
	.ops = &skl_be_ssp_dai_ops,
	.playback = अणु
		.stream_name = "ssp1 Tx",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "ssp1 Rx",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "SSP2 Pin",
	.ops = &skl_be_ssp_dai_ops,
	.playback = अणु
		.stream_name = "ssp2 Tx",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "ssp2 Rx",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "SSP3 Pin",
	.ops = &skl_be_ssp_dai_ops,
	.playback = अणु
		.stream_name = "ssp3 Tx",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "ssp3 Rx",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "SSP4 Pin",
	.ops = &skl_be_ssp_dai_ops,
	.playback = अणु
		.stream_name = "ssp4 Tx",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "ssp4 Rx",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "SSP5 Pin",
	.ops = &skl_be_ssp_dai_ops,
	.playback = अणु
		.stream_name = "ssp5 Tx",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "ssp5 Rx",
		.channels_min = HDA_STEREO,
		.channels_max = HDA_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "iDisp1 Pin",
	.ops = &skl_link_dai_ops,
	.playback = अणु
		.stream_name = "iDisp1 Tx",
		.channels_min = HDA_STEREO,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_8000|SNDRV_PCM_RATE_16000|SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE |
			SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "iDisp2 Pin",
	.ops = &skl_link_dai_ops,
	.playback = अणु
		.stream_name = "iDisp2 Tx",
		.channels_min = HDA_STEREO,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_8000|SNDRV_PCM_RATE_16000|
			SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE |
			SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "iDisp3 Pin",
	.ops = &skl_link_dai_ops,
	.playback = अणु
		.stream_name = "iDisp3 Tx",
		.channels_min = HDA_STEREO,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_8000|SNDRV_PCM_RATE_16000|
			SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE |
			SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "DMIC01 Pin",
	.ops = &skl_dmic_dai_ops,
	.capture = अणु
		.stream_name = "DMIC01 Rx",
		.channels_min = HDA_MONO,
		.channels_max = HDA_QUAD,
		.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_16000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "DMIC16k Pin",
	.ops = &skl_dmic_dai_ops,
	.capture = अणु
		.stream_name = "DMIC16k Rx",
		.channels_min = HDA_MONO,
		.channels_max = HDA_QUAD,
		.rates = SNDRV_PCM_RATE_16000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "Analog CPU DAI",
	.ops = &skl_link_dai_ops,
	.playback = अणु
		.stream_name = "Analog CPU Playback",
		.channels_min = HDA_MONO,
		.channels_max = HDA_MAX,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Analog CPU Capture",
		.channels_min = HDA_MONO,
		.channels_max = HDA_MAX,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "Alt Analog CPU DAI",
	.ops = &skl_link_dai_ops,
	.playback = अणु
		.stream_name = "Alt Analog CPU Playback",
		.channels_min = HDA_MONO,
		.channels_max = HDA_MAX,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Alt Analog CPU Capture",
		.channels_min = HDA_MONO,
		.channels_max = HDA_MAX,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "Digital CPU DAI",
	.ops = &skl_link_dai_ops,
	.playback = अणु
		.stream_name = "Digital CPU Playback",
		.channels_min = HDA_MONO,
		.channels_max = HDA_MAX,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Digital CPU Capture",
		.channels_min = HDA_MONO,
		.channels_max = HDA_MAX,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
पूर्ण,
पूर्ण;

पूर्णांक skl_dai_load(काष्ठा snd_soc_component *cmp, पूर्णांक index,
			काष्ठा snd_soc_dai_driver *dai_drv,
			काष्ठा snd_soc_tplg_pcm *pcm, काष्ठा snd_soc_dai *dai)
अणु
	dai_drv->ops = &skl_pcm_dai_ops;

	वापस 0;
पूर्ण

अटल पूर्णांक skl_platक्रमm_soc_खोलो(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai_link *dai_link = rtd->dai_link;

	dev_dbg(asoc_rtd_to_cpu(rtd, 0)->dev, "In %s:%s\n", __func__,
					dai_link->cpus->dai_name);

	snd_soc_set_runसमय_hwparams(substream, &azx_pcm_hw);

	वापस 0;
पूर्ण

अटल पूर्णांक skl_coupled_trigger(काष्ठा snd_pcm_substream *substream,
					पूर्णांक cmd)
अणु
	काष्ठा hdac_bus *bus = get_bus_ctx(substream);
	काष्ठा hdac_ext_stream *stream;
	काष्ठा snd_pcm_substream *s;
	bool start;
	पूर्णांक sbits = 0;
	अचिन्हित दीर्घ cookie;
	काष्ठा hdac_stream *hstr;

	stream = get_hdac_ext_stream(substream);
	hstr = hdac_stream(stream);

	dev_dbg(bus->dev, "In %s cmd=%d\n", __func__, cmd);

	अगर (!hstr->prepared)
		वापस -EPIPE;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		start = true;
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		start = false;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (s->pcm->card != substream->pcm->card)
			जारी;
		stream = get_hdac_ext_stream(s);
		sbits |= 1 << hdac_stream(stream)->index;
		snd_pcm_trigger_करोne(s, substream);
	पूर्ण

	spin_lock_irqsave(&bus->reg_lock, cookie);

	/* first, set SYNC bits of corresponding streams */
	snd_hdac_stream_sync_trigger(hstr, true, sbits, AZX_REG_SSYNC);

	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (s->pcm->card != substream->pcm->card)
			जारी;
		stream = get_hdac_ext_stream(s);
		अगर (start)
			snd_hdac_stream_start(hdac_stream(stream), true);
		अन्यथा
			snd_hdac_stream_stop(hdac_stream(stream));
	पूर्ण
	spin_unlock_irqrestore(&bus->reg_lock, cookie);

	snd_hdac_stream_sync(hstr, start, sbits);

	spin_lock_irqsave(&bus->reg_lock, cookie);

	/* reset SYNC bits */
	snd_hdac_stream_sync_trigger(hstr, false, sbits, AZX_REG_SSYNC);
	अगर (start)
		snd_hdac_stream_समयcounter_init(hstr, sbits);
	spin_unlock_irqrestore(&bus->reg_lock, cookie);

	वापस 0;
पूर्ण

अटल पूर्णांक skl_platक्रमm_soc_trigger(काष्ठा snd_soc_component *component,
				    काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd)
अणु
	काष्ठा hdac_bus *bus = get_bus_ctx(substream);

	अगर (!bus->ppcap)
		वापस skl_coupled_trigger(substream, cmd);

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t skl_platक्रमm_soc_poपूर्णांकer(
	काष्ठा snd_soc_component *component,
	काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdac_ext_stream *hstream = get_hdac_ext_stream(substream);
	काष्ठा hdac_bus *bus = get_bus_ctx(substream);
	अचिन्हित पूर्णांक pos;

	/*
	 * Use DPIB क्रम Playback stream as the periodic DMA Position-in-
	 * Buffer Writes may be scheduled at the same समय or later than
	 * the MSI and करोes not guarantee to reflect the Position of the
	 * last buffer that was transferred. Whereas DPIB रेजिस्टर in
	 * HAD space reflects the actual data that is transferred.
	 * Use the position buffer क्रम capture, as DPIB ग_लिखो माला_लो
	 * completed earlier than the actual data written to the DDR.
	 *
	 * For capture stream following workaround is required to fix the
	 * incorrect position reporting.
	 *
	 * 1. Wait क्रम 20us beक्रमe पढ़ोing the DMA position in buffer once
	 * the पूर्णांकerrupt is generated क्रम stream completion as update happens
	 * on the HDA frame boundary i.e. 20.833uSec.
	 * 2. Read DPIB रेजिस्टर to flush the DMA position value. This dummy
	 * पढ़ो is required to flush DMA position value.
	 * 3. Read the DMA Position-in-Buffer. This value now will be equal to
	 * or greater than period boundary.
	 */

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		pos = पढ़ोl(bus->remap_addr + AZX_REG_VS_SDXDPIB_XBASE +
				(AZX_REG_VS_SDXDPIB_XINTERVAL *
				hdac_stream(hstream)->index));
	पूर्ण अन्यथा अणु
		udelay(20);
		पढ़ोl(bus->remap_addr +
				AZX_REG_VS_SDXDPIB_XBASE +
				(AZX_REG_VS_SDXDPIB_XINTERVAL *
				 hdac_stream(hstream)->index));
		pos = snd_hdac_stream_get_pos_posbuf(hdac_stream(hstream));
	पूर्ण

	अगर (pos >= hdac_stream(hstream)->bufsize)
		pos = 0;

	वापस bytes_to_frames(substream->runसमय, pos);
पूर्ण

अटल पूर्णांक skl_platक्रमm_soc_mmap(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream,
				 काष्ठा vm_area_काष्ठा *area)
अणु
	वापस snd_pcm_lib_शेष_mmap(substream, area);
पूर्ण

अटल u64 skl_adjust_codec_delay(काष्ठा snd_pcm_substream *substream,
				u64 nsec)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	u64 codec_frames, codec_nsecs;

	अगर (!codec_dai->driver->ops->delay)
		वापस nsec;

	codec_frames = codec_dai->driver->ops->delay(substream, codec_dai);
	codec_nsecs = भाग_u64(codec_frames * 1000000000LL,
			      substream->runसमय->rate);

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		वापस nsec + codec_nsecs;

	वापस (nsec > codec_nsecs) ? nsec - codec_nsecs : 0;
पूर्ण

अटल पूर्णांक skl_platक्रमm_soc_get_समय_info(
			काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream,
			काष्ठा बारpec64 *प्रणाली_ts, काष्ठा बारpec64 *audio_ts,
			काष्ठा snd_pcm_audio_tstamp_config *audio_tstamp_config,
			काष्ठा snd_pcm_audio_tstamp_report *audio_tstamp_report)
अणु
	काष्ठा hdac_ext_stream *sstream = get_hdac_ext_stream(substream);
	काष्ठा hdac_stream *hstr = hdac_stream(sstream);
	u64 nsec;

	अगर ((substream->runसमय->hw.info & SNDRV_PCM_INFO_HAS_LINK_ATIME) &&
		(audio_tstamp_config->type_requested == SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK)) अणु

		snd_pcm_समय_लो(substream->runसमय, प्रणाली_ts);

		nsec = समयcounter_पढ़ो(&hstr->tc);
		nsec = भाग_u64(nsec, 3); /* can be optimized */
		अगर (audio_tstamp_config->report_delay)
			nsec = skl_adjust_codec_delay(substream, nsec);

		*audio_ts = ns_to_बारpec64(nsec);

		audio_tstamp_report->actual_type = SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK;
		audio_tstamp_report->accuracy_report = 1; /* rest of काष्ठा is valid */
		audio_tstamp_report->accuracy = 42; /* 24MHzWallClk == 42ns resolution */

	पूर्ण अन्यथा अणु
		audio_tstamp_report->actual_type = SNDRV_PCM_AUDIO_TSTAMP_TYPE_DEFAULT;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा MAX_PREALLOC_SIZE	(32 * 1024 * 1024)

अटल पूर्णांक skl_platक्रमm_soc_new(काष्ठा snd_soc_component *component,
				काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा hdac_bus *bus = dev_get_drvdata(dai->dev);
	काष्ठा snd_pcm *pcm = rtd->pcm;
	अचिन्हित पूर्णांक size;
	काष्ठा skl_dev *skl = bus_to_skl(bus);

	अगर (dai->driver->playback.channels_min ||
		dai->driver->capture.channels_min) अणु
		/* buffer pre-allocation */
		size = CONFIG_SND_HDA_PREALLOC_SIZE * 1024;
		अगर (size > MAX_PREALLOC_SIZE)
			size = MAX_PREALLOC_SIZE;
		snd_pcm_set_managed_buffer_all(pcm,
					       SNDRV_DMA_TYPE_DEV_SG,
					       &skl->pci->dev,
					       size, MAX_PREALLOC_SIZE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_get_module_info(काष्ठा skl_dev *skl,
		काष्ठा skl_module_cfg *mconfig)
अणु
	काष्ठा skl_module_inst_id *pin_id;
	guid_t *uuid_mod, *uuid_tplg;
	काष्ठा skl_module *skl_module;
	काष्ठा uuid_module *module;
	पूर्णांक i, ret = -EIO;

	uuid_mod = (guid_t *)mconfig->guid;

	अगर (list_empty(&skl->uuid_list)) अणु
		dev_err(skl->dev, "Module list is empty\n");
		वापस -EIO;
	पूर्ण

	list_क्रम_each_entry(module, &skl->uuid_list, list) अणु
		अगर (guid_equal(uuid_mod, &module->uuid)) अणु
			mconfig->id.module_id = module->id;
			अगर (mconfig->module)
				mconfig->module->loadable = module->is_loadable;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस ret;

	uuid_mod = &module->uuid;
	ret = -EIO;
	क्रम (i = 0; i < skl->nr_modules; i++) अणु
		skl_module = skl->modules[i];
		uuid_tplg = &skl_module->uuid;
		अगर (guid_equal(uuid_mod, uuid_tplg)) अणु
			mconfig->module = skl_module;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (skl->nr_modules && ret)
		वापस ret;

	list_क्रम_each_entry(module, &skl->uuid_list, list) अणु
		क्रम (i = 0; i < MAX_IN_QUEUE; i++) अणु
			pin_id = &mconfig->m_in_pin[i].id;
			अगर (guid_equal(&pin_id->mod_uuid, &module->uuid))
				pin_id->module_id = module->id;
		पूर्ण

		क्रम (i = 0; i < MAX_OUT_QUEUE; i++) अणु
			pin_id = &mconfig->m_out_pin[i].id;
			अगर (guid_equal(&pin_id->mod_uuid, &module->uuid))
				pin_id->module_id = module->id;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_populate_modules(काष्ठा skl_dev *skl)
अणु
	काष्ठा skl_pipeline *p;
	काष्ठा skl_pipe_module *m;
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा skl_module_cfg *mconfig;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(p, &skl->ppl_list, node) अणु
		list_क्रम_each_entry(m, &p->pipe->w_list, node) अणु
			w = m->w;
			mconfig = w->priv;

			ret = skl_get_module_info(skl, mconfig);
			अगर (ret < 0) अणु
				dev_err(skl->dev,
					"query module info failed\n");
				वापस ret;
			पूर्ण

			skl_tplg_add_moduleid_in_bind_params(skl, w);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक skl_platक्रमm_soc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(component->dev);
	काष्ठा skl_dev *skl = bus_to_skl(bus);
	स्थिर काष्ठा skl_dsp_ops *ops;
	पूर्णांक ret;

	pm_runसमय_get_sync(component->dev);
	अगर (bus->ppcap) अणु
		skl->component = component;

		/* init debugfs */
		skl->debugfs = skl_debugfs_init(skl);

		ret = skl_tplg_init(component, bus);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Failed to init topology!\n");
			वापस ret;
		पूर्ण

		/* load the firmwares, since all is set */
		ops = skl_get_dsp_ops(skl->pci->device);
		अगर (!ops)
			वापस -EIO;

		/*
		 * Disable dynamic घड़ी and घातer gating during firmware
		 * and library करोwnload
		 */
		skl->enable_miscbdcge(component->dev, false);
		skl->घड़ी_घातer_gating(component->dev, false);

		ret = ops->init_fw(component->dev, skl);
		skl->enable_miscbdcge(component->dev, true);
		skl->घड़ी_घातer_gating(component->dev, true);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Failed to boot first fw: %d\n", ret);
			वापस ret;
		पूर्ण
		skl_populate_modules(skl);
		skl->update_d0i3c = skl_update_d0i3c;

		अगर (skl->cfg.astate_cfg != शून्य) अणु
			skl_dsp_set_astate_cfg(skl,
					skl->cfg.astate_cfg->count,
					skl->cfg.astate_cfg);
		पूर्ण
	पूर्ण
	pm_runसमय_mark_last_busy(component->dev);
	pm_runसमय_put_स्वतःsuspend(component->dev);

	वापस 0;
पूर्ण

अटल व्योम skl_platक्रमm_soc_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(component->dev);
	काष्ठा skl_dev *skl = bus_to_skl(bus);

	skl_tplg_निकास(component, bus);

	skl_debugfs_निकास(skl);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver skl_component  = अणु
	.name		= "pcm",
	.probe		= skl_platक्रमm_soc_probe,
	.हटाओ		= skl_platक्रमm_soc_हटाओ,
	.खोलो		= skl_platक्रमm_soc_खोलो,
	.trigger	= skl_platक्रमm_soc_trigger,
	.poपूर्णांकer	= skl_platक्रमm_soc_poपूर्णांकer,
	.get_समय_info	= skl_platक्रमm_soc_get_समय_info,
	.mmap		= skl_platक्रमm_soc_mmap,
	.pcm_स्थिरruct	= skl_platक्रमm_soc_new,
	.module_get_upon_खोलो = 1, /* increment refcount when a pcm is खोलोed */
पूर्ण;

पूर्णांक skl_platक्रमm_रेजिस्टर(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_dai_driver *dais;
	पूर्णांक num_dais = ARRAY_SIZE(skl_platक्रमm_dai);
	काष्ठा hdac_bus *bus = dev_get_drvdata(dev);
	काष्ठा skl_dev *skl = bus_to_skl(bus);

	skl->dais = kmemdup(skl_platक्रमm_dai, माप(skl_platक्रमm_dai),
			    GFP_KERNEL);
	अगर (!skl->dais) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	अगर (!skl->use_tplg_pcm) अणु
		dais = kपुनः_स्मृति(skl->dais, माप(skl_fe_dai) +
				माप(skl_platक्रमm_dai), GFP_KERNEL);
		अगर (!dais) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		skl->dais = dais;
		स_नकल(&skl->dais[ARRAY_SIZE(skl_platक्रमm_dai)], skl_fe_dai,
		       माप(skl_fe_dai));
		num_dais += ARRAY_SIZE(skl_fe_dai);
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(dev, &skl_component,
					 skl->dais, num_dais);
	अगर (ret)
		dev_err(dev, "soc component registration failed %d\n", ret);
err:
	वापस ret;
पूर्ण

पूर्णांक skl_platक्रमm_unरेजिस्टर(काष्ठा device *dev)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dev);
	काष्ठा skl_dev *skl = bus_to_skl(bus);
	काष्ठा skl_module_deferred_bind *modules, *पंचांगp;

	list_क्रम_each_entry_safe(modules, पंचांगp, &skl->bind_list, node) अणु
		list_del(&modules->node);
		kमुक्त(modules);
	पूर्ण

	kमुक्त(skl->dais);

	वापस 0;
पूर्ण
