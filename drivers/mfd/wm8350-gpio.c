<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8350-core.c  --  Device access क्रम Wolfson WM8350
 *
 * Copyright 2007, 2008 Wolfson Microelectronics PLC.
 *
 * Author: Liam Girdwood
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <linux/mfd/wm8350/core.h>
#समावेश <linux/mfd/wm8350/gpपन.स>
#समावेश <linux/mfd/wm8350/pmic.h>

अटल पूर्णांक gpio_set_dir(काष्ठा wm8350 *wm8350, पूर्णांक gpio, पूर्णांक dir)
अणु
	पूर्णांक ret;

	wm8350_reg_unlock(wm8350);
	अगर (dir == WM8350_GPIO_सूची_OUT)
		ret = wm8350_clear_bits(wm8350,
					WM8350_GPIO_CONFIGURATION_I_O,
					1 << gpio);
	अन्यथा
		ret = wm8350_set_bits(wm8350,
				      WM8350_GPIO_CONFIGURATION_I_O,
				      1 << gpio);
	wm8350_reg_lock(wm8350);
	वापस ret;
पूर्ण

अटल पूर्णांक wm8350_gpio_set_debounce(काष्ठा wm8350 *wm8350, पूर्णांक gpio, पूर्णांक db)
अणु
	अगर (db == WM8350_GPIO_DEBOUNCE_ON)
		वापस wm8350_set_bits(wm8350, WM8350_GPIO_DEBOUNCE,
				       1 << gpio);
	अन्यथा
		वापस wm8350_clear_bits(wm8350,
					 WM8350_GPIO_DEBOUNCE, 1 << gpio);
पूर्ण

अटल पूर्णांक gpio_set_func(काष्ठा wm8350 *wm8350, पूर्णांक gpio, पूर्णांक func)
अणु
	u16 reg;

	wm8350_reg_unlock(wm8350);
	चयन (gpio) अणु
	हाल 0:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_1)
		    & ~WM8350_GP0_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_1,
				 reg | ((func & 0xf) << 0));
		अवरोध;
	हाल 1:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_1)
		    & ~WM8350_GP1_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_1,
				 reg | ((func & 0xf) << 4));
		अवरोध;
	हाल 2:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_1)
		    & ~WM8350_GP2_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_1,
				 reg | ((func & 0xf) << 8));
		अवरोध;
	हाल 3:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_1)
		    & ~WM8350_GP3_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_1,
				 reg | ((func & 0xf) << 12));
		अवरोध;
	हाल 4:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_2)
		    & ~WM8350_GP4_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_2,
				 reg | ((func & 0xf) << 0));
		अवरोध;
	हाल 5:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_2)
		    & ~WM8350_GP5_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_2,
				 reg | ((func & 0xf) << 4));
		अवरोध;
	हाल 6:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_2)
		    & ~WM8350_GP6_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_2,
				 reg | ((func & 0xf) << 8));
		अवरोध;
	हाल 7:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_2)
		    & ~WM8350_GP7_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_2,
				 reg | ((func & 0xf) << 12));
		अवरोध;
	हाल 8:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_3)
		    & ~WM8350_GP8_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_3,
				 reg | ((func & 0xf) << 0));
		अवरोध;
	हाल 9:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_3)
		    & ~WM8350_GP9_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_3,
				 reg | ((func & 0xf) << 4));
		अवरोध;
	हाल 10:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_3)
		    & ~WM8350_GP10_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_3,
				 reg | ((func & 0xf) << 8));
		अवरोध;
	हाल 11:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_3)
		    & ~WM8350_GP11_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_3,
				 reg | ((func & 0xf) << 12));
		अवरोध;
	हाल 12:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_FUNCTION_SELECT_4)
		    & ~WM8350_GP12_FN_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_GPIO_FUNCTION_SELECT_4,
				 reg | ((func & 0xf) << 0));
		अवरोध;
	शेष:
		wm8350_reg_lock(wm8350);
		वापस -EINVAL;
	पूर्ण

	wm8350_reg_lock(wm8350);
	वापस 0;
