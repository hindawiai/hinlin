<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/समय.स>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/gus.h>
#घोषणा __GUS_TABLES_ALLOC__
#समावेश "gus_tables.h"

EXPORT_SYMBOL(snd_gf1_atten_table); /* क्रम snd-gus-synth module */

अचिन्हित लघु snd_gf1_lvol_to_gvol_raw(अचिन्हित पूर्णांक vol)
अणु
	अचिन्हित लघु e, m, पंचांगp;

	अगर (vol > 65535)
		vol = 65535;
	पंचांगp = vol;
	e = 7;
	अगर (पंचांगp < 128) अणु
		जबतक (e > 0 && पंचांगp < (1 << e))
			e--;
	पूर्ण अन्यथा अणु
		जबतक (पंचांगp > 255) अणु
			पंचांगp >>= 1;
			e++;
		पूर्ण
	पूर्ण
	m = vol - (1 << e);
	अगर (m > 0) अणु
		अगर (e > 8)
			m >>= e - 8;
		अन्यथा अगर (e < 8)
			m <<= 8 - e;
		m &= 255;
	पूर्ण
	वापस (e << 8) | m;
पूर्ण

#अगर 0

अचिन्हित पूर्णांक snd_gf1_gvol_to_lvol_raw(अचिन्हित लघु gf1_vol)
अणु
	अचिन्हित पूर्णांक rvol;
	अचिन्हित लघु e, m;

	अगर (!gf1_vol)
		वापस 0;
	e = gf1_vol >> 8;
	m = (अचिन्हित अक्षर) gf1_vol;
	rvol = 1 << e;
	अगर (e > 8)
		वापस rvol | (m << (e - 8));
	वापस rvol | (m >> (8 - e));
पूर्ण

अचिन्हित पूर्णांक snd_gf1_calc_ramp_rate(काष्ठा snd_gus_card * gus,
				    अचिन्हित लघु start,
				    अचिन्हित लघु end,
				    अचिन्हित पूर्णांक us)
अणु
	अटल स्थिर अचिन्हित अक्षर vol_rates[19] =
	अणु
		23, 24, 26, 28, 29, 31, 32, 34,
		36, 37, 39, 40, 42, 44, 45, 47,
		49, 50, 52
	पूर्ण;
	अचिन्हित लघु range, increment, value, i;

	start >>= 4;
	end >>= 4;
	अगर (start < end)
		us /= end - start;
	अन्यथा
		us /= start - end;
	range = 4;
	value = gus->gf1.enh_mode ?
	    vol_rates[0] :
	    vol_rates[gus->gf1.active_voices - 14];
	क्रम (i = 0; i < 3; i++) अणु
		अगर (us < value) अणु
			range = i;
			अवरोध;
		पूर्ण अन्यथा
			value <<= 3;
	पूर्ण
	अगर (range == 4) अणु
		range = 3;
		increment = 1;
	पूर्ण अन्यथा
		increment = (value + (value >> 1)) / us;
	वापस (range << 6) | (increment & 0x3f);
पूर्ण

#पूर्ण_अगर  /*  0  */

अचिन्हित लघु snd_gf1_translate_freq(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक freq16)
अणु
	freq16 >>= 3;
	अगर (freq16 < 50)
		freq16 = 50;
	अगर (freq16 & 0xf8000000) अणु
		freq16 = ~0xf8000000;
		snd_prपूर्णांकk(KERN_ERR "snd_gf1_translate_freq: overflow - freq = 0x%x\n", freq16);
	पूर्ण
	वापस ((freq16 << 9) + (gus->gf1.playback_freq >> 1)) / gus->gf1.playback_freq;
पूर्ण

#अगर 0

