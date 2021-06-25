<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/प्रकार.स>
#समावेश "spk_types.h"
#समावेश "spk_priv.h"
#समावेश "speakup.h"

अटल काष्ठा st_var_header var_headers[] = अणु
	अणु "version", VERSION, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "synth_name", SYNTH, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "keymap", KEYMAP, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "silent", SILENT, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "punc_some", PUNC_SOME, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "punc_most", PUNC_MOST, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "punc_all", PUNC_ALL, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "delimiters", DELIM, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "repeats", REPEATS, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "ex_num", EXNUMBER, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "characters", CHARS, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "synth_direct", SYNTH_सूचीECT, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "caps_start", CAPS_START, VAR_STRING, spk_str_caps_start, शून्य पूर्ण,
	अणु "caps_stop", CAPS_STOP, VAR_STRING, spk_str_caps_stop, शून्य पूर्ण,
	अणु "delay_time", DELAY, VAR_TIME, शून्य, शून्य पूर्ण,
	अणु "trigger_time", TRIGGER, VAR_TIME, शून्य, शून्य पूर्ण,
	अणु "jiffy_delta", JIFFY, VAR_TIME, शून्य, शून्य पूर्ण,
	अणु "full_time", FULL, VAR_TIME, शून्य, शून्य पूर्ण,
	अणु "flush_time", FLUSH, VAR_TIME, शून्य, शून्य पूर्ण,
	अणु "spell_delay", SPELL_DELAY, VAR_NUM, &spk_spell_delay, शून्य पूर्ण,
	अणु "bleeps", BLEEPS, VAR_NUM, &spk_bleeps, शून्य पूर्ण,
	अणु "attrib_bleep", ATTRIB_BLEEP, VAR_NUM, &spk_attrib_bleep, शून्य पूर्ण,
	अणु "bleep_time", BLEEP_TIME, VAR_TIME, &spk_bleep_समय, शून्य पूर्ण,
	अणु "cursor_time", CURSOR_TIME, VAR_TIME, शून्य, शून्य पूर्ण,
	अणु "punc_level", PUNC_LEVEL, VAR_NUM, &spk_punc_level, शून्य पूर्ण,
	अणु "reading_punc", READING_PUNC, VAR_NUM, &spk_पढ़ोing_punc, शून्य पूर्ण,
	अणु "say_control", SAY_CONTROL, VAR_NUM, &spk_say_ctrl, शून्य पूर्ण,
	अणु "say_word_ctl", SAY_WORD_CTL, VAR_NUM, &spk_say_word_ctl, शून्य पूर्ण,
	अणु "no_interrupt", NO_INTERRUPT, VAR_NUM, &spk_no_पूर्णांकr, शून्य पूर्ण,
	अणु "key_echo", KEY_ECHO, VAR_NUM, &spk_key_echo, शून्य पूर्ण,
	अणु "bell_pos", BELL_POS, VAR_NUM, &spk_bell_pos, शून्य पूर्ण,
	अणु "rate", RATE, VAR_NUM, शून्य, शून्य पूर्ण,
	अणु "pitch", PITCH, VAR_NUM, शून्य, शून्य पूर्ण,
	अणु "inflection", INFLECTION, VAR_NUM, शून्य, शून्य पूर्ण,
	अणु "vol", VOL, VAR_NUM, शून्य, शून्य पूर्ण,
	अणु "tone", TONE, VAR_NUM, शून्य, शून्य पूर्ण,
	अणु "punct", PUNCT, VAR_NUM, शून्य, शून्य   पूर्ण,
	अणु "voice", VOICE, VAR_NUM, शून्य, शून्य पूर्ण,
	अणु "freq", FREQUENCY, VAR_NUM, शून्य, शून्य पूर्ण,
	अणु "lang", LANG, VAR_NUM, शून्य, शून्य पूर्ण,
	अणु "chartab", CHARTAB, VAR_PROC, शून्य, शून्य पूर्ण,
	अणु "direct", सूचीECT, VAR_NUM, शून्य, शून्य पूर्ण,
	अणु "pause", PAUSE, VAR_STRING, spk_str_छोड़ो, शून्य पूर्ण,
पूर्ण;

अटल काष्ठा st_var_header *var_ptrs[MAXVARS] = अणु शून्य, शून्य, शून्य पूर्ण;

अटल काष्ठा punc_var_t punc_vars[] = अणु
	अणु PUNC_SOME, 1 पूर्ण,
	अणु PUNC_MOST, 2 पूर्ण,
	अणु PUNC_ALL, 3 पूर्ण,
	अणु DELIM, 4 पूर्ण,
	अणु REPEATS, 5 पूर्ण,
	अणु EXNUMBER, 6 पूर्ण,
	अणु -1, -1 पूर्ण,
पूर्ण;

