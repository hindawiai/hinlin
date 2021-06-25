<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/renesas/r7780rp/psw.c
 *
 * push चयन support क्रम RDBRP-1/RDBREVRP-1 debug boards.
 *
 * Copyright (C) 2006  Paul Mundt
 */
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <mach/highlander.h>
#समावेश <यंत्र/push-चयन.h>

अटल irqवापस_t psw_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा platक्रमm_device *pdev = arg;
	काष्ठा push_चयन *psw = platक्रमm_get_drvdata(pdev);
	काष्ठा push_चयन_platक्रमm_info *psw_info = pdev->dev.platक्रमm_data;
	अचिन्हित पूर्णांक l, mask;
	पूर्णांक ret = 0;

	l = __raw_पढ़ोw(PA_DBSW);

	/* Nothing to करो अगर there's no state change */
	अगर (psw->state) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	mask = l & 0x70;
	/* Figure out who उठाओd it */
	अगर (mask & (1 << psw_info->bit)) अणु
		psw->state = !!(mask & (1 << psw_info->bit));
		अगर (psw->state)	/* debounce */
			mod_समयr(&psw->debounce, jअगरfies + 50);

		ret = 1;
	पूर्ण

out:
	/* Clear the चयन IRQs */
	l |= (0x7 << 12);
	__raw_ग_लिखोw(l, PA_DBSW);

	वापस IRQ_RETVAL(ret);
पूर्ण

अटल काष्ठा resource psw_resources[] = अणु
	[0] = अणु
		.start	= IRQ_PSW,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा push_चयन_platक्रमm_info s2_platक्रमm_data = अणु
	.name		= "s2",
	.bit		= 6,
	.irq_flags	= IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
			  IRQF_SHARED,
	.irq_handler	= psw_irq_handler,
पूर्ण;

अटल काष्ठा platक्रमm_device s2_चयन_device = अणु
	.name		= "push-switch",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(psw_resources),
	.resource	= psw_resources,
	.dev		= अणु
		.platक्रमm_data = &s2_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा push_चयन_platक्रमm_info s3_platक्रमm_data = अणु
	.name		= "s3",
	.bit		= 5,
	.irq_flags	= IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
			  IRQF_SHARED,
	.irq_handler	= psw_irq_handler,
पूर्ण;

अटल काष्ठा platक्रमm_device s3_चयन_device = अणु
	.name		= "push-switch",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(psw_resources),
	.resource	= psw_resources,
	.dev		= अणु
		.platक्रमm_data = &s3_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा push_चयन_platक्रमm_info s4_platक्रमm_data = अणु
	.name		= "s4",
	.bit		= 4,
	.irq_flags	= IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
			  IRQF_SHARED,
	.irq_handler	= psw_irq_handler,
पूर्ण;

अटल काष्ठा platक्रमm_device s4_चयन_device = अणु
	.name		= "push-switch",
	.id		= 2,
	.num_resources	= ARRAY_SIZE(psw_resources),
	.resource	= psw_resources,
	.dev		= अणु
		.platक्रमm_data = &s4_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *psw_devices[] = अणु
	&s2_चयन_device, &s3_चयन_device, &s4_चयन_device,
पूर्ण;

अटल पूर्णांक __init psw_init(व्योम)
अणु
	वापस platक्रमm_add_devices(psw_devices, ARRAY_SIZE(psw_devices));
पूर्ण
module_init(psw_init);
