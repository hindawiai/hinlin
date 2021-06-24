<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */

#समावेश <linux/export.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/setup.h>

#समावेश <loongson.h>

/* raw */
अचिन्हित दीर्घ loongson_uart_base;
/* ioremapped */
अचिन्हित दीर्घ _loongson_uart_base;

EXPORT_SYMBOL(loongson_uart_base);
EXPORT_SYMBOL(_loongson_uart_base);

व्योम prom_init_loongson_uart_base(व्योम)
अणु
	चयन (mips_machtype) अणु
	हाल MACH_LEMOTE_FL2E:
		loongson_uart_base = LOONGSON_PCIIO_BASE + 0x3f8;
		अवरोध;
	हाल MACH_LEMOTE_FL2F:
	हाल MACH_LEMOTE_LL2F:
		loongson_uart_base = LOONGSON_PCIIO_BASE + 0x2f8;
		अवरोध;
	हाल MACH_LEMOTE_ML2F7:
	हाल MACH_LEMOTE_YL2F89:
	हाल MACH_DEXXON_GDIUM2F10:
	हाल MACH_LEMOTE_NAS:
	शेष:
		/* The CPU provided serial port (LPC) */
		loongson_uart_base = LOONGSON_LIO1_BASE + 0x3f8;
		अवरोध;
	पूर्ण

	_loongson_uart_base = TO_UNCAC(loongson_uart_base);
	setup_8250_early_prपूर्णांकk_port(_loongson_uart_base, 0, 1024);
पूर्ण
