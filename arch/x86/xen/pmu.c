<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/xen/hypercall.h>
#समावेश <xen/xen.h>
#समावेश <xen/page.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/vcpu.h>
#समावेश <xen/पूर्णांकerface/xenpmu.h>

#समावेश "xen-ops.h"
#समावेश "pmu.h"

/* x86_pmu.handle_irq definition */
#समावेश "../events/perf_event.h"

#घोषणा XENPMU_IRQ_PROCESSING    1
काष्ठा xenpmu अणु
	/* Shared page between hypervisor and करोमुख्य */
	काष्ठा xen_pmu_data *xenpmu_data;

	uपूर्णांक8_t flags;
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा xenpmu, xenpmu_shared);
#घोषणा get_xenpmu_data()    (this_cpu_ptr(&xenpmu_shared)->xenpmu_data)
#घोषणा get_xenpmu_flags()   (this_cpu_ptr(&xenpmu_shared)->flags)

/* Macro क्रम computing address of a PMU MSR bank */
#घोषणा field_offset(ctxt, field) ((व्योम *)((uपूर्णांकptr_t)ctxt + \
					    (uपूर्णांकptr_t)ctxt->field))

/* AMD PMU */
#घोषणा F15H_NUM_COUNTERS   6
#घोषणा F10H_NUM_COUNTERS   4

अटल __पढ़ो_mostly uपूर्णांक32_t amd_counters_base;
अटल __पढ़ो_mostly uपूर्णांक32_t amd_ctrls_base;
अटल __पढ़ो_mostly पूर्णांक amd_msr_step;
अटल __पढ़ो_mostly पूर्णांक k7_counters_mirrored;
अटल __पढ़ो_mostly पूर्णांक amd_num_counters;

/* Intel PMU */
#घोषणा MSR_TYPE_COUNTER            0
#घोषणा MSR_TYPE_CTRL               1
#घोषणा MSR_TYPE_GLOBAL             2
#घोषणा MSR_TYPE_ARCH_COUNTER       3
#घोषणा MSR_TYPE_ARCH_CTRL          4

/* Number of general pmu रेजिस्टरs (CPUID.EAX[0xa].EAX[8..15]) */
#घोषणा PMU_GENERAL_NR_SHIFT        8
#घोषणा PMU_GENERAL_NR_BITS         8
#घोषणा PMU_GENERAL_NR_MASK         (((1 << PMU_GENERAL_NR_BITS) - 1) \
				     << PMU_GENERAL_NR_SHIFT)

/* Number of fixed pmu रेजिस्टरs (CPUID.EDX[0xa].EDX[0..4]) */
#घोषणा PMU_FIXED_NR_SHIFT          0
#घोषणा PMU_FIXED_NR_BITS           5
#घोषणा PMU_FIXED_NR_MASK           (((1 << PMU_FIXED_NR_BITS) - 1) \
				     << PMU_FIXED_NR_SHIFT)

/* Alias रेजिस्टरs (0x4c1) क्रम full-width ग_लिखोs to PMCs */
#घोषणा MSR_PMC_ALIAS_MASK          (~(MSR_IA32_PERFCTR0 ^ MSR_IA32_PMC0))

#घोषणा INTEL_PMC_TYPE_SHIFT        30

अटल __पढ़ो_mostly पूर्णांक पूर्णांकel_num_arch_counters, पूर्णांकel_num_fixed_counters;


