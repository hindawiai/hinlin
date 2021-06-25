<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* speakup.c
 * review functions क्रम the speakup screen review package.
 * originally written by: Kirk Reiser and Andy Berdan.
 *
 * extensively modअगरied by David Borowski.
 *
 ** Copyright (C) 1998  Kirk Reiser.
 *  Copyright (C) 2003  David Borowski.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/vt.h>
#समावेश <linux/tty.h>
#समावेश <linux/mm.h>		/* __get_मुक्त_page() and मित्रs */
#समावेश <linux/vt_kern.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/selection.h>
#समावेश <linux/unistd.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/keyboard.h>	/* क्रम KT_SHIFT */
#समावेश <linux/kbd_kern.h>	/* क्रम vc_kbd_* and मित्रs */
#समावेश <linux/input.h>
#समावेश <linux/kmod.h>

/* speakup_*_selection */
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/consolemap.h>

#समावेश <linux/spinlock.h>
#समावेश <linux/notअगरier.h>

#समावेश <linux/uaccess.h>	/* copy_from|to|user() and others */

#समावेश "spk_priv.h"
#समावेश "speakup.h"

#घोषणा MAX_DELAY msecs_to_jअगरfies(500)
#घोषणा MINECHOCHAR SPACE

MODULE_AUTHOR("Kirk Reiser <kirk@braille.uwo.ca>");
MODULE_AUTHOR("Daniel Drake <dsd@gentoo.org>");
MODULE_DESCRIPTION("Speakup console speech");
MODULE_LICENSE("GPL");
MODULE_VERSION(SPEAKUP_VERSION);

अक्षर *synth_name;
module_param_named(synth, synth_name, अक्षरp, 0444);
module_param_named(quiet, spk_quiet_boot, bool, 0444);

MODULE_PARM_DESC(synth, "Synth to start if speakup is built in.");
MODULE_PARM_DESC(quiet, "Do not announce when the synthesizer is found.");

special_func spk_special_handler;

लघु spk_pitch_shअगरt, synth_flags;
अटल u16 buf[256];
पूर्णांक spk_attrib_bleep, spk_bleeps, spk_bleep_समय = 10;
पूर्णांक spk_no_पूर्णांकr, spk_spell_delay;
पूर्णांक spk_key_echo, spk_say_word_ctl;
पूर्णांक spk_say_ctrl, spk_bell_pos;
लघु spk_punc_mask;
पूर्णांक spk_punc_level, spk_पढ़ोing_punc;
अक्षर spk_str_caps_start[MAXVARLEN + 1] = "\0";
अक्षर spk_str_caps_stop[MAXVARLEN + 1] = "\0";
अक्षर spk_str_छोड़ो[MAXVARLEN + 1] = "\0";
bool spk_छोड़ोd;
स्थिर काष्ठा st_bits_data spk_punc_info[] = अणु
	अणु"none", "", 0पूर्ण,
	अणु"some", "/$%&@", SOMEपूर्ण,
	अणु"most", "$%&#()=+*/@^<>|\\", MOSTपूर्ण,
	अणु"all", "!\"#$%&'()*+,-./:;<=>?@[\\]^_`अणु|पूर्ण~", PUNCपूर्ण,
	अणु"delimiters", "", B_WDLMपूर्ण,
	अणु"repeats", "()", CH_RPTपूर्ण,
	अणु"extended numeric", "", B_EXNUMपूर्ण,
	अणु"symbols", "", B_SYMपूर्ण,
	अणुशून्य, शून्यपूर्ण
पूर्ण;

अटल अक्षर mark_cut_flag;
#घोषणा MAX_KEY 160
अटल u_अक्षर *spk_shअगरt_table;
u_अक्षर *spk_our_keys[MAX_KEY];
u_अक्षर spk_key_buf[600];
स्थिर u_अक्षर spk_key_शेषs[] = अणु
#समावेश "speakupmap.h"
पूर्ण;

/* cursor track modes, must be ordered same as cursor_msgs in क्रमागत msg_index_t */
क्रमागत cursor_track अणु
	CT_Off = 0,
	CT_On,
	CT_Highlight,
	CT_Winकरोw,
	CT_Max,
	पढ़ो_all_mode = CT_Max,
पूर्ण;

/* Speakup Cursor Track Variables */
अटल क्रमागत cursor_track cursor_track = 1, prev_cursor_track = 1;

अटल काष्ठा tty_काष्ठा *tty;

अटल व्योम spkup_ग_लिखो(स्थिर u16 *in_buf, पूर्णांक count);

अटल अक्षर *phonetic[] = अणु
	"alfa", "bravo", "charlie", "delta", "echo", "foxtrot", "golf", "hotel",
	"india", "juliett", "keelo", "leema", "mike", "november", "oscar",
	    "papa",
	"keh beck", "romeo", "sierra", "tango", "uniform", "victer", "whiskey",
	"x ray", "yankee", "zulu"
पूर्ण;

/* array of 256 अक्षर poपूर्णांकers (one क्रम each अक्षरacter description)
 * initialized to शेष_अक्षरs and user selectable via
 * /proc/speakup/अक्षरacters
 */
अक्षर *spk_अक्षरacters[256];

अक्षर *spk_शेष_अक्षरs[256] = अणु
/*000*/ "null", "^a", "^b", "^c", "^d", "^e", "^f", "^g",
/*008*/ "^h", "^i", "^j", "^k", "^l", "^m", "^n", "^o",
/*016*/ "^p", "^q", "^r", "^s", "^t", "^u", "^v", "^w",
/*024*/ "^x", "^y", "^z", "control", "control", "control", "control",
	    "control",
/*032*/ "space", "bang!", "quote", "number", "dollar", "percent", "and",
	    "tick",
/*040*/ "left paren", "right paren", "star", "plus", "comma", "dash",
	    "dot",
	"slash",
/*048*/ "zero", "one", "two", "three", "four", "five", "six", "seven",
	"eight", "nine",
/*058*/ "colon", "semmy", "less", "equals", "greater", "question", "at",
/*065*/ "EIGH", "B", "C", "D", "E", "F", "G",
/*072*/ "H", "I", "J", "K", "L", "M", "N", "O",
/*080*/ "P", "Q", "R", "S", "T", "U", "V", "W", "X",
/*089*/ "Y", "ZED", "left bracket", "backslash", "right bracket",
	    "caret",
	"line",
/*096*/ "accent", "a", "b", "c", "d", "e", "f", "g",
/*104*/ "h", "i", "j", "k", "l", "m", "n", "o",
/*112*/ "p", "q", "r", "s", "t", "u", "v", "w",
/*120*/ "x", "y", "zed", "left brace", "bar", "right brace", "tihlduh",
/*127*/ "del", "control", "control", "control", "control", "control",
	    "control", "control", "control", "control", "control",
/*138*/ "control", "control", "control", "control", "control",
	    "control", "control", "control", "control", "control",
	    "control", "control",
/*150*/ "control", "control", "control", "control", "control",
	    "control", "control", "control", "control", "control",
/*160*/ "nbsp", "inverted bang",
/*162*/ "cents", "pounds", "currency", "yen", "broken bar", "section",
/*168*/ "diaeresis", "copyright", "female ordinal", "double left angle",
/*172*/ "not", "soft hyphen", "registered", "macron",
/*176*/ "degrees", "plus or minus", "super two", "super three",
/*180*/ "acute accent", "micro", "pilcrow", "middle dot",
/*184*/ "cedilla", "super one", "male ordinal", "double right angle",
/*188*/ "one quarter", "one half", "three quarters",
	    "inverted question",
/*192*/ "A GRAVE", "A ACUTE", "A CIRCUMFLEX", "A TILDE", "A OOMLAUT",
	    "A RING",
/*198*/ "AE", "C CIDELLA", "E GRAVE", "E ACUTE", "E CIRCUMFLEX",
	    "E OOMLAUT",
/*204*/ "I GRAVE", "I ACUTE", "I CIRCUMFLEX", "I OOMLAUT", "ETH",
	    "N TILDE",
/*210*/ "O GRAVE", "O ACUTE", "O CIRCUMFLEX", "O TILDE", "O OOMLAUT",
/*215*/ "multiplied by", "O STROKE", "U GRAVE", "U ACUTE",
	    "U CIRCUMFLEX",
/*220*/ "U OOMLAUT", "Y ACUTE", "THORN", "sharp s", "a grave",
/*225*/ "a acute", "a circumflex", "a tilde", "a oomlaut", "a ring",
/*230*/ "ae", "c cidella", "e grave", "e acute",
/*234*/ "e circumflex", "e oomlaut", "i grave", "i acute",
	    "i circumflex",
/*239*/ "i oomlaut", "eth", "n tilde", "o grave", "o acute",
	    "o circumflex",
/*245*/ "o tilde", "o oomlaut", "divided by", "o stroke", "u grave",
	    "u acute",
/* 251 */ "u circumflex", "u oomlaut", "y acute", "thorn", "y oomlaut"
पूर्ण;

/* array of 256 u_लघु (one क्रम each अक्षरacter)
 * initialized to शेष_अक्षरtab and user selectable via
 * /sys/module/speakup/parameters/अक्षरtab
 */
u_लघु spk_अक्षरtab[256];

अटल u_लघु शेष_अक्षरtab[256] = अणु
	B_CTL, B_CTL, B_CTL, B_CTL, B_CTL, B_CTL, B_CTL, B_CTL,	/* 0-7 */
	B_CTL, B_CTL, A_CTL, B_CTL, B_CTL, B_CTL, B_CTL, B_CTL,	/* 8-15 */
	B_CTL, B_CTL, B_CTL, B_CTL, B_CTL, B_CTL, B_CTL, B_CTL,	/*16-23 */
	B_CTL, B_CTL, B_CTL, B_CTL, B_CTL, B_CTL, B_CTL, B_CTL,	/* 24-31 */
	WDLM, A_PUNC, PUNC, PUNC, PUNC, PUNC, PUNC, A_PUNC,	/*  !"#$%&' */
	PUNC, PUNC, PUNC, PUNC, A_PUNC, A_PUNC, A_PUNC, PUNC,	/* ()*+, -./ */
	NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM,	/* 01234567 */
	NUM, NUM, A_PUNC, PUNC, PUNC, PUNC, PUNC, A_PUNC,	/* 89:;<=>? */
	PUNC, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP,	/* @ABCDEFG */
	A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP,	/* HIJKLMNO */
	A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP,	/* PQRSTUVW */
	A_CAP, A_CAP, A_CAP, PUNC, PUNC, PUNC, PUNC, PUNC,	/* XYZ[\]^_ */
	PUNC, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA,	/* `abcdefg */
	ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA,	/* hijklmno */
	ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA,	/* pqrstuvw */
	ALPHA, ALPHA, ALPHA, PUNC, PUNC, PUNC, PUNC, 0,	/* xyzअणु|पूर्ण~ */
	B_CAPSYM, B_CAPSYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, /* 128-134 */
	B_SYM,	/* 135 */
	B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, /* 136-142 */
	B_CAPSYM,	/* 143 */
	B_CAPSYM, B_CAPSYM, B_SYM, B_CAPSYM, B_SYM, B_SYM, B_SYM, /* 144-150 */
	B_SYM,	/* 151 */
	B_SYM, B_SYM, B_CAPSYM, B_CAPSYM, B_SYM, B_SYM, B_SYM, /*152-158 */
	B_SYM,	/* 159 */
	WDLM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_CAPSYM, /* 160-166 */
	B_SYM,	/* 167 */
	B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM,	/* 168-175 */
	B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM,	/* 176-183 */
	B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM,	/* 184-191 */
	A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP,	/* 192-199 */
	A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP,	/* 200-207 */
	A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, B_SYM,	/* 208-215 */
	A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, ALPHA,	/* 216-223 */
	ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA,	/* 224-231 */
	ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA,	/* 232-239 */
	ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, B_SYM,	/* 240-247 */
	ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA, ALPHA	/* 248-255 */
पूर्ण;

