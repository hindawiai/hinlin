<शैली गुरु>
/*
 *	An async IO implementation क्रम Linux
 *	Written by Benjamin LaHaise <bcrl@kvack.org>
 *
 *	Implements an efficient asynchronous io पूर्णांकerface.
 *
 *	Copyright 2000, 2001, 2002 Red Hat, Inc.  All Rights Reserved.
 *	Copyright 2018 Christoph Hellwig.
 *
 *	See ../COPYING क्रम licensing terms.
 */
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/aio_abi.h>
#समावेश <linux/export.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/refcount.h>
#समावेश <linux/uपन.स>

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/aपन.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/security.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/compat.h>
#समावेश <linux/migrate.h>
#समावेश <linux/ramfs.h>
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/nospec.h>

#समावेश "internal.h"

#घोषणा KIOCB_KEY		0

#घोषणा AIO_RING_MAGIC			0xa10a10a1
#घोषणा AIO_RING_COMPAT_FEATURES	1
#घोषणा AIO_RING_INCOMPAT_FEATURES	0
काष्ठा aio_ring अणु
	अचिन्हित	id;	/* kernel पूर्णांकernal index number */
	अचिन्हित	nr;	/* number of io_events */
	अचिन्हित	head;	/* Written to by userland or under ring_lock
				 * mutex by aio_पढ़ो_events_ring(). */
	अचिन्हित	tail;

	अचिन्हित	magic;
	अचिन्हित	compat_features;
	अचिन्हित	incompat_features;
	अचिन्हित	header_length;	/* size of aio_ring */


	काष्ठा io_event		io_events[];
पूर्ण; /* 128 bytes + ring size */

/*
 * Plugging is meant to work with larger batches of IOs. If we करोn't
 * have more than the below, then करोn't bother setting up a plug.
 */
#घोषणा AIO_PLUG_THRESHOLD	2

#घोषणा AIO_RING_PAGES	8

काष्ठा kioctx_table अणु
	काष्ठा rcu_head		rcu;
	अचिन्हित		nr;
	काष्ठा kioctx __rcu	*table[];
पूर्ण;

काष्ठा kioctx_cpu अणु
	अचिन्हित		reqs_available;
पूर्ण;

काष्ठा ctx_rq_रुको अणु
	काष्ठा completion comp;
	atomic_t count;
पूर्ण;

काष्ठा kioctx अणु
	काष्ठा percpu_ref	users;
	atomic_t		dead;

	काष्ठा percpu_ref	reqs;

	अचिन्हित दीर्घ		user_id;

	काष्ठा __percpu kioctx_cpu *cpu;

	/*
	 * For percpu reqs_available, number of slots we move to/from global
	 * counter at a समय:
	 */
	अचिन्हित		req_batch;
	/*
	 * This is what userspace passed to io_setup(), it's not used क्रम
	 * anything but counting against the global max_reqs quota.
	 *
	 * The real limit is nr_events - 1, which will be larger (see
	 * aio_setup_ring())
	 */
	अचिन्हित		max_reqs;

	/* Size of ringbuffer, in units of काष्ठा io_event */
	अचिन्हित		nr_events;

	अचिन्हित दीर्घ		mmap_base;
	अचिन्हित दीर्घ		mmap_size;

	काष्ठा page		**ring_pages;
	दीर्घ			nr_pages;

	काष्ठा rcu_work		मुक्त_rwork;	/* see मुक्त_ioctx() */

	/*
	 * संकेतs when all in-flight requests are करोne
	 */
	काष्ठा ctx_rq_रुको	*rq_रुको;

	काष्ठा अणु
		/*
		 * This counts the number of available slots in the ringbuffer,
		 * so we aव्योम overflowing it: it's decremented (अगर positive)
		 * when allocating a kiocb and incremented when the resulting
		 * io_event is pulled off the ringbuffer.
		 *
		 * We batch accesses to it with a percpu version.
		 */
		atomic_t	reqs_available;
	पूर्ण ____cacheline_aligned_in_smp;

	काष्ठा अणु
		spinlock_t	ctx_lock;
		काष्ठा list_head active_reqs;	/* used क्रम cancellation */
	पूर्ण ____cacheline_aligned_in_smp;

	काष्ठा अणु
		काष्ठा mutex	ring_lock;
		रुको_queue_head_t रुको;
	पूर्ण ____cacheline_aligned_in_smp;

	काष्ठा अणु
		अचिन्हित	tail;
		अचिन्हित	completed_events;
		spinlock_t	completion_lock;
	पूर्ण ____cacheline_aligned_in_smp;

	काष्ठा page		*पूर्णांकernal_pages[AIO_RING_PAGES];
	काष्ठा file		*aio_ring_file;

	अचिन्हित		id;
पूर्ण;

/*
 * First field must be the file poपूर्णांकer in all the
 * iocb जोड़s! See also 'struct kiocb' in <linux/fs.h>
 */
काष्ठा fsync_iocb अणु
	काष्ठा file		*file;
	काष्ठा work_काष्ठा	work;
	bool			datasync;
	काष्ठा cred		*creds;
पूर्ण;

काष्ठा poll_iocb अणु
	काष्ठा file		*file;
	काष्ठा रुको_queue_head	*head;
	__poll_t		events;
	bool			करोne;
	bool			cancelled;
	काष्ठा रुको_queue_entry	रुको;
	काष्ठा work_काष्ठा	work;
पूर्ण;

/*
 * NOTE! Each of the iocb जोड़ members has the file poपूर्णांकer
 * as the first entry in their काष्ठा definition. So you can
 * access the file poपूर्णांकer through any of the sub-काष्ठाs,
 * or directly as just 'ki_filp' in this काष्ठा.
 */
काष्ठा aio_kiocb अणु
	जोड़ अणु
		काष्ठा file		*ki_filp;
		काष्ठा kiocb		rw;
		काष्ठा fsync_iocb	fsync;
		काष्ठा poll_iocb	poll;
	पूर्ण;

	काष्ठा kioctx		*ki_ctx;
	kiocb_cancel_fn		*ki_cancel;

	काष्ठा io_event		ki_res;

	काष्ठा list_head	ki_list;	/* the aio core uses this
						 * क्रम cancellation */
	refcount_t		ki_refcnt;

	/*
	 * If the aio_resfd field of the userspace iocb is not zero,
	 * this is the underlying eventfd context to deliver events to.
	 */
	काष्ठा eventfd_ctx	*ki_eventfd;
पूर्ण;

/*------ sysctl variables----*/
अटल DEFINE_SPINLOCK(aio_nr_lock);
अचिन्हित दीर्घ aio_nr;		/* current प्रणाली wide number of aio requests */
अचिन्हित दीर्घ aio_max_nr = 0x10000; /* प्रणाली wide maximum number of aio requests */
/*----end sysctl variables---*/

अटल काष्ठा kmem_cache	*kiocb_cachep;
अटल काष्ठा kmem_cache	*kioctx_cachep;

अटल काष्ठा vfsmount *aio_mnt;

अटल स्थिर काष्ठा file_operations aio_ring_fops;
अटल स्थिर काष्ठा address_space_operations aio_ctx_aops;

अटल काष्ठा file *aio_निजी_file(काष्ठा kioctx *ctx, loff_t nr_pages)
अणु
	काष्ठा file *file;
	काष्ठा inode *inode = alloc_anon_inode(aio_mnt->mnt_sb);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	inode->i_mapping->a_ops = &aio_ctx_aops;
	inode->i_mapping->निजी_data = ctx;
	inode->i_size = PAGE_SIZE * nr_pages;

	file = alloc_file_pseuकरो(inode, aio_mnt, "[aio]",
				O_RDWR, &aio_ring_fops);
	अगर (IS_ERR(file))
		iput(inode);
	वापस file;
पूर्ण

अटल पूर्णांक aio_init_fs_context(काष्ठा fs_context *fc)
अणु
	अगर (!init_pseuकरो(fc, AIO_RING_MAGIC))
		वापस -ENOMEM;
	fc->s_अगरlags |= SB_I_NOEXEC;
	वापस 0;
पूर्ण

/* aio_setup
 *	Creates the slab caches used by the aio routines, panic on
 *	failure as this is करोne early during the boot sequence.
 */
अटल पूर्णांक __init aio_setup(व्योम)
अणु
	अटल काष्ठा file_प्रणाली_type aio_fs = अणु
		.name		= "aio",
		.init_fs_context = aio_init_fs_context,
		.समाप्त_sb	= समाप्त_anon_super,
	पूर्ण;
	aio_mnt = kern_mount(&aio_fs);
	अगर (IS_ERR(aio_mnt))
		panic("Failed to create aio fs mount.");

	kiocb_cachep = KMEM_CACHE(aio_kiocb, SLAB_HWCACHE_ALIGN|SLAB_PANIC);
	kioctx_cachep = KMEM_CACHE(kioctx,SLAB_HWCACHE_ALIGN|SLAB_PANIC);
	वापस 0;
पूर्ण
__initcall(aio_setup);

अटल व्योम put_aio_ring_file(काष्ठा kioctx *ctx)
अणु
	काष्ठा file *aio_ring_file = ctx->aio_ring_file;
	काष्ठा address_space *i_mapping;

	अगर (aio_ring_file) अणु
		truncate_setsize(file_inode(aio_ring_file), 0);

		/* Prevent further access to the kioctx from migratepages */
		i_mapping = aio_ring_file->f_mapping;
		spin_lock(&i_mapping->निजी_lock);
		i_mapping->निजी_data = शून्य;
		ctx->aio_ring_file = शून्य;
		spin_unlock(&i_mapping->निजी_lock);

		fput(aio_ring_file);
	पूर्ण
पूर्ण