अटल व्योम xen_pmu_arch_init(व्योम)
अणु
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD) अणु

		चयन (boot_cpu_data.x86) अणु
		हाल 0x15:
			amd_num_counters = F15H_NUM_COUNTERS;
			amd_counters_base = MSR_F15H_PERF_CTR;
			amd_ctrls_base = MSR_F15H_PERF_CTL;
			amd_msr_step = 2;
			k7_counters_mirrored = 1;
			अवरोध;
		हाल 0x10:
		हाल 0x12:
		हाल 0x14:
		हाल 0x16:
		शेष:
			amd_num_counters = F10H_NUM_COUNTERS;
			amd_counters_base = MSR_K7_PERFCTR0;
			amd_ctrls_base = MSR_K7_EVNTSEL0;
			amd_msr_step = 1;
			k7_counters_mirrored = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON) अणु
		amd_num_counters = F10H_NUM_COUNTERS;
		amd_counters_base = MSR_K7_PERFCTR0;
		amd_ctrls_base = MSR_K7_EVNTSEL0;
		amd_msr_step = 1;
		k7_counters_mirrored = 0;
	पूर्ण अन्यथा अणु
		uपूर्णांक32_t eax, ebx, ecx, edx;

		cpuid(0xa, &eax, &ebx, &ecx, &edx);

		पूर्णांकel_num_arch_counters = (eax & PMU_GENERAL_NR_MASK) >>
			PMU_GENERAL_NR_SHIFT;
		पूर्णांकel_num_fixed_counters = (edx & PMU_FIXED_NR_MASK) >>
			PMU_FIXED_NR_SHIFT;
	पूर्ण
पूर्ण

अटल अंतरभूत uपूर्णांक32_t get_fam15h_addr(u32 addr)
अणु
	चयन (addr) अणु
	हाल MSR_K7_PERFCTR0:
	हाल MSR_K7_PERFCTR1:
	हाल MSR_K7_PERFCTR2:
	हाल MSR_K7_PERFCTR3:
		वापस MSR_F15H_PERF_CTR + (addr - MSR_K7_PERFCTR0);
	हाल MSR_K7_EVNTSEL0:
	हाल MSR_K7_EVNTSEL1:
	हाल MSR_K7_EVNTSEL2:
	हाल MSR_K7_EVNTSEL3:
		वापस MSR_F15H_PERF_CTL + (addr - MSR_K7_EVNTSEL0);
	शेष:
		अवरोध;
	पूर्ण

	वापस addr;
पूर्ण

अटल अंतरभूत bool is_amd_pmu_msr(अचिन्हित पूर्णांक msr)
अणु
	अगर ((msr >= MSR_F15H_PERF_CTL &&
	     msr < MSR_F15H_PERF_CTR + (amd_num_counters * 2)) ||
	    (msr >= MSR_K7_EVNTSEL0 &&
	     msr < MSR_K7_PERFCTR0 + amd_num_counters))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक is_पूर्णांकel_pmu_msr(u32 msr_index, पूर्णांक *type, पूर्णांक *index)
अणु
	u32 msr_index_pmc;

	चयन (msr_index) अणु
	हाल MSR_CORE_PERF_FIXED_CTR_CTRL:
	हाल MSR_IA32_DS_AREA:
	हाल MSR_IA32_PEBS_ENABLE:
		*type = MSR_TYPE_CTRL;
		वापस true;

	हाल MSR_CORE_PERF_GLOBAL_CTRL:
	हाल MSR_CORE_PERF_GLOBAL_STATUS:
	हाल MSR_CORE_PERF_GLOBAL_OVF_CTRL:
		*type = MSR_TYPE_GLOBAL;
		वापस true;

	शेष:

		अगर ((msr_index >= MSR_CORE_PERF_FIXED_CTR0) &&
		    (msr_index < MSR_CORE_PERF_FIXED_CTR0 +
				 पूर्णांकel_num_fixed_counters)) अणु
			*index = msr_index - MSR_CORE_PERF_FIXED_CTR0;
			*type = MSR_TYPE_COUNTER;
			वापस true;
		पूर्ण

		अगर ((msr_index >= MSR_P6_EVNTSEL0) &&
		    (msr_index < MSR_P6_EVNTSEL0 +  पूर्णांकel_num_arch_counters)) अणु
			*index = msr_index - MSR_P6_EVNTSEL0;
			*type = MSR_TYPE_ARCH_CTRL;
			वापस true;
		पूर्ण

		msr_index_pmc = msr_index & MSR_PMC_ALIAS_MASK;
		अगर ((msr_index_pmc >= MSR_IA32_PERFCTR0) &&
		    (msr_index_pmc < MSR_IA32_PERFCTR0 +
				     पूर्णांकel_num_arch_counters)) अणु
			*type = MSR_TYPE_ARCH_COUNTER;
			*index = msr_index_pmc - MSR_IA32_PERFCTR0;
			वापस true;
		पूर्ण
		वापस false;
	पूर्ण
