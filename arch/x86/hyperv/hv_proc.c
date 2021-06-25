<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/acpi.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/minmax.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/mshyperv.h>
#समावेश <यंत्र/apic.h>

#समावेश <यंत्र/trace/hyperv.h>

/*
 * See काष्ठा hv_deposit_memory. The first u64 is partition ID, the rest
 * are GPAs.
 */
#घोषणा HV_DEPOSIT_MAX (HV_HYP_PAGE_SIZE / माप(u64) - 1)

/* Deposits exact number of pages. Must be called with पूर्णांकerrupts enabled.  */
पूर्णांक hv_call_deposit_pages(पूर्णांक node, u64 partition_id, u32 num_pages)
अणु
	काष्ठा page **pages, *page;
	पूर्णांक *counts;
	पूर्णांक num_allocations;
	पूर्णांक i, j, page_count;
	पूर्णांक order;
	u64 status;
	पूर्णांक ret;
	u64 base_pfn;
	काष्ठा hv_deposit_memory *input_page;
	अचिन्हित दीर्घ flags;

	अगर (num_pages > HV_DEPOSIT_MAX)
		वापस -E2BIG;
	अगर (!num_pages)
		वापस 0;

	/* One buffer क्रम page poपूर्णांकers and counts */
	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;
	pages = page_address(page);

	counts = kसुस्मृति(HV_DEPOSIT_MAX, माप(पूर्णांक), GFP_KERNEL);
	अगर (!counts) अणु
		मुक्त_page((अचिन्हित दीर्घ)pages);
		वापस -ENOMEM;
	पूर्ण

	/* Allocate all the pages beक्रमe disabling पूर्णांकerrupts */
	i = 0;

	जबतक (num_pages) अणु
		/* Find highest order we can actually allocate */
		order = 31 - __builtin_clz(num_pages);

		जबतक (1) अणु
			pages[i] = alloc_pages_node(node, GFP_KERNEL, order);
			अगर (pages[i])
				अवरोध;
			अगर (!order) अणु
				ret = -ENOMEM;
				num_allocations = i;
				जाओ err_मुक्त_allocations;
			पूर्ण
			--order;
		पूर्ण

		split_page(pages[i], order);
		counts[i] = 1 << order;
		num_pages -= counts[i];
		i++;
	पूर्ण
	num_allocations = i;

	local_irq_save(flags);

	input_page = *this_cpu_ptr(hyperv_pcpu_input_arg);

	input_page->partition_id = partition_id;

	/* Populate gpa_page_list - these will fit on the input page */
	क्रम (i = 0, page_count = 0; i < num_allocations; ++i) अणु
		base_pfn = page_to_pfn(pages[i]);
		क्रम (j = 0; j < counts[i]; ++j, ++page_count)
			input_page->gpa_page_list[page_count] = base_pfn + j;
	पूर्ण
	status = hv_करो_rep_hypercall(HVCALL_DEPOSIT_MEMORY,
				     page_count, 0, input_page, शून्य);
	local_irq_restore(flags);
	अगर (!hv_result_success(status)) अणु
		pr_err("Failed to deposit pages: %lld\n", status);
		ret = hv_result(status);
		जाओ err_मुक्त_allocations;
	पूर्ण

	ret = 0;
	जाओ मुक्त_buf;

err_मुक्त_allocations:
	क्रम (i = 0; i < num_allocations; ++i) अणु
		base_pfn = page_to_pfn(pages[i]);
		क्रम (j = 0; j < counts[i]; ++j)
			__मुक्त_page(pfn_to_page(base_pfn + j));
	पूर्ण

मुक्त_buf:
	मुक्त_page((अचिन्हित दीर्घ)pages);
	kमुक्त(counts);
	वापस ret;
पूर्ण

पूर्णांक hv_call_add_logical_proc(पूर्णांक node, u32 lp_index, u32 apic_id)
अणु
	काष्ठा hv_add_logical_processor_in *input;
	काष्ठा hv_add_logical_processor_out *output;
	u64 status;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = HV_STATUS_SUCCESS;
	पूर्णांक pxm = node_to_pxm(node);

	/*
	 * When adding a logical processor, the hypervisor may वापस
	 * HV_STATUS_INSUFFICIENT_MEMORY. When that happens, we deposit more
	 * pages and retry.
	 */
	करो अणु
		local_irq_save(flags);

		input = *this_cpu_ptr(hyperv_pcpu_input_arg);
		/* We करोn't करो anything with the output right now */
		output = *this_cpu_ptr(hyperv_pcpu_output_arg);

		input->lp_index = lp_index;
		input->apic_id = apic_id;
		input->flags = 0;
		input->proximity_करोमुख्य_info.करोमुख्य_id = pxm;
		input->proximity_करोमुख्य_info.flags.reserved = 0;
		input->proximity_करोमुख्य_info.flags.proximity_info_valid = 1;
		input->proximity_करोमुख्य_info.flags.proximity_preferred = 1;
		status = hv_करो_hypercall(HVCALL_ADD_LOGICAL_PROCESSOR,
					 input, output);
		local_irq_restore(flags);

		अगर (hv_result(status) != HV_STATUS_INSUFFICIENT_MEMORY) अणु
			अगर (!hv_result_success(status)) अणु
				pr_err("%s: cpu %u apic ID %u, %lld\n", __func__,
				       lp_index, apic_id, status);
				ret = hv_result(status);
			पूर्ण
			अवरोध;
		पूर्ण
		ret = hv_call_deposit_pages(node, hv_current_partition_id, 1);
	पूर्ण जबतक (!ret);

	वापस ret;
पूर्ण

पूर्णांक hv_call_create_vp(पूर्णांक node, u64 partition_id, u32 vp_index, u32 flags)
अणु
	काष्ठा hv_create_vp *input;
	u64 status;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक ret = HV_STATUS_SUCCESS;
	पूर्णांक pxm = node_to_pxm(node);

	/* Root VPs करोn't seem to need pages deposited */
	अगर (partition_id != hv_current_partition_id) अणु
		/* The value 90 is empirically determined. It may change. */
		ret = hv_call_deposit_pages(node, partition_id, 90);
		अगर (ret)
			वापस ret;
	पूर्ण

	करो अणु
		local_irq_save(irq_flags);

		input = *this_cpu_ptr(hyperv_pcpu_input_arg);

		input->partition_id = partition_id;
		input->vp_index = vp_index;
		input->flags = flags;
		input->subnode_type = HvSubnodeAny;
		अगर (node != NUMA_NO_NODE) अणु
			input->proximity_करोमुख्य_info.करोमुख्य_id = pxm;
			input->proximity_करोमुख्य_info.flags.reserved = 0;
			input->proximity_करोमुख्य_info.flags.proximity_info_valid = 1;
			input->proximity_करोमुख्य_info.flags.proximity_preferred = 1;
		पूर्ण अन्यथा अणु
			input->proximity_करोमुख्य_info.as_uपूर्णांक64 = 0;
		पूर्ण
		status = hv_करो_hypercall(HVCALL_CREATE_VP, input, शून्य);
		local_irq_restore(irq_flags);

		अगर (hv_result(status) != HV_STATUS_INSUFFICIENT_MEMORY) अणु
			अगर (!hv_result_success(status)) अणु
				pr_err("%s: vcpu %u, lp %u, %lld\n", __func__,
				       vp_index, flags, status);
				ret = hv_result(status);
			पूर्ण
			अवरोध;
		पूर्ण
		ret = hv_call_deposit_pages(node, partition_id, 1);

	पूर्ण जबतक (!ret);

	वापस ret;
पूर्ण