अटल व्योम aio_मुक्त_ring(काष्ठा kioctx *ctx)
अणु
	पूर्णांक i;

	/* Disconnect the kiotx from the ring file.  This prevents future
	 * accesses to the kioctx from page migration.
	 */
	put_aio_ring_file(ctx);

	क्रम (i = 0; i < ctx->nr_pages; i++) अणु
		काष्ठा page *page;
		pr_debug("pid(%d) [%d] page->count=%d\n", current->pid, i,
				page_count(ctx->ring_pages[i]));
		page = ctx->ring_pages[i];
		अगर (!page)
			जारी;
		ctx->ring_pages[i] = शून्य;
		put_page(page);
	पूर्ण

	अगर (ctx->ring_pages && ctx->ring_pages != ctx->पूर्णांकernal_pages) अणु
		kमुक्त(ctx->ring_pages);
		ctx->ring_pages = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक aio_ring_mremap(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा kioctx_table *table;
	पूर्णांक i, res = -EINVAL;

	spin_lock(&mm->ioctx_lock);
	rcu_पढ़ो_lock();
	table = rcu_dereference(mm->ioctx_table);
	क्रम (i = 0; i < table->nr; i++) अणु
		काष्ठा kioctx *ctx;

		ctx = rcu_dereference(table->table[i]);
		अगर (ctx && ctx->aio_ring_file == file) अणु
			अगर (!atomic_पढ़ो(&ctx->dead)) अणु
				ctx->user_id = ctx->mmap_base = vma->vm_start;
				res = 0;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	spin_unlock(&mm->ioctx_lock);
	वापस res;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा aio_ring_vm_ops = अणु
	.mremap		= aio_ring_mremap,
#अगर IS_ENABLED(CONFIG_MMU)
	.fault		= filemap_fault,
	.map_pages	= filemap_map_pages,
	.page_mkग_लिखो	= filemap_page_mkग_लिखो,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक aio_ring_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	vma->vm_flags |= VM_DONTEXPAND;
	vma->vm_ops = &aio_ring_vm_ops;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations aio_ring_fops = अणु
	.mmap = aio_ring_mmap,
पूर्ण;

#अगर IS_ENABLED(CONFIG_MIGRATION)
अटल पूर्णांक aio_migratepage(काष्ठा address_space *mapping, काष्ठा page *new,
			काष्ठा page *old, क्रमागत migrate_mode mode)
अणु
	काष्ठा kioctx *ctx;
	अचिन्हित दीर्घ flags;
	pgoff_t idx;
	पूर्णांक rc;

	/*
	 * We cannot support the _NO_COPY हाल here, because copy needs to
	 * happen under the ctx->completion_lock. That करोes not work with the
	 * migration workflow of MIGRATE_SYNC_NO_COPY.
	 */
	अगर (mode == MIGRATE_SYNC_NO_COPY)
		वापस -EINVAL;

	rc = 0;

	/* mapping->निजी_lock here protects against the kioctx tearकरोwn.  */
	spin_lock(&mapping->निजी_lock);
	ctx = mapping->निजी_data;
	अगर (!ctx) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* The ring_lock mutex.  The prevents aio_पढ़ो_events() from writing
	 * to the ring's head, and prevents page migration from mucking in
	 * a partially initialized kiotx.
	 */
	अगर (!mutex_trylock(&ctx->ring_lock)) अणु
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	idx = old->index;
	अगर (idx < (pgoff_t)ctx->nr_pages) अणु
		/* Make sure the old page hasn't alपढ़ोy been changed */
		अगर (ctx->ring_pages[idx] != old)
			rc = -EAGAIN;
	पूर्ण अन्यथा
		rc = -EINVAL;

	अगर (rc != 0)
		जाओ out_unlock;

	/* Writeback must be complete */
	BUG_ON(PageWriteback(old));
	get_page(new);

	rc = migrate_page_move_mapping(mapping, new, old, 1);
	अगर (rc != MIGRATEPAGE_SUCCESS) अणु
		put_page(new);
		जाओ out_unlock;
	पूर्ण

	/* Take completion_lock to prevent other ग_लिखोs to the ring buffer
	 * जबतक the old page is copied to the new.  This prevents new
	 * events from being lost.
	 */
	spin_lock_irqsave(&ctx->completion_lock, flags);
	migrate_page_copy(new, old);
	BUG_ON(ctx->ring_pages[idx] != old);
	ctx->ring_pages[idx] = new;
	spin_unlock_irqrestore(&ctx->completion_lock, flags);

	/* The old page is no दीर्घer accessible. */
	put_page(old);

out_unlock:
	mutex_unlock(&ctx->ring_lock);
out:
	spin_unlock(&mapping->निजी_lock);
	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा address_space_operations aio_ctx_aops = अणु
	.set_page_dirty = __set_page_dirty_no_ग_लिखोback,
#अगर IS_ENABLED(CONFIG_MIGRATION)
	.migratepage	= aio_migratepage,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक aio_setup_ring(काष्ठा kioctx *ctx, अचिन्हित पूर्णांक nr_events)
अणु
	काष्ठा aio_ring *ring;
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ size, unused;
	पूर्णांक nr_pages;
	पूर्णांक i;
	काष्ठा file *file;

	/* Compensate क्रम the ring buffer's head/tail overlap entry */
	nr_events += 2;	/* 1 is required, 2 क्रम good luck */

	size = माप(काष्ठा aio_ring);
	size += माप(काष्ठा io_event) * nr_events;

	nr_pages = PFN_UP(size);
	अगर (nr_pages < 0)
		वापस -EINVAL;

	file = aio_निजी_file(ctx, nr_pages);
	अगर (IS_ERR(file)) अणु
		ctx->aio_ring_file = शून्य;
		वापस -ENOMEM;
	पूर्ण

	ctx->aio_ring_file = file;
	nr_events = (PAGE_SIZE * nr_pages - माप(काष्ठा aio_ring))
			/ माप(काष्ठा io_event);

	ctx->ring_pages = ctx->पूर्णांकernal_pages;
	अगर (nr_pages > AIO_RING_PAGES) अणु
		ctx->ring_pages = kसुस्मृति(nr_pages, माप(काष्ठा page *),
					  GFP_KERNEL);
		अगर (!ctx->ring_pages) अणु
			put_aio_ring_file(ctx);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nr_pages; i++) अणु
		काष्ठा page *page;
		page = find_or_create_page(file->f_mapping,
					   i, GFP_HIGHUSER | __GFP_ZERO);
		अगर (!page)
			अवरोध;
		pr_debug("pid(%d) page[%d]->count=%d\n",
			 current->pid, i, page_count(page));
		SetPageUptodate(page);
		unlock_page(page);

		ctx->ring_pages[i] = page;
	पूर्ण
	ctx->nr_pages = i;

	अगर (unlikely(i != nr_pages)) अणु
		aio_मुक्त_ring(ctx);
		वापस -ENOMEM;
	पूर्ण

	ctx->mmap_size = nr_pages * PAGE_SIZE;
	pr_debug("attempting mmap of %lu bytes\n", ctx->mmap_size);

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm)) अणु
		ctx->mmap_size = 0;
		aio_मुक्त_ring(ctx);
		वापस -EINTR;
	पूर्ण

	ctx->mmap_base = करो_mmap(ctx->aio_ring_file, 0, ctx->mmap_size,
				 PROT_READ | PROT_WRITE,
				 MAP_SHARED, 0, &unused, शून्य);
	mmap_ग_लिखो_unlock(mm);
	अगर (IS_ERR((व्योम *)ctx->mmap_base)) अणु
		ctx->mmap_size = 0;
		aio_मुक्त_ring(ctx);
		वापस -ENOMEM;
	पूर्ण

	pr_debug("mmap address: 0x%08lx\n", ctx->mmap_base);

	ctx->user_id = ctx->mmap_base;
	ctx->nr_events = nr_events; /* trusted copy */

	ring = kmap_atomic(ctx->ring_pages[0]);
	ring->nr = nr_events;	/* user copy */
	ring->id = ~0U;
	ring->head = ring->tail = 0;
	ring->magic = AIO_RING_MAGIC;
	ring->compat_features = AIO_RING_COMPAT_FEATURES;
	ring->incompat_features = AIO_RING_INCOMPAT_FEATURES;
	ring->header_length = माप(काष्ठा aio_ring);
	kunmap_atomic(ring);
	flush_dcache_page(ctx->ring_pages[0]);

	वापस 0;
पूर्ण

#घोषणा AIO_EVENTS_PER_PAGE	(PAGE_SIZE / माप(काष्ठा io_event))
#घोषणा AIO_EVENTS_FIRST_PAGE	((PAGE_SIZE - माप(काष्ठा aio_ring)) / माप(काष्ठा io_event))
#घोषणा AIO_EVENTS_OFFSET	(AIO_EVENTS_PER_PAGE - AIO_EVENTS_FIRST_PAGE)

व्योम kiocb_set_cancel_fn(काष्ठा kiocb *iocb, kiocb_cancel_fn *cancel)
अणु
	काष्ठा aio_kiocb *req = container_of(iocb, काष्ठा aio_kiocb, rw);
	काष्ठा kioctx *ctx = req->ki_ctx;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON_ONCE(!list_empty(&req->ki_list)))
		वापस;

	spin_lock_irqsave(&ctx->ctx_lock, flags);
	list_add_tail(&req->ki_list, &ctx->active_reqs);
	req->ki_cancel = cancel;
	spin_unlock_irqrestore(&ctx->ctx_lock, flags);
पूर्ण
EXPORT_SYMBOL(kiocb_set_cancel_fn);

/*
 * मुक्त_ioctx() should be RCU delayed to synchronize against the RCU
 * रक्षित lookup_ioctx() and also needs process context to call
 * aio_मुक्त_ring().  Use rcu_work.
 */
अटल व्योम मुक्त_ioctx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kioctx *ctx = container_of(to_rcu_work(work), काष्ठा kioctx,
					  मुक्त_rwork);
	pr_debug("freeing %p\n", ctx);

	aio_मुक्त_ring(ctx);
	मुक्त_percpu(ctx->cpu);
	percpu_ref_निकास(&ctx->reqs);
	percpu_ref_निकास(&ctx->users);
	kmem_cache_मुक्त(kioctx_cachep, ctx);
पूर्ण

अटल व्योम मुक्त_ioctx_reqs(काष्ठा percpu_ref *ref)
अणु
	काष्ठा kioctx *ctx = container_of(ref, काष्ठा kioctx, reqs);

	/* At this poपूर्णांक we know that there are no any in-flight requests */
	अगर (ctx->rq_रुको && atomic_dec_and_test(&ctx->rq_रुको->count))
		complete(&ctx->rq_रुको->comp);

	/* Synchronize against RCU रक्षित table->table[] dereferences */
	INIT_RCU_WORK(&ctx->मुक्त_rwork, मुक्त_ioctx);
	queue_rcu_work(प्रणाली_wq, &ctx->मुक्त_rwork);
पूर्ण

/*
 * When this function runs, the kioctx has been हटाओd from the "hash table"
 * and ctx->users has dropped to 0, so we know no more kiocbs can be submitted -
 * now it's safe to cancel any that need to be.
 */
