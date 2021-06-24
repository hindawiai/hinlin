<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2006, Intel Corporation.
 *
 * Copyright (C) 2006-2008 Intel Corporation
 * Author: Anil S Keshavamurthy <anil.s.keshavamurthy@पूर्णांकel.com>
 */

#अगर_अघोषित _IOVA_H_
#घोषणा _IOVA_H_

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/atomic.h>
#समावेश <linux/dma-mapping.h>

/* iova काष्ठाure */
काष्ठा iova अणु
	काष्ठा rb_node	node;
	अचिन्हित दीर्घ	pfn_hi; /* Highest allocated pfn */
	अचिन्हित दीर्घ	pfn_lo; /* Lowest allocated pfn */
पूर्ण;

काष्ठा iova_magazine;
काष्ठा iova_cpu_rcache;

#घोषणा IOVA_RANGE_CACHE_MAX_SIZE 6	/* log of max cached IOVA range size (in pages) */
#घोषणा MAX_GLOBAL_MAGS 32	/* magazines per bin */

काष्ठा iova_rcache अणु
	spinlock_t lock;
	अचिन्हित दीर्घ depot_size;
	काष्ठा iova_magazine *depot[MAX_GLOBAL_MAGS];
	काष्ठा iova_cpu_rcache __percpu *cpu_rcaches;
पूर्ण;

काष्ठा iova_करोमुख्य;

/* Call-Back from IOVA code पूर्णांकo IOMMU drivers */
प्रकार व्योम (* iova_flush_cb)(काष्ठा iova_करोमुख्य *करोमुख्य);

/* Deकाष्ठाor क्रम per-entry data */
प्रकार व्योम (* iova_entry_dtor)(अचिन्हित दीर्घ data);

/* Number of entries per Flush Queue */
#घोषणा IOVA_FQ_SIZE	256

/* Timeout (in ms) after which entries are flushed from the Flush-Queue */
#घोषणा IOVA_FQ_TIMEOUT	10

/* Flush Queue entry क्रम defered flushing */
काष्ठा iova_fq_entry अणु
	अचिन्हित दीर्घ iova_pfn;
	अचिन्हित दीर्घ pages;
	अचिन्हित दीर्घ data;
	u64 counter; /* Flush counter when this entrie was added */
पूर्ण;

/* Per-CPU Flush Queue काष्ठाure */
काष्ठा iova_fq अणु
	काष्ठा iova_fq_entry entries[IOVA_FQ_SIZE];
	अचिन्हित head, tail;
	spinlock_t lock;
पूर्ण;

/* holds all the iova translations क्रम a करोमुख्य */
काष्ठा iova_करोमुख्य अणु
	spinlock_t	iova_rbtree_lock; /* Lock to protect update of rbtree */
	काष्ठा rb_root	rbroot;		/* iova करोमुख्य rbtree root */
	काष्ठा rb_node	*cached_node;	/* Save last alloced node */
	काष्ठा rb_node	*cached32_node; /* Save last 32-bit alloced node */
	अचिन्हित दीर्घ	granule;	/* pfn granularity क्रम this करोमुख्य */
	अचिन्हित दीर्घ	start_pfn;	/* Lower limit क्रम this करोमुख्य */
	अचिन्हित दीर्घ	dma_32bit_pfn;
	अचिन्हित दीर्घ	max32_alloc_size; /* Size of last failed allocation */
	काष्ठा iova_fq __percpu *fq;	/* Flush Queue */

	atomic64_t	fq_flush_start_cnt;	/* Number of TLB flushes that
						   have been started */

	atomic64_t	fq_flush_finish_cnt;	/* Number of TLB flushes that
						   have been finished */

	काष्ठा iova	anchor;		/* rbtree lookup anchor */
	काष्ठा iova_rcache rcaches[IOVA_RANGE_CACHE_MAX_SIZE];	/* IOVA range caches */

	iova_flush_cb	flush_cb;	/* Call-Back function to flush IOMMU
					   TLBs */

	iova_entry_dtor entry_dtor;	/* IOMMU driver specअगरic deकाष्ठाor क्रम
					   iova entry */

	काष्ठा समयr_list fq_समयr;		/* Timer to regularily empty the
						   flush-queues */
	atomic_t fq_समयr_on;			/* 1 when समयr is active, 0
						   when not */
	काष्ठा hlist_node	cpuhp_dead;
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ iova_size(काष्ठा iova *iova)
अणु
	वापस iova->pfn_hi - iova->pfn_lo + 1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ iova_shअगरt(काष्ठा iova_करोमुख्य *iovad)
