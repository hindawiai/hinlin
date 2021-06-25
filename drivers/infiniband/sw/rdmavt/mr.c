<शैली गुरु>
/*
 * Copyright(c) 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/rdma_vt.h>
#समावेश "vt.h"
#समावेश "mr.h"
#समावेश "trace.h"

/**
 * rvt_driver_mr_init - Init MR resources per driver
 * @rdi: rvt dev काष्ठा
 *
 * Do any पूर्णांकilization needed when a driver रेजिस्टरs with rdmavt.
 *
 * Return: 0 on success or त्रुटि_सं on failure
 */
पूर्णांक rvt_driver_mr_init(काष्ठा rvt_dev_info *rdi)
अणु
	अचिन्हित पूर्णांक lkey_table_size = rdi->dparms.lkey_table_size;
	अचिन्हित lk_tab_size;
	पूर्णांक i;

	/*
	 * The top hfi1_lkey_table_size bits are used to index the
	 * table.  The lower 8 bits can be owned by the user (copied from
	 * the LKEY).  The reमुख्यing bits act as a generation number or tag.
	 */
	अगर (!lkey_table_size)
		वापस -EINVAL;

	spin_lock_init(&rdi->lkey_table.lock);

	/* ensure generation is at least 4 bits */
	अगर (lkey_table_size > RVT_MAX_LKEY_TABLE_BITS) अणु
		rvt_pr_warn(rdi, "lkey bits %u too large, reduced to %u\n",
			    lkey_table_size, RVT_MAX_LKEY_TABLE_BITS);
		rdi->dparms.lkey_table_size = RVT_MAX_LKEY_TABLE_BITS;
		lkey_table_size = rdi->dparms.lkey_table_size;
	पूर्ण
	rdi->lkey_table.max = 1 << lkey_table_size;
	rdi->lkey_table.shअगरt = 32 - lkey_table_size;
	lk_tab_size = rdi->lkey_table.max * माप(*rdi->lkey_table.table);
	rdi->lkey_table.table = (काष्ठा rvt_mregion __rcu **)
			       vदो_स्मृति_node(lk_tab_size, rdi->dparms.node);
	अगर (!rdi->lkey_table.table)
		वापस -ENOMEM;

	RCU_INIT_POINTER(rdi->dma_mr, शून्य);
	क्रम (i = 0; i < rdi->lkey_table.max; i++)
		RCU_INIT_POINTER(rdi->lkey_table.table[i], शून्य);

	rdi->dparms.props.max_mr = rdi->lkey_table.max;
	वापस 0;
पूर्ण

/**
 *rvt_mr_निकास: clean up MR
 *@rdi: rvt dev काष्ठाure
 *
 * called when drivers have unरेजिस्टरed or perhaps failed to रेजिस्टर with us
 */
व्योम rvt_mr_निकास(काष्ठा rvt_dev_info *rdi)
अणु
	अगर (rdi->dma_mr)
		rvt_pr_err(rdi, "DMA MR not null!\n");

	vमुक्त(rdi->lkey_table.table);
पूर्ण

अटल व्योम rvt_deinit_mregion(काष्ठा rvt_mregion *mr)
अणु
	पूर्णांक i = mr->mapsz;

	mr->mapsz = 0;
	जबतक (i)
		kमुक्त(mr->map[--i]);
	percpu_ref_निकास(&mr->refcount);
पूर्ण

अटल व्योम __rvt_mregion_complete(काष्ठा percpu_ref *ref)
अणु
	काष्ठा rvt_mregion *mr = container_of(ref, काष्ठा rvt_mregion,
					      refcount);

	complete(&mr->comp);
पूर्ण

अटल पूर्णांक rvt_init_mregion(काष्ठा rvt_mregion *mr, काष्ठा ib_pd *pd,
			    पूर्णांक count, अचिन्हित पूर्णांक percpu_flags)
