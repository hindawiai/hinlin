<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/pxa2xx_palmtx.c
 *
 * Driver क्रम Palm T|X PCMCIA
 *
 * Copyright (C) 2007-2011 Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/palmtx.h>
#समावेश "soc_common.h"

अटल काष्ठा gpio palmtx_pcmcia_gpios[] = अणु
	अणु GPIO_NR_PALMTX_PCMCIA_POWER1,	GPIOF_INIT_LOW,	"PCMCIA Power 1" पूर्ण,
	अणु GPIO_NR_PALMTX_PCMCIA_POWER2,	GPIOF_INIT_LOW,	"PCMCIA Power 2" पूर्ण,
	अणु GPIO_NR_PALMTX_PCMCIA_RESET,	GPIOF_INIT_HIGH,"PCMCIA Reset" पूर्ण,
पूर्ण;

अटल पूर्णांक palmtx_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	पूर्णांक ret;

	ret = gpio_request_array(palmtx_pcmcia_gpios,
				ARRAY_SIZE(palmtx_pcmcia_gpios));

	skt->stat[SOC_STAT_RDY].gpio = GPIO_NR_PALMTX_PCMCIA_READY;
	skt->stat[SOC_STAT_RDY].name = "PCMCIA Ready";

	वापस ret;
पूर्ण

अटल व्योम palmtx_pcmcia_hw_shutकरोwn(काष्ठा soc_pcmcia_socket *skt)
अणु
	gpio_मुक्त_array(palmtx_pcmcia_gpios, ARRAY_SIZE(palmtx_pcmcia_gpios));
पूर्ण

अटल व्योम palmtx_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
					काष्ठा pcmcia_state *state)
अणु
	state->detect = 1; /* always inserted */
	state->vs_3v  = 1;
	state->vs_Xv  = 0;
पूर्ण

अटल पूर्णांक
palmtx_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
				स्थिर socket_state_t *state)
अणु
	gpio_set_value(GPIO_NR_PALMTX_PCMCIA_POWER1, 1);
	gpio_set_value(GPIO_NR_PALMTX_PCMCIA_POWER2, 1);
	gpio_set_value(GPIO_NR_PALMTX_PCMCIA_RESET,
			!!(state->flags & SS_RESET));

	वापस 0;
पूर्ण

अटल काष्ठा pcmcia_low_level palmtx_pcmcia_ops = अणु
	.owner			= THIS_MODULE,

	.first			= 0,
	.nr			= 1,

	.hw_init		= palmtx_pcmcia_hw_init,
	.hw_shutकरोwn		= palmtx_pcmcia_hw_shutकरोwn,

	.socket_state		= palmtx_pcmcia_socket_state,
	.configure_socket	= palmtx_pcmcia_configure_socket,
पूर्ण;

अटल काष्ठा platक्रमm_device *palmtx_pcmcia_device;

अटल पूर्णांक __init palmtx_pcmcia_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_palmtx())
		वापस -ENODEV;

	palmtx_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);
	अगर (!palmtx_pcmcia_device)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(palmtx_pcmcia_device, &palmtx_pcmcia_ops,
					माप(palmtx_pcmcia_ops));

	अगर (!ret)
		ret = platक्रमm_device_add(palmtx_pcmcia_device);

	अगर (ret)
		platक्रमm_device_put(palmtx_pcmcia_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास palmtx_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(palmtx_pcmcia_device);
पूर्ण

module_init(palmtx_pcmcia_init);
module_निकास(palmtx_pcmcia_निकास);

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("PCMCIA support for Palm T|X");
MODULE_ALIAS("platform:pxa2xx-pcmcia");
MODULE_LICENSE("GPL");
