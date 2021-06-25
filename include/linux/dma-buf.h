<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Header file क्रम dma buffer sharing framework.
 *
 * Copyright(C) 2011 Linaro Limited. All rights reserved.
 * Author: Sumit Semwal <sumit.semwal@ti.com>
 *
 * Many thanks to linaro-mm-sig list, and specially
 * Arnd Bergmann <arnd@arndb.de>, Rob Clark <rob@ti.com> and
 * Daniel Vetter <daniel@ffwll.ch> क्रम their support in creation and
 * refining of this idea.
 */
#अगर_अघोषित __DMA_BUF_H__
#घोषणा __DMA_BUF_H__

#समावेश <linux/dma-buf-map.h>
#समावेश <linux/file.h>
#समावेश <linux/err.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/list.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fs.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/रुको.h>

काष्ठा device;
काष्ठा dma_buf;
काष्ठा dma_buf_attachment;

/**
 * काष्ठा dma_buf_ops - operations possible on काष्ठा dma_buf
 * @vmap: [optional] creates a भव mapping क्रम the buffer पूर्णांकo kernel
 *	  address space. Same restrictions as क्रम vmap and मित्रs apply.
 * @vunmap: [optional] unmaps a vmap from the buffer
 */
काष्ठा dma_buf_ops अणु
	/**
	  * @cache_sgt_mapping:
	  *
	  * If true the framework will cache the first mapping made क्रम each
	  * attachment. This aव्योमs creating mappings क्रम attachments multiple
	  * बार.
	  */
	bool cache_sgt_mapping;

	/**
	 * @attach:
	 *
	 * This is called from dma_buf_attach() to make sure that a given
	 * &dma_buf_attachment.dev can access the provided &dma_buf. Exporters
	 * which support buffer objects in special locations like VRAM or
	 * device-specअगरic carveout areas should check whether the buffer could
	 * be move to प्रणाली memory (or directly accessed by the provided
	 * device), and otherwise need to fail the attach operation.
	 *
	 * The exporter should also in general check whether the current
	 * allocation fullfills the DMA स्थिरraपूर्णांकs of the new device. If this
	 * is not the हाल, and the allocation cannot be moved, it should also
	 * fail the attach operation.
	 *
	 * Any exporter-निजी housekeeping data can be stored in the
	 * &dma_buf_attachment.priv poपूर्णांकer.
	 *
	 * This callback is optional.
	 *
	 * Returns:
	 *
	 * 0 on success, negative error code on failure. It might वापस -EBUSY
	 * to संकेत that backing storage is alपढ़ोy allocated and incompatible
	 * with the requirements of requesting device.
	 */
	पूर्णांक (*attach)(काष्ठा dma_buf *, काष्ठा dma_buf_attachment *);

	/**
	 * @detach:
	 *
	 * This is called by dma_buf_detach() to release a &dma_buf_attachment.
	 * Provided so that exporters can clean up any housekeeping क्रम an
	 * &dma_buf_attachment.
	 *
	 * This callback is optional.
	 */
	व्योम (*detach)(काष्ठा dma_buf *, काष्ठा dma_buf_attachment *);

	/**
	 * @pin:
	 *
	 * This is called by dma_buf_pin() and lets the exporter know that the
	 * DMA-buf can't be moved any more. The exporter should pin the buffer
	 * पूर्णांकo प्रणाली memory to make sure it is generally accessible by other
	 * devices.
	 *
	 * This is called with the &dmabuf.resv object locked and is mutual
	 * exclusive with @cache_sgt_mapping.
	 *
	 * This is called स्वतःmatically क्रम non-dynamic importers from
	 * dma_buf_attach().
	 *
	 * Returns:
	 *
	 * 0 on success, negative error code on failure.
	 */
	पूर्णांक (*pin)(काष्ठा dma_buf_attachment *attach);

	/**
	 * @unpin:
	 *
	 * This is called by dma_buf_unpin() and lets the exporter know that the
	 * DMA-buf can be moved again.
	 *
	 * This is called with the dmabuf->resv object locked and is mutual
	 * exclusive with @cache_sgt_mapping.
	 *
	 * This callback is optional.
	 */
	व्योम (*unpin)(काष्ठा dma_buf_attachment *attach);

	/**
	 * @map_dma_buf:
	 *
	 * This is called by dma_buf_map_attachment() and is used to map a
	 * shared &dma_buf पूर्णांकo device address space, and it is mandatory. It
	 * can only be called अगर @attach has been called successfully.
	 *
	 * This call may sleep, e.g. when the backing storage first needs to be
	 * allocated, or moved to a location suitable क्रम all currently attached
	 * devices.
	 *
	 * Note that any specअगरic buffer attributes required क्रम this function
	 * should get added to device_dma_parameters accessible via
	 * &device.dma_params from the &dma_buf_attachment. The @attach callback
	 * should also check these स्थिरraपूर्णांकs.
	 *
	 * If this is being called क्रम the first समय, the exporter can now
	 * choose to scan through the list of attachments क्रम this buffer,
	 * collate the requirements of the attached devices, and choose an
	 * appropriate backing storage क्रम the buffer.
	 *
	 * Based on क्रमागत dma_data_direction, it might be possible to have
	 * multiple users accessing at the same समय (क्रम पढ़ोing, maybe), or
	 * any other kind of sharing that the exporter might wish to make
	 * available to buffer-users.
	 *
	 * This is always called with the dmabuf->resv object locked when
	 * the dynamic_mapping flag is true.
	 *
	 * Returns:
	 *
	 * A &sg_table scatter list of or the backing storage of the DMA buffer,
	 * alपढ़ोy mapped पूर्णांकo the device address space of the &device attached
	 * with the provided &dma_buf_attachment. The addresses and lengths in
	 * the scatter list are PAGE_SIZE aligned.
	 *
	 * On failure, वापसs a negative error value wrapped पूर्णांकo a poपूर्णांकer.
	 * May also वापस -EINTR when a संकेत was received जबतक being
	 * blocked.
	 *
	 * Note that exporters should not try to cache the scatter list, or
	 * वापस the same one क्रम multiple calls. Caching is करोne either by the
	 * DMA-BUF code (क्रम non-dynamic importers) or the importer. Ownership
	 * of the scatter list is transferred to the caller, and वापसed by
	 * @unmap_dma_buf.
	 */
	काष्ठा sg_table * (*map_dma_buf)(काष्ठा dma_buf_attachment *,
					 क्रमागत dma_data_direction);
	/**
	 * @unmap_dma_buf:
	 *
	 * This is called by dma_buf_unmap_attachment() and should unmap and
	 * release the &sg_table allocated in @map_dma_buf, and it is mandatory.
	 * For अटल dma_buf handling this might also unpins the backing
	 * storage अगर this is the last mapping of the DMA buffer.
	 */
	व्योम (*unmap_dma_buf)(काष्ठा dma_buf_attachment *,
			      काष्ठा sg_table *,
			      क्रमागत dma_data_direction);

	/* TODO: Add try_map_dma_buf version, to वापस immed with -EBUSY
	 * अगर the call would block.
	 */

	/**
	 * @release:
	 *
	 * Called after the last dma_buf_put to release the &dma_buf, and
	 * mandatory.
	 */
	व्योम (*release)(काष्ठा dma_buf *);

	/**
	 * @begin_cpu_access:
	 *
	 * This is called from dma_buf_begin_cpu_access() and allows the
	 * exporter to ensure that the memory is actually coherent क्रम cpu
	 * access. The exporter also needs to ensure that cpu access is coherent
	 * क्रम the access direction. The direction can be used by the exporter
	 * to optimize the cache flushing, i.e. access with a dअगरferent
	 * direction (पढ़ो instead of ग_लिखो) might वापस stale or even bogus
	 * data (e.g. when the exporter needs to copy the data to temporary
	 * storage).
	 *
	 * Note that this is both called through the DMA_BUF_IOCTL_SYNC IOCTL
	 * command क्रम userspace mappings established through @mmap, and also
	 * क्रम kernel mappings established with @vmap.
	 *
	 * This callback is optional.
	 *
	 * Returns:
	 *
	 * 0 on success or a negative error code on failure. This can क्रम
	 * example fail when the backing storage can't be allocated. Can also
	 * वापस -ERESTARTSYS or -EINTR when the call has been पूर्णांकerrupted and
	 * needs to be restarted.
	 */
	पूर्णांक (*begin_cpu_access)(काष्ठा dma_buf *, क्रमागत dma_data_direction);

	/**
	 * @end_cpu_access:
	 *
	 * This is called from dma_buf_end_cpu_access() when the importer is
	 * करोne accessing the CPU. The exporter can use this to flush caches and
	 * unकरो anything अन्यथा करोne in @begin_cpu_access.
	 *
	 * This callback is optional.
	 *
	 * Returns:
	 *
	 * 0 on success or a negative error code on failure. Can वापस
	 * -ERESTARTSYS or -EINTR when the call has been पूर्णांकerrupted and needs
	 * to be restarted.
	 */
	पूर्णांक (*end_cpu_access)(काष्ठा dma_buf *, क्रमागत dma_data_direction);

	/**
	 * @mmap:
	 *
	 * This callback is used by the dma_buf_mmap() function
	 *
	 * Note that the mapping needs to be incoherent, userspace is expected
	 * to braket CPU access using the DMA_BUF_IOCTL_SYNC पूर्णांकerface.
	 *
	 * Because dma-buf buffers have invariant size over their lअगरeसमय, the
	 * dma-buf core checks whether a vma is too large and rejects such
	 * mappings. The exporter hence करोes not need to duplicate this check.
	 * Drivers करो not need to check this themselves.
	 *
	 * If an exporter needs to manually flush caches and hence needs to fake
	 * coherency क्रम mmap support, it needs to be able to zap all the ptes
	 * poपूर्णांकing at the backing storage. Now linux mm needs a काष्ठा
	 * address_space associated with the काष्ठा file stored in vma->vm_file
	 * to करो that with the function unmap_mapping_range. But the dma_buf
	 * framework only backs every dma_buf fd with the anon_file काष्ठा file,
	 * i.e. all dma_bufs share the same file.
	 *
	 * Hence exporters need to setup their own file (and address_space)
	 * association by setting vma->vm_file and adjusting vma->vm_pgoff in
	 * the dma_buf mmap callback. In the specअगरic हाल of a gem driver the
	 * exporter could use the shmem file alपढ़ोy provided by gem (and set
	 * vm_pgoff = 0). Exporters can then zap ptes by unmapping the
	 * corresponding range of the काष्ठा address_space associated with their
	 * own file.
	 *
	 * This callback is optional.
	 *
	 * Returns:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*mmap)(काष्ठा dma_buf *, काष्ठा vm_area_काष्ठा *vma);

	पूर्णांक (*vmap)(काष्ठा dma_buf *dmabuf, काष्ठा dma_buf_map *map);
	व्योम (*vunmap)(काष्ठा dma_buf *dmabuf, काष्ठा dma_buf_map *map);
पूर्ण;

/**
 * काष्ठा dma_buf - shared buffer object
 * @size: size of the buffer; invariant over the lअगरeसमय of the buffer.
 * @file: file poपूर्णांकer used क्रम sharing buffers across, and क्रम refcounting.
 * @attachments: list of dma_buf_attachment that denotes all devices attached,
 *               रक्षित by dma_resv lock.
 * @ops: dma_buf_ops associated with this buffer object.
 * @lock: used पूर्णांकernally to serialize list manipulation, attach/detach and
 *        vmap/unmap
 * @vmapping_counter: used पूर्णांकernally to refcnt the vmaps
 * @vmap_ptr: the current vmap ptr अगर vmapping_counter > 0
 * @exp_name: name of the exporter; useful क्रम debugging.
 * @name: userspace-provided name; useful क्रम accounting and debugging,
 *        रक्षित by @resv.
 * @name_lock: spinlock to protect name access
 * @owner: poपूर्णांकer to exporter module; used क्रम refcounting when exporter is a
 *         kernel module.
 * @list_node: node क्रम dma_buf accounting and debugging.
 * @priv: exporter specअगरic निजी data क्रम this buffer object.
 * @resv: reservation object linked to this dma-buf
 * @poll: क्रम userspace poll support
 * @cb_excl: क्रम userspace poll support
 * @cb_shared: क्रम userspace poll support
 *
 * This represents a shared buffer, created by calling dma_buf_export(). The
 * userspace representation is a normal file descriptor, which can be created by
 * calling dma_buf_fd().
 *
 * Shared dma buffers are reference counted using dma_buf_put() and
 * get_dma_buf().
 *
 * Device DMA access is handled by the separate &काष्ठा dma_buf_attachment.
 */
