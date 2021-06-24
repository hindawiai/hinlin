<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Per-device inक्रमmation from the pin control प्रणाली.
 * This is the stuff that get included पूर्णांकo the device
 * core.
 *
 * Copyright (C) 2012 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 * This पूर्णांकerface is used in the core to keep track of pins.
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#अगर_अघोषित PINCTRL_DEVINFO_H
#घोषणा PINCTRL_DEVINFO_H

#अगर_घोषित CONFIG_PINCTRL

/* The device core acts as a consumer toward pinctrl */
#समावेश <linux/pinctrl/consumer.h>

/**
 * काष्ठा dev_pin_info - pin state container क्रम devices
 * @p: pinctrl handle क्रम the containing device
 * @शेष_state: the शेष state क्रम the handle, अगर found
 * @init_state: the state at probe समय, अगर found
 * @sleep_state: the state at suspend समय, अगर found
 * @idle_state: the state at idle (runसमय suspend) समय, अगर found
 */
काष्ठा dev_pin_info अणु
	काष्ठा pinctrl *p;
	काष्ठा pinctrl_state *शेष_state;
	काष्ठा pinctrl_state *init_state;
#अगर_घोषित CONFIG_PM
	काष्ठा pinctrl_state *sleep_state;
	काष्ठा pinctrl_state *idle_state;
#पूर्ण_अगर
पूर्ण;

बाह्य पूर्णांक pinctrl_bind_pins(काष्ठा device *dev);
बाह्य पूर्णांक pinctrl_init_करोne(काष्ठा device *dev);

#अन्यथा

काष्ठा device;

/* Stubs अगर we're not using pinctrl */

अटल अंतरभूत पूर्णांक pinctrl_bind_pins(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pinctrl_init_करोne(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PINCTRL */
#पूर्ण_अगर /* PINCTRL_DEVINFO_H */