पूर्ण

अटल पूर्णांक gpio_set_pull_up(काष्ठा wm8350 *wm8350, पूर्णांक gpio, पूर्णांक up)
अणु
	अगर (up)
		वापस wm8350_set_bits(wm8350,
				       WM8350_GPIO_PIN_PULL_UP_CONTROL,
				       1 << gpio);
	अन्यथा
		वापस wm8350_clear_bits(wm8350,
					 WM8350_GPIO_PIN_PULL_UP_CONTROL,
					 1 << gpio);
पूर्ण

अटल पूर्णांक gpio_set_pull_करोwn(काष्ठा wm8350 *wm8350, पूर्णांक gpio, पूर्णांक करोwn)
अणु
	अगर (करोwn)
		वापस wm8350_set_bits(wm8350,
				       WM8350_GPIO_PULL_DOWN_CONTROL,
				       1 << gpio);
	अन्यथा
		वापस wm8350_clear_bits(wm8350,
					 WM8350_GPIO_PULL_DOWN_CONTROL,
					 1 << gpio);
पूर्ण

अटल पूर्णांक gpio_set_polarity(काष्ठा wm8350 *wm8350, पूर्णांक gpio, पूर्णांक pol)
अणु
	अगर (pol == WM8350_GPIO_ACTIVE_HIGH)
		वापस wm8350_set_bits(wm8350,
				       WM8350_GPIO_PIN_POLARITY_TYPE,
				       1 << gpio);
	अन्यथा
		वापस wm8350_clear_bits(wm8350,
					 WM8350_GPIO_PIN_POLARITY_TYPE,
					 1 << gpio);
पूर्ण

अटल पूर्णांक gpio_set_invert(काष्ठा wm8350 *wm8350, पूर्णांक gpio, पूर्णांक invert)
अणु
	अगर (invert == WM8350_GPIO_INVERT_ON)
		वापस wm8350_set_bits(wm8350, WM8350_GPIO_INT_MODE, 1 << gpio);
	अन्यथा
		वापस wm8350_clear_bits(wm8350,
					 WM8350_GPIO_INT_MODE, 1 << gpio);
पूर्ण

पूर्णांक wm8350_gpio_config(काष्ठा wm8350 *wm8350, पूर्णांक gpio, पूर्णांक dir, पूर्णांक func,
		       पूर्णांक pol, पूर्णांक pull, पूर्णांक invert, पूर्णांक debounce)
अणु
	/* make sure we never pull up and करोwn at the same समय */
	अगर (pull == WM8350_GPIO_PULL_NONE) अणु
		अगर (gpio_set_pull_up(wm8350, gpio, 0))
			जाओ err;
		अगर (gpio_set_pull_करोwn(wm8350, gpio, 0))
			जाओ err;
	पूर्ण अन्यथा अगर (pull == WM8350_GPIO_PULL_UP) अणु
		अगर (gpio_set_pull_करोwn(wm8350, gpio, 0))
			जाओ err;
		अगर (gpio_set_pull_up(wm8350, gpio, 1))
			जाओ err;
	पूर्ण अन्यथा अगर (pull == WM8350_GPIO_PULL_DOWN) अणु
		अगर (gpio_set_pull_up(wm8350, gpio, 0))
			जाओ err;
		अगर (gpio_set_pull_करोwn(wm8350, gpio, 1))
			जाओ err;
	पूर्ण

	अगर (gpio_set_invert(wm8350, gpio, invert))
		जाओ err;
	अगर (gpio_set_polarity(wm8350, gpio, pol))
		जाओ err;
	अगर (wm8350_gpio_set_debounce(wm8350, gpio, debounce))
		जाओ err;
	अगर (gpio_set_dir(wm8350, gpio, dir))
		जाओ err;
	वापस gpio_set_func(wm8350, gpio, func);

err:
	वापस -EIO;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_gpio_config);
