<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Virtio driver क्रम the paraभवized IOMMU
 *
 * Copyright (C) 2019 Arm Limited
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/amba/bus.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/पूर्णांकerval_tree.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/रुको.h>

#समावेश <uapi/linux/virtio_iommu.h>

#घोषणा MSI_IOVA_BASE			0x8000000
#घोषणा MSI_IOVA_LENGTH			0x100000

#घोषणा VIOMMU_REQUEST_VQ		0
#घोषणा VIOMMU_EVENT_VQ			1
#घोषणा VIOMMU_NR_VQS			2

काष्ठा viommu_dev अणु
	काष्ठा iommu_device		iommu;
	काष्ठा device			*dev;
	काष्ठा virtio_device		*vdev;

	काष्ठा ida			करोमुख्य_ids;

	काष्ठा virtqueue		*vqs[VIOMMU_NR_VQS];
	spinlock_t			request_lock;
	काष्ठा list_head		requests;
	व्योम				*evts;

	/* Device configuration */
	काष्ठा iommu_करोमुख्य_geometry	geometry;
	u64				pgsize_biपंचांगap;
	u32				first_करोमुख्य;
	u32				last_करोमुख्य;
	/* Supported MAP flags */
	u32				map_flags;
	u32				probe_size;
पूर्ण;

काष्ठा viommu_mapping अणु
	phys_addr_t			paddr;
	काष्ठा पूर्णांकerval_tree_node	iova;
	u32				flags;
पूर्ण;

काष्ठा viommu_करोमुख्य अणु
	काष्ठा iommu_करोमुख्य		करोमुख्य;
	काष्ठा viommu_dev		*viommu;
	काष्ठा mutex			mutex; /* protects viommu poपूर्णांकer */
	अचिन्हित पूर्णांक			id;
	u32				map_flags;

	spinlock_t			mappings_lock;
	काष्ठा rb_root_cached		mappings;

	अचिन्हित दीर्घ			nr_endpoपूर्णांकs;
पूर्ण;

काष्ठा viommu_endpoपूर्णांक अणु
	काष्ठा device			*dev;
	काष्ठा viommu_dev		*viommu;
	काष्ठा viommu_करोमुख्य		*vकरोमुख्य;
	काष्ठा list_head		resv_regions;
पूर्ण;

काष्ठा viommu_request अणु
	काष्ठा list_head		list;
	व्योम				*ग_लिखोback;
	अचिन्हित पूर्णांक			ग_लिखो_offset;
	अचिन्हित पूर्णांक			len;
	अक्षर				buf[];
पूर्ण;

#घोषणा VIOMMU_FAULT_RESV_MASK		0xffffff00

काष्ठा viommu_event अणु
	जोड़ अणु
		u32			head;
		काष्ठा virtio_iommu_fault fault;
	पूर्ण;
पूर्ण;

#घोषणा to_viommu_करोमुख्य(करोमुख्य)	\
	container_of(करोमुख्य, काष्ठा viommu_करोमुख्य, करोमुख्य)

अटल पूर्णांक viommu_get_req_त्रुटि_सं(व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा virtio_iommu_req_tail *tail = buf + len - माप(*tail);

	चयन (tail->status) अणु
	हाल VIRTIO_IOMMU_S_OK:
		वापस 0;
	हाल VIRTIO_IOMMU_S_UNSUPP:
		वापस -ENOSYS;
	हाल VIRTIO_IOMMU_S_INVAL:
		वापस -EINVAL;
	हाल VIRTIO_IOMMU_S_RANGE:
		वापस -दुस्फल;
	हाल VIRTIO_IOMMU_S_NOENT:
		वापस -ENOENT;
	हाल VIRTIO_IOMMU_S_FAULT:
		वापस -EFAULT;
	हाल VIRTIO_IOMMU_S_NOMEM:
		वापस -ENOMEM;
	हाल VIRTIO_IOMMU_S_IOERR:
	हाल VIRTIO_IOMMU_S_DEVERR:
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल व्योम viommu_set_req_status(व्योम *buf, माप_प्रकार len, पूर्णांक status)
अणु
	काष्ठा virtio_iommu_req_tail *tail = buf + len - माप(*tail);

	tail->status = status;
पूर्ण

अटल off_t viommu_get_ग_लिखो_desc_offset(काष्ठा viommu_dev *viommu,
					  काष्ठा virtio_iommu_req_head *req,
					  माप_प्रकार len)
अणु
	माप_प्रकार tail_size = माप(काष्ठा virtio_iommu_req_tail);

	अगर (req->type == VIRTIO_IOMMU_T_PROBE)
		वापस len - viommu->probe_size - tail_size;

	वापस len - tail_size;
पूर्ण

/*
 * __viommu_sync_req - Complete all in-flight requests
 *
 * Wait क्रम all added requests to complete. When this function वापसs, all
 * requests that were in-flight at the समय of the call have completed.
 */
अटल पूर्णांक __viommu_sync_req(काष्ठा viommu_dev *viommu)
अणु
	अचिन्हित पूर्णांक len;
	माप_प्रकार ग_लिखो_len;
	काष्ठा viommu_request *req;
	काष्ठा virtqueue *vq = viommu->vqs[VIOMMU_REQUEST_VQ];

	निश्चित_spin_locked(&viommu->request_lock);

	virtqueue_kick(vq);

	जबतक (!list_empty(&viommu->requests)) अणु
		len = 0;
		req = virtqueue_get_buf(vq, &len);
		अगर (!req)
			जारी;

		अगर (!len)
			viommu_set_req_status(req->buf, req->len,
					      VIRTIO_IOMMU_S_IOERR);

		ग_लिखो_len = req->len - req->ग_लिखो_offset;
		अगर (req->ग_लिखोback && len == ग_लिखो_len)
			स_नकल(req->ग_लिखोback, req->buf + req->ग_लिखो_offset,
			       ग_लिखो_len);

		list_del(&req->list);
		kमुक्त(req);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक viommu_sync_req(काष्ठा viommu_dev *viommu)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&viommu->request_lock, flags);
	ret = __viommu_sync_req(viommu);
	अगर (ret)
		dev_dbg(viommu->dev, "could not sync requests (%d)\n", ret);
	spin_unlock_irqrestore(&viommu->request_lock, flags);

	वापस ret;
