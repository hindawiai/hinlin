<शैली गुरु>
/*
 * Copyright (c) 2009-2010 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* Crude resource management */
#समावेश <linux/spinlock.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/ratelimit.h>
#समावेश "iw_cxgb4.h"

अटल पूर्णांक c4iw_init_qid_table(काष्ठा c4iw_rdev *rdev)
अणु
	u32 i;

	अगर (c4iw_id_table_alloc(&rdev->resource.qid_table,
				rdev->lldi.vr->qp.start,
				rdev->lldi.vr->qp.size,
				rdev->lldi.vr->qp.size, 0))
		वापस -ENOMEM;

	क्रम (i = rdev->lldi.vr->qp.start;
		i < rdev->lldi.vr->qp.start + rdev->lldi.vr->qp.size; i++)
		अगर (!(i & rdev->qpmask))
			c4iw_id_मुक्त(&rdev->resource.qid_table, i);
	वापस 0;
पूर्ण

/* nr_* must be घातer of 2 */
पूर्णांक c4iw_init_resource(काष्ठा c4iw_rdev *rdev, u32 nr_tpt,
		       u32 nr_pdid, u32 nr_srqt)
अणु
	पूर्णांक err = 0;
	err = c4iw_id_table_alloc(&rdev->resource.tpt_table, 0, nr_tpt, 1,
					C4IW_ID_TABLE_F_RANDOM);
	अगर (err)
		जाओ tpt_err;
	err = c4iw_init_qid_table(rdev);
	अगर (err)
		जाओ qid_err;
	err = c4iw_id_table_alloc(&rdev->resource.pdid_table, 0,
					nr_pdid, 1, 0);
	अगर (err)
		जाओ pdid_err;
	अगर (!nr_srqt)
		err = c4iw_id_table_alloc(&rdev->resource.srq_table, 0,
					  1, 1, 0);
	अन्यथा
		err = c4iw_id_table_alloc(&rdev->resource.srq_table, 0,
					  nr_srqt, 0, 0);
	अगर (err)
		जाओ srq_err;
	वापस 0;
 srq_err:
	c4iw_id_table_मुक्त(&rdev->resource.pdid_table);
 pdid_err:
	c4iw_id_table_मुक्त(&rdev->resource.qid_table);
 qid_err:
	c4iw_id_table_मुक्त(&rdev->resource.tpt_table);
 tpt_err:
	वापस -ENOMEM;
पूर्ण

/*
 * वापसs 0 अगर no resource available
 */
u32 c4iw_get_resource(काष्ठा c4iw_id_table *id_table)
अणु
	u32 entry;
	entry = c4iw_id_alloc(id_table);
	अगर (entry == (u32)(-1))
		वापस 0;
	वापस entry;
पूर्ण

व्योम c4iw_put_resource(काष्ठा c4iw_id_table *id_table, u32 entry)
अणु
	pr_debug("entry 0x%x\n", entry);
	c4iw_id_मुक्त(id_table, entry);
पूर्ण

u32 c4iw_get_cqid(काष्ठा c4iw_rdev *rdev, काष्ठा c4iw_dev_ucontext *uctx)
अणु
	काष्ठा c4iw_qid_list *entry;
	u32 qid;
	पूर्णांक i;

	mutex_lock(&uctx->lock);
	अगर (!list_empty(&uctx->cqids)) अणु
		entry = list_entry(uctx->cqids.next, काष्ठा c4iw_qid_list,
				   entry);
		list_del(&entry->entry);
		qid = entry->qid;
		kमुक्त(entry);
	पूर्ण अन्यथा अणु
		qid = c4iw_get_resource(&rdev->resource.qid_table);
		अगर (!qid)
			जाओ out;
		mutex_lock(&rdev->stats.lock);
		rdev->stats.qid.cur += rdev->qpmask + 1;
		mutex_unlock(&rdev->stats.lock);
		क्रम (i = qid+1; i & rdev->qpmask; i++) अणु
			entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
			अगर (!entry)
				जाओ out;
			entry->qid = i;
			list_add_tail(&entry->entry, &uctx->cqids);
		पूर्ण

		/*
		 * now put the same ids on the qp list since they all
		 * map to the same db/gts page.
		 */
		entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
		अगर (!entry)
			जाओ out;
		entry->qid = qid;
		list_add_tail(&entry->entry, &uctx->qpids);
		क्रम (i = qid+1; i & rdev->qpmask; i++) अणु
			entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
			अगर (!entry)
				जाओ out;
			entry->qid = i;
			list_add_tail(&entry->entry, &uctx->qpids);
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&uctx->lock);
	pr_debug("qid 0x%x\n", qid);
	mutex_lock(&rdev->stats.lock);
	अगर (rdev->stats.qid.cur > rdev->stats.qid.max)
		rdev->stats.qid.max = rdev->stats.qid.cur;
	mutex_unlock(&rdev->stats.lock);
	वापस qid;
