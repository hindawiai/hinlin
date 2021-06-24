<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 Keith M Wesolowski
 * Copyright (C) 2005 Ilya A. Volynets (Total Knowledge)
 */
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/ip32/crime.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/page.h>

बाह्य व्योम crime_init(व्योम);

व्योम __init prom_meminit(व्योम)
अणु
	u64 base, size;
	पूर्णांक bank;

	crime_init();

	क्रम (bank=0; bank < CRIME_MAXBANKS; bank++) अणु
		u64 bankctl = crime->bank_ctrl[bank];
		base = (bankctl & CRIME_MEM_BANK_CONTROL_ADDR) << 25;
		अगर (bank != 0 && base == 0)
			जारी;
		size = (bankctl & CRIME_MEM_BANK_CONTROL_SDRAM_SIZE) ? 128 : 32;
		size <<= 20;
		अगर (base + size > (256 << 20))
			base += CRIME_HI_MEM_BASE;

		prपूर्णांकk("CRIME MC: bank %u base 0x%016Lx size %LuMiB\n",
			bank, base, size >> 20);
		memblock_add(base, size);
	पूर्ण
पूर्ण
