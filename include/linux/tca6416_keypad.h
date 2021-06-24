<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tca6416 keypad platक्रमm support
 *
 * Copyright (C) 2010 Texas Instruments
 *
 * Author: Sriramakrishnan <srk@ti.com>
 */

#अगर_अघोषित _TCA6416_KEYS_H
#घोषणा _TCA6416_KEYS_H

#समावेश <linux/types.h>

काष्ठा tca6416_button अणु
	/* Configuration parameters */
	पूर्णांक code;		/* input event code (KEY_*, SW_*) */
	पूर्णांक active_low;
	पूर्णांक type;		/* input event type (EV_KEY, EV_SW) */
पूर्ण;

काष्ठा tca6416_keys_platक्रमm_data अणु
	काष्ठा tca6416_button *buttons;
	पूर्णांक nbuttons;
	अचिन्हित पूर्णांक rep:1;	/* enable input subप्रणाली स्वतः repeat */
	uपूर्णांक16_t pinmask;
	uपूर्णांक16_t invert;
	पूर्णांक irq_is_gpio;
	पूर्णांक use_polling;	/* use polling अगर Interrupt is not connected*/
पूर्ण;
#पूर्ण_अगर