काष्ठा dma_buf अणु
	माप_प्रकार size;
	काष्ठा file *file;
	काष्ठा list_head attachments;
	स्थिर काष्ठा dma_buf_ops *ops;
	काष्ठा mutex lock;
	अचिन्हित vmapping_counter;
	काष्ठा dma_buf_map vmap_ptr;
	स्थिर अक्षर *exp_name;
	स्थिर अक्षर *name;
	spinlock_t name_lock;
	काष्ठा module *owner;
	काष्ठा list_head list_node;
	व्योम *priv;
	काष्ठा dma_resv *resv;

	/* poll support */
	रुको_queue_head_t poll;

	काष्ठा dma_buf_poll_cb_t अणु
		काष्ठा dma_fence_cb cb;
		रुको_queue_head_t *poll;

		__poll_t active;
	पूर्ण cb_excl, cb_shared;
पूर्ण;

/**
 * काष्ठा dma_buf_attach_ops - importer operations क्रम an attachment
 *
 * Attachment operations implemented by the importer.
 */
काष्ठा dma_buf_attach_ops अणु
	/**
	 * @allow_peer2peer:
	 *
	 * If this is set to true the importer must be able to handle peer
	 * resources without काष्ठा pages.
	 */
	bool allow_peer2peer;

	/**
	 * @move_notअगरy: [optional] notअगरication that the DMA-buf is moving
	 *
	 * If this callback is provided the framework can aव्योम pinning the
	 * backing store जबतक mappings exists.
	 *
	 * This callback is called with the lock of the reservation object
	 * associated with the dma_buf held and the mapping function must be
	 * called with this lock held as well. This makes sure that no mapping
	 * is created concurrently with an ongoing move operation.
	 *
	 * Mappings stay valid and are not directly affected by this callback.
	 * But the DMA-buf can now be in a dअगरferent physical location, so all
	 * mappings should be destroyed and re-created as soon as possible.
	 *
	 * New mappings can be created after this callback वापसs, and will
	 * poपूर्णांक to the new location of the DMA-buf.
	 */
	व्योम (*move_notअगरy)(काष्ठा dma_buf_attachment *attach);
