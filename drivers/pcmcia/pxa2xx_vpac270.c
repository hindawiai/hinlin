<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/pxa2xx_vpac270.c
 *
 * Driver क्रम Voipac PXA270 PCMCIA and CF sockets
 *
 * Copyright (C) 2010-2011 Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mach-types.h>

#समावेश <mach/vpac270.h>

#समावेश "soc_common.h"

अटल काष्ठा gpio vpac270_pcmcia_gpios[] = अणु
	अणु GPIO107_VPAC270_PCMCIA_PPEN,	GPIOF_INIT_LOW,	"PCMCIA PPEN" पूर्ण,
	अणु GPIO11_VPAC270_PCMCIA_RESET,	GPIOF_INIT_LOW,	"PCMCIA Reset" पूर्ण,
पूर्ण;

अटल काष्ठा gpio vpac270_cf_gpios[] = अणु
	अणु GPIO16_VPAC270_CF_RESET,	GPIOF_INIT_LOW,	"CF Reset" पूर्ण,
पूर्ण;

अटल पूर्णांक vpac270_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	पूर्णांक ret;

	अगर (skt->nr == 0) अणु
		ret = gpio_request_array(vpac270_pcmcia_gpios,
				ARRAY_SIZE(vpac270_pcmcia_gpios));

		skt->stat[SOC_STAT_CD].gpio = GPIO84_VPAC270_PCMCIA_CD;
		skt->stat[SOC_STAT_CD].name = "PCMCIA CD";
		skt->stat[SOC_STAT_RDY].gpio = GPIO35_VPAC270_PCMCIA_RDY;
		skt->stat[SOC_STAT_RDY].name = "PCMCIA Ready";
	पूर्ण अन्यथा अणु
		ret = gpio_request_array(vpac270_cf_gpios,
				ARRAY_SIZE(vpac270_cf_gpios));

		skt->stat[SOC_STAT_CD].gpio = GPIO17_VPAC270_CF_CD;
		skt->stat[SOC_STAT_CD].name = "CF CD";
		skt->stat[SOC_STAT_RDY].gpio = GPIO12_VPAC270_CF_RDY;
		skt->stat[SOC_STAT_RDY].name = "CF Ready";
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vpac270_pcmcia_hw_shutकरोwn(काष्ठा soc_pcmcia_socket *skt)
अणु
	अगर (skt->nr == 0)
		gpio_मुक्त_array(vpac270_pcmcia_gpios,
					ARRAY_SIZE(vpac270_pcmcia_gpios));
	अन्यथा
		gpio_मुक्त_array(vpac270_cf_gpios,
					ARRAY_SIZE(vpac270_cf_gpios));
पूर्ण

अटल व्योम vpac270_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
					काष्ठा pcmcia_state *state)
अणु
	state->vs_3v  = 1;
	state->vs_Xv  = 0;
पूर्ण

अटल पूर्णांक
vpac270_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
				स्थिर socket_state_t *state)
अणु
	अगर (skt->nr == 0) अणु
		gpio_set_value(GPIO11_VPAC270_PCMCIA_RESET,
			(state->flags & SS_RESET));
		gpio_set_value(GPIO107_VPAC270_PCMCIA_PPEN,
			!(state->Vcc == 33 || state->Vcc == 50));
	पूर्ण अन्यथा अणु
		gpio_set_value(GPIO16_VPAC270_CF_RESET,
			(state->flags & SS_RESET));
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pcmcia_low_level vpac270_pcmcia_ops = अणु
	.owner			= THIS_MODULE,

	.first			= 0,
	.nr			= 2,

	.hw_init		= vpac270_pcmcia_hw_init,
	.hw_shutकरोwn		= vpac270_pcmcia_hw_shutकरोwn,

	.socket_state		= vpac270_pcmcia_socket_state,
	.configure_socket	= vpac270_pcmcia_configure_socket,
पूर्ण;

अटल काष्ठा platक्रमm_device *vpac270_pcmcia_device;

अटल पूर्णांक __init vpac270_pcmcia_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_vpac270())
		वापस -ENODEV;

	vpac270_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);
	अगर (!vpac270_pcmcia_device)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(vpac270_pcmcia_device,
		&vpac270_pcmcia_ops, माप(vpac270_pcmcia_ops));

	अगर (!ret)
		ret = platक्रमm_device_add(vpac270_pcmcia_device);

	अगर (ret)
		platक्रमm_device_put(vpac270_pcmcia_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास vpac270_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(vpac270_pcmcia_device);
पूर्ण

module_init(vpac270_pcmcia_init);
module_निकास(vpac270_pcmcia_निकास);

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("PCMCIA support for Voipac PXA270");
MODULE_ALIAS("platform:pxa2xx-pcmcia");
MODULE_LICENSE("GPL");
