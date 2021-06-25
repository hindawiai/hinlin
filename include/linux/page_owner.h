<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_PAGE_OWNER_H
#घोषणा __LINUX_PAGE_OWNER_H

#समावेश <linux/jump_label.h>

#अगर_घोषित CONFIG_PAGE_OWNER
बाह्य काष्ठा अटल_key_false page_owner_inited;
बाह्य काष्ठा page_ext_operations page_owner_ops;

बाह्य व्योम __reset_page_owner(काष्ठा page *page, अचिन्हित पूर्णांक order);
बाह्य व्योम __set_page_owner(काष्ठा page *page,
			अचिन्हित पूर्णांक order, gfp_t gfp_mask);
बाह्य व्योम __split_page_owner(काष्ठा page *page, अचिन्हित पूर्णांक nr);
बाह्य व्योम __copy_page_owner(काष्ठा page *oldpage, काष्ठा page *newpage);
बाह्य व्योम __set_page_owner_migrate_reason(काष्ठा page *page, पूर्णांक reason);
बाह्य व्योम __dump_page_owner(काष्ठा page *page);
बाह्य व्योम pagetypeinfo_showmixedcount_prपूर्णांक(काष्ठा seq_file *m,
					pg_data_t *pgdat, काष्ठा zone *zone);

अटल अंतरभूत व्योम reset_page_owner(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	अगर (अटल_branch_unlikely(&page_owner_inited))
		__reset_page_owner(page, order);
पूर्ण

अटल अंतरभूत व्योम set_page_owner(काष्ठा page *page,
			अचिन्हित पूर्णांक order, gfp_t gfp_mask)
अणु
	अगर (अटल_branch_unlikely(&page_owner_inited))
		__set_page_owner(page, order, gfp_mask);
पूर्ण

अटल अंतरभूत व्योम split_page_owner(काष्ठा page *page, अचिन्हित पूर्णांक nr)
अणु
	अगर (अटल_branch_unlikely(&page_owner_inited))
		__split_page_owner(page, nr);
पूर्ण
अटल अंतरभूत व्योम copy_page_owner(काष्ठा page *oldpage, काष्ठा page *newpage)
अणु
	अगर (अटल_branch_unlikely(&page_owner_inited))
		__copy_page_owner(oldpage, newpage);
पूर्ण
अटल अंतरभूत व्योम set_page_owner_migrate_reason(काष्ठा page *page, पूर्णांक reason)
अणु
	अगर (अटल_branch_unlikely(&page_owner_inited))
		__set_page_owner_migrate_reason(page, reason);
पूर्ण
अटल अंतरभूत व्योम dump_page_owner(काष्ठा page *page)
अणु
	अगर (अटल_branch_unlikely(&page_owner_inited))
		__dump_page_owner(page);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम reset_page_owner(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
पूर्ण
अटल अंतरभूत व्योम set_page_owner(काष्ठा page *page,
			अचिन्हित पूर्णांक order, gfp_t gfp_mask)
अणु
पूर्ण
अटल अंतरभूत व्योम split_page_owner(काष्ठा page *page,
			अचिन्हित पूर्णांक order)
अणु
पूर्ण
अटल अंतरभूत व्योम copy_page_owner(काष्ठा page *oldpage, काष्ठा page *newpage)
अणु
पूर्ण
अटल अंतरभूत व्योम set_page_owner_migrate_reason(काष्ठा page *page, पूर्णांक reason)
अणु
पूर्ण
अटल अंतरभूत व्योम dump_page_owner(काष्ठा page *page)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PAGE_OWNER */
#पूर्ण_अगर /* __LINUX_PAGE_OWNER_H */