अणु
	पूर्णांक m, i = 0;
	काष्ठा rvt_dev_info *dev = ib_to_rvt(pd->device);

	mr->mapsz = 0;
	m = (count + RVT_SEGSZ - 1) / RVT_SEGSZ;
	क्रम (; i < m; i++) अणु
		mr->map[i] = kzalloc_node(माप(*mr->map[0]), GFP_KERNEL,
					  dev->dparms.node);
		अगर (!mr->map[i])
			जाओ bail;
		mr->mapsz++;
	पूर्ण
	init_completion(&mr->comp);
	/* count वापसing the ptr to user */
	अगर (percpu_ref_init(&mr->refcount, &__rvt_mregion_complete,
			    percpu_flags, GFP_KERNEL))
		जाओ bail;

	atomic_set(&mr->lkey_invalid, 0);
	mr->pd = pd;
	mr->max_segs = count;
	वापस 0;
bail:
	rvt_deinit_mregion(mr);
	वापस -ENOMEM;
पूर्ण

/**
 * rvt_alloc_lkey - allocate an lkey
 * @mr: memory region that this lkey protects
 * @dma_region: 0->normal key, 1->restricted DMA key
 *
 * Returns 0 अगर successful, otherwise वापसs -त्रुटि_सं.
 *
 * Increments mr reference count as required.
 *
 * Sets the lkey field mr क्रम non-dma regions.
 *
 */
अटल पूर्णांक rvt_alloc_lkey(काष्ठा rvt_mregion *mr, पूर्णांक dma_region)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;
	u32 n;
	पूर्णांक ret = 0;
	काष्ठा rvt_dev_info *dev = ib_to_rvt(mr->pd->device);
	काष्ठा rvt_lkey_table *rkt = &dev->lkey_table;

	rvt_get_mr(mr);
	spin_lock_irqsave(&rkt->lock, flags);

	/* special हाल क्रम dma_mr lkey == 0 */
	अगर (dma_region) अणु
		काष्ठा rvt_mregion *पंचांगr;

		पंचांगr = rcu_access_poपूर्णांकer(dev->dma_mr);
		अगर (!पंचांगr) अणु
			mr->lkey_published = 1;
			/* Insure published written first */
			rcu_assign_poपूर्णांकer(dev->dma_mr, mr);
			rvt_get_mr(mr);
		पूर्ण
		जाओ success;
	पूर्ण

	/* Find the next available LKEY */
	r = rkt->next;
	n = r;
	क्रम (;;) अणु
		अगर (!rcu_access_poपूर्णांकer(rkt->table[r]))
			अवरोध;
		r = (r + 1) & (rkt->max - 1);
		अगर (r == n)
			जाओ bail;
	पूर्ण
	rkt->next = (r + 1) & (rkt->max - 1);
	/*
	 * Make sure lkey is never zero which is reserved to indicate an
	 * unrestricted LKEY.
	 */
	rkt->gen++;
	/*
	 * bits are capped to ensure enough bits क्रम generation number
	 */
	mr->lkey = (r << (32 - dev->dparms.lkey_table_size)) |
		((((1 << (24 - dev->dparms.lkey_table_size)) - 1) & rkt->gen)
		 << 8);
	अगर (mr->lkey == 0) अणु
		mr->lkey |= 1 << 8;
		rkt->gen++;
	पूर्ण
	mr->lkey_published = 1;
	/* Insure published written first */
	rcu_assign_poपूर्णांकer(rkt->table[r], mr);
success:
	spin_unlock_irqrestore(&rkt->lock, flags);
out:
	वापस ret;
bail:
	rvt_put_mr(mr);
	spin_unlock_irqrestore(&rkt->lock, flags);
	ret = -ENOMEM;
	जाओ out;
पूर्ण

/**
 * rvt_मुक्त_lkey - मुक्त an lkey
 * @mr: mr to मुक्त from tables
 */
