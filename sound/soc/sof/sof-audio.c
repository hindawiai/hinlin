<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2019 Intel Corporation. All rights reserved.
//
// Author: Ranjani Sridharan <ranjani.sridharan@linux.पूर्णांकel.com>
//

#समावेश "sof-audio.h"
#समावेश "ops.h"

/*
 * helper to determine अगर there are only D0i3 compatible
 * streams active
 */
bool snd_sof_dsp_only_d0i3_compatible_stream_active(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_sof_pcm *spcm;
	bool d0i3_compatible_active = false;
	पूर्णांक dir;

	list_क्रम_each_entry(spcm, &sdev->pcm_list, list) अणु
		क्रम_each_pcm_streams(dir) अणु
			substream = spcm->stream[dir].substream;
			अगर (!substream || !substream->runसमय)
				जारी;

			/*
			 * substream->runसमय being not शून्य indicates
			 * that the stream is खोलो. No need to check the
			 * stream state.
			 */
			अगर (!spcm->stream[dir].d0i3_compatible)
				वापस false;

			d0i3_compatible_active = true;
		पूर्ण
	पूर्ण

	वापस d0i3_compatible_active;
पूर्ण
EXPORT_SYMBOL(snd_sof_dsp_only_d0i3_compatible_stream_active);

bool snd_sof_stream_suspend_ignored(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pcm *spcm;

	list_क्रम_each_entry(spcm, &sdev->pcm_list, list) अणु
		अगर (spcm->stream[SNDRV_PCM_STREAM_PLAYBACK].suspend_ignored ||
		    spcm->stream[SNDRV_PCM_STREAM_CAPTURE].suspend_ignored)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक sof_set_hw_params_upon_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_sof_pcm *spcm;
	snd_pcm_state_t state;
	पूर्णांक dir;

	/*
	 * SOF requires hw_params to be set-up पूर्णांकernally upon resume.
	 * So, set the flag to indicate this क्रम those streams that
	 * have been suspended.
	 */
	list_क्रम_each_entry(spcm, &sdev->pcm_list, list) अणु
		क्रम_each_pcm_streams(dir) अणु
			/*
			 * करो not reset hw_params upon resume क्रम streams that
			 * were kept running during suspend
			 */
			अगर (spcm->stream[dir].suspend_ignored)
				जारी;

			substream = spcm->stream[dir].substream;
			अगर (!substream || !substream->runसमय)
				जारी;

			state = substream->runसमय->status->state;
			अगर (state == SNDRV_PCM_STATE_SUSPENDED)
				spcm->prepared[dir] = false;
		पूर्ण
	पूर्ण

	/* set पूर्णांकernal flag क्रम BE */
	वापस snd_sof_dsp_hw_params_upon_resume(sdev);
पूर्ण

अटल पूर्णांक sof_restore_kcontrols(काष्ठा device *dev)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);
	काष्ठा snd_sof_control *scontrol;
	पूर्णांक ipc_cmd, ctrl_type;
	पूर्णांक ret = 0;

	/* restore kcontrol values */
	list_क्रम_each_entry(scontrol, &sdev->kcontrol_list, list) अणु
		/* reset पढ़ोback offset क्रम scontrol after resuming */
		scontrol->पढ़ोback_offset = 0;

		/* notअगरy DSP of kcontrol values */
		चयन (scontrol->cmd) अणु
		हाल SOF_CTRL_CMD_VOLUME:
		हाल SOF_CTRL_CMD_ENUM:
		हाल SOF_CTRL_CMD_SWITCH:
			ipc_cmd = SOF_IPC_COMP_SET_VALUE;
			ctrl_type = SOF_CTRL_TYPE_VALUE_CHAN_SET;
			ret = snd_sof_ipc_set_get_comp_data(scontrol,
							    ipc_cmd, ctrl_type,
							    scontrol->cmd,
							    true);
			अवरोध;
		हाल SOF_CTRL_CMD_BINARY:
			ipc_cmd = SOF_IPC_COMP_SET_DATA;
			ctrl_type = SOF_CTRL_TYPE_DATA_SET;
			ret = snd_sof_ipc_set_get_comp_data(scontrol,
							    ipc_cmd, ctrl_type,
							    scontrol->cmd,
							    true);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		अगर (ret < 0) अणु
			dev_err(dev,
				"error: failed kcontrol value set for widget: %d\n",
				scontrol->comp_id);

			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा sof_ipc_pipe_new *snd_sof_pipeline_find(काष्ठा snd_sof_dev *sdev,
						     पूर्णांक pipeline_id)
अणु
	स्थिर काष्ठा snd_sof_widget *swidget;

	list_क्रम_each_entry(swidget, &sdev->widget_list, list)
		अगर (swidget->id == snd_soc_dapm_scheduler) अणु
			स्थिर काष्ठा sof_ipc_pipe_new *pipeline =
				swidget->निजी;
			अगर (pipeline->pipeline_id == pipeline_id)
				वापस pipeline;
		पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक sof_restore_pipelines(काष्ठा device *dev)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);
	काष्ठा snd_sof_widget *swidget;
	काष्ठा snd_sof_route *sroute;
	काष्ठा sof_ipc_pipe_new *pipeline;
	काष्ठा snd_sof_dai *dai;
	काष्ठा sof_ipc_cmd_hdr *hdr;
	काष्ठा sof_ipc_comp *comp;
	माप_प्रकार ipc_size;
	पूर्णांक ret;

	/* restore pipeline components */
	list_क्रम_each_entry_reverse(swidget, &sdev->widget_list, list) अणु
		काष्ठा sof_ipc_comp_reply r;

		/* skip अगर there is no निजी data */
		अगर (!swidget->निजी)
			जारी;

		ret = sof_pipeline_core_enable(sdev, swidget);
		अगर (ret < 0) अणु
			dev_err(dev,
				"error: failed to enable target core: %d\n",
				ret);

			वापस ret;
		पूर्ण

		चयन (swidget->id) अणु
		हाल snd_soc_dapm_dai_in:
		हाल snd_soc_dapm_dai_out:
			ipc_size = माप(काष्ठा sof_ipc_comp_dai) +
				   माप(काष्ठा sof_ipc_comp_ext);
			comp = kzalloc(ipc_size, GFP_KERNEL);
			अगर (!comp)
				वापस -ENOMEM;

			dai = swidget->निजी;
			स_नकल(comp, &dai->comp_dai,
			       माप(काष्ठा sof_ipc_comp_dai));

			/* append extended data to the end of the component */
			स_नकल((u8 *)comp + माप(काष्ठा sof_ipc_comp_dai),
			       &swidget->comp_ext, माप(swidget->comp_ext));

			ret = sof_ipc_tx_message(sdev->ipc, comp->hdr.cmd,
						 comp, ipc_size,
						 &r, माप(r));
			kमुक्त(comp);
			अवरोध;
		हाल snd_soc_dapm_scheduler:

			/*
			 * During suspend, all DSP cores are घातered off.
			 * Thereक्रमe upon resume, create the pipeline comp
			 * and घातer up the core that the pipeline is
			 * scheduled on.
			 */
			pipeline = swidget->निजी;
			ret = sof_load_pipeline_ipc(dev, pipeline, &r);
			अवरोध;
		शेष:
			hdr = swidget->निजी;
			ret = sof_ipc_tx_message(sdev->ipc, hdr->cmd,
						 swidget->निजी, hdr->size,
						 &r, माप(r));
			अवरोध;
		पूर्ण
		अगर (ret < 0) अणु
			dev_err(dev,
				"error: failed to load widget type %d with ID: %d\n",
				swidget->widget->id, swidget->comp_id);

			वापस ret;
		पूर्ण
	पूर्ण

	/* restore pipeline connections */
	list_क्रम_each_entry_reverse(sroute, &sdev->route_list, list) अणु
		काष्ठा sof_ipc_pipe_comp_connect *connect;
		काष्ठा sof_ipc_reply reply;

		/* skip अगर there's no निजी data */
		अगर (!sroute->निजी)
			जारी;

		connect = sroute->निजी;

		/* send ipc */
		ret = sof_ipc_tx_message(sdev->ipc,
					 connect->hdr.cmd,
					 connect, माप(*connect),
					 &reply, माप(reply));
		अगर (ret < 0) अणु
			dev_err(dev,
				"error: failed to load route sink %s control %s source %s\n",
				sroute->route->sink,
				sroute->route->control ? sroute->route->control
					: "none",
				sroute->route->source);

			वापस ret;
		पूर्ण
	पूर्ण

	/* restore dai links */
	list_क्रम_each_entry_reverse(dai, &sdev->dai_list, list) अणु
		काष्ठा sof_ipc_reply reply;
		काष्ठा sof_ipc_dai_config *config = &dai->dai_config[dai->current_config];

		अगर (!config) अणु
			dev_err(dev, "error: no config for DAI %s\n",
				dai->name);
			जारी;
		पूर्ण

		/*
		 * The link DMA channel would be invalidated क्रम running
		 * streams but not क्रम streams that were in the PAUSED
		 * state during suspend. So invalidate it here beक्रमe setting
		 * the dai config in the DSP.
		 */
		अगर (config->type == SOF_DAI_INTEL_HDA)
			config->hda.link_dma_ch = DMA_CHAN_INVALID;

		ret = sof_ipc_tx_message(sdev->ipc,
					 config->hdr.cmd, config,
					 config->hdr.size,
					 &reply, माप(reply));

		अगर (ret < 0) अणु
			dev_err(dev,
				"error: failed to set dai config for %s\n",
				dai->name);

			वापस ret;
		पूर्ण
	पूर्ण

	/* complete pipeline */
	list_क्रम_each_entry(swidget, &sdev->widget_list, list) अणु
		चयन (swidget->id) अणु
		हाल snd_soc_dapm_scheduler:
			swidget->complete =
				snd_sof_complete_pipeline(dev, swidget);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* restore pipeline kcontrols */
	ret = sof_restore_kcontrols(dev);
	अगर (ret < 0)
		dev_err(dev,
			"error: restoring kcontrols after resume\n");

	वापस ret;
