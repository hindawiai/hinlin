<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/m68k/kernel/sys_m68k.c
 *
 * This file contains various अक्रमom प्रणाली calls that
 * have a non-standard calling sequence on the Linux/m68k
 * platक्रमm.
 */

#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/smp.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/mman.h>
#समावेश <linux/file.h>
#समावेश <linux/ipc.h>

#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cachectl.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/cacheflush.h>

#अगर_घोषित CONFIG_MMU

#समावेश <यंत्र/tlb.h>

यंत्रlinkage पूर्णांक करो_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
			     अचिन्हित दीर्घ error_code);

यंत्रlinkage दीर्घ sys_mmap2(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
	अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
	अचिन्हित दीर्घ fd, अचिन्हित दीर्घ pgoff)
अणु
	/*
	 * This is wrong क्रम sun3 - there PAGE_SIZE is 8Kb,
	 * so we need to shअगरt the argument करोwn by 1; m68k mmap64(3)
	 * (in libc) expects the last argument of mmap2 in 4Kb units.
	 */
	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd, pgoff);
पूर्ण

/* Convert भव (user) address VADDR to physical address PADDR */
#घोषणा virt_to_phys_040(vaddr)						\
(अणु									\
  अचिन्हित दीर्घ _mmusr, _paddr;						\
									\
  __यंत्र__ __अस्थिर__ (".chip 68040\n\t"				\
			"ptestr (%1)\n\t"				\
			"movec %%mmusr,%0\n\t"				\
			".chip 68k"					\
			: "=r" (_mmusr)					\
			: "a" (vaddr));					\
  _paddr = (_mmusr & MMU_R_040) ? (_mmusr & PAGE_MASK) : 0;		\
  _paddr;								\
पूर्ण)

