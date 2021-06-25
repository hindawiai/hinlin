<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/m68k/mm/cache.c
 *
 *  Inकाष्ठाion cache handling
 *
 *  Copyright (C) 1995  Hamish Macकरोnald
 */

#समावेश <linux/module.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/traps.h>


अटल अचिन्हित दीर्घ virt_to_phys_slow(अचिन्हित दीर्घ vaddr)
अणु
	अगर (CPU_IS_060) अणु
		अचिन्हित दीर्घ paddr;

		/* The PLPAR inकाष्ठाion causes an access error अगर the translation
		 * is not possible. To catch this we use the same exception mechanism
		 * as क्रम user space accesses in <यंत्र/uaccess.h>. */
		यंत्र अस्थिर (".chip 68060\n"
			      "1: plpar (%0)\n"
			      ".chip 68k\n"
			      "2:\n"
			      ".section .fixup,\"ax\"\n"
			      "   .even\n"
			      "3: sub.l %0,%0\n"
			      "   jra 2b\n"
			      ".previous\n"
			      ".section __ex_table,\"a\"\n"
			      "   .align 4\n"
			      "   .long 1b,3b\n"
			      ".previous"
			      : "=a" (paddr)
			      : "0" (vaddr));
		वापस paddr;
	पूर्ण अन्यथा अगर (CPU_IS_040) अणु
		अचिन्हित दीर्घ mmusr;

		यंत्र अस्थिर (".chip 68040\n\t"
			      "ptestr (%1)\n\t"
			      "movec %%mmusr, %0\n\t"
			      ".chip 68k"
			      : "=r" (mmusr)
			      : "a" (vaddr));

		अगर (mmusr & MMU_R_040)
			वापस (mmusr & PAGE_MASK) | (vaddr & ~PAGE_MASK);
	पूर्ण अन्यथा अणु
		अचिन्हित लघु mmusr;
		अचिन्हित दीर्घ *descaddr;

		यंत्र अस्थिर ("ptestr %3,%2@,#7,%0\n\t"
			      "pmove %%psr,%1"
			      : "=a&" (descaddr), "=m" (mmusr)
			      : "a" (vaddr), "d" (get_fs().seg));
		अगर (mmusr & (MMU_I|MMU_B|MMU_L))
			वापस 0;
		descaddr = phys_to_virt((अचिन्हित दीर्घ)descaddr);
		चयन (mmusr & MMU_NUM) अणु
		हाल 1:
			वापस (*descaddr & 0xfe000000) | (vaddr & 0x01ffffff);
		हाल 2:
			वापस (*descaddr & 0xfffc0000) | (vaddr & 0x0003ffff);
		हाल 3:
			वापस (*descaddr & PAGE_MASK) | (vaddr & ~PAGE_MASK);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Push n pages at kernel भव address and clear the icache */
/* RZ: use cpush %bc instead of cpush %dc, cinv %ic */
व्योम flush_icache_user_range(अचिन्हित दीर्घ address, अचिन्हित दीर्घ endaddr)
अणु
	अगर (CPU_IS_COLDFIRE) अणु
		अचिन्हित दीर्घ start, end;
		start = address & ICACHE_SET_MASK;
		end = endaddr & ICACHE_SET_MASK;
		अगर (start > end) अणु
			flush_cf_icache(0, end);
			end = ICACHE_MAX_ADDR;
		पूर्ण
		flush_cf_icache(start, end);
	पूर्ण अन्यथा अगर (CPU_IS_040_OR_060) अणु
		address &= PAGE_MASK;

		करो अणु
			यंत्र अस्थिर ("nop\n\t"
				      ".chip 68040\n\t"
				      "cpushp %%bc,(%0)\n\t"
				      ".chip 68k"
				      : : "a" (virt_to_phys_slow(address)));
			address += PAGE_SIZE;
		पूर्ण जबतक (address < endaddr);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ पंचांगp;
		यंत्र अस्थिर ("movec %%cacr,%0\n\t"
			      "orw %1,%0\n\t"
			      "movec %0,%%cacr"
			      : "=&d" (पंचांगp)
			      : "di" (FLUSH_I));
	पूर्ण
पूर्ण

व्योम flush_icache_range(अचिन्हित दीर्घ address, अचिन्हित दीर्घ endaddr)
अणु
	mm_segment_t old_fs = get_fs();

	set_fs(KERNEL_DS);
	flush_icache_user_range(address, endaddr);
	set_fs(old_fs);
पूर्ण
EXPORT_SYMBOL(flush_icache_range);

व्योम flush_icache_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			     अचिन्हित दीर्घ addr, पूर्णांक len)
अणु
	अगर (CPU_IS_COLDFIRE) अणु
		अचिन्हित दीर्घ start, end;
		start = addr & ICACHE_SET_MASK;
		end = (addr + len) & ICACHE_SET_MASK;
		अगर (start > end) अणु
			flush_cf_icache(0, end);
			end = ICACHE_MAX_ADDR;
		पूर्ण
		flush_cf_icache(start, end);

	पूर्ण अन्यथा अगर (CPU_IS_040_OR_060) अणु
		यंत्र अस्थिर ("nop\n\t"
			      ".chip 68040\n\t"
			      "cpushp %%bc,(%0)\n\t"
			      ".chip 68k"
			      : : "a" (page_to_phys(page)));
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ पंचांगp;
		यंत्र अस्थिर ("movec %%cacr,%0\n\t"
			      "orw %1,%0\n\t"
			      "movec %0,%%cacr"
			      : "=&d" (पंचांगp)
			      : "di" (FLUSH_I));
	पूर्ण
पूर्ण

