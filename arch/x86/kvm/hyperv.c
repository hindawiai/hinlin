<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * KVM Microsoft Hyper-V emulation
 *
 * derived from arch/x86/kvm/x86.c
 *
 * Copyright (C) 2006 Qumranet, Inc.
 * Copyright (C) 2008 Qumranet, Inc.
 * Copyright IBM Corporation, 2008
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 * Copyright (C) 2015 Andrey Smetanin <यंत्रetanin@virtuozzo.com>
 *
 * Authors:
 *   Avi Kivity   <avi@qumranet.com>
 *   Yaniv Kamay  <yaniv@qumranet.com>
 *   Amit Shah    <amit.shah@qumranet.com>
 *   Ben-Ami Yassour <benami@il.ibm.com>
 *   Andrey Smetanin <यंत्रetanin@virtuozzo.com>
 */

#समावेश "x86.h"
#समावेश "lapic.h"
#समावेश "ioapic.h"
#समावेश "cpuid.h"
#समावेश "hyperv.h"
#समावेश "xen.h"

#समावेश <linux/cpu.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/eventfd.h>

#समावेश <यंत्र/apicdef.h>
#समावेश <trace/events/kvm.h>

#समावेश "trace.h"
#समावेश "irq.h"

/* "Hv#1" signature */
#घोषणा HYPERV_CPUID_SIGNATURE_EAX 0x31237648

#घोषणा KVM_HV_MAX_SPARSE_VCPU_SET_BITS DIV_ROUND_UP(KVM_MAX_VCPUS, 64)

अटल व्योम sसमयr_mark_pending(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr,
				bool vcpu_kick);

अटल अंतरभूत u64 synic_पढ़ो_sपूर्णांक(काष्ठा kvm_vcpu_hv_synic *synic, पूर्णांक sपूर्णांक)
अणु
	वापस atomic64_पढ़ो(&synic->sपूर्णांक[sपूर्णांक]);
पूर्ण

अटल अंतरभूत पूर्णांक synic_get_sपूर्णांक_vector(u64 sपूर्णांक_value)
अणु
	अगर (sपूर्णांक_value & HV_SYNIC_SINT_MASKED)
		वापस -1;
	वापस sपूर्णांक_value & HV_SYNIC_SINT_VECTOR_MASK;
पूर्ण

अटल bool synic_has_vector_connected(काष्ठा kvm_vcpu_hv_synic *synic,
				      पूर्णांक vector)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(synic->sपूर्णांक); i++) अणु
		अगर (synic_get_sपूर्णांक_vector(synic_पढ़ो_sपूर्णांक(synic, i)) == vector)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool synic_has_vector_स्वतः_eoi(काष्ठा kvm_vcpu_hv_synic *synic,
				     पूर्णांक vector)
अणु
	पूर्णांक i;
	u64 sपूर्णांक_value;

	क्रम (i = 0; i < ARRAY_SIZE(synic->sपूर्णांक); i++) अणु
		sपूर्णांक_value = synic_पढ़ो_sपूर्णांक(synic, i);
		अगर (synic_get_sपूर्णांक_vector(sपूर्णांक_value) == vector &&
		    sपूर्णांक_value & HV_SYNIC_SINT_AUTO_EOI)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम synic_update_vector(काष्ठा kvm_vcpu_hv_synic *synic,
				पूर्णांक vector)
अणु
	अगर (vector < HV_SYNIC_FIRST_VALID_VECTOR)
		वापस;

	अगर (synic_has_vector_connected(synic, vector))
		__set_bit(vector, synic->vec_biपंचांगap);
	अन्यथा
		__clear_bit(vector, synic->vec_biपंचांगap);

	अगर (synic_has_vector_स्वतः_eoi(synic, vector))
		__set_bit(vector, synic->स्वतः_eoi_biपंचांगap);
	अन्यथा
		__clear_bit(vector, synic->स्वतः_eoi_biपंचांगap);
पूर्ण

अटल पूर्णांक synic_set_sपूर्णांक(काष्ठा kvm_vcpu_hv_synic *synic, पूर्णांक sपूर्णांक,
			  u64 data, bool host)
अणु
	पूर्णांक vector, old_vector;
	bool masked;

	vector = data & HV_SYNIC_SINT_VECTOR_MASK;
	masked = data & HV_SYNIC_SINT_MASKED;

	/*
	 * Valid vectors are 16-255, however, nested Hyper-V attempts to ग_लिखो
	 * शेष '0x10000' value on boot and this should not #GP. We need to
	 * allow zero-initing the रेजिस्टर from host as well.
	 */
	अगर (vector < HV_SYNIC_FIRST_VALID_VECTOR && !host && !masked)
		वापस 1;
	/*
	 * Guest may configure multiple SINTs to use the same vector, so
	 * we मुख्यtain a biपंचांगap of vectors handled by synic, and a
	 * biपंचांगap of vectors with स्वतः-eoi behavior.  The biपंचांगaps are
	 * updated here, and atomically queried on fast paths.
	 */
	old_vector = synic_पढ़ो_sपूर्णांक(synic, sपूर्णांक) & HV_SYNIC_SINT_VECTOR_MASK;

	atomic64_set(&synic->sपूर्णांक[sपूर्णांक], data);

	synic_update_vector(synic, old_vector);

	synic_update_vector(synic, vector);

	/* Load SynIC vectors पूर्णांकo EOI निकास biपंचांगap */
	kvm_make_request(KVM_REQ_SCAN_IOAPIC, hv_synic_to_vcpu(synic));
	वापस 0;
पूर्ण

अटल काष्ठा kvm_vcpu *get_vcpu_by_vpidx(काष्ठा kvm *kvm, u32 vpidx)
अणु
	काष्ठा kvm_vcpu *vcpu = शून्य;
	पूर्णांक i;

	अगर (vpidx >= KVM_MAX_VCPUS)
		वापस शून्य;

	vcpu = kvm_get_vcpu(kvm, vpidx);
	अगर (vcpu && kvm_hv_get_vpindex(vcpu) == vpidx)
		वापस vcpu;
	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		अगर (kvm_hv_get_vpindex(vcpu) == vpidx)
			वापस vcpu;
	वापस शून्य;
पूर्ण

अटल काष्ठा kvm_vcpu_hv_synic *synic_get(काष्ठा kvm *kvm, u32 vpidx)
अणु
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा kvm_vcpu_hv_synic *synic;

	vcpu = get_vcpu_by_vpidx(kvm, vpidx);
	अगर (!vcpu || !to_hv_vcpu(vcpu))
		वापस शून्य;
	synic = to_hv_synic(vcpu);
	वापस (synic->active) ? synic : शून्य;
पूर्ण

अटल व्योम kvm_hv_notअगरy_acked_sपूर्णांक(काष्ठा kvm_vcpu *vcpu, u32 sपूर्णांक)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_vcpu_hv_synic *synic = to_hv_synic(vcpu);
	काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	काष्ठा kvm_vcpu_hv_sसमयr *sसमयr;
	पूर्णांक gsi, idx;

	trace_kvm_hv_notअगरy_acked_sपूर्णांक(vcpu->vcpu_id, sपूर्णांक);

	/* Try to deliver pending Hyper-V SynIC समयrs messages */
	क्रम (idx = 0; idx < ARRAY_SIZE(hv_vcpu->sसमयr); idx++) अणु
		sसमयr = &hv_vcpu->sसमयr[idx];
		अगर (sसमयr->msg_pending && sसमयr->config.enable &&
		    !sसमयr->config.direct_mode &&
		    sसमयr->config.sपूर्णांकx == sपूर्णांक)
			sसमयr_mark_pending(sसमयr, false);
	पूर्ण

	idx = srcu_पढ़ो_lock(&kvm->irq_srcu);
	gsi = atomic_पढ़ो(&synic->sपूर्णांक_to_gsi[sपूर्णांक]);
	अगर (gsi != -1)
		kvm_notअगरy_acked_gsi(kvm, gsi);
	srcu_पढ़ो_unlock(&kvm->irq_srcu, idx);
पूर्ण

अटल व्योम synic_निकास(काष्ठा kvm_vcpu_hv_synic *synic, u32 msr)
अणु
	काष्ठा kvm_vcpu *vcpu = hv_synic_to_vcpu(synic);
	काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	hv_vcpu->निकास.type = KVM_EXIT_HYPERV_SYNIC;
	hv_vcpu->निकास.u.synic.msr = msr;
	hv_vcpu->निकास.u.synic.control = synic->control;
	hv_vcpu->निकास.u.synic.evt_page = synic->evt_page;
	hv_vcpu->निकास.u.synic.msg_page = synic->msg_page;

	kvm_make_request(KVM_REQ_HV_EXIT, vcpu);
पूर्ण

अटल पूर्णांक synic_set_msr(काष्ठा kvm_vcpu_hv_synic *synic,
			 u32 msr, u64 data, bool host)
अणु
	काष्ठा kvm_vcpu *vcpu = hv_synic_to_vcpu(synic);
	पूर्णांक ret;

	अगर (!synic->active && !host)
		वापस 1;

	trace_kvm_hv_synic_set_msr(vcpu->vcpu_id, msr, data, host);

	ret = 0;
	चयन (msr) अणु
	हाल HV_X64_MSR_SCONTROL:
		synic->control = data;
		अगर (!host)
			synic_निकास(synic, msr);
		अवरोध;
	हाल HV_X64_MSR_SVERSION:
		अगर (!host) अणु
			ret = 1;
			अवरोध;
		पूर्ण
		synic->version = data;
		अवरोध;
	हाल HV_X64_MSR_SIEFP:
		अगर ((data & HV_SYNIC_SIEFP_ENABLE) && !host &&
		    !synic->करोnt_zero_synic_pages)
			अगर (kvm_clear_guest(vcpu->kvm,
					    data & PAGE_MASK, PAGE_SIZE)) अणु
				ret = 1;
				अवरोध;
			पूर्ण
		synic->evt_page = data;
		अगर (!host)
			synic_निकास(synic, msr);
		अवरोध;
	हाल HV_X64_MSR_SIMP:
		अगर ((data & HV_SYNIC_SIMP_ENABLE) && !host &&
		    !synic->करोnt_zero_synic_pages)
			अगर (kvm_clear_guest(vcpu->kvm,
					    data & PAGE_MASK, PAGE_SIZE)) अणु
				ret = 1;
				अवरोध;
			पूर्ण
		synic->msg_page = data;
		अगर (!host)
			synic_निकास(synic, msr);
		अवरोध;
	हाल HV_X64_MSR_EOM: अणु
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(synic->sपूर्णांक); i++)
			kvm_hv_notअगरy_acked_sपूर्णांक(vcpu, i);
		अवरोध;
	पूर्ण
	हाल HV_X64_MSR_SINT0 ... HV_X64_MSR_SINT15:
		ret = synic_set_sपूर्णांक(synic, msr - HV_X64_MSR_SINT0, data, host);
		अवरोध;
	शेष:
		ret = 1;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल bool kvm_hv_is_syndbg_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpuid_entry2 *entry;

	entry = kvm_find_cpuid_entry(vcpu,
				     HYPERV_CPUID_SYNDBG_PLATFORM_CAPABILITIES,
				     0);
	अगर (!entry)
		वापस false;

	वापस entry->eax & HV_X64_SYNDBG_CAP_ALLOW_KERNEL_DEBUGGING;
पूर्ण

