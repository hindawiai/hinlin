<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/pcmcia/sa1100_h3600.c
 *
 * PCMCIA implementation routines क्रम H3600
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/h3xxx.h>

#समावेश "sa1100_generic.h"

अटल पूर्णांक h3600_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	पूर्णांक err;

	skt->stat[SOC_STAT_CD].name = skt->nr ? "pcmcia1-detect" : "pcmcia0-detect";
	skt->stat[SOC_STAT_RDY].name = skt->nr ? "pcmcia1-ready" : "pcmcia0-ready";

	err = soc_pcmcia_request_gpiods(skt);
	अगर (err)
		वापस err;

	चयन (skt->nr) अणु
	हाल 0:
		err = gpio_request(H3XXX_EGPIO_OPT_NVRAM_ON, "OPT NVRAM ON");
		अगर (err)
			जाओ err01;
		err = gpio_direction_output(H3XXX_EGPIO_OPT_NVRAM_ON, 0);
		अगर (err)
			जाओ err03;
		err = gpio_request(H3XXX_EGPIO_OPT_ON, "OPT ON");
		अगर (err)
			जाओ err03;
		err = gpio_direction_output(H3XXX_EGPIO_OPT_ON, 0);
		अगर (err)
			जाओ err04;
		err = gpio_request(H3XXX_EGPIO_OPT_RESET, "OPT RESET");
		अगर (err)
			जाओ err04;
		err = gpio_direction_output(H3XXX_EGPIO_OPT_RESET, 0);
		अगर (err)
			जाओ err05;
		err = gpio_request(H3XXX_EGPIO_CARD_RESET, "PCMCIA CARD RESET");
		अगर (err)
			जाओ err05;
		err = gpio_direction_output(H3XXX_EGPIO_CARD_RESET, 0);
		अगर (err)
			जाओ err06;
		अवरोध;
	हाल 1:
		अवरोध;
	पूर्ण
	वापस 0;

err06:	gpio_मुक्त(H3XXX_EGPIO_CARD_RESET);
err05:	gpio_मुक्त(H3XXX_EGPIO_OPT_RESET);
err04:	gpio_मुक्त(H3XXX_EGPIO_OPT_ON);
err03:	gpio_मुक्त(H3XXX_EGPIO_OPT_NVRAM_ON);
err01:	gpio_मुक्त(H3XXX_GPIO_PCMCIA_IRQ0);
	वापस err;
पूर्ण

अटल व्योम h3600_pcmcia_hw_shutकरोwn(काष्ठा soc_pcmcia_socket *skt)
अणु
	चयन (skt->nr) अणु
	हाल 0:
		/* Disable CF bus: */
		gpio_set_value(H3XXX_EGPIO_OPT_NVRAM_ON, 0);
		gpio_set_value(H3XXX_EGPIO_OPT_ON, 0);
		gpio_set_value(H3XXX_EGPIO_OPT_RESET, 1);

		gpio_मुक्त(H3XXX_EGPIO_CARD_RESET);
		gpio_मुक्त(H3XXX_EGPIO_OPT_RESET);
		gpio_मुक्त(H3XXX_EGPIO_OPT_ON);
		gpio_मुक्त(H3XXX_EGPIO_OPT_NVRAM_ON);
		अवरोध;
	हाल 1:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
h3600_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt, काष्ठा pcmcia_state *state)
अणु
	state->bvd1 = 0;
	state->bvd2 = 0;
	state->vs_3v = 0;
	state->vs_Xv = 0;
पूर्ण

अटल पूर्णांक
h3600_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt, स्थिर socket_state_t *state)
अणु
	अगर (state->Vcc != 0 && state->Vcc != 33 && state->Vcc != 50) अणु
		prपूर्णांकk(KERN_ERR "h3600_pcmcia: unrecognized Vcc %u.%uV\n",
		       state->Vcc / 10, state->Vcc % 10);
		वापस -1;
	पूर्ण

	gpio_set_value(H3XXX_EGPIO_CARD_RESET, !!(state->flags & SS_RESET));

	/* Silently ignore Vpp, output enable, speaker enable. */

	वापस 0;
पूर्ण

अटल व्योम h3600_pcmcia_socket_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	/* Enable CF bus: */
	gpio_set_value(H3XXX_EGPIO_OPT_NVRAM_ON, 1);
	gpio_set_value(H3XXX_EGPIO_OPT_ON, 1);
	gpio_set_value(H3XXX_EGPIO_OPT_RESET, 0);

	msleep(10);
पूर्ण

अटल व्योम h3600_pcmcia_socket_suspend(काष्ठा soc_pcmcia_socket *skt)
अणु
	/*
	 * FIXME:  This करोesn't fit well.  We don't have the mechanism in
	 * the generic PCMCIA layer to deal with the idea of two sockets
	 * on one bus.  We rely on the cs.c behaviour shutting करोwn
	 * socket 0 then socket 1.
	 */
	अगर (skt->nr == 1) अणु
		gpio_set_value(H3XXX_EGPIO_OPT_ON, 0);
		gpio_set_value(H3XXX_EGPIO_OPT_NVRAM_ON, 0);
		/* hmm, करोes this suck घातer? */
		gpio_set_value(H3XXX_EGPIO_OPT_RESET, 1);
	पूर्ण
पूर्ण

काष्ठा pcmcia_low_level h3600_pcmcia_ops = अणु 
	.owner			= THIS_MODULE,
	.hw_init		= h3600_pcmcia_hw_init,
	.hw_shutकरोwn		= h3600_pcmcia_hw_shutकरोwn,
	.socket_state		= h3600_pcmcia_socket_state,
	.configure_socket	= h3600_pcmcia_configure_socket,

	.socket_init		= h3600_pcmcia_socket_init,
	.socket_suspend		= h3600_pcmcia_socket_suspend,
पूर्ण;

पूर्णांक pcmcia_h3600_init(काष्ठा device *dev)
अणु
	पूर्णांक ret = -ENODEV;

	अगर (machine_is_h3600() || machine_is_h3100())
		ret = sa11xx_drv_pcmcia_probe(dev, &h3600_pcmcia_ops, 0, 2);

	वापस ret;
पूर्ण
