<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __IRQ_H
#घोषणा __IRQ_H

#समावेश <linux/kvm_host.h>

अटल अंतरभूत पूर्णांक irqchip_in_kernel(काष्ठा kvm *kvm)
अणु
	पूर्णांक ret = 0;

#अगर_घोषित CONFIG_KVM_MPIC
	ret = ret || (kvm->arch.mpic != शून्य);
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_XICS
	ret = ret || (kvm->arch.xics != शून्य);
	ret = ret || (kvm->arch.xive != शून्य);
#पूर्ण_अगर
	smp_rmb();
	वापस ret;
पूर्ण

#पूर्ण_अगर
