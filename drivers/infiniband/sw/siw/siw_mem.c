<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/* Copyright (c) 2008-2019, IBM Corporation */

#समावेश <linux/gfp.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/resource.h>

#समावेश "siw.h"
#समावेश "siw_mem.h"

/*
 * Stag lookup is based on its index part only (24 bits).
 * The code aव्योमs special Stag of zero and tries to अक्रमomize
 * STag values between 1 and SIW_STAG_MAX_INDEX.
 */
पूर्णांक siw_mem_add(काष्ठा siw_device *sdev, काष्ठा siw_mem *m)
अणु
	काष्ठा xa_limit limit = XA_LIMIT(1, 0x00ffffff);
	u32 id, next;

	get_अक्रमom_bytes(&next, 4);
	next &= 0x00ffffff;

	अगर (xa_alloc_cyclic(&sdev->mem_xa, &id, m, limit, &next,
	    GFP_KERNEL) < 0)
		वापस -ENOMEM;

	/* Set the STag index part */
	m->stag = id << 8;

	siw_dbg_mem(m, "new MEM object\n");

	वापस 0;
पूर्ण

/*
 * siw_mem_id2obj()
 *
 * resolves memory from stag given by id. might be called from:
 * o process context beक्रमe sending out of sgl, or
 * o in softirq when resolving target memory
 */
काष्ठा siw_mem *siw_mem_id2obj(काष्ठा siw_device *sdev, पूर्णांक stag_index)
अणु
	काष्ठा siw_mem *mem;

	rcu_पढ़ो_lock();
	mem = xa_load(&sdev->mem_xa, stag_index);
	अगर (likely(mem && kref_get_unless_zero(&mem->ref))) अणु
		rcu_पढ़ो_unlock();
		वापस mem;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

अटल व्योम siw_मुक्त_plist(काष्ठा siw_page_chunk *chunk, पूर्णांक num_pages,
			   bool dirty)
अणु
	unpin_user_pages_dirty_lock(chunk->plist, num_pages, dirty);
पूर्ण

व्योम siw_umem_release(काष्ठा siw_umem *umem, bool dirty)
अणु
	काष्ठा mm_काष्ठा *mm_s = umem->owning_mm;
	पूर्णांक i, num_pages = umem->num_pages;

	क्रम (i = 0; num_pages; i++) अणु
		पूर्णांक to_मुक्त = min_t(पूर्णांक, PAGES_PER_CHUNK, num_pages);

		siw_मुक्त_plist(&umem->page_chunk[i], to_मुक्त,
			       umem->writable && dirty);
		kमुक्त(umem->page_chunk[i].plist);
		num_pages -= to_मुक्त;
	पूर्ण
	atomic64_sub(umem->num_pages, &mm_s->pinned_vm);

	mmdrop(mm_s);
	kमुक्त(umem->page_chunk);
	kमुक्त(umem);
पूर्ण

पूर्णांक siw_mr_add_mem(काष्ठा siw_mr *mr, काष्ठा ib_pd *pd, व्योम *mem_obj,
		   u64 start, u64 len, पूर्णांक rights)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(pd->device);
	काष्ठा siw_mem *mem = kzalloc(माप(*mem), GFP_KERNEL);
	काष्ठा xa_limit limit = XA_LIMIT(1, 0x00ffffff);
	u32 id, next;

	अगर (!mem)
		वापस -ENOMEM;

	mem->mem_obj = mem_obj;
	mem->stag_valid = 0;
	mem->sdev = sdev;
	mem->va = start;
	mem->len = len;
	mem->pd = pd;
	mem->perms = rights & IWARP_ACCESS_MASK;
	kref_init(&mem->ref);

	get_अक्रमom_bytes(&next, 4);
	next &= 0x00ffffff;

	अगर (xa_alloc_cyclic(&sdev->mem_xa, &id, mem, limit, &next,
	    GFP_KERNEL) < 0) अणु
		kमुक्त(mem);
		वापस -ENOMEM;
	पूर्ण

	mr->mem = mem;
	/* Set the STag index part */
	mem->stag = id << 8;
	mr->base_mr.lkey = mr->base_mr.rkey = mem->stag;

	वापस 0;
