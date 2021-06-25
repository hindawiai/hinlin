<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/pcmcia/sa1100_jornada720.c
 *
 * Jornada720 PCMCIA specअगरic routines
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "sa1111_generic.h"

/*
 * Socket 0 घातer: GPIO A0
 * Socket 0 3V: GPIO A2
 * Socket 1 घातer: GPIO A1 & GPIO A3
 * Socket 1 3V: GPIO A3
 * Does Socket 1 3V actually करो anything?
 */
क्रमागत अणु
	J720_GPIO_PWR,
	J720_GPIO_3V,
	J720_GPIO_MAX,
पूर्ण;
काष्ठा jornada720_data अणु
	काष्ठा gpio_desc *gpio[J720_GPIO_MAX];
पूर्ण;

अटल पूर्णांक jornada720_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	काष्ठा device *dev = skt->socket.dev.parent;
	काष्ठा jornada720_data *j;

	j = devm_kzalloc(dev, माप(*j), GFP_KERNEL);
	अगर (!j)
		वापस -ENOMEM;

	j->gpio[J720_GPIO_PWR] = devm_gpiod_get(dev, skt->nr ? "s1-power" :
						"s0-power", GPIOD_OUT_LOW);
	अगर (IS_ERR(j->gpio[J720_GPIO_PWR]))
		वापस PTR_ERR(j->gpio[J720_GPIO_PWR]);

	j->gpio[J720_GPIO_3V] = devm_gpiod_get(dev, skt->nr ? "s1-3v" :
					       "s0-3v", GPIOD_OUT_LOW);
	अगर (IS_ERR(j->gpio[J720_GPIO_3V]))
		वापस PTR_ERR(j->gpio[J720_GPIO_3V]);

	skt->driver_data = j;

	वापस 0;
पूर्ण

अटल पूर्णांक
jornada720_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt, स्थिर socket_state_t *state)
अणु
	काष्ठा jornada720_data *j = skt->driver_data;
	DECLARE_BITMAP(values, J720_GPIO_MAX) = अणु 0, पूर्ण;
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO "%s(): config socket %d vcc %d vpp %d\n", __func__,
		skt->nr, state->Vcc, state->Vpp);

	चयन (skt->nr) अणु
	हाल 0:
		चयन (state->Vcc) अणु
		शेष:
		हाल  0:
			__assign_bit(J720_GPIO_PWR, values, 0);
			__assign_bit(J720_GPIO_3V, values, 0);
			अवरोध;
		हाल 33:
			__assign_bit(J720_GPIO_PWR, values, 1);
			__assign_bit(J720_GPIO_3V, values, 1);
			अवरोध;
		हाल 50:
			__assign_bit(J720_GPIO_PWR, values, 1);
			__assign_bit(J720_GPIO_3V, values, 0);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 1:
		चयन (state->Vcc) अणु
		शेष:
		हाल 0:
			__assign_bit(J720_GPIO_PWR, values, 0);
			__assign_bit(J720_GPIO_3V, values, 0);
			अवरोध;
		हाल 33:
		हाल 50:
			__assign_bit(J720_GPIO_PWR, values, 1);
			__assign_bit(J720_GPIO_3V, values, 1);
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		वापस -1;
	पूर्ण

	अगर (state->Vpp != state->Vcc && state->Vpp != 0) अणु
		prपूर्णांकk(KERN_ERR "%s(): slot cannot support VPP %u\n",
			__func__, state->Vpp);
		वापस -EPERM;
	पूर्ण

	ret = sa1111_pcmcia_configure_socket(skt, state);
	अगर (ret == 0)
		ret = gpiod_set_array_value_cansleep(J720_GPIO_MAX, j->gpio,
						     शून्य, values);

	वापस ret;
पूर्ण

अटल काष्ठा pcmcia_low_level jornada720_pcmcia_ops = अणु
	.owner			= THIS_MODULE,
	.hw_init		= jornada720_pcmcia_hw_init,
	.configure_socket	= jornada720_pcmcia_configure_socket,
	.first			= 0,
	.nr			= 2,
पूर्ण;

पूर्णांक pcmcia_jornada720_init(काष्ठा sa1111_dev *sadev)
अणु
	/* Fixme: why messing around with SA11x0's GPIO1? */
	GRER |= 0x00000002;

	sa11xx_drv_pcmcia_ops(&jornada720_pcmcia_ops);
	वापस sa1111_pcmcia_add(sadev, &jornada720_pcmcia_ops,
				 sa11xx_drv_pcmcia_add_one);
पूर्ण
