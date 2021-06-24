<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-sa1100/badge4.c
 *
 * BadgePAD 4 specअगरic initialization
 *
 *   Tim Connors <connors@hpl.hp.com>
 *   Christopher Hoover <ch@hpl.hp.com>
 *
 * Copyright (C) 2002 Hewlett-Packard Company
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/tty.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/leds.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/setup.h>
#समावेश <mach/irqs.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/hardware/sa1111.h>

#समावेश <mach/badge4.h>

#समावेश "generic.h"

अटल काष्ठा resource sa1111_resources[] = अणु
	[0] = DEFINE_RES_MEM(BADGE4_SA1111_BASE, 0x2000),
	[1] = DEFINE_RES_IRQ(BADGE4_IRQ_GPIO_SA1111),
पूर्ण;

अटल पूर्णांक badge4_sa1111_enable(व्योम *data, अचिन्हित devid)
अणु
	अगर (devid == SA1111_DEVID_USB)
		badge4_set_5V(BADGE4_5V_USB, 1);
	वापस 0;
पूर्ण

अटल व्योम badge4_sa1111_disable(व्योम *data, अचिन्हित devid)
अणु
	अगर (devid == SA1111_DEVID_USB)
		badge4_set_5V(BADGE4_5V_USB, 0);
पूर्ण

अटल काष्ठा sa1111_platक्रमm_data sa1111_info = अणु
	.disable_devs	= SA1111_DEVID_PS2_MSE,
	.enable		= badge4_sa1111_enable,
	.disable	= badge4_sa1111_disable,
पूर्ण;

अटल u64 sa1111_dmamask = 0xffffffffUL;

अटल काष्ठा platक्रमm_device sa1111_device = अणु
	.name		= "sa1111",
	.id		= 0,
	.dev		= अणु
		.dma_mask = &sa1111_dmamask,
		.coherent_dma_mask = 0xffffffff,
		.platक्रमm_data = &sa1111_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sa1111_resources),
	.resource	= sa1111_resources,
पूर्ण;