अटल व्योम rvt_मुक्त_lkey(काष्ठा rvt_mregion *mr)
अणु
	अचिन्हित दीर्घ flags;
	u32 lkey = mr->lkey;
	u32 r;
	काष्ठा rvt_dev_info *dev = ib_to_rvt(mr->pd->device);
	काष्ठा rvt_lkey_table *rkt = &dev->lkey_table;
	पूर्णांक मुक्तd = 0;

	spin_lock_irqsave(&rkt->lock, flags);
	अगर (!lkey) अणु
		अगर (mr->lkey_published) अणु
			mr->lkey_published = 0;
			/* insure published is written beक्रमe poपूर्णांकer */
			rcu_assign_poपूर्णांकer(dev->dma_mr, शून्य);
			rvt_put_mr(mr);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!mr->lkey_published)
			जाओ out;
		r = lkey >> (32 - dev->dparms.lkey_table_size);
		mr->lkey_published = 0;
		/* insure published is written beक्रमe poपूर्णांकer */
		rcu_assign_poपूर्णांकer(rkt->table[r], शून्य);
	पूर्ण
	मुक्तd++;
out:
	spin_unlock_irqrestore(&rkt->lock, flags);
	अगर (मुक्तd)
		percpu_ref_समाप्त(&mr->refcount);
पूर्ण

अटल काष्ठा rvt_mr *__rvt_alloc_mr(पूर्णांक count, काष्ठा ib_pd *pd)
अणु
	काष्ठा rvt_mr *mr;
	पूर्णांक rval = -ENOMEM;
	पूर्णांक m;

	/* Allocate काष्ठा plus poपूर्णांकers to first level page tables. */
	m = (count + RVT_SEGSZ - 1) / RVT_SEGSZ;
	mr = kzalloc(काष्ठा_size(mr, mr.map, m), GFP_KERNEL);
	अगर (!mr)
		जाओ bail;

	rval = rvt_init_mregion(&mr->mr, pd, count, 0);
	अगर (rval)
		जाओ bail;
	/*
	 * ib_reg_phys_mr() will initialize mr->ibmr except क्रम
	 * lkey and rkey.
	 */
	rval = rvt_alloc_lkey(&mr->mr, 0);
	अगर (rval)
		जाओ bail_mregion;
	mr->ibmr.lkey = mr->mr.lkey;
	mr->ibmr.rkey = mr->mr.lkey;
करोne:
	वापस mr;

bail_mregion:
	rvt_deinit_mregion(&mr->mr);
bail:
	kमुक्त(mr);
	mr = ERR_PTR(rval);
	जाओ करोne;
पूर्ण

अटल व्योम __rvt_मुक्त_mr(काष्ठा rvt_mr *mr)
अणु
	rvt_मुक्त_lkey(&mr->mr);
	rvt_deinit_mregion(&mr->mr);
	kमुक्त(mr);
पूर्ण

/**
 * rvt_get_dma_mr - get a DMA memory region
 * @pd: protection करोमुख्य क्रम this memory region
 * @acc: access flags
 *
 * Return: the memory region on success, otherwise वापसs an त्रुटि_सं.
 */
काष्ठा ib_mr *rvt_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc)
अणु
	काष्ठा rvt_mr *mr;
	काष्ठा ib_mr *ret;
	पूर्णांक rval;

	अगर (ibpd_to_rvtpd(pd)->user)
		वापस ERR_PTR(-EPERM);

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr) अणु
		ret = ERR_PTR(-ENOMEM);
		जाओ bail;
	पूर्ण

	rval = rvt_init_mregion(&mr->mr, pd, 0, 0);
	अगर (rval) अणु
		ret = ERR_PTR(rval);
		जाओ bail;
	पूर्ण

	rval = rvt_alloc_lkey(&mr->mr, 1);
	अगर (rval) अणु
		ret = ERR_PTR(rval);
		जाओ bail_mregion;
	पूर्ण

	mr->mr.access_flags = acc;
	ret = &mr->ibmr;
करोne:
	वापस ret;

bail_mregion:
	rvt_deinit_mregion(&mr->mr);
bail:
	kमुक्त(mr);
	जाओ करोne;
पूर्ण

/**
 * rvt_reg_user_mr - रेजिस्टर a userspace memory region
 * @pd: protection करोमुख्य क्रम this memory region
 * @start: starting userspace address
 * @length: length of region to रेजिस्टर
 * @virt_addr: associated भव address
 * @mr_access_flags: access flags क्रम this memory region
 * @udata: unused by the driver
 *
 * Return: the memory region on success, otherwise वापसs an त्रुटि_सं.
 */
