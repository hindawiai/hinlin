<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * lm8323.h - Configuration क्रम LM8323 keypad driver.
 */

#अगर_अघोषित __LINUX_LM8323_H
#घोषणा __LINUX_LM8323_H

#समावेश <linux/types.h>

/*
 * Largest keycode that the chip can send, plus one,
 * so keys can be mapped directly at the index of the
 * LM8323 keycode instead of subtracting one.
 */
#घोषणा LM8323_KEYMAP_SIZE	(0x7f + 1)

#घोषणा LM8323_NUM_PWMS		3

काष्ठा lm8323_platक्रमm_data अणु
	पूर्णांक debounce_समय; /* Time to watch क्रम key bouncing, in ms. */
	पूर्णांक active_समय; /* Idle समय until sleep, in ms. */

	पूर्णांक size_x;
	पूर्णांक size_y;
	bool repeat;
	स्थिर अचिन्हित लघु *keymap;

	स्थिर अक्षर *pwm_names[LM8323_NUM_PWMS];

	स्थिर अक्षर *name; /* Device name. */
पूर्ण;

#पूर्ण_अगर /* __LINUX_LM8323_H */