/* LEDs */
काष्ठा gpio_led badge4_gpio_leds[] = अणु
	अणु
		.name			= "badge4:red",
		.शेष_trigger	= "heartbeat",
		.gpio			= 7,
	पूर्ण,
	अणु
		.name			= "badge4:green",
		.शेष_trigger	= "cpu0",
		.gpio			= 9,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data badge4_gpio_led_info = अणु
	.leds		= badge4_gpio_leds,
	.num_leds	= ARRAY_SIZE(badge4_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device badge4_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &badge4_gpio_led_info,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&sa1111_device,
	&badge4_leds,
पूर्ण;

अटल पूर्णांक __init badge4_sa1111_init(व्योम)
अणु
	/*
	 * Ensure that the memory bus request/grant संकेतs are setup,
	 * and the grant is held in its inactive state
	 */
	sa1110_mb_disable();

	/*
	 * Probe क्रम SA1111.
	 */
	वापस platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
पूर्ण


/*
 * 1 x Intel 28F320C3 Advanced+ Boot Block Flash (32 Mi bit)
 *   Eight 4 KiW Parameter Bottom Blocks (64 KiB)
 *   Sixty-three 32 KiW Main Blocks (4032 Ki b)
 *
 * <or>
 *
 * 1 x Intel 28F640C3 Advanced+ Boot Block Flash (64 Mi bit)
 *   Eight 4 KiW Parameter Bottom Blocks (64 KiB)
 *   One-hundred-twenty-seven 32 KiW Main Blocks (8128 Ki b)
 */
अटल काष्ठा mtd_partition badge4_partitions[] = अणु
	अणु
		.name	= "BLOB boot loader",
		.offset	= 0,
		.size	= 0x0000A000
	पूर्ण, अणु
		.name	= "params",
		.offset	= MTDPART_OFS_APPEND,
		.size	= 0x00006000
	पूर्ण, अणु
		.name	= "root",
		.offset	= MTDPART_OFS_APPEND,
		.size	= MTDPART_SIZ_FULL
	पूर्ण
पूर्ण;

अटल काष्ठा flash_platक्रमm_data badge4_flash_data = अणु
	.map_name	= "cfi_probe",
	.parts		= badge4_partitions,
	.nr_parts	= ARRAY_SIZE(badge4_partitions),
पूर्ण;

अटल काष्ठा resource badge4_flash_resource =
	DEFINE_RES_MEM(SA1100_CS0_PHYS, SZ_64M);

अटल पूर्णांक five_v_on __initdata = 0;

अटल पूर्णांक __init five_v_on_setup(अक्षर *ignore)
अणु
	five_v_on = 1;
	वापस 1;
पूर्ण
__setup("five_v_on", five_v_on_setup);


अटल पूर्णांक __init badge4_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_badge4())
		वापस -ENODEV;

	/* LCD */
	GPCR  = (BADGE4_GPIO_LGP2 | BADGE4_GPIO_LGP3 |
		 BADGE4_GPIO_LGP4 | BADGE4_GPIO_LGP5 |
		 BADGE4_GPIO_LGP6 | BADGE4_GPIO_LGP7 |
		 BADGE4_GPIO_LGP8 | BADGE4_GPIO_LGP9 |
		 BADGE4_GPIO_GPA_VID | BADGE4_GPIO_GPB_VID |
		 BADGE4_GPIO_GPC_VID);
	GPDR &= ~BADGE4_GPIO_INT_VID;
	GPDR |= (BADGE4_GPIO_LGP2 | BADGE4_GPIO_LGP3 |
		 BADGE4_GPIO_LGP4 | BADGE4_GPIO_LGP5 |
		 BADGE4_GPIO_LGP6 | BADGE4_GPIO_LGP7 |
		 BADGE4_GPIO_LGP8 | BADGE4_GPIO_LGP9 |
		 BADGE4_GPIO_GPA_VID | BADGE4_GPIO_GPB_VID |
		 BADGE4_GPIO_GPC_VID);

	/* SDRAM SPD i2c */
	GPCR  = (BADGE4_GPIO_SDSDA | BADGE4_GPIO_SDSCL);
	GPDR |= (BADGE4_GPIO_SDSDA | BADGE4_GPIO_SDSCL);

	/* uart */
	GPCR  = (BADGE4_GPIO_UART_HS1 | BADGE4_GPIO_UART_HS2);
	GPDR |= (BADGE4_GPIO_UART_HS1 | BADGE4_GPIO_UART_HS2);

	/* CPLD muxsel0 input क्रम mux/adc chip select */
	GPCR  = BADGE4_GPIO_MUXSEL0;
	GPDR |= BADGE4_GPIO_MUXSEL0;

	/* test poपूर्णांकs: J5, J6 as inमाला_दो, J7 outमाला_दो */
	GPDR &= ~(BADGE4_GPIO_TESTPT_J5 | BADGE4_GPIO_TESTPT_J6);
	GPCR  = BADGE4_GPIO_TESTPT_J7;
	GPDR |= BADGE4_GPIO_TESTPT_J7;

	/* 5V supply rail. */
	GPCR  = BADGE4_GPIO_PCMEN5V;		/* initially off */
	GPDR |= BADGE4_GPIO_PCMEN5V;

	/* CPLD sdram type inमाला_दो; set up by blob */
	//GPDR |= (BADGE4_GPIO_SDTYP1 | BADGE4_GPIO_SDTYP0);
	prपूर्णांकk(KERN_DEBUG __खाता__ ": SDRAM CPLD typ1=%d typ0=%d\n",
		!!(GPLR & BADGE4_GPIO_SDTYP1),
		!!(GPLR & BADGE4_GPIO_SDTYP0));

	/* SA1111 reset pin; set up by blob */
	//GPSR  = BADGE4_GPIO_SA1111_NRST;
	//GPDR |= BADGE4_GPIO_SA1111_NRST;


	/* घातer management cruft */
	PGSR = 0;
	PWER = 0;
	PCFR = 0;
	PSDR = 0;

	PWER |= PWER_GPIO26;	/* wake up on an edge from TESTPT_J5 */
	PWER |= PWER_RTC;	/* wake up अगर rtc fires */

	/* drive sa1111_nrst during sleep */
	PGSR |= BADGE4_GPIO_SA1111_NRST;
	/* drive CPLD as is during sleep */
	PGSR |= (GPLR & (BADGE4_GPIO_SDTYP0|BADGE4_GPIO_SDTYP1));


	/* Now bring up the SA-1111. */
	ret = badge4_sa1111_init();
	अगर (ret < 0)
		prपूर्णांकk(KERN_ERR
			"%s: SA-1111 initialization failed (%d)\n",
			__func__, ret);


	/* maybe turn on 5v0 from the start */
	badge4_set_5V(BADGE4_5V_INITIALLY, five_v_on);

	sa11x0_रेजिस्टर_mtd(&badge4_flash_data, &badge4_flash_resource, 1);

	वापस 0;