पूर्ण;

/**
 * काष्ठा dma_buf_attachment - holds device-buffer attachment data
 * @dmabuf: buffer क्रम this attachment.
 * @dev: device attached to the buffer.
 * @node: list of dma_buf_attachment, रक्षित by dma_resv lock of the dmabuf.
 * @sgt: cached mapping.
 * @dir: direction of cached mapping.
 * @peer2peer: true अगर the importer can handle peer resources without pages.
 * @priv: exporter specअगरic attachment data.
 * @importer_ops: importer operations क्रम this attachment, अगर provided
 * dma_buf_map/unmap_attachment() must be called with the dma_resv lock held.
 * @importer_priv: importer specअगरic attachment data.
 *
 * This काष्ठाure holds the attachment inक्रमmation between the dma_buf buffer
 * and its user device(s). The list contains one attachment काष्ठा per device
 * attached to the buffer.
 *
 * An attachment is created by calling dma_buf_attach(), and released again by
 * calling dma_buf_detach(). The DMA mapping itself needed to initiate a
 * transfer is created by dma_buf_map_attachment() and मुक्तd again by calling
 * dma_buf_unmap_attachment().
 */
काष्ठा dma_buf_attachment अणु
	काष्ठा dma_buf *dmabuf;
	काष्ठा device *dev;
	काष्ठा list_head node;
	काष्ठा sg_table *sgt;
	क्रमागत dma_data_direction dir;
	bool peer2peer;
	स्थिर काष्ठा dma_buf_attach_ops *importer_ops;
	व्योम *importer_priv;
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा dma_buf_export_info - holds inक्रमmation needed to export a dma_buf
 * @exp_name:	name of the exporter - useful क्रम debugging.
 * @owner:	poपूर्णांकer to exporter module - used क्रम refcounting kernel module
 * @ops:	Attach allocator-defined dma buf ops to the new buffer
 * @size:	Size of the buffer - invariant over the lअगरeसमय of the buffer
 * @flags:	mode flags क्रम the file
 * @resv:	reservation-object, शून्य to allocate शेष one
 * @priv:	Attach निजी data of allocator to this buffer
 *
 * This काष्ठाure holds the inक्रमmation required to export the buffer. Used
 * with dma_buf_export() only.
 */
