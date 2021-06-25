<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * c 2001 PPC 64 Team, IBM Corp
 */

#समावेश <linux/smp.h>
#समावेश <linux/export.h>
#समावेश <linux/memblock.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/numa.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/lppaca.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/svm.h>
#समावेश <यंत्र/ultravisor.h>
#समावेश <यंत्र/rtas.h>

#समावेश "setup.h"

#अगर_अघोषित CONFIG_SMP
#घोषणा boot_cpuid 0
#पूर्ण_अगर

अटल व्योम *__init alloc_paca_data(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align,
				अचिन्हित दीर्घ limit, पूर्णांक cpu)
अणु
	व्योम *ptr;
	पूर्णांक nid;

	/*
	 * boot_cpuid paca is allocated very early beक्रमe cpu_to_node is up.
	 * Set bottom-up mode, because the boot CPU should be on node-0,
	 * which will put its paca in the right place.
	 */
	अगर (cpu == boot_cpuid) अणु
		nid = NUMA_NO_NODE;
		memblock_set_bottom_up(true);
	पूर्ण अन्यथा अणु
		nid = early_cpu_to_node(cpu);
	पूर्ण

	ptr = memblock_alloc_try_nid(size, align, MEMBLOCK_LOW_LIMIT,
				     limit, nid);
	अगर (!ptr)
		panic("cannot allocate paca data");

	अगर (cpu == boot_cpuid)
		memblock_set_bottom_up(false);

	वापस ptr;
पूर्ण

#अगर_घोषित CONFIG_PPC_PSERIES

#घोषणा LPPACA_SIZE 0x400

अटल व्योम *__init alloc_shared_lppaca(अचिन्हित दीर्घ size, अचिन्हित दीर्घ limit,
					पूर्णांक cpu)
अणु
	माप_प्रकार shared_lppaca_total_size = PAGE_ALIGN(nr_cpu_ids * LPPACA_SIZE);
	अटल अचिन्हित दीर्घ shared_lppaca_size;
	अटल व्योम *shared_lppaca;
	व्योम *ptr;

	अगर (!shared_lppaca) अणु
		memblock_set_bottom_up(true);

		/*
		 * See Documentation/घातerpc/ultravisor.rst क्रम more details.
		 *
		 * UV/HV data sharing is in PAGE_SIZE granularity. In order to
		 * minimize the number of pages shared, align the allocation to
		 * PAGE_SIZE.
		 */
		shared_lppaca =
			memblock_alloc_try_nid(shared_lppaca_total_size,
					       PAGE_SIZE, MEMBLOCK_LOW_LIMIT,
					       limit, NUMA_NO_NODE);
		अगर (!shared_lppaca)
			panic("cannot allocate shared data");

		memblock_set_bottom_up(false);
		uv_share_page(PHYS_PFN(__pa(shared_lppaca)),
			      shared_lppaca_total_size >> PAGE_SHIFT);
	पूर्ण

	ptr = shared_lppaca + shared_lppaca_size;
	shared_lppaca_size += size;

	/*
	 * This is very early in boot, so no harm करोne अगर the kernel crashes at
	 * this poपूर्णांक.
	 */
	BUG_ON(shared_lppaca_size > shared_lppaca_total_size);

	वापस ptr;
पूर्ण

/*
 * See यंत्र/lppaca.h क्रम more detail.
 *
 * lppaca काष्ठाures must must be 1kB in size, L1 cache line aligned,
 * and not cross 4kB boundary. A 1kB size and 1kB alignment will satisfy
 * these requirements.
 */
अटल अंतरभूत व्योम init_lppaca(काष्ठा lppaca *lppaca)
अणु
	BUILD_BUG_ON(माप(काष्ठा lppaca) != 640);

	*lppaca = (काष्ठा lppaca) अणु
		.desc = cpu_to_be32(0xd397d781),	/* "LpPa" */
		.size = cpu_to_be16(LPPACA_SIZE),
		.fpregs_in_use = 1,
		.slb_count = cpu_to_be16(64),
		.vmxregs_in_use = 0,
		.page_ins = 0, पूर्ण;
पूर्ण;

अटल काष्ठा lppaca * __init new_lppaca(पूर्णांक cpu, अचिन्हित दीर्घ limit)
अणु
	काष्ठा lppaca *lp;

	BUILD_BUG_ON(माप(काष्ठा lppaca) > LPPACA_SIZE);

	अगर (early_cpu_has_feature(CPU_FTR_HVMODE))
		वापस शून्य;

	अगर (is_secure_guest())
		lp = alloc_shared_lppaca(LPPACA_SIZE, limit, cpu);
	अन्यथा
		lp = alloc_paca_data(LPPACA_SIZE, 0x400, limit, cpu);

	init_lppaca(lp);

	वापस lp;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

