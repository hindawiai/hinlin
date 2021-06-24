<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_INIT_H
#घोषणा _ASM_X86_INIT_H

काष्ठा x86_mapping_info अणु
	व्योम *(*alloc_pgt_page)(व्योम *); /* allocate buf क्रम page table */
	व्योम *context;			 /* context क्रम alloc_pgt_page */
	अचिन्हित दीर्घ page_flag;	 /* page flag क्रम PMD or PUD entry */
	अचिन्हित दीर्घ offset;		 /* ident mapping offset */
	bool direct_gbpages;		 /* PUD level 1GB page support */
	अचिन्हित दीर्घ kernpg_flag;	 /* kernel pagetable flag override */
पूर्ण;

पूर्णांक kernel_ident_mapping_init(काष्ठा x86_mapping_info *info, pgd_t *pgd_page,
				अचिन्हित दीर्घ pstart, अचिन्हित दीर्घ pend);

#पूर्ण_अगर /* _ASM_X86_INIT_H */
