<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* XDP user-space packet buffer
 * Copyright(c) 2018 Intel Corporation.
 */

#समावेश <linux/init.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/bpf.h>
#समावेश <linux/mm.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/idr.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "xdp_umem.h"
#समावेश "xsk_queue.h"

#घोषणा XDP_UMEM_MIN_CHUNK_SIZE 2048

अटल DEFINE_IDA(umem_ida);

अटल व्योम xdp_umem_unpin_pages(काष्ठा xdp_umem *umem)
अणु
	unpin_user_pages_dirty_lock(umem->pgs, umem->npgs, true);

	kमुक्त(umem->pgs);
	umem->pgs = शून्य;
पूर्ण

अटल व्योम xdp_umem_unaccount_pages(काष्ठा xdp_umem *umem)
अणु
	अगर (umem->user) अणु
		atomic_दीर्घ_sub(umem->npgs, &umem->user->locked_vm);
		मुक्त_uid(umem->user);
	पूर्ण
पूर्ण

अटल व्योम xdp_umem_addr_unmap(काष्ठा xdp_umem *umem)
अणु
	vunmap(umem->addrs);
	umem->addrs = शून्य;
पूर्ण

अटल पूर्णांक xdp_umem_addr_map(काष्ठा xdp_umem *umem, काष्ठा page **pages,
			     u32 nr_pages)
अणु
	umem->addrs = vmap(pages, nr_pages, VM_MAP, PAGE_KERNEL);
	अगर (!umem->addrs)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम xdp_umem_release(काष्ठा xdp_umem *umem)
अणु
	umem->zc = false;
	ida_simple_हटाओ(&umem_ida, umem->id);

	xdp_umem_addr_unmap(umem);
	xdp_umem_unpin_pages(umem);

	xdp_umem_unaccount_pages(umem);
	kमुक्त(umem);
पूर्ण