अणु
	वापस __ffs(iovad->granule);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ iova_mask(काष्ठा iova_करोमुख्य *iovad)
अणु
	वापस iovad->granule - 1;
पूर्ण

अटल अंतरभूत माप_प्रकार iova_offset(काष्ठा iova_करोमुख्य *iovad, dma_addr_t iova)
अणु
	वापस iova & iova_mask(iovad);
पूर्ण

अटल अंतरभूत माप_प्रकार iova_align(काष्ठा iova_करोमुख्य *iovad, माप_प्रकार size)
अणु
	वापस ALIGN(size, iovad->granule);
पूर्ण

अटल अंतरभूत dma_addr_t iova_dma_addr(काष्ठा iova_करोमुख्य *iovad, काष्ठा iova *iova)
अणु
	वापस (dma_addr_t)iova->pfn_lo << iova_shअगरt(iovad);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ iova_pfn(काष्ठा iova_करोमुख्य *iovad, dma_addr_t iova)
अणु
	वापस iova >> iova_shअगरt(iovad);
पूर्ण

#अगर IS_ENABLED(CONFIG_IOMMU_IOVA)
पूर्णांक iova_cache_get(व्योम);
व्योम iova_cache_put(व्योम);

व्योम मुक्त_iova(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ pfn);
व्योम __मुक्त_iova(काष्ठा iova_करोमुख्य *iovad, काष्ठा iova *iova);
काष्ठा iova *alloc_iova(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ size,
	अचिन्हित दीर्घ limit_pfn,
	bool size_aligned);
व्योम मुक्त_iova_fast(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ pfn,
		    अचिन्हित दीर्घ size);
व्योम queue_iova(काष्ठा iova_करोमुख्य *iovad,
		अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ pages,
		अचिन्हित दीर्घ data);
अचिन्हित दीर्घ alloc_iova_fast(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ size,
			      अचिन्हित दीर्घ limit_pfn, bool flush_rcache);
काष्ठा iova *reserve_iova(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ pfn_lo,
	अचिन्हित दीर्घ pfn_hi);
व्योम init_iova_करोमुख्य(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ granule,
	अचिन्हित दीर्घ start_pfn);
पूर्णांक init_iova_flush_queue(काष्ठा iova_करोमुख्य *iovad,
			  iova_flush_cb flush_cb, iova_entry_dtor entry_dtor);
काष्ठा iova *find_iova(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ pfn);
व्योम put_iova_करोमुख्य(काष्ठा iova_करोमुख्य *iovad);
#अन्यथा
अटल अंतरभूत पूर्णांक iova_cache_get(व्योम)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत व्योम iova_cache_put(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम मुक्त_iova(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ pfn)
अणु
पूर्ण

अटल अंतरभूत व्योम __मुक्त_iova(काष्ठा iova_करोमुख्य *iovad, काष्ठा iova *iova)
अणु
पूर्ण

अटल अंतरभूत काष्ठा iova *alloc_iova(काष्ठा iova_करोमुख्य *iovad,
				      अचिन्हित दीर्घ size,
				      अचिन्हित दीर्घ limit_pfn,
				      bool size_aligned)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम मुक्त_iova_fast(काष्ठा iova_करोमुख्य *iovad,
				  अचिन्हित दीर्घ pfn,
				  अचिन्हित दीर्घ size)
अणु
पूर्ण

अटल अंतरभूत व्योम queue_iova(काष्ठा iova_करोमुख्य *iovad,
			      अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ pages,
			      अचिन्हित दीर्घ data)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ alloc_iova_fast(काष्ठा iova_करोमुख्य *iovad,
					    अचिन्हित दीर्घ size,
					    अचिन्हित दीर्घ limit_pfn,
					    bool flush_rcache)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा iova *reserve_iova(काष्ठा iova_करोमुख्य *iovad,
					अचिन्हित दीर्घ pfn_lo,
					अचिन्हित दीर्घ pfn_hi)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम init_iova_करोमुख्य(काष्ठा iova_करोमुख्य *iovad,
				    अचिन्हित दीर्घ granule,
				    अचिन्हित दीर्घ start_pfn)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक init_iova_flush_queue(काष्ठा iova_करोमुख्य *iovad,
					iova_flush_cb flush_cb,
					iova_entry_dtor entry_dtor)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा iova *find_iova(काष्ठा iova_करोमुख्य *iovad,
				     अचिन्हित दीर्घ pfn)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम put_iova_करोमुख्य(काष्ठा iova_करोमुख्य *iovad)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
