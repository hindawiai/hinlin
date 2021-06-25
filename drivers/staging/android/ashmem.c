<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* mm/ashmem.c
 *
 * Anonymous Shared Memory Subप्रणाली, ashmem
 *
 * Copyright (C) 2008 Google, Inc.
 *
 * Robert Love <rlove@google.com>
 */

#घोषणा pr_fmt(fmt) "ashmem: " fmt

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/security.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/personality.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/shmem_fs.h>
#समावेश "ashmem.h"

#घोषणा ASHMEM_NAME_PREFIX "dev/ashmem/"
#घोषणा ASHMEM_NAME_PREFIX_LEN (माप(ASHMEM_NAME_PREFIX) - 1)
#घोषणा ASHMEM_FULL_NAME_LEN (ASHMEM_NAME_LEN + ASHMEM_NAME_PREFIX_LEN)

/**
 * काष्ठा ashmem_area - The anonymous shared memory area
 * @name:		The optional name in /proc/pid/maps
 * @unpinned_list:	The list of all ashmem areas
 * @file:		The shmem-based backing file
 * @size:		The size of the mapping, in bytes
 * @prot_mask:		The allowed protection bits, as vm_flags
 *
 * The lअगरecycle of this काष्ठाure is from our parent file's खोलो() until
 * its release(). It is also रक्षित by 'ashmem_mutex'
 *
 * Warning: Mappings करो NOT pin this काष्ठाure; It dies on बंद()
 */
काष्ठा ashmem_area अणु
	अक्षर name[ASHMEM_FULL_NAME_LEN];
	काष्ठा list_head unpinned_list;
	काष्ठा file *file;
	माप_प्रकार size;
	अचिन्हित दीर्घ prot_mask;
पूर्ण;

/**
 * काष्ठा ashmem_range - A range of unpinned/evictable pages
 * @lru:	         The entry in the LRU list
 * @unpinned:	         The entry in its area's unpinned list
 * @यंत्रa:	         The associated anonymous shared memory area.
 * @pgstart:	         The starting page (inclusive)
 * @pgend:	         The ending page (inclusive)
 * @purged:	         The purge status (ASHMEM_NOT or ASHMEM_WAS_PURGED)
 *
 * The lअगरecycle of this काष्ठाure is from unpin to pin.
 * It is रक्षित by 'ashmem_mutex'
 */
काष्ठा ashmem_range अणु
	काष्ठा list_head lru;
	काष्ठा list_head unpinned;
	काष्ठा ashmem_area *यंत्रa;
	माप_प्रकार pgstart;
	माप_प्रकार pgend;
	अचिन्हित पूर्णांक purged;
पूर्ण;

/* LRU list of unpinned pages, रक्षित by ashmem_mutex */
अटल LIST_HEAD(ashmem_lru_list);

अटल atomic_t ashmem_shrink_inflight = ATOMIC_INIT(0);
अटल DECLARE_WAIT_QUEUE_HEAD(ashmem_shrink_रुको);

/*
 * दीर्घ lru_count - The count of pages on our LRU list.
 *
 * This is रक्षित by ashmem_mutex.
 */
अटल अचिन्हित दीर्घ lru_count;

/*
 * ashmem_mutex - protects the list of and each inभागidual ashmem_area
 *
 * Lock Ordering: ashmex_mutex -> i_mutex -> i_alloc_sem
 */
अटल DEFINE_MUTEX(ashmem_mutex);

अटल काष्ठा kmem_cache *ashmem_area_cachep __पढ़ो_mostly;
अटल काष्ठा kmem_cache *ashmem_range_cachep __पढ़ो_mostly;

/*
 * A separate lockdep class क्रम the backing shmem inodes to resolve the lockdep
 * warning about the race between kswapd taking fs_reclaim beक्रमe inode_lock
 * and ग_लिखो syscall taking inode_lock and then fs_reclaim.
 * Note that such race is impossible because ashmem करोes not support ग_लिखो
 * syscalls operating on the backing shmem.
 */
अटल काष्ठा lock_class_key backing_shmem_inode_class;

अटल अंतरभूत अचिन्हित दीर्घ range_size(काष्ठा ashmem_range *range)
अणु
	वापस range->pgend - range->pgstart + 1;
पूर्ण

अटल अंतरभूत bool range_on_lru(काष्ठा ashmem_range *range)
अणु
	वापस range->purged == ASHMEM_NOT_PURGED;
