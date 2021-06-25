<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MAX1600 PCMCIA घातer चयन library
 *
 * Copyright (C) 2016 Russell King
 */
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>
#समावेश "max1600.h"

अटल स्थिर अक्षर *max1600_gpio_name[2][MAX1600_GPIO_MAX] = अणु
	अणु "a0vcc", "a1vcc", "a0vpp", "a1vpp" पूर्ण,
	अणु "b0vcc", "b1vcc", "b0vpp", "b1vpp" पूर्ण,
पूर्ण;

पूर्णांक max1600_init(काष्ठा device *dev, काष्ठा max1600 **ptr,
	अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक code)
अणु
	काष्ठा max1600 *m;
	पूर्णांक chan;
	पूर्णांक i;

	चयन (channel) अणु
	हाल MAX1600_CHAN_A:
		chan = 0;
		अवरोध;
	हाल MAX1600_CHAN_B:
		chan = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (code != MAX1600_CODE_LOW && code != MAX1600_CODE_HIGH)
		वापस -EINVAL;

	m = devm_kzalloc(dev, माप(*m), GFP_KERNEL);
	अगर (!m)
		वापस -ENOMEM;

	m->dev = dev;
	m->code = code;

	क्रम (i = 0; i < MAX1600_GPIO_MAX; i++) अणु
		स्थिर अक्षर *name;

		name = max1600_gpio_name[chan][i];
		अगर (i != MAX1600_GPIO_0VPP) अणु
			m->gpio[i] = devm_gpiod_get(dev, name, GPIOD_OUT_LOW);
		पूर्ण अन्यथा अणु
			m->gpio[i] = devm_gpiod_get_optional(dev, name,
							     GPIOD_OUT_LOW);
			अगर (!m->gpio[i])
				अवरोध;
		पूर्ण
		अगर (IS_ERR(m->gpio[i]))
			वापस PTR_ERR(m->gpio[i]);
	पूर्ण

	*ptr = m;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max1600_init);

पूर्णांक max1600_configure(काष्ठा max1600 *m, अचिन्हित पूर्णांक vcc, अचिन्हित पूर्णांक vpp)
अणु
	DECLARE_BITMAP(values, MAX1600_GPIO_MAX) = अणु 0, पूर्ण;
	पूर्णांक n = MAX1600_GPIO_0VPP;

	अगर (m->gpio[MAX1600_GPIO_0VPP]) अणु
		अगर (vpp == 0) अणु
			__assign_bit(MAX1600_GPIO_0VPP, values, 0);
			__assign_bit(MAX1600_GPIO_1VPP, values, 0);
		पूर्ण अन्यथा अगर (vpp == 120) अणु
			__assign_bit(MAX1600_GPIO_0VPP, values, 0);
			__assign_bit(MAX1600_GPIO_1VPP, values, 1);
		पूर्ण अन्यथा अगर (vpp == vcc) अणु
			__assign_bit(MAX1600_GPIO_0VPP, values, 1);
			__assign_bit(MAX1600_GPIO_1VPP, values, 0);
		पूर्ण अन्यथा अणु
			dev_err(m->dev, "unrecognised Vpp %u.%uV\n",
				vpp / 10, vpp % 10);
			वापस -EINVAL;
		पूर्ण
		n = MAX1600_GPIO_MAX;
	पूर्ण अन्यथा अगर (vpp != vcc && vpp != 0) अणु
		dev_err(m->dev, "no VPP control\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vcc == 0) अणु
		__assign_bit(MAX1600_GPIO_0VCC, values, 0);
		__assign_bit(MAX1600_GPIO_1VCC, values, 0);
	पूर्ण अन्यथा अगर (vcc == 33) अणु /* VY */
		__assign_bit(MAX1600_GPIO_0VCC, values, 1);
		__assign_bit(MAX1600_GPIO_1VCC, values, 0);
	पूर्ण अन्यथा अगर (vcc == 50) अणु /* VX */
		__assign_bit(MAX1600_GPIO_0VCC, values, 0);
		__assign_bit(MAX1600_GPIO_1VCC, values, 1);
	पूर्ण अन्यथा अणु
		dev_err(m->dev, "unrecognised Vcc %u.%uV\n",
			vcc / 10, vcc % 10);
		वापस -EINVAL;
	पूर्ण

	अगर (m->code == MAX1600_CODE_HIGH) अणु
		/*
		 * Cirrus mode appears to be the same as Intel mode,
		 * except the VCC pins are inverted.
		 */
		__change_bit(MAX1600_GPIO_0VCC, values);
		__change_bit(MAX1600_GPIO_1VCC, values);
	पूर्ण

	वापस gpiod_set_array_value_cansleep(n, m->gpio, शून्य, values);
पूर्ण
EXPORT_SYMBOL_GPL(max1600_configure);

MODULE_LICENSE("GPL v2");
