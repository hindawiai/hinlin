<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/pxa2xx_palmtc.c
 *
 * Driver क्रम Palm Tungsten|C PCMCIA
 *
 * Copyright (C) 2008 Alex Osborne <ato@meshy.org>
 * Copyright (C) 2009-2011 Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/palmtc.h>
#समावेश "soc_common.h"

अटल काष्ठा gpio palmtc_pcmcia_gpios[] = अणु
	अणु GPIO_NR_PALMTC_PCMCIA_POWER1,	GPIOF_INIT_LOW,	"PCMCIA Power 1" पूर्ण,
	अणु GPIO_NR_PALMTC_PCMCIA_POWER2,	GPIOF_INIT_LOW,	"PCMCIA Power 2" पूर्ण,
	अणु GPIO_NR_PALMTC_PCMCIA_POWER3,	GPIOF_INIT_LOW,	"PCMCIA Power 3" पूर्ण,
	अणु GPIO_NR_PALMTC_PCMCIA_RESET,	GPIOF_INIT_HIGH,"PCMCIA Reset" पूर्ण,
	अणु GPIO_NR_PALMTC_PCMCIA_PWRREADY, GPIOF_IN,	"PCMCIA Power Ready" पूर्ण,
पूर्ण;

अटल पूर्णांक palmtc_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	पूर्णांक ret;

	ret = gpio_request_array(palmtc_pcmcia_gpios,
				ARRAY_SIZE(palmtc_pcmcia_gpios));

	skt->stat[SOC_STAT_RDY].gpio = GPIO_NR_PALMTC_PCMCIA_READY;
	skt->stat[SOC_STAT_RDY].name = "PCMCIA Ready";

	वापस ret;
पूर्ण

अटल व्योम palmtc_pcmcia_hw_shutकरोwn(काष्ठा soc_pcmcia_socket *skt)
अणु
	gpio_मुक्त_array(palmtc_pcmcia_gpios, ARRAY_SIZE(palmtc_pcmcia_gpios));
पूर्ण

अटल व्योम palmtc_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
					काष्ठा pcmcia_state *state)
अणु
	state->detect = 1; /* always inserted */
	state->vs_3v  = 1;
	state->vs_Xv  = 0;
पूर्ण

अटल पूर्णांक palmtc_wअगरi_घातerकरोwn(व्योम)
अणु
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_RESET, 1);
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_POWER2, 0);
	mdelay(40);
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_POWER1, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक palmtc_wअगरi_घातerup(व्योम)
अणु
	पूर्णांक समयout = 50;

	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_POWER3, 1);
	mdelay(50);

	/* Power up the card, 1.8V first, after a जबतक 3.3V */
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_POWER1, 1);
	mdelay(100);
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_POWER2, 1);

	/* Wait till the card is पढ़ोy */
	जबतक (!gpio_get_value(GPIO_NR_PALMTC_PCMCIA_PWRREADY) &&
		समयout) अणु
		mdelay(1);
		समयout--;
	पूर्ण

	/* Power करोwn the WiFi in हाल of error */
	अगर (!समयout) अणु
		palmtc_wअगरi_घातerकरोwn();
		वापस 1;
	पूर्ण

	/* Reset the card */
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_RESET, 1);
	mdelay(20);
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_RESET, 0);
	mdelay(25);

	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_POWER3, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक palmtc_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
					स्थिर socket_state_t *state)
अणु
	पूर्णांक ret = 1;

	अगर (state->Vcc == 0)
		ret = palmtc_wअगरi_घातerकरोwn();
	अन्यथा अगर (state->Vcc == 33)
		ret = palmtc_wअगरi_घातerup();

	वापस ret;
पूर्ण

अटल काष्ठा pcmcia_low_level palmtc_pcmcia_ops = अणु
	.owner			= THIS_MODULE,

	.first			= 0,
	.nr			= 1,

	.hw_init		= palmtc_pcmcia_hw_init,
	.hw_shutकरोwn		= palmtc_pcmcia_hw_shutकरोwn,

	.socket_state		= palmtc_pcmcia_socket_state,
	.configure_socket	= palmtc_pcmcia_configure_socket,
पूर्ण;

अटल काष्ठा platक्रमm_device *palmtc_pcmcia_device;

अटल पूर्णांक __init palmtc_pcmcia_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_palmtc())
		वापस -ENODEV;

	palmtc_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);
	अगर (!palmtc_pcmcia_device)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(palmtc_pcmcia_device, &palmtc_pcmcia_ops,
					माप(palmtc_pcmcia_ops));

	अगर (!ret)
		ret = platक्रमm_device_add(palmtc_pcmcia_device);

	अगर (ret)
		platक्रमm_device_put(palmtc_pcmcia_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास palmtc_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(palmtc_pcmcia_device);
पूर्ण

module_init(palmtc_pcmcia_init);
module_निकास(palmtc_pcmcia_निकास);

MODULE_AUTHOR("Alex Osborne <ato@meshy.org>,"
	    " Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("PCMCIA support for Palm Tungsten|C");
MODULE_ALIAS("platform:pxa2xx-pcmcia");
MODULE_LICENSE("GPL");