पूर्ण

अटल bool xen_पूर्णांकel_pmu_emulate(अचिन्हित पूर्णांक msr, u64 *val, पूर्णांक type,
				  पूर्णांक index, bool is_पढ़ो)
अणु
	uपूर्णांक64_t *reg = शून्य;
	काष्ठा xen_pmu_पूर्णांकel_ctxt *ctxt;
	uपूर्णांक64_t *fix_counters;
	काष्ठा xen_pmu_cntr_pair *arch_cntr_pair;
	काष्ठा xen_pmu_data *xenpmu_data = get_xenpmu_data();
	uपूर्णांक8_t xenpmu_flags = get_xenpmu_flags();


	अगर (!xenpmu_data || !(xenpmu_flags & XENPMU_IRQ_PROCESSING))
		वापस false;

	ctxt = &xenpmu_data->pmu.c.पूर्णांकel;

	चयन (msr) अणु
	हाल MSR_CORE_PERF_GLOBAL_OVF_CTRL:
		reg = &ctxt->global_ovf_ctrl;
		अवरोध;
	हाल MSR_CORE_PERF_GLOBAL_STATUS:
		reg = &ctxt->global_status;
		अवरोध;
	हाल MSR_CORE_PERF_GLOBAL_CTRL:
		reg = &ctxt->global_ctrl;
		अवरोध;
	हाल MSR_CORE_PERF_FIXED_CTR_CTRL:
		reg = &ctxt->fixed_ctrl;
		अवरोध;
	शेष:
		चयन (type) अणु
		हाल MSR_TYPE_COUNTER:
			fix_counters = field_offset(ctxt, fixed_counters);
			reg = &fix_counters[index];
			अवरोध;
		हाल MSR_TYPE_ARCH_COUNTER:
			arch_cntr_pair = field_offset(ctxt, arch_counters);
			reg = &arch_cntr_pair[index].counter;
			अवरोध;
		हाल MSR_TYPE_ARCH_CTRL:
			arch_cntr_pair = field_offset(ctxt, arch_counters);
			reg = &arch_cntr_pair[index].control;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	अगर (reg) अणु
		अगर (is_पढ़ो)
			*val = *reg;
		अन्यथा अणु
			*reg = *val;

			अगर (msr == MSR_CORE_PERF_GLOBAL_OVF_CTRL)
				ctxt->global_status &= (~(*val));
		पूर्ण
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool xen_amd_pmu_emulate(अचिन्हित पूर्णांक msr, u64 *val, bool is_पढ़ो)
अणु
	uपूर्णांक64_t *reg = शून्य;
	पूर्णांक i, off = 0;
	काष्ठा xen_pmu_amd_ctxt *ctxt;
	uपूर्णांक64_t *counter_regs, *ctrl_regs;
	काष्ठा xen_pmu_data *xenpmu_data = get_xenpmu_data();
	uपूर्णांक8_t xenpmu_flags = get_xenpmu_flags();

	अगर (!xenpmu_data || !(xenpmu_flags & XENPMU_IRQ_PROCESSING))
		वापस false;

	अगर (k7_counters_mirrored &&
	    ((msr >= MSR_K7_EVNTSEL0) && (msr <= MSR_K7_PERFCTR3)))
		msr = get_fam15h_addr(msr);

	ctxt = &xenpmu_data->pmu.c.amd;
	क्रम (i = 0; i < amd_num_counters; i++) अणु
		अगर (msr == amd_ctrls_base + off) अणु
			ctrl_regs = field_offset(ctxt, ctrls);
			reg = &ctrl_regs[i];
			अवरोध;
		पूर्ण अन्यथा अगर (msr == amd_counters_base + off) अणु
			counter_regs = field_offset(ctxt, counters);
			reg = &counter_regs[i];
			अवरोध;
		पूर्ण
		off += amd_msr_step;
	पूर्ण

	अगर (reg) अणु
		अगर (is_पढ़ो)
			*val = *reg;
		अन्यथा
			*reg = *val;

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool pmu_msr_पढ़ो(अचिन्हित पूर्णांक msr, uपूर्णांक64_t *val, पूर्णांक *err)
अणु
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL) अणु
		अगर (is_amd_pmu_msr(msr)) अणु
			अगर (!xen_amd_pmu_emulate(msr, val, 1))
				*val = native_पढ़ो_msr_safe(msr, err);
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक type, index;

		अगर (is_पूर्णांकel_pmu_msr(msr, &type, &index)) अणु
			अगर (!xen_पूर्णांकel_pmu_emulate(msr, val, type, index, 1))
				*val = native_पढ़ो_msr_safe(msr, err);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