पूर्ण

अटल अंतरभूत bool page_range_subsumes_range(काष्ठा ashmem_range *range,
					     माप_प्रकार start, माप_प्रकार end)
अणु
	वापस (range->pgstart >= start) && (range->pgend <= end);
पूर्ण

अटल अंतरभूत bool page_range_subsumed_by_range(काष्ठा ashmem_range *range,
						माप_प्रकार start, माप_प्रकार end)
अणु
	वापस (range->pgstart <= start) && (range->pgend >= end);
पूर्ण

अटल अंतरभूत bool page_in_range(काष्ठा ashmem_range *range, माप_प्रकार page)
अणु
	वापस (range->pgstart <= page) && (range->pgend >= page);
पूर्ण

अटल अंतरभूत bool page_range_in_range(काष्ठा ashmem_range *range,
				       माप_प्रकार start, माप_प्रकार end)
अणु
	वापस page_in_range(range, start) || page_in_range(range, end) ||
		page_range_subsumes_range(range, start, end);
पूर्ण

अटल अंतरभूत bool range_beक्रमe_page(काष्ठा ashmem_range *range,
				     माप_प्रकार page)
अणु
	वापस range->pgend < page;
पूर्ण

#घोषणा PROT_MASK		(PROT_EXEC | PROT_READ | PROT_WRITE)

/**
 * lru_add() - Adds a range of memory to the LRU list
 * @range:     The memory range being added.
 *
 * The range is first added to the end (tail) of the LRU list.
 * After this, the size of the range is added to @lru_count
 */
अटल अंतरभूत व्योम lru_add(काष्ठा ashmem_range *range)
अणु
	list_add_tail(&range->lru, &ashmem_lru_list);
	lru_count += range_size(range);
पूर्ण

/**
 * lru_del() - Removes a range of memory from the LRU list
 * @range:     The memory range being हटाओd
 *
 * The range is first deleted from the LRU list.
 * After this, the size of the range is हटाओd from @lru_count
 */
अटल अंतरभूत व्योम lru_del(काष्ठा ashmem_range *range)
अणु
	list_del(&range->lru);
	lru_count -= range_size(range);
पूर्ण

/**
 * range_alloc() - Allocates and initializes a new ashmem_range काष्ठाure
 * @यंत्रa:	   The associated ashmem_area
 * @prev_range:	   The previous ashmem_range in the sorted यंत्रa->unpinned list
 * @purged:	   Initial purge status (ASMEM_NOT_PURGED or ASHMEM_WAS_PURGED)
 * @start:	   The starting page (inclusive)
 * @end:	   The ending page (inclusive)
 *
 * This function is रक्षित by ashmem_mutex.
 */
अटल व्योम range_alloc(काष्ठा ashmem_area *यंत्रa,
			काष्ठा ashmem_range *prev_range, अचिन्हित पूर्णांक purged,
			माप_प्रकार start, माप_प्रकार end,
			काष्ठा ashmem_range **new_range)
अणु
	काष्ठा ashmem_range *range = *new_range;

	*new_range = शून्य;
	range->यंत्रa = यंत्रa;
	range->pgstart = start;
	range->pgend = end;
	range->purged = purged;

	list_add_tail(&range->unpinned, &prev_range->unpinned);

	अगर (range_on_lru(range))
		lru_add(range);
पूर्ण

/**
 * range_del() - Deletes and deallocates an ashmem_range काष्ठाure
 * @range:	 The associated ashmem_range that has previously been allocated
 */
अटल व्योम range_del(काष्ठा ashmem_range *range)
अणु
	list_del(&range->unpinned);
	अगर (range_on_lru(range))
		lru_del(range);
	kmem_cache_मुक्त(ashmem_range_cachep, range);
पूर्ण

/**
 * range_shrink() - Shrinks an ashmem_range
 * @range:	    The associated ashmem_range being shrunk
 * @start:	    The starting byte of the new range
 * @end:	    The ending byte of the new range
 *
 * This करोes not modअगरy the data inside the existing range in any way - It
 * simply shrinks the boundaries of the range.
 *
 * Theoretically, with a little tweaking, this could eventually be changed
 * to range_resize, and expand the lru_count अगर the new range is larger.
 */
अटल अंतरभूत व्योम range_shrink(काष्ठा ashmem_range *range,
				माप_प्रकार start, माप_प्रकार end)
