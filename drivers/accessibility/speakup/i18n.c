<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Internationalization implementation.  Includes definitions of English
 * string arrays, and the i18n poपूर्णांकer.
 */

#समावेश <linux/slab.h>		/* For kदो_स्मृति. */
#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश "speakup.h"
#समावेश "spk_priv.h"

अटल अक्षर *speakup_msgs[MSG_LAST_INDEX];
अटल अक्षर *speakup_शेष_msgs[MSG_LAST_INDEX] = अणु
	[MSG_BLANK] = "blank",
	[MSG_IAM_ALIVE] = "I'm aLive!",
	[MSG_YOU_KILLED_SPEAKUP] = "You killed speakup!",
	[MSG_HEY_THATS_BETTER] = "hey. That's better!",
	[MSG_YOU_TURNED_ME_OFF] = "You turned me off!",
	[MSG_PARKED] = "parked!",
	[MSG_UNPARKED] = "unparked!",
	[MSG_MARK] = "mark",
	[MSG_CUT] = "cut",
	[MSG_MARK_CLEARED] = "mark, cleared",
	[MSG_PASTE] = "paste",
	[MSG_BRIGHT] = "bright",
	[MSG_ON_BLINKING] = "on blinking",
	[MSG_OFF] = "off",
	[MSG_ON] = "on",
	[MSG_NO_WINDOW] = "no window",
	[MSG_CURSORING_OFF] = "cursoring off",
	[MSG_CURSORING_ON] = "cursoring on",
	[MSG_HIGHLIGHT_TRACKING] = "highlight tracking",
	[MSG_READ_WINDOW] = "read windo",
	[MSG_READ_ALL] = "read all",
	[MSG_EDIT_DONE] = "edit done",
	[MSG_WINDOW_ALREADY_SET] = "window already set, clear then reset",
	[MSG_END_BEFORE_START] = "error end before start",
	[MSG_WINDOW_CLEARED] = "window cleared",
	[MSG_WINDOW_SILENCED] = "window silenced",
	[MSG_WINDOW_SILENCE_DISABLED] = "window silence disabled",
	[MSG_ERROR] = "error",
	[MSG_GOTO_CANCELED] = "goto canceled",
	[MSG_GOTO] = "go to?",
	[MSG_LEAVING_HELP] = "leaving help",
	[MSG_IS_UNASSIGNED] = "is unassigned",
	[MSG_HELP_INFO] =
	"press space to exit, up or down to scroll, or a letter to go to a command",
	[MSG_EDGE_TOP] = "top,",
	[MSG_EDGE_BOTTOM] = "bottom,",
	[MSG_EDGE_LEFT] = "left,",
	[MSG_EDGE_RIGHT] = "right,",
	[MSG_NUMBER] = "number",
	[MSG_SPACE] = "space",
	[MSG_START] = "start",
	[MSG_END] = "end",
	[MSG_CTRL] = "control-",
	[MSG_DISJUNCTION] = "or",

