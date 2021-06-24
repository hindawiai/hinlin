<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_EMUX_LEGACY_H
#घोषणा __SOUND_EMUX_LEGACY_H

/*
 *  Copyright (c) 1999-2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Definitions of OSS compatible headers क्रम Emu8000 device inक्रमmations
 */

#समावेश <sound/seq_oss_legacy.h>

/*
 * awe hardware controls
 */

#घोषणा _EMUX_OSS_DEBUG_MODE		0x00
#घोषणा _EMUX_OSS_REVERB_MODE		0x01
#घोषणा _EMUX_OSS_CHORUS_MODE		0x02
#घोषणा _EMUX_OSS_REMOVE_LAST_SAMPLES	0x03
#घोषणा _EMUX_OSS_INITIALIZE_CHIP	0x04
#घोषणा _EMUX_OSS_SEND_EFFECT		0x05
#घोषणा _EMUX_OSS_TERMINATE_CHANNEL	0x06
#घोषणा _EMUX_OSS_TERMINATE_ALL		0x07
#घोषणा _EMUX_OSS_INITIAL_VOLUME	0x08
#घोषणा _EMUX_OSS_INITIAL_ATTEN	_EMUX_OSS_INITIAL_VOLUME
#घोषणा _EMUX_OSS_RESET_CHANNEL		0x09
#घोषणा _EMUX_OSS_CHANNEL_MODE		0x0a
#घोषणा _EMUX_OSS_DRUM_CHANNELS		0x0b
#घोषणा _EMUX_OSS_MISC_MODE		0x0c
#घोषणा _EMUX_OSS_RELEASE_ALL		0x0d
#घोषणा _EMUX_OSS_NOTखातापूर्णF_ALL		0x0e
#घोषणा _EMUX_OSS_CHN_PRESSURE		0x0f
#घोषणा _EMUX_OSS_EQUALIZER		0x11

#घोषणा _EMUX_OSS_MODE_FLAG		0x80
#घोषणा _EMUX_OSS_COOKED_FLAG		0x40	/* not supported */
#घोषणा _EMUX_OSS_MODE_VALUE_MASK	0x3F


/*
 * mode type definitions
 */
क्रमागत अणु
/* 0*/	EMUX_MD_EXCLUSIVE_OFF,	/* obsolete */
/* 1*/	EMUX_MD_EXCLUSIVE_ON,	/* obsolete */
/* 2*/	EMUX_MD_VERSION,		/* पढ़ो only */
/* 3*/	EMUX_MD_EXCLUSIVE_SOUND,	/* 0/1: exclusive note on (शेष=1) */
/* 4*/	EMUX_MD_REALTIME_PAN,	/* 0/1: करो realसमय pan change (शेष=1) */
/* 5*/	EMUX_MD_GUS_BANK,	/* bank number क्रम GUS patches (शेष=0) */
/* 6*/	EMUX_MD_KEEP_EFFECT,	/* 0/1: keep effect values, (शेष=0) */
/* 7*/	EMUX_MD_ZERO_ATTEN,	/* attenuation of max volume (शेष=32) */
/* 8*/	EMUX_MD_CHN_PRIOR,	/* 0/1: set MIDI channel priority mode (शेष=1) */
/* 9*/	EMUX_MD_MOD_SENSE,	/* पूर्णांकeger: modwheel sensitivity (def=18) */
/*10*/	EMUX_MD_DEF_PRESET,	/* पूर्णांकeger: शेष preset number (def=0) */
/*11*/	EMUX_MD_DEF_BANK,	/* पूर्णांकeger: शेष bank number (def=0) */
/*12*/	EMUX_MD_DEF_DRUM,	/* पूर्णांकeger: शेष drumset number (def=0) */
/*13*/	EMUX_MD_TOGGLE_DRUM_BANK, /* 0/1: toggle drum flag with bank# (def=0) */
/*14*/	EMUX_MD_NEW_VOLUME_CALC,	/* 0/1: volume calculation mode (def=1) */
/*15*/	EMUX_MD_CHORUS_MODE,	/* पूर्णांकeger: chorus mode (def=2) */
/*16*/	EMUX_MD_REVERB_MODE,	/* पूर्णांकeger: chorus mode (def=4) */
/*17*/	EMUX_MD_BASS_LEVEL,	/* पूर्णांकeger: bass level (def=5) */
/*18*/	EMUX_MD_TREBLE_LEVEL,	/* पूर्णांकeger: treble level (def=9) */
/*19*/	EMUX_MD_DEBUG_MODE,	/* पूर्णांकeger: debug level (def=0) */
/*20*/	EMUX_MD_PAN_EXCHANGE,	/* 0/1: exchange panning direction (def=0) */
	EMUX_MD_END,
