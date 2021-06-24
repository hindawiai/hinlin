<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
* Copyright (C) 2012 Texas Instruments
*
* Simple driver क्रम Texas Instruments LM3642 LED driver chip
*
* Author: G.Shark Jeong <gshark.jeong@gmail.com>
*         Daniel Jeong <daniel.jeong@ti.com>
*/

#अगर_अघोषित __LINUX_LM3642_H
#घोषणा __LINUX_LM3642_H

#घोषणा LM3642_NAME "leds-lm3642"

क्रमागत lm3642_torch_pin_enable अणु
	LM3642_TORCH_PIN_DISABLE = 0x00,
	LM3642_TORCH_PIN_ENABLE = 0x10,
पूर्ण;

क्रमागत lm3642_strobe_pin_enable अणु
	LM3642_STROBE_PIN_DISABLE = 0x00,
	LM3642_STROBE_PIN_ENABLE = 0x20,
पूर्ण;

क्रमागत lm3642_tx_pin_enable अणु
	LM3642_TX_PIN_DISABLE = 0x00,
	LM3642_TX_PIN_ENABLE = 0x40,
पूर्ण;

काष्ठा lm3642_platक्रमm_data अणु
	क्रमागत lm3642_torch_pin_enable torch_pin;
	क्रमागत lm3642_strobe_pin_enable strobe_pin;
	क्रमागत lm3642_tx_pin_enable tx_pin;
पूर्ण;

#पूर्ण_अगर /* __LINUX_LM3642_H */
