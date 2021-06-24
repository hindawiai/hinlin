<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SPEAKUP_TYPES_H
#घोषणा SPEAKUP_TYPES_H

/* This file includes all of the प्रकारs and काष्ठाs used in speakup. */

#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>		/* क्रम रुको_queue */
#समावेश <linux/init.h>		/* क्रम __init */
#समावेश <linux/module.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>		/* क्रम inb_p, outb_p, inb, outb, etc... */
#समावेश <linux/device.h>

क्रमागत var_type_t अणु
	VAR_NUM = 0,
	VAR_TIME,
	VAR_STRING,
	VAR_PROC
पूर्ण;

क्रमागत अणु
	E_DEFAULT = 0,
	E_SET,
	E_INC,
	E_DEC,
	E_NEW_DEFAULT,
पूर्ण;

/*
 * Note: add new members at the end, speakupmap.h depends on the values of the
 * क्रमागत starting from SPELL_DELAY (see inc_dec_var)
 */
क्रमागत var_id_t अणु
	VERSION = 0, SYNTH, SILENT, SYNTH_सूचीECT,
	KEYMAP, CHARS,
	PUNC_SOME, PUNC_MOST, PUNC_ALL,
	DELIM, REPEATS, EXNUMBER,
	DELAY, TRIGGER, JIFFY, FULL, /* all समयrs must be together */
	BLEEP_TIME, CURSOR_TIME, BELL_POS,
	SAY_CONTROL, SAY_WORD_CTL, NO_INTERRUPT, KEY_ECHO,
	SPELL_DELAY, PUNC_LEVEL, READING_PUNC,
	ATTRIB_BLEEP, BLEEPS,
	RATE, PITCH, VOL, TONE, PUNCT, VOICE, FREQUENCY, LANG,
	सूचीECT, PAUSE,
	CAPS_START, CAPS_STOP, CHARTAB, INFLECTION, FLUSH,
	MAXVARS
पूर्ण;

प्रकार पूर्णांक (*special_func)(काष्ठा vc_data *vc, u_अक्षर type, u_अक्षर ch,
		u_लघु key);

#घोषणा COLOR_BUFFER_SIZE 160

काष्ठा spk_highlight_color_track अणु
	/* Count of each background color */
	अचिन्हित पूर्णांक bgcount[8];
	/* Buffer क्रम अक्षरacters drawn with each background color */
	u16 highbuf[8][COLOR_BUFFER_SIZE];
	/* Current index पूर्णांकo highbuf */
	अचिन्हित पूर्णांक highsize[8];
	/* Reading Position क्रम each color */
	u_दीर्घ rpos[8], rx[8], ry[8];
	/* Real Cursor Y Position */
	uदीर्घ cy;
पूर्ण;

काष्ठा st_spk_t अणु
	u_दीर्घ पढ़ोing_x, cursor_x;
	u_दीर्घ पढ़ोing_y, cursor_y;
	u_दीर्घ पढ़ोing_pos, cursor_pos;
	u_दीर्घ go_x, go_pos;
	u_दीर्घ w_top, w_bottom, w_left, w_right;
	u_अक्षर w_start, w_enabled;
	u_अक्षर पढ़ोing_attr, old_attr;
	अक्षर parked, shut_up;
	काष्ठा spk_highlight_color_track ht;
	पूर्णांक tty_stopped;
पूर्ण;

/* now some defines to make these easier to use. */
#घोषणा spk_shut_up (speakup_console[vc->vc_num]->shut_up)
#घोषणा spk_समाप्तed (speakup_console[vc->vc_num]->shut_up & 0x40)
#घोषणा spk_x (speakup_console[vc->vc_num]->पढ़ोing_x)
#घोषणा spk_cx (speakup_console[vc->vc_num]->cursor_x)
#घोषणा spk_y (speakup_console[vc->vc_num]->पढ़ोing_y)
#घोषणा spk_cy (speakup_console[vc->vc_num]->cursor_y)
#घोषणा spk_pos (speakup_console[vc->vc_num]->पढ़ोing_pos)
#घोषणा spk_cp (speakup_console[vc->vc_num]->cursor_pos)
#घोषणा जाओ_pos (speakup_console[vc->vc_num]->go_pos)
#घोषणा जाओ_x (speakup_console[vc->vc_num]->go_x)
#घोषणा win_top (speakup_console[vc->vc_num]->w_top)
#घोषणा win_bottom (speakup_console[vc->vc_num]->w_bottom)
#घोषणा win_left (speakup_console[vc->vc_num]->w_left)
#घोषणा win_right (speakup_console[vc->vc_num]->w_right)
#घोषणा win_start (speakup_console[vc->vc_num]->w_start)
#घोषणा win_enabled (speakup_console[vc->vc_num]->w_enabled)
#घोषणा spk_attr (speakup_console[vc->vc_num]->पढ़ोing_attr)
#घोषणा spk_old_attr (speakup_console[vc->vc_num]->old_attr)
#घोषणा spk_parked (speakup_console[vc->vc_num]->parked)

