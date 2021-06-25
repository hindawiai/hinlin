<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Virtio ring implementation.
 *
 *  Copyright 2007 Rusty Russell IBM Corporation
 */
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_ring.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/dma-mapping.h>
#समावेश <xen/xen.h>

#अगर_घोषित DEBUG
/* For development, we want to crash whenever the ring is screwed. */
#घोषणा BAD_RING(_vq, fmt, args...)				\
	करो अणु							\
		dev_err(&(_vq)->vq.vdev->dev,			\
			"%s:"fmt, (_vq)->vq.name, ##args);	\
		BUG();						\
	पूर्ण जबतक (0)
/* Caller is supposed to guarantee no reentry. */
#घोषणा START_USE(_vq)						\
	करो अणु							\
		अगर ((_vq)->in_use)				\
			panic("%s:in_use = %i\n",		\
			      (_vq)->vq.name, (_vq)->in_use);	\
		(_vq)->in_use = __LINE__;			\
	पूर्ण जबतक (0)
#घोषणा END_USE(_vq) \
	करो अणु BUG_ON(!(_vq)->in_use); (_vq)->in_use = 0; पूर्ण जबतक(0)
#घोषणा LAST_ADD_TIME_UPDATE(_vq)				\
	करो अणु							\
		kसमय_प्रकार now = kसमय_get();			\
								\
		/* No kick or get, with .1 second between?  Warn. */ \
		अगर ((_vq)->last_add_समय_valid)			\
			WARN_ON(kसमय_प्रकारo_ms(kसमय_sub(now,	\
				(_vq)->last_add_समय)) > 100);	\
		(_vq)->last_add_समय = now;			\
		(_vq)->last_add_समय_valid = true;		\
	पूर्ण जबतक (0)
#घोषणा LAST_ADD_TIME_CHECK(_vq)				\
	करो अणु							\
		अगर ((_vq)->last_add_समय_valid) अणु		\
			WARN_ON(kसमय_प्रकारo_ms(kसमय_sub(kसमय_get(), \
				      (_vq)->last_add_समय)) > 100); \
		पूर्ण						\
	पूर्ण जबतक (0)
#घोषणा LAST_ADD_TIME_INVALID(_vq)				\
	((_vq)->last_add_समय_valid = false)
#अन्यथा
#घोषणा BAD_RING(_vq, fmt, args...)				\
	करो अणु							\
		dev_err(&_vq->vq.vdev->dev,			\
			"%s:"fmt, (_vq)->vq.name, ##args);	\
		(_vq)->broken = true;				\
	पूर्ण जबतक (0)
#घोषणा START_USE(vq)
#घोषणा END_USE(vq)
#घोषणा LAST_ADD_TIME_UPDATE(vq)
#घोषणा LAST_ADD_TIME_CHECK(vq)
#घोषणा LAST_ADD_TIME_INVALID(vq)
#पूर्ण_अगर

काष्ठा vring_desc_state_split अणु
	व्योम *data;			/* Data क्रम callback. */
	काष्ठा vring_desc *indir_desc;	/* Indirect descriptor, अगर any. */
पूर्ण;

काष्ठा vring_desc_state_packed अणु
	व्योम *data;			/* Data क्रम callback. */
	काष्ठा vring_packed_desc *indir_desc; /* Indirect descriptor, अगर any. */
	u16 num;			/* Descriptor list length. */
	u16 next;			/* The next desc state in a list. */
	u16 last;			/* The last desc state in a list. */
पूर्ण;

काष्ठा vring_desc_extra_packed अणु
	dma_addr_t addr;		/* Buffer DMA addr. */
	u32 len;			/* Buffer length. */
	u16 flags;			/* Descriptor flags. */
पूर्ण;

काष्ठा vring_virtqueue अणु
	काष्ठा virtqueue vq;

	/* Is this a packed ring? */
	bool packed_ring;

	/* Is DMA API used? */
	bool use_dma_api;

	/* Can we use weak barriers? */
	bool weak_barriers;

	/* Other side has made a mess, करोn't try any more. */
	bool broken;

	/* Host supports indirect buffers */
	bool indirect;

	/* Host publishes avail event idx */
	bool event;

	/* Head of मुक्त buffer list. */
	अचिन्हित पूर्णांक मुक्त_head;
	/* Number we've added since last sync. */
	अचिन्हित पूर्णांक num_added;

	/* Last used index we've seen. */
	u16 last_used_idx;

	जोड़ अणु
		/* Available क्रम split ring */
		काष्ठा अणु
			/* Actual memory layout क्रम this queue. */
			काष्ठा vring vring;

			/* Last written value to avail->flags */
			u16 avail_flags_shaकरोw;

			/*
			 * Last written value to avail->idx in
			 * guest byte order.
			 */
			u16 avail_idx_shaकरोw;

			/* Per-descriptor state. */
			काष्ठा vring_desc_state_split *desc_state;

			/* DMA address and size inक्रमmation */
			dma_addr_t queue_dma_addr;
			माप_प्रकार queue_size_in_bytes;
		पूर्ण split;

		/* Available क्रम packed ring */
		काष्ठा अणु
			/* Actual memory layout क्रम this queue. */
			काष्ठा अणु
				अचिन्हित पूर्णांक num;
				काष्ठा vring_packed_desc *desc;
				काष्ठा vring_packed_desc_event *driver;
				काष्ठा vring_packed_desc_event *device;
			पूर्ण vring;

			/* Driver ring wrap counter. */
			bool avail_wrap_counter;

			/* Device ring wrap counter. */
			bool used_wrap_counter;

			/* Avail used flags. */
			u16 avail_used_flags;

			/* Index of the next avail descriptor. */
			u16 next_avail_idx;

			/*
			 * Last written value to driver->flags in
			 * guest byte order.
			 */
			u16 event_flags_shaकरोw;

			/* Per-descriptor state. */
			काष्ठा vring_desc_state_packed *desc_state;
			काष्ठा vring_desc_extra_packed *desc_extra;

			/* DMA address and size inक्रमmation */
			dma_addr_t ring_dma_addr;
			dma_addr_t driver_event_dma_addr;
			dma_addr_t device_event_dma_addr;
			माप_प्रकार ring_size_in_bytes;
			माप_प्रकार event_size_in_bytes;
		पूर्ण packed;
	पूर्ण;

	/* How to notअगरy other side. FIXME: commonalize hcalls! */
	bool (*notअगरy)(काष्ठा virtqueue *vq);

	/* DMA, allocation, and size inक्रमmation */
	bool we_own_ring;

#अगर_घोषित DEBUG
	/* They're supposed to lock क्रम us. */
	अचिन्हित पूर्णांक in_use;

	/* Figure out अगर their kicks are too delayed. */
	bool last_add_समय_valid;
	kसमय_प्रकार last_add_समय;
#पूर्ण_अगर
पूर्ण;


/*
 * Helpers.
 */

#घोषणा to_vvq(_vq) container_of(_vq, काष्ठा vring_virtqueue, vq)

अटल अंतरभूत bool virtqueue_use_indirect(काष्ठा virtqueue *_vq,
					  अचिन्हित पूर्णांक total_sg)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	/*
	 * If the host supports indirect descriptor tables, and we have multiple
	 * buffers, then go indirect. FIXME: tune this threshold
	 */
	वापस (vq->indirect && total_sg > 1 && vq->vq.num_मुक्त);
पूर्ण

/*
 * Modern virtio devices have feature bits to specअगरy whether they need a
 * quirk and bypass the IOMMU. If not there, just use the DMA API.
 *
 * If there, the पूर्णांकeraction between virtio and DMA API is messy.
 *
 * On most प्रणालीs with virtio, physical addresses match bus addresses,
 * and it करोesn't particularly matter whether we use the DMA API.
 *
 * On some प्रणालीs, including Xen and any प्रणाली with a physical device
 * that speaks virtio behind a physical IOMMU, we must use the DMA API
 * क्रम virtio DMA to work at all.
 *
 * On other प्रणालीs, including SPARC and PPC64, virtio-pci devices are
 * क्रमागतerated as though they are behind an IOMMU, but the virtio host
 * ignores the IOMMU, so we must either pretend that the IOMMU isn't
 * there or somehow map everything as the identity.
 *
 * For the समय being, we preserve historic behavior and bypass the DMA
 * API.
 *
 * TODO: install a per-device DMA ops काष्ठाure that करोes the right thing
 * taking पूर्णांकo account all the above quirks, and use the DMA API
 * unconditionally on data path.
 */

अटल bool vring_use_dma_api(काष्ठा virtio_device *vdev)
अणु
	अगर (!virtio_has_dma_quirk(vdev))
		वापस true;

	/* Otherwise, we are left to guess. */
	/*
	 * In theory, it's possible to have a buggy QEMU-supposed
	 * emulated Q35 IOMMU and Xen enabled at the same समय.  On
	 * such a configuration, virtio has never worked and will
	 * not work without an even larger kludge.  Instead, enable
	 * the DMA API अगर we're a Xen guest, which at least allows
	 * all of the sensible Xen configurations to work correctly.
	 */
	अगर (xen_करोमुख्य())
		वापस true;

	वापस false;
पूर्ण

माप_प्रकार virtio_max_dma_size(काष्ठा virtio_device *vdev)
अणु
	माप_प्रकार max_segment_size = SIZE_MAX;

	अगर (vring_use_dma_api(vdev))
		max_segment_size = dma_max_mapping_size(&vdev->dev);

	वापस max_segment_size;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_max_dma_size);

अटल व्योम *vring_alloc_queue(काष्ठा virtio_device *vdev, माप_प्रकार size,
			      dma_addr_t *dma_handle, gfp_t flag)
अणु
	अगर (vring_use_dma_api(vdev)) अणु
		वापस dma_alloc_coherent(vdev->dev.parent, size,
					  dma_handle, flag);
	पूर्ण अन्यथा अणु
		व्योम *queue = alloc_pages_exact(PAGE_ALIGN(size), flag);

		अगर (queue) अणु
			phys_addr_t phys_addr = virt_to_phys(queue);
			*dma_handle = (dma_addr_t)phys_addr;

			/*
			 * Sanity check: make sure we dind't truncate
			 * the address.  The only arches I can find that
			 * have 64-bit phys_addr_t but 32-bit dma_addr_t
			 * are certain non-highmem MIPS and x86
			 * configurations, but these configurations
			 * should never allocate physical pages above 32
			 * bits, so this is fine.  Just in हाल, throw a
			 * warning and पात अगर we end up with an
			 * unrepresentable address.
			 */
			अगर (WARN_ON_ONCE(*dma_handle != phys_addr)) अणु
				मुक्त_pages_exact(queue, PAGE_ALIGN(size));
				वापस शून्य;
			पूर्ण
		पूर्ण
		वापस queue;
	पूर्ण
पूर्ण

अटल व्योम vring_मुक्त_queue(काष्ठा virtio_device *vdev, माप_प्रकार size,
			     व्योम *queue, dma_addr_t dma_handle)
अणु
	अगर (vring_use_dma_api(vdev))
		dma_मुक्त_coherent(vdev->dev.parent, size, queue, dma_handle);
	अन्यथा
		मुक्त_pages_exact(queue, PAGE_ALIGN(size));
पूर्ण

/*
 * The DMA ops on various arches are rather gnarly right now, and
 * making all of the arch DMA ops work on the vring device itself
 * is a mess.  For now, we use the parent device क्रम DMA ops.
 */
अटल अंतरभूत काष्ठा device *vring_dma_dev(स्थिर काष्ठा vring_virtqueue *vq)
अणु
	वापस vq->vq.vdev->dev.parent;
पूर्ण

/* Map one sg entry. */
अटल dma_addr_t vring_map_one_sg(स्थिर काष्ठा vring_virtqueue *vq,
				   काष्ठा scatterlist *sg,
				   क्रमागत dma_data_direction direction)
अणु
	अगर (!vq->use_dma_api)
		वापस (dma_addr_t)sg_phys(sg);

	/*
	 * We can't use dma_map_sg, because we don't use scatterlists in
	 * the way it expects (we करोn't guarantee that the scatterlist
	 * will exist क्रम the lअगरeसमय of the mapping).
	 */
	वापस dma_map_page(vring_dma_dev(vq),
			    sg_page(sg), sg->offset, sg->length,
			    direction);
पूर्ण

अटल dma_addr_t vring_map_single(स्थिर काष्ठा vring_virtqueue *vq,
				   व्योम *cpu_addr, माप_प्रकार size,
				   क्रमागत dma_data_direction direction)
अणु
	अगर (!vq->use_dma_api)
		वापस (dma_addr_t)virt_to_phys(cpu_addr);

	वापस dma_map_single(vring_dma_dev(vq),
			      cpu_addr, size, direction);
पूर्ण

अटल पूर्णांक vring_mapping_error(स्थिर काष्ठा vring_virtqueue *vq,
			       dma_addr_t addr)
अणु
	अगर (!vq->use_dma_api)
		वापस 0;

	वापस dma_mapping_error(vring_dma_dev(vq), addr);
पूर्ण


/*
 * Split ring specअगरic functions - *_split().
 */

अटल व्योम vring_unmap_one_split(स्थिर काष्ठा vring_virtqueue *vq,
				  काष्ठा vring_desc *desc)
अणु
	u16 flags;

	अगर (!vq->use_dma_api)
		वापस;

	flags = virtio16_to_cpu(vq->vq.vdev, desc->flags);

	अगर (flags & VRING_DESC_F_INसूचीECT) अणु
		dma_unmap_single(vring_dma_dev(vq),
				 virtio64_to_cpu(vq->vq.vdev, desc->addr),
				 virtio32_to_cpu(vq->vq.vdev, desc->len),
				 (flags & VRING_DESC_F_WRITE) ?
				 DMA_FROM_DEVICE : DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		dma_unmap_page(vring_dma_dev(vq),
			       virtio64_to_cpu(vq->vq.vdev, desc->addr),
			       virtio32_to_cpu(vq->vq.vdev, desc->len),
			       (flags & VRING_DESC_F_WRITE) ?
			       DMA_FROM_DEVICE : DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल काष्ठा vring_desc *alloc_indirect_split(काष्ठा virtqueue *_vq,
					       अचिन्हित पूर्णांक total_sg,
					       gfp_t gfp)
अणु
	काष्ठा vring_desc *desc;
	अचिन्हित पूर्णांक i;

	/*
	 * We require lowmem mappings क्रम the descriptors because
	 * otherwise virt_to_phys will give us bogus addresses in the
	 * virtqueue.
	 */
	gfp &= ~__GFP_HIGHMEM;

	desc = kदो_स्मृति_array(total_sg, माप(काष्ठा vring_desc), gfp);
	अगर (!desc)
		वापस शून्य;

	क्रम (i = 0; i < total_sg; i++)
		desc[i].next = cpu_to_virtio16(_vq->vdev, i + 1);
	वापस desc;
पूर्ण

अटल अंतरभूत पूर्णांक virtqueue_add_split(काष्ठा virtqueue *_vq,
				      काष्ठा scatterlist *sgs[],
				      अचिन्हित पूर्णांक total_sg,
				      अचिन्हित पूर्णांक out_sgs,
				      अचिन्हित पूर्णांक in_sgs,
				      व्योम *data,
				      व्योम *ctx,
				      gfp_t gfp)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);
	काष्ठा scatterlist *sg;
	काष्ठा vring_desc *desc;
	अचिन्हित पूर्णांक i, n, avail, descs_used, prev, err_idx;
	पूर्णांक head;
	bool indirect;

	START_USE(vq);

	BUG_ON(data == शून्य);
	BUG_ON(ctx && vq->indirect);

	अगर (unlikely(vq->broken)) अणु
		END_USE(vq);
		वापस -EIO;
	पूर्ण

	LAST_ADD_TIME_UPDATE(vq);

	BUG_ON(total_sg == 0);

	head = vq->मुक्त_head;

	अगर (virtqueue_use_indirect(_vq, total_sg))
		desc = alloc_indirect_split(_vq, total_sg, gfp);
	अन्यथा अणु
		desc = शून्य;
		WARN_ON_ONCE(total_sg > vq->split.vring.num && !vq->indirect);
	पूर्ण

	अगर (desc) अणु
		/* Use a single buffer which करोesn't जारी */
		indirect = true;
		/* Set up rest to use this indirect table. */
		i = 0;
		descs_used = 1;
	पूर्ण अन्यथा अणु
		indirect = false;
		desc = vq->split.vring.desc;
		i = head;
		descs_used = total_sg;
	पूर्ण

	अगर (vq->vq.num_मुक्त < descs_used) अणु
		pr_debug("Can't add buf len %i - avail = %i\n",
			 descs_used, vq->vq.num_मुक्त);
		/* FIXME: क्रम historical reasons, we क्रमce a notअगरy here अगर
		 * there are outgoing parts to the buffer.  Presumably the
		 * host should service the ring ASAP. */
		अगर (out_sgs)
			vq->notअगरy(&vq->vq);
		अगर (indirect)
			kमुक्त(desc);
		END_USE(vq);
		वापस -ENOSPC;
	पूर्ण

	क्रम (n = 0; n < out_sgs; n++) अणु
		क्रम (sg = sgs[n]; sg; sg = sg_next(sg)) अणु
			dma_addr_t addr = vring_map_one_sg(vq, sg, DMA_TO_DEVICE);
			अगर (vring_mapping_error(vq, addr))
				जाओ unmap_release;

			desc[i].flags = cpu_to_virtio16(_vq->vdev, VRING_DESC_F_NEXT);
			desc[i].addr = cpu_to_virtio64(_vq->vdev, addr);
			desc[i].len = cpu_to_virtio32(_vq->vdev, sg->length);
			prev = i;
			i = virtio16_to_cpu(_vq->vdev, desc[i].next);
		पूर्ण
	पूर्ण
	क्रम (; n < (out_sgs + in_sgs); n++) अणु
		क्रम (sg = sgs[n]; sg; sg = sg_next(sg)) अणु
			dma_addr_t addr = vring_map_one_sg(vq, sg, DMA_FROM_DEVICE);
			अगर (vring_mapping_error(vq, addr))
				जाओ unmap_release;

			desc[i].flags = cpu_to_virtio16(_vq->vdev, VRING_DESC_F_NEXT | VRING_DESC_F_WRITE);
			desc[i].addr = cpu_to_virtio64(_vq->vdev, addr);
			desc[i].len = cpu_to_virtio32(_vq->vdev, sg->length);
			prev = i;
			i = virtio16_to_cpu(_vq->vdev, desc[i].next);
		पूर्ण
	पूर्ण
	/* Last one करोesn't जारी. */
	desc[prev].flags &= cpu_to_virtio16(_vq->vdev, ~VRING_DESC_F_NEXT);

	अगर (indirect) अणु
		/* Now that the indirect table is filled in, map it. */
		dma_addr_t addr = vring_map_single(
			vq, desc, total_sg * माप(काष्ठा vring_desc),
			DMA_TO_DEVICE);
		अगर (vring_mapping_error(vq, addr))
			जाओ unmap_release;

		vq->split.vring.desc[head].flags = cpu_to_virtio16(_vq->vdev,
				VRING_DESC_F_INसूचीECT);
		vq->split.vring.desc[head].addr = cpu_to_virtio64(_vq->vdev,
				addr);

		vq->split.vring.desc[head].len = cpu_to_virtio32(_vq->vdev,
				total_sg * माप(काष्ठा vring_desc));
	पूर्ण

	/* We're using some buffers from the मुक्त list. */
	vq->vq.num_मुक्त -= descs_used;

	/* Update मुक्त poपूर्णांकer */
	अगर (indirect)
		vq->मुक्त_head = virtio16_to_cpu(_vq->vdev,
					vq->split.vring.desc[head].next);
	अन्यथा
		vq->मुक्त_head = i;

	/* Store token and indirect buffer state. */
	vq->split.desc_state[head].data = data;
	अगर (indirect)
		vq->split.desc_state[head].indir_desc = desc;
	अन्यथा
		vq->split.desc_state[head].indir_desc = ctx;

	/* Put entry in available array (but करोn't update avail->idx until they
	 * करो sync). */
	avail = vq->split.avail_idx_shaकरोw & (vq->split.vring.num - 1);
	vq->split.vring.avail->ring[avail] = cpu_to_virtio16(_vq->vdev, head);

	/* Descriptors and available array need to be set beक्रमe we expose the
	 * new available array entries. */
	virtio_wmb(vq->weak_barriers);
	vq->split.avail_idx_shaकरोw++;
	vq->split.vring.avail->idx = cpu_to_virtio16(_vq->vdev,
						vq->split.avail_idx_shaकरोw);
	vq->num_added++;

	pr_debug("Added buffer head %i to %p\n", head, vq);
	END_USE(vq);

	/* This is very unlikely, but theoretically possible.  Kick
	 * just in हाल. */
	अगर (unlikely(vq->num_added == (1 << 16) - 1))
		virtqueue_kick(_vq);

	वापस 0;

unmap_release:
	err_idx = i;

	अगर (indirect)
		i = 0;
	अन्यथा
		i = head;

	क्रम (n = 0; n < total_sg; n++) अणु
		अगर (i == err_idx)
			अवरोध;
		vring_unmap_one_split(vq, &desc[i]);
		i = virtio16_to_cpu(_vq->vdev, desc[i].next);
	पूर्ण

	अगर (indirect)
		kमुक्त(desc);

	END_USE(vq);
	वापस -ENOMEM;
पूर्ण

अटल bool virtqueue_kick_prepare_split(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);
	u16 new, old;
	bool needs_kick;

	START_USE(vq);
	/* We need to expose available array entries beक्रमe checking avail
	 * event. */
	virtio_mb(vq->weak_barriers);

	old = vq->split.avail_idx_shaकरोw - vq->num_added;
	new = vq->split.avail_idx_shaकरोw;
	vq->num_added = 0;

	LAST_ADD_TIME_CHECK(vq);
	LAST_ADD_TIME_INVALID(vq);

	अगर (vq->event) अणु
		needs_kick = vring_need_event(virtio16_to_cpu(_vq->vdev,
					vring_avail_event(&vq->split.vring)),
					      new, old);
	पूर्ण अन्यथा अणु
		needs_kick = !(vq->split.vring.used->flags &
					cpu_to_virtio16(_vq->vdev,
						VRING_USED_F_NO_NOTIFY));
	पूर्ण
	END_USE(vq);
	वापस needs_kick;
पूर्ण

अटल व्योम detach_buf_split(काष्ठा vring_virtqueue *vq, अचिन्हित पूर्णांक head,
			     व्योम **ctx)
अणु
	अचिन्हित पूर्णांक i, j;
	__virtio16 nextflag = cpu_to_virtio16(vq->vq.vdev, VRING_DESC_F_NEXT);

	/* Clear data ptr. */
	vq->split.desc_state[head].data = शून्य;

	/* Put back on मुक्त list: unmap first-level descriptors and find end */
	i = head;

	जबतक (vq->split.vring.desc[i].flags & nextflag) अणु
		vring_unmap_one_split(vq, &vq->split.vring.desc[i]);
		i = virtio16_to_cpu(vq->vq.vdev, vq->split.vring.desc[i].next);
		vq->vq.num_मुक्त++;
	पूर्ण

	vring_unmap_one_split(vq, &vq->split.vring.desc[i]);
	vq->split.vring.desc[i].next = cpu_to_virtio16(vq->vq.vdev,
						vq->मुक्त_head);
	vq->मुक्त_head = head;

	/* Plus final descriptor */
	vq->vq.num_मुक्त++;

	अगर (vq->indirect) अणु
		काष्ठा vring_desc *indir_desc =
				vq->split.desc_state[head].indir_desc;
		u32 len;

		/* Free the indirect table, अगर any, now that it's unmapped. */
		अगर (!indir_desc)
			वापस;

		len = virtio32_to_cpu(vq->vq.vdev,
				vq->split.vring.desc[head].len);

		BUG_ON(!(vq->split.vring.desc[head].flags &
			 cpu_to_virtio16(vq->vq.vdev, VRING_DESC_F_INसूचीECT)));
		BUG_ON(len == 0 || len % माप(काष्ठा vring_desc));

		क्रम (j = 0; j < len / माप(काष्ठा vring_desc); j++)
			vring_unmap_one_split(vq, &indir_desc[j]);

		kमुक्त(indir_desc);
		vq->split.desc_state[head].indir_desc = शून्य;
	पूर्ण अन्यथा अगर (ctx) अणु
		*ctx = vq->split.desc_state[head].indir_desc;
	पूर्ण
पूर्ण

अटल अंतरभूत bool more_used_split(स्थिर काष्ठा vring_virtqueue *vq)
अणु
	वापस vq->last_used_idx != virtio16_to_cpu(vq->vq.vdev,
			vq->split.vring.used->idx);
पूर्ण

अटल व्योम *virtqueue_get_buf_ctx_split(काष्ठा virtqueue *_vq,
					 अचिन्हित पूर्णांक *len,
					 व्योम **ctx)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);
	व्योम *ret;
	अचिन्हित पूर्णांक i;
	u16 last_used;

	START_USE(vq);

	अगर (unlikely(vq->broken)) अणु
		END_USE(vq);
		वापस शून्य;
	पूर्ण

	अगर (!more_used_split(vq)) अणु
		pr_debug("No more buffers in queue\n");
		END_USE(vq);
		वापस शून्य;
	पूर्ण

	/* Only get used array entries after they have been exposed by host. */
	virtio_rmb(vq->weak_barriers);

	last_used = (vq->last_used_idx & (vq->split.vring.num - 1));
	i = virtio32_to_cpu(_vq->vdev,
			vq->split.vring.used->ring[last_used].id);
	*len = virtio32_to_cpu(_vq->vdev,
			vq->split.vring.used->ring[last_used].len);

	अगर (unlikely(i >= vq->split.vring.num)) अणु
		BAD_RING(vq, "id %u out of range\n", i);
		वापस शून्य;
	पूर्ण
	अगर (unlikely(!vq->split.desc_state[i].data)) अणु
		BAD_RING(vq, "id %u is not a head!\n", i);
		वापस शून्य;
	पूर्ण

	/* detach_buf_split clears data, so grab it now. */
	ret = vq->split.desc_state[i].data;
	detach_buf_split(vq, i, ctx);
	vq->last_used_idx++;
	/* If we expect an पूर्णांकerrupt क्रम the next entry, tell host
	 * by writing event index and flush out the ग_लिखो beक्रमe
	 * the पढ़ो in the next get_buf call. */
	अगर (!(vq->split.avail_flags_shaकरोw & VRING_AVAIL_F_NO_INTERRUPT))
		virtio_store_mb(vq->weak_barriers,
				&vring_used_event(&vq->split.vring),
				cpu_to_virtio16(_vq->vdev, vq->last_used_idx));

	LAST_ADD_TIME_INVALID(vq);

	END_USE(vq);
	वापस ret;
पूर्ण

अटल व्योम virtqueue_disable_cb_split(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	अगर (!(vq->split.avail_flags_shaकरोw & VRING_AVAIL_F_NO_INTERRUPT)) अणु
		vq->split.avail_flags_shaकरोw |= VRING_AVAIL_F_NO_INTERRUPT;
		अगर (!vq->event)
			vq->split.vring.avail->flags =
				cpu_to_virtio16(_vq->vdev,
						vq->split.avail_flags_shaकरोw);
	पूर्ण
पूर्ण

अटल अचिन्हित virtqueue_enable_cb_prepare_split(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);
	u16 last_used_idx;

	START_USE(vq);

	/* We optimistically turn back on पूर्णांकerrupts, then check अगर there was
	 * more to करो. */
	/* Depending on the VIRTIO_RING_F_EVENT_IDX feature, we need to
	 * either clear the flags bit or poपूर्णांक the event index at the next
	 * entry. Always करो both to keep code simple. */
	अगर (vq->split.avail_flags_shaकरोw & VRING_AVAIL_F_NO_INTERRUPT) अणु
		vq->split.avail_flags_shaकरोw &= ~VRING_AVAIL_F_NO_INTERRUPT;
		अगर (!vq->event)
			vq->split.vring.avail->flags =
				cpu_to_virtio16(_vq->vdev,
						vq->split.avail_flags_shaकरोw);
	पूर्ण
	vring_used_event(&vq->split.vring) = cpu_to_virtio16(_vq->vdev,
			last_used_idx = vq->last_used_idx);
	END_USE(vq);
	वापस last_used_idx;
पूर्ण

अटल bool virtqueue_poll_split(काष्ठा virtqueue *_vq, अचिन्हित last_used_idx)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	वापस (u16)last_used_idx != virtio16_to_cpu(_vq->vdev,
			vq->split.vring.used->idx);
पूर्ण

अटल bool virtqueue_enable_cb_delayed_split(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);
	u16 bufs;

	START_USE(vq);

	/* We optimistically turn back on पूर्णांकerrupts, then check अगर there was
	 * more to करो. */
	/* Depending on the VIRTIO_RING_F_USED_EVENT_IDX feature, we need to
	 * either clear the flags bit or poपूर्णांक the event index at the next
	 * entry. Always update the event index to keep code simple. */
	अगर (vq->split.avail_flags_shaकरोw & VRING_AVAIL_F_NO_INTERRUPT) अणु
		vq->split.avail_flags_shaकरोw &= ~VRING_AVAIL_F_NO_INTERRUPT;
		अगर (!vq->event)
			vq->split.vring.avail->flags =
				cpu_to_virtio16(_vq->vdev,
						vq->split.avail_flags_shaकरोw);
	पूर्ण
	/* TODO: tune this threshold */
	bufs = (u16)(vq->split.avail_idx_shaकरोw - vq->last_used_idx) * 3 / 4;

	virtio_store_mb(vq->weak_barriers,
			&vring_used_event(&vq->split.vring),
			cpu_to_virtio16(_vq->vdev, vq->last_used_idx + bufs));

	अगर (unlikely((u16)(virtio16_to_cpu(_vq->vdev, vq->split.vring.used->idx)
					- vq->last_used_idx) > bufs)) अणु
		END_USE(vq);
		वापस false;
	पूर्ण

	END_USE(vq);
	वापस true;
पूर्ण

अटल व्योम *virtqueue_detach_unused_buf_split(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);
	अचिन्हित पूर्णांक i;
	व्योम *buf;

	START_USE(vq);

	क्रम (i = 0; i < vq->split.vring.num; i++) अणु
		अगर (!vq->split.desc_state[i].data)
			जारी;
		/* detach_buf_split clears data, so grab it now. */
		buf = vq->split.desc_state[i].data;
		detach_buf_split(vq, i, शून्य);
		vq->split.avail_idx_shaकरोw--;
		vq->split.vring.avail->idx = cpu_to_virtio16(_vq->vdev,
				vq->split.avail_idx_shaकरोw);
		END_USE(vq);
		वापस buf;
	पूर्ण
	/* That should have मुक्तd everything. */
	BUG_ON(vq->vq.num_मुक्त != vq->split.vring.num);

	END_USE(vq);
	वापस शून्य;
पूर्ण

अटल काष्ठा virtqueue *vring_create_virtqueue_split(
	अचिन्हित पूर्णांक index,
	अचिन्हित पूर्णांक num,
	अचिन्हित पूर्णांक vring_align,
	काष्ठा virtio_device *vdev,
	bool weak_barriers,
	bool may_reduce_num,
	bool context,
	bool (*notअगरy)(काष्ठा virtqueue *),
	व्योम (*callback)(काष्ठा virtqueue *),
	स्थिर अक्षर *name)
अणु
	काष्ठा virtqueue *vq;
	व्योम *queue = शून्य;
	dma_addr_t dma_addr;
	माप_प्रकार queue_size_in_bytes;
	काष्ठा vring vring;

	/* We assume num is a घातer of 2. */
	अगर (num & (num - 1)) अणु
		dev_warn(&vdev->dev, "Bad virtqueue length %u\n", num);
		वापस शून्य;
	पूर्ण

	/* TODO: allocate each queue chunk inभागidually */
	क्रम (; num && vring_size(num, vring_align) > PAGE_SIZE; num /= 2) अणु
		queue = vring_alloc_queue(vdev, vring_size(num, vring_align),
					  &dma_addr,
					  GFP_KERNEL|__GFP_NOWARN|__GFP_ZERO);
		अगर (queue)
			अवरोध;
		अगर (!may_reduce_num)
			वापस शून्य;
	पूर्ण

	अगर (!num)
		वापस शून्य;

	अगर (!queue) अणु
		/* Try to get a single page. You are my only hope! */
		queue = vring_alloc_queue(vdev, vring_size(num, vring_align),
					  &dma_addr, GFP_KERNEL|__GFP_ZERO);
	पूर्ण
	अगर (!queue)
		वापस शून्य;

	queue_size_in_bytes = vring_size(num, vring_align);
	vring_init(&vring, num, queue, vring_align);

	vq = __vring_new_virtqueue(index, vring, vdev, weak_barriers, context,
				   notअगरy, callback, name);
	अगर (!vq) अणु
		vring_मुक्त_queue(vdev, queue_size_in_bytes, queue,
				 dma_addr);
		वापस शून्य;
	पूर्ण

	to_vvq(vq)->split.queue_dma_addr = dma_addr;
	to_vvq(vq)->split.queue_size_in_bytes = queue_size_in_bytes;
	to_vvq(vq)->we_own_ring = true;

	वापस vq;
पूर्ण


/*
 * Packed ring specअगरic functions - *_packed().
 */

अटल व्योम vring_unmap_state_packed(स्थिर काष्ठा vring_virtqueue *vq,
				     काष्ठा vring_desc_extra_packed *state)
अणु
	u16 flags;

	अगर (!vq->use_dma_api)
		वापस;

	flags = state->flags;

	अगर (flags & VRING_DESC_F_INसूचीECT) अणु
		dma_unmap_single(vring_dma_dev(vq),
				 state->addr, state->len,
				 (flags & VRING_DESC_F_WRITE) ?
				 DMA_FROM_DEVICE : DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		dma_unmap_page(vring_dma_dev(vq),
			       state->addr, state->len,
			       (flags & VRING_DESC_F_WRITE) ?
			       DMA_FROM_DEVICE : DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल व्योम vring_unmap_desc_packed(स्थिर काष्ठा vring_virtqueue *vq,
				   काष्ठा vring_packed_desc *desc)
अणु
	u16 flags;

	अगर (!vq->use_dma_api)
		वापस;

	flags = le16_to_cpu(desc->flags);

	अगर (flags & VRING_DESC_F_INसूचीECT) अणु
		dma_unmap_single(vring_dma_dev(vq),
				 le64_to_cpu(desc->addr),
				 le32_to_cpu(desc->len),
				 (flags & VRING_DESC_F_WRITE) ?
				 DMA_FROM_DEVICE : DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		dma_unmap_page(vring_dma_dev(vq),
			       le64_to_cpu(desc->addr),
			       le32_to_cpu(desc->len),
			       (flags & VRING_DESC_F_WRITE) ?
			       DMA_FROM_DEVICE : DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल काष्ठा vring_packed_desc *alloc_indirect_packed(अचिन्हित पूर्णांक total_sg,
						       gfp_t gfp)
अणु
	काष्ठा vring_packed_desc *desc;

	/*
	 * We require lowmem mappings क्रम the descriptors because
	 * otherwise virt_to_phys will give us bogus addresses in the
	 * virtqueue.
	 */
	gfp &= ~__GFP_HIGHMEM;

	desc = kदो_स्मृति_array(total_sg, माप(काष्ठा vring_packed_desc), gfp);

	वापस desc;
पूर्ण

अटल पूर्णांक virtqueue_add_indirect_packed(काष्ठा vring_virtqueue *vq,
				       काष्ठा scatterlist *sgs[],
				       अचिन्हित पूर्णांक total_sg,
				       अचिन्हित पूर्णांक out_sgs,
				       अचिन्हित पूर्णांक in_sgs,
				       व्योम *data,
				       gfp_t gfp)
अणु
	काष्ठा vring_packed_desc *desc;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i, n, err_idx;
	u16 head, id;
	dma_addr_t addr;

	head = vq->packed.next_avail_idx;
	desc = alloc_indirect_packed(total_sg, gfp);

	अगर (unlikely(vq->vq.num_मुक्त < 1)) अणु
		pr_debug("Can't add buf len 1 - avail = 0\n");
		kमुक्त(desc);
		END_USE(vq);
		वापस -ENOSPC;
	पूर्ण

	i = 0;
	id = vq->मुक्त_head;
	BUG_ON(id == vq->packed.vring.num);

	क्रम (n = 0; n < out_sgs + in_sgs; n++) अणु
		क्रम (sg = sgs[n]; sg; sg = sg_next(sg)) अणु
			addr = vring_map_one_sg(vq, sg, n < out_sgs ?
					DMA_TO_DEVICE : DMA_FROM_DEVICE);
			अगर (vring_mapping_error(vq, addr))
				जाओ unmap_release;

			desc[i].flags = cpu_to_le16(n < out_sgs ?
						0 : VRING_DESC_F_WRITE);
			desc[i].addr = cpu_to_le64(addr);
			desc[i].len = cpu_to_le32(sg->length);
			i++;
		पूर्ण
	पूर्ण

	/* Now that the indirect table is filled in, map it. */
	addr = vring_map_single(vq, desc,
			total_sg * माप(काष्ठा vring_packed_desc),
			DMA_TO_DEVICE);
	अगर (vring_mapping_error(vq, addr))
		जाओ unmap_release;

	vq->packed.vring.desc[head].addr = cpu_to_le64(addr);
	vq->packed.vring.desc[head].len = cpu_to_le32(total_sg *
				माप(काष्ठा vring_packed_desc));
	vq->packed.vring.desc[head].id = cpu_to_le16(id);

	अगर (vq->use_dma_api) अणु
		vq->packed.desc_extra[id].addr = addr;
		vq->packed.desc_extra[id].len = total_sg *
				माप(काष्ठा vring_packed_desc);
		vq->packed.desc_extra[id].flags = VRING_DESC_F_INसूचीECT |
						  vq->packed.avail_used_flags;
	पूर्ण

	/*
	 * A driver MUST NOT make the first descriptor in the list
	 * available beक्रमe all subsequent descriptors comprising
	 * the list are made available.
	 */
	virtio_wmb(vq->weak_barriers);
	vq->packed.vring.desc[head].flags = cpu_to_le16(VRING_DESC_F_INसूचीECT |
						vq->packed.avail_used_flags);

	/* We're using some buffers from the मुक्त list. */
	vq->vq.num_मुक्त -= 1;

	/* Update मुक्त poपूर्णांकer */
	n = head + 1;
	अगर (n >= vq->packed.vring.num) अणु
		n = 0;
		vq->packed.avail_wrap_counter ^= 1;
		vq->packed.avail_used_flags ^=
				1 << VRING_PACKED_DESC_F_AVAIL |
				1 << VRING_PACKED_DESC_F_USED;
	पूर्ण
	vq->packed.next_avail_idx = n;
	vq->मुक्त_head = vq->packed.desc_state[id].next;

	/* Store token and indirect buffer state. */
	vq->packed.desc_state[id].num = 1;
	vq->packed.desc_state[id].data = data;
	vq->packed.desc_state[id].indir_desc = desc;
	vq->packed.desc_state[id].last = id;

	vq->num_added += 1;

	pr_debug("Added buffer head %i to %p\n", head, vq);
	END_USE(vq);

	वापस 0;

unmap_release:
	err_idx = i;

	क्रम (i = 0; i < err_idx; i++)
		vring_unmap_desc_packed(vq, &desc[i]);

	kमुक्त(desc);

	END_USE(vq);
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत पूर्णांक virtqueue_add_packed(काष्ठा virtqueue *_vq,
				       काष्ठा scatterlist *sgs[],
				       अचिन्हित पूर्णांक total_sg,
				       अचिन्हित पूर्णांक out_sgs,
				       अचिन्हित पूर्णांक in_sgs,
				       व्योम *data,
				       व्योम *ctx,
				       gfp_t gfp)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);
	काष्ठा vring_packed_desc *desc;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i, n, c, descs_used, err_idx;
	__le16 head_flags, flags;
	u16 head, id, prev, curr, avail_used_flags;

	START_USE(vq);

	BUG_ON(data == शून्य);
	BUG_ON(ctx && vq->indirect);

	अगर (unlikely(vq->broken)) अणु
		END_USE(vq);
		वापस -EIO;
	पूर्ण

	LAST_ADD_TIME_UPDATE(vq);

	BUG_ON(total_sg == 0);

	अगर (virtqueue_use_indirect(_vq, total_sg))
		वापस virtqueue_add_indirect_packed(vq, sgs, total_sg,
				out_sgs, in_sgs, data, gfp);

	head = vq->packed.next_avail_idx;
	avail_used_flags = vq->packed.avail_used_flags;

	WARN_ON_ONCE(total_sg > vq->packed.vring.num && !vq->indirect);

	desc = vq->packed.vring.desc;
	i = head;
	descs_used = total_sg;

	अगर (unlikely(vq->vq.num_मुक्त < descs_used)) अणु
		pr_debug("Can't add buf len %i - avail = %i\n",
			 descs_used, vq->vq.num_मुक्त);
		END_USE(vq);
		वापस -ENOSPC;
	पूर्ण

	id = vq->मुक्त_head;
	BUG_ON(id == vq->packed.vring.num);

	curr = id;
	c = 0;
	क्रम (n = 0; n < out_sgs + in_sgs; n++) अणु
		क्रम (sg = sgs[n]; sg; sg = sg_next(sg)) अणु
			dma_addr_t addr = vring_map_one_sg(vq, sg, n < out_sgs ?
					DMA_TO_DEVICE : DMA_FROM_DEVICE);
			अगर (vring_mapping_error(vq, addr))
				जाओ unmap_release;

			flags = cpu_to_le16(vq->packed.avail_used_flags |
				    (++c == total_sg ? 0 : VRING_DESC_F_NEXT) |
				    (n < out_sgs ? 0 : VRING_DESC_F_WRITE));
			अगर (i == head)
				head_flags = flags;
			अन्यथा
				desc[i].flags = flags;

			desc[i].addr = cpu_to_le64(addr);
			desc[i].len = cpu_to_le32(sg->length);
			desc[i].id = cpu_to_le16(id);

			अगर (unlikely(vq->use_dma_api)) अणु
				vq->packed.desc_extra[curr].addr = addr;
				vq->packed.desc_extra[curr].len = sg->length;
				vq->packed.desc_extra[curr].flags =
					le16_to_cpu(flags);
			पूर्ण
			prev = curr;
			curr = vq->packed.desc_state[curr].next;

			अगर ((unlikely(++i >= vq->packed.vring.num))) अणु
				i = 0;
				vq->packed.avail_used_flags ^=
					1 << VRING_PACKED_DESC_F_AVAIL |
					1 << VRING_PACKED_DESC_F_USED;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (i < head)
		vq->packed.avail_wrap_counter ^= 1;

	/* We're using some buffers from the मुक्त list. */
	vq->vq.num_मुक्त -= descs_used;

	/* Update मुक्त poपूर्णांकer */
	vq->packed.next_avail_idx = i;
	vq->मुक्त_head = curr;

	/* Store token. */
	vq->packed.desc_state[id].num = descs_used;
	vq->packed.desc_state[id].data = data;
	vq->packed.desc_state[id].indir_desc = ctx;
	vq->packed.desc_state[id].last = prev;

	/*
	 * A driver MUST NOT make the first descriptor in the list
	 * available beक्रमe all subsequent descriptors comprising
	 * the list are made available.
	 */
	virtio_wmb(vq->weak_barriers);
	vq->packed.vring.desc[head].flags = head_flags;
	vq->num_added += descs_used;

	pr_debug("Added buffer head %i to %p\n", head, vq);
	END_USE(vq);

	वापस 0;

unmap_release:
	err_idx = i;
	i = head;

	vq->packed.avail_used_flags = avail_used_flags;

	क्रम (n = 0; n < total_sg; n++) अणु
		अगर (i == err_idx)
			अवरोध;
		vring_unmap_desc_packed(vq, &desc[i]);
		i++;
		अगर (i >= vq->packed.vring.num)
			i = 0;
	पूर्ण

	END_USE(vq);
	वापस -EIO;
पूर्ण

अटल bool virtqueue_kick_prepare_packed(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);
	u16 new, old, off_wrap, flags, wrap_counter, event_idx;
	bool needs_kick;
	जोड़ अणु
		काष्ठा अणु
			__le16 off_wrap;
			__le16 flags;
		पूर्ण;
		u32 u32;
	पूर्ण snapshot;

	START_USE(vq);

	/*
	 * We need to expose the new flags value beक्रमe checking notअगरication
	 * suppressions.
	 */
	virtio_mb(vq->weak_barriers);

	old = vq->packed.next_avail_idx - vq->num_added;
	new = vq->packed.next_avail_idx;
	vq->num_added = 0;

	snapshot.u32 = *(u32 *)vq->packed.vring.device;
	flags = le16_to_cpu(snapshot.flags);

	LAST_ADD_TIME_CHECK(vq);
	LAST_ADD_TIME_INVALID(vq);

	अगर (flags != VRING_PACKED_EVENT_FLAG_DESC) अणु
		needs_kick = (flags != VRING_PACKED_EVENT_FLAG_DISABLE);
		जाओ out;
	पूर्ण

	off_wrap = le16_to_cpu(snapshot.off_wrap);

	wrap_counter = off_wrap >> VRING_PACKED_EVENT_F_WRAP_CTR;
	event_idx = off_wrap & ~(1 << VRING_PACKED_EVENT_F_WRAP_CTR);
	अगर (wrap_counter != vq->packed.avail_wrap_counter)
		event_idx -= vq->packed.vring.num;

	needs_kick = vring_need_event(event_idx, new, old);
out:
	END_USE(vq);
	वापस needs_kick;
पूर्ण

अटल व्योम detach_buf_packed(काष्ठा vring_virtqueue *vq,
			      अचिन्हित पूर्णांक id, व्योम **ctx)
अणु
	काष्ठा vring_desc_state_packed *state = शून्य;
	काष्ठा vring_packed_desc *desc;
	अचिन्हित पूर्णांक i, curr;

	state = &vq->packed.desc_state[id];

	/* Clear data ptr. */
	state->data = शून्य;

	vq->packed.desc_state[state->last].next = vq->मुक्त_head;
	vq->मुक्त_head = id;
	vq->vq.num_मुक्त += state->num;

	अगर (unlikely(vq->use_dma_api)) अणु
		curr = id;
		क्रम (i = 0; i < state->num; i++) अणु
			vring_unmap_state_packed(vq,
				&vq->packed.desc_extra[curr]);
			curr = vq->packed.desc_state[curr].next;
		पूर्ण
	पूर्ण

	अगर (vq->indirect) अणु
		u32 len;

		/* Free the indirect table, अगर any, now that it's unmapped. */
		desc = state->indir_desc;
		अगर (!desc)
			वापस;

		अगर (vq->use_dma_api) अणु
			len = vq->packed.desc_extra[id].len;
			क्रम (i = 0; i < len / माप(काष्ठा vring_packed_desc);
					i++)
				vring_unmap_desc_packed(vq, &desc[i]);
		पूर्ण
		kमुक्त(desc);
		state->indir_desc = शून्य;
	पूर्ण अन्यथा अगर (ctx) अणु
		*ctx = state->indir_desc;
	पूर्ण
पूर्ण

अटल अंतरभूत bool is_used_desc_packed(स्थिर काष्ठा vring_virtqueue *vq,
				       u16 idx, bool used_wrap_counter)
अणु
	bool avail, used;
	u16 flags;

	flags = le16_to_cpu(vq->packed.vring.desc[idx].flags);
	avail = !!(flags & (1 << VRING_PACKED_DESC_F_AVAIL));
	used = !!(flags & (1 << VRING_PACKED_DESC_F_USED));

	वापस avail == used && used == used_wrap_counter;
पूर्ण

अटल अंतरभूत bool more_used_packed(स्थिर काष्ठा vring_virtqueue *vq)
अणु
	वापस is_used_desc_packed(vq, vq->last_used_idx,
			vq->packed.used_wrap_counter);
पूर्ण

अटल व्योम *virtqueue_get_buf_ctx_packed(काष्ठा virtqueue *_vq,
					  अचिन्हित पूर्णांक *len,
					  व्योम **ctx)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);
	u16 last_used, id;
	व्योम *ret;

	START_USE(vq);

	अगर (unlikely(vq->broken)) अणु
		END_USE(vq);
		वापस शून्य;
	पूर्ण

	अगर (!more_used_packed(vq)) अणु
		pr_debug("No more buffers in queue\n");
		END_USE(vq);
		वापस शून्य;
	पूर्ण

	/* Only get used elements after they have been exposed by host. */
	virtio_rmb(vq->weak_barriers);

	last_used = vq->last_used_idx;
	id = le16_to_cpu(vq->packed.vring.desc[last_used].id);
	*len = le32_to_cpu(vq->packed.vring.desc[last_used].len);

	अगर (unlikely(id >= vq->packed.vring.num)) अणु
		BAD_RING(vq, "id %u out of range\n", id);
		वापस शून्य;
	पूर्ण
	अगर (unlikely(!vq->packed.desc_state[id].data)) अणु
		BAD_RING(vq, "id %u is not a head!\n", id);
		वापस शून्य;
	पूर्ण

	/* detach_buf_packed clears data, so grab it now. */
	ret = vq->packed.desc_state[id].data;
	detach_buf_packed(vq, id, ctx);

	vq->last_used_idx += vq->packed.desc_state[id].num;
	अगर (unlikely(vq->last_used_idx >= vq->packed.vring.num)) अणु
		vq->last_used_idx -= vq->packed.vring.num;
		vq->packed.used_wrap_counter ^= 1;
	पूर्ण

	/*
	 * If we expect an पूर्णांकerrupt क्रम the next entry, tell host
	 * by writing event index and flush out the ग_लिखो beक्रमe
	 * the पढ़ो in the next get_buf call.
	 */
	अगर (vq->packed.event_flags_shaकरोw == VRING_PACKED_EVENT_FLAG_DESC)
		virtio_store_mb(vq->weak_barriers,
				&vq->packed.vring.driver->off_wrap,
				cpu_to_le16(vq->last_used_idx |
					(vq->packed.used_wrap_counter <<
					 VRING_PACKED_EVENT_F_WRAP_CTR)));

	LAST_ADD_TIME_INVALID(vq);

	END_USE(vq);
	वापस ret;
पूर्ण

अटल व्योम virtqueue_disable_cb_packed(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	अगर (vq->packed.event_flags_shaकरोw != VRING_PACKED_EVENT_FLAG_DISABLE) अणु
		vq->packed.event_flags_shaकरोw = VRING_PACKED_EVENT_FLAG_DISABLE;
		vq->packed.vring.driver->flags =
			cpu_to_le16(vq->packed.event_flags_shaकरोw);
	पूर्ण
पूर्ण

अटल अचिन्हित virtqueue_enable_cb_prepare_packed(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	START_USE(vq);

	/*
	 * We optimistically turn back on पूर्णांकerrupts, then check अगर there was
	 * more to करो.
	 */

	अगर (vq->event) अणु
		vq->packed.vring.driver->off_wrap =
			cpu_to_le16(vq->last_used_idx |
				(vq->packed.used_wrap_counter <<
				 VRING_PACKED_EVENT_F_WRAP_CTR));
		/*
		 * We need to update event offset and event wrap
		 * counter first beक्रमe updating event flags.
		 */
		virtio_wmb(vq->weak_barriers);
	पूर्ण

	अगर (vq->packed.event_flags_shaकरोw == VRING_PACKED_EVENT_FLAG_DISABLE) अणु
		vq->packed.event_flags_shaकरोw = vq->event ?
				VRING_PACKED_EVENT_FLAG_DESC :
				VRING_PACKED_EVENT_FLAG_ENABLE;
		vq->packed.vring.driver->flags =
				cpu_to_le16(vq->packed.event_flags_shaकरोw);
	पूर्ण

	END_USE(vq);
	वापस vq->last_used_idx | ((u16)vq->packed.used_wrap_counter <<
			VRING_PACKED_EVENT_F_WRAP_CTR);
पूर्ण

अटल bool virtqueue_poll_packed(काष्ठा virtqueue *_vq, u16 off_wrap)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);
	bool wrap_counter;
	u16 used_idx;

	wrap_counter = off_wrap >> VRING_PACKED_EVENT_F_WRAP_CTR;
	used_idx = off_wrap & ~(1 << VRING_PACKED_EVENT_F_WRAP_CTR);

	वापस is_used_desc_packed(vq, used_idx, wrap_counter);
पूर्ण

अटल bool virtqueue_enable_cb_delayed_packed(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);
	u16 used_idx, wrap_counter;
	u16 bufs;

	START_USE(vq);

	/*
	 * We optimistically turn back on पूर्णांकerrupts, then check अगर there was
	 * more to करो.
	 */

	अगर (vq->event) अणु
		/* TODO: tune this threshold */
		bufs = (vq->packed.vring.num - vq->vq.num_मुक्त) * 3 / 4;
		wrap_counter = vq->packed.used_wrap_counter;

		used_idx = vq->last_used_idx + bufs;
		अगर (used_idx >= vq->packed.vring.num) अणु
			used_idx -= vq->packed.vring.num;
			wrap_counter ^= 1;
		पूर्ण

		vq->packed.vring.driver->off_wrap = cpu_to_le16(used_idx |
			(wrap_counter << VRING_PACKED_EVENT_F_WRAP_CTR));

		/*
		 * We need to update event offset and event wrap
		 * counter first beक्रमe updating event flags.
		 */
		virtio_wmb(vq->weak_barriers);
	पूर्ण

	अगर (vq->packed.event_flags_shaकरोw == VRING_PACKED_EVENT_FLAG_DISABLE) अणु
		vq->packed.event_flags_shaकरोw = vq->event ?
				VRING_PACKED_EVENT_FLAG_DESC :
				VRING_PACKED_EVENT_FLAG_ENABLE;
		vq->packed.vring.driver->flags =
				cpu_to_le16(vq->packed.event_flags_shaकरोw);
	पूर्ण

	/*
	 * We need to update event suppression काष्ठाure first
	 * beक्रमe re-checking क्रम more used buffers.
	 */
	virtio_mb(vq->weak_barriers);

	अगर (is_used_desc_packed(vq,
				vq->last_used_idx,
				vq->packed.used_wrap_counter)) अणु
		END_USE(vq);
		वापस false;
	पूर्ण

	END_USE(vq);
	वापस true;
पूर्ण

अटल व्योम *virtqueue_detach_unused_buf_packed(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);
	अचिन्हित पूर्णांक i;
	व्योम *buf;

	START_USE(vq);

	क्रम (i = 0; i < vq->packed.vring.num; i++) अणु
		अगर (!vq->packed.desc_state[i].data)
			जारी;
		/* detach_buf clears data, so grab it now. */
		buf = vq->packed.desc_state[i].data;
		detach_buf_packed(vq, i, शून्य);
		END_USE(vq);
		वापस buf;
	पूर्ण
	/* That should have मुक्तd everything. */
	BUG_ON(vq->vq.num_मुक्त != vq->packed.vring.num);

	END_USE(vq);
	वापस शून्य;
पूर्ण

अटल काष्ठा virtqueue *vring_create_virtqueue_packed(
	अचिन्हित पूर्णांक index,
	अचिन्हित पूर्णांक num,
	अचिन्हित पूर्णांक vring_align,
	काष्ठा virtio_device *vdev,
	bool weak_barriers,
	bool may_reduce_num,
	bool context,
	bool (*notअगरy)(काष्ठा virtqueue *),
	व्योम (*callback)(काष्ठा virtqueue *),
	स्थिर अक्षर *name)
अणु
	काष्ठा vring_virtqueue *vq;
	काष्ठा vring_packed_desc *ring;
	काष्ठा vring_packed_desc_event *driver, *device;
	dma_addr_t ring_dma_addr, driver_event_dma_addr, device_event_dma_addr;
	माप_प्रकार ring_size_in_bytes, event_size_in_bytes;
	अचिन्हित पूर्णांक i;

	ring_size_in_bytes = num * माप(काष्ठा vring_packed_desc);

	ring = vring_alloc_queue(vdev, ring_size_in_bytes,
				 &ring_dma_addr,
				 GFP_KERNEL|__GFP_NOWARN|__GFP_ZERO);
	अगर (!ring)
		जाओ err_ring;

	event_size_in_bytes = माप(काष्ठा vring_packed_desc_event);

	driver = vring_alloc_queue(vdev, event_size_in_bytes,
				   &driver_event_dma_addr,
				   GFP_KERNEL|__GFP_NOWARN|__GFP_ZERO);
	अगर (!driver)
		जाओ err_driver;

	device = vring_alloc_queue(vdev, event_size_in_bytes,
				   &device_event_dma_addr,
				   GFP_KERNEL|__GFP_NOWARN|__GFP_ZERO);
	अगर (!device)
		जाओ err_device;

	vq = kदो_स्मृति(माप(*vq), GFP_KERNEL);
	अगर (!vq)
		जाओ err_vq;

	vq->vq.callback = callback;
	vq->vq.vdev = vdev;
	vq->vq.name = name;
	vq->vq.num_मुक्त = num;
	vq->vq.index = index;
	vq->we_own_ring = true;
	vq->notअगरy = notअगरy;
	vq->weak_barriers = weak_barriers;
	vq->broken = false;
	vq->last_used_idx = 0;
	vq->num_added = 0;
	vq->packed_ring = true;
	vq->use_dma_api = vring_use_dma_api(vdev);
#अगर_घोषित DEBUG
	vq->in_use = false;
	vq->last_add_समय_valid = false;
#पूर्ण_अगर

	vq->indirect = virtio_has_feature(vdev, VIRTIO_RING_F_INसूचीECT_DESC) &&
		!context;
	vq->event = virtio_has_feature(vdev, VIRTIO_RING_F_EVENT_IDX);

	अगर (virtio_has_feature(vdev, VIRTIO_F_ORDER_PLATFORM))
		vq->weak_barriers = false;

	vq->packed.ring_dma_addr = ring_dma_addr;
	vq->packed.driver_event_dma_addr = driver_event_dma_addr;
	vq->packed.device_event_dma_addr = device_event_dma_addr;

	vq->packed.ring_size_in_bytes = ring_size_in_bytes;
	vq->packed.event_size_in_bytes = event_size_in_bytes;

	vq->packed.vring.num = num;
	vq->packed.vring.desc = ring;
	vq->packed.vring.driver = driver;
	vq->packed.vring.device = device;

	vq->packed.next_avail_idx = 0;
	vq->packed.avail_wrap_counter = 1;
	vq->packed.used_wrap_counter = 1;
	vq->packed.event_flags_shaकरोw = 0;
	vq->packed.avail_used_flags = 1 << VRING_PACKED_DESC_F_AVAIL;

	vq->packed.desc_state = kदो_स्मृति_array(num,
			माप(काष्ठा vring_desc_state_packed),
			GFP_KERNEL);
	अगर (!vq->packed.desc_state)
		जाओ err_desc_state;

	स_रखो(vq->packed.desc_state, 0,
		num * माप(काष्ठा vring_desc_state_packed));

	/* Put everything in मुक्त lists. */
	vq->मुक्त_head = 0;
	क्रम (i = 0; i < num-1; i++)
		vq->packed.desc_state[i].next = i + 1;

	vq->packed.desc_extra = kदो_स्मृति_array(num,
			माप(काष्ठा vring_desc_extra_packed),
			GFP_KERNEL);
	अगर (!vq->packed.desc_extra)
		जाओ err_desc_extra;

	स_रखो(vq->packed.desc_extra, 0,
		num * माप(काष्ठा vring_desc_extra_packed));

	/* No callback?  Tell other side not to bother us. */
	अगर (!callback) अणु
		vq->packed.event_flags_shaकरोw = VRING_PACKED_EVENT_FLAG_DISABLE;
		vq->packed.vring.driver->flags =
			cpu_to_le16(vq->packed.event_flags_shaकरोw);
	पूर्ण

	list_add_tail(&vq->vq.list, &vdev->vqs);
	वापस &vq->vq;

err_desc_extra:
	kमुक्त(vq->packed.desc_state);
err_desc_state:
	kमुक्त(vq);
err_vq:
	vring_मुक्त_queue(vdev, event_size_in_bytes, device, device_event_dma_addr);
err_device:
	vring_मुक्त_queue(vdev, event_size_in_bytes, driver, driver_event_dma_addr);
err_driver:
	vring_मुक्त_queue(vdev, ring_size_in_bytes, ring, ring_dma_addr);
err_ring:
	वापस शून्य;
पूर्ण


/*
 * Generic functions and exported symbols.
 */

अटल अंतरभूत पूर्णांक virtqueue_add(काष्ठा virtqueue *_vq,
				काष्ठा scatterlist *sgs[],
				अचिन्हित पूर्णांक total_sg,
				अचिन्हित पूर्णांक out_sgs,
				अचिन्हित पूर्णांक in_sgs,
				व्योम *data,
				व्योम *ctx,
				gfp_t gfp)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	वापस vq->packed_ring ? virtqueue_add_packed(_vq, sgs, total_sg,
					out_sgs, in_sgs, data, ctx, gfp) :
				 virtqueue_add_split(_vq, sgs, total_sg,
					out_sgs, in_sgs, data, ctx, gfp);
पूर्ण

/**
 * virtqueue_add_sgs - expose buffers to other end
 * @_vq: the काष्ठा virtqueue we're talking about.
 * @sgs: array of terminated scatterlists.
 * @out_sgs: the number of scatterlists पढ़ोable by other side
 * @in_sgs: the number of scatterlists which are writable (after पढ़ोable ones)
 * @data: the token identअगरying the buffer.
 * @gfp: how to करो memory allocations (अगर necessary).
 *
 * Caller must ensure we करोn't call this with other virtqueue operations
 * at the same समय (except where noted).
 *
 * Returns zero or a negative error (ie. ENOSPC, ENOMEM, EIO).
 */
पूर्णांक virtqueue_add_sgs(काष्ठा virtqueue *_vq,
		      काष्ठा scatterlist *sgs[],
		      अचिन्हित पूर्णांक out_sgs,
		      अचिन्हित पूर्णांक in_sgs,
		      व्योम *data,
		      gfp_t gfp)
अणु
	अचिन्हित पूर्णांक i, total_sg = 0;

	/* Count them first. */
	क्रम (i = 0; i < out_sgs + in_sgs; i++) अणु
		काष्ठा scatterlist *sg;

		क्रम (sg = sgs[i]; sg; sg = sg_next(sg))
			total_sg++;
	पूर्ण
	वापस virtqueue_add(_vq, sgs, total_sg, out_sgs, in_sgs,
			     data, शून्य, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_add_sgs);

/**
 * virtqueue_add_outbuf - expose output buffers to other end
 * @vq: the काष्ठा virtqueue we're talking about.
 * @sg: scatterlist (must be well-क्रमmed and terminated!)
 * @num: the number of entries in @sg पढ़ोable by other side
 * @data: the token identअगरying the buffer.
 * @gfp: how to करो memory allocations (अगर necessary).
 *
 * Caller must ensure we करोn't call this with other virtqueue operations
 * at the same समय (except where noted).
 *
 * Returns zero or a negative error (ie. ENOSPC, ENOMEM, EIO).
 */
पूर्णांक virtqueue_add_outbuf(काष्ठा virtqueue *vq,
			 काष्ठा scatterlist *sg, अचिन्हित पूर्णांक num,
			 व्योम *data,
			 gfp_t gfp)
अणु
	वापस virtqueue_add(vq, &sg, num, 1, 0, data, शून्य, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_add_outbuf);

/**
 * virtqueue_add_inbuf - expose input buffers to other end
 * @vq: the काष्ठा virtqueue we're talking about.
 * @sg: scatterlist (must be well-क्रमmed and terminated!)
 * @num: the number of entries in @sg writable by other side
 * @data: the token identअगरying the buffer.
 * @gfp: how to करो memory allocations (अगर necessary).
 *
 * Caller must ensure we करोn't call this with other virtqueue operations
 * at the same समय (except where noted).
 *
 * Returns zero or a negative error (ie. ENOSPC, ENOMEM, EIO).
 */
पूर्णांक virtqueue_add_inbuf(काष्ठा virtqueue *vq,
			काष्ठा scatterlist *sg, अचिन्हित पूर्णांक num,
			व्योम *data,
			gfp_t gfp)
अणु
	वापस virtqueue_add(vq, &sg, num, 0, 1, data, शून्य, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_add_inbuf);

/**
 * virtqueue_add_inbuf_ctx - expose input buffers to other end
 * @vq: the काष्ठा virtqueue we're talking about.
 * @sg: scatterlist (must be well-क्रमmed and terminated!)
 * @num: the number of entries in @sg writable by other side
 * @data: the token identअगरying the buffer.
 * @ctx: extra context क्रम the token
 * @gfp: how to करो memory allocations (अगर necessary).
 *
 * Caller must ensure we करोn't call this with other virtqueue operations
 * at the same समय (except where noted).
 *
 * Returns zero or a negative error (ie. ENOSPC, ENOMEM, EIO).
 */
पूर्णांक virtqueue_add_inbuf_ctx(काष्ठा virtqueue *vq,
			काष्ठा scatterlist *sg, अचिन्हित पूर्णांक num,
			व्योम *data,
			व्योम *ctx,
			gfp_t gfp)
अणु
	वापस virtqueue_add(vq, &sg, num, 0, 1, data, ctx, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_add_inbuf_ctx);

/**
 * virtqueue_kick_prepare - first half of split virtqueue_kick call.
 * @_vq: the काष्ठा virtqueue
 *
 * Instead of virtqueue_kick(), you can करो:
 *	अगर (virtqueue_kick_prepare(vq))
 *		virtqueue_notअगरy(vq);
 *
 * This is someबार useful because the virtqueue_kick_prepare() needs
 * to be serialized, but the actual virtqueue_notअगरy() call करोes not.
 */
bool virtqueue_kick_prepare(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	वापस vq->packed_ring ? virtqueue_kick_prepare_packed(_vq) :
				 virtqueue_kick_prepare_split(_vq);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_kick_prepare);

/**
 * virtqueue_notअगरy - second half of split virtqueue_kick call.
 * @_vq: the काष्ठा virtqueue
 *
 * This करोes not need to be serialized.
 *
 * Returns false अगर host notअगरy failed or queue is broken, otherwise true.
 */
bool virtqueue_notअगरy(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	अगर (unlikely(vq->broken))
		वापस false;

	/* Prod other side to tell it about changes. */
	अगर (!vq->notअगरy(_vq)) अणु
		vq->broken = true;
		वापस false;
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_notअगरy);

/**
 * virtqueue_kick - update after add_buf
 * @vq: the काष्ठा virtqueue
 *
 * After one or more virtqueue_add_* calls, invoke this to kick
 * the other side.
 *
 * Caller must ensure we करोn't call this with other virtqueue
 * operations at the same समय (except where noted).
 *
 * Returns false अगर kick failed, otherwise true.
 */
bool virtqueue_kick(काष्ठा virtqueue *vq)
अणु
	अगर (virtqueue_kick_prepare(vq))
		वापस virtqueue_notअगरy(vq);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_kick);

/**
 * virtqueue_get_buf - get the next used buffer
 * @_vq: the काष्ठा virtqueue we're talking about.
 * @len: the length written पूर्णांकo the buffer
 * @ctx: extra context क्रम the token
 *
 * If the device wrote data पूर्णांकo the buffer, @len will be set to the
 * amount written.  This means you करोn't need to clear the buffer
 * beक्रमehand to ensure there's no data leakage in the हाल of लघु
 * ग_लिखोs.
 *
 * Caller must ensure we करोn't call this with other virtqueue
 * operations at the same समय (except where noted).
 *
 * Returns शून्य अगर there are no used buffers, or the "data" token
 * handed to virtqueue_add_*().
 */
व्योम *virtqueue_get_buf_ctx(काष्ठा virtqueue *_vq, अचिन्हित पूर्णांक *len,
			    व्योम **ctx)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	वापस vq->packed_ring ? virtqueue_get_buf_ctx_packed(_vq, len, ctx) :
				 virtqueue_get_buf_ctx_split(_vq, len, ctx);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_get_buf_ctx);

व्योम *virtqueue_get_buf(काष्ठा virtqueue *_vq, अचिन्हित पूर्णांक *len)
अणु
	वापस virtqueue_get_buf_ctx(_vq, len, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_get_buf);
/**
 * virtqueue_disable_cb - disable callbacks
 * @_vq: the काष्ठा virtqueue we're talking about.
 *
 * Note that this is not necessarily synchronous, hence unreliable and only
 * useful as an optimization.
 *
 * Unlike other operations, this need not be serialized.
 */
व्योम virtqueue_disable_cb(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	अगर (vq->packed_ring)
		virtqueue_disable_cb_packed(_vq);
	अन्यथा
		virtqueue_disable_cb_split(_vq);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_disable_cb);

/**
 * virtqueue_enable_cb_prepare - restart callbacks after disable_cb
 * @_vq: the काष्ठा virtqueue we're talking about.
 *
 * This re-enables callbacks; it वापसs current queue state
 * in an opaque अचिन्हित value. This value should be later tested by
 * virtqueue_poll, to detect a possible race between the driver checking क्रम
 * more work, and enabling callbacks.
 *
 * Caller must ensure we करोn't call this with other virtqueue
 * operations at the same समय (except where noted).
 */
अचिन्हित virtqueue_enable_cb_prepare(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	वापस vq->packed_ring ? virtqueue_enable_cb_prepare_packed(_vq) :
				 virtqueue_enable_cb_prepare_split(_vq);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_enable_cb_prepare);

/**
 * virtqueue_poll - query pending used buffers
 * @_vq: the काष्ठा virtqueue we're talking about.
 * @last_used_idx: virtqueue state (from call to virtqueue_enable_cb_prepare).
 *
 * Returns "true" अगर there are pending used buffers in the queue.
 *
 * This करोes not need to be serialized.
 */
bool virtqueue_poll(काष्ठा virtqueue *_vq, अचिन्हित last_used_idx)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	अगर (unlikely(vq->broken))
		वापस false;

	virtio_mb(vq->weak_barriers);
	वापस vq->packed_ring ? virtqueue_poll_packed(_vq, last_used_idx) :
				 virtqueue_poll_split(_vq, last_used_idx);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_poll);

/**
 * virtqueue_enable_cb - restart callbacks after disable_cb.
 * @_vq: the काष्ठा virtqueue we're talking about.
 *
 * This re-enables callbacks; it वापसs "false" अगर there are pending
 * buffers in the queue, to detect a possible race between the driver
 * checking क्रम more work, and enabling callbacks.
 *
 * Caller must ensure we करोn't call this with other virtqueue
 * operations at the same समय (except where noted).
 */
bool virtqueue_enable_cb(काष्ठा virtqueue *_vq)
अणु
	अचिन्हित last_used_idx = virtqueue_enable_cb_prepare(_vq);

	वापस !virtqueue_poll(_vq, last_used_idx);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_enable_cb);

/**
 * virtqueue_enable_cb_delayed - restart callbacks after disable_cb.
 * @_vq: the काष्ठा virtqueue we're talking about.
 *
 * This re-enables callbacks but hपूर्णांकs to the other side to delay
 * पूर्णांकerrupts until most of the available buffers have been processed;
 * it वापसs "false" अगर there are many pending buffers in the queue,
 * to detect a possible race between the driver checking क्रम more work,
 * and enabling callbacks.
 *
 * Caller must ensure we करोn't call this with other virtqueue
 * operations at the same समय (except where noted).
 */
bool virtqueue_enable_cb_delayed(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	वापस vq->packed_ring ? virtqueue_enable_cb_delayed_packed(_vq) :
				 virtqueue_enable_cb_delayed_split(_vq);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_enable_cb_delayed);

/**
 * virtqueue_detach_unused_buf - detach first unused buffer
 * @_vq: the काष्ठा virtqueue we're talking about.
 *
 * Returns शून्य or the "data" token handed to virtqueue_add_*().
 * This is not valid on an active queue; it is useful only क्रम device
 * shutकरोwn.
 */
व्योम *virtqueue_detach_unused_buf(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	वापस vq->packed_ring ? virtqueue_detach_unused_buf_packed(_vq) :
				 virtqueue_detach_unused_buf_split(_vq);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_detach_unused_buf);

अटल अंतरभूत bool more_used(स्थिर काष्ठा vring_virtqueue *vq)
अणु
	वापस vq->packed_ring ? more_used_packed(vq) : more_used_split(vq);
पूर्ण

irqवापस_t vring_पूर्णांकerrupt(पूर्णांक irq, व्योम *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	अगर (!more_used(vq)) अणु
		pr_debug("virtqueue interrupt with no work for %p\n", vq);
		वापस IRQ_NONE;
	पूर्ण

	अगर (unlikely(vq->broken))
		वापस IRQ_HANDLED;

	pr_debug("virtqueue callback for %p (%p)\n", vq, vq->vq.callback);
	अगर (vq->vq.callback)
		vq->vq.callback(&vq->vq);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(vring_पूर्णांकerrupt);

/* Only available क्रम split ring */
काष्ठा virtqueue *__vring_new_virtqueue(अचिन्हित पूर्णांक index,
					काष्ठा vring vring,
					काष्ठा virtio_device *vdev,
					bool weak_barriers,
					bool context,
					bool (*notअगरy)(काष्ठा virtqueue *),
					व्योम (*callback)(काष्ठा virtqueue *),
					स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा vring_virtqueue *vq;

	अगर (virtio_has_feature(vdev, VIRTIO_F_RING_PACKED))
		वापस शून्य;

	vq = kदो_स्मृति(माप(*vq), GFP_KERNEL);
	अगर (!vq)
		वापस शून्य;

	vq->packed_ring = false;
	vq->vq.callback = callback;
	vq->vq.vdev = vdev;
	vq->vq.name = name;
	vq->vq.num_मुक्त = vring.num;
	vq->vq.index = index;
	vq->we_own_ring = false;
	vq->notअगरy = notअगरy;
	vq->weak_barriers = weak_barriers;
	vq->broken = false;
	vq->last_used_idx = 0;
	vq->num_added = 0;
	vq->use_dma_api = vring_use_dma_api(vdev);
#अगर_घोषित DEBUG
	vq->in_use = false;
	vq->last_add_समय_valid = false;
#पूर्ण_अगर

	vq->indirect = virtio_has_feature(vdev, VIRTIO_RING_F_INसूचीECT_DESC) &&
		!context;
	vq->event = virtio_has_feature(vdev, VIRTIO_RING_F_EVENT_IDX);

	अगर (virtio_has_feature(vdev, VIRTIO_F_ORDER_PLATFORM))
		vq->weak_barriers = false;

	vq->split.queue_dma_addr = 0;
	vq->split.queue_size_in_bytes = 0;

	vq->split.vring = vring;
	vq->split.avail_flags_shaकरोw = 0;
	vq->split.avail_idx_shaकरोw = 0;

	/* No callback?  Tell other side not to bother us. */
	अगर (!callback) अणु
		vq->split.avail_flags_shaकरोw |= VRING_AVAIL_F_NO_INTERRUPT;
		अगर (!vq->event)
			vq->split.vring.avail->flags = cpu_to_virtio16(vdev,
					vq->split.avail_flags_shaकरोw);
	पूर्ण

	vq->split.desc_state = kदो_स्मृति_array(vring.num,
			माप(काष्ठा vring_desc_state_split), GFP_KERNEL);
	अगर (!vq->split.desc_state) अणु
		kमुक्त(vq);
		वापस शून्य;
	पूर्ण

	/* Put everything in मुक्त lists. */
	vq->मुक्त_head = 0;
	क्रम (i = 0; i < vring.num-1; i++)
		vq->split.vring.desc[i].next = cpu_to_virtio16(vdev, i + 1);
	स_रखो(vq->split.desc_state, 0, vring.num *
			माप(काष्ठा vring_desc_state_split));

	list_add_tail(&vq->vq.list, &vdev->vqs);
	वापस &vq->vq;
पूर्ण
EXPORT_SYMBOL_GPL(__vring_new_virtqueue);

काष्ठा virtqueue *vring_create_virtqueue(
	अचिन्हित पूर्णांक index,
	अचिन्हित पूर्णांक num,
	अचिन्हित पूर्णांक vring_align,
	काष्ठा virtio_device *vdev,
	bool weak_barriers,
	bool may_reduce_num,
	bool context,
	bool (*notअगरy)(काष्ठा virtqueue *),
	व्योम (*callback)(काष्ठा virtqueue *),
	स्थिर अक्षर *name)
अणु

	अगर (virtio_has_feature(vdev, VIRTIO_F_RING_PACKED))
		वापस vring_create_virtqueue_packed(index, num, vring_align,
				vdev, weak_barriers, may_reduce_num,
				context, notअगरy, callback, name);

	वापस vring_create_virtqueue_split(index, num, vring_align,
			vdev, weak_barriers, may_reduce_num,
			context, notअगरy, callback, name);
पूर्ण
EXPORT_SYMBOL_GPL(vring_create_virtqueue);

/* Only available क्रम split ring */
काष्ठा virtqueue *vring_new_virtqueue(अचिन्हित पूर्णांक index,
				      अचिन्हित पूर्णांक num,
				      अचिन्हित पूर्णांक vring_align,
				      काष्ठा virtio_device *vdev,
				      bool weak_barriers,
				      bool context,
				      व्योम *pages,
				      bool (*notअगरy)(काष्ठा virtqueue *vq),
				      व्योम (*callback)(काष्ठा virtqueue *vq),
				      स्थिर अक्षर *name)
अणु
	काष्ठा vring vring;

	अगर (virtio_has_feature(vdev, VIRTIO_F_RING_PACKED))
		वापस शून्य;

	vring_init(&vring, num, pages, vring_align);
	वापस __vring_new_virtqueue(index, vring, vdev, weak_barriers, context,
				     notअगरy, callback, name);
पूर्ण
EXPORT_SYMBOL_GPL(vring_new_virtqueue);

व्योम vring_del_virtqueue(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	अगर (vq->we_own_ring) अणु
		अगर (vq->packed_ring) अणु
			vring_मुक्त_queue(vq->vq.vdev,
					 vq->packed.ring_size_in_bytes,
					 vq->packed.vring.desc,
					 vq->packed.ring_dma_addr);

			vring_मुक्त_queue(vq->vq.vdev,
					 vq->packed.event_size_in_bytes,
					 vq->packed.vring.driver,
					 vq->packed.driver_event_dma_addr);

			vring_मुक्त_queue(vq->vq.vdev,
					 vq->packed.event_size_in_bytes,
					 vq->packed.vring.device,
					 vq->packed.device_event_dma_addr);

			kमुक्त(vq->packed.desc_state);
			kमुक्त(vq->packed.desc_extra);
		पूर्ण अन्यथा अणु
			vring_मुक्त_queue(vq->vq.vdev,
					 vq->split.queue_size_in_bytes,
					 vq->split.vring.desc,
					 vq->split.queue_dma_addr);
		पूर्ण
	पूर्ण
	अगर (!vq->packed_ring)
		kमुक्त(vq->split.desc_state);
	list_del(&_vq->list);
	kमुक्त(vq);
पूर्ण
EXPORT_SYMBOL_GPL(vring_del_virtqueue);

/* Manipulates transport-specअगरic feature bits. */
व्योम vring_transport_features(काष्ठा virtio_device *vdev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = VIRTIO_TRANSPORT_F_START; i < VIRTIO_TRANSPORT_F_END; i++) अणु
		चयन (i) अणु
		हाल VIRTIO_RING_F_INसूचीECT_DESC:
			अवरोध;
		हाल VIRTIO_RING_F_EVENT_IDX:
			अवरोध;
		हाल VIRTIO_F_VERSION_1:
			अवरोध;
		हाल VIRTIO_F_ACCESS_PLATFORM:
			अवरोध;
		हाल VIRTIO_F_RING_PACKED:
			अवरोध;
		हाल VIRTIO_F_ORDER_PLATFORM:
			अवरोध;
		शेष:
			/* We करोn't understand this bit. */
			__virtio_clear_bit(vdev, i);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vring_transport_features);

/**
 * virtqueue_get_vring_size - वापस the size of the virtqueue's vring
 * @_vq: the काष्ठा virtqueue containing the vring of पूर्णांकerest.
 *
 * Returns the size of the vring.  This is मुख्यly used क्रम boasting to
 * userspace.  Unlike other operations, this need not be serialized.
 */
अचिन्हित पूर्णांक virtqueue_get_vring_size(काष्ठा virtqueue *_vq)
अणु

	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	वापस vq->packed_ring ? vq->packed.vring.num : vq->split.vring.num;
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_get_vring_size);

bool virtqueue_is_broken(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	वापस vq->broken;
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_is_broken);

/*
 * This should prevent the device from being used, allowing drivers to
 * recover.  You may need to grab appropriate locks to flush.
 */
व्योम virtio_अवरोध_device(काष्ठा virtio_device *dev)
अणु
	काष्ठा virtqueue *_vq;

	list_क्रम_each_entry(_vq, &dev->vqs, list) अणु
		काष्ठा vring_virtqueue *vq = to_vvq(_vq);
		vq->broken = true;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(virtio_अवरोध_device);

dma_addr_t virtqueue_get_desc_addr(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	BUG_ON(!vq->we_own_ring);

	अगर (vq->packed_ring)
		वापस vq->packed.ring_dma_addr;

	वापस vq->split.queue_dma_addr;
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_get_desc_addr);

dma_addr_t virtqueue_get_avail_addr(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	BUG_ON(!vq->we_own_ring);

	अगर (vq->packed_ring)
		वापस vq->packed.driver_event_dma_addr;

	वापस vq->split.queue_dma_addr +
		((अक्षर *)vq->split.vring.avail - (अक्षर *)vq->split.vring.desc);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_get_avail_addr);

dma_addr_t virtqueue_get_used_addr(काष्ठा virtqueue *_vq)
अणु
	काष्ठा vring_virtqueue *vq = to_vvq(_vq);

	BUG_ON(!vq->we_own_ring);

	अगर (vq->packed_ring)
		वापस vq->packed.device_event_dma_addr;

	वापस vq->split.queue_dma_addr +
		((अक्षर *)vq->split.vring.used - (अक्षर *)vq->split.vring.desc);
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_get_used_addr);

/* Only available क्रम split ring */
स्थिर काष्ठा vring *virtqueue_get_vring(काष्ठा virtqueue *vq)
अणु
	वापस &to_vvq(vq)->split.vring;
पूर्ण
EXPORT_SYMBOL_GPL(virtqueue_get_vring);

MODULE_LICENSE("GPL");
