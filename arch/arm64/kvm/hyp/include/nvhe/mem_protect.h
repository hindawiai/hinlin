<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 Google LLC
 * Author: Quentin Perret <qperret@google.com>
 */

#अगर_अघोषित __KVM_NVHE_MEM_PROTECT__
#घोषणा __KVM_NVHE_MEM_PROTECT__
#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_pgtable.h>
#समावेश <यंत्र/virt.h>
#समावेश <nvhe/spinlock.h>

काष्ठा host_kvm अणु
	काष्ठा kvm_arch arch;
	काष्ठा kvm_pgtable pgt;
	काष्ठा kvm_pgtable_mm_ops mm_ops;
	hyp_spinlock_t lock;
पूर्ण;
बाह्य काष्ठा host_kvm host_kvm;

पूर्णांक __pkvm_prot_finalize(व्योम);
पूर्णांक __pkvm_mark_hyp(phys_addr_t start, phys_addr_t end);

पूर्णांक kvm_host_prepare_stage2(व्योम *mem_pgt_pool, व्योम *dev_pgt_pool);
व्योम handle_host_mem_पात(काष्ठा kvm_cpu_context *host_ctxt);

अटल __always_अंतरभूत व्योम __load_host_stage2(व्योम)
अणु
	अगर (अटल_branch_likely(&kvm_रक्षित_mode_initialized))
		__load_stage2(&host_kvm.arch.mmu, host_kvm.arch.vtcr);
	अन्यथा
		ग_लिखो_sysreg(0, vttbr_el2);
पूर्ण
#पूर्ण_अगर /* __KVM_NVHE_MEM_PROTECT__ */
