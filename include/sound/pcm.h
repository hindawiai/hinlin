<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_PCM_H
#घोषणा __SOUND_PCM_H

/*
 *  Digital Audio (PCM) असलtract layer
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Abramo Bagnara <abramo@alsa-project.org>
 */

#समावेश <sound/asound.h>
#समावेश <sound/meदो_स्मृति.h>
#समावेश <sound/minors.h>
#समावेश <linux/poll.h>
#समावेश <linux/mm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/refcount.h>

#घोषणा snd_pcm_substream_chip(substream) ((substream)->निजी_data)
#घोषणा snd_pcm_chip(pcm) ((pcm)->निजी_data)

#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
#समावेश <sound/pcm_oss.h>
#पूर्ण_अगर

/*
 *  Hardware (lowlevel) section
 */

काष्ठा snd_pcm_hardware अणु
	अचिन्हित पूर्णांक info;		/* SNDRV_PCM_INFO_* */
	u64 क्रमmats;			/* SNDRV_PCM_FMTBIT_* */
	अचिन्हित पूर्णांक rates;		/* SNDRV_PCM_RATE_* */
	अचिन्हित पूर्णांक rate_min;		/* min rate */
	अचिन्हित पूर्णांक rate_max;		/* max rate */
	अचिन्हित पूर्णांक channels_min;	/* min channels */
	अचिन्हित पूर्णांक channels_max;	/* max channels */
	माप_प्रकार buffer_bytes_max;	/* max buffer size */
	माप_प्रकार period_bytes_min;	/* min period size */
	माप_प्रकार period_bytes_max;	/* max period size */
	अचिन्हित पूर्णांक periods_min;	/* min # of periods */
	अचिन्हित पूर्णांक periods_max;	/* max # of periods */
	माप_प्रकार fअगरo_size;		/* fअगरo size in bytes */
पूर्ण;

काष्ठा snd_pcm_status64;
काष्ठा snd_pcm_substream;

काष्ठा snd_pcm_audio_tstamp_config; /* definitions further करोwn */
काष्ठा snd_pcm_audio_tstamp_report;

काष्ठा snd_pcm_ops अणु
	पूर्णांक (*खोलो)(काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*बंद)(काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*ioctl)(काष्ठा snd_pcm_substream * substream,
		     अचिन्हित पूर्णांक cmd, व्योम *arg);
	पूर्णांक (*hw_params)(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *params);
	पूर्णांक (*hw_मुक्त)(काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*prepare)(काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*trigger)(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd);
	पूर्णांक (*sync_stop)(काष्ठा snd_pcm_substream *substream);
	snd_pcm_uframes_t (*poपूर्णांकer)(काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*get_समय_info)(काष्ठा snd_pcm_substream *substream,
			काष्ठा बारpec64 *प्रणाली_ts, काष्ठा बारpec64 *audio_ts,
			काष्ठा snd_pcm_audio_tstamp_config *audio_tstamp_config,
			काष्ठा snd_pcm_audio_tstamp_report *audio_tstamp_report);
	पूर्णांक (*fill_silence)(काष्ठा snd_pcm_substream *substream, पूर्णांक channel,
			    अचिन्हित दीर्घ pos, अचिन्हित दीर्घ bytes);
	पूर्णांक (*copy_user)(काष्ठा snd_pcm_substream *substream, पूर्णांक channel,
			 अचिन्हित दीर्घ pos, व्योम __user *buf,
			 अचिन्हित दीर्घ bytes);
	पूर्णांक (*copy_kernel)(काष्ठा snd_pcm_substream *substream, पूर्णांक channel,
			   अचिन्हित दीर्घ pos, व्योम *buf, अचिन्हित दीर्घ bytes);
	काष्ठा page *(*page)(काष्ठा snd_pcm_substream *substream,
			     अचिन्हित दीर्घ offset);
	पूर्णांक (*mmap)(काष्ठा snd_pcm_substream *substream, काष्ठा vm_area_काष्ठा *vma);
	पूर्णांक (*ack)(काष्ठा snd_pcm_substream *substream);
पूर्ण;

/*
 *
 */

#अगर defined(CONFIG_SND_DYNAMIC_MINORS)
#घोषणा SNDRV_PCM_DEVICES	(SNDRV_OS_MINORS-2)
#अन्यथा
#घोषणा SNDRV_PCM_DEVICES	8
#पूर्ण_अगर

#घोषणा SNDRV_PCM_IOCTL1_RESET		0
/* 1 is असलent slot. */
#घोषणा SNDRV_PCM_IOCTL1_CHANNEL_INFO	2
/* 3 is असलent slot. */
#घोषणा SNDRV_PCM_IOCTL1_FIFO_SIZE	4

#घोषणा SNDRV_PCM_TRIGGER_STOP		0
#घोषणा SNDRV_PCM_TRIGGER_START		1
#घोषणा SNDRV_PCM_TRIGGER_PAUSE_PUSH	3
#घोषणा SNDRV_PCM_TRIGGER_PAUSE_RELEASE	4
#घोषणा SNDRV_PCM_TRIGGER_SUSPEND	5
#घोषणा SNDRV_PCM_TRIGGER_RESUME	6
#घोषणा SNDRV_PCM_TRIGGER_DRAIN		7

#घोषणा SNDRV_PCM_POS_XRUN		((snd_pcm_uframes_t)-1)

/* If you change this करोn't क्रमget to change rates[] table in pcm_native.c */
#घोषणा SNDRV_PCM_RATE_5512		(1<<0)		/* 5512Hz */
#घोषणा SNDRV_PCM_RATE_8000		(1<<1)		/* 8000Hz */
#घोषणा SNDRV_PCM_RATE_11025		(1<<2)		/* 11025Hz */
#घोषणा SNDRV_PCM_RATE_16000		(1<<3)		/* 16000Hz */
#घोषणा SNDRV_PCM_RATE_22050		(1<<4)		/* 22050Hz */
#घोषणा SNDRV_PCM_RATE_32000		(1<<5)		/* 32000Hz */
#घोषणा SNDRV_PCM_RATE_44100		(1<<6)		/* 44100Hz */
#घोषणा SNDRV_PCM_RATE_48000		(1<<7)		/* 48000Hz */
#घोषणा SNDRV_PCM_RATE_64000		(1<<8)		/* 64000Hz */
#घोषणा SNDRV_PCM_RATE_88200		(1<<9)		/* 88200Hz */
#घोषणा SNDRV_PCM_RATE_96000		(1<<10)		/* 96000Hz */
#घोषणा SNDRV_PCM_RATE_176400		(1<<11)		/* 176400Hz */
#घोषणा SNDRV_PCM_RATE_192000		(1<<12)		/* 192000Hz */
#घोषणा SNDRV_PCM_RATE_352800		(1<<13)		/* 352800Hz */
#घोषणा SNDRV_PCM_RATE_384000		(1<<14)		/* 384000Hz */

#घोषणा SNDRV_PCM_RATE_CONTINUOUS	(1<<30)		/* continuous range */
#घोषणा SNDRV_PCM_RATE_KNOT		(1<<31)		/* supports more non-continuos rates */

#घोषणा SNDRV_PCM_RATE_8000_44100	(SNDRV_PCM_RATE_8000|SNDRV_PCM_RATE_11025|\
					 SNDRV_PCM_RATE_16000|SNDRV_PCM_RATE_22050|\
					 SNDRV_PCM_RATE_32000|SNDRV_PCM_RATE_44100)
#घोषणा SNDRV_PCM_RATE_8000_48000	(SNDRV_PCM_RATE_8000_44100|SNDRV_PCM_RATE_48000)
#घोषणा SNDRV_PCM_RATE_8000_96000	(SNDRV_PCM_RATE_8000_48000|SNDRV_PCM_RATE_64000|\
					 SNDRV_PCM_RATE_88200|SNDRV_PCM_RATE_96000)
#घोषणा SNDRV_PCM_RATE_8000_192000	(SNDRV_PCM_RATE_8000_96000|SNDRV_PCM_RATE_176400|\
					 SNDRV_PCM_RATE_192000)
#घोषणा SNDRV_PCM_RATE_8000_384000	(SNDRV_PCM_RATE_8000_192000|\
					 SNDRV_PCM_RATE_352800|\
					 SNDRV_PCM_RATE_384000)
