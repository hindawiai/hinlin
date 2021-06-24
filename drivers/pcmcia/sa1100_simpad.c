<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/pcmcia/sa1100_simpad.c
 *
 * PCMCIA implementation routines क्रम simpad
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/simpad.h>
#समावेश "sa1100_generic.h"

अटल पूर्णांक simpad_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु

	simpad_clear_cs3_bit(VCC_3V_EN|VCC_5V_EN|EN0|EN1);

	skt->stat[SOC_STAT_CD].name = "cf-detect";
	skt->stat[SOC_STAT_RDY].name = "cf-ready";

	वापस soc_pcmcia_request_gpiods(skt);
पूर्ण

अटल व्योम simpad_pcmcia_hw_shutकरोwn(काष्ठा soc_pcmcia_socket *skt)
अणु
	/* Disable CF bus: */
	/*simpad_set_cs3_bit(PCMCIA_BUFF_DIS);*/
	simpad_clear_cs3_bit(PCMCIA_RESET);
पूर्ण

अटल व्योम
simpad_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
			   काष्ठा pcmcia_state *state)
अणु
	दीर्घ cs3reg = simpad_get_cs3_ro();

	/* bvd1 might be cs3reg & PCMCIA_BVD1 */
	/* bvd2 might be cs3reg & PCMCIA_BVD2 */

	अगर ((cs3reg & (PCMCIA_VS1|PCMCIA_VS2)) ==
			(PCMCIA_VS1|PCMCIA_VS2)) अणु
		state->vs_3v=0;
		state->vs_Xv=0;
	पूर्ण अन्यथा अणु
		state->vs_3v=1;
		state->vs_Xv=0;
	पूर्ण
पूर्ण

अटल पूर्णांक
simpad_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
			       स्थिर socket_state_t *state)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/* Murphy: see table of MIC2562a-1 */
	चयन (state->Vcc) अणु
	हाल 0:
		simpad_clear_cs3_bit(VCC_3V_EN|VCC_5V_EN|EN0|EN1);
		अवरोध;

	हाल 33:
		simpad_clear_cs3_bit(VCC_3V_EN|EN1);
		simpad_set_cs3_bit(VCC_5V_EN|EN0);
		अवरोध;

	हाल 50:
		simpad_clear_cs3_bit(VCC_5V_EN|EN1);
		simpad_set_cs3_bit(VCC_3V_EN|EN0);
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "%s(): unrecognized Vcc %u\n",
			__func__, state->Vcc);
		simpad_clear_cs3_bit(VCC_3V_EN|VCC_5V_EN|EN0|EN1);
		local_irq_restore(flags);
		वापस -1;
	पूर्ण


	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल व्योम simpad_pcmcia_socket_suspend(काष्ठा soc_pcmcia_socket *skt)
अणु
	simpad_set_cs3_bit(PCMCIA_RESET);
पूर्ण

अटल काष्ठा pcmcia_low_level simpad_pcmcia_ops = अणु
	.owner			= THIS_MODULE,
	.hw_init		= simpad_pcmcia_hw_init,
	.hw_shutकरोwn		= simpad_pcmcia_hw_shutकरोwn,
	.socket_state		= simpad_pcmcia_socket_state,
	.configure_socket	= simpad_pcmcia_configure_socket,
	.socket_suspend		= simpad_pcmcia_socket_suspend,
पूर्ण;

पूर्णांक pcmcia_simpad_init(काष्ठा device *dev)
अणु
	पूर्णांक ret = -ENODEV;

	अगर (machine_is_simpad())
		ret = sa11xx_drv_pcmcia_probe(dev, &simpad_pcmcia_ops, 1, 1);

	वापस ret;
पूर्ण
