<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Uros Bizjak <uros@kss-loka.si>
 *
 *   OPL2/OPL3/OPL4 FM routines क्रम पूर्णांकernal percussion channels
 */

#समावेश "opl3_voice.h"

अटल स्थिर अक्षर snd_opl3_drum_table[47] =
अणु
	OPL3_BASSDRUM_ON,  OPL3_BASSDRUM_ON,  OPL3_HIHAT_ON,	/* 35 - 37 */
	OPL3_SNAREDRUM_ON, OPL3_HIHAT_ON,     OPL3_SNAREDRUM_ON, /* 38 - 40 */
	OPL3_BASSDRUM_ON,  OPL3_HIHAT_ON,     OPL3_BASSDRUM_ON,	/* 41 - 43 */
	OPL3_HIHAT_ON,     OPL3_TOMTOM_ON,    OPL3_HIHAT_ON,	/* 44 - 46 */
	OPL3_TOMTOM_ON,    OPL3_TOMTOM_ON,    OPL3_CYMBAL_ON,	/* 47 - 49 */

	OPL3_TOMTOM_ON,    OPL3_CYMBAL_ON,    OPL3_CYMBAL_ON,	/* 50 - 52 */
	OPL3_CYMBAL_ON,    OPL3_CYMBAL_ON,    OPL3_CYMBAL_ON,	/* 53 - 55 */
	OPL3_HIHAT_ON,     OPL3_CYMBAL_ON,    OPL3_TOMTOM_ON,	/* 56 - 58 */
	OPL3_CYMBAL_ON,    OPL3_TOMTOM_ON,    OPL3_TOMTOM_ON,	/* 59 - 61 */
	OPL3_HIHAT_ON,     OPL3_TOMTOM_ON,    OPL3_TOMTOM_ON,	/* 62 - 64 */

	OPL3_TOMTOM_ON,    OPL3_TOMTOM_ON,    OPL3_TOMTOM_ON,	/* 65 - 67 */
	OPL3_TOMTOM_ON,    OPL3_HIHAT_ON,     OPL3_HIHAT_ON,	/* 68 - 70 */
	OPL3_HIHAT_ON,     OPL3_HIHAT_ON,     OPL3_TOMTOM_ON,	/* 71 - 73 */
	OPL3_TOMTOM_ON,    OPL3_TOMTOM_ON,    OPL3_TOMTOM_ON,	/* 74 - 76 */
	OPL3_TOMTOM_ON,    OPL3_TOMTOM_ON,    OPL3_TOMTOM_ON,	/* 77 - 79 */
	OPL3_CYMBAL_ON,    OPL3_CYMBAL_ON			/* 80 - 81 */
पूर्ण;

काष्ठा snd_opl3_drum_voice अणु
	पूर्णांक voice;
	पूर्णांक op;
	अचिन्हित अक्षर am_vib;
	अचिन्हित अक्षर ksl_level;
	अचिन्हित अक्षर attack_decay;
	अचिन्हित अक्षर sustain_release;
	अचिन्हित अक्षर feedback_connection;
	अचिन्हित अक्षर wave_select;
पूर्ण;

काष्ठा snd_opl3_drum_note अणु
	पूर्णांक voice;
	अचिन्हित अक्षर fnum;
	अचिन्हित अक्षर octave_f;
	अचिन्हित अक्षर feedback_connection;
पूर्ण;

अटल स्थिर काष्ठा snd_opl3_drum_voice bass_op0 = अणु6, 0, 0x00, 0x32, 0xf8, 0x66, 0x30, 0x00पूर्ण;
अटल स्थिर काष्ठा snd_opl3_drum_voice bass_op1 = अणु6, 1, 0x00, 0x03, 0xf6, 0x57, 0x30, 0x00पूर्ण;
अटल स्थिर काष्ठा snd_opl3_drum_note bass_note = अणु6, 0x90, 0x09पूर्ण;

अटल स्थिर काष्ठा snd_opl3_drum_voice hihat = अणु7, 0, 0x00, 0x03, 0xf0, 0x06, 0x20, 0x00पूर्ण;

अटल स्थिर काष्ठा snd_opl3_drum_voice snare = अणु7, 1, 0x00, 0x03, 0xf0, 0x07, 0x20, 0x02पूर्ण;
अटल स्थिर काष्ठा snd_opl3_drum_note snare_note = अणु7, 0xf4, 0x0dपूर्ण;

अटल स्थिर काष्ठा snd_opl3_drum_voice tomtom = अणु8, 0, 0x02, 0x03, 0xf0, 0x06, 0x10, 0x00पूर्ण;
अटल स्थिर काष्ठा snd_opl3_drum_note tomtom_note = अणु8, 0xf4, 0x09पूर्ण;

अटल स्थिर काष्ठा snd_opl3_drum_voice cymbal = अणु8, 1, 0x04, 0x03, 0xf0, 0x06, 0x10, 0x00पूर्ण;

/*
 * set drum voice अक्षरacteristics
 */
अटल व्योम snd_opl3_drum_voice_set(काष्ठा snd_opl3 *opl3,
				    स्थिर काष्ठा snd_opl3_drum_voice *data)
