<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/mem_detect.h>
#समावेश <यंत्र/sparseस्मृति.स>
#समावेश "compressed/decompressor.h"
#समावेश "boot.h"

काष्ठा mem_detect_info __bootdata(mem_detect);

/* up to 256 storage elements, 1020 subincrements each */
#घोषणा ENTRIES_EXTENDED_MAX						       \
	(256 * (1020 / 2) * माप(काष्ठा mem_detect_block))

/*
 * To aव्योम corrupting old kernel memory during dump, find lowest memory
 * chunk possible either right after the kernel end (decompressed kernel) or
 * after initrd (अगर it is present and there is no hole between the kernel end
 * and initrd)
 */
अटल व्योम *mem_detect_alloc_extended(व्योम)
अणु
	अचिन्हित दीर्घ offset = ALIGN(mem_safe_offset(), माप(u64));

	अगर (IS_ENABLED(CONFIG_BLK_DEV_INITRD) && INITRD_START && INITRD_SIZE &&
	    INITRD_START < offset + ENTRIES_EXTENDED_MAX)
		offset = ALIGN(INITRD_START + INITRD_SIZE, माप(u64));

	वापस (व्योम *)offset;
पूर्ण

अटल काष्ठा mem_detect_block *__get_mem_detect_block_ptr(u32 n)
अणु
	अगर (n < MEM_INLINED_ENTRIES)
		वापस &mem_detect.entries[n];
	अगर (unlikely(!mem_detect.entries_extended))
		mem_detect.entries_extended = mem_detect_alloc_extended();
	वापस &mem_detect.entries_extended[n - MEM_INLINED_ENTRIES];
पूर्ण

/*
 * sequential calls to add_mem_detect_block with adjacent memory areas
 * are merged together पूर्णांकo single memory block.
 */
व्योम add_mem_detect_block(u64 start, u64 end)
अणु
	काष्ठा mem_detect_block *block;

	अगर (mem_detect.count) अणु
		block = __get_mem_detect_block_ptr(mem_detect.count - 1);
		अगर (block->end == start) अणु
			block->end = end;
			वापस;
		पूर्ण
	पूर्ण

	block = __get_mem_detect_block_ptr(mem_detect.count);
	block->start = start;
	block->end = end;
	mem_detect.count++;
पूर्ण

अटल पूर्णांक __diag260(अचिन्हित दीर्घ rx1, अचिन्हित दीर्घ rx2)
अणु
	रेजिस्टर अचिन्हित दीर्घ _rx1 यंत्र("2") = rx1;
	रेजिस्टर अचिन्हित दीर्घ _rx2 यंत्र("3") = rx2;
	रेजिस्टर अचिन्हित दीर्घ _ry यंत्र("4") = 0x10; /* storage configuration */
	पूर्णांक rc = -1;				    /* fail */
	अचिन्हित दीर्घ reg1, reg2;
	psw_t old = S390_lowcore.program_new_psw;

	यंत्र अस्थिर(
		"	epsw	%0,%1\n"
		"	st	%0,%[psw_pgm]\n"
		"	st	%1,%[psw_pgm]+4\n"
		"	larl	%0,1f\n"
		"	stg	%0,%[psw_pgm]+8\n"
		"	diag	%[rx],%[ry],0x260\n"
		"	ipm	%[rc]\n"
		"	srl	%[rc],28\n"
		"1:\n"
		: "=&d" (reg1), "=&a" (reg2),
		  [psw_pgm] "=Q" (S390_lowcore.program_new_psw),
		  [rc] "+&d" (rc), [ry] "+d" (_ry)
		: [rx] "d" (_rx1), "d" (_rx2)
		: "cc", "memory");
	S390_lowcore.program_new_psw = old;
	वापस rc == 0 ? _ry : -1;
पूर्ण

अटल पूर्णांक diag260(व्योम)
अणु
	पूर्णांक rc, i;

	काष्ठा अणु
		अचिन्हित दीर्घ start;
		अचिन्हित दीर्घ end;
	पूर्ण storage_extents[8] __aligned(16); /* VM supports up to 8 extends */

	स_रखो(storage_extents, 0, माप(storage_extents));
	rc = __diag260((अचिन्हित दीर्घ)storage_extents, माप(storage_extents));
	अगर (rc == -1)
		वापस -1;

	क्रम (i = 0; i < min_t(पूर्णांक, rc, ARRAY_SIZE(storage_extents)); i++)
		add_mem_detect_block(storage_extents[i].start, storage_extents[i].end + 1);
	वापस 0;
पूर्ण

अटल पूर्णांक tprot(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ pgm_addr;
	पूर्णांक rc = -EFAULT;
	psw_t old = S390_lowcore.program_new_psw;

	S390_lowcore.program_new_psw.mask = __extract_psw();
	यंत्र अस्थिर(
		"	larl	%[pgm_addr],1f\n"
		"	stg	%[pgm_addr],%[psw_pgm_addr]\n"
		"	tprot	0(%[addr]),0\n"
		"	ipm	%[rc]\n"
		"	srl	%[rc],28\n"
		"1:\n"
		: [pgm_addr] "=&d"(pgm_addr),
		  [psw_pgm_addr] "=Q"(S390_lowcore.program_new_psw.addr),
		  [rc] "+&d"(rc)
		: [addr] "a"(addr)
		: "cc", "memory");
	S390_lowcore.program_new_psw = old;
	वापस rc;
पूर्ण

अटल व्योम search_mem_end(व्योम)
अणु
	अचिन्हित दीर्घ range = 1 << (MAX_PHYSMEM_BITS - 20); /* in 1MB blocks */
	अचिन्हित दीर्घ offset = 0;
	अचिन्हित दीर्घ pivot;

	जबतक (range > 1) अणु
		range >>= 1;
		pivot = offset + range;
		अगर (!tprot(pivot << 20))
			offset = pivot;
	पूर्ण

	add_mem_detect_block(0, (offset + 1) << 20);
पूर्ण

अचिन्हित दीर्घ detect_memory(व्योम)
अणु
	अचिन्हित दीर्घ max_physmem_end;

	sclp_early_get_memsize(&max_physmem_end);

	अगर (!sclp_early_पढ़ो_storage_info()) अणु
		mem_detect.info_source = MEM_DETECT_SCLP_STOR_INFO;
		वापस max_physmem_end;
	पूर्ण

	अगर (!diag260()) अणु
		mem_detect.info_source = MEM_DETECT_DIAG260;
		वापस max_physmem_end;
	पूर्ण

	अगर (max_physmem_end) अणु
		add_mem_detect_block(0, max_physmem_end);
		mem_detect.info_source = MEM_DETECT_SCLP_READ_INFO;
		वापस max_physmem_end;
	पूर्ण

	search_mem_end();
	mem_detect.info_source = MEM_DETECT_BIN_SEARCH;
	वापस get_mem_detect_end();
पूर्ण
