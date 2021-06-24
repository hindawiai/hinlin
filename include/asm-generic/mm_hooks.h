<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Define generic no-op hooks क्रम arch_dup_mmap, arch_निकास_mmap
 * and arch_unmap to be included in यंत्र-FOO/mmu_context.h क्रम any
 * arch FOO which करोesn't need to hook these.
 */
#अगर_अघोषित _ASM_GENERIC_MM_HOOKS_H
#घोषणा _ASM_GENERIC_MM_HOOKS_H

अटल अंतरभूत पूर्णांक arch_dup_mmap(काष्ठा mm_काष्ठा *oldmm,
				काष्ठा mm_काष्ठा *mm)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम arch_निकास_mmap(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण

अटल अंतरभूत व्योम arch_unmap(काष्ठा mm_काष्ठा *mm,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
पूर्ण

अटल अंतरभूत bool arch_vma_access_permitted(काष्ठा vm_area_काष्ठा *vma,
		bool ग_लिखो, bool execute, bool क्रमeign)
अणु
	/* by शेष, allow everything */
	वापस true;
पूर्ण
#पूर्ण_अगर	/* _ASM_GENERIC_MM_HOOKS_H */