अटल पूर्णांक kvm_hv_syndbg_complete_userspace(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(vcpu->kvm);

	अगर (vcpu->run->hyperv.u.syndbg.msr == HV_X64_MSR_SYNDBG_CONTROL)
		hv->hv_syndbg.control.status =
			vcpu->run->hyperv.u.syndbg.status;
	वापस 1;
पूर्ण

अटल व्योम syndbg_निकास(काष्ठा kvm_vcpu *vcpu, u32 msr)
अणु
	काष्ठा kvm_hv_syndbg *syndbg = to_hv_syndbg(vcpu);
	काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	hv_vcpu->निकास.type = KVM_EXIT_HYPERV_SYNDBG;
	hv_vcpu->निकास.u.syndbg.msr = msr;
	hv_vcpu->निकास.u.syndbg.control = syndbg->control.control;
	hv_vcpu->निकास.u.syndbg.send_page = syndbg->control.send_page;
	hv_vcpu->निकास.u.syndbg.recv_page = syndbg->control.recv_page;
	hv_vcpu->निकास.u.syndbg.pending_page = syndbg->control.pending_page;
	vcpu->arch.complete_userspace_io =
			kvm_hv_syndbg_complete_userspace;

	kvm_make_request(KVM_REQ_HV_EXIT, vcpu);
पूर्ण

अटल पूर्णांक syndbg_set_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data, bool host)
अणु
	काष्ठा kvm_hv_syndbg *syndbg = to_hv_syndbg(vcpu);

	अगर (!kvm_hv_is_syndbg_enabled(vcpu) && !host)
		वापस 1;

	trace_kvm_hv_syndbg_set_msr(vcpu->vcpu_id,
				    to_hv_vcpu(vcpu)->vp_index, msr, data);
	चयन (msr) अणु
	हाल HV_X64_MSR_SYNDBG_CONTROL:
		syndbg->control.control = data;
		अगर (!host)
			syndbg_निकास(vcpu, msr);
		अवरोध;
	हाल HV_X64_MSR_SYNDBG_STATUS:
		syndbg->control.status = data;
		अवरोध;
	हाल HV_X64_MSR_SYNDBG_SEND_BUFFER:
		syndbg->control.send_page = data;
		अवरोध;
	हाल HV_X64_MSR_SYNDBG_RECV_BUFFER:
		syndbg->control.recv_page = data;
		अवरोध;
	हाल HV_X64_MSR_SYNDBG_PENDING_BUFFER:
		syndbg->control.pending_page = data;
		अगर (!host)
			syndbg_निकास(vcpu, msr);
		अवरोध;
	हाल HV_X64_MSR_SYNDBG_OPTIONS:
		syndbg->options = data;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक syndbg_get_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 *pdata, bool host)
