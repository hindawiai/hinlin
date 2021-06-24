<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/pxa2xx_stargate2.c
 *
 * Stargate 2 PCMCIA specअगरic routines.
 *
 * Created:	December 6, 2005
 * Author:	Ed C. Epp
 * Copyright:	Intel Corp 2005
 *              Jonathan Cameron <jic23@cam.ac.uk> 2009
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>

#समावेश <pcmcia/ss.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "soc_common.h"

#घोषणा SG2_S0_POWER_CTL	108
#घोषणा SG2_S0_GPIO_RESET	82
#घोषणा SG2_S0_GPIO_DETECT	53
#घोषणा SG2_S0_GPIO_READY	81

अटल काष्ठा gpio sg2_pcmcia_gpios[] = अणु
	अणु SG2_S0_GPIO_RESET, GPIOF_OUT_INIT_HIGH, "PCMCIA Reset" पूर्ण,
	अणु SG2_S0_POWER_CTL, GPIOF_OUT_INIT_HIGH, "PCMCIA Power Ctrl" पूर्ण,
पूर्ण;

अटल पूर्णांक sg2_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	skt->stat[SOC_STAT_CD].gpio = SG2_S0_GPIO_DETECT;
	skt->stat[SOC_STAT_CD].name = "PCMCIA0 CD";
	skt->stat[SOC_STAT_RDY].gpio = SG2_S0_GPIO_READY;
	skt->stat[SOC_STAT_RDY].name = "PCMCIA0 RDY";
	वापस 0;
पूर्ण

अटल व्योम sg2_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
				    काष्ठा pcmcia_state *state)
अणु
	state->bvd1   = 0; /* not available - battery detect on card */
	state->bvd2   = 0; /* not available */
	state->vs_3v  = 1; /* not available - voltage detect क्रम card */
	state->vs_Xv  = 0; /* not available */
पूर्ण

अटल पूर्णांक sg2_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
				       स्थिर socket_state_t *state)
अणु
	/* Enable card घातer */
	चयन (state->Vcc) अणु
	हाल 0:
		/* sets घातer ctl रेजिस्टर high */
		gpio_set_value(SG2_S0_POWER_CTL, 1);
		अवरोध;
	हाल 33:
	हाल 50:
		/* sets घातer control रेजिस्टर low (clear) */
		gpio_set_value(SG2_S0_POWER_CTL, 0);
		msleep(100);
		अवरोध;
	शेष:
		pr_err("%s(): bad Vcc %u\n",
		       __func__, state->Vcc);
		वापस -1;
	पूर्ण

	/* reset */
	gpio_set_value(SG2_S0_GPIO_RESET, !!(state->flags & SS_RESET));

	वापस 0;
पूर्ण

अटल काष्ठा pcmcia_low_level sg2_pcmcia_ops __initdata = अणु
	.owner			= THIS_MODULE,
	.hw_init		= sg2_pcmcia_hw_init,
	.socket_state		= sg2_pcmcia_socket_state,
	.configure_socket	= sg2_pcmcia_configure_socket,
	.nr			= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device *sg2_pcmcia_device;

अटल पूर्णांक __init sg2_pcmcia_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_stargate2())
		वापस -ENODEV;

	sg2_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);
	अगर (!sg2_pcmcia_device)
		वापस -ENOMEM;

	ret = gpio_request_array(sg2_pcmcia_gpios, ARRAY_SIZE(sg2_pcmcia_gpios));
	अगर (ret)
		जाओ error_put_platक्रमm_device;

	ret = platक्रमm_device_add_data(sg2_pcmcia_device,
				       &sg2_pcmcia_ops,
				       माप(sg2_pcmcia_ops));
	अगर (ret)
		जाओ error_मुक्त_gpios;

	ret = platक्रमm_device_add(sg2_pcmcia_device);
	अगर (ret)
		जाओ error_मुक्त_gpios;

	वापस 0;
error_मुक्त_gpios:
	gpio_मुक्त_array(sg2_pcmcia_gpios, ARRAY_SIZE(sg2_pcmcia_gpios));
error_put_platक्रमm_device:
	platक्रमm_device_put(sg2_pcmcia_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास sg2_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(sg2_pcmcia_device);
	gpio_मुक्त_array(sg2_pcmcia_gpios, ARRAY_SIZE(sg2_pcmcia_gpios));
पूर्ण

fs_initcall(sg2_pcmcia_init);
module_निकास(sg2_pcmcia_निकास);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa2xx-pcmcia");