/* Messages with embedded क्रमmat specअगरiers. */
	[MSG_POS_INFO] = "line %ld, col %ld, t t y %d",
	[MSG_CHAR_INFO] = "hex %02x, decimal %d",
	[MSG_REPEAT_DESC] = "times %d .",
	[MSG_REPEAT_DESC2] = "repeated %d .",
	[MSG_WINDOW_LINE] = "window is line %d",
	[MSG_WINDOW_BOUNDARY] = "%s at line %d, column %d",
	[MSG_EDIT_PROMPT] = "edit  %s, press space when done",
	[MSG_NO_COMMAND] = "no commands for %c",
	[MSG_KEYDESC] = "is %s",

	/* Control keys. */
	/* Most of these duplicate the entries in state names. */
	[MSG_CTL_SHIFT] = "shift",
	[MSG_CTL_ALTGR] = "altgr",
	[MSG_CTL_CONTROL] = "control",
	[MSG_CTL_ALT] = "alt",
	[MSG_CTL_LSHIFT] = "l shift",
	[MSG_CTL_SPEAKUP] = "speakup",
	[MSG_CTL_LCONTROL] = "l control",
	[MSG_CTL_RCONTROL] = "r control",
	[MSG_CTL_CAPSSHIFT] = "caps shift",

	/* Color names. */
	[MSG_COLOR_BLACK] = "black",
	[MSG_COLOR_BLUE] = "blue",
	[MSG_COLOR_GREEN] = "green",
	[MSG_COLOR_CYAN] = "cyan",
	[MSG_COLOR_RED] = "red",
	[MSG_COLOR_MAGENTA] = "magenta",
	[MSG_COLOR_YELLOW] = "yellow",
	[MSG_COLOR_WHITE] = "white",
	[MSG_COLOR_GREY] = "grey",

	/* Names of key states. */
	[MSG_STATE_DOUBLE] = "double",
	[MSG_STATE_SPEAKUP] = "speakup",
	[MSG_STATE_ALT] = "alt",
	[MSG_STATE_CONTROL] = "ctrl",
	[MSG_STATE_ALTGR] = "altgr",
	[MSG_STATE_SHIFT] = "shift",

	/* Key names. */
	[MSG_KEYNAME_ESC] = "escape",
	[MSG_KEYNAME_1] = "1",
	[MSG_KEYNAME_2] = "2",
	[MSG_KEYNAME_3] = "3",
	[MSG_KEYNAME_4] = "4",
	[MSG_KEYNAME_5] = "5",
	[MSG_KEYNAME_6] = "6",
	[MSG_KEYNAME_7] = "7",
	[MSG_KEYNAME_8] = "8",
	[MSG_KEYNAME_9] = "9",
	[MSG_KEYNAME_0] = "0",
	[MSG_KEYNAME_DASH] = "minus",
	[MSG_KEYNAME_EQUAL] = "equal",
	[MSG_KEYNAME_BS] = "back space",
	[MSG_KEYNAME_TAB] = "tab",
	[MSG_KEYNAME_Q] = "q",
	[MSG_KEYNAME_W] = "w",
	[MSG_KEYNAME_E] = "e",
	[MSG_KEYNAME_R] = "r",
	[MSG_KEYNAME_T] = "t",
	[MSG_KEYNAME_Y] = "y",
	[MSG_KEYNAME_U] = "u",
	[MSG_KEYNAME_I] = "i",
	[MSG_KEYNAME_O] = "o",
	[MSG_KEYNAME_P] = "p",
	[MSG_KEYNAME_LEFTBRACE] = "left brace",
	[MSG_KEYNAME_RIGHTBRACE] = "right brace",
	[MSG_KEYNAME_ENTER] = "enter",
	[MSG_KEYNAME_LEFTCTRL] = "left control",
	[MSG_KEYNAME_A] = "a",
	[MSG_KEYNAME_S] = "s",
	[MSG_KEYNAME_D] = "d",
	[MSG_KEYNAME_F] = "f",
	[MSG_KEYNAME_G] = "g",
	[MSG_KEYNAME_H] = "h",
	[MSG_KEYNAME_J] = "j",
	[MSG_KEYNAME_K] = "k",
	[MSG_KEYNAME_L] = "l",
	[MSG_KEYNAME_SEMICOLON] = "semicolon",
	[MSG_KEYNAME_SINGLEQUOTE] = "apostrophe",
	[MSG_KEYNAME_GRAVE] = "accent",
	[MSG_KEYNAME_LEFTSHFT] = "left shift",
	[MSG_KEYNAME_BACKSLASH] = "back slash",
	[MSG_KEYNAME_Z] = "z",
	[MSG_KEYNAME_X] = "x",
	[MSG_KEYNAME_C] = "c",
	[MSG_KEYNAME_V] = "v",
	[MSG_KEYNAME_B] = "b",
	[MSG_KEYNAME_N] = "n",
	[MSG_KEYNAME_M] = "m",
	[MSG_KEYNAME_COMMA] = "comma",
	[MSG_KEYNAME_DOT] = "dot",
	[MSG_KEYNAME_SLASH] = "slash",
	[MSG_KEYNAME_RIGHTSHFT] = "right shift",
	[MSG_KEYNAME_KPSTAR] = "keypad asterisk",
	[MSG_KEYNAME_LEFTALT] = "left alt",
	[MSG_KEYNAME_SPACE] = "space",
	[MSG_KEYNAME_CAPSLOCK] = "caps lock",
	[MSG_KEYNAME_F1] = "f1",
	[MSG_KEYNAME_F2] = "f2",
	[MSG_KEYNAME_F3] = "f3",
	[MSG_KEYNAME_F4] = "f4",
	[MSG_KEYNAME_F5] = "f5",
	[MSG_KEYNAME_F6] = "f6",
	[MSG_KEYNAME_F7] = "f7",
	[MSG_KEYNAME_F8] = "f8",
	[MSG_KEYNAME_F9] = "f9",
	[MSG_KEYNAME_F10] = "f10",
	[MSG_KEYNAME_NUMLOCK] = "num lock",
	[MSG_KEYNAME_SCROLLLOCK] = "scroll lock",
	[MSG_KEYNAME_KP7] = "keypad 7",
	[MSG_KEYNAME_KP8] = "keypad 8",
	[MSG_KEYNAME_KP9] = "keypad 9",
	[MSG_KEYNAME_KPMINUS] = "keypad minus",
	[MSG_KEYNAME_KP4] = "keypad 4",
	[MSG_KEYNAME_KP5] = "keypad 5",
	[MSG_KEYNAME_KP6] = "keypad 6",
	[MSG_KEYNAME_KPPLUS] = "keypad plus",
	[MSG_KEYNAME_KP1] = "keypad 1",
	[MSG_KEYNAME_KP2] = "keypad 2",
	[MSG_KEYNAME_KP3] = "keypad 3",
	[MSG_KEYNAME_KP0] = "keypad 0",
	[MSG_KEYNAME_KPDOT] = "keypad dot",
	[MSG_KEYNAME_103RD] = "103rd",
	[MSG_KEYNAME_F13] = "f13",
	[MSG_KEYNAME_102ND] = "102nd",
	[MSG_KEYNAME_F11] = "f11",
	[MSG_KEYNAME_F12] = "f12",
	[MSG_KEYNAME_F14] = "f14",
	[MSG_KEYNAME_F15] = "f15",
	[MSG_KEYNAME_F16] = "f16",
	[MSG_KEYNAME_F17] = "f17",
	[MSG_KEYNAME_F18] = "f18",
	[MSG_KEYNAME_F19] = "f19",
	[MSG_KEYNAME_F20] = "f20",
	[MSG_KEYNAME_KPENTER] = "keypad enter",
	[MSG_KEYNAME_RIGHTCTRL] = "right control",
	[MSG_KEYNAME_KPSLASH] = "keypad slash",
	[MSG_KEYNAME_SYSRQ] = "sysrq",
	[MSG_KEYNAME_RIGHTALT] = "right alt",
	[MSG_KEYNAME_LF] = "line feed",
	[MSG_KEYNAME_HOME] = "home",
	[MSG_KEYNAME_UP] = "up",
	[MSG_KEYNAME_PGUP] = "page up",
	[MSG_KEYNAME_LEFT] = "left",
	[MSG_KEYNAME_RIGHT] = "right",
	[MSG_KEYNAME_END] = "end",
	[MSG_KEYNAME_DOWN] = "down",
	[MSG_KEYNAME_PGDN] = "page down",
	[MSG_KEYNAME_INS] = "insert",
	[MSG_KEYNAME_DEL] = "delete",
	[MSG_KEYNAME_MACRO] = "macro",
	[MSG_KEYNAME_MUTE] = "mute",
	[MSG_KEYNAME_VOLDOWN] = "volume down",
	[MSG_KEYNAME_VOLUP] = "volume up",
	[MSG_KEYNAME_POWER] = "power",
	[MSG_KEYNAME_KPEQUAL] = "keypad equal",
	[MSG_KEYNAME_KPPLUSDASH] = "keypad plusminus",
	[MSG_KEYNAME_PAUSE] = "pause",
	[MSG_KEYNAME_F21] = "f21",
	[MSG_KEYNAME_F22] = "f22",
	[MSG_KEYNAME_F23] = "f23",
	[MSG_KEYNAME_F24] = "f24",
	[MSG_KEYNAME_KPCOMMA] = "keypad comma",
	[MSG_KEYNAME_LEFTMETA] = "left meta",
	[MSG_KEYNAME_RIGHTMETA] = "right meta",
	[MSG_KEYNAME_COMPOSE] = "compose",
	[MSG_KEYNAME_STOP] = "stop",
	[MSG_KEYNAME_AGAIN] = "again",
	[MSG_KEYNAME_PROPS] = "props",
	[MSG_KEYNAME_UNDO] = "undo",
	[MSG_KEYNAME_FRONT] = "front",
	[MSG_KEYNAME_COPY] = "copy",
	[MSG_KEYNAME_OPEN] = "open",
	[MSG_KEYNAME_PASTE] = "paste",
	[MSG_KEYNAME_FIND] = "find",
	[MSG_KEYNAME_CUT] = "cut",
	[MSG_KEYNAME_HELP] = "help",
	[MSG_KEYNAME_MENU] = "menu",
	[MSG_KEYNAME_CALC] = "calc",
	[MSG_KEYNAME_SETUP] = "setup",
	[MSG_KEYNAME_SLEEP] = "sleep",
	[MSG_KEYNAME_WAKEUP] = "wakeup",
	[MSG_KEYNAME_खाता] = "file",
	[MSG_KEYNAME_SENDखाता] = "send file",
	[MSG_KEYNAME_DELखाता] = "delete file",
	[MSG_KEYNAME_XFER] = "transfer",
	[MSG_KEYNAME_PROG1] = "prog1",
	[MSG_KEYNAME_PROG2] = "prog2",
	[MSG_KEYNAME_WWW] = "www",
	[MSG_KEYNAME_MSDOS] = "msdos",
	[MSG_KEYNAME_COFFEE] = "coffee",
	[MSG_KEYNAME_सूचीECTION] = "direction",
	[MSG_KEYNAME_CYCLEWINDOWS] = "cycle windows",
	[MSG_KEYNAME_MAIL] = "mail",
	[MSG_KEYNAME_BOOKMARKS] = "bookmarks",
	[MSG_KEYNAME_COMPUTER] = "computer",
	[MSG_KEYNAME_BACK] = "back",
	[MSG_KEYNAME_FORWARD] = "forward",
	[MSG_KEYNAME_CLOSECD] = "close cd",
	[MSG_KEYNAME_EJECTCD] = "eject cd",
	[MSG_KEYNAME_EJECTCLOSE] = "eject close cd",
	[MSG_KEYNAME_NEXTSONG] = "next song",
	[MSG_KEYNAME_PLAYPAUSE] = "play pause",
	[MSG_KEYNAME_PREVSONG] = "previous song",
	[MSG_KEYNAME_STOPCD] = "stop cd",
	[MSG_KEYNAME_RECORD] = "record",
	[MSG_KEYNAME_REWIND] = "rewind",
	[MSG_KEYNAME_PHONE] = "phone",
	[MSG_KEYNAME_ISO] = "iso",
	[MSG_KEYNAME_CONFIG] = "config",
	[MSG_KEYNAME_HOMEPG] = "home page",
	[MSG_KEYNAME_REFRESH] = "refresh",
	[MSG_KEYNAME_EXIT] = "exit",
	[MSG_KEYNAME_MOVE] = "move",
	[MSG_KEYNAME_EDIT] = "edit",
	[MSG_KEYNAME_SCROLLUP] = "scroll up",
	[MSG_KEYNAME_SCROLLDN] = "scroll down",
	[MSG_KEYNAME_KPLEFTPAR] = "keypad left paren",
	[MSG_KEYNAME_KPRIGHTPAR] = "keypad right paren",

	/* Function names. */
	[MSG_FUNCNAME_ATTRIB_BLEEP_DEC] = "attribute bleep decrement",
	[MSG_FUNCNAME_ATTRIB_BLEEP_INC] = "attribute bleep increment",
	[MSG_FUNCNAME_BLEEPS_DEC] = "bleeps decrement",
	[MSG_FUNCNAME_BLEEPS_INC] = "bleeps increment",
	[MSG_FUNCNAME_CHAR_FIRST] = "character, first",
	[MSG_FUNCNAME_CHAR_LAST] = "character, last",
	[MSG_FUNCNAME_CHAR_CURRENT] = "character, say current",
	[MSG_FUNCNAME_CHAR_HEX_AND_DEC] = "character, say hex and decimal",
	[MSG_FUNCNAME_CHAR_NEXT] = "character, say next",
	[MSG_FUNCNAME_CHAR_PHONETIC] = "character, say phonetic",
	[MSG_FUNCNAME_CHAR_PREVIOUS] = "character, say previous",
	[MSG_FUNCNAME_CURSOR_PARK] = "cursor park",
	[MSG_FUNCNAME_CUT] = "cut",
	[MSG_FUNCNAME_EDIT_DELIM] = "edit delimiters",
	[MSG_FUNCNAME_EDIT_EXNUM] = "edit exnum",
	[MSG_FUNCNAME_EDIT_MOST] = "edit most",
	[MSG_FUNCNAME_EDIT_REPEATS] = "edit repeats",
	[MSG_FUNCNAME_EDIT_SOME] = "edit some",
	[MSG_FUNCNAME_GOTO] = "go to",
	[MSG_FUNCNAME_GOTO_BOTTOM] = "go to bottom edge",
	[MSG_FUNCNAME_GOTO_LEFT] = "go to left edge",
	[MSG_FUNCNAME_GOTO_RIGHT] = "go to right edge",
	[MSG_FUNCNAME_GOTO_TOP] = "go to top edge",
	[MSG_FUNCNAME_HELP] = "help",
	[MSG_FUNCNAME_LINE_SAY_CURRENT] = "line, say current",
	[MSG_FUNCNAME_LINE_SAY_NEXT] = "line, say next",
	[MSG_FUNCNAME_LINE_SAY_PREVIOUS] = "line, say previous",
	[MSG_FUNCNAME_LINE_SAY_WITH_INDENT] = "line, say with indent",
	[MSG_FUNCNAME_PASTE] = "paste",
	[MSG_FUNCNAME_PITCH_DEC] = "pitch decrement",
	[MSG_FUNCNAME_PITCH_INC] = "pitch increment",
	[MSG_FUNCNAME_PUNC_DEC] = "punctuation decrement",
	[MSG_FUNCNAME_PUNC_INC] = "punctuation increment",
	[MSG_FUNCNAME_PUNC_LEVEL_DEC] = "punc level decrement",
	[MSG_FUNCNAME_PUNC_LEVEL_INC] = "punc level increment",
	[MSG_FUNCNAME_QUIET] = "quiet",
	[MSG_FUNCNAME_RATE_DEC] = "rate decrement",
	[MSG_FUNCNAME_RATE_INC] = "rate increment",
	[MSG_FUNCNAME_READING_PUNC_DEC] = "reading punctuation decrement",
	[MSG_FUNCNAME_READING_PUNC_INC] = "reading punctuation increment",
	[MSG_FUNCNAME_SAY_ATTRIBUTES] = "say attributes",
	[MSG_FUNCNAME_SAY_FROM_LEFT] = "say from left",
	[MSG_FUNCNAME_SAY_FROM_TOP] = "say from top",
	[MSG_FUNCNAME_SAY_POSITION] = "say position",
	[MSG_FUNCNAME_SAY_SCREEN] = "say screen",
	[MSG_FUNCNAME_SAY_TO_BOTTOM] = "say to bottom",
	[MSG_FUNCNAME_SAY_TO_RIGHT] = "say to right",
	[MSG_FUNCNAME_SPEAKUP] = "speakup",
	[MSG_FUNCNAME_SPEAKUP_LOCK] = "speakup lock",
	[MSG_FUNCNAME_SPEAKUP_OFF] = "speakup off",
	[MSG_FUNCNAME_SPEECH_KILL] = "speech kill",
	[MSG_FUNCNAME_SPELL_DELAY_DEC] = "spell delay decrement",
	[MSG_FUNCNAME_SPELL_DELAY_INC] = "spell delay increment",
	[MSG_FUNCNAME_SPELL_WORD] = "spell word",
	[MSG_FUNCNAME_SPELL_WORD_PHONETICALLY] = "spell word phonetically",
	[MSG_FUNCNAME_TONE_DEC] = "tone decrement",
	[MSG_FUNCNAME_TONE_INC] = "tone increment",
	[MSG_FUNCNAME_VOICE_DEC] = "voice decrement",
	[MSG_FUNCNAME_VOICE_INC] = "voice increment",
	[MSG_FUNCNAME_VOLUME_DEC] = "volume decrement",
	[MSG_FUNCNAME_VOLUME_INC] = "volume increment",
	[MSG_FUNCNAME_WINDOW_CLEAR] = "window, clear",
	[MSG_FUNCNAME_WINDOW_SAY] = "window, say",
	[MSG_FUNCNAME_WINDOW_SET] = "window, set",
	[MSG_FUNCNAME_WINDOW_SILENCE] = "window, silence",
	[MSG_FUNCNAME_WORD_SAY_CURRENT] = "word, say current",
	[MSG_FUNCNAME_WORD_SAY_NEXT] = "word, say next",
	[MSG_FUNCNAME_WORD_SAY_PREVIOUS] = "word, say previous",