अणु
	काष्ठा kvm_hv_syndbg *syndbg = to_hv_syndbg(vcpu);

	अगर (!kvm_hv_is_syndbg_enabled(vcpu) && !host)
		वापस 1;

	चयन (msr) अणु
	हाल HV_X64_MSR_SYNDBG_CONTROL:
		*pdata = syndbg->control.control;
		अवरोध;
	हाल HV_X64_MSR_SYNDBG_STATUS:
		*pdata = syndbg->control.status;
		अवरोध;
	हाल HV_X64_MSR_SYNDBG_SEND_BUFFER:
		*pdata = syndbg->control.send_page;
		अवरोध;
	हाल HV_X64_MSR_SYNDBG_RECV_BUFFER:
		*pdata = syndbg->control.recv_page;
		अवरोध;
	हाल HV_X64_MSR_SYNDBG_PENDING_BUFFER:
		*pdata = syndbg->control.pending_page;
		अवरोध;
	हाल HV_X64_MSR_SYNDBG_OPTIONS:
		*pdata = syndbg->options;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	trace_kvm_hv_syndbg_get_msr(vcpu->vcpu_id, kvm_hv_get_vpindex(vcpu), msr, *pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक synic_get_msr(काष्ठा kvm_vcpu_hv_synic *synic, u32 msr, u64 *pdata,
			 bool host)
अणु
	पूर्णांक ret;

	अगर (!synic->active && !host)
		वापस 1;

	ret = 0;
	चयन (msr) अणु
	हाल HV_X64_MSR_SCONTROL:
		*pdata = synic->control;
		अवरोध;
	हाल HV_X64_MSR_SVERSION:
		*pdata = synic->version;
		अवरोध;
	हाल HV_X64_MSR_SIEFP:
		*pdata = synic->evt_page;
		अवरोध;
	हाल HV_X64_MSR_SIMP:
		*pdata = synic->msg_page;
		अवरोध;
	हाल HV_X64_MSR_EOM:
		*pdata = 0;
		अवरोध;
	हाल HV_X64_MSR_SINT0 ... HV_X64_MSR_SINT15:
		*pdata = atomic64_पढ़ो(&synic->sपूर्णांक[msr - HV_X64_MSR_SINT0]);
		अवरोध;
	शेष:
		ret = 1;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक synic_set_irq(काष्ठा kvm_vcpu_hv_synic *synic, u32 sपूर्णांक)
अणु
	काष्ठा kvm_vcpu *vcpu = hv_synic_to_vcpu(synic);
	काष्ठा kvm_lapic_irq irq;
	पूर्णांक ret, vector;

	अगर (sपूर्णांक >= ARRAY_SIZE(synic->sपूर्णांक))
		वापस -EINVAL;

	vector = synic_get_sपूर्णांक_vector(synic_पढ़ो_sपूर्णांक(synic, sपूर्णांक));
	अगर (vector < 0)
		वापस -ENOENT;

	स_रखो(&irq, 0, माप(irq));
	irq.लघुhand = APIC_DEST_SELF;
	irq.dest_mode = APIC_DEST_PHYSICAL;
	irq.delivery_mode = APIC_DM_FIXED;
	irq.vector = vector;
	irq.level = 1;

	ret = kvm_irq_delivery_to_apic(vcpu->kvm, vcpu->arch.apic, &irq, शून्य);
	trace_kvm_hv_synic_set_irq(vcpu->vcpu_id, sपूर्णांक, irq.vector, ret);
	वापस ret;
पूर्ण

पूर्णांक kvm_hv_synic_set_irq(काष्ठा kvm *kvm, u32 vpidx, u32 sपूर्णांक)
अणु
	काष्ठा kvm_vcpu_hv_synic *synic;

	synic = synic_get(kvm, vpidx);
	अगर (!synic)
		वापस -EINVAL;

	वापस synic_set_irq(synic, sपूर्णांक);
पूर्ण

व्योम kvm_hv_synic_send_eoi(काष्ठा kvm_vcpu *vcpu, पूर्णांक vector)
अणु
	काष्ठा kvm_vcpu_hv_synic *synic = to_hv_synic(vcpu);
	पूर्णांक i;

	trace_kvm_hv_synic_send_eoi(vcpu->vcpu_id, vector);

	क्रम (i = 0; i < ARRAY_SIZE(synic->sपूर्णांक); i++)
		अगर (synic_get_sपूर्णांक_vector(synic_पढ़ो_sपूर्णांक(synic, i)) == vector)
			kvm_hv_notअगरy_acked_sपूर्णांक(vcpu, i);
पूर्ण

अटल पूर्णांक kvm_hv_set_sपूर्णांक_gsi(काष्ठा kvm *kvm, u32 vpidx, u32 sपूर्णांक, पूर्णांक gsi)
अणु
	काष्ठा kvm_vcpu_hv_synic *synic;

	synic = synic_get(kvm, vpidx);
	अगर (!synic)
		वापस -EINVAL;

	अगर (sपूर्णांक >= ARRAY_SIZE(synic->sपूर्णांक_to_gsi))
		वापस -EINVAL;

	atomic_set(&synic->sपूर्णांक_to_gsi[sपूर्णांक], gsi);
	वापस 0;
पूर्ण

व्योम kvm_hv_irq_routing_update(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_irq_routing_table *irq_rt;
	काष्ठा kvm_kernel_irq_routing_entry *e;
	u32 gsi;

	irq_rt = srcu_dereference_check(kvm->irq_routing, &kvm->irq_srcu,
					lockdep_is_held(&kvm->irq_lock));

	क्रम (gsi = 0; gsi < irq_rt->nr_rt_entries; gsi++) अणु
		hlist_क्रम_each_entry(e, &irq_rt->map[gsi], link) अणु
			अगर (e->type == KVM_IRQ_ROUTING_HV_SINT)
				kvm_hv_set_sपूर्णांक_gsi(kvm, e->hv_sपूर्णांक.vcpu,
						    e->hv_sपूर्णांक.sपूर्णांक, gsi);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम synic_init(काष्ठा kvm_vcpu_hv_synic *synic)
अणु
	पूर्णांक i;

	स_रखो(synic, 0, माप(*synic));
	synic->version = HV_SYNIC_VERSION_1;
	क्रम (i = 0; i < ARRAY_SIZE(synic->sपूर्णांक); i++) अणु
		atomic64_set(&synic->sपूर्णांक[i], HV_SYNIC_SINT_MASKED);
		atomic_set(&synic->sपूर्णांक_to_gsi[i], -1);
	पूर्ण
पूर्ण

अटल u64 get_समय_ref_counter(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);
	काष्ठा kvm_vcpu *vcpu;
	u64 tsc;

	/*
	 * Fall back to get_kvmघड़ी_ns() when TSC page hasn't been set up,
	 * is broken, disabled or being updated.
	 */
	अगर (hv->hv_tsc_page_status != HV_TSC_PAGE_SET)
		वापस भाग_u64(get_kvmघड़ी_ns(kvm), 100);

	vcpu = kvm_get_vcpu(kvm, 0);
	tsc = kvm_पढ़ो_l1_tsc(vcpu, rdtsc());
	वापस mul_u64_u64_shr(tsc, hv->tsc_ref.tsc_scale, 64)
		+ hv->tsc_ref.tsc_offset;
पूर्ण

अटल व्योम sसमयr_mark_pending(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr,
				bool vcpu_kick)
अणु
	काष्ठा kvm_vcpu *vcpu = hv_sसमयr_to_vcpu(sसमयr);

	set_bit(sसमयr->index,
		to_hv_vcpu(vcpu)->sसमयr_pending_biपंचांगap);
	kvm_make_request(KVM_REQ_HV_STIMER, vcpu);
	अगर (vcpu_kick)
		kvm_vcpu_kick(vcpu);
पूर्ण

अटल व्योम sसमयr_cleanup(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr)
अणु
	काष्ठा kvm_vcpu *vcpu = hv_sसमयr_to_vcpu(sसमयr);

	trace_kvm_hv_sसमयr_cleanup(hv_sसमयr_to_vcpu(sसमयr)->vcpu_id,
				    sसमयr->index);

	hrसमयr_cancel(&sसमयr->समयr);
	clear_bit(sसमयr->index,
		  to_hv_vcpu(vcpu)->sसमयr_pending_biपंचांगap);
	sसमयr->msg_pending = false;
	sसमयr->exp_समय = 0;
पूर्ण

अटल क्रमागत hrसमयr_restart sसमयr_समयr_callback(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा kvm_vcpu_hv_sसमयr *sसमयr;

	sसमयr = container_of(समयr, काष्ठा kvm_vcpu_hv_sसमयr, समयr);
	trace_kvm_hv_sसमयr_callback(hv_sसमयr_to_vcpu(sसमयr)->vcpu_id,
				     sसमयr->index);
	sसमयr_mark_pending(sसमयr, true);

	वापस HRTIMER_NORESTART;
पूर्ण

/*
 * sसमयr_start() assumptions:
 * a) sसमयr->count is not equal to 0
 * b) sसमयr->config has HV_STIMER_ENABLE flag
 */
अटल पूर्णांक sसमयr_start(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr)
अणु
	u64 समय_now;
	kसमय_प्रकार kसमय_now;

	समय_now = get_समय_ref_counter(hv_sसमयr_to_vcpu(sसमयr)->kvm);
	kसमय_now = kसमय_get();

	अगर (sसमयr->config.periodic) अणु
		अगर (sसमयr->exp_समय) अणु
			अगर (समय_now >= sसमयr->exp_समय) अणु
				u64 reमुख्यder;

				भाग64_u64_rem(समय_now - sसमयr->exp_समय,
					      sसमयr->count, &reमुख्यder);
				sसमयr->exp_समय =
					समय_now + (sसमयr->count - reमुख्यder);
			पूर्ण
		पूर्ण अन्यथा
			sसमयr->exp_समय = समय_now + sसमयr->count;

		trace_kvm_hv_sसमयr_start_periodic(
					hv_sसमयr_to_vcpu(sसमयr)->vcpu_id,
					sसमयr->index,
					समय_now, sसमयr->exp_समय);

		hrसमयr_start(&sसमयr->समयr,
			      kसमय_add_ns(kसमय_now,
					   100 * (sसमयr->exp_समय - समय_now)),
			      HRTIMER_MODE_ABS);
		वापस 0;
	पूर्ण
	sसमयr->exp_समय = sसमयr->count;
	अगर (समय_now >= sसमयr->count) अणु
		/*
		 * Expire समयr according to Hypervisor Top-Level Functional
		 * specअगरication v4(15.3.1):
		 * "If a one shot is enabled and the specअगरied count is in
		 * the past, it will expire immediately."
		 */
		sसमयr_mark_pending(sसमयr, false);
		वापस 0;
	पूर्ण

	trace_kvm_hv_sसमयr_start_one_shot(hv_sसमयr_to_vcpu(sसमयr)->vcpu_id,
					   sसमयr->index,
					   समय_now, sसमयr->count);

	hrसमयr_start(&sसमयr->समयr,
		      kसमय_add_ns(kसमय_now, 100 * (sसमयr->count - समय_now)),
		      HRTIMER_MODE_ABS);
	वापस 0;
पूर्ण

अटल पूर्णांक sसमयr_set_config(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr, u64 config,
			     bool host)
अणु
	जोड़ hv_sसमयr_config new_config = अणु.as_uपूर्णांक64 = configपूर्ण,
		old_config = अणु.as_uपूर्णांक64 = sसमयr->config.as_uपूर्णांक64पूर्ण;
	काष्ठा kvm_vcpu *vcpu = hv_sसमयr_to_vcpu(sसमयr);
	काष्ठा kvm_vcpu_hv_synic *synic = to_hv_synic(vcpu);

	अगर (!synic->active && !host)
		वापस 1;

	trace_kvm_hv_sसमयr_set_config(hv_sसमयr_to_vcpu(sसमयr)->vcpu_id,
				       sसमयr->index, config, host);

	sसमयr_cleanup(sसमयr);
	अगर (old_config.enable &&
	    !new_config.direct_mode && new_config.sपूर्णांकx == 0)
		new_config.enable = 0;
	sसमयr->config.as_uपूर्णांक64 = new_config.as_uपूर्णांक64;

	अगर (sसमयr->config.enable)
		sसमयr_mark_pending(sसमयr, false);

	वापस 0;
पूर्ण

अटल पूर्णांक sसमयr_set_count(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr, u64 count,
			    bool host)
अणु
	काष्ठा kvm_vcpu *vcpu = hv_sसमयr_to_vcpu(sसमयr);
	काष्ठा kvm_vcpu_hv_synic *synic = to_hv_synic(vcpu);

	अगर (!synic->active && !host)
		वापस 1;

	trace_kvm_hv_sसमयr_set_count(hv_sसमयr_to_vcpu(sसमयr)->vcpu_id,
				      sसमयr->index, count, host);

	sसमयr_cleanup(sसमयr);
	sसमयr->count = count;
	अगर (sसमयr->count == 0)
		sसमयr->config.enable = 0;
	अन्यथा अगर (sसमयr->config.स्वतः_enable)
		sसमयr->config.enable = 1;

	अगर (sसमयr->config.enable)
		sसमयr_mark_pending(sसमयr, false);

	वापस 0;
पूर्ण

अटल पूर्णांक sसमयr_get_config(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr, u64 *pconfig)
अणु
	*pconfig = sसमयr->config.as_uपूर्णांक64;
	वापस 0;
पूर्ण

अटल पूर्णांक sसमयr_get_count(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr, u64 *pcount)
अणु
	*pcount = sसमयr->count;
	वापस 0;
पूर्ण

अटल पूर्णांक synic_deliver_msg(काष्ठा kvm_vcpu_hv_synic *synic, u32 sपूर्णांक,
			     काष्ठा hv_message *src_msg, bool no_retry)
अणु
	काष्ठा kvm_vcpu *vcpu = hv_synic_to_vcpu(synic);
	पूर्णांक msg_off = दुरत्व(काष्ठा hv_message_page, sपूर्णांक_message[sपूर्णांक]);
	gfn_t msg_page_gfn;
	काष्ठा hv_message_header hv_hdr;
	पूर्णांक r;

	अगर (!(synic->msg_page & HV_SYNIC_SIMP_ENABLE))
		वापस -ENOENT;

	msg_page_gfn = synic->msg_page >> PAGE_SHIFT;

	/*
	 * Strictly following the spec-mandated ordering would assume setting
	 * .msg_pending beक्रमe checking .message_type.  However, this function
	 * is only called in vcpu context so the entire update is atomic from
	 * guest POV and thus the exact order here करोesn't matter.
	 */
	r = kvm_vcpu_पढ़ो_guest_page(vcpu, msg_page_gfn, &hv_hdr.message_type,
				     msg_off + दुरत्व(काष्ठा hv_message,
							header.message_type),
				     माप(hv_hdr.message_type));
	अगर (r < 0)
		वापस r;

	अगर (hv_hdr.message_type != HVMSG_NONE) अणु
		अगर (no_retry)
			वापस 0;

		hv_hdr.message_flags.msg_pending = 1;
		r = kvm_vcpu_ग_लिखो_guest_page(vcpu, msg_page_gfn,
					      &hv_hdr.message_flags,
					      msg_off +
					      दुरत्व(काष्ठा hv_message,
						       header.message_flags),
					      माप(hv_hdr.message_flags));
		अगर (r < 0)
			वापस r;
		वापस -EAGAIN;
	पूर्ण

	r = kvm_vcpu_ग_लिखो_guest_page(vcpu, msg_page_gfn, src_msg, msg_off,
				      माप(src_msg->header) +
				      src_msg->header.payload_size);
	अगर (r < 0)
		वापस r;

	r = synic_set_irq(synic, sपूर्णांक);
	अगर (r < 0)
		वापस r;
	अगर (r == 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक sसमयr_send_msg(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr)
अणु
	काष्ठा kvm_vcpu *vcpu = hv_sसमयr_to_vcpu(sसमयr);
	काष्ठा hv_message *msg = &sसमयr->msg;
	काष्ठा hv_समयr_message_payload *payload =
			(काष्ठा hv_समयr_message_payload *)&msg->u.payload;

	/*
	 * To aव्योम piling up periodic ticks, करोn't retry message
	 * delivery क्रम them (within "lazy" lost ticks policy).
	 */
	bool no_retry = sसमयr->config.periodic;

	payload->expiration_समय = sसमयr->exp_समय;
	payload->delivery_समय = get_समय_ref_counter(vcpu->kvm);
	वापस synic_deliver_msg(to_hv_synic(vcpu),
				 sसमयr->config.sपूर्णांकx, msg,
				 no_retry);
पूर्ण

अटल पूर्णांक sसमयr_notअगरy_direct(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr)
अणु
	काष्ठा kvm_vcpu *vcpu = hv_sसमयr_to_vcpu(sसमयr);
	काष्ठा kvm_lapic_irq irq = अणु
		.delivery_mode = APIC_DM_FIXED,
		.vector = sसमयr->config.apic_vector
	पूर्ण;

	अगर (lapic_in_kernel(vcpu))
		वापस !kvm_apic_set_irq(vcpu, &irq, शून्य);
	वापस 0;
पूर्ण

अटल व्योम sसमयr_expiration(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr)
अणु
	पूर्णांक r, direct = sसमयr->config.direct_mode;

	sसमयr->msg_pending = true;
	अगर (!direct)
		r = sसमयr_send_msg(sसमयr);
	अन्यथा
		r = sसमयr_notअगरy_direct(sसमयr);
	trace_kvm_hv_sसमयr_expiration(hv_sसमयr_to_vcpu(sसमयr)->vcpu_id,
				       sसमयr->index, direct, r);
	अगर (!r) अणु
		sसमयr->msg_pending = false;
		अगर (!(sसमयr->config.periodic))
			sसमयr->config.enable = 0;
	पूर्ण
पूर्ण

व्योम kvm_hv_process_sसमयrs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	काष्ठा kvm_vcpu_hv_sसमयr *sसमयr;
	u64 समय_now, exp_समय;
	पूर्णांक i;

	अगर (!hv_vcpu)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(hv_vcpu->sसमयr); i++)
		अगर (test_and_clear_bit(i, hv_vcpu->sसमयr_pending_biपंचांगap)) अणु
			sसमयr = &hv_vcpu->sसमयr[i];
			अगर (sसमयr->config.enable) अणु
				exp_समय = sसमयr->exp_समय;

				अगर (exp_समय) अणु
					समय_now =
						get_समय_ref_counter(vcpu->kvm);
					अगर (समय_now >= exp_समय)
						sसमयr_expiration(sसमयr);
				पूर्ण

				अगर ((sसमयr->config.enable) &&
				    sसमयr->count) अणु
					अगर (!sसमयr->msg_pending)
						sसमयr_start(sसमयr);
				पूर्ण अन्यथा
					sसमयr_cleanup(sसमयr);
			पूर्ण
		पूर्ण
पूर्ण

व्योम kvm_hv_vcpu_uninit(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	पूर्णांक i;

	अगर (!hv_vcpu)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(hv_vcpu->sसमयr); i++)
		sसमयr_cleanup(&hv_vcpu->sसमयr[i]);

	kमुक्त(hv_vcpu);
	vcpu->arch.hyperv = शून्य;
पूर्ण

bool kvm_hv_assist_page_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	अगर (!hv_vcpu)
		वापस false;

	अगर (!(hv_vcpu->hv_vapic & HV_X64_MSR_VP_ASSIST_PAGE_ENABLE))
		वापस false;
	वापस vcpu->arch.pv_eoi.msr_val & KVM_MSR_ENABLED;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_hv_assist_page_enabled);

bool kvm_hv_get_assist_page(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा hv_vp_assist_page *assist_page)
अणु
	अगर (!kvm_hv_assist_page_enabled(vcpu))
		वापस false;
	वापस !kvm_पढ़ो_guest_cached(vcpu->kvm, &vcpu->arch.pv_eoi.data,
				      assist_page, माप(*assist_page));
पूर्ण
EXPORT_SYMBOL_GPL(kvm_hv_get_assist_page);

अटल व्योम sसमयr_prepare_msg(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr)
अणु
	काष्ठा hv_message *msg = &sसमयr->msg;
	काष्ठा hv_समयr_message_payload *payload =
			(काष्ठा hv_समयr_message_payload *)&msg->u.payload;

	स_रखो(&msg->header, 0, माप(msg->header));
	msg->header.message_type = HVMSG_TIMER_EXPIRED;
	msg->header.payload_size = माप(*payload);

	payload->समयr_index = sसमयr->index;
	payload->expiration_समय = 0;
	payload->delivery_समय = 0;
पूर्ण

अटल व्योम sसमयr_init(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr, पूर्णांक समयr_index)
अणु
	स_रखो(sसमयr, 0, माप(*sसमयr));
	sसमयr->index = समयr_index;
	hrसमयr_init(&sसमयr->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	sसमयr->समयr.function = sसमयr_समयr_callback;
	sसमयr_prepare_msg(sसमयr);
पूर्ण

अटल पूर्णांक kvm_hv_vcpu_init(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_vcpu_hv *hv_vcpu;
	पूर्णांक i;

	hv_vcpu = kzalloc(माप(काष्ठा kvm_vcpu_hv), GFP_KERNEL_ACCOUNT);
	अगर (!hv_vcpu)
		वापस -ENOMEM;

	vcpu->arch.hyperv = hv_vcpu;
	hv_vcpu->vcpu = vcpu;

	synic_init(&hv_vcpu->synic);

	biपंचांगap_zero(hv_vcpu->sसमयr_pending_biपंचांगap, HV_SYNIC_STIMER_COUNT);
	क्रम (i = 0; i < ARRAY_SIZE(hv_vcpu->sसमयr); i++)
		sसमयr_init(&hv_vcpu->sसमयr[i], i);

	hv_vcpu->vp_index = kvm_vcpu_get_idx(vcpu);

	वापस 0;
पूर्ण

पूर्णांक kvm_hv_activate_synic(काष्ठा kvm_vcpu *vcpu, bool करोnt_zero_synic_pages)
अणु
	काष्ठा kvm_vcpu_hv_synic *synic;
	पूर्णांक r;

	अगर (!to_hv_vcpu(vcpu)) अणु
		r = kvm_hv_vcpu_init(vcpu);
		अगर (r)
			वापस r;
	पूर्ण

	synic = to_hv_synic(vcpu);

	/*
	 * Hyper-V SynIC स्वतः EOI SINT's are
	 * not compatible with APICV, so request
	 * to deactivate APICV permanently.
	 */
	kvm_request_apicv_update(vcpu->kvm, false, APICV_INHIBIT_REASON_HYPERV);
	synic->active = true;
	synic->करोnt_zero_synic_pages = करोnt_zero_synic_pages;
	synic->control = HV_SYNIC_CONTROL_ENABLE;
	वापस 0;
पूर्ण

अटल bool kvm_hv_msr_partition_wide(u32 msr)
अणु
	bool r = false;

	चयन (msr) अणु
	हाल HV_X64_MSR_GUEST_OS_ID:
	हाल HV_X64_MSR_HYPERCALL:
	हाल HV_X64_MSR_REFERENCE_TSC:
	हाल HV_X64_MSR_TIME_REF_COUNT:
	हाल HV_X64_MSR_CRASH_CTL:
	हाल HV_X64_MSR_CRASH_P0 ... HV_X64_MSR_CRASH_P4:
	हाल HV_X64_MSR_RESET:
	हाल HV_X64_MSR_REENLIGHTENMENT_CONTROL:
	हाल HV_X64_MSR_TSC_EMULATION_CONTROL:
	हाल HV_X64_MSR_TSC_EMULATION_STATUS:
	हाल HV_X64_MSR_SYNDBG_OPTIONS:
	हाल HV_X64_MSR_SYNDBG_CONTROL ... HV_X64_MSR_SYNDBG_PENDING_BUFFER:
		r = true;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvm_hv_msr_get_crash_data(काष्ठा kvm *kvm, u32 index, u64 *pdata)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);
	माप_प्रकार size = ARRAY_SIZE(hv->hv_crash_param);

	अगर (WARN_ON_ONCE(index >= size))
		वापस -EINVAL;

	*pdata = hv->hv_crash_param[array_index_nospec(index, size)];
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_hv_msr_get_crash_ctl(काष्ठा kvm *kvm, u64 *pdata)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);

	*pdata = hv->hv_crash_ctl;
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_hv_msr_set_crash_ctl(काष्ठा kvm *kvm, u64 data)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);

	hv->hv_crash_ctl = data & HV_CRASH_CTL_CRASH_NOTIFY;

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_hv_msr_set_crash_data(काष्ठा kvm *kvm, u32 index, u64 data)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);
	माप_प्रकार size = ARRAY_SIZE(hv->hv_crash_param);

	अगर (WARN_ON_ONCE(index >= size))
		वापस -EINVAL;

	hv->hv_crash_param[array_index_nospec(index, size)] = data;
	वापस 0;