पूर्ण

/*
 * Generic object lookup APIs.
 */

काष्ठा snd_sof_pcm *snd_sof_find_spcm_name(काष्ठा snd_soc_component *scomp,
					   स्थिर अक्षर *name)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_sof_pcm *spcm;

	list_क्रम_each_entry(spcm, &sdev->pcm_list, list) अणु
		/* match with PCM dai name */
		अगर (म_भेद(spcm->pcm.dai_name, name) == 0)
			वापस spcm;

		/* match with playback caps name अगर set */
		अगर (*spcm->pcm.caps[0].name &&
		    !म_भेद(spcm->pcm.caps[0].name, name))
			वापस spcm;

		/* match with capture caps name अगर set */
		अगर (*spcm->pcm.caps[1].name &&
		    !म_भेद(spcm->pcm.caps[1].name, name))
			वापस spcm;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा snd_sof_pcm *snd_sof_find_spcm_comp(काष्ठा snd_soc_component *scomp,
					   अचिन्हित पूर्णांक comp_id,
					   पूर्णांक *direction)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_sof_pcm *spcm;
	पूर्णांक dir;

	list_क्रम_each_entry(spcm, &sdev->pcm_list, list) अणु
		क्रम_each_pcm_streams(dir) अणु
			अगर (spcm->stream[dir].comp_id == comp_id) अणु
				*direction = dir;
				वापस spcm;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा snd_sof_pcm *snd_sof_find_spcm_pcm_id(काष्ठा snd_soc_component *scomp,
					     अचिन्हित पूर्णांक pcm_id)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_sof_pcm *spcm;

	list_क्रम_each_entry(spcm, &sdev->pcm_list, list) अणु
		अगर (le32_to_cpu(spcm->pcm.pcm_id) == pcm_id)
			वापस spcm;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा snd_sof_widget *snd_sof_find_swidget(काष्ठा snd_soc_component *scomp,
					    स्थिर अक्षर *name)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_sof_widget *swidget;

	list_क्रम_each_entry(swidget, &sdev->widget_list, list) अणु
		अगर (म_भेद(name, swidget->widget->name) == 0)
			वापस swidget;
	पूर्ण

	वापस शून्य;
