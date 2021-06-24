<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __KVM_HYP_GFP_H
#घोषणा __KVM_HYP_GFP_H

#समावेश <linux/list.h>

#समावेश <nvhe/memory.h>
#समावेश <nvhe/spinlock.h>

#घोषणा HYP_NO_ORDER	अच_पूर्णांक_उच्च

काष्ठा hyp_pool अणु
	/*
	 * Spinlock protecting concurrent changes to the memory pool as well as
	 * the काष्ठा hyp_page of the pool's pages until we have a proper atomic
	 * API at EL2.
	 */
	hyp_spinlock_t lock;
	काष्ठा list_head मुक्त_area[MAX_ORDER];
	phys_addr_t range_start;
	phys_addr_t range_end;
	अचिन्हित पूर्णांक max_order;
पूर्ण;

अटल अंतरभूत व्योम hyp_page_ref_inc(काष्ठा hyp_page *p)
अणु
	काष्ठा hyp_pool *pool = hyp_page_to_pool(p);

	hyp_spin_lock(&pool->lock);
	p->refcount++;
	hyp_spin_unlock(&pool->lock);
पूर्ण

अटल अंतरभूत पूर्णांक hyp_page_ref_dec_and_test(काष्ठा hyp_page *p)
अणु
	काष्ठा hyp_pool *pool = hyp_page_to_pool(p);
	पूर्णांक ret;

	hyp_spin_lock(&pool->lock);
	p->refcount--;
	ret = (p->refcount == 0);
	hyp_spin_unlock(&pool->lock);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम hyp_set_page_refcounted(काष्ठा hyp_page *p)
अणु
	काष्ठा hyp_pool *pool = hyp_page_to_pool(p);

	hyp_spin_lock(&pool->lock);
	अगर (p->refcount) अणु
		hyp_spin_unlock(&pool->lock);
		BUG();
	पूर्ण
	p->refcount = 1;
	hyp_spin_unlock(&pool->lock);
पूर्ण

/* Allocation */
व्योम *hyp_alloc_pages(काष्ठा hyp_pool *pool, अचिन्हित पूर्णांक order);
व्योम hyp_get_page(व्योम *addr);
व्योम hyp_put_page(व्योम *addr);

/* Used pages cannot be मुक्तd */
पूर्णांक hyp_pool_init(काष्ठा hyp_pool *pool, u64 pfn, अचिन्हित पूर्णांक nr_pages,
		  अचिन्हित पूर्णांक reserved_pages);
#पूर्ण_अगर /* __KVM_HYP_GFP_H */
