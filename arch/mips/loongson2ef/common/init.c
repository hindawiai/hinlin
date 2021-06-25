<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */

#समावेश <linux/memblock.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/smp-ops.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fw/fw.h>

#समावेश <loongson.h>

/* Loongson CPU address winकरोws config space base address */
अचिन्हित दीर्घ __maybe_unused _loongson_addrwincfg_base;

अटल व्योम __init mips_nmi_setup(व्योम)
अणु
	व्योम *base;

	base = (व्योम *)(CAC_BASE + 0x380);
	स_नकल(base, except_vec_nmi, 0x80);
	flush_icache_range((अचिन्हित दीर्घ)base, (अचिन्हित दीर्घ)base + 0x80);
पूर्ण

व्योम __init prom_init(व्योम)
अणु
#अगर_घोषित CONFIG_CPU_SUPPORTS_ADDRWINCFG
	_loongson_addrwincfg_base = (अचिन्हित दीर्घ)
		ioremap(LOONGSON_ADDRWINCFG_BASE, LOONGSON_ADDRWINCFG_SIZE);
#पूर्ण_अगर

	fw_init_cmdline();
	prom_init_machtype();
	prom_init_env();

	/* init base address of io space */
	set_io_port_base((अचिन्हित दीर्घ)
		ioremap(LOONGSON_PCIIO_BASE, LOONGSON_PCIIO_SIZE));
	prom_init_memory();

	/*init the uart base address */
	prom_init_uart_base();
	board_nmi_handler_setup = mips_nmi_setup;
पूर्ण
