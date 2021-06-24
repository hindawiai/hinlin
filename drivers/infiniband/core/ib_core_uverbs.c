<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 * Copyright 2018-2019 Amazon.com, Inc. or its affiliates. All rights reserved.
 * Copyright 2019 Marvell. All rights reserved.
 */
#समावेश <linux/xarray.h>
#समावेश "uverbs.h"
#समावेश "core_priv.h"

/**
 * rdma_umap_priv_init() - Initialize the निजी data of a vma
 *
 * @priv: The alपढ़ोy allocated निजी data
 * @vma: The vm area काष्ठा that needs निजी data
 * @entry: entry पूर्णांकo the mmap_xa that needs to be linked with
 *       this vma
 *
 * Each समय we map IO memory पूर्णांकo user space this keeps track of the
 * mapping. When the device is hot-unplugged we 'zap' the mmaps in user space
 * to poपूर्णांक to the zero page and allow the hot unplug to proceed.
 *
 * This is necessary क्रम हालs like PCI physical hot unplug as the actual BAR
 * memory may vanish after this and access to it from userspace could MCE.
 *
 * RDMA drivers supporting disassociation must have their user space deचिन्हित
 * to cope in some way with their IO pages going to the zero page.
 *
 */
व्योम rdma_umap_priv_init(काष्ठा rdma_umap_priv *priv,
			 काष्ठा vm_area_काष्ठा *vma,
			 काष्ठा rdma_user_mmap_entry *entry)
अणु
	काष्ठा ib_uverbs_file *ufile = vma->vm_file->निजी_data;

	priv->vma = vma;
	अगर (entry) अणु
		kref_get(&entry->ref);
		priv->entry = entry;
	पूर्ण
	vma->vm_निजी_data = priv;
	/* vm_ops is setup in ib_uverbs_mmap() to aव्योम module dependencies */

	mutex_lock(&ufile->umap_lock);
	list_add(&priv->list, &ufile->umaps);
	mutex_unlock(&ufile->umap_lock);
पूर्ण
EXPORT_SYMBOL(rdma_umap_priv_init);

/**
 * rdma_user_mmap_io() - Map IO memory पूर्णांकo a process
 *
 * @ucontext: associated user context
 * @vma: the vma related to the current mmap call
 * @pfn: pfn to map
 * @size: size to map
 * @prot: pgprot to use in remap call
 * @entry: mmap_entry retrieved from rdma_user_mmap_entry_get(), or शून्य
 *         अगर mmap_entry is not used by the driver
 *
 * This is to be called by drivers as part of their mmap() functions अगर they
 * wish to send something like PCI-E BAR memory to userspace.
 *
 * Return -EINVAL on wrong flags or size, -EAGAIN on failure to map. 0 on
 * success.
 */
पूर्णांक rdma_user_mmap_io(काष्ठा ib_ucontext *ucontext, काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size, pgprot_t prot,
		      काष्ठा rdma_user_mmap_entry *entry)
अणु
	काष्ठा ib_uverbs_file *ufile = ucontext->ufile;
	काष्ठा rdma_umap_priv *priv;

	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	अगर (vma->vm_end - vma->vm_start != size)
		वापस -EINVAL;

	/* Driver is using this wrong, must be called by ib_uverbs_mmap */
	अगर (WARN_ON(!vma->vm_file ||
		    vma->vm_file->निजी_data != ufile))
		वापस -EINVAL;
	lockdep_निश्चित_held(&ufile->device->disassociate_srcu);

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	vma->vm_page_prot = prot;
	अगर (io_remap_pfn_range(vma, vma->vm_start, pfn, size, prot)) अणु
		kमुक्त(priv);
		वापस -EAGAIN;
	पूर्ण

	rdma_umap_priv_init(priv, vma, entry);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rdma_user_mmap_io);

/**
 * rdma_user_mmap_entry_get_pgoff() - Get an entry from the mmap_xa
 *
 * @ucontext: associated user context
 * @pgoff: The mmap offset >> PAGE_SHIFT
 *
 * This function is called when a user tries to mmap with an offset (वापसed
 * by rdma_user_mmap_get_offset()) it initially received from the driver. The
 * rdma_user_mmap_entry was created by the function
 * rdma_user_mmap_entry_insert().  This function increases the refcnt of the
 * entry so that it won't be deleted from the xarray in the meanसमय.
 *
 * Return an reference to an entry अगर exists or शून्य अगर there is no
 * match. rdma_user_mmap_entry_put() must be called to put the reference.
 */
काष्ठा rdma_user_mmap_entry *
rdma_user_mmap_entry_get_pgoff(काष्ठा ib_ucontext *ucontext,
			       अचिन्हित दीर्घ pgoff)