पूर्ण;

अटल काष्ठा msg_group_t all_groups[] = अणु
	अणु
		.name = "ctl_keys",
		.start = MSG_CTL_START,
		.end = MSG_CTL_END,
	पूर्ण,
	अणु
		.name = "colors",
		.start = MSG_COLORS_START,
		.end = MSG_COLORS_END,
	पूर्ण,
	अणु
		.name = "formatted",
		.start = MSG_FORMATTED_START,
		.end = MSG_FORMATTED_END,
	पूर्ण,
	अणु
		.name = "function_names",
		.start = MSG_FUNCNAMES_START,
		.end = MSG_FUNCNAMES_END,
	पूर्ण,
	अणु
		.name = "key_names",
		.start = MSG_KEYNAMES_START,
		.end = MSG_KEYNAMES_END,
	पूर्ण,
	अणु
		.name = "announcements",
		.start = MSG_ANNOUNCEMENTS_START,
		.end = MSG_ANNOUNCEMENTS_END,
	पूर्ण,
	अणु
		.name = "states",
		.start = MSG_STATES_START,
		.end = MSG_STATES_END,
	पूर्ण,
पूर्ण;

अटल स्थिर  पूर्णांक num_groups = ARRAY_SIZE(all_groups);

अक्षर *spk_msg_get(क्रमागत msg_index_t index)
अणु
	वापस speakup_msgs[index];
