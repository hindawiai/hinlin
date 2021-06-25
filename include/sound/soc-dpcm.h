<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * linux/sound/soc-dpcm.h -- ALSA SoC Dynamic PCM Support
 *
 * Author:		Liam Girdwood <lrg@ti.com>
 */

#अगर_अघोषित __LINUX_SND_SOC_DPCM_H
#घोषणा __LINUX_SND_SOC_DPCM_H

#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <sound/pcm.h>

काष्ठा snd_soc_pcm_runसमय;

/*
 * Types of runसमय_update to perक्रमm. e.g. originated from FE PCM ops
 * or audio route changes triggered by muxes/mixers.
 */
क्रमागत snd_soc_dpcm_update अणु
	SND_SOC_DPCM_UPDATE_NO	= 0,
	SND_SOC_DPCM_UPDATE_BE,
	SND_SOC_DPCM_UPDATE_FE,
पूर्ण;

/*
 * Dynamic PCM Frontend -> Backend link management states.
 */
क्रमागत snd_soc_dpcm_link_state अणु
	SND_SOC_DPCM_LINK_STATE_NEW	= 0,	/* newly created link */
	SND_SOC_DPCM_LINK_STATE_FREE,		/* link to be dismantled */
पूर्ण;

/*
 * Dynamic PCM Frontend -> Backend link PCM states.
 */
क्रमागत snd_soc_dpcm_state अणु
	SND_SOC_DPCM_STATE_NEW	= 0,
	SND_SOC_DPCM_STATE_OPEN,
	SND_SOC_DPCM_STATE_HW_PARAMS,
	SND_SOC_DPCM_STATE_PREPARE,
	SND_SOC_DPCM_STATE_START,
	SND_SOC_DPCM_STATE_STOP,
	SND_SOC_DPCM_STATE_PAUSED,
	SND_SOC_DPCM_STATE_SUSPEND,
	SND_SOC_DPCM_STATE_HW_FREE,
	SND_SOC_DPCM_STATE_CLOSE,
पूर्ण;

/*
 * Dynamic PCM trigger ordering. Triggering flexibility is required as some
 * DSPs require triggering beक्रमe/after their CPU platक्रमm and DAIs.
 *
 * i.e. some clients may want to manually order this call in their PCM
 * trigger() whilst others will just use the regular core ordering.
 */
क्रमागत snd_soc_dpcm_trigger अणु
	SND_SOC_DPCM_TRIGGER_PRE		= 0,
	SND_SOC_DPCM_TRIGGER_POST,
	SND_SOC_DPCM_TRIGGER_BESPOKE,
पूर्ण;

/*
 * Dynamic PCM link
 * This links together a FE and BE DAI at runसमय and stores the link
 * state inक्रमmation and the hw_params configuration.
 */
काष्ठा snd_soc_dpcm अणु
	/* FE and BE DAIs*/
	काष्ठा snd_soc_pcm_runसमय *be;
	काष्ठा snd_soc_pcm_runसमय *fe;

	/* link state */
	क्रमागत snd_soc_dpcm_link_state state;

	/* list of BE and FE क्रम this DPCM link */
	काष्ठा list_head list_be;
	काष्ठा list_head list_fe;

	/* hw params क्रम this link - may be dअगरferent क्रम each link */
	काष्ठा snd_pcm_hw_params hw_params;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_state;
#पूर्ण_अगर
पूर्ण;

/*
 * Dynamic PCM runसमय data.
 */
काष्ठा snd_soc_dpcm_runसमय अणु
	काष्ठा list_head be_clients;
	काष्ठा list_head fe_clients;

	पूर्णांक users;
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा snd_pcm_hw_params hw_params;

	/* state and update */
	क्रमागत snd_soc_dpcm_update runसमय_update;
	क्रमागत snd_soc_dpcm_state state;

	पूर्णांक trigger_pending; /* trigger cmd + 1 अगर pending, 0 अगर not */
पूर्ण;

