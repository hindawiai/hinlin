<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/setup.h>

/*
 * One C-SKY MMU TLB entry contain two PFN/page entry, ie:
 * 1VPN -> 2PFN
 */
#घोषणा TLB_ENTRY_SIZE		(PAGE_SIZE * 2)
#घोषणा TLB_ENTRY_SIZE_MASK	(PAGE_MASK << 1)

व्योम flush_tlb_all(व्योम)
अणु
	tlb_invalid_all();
पूर्ण

व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_CPU_HAS_TLBI
	sync_is();
	यंत्र अस्थिर(
		"tlbi.asids %0	\n"
		"sync.i		\n"
		:
		: "r" (cpu_asid(mm))
		: "memory");
#अन्यथा
	tlb_invalid_all();
#पूर्ण_अगर
पूर्ण

/*
 * MMU operation regs only could invalid tlb entry in jtlb and we
 * need change asid field to invalid I-utlb & D-utlb.
 */
#अगर_अघोषित CONFIG_CPU_HAS_TLBI
#घोषणा restore_asid_inv_utlb(oldpid, newpid) \
करो अणु \
	अगर (oldpid == newpid) \
		ग_लिखो_mmu_entryhi(oldpid + 1); \
	ग_लिखो_mmu_entryhi(oldpid); \
पूर्ण जबतक (0)
#पूर्ण_अगर

व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ newpid = cpu_asid(vma->vm_mm);

	start &= TLB_ENTRY_SIZE_MASK;
	end   += TLB_ENTRY_SIZE - 1;
	end   &= TLB_ENTRY_SIZE_MASK;

#अगर_घोषित CONFIG_CPU_HAS_TLBI
	sync_is();
	जबतक (start < end) अणु
		यंत्र अस्थिर(
			"tlbi.vas %0	\n"
			:
			: "r" (start | newpid)
			: "memory");

		start += 2*PAGE_SIZE;
	पूर्ण
	यंत्र अस्थिर("sync.i\n");
#अन्यथा
	अणु
	अचिन्हित दीर्घ flags, oldpid;

	local_irq_save(flags);
	oldpid = पढ़ो_mmu_entryhi() & ASID_MASK;
	जबतक (start < end) अणु
		पूर्णांक idx;

		ग_लिखो_mmu_entryhi(start | newpid);
		start += 2*PAGE_SIZE;
		tlb_probe();
		idx = पढ़ो_mmu_index();
		अगर (idx >= 0)
			tlb_invalid_indexed();
	पूर्ण
	restore_asid_inv_utlb(oldpid, newpid);
	local_irq_restore(flags);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	start &= TLB_ENTRY_SIZE_MASK;
	end   += TLB_ENTRY_SIZE - 1;
	end   &= TLB_ENTRY_SIZE_MASK;

#अगर_घोषित CONFIG_CPU_HAS_TLBI
	sync_is();
	जबतक (start < end) अणु
		यंत्र अस्थिर(
			"tlbi.vaas %0	\n"
			:
			: "r" (start)
			: "memory");

		start += 2*PAGE_SIZE;
	पूर्ण
	यंत्र अस्थिर("sync.i\n");
#अन्यथा
	अणु
	अचिन्हित दीर्घ flags, oldpid;

	local_irq_save(flags);
	oldpid = पढ़ो_mmu_entryhi() & ASID_MASK;
	जबतक (start < end) अणु
		पूर्णांक idx;

		ग_लिखो_mmu_entryhi(start | oldpid);
		start += 2*PAGE_SIZE;
		tlb_probe();
		idx = पढ़ो_mmu_index();
		अगर (idx >= 0)
			tlb_invalid_indexed();
	पूर्ण
	restore_asid_inv_utlb(oldpid, oldpid);
	local_irq_restore(flags);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक newpid = cpu_asid(vma->vm_mm);

	addr &= TLB_ENTRY_SIZE_MASK;

#अगर_घोषित CONFIG_CPU_HAS_TLBI
	sync_is();
	यंत्र अस्थिर(
		"tlbi.vas %0	\n"
		"sync.i		\n"
		:
		: "r" (addr | newpid)
		: "memory");
#अन्यथा
	अणु
	पूर्णांक oldpid, idx;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	oldpid = पढ़ो_mmu_entryhi() & ASID_MASK;
	ग_लिखो_mmu_entryhi(addr | newpid);
	tlb_probe();
	idx = पढ़ो_mmu_index();
	अगर (idx >= 0)
		tlb_invalid_indexed();

	restore_asid_inv_utlb(oldpid, newpid);
	local_irq_restore(flags);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम flush_tlb_one(अचिन्हित दीर्घ addr)
अणु
	addr &= TLB_ENTRY_SIZE_MASK;

#अगर_घोषित CONFIG_CPU_HAS_TLBI
	sync_is();
	यंत्र अस्थिर(
		"tlbi.vaas %0	\n"
		"sync.i		\n"
		:
		: "r" (addr)
		: "memory");
#अन्यथा
	अणु
	पूर्णांक oldpid, idx;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	oldpid = पढ़ो_mmu_entryhi() & ASID_MASK;
	ग_लिखो_mmu_entryhi(addr | oldpid);
	tlb_probe();
	idx = पढ़ो_mmu_index();
	अगर (idx >= 0)
		tlb_invalid_indexed();

	restore_asid_inv_utlb(oldpid, oldpid);
	local_irq_restore(flags);
	पूर्ण
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(flush_tlb_one);