पूर्ण

/*
 * __viommu_add_request - Add one request to the queue
 * @buf: poपूर्णांकer to the request buffer
 * @len: length of the request buffer
 * @ग_लिखोback: copy data back to the buffer when the request completes.
 *
 * Add a request to the queue. Only synchronize the queue अगर it's alपढ़ोy full.
 * Otherwise करोn't kick the queue nor रुको क्रम requests to complete.
 *
 * When @ग_लिखोback is true, data written by the device, including the request
 * status, is copied पूर्णांकo @buf after the request completes. This is unsafe अगर
 * the caller allocates @buf on stack and drops the lock between add_req() and
 * sync_req().
 *
 * Return 0 अगर the request was successfully added to the queue.
 */
अटल पूर्णांक __viommu_add_req(काष्ठा viommu_dev *viommu, व्योम *buf, माप_प्रकार len,
			    bool ग_लिखोback)
अणु
	पूर्णांक ret;
	off_t ग_लिखो_offset;
	काष्ठा viommu_request *req;
	काष्ठा scatterlist top_sg, bottom_sg;
	काष्ठा scatterlist *sg[2] = अणु &top_sg, &bottom_sg पूर्ण;
	काष्ठा virtqueue *vq = viommu->vqs[VIOMMU_REQUEST_VQ];

	निश्चित_spin_locked(&viommu->request_lock);

	ग_लिखो_offset = viommu_get_ग_लिखो_desc_offset(viommu, buf, len);
	अगर (ग_लिखो_offset <= 0)
		वापस -EINVAL;

	req = kzalloc(माप(*req) + len, GFP_ATOMIC);
	अगर (!req)
		वापस -ENOMEM;

	req->len = len;
	अगर (ग_लिखोback) अणु
		req->ग_लिखोback = buf + ग_लिखो_offset;
		req->ग_लिखो_offset = ग_लिखो_offset;
	पूर्ण
	स_नकल(&req->buf, buf, ग_लिखो_offset);

	sg_init_one(&top_sg, req->buf, ग_लिखो_offset);
	sg_init_one(&bottom_sg, req->buf + ग_लिखो_offset, len - ग_लिखो_offset);

	ret = virtqueue_add_sgs(vq, sg, 1, 1, req, GFP_ATOMIC);
	अगर (ret == -ENOSPC) अणु
		/* If the queue is full, sync and retry */
		अगर (!__viommu_sync_req(viommu))
			ret = virtqueue_add_sgs(vq, sg, 1, 1, req, GFP_ATOMIC);
	पूर्ण
	अगर (ret)
		जाओ err_मुक्त;

	list_add_tail(&req->list, &viommu->requests);
	वापस 0;

err_मुक्त:
	kमुक्त(req);
	वापस ret;
पूर्ण

अटल पूर्णांक viommu_add_req(काष्ठा viommu_dev *viommu, व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&viommu->request_lock, flags);
	ret = __viommu_add_req(viommu, buf, len, false);
	अगर (ret)
		dev_dbg(viommu->dev, "could not add request: %d\n", ret);
	spin_unlock_irqrestore(&viommu->request_lock, flags);

	वापस ret;
पूर्ण

/*
 * Send a request and रुको क्रम it to complete. Return the request status (as an
 * त्रुटि_सं)
 */
अटल पूर्णांक viommu_send_req_sync(काष्ठा viommu_dev *viommu, व्योम *buf,
				माप_प्रकार len)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&viommu->request_lock, flags);

	ret = __viommu_add_req(viommu, buf, len, true);
	अगर (ret) अणु
		dev_dbg(viommu->dev, "could not add request (%d)\n", ret);
		जाओ out_unlock;
	पूर्ण

	ret = __viommu_sync_req(viommu);
	अगर (ret) अणु
		dev_dbg(viommu->dev, "could not sync requests (%d)\n", ret);
		/* Fall-through (get the actual request status) */
	पूर्ण

	ret = viommu_get_req_त्रुटि_सं(buf, len);
out_unlock:
	spin_unlock_irqrestore(&viommu->request_lock, flags);
	वापस ret;
पूर्ण

/*
 * viommu_add_mapping - add a mapping to the पूर्णांकernal tree
 *
 * On success, वापस the new mapping. Otherwise वापस शून्य.
 */
अटल पूर्णांक viommu_add_mapping(काष्ठा viommu_करोमुख्य *vकरोमुख्य, अचिन्हित दीर्घ iova,
			      phys_addr_t paddr, माप_प्रकार size, u32 flags)