अटल व्योम xdp_umem_release_deferred(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xdp_umem *umem = container_of(work, काष्ठा xdp_umem, work);

	xdp_umem_release(umem);
पूर्ण

व्योम xdp_get_umem(काष्ठा xdp_umem *umem)
अणु
	refcount_inc(&umem->users);
पूर्ण

व्योम xdp_put_umem(काष्ठा xdp_umem *umem, bool defer_cleanup)
अणु
	अगर (!umem)
		वापस;

	अगर (refcount_dec_and_test(&umem->users)) अणु
		अगर (defer_cleanup) अणु
			INIT_WORK(&umem->work, xdp_umem_release_deferred);
			schedule_work(&umem->work);
		पूर्ण अन्यथा अणु
			xdp_umem_release(umem);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक xdp_umem_pin_pages(काष्ठा xdp_umem *umem, अचिन्हित दीर्घ address)
अणु
	अचिन्हित पूर्णांक gup_flags = FOLL_WRITE;
	दीर्घ npgs;
	पूर्णांक err;

	umem->pgs = kसुस्मृति(umem->npgs, माप(*umem->pgs),
			    GFP_KERNEL | __GFP_NOWARN);
	अगर (!umem->pgs)
		वापस -ENOMEM;

	mmap_पढ़ो_lock(current->mm);
	npgs = pin_user_pages(address, umem->npgs,
			      gup_flags | FOLL_LONGTERM, &umem->pgs[0], शून्य);
	mmap_पढ़ो_unlock(current->mm);

	अगर (npgs != umem->npgs) अणु
		अगर (npgs >= 0) अणु
			umem->npgs = npgs;
			err = -ENOMEM;
			जाओ out_pin;
		पूर्ण
		err = npgs;
		जाओ out_pgs;
	पूर्ण
	वापस 0;

out_pin:
	xdp_umem_unpin_pages(umem);
out_pgs:
	kमुक्त(umem->pgs);
	umem->pgs = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक xdp_umem_account_pages(काष्ठा xdp_umem *umem)
अणु
	अचिन्हित दीर्घ lock_limit, new_npgs, old_npgs;

	अगर (capable(CAP_IPC_LOCK))
		वापस 0;

	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	umem->user = get_uid(current_user());

	करो अणु
		old_npgs = atomic_दीर्घ_पढ़ो(&umem->user->locked_vm);
		new_npgs = old_npgs + umem->npgs;
		अगर (new_npgs > lock_limit) अणु
			मुक्त_uid(umem->user);
			umem->user = शून्य;
			वापस -ENOBUFS;
		पूर्ण
	पूर्ण जबतक (atomic_दीर्घ_cmpxchg(&umem->user->locked_vm, old_npgs,
				     new_npgs) != old_npgs);
	वापस 0;
पूर्ण

अटल पूर्णांक xdp_umem_reg(काष्ठा xdp_umem *umem, काष्ठा xdp_umem_reg *mr)
अणु
	u32 npgs_rem, chunk_size = mr->chunk_size, headroom = mr->headroom;
	bool unaligned_chunks = mr->flags & XDP_UMEM_UNALIGNED_CHUNK_FLAG;
	u64 npgs, addr = mr->addr, size = mr->len;
	अचिन्हित पूर्णांक chunks, chunks_rem;
	पूर्णांक err;

	अगर (chunk_size < XDP_UMEM_MIN_CHUNK_SIZE || chunk_size > PAGE_SIZE) अणु
		/* Strictly speaking we could support this, अगर:
		 * - huge pages, or*
		 * - using an IOMMU, or
		 * - making sure the memory area is consecutive
		 * but क्रम now, we simply say "computer says no".
		 */
		वापस -EINVAL;
	पूर्ण

	अगर (mr->flags & ~XDP_UMEM_UNALIGNED_CHUNK_FLAG)
		वापस -EINVAL;

	अगर (!unaligned_chunks && !is_घातer_of_2(chunk_size))
		वापस -EINVAL;

	अगर (!PAGE_ALIGNED(addr)) अणु
		/* Memory area has to be page size aligned. For
		 * simplicity, this might change.
		 */
		वापस -EINVAL;
	पूर्ण

	अगर ((addr + size) < addr)
		वापस -EINVAL;

	npgs = भाग_u64_rem(size, PAGE_SIZE, &npgs_rem);
	अगर (npgs_rem)
		npgs++;
	अगर (npgs > U32_MAX)
		वापस -EINVAL;

	chunks = (अचिन्हित पूर्णांक)भाग_u64_rem(size, chunk_size, &chunks_rem);
	अगर (chunks == 0)
		वापस -EINVAL;

	अगर (!unaligned_chunks && chunks_rem)
		वापस -EINVAL;

	अगर (headroom >= chunk_size - XDP_PACKET_HEADROOM)
		वापस -EINVAL;

	umem->size = size;
	umem->headroom = headroom;
	umem->chunk_size = chunk_size;
	umem->chunks = chunks;
	umem->npgs = (u32)npgs;
	umem->pgs = शून्य;
	umem->user = शून्य;
	umem->flags = mr->flags;

	INIT_LIST_HEAD(&umem->xsk_dma_list);
	refcount_set(&umem->users, 1);

	err = xdp_umem_account_pages(umem);
	अगर (err)
		वापस err;

	err = xdp_umem_pin_pages(umem, (अचिन्हित दीर्घ)addr);
	अगर (err)
		जाओ out_account;

	err = xdp_umem_addr_map(umem, umem->pgs, umem->npgs);
	अगर (err)
		जाओ out_unpin;

	वापस 0;

out_unpin:
	xdp_umem_unpin_pages(umem);
out_account:
	xdp_umem_unaccount_pages(umem);
	वापस err;
पूर्ण

काष्ठा xdp_umem *xdp_umem_create(काष्ठा xdp_umem_reg *mr)
अणु
	काष्ठा xdp_umem *umem;
	पूर्णांक err;

	umem = kzalloc(माप(*umem), GFP_KERNEL);
	अगर (!umem)
		वापस ERR_PTR(-ENOMEM);

	err = ida_simple_get(&umem_ida, 0, 0, GFP_KERNEL);
	अगर (err < 0) अणु
		kमुक्त(umem);
		वापस ERR_PTR(err);
	पूर्ण
	umem->id = err;

	err = xdp_umem_reg(umem, mr);
	अगर (err) अणु
		ida_simple_हटाओ(&umem_ida, umem->id);
		kमुक्त(umem);
		वापस ERR_PTR(err);
	पूर्ण

	वापस umem;
पूर्ण
