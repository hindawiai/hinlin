<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 IBM Corporation
 */

#अगर_अघोषित _ASM_POWERPC_KVM_GUEST_H_
#घोषणा _ASM_POWERPC_KVM_GUEST_H_

#अगर defined(CONFIG_PPC_PSERIES) || defined(CONFIG_KVM_GUEST)
#समावेश <linux/jump_label.h>

DECLARE_STATIC_KEY_FALSE(kvm_guest);

अटल अंतरभूत bool is_kvm_guest(व्योम)
अणु
	वापस अटल_branch_unlikely(&kvm_guest);
पूर्ण

bool check_kvm_guest(व्योम);
#अन्यथा
अटल अंतरभूत bool is_kvm_guest(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool check_kvm_guest(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_POWERPC_KVM_GUEST_H_ */