पूर्ण

व्योम c4iw_put_cqid(काष्ठा c4iw_rdev *rdev, u32 qid,
		   काष्ठा c4iw_dev_ucontext *uctx)
अणु
	काष्ठा c4iw_qid_list *entry;

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस;
	pr_debug("qid 0x%x\n", qid);
	entry->qid = qid;
	mutex_lock(&uctx->lock);
	list_add_tail(&entry->entry, &uctx->cqids);
	mutex_unlock(&uctx->lock);
पूर्ण

u32 c4iw_get_qpid(काष्ठा c4iw_rdev *rdev, काष्ठा c4iw_dev_ucontext *uctx)
अणु
	काष्ठा c4iw_qid_list *entry;
	u32 qid;
	पूर्णांक i;

	mutex_lock(&uctx->lock);
	अगर (!list_empty(&uctx->qpids)) अणु
		entry = list_entry(uctx->qpids.next, काष्ठा c4iw_qid_list,
				   entry);
		list_del(&entry->entry);
		qid = entry->qid;
		kमुक्त(entry);
	पूर्ण अन्यथा अणु
		qid = c4iw_get_resource(&rdev->resource.qid_table);
		अगर (!qid) अणु
			mutex_lock(&rdev->stats.lock);
			rdev->stats.qid.fail++;
			mutex_unlock(&rdev->stats.lock);
			जाओ out;
		पूर्ण
		mutex_lock(&rdev->stats.lock);
		rdev->stats.qid.cur += rdev->qpmask + 1;
		mutex_unlock(&rdev->stats.lock);
		क्रम (i = qid+1; i & rdev->qpmask; i++) अणु
			entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
			अगर (!entry)
				जाओ out;
			entry->qid = i;
			list_add_tail(&entry->entry, &uctx->qpids);
		पूर्ण

		/*
		 * now put the same ids on the cq list since they all
		 * map to the same db/gts page.
		 */
		entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
		अगर (!entry)
			जाओ out;
		entry->qid = qid;
		list_add_tail(&entry->entry, &uctx->cqids);
		क्रम (i = qid + 1; i & rdev->qpmask; i++) अणु
			entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
			अगर (!entry)
				जाओ out;
			entry->qid = i;
			list_add_tail(&entry->entry, &uctx->cqids);
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&uctx->lock);
	pr_debug("qid 0x%x\n", qid);
	mutex_lock(&rdev->stats.lock);
	अगर (rdev->stats.qid.cur > rdev->stats.qid.max)
		rdev->stats.qid.max = rdev->stats.qid.cur;
	mutex_unlock(&rdev->stats.lock);
	वापस qid;
पूर्ण

व्योम c4iw_put_qpid(काष्ठा c4iw_rdev *rdev, u32 qid,
		   काष्ठा c4iw_dev_ucontext *uctx)
अणु
	काष्ठा c4iw_qid_list *entry;

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस;
	pr_debug("qid 0x%x\n", qid);
	entry->qid = qid;
	mutex_lock(&uctx->lock);
	list_add_tail(&entry->entry, &uctx->qpids);
	mutex_unlock(&uctx->lock);