काष्ठा ib_mr *rvt_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
			      u64 virt_addr, पूर्णांक mr_access_flags,
			      काष्ठा ib_udata *udata)
अणु
	काष्ठा rvt_mr *mr;
	काष्ठा ib_umem *umem;
	काष्ठा sg_page_iter sg_iter;
	पूर्णांक n, m;
	काष्ठा ib_mr *ret;

	अगर (length == 0)
		वापस ERR_PTR(-EINVAL);

	umem = ib_umem_get(pd->device, start, length, mr_access_flags);
	अगर (IS_ERR(umem))
		वापस (व्योम *)umem;

	n = ib_umem_num_pages(umem);

	mr = __rvt_alloc_mr(n, pd);
	अगर (IS_ERR(mr)) अणु
		ret = (काष्ठा ib_mr *)mr;
		जाओ bail_umem;
	पूर्ण

	mr->mr.user_base = start;
	mr->mr.iova = virt_addr;
	mr->mr.length = length;
	mr->mr.offset = ib_umem_offset(umem);
	mr->mr.access_flags = mr_access_flags;
	mr->umem = umem;

	mr->mr.page_shअगरt = PAGE_SHIFT;
	m = 0;
	n = 0;
	क्रम_each_sg_page (umem->sg_head.sgl, &sg_iter, umem->nmap, 0) अणु
		व्योम *vaddr;

		vaddr = page_address(sg_page_iter_page(&sg_iter));
		अगर (!vaddr) अणु
			ret = ERR_PTR(-EINVAL);
			जाओ bail_inval;
		पूर्ण
		mr->mr.map[m]->segs[n].vaddr = vaddr;
		mr->mr.map[m]->segs[n].length = PAGE_SIZE;
		trace_rvt_mr_user_seg(&mr->mr, m, n, vaddr, PAGE_SIZE);
		अगर (++n == RVT_SEGSZ) अणु
			m++;
			n = 0;
		पूर्ण
	पूर्ण
	वापस &mr->ibmr;

bail_inval:
	__rvt_मुक्त_mr(mr);

bail_umem:
	ib_umem_release(umem);

	वापस ret;
पूर्ण

/**
 * rvt_dereg_clean_qp_cb - callback from iterator
 * @qp: the qp
 * @v: the mregion (as u64)
 *
 * This routine fields the callback क्रम all QPs and
 * क्रम QPs in the same PD as the MR will call the
 * rvt_qp_mr_clean() to potentially cleanup references.
 */
अटल व्योम rvt_dereg_clean_qp_cb(काष्ठा rvt_qp *qp, u64 v)
अणु
	काष्ठा rvt_mregion *mr = (काष्ठा rvt_mregion *)v;

	/* skip PDs that are not ours */
	अगर (mr->pd != qp->ibqp.pd)
		वापस;
	rvt_qp_mr_clean(qp, mr->lkey);
पूर्ण

/**
 * rvt_dereg_clean_qps - find QPs क्रम reference cleanup
 * @mr: the MR that is being deरेजिस्टरed
 *
 * This routine iterates RC QPs looking क्रम references
 * to the lkey noted in mr.
 */
अटल व्योम rvt_dereg_clean_qps(काष्ठा rvt_mregion *mr)
अणु
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(mr->pd->device);

	rvt_qp_iter(rdi, (u64)mr, rvt_dereg_clean_qp_cb);
पूर्ण

/**
 * rvt_check_refs - check references
 * @mr: the megion
 * @t: the caller identअगरication
 *
 * This routine checks MRs holding a reference during
 * when being de-रेजिस्टरed.
 *
 * If the count is non-zero, the code calls a clean routine then
 * रुकोs क्रम the समयout क्रम the count to zero.
 */
