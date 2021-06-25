<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPEAKUP_H
#घोषणा _SPEAKUP_H

#समावेश "spk_types.h"
#समावेश "i18n.h"

#घोषणा SPEAKUP_VERSION "3.1.6"
#घोषणा KEY_MAP_VER 119
#घोषणा SHIFT_TBL_SIZE 64
#घोषणा MAX_DESC_LEN 72

#घोषणा TOGGLE_0 .u.n = अणुशून्य, 0, 0, 1, 0, 0, शून्य पूर्ण
#घोषणा TOGGLE_1 .u.n = अणुशून्य, 1, 0, 1, 0, 0, शून्य पूर्ण
#घोषणा MAXVARLEN 15

#घोषणा SYNTH_OK 0x0001
#घोषणा B_ALPHA 0x0002
#घोषणा ALPHA 0x0003
#घोषणा B_CAP 0x0004
#घोषणा A_CAP 0x0007
#घोषणा B_NUM 0x0008
#घोषणा NUM 0x0009
#घोषणा ALPHANUM (B_ALPHA | B_NUM)
#घोषणा SOME 0x0010
#घोषणा MOST 0x0020
#घोषणा PUNC 0x0040
#घोषणा A_PUNC 0x0041
#घोषणा B_WDLM 0x0080
#घोषणा WDLM 0x0081
#घोषणा B_EXNUM 0x0100
#घोषणा CH_RPT 0x0200
#घोषणा B_CTL 0x0400
#घोषणा A_CTL (B_CTL + SYNTH_OK)
#घोषणा B_SYM 0x0800
#घोषणा B_CAPSYM (B_CAP | B_SYM)

/* FIXME: u16 */
#घोषणा IS_WDLM(x) (spk_अक्षरtab[((u_अक्षर)x)] & B_WDLM)
#घोषणा IS_CHAR(x, type) (spk_अक्षरtab[((u_अक्षर)x)] & type)
#घोषणा IS_TYPE(x, type) ((spk_अक्षरtab[((u_अक्षर)x)] & type) == type)

पूर्णांक speakup_thपढ़ो(व्योम *data);
व्योम spk_reset_शेष_अक्षरs(व्योम);
व्योम spk_reset_शेष_अक्षरtab(व्योम);
व्योम synth_start(व्योम);
व्योम synth_insert_next_index(पूर्णांक sent_num);
व्योम spk_reset_index_count(पूर्णांक sc);
व्योम spk_get_index_count(पूर्णांक *linecount, पूर्णांक *sentcount);
पूर्णांक spk_set_key_info(स्थिर u_अक्षर *key_info, u_अक्षर *k_buffer);
अक्षर *spk_strlwr(अक्षर *s);
अक्षर *spk_s2uअक्षर(अक्षर *start, अक्षर *dest);
पूर्णांक speakup_kobj_init(व्योम);
व्योम speakup_kobj_निकास(व्योम);
पूर्णांक spk_अक्षरtab_get_value(अक्षर *keyword);
व्योम speakup_रेजिस्टर_var(काष्ठा var_t *var);
व्योम speakup_unरेजिस्टर_var(क्रमागत var_id_t var_id);
काष्ठा st_var_header *spk_get_var_header(क्रमागत var_id_t var_id);
काष्ठा st_var_header *spk_var_header_by_name(स्थिर अक्षर *name);
काष्ठा punc_var_t *spk_get_punc_var(क्रमागत var_id_t var_id);
पूर्णांक spk_set_num_var(पूर्णांक val, काष्ठा st_var_header *var, पूर्णांक how);
पूर्णांक spk_set_string_var(स्थिर अक्षर *page, काष्ठा st_var_header *var, पूर्णांक len);
पूर्णांक spk_set_mask_bits(स्थिर अक्षर *input, स्थिर पूर्णांक which, स्थिर पूर्णांक how);
बाह्य special_func spk_special_handler;
पूर्णांक spk_handle_help(काष्ठा vc_data *vc, u_अक्षर type, u_अक्षर ch, u_लघु key);
पूर्णांक synth_init(अक्षर *name);
व्योम synth_release(व्योम);

व्योम spk_करो_flush(व्योम);
व्योम speakup_start_ttys(व्योम);
व्योम synth_buffer_add(u16 ch);
व्योम synth_buffer_clear(व्योम);
पूर्णांक speakup_set_selection(काष्ठा tty_काष्ठा *tty);
व्योम speakup_cancel_selection(व्योम);
पूर्णांक speakup_paste_selection(काष्ठा tty_काष्ठा *tty);
व्योम speakup_cancel_paste(व्योम);
व्योम speakup_रेजिस्टर_devsynth(व्योम);
व्योम speakup_unरेजिस्टर_devsynth(व्योम);
व्योम synth_ग_लिखो(स्थिर अक्षर *buf, माप_प्रकार count);
पूर्णांक synth_supports_indexing(व्योम);

बाह्य काष्ठा vc_data *spk_sel_cons;
बाह्य अचिन्हित लघु spk_xs, spk_ys, spk_xe, spk_ye; /* our region poपूर्णांकs */

बाह्य रुको_queue_head_t speakup_event;
बाह्य काष्ठा kobject *speakup_kobj;
बाह्य काष्ठा task_काष्ठा *speakup_task;
बाह्य स्थिर u_अक्षर spk_key_शेषs[];

/* Protect speakup synthesizer list */
बाह्य काष्ठा mutex spk_mutex;
बाह्य काष्ठा st_spk_t *speakup_console[];
बाह्य काष्ठा spk_synth *synth;
बाह्य अक्षर spk_pitch_buff[];
बाह्य u_अक्षर *spk_our_keys[];
बाह्य लघु spk_punc_masks[];
बाह्य अक्षर spk_str_caps_start[], spk_str_caps_stop[], spk_str_छोड़ो[];
बाह्य bool spk_छोड़ोd;
बाह्य स्थिर काष्ठा st_bits_data spk_punc_info[];
बाह्य u_अक्षर spk_key_buf[600];
बाह्य अक्षर *spk_अक्षरacters[];
बाह्य अक्षर *spk_शेष_अक्षरs[];
बाह्य u_लघु spk_अक्षरtab[];
बाह्य पूर्णांक spk_no_पूर्णांकr, spk_say_ctrl, spk_say_word_ctl, spk_punc_level;
बाह्य पूर्णांक spk_पढ़ोing_punc, spk_attrib_bleep, spk_bleeps;
बाह्य पूर्णांक spk_bleep_समय, spk_bell_pos;
बाह्य पूर्णांक spk_spell_delay, spk_key_echo;
बाह्य लघु spk_punc_mask;
बाह्य लघु spk_pitch_shअगरt, synth_flags;
बाह्य bool spk_quiet_boot;
बाह्य अक्षर *synth_name;
बाह्य काष्ठा bleep spk_unprocessed_sound;

/* Prototypes from fakekey.c. */
पूर्णांक speakup_add_भव_keyboard(व्योम);
व्योम speakup_हटाओ_भव_keyboard(व्योम);
व्योम speakup_fake_करोwn_arrow(व्योम);
bool speakup_fake_key_pressed(व्योम);

#पूर्ण_अगर