पूर्ण

/* find widget by stream name and direction */
काष्ठा snd_sof_widget *
snd_sof_find_swidget_sname(काष्ठा snd_soc_component *scomp,
			   स्थिर अक्षर *pcm_name, पूर्णांक dir)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_sof_widget *swidget;
	क्रमागत snd_soc_dapm_type type;

	अगर (dir == SNDRV_PCM_STREAM_PLAYBACK)
		type = snd_soc_dapm_aअगर_in;
	अन्यथा
		type = snd_soc_dapm_aअगर_out;

	list_क्रम_each_entry(swidget, &sdev->widget_list, list) अणु
		अगर (!म_भेद(pcm_name, swidget->widget->sname) &&
		    swidget->id == type)
			वापस swidget;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा snd_sof_dai *snd_sof_find_dai(काष्ठा snd_soc_component *scomp,
				     स्थिर अक्षर *name)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_sof_dai *dai;

	list_क्रम_each_entry(dai, &sdev->dai_list, list) अणु
		अगर (dai->name && (म_भेद(name, dai->name) == 0))
			वापस dai;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Helper to get SSP MCLK from a pcm_runसमय.
 * Return 0 अगर not exist.
 */
पूर्णांक sof_dai_get_mclk(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, SOF_AUDIO_PCM_DRV_NAME);
	काष्ठा snd_sof_dai *dai =
		snd_sof_find_dai(component, (अक्षर *)rtd->dai_link->name);

	/* use the tplg configured mclk अगर existed */
	अगर (!dai || !dai->dai_config)
		वापस 0;

	चयन (dai->dai_config->type) अणु
	हाल SOF_DAI_INTEL_SSP:
		वापस dai->dai_config->ssp.mclk_rate;
	शेष:
		/* not yet implemented क्रम platक्रमms other than the above */
		dev_err(rtd->dev, "mclk for dai_config->type %d not supported yet!\n",
			dai->dai_config->type);
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sof_dai_get_mclk);

