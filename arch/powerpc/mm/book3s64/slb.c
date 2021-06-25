<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerPC64 SLB support.
 *
 * Copyright (C) 2004 David Gibson <dwg@au.ibm.com>, IBM
 * Based on earlier code written by:
 * Dave Engebretsen and Mike Corrigan अणुengebret|mikejcपूर्ण@us.ibm.com
 *    Copyright (c) 2001 Dave Engebretsen
 * Copyright (C) 2002 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 */

#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp.h>
#समावेश <linux/compiler.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/code-patching.h>

#समावेश "internal.h"


अटल दीर्घ slb_allocate_user(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea);

bool stress_slb_enabled __initdata;

अटल पूर्णांक __init parse_stress_slb(अक्षर *p)
अणु
	stress_slb_enabled = true;
	वापस 0;
पूर्ण
early_param("stress_slb", parse_stress_slb);

__ro_after_init DEFINE_STATIC_KEY_FALSE(stress_slb_key);

अटल व्योम निश्चित_slb_presence(bool present, अचिन्हित दीर्घ ea)
अणु
#अगर_घोषित CONFIG_DEBUG_VM
	अचिन्हित दीर्घ पंचांगp;

	WARN_ON_ONCE(mfmsr() & MSR_EE);

	अगर (!cpu_has_feature(CPU_FTR_ARCH_206))
		वापस;

	/*
	 * slbfee. requires bit 24 (PPC bit 39) be clear in RB. Hardware
	 * ignores all other bits from 0-27, so just clear them all.
	 */
	ea &= ~((1UL << SID_SHIFT) - 1);
	यंत्र अस्थिर(__PPC_SLBFEE_DOT(%0, %1) : "=r"(पंचांगp) : "r"(ea) : "cr0");

	WARN_ON(present == (पंचांगp == 0));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम slb_shaकरोw_update(अचिन्हित दीर्घ ea, पूर्णांक ssize,
				     अचिन्हित दीर्घ flags,
				     क्रमागत slb_index index)
अणु
	काष्ठा slb_shaकरोw *p = get_slb_shaकरोw();

	/*
	 * Clear the ESID first so the entry is not valid जबतक we are
	 * updating it.  No ग_लिखो barriers are needed here, provided
	 * we only update the current CPU's SLB shaकरोw buffer.
	 */
	WRITE_ONCE(p->save_area[index].esid, 0);
	WRITE_ONCE(p->save_area[index].vsid, cpu_to_be64(mk_vsid_data(ea, ssize, flags)));
	WRITE_ONCE(p->save_area[index].esid, cpu_to_be64(mk_esid_data(ea, ssize, index)));
पूर्ण

अटल अंतरभूत व्योम slb_shaकरोw_clear(क्रमागत slb_index index)
अणु
	WRITE_ONCE(get_slb_shaकरोw()->save_area[index].esid, cpu_to_be64(index));
पूर्ण

अटल अंतरभूत व्योम create_shaकरोwed_slbe(अचिन्हित दीर्घ ea, पूर्णांक ssize,
					अचिन्हित दीर्घ flags,
					क्रमागत slb_index index)
अणु
	/*
	 * Updating the shaकरोw buffer beक्रमe writing the SLB ensures
	 * we करोn't get a stale entry here अगर we get preempted by PHYP
	 * between these two statements.
	 */
	slb_shaकरोw_update(ea, ssize, flags, index);

	निश्चित_slb_presence(false, ea);
	यंत्र अस्थिर("slbmte  %0,%1" :
		     : "r" (mk_vsid_data(ea, ssize, flags)),
		       "r" (mk_esid_data(ea, ssize, index))
		     : "memory" );
पूर्ण

/*
 * Insert bolted entries पूर्णांकo SLB (which may not be empty, so करोn't clear
 * slb_cache_ptr).
 */
व्योम __slb_restore_bolted_realmode(व्योम)
अणु
	काष्ठा slb_shaकरोw *p = get_slb_shaकरोw();
	क्रमागत slb_index index;

	 /* No isync needed because realmode. */
	क्रम (index = 0; index < SLB_NUM_BOLTED; index++) अणु
		यंत्र अस्थिर("slbmte  %0,%1" :
		     : "r" (be64_to_cpu(p->save_area[index].vsid)),
		       "r" (be64_to_cpu(p->save_area[index].esid)));
	पूर्ण

	निश्चित_slb_presence(true, local_paca->kstack);
