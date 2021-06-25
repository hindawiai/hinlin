<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2007 Ralf Baechle (ralf@linux-mips.org)
 *
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Yan hua (yanhua@lemote.com)
 * Author: Wu Zhangjin (wuzhangjin@gmail.com)
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/serial_8250.h>

#समावेश <यंत्र/bootinfo.h>

#समावेश <loongson.h>
#समावेश <machine.h>

#घोषणा PORT(पूर्णांक, clk)			\
अणु								\
	.irq		= पूर्णांक,					\
	.uartclk	= clk,					\
	.iotype		= UPIO_PORT,				\
	.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,	\
	.regshअगरt	= 0,					\
पूर्ण

#घोषणा PORT_M(पूर्णांक, clk)				\
अणु								\
	.irq		= MIPS_CPU_IRQ_BASE + (पूर्णांक),		\
	.uartclk	= clk,					\
	.iotype		= UPIO_MEM,				\
	.membase	= (व्योम __iomem *)शून्य,			\
	.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,	\
	.regshअगरt	= 0,					\
पूर्ण

अटल काष्ठा plat_serial8250_port uart8250_data[MACH_LOONGSON_END + 1] = अणु
	[MACH_LOONGSON_UNKNOWN]	= अणुपूर्ण,
	[MACH_LEMOTE_FL2E]	= PORT(4, 1843200),
	[MACH_LEMOTE_FL2F]	= PORT(3, 1843200),
	[MACH_LEMOTE_ML2F7]	= PORT_M(3, 3686400),
	[MACH_LEMOTE_YL2F89]	= PORT_M(3, 3686400),
	[MACH_DEXXON_GDIUM2F10]	= PORT_M(3, 3686400),
	[MACH_LEMOTE_NAS]	= PORT_M(3, 3686400),
	[MACH_LEMOTE_LL2F]	= PORT(3, 1843200),
	[MACH_LOONGSON_END]	= अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device uart8250_device = अणु
	.name = "serial8250",
	.id = PLAT8250_DEV_PLATFORM,
पूर्ण;

अटल पूर्णांक __init serial_init(व्योम)
अणु
	अचिन्हित अक्षर iotype;

	iotype = uart8250_data[mips_machtype].iotype;

	अगर (UPIO_MEM == iotype) अणु
		uart8250_data[mips_machtype].mapbase =
			loongson_uart_base;
		uart8250_data[mips_machtype].membase =
			(व्योम __iomem *)_loongson_uart_base;
	पूर्ण
	अन्यथा अगर (UPIO_PORT == iotype)
		uart8250_data[mips_machtype].iobase =
			loongson_uart_base - LOONGSON_PCIIO_BASE;

	स_रखो(&uart8250_data[mips_machtype + 1], 0,
			माप(काष्ठा plat_serial8250_port));
	uart8250_device.dev.platक्रमm_data = &uart8250_data[mips_machtype];

	वापस platक्रमm_device_रेजिस्टर(&uart8250_device);
पूर्ण
module_init(serial_init);

अटल व्योम __निकास serial_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(&uart8250_device);
पूर्ण
module_निकास(serial_निकास);