काष्ठा task_काष्ठा *speakup_task;
काष्ठा bleep spk_unprocessed_sound;
अटल पूर्णांक spk_keyकरोwn;
अटल u16 spk_lastkey;
अटल u_अक्षर spk_बंद_press, keymap_flags;
अटल u_अक्षर last_keycode, this_speakup_key;
अटल u_दीर्घ last_spk_jअगरfy;

काष्ठा st_spk_t *speakup_console[MAX_NR_CONSOLES];

DEFINE_MUTEX(spk_mutex);

अटल पूर्णांक keyboard_notअगरier_call(काष्ठा notअगरier_block *,
				  अचिन्हित दीर्घ code, व्योम *param);

अटल काष्ठा notअगरier_block keyboard_notअगरier_block = अणु
	.notअगरier_call = keyboard_notअगरier_call,
पूर्ण;

अटल पूर्णांक vt_notअगरier_call(काष्ठा notअगरier_block *,
			    अचिन्हित दीर्घ code, व्योम *param);

अटल काष्ठा notअगरier_block vt_notअगरier_block = अणु
	.notअगरier_call = vt_notअगरier_call,
पूर्ण;

अटल अचिन्हित अक्षर get_attributes(काष्ठा vc_data *vc, u16 *pos)
अणु
	pos = screen_pos(vc, pos - (u16 *)vc->vc_origin, true);
	वापस (scr_पढ़ोw(pos) & ~vc->vc_hi_font_mask) >> 8;
पूर्ण

अटल व्योम speakup_date(काष्ठा vc_data *vc)
अणु
	spk_x = spk_cx = vc->state.x;
	spk_y = spk_cy = vc->state.y;
	spk_pos = spk_cp = vc->vc_pos;
	spk_old_attr = spk_attr;
	spk_attr = get_attributes(vc, (u_लघु *)spk_pos);
पूर्ण

अटल व्योम bleep(u_लघु val)
अणु
	अटल स्थिर लघु vals[] = अणु
		350, 370, 392, 414, 440, 466, 491, 523, 554, 587, 619, 659
	पूर्ण;
	लघु freq;
	पूर्णांक समय = spk_bleep_समय;

	freq = vals[val % 12];
	अगर (val > 11)
		freq *= (1 << (val / 12));
	spk_unprocessed_sound.freq = freq;
	spk_unprocessed_sound.jअगरfies = msecs_to_jअगरfies(समय);
	spk_unprocessed_sound.active = 1;
	/* We can only have 1 active sound at a समय. */
पूर्ण

अटल व्योम speakup_shut_up(काष्ठा vc_data *vc)
अणु
	अगर (spk_समाप्तed)
		वापस;
	spk_shut_up |= 0x01;
	spk_parked &= 0xfe;
	speakup_date(vc);
	अगर (synth)
		spk_करो_flush();
पूर्ण

अटल व्योम speech_समाप्त(काष्ठा vc_data *vc)
अणु
	अक्षर val = synth->is_alive(synth);

	अगर (val == 0)
		वापस;

	/* re-enables synth, अगर disabled */
	अगर (val == 2 || spk_समाप्तed) अणु
		/* dead */
		spk_shut_up &= ~0x40;
		synth_म_लिखो("%s\n", spk_msg_get(MSG_IAM_ALIVE));
	पूर्ण अन्यथा अणु
		synth_म_लिखो("%s\n", spk_msg_get(MSG_YOU_KILLED_SPEAKUP));
		spk_shut_up |= 0x40;
	पूर्ण
पूर्ण

अटल व्योम speakup_off(काष्ठा vc_data *vc)
अणु
	अगर (spk_shut_up & 0x80) अणु
		spk_shut_up &= 0x7f;
		synth_म_लिखो("%s\n", spk_msg_get(MSG_HEY_THATS_BETTER));
	पूर्ण अन्यथा अणु
		spk_shut_up |= 0x80;
		synth_म_लिखो("%s\n", spk_msg_get(MSG_YOU_TURNED_ME_OFF));
	पूर्ण
	speakup_date(vc);
पूर्ण

अटल व्योम speakup_parked(काष्ठा vc_data *vc)
अणु
	अगर (spk_parked & 0x80) अणु
		spk_parked = 0;
		synth_म_लिखो("%s\n", spk_msg_get(MSG_UNPARKED));
	पूर्ण अन्यथा अणु
		spk_parked |= 0x80;
		synth_म_लिखो("%s\n", spk_msg_get(MSG_PARKED));
	पूर्ण
पूर्ण

अटल व्योम speakup_cut(काष्ठा vc_data *vc)
अणु
	अटल स्थिर अक्षर err_buf[] = "set selection failed";
	पूर्णांक ret;

	अगर (!mark_cut_flag) अणु
		mark_cut_flag = 1;
		spk_xs = (u_लघु)spk_x;
		spk_ys = (u_लघु)spk_y;
		spk_sel_cons = vc;
		synth_म_लिखो("%s\n", spk_msg_get(MSG_MARK));
		वापस;
	पूर्ण
	spk_xe = (u_लघु)spk_x;
	spk_ye = (u_लघु)spk_y;
	mark_cut_flag = 0;
	synth_म_लिखो("%s\n", spk_msg_get(MSG_CUT));

	ret = speakup_set_selection(tty);

	चयन (ret) अणु
	हाल 0:
		अवरोध;		/* no error */
	हाल -EFAULT:
		pr_warn("%sEFAULT\n", err_buf);
		अवरोध;
	हाल -EINVAL:
		pr_warn("%sEINVAL\n", err_buf);
		अवरोध;
	हाल -ENOMEM:
		pr_warn("%sENOMEM\n", err_buf);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम speakup_paste(काष्ठा vc_data *vc)
अणु
	अगर (mark_cut_flag) अणु
		mark_cut_flag = 0;
		synth_म_लिखो("%s\n", spk_msg_get(MSG_MARK_CLEARED));
	पूर्ण अन्यथा अणु
		synth_म_लिखो("%s\n", spk_msg_get(MSG_PASTE));
		speakup_paste_selection(tty);
	पूर्ण
पूर्ण

अटल व्योम say_attributes(काष्ठा vc_data *vc)
अणु
	पूर्णांक fg = spk_attr & 0x0f;
	पूर्णांक bg = spk_attr >> 4;

	अगर (fg > 8) अणु
		synth_म_लिखो("%s ", spk_msg_get(MSG_BRIGHT));
		fg -= 8;
	पूर्ण
	synth_म_लिखो("%s", spk_msg_get(MSG_COLORS_START + fg));
	अगर (bg > 7) अणु
		synth_म_लिखो(" %s ", spk_msg_get(MSG_ON_BLINKING));
		bg -= 8;
	पूर्ण अन्यथा अणु
		synth_म_लिखो(" %s ", spk_msg_get(MSG_ON));
	पूर्ण
	synth_म_लिखो("%s\n", spk_msg_get(MSG_COLORS_START + bg));
पूर्ण

/* must be ordered same as edge_msgs in क्रमागत msg_index_t */
क्रमागत edge अणु
	edge_none = 0,
	edge_top,
	edge_bottom,
	edge_left,
	edge_right,
	edge_quiet
पूर्ण;

अटल व्योम announce_edge(काष्ठा vc_data *vc, क्रमागत edge msg_id)
अणु
	अगर (spk_bleeps & 1)
		bleep(spk_y);
	अगर ((spk_bleeps & 2) && (msg_id < edge_quiet))
		synth_म_लिखो("%s\n",
			     spk_msg_get(MSG_EDGE_MSGS_START + msg_id - 1));
पूर्ण

अटल व्योम speak_अक्षर(u16 ch)
अणु
	अक्षर *cp;
	काष्ठा var_t *direct = spk_get_var(सूचीECT);

	अगर (ch >= 0x100 || (direct && direct->u.n.value)) अणु
		अगर (ch < 0x100 && IS_CHAR(ch, B_CAP)) अणु
			spk_pitch_shअगरt++;
			synth_म_लिखो("%s", spk_str_caps_start);
		पूर्ण
		synth_putwc_s(ch);
		अगर (ch < 0x100 && IS_CHAR(ch, B_CAP))
			synth_म_लिखो("%s", spk_str_caps_stop);
		वापस;
	पूर्ण

	cp = spk_अक्षरacters[ch];
	अगर (!cp) अणु
		pr_info("%s: cp == NULL!\n", __func__);
		वापस;
	पूर्ण
	अगर (IS_CHAR(ch, B_CAP)) अणु
		spk_pitch_shअगरt++;
		synth_म_लिखो("%s %s %s",
			     spk_str_caps_start, cp, spk_str_caps_stop);
	पूर्ण अन्यथा अणु
		अगर (*cp == '^') अणु
			cp++;
			synth_म_लिखो(" %s%s ", spk_msg_get(MSG_CTRL), cp);
		पूर्ण अन्यथा अणु
			synth_म_लिखो(" %s ", cp);
		पूर्ण
	पूर्ण
पूर्ण

अटल u16 get_अक्षर(काष्ठा vc_data *vc, u16 *pos, u_अक्षर *attribs)
अणु
	u16 ch = ' ';

	अगर (vc && pos) अणु
		u16 w;
		u16 c;

		pos = screen_pos(vc, pos - (u16 *)vc->vc_origin, true);
		w = scr_पढ़ोw(pos);
		c = w & 0xff;

		अगर (w & vc->vc_hi_font_mask) अणु
			w &= ~vc->vc_hi_font_mask;
			c |= 0x100;
		पूर्ण

		ch = inverse_translate(vc, c, 1);
		*attribs = (w & 0xff00) >> 8;
	पूर्ण
	वापस ch;
पूर्ण

अटल व्योम say_अक्षर(काष्ठा vc_data *vc)
अणु
	u16 ch;

	spk_old_attr = spk_attr;
	ch = get_अक्षर(vc, (u_लघु *)spk_pos, &spk_attr);
	अगर (spk_attr != spk_old_attr) अणु
		अगर (spk_attrib_bleep & 1)
			bleep(spk_y);
		अगर (spk_attrib_bleep & 2)
			say_attributes(vc);
	पूर्ण
	speak_अक्षर(ch);
पूर्ण

अटल व्योम say_phonetic_अक्षर(काष्ठा vc_data *vc)
अणु
	u16 ch;

	spk_old_attr = spk_attr;
	ch = get_अक्षर(vc, (u_लघु *)spk_pos, &spk_attr);
	अगर (ch <= 0x7f && है_अक्षर(ch)) अणु
		ch &= 0x1f;
		synth_म_लिखो("%s\n", phonetic[--ch]);
	पूर्ण अन्यथा अणु
		अगर (ch < 0x100 && IS_CHAR(ch, B_NUM))
			synth_म_लिखो("%s ", spk_msg_get(MSG_NUMBER));
		speak_अक्षर(ch);
	पूर्ण
पूर्ण

अटल व्योम say_prev_अक्षर(काष्ठा vc_data *vc)
अणु
	spk_parked |= 0x01;
	अगर (spk_x == 0) अणु
		announce_edge(vc, edge_left);
		वापस;
	पूर्ण
	spk_x--;
	spk_pos -= 2;
	say_अक्षर(vc);
पूर्ण

अटल व्योम say_next_अक्षर(काष्ठा vc_data *vc)
अणु
	spk_parked |= 0x01;
	अगर (spk_x == vc->vc_cols - 1) अणु
		announce_edge(vc, edge_right);
		वापस;
	पूर्ण
	spk_x++;
	spk_pos += 2;
	say_अक्षर(vc);
पूर्ण

/* get_word - will first check to see अगर the अक्षरacter under the
 * पढ़ोing cursor is a space and अगर spk_say_word_ctl is true it will
 * वापस the word space.  If spk_say_word_ctl is not set it will check to
 * see अगर there is a word starting on the next position to the right
 * and वापस that word अगर it exists.  If it करोes not exist it will
 * move left to the beginning of any previous word on the line or the
 * beginning off the line whichever comes first..
 */

