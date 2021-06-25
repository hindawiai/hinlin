<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH4-202 Setup
 *
 *  Copyright (C) 2006  Paul Mundt
 *  Copyright (C) 2009  Magnus Damm
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/platक्रमm_early.h>

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xffe80000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x700)),
	DEFINE_RES_IRQ(evt2irq(0x720)),
	DEFINE_RES_IRQ(evt2irq(0x760)),
	DEFINE_RES_IRQ(evt2irq(0x740)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर0_device = अणु
	.name		= "sh-sci",
	.id		= 0,
	.resource	= scअगर0_resources,
	.num_resources	= ARRAY_SIZE(scअगर0_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर0_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_समयr_config पंचांगu0_platक्रमm_data = अणु
	.channels_mask = 7,
पूर्ण;

अटल काष्ठा resource पंचांगu0_resources[] = अणु
	DEFINE_RES_MEM(0xffd80000, 0x30),
	DEFINE_RES_IRQ(evt2irq(0x400)),
	DEFINE_RES_IRQ(evt2irq(0x420)),
	DEFINE_RES_IRQ(evt2irq(0x440)),
पूर्ण;

अटल काष्ठा platक्रमm_device पंचांगu0_device = अणु
	.name		= "sh-tmu",
	.id		= 0,
	.dev = अणु
		.platक्रमm_data	= &पंचांगu0_platक्रमm_data,
	पूर्ण,
	.resource	= पंचांगu0_resources,
	.num_resources	= ARRAY_SIZE(पंचांगu0_resources),
पूर्ण;

अटल काष्ठा platक्रमm_device *sh4202_devices[] __initdata = अणु
	&scअगर0_device,
	&पंचांगu0_device,
पूर्ण;

अटल पूर्णांक __init sh4202_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh4202_devices,
				    ARRAY_SIZE(sh4202_devices));
पूर्ण
arch_initcall(sh4202_devices_setup);

अटल काष्ठा platक्रमm_device *sh4202_early_devices[] __initdata = अणु
	&scअगर0_device,
	&पंचांगu0_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh4202_early_devices,
				   ARRAY_SIZE(sh4202_early_devices));
पूर्ण

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRL0, IRL1, IRL2, IRL3, /* only IRLM mode supported */
	HUDI, TMU0, TMU1, TMU2, RTC, SCIF, WDT,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_VECT(HUDI, 0x600),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU2, 0x460),
	INTC_VECT(RTC, 0x480), INTC_VECT(RTC, 0x4a0),
	INTC_VECT(RTC, 0x4c0),
	INTC_VECT(SCIF, 0x700), INTC_VECT(SCIF, 0x720),
	INTC_VECT(SCIF, 0x740), INTC_VECT(SCIF, 0x760),
	INTC_VECT(WDT, 0x560),
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd00004, 0, 16, 4, /* IPRA */ अणु TMU0, TMU1, TMU2, RTC पूर्ण पूर्ण,
	अणु 0xffd00008, 0, 16, 4, /* IPRB */ अणु WDT, 0, 0, 0 पूर्ण पूर्ण,
	अणु 0xffd0000c, 0, 16, 4, /* IPRC */ अणु 0, 0, SCIF, HUDI पूर्ण पूर्ण,
	अणु 0xffd00010, 0, 16, 4, /* IPRD */ अणु IRL0, IRL1, IRL2, IRL3 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh4-202", vectors, शून्य,
			 शून्य, prio_रेजिस्टरs, शून्य);

अटल काष्ठा पूर्णांकc_vect vectors_irlm[] __initdata = अणु
	INTC_VECT(IRL0, 0x240), INTC_VECT(IRL1, 0x2a0),
	INTC_VECT(IRL2, 0x300), INTC_VECT(IRL3, 0x360),
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_irlm, "sh4-202_irlm", vectors_irlm, शून्य,
			 शून्य, prio_रेजिस्टरs, शून्य);

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण

#घोषणा INTC_ICR	0xffd00000UL
#घोषणा INTC_ICR_IRLM   (1<<7)

व्योम __init plat_irq_setup_pins(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल IRQ_MODE_IRQ: /* inभागidual पूर्णांकerrupt mode क्रम IRL3-0 */
		__raw_ग_लिखोw(__raw_पढ़ोw(INTC_ICR) | INTC_ICR_IRLM, INTC_ICR);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irlm);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण
