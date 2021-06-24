<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Texas Instruments
 *
 * Simple driver क्रम Texas Instruments LM355x LED driver chip
 *
 * Author: G.Shark Jeong <gshark.jeong@gmail.com>
 *         Daniel Jeong <daniel.jeong@ti.com>
 */

#घोषणा LM355x_NAME "leds-lm355x"
#घोषणा LM3554_NAME "leds-lm3554"
#घोषणा LM3556_NAME "leds-lm3556"

/* lm3554 : strobe def. on */
क्रमागत lm355x_strobe अणु
	LM355x_PIN_STROBE_DISABLE = 0x00,
	LM355x_PIN_STROBE_ENABLE = 0x01,
पूर्ण;

क्रमागत lm355x_torch अणु
	LM355x_PIN_TORCH_DISABLE = 0,
	LM3554_PIN_TORCH_ENABLE = 0x80,
	LM3556_PIN_TORCH_ENABLE = 0x10,
पूर्ण;

क्रमागत lm355x_tx2 अणु
	LM355x_PIN_TX_DISABLE = 0,
	LM3554_PIN_TX_ENABLE = 0x20,
	LM3556_PIN_TX_ENABLE = 0x40,
पूर्ण;

क्रमागत lm355x_ntc अणु
	LM355x_PIN_NTC_DISABLE = 0,
	LM3554_PIN_NTC_ENABLE = 0x08,
	LM3556_PIN_NTC_ENABLE = 0x80,
पूर्ण;

क्रमागत lm355x_pmode अणु
	LM355x_PMODE_DISABLE = 0,
	LM355x_PMODE_ENABLE = 0x04,
पूर्ण;

/*
 * काष्ठा lm3554_platक्रमm_data
 * @pin_strobe: strobe input
 * @pin_torch : input pin
 *              lm3554-tx1/torch/gpio1
 *              lm3556-torch
 * @pin_tx2   : input pin
 *              lm3554-envm/tx2/gpio2
 *              lm3556-tx pin
 * @ntc_pin  : output pin
 *              lm3554-ledi/ntc
 *              lm3556-temp pin
 * @pass_mode : pass mode
 */
काष्ठा lm355x_platक्रमm_data अणु
	क्रमागत lm355x_strobe pin_strobe;
	क्रमागत lm355x_torch pin_tx1;
	क्रमागत lm355x_tx2 pin_tx2;
	क्रमागत lm355x_ntc ntc_pin;

	क्रमागत lm355x_pmode pass_mode;
पूर्ण;