लघु snd_gf1_compute_vibrato(लघु cents, अचिन्हित लघु fc_रेजिस्टर)
अणु
	अटल स्थिर लघु vibrato_table[] =
	अणु
		0, 0, 32, 592, 61, 1175, 93, 1808,
		124, 2433, 152, 3007, 182, 3632, 213, 4290,
		241, 4834, 255, 5200
	पूर्ण;

	दीर्घ depth;
	स्थिर लघु *vi1, *vi2;
	लघु pcents, v1;

	pcents = cents < 0 ? -cents : cents;
	क्रम (vi1 = vibrato_table, vi2 = vi1 + 2; pcents > *vi2; vi1 = vi2, vi2 += 2);
	v1 = *(vi1 + 1);
	/* The FC table above is a list of pairs. The first number in the pair     */
	/* is the cents index from 0-255 cents, and the second number in the       */
	/* pair is the FC adjusपंचांगent needed to change the pitch by the indexed     */
	/* number of cents. The table was created क्रम an FC of 32768.              */
	/* The following expression करोes a linear पूर्णांकerpolation against the        */
	/* approximated log curve in the table above, and then scales the number   */
	/* by the FC beक्रमe the LFO. This calculation also adjusts the output      */
	/* value to produce the appropriate depth क्रम the hardware. The depth      */
	/* is 2 * desired FC + 1.                                                  */
	depth = (((पूर्णांक) (*(vi2 + 1) - *vi1) * (pcents - *vi1) / (*vi2 - *vi1)) + v1) * fc_रेजिस्टर >> 14;
	अगर (depth)
		depth++;
	अगर (depth > 255)
		depth = 255;
	वापस cents < 0 ? -(लघु) depth : (लघु) depth;
पूर्ण

अचिन्हित लघु snd_gf1_compute_pitchbend(अचिन्हित लघु pitchbend, अचिन्हित लघु sens)
अणु
	अटल स्थिर दीर्घ log_table[] = अणु1024, 1085, 1149, 1218, 1290, 1367, 1448, 1534, 1625, 1722, 1825, 1933पूर्ण;
	पूर्णांक wheel, sensitivity;
	अचिन्हित पूर्णांक mantissa, f1, f2;
	अचिन्हित लघु semitones, f1_index, f2_index, f1_घातer, f2_घातer;
	अक्षर bend_करोwn = 0;
	पूर्णांक bend;

	अगर (!sens)
		वापस 1024;
	wheel = (पूर्णांक) pitchbend - 8192;
	sensitivity = ((पूर्णांक) sens * wheel) / 128;
	अगर (sensitivity < 0) अणु
		bend_करोwn = 1;
		sensitivity = -sensitivity;
	पूर्ण
	semitones = (अचिन्हित पूर्णांक) (sensitivity >> 13);
	mantissa = sensitivity % 8192;
	f1_index = semitones % 12;
	f2_index = (semitones + 1) % 12;
	f1_घातer = semitones / 12;
	f2_घातer = (semitones + 1) / 12;
	f1 = log_table[f1_index] << f1_घातer;
	f2 = log_table[f2_index] << f2_घातer;
	bend = (पूर्णांक) ((((f2 - f1) * mantissa) >> 13) + f1);
	अगर (bend_करोwn)
		bend = 1048576L / bend;
	वापस bend;
पूर्ण

अचिन्हित लघु snd_gf1_compute_freq(अचिन्हित पूर्णांक freq,
				    अचिन्हित पूर्णांक rate,
				    अचिन्हित लघु mix_rate)
अणु
	अचिन्हित पूर्णांक fc;
	पूर्णांक scale = 0;

	जबतक (freq >= 4194304L) अणु
		scale++;
		freq >>= 1;
	पूर्ण
	fc = (freq << 10) / rate;
	अगर (fc > 97391L) अणु
		fc = 97391;
		snd_prपूर्णांकk(KERN_ERR "patch: (1) fc frequency overflow - %u\n", fc);
	पूर्ण
	fc = (fc * 44100UL) / mix_rate;
	जबतक (scale--)
		fc <<= 1;
	अगर (fc > 65535L) अणु
		fc = 65535;
		snd_prपूर्णांकk(KERN_ERR "patch: (2) fc frequency overflow - %u\n", fc);
	पूर्ण
	वापस (अचिन्हित लघु) fc;
पूर्ण

#पूर्ण_अगर  /*  0  */