अणु
	अचिन्हित अक्षर op_offset = snd_opl3_regmap[data->voice][data->op];
	अचिन्हित अक्षर voice_offset = data->voice;
	अचिन्हित लघु opl3_reg;
	
	/* Set OPL3 AM_VIB रेजिस्टर */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_AM_VIB + op_offset);
	opl3->command(opl3, opl3_reg, data->am_vib);

	/* Set OPL3 KSL_LEVEL रेजिस्टर */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_KSL_LEVEL + op_offset);
	opl3->command(opl3, opl3_reg, data->ksl_level);

	/* Set OPL3 ATTACK_DECAY रेजिस्टर */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_ATTACK_DECAY + op_offset);
	opl3->command(opl3, opl3_reg, data->attack_decay);

	/* Set OPL3 SUSTAIN_RELEASE रेजिस्टर */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_SUSTAIN_RELEASE + op_offset);
	opl3->command(opl3, opl3_reg, data->sustain_release);

	/* Set OPL3 FEEDBACK_CONNECTION रेजिस्टर */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_FEEDBACK_CONNECTION + voice_offset);
	opl3->command(opl3, opl3_reg, data->feedback_connection);

	/* Select waveक्रमm */
	opl3_reg = OPL3_LEFT | (OPL3_REG_WAVE_SELECT + op_offset);
	opl3->command(opl3, opl3_reg, data->wave_select);
पूर्ण

/*
 * Set drum voice pitch
 */
अटल व्योम snd_opl3_drum_note_set(काष्ठा snd_opl3 *opl3,
				   स्थिर काष्ठा snd_opl3_drum_note *data)
अणु
	अचिन्हित अक्षर voice_offset = data->voice;
	अचिन्हित लघु opl3_reg;

	/* Set OPL3 FNUM_LOW रेजिस्टर */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_FNUM_LOW + voice_offset);
	opl3->command(opl3, opl3_reg, data->fnum);

	/* Set OPL3 KEYON_BLOCK रेजिस्टर */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_KEYON_BLOCK + voice_offset);
	opl3->command(opl3, opl3_reg, data->octave_f);
पूर्ण

/*
 * Set drum voice volume and position
 */
अटल व्योम snd_opl3_drum_vol_set(काष्ठा snd_opl3 *opl3,
				  स्थिर काष्ठा snd_opl3_drum_voice *data,
				  पूर्णांक vel, काष्ठा snd_midi_channel *chan)
अणु
	अचिन्हित अक्षर op_offset = snd_opl3_regmap[data->voice][data->op];
	अचिन्हित अक्षर voice_offset = data->voice;
	अचिन्हित अक्षर reg_val;
	अचिन्हित लघु opl3_reg;

	/* Set OPL3 KSL_LEVEL रेजिस्टर */ 
	reg_val = data->ksl_level;
	snd_opl3_calc_volume(&reg_val, vel, chan);
	opl3_reg = OPL3_LEFT | (OPL3_REG_KSL_LEVEL + op_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	/* Set OPL3 FEEDBACK_CONNECTION रेजिस्टर */ 
	/* Set output voice connection */
	reg_val = data->feedback_connection | OPL3_STEREO_BITS;
	अगर (chan->gm_pan < 43)
		reg_val &= ~OPL3_VOICE_TO_RIGHT;
	अगर (chan->gm_pan > 85)
		reg_val &= ~OPL3_VOICE_TO_LEFT;
	opl3_reg = OPL3_LEFT | (OPL3_REG_FEEDBACK_CONNECTION + voice_offset);
	opl3->command(opl3, opl3_reg, reg_val);
पूर्ण

/*
 * Loads drum voices at init समय
 */
व्योम snd_opl3_load_drums(काष्ठा snd_opl3 *opl3)
अणु
	snd_opl3_drum_voice_set(opl3, &bass_op0);
	snd_opl3_drum_voice_set(opl3, &bass_op1);
	snd_opl3_drum_note_set(opl3, &bass_note);

	snd_opl3_drum_voice_set(opl3, &hihat);

	snd_opl3_drum_voice_set(opl3, &snare);
	snd_opl3_drum_note_set(opl3, &snare_note);

	snd_opl3_drum_voice_set(opl3, &tomtom);
	snd_opl3_drum_note_set(opl3, &tomtom_note);

	snd_opl3_drum_voice_set(opl3, &cymbal);
पूर्ण

/*
 * Switch drum voice on or off
 */
व्योम snd_opl3_drum_चयन(काष्ठा snd_opl3 *opl3, पूर्णांक note, पूर्णांक vel, पूर्णांक on_off,
			  काष्ठा snd_midi_channel *chan)
अणु
	अचिन्हित अक्षर drum_mask;
	स्थिर काष्ठा snd_opl3_drum_voice *drum_voice;

	अगर (!(opl3->drum_reg & OPL3_PERCUSSION_ENABLE))
		वापस;

	अगर ((note < 35) || (note > 81))
		वापस;
	drum_mask = snd_opl3_drum_table[note - 35];

	अगर (on_off) अणु
		चयन (drum_mask) अणु
		हाल OPL3_BASSDRUM_ON:
			drum_voice = &bass_op1;
			अवरोध;
		हाल OPL3_HIHAT_ON:
			drum_voice = &hihat;
			अवरोध;
		हाल OPL3_SNAREDRUM_ON:
			drum_voice = &snare;
			अवरोध;
		हाल OPL3_TOMTOM_ON:
			drum_voice = &tomtom;
			अवरोध;
		हाल OPL3_CYMBAL_ON:
			drum_voice = &cymbal;
			अवरोध;
		शेष:
			drum_voice = &tomtom;
		पूर्ण

		snd_opl3_drum_vol_set(opl3, drum_voice, vel, chan);
		opl3->drum_reg |= drum_mask;
	पूर्ण अन्यथा अणु
		opl3->drum_reg &= ~drum_mask;
	पूर्ण
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_PERCUSSION,
			 opl3->drum_reg);
पूर्ण
