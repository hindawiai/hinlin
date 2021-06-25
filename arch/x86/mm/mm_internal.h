<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __X86_MM_INTERNAL_H
#घोषणा __X86_MM_INTERNAL_H

व्योम *alloc_low_pages(अचिन्हित पूर्णांक num);
अटल अंतरभूत व्योम *alloc_low_page(व्योम)
अणु
	वापस alloc_low_pages(1);
पूर्ण

व्योम early_ioremap_page_table_range_init(व्योम);

अचिन्हित दीर्घ kernel_physical_mapping_init(अचिन्हित दीर्घ start,
					     अचिन्हित दीर्घ end,
					     अचिन्हित दीर्घ page_size_mask,
					     pgprot_t prot);
अचिन्हित दीर्घ kernel_physical_mapping_change(अचिन्हित दीर्घ start,
					     अचिन्हित दीर्घ end,
					     अचिन्हित दीर्घ page_size_mask);
व्योम zone_sizes_init(व्योम);

बाह्य पूर्णांक after_booपंचांगem;

व्योम update_cache_mode_entry(अचिन्हित entry, क्रमागत page_cache_mode cache);

बाह्य अचिन्हित दीर्घ tlb_single_page_flush_उच्चमानing;

#पूर्ण_अगर	/* __X86_MM_INTERNAL_H */
