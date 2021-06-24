<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * June 2006 Steve Glendinning <steve.glendinning@shawell.net>
 *
 * Polaris-specअगरic resource declaration
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/smsc911x.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/heartbeat.h>
#समावेश <cpu/gpपन.स>
#समावेश <mach-se/mach/se.h>

#घोषणा BCR2		(0xFFFFFF62)
#घोषणा WCR2		(0xFFFFFF66)
#घोषणा AREA5_WAIT_CTRL	(0x1C00)
#घोषणा WAIT_STATES_10	(0x7)

/* Dummy supplies, where voltage करोesn't matter */
अटल काष्ठा regulator_consumer_supply dummy_supplies[] = अणु
	REGULATOR_SUPPLY("vddvario", "smsc911x.0"),
	REGULATOR_SUPPLY("vdd33a", "smsc911x.0"),
पूर्ण;

अटल काष्ठा resource smsc911x_resources[] = अणु
	[0] = अणु
		.name		= "smsc911x-memory",
		.start		= PA_EXT5,
		.end		= PA_EXT5 + 0x1fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.name		= "smsc911x-irq",
		.start		= IRQ0_IRQ,
		.end		= IRQ0_IRQ,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा smsc911x_platक्रमm_config smsc911x_config = अणु
	.irq_polarity	= SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type	= SMSC911X_IRQ_TYPE_OPEN_DRAIN,
	.flags		= SMSC911X_USE_32BIT,
	.phy_पूर्णांकerface	= PHY_INTERFACE_MODE_MII,
पूर्ण;

अटल काष्ठा platक्रमm_device smsc911x_device = अणु
	.name		= "smsc911x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smsc911x_resources),
	.resource	= smsc911x_resources,
	.dev = अणु
		.platक्रमm_data = &smsc911x_config,
	पूर्ण,
पूर्ण;

अटल अचिन्हित अक्षर heartbeat_bit_pos[] = अणु 0, 1, 2, 3 पूर्ण;

अटल काष्ठा heartbeat_data heartbeat_data = अणु
	.bit_pos	= heartbeat_bit_pos,
	.nr_bits	= ARRAY_SIZE(heartbeat_bit_pos),
पूर्ण;

अटल काष्ठा resource heartbeat_resource = अणु
	.start	= PORT_PCDR,
	.end	= PORT_PCDR,
	.flags	= IORESOURCE_MEM | IORESOURCE_MEM_8BIT,
पूर्ण;

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name		= "heartbeat",
	.id		= -1,
	.dev	= अणु
		.platक्रमm_data	= &heartbeat_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &heartbeat_resource,
पूर्ण;

अटल काष्ठा platक्रमm_device *polaris_devices[] __initdata = अणु
	&smsc911x_device,
	&heartbeat_device,
पूर्ण;

अटल पूर्णांक __init polaris_initialise(व्योम)
अणु
	u16 wcr, bcr_mask;

	prपूर्णांकk(KERN_INFO "Configuring Polaris external bus\n");

	regulator_रेजिस्टर_fixed(0, dummy_supplies, ARRAY_SIZE(dummy_supplies));

	/* Configure area 5 with 2 रुको states */
	wcr = __raw_पढ़ोw(WCR2);
	wcr &= (~AREA5_WAIT_CTRL);
	wcr |= (WAIT_STATES_10 << 10);
	__raw_ग_लिखोw(wcr, WCR2);

	/* Configure area 5 क्रम 32-bit access */
	bcr_mask = __raw_पढ़ोw(BCR2);
	bcr_mask |= 1 << 10;
	__raw_ग_लिखोw(bcr_mask, BCR2);

	वापस platक्रमm_add_devices(polaris_devices,
				    ARRAY_SIZE(polaris_devices));
पूर्ण
arch_initcall(polaris_initialise);

अटल काष्ठा ipr_data ipr_irq_table[] = अणु
	/* External IRQs */
	अणु IRQ0_IRQ, 0,  0,  1, पूर्ण,	/* IRQ0 */
	अणु IRQ1_IRQ, 0,  4,  1, पूर्ण,	/* IRQ1 */
पूर्ण;

अटल अचिन्हित दीर्घ ipr_offsets[] = अणु
	INTC_IPRC
पूर्ण;

अटल काष्ठा ipr_desc ipr_irq_desc = अणु
	.ipr_offsets	= ipr_offsets,
	.nr_offsets	= ARRAY_SIZE(ipr_offsets),

	.ipr_data	= ipr_irq_table,
	.nr_irqs	= ARRAY_SIZE(ipr_irq_table),
	.chip = अणु
		.name	= "sh7709-ext",
	पूर्ण,
पूर्ण;

अटल व्योम __init init_polaris_irq(व्योम)
अणु
	/* Disable all पूर्णांकerrupts */
	__raw_ग_लिखोw(0, BCR_ILCRA);
	__raw_ग_लिखोw(0, BCR_ILCRB);
	__raw_ग_लिखोw(0, BCR_ILCRC);
	__raw_ग_लिखोw(0, BCR_ILCRD);
	__raw_ग_लिखोw(0, BCR_ILCRE);
	__raw_ग_लिखोw(0, BCR_ILCRF);
	__raw_ग_लिखोw(0, BCR_ILCRG);

	रेजिस्टर_ipr_controller(&ipr_irq_desc);
पूर्ण

अटल काष्ठा sh_machine_vector mv_polaris __iniपंचांगv = अणु
	.mv_name		= "Polaris",
	.mv_init_irq		= init_polaris_irq,
पूर्ण;
