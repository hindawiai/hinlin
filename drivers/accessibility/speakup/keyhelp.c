<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* speakup_keyhelp.c
 * help module क्रम speakup
 *
 *written by David Borowski.
 *
 *  Copyright (C) 2003  David Borowski.
 */

#समावेश <linux/keyboard.h>
#समावेश "spk_priv.h"
#समावेश "speakup.h"

#घोषणा MAXFUNCS 130
#घोषणा MAXKEYS 256
अटल स्थिर पूर्णांक num_key_names = MSG_KEYNAMES_END - MSG_KEYNAMES_START + 1;
अटल u_लघु key_offsets[MAXFUNCS], key_data[MAXKEYS];
अटल u_लघु masks[] = अणु 32, 16, 8, 4, 2, 1 पूर्ण;

अटल लघु letter_offsets[26] = अणु
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1 पूर्ण;

अटल u_अक्षर funcvals[] = अणु
	ATTRIB_BLEEP_DEC, ATTRIB_BLEEP_INC, BLEEPS_DEC, BLEEPS_INC,
	SAY_FIRST_CHAR, SAY_LAST_CHAR, SAY_CHAR, SAY_CHAR_NUM,
	SAY_NEXT_CHAR, SAY_PHONETIC_CHAR, SAY_PREV_CHAR, SPEAKUP_PARKED,
	SPEAKUP_CUT, EDIT_DELIM, EDIT_EXNUM, EDIT_MOST,
	EDIT_REPEAT, EDIT_SOME, SPEAKUP_GOTO, BOTTOM_EDGE,
	LEFT_EDGE, RIGHT_EDGE, TOP_EDGE, SPEAKUP_HELP,
	SAY_LINE, SAY_NEXT_LINE, SAY_PREV_LINE, SAY_LINE_INDENT,
	SPEAKUP_PASTE, PITCH_DEC, PITCH_INC, PUNCT_DEC,
	PUNCT_INC, PUNC_LEVEL_DEC, PUNC_LEVEL_INC, SPEAKUP_QUIET,
	RATE_DEC, RATE_INC, READING_PUNC_DEC, READING_PUNC_INC,
	SAY_ATTRIBUTES, SAY_FROM_LEFT, SAY_FROM_TOP, SAY_POSITION,
	SAY_SCREEN, SAY_TO_BOTTOM, SAY_TO_RIGHT, SPK_KEY,
	SPK_LOCK, SPEAKUP_OFF, SPEECH_KILL, SPELL_DELAY_DEC,
	SPELL_DELAY_INC, SPELL_WORD, SPELL_PHONETIC, TONE_DEC,
	TONE_INC, VOICE_DEC, VOICE_INC, VOL_DEC,
	VOL_INC, CLEAR_WIN, SAY_WIN, SET_WIN,
	ENABLE_WIN, SAY_WORD, SAY_NEXT_WORD, SAY_PREV_WORD, 0
पूर्ण;

अटल u_अक्षर *state_tbl;
अटल पूर्णांक cur_item, nstates;

अटल व्योम build_key_data(व्योम)
अणु
	u_अक्षर *kp, counters[MAXFUNCS], ch, ch1;
	u_लघु *p_key, key;
	पूर्णांक i, offset = 1;

	nstates = (पूर्णांक)(state_tbl[-1]);
	स_रखो(counters, 0, माप(counters));
	स_रखो(key_offsets, 0, माप(key_offsets));
	kp = state_tbl + nstates + 1;
	जबतक (*kp++) अणु
		/* count occurrences of each function */
		क्रम (i = 0; i < nstates; i++, kp++) अणु
			अगर (!*kp)
				जारी;
			अगर ((state_tbl[i] & 16) != 0 && *kp == SPK_KEY)
				जारी;
			counters[*kp]++;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < MAXFUNCS; i++) अणु
		अगर (counters[i] == 0)
			जारी;
		key_offsets[i] = offset;
		offset += (counters[i] + 1);
		अगर (offset >= MAXKEYS)
			अवरोध;
	पूर्ण
/* leave counters set so high keycodes come first.
 * this is करोne so num pad and other extended keys maps are spoken beक्रमe
 * the alpha with speakup type mapping.
 */
	kp = state_tbl + nstates + 1;
	जबतक ((ch = *kp++)) अणु
		क्रम (i = 0; i < nstates; i++) अणु
			ch1 = *kp++;
			अगर (!ch1)
				जारी;
			अगर ((state_tbl[i] & 16) != 0 && ch1 == SPK_KEY)
				जारी;
			key = (state_tbl[i] << 8) + ch;
			counters[ch1]--;
			offset = key_offsets[ch1];
			अगर (!offset)
				जारी;
			p_key = key_data + offset + counters[ch1];
			*p_key = key;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम say_key(पूर्णांक key)
