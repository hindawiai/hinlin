<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KEYPAD_EP93XX_H
#घोषणा __KEYPAD_EP93XX_H

काष्ठा matrix_keymap_data;

/* flags क्रम the ep93xx_keypad driver */
#घोषणा EP93XX_KEYPAD_DISABLE_3_KEY	(1<<0)	/* disable 3-key reset */
#घोषणा EP93XX_KEYPAD_DIAG_MODE		(1<<1)	/* diagnostic mode */
#घोषणा EP93XX_KEYPAD_BACK_DRIVE	(1<<2)	/* back driving mode */
#घोषणा EP93XX_KEYPAD_TEST_MODE		(1<<3)	/* scan only column 0 */
#घोषणा EP93XX_KEYPAD_AUTOREPEAT	(1<<4)	/* enable key स्वतःrepeat */

/**
 * काष्ठा ep93xx_keypad_platक्रमm_data - platक्रमm specअगरic device काष्ठाure
 * @keymap_data:	poपूर्णांकer to &matrix_keymap_data
 * @debounce:		debounce start count; terminal count is 0xff
 * @prescale:		row/column counter pre-scaler load value
 * @flags:		see above
 */
काष्ठा ep93xx_keypad_platक्रमm_data अणु
	काष्ठा matrix_keymap_data *keymap_data;
	अचिन्हित पूर्णांक	debounce;
	अचिन्हित पूर्णांक	prescale;
	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	clk_rate;
पूर्ण;

#घोषणा EP93XX_MATRIX_ROWS		(8)
#घोषणा EP93XX_MATRIX_COLS		(8)

#पूर्ण_अगर	/* __KEYPAD_EP93XX_H */
