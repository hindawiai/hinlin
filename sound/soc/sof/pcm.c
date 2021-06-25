<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//
// PCM Layer, पूर्णांकerface between ALSA and IPC.
//

#समावेश <linux/pm_runसमय.स>
#समावेश <sound/pcm_params.h>
#समावेश <sound/sof.h>
#समावेश "sof-priv.h"
#समावेश "sof-audio.h"
#समावेश "ops.h"
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_PROBES)
#समावेश "compress.h"
#पूर्ण_अगर

/* Create DMA buffer page table क्रम DSP */
अटल पूर्णांक create_page_table(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream,
			     अचिन्हित अक्षर *dma_area, माप_प्रकार size)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_sof_pcm *spcm;
	काष्ठा snd_dma_buffer *dmab = snd_pcm_get_dma_buf(substream);
	पूर्णांक stream = substream->stream;

	spcm = snd_sof_find_spcm_dai(component, rtd);
	अगर (!spcm)
		वापस -EINVAL;

	वापस snd_sof_create_page_table(component->dev, dmab,
		spcm->stream[stream].page_table.area, size);
पूर्ण

अटल पूर्णांक sof_pcm_dsp_params(काष्ठा snd_sof_pcm *spcm, काष्ठा snd_pcm_substream *substream,
			      स्थिर काष्ठा sof_ipc_pcm_params_reply *reply)
अणु
	काष्ठा snd_soc_component *scomp = spcm->scomp;
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);

	/* validate offset */
	पूर्णांक ret = snd_sof_ipc_pcm_params(sdev, substream, reply);

	अगर (ret < 0)
		dev_err(scomp->dev, "error: got wrong reply for PCM %d\n",
			spcm->pcm.pcm_id);

	वापस ret;
पूर्ण

/*
 * sof pcm period elapse work
 */
व्योम snd_sof_pcm_period_elapsed_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_sof_pcm_stream *sps =
		container_of(work, काष्ठा snd_sof_pcm_stream,
			     period_elapsed_work);

	snd_pcm_period_elapsed(sps->substream);
पूर्ण

/*
 * sof pcm period elapse, this could be called at irq thपढ़ो context.
 */
व्योम snd_sof_pcm_period_elapsed(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, SOF_AUDIO_PCM_DRV_NAME);
	काष्ठा snd_sof_pcm *spcm;

	spcm = snd_sof_find_spcm_dai(component, rtd);
	अगर (!spcm) अणु
		dev_err(component->dev,
			"error: period elapsed for unknown stream!\n");
		वापस;
	पूर्ण

	/*
	 * snd_pcm_period_elapsed() can be called in पूर्णांकerrupt context
	 * beक्रमe IRQ_HANDLED is वापसed. Inside snd_pcm_period_elapsed(),
	 * when the PCM is करोne draining or xrun happened, a STOP IPC will
	 * then be sent and this IPC will hit IPC समयout.
	 * To aव्योम sending IPC beक्रमe the previous IPC is handled, we
	 * schedule delayed work here to call the snd_pcm_period_elapsed().
	 */
	schedule_work(&spcm->stream[substream->stream].period_elapsed_work);
पूर्ण
EXPORT_SYMBOL(snd_sof_pcm_period_elapsed);

अटल पूर्णांक sof_pcm_dsp_pcm_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_sof_dev *sdev,
				काष्ठा snd_sof_pcm *spcm)
अणु
	काष्ठा sof_ipc_stream stream;
	काष्ठा sof_ipc_reply reply;
	पूर्णांक ret;

	stream.hdr.size = माप(stream);
	stream.hdr.cmd = SOF_IPC_GLB_STREAM_MSG | SOF_IPC_STREAM_PCM_FREE;
	stream.comp_id = spcm->stream[substream->stream].comp_id;

	/* send IPC to the DSP */
	ret = sof_ipc_tx_message(sdev->ipc, stream.hdr.cmd, &stream,
				 माप(stream), &reply, माप(reply));
	अगर (!ret)
		spcm->prepared[substream->stream] = false;

	वापस ret;
पूर्ण