पूर्ण

व्योम c4iw_destroy_resource(काष्ठा c4iw_resource *rscp)
अणु
	c4iw_id_table_मुक्त(&rscp->tpt_table);
	c4iw_id_table_मुक्त(&rscp->qid_table);
	c4iw_id_table_मुक्त(&rscp->pdid_table);
पूर्ण

/*
 * PBL Memory Manager.  Uses Linux generic allocator.
 */

#घोषणा MIN_PBL_SHIFT 8			/* 256B == min PBL size (32 entries) */

u32 c4iw_pblpool_alloc(काष्ठा c4iw_rdev *rdev, पूर्णांक size)
अणु
	अचिन्हित दीर्घ addr = gen_pool_alloc(rdev->pbl_pool, size);
	pr_debug("addr 0x%x size %d\n", (u32)addr, size);
	mutex_lock(&rdev->stats.lock);
	अगर (addr) अणु
		rdev->stats.pbl.cur += roundup(size, 1 << MIN_PBL_SHIFT);
		अगर (rdev->stats.pbl.cur > rdev->stats.pbl.max)
			rdev->stats.pbl.max = rdev->stats.pbl.cur;
		kref_get(&rdev->pbl_kref);
	पूर्ण अन्यथा
		rdev->stats.pbl.fail++;
	mutex_unlock(&rdev->stats.lock);
	वापस (u32)addr;
पूर्ण

अटल व्योम destroy_pblpool(काष्ठा kref *kref)
अणु
	काष्ठा c4iw_rdev *rdev;

	rdev = container_of(kref, काष्ठा c4iw_rdev, pbl_kref);
	gen_pool_destroy(rdev->pbl_pool);
	complete(&rdev->pbl_compl);
पूर्ण

व्योम c4iw_pblpool_मुक्त(काष्ठा c4iw_rdev *rdev, u32 addr, पूर्णांक size)
अणु
	pr_debug("addr 0x%x size %d\n", addr, size);
	mutex_lock(&rdev->stats.lock);
	rdev->stats.pbl.cur -= roundup(size, 1 << MIN_PBL_SHIFT);
	mutex_unlock(&rdev->stats.lock);
	gen_pool_मुक्त(rdev->pbl_pool, (अचिन्हित दीर्घ)addr, size);
	kref_put(&rdev->pbl_kref, destroy_pblpool);
पूर्ण

पूर्णांक c4iw_pblpool_create(काष्ठा c4iw_rdev *rdev)
अणु
	अचिन्हित pbl_start, pbl_chunk, pbl_top;

	rdev->pbl_pool = gen_pool_create(MIN_PBL_SHIFT, -1);
	अगर (!rdev->pbl_pool)
		वापस -ENOMEM;

	pbl_start = rdev->lldi.vr->pbl.start;
	pbl_chunk = rdev->lldi.vr->pbl.size;
	pbl_top = pbl_start + pbl_chunk;

	जबतक (pbl_start < pbl_top) अणु
		pbl_chunk = min(pbl_top - pbl_start + 1, pbl_chunk);
		अगर (gen_pool_add(rdev->pbl_pool, pbl_start, pbl_chunk, -1)) अणु
			pr_debug("failed to add PBL chunk (%x/%x)\n",
				 pbl_start, pbl_chunk);
			अगर (pbl_chunk <= 1024 << MIN_PBL_SHIFT) अणु
				pr_warn("Failed to add all PBL chunks (%x/%x)\n",
					pbl_start, pbl_top - pbl_start);
				वापस 0;
			पूर्ण
			pbl_chunk >>= 1;
		पूर्ण अन्यथा अणु
			pr_debug("added PBL chunk (%x/%x)\n",
				 pbl_start, pbl_chunk);
			pbl_start += pbl_chunk;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम c4iw_pblpool_destroy(काष्ठा c4iw_rdev *rdev)
अणु
	kref_put(&rdev->pbl_kref, destroy_pblpool);
पूर्ण

/*
 * RQT Memory Manager.  Uses Linux generic allocator.
 */