पूर्ण

/*
 * Insert the bolted entries पूर्णांकo an empty SLB.
 */
व्योम slb_restore_bolted_realmode(व्योम)
अणु
	__slb_restore_bolted_realmode();
	get_paca()->slb_cache_ptr = 0;

	get_paca()->slb_kern_biपंचांगap = (1U << SLB_NUM_BOLTED) - 1;
	get_paca()->slb_used_biपंचांगap = get_paca()->slb_kern_biपंचांगap;
पूर्ण

/*
 * This flushes all SLB entries including 0, so it must be realmode.
 */
व्योम slb_flush_all_realmode(व्योम)
अणु
	यंत्र अस्थिर("slbmte %0,%0; slbia" : : "r" (0));
पूर्ण

अटल __always_अंतरभूत व्योम __slb_flush_and_restore_bolted(bool preserve_kernel_lookaside)
अणु
	काष्ठा slb_shaकरोw *p = get_slb_shaकरोw();
	अचिन्हित दीर्घ ksp_esid_data, ksp_vsid_data;
	u32 ih;

	/*
	 * SLBIA IH=1 on ISA v2.05 and newer processors may preserve lookaside
	 * inक्रमmation created with Class=0 entries, which we use क्रम kernel
	 * SLB entries (the SLB entries themselves are still invalidated).
	 *
	 * Older processors will ignore this optimisation. Over-invalidation
	 * is fine because we never rely on lookaside inक्रमmation existing.
	 */
	अगर (preserve_kernel_lookaside)
		ih = 1;
	अन्यथा
		ih = 0;

	ksp_esid_data = be64_to_cpu(p->save_area[KSTACK_INDEX].esid);
	ksp_vsid_data = be64_to_cpu(p->save_area[KSTACK_INDEX].vsid);

	यंत्र अस्थिर(PPC_SLBIA(%0)"	\n"
		     "slbmte	%1, %2	\n"
		     :: "i" (ih),
			"r" (ksp_vsid_data),
			"r" (ksp_esid_data)
		     : "memory");
पूर्ण

/*
 * This flushes non-bolted entries, it can be run in भव mode. Must
 * be called with पूर्णांकerrupts disabled.
 */
व्योम slb_flush_and_restore_bolted(व्योम)
अणु
	BUILD_BUG_ON(SLB_NUM_BOLTED != 2);

	WARN_ON(!irqs_disabled());

	/*
	 * We can't take a PMU exception in the following code, so hard
	 * disable पूर्णांकerrupts.
	 */
	hard_irq_disable();

	isync();
	__slb_flush_and_restore_bolted(false);
	isync();

	निश्चित_slb_presence(true, get_paca()->kstack);

	get_paca()->slb_cache_ptr = 0;

	get_paca()->slb_kern_biपंचांगap = (1U << SLB_NUM_BOLTED) - 1;
	get_paca()->slb_used_biपंचांगap = get_paca()->slb_kern_biपंचांगap;
पूर्ण

व्योम slb_save_contents(काष्ठा slb_entry *slb_ptr)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ e, v;

	/* Save slb_cache_ptr value. */
	get_paca()->slb_save_cache_ptr = get_paca()->slb_cache_ptr;

	अगर (!slb_ptr)
		वापस;

	क्रम (i = 0; i < mmu_slb_size; i++) अणु
		यंत्र अस्थिर("slbmfee  %0,%1" : "=r" (e) : "r" (i));
		यंत्र अस्थिर("slbmfev  %0,%1" : "=r" (v) : "r" (i));
		slb_ptr->esid = e;
		slb_ptr->vsid = v;
		slb_ptr++;
	पूर्ण
पूर्ण