अणु
	अचिन्हित दीर्घ irqflags;
	काष्ठा viommu_mapping *mapping;

	mapping = kzalloc(माप(*mapping), GFP_ATOMIC);
	अगर (!mapping)
		वापस -ENOMEM;

	mapping->paddr		= paddr;
	mapping->iova.start	= iova;
	mapping->iova.last	= iova + size - 1;
	mapping->flags		= flags;

	spin_lock_irqsave(&vकरोमुख्य->mappings_lock, irqflags);
	पूर्णांकerval_tree_insert(&mapping->iova, &vकरोमुख्य->mappings);
	spin_unlock_irqrestore(&vकरोमुख्य->mappings_lock, irqflags);

	वापस 0;
पूर्ण

/*
 * viommu_del_mappings - हटाओ mappings from the पूर्णांकernal tree
 *
 * @vकरोमुख्य: the करोमुख्य
 * @iova: start of the range
 * @size: size of the range. A size of 0 corresponds to the entire address
 *	space.
 *
 * On success, वापसs the number of unmapped bytes (>= size)
 */
अटल माप_प्रकार viommu_del_mappings(काष्ठा viommu_करोमुख्य *vकरोमुख्य,
				  अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
	माप_प्रकार unmapped = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ last = iova + size - 1;
	काष्ठा viommu_mapping *mapping = शून्य;
	काष्ठा पूर्णांकerval_tree_node *node, *next;

	spin_lock_irqsave(&vकरोमुख्य->mappings_lock, flags);
	next = पूर्णांकerval_tree_iter_first(&vकरोमुख्य->mappings, iova, last);
	जबतक (next) अणु
		node = next;
		mapping = container_of(node, काष्ठा viommu_mapping, iova);
		next = पूर्णांकerval_tree_iter_next(node, iova, last);

		/* Trying to split a mapping? */
		अगर (mapping->iova.start < iova)
			अवरोध;

		/*
		 * Virtio-iommu करोesn't allow UNMAP to split a mapping created
		 * with a single MAP request, so हटाओ the full mapping.
		 */
		unmapped += mapping->iova.last - mapping->iova.start + 1;

		पूर्णांकerval_tree_हटाओ(node, &vकरोमुख्य->mappings);
		kमुक्त(mapping);
	पूर्ण
	spin_unlock_irqrestore(&vकरोमुख्य->mappings_lock, flags);

	वापस unmapped;
पूर्ण

/*
 * viommu_replay_mappings - re-send MAP requests
 *
 * When reattaching a करोमुख्य that was previously detached from all endpoपूर्णांकs,
 * mappings were deleted from the device. Re-create the mappings available in
 * the पूर्णांकernal tree.
 */
अटल पूर्णांक viommu_replay_mappings(काष्ठा viommu_करोमुख्य *vकरोमुख्य)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा viommu_mapping *mapping;
	काष्ठा पूर्णांकerval_tree_node *node;
	काष्ठा virtio_iommu_req_map map;

	spin_lock_irqsave(&vकरोमुख्य->mappings_lock, flags);
	node = पूर्णांकerval_tree_iter_first(&vकरोमुख्य->mappings, 0, -1UL);
	जबतक (node) अणु
		mapping = container_of(node, काष्ठा viommu_mapping, iova);
		map = (काष्ठा virtio_iommu_req_map) अणु
			.head.type	= VIRTIO_IOMMU_T_MAP,
			.करोमुख्य		= cpu_to_le32(vकरोमुख्य->id),
			.virt_start	= cpu_to_le64(mapping->iova.start),
			.virt_end	= cpu_to_le64(mapping->iova.last),
			.phys_start	= cpu_to_le64(mapping->paddr),
			.flags		= cpu_to_le32(mapping->flags),
		पूर्ण;

		ret = viommu_send_req_sync(vकरोमुख्य->viommu, &map, माप(map));
		अगर (ret)
			अवरोध;

		node = पूर्णांकerval_tree_iter_next(node, 0, -1UL);
	पूर्ण
	spin_unlock_irqrestore(&vकरोमुख्य->mappings_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक viommu_add_resv_mem(काष्ठा viommu_endpoपूर्णांक *vdev,
			       काष्ठा virtio_iommu_probe_resv_mem *mem,
			       माप_प्रकार len)
अणु
	माप_प्रकार size;
	u64 start64, end64;
	phys_addr_t start, end;
	काष्ठा iommu_resv_region *region = शून्य;
	अचिन्हित दीर्घ prot = IOMMU_WRITE | IOMMU_NOEXEC | IOMMU_MMIO;

	start = start64 = le64_to_cpu(mem->start);
	end = end64 = le64_to_cpu(mem->end);
	size = end64 - start64 + 1;

	/* Catch any overflow, including the unlikely end64 - start64 + 1 = 0 */
	अगर (start != start64 || end != end64 || size < end64 - start64)
		वापस -EOVERFLOW;

	अगर (len < माप(*mem))
		वापस -EINVAL;

	चयन (mem->subtype) अणु
	शेष:
		dev_warn(vdev->dev, "unknown resv mem subtype 0x%x\n",
			 mem->subtype);
		fallthrough;
	हाल VIRTIO_IOMMU_RESV_MEM_T_RESERVED:
		region = iommu_alloc_resv_region(start, size, 0,
						 IOMMU_RESV_RESERVED);
		अवरोध;
	हाल VIRTIO_IOMMU_RESV_MEM_T_MSI:
		region = iommu_alloc_resv_region(start, size, prot,
						 IOMMU_RESV_MSI);
		अवरोध;
	पूर्ण
	अगर (!region)
		वापस -ENOMEM;

	list_add(&region->list, &vdev->resv_regions);
	वापस 0;
पूर्ण

अटल पूर्णांक viommu_probe_endpoपूर्णांक(काष्ठा viommu_dev *viommu, काष्ठा device *dev)
अणु
	पूर्णांक ret;
	u16 type, len;
	माप_प्रकार cur = 0;
	माप_प्रकार probe_len;
	काष्ठा virtio_iommu_req_probe *probe;
	काष्ठा virtio_iommu_probe_property *prop;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा viommu_endpoपूर्णांक *vdev = dev_iommu_priv_get(dev);

	अगर (!fwspec->num_ids)
		वापस -EINVAL;

	probe_len = माप(*probe) + viommu->probe_size +
		    माप(काष्ठा virtio_iommu_req_tail);
	probe = kzalloc(probe_len, GFP_KERNEL);
	अगर (!probe)
		वापस -ENOMEM;

	probe->head.type = VIRTIO_IOMMU_T_PROBE;
	/*
	 * For now, assume that properties of an endpoपूर्णांक that outमाला_दो multiple
	 * IDs are consistent. Only probe the first one.
	 */
	probe->endpoपूर्णांक = cpu_to_le32(fwspec->ids[0]);

	ret = viommu_send_req_sync(viommu, probe, probe_len);
	अगर (ret)
		जाओ out_मुक्त;

	prop = (व्योम *)probe->properties;
	type = le16_to_cpu(prop->type) & VIRTIO_IOMMU_PROBE_T_MASK;

	जबतक (type != VIRTIO_IOMMU_PROBE_T_NONE &&
	       cur < viommu->probe_size) अणु
		len = le16_to_cpu(prop->length) + माप(*prop);

		चयन (type) अणु
		हाल VIRTIO_IOMMU_PROBE_T_RESV_MEM:
			ret = viommu_add_resv_mem(vdev, (व्योम *)prop, len);
			अवरोध;
		शेष:
			dev_err(dev, "unknown viommu prop 0x%x\n", type);
		पूर्ण

		अगर (ret)
			dev_err(dev, "failed to parse viommu prop 0x%x\n", type);

		cur += len;
		अगर (cur >= viommu->probe_size)
			अवरोध;

		prop = (व्योम *)probe->properties + cur;
		type = le16_to_cpu(prop->type) & VIRTIO_IOMMU_PROBE_T_MASK;
	पूर्ण

out_मुक्त:
	kमुक्त(probe);
	वापस ret;
पूर्ण

अटल पूर्णांक viommu_fault_handler(काष्ठा viommu_dev *viommu,
				काष्ठा virtio_iommu_fault *fault)
अणु
	अक्षर *reason_str;

	u8 reason	= fault->reason;
	u32 flags	= le32_to_cpu(fault->flags);
	u32 endpoपूर्णांक	= le32_to_cpu(fault->endpoपूर्णांक);
	u64 address	= le64_to_cpu(fault->address);

	चयन (reason) अणु
	हाल VIRTIO_IOMMU_FAULT_R_DOMAIN:
		reason_str = "domain";
		अवरोध;
	हाल VIRTIO_IOMMU_FAULT_R_MAPPING:
		reason_str = "page";
		अवरोध;
	हाल VIRTIO_IOMMU_FAULT_R_UNKNOWN:
	शेष:
		reason_str = "unknown";
		अवरोध;
	पूर्ण

	/* TODO: find EP by ID and report_iommu_fault */
	अगर (flags & VIRTIO_IOMMU_FAULT_F_ADDRESS)
		dev_err_ratelimited(viommu->dev, "%s fault from EP %u at %#llx [%s%s%s]\n",
				    reason_str, endpoपूर्णांक, address,
				    flags & VIRTIO_IOMMU_FAULT_F_READ ? "R" : "",
				    flags & VIRTIO_IOMMU_FAULT_F_WRITE ? "W" : "",
				    flags & VIRTIO_IOMMU_FAULT_F_EXEC ? "X" : "");
	अन्यथा
		dev_err_ratelimited(viommu->dev, "%s fault from EP %u\n",
				    reason_str, endpoपूर्णांक);
	वापस 0;
पूर्ण

अटल व्योम viommu_event_handler(काष्ठा virtqueue *vq)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक len;
	काष्ठा scatterlist sg[1];
	काष्ठा viommu_event *evt;
	काष्ठा viommu_dev *viommu = vq->vdev->priv;

	जबतक ((evt = virtqueue_get_buf(vq, &len)) != शून्य) अणु
		अगर (len > माप(*evt)) अणु
			dev_err(viommu->dev,
				"invalid event buffer (len %u != %zu)\n",
				len, माप(*evt));
		पूर्ण अन्यथा अगर (!(evt->head & VIOMMU_FAULT_RESV_MASK)) अणु
			viommu_fault_handler(viommu, &evt->fault);
		पूर्ण

		sg_init_one(sg, evt, माप(*evt));
		ret = virtqueue_add_inbuf(vq, sg, 1, evt, GFP_ATOMIC);
		अगर (ret)
			dev_err(viommu->dev, "could not add event buffer\n");
	पूर्ण

	virtqueue_kick(vq);
पूर्ण

/* IOMMU API */

अटल काष्ठा iommu_करोमुख्य *viommu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा viommu_करोमुख्य *vकरोमुख्य;

	अगर (type != IOMMU_DOMAIN_UNMANAGED && type != IOMMU_DOMAIN_DMA)
		वापस शून्य;

	vकरोमुख्य = kzalloc(माप(*vकरोमुख्य), GFP_KERNEL);
	अगर (!vकरोमुख्य)
		वापस शून्य;

	mutex_init(&vकरोमुख्य->mutex);
	spin_lock_init(&vकरोमुख्य->mappings_lock);
	vकरोमुख्य->mappings = RB_ROOT_CACHED;

	अगर (type == IOMMU_DOMAIN_DMA &&
	    iommu_get_dma_cookie(&vकरोमुख्य->करोमुख्य)) अणु
		kमुक्त(vकरोमुख्य);
		वापस शून्य;
	पूर्ण

	वापस &vकरोमुख्य->करोमुख्य;
पूर्ण

अटल पूर्णांक viommu_करोमुख्य_finalise(काष्ठा viommu_endpoपूर्णांक *vdev,
				  काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ viommu_page_size;
	काष्ठा viommu_dev *viommu = vdev->viommu;
	काष्ठा viommu_करोमुख्य *vकरोमुख्य = to_viommu_करोमुख्य(करोमुख्य);

	viommu_page_size = 1UL << __ffs(viommu->pgsize_biपंचांगap);
	अगर (viommu_page_size > PAGE_SIZE) अणु
		dev_err(vdev->dev,
			"granule 0x%lx larger than system page size 0x%lx\n",
			viommu_page_size, PAGE_SIZE);
		वापस -EINVAL;
	पूर्ण

	ret = ida_alloc_range(&viommu->करोमुख्य_ids, viommu->first_करोमुख्य,
			      viommu->last_करोमुख्य, GFP_KERNEL);
	अगर (ret < 0)
		वापस ret;

	vकरोमुख्य->id		= (अचिन्हित पूर्णांक)ret;

	करोमुख्य->pgsize_biपंचांगap	= viommu->pgsize_biपंचांगap;
	करोमुख्य->geometry	= viommu->geometry;

	vकरोमुख्य->map_flags	= viommu->map_flags;
	vकरोमुख्य->viommu		= viommu;

	वापस 0;
पूर्ण

अटल व्योम viommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा viommu_करोमुख्य *vकरोमुख्य = to_viommu_करोमुख्य(करोमुख्य);

	iommu_put_dma_cookie(करोमुख्य);

	/* Free all reमुख्यing mappings (size 2^64) */
	viommu_del_mappings(vकरोमुख्य, 0, 0);

	अगर (vकरोमुख्य->viommu)
		ida_मुक्त(&vकरोमुख्य->viommu->करोमुख्य_ids, vकरोमुख्य->id);

	kमुक्त(vकरोमुख्य);
पूर्ण

अटल पूर्णांक viommu_attach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा virtio_iommu_req_attach req;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा viommu_endpoपूर्णांक *vdev = dev_iommu_priv_get(dev);
	काष्ठा viommu_करोमुख्य *vकरोमुख्य = to_viommu_करोमुख्य(करोमुख्य);

	mutex_lock(&vकरोमुख्य->mutex);
	अगर (!vकरोमुख्य->viommu) अणु
		/*
		 * Properly initialize the करोमुख्य now that we know which viommu
		 * owns it.
		 */
		ret = viommu_करोमुख्य_finalise(vdev, करोमुख्य);
	पूर्ण अन्यथा अगर (vकरोमुख्य->viommu != vdev->viommu) अणु
		dev_err(dev, "cannot attach to foreign vIOMMU\n");
		ret = -EXDEV;
	पूर्ण
	mutex_unlock(&vकरोमुख्य->mutex);

	अगर (ret)
		वापस ret;

	/*
	 * In the virtio-iommu device, when attaching the endpoपूर्णांक to a new
	 * करोमुख्य, it is detached from the old one and, अगर as as a result the
	 * old करोमुख्य isn't attached to any endpoपूर्णांक, all mappings are हटाओd
	 * from the old करोमुख्य and it is मुक्तd.
	 *
	 * In the driver the old करोमुख्य still exists, and its mappings will be
	 * recreated अगर it माला_लो reattached to an endpoपूर्णांक. Otherwise it will be
	 * मुक्तd explicitly.
	 *
	 * vdev->vकरोमुख्य is रक्षित by group->mutex
	 */
	अगर (vdev->vकरोमुख्य)
		vdev->vकरोमुख्य->nr_endpoपूर्णांकs--;

	req = (काष्ठा virtio_iommu_req_attach) अणु
		.head.type	= VIRTIO_IOMMU_T_ATTACH,
		.करोमुख्य		= cpu_to_le32(vकरोमुख्य->id),
	पूर्ण;

	क्रम (i = 0; i < fwspec->num_ids; i++) अणु
		req.endpoपूर्णांक = cpu_to_le32(fwspec->ids[i]);

		ret = viommu_send_req_sync(vकरोमुख्य->viommu, &req, माप(req));
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!vकरोमुख्य->nr_endpoपूर्णांकs) अणु
		/*
		 * This endpoपूर्णांक is the first to be attached to the करोमुख्य.
		 * Replay existing mappings (e.g. SW MSI).
		 */
		ret = viommu_replay_mappings(vकरोमुख्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	vकरोमुख्य->nr_endpoपूर्णांकs++;
	vdev->vकरोमुख्य = vकरोमुख्य;

	वापस 0;
पूर्ण

अटल पूर्णांक viommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
		      phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	पूर्णांक ret;
	u32 flags;
	काष्ठा virtio_iommu_req_map map;
	काष्ठा viommu_करोमुख्य *vकरोमुख्य = to_viommu_करोमुख्य(करोमुख्य);

	flags = (prot & IOMMU_READ ? VIRTIO_IOMMU_MAP_F_READ : 0) |
		(prot & IOMMU_WRITE ? VIRTIO_IOMMU_MAP_F_WRITE : 0) |
		(prot & IOMMU_MMIO ? VIRTIO_IOMMU_MAP_F_MMIO : 0);

	अगर (flags & ~vकरोमुख्य->map_flags)
		वापस -EINVAL;

	ret = viommu_add_mapping(vकरोमुख्य, iova, paddr, size, flags);
	अगर (ret)
		वापस ret;

	map = (काष्ठा virtio_iommu_req_map) अणु
		.head.type	= VIRTIO_IOMMU_T_MAP,
		.करोमुख्य		= cpu_to_le32(vकरोमुख्य->id),
		.virt_start	= cpu_to_le64(iova),
		.phys_start	= cpu_to_le64(paddr),
		.virt_end	= cpu_to_le64(iova + size - 1),
		.flags		= cpu_to_le32(flags),
	पूर्ण;

	अगर (!vकरोमुख्य->nr_endpoपूर्णांकs)
		वापस 0;

	ret = viommu_send_req_sync(vकरोमुख्य->viommu, &map, माप(map));
	अगर (ret)
		viommu_del_mappings(vकरोमुख्य, iova, size);

	वापस ret;
पूर्ण

अटल माप_प्रकार viommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			   माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather)
अणु
	पूर्णांक ret = 0;
	माप_प्रकार unmapped;
	काष्ठा virtio_iommu_req_unmap unmap;
	काष्ठा viommu_करोमुख्य *vकरोमुख्य = to_viommu_करोमुख्य(करोमुख्य);

	unmapped = viommu_del_mappings(vकरोमुख्य, iova, size);
	अगर (unmapped < size)
		वापस 0;

	/* Device alपढ़ोy हटाओd all mappings after detach. */
	अगर (!vकरोमुख्य->nr_endpoपूर्णांकs)
		वापस unmapped;

	unmap = (काष्ठा virtio_iommu_req_unmap) अणु
		.head.type	= VIRTIO_IOMMU_T_UNMAP,
		.करोमुख्य		= cpu_to_le32(vकरोमुख्य->id),
		.virt_start	= cpu_to_le64(iova),
		.virt_end	= cpu_to_le64(iova + unmapped - 1),
	पूर्ण;

	ret = viommu_add_req(vकरोमुख्य->viommu, &unmap, माप(unmap));
	वापस ret ? 0 : unmapped;
पूर्ण

अटल phys_addr_t viommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
				       dma_addr_t iova)
अणु
	u64 paddr = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा viommu_mapping *mapping;
	काष्ठा पूर्णांकerval_tree_node *node;
	काष्ठा viommu_करोमुख्य *vकरोमुख्य = to_viommu_करोमुख्य(करोमुख्य);

	spin_lock_irqsave(&vकरोमुख्य->mappings_lock, flags);
	node = पूर्णांकerval_tree_iter_first(&vकरोमुख्य->mappings, iova, iova);
	अगर (node) अणु
		mapping = container_of(node, काष्ठा viommu_mapping, iova);
		paddr = mapping->paddr + (iova - mapping->iova.start);
	पूर्ण
	spin_unlock_irqrestore(&vकरोमुख्य->mappings_lock, flags);

	वापस paddr;
पूर्ण

अटल व्योम viommu_iotlb_sync(काष्ठा iommu_करोमुख्य *करोमुख्य,
			      काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा viommu_करोमुख्य *vकरोमुख्य = to_viommu_करोमुख्य(करोमुख्य);

	viommu_sync_req(vकरोमुख्य->viommu);
पूर्ण

अटल व्योम viommu_get_resv_regions(काष्ठा device *dev, काष्ठा list_head *head)
अणु
	काष्ठा iommu_resv_region *entry, *new_entry, *msi = शून्य;
	काष्ठा viommu_endpoपूर्णांक *vdev = dev_iommu_priv_get(dev);
	पूर्णांक prot = IOMMU_WRITE | IOMMU_NOEXEC | IOMMU_MMIO;

	list_क्रम_each_entry(entry, &vdev->resv_regions, list) अणु
		अगर (entry->type == IOMMU_RESV_MSI)
			msi = entry;

		new_entry = kmemdup(entry, माप(*entry), GFP_KERNEL);
		अगर (!new_entry)
			वापस;
		list_add_tail(&new_entry->list, head);
	पूर्ण

	/*
	 * If the device didn't रेजिस्टर any bypass MSI winकरोw, add a
	 * software-mapped region.
	 */
	अगर (!msi) अणु
		msi = iommu_alloc_resv_region(MSI_IOVA_BASE, MSI_IOVA_LENGTH,
					      prot, IOMMU_RESV_SW_MSI);
		अगर (!msi)
			वापस;

		list_add_tail(&msi->list, head);
	पूर्ण

	iommu_dma_get_resv_regions(dev, head);
पूर्ण

अटल काष्ठा iommu_ops viommu_ops;
अटल काष्ठा virtio_driver virtio_iommu_drv;

अटल पूर्णांक viommu_match_node(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	वापस dev->parent->fwnode == data;
पूर्ण

अटल काष्ठा viommu_dev *viommu_get_by_fwnode(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा device *dev = driver_find_device(&virtio_iommu_drv.driver, शून्य,
						fwnode, viommu_match_node);
	put_device(dev);

	वापस dev ? dev_to_virtio(dev)->priv : शून्य;
पूर्ण

अटल काष्ठा iommu_device *viommu_probe_device(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा viommu_endpoपूर्णांक *vdev;
	काष्ठा viommu_dev *viommu = शून्य;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	अगर (!fwspec || fwspec->ops != &viommu_ops)
		वापस ERR_PTR(-ENODEV);

	viommu = viommu_get_by_fwnode(fwspec->iommu_fwnode);
	अगर (!viommu)
		वापस ERR_PTR(-ENODEV);

	vdev = kzalloc(माप(*vdev), GFP_KERNEL);
	अगर (!vdev)
		वापस ERR_PTR(-ENOMEM);

	vdev->dev = dev;
	vdev->viommu = viommu;
	INIT_LIST_HEAD(&vdev->resv_regions);
	dev_iommu_priv_set(dev, vdev);

	अगर (viommu->probe_size) अणु
		/* Get additional inक्रमmation क्रम this endpoपूर्णांक */
		ret = viommu_probe_endpoपूर्णांक(viommu, dev);
		अगर (ret)
			जाओ err_मुक्त_dev;
	पूर्ण

	वापस &viommu->iommu;

err_मुक्त_dev:
	generic_iommu_put_resv_regions(dev, &vdev->resv_regions);
	kमुक्त(vdev);

	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम viommu_release_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा viommu_endpoपूर्णांक *vdev;

	अगर (!fwspec || fwspec->ops != &viommu_ops)
		वापस;

	vdev = dev_iommu_priv_get(dev);

	generic_iommu_put_resv_regions(dev, &vdev->resv_regions);
	kमुक्त(vdev);
पूर्ण

अटल काष्ठा iommu_group *viommu_device_group(काष्ठा device *dev)
अणु
	अगर (dev_is_pci(dev))
		वापस pci_device_group(dev);
	अन्यथा
		वापस generic_device_group(dev);
पूर्ण

अटल पूर्णांक viommu_of_xlate(काष्ठा device *dev, काष्ठा of_phandle_args *args)
अणु
	वापस iommu_fwspec_add_ids(dev, args->args, 1);
पूर्ण

अटल काष्ठा iommu_ops viommu_ops = अणु
	.करोमुख्य_alloc		= viommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त		= viommu_करोमुख्य_मुक्त,
	.attach_dev		= viommu_attach_dev,
	.map			= viommu_map,
	.unmap			= viommu_unmap,
	.iova_to_phys		= viommu_iova_to_phys,
	.iotlb_sync		= viommu_iotlb_sync,
	.probe_device		= viommu_probe_device,
	.release_device		= viommu_release_device,
	.device_group		= viommu_device_group,
	.get_resv_regions	= viommu_get_resv_regions,
	.put_resv_regions	= generic_iommu_put_resv_regions,
	.of_xlate		= viommu_of_xlate,
	.owner			= THIS_MODULE,
पूर्ण;

अटल पूर्णांक viommu_init_vqs(काष्ठा viommu_dev *viommu)
अणु
	काष्ठा virtio_device *vdev = dev_to_virtio(viommu->dev);
	स्थिर अक्षर *names[] = अणु "request", "event" पूर्ण;
	vq_callback_t *callbacks[] = अणु
		शून्य, /* No async requests */
		viommu_event_handler,
	पूर्ण;

	वापस virtio_find_vqs(vdev, VIOMMU_NR_VQS, viommu->vqs, callbacks,
			       names, शून्य);
पूर्ण

अटल पूर्णांक viommu_fill_evtq(काष्ठा viommu_dev *viommu)
अणु
	पूर्णांक i, ret;
	काष्ठा scatterlist sg[1];
	काष्ठा viommu_event *evts;
	काष्ठा virtqueue *vq = viommu->vqs[VIOMMU_EVENT_VQ];
	माप_प्रकार nr_evts = vq->num_मुक्त;

	viommu->evts = evts = devm_kदो_स्मृति_array(viommu->dev, nr_evts,
						 माप(*evts), GFP_KERNEL);
	अगर (!evts)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr_evts; i++) अणु
		sg_init_one(sg, &evts[i], माप(*evts));
		ret = virtqueue_add_inbuf(vq, sg, 1, &evts[i], GFP_KERNEL);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक viommu_probe(काष्ठा virtio_device *vdev)
अणु
	काष्ठा device *parent_dev = vdev->dev.parent;
	काष्ठा viommu_dev *viommu = शून्य;
	काष्ठा device *dev = &vdev->dev;
	u64 input_start = 0;
	u64 input_end = -1UL;
	पूर्णांक ret;

	अगर (!virtio_has_feature(vdev, VIRTIO_F_VERSION_1) ||
	    !virtio_has_feature(vdev, VIRTIO_IOMMU_F_MAP_UNMAP))
		वापस -ENODEV;

	viommu = devm_kzalloc(dev, माप(*viommu), GFP_KERNEL);
	अगर (!viommu)
		वापस -ENOMEM;

	spin_lock_init(&viommu->request_lock);
	ida_init(&viommu->करोमुख्य_ids);
	viommu->dev = dev;
	viommu->vdev = vdev;
	INIT_LIST_HEAD(&viommu->requests);

	ret = viommu_init_vqs(viommu);
	अगर (ret)
		वापस ret;

	virtio_cपढ़ो_le(vdev, काष्ठा virtio_iommu_config, page_size_mask,
			&viommu->pgsize_biपंचांगap);

	अगर (!viommu->pgsize_biपंचांगap) अणु
		ret = -EINVAL;
		जाओ err_मुक्त_vqs;
	पूर्ण

	viommu->map_flags = VIRTIO_IOMMU_MAP_F_READ | VIRTIO_IOMMU_MAP_F_WRITE;
	viommu->last_करोमुख्य = ~0U;

	/* Optional features */
	virtio_cपढ़ो_le_feature(vdev, VIRTIO_IOMMU_F_INPUT_RANGE,
				काष्ठा virtio_iommu_config, input_range.start,
				&input_start);

	virtio_cपढ़ो_le_feature(vdev, VIRTIO_IOMMU_F_INPUT_RANGE,
				काष्ठा virtio_iommu_config, input_range.end,
				&input_end);

	virtio_cपढ़ो_le_feature(vdev, VIRTIO_IOMMU_F_DOMAIN_RANGE,
				काष्ठा virtio_iommu_config, करोमुख्य_range.start,
				&viommu->first_करोमुख्य);

	virtio_cपढ़ो_le_feature(vdev, VIRTIO_IOMMU_F_DOMAIN_RANGE,
				काष्ठा virtio_iommu_config, करोमुख्य_range.end,
				&viommu->last_करोमुख्य);

	virtio_cपढ़ो_le_feature(vdev, VIRTIO_IOMMU_F_PROBE,
				काष्ठा virtio_iommu_config, probe_size,
				&viommu->probe_size);

	viommu->geometry = (काष्ठा iommu_करोमुख्य_geometry) अणु
		.aperture_start	= input_start,
		.aperture_end	= input_end,
		.क्रमce_aperture	= true,
	पूर्ण;

	अगर (virtio_has_feature(vdev, VIRTIO_IOMMU_F_MMIO))
		viommu->map_flags |= VIRTIO_IOMMU_MAP_F_MMIO;

	viommu_ops.pgsize_biपंचांगap = viommu->pgsize_biपंचांगap;

	virtio_device_पढ़ोy(vdev);

	/* Populate the event queue with buffers */
	ret = viommu_fill_evtq(viommu);
	अगर (ret)
		जाओ err_मुक्त_vqs;

	ret = iommu_device_sysfs_add(&viommu->iommu, dev, शून्य, "%s",
				     virtio_bus_name(vdev));
	अगर (ret)
		जाओ err_मुक्त_vqs;

	iommu_device_रेजिस्टर(&viommu->iommu, &viommu_ops, parent_dev);

#अगर_घोषित CONFIG_PCI
	अगर (pci_bus_type.iommu_ops != &viommu_ops) अणु
		ret = bus_set_iommu(&pci_bus_type, &viommu_ops);
		अगर (ret)
			जाओ err_unरेजिस्टर;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM_AMBA
	अगर (amba_bustype.iommu_ops != &viommu_ops) अणु
		ret = bus_set_iommu(&amba_bustype, &viommu_ops);
		अगर (ret)
			जाओ err_unरेजिस्टर;
	पूर्ण
#पूर्ण_अगर
	अगर (platक्रमm_bus_type.iommu_ops != &viommu_ops) अणु
		ret = bus_set_iommu(&platक्रमm_bus_type, &viommu_ops);
		अगर (ret)
			जाओ err_unरेजिस्टर;
	पूर्ण

	vdev->priv = viommu;

	dev_info(dev, "input address: %u bits\n",
		 order_base_2(viommu->geometry.aperture_end));
	dev_info(dev, "page mask: %#llx\n", viommu->pgsize_biपंचांगap);

	वापस 0;

err_unरेजिस्टर:
	iommu_device_sysfs_हटाओ(&viommu->iommu);
	iommu_device_unरेजिस्टर(&viommu->iommu);
err_मुक्त_vqs:
	vdev->config->del_vqs(vdev);

	वापस ret;
पूर्ण

अटल व्योम viommu_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा viommu_dev *viommu = vdev->priv;

	iommu_device_sysfs_हटाओ(&viommu->iommu);
	iommu_device_unरेजिस्टर(&viommu->iommu);

	/* Stop all virtqueues */
	vdev->config->reset(vdev);
	vdev->config->del_vqs(vdev);

	dev_info(&vdev->dev, "device removed\n");
पूर्ण

अटल व्योम viommu_config_changed(काष्ठा virtio_device *vdev)
अणु
	dev_warn(&vdev->dev, "config changed\n");
पूर्ण

अटल अचिन्हित पूर्णांक features[] = अणु
	VIRTIO_IOMMU_F_MAP_UNMAP,
	VIRTIO_IOMMU_F_INPUT_RANGE,
	VIRTIO_IOMMU_F_DOMAIN_RANGE,
	VIRTIO_IOMMU_F_PROBE,
	VIRTIO_IOMMU_F_MMIO,
पूर्ण;

अटल काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_IOMMU, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(virtio, id_table);

अटल काष्ठा virtio_driver virtio_iommu_drv = अणु
	.driver.name		= KBUILD_MODNAME,
	.driver.owner		= THIS_MODULE,
	.id_table		= id_table,
	.feature_table		= features,
	.feature_table_size	= ARRAY_SIZE(features),
	.probe			= viommu_probe,
	.हटाओ			= viommu_हटाओ,
	.config_changed		= viommu_config_changed,
पूर्ण;

module_virtio_driver(virtio_iommu_drv);

MODULE_DESCRIPTION("Virtio IOMMU driver");
MODULE_AUTHOR("Jean-Philippe Brucker <jean-philippe.brucker@arm.com>");
MODULE_LICENSE("GPL v2");
