<शैली गुरु>
/*
 * Nios2 TLB handling
 *
 * Copyright (C) 2009, Wind River Systems Inc
 *   Implemented by fredrik.markstrom@gmail.com and ivarholmqvist@gmail.com
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>

#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cpuinfo.h>

#घोषणा TLB_INDEX_MASK		\
	((((1UL << (cpuinfo.tlb_ptr_sz - cpuinfo.tlb_num_ways_log2))) - 1) \
		<< PAGE_SHIFT)

अटल व्योम get_misc_and_pid(अचिन्हित दीर्घ *misc, अचिन्हित दीर्घ *pid)
अणु
	*misc  = RDCTL(CTL_TLBMISC);
	*misc &= (TLBMISC_PID | TLBMISC_WAY);
	*pid  = *misc & TLBMISC_PID;
पूर्ण

/*
 * This provides a PTEADDR value क्रम addr that will cause a TLB miss
 * (fast TLB miss). TLB invalidation replaces entries with this value.
 */
अटल अचिन्हित दीर्घ pteaddr_invalid(अचिन्हित दीर्घ addr)
अणु
	वापस ((addr | 0xC0000000UL) >> PAGE_SHIFT) << 2;
पूर्ण

/*
 * This one is only used क्रम pages with the global bit set so we करोn't care
 * much about the ASID.
 */
अटल व्योम replace_tlb_one_pid(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ mmu_pid, अचिन्हित दीर्घ tlbacc)
अणु
	अचिन्हित पूर्णांक way;
	अचिन्हित दीर्घ org_misc, pid_misc;

	/* remember pid/way until we वापस. */
	get_misc_and_pid(&org_misc, &pid_misc);

	WRCTL(CTL_PTEADDR, (addr >> PAGE_SHIFT) << 2);

	क्रम (way = 0; way < cpuinfo.tlb_num_ways; way++) अणु
		अचिन्हित दीर्घ pteaddr;
		अचिन्हित दीर्घ tlbmisc;
		अचिन्हित दीर्घ pid;

		tlbmisc = TLBMISC_RD | (way << TLBMISC_WAY_SHIFT);
		WRCTL(CTL_TLBMISC, tlbmisc);

		pteaddr = RDCTL(CTL_PTEADDR);
		अगर (((pteaddr >> 2) & 0xfffff) != (addr >> PAGE_SHIFT))
			जारी;

		tlbmisc = RDCTL(CTL_TLBMISC);
		pid = (tlbmisc >> TLBMISC_PID_SHIFT) & TLBMISC_PID_MASK;
		अगर (pid != mmu_pid)
			जारी;

		tlbmisc = (mmu_pid << TLBMISC_PID_SHIFT) | TLBMISC_WE |
			  (way << TLBMISC_WAY_SHIFT);
		WRCTL(CTL_TLBMISC, tlbmisc);
		अगर (tlbacc == 0)
			WRCTL(CTL_PTEADDR, pteaddr_invalid(addr));
		WRCTL(CTL_TLBACC, tlbacc);
		/*
		 * There should be only a single entry that maps a
		 * particular अणुaddress,pidपूर्ण so अवरोध after a match.
		 */
		अवरोध;
	पूर्ण

	WRCTL(CTL_TLBMISC, org_misc);
पूर्ण

अटल व्योम flush_tlb_one_pid(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ mmu_pid)
अणु
	pr_debug("Flush tlb-entry for vaddr=%#lx\n", addr);

	replace_tlb_one_pid(addr, mmu_pid, 0);
पूर्ण

अटल व्योम reload_tlb_one_pid(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ mmu_pid, pte_t pte)
अणु
	pr_debug("Reload tlb-entry for vaddr=%#lx\n", addr);

	replace_tlb_one_pid(addr, mmu_pid, pte_val(pte));
पूर्ण

व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ mmu_pid = get_pid_from_context(&vma->vm_mm->context);

	जबतक (start < end) अणु
		flush_tlb_one_pid(start, mmu_pid);
		start += PAGE_SIZE;
	पूर्ण