अणु
	काष्ठा rdma_user_mmap_entry *entry;

	अगर (pgoff > U32_MAX)
		वापस शून्य;

	xa_lock(&ucontext->mmap_xa);

	entry = xa_load(&ucontext->mmap_xa, pgoff);

	/*
	 * If refcount is zero, entry is alपढ़ोy being deleted, driver_हटाओd
	 * indicates that the no further mmaps are possible and we रुकोing क्रम
	 * the active VMAs to be बंदd.
	 */
	अगर (!entry || entry->start_pgoff != pgoff || entry->driver_हटाओd ||
	    !kref_get_unless_zero(&entry->ref))
		जाओ err;

	xa_unlock(&ucontext->mmap_xa);

	ibdev_dbg(ucontext->device, "mmap: pgoff[%#lx] npages[%#zx] returned\n",
		  pgoff, entry->npages);

	वापस entry;

err:
	xa_unlock(&ucontext->mmap_xa);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(rdma_user_mmap_entry_get_pgoff);

/**
 * rdma_user_mmap_entry_get() - Get an entry from the mmap_xa
 *
 * @ucontext: associated user context
 * @vma: the vma being mmap'd पूर्णांकo
 *
 * This function is like rdma_user_mmap_entry_get_pgoff() except that it also
 * checks that the VMA is correct.
 */