अणु
	पूर्णांक i, state = key >> 8;

	key &= 0xff;
	क्रम (i = 0; i < 6; i++) अणु
		अगर (state & masks[i])
			synth_म_लिखो(" %s", spk_msg_get(MSG_STATES_START + i));
	पूर्ण
	अगर ((key > 0) && (key <= num_key_names))
		synth_म_लिखो(" %s\n",
			     spk_msg_get(MSG_KEYNAMES_START + (key - 1)));
पूर्ण

अटल पूर्णांक help_init(व्योम)
अणु
	अक्षर start = SPACE;
	पूर्णांक i;
	पूर्णांक num_funcs = MSG_FUNCNAMES_END - MSG_FUNCNAMES_START + 1;

	state_tbl = spk_our_keys[0] + SHIFT_TBL_SIZE + 2;
	क्रम (i = 0; i < num_funcs; i++) अणु
		अक्षर *cur_funcname = spk_msg_get(MSG_FUNCNAMES_START + i);

		अगर (start == *cur_funcname)
			जारी;
		start = *cur_funcname;
		letter_offsets[(start & 31) - 1] = i;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक spk_handle_help(काष्ठा vc_data *vc, u_अक्षर type, u_अक्षर ch, u_लघु key)
अणु
	पूर्णांक i, n;
	अक्षर *name;
	u_अक्षर func, *kp;
	u_लघु *p_keys, val;

	अगर (letter_offsets[0] == -1)
		help_init();
	अगर (type == KT_LATIN) अणु
		अगर (ch == SPACE) अणु
			spk_special_handler = शून्य;
			synth_म_लिखो("%s\n", spk_msg_get(MSG_LEAVING_HELP));
			वापस 1;
		पूर्ण
		ch |= 32; /* lower हाल */
		अगर (ch < 'a' || ch > 'z')
			वापस -1;
		अगर (letter_offsets[ch - 'a'] == -1) अणु
			synth_म_लिखो(spk_msg_get(MSG_NO_COMMAND), ch);
			synth_म_लिखो("\n");
			वापस 1;
		पूर्ण
		cur_item = letter_offsets[ch - 'a'];
	पूर्ण अन्यथा अगर (type == KT_CUR) अणु
		अगर (ch == 0 &&
		    (MSG_FUNCNAMES_START + cur_item + 1) <= MSG_FUNCNAMES_END)
			cur_item++;
		अन्यथा अगर (ch == 3 && cur_item > 0)
			cur_item--;
		अन्यथा
			वापस -1;
	पूर्ण अन्यथा अगर (type == KT_SPKUP && ch == SPEAKUP_HELP &&
		   !spk_special_handler) अणु
		spk_special_handler = spk_handle_help;
		synth_म_लिखो("%s\n", spk_msg_get(MSG_HELP_INFO));
		build_key_data(); /* rebuild each समय in हाल new mapping */
		वापस 1;
	पूर्ण अन्यथा अणु
		name = शून्य;
		अगर ((type != KT_SPKUP) && (key > 0) && (key <= num_key_names)) अणु
			synth_म_लिखो("%s\n",
				     spk_msg_get(MSG_KEYNAMES_START + key - 1));
			वापस 1;
		पूर्ण
		क्रम (i = 0; funcvals[i] != 0 && !name; i++) अणु
			अगर (ch == funcvals[i])
				name = spk_msg_get(MSG_FUNCNAMES_START + i);
		पूर्ण
		अगर (!name)
			वापस -1;
		kp = spk_our_keys[key] + 1;
		क्रम (i = 0; i < nstates; i++) अणु
			अगर (ch == kp[i])
				अवरोध;
		पूर्ण
		key += (state_tbl[i] << 8);
		say_key(key);
		synth_म_लिखो(spk_msg_get(MSG_KEYDESC), name);
		synth_म_लिखो("\n");
		वापस 1;
	पूर्ण
	name = spk_msg_get(MSG_FUNCNAMES_START + cur_item);
	func = funcvals[cur_item];
	synth_म_लिखो("%s", name);
	अगर (key_offsets[func] == 0) अणु
		synth_म_लिखो(" %s\n", spk_msg_get(MSG_IS_UNASSIGNED));
		वापस 1;
	पूर्ण
	p_keys = key_data + key_offsets[func];
	क्रम (n = 0; p_keys[n]; n++) अणु
		val = p_keys[n];
		अगर (n > 0)
			synth_म_लिखो("%s ", spk_msg_get(MSG_DISJUNCTION));
		say_key(val);
	पूर्ण
	वापस 1;
पूर्ण