पूर्ण

व्योम siw_mr_drop_mem(काष्ठा siw_mr *mr)
अणु
	काष्ठा siw_mem *mem = mr->mem, *found;

	mem->stag_valid = 0;

	/* make STag invalid visible asap */
	smp_mb();

	found = xa_erase(&mem->sdev->mem_xa, mem->stag >> 8);
	WARN_ON(found != mem);
	siw_mem_put(mem);
पूर्ण

व्योम siw_मुक्त_mem(काष्ठा kref *ref)
अणु
	काष्ठा siw_mem *mem = container_of(ref, काष्ठा siw_mem, ref);

	siw_dbg_mem(mem, "free mem, pbl: %s\n", mem->is_pbl ? "y" : "n");

	अगर (!mem->is_mw && mem->mem_obj) अणु
		अगर (mem->is_pbl == 0)
			siw_umem_release(mem->umem, true);
		अन्यथा
			kमुक्त(mem->pbl);
	पूर्ण
	kमुक्त(mem);
पूर्ण

/*
 * siw_check_mem()
 *
 * Check protection करोमुख्य, STAG state, access permissions and
 * address range क्रम memory object.
 *
 * @pd:		Protection Doमुख्य memory should beदीर्घ to
 * @mem:	memory to be checked
 * @addr:	starting addr of mem
 * @perms:	requested access permissions
 * @len:	len of memory पूर्णांकerval to be checked
 *
 */
पूर्णांक siw_check_mem(काष्ठा ib_pd *pd, काष्ठा siw_mem *mem, u64 addr,
		  क्रमागत ib_access_flags perms, पूर्णांक len)
अणु
	अगर (!mem->stag_valid) अणु
		siw_dbg_pd(pd, "STag 0x%08x invalid\n", mem->stag);
		वापस -E_STAG_INVALID;
	पूर्ण
	अगर (mem->pd != pd) अणु
		siw_dbg_pd(pd, "STag 0x%08x: PD mismatch\n", mem->stag);
		वापस -E_PD_MISMATCH;
	पूर्ण
	/*
	 * check access permissions
	 */
	अगर ((mem->perms & perms) < perms) अणु
		siw_dbg_pd(pd, "permissions 0x%08x < 0x%08x\n",
			   mem->perms, perms);
		वापस -E_ACCESS_PERM;
	पूर्ण
	/*
	 * Check अगर access falls पूर्णांकo valid memory पूर्णांकerval.
	 */
	अगर (addr < mem->va || addr + len > mem->va + mem->len) अणु
		siw_dbg_pd(pd, "MEM interval len %d\n", len);
		siw_dbg_pd(pd, "[0x%pK, 0x%pK] out of bounds\n",
			   (व्योम *)(uपूर्णांकptr_t)addr,
			   (व्योम *)(uपूर्णांकptr_t)(addr + len));
		siw_dbg_pd(pd, "[0x%pK, 0x%pK] STag=0x%08x\n",
			   (व्योम *)(uपूर्णांकptr_t)mem->va,
			   (व्योम *)(uपूर्णांकptr_t)(mem->va + mem->len),
			   mem->stag);

		वापस -E_BASE_BOUNDS;
	पूर्ण
	वापस E_ACCESS_OK;
पूर्ण

/*
 * siw_check_sge()
 *
 * Check SGE क्रम access rights in given पूर्णांकerval
 *
 * @pd:		Protection Doमुख्य memory should beदीर्घ to
 * @sge:	SGE to be checked
 * @mem:	location of memory reference within array
 * @perms:	requested access permissions
 * @off:	starting offset in SGE
 * @len:	len of memory पूर्णांकerval to be checked
 *
 * NOTE: Function references SGE's memory object (mem->obj)
 * अगर not yet करोne. New reference is kept अगर check went ok and
 * released अगर check failed. If mem->obj is alपढ़ोy valid, no new
 * lookup is being करोne and mem is not released it check fails.
 */
