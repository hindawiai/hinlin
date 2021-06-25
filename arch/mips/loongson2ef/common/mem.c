<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */
#समावेश <linux/fs.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/bootinfo.h>

#समावेश <loongson.h>
#समावेश <स्मृति.स>
#समावेश <pci.h>


u32 memsize, highmemsize;

व्योम __init prom_init_memory(व्योम)
अणु
	memblock_add(0x0, (memsize << 20));

#अगर_घोषित CONFIG_CPU_SUPPORTS_ADDRWINCFG
	अणु
		पूर्णांक bit;

		bit = fls(memsize + highmemsize);
		अगर (bit != ffs(memsize + highmemsize))
			bit += 20;
		अन्यथा
			bit = bit + 20 - 1;

		/* set cpu winकरोw3 to map CPU to DDR: 2G -> 2G */
		LOONGSON_ADDRWIN_CPUTODDR(ADDRWIN_WIN3, 0x80000000ul,
					  0x80000000ul, (1 << bit));
		mmiowb();
	पूर्ण
#पूर्ण_अगर /* !CONFIG_CPU_SUPPORTS_ADDRWINCFG */

#अगर_घोषित CONFIG_64BIT
	अगर (highmemsize > 0)
		memblock_add(LOONGSON_HIGHMEM_START, highmemsize << 20);
#पूर्ण_अगर /* !CONFIG_64BIT */
पूर्ण