अटल पूर्णांक sof_pcm_hw_params(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	काष्ठा snd_sof_pcm *spcm;
	काष्ठा sof_ipc_pcm_params pcm;
	काष्ठा sof_ipc_pcm_params_reply ipc_params_reply;
	पूर्णांक ret;

	/* nothing to करो क्रम BE */
	अगर (rtd->dai_link->no_pcm)
		वापस 0;

	spcm = snd_sof_find_spcm_dai(component, rtd);
	अगर (!spcm)
		वापस -EINVAL;

	/*
	 * Handle repeated calls to hw_params() without मुक्त_pcm() in
	 * between. At least ALSA OSS emulation depends on this.
	 */
	अगर (spcm->prepared[substream->stream]) अणु
		ret = sof_pcm_dsp_pcm_मुक्त(substream, sdev, spcm);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	dev_dbg(component->dev, "pcm: hw params stream %d dir %d\n",
		spcm->pcm.pcm_id, substream->stream);

	स_रखो(&pcm, 0, माप(pcm));

	/* create compressed page table क्रम audio firmware */
	अगर (runसमय->buffer_changed) अणु
		ret = create_page_table(component, substream, runसमय->dma_area,
					runसमय->dma_bytes);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* number of pages should be rounded up */
	pcm.params.buffer.pages = PFN_UP(runसमय->dma_bytes);

	/* set IPC PCM parameters */
	pcm.hdr.size = माप(pcm);
	pcm.hdr.cmd = SOF_IPC_GLB_STREAM_MSG | SOF_IPC_STREAM_PCM_PARAMS;
	pcm.comp_id = spcm->stream[substream->stream].comp_id;
	pcm.params.hdr.size = माप(pcm.params);
	pcm.params.buffer.phy_addr =
		spcm->stream[substream->stream].page_table.addr;
	pcm.params.buffer.size = runसमय->dma_bytes;
	pcm.params.direction = substream->stream;
	pcm.params.sample_valid_bytes = params_width(params) >> 3;
	pcm.params.buffer_fmt = SOF_IPC_BUFFER_INTERLEAVED;
	pcm.params.rate = params_rate(params);
	pcm.params.channels = params_channels(params);
	pcm.params.host_period_bytes = params_period_bytes(params);

	/* container size */
	ret = snd_pcm_क्रमmat_physical_width(params_क्रमmat(params));
	अगर (ret < 0)
		वापस ret;
	pcm.params.sample_container_bytes = ret >> 3;

	/* क्रमmat */
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16:
		pcm.params.frame_fmt = SOF_IPC_FRAME_S16_LE;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24:
		pcm.params.frame_fmt = SOF_IPC_FRAME_S24_4LE;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32:
		pcm.params.frame_fmt = SOF_IPC_FRAME_S32_LE;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_FLOAT:
		pcm.params.frame_fmt = SOF_IPC_FRAME_FLOAT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* firmware alपढ़ोy configured host stream */
	ret = snd_sof_pcm_platक्रमm_hw_params(sdev,
					     substream,
					     params,
					     &pcm.params);
	अगर (ret < 0) अणु
		dev_err(component->dev, "error: platform hw params failed\n");
		वापस ret;
	पूर्ण

	dev_dbg(component->dev, "stream_tag %d", pcm.params.stream_tag);

	/* send IPC to the DSP */
	ret = sof_ipc_tx_message(sdev->ipc, pcm.hdr.cmd, &pcm, माप(pcm),
				 &ipc_params_reply, माप(ipc_params_reply));
	अगर (ret < 0) अणु
		dev_err(component->dev, "error: hw params ipc failed for stream %d\n",
			pcm.params.stream_tag);
		वापस ret;
	पूर्ण

	ret = sof_pcm_dsp_params(spcm, substream, &ipc_params_reply);
	अगर (ret < 0)
		वापस ret;

	spcm->prepared[substream->stream] = true;

	/* save pcm hw_params */
	स_नकल(&spcm->params[substream->stream], params, माप(*params));

	वापस ret;
पूर्ण

अटल पूर्णांक sof_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	काष्ठा snd_sof_pcm *spcm;
	पूर्णांक ret, err = 0;

	/* nothing to करो क्रम BE */
	अगर (rtd->dai_link->no_pcm)
		वापस 0;

	spcm = snd_sof_find_spcm_dai(component, rtd);
	अगर (!spcm)
		वापस -EINVAL;

	dev_dbg(component->dev, "pcm: free stream %d dir %d\n",
		spcm->pcm.pcm_id, substream->stream);

	अगर (spcm->prepared[substream->stream]) अणु
		ret = sof_pcm_dsp_pcm_मुक्त(substream, sdev, spcm);
		अगर (ret < 0)
			err = ret;
	पूर्ण

	cancel_work_sync(&spcm->stream[substream->stream].period_elapsed_work);

	ret = snd_sof_pcm_platक्रमm_hw_मुक्त(sdev, substream);
	अगर (ret < 0) अणु
		dev_err(component->dev, "error: platform hw free failed\n");
		err = ret;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक sof_pcm_prepare(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_sof_pcm *spcm;
	पूर्णांक ret;

	/* nothing to करो क्रम BE */
	अगर (rtd->dai_link->no_pcm)
		वापस 0;

	spcm = snd_sof_find_spcm_dai(component, rtd);
	अगर (!spcm)
		वापस -EINVAL;

	अगर (spcm->prepared[substream->stream])
		वापस 0;

	dev_dbg(component->dev, "pcm: prepare stream %d dir %d\n",
		spcm->pcm.pcm_id, substream->stream);

	/* set hw_params */
	ret = sof_pcm_hw_params(component,
				substream, &spcm->params[substream->stream]);
	अगर (ret < 0) अणु
		dev_err(component->dev,
			"error: set pcm hw_params after resume\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * FE dai link trigger actions are always executed in non-atomic context because
 * they involve IPC's.
 */
अटल पूर्णांक sof_pcm_trigger(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	काष्ठा snd_sof_pcm *spcm;
	काष्ठा sof_ipc_stream stream;
	काष्ठा sof_ipc_reply reply;
	bool reset_hw_params = false;
	bool ipc_first = false;
	पूर्णांक ret;

	/* nothing to करो क्रम BE */
	अगर (rtd->dai_link->no_pcm)
		वापस 0;

	spcm = snd_sof_find_spcm_dai(component, rtd);
	अगर (!spcm)
		वापस -EINVAL;

	dev_dbg(component->dev, "pcm: trigger stream %d dir %d cmd %d\n",
		spcm->pcm.pcm_id, substream->stream, cmd);

	stream.hdr.size = माप(stream);
	stream.hdr.cmd = SOF_IPC_GLB_STREAM_MSG;
	stream.comp_id = spcm->stream[substream->stream].comp_id;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		stream.hdr.cmd |= SOF_IPC_STREAM_TRIG_PAUSE;
		ipc_first = true;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		stream.hdr.cmd |= SOF_IPC_STREAM_TRIG_RELEASE;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (spcm->stream[substream->stream].suspend_ignored) अणु
			/*
			 * this हाल will be triggered when INFO_RESUME is
			 * supported, no need to resume streams that reमुख्यed
			 * enabled in D0ix.
			 */
			spcm->stream[substream->stream].suspend_ignored = false;
			वापस 0;
		पूर्ण

		/* set up hw_params */
		ret = sof_pcm_prepare(component, substream);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"error: failed to set up hw_params upon resume\n");
			वापस ret;
		पूर्ण

		fallthrough;
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (spcm->stream[substream->stream].suspend_ignored) अणु
			/*
			 * This हाल will be triggered when INFO_RESUME is
			 * not supported, no need to re-start streams that
			 * reमुख्यed enabled in D0ix.
			 */
			spcm->stream[substream->stream].suspend_ignored = false;
			वापस 0;
		पूर्ण
		stream.hdr.cmd |= SOF_IPC_STREAM_TRIG_START;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (sdev->प्रणाली_suspend_target == SOF_SUSPEND_S0IX &&
		    spcm->stream[substream->stream].d0i3_compatible) अणु
			/*
			 * trap the event, not sending trigger stop to
			 * prevent the FW pipelines from being stopped,
			 * and mark the flag to ignore the upcoming DAPM
			 * PM events.
			 */
			spcm->stream[substream->stream].suspend_ignored = true;
			वापस 0;
		पूर्ण
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_STOP:
		stream.hdr.cmd |= SOF_IPC_STREAM_TRIG_STOP;
		ipc_first = true;
		reset_hw_params = true;
		अवरोध;
	शेष:
		dev_err(component->dev, "error: unhandled trigger cmd %d\n",
			cmd);
		वापस -EINVAL;
	पूर्ण

	/*
	 * DMA and IPC sequence is dअगरferent क्रम start and stop. Need to send
	 * STOP IPC beक्रमe stop DMA
	 */
	अगर (!ipc_first)
		snd_sof_pcm_platक्रमm_trigger(sdev, substream, cmd);

	/* send IPC to the DSP */
	ret = sof_ipc_tx_message(sdev->ipc, stream.hdr.cmd, &stream,
				 माप(stream), &reply, माप(reply));

	/* need to STOP DMA even अगर STOP IPC failed */
	अगर (ipc_first)
		snd_sof_pcm_platक्रमm_trigger(sdev, substream, cmd);

	/* मुक्त PCM अगर reset_hw_params is set and the STOP IPC is successful */
	अगर (!ret && reset_hw_params)
		ret = sof_pcm_dsp_pcm_मुक्त(substream, sdev, spcm);

	वापस ret;
पूर्ण

अटल snd_pcm_uframes_t sof_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
					 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	काष्ठा snd_sof_pcm *spcm;
	snd_pcm_uframes_t host, dai;

	/* nothing to करो क्रम BE */
	अगर (rtd->dai_link->no_pcm)
		वापस 0;

	/* use dsp ops poपूर्णांकer callback directly अगर set */
	अगर (sof_ops(sdev)->pcm_poपूर्णांकer)
		वापस sof_ops(sdev)->pcm_poपूर्णांकer(sdev, substream);

	spcm = snd_sof_find_spcm_dai(component, rtd);
	अगर (!spcm)
		वापस -EINVAL;

	/* पढ़ो position from DSP */
	host = bytes_to_frames(substream->runसमय,
			       spcm->stream[substream->stream].posn.host_posn);
	dai = bytes_to_frames(substream->runसमय,
			      spcm->stream[substream->stream].posn.dai_posn);

	dev_vdbg(component->dev,
		 "PCM: stream %d dir %d DMA position %lu DAI position %lu\n",
		 spcm->pcm.pcm_id, substream->stream, host, dai);

	वापस host;
पूर्ण

अटल पूर्णांक sof_pcm_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	स्थिर काष्ठा snd_sof_dsp_ops *ops = sof_ops(sdev);
	काष्ठा snd_sof_pcm *spcm;
	काष्ठा snd_soc_tplg_stream_caps *caps;
	पूर्णांक ret;

	/* nothing to करो क्रम BE */
	अगर (rtd->dai_link->no_pcm)
		वापस 0;

	spcm = snd_sof_find_spcm_dai(component, rtd);
	अगर (!spcm)
		वापस -EINVAL;

	dev_dbg(component->dev, "pcm: open stream %d dir %d\n",
		spcm->pcm.pcm_id, substream->stream);


	caps = &spcm->pcm.caps[substream->stream];

	/* set runसमय config */
	runसमय->hw.info = ops->hw_info; /* platक्रमm-specअगरic */

	/* set any runसमय स्थिरraपूर्णांकs based on topology */
	runसमय->hw.क्रमmats = le64_to_cpu(caps->क्रमmats);
	runसमय->hw.period_bytes_min = le32_to_cpu(caps->period_size_min);
	runसमय->hw.period_bytes_max = le32_to_cpu(caps->period_size_max);
	runसमय->hw.periods_min = le32_to_cpu(caps->periods_min);
	runसमय->hw.periods_max = le32_to_cpu(caps->periods_max);

	/*
	 * caps->buffer_size_min is not used since the
	 * snd_pcm_hardware काष्ठाure only defines buffer_bytes_max
	 */
	runसमय->hw.buffer_bytes_max = le32_to_cpu(caps->buffer_size_max);

	dev_dbg(component->dev, "period min %zd max %zd bytes\n",
		runसमय->hw.period_bytes_min,
		runसमय->hw.period_bytes_max);
	dev_dbg(component->dev, "period count %d max %d\n",
		runसमय->hw.periods_min,
		runसमय->hw.periods_max);
	dev_dbg(component->dev, "buffer max %zd bytes\n",
		runसमय->hw.buffer_bytes_max);

	/* set रुको समय - TODO: come from topology */
	substream->रुको_समय = 500;

	spcm->stream[substream->stream].posn.host_posn = 0;
	spcm->stream[substream->stream].posn.dai_posn = 0;
	spcm->stream[substream->stream].substream = substream;
	spcm->prepared[substream->stream] = false;

	ret = snd_sof_pcm_platक्रमm_खोलो(sdev, substream);
	अगर (ret < 0)
		dev_err(component->dev, "error: pcm open failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक sof_pcm_बंद(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	काष्ठा snd_sof_pcm *spcm;
	पूर्णांक err;

	/* nothing to करो क्रम BE */
	अगर (rtd->dai_link->no_pcm)
		वापस 0;

	spcm = snd_sof_find_spcm_dai(component, rtd);
	अगर (!spcm)
		वापस -EINVAL;

	dev_dbg(component->dev, "pcm: close stream %d dir %d\n",
		spcm->pcm.pcm_id, substream->stream);

	err = snd_sof_pcm_platक्रमm_बंद(sdev, substream);
	अगर (err < 0) अणु
		dev_err(component->dev, "error: pcm close failed %d\n",
			err);
		/*
		 * keep going, no poपूर्णांक in preventing the बंद
		 * from happening
		 */
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Pre-allocate playback/capture audio buffer pages.
 * no need to explicitly release memory pपुनः_स्मृतिated by sof_pcm_new in pcm_मुक्त
 * snd_pcm_lib_pपुनः_स्मृतिate_मुक्त_क्रम_all() is called by the core.
 */
अटल पूर्णांक sof_pcm_new(काष्ठा snd_soc_component *component,
		       काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	काष्ठा snd_sof_pcm *spcm;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	काष्ठा snd_soc_tplg_stream_caps *caps;
	पूर्णांक stream = SNDRV_PCM_STREAM_PLAYBACK;

	/* find SOF PCM क्रम this RTD */
	spcm = snd_sof_find_spcm_dai(component, rtd);
	अगर (!spcm) अणु
		dev_warn(component->dev, "warn: can't find PCM with DAI ID %d\n",
			 rtd->dai_link->id);
		वापस 0;
	पूर्ण

	dev_dbg(component->dev, "creating new PCM %s\n", spcm->pcm.pcm_name);

	/* करो we need to pre-allocate playback audio buffer pages */
	अगर (!spcm->pcm.playback)
		जाओ capture;

	caps = &spcm->pcm.caps[stream];

	/* pre-allocate playback audio buffer pages */
	dev_dbg(component->dev,
		"spcm: allocate %s playback DMA buffer size 0x%x max 0x%x\n",
		caps->name, caps->buffer_size_min, caps->buffer_size_max);

	अगर (!pcm->streams[stream].substream) अणु
		dev_err(component->dev, "error: NULL playback substream!\n");
		वापस -EINVAL;
	पूर्ण

	snd_pcm_set_managed_buffer(pcm->streams[stream].substream,
				   SNDRV_DMA_TYPE_DEV_SG, sdev->dev,
				   0, le32_to_cpu(caps->buffer_size_max));
capture:
	stream = SNDRV_PCM_STREAM_CAPTURE;

	/* करो we need to pre-allocate capture audio buffer pages */
	अगर (!spcm->pcm.capture)
		वापस 0;

	caps = &spcm->pcm.caps[stream];

	/* pre-allocate capture audio buffer pages */
	dev_dbg(component->dev,
		"spcm: allocate %s capture DMA buffer size 0x%x max 0x%x\n",
		caps->name, caps->buffer_size_min, caps->buffer_size_max);

	अगर (!pcm->streams[stream].substream) अणु
		dev_err(component->dev, "error: NULL capture substream!\n");
		वापस -EINVAL;
	पूर्ण

	snd_pcm_set_managed_buffer(pcm->streams[stream].substream,
				   SNDRV_DMA_TYPE_DEV_SG, sdev->dev,
				   0, le32_to_cpu(caps->buffer_size_max));

	वापस 0;
पूर्ण

अटल व्योम ssp_dai_config_pcm_params_match(काष्ठा snd_sof_dev *sdev, स्थिर अक्षर *link_name,
					    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा sof_ipc_dai_config *config;
	काष्ठा snd_sof_dai *dai;
	पूर्णांक i;

	/*
	 * Search क्रम all matching DAIs as we can have both playback and capture DAI
	 * associated with the same link.
	 */
	list_क्रम_each_entry(dai, &sdev->dai_list, list) अणु
		अगर (!dai->name || म_भेद(link_name, dai->name))
			जारी;
		क्रम (i = 0; i < dai->number_configs; i++) अणु
			config = &dai->dai_config[i];
			अगर (config->ssp.fsync_rate == params_rate(params)) अणु
				dev_dbg(sdev->dev, "DAI config %d matches pcm hw params\n", i);
				dai->current_config = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* fixup the BE DAI link to match any values from topology */
पूर्णांक sof_pcm_dai_link_fixup(काष्ठा snd_soc_pcm_runसमय *rtd, काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, SOF_AUDIO_PCM_DRV_NAME);
	काष्ठा snd_sof_dai *dai =
		snd_sof_find_dai(component, (अक्षर *)rtd->dai_link->name);
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dpcm *dpcm;

	/* no topology exists क्रम this BE, try a common configuration */
	अगर (!dai) अणु
		dev_warn(component->dev,
			 "warning: no topology found for BE DAI %s config\n",
			 rtd->dai_link->name);

		/*  set 48k, stereo, 16bits by शेष */
		rate->min = 48000;
		rate->max = 48000;

		channels->min = 2;
		channels->max = 2;

		snd_mask_none(fmt);
		snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S16_LE);

		वापस 0;
	पूर्ण

	/* पढ़ो क्रमmat from topology */
	snd_mask_none(fmt);

	चयन (dai->comp_dai.config.frame_fmt) अणु
	हाल SOF_IPC_FRAME_S16_LE:
		snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S16_LE);
		अवरोध;
	हाल SOF_IPC_FRAME_S24_4LE:
		snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S24_LE);
		अवरोध;
	हाल SOF_IPC_FRAME_S32_LE:
		snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S32_LE);
		अवरोध;
	शेष:
		dev_err(component->dev, "error: No available DAI format!\n");
		वापस -EINVAL;
	पूर्ण

	/* पढ़ो rate and channels from topology */
	चयन (dai->dai_config->type) अणु
	हाल SOF_DAI_INTEL_SSP:
		/* search क्रम config to pcm params match, अगर not found use शेष */
		ssp_dai_config_pcm_params_match(sdev, (अक्षर *)rtd->dai_link->name, params);

		rate->min = dai->dai_config[dai->current_config].ssp.fsync_rate;
		rate->max = dai->dai_config[dai->current_config].ssp.fsync_rate;
		channels->min = dai->dai_config[dai->current_config].ssp.tdm_slots;
		channels->max = dai->dai_config[dai->current_config].ssp.tdm_slots;

		dev_dbg(component->dev,
			"rate_min: %d rate_max: %d\n", rate->min, rate->max);
		dev_dbg(component->dev,
			"channels_min: %d channels_max: %d\n",
			channels->min, channels->max);

		अवरोध;
	हाल SOF_DAI_INTEL_DMIC:
		/* DMIC only supports 16 or 32 bit क्रमmats */
		अगर (dai->comp_dai.config.frame_fmt == SOF_IPC_FRAME_S24_4LE) अणु
			dev_err(component->dev,
				"error: invalid fmt %d for DAI type %d\n",
				dai->comp_dai.config.frame_fmt,
				dai->dai_config->type);
		पूर्ण
		अवरोध;
	हाल SOF_DAI_INTEL_HDA:
		/*
		 * HDAudio करोes not follow the शेष trigger
		 * sequence due to firmware implementation
		 */
		क्रम_each_dpcm_fe(rtd, SNDRV_PCM_STREAM_PLAYBACK, dpcm) अणु
			काष्ठा snd_soc_pcm_runसमय *fe = dpcm->fe;

			fe->dai_link->trigger[SNDRV_PCM_STREAM_PLAYBACK] =
				SND_SOC_DPCM_TRIGGER_POST;
		पूर्ण
		अवरोध;
	हाल SOF_DAI_INTEL_ALH:
		/*
		 * Dai could run with dअगरferent channel count compared with
		 * front end, so get dai channel count from topology
		 */
		channels->min = dai->dai_config->alh.channels;
		channels->max = dai->dai_config->alh.channels;
		अवरोध;
	हाल SOF_DAI_IMX_ESAI:
		rate->min = dai->dai_config->esai.fsync_rate;
		rate->max = dai->dai_config->esai.fsync_rate;
		channels->min = dai->dai_config->esai.tdm_slots;
		channels->max = dai->dai_config->esai.tdm_slots;

		dev_dbg(component->dev,
			"rate_min: %d rate_max: %d\n", rate->min, rate->max);
		dev_dbg(component->dev,
			"channels_min: %d channels_max: %d\n",
			channels->min, channels->max);
		अवरोध;
	हाल SOF_DAI_IMX_SAI:
		rate->min = dai->dai_config->sai.fsync_rate;
		rate->max = dai->dai_config->sai.fsync_rate;
		channels->min = dai->dai_config->sai.tdm_slots;
		channels->max = dai->dai_config->sai.tdm_slots;

		dev_dbg(component->dev,
			"rate_min: %d rate_max: %d\n", rate->min, rate->max);
		dev_dbg(component->dev,
			"channels_min: %d channels_max: %d\n",
			channels->min, channels->max);
		अवरोध;
	शेष:
		dev_err(component->dev, "error: invalid DAI type %d\n",
			dai->dai_config->type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sof_pcm_dai_link_fixup);

अटल पूर्णांक sof_pcm_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	काष्ठा snd_sof_pdata *plat_data = sdev->pdata;
	स्थिर अक्षर *tplg_filename;
	पूर्णांक ret;

	/* load the शेष topology */
	sdev->component = component;

	tplg_filename = devm_kaप्र_लिखो(sdev->dev, GFP_KERNEL,
				       "%s/%s",
				       plat_data->tplg_filename_prefix,
				       plat_data->tplg_filename);
	अगर (!tplg_filename)
		वापस -ENOMEM;

	ret = snd_sof_load_topology(component, tplg_filename);
	अगर (ret < 0) अणु
		dev_err(component->dev, "error: failed to load DSP topology %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sof_pcm_हटाओ(काष्ठा snd_soc_component *component)
अणु
	/* हटाओ topology */
	snd_soc_tplg_component_हटाओ(component);
पूर्ण

व्योम snd_sof_new_platक्रमm_drv(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_soc_component_driver *pd = &sdev->plat_drv;
	काष्ठा snd_sof_pdata *plat_data = sdev->pdata;
	स्थिर अक्षर *drv_name;

	drv_name = plat_data->machine->drv_name;

	pd->name = "sof-audio-component";
	pd->probe = sof_pcm_probe;
	pd->हटाओ = sof_pcm_हटाओ;
	pd->खोलो = sof_pcm_खोलो;
	pd->बंद = sof_pcm_बंद;
	pd->hw_params = sof_pcm_hw_params;
	pd->prepare = sof_pcm_prepare;
	pd->hw_मुक्त = sof_pcm_hw_मुक्त;
	pd->trigger = sof_pcm_trigger;
	pd->poपूर्णांकer = sof_pcm_poपूर्णांकer;

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_COMPRESS)
	pd->compress_ops = &sof_compressed_ops;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_PROBES)
	/* override cops when probe support is enabled */
	pd->compress_ops = &sof_probe_compressed_ops;
#पूर्ण_अगर
	pd->pcm_स्थिरruct = sof_pcm_new;
	pd->ignore_machine = drv_name;
	pd->be_hw_params_fixup = sof_pcm_dai_link_fixup;
	pd->be_pcm_base = SOF_BE_PCM_BASE;
	pd->use_dai_pcm_id = true;
	pd->topology_name_prefix = "sof";

	 /* increment module refcount when a pcm is खोलोed */
	pd->module_get_upon_खोलो = 1;
पूर्ण