पूर्णांक siw_check_sge(काष्ठा ib_pd *pd, काष्ठा siw_sge *sge, काष्ठा siw_mem *mem[],
		  क्रमागत ib_access_flags perms, u32 off, पूर्णांक len)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(pd->device);
	काष्ठा siw_mem *new = शून्य;
	पूर्णांक rv = E_ACCESS_OK;

	अगर (len + off > sge->length) अणु
		rv = -E_BASE_BOUNDS;
		जाओ fail;
	पूर्ण
	अगर (*mem == शून्य) अणु
		new = siw_mem_id2obj(sdev, sge->lkey >> 8);
		अगर (unlikely(!new)) अणु
			siw_dbg_pd(pd, "STag unknown: 0x%08x\n", sge->lkey);
			rv = -E_STAG_INVALID;
			जाओ fail;
		पूर्ण
		*mem = new;
	पूर्ण
	/* Check अगर user re-रेजिस्टरed with dअगरferent STag key */
	अगर (unlikely((*mem)->stag != sge->lkey)) अणु
		siw_dbg_mem((*mem), "STag mismatch: 0x%08x\n", sge->lkey);
		rv = -E_STAG_INVALID;
		जाओ fail;
	पूर्ण
	rv = siw_check_mem(pd, *mem, sge->laddr + off, perms, len);
	अगर (unlikely(rv))
		जाओ fail;

	वापस 0;

fail:
	अगर (new) अणु
		*mem = शून्य;
		siw_mem_put(new);
	पूर्ण
	वापस rv;
पूर्ण

व्योम siw_wqe_put_mem(काष्ठा siw_wqe *wqe, क्रमागत siw_opcode op)
अणु
	चयन (op) अणु
	हाल SIW_OP_SEND:
	हाल SIW_OP_WRITE:
	हाल SIW_OP_SEND_WITH_IMM:
	हाल SIW_OP_SEND_REMOTE_INV:
	हाल SIW_OP_READ:
	हाल SIW_OP_READ_LOCAL_INV:
		अगर (!(wqe->sqe.flags & SIW_WQE_INLINE))
			siw_unref_mem_sgl(wqe->mem, wqe->sqe.num_sge);
		अवरोध;

	हाल SIW_OP_RECEIVE:
		siw_unref_mem_sgl(wqe->mem, wqe->rqe.num_sge);
		अवरोध;

	हाल SIW_OP_READ_RESPONSE:
		siw_unref_mem_sgl(wqe->mem, 1);
		अवरोध;

	शेष:
		/*
		 * SIW_OP_INVAL_STAG and SIW_OP_REG_MR
		 * करो not hold memory references
		 */
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक siw_invalidate_stag(काष्ठा ib_pd *pd, u32 stag)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(pd->device);
	काष्ठा siw_mem *mem = siw_mem_id2obj(sdev, stag >> 8);
	पूर्णांक rv = 0;

	अगर (unlikely(!mem)) अणु
		siw_dbg_pd(pd, "STag 0x%08x unknown\n", stag);
		वापस -EINVAL;
	पूर्ण
	अगर (unlikely(mem->pd != pd)) अणु
		siw_dbg_pd(pd, "PD mismatch for STag 0x%08x\n", stag);
		rv = -EACCES;
		जाओ out;
	पूर्ण
	/*
	 * Per RDMA verbs definition, an STag may alपढ़ोy be in invalid
	 * state अगर invalidation is requested. So no state check here.
	 */
	mem->stag_valid = 0;

	siw_dbg_pd(pd, "STag 0x%08x now invalid\n", stag);
out:
	siw_mem_put(mem);
	वापस rv;
पूर्ण

/*
 * Gets physical address backed by PBL element. Address is referenced
 * by linear byte offset पूर्णांकo list of variably sized PB elements.
 * Optionally, provides reमुख्यing len within current element, and
 * current PBL index क्रम later resume at same element.
 */
