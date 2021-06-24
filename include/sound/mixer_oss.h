<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_MIXER_OSS_H
#घोषणा __SOUND_MIXER_OSS_H

/*
 *  OSS MIXER API
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#अगर IS_ENABLED(CONFIG_SND_MIXER_OSS)

#घोषणा SNDRV_OSS_MAX_MIXERS	32

काष्ठा snd_mixer_oss_file;

काष्ठा snd_mixer_oss_slot अणु
	पूर्णांक number;
	अचिन्हित पूर्णांक stereo: 1;
	पूर्णांक (*get_volume)(काष्ठा snd_mixer_oss_file *fmixer,
			  काष्ठा snd_mixer_oss_slot *chn,
			  पूर्णांक *left, पूर्णांक *right);
	पूर्णांक (*put_volume)(काष्ठा snd_mixer_oss_file *fmixer,
			  काष्ठा snd_mixer_oss_slot *chn,
			  पूर्णांक left, पूर्णांक right);
	पूर्णांक (*get_recsrc)(काष्ठा snd_mixer_oss_file *fmixer,
			  काष्ठा snd_mixer_oss_slot *chn,
			  पूर्णांक *active);
	पूर्णांक (*put_recsrc)(काष्ठा snd_mixer_oss_file *fmixer,
			  काष्ठा snd_mixer_oss_slot *chn,
			  पूर्णांक active);
	अचिन्हित दीर्घ निजी_value;
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा snd_mixer_oss_slot *slot);
	पूर्णांक volume[2];
पूर्ण;

काष्ठा snd_mixer_oss अणु
	काष्ठा snd_card *card;
	अक्षर id[16];
	अक्षर name[32];
	काष्ठा snd_mixer_oss_slot slots[SNDRV_OSS_MAX_MIXERS]; /* OSS mixer slots */
	अचिन्हित पूर्णांक mask_recsrc;		/* exclusive recsrc mask */
	पूर्णांक (*get_recsrc)(काष्ठा snd_mixer_oss_file *fmixer,
			  अचिन्हित पूर्णांक *active_index);
	पूर्णांक (*put_recsrc)(काष्ठा snd_mixer_oss_file *fmixer,
			  अचिन्हित पूर्णांक active_index);
	व्योम *निजी_data_recsrc;
	व्योम (*निजी_मुक्त_recsrc)(काष्ठा snd_mixer_oss *mixer);
	काष्ठा mutex reg_mutex;
	काष्ठा snd_info_entry *proc_entry;
	पूर्णांक oss_dev_alloc;
	/* --- */
	पूर्णांक oss_recsrc;
पूर्ण;

काष्ठा snd_mixer_oss_file अणु
	काष्ठा snd_card *card;
	काष्ठा snd_mixer_oss *mixer;
पूर्ण;

पूर्णांक snd_mixer_oss_ioctl_card(काष्ठा snd_card *card,
			     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

#पूर्ण_अगर /* CONFIG_SND_MIXER_OSS */

#पूर्ण_अगर /* __SOUND_MIXER_OSS_H */
