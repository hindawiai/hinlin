<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_SOUNDFONT_H
#घोषणा __SOUND_SOUNDFONT_H

/*
 *  Soundfont defines and definitions.
 *
 *  Copyright (C) 1999 Steve Ratclअगरfe
 *  Copyright (c) 1999-2000 Takashi iwai <tiwai@suse.de>
 */

#समावेश <sound/sfnt_info.h>
#समावेश <sound/util_स्मृति.स>

#घोषणा SF_MAX_INSTRUMENTS	128	/* maximum instrument number */
#घोषणा SF_MAX_PRESETS  256	/* drums are mapped from 128 to 256 */
#घोषणा SF_IS_DRUM_BANK(z) ((z) == 128)

काष्ठा snd_sf_zone अणु
	काष्ठा snd_sf_zone *next;	/* Link to next */
	अचिन्हित अक्षर bank;		/* Midi bank क्रम this zone */
	अचिन्हित अक्षर instr;		/* Midi program क्रम this zone */
	अचिन्हित अक्षर mapped;		/* True अगर mapped to something अन्यथा */

	काष्ठा soundfont_voice_info v;	/* All the soundfont parameters */
	पूर्णांक counter;
	काष्ठा snd_sf_sample *sample;	/* Link to sample */

	/* The following deals with preset numbers (programs) */
	काष्ठा snd_sf_zone *next_instr;	/* Next zone of this instrument */
	काष्ठा snd_sf_zone *next_zone;	/* Next zone in play list */
पूर्ण;

काष्ठा snd_sf_sample अणु
	काष्ठा soundfont_sample_info v;
	पूर्णांक counter;
	काष्ठा snd_util_memblk *block;	/* allocated data block */
	काष्ठा snd_sf_sample *next;
पूर्ण;

/*
 * This represents all the inक्रमmation relating to a soundfont.
 */
काष्ठा snd_soundfont अणु
	काष्ठा snd_soundfont *next;	/* Link to next */
	/*काष्ठा snd_soundfont *prev;*/	/* Link to previous */
	लघु  id;		/* file id */
	लघु  type;		/* font type */
	अचिन्हित अक्षर name[SNDRV_SFNT_PATCH_NAME_LEN];	/* identअगरier */
	काष्ठा snd_sf_zone *zones; /* Font inक्रमmation */
	काष्ठा snd_sf_sample *samples; /* The sample headers */
पूर्ण;

/*
 * Type of the sample access callback
 */
काष्ठा snd_sf_callback अणु
	व्योम *निजी_data;
	पूर्णांक (*sample_new)(व्योम *निजी_data, काष्ठा snd_sf_sample *sp,
			  काष्ठा snd_util_memhdr *hdr,
			  स्थिर व्योम __user *buf, दीर्घ count);
	पूर्णांक (*sample_मुक्त)(व्योम *निजी_data, काष्ठा snd_sf_sample *sp,
			   काष्ठा snd_util_memhdr *hdr);
	व्योम (*sample_reset)(व्योम *निजी);
पूर्ण;

/*
 * List of soundfonts.
 */
काष्ठा snd_sf_list अणु
	काष्ठा snd_soundfont *currsf; /* The currently खोलो soundfont */
	पूर्णांक खोलो_client;	/* client poपूर्णांकer क्रम lock */
	पूर्णांक mem_used;		/* used memory size */
	काष्ठा snd_sf_zone *presets[SF_MAX_PRESETS];
	काष्ठा snd_soundfont *fonts; /* The list of soundfonts */
	पूर्णांक fonts_size;	/* number of fonts allocated */
	पूर्णांक zone_counter;	/* last allocated समय क्रम zone */
	पूर्णांक sample_counter;	/* last allocated समय क्रम sample */
	पूर्णांक zone_locked;	/* locked समय क्रम zone */
	पूर्णांक sample_locked;	/* locked समय क्रम sample */
	काष्ठा snd_sf_callback callback;	/* callback functions */
	पूर्णांक presets_locked;
	काष्ठा mutex presets_mutex;
	spinlock_t lock;
	काष्ठा snd_util_memhdr *memhdr;
पूर्ण;

/* Prototypes क्रम soundfont.c */
पूर्णांक snd_soundfont_load(काष्ठा snd_sf_list *sflist, स्थिर व्योम __user *data,
		       दीर्घ count, पूर्णांक client);
पूर्णांक snd_soundfont_load_guspatch(काष्ठा snd_sf_list *sflist, स्थिर अक्षर __user *data,
				दीर्घ count, पूर्णांक client);
पूर्णांक snd_soundfont_बंद_check(काष्ठा snd_sf_list *sflist, पूर्णांक client);

काष्ठा snd_sf_list *snd_sf_new(काष्ठा snd_sf_callback *callback,
			       काष्ठा snd_util_memhdr *hdr);
व्योम snd_sf_मुक्त(काष्ठा snd_sf_list *sflist);

पूर्णांक snd_soundfont_हटाओ_samples(काष्ठा snd_sf_list *sflist);
पूर्णांक snd_soundfont_हटाओ_unlocked(काष्ठा snd_sf_list *sflist);

पूर्णांक snd_soundfont_search_zone(काष्ठा snd_sf_list *sflist, पूर्णांक *notep, पूर्णांक vel,
			      पूर्णांक preset, पूर्णांक bank,
			      पूर्णांक def_preset, पूर्णांक def_bank,
			      काष्ठा snd_sf_zone **table, पूर्णांक max_layers);

/* Parameter conversions */
पूर्णांक snd_sf_calc_parm_hold(पूर्णांक msec);
पूर्णांक snd_sf_calc_parm_attack(पूर्णांक msec);
पूर्णांक snd_sf_calc_parm_decay(पूर्णांक msec);
#घोषणा snd_sf_calc_parm_delay(msec) (0x8000 - (msec) * 1000 / 725)
बाह्य पूर्णांक snd_sf_vol_table[128];
पूर्णांक snd_sf_linear_to_log(अचिन्हित पूर्णांक amount, पूर्णांक offset, पूर्णांक ratio);


#पूर्ण_अगर /* __SOUND_SOUNDFONT_H */
