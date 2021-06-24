<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/pxa2xx_palmld.c
 *
 * Driver क्रम Palm LअगरeDrive PCMCIA
 *
 * Copyright (C) 2006 Alex Osborne <ato@meshy.org>
 * Copyright (C) 2007-2011 Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/palmld.h>
#समावेश "soc_common.h"

अटल काष्ठा gpio palmld_pcmcia_gpios[] = अणु
	अणु GPIO_NR_PALMLD_PCMCIA_POWER,	GPIOF_INIT_LOW,	"PCMCIA Power" पूर्ण,
	अणु GPIO_NR_PALMLD_PCMCIA_RESET,	GPIOF_INIT_HIGH,"PCMCIA Reset" पूर्ण,
पूर्ण;

अटल पूर्णांक palmld_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	पूर्णांक ret;

	ret = gpio_request_array(palmld_pcmcia_gpios,
				ARRAY_SIZE(palmld_pcmcia_gpios));

	skt->stat[SOC_STAT_RDY].gpio = GPIO_NR_PALMLD_PCMCIA_READY;
	skt->stat[SOC_STAT_RDY].name = "PCMCIA Ready";

	वापस ret;
पूर्ण

अटल व्योम palmld_pcmcia_hw_shutकरोwn(काष्ठा soc_pcmcia_socket *skt)
अणु
	gpio_मुक्त_array(palmld_pcmcia_gpios, ARRAY_SIZE(palmld_pcmcia_gpios));
पूर्ण

अटल व्योम palmld_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
					काष्ठा pcmcia_state *state)
अणु
	state->detect = 1; /* always inserted */
	state->vs_3v  = 1;
	state->vs_Xv  = 0;
पूर्ण

अटल पूर्णांक palmld_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
					स्थिर socket_state_t *state)
अणु
	gpio_set_value(GPIO_NR_PALMLD_PCMCIA_POWER, 1);
	gpio_set_value(GPIO_NR_PALMLD_PCMCIA_RESET,
			!!(state->flags & SS_RESET));

	वापस 0;
पूर्ण

अटल काष्ठा pcmcia_low_level palmld_pcmcia_ops = अणु
	.owner			= THIS_MODULE,

	.first			= 1,
	.nr			= 1,

	.hw_init		= palmld_pcmcia_hw_init,
	.hw_shutकरोwn		= palmld_pcmcia_hw_shutकरोwn,

	.socket_state		= palmld_pcmcia_socket_state,
	.configure_socket	= palmld_pcmcia_configure_socket,
पूर्ण;

अटल काष्ठा platक्रमm_device *palmld_pcmcia_device;

अटल पूर्णांक __init palmld_pcmcia_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_palmld())
		वापस -ENODEV;

	palmld_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);
	अगर (!palmld_pcmcia_device)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(palmld_pcmcia_device, &palmld_pcmcia_ops,
					माप(palmld_pcmcia_ops));

	अगर (!ret)
		ret = platक्रमm_device_add(palmld_pcmcia_device);

	अगर (ret)
		platक्रमm_device_put(palmld_pcmcia_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास palmld_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(palmld_pcmcia_device);
पूर्ण

module_init(palmld_pcmcia_init);
module_निकास(palmld_pcmcia_निकास);

MODULE_AUTHOR("Alex Osborne <ato@meshy.org>,"
	    " Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("PCMCIA support for Palm LifeDrive");
MODULE_ALIAS("platform:pxa2xx-pcmcia");
MODULE_LICENSE("GPL");
