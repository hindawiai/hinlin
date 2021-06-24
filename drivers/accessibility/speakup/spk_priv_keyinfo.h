<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* spk_priv.h
 * review functions क्रम the speakup screen review package.
 * originally written by: Kirk Reiser and Andy Berdan.
 *
 * extensively modअगरied by David Borowski.
 *
 * Copyright (C) 1998  Kirk Reiser.
 * Copyright (C) 2003  David Borowski.
 */

#अगर_अघोषित _SPEAKUP_KEYINFO_H
#घोषणा _SPEAKUP_KEYINFO_H

#घोषणा FIRST_SYNTH_VAR RATE
/* 0 is reserved क्रम no remap */
#घोषणा SPEAKUP_GOTO		0x01
#घोषणा SPEECH_KILL		0x02
#घोषणा SPEAKUP_QUIET		0x03
#घोषणा SPEAKUP_CUT		0x04
#घोषणा SPEAKUP_PASTE		0x05
#घोषणा SAY_FIRST_CHAR		0x06
#घोषणा SAY_LAST_CHAR		0x07
#घोषणा SAY_CHAR		0x08
#घोषणा SAY_PREV_CHAR		0x09
#घोषणा SAY_NEXT_CHAR		0x0a
#घोषणा SAY_WORD		0x0b
#घोषणा SAY_PREV_WORD		0x0c
#घोषणा SAY_NEXT_WORD		0x0d
#घोषणा SAY_LINE		0x0e
#घोषणा SAY_PREV_LINE		0x0f
#घोषणा SAY_NEXT_LINE		0x10
#घोषणा TOP_EDGE		0x11
#घोषणा BOTTOM_EDGE		0x12
#घोषणा LEFT_EDGE		0x13
#घोषणा RIGHT_EDGE		0x14
#घोषणा SPELL_PHONETIC		0x15
#घोषणा SPELL_WORD		0x16
#घोषणा SAY_SCREEN		0x17
#घोषणा SAY_POSITION		0x18
#घोषणा SAY_ATTRIBUTES		0x19
#घोषणा SPEAKUP_OFF		0x1a
#घोषणा SPEAKUP_PARKED		0x1b
#घोषणा SAY_LINE_INDENT	0x1c
#घोषणा SAY_FROM_TOP		0x1d
#घोषणा SAY_TO_BOTTOM		0x1e
#घोषणा SAY_FROM_LEFT		0x1f
#घोषणा SAY_TO_RIGHT		0x20
#घोषणा SAY_CHAR_NUM		0x21
#घोषणा EDIT_SOME		0x22
#घोषणा EDIT_MOST		0x23
#घोषणा SAY_PHONETIC_CHAR	0x24
#घोषणा EDIT_DELIM		0x25
#घोषणा EDIT_REPEAT		0x26
#घोषणा EDIT_EXNUM		0x27
#घोषणा SET_WIN		0x28
#घोषणा CLEAR_WIN		0x29
#घोषणा ENABLE_WIN		0x2a
#घोषणा SAY_WIN		0x2b
#घोषणा SPK_LOCK		0x2c
#घोषणा SPEAKUP_HELP		0x2d
#घोषणा TOGGLE_CURSORING	0x2e
#घोषणा READ_ALL_DOC		0x2f

/* one greater than the last func handler */
#घोषणा SPKUP_MAX_FUNC		0x30

#घोषणा SPK_KEY		0x80
#घोषणा FIRST_EDIT_BITS	0x22
#घोषणा FIRST_SET_VAR SPELL_DELAY

/* increase अगर adding more than 0x3f functions */
#घोषणा VAR_START		0x40

/* keys क्रम setting variables, must be ordered same as the क्रमागत क्रम var_ids */
/* with dec being even and inc being 1 greater */
#घोषणा SPELL_DELAY_DEC (VAR_START + 0)
#घोषणा SPELL_DELAY_INC (SPELL_DELAY_DEC + 1)
#घोषणा PUNC_LEVEL_DEC (SPELL_DELAY_DEC + 2)
#घोषणा PUNC_LEVEL_INC (PUNC_LEVEL_DEC + 1)
#घोषणा READING_PUNC_DEC (PUNC_LEVEL_DEC + 2)
#घोषणा READING_PUNC_INC (READING_PUNC_DEC + 1)
#घोषणा ATTRIB_BLEEP_DEC (READING_PUNC_DEC + 2)
#घोषणा ATTRIB_BLEEP_INC (ATTRIB_BLEEP_DEC + 1)
#घोषणा BLEEPS_DEC (ATTRIB_BLEEP_DEC + 2)
#घोषणा BLEEPS_INC (BLEEPS_DEC + 1)
#घोषणा RATE_DEC (BLEEPS_DEC + 2)
#घोषणा RATE_INC (RATE_DEC + 1)
#घोषणा PITCH_DEC (RATE_DEC + 2)
#घोषणा PITCH_INC (PITCH_DEC + 1)
#घोषणा VOL_DEC (PITCH_DEC + 2)
#घोषणा VOL_INC (VOL_DEC + 1)
#घोषणा TONE_DEC (VOL_DEC + 2)
#घोषणा TONE_INC (TONE_DEC + 1)
#घोषणा PUNCT_DEC (TONE_DEC + 2)
#घोषणा PUNCT_INC (PUNCT_DEC + 1)
#घोषणा VOICE_DEC (PUNCT_DEC + 2)
#घोषणा VOICE_INC (VOICE_DEC + 1)

#पूर्ण_अगर