अटल u_दीर्घ get_word(काष्ठा vc_data *vc)
अणु
	u_दीर्घ cnt = 0, पंचांगpx = spk_x, पंचांगp_pos = spk_pos;
	u16 ch;
	u16 attr_ch;
	u_अक्षर temp;

	spk_old_attr = spk_attr;
	ch = get_अक्षर(vc, (u_लघु *)पंचांगp_pos, &temp);

/* decided to take out the sayword अगर on a space (mis-inक्रमmation */
	अगर (spk_say_word_ctl && ch == SPACE) अणु
		*buf = '\0';
		synth_म_लिखो("%s\n", spk_msg_get(MSG_SPACE));
		वापस 0;
	पूर्ण अन्यथा अगर (पंचांगpx < vc->vc_cols - 2 &&
		   (ch == SPACE || ch == 0 || (ch < 0x100 && IS_WDLM(ch))) &&
		   get_अक्षर(vc, (u_लघु *)पंचांगp_pos + 1, &temp) > SPACE) अणु
		पंचांगp_pos += 2;
		पंचांगpx++;
	पूर्ण अन्यथा अणु
		जबतक (पंचांगpx > 0) अणु
			ch = get_अक्षर(vc, (u_लघु *)पंचांगp_pos - 1, &temp);
			अगर ((ch == SPACE || ch == 0 ||
			     (ch < 0x100 && IS_WDLM(ch))) &&
			    get_अक्षर(vc, (u_लघु *)पंचांगp_pos, &temp) > SPACE)
				अवरोध;
			पंचांगp_pos -= 2;
			पंचांगpx--;
		पूर्ण
	पूर्ण
	attr_ch = get_अक्षर(vc, (u_लघु *)पंचांगp_pos, &spk_attr);
	buf[cnt++] = attr_ch;
	जबतक (पंचांगpx < vc->vc_cols - 1) अणु
		पंचांगp_pos += 2;
		पंचांगpx++;
		ch = get_अक्षर(vc, (u_लघु *)पंचांगp_pos, &temp);
		अगर (ch == SPACE || ch == 0 ||
		    (buf[cnt - 1] < 0x100 && IS_WDLM(buf[cnt - 1]) &&
		     ch > SPACE))
			अवरोध;
		buf[cnt++] = ch;
	पूर्ण
	buf[cnt] = '\0';
	वापस cnt;
पूर्ण

अटल व्योम say_word(काष्ठा vc_data *vc)
अणु
	u_दीर्घ cnt = get_word(vc);
	u_लघु saved_punc_mask = spk_punc_mask;

	अगर (cnt == 0)
		वापस;
	spk_punc_mask = PUNC;
	buf[cnt++] = SPACE;
	spkup_ग_लिखो(buf, cnt);
	spk_punc_mask = saved_punc_mask;
पूर्ण

अटल व्योम say_prev_word(काष्ठा vc_data *vc)
अणु
	u_अक्षर temp;
	u16 ch;
	क्रमागत edge edge_said = edge_none;
	u_लघु last_state = 0, state = 0;

	spk_parked |= 0x01;

	अगर (spk_x == 0) अणु
		अगर (spk_y == 0) अणु
			announce_edge(vc, edge_top);
			वापस;
		पूर्ण
		spk_y--;
		spk_x = vc->vc_cols;
		edge_said = edge_quiet;
	पूर्ण
	जबतक (1) अणु
		अगर (spk_x == 0) अणु
			अगर (spk_y == 0) अणु
				edge_said = edge_top;
				अवरोध;
			पूर्ण
			अगर (edge_said != edge_quiet)
				edge_said = edge_left;
			अगर (state > 0)
				अवरोध;
			spk_y--;
			spk_x = vc->vc_cols - 1;
		पूर्ण अन्यथा अणु
			spk_x--;
		पूर्ण
		spk_pos -= 2;
		ch = get_अक्षर(vc, (u_लघु *)spk_pos, &temp);
		अगर (ch == SPACE || ch == 0)
			state = 0;
		अन्यथा अगर (ch < 0x100 && IS_WDLM(ch))
			state = 1;
		अन्यथा
			state = 2;
		अगर (state < last_state) अणु
			spk_pos += 2;
			spk_x++;
			अवरोध;
		पूर्ण
		last_state = state;
	पूर्ण
	अगर (spk_x == 0 && edge_said == edge_quiet)
		edge_said = edge_left;
	अगर (edge_said > edge_none && edge_said < edge_quiet)
		announce_edge(vc, edge_said);
	say_word(vc);
पूर्ण

अटल व्योम say_next_word(काष्ठा vc_data *vc)
अणु
	u_अक्षर temp;
	u16 ch;
	क्रमागत edge edge_said = edge_none;
	u_लघु last_state = 2, state = 0;

	spk_parked |= 0x01;
	अगर (spk_x == vc->vc_cols - 1 && spk_y == vc->vc_rows - 1) अणु
		announce_edge(vc, edge_bottom);
		वापस;
	पूर्ण
	जबतक (1) अणु
		ch = get_अक्षर(vc, (u_लघु *)spk_pos, &temp);
		अगर (ch == SPACE || ch == 0)
			state = 0;
		अन्यथा अगर (ch < 0x100 && IS_WDLM(ch))
			state = 1;
		अन्यथा
			state = 2;
		अगर (state > last_state)
			अवरोध;
		अगर (spk_x >= vc->vc_cols - 1) अणु
			अगर (spk_y == vc->vc_rows - 1) अणु
				edge_said = edge_bottom;
				अवरोध;
			पूर्ण
			state = 0;
			spk_y++;
			spk_x = 0;
			edge_said = edge_right;
		पूर्ण अन्यथा अणु
			spk_x++;
		पूर्ण
		spk_pos += 2;
		last_state = state;
	पूर्ण
	अगर (edge_said > edge_none)
		announce_edge(vc, edge_said);
	say_word(vc);
पूर्ण

अटल व्योम spell_word(काष्ठा vc_data *vc)
अणु
	अटल अक्षर स्थिर *delay_str[] = अणु "", ",", ".", ". .", ". . ." पूर्ण;
	u16 *cp = buf;
	अक्षर *cp1;
	अक्षर *str_cap = spk_str_caps_stop;
	अक्षर *last_cap = spk_str_caps_stop;
	काष्ठा var_t *direct = spk_get_var(सूचीECT);
	u16 ch;

	अगर (!get_word(vc))
		वापस;
	जबतक ((ch = *cp)) अणु
		अगर (cp != buf)
			synth_म_लिखो(" %s ", delay_str[spk_spell_delay]);
		/* FIXME: Non-latin1 considered as lower हाल */
		अगर (ch < 0x100 && IS_CHAR(ch, B_CAP)) अणु
			str_cap = spk_str_caps_start;
			अगर (*spk_str_caps_stop)
				spk_pitch_shअगरt++;
			अन्यथा	/* synth has no pitch */
				last_cap = spk_str_caps_stop;
		पूर्ण अन्यथा अणु
			str_cap = spk_str_caps_stop;
		पूर्ण
		अगर (str_cap != last_cap) अणु
			synth_म_लिखो("%s", str_cap);
			last_cap = str_cap;
		पूर्ण
		अगर (ch >= 0x100 || (direct && direct->u.n.value)) अणु
			synth_putwc_s(ch);
		पूर्ण अन्यथा अगर (this_speakup_key == SPELL_PHONETIC &&
		    ch <= 0x7f && है_अक्षर(ch)) अणु
			ch &= 0x1f;
			cp1 = phonetic[--ch];
			synth_म_लिखो("%s", cp1);
		पूर्ण अन्यथा अणु
			cp1 = spk_अक्षरacters[ch];
			अगर (*cp1 == '^') अणु
				synth_म_लिखो("%s", spk_msg_get(MSG_CTRL));
				cp1++;
			पूर्ण
			synth_म_लिखो("%s", cp1);
		पूर्ण
		cp++;
	पूर्ण
	अगर (str_cap != spk_str_caps_stop)
		synth_म_लिखो("%s", spk_str_caps_stop);
पूर्ण

अटल पूर्णांक get_line(काष्ठा vc_data *vc)
अणु
	u_दीर्घ पंचांगp = spk_pos - (spk_x * 2);
	पूर्णांक i = 0;
	u_अक्षर पंचांगp2;

	spk_old_attr = spk_attr;
	spk_attr = get_attributes(vc, (u_लघु *)spk_pos);
	क्रम (i = 0; i < vc->vc_cols; i++) अणु
		buf[i] = get_अक्षर(vc, (u_लघु *)पंचांगp, &पंचांगp2);
		पंचांगp += 2;
	पूर्ण
	क्रम (--i; i >= 0; i--)
		अगर (buf[i] != SPACE)
			अवरोध;
	वापस ++i;
पूर्ण

अटल व्योम say_line(काष्ठा vc_data *vc)
अणु
	पूर्णांक i = get_line(vc);
	u16 *cp;
	u_लघु saved_punc_mask = spk_punc_mask;

	अगर (i == 0) अणु
		synth_म_लिखो("%s\n", spk_msg_get(MSG_BLANK));
		वापस;
	पूर्ण
	buf[i++] = '\n';
	अगर (this_speakup_key == SAY_LINE_INDENT) अणु
		cp = buf;
		जबतक (*cp == SPACE)
			cp++;
		synth_म_लिखो("%zd, ", (cp - buf) + 1);
	पूर्ण
	spk_punc_mask = spk_punc_masks[spk_पढ़ोing_punc];
	spkup_ग_लिखो(buf, i);
	spk_punc_mask = saved_punc_mask;
पूर्ण

अटल व्योम say_prev_line(काष्ठा vc_data *vc)
अणु
	spk_parked |= 0x01;
	अगर (spk_y == 0) अणु
		announce_edge(vc, edge_top);
		वापस;
	पूर्ण
	spk_y--;
	spk_pos -= vc->vc_size_row;
	say_line(vc);
पूर्ण

अटल व्योम say_next_line(काष्ठा vc_data *vc)
अणु
	spk_parked |= 0x01;
	अगर (spk_y == vc->vc_rows - 1) अणु
		announce_edge(vc, edge_bottom);
		वापस;
	पूर्ण
	spk_y++;
	spk_pos += vc->vc_size_row;
	say_line(vc);
पूर्ण

अटल पूर्णांक say_from_to(काष्ठा vc_data *vc, u_दीर्घ from, u_दीर्घ to,
		       पूर्णांक पढ़ो_punc)
अणु
	पूर्णांक i = 0;
	u_अक्षर पंचांगp;
	u_लघु saved_punc_mask = spk_punc_mask;

	spk_old_attr = spk_attr;
	spk_attr = get_attributes(vc, (u_लघु *)from);
	जबतक (from < to) अणु
		buf[i++] = get_अक्षर(vc, (u_लघु *)from, &पंचांगp);
		from += 2;
		अगर (i >= vc->vc_size_row)
			अवरोध;
	पूर्ण
	क्रम (--i; i >= 0; i--)
		अगर (buf[i] != SPACE)
			अवरोध;
	buf[++i] = SPACE;
	buf[++i] = '\0';
	अगर (i < 1)
		वापस i;
	अगर (पढ़ो_punc)
		spk_punc_mask = spk_punc_info[spk_पढ़ोing_punc].mask;
	spkup_ग_लिखो(buf, i);
	अगर (पढ़ो_punc)
		spk_punc_mask = saved_punc_mask;
	वापस i - 1;
पूर्ण

अटल व्योम say_line_from_to(काष्ठा vc_data *vc, u_दीर्घ from, u_दीर्घ to,
			     पूर्णांक पढ़ो_punc)
अणु
	u_दीर्घ start = vc->vc_origin + (spk_y * vc->vc_size_row);
	u_दीर्घ end = start + (to * 2);

	start += from * 2;
	अगर (say_from_to(vc, start, end, पढ़ो_punc) <= 0)
		अगर (cursor_track != पढ़ो_all_mode)
			synth_म_लिखो("%s\n", spk_msg_get(MSG_BLANK));
पूर्ण

/* Sentence Reading Commands */

