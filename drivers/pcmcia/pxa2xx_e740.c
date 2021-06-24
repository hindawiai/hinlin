<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Toshiba e740 PCMCIA specअगरic routines.
 *
 * (c) 2004 Ian Molton <spyro@f2s.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <mach/eseries-gpपन.स>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "soc_common.h"

अटल पूर्णांक e740_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	अगर (skt->nr == 0) अणु
		skt->stat[SOC_STAT_CD].gpio = GPIO_E740_PCMCIA_CD0;
		skt->stat[SOC_STAT_CD].name = "CF card detect";
		skt->stat[SOC_STAT_RDY].gpio = GPIO_E740_PCMCIA_RDY0;
		skt->stat[SOC_STAT_RDY].name = "CF ready";
	पूर्ण अन्यथा अणु
		skt->stat[SOC_STAT_CD].gpio = GPIO_E740_PCMCIA_CD1;
		skt->stat[SOC_STAT_CD].name = "Wifi switch";
		skt->stat[SOC_STAT_RDY].gpio = GPIO_E740_PCMCIA_RDY1;
		skt->stat[SOC_STAT_RDY].name = "Wifi ready";
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम e740_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
					काष्ठा pcmcia_state *state)
अणु
	state->vs_3v  = 1;
	state->vs_Xv  = 0;
पूर्ण

अटल पूर्णांक e740_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
					स्थिर socket_state_t *state)
अणु
	अगर (state->flags & SS_RESET) अणु
		अगर (skt->nr == 0)
			gpio_set_value(GPIO_E740_PCMCIA_RST0, 1);
		अन्यथा
			gpio_set_value(GPIO_E740_PCMCIA_RST1, 1);
	पूर्ण अन्यथा अणु
		अगर (skt->nr == 0)
			gpio_set_value(GPIO_E740_PCMCIA_RST0, 0);
		अन्यथा
			gpio_set_value(GPIO_E740_PCMCIA_RST1, 0);
	पूर्ण

	चयन (state->Vcc) अणु
	हाल 0:	/* Socket off */
		अगर (skt->nr == 0)
			gpio_set_value(GPIO_E740_PCMCIA_PWR0, 0);
		अन्यथा
			gpio_set_value(GPIO_E740_PCMCIA_PWR1, 1);
		अवरोध;
	हाल 50:
	हाल 33: /* socket on */
		अगर (skt->nr == 0)
			gpio_set_value(GPIO_E740_PCMCIA_PWR0, 1);
		अन्यथा
			gpio_set_value(GPIO_E740_PCMCIA_PWR1, 0);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "e740_cs: Unsupported Vcc: %d\n", state->Vcc);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pcmcia_low_level e740_pcmcia_ops = अणु
	.owner            = THIS_MODULE,
	.hw_init          = e740_pcmcia_hw_init,
	.socket_state     = e740_pcmcia_socket_state,
	.configure_socket = e740_pcmcia_configure_socket,
	.nr               = 2,
पूर्ण;

अटल काष्ठा platक्रमm_device *e740_pcmcia_device;

अटल पूर्णांक __init e740_pcmcia_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_e740())
		वापस -ENODEV;

	e740_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);
	अगर (!e740_pcmcia_device)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(e740_pcmcia_device, &e740_pcmcia_ops,
					माप(e740_pcmcia_ops));

	अगर (!ret)
		ret = platक्रमm_device_add(e740_pcmcia_device);

	अगर (ret)
		platक्रमm_device_put(e740_pcmcia_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास e740_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(e740_pcmcia_device);
पूर्ण

module_init(e740_pcmcia_init);
module_निकास(e740_pcmcia_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ian Molton <spyro@f2s.com>");
MODULE_ALIAS("platform:pxa2xx-pcmcia");
MODULE_DESCRIPTION("e740 PCMCIA platform support");
