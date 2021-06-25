<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __KVM_HYP_EARLY_ALLOC_H
#घोषणा __KVM_HYP_EARLY_ALLOC_H

#समावेश <यंत्र/kvm_pgtable.h>

व्योम hyp_early_alloc_init(व्योम *virt, अचिन्हित दीर्घ size);
अचिन्हित दीर्घ hyp_early_alloc_nr_used_pages(व्योम);
व्योम *hyp_early_alloc_page(व्योम *arg);
व्योम *hyp_early_alloc_contig(अचिन्हित पूर्णांक nr_pages);

बाह्य काष्ठा kvm_pgtable_mm_ops hyp_early_alloc_mm_ops;

#पूर्ण_अगर /* __KVM_HYP_EARLY_ALLOC_H */
