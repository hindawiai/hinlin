<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_SGX_H
#घोषणा __KVM_X86_SGX_H

#समावेश <linux/kvm_host.h>

#समावेश "capabilities.h"
#समावेश "vmx_ops.h"

#अगर_घोषित CONFIG_X86_SGX_KVM
बाह्य bool __पढ़ो_mostly enable_sgx;

पूर्णांक handle_encls(काष्ठा kvm_vcpu *vcpu);

व्योम setup_शेष_sgx_lepubkeyhash(व्योम);
व्योम vcpu_setup_sgx_lepubkeyhash(काष्ठा kvm_vcpu *vcpu);

व्योम vmx_ग_लिखो_encls_biपंचांगap(काष्ठा kvm_vcpu *vcpu, काष्ठा vmcs12 *vmcs12);
#अन्यथा
#घोषणा enable_sgx 0

अटल अंतरभूत व्योम setup_शेष_sgx_lepubkeyhash(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम vcpu_setup_sgx_lepubkeyhash(काष्ठा kvm_vcpu *vcpu) अणु पूर्ण

अटल अंतरभूत व्योम vmx_ग_लिखो_encls_biपंचांगap(काष्ठा kvm_vcpu *vcpu,
					  काष्ठा vmcs12 *vmcs12)
अणु
	/* Nothing to करो अगर hardware करोesn't support SGX */
	अगर (cpu_has_vmx_encls_vmनिकास())
		vmcs_ग_लिखो64(ENCLS_EXITING_BITMAP, -1ull);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __KVM_X86_SGX_H */