#घोषणा MIN_RQT_SHIFT 10	/* 1KB == min RQT size (16 entries) */

u32 c4iw_rqtpool_alloc(काष्ठा c4iw_rdev *rdev, पूर्णांक size)
अणु
	अचिन्हित दीर्घ addr = gen_pool_alloc(rdev->rqt_pool, size << 6);
	pr_debug("addr 0x%x size %d\n", (u32)addr, size << 6);
	अगर (!addr)
		pr_warn_ratelimited("%s: Out of RQT memory\n",
				    pci_name(rdev->lldi.pdev));
	mutex_lock(&rdev->stats.lock);
	अगर (addr) अणु
		rdev->stats.rqt.cur += roundup(size << 6, 1 << MIN_RQT_SHIFT);
		अगर (rdev->stats.rqt.cur > rdev->stats.rqt.max)
			rdev->stats.rqt.max = rdev->stats.rqt.cur;
		kref_get(&rdev->rqt_kref);
	पूर्ण अन्यथा
		rdev->stats.rqt.fail++;
	mutex_unlock(&rdev->stats.lock);
	वापस (u32)addr;
पूर्ण

अटल व्योम destroy_rqtpool(काष्ठा kref *kref)
अणु
	काष्ठा c4iw_rdev *rdev;

	rdev = container_of(kref, काष्ठा c4iw_rdev, rqt_kref);
	gen_pool_destroy(rdev->rqt_pool);
	complete(&rdev->rqt_compl);
पूर्ण

व्योम c4iw_rqtpool_मुक्त(काष्ठा c4iw_rdev *rdev, u32 addr, पूर्णांक size)
अणु
	pr_debug("addr 0x%x size %d\n", addr, size << 6);
	mutex_lock(&rdev->stats.lock);
	rdev->stats.rqt.cur -= roundup(size << 6, 1 << MIN_RQT_SHIFT);
	mutex_unlock(&rdev->stats.lock);
	gen_pool_मुक्त(rdev->rqt_pool, (अचिन्हित दीर्घ)addr, size << 6);
	kref_put(&rdev->rqt_kref, destroy_rqtpool);
पूर्ण

पूर्णांक c4iw_rqtpool_create(काष्ठा c4iw_rdev *rdev)
अणु
	अचिन्हित rqt_start, rqt_chunk, rqt_top;
	पूर्णांक skip = 0;

	rdev->rqt_pool = gen_pool_create(MIN_RQT_SHIFT, -1);
	अगर (!rdev->rqt_pool)
		वापस -ENOMEM;

	/*
	 * If SRQs are supported, then never use the first RQE from
	 * the RQT region. This is because HW uses RQT index 0 as शून्य.
	 */
	अगर (rdev->lldi.vr->srq.size)
		skip = T4_RQT_ENTRY_SIZE;

	rqt_start = rdev->lldi.vr->rq.start + skip;
	rqt_chunk = rdev->lldi.vr->rq.size - skip;
	rqt_top = rqt_start + rqt_chunk;

	जबतक (rqt_start < rqt_top) अणु
		rqt_chunk = min(rqt_top - rqt_start + 1, rqt_chunk);
		अगर (gen_pool_add(rdev->rqt_pool, rqt_start, rqt_chunk, -1)) अणु
			pr_debug("failed to add RQT chunk (%x/%x)\n",
				 rqt_start, rqt_chunk);
			अगर (rqt_chunk <= 1024 << MIN_RQT_SHIFT) अणु
				pr_warn("Failed to add all RQT chunks (%x/%x)\n",
					rqt_start, rqt_top - rqt_start);
				वापस 0;
			पूर्ण
			rqt_chunk >>= 1;
		पूर्ण अन्यथा अणु
			pr_debug("added RQT chunk (%x/%x)\n",
				 rqt_start, rqt_chunk);
			rqt_start += rqt_chunk;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम c4iw_rqtpool_destroy(काष्ठा c4iw_rdev *rdev)
अणु
	kref_put(&rdev->rqt_kref, destroy_rqtpool);
