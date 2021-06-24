<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2012 Paul Parsons <lost.distance@yahoo.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/irq.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hx4700.h>

#समावेश "soc_common.h"

अटल काष्ठा gpio gpios[] = अणु
	अणु GPIO114_HX4700_CF_RESET,    GPIOF_OUT_INIT_LOW,   "CF reset"        पूर्ण,
	अणु EGPIO4_CF_3V3_ON,           GPIOF_OUT_INIT_LOW,   "CF 3.3V enable"  पूर्ण,
पूर्ण;

अटल पूर्णांक hx4700_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	पूर्णांक ret;

	ret = gpio_request_array(gpios, ARRAY_SIZE(gpios));
	अगर (ret)
		जाओ out;

	/*
	 * IRQ type must be set beक्रमe soc_pcmcia_hw_init() calls request_irq().
	 * The asic3 शेष IRQ type is level trigger low level detect, exactly
	 * the the संकेत present on GPIOD4_CF_nCD when a CF card is inserted.
	 * If the IRQ type is not changed, the asic3 पूर्णांकerrupt handler will loop
	 * repeatedly because it is unable to clear the level trigger पूर्णांकerrupt.
	 */
	irq_set_irq_type(gpio_to_irq(GPIOD4_CF_nCD), IRQ_TYPE_EDGE_BOTH);

	skt->stat[SOC_STAT_CD].gpio = GPIOD4_CF_nCD;
	skt->stat[SOC_STAT_CD].name = "PCMCIA CD";
	skt->stat[SOC_STAT_RDY].gpio = GPIO60_HX4700_CF_RNB;
	skt->stat[SOC_STAT_RDY].name = "PCMCIA Ready";

out:
	वापस ret;
पूर्ण

अटल व्योम hx4700_pcmcia_hw_shutकरोwn(काष्ठा soc_pcmcia_socket *skt)
अणु
	gpio_मुक्त_array(gpios, ARRAY_SIZE(gpios));
पूर्ण

अटल व्योम hx4700_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
	काष्ठा pcmcia_state *state)
अणु
	state->vs_3v = 1;
	state->vs_Xv = 0;
पूर्ण

अटल पूर्णांक hx4700_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
	स्थिर socket_state_t *state)
अणु
	चयन (state->Vcc) अणु
	हाल 0:
		gpio_set_value(EGPIO4_CF_3V3_ON, 0);
		अवरोध;
	हाल 33:
		gpio_set_value(EGPIO4_CF_3V3_ON, 1);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "pcmcia: Unsupported Vcc: %d\n", state->Vcc);
		वापस -EINVAL;
	पूर्ण

	gpio_set_value(GPIO114_HX4700_CF_RESET, (state->flags & SS_RESET) != 0);

	वापस 0;
पूर्ण

अटल काष्ठा pcmcia_low_level hx4700_pcmcia_ops = अणु
	.owner          = THIS_MODULE,
	.nr             = 1,
	.hw_init        = hx4700_pcmcia_hw_init,
	.hw_shutकरोwn    = hx4700_pcmcia_hw_shutकरोwn,
	.socket_state   = hx4700_pcmcia_socket_state,
	.configure_socket = hx4700_pcmcia_configure_socket,
पूर्ण;

अटल काष्ठा platक्रमm_device *hx4700_pcmcia_device;

अटल पूर्णांक __init hx4700_pcmcia_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;

	अगर (!machine_is_h4700())
		वापस -ENODEV;

	pdev = platक्रमm_device_रेजिस्टर_data(शून्य, "pxa2xx-pcmcia", -1,
		&hx4700_pcmcia_ops, माप(hx4700_pcmcia_ops));
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	hx4700_pcmcia_device = pdev;

	वापस 0;
पूर्ण

अटल व्योम __निकास hx4700_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(hx4700_pcmcia_device);
पूर्ण

module_init(hx4700_pcmcia_init);
module_निकास(hx4700_pcmcia_निकास);

MODULE_AUTHOR("Paul Parsons <lost.distance@yahoo.com>");
MODULE_DESCRIPTION("HP iPAQ hx4700 PCMCIA driver");
MODULE_LICENSE("GPL");