पूर्णांक spk_अक्षरtab_get_value(अक्षर *keyword)
अणु
	पूर्णांक value = 0;

	अगर (!म_भेद(keyword, "ALPHA"))
		value = ALPHA;
	अन्यथा अगर (!म_भेद(keyword, "B_CTL"))
		value = B_CTL;
	अन्यथा अगर (!म_भेद(keyword, "WDLM"))
		value = WDLM;
	अन्यथा अगर (!म_भेद(keyword, "A_PUNC"))
		value = A_PUNC;
	अन्यथा अगर (!म_भेद(keyword, "PUNC"))
		value = PUNC;
	अन्यथा अगर (!म_भेद(keyword, "NUM"))
		value = NUM;
	अन्यथा अगर (!म_भेद(keyword, "A_CAP"))
		value = A_CAP;
	अन्यथा अगर (!म_भेद(keyword, "B_CAPSYM"))
		value = B_CAPSYM;
	अन्यथा अगर (!म_भेद(keyword, "B_SYM"))
		value = B_SYM;
	वापस value;
पूर्ण

व्योम speakup_रेजिस्टर_var(काष्ठा var_t *var)
अणु
	अटल अक्षर nothing[2] = "\0";
	पूर्णांक i;
	काष्ठा st_var_header *p_header;

	BUG_ON(!var || var->var_id < 0 || var->var_id >= MAXVARS);
	अगर (!var_ptrs[0]) अणु
		क्रम (i = 0; i < MAXVARS; i++) अणु
			p_header = &var_headers[i];
			var_ptrs[p_header->var_id] = p_header;
			p_header->data = शून्य;
		पूर्ण
	पूर्ण
	p_header = var_ptrs[var->var_id];
	अगर (p_header->data)
		वापस;
	p_header->data = var;
	चयन (p_header->var_type) अणु
	हाल VAR_STRING:
		spk_set_string_var(nothing, p_header, 0);
		अवरोध;
	हाल VAR_NUM:
	हाल VAR_TIME:
		spk_set_num_var(0, p_header, E_DEFAULT);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम speakup_unरेजिस्टर_var(क्रमागत var_id_t var_id)
अणु
	काष्ठा st_var_header *p_header;

	BUG_ON(var_id < 0 || var_id >= MAXVARS);
	p_header = var_ptrs[var_id];
	p_header->data = शून्य;
पूर्ण

काष्ठा st_var_header *spk_get_var_header(क्रमागत var_id_t var_id)
अणु
	काष्ठा st_var_header *p_header;

	अगर (var_id < 0 || var_id >= MAXVARS)
		वापस शून्य;
	p_header = var_ptrs[var_id];
	अगर (!p_header->data)
		वापस शून्य;
	वापस p_header;
पूर्ण

