<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * memory.c: memory initialisation code.
 *
 * Copyright (C) 1998 Harald Koerfgen, Frieder Streffer and Paul M. Antoine
 * Copyright (C) 2000, 2002  Maciej W. Rozycki
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/dec/machtype.h>
#समावेश <यंत्र/dec/prom.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>


अस्थिर अचिन्हित दीर्घ mem_err;		/* So we know an error occurred */

/*
 * Probe memory in 4MB chunks, रुकोing क्रम an error to tell us we've fallen
 * off the end of real memory.  Only suitable क्रम the 2100/3100's (PMAX).
 */

#घोषणा CHUNK_SIZE 0x400000

अटल __init व्योम pmax_setup_memory_region(व्योम)
अणु
	अस्थिर अचिन्हित अक्षर *memory_page, dummy;
	अक्षर old_handler[0x80];
	बाह्य अक्षर genexcept_early;

	/* Install exception handler */
	स_नकल(&old_handler, (व्योम *)(CKSEG0 + 0x80), 0x80);
	स_नकल((व्योम *)(CKSEG0 + 0x80), &genexcept_early, 0x80);

	/* पढ़ो unmapped and uncached (KSEG1)
	 * DECstations have at least 4MB RAM
	 * Assume less than 480MB of RAM, as this is max क्रम 5000/2xx
	 * FIXME this should be replaced by the first मुक्त page!
	 */
	क्रम (memory_page = (अचिन्हित अक्षर *)CKSEG1 + CHUNK_SIZE;
	     mem_err == 0 && memory_page < (अचिन्हित अक्षर *)CKSEG1 + 0x1e00000;
	     memory_page += CHUNK_SIZE) अणु
		dummy = *memory_page;
	पूर्ण
	स_नकल((व्योम *)(CKSEG0 + 0x80), &old_handler, 0x80);

	memblock_add(0, (अचिन्हित दीर्घ)memory_page - CKSEG1 - CHUNK_SIZE);
पूर्ण

/*
 * Use the REX prom calls to get hold of the memory biपंचांगap, and thence
 * determine memory size.
 */
अटल __init व्योम rex_setup_memory_region(व्योम)
अणु
	पूर्णांक i, biपंचांगap_size;
	अचिन्हित दीर्घ mem_start = 0, mem_size = 0;
	memmap *bm;

	/* some मुक्त 64k */
	bm = (memmap *)CKSEG0ADDR(0x28000);

	biपंचांगap_size = rex_getbiपंचांगap(bm);

	क्रम (i = 0; i < biपंचांगap_size; i++) अणु
		/* FIXME: very simplistically only add full sets of pages */
		अगर (bm->biपंचांगap[i] == 0xff)
			mem_size += (8 * bm->pagesize);
		अन्यथा अगर (!mem_size)
			mem_start += (8 * bm->pagesize);
		अन्यथा अणु
			memblock_add(mem_start, mem_size);
			mem_start += mem_size + (8 * bm->pagesize);
			mem_size = 0;
		पूर्ण
	पूर्ण
	अगर (mem_size)
		memblock_add(mem_start, mem_size);
पूर्ण

व्योम __init prom_meminit(u32 magic)
अणु
	अगर (!prom_is_rex(magic))
		pmax_setup_memory_region();
	अन्यथा
		rex_setup_memory_region();
पूर्ण

व्योम __init prom_मुक्त_prom_memory(व्योम)
अणु
	अचिन्हित दीर्घ end;

	/*
	 * Free everything below the kernel itself but leave
	 * the first page reserved क्रम the exception handlers.
	 */

#अगर IS_ENABLED(CONFIG_DECLANCE)
	/*
	 * Leave 128 KB reserved क्रम Lance memory क्रम
	 * IOASIC DECstations.
	 *
	 * XXX: save this address क्रम use in dec_lance.c?
	 */
	अगर (IOASIC)
		end = __pa(&_text) - 0x00020000;
	अन्यथा
#पूर्ण_अगर
		end = __pa(&_text);

	मुक्त_init_pages("unused PROM memory", PAGE_SIZE, end);
पूर्ण