काष्ठा dma_buf_export_info अणु
	स्थिर अक्षर *exp_name;
	काष्ठा module *owner;
	स्थिर काष्ठा dma_buf_ops *ops;
	माप_प्रकार size;
	पूर्णांक flags;
	काष्ठा dma_resv *resv;
	व्योम *priv;
पूर्ण;

/**
 * DEFINE_DMA_BUF_EXPORT_INFO - helper macro क्रम exporters
 * @name: export-info name
 *
 * DEFINE_DMA_BUF_EXPORT_INFO macro defines the &काष्ठा dma_buf_export_info,
 * zeroes it out and pre-populates exp_name in it.
 */
#घोषणा DEFINE_DMA_BUF_EXPORT_INFO(name)	\
	काष्ठा dma_buf_export_info name = अणु .exp_name = KBUILD_MODNAME, \
					 .owner = THIS_MODULE पूर्ण

/**
 * get_dma_buf - convenience wrapper क्रम get_file.
 * @dmabuf:	[in]	poपूर्णांकer to dma_buf
 *
 * Increments the reference count on the dma-buf, needed in हाल of drivers
 * that either need to create additional references to the dmabuf on the
 * kernel side.  For example, an exporter that needs to keep a dmabuf ptr
 * so that subsequent exports करोn't create a new dmabuf.
 */
