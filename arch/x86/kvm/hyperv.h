<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
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

#अगर_अघोषित __ARCH_X86_KVM_HYPERV_H__
#घोषणा __ARCH_X86_KVM_HYPERV_H__

#समावेश <linux/kvm_host.h>

/*
 * The #घोषणाs related to the synthetic debugger are required by KDNet, but
 * they are not करोcumented in the Hyper-V TLFS because the synthetic debugger
 * functionality has been deprecated and is subject to removal in future
 * versions of Winकरोws.
 */
#घोषणा HYPERV_CPUID_SYNDBG_VENDOR_AND_MAX_FUNCTIONS	0x40000080
#घोषणा HYPERV_CPUID_SYNDBG_INTERFACE			0x40000081
#घोषणा HYPERV_CPUID_SYNDBG_PLATFORM_CAPABILITIES	0x40000082

/*
 * Hyper-V synthetic debugger platक्रमm capabilities
 * These are HYPERV_CPUID_SYNDBG_PLATFORM_CAPABILITIES.EAX bits.
 */
#घोषणा HV_X64_SYNDBG_CAP_ALLOW_KERNEL_DEBUGGING	BIT(1)

/* Hyper-V Synthetic debug options MSR */
#घोषणा HV_X64_MSR_SYNDBG_CONTROL		0x400000F1
#घोषणा HV_X64_MSR_SYNDBG_STATUS		0x400000F2
#घोषणा HV_X64_MSR_SYNDBG_SEND_BUFFER		0x400000F3
#घोषणा HV_X64_MSR_SYNDBG_RECV_BUFFER		0x400000F4
#घोषणा HV_X64_MSR_SYNDBG_PENDING_BUFFER	0x400000F5
#घोषणा HV_X64_MSR_SYNDBG_OPTIONS		0x400000FF

/* Hyper-V HV_X64_MSR_SYNDBG_OPTIONS bits */
#घोषणा HV_X64_SYNDBG_OPTION_USE_HCALLS		BIT(2)

अटल अंतरभूत काष्ठा kvm_hv *to_kvm_hv(काष्ठा kvm *kvm)
अणु
	वापस &kvm->arch.hyperv;
पूर्ण

अटल अंतरभूत काष्ठा kvm_vcpu_hv *to_hv_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.hyperv;
पूर्ण

अटल अंतरभूत काष्ठा kvm_vcpu_hv_synic *to_hv_synic(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	वापस &hv_vcpu->synic;
पूर्ण

अटल अंतरभूत काष्ठा kvm_vcpu *hv_synic_to_vcpu(काष्ठा kvm_vcpu_hv_synic *synic)
अणु
	काष्ठा kvm_vcpu_hv *hv_vcpu = container_of(synic, काष्ठा kvm_vcpu_hv, synic);

	वापस hv_vcpu->vcpu;
पूर्ण

अटल अंतरभूत काष्ठा kvm_hv_syndbg *to_hv_syndbg(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस &vcpu->kvm->arch.hyperv.hv_syndbg;
पूर्ण

अटल अंतरभूत u32 kvm_hv_get_vpindex(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	वापस hv_vcpu ? hv_vcpu->vp_index : kvm_vcpu_get_idx(vcpu);
पूर्ण

पूर्णांक kvm_hv_set_msr_common(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data, bool host);
पूर्णांक kvm_hv_get_msr_common(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 *pdata, bool host);

bool kvm_hv_hypercall_enabled(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_hv_hypercall(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_hv_irq_routing_update(काष्ठा kvm *kvm);
पूर्णांक kvm_hv_synic_set_irq(काष्ठा kvm *kvm, u32 vcpu_id, u32 sपूर्णांक);
व्योम kvm_hv_synic_send_eoi(काष्ठा kvm_vcpu *vcpu, पूर्णांक vector);
पूर्णांक kvm_hv_activate_synic(काष्ठा kvm_vcpu *vcpu, bool करोnt_zero_synic_pages);

व्योम kvm_hv_vcpu_uninit(काष्ठा kvm_vcpu *vcpu);

bool kvm_hv_assist_page_enabled(काष्ठा kvm_vcpu *vcpu);
bool kvm_hv_get_assist_page(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा hv_vp_assist_page *assist_page);

अटल अंतरभूत काष्ठा kvm_vcpu_hv_sसमयr *to_hv_sसमयr(काष्ठा kvm_vcpu *vcpu,
						      पूर्णांक समयr_index)
अणु
	वापस &to_hv_vcpu(vcpu)->sसमयr[समयr_index];
पूर्ण

अटल अंतरभूत काष्ठा kvm_vcpu *hv_sसमयr_to_vcpu(काष्ठा kvm_vcpu_hv_sसमयr *sसमयr)
अणु
	काष्ठा kvm_vcpu_hv *hv_vcpu;

	hv_vcpu = container_of(sसमयr - sसमयr->index, काष्ठा kvm_vcpu_hv,
			       sसमयr[0]);
	वापस hv_vcpu->vcpu;
पूर्ण

अटल अंतरभूत bool kvm_hv_has_sसमयr_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	अगर (!hv_vcpu)
		वापस false;

	वापस !biपंचांगap_empty(hv_vcpu->sसमयr_pending_biपंचांगap,
			     HV_SYNIC_STIMER_COUNT);
पूर्ण

व्योम kvm_hv_process_sसमयrs(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_hv_setup_tsc_page(काष्ठा kvm *kvm,
			   काष्ठा pvघड़ी_vcpu_समय_info *hv_घड़ी);
व्योम kvm_hv_invalidate_tsc_page(काष्ठा kvm *kvm);

व्योम kvm_hv_init_vm(काष्ठा kvm *kvm);
व्योम kvm_hv_destroy_vm(काष्ठा kvm *kvm);
व्योम kvm_hv_set_cpuid(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_vm_ioctl_hv_eventfd(काष्ठा kvm *kvm, काष्ठा kvm_hyperv_eventfd *args);
पूर्णांक kvm_get_hv_cpuid(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_cpuid2 *cpuid,
		     काष्ठा kvm_cpuid_entry2 __user *entries);

#पूर्ण_अगर