#घोषणा क्रम_each_dpcm_fe(be, stream, _dpcm)				\
	list_क्रम_each_entry(_dpcm, &(be)->dpcm[stream].fe_clients, list_fe)

#घोषणा क्रम_each_dpcm_be(fe, stream, _dpcm)				\
	list_क्रम_each_entry(_dpcm, &(fe)->dpcm[stream].be_clients, list_be)
#घोषणा क्रम_each_dpcm_be_safe(fe, stream, _dpcm, __dpcm)			\
	list_क्रम_each_entry_safe(_dpcm, __dpcm, &(fe)->dpcm[stream].be_clients, list_be)
#घोषणा क्रम_each_dpcm_be_rollback(fe, stream, _dpcm)			\
	list_क्रम_each_entry_जारी_reverse(_dpcm, &(fe)->dpcm[stream].be_clients, list_be)

/* can this BE stop and मुक्त */
पूर्णांक snd_soc_dpcm_can_be_मुक्त_stop(काष्ठा snd_soc_pcm_runसमय *fe,
		काष्ठा snd_soc_pcm_runसमय *be, पूर्णांक stream);

/* can this BE perक्रमm a hw_params() */
पूर्णांक snd_soc_dpcm_can_be_params(काष्ठा snd_soc_pcm_runसमय *fe,
		काष्ठा snd_soc_pcm_runसमय *be, पूर्णांक stream);

/* is the current PCM operation क्रम this FE ? */
पूर्णांक snd_soc_dpcm_fe_can_update(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream);

/* is the current PCM operation क्रम this BE ? */
पूर्णांक snd_soc_dpcm_be_can_update(काष्ठा snd_soc_pcm_runसमय *fe,
		काष्ठा snd_soc_pcm_runसमय *be, पूर्णांक stream);

/* get the substream क्रम this BE */
काष्ठा snd_pcm_substream *
	snd_soc_dpcm_get_substream(काष्ठा snd_soc_pcm_runसमय *be, पूर्णांक stream);

/* update audio routing between PCMs and any DAI links */
पूर्णांक snd_soc_dpcm_runसमय_update(काष्ठा snd_soc_card *card);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम soc_dpcm_debugfs_add(काष्ठा snd_soc_pcm_runसमय *rtd);
#अन्यथा
अटल अंतरभूत व्योम soc_dpcm_debugfs_add(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक dpcm_path_get(काष्ठा snd_soc_pcm_runसमय *fe,
	पूर्णांक stream, काष्ठा snd_soc_dapm_widget_list **list_);
व्योम dpcm_path_put(काष्ठा snd_soc_dapm_widget_list **list);
पूर्णांक dpcm_process_paths(काष्ठा snd_soc_pcm_runसमय *fe,
	पूर्णांक stream, काष्ठा snd_soc_dapm_widget_list **list, पूर्णांक new);
पूर्णांक dpcm_be_dai_startup(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream);
व्योम dpcm_be_dai_stop(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream,
		      पूर्णांक करो_hw_मुक्त, काष्ठा snd_soc_dpcm *last);
व्योम dpcm_be_disconnect(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream);
व्योम dpcm_clear_pending_state(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream);
व्योम dpcm_be_dai_hw_मुक्त(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream);
पूर्णांक dpcm_be_dai_hw_params(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक tream);
पूर्णांक dpcm_be_dai_trigger(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream, पूर्णांक cmd);
पूर्णांक dpcm_be_dai_prepare(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream);
पूर्णांक dpcm_dapm_stream_event(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक dir,
	पूर्णांक event);

#घोषणा dpcm_be_dai_startup_rollback(fe, stream, last)	\
						dpcm_be_dai_stop(fe, stream, 0, last)
#घोषणा dpcm_be_dai_startup_unwind(fe, stream)	dpcm_be_dai_stop(fe, stream, 0, शून्य)
#घोषणा dpcm_be_dai_shutकरोwn(fe, stream)	dpcm_be_dai_stop(fe, stream, 1, शून्य)

#पूर्ण_अगर
