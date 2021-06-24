<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/pxa2xx_colibri.c
 *
 * Driver क्रम Toradex Colibri PXA270 CF socket
 *
 * Copyright (C) 2010 Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>

#समावेश <यंत्र/mach-types.h>

#समावेश "soc_common.h"

#घोषणा	COLIBRI270_RESET_GPIO	53
#घोषणा	COLIBRI270_PPEN_GPIO	107
#घोषणा	COLIBRI270_BVD1_GPIO	83
#घोषणा	COLIBRI270_BVD2_GPIO	82
#घोषणा	COLIBRI270_DETECT_GPIO	84
#घोषणा	COLIBRI270_READY_GPIO	1

#घोषणा	COLIBRI320_RESET_GPIO	77
#घोषणा	COLIBRI320_PPEN_GPIO	57
#घोषणा	COLIBRI320_BVD1_GPIO	53
#घोषणा	COLIBRI320_BVD2_GPIO	79
#घोषणा	COLIBRI320_DETECT_GPIO	81
#घोषणा	COLIBRI320_READY_GPIO	29

क्रमागत अणु
	DETECT = 0,
	READY = 1,
	BVD1 = 2,
	BVD2 = 3,
	PPEN = 4,
	RESET = 5,
पूर्ण;

/* Contents of this array are configured on-the-fly in init function */
अटल काष्ठा gpio colibri_pcmcia_gpios[] = अणु
	अणु 0,	GPIOF_IN,	"PCMCIA Detect" पूर्ण,
	अणु 0,	GPIOF_IN,	"PCMCIA Ready" पूर्ण,
	अणु 0,	GPIOF_IN,	"PCMCIA BVD1" पूर्ण,
	अणु 0,	GPIOF_IN,	"PCMCIA BVD2" पूर्ण,
	अणु 0,	GPIOF_INIT_LOW,	"PCMCIA PPEN" पूर्ण,
	अणु 0,	GPIOF_INIT_HIGH,"PCMCIA Reset" पूर्ण,
पूर्ण;

अटल पूर्णांक colibri_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	पूर्णांक ret;

	ret = gpio_request_array(colibri_pcmcia_gpios,
				ARRAY_SIZE(colibri_pcmcia_gpios));
	अगर (ret)
		जाओ err1;

	skt->socket.pci_irq = gpio_to_irq(colibri_pcmcia_gpios[READY].gpio);
	skt->stat[SOC_STAT_CD].irq = gpio_to_irq(colibri_pcmcia_gpios[DETECT].gpio);
	skt->stat[SOC_STAT_CD].name = "PCMCIA CD";

err1:
	वापस ret;
पूर्ण

अटल व्योम colibri_pcmcia_hw_shutकरोwn(काष्ठा soc_pcmcia_socket *skt)
अणु
	gpio_मुक्त_array(colibri_pcmcia_gpios,
			ARRAY_SIZE(colibri_pcmcia_gpios));
पूर्ण

अटल व्योम colibri_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
					काष्ठा pcmcia_state *state)
अणु

	state->detect = !!gpio_get_value(colibri_pcmcia_gpios[DETECT].gpio);
	state->पढ़ोy  = !!gpio_get_value(colibri_pcmcia_gpios[READY].gpio);
	state->bvd1   = !!gpio_get_value(colibri_pcmcia_gpios[BVD1].gpio);
	state->bvd2   = !!gpio_get_value(colibri_pcmcia_gpios[BVD2].gpio);
	state->vs_3v  = 1;
	state->vs_Xv  = 0;
पूर्ण

अटल पूर्णांक
colibri_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
				स्थिर socket_state_t *state)
अणु
	gpio_set_value(colibri_pcmcia_gpios[PPEN].gpio,
			!(state->Vcc == 33 && state->Vpp < 50));
	gpio_set_value(colibri_pcmcia_gpios[RESET].gpio,
			state->flags & SS_RESET);
	वापस 0;
पूर्ण

अटल काष्ठा pcmcia_low_level colibri_pcmcia_ops = अणु
	.owner			= THIS_MODULE,

	.first			= 0,
	.nr			= 1,

	.hw_init		= colibri_pcmcia_hw_init,
	.hw_shutकरोwn		= colibri_pcmcia_hw_shutकरोwn,

	.socket_state		= colibri_pcmcia_socket_state,
	.configure_socket	= colibri_pcmcia_configure_socket,
पूर्ण;

अटल काष्ठा platक्रमm_device *colibri_pcmcia_device;

अटल पूर्णांक __init colibri_pcmcia_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_colibri() && !machine_is_colibri320())
		वापस -ENODEV;

	colibri_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);
	अगर (!colibri_pcmcia_device)
		वापस -ENOMEM;

	/* Colibri PXA270 */
	अगर (machine_is_colibri()) अणु
		colibri_pcmcia_gpios[RESET].gpio	= COLIBRI270_RESET_GPIO;
		colibri_pcmcia_gpios[PPEN].gpio		= COLIBRI270_PPEN_GPIO;
		colibri_pcmcia_gpios[BVD1].gpio		= COLIBRI270_BVD1_GPIO;
		colibri_pcmcia_gpios[BVD2].gpio		= COLIBRI270_BVD2_GPIO;
		colibri_pcmcia_gpios[DETECT].gpio	= COLIBRI270_DETECT_GPIO;
		colibri_pcmcia_gpios[READY].gpio	= COLIBRI270_READY_GPIO;
	/* Colibri PXA320 */
	पूर्ण अन्यथा अगर (machine_is_colibri320()) अणु
		colibri_pcmcia_gpios[RESET].gpio	= COLIBRI320_RESET_GPIO;
		colibri_pcmcia_gpios[PPEN].gpio		= COLIBRI320_PPEN_GPIO;
		colibri_pcmcia_gpios[BVD1].gpio		= COLIBRI320_BVD1_GPIO;
		colibri_pcmcia_gpios[BVD2].gpio		= COLIBRI320_BVD2_GPIO;
		colibri_pcmcia_gpios[DETECT].gpio	= COLIBRI320_DETECT_GPIO;
		colibri_pcmcia_gpios[READY].gpio	= COLIBRI320_READY_GPIO;
	पूर्ण

	ret = platक्रमm_device_add_data(colibri_pcmcia_device,
		&colibri_pcmcia_ops, माप(colibri_pcmcia_ops));

	अगर (!ret)
		ret = platक्रमm_device_add(colibri_pcmcia_device);

	अगर (ret)
		platक्रमm_device_put(colibri_pcmcia_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास colibri_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(colibri_pcmcia_device);
पूर्ण

module_init(colibri_pcmcia_init);
module_निकास(colibri_pcmcia_निकास);

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("PCMCIA support for Toradex Colibri PXA270/PXA320");
MODULE_ALIAS("platform:pxa2xx-pcmcia");
MODULE_LICENSE("GPL");
