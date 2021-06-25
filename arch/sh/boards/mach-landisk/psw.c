<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/landisk/psw.c
 *
 * push चयन support क्रम LANDISK and USL-5P
 *
 * Copyright (C) 2006-2007  Paul Mundt
 * Copyright (C) 2007  kogiidena
 */
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <mach-landisk/mach/iodata_landisk.h>
#समावेश <यंत्र/push-चयन.h>

अटल irqवापस_t psw_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा platक्रमm_device *pdev = arg;
	काष्ठा push_चयन *psw = platक्रमm_get_drvdata(pdev);
	काष्ठा push_चयन_platक्रमm_info *psw_info = pdev->dev.platक्रमm_data;
	अचिन्हित पूर्णांक sw_value;
	पूर्णांक ret = 0;

	sw_value = (0x0ff & (~__raw_पढ़ोb(PA_STATUS)));

	/* Nothing to करो अगर there's no state change */
	अगर (psw->state) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	/* Figure out who उठाओd it */
	अगर (sw_value & (1 << psw_info->bit)) अणु
		psw->state = 1;
		mod_समयr(&psw->debounce, jअगरfies + 50);
		ret = 1;
	पूर्ण

out:
	/* Clear the चयन IRQs */
	__raw_ग_लिखोb(0x00, PA_PWRINT_CLR);

	वापस IRQ_RETVAL(ret);
पूर्ण

अटल काष्ठा resource psw_घातer_resources[] = अणु
	[0] = अणु
		.start = IRQ_POWER,
		.flags = IORESOURCE_IRQ,
       पूर्ण,
पूर्ण;

अटल काष्ठा resource psw_usl5p_resources[] = अणु
	[0] = अणु
		.start = IRQ_BUTTON,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा push_चयन_platक्रमm_info psw_घातer_platक्रमm_data = अणु
	.name		= "psw_power",
	.bit		= 4,
	.irq_flags	= IRQF_SHARED,
	.irq_handler	= psw_irq_handler,
पूर्ण;

अटल काष्ठा push_चयन_platक्रमm_info psw1_platक्रमm_data = अणु
	.name		= "psw1",
	.bit		= 0,
	.irq_flags	= IRQF_SHARED,
	.irq_handler	= psw_irq_handler,
पूर्ण;

अटल काष्ठा push_चयन_platक्रमm_info psw2_platक्रमm_data = अणु
	.name		= "psw2",
	.bit		= 2,
	.irq_flags	= IRQF_SHARED,
	.irq_handler	= psw_irq_handler,
पूर्ण;

अटल काष्ठा push_चयन_platक्रमm_info psw3_platक्रमm_data = अणु
	.name		= "psw3",
	.bit		= 1,
	.irq_flags	= IRQF_SHARED,
	.irq_handler	= psw_irq_handler,
पूर्ण;

अटल काष्ठा platक्रमm_device psw_घातer_चयन_device = अणु
	.name		= "push-switch",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(psw_घातer_resources),
	.resource	= psw_घातer_resources,
	.dev		= अणु
		.platक्रमm_data = &psw_घातer_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device psw1_चयन_device = अणु
	.name		= "push-switch",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(psw_usl5p_resources),
	.resource	= psw_usl5p_resources,
	.dev		= अणु
		.platक्रमm_data = &psw1_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device psw2_चयन_device = अणु
	.name		= "push-switch",
	.id		= 2,
	.num_resources	= ARRAY_SIZE(psw_usl5p_resources),
	.resource	= psw_usl5p_resources,
	.dev		= अणु
		.platक्रमm_data = &psw2_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device psw3_चयन_device = अणु
	.name		= "push-switch",
	.id		= 3,
	.num_resources	= ARRAY_SIZE(psw_usl5p_resources),
	.resource	= psw_usl5p_resources,
	.dev = अणु
		.platक्रमm_data = &psw3_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *psw_devices[] = अणु
	&psw_घातer_चयन_device,
	&psw1_चयन_device,
	&psw2_चयन_device,
	&psw3_चयन_device,
पूर्ण;

अटल पूर्णांक __init psw_init(व्योम)
अणु
	वापस platक्रमm_add_devices(psw_devices, ARRAY_SIZE(psw_devices));
पूर्ण
device_initcall(psw_init);
