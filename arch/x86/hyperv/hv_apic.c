<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Hyper-V specअगरic APIC code.
 *
 * Copyright (C) 2018, Microsoft, Inc.
 *
 * Author : K. Y. Srinivasan <kys@microsoft.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/mshyperv.h>
#समावेश <यंत्र/apic.h>

#समावेश <यंत्र/trace/hyperv.h>

अटल काष्ठा apic orig_apic;

अटल u64 hv_apic_icr_पढ़ो(व्योम)
अणु
	u64 reg_val;

	rdmsrl(HV_X64_MSR_ICR, reg_val);
	वापस reg_val;
पूर्ण

अटल व्योम hv_apic_icr_ग_लिखो(u32 low, u32 id)
अणु
	u64 reg_val;

	reg_val = SET_APIC_DEST_FIELD(id);
	reg_val = reg_val << 32;
	reg_val |= low;

	wrmsrl(HV_X64_MSR_ICR, reg_val);
पूर्ण

अटल u32 hv_apic_पढ़ो(u32 reg)
अणु
	u32 reg_val, hi;

	चयन (reg) अणु
	हाल APIC_EOI:
		rdmsr(HV_X64_MSR_EOI, reg_val, hi);
		(व्योम)hi;
		वापस reg_val;
	हाल APIC_TASKPRI:
		rdmsr(HV_X64_MSR_TPR, reg_val, hi);
		(व्योम)hi;
		वापस reg_val;

	शेष:
		वापस native_apic_mem_पढ़ो(reg);
	पूर्ण
पूर्ण

अटल व्योम hv_apic_ग_लिखो(u32 reg, u32 val)
अणु
	चयन (reg) अणु
	हाल APIC_EOI:
		wrmsr(HV_X64_MSR_EOI, val, 0);
		अवरोध;
	हाल APIC_TASKPRI:
		wrmsr(HV_X64_MSR_TPR, val, 0);
		अवरोध;
	शेष:
		native_apic_mem_ग_लिखो(reg, val);
	पूर्ण
पूर्ण

अटल व्योम hv_apic_eoi_ग_लिखो(u32 reg, u32 val)
अणु
	काष्ठा hv_vp_assist_page *hvp = hv_vp_assist_page[smp_processor_id()];

	अगर (hvp && (xchg(&hvp->apic_assist, 0) & 0x1))
		वापस;

	wrmsr(HV_X64_MSR_EOI, val, 0);
पूर्ण

/*
 * IPI implementation on Hyper-V.
 */