व्योम slb_dump_contents(काष्ठा slb_entry *slb_ptr)
अणु
	पूर्णांक i, n;
	अचिन्हित दीर्घ e, v;
	अचिन्हित दीर्घ llp;

	अगर (!slb_ptr)
		वापस;

	pr_err("SLB contents of cpu 0x%x\n", smp_processor_id());

	क्रम (i = 0; i < mmu_slb_size; i++) अणु
		e = slb_ptr->esid;
		v = slb_ptr->vsid;
		slb_ptr++;

		अगर (!e && !v)
			जारी;

		pr_err("%02d %016lx %016lx %s\n", i, e, v,
				(e & SLB_ESID_V) ? "VALID" : "NOT VALID");

		अगर (!(e & SLB_ESID_V))
			जारी;

		llp = v & SLB_VSID_LLP;
		अगर (v & SLB_VSID_B_1T) अणु
			pr_err("     1T ESID=%9lx VSID=%13lx LLP:%3lx\n",
			       GET_ESID_1T(e),
			       (v & ~SLB_VSID_B) >> SLB_VSID_SHIFT_1T, llp);
		पूर्ण अन्यथा अणु
			pr_err("   256M ESID=%9lx VSID=%13lx LLP:%3lx\n",
			       GET_ESID(e),
			       (v & ~SLB_VSID_B) >> SLB_VSID_SHIFT, llp);
		पूर्ण
	पूर्ण

	अगर (!early_cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		/* RR is not so useful as it's often not used क्रम allocation */
		pr_err("SLB RR allocator index %d\n", get_paca()->stab_rr);

		/* Dump slb cache entires as well. */
		pr_err("SLB cache ptr value = %d\n", get_paca()->slb_save_cache_ptr);
		pr_err("Valid SLB cache entries:\n");
		n = min_t(पूर्णांक, get_paca()->slb_save_cache_ptr, SLB_CACHE_ENTRIES);
		क्रम (i = 0; i < n; i++)
			pr_err("%02d EA[0-35]=%9x\n", i, get_paca()->slb_cache[i]);
		pr_err("Rest of SLB cache entries:\n");
		क्रम (i = n; i < SLB_CACHE_ENTRIES; i++)
			pr_err("%02d EA[0-35]=%9x\n", i, get_paca()->slb_cache[i]);
	पूर्ण
पूर्ण

व्योम slb_vदो_स्मृति_update(व्योम)
अणु
	/*
	 * vदो_स्मृति is not bolted, so just have to flush non-bolted.
	 */
	slb_flush_and_restore_bolted();
पूर्ण

अटल bool preload_hit(काष्ठा thपढ़ो_info *ti, अचिन्हित दीर्घ esid)
अणु
	अचिन्हित अक्षर i;

	क्रम (i = 0; i < ti->slb_preload_nr; i++) अणु
		अचिन्हित अक्षर idx;

		idx = (ti->slb_preload_tail + i) % SLB_PRELOAD_NR;
		अगर (esid == ti->slb_preload_esid[idx])
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool preload_add(काष्ठा thपढ़ो_info *ti, अचिन्हित दीर्घ ea)
अणु
	अचिन्हित अक्षर idx;
	अचिन्हित दीर्घ esid;

	अगर (mmu_has_feature(MMU_FTR_1T_SEGMENT)) अणु
		/* EAs are stored >> 28 so 256MB segments करोn't need clearing */
		अगर (ea & ESID_MASK_1T)
			ea &= ESID_MASK_1T;
	पूर्ण

	esid = ea >> SID_SHIFT;

	अगर (preload_hit(ti, esid))
		वापस false;

	idx = (ti->slb_preload_tail + ti->slb_preload_nr) % SLB_PRELOAD_NR;
	ti->slb_preload_esid[idx] = esid;
	अगर (ti->slb_preload_nr == SLB_PRELOAD_NR)
		ti->slb_preload_tail = (ti->slb_preload_tail + 1) % SLB_PRELOAD_NR;
	अन्यथा
		ti->slb_preload_nr++;

	वापस true;
पूर्ण

अटल व्योम preload_age(काष्ठा thपढ़ो_info *ti)
अणु
	अगर (!ti->slb_preload_nr)
		वापस;
	ti->slb_preload_nr--;
	ti->slb_preload_tail = (ti->slb_preload_tail + 1) % SLB_PRELOAD_NR;
पूर्ण

व्योम slb_setup_new_exec(व्योम)
अणु
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ exec = 0x10000000;

	WARN_ON(irqs_disabled());

	/*
	 * preload cache can only be used to determine whether a SLB
	 * entry exists अगर it करोes not start to overflow.
	 */
	अगर (ti->slb_preload_nr + 2 > SLB_PRELOAD_NR)
		वापस;

	hard_irq_disable();

	/*
	 * We have no good place to clear the slb preload cache on exec,
	 * flush_thपढ़ो is about the earliest arch hook but that happens
	 * after we चयन to the mm and have aleady preloaded the SLBEs.
	 *
	 * For the most part that's probably okay to use entries from the
	 * previous exec, they will age out अगर unused. It may turn out to
	 * be an advantage to clear the cache beक्रमe चयनing to it,
	 * however.
	 */

	/*
	 * preload some userspace segments पूर्णांकo the SLB.
	 * Almost all 32 and 64bit PowerPC executables are linked at
	 * 0x10000000 so it makes sense to preload this segment.
	 */
	अगर (!is_kernel_addr(exec)) अणु
		अगर (preload_add(ti, exec))
			slb_allocate_user(mm, exec);
	पूर्ण

	/* Libraries and mmaps. */
	अगर (!is_kernel_addr(mm->mmap_base)) अणु
		अगर (preload_add(ti, mm->mmap_base))
			slb_allocate_user(mm, mm->mmap_base);
	पूर्ण

	/* see चयन_slb */
	यंत्र अस्थिर("isync" : : : "memory");

	local_irq_enable();
पूर्ण

व्योम preload_new_slb_context(अचिन्हित दीर्घ start, अचिन्हित दीर्घ sp)
अणु
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ heap = mm->start_brk;

	WARN_ON(irqs_disabled());

	/* see above */
	अगर (ti->slb_preload_nr + 3 > SLB_PRELOAD_NR)
		वापस;

	hard_irq_disable();

	/* Userspace entry address. */
	अगर (!is_kernel_addr(start)) अणु
		अगर (preload_add(ti, start))
			slb_allocate_user(mm, start);
	पूर्ण

	/* Top of stack, grows करोwn. */
	अगर (!is_kernel_addr(sp)) अणु
		अगर (preload_add(ti, sp))
			slb_allocate_user(mm, sp);
	पूर्ण

	/* Bottom of heap, grows up. */
	अगर (heap && !is_kernel_addr(heap)) अणु
		अगर (preload_add(ti, heap))
			slb_allocate_user(mm, heap);
	पूर्ण

	/* see चयन_slb */
	यंत्र अस्थिर("isync" : : : "memory");

	local_irq_enable();
पूर्ण

अटल व्योम slb_cache_slbie_kernel(अचिन्हित पूर्णांक index)
अणु
	अचिन्हित दीर्घ slbie_data = get_paca()->slb_cache[index];
	अचिन्हित दीर्घ ksp = get_paca()->kstack;

	slbie_data <<= SID_SHIFT;
	slbie_data |= 0xc000000000000000ULL;
	अगर ((ksp & slb_esid_mask(mmu_kernel_ssize)) == slbie_data)
		वापस;
	slbie_data |= mmu_kernel_ssize << SLBIE_SSIZE_SHIFT;

	यंत्र अस्थिर("slbie %0" : : "r" (slbie_data));
पूर्ण

अटल व्योम slb_cache_slbie_user(अचिन्हित पूर्णांक index)
अणु
	अचिन्हित दीर्घ slbie_data = get_paca()->slb_cache[index];

	slbie_data <<= SID_SHIFT;
	slbie_data |= user_segment_size(slbie_data) << SLBIE_SSIZE_SHIFT;
	slbie_data |= SLBIE_C; /* user slbs have C=1 */

	यंत्र अस्थिर("slbie %0" : : "r" (slbie_data));
पूर्ण

/* Flush all user entries from the segment table of the current processor. */
व्योम चयन_slb(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(tsk);
	अचिन्हित अक्षर i;

	/*
	 * We need पूर्णांकerrupts hard-disabled here, not just soft-disabled,
	 * so that a PMU पूर्णांकerrupt can't occur, which might try to access
	 * user memory (to get a stack trace) and possible cause an SLB miss
	 * which would update the slb_cache/slb_cache_ptr fields in the PACA.
	 */
	hard_irq_disable();
	isync();
	अगर (stress_slb()) अणु
		__slb_flush_and_restore_bolted(false);
		isync();
		get_paca()->slb_cache_ptr = 0;
		get_paca()->slb_kern_biपंचांगap = (1U << SLB_NUM_BOLTED) - 1;

	पूर्ण अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		/*
		 * SLBIA IH=3 invalidates all Class=1 SLBEs and their
		 * associated lookaside काष्ठाures, which matches what
		 * चयन_slb wants. So ARCH_300 करोes not use the slb
		 * cache.
		 */
		यंत्र अस्थिर(PPC_SLBIA(3));

	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ offset = get_paca()->slb_cache_ptr;

		अगर (!mmu_has_feature(MMU_FTR_NO_SLBIE_B) &&
		    offset <= SLB_CACHE_ENTRIES) अणु
			/*
			 * Could निश्चित_slb_presence(true) here, but
			 * hypervisor or machine check could have come
			 * in and हटाओd the entry at this poपूर्णांक.
			 */

			क्रम (i = 0; i < offset; i++)
				slb_cache_slbie_user(i);

			/* Workaround POWER5 < DD2.1 issue */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_207S) && offset == 1)
				slb_cache_slbie_user(0);

		पूर्ण अन्यथा अणु
			/* Flush but retain kernel lookaside inक्रमmation */
			__slb_flush_and_restore_bolted(true);
			isync();

			get_paca()->slb_kern_biपंचांगap = (1U << SLB_NUM_BOLTED) - 1;
		पूर्ण

		get_paca()->slb_cache_ptr = 0;
	पूर्ण
	get_paca()->slb_used_biपंचांगap = get_paca()->slb_kern_biपंचांगap;

	copy_mm_to_paca(mm);

	/*
	 * We gradually age out SLBs after a number of context चयनes to
	 * reduce reload overhead of unused entries (like we करो with FP/VEC
	 * reload). Each समय we wrap 256 चयनes, take an entry out of the
	 * SLB preload cache.
	 */
	tsk->thपढ़ो.load_slb++;
	अगर (!tsk->thपढ़ो.load_slb) अणु
		अचिन्हित दीर्घ pc = KSTK_EIP(tsk);

		preload_age(ti);
		preload_add(ti, pc);
	पूर्ण

	क्रम (i = 0; i < ti->slb_preload_nr; i++) अणु
		अचिन्हित अक्षर idx;
		अचिन्हित दीर्घ ea;

		idx = (ti->slb_preload_tail + i) % SLB_PRELOAD_NR;
		ea = (अचिन्हित दीर्घ)ti->slb_preload_esid[idx] << SID_SHIFT;

		slb_allocate_user(mm, ea);
	पूर्ण

	/*
	 * Synchronize slbmte preloads with possible subsequent user memory
	 * address accesses by the kernel (user mode won't happen until
	 * rfid, which is safe).
	 */
	isync();