अटल पूर्णांक currsentence;
अटल पूर्णांक numsentences[2];
अटल u16 *sentbufend[2];
अटल u16 *senपंचांगarks[2][10];
अटल पूर्णांक currbuf;
अटल पूर्णांक bn;
अटल u16 sentbuf[2][256];

अटल पूर्णांक say_sentence_num(पूर्णांक num, पूर्णांक prev)
अणु
	bn = currbuf;
	currsentence = num + 1;
	अगर (prev && --bn == -1)
		bn = 1;

	अगर (num > numsentences[bn])
		वापस 0;

	spkup_ग_लिखो(senपंचांगarks[bn][num], sentbufend[bn] - senपंचांगarks[bn][num]);
	वापस 1;
पूर्ण

अटल पूर्णांक get_sentence_buf(काष्ठा vc_data *vc, पूर्णांक पढ़ो_punc)
अणु
	u_दीर्घ start, end;
	पूर्णांक i, bn;
	u_अक्षर पंचांगp;

	currbuf++;
	अगर (currbuf == 2)
		currbuf = 0;
	bn = currbuf;
	start = vc->vc_origin + ((spk_y) * vc->vc_size_row);
	end = vc->vc_origin + ((spk_y) * vc->vc_size_row) + vc->vc_cols * 2;

	numsentences[bn] = 0;
	senपंचांगarks[bn][0] = &sentbuf[bn][0];
	i = 0;
	spk_old_attr = spk_attr;
	spk_attr = get_attributes(vc, (u_लघु *)start);

	जबतक (start < end) अणु
		sentbuf[bn][i] = get_अक्षर(vc, (u_लघु *)start, &पंचांगp);
		अगर (i > 0) अणु
			अगर (sentbuf[bn][i] == SPACE &&
			    sentbuf[bn][i - 1] == '.' &&
			    numsentences[bn] < 9) अणु
				/* Sentence Marker */
				numsentences[bn]++;
				senपंचांगarks[bn][numsentences[bn]] =
				    &sentbuf[bn][i];
			पूर्ण
		पूर्ण
		i++;
		start += 2;
		अगर (i >= vc->vc_size_row)
			अवरोध;
	पूर्ण

	क्रम (--i; i >= 0; i--)
		अगर (sentbuf[bn][i] != SPACE)
			अवरोध;

	अगर (i < 1)
		वापस -1;

	sentbuf[bn][++i] = SPACE;
	sentbuf[bn][++i] = '\0';

	sentbufend[bn] = &sentbuf[bn][i];
	वापस numsentences[bn];
पूर्ण

अटल व्योम say_screen_from_to(काष्ठा vc_data *vc, u_दीर्घ from, u_दीर्घ to)
अणु
	u_दीर्घ start = vc->vc_origin, end;

	अगर (from > 0)
		start += from * vc->vc_size_row;
	अगर (to > vc->vc_rows)
		to = vc->vc_rows;
	end = vc->vc_origin + (to * vc->vc_size_row);
	क्रम (from = start; from < end; from = to) अणु
		to = from + vc->vc_size_row;
		say_from_to(vc, from, to, 1);
	पूर्ण
पूर्ण

अटल व्योम say_screen(काष्ठा vc_data *vc)
अणु
	say_screen_from_to(vc, 0, vc->vc_rows);
पूर्ण

अटल व्योम speakup_win_say(काष्ठा vc_data *vc)
अणु
	u_दीर्घ start, end, from, to;

	अगर (win_start < 2) अणु
		synth_म_लिखो("%s\n", spk_msg_get(MSG_NO_WINDOW));
		वापस;
	पूर्ण
	start = vc->vc_origin + (win_top * vc->vc_size_row);
	end = vc->vc_origin + (win_bottom * vc->vc_size_row);
	जबतक (start <= end) अणु
		from = start + (win_left * 2);
		to = start + (win_right * 2);
		say_from_to(vc, from, to, 1);
		start += vc->vc_size_row;
	पूर्ण
पूर्ण

अटल व्योम top_edge(काष्ठा vc_data *vc)
अणु
	spk_parked |= 0x01;
	spk_pos = vc->vc_origin + 2 * spk_x;
	spk_y = 0;
	say_line(vc);
पूर्ण

अटल व्योम bottom_edge(काष्ठा vc_data *vc)
अणु
	spk_parked |= 0x01;
	spk_pos += (vc->vc_rows - spk_y - 1) * vc->vc_size_row;
	spk_y = vc->vc_rows - 1;
	say_line(vc);
पूर्ण

अटल व्योम left_edge(काष्ठा vc_data *vc)
अणु
	spk_parked |= 0x01;
	spk_pos -= spk_x * 2;
	spk_x = 0;
	say_अक्षर(vc);
पूर्ण

अटल व्योम right_edge(काष्ठा vc_data *vc)
अणु
	spk_parked |= 0x01;
	spk_pos += (vc->vc_cols - spk_x - 1) * 2;
	spk_x = vc->vc_cols - 1;
	say_अक्षर(vc);
पूर्ण

अटल व्योम say_first_अक्षर(काष्ठा vc_data *vc)
अणु
	पूर्णांक i, len = get_line(vc);
	u16 ch;

	spk_parked |= 0x01;
	अगर (len == 0) अणु
		synth_म_लिखो("%s\n", spk_msg_get(MSG_BLANK));
		वापस;
	पूर्ण
	क्रम (i = 0; i < len; i++)
		अगर (buf[i] != SPACE)
			अवरोध;
	ch = buf[i];
	spk_pos -= (spk_x - i) * 2;
	spk_x = i;
	synth_म_लिखो("%d, ", ++i);
	speak_अक्षर(ch);
पूर्ण

अटल व्योम say_last_अक्षर(काष्ठा vc_data *vc)
अणु
	पूर्णांक len = get_line(vc);
	u16 ch;

	spk_parked |= 0x01;
	अगर (len == 0) अणु
		synth_म_लिखो("%s\n", spk_msg_get(MSG_BLANK));
		वापस;
	पूर्ण
	ch = buf[--len];
	spk_pos -= (spk_x - len) * 2;
	spk_x = len;
	synth_म_लिखो("%d, ", ++len);
	speak_अक्षर(ch);
पूर्ण

अटल व्योम say_position(काष्ठा vc_data *vc)
अणु
	synth_म_लिखो(spk_msg_get(MSG_POS_INFO), spk_y + 1, spk_x + 1,
		     vc->vc_num + 1);
	synth_म_लिखो("\n");
पूर्ण

/* Added by brianb */
अटल व्योम say_अक्षर_num(काष्ठा vc_data *vc)
अणु
	u_अक्षर पंचांगp;
	u16 ch = get_अक्षर(vc, (u_लघु *)spk_pos, &पंचांगp);

	synth_म_लिखो(spk_msg_get(MSG_CHAR_INFO), ch, ch);
पूर्ण

/* these are stub functions to keep keyboard.c happy. */

अटल व्योम say_from_top(काष्ठा vc_data *vc)
अणु
	say_screen_from_to(vc, 0, spk_y);
पूर्ण

अटल व्योम say_to_bottom(काष्ठा vc_data *vc)
अणु
	say_screen_from_to(vc, spk_y, vc->vc_rows);
पूर्ण

अटल व्योम say_from_left(काष्ठा vc_data *vc)
अणु
	say_line_from_to(vc, 0, spk_x, 1);
पूर्ण

अटल व्योम say_to_right(काष्ठा vc_data *vc)
अणु
	say_line_from_to(vc, spk_x, vc->vc_cols, 1);
पूर्ण

/* end of stub functions. */

अटल व्योम spkup_ग_लिखो(स्थिर u16 *in_buf, पूर्णांक count)
अणु
	अटल पूर्णांक rep_count;
	अटल u16 ch = '\0', old_ch = '\0';
	अटल u_लघु अक्षर_type, last_type;
	पूर्णांक in_count = count;

	spk_keyकरोwn = 0;
	जबतक (count--) अणु
		अगर (cursor_track == पढ़ो_all_mode) अणु
			/* Insert Sentence Index */
			अगर ((in_buf == senपंचांगarks[bn][currsentence]) &&
			    (currsentence <= numsentences[bn]))
				synth_insert_next_index(currsentence++);
		पूर्ण
		ch = *in_buf++;
		अगर (ch < 0x100)
			अक्षर_type = spk_अक्षरtab[ch];
		अन्यथा
			अक्षर_type = ALPHA;
		अगर (ch == old_ch && !(अक्षर_type & B_NUM)) अणु
			अगर (++rep_count > 2)
				जारी;
		पूर्ण अन्यथा अणु
			अगर ((last_type & CH_RPT) && rep_count > 2) अणु
				synth_म_लिखो(" ");
				synth_म_लिखो(spk_msg_get(MSG_REPEAT_DESC),
					     ++rep_count);
				synth_म_लिखो(" ");
			पूर्ण
			rep_count = 0;
		पूर्ण
		अगर (ch == spk_lastkey) अणु
			rep_count = 0;
			अगर (spk_key_echo == 1 && ch >= MINECHOCHAR)
				speak_अक्षर(ch);
		पूर्ण अन्यथा अगर (अक्षर_type & B_ALPHA) अणु
			अगर ((synth_flags & SF_DEC) && (last_type & PUNC))
				synth_buffer_add(SPACE);
			synth_putwc_s(ch);
		पूर्ण अन्यथा अगर (अक्षर_type & B_NUM) अणु
			rep_count = 0;
			synth_putwc_s(ch);
		पूर्ण अन्यथा अगर (अक्षर_type & spk_punc_mask) अणु
			speak_अक्षर(ch);
			अक्षर_type &= ~PUNC;	/* क्रम dec nospell processing */
		पूर्ण अन्यथा अगर (अक्षर_type & SYNTH_OK) अणु
			/* these are usually puncts like . and , which synth
			 * needs क्रम expression.
			 * suppress multiple to get rid of दीर्घ छोड़ोs and
			 * clear repeat count
			 * so अगर someone has
			 * repeats on you करोn't get nothing repeated count
			 */
			अगर (ch != old_ch)
				synth_putwc_s(ch);
			अन्यथा
				rep_count = 0;
		पूर्ण अन्यथा अणु
/* send space and record position, अगर next is num overग_लिखो space */
			अगर (old_ch != ch)
				synth_buffer_add(SPACE);
			अन्यथा
				rep_count = 0;
		पूर्ण
		old_ch = ch;
		last_type = अक्षर_type;
	पूर्ण
	spk_lastkey = 0;
	अगर (in_count > 2 && rep_count > 2) अणु
		अगर (last_type & CH_RPT) अणु
			synth_म_लिखो(" ");
			synth_म_लिखो(spk_msg_get(MSG_REPEAT_DESC2),
				     ++rep_count);
			synth_म_लिखो(" ");
		पूर्ण
		rep_count = 0;
	पूर्ण
पूर्ण

अटल स्थिर पूर्णांक NUM_CTL_LABELS = (MSG_CTL_END - MSG_CTL_START + 1);

अटल व्योम पढ़ो_all_करोc(काष्ठा vc_data *vc);
अटल व्योम cursor_करोne(काष्ठा समयr_list *unused);
अटल DEFINE_TIMER(cursor_समयr, cursor_करोne);

अटल व्योम करो_handle_shअगरt(काष्ठा vc_data *vc, u_अक्षर value, अक्षर up_flag)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!synth || up_flag || spk_समाप्तed)
		वापस;
	spin_lock_irqsave(&speakup_info.spinlock, flags);
	अगर (cursor_track == पढ़ो_all_mode) अणु
		चयन (value) अणु
		हाल KVAL(K_SHIFT):
			del_समयr(&cursor_समयr);
			spk_shut_up &= 0xfe;
			spk_करो_flush();
			पढ़ो_all_करोc(vc);
			अवरोध;
		हाल KVAL(K_CTRL):
			del_समयr(&cursor_समयr);
			cursor_track = prev_cursor_track;
			spk_shut_up &= 0xfe;
			spk_करो_flush();
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		spk_shut_up &= 0xfe;
		spk_करो_flush();
	पूर्ण
	अगर (spk_say_ctrl && value < NUM_CTL_LABELS)
		synth_म_लिखो("%s", spk_msg_get(MSG_CTL_START + value));
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
पूर्ण

