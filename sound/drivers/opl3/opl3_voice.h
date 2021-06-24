<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __OPL3_VOICE_H
#घोषणा __OPL3_VOICE_H

/*
 *  Copyright (c) 2000 Uros Bizjak <uros@kss-loka.si>
 */

#समावेश <sound/opl3.h>

/* Prototypes क्रम opl3_seq.c */
पूर्णांक snd_opl3_synth_use_inc(काष्ठा snd_opl3 * opl3);
व्योम snd_opl3_synth_use_dec(काष्ठा snd_opl3 * opl3);
पूर्णांक snd_opl3_synth_setup(काष्ठा snd_opl3 * opl3);
व्योम snd_opl3_synth_cleanup(काष्ठा snd_opl3 * opl3);

/* Prototypes क्रम opl3_midi.c */
व्योम snd_opl3_note_on(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan);
व्योम snd_opl3_note_off(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan);
व्योम snd_opl3_key_press(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan);
व्योम snd_opl3_terminate_note(व्योम *p, पूर्णांक note, काष्ठा snd_midi_channel *chan);
व्योम snd_opl3_control(व्योम *p, पूर्णांक type, काष्ठा snd_midi_channel *chan);
व्योम snd_opl3_nrpn(व्योम *p, काष्ठा snd_midi_channel *chan, काष्ठा snd_midi_channel_set *chset);
व्योम snd_opl3_sysex(व्योम *p, अचिन्हित अक्षर *buf, पूर्णांक len, पूर्णांक parsed, काष्ठा snd_midi_channel_set *chset);

व्योम snd_opl3_calc_volume(अचिन्हित अक्षर *reg, पूर्णांक vel, काष्ठा snd_midi_channel *chan);
व्योम snd_opl3_समयr_func(काष्ठा समयr_list *t);

/* Prototypes क्रम opl3_drums.c */
व्योम snd_opl3_load_drums(काष्ठा snd_opl3 *opl3);
व्योम snd_opl3_drum_चयन(काष्ठा snd_opl3 *opl3, पूर्णांक note, पूर्णांक vel, पूर्णांक on_off, काष्ठा snd_midi_channel *chan);

/* Prototypes क्रम opl3_oss.c */
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
व्योम snd_opl3_init_seq_oss(काष्ठा snd_opl3 *opl3, अक्षर *name);
व्योम snd_opl3_मुक्त_seq_oss(काष्ठा snd_opl3 *opl3);
#अन्यथा
#घोषणा snd_opl3_init_seq_oss(opl3, name) /* NOP */
#घोषणा snd_opl3_मुक्त_seq_oss(opl3) /* NOP */
#पूर्ण_अगर

बाह्य अक्षर snd_opl3_regmap[MAX_OPL2_VOICES][4];
बाह्य bool use_पूर्णांकernal_drums;
बाह्य स्थिर काष्ठा snd_midi_op opl3_ops;

#पूर्ण_अगर