पूर्ण

व्योम slb_set_size(u16 size)
अणु
	mmu_slb_size = size;
पूर्ण

व्योम slb_initialize(व्योम)
अणु
	अचिन्हित दीर्घ linear_llp, vदो_स्मृति_llp, io_llp;
	अचिन्हित दीर्घ lflags;
	अटल पूर्णांक slb_encoding_inited;
#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
	अचिन्हित दीर्घ vmemmap_llp;
#पूर्ण_अगर

	/* Prepare our SLB miss handler based on our page size */
	linear_llp = mmu_psize_defs[mmu_linear_psize].sllp;
	io_llp = mmu_psize_defs[mmu_io_psize].sllp;
	vदो_स्मृति_llp = mmu_psize_defs[mmu_vदो_स्मृति_psize].sllp;
	get_paca()->vदो_स्मृति_sllp = SLB_VSID_KERNEL | vदो_स्मृति_llp;
#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
	vmemmap_llp = mmu_psize_defs[mmu_vmemmap_psize].sllp;
#पूर्ण_अगर
	अगर (!slb_encoding_inited) अणु
		slb_encoding_inited = 1;
		pr_devel("SLB: linear  LLP = %04lx\n", linear_llp);
		pr_devel("SLB: io      LLP = %04lx\n", io_llp);
