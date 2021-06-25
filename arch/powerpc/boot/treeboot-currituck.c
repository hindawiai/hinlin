<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright तऊ 2011 Tony Breeds IBM Corporation
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
 *    Copyright 2010 Ben. Herrenschmidt, IBM Corporation.
 *    Copyright तऊ 2011 David Kleikamp IBM Corporation
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

#घोषणा MAX_RANKS	0x4
#घोषणा DDR3_MR0CF	0x80010011U

अटल अचिन्हित दीर्घ दीर्घ ibm_currituck_memsize;
अटल अचिन्हित दीर्घ दीर्घ ibm_currituck_detect_memsize(व्योम)
अणु
	u32 reg;
	अचिन्हित i;
	अचिन्हित दीर्घ दीर्घ memsize = 0;

	क्रम(i = 0; i < MAX_RANKS; i++)अणु
		reg = mfdcrx(DDR3_MR0CF + i);

		अगर (!(reg & 1))
			जारी;

		reg &= 0x0000f000;
		reg >>= 12;
		memsize += (0x800000ULL << reg);
	पूर्ण

	वापस memsize;
पूर्ण

अटल व्योम ibm_currituck_fixups(व्योम)
अणु
	व्योम *devp = finddevice("/");
	u32 dma_ranges[7];

	dt_fixup_memory(0x0ULL,  ibm_currituck_memsize);

	जबतक ((devp = find_node_by_devtype(devp, "pci"))) अणु
		अगर (getprop(devp, "dma-ranges", dma_ranges, माप(dma_ranges)) < 0) अणु
			म_लिखो("%s: Failed to get dma-ranges\r\n", __func__);
			जारी;
		पूर्ण

		dma_ranges[5] = ibm_currituck_memsize >> 32;
		dma_ranges[6] = ibm_currituck_memsize & 0xffffffffUL;

		setprop(devp, "dma-ranges", dma_ranges, माप(dma_ranges));
	पूर्ण
पूर्ण

#घोषणा SPRN_PIR	0x11E	/* Processor Identअगरication Register */
व्योम platक्रमm_init(व्योम)
अणु
	अचिन्हित दीर्घ end_of_ram, avail_ram;
	u32 pir_reg;
	पूर्णांक node, size;
	स्थिर u32 *समयbase;

	ibm_currituck_memsize = ibm_currituck_detect_memsize();
	अगर (ibm_currituck_memsize >> 32)
		end_of_ram = ~0UL;
	अन्यथा
		end_of_ram = ibm_currituck_memsize;
	avail_ram = end_of_ram - (अचिन्हित दीर्घ)_end;

	simple_alloc_init(_end, avail_ram, 128, 64);
	platक्रमm_ops.fixups = ibm_currituck_fixups;
	platक्रमm_ops.निकास = ibm44x_dbcr_reset;
	pir_reg = mfspr(SPRN_PIR);

	/* Make sure FDT blob is sane */
	अगर (fdt_check_header(_dtb_start) != 0)
		fatal("Invalid device tree blob\n");

	node = fdt_node_offset_by_prop_value(_dtb_start, -1, "device_type",
	                                     "cpu", माप("cpu"));
	अगर (!node)
		fatal("Cannot find cpu node\n");
	समयbase = fdt_getprop(_dtb_start, node, "timebase-frequency", &size);
	अगर (समयbase && (size == 4))
		समयbase_period_ns = 1000000000 / *समयbase;

	fdt_set_boot_cpuid_phys(_dtb_start, pir_reg);
	fdt_init(_dtb_start);

	serial_console_init();
पूर्ण
