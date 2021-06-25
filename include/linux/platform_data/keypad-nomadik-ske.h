<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Naveen Kumar Gaddipati <naveen.gaddipati@stericsson.com>
 *
 * ux500 Scroll key and Keypad Encoder (SKE) header
 */

#अगर_अघोषित __SKE_H
#घोषणा __SKE_H

#समावेश <linux/input/matrix_keypad.h>

/* रेजिस्टर definitions क्रम SKE peripheral */
#घोषणा SKE_CR		0x00
#घोषणा SKE_VAL0	0x04
#घोषणा SKE_VAL1	0x08
#घोषणा SKE_DBCR	0x0C
#घोषणा SKE_IMSC	0x10
#घोषणा SKE_RIS		0x14
#घोषणा SKE_MIS		0x18
#घोषणा SKE_ICR		0x1C

/*
 * Keypad module
 */

/**
 * काष्ठा keypad_platक्रमm_data - काष्ठाure क्रम platक्रमm specअगरic data
 * @init:	poपूर्णांकer to keypad init function
 * @निकास:	poपूर्णांकer to keypad deinitialisation function
 * @keymap_data: matrix scan code table क्रम keycodes
 * @krow:	maximum number of rows
 * @kcol:	maximum number of columns
 * @debounce_ms: platक्रमm specअगरic debounce समय
 * @no_स्वतःrepeat: flag क्रम स्वतः repetition
 * @wakeup_enable: allow waking up the प्रणाली
 */
काष्ठा ske_keypad_platक्रमm_data अणु
	पूर्णांक (*init)(व्योम);
	पूर्णांक (*निकास)(व्योम);
	स्थिर काष्ठा matrix_keymap_data *keymap_data;
	u8 krow;
	u8 kcol;
	u8 debounce_ms;
	bool no_स्वतःrepeat;
	bool wakeup_enable;
पूर्ण;
#पूर्ण_अगर	/*__SKE_KPD_H*/