#अगर_घोषित CONFIG_PPC_BOOK3S_64

/*
 * 3 persistent SLBs are allocated here.  The buffer will be zero
 * initially, hence will all be invaild until we actually ग_लिखो them.
 *
 * If you make the number of persistent SLB entries dynamic, please also
 * update PR KVM to flush and restore them accordingly.
 */
अटल काष्ठा slb_shaकरोw * __init new_slb_shaकरोw(पूर्णांक cpu, अचिन्हित दीर्घ limit)
अणु
	काष्ठा slb_shaकरोw *s;

	अगर (cpu != boot_cpuid) अणु
		/*
		 * Boot CPU comes here beक्रमe early_radix_enabled
		 * is parsed (e.g., क्रम disable_radix). So allocate
		 * always and this will be fixed up in मुक्त_unused_pacas.
		 */
		अगर (early_radix_enabled())
			वापस शून्य;
	पूर्ण

	s = alloc_paca_data(माप(*s), L1_CACHE_BYTES, limit, cpu);

	s->persistent = cpu_to_be32(SLB_NUM_BOLTED);
	s->buffer_length = cpu_to_be32(माप(*s));

	वापस s;
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

#अगर_घोषित CONFIG_PPC_PSERIES
/**
 * new_rtas_args() - Allocates rtas args
 * @cpu:	CPU number
 * @limit:	Memory limit क्रम this allocation
 *
 * Allocates a काष्ठा rtas_args and वापस it's poपूर्णांकer,
 * अगर not in Hypervisor mode
 *
 * Return:	Poपूर्णांकer to allocated rtas_args
 *		शून्य अगर CPU in Hypervisor Mode
 */
अटल काष्ठा rtas_args * __init new_rtas_args(पूर्णांक cpu, अचिन्हित दीर्घ limit)
अणु
	limit = min_t(अचिन्हित दीर्घ, limit, RTAS_INSTANTIATE_MAX);

	अगर (early_cpu_has_feature(CPU_FTR_HVMODE))
		वापस शून्य;

	वापस alloc_paca_data(माप(काष्ठा rtas_args), L1_CACHE_BYTES,
			       limit, cpu);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

/* The Paca is an array with one entry per processor.  Each contains an
 * lppaca, which contains the inक्रमmation shared between the
 * hypervisor and Linux.
 * On प्रणालीs with hardware multi-thपढ़ोing, there are two thपढ़ोs
 * per processor.  The Paca array must contain an entry क्रम each thपढ़ो.
 * The VPD Areas will give a max logical processors = 2 * max physical
 * processors.  The processor VPD array needs one entry per physical
 * processor (not thपढ़ो).
 */
काष्ठा paca_काष्ठा **paca_ptrs __पढ़ो_mostly;
EXPORT_SYMBOL(paca_ptrs);

