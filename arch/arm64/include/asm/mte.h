<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020 ARM Ltd.
 */
#अगर_अघोषित __ASM_MTE_H
#घोषणा __ASM_MTE_H

#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/mte-def.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/bitfield.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/pgtable-types.h>

बाह्य u64 gcr_kernel_excl;

व्योम mte_clear_page_tags(व्योम *addr);
अचिन्हित दीर्घ mte_copy_tags_from_user(व्योम *to, स्थिर व्योम __user *from,
				      अचिन्हित दीर्घ n);
अचिन्हित दीर्घ mte_copy_tags_to_user(व्योम __user *to, व्योम *from,
				    अचिन्हित दीर्घ n);
पूर्णांक mte_save_tags(काष्ठा page *page);
व्योम mte_save_page_tags(स्थिर व्योम *page_addr, व्योम *tag_storage);
bool mte_restore_tags(swp_entry_t entry, काष्ठा page *page);
व्योम mte_restore_page_tags(व्योम *page_addr, स्थिर व्योम *tag_storage);
व्योम mte_invalidate_tags(पूर्णांक type, pgoff_t offset);
व्योम mte_invalidate_tags_area(पूर्णांक type);
व्योम *mte_allocate_tag_storage(व्योम);
व्योम mte_मुक्त_tag_storage(अक्षर *storage);

#अगर_घोषित CONFIG_ARM64_MTE

/* track which pages have valid allocation tags */
#घोषणा PG_mte_tagged	PG_arch_2

व्योम mte_sync_tags(pte_t *ptep, pte_t pte);
व्योम mte_copy_page_tags(व्योम *kto, स्थिर व्योम *kfrom);
व्योम mte_thपढ़ो_init_user(व्योम);
व्योम mte_thपढ़ो_चयन(काष्ठा task_काष्ठा *next);
व्योम mte_suspend_enter(व्योम);
व्योम mte_suspend_निकास(व्योम);
दीर्घ set_mte_ctrl(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ arg);
दीर्घ get_mte_ctrl(काष्ठा task_काष्ठा *task);
पूर्णांक mte_ptrace_copy_tags(काष्ठा task_काष्ठा *child, दीर्घ request,
			 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data);

#अन्यथा /* CONFIG_ARM64_MTE */

/* unused अगर !CONFIG_ARM64_MTE, silence the compiler */
#घोषणा PG_mte_tagged	0

अटल अंतरभूत व्योम mte_sync_tags(pte_t *ptep, pte_t pte)
अणु
पूर्ण
अटल अंतरभूत व्योम mte_copy_page_tags(व्योम *kto, स्थिर व्योम *kfrom)
अणु
पूर्ण
अटल अंतरभूत व्योम mte_thपढ़ो_init_user(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम mte_thपढ़ो_चयन(काष्ठा task_काष्ठा *next)
अणु
पूर्ण
अटल अंतरभूत व्योम mte_suspend_enter(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम mte_suspend_निकास(व्योम)
अणु
पूर्ण
अटल अंतरभूत दीर्घ set_mte_ctrl(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ arg)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत दीर्घ get_mte_ctrl(काष्ठा task_काष्ठा *task)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक mte_ptrace_copy_tags(काष्ठा task_काष्ठा *child,
				       दीर्घ request, अचिन्हित दीर्घ addr,
				       अचिन्हित दीर्घ data)
अणु
	वापस -EIO;
पूर्ण

#पूर्ण_अगर /* CONFIG_ARM64_MTE */

#अगर_घोषित CONFIG_KASAN_HW_TAGS
/* Whether the MTE asynchronous mode is enabled. */
DECLARE_STATIC_KEY_FALSE(mte_async_mode);

अटल अंतरभूत bool प्रणाली_uses_mte_async_mode(व्योम)
अणु
	वापस अटल_branch_unlikely(&mte_async_mode);
पूर्ण

व्योम mte_check_tfsr_el1(व्योम);

अटल अंतरभूत व्योम mte_check_tfsr_entry(व्योम)
अणु
	mte_check_tfsr_el1();
पूर्ण

अटल अंतरभूत व्योम mte_check_tfsr_निकास(व्योम)
अणु
	/*
	 * The asynchronous faults are sync'ed स्वतःmatically with
	 * TFSR_EL1 on kernel entry but क्रम निकास an explicit dsb()
	 * is required.
	 */
	dsb(nsh);
	isb();

	mte_check_tfsr_el1();
पूर्ण
#अन्यथा
अटल अंतरभूत bool प्रणाली_uses_mte_async_mode(व्योम)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम mte_check_tfsr_el1(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम mte_check_tfsr_entry(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम mte_check_tfsr_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_KASAN_HW_TAGS */

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_MTE_H  */
