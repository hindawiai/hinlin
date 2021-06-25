<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __EMUX_VOICE_H
#घोषणा __EMUX_VOICE_H

/*
 * A काष्ठाure to keep track of each hardware voice
 *
 *  Copyright (C) 1999 Steve Ratclअगरfe
 *  Copyright (c) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <sound/core.h>
#समावेश <sound/emux_synth.h>

/* Prototypes क्रम emux_seq.c */
पूर्णांक snd_emux_init_seq(काष्ठा snd_emux *emu, काष्ठा snd_card *card, पूर्णांक index);
व्योम snd_emux_detach_seq(काष्ठा snd_emux *emu);
काष्ठा snd_emux_port *snd_emux_create_port(काष्ठा snd_emux *emu, अक्षर *name,
					   पूर्णांक max_channels, पूर्णांक type,
					   काष्ठा snd_seq_port_callback *callback);
व्योम snd_emux_reset_port(काष्ठा snd_emux_port *port);
पूर्णांक snd_emux_event_input(काष्ठा snd_seq_event *ev, पूर्णांक direct, व्योम *निजी,
			 पूर्णांक atomic, पूर्णांक hop);
पूर्णांक snd_emux_inc_count(काष्ठा snd_emux *emu);
व्योम snd_emux_dec_count(काष्ठा snd_emux *emu);
पूर्णांक snd_emux_init_virmidi(काष्ठा snd_emux *emu, काष्ठा snd_card *card);
पूर्णांक snd_emux_delete_virmidi(काष्ठा snd_emux *emu);

/* Prototypes क्रम emux_synth.c */
व्योम snd_emux_init_voices(काष्ठा snd_emux *emu);

व्योम snd_emux_note_on(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan);
व्योम snd_emux_note_off(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan);
व्योम snd_emux_key_press(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan);
व्योम snd_emux_terminate_note(व्योम *p, पूर्णांक note, काष्ठा snd_midi_channel *chan);
व्योम snd_emux_control(व्योम *p, पूर्णांक type, काष्ठा snd_midi_channel *chan);

व्योम snd_emux_sounds_off_all(काष्ठा snd_emux_port *port);
व्योम snd_emux_update_channel(काष्ठा snd_emux_port *port,
			     काष्ठा snd_midi_channel *chan, पूर्णांक update);
व्योम snd_emux_update_port(काष्ठा snd_emux_port *port, पूर्णांक update);

व्योम snd_emux_समयr_callback(काष्ठा समयr_list *t);

/* emux_effect.c */
#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
व्योम snd_emux_create_effect(काष्ठा snd_emux_port *p);
व्योम snd_emux_delete_effect(काष्ठा snd_emux_port *p);
व्योम snd_emux_clear_effect(काष्ठा snd_emux_port *p);
व्योम snd_emux_setup_effect(काष्ठा snd_emux_voice *vp);
व्योम snd_emux_send_effect_oss(काष्ठा snd_emux_port *port,
			      काष्ठा snd_midi_channel *chan, पूर्णांक type, पूर्णांक val);
व्योम snd_emux_send_effect(काष्ठा snd_emux_port *port,
			  काष्ठा snd_midi_channel *chan, पूर्णांक type, पूर्णांक val, पूर्णांक mode);
#पूर्ण_अगर

/* emux_nrpn.c */
व्योम snd_emux_sysex(व्योम *निजी_data, अचिन्हित अक्षर *buf, पूर्णांक len,
		    पूर्णांक parsed, काष्ठा snd_midi_channel_set *chset);
पूर्णांक snd_emux_xg_control(काष्ठा snd_emux_port *port,
			काष्ठा snd_midi_channel *chan, पूर्णांक param);
व्योम snd_emux_nrpn(व्योम *निजी_data, काष्ठा snd_midi_channel *chan,
		   काष्ठा snd_midi_channel_set *chset);

/* emux_oss.c */
व्योम snd_emux_init_seq_oss(काष्ठा snd_emux *emu);
व्योम snd_emux_detach_seq_oss(काष्ठा snd_emux *emu);

/* emux_proc.c */
#अगर_घोषित CONFIG_SND_PROC_FS
व्योम snd_emux_proc_init(काष्ठा snd_emux *emu, काष्ठा snd_card *card, पूर्णांक device);
व्योम snd_emux_proc_मुक्त(काष्ठा snd_emux *emu);
#अन्यथा
अटल अंतरभूत व्योम snd_emux_proc_init(काष्ठा snd_emux *emu,
				      काष्ठा snd_card *card, पूर्णांक device) अणुपूर्ण
अटल अंतरभूत व्योम snd_emux_proc_मुक्त(काष्ठा snd_emux *emu) अणुपूर्ण
#पूर्ण_अगर

#घोषणा STATE_IS_PLAYING(s) ((s) & SNDRV_EMUX_ST_ON)

/* emux_hwdep.c */
पूर्णांक snd_emux_init_hwdep(काष्ठा snd_emux *emu);
व्योम snd_emux_delete_hwdep(काष्ठा snd_emux *emu);

#पूर्ण_अगर