अटल पूर्णांक rvt_check_refs(काष्ठा rvt_mregion *mr, स्थिर अक्षर *t)
अणु
	अचिन्हित दीर्घ समयout;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(mr->pd->device);

	अगर (mr->lkey) अणु
		/* aव्योम dma mr */
		rvt_dereg_clean_qps(mr);
		/* @mr was indexed on rcu रक्षित @lkey_table */
		synchronize_rcu();
	पूर्ण

	समयout = रुको_क्रम_completion_समयout(&mr->comp, 5 * HZ);
	अगर (!समयout) अणु
		rvt_pr_err(rdi,
			   "%s timeout mr %p pd %p lkey %x refcount %ld\n",
			   t, mr, mr->pd, mr->lkey,
			   atomic_दीर्घ_पढ़ो(&mr->refcount.data->count));
		rvt_get_mr(mr);
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * rvt_mr_has_lkey - is MR
 * @mr: the mregion
 * @lkey: the lkey
 */
bool rvt_mr_has_lkey(काष्ठा rvt_mregion *mr, u32 lkey)
अणु
	वापस mr && lkey == mr->lkey;
पूर्ण

/**
 * rvt_ss_has_lkey - is mr in sge tests
 * @ss: the sge state
 * @lkey: the lkey
 *
 * This code tests क्रम an MR in the indicated
 * sge state.
 */
bool rvt_ss_has_lkey(काष्ठा rvt_sge_state *ss, u32 lkey)
अणु
	पूर्णांक i;
	bool rval = false;

	अगर (!ss->num_sge)
		वापस rval;
	/* first one */
	rval = rvt_mr_has_lkey(ss->sge.mr, lkey);
	/* any others */
	क्रम (i = 0; !rval && i < ss->num_sge - 1; i++)
		rval = rvt_mr_has_lkey(ss->sg_list[i].mr, lkey);
	वापस rval;
पूर्ण

/**
 * rvt_dereg_mr - unरेजिस्टर and मुक्त a memory region
 * @ibmr: the memory region to मुक्त
 * @udata: unused by the driver
 *
 * Note that this is called to मुक्त MRs created by rvt_get_dma_mr()
 * or rvt_reg_user_mr().
 *
 * Returns 0 on success.
 */
पूर्णांक rvt_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata)
अणु
	काष्ठा rvt_mr *mr = to_imr(ibmr);
	पूर्णांक ret;

	rvt_मुक्त_lkey(&mr->mr);

	rvt_put_mr(&mr->mr); /* will set completion अगर last */
	ret = rvt_check_refs(&mr->mr, __func__);
	अगर (ret)
		जाओ out;
	rvt_deinit_mregion(&mr->mr);
	ib_umem_release(mr->umem);
	kमुक्त(mr);
out:
	वापस ret;
पूर्ण

/**
 * rvt_alloc_mr - Allocate a memory region usable with the
 * @pd: protection करोमुख्य क्रम this memory region
 * @mr_type: mem region type
 * @max_num_sg: Max number of segments allowed
 *
 * Return: the memory region on success, otherwise वापस an त्रुटि_सं.
 */
काष्ठा ib_mr *rvt_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			   u32 max_num_sg)
अणु
	काष्ठा rvt_mr *mr;

	अगर (mr_type != IB_MR_TYPE_MEM_REG)
		वापस ERR_PTR(-EINVAL);

	mr = __rvt_alloc_mr(max_num_sg, pd);
	अगर (IS_ERR(mr))
		वापस (काष्ठा ib_mr *)mr;

	वापस &mr->ibmr;
पूर्ण

/**
 * rvt_set_page - page assignment function called by ib_sg_to_pages
 * @ibmr: memory region
 * @addr: dma address of mapped page
 *
 * Return: 0 on success
 */
अटल पूर्णांक rvt_set_page(काष्ठा ib_mr *ibmr, u64 addr)
अणु
	काष्ठा rvt_mr *mr = to_imr(ibmr);
	u32 ps = 1 << mr->mr.page_shअगरt;
	u32 mapped_segs = mr->mr.length >> mr->mr.page_shअगरt;
	पूर्णांक m, n;

	अगर (unlikely(mapped_segs == mr->mr.max_segs))
		वापस -ENOMEM;

	m = mapped_segs / RVT_SEGSZ;
	n = mapped_segs % RVT_SEGSZ;
	mr->mr.map[m]->segs[n].vaddr = (व्योम *)addr;
	mr->mr.map[m]->segs[n].length = ps;
	mr->mr.length += ps;
	trace_rvt_mr_page_seg(&mr->mr, m, n, (व्योम *)addr, ps);

	वापस 0;
