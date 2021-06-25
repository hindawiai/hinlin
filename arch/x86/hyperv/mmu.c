<शैली गुरु>
#घोषणा pr_fmt(fmt)  "Hyper-V: " fmt

#समावेश <linux/hyperv.h>
#समावेश <linux/log2.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/mshyperv.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/tlb.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <यंत्र/trace/hyperv.h>

/* Each gva in gबहु_सूची encodes up to 4096 pages to flush */
#घोषणा HV_TLB_FLUSH_UNIT (4096 * PAGE_SIZE)

अटल u64 hyperv_flush_tlb_others_ex(स्थिर काष्ठा cpumask *cpus,
				      स्थिर काष्ठा flush_tlb_info *info);

/*
 * Fills in gबहु_सूची starting from offset. Returns the number of items added.
 */
अटल अंतरभूत पूर्णांक fill_gबहु_सूची(u64 gबहु_सूची[], पूर्णांक offset,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	पूर्णांक gva_n = offset;
	अचिन्हित दीर्घ cur = start, dअगरf;

	करो अणु
		dअगरf = end > cur ? end - cur : 0;

		gबहु_सूची[gva_n] = cur & PAGE_MASK;
		/*
		 * Lower 12 bits encode the number of additional
		 * pages to flush (in addition to the 'cur' page).
		 */
		अगर (dअगरf >= HV_TLB_FLUSH_UNIT) अणु
			gबहु_सूची[gva_n] |= ~PAGE_MASK;
			cur += HV_TLB_FLUSH_UNIT;
		पूर्ण  अन्यथा अगर (dअगरf) अणु
			gबहु_सूची[gva_n] |= (dअगरf - 1) >> PAGE_SHIFT;
			cur = end;
		पूर्ण

		gva_n++;

	पूर्ण जबतक (cur < end);

	वापस gva_n - offset;
पूर्ण

अटल व्योम hyperv_flush_tlb_multi(स्थिर काष्ठा cpumask *cpus,
				   स्थिर काष्ठा flush_tlb_info *info)
अणु
	पूर्णांक cpu, vcpu, gva_n, max_gvas;
	काष्ठा hv_tlb_flush **flush_pcpu;
	काष्ठा hv_tlb_flush *flush;
	u64 status;
	अचिन्हित दीर्घ flags;

	trace_hyperv_mmu_flush_tlb_multi(cpus, info);

	अगर (!hv_hypercall_pg)
		जाओ करो_native;

	local_irq_save(flags);

	/*
	 * Only check the mask _after_ पूर्णांकerrupt has been disabled to aव्योम the
	 * mask changing under our feet.
	 */
	अगर (cpumask_empty(cpus)) अणु
		local_irq_restore(flags);
		वापस;
	पूर्ण

	flush_pcpu = (काष्ठा hv_tlb_flush **)
		     this_cpu_ptr(hyperv_pcpu_input_arg);

	flush = *flush_pcpu;

	अगर (unlikely(!flush)) अणु
		local_irq_restore(flags);
		जाओ करो_native;
	पूर्ण

	अगर (info->mm) अणु
		/*
		 * AddressSpace argument must match the CR3 with PCID bits
		 * stripped out.
		 */
		flush->address_space = virt_to_phys(info->mm->pgd);
		flush->address_space &= CR3_ADDR_MASK;
		flush->flags = 0;
	पूर्ण अन्यथा अणु
		flush->address_space = 0;
		flush->flags = HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES;
	पूर्ण

	flush->processor_mask = 0;
	अगर (cpumask_equal(cpus, cpu_present_mask)) अणु
		flush->flags |= HV_FLUSH_ALL_PROCESSORS;
	पूर्ण अन्यथा अणु
		/*
		 * From the supplied CPU set we need to figure out अगर we can get
		 * away with cheaper HVCALL_FLUSH_VIRTUAL_ADDRESS_अणुLIST,SPACEपूर्ण
		 * hypercalls. This is possible when the highest VP number in
		 * the set is < 64. As VP numbers are usually in ascending order
		 * and match Linux CPU ids, here is an optimization: we check
		 * the VP number क्रम the highest bit in the supplied set first
		 * so we can quickly find out अगर using *_EX hypercalls is a
		 * must. We will also check all VP numbers when walking the
		 * supplied CPU set to reमुख्य correct in all हालs.
		 */
		अगर (hv_cpu_number_to_vp_number(cpumask_last(cpus)) >= 64)
			जाओ करो_ex_hypercall;

		क्रम_each_cpu(cpu, cpus) अणु
			vcpu = hv_cpu_number_to_vp_number(cpu);
			अगर (vcpu == VP_INVAL) अणु
				local_irq_restore(flags);
				जाओ करो_native;
			पूर्ण

			अगर (vcpu >= 64)
				जाओ करो_ex_hypercall;

			__set_bit(vcpu, (अचिन्हित दीर्घ *)
				  &flush->processor_mask);
		पूर्ण
	पूर्ण

	/*
	 * We can flush not more than max_gvas with one hypercall. Flush the
	 * whole address space अगर we were asked to करो more.
	 */
	max_gvas = (PAGE_SIZE - माप(*flush)) / माप(flush->gबहु_सूची[0]);

	अगर (info->end == TLB_FLUSH_ALL) अणु
		flush->flags |= HV_FLUSH_NON_GLOBAL_MAPPINGS_ONLY;
		status = hv_करो_hypercall(HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE,
					 flush, शून्य);
	पूर्ण अन्यथा अगर (info->end &&
		   ((info->end - info->start)/HV_TLB_FLUSH_UNIT) > max_gvas) अणु
		status = hv_करो_hypercall(HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE,
					 flush, शून्य);
	पूर्ण अन्यथा अणु
		gva_n = fill_gबहु_सूची(flush->gबहु_सूची, 0,
				      info->start, info->end);
		status = hv_करो_rep_hypercall(HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST,
					     gva_n, 0, flush, शून्य);
	पूर्ण
	जाओ check_status;

करो_ex_hypercall:
	status = hyperv_flush_tlb_others_ex(cpus, info);

check_status:
	local_irq_restore(flags);

	अगर (hv_result_success(status))
		वापस;
करो_native:
	native_flush_tlb_multi(cpus, info);
पूर्ण

अटल u64 hyperv_flush_tlb_others_ex(स्थिर काष्ठा cpumask *cpus,
				      स्थिर काष्ठा flush_tlb_info *info)
अणु
	पूर्णांक nr_bank = 0, max_gvas, gva_n;
	काष्ठा hv_tlb_flush_ex **flush_pcpu;
	काष्ठा hv_tlb_flush_ex *flush;
	u64 status;

	अगर (!(ms_hyperv.hपूर्णांकs & HV_X64_EX_PROCESSOR_MASKS_RECOMMENDED))
		वापस HV_STATUS_INVALID_PARAMETER;

	flush_pcpu = (काष्ठा hv_tlb_flush_ex **)
		     this_cpu_ptr(hyperv_pcpu_input_arg);

	flush = *flush_pcpu;

	अगर (info->mm) अणु
		/*
		 * AddressSpace argument must match the CR3 with PCID bits
		 * stripped out.
		 */
		flush->address_space = virt_to_phys(info->mm->pgd);
		flush->address_space &= CR3_ADDR_MASK;
		flush->flags = 0;
	पूर्ण अन्यथा अणु
		flush->address_space = 0;
		flush->flags = HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES;
	पूर्ण

	flush->hv_vp_set.valid_bank_mask = 0;

	flush->hv_vp_set.क्रमmat = HV_GENERIC_SET_SPARSE_4K;
	nr_bank = cpumask_to_vpset(&(flush->hv_vp_set), cpus);
	अगर (nr_bank < 0)
		वापस HV_STATUS_INVALID_PARAMETER;

	/*
	 * We can flush not more than max_gvas with one hypercall. Flush the
	 * whole address space अगर we were asked to करो more.
	 */
	max_gvas =
		(PAGE_SIZE - माप(*flush) - nr_bank *
		 माप(flush->hv_vp_set.bank_contents[0])) /
		माप(flush->gबहु_सूची[0]);

	अगर (info->end == TLB_FLUSH_ALL) अणु
		flush->flags |= HV_FLUSH_NON_GLOBAL_MAPPINGS_ONLY;
		status = hv_करो_rep_hypercall(
			HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE_EX,
			0, nr_bank, flush, शून्य);
	पूर्ण अन्यथा अगर (info->end &&
		   ((info->end - info->start)/HV_TLB_FLUSH_UNIT) > max_gvas) अणु
		status = hv_करो_rep_hypercall(
			HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE_EX,
			0, nr_bank, flush, शून्य);
	पूर्ण अन्यथा अणु
		gva_n = fill_gबहु_सूची(flush->gबहु_सूची, nr_bank,
				      info->start, info->end);
		status = hv_करो_rep_hypercall(
			HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST_EX,
			gva_n, nr_bank, flush, शून्य);
	पूर्ण

	वापस status;
पूर्ण

व्योम hyperv_setup_mmu_ops(व्योम)
अणु
	अगर (!(ms_hyperv.hपूर्णांकs & HV_X64_REMOTE_TLB_FLUSH_RECOMMENDED))
		वापस;

	pr_info("Using hypercall for remote TLB flush\n");
	pv_ops.mmu.flush_tlb_multi = hyperv_flush_tlb_multi;
	pv_ops.mmu.tlb_हटाओ_table = tlb_हटाओ_table;
पूर्ण