पूर्ण

arch_initcall(badge4_init);


अटल अचिन्हित badge4_5V_biपंचांगap = 0;

व्योम badge4_set_5V(अचिन्हित subप्रणाली, पूर्णांक on)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित old_5V_biपंचांगap;

	local_irq_save(flags);

	old_5V_biपंचांगap = badge4_5V_biपंचांगap;

	अगर (on) अणु
		badge4_5V_biपंचांगap |= subप्रणाली;
	पूर्ण अन्यथा अणु
		badge4_5V_biपंचांगap &= ~subप्रणाली;
	पूर्ण

	/* detect on->off and off->on transitions */
	अगर ((!old_5V_biपंचांगap) && (badge4_5V_biपंचांगap)) अणु
		/* was off, now on */
		prपूर्णांकk(KERN_INFO "%s: enabling 5V supply rail\n", __func__);
		GPSR = BADGE4_GPIO_PCMEN5V;
	पूर्ण अन्यथा अगर ((old_5V_biपंचांगap) && (!badge4_5V_biपंचांगap)) अणु
		/* was on, now off */
		prपूर्णांकk(KERN_INFO "%s: disabling 5V supply rail\n", __func__);
		GPCR = BADGE4_GPIO_PCMEN5V;
	पूर्ण

	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(badge4_set_5V);


अटल काष्ठा map_desc badge4_io_desc[] __initdata = अणु
	अणु	/* SRAM  bank 1 */
		.भव	= 0xf1000000,
		.pfn		= __phys_to_pfn(0x08000000),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* SRAM  bank 2 */
		.भव	= 0xf2000000,
		.pfn		= __phys_to_pfn(0x10000000),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम
badge4_uart_pm(काष्ठा uart_port *port, u_पूर्णांक state, u_पूर्णांक oldstate)
अणु
	अगर (!state) अणु
		Ser1SDCR0 |= SDCR0_UART;
	पूर्ण
पूर्ण

अटल काष्ठा sa1100_port_fns badge4_port_fns __initdata = अणु
	.pm		= badge4_uart_pm,
पूर्ण;

अटल व्योम __init badge4_map_io(व्योम)
अणु
	sa1100_map_io();
	iotable_init(badge4_io_desc, ARRAY_SIZE(badge4_io_desc));

	sa1100_रेजिस्टर_uart_fns(&badge4_port_fns);
	sa1100_रेजिस्टर_uart(0, 3);
	sa1100_रेजिस्टर_uart(1, 1);
पूर्ण

MACHINE_START(BADGE4, "Hewlett-Packard Laboratories BadgePAD 4")
	.atag_offset	= 0x100,
	.map_io		= badge4_map_io,
	.nr_irqs	= SA1100_NR_IRQS,
	.init_irq	= sa1100_init_irq,
	.init_late	= sa11x0_init_late,
	.init_समय	= sa1100_समयr_init,
#अगर_घोषित CONFIG_SA1111
	.dma_zone_size	= SZ_1M,
#पूर्ण_अगर
	.restart	= sa11x0_restart,
MACHINE_END