पूर्ण

/**
 * rvt_map_mr_sg - map sg list and set it the memory region
 * @ibmr: memory region
 * @sg: dma mapped scatterlist
 * @sg_nents: number of entries in sg
 * @sg_offset: offset in bytes पूर्णांकo sg
 *
 * Overग_लिखो rvt_mr length with mr length calculated by ib_sg_to_pages.
 *
 * Return: number of sg elements mapped to the memory region
 */
पूर्णांक rvt_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg,
		  पूर्णांक sg_nents, अचिन्हित पूर्णांक *sg_offset)
अणु
	काष्ठा rvt_mr *mr = to_imr(ibmr);
	पूर्णांक ret;

	mr->mr.length = 0;
	mr->mr.page_shअगरt = PAGE_SHIFT;
	ret = ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset, rvt_set_page);
	mr->mr.user_base = ibmr->iova;
	mr->mr.iova = ibmr->iova;
	mr->mr.offset = ibmr->iova - (u64)mr->mr.map[0]->segs[0].vaddr;
	mr->mr.length = (माप_प्रकार)ibmr->length;
	trace_rvt_map_mr_sg(ibmr, sg_nents, sg_offset);
	वापस ret;
पूर्ण

/**
 * rvt_fast_reg_mr - fast रेजिस्टर physical MR
 * @qp: the queue pair where the work request comes from
 * @ibmr: the memory region to be रेजिस्टरed
 * @key: updated key क्रम this memory region
 * @access: access flags क्रम this memory region
 *
 * Returns 0 on success.
 */
पूर्णांक rvt_fast_reg_mr(काष्ठा rvt_qp *qp, काष्ठा ib_mr *ibmr, u32 key,
		    पूर्णांक access)
अणु
	काष्ठा rvt_mr *mr = to_imr(ibmr);

	अगर (qp->ibqp.pd != mr->mr.pd)
		वापस -EACCES;

	/* not applicable to dma MR or user MR */
	अगर (!mr->mr.lkey || mr->umem)
		वापस -EINVAL;

	अगर ((key & 0xFFFFFF00) != (mr->mr.lkey & 0xFFFFFF00))
		वापस -EINVAL;

	ibmr->lkey = key;
	ibmr->rkey = key;
	mr->mr.lkey = key;
	mr->mr.access_flags = access;
	mr->mr.iova = ibmr->iova;
	atomic_set(&mr->mr.lkey_invalid, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rvt_fast_reg_mr);

/**
 * rvt_invalidate_rkey - invalidate an MR rkey
 * @qp: queue pair associated with the invalidate op
 * @rkey: rkey to invalidate
 *
 * Returns 0 on success.
 */
पूर्णांक rvt_invalidate_rkey(काष्ठा rvt_qp *qp, u32 rkey)
अणु
	काष्ठा rvt_dev_info *dev = ib_to_rvt(qp->ibqp.device);
	काष्ठा rvt_lkey_table *rkt = &dev->lkey_table;
	काष्ठा rvt_mregion *mr;

	अगर (rkey == 0)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	mr = rcu_dereference(
		rkt->table[(rkey >> (32 - dev->dparms.lkey_table_size))]);
	अगर (unlikely(!mr || mr->lkey != rkey || qp->ibqp.pd != mr->pd))
		जाओ bail;

	atomic_set(&mr->lkey_invalid, 1);
	rcu_पढ़ो_unlock();
	वापस 0;

bail:
	rcu_पढ़ो_unlock();
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(rvt_invalidate_rkey);

/**
 * rvt_sge_adjacent - is isge compressible
 * @last_sge: last outgoing SGE written
 * @sge: SGE to check
 *
 * If adjacent will update last_sge to add length.
 *
 * Return: true अगर isge is adjacent to last sge
 */
अटल अंतरभूत bool rvt_sge_adjacent(काष्ठा rvt_sge *last_sge,
				    काष्ठा ib_sge *sge)