dma_addr_t siw_pbl_get_buffer(काष्ठा siw_pbl *pbl, u64 off, पूर्णांक *len, पूर्णांक *idx)
अणु
	पूर्णांक i = idx ? *idx : 0;

	जबतक (i < pbl->num_buf) अणु
		काष्ठा siw_pble *pble = &pbl->pbe[i];

		अगर (pble->pbl_off + pble->size > off) अणु
			u64 pble_off = off - pble->pbl_off;

			अगर (len)
				*len = pble->size - pble_off;
			अगर (idx)
				*idx = i;

			वापस pble->addr + pble_off;
		पूर्ण
		i++;
	पूर्ण
	अगर (len)
		*len = 0;
	वापस 0;
पूर्ण

काष्ठा siw_pbl *siw_pbl_alloc(u32 num_buf)
अणु
	काष्ठा siw_pbl *pbl;

	अगर (num_buf == 0)
		वापस ERR_PTR(-EINVAL);

	pbl = kzalloc(काष्ठा_size(pbl, pbe, num_buf), GFP_KERNEL);
	अगर (!pbl)
		वापस ERR_PTR(-ENOMEM);

	pbl->max_buf = num_buf;

	वापस pbl;
पूर्ण

काष्ठा siw_umem *siw_umem_get(u64 start, u64 len, bool writable)
अणु
	काष्ठा siw_umem *umem;
	काष्ठा mm_काष्ठा *mm_s;
	u64 first_page_va;
	अचिन्हित दीर्घ mlock_limit;
	अचिन्हित पूर्णांक foll_flags = FOLL_WRITE;
	पूर्णांक num_pages, num_chunks, i, rv = 0;

	अगर (!can_करो_mlock())
		वापस ERR_PTR(-EPERM);

	अगर (!len)
		वापस ERR_PTR(-EINVAL);

	first_page_va = start & PAGE_MASK;
	num_pages = PAGE_ALIGN(start + len - first_page_va) >> PAGE_SHIFT;
	num_chunks = (num_pages >> CHUNK_SHIFT) + 1;

	umem = kzalloc(माप(*umem), GFP_KERNEL);
	अगर (!umem)
		वापस ERR_PTR(-ENOMEM);

	mm_s = current->mm;
	umem->owning_mm = mm_s;
	umem->writable = writable;

	mmgrab(mm_s);

	अगर (!writable)
		foll_flags |= FOLL_FORCE;

	mmap_पढ़ो_lock(mm_s);

	mlock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;

	अगर (num_pages + atomic64_पढ़ो(&mm_s->pinned_vm) > mlock_limit) अणु
		rv = -ENOMEM;
		जाओ out_sem_up;
	पूर्ण
	umem->fp_addr = first_page_va;

	umem->page_chunk =
		kसुस्मृति(num_chunks, माप(काष्ठा siw_page_chunk), GFP_KERNEL);
	अगर (!umem->page_chunk) अणु
		rv = -ENOMEM;
		जाओ out_sem_up;
	पूर्ण
	क्रम (i = 0; num_pages; i++) अणु
		पूर्णांक got, nents = min_t(पूर्णांक, num_pages, PAGES_PER_CHUNK);

		umem->page_chunk[i].plist =
			kसुस्मृति(nents, माप(काष्ठा page *), GFP_KERNEL);
		अगर (!umem->page_chunk[i].plist) अणु
			rv = -ENOMEM;
			जाओ out_sem_up;
		पूर्ण
		got = 0;
		जबतक (nents) अणु
			काष्ठा page **plist = &umem->page_chunk[i].plist[got];

			rv = pin_user_pages(first_page_va, nents,
					    foll_flags | FOLL_LONGTERM,
					    plist, शून्य);
			अगर (rv < 0)
				जाओ out_sem_up;

			umem->num_pages += rv;
			atomic64_add(rv, &mm_s->pinned_vm);
			first_page_va += rv * PAGE_SIZE;
			nents -= rv;
			got += rv;
		पूर्ण
		num_pages -= got;
	पूर्ण
out_sem_up:
	mmap_पढ़ो_unlock(mm_s);

	अगर (rv > 0)
		वापस umem;

	siw_umem_release(umem, false);

	वापस ERR_PTR(rv);
पूर्ण