पूर्ण

व्योम reload_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr, pte_t pte)
अणु
	अचिन्हित दीर्घ mmu_pid = get_pid_from_context(&vma->vm_mm->context);

	reload_tlb_one_pid(addr, mmu_pid, pte);
पूर्ण

/*
 * This one is only used क्रम pages with the global bit set so we करोn't care
 * much about the ASID.
 */
अटल व्योम flush_tlb_one(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित पूर्णांक way;
	अचिन्हित दीर्घ org_misc, pid_misc;

	pr_debug("Flush tlb-entry for vaddr=%#lx\n", addr);

	/* remember pid/way until we वापस. */
	get_misc_and_pid(&org_misc, &pid_misc);

	WRCTL(CTL_PTEADDR, (addr >> PAGE_SHIFT) << 2);

	क्रम (way = 0; way < cpuinfo.tlb_num_ways; way++) अणु
		अचिन्हित दीर्घ pteaddr;
		अचिन्हित दीर्घ tlbmisc;

		tlbmisc = TLBMISC_RD | (way << TLBMISC_WAY_SHIFT);
		WRCTL(CTL_TLBMISC, tlbmisc);

		pteaddr = RDCTL(CTL_PTEADDR);
		अगर (((pteaddr >> 2) & 0xfffff) != (addr >> PAGE_SHIFT))
			जारी;

		pr_debug("Flush entry by writing way=%dl pid=%ld\n",
			 way, (pid_misc >> TLBMISC_PID_SHIFT));

		tlbmisc = TLBMISC_WE | (way << TLBMISC_WAY_SHIFT);
		WRCTL(CTL_TLBMISC, tlbmisc);
		WRCTL(CTL_PTEADDR, pteaddr_invalid(addr));
		WRCTL(CTL_TLBACC, 0);
	पूर्ण

	WRCTL(CTL_TLBMISC, org_misc);
पूर्ण

व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	जबतक (start < end) अणु
		flush_tlb_one(start);
		start += PAGE_SIZE;
	पूर्ण
पूर्ण

व्योम dump_tlb_line(अचिन्हित दीर्घ line)
अणु
	अचिन्हित पूर्णांक way;
	अचिन्हित दीर्घ org_misc;

	pr_debug("dump tlb-entries for line=%#lx (addr %08lx)\n", line,
		line << (PAGE_SHIFT + cpuinfo.tlb_num_ways_log2));

	/* remember pid/way until we वापस */
	org_misc = (RDCTL(CTL_TLBMISC) & (TLBMISC_PID | TLBMISC_WAY));

	WRCTL(CTL_PTEADDR, line << 2);

	क्रम (way = 0; way < cpuinfo.tlb_num_ways; way++) अणु
		अचिन्हित दीर्घ pteaddr;
		अचिन्हित दीर्घ tlbmisc;
		अचिन्हित दीर्घ tlbacc;

		WRCTL(CTL_TLBMISC, TLBMISC_RD | (way << TLBMISC_WAY_SHIFT));
		pteaddr = RDCTL(CTL_PTEADDR);
		tlbmisc = RDCTL(CTL_TLBMISC);
		tlbacc = RDCTL(CTL_TLBACC);

		अगर ((tlbacc << PAGE_SHIFT) != 0) अणु
			pr_debug("-- way:%02x vpn:0x%08lx phys:0x%08lx pid:0x%02lx flags:%c%c%c%c%c\n",
				way,
				(pteaddr << (PAGE_SHIFT-2)),
				(tlbacc << PAGE_SHIFT),
				((tlbmisc >> TLBMISC_PID_SHIFT) &
				TLBMISC_PID_MASK),
				(tlbacc & _PAGE_READ ? 'r' : '-'),
				(tlbacc & _PAGE_WRITE ? 'w' : '-'),
				(tlbacc & _PAGE_EXEC ? 'x' : '-'),
				(tlbacc & _PAGE_GLOBAL ? 'g' : '-'),
				(tlbacc & _PAGE_CACHED ? 'c' : '-'));
		पूर्ण
	पूर्ण

	WRCTL(CTL_TLBMISC, org_misc);
पूर्ण

व्योम dump_tlb(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < cpuinfo.tlb_num_lines; i++)
		dump_tlb_line(i);
पूर्ण

व्योम flush_tlb_pid(अचिन्हित दीर्घ mmu_pid)
अणु
	अचिन्हित दीर्घ addr = 0;
	अचिन्हित पूर्णांक line;
	अचिन्हित पूर्णांक way;
	अचिन्हित दीर्घ org_misc, pid_misc;

	/* remember pid/way until we वापस */
	get_misc_and_pid(&org_misc, &pid_misc);

	क्रम (line = 0; line < cpuinfo.tlb_num_lines; line++) अणु
		WRCTL(CTL_PTEADDR, pteaddr_invalid(addr));

		क्रम (way = 0; way < cpuinfo.tlb_num_ways; way++) अणु
			अचिन्हित दीर्घ tlbmisc;
			अचिन्हित दीर्घ pid;

			tlbmisc = TLBMISC_RD | (way << TLBMISC_WAY_SHIFT);
			WRCTL(CTL_TLBMISC, tlbmisc);
			tlbmisc = RDCTL(CTL_TLBMISC);
			pid = (tlbmisc >> TLBMISC_PID_SHIFT) & TLBMISC_PID_MASK;
			अगर (pid != mmu_pid)
				जारी;

			tlbmisc = TLBMISC_WE | (way << TLBMISC_WAY_SHIFT);
			WRCTL(CTL_TLBMISC, tlbmisc);
			WRCTL(CTL_TLBACC, 0);
		पूर्ण

		addr += PAGE_SIZE;
	पूर्ण

	WRCTL(CTL_TLBMISC, org_misc);
पूर्ण

/*
 * All entries common to a mm share an asid.  To effectively flush these
 * entries, we just bump the asid.
 */
व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (current->mm == mm) अणु
		अचिन्हित दीर्घ mmu_pid = get_pid_from_context(&mm->context);
		flush_tlb_pid(mmu_pid);
	पूर्ण अन्यथा अणु
		स_रखो(&mm->context, 0, माप(mm_context_t));
	पूर्ण
पूर्ण

व्योम flush_tlb_all(व्योम)
अणु
	अचिन्हित दीर्घ addr = 0;
	अचिन्हित पूर्णांक line;
	अचिन्हित पूर्णांक way;
	अचिन्हित दीर्घ org_misc, pid_misc;

	/* remember pid/way until we वापस */
	get_misc_and_pid(&org_misc, &pid_misc);

	/* Start at way 0, way is स्वतः-incremented after each TLBACC ग_लिखो */
	WRCTL(CTL_TLBMISC, TLBMISC_WE);

	/* Map each TLB entry to physcal address 0 with no-access and a
	   bad ptbase */
	क्रम (line = 0; line < cpuinfo.tlb_num_lines; line++) अणु
		WRCTL(CTL_PTEADDR, pteaddr_invalid(addr));
		क्रम (way = 0; way < cpuinfo.tlb_num_ways; way++)
			WRCTL(CTL_TLBACC, 0);

		addr += PAGE_SIZE;
	पूर्ण

	/* restore pid/way */
	WRCTL(CTL_TLBMISC, org_misc);
पूर्ण

व्योम set_mmu_pid(अचिन्हित दीर्घ pid)
अणु
	अचिन्हित दीर्घ tlbmisc;

	tlbmisc = RDCTL(CTL_TLBMISC);
	tlbmisc = (tlbmisc & TLBMISC_WAY);
	tlbmisc |= (pid & TLBMISC_PID_MASK) << TLBMISC_PID_SHIFT;
	WRCTL(CTL_TLBMISC, tlbmisc);
पूर्ण
