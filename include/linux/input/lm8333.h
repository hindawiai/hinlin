<शैली गुरु>
/*
 * खुला include क्रम LM8333 keypad driver - same license as driver
 * Copyright (C) 2012 Wolfram Sang, Pengutronix <kernel@pengutronix.de>
 */

#अगर_अघोषित _LM8333_H
#घोषणा _LM8333_H

काष्ठा lm8333;

काष्ठा lm8333_platक्रमm_data अणु
	/* Keymap data */
	स्थिर काष्ठा matrix_keymap_data *matrix_data;
	/* Active समयout beक्रमe enter HALT mode in microseconds */
	अचिन्हित active_समय;
	/* Debounce पूर्णांकerval in microseconds */
	अचिन्हित debounce_समय;
पूर्ण;

बाह्य पूर्णांक lm8333_पढ़ो8(काष्ठा lm8333 *lm8333, u8 cmd);
बाह्य पूर्णांक lm8333_ग_लिखो8(काष्ठा lm8333 *lm8333, u8 cmd, u8 val);
बाह्य पूर्णांक lm8333_पढ़ो_block(काष्ठा lm8333 *lm8333, u8 cmd, u8 len, u8 *buf);

#पूर्ण_अगर /* _LM8333_H */