अटल व्योम करो_handle_latin(काष्ठा vc_data *vc, u_अक्षर value, अक्षर up_flag)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	अगर (up_flag) अणु
		spk_lastkey = 0;
		spk_keyकरोwn = 0;
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		वापस;
	पूर्ण
	अगर (!synth || spk_समाप्तed) अणु
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		वापस;
	पूर्ण
	spk_shut_up &= 0xfe;
	spk_lastkey = value;
	spk_keyकरोwn++;
	spk_parked &= 0xfe;
	अगर (spk_key_echo == 2 && value >= MINECHOCHAR)
		speak_अक्षर(value);
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
पूर्ण

पूर्णांक spk_set_key_info(स्थिर u_अक्षर *key_info, u_अक्षर *k_buffer)
अणु
	पूर्णांक i = 0, states, key_data_len;
	स्थिर u_अक्षर *cp = key_info;
	u_अक्षर *cp1 = k_buffer;
	u_अक्षर ch, version, num_keys;

	version = *cp++;
	अगर (version != KEY_MAP_VER) अणु
		pr_debug("version found %d should be %d\n",
			 version, KEY_MAP_VER);
		वापस -EINVAL;
	पूर्ण
	num_keys = *cp;
	states = (पूर्णांक)cp[1];
	key_data_len = (states + 1) * (num_keys + 1);
	अगर (key_data_len + SHIFT_TBL_SIZE + 4 >= माप(spk_key_buf)) अणु
		pr_debug("too many key_infos (%d over %u)\n",
			 key_data_len + SHIFT_TBL_SIZE + 4,
			 (अचिन्हित पूर्णांक)(माप(spk_key_buf)));
		वापस -EINVAL;
	पूर्ण
	स_रखो(k_buffer, 0, SHIFT_TBL_SIZE);
	स_रखो(spk_our_keys, 0, माप(spk_our_keys));
	spk_shअगरt_table = k_buffer;
	spk_our_keys[0] = spk_shअगरt_table;
	cp1 += SHIFT_TBL_SIZE;
	स_नकल(cp1, cp, key_data_len + 3);
	/* get num_keys, states and data */
	cp1 += 2;		/* now poपूर्णांकing at shअगरt states */
	क्रम (i = 1; i <= states; i++) अणु
		ch = *cp1++;
		अगर (ch >= SHIFT_TBL_SIZE) अणु
			pr_debug("(%d) not valid shift state (max_allowed = %d)\n",
				 ch, SHIFT_TBL_SIZE);
			वापस -EINVAL;
		पूर्ण
		spk_shअगरt_table[ch] = i;
	पूर्ण
	keymap_flags = *cp1++;
	जबतक ((ch = *cp1)) अणु
		अगर (ch >= MAX_KEY) अणु
			pr_debug("(%d), not valid key, (max_allowed = %d)\n",
				 ch, MAX_KEY);
			वापस -EINVAL;
		पूर्ण
		spk_our_keys[ch] = cp1;
		cp1 += states + 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा var_t spk_vars[] = अणु
	/* bell must be first to set high limit */
	अणुBELL_POS, .u.n = अणुशून्य, 0, 0, 0, 0, 0, शून्यपूर्ण पूर्ण,
	अणुSPELL_DELAY, .u.n = अणुशून्य, 0, 0, 4, 0, 0, शून्यपूर्ण पूर्ण,
	अणुATTRIB_BLEEP, .u.n = अणुशून्य, 1, 0, 3, 0, 0, शून्यपूर्ण पूर्ण,
	अणुBLEEPS, .u.n = अणुशून्य, 3, 0, 3, 0, 0, शून्यपूर्ण पूर्ण,
	अणुBLEEP_TIME, .u.n = अणुशून्य, 30, 1, 200, 0, 0, शून्यपूर्ण पूर्ण,
	अणुPUNC_LEVEL, .u.n = अणुशून्य, 1, 0, 4, 0, 0, शून्यपूर्ण पूर्ण,
	अणुREADING_PUNC, .u.n = अणुशून्य, 1, 0, 4, 0, 0, शून्यपूर्ण पूर्ण,
	अणुCURSOR_TIME, .u.n = अणुशून्य, 120, 50, 600, 0, 0, शून्यपूर्ण पूर्ण,
	अणुSAY_CONTROL, TOGGLE_0पूर्ण,
	अणुSAY_WORD_CTL, TOGGLE_0पूर्ण,
	अणुNO_INTERRUPT, TOGGLE_0पूर्ण,
	अणुKEY_ECHO, .u.n = अणुशून्य, 1, 0, 2, 0, 0, शून्यपूर्ण पूर्ण,
	V_LAST_VAR
पूर्ण;

अटल व्योम toggle_cursoring(काष्ठा vc_data *vc)
अणु
	अगर (cursor_track == पढ़ो_all_mode)
		cursor_track = prev_cursor_track;
	अगर (++cursor_track >= CT_Max)
		cursor_track = 0;
	synth_म_लिखो("%s\n", spk_msg_get(MSG_CURSOR_MSGS_START + cursor_track));
पूर्ण

व्योम spk_reset_शेष_अक्षरs(व्योम)
अणु
	पूर्णांक i;

	/* First, मुक्त any non-शेष */
	क्रम (i = 0; i < 256; i++) अणु
		अगर (spk_अक्षरacters[i] &&
		    (spk_अक्षरacters[i] != spk_शेष_अक्षरs[i]))
			kमुक्त(spk_अक्षरacters[i]);
	पूर्ण

	स_नकल(spk_अक्षरacters, spk_शेष_अक्षरs, माप(spk_शेष_अक्षरs));
पूर्ण

व्योम spk_reset_शेष_अक्षरtab(व्योम)
अणु
	स_नकल(spk_अक्षरtab, शेष_अक्षरtab, माप(शेष_अक्षरtab));
पूर्ण

अटल स्थिर काष्ठा st_bits_data *pb_edit;

अटल पूर्णांक edit_bits(काष्ठा vc_data *vc, u_अक्षर type, u_अक्षर ch, u_लघु key)
अणु
	लघु mask = pb_edit->mask, ch_type = spk_अक्षरtab[ch];

	अगर (type != KT_LATIN || (ch_type & B_NUM) || ch < SPACE)
		वापस -1;
	अगर (ch == SPACE) अणु
		synth_म_लिखो("%s\n", spk_msg_get(MSG_EDIT_DONE));
		spk_special_handler = शून्य;
		वापस 1;
	पूर्ण
	अगर (mask < PUNC && !(ch_type & PUNC))
		वापस -1;
	spk_अक्षरtab[ch] ^= mask;
	speak_अक्षर(ch);
	synth_म_लिखो(" %s\n",
		     (spk_अक्षरtab[ch] & mask) ? spk_msg_get(MSG_ON) :
		     spk_msg_get(MSG_OFF));
	वापस 1;
पूर्ण

/* Allocation concurrency is रक्षित by the console semaphore */
अटल पूर्णांक speakup_allocate(काष्ठा vc_data *vc, gfp_t gfp_flags)
अणु
	पूर्णांक vc_num;

	vc_num = vc->vc_num;
	अगर (!speakup_console[vc_num]) अणु
		speakup_console[vc_num] = kzalloc(माप(*speakup_console[0]),
						  gfp_flags);
		अगर (!speakup_console[vc_num])
			वापस -ENOMEM;
		speakup_date(vc);
	पूर्ण अन्यथा अगर (!spk_parked) अणु
		speakup_date(vc);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम speakup_deallocate(काष्ठा vc_data *vc)
अणु
	पूर्णांक vc_num;

	vc_num = vc->vc_num;
	kमुक्त(speakup_console[vc_num]);
	speakup_console[vc_num] = शून्य;
पूर्ण

क्रमागत पढ़ो_all_command अणु
	RA_NEXT_SENT = KVAL(K_DOWN)+1,
	RA_PREV_LINE = KVAL(K_LEFT)+1,
	RA_NEXT_LINE = KVAL(K_RIGHT)+1,
	RA_PREV_SENT = KVAL(K_UP)+1,
	RA_DOWN_ARROW,
	RA_TIMER,
	RA_FIND_NEXT_SENT,
	RA_FIND_PREV_SENT,
पूर्ण;

अटल u_अक्षर is_cursor;
अटल u_दीर्घ old_cursor_pos, old_cursor_x, old_cursor_y;
अटल पूर्णांक cursor_con;

अटल व्योम reset_highlight_buffers(काष्ठा vc_data *);

अटल क्रमागत पढ़ो_all_command पढ़ो_all_key;

अटल पूर्णांक in_keyboard_notअगरier;

अटल व्योम start_पढ़ो_all_समयr(काष्ठा vc_data *vc, क्रमागत पढ़ो_all_command command);

अटल व्योम kbd_fakekey2(काष्ठा vc_data *vc, क्रमागत पढ़ो_all_command command)
अणु
	del_समयr(&cursor_समयr);
	speakup_fake_करोwn_arrow();
	start_पढ़ो_all_समयr(vc, command);
पूर्ण

अटल व्योम पढ़ो_all_करोc(काष्ठा vc_data *vc)
अणु
	अगर ((vc->vc_num != fg_console) || !synth || spk_shut_up)
		वापस;
	अगर (!synth_supports_indexing())
		वापस;
	अगर (cursor_track != पढ़ो_all_mode)
		prev_cursor_track = cursor_track;
	cursor_track = पढ़ो_all_mode;
	spk_reset_index_count(0);
	अगर (get_sentence_buf(vc, 0) == -1) अणु
		del_समयr(&cursor_समयr);
		अगर (!in_keyboard_notअगरier)
			speakup_fake_करोwn_arrow();
		start_पढ़ो_all_समयr(vc, RA_DOWN_ARROW);
	पूर्ण अन्यथा अणु
		say_sentence_num(0, 0);
		synth_insert_next_index(0);
		start_पढ़ो_all_समयr(vc, RA_TIMER);
	पूर्ण
पूर्ण

अटल व्योम stop_पढ़ो_all(काष्ठा vc_data *vc)
अणु
	del_समयr(&cursor_समयr);
	cursor_track = prev_cursor_track;
	spk_shut_up &= 0xfe;
	spk_करो_flush();
पूर्ण

अटल व्योम start_पढ़ो_all_समयr(काष्ठा vc_data *vc, क्रमागत पढ़ो_all_command command)
अणु
	काष्ठा var_t *cursor_समयout;

	cursor_con = vc->vc_num;
	पढ़ो_all_key = command;
	cursor_समयout = spk_get_var(CURSOR_TIME);
	mod_समयr(&cursor_समयr,
		  jअगरfies + msecs_to_jअगरfies(cursor_समयout->u.n.value));
पूर्ण

