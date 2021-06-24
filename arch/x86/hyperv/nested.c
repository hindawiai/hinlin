<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Hyper-V nested भवization code.
 *
 * Copyright (C) 2018, Microsoft, Inc.
 *
 * Author : Lan Tianyu <Tianyu.Lan@microsoft.com>
 */
#घोषणा pr_fmt(fmt)  "Hyper-V: " fmt


#समावेश <linux/types.h>
#समावेश <यंत्र/hyperv-tlfs.h>
#समावेश <यंत्र/mshyperv.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश <यंत्र/trace/hyperv.h>

पूर्णांक hyperv_flush_guest_mapping(u64 as)
अणु
	काष्ठा hv_guest_mapping_flush **flush_pcpu;
	काष्ठा hv_guest_mapping_flush *flush;
	u64 status;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ENOTSUPP;

	अगर (!hv_hypercall_pg)
		जाओ fault;

	local_irq_save(flags);

	flush_pcpu = (काष्ठा hv_guest_mapping_flush **)
		this_cpu_ptr(hyperv_pcpu_input_arg);

	flush = *flush_pcpu;

	अगर (unlikely(!flush)) अणु
		local_irq_restore(flags);
		जाओ fault;
	पूर्ण

	flush->address_space = as;
	flush->flags = 0;

	status = hv_करो_hypercall(HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_SPACE,
				 flush, शून्य);
	local_irq_restore(flags);

	अगर (hv_result_success(status))
		ret = 0;

fault:
	trace_hyperv_nested_flush_guest_mapping(as, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hyperv_flush_guest_mapping);

पूर्णांक hyperv_fill_flush_guest_mapping_list(
		काष्ठा hv_guest_mapping_flush_list *flush,
		u64 start_gfn, u64 pages)
अणु
	u64 cur = start_gfn;
	u64 additional_pages;
	पूर्णांक gpa_n = 0;

	करो अणु
		/*
		 * If flush requests exceed max flush count, go back to
		 * flush tlbs without range.
		 */
		अगर (gpa_n >= HV_MAX_FLUSH_REP_COUNT)
			वापस -ENOSPC;

		additional_pages = min_t(u64, pages, HV_MAX_FLUSH_PAGES) - 1;

		flush->gpa_list[gpa_n].page.additional_pages = additional_pages;
		flush->gpa_list[gpa_n].page.largepage = false;
		flush->gpa_list[gpa_n].page.basepfn = cur;

		pages -= additional_pages + 1;
		cur += additional_pages + 1;
		gpa_n++;
	पूर्ण जबतक (pages > 0);

	वापस gpa_n;
पूर्ण
EXPORT_SYMBOL_GPL(hyperv_fill_flush_guest_mapping_list);

पूर्णांक hyperv_flush_guest_mapping_range(u64 as,
		hyperv_fill_flush_list_func fill_flush_list_func, व्योम *data)
अणु
	काष्ठा hv_guest_mapping_flush_list **flush_pcpu;
	काष्ठा hv_guest_mapping_flush_list *flush;
	u64 status;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ENOTSUPP;
	पूर्णांक gpa_n = 0;

	अगर (!hv_hypercall_pg || !fill_flush_list_func)
		जाओ fault;

	local_irq_save(flags);

	flush_pcpu = (काष्ठा hv_guest_mapping_flush_list **)
		this_cpu_ptr(hyperv_pcpu_input_arg);

	flush = *flush_pcpu;
	अगर (unlikely(!flush)) अणु
		local_irq_restore(flags);
		जाओ fault;
	पूर्ण

	flush->address_space = as;
	flush->flags = 0;

	gpa_n = fill_flush_list_func(flush, data);
	अगर (gpa_n < 0) अणु
		local_irq_restore(flags);
		जाओ fault;
	पूर्ण

	status = hv_करो_rep_hypercall(HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST,
				     gpa_n, 0, flush, शून्य);

	local_irq_restore(flags);

	अगर (hv_result_success(status))
		ret = 0;
	अन्यथा
		ret = hv_result(status);
fault:
	trace_hyperv_nested_flush_guest_mapping_range(as, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hyperv_flush_guest_mapping_range);
