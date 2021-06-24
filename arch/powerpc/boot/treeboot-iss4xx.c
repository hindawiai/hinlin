<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2010 Ben. Herrenschmidt, IBM Corporation.
 *
 * Based on earlier code:
 *   Copyright (C) Paul Mackerras 1997.
 *
 *   Matt Porter <mporter@kernel.crashing.org>
 *   Copyright 2002-2005 MontaVista Software Inc.
 *
 *   Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *   Copyright (c) 2003, 2004 Zultys Technologies
 *
 *    Copyright 2007 David Gibson, IBM Corporation.
 */
#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "elf.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "page.h"
#समावेश "ops.h"
#समावेश "reg.h"
#समावेश "io.h"
#समावेश "dcr.h"
#समावेश "4xx.h"
#समावेश "44x.h"
#समावेश "libfdt.h"

BSS_STACK(4096);

अटल u32 ibm4xx_memstart;

अटल व्योम iss_4xx_fixups(व्योम)
अणु
	व्योम *memory;
	u32 reg[3];

	memory = finddevice("/memory");
	अगर (!memory)
		fatal("Can't find memory node\n");
	/* This assumes #address-cells = 2, #size-cells =1 and that */
	getprop(memory, "reg", reg, माप(reg));
	अगर (reg[2])
		/* If the device tree specअगरies the memory range, use it */
		ibm4xx_memstart = reg[1];
	अन्यथा
		/* othersize, पढ़ो it from the SDRAM controller */
		ibm4xx_sdram_fixup_memsize();
पूर्ण

अटल व्योम *iss_4xx_vmlinux_alloc(अचिन्हित दीर्घ size)
अणु
	वापस (व्योम *)ibm4xx_memstart;
पूर्ण

#घोषणा SPRN_PIR	0x11E	/* Processor Identअगरication Register */
व्योम platक्रमm_init(व्योम)
अणु
	अचिन्हित दीर्घ end_of_ram = 0x08000000;
	अचिन्हित दीर्घ avail_ram = end_of_ram - (अचिन्हित दीर्घ)_end;
	u32 pir_reg;

	simple_alloc_init(_end, avail_ram, 128, 64);
	platक्रमm_ops.fixups = iss_4xx_fixups;
	platक्रमm_ops.vmlinux_alloc = iss_4xx_vmlinux_alloc;
	platक्रमm_ops.निकास = ibm44x_dbcr_reset;
	pir_reg = mfspr(SPRN_PIR);
	fdt_set_boot_cpuid_phys(_dtb_start, pir_reg);
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