#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
		pr_devel("SLB: vmemmap LLP = %04lx\n", vmemmap_llp);
#पूर्ण_अगर
	पूर्ण

	get_paca()->stab_rr = SLB_NUM_BOLTED - 1;
	get_paca()->slb_kern_biपंचांगap = (1U << SLB_NUM_BOLTED) - 1;
	get_paca()->slb_used_biपंचांगap = get_paca()->slb_kern_biपंचांगap;

	lflags = SLB_VSID_KERNEL | linear_llp;

	/* Invalidate the entire SLB (even entry 0) & all the ERATS */
	यंत्र अस्थिर("isync":::"memory");
	यंत्र अस्थिर("slbmte  %0,%0"::"r" (0) : "memory");
	यंत्र अस्थिर("isync; slbia; isync":::"memory");
	create_shaकरोwed_slbe(PAGE_OFFSET, mmu_kernel_ssize, lflags, LINEAR_INDEX);

	/*
	 * For the boot cpu, we're running on the stack in init_thपढ़ो_जोड़,
	 * which is in the first segment of the linear mapping, and also
	 * get_paca()->kstack hasn't been initialized yet.
	 * For secondary cpus, we need to bolt the kernel stack entry now.
	 */
	slb_shaकरोw_clear(KSTACK_INDEX);
	अगर (raw_smp_processor_id() != boot_cpuid &&
	    (get_paca()->kstack & slb_esid_mask(mmu_kernel_ssize)) > PAGE_OFFSET)
		create_shaकरोwed_slbe(get_paca()->kstack,
				     mmu_kernel_ssize, lflags, KSTACK_INDEX);

	यंत्र अस्थिर("isync":::"memory");