अटल व्योम handle_cursor_पढ़ो_all(काष्ठा vc_data *vc, क्रमागत पढ़ो_all_command command)
अणु
	पूर्णांक indcount, sentcount, rv, sn;

	चयन (command) अणु
	हाल RA_NEXT_SENT:
		/* Get Current Sentence */
		spk_get_index_count(&indcount, &sentcount);
		/*prपूर्णांकk("%d %d  ", indcount, sentcount); */
		spk_reset_index_count(sentcount + 1);
		अगर (indcount == 1) अणु
			अगर (!say_sentence_num(sentcount + 1, 0)) अणु
				kbd_fakekey2(vc, RA_FIND_NEXT_SENT);
				वापस;
			पूर्ण
			synth_insert_next_index(0);
		पूर्ण अन्यथा अणु
			sn = 0;
			अगर (!say_sentence_num(sentcount + 1, 1)) अणु
				sn = 1;
				spk_reset_index_count(sn);
			पूर्ण अन्यथा अणु
				synth_insert_next_index(0);
			पूर्ण
			अगर (!say_sentence_num(sn, 0)) अणु
				kbd_fakekey2(vc, RA_FIND_NEXT_SENT);
				वापस;
			पूर्ण
			synth_insert_next_index(0);
		पूर्ण
		start_पढ़ो_all_समयr(vc, RA_TIMER);
		अवरोध;
	हाल RA_PREV_SENT:
		अवरोध;
	हाल RA_NEXT_LINE:
		पढ़ो_all_करोc(vc);
		अवरोध;
	हाल RA_PREV_LINE:
		अवरोध;
	हाल RA_DOWN_ARROW:
		अगर (get_sentence_buf(vc, 0) == -1) अणु
			kbd_fakekey2(vc, RA_DOWN_ARROW);
		पूर्ण अन्यथा अणु
			say_sentence_num(0, 0);
			synth_insert_next_index(0);
			start_पढ़ो_all_समयr(vc, RA_TIMER);
		पूर्ण
		अवरोध;
	हाल RA_FIND_NEXT_SENT:
		rv = get_sentence_buf(vc, 0);
		अगर (rv == -1)
			पढ़ो_all_करोc(vc);
		अगर (rv == 0) अणु
			kbd_fakekey2(vc, RA_FIND_NEXT_SENT);
		पूर्ण अन्यथा अणु
			say_sentence_num(1, 0);
			synth_insert_next_index(0);
			start_पढ़ो_all_समयr(vc, RA_TIMER);
		पूर्ण
		अवरोध;
	हाल RA_FIND_PREV_SENT:
		अवरोध;
	हाल RA_TIMER:
		spk_get_index_count(&indcount, &sentcount);
		अगर (indcount < 2)
			kbd_fakekey2(vc, RA_DOWN_ARROW);
		अन्यथा
			start_पढ़ो_all_समयr(vc, RA_TIMER);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pre_handle_cursor(काष्ठा vc_data *vc, u_अक्षर value, अक्षर up_flag)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	अगर (cursor_track == पढ़ो_all_mode) अणु
		spk_parked &= 0xfe;
		अगर (!synth || up_flag || spk_shut_up) अणु
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			वापस NOTIFY_STOP;
		पूर्ण
		del_समयr(&cursor_समयr);
		spk_shut_up &= 0xfe;
		spk_करो_flush();
		start_पढ़ो_all_समयr(vc, value + 1);
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		वापस NOTIFY_STOP;
	पूर्ण
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस NOTIFY_OK;
पूर्ण

अटल व्योम करो_handle_cursor(काष्ठा vc_data *vc, u_अक्षर value, अक्षर up_flag)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा var_t *cursor_समयout;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	spk_parked &= 0xfe;
	अगर (!synth || up_flag || spk_shut_up || cursor_track == CT_Off) अणु
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		वापस;
	पूर्ण
	spk_shut_up &= 0xfe;
	अगर (spk_no_पूर्णांकr)
		spk_करो_flush();
/* the key press flushes अगर !no_पूर्णांकer but we want to flush on cursor
 * moves regardless of no_पूर्णांकer state
 */
	is_cursor = value + 1;
	old_cursor_pos = vc->vc_pos;
	old_cursor_x = vc->state.x;
	old_cursor_y = vc->state.y;
	speakup_console[vc->vc_num]->ht.cy = vc->state.y;
	cursor_con = vc->vc_num;
	अगर (cursor_track == CT_Highlight)
		reset_highlight_buffers(vc);
	cursor_समयout = spk_get_var(CURSOR_TIME);
	mod_समयr(&cursor_समयr,
		  jअगरfies + msecs_to_jअगरfies(cursor_समयout->u.n.value));
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
पूर्ण

अटल व्योम update_color_buffer(काष्ठा vc_data *vc, स्थिर u16 *ic, पूर्णांक len)
अणु
	पूर्णांक i, bi, hi;
	पूर्णांक vc_num = vc->vc_num;

	bi = (vc->vc_attr & 0x70) >> 4;
	hi = speakup_console[vc_num]->ht.highsize[bi];

	i = 0;
	अगर (speakup_console[vc_num]->ht.highsize[bi] == 0) अणु
		speakup_console[vc_num]->ht.rpos[bi] = vc->vc_pos;
		speakup_console[vc_num]->ht.rx[bi] = vc->state.x;
		speakup_console[vc_num]->ht.ry[bi] = vc->state.y;
	पूर्ण
	जबतक ((hi < COLOR_BUFFER_SIZE) && (i < len)) अणु
		अगर (ic[i] > 32) अणु
			speakup_console[vc_num]->ht.highbuf[bi][hi] = ic[i];
			hi++;
		पूर्ण अन्यथा अगर ((ic[i] == 32) && (hi != 0)) अणु
			अगर (speakup_console[vc_num]->ht.highbuf[bi][hi - 1] !=
			    32) अणु
				speakup_console[vc_num]->ht.highbuf[bi][hi] =
				    ic[i];
				hi++;
			पूर्ण
		पूर्ण
		i++;
	पूर्ण
	speakup_console[vc_num]->ht.highsize[bi] = hi;
पूर्ण

अटल व्योम reset_highlight_buffers(काष्ठा vc_data *vc)
अणु
	पूर्णांक i;
	पूर्णांक vc_num = vc->vc_num;

	क्रम (i = 0; i < 8; i++)
		speakup_console[vc_num]->ht.highsize[i] = 0;
पूर्ण

अटल पूर्णांक count_highlight_color(काष्ठा vc_data *vc)
अणु
	पूर्णांक i, bg;
	पूर्णांक cc;
	पूर्णांक vc_num = vc->vc_num;
	u16 ch;
	u16 *start = (u16 *)vc->vc_origin;

	क्रम (i = 0; i < 8; i++)
		speakup_console[vc_num]->ht.bgcount[i] = 0;

	क्रम (i = 0; i < vc->vc_rows; i++) अणु
		u16 *end = start + vc->vc_cols * 2;
		u16 *ptr;

		क्रम (ptr = start; ptr < end; ptr++) अणु
			ch = get_attributes(vc, ptr);
			bg = (ch & 0x70) >> 4;
			speakup_console[vc_num]->ht.bgcount[bg]++;
		पूर्ण
		start += vc->vc_size_row;
	पूर्ण

	cc = 0;
	क्रम (i = 0; i < 8; i++)
		अगर (speakup_console[vc_num]->ht.bgcount[i] > 0)
			cc++;
	वापस cc;
पूर्ण

अटल पूर्णांक get_highlight_color(काष्ठा vc_data *vc)
अणु
	पूर्णांक i, j;
	अचिन्हित पूर्णांक cptr[8];
	पूर्णांक vc_num = vc->vc_num;

	क्रम (i = 0; i < 8; i++)
		cptr[i] = i;

	क्रम (i = 0; i < 7; i++)
		क्रम (j = i + 1; j < 8; j++)
			अगर (speakup_console[vc_num]->ht.bgcount[cptr[i]] >
			    speakup_console[vc_num]->ht.bgcount[cptr[j]])
				swap(cptr[i], cptr[j]);

	क्रम (i = 0; i < 8; i++)
		अगर (speakup_console[vc_num]->ht.bgcount[cptr[i]] != 0)
			अगर (speakup_console[vc_num]->ht.highsize[cptr[i]] > 0)
				वापस cptr[i];
	वापस -1;
पूर्ण

अटल पूर्णांक speak_highlight(काष्ठा vc_data *vc)
अणु
	पूर्णांक hc, d;
	पूर्णांक vc_num = vc->vc_num;

	अगर (count_highlight_color(vc) == 1)
		वापस 0;
	hc = get_highlight_color(vc);
	अगर (hc != -1) अणु
		d = vc->state.y - speakup_console[vc_num]->ht.cy;
		अगर ((d == 1) || (d == -1))
			अगर (speakup_console[vc_num]->ht.ry[hc] != vc->state.y)
				वापस 0;
		spk_parked |= 0x01;
		spk_करो_flush();
		spkup_ग_लिखो(speakup_console[vc_num]->ht.highbuf[hc],
			    speakup_console[vc_num]->ht.highsize[hc]);
		spk_pos = spk_cp = speakup_console[vc_num]->ht.rpos[hc];
		spk_x = spk_cx = speakup_console[vc_num]->ht.rx[hc];
		spk_y = spk_cy = speakup_console[vc_num]->ht.ry[hc];
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cursor_करोne(काष्ठा समयr_list *unused)
अणु
	काष्ठा vc_data *vc = vc_cons[cursor_con].d;
	अचिन्हित दीर्घ flags;

	del_समयr(&cursor_समयr);
	spin_lock_irqsave(&speakup_info.spinlock, flags);
	अगर (cursor_con != fg_console) अणु
		is_cursor = 0;
		जाओ out;
	पूर्ण
	speakup_date(vc);
	अगर (win_enabled) अणु
		अगर (vc->state.x >= win_left && vc->state.x <= win_right &&
		    vc->state.y >= win_top && vc->state.y <= win_bottom) अणु
			spk_keyकरोwn = 0;
			is_cursor = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (cursor_track == पढ़ो_all_mode) अणु
		handle_cursor_पढ़ो_all(vc, पढ़ो_all_key);
		जाओ out;
	पूर्ण
	अगर (cursor_track == CT_Highlight) अणु
		अगर (speak_highlight(vc)) अणु
			spk_keyकरोwn = 0;
			is_cursor = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (cursor_track == CT_Winकरोw)
		speakup_win_say(vc);
	अन्यथा अगर (is_cursor == 1 || is_cursor == 4)
		say_line_from_to(vc, 0, vc->vc_cols, 0);
	अन्यथा
		say_अक्षर(vc);
	spk_keyकरोwn = 0;
	is_cursor = 0;
out:
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
पूर्ण

/* called by: vt_notअगरier_call() */
अटल व्योम speakup_bs(काष्ठा vc_data *vc)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!speakup_console[vc->vc_num])
		वापस;
	अगर (!spin_trylock_irqsave(&speakup_info.spinlock, flags))
		/* Speakup output, discard */
		वापस;
	अगर (!spk_parked)
		speakup_date(vc);
	अगर (spk_shut_up || !synth) अणु
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		वापस;
	पूर्ण
	अगर (vc->vc_num == fg_console && spk_keyकरोwn) अणु
		spk_keyकरोwn = 0;
		अगर (!is_cursor)
			say_अक्षर(vc);
	पूर्ण
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
पूर्ण

/* called by: vt_notअगरier_call() */
अटल व्योम speakup_con_ग_लिखो(काष्ठा vc_data *vc, u16 *str, पूर्णांक len)
अणु
	अचिन्हित दीर्घ flags;

	अगर ((vc->vc_num != fg_console) || spk_shut_up || !synth)
		वापस;
	अगर (!spin_trylock_irqsave(&speakup_info.spinlock, flags))
		/* Speakup output, discard */
		वापस;
	अगर (spk_bell_pos && spk_keyकरोwn && (vc->state.x == spk_bell_pos - 1))
		bleep(3);
	अगर ((is_cursor) || (cursor_track == पढ़ो_all_mode)) अणु
		अगर (cursor_track == CT_Highlight)
			update_color_buffer(vc, str, len);
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		वापस;
	पूर्ण
	अगर (win_enabled) अणु
		अगर (vc->state.x >= win_left && vc->state.x <= win_right &&
		    vc->state.y >= win_top && vc->state.y <= win_bottom) अणु
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			वापस;
		पूर्ण
	पूर्ण

	spkup_ग_लिखो(str, len);
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
पूर्ण

अटल व्योम speakup_con_update(काष्ठा vc_data *vc)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!speakup_console[vc->vc_num] || spk_parked)
		वापस;
	अगर (!spin_trylock_irqsave(&speakup_info.spinlock, flags))
		/* Speakup output, discard */
		वापस;
	speakup_date(vc);
	अगर (vc->vc_mode == KD_GRAPHICS && !spk_छोड़ोd && spk_str_छोड़ो[0]) अणु
		synth_म_लिखो("%s", spk_str_छोड़ो);
		spk_छोड़ोd = true;
	पूर्ण
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
पूर्ण