काष्ठा st_var_header *spk_var_header_by_name(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	अगर (!name)
		वापस शून्य;

	क्रम (i = 0; i < MAXVARS; i++) अणु
		अगर (म_भेद(name, var_ptrs[i]->name) == 0)
			वापस var_ptrs[i];
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा var_t *spk_get_var(क्रमागत var_id_t var_id)
अणु
	BUG_ON(var_id < 0 || var_id >= MAXVARS);
	BUG_ON(!var_ptrs[var_id]);
	वापस var_ptrs[var_id]->data;
पूर्ण
EXPORT_SYMBOL_GPL(spk_get_var);

काष्ठा punc_var_t *spk_get_punc_var(क्रमागत var_id_t var_id)
अणु
	काष्ठा punc_var_t *rv = शून्य;
	काष्ठा punc_var_t *where;

	where = punc_vars;
	जबतक ((where->var_id != -1) && (!rv)) अणु
		अगर (where->var_id == var_id)
			rv = where;
		अन्यथा
			where++;
	पूर्ण
	वापस rv;
पूर्ण

/* handlers क्रम setting vars */
पूर्णांक spk_set_num_var(पूर्णांक input, काष्ठा st_var_header *var, पूर्णांक how)
अणु
	पूर्णांक val;
	पूर्णांक *p_val = var->p_val;
	अक्षर buf[32];
	अक्षर *cp;
	काष्ठा var_t *var_data = var->data;

	अगर (!var_data)
		वापस -ENODATA;

	val = var_data->u.n.value;
	चयन (how) अणु
	हाल E_NEW_DEFAULT:
		अगर (input < var_data->u.n.low || input > var_data->u.n.high)
			वापस -दुस्फल;
		var_data->u.n.शेष_val = input;
		वापस 0;
	हाल E_DEFAULT:
		val = var_data->u.n.शेष_val;
		अवरोध;
	हाल E_SET:
		val = input;
		अवरोध;
	हाल E_INC:
		val += input;
		अवरोध;
	हाल E_DEC:
		val -= input;
		अवरोध;
	पूर्ण

	अगर (val < var_data->u.n.low || val > var_data->u.n.high)
		वापस -दुस्फल;

	var_data->u.n.value = val;
	अगर (var->var_type == VAR_TIME && p_val) अणु
		*p_val = msecs_to_jअगरfies(val);
		वापस 0;
	पूर्ण
	अगर (p_val)
		*p_val = val;
	अगर (var->var_id == PUNC_LEVEL) अणु
		spk_punc_mask = spk_punc_masks[val];
		वापस 0;
	पूर्ण
	अगर (var_data->u.n.multiplier != 0)
		val *= var_data->u.n.multiplier;
	val += var_data->u.n.offset;
	अगर (var->var_id < FIRST_SYNTH_VAR || !synth)
		वापस 0;
	अगर (synth->synth_adjust)
		वापस synth->synth_adjust(var);

	अगर (!var_data->u.n.synth_fmt)
		वापस 0;
	अगर (var->var_id == PITCH)
		cp = spk_pitch_buff;
	अन्यथा
		cp = buf;
	अगर (!var_data->u.n.out_str)
		प्र_लिखो(cp, var_data->u.n.synth_fmt, (पूर्णांक)val);
	अन्यथा
		प्र_लिखो(cp, var_data->u.n.synth_fmt,
			var_data->u.n.out_str[val]);
	synth_म_लिखो("%s", cp);
	वापस 0;
पूर्ण

पूर्णांक spk_set_string_var(स्थिर अक्षर *page, काष्ठा st_var_header *var, पूर्णांक len)
अणु
	काष्ठा var_t *var_data = var->data;

	अगर (!var_data)
		वापस -ENODATA;
	अगर (len > MAXVARLEN)
		वापस -E2BIG;
	अगर (!len) अणु
		अगर (!var_data->u.s.शेष_val)
			वापस 0;
		अगर (!var->p_val)
			var->p_val = var_data->u.s.शेष_val;
		अगर (var->p_val != var_data->u.s.शेष_val)
			म_नकल((अक्षर *)var->p_val, var_data->u.s.शेष_val);
		वापस -ERESTART;
	पूर्ण अन्यथा अगर (var->p_val) अणु
		म_नकल((अक्षर *)var->p_val, page);
	पूर्ण अन्यथा अणु
		वापस -E2BIG;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * spk_set_mask_bits sets or clears the punc/delim/repeat bits,
 * अगर input is null uses the शेषs.
 * values क्रम how: 0 clears bits of अक्षरs supplied,
 * 1 clears allk, 2 sets bits क्रम अक्षरs
 */
पूर्णांक spk_set_mask_bits(स्थिर अक्षर *input, स्थिर पूर्णांक which, स्थिर पूर्णांक how)
अणु
	u_अक्षर *cp;
	लघु mask = spk_punc_info[which].mask;

	अगर (how & 1) अणु
		क्रम (cp = (u_अक्षर *)spk_punc_info[3].value; *cp; cp++)
			spk_अक्षरtab[*cp] &= ~mask;
	पूर्ण
	cp = (u_अक्षर *)input;
	अगर (!cp) अणु
		cp = spk_punc_info[which].value;
	पूर्ण अन्यथा अणु
		क्रम (; *cp; cp++) अणु
			अगर (*cp < SPACE)
				अवरोध;
			अगर (mask < PUNC) अणु
				अगर (!(spk_अक्षरtab[*cp] & PUNC))
					अवरोध;
			पूर्ण अन्यथा अगर (spk_अक्षरtab[*cp] & B_NUM) अणु
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (*cp)
			वापस -EINVAL;
		cp = (u_अक्षर *)input;
	पूर्ण
	अगर (how & 2) अणु
		क्रम (; *cp; cp++)
			अगर (*cp > SPACE)
				spk_अक्षरtab[*cp] |= mask;
	पूर्ण अन्यथा अणु
		क्रम (; *cp; cp++)
			अगर (*cp > SPACE)
				spk_अक्षरtab[*cp] &= ~mask;
	पूर्ण
	वापस 0;
पूर्ण

अक्षर *spk_strlwr(अक्षर *s)
अणु
	अक्षर *p;

	अगर (!s)
		वापस शून्य;

	क्रम (p = s; *p; p++)
		*p = छोटे(*p);
	वापस s;
पूर्ण

अक्षर *spk_s2uअक्षर(अक्षर *start, अक्षर *dest)
अणु
	पूर्णांक val;

	/* Do not replace with kम_से_अदीर्घ: here we need start to be updated */
	val = simple_म_से_अदीर्घ(skip_spaces(start), &start, 10);
	अगर (*start == ',')
		start++;
	*dest = (u_अक्षर)val;
	वापस start;
पूर्ण