पूर्ण

अटल व्योम slb_cache_update(अचिन्हित दीर्घ esid_data)
अणु
	पूर्णांक slb_cache_index;

	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		वापस; /* ISAv3.0B and later करोes not use slb_cache */

	अगर (stress_slb())
		वापस;

	/*
	 * Now update slb cache entries
	 */
	slb_cache_index = local_paca->slb_cache_ptr;
	अगर (slb_cache_index < SLB_CACHE_ENTRIES) अणु
		/*
		 * We have space in slb cache क्रम optimized चयन_slb().
		 * Top 36 bits from esid_data as per ISA
		 */
		local_paca->slb_cache[slb_cache_index++] = esid_data >> SID_SHIFT;
		local_paca->slb_cache_ptr++;
	पूर्ण अन्यथा अणु
		/*
		 * Our cache is full and the current cache content strictly
		 * करोesn't indicate the active SLB conents. Bump the ptr
		 * so that चयन_slb() will ignore the cache.
		 */
		local_paca->slb_cache_ptr = SLB_CACHE_ENTRIES + 1;
	पूर्ण
पूर्ण

अटल क्रमागत slb_index alloc_slb_index(bool kernel)
अणु
	क्रमागत slb_index index;

	/*
	 * The allocation biपंचांगaps can become out of synch with the SLB
	 * when the _चयन code करोes slbie when bolting a new stack
	 * segment and it must not be anywhere अन्यथा in the SLB. This leaves
	 * a kernel allocated entry that is unused in the SLB. With very
	 * large प्रणालीs or small segment sizes, the biपंचांगaps could slowly
	 * fill with these entries. They will eventually be cleared out
	 * by the round robin allocator in that हाल, so it's probably not
	 * worth accounting क्रम.
	 */

	/*
	 * SLBs beyond 32 entries are allocated with stab_rr only
	 * POWER7/8/9 have 32 SLB entries, this could be expanded अगर a
	 * future CPU has more.
	 */
	अगर (local_paca->slb_used_biपंचांगap != U32_MAX) अणु
		index = ffz(local_paca->slb_used_biपंचांगap);
		local_paca->slb_used_biपंचांगap |= 1U << index;
		अगर (kernel)
			local_paca->slb_kern_biपंचांगap |= 1U << index;
	पूर्ण अन्यथा अणु
		/* round-robin replacement of slb starting at SLB_NUM_BOLTED. */
		index = local_paca->stab_rr;
		अगर (index < (mmu_slb_size - 1))
			index++;
		अन्यथा
			index = SLB_NUM_BOLTED;
		local_paca->stab_rr = index;
		अगर (index < 32) अणु
			अगर (kernel)
				local_paca->slb_kern_biपंचांगap |= 1U << index;
			अन्यथा
				local_paca->slb_kern_biपंचांगap &= ~(1U << index);
		पूर्ण
	पूर्ण
	BUG_ON(index < SLB_NUM_BOLTED);

	वापस index;
