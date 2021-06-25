<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright IBM Corp. 2008
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 */
#अगर_अघोषित __POWERPC_KVM_PARA_H__
#घोषणा __POWERPC_KVM_PARA_H__

#समावेश <यंत्र/kvm_guest.h>

#समावेश <uapi/यंत्र/kvm_para.h>

अटल अंतरभूत पूर्णांक kvm_para_available(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_KVM_GUEST) && is_kvm_guest();
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_arch_para_features(व्योम)
अणु
	अचिन्हित दीर्घ r;

	अगर (!kvm_para_available())
		वापस 0;

	अगर(epapr_hypercall0_1(KVM_HCALL_TOKEN(KVM_HC_FEATURES), &r))
		वापस 0;

	वापस r;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_arch_para_hपूर्णांकs(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool kvm_check_and_clear_guest_छोड़ोd(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* __POWERPC_KVM_PARA_H__ */