अणु
	अगर (last_sge && sge->lkey == last_sge->mr->lkey &&
	    ((uपूर्णांक64_t)(last_sge->vaddr + last_sge->length) == sge->addr)) अणु
		अगर (sge->lkey) अणु
			अगर (unlikely((sge->addr - last_sge->mr->user_base +
			      sge->length > last_sge->mr->length)))
				वापस false; /* overrun, caller will catch */
		पूर्ण अन्यथा अणु
			last_sge->length += sge->length;
		पूर्ण
		last_sge->sge_length += sge->length;
		trace_rvt_sge_adjacent(last_sge, sge);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * rvt_lkey_ok - check IB SGE क्रम validity and initialize
 * @rkt: table containing lkey to check SGE against
 * @pd: protection करोमुख्य
 * @isge: outgoing पूर्णांकernal SGE
 * @last_sge: last outgoing SGE written
 * @sge: SGE to check
 * @acc: access flags
 *
 * Check the IB SGE क्रम validity and initialize our पूर्णांकernal version
 * of it.
 *
 * Increments the reference count when a new sge is stored.
 *
 * Return: 0 अगर compressed, 1 अगर added , otherwise वापसs -त्रुटि_सं.
 */
पूर्णांक rvt_lkey_ok(काष्ठा rvt_lkey_table *rkt, काष्ठा rvt_pd *pd,
		काष्ठा rvt_sge *isge, काष्ठा rvt_sge *last_sge,
		काष्ठा ib_sge *sge, पूर्णांक acc)
अणु
	काष्ठा rvt_mregion *mr;
	अचिन्हित n, m;
	माप_प्रकार off;

	/*
	 * We use LKEY == zero क्रम kernel भव addresses
	 * (see rvt_get_dma_mr()).
	 */
	अगर (sge->lkey == 0) अणु
		काष्ठा rvt_dev_info *dev = ib_to_rvt(pd->ibpd.device);

		अगर (pd->user)
			वापस -EINVAL;
		अगर (rvt_sge_adjacent(last_sge, sge))
			वापस 0;
		rcu_पढ़ो_lock();
		mr = rcu_dereference(dev->dma_mr);
		अगर (!mr)
			जाओ bail;
		rvt_get_mr(mr);
		rcu_पढ़ो_unlock();

		isge->mr = mr;
		isge->vaddr = (व्योम *)sge->addr;
		isge->length = sge->length;
		isge->sge_length = sge->length;
		isge->m = 0;
		isge->n = 0;
		जाओ ok;
	पूर्ण
	अगर (rvt_sge_adjacent(last_sge, sge))
		वापस 0;
	rcu_पढ़ो_lock();
	mr = rcu_dereference(rkt->table[sge->lkey >> rkt->shअगरt]);
	अगर (!mr)
		जाओ bail;
	rvt_get_mr(mr);
	अगर (!READ_ONCE(mr->lkey_published))
		जाओ bail_unref;

	अगर (unlikely(atomic_पढ़ो(&mr->lkey_invalid) ||
		     mr->lkey != sge->lkey || mr->pd != &pd->ibpd))
		जाओ bail_unref;

	off = sge->addr - mr->user_base;
	अगर (unlikely(sge->addr < mr->user_base ||
		     off + sge->length > mr->length ||
		     (mr->access_flags & acc) != acc))
		जाओ bail_unref;
	rcu_पढ़ो_unlock();

	off += mr->offset;
	अगर (mr->page_shअगरt) अणु
		/*
		 * page sizes are unअगरorm घातer of 2 so no loop is necessary
		 * entries_spanned_by_off is the number of बार the loop below
		 * would have executed.
		*/
		माप_प्रकार entries_spanned_by_off;

		entries_spanned_by_off = off >> mr->page_shअगरt;
		off -= (entries_spanned_by_off << mr->page_shअगरt);
		m = entries_spanned_by_off / RVT_SEGSZ;
		n = entries_spanned_by_off % RVT_SEGSZ;
	पूर्ण अन्यथा अणु
		m = 0;
		n = 0;
		जबतक (off >= mr->map[m]->segs[n].length) अणु
			off -= mr->map[m]->segs[n].length;
			n++;
			अगर (n >= RVT_SEGSZ) अणु
				m++;
				n = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	isge->mr = mr;
	isge->vaddr = mr->map[m]->segs[n].vaddr + off;
	isge->length = mr->map[m]->segs[n].length - off;
	isge->sge_length = sge->length;
	isge->m = m;
	isge->n = n;