पूर्ण

/*
 * Function: next_specअगरier
 * Finds the start of the next क्रमmat specअगरier in the argument string.
 * Return value: poपूर्णांकer to start of क्रमmat
 * specअगरier, or शून्य अगर no specअगरier exists.
 */
अटल अक्षर *next_specअगरier(अक्षर *input)
अणु
	पूर्णांक found = 0;
	अक्षर *next_percent = input;

	जबतक (next_percent && !found) अणु
		next_percent = म_अक्षर(next_percent, '%');
		अगर (next_percent) अणु
			/* skip over द्विगुनd percent signs */
			जबतक (next_percent[0] == '%' &&
			       next_percent[1] == '%')
				next_percent += 2;
			अगर (*next_percent == '%')
				found = 1;
			अन्यथा अगर (*next_percent == '\0')
				next_percent = शून्य;
		पूर्ण
	पूर्ण

	वापस next_percent;
पूर्ण

/* Skip over 0 or more flags. */
अटल अक्षर *skip_flags(अक्षर *input)
अणु
	जबतक ((*input != '\0') && म_अक्षर(" 0+-#", *input))
		input++;
	वापस input;
पूर्ण

/* Skip over width.precision, अगर it exists. */
अटल अक्षर *skip_width(अक्षर *input)
अणु
	जबतक (है_अंक(*input))
		input++;
	अगर (*input == '.') अणु
		input++;
		जबतक (है_अंक(*input))
			input++;
	पूर्ण
	वापस input;