पूर्ण

अटल दीर्घ slb_insert_entry(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ context,
				अचिन्हित दीर्घ flags, पूर्णांक ssize, bool kernel)
अणु
	अचिन्हित दीर्घ vsid;
	अचिन्हित दीर्घ vsid_data, esid_data;
	क्रमागत slb_index index;

	vsid = get_vsid(context, ea, ssize);
	अगर (!vsid)
		वापस -EFAULT;

	/*
	 * There must not be a kernel SLB fault in alloc_slb_index or beक्रमe
	 * slbmte here or the allocation biपंचांगaps could get out of whack with
	 * the SLB.
	 *
	 * User SLB faults or preloads take this path which might get अंतरभूतd
	 * पूर्णांकo the caller, so add compiler barriers here to ensure unsafe
	 * memory accesses करो not come between.
	 */
	barrier();

	index = alloc_slb_index(kernel);

	vsid_data = __mk_vsid_data(vsid, ssize, flags);
	esid_data = mk_esid_data(ea, ssize, index);

	/*
	 * No need क्रम an isync beक्रमe or after this slbmte. The exception
	 * we enter with and the rfid we निकास with are context synchronizing.
	 * User preloads should add isync afterwards in हाल the kernel
	 * accesses user memory beक्रमe it वापसs to userspace with rfid.
	 */
	निश्चित_slb_presence(false, ea);
	अगर (stress_slb()) अणु
		पूर्णांक slb_cache_index = local_paca->slb_cache_ptr;

		/*
		 * stress_slb() करोes not use slb cache, repurpose as a
		 * cache of inserted (non-bolted) kernel SLB entries. All
		 * non-bolted kernel entries are flushed on any user fault,
		 * or अगर there are alपढ़ोy 3 non-boled kernel entries.
		 */
		BUILD_BUG_ON(SLB_CACHE_ENTRIES < 3);
		अगर (!kernel || slb_cache_index == 3) अणु
			पूर्णांक i;

			क्रम (i = 0; i < slb_cache_index; i++)
				slb_cache_slbie_kernel(i);
			slb_cache_index = 0;
		पूर्ण

		अगर (kernel)
			local_paca->slb_cache[slb_cache_index++] = esid_data >> SID_SHIFT;
		local_paca->slb_cache_ptr = slb_cache_index;
	पूर्ण
	यंत्र अस्थिर("slbmte %0, %1" : : "r" (vsid_data), "r" (esid_data));

	barrier();

	अगर (!kernel)
		slb_cache_update(esid_data);

	वापस 0;
पूर्ण

अटल दीर्घ slb_allocate_kernel(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ id)
अणु
	अचिन्हित दीर्घ context;
	अचिन्हित दीर्घ flags;
	पूर्णांक ssize;

	अगर (id == LINEAR_MAP_REGION_ID) अणु

		/* We only support upto H_MAX_PHYSMEM_BITS */
		अगर ((ea & EA_MASK) > (1UL << H_MAX_PHYSMEM_BITS))
			वापस -EFAULT;

		flags = SLB_VSID_KERNEL | mmu_psize_defs[mmu_linear_psize].sllp;

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
	पूर्ण अन्यथा अगर (id == VMEMMAP_REGION_ID) अणु

		अगर (ea >= H_VMEMMAP_END)
			वापस -EFAULT;

		flags = SLB_VSID_KERNEL | mmu_psize_defs[mmu_vmemmap_psize].sllp;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (id == VMALLOC_REGION_ID) अणु

		अगर (ea >= H_VMALLOC_END)
			वापस -EFAULT;

		flags = local_paca->vदो_स्मृति_sllp;

	पूर्ण अन्यथा अगर (id == IO_REGION_ID) अणु

		अगर (ea >= H_KERN_IO_END)
			वापस -EFAULT;

		flags = SLB_VSID_KERNEL | mmu_psize_defs[mmu_io_psize].sllp;

	पूर्ण अन्यथा अणु
		वापस -EFAULT;
	पूर्ण

	ssize = MMU_SEGSIZE_1T;
	अगर (!mmu_has_feature(MMU_FTR_1T_SEGMENT))
		ssize = MMU_SEGSIZE_256M;

	context = get_kernel_context(ea);

	वापस slb_insert_entry(ea, context, flags, ssize, true);