अटल व्योम करो_handle_spec(काष्ठा vc_data *vc, u_अक्षर value, अक्षर up_flag)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक on_off = 2;
	अक्षर *label;

	अगर (!synth || up_flag || spk_समाप्तed)
		वापस;
	spin_lock_irqsave(&speakup_info.spinlock, flags);
	spk_shut_up &= 0xfe;
	अगर (spk_no_पूर्णांकr)
		spk_करो_flush();
	चयन (value) अणु
	हाल KVAL(K_CAPS):
		label = spk_msg_get(MSG_KEYNAME_CAPSLOCK);
		on_off = vt_get_leds(fg_console, VC_CAPSLOCK);
		अवरोध;
	हाल KVAL(K_NUM):
		label = spk_msg_get(MSG_KEYNAME_NUMLOCK);
		on_off = vt_get_leds(fg_console, VC_NUMLOCK);
		अवरोध;
	हाल KVAL(K_HOLD):
		label = spk_msg_get(MSG_KEYNAME_SCROLLLOCK);
		on_off = vt_get_leds(fg_console, VC_SCROLLOCK);
		अगर (speakup_console[vc->vc_num])
			speakup_console[vc->vc_num]->tty_stopped = on_off;
		अवरोध;
	शेष:
		spk_parked &= 0xfe;
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		वापस;
	पूर्ण
	अगर (on_off < 2)
		synth_म_लिखो("%s %s\n",
			     label, spk_msg_get(MSG_STATUS_START + on_off));
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
पूर्ण

अटल पूर्णांक inc_dec_var(u_अक्षर value)
अणु
	काष्ठा st_var_header *p_header;
	काष्ठा var_t *var_data;
	अक्षर num_buf[32];
	अक्षर *cp = num_buf;
	अक्षर *pn;
	पूर्णांक var_id = (पूर्णांक)value - VAR_START;
	पूर्णांक how = (var_id & 1) ? E_INC : E_DEC;

	var_id = var_id / 2 + FIRST_SET_VAR;
	p_header = spk_get_var_header(var_id);
	अगर (!p_header)
		वापस -1;
	अगर (p_header->var_type != VAR_NUM)
		वापस -1;
	var_data = p_header->data;
	अगर (spk_set_num_var(1, p_header, how) != 0)
		वापस -1;
	अगर (!spk_बंद_press) अणु
		क्रम (pn = p_header->name; *pn; pn++) अणु
			अगर (*pn == '_')
				*cp = SPACE;
			अन्यथा
				*cp++ = *pn;
		पूर्ण
	पूर्ण
	snम_लिखो(cp, माप(num_buf) - (cp - num_buf), " %d ",
		 var_data->u.n.value);
	synth_म_लिखो("%s", num_buf);
	वापस 0;
पूर्ण

अटल व्योम speakup_win_set(काष्ठा vc_data *vc)
अणु
	अक्षर info[40];

	अगर (win_start > 1) अणु
		synth_म_लिखो("%s\n", spk_msg_get(MSG_WINDOW_ALREADY_SET));
		वापस;
	पूर्ण
	अगर (spk_x < win_left || spk_y < win_top) अणु
		synth_म_लिखो("%s\n", spk_msg_get(MSG_END_BEFORE_START));
		वापस;
	पूर्ण
	अगर (win_start && spk_x == win_left && spk_y == win_top) अणु
		win_left = 0;
		win_right = vc->vc_cols - 1;
		win_bottom = spk_y;
		snम_लिखो(info, माप(info), spk_msg_get(MSG_WINDOW_LINE),
			 (पूर्णांक)win_top + 1);
	पूर्ण अन्यथा अणु
		अगर (!win_start) अणु
			win_top = spk_y;
			win_left = spk_x;
		पूर्ण अन्यथा अणु
			win_bottom = spk_y;
			win_right = spk_x;
		पूर्ण
		snम_लिखो(info, माप(info), spk_msg_get(MSG_WINDOW_BOUNDARY),
			 (win_start) ?
				spk_msg_get(MSG_END) : spk_msg_get(MSG_START),
			 (पूर्णांक)spk_y + 1, (पूर्णांक)spk_x + 1);
	पूर्ण
	synth_म_लिखो("%s\n", info);
	win_start++;
पूर्ण

अटल व्योम speakup_win_clear(काष्ठा vc_data *vc)
अणु
	win_top = 0;
	win_bottom = 0;
	win_left = 0;
	win_right = 0;
	win_start = 0;
	synth_म_लिखो("%s\n", spk_msg_get(MSG_WINDOW_CLEARED));
पूर्ण

अटल व्योम speakup_win_enable(काष्ठा vc_data *vc)
अणु
	अगर (win_start < 2) अणु
		synth_म_लिखो("%s\n", spk_msg_get(MSG_NO_WINDOW));
		वापस;
	पूर्ण
	win_enabled ^= 1;
	अगर (win_enabled)
		synth_म_लिखो("%s\n", spk_msg_get(MSG_WINDOW_SILENCED));
	अन्यथा
		synth_म_लिखो("%s\n", spk_msg_get(MSG_WINDOW_SILENCE_DISABLED));
पूर्ण

अटल व्योम speakup_bits(काष्ठा vc_data *vc)
अणु
	पूर्णांक val = this_speakup_key - (FIRST_EDIT_BITS - 1);

	अगर (spk_special_handler || val < 1 || val > 6) अणु
		synth_म_लिखो("%s\n", spk_msg_get(MSG_ERROR));
		वापस;
	पूर्ण
	pb_edit = &spk_punc_info[val];
	synth_म_लिखो(spk_msg_get(MSG_EDIT_PROMPT), pb_edit->name);
	spk_special_handler = edit_bits;
पूर्ण

अटल पूर्णांक handle_जाओ(काष्ठा vc_data *vc, u_अक्षर type, u_अक्षर ch, u_लघु key)
अणु
	अटल u_अक्षर जाओ_buf[8];
	अटल पूर्णांक num;
	पूर्णांक maxlen;
	अक्षर *cp;
	u16 wch;

	अगर (type == KT_SPKUP && ch == SPEAKUP_GOTO)
		जाओ करो_जाओ;
	अगर (type == KT_LATIN && ch == '\n')
		जाओ करो_जाओ;
	अगर (type != 0)
		जाओ oops;
	अगर (ch == 8) अणु
		u16 wch;

		अगर (num == 0)
			वापस -1;
		wch = जाओ_buf[--num];
		जाओ_buf[num] = '\0';
		spkup_ग_लिखो(&wch, 1);
		वापस 1;
	पूर्ण
	अगर (ch < '+' || ch > 'y')
		जाओ oops;
	wch = ch;
	जाओ_buf[num++] = ch;
	जाओ_buf[num] = '\0';
	spkup_ग_लिखो(&wch, 1);
	maxlen = (*जाओ_buf >= '0') ? 3 : 4;
	अगर ((ch == '+' || ch == '-') && num == 1)
		वापस 1;
	अगर (ch >= '0' && ch <= '9' && num < maxlen)
		वापस 1;
	अगर (num < maxlen - 1 || num > maxlen)
		जाओ oops;
	अगर (ch < 'x' || ch > 'y') अणु
oops:
		अगर (!spk_समाप्तed)
			synth_म_लिखो(" %s\n", spk_msg_get(MSG_GOTO_CANCELED));
		जाओ_buf[num = 0] = '\0';
		spk_special_handler = शून्य;
		वापस 1;
	पूर्ण

	/* Do not replace with kम_से_अदीर्घ: here we need cp to be updated */
	जाओ_pos = simple_म_से_अदीर्घ(जाओ_buf, &cp, 10);

	अगर (*cp == 'x') अणु
		अगर (*जाओ_buf < '0')
			जाओ_pos += spk_x;
		अन्यथा अगर (जाओ_pos > 0)
			जाओ_pos--;

		अगर (जाओ_pos >= vc->vc_cols)
			जाओ_pos = vc->vc_cols - 1;
		जाओ_x = 1;
	पूर्ण अन्यथा अणु
		अगर (*जाओ_buf < '0')
			जाओ_pos += spk_y;
		अन्यथा अगर (जाओ_pos > 0)
			जाओ_pos--;

		अगर (जाओ_pos >= vc->vc_rows)
			जाओ_pos = vc->vc_rows - 1;
		जाओ_x = 0;
	पूर्ण
	जाओ_buf[num = 0] = '\0';
करो_जाओ:
	spk_special_handler = शून्य;
	spk_parked |= 0x01;
	अगर (जाओ_x) अणु
		spk_pos -= spk_x * 2;
		spk_x = जाओ_pos;
		spk_pos += जाओ_pos * 2;
		say_word(vc);
	पूर्ण अन्यथा अणु
		spk_y = जाओ_pos;
		spk_pos = vc->vc_origin + (जाओ_pos * vc->vc_size_row);
		say_line(vc);
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम speakup_जाओ(काष्ठा vc_data *vc)
अणु
	अगर (spk_special_handler) अणु
		synth_म_लिखो("%s\n", spk_msg_get(MSG_ERROR));
		वापस;
	पूर्ण
	synth_म_लिखो("%s\n", spk_msg_get(MSG_GOTO));
	spk_special_handler = handle_जाओ;
पूर्ण

अटल व्योम speakup_help(काष्ठा vc_data *vc)
अणु
	spk_handle_help(vc, KT_SPKUP, SPEAKUP_HELP, 0);
पूर्ण

अटल व्योम करो_nothing(काष्ठा vc_data *vc)
अणु
	वापस;			/* flush करोne in करो_spkup */
पूर्ण

अटल u_अक्षर key_speakup, spk_key_locked;

अटल व्योम speakup_lock(काष्ठा vc_data *vc)
अणु
	अगर (!spk_key_locked) अणु
		spk_key_locked = 16;
		key_speakup = 16;
	पूर्ण अन्यथा अणु
		spk_key_locked = 0;
		key_speakup = 0;
	पूर्ण
पूर्ण

प्रकार व्योम (*spkup_hand) (काष्ठा vc_data *);
अटल spkup_hand spkup_handler[] = अणु
	/* must be ordered same as defines in speakup.h */
	करो_nothing, speakup_जाओ, speech_समाप्त, speakup_shut_up,
	speakup_cut, speakup_paste, say_first_अक्षर, say_last_अक्षर,
	say_अक्षर, say_prev_अक्षर, say_next_अक्षर,
	say_word, say_prev_word, say_next_word,
	say_line, say_prev_line, say_next_line,
	top_edge, bottom_edge, left_edge, right_edge,
	spell_word, spell_word, say_screen,
	say_position, say_attributes,
	speakup_off, speakup_parked, say_line,	/* this is क्रम indent */
	say_from_top, say_to_bottom,
	say_from_left, say_to_right,
	say_अक्षर_num, speakup_bits, speakup_bits, say_phonetic_अक्षर,
	speakup_bits, speakup_bits, speakup_bits,
	speakup_win_set, speakup_win_clear, speakup_win_enable, speakup_win_say,
	speakup_lock, speakup_help, toggle_cursoring, पढ़ो_all_करोc, शून्य
पूर्ण;

अटल व्योम करो_spkup(काष्ठा vc_data *vc, u_अक्षर value)
अणु
	अगर (spk_समाप्तed && value != SPEECH_KILL)
		वापस;
	spk_keyकरोwn = 0;
	spk_lastkey = 0;
	spk_shut_up &= 0xfe;
	this_speakup_key = value;
	अगर (value < SPKUP_MAX_FUNC && spkup_handler[value]) अणु
		spk_करो_flush();
		(*spkup_handler[value]) (vc);
	पूर्ण अन्यथा अणु
		अगर (inc_dec_var(value) < 0)
			bleep(9);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *pad_अक्षरs = "0123456789+-*/\015,.?()";

