<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright तऊ 2013 Tony Breeds IBM Corporation
 * Copyright तऊ 2013 Alistair Popple IBM Corporation
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
#समावेश "stdlib.h"
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

#घोषणा SPRN_PIR	0x11E	/* Processor Identअगरication Register */
#घोषणा USERDATA_LEN	256	/* Length of userdata passed in by PIBS */
#घोषणा MAX_RANKS	0x4
#घोषणा DDR3_MR0CF	0x80010011U
#घोषणा CCTL0_MCO2	0x8000080FU
#घोषणा CCTL0_MCO3	0x80000810U
#घोषणा CCTL0_MCO4	0x80000811U
#घोषणा CCTL0_MCO5	0x80000812U
#घोषणा CCTL0_MCO6	0x80000813U

अटल अचिन्हित दीर्घ दीर्घ ibm_akebono_memsize;
अटल दीर्घ दीर्घ अचिन्हित mac_addr;

अटल अचिन्हित दीर्घ दीर्घ ibm_akebono_detect_memsize(व्योम)
अणु
	u32 reg;
	अचिन्हित i;
	अचिन्हित दीर्घ दीर्घ memsize = 0;

	क्रम (i = 0; i < MAX_RANKS; i++) अणु
		reg = mfdcrx(DDR3_MR0CF + i);

		अगर (!(reg & 1))
			जारी;

		reg &= 0x0000f000;
		reg >>= 12;
		memsize += (0x800000ULL << reg);
	पूर्ण

	वापस memsize;
पूर्ण

अटल व्योम ibm_akebono_fixups(व्योम)
अणु
	व्योम *emac;
	u32 reg;

	dt_fixup_memory(0x0ULL,  ibm_akebono_memsize);

	/* Fixup the SD समयout frequency */
	mtdcrx(CCTL0_MCO4, 0x1);

	/* Disable SD high-speed mode (which seems to be broken) */
	reg = mfdcrx(CCTL0_MCO2) & ~0x2;
	mtdcrx(CCTL0_MCO2, reg);

	/* Set the MAC address */
	emac = finddevice("/plb/opb/ethernet");
	अगर (emac > 0) अणु
		अगर (mac_addr)
			setprop(emac, "local-mac-address",
				((u8 *) &mac_addr) + 2 , 6);
	पूर्ण
पूर्ण

व्योम platक्रमm_init(अक्षर *userdata)
अणु
	अचिन्हित दीर्घ end_of_ram, avail_ram;
	u32 pir_reg;
	पूर्णांक node, size;
	स्थिर u32 *समयbase;
	पूर्णांक len, i, userdata_len;
	अक्षर *end;

	userdata[USERDATA_LEN - 1] = '\0';
	userdata_len = म_माप(userdata);
	क्रम (i = 0; i < userdata_len - 15; i++) अणु
		अगर (म_भेदन(&userdata[i], "local-mac-addr=", 15) == 0) अणु
			अगर (i > 0 && userdata[i - 1] != ' ') अणु
				/* We've only found a substring ending
				 * with local-mac-addr so this isn't
				 * our mac address. */
				जारी;
			पूर्ण

			mac_addr = म_से_अदीर्घl(&userdata[i + 15], &end, 16);

			/* Remove the "local-mac-addr=<...>" from the kernel
			 * command line, including the tailing space अगर
			 * present. */
			अगर (*end == ' ')
				end++;

			len = ((पूर्णांक) end) - ((पूर्णांक) &userdata[i]);
			स_हटाओ(&userdata[i], end,
				userdata_len - (len + i) + 1);
			अवरोध;
		पूर्ण
	पूर्ण

	loader_info.cmdline = userdata;
	loader_info.cmdline_len = 256;

	ibm_akebono_memsize = ibm_akebono_detect_memsize();
	अगर (ibm_akebono_memsize >> 32)
		end_of_ram = ~0UL;
	अन्यथा
		end_of_ram = ibm_akebono_memsize;
	avail_ram = end_of_ram - (अचिन्हित दीर्घ)_end;

	simple_alloc_init(_end, avail_ram, 128, 64);
	platक्रमm_ops.fixups = ibm_akebono_fixups;
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