अणु
	माप_प्रकार pre = range_size(range);

	range->pgstart = start;
	range->pgend = end;

	अगर (range_on_lru(range))
		lru_count -= pre - range_size(range);
पूर्ण

/**
 * ashmem_खोलो() - Opens an Anonymous Shared Memory काष्ठाure
 * @inode:	   The backing file's index node(?)
 * @file:	   The backing file
 *
 * Please note that the ashmem_area is not वापसed by this function - It is
 * instead written to "file->private_data".
 *
 * Return: 0 अगर successful, or another code अगर unsuccessful.
 */
अटल पूर्णांक ashmem_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ashmem_area *यंत्रa;
	पूर्णांक ret;

	ret = generic_file_खोलो(inode, file);
	अगर (ret)
		वापस ret;

	यंत्रa = kmem_cache_zalloc(ashmem_area_cachep, GFP_KERNEL);
	अगर (!यंत्रa)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&यंत्रa->unpinned_list);
	स_नकल(यंत्रa->name, ASHMEM_NAME_PREFIX, ASHMEM_NAME_PREFIX_LEN);
	यंत्रa->prot_mask = PROT_MASK;
	file->निजी_data = यंत्रa;

	वापस 0;
पूर्ण

/**
 * ashmem_release() - Releases an Anonymous Shared Memory काष्ठाure
 * @ignored:	      The backing file's Index Node(?) - It is ignored here.
 * @file:	      The backing file
 *
 * Return: 0 अगर successful. If it is anything अन्यथा, go have a coffee and
 * try again.
 */
अटल पूर्णांक ashmem_release(काष्ठा inode *ignored, काष्ठा file *file)
अणु
	काष्ठा ashmem_area *यंत्रa = file->निजी_data;
	काष्ठा ashmem_range *range, *next;

	mutex_lock(&ashmem_mutex);
	list_क्रम_each_entry_safe(range, next, &यंत्रa->unpinned_list, unpinned)
		range_del(range);
	mutex_unlock(&ashmem_mutex);

	अगर (यंत्रa->file)
		fput(यंत्रa->file);
	kmem_cache_मुक्त(ashmem_area_cachep, यंत्रa);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ashmem_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा ashmem_area *यंत्रa = iocb->ki_filp->निजी_data;
	पूर्णांक ret = 0;

	mutex_lock(&ashmem_mutex);

	/* If size is not set, or set to 0, always वापस खातापूर्ण. */
	अगर (यंत्रa->size == 0)
		जाओ out_unlock;

	अगर (!यंत्रa->file) अणु
		ret = -EBADF;
		जाओ out_unlock;
	पूर्ण

	/*
	 * यंत्रa and यंत्रa->file are used outside the lock here.  We assume
	 * once यंत्रa->file is set it will never be changed, and will not
	 * be destroyed until all references to the file are dropped and
	 * ashmem_release is called.
	 */
	mutex_unlock(&ashmem_mutex);
	ret = vfs_iter_पढ़ो(यंत्रa->file, iter, &iocb->ki_pos, 0);
	mutex_lock(&ashmem_mutex);
	अगर (ret > 0)
		यंत्रa->file->f_pos = iocb->ki_pos;
out_unlock:
	mutex_unlock(&ashmem_mutex);
	वापस ret;
पूर्ण

अटल loff_t ashmem_llseek(काष्ठा file *file, loff_t offset, पूर्णांक origin)
अणु
	काष्ठा ashmem_area *यंत्रa = file->निजी_data;
	loff_t ret;

	mutex_lock(&ashmem_mutex);

	अगर (यंत्रa->size == 0) अणु
		mutex_unlock(&ashmem_mutex);
		वापस -EINVAL;
	पूर्ण

	अगर (!यंत्रa->file) अणु
		mutex_unlock(&ashmem_mutex);
		वापस -EBADF;
	पूर्ण

	mutex_unlock(&ashmem_mutex);

	ret = vfs_llseek(यंत्रa->file, offset, origin);
	अगर (ret < 0)
		वापस ret;

	/** Copy f_pos from backing file, since f_ops->llseek() sets it */
	file->f_pos = यंत्रa->file->f_pos;
	वापस ret;
पूर्ण

अटल अंतरभूत vm_flags_t calc_vm_may_flags(अचिन्हित दीर्घ prot)
अणु
	वापस _calc_vm_trans(prot, PROT_READ,  VM_MAYREAD) |
	       _calc_vm_trans(prot, PROT_WRITE, VM_MAYWRITE) |
	       _calc_vm_trans(prot, PROT_EXEC,  VM_MAYEXEC);