पूर्ण;


/*
 * effect parameters
 */
क्रमागत अणु

/* modulation envelope parameters */
/* 0*/	EMUX_FX_ENV1_DELAY,	/* WORD: ENVVAL */
/* 1*/	EMUX_FX_ENV1_ATTACK,	/* BYTE: up ATKHLD */
/* 2*/	EMUX_FX_ENV1_HOLD,	/* BYTE: lw ATKHLD */
/* 3*/	EMUX_FX_ENV1_DECAY,	/* BYTE: lw DCYSUS */
/* 4*/	EMUX_FX_ENV1_RELEASE,	/* BYTE: lw DCYSUS */
/* 5*/	EMUX_FX_ENV1_SUSTAIN,	/* BYTE: up DCYSUS */
/* 6*/	EMUX_FX_ENV1_PITCH,	/* BYTE: up PEFE */
/* 7*/	EMUX_FX_ENV1_CUTOFF,	/* BYTE: lw PEFE */

/* volume envelope parameters */
/* 8*/	EMUX_FX_ENV2_DELAY,	/* WORD: ENVVOL */
/* 9*/	EMUX_FX_ENV2_ATTACK,	/* BYTE: up ATKHLDV */
/*10*/	EMUX_FX_ENV2_HOLD,	/* BYTE: lw ATKHLDV */
/*11*/	EMUX_FX_ENV2_DECAY,	/* BYTE: lw DCYSUSV */
/*12*/	EMUX_FX_ENV2_RELEASE,	/* BYTE: lw DCYSUSV */
/*13*/	EMUX_FX_ENV2_SUSTAIN,	/* BYTE: up DCYSUSV */
	
/* LFO1 (tremolo & vibrato) parameters */
/*14*/	EMUX_FX_LFO1_DELAY,	/* WORD: LFO1VAL */
/*15*/	EMUX_FX_LFO1_FREQ,	/* BYTE: lo TREMFRQ */
/*16*/	EMUX_FX_LFO1_VOLUME,	/* BYTE: up TREMFRQ */
/*17*/	EMUX_FX_LFO1_PITCH,	/* BYTE: up FMMOD */
/*18*/	EMUX_FX_LFO1_CUTOFF,	/* BYTE: lo FMMOD */

/* LFO2 (vibrato) parameters */
/*19*/	EMUX_FX_LFO2_DELAY,	/* WORD: LFO2VAL */
/*20*/	EMUX_FX_LFO2_FREQ,	/* BYTE: lo FM2FRQ2 */
/*21*/	EMUX_FX_LFO2_PITCH,	/* BYTE: up FM2FRQ2 */

/* Other overall effect parameters */
/*22*/	EMUX_FX_INIT_PITCH,	/* SHORT: pitch offset */
/*23*/	EMUX_FX_CHORUS,		/* BYTE: chorus effects send (0-255) */
/*24*/	EMUX_FX_REVERB,		/* BYTE: reverb effects send (0-255) */
/*25*/	EMUX_FX_CUTOFF,		/* BYTE: up IFATN */
/*26*/	EMUX_FX_FILTERQ,		/* BYTE: up CCCA */

/* Sample / loop offset changes */
/*27*/	EMUX_FX_SAMPLE_START,	/* SHORT: offset */
/*28*/	EMUX_FX_LOOP_START,	/* SHORT: offset */
/*29*/	EMUX_FX_LOOP_END,	/* SHORT: offset */
/*30*/	EMUX_FX_COARSE_SAMPLE_START,	/* SHORT: upper word offset */
/*31*/	EMUX_FX_COARSE_LOOP_START,	/* SHORT: upper word offset */
/*32*/	EMUX_FX_COARSE_LOOP_END,		/* SHORT: upper word offset */
/*33*/	EMUX_FX_ATTEN,		/* BYTE: lo IFATN */

	EMUX_FX_END,
पूर्ण;
/* number of effects */
#घोषणा EMUX_NUM_EFFECTS  EMUX_FX_END

/* effect flag values */
#घोषणा EMUX_FX_FLAG_OFF	0
#घोषणा EMUX_FX_FLAG_SET	1
#घोषणा EMUX_FX_FLAG_ADD	2


#पूर्ण_अगर /* __SOUND_EMUX_LEGACY_H */