पूर्ण

/*
 * Skip past the end of the conversion part.
 * Note that this code only accepts a handful of conversion specअगरiers:
 * c d s x and ld.  Not accidental; these are exactly the ones used in
 * the शेष group of क्रमmatted messages.
 */
अटल अक्षर *skip_conversion(अक्षर *input)
अणु
	अगर ((input[0] == 'l') && (input[1] == 'd'))
		input += 2;
	अन्यथा अगर ((*input != '\0') && म_अक्षर("cdsx", *input))
		input++;
	वापस input;
पूर्ण

/*
 * Function: find_specअगरier_end
 * Return a poपूर्णांकer to the end of the क्रमmat specअगरier.
 */
अटल अक्षर *find_specअगरier_end(अक्षर *input)
अणु
	input++;		/* Advance over %. */
	input = skip_flags(input);
	input = skip_width(input);
	input = skip_conversion(input);
	वापस input;
पूर्ण

/*
 * Function: compare_specअगरiers
 * Compare the क्रमmat specअगरiers poपूर्णांकed to by *input1 and *input2.
 * Return true अगर they are the same, false otherwise.
 * Advance *input1 and *input2 so that they poपूर्णांक to the अक्षरacter following
 * the end of the specअगरier.
 */
अटल bool compare_specअगरiers(अक्षर **input1, अक्षर **input2)
अणु
	bool same = false;
	अक्षर *end1 = find_specअगरier_end(*input1);
	अक्षर *end2 = find_specअगरier_end(*input2);
	माप_प्रकार length1 = end1 - *input1;
	माप_प्रकार length2 = end2 - *input2;

	अगर ((length1 == length2) && !स_भेद(*input1, *input2, length1))
		same = true;

	*input1 = end1;
	*input2 = end2;
	वापस same;
