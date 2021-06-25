<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/pxa2xx_मुख्यstone.c
 *
 * Mainstone PCMCIA specअगरic routines.
 *
 * Created:	May 12, 2004
 * Author:	Nicolas Pitre
 * Copyright:	MontaVista Software Inc.
 */
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश <pcmcia/ss.h>

#समावेश <यंत्र/mach-types.h>

#समावेश "soc_common.h"
#समावेश "max1600.h"

अटल पूर्णांक mst_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	काष्ठा device *dev = skt->socket.dev.parent;
	काष्ठा max1600 *m;
	पूर्णांक ret;

	skt->stat[SOC_STAT_CD].name = skt->nr ? "bdetect" : "adetect";
	skt->stat[SOC_STAT_BVD1].name = skt->nr ? "bbvd1" : "abvd1";
	skt->stat[SOC_STAT_BVD2].name = skt->nr ? "bbvd2" : "abvd2";
	skt->stat[SOC_STAT_RDY].name = skt->nr ? "bready" : "aready";
	skt->stat[SOC_STAT_VS1].name = skt->nr ? "bvs1" : "avs1";
	skt->stat[SOC_STAT_VS2].name = skt->nr ? "bvs2" : "avs2";

	skt->gpio_reset = devm_gpiod_get(dev, skt->nr ? "breset" : "areset",
					 GPIOD_OUT_HIGH);
	अगर (IS_ERR(skt->gpio_reset))
		वापस PTR_ERR(skt->gpio_reset);

	ret = max1600_init(dev, &m, skt->nr ? MAX1600_CHAN_B : MAX1600_CHAN_A,
			   MAX1600_CODE_HIGH);
	अगर (ret)
		वापस ret;

	skt->driver_data = m;

	वापस soc_pcmcia_request_gpiods(skt);
पूर्ण

अटल अचिन्हित पूर्णांक mst_pcmcia_bvd1_status[2];

अटल व्योम mst_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
				    काष्ठा pcmcia_state *state)
अणु
	अचिन्हित पूर्णांक flip = mst_pcmcia_bvd1_status[skt->nr] ^ state->bvd1;

	/*
	 * Workaround क्रम STSCHG which can't be deनिश्चितed:
	 * We thereक्रमe disable/enable corresponding IRQs
	 * as needed to aव्योम IRQ locks.
	 */
	अगर (flip) अणु
		mst_pcmcia_bvd1_status[skt->nr] = state->bvd1;
		अगर (state->bvd1)
			enable_irq(skt->stat[SOC_STAT_BVD1].irq);
		अन्यथा
			disable_irq(skt->stat[SOC_STAT_BVD2].irq);
	पूर्ण
पूर्ण

अटल पूर्णांक mst_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
				       स्थिर socket_state_t *state)
अणु
	वापस max1600_configure(skt->driver_data, state->Vcc, state->Vpp);
पूर्ण

अटल काष्ठा pcmcia_low_level mst_pcmcia_ops __initdata = अणु
	.owner			= THIS_MODULE,
	.hw_init		= mst_pcmcia_hw_init,
	.socket_state		= mst_pcmcia_socket_state,
	.configure_socket	= mst_pcmcia_configure_socket,
	.nr			= 2,
पूर्ण;

अटल काष्ठा platक्रमm_device *mst_pcmcia_device;

अटल पूर्णांक __init mst_pcmcia_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_मुख्यstone())
		वापस -ENODEV;

	mst_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);
	अगर (!mst_pcmcia_device)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(mst_pcmcia_device, &mst_pcmcia_ops,
				       माप(mst_pcmcia_ops));
	अगर (ret == 0)
		ret = platक्रमm_device_add(mst_pcmcia_device);

	अगर (ret)
		platक्रमm_device_put(mst_pcmcia_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास mst_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(mst_pcmcia_device);
पूर्ण

fs_initcall(mst_pcmcia_init);
module_निकास(mst_pcmcia_निकास);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa2xx-pcmcia");