पूर्ण

अटल दीर्घ slb_allocate_user(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea)
अणु
	अचिन्हित दीर्घ context;
	अचिन्हित दीर्घ flags;
	पूर्णांक bpsize;
	पूर्णांक ssize;

	/*
	 * consider this as bad access अगर we take a SLB miss
	 * on an address above addr limit.
	 */
	अगर (ea >= mm_ctx_slb_addr_limit(&mm->context))
		वापस -EFAULT;

	context = get_user_context(&mm->context, ea);
	अगर (!context)
		वापस -EFAULT;

	अगर (unlikely(ea >= H_PGTABLE_RANGE)) अणु
		WARN_ON(1);
		वापस -EFAULT;
	पूर्ण

	ssize = user_segment_size(ea);

	bpsize = get_slice_psize(mm, ea);
	flags = SLB_VSID_USER | mmu_psize_defs[bpsize].sllp;

	वापस slb_insert_entry(ea, context, flags, ssize, false);
पूर्ण

DEFINE_INTERRUPT_HANDLER_RAW(करो_slb_fault)
अणु
	अचिन्हित दीर्घ ea = regs->dar;
	अचिन्हित दीर्घ id = get_region_id(ea);

	/* IRQs are not reconciled here, so can't check irqs_disabled */
	VM_WARN_ON(mfmsr() & MSR_EE);

	अगर (unlikely(!(regs->msr & MSR_RI)))
		वापस -EINVAL;

	/*
	 * SLB kernel faults must be very careful not to touch anything that is
	 * not bolted. E.g., PACA and global variables are okay, mm->context
	 * stuff is not. SLB user faults may access all of memory (and induce
	 * one recursive SLB kernel fault), so the kernel fault must not
	 * trample on the user fault state at those poपूर्णांकs.
	 */

	/*
	 * This is a raw पूर्णांकerrupt handler, क्रम perक्रमmance, so that
	 * fast_पूर्णांकerrupt_वापस can be used. The handler must not touch local
	 * irq state, or schedule. We could test क्रम usermode and upgrade to a
	 * normal process context (synchronous) पूर्णांकerrupt क्रम those, which
	 * would make them first-class kernel code and able to be traced and
	 * instrumented, although perक्रमmance would suffer a bit, it would
	 * probably be a good tradeoff.
	 */
	अगर (id >= LINEAR_MAP_REGION_ID) अणु
		दीर्घ err;
#अगर_घोषित CONFIG_DEBUG_VM
		/* Catch recursive kernel SLB faults. */
		BUG_ON(local_paca->in_kernel_slb_handler);
		local_paca->in_kernel_slb_handler = 1;
#पूर्ण_अगर
		err = slb_allocate_kernel(ea, id);
#अगर_घोषित CONFIG_DEBUG_VM
		local_paca->in_kernel_slb_handler = 0;
#पूर्ण_अगर
		वापस err;
	पूर्ण अन्यथा अणु
		काष्ठा mm_काष्ठा *mm = current->mm;
		दीर्घ err;

		अगर (unlikely(!mm))
			वापस -EFAULT;

		err = slb_allocate_user(mm, ea);
		अगर (!err)
			preload_add(current_thपढ़ो_info(), ea);

		वापस err;
	पूर्ण
पूर्ण

DEFINE_INTERRUPT_HANDLER(करो_bad_slb_fault)
अणु
	पूर्णांक err = regs->result;

	अगर (err == -EFAULT) अणु
		अगर (user_mode(regs))
			_exception(संक_अंश, regs, SEGV_BNDERR, regs->dar);
		अन्यथा
			bad_page_fault(regs, संक_अंश);
	पूर्ण अन्यथा अगर (err == -EINVAL) अणु
		unrecoverable_exception(regs);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण
पूर्ण
