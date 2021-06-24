<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Consumer पूर्णांकerface the pin control subप्रणाली
 *
 * Copyright (C) 2012 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 * Based on bits of regulator core, gpio core and clk core
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#अगर_अघोषित __LINUX_PINCTRL_CONSUMER_H
#घोषणा __LINUX_PINCTRL_CONSUMER_H

#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pinctrl/pinctrl-state.h>

/* This काष्ठा is निजी to the core and should be regarded as a cookie */
काष्ठा pinctrl;
काष्ठा pinctrl_state;
काष्ठा device;

#अगर_घोषित CONFIG_PINCTRL

/* External पूर्णांकerface to pin control */
बाह्य bool pinctrl_gpio_can_use_line(अचिन्हित gpio);
बाह्य पूर्णांक pinctrl_gpio_request(अचिन्हित gpio);
बाह्य व्योम pinctrl_gpio_मुक्त(अचिन्हित gpio);
बाह्य पूर्णांक pinctrl_gpio_direction_input(अचिन्हित gpio);
बाह्य पूर्णांक pinctrl_gpio_direction_output(अचिन्हित gpio);
बाह्य पूर्णांक pinctrl_gpio_set_config(अचिन्हित gpio, अचिन्हित दीर्घ config);

बाह्य काष्ठा pinctrl * __must_check pinctrl_get(काष्ठा device *dev);
बाह्य व्योम pinctrl_put(काष्ठा pinctrl *p);
बाह्य काष्ठा pinctrl_state * __must_check pinctrl_lookup_state(
							काष्ठा pinctrl *p,
							स्थिर अक्षर *name);
बाह्य पूर्णांक pinctrl_select_state(काष्ठा pinctrl *p, काष्ठा pinctrl_state *s);

बाह्य काष्ठा pinctrl * __must_check devm_pinctrl_get(काष्ठा device *dev);
बाह्य व्योम devm_pinctrl_put(काष्ठा pinctrl *p);
बाह्य पूर्णांक pinctrl_select_शेष_state(काष्ठा device *dev);

#अगर_घोषित CONFIG_PM
बाह्य पूर्णांक pinctrl_pm_select_शेष_state(काष्ठा device *dev);
बाह्य पूर्णांक pinctrl_pm_select_sleep_state(काष्ठा device *dev);
बाह्य पूर्णांक pinctrl_pm_select_idle_state(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक pinctrl_pm_select_शेष_state(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक pinctrl_pm_select_sleep_state(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक pinctrl_pm_select_idle_state(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अन्यथा /* !CONFIG_PINCTRL */

अटल अंतरभूत bool pinctrl_gpio_can_use_line(अचिन्हित gpio)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक pinctrl_gpio_request(अचिन्हित gpio)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pinctrl_gpio_मुक्त(अचिन्हित gpio)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक pinctrl_gpio_direction_input(अचिन्हित gpio)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pinctrl_gpio_direction_output(अचिन्हित gpio)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pinctrl_gpio_set_config(अचिन्हित gpio, अचिन्हित दीर्घ config)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा pinctrl * __must_check pinctrl_get(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम pinctrl_put(काष्ठा pinctrl *p)
अणु
पूर्ण

अटल अंतरभूत काष्ठा pinctrl_state * __must_check pinctrl_lookup_state(
							काष्ठा pinctrl *p,
							स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक pinctrl_select_state(काष्ठा pinctrl *p,
				       काष्ठा pinctrl_state *s)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा pinctrl * __must_check devm_pinctrl_get(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम devm_pinctrl_put(काष्ठा pinctrl *p)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक pinctrl_select_शेष_state(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pinctrl_pm_select_शेष_state(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pinctrl_pm_select_sleep_state(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pinctrl_pm_select_idle_state(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PINCTRL */

अटल अंतरभूत काष्ठा pinctrl * __must_check pinctrl_get_select(
					काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा pinctrl *p;
	काष्ठा pinctrl_state *s;
	पूर्णांक ret;

	p = pinctrl_get(dev);
	अगर (IS_ERR(p))
		वापस p;

	s = pinctrl_lookup_state(p, name);
	अगर (IS_ERR(s)) अणु
		pinctrl_put(p);
		वापस ERR_CAST(s);
	पूर्ण

	ret = pinctrl_select_state(p, s);
	अगर (ret < 0) अणु
		pinctrl_put(p);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस p;
पूर्ण

अटल अंतरभूत काष्ठा pinctrl * __must_check pinctrl_get_select_शेष(
					काष्ठा device *dev)
अणु
	वापस pinctrl_get_select(dev, PINCTRL_STATE_DEFAULT);
पूर्ण

अटल अंतरभूत काष्ठा pinctrl * __must_check devm_pinctrl_get_select(
					काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा pinctrl *p;
	काष्ठा pinctrl_state *s;
	पूर्णांक ret;

	p = devm_pinctrl_get(dev);
	अगर (IS_ERR(p))
		वापस p;

	s = pinctrl_lookup_state(p, name);
	अगर (IS_ERR(s)) अणु
		devm_pinctrl_put(p);
		वापस ERR_CAST(s);
	पूर्ण

	ret = pinctrl_select_state(p, s);
	अगर (ret < 0) अणु
		devm_pinctrl_put(p);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस p;
पूर्ण

अटल अंतरभूत काष्ठा pinctrl * __must_check devm_pinctrl_get_select_शेष(
					काष्ठा device *dev)
अणु
	वापस devm_pinctrl_get_select(dev, PINCTRL_STATE_DEFAULT);
पूर्ण

#पूर्ण_अगर /* __LINUX_PINCTRL_CONSUMER_H */