#घोषणा _SNDRV_PCM_FMTBIT(fmt)		(1ULL << (__क्रमce पूर्णांक)SNDRV_PCM_FORMAT_##fmt)
#घोषणा SNDRV_PCM_FMTBIT_S8		_SNDRV_PCM_FMTBIT(S8)
#घोषणा SNDRV_PCM_FMTBIT_U8		_SNDRV_PCM_FMTBIT(U8)
#घोषणा SNDRV_PCM_FMTBIT_S16_LE		_SNDRV_PCM_FMTBIT(S16_LE)
#घोषणा SNDRV_PCM_FMTBIT_S16_BE		_SNDRV_PCM_FMTBIT(S16_BE)
#घोषणा SNDRV_PCM_FMTBIT_U16_LE		_SNDRV_PCM_FMTBIT(U16_LE)
#घोषणा SNDRV_PCM_FMTBIT_U16_BE		_SNDRV_PCM_FMTBIT(U16_BE)
#घोषणा SNDRV_PCM_FMTBIT_S24_LE		_SNDRV_PCM_FMTBIT(S24_LE)
#घोषणा SNDRV_PCM_FMTBIT_S24_BE		_SNDRV_PCM_FMTBIT(S24_BE)
#घोषणा SNDRV_PCM_FMTBIT_U24_LE		_SNDRV_PCM_FMTBIT(U24_LE)
#घोषणा SNDRV_PCM_FMTBIT_U24_BE		_SNDRV_PCM_FMTBIT(U24_BE)
#घोषणा SNDRV_PCM_FMTBIT_S32_LE		_SNDRV_PCM_FMTBIT(S32_LE)
#घोषणा SNDRV_PCM_FMTBIT_S32_BE		_SNDRV_PCM_FMTBIT(S32_BE)
#घोषणा SNDRV_PCM_FMTBIT_U32_LE		_SNDRV_PCM_FMTBIT(U32_LE)
#घोषणा SNDRV_PCM_FMTBIT_U32_BE		_SNDRV_PCM_FMTBIT(U32_BE)
#घोषणा SNDRV_PCM_FMTBIT_FLOAT_LE	_SNDRV_PCM_FMTBIT(FLOAT_LE)
#घोषणा SNDRV_PCM_FMTBIT_FLOAT_BE	_SNDRV_PCM_FMTBIT(FLOAT_BE)
#घोषणा SNDRV_PCM_FMTBIT_FLOAT64_LE	_SNDRV_PCM_FMTBIT(FLOAT64_LE)
#घोषणा SNDRV_PCM_FMTBIT_FLOAT64_BE	_SNDRV_PCM_FMTBIT(FLOAT64_BE)
#घोषणा SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE _SNDRV_PCM_FMTBIT(IEC958_SUBFRAME_LE)
#घोषणा SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_BE _SNDRV_PCM_FMTBIT(IEC958_SUBFRAME_BE)
#घोषणा SNDRV_PCM_FMTBIT_MU_LAW		_SNDRV_PCM_FMTBIT(MU_LAW)
#घोषणा SNDRV_PCM_FMTBIT_A_LAW		_SNDRV_PCM_FMTBIT(A_LAW)
#घोषणा SNDRV_PCM_FMTBIT_IMA_ADPCM	_SNDRV_PCM_FMTBIT(IMA_ADPCM)
#घोषणा SNDRV_PCM_FMTBIT_MPEG		_SNDRV_PCM_FMTBIT(MPEG)
#घोषणा SNDRV_PCM_FMTBIT_GSM		_SNDRV_PCM_FMTBIT(GSM)
#घोषणा SNDRV_PCM_FMTBIT_S20_LE	_SNDRV_PCM_FMTBIT(S20_LE)
#घोषणा SNDRV_PCM_FMTBIT_U20_LE	_SNDRV_PCM_FMTBIT(U20_LE)
#घोषणा SNDRV_PCM_FMTBIT_S20_BE	_SNDRV_PCM_FMTBIT(S20_BE)
#घोषणा SNDRV_PCM_FMTBIT_U20_BE	_SNDRV_PCM_FMTBIT(U20_BE)
#घोषणा SNDRV_PCM_FMTBIT_SPECIAL	_SNDRV_PCM_FMTBIT(SPECIAL)
#घोषणा SNDRV_PCM_FMTBIT_S24_3LE	_SNDRV_PCM_FMTBIT(S24_3LE)
#घोषणा SNDRV_PCM_FMTBIT_U24_3LE	_SNDRV_PCM_FMTBIT(U24_3LE)
#घोषणा SNDRV_PCM_FMTBIT_S24_3BE	_SNDRV_PCM_FMTBIT(S24_3BE)
#घोषणा SNDRV_PCM_FMTBIT_U24_3BE	_SNDRV_PCM_FMTBIT(U24_3BE)
#घोषणा SNDRV_PCM_FMTBIT_S20_3LE	_SNDRV_PCM_FMTBIT(S20_3LE)
#घोषणा SNDRV_PCM_FMTBIT_U20_3LE	_SNDRV_PCM_FMTBIT(U20_3LE)
#घोषणा SNDRV_PCM_FMTBIT_S20_3BE	_SNDRV_PCM_FMTBIT(S20_3BE)
#घोषणा SNDRV_PCM_FMTBIT_U20_3BE	_SNDRV_PCM_FMTBIT(U20_3BE)
#घोषणा SNDRV_PCM_FMTBIT_S18_3LE	_SNDRV_PCM_FMTBIT(S18_3LE)
#घोषणा SNDRV_PCM_FMTBIT_U18_3LE	_SNDRV_PCM_FMTBIT(U18_3LE)
#घोषणा SNDRV_PCM_FMTBIT_S18_3BE	_SNDRV_PCM_FMTBIT(S18_3BE)
#घोषणा SNDRV_PCM_FMTBIT_U18_3BE	_SNDRV_PCM_FMTBIT(U18_3BE)
#घोषणा SNDRV_PCM_FMTBIT_G723_24	_SNDRV_PCM_FMTBIT(G723_24)
#घोषणा SNDRV_PCM_FMTBIT_G723_24_1B	_SNDRV_PCM_FMTBIT(G723_24_1B)
#घोषणा SNDRV_PCM_FMTBIT_G723_40	_SNDRV_PCM_FMTBIT(G723_40)
#घोषणा SNDRV_PCM_FMTBIT_G723_40_1B	_SNDRV_PCM_FMTBIT(G723_40_1B)
#घोषणा SNDRV_PCM_FMTBIT_DSD_U8		_SNDRV_PCM_FMTBIT(DSD_U8)
#घोषणा SNDRV_PCM_FMTBIT_DSD_U16_LE	_SNDRV_PCM_FMTBIT(DSD_U16_LE)
#घोषणा SNDRV_PCM_FMTBIT_DSD_U32_LE	_SNDRV_PCM_FMTBIT(DSD_U32_LE)
#घोषणा SNDRV_PCM_FMTBIT_DSD_U16_BE	_SNDRV_PCM_FMTBIT(DSD_U16_BE)
#घोषणा SNDRV_PCM_FMTBIT_DSD_U32_BE	_SNDRV_PCM_FMTBIT(DSD_U32_BE)

#अगर_घोषित SNDRV_LITTLE_ENDIAN
#घोषणा SNDRV_PCM_FMTBIT_S16		SNDRV_PCM_FMTBIT_S16_LE
#घोषणा SNDRV_PCM_FMTBIT_U16		SNDRV_PCM_FMTBIT_U16_LE
#घोषणा SNDRV_PCM_FMTBIT_S24		SNDRV_PCM_FMTBIT_S24_LE
#घोषणा SNDRV_PCM_FMTBIT_U24		SNDRV_PCM_FMTBIT_U24_LE
#घोषणा SNDRV_PCM_FMTBIT_S32		SNDRV_PCM_FMTBIT_S32_LE
#घोषणा SNDRV_PCM_FMTBIT_U32		SNDRV_PCM_FMTBIT_U32_LE
#घोषणा SNDRV_PCM_FMTBIT_FLOAT		SNDRV_PCM_FMTBIT_FLOAT_LE
#घोषणा SNDRV_PCM_FMTBIT_FLOAT64	SNDRV_PCM_FMTBIT_FLOAT64_LE
#घोषणा SNDRV_PCM_FMTBIT_IEC958_SUBFRAME SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE
#घोषणा SNDRV_PCM_FMTBIT_S20		SNDRV_PCM_FMTBIT_S20_LE
#घोषणा SNDRV_PCM_FMTBIT_U20		SNDRV_PCM_FMTBIT_U20_LE
#पूर्ण_अगर
#अगर_घोषित SNDRV_BIG_ENDIAN
#घोषणा SNDRV_PCM_FMTBIT_S16		SNDRV_PCM_FMTBIT_S16_BE
#घोषणा SNDRV_PCM_FMTBIT_U16		SNDRV_PCM_FMTBIT_U16_BE
#घोषणा SNDRV_PCM_FMTBIT_S24		SNDRV_PCM_FMTBIT_S24_BE
#घोषणा SNDRV_PCM_FMTBIT_U24		SNDRV_PCM_FMTBIT_U24_BE
#घोषणा SNDRV_PCM_FMTBIT_S32		SNDRV_PCM_FMTBIT_S32_BE
#घोषणा SNDRV_PCM_FMTBIT_U32		SNDRV_PCM_FMTBIT_U32_BE
#घोषणा SNDRV_PCM_FMTBIT_FLOAT		SNDRV_PCM_FMTBIT_FLOAT_BE
#घोषणा SNDRV_PCM_FMTBIT_FLOAT64	SNDRV_PCM_FMTBIT_FLOAT64_BE
#घोषणा SNDRV_PCM_FMTBIT_IEC958_SUBFRAME SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_BE
#घोषणा SNDRV_PCM_FMTBIT_S20		SNDRV_PCM_FMTBIT_S20_BE
#घोषणा SNDRV_PCM_FMTBIT_U20		SNDRV_PCM_FMTBIT_U20_BE
#पूर्ण_अगर

काष्ठा snd_pcm_file अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक no_compat_mmap;
	अचिन्हित पूर्णांक user_pversion;	/* supported protocol version */
पूर्ण;

काष्ठा snd_pcm_hw_rule;
प्रकार पूर्णांक (*snd_pcm_hw_rule_func_t)(काष्ठा snd_pcm_hw_params *params,
				      काष्ठा snd_pcm_hw_rule *rule);

काष्ठा snd_pcm_hw_rule अणु
	अचिन्हित पूर्णांक cond;
	पूर्णांक var;
	पूर्णांक deps[5];

	snd_pcm_hw_rule_func_t func;
	व्योम *निजी;
पूर्ण;

काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs अणु
	काष्ठा snd_mask masks[SNDRV_PCM_HW_PARAM_LAST_MASK - 
			 SNDRV_PCM_HW_PARAM_FIRST_MASK + 1];
	काष्ठा snd_पूर्णांकerval पूर्णांकervals[SNDRV_PCM_HW_PARAM_LAST_INTERVAL -
			     SNDRV_PCM_HW_PARAM_FIRST_INTERVAL + 1];
	अचिन्हित पूर्णांक rules_num;
	अचिन्हित पूर्णांक rules_all;
	काष्ठा snd_pcm_hw_rule *rules;
पूर्ण;

अटल अंतरभूत काष्ठा snd_mask *स्थिरrs_mask(काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs *स्थिरrs,
					    snd_pcm_hw_param_t var)
अणु
	वापस &स्थिरrs->masks[var - SNDRV_PCM_HW_PARAM_FIRST_MASK];
पूर्ण

अटल अंतरभूत काष्ठा snd_पूर्णांकerval *स्थिरrs_पूर्णांकerval(काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs *स्थिरrs,
						    snd_pcm_hw_param_t var)
