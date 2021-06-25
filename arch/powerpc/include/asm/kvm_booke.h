<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright SUSE Linux Products GmbH 2010
 *
 * Authors: Alexander Graf <agraf@suse.de>
 */

#अगर_अघोषित __ASM_KVM_BOOKE_H__
#घोषणा __ASM_KVM_BOOKE_H__

#समावेश <linux/types.h>
#समावेश <linux/kvm_host.h>

/*
 * Number of available lpids. Only the low-order 6 bits of LPID rgister are
 * implemented on e500mc+ cores.
 */
#घोषणा KVMPPC_NR_LPIDS                        64

#घोषणा KVMPPC_INST_EHPRIV		0x7c00021c
#घोषणा EHPRIV_OC_SHIFT			11
/* "ehpriv 1" : ehpriv with OC = 1 is used क्रम debug emulation */
#घोषणा EHPRIV_OC_DEBUG			1

अटल अंतरभूत व्योम kvmppc_set_gpr(काष्ठा kvm_vcpu *vcpu, पूर्णांक num, uदीर्घ val)
अणु
	vcpu->arch.regs.gpr[num] = val;
पूर्ण

अटल अंतरभूत uदीर्घ kvmppc_get_gpr(काष्ठा kvm_vcpu *vcpu, पूर्णांक num)
अणु
	वापस vcpu->arch.regs.gpr[num];
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_cr(काष्ठा kvm_vcpu *vcpu, u32 val)
अणु
	vcpu->arch.regs.ccr = val;
पूर्ण

अटल अंतरभूत u32 kvmppc_get_cr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.regs.ccr;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_xer(काष्ठा kvm_vcpu *vcpu, uदीर्घ val)
अणु
	vcpu->arch.regs.xer = val;
पूर्ण

अटल अंतरभूत uदीर्घ kvmppc_get_xer(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.regs.xer;
पूर्ण

अटल अंतरभूत bool kvmppc_need_byteswap(काष्ठा kvm_vcpu *vcpu)
अणु
	/* XXX Would need to check TLB entry */
	वापस false;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_ctr(काष्ठा kvm_vcpu *vcpu, uदीर्घ val)
अणु
	vcpu->arch.regs.ctr = val;
पूर्ण

अटल अंतरभूत uदीर्घ kvmppc_get_ctr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.regs.ctr;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_lr(काष्ठा kvm_vcpu *vcpu, uदीर्घ val)
अणु
	vcpu->arch.regs.link = val;
पूर्ण

अटल अंतरभूत uदीर्घ kvmppc_get_lr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.regs.link;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_pc(काष्ठा kvm_vcpu *vcpu, uदीर्घ val)
अणु
	vcpu->arch.regs.nip = val;
पूर्ण

अटल अंतरभूत uदीर्घ kvmppc_get_pc(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.regs.nip;
पूर्ण

#अगर_घोषित CONFIG_BOOKE
अटल अंतरभूत uदीर्घ kvmppc_get_fault_dar(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.fault_dear;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool kvmppc_supports_magic_page(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Magic page is only supported on e500v2 */
#अगर_घोषित CONFIG_KVM_E500V2
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर /* __ASM_KVM_BOOKE_H__ */
