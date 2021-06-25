<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018-2020 Intel Corporation.
 * Copyright (C) 2020 Red Hat, Inc.
 *
 * Author: Tiwei Bie <tiwei.bie@पूर्णांकel.com>
 *         Jason Wang <jasowang@redhat.com>
 *
 * Thanks Michael S. Tsirkin क्रम the valuable comments and
 * suggestions.  And thanks to Cunming Liang and Zhihong Wang क्रम all
 * their supports.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/iommu.h>
#समावेश <linux/uuid.h>
#समावेश <linux/vdpa.h>
#समावेश <linux/nospec.h>
#समावेश <linux/vhost.h>

#समावेश "vhost.h"

क्रमागत अणु
	VHOST_VDPA_BACKEND_FEATURES =
	(1ULL << VHOST_BACKEND_F_IOTLB_MSG_V2) |
	(1ULL << VHOST_BACKEND_F_IOTLB_BATCH),
पूर्ण;

#घोषणा VHOST_VDPA_DEV_MAX (1U << MINORBITS)

काष्ठा vhost_vdpa अणु
	काष्ठा vhost_dev vdev;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा vhost_virtqueue *vqs;
	काष्ठा completion completion;
	काष्ठा vdpa_device *vdpa;
	काष्ठा device dev;
	काष्ठा cdev cdev;
	atomic_t खोलोed;
	पूर्णांक nvqs;
	पूर्णांक virtio_id;
	पूर्णांक minor;
	काष्ठा eventfd_ctx *config_ctx;
	पूर्णांक in_batch;
	काष्ठा vdpa_iova_range range;
पूर्ण;

अटल DEFINE_IDA(vhost_vdpa_ida);

अटल dev_t vhost_vdpa_major;

