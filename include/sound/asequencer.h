<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Main header file क्रम the ALSA sequencer
 *  Copyright (c) 1998-1999 by Frank van de Pol <fvdpol@coil.demon.nl>
 *            (c) 1998-1999 by Jaroslav Kysela <perex@perex.cz>
 */
#अगर_अघोषित __SOUND_ASEQUENCER_H
#घोषणा __SOUND_ASEQUENCER_H

#समावेश <linux/ioctl.h>
#समावेश <sound/asound.h>
#समावेश <uapi/sound/asequencer.h>

/* helper macro */
#घोषणा snd_seq_event_bounce_ext_data(ev) ((व्योम*)((अक्षर *)(ev)->data.ext.ptr + माप(काष्ठा snd_seq_event_bounce)))

/*
 * type check macros
 */
/* result events: 0-4 */
#घोषणा snd_seq_ev_is_result_type(ev)	((ev)->type < 5)
/* channel specअगरic events: 5-19 */
#घोषणा snd_seq_ev_is_channel_type(ev)	((ev)->type >= 5 && (ev)->type < 20)
/* note events: 5-9 */
#घोषणा snd_seq_ev_is_note_type(ev)	((ev)->type >= 5 && (ev)->type < 10)
/* control events: 10-19 */
#घोषणा snd_seq_ev_is_control_type(ev)	((ev)->type >= 10 && (ev)->type < 20)
/* queue control events: 30-39 */
#घोषणा snd_seq_ev_is_queue_type(ev)	((ev)->type >= 30 && (ev)->type < 40)
/* प्रणाली status messages */
#घोषणा snd_seq_ev_is_message_type(ev)	((ev)->type >= 60 && (ev)->type < 69)
/* sample messages */
#घोषणा snd_seq_ev_is_sample_type(ev)	((ev)->type >= 70 && (ev)->type < 79)
/* user-defined messages */
#घोषणा snd_seq_ev_is_user_type(ev)	((ev)->type >= 90 && (ev)->type < 99)
/* fixed length events: 0-99 */
#घोषणा snd_seq_ev_is_fixed_type(ev)	((ev)->type < 100)
/* variable length events: 130-139 */
#घोषणा snd_seq_ev_is_variable_type(ev)	((ev)->type >= 130 && (ev)->type < 140)
/* reserved क्रम kernel */
#घोषणा snd_seq_ev_is_reserved(ev)	((ev)->type >= 150)

/* direct dispatched events */
#घोषणा snd_seq_ev_is_direct(ev)	((ev)->queue == SNDRV_SEQ_QUEUE_सूचीECT)

/*
 * macros to check event flags
 */
/* prior events */
#घोषणा snd_seq_ev_is_prior(ev)		(((ev)->flags & SNDRV_SEQ_PRIORITY_MASK) == SNDRV_SEQ_PRIORITY_HIGH)

/* event length type */
#घोषणा snd_seq_ev_length_type(ev)	((ev)->flags & SNDRV_SEQ_EVENT_LENGTH_MASK)
#घोषणा snd_seq_ev_is_fixed(ev)		(snd_seq_ev_length_type(ev) == SNDRV_SEQ_EVENT_LENGTH_FIXED)
#घोषणा snd_seq_ev_is_variable(ev)	(snd_seq_ev_length_type(ev) == SNDRV_SEQ_EVENT_LENGTH_VARIABLE)
#घोषणा snd_seq_ev_is_varusr(ev)	(snd_seq_ev_length_type(ev) == SNDRV_SEQ_EVENT_LENGTH_VARUSR)

/* समय-stamp type */
#घोषणा snd_seq_ev_बारtamp_type(ev)	((ev)->flags & SNDRV_SEQ_TIME_STAMP_MASK)
#घोषणा snd_seq_ev_is_tick(ev)		(snd_seq_ev_बारtamp_type(ev) == SNDRV_SEQ_TIME_STAMP_TICK)
#घोषणा snd_seq_ev_is_real(ev)		(snd_seq_ev_बारtamp_type(ev) == SNDRV_SEQ_TIME_STAMP_REAL)

/* समय-mode type */
#घोषणा snd_seq_ev_समयmode_type(ev)	((ev)->flags & SNDRV_SEQ_TIME_MODE_MASK)
#घोषणा snd_seq_ev_is_असलसमय(ev)	(snd_seq_ev_समयmode_type(ev) == SNDRV_SEQ_TIME_MODE_ABS)
#घोषणा snd_seq_ev_is_relसमय(ev)	(snd_seq_ev_समयmode_type(ev) == SNDRV_SEQ_TIME_MODE_REL)

/* queue sync port */
#घोषणा snd_seq_queue_sync_port(q)	((q) + 16)

#पूर्ण_अगर /* __SOUND_ASEQUENCER_H */