अणु
	वापस &स्थिरrs->पूर्णांकervals[var - SNDRV_PCM_HW_PARAM_FIRST_INTERVAL];
पूर्ण

काष्ठा snd_ratnum अणु
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक den_min, den_max, den_step;
पूर्ण;

काष्ठा snd_ratden अणु
	अचिन्हित पूर्णांक num_min, num_max, num_step;
	अचिन्हित पूर्णांक den;
पूर्ण;

काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums अणु
	पूर्णांक nrats;
	स्थिर काष्ठा snd_ratnum *rats;
पूर्ण;

काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratdens अणु
	पूर्णांक nrats;
	स्थिर काष्ठा snd_ratden *rats;
पूर्ण;

काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list अणु
	स्थिर अचिन्हित पूर्णांक *list;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक mask;
पूर्ण;

काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ranges अणु
	अचिन्हित पूर्णांक count;
	स्थिर काष्ठा snd_पूर्णांकerval *ranges;
	अचिन्हित पूर्णांक mask;
पूर्ण;

/*
 * userspace-provided audio बारtamp config to kernel,
 * काष्ठाure is क्रम पूर्णांकernal use only and filled with dedicated unpack routine
 */
काष्ठा snd_pcm_audio_tstamp_config अणु
	/* 5 of max 16 bits used */
	u32 type_requested:4;
	u32 report_delay:1; /* add total delay to A/D or D/A */
पूर्ण;

अटल अंतरभूत व्योम snd_pcm_unpack_audio_tstamp_config(__u32 data,
						काष्ठा snd_pcm_audio_tstamp_config *config)
अणु
	config->type_requested = data & 0xF;
	config->report_delay = (data >> 4) & 1;
पूर्ण

/*
 * kernel-provided audio बारtamp report to user-space
 * काष्ठाure is क्रम पूर्णांकernal use only and पढ़ो by dedicated pack routine
 */
काष्ठा snd_pcm_audio_tstamp_report अणु
	/* 6 of max 16 bits used क्रम bit-fields */

	/* क्रम backwards compatibility */
	u32 valid:1;

	/* actual type अगर hardware could not support requested बारtamp */
	u32 actual_type:4;

	/* accuracy represented in ns units */
	u32 accuracy_report:1; /* 0 अगर accuracy unknown, 1 अगर accuracy field is valid */
	u32 accuracy; /* up to 4.29s, will be packed in separate field  */
पूर्ण;

अटल अंतरभूत व्योम snd_pcm_pack_audio_tstamp_report(__u32 *data, __u32 *accuracy,
						स्थिर काष्ठा snd_pcm_audio_tstamp_report *report)
अणु
	u32 पंचांगp;

	पंचांगp = report->accuracy_report;
	पंचांगp <<= 4;
	पंचांगp |= report->actual_type;
	पंचांगp <<= 1;
	पंचांगp |= report->valid;

	*data &= 0xffff; /* zero-clear MSBs */
	*data |= (पंचांगp << 16);
	*accuracy = report->accuracy;
पूर्ण


काष्ठा snd_pcm_runसमय अणु
	/* -- Status -- */
	काष्ठा snd_pcm_substream *trigger_master;
	काष्ठा बारpec64 trigger_tstamp;	/* trigger बारtamp */
	bool trigger_tstamp_latched;     /* trigger बारtamp latched in low-level driver/hardware */
	पूर्णांक overrange;
	snd_pcm_uframes_t avail_max;
	snd_pcm_uframes_t hw_ptr_base;	/* Position at buffer restart */
	snd_pcm_uframes_t hw_ptr_पूर्णांकerrupt; /* Position at पूर्णांकerrupt समय */
	अचिन्हित दीर्घ hw_ptr_jअगरfies;	/* Time when hw_ptr is updated */
	अचिन्हित दीर्घ hw_ptr_buffer_jअगरfies; /* buffer समय in jअगरfies */
	snd_pcm_sframes_t delay;	/* extra delay; typically FIFO size */
	u64 hw_ptr_wrap;                /* offset क्रम hw_ptr due to boundary wrap-around */

	/* -- HW params -- */
	snd_pcm_access_t access;	/* access mode */
	snd_pcm_क्रमmat_t क्रमmat;	/* SNDRV_PCM_FORMAT_* */
	snd_pcm_subक्रमmat_t subक्रमmat;	/* subक्रमmat */
	अचिन्हित पूर्णांक rate;		/* rate in Hz */
	अचिन्हित पूर्णांक channels;		/* channels */
	snd_pcm_uframes_t period_size;	/* period size */
	अचिन्हित पूर्णांक periods;		/* periods */
	snd_pcm_uframes_t buffer_size;	/* buffer size */
	snd_pcm_uframes_t min_align;	/* Min alignment क्रम the क्रमmat */
	माप_प्रकार byte_align;
	अचिन्हित पूर्णांक frame_bits;
	अचिन्हित पूर्णांक sample_bits;
	अचिन्हित पूर्णांक info;
	अचिन्हित पूर्णांक rate_num;
	अचिन्हित पूर्णांक rate_den;
	अचिन्हित पूर्णांक no_period_wakeup: 1;

	/* -- SW params -- */
	पूर्णांक tstamp_mode;		/* mmap बारtamp is updated */
  	अचिन्हित पूर्णांक period_step;
	snd_pcm_uframes_t start_threshold;
	snd_pcm_uframes_t stop_threshold;
	snd_pcm_uframes_t silence_threshold; /* Silence filling happens when
						noise is nearest than this */
	snd_pcm_uframes_t silence_size;	/* Silence filling size */
	snd_pcm_uframes_t boundary;	/* poपूर्णांकers wrap poपूर्णांक */

	snd_pcm_uframes_t silence_start; /* starting poपूर्णांकer to silence area */
	snd_pcm_uframes_t silence_filled; /* size filled with silence */

	जोड़ snd_pcm_sync_id sync;	/* hardware synchronization ID */

	/* -- mmap -- */
	काष्ठा snd_pcm_mmap_status *status;
	काष्ठा snd_pcm_mmap_control *control;

	/* -- locking / scheduling -- */
	snd_pcm_uframes_t twake; 	/* करो transfer (!poll) wakeup अगर non-zero */
	रुको_queue_head_t sleep;	/* poll sleep */
	रुको_queue_head_t tsleep;	/* transfer sleep */
	काष्ठा fasync_काष्ठा *fasync;
	bool stop_operating;		/* sync_stop will be called */

	/* -- निजी section -- */
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा snd_pcm_runसमय *runसमय);

	/* -- hardware description -- */
	काष्ठा snd_pcm_hardware hw;
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs hw_स्थिरraपूर्णांकs;

	/* -- समयr -- */
	अचिन्हित पूर्णांक समयr_resolution;	/* समयr resolution */
	पूर्णांक tstamp_type;		/* बारtamp type */

	/* -- DMA -- */           
	अचिन्हित अक्षर *dma_area;	/* DMA area */
	dma_addr_t dma_addr;		/* physical bus address (not accessible from मुख्य CPU) */
	माप_प्रकार dma_bytes;		/* size of DMA area */

	काष्ठा snd_dma_buffer *dma_buffer_p;	/* allocated buffer */
	अचिन्हित पूर्णांक buffer_changed:1;	/* buffer allocation changed; set only in managed mode */

	/* -- audio बारtamp config -- */
	काष्ठा snd_pcm_audio_tstamp_config audio_tstamp_config;
	काष्ठा snd_pcm_audio_tstamp_report audio_tstamp_report;
	काष्ठा बारpec64 driver_tstamp;

#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
	/* -- OSS things -- */
	काष्ठा snd_pcm_oss_runसमय oss;
#पूर्ण_अगर
पूर्ण;

काष्ठा snd_pcm_group अणु		/* keep linked substreams */
	spinlock_t lock;
	काष्ठा mutex mutex;
	काष्ठा list_head substreams;
	refcount_t refs;
पूर्ण;

काष्ठा pid;

काष्ठा snd_pcm_substream अणु
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_str *pstr;
	व्योम *निजी_data;		/* copied from pcm->निजी_data */
	पूर्णांक number;
	अक्षर name[32];			/* substream name */
	पूर्णांक stream;			/* stream (direction) */
	काष्ठा pm_qos_request latency_pm_qos_req; /* pm_qos request */
	माप_प्रकार buffer_bytes_max;	/* limit ring buffer size */
	काष्ठा snd_dma_buffer dma_buffer;
	माप_प्रकार dma_max;
	/* -- hardware operations -- */
	स्थिर काष्ठा snd_pcm_ops *ops;
	/* -- runसमय inक्रमmation -- */
	काष्ठा snd_pcm_runसमय *runसमय;
        /* -- समयr section -- */
	काष्ठा snd_समयr *समयr;		/* समयr */
	अचिन्हित समयr_running: 1;	/* समय is running */
	दीर्घ रुको_समय;	/* समय in ms क्रम R/W to रुको क्रम avail */
	/* -- next substream -- */
	काष्ठा snd_pcm_substream *next;
	/* -- linked substreams -- */
	काष्ठा list_head link_list;	/* linked list member */
	काष्ठा snd_pcm_group self_group;	/* fake group क्रम non linked substream (with substream lock inside) */
	काष्ठा snd_pcm_group *group;		/* poपूर्णांकer to current group */
	/* -- asचिन्हित files -- */
	पूर्णांक ref_count;
	atomic_t mmap_count;
	अचिन्हित पूर्णांक f_flags;
	व्योम (*pcm_release)(काष्ठा snd_pcm_substream *);
	काष्ठा pid *pid;
#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
	/* -- OSS things -- */
	काष्ठा snd_pcm_oss_substream oss;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SND_VERBOSE_PROCFS
	काष्ठा snd_info_entry *proc_root;
#पूर्ण_अगर /* CONFIG_SND_VERBOSE_PROCFS */
	/* misc flags */
	अचिन्हित पूर्णांक hw_खोलोed: 1;
	अचिन्हित पूर्णांक managed_buffer_alloc:1;