पूर्ण

/*
 * The kvmघड़ी and Hyper-V TSC page use similar क्रमmulas, and converting
 * between them is possible:
 *
 * kvmघड़ी क्रमmula:
 *    nsec = (ticks - tsc_बारtamp) * tsc_to_प्रणाली_mul * 2^(tsc_shअगरt-32)
 *           + प्रणाली_समय
 *
 * Hyper-V क्रमmula:
 *    nsec/100 = ticks * scale / 2^64 + offset
 *
 * When tsc_बारtamp = प्रणाली_समय = 0, offset is zero in the Hyper-V क्रमmula.
 * By भागiding the kvmघड़ी क्रमmula by 100 and equating what's left we get:
 *    ticks * scale / 2^64 = ticks * tsc_to_प्रणाली_mul * 2^(tsc_shअगरt-32) / 100
 *            scale / 2^64 =         tsc_to_प्रणाली_mul * 2^(tsc_shअगरt-32) / 100
 *            scale        =         tsc_to_प्रणाली_mul * 2^(32+tsc_shअगरt) / 100
 *
 * Now expand the kvmघड़ी क्रमmula and भागide by 100:
 *    nsec = ticks * tsc_to_प्रणाली_mul * 2^(tsc_shअगरt-32)
 *           - tsc_बारtamp * tsc_to_प्रणाली_mul * 2^(tsc_shअगरt-32)
 *           + प्रणाली_समय
 *    nsec/100 = ticks * tsc_to_प्रणाली_mul * 2^(tsc_shअगरt-32) / 100
 *               - tsc_बारtamp * tsc_to_प्रणाली_mul * 2^(tsc_shअगरt-32) / 100
 *               + प्रणाली_समय / 100
 *
 * Replace tsc_to_प्रणाली_mul * 2^(tsc_shअगरt-32) / 100 by scale / 2^64:
 *    nsec/100 = ticks * scale / 2^64
 *               - tsc_बारtamp * scale / 2^64
 *               + प्रणाली_समय / 100
 *
 * Equate with the Hyper-V क्रमmula so that ticks * scale / 2^64 cancels out:
 *    offset = प्रणाली_समय / 100 - tsc_बारtamp * scale / 2^64
 *
 * These two equivalencies are implemented in this function.
 */
अटल bool compute_tsc_page_parameters(काष्ठा pvघड़ी_vcpu_समय_info *hv_घड़ी,
					काष्ठा ms_hyperv_tsc_page *tsc_ref)
अणु
	u64 max_mul;

	अगर (!(hv_घड़ी->flags & PVCLOCK_TSC_STABLE_BIT))
		वापस false;

	/*
	 * check अगर scale would overflow, अगर so we use the समय ref counter
	 *    tsc_to_प्रणाली_mul * 2^(tsc_shअगरt+32) / 100 >= 2^64
	 *    tsc_to_प्रणाली_mul / 100 >= 2^(32-tsc_shअगरt)
	 *    tsc_to_प्रणाली_mul >= 100 * 2^(32-tsc_shअगरt)
	 */
	max_mul = 100ull << (32 - hv_घड़ी->tsc_shअगरt);
	अगर (hv_घड़ी->tsc_to_प्रणाली_mul >= max_mul)
		वापस false;

	/*
	 * Otherwise compute the scale and offset according to the क्रमmulas
	 * derived above.
	 */
	tsc_ref->tsc_scale =
		mul_u64_u32_भाग(1ULL << (32 + hv_घड़ी->tsc_shअगरt),
				hv_घड़ी->tsc_to_प्रणाली_mul,
				100);

	tsc_ref->tsc_offset = hv_घड़ी->प्रणाली_समय;
	करो_भाग(tsc_ref->tsc_offset, 100);
	tsc_ref->tsc_offset -=
		mul_u64_u64_shr(hv_घड़ी->tsc_बारtamp, tsc_ref->tsc_scale, 64);
	वापस true;
पूर्ण

/*
 * Don't touch TSC page values अगर the guest has opted क्रम TSC emulation after
 * migration. KVM करोesn't fully support reenlightenment notअगरications and TSC
 * access emulation and Hyper-V is known to expect the values in TSC page to
 * stay स्थिरant beक्रमe TSC access emulation is disabled from guest side
 * (HV_X64_MSR_TSC_EMULATION_STATUS). KVM userspace is expected to preserve TSC
 * frequency and guest visible TSC value across migration (and prevent it when
 * TSC scaling is unsupported).
 */
अटल अंतरभूत bool tsc_page_update_unsafe(काष्ठा kvm_hv *hv)
अणु
	वापस (hv->hv_tsc_page_status != HV_TSC_PAGE_GUEST_CHANGED) &&
		hv->hv_tsc_emulation_control;
पूर्ण

व्योम kvm_hv_setup_tsc_page(काष्ठा kvm *kvm,
			   काष्ठा pvघड़ी_vcpu_समय_info *hv_घड़ी)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);
	u32 tsc_seq;
	u64 gfn;

	BUILD_BUG_ON(माप(tsc_seq) != माप(hv->tsc_ref.tsc_sequence));
	BUILD_BUG_ON(दुरत्व(काष्ठा ms_hyperv_tsc_page, tsc_sequence) != 0);

	अगर (hv->hv_tsc_page_status == HV_TSC_PAGE_BROKEN ||
	    hv->hv_tsc_page_status == HV_TSC_PAGE_UNSET)
		वापस;

	mutex_lock(&hv->hv_lock);
	अगर (!(hv->hv_tsc_page & HV_X64_MSR_TSC_REFERENCE_ENABLE))
		जाओ out_unlock;

	gfn = hv->hv_tsc_page >> HV_X64_MSR_TSC_REFERENCE_ADDRESS_SHIFT;
	/*
	 * Because the TSC parameters only vary when there is a
	 * change in the master घड़ी, करो not bother with caching.
	 */
	अगर (unlikely(kvm_पढ़ो_guest(kvm, gfn_to_gpa(gfn),
				    &tsc_seq, माप(tsc_seq))))
		जाओ out_err;

	अगर (tsc_seq && tsc_page_update_unsafe(hv)) अणु
		अगर (kvm_पढ़ो_guest(kvm, gfn_to_gpa(gfn), &hv->tsc_ref, माप(hv->tsc_ref)))
			जाओ out_err;

		hv->hv_tsc_page_status = HV_TSC_PAGE_SET;
		जाओ out_unlock;
	पूर्ण

	/*
	 * While we're computing and writing the parameters, क्रमce the
	 * guest to use the समय reference count MSR.
	 */
	hv->tsc_ref.tsc_sequence = 0;
	अगर (kvm_ग_लिखो_guest(kvm, gfn_to_gpa(gfn),
			    &hv->tsc_ref, माप(hv->tsc_ref.tsc_sequence)))
		जाओ out_err;

	अगर (!compute_tsc_page_parameters(hv_घड़ी, &hv->tsc_ref))
		जाओ out_err;

	/* Ensure sequence is zero beक्रमe writing the rest of the काष्ठा.  */
	smp_wmb();
	अगर (kvm_ग_लिखो_guest(kvm, gfn_to_gpa(gfn), &hv->tsc_ref, माप(hv->tsc_ref)))
		जाओ out_err;

	/*
	 * Now चयन to the TSC page mechanism by writing the sequence.
	 */
	tsc_seq++;
	अगर (tsc_seq == 0xFFFFFFFF || tsc_seq == 0)
		tsc_seq = 1;

	/* Write the काष्ठा entirely beक्रमe the non-zero sequence.  */
	smp_wmb();

	hv->tsc_ref.tsc_sequence = tsc_seq;
	अगर (kvm_ग_लिखो_guest(kvm, gfn_to_gpa(gfn),
			    &hv->tsc_ref, माप(hv->tsc_ref.tsc_sequence)))
		जाओ out_err;

	hv->hv_tsc_page_status = HV_TSC_PAGE_SET;
	जाओ out_unlock;