पूर्ण

पूर्णांक c4iw_alloc_srq_idx(काष्ठा c4iw_rdev *rdev)
अणु
	पूर्णांक idx;

	idx = c4iw_id_alloc(&rdev->resource.srq_table);
	mutex_lock(&rdev->stats.lock);
	अगर (idx == -1) अणु
		rdev->stats.srqt.fail++;
		mutex_unlock(&rdev->stats.lock);
		वापस -ENOMEM;
	पूर्ण
	rdev->stats.srqt.cur++;
	अगर (rdev->stats.srqt.cur > rdev->stats.srqt.max)
		rdev->stats.srqt.max = rdev->stats.srqt.cur;
	mutex_unlock(&rdev->stats.lock);
	वापस idx;
पूर्ण

व्योम c4iw_मुक्त_srq_idx(काष्ठा c4iw_rdev *rdev, पूर्णांक idx)
अणु
	c4iw_id_मुक्त(&rdev->resource.srq_table, idx);
	mutex_lock(&rdev->stats.lock);
	rdev->stats.srqt.cur--;
	mutex_unlock(&rdev->stats.lock);
पूर्ण

/*
 * On-Chip QP Memory.
 */
#घोषणा MIN_OCQP_SHIFT 12	/* 4KB == min ocqp size */

u32 c4iw_ocqp_pool_alloc(काष्ठा c4iw_rdev *rdev, पूर्णांक size)
अणु
	अचिन्हित दीर्घ addr = gen_pool_alloc(rdev->ocqp_pool, size);
	pr_debug("addr 0x%x size %d\n", (u32)addr, size);
	अगर (addr) अणु
		mutex_lock(&rdev->stats.lock);
		rdev->stats.ocqp.cur += roundup(size, 1 << MIN_OCQP_SHIFT);
		अगर (rdev->stats.ocqp.cur > rdev->stats.ocqp.max)
			rdev->stats.ocqp.max = rdev->stats.ocqp.cur;
		mutex_unlock(&rdev->stats.lock);
	पूर्ण
	वापस (u32)addr;
पूर्ण

व्योम c4iw_ocqp_pool_मुक्त(काष्ठा c4iw_rdev *rdev, u32 addr, पूर्णांक size)
अणु
	pr_debug("addr 0x%x size %d\n", addr, size);
	mutex_lock(&rdev->stats.lock);
	rdev->stats.ocqp.cur -= roundup(size, 1 << MIN_OCQP_SHIFT);
	mutex_unlock(&rdev->stats.lock);
	gen_pool_मुक्त(rdev->ocqp_pool, (अचिन्हित दीर्घ)addr, size);
पूर्ण

पूर्णांक c4iw_ocqp_pool_create(काष्ठा c4iw_rdev *rdev)
अणु
	अचिन्हित start, chunk, top;

	rdev->ocqp_pool = gen_pool_create(MIN_OCQP_SHIFT, -1);
	अगर (!rdev->ocqp_pool)
		वापस -ENOMEM;

	start = rdev->lldi.vr->ocq.start;
	chunk = rdev->lldi.vr->ocq.size;
	top = start + chunk;

	जबतक (start < top) अणु
		chunk = min(top - start + 1, chunk);
		अगर (gen_pool_add(rdev->ocqp_pool, start, chunk, -1)) अणु
			pr_debug("failed to add OCQP chunk (%x/%x)\n",
				 start, chunk);
			अगर (chunk <= 1024 << MIN_OCQP_SHIFT) अणु
				pr_warn("Failed to add all OCQP chunks (%x/%x)\n",
					start, top - start);
				वापस 0;
			पूर्ण
			chunk >>= 1;
		पूर्ण अन्यथा अणु
			pr_debug("added OCQP chunk (%x/%x)\n",
				 start, chunk);
			start += chunk;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम c4iw_ocqp_pool_destroy(काष्ठा c4iw_rdev *rdev)
अणु
	gen_pool_destroy(rdev->ocqp_pool);
पूर्ण