अटल पूर्णांक
speakup_key(काष्ठा vc_data *vc, पूर्णांक shअगरt_state, पूर्णांक keycode, u_लघु keysym,
	    पूर्णांक up_flag)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक kh;
	u_अक्षर *key_info;
	u_अक्षर type = KTYP(keysym), value = KVAL(keysym), new_key = 0;
	u_अक्षर shअगरt_info, offset;
	पूर्णांक ret = 0;

	अगर (!synth)
		वापस 0;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	tty = vc->port.tty;
	अगर (type >= 0xf0)
		type -= 0xf0;
	अगर (type == KT_PAD &&
	    (vt_get_leds(fg_console, VC_NUMLOCK))) अणु
		अगर (up_flag) अणु
			spk_keyकरोwn = 0;
			जाओ out;
		पूर्ण
		value = pad_अक्षरs[value];
		spk_lastkey = value;
		spk_keyकरोwn++;
		spk_parked &= 0xfe;
		जाओ no_map;
	पूर्ण
	अगर (keycode >= MAX_KEY)
		जाओ no_map;
	key_info = spk_our_keys[keycode];
	अगर (!key_info)
		जाओ no_map;
	/* Check valid पढ़ो all mode keys */
	अगर ((cursor_track == पढ़ो_all_mode) && (!up_flag)) अणु
		चयन (value) अणु
		हाल KVAL(K_DOWN):
		हाल KVAL(K_UP):
		हाल KVAL(K_LEFT):
		हाल KVAL(K_RIGHT):
		हाल KVAL(K_PGUP):
		हाल KVAL(K_PGDN):
			अवरोध;
		शेष:
			stop_पढ़ो_all(vc);
			अवरोध;
		पूर्ण
	पूर्ण
	shअगरt_info = (shअगरt_state & 0x0f) + key_speakup;
	offset = spk_shअगरt_table[shअगरt_info];
	अगर (offset) अणु
		new_key = key_info[offset];
		अगर (new_key) अणु
			ret = 1;
			अगर (new_key == SPK_KEY) अणु
				अगर (!spk_key_locked)
					key_speakup = (up_flag) ? 0 : 16;
				अगर (up_flag || spk_समाप्तed)
					जाओ out;
				spk_shut_up &= 0xfe;
				spk_करो_flush();
				जाओ out;
			पूर्ण
			अगर (up_flag)
				जाओ out;
			अगर (last_keycode == keycode &&
			    समय_after(last_spk_jअगरfy + MAX_DELAY, jअगरfies)) अणु
				spk_बंद_press = 1;
				offset = spk_shअगरt_table[shअगरt_info + 32];
				/* द्विगुन press? */
				अगर (offset && key_info[offset])
					new_key = key_info[offset];
			पूर्ण
			last_keycode = keycode;
			last_spk_jअगरfy = jअगरfies;
			type = KT_SPKUP;
			value = new_key;
		पूर्ण
	पूर्ण
no_map:
	अगर (type == KT_SPKUP && !spk_special_handler) अणु
		करो_spkup(vc, new_key);
		spk_बंद_press = 0;
		ret = 1;
		जाओ out;
	पूर्ण
	अगर (up_flag || spk_समाप्तed || type == KT_SHIFT)
		जाओ out;
	spk_shut_up &= 0xfe;
	kh = (value == KVAL(K_DOWN)) ||
	    (value == KVAL(K_UP)) ||
	    (value == KVAL(K_LEFT)) ||
	    (value == KVAL(K_RIGHT));
	अगर ((cursor_track != पढ़ो_all_mode) || !kh)
		अगर (!spk_no_पूर्णांकr)
			spk_करो_flush();
	अगर (spk_special_handler) अणु
		अगर (type == KT_SPEC && value == 1) अणु
			value = '\n';
			type = KT_LATIN;
		पूर्ण अन्यथा अगर (type == KT_LETTER) अणु
			type = KT_LATIN;
		पूर्ण अन्यथा अगर (value == 0x7f) अणु
			value = 8;	/* make del = backspace */
		पूर्ण
		ret = (*spk_special_handler) (vc, type, value, keycode);
		spk_बंद_press = 0;
		अगर (ret < 0)
			bleep(9);
		जाओ out;
	पूर्ण
	last_keycode = 0;
out:
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक keyboard_notअगरier_call(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ code, व्योम *_param)
अणु
	काष्ठा keyboard_notअगरier_param *param = _param;
	काष्ठा vc_data *vc = param->vc;
	पूर्णांक up = !param->करोwn;
	पूर्णांक ret = NOTIFY_OK;
	अटल पूर्णांक keycode;	/* to hold the current keycode */

	in_keyboard_notअगरier = 1;

	अगर (vc->vc_mode == KD_GRAPHICS)
		जाओ out;

	/*
	 * First, determine whether we are handling a fake keypress on
	 * the current processor.  If we are, then वापस NOTIFY_OK,
	 * to pass the keystroke up the chain.  This prevents us from
	 * trying to take the Speakup lock जबतक it is held by the
	 * processor on which the simulated keystroke was generated.
	 * Also, the simulated keystrokes should be ignored by Speakup.
	 */

	अगर (speakup_fake_key_pressed())
		जाओ out;

	चयन (code) अणु
	हाल KBD_KEYCODE:
		/* speakup requires keycode and keysym currently */
		keycode = param->value;
		अवरोध;
	हाल KBD_UNBOUND_KEYCODE:
		/* not used yet */
		अवरोध;
	हाल KBD_UNICODE:
		/* not used yet */
		अवरोध;
	हाल KBD_KEYSYM:
		अगर (speakup_key(vc, param->shअगरt, keycode, param->value, up))
			ret = NOTIFY_STOP;
		अन्यथा अगर (KTYP(param->value) == KT_CUR)
			ret = pre_handle_cursor(vc, KVAL(param->value), up);
		अवरोध;
	हाल KBD_POST_KEYSYM:अणु
			अचिन्हित अक्षर type = KTYP(param->value) - 0xf0;
			अचिन्हित अक्षर val = KVAL(param->value);

			चयन (type) अणु
			हाल KT_SHIFT:
				करो_handle_shअगरt(vc, val, up);
				अवरोध;
			हाल KT_LATIN:
			हाल KT_LETTER:
				करो_handle_latin(vc, val, up);
				अवरोध;
			हाल KT_CUR:
				करो_handle_cursor(vc, val, up);
				अवरोध;
			हाल KT_SPEC:
				करो_handle_spec(vc, val, up);
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
out:
	in_keyboard_notअगरier = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक vt_notअगरier_call(काष्ठा notअगरier_block *nb,
			    अचिन्हित दीर्घ code, व्योम *_param)
अणु
	काष्ठा vt_notअगरier_param *param = _param;
	काष्ठा vc_data *vc = param->vc;

	चयन (code) अणु
	हाल VT_ALLOCATE:
		अगर (vc->vc_mode == KD_TEXT)
			speakup_allocate(vc, GFP_ATOMIC);
		अवरोध;
	हाल VT_DEALLOCATE:
		speakup_deallocate(vc);
		अवरोध;
	हाल VT_WRITE:
		अगर (param->c == '\b') अणु
			speakup_bs(vc);
		पूर्ण अन्यथा अणु
			u16 d = param->c;

			speakup_con_ग_लिखो(vc, &d, 1);
		पूर्ण
		अवरोध;
	हाल VT_UPDATE:
		speakup_con_update(vc);
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

/* called by: module_निकास() */
अटल व्योम __निकास speakup_निकास(व्योम)
अणु
	पूर्णांक i;

	unरेजिस्टर_keyboard_notअगरier(&keyboard_notअगरier_block);
	unरेजिस्टर_vt_notअगरier(&vt_notअगरier_block);
	speakup_unरेजिस्टर_devsynth();
	speakup_cancel_selection();
	speakup_cancel_paste();
	del_समयr_sync(&cursor_समयr);
	kthपढ़ो_stop(speakup_task);
	speakup_task = शून्य;
	mutex_lock(&spk_mutex);
	synth_release();
	mutex_unlock(&spk_mutex);
	spk_ttyio_unरेजिस्टर_ldisc();

	speakup_kobj_निकास();

	क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
		kमुक्त(speakup_console[i]);

	speakup_हटाओ_भव_keyboard();

	क्रम (i = 0; i < MAXVARS; i++)
		speakup_unरेजिस्टर_var(i);

	क्रम (i = 0; i < 256; i++) अणु
		अगर (spk_अक्षरacters[i] != spk_शेष_अक्षरs[i])
			kमुक्त(spk_अक्षरacters[i]);
	पूर्ण

	spk_मुक्त_user_msgs();
पूर्ण

/* call by: module_init() */
अटल पूर्णांक __init speakup_init(व्योम)
अणु
	पूर्णांक i;
	दीर्घ err = 0;
	काष्ठा vc_data *vc = vc_cons[fg_console].d;
	काष्ठा var_t *var;

	/* These first few initializations cannot fail. */
	spk_initialize_msgs();	/* Initialize arrays क्रम i18n. */
	spk_reset_शेष_अक्षरs();
	spk_reset_शेष_अक्षरtab();
	spk_strlwr(synth_name);
	spk_vars[0].u.n.high = vc->vc_cols;
	क्रम (var = spk_vars; var->var_id != MAXVARS; var++)
		speakup_रेजिस्टर_var(var);
	क्रम (var = synth_समय_vars;
	     (var->var_id >= 0) && (var->var_id < MAXVARS); var++)
		speakup_रेजिस्टर_var(var);
	क्रम (i = 1; spk_punc_info[i].mask != 0; i++)
		spk_set_mask_bits(शून्य, i, 2);

	spk_set_key_info(spk_key_शेषs, spk_key_buf);

	/* From here on out, initializations can fail. */
	err = speakup_add_भव_keyboard();
	अगर (err)
		जाओ error_virtkeyboard;

	क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
		अगर (vc_cons[i].d) अणु
			err = speakup_allocate(vc_cons[i].d, GFP_KERNEL);
			अगर (err)
				जाओ error_kobjects;
		पूर्ण

	अगर (spk_quiet_boot)
		spk_shut_up |= 0x01;

	err = speakup_kobj_init();
	अगर (err)
		जाओ error_kobjects;

	spk_ttyio_रेजिस्टर_ldisc();
	synth_init(synth_name);
	speakup_रेजिस्टर_devsynth();
	/*
	 * रेजिस्टर_devsynth might fail, but this error is not fatal.
	 * /dev/synth is an extra feature; the rest of Speakup
	 * will work fine without it.
	 */

	err = रेजिस्टर_keyboard_notअगरier(&keyboard_notअगरier_block);
	अगर (err)
		जाओ error_kbdnotअगरier;
	err = रेजिस्टर_vt_notअगरier(&vt_notअगरier_block);
	अगर (err)
		जाओ error_vtnotअगरier;

	speakup_task = kthपढ़ो_create(speakup_thपढ़ो, शून्य, "speakup");

	अगर (IS_ERR(speakup_task)) अणु
		err = PTR_ERR(speakup_task);
		जाओ error_task;
	पूर्ण

	set_user_nice(speakup_task, 10);
	wake_up_process(speakup_task);

	pr_info("speakup %s: initialized\n", SPEAKUP_VERSION);
	pr_info("synth name on entry is: %s\n", synth_name);
	जाओ out;

error_task:
	unरेजिस्टर_vt_notअगरier(&vt_notअगरier_block);

error_vtnotअगरier:
	unरेजिस्टर_keyboard_notअगरier(&keyboard_notअगरier_block);
	del_समयr(&cursor_समयr);

error_kbdnotअगरier:
	speakup_unरेजिस्टर_devsynth();
	mutex_lock(&spk_mutex);
	synth_release();
	mutex_unlock(&spk_mutex);
	speakup_kobj_निकास();

error_kobjects:
	क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
		kमुक्त(speakup_console[i]);

	speakup_हटाओ_भव_keyboard();

error_virtkeyboard:
	क्रम (i = 0; i < MAXVARS; i++)
		speakup_unरेजिस्टर_var(i);

	क्रम (i = 0; i < 256; i++) अणु
		अगर (spk_अक्षरacters[i] != spk_शेष_अक्षरs[i])
			kमुक्त(spk_अक्षरacters[i]);
	पूर्ण

	spk_मुक्त_user_msgs();

out:
	वापस err;
पूर्ण

module_init(speakup_init);
module_निकास(speakup_निकास);
