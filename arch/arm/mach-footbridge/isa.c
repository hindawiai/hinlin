<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-footbridge/isa.c
 *
 *  Copyright (C) 2004 Russell King.
 */
#समावेश <linux/init.h>
#समावेश <linux/serial_8250.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hardware/dec21285.h>

#समावेश "common.h"

अटल काष्ठा resource rtc_resources[] = अणु
	[0] = अणु
		.start	= 0x70,
		.end	= 0x73,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_ISA_RTC_ALARM,
		.end	= IRQ_ISA_RTC_ALARM,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "rtc_cmos",
	.id		= -1,
	.resource	= rtc_resources,
	.num_resources	= ARRAY_SIZE(rtc_resources),
पूर्ण;

अटल काष्ठा resource serial_resources[] = अणु
	[0] = अणु
		.start	= 0x3f8,
		.end	= 0x3ff,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		.start	= 0x2f8,
		.end	= 0x2ff,
		.flags	= IORESOURCE_IO,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_serial8250_port serial_platक्रमm_data[] = अणु
	अणु
		.iobase		= 0x3f8,
		.irq		= IRQ_ISA_UART,
		.uartclk	= 1843200,
		.regshअगरt	= 0,
		.iotype		= UPIO_PORT,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
	पूर्ण,
	अणु
		.iobase		= 0x2f8,
		.irq		= IRQ_ISA_UART2,
		.uartclk	= 1843200,
		.regshअगरt	= 0,
		.iotype		= UPIO_PORT,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device serial_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= serial_platक्रमm_data,
	पूर्ण,
	.resource		= serial_resources,
	.num_resources		= ARRAY_SIZE(serial_resources),
पूर्ण;

अटल पूर्णांक __init footbridge_isa_init(व्योम)
अणु
	पूर्णांक err = 0;

	अगर (!footbridge_cfn_mode())
		वापस 0;

	/* Personal server करोesn't have RTC */
	अगर (!machine_is_personal_server()) अणु
		isa_rtc_init();
		err = platक्रमm_device_रेजिस्टर(&rtc_device);
		अगर (err)
			prपूर्णांकk(KERN_ERR "Unable to register RTC device: %d\n", err);
	पूर्ण
	err = platक्रमm_device_रेजिस्टर(&serial_device);
	अगर (err)
		prपूर्णांकk(KERN_ERR "Unable to register serial device: %d\n", err);
	वापस 0;
पूर्ण

arch_initcall(footbridge_isa_init);