काष्ठा st_var_header अणु
	अक्षर *name;
	क्रमागत var_id_t var_id;
	क्रमागत var_type_t var_type;
	व्योम *p_val; /* ptr to programs variable to store value */
	व्योम *data;  /* ptr to the vars data */
पूर्ण;

काष्ठा num_var_t अणु
	अक्षर *synth_fmt;
	पूर्णांक शेष_val;
	पूर्णांक low;
	पूर्णांक high;
	लघु offset, multiplier; /* क्रम fiddling rates etc. */
	अक्षर *out_str;  /* अगर synth needs अक्षर representation of number */
	पूर्णांक value;	/* current value */
पूर्ण;

काष्ठा punc_var_t अणु
	क्रमागत var_id_t var_id;
	लघु value;
पूर्ण;

काष्ठा string_var_t अणु
	अक्षर *शेष_val;
पूर्ण;

काष्ठा var_t अणु
	क्रमागत var_id_t var_id;
	जोड़ अणु
		काष्ठा num_var_t n;
		काष्ठा string_var_t s;
	पूर्ण u;
पूर्ण;

काष्ठा st_bits_data अणु /* punc, repeats, word delim bits */
	अक्षर *name;
	अक्षर *value;
	लघु mask;
पूर्ण;

काष्ठा synth_indexing अणु
	अक्षर *command;
	अचिन्हित अक्षर lowindex;
	अचिन्हित अक्षर highindex;
	अचिन्हित अक्षर currindex;
पूर्ण;

काष्ठा spk_synth;

काष्ठा spk_io_ops अणु
	पूर्णांक (*synth_out)(काष्ठा spk_synth *synth, स्थिर अक्षर ch);
	पूर्णांक (*synth_out_unicode)(काष्ठा spk_synth *synth, u16 ch);
	व्योम (*send_xअक्षर)(काष्ठा spk_synth *synth, अक्षर ch);
	व्योम (*tiocmset)(काष्ठा spk_synth *synth, अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
	अचिन्हित अक्षर (*synth_in)(काष्ठा spk_synth *synth);
	अचिन्हित अक्षर (*synth_in_noरुको)(काष्ठा spk_synth *synth);
	व्योम (*flush_buffer)(काष्ठा spk_synth *synth);
	पूर्णांक (*रुको_क्रम_xmitr)(काष्ठा spk_synth *synth);
पूर्ण;

काष्ठा spk_synth अणु
	काष्ठा list_head node;

	स्थिर अक्षर *name;
	स्थिर अक्षर *version;
	स्थिर अक्षर *दीर्घ_name;
	स्थिर अक्षर *init;
	अक्षर procspeech;
	अक्षर clear;
	पूर्णांक delay;
	पूर्णांक trigger;
	पूर्णांक jअगरfies;
	पूर्णांक full;
	पूर्णांक flush_समय;
	पूर्णांक ser;
	अक्षर *dev_name;
	लघु flags;
	लघु startup;
	स्थिर पूर्णांक checkval; /* क्रम validating a proper synth module */
	काष्ठा var_t *vars;
	पूर्णांक *शेष_pitch;
	पूर्णांक *शेष_vol;
	काष्ठा spk_io_ops *io_ops;
	पूर्णांक (*probe)(काष्ठा spk_synth *synth);
	व्योम (*release)(काष्ठा spk_synth *synth);
	स्थिर अक्षर *(*synth_immediate)(काष्ठा spk_synth *synth,
				       स्थिर अक्षर *buff);
	व्योम (*catch_up)(काष्ठा spk_synth *synth);
	व्योम (*flush)(काष्ठा spk_synth *synth);
	पूर्णांक (*is_alive)(काष्ठा spk_synth *synth);
	पूर्णांक (*synth_adjust)(काष्ठा st_var_header *var);
	व्योम (*पढ़ो_buff_add)(u_अक्षर c);
	अचिन्हित अक्षर (*get_index)(काष्ठा spk_synth *synth);
	काष्ठा synth_indexing indexing;
	पूर्णांक alive;
	काष्ठा attribute_group attributes;

	व्योम *dev;
पूर्ण;

/*
 * module_spk_synth() - Helper macro क्रम रेजिस्टरing a speakup driver
 * @__spk_synth: spk_synth काष्ठा
 * Helper macro क्रम speakup drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_spk_synth(__spk_synth) \
	module_driver(__spk_synth, synth_add, synth_हटाओ)

काष्ठा speakup_info_t अणु
	spinlock_t spinlock;
	पूर्णांक port_tts;
	पूर्णांक flushing;
पूर्ण;

काष्ठा bleep अणु
	लघु freq;
	अचिन्हित दीर्घ jअगरfies;
	पूर्णांक active;
पूर्ण;
#पूर्ण_अगर
