<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * pcm_local.h - a local header file क्रम snd-pcm module.
 *
 * Copyright (c) Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#अगर_अघोषित __SOUND_CORE_PCM_LOCAL_H
#घोषणा __SOUND_CORE_PCM_LOCAL_H

बाह्य स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list snd_pcm_known_rates;

व्योम snd_पूर्णांकerval_mul(स्थिर काष्ठा snd_पूर्णांकerval *a,
		      स्थिर काष्ठा snd_पूर्णांकerval *b, काष्ठा snd_पूर्णांकerval *c);
व्योम snd_पूर्णांकerval_भाग(स्थिर काष्ठा snd_पूर्णांकerval *a,
		      स्थिर काष्ठा snd_पूर्णांकerval *b, काष्ठा snd_पूर्णांकerval *c);
व्योम snd_पूर्णांकerval_muद_भागk(स्थिर काष्ठा snd_पूर्णांकerval *a,
			  स्थिर काष्ठा snd_पूर्णांकerval *b,
			  अचिन्हित पूर्णांक k, काष्ठा snd_पूर्णांकerval *c);
व्योम snd_पूर्णांकerval_mulkभाग(स्थिर काष्ठा snd_पूर्णांकerval *a, अचिन्हित पूर्णांक k,
			  स्थिर काष्ठा snd_पूर्णांकerval *b, काष्ठा snd_पूर्णांकerval *c);

पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_mask(काष्ठा snd_pcm_runसमय *runसमय,
			       snd_pcm_hw_param_t var, u_पूर्णांक32_t mask);

पूर्णांक pcm_lib_apply_appl_ptr(काष्ठा snd_pcm_substream *substream,
			   snd_pcm_uframes_t appl_ptr);
पूर्णांक snd_pcm_update_state(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_runसमय *runसमय);
पूर्णांक snd_pcm_update_hw_ptr(काष्ठा snd_pcm_substream *substream);

व्योम snd_pcm_playback_silence(काष्ठा snd_pcm_substream *substream,
			      snd_pcm_uframes_t new_hw_ptr);

अटल अंतरभूत snd_pcm_uframes_t
snd_pcm_avail(काष्ठा snd_pcm_substream *substream)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस snd_pcm_playback_avail(substream->runसमय);
	अन्यथा
		वापस snd_pcm_capture_avail(substream->runसमय);
पूर्ण

अटल अंतरभूत snd_pcm_uframes_t
snd_pcm_hw_avail(काष्ठा snd_pcm_substream *substream)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस snd_pcm_playback_hw_avail(substream->runसमय);
	अन्यथा
		वापस snd_pcm_capture_hw_avail(substream->runसमय);
पूर्ण

#अगर_घोषित CONFIG_SND_PCM_TIMER
व्योम snd_pcm_समयr_resolution_change(काष्ठा snd_pcm_substream *substream);
व्योम snd_pcm_समयr_init(काष्ठा snd_pcm_substream *substream);
व्योम snd_pcm_समयr_करोne(काष्ठा snd_pcm_substream *substream);
#अन्यथा
अटल अंतरभूत व्योम
snd_pcm_समयr_resolution_change(काष्ठा snd_pcm_substream *substream) अणुपूर्ण
अटल अंतरभूत व्योम snd_pcm_समयr_init(काष्ठा snd_pcm_substream *substream) अणुपूर्ण
अटल अंतरभूत व्योम snd_pcm_समयr_करोne(काष्ठा snd_pcm_substream *substream) अणुपूर्ण
#पूर्ण_अगर

व्योम __snd_pcm_xrun(काष्ठा snd_pcm_substream *substream);
व्योम snd_pcm_group_init(काष्ठा snd_pcm_group *group);
व्योम snd_pcm_sync_stop(काष्ठा snd_pcm_substream *substream, bool sync_irq);

#अगर_घोषित CONFIG_SND_DMA_SGBUF
काष्ठा page *snd_pcm_sgbuf_ops_page(काष्ठा snd_pcm_substream *substream,
				    अचिन्हित दीर्घ offset);
#पूर्ण_अगर

#घोषणा PCM_RUNTIME_CHECK(sub) snd_BUG_ON(!(sub) || !(sub)->runसमय)

/* loop over all PCM substreams */
#घोषणा क्रम_each_pcm_substream(pcm, str, subs) \
	क्रम ((str) = 0; (str) < 2; (str)++) \
		क्रम ((subs) = (pcm)->streams[str].substream; (subs); \
		     (subs) = (subs)->next)

#पूर्ण_अगर	/* __SOUND_CORE_PCM_LOCAL_H */