अटल व्योम मुक्त_ioctx_users(काष्ठा percpu_ref *ref)
अणु
	काष्ठा kioctx *ctx = container_of(ref, काष्ठा kioctx, users);
	काष्ठा aio_kiocb *req;

	spin_lock_irq(&ctx->ctx_lock);

	जबतक (!list_empty(&ctx->active_reqs)) अणु
		req = list_first_entry(&ctx->active_reqs,
				       काष्ठा aio_kiocb, ki_list);
		req->ki_cancel(&req->rw);
		list_del_init(&req->ki_list);
	पूर्ण

	spin_unlock_irq(&ctx->ctx_lock);

	percpu_ref_समाप्त(&ctx->reqs);
	percpu_ref_put(&ctx->reqs);
पूर्ण

अटल पूर्णांक ioctx_add_table(काष्ठा kioctx *ctx, काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित i, new_nr;
	काष्ठा kioctx_table *table, *old;
	काष्ठा aio_ring *ring;

	spin_lock(&mm->ioctx_lock);
	table = rcu_dereference_raw(mm->ioctx_table);

	जबतक (1) अणु
		अगर (table)
			क्रम (i = 0; i < table->nr; i++)
				अगर (!rcu_access_poपूर्णांकer(table->table[i])) अणु
					ctx->id = i;
					rcu_assign_poपूर्णांकer(table->table[i], ctx);
					spin_unlock(&mm->ioctx_lock);

					/* While kioctx setup is in progress,
					 * we are रक्षित from page migration
					 * changes ring_pages by ->ring_lock.
					 */
					ring = kmap_atomic(ctx->ring_pages[0]);
					ring->id = ctx->id;
					kunmap_atomic(ring);
					वापस 0;
				पूर्ण

		new_nr = (table ? table->nr : 1) * 4;
		spin_unlock(&mm->ioctx_lock);

		table = kzalloc(माप(*table) + माप(काष्ठा kioctx *) *
				new_nr, GFP_KERNEL);
		अगर (!table)
			वापस -ENOMEM;

		table->nr = new_nr;

		spin_lock(&mm->ioctx_lock);
		old = rcu_dereference_raw(mm->ioctx_table);

		अगर (!old) अणु
			rcu_assign_poपूर्णांकer(mm->ioctx_table, table);
		पूर्ण अन्यथा अगर (table->nr > old->nr) अणु
			स_नकल(table->table, old->table,
			       old->nr * माप(काष्ठा kioctx *));

			rcu_assign_poपूर्णांकer(mm->ioctx_table, table);
			kमुक्त_rcu(old, rcu);
		पूर्ण अन्यथा अणु
			kमुक्त(table);
			table = old;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम aio_nr_sub(अचिन्हित nr)
अणु
	spin_lock(&aio_nr_lock);
	अगर (WARN_ON(aio_nr - nr > aio_nr))
		aio_nr = 0;
	अन्यथा
		aio_nr -= nr;
	spin_unlock(&aio_nr_lock);
पूर्ण

/* ioctx_alloc
 *	Allocates and initializes an ioctx.  Returns an ERR_PTR अगर it failed.
 */
अटल काष्ठा kioctx *ioctx_alloc(अचिन्हित nr_events)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा kioctx *ctx;
	पूर्णांक err = -ENOMEM;

	/*
	 * Store the original nr_events -- what userspace passed to io_setup(),
	 * क्रम counting against the global limit -- beक्रमe it changes.
	 */
	अचिन्हित पूर्णांक max_reqs = nr_events;

	/*
	 * We keep track of the number of available ringbuffer slots, to prevent
	 * overflow (reqs_available), and we also use percpu counters क्रम this.
	 *
	 * So since up to half the slots might be on other cpu's percpu counters
	 * and unavailable, द्विगुन nr_events so userspace sees what they
	 * expected: additionally, we move req_batch slots to/from percpu
	 * counters at a समय, so make sure that isn't 0:
	 */
	nr_events = max(nr_events, num_possible_cpus() * 4);
	nr_events *= 2;

	/* Prevent overflows */
	अगर (nr_events > (0x10000000U / माप(काष्ठा io_event))) अणु
		pr_debug("ENOMEM: nr_events too high\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!nr_events || (अचिन्हित दीर्घ)max_reqs > aio_max_nr)
		वापस ERR_PTR(-EAGAIN);

	ctx = kmem_cache_zalloc(kioctx_cachep, GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	ctx->max_reqs = max_reqs;

	spin_lock_init(&ctx->ctx_lock);
	spin_lock_init(&ctx->completion_lock);
	mutex_init(&ctx->ring_lock);
	/* Protect against page migration throughout kiotx setup by keeping
	 * the ring_lock mutex held until setup is complete. */
	mutex_lock(&ctx->ring_lock);
	init_रुकोqueue_head(&ctx->रुको);

	INIT_LIST_HEAD(&ctx->active_reqs);

	अगर (percpu_ref_init(&ctx->users, मुक्त_ioctx_users, 0, GFP_KERNEL))
		जाओ err;

	अगर (percpu_ref_init(&ctx->reqs, मुक्त_ioctx_reqs, 0, GFP_KERNEL))
		जाओ err;

	ctx->cpu = alloc_percpu(काष्ठा kioctx_cpu);
	अगर (!ctx->cpu)
		जाओ err;

	err = aio_setup_ring(ctx, nr_events);
	अगर (err < 0)
		जाओ err;

	atomic_set(&ctx->reqs_available, ctx->nr_events - 1);
	ctx->req_batch = (ctx->nr_events - 1) / (num_possible_cpus() * 4);
	अगर (ctx->req_batch < 1)
		ctx->req_batch = 1;

	/* limit the number of प्रणाली wide aios */
	spin_lock(&aio_nr_lock);
	अगर (aio_nr + ctx->max_reqs > aio_max_nr ||
	    aio_nr + ctx->max_reqs < aio_nr) अणु
		spin_unlock(&aio_nr_lock);
		err = -EAGAIN;
		जाओ err_ctx;
	पूर्ण
	aio_nr += ctx->max_reqs;
	spin_unlock(&aio_nr_lock);

	percpu_ref_get(&ctx->users);	/* io_setup() will drop this ref */
	percpu_ref_get(&ctx->reqs);	/* मुक्त_ioctx_users() will drop this */

	err = ioctx_add_table(ctx, mm);
	अगर (err)
		जाओ err_cleanup;

	/* Release the ring_lock mutex now that all setup is complete. */
	mutex_unlock(&ctx->ring_lock);

	pr_debug("allocated ioctx %p[%ld]: mm=%p mask=0x%x\n",
		 ctx, ctx->user_id, mm, ctx->nr_events);
	वापस ctx;

err_cleanup:
	aio_nr_sub(ctx->max_reqs);
err_ctx:
	atomic_set(&ctx->dead, 1);
	अगर (ctx->mmap_size)
		vm_munmap(ctx->mmap_base, ctx->mmap_size);
	aio_मुक्त_ring(ctx);
err:
	mutex_unlock(&ctx->ring_lock);
	मुक्त_percpu(ctx->cpu);
	percpu_ref_निकास(&ctx->reqs);
	percpu_ref_निकास(&ctx->users);
	kmem_cache_मुक्त(kioctx_cachep, ctx);
	pr_debug("error allocating ioctx %d\n", err);
	वापस ERR_PTR(err);
पूर्ण

/* समाप्त_ioctx
 *	Cancels all outstanding aio requests on an aio context.  Used
 *	when the processes owning a context have all निकासed to encourage
 *	the rapid deकाष्ठाion of the kioctx.
 */
अटल पूर्णांक समाप्त_ioctx(काष्ठा mm_काष्ठा *mm, काष्ठा kioctx *ctx,
		      काष्ठा ctx_rq_रुको *रुको)
अणु
	काष्ठा kioctx_table *table;

	spin_lock(&mm->ioctx_lock);
	अगर (atomic_xchg(&ctx->dead, 1)) अणु
		spin_unlock(&mm->ioctx_lock);
		वापस -EINVAL;
	पूर्ण

	table = rcu_dereference_raw(mm->ioctx_table);
	WARN_ON(ctx != rcu_access_poपूर्णांकer(table->table[ctx->id]));
	RCU_INIT_POINTER(table->table[ctx->id], शून्य);
	spin_unlock(&mm->ioctx_lock);

	/* मुक्त_ioctx_reqs() will करो the necessary RCU synchronization */
	wake_up_all(&ctx->रुको);

	/*
	 * It'd be more correct to करो this in मुक्त_ioctx(), after all
	 * the outstanding kiocbs have finished - but by then io_destroy
	 * has alपढ़ोy वापसed, so io_setup() could potentially वापस
	 * -EAGAIN with no ioctxs actually in use (as far as userspace
	 *  could tell).
	 */
	aio_nr_sub(ctx->max_reqs);

	अगर (ctx->mmap_size)
		vm_munmap(ctx->mmap_base, ctx->mmap_size);

	ctx->rq_रुको = रुको;
	percpu_ref_समाप्त(&ctx->users);
	वापस 0;
पूर्ण

/*
 * निकास_aio: called when the last user of mm goes away.  At this poपूर्णांक, there is
 * no way क्रम any new requests to be submited or any of the io_* syscalls to be
 * called on the context.
 *
 * There may be outstanding kiocbs, but मुक्त_ioctx() will explicitly रुको on
 * them.
 */
व्योम निकास_aio(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा kioctx_table *table = rcu_dereference_raw(mm->ioctx_table);
	काष्ठा ctx_rq_रुको रुको;
	पूर्णांक i, skipped;

	अगर (!table)
		वापस;

	atomic_set(&रुको.count, table->nr);
	init_completion(&रुको.comp);

	skipped = 0;
	क्रम (i = 0; i < table->nr; ++i) अणु
		काष्ठा kioctx *ctx =
			rcu_dereference_रक्षित(table->table[i], true);

		अगर (!ctx) अणु
			skipped++;
			जारी;
		पूर्ण

		/*
		 * We करोn't need to bother with munmap() here - निकास_mmap(mm)
		 * is coming and it'll unmap everything. And we simply can't,
		 * this is not necessarily our ->mm.
		 * Since समाप्त_ioctx() uses non-zero ->mmap_size as indicator
		 * that it needs to unmap the area, just set it to 0.
		 */
		ctx->mmap_size = 0;
		समाप्त_ioctx(mm, ctx, &रुको);
	पूर्ण

	अगर (!atomic_sub_and_test(skipped, &रुको.count)) अणु
		/* Wait until all IO क्रम the context are करोne. */
		रुको_क्रम_completion(&रुको.comp);
	पूर्ण

	RCU_INIT_POINTER(mm->ioctx_table, शून्य);
	kमुक्त(table);
पूर्ण

अटल व्योम put_reqs_available(काष्ठा kioctx *ctx, अचिन्हित nr)
अणु
	काष्ठा kioctx_cpu *kcpu;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	kcpu = this_cpu_ptr(ctx->cpu);
	kcpu->reqs_available += nr;

	जबतक (kcpu->reqs_available >= ctx->req_batch * 2) अणु
		kcpu->reqs_available -= ctx->req_batch;
		atomic_add(ctx->req_batch, &ctx->reqs_available);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल bool __get_reqs_available(काष्ठा kioctx *ctx)
अणु
	काष्ठा kioctx_cpu *kcpu;
	bool ret = false;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	kcpu = this_cpu_ptr(ctx->cpu);
	अगर (!kcpu->reqs_available) अणु
		पूर्णांक old, avail = atomic_पढ़ो(&ctx->reqs_available);

		करो अणु
			अगर (avail < ctx->req_batch)
				जाओ out;

			old = avail;
			avail = atomic_cmpxchg(&ctx->reqs_available,
					       avail, avail - ctx->req_batch);
		पूर्ण जबतक (avail != old);

		kcpu->reqs_available += ctx->req_batch;
	पूर्ण

	ret = true;
	kcpu->reqs_available--;
out:
	local_irq_restore(flags);
	वापस ret;
पूर्ण

/* refill_reqs_available
 *	Updates the reqs_available reference counts used क्रम tracking the
 *	number of मुक्त slots in the completion ring.  This can be called
 *	from aio_complete() (to optimistically update reqs_available) or
 *	from aio_get_req() (the we're out of events हाल).  It must be
 *	called holding ctx->completion_lock.
 */
अटल व्योम refill_reqs_available(काष्ठा kioctx *ctx, अचिन्हित head,
                                  अचिन्हित tail)
अणु
	अचिन्हित events_in_ring, completed;

	/* Clamp head since userland can ग_लिखो to it. */
	head %= ctx->nr_events;
	अगर (head <= tail)
		events_in_ring = tail - head;
	अन्यथा
		events_in_ring = ctx->nr_events - (head - tail);

	completed = ctx->completed_events;
	अगर (events_in_ring < completed)
		completed -= events_in_ring;
	अन्यथा
		completed = 0;

	अगर (!completed)
		वापस;

	ctx->completed_events -= completed;
	put_reqs_available(ctx, completed);
पूर्ण

/* user_refill_reqs_available
 *	Called to refill reqs_available when aio_get_req() encounters an
 *	out of space in the completion ring.
 */
अटल व्योम user_refill_reqs_available(काष्ठा kioctx *ctx)
अणु
	spin_lock_irq(&ctx->completion_lock);
	अगर (ctx->completed_events) अणु
		काष्ठा aio_ring *ring;
		अचिन्हित head;

		/* Access of ring->head may race with aio_पढ़ो_events_ring()
		 * here, but that's okay since whether we पढ़ो the old version
		 * or the new version, and either will be valid.  The important
		 * part is that head cannot pass tail since we prevent
		 * aio_complete() from updating tail by holding
		 * ctx->completion_lock.  Even अगर head is invalid, the check
		 * against ctx->completed_events below will make sure we करो the
		 * safe/right thing.
		 */
		ring = kmap_atomic(ctx->ring_pages[0]);
		head = ring->head;
		kunmap_atomic(ring);

		refill_reqs_available(ctx, head, ctx->tail);
	पूर्ण

	spin_unlock_irq(&ctx->completion_lock);
पूर्ण

अटल bool get_reqs_available(काष्ठा kioctx *ctx)
अणु
	अगर (__get_reqs_available(ctx))
		वापस true;
	user_refill_reqs_available(ctx);
	वापस __get_reqs_available(ctx);
पूर्ण

/* aio_get_req
 *	Allocate a slot क्रम an aio request.
 * Returns शून्य अगर no requests are मुक्त.
 *
 * The refcount is initialized to 2 - one क्रम the async op completion,
 * one क्रम the synchronous code that करोes this.
 */
अटल अंतरभूत काष्ठा aio_kiocb *aio_get_req(काष्ठा kioctx *ctx)
अणु
	काष्ठा aio_kiocb *req;

	req = kmem_cache_alloc(kiocb_cachep, GFP_KERNEL);
	अगर (unlikely(!req))
		वापस शून्य;

	अगर (unlikely(!get_reqs_available(ctx))) अणु
		kmem_cache_मुक्त(kiocb_cachep, req);
		वापस शून्य;
	पूर्ण

	percpu_ref_get(&ctx->reqs);
	req->ki_ctx = ctx;
	INIT_LIST_HEAD(&req->ki_list);
	refcount_set(&req->ki_refcnt, 2);
	req->ki_eventfd = शून्य;
	वापस req;
पूर्ण

अटल काष्ठा kioctx *lookup_ioctx(अचिन्हित दीर्घ ctx_id)
अणु
	काष्ठा aio_ring __user *ring  = (व्योम __user *)ctx_id;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा kioctx *ctx, *ret = शून्य;
	काष्ठा kioctx_table *table;
	अचिन्हित id;

	अगर (get_user(id, &ring->id))
		वापस शून्य;

	rcu_पढ़ो_lock();
	table = rcu_dereference(mm->ioctx_table);

	अगर (!table || id >= table->nr)
		जाओ out;

	id = array_index_nospec(id, table->nr);
	ctx = rcu_dereference(table->table[id]);
	अगर (ctx && ctx->user_id == ctx_id) अणु
		अगर (percpu_ref_tryget_live(&ctx->users))
			ret = ctx;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम iocb_destroy(काष्ठा aio_kiocb *iocb)
अणु
	अगर (iocb->ki_eventfd)
		eventfd_ctx_put(iocb->ki_eventfd);
	अगर (iocb->ki_filp)
		fput(iocb->ki_filp);
	percpu_ref_put(&iocb->ki_ctx->reqs);
	kmem_cache_मुक्त(kiocb_cachep, iocb);
पूर्ण

/* aio_complete
 *	Called when the io request on the given iocb is complete.
 */
अटल व्योम aio_complete(काष्ठा aio_kiocb *iocb)
अणु
	काष्ठा kioctx	*ctx = iocb->ki_ctx;
	काष्ठा aio_ring	*ring;
	काष्ठा io_event	*ev_page, *event;
	अचिन्हित tail, pos, head;
	अचिन्हित दीर्घ	flags;

	/*
	 * Add a completion event to the ring buffer. Must be करोne holding
	 * ctx->completion_lock to prevent other code from messing with the tail
	 * poपूर्णांकer since we might be called from irq context.
	 */
	spin_lock_irqsave(&ctx->completion_lock, flags);

	tail = ctx->tail;
	pos = tail + AIO_EVENTS_OFFSET;

	अगर (++tail >= ctx->nr_events)
		tail = 0;

	ev_page = kmap_atomic(ctx->ring_pages[pos / AIO_EVENTS_PER_PAGE]);
	event = ev_page + pos % AIO_EVENTS_PER_PAGE;

	*event = iocb->ki_res;

	kunmap_atomic(ev_page);
	flush_dcache_page(ctx->ring_pages[pos / AIO_EVENTS_PER_PAGE]);

	pr_debug("%p[%u]: %p: %p %Lx %Lx %Lx\n", ctx, tail, iocb,
		 (व्योम __user *)(अचिन्हित दीर्घ)iocb->ki_res.obj,
		 iocb->ki_res.data, iocb->ki_res.res, iocb->ki_res.res2);

	/* after flagging the request as करोne, we
	 * must never even look at it again
	 */
	smp_wmb();	/* make event visible beक्रमe updating tail */

	ctx->tail = tail;

	ring = kmap_atomic(ctx->ring_pages[0]);
	head = ring->head;
	ring->tail = tail;
	kunmap_atomic(ring);
	flush_dcache_page(ctx->ring_pages[0]);

	ctx->completed_events++;
	अगर (ctx->completed_events > 1)
		refill_reqs_available(ctx, head, tail);
	spin_unlock_irqrestore(&ctx->completion_lock, flags);

	pr_debug("added to ring %p at [%u]\n", iocb, tail);

	/*
	 * Check अगर the user asked us to deliver the result through an
	 * eventfd. The eventfd_संकेत() function is safe to be called
	 * from IRQ context.
	 */
	अगर (iocb->ki_eventfd)
		eventfd_संकेत(iocb->ki_eventfd, 1);

	/*
	 * We have to order our ring_info tail store above and test
	 * of the रुको list below outside the रुको lock.  This is
	 * like in wake_up_bit() where clearing a bit has to be
	 * ordered with the unlocked test.
	 */
	smp_mb();

	अगर (रुकोqueue_active(&ctx->रुको))
		wake_up(&ctx->रुको);
पूर्ण

अटल अंतरभूत व्योम iocb_put(काष्ठा aio_kiocb *iocb)
अणु
	अगर (refcount_dec_and_test(&iocb->ki_refcnt)) अणु
		aio_complete(iocb);
		iocb_destroy(iocb);
	पूर्ण
पूर्ण

/* aio_पढ़ो_events_ring
 *	Pull an event off of the ioctx's event ring.  Returns the number of
 *	events fetched
 */
अटल दीर्घ aio_पढ़ो_events_ring(काष्ठा kioctx *ctx,
				 काष्ठा io_event __user *event, दीर्घ nr)
अणु
	काष्ठा aio_ring *ring;
	अचिन्हित head, tail, pos;
	दीर्घ ret = 0;
	पूर्णांक copy_ret;

	/*
	 * The mutex can block and wake us up and that will cause
	 * रुको_event_पूर्णांकerruptible_hrसमयout() to schedule without sleeping
	 * and repeat. This should be rare enough that it करोesn't cause
	 * peक्रमmance issues. See the comment in पढ़ो_events() क्रम more detail.
	 */
	sched_annotate_sleep();
	mutex_lock(&ctx->ring_lock);

	/* Access to ->ring_pages here is रक्षित by ctx->ring_lock. */
	ring = kmap_atomic(ctx->ring_pages[0]);
	head = ring->head;
	tail = ring->tail;
	kunmap_atomic(ring);

	/*
	 * Ensure that once we've पढ़ो the current tail poपूर्णांकer, that
	 * we also see the events that were stored up to the tail.
	 */
	smp_rmb();

	pr_debug("h%u t%u m%u\n", head, tail, ctx->nr_events);

	अगर (head == tail)
		जाओ out;

	head %= ctx->nr_events;
	tail %= ctx->nr_events;

	जबतक (ret < nr) अणु
		दीर्घ avail;
		काष्ठा io_event *ev;
		काष्ठा page *page;

		avail = (head <= tail ?  tail : ctx->nr_events) - head;
		अगर (head == tail)
			अवरोध;

		pos = head + AIO_EVENTS_OFFSET;
		page = ctx->ring_pages[pos / AIO_EVENTS_PER_PAGE];
		pos %= AIO_EVENTS_PER_PAGE;

		avail = min(avail, nr - ret);
		avail = min_t(दीर्घ, avail, AIO_EVENTS_PER_PAGE - pos);

		ev = kmap(page);
		copy_ret = copy_to_user(event + ret, ev + pos,
					माप(*ev) * avail);
		kunmap(page);

		अगर (unlikely(copy_ret)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		ret += avail;
		head += avail;
		head %= ctx->nr_events;
	पूर्ण

	ring = kmap_atomic(ctx->ring_pages[0]);
	ring->head = head;
	kunmap_atomic(ring);
	flush_dcache_page(ctx->ring_pages[0]);

	pr_debug("%li  h%u t%u\n", ret, head, tail);
out:
	mutex_unlock(&ctx->ring_lock);

	वापस ret;
पूर्ण

अटल bool aio_पढ़ो_events(काष्ठा kioctx *ctx, दीर्घ min_nr, दीर्घ nr,
			    काष्ठा io_event __user *event, दीर्घ *i)
अणु
	दीर्घ ret = aio_पढ़ो_events_ring(ctx, event + *i, nr - *i);

	अगर (ret > 0)
		*i += ret;

	अगर (unlikely(atomic_पढ़ो(&ctx->dead)))
		ret = -EINVAL;

	अगर (!*i)
		*i = ret;

	वापस ret < 0 || *i >= min_nr;
पूर्ण

अटल दीर्घ पढ़ो_events(काष्ठा kioctx *ctx, दीर्घ min_nr, दीर्घ nr,
			काष्ठा io_event __user *event,
			kसमय_प्रकार until)
अणु
	दीर्घ ret = 0;

	/*
	 * Note that aio_पढ़ो_events() is being called as the conditional - i.e.
	 * we're calling it after prepare_to_रुको() has set task state to
	 * TASK_INTERRUPTIBLE.
	 *
	 * But aio_पढ़ो_events() can block, and अगर it blocks it's going to flip
	 * the task state back to TASK_RUNNING.
	 *
	 * This should be ok, provided it करोesn't flip the state back to
	 * TASK_RUNNING and वापस 0 too much - that causes us to spin. That
	 * will only happen अगर the mutex_lock() call blocks, and we then find
	 * the ringbuffer empty. So in practice we should be ok, but it's
	 * something to be aware of when touching this code.
	 */
	अगर (until == 0)
		aio_पढ़ो_events(ctx, min_nr, nr, event, &ret);
	अन्यथा
		रुको_event_पूर्णांकerruptible_hrसमयout(ctx->रुको,
				aio_पढ़ो_events(ctx, min_nr, nr, event, &ret),
				until);
	वापस ret;
पूर्ण

/* sys_io_setup:
 *	Create an aio_context capable of receiving at least nr_events.
 *	ctxp must not poपूर्णांक to an aio_context that alपढ़ोy exists, and
 *	must be initialized to 0 prior to the call.  On successful
 *	creation of the aio_context, *ctxp is filled in with the resulting 
 *	handle.  May fail with -EINVAL अगर *ctxp is not initialized,
 *	अगर the specअगरied nr_events exceeds पूर्णांकernal limits.  May fail 
 *	with -EAGAIN अगर the specअगरied nr_events exceeds the user's limit 
 *	of available events.  May fail with -ENOMEM अगर insufficient kernel
 *	resources are available.  May fail with -EFAULT अगर an invalid
 *	poपूर्णांकer is passed क्रम ctxp.  Will fail with -ENOSYS अगर not
 *	implemented.
 */
SYSCALL_DEFINE2(io_setup, अचिन्हित, nr_events, aio_context_t __user *, ctxp)
अणु
	काष्ठा kioctx *ioctx = शून्य;
	अचिन्हित दीर्घ ctx;
	दीर्घ ret;

	ret = get_user(ctx, ctxp);
	अगर (unlikely(ret))
		जाओ out;

	ret = -EINVAL;
	अगर (unlikely(ctx || nr_events == 0)) अणु
		pr_debug("EINVAL: ctx %lu nr_events %u\n",
		         ctx, nr_events);
		जाओ out;
	पूर्ण

	ioctx = ioctx_alloc(nr_events);
	ret = PTR_ERR(ioctx);
	अगर (!IS_ERR(ioctx)) अणु
		ret = put_user(ioctx->user_id, ctxp);
		अगर (ret)
			समाप्त_ioctx(current->mm, ioctx, शून्य);
		percpu_ref_put(&ioctx->users);
	पूर्ण

out:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE2(io_setup, अचिन्हित, nr_events, u32 __user *, ctx32p)
अणु
	काष्ठा kioctx *ioctx = शून्य;
	अचिन्हित दीर्घ ctx;
	दीर्घ ret;

	ret = get_user(ctx, ctx32p);
	अगर (unlikely(ret))
		जाओ out;

	ret = -EINVAL;
	अगर (unlikely(ctx || nr_events == 0)) अणु
		pr_debug("EINVAL: ctx %lu nr_events %u\n",
		         ctx, nr_events);
		जाओ out;
	पूर्ण

	ioctx = ioctx_alloc(nr_events);
	ret = PTR_ERR(ioctx);
	अगर (!IS_ERR(ioctx)) अणु
		/* truncating is ok because it's a user address */
		ret = put_user((u32)ioctx->user_id, ctx32p);
		अगर (ret)
			समाप्त_ioctx(current->mm, ioctx, शून्य);
		percpu_ref_put(&ioctx->users);
	पूर्ण

out:
	वापस ret;
पूर्ण
#पूर्ण_अगर

/* sys_io_destroy:
 *	Destroy the aio_context specअगरied.  May cancel any outstanding 
 *	AIOs and block on completion.  Will fail with -ENOSYS अगर not
 *	implemented.  May fail with -EINVAL अगर the context poपूर्णांकed to
 *	is invalid.
 */
SYSCALL_DEFINE1(io_destroy, aio_context_t, ctx)
अणु
	काष्ठा kioctx *ioctx = lookup_ioctx(ctx);
	अगर (likely(शून्य != ioctx)) अणु
		काष्ठा ctx_rq_रुको रुको;
		पूर्णांक ret;

		init_completion(&रुको.comp);
		atomic_set(&रुको.count, 1);

		/* Pass requests_करोne to समाप्त_ioctx() where it can be set
		 * in a thपढ़ो-safe way. If we try to set it here then we have
		 * a race condition अगर two io_destroy() called simultaneously.
		 */
		ret = समाप्त_ioctx(current->mm, ioctx, &रुको);
		percpu_ref_put(&ioctx->users);

		/* Wait until all IO क्रम the context are करोne. Otherwise kernel
		 * keep using user-space buffers even अगर user thinks the context
		 * is destroyed.
		 */
		अगर (!ret)
			रुको_क्रम_completion(&रुको.comp);

		वापस ret;
	पूर्ण
	pr_debug("EINVAL: invalid context id\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम aio_हटाओ_iocb(काष्ठा aio_kiocb *iocb)
अणु
	काष्ठा kioctx *ctx = iocb->ki_ctx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->ctx_lock, flags);
	list_del(&iocb->ki_list);
	spin_unlock_irqrestore(&ctx->ctx_lock, flags);
पूर्ण

अटल व्योम aio_complete_rw(काष्ठा kiocb *kiocb, दीर्घ res, दीर्घ res2)
अणु
	काष्ठा aio_kiocb *iocb = container_of(kiocb, काष्ठा aio_kiocb, rw);

	अगर (!list_empty_careful(&iocb->ki_list))
		aio_हटाओ_iocb(iocb);

	अगर (kiocb->ki_flags & IOCB_WRITE) अणु
		काष्ठा inode *inode = file_inode(kiocb->ki_filp);

		/*
		 * Tell lockdep we inherited मुक्तze protection from submission
		 * thपढ़ो.
		 */
		अगर (S_ISREG(inode->i_mode))
			__sb_ग_लिखोrs_acquired(inode->i_sb, SB_FREEZE_WRITE);
		file_end_ग_लिखो(kiocb->ki_filp);
	पूर्ण

	iocb->ki_res.res = res;
	iocb->ki_res.res2 = res2;
	iocb_put(iocb);
पूर्ण

अटल पूर्णांक aio_prep_rw(काष्ठा kiocb *req, स्थिर काष्ठा iocb *iocb)
अणु
	पूर्णांक ret;

	req->ki_complete = aio_complete_rw;
	req->निजी = शून्य;
	req->ki_pos = iocb->aio_offset;
	req->ki_flags = iocb_flags(req->ki_filp);
	अगर (iocb->aio_flags & IOCB_FLAG_RESFD)
		req->ki_flags |= IOCB_EVENTFD;
	req->ki_hपूर्णांक = ki_hपूर्णांक_validate(file_ग_लिखो_hपूर्णांक(req->ki_filp));
	अगर (iocb->aio_flags & IOCB_FLAG_IOPRIO) अणु
		/*
		 * If the IOCB_FLAG_IOPRIO flag of aio_flags is set, then
		 * aio_reqprio is पूर्णांकerpreted as an I/O scheduling
		 * class and priority.
		 */
		ret = ioprio_check_cap(iocb->aio_reqprio);
		अगर (ret) अणु
			pr_debug("aio ioprio check cap error: %d\n", ret);
			वापस ret;
		पूर्ण

		req->ki_ioprio = iocb->aio_reqprio;
	पूर्ण अन्यथा
		req->ki_ioprio = get_current_ioprio();

	ret = kiocb_set_rw_flags(req, iocb->aio_rw_flags);
	अगर (unlikely(ret))
		वापस ret;

	req->ki_flags &= ~IOCB_HIPRI; /* no one is going to poll क्रम this I/O */
	वापस 0;
पूर्ण

अटल sमाप_प्रकार aio_setup_rw(पूर्णांक rw, स्थिर काष्ठा iocb *iocb,
		काष्ठा iovec **iovec, bool vectored, bool compat,
		काष्ठा iov_iter *iter)
अणु
	व्योम __user *buf = (व्योम __user *)(uपूर्णांकptr_t)iocb->aio_buf;
	माप_प्रकार len = iocb->aio_nbytes;

	अगर (!vectored) अणु
		sमाप_प्रकार ret = import_single_range(rw, buf, len, *iovec, iter);
		*iovec = शून्य;
		वापस ret;
	पूर्ण

	वापस __import_iovec(rw, buf, len, UIO_FASTIOV, iovec, iter, compat);
पूर्ण

अटल अंतरभूत व्योम aio_rw_करोne(काष्ठा kiocb *req, sमाप_प्रकार ret)
अणु
	चयन (ret) अणु
	हाल -EIOCBQUEUED:
		अवरोध;
	हाल -ERESTARTSYS:
	हाल -ERESTARTNOINTR:
	हाल -ERESTARTNOHAND:
	हाल -ERESTART_RESTARTBLOCK:
		/*
		 * There's no easy way to restart the syscall since other AIO's
		 * may be alपढ़ोy running. Just fail this IO with EINTR.
		 */
		ret = -EINTR;
		fallthrough;
	शेष:
		req->ki_complete(req, ret, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक aio_पढ़ो(काष्ठा kiocb *req, स्थिर काष्ठा iocb *iocb,
			bool vectored, bool compat)
अणु
	काष्ठा iovec अंतरभूत_vecs[UIO_FASTIOV], *iovec = अंतरभूत_vecs;
	काष्ठा iov_iter iter;
	काष्ठा file *file;
	पूर्णांक ret;

	ret = aio_prep_rw(req, iocb);
	अगर (ret)
		वापस ret;
	file = req->ki_filp;
	अगर (unlikely(!(file->f_mode & FMODE_READ)))
		वापस -EBADF;
	ret = -EINVAL;
	अगर (unlikely(!file->f_op->पढ़ो_iter))
		वापस -EINVAL;

	ret = aio_setup_rw(READ, iocb, &iovec, vectored, compat, &iter);
	अगर (ret < 0)
		वापस ret;
	ret = rw_verअगरy_area(READ, file, &req->ki_pos, iov_iter_count(&iter));
	अगर (!ret)
		aio_rw_करोne(req, call_पढ़ो_iter(file, req, &iter));
	kमुक्त(iovec);
	वापस ret;
पूर्ण

अटल पूर्णांक aio_ग_लिखो(काष्ठा kiocb *req, स्थिर काष्ठा iocb *iocb,
			 bool vectored, bool compat)
अणु
	काष्ठा iovec अंतरभूत_vecs[UIO_FASTIOV], *iovec = अंतरभूत_vecs;
	काष्ठा iov_iter iter;
	काष्ठा file *file;
	पूर्णांक ret;

	ret = aio_prep_rw(req, iocb);
	अगर (ret)
		वापस ret;
	file = req->ki_filp;

	अगर (unlikely(!(file->f_mode & FMODE_WRITE)))
		वापस -EBADF;
	अगर (unlikely(!file->f_op->ग_लिखो_iter))
		वापस -EINVAL;

	ret = aio_setup_rw(WRITE, iocb, &iovec, vectored, compat, &iter);
	अगर (ret < 0)
		वापस ret;
	ret = rw_verअगरy_area(WRITE, file, &req->ki_pos, iov_iter_count(&iter));
	अगर (!ret) अणु
		/*
		 * Open-code file_start_ग_लिखो here to grab मुक्तze protection,
		 * which will be released by another thपढ़ो in
		 * aio_complete_rw().  Fool lockdep by telling it the lock got
		 * released so that it करोesn't complain about the held lock when
		 * we वापस to userspace.
		 */
		अगर (S_ISREG(file_inode(file)->i_mode)) अणु
			sb_start_ग_लिखो(file_inode(file)->i_sb);
			__sb_ग_लिखोrs_release(file_inode(file)->i_sb, SB_FREEZE_WRITE);
		पूर्ण
		req->ki_flags |= IOCB_WRITE;
		aio_rw_करोne(req, call_ग_लिखो_iter(file, req, &iter));
	पूर्ण
	kमुक्त(iovec);
	वापस ret;
पूर्ण

अटल व्योम aio_fsync_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा aio_kiocb *iocb = container_of(work, काष्ठा aio_kiocb, fsync.work);
	स्थिर काष्ठा cred *old_cred = override_creds(iocb->fsync.creds);

	iocb->ki_res.res = vfs_fsync(iocb->fsync.file, iocb->fsync.datasync);
	revert_creds(old_cred);
	put_cred(iocb->fsync.creds);
	iocb_put(iocb);
पूर्ण

अटल पूर्णांक aio_fsync(काष्ठा fsync_iocb *req, स्थिर काष्ठा iocb *iocb,
		     bool datasync)
अणु
	अगर (unlikely(iocb->aio_buf || iocb->aio_offset || iocb->aio_nbytes ||
			iocb->aio_rw_flags))
		वापस -EINVAL;

	अगर (unlikely(!req->file->f_op->fsync))
		वापस -EINVAL;

	req->creds = prepare_creds();
	अगर (!req->creds)
		वापस -ENOMEM;

	req->datasync = datasync;
	INIT_WORK(&req->work, aio_fsync_work);
	schedule_work(&req->work);
	वापस 0;
पूर्ण

अटल व्योम aio_poll_put_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा poll_iocb *req = container_of(work, काष्ठा poll_iocb, work);
	काष्ठा aio_kiocb *iocb = container_of(req, काष्ठा aio_kiocb, poll);

	iocb_put(iocb);
पूर्ण

अटल व्योम aio_poll_complete_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा poll_iocb *req = container_of(work, काष्ठा poll_iocb, work);
	काष्ठा aio_kiocb *iocb = container_of(req, काष्ठा aio_kiocb, poll);
	काष्ठा poll_table_काष्ठा pt = अणु ._key = req->events पूर्ण;
	काष्ठा kioctx *ctx = iocb->ki_ctx;
	__poll_t mask = 0;

	अगर (!READ_ONCE(req->cancelled))
		mask = vfs_poll(req->file, &pt) & req->events;

	/*
	 * Note that ->ki_cancel callers also delete iocb from active_reqs after
	 * calling ->ki_cancel.  We need the ctx_lock roundtrip here to
	 * synchronize with them.  In the cancellation हाल the list_del_init
	 * itself is not actually needed, but harmless so we keep it in to
	 * aव्योम further branches in the fast path.
	 */
	spin_lock_irq(&ctx->ctx_lock);
	अगर (!mask && !READ_ONCE(req->cancelled)) अणु
		add_रुको_queue(req->head, &req->रुको);
		spin_unlock_irq(&ctx->ctx_lock);
		वापस;
	पूर्ण
	list_del_init(&iocb->ki_list);
	iocb->ki_res.res = mangle_poll(mask);
	req->करोne = true;
	spin_unlock_irq(&ctx->ctx_lock);

	iocb_put(iocb);
पूर्ण

/* assumes we are called with irqs disabled */
अटल पूर्णांक aio_poll_cancel(काष्ठा kiocb *iocb)
अणु
	काष्ठा aio_kiocb *aiocb = container_of(iocb, काष्ठा aio_kiocb, rw);
	काष्ठा poll_iocb *req = &aiocb->poll;

	spin_lock(&req->head->lock);
	WRITE_ONCE(req->cancelled, true);
	अगर (!list_empty(&req->रुको.entry)) अणु
		list_del_init(&req->रुको.entry);
		schedule_work(&aiocb->poll.work);
	पूर्ण
	spin_unlock(&req->head->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक aio_poll_wake(काष्ठा रुको_queue_entry *रुको, अचिन्हित mode, पूर्णांक sync,
		व्योम *key)
अणु
	काष्ठा poll_iocb *req = container_of(रुको, काष्ठा poll_iocb, रुको);
	काष्ठा aio_kiocb *iocb = container_of(req, काष्ठा aio_kiocb, poll);
	__poll_t mask = key_to_poll(key);
	अचिन्हित दीर्घ flags;

	/* क्रम instances that support it check क्रम an event match first: */
	अगर (mask && !(mask & req->events))
		वापस 0;

	list_del_init(&req->रुको.entry);

	अगर (mask && spin_trylock_irqsave(&iocb->ki_ctx->ctx_lock, flags)) अणु
		काष्ठा kioctx *ctx = iocb->ki_ctx;

		/*
		 * Try to complete the iocb अंतरभूत अगर we can. Use
		 * irqsave/irqrestore because not all fileप्रणालीs (e.g. fuse)
		 * call this function with IRQs disabled and because IRQs
		 * have to be disabled beक्रमe ctx_lock is obtained.
		 */
		list_del(&iocb->ki_list);
		iocb->ki_res.res = mangle_poll(mask);
		req->करोne = true;
		अगर (iocb->ki_eventfd && eventfd_संकेत_count()) अणु
			iocb = शून्य;
			INIT_WORK(&req->work, aio_poll_put_work);
			schedule_work(&req->work);
		पूर्ण
		spin_unlock_irqrestore(&ctx->ctx_lock, flags);
		अगर (iocb)
			iocb_put(iocb);
	पूर्ण अन्यथा अणु
		schedule_work(&req->work);
	पूर्ण
	वापस 1;
पूर्ण

काष्ठा aio_poll_table अणु
	काष्ठा poll_table_काष्ठा	pt;
	काष्ठा aio_kiocb		*iocb;
	पूर्णांक				error;
पूर्ण;

अटल व्योम
aio_poll_queue_proc(काष्ठा file *file, काष्ठा रुको_queue_head *head,
		काष्ठा poll_table_काष्ठा *p)
अणु
	काष्ठा aio_poll_table *pt = container_of(p, काष्ठा aio_poll_table, pt);

	/* multiple रुको queues per file are not supported */
	अगर (unlikely(pt->iocb->poll.head)) अणु
		pt->error = -EINVAL;
		वापस;
	पूर्ण

	pt->error = 0;
	pt->iocb->poll.head = head;
	add_रुको_queue(head, &pt->iocb->poll.रुको);
पूर्ण

अटल पूर्णांक aio_poll(काष्ठा aio_kiocb *aiocb, स्थिर काष्ठा iocb *iocb)
अणु
	काष्ठा kioctx *ctx = aiocb->ki_ctx;
	काष्ठा poll_iocb *req = &aiocb->poll;
	काष्ठा aio_poll_table apt;
	bool cancel = false;
	__poll_t mask;

	/* reject any unknown events outside the normal event mask. */
	अगर ((u16)iocb->aio_buf != iocb->aio_buf)
		वापस -EINVAL;
	/* reject fields that are not defined क्रम poll */
	अगर (iocb->aio_offset || iocb->aio_nbytes || iocb->aio_rw_flags)
		वापस -EINVAL;

	INIT_WORK(&req->work, aio_poll_complete_work);
	req->events = demangle_poll(iocb->aio_buf) | EPOLLERR | EPOLLHUP;

	req->head = शून्य;
	req->करोne = false;
	req->cancelled = false;

	apt.pt._qproc = aio_poll_queue_proc;
	apt.pt._key = req->events;
	apt.iocb = aiocb;
	apt.error = -EINVAL; /* same as no support क्रम IOCB_CMD_POLL */

	/* initialized the list so that we can करो list_empty checks */
	INIT_LIST_HEAD(&req->रुको.entry);
	init_रुकोqueue_func_entry(&req->रुको, aio_poll_wake);

	mask = vfs_poll(req->file, &apt.pt) & req->events;
	spin_lock_irq(&ctx->ctx_lock);
	अगर (likely(req->head)) अणु
		spin_lock(&req->head->lock);
		अगर (unlikely(list_empty(&req->रुको.entry))) अणु
			अगर (apt.error)
				cancel = true;
			apt.error = 0;
			mask = 0;
		पूर्ण
		अगर (mask || apt.error) अणु
			list_del_init(&req->रुको.entry);
		पूर्ण अन्यथा अगर (cancel) अणु
			WRITE_ONCE(req->cancelled, true);
		पूर्ण अन्यथा अगर (!req->करोne) अणु /* actually रुकोing क्रम an event */
			list_add_tail(&aiocb->ki_list, &ctx->active_reqs);
			aiocb->ki_cancel = aio_poll_cancel;
		पूर्ण
		spin_unlock(&req->head->lock);
	पूर्ण
	अगर (mask) अणु /* no async, we'd stolen it */
		aiocb->ki_res.res = mangle_poll(mask);
		apt.error = 0;
	पूर्ण
	spin_unlock_irq(&ctx->ctx_lock);
	अगर (mask)
		iocb_put(aiocb);
	वापस apt.error;
पूर्ण

अटल पूर्णांक __io_submit_one(काष्ठा kioctx *ctx, स्थिर काष्ठा iocb *iocb,
			   काष्ठा iocb __user *user_iocb, काष्ठा aio_kiocb *req,
			   bool compat)
अणु
	req->ki_filp = fget(iocb->aio_fildes);
	अगर (unlikely(!req->ki_filp))
		वापस -EBADF;

	अगर (iocb->aio_flags & IOCB_FLAG_RESFD) अणु
		काष्ठा eventfd_ctx *eventfd;
		/*
		 * If the IOCB_FLAG_RESFD flag of aio_flags is set, get an
		 * instance of the file* now. The file descriptor must be
		 * an eventfd() fd, and will be संकेतed क्रम each completed
		 * event using the eventfd_संकेत() function.
		 */
		eventfd = eventfd_ctx_fdget(iocb->aio_resfd);
		अगर (IS_ERR(eventfd))
			वापस PTR_ERR(eventfd);

		req->ki_eventfd = eventfd;
	पूर्ण

	अगर (unlikely(put_user(KIOCB_KEY, &user_iocb->aio_key))) अणु
		pr_debug("EFAULT: aio_key\n");
		वापस -EFAULT;
	पूर्ण

	req->ki_res.obj = (u64)(अचिन्हित दीर्घ)user_iocb;
	req->ki_res.data = iocb->aio_data;
	req->ki_res.res = 0;
	req->ki_res.res2 = 0;

	चयन (iocb->aio_lio_opcode) अणु
	हाल IOCB_CMD_PREAD:
		वापस aio_पढ़ो(&req->rw, iocb, false, compat);
	हाल IOCB_CMD_PWRITE:
		वापस aio_ग_लिखो(&req->rw, iocb, false, compat);
	हाल IOCB_CMD_PREADV:
		वापस aio_पढ़ो(&req->rw, iocb, true, compat);
	हाल IOCB_CMD_PWRITEV:
		वापस aio_ग_लिखो(&req->rw, iocb, true, compat);
	हाल IOCB_CMD_FSYNC:
		वापस aio_fsync(&req->fsync, iocb, false);
	हाल IOCB_CMD_FDSYNC:
		वापस aio_fsync(&req->fsync, iocb, true);
	हाल IOCB_CMD_POLL:
		वापस aio_poll(req, iocb);
	शेष:
		pr_debug("invalid aio operation %d\n", iocb->aio_lio_opcode);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक io_submit_one(काष्ठा kioctx *ctx, काष्ठा iocb __user *user_iocb,
			 bool compat)
अणु
	काष्ठा aio_kiocb *req;
	काष्ठा iocb iocb;
	पूर्णांक err;

	अगर (unlikely(copy_from_user(&iocb, user_iocb, माप(iocb))))
		वापस -EFAULT;

	/* enक्रमce क्रमwards compatibility on users */
	अगर (unlikely(iocb.aio_reserved2)) अणु
		pr_debug("EINVAL: reserve field set\n");
		वापस -EINVAL;
	पूर्ण

	/* prevent overflows */
	अगर (unlikely(
	    (iocb.aio_buf != (अचिन्हित दीर्घ)iocb.aio_buf) ||
	    (iocb.aio_nbytes != (माप_प्रकार)iocb.aio_nbytes) ||
	    ((sमाप_प्रकार)iocb.aio_nbytes < 0)
	   )) अणु
		pr_debug("EINVAL: overflow check\n");
		वापस -EINVAL;
	पूर्ण

	req = aio_get_req(ctx);
	अगर (unlikely(!req))
		वापस -EAGAIN;

	err = __io_submit_one(ctx, &iocb, user_iocb, req, compat);

	/* Done with the synchronous reference */
	iocb_put(req);

	/*
	 * If err is 0, we'd either करोne aio_complete() ourselves or have
	 * arranged क्रम that to be करोne asynchronously.  Anything non-zero
	 * means that we need to destroy req ourselves.
	 */
	अगर (unlikely(err)) अणु
		iocb_destroy(req);
		put_reqs_available(ctx, 1);
	पूर्ण
	वापस err;
पूर्ण

/* sys_io_submit:
 *	Queue the nr iocbs poपूर्णांकed to by iocbpp क्रम processing.  Returns
 *	the number of iocbs queued.  May वापस -EINVAL अगर the aio_context
 *	specअगरied by ctx_id is invalid, अगर nr is < 0, अगर the iocb at
 *	*iocbpp[0] is not properly initialized, अगर the operation specअगरied
 *	is invalid क्रम the file descriptor in the iocb.  May fail with
 *	-EFAULT अगर any of the data काष्ठाures poपूर्णांक to invalid data.  May
 *	fail with -EBADF अगर the file descriptor specअगरied in the first
 *	iocb is invalid.  May fail with -EAGAIN अगर insufficient resources
 *	are available to queue any iocbs.  Will वापस 0 अगर nr is 0.  Will
 *	fail with -ENOSYS अगर not implemented.
 */
SYSCALL_DEFINE3(io_submit, aio_context_t, ctx_id, दीर्घ, nr,
		काष्ठा iocb __user * __user *, iocbpp)
अणु
	काष्ठा kioctx *ctx;
	दीर्घ ret = 0;
	पूर्णांक i = 0;
	काष्ठा blk_plug plug;

	अगर (unlikely(nr < 0))
		वापस -EINVAL;

	ctx = lookup_ioctx(ctx_id);
	अगर (unlikely(!ctx)) अणु
		pr_debug("EINVAL: invalid context id\n");
		वापस -EINVAL;
	पूर्ण

	अगर (nr > ctx->nr_events)
		nr = ctx->nr_events;

	अगर (nr > AIO_PLUG_THRESHOLD)
		blk_start_plug(&plug);
	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा iocb __user *user_iocb;

		अगर (unlikely(get_user(user_iocb, iocbpp + i))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		ret = io_submit_one(ctx, user_iocb, false);
		अगर (ret)
			अवरोध;
	पूर्ण
	अगर (nr > AIO_PLUG_THRESHOLD)
		blk_finish_plug(&plug);

	percpu_ref_put(&ctx->users);
	वापस i ? i : ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE3(io_submit, compat_aio_context_t, ctx_id,
		       पूर्णांक, nr, compat_uptr_t __user *, iocbpp)
अणु
	काष्ठा kioctx *ctx;
	दीर्घ ret = 0;
	पूर्णांक i = 0;
	काष्ठा blk_plug plug;

	अगर (unlikely(nr < 0))
		वापस -EINVAL;

	ctx = lookup_ioctx(ctx_id);
	अगर (unlikely(!ctx)) अणु
		pr_debug("EINVAL: invalid context id\n");
		वापस -EINVAL;
	पूर्ण

	अगर (nr > ctx->nr_events)
		nr = ctx->nr_events;

	अगर (nr > AIO_PLUG_THRESHOLD)
		blk_start_plug(&plug);
	क्रम (i = 0; i < nr; i++) अणु
		compat_uptr_t user_iocb;

		अगर (unlikely(get_user(user_iocb, iocbpp + i))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		ret = io_submit_one(ctx, compat_ptr(user_iocb), true);
		अगर (ret)
			अवरोध;
	पूर्ण
	अगर (nr > AIO_PLUG_THRESHOLD)
		blk_finish_plug(&plug);

	percpu_ref_put(&ctx->users);
	वापस i ? i : ret;
पूर्ण
#पूर्ण_अगर

/* sys_io_cancel:
 *	Attempts to cancel an iocb previously passed to io_submit.  If
 *	the operation is successfully cancelled, the resulting event is
 *	copied पूर्णांकo the memory poपूर्णांकed to by result without being placed
 *	पूर्णांकo the completion queue and 0 is वापसed.  May fail with
 *	-EFAULT अगर any of the data काष्ठाures poपूर्णांकed to are invalid.
 *	May fail with -EINVAL अगर aio_context specअगरied by ctx_id is
 *	invalid.  May fail with -EAGAIN अगर the iocb specअगरied was not
 *	cancelled.  Will fail with -ENOSYS अगर not implemented.
 */
SYSCALL_DEFINE3(io_cancel, aio_context_t, ctx_id, काष्ठा iocb __user *, iocb,
		काष्ठा io_event __user *, result)
अणु
	काष्ठा kioctx *ctx;
	काष्ठा aio_kiocb *kiocb;
	पूर्णांक ret = -EINVAL;
	u32 key;
	u64 obj = (u64)(अचिन्हित दीर्घ)iocb;

	अगर (unlikely(get_user(key, &iocb->aio_key)))
		वापस -EFAULT;
	अगर (unlikely(key != KIOCB_KEY))
		वापस -EINVAL;

	ctx = lookup_ioctx(ctx_id);
	अगर (unlikely(!ctx))
		वापस -EINVAL;

	spin_lock_irq(&ctx->ctx_lock);
	/* TODO: use a hash or array, this sucks. */
	list_क्रम_each_entry(kiocb, &ctx->active_reqs, ki_list) अणु
		अगर (kiocb->ki_res.obj == obj) अणु
			ret = kiocb->ki_cancel(&kiocb->rw);
			list_del_init(&kiocb->ki_list);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&ctx->ctx_lock);

	अगर (!ret) अणु
		/*
		 * The result argument is no दीर्घer used - the io_event is
		 * always delivered via the ring buffer. -EINPROGRESS indicates
		 * cancellation is progress:
		 */
		ret = -EINPROGRESS;
	पूर्ण

	percpu_ref_put(&ctx->users);

	वापस ret;
पूर्ण

अटल दीर्घ करो_io_getevents(aio_context_t ctx_id,
		दीर्घ min_nr,
		दीर्घ nr,
		काष्ठा io_event __user *events,
		काष्ठा बारpec64 *ts)
अणु
	kसमय_प्रकार until = ts ? बारpec64_to_kसमय(*ts) : KTIME_MAX;
	काष्ठा kioctx *ioctx = lookup_ioctx(ctx_id);
	दीर्घ ret = -EINVAL;

	अगर (likely(ioctx)) अणु
		अगर (likely(min_nr <= nr && min_nr >= 0))
			ret = पढ़ो_events(ioctx, min_nr, nr, events, until);
		percpu_ref_put(&ioctx->users);
	पूर्ण

	वापस ret;
पूर्ण

/* io_getevents:
 *	Attempts to पढ़ो at least min_nr events and up to nr events from
 *	the completion queue क्रम the aio_context specअगरied by ctx_id. If
 *	it succeeds, the number of पढ़ो events is वापसed. May fail with
 *	-EINVAL अगर ctx_id is invalid, अगर min_nr is out of range, अगर nr is
 *	out of range, अगर समयout is out of range.  May fail with -EFAULT
 *	अगर any of the memory specअगरied is invalid.  May वापस 0 or
 *	< min_nr अगर the समयout specअगरied by समयout has elapsed
 *	beक्रमe sufficient events are available, where समयout == शून्य
 *	specअगरies an infinite समयout. Note that the समयout poपूर्णांकed to by
 *	समयout is relative.  Will fail with -ENOSYS अगर not implemented.
 */
#अगर_घोषित CONFIG_64BIT

SYSCALL_DEFINE5(io_getevents, aio_context_t, ctx_id,
		दीर्घ, min_nr,
		दीर्घ, nr,
		काष्ठा io_event __user *, events,
		काष्ठा __kernel_बारpec __user *, समयout)
अणु
	काष्ठा बारpec64	ts;
	पूर्णांक			ret;

	अगर (समयout && unlikely(get_बारpec64(&ts, समयout)))
		वापस -EFAULT;

	ret = करो_io_getevents(ctx_id, min_nr, nr, events, समयout ? &ts : शून्य);
	अगर (!ret && संकेत_pending(current))
		ret = -EINTR;
	वापस ret;
पूर्ण

#पूर्ण_अगर

काष्ठा __aio_sigset अणु
	स्थिर sigset_t __user	*sigmask;
	माप_प्रकार		sigsetsize;
पूर्ण;

SYSCALL_DEFINE6(io_pgetevents,
		aio_context_t, ctx_id,
		दीर्घ, min_nr,
		दीर्घ, nr,
		काष्ठा io_event __user *, events,
		काष्ठा __kernel_बारpec __user *, समयout,
		स्थिर काष्ठा __aio_sigset __user *, usig)
अणु
	काष्ठा __aio_sigset	ksig = अणु शून्य, पूर्ण;
	काष्ठा बारpec64	ts;
	bool पूर्णांकerrupted;
	पूर्णांक ret;

	अगर (समयout && unlikely(get_बारpec64(&ts, समयout)))
		वापस -EFAULT;

	अगर (usig && copy_from_user(&ksig, usig, माप(ksig)))
		वापस -EFAULT;

	ret = set_user_sigmask(ksig.sigmask, ksig.sigsetsize);
	अगर (ret)
		वापस ret;

	ret = करो_io_getevents(ctx_id, min_nr, nr, events, समयout ? &ts : शून्य);

	पूर्णांकerrupted = संकेत_pending(current);
	restore_saved_sigmask_unless(पूर्णांकerrupted);
	अगर (पूर्णांकerrupted && !ret)
		ret = -ERESTARTNOHAND;

	वापस ret;
पूर्ण

#अगर defined(CONFIG_COMPAT_32BIT_TIME) && !defined(CONFIG_64BIT)

SYSCALL_DEFINE6(io_pgetevents_समय32,
		aio_context_t, ctx_id,
		दीर्घ, min_nr,
		दीर्घ, nr,
		काष्ठा io_event __user *, events,
		काष्ठा old_बारpec32 __user *, समयout,
		स्थिर काष्ठा __aio_sigset __user *, usig)
अणु
	काष्ठा __aio_sigset	ksig = अणु शून्य, पूर्ण;
	काष्ठा बारpec64	ts;
	bool पूर्णांकerrupted;
	पूर्णांक ret;

	अगर (समयout && unlikely(get_old_बारpec32(&ts, समयout)))
		वापस -EFAULT;

	अगर (usig && copy_from_user(&ksig, usig, माप(ksig)))
		वापस -EFAULT;


	ret = set_user_sigmask(ksig.sigmask, ksig.sigsetsize);
	अगर (ret)
		वापस ret;

	ret = करो_io_getevents(ctx_id, min_nr, nr, events, समयout ? &ts : शून्य);

	पूर्णांकerrupted = संकेत_pending(current);
	restore_saved_sigmask_unless(पूर्णांकerrupted);
	अगर (पूर्णांकerrupted && !ret)
		ret = -ERESTARTNOHAND;

	वापस ret;
पूर्ण

#पूर्ण_अगर

#अगर defined(CONFIG_COMPAT_32BIT_TIME)

SYSCALL_DEFINE5(io_getevents_समय32, __u32, ctx_id,
		__s32, min_nr,
		__s32, nr,
		काष्ठा io_event __user *, events,
		काष्ठा old_बारpec32 __user *, समयout)
अणु
	काष्ठा बारpec64 t;
	पूर्णांक ret;

	अगर (समयout && get_old_बारpec32(&t, समयout))
		वापस -EFAULT;

	ret = करो_io_getevents(ctx_id, min_nr, nr, events, समयout ? &t : शून्य);
	अगर (!ret && संकेत_pending(current))
		ret = -EINTR;
	वापस ret;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT

काष्ठा __compat_aio_sigset अणु
	compat_uptr_t		sigmask;
	compat_माप_प्रकार		sigsetsize;
पूर्ण;

#अगर defined(CONFIG_COMPAT_32BIT_TIME)

COMPAT_SYSCALL_DEFINE6(io_pgetevents,
		compat_aio_context_t, ctx_id,
		compat_दीर्घ_t, min_nr,
		compat_दीर्घ_t, nr,
		काष्ठा io_event __user *, events,
		काष्ठा old_बारpec32 __user *, समयout,
		स्थिर काष्ठा __compat_aio_sigset __user *, usig)
अणु
	काष्ठा __compat_aio_sigset ksig = अणु 0, पूर्ण;
	काष्ठा बारpec64 t;
	bool पूर्णांकerrupted;
	पूर्णांक ret;

	अगर (समयout && get_old_बारpec32(&t, समयout))
		वापस -EFAULT;

	अगर (usig && copy_from_user(&ksig, usig, माप(ksig)))
		वापस -EFAULT;

	ret = set_compat_user_sigmask(compat_ptr(ksig.sigmask), ksig.sigsetsize);
	अगर (ret)
		वापस ret;

	ret = करो_io_getevents(ctx_id, min_nr, nr, events, समयout ? &t : शून्य);

	पूर्णांकerrupted = संकेत_pending(current);
	restore_saved_sigmask_unless(पूर्णांकerrupted);
	अगर (पूर्णांकerrupted && !ret)
		ret = -ERESTARTNOHAND;

	वापस ret;
पूर्ण

#पूर्ण_अगर

COMPAT_SYSCALL_DEFINE6(io_pgetevents_समय64,
		compat_aio_context_t, ctx_id,
		compat_दीर्घ_t, min_nr,
		compat_दीर्घ_t, nr,
		काष्ठा io_event __user *, events,
		काष्ठा __kernel_बारpec __user *, समयout,
		स्थिर काष्ठा __compat_aio_sigset __user *, usig)
अणु
	काष्ठा __compat_aio_sigset ksig = अणु 0, पूर्ण;
	काष्ठा बारpec64 t;
	bool पूर्णांकerrupted;
	पूर्णांक ret;

	अगर (समयout && get_बारpec64(&t, समयout))
		वापस -EFAULT;

	अगर (usig && copy_from_user(&ksig, usig, माप(ksig)))
		वापस -EFAULT;

	ret = set_compat_user_sigmask(compat_ptr(ksig.sigmask), ksig.sigsetsize);
	अगर (ret)
		वापस ret;

	ret = करो_io_getevents(ctx_id, min_nr, nr, events, समयout ? &t : शून्य);

	पूर्णांकerrupted = संकेत_pending(current);
	restore_saved_sigmask_unless(पूर्णांकerrupted);
	अगर (पूर्णांकerrupted && !ret)
		ret = -ERESTARTNOHAND;

	वापस ret;
पूर्ण
#पूर्ण_अगर