अटल अंतरभूत पूर्णांक
cache_flush_040 (अचिन्हित दीर्घ addr, पूर्णांक scope, पूर्णांक cache, अचिन्हित दीर्घ len)
अणु
  अचिन्हित दीर्घ paddr, i;

  चयन (scope)
    अणु
    हाल FLUSH_SCOPE_ALL:
      चयन (cache)
	अणु
	हाल FLUSH_CACHE_DATA:
	  /* This nop is needed क्रम some broken versions of the 68040.  */
	  __यंत्र__ __अस्थिर__ ("nop\n\t"
				".chip 68040\n\t"
				"cpusha %dc\n\t"
				".chip 68k");
	  अवरोध;
	हाल FLUSH_CACHE_INSN:
	  __यंत्र__ __अस्थिर__ ("nop\n\t"
				".chip 68040\n\t"
				"cpusha %ic\n\t"
				".chip 68k");
	  अवरोध;
	शेष:
	हाल FLUSH_CACHE_BOTH:
	  __यंत्र__ __अस्थिर__ ("nop\n\t"
				".chip 68040\n\t"
				"cpusha %bc\n\t"
				".chip 68k");
	  अवरोध;
	पूर्ण
      अवरोध;

    हाल FLUSH_SCOPE_LINE:
      /* Find the physical address of the first mapped page in the
	 address range.  */
      अगर ((paddr = virt_to_phys_040(addr))) अणु
        paddr += addr & ~(PAGE_MASK | 15);
        len = (len + (addr & 15) + 15) >> 4;
      पूर्ण अन्यथा अणु
	अचिन्हित दीर्घ पंचांगp = PAGE_SIZE - (addr & ~PAGE_MASK);

	अगर (len <= पंचांगp)
	  वापस 0;
	addr += पंचांगp;
	len -= पंचांगp;
	पंचांगp = PAGE_SIZE;
	क्रम (;;)
	  अणु
	    अगर ((paddr = virt_to_phys_040(addr)))
	      अवरोध;
	    अगर (len <= पंचांगp)
	      वापस 0;
	    addr += पंचांगp;
	    len -= पंचांगp;
	  पूर्ण
	len = (len + 15) >> 4;
      पूर्ण
      i = (PAGE_SIZE - (paddr & ~PAGE_MASK)) >> 4;
      जबतक (len--)
	अणु
	  चयन (cache)
	    अणु
	    हाल FLUSH_CACHE_DATA:
	      __यंत्र__ __अस्थिर__ ("nop\n\t"
				    ".chip 68040\n\t"
				    "cpushl %%dc,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      अवरोध;
	    हाल FLUSH_CACHE_INSN:
	      __यंत्र__ __अस्थिर__ ("nop\n\t"
				    ".chip 68040\n\t"
				    "cpushl %%ic,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      अवरोध;
	    शेष:
	    हाल FLUSH_CACHE_BOTH:
	      __यंत्र__ __अस्थिर__ ("nop\n\t"
				    ".chip 68040\n\t"
				    "cpushl %%bc,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      अवरोध;
	    पूर्ण
	  अगर (!--i && len)
	    अणु
	      /*
	       * No need to page align here since it is करोne by
	       * virt_to_phys_040().
	       */
	      addr += PAGE_SIZE;
	      i = PAGE_SIZE / 16;
	      /* Recompute physical address when crossing a page
	         boundary. */
	      क्रम (;;)
		अणु
		  अगर ((paddr = virt_to_phys_040(addr)))
		    अवरोध;
		  अगर (len <= i)
		    वापस 0;
		  len -= i;
		  addr += PAGE_SIZE;
		पूर्ण
	    पूर्ण
	  अन्यथा
	    paddr += 16;
	पूर्ण
      अवरोध;

    शेष:
    हाल FLUSH_SCOPE_PAGE:
      len += (addr & ~PAGE_MASK) + (PAGE_SIZE - 1);
      क्रम (len >>= PAGE_SHIFT; len--; addr += PAGE_SIZE)
	अणु
	  अगर (!(paddr = virt_to_phys_040(addr)))
	    जारी;
	  चयन (cache)
	    अणु
	    हाल FLUSH_CACHE_DATA:
	      __यंत्र__ __अस्थिर__ ("nop\n\t"
				    ".chip 68040\n\t"
				    "cpushp %%dc,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      अवरोध;
	    हाल FLUSH_CACHE_INSN:
	      __यंत्र__ __अस्थिर__ ("nop\n\t"
				    ".chip 68040\n\t"
				    "cpushp %%ic,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      अवरोध;
	    शेष:
	    हाल FLUSH_CACHE_BOTH:
	      __यंत्र__ __अस्थिर__ ("nop\n\t"
				    ".chip 68040\n\t"
				    "cpushp %%bc,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      अवरोध;
	    पूर्ण
	पूर्ण
      अवरोध;
    पूर्ण
  वापस 0;
पूर्ण

#घोषणा virt_to_phys_060(vaddr)				\
(अणु							\
  अचिन्हित दीर्घ paddr;					\
  __यंत्र__ __अस्थिर__ (".chip 68060\n\t"		\
			"plpar (%0)\n\t"		\
			".chip 68k"			\
			: "=a" (paddr)			\
			: "0" (vaddr));			\
  (paddr); /* XXX */					\
पूर्ण)

अटल अंतरभूत पूर्णांक
cache_flush_060 (अचिन्हित दीर्घ addr, पूर्णांक scope, पूर्णांक cache, अचिन्हित दीर्घ len)
अणु
  अचिन्हित दीर्घ paddr, i;

  /*
   * 68060 manual says:
   *  cpush %dc : flush DC, reमुख्यs valid (with our %cacr setup)
   *  cpush %ic : invalidate IC
   *  cpush %bc : flush DC + invalidate IC
   */
  चयन (scope)
    अणु
    हाल FLUSH_SCOPE_ALL:
      चयन (cache)
	अणु
	हाल FLUSH_CACHE_DATA:
	  __यंत्र__ __अस्थिर__ (".chip 68060\n\t"
				"cpusha %dc\n\t"
				".chip 68k");
	  अवरोध;
	हाल FLUSH_CACHE_INSN:
	  __यंत्र__ __अस्थिर__ (".chip 68060\n\t"
				"cpusha %ic\n\t"
				".chip 68k");
	  अवरोध;
	शेष:
	हाल FLUSH_CACHE_BOTH:
	  __यंत्र__ __अस्थिर__ (".chip 68060\n\t"
				"cpusha %bc\n\t"
				".chip 68k");
	  अवरोध;
	पूर्ण
      अवरोध;

    हाल FLUSH_SCOPE_LINE:
      /* Find the physical address of the first mapped page in the
	 address range.  */
      len += addr & 15;
      addr &= -16;
      अगर (!(paddr = virt_to_phys_060(addr))) अणु
	अचिन्हित दीर्घ पंचांगp = PAGE_SIZE - (addr & ~PAGE_MASK);

	अगर (len <= पंचांगp)
	  वापस 0;
	addr += पंचांगp;
	len -= पंचांगp;
	पंचांगp = PAGE_SIZE;
	क्रम (;;)
	  अणु
	    अगर ((paddr = virt_to_phys_060(addr)))
	      अवरोध;
	    अगर (len <= पंचांगp)
	      वापस 0;
	    addr += पंचांगp;
	    len -= पंचांगp;
	  पूर्ण
      पूर्ण
      len = (len + 15) >> 4;
      i = (PAGE_SIZE - (paddr & ~PAGE_MASK)) >> 4;
      जबतक (len--)
	अणु
	  चयन (cache)
	    अणु
	    हाल FLUSH_CACHE_DATA:
	      __यंत्र__ __अस्थिर__ (".chip 68060\n\t"
				    "cpushl %%dc,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      अवरोध;
	    हाल FLUSH_CACHE_INSN:
	      __यंत्र__ __अस्थिर__ (".chip 68060\n\t"
				    "cpushl %%ic,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      अवरोध;
	    शेष:
	    हाल FLUSH_CACHE_BOTH:
	      __यंत्र__ __अस्थिर__ (".chip 68060\n\t"
				    "cpushl %%bc,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      अवरोध;
	    पूर्ण
	  अगर (!--i && len)
	    अणु

	      /*
	       * We just want to jump to the first cache line
	       * in the next page.
	       */
	      addr += PAGE_SIZE;
	      addr &= PAGE_MASK;

	      i = PAGE_SIZE / 16;
	      /* Recompute physical address when crossing a page
	         boundary. */
	      क्रम (;;)
	        अणु
	          अगर ((paddr = virt_to_phys_060(addr)))
	            अवरोध;
	          अगर (len <= i)
	            वापस 0;
	          len -= i;
	          addr += PAGE_SIZE;
	        पूर्ण
	    पूर्ण
	  अन्यथा
	    paddr += 16;
	पूर्ण
      अवरोध;

    शेष:
    हाल FLUSH_SCOPE_PAGE:
      len += (addr & ~PAGE_MASK) + (PAGE_SIZE - 1);
      addr &= PAGE_MASK;	/* Workaround क्रम bug in some
				   revisions of the 68060 */
      क्रम (len >>= PAGE_SHIFT; len--; addr += PAGE_SIZE)
	अणु
	  अगर (!(paddr = virt_to_phys_060(addr)))
	    जारी;
	  चयन (cache)
	    अणु
	    हाल FLUSH_CACHE_DATA:
	      __यंत्र__ __अस्थिर__ (".chip 68060\n\t"
				    "cpushp %%dc,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      अवरोध;
	    हाल FLUSH_CACHE_INSN:
	      __यंत्र__ __अस्थिर__ (".chip 68060\n\t"
				    "cpushp %%ic,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      अवरोध;
	    शेष:
	    हाल FLUSH_CACHE_BOTH:
	      __यंत्र__ __अस्थिर__ (".chip 68060\n\t"
				    "cpushp %%bc,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      अवरोध;
	    पूर्ण
	पूर्ण
      अवरोध;
    पूर्ण
  वापस 0;
पूर्ण

/* sys_cacheflush -- flush (part of) the processor cache.  */
यंत्रlinkage पूर्णांक
sys_cacheflush (अचिन्हित दीर्घ addr, पूर्णांक scope, पूर्णांक cache, अचिन्हित दीर्घ len)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (scope < FLUSH_SCOPE_LINE || scope > FLUSH_SCOPE_ALL ||
	    cache & ~FLUSH_CACHE_BOTH)
		जाओ out;

	अगर (scope == FLUSH_SCOPE_ALL) अणु
		/* Only the superuser may explicitly flush the whole cache. */
		ret = -EPERM;
		अगर (!capable(CAP_SYS_ADMIN))
			जाओ out;

		mmap_पढ़ो_lock(current->mm);
	पूर्ण अन्यथा अणु
		काष्ठा vm_area_काष्ठा *vma;

		/* Check क्रम overflow.  */
		अगर (addr + len < addr)
			जाओ out;

		/*
		 * Verअगरy that the specअगरied address region actually beदीर्घs
		 * to this process.
		 */
		mmap_पढ़ो_lock(current->mm);
		vma = find_vma(current->mm, addr);
		अगर (!vma || addr < vma->vm_start || addr + len > vma->vm_end)
			जाओ out_unlock;
	पूर्ण

	अगर (CPU_IS_020_OR_030) अणु
		अगर (scope == FLUSH_SCOPE_LINE && len < 256) अणु
			अचिन्हित दीर्घ cacr;
			__यंत्र__ ("movec %%cacr, %0" : "=r" (cacr));
			अगर (cache & FLUSH_CACHE_INSN)
				cacr |= 4;
			अगर (cache & FLUSH_CACHE_DATA)
				cacr |= 0x400;
			len >>= 2;
			जबतक (len--) अणु
				__यंत्र__ __अस्थिर__ ("movec %1, %%caar\n\t"
						      "movec %0, %%cacr"
						      : /* no outमाला_दो */
						      : "r" (cacr), "r" (addr));
				addr += 4;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Flush the whole cache, even अगर page granularity requested. */
			अचिन्हित दीर्घ cacr;
			__यंत्र__ ("movec %%cacr, %0" : "=r" (cacr));
			अगर (cache & FLUSH_CACHE_INSN)
				cacr |= 8;
			अगर (cache & FLUSH_CACHE_DATA)
				cacr |= 0x800;
			__यंत्र__ __अस्थिर__ ("movec %0, %%cacr" : : "r" (cacr));
		पूर्ण
		ret = 0;
		जाओ out_unlock;
	पूर्ण अन्यथा अणु
	    /*
	     * 040 or 060: करोn't blindly trust 'scope', someone could
	     * try to flush a few megs of memory.
	     */

	    अगर (len>=3*PAGE_SIZE && scope<FLUSH_SCOPE_PAGE)
	        scope=FLUSH_SCOPE_PAGE;
	    अगर (len>=10*PAGE_SIZE && scope<FLUSH_SCOPE_ALL)
	        scope=FLUSH_SCOPE_ALL;
	    अगर (CPU_IS_040) अणु
		ret = cache_flush_040 (addr, scope, cache, len);
	    पूर्ण अन्यथा अगर (CPU_IS_060) अणु
		ret = cache_flush_060 (addr, scope, cache, len);
	    पूर्ण
	पूर्ण
out_unlock:
	mmap_पढ़ो_unlock(current->mm);
out:
	वापस ret;
पूर्ण

/* This syscall माला_लो its arguments in A0 (mem), D2 (oldval) and
   D1 (newval).  */
यंत्रlinkage पूर्णांक
sys_atomic_cmpxchg_32(अचिन्हित दीर्घ newval, पूर्णांक oldval, पूर्णांक d3, पूर्णांक d4, पूर्णांक d5,
		      अचिन्हित दीर्घ __user * mem)
अणु
	/* This was borrowed from ARM's implementation.  */
	क्रम (;;) अणु
		काष्ठा mm_काष्ठा *mm = current->mm;
		pgd_t *pgd;
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;
		pte_t *pte;
		spinlock_t *ptl;
		अचिन्हित दीर्घ mem_value;

		mmap_पढ़ो_lock(mm);
		pgd = pgd_offset(mm, (अचिन्हित दीर्घ)mem);
		अगर (!pgd_present(*pgd))
			जाओ bad_access;
		p4d = p4d_offset(pgd, (अचिन्हित दीर्घ)mem);
		अगर (!p4d_present(*p4d))
			जाओ bad_access;
		pud = pud_offset(p4d, (अचिन्हित दीर्घ)mem);
		अगर (!pud_present(*pud))
			जाओ bad_access;
		pmd = pmd_offset(pud, (अचिन्हित दीर्घ)mem);
		अगर (!pmd_present(*pmd))
			जाओ bad_access;
		pte = pte_offset_map_lock(mm, pmd, (अचिन्हित दीर्घ)mem, &ptl);
		अगर (!pte_present(*pte) || !pte_dirty(*pte)
		    || !pte_ग_लिखो(*pte)) अणु
			pte_unmap_unlock(pte, ptl);
			जाओ bad_access;
		पूर्ण

		/*
		 * No need to check क्रम EFAULT; we know that the page is
		 * present and writable.
		 */
		__get_user(mem_value, mem);
		अगर (mem_value == oldval)
			__put_user(newval, mem);

		pte_unmap_unlock(pte, ptl);
		mmap_पढ़ो_unlock(mm);
		वापस mem_value;

	      bad_access:
		mmap_पढ़ो_unlock(mm);
		/* This is not necessarily a bad access, we can get here अगर
		   a memory we're trying to ग_लिखो to should be copied-on-ग_लिखो.
		   Make the kernel करो the necessary page stuff, then re-iterate.
		   Simulate a ग_लिखो access fault to करो that.  */
		अणु
			/* The first argument of the function corresponds to
			   D1, which is the first field of काष्ठा pt_regs.  */
			काष्ठा pt_regs *fp = (काष्ठा pt_regs *)&newval;

			/* '3' is an RMW flag.  */
			अगर (करो_page_fault(fp, (अचिन्हित दीर्घ)mem, 3))
				/* If the करो_page_fault() failed, we करोn't
				   have anything meaningful to वापस.
				   There should be a संक_अंश pending क्रम
				   the process.  */
				वापस 0xdeadbeef;
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा

/* sys_cacheflush -- flush (part of) the processor cache.  */
यंत्रlinkage पूर्णांक
sys_cacheflush (अचिन्हित दीर्घ addr, पूर्णांक scope, पूर्णांक cache, अचिन्हित दीर्घ len)
अणु
	flush_cache_all();
	वापस 0;
पूर्ण

/* This syscall माला_लो its arguments in A0 (mem), D2 (oldval) and
   D1 (newval).  */
यंत्रlinkage पूर्णांक
sys_atomic_cmpxchg_32(अचिन्हित दीर्घ newval, पूर्णांक oldval, पूर्णांक d3, पूर्णांक d4, पूर्णांक d5,
		      अचिन्हित दीर्घ __user * mem)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ mem_value;

	mmap_पढ़ो_lock(mm);

	mem_value = *mem;
	अगर (mem_value == oldval)
		*mem = newval;

	mmap_पढ़ो_unlock(mm);
	वापस mem_value;
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU */

यंत्रlinkage पूर्णांक sys_getpagesize(व्योम)
अणु
	वापस PAGE_SIZE;
पूर्ण

यंत्रlinkage अचिन्हित दीर्घ sys_get_thपढ़ो_area(व्योम)
अणु
	वापस current_thपढ़ो_info()->tp_value;
पूर्ण

यंत्रlinkage पूर्णांक sys_set_thपढ़ो_area(अचिन्हित दीर्घ tp)
अणु
	current_thपढ़ो_info()->tp_value = tp;
	वापस 0;
पूर्ण

यंत्रlinkage पूर्णांक sys_atomic_barrier(व्योम)
अणु
	/* no code needed क्रम uniprocs */
	वापस 0;
पूर्ण
