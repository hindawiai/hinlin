<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MM_CMA_H__
#घोषणा __MM_CMA_H__

#समावेश <linux/debugfs.h>
#समावेश <linux/kobject.h>

काष्ठा cma_kobject अणु
	काष्ठा kobject kobj;
	काष्ठा cma *cma;
पूर्ण;

काष्ठा cma अणु
	अचिन्हित दीर्घ   base_pfn;
	अचिन्हित दीर्घ   count;
	अचिन्हित दीर्घ   *biपंचांगap;
	अचिन्हित पूर्णांक order_per_bit; /* Order of pages represented by one bit */
	spinlock_t	lock;
#अगर_घोषित CONFIG_CMA_DEBUGFS
	काष्ठा hlist_head mem_head;
	spinlock_t mem_head_lock;
	काष्ठा debugfs_u32_array dfs_biपंचांगap;
#पूर्ण_अगर
	अक्षर name[CMA_MAX_NAME];
#अगर_घोषित CONFIG_CMA_SYSFS
	/* the number of CMA page successful allocations */
	atomic64_t nr_pages_succeeded;
	/* the number of CMA page allocation failures */
	atomic64_t nr_pages_failed;
	/* kobject requires dynamic object */
	काष्ठा cma_kobject *cma_kobj;
#पूर्ण_अगर
पूर्ण;

बाह्य काष्ठा cma cma_areas[MAX_CMA_AREAS];
बाह्य अचिन्हित cma_area_count;

अटल अंतरभूत अचिन्हित दीर्घ cma_biपंचांगap_maxno(काष्ठा cma *cma)
अणु
	वापस cma->count >> cma->order_per_bit;
पूर्ण

#अगर_घोषित CONFIG_CMA_SYSFS
व्योम cma_sysfs_account_success_pages(काष्ठा cma *cma, अचिन्हित दीर्घ nr_pages);
व्योम cma_sysfs_account_fail_pages(काष्ठा cma *cma, अचिन्हित दीर्घ nr_pages);
#अन्यथा
अटल अंतरभूत व्योम cma_sysfs_account_success_pages(काष्ठा cma *cma,
						   अचिन्हित दीर्घ nr_pages) अणुपूर्ण;
अटल अंतरभूत व्योम cma_sysfs_account_fail_pages(काष्ठा cma *cma,
						अचिन्हित दीर्घ nr_pages) अणुपूर्ण;
#पूर्ण_अगर
#पूर्ण_अगर