पूर्ण;

#घोषणा SUBSTREAM_BUSY(substream) ((substream)->ref_count > 0)


काष्ठा snd_pcm_str अणु
	पूर्णांक stream;				/* stream (direction) */
	काष्ठा snd_pcm *pcm;
	/* -- substreams -- */
	अचिन्हित पूर्णांक substream_count;
	अचिन्हित पूर्णांक substream_खोलोed;
	काष्ठा snd_pcm_substream *substream;
#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
	/* -- OSS things -- */
	काष्ठा snd_pcm_oss_stream oss;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SND_VERBOSE_PROCFS
	काष्ठा snd_info_entry *proc_root;
#अगर_घोषित CONFIG_SND_PCM_XRUN_DEBUG
	अचिन्हित पूर्णांक xrun_debug;	/* 0 = disabled, 1 = verbose, 2 = stacktrace */
#पूर्ण_अगर
#पूर्ण_अगर
	काष्ठा snd_kcontrol *chmap_kctl; /* channel-mapping controls */
	काष्ठा device dev;
पूर्ण;

काष्ठा snd_pcm अणु
	काष्ठा snd_card *card;
	काष्ठा list_head list;
	पूर्णांक device; /* device number */
	अचिन्हित पूर्णांक info_flags;
	अचिन्हित लघु dev_class;
	अचिन्हित लघु dev_subclass;
	अक्षर id[64];
	अक्षर name[80];
	काष्ठा snd_pcm_str streams[2];
	काष्ठा mutex खोलो_mutex;
	रुको_queue_head_t खोलो_रुको;
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त) (काष्ठा snd_pcm *pcm);
	bool पूर्णांकernal; /* pcm is क्रम पूर्णांकernal use only */
	bool nonatomic; /* whole PCM operations are in non-atomic context */
	bool no_device_suspend; /* करोn't invoke device PM suspend */
#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
	काष्ठा snd_pcm_oss oss;
#पूर्ण_अगर
पूर्ण;

/*
 *  Registering
 */

बाह्य स्थिर काष्ठा file_operations snd_pcm_f_ops[2];

पूर्णांक snd_pcm_new(काष्ठा snd_card *card, स्थिर अक्षर *id, पूर्णांक device,
		पूर्णांक playback_count, पूर्णांक capture_count,
		काष्ठा snd_pcm **rpcm);
पूर्णांक snd_pcm_new_पूर्णांकernal(काष्ठा snd_card *card, स्थिर अक्षर *id, पूर्णांक device,
		पूर्णांक playback_count, पूर्णांक capture_count,
		काष्ठा snd_pcm **rpcm);
पूर्णांक snd_pcm_new_stream(काष्ठा snd_pcm *pcm, पूर्णांक stream, पूर्णांक substream_count);

#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
काष्ठा snd_pcm_notअगरy अणु
	पूर्णांक (*n_रेजिस्टर) (काष्ठा snd_pcm * pcm);
	पूर्णांक (*n_disconnect) (काष्ठा snd_pcm * pcm);
	पूर्णांक (*n_unरेजिस्टर) (काष्ठा snd_pcm * pcm);
	काष्ठा list_head list;
पूर्ण;
पूर्णांक snd_pcm_notअगरy(काष्ठा snd_pcm_notअगरy *notअगरy, पूर्णांक nमुक्त);
#पूर्ण_अगर

/*
 *  Native I/O
 */

पूर्णांक snd_pcm_info(काष्ठा snd_pcm_substream *substream, काष्ठा snd_pcm_info *info);
पूर्णांक snd_pcm_info_user(काष्ठा snd_pcm_substream *substream,
		      काष्ठा snd_pcm_info __user *info);
पूर्णांक snd_pcm_status64(काष्ठा snd_pcm_substream *substream,
		     काष्ठा snd_pcm_status64 *status);
