<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Bootwrapper क्रम ePAPR compliant firmwares
 *
 * Copyright 2010 David Gibson <david@gibson.dropbear.id.au>, IBM Corporation.
 *
 * Based on earlier bootwrappers by:
 * (c) Benjamin Herrenschmidt <benh@kernel.crashing.org>, IBM Corp,\
 *   and
 * Scott Wood <scottwood@मुक्तscale.com>
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "io.h"
#समावेश <libfdt.h>

BSS_STACK(4096);

#घोषणा EPAPR_SMAGIC	0x65504150
#घोषणा EPAPR_EMAGIC	0x45504150

अटल अचिन्हित epapr_magic;
अटल अचिन्हित दीर्घ ima_size;
अटल अचिन्हित दीर्घ fdt_addr;

अटल व्योम platक्रमm_fixups(व्योम)
अणु
	अगर ((epapr_magic != EPAPR_EMAGIC)
	    && (epapr_magic != EPAPR_SMAGIC))
		fatal("r6 contained 0x%08x instead of ePAPR magic number\n",
		      epapr_magic);

	अगर (ima_size < (अचिन्हित दीर्घ)_end)
		म_लिखो("WARNING: Image loaded outside IMA!"
		       " (_end=%p, ima_size=0x%lx)\n", _end, ima_size);
	अगर (ima_size < fdt_addr)
		म_लिखो("WARNING: Device tree address is outside IMA!"
		       "(fdt_addr=0x%lx, ima_size=0x%lx)\n", fdt_addr,
		       ima_size);
	अगर (ima_size < fdt_addr + fdt_totalsize((व्योम *)fdt_addr))
		म_लिखो("WARNING: Device tree extends outside IMA!"
		       " (fdt_addr=0x%lx, size=0x%x, ima_size=0x%lx\n",
		       fdt_addr, fdt_totalsize((व्योम *)fdt_addr), ima_size);
पूर्ण

व्योम epapr_platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
			 अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	epapr_magic = r6;
	ima_size = r7;
	fdt_addr = r3;

	/* FIXME: we should process reserve entries */

	simple_alloc_init(_end, ima_size - (अचिन्हित दीर्घ)_end, 32, 64);

	fdt_init((व्योम *)fdt_addr);

	serial_console_init();
	platक्रमm_ops.fixups = platक्रमm_fixups;
पूर्ण
