<शैली गुरु>
/*
 * Local definitions क्रम the OPL4 driver
 *
 * Copyright (c) 2003 by Clemens Ladisch <clemens@ladisch.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed and/or modअगरied under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#अगर_अघोषित __OPL4_LOCAL_H
#घोषणा __OPL4_LOCAL_H

#समावेश <sound/opl4.h>

/*
 * Register numbers
 */

#घोषणा OPL4_REG_TEST0			0x00
#घोषणा OPL4_REG_TEST1			0x01

#घोषणा OPL4_REG_MEMORY_CONFIGURATION	0x02
#घोषणा   OPL4_MODE_BIT			0x01
#घोषणा   OPL4_MTYPE_BIT		0x02
#घोषणा   OPL4_TONE_HEADER_MASK		0x1c
#घोषणा   OPL4_DEVICE_ID_MASK		0xe0

#घोषणा OPL4_REG_MEMORY_ADDRESS_HIGH	0x03
#घोषणा OPL4_REG_MEMORY_ADDRESS_MID	0x04
#घोषणा OPL4_REG_MEMORY_ADDRESS_LOW	0x05
#घोषणा OPL4_REG_MEMORY_DATA		0x06

/*
 * Offsets to the रेजिस्टर banks क्रम voices. To get the
 * रेजिस्टर number just add the voice number to the bank offset.
 *
 * Wave Table Number low bits (0x08 to 0x1F)
 */
#घोषणा OPL4_REG_TONE_NUMBER		0x08

/* Wave Table Number high bit, F-Number low bits (0x20 to 0x37) */
#घोषणा OPL4_REG_F_NUMBER		0x20
#घोषणा   OPL4_TONE_NUMBER_BIT8		0x01
#घोषणा   OPL4_F_NUMBER_LOW_MASK	0xfe

/* F-Number high bits, Octave, Pseuकरो-Reverb (0x38 to 0x4F) */
#घोषणा OPL4_REG_OCTAVE			0x38
#घोषणा   OPL4_F_NUMBER_HIGH_MASK	0x07
#घोषणा   OPL4_BLOCK_MASK		0xf0
#घोषणा   OPL4_PSEUDO_REVERB_BIT	0x08

/* Total Level, Level Direct (0x50 to 0x67) */
#घोषणा OPL4_REG_LEVEL			0x50
#घोषणा   OPL4_TOTAL_LEVEL_MASK		0xfe
#घोषणा   OPL4_LEVEL_सूचीECT_BIT		0x01

/* Key On, Damp, LFO RST, CH, Panpot (0x68 to 0x7F) */
#घोषणा OPL4_REG_MISC			0x68
#घोषणा   OPL4_KEY_ON_BIT		0x80
#घोषणा   OPL4_DAMP_BIT			0x40
#घोषणा   OPL4_LFO_RESET_BIT		0x20
#घोषणा   OPL4_OUTPUT_CHANNEL_BIT	0x10
#घोषणा   OPL4_PAN_POT_MASK		0x0f

/* LFO, VIB (0x80 to 0x97) */
#घोषणा OPL4_REG_LFO_VIBRATO		0x80
#घोषणा   OPL4_LFO_FREQUENCY_MASK	0x38
#घोषणा   OPL4_VIBRATO_DEPTH_MASK	0x07
#घोषणा   OPL4_CHORUS_SEND_MASK		0xc0 /* ML only */

/* Attack / Decay 1 rate (0x98 to 0xAF) */
#घोषणा OPL4_REG_ATTACK_DECAY1		0x98
#घोषणा   OPL4_ATTACK_RATE_MASK		0xf0
#घोषणा   OPL4_DECAY1_RATE_MASK		0x0f

/* Decay level / 2 rate (0xB0 to 0xC7) */
#घोषणा OPL4_REG_LEVEL_DECAY2		0xb0
#घोषणा   OPL4_DECAY_LEVEL_MASK		0xf0
#घोषणा   OPL4_DECAY2_RATE_MASK		0x0f

/* Release rate / Rate correction (0xC8 to 0xDF) */
#घोषणा OPL4_REG_RELEASE_CORRECTION	0xc8
#घोषणा   OPL4_RELEASE_RATE_MASK	0x0f
#घोषणा   OPL4_RATE_INTERPOLATION_MASK	0xf0

/* AM (0xE0 to 0xF7) */
#घोषणा OPL4_REG_TREMOLO		0xe0
#घोषणा   OPL4_TREMOLO_DEPTH_MASK	0x07
#घोषणा   OPL4_REVERB_SEND_MASK		0xe0 /* ML only */

/* Mixer */
#घोषणा OPL4_REG_MIX_CONTROL_FM		0xf8
#घोषणा OPL4_REG_MIX_CONTROL_PCM	0xf9
#घोषणा   OPL4_MIX_LEFT_MASK		0x07
#घोषणा   OPL4_MIX_RIGHT_MASK		0x38