अटल अंतरभूत व्योम get_dma_buf(काष्ठा dma_buf *dmabuf)
अणु
	get_file(dmabuf->file);
पूर्ण

/**
 * dma_buf_is_dynamic - check अगर a DMA-buf uses dynamic mappings.
 * @dmabuf: the DMA-buf to check
 *
 * Returns true अगर a DMA-buf exporter wants to be called with the dma_resv
 * locked क्रम the map/unmap callbacks, false अगर it करोesn't wants to be called
 * with the lock held.
 */
अटल अंतरभूत bool dma_buf_is_dynamic(काष्ठा dma_buf *dmabuf)
अणु
	वापस !!dmabuf->ops->pin;
पूर्ण

/**
 * dma_buf_attachment_is_dynamic - check अगर a DMA-buf attachment uses dynamic
 * mappinsg
 * @attach: the DMA-buf attachment to check
 *
 * Returns true अगर a DMA-buf importer wants to call the map/unmap functions with
 * the dma_resv lock held.
 */
अटल अंतरभूत bool
dma_buf_attachment_is_dynamic(काष्ठा dma_buf_attachment *attach)
अणु
	वापस !!attach->importer_ops;
पूर्ण

काष्ठा dma_buf_attachment *dma_buf_attach(काष्ठा dma_buf *dmabuf,
					  काष्ठा device *dev);
काष्ठा dma_buf_attachment *
dma_buf_dynamic_attach(काष्ठा dma_buf *dmabuf, काष्ठा device *dev,
		       स्थिर काष्ठा dma_buf_attach_ops *importer_ops,
		       व्योम *importer_priv);
व्योम dma_buf_detach(काष्ठा dma_buf *dmabuf,
		    काष्ठा dma_buf_attachment *attach);
पूर्णांक dma_buf_pin(काष्ठा dma_buf_attachment *attach);
व्योम dma_buf_unpin(काष्ठा dma_buf_attachment *attach);

काष्ठा dma_buf *dma_buf_export(स्थिर काष्ठा dma_buf_export_info *exp_info);

पूर्णांक dma_buf_fd(काष्ठा dma_buf *dmabuf, पूर्णांक flags);
काष्ठा dma_buf *dma_buf_get(पूर्णांक fd);
व्योम dma_buf_put(काष्ठा dma_buf *dmabuf);

काष्ठा sg_table *dma_buf_map_attachment(काष्ठा dma_buf_attachment *,
					क्रमागत dma_data_direction);
व्योम dma_buf_unmap_attachment(काष्ठा dma_buf_attachment *, काष्ठा sg_table *,
				क्रमागत dma_data_direction);
व्योम dma_buf_move_notअगरy(काष्ठा dma_buf *dma_buf);
पूर्णांक dma_buf_begin_cpu_access(काष्ठा dma_buf *dma_buf,
			     क्रमागत dma_data_direction dir);
पूर्णांक dma_buf_end_cpu_access(काष्ठा dma_buf *dma_buf,
			   क्रमागत dma_data_direction dir);

पूर्णांक dma_buf_mmap(काष्ठा dma_buf *, काष्ठा vm_area_काष्ठा *,
		 अचिन्हित दीर्घ);
पूर्णांक dma_buf_vmap(काष्ठा dma_buf *dmabuf, काष्ठा dma_buf_map *map);
व्योम dma_buf_vunmap(काष्ठा dma_buf *dmabuf, काष्ठा dma_buf_map *map);
#पूर्ण_अगर /* __DMA_BUF_H__ */