व्योम __init initialise_paca(काष्ठा paca_काष्ठा *new_paca, पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_PPC_PSERIES
	new_paca->lppaca_ptr = शून्य;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3E
	new_paca->kernel_pgd = swapper_pg_dir;
#पूर्ण_अगर
	new_paca->lock_token = 0x8000;
	new_paca->paca_index = cpu;
	new_paca->kernel_toc = kernel_toc_addr();
	new_paca->kernelbase = (अचिन्हित दीर्घ) _stext;
	/* Only set MSR:IR/DR when MMU is initialized */
	new_paca->kernel_msr = MSR_KERNEL & ~(MSR_IR | MSR_DR);
	new_paca->hw_cpu_id = 0xffff;
	new_paca->kexec_state = KEXEC_STATE_NONE;
	new_paca->__current = &init_task;
	new_paca->data_offset = 0xfeeeeeeeeeeeeeeeULL;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	new_paca->slb_shaकरोw_ptr = शून्य;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3E
	/* For now -- अगर we have thपढ़ोs this will be adjusted later */
	new_paca->tcd_ptr = &new_paca->tcd;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_PSERIES
	new_paca->rtas_args_reentrant = शून्य;
#पूर्ण_अगर
पूर्ण

/* Put the paca poपूर्णांकer पूर्णांकo r13 and SPRG_PACA */
व्योम setup_paca(काष्ठा paca_काष्ठा *new_paca)
अणु
	/* Setup r13 */
	local_paca = new_paca;

#अगर_घोषित CONFIG_PPC_BOOK3E
	/* On Book3E, initialize the TLB miss exception frames */
	mtspr(SPRN_SPRG_TLB_EXFRAME, local_paca->extlb);
#अन्यथा
	/*
	 * In HV mode, we setup both HPACA and PACA to aव्योम problems
	 * अगर we करो a GET_PACA() beक्रमe the feature fixups have been
	 * applied.
	 *
	 * Normally you should test against CPU_FTR_HVMODE, but CPU features
	 * are not yet set up when we first reach here.
	 */
	अगर (mfmsr() & MSR_HV)
		mtspr(SPRN_SPRG_HPACA, local_paca);
#पूर्ण_अगर
	mtspr(SPRN_SPRG_PACA, local_paca);

पूर्ण

अटल पूर्णांक __initdata paca_nr_cpu_ids;
अटल पूर्णांक __initdata paca_ptrs_size;
अटल पूर्णांक __initdata paca_काष्ठा_size;

व्योम __init allocate_paca_ptrs(व्योम)
अणु
	paca_nr_cpu_ids = nr_cpu_ids;

	paca_ptrs_size = माप(काष्ठा paca_काष्ठा *) * nr_cpu_ids;
	paca_ptrs = memblock_alloc_raw(paca_ptrs_size, SMP_CACHE_BYTES);
	अगर (!paca_ptrs)
		panic("Failed to allocate %d bytes for paca pointers\n",
		      paca_ptrs_size);

	स_रखो(paca_ptrs, 0x88, paca_ptrs_size);
पूर्ण

व्योम __init allocate_paca(पूर्णांक cpu)
अणु
	u64 limit;
	काष्ठा paca_काष्ठा *paca;

	BUG_ON(cpu >= paca_nr_cpu_ids);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/*
	 * We access pacas in real mode, and cannot take SLB faults
	 * on them when in भव mode, so allocate them accordingly.
	 */
	limit = min(ppc64_bolted_size(), ppc64_rma_size);
#अन्यथा
	limit = ppc64_rma_size;
#पूर्ण_अगर

	paca = alloc_paca_data(माप(काष्ठा paca_काष्ठा), L1_CACHE_BYTES,
				limit, cpu);
	paca_ptrs[cpu] = paca;

	initialise_paca(paca, cpu);
#अगर_घोषित CONFIG_PPC_PSERIES
	paca->lppaca_ptr = new_lppaca(cpu, limit);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	paca->slb_shaकरोw_ptr = new_slb_shaकरोw(cpu, limit);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_PSERIES
	paca->rtas_args_reentrant = new_rtas_args(cpu, limit);
#पूर्ण_अगर
	paca_काष्ठा_size += माप(काष्ठा paca_काष्ठा);
पूर्ण

व्योम __init मुक्त_unused_pacas(व्योम)
अणु
	पूर्णांक new_ptrs_size;

	new_ptrs_size = माप(काष्ठा paca_काष्ठा *) * nr_cpu_ids;
	अगर (new_ptrs_size < paca_ptrs_size)
		memblock_मुक्त(__pa(paca_ptrs) + new_ptrs_size,
					paca_ptrs_size - new_ptrs_size);

	paca_nr_cpu_ids = nr_cpu_ids;
	paca_ptrs_size = new_ptrs_size;

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (early_radix_enabled()) अणु
		/* Ugly fixup, see new_slb_shaकरोw() */
		memblock_मुक्त(__pa(paca_ptrs[boot_cpuid]->slb_shaकरोw_ptr),
				माप(काष्ठा slb_shaकरोw));
		paca_ptrs[boot_cpuid]->slb_shaकरोw_ptr = शून्य;
	पूर्ण
#पूर्ण_अगर

	prपूर्णांकk(KERN_DEBUG "Allocated %u bytes for %u pacas\n",
			paca_ptrs_size + paca_काष्ठा_size, nr_cpu_ids);
पूर्ण

व्योम copy_mm_to_paca(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S
	mm_context_t *context = &mm->context;

	get_paca()->mm_ctx_id = context->id;
#अगर_घोषित CONFIG_PPC_MM_SLICES
	VM_BUG_ON(!mm_ctx_slb_addr_limit(context));
	get_paca()->mm_ctx_slb_addr_limit = mm_ctx_slb_addr_limit(context);
	स_नकल(&get_paca()->mm_ctx_low_slices_psize, mm_ctx_low_slices(context),
	       LOW_SLICE_ARRAY_SZ);
	स_नकल(&get_paca()->mm_ctx_high_slices_psize, mm_ctx_high_slices(context),
	       TASK_SLICE_ARRAY_SZ(context));
#अन्यथा /* CONFIG_PPC_MM_SLICES */
	get_paca()->mm_ctx_user_psize = context->user_psize;
	get_paca()->mm_ctx_sllp = context->sllp;
#पूर्ण_अगर
#अन्यथा /* !CONFIG_PPC_BOOK3S */
	वापस;
#पूर्ण_अगर
पूर्ण
