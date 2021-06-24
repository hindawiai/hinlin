<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/pxa/pxa_cm_x255.c
 *
 * Compulab Ltd., 2003, 2007, 2008
 * Mike Rapoport <mike@compulab.co.il>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/export.h>

#समावेश "soc_common.h"

#घोषणा GPIO_PCMCIA_SKTSEL	(54)
#घोषणा GPIO_PCMCIA_S0_CD_VALID	(16)
#घोषणा GPIO_PCMCIA_S1_CD_VALID	(17)
#घोषणा GPIO_PCMCIA_S0_RDYINT	(6)
#घोषणा GPIO_PCMCIA_S1_RDYINT	(8)
#घोषणा GPIO_PCMCIA_RESET	(9)

अटल पूर्णांक cmx255_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	पूर्णांक ret = gpio_request(GPIO_PCMCIA_RESET, "PCCard reset");
	अगर (ret)
		वापस ret;
	gpio_direction_output(GPIO_PCMCIA_RESET, 0);

	अगर (skt->nr == 0) अणु
		skt->stat[SOC_STAT_CD].gpio = GPIO_PCMCIA_S0_CD_VALID;
		skt->stat[SOC_STAT_CD].name = "PCMCIA0 CD";
		skt->stat[SOC_STAT_RDY].gpio = GPIO_PCMCIA_S0_RDYINT;
		skt->stat[SOC_STAT_RDY].name = "PCMCIA0 RDY";
	पूर्ण अन्यथा अणु
		skt->stat[SOC_STAT_CD].gpio = GPIO_PCMCIA_S1_CD_VALID;
		skt->stat[SOC_STAT_CD].name = "PCMCIA1 CD";
		skt->stat[SOC_STAT_RDY].gpio = GPIO_PCMCIA_S1_RDYINT;
		skt->stat[SOC_STAT_RDY].name = "PCMCIA1 RDY";
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cmx255_pcmcia_shutकरोwn(काष्ठा soc_pcmcia_socket *skt)
अणु
	gpio_मुक्त(GPIO_PCMCIA_RESET);
पूर्ण


अटल व्योम cmx255_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
				       काष्ठा pcmcia_state *state)
अणु
	state->vs_3v  = 0;
	state->vs_Xv  = 0;
पूर्ण


अटल पूर्णांक cmx255_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
					  स्थिर socket_state_t *state)
अणु
	चयन (skt->nr) अणु
	हाल 0:
		अगर (state->flags & SS_RESET) अणु
			gpio_set_value(GPIO_PCMCIA_SKTSEL, 0);
			udelay(1);
			gpio_set_value(GPIO_PCMCIA_RESET, 1);
			udelay(10);
			gpio_set_value(GPIO_PCMCIA_RESET, 0);
		पूर्ण
		अवरोध;
	हाल 1:
		अगर (state->flags & SS_RESET) अणु
			gpio_set_value(GPIO_PCMCIA_SKTSEL, 1);
			udelay(1);
			gpio_set_value(GPIO_PCMCIA_RESET, 1);
			udelay(10);
			gpio_set_value(GPIO_PCMCIA_RESET, 0);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pcmcia_low_level cmx255_pcmcia_ops __initdata = अणु
	.owner			= THIS_MODULE,
	.hw_init		= cmx255_pcmcia_hw_init,
	.hw_shutकरोwn		= cmx255_pcmcia_shutकरोwn,
	.socket_state		= cmx255_pcmcia_socket_state,
	.configure_socket	= cmx255_pcmcia_configure_socket,
	.nr			= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device *cmx255_pcmcia_device;

पूर्णांक __init cmx255_pcmcia_init(व्योम)
अणु
	पूर्णांक ret;

	cmx255_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);

	अगर (!cmx255_pcmcia_device)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(cmx255_pcmcia_device, &cmx255_pcmcia_ops,
				       माप(cmx255_pcmcia_ops));

	अगर (ret == 0) अणु
		prपूर्णांकk(KERN_INFO "Registering cm-x255 PCMCIA interface.\n");
		ret = platक्रमm_device_add(cmx255_pcmcia_device);
	पूर्ण

	अगर (ret)
		platक्रमm_device_put(cmx255_pcmcia_device);

	वापस ret;
पूर्ण

व्योम __निकास cmx255_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(cmx255_pcmcia_device);
पूर्ण