ok:
	trace_rvt_sge_new(isge, sge);
	वापस 1;
bail_unref:
	rvt_put_mr(mr);
bail:
	rcu_पढ़ो_unlock();
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(rvt_lkey_ok);

/**
 * rvt_rkey_ok - check the IB भव address, length, and RKEY
 * @qp: qp क्रम validation
 * @sge: SGE state
 * @len: length of data
 * @vaddr: भव address to place data
 * @rkey: rkey to check
 * @acc: access flags
 *
 * Return: 1 अगर successful, otherwise 0.
 *
 * increments the reference count upon success
 */
पूर्णांक rvt_rkey_ok(काष्ठा rvt_qp *qp, काष्ठा rvt_sge *sge,
		u32 len, u64 vaddr, u32 rkey, पूर्णांक acc)
अणु
	काष्ठा rvt_dev_info *dev = ib_to_rvt(qp->ibqp.device);
	काष्ठा rvt_lkey_table *rkt = &dev->lkey_table;
	काष्ठा rvt_mregion *mr;
	अचिन्हित n, m;
	माप_प्रकार off;

	/*
	 * We use RKEY == zero क्रम kernel भव addresses
	 * (see rvt_get_dma_mr()).
	 */
	rcu_पढ़ो_lock();
	अगर (rkey == 0) अणु
		काष्ठा rvt_pd *pd = ibpd_to_rvtpd(qp->ibqp.pd);
		काष्ठा rvt_dev_info *rdi = ib_to_rvt(pd->ibpd.device);

		अगर (pd->user)
			जाओ bail;
		mr = rcu_dereference(rdi->dma_mr);
		अगर (!mr)
			जाओ bail;
		rvt_get_mr(mr);
		rcu_पढ़ो_unlock();

		sge->mr = mr;
		sge->vaddr = (व्योम *)vaddr;
		sge->length = len;
		sge->sge_length = len;
		sge->m = 0;
		sge->n = 0;
		जाओ ok;
	पूर्ण

	mr = rcu_dereference(rkt->table[rkey >> rkt->shअगरt]);
	अगर (!mr)
		जाओ bail;
	rvt_get_mr(mr);
	/* insure mr पढ़ो is beक्रमe test */
	अगर (!READ_ONCE(mr->lkey_published))
		जाओ bail_unref;
	अगर (unlikely(atomic_पढ़ो(&mr->lkey_invalid) ||
		     mr->lkey != rkey || qp->ibqp.pd != mr->pd))
		जाओ bail_unref;

	off = vaddr - mr->iova;
	अगर (unlikely(vaddr < mr->iova || off + len > mr->length ||
		     (mr->access_flags & acc) == 0))
		जाओ bail_unref;
	rcu_पढ़ो_unlock();

	off += mr->offset;
	अगर (mr->page_shअगरt) अणु
		/*
		 * page sizes are unअगरorm घातer of 2 so no loop is necessary
		 * entries_spanned_by_off is the number of बार the loop below
		 * would have executed.
		*/
		माप_प्रकार entries_spanned_by_off;

		entries_spanned_by_off = off >> mr->page_shअगरt;
		off -= (entries_spanned_by_off << mr->page_shअगरt);
		m = entries_spanned_by_off / RVT_SEGSZ;
		n = entries_spanned_by_off % RVT_SEGSZ;
	पूर्ण अन्यथा अणु
		m = 0;
		n = 0;
		जबतक (off >= mr->map[m]->segs[n].length) अणु
			off -= mr->map[m]->segs[n].length;
			n++;
			अगर (n >= RVT_SEGSZ) अणु
				m++;
				n = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	sge->mr = mr;
	sge->vaddr = mr->map[m]->segs[n].vaddr + off;
	sge->length = mr->map[m]->segs[n].length - off;
	sge->sge_length = len;
	sge->m = m;
	sge->n = n;
ok:
	वापस 1;
bail_unref:
	rvt_put_mr(mr);
bail:
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rvt_rkey_ok);
