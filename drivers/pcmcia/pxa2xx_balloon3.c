<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/pxa2xx_balloon3.c
 *
 * Balloon3 PCMCIA specअगरic routines.
 *
 *  Author:	Nick Bane
 *  Created:	June, 2006
 *  Copyright:	Toby Churchill Ltd
 *  Derived from pxa2xx_मुख्यstone.c, by Nico Pitre
 *
 * Various modअगरication by Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>

#समावेश <mach/balloon3.h>

#समावेश <यंत्र/mach-types.h>

#समावेश "soc_common.h"

अटल पूर्णांक balloon3_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	uपूर्णांक16_t ver;

	ver = __raw_पढ़ोw(BALLOON3_FPGA_VER);
	अगर (ver < 0x4f08)
		pr_warn("The FPGA code, version 0x%04x, is too old. "
			"PCMCIA/CF support might be broken in this version!",
			ver);

	skt->socket.pci_irq = BALLOON3_BP_CF_NRDY_IRQ;
	skt->stat[SOC_STAT_CD].gpio = BALLOON3_GPIO_S0_CD;
	skt->stat[SOC_STAT_CD].name = "PCMCIA0 CD";
	skt->stat[SOC_STAT_BVD1].irq = BALLOON3_BP_NSTSCHG_IRQ;
	skt->stat[SOC_STAT_BVD1].name = "PCMCIA0 STSCHG";

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ balloon3_pcmcia_status[2] = अणु
	BALLOON3_CF_nSTSCHG_BVD1,
	BALLOON3_CF_nSTSCHG_BVD1
पूर्ण;

अटल व्योम balloon3_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
				    काष्ठा pcmcia_state *state)
अणु
	uपूर्णांक16_t status;
	पूर्णांक flip;

	/* This actually पढ़ोs the STATUS रेजिस्टर */
	status = __raw_पढ़ोw(BALLOON3_CF_STATUS_REG);
	flip = (status ^ balloon3_pcmcia_status[skt->nr])
		& BALLOON3_CF_nSTSCHG_BVD1;
	/*
	 * Workaround क्रम STSCHG which can't be deनिश्चितed:
	 * We thereक्रमe disable/enable corresponding IRQs
	 * as needed to aव्योम IRQ locks.
	 */
	अगर (flip) अणु
		balloon3_pcmcia_status[skt->nr] = status;
		अगर (status & BALLOON3_CF_nSTSCHG_BVD1)
			enable_irq(BALLOON3_BP_NSTSCHG_IRQ);
		अन्यथा
			disable_irq(BALLOON3_BP_NSTSCHG_IRQ);
	पूर्ण

	state->पढ़ोy	= !!(status & BALLOON3_CF_nIRQ);
	state->bvd1	= !!(status & BALLOON3_CF_nSTSCHG_BVD1);
	state->bvd2	= 0;	/* not available */
	state->vs_3v	= 1;	/* Always true its a CF card */
	state->vs_Xv	= 0;	/* not available */
पूर्ण

अटल पूर्णांक balloon3_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
				       स्थिर socket_state_t *state)
अणु
	__raw_ग_लिखोw(BALLOON3_CF_RESET, BALLOON3_CF_CONTROL_REG +
			((state->flags & SS_RESET) ?
			BALLOON3_FPGA_SETnCLR : 0));
	वापस 0;
पूर्ण

अटल काष्ठा pcmcia_low_level balloon3_pcmcia_ops = अणु
	.owner			= THIS_MODULE,
	.hw_init		= balloon3_pcmcia_hw_init,
	.socket_state		= balloon3_pcmcia_socket_state,
	.configure_socket	= balloon3_pcmcia_configure_socket,
	.first			= 0,
	.nr			= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device *balloon3_pcmcia_device;

अटल पूर्णांक __init balloon3_pcmcia_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_balloon3())
		वापस -ENODEV;

	balloon3_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);
	अगर (!balloon3_pcmcia_device)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(balloon3_pcmcia_device,
			&balloon3_pcmcia_ops, माप(balloon3_pcmcia_ops));

	अगर (!ret)
		ret = platक्रमm_device_add(balloon3_pcmcia_device);

	अगर (ret)
		platक्रमm_device_put(balloon3_pcmcia_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास balloon3_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(balloon3_pcmcia_device);
पूर्ण

module_init(balloon3_pcmcia_init);
module_निकास(balloon3_pcmcia_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nick Bane <nick@cecomputing.co.uk>");
MODULE_ALIAS("platform:pxa2xx-pcmcia");
MODULE_DESCRIPTION("Balloon3 board CF/PCMCIA driver");
