<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright SUSE Linux Products GmbH 2010
 *
 * Authors: Alexander Graf <agraf@suse.de>
 */

#अगर_अघोषित __ASM_KVM_BOOK3S_32_H__
#घोषणा __ASM_KVM_BOOK3S_32_H__

अटल अंतरभूत काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu_get(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.shaकरोw_vcpu;
पूर्ण

अटल अंतरभूत व्योम svcpu_put(काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu)
अणु
पूर्ण

#घोषणा PTE_SIZE	12
#घोषणा VSID_ALL	0
#घोषणा SR_INVALID	0x00000001	/* VSID 1 should always be unused */
#घोषणा SR_KP		0x20000000
#घोषणा PTE_V		0x80000000
#घोषणा PTE_SEC		0x00000040
#घोषणा PTE_M		0x00000010
#घोषणा PTE_R		0x00000100
#घोषणा PTE_C		0x00000080

#घोषणा SID_SHIFT	28
#घोषणा ESID_MASK	0xf0000000
#घोषणा VSID_MASK	0x00fffffff0000000ULL
#घोषणा VPN_SHIFT	12

#पूर्ण_अगर /* __ASM_KVM_BOOK3S_32_H__ */