पूर्ण

/*
 * Function: fmt_validate
 * Check that two क्रमmat strings contain the same number of क्रमmat specअगरiers,
 * and that the order of specअगरiers is the same in both strings.
 * Return true अगर the condition holds, false अगर it करोesn't.
 */
अटल bool fmt_validate(अक्षर *ढाँचा, अक्षर *user)
अणु
	bool valid = true;
	bool still_comparing = true;
	अक्षर *ढाँचा_ptr = ढाँचा;
	अक्षर *user_ptr = user;

	जबतक (still_comparing && valid) अणु
		ढाँचा_ptr = next_specअगरier(ढाँचा_ptr);
		user_ptr = next_specअगरier(user_ptr);
		अगर (ढाँचा_ptr && user_ptr) अणु
			/* Both have at least one more specअगरier. */
			valid = compare_specअगरiers(&ढाँचा_ptr, &user_ptr);
		पूर्ण अन्यथा अणु
			/* No more क्रमmat specअगरiers in one or both strings. */
			still_comparing = false;
			/* See अगर one has more specअगरiers than the other. */
			अगर (ढाँचा_ptr || user_ptr)
				valid = false;
		पूर्ण
	पूर्ण
	वापस valid;
पूर्ण

/*
 * Function: msg_set
 * Description: Add a user-supplied message to the user_messages array.
 * The message text is copied to a memory area allocated with kदो_स्मृति.
 * If the function fails, then user_messages is untouched.
 * Arguments:
 * - index: a message number, as found in i18n.h.
 * - text:  text of message.  Not NUL-terminated.
 * - length: number of bytes in text.
 * Failure conditions:
 * -EINVAL -  Invalid क्रमmat specअगरiers in क्रमmatted message or illegal index.
 * -ENOMEM -  Unable to allocate memory.
 */
