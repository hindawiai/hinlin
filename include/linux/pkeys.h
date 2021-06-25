<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PKEYS_H
#घोषणा _LINUX_PKEYS_H

#समावेश <linux/mm.h>

#अगर_घोषित CONFIG_ARCH_HAS_PKEYS
#समावेश <यंत्र/pkeys.h>
#अन्यथा /* ! CONFIG_ARCH_HAS_PKEYS */
#घोषणा arch_max_pkey() (1)
#घोषणा execute_only_pkey(mm) (0)
#घोषणा arch_override_mprotect_pkey(vma, prot, pkey) (0)
#घोषणा PKEY_DEDICATED_EXECUTE_ONLY 0
#घोषणा ARCH_VM_PKEY_FLAGS 0

अटल अंतरभूत पूर्णांक vma_pkey(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool mm_pkey_is_allocated(काष्ठा mm_काष्ठा *mm, पूर्णांक pkey)
अणु
	वापस (pkey == 0);
पूर्ण

अटल अंतरभूत पूर्णांक mm_pkey_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक mm_pkey_मुक्त(काष्ठा mm_काष्ठा *mm, पूर्णांक pkey)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक arch_set_user_pkey_access(काष्ठा task_काष्ठा *tsk, पूर्णांक pkey,
			अचिन्हित दीर्घ init_val)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool arch_pkeys_enabled(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम copy_init_pkru_to_fpregs(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* ! CONFIG_ARCH_HAS_PKEYS */

#पूर्ण_अगर /* _LINUX_PKEYS_H */