/*
 * SOF Driver क्रमागतeration.
 */
पूर्णांक sof_machine_check(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *sof_pdata = sdev->pdata;
	स्थिर काष्ठा sof_dev_desc *desc = sof_pdata->desc;
	काष्ठा snd_soc_acpi_mach *mach;

	अगर (!IS_ENABLED(CONFIG_SND_SOC_SOF_FORCE_NOCODEC_MODE)) अणु

		/* find machine */
		snd_sof_machine_select(sdev);
		अगर (sof_pdata->machine) अणु
			snd_sof_set_mach_params(sof_pdata->machine, sdev);
			वापस 0;
		पूर्ण

		अगर (!IS_ENABLED(CONFIG_SND_SOC_SOF_NOCODEC)) अणु
			dev_err(sdev->dev, "error: no matching ASoC machine driver found - aborting probe\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(sdev->dev, "Force to use nocodec mode\n");
	पूर्ण

	/* select nocodec mode */
	dev_warn(sdev->dev, "Using nocodec machine driver\n");
	mach = devm_kzalloc(sdev->dev, माप(*mach), GFP_KERNEL);
	अगर (!mach)
		वापस -ENOMEM;

	mach->drv_name = "sof-nocodec";
	sof_pdata->tplg_filename = desc->nocodec_tplg_filename;

	sof_pdata->machine = mach;
	snd_sof_set_mach_params(sof_pdata->machine, sdev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sof_machine_check);

पूर्णांक sof_machine_रेजिस्टर(काष्ठा snd_sof_dev *sdev, व्योम *pdata)
अणु
	काष्ठा snd_sof_pdata *plat_data = pdata;
	स्थिर अक्षर *drv_name;
	स्थिर व्योम *mach;
	पूर्णांक size;

	drv_name = plat_data->machine->drv_name;
	mach = plat_data->machine;
	size = माप(*plat_data->machine);

	/* रेजिस्टर machine driver, pass machine info as pdata */
	plat_data->pdev_mach =
		platक्रमm_device_रेजिस्टर_data(sdev->dev, drv_name,
					      PLATFORM_DEVID_NONE, mach, size);
	अगर (IS_ERR(plat_data->pdev_mach))
		वापस PTR_ERR(plat_data->pdev_mach);

	dev_dbg(sdev->dev, "created machine %s\n",
		dev_name(&plat_data->pdev_mach->dev));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sof_machine_रेजिस्टर);

व्योम sof_machine_unरेजिस्टर(काष्ठा snd_sof_dev *sdev, व्योम *pdata)
अणु
	काष्ठा snd_sof_pdata *plat_data = pdata;

	अगर (!IS_ERR_OR_शून्य(plat_data->pdev_mach))
		platक्रमm_device_unरेजिस्टर(plat_data->pdev_mach);
पूर्ण
EXPORT_SYMBOL(sof_machine_unरेजिस्टर);
