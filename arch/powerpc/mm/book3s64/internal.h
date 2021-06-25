<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित ARCH_POWERPC_MM_BOOK3S64_INTERNAL_H
#घोषणा ARCH_POWERPC_MM_BOOK3S64_INTERNAL_H

#समावेश <linux/jump_label.h>

बाह्य bool stress_slb_enabled;

DECLARE_STATIC_KEY_FALSE(stress_slb_key);

अटल अंतरभूत bool stress_slb(व्योम)
अणु
	वापस अटल_branch_unlikely(&stress_slb_key);
पूर्ण

व्योम slb_setup_new_exec(व्योम);

व्योम निकास_lazy_flush_tlb(काष्ठा mm_काष्ठा *mm, bool always_flush);

#पूर्ण_अगर /* ARCH_POWERPC_MM_BOOK3S64_INTERNAL_H */