अटल bool __send_ipi_mask_ex(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	काष्ठा hv_send_ipi_ex **arg;
	काष्ठा hv_send_ipi_ex *ipi_arg;
	अचिन्हित दीर्घ flags;
	पूर्णांक nr_bank = 0;
	u64 status = HV_STATUS_INVALID_PARAMETER;

	अगर (!(ms_hyperv.hपूर्णांकs & HV_X64_EX_PROCESSOR_MASKS_RECOMMENDED))
		वापस false;

	local_irq_save(flags);
	arg = (काष्ठा hv_send_ipi_ex **)this_cpu_ptr(hyperv_pcpu_input_arg);

	ipi_arg = *arg;
	अगर (unlikely(!ipi_arg))
		जाओ ipi_mask_ex_करोne;

	ipi_arg->vector = vector;
	ipi_arg->reserved = 0;
	ipi_arg->vp_set.valid_bank_mask = 0;

	अगर (!cpumask_equal(mask, cpu_present_mask)) अणु
		ipi_arg->vp_set.क्रमmat = HV_GENERIC_SET_SPARSE_4K;
		nr_bank = cpumask_to_vpset(&(ipi_arg->vp_set), mask);
	पूर्ण
	अगर (nr_bank < 0)
		जाओ ipi_mask_ex_करोne;
	अगर (!nr_bank)
		ipi_arg->vp_set.क्रमmat = HV_GENERIC_SET_ALL;

	status = hv_करो_rep_hypercall(HVCALL_SEND_IPI_EX, 0, nr_bank,
			      ipi_arg, शून्य);

ipi_mask_ex_करोne:
	local_irq_restore(flags);
	वापस hv_result_success(status);
पूर्ण

अटल bool __send_ipi_mask(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	पूर्णांक cur_cpu, vcpu;
	काष्ठा hv_send_ipi ipi_arg;
	u64 status;

	trace_hyperv_send_ipi_mask(mask, vector);

	अगर (cpumask_empty(mask))
		वापस true;

	अगर (!hv_hypercall_pg)
		वापस false;

	अगर ((vector < HV_IPI_LOW_VECTOR) || (vector > HV_IPI_HIGH_VECTOR))
		वापस false;

	/*
	 * From the supplied CPU set we need to figure out अगर we can get away
	 * with cheaper HVCALL_SEND_IPI hypercall. This is possible when the
	 * highest VP number in the set is < 64. As VP numbers are usually in
	 * ascending order and match Linux CPU ids, here is an optimization:
	 * we check the VP number क्रम the highest bit in the supplied set first
	 * so we can quickly find out अगर using HVCALL_SEND_IPI_EX hypercall is
	 * a must. We will also check all VP numbers when walking the supplied
	 * CPU set to reमुख्य correct in all हालs.
	 */
	अगर (hv_cpu_number_to_vp_number(cpumask_last(mask)) >= 64)
		जाओ करो_ex_hypercall;

	ipi_arg.vector = vector;
	ipi_arg.cpu_mask = 0;

	क्रम_each_cpu(cur_cpu, mask) अणु
		vcpu = hv_cpu_number_to_vp_number(cur_cpu);
		अगर (vcpu == VP_INVAL)
			वापस false;

		/*
		 * This particular version of the IPI hypercall can
		 * only target upto 64 CPUs.
		 */
		अगर (vcpu >= 64)
			जाओ करो_ex_hypercall;

		__set_bit(vcpu, (अचिन्हित दीर्घ *)&ipi_arg.cpu_mask);
	पूर्ण

	status = hv_करो_fast_hypercall16(HVCALL_SEND_IPI, ipi_arg.vector,
				     ipi_arg.cpu_mask);
	वापस hv_result_success(status);

करो_ex_hypercall:
	वापस __send_ipi_mask_ex(mask, vector);
पूर्ण

अटल bool __send_ipi_one(पूर्णांक cpu, पूर्णांक vector)
अणु
	पूर्णांक vp = hv_cpu_number_to_vp_number(cpu);
	u64 status;

	trace_hyperv_send_ipi_one(cpu, vector);

	अगर (!hv_hypercall_pg || (vp == VP_INVAL))
		वापस false;

	अगर ((vector < HV_IPI_LOW_VECTOR) || (vector > HV_IPI_HIGH_VECTOR))
		वापस false;

	अगर (vp >= 64)
		वापस __send_ipi_mask_ex(cpumask_of(cpu), vector);

	status = hv_करो_fast_hypercall16(HVCALL_SEND_IPI, vector, BIT_ULL(vp));
	वापस hv_result_success(status);
पूर्ण

अटल व्योम hv_send_ipi(पूर्णांक cpu, पूर्णांक vector)
अणु
	अगर (!__send_ipi_one(cpu, vector))
		orig_apic.send_IPI(cpu, vector);
पूर्ण

अटल व्योम hv_send_ipi_mask(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	अगर (!__send_ipi_mask(mask, vector))
		orig_apic.send_IPI_mask(mask, vector);
पूर्ण

अटल व्योम hv_send_ipi_mask_allbutself(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();
	काष्ठा cpumask new_mask;
	स्थिर काष्ठा cpumask *local_mask;

	cpumask_copy(&new_mask, mask);
	cpumask_clear_cpu(this_cpu, &new_mask);
	local_mask = &new_mask;
	अगर (!__send_ipi_mask(local_mask, vector))
		orig_apic.send_IPI_mask_allbutself(mask, vector);
पूर्ण

अटल व्योम hv_send_ipi_allbutself(पूर्णांक vector)
अणु
	hv_send_ipi_mask_allbutself(cpu_online_mask, vector);
पूर्ण

अटल व्योम hv_send_ipi_all(पूर्णांक vector)
अणु
	अगर (!__send_ipi_mask(cpu_online_mask, vector))
		orig_apic.send_IPI_all(vector);
पूर्ण

अटल व्योम hv_send_ipi_self(पूर्णांक vector)
अणु
	अगर (!__send_ipi_one(smp_processor_id(), vector))
		orig_apic.send_IPI_self(vector);
पूर्ण

व्योम __init hv_apic_init(व्योम)
अणु
	अगर (ms_hyperv.hपूर्णांकs & HV_X64_CLUSTER_IPI_RECOMMENDED) अणु
		pr_info("Hyper-V: Using IPI hypercalls\n");
		/*
		 * Set the IPI entry poपूर्णांकs.
		 */
		orig_apic = *apic;

		apic->send_IPI = hv_send_ipi;
		apic->send_IPI_mask = hv_send_ipi_mask;
		apic->send_IPI_mask_allbutself = hv_send_ipi_mask_allbutself;
		apic->send_IPI_allbutself = hv_send_ipi_allbutself;
		apic->send_IPI_all = hv_send_ipi_all;
		apic->send_IPI_self = hv_send_ipi_self;
	पूर्ण

	अगर (ms_hyperv.hपूर्णांकs & HV_X64_APIC_ACCESS_RECOMMENDED) अणु
		pr_info("Hyper-V: Using enlightened APIC (%s mode)",
			x2apic_enabled() ? "x2apic" : "xapic");
		/*
		 * When in x2apic mode, करोn't use the Hyper-V specअगरic APIC
		 * accessors since the field layout in the ICR रेजिस्टर is
		 * dअगरferent in x2apic mode. Furthermore, the architectural
		 * x2apic MSRs function just as well as the Hyper-V
		 * synthetic APIC MSRs, so there's no benefit in having
		 * separate Hyper-V accessors क्रम x2apic mode. The only
		 * exception is hv_apic_eoi_ग_लिखो, because it benefits from
		 * lazy EOI when available, but the same accessor works क्रम
		 * both xapic and x2apic because the field layout is the same.
		 */
		apic_set_eoi_ग_लिखो(hv_apic_eoi_ग_लिखो);
		अगर (!x2apic_enabled()) अणु
			apic->पढ़ो      = hv_apic_पढ़ो;
			apic->ग_लिखो     = hv_apic_ग_लिखो;
			apic->icr_ग_लिखो = hv_apic_icr_ग_लिखो;
			apic->icr_पढ़ो  = hv_apic_icr_पढ़ो;
		पूर्ण
	पूर्ण
पूर्ण
