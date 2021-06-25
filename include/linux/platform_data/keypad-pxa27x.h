<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARCH_PXA27x_KEYPAD_H
#घोषणा __ASM_ARCH_PXA27x_KEYPAD_H

#समावेश <linux/input.h>
#समावेश <linux/input/matrix_keypad.h>

#घोषणा MAX_MATRIX_KEY_ROWS	(8)
#घोषणा MAX_MATRIX_KEY_COLS	(8)
#घोषणा MATRIX_ROW_SHIFT	(3)
#घोषणा MAX_सूचीECT_KEY_NUM	(8)

/* pxa3xx keypad platक्रमm specअगरic parameters
 *
 * NOTE:
 * 1. direct_key_num indicates the number of keys in the direct keypad
 *    _plus_ the number of rotary-encoder sensor inमाला_दो,  this can be
 *    left as 0 अगर only rotary encoders are enabled,  the driver will
 *    स्वतःmatically calculate this
 *
 * 2. direct_key_map is the key code map क्रम the direct keys, अगर rotary
 *    encoder(s) are enabled, direct key 0/1(2/3) will be ignored
 *
 * 3. rotary can be either पूर्णांकerpreted as a relative input event (e.g.
 *    REL_WHEEL/REL_HWHEEL) or specअगरic keys (e.g. UP/DOWN/LEFT/RIGHT)
 *
 * 4. matrix key and direct key will use the same debounce_पूर्णांकerval by
 *    शेष, which should be sufficient in most हालs
 *
 * pxa168 keypad platक्रमm specअगरic parameter
 *
 * NOTE:
 * clear_wakeup_event callback is a workaround required to clear the
 * keypad पूर्णांकerrupt. The keypad wake must be cleared in addition to
 * पढ़ोing the MI/DI bits in the KPC रेजिस्टर.
 */
काष्ठा pxa27x_keypad_platक्रमm_data अणु

	/* code map क्रम the matrix keys */
	स्थिर काष्ठा matrix_keymap_data *matrix_keymap_data;
	अचिन्हित पूर्णांक	matrix_key_rows;
	अचिन्हित पूर्णांक	matrix_key_cols;

	/* direct keys */
	पूर्णांक		direct_key_num;
	अचिन्हित पूर्णांक	direct_key_map[MAX_सूचीECT_KEY_NUM];
	/* the key output may be low active */
	पूर्णांक		direct_key_low_active;
	/* give board a chance to choose the start direct key */
	अचिन्हित पूर्णांक	direct_key_mask;

	/* rotary encoders 0 */
	पूर्णांक		enable_rotary0;
	पूर्णांक		rotary0_rel_code;
	पूर्णांक		rotary0_up_key;
	पूर्णांक		rotary0_करोwn_key;

	/* rotary encoders 1 */
	पूर्णांक		enable_rotary1;
	पूर्णांक		rotary1_rel_code;
	पूर्णांक		rotary1_up_key;
	पूर्णांक		rotary1_करोwn_key;

	/* key debounce पूर्णांकerval */
	अचिन्हित पूर्णांक	debounce_पूर्णांकerval;

	/* clear wakeup event requirement क्रम pxa168 */
	व्योम		(*clear_wakeup_event)(व्योम);
पूर्ण;

बाह्य व्योम pxa_set_keypad_info(काष्ठा pxa27x_keypad_platक्रमm_data *info);

#पूर्ण_अगर /* __ASM_ARCH_PXA27x_KEYPAD_H */
