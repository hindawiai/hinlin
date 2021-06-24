<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// soc-link.c
//
// Copyright (C) 2019 Renesas Electronics Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
//
#समावेश <sound/soc.h>
#समावेश <sound/soc-link.h>

#घोषणा soc_link_ret(rtd, ret) _soc_link_ret(rtd, __func__, ret)
अटल अंतरभूत पूर्णांक _soc_link_ret(काष्ठा snd_soc_pcm_runसमय *rtd,
				स्थिर अक्षर *func, पूर्णांक ret)
अणु
	/* Positive, Zero values are not errors */
	अगर (ret >= 0)
		वापस ret;

	/* Negative values might be errors */
	चयन (ret) अणु
	हाल -EPROBE_DEFER:
	हाल -ENOTSUPP:
		अवरोध;
	शेष:
		dev_err(rtd->dev,
			"ASoC: error at %s on %s: %d\n",
			func, rtd->dai_link->name, ret);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * We might want to check substream by using list.
 * In such हाल, we can update these macros.
 */
#घोषणा soc_link_mark_push(rtd, substream, tgt)		((rtd)->mark_##tgt = substream)
#घोषणा soc_link_mark_pop(rtd, substream, tgt)		((rtd)->mark_##tgt = शून्य)
#घोषणा soc_link_mark_match(rtd, substream, tgt)	((rtd)->mark_##tgt == substream)

पूर्णांक snd_soc_link_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret = 0;

	अगर (rtd->dai_link->init)
		ret = rtd->dai_link->init(rtd);

	वापस soc_link_ret(rtd, ret);
पूर्ण

व्योम snd_soc_link_निकास(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	अगर (rtd->dai_link->निकास)
		rtd->dai_link->निकास(rtd);
पूर्ण

पूर्णांक snd_soc_link_be_hw_params_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
				    काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक ret = 0;

	अगर (rtd->dai_link->be_hw_params_fixup)
		ret = rtd->dai_link->be_hw_params_fixup(rtd, params);

	वापस soc_link_ret(rtd, ret);
पूर्ण

पूर्णांक snd_soc_link_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक ret = 0;

	अगर (rtd->dai_link->ops &&
	    rtd->dai_link->ops->startup)
		ret = rtd->dai_link->ops->startup(substream);

	/* mark substream अगर succeeded */
	अगर (ret == 0)
		soc_link_mark_push(rtd, substream, startup);

	वापस soc_link_ret(rtd, ret);
पूर्ण

व्योम snd_soc_link_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			   पूर्णांक rollback)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	अगर (rollback && !soc_link_mark_match(rtd, substream, startup))
		वापस;

	अगर (rtd->dai_link->ops &&
	    rtd->dai_link->ops->shutकरोwn)
		rtd->dai_link->ops->shutकरोwn(substream);

	/* हटाओ marked substream */
	soc_link_mark_pop(rtd, substream, startup);
पूर्ण

पूर्णांक snd_soc_link_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक ret = 0;

	अगर (rtd->dai_link->ops &&
	    rtd->dai_link->ops->prepare)
		ret = rtd->dai_link->ops->prepare(substream);

	वापस soc_link_ret(rtd, ret);
पूर्ण

पूर्णांक snd_soc_link_hw_params(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक ret = 0;

	अगर (rtd->dai_link->ops &&
	    rtd->dai_link->ops->hw_params)
		ret = rtd->dai_link->ops->hw_params(substream, params);

	/* mark substream अगर succeeded */
	अगर (ret == 0)
		soc_link_mark_push(rtd, substream, hw_params);

	वापस soc_link_ret(rtd, ret);
पूर्ण

व्योम snd_soc_link_hw_मुक्त(काष्ठा snd_pcm_substream *substream, पूर्णांक rollback)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	अगर (rollback && !soc_link_mark_match(rtd, substream, hw_params))
		वापस;

	अगर (rtd->dai_link->ops &&
	    rtd->dai_link->ops->hw_मुक्त)
		rtd->dai_link->ops->hw_मुक्त(substream);

	/* हटाओ marked substream */
	soc_link_mark_pop(rtd, substream, hw_params);
पूर्ण

अटल पूर्णांक soc_link_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक ret = 0;

	अगर (rtd->dai_link->ops &&
	    rtd->dai_link->ops->trigger)
		ret = rtd->dai_link->ops->trigger(substream, cmd);

	वापस soc_link_ret(rtd, ret);
पूर्ण

पूर्णांक snd_soc_link_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			 पूर्णांक rollback)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = soc_link_trigger(substream, cmd);
		अगर (ret < 0)
			अवरोध;
		soc_link_mark_push(rtd, substream, trigger);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (rollback && !soc_link_mark_match(rtd, substream, trigger))
			अवरोध;

		ret = soc_link_trigger(substream, cmd);
		soc_link_mark_pop(rtd, substream, startup);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक snd_soc_link_compr_startup(काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	पूर्णांक ret = 0;

	अगर (rtd->dai_link->compr_ops &&
	    rtd->dai_link->compr_ops->startup)
		ret = rtd->dai_link->compr_ops->startup(cstream);

	अगर (ret == 0)
		soc_link_mark_push(rtd, cstream, compr_startup);

	वापस soc_link_ret(rtd, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_link_compr_startup);

व्योम snd_soc_link_compr_shutकरोwn(काष्ठा snd_compr_stream *cstream,
				 पूर्णांक rollback)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;

	अगर (rollback && !soc_link_mark_match(rtd, cstream, compr_startup))
		वापस;

	अगर (rtd->dai_link->compr_ops &&
	    rtd->dai_link->compr_ops->shutकरोwn)
		rtd->dai_link->compr_ops->shutकरोwn(cstream);

	soc_link_mark_pop(rtd, cstream, compr_startup);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_link_compr_shutकरोwn);

पूर्णांक snd_soc_link_compr_set_params(काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	पूर्णांक ret = 0;

	अगर (rtd->dai_link->compr_ops &&
	    rtd->dai_link->compr_ops->set_params)
		ret = rtd->dai_link->compr_ops->set_params(cstream);

	वापस soc_link_ret(rtd, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_link_compr_set_params);
