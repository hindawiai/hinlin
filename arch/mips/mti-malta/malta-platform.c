<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2006, 07 MIPS Technologies, Inc.
 *   written by Ralf Baechle (ralf@linux-mips.org)
 *     written by Ralf Baechle <ralf@linux-mips.org>
 *
 * Copyright (C) 2008 Wind River Systems, Inc.
 *   updated by Tiejun Chen <tiejun.chen@windriver.com>
 *
 * 1. Probe driver क्रम the Malta's UART ports:
 *
 *   o 2 ports in the SMC SuperIO
 *   o 1 port in the CBUS UART, a discrete 16550 which normally is only used
 *     क्रम bringups.
 *
 * We करोn't use 8250_platक्रमm.c on Malta as it would result in the CBUS
 * UART becoming ttyS0.
 *
 * 2. Register RTC-CMOS platक्रमm device on Malta.
 */
#समावेश <linux/init.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/mips-boards/maltaपूर्णांक.h>

#घोषणा SMC_PORT(base, पूर्णांक)						\
अणु									\
	.iobase		= base,						\
	.irq		= पूर्णांक,						\
	.uartclk	= 1843200,					\
	.iotype		= UPIO_PORT,					\
	.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,		\
	.regshअगरt	= 0,						\
पूर्ण

#घोषणा CBUS_UART_FLAGS (UPF_BOOT_AUTOCONF | UPF_SKIP_TEST | UPF_IOREMAP)

अटल काष्ठा plat_serial8250_port uart8250_data[] = अणु
	SMC_PORT(0x3F8, 4),
	SMC_PORT(0x2F8, 3),
#अगर_अघोषित CONFIG_MIPS_CMP
	अणु
		.mapbase	= 0x1f000900,	/* The CBUS UART */
		.irq		= MIPS_CPU_IRQ_BASE + MIPSCPU_INT_MB2,
		.uartclk	= 3686400,	/* Twice the usual clk! */
		.iotype		= UPIO_MEM32,
		.flags		= CBUS_UART_FLAGS,
		.regshअगरt	= 3,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device malta_uart8250_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= uart8250_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *malta_devices[] __initdata = अणु
	&malta_uart8250_device,
पूर्ण;

अटल पूर्णांक __init malta_add_devices(व्योम)
अणु
	वापस platक्रमm_add_devices(malta_devices, ARRAY_SIZE(malta_devices));
पूर्ण

device_initcall(malta_add_devices);