पूर्ण

अटल पूर्णांक ashmem_vmfile_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	/* करो not allow to mmap ashmem backing shmem file directly */
	वापस -EPERM;
पूर्ण

अटल अचिन्हित दीर्घ
ashmem_vmfile_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
				अचिन्हित दीर्घ flags)
अणु
	वापस current->mm->get_unmapped_area(file, addr, len, pgoff, flags);
पूर्ण

अटल पूर्णांक ashmem_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अटल काष्ठा file_operations vmfile_fops;
	काष्ठा ashmem_area *यंत्रa = file->निजी_data;
	पूर्णांक ret = 0;

	mutex_lock(&ashmem_mutex);

	/* user needs to SET_SIZE beक्रमe mapping */
	अगर (!यंत्रa->size) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* requested mapping size larger than object size */
	अगर (vma->vm_end - vma->vm_start > PAGE_ALIGN(यंत्रa->size)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* requested protection bits must match our allowed protection mask */
	अगर ((vma->vm_flags & ~calc_vm_prot_bits(यंत्रa->prot_mask, 0)) &
	    calc_vm_prot_bits(PROT_MASK, 0)) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण
	vma->vm_flags &= ~calc_vm_may_flags(~यंत्रa->prot_mask);

	अगर (!यंत्रa->file) अणु
		अक्षर *name = ASHMEM_NAME_DEF;
		काष्ठा file *vmfile;
		काष्ठा inode *inode;

		अगर (यंत्रa->name[ASHMEM_NAME_PREFIX_LEN] != '\0')
			name = यंत्रa->name;

		/* ... and allocate the backing shmem file */
		vmfile = shmem_file_setup(name, यंत्रa->size, vma->vm_flags);
		अगर (IS_ERR(vmfile)) अणु
			ret = PTR_ERR(vmfile);
			जाओ out;
		पूर्ण
		vmfile->f_mode |= FMODE_LSEEK;
		inode = file_inode(vmfile);
		lockdep_set_class(&inode->i_rwsem, &backing_shmem_inode_class);
		यंत्रa->file = vmfile;
		/*
		 * override mmap operation of the vmfile so that it can't be
		 * remapped which would lead to creation of a new vma with no
		 * यंत्रa permission checks. Have to override get_unmapped_area
		 * as well to prevent VM_BUG_ON check क्रम f_ops modअगरication.
		 */
		अगर (!vmfile_fops.mmap) अणु
			vmfile_fops = *vmfile->f_op;
			vmfile_fops.mmap = ashmem_vmfile_mmap;
			vmfile_fops.get_unmapped_area =
					ashmem_vmfile_get_unmapped_area;
		पूर्ण
		vmfile->f_op = &vmfile_fops;
	पूर्ण
	get_file(यंत्रa->file);

	/*
	 * XXX - Reworked to use shmem_zero_setup() instead of
	 * shmem_set_file जबतक we're in staging. -jstultz
	 */
	अगर (vma->vm_flags & VM_SHARED) अणु
		ret = shmem_zero_setup(vma);
		अगर (ret) अणु
			fput(यंत्रa->file);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		vma_set_anonymous(vma);
	पूर्ण

	vma_set_file(vma, यंत्रa->file);
	/* XXX: merge this with the get_file() above अगर possible */
	fput(यंत्रa->file);

out:
	mutex_unlock(&ashmem_mutex);
	वापस ret;
पूर्ण

/*
 * ashmem_shrink - our cache shrinker, called from mm/vmscan.c
 *
 * 'nr_to_scan' is the number of objects to scan क्रम मुक्तing.
 *
 * 'gfp_mask' is the mask of the allocation that got us पूर्णांकo this mess.
 *
 * Return value is the number of objects मुक्तd or -1 अगर we cannot
 * proceed without risk of deadlock (due to gfp_mask).
 *
 * We approximate LRU via least-recently-unpinned, jettisoning unpinned partial
 * chunks of ashmem regions LRU-wise one-at-a-समय until we hit 'nr_to_scan'
 * pages मुक्तd.
 */
अटल अचिन्हित दीर्घ
ashmem_shrink_scan(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	अचिन्हित दीर्घ मुक्तd = 0;

	/* We might recurse पूर्णांकo fileप्रणाली code, so bail out अगर necessary */
	अगर (!(sc->gfp_mask & __GFP_FS))
		वापस SHRINK_STOP;

	अगर (!mutex_trylock(&ashmem_mutex))
		वापस -1;

	जबतक (!list_empty(&ashmem_lru_list)) अणु
		काष्ठा ashmem_range *range =
			list_first_entry(&ashmem_lru_list, typeof(*range), lru);
		loff_t start = range->pgstart * PAGE_SIZE;
		loff_t end = (range->pgend + 1) * PAGE_SIZE;
		काष्ठा file *f = range->यंत्रa->file;

		get_file(f);
		atomic_inc(&ashmem_shrink_inflight);
		range->purged = ASHMEM_WAS_PURGED;
		lru_del(range);

		मुक्तd += range_size(range);
		mutex_unlock(&ashmem_mutex);
		f->f_op->fallocate(f,
				   FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE,
				   start, end - start);
		fput(f);
		अगर (atomic_dec_and_test(&ashmem_shrink_inflight))
			wake_up_all(&ashmem_shrink_रुको);
		अगर (!mutex_trylock(&ashmem_mutex))
			जाओ out;
		अगर (--sc->nr_to_scan <= 0)
			अवरोध;
	पूर्ण
	mutex_unlock(&ashmem_mutex);
out:
	वापस मुक्तd;
पूर्ण

अटल अचिन्हित दीर्घ
ashmem_shrink_count(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	/*
	 * note that lru_count is count of pages on the lru, not a count of
	 * objects on the list. This means the scan function needs to वापस the
	 * number of pages मुक्तd, not the number of objects scanned.
	 */
	वापस lru_count;
पूर्ण

अटल काष्ठा shrinker ashmem_shrinker = अणु
	.count_objects = ashmem_shrink_count,
	.scan_objects = ashmem_shrink_scan,
	/*
	 * XXX (dchinner): I wish people would comment on why they need on
	 * signअगरicant changes to the शेष value here
	 */
	.seeks = DEFAULT_SEEKS * 4,
पूर्ण;

अटल पूर्णांक set_prot_mask(काष्ठा ashmem_area *यंत्रa, अचिन्हित दीर्घ prot)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&ashmem_mutex);

	/* the user can only हटाओ, not add, protection bits */
	अगर ((यंत्रa->prot_mask & prot) != prot) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* करोes the application expect PROT_READ to imply PROT_EXEC? */
	अगर ((prot & PROT_READ) && (current->personality & READ_IMPLIES_EXEC))
		prot |= PROT_EXEC;

	यंत्रa->prot_mask = prot;

out:
	mutex_unlock(&ashmem_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक set_name(काष्ठा ashmem_area *यंत्रa, व्योम __user *name)
अणु
	पूर्णांक len;
	पूर्णांक ret = 0;
	अक्षर local_name[ASHMEM_NAME_LEN];

	/*
	 * Holding the ashmem_mutex जबतक करोing a copy_from_user might cause
	 * an data पात which would try to access mmap_lock. If another
	 * thपढ़ो has invoked ashmem_mmap then it will be holding the
	 * semaphore and will be रुकोing क्रम ashmem_mutex, there by leading to
	 * deadlock. We'll release the mutex and take the name to a local
	 * variable that करोes not need protection and later copy the local
	 * variable to the काष्ठाure member with lock held.
	 */
	len = म_नकलन_from_user(local_name, name, ASHMEM_NAME_LEN);
	अगर (len < 0)
		वापस len;

	mutex_lock(&ashmem_mutex);
	/* cannot change an existing mapping's name */
	अगर (यंत्रa->file)
		ret = -EINVAL;
	अन्यथा
		strscpy(यंत्रa->name + ASHMEM_NAME_PREFIX_LEN, local_name,
			ASHMEM_NAME_LEN);

	mutex_unlock(&ashmem_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक get_name(काष्ठा ashmem_area *यंत्रa, व्योम __user *name)
अणु
	पूर्णांक ret = 0;
	माप_प्रकार len;
	/*
	 * Have a local variable to which we'll copy the content
	 * from यंत्रa with the lock held. Later we can copy this to the user
	 * space safely without holding any locks. So even अगर we proceed to
	 * रुको क्रम mmap_lock, it won't lead to deadlock.
	 */
	अक्षर local_name[ASHMEM_NAME_LEN];

	mutex_lock(&ashmem_mutex);
	अगर (यंत्रa->name[ASHMEM_NAME_PREFIX_LEN] != '\0') अणु
		/*
		 * Copying only `len', instead of ASHMEM_NAME_LEN, bytes
		 * prevents us from revealing one user's stack to another.
		 */
		len = म_माप(यंत्रa->name + ASHMEM_NAME_PREFIX_LEN) + 1;
		स_नकल(local_name, यंत्रa->name + ASHMEM_NAME_PREFIX_LEN, len);
	पूर्ण अन्यथा अणु
		len = माप(ASHMEM_NAME_DEF);
		स_नकल(local_name, ASHMEM_NAME_DEF, len);
	पूर्ण
	mutex_unlock(&ashmem_mutex);

	/*
	 * Now we are just copying from the stack variable to userland
	 * No lock held
	 */
	अगर (copy_to_user(name, local_name, len))
		ret = -EFAULT;
	वापस ret;
पूर्ण

/*
 * ashmem_pin - pin the given ashmem region, वापसing whether it was
 * previously purged (ASHMEM_WAS_PURGED) or not (ASHMEM_NOT_PURGED).
 *
 * Caller must hold ashmem_mutex.
 */
अटल पूर्णांक ashmem_pin(काष्ठा ashmem_area *यंत्रa, माप_प्रकार pgstart, माप_प्रकार pgend,
		      काष्ठा ashmem_range **new_range)
अणु
	काष्ठा ashmem_range *range, *next;
	पूर्णांक ret = ASHMEM_NOT_PURGED;

	list_क्रम_each_entry_safe(range, next, &यंत्रa->unpinned_list, unpinned) अणु
		/* moved past last applicable page; we can लघु circuit */
		अगर (range_beक्रमe_page(range, pgstart))
			अवरोध;

		/*
		 * The user can ask us to pin pages that span multiple ranges,
		 * or to pin pages that aren't even unpinned, so this is messy.
		 *
		 * Four हालs:
		 * 1. The requested range subsumes an existing range, so we
		 *    just हटाओ the entire matching range.
		 * 2. The requested range overlaps the start of an existing
		 *    range, so we just update that range.
		 * 3. The requested range overlaps the end of an existing
		 *    range, so we just update that range.
		 * 4. The requested range punches a hole in an existing range,
		 *    so we have to update one side of the range and then
		 *    create a new range क्रम the other side.
		 */
		अगर (page_range_in_range(range, pgstart, pgend)) अणु
			ret |= range->purged;

			/* Case #1: Easy. Just nuke the whole thing. */
			अगर (page_range_subsumes_range(range, pgstart, pgend)) अणु
				range_del(range);
				जारी;
			पूर्ण

			/* Case #2: We overlap from the start, so adjust it */
			अगर (range->pgstart >= pgstart) अणु
				range_shrink(range, pgend + 1, range->pgend);
				जारी;
			पूर्ण

			/* Case #3: We overlap from the rear, so adjust it */
			अगर (range->pgend <= pgend) अणु
				range_shrink(range, range->pgstart,
					     pgstart - 1);
				जारी;
			पूर्ण

			/*
			 * Case #4: We eat a chunk out of the middle. A bit
			 * more complicated, we allocate a new range क्रम the
			 * second half and adjust the first chunk's endpoपूर्णांक.
			 */
			range_alloc(यंत्रa, range, range->purged,
				    pgend + 1, range->pgend, new_range);
			range_shrink(range, range->pgstart, pgstart - 1);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * ashmem_unpin - unpin the given range of pages. Returns zero on success.
 *
 * Caller must hold ashmem_mutex.
 */
अटल पूर्णांक ashmem_unpin(काष्ठा ashmem_area *यंत्रa, माप_प्रकार pgstart, माप_प्रकार pgend,
			काष्ठा ashmem_range **new_range)
अणु
	काष्ठा ashmem_range *range, *next;
	अचिन्हित पूर्णांक purged = ASHMEM_NOT_PURGED;

restart:
	list_क्रम_each_entry_safe(range, next, &यंत्रa->unpinned_list, unpinned) अणु
		/* लघु circuit: this is our insertion poपूर्णांक */
		अगर (range_beक्रमe_page(range, pgstart))
			अवरोध;

		/*
		 * The user can ask us to unpin pages that are alपढ़ोy entirely
		 * or partially pinned. We handle those two हालs here.
		 */
		अगर (page_range_subsumed_by_range(range, pgstart, pgend))
			वापस 0;
		अगर (page_range_in_range(range, pgstart, pgend)) अणु
			pgstart = min(range->pgstart, pgstart);
			pgend = max(range->pgend, pgend);
			purged |= range->purged;
			range_del(range);
			जाओ restart;
		पूर्ण
	पूर्ण

	range_alloc(यंत्रa, range, purged, pgstart, pgend, new_range);
	वापस 0;
पूर्ण

/*
 * ashmem_get_pin_status - Returns ASHMEM_IS_UNPINNED अगर _any_ pages in the
 * given पूर्णांकerval are unpinned and ASHMEM_IS_PINNED otherwise.
 *
 * Caller must hold ashmem_mutex.
 */
अटल पूर्णांक ashmem_get_pin_status(काष्ठा ashmem_area *यंत्रa, माप_प्रकार pgstart,
				 माप_प्रकार pgend)
अणु
	काष्ठा ashmem_range *range;
	पूर्णांक ret = ASHMEM_IS_PINNED;

	list_क्रम_each_entry(range, &यंत्रa->unpinned_list, unpinned) अणु
		अगर (range_beक्रमe_page(range, pgstart))
			अवरोध;
		अगर (page_range_in_range(range, pgstart, pgend)) अणु
			ret = ASHMEM_IS_UNPINNED;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ashmem_pin_unpin(काष्ठा ashmem_area *यंत्रa, अचिन्हित दीर्घ cmd,
			    व्योम __user *p)
अणु
	काष्ठा ashmem_pin pin;
	माप_प्रकार pgstart, pgend;
	पूर्णांक ret = -EINVAL;
	काष्ठा ashmem_range *range = शून्य;

	अगर (copy_from_user(&pin, p, माप(pin)))
		वापस -EFAULT;

	अगर (cmd == ASHMEM_PIN || cmd == ASHMEM_UNPIN) अणु
		range = kmem_cache_zalloc(ashmem_range_cachep, GFP_KERNEL);
		अगर (!range)
			वापस -ENOMEM;
	पूर्ण

	mutex_lock(&ashmem_mutex);
	रुको_event(ashmem_shrink_रुको, !atomic_पढ़ो(&ashmem_shrink_inflight));

	अगर (!यंत्रa->file)
		जाओ out_unlock;

	/* per custom, you can pass zero क्रम len to mean "everything onward" */
	अगर (!pin.len)
		pin.len = PAGE_ALIGN(यंत्रa->size) - pin.offset;

	अगर ((pin.offset | pin.len) & ~PAGE_MASK)
		जाओ out_unlock;

	अगर (((__u32)-1) - pin.offset < pin.len)
		जाओ out_unlock;

	अगर (PAGE_ALIGN(यंत्रa->size) < pin.offset + pin.len)
		जाओ out_unlock;

	pgstart = pin.offset / PAGE_SIZE;
	pgend = pgstart + (pin.len / PAGE_SIZE) - 1;

	चयन (cmd) अणु
	हाल ASHMEM_PIN:
		ret = ashmem_pin(यंत्रa, pgstart, pgend, &range);
		अवरोध;
	हाल ASHMEM_UNPIN:
		ret = ashmem_unpin(यंत्रa, pgstart, pgend, &range);
		अवरोध;
	हाल ASHMEM_GET_PIN_STATUS:
		ret = ashmem_get_pin_status(यंत्रa, pgstart, pgend);
		अवरोध;
	पूर्ण

out_unlock:
	mutex_unlock(&ashmem_mutex);
	अगर (range)
		kmem_cache_मुक्त(ashmem_range_cachep, range);

	वापस ret;
पूर्ण

अटल दीर्घ ashmem_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ashmem_area *यंत्रa = file->निजी_data;
	दीर्घ ret = -ENOTTY;

	चयन (cmd) अणु
	हाल ASHMEM_SET_NAME:
		ret = set_name(यंत्रa, (व्योम __user *)arg);
		अवरोध;
	हाल ASHMEM_GET_NAME:
		ret = get_name(यंत्रa, (व्योम __user *)arg);
		अवरोध;
	हाल ASHMEM_SET_SIZE:
		ret = -EINVAL;
		mutex_lock(&ashmem_mutex);
		अगर (!यंत्रa->file) अणु
			ret = 0;
			यंत्रa->size = (माप_प्रकार)arg;
		पूर्ण
		mutex_unlock(&ashmem_mutex);
		अवरोध;
	हाल ASHMEM_GET_SIZE:
		ret = यंत्रa->size;
		अवरोध;
	हाल ASHMEM_SET_PROT_MASK:
		ret = set_prot_mask(यंत्रa, arg);
		अवरोध;
	हाल ASHMEM_GET_PROT_MASK:
		ret = यंत्रa->prot_mask;
		अवरोध;
	हाल ASHMEM_PIN:
	हाल ASHMEM_UNPIN:
	हाल ASHMEM_GET_PIN_STATUS:
		ret = ashmem_pin_unpin(यंत्रa, cmd, (व्योम __user *)arg);
		अवरोध;
	हाल ASHMEM_PURGE_ALL_CACHES:
		ret = -EPERM;
		अगर (capable(CAP_SYS_ADMIN)) अणु
			काष्ठा shrink_control sc = अणु
				.gfp_mask = GFP_KERNEL,
				.nr_to_scan = दीर्घ_उच्च,
			पूर्ण;
			ret = ashmem_shrink_count(&ashmem_shrinker, &sc);
			ashmem_shrink_scan(&ashmem_shrinker, &sc);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* support of 32bit userspace on 64bit platक्रमms */
#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ compat_ashmem_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल COMPAT_ASHMEM_SET_SIZE:
		cmd = ASHMEM_SET_SIZE;
		अवरोध;
	हाल COMPAT_ASHMEM_SET_PROT_MASK:
		cmd = ASHMEM_SET_PROT_MASK;
		अवरोध;
	पूर्ण
	वापस ashmem_ioctl(file, cmd, arg);
पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_FS
अटल व्योम ashmem_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *file)
अणु
	काष्ठा ashmem_area *यंत्रa = file->निजी_data;

	mutex_lock(&ashmem_mutex);

	अगर (यंत्रa->file)
		seq_म_लिखो(m, "inode:\t%ld\n", file_inode(यंत्रa->file)->i_ino);

	अगर (यंत्रa->name[ASHMEM_NAME_PREFIX_LEN] != '\0')
		seq_म_लिखो(m, "name:\t%s\n",
			   यंत्रa->name + ASHMEM_NAME_PREFIX_LEN);

	mutex_unlock(&ashmem_mutex);
पूर्ण
#पूर्ण_अगर
अटल स्थिर काष्ठा file_operations ashmem_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = ashmem_खोलो,
	.release = ashmem_release,
	.पढ़ो_iter = ashmem_पढ़ो_iter,
	.llseek = ashmem_llseek,
	.mmap = ashmem_mmap,
	.unlocked_ioctl = ashmem_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = compat_ashmem_ioctl,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_FS
	.show_fdinfo = ashmem_show_fdinfo,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा miscdevice ashmem_misc = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "ashmem",
	.fops = &ashmem_fops,
पूर्ण;

अटल पूर्णांक __init ashmem_init(व्योम)
अणु
	पूर्णांक ret = -ENOMEM;

	ashmem_area_cachep = kmem_cache_create("ashmem_area_cache",
					       माप(काष्ठा ashmem_area),
					       0, 0, शून्य);
	अगर (!ashmem_area_cachep) अणु
		pr_err("failed to create slab cache\n");
		जाओ out;
	पूर्ण

	ashmem_range_cachep = kmem_cache_create("ashmem_range_cache",
						माप(काष्ठा ashmem_range),
						0, SLAB_RECLAIM_ACCOUNT, शून्य);
	अगर (!ashmem_range_cachep) अणु
		pr_err("failed to create slab cache\n");
		जाओ out_मुक्त1;
	पूर्ण

	ret = misc_रेजिस्टर(&ashmem_misc);
	अगर (ret) अणु
		pr_err("failed to register misc device!\n");
		जाओ out_मुक्त2;
	पूर्ण

	ret = रेजिस्टर_shrinker(&ashmem_shrinker);
	अगर (ret) अणु
		pr_err("failed to register shrinker!\n");
		जाओ out_demisc;
	पूर्ण

	pr_info("initialized\n");

	वापस 0;

out_demisc:
	misc_deरेजिस्टर(&ashmem_misc);
out_मुक्त2:
	kmem_cache_destroy(ashmem_range_cachep);
out_मुक्त1:
	kmem_cache_destroy(ashmem_area_cachep);
out:
	वापस ret;
पूर्ण
device_initcall(ashmem_init);