अटल व्योम handle_vq_kick(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_virtqueue *vq = container_of(work, काष्ठा vhost_virtqueue,
						  poll.work);
	काष्ठा vhost_vdpa *v = container_of(vq->dev, काष्ठा vhost_vdpa, vdev);
	स्थिर काष्ठा vdpa_config_ops *ops = v->vdpa->config;

	ops->kick_vq(v->vdpa, vq - v->vqs);
पूर्ण

अटल irqवापस_t vhost_vdpa_virtqueue_cb(व्योम *निजी)
अणु
	काष्ठा vhost_virtqueue *vq = निजी;
	काष्ठा eventfd_ctx *call_ctx = vq->call_ctx.ctx;

	अगर (call_ctx)
		eventfd_संकेत(call_ctx, 1);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t vhost_vdpa_config_cb(व्योम *निजी)
अणु
	काष्ठा vhost_vdpa *v = निजी;
	काष्ठा eventfd_ctx *config_ctx = v->config_ctx;

	अगर (config_ctx)
		eventfd_संकेत(config_ctx, 1);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम vhost_vdpa_setup_vq_irq(काष्ठा vhost_vdpa *v, u16 qid)
अणु
	काष्ठा vhost_virtqueue *vq = &v->vqs[qid];
	स्थिर काष्ठा vdpa_config_ops *ops = v->vdpa->config;
	काष्ठा vdpa_device *vdpa = v->vdpa;
	पूर्णांक ret, irq;

	अगर (!ops->get_vq_irq)
		वापस;

	irq = ops->get_vq_irq(vdpa, qid);
	irq_bypass_unरेजिस्टर_producer(&vq->call_ctx.producer);
	अगर (!vq->call_ctx.ctx || irq < 0)
		वापस;

	vq->call_ctx.producer.token = vq->call_ctx.ctx;
	vq->call_ctx.producer.irq = irq;
	ret = irq_bypass_रेजिस्टर_producer(&vq->call_ctx.producer);
	अगर (unlikely(ret))
		dev_info(&v->dev, "vq %u, irq bypass producer (token %p) registration fails, ret =  %d\n",
			 qid, vq->call_ctx.producer.token, ret);
पूर्ण

अटल व्योम vhost_vdpa_unsetup_vq_irq(काष्ठा vhost_vdpa *v, u16 qid)
अणु
	काष्ठा vhost_virtqueue *vq = &v->vqs[qid];

	irq_bypass_unरेजिस्टर_producer(&vq->call_ctx.producer);
पूर्ण

अटल व्योम vhost_vdpa_reset(काष्ठा vhost_vdpa *v)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;

	vdpa_reset(vdpa);
	v->in_batch = 0;
पूर्ण

अटल दीर्घ vhost_vdpa_get_device_id(काष्ठा vhost_vdpa *v, u8 __user *argp)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	u32 device_id;

	device_id = ops->get_device_id(vdpa);

	अगर (copy_to_user(argp, &device_id, माप(device_id)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ vhost_vdpa_get_status(काष्ठा vhost_vdpa *v, u8 __user *statusp)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	u8 status;

	status = ops->get_status(vdpa);

	अगर (copy_to_user(statusp, &status, माप(status)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ vhost_vdpa_set_status(काष्ठा vhost_vdpa *v, u8 __user *statusp)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	u8 status, status_old;
	पूर्णांक nvqs = v->nvqs;
	u16 i;

	अगर (copy_from_user(&status, statusp, माप(status)))
		वापस -EFAULT;

	status_old = ops->get_status(vdpa);

	/*
	 * Userspace shouldn't हटाओ status bits unless reset the
	 * status to 0.
	 */
	अगर (status != 0 && (ops->get_status(vdpa) & ~status) != 0)
		वापस -EINVAL;

	ops->set_status(vdpa, status);

	अगर ((status & VIRTIO_CONFIG_S_DRIVER_OK) && !(status_old & VIRTIO_CONFIG_S_DRIVER_OK))
		क्रम (i = 0; i < nvqs; i++)
			vhost_vdpa_setup_vq_irq(v, i);

	अगर ((status_old & VIRTIO_CONFIG_S_DRIVER_OK) && !(status & VIRTIO_CONFIG_S_DRIVER_OK))
		क्रम (i = 0; i < nvqs; i++)
			vhost_vdpa_unsetup_vq_irq(v, i);

	वापस 0;
पूर्ण

अटल पूर्णांक vhost_vdpa_config_validate(काष्ठा vhost_vdpa *v,
				      काष्ठा vhost_vdpa_config *c)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;
	दीर्घ size = vdpa->config->get_config_size(vdpa);

	अगर (c->len == 0)
		वापस -EINVAL;

	अगर (c->len > size - c->off)
		वापस -E2BIG;

	वापस 0;
पूर्ण

अटल दीर्घ vhost_vdpa_get_config(काष्ठा vhost_vdpa *v,
				  काष्ठा vhost_vdpa_config __user *c)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;
	काष्ठा vhost_vdpa_config config;
	अचिन्हित दीर्घ size = दुरत्व(काष्ठा vhost_vdpa_config, buf);
	u8 *buf;

	अगर (copy_from_user(&config, c, size))
		वापस -EFAULT;
	अगर (vhost_vdpa_config_validate(v, &config))
		वापस -EINVAL;
	buf = kvzalloc(config.len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	vdpa_get_config(vdpa, config.off, buf, config.len);

	अगर (copy_to_user(c->buf, buf, config.len)) अणु
		kvमुक्त(buf);
		वापस -EFAULT;
	पूर्ण

	kvमुक्त(buf);
	वापस 0;
पूर्ण

अटल दीर्घ vhost_vdpa_set_config(काष्ठा vhost_vdpa *v,
				  काष्ठा vhost_vdpa_config __user *c)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	काष्ठा vhost_vdpa_config config;
	अचिन्हित दीर्घ size = दुरत्व(काष्ठा vhost_vdpa_config, buf);
	u8 *buf;

	अगर (copy_from_user(&config, c, size))
		वापस -EFAULT;
	अगर (vhost_vdpa_config_validate(v, &config))
		वापस -EINVAL;

	buf = vmemdup_user(c->buf, config.len);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	ops->set_config(vdpa, config.off, buf, config.len);

	kvमुक्त(buf);
	वापस 0;
पूर्ण

अटल दीर्घ vhost_vdpa_get_features(काष्ठा vhost_vdpa *v, u64 __user *featurep)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	u64 features;

	features = ops->get_features(vdpa);

	अगर (copy_to_user(featurep, &features, माप(features)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ vhost_vdpa_set_features(काष्ठा vhost_vdpa *v, u64 __user *featurep)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	u64 features;

	/*
	 * It's not allowed to change the features after they have
	 * been negotiated.
	 */
	अगर (ops->get_status(vdpa) & VIRTIO_CONFIG_S_FEATURES_OK)
		वापस -EBUSY;

	अगर (copy_from_user(&features, featurep, माप(features)))
		वापस -EFAULT;

	अगर (vdpa_set_features(vdpa, features))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल दीर्घ vhost_vdpa_get_vring_num(काष्ठा vhost_vdpa *v, u16 __user *argp)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	u16 num;

	num = ops->get_vq_num_max(vdpa);

	अगर (copy_to_user(argp, &num, माप(num)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल व्योम vhost_vdpa_config_put(काष्ठा vhost_vdpa *v)
अणु
	अगर (v->config_ctx) अणु
		eventfd_ctx_put(v->config_ctx);
		v->config_ctx = शून्य;
	पूर्ण
पूर्ण

अटल दीर्घ vhost_vdpa_set_config_call(काष्ठा vhost_vdpa *v, u32 __user *argp)
अणु
	काष्ठा vdpa_callback cb;
	पूर्णांक fd;
	काष्ठा eventfd_ctx *ctx;

	cb.callback = vhost_vdpa_config_cb;
	cb.निजी = v->vdpa;
	अगर (copy_from_user(&fd, argp, माप(fd)))
		वापस  -EFAULT;

	ctx = fd == VHOST_खाता_UNBIND ? शून्य : eventfd_ctx_fdget(fd);
	swap(ctx, v->config_ctx);

	अगर (!IS_ERR_OR_शून्य(ctx))
		eventfd_ctx_put(ctx);

	अगर (IS_ERR(v->config_ctx)) अणु
		दीर्घ ret = PTR_ERR(v->config_ctx);

		v->config_ctx = शून्य;
		वापस ret;
	पूर्ण

	v->vdpa->config->set_config_cb(v->vdpa, &cb);

	वापस 0;
पूर्ण

अटल दीर्घ vhost_vdpa_get_iova_range(काष्ठा vhost_vdpa *v, u32 __user *argp)
अणु
	काष्ठा vhost_vdpa_iova_range range = अणु
		.first = v->range.first,
		.last = v->range.last,
	पूर्ण;

	अगर (copy_to_user(argp, &range, माप(range)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल दीर्घ vhost_vdpa_vring_ioctl(काष्ठा vhost_vdpa *v, अचिन्हित पूर्णांक cmd,
				   व्योम __user *argp)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	काष्ठा vdpa_vq_state vq_state;
	काष्ठा vdpa_callback cb;
	काष्ठा vhost_virtqueue *vq;
	काष्ठा vhost_vring_state s;
	u32 idx;
	दीर्घ r;

	r = get_user(idx, (u32 __user *)argp);
	अगर (r < 0)
		वापस r;

	अगर (idx >= v->nvqs)
		वापस -ENOBUFS;

	idx = array_index_nospec(idx, v->nvqs);
	vq = &v->vqs[idx];

	चयन (cmd) अणु
	हाल VHOST_VDPA_SET_VRING_ENABLE:
		अगर (copy_from_user(&s, argp, माप(s)))
			वापस -EFAULT;
		ops->set_vq_पढ़ोy(vdpa, idx, s.num);
		वापस 0;
	हाल VHOST_GET_VRING_BASE:
		r = ops->get_vq_state(v->vdpa, idx, &vq_state);
		अगर (r)
			वापस r;

		vq->last_avail_idx = vq_state.avail_index;
		अवरोध;
	पूर्ण

	r = vhost_vring_ioctl(&v->vdev, cmd, argp);
	अगर (r)
		वापस r;

	चयन (cmd) अणु
	हाल VHOST_SET_VRING_ADDR:
		अगर (ops->set_vq_address(vdpa, idx,
					(u64)(uपूर्णांकptr_t)vq->desc,
					(u64)(uपूर्णांकptr_t)vq->avail,
					(u64)(uपूर्णांकptr_t)vq->used))
			r = -EINVAL;
		अवरोध;

	हाल VHOST_SET_VRING_BASE:
		vq_state.avail_index = vq->last_avail_idx;
		अगर (ops->set_vq_state(vdpa, idx, &vq_state))
			r = -EINVAL;
		अवरोध;

	हाल VHOST_SET_VRING_CALL:
		अगर (vq->call_ctx.ctx) अणु
			cb.callback = vhost_vdpa_virtqueue_cb;
			cb.निजी = vq;
		पूर्ण अन्यथा अणु
			cb.callback = शून्य;
			cb.निजी = शून्य;
		पूर्ण
		ops->set_vq_cb(vdpa, idx, &cb);
		vhost_vdpa_setup_vq_irq(v, idx);
		अवरोध;

	हाल VHOST_SET_VRING_NUM:
		ops->set_vq_num(vdpa, idx, vq->num);
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल दीर्घ vhost_vdpa_unlocked_ioctl(काष्ठा file *filep,
				      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vhost_vdpa *v = filep->निजी_data;
	काष्ठा vhost_dev *d = &v->vdev;
	व्योम __user *argp = (व्योम __user *)arg;
	u64 __user *featurep = argp;
	u64 features;
	दीर्घ r = 0;

	अगर (cmd == VHOST_SET_BACKEND_FEATURES) अणु
		अगर (copy_from_user(&features, featurep, माप(features)))
			वापस -EFAULT;
		अगर (features & ~VHOST_VDPA_BACKEND_FEATURES)
			वापस -EOPNOTSUPP;
		vhost_set_backend_features(&v->vdev, features);
		वापस 0;
	पूर्ण

	mutex_lock(&d->mutex);

	चयन (cmd) अणु
	हाल VHOST_VDPA_GET_DEVICE_ID:
		r = vhost_vdpa_get_device_id(v, argp);
		अवरोध;
	हाल VHOST_VDPA_GET_STATUS:
		r = vhost_vdpa_get_status(v, argp);
		अवरोध;
	हाल VHOST_VDPA_SET_STATUS:
		r = vhost_vdpa_set_status(v, argp);
		अवरोध;
	हाल VHOST_VDPA_GET_CONFIG:
		r = vhost_vdpa_get_config(v, argp);
		अवरोध;
	हाल VHOST_VDPA_SET_CONFIG:
		r = vhost_vdpa_set_config(v, argp);
		अवरोध;
	हाल VHOST_GET_FEATURES:
		r = vhost_vdpa_get_features(v, argp);
		अवरोध;
	हाल VHOST_SET_FEATURES:
		r = vhost_vdpa_set_features(v, argp);
		अवरोध;
	हाल VHOST_VDPA_GET_VRING_NUM:
		r = vhost_vdpa_get_vring_num(v, argp);
		अवरोध;
	हाल VHOST_SET_LOG_BASE:
	हाल VHOST_SET_LOG_FD:
		r = -ENOIOCTLCMD;
		अवरोध;
	हाल VHOST_VDPA_SET_CONFIG_CALL:
		r = vhost_vdpa_set_config_call(v, argp);
		अवरोध;
	हाल VHOST_GET_BACKEND_FEATURES:
		features = VHOST_VDPA_BACKEND_FEATURES;
		अगर (copy_to_user(featurep, &features, माप(features)))
			r = -EFAULT;
		अवरोध;
	हाल VHOST_VDPA_GET_IOVA_RANGE:
		r = vhost_vdpa_get_iova_range(v, argp);
		अवरोध;
	शेष:
		r = vhost_dev_ioctl(&v->vdev, cmd, argp);
		अगर (r == -ENOIOCTLCMD)
			r = vhost_vdpa_vring_ioctl(v, cmd, argp);
		अवरोध;
	पूर्ण

	mutex_unlock(&d->mutex);
	वापस r;
पूर्ण

अटल व्योम vhost_vdpa_iotlb_unmap(काष्ठा vhost_vdpa *v, u64 start, u64 last)
अणु
	काष्ठा vhost_dev *dev = &v->vdev;
	काष्ठा vhost_iotlb *iotlb = dev->iotlb;
	काष्ठा vhost_iotlb_map *map;
	काष्ठा page *page;
	अचिन्हित दीर्घ pfn, pinned;

	जबतक ((map = vhost_iotlb_itree_first(iotlb, start, last)) != शून्य) अणु
		pinned = map->size >> PAGE_SHIFT;
		क्रम (pfn = map->addr >> PAGE_SHIFT;
		     pinned > 0; pfn++, pinned--) अणु
			page = pfn_to_page(pfn);
			अगर (map->perm & VHOST_ACCESS_WO)
				set_page_dirty_lock(page);
			unpin_user_page(page);
		पूर्ण
		atomic64_sub(map->size >> PAGE_SHIFT, &dev->mm->pinned_vm);
		vhost_iotlb_map_मुक्त(iotlb, map);
	पूर्ण
पूर्ण

अटल व्योम vhost_vdpa_iotlb_मुक्त(काष्ठा vhost_vdpa *v)
अणु
	काष्ठा vhost_dev *dev = &v->vdev;

	vhost_vdpa_iotlb_unmap(v, 0ULL, 0ULL - 1);
	kमुक्त(dev->iotlb);
	dev->iotlb = शून्य;
पूर्ण

अटल पूर्णांक perm_to_iommu_flags(u32 perm)
अणु
	पूर्णांक flags = 0;

	चयन (perm) अणु
	हाल VHOST_ACCESS_WO:
		flags |= IOMMU_WRITE;
		अवरोध;
	हाल VHOST_ACCESS_RO:
		flags |= IOMMU_READ;
		अवरोध;
	हाल VHOST_ACCESS_RW:
		flags |= (IOMMU_WRITE | IOMMU_READ);
		अवरोध;
	शेष:
		WARN(1, "invalidate vhost IOTLB permission\n");
		अवरोध;
	पूर्ण

	वापस flags | IOMMU_CACHE;
पूर्ण

अटल पूर्णांक vhost_vdpa_map(काष्ठा vhost_vdpa *v,
			  u64 iova, u64 size, u64 pa, u32 perm)
अणु
	काष्ठा vhost_dev *dev = &v->vdev;
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	पूर्णांक r = 0;

	r = vhost_iotlb_add_range(dev->iotlb, iova, iova + size - 1,
				  pa, perm);
	अगर (r)
		वापस r;

	अगर (ops->dma_map) अणु
		r = ops->dma_map(vdpa, iova, size, pa, perm);
	पूर्ण अन्यथा अगर (ops->set_map) अणु
		अगर (!v->in_batch)
			r = ops->set_map(vdpa, dev->iotlb);
	पूर्ण अन्यथा अणु
		r = iommu_map(v->करोमुख्य, iova, pa, size,
			      perm_to_iommu_flags(perm));
	पूर्ण

	अगर (r)
		vhost_iotlb_del_range(dev->iotlb, iova, iova + size - 1);
	अन्यथा
		atomic64_add(size >> PAGE_SHIFT, &dev->mm->pinned_vm);

	वापस r;
पूर्ण

अटल व्योम vhost_vdpa_unmap(काष्ठा vhost_vdpa *v, u64 iova, u64 size)
अणु
	काष्ठा vhost_dev *dev = &v->vdev;
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;

	vhost_vdpa_iotlb_unmap(v, iova, iova + size - 1);

	अगर (ops->dma_map) अणु
		ops->dma_unmap(vdpa, iova, size);
	पूर्ण अन्यथा अगर (ops->set_map) अणु
		अगर (!v->in_batch)
			ops->set_map(vdpa, dev->iotlb);
	पूर्ण अन्यथा अणु
		iommu_unmap(v->करोमुख्य, iova, size);
	पूर्ण
पूर्ण

अटल पूर्णांक vhost_vdpa_process_iotlb_update(काष्ठा vhost_vdpa *v,
					   काष्ठा vhost_iotlb_msg *msg)
अणु
	काष्ठा vhost_dev *dev = &v->vdev;
	काष्ठा vhost_iotlb *iotlb = dev->iotlb;
	काष्ठा page **page_list;
	अचिन्हित दीर्घ list_size = PAGE_SIZE / माप(काष्ठा page *);
	अचिन्हित पूर्णांक gup_flags = FOLL_LONGTERM;
	अचिन्हित दीर्घ npages, cur_base, map_pfn, last_pfn = 0;
	अचिन्हित दीर्घ lock_limit, sz2pin, nchunks, i;
	u64 iova = msg->iova;
	दीर्घ pinned;
	पूर्णांक ret = 0;

	अगर (msg->iova < v->range.first ||
	    msg->iova + msg->size - 1 > v->range.last)
		वापस -EINVAL;

	अगर (vhost_iotlb_itree_first(iotlb, msg->iova,
				    msg->iova + msg->size - 1))
		वापस -EEXIST;

	/* Limit the use of memory क्रम bookkeeping */
	page_list = (काष्ठा page **) __get_मुक्त_page(GFP_KERNEL);
	अगर (!page_list)
		वापस -ENOMEM;

	अगर (msg->perm & VHOST_ACCESS_WO)
		gup_flags |= FOLL_WRITE;

	npages = PAGE_ALIGN(msg->size + (iova & ~PAGE_MASK)) >> PAGE_SHIFT;
	अगर (!npages) अणु
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	mmap_पढ़ो_lock(dev->mm);

	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	अगर (npages + atomic64_पढ़ो(&dev->mm->pinned_vm) > lock_limit) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	cur_base = msg->uaddr & PAGE_MASK;
	iova &= PAGE_MASK;
	nchunks = 0;

	जबतक (npages) अणु
		sz2pin = min_t(अचिन्हित दीर्घ, npages, list_size);
		pinned = pin_user_pages(cur_base, sz2pin,
					gup_flags, page_list, शून्य);
		अगर (sz2pin != pinned) अणु
			अगर (pinned < 0) अणु
				ret = pinned;
			पूर्ण अन्यथा अणु
				unpin_user_pages(page_list, pinned);
				ret = -ENOMEM;
			पूर्ण
			जाओ out;
		पूर्ण
		nchunks++;

		अगर (!last_pfn)
			map_pfn = page_to_pfn(page_list[0]);

		क्रम (i = 0; i < pinned; i++) अणु
			अचिन्हित दीर्घ this_pfn = page_to_pfn(page_list[i]);
			u64 csize;

			अगर (last_pfn && (this_pfn != last_pfn + 1)) अणु
				/* Pin a contiguous chunk of memory */
				csize = (last_pfn - map_pfn + 1) << PAGE_SHIFT;
				ret = vhost_vdpa_map(v, iova, csize,
						     map_pfn << PAGE_SHIFT,
						     msg->perm);
				अगर (ret) अणु
					/*
					 * Unpin the pages that are left unmapped
					 * from this poपूर्णांक on in the current
					 * page_list. The reमुख्यing outstanding
					 * ones which may stride across several
					 * chunks will be covered in the common
					 * error path subsequently.
					 */
					unpin_user_pages(&page_list[i],
							 pinned - i);
					जाओ out;
				पूर्ण

				map_pfn = this_pfn;
				iova += csize;
				nchunks = 0;
			पूर्ण

			last_pfn = this_pfn;
		पूर्ण

		cur_base += pinned << PAGE_SHIFT;
		npages -= pinned;
	पूर्ण

	/* Pin the rest chunk */
	ret = vhost_vdpa_map(v, iova, (last_pfn - map_pfn + 1) << PAGE_SHIFT,
			     map_pfn << PAGE_SHIFT, msg->perm);
out:
	अगर (ret) अणु
		अगर (nchunks) अणु
			अचिन्हित दीर्घ pfn;

			/*
			 * Unpin the outstanding pages which are yet to be
			 * mapped but haven't due to vdpa_map() or
			 * pin_user_pages() failure.
			 *
			 * Mapped pages are accounted in vdpa_map(), hence
			 * the corresponding unpinning will be handled by
			 * vdpa_unmap().
			 */
			WARN_ON(!last_pfn);
			क्रम (pfn = map_pfn; pfn <= last_pfn; pfn++)
				unpin_user_page(pfn_to_page(pfn));
		पूर्ण
		vhost_vdpa_unmap(v, msg->iova, msg->size);
	पूर्ण
unlock:
	mmap_पढ़ो_unlock(dev->mm);
मुक्त:
	मुक्त_page((अचिन्हित दीर्घ)page_list);
	वापस ret;
पूर्ण

अटल पूर्णांक vhost_vdpa_process_iotlb_msg(काष्ठा vhost_dev *dev,
					काष्ठा vhost_iotlb_msg *msg)
अणु
	काष्ठा vhost_vdpa *v = container_of(dev, काष्ठा vhost_vdpa, vdev);
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	पूर्णांक r = 0;

	mutex_lock(&dev->mutex);

	r = vhost_dev_check_owner(dev);
	अगर (r)
		जाओ unlock;

	चयन (msg->type) अणु
	हाल VHOST_IOTLB_UPDATE:
		r = vhost_vdpa_process_iotlb_update(v, msg);
		अवरोध;
	हाल VHOST_IOTLB_INVALIDATE:
		vhost_vdpa_unmap(v, msg->iova, msg->size);
		अवरोध;
	हाल VHOST_IOTLB_BATCH_BEGIN:
		v->in_batch = true;
		अवरोध;
	हाल VHOST_IOTLB_BATCH_END:
		अगर (v->in_batch && ops->set_map)
			ops->set_map(vdpa, dev->iotlb);
		v->in_batch = false;
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण
unlock:
	mutex_unlock(&dev->mutex);

	वापस r;
पूर्ण

अटल sमाप_प्रकार vhost_vdpa_chr_ग_लिखो_iter(काष्ठा kiocb *iocb,
					 काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा vhost_vdpa *v = file->निजी_data;
	काष्ठा vhost_dev *dev = &v->vdev;

	वापस vhost_chr_ग_लिखो_iter(dev, from);
पूर्ण

अटल पूर्णांक vhost_vdpa_alloc_करोमुख्य(काष्ठा vhost_vdpa *v)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	काष्ठा device *dma_dev = vdpa_get_dma_dev(vdpa);
	काष्ठा bus_type *bus;
	पूर्णांक ret;

	/* Device want to करो DMA by itself */
	अगर (ops->set_map || ops->dma_map)
		वापस 0;

	bus = dma_dev->bus;
	अगर (!bus)
		वापस -EFAULT;

	अगर (!iommu_capable(bus, IOMMU_CAP_CACHE_COHERENCY))
		वापस -ENOTSUPP;

	v->करोमुख्य = iommu_करोमुख्य_alloc(bus);
	अगर (!v->करोमुख्य)
		वापस -EIO;

	ret = iommu_attach_device(v->करोमुख्य, dma_dev);
	अगर (ret)
		जाओ err_attach;

	वापस 0;

err_attach:
	iommu_करोमुख्य_मुक्त(v->करोमुख्य);
	वापस ret;
पूर्ण

अटल व्योम vhost_vdpa_मुक्त_करोमुख्य(काष्ठा vhost_vdpa *v)
अणु
	काष्ठा vdpa_device *vdpa = v->vdpa;
	काष्ठा device *dma_dev = vdpa_get_dma_dev(vdpa);

	अगर (v->करोमुख्य) अणु
		iommu_detach_device(v->करोमुख्य, dma_dev);
		iommu_करोमुख्य_मुक्त(v->करोमुख्य);
	पूर्ण

	v->करोमुख्य = शून्य;
पूर्ण

अटल व्योम vhost_vdpa_set_iova_range(काष्ठा vhost_vdpa *v)
अणु
	काष्ठा vdpa_iova_range *range = &v->range;
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;

	अगर (ops->get_iova_range) अणु
		*range = ops->get_iova_range(vdpa);
	पूर्ण अन्यथा अगर (v->करोमुख्य && v->करोमुख्य->geometry.क्रमce_aperture) अणु
		range->first = v->करोमुख्य->geometry.aperture_start;
		range->last = v->करोमुख्य->geometry.aperture_end;
	पूर्ण अन्यथा अणु
		range->first = 0;
		range->last = ULदीर्घ_उच्च;
	पूर्ण
पूर्ण

अटल पूर्णांक vhost_vdpa_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा vhost_vdpa *v;
	काष्ठा vhost_dev *dev;
	काष्ठा vhost_virtqueue **vqs;
	पूर्णांक nvqs, i, r, खोलोed;

	v = container_of(inode->i_cdev, काष्ठा vhost_vdpa, cdev);

	खोलोed = atomic_cmpxchg(&v->खोलोed, 0, 1);
	अगर (खोलोed)
		वापस -EBUSY;

	nvqs = v->nvqs;
	vhost_vdpa_reset(v);

	vqs = kदो_स्मृति_array(nvqs, माप(*vqs), GFP_KERNEL);
	अगर (!vqs) अणु
		r = -ENOMEM;
		जाओ err;
	पूर्ण

	dev = &v->vdev;
	क्रम (i = 0; i < nvqs; i++) अणु
		vqs[i] = &v->vqs[i];
		vqs[i]->handle_kick = handle_vq_kick;
	पूर्ण
	vhost_dev_init(dev, vqs, nvqs, 0, 0, 0, false,
		       vhost_vdpa_process_iotlb_msg);

	dev->iotlb = vhost_iotlb_alloc(0, 0);
	अगर (!dev->iotlb) अणु
		r = -ENOMEM;
		जाओ err_init_iotlb;
	पूर्ण

	r = vhost_vdpa_alloc_करोमुख्य(v);
	अगर (r)
		जाओ err_init_iotlb;

	vhost_vdpa_set_iova_range(v);

	filep->निजी_data = v;

	वापस 0;

err_init_iotlb:
	vhost_dev_cleanup(&v->vdev);
	kमुक्त(vqs);
err:
	atomic_dec(&v->खोलोed);
	वापस r;
पूर्ण

अटल व्योम vhost_vdpa_clean_irq(काष्ठा vhost_vdpa *v)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < v->nvqs; i++)
		vhost_vdpa_unsetup_vq_irq(v, i);
पूर्ण

अटल पूर्णांक vhost_vdpa_release(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा vhost_vdpa *v = filep->निजी_data;
	काष्ठा vhost_dev *d = &v->vdev;

	mutex_lock(&d->mutex);
	filep->निजी_data = शून्य;
	vhost_vdpa_reset(v);
	vhost_dev_stop(&v->vdev);
	vhost_vdpa_iotlb_मुक्त(v);
	vhost_vdpa_मुक्त_करोमुख्य(v);
	vhost_vdpa_config_put(v);
	vhost_vdpa_clean_irq(v);
	vhost_dev_cleanup(&v->vdev);
	kमुक्त(v->vdev.vqs);
	mutex_unlock(&d->mutex);

	atomic_dec(&v->खोलोed);
	complete(&v->completion);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MMU
अटल vm_fault_t vhost_vdpa_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vhost_vdpa *v = vmf->vma->vm_file->निजी_data;
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	काष्ठा vdpa_notअगरication_area notअगरy;
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	u16 index = vma->vm_pgoff;

	notअगरy = ops->get_vq_notअगरication(vdpa, index);

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	अगर (remap_pfn_range(vma, vmf->address & PAGE_MASK,
			    notअगरy.addr >> PAGE_SHIFT, PAGE_SIZE,
			    vma->vm_page_prot))
		वापस VM_FAULT_SIGBUS;

	वापस VM_FAULT_NOPAGE;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा vhost_vdpa_vm_ops = अणु
	.fault = vhost_vdpa_fault,
पूर्ण;

अटल पूर्णांक vhost_vdpa_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vhost_vdpa *v = vma->vm_file->निजी_data;
	काष्ठा vdpa_device *vdpa = v->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	काष्ठा vdpa_notअगरication_area notअगरy;
	अचिन्हित दीर्घ index = vma->vm_pgoff;

	अगर (vma->vm_end - vma->vm_start != PAGE_SIZE)
		वापस -EINVAL;
	अगर ((vma->vm_flags & VM_SHARED) == 0)
		वापस -EINVAL;
	अगर (vma->vm_flags & VM_READ)
		वापस -EINVAL;
	अगर (index > 65535)
		वापस -EINVAL;
	अगर (!ops->get_vq_notअगरication)
		वापस -ENOTSUPP;

	/* To be safe and easily modelled by userspace, We only
	 * support the करोorbell which sits on the page boundary and
	 * करोes not share the page with other रेजिस्टरs.
	 */
	notअगरy = ops->get_vq_notअगरication(vdpa, index);
	अगर (notअगरy.addr & (PAGE_SIZE - 1))
		वापस -EINVAL;
	अगर (vma->vm_end - vma->vm_start != notअगरy.size)
		वापस -ENOTSUPP;

	vma->vm_flags |= VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_ops = &vhost_vdpa_vm_ops;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */

अटल स्थिर काष्ठा file_operations vhost_vdpa_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= vhost_vdpa_खोलो,
	.release	= vhost_vdpa_release,
	.ग_लिखो_iter	= vhost_vdpa_chr_ग_लिखो_iter,
	.unlocked_ioctl	= vhost_vdpa_unlocked_ioctl,
#अगर_घोषित CONFIG_MMU
	.mmap		= vhost_vdpa_mmap,
#पूर्ण_अगर /* CONFIG_MMU */
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;

अटल व्योम vhost_vdpa_release_dev(काष्ठा device *device)
अणु
	काष्ठा vhost_vdpa *v =
	       container_of(device, काष्ठा vhost_vdpa, dev);

	ida_simple_हटाओ(&vhost_vdpa_ida, v->minor);
	kमुक्त(v->vqs);
	kमुक्त(v);
पूर्ण

अटल पूर्णांक vhost_vdpa_probe(काष्ठा vdpa_device *vdpa)
अणु
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	काष्ठा vhost_vdpa *v;
	पूर्णांक minor;
	पूर्णांक r;

	v = kzalloc(माप(*v), GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	अगर (!v)
		वापस -ENOMEM;

	minor = ida_simple_get(&vhost_vdpa_ida, 0,
			       VHOST_VDPA_DEV_MAX, GFP_KERNEL);
	अगर (minor < 0) अणु
		kमुक्त(v);
		वापस minor;
	पूर्ण

	atomic_set(&v->खोलोed, 0);
	v->minor = minor;
	v->vdpa = vdpa;
	v->nvqs = vdpa->nvqs;
	v->virtio_id = ops->get_device_id(vdpa);

	device_initialize(&v->dev);
	v->dev.release = vhost_vdpa_release_dev;
	v->dev.parent = &vdpa->dev;
	v->dev.devt = MKDEV(MAJOR(vhost_vdpa_major), minor);
	v->vqs = kदो_स्मृति_array(v->nvqs, माप(काष्ठा vhost_virtqueue),
			       GFP_KERNEL);
	अगर (!v->vqs) अणु
		r = -ENOMEM;
		जाओ err;
	पूर्ण

	r = dev_set_name(&v->dev, "vhost-vdpa-%u", minor);
	अगर (r)
		जाओ err;

	cdev_init(&v->cdev, &vhost_vdpa_fops);
	v->cdev.owner = THIS_MODULE;

	r = cdev_device_add(&v->cdev, &v->dev);
	अगर (r)
		जाओ err;

	init_completion(&v->completion);
	vdpa_set_drvdata(vdpa, v);

	वापस 0;

err:
	put_device(&v->dev);
	वापस r;
पूर्ण

अटल व्योम vhost_vdpa_हटाओ(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा vhost_vdpa *v = vdpa_get_drvdata(vdpa);
	पूर्णांक खोलोed;

	cdev_device_del(&v->cdev, &v->dev);

	करो अणु
		खोलोed = atomic_cmpxchg(&v->खोलोed, 0, 1);
		अगर (!खोलोed)
			अवरोध;
		रुको_क्रम_completion(&v->completion);
	पूर्ण जबतक (1);

	put_device(&v->dev);
पूर्ण

अटल काष्ठा vdpa_driver vhost_vdpa_driver = अणु
	.driver = अणु
		.name	= "vhost_vdpa",
	पूर्ण,
	.probe	= vhost_vdpa_probe,
	.हटाओ	= vhost_vdpa_हटाओ,
पूर्ण;

अटल पूर्णांक __init vhost_vdpa_init(व्योम)
अणु
	पूर्णांक r;

	r = alloc_chrdev_region(&vhost_vdpa_major, 0, VHOST_VDPA_DEV_MAX,
				"vhost-vdpa");
	अगर (r)
		जाओ err_alloc_chrdev;

	r = vdpa_रेजिस्टर_driver(&vhost_vdpa_driver);
	अगर (r)
		जाओ err_vdpa_रेजिस्टर_driver;

	वापस 0;

err_vdpa_रेजिस्टर_driver:
	unरेजिस्टर_chrdev_region(vhost_vdpa_major, VHOST_VDPA_DEV_MAX);
err_alloc_chrdev:
	वापस r;
पूर्ण
module_init(vhost_vdpa_init);

अटल व्योम __निकास vhost_vdpa_निकास(व्योम)
अणु
	vdpa_unरेजिस्टर_driver(&vhost_vdpa_driver);
	unरेजिस्टर_chrdev_region(vhost_vdpa_major, VHOST_VDPA_DEV_MAX);
पूर्ण
module_निकास(vhost_vdpa_निकास);

MODULE_VERSION("0.0.1");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("vDPA-based vhost backend for virtio");
