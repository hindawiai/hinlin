<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2019 Arm Ltd. */

#अगर_अघोषित __KVM_ARM_HYPERCALLS_H
#घोषणा __KVM_ARM_HYPERCALLS_H

#समावेश <यंत्र/kvm_emulate.h>

पूर्णांक kvm_hvc_call_handler(काष्ठा kvm_vcpu *vcpu);

अटल अंतरभूत u32 smccc_get_function(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu_get_reg(vcpu, 0);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ smccc_get_arg1(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu_get_reg(vcpu, 1);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ smccc_get_arg2(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu_get_reg(vcpu, 2);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ smccc_get_arg3(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu_get_reg(vcpu, 3);
पूर्ण

अटल अंतरभूत व्योम smccc_set_retval(काष्ठा kvm_vcpu *vcpu,
				    अचिन्हित दीर्घ a0,
				    अचिन्हित दीर्घ a1,
				    अचिन्हित दीर्घ a2,
				    अचिन्हित दीर्घ a3)
अणु
	vcpu_set_reg(vcpu, 0, a0);
	vcpu_set_reg(vcpu, 1, a1);
	vcpu_set_reg(vcpu, 2, a2);
	vcpu_set_reg(vcpu, 3, a3);
पूर्ण

#पूर्ण_अगर