out_err:
	hv->hv_tsc_page_status = HV_TSC_PAGE_BROKEN;
out_unlock:
	mutex_unlock(&hv->hv_lock);
पूर्ण

व्योम kvm_hv_invalidate_tsc_page(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);
	u64 gfn;
	पूर्णांक idx;

	अगर (hv->hv_tsc_page_status == HV_TSC_PAGE_BROKEN ||
	    hv->hv_tsc_page_status == HV_TSC_PAGE_UNSET ||
	    tsc_page_update_unsafe(hv))
		वापस;

	mutex_lock(&hv->hv_lock);

	अगर (!(hv->hv_tsc_page & HV_X64_MSR_TSC_REFERENCE_ENABLE))
		जाओ out_unlock;

	/* Preserve HV_TSC_PAGE_GUEST_CHANGED/HV_TSC_PAGE_HOST_CHANGED states */
	अगर (hv->hv_tsc_page_status == HV_TSC_PAGE_SET)
		hv->hv_tsc_page_status = HV_TSC_PAGE_UPDATING;

	gfn = hv->hv_tsc_page >> HV_X64_MSR_TSC_REFERENCE_ADDRESS_SHIFT;

	hv->tsc_ref.tsc_sequence = 0;

	/*
	 * Take the srcu lock as memslots will be accessed to check the gfn
	 * cache generation against the memslots generation.
	 */
	idx = srcu_पढ़ो_lock(&kvm->srcu);
	अगर (kvm_ग_लिखो_guest(kvm, gfn_to_gpa(gfn),
			    &hv->tsc_ref, माप(hv->tsc_ref.tsc_sequence)))
		hv->hv_tsc_page_status = HV_TSC_PAGE_BROKEN;
	srcu_पढ़ो_unlock(&kvm->srcu, idx);

out_unlock:
	mutex_unlock(&hv->hv_lock);
पूर्ण

अटल पूर्णांक kvm_hv_set_msr_pw(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data,
			     bool host)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);

	चयन (msr) अणु
	हाल HV_X64_MSR_GUEST_OS_ID:
		hv->hv_guest_os_id = data;
		/* setting guest os id to zero disables hypercall page */
		अगर (!hv->hv_guest_os_id)
			hv->hv_hypercall &= ~HV_X64_MSR_HYPERCALL_ENABLE;
		अवरोध;
	हाल HV_X64_MSR_HYPERCALL: अणु
		u8 inकाष्ठाions[9];
		पूर्णांक i = 0;
		u64 addr;

		/* अगर guest os id is not set hypercall should reमुख्य disabled */
		अगर (!hv->hv_guest_os_id)
			अवरोध;
		अगर (!(data & HV_X64_MSR_HYPERCALL_ENABLE)) अणु
			hv->hv_hypercall = data;
			अवरोध;
		पूर्ण

		/*
		 * If Xen and Hyper-V hypercalls are both enabled, disambiguate
		 * the same way Xen itself करोes, by setting the bit 31 of EAX
		 * which is RsvdZ in the 32-bit Hyper-V hypercall ABI and just
		 * going to be clobbered on 64-bit.
		 */
		अगर (kvm_xen_hypercall_enabled(kvm)) अणु
			/* orl $0x80000000, %eax */
			inकाष्ठाions[i++] = 0x0d;
			inकाष्ठाions[i++] = 0x00;
			inकाष्ठाions[i++] = 0x00;
			inकाष्ठाions[i++] = 0x00;
			inकाष्ठाions[i++] = 0x80;
		पूर्ण

		/* vmcall/vmmcall */
		अटल_call(kvm_x86_patch_hypercall)(vcpu, inकाष्ठाions + i);
		i += 3;

		/* ret */
		((अचिन्हित अक्षर *)inकाष्ठाions)[i++] = 0xc3;

		addr = data & HV_X64_MSR_HYPERCALL_PAGE_ADDRESS_MASK;
		अगर (kvm_vcpu_ग_लिखो_guest(vcpu, addr, inकाष्ठाions, i))
			वापस 1;
		hv->hv_hypercall = data;
		अवरोध;
	पूर्ण
	हाल HV_X64_MSR_REFERENCE_TSC:
		hv->hv_tsc_page = data;
		अगर (hv->hv_tsc_page & HV_X64_MSR_TSC_REFERENCE_ENABLE) अणु
			अगर (!host)
				hv->hv_tsc_page_status = HV_TSC_PAGE_GUEST_CHANGED;
			अन्यथा
				hv->hv_tsc_page_status = HV_TSC_PAGE_HOST_CHANGED;
			kvm_make_request(KVM_REQ_MASTERCLOCK_UPDATE, vcpu);
		पूर्ण अन्यथा अणु
			hv->hv_tsc_page_status = HV_TSC_PAGE_UNSET;
		पूर्ण
		अवरोध;
	हाल HV_X64_MSR_CRASH_P0 ... HV_X64_MSR_CRASH_P4:
		वापस kvm_hv_msr_set_crash_data(kvm,
						 msr - HV_X64_MSR_CRASH_P0,
						 data);
	हाल HV_X64_MSR_CRASH_CTL:
		अगर (host)
			वापस kvm_hv_msr_set_crash_ctl(kvm, data);

		अगर (data & HV_CRASH_CTL_CRASH_NOTIFY) अणु
			vcpu_debug(vcpu, "hv crash (0x%llx 0x%llx 0x%llx 0x%llx 0x%llx)\n",
				   hv->hv_crash_param[0],
				   hv->hv_crash_param[1],
				   hv->hv_crash_param[2],
				   hv->hv_crash_param[3],
				   hv->hv_crash_param[4]);

			/* Send notअगरication about crash to user space */
			kvm_make_request(KVM_REQ_HV_CRASH, vcpu);
		पूर्ण
		अवरोध;
	हाल HV_X64_MSR_RESET:
		अगर (data == 1) अणु
			vcpu_debug(vcpu, "hyper-v reset requested\n");
			kvm_make_request(KVM_REQ_HV_RESET, vcpu);
		पूर्ण
		अवरोध;
	हाल HV_X64_MSR_REENLIGHTENMENT_CONTROL:
		hv->hv_reenlightenment_control = data;
		अवरोध;
	हाल HV_X64_MSR_TSC_EMULATION_CONTROL:
		hv->hv_tsc_emulation_control = data;
		अवरोध;
	हाल HV_X64_MSR_TSC_EMULATION_STATUS:
		अगर (data && !host)
			वापस 1;

		hv->hv_tsc_emulation_status = data;
		अवरोध;
	हाल HV_X64_MSR_TIME_REF_COUNT:
		/* पढ़ो-only, but still ignore it अगर host-initiated */
		अगर (!host)
			वापस 1;
		अवरोध;
	हाल HV_X64_MSR_SYNDBG_OPTIONS:
	हाल HV_X64_MSR_SYNDBG_CONTROL ... HV_X64_MSR_SYNDBG_PENDING_BUFFER:
		वापस syndbg_set_msr(vcpu, msr, data, host);
	शेष:
		vcpu_unimpl(vcpu, "Hyper-V unhandled wrmsr: 0x%x data 0x%llx\n",
			    msr, data);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Calculate cpu समय spent by current task in 100ns units */
अटल u64 current_task_runसमय_100ns(व्योम)
अणु
	u64 uसमय, sसमय;

	task_cpuसमय_adjusted(current, &uसमय, &sसमय);

	वापस भाग_u64(uसमय + sसमय, 100);
पूर्ण

अटल पूर्णांक kvm_hv_set_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data, bool host)
अणु
	काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	चयन (msr) अणु
	हाल HV_X64_MSR_VP_INDEX: अणु
		काष्ठा kvm_hv *hv = to_kvm_hv(vcpu->kvm);
		पूर्णांक vcpu_idx = kvm_vcpu_get_idx(vcpu);
		u32 new_vp_index = (u32)data;

		अगर (!host || new_vp_index >= KVM_MAX_VCPUS)
			वापस 1;

		अगर (new_vp_index == hv_vcpu->vp_index)
			वापस 0;

		/*
		 * The VP index is initialized to vcpu_index by
		 * kvm_hv_vcpu_postcreate so they initially match.  Now the
		 * VP index is changing, adjust num_mismatched_vp_indexes अगर
		 * it now matches or no दीर्घer matches vcpu_idx.
		 */
		अगर (hv_vcpu->vp_index == vcpu_idx)
			atomic_inc(&hv->num_mismatched_vp_indexes);
		अन्यथा अगर (new_vp_index == vcpu_idx)
			atomic_dec(&hv->num_mismatched_vp_indexes);

		hv_vcpu->vp_index = new_vp_index;
		अवरोध;
	पूर्ण
	हाल HV_X64_MSR_VP_ASSIST_PAGE: अणु
		u64 gfn;
		अचिन्हित दीर्घ addr;

		अगर (!(data & HV_X64_MSR_VP_ASSIST_PAGE_ENABLE)) अणु
			hv_vcpu->hv_vapic = data;
			अगर (kvm_lapic_enable_pv_eoi(vcpu, 0, 0))
				वापस 1;
			अवरोध;
		पूर्ण
		gfn = data >> HV_X64_MSR_VP_ASSIST_PAGE_ADDRESS_SHIFT;
		addr = kvm_vcpu_gfn_to_hva(vcpu, gfn);
		अगर (kvm_is_error_hva(addr))
			वापस 1;

		/*
		 * Clear apic_assist portion of काष्ठा hv_vp_assist_page
		 * only, there can be valuable data in the rest which needs
		 * to be preserved e.g. on migration.
		 */
		अगर (__put_user(0, (u32 __user *)addr))
			वापस 1;
		hv_vcpu->hv_vapic = data;
		kvm_vcpu_mark_page_dirty(vcpu, gfn);
		अगर (kvm_lapic_enable_pv_eoi(vcpu,
					    gfn_to_gpa(gfn) | KVM_MSR_ENABLED,
					    माप(काष्ठा hv_vp_assist_page)))
			वापस 1;
		अवरोध;
	पूर्ण
	हाल HV_X64_MSR_EOI:
		वापस kvm_hv_vapic_msr_ग_लिखो(vcpu, APIC_EOI, data);
	हाल HV_X64_MSR_ICR:
		वापस kvm_hv_vapic_msr_ग_लिखो(vcpu, APIC_ICR, data);
	हाल HV_X64_MSR_TPR:
		वापस kvm_hv_vapic_msr_ग_लिखो(vcpu, APIC_TASKPRI, data);
	हाल HV_X64_MSR_VP_RUNTIME:
		अगर (!host)
			वापस 1;
		hv_vcpu->runसमय_offset = data - current_task_runसमय_100ns();
		अवरोध;
	हाल HV_X64_MSR_SCONTROL:
	हाल HV_X64_MSR_SVERSION:
	हाल HV_X64_MSR_SIEFP:
	हाल HV_X64_MSR_SIMP:
	हाल HV_X64_MSR_EOM:
	हाल HV_X64_MSR_SINT0 ... HV_X64_MSR_SINT15:
		वापस synic_set_msr(to_hv_synic(vcpu), msr, data, host);
	हाल HV_X64_MSR_STIMER0_CONFIG:
	हाल HV_X64_MSR_STIMER1_CONFIG:
	हाल HV_X64_MSR_STIMER2_CONFIG:
	हाल HV_X64_MSR_STIMER3_CONFIG: अणु
		पूर्णांक समयr_index = (msr - HV_X64_MSR_STIMER0_CONFIG)/2;

		वापस sसमयr_set_config(to_hv_sसमयr(vcpu, समयr_index),
					 data, host);
	पूर्ण
	हाल HV_X64_MSR_STIMER0_COUNT:
	हाल HV_X64_MSR_STIMER1_COUNT:
	हाल HV_X64_MSR_STIMER2_COUNT:
	हाल HV_X64_MSR_STIMER3_COUNT: अणु
		पूर्णांक समयr_index = (msr - HV_X64_MSR_STIMER0_COUNT)/2;

		वापस sसमयr_set_count(to_hv_sसमयr(vcpu, समयr_index),
					data, host);
	पूर्ण
	हाल HV_X64_MSR_TSC_FREQUENCY:
	हाल HV_X64_MSR_APIC_FREQUENCY:
		/* पढ़ो-only, but still ignore it अगर host-initiated */
		अगर (!host)
			वापस 1;
		अवरोध;
	शेष:
		vcpu_unimpl(vcpu, "Hyper-V unhandled wrmsr: 0x%x data 0x%llx\n",
			    msr, data);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_hv_get_msr_pw(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 *pdata,
			     bool host)
