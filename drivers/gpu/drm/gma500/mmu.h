<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/**************************************************************************
 * Copyright (c) 2007-2011, Intel Corporation.
 * All Rights Reserved.
 *
 **************************************************************************/

#अगर_अघोषित __MMU_H
#घोषणा __MMU_H

काष्ठा psb_mmu_driver अणु
	/* protects driver- and pd काष्ठाures. Always take in पढ़ो mode
	 * beक्रमe taking the page table spinlock.
	 */
	काष्ठा rw_semaphore sem;

	/* protects page tables, directory tables and pt tables.
	 * and pt काष्ठाures.
	 */
	spinlock_t lock;

	atomic_t needs_tlbflush;
	atomic_t *msvdx_mmu_invaldc;
	काष्ठा psb_mmu_pd *शेष_pd;
	uपूर्णांक32_t bअगर_ctrl;
	पूर्णांक has_clflush;
	पूर्णांक clflush_add;
	अचिन्हित दीर्घ clflush_mask;

	काष्ठा drm_device *dev;
पूर्ण;

काष्ठा psb_mmu_pd;

काष्ठा psb_mmu_pt अणु
	काष्ठा psb_mmu_pd *pd;
	uपूर्णांक32_t index;
	uपूर्णांक32_t count;
	काष्ठा page *p;
	uपूर्णांक32_t *v;
पूर्ण;

काष्ठा psb_mmu_pd अणु
	काष्ठा psb_mmu_driver *driver;
	पूर्णांक hw_context;
	काष्ठा psb_mmu_pt **tables;
	काष्ठा page *p;
	काष्ठा page *dummy_pt;
	काष्ठा page *dummy_page;
	uपूर्णांक32_t pd_mask;
	uपूर्णांक32_t invalid_pde;
	uपूर्णांक32_t invalid_pte;
पूर्ण;

बाह्य काष्ठा psb_mmu_driver *psb_mmu_driver_init(काष्ठा drm_device *dev,
						  पूर्णांक trap_pagefaults,
						  पूर्णांक invalid_type,
						  atomic_t *msvdx_mmu_invaldc);
बाह्य व्योम psb_mmu_driver_takeकरोwn(काष्ठा psb_mmu_driver *driver);
बाह्य काष्ठा psb_mmu_pd *psb_mmu_get_शेष_pd(काष्ठा psb_mmu_driver
						 *driver);
बाह्य काष्ठा psb_mmu_pd *psb_mmu_alloc_pd(काष्ठा psb_mmu_driver *driver,
					   पूर्णांक trap_pagefaults,
					   पूर्णांक invalid_type);
बाह्य व्योम psb_mmu_मुक्त_pagedir(काष्ठा psb_mmu_pd *pd);
बाह्य व्योम psb_mmu_flush(काष्ठा psb_mmu_driver *driver);
बाह्य व्योम psb_mmu_हटाओ_pfn_sequence(काष्ठा psb_mmu_pd *pd,
					अचिन्हित दीर्घ address,
					uपूर्णांक32_t num_pages);
बाह्य पूर्णांक psb_mmu_insert_pfn_sequence(काष्ठा psb_mmu_pd *pd,
				       uपूर्णांक32_t start_pfn,
				       अचिन्हित दीर्घ address,
				       uपूर्णांक32_t num_pages, पूर्णांक type);
बाह्य पूर्णांक psb_mmu_भव_to_pfn(काष्ठा psb_mmu_pd *pd, uपूर्णांक32_t भव,
				  अचिन्हित दीर्घ *pfn);
बाह्य व्योम psb_mmu_set_pd_context(काष्ठा psb_mmu_pd *pd, पूर्णांक hw_context);
बाह्य पूर्णांक psb_mmu_insert_pages(काष्ठा psb_mmu_pd *pd, काष्ठा page **pages,
				अचिन्हित दीर्घ address, uपूर्णांक32_t num_pages,
				uपूर्णांक32_t desired_tile_stride,
				uपूर्णांक32_t hw_tile_stride, पूर्णांक type);
बाह्य व्योम psb_mmu_हटाओ_pages(काष्ठा psb_mmu_pd *pd,
				 अचिन्हित दीर्घ address, uपूर्णांक32_t num_pages,
				 uपूर्णांक32_t desired_tile_stride,
				 uपूर्णांक32_t hw_tile_stride);

#पूर्ण_अगर
