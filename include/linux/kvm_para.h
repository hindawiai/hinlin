<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_KVM_PARA_H
#घोषणा __LINUX_KVM_PARA_H

#समावेश <uapi/linux/kvm_para.h>


अटल अंतरभूत bool kvm_para_has_feature(अचिन्हित पूर्णांक feature)
अणु
	वापस !!(kvm_arch_para_features() & (1UL << feature));
पूर्ण

अटल अंतरभूत bool kvm_para_has_hपूर्णांक(अचिन्हित पूर्णांक feature)
अणु
	वापस !!(kvm_arch_para_hपूर्णांकs() & (1UL << feature));
पूर्ण
#पूर्ण_अगर /* __LINUX_KVM_PARA_H */