अणु
	u64 data = 0;
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);

	चयन (msr) अणु
	हाल HV_X64_MSR_GUEST_OS_ID:
		data = hv->hv_guest_os_id;
		अवरोध;
	हाल HV_X64_MSR_HYPERCALL:
		data = hv->hv_hypercall;
		अवरोध;
	हाल HV_X64_MSR_TIME_REF_COUNT:
		data = get_समय_ref_counter(kvm);
		अवरोध;
	हाल HV_X64_MSR_REFERENCE_TSC:
		data = hv->hv_tsc_page;
		अवरोध;
	हाल HV_X64_MSR_CRASH_P0 ... HV_X64_MSR_CRASH_P4:
		वापस kvm_hv_msr_get_crash_data(kvm,
						 msr - HV_X64_MSR_CRASH_P0,
						 pdata);
	हाल HV_X64_MSR_CRASH_CTL:
		वापस kvm_hv_msr_get_crash_ctl(kvm, pdata);
	हाल HV_X64_MSR_RESET:
		data = 0;
		अवरोध;
	हाल HV_X64_MSR_REENLIGHTENMENT_CONTROL:
		data = hv->hv_reenlightenment_control;
		अवरोध;
	हाल HV_X64_MSR_TSC_EMULATION_CONTROL:
		data = hv->hv_tsc_emulation_control;
		अवरोध;
	हाल HV_X64_MSR_TSC_EMULATION_STATUS:
		data = hv->hv_tsc_emulation_status;
		अवरोध;
	हाल HV_X64_MSR_SYNDBG_OPTIONS:
	हाल HV_X64_MSR_SYNDBG_CONTROL ... HV_X64_MSR_SYNDBG_PENDING_BUFFER:
		वापस syndbg_get_msr(vcpu, msr, pdata, host);
	शेष:
		vcpu_unimpl(vcpu, "Hyper-V unhandled rdmsr: 0x%x\n", msr);
		वापस 1;
	पूर्ण

	*pdata = data;
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_hv_get_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 *pdata,
			  bool host)
अणु
	u64 data = 0;
	काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	चयन (msr) अणु
	हाल HV_X64_MSR_VP_INDEX:
		data = hv_vcpu->vp_index;
		अवरोध;
	हाल HV_X64_MSR_EOI:
		वापस kvm_hv_vapic_msr_पढ़ो(vcpu, APIC_EOI, pdata);
	हाल HV_X64_MSR_ICR:
		वापस kvm_hv_vapic_msr_पढ़ो(vcpu, APIC_ICR, pdata);
	हाल HV_X64_MSR_TPR:
		वापस kvm_hv_vapic_msr_पढ़ो(vcpu, APIC_TASKPRI, pdata);
	हाल HV_X64_MSR_VP_ASSIST_PAGE:
		data = hv_vcpu->hv_vapic;
		अवरोध;
	हाल HV_X64_MSR_VP_RUNTIME:
		data = current_task_runसमय_100ns() + hv_vcpu->runसमय_offset;
		अवरोध;
	हाल HV_X64_MSR_SCONTROL:
	हाल HV_X64_MSR_SVERSION:
	हाल HV_X64_MSR_SIEFP:
	हाल HV_X64_MSR_SIMP:
	हाल HV_X64_MSR_EOM:
	हाल HV_X64_MSR_SINT0 ... HV_X64_MSR_SINT15:
		वापस synic_get_msr(to_hv_synic(vcpu), msr, pdata, host);
	हाल HV_X64_MSR_STIMER0_CONFIG:
	हाल HV_X64_MSR_STIMER1_CONFIG:
	हाल HV_X64_MSR_STIMER2_CONFIG:
	हाल HV_X64_MSR_STIMER3_CONFIG: अणु
		पूर्णांक समयr_index = (msr - HV_X64_MSR_STIMER0_CONFIG)/2;

		वापस sसमयr_get_config(to_hv_sसमयr(vcpu, समयr_index),
					 pdata);
	पूर्ण
	हाल HV_X64_MSR_STIMER0_COUNT:
	हाल HV_X64_MSR_STIMER1_COUNT:
	हाल HV_X64_MSR_STIMER2_COUNT:
	हाल HV_X64_MSR_STIMER3_COUNT: अणु
		पूर्णांक समयr_index = (msr - HV_X64_MSR_STIMER0_COUNT)/2;

		वापस sसमयr_get_count(to_hv_sसमयr(vcpu, समयr_index),
					pdata);
	पूर्ण
	हाल HV_X64_MSR_TSC_FREQUENCY:
		data = (u64)vcpu->arch.भव_tsc_khz * 1000;
		अवरोध;
	हाल HV_X64_MSR_APIC_FREQUENCY:
		data = APIC_BUS_FREQUENCY;
		अवरोध;
	शेष:
		vcpu_unimpl(vcpu, "Hyper-V unhandled rdmsr: 0x%x\n", msr);
		वापस 1;
	पूर्ण
	*pdata = data;
	वापस 0;
पूर्ण

पूर्णांक kvm_hv_set_msr_common(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data, bool host)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(vcpu->kvm);

	अगर (!host && !vcpu->arch.hyperv_enabled)
		वापस 1;

	अगर (!to_hv_vcpu(vcpu)) अणु
		अगर (kvm_hv_vcpu_init(vcpu))
			वापस 1;
	पूर्ण

	अगर (kvm_hv_msr_partition_wide(msr)) अणु
		पूर्णांक r;

		mutex_lock(&hv->hv_lock);
		r = kvm_hv_set_msr_pw(vcpu, msr, data, host);
		mutex_unlock(&hv->hv_lock);
		वापस r;
	पूर्ण अन्यथा
		वापस kvm_hv_set_msr(vcpu, msr, data, host);
पूर्ण

पूर्णांक kvm_hv_get_msr_common(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 *pdata, bool host)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(vcpu->kvm);

	अगर (!host && !vcpu->arch.hyperv_enabled)
		वापस 1;

	अगर (!to_hv_vcpu(vcpu)) अणु
		अगर (kvm_hv_vcpu_init(vcpu))
			वापस 1;
	पूर्ण

	अगर (kvm_hv_msr_partition_wide(msr)) अणु
		पूर्णांक r;

		mutex_lock(&hv->hv_lock);
		r = kvm_hv_get_msr_pw(vcpu, msr, pdata, host);
		mutex_unlock(&hv->hv_lock);
		वापस r;
	पूर्ण अन्यथा
		वापस kvm_hv_get_msr(vcpu, msr, pdata, host);
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ *sparse_set_to_vcpu_mask(
	काष्ठा kvm *kvm, u64 *sparse_banks, u64 valid_bank_mask,
	u64 *vp_biपंचांगap, अचिन्हित दीर्घ *vcpu_biपंचांगap)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i, bank, sbank = 0;

	स_रखो(vp_biपंचांगap, 0,
	       KVM_HV_MAX_SPARSE_VCPU_SET_BITS * माप(*vp_biपंचांगap));
	क्रम_each_set_bit(bank, (अचिन्हित दीर्घ *)&valid_bank_mask,
			 KVM_HV_MAX_SPARSE_VCPU_SET_BITS)
		vp_biपंचांगap[bank] = sparse_banks[sbank++];

	अगर (likely(!atomic_पढ़ो(&hv->num_mismatched_vp_indexes))) अणु
		/* क्रम all vcpus vp_index == vcpu_idx */
		वापस (अचिन्हित दीर्घ *)vp_biपंचांगap;
	पूर्ण

	biपंचांगap_zero(vcpu_biपंचांगap, KVM_MAX_VCPUS);
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (test_bit(kvm_hv_get_vpindex(vcpu), (अचिन्हित दीर्घ *)vp_biपंचांगap))
			__set_bit(i, vcpu_biपंचांगap);
	पूर्ण
	वापस vcpu_biपंचांगap;
पूर्ण

अटल u64 kvm_hv_flush_tlb(काष्ठा kvm_vcpu *vcpu, u64 ingpa, u16 rep_cnt, bool ex)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	काष्ठा hv_tlb_flush_ex flush_ex;
	काष्ठा hv_tlb_flush flush;
	u64 vp_biपंचांगap[KVM_HV_MAX_SPARSE_VCPU_SET_BITS];
	DECLARE_BITMAP(vcpu_biपंचांगap, KVM_MAX_VCPUS);
	अचिन्हित दीर्घ *vcpu_mask;
	u64 valid_bank_mask;
	u64 sparse_banks[64];
	पूर्णांक sparse_banks_len;
	bool all_cpus;

	अगर (!ex) अणु
		अगर (unlikely(kvm_पढ़ो_guest(kvm, ingpa, &flush, माप(flush))))
			वापस HV_STATUS_INVALID_HYPERCALL_INPUT;

		trace_kvm_hv_flush_tlb(flush.processor_mask,
				       flush.address_space, flush.flags);

		valid_bank_mask = BIT_ULL(0);
		sparse_banks[0] = flush.processor_mask;

		/*
		 * Work around possible WS2012 bug: it sends hypercalls
		 * with processor_mask = 0x0 and HV_FLUSH_ALL_PROCESSORS clear,
		 * जबतक also expecting us to flush something and crashing अगर
		 * we करोn't. Let's treat processor_mask == 0 same as
		 * HV_FLUSH_ALL_PROCESSORS.
		 */
		all_cpus = (flush.flags & HV_FLUSH_ALL_PROCESSORS) ||
			flush.processor_mask == 0;
	पूर्ण अन्यथा अणु
		अगर (unlikely(kvm_पढ़ो_guest(kvm, ingpa, &flush_ex,
					    माप(flush_ex))))
			वापस HV_STATUS_INVALID_HYPERCALL_INPUT;

		trace_kvm_hv_flush_tlb_ex(flush_ex.hv_vp_set.valid_bank_mask,
					  flush_ex.hv_vp_set.क्रमmat,
					  flush_ex.address_space,
					  flush_ex.flags);

		valid_bank_mask = flush_ex.hv_vp_set.valid_bank_mask;
		all_cpus = flush_ex.hv_vp_set.क्रमmat !=
			HV_GENERIC_SET_SPARSE_4K;

		sparse_banks_len =
			biपंचांगap_weight((अचिन्हित दीर्घ *)&valid_bank_mask, 64) *
			माप(sparse_banks[0]);

		अगर (!sparse_banks_len && !all_cpus)
			जाओ ret_success;

		अगर (!all_cpus &&
		    kvm_पढ़ो_guest(kvm,
				   ingpa + दुरत्व(काष्ठा hv_tlb_flush_ex,
						    hv_vp_set.bank_contents),
				   sparse_banks,
				   sparse_banks_len))
			वापस HV_STATUS_INVALID_HYPERCALL_INPUT;
	पूर्ण

	cpumask_clear(&hv_vcpu->tlb_flush);

	vcpu_mask = all_cpus ? शून्य :
		sparse_set_to_vcpu_mask(kvm, sparse_banks, valid_bank_mask,
					vp_biपंचांगap, vcpu_biपंचांगap);

	/*
	 * vcpu->arch.cr3 may not be up-to-date क्रम running vCPUs so we can't
	 * analyze it here, flush TLB regardless of the specअगरied address space.
	 */
	kvm_make_vcpus_request_mask(kvm, KVM_REQ_HV_TLB_FLUSH,
				    शून्य, vcpu_mask, &hv_vcpu->tlb_flush);

