<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas MX-G (R8A03022BG) Setup
 *
 *  Copyright (C) 2008, 2009  Paul Mundt
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/sh_समयr.h>
#समावेश <यंत्र/platक्रमm_early.h>

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7,
	IRQ8, IRQ9, IRQ10, IRQ11, IRQ12, IRQ13, IRQ14, IRQ15,

	PINT0, PINT1, PINT2, PINT3, PINT4, PINT5, PINT6, PINT7,
	SINT8, SINT7, SINT6, SINT5, SINT4, SINT3, SINT2, SINT1,

	SCIF0, SCIF1,

	MTU2_GROUP1, MTU2_GROUP2, MTU2_GROUP3, MTU2_GROUP4, MTU2_GROUP5,
	MTU2_TGI3B, MTU2_TGI3C,

	/* पूर्णांकerrupt groups */
	PINT,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_IRQ(IRQ0, 64), INTC_IRQ(IRQ1, 65),
	INTC_IRQ(IRQ2, 66), INTC_IRQ(IRQ3, 67),
	INTC_IRQ(IRQ4, 68), INTC_IRQ(IRQ5, 69),
	INTC_IRQ(IRQ6, 70), INTC_IRQ(IRQ7, 71),
	INTC_IRQ(IRQ8, 72), INTC_IRQ(IRQ9, 73),
	INTC_IRQ(IRQ10, 74), INTC_IRQ(IRQ11, 75),
	INTC_IRQ(IRQ12, 76), INTC_IRQ(IRQ13, 77),
	INTC_IRQ(IRQ14, 78), INTC_IRQ(IRQ15, 79),

	INTC_IRQ(PINT0, 80), INTC_IRQ(PINT1, 81),
	INTC_IRQ(PINT2, 82), INTC_IRQ(PINT3, 83),
	INTC_IRQ(PINT4, 84), INTC_IRQ(PINT5, 85),
	INTC_IRQ(PINT6, 86), INTC_IRQ(PINT7, 87),

	INTC_IRQ(SINT8, 94), INTC_IRQ(SINT7, 95),
	INTC_IRQ(SINT6, 96), INTC_IRQ(SINT5, 97),
	INTC_IRQ(SINT4, 98), INTC_IRQ(SINT3, 99),
	INTC_IRQ(SINT2, 100), INTC_IRQ(SINT1, 101),

	INTC_IRQ(SCIF0, 220), INTC_IRQ(SCIF0, 221),
	INTC_IRQ(SCIF0, 222), INTC_IRQ(SCIF0, 223),
	INTC_IRQ(SCIF1, 224), INTC_IRQ(SCIF1, 225),
	INTC_IRQ(SCIF1, 226), INTC_IRQ(SCIF1, 227),

	INTC_IRQ(MTU2_GROUP1, 228), INTC_IRQ(MTU2_GROUP1, 229),
	INTC_IRQ(MTU2_GROUP1, 230), INTC_IRQ(MTU2_GROUP1, 231),
	INTC_IRQ(MTU2_GROUP1, 232), INTC_IRQ(MTU2_GROUP1, 233),

	INTC_IRQ(MTU2_GROUP2, 234), INTC_IRQ(MTU2_GROUP2, 235),
	INTC_IRQ(MTU2_GROUP2, 236), INTC_IRQ(MTU2_GROUP2, 237),
	INTC_IRQ(MTU2_GROUP2, 238), INTC_IRQ(MTU2_GROUP2, 239),

	INTC_IRQ(MTU2_GROUP3, 240), INTC_IRQ(MTU2_GROUP3, 241),
	INTC_IRQ(MTU2_GROUP3, 242), INTC_IRQ(MTU2_GROUP3, 243),

	INTC_IRQ(MTU2_TGI3B, 244),
	INTC_IRQ(MTU2_TGI3C, 245),

	INTC_IRQ(MTU2_GROUP4, 246), INTC_IRQ(MTU2_GROUP4, 247),
	INTC_IRQ(MTU2_GROUP4, 248), INTC_IRQ(MTU2_GROUP4, 249),
	INTC_IRQ(MTU2_GROUP4, 250), INTC_IRQ(MTU2_GROUP4, 251),

	INTC_IRQ(MTU2_GROUP5, 252), INTC_IRQ(MTU2_GROUP5, 253),
	INTC_IRQ(MTU2_GROUP5, 254), INTC_IRQ(MTU2_GROUP5, 255),
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	INTC_GROUP(PINT, PINT0, PINT1, PINT2, PINT3,
		   PINT4, PINT5, PINT6, PINT7),
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xfffd9418, 0, 16, 4, /* IPR01 */ अणु IRQ0, IRQ1, IRQ2, IRQ3 पूर्ण पूर्ण,
	अणु 0xfffd941a, 0, 16, 4, /* IPR02 */ अणु IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
	अणु 0xfffd941c, 0, 16, 4, /* IPR03 */ अणु IRQ8, IRQ9, IRQ10, IRQ11 पूर्ण पूर्ण,
	अणु 0xfffd941e, 0, 16, 4, /* IPR04 */ अणु IRQ12, IRQ13, IRQ14, IRQ15 पूर्ण पूर्ण,
	अणु 0xfffd9420, 0, 16, 4, /* IPR05 */ अणु PINT, 0, 0, 0 पूर्ण पूर्ण,
	अणु 0xfffd9800, 0, 16, 4, /* IPR06 */ अणु पूर्ण पूर्ण,
	अणु 0xfffd9802, 0, 16, 4, /* IPR07 */ अणु पूर्ण पूर्ण,
	अणु 0xfffd9804, 0, 16, 4, /* IPR08 */ अणु पूर्ण पूर्ण,
	अणु 0xfffd9806, 0, 16, 4, /* IPR09 */ अणु पूर्ण पूर्ण,
	अणु 0xfffd9808, 0, 16, 4, /* IPR10 */ अणु पूर्ण पूर्ण,
	अणु 0xfffd980a, 0, 16, 4, /* IPR11 */ अणु पूर्ण पूर्ण,
	अणु 0xfffd980c, 0, 16, 4, /* IPR12 */ अणु पूर्ण पूर्ण,
	अणु 0xfffd980e, 0, 16, 4, /* IPR13 */ अणु पूर्ण पूर्ण,
	अणु 0xfffd9810, 0, 16, 4, /* IPR14 */ अणु 0, 0, 0, SCIF0 पूर्ण पूर्ण,
	अणु 0xfffd9812, 0, 16, 4, /* IPR15 */
		अणु SCIF1, MTU2_GROUP1, MTU2_GROUP2, MTU2_GROUP3 पूर्ण पूर्ण,
	अणु 0xfffd9814, 0, 16, 4, /* IPR16 */
		अणु MTU2_TGI3B, MTU2_TGI3C, MTU2_GROUP4, MTU2_GROUP5 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xfffd9408, 0, 16, /* PINTER */
	  अणु 0, 0, 0, 0, 0, 0, 0, 0,
	    PINT7, PINT6, PINT5, PINT4, PINT3, PINT2, PINT1, PINT0 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "mxg", vectors, groups,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);

