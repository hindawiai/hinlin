<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/pxa2xx_trizeps4.c
 *
 * TRIZEPS PCMCIA specअगरic routines.
 *
 * Author:	Jथञrgen Schindele
 * Created:	20 02, 2006
 * Copyright:	Jथञrgen Schindele
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/irq.h>

#समावेश <mach/pxa2xx-regs.h>
#समावेश <mach/trizeps4.h>

#समावेश "soc_common.h"

बाह्य व्योम board_pcmcia_घातer(पूर्णांक घातer);

अटल पूर्णांक trizeps_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	/* we करोnt have voltage/card/पढ़ोy detection
	 * so we करोnt need पूर्णांकerrupts क्रम it
	 */
	चयन (skt->nr) अणु
	हाल 0:
		skt->stat[SOC_STAT_CD].gpio = GPIO_PCD;
		skt->stat[SOC_STAT_CD].name = "cs0_cd";
		skt->stat[SOC_STAT_RDY].gpio = GPIO_PRDY;
		skt->stat[SOC_STAT_RDY].name = "cs0_rdy";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/* release the reset of this card */
	pr_debug("%s: sock %d irq %d\n", __func__, skt->nr, skt->socket.pci_irq);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ trizeps_pcmcia_status[2];

अटल व्योम trizeps_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
				काष्ठा pcmcia_state *state)
अणु
	अचिन्हित लघु status = 0, change;
	status = CFSR_पढ़ोw();
	change = (status ^ trizeps_pcmcia_status[skt->nr]) &
				ConXS_CFSR_BVD_MASK;
	अगर (change) अणु
		trizeps_pcmcia_status[skt->nr] = status;
		अगर (status & ConXS_CFSR_BVD1) अणु
			/* enable_irq empty */
		पूर्ण अन्यथा अणु
			/* disable_irq empty */
		पूर्ण
	पूर्ण

	चयन (skt->nr) अणु
	हाल 0:
		/* just fill in fix states */
		state->bvd1   = (status & ConXS_CFSR_BVD1) ? 1 : 0;
		state->bvd2   = (status & ConXS_CFSR_BVD2) ? 1 : 0;
		state->vs_3v  = (status & ConXS_CFSR_VS1) ? 0 : 1;
		state->vs_Xv  = (status & ConXS_CFSR_VS2) ? 0 : 1;
		अवरोध;

#अगर_अघोषित CONFIG_MACH_TRIZEPS_CONXS
	/* on ConXS we only have one slot. Second is inactive */
	हाल 1:
		state->detect = 0;
		state->पढ़ोy  = 0;
		state->bvd1   = 0;
		state->bvd2   = 0;
		state->vs_3v  = 0;
		state->vs_Xv  = 0;
		अवरोध;

#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक trizeps_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
				स्थिर socket_state_t *state)
अणु
	पूर्णांक ret = 0;
	अचिन्हित लघु घातer = 0;

	/* we करो nothing here just check a bit */
	चयन (state->Vcc) अणु
	हाल 0:  घातer &= 0xfc; अवरोध;
	हाल 33: घातer |= ConXS_BCR_S0_VCC_3V3; अवरोध;
	हाल 50:
		pr_err("%s(): Vcc 5V not supported in socket\n", __func__);
		अवरोध;
	शेष:
		pr_err("%s(): bad Vcc %u\n", __func__, state->Vcc);
		ret = -1;
	पूर्ण

	चयन (state->Vpp) अणु
	हाल 0:  घातer &= 0xf3; अवरोध;
	हाल 33: घातer |= ConXS_BCR_S0_VPP_3V3; अवरोध;
	हाल 120:
		pr_err("%s(): Vpp 12V not supported in socket\n", __func__);
		अवरोध;
	शेष:
		अगर (state->Vpp != state->Vcc) अणु
			pr_err("%s(): bad Vpp %u\n", __func__, state->Vpp);
			ret = -1;
		पूर्ण
	पूर्ण

	चयन (skt->nr) अणु
	हाल 0:			 /* we only have 3.3V */
		board_pcmcia_घातer(घातer);
		अवरोध;

#अगर_अघोषित CONFIG_MACH_TRIZEPS_CONXS
	/* on ConXS we only have one slot. Second is inactive */
	हाल 1:
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम trizeps_pcmcia_socket_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	/* शेष is on */
	board_pcmcia_घातer(0x9);
पूर्ण

अटल व्योम trizeps_pcmcia_socket_suspend(काष्ठा soc_pcmcia_socket *skt)
अणु
	board_pcmcia_घातer(0x0);
पूर्ण

अटल काष्ठा pcmcia_low_level trizeps_pcmcia_ops = अणु
	.owner			= THIS_MODULE,
	.hw_init		= trizeps_pcmcia_hw_init,
	.socket_state		= trizeps_pcmcia_socket_state,
	.configure_socket	= trizeps_pcmcia_configure_socket,
	.socket_init		= trizeps_pcmcia_socket_init,
	.socket_suspend		= trizeps_pcmcia_socket_suspend,
#अगर_घोषित CONFIG_MACH_TRIZEPS_CONXS
	.nr			= 1,
#अन्यथा
	.nr			= 2,
#पूर्ण_अगर
	.first			= 0,
पूर्ण;

अटल काष्ठा platक्रमm_device *trizeps_pcmcia_device;

अटल पूर्णांक __init trizeps_pcmcia_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_trizeps4() && !machine_is_trizeps4wl())
		वापस -ENODEV;

	trizeps_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);
	अगर (!trizeps_pcmcia_device)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(trizeps_pcmcia_device,
			&trizeps_pcmcia_ops, माप(trizeps_pcmcia_ops));

	अगर (ret == 0)
		ret = platक्रमm_device_add(trizeps_pcmcia_device);

	अगर (ret)
		platक्रमm_device_put(trizeps_pcmcia_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास trizeps_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(trizeps_pcmcia_device);
पूर्ण

fs_initcall(trizeps_pcmcia_init);
module_निकास(trizeps_pcmcia_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Juergen Schindele");
MODULE_ALIAS("platform:pxa2xx-pcmcia");