ret_success:
	/* We always करो full TLB flush, set rep_करोne = rep_cnt. */
	वापस (u64)HV_STATUS_SUCCESS |
		((u64)rep_cnt << HV_HYPERCALL_REP_COMP_OFFSET);
पूर्ण

अटल व्योम kvm_send_ipi_to_many(काष्ठा kvm *kvm, u32 vector,
				 अचिन्हित दीर्घ *vcpu_biपंचांगap)
अणु
	काष्ठा kvm_lapic_irq irq = अणु
		.delivery_mode = APIC_DM_FIXED,
		.vector = vector
	पूर्ण;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (vcpu_biपंचांगap && !test_bit(i, vcpu_biपंचांगap))
			जारी;

		/* We fail only when APIC is disabled */
		kvm_apic_set_irq(vcpu, &irq, शून्य);
	पूर्ण
पूर्ण

अटल u64 kvm_hv_send_ipi(काष्ठा kvm_vcpu *vcpu, u64 ingpa, u64 outgpa,
			   bool ex, bool fast)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा hv_send_ipi_ex send_ipi_ex;
	काष्ठा hv_send_ipi send_ipi;
	u64 vp_biपंचांगap[KVM_HV_MAX_SPARSE_VCPU_SET_BITS];
	DECLARE_BITMAP(vcpu_biपंचांगap, KVM_MAX_VCPUS);
	अचिन्हित दीर्घ *vcpu_mask;
	अचिन्हित दीर्घ valid_bank_mask;
	u64 sparse_banks[64];
	पूर्णांक sparse_banks_len;
	u32 vector;
	bool all_cpus;

	अगर (!ex) अणु
		अगर (!fast) अणु
			अगर (unlikely(kvm_पढ़ो_guest(kvm, ingpa, &send_ipi,
						    माप(send_ipi))))
				वापस HV_STATUS_INVALID_HYPERCALL_INPUT;
			sparse_banks[0] = send_ipi.cpu_mask;
			vector = send_ipi.vector;
		पूर्ण अन्यथा अणु
			/* 'reserved' part of hv_send_ipi should be 0 */
			अगर (unlikely(ingpa >> 32 != 0))
				वापस HV_STATUS_INVALID_HYPERCALL_INPUT;
			sparse_banks[0] = outgpa;
			vector = (u32)ingpa;
		पूर्ण
		all_cpus = false;
		valid_bank_mask = BIT_ULL(0);

		trace_kvm_hv_send_ipi(vector, sparse_banks[0]);
	पूर्ण अन्यथा अणु
		अगर (unlikely(kvm_पढ़ो_guest(kvm, ingpa, &send_ipi_ex,
					    माप(send_ipi_ex))))
			वापस HV_STATUS_INVALID_HYPERCALL_INPUT;

		trace_kvm_hv_send_ipi_ex(send_ipi_ex.vector,
					 send_ipi_ex.vp_set.क्रमmat,
					 send_ipi_ex.vp_set.valid_bank_mask);

		vector = send_ipi_ex.vector;
		valid_bank_mask = send_ipi_ex.vp_set.valid_bank_mask;
		sparse_banks_len = biपंचांगap_weight(&valid_bank_mask, 64) *
			माप(sparse_banks[0]);

		all_cpus = send_ipi_ex.vp_set.क्रमmat == HV_GENERIC_SET_ALL;

		अगर (!sparse_banks_len)
			जाओ ret_success;

		अगर (!all_cpus &&
		    kvm_पढ़ो_guest(kvm,
				   ingpa + दुरत्व(काष्ठा hv_send_ipi_ex,
						    vp_set.bank_contents),
				   sparse_banks,
				   sparse_banks_len))
			वापस HV_STATUS_INVALID_HYPERCALL_INPUT;
	पूर्ण

	अगर ((vector < HV_IPI_LOW_VECTOR) || (vector > HV_IPI_HIGH_VECTOR))
		वापस HV_STATUS_INVALID_HYPERCALL_INPUT;

	vcpu_mask = all_cpus ? शून्य :
		sparse_set_to_vcpu_mask(kvm, sparse_banks, valid_bank_mask,
					vp_biपंचांगap, vcpu_biपंचांगap);

	kvm_send_ipi_to_many(kvm, vector, vcpu_mask);

ret_success:
	वापस HV_STATUS_SUCCESS;
पूर्ण

