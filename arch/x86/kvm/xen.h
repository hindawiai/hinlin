<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright तऊ 2019 Oracle and/or its affiliates. All rights reserved.
 * Copyright तऊ 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * KVM Xen emulation
 */

#अगर_अघोषित __ARCH_X86_KVM_XEN_H__
#घोषणा __ARCH_X86_KVM_XEN_H__

#अगर_घोषित CONFIG_KVM_XEN
#समावेश <linux/jump_label_ratelimit.h>

बाह्य काष्ठा अटल_key_false_deferred kvm_xen_enabled;

पूर्णांक __kvm_xen_has_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_xen_vcpu_set_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_xen_vcpu_attr *data);
पूर्णांक kvm_xen_vcpu_get_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_xen_vcpu_attr *data);
पूर्णांक kvm_xen_hvm_set_attr(काष्ठा kvm *kvm, काष्ठा kvm_xen_hvm_attr *data);
पूर्णांक kvm_xen_hvm_get_attr(काष्ठा kvm *kvm, काष्ठा kvm_xen_hvm_attr *data);
पूर्णांक kvm_xen_ग_लिखो_hypercall_page(काष्ठा kvm_vcpu *vcpu, u64 data);
पूर्णांक kvm_xen_hvm_config(काष्ठा kvm *kvm, काष्ठा kvm_xen_hvm_config *xhc);
व्योम kvm_xen_destroy_vm(काष्ठा kvm *kvm);

अटल अंतरभूत bool kvm_xen_msr_enabled(काष्ठा kvm *kvm)
अणु
	वापस अटल_branch_unlikely(&kvm_xen_enabled.key) &&
		kvm->arch.xen_hvm_config.msr;
पूर्ण

अटल अंतरभूत bool kvm_xen_hypercall_enabled(काष्ठा kvm *kvm)
अणु
	वापस अटल_branch_unlikely(&kvm_xen_enabled.key) &&
		(kvm->arch.xen_hvm_config.flags &
		 KVM_XEN_HVM_CONFIG_INTERCEPT_HCALL);
पूर्ण

अटल अंतरभूत पूर्णांक kvm_xen_has_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (अटल_branch_unlikely(&kvm_xen_enabled.key) &&
	    vcpu->arch.xen.vcpu_info_set && vcpu->kvm->arch.xen.upcall_vector)
		वापस __kvm_xen_has_पूर्णांकerrupt(vcpu);

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक kvm_xen_ग_लिखो_hypercall_page(काष्ठा kvm_vcpu *vcpu, u64 data)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम kvm_xen_destroy_vm(काष्ठा kvm *kvm)
अणु
पूर्ण

अटल अंतरभूत bool kvm_xen_msr_enabled(काष्ठा kvm *kvm)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool kvm_xen_hypercall_enabled(काष्ठा kvm *kvm)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक kvm_xen_has_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक kvm_xen_hypercall(काष्ठा kvm_vcpu *vcpu);

#समावेश <यंत्र/pvघड़ी-abi.h>
#समावेश <यंत्र/xen/पूर्णांकerface.h>
#समावेश <xen/पूर्णांकerface/vcpu.h>

व्योम kvm_xen_update_runstate_guest(काष्ठा kvm_vcpu *vcpu, पूर्णांक state);

अटल अंतरभूत व्योम kvm_xen_runstate_set_running(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_xen_update_runstate_guest(vcpu, RUNSTATE_running);
पूर्ण

अटल अंतरभूत व्योम kvm_xen_runstate_set_preempted(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * If the vCPU wasn't preempted but took a normal निकास क्रम
	 * some reason (hypercalls, I/O, etc.), that is accounted as
	 * still RUNSTATE_running, as the VMM is still operating on
	 * behalf of the vCPU. Only अगर the VMM करोes actually block
	 * करोes it need to enter RUNSTATE_blocked.
	 */
	अगर (vcpu->preempted)
		kvm_xen_update_runstate_guest(vcpu, RUNSTATE_runnable);
पूर्ण

/* 32-bit compatibility definitions, also used natively in 32-bit build */
काष्ठा compat_arch_vcpu_info अणु
	अचिन्हित पूर्णांक cr2;
	अचिन्हित पूर्णांक pad[5];
पूर्ण;

काष्ठा compat_vcpu_info अणु
	uपूर्णांक8_t evtchn_upcall_pending;
	uपूर्णांक8_t evtchn_upcall_mask;
	uपूर्णांक16_t pad;
	uपूर्णांक32_t evtchn_pending_sel;
	काष्ठा compat_arch_vcpu_info arch;
	काष्ठा pvघड़ी_vcpu_समय_info समय;
पूर्ण; /* 64 bytes (x86) */

काष्ठा compat_arch_shared_info अणु
	अचिन्हित पूर्णांक max_pfn;
	अचिन्हित पूर्णांक pfn_to_mfn_frame_list_list;
	अचिन्हित पूर्णांक nmi_reason;
	अचिन्हित पूर्णांक p2m_cr3;
	अचिन्हित पूर्णांक p2m_vaddr;
	अचिन्हित पूर्णांक p2m_generation;
	uपूर्णांक32_t wc_sec_hi;
पूर्ण;

काष्ठा compat_shared_info अणु
	काष्ठा compat_vcpu_info vcpu_info[MAX_VIRT_CPUS];
	uपूर्णांक32_t evtchn_pending[32];
	uपूर्णांक32_t evtchn_mask[32];
	काष्ठा pvघड़ी_wall_घड़ी wc;
	काष्ठा compat_arch_shared_info arch;
पूर्ण;

काष्ठा compat_vcpu_runstate_info अणु
    पूर्णांक state;
    uपूर्णांक64_t state_entry_समय;
    uपूर्णांक64_t समय[4];
पूर्ण __attribute__((packed));

#पूर्ण_अगर /* __ARCH_X86_KVM_XEN_H__ */