sमाप_प्रकार spk_msg_set(क्रमागत msg_index_t index, अक्षर *text, माप_प्रकार length)
अणु
	अक्षर *newstr = शून्य;
	अचिन्हित दीर्घ flags;

	अगर ((index < MSG_FIRST_INDEX) || (index >= MSG_LAST_INDEX))
		वापस -EINVAL;

	newstr = kmemdup_nul(text, length, GFP_KERNEL);
	अगर (!newstr)
		वापस -ENOMEM;

	अगर (index >= MSG_FORMATTED_START &&
	    index <= MSG_FORMATTED_END &&
	    !fmt_validate(speakup_शेष_msgs[index], newstr)) अणु
		kमुक्त(newstr);
		वापस -EINVAL;
	पूर्ण
	spin_lock_irqsave(&speakup_info.spinlock, flags);
	अगर (speakup_msgs[index] != speakup_शेष_msgs[index])
		kमुक्त(speakup_msgs[index]);
	speakup_msgs[index] = newstr;
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस 0;
पूर्ण

/*
 * Find a message group, given its name.  Return a poपूर्णांकer to the काष्ठाure
 * अगर found, or शून्य otherwise.
 */
काष्ठा msg_group_t *spk_find_msg_group(स्थिर अक्षर *group_name)
अणु
	काष्ठा msg_group_t *group = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < num_groups; i++) अणु
		अगर (!म_भेद(all_groups[i].name, group_name)) अणु
			group = &all_groups[i];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस group;
पूर्ण

व्योम spk_reset_msg_group(काष्ठा msg_group_t *group)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत msg_index_t i;

	spin_lock_irqsave(&speakup_info.spinlock, flags);

	क्रम (i = group->start; i <= group->end; i++) अणु
		अगर (speakup_msgs[i] != speakup_शेष_msgs[i])
			kमुक्त(speakup_msgs[i]);
		speakup_msgs[i] = speakup_शेष_msgs[i];
	पूर्ण
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
पूर्ण

/* Called at initialization समय, to establish शेष messages. */
व्योम spk_initialize_msgs(व्योम)
अणु
	स_नकल(speakup_msgs, speakup_शेष_msgs,
	       माप(speakup_शेष_msgs));
पूर्ण

/* Free user-supplied strings when module is unloaded: */
व्योम spk_मुक्त_user_msgs(व्योम)
अणु
	क्रमागत msg_index_t index;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	क्रम (index = MSG_FIRST_INDEX; index < MSG_LAST_INDEX; index++) अणु
		अगर (speakup_msgs[index] != speakup_शेष_msgs[index]) अणु
			kमुक्त(speakup_msgs[index]);
			speakup_msgs[index] = speakup_शेष_msgs[index];
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
पूर्ण