व्योम kvm_hv_set_cpuid(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpuid_entry2 *entry;

	entry = kvm_find_cpuid_entry(vcpu, HYPERV_CPUID_INTERFACE, 0);
	अगर (entry && entry->eax == HYPERV_CPUID_SIGNATURE_EAX)
		vcpu->arch.hyperv_enabled = true;
	अन्यथा
		vcpu->arch.hyperv_enabled = false;
पूर्ण

bool kvm_hv_hypercall_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.hyperv_enabled && to_kvm_hv(vcpu->kvm)->hv_guest_os_id;
पूर्ण

अटल व्योम kvm_hv_hypercall_set_result(काष्ठा kvm_vcpu *vcpu, u64 result)
अणु
	bool दीर्घmode;

	दीर्घmode = is_64_bit_mode(vcpu);
	अगर (दीर्घmode)
		kvm_rax_ग_लिखो(vcpu, result);
	अन्यथा अणु
		kvm_rdx_ग_लिखो(vcpu, result >> 32);
		kvm_rax_ग_लिखो(vcpu, result & 0xffffffff);
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_hv_hypercall_complete(काष्ठा kvm_vcpu *vcpu, u64 result)
अणु
	kvm_hv_hypercall_set_result(vcpu, result);
	++vcpu->स्थिति.सypercalls;
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल पूर्णांक kvm_hv_hypercall_complete_userspace(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_hv_hypercall_complete(vcpu, vcpu->run->hyperv.u.hcall.result);
पूर्ण

अटल u16 kvm_hvcall_संकेत_event(काष्ठा kvm_vcpu *vcpu, bool fast, u64 param)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(vcpu->kvm);
	काष्ठा eventfd_ctx *eventfd;

	अगर (unlikely(!fast)) अणु
		पूर्णांक ret;
		gpa_t gpa = param;

		अगर ((gpa & (__alignof__(param) - 1)) ||
		    offset_in_page(gpa) + माप(param) > PAGE_SIZE)
			वापस HV_STATUS_INVALID_ALIGNMENT;

		ret = kvm_vcpu_पढ़ो_guest(vcpu, gpa, &param, माप(param));
		अगर (ret < 0)
			वापस HV_STATUS_INVALID_ALIGNMENT;
	पूर्ण

	/*
	 * Per spec, bits 32-47 contain the extra "flag number".  However, we
	 * have no use क्रम it, and in all known useहालs it is zero, so just
	 * report lookup failure अगर it isn't.
	 */
	अगर (param & 0xffff00000000ULL)
		वापस HV_STATUS_INVALID_PORT_ID;
	/* reमुख्यing bits are reserved-zero */
	अगर (param & ~KVM_HYPERV_CONN_ID_MASK)
		वापस HV_STATUS_INVALID_HYPERCALL_INPUT;

	/* the eventfd is रक्षित by vcpu->kvm->srcu, but conn_to_evt isn't */
	rcu_पढ़ो_lock();
	eventfd = idr_find(&hv->conn_to_evt, param);
	rcu_पढ़ो_unlock();
	अगर (!eventfd)
		वापस HV_STATUS_INVALID_PORT_ID;

	eventfd_संकेत(eventfd, 1);
	वापस HV_STATUS_SUCCESS;
पूर्ण

पूर्णांक kvm_hv_hypercall(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 param, ingpa, outgpa, ret = HV_STATUS_SUCCESS;
	uपूर्णांक16_t code, rep_idx, rep_cnt;
	bool fast, rep;

	/*
	 * hypercall generates UD from non zero cpl and real mode
	 * per HYPER-V spec
	 */
	अगर (अटल_call(kvm_x86_get_cpl)(vcpu) != 0 || !is_proपंचांगode(vcpu)) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 1;
	पूर्ण

#अगर_घोषित CONFIG_X86_64
	अगर (is_64_bit_mode(vcpu)) अणु
		param = kvm_rcx_पढ़ो(vcpu);
		ingpa = kvm_rdx_पढ़ो(vcpu);
		outgpa = kvm_r8_पढ़ो(vcpu);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		param = ((u64)kvm_rdx_पढ़ो(vcpu) << 32) |
			(kvm_rax_पढ़ो(vcpu) & 0xffffffff);
		ingpa = ((u64)kvm_rbx_पढ़ो(vcpu) << 32) |
			(kvm_rcx_पढ़ो(vcpu) & 0xffffffff);
		outgpa = ((u64)kvm_rdi_पढ़ो(vcpu) << 32) |
			(kvm_rsi_पढ़ो(vcpu) & 0xffffffff);
	पूर्ण

	code = param & 0xffff;
	fast = !!(param & HV_HYPERCALL_FAST_BIT);
	rep_cnt = (param >> HV_HYPERCALL_REP_COMP_OFFSET) & 0xfff;
	rep_idx = (param >> HV_HYPERCALL_REP_START_OFFSET) & 0xfff;
	rep = !!(rep_cnt || rep_idx);

	trace_kvm_hv_hypercall(code, fast, rep_cnt, rep_idx, ingpa, outgpa);

	चयन (code) अणु
	हाल HVCALL_NOTIFY_LONG_SPIN_WAIT:
		अगर (unlikely(rep)) अणु
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			अवरोध;
		पूर्ण
		kvm_vcpu_on_spin(vcpu, true);
		अवरोध;
	हाल HVCALL_SIGNAL_EVENT:
		अगर (unlikely(rep)) अणु
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			अवरोध;
		पूर्ण
		ret = kvm_hvcall_संकेत_event(vcpu, fast, ingpa);
		अगर (ret != HV_STATUS_INVALID_PORT_ID)
			अवरोध;
		fallthrough;	/* maybe userspace knows this conn_id */
	हाल HVCALL_POST_MESSAGE:
		/* करोn't bother userspace अगर it has no way to handle it */
		अगर (unlikely(rep || !to_hv_synic(vcpu)->active)) अणु
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			अवरोध;
		पूर्ण
		vcpu->run->निकास_reason = KVM_EXIT_HYPERV;
		vcpu->run->hyperv.type = KVM_EXIT_HYPERV_HCALL;
		vcpu->run->hyperv.u.hcall.input = param;
		vcpu->run->hyperv.u.hcall.params[0] = ingpa;
		vcpu->run->hyperv.u.hcall.params[1] = outgpa;
		vcpu->arch.complete_userspace_io =
				kvm_hv_hypercall_complete_userspace;
		वापस 0;
	हाल HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST:
		अगर (unlikely(fast || !rep_cnt || rep_idx)) अणु
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			अवरोध;
		पूर्ण
		ret = kvm_hv_flush_tlb(vcpu, ingpa, rep_cnt, false);
		अवरोध;
	हाल HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE:
		अगर (unlikely(fast || rep)) अणु
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			अवरोध;
		पूर्ण
		ret = kvm_hv_flush_tlb(vcpu, ingpa, rep_cnt, false);
		अवरोध;
	हाल HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST_EX:
		अगर (unlikely(fast || !rep_cnt || rep_idx)) अणु
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			अवरोध;
		पूर्ण
		ret = kvm_hv_flush_tlb(vcpu, ingpa, rep_cnt, true);
		अवरोध;
	हाल HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE_EX:
		अगर (unlikely(fast || rep)) अणु
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			अवरोध;
		पूर्ण
		ret = kvm_hv_flush_tlb(vcpu, ingpa, rep_cnt, true);
		अवरोध;
	हाल HVCALL_SEND_IPI:
		अगर (unlikely(rep)) अणु
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			अवरोध;
		पूर्ण
		ret = kvm_hv_send_ipi(vcpu, ingpa, outgpa, false, fast);
		अवरोध;
	हाल HVCALL_SEND_IPI_EX:
		अगर (unlikely(fast || rep)) अणु
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			अवरोध;
		पूर्ण
		ret = kvm_hv_send_ipi(vcpu, ingpa, outgpa, true, false);
		अवरोध;
	हाल HVCALL_POST_DEBUG_DATA:
	हाल HVCALL_RETRIEVE_DEBUG_DATA:
		अगर (unlikely(fast)) अणु
			ret = HV_STATUS_INVALID_PARAMETER;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल HVCALL_RESET_DEBUG_SESSION: अणु
		काष्ठा kvm_hv_syndbg *syndbg = to_hv_syndbg(vcpu);

		अगर (!kvm_hv_is_syndbg_enabled(vcpu)) अणु
			ret = HV_STATUS_INVALID_HYPERCALL_CODE;
			अवरोध;
		पूर्ण

		अगर (!(syndbg->options & HV_X64_SYNDBG_OPTION_USE_HCALLS)) अणु
			ret = HV_STATUS_OPERATION_DENIED;
			अवरोध;
		पूर्ण
		vcpu->run->निकास_reason = KVM_EXIT_HYPERV;
		vcpu->run->hyperv.type = KVM_EXIT_HYPERV_HCALL;
		vcpu->run->hyperv.u.hcall.input = param;
		vcpu->run->hyperv.u.hcall.params[0] = ingpa;
		vcpu->run->hyperv.u.hcall.params[1] = outgpa;
		vcpu->arch.complete_userspace_io =
				kvm_hv_hypercall_complete_userspace;
		वापस 0;
	पूर्ण
	शेष:
		ret = HV_STATUS_INVALID_HYPERCALL_CODE;
		अवरोध;
	पूर्ण

	वापस kvm_hv_hypercall_complete(vcpu, ret);
पूर्ण

व्योम kvm_hv_init_vm(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);

	mutex_init(&hv->hv_lock);
	idr_init(&hv->conn_to_evt);
पूर्ण

व्योम kvm_hv_destroy_vm(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);
	काष्ठा eventfd_ctx *eventfd;
	पूर्णांक i;

	idr_क्रम_each_entry(&hv->conn_to_evt, eventfd, i)
		eventfd_ctx_put(eventfd);
	idr_destroy(&hv->conn_to_evt);
पूर्ण

अटल पूर्णांक kvm_hv_eventfd_assign(काष्ठा kvm *kvm, u32 conn_id, पूर्णांक fd)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);
	काष्ठा eventfd_ctx *eventfd;
	पूर्णांक ret;

	eventfd = eventfd_ctx_fdget(fd);
	अगर (IS_ERR(eventfd))
		वापस PTR_ERR(eventfd);

	mutex_lock(&hv->hv_lock);
	ret = idr_alloc(&hv->conn_to_evt, eventfd, conn_id, conn_id + 1,
			GFP_KERNEL_ACCOUNT);
	mutex_unlock(&hv->hv_lock);

	अगर (ret >= 0)
		वापस 0;

	अगर (ret == -ENOSPC)
		ret = -EEXIST;
	eventfd_ctx_put(eventfd);
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_hv_eventfd_deassign(काष्ठा kvm *kvm, u32 conn_id)
अणु
	काष्ठा kvm_hv *hv = to_kvm_hv(kvm);
	काष्ठा eventfd_ctx *eventfd;

	mutex_lock(&hv->hv_lock);
	eventfd = idr_हटाओ(&hv->conn_to_evt, conn_id);
	mutex_unlock(&hv->hv_lock);

	अगर (!eventfd)
		वापस -ENOENT;

	synchronize_srcu(&kvm->srcu);
	eventfd_ctx_put(eventfd);
	वापस 0;
पूर्ण

पूर्णांक kvm_vm_ioctl_hv_eventfd(काष्ठा kvm *kvm, काष्ठा kvm_hyperv_eventfd *args)
अणु
	अगर ((args->flags & ~KVM_HYPERV_EVENTFD_DEASSIGN) ||
	    (args->conn_id & ~KVM_HYPERV_CONN_ID_MASK))
		वापस -EINVAL;

	अगर (args->flags == KVM_HYPERV_EVENTFD_DEASSIGN)
		वापस kvm_hv_eventfd_deassign(kvm, args->conn_id);
	वापस kvm_hv_eventfd_assign(kvm, args->conn_id, args->fd);
पूर्ण

पूर्णांक kvm_get_hv_cpuid(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_cpuid2 *cpuid,
		     काष्ठा kvm_cpuid_entry2 __user *entries)
अणु
	uपूर्णांक16_t evmcs_ver = 0;
	काष्ठा kvm_cpuid_entry2 cpuid_entries[] = अणु
		अणु .function = HYPERV_CPUID_VENDOR_AND_MAX_FUNCTIONS पूर्ण,
		अणु .function = HYPERV_CPUID_INTERFACE पूर्ण,
		अणु .function = HYPERV_CPUID_VERSION पूर्ण,
		अणु .function = HYPERV_CPUID_FEATURES पूर्ण,
		अणु .function = HYPERV_CPUID_ENLIGHTMENT_INFO पूर्ण,
		अणु .function = HYPERV_CPUID_IMPLEMENT_LIMITS पूर्ण,
		अणु .function = HYPERV_CPUID_SYNDBG_VENDOR_AND_MAX_FUNCTIONS पूर्ण,
		अणु .function = HYPERV_CPUID_SYNDBG_INTERFACE पूर्ण,
		अणु .function = HYPERV_CPUID_SYNDBG_PLATFORM_CAPABILITIES	पूर्ण,
		अणु .function = HYPERV_CPUID_NESTED_FEATURES पूर्ण,
	पूर्ण;
	पूर्णांक i, nent = ARRAY_SIZE(cpuid_entries);

	अगर (kvm_x86_ops.nested_ops->get_evmcs_version)
		evmcs_ver = kvm_x86_ops.nested_ops->get_evmcs_version(vcpu);

	/* Skip NESTED_FEATURES अगर eVMCS is not supported */
	अगर (!evmcs_ver)
		--nent;

	अगर (cpuid->nent < nent)
		वापस -E2BIG;

	अगर (cpuid->nent > nent)
		cpuid->nent = nent;

	क्रम (i = 0; i < nent; i++) अणु
		काष्ठा kvm_cpuid_entry2 *ent = &cpuid_entries[i];
		u32 signature[3];

		चयन (ent->function) अणु
		हाल HYPERV_CPUID_VENDOR_AND_MAX_FUNCTIONS:
			स_नकल(signature, "Linux KVM Hv", 12);

			ent->eax = HYPERV_CPUID_SYNDBG_PLATFORM_CAPABILITIES;
			ent->ebx = signature[0];
			ent->ecx = signature[1];
			ent->edx = signature[2];
			अवरोध;

		हाल HYPERV_CPUID_INTERFACE:
			ent->eax = HYPERV_CPUID_SIGNATURE_EAX;
			अवरोध;

		हाल HYPERV_CPUID_VERSION:
			/*
			 * We implement some Hyper-V 2016 functions so let's use
			 * this version.
			 */
			ent->eax = 0x00003839;
			ent->ebx = 0x000A0000;
			अवरोध;

		हाल HYPERV_CPUID_FEATURES:
			ent->eax |= HV_MSR_VP_RUNTIME_AVAILABLE;
			ent->eax |= HV_MSR_TIME_REF_COUNT_AVAILABLE;
			ent->eax |= HV_MSR_SYNIC_AVAILABLE;
			ent->eax |= HV_MSR_SYNTIMER_AVAILABLE;
			ent->eax |= HV_MSR_APIC_ACCESS_AVAILABLE;
			ent->eax |= HV_MSR_HYPERCALL_AVAILABLE;
			ent->eax |= HV_MSR_VP_INDEX_AVAILABLE;
			ent->eax |= HV_MSR_RESET_AVAILABLE;
			ent->eax |= HV_MSR_REFERENCE_TSC_AVAILABLE;
			ent->eax |= HV_ACCESS_FREQUENCY_MSRS;
			ent->eax |= HV_ACCESS_REENLIGHTENMENT;

			ent->ebx |= HV_POST_MESSAGES;
			ent->ebx |= HV_SIGNAL_EVENTS;

			ent->edx |= HV_FEATURE_FREQUENCY_MSRS_AVAILABLE;
			ent->edx |= HV_FEATURE_GUEST_CRASH_MSR_AVAILABLE;

			ent->ebx |= HV_DEBUGGING;
			ent->edx |= HV_X64_GUEST_DEBUGGING_AVAILABLE;
			ent->edx |= HV_FEATURE_DEBUG_MSRS_AVAILABLE;

			/*
			 * Direct Synthetic समयrs only make sense with in-kernel
			 * LAPIC
			 */
			अगर (!vcpu || lapic_in_kernel(vcpu))
				ent->edx |= HV_STIMER_सूचीECT_MODE_AVAILABLE;

			अवरोध;

		हाल HYPERV_CPUID_ENLIGHTMENT_INFO:
			ent->eax |= HV_X64_REMOTE_TLB_FLUSH_RECOMMENDED;
			ent->eax |= HV_X64_APIC_ACCESS_RECOMMENDED;
			ent->eax |= HV_X64_RELAXED_TIMING_RECOMMENDED;
			ent->eax |= HV_X64_CLUSTER_IPI_RECOMMENDED;
			ent->eax |= HV_X64_EX_PROCESSOR_MASKS_RECOMMENDED;
			अगर (evmcs_ver)
				ent->eax |= HV_X64_ENLIGHTENED_VMCS_RECOMMENDED;
			अगर (!cpu_smt_possible())
				ent->eax |= HV_X64_NO_NONARCH_CORESHARING;
			/*
			 * Default number of spinlock retry attempts, matches
			 * HyperV 2016.
			 */
			ent->ebx = 0x00000FFF;

			अवरोध;

		हाल HYPERV_CPUID_IMPLEMENT_LIMITS:
			/* Maximum number of भव processors */
			ent->eax = KVM_MAX_VCPUS;
			/*
			 * Maximum number of logical processors, matches
			 * HyperV 2016.
			 */
			ent->ebx = 64;

			अवरोध;

		हाल HYPERV_CPUID_NESTED_FEATURES:
			ent->eax = evmcs_ver;

			अवरोध;

		हाल HYPERV_CPUID_SYNDBG_VENDOR_AND_MAX_FUNCTIONS:
			स_नकल(signature, "Linux KVM Hv", 12);

			ent->eax = 0;
			ent->ebx = signature[0];
			ent->ecx = signature[1];
			ent->edx = signature[2];
			अवरोध;

		हाल HYPERV_CPUID_SYNDBG_INTERFACE:
			स_नकल(signature, "VS#1\0\0\0\0\0\0\0\0", 12);
			ent->eax = signature[0];
			अवरोध;

		हाल HYPERV_CPUID_SYNDBG_PLATFORM_CAPABILITIES:
			ent->eax |= HV_X64_SYNDBG_CAP_ALLOW_KERNEL_DEBUGGING;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (copy_to_user(entries, cpuid_entries,
			 nent * माप(काष्ठा kvm_cpuid_entry2)))
		वापस -EFAULT;

	वापस 0;
पूर्ण
