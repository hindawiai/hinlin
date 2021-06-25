<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * PROM library functions क्रम acquiring/using memory descriptors given to
 * us from the YAMON.
 *
 * Copyright (C) 1999,2000,2012  MIPS Technologies, Inc.
 * All rights reserved.
 * Authors: Carsten Langgaard <carstenl@mips.com>
 *          Steven J. Hill <sjhill@mips.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cdmm.h>
#समावेश <यंत्र/maar.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/fw/fw.h>

/* determined physical memory size, not overridden by command line args	 */
अचिन्हित दीर्घ physical_memsize = 0L;

अटल व्योम मुक्त_init_pages_eva_malta(व्योम *begin, व्योम *end)
अणु
	मुक्त_init_pages("unused kernel", __pa_symbol((अचिन्हित दीर्घ *)begin),
			__pa_symbol((अचिन्हित दीर्घ *)end));
पूर्ण

व्योम __init fw_meminit(व्योम)
अणु
	bool eva = IS_ENABLED(CONFIG_EVA);

	मुक्त_init_pages_eva = eva ? मुक्त_init_pages_eva_malta : शून्य;
पूर्ण

phys_addr_t mips_cdmm_phys_base(व्योम)
अणु
	/* This address is "typically unused" */
	वापस 0x1fc10000;
पूर्ण