bool pmu_msr_ग_लिखो(अचिन्हित पूर्णांक msr, uपूर्णांक32_t low, uपूर्णांक32_t high, पूर्णांक *err)
अणु
	uपूर्णांक64_t val = ((uपूर्णांक64_t)high << 32) | low;

	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL) अणु
		अगर (is_amd_pmu_msr(msr)) अणु
			अगर (!xen_amd_pmu_emulate(msr, &val, 0))
				*err = native_ग_लिखो_msr_safe(msr, low, high);
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक type, index;

		अगर (is_पूर्णांकel_pmu_msr(msr, &type, &index)) अणु
			अगर (!xen_पूर्णांकel_pmu_emulate(msr, &val, type, index, 0))
				*err = native_ग_लिखो_msr_safe(msr, low, high);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ xen_amd_पढ़ो_pmc(पूर्णांक counter)
अणु
	काष्ठा xen_pmu_amd_ctxt *ctxt;
	uपूर्णांक64_t *counter_regs;
	काष्ठा xen_pmu_data *xenpmu_data = get_xenpmu_data();
	uपूर्णांक8_t xenpmu_flags = get_xenpmu_flags();

	अगर (!xenpmu_data || !(xenpmu_flags & XENPMU_IRQ_PROCESSING)) अणु
		uपूर्णांक32_t msr;
		पूर्णांक err;

		msr = amd_counters_base + (counter * amd_msr_step);
		वापस native_पढ़ो_msr_safe(msr, &err);
	पूर्ण

	ctxt = &xenpmu_data->pmu.c.amd;
	counter_regs = field_offset(ctxt, counters);
	वापस counter_regs[counter];
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ xen_पूर्णांकel_पढ़ो_pmc(पूर्णांक counter)
अणु
	काष्ठा xen_pmu_पूर्णांकel_ctxt *ctxt;
	uपूर्णांक64_t *fixed_counters;
	काष्ठा xen_pmu_cntr_pair *arch_cntr_pair;
	काष्ठा xen_pmu_data *xenpmu_data = get_xenpmu_data();
	uपूर्णांक8_t xenpmu_flags = get_xenpmu_flags();

	अगर (!xenpmu_data || !(xenpmu_flags & XENPMU_IRQ_PROCESSING)) अणु
		uपूर्णांक32_t msr;
		पूर्णांक err;

		अगर (counter & (1 << INTEL_PMC_TYPE_SHIFT))
			msr = MSR_CORE_PERF_FIXED_CTR0 + (counter & 0xffff);
		अन्यथा
			msr = MSR_IA32_PERFCTR0 + counter;

		वापस native_पढ़ो_msr_safe(msr, &err);
	पूर्ण

	ctxt = &xenpmu_data->pmu.c.पूर्णांकel;
	अगर (counter & (1 << INTEL_PMC_TYPE_SHIFT)) अणु
		fixed_counters = field_offset(ctxt, fixed_counters);
		वापस fixed_counters[counter & 0xffff];
	पूर्ण

	arch_cntr_pair = field_offset(ctxt, arch_counters);
	वापस arch_cntr_pair[counter].counter;