पूर्णांक snd_pcm_start(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_pcm_stop(काष्ठा snd_pcm_substream *substream, snd_pcm_state_t status);
पूर्णांक snd_pcm_drain_करोne(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_pcm_stop_xrun(काष्ठा snd_pcm_substream *substream);
#अगर_घोषित CONFIG_PM
पूर्णांक snd_pcm_suspend_all(काष्ठा snd_pcm *pcm);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_pcm_suspend_all(काष्ठा snd_pcm *pcm)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
पूर्णांक snd_pcm_kernel_ioctl(काष्ठा snd_pcm_substream *substream, अचिन्हित पूर्णांक cmd, व्योम *arg);
पूर्णांक snd_pcm_खोलो_substream(काष्ठा snd_pcm *pcm, पूर्णांक stream, काष्ठा file *file,
			   काष्ठा snd_pcm_substream **rsubstream);
व्योम snd_pcm_release_substream(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_pcm_attach_substream(काष्ठा snd_pcm *pcm, पूर्णांक stream, काष्ठा file *file,
			     काष्ठा snd_pcm_substream **rsubstream);
व्योम snd_pcm_detach_substream(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_pcm_mmap_data(काष्ठा snd_pcm_substream *substream, काष्ठा file *file, काष्ठा vm_area_काष्ठा *area);


#अगर_घोषित CONFIG_SND_DEBUG
व्योम snd_pcm_debug_name(काष्ठा snd_pcm_substream *substream,
			   अक्षर *name, माप_प्रकार len);
#अन्यथा
अटल अंतरभूत व्योम
snd_pcm_debug_name(काष्ठा snd_pcm_substream *substream, अक्षर *buf, माप_प्रकार size)
अणु
	*buf = 0;
पूर्ण
#पूर्ण_अगर

/*
 *  PCM library
 */

/**
 * snd_pcm_stream_linked - Check whether the substream is linked with others
 * @substream: substream to check
 *
 * Returns true अगर the given substream is being linked with others.
 */
अटल अंतरभूत पूर्णांक snd_pcm_stream_linked(काष्ठा snd_pcm_substream *substream)
अणु
	वापस substream->group != &substream->self_group;
पूर्ण

व्योम snd_pcm_stream_lock(काष्ठा snd_pcm_substream *substream);
व्योम snd_pcm_stream_unlock(काष्ठा snd_pcm_substream *substream);
व्योम snd_pcm_stream_lock_irq(काष्ठा snd_pcm_substream *substream);
व्योम snd_pcm_stream_unlock_irq(काष्ठा snd_pcm_substream *substream);
अचिन्हित दीर्घ _snd_pcm_stream_lock_irqsave(काष्ठा snd_pcm_substream *substream);

/**
 * snd_pcm_stream_lock_irqsave - Lock the PCM stream
 * @substream: PCM substream
 * @flags: irq flags
 *
 * This locks the PCM stream like snd_pcm_stream_lock() but with the local
 * IRQ (only when nonatomic is false).  In nonatomic हाल, this is identical
 * as snd_pcm_stream_lock().
 */
#घोषणा snd_pcm_stream_lock_irqsave(substream, flags)		 \
	करो अणु							 \
		typecheck(अचिन्हित दीर्घ, flags);		 \
		flags = _snd_pcm_stream_lock_irqsave(substream); \
	पूर्ण जबतक (0)
व्योम snd_pcm_stream_unlock_irqrestore(काष्ठा snd_pcm_substream *substream,
				      अचिन्हित दीर्घ flags);

/**
 * snd_pcm_group_क्रम_each_entry - iterate over the linked substreams
 * @s: the iterator
 * @substream: the substream
 *
 * Iterate over the all linked substreams to the given @substream.
 * When @substream isn't linked with any others, this gives वापसs @substream
 * itself once.
 */
#घोषणा snd_pcm_group_क्रम_each_entry(s, substream) \
	list_क्रम_each_entry(s, &substream->group->substreams, link_list)

#घोषणा क्रम_each_pcm_streams(stream)			\
	क्रम (stream  = SNDRV_PCM_STREAM_PLAYBACK;	\
	     stream <= SNDRV_PCM_STREAM_LAST;		\
	     stream++)

/**
 * snd_pcm_running - Check whether the substream is in a running state
 * @substream: substream to check
 *
 * Returns true अगर the given substream is in the state RUNNING, or in the
 * state DRAINING क्रम playback.
 */
अटल अंतरभूत पूर्णांक snd_pcm_running(काष्ठा snd_pcm_substream *substream)
अणु
	वापस (substream->runसमय->status->state == SNDRV_PCM_STATE_RUNNING ||
		(substream->runसमय->status->state == SNDRV_PCM_STATE_DRAINING &&
		 substream->stream == SNDRV_PCM_STREAM_PLAYBACK));
पूर्ण

/**
 * bytes_to_samples - Unit conversion of the size from bytes to samples
 * @runसमय: PCM runसमय instance
 * @size: size in bytes
 */
अटल अंतरभूत sमाप_प्रकार bytes_to_samples(काष्ठा snd_pcm_runसमय *runसमय, sमाप_प्रकार size)
अणु
	वापस size * 8 / runसमय->sample_bits;
पूर्ण

/**
 * bytes_to_frames - Unit conversion of the size from bytes to frames
 * @runसमय: PCM runसमय instance
 * @size: size in bytes
 */
अटल अंतरभूत snd_pcm_sframes_t bytes_to_frames(काष्ठा snd_pcm_runसमय *runसमय, sमाप_प्रकार size)
अणु
	वापस size * 8 / runसमय->frame_bits;
पूर्ण

/**
 * samples_to_bytes - Unit conversion of the size from samples to bytes
 * @runसमय: PCM runसमय instance
 * @size: size in samples
 */
अटल अंतरभूत sमाप_प्रकार samples_to_bytes(काष्ठा snd_pcm_runसमय *runसमय, sमाप_प्रकार size)
अणु
	वापस size * runसमय->sample_bits / 8;
पूर्ण

/**
 * frames_to_bytes - Unit conversion of the size from frames to bytes
 * @runसमय: PCM runसमय instance
 * @size: size in frames
 */
अटल अंतरभूत sमाप_प्रकार frames_to_bytes(काष्ठा snd_pcm_runसमय *runसमय, snd_pcm_sframes_t size)
अणु
	वापस size * runसमय->frame_bits / 8;
पूर्ण

/**
 * frame_aligned - Check whether the byte size is aligned to frames
 * @runसमय: PCM runसमय instance
 * @bytes: size in bytes
 */
अटल अंतरभूत पूर्णांक frame_aligned(काष्ठा snd_pcm_runसमय *runसमय, sमाप_प्रकार bytes)
अणु
	वापस bytes % runसमय->byte_align == 0;
पूर्ण

/**
 * snd_pcm_lib_buffer_bytes - Get the buffer size of the current PCM in bytes
 * @substream: PCM substream
 */
अटल अंतरभूत माप_प्रकार snd_pcm_lib_buffer_bytes(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	वापस frames_to_bytes(runसमय, runसमय->buffer_size);
पूर्ण

/**
 * snd_pcm_lib_period_bytes - Get the period size of the current PCM in bytes
 * @substream: PCM substream
 */
अटल अंतरभूत माप_प्रकार snd_pcm_lib_period_bytes(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	वापस frames_to_bytes(runसमय, runसमय->period_size);
पूर्ण

/**
 * snd_pcm_playback_avail - Get the available (writable) space क्रम playback
 * @runसमय: PCM runसमय instance
 *
 * Result is between 0 ... (boundary - 1)
 */
अटल अंतरभूत snd_pcm_uframes_t snd_pcm_playback_avail(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	snd_pcm_sframes_t avail = runसमय->status->hw_ptr + runसमय->buffer_size - runसमय->control->appl_ptr;
	अगर (avail < 0)
		avail += runसमय->boundary;
	अन्यथा अगर ((snd_pcm_uframes_t) avail >= runसमय->boundary)
		avail -= runसमय->boundary;
	वापस avail;
पूर्ण

/**
 * snd_pcm_capture_avail - Get the available (पढ़ोable) space क्रम capture
 * @runसमय: PCM runसमय instance
 *
 * Result is between 0 ... (boundary - 1)
 */
अटल अंतरभूत snd_pcm_uframes_t snd_pcm_capture_avail(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	snd_pcm_sframes_t avail = runसमय->status->hw_ptr - runसमय->control->appl_ptr;
	अगर (avail < 0)
		avail += runसमय->boundary;
	वापस avail;
पूर्ण

/**
 * snd_pcm_playback_hw_avail - Get the queued space क्रम playback
 * @runसमय: PCM runसमय instance
 */
अटल अंतरभूत snd_pcm_sframes_t snd_pcm_playback_hw_avail(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	वापस runसमय->buffer_size - snd_pcm_playback_avail(runसमय);
पूर्ण

/**
 * snd_pcm_capture_hw_avail - Get the मुक्त space क्रम capture
 * @runसमय: PCM runसमय instance
 */
अटल अंतरभूत snd_pcm_sframes_t snd_pcm_capture_hw_avail(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	वापस runसमय->buffer_size - snd_pcm_capture_avail(runसमय);
पूर्ण

/**
 * snd_pcm_playback_पढ़ोy - check whether the playback buffer is available
 * @substream: the pcm substream instance
 *
 * Checks whether enough मुक्त space is available on the playback buffer.
 *
 * Return: Non-zero अगर available, or zero अगर not.
 */
अटल अंतरभूत पूर्णांक snd_pcm_playback_पढ़ोy(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	वापस snd_pcm_playback_avail(runसमय) >= runसमय->control->avail_min;
पूर्ण

/**
 * snd_pcm_capture_पढ़ोy - check whether the capture buffer is available
 * @substream: the pcm substream instance
 *
 * Checks whether enough capture data is available on the capture buffer.
 *
 * Return: Non-zero अगर available, or zero अगर not.
 */
अटल अंतरभूत पूर्णांक snd_pcm_capture_पढ़ोy(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	वापस snd_pcm_capture_avail(runसमय) >= runसमय->control->avail_min;
पूर्ण

/**
 * snd_pcm_playback_data - check whether any data exists on the playback buffer
 * @substream: the pcm substream instance
 *
 * Checks whether any data exists on the playback buffer.
 *
 * Return: Non-zero अगर any data exists, or zero अगर not. If stop_threshold
 * is bigger or equal to boundary, then this function वापसs always non-zero.
 */
अटल अंतरभूत पूर्णांक snd_pcm_playback_data(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	
	अगर (runसमय->stop_threshold >= runसमय->boundary)
		वापस 1;
	वापस snd_pcm_playback_avail(runसमय) < runसमय->buffer_size;
पूर्ण

/**
 * snd_pcm_playback_empty - check whether the playback buffer is empty
 * @substream: the pcm substream instance
 *
 * Checks whether the playback buffer is empty.
 *
 * Return: Non-zero अगर empty, or zero अगर not.
 */
अटल अंतरभूत पूर्णांक snd_pcm_playback_empty(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	वापस snd_pcm_playback_avail(runसमय) >= runसमय->buffer_size;
पूर्ण

/**
 * snd_pcm_capture_empty - check whether the capture buffer is empty
 * @substream: the pcm substream instance
 *
 * Checks whether the capture buffer is empty.
 *
 * Return: Non-zero अगर empty, or zero अगर not.
 */
अटल अंतरभूत पूर्णांक snd_pcm_capture_empty(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	वापस snd_pcm_capture_avail(runसमय) == 0;
पूर्ण

/**
 * snd_pcm_trigger_करोne - Mark the master substream
 * @substream: the pcm substream instance
 * @master: the linked master substream
 *
 * When multiple substreams of the same card are linked and the hardware
 * supports the single-shot operation, the driver calls this in the loop
 * in snd_pcm_group_क्रम_each_entry() क्रम marking the substream as "done".
 * Then most of trigger operations are perक्रमmed only to the given master
 * substream.
 *
 * The trigger_master mark is cleared at बारtamp updates at the end
 * of trigger operations.
 */
अटल अंतरभूत व्योम snd_pcm_trigger_करोne(काष्ठा snd_pcm_substream *substream, 
					काष्ठा snd_pcm_substream *master)
अणु
	substream->runसमय->trigger_master = master;
पूर्ण

अटल अंतरभूत पूर्णांक hw_is_mask(पूर्णांक var)
अणु
	वापस var >= SNDRV_PCM_HW_PARAM_FIRST_MASK &&
		var <= SNDRV_PCM_HW_PARAM_LAST_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक hw_is_पूर्णांकerval(पूर्णांक var)
अणु
	वापस var >= SNDRV_PCM_HW_PARAM_FIRST_INTERVAL &&
		var <= SNDRV_PCM_HW_PARAM_LAST_INTERVAL;
पूर्ण

अटल अंतरभूत काष्ठा snd_mask *hw_param_mask(काष्ठा snd_pcm_hw_params *params,
				     snd_pcm_hw_param_t var)
अणु
	वापस &params->masks[var - SNDRV_PCM_HW_PARAM_FIRST_MASK];
पूर्ण

अटल अंतरभूत काष्ठा snd_पूर्णांकerval *hw_param_पूर्णांकerval(काष्ठा snd_pcm_hw_params *params,
					     snd_pcm_hw_param_t var)
अणु
	वापस &params->पूर्णांकervals[var - SNDRV_PCM_HW_PARAM_FIRST_INTERVAL];
पूर्ण

अटल अंतरभूत स्थिर काष्ठा snd_mask *hw_param_mask_c(स्थिर काष्ठा snd_pcm_hw_params *params,
					     snd_pcm_hw_param_t var)
अणु
	वापस &params->masks[var - SNDRV_PCM_HW_PARAM_FIRST_MASK];
पूर्ण

अटल अंतरभूत स्थिर काष्ठा snd_पूर्णांकerval *hw_param_पूर्णांकerval_c(स्थिर काष्ठा snd_pcm_hw_params *params,
						     snd_pcm_hw_param_t var)
अणु
	वापस &params->पूर्णांकervals[var - SNDRV_PCM_HW_PARAM_FIRST_INTERVAL];
पूर्ण

/**
 * params_channels - Get the number of channels from the hw params
 * @p: hw params
 */
अटल अंतरभूत अचिन्हित पूर्णांक params_channels(स्थिर काष्ठा snd_pcm_hw_params *p)
अणु
	वापस hw_param_पूर्णांकerval_c(p, SNDRV_PCM_HW_PARAM_CHANNELS)->min;
पूर्ण

/**
 * params_rate - Get the sample rate from the hw params
 * @p: hw params
 */
अटल अंतरभूत अचिन्हित पूर्णांक params_rate(स्थिर काष्ठा snd_pcm_hw_params *p)
अणु
	वापस hw_param_पूर्णांकerval_c(p, SNDRV_PCM_HW_PARAM_RATE)->min;
पूर्ण

/**
 * params_period_size - Get the period size (in frames) from the hw params
 * @p: hw params
 */
अटल अंतरभूत अचिन्हित पूर्णांक params_period_size(स्थिर काष्ठा snd_pcm_hw_params *p)
अणु
	वापस hw_param_पूर्णांकerval_c(p, SNDRV_PCM_HW_PARAM_PERIOD_SIZE)->min;
पूर्ण

/**
 * params_periods - Get the number of periods from the hw params
 * @p: hw params
 */
अटल अंतरभूत अचिन्हित पूर्णांक params_periods(स्थिर काष्ठा snd_pcm_hw_params *p)
अणु
	वापस hw_param_पूर्णांकerval_c(p, SNDRV_PCM_HW_PARAM_PERIODS)->min;
पूर्ण

/**
 * params_buffer_size - Get the buffer size (in frames) from the hw params
 * @p: hw params
 */
अटल अंतरभूत अचिन्हित पूर्णांक params_buffer_size(स्थिर काष्ठा snd_pcm_hw_params *p)
अणु
	वापस hw_param_पूर्णांकerval_c(p, SNDRV_PCM_HW_PARAM_BUFFER_SIZE)->min;
पूर्ण

/**
 * params_buffer_bytes - Get the buffer size (in bytes) from the hw params
 * @p: hw params
 */
अटल अंतरभूत अचिन्हित पूर्णांक params_buffer_bytes(स्थिर काष्ठा snd_pcm_hw_params *p)
अणु
	वापस hw_param_पूर्णांकerval_c(p, SNDRV_PCM_HW_PARAM_BUFFER_BYTES)->min;
पूर्ण

पूर्णांक snd_पूर्णांकerval_refine(काष्ठा snd_पूर्णांकerval *i, स्थिर काष्ठा snd_पूर्णांकerval *v);
पूर्णांक snd_पूर्णांकerval_list(काष्ठा snd_पूर्णांकerval *i, अचिन्हित पूर्णांक count,
		      स्थिर अचिन्हित पूर्णांक *list, अचिन्हित पूर्णांक mask);
पूर्णांक snd_पूर्णांकerval_ranges(काष्ठा snd_पूर्णांकerval *i, अचिन्हित पूर्णांक count,
			स्थिर काष्ठा snd_पूर्णांकerval *list, अचिन्हित पूर्णांक mask);
पूर्णांक snd_पूर्णांकerval_ratnum(काष्ठा snd_पूर्णांकerval *i,
			अचिन्हित पूर्णांक rats_count, स्थिर काष्ठा snd_ratnum *rats,
			अचिन्हित पूर्णांक *nump, अचिन्हित पूर्णांक *denp);

व्योम _snd_pcm_hw_params_any(काष्ठा snd_pcm_hw_params *params);
व्योम _snd_pcm_hw_param_setempty(काष्ठा snd_pcm_hw_params *params, snd_pcm_hw_param_t var);

पूर्णांक snd_pcm_hw_refine(काष्ठा snd_pcm_substream *substream, काष्ठा snd_pcm_hw_params *params);

पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_mask64(काष्ठा snd_pcm_runसमय *runसमय, snd_pcm_hw_param_t var,
				 u_पूर्णांक64_t mask);
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_minmax(काष्ठा snd_pcm_runसमय *runसमय, snd_pcm_hw_param_t var,
				 अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max);
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(काष्ठा snd_pcm_runसमय *runसमय, snd_pcm_hw_param_t var);
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_list(काष्ठा snd_pcm_runसमय *runसमय, 
			       अचिन्हित पूर्णांक cond,
			       snd_pcm_hw_param_t var,
			       स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *l);
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_ranges(काष्ठा snd_pcm_runसमय *runसमय,
				 अचिन्हित पूर्णांक cond,
				 snd_pcm_hw_param_t var,
				 स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ranges *r);
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_ratnums(काष्ठा snd_pcm_runसमय *runसमय, 
				  अचिन्हित पूर्णांक cond,
				  snd_pcm_hw_param_t var,
				  स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums *r);
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_ratdens(काष्ठा snd_pcm_runसमय *runसमय, 
				  अचिन्हित पूर्णांक cond,
				  snd_pcm_hw_param_t var,
				  स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratdens *r);
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_msbits(काष्ठा snd_pcm_runसमय *runसमय, 
				 अचिन्हित पूर्णांक cond,
				 अचिन्हित पूर्णांक width,
				 अचिन्हित पूर्णांक msbits);
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_step(काष्ठा snd_pcm_runसमय *runसमय,
			       अचिन्हित पूर्णांक cond,
			       snd_pcm_hw_param_t var,
			       अचिन्हित दीर्घ step);
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_घात2(काष्ठा snd_pcm_runसमय *runसमय,
			       अचिन्हित पूर्णांक cond,
			       snd_pcm_hw_param_t var);
पूर्णांक snd_pcm_hw_rule_noresample(काष्ठा snd_pcm_runसमय *runसमय,
			       अचिन्हित पूर्णांक base_rate);
पूर्णांक snd_pcm_hw_rule_add(काष्ठा snd_pcm_runसमय *runसमय,
			अचिन्हित पूर्णांक cond,
			पूर्णांक var,
			snd_pcm_hw_rule_func_t func, व्योम *निजी,
			पूर्णांक dep, ...);

/**
 * snd_pcm_hw_स्थिरraपूर्णांक_single() - Constrain parameter to a single value
 * @runसमय: PCM runसमय instance
 * @var: The hw_params variable to स्थिरrain
 * @val: The value to स्थिरrain to
 *
 * Return: Positive अगर the value is changed, zero अगर it's not changed, or a
 * negative error code.
 */
अटल अंतरभूत पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_single(
	काष्ठा snd_pcm_runसमय *runसमय, snd_pcm_hw_param_t var,
	अचिन्हित पूर्णांक val)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, var, val, val);
पूर्ण

पूर्णांक snd_pcm_क्रमmat_चिन्हित(snd_pcm_क्रमmat_t क्रमmat);
पूर्णांक snd_pcm_क्रमmat_अचिन्हित(snd_pcm_क्रमmat_t क्रमmat);
पूर्णांक snd_pcm_क्रमmat_linear(snd_pcm_क्रमmat_t क्रमmat);
पूर्णांक snd_pcm_क्रमmat_little_endian(snd_pcm_क्रमmat_t क्रमmat);
पूर्णांक snd_pcm_क्रमmat_big_endian(snd_pcm_क्रमmat_t क्रमmat);
#अगर 0 /* just क्रम kernel-करोc */
/**
 * snd_pcm_क्रमmat_cpu_endian - Check the PCM क्रमmat is CPU-endian
 * @क्रमmat: the क्रमmat to check
 *
 * Return: 1 अगर the given PCM क्रमmat is CPU-endian, 0 अगर
 * opposite, or a negative error code अगर endian not specअगरied.
 */
पूर्णांक snd_pcm_क्रमmat_cpu_endian(snd_pcm_क्रमmat_t क्रमmat);
#पूर्ण_अगर /* DocBook */
#अगर_घोषित SNDRV_LITTLE_ENDIAN
#घोषणा snd_pcm_क्रमmat_cpu_endian(क्रमmat) snd_pcm_क्रमmat_little_endian(क्रमmat)
#अन्यथा
#घोषणा snd_pcm_क्रमmat_cpu_endian(क्रमmat) snd_pcm_क्रमmat_big_endian(क्रमmat)
#पूर्ण_अगर
पूर्णांक snd_pcm_क्रमmat_width(snd_pcm_क्रमmat_t क्रमmat);			/* in bits */
पूर्णांक snd_pcm_क्रमmat_physical_width(snd_pcm_क्रमmat_t क्रमmat);		/* in bits */
sमाप_प्रकार snd_pcm_क्रमmat_size(snd_pcm_क्रमmat_t क्रमmat, माप_प्रकार samples);
स्थिर अचिन्हित अक्षर *snd_pcm_क्रमmat_silence_64(snd_pcm_क्रमmat_t क्रमmat);
पूर्णांक snd_pcm_क्रमmat_set_silence(snd_pcm_क्रमmat_t क्रमmat, व्योम *buf, अचिन्हित पूर्णांक frames);

व्योम snd_pcm_set_ops(काष्ठा snd_pcm * pcm, पूर्णांक direction,
		     स्थिर काष्ठा snd_pcm_ops *ops);
व्योम snd_pcm_set_sync(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_pcm_lib_ioctl(काष्ठा snd_pcm_substream *substream,
		      अचिन्हित पूर्णांक cmd, व्योम *arg);                      
व्योम snd_pcm_period_elapsed(काष्ठा snd_pcm_substream *substream);
snd_pcm_sframes_t __snd_pcm_lib_xfer(काष्ठा snd_pcm_substream *substream,
				     व्योम *buf, bool पूर्णांकerleaved,
				     snd_pcm_uframes_t frames, bool in_kernel);

अटल अंतरभूत snd_pcm_sframes_t
snd_pcm_lib_ग_लिखो(काष्ठा snd_pcm_substream *substream,
		  स्थिर व्योम __user *buf, snd_pcm_uframes_t frames)
अणु
	वापस __snd_pcm_lib_xfer(substream, (व्योम __क्रमce *)buf, true, frames, false);
पूर्ण

अटल अंतरभूत snd_pcm_sframes_t
snd_pcm_lib_पढ़ो(काष्ठा snd_pcm_substream *substream,
		 व्योम __user *buf, snd_pcm_uframes_t frames)
अणु
	वापस __snd_pcm_lib_xfer(substream, (व्योम __क्रमce *)buf, true, frames, false);
पूर्ण

अटल अंतरभूत snd_pcm_sframes_t
snd_pcm_lib_ग_लिखोv(काष्ठा snd_pcm_substream *substream,
		   व्योम __user **bufs, snd_pcm_uframes_t frames)
अणु
	वापस __snd_pcm_lib_xfer(substream, (व्योम *)bufs, false, frames, false);
पूर्ण

अटल अंतरभूत snd_pcm_sframes_t
snd_pcm_lib_पढ़ोv(काष्ठा snd_pcm_substream *substream,
		  व्योम __user **bufs, snd_pcm_uframes_t frames)
अणु
	वापस __snd_pcm_lib_xfer(substream, (व्योम *)bufs, false, frames, false);
पूर्ण

अटल अंतरभूत snd_pcm_sframes_t
snd_pcm_kernel_ग_लिखो(काष्ठा snd_pcm_substream *substream,
		     स्थिर व्योम *buf, snd_pcm_uframes_t frames)
अणु
	वापस __snd_pcm_lib_xfer(substream, (व्योम *)buf, true, frames, true);
पूर्ण

अटल अंतरभूत snd_pcm_sframes_t
snd_pcm_kernel_पढ़ो(काष्ठा snd_pcm_substream *substream,
		    व्योम *buf, snd_pcm_uframes_t frames)
अणु
	वापस __snd_pcm_lib_xfer(substream, buf, true, frames, true);
पूर्ण

अटल अंतरभूत snd_pcm_sframes_t
snd_pcm_kernel_ग_लिखोv(काष्ठा snd_pcm_substream *substream,
		      व्योम **bufs, snd_pcm_uframes_t frames)
अणु
	वापस __snd_pcm_lib_xfer(substream, bufs, false, frames, true);
पूर्ण

अटल अंतरभूत snd_pcm_sframes_t
snd_pcm_kernel_पढ़ोv(काष्ठा snd_pcm_substream *substream,
		     व्योम **bufs, snd_pcm_uframes_t frames)
अणु
	वापस __snd_pcm_lib_xfer(substream, bufs, false, frames, true);
पूर्ण

पूर्णांक snd_pcm_hw_limit_rates(काष्ठा snd_pcm_hardware *hw);

अटल अंतरभूत पूर्णांक
snd_pcm_limit_hw_rates(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	वापस snd_pcm_hw_limit_rates(&runसमय->hw);
पूर्ण

अचिन्हित पूर्णांक snd_pcm_rate_to_rate_bit(अचिन्हित पूर्णांक rate);
अचिन्हित पूर्णांक snd_pcm_rate_bit_to_rate(अचिन्हित पूर्णांक rate_bit);
अचिन्हित पूर्णांक snd_pcm_rate_mask_पूर्णांकersect(अचिन्हित पूर्णांक rates_a,
					 अचिन्हित पूर्णांक rates_b);
अचिन्हित पूर्णांक snd_pcm_rate_range_to_bits(अचिन्हित पूर्णांक rate_min,
					अचिन्हित पूर्णांक rate_max);

/**
 * snd_pcm_set_runसमय_buffer - Set the PCM runसमय buffer
 * @substream: PCM substream to set
 * @bufp: the buffer inक्रमmation, शून्य to clear
 *
 * Copy the buffer inक्रमmation to runसमय->dma_buffer when @bufp is non-शून्य.
 * Otherwise it clears the current buffer inक्रमmation.
 */
अटल अंतरभूत व्योम snd_pcm_set_runसमय_buffer(काष्ठा snd_pcm_substream *substream,
					      काष्ठा snd_dma_buffer *bufp)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (bufp) अणु
		runसमय->dma_buffer_p = bufp;
		runसमय->dma_area = bufp->area;
		runसमय->dma_addr = bufp->addr;
		runसमय->dma_bytes = bufp->bytes;
	पूर्ण अन्यथा अणु
		runसमय->dma_buffer_p = शून्य;
		runसमय->dma_area = शून्य;
		runसमय->dma_addr = 0;
		runसमय->dma_bytes = 0;
	पूर्ण
पूर्ण

/**
 * snd_pcm_समय_लो - Fill the बारpec64 depending on the बारtamp mode
 * @runसमय: PCM runसमय instance
 * @tv: बारpec64 to fill
 */
अटल अंतरभूत व्योम snd_pcm_समय_लो(काष्ठा snd_pcm_runसमय *runसमय,
				   काष्ठा बारpec64 *tv)
अणु
	चयन (runसमय->tstamp_type) अणु
	हाल SNDRV_PCM_TSTAMP_TYPE_MONOTONIC:
		kसमय_get_ts64(tv);
		अवरोध;
	हाल SNDRV_PCM_TSTAMP_TYPE_MONOTONIC_RAW:
		kसमय_get_raw_ts64(tv);
		अवरोध;
	शेष:
		kसमय_get_real_ts64(tv);
		अवरोध;
	पूर्ण
पूर्ण

/*
 *  Memory
 */

व्योम snd_pcm_lib_pपुनः_स्मृतिate_मुक्त(काष्ठा snd_pcm_substream *substream);
व्योम snd_pcm_lib_pपुनः_स्मृतिate_मुक्त_क्रम_all(काष्ठा snd_pcm *pcm);
व्योम snd_pcm_lib_pपुनः_स्मृतिate_pages(काष्ठा snd_pcm_substream *substream,
				  पूर्णांक type, काष्ठा device *data,
				  माप_प्रकार size, माप_प्रकार max);
व्योम snd_pcm_lib_pपुनः_स्मृतिate_pages_क्रम_all(काष्ठा snd_pcm *pcm,
					  पूर्णांक type, व्योम *data,
					  माप_प्रकार size, माप_प्रकार max);
पूर्णांक snd_pcm_lib_दो_स्मृति_pages(काष्ठा snd_pcm_substream *substream, माप_प्रकार size);
पूर्णांक snd_pcm_lib_मुक्त_pages(काष्ठा snd_pcm_substream *substream);

व्योम snd_pcm_set_managed_buffer(काष्ठा snd_pcm_substream *substream, पूर्णांक type,
				काष्ठा device *data, माप_प्रकार size, माप_प्रकार max);
व्योम snd_pcm_set_managed_buffer_all(काष्ठा snd_pcm *pcm, पूर्णांक type,
				    काष्ठा device *data,
				    माप_प्रकार size, माप_प्रकार max);

पूर्णांक _snd_pcm_lib_alloc_vदो_स्मृति_buffer(काष्ठा snd_pcm_substream *substream,
				      माप_प्रकार size, gfp_t gfp_flags);
पूर्णांक snd_pcm_lib_मुक्त_vदो_स्मृति_buffer(काष्ठा snd_pcm_substream *substream);
काष्ठा page *snd_pcm_lib_get_vदो_स्मृति_page(काष्ठा snd_pcm_substream *substream,
					  अचिन्हित दीर्घ offset);
/**
 * snd_pcm_lib_alloc_vदो_स्मृति_buffer - allocate भव DMA buffer
 * @substream: the substream to allocate the buffer to
 * @size: the requested buffer size, in bytes
 *
 * Allocates the PCM substream buffer using vदो_स्मृति(), i.e., the memory is
 * contiguous in kernel भव space, but not in physical memory.  Use this
 * अगर the buffer is accessed by kernel code but not by device DMA.
 *
 * Return: 1 अगर the buffer was changed, 0 अगर not changed, or a negative error
 * code.
 */
अटल अंतरभूत पूर्णांक snd_pcm_lib_alloc_vदो_स्मृति_buffer
			(काष्ठा snd_pcm_substream *substream, माप_प्रकार size)
अणु
	वापस _snd_pcm_lib_alloc_vदो_स्मृति_buffer(substream, size,
						 GFP_KERNEL | __GFP_HIGHMEM | __GFP_ZERO);
पूर्ण

/**
 * snd_pcm_lib_alloc_vदो_स्मृति_32_buffer - allocate 32-bit-addressable buffer
 * @substream: the substream to allocate the buffer to
 * @size: the requested buffer size, in bytes
 *
 * This function works like snd_pcm_lib_alloc_vदो_स्मृति_buffer(), but uses
 * vदो_स्मृति_32(), i.e., the pages are allocated from 32-bit-addressable memory.
 *
 * Return: 1 अगर the buffer was changed, 0 अगर not changed, or a negative error
 * code.
 */
अटल अंतरभूत पूर्णांक snd_pcm_lib_alloc_vदो_स्मृति_32_buffer
			(काष्ठा snd_pcm_substream *substream, माप_प्रकार size)
अणु
	वापस _snd_pcm_lib_alloc_vदो_स्मृति_buffer(substream, size,
						 GFP_KERNEL | GFP_DMA32 | __GFP_ZERO);
पूर्ण

#घोषणा snd_pcm_get_dma_buf(substream) ((substream)->runसमय->dma_buffer_p)

#अगर_घोषित CONFIG_SND_DMA_SGBUF
/*
 * SG-buffer handling
 */
#घोषणा snd_pcm_substream_sgbuf(substream) \
	snd_pcm_get_dma_buf(substream)->निजी_data
#पूर्ण_अगर /* SND_DMA_SGBUF */

/**
 * snd_pcm_sgbuf_get_addr - Get the DMA address at the corresponding offset
 * @substream: PCM substream
 * @ofs: byte offset
 */
अटल अंतरभूत dma_addr_t
snd_pcm_sgbuf_get_addr(काष्ठा snd_pcm_substream *substream, अचिन्हित पूर्णांक ofs)
अणु
	वापस snd_sgbuf_get_addr(snd_pcm_get_dma_buf(substream), ofs);
पूर्ण

/**
 * snd_pcm_sgbuf_get_ptr - Get the भव address at the corresponding offset
 * @substream: PCM substream
 * @ofs: byte offset
 */
अटल अंतरभूत व्योम *
snd_pcm_sgbuf_get_ptr(काष्ठा snd_pcm_substream *substream, अचिन्हित पूर्णांक ofs)
अणु
	वापस snd_sgbuf_get_ptr(snd_pcm_get_dma_buf(substream), ofs);
पूर्ण

/**
 * snd_pcm_sgbuf_get_chunk_size - Compute the max size that fits within the
 * contig. page from the given size
 * @substream: PCM substream
 * @ofs: byte offset
 * @size: byte size to examine
 */
अटल अंतरभूत अचिन्हित पूर्णांक
snd_pcm_sgbuf_get_chunk_size(काष्ठा snd_pcm_substream *substream,
			     अचिन्हित पूर्णांक ofs, अचिन्हित पूर्णांक size)
अणु
	वापस snd_sgbuf_get_chunk_size(snd_pcm_get_dma_buf(substream), ofs, size);
पूर्ण

/**
 * snd_pcm_mmap_data_खोलो - increase the mmap counter
 * @area: VMA
 *
 * PCM mmap callback should handle this counter properly
 */
अटल अंतरभूत व्योम snd_pcm_mmap_data_खोलो(काष्ठा vm_area_काष्ठा *area)
अणु
	काष्ठा snd_pcm_substream *substream = (काष्ठा snd_pcm_substream *)area->vm_निजी_data;
	atomic_inc(&substream->mmap_count);
पूर्ण

/**
 * snd_pcm_mmap_data_बंद - decrease the mmap counter
 * @area: VMA
 *
 * PCM mmap callback should handle this counter properly
 */
अटल अंतरभूत व्योम snd_pcm_mmap_data_बंद(काष्ठा vm_area_काष्ठा *area)
अणु
	काष्ठा snd_pcm_substream *substream = (काष्ठा snd_pcm_substream *)area->vm_निजी_data;
	atomic_dec(&substream->mmap_count);
पूर्ण

पूर्णांक snd_pcm_lib_शेष_mmap(काष्ठा snd_pcm_substream *substream,
			     काष्ठा vm_area_काष्ठा *area);
/* mmap क्रम io-memory area */
#अगर defined(CONFIG_X86) || defined(CONFIG_PPC) || defined(CONFIG_ALPHA)
#घोषणा SNDRV_PCM_INFO_MMAP_IOMEM	SNDRV_PCM_INFO_MMAP
पूर्णांक snd_pcm_lib_mmap_iomem(काष्ठा snd_pcm_substream *substream, काष्ठा vm_area_काष्ठा *area);
#अन्यथा
#घोषणा SNDRV_PCM_INFO_MMAP_IOMEM	0
#घोषणा snd_pcm_lib_mmap_iomem	शून्य
#पूर्ण_अगर

/**
 * snd_pcm_limit_isa_dma_size - Get the max size fitting with ISA DMA transfer
 * @dma: DMA number
 * @max: poपूर्णांकer to store the max size
 */
अटल अंतरभूत व्योम snd_pcm_limit_isa_dma_size(पूर्णांक dma, माप_प्रकार *max)
अणु
	*max = dma < 4 ? 64 * 1024 : 128 * 1024;
पूर्ण

/*
 *  Misc
 */

#घोषणा SNDRV_PCM_DEFAULT_CON_SPDIF	(IEC958_AES0_CON_EMPHASIS_NONE|\
					 (IEC958_AES1_CON_ORIGINAL<<8)|\
					 (IEC958_AES1_CON_PCM_CODER<<8)|\
					 (IEC958_AES3_CON_FS_48000<<24))

स्थिर अक्षर *snd_pcm_क्रमmat_name(snd_pcm_क्रमmat_t क्रमmat);

/**
 * snd_pcm_stream_str - Get a string naming the direction of a stream
 * @substream: the pcm substream instance
 *
 * Return: A string naming the direction of the stream.
 */
अटल अंतरभूत स्थिर अक्षर *snd_pcm_stream_str(काष्ठा snd_pcm_substream *substream)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस "Playback";
	अन्यथा
		वापस "Capture";
पूर्ण

/*
 * PCM channel-mapping control API
 */
/* array element of channel maps */
काष्ठा snd_pcm_chmap_elem अणु
	अचिन्हित अक्षर channels;
	अचिन्हित अक्षर map[15];
पूर्ण;

/* channel map inक्रमmation; retrieved via snd_kcontrol_chip() */
काष्ठा snd_pcm_chmap अणु
	काष्ठा snd_pcm *pcm;	/* asचिन्हित PCM instance */
	पूर्णांक stream;		/* PLAYBACK or CAPTURE */
	काष्ठा snd_kcontrol *kctl;
	स्थिर काष्ठा snd_pcm_chmap_elem *chmap;
	अचिन्हित पूर्णांक max_channels;
	अचिन्हित पूर्णांक channel_mask;	/* optional: active channels biपंचांगask */
	व्योम *निजी_data;	/* optional: निजी data poपूर्णांकer */
पूर्ण;

/**
 * snd_pcm_chmap_substream - get the PCM substream asचिन्हित to the given chmap info
 * @info: chmap inक्रमmation
 * @idx: the substream number index
 */
अटल अंतरभूत काष्ठा snd_pcm_substream *
snd_pcm_chmap_substream(काष्ठा snd_pcm_chmap *info, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा snd_pcm_substream *s;
	क्रम (s = info->pcm->streams[info->stream].substream; s; s = s->next)
		अगर (s->number == idx)
			वापस s;
	वापस शून्य;
पूर्ण

/* ALSA-standard channel maps (RL/RR prior to C/LFE) */
बाह्य स्थिर काष्ठा snd_pcm_chmap_elem snd_pcm_std_chmaps[];
/* Other world's standard channel maps (C/LFE prior to RL/RR) */
बाह्य स्थिर काष्ठा snd_pcm_chmap_elem snd_pcm_alt_chmaps[];

/* bit masks to be passed to snd_pcm_chmap.channel_mask field */
#घोषणा SND_PCM_CHMAP_MASK_24	((1U << 2) | (1U << 4))
#घोषणा SND_PCM_CHMAP_MASK_246	(SND_PCM_CHMAP_MASK_24 | (1U << 6))
#घोषणा SND_PCM_CHMAP_MASK_2468	(SND_PCM_CHMAP_MASK_246 | (1U << 8))

पूर्णांक snd_pcm_add_chmap_ctls(काष्ठा snd_pcm *pcm, पूर्णांक stream,
			   स्थिर काष्ठा snd_pcm_chmap_elem *chmap,
			   पूर्णांक max_channels,
			   अचिन्हित दीर्घ निजी_value,
			   काष्ठा snd_pcm_chmap **info_ret);

/**
 * pcm_क्रमmat_to_bits - Strong-typed conversion of pcm_क्रमmat to bitwise
 * @pcm_क्रमmat: PCM क्रमmat
 */
अटल अंतरभूत u64 pcm_क्रमmat_to_bits(snd_pcm_क्रमmat_t pcm_क्रमmat)
अणु
	वापस 1ULL << (__क्रमce पूर्णांक) pcm_क्रमmat;
पूर्ण

/**
 * pcm_क्रम_each_क्रमmat - helper to iterate क्रम each क्रमmat type
 * @f: the iterator variable in snd_pcm_क्रमmat_t type
 */
#घोषणा pcm_क्रम_each_क्रमmat(f)						\
	क्रम ((f) = SNDRV_PCM_FORMAT_FIRST;				\
	     (__क्रमce पूर्णांक)(f) <= (__क्रमce पूर्णांक)SNDRV_PCM_FORMAT_LAST;	\
	     (f) = (__क्रमce snd_pcm_क्रमmat_t)((__क्रमce पूर्णांक)(f) + 1))

/* prपूर्णांकk helpers */
#घोषणा pcm_err(pcm, fmt, args...) \
	dev_err((pcm)->card->dev, fmt, ##args)
#घोषणा pcm_warn(pcm, fmt, args...) \
	dev_warn((pcm)->card->dev, fmt, ##args)
#घोषणा pcm_dbg(pcm, fmt, args...) \
	dev_dbg((pcm)->card->dev, fmt, ##args)

काष्ठा snd_pcm_status64 अणु
	snd_pcm_state_t state;		/* stream state */
	u8 rsvd[4];
	s64 trigger_tstamp_sec;		/* समय when stream was started/stopped/छोड़ोd */
	s64 trigger_tstamp_nsec;
	s64 tstamp_sec;			/* reference बारtamp */
	s64 tstamp_nsec;
	snd_pcm_uframes_t appl_ptr;	/* appl ptr */
	snd_pcm_uframes_t hw_ptr;	/* hw ptr */
	snd_pcm_sframes_t delay;	/* current delay in frames */
	snd_pcm_uframes_t avail;	/* number of frames available */
	snd_pcm_uframes_t avail_max;	/* max frames available on hw since last status */
	snd_pcm_uframes_t overrange;	/* count of ADC (capture) overrange detections from last status */
	snd_pcm_state_t suspended_state; /* suspended stream state */
	__u32 audio_tstamp_data;	 /* needed क्रम 64-bit alignment, used क्रम configs/report to/from userspace */
	s64 audio_tstamp_sec;		/* sample counter, wall घड़ी, PHC or on-demand sync'ed */
	s64 audio_tstamp_nsec;
	s64 driver_tstamp_sec;		/* useful in हाल reference प्रणाली tstamp is reported with delay */
	s64 driver_tstamp_nsec;
	__u32 audio_tstamp_accuracy;	/* in ns units, only valid अगर indicated in audio_tstamp_data */
	अचिन्हित अक्षर reserved[52-4*माप(s64)]; /* must be filled with zero */
पूर्ण;

#घोषणा SNDRV_PCM_IOCTL_STATUS64	_IOR('A', 0x20, काष्ठा snd_pcm_status64)
#घोषणा SNDRV_PCM_IOCTL_STATUS_EXT64	_IOWR('A', 0x24, काष्ठा snd_pcm_status64)

काष्ठा snd_pcm_status32 अणु
	snd_pcm_state_t state;		/* stream state */
	s32 trigger_tstamp_sec;	/* समय when stream was started/stopped/छोड़ोd */
	s32 trigger_tstamp_nsec;
	s32 tstamp_sec;		/* reference बारtamp */
	s32 tstamp_nsec;
	u32 appl_ptr;		/* appl ptr */
	u32 hw_ptr;		/* hw ptr */
	s32 delay;		/* current delay in frames */
	u32 avail;		/* number of frames available */
	u32 avail_max;		/* max frames available on hw since last status */
	u32 overrange;		/* count of ADC (capture) overrange detections from last status */
	snd_pcm_state_t suspended_state;	/* suspended stream state */
	u32 audio_tstamp_data;	/* needed क्रम 64-bit alignment, used क्रम configs/report to/from userspace */
	s32 audio_tstamp_sec;	/* sample counter, wall घड़ी, PHC or on-demand sync'ed */
	s32 audio_tstamp_nsec;
	s32 driver_tstamp_sec;	/* useful in हाल reference प्रणाली tstamp is reported with delay */
	s32 driver_tstamp_nsec;
	u32 audio_tstamp_accuracy;	/* in ns units, only valid अगर indicated in audio_tstamp_data */
	अचिन्हित अक्षर reserved[52-4*माप(s32)]; /* must be filled with zero */
पूर्ण;

#घोषणा SNDRV_PCM_IOCTL_STATUS32	_IOR('A', 0x20, काष्ठा snd_pcm_status32)
#घोषणा SNDRV_PCM_IOCTL_STATUS_EXT32	_IOWR('A', 0x24, काष्ठा snd_pcm_status32)

#पूर्ण_अगर /* __SOUND_PCM_H */
