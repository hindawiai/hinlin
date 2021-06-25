<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_PCM_OSS_H
#घोषणा __SOUND_PCM_OSS_H

/*
 *  Digital Audio (PCM) - OSS compatibility असलtract layer
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

काष्ठा snd_pcm_oss_setup अणु
	अक्षर *task_name;
	अचिन्हित पूर्णांक disable:1,
		     direct:1,
		     block:1,
		     nonblock:1,
		     partialfrag:1,
		     nosilence:1,
		     buggyptr:1;
	अचिन्हित पूर्णांक periods;
	अचिन्हित पूर्णांक period_size;
	काष्ठा snd_pcm_oss_setup *next;
पूर्ण;

काष्ठा snd_pcm_oss_runसमय अणु
	अचिन्हित params: 1,			/* क्रमmat/parameter change */
		 prepare: 1,			/* need to prepare the operation */
		 trigger: 1,			/* trigger flag */
		 sync_trigger: 1;		/* sync trigger flag */
	पूर्णांक rate;				/* requested rate */
	पूर्णांक क्रमmat;				/* requested OSS क्रमmat */
	अचिन्हित पूर्णांक channels;			/* requested channels */
	अचिन्हित पूर्णांक fragshअगरt;
	अचिन्हित पूर्णांक maxfrags;
	अचिन्हित पूर्णांक subभागision;		/* requested subभागision */
	माप_प्रकार period_bytes;			/* requested period size */
	माप_प्रकार period_frames;			/* period frames क्रम poll */
	माप_प्रकार period_ptr;			/* actual ग_लिखो poपूर्णांकer to period */
	अचिन्हित पूर्णांक periods;
	माप_प्रकार buffer_bytes;			/* requested buffer size */
	माप_प्रकार bytes;				/* total # bytes processed */
	माप_प्रकार mmap_bytes;
	अक्षर *buffer;				/* vदो_स्मृतिated period */
	माप_प्रकार buffer_used;			/* used length from period buffer */
	काष्ठा mutex params_lock;
	atomic_t rw_ref;		/* concurrent पढ़ो/ग_लिखो accesses */
#अगर_घोषित CONFIG_SND_PCM_OSS_PLUGINS
	काष्ठा snd_pcm_plugin *plugin_first;
	काष्ठा snd_pcm_plugin *plugin_last;
#पूर्ण_अगर
	अचिन्हित पूर्णांक prev_hw_ptr_period;
पूर्ण;

काष्ठा snd_pcm_oss_file अणु
	काष्ठा snd_pcm_substream *streams[2];
पूर्ण;

काष्ठा snd_pcm_oss_substream अणु
	अचिन्हित oss: 1;			/* oss mode */
	काष्ठा snd_pcm_oss_setup setup;		/* active setup */
पूर्ण;

काष्ठा snd_pcm_oss_stream अणु
	काष्ठा snd_pcm_oss_setup *setup_list;	/* setup list */
	काष्ठा mutex setup_mutex;
#अगर_घोषित CONFIG_SND_VERBOSE_PROCFS
	काष्ठा snd_info_entry *proc_entry;
#पूर्ण_अगर
पूर्ण;

काष्ठा snd_pcm_oss अणु
	पूर्णांक reg;
	अचिन्हित पूर्णांक reg_mask;
पूर्ण;

#पूर्ण_अगर /* __SOUND_PCM_OSS_H */
