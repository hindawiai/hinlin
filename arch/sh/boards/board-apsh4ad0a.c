<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ALPHAPROJECT AP-SH4AD-0A Support.
 *
 * Copyright (C) 2010 ALPHAPROJECT Co.,Ltd.
 * Copyright (C) 2010  Matt Fleming
 * Copyright (C) 2010  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/smsc911x.h>
#समावेश <linux/irq.h>
#समावेश <linux/clk.h>
#समावेश <यंत्र/machvec.h>
#समावेश <linux/sizes.h>

/* Dummy supplies, where voltage करोesn't matter */
अटल काष्ठा regulator_consumer_supply dummy_supplies[] = अणु
	REGULATOR_SUPPLY("vddvario", "smsc911x"),
	REGULATOR_SUPPLY("vdd33a", "smsc911x"),
पूर्ण;

अटल काष्ठा resource smsc911x_resources[] = अणु
	[0] = अणु
		.name		= "smsc911x-memory",
		.start		= 0xA4000000,
		.end		= 0xA4000000 + SZ_256 - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.name		= "smsc911x-irq",
		.start		= evt2irq(0x200),
		.end		= evt2irq(0x200),
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा smsc911x_platक्रमm_config smsc911x_config = अणु
	.irq_polarity	= SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type	= SMSC911X_IRQ_TYPE_OPEN_DRAIN,
	.flags		= SMSC911X_USE_16BIT,
	.phy_पूर्णांकerface	= PHY_INTERFACE_MODE_MII,
पूर्ण;

अटल काष्ठा platक्रमm_device smsc911x_device = अणु
	.name		= "smsc911x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smsc911x_resources),
	.resource	= smsc911x_resources,
	.dev = अणु
		.platक्रमm_data = &smsc911x_config,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *apsh4ad0a_devices[] __initdata = अणु
	&smsc911x_device,
पूर्ण;

अटल पूर्णांक __init apsh4ad0a_devices_setup(व्योम)
अणु
	regulator_रेजिस्टर_fixed(0, dummy_supplies, ARRAY_SIZE(dummy_supplies));

	वापस platक्रमm_add_devices(apsh4ad0a_devices,
				    ARRAY_SIZE(apsh4ad0a_devices));
पूर्ण
device_initcall(apsh4ad0a_devices_setup);

अटल पूर्णांक apsh4ad0a_mode_pins(व्योम)
अणु
	पूर्णांक value = 0;

	/* These are the factory शेष settings of SW1 and SW2.
	 * If you change these dip चयनes then you will need to
	 * adjust the values below as well.
	 */
	value |=  MODE_PIN0;  /* Clock Mode 3 */
	value |=  MODE_PIN1;
	value &= ~MODE_PIN2;
	value &= ~MODE_PIN3;
	value &= ~MODE_PIN4;  /* 16-bit Area0 bus width  */
	value |=  MODE_PIN5;
	value |=  MODE_PIN6;
	value |=  MODE_PIN7;  /* Normal mode */
	value |=  MODE_PIN8;  /* Little Endian */
	value |=  MODE_PIN9;  /* Crystal resonator */
	value &= ~MODE_PIN10; /* 29-bit address mode */
	value &= ~MODE_PIN11; /* PCI-E Root port */
	value &= ~MODE_PIN12; /* 4 lane + 1 lane */
	value |=  MODE_PIN13; /* AUD Enable */
	value &= ~MODE_PIN14; /* Normal Operation */

	वापस value;
पूर्ण

अटल पूर्णांक apsh4ad0a_clk_init(व्योम)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = clk_get(शून्य, "extal");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);
	ret = clk_set_rate(clk, 33333000);
	clk_put(clk);

	वापस ret;
पूर्ण

/* Initialize the board */
अटल व्योम __init apsh4ad0a_setup(अक्षर **cmdline_p)
अणु
	pr_info("Alpha Project AP-SH4AD-0A support:\n");
पूर्ण

अटल व्योम __init apsh4ad0a_init_irq(व्योम)
अणु
	plat_irq_setup_pins(IRQ_MODE_IRQ3210);
पूर्ण

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_apsh4ad0a __iniपंचांगv = अणु
	.mv_name		= "AP-SH4AD-0A",
	.mv_setup		= apsh4ad0a_setup,
	.mv_mode_pins		= apsh4ad0a_mode_pins,
	.mv_clk_init		= apsh4ad0a_clk_init,
	.mv_init_irq		= apsh4ad0a_init_irq,
पूर्ण;