अटल काष्ठा resource mtu2_resources[] = अणु
	DEFINE_RES_MEM(0xff801000, 0x400),
	DEFINE_RES_IRQ_NAMED(228, "tgi0a"),
	DEFINE_RES_IRQ_NAMED(234, "tgi1a"),
	DEFINE_RES_IRQ_NAMED(240, "tgi2a"),
पूर्ण;

अटल काष्ठा platक्रमm_device mtu2_device = अणु
	.name		= "sh-mtu2",
	.id		= -1,
	.resource	= mtu2_resources,
	.num_resources	= ARRAY_SIZE(mtu2_resources),
पूर्ण;

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xff804000, 0x100),
	DEFINE_RES_IRQ(220),
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

अटल काष्ठा platक्रमm_device *mxg_devices[] __initdata = अणु
	&scअगर0_device,
	&mtu2_device,
पूर्ण;

अटल पूर्णांक __init mxg_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(mxg_devices,
				    ARRAY_SIZE(mxg_devices));
पूर्ण
arch_initcall(mxg_devices_setup);

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण

अटल काष्ठा platक्रमm_device *mxg_early_devices[] __initdata = अणु
	&scअगर0_device,
	&mtu2_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(mxg_early_devices,
				   ARRAY_SIZE(mxg_early_devices));
पूर्ण