काष्ठा rdma_user_mmap_entry *
rdma_user_mmap_entry_get(काष्ठा ib_ucontext *ucontext,
			 काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rdma_user_mmap_entry *entry;

	अगर (!(vma->vm_flags & VM_SHARED))
		वापस शून्य;
	entry = rdma_user_mmap_entry_get_pgoff(ucontext, vma->vm_pgoff);
	अगर (!entry)
		वापस शून्य;
	अगर (entry->npages * PAGE_SIZE != vma->vm_end - vma->vm_start) अणु
		rdma_user_mmap_entry_put(entry);
		वापस शून्य;
	पूर्ण
	वापस entry;
पूर्ण
EXPORT_SYMBOL(rdma_user_mmap_entry_get);

अटल व्योम rdma_user_mmap_entry_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा rdma_user_mmap_entry *entry =
		container_of(kref, काष्ठा rdma_user_mmap_entry, ref);
	काष्ठा ib_ucontext *ucontext = entry->ucontext;
	अचिन्हित दीर्घ i;

	/*
	 * Erase all entries occupied by this single entry, this is deferred
	 * until all VMA are बंदd so that the mmap offsets reमुख्य unique.
	 */
	xa_lock(&ucontext->mmap_xa);
	क्रम (i = 0; i < entry->npages; i++)
		__xa_erase(&ucontext->mmap_xa, entry->start_pgoff + i);
	xa_unlock(&ucontext->mmap_xa);

	ibdev_dbg(ucontext->device, "mmap: pgoff[%#lx] npages[%#zx] removed\n",
		  entry->start_pgoff, entry->npages);

	अगर (ucontext->device->ops.mmap_मुक्त)
		ucontext->device->ops.mmap_मुक्त(entry);
पूर्ण

/**
 * rdma_user_mmap_entry_put() - Drop reference to the mmap entry
 *
 * @entry: an entry in the mmap_xa
 *
 * This function is called when the mapping is बंदd अगर it was
 * an io mapping or when the driver is करोne with the entry क्रम
 * some other reason.
 * Should be called after rdma_user_mmap_entry_get was called
 * and entry is no दीर्घer needed. This function will erase the
 * entry and मुक्त it अगर its refcnt reaches zero.
 */
व्योम rdma_user_mmap_entry_put(काष्ठा rdma_user_mmap_entry *entry)
अणु
	kref_put(&entry->ref, rdma_user_mmap_entry_मुक्त);
पूर्ण
EXPORT_SYMBOL(rdma_user_mmap_entry_put);

/**
 * rdma_user_mmap_entry_हटाओ() - Drop reference to entry and
 *				   mark it as unmmapable
 *
 * @entry: the entry to insert पूर्णांकo the mmap_xa
 *
 * Drivers can call this to prevent userspace from creating more mappings क्रम
 * entry, however existing mmaps जारी to exist and ops->mmap_मुक्त() will
 * not be called until all user mmaps are destroyed.
 */
व्योम rdma_user_mmap_entry_हटाओ(काष्ठा rdma_user_mmap_entry *entry)
अणु
	अगर (!entry)
		वापस;

	xa_lock(&entry->ucontext->mmap_xa);
	entry->driver_हटाओd = true;
	xa_unlock(&entry->ucontext->mmap_xa);
	kref_put(&entry->ref, rdma_user_mmap_entry_मुक्त);
पूर्ण
EXPORT_SYMBOL(rdma_user_mmap_entry_हटाओ);

/**
 * rdma_user_mmap_entry_insert_range() - Insert an entry to the mmap_xa
 *					 in a given range.
 *
 * @ucontext: associated user context.
 * @entry: the entry to insert पूर्णांकo the mmap_xa
 * @length: length of the address that will be mmapped
 * @min_pgoff: minimum pgoff to be वापसed
 * @max_pgoff: maximum pgoff to be वापसed
 *
 * This function should be called by drivers that use the rdma_user_mmap
 * पूर्णांकerface क्रम implementing their mmap syscall A database of mmap offsets is
 * handled in the core and helper functions are provided to insert entries
 * पूर्णांकo the database and extract entries when the user calls mmap with the
 * given offset. The function allocates a unique page offset in a given range
 * that should be provided to user, the user will use the offset to retrieve
 * inक्रमmation such as address to be mapped and how.
 *
 * Return: 0 on success and -ENOMEM on failure
 */
पूर्णांक rdma_user_mmap_entry_insert_range(काष्ठा ib_ucontext *ucontext,
				      काष्ठा rdma_user_mmap_entry *entry,
				      माप_प्रकार length, u32 min_pgoff,
				      u32 max_pgoff)
अणु
	काष्ठा ib_uverbs_file *ufile = ucontext->ufile;
	XA_STATE(xas, &ucontext->mmap_xa, min_pgoff);
	u32 xa_first, xa_last, npages;
	पूर्णांक err;
	u32 i;

	अगर (!entry)
		वापस -EINVAL;

	kref_init(&entry->ref);
	entry->ucontext = ucontext;

	/*
	 * We want the whole allocation to be करोne without पूर्णांकerruption from a
	 * dअगरferent thपढ़ो. The allocation requires finding a मुक्त range and
	 * storing. During the xa_insert the lock could be released, possibly
	 * allowing another thपढ़ो to choose the same range.
	 */
	mutex_lock(&ufile->umap_lock);

	xa_lock(&ucontext->mmap_xa);

	/* We want to find an empty range */
	npages = (u32)DIV_ROUND_UP(length, PAGE_SIZE);
	entry->npages = npages;
	जबतक (true) अणु
		/* First find an empty index */
		xas_find_marked(&xas, max_pgoff, XA_FREE_MARK);
		अगर (xas.xa_node == XAS_RESTART)
			जाओ err_unlock;

		xa_first = xas.xa_index;

		/* Is there enough room to have the range? */
		अगर (check_add_overflow(xa_first, npages, &xa_last))
			जाओ err_unlock;

		/*
		 * Now look क्रम the next present entry. If an entry करोesn't
		 * exist, we found an empty range and can proceed.
		 */
		xas_next_entry(&xas, xa_last - 1);
		अगर (xas.xa_node == XAS_BOUNDS || xas.xa_index >= xa_last)
			अवरोध;
	पूर्ण

	क्रम (i = xa_first; i < xa_last; i++) अणु
		err = __xa_insert(&ucontext->mmap_xa, i, entry, GFP_KERNEL);
		अगर (err)
			जाओ err_unकरो;
	पूर्ण

	/*
	 * Internally the kernel uses a page offset, in libc this is a byte
	 * offset. Drivers should not वापस pgoff to userspace.
	 */
	entry->start_pgoff = xa_first;
	xa_unlock(&ucontext->mmap_xa);
	mutex_unlock(&ufile->umap_lock);

	ibdev_dbg(ucontext->device, "mmap: pgoff[%#lx] npages[%#x] inserted\n",
		  entry->start_pgoff, npages);

	वापस 0;

err_unकरो:
	क्रम (; i > xa_first; i--)
		__xa_erase(&ucontext->mmap_xa, i - 1);

err_unlock:
	xa_unlock(&ucontext->mmap_xa);
	mutex_unlock(&ufile->umap_lock);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(rdma_user_mmap_entry_insert_range);

/**
 * rdma_user_mmap_entry_insert() - Insert an entry to the mmap_xa.
 *
 * @ucontext: associated user context.
 * @entry: the entry to insert पूर्णांकo the mmap_xa
 * @length: length of the address that will be mmapped
 *
 * This function should be called by drivers that use the rdma_user_mmap
 * पूर्णांकerface क्रम handling user mmapped addresses. The database is handled in
 * the core and helper functions are provided to insert entries पूर्णांकo the
 * database and extract entries when the user calls mmap with the given offset.
 * The function allocates a unique page offset that should be provided to user,
 * the user will use the offset to retrieve inक्रमmation such as address to
 * be mapped and how.
 *
 * Return: 0 on success and -ENOMEM on failure
 */
पूर्णांक rdma_user_mmap_entry_insert(काष्ठा ib_ucontext *ucontext,
				काष्ठा rdma_user_mmap_entry *entry,
				माप_प्रकार length)
अणु
	वापस rdma_user_mmap_entry_insert_range(ucontext, entry, length, 0,
						 U32_MAX);
पूर्ण
EXPORT_SYMBOL(rdma_user_mmap_entry_insert);