#घोषणा OPL4_REG_ATC			0xfa
#घोषणा   OPL4_ATC_BIT			0x01 /* ???, ML only */

/* bits in the OPL3 Status रेजिस्टर */
#घोषणा OPL4_STATUS_BUSY		0x01
#घोषणा OPL4_STATUS_LOAD		0x02


#घोषणा OPL4_MAX_VOICES 24

#घोषणा SNDRV_SEQ_DEV_ID_OPL4 "opl4-synth"


काष्ठा opl4_sound अणु
	u16 tone;
	s16 pitch_offset;
	u8 key_scaling;
	s8 panpot;
	u8 vibrato;
	u8 tone_attenuate;
	u8 volume_factor;
	u8 reg_lfo_vibrato;
	u8 reg_attack_decay1;
	u8 reg_level_decay2;
	u8 reg_release_correction;
	u8 reg_tremolo;
पूर्ण;

काष्ठा opl4_region अणु
	u8 key_min, key_max;
	काष्ठा opl4_sound sound;
पूर्ण;

काष्ठा opl4_region_ptr अणु
	पूर्णांक count;
	स्थिर काष्ठा opl4_region *regions;
पूर्ण;

काष्ठा opl4_voice अणु
	काष्ठा list_head list;
	पूर्णांक number;
	काष्ठा snd_midi_channel *chan;
	पूर्णांक note;
	पूर्णांक velocity;
	स्थिर काष्ठा opl4_sound *sound;
	u8 level_direct;
	u8 reg_f_number;
	u8 reg_misc;
	u8 reg_lfo_vibrato;
पूर्ण;

काष्ठा snd_opl4 अणु
	अचिन्हित दीर्घ fm_port;
	अचिन्हित दीर्घ pcm_port;
	काष्ठा resource *res_fm_port;
	काष्ठा resource *res_pcm_port;
	अचिन्हित लघु hardware;
	spinlock_t reg_lock;
	काष्ठा snd_card *card;

#अगर_घोषित CONFIG_SND_PROC_FS
	काष्ठा snd_info_entry *proc_entry;
	पूर्णांक memory_access;
#पूर्ण_अगर
	काष्ठा mutex access_mutex;

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
	पूर्णांक used;

	पूर्णांक seq_dev_num;
	पूर्णांक seq_client;
	काष्ठा snd_seq_device *seq_dev;

	काष्ठा snd_midi_channel_set *chset;
	काष्ठा opl4_voice voices[OPL4_MAX_VOICES];
	काष्ठा list_head off_voices;
	काष्ठा list_head on_voices;
#पूर्ण_अगर
पूर्ण;

/* opl4_lib.c */
व्योम snd_opl4_ग_लिखो(काष्ठा snd_opl4 *opl4, u8 reg, u8 value);
u8 snd_opl4_पढ़ो(काष्ठा snd_opl4 *opl4, u8 reg);
व्योम snd_opl4_पढ़ो_memory(काष्ठा snd_opl4 *opl4, अक्षर *buf, पूर्णांक offset, पूर्णांक size);
व्योम snd_opl4_ग_लिखो_memory(काष्ठा snd_opl4 *opl4, स्थिर अक्षर *buf, पूर्णांक offset, पूर्णांक size);

/* opl4_mixer.c */
पूर्णांक snd_opl4_create_mixer(काष्ठा snd_opl4 *opl4);

#अगर_घोषित CONFIG_SND_PROC_FS
/* opl4_proc.c */
पूर्णांक snd_opl4_create_proc(काष्ठा snd_opl4 *opl4);
व्योम snd_opl4_मुक्त_proc(काष्ठा snd_opl4 *opl4);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_opl4_create_proc(काष्ठा snd_opl4 *opl4) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम snd_opl4_मुक्त_proc(काष्ठा snd_opl4 *opl4) अणुपूर्ण
#पूर्ण_अगर

/* opl4_seq.c */
बाह्य पूर्णांक volume_boost;

/* opl4_synth.c */
व्योम snd_opl4_synth_reset(काष्ठा snd_opl4 *opl4);
व्योम snd_opl4_synth_shutकरोwn(काष्ठा snd_opl4 *opl4);
व्योम snd_opl4_note_on(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan);
व्योम snd_opl4_note_off(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan);
व्योम snd_opl4_terminate_note(व्योम *p, पूर्णांक note, काष्ठा snd_midi_channel *chan);
व्योम snd_opl4_control(व्योम *p, पूर्णांक type, काष्ठा snd_midi_channel *chan);
व्योम snd_opl4_sysex(व्योम *p, अचिन्हित अक्षर *buf, पूर्णांक len, पूर्णांक parsed, काष्ठा snd_midi_channel_set *chset);

/* yrw801.c */
पूर्णांक snd_yrw801_detect(काष्ठा snd_opl4 *opl4);
बाह्य स्थिर काष्ठा opl4_region_ptr snd_yrw801_regions[];

#पूर्ण_अगर /* __OPL4_LOCAL_H */