पूर्ण

अचिन्हित दीर्घ दीर्घ xen_पढ़ो_pmc(पूर्णांक counter)
अणु
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL)
		वापस xen_amd_पढ़ो_pmc(counter);
	अन्यथा
		वापस xen_पूर्णांकel_पढ़ो_pmc(counter);
पूर्ण

पूर्णांक pmu_apic_update(uपूर्णांक32_t val)
अणु
	पूर्णांक ret;
	काष्ठा xen_pmu_data *xenpmu_data = get_xenpmu_data();

	अगर (!xenpmu_data) अणु
		pr_warn_once("%s: pmudata not initialized\n", __func__);
		वापस -EINVAL;
	पूर्ण

	xenpmu_data->pmu.l.lapic_lvtpc = val;

	अगर (get_xenpmu_flags() & XENPMU_IRQ_PROCESSING)
		वापस 0;

	ret = HYPERVISOR_xenpmu_op(XENPMU_lvtpc_set, शून्य);

	वापस ret;
पूर्ण

/* perf callbacks */
अटल पूर्णांक xen_is_in_guest(व्योम)
अणु
	स्थिर काष्ठा xen_pmu_data *xenpmu_data = get_xenpmu_data();

	अगर (!xenpmu_data) अणु
		pr_warn_once("%s: pmudata not initialized\n", __func__);
		वापस 0;
	पूर्ण

	अगर (!xen_initial_करोमुख्य() || (xenpmu_data->करोमुख्य_id >= DOMID_SELF))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक xen_is_user_mode(व्योम)
अणु
	स्थिर काष्ठा xen_pmu_data *xenpmu_data = get_xenpmu_data();

	अगर (!xenpmu_data) अणु
		pr_warn_once("%s: pmudata not initialized\n", __func__);
		वापस 0;
	पूर्ण

	अगर (xenpmu_data->pmu.pmu_flags & PMU_SAMPLE_PV)
		वापस (xenpmu_data->pmu.pmu_flags & PMU_SAMPLE_USER);
	अन्यथा
		वापस !!(xenpmu_data->pmu.r.regs.cpl & 3);
पूर्ण

अटल अचिन्हित दीर्घ xen_get_guest_ip(व्योम)
अणु
	स्थिर काष्ठा xen_pmu_data *xenpmu_data = get_xenpmu_data();

	अगर (!xenpmu_data) अणु
		pr_warn_once("%s: pmudata not initialized\n", __func__);
		वापस 0;
	पूर्ण

	वापस xenpmu_data->pmu.r.regs.ip;
पूर्ण

अटल काष्ठा perf_guest_info_callbacks xen_guest_cbs = अणु
	.is_in_guest            = xen_is_in_guest,
	.is_user_mode           = xen_is_user_mode,
	.get_guest_ip           = xen_get_guest_ip,
पूर्ण;

/* Convert रेजिस्टरs from Xen's format to Linux' */
अटल व्योम xen_convert_regs(स्थिर काष्ठा xen_pmu_regs *xen_regs,
			     काष्ठा pt_regs *regs, uपूर्णांक64_t pmu_flags)
अणु
	regs->ip = xen_regs->ip;
	regs->cs = xen_regs->cs;
	regs->sp = xen_regs->sp;

	अगर (pmu_flags & PMU_SAMPLE_PV) अणु
		अगर (pmu_flags & PMU_SAMPLE_USER)
			regs->cs |= 3;
		अन्यथा
			regs->cs &= ~3;
	पूर्ण अन्यथा अणु
		अगर (xen_regs->cpl)
			regs->cs |= 3;
		अन्यथा
			regs->cs &= ~3;
	पूर्ण
