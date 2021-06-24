<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) 1999 by Uros Bizjak <uros@kss-loka.si>
 *                        Takashi Iwai <tiwai@suse.de>
 *
 *  SB16ASP/AWE32 CSP control
 */
#अगर_अघोषित __SOUND_SB16_CSP_H
#घोषणा __SOUND_SB16_CSP_H

#समावेश <sound/sb.h>
#समावेश <sound/hwdep.h>
#समावेश <linux/firmware.h>
#समावेश <uapi/sound/sb16_csp.h>

काष्ठा snd_sb_csp;

/* indices क्रम the known CSP programs */
क्रमागत अणु
	CSP_PROGRAM_MULAW,
	CSP_PROGRAM_ALAW,
	CSP_PROGRAM_ADPCM_INIT,
	CSP_PROGRAM_ADPCM_PLAYBACK,
	CSP_PROGRAM_ADPCM_CAPTURE,

	CSP_PROGRAM_COUNT
पूर्ण;

/*
 * CSP चालकs
 */
काष्ठा snd_sb_csp_ops अणु
	पूर्णांक (*csp_use) (काष्ठा snd_sb_csp * p);
	पूर्णांक (*csp_unuse) (काष्ठा snd_sb_csp * p);
	पूर्णांक (*csp_स्वतःload) (काष्ठा snd_sb_csp * p, snd_pcm_क्रमmat_t pcm_sfmt, पूर्णांक play_rec_mode);
	पूर्णांक (*csp_start) (काष्ठा snd_sb_csp * p, पूर्णांक sample_width, पूर्णांक channels);
	पूर्णांक (*csp_stop) (काष्ठा snd_sb_csp * p);
	पूर्णांक (*csp_qsound_transfer) (काष्ठा snd_sb_csp * p);
पूर्ण;

/*
 * CSP निजी data
 */
काष्ठा snd_sb_csp अणु
	काष्ठा snd_sb *chip;		/* SB16 DSP */
	पूर्णांक used;		/* usage flag - exclusive */
	अक्षर codec_name[16];	/* name of codec */
	अचिन्हित लघु func_nr;	/* function number */
	अचिन्हित पूर्णांक acc_क्रमmat;	/* accepted PCM क्रमmats */
	पूर्णांक acc_channels;	/* accepted channels */
	पूर्णांक acc_width;		/* accepted sample width */
	पूर्णांक acc_rates;		/* accepted sample rates */
	पूर्णांक mode;		/* MODE */
	पूर्णांक run_channels;	/* current CSP channels */
	पूर्णांक run_width;		/* current sample width */
	पूर्णांक version;		/* CSP version (0x10 - 0x1f) */
	पूर्णांक running;		/* running state */

	काष्ठा snd_sb_csp_ops ops;	/* चालकs */

	spinlock_t q_lock;	/* locking */
	पूर्णांक q_enabled;		/* enabled flag */
	पूर्णांक qpos_left;		/* left position */
	पूर्णांक qpos_right;		/* right position */
	पूर्णांक qpos_changed;	/* position changed flag */

	काष्ठा snd_kcontrol *qsound_चयन;
	काष्ठा snd_kcontrol *qsound_space;

	काष्ठा mutex access_mutex;	/* locking */

	स्थिर काष्ठा firmware *csp_programs[CSP_PROGRAM_COUNT];
पूर्ण;

पूर्णांक snd_sb_csp_new(काष्ठा snd_sb *chip, पूर्णांक device, काष्ठा snd_hwdep ** rhwdep);
#पूर्ण_अगर /* __SOUND_SB16_CSP */