पूर्ण

irqवापस_t xen_pmu_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक err, ret = IRQ_NONE;
	काष्ठा pt_regs regs = अणु0पूर्ण;
	स्थिर काष्ठा xen_pmu_data *xenpmu_data = get_xenpmu_data();
	uपूर्णांक8_t xenpmu_flags = get_xenpmu_flags();

	अगर (!xenpmu_data) अणु
		pr_warn_once("%s: pmudata not initialized\n", __func__);
		वापस ret;
	पूर्ण

	this_cpu_ptr(&xenpmu_shared)->flags =
		xenpmu_flags | XENPMU_IRQ_PROCESSING;
	xen_convert_regs(&xenpmu_data->pmu.r.regs, &regs,
			 xenpmu_data->pmu.pmu_flags);
	अगर (x86_pmu.handle_irq(&regs))
		ret = IRQ_HANDLED;

	/* Write out cached context to HW */
	err = HYPERVISOR_xenpmu_op(XENPMU_flush, शून्य);
	this_cpu_ptr(&xenpmu_shared)->flags = xenpmu_flags;
	अगर (err) अणु
		pr_warn_once("%s: failed hypercall, err: %d\n", __func__, err);
		वापस IRQ_NONE;
	पूर्ण

	वापस ret;
पूर्ण

bool is_xen_pmu(पूर्णांक cpu)
अणु
	वापस (get_xenpmu_data() != शून्य);
पूर्ण

व्योम xen_pmu_init(पूर्णांक cpu)
अणु
	पूर्णांक err;
	काष्ठा xen_pmu_params xp;
	अचिन्हित दीर्घ pfn;
	काष्ठा xen_pmu_data *xenpmu_data;

	BUILD_BUG_ON(माप(काष्ठा xen_pmu_data) > PAGE_SIZE);

	अगर (xen_hvm_करोमुख्य())
		वापस;

	xenpmu_data = (काष्ठा xen_pmu_data *)get_zeroed_page(GFP_KERNEL);
	अगर (!xenpmu_data) अणु
		pr_err("VPMU init: No memory\n");
		वापस;
	पूर्ण
	pfn = virt_to_pfn(xenpmu_data);

	xp.val = pfn_to_mfn(pfn);
	xp.vcpu = cpu;
	xp.version.maj = XENPMU_VER_MAJ;
	xp.version.min = XENPMU_VER_MIN;
	err = HYPERVISOR_xenpmu_op(XENPMU_init, &xp);
	अगर (err)
		जाओ fail;

	per_cpu(xenpmu_shared, cpu).xenpmu_data = xenpmu_data;
	per_cpu(xenpmu_shared, cpu).flags = 0;

	अगर (cpu == 0) अणु
		perf_रेजिस्टर_guest_info_callbacks(&xen_guest_cbs);
		xen_pmu_arch_init();
	पूर्ण

	वापस;

fail:
	अगर (err == -EOPNOTSUPP || err == -ENOSYS)
		pr_info_once("VPMU disabled by hypervisor.\n");
	अन्यथा
		pr_info_once("Could not initialize VPMU for cpu %d, error %d\n",
			cpu, err);
	मुक्त_pages((अचिन्हित दीर्घ)xenpmu_data, 0);
पूर्ण

व्योम xen_pmu_finish(पूर्णांक cpu)
अणु
	काष्ठा xen_pmu_params xp;

	अगर (xen_hvm_करोमुख्य())
		वापस;

	xp.vcpu = cpu;
	xp.version.maj = XENPMU_VER_MAJ;
	xp.version.min = XENPMU_VER_MIN;

	(व्योम)HYPERVISOR_xenpmu_op(XENPMU_finish, &xp);

	मुक्त_pages((अचिन्हित दीर्घ)per_cpu(xenpmu_shared, cpu).xenpmu_data, 0);
	per_cpu(xenpmu_shared, cpu).xenpmu_data = शून्य;
पूर्ण
