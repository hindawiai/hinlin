<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2009 Red Hat, Inc.
 * Copyright (C) 2006 Rusty Russell IBM Corporation
 *
 * Author: Michael S. Tsirkin <mst@redhat.com>
 *
 * Inspiration, some code, and most witty comments come from
 * Documentation/भव/lguest/lguest.c, by Rusty Russell
 *
 * Generic code क्रम virtio server in host kernel.
 */

#समावेश <linux/eventfd.h>
#समावेश <linux/vhost.h>
#समावेश <linux/uपन.स>
#समावेश <linux/mm.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/file.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/module.h>
#समावेश <linux/sort.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/पूर्णांकerval_tree_generic.h>
#समावेश <linux/nospec.h>
#समावेश <linux/kcov.h>

#समावेश "vhost.h"

अटल uलघु max_mem_regions = 64;
module_param(max_mem_regions, uलघु, 0444);
MODULE_PARM_DESC(max_mem_regions,
	"Maximum number of memory regions in memory map. (default: 64)");
अटल पूर्णांक max_iotlb_entries = 2048;
module_param(max_iotlb_entries, पूर्णांक, 0444);
MODULE_PARM_DESC(max_iotlb_entries,
	"Maximum number of iotlb entries. (default: 2048)");

क्रमागत अणु
	VHOST_MEMORY_F_LOG = 0x1,
पूर्ण;

#घोषणा vhost_used_event(vq) ((__virtio16 __user *)&vq->avail->ring[vq->num])
#घोषणा vhost_avail_event(vq) ((__virtio16 __user *)&vq->used->ring[vq->num])

#अगर_घोषित CONFIG_VHOST_CROSS_ENDIAN_LEGACY
अटल व्योम vhost_disable_cross_endian(काष्ठा vhost_virtqueue *vq)
अणु
	vq->user_be = !virtio_legacy_is_little_endian();
पूर्ण

अटल व्योम vhost_enable_cross_endian_big(काष्ठा vhost_virtqueue *vq)
अणु
	vq->user_be = true;
पूर्ण

अटल व्योम vhost_enable_cross_endian_little(काष्ठा vhost_virtqueue *vq)
अणु
	vq->user_be = false;
पूर्ण

अटल दीर्घ vhost_set_vring_endian(काष्ठा vhost_virtqueue *vq, पूर्णांक __user *argp)
अणु
	काष्ठा vhost_vring_state s;

	अगर (vq->निजी_data)
		वापस -EBUSY;

	अगर (copy_from_user(&s, argp, माप(s)))
		वापस -EFAULT;

	अगर (s.num != VHOST_VRING_LITTLE_ENDIAN &&
	    s.num != VHOST_VRING_BIG_ENDIAN)
		वापस -EINVAL;

	अगर (s.num == VHOST_VRING_BIG_ENDIAN)
		vhost_enable_cross_endian_big(vq);
	अन्यथा
		vhost_enable_cross_endian_little(vq);

	वापस 0;
पूर्ण

अटल दीर्घ vhost_get_vring_endian(काष्ठा vhost_virtqueue *vq, u32 idx,
				   पूर्णांक __user *argp)
अणु
	काष्ठा vhost_vring_state s = अणु
		.index = idx,
		.num = vq->user_be
	पूर्ण;

	अगर (copy_to_user(argp, &s, माप(s)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल व्योम vhost_init_is_le(काष्ठा vhost_virtqueue *vq)
अणु
	/* Note क्रम legacy virtio: user_be is initialized at reset समय
	 * according to the host endianness. If userspace करोes not set an
	 * explicit endianness, the शेष behavior is native endian, as
	 * expected by legacy virtio.
	 */
	vq->is_le = vhost_has_feature(vq, VIRTIO_F_VERSION_1) || !vq->user_be;
पूर्ण
#अन्यथा
अटल व्योम vhost_disable_cross_endian(काष्ठा vhost_virtqueue *vq)
अणु
पूर्ण

अटल दीर्घ vhost_set_vring_endian(काष्ठा vhost_virtqueue *vq, पूर्णांक __user *argp)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

अटल दीर्घ vhost_get_vring_endian(काष्ठा vhost_virtqueue *vq, u32 idx,
				   पूर्णांक __user *argp)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

अटल व्योम vhost_init_is_le(काष्ठा vhost_virtqueue *vq)
अणु
	vq->is_le = vhost_has_feature(vq, VIRTIO_F_VERSION_1)
		|| virtio_legacy_is_little_endian();
पूर्ण
#पूर्ण_अगर /* CONFIG_VHOST_CROSS_ENDIAN_LEGACY */

अटल व्योम vhost_reset_is_le(काष्ठा vhost_virtqueue *vq)
अणु
	vhost_init_is_le(vq);
पूर्ण

काष्ठा vhost_flush_काष्ठा अणु
	काष्ठा vhost_work work;
	काष्ठा completion रुको_event;
पूर्ण;

अटल व्योम vhost_flush_work(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_flush_काष्ठा *s;

	s = container_of(work, काष्ठा vhost_flush_काष्ठा, work);
	complete(&s->रुको_event);
पूर्ण

अटल व्योम vhost_poll_func(काष्ठा file *file, रुको_queue_head_t *wqh,
			    poll_table *pt)
अणु
	काष्ठा vhost_poll *poll;

	poll = container_of(pt, काष्ठा vhost_poll, table);
	poll->wqh = wqh;
	add_रुको_queue(wqh, &poll->रुको);
पूर्ण

अटल पूर्णांक vhost_poll_wakeup(रुको_queue_entry_t *रुको, अचिन्हित mode, पूर्णांक sync,
			     व्योम *key)
अणु
	काष्ठा vhost_poll *poll = container_of(रुको, काष्ठा vhost_poll, रुको);
	काष्ठा vhost_work *work = &poll->work;

	अगर (!(key_to_poll(key) & poll->mask))
		वापस 0;

	अगर (!poll->dev->use_worker)
		work->fn(work);
	अन्यथा
		vhost_poll_queue(poll);

	वापस 0;
पूर्ण

व्योम vhost_work_init(काष्ठा vhost_work *work, vhost_work_fn_t fn)
अणु
	clear_bit(VHOST_WORK_QUEUED, &work->flags);
	work->fn = fn;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_work_init);

/* Init poll काष्ठाure */
व्योम vhost_poll_init(काष्ठा vhost_poll *poll, vhost_work_fn_t fn,
		     __poll_t mask, काष्ठा vhost_dev *dev)
अणु
	init_रुकोqueue_func_entry(&poll->रुको, vhost_poll_wakeup);
	init_poll_funcptr(&poll->table, vhost_poll_func);
	poll->mask = mask;
	poll->dev = dev;
	poll->wqh = शून्य;

	vhost_work_init(&poll->work, fn);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_poll_init);

/* Start polling a file. We add ourselves to file's रुको queue. The caller must
 * keep a reference to a file until after vhost_poll_stop is called. */
पूर्णांक vhost_poll_start(काष्ठा vhost_poll *poll, काष्ठा file *file)
अणु
	__poll_t mask;

	अगर (poll->wqh)
		वापस 0;

	mask = vfs_poll(file, &poll->table);
	अगर (mask)
		vhost_poll_wakeup(&poll->रुको, 0, 0, poll_to_key(mask));
	अगर (mask & EPOLLERR) अणु
		vhost_poll_stop(poll);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_poll_start);

/* Stop polling a file. After this function वापसs, it becomes safe to drop the
 * file reference. You must also flush afterwards. */
व्योम vhost_poll_stop(काष्ठा vhost_poll *poll)
अणु
	अगर (poll->wqh) अणु
		हटाओ_रुको_queue(poll->wqh, &poll->रुको);
		poll->wqh = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vhost_poll_stop);

व्योम vhost_work_flush(काष्ठा vhost_dev *dev, काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_flush_काष्ठा flush;

	अगर (dev->worker) अणु
		init_completion(&flush.रुको_event);
		vhost_work_init(&flush.work, vhost_flush_work);

		vhost_work_queue(dev, &flush.work);
		रुको_क्रम_completion(&flush.रुको_event);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vhost_work_flush);

/* Flush any work that has been scheduled. When calling this, करोn't hold any
 * locks that are also used by the callback. */
व्योम vhost_poll_flush(काष्ठा vhost_poll *poll)
अणु
	vhost_work_flush(poll->dev, &poll->work);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_poll_flush);

व्योम vhost_work_queue(काष्ठा vhost_dev *dev, काष्ठा vhost_work *work)
अणु
	अगर (!dev->worker)
		वापस;

	अगर (!test_and_set_bit(VHOST_WORK_QUEUED, &work->flags)) अणु
		/* We can only add the work to the list after we're
		 * sure it was not in the list.
		 * test_and_set_bit() implies a memory barrier.
		 */
		llist_add(&work->node, &dev->work_list);
		wake_up_process(dev->worker);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vhost_work_queue);

/* A lockless hपूर्णांक क्रम busy polling code to निकास the loop */
bool vhost_has_work(काष्ठा vhost_dev *dev)
अणु
	वापस !llist_empty(&dev->work_list);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_has_work);

व्योम vhost_poll_queue(काष्ठा vhost_poll *poll)
अणु
	vhost_work_queue(poll->dev, &poll->work);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_poll_queue);

अटल व्योम __vhost_vq_meta_reset(काष्ठा vhost_virtqueue *vq)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < VHOST_NUM_ADDRS; j++)
		vq->meta_iotlb[j] = शून्य;
पूर्ण

अटल व्योम vhost_vq_meta_reset(काष्ठा vhost_dev *d)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < d->nvqs; ++i)
		__vhost_vq_meta_reset(d->vqs[i]);
पूर्ण

अटल व्योम vhost_vring_call_reset(काष्ठा vhost_vring_call *call_ctx)
अणु
	call_ctx->ctx = शून्य;
	स_रखो(&call_ctx->producer, 0x0, माप(काष्ठा irq_bypass_producer));
पूर्ण

bool vhost_vq_is_setup(काष्ठा vhost_virtqueue *vq)
अणु
	वापस vq->avail && vq->desc && vq->used && vhost_vq_access_ok(vq);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_vq_is_setup);

अटल व्योम vhost_vq_reset(काष्ठा vhost_dev *dev,
			   काष्ठा vhost_virtqueue *vq)
अणु
	vq->num = 1;
	vq->desc = शून्य;
	vq->avail = शून्य;
	vq->used = शून्य;
	vq->last_avail_idx = 0;
	vq->avail_idx = 0;
	vq->last_used_idx = 0;
	vq->संकेतled_used = 0;
	vq->संकेतled_used_valid = false;
	vq->used_flags = 0;
	vq->log_used = false;
	vq->log_addr = -1ull;
	vq->निजी_data = शून्य;
	vq->acked_features = 0;
	vq->acked_backend_features = 0;
	vq->log_base = शून्य;
	vq->error_ctx = शून्य;
	vq->kick = शून्य;
	vq->log_ctx = शून्य;
	vhost_disable_cross_endian(vq);
	vhost_reset_is_le(vq);
	vq->busyloop_समयout = 0;
	vq->umem = शून्य;
	vq->iotlb = शून्य;
	vhost_vring_call_reset(&vq->call_ctx);
	__vhost_vq_meta_reset(vq);
पूर्ण

अटल पूर्णांक vhost_worker(व्योम *data)
अणु
	काष्ठा vhost_dev *dev = data;
	काष्ठा vhost_work *work, *work_next;
	काष्ठा llist_node *node;

	kthपढ़ो_use_mm(dev->mm);

	क्रम (;;) अणु
		/* mb paired w/ kthपढ़ो_stop */
		set_current_state(TASK_INTERRUPTIBLE);

		अगर (kthपढ़ो_should_stop()) अणु
			__set_current_state(TASK_RUNNING);
			अवरोध;
		पूर्ण

		node = llist_del_all(&dev->work_list);
		अगर (!node)
			schedule();

		node = llist_reverse_order(node);
		/* make sure flag is seen after deletion */
		smp_wmb();
		llist_क्रम_each_entry_safe(work, work_next, node, node) अणु
			clear_bit(VHOST_WORK_QUEUED, &work->flags);
			__set_current_state(TASK_RUNNING);
			kcov_remote_start_common(dev->kcov_handle);
			work->fn(work);
			kcov_remote_stop();
			अगर (need_resched())
				schedule();
		पूर्ण
	पूर्ण
	kthपढ़ो_unuse_mm(dev->mm);
	वापस 0;
पूर्ण

अटल व्योम vhost_vq_मुक्त_iovecs(काष्ठा vhost_virtqueue *vq)
अणु
	kमुक्त(vq->indirect);
	vq->indirect = शून्य;
	kमुक्त(vq->log);
	vq->log = शून्य;
	kमुक्त(vq->heads);
	vq->heads = शून्य;
पूर्ण

/* Helper to allocate iovec buffers क्रम all vqs. */
अटल दीर्घ vhost_dev_alloc_iovecs(काष्ठा vhost_dev *dev)
अणु
	काष्ठा vhost_virtqueue *vq;
	पूर्णांक i;

	क्रम (i = 0; i < dev->nvqs; ++i) अणु
		vq = dev->vqs[i];
		vq->indirect = kदो_स्मृति_array(UIO_MAXIOV,
					     माप(*vq->indirect),
					     GFP_KERNEL);
		vq->log = kदो_स्मृति_array(dev->iov_limit, माप(*vq->log),
					GFP_KERNEL);
		vq->heads = kदो_स्मृति_array(dev->iov_limit, माप(*vq->heads),
					  GFP_KERNEL);
		अगर (!vq->indirect || !vq->log || !vq->heads)
			जाओ err_nomem;
	पूर्ण
	वापस 0;

err_nomem:
	क्रम (; i >= 0; --i)
		vhost_vq_मुक्त_iovecs(dev->vqs[i]);
	वापस -ENOMEM;
पूर्ण

अटल व्योम vhost_dev_मुक्त_iovecs(काष्ठा vhost_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev->nvqs; ++i)
		vhost_vq_मुक्त_iovecs(dev->vqs[i]);
पूर्ण

bool vhost_exceeds_weight(काष्ठा vhost_virtqueue *vq,
			  पूर्णांक pkts, पूर्णांक total_len)
अणु
	काष्ठा vhost_dev *dev = vq->dev;

	अगर ((dev->byte_weight && total_len >= dev->byte_weight) ||
	    pkts >= dev->weight) अणु
		vhost_poll_queue(&vq->poll);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_exceeds_weight);

अटल माप_प्रकार vhost_get_avail_size(काष्ठा vhost_virtqueue *vq,
				   अचिन्हित पूर्णांक num)
अणु
	माप_प्रकार event __maybe_unused =
	       vhost_has_feature(vq, VIRTIO_RING_F_EVENT_IDX) ? 2 : 0;

	वापस माप(*vq->avail) +
	       माप(*vq->avail->ring) * num + event;
पूर्ण

अटल माप_प्रकार vhost_get_used_size(काष्ठा vhost_virtqueue *vq,
				  अचिन्हित पूर्णांक num)
अणु
	माप_प्रकार event __maybe_unused =
	       vhost_has_feature(vq, VIRTIO_RING_F_EVENT_IDX) ? 2 : 0;

	वापस माप(*vq->used) +
	       माप(*vq->used->ring) * num + event;
पूर्ण

अटल माप_प्रकार vhost_get_desc_size(काष्ठा vhost_virtqueue *vq,
				  अचिन्हित पूर्णांक num)
अणु
	वापस माप(*vq->desc) * num;
पूर्ण

व्योम vhost_dev_init(काष्ठा vhost_dev *dev,
		    काष्ठा vhost_virtqueue **vqs, पूर्णांक nvqs,
		    पूर्णांक iov_limit, पूर्णांक weight, पूर्णांक byte_weight,
		    bool use_worker,
		    पूर्णांक (*msg_handler)(काष्ठा vhost_dev *dev,
				       काष्ठा vhost_iotlb_msg *msg))
अणु
	काष्ठा vhost_virtqueue *vq;
	पूर्णांक i;

	dev->vqs = vqs;
	dev->nvqs = nvqs;
	mutex_init(&dev->mutex);
	dev->log_ctx = शून्य;
	dev->umem = शून्य;
	dev->iotlb = शून्य;
	dev->mm = शून्य;
	dev->worker = शून्य;
	dev->iov_limit = iov_limit;
	dev->weight = weight;
	dev->byte_weight = byte_weight;
	dev->use_worker = use_worker;
	dev->msg_handler = msg_handler;
	init_llist_head(&dev->work_list);
	init_रुकोqueue_head(&dev->रुको);
	INIT_LIST_HEAD(&dev->पढ़ो_list);
	INIT_LIST_HEAD(&dev->pending_list);
	spin_lock_init(&dev->iotlb_lock);


	क्रम (i = 0; i < dev->nvqs; ++i) अणु
		vq = dev->vqs[i];
		vq->log = शून्य;
		vq->indirect = शून्य;
		vq->heads = शून्य;
		vq->dev = dev;
		mutex_init(&vq->mutex);
		vhost_vq_reset(dev, vq);
		अगर (vq->handle_kick)
			vhost_poll_init(&vq->poll, vq->handle_kick,
					EPOLLIN, dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vhost_dev_init);

/* Caller should have device mutex */
दीर्घ vhost_dev_check_owner(काष्ठा vhost_dev *dev)
अणु
	/* Are you the owner? If not, I करोn't think you mean to करो that */
	वापस dev->mm == current->mm ? 0 : -EPERM;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_dev_check_owner);

काष्ठा vhost_attach_cgroups_काष्ठा अणु
	काष्ठा vhost_work work;
	काष्ठा task_काष्ठा *owner;
	पूर्णांक ret;
पूर्ण;

अटल व्योम vhost_attach_cgroups_work(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_attach_cgroups_काष्ठा *s;

	s = container_of(work, काष्ठा vhost_attach_cgroups_काष्ठा, work);
	s->ret = cgroup_attach_task_all(s->owner, current);
पूर्ण

अटल पूर्णांक vhost_attach_cgroups(काष्ठा vhost_dev *dev)
अणु
	काष्ठा vhost_attach_cgroups_काष्ठा attach;

	attach.owner = current;
	vhost_work_init(&attach.work, vhost_attach_cgroups_work);
	vhost_work_queue(dev, &attach.work);
	vhost_work_flush(dev, &attach.work);
	वापस attach.ret;
पूर्ण

/* Caller should have device mutex */
bool vhost_dev_has_owner(काष्ठा vhost_dev *dev)
अणु
	वापस dev->mm;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_dev_has_owner);

अटल व्योम vhost_attach_mm(काष्ठा vhost_dev *dev)
अणु
	/* No owner, become one */
	अगर (dev->use_worker) अणु
		dev->mm = get_task_mm(current);
	पूर्ण अन्यथा अणु
		/* vDPA device करोes not use worker thead, so there's
		 * no need to hold the address space क्रम mm. This help
		 * to aव्योम deadlock in the हाल of mmap() which may
		 * held the refcnt of the file and depends on release
		 * method to हटाओ vma.
		 */
		dev->mm = current->mm;
		mmgrab(dev->mm);
	पूर्ण
पूर्ण

अटल व्योम vhost_detach_mm(काष्ठा vhost_dev *dev)
अणु
	अगर (!dev->mm)
		वापस;

	अगर (dev->use_worker)
		mmput(dev->mm);
	अन्यथा
		mmdrop(dev->mm);

	dev->mm = शून्य;
पूर्ण

/* Caller should have device mutex */
दीर्घ vhost_dev_set_owner(काष्ठा vhost_dev *dev)
अणु
	काष्ठा task_काष्ठा *worker;
	पूर्णांक err;

	/* Is there an owner alपढ़ोy? */
	अगर (vhost_dev_has_owner(dev)) अणु
		err = -EBUSY;
		जाओ err_mm;
	पूर्ण

	vhost_attach_mm(dev);

	dev->kcov_handle = kcov_common_handle();
	अगर (dev->use_worker) अणु
		worker = kthपढ़ो_create(vhost_worker, dev,
					"vhost-%d", current->pid);
		अगर (IS_ERR(worker)) अणु
			err = PTR_ERR(worker);
			जाओ err_worker;
		पूर्ण

		dev->worker = worker;
		wake_up_process(worker); /* aव्योम contributing to loadavg */

		err = vhost_attach_cgroups(dev);
		अगर (err)
			जाओ err_cgroup;
	पूर्ण

	err = vhost_dev_alloc_iovecs(dev);
	अगर (err)
		जाओ err_cgroup;

	वापस 0;
err_cgroup:
	अगर (dev->worker) अणु
		kthपढ़ो_stop(dev->worker);
		dev->worker = शून्य;
	पूर्ण
err_worker:
	vhost_detach_mm(dev);
	dev->kcov_handle = 0;
err_mm:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_dev_set_owner);

अटल काष्ठा vhost_iotlb *iotlb_alloc(व्योम)
अणु
	वापस vhost_iotlb_alloc(max_iotlb_entries,
				 VHOST_IOTLB_FLAG_RETIRE);
पूर्ण

काष्ठा vhost_iotlb *vhost_dev_reset_owner_prepare(व्योम)
अणु
	वापस iotlb_alloc();
पूर्ण
EXPORT_SYMBOL_GPL(vhost_dev_reset_owner_prepare);

/* Caller should have device mutex */
व्योम vhost_dev_reset_owner(काष्ठा vhost_dev *dev, काष्ठा vhost_iotlb *umem)
अणु
	पूर्णांक i;

	vhost_dev_cleanup(dev);

	dev->umem = umem;
	/* We करोn't need VQ locks below since vhost_dev_cleanup makes sure
	 * VQs aren't running.
	 */
	क्रम (i = 0; i < dev->nvqs; ++i)
		dev->vqs[i]->umem = umem;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_dev_reset_owner);

व्योम vhost_dev_stop(काष्ठा vhost_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev->nvqs; ++i) अणु
		अगर (dev->vqs[i]->kick && dev->vqs[i]->handle_kick) अणु
			vhost_poll_stop(&dev->vqs[i]->poll);
			vhost_poll_flush(&dev->vqs[i]->poll);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vhost_dev_stop);

अटल व्योम vhost_clear_msg(काष्ठा vhost_dev *dev)
अणु
	काष्ठा vhost_msg_node *node, *n;

	spin_lock(&dev->iotlb_lock);

	list_क्रम_each_entry_safe(node, n, &dev->पढ़ो_list, node) अणु
		list_del(&node->node);
		kमुक्त(node);
	पूर्ण

	list_क्रम_each_entry_safe(node, n, &dev->pending_list, node) अणु
		list_del(&node->node);
		kमुक्त(node);
	पूर्ण

	spin_unlock(&dev->iotlb_lock);
पूर्ण

व्योम vhost_dev_cleanup(काष्ठा vhost_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev->nvqs; ++i) अणु
		अगर (dev->vqs[i]->error_ctx)
			eventfd_ctx_put(dev->vqs[i]->error_ctx);
		अगर (dev->vqs[i]->kick)
			fput(dev->vqs[i]->kick);
		अगर (dev->vqs[i]->call_ctx.ctx)
			eventfd_ctx_put(dev->vqs[i]->call_ctx.ctx);
		vhost_vq_reset(dev, dev->vqs[i]);
	पूर्ण
	vhost_dev_मुक्त_iovecs(dev);
	अगर (dev->log_ctx)
		eventfd_ctx_put(dev->log_ctx);
	dev->log_ctx = शून्य;
	/* No one will access memory at this poपूर्णांक */
	vhost_iotlb_मुक्त(dev->umem);
	dev->umem = शून्य;
	vhost_iotlb_मुक्त(dev->iotlb);
	dev->iotlb = शून्य;
	vhost_clear_msg(dev);
	wake_up_पूर्णांकerruptible_poll(&dev->रुको, EPOLLIN | EPOLLRDNORM);
	WARN_ON(!llist_empty(&dev->work_list));
	अगर (dev->worker) अणु
		kthपढ़ो_stop(dev->worker);
		dev->worker = शून्य;
		dev->kcov_handle = 0;
	पूर्ण
	vhost_detach_mm(dev);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_dev_cleanup);

अटल bool log_access_ok(व्योम __user *log_base, u64 addr, अचिन्हित दीर्घ sz)
अणु
	u64 a = addr / VHOST_PAGE_SIZE / 8;

	/* Make sure 64 bit math will not overflow. */
	अगर (a > अच_दीर्घ_उच्च - (अचिन्हित दीर्घ)log_base ||
	    a + (अचिन्हित दीर्घ)log_base > अच_दीर्घ_उच्च)
		वापस false;

	वापस access_ok(log_base + a,
			 (sz + VHOST_PAGE_SIZE * 8 - 1) / VHOST_PAGE_SIZE / 8);
पूर्ण

अटल bool vhost_overflow(u64 uaddr, u64 size)
अणु
	/* Make sure 64 bit math will not overflow. */
	वापस uaddr > अच_दीर्घ_उच्च || size > अच_दीर्घ_उच्च || uaddr > अच_दीर्घ_उच्च - size;
पूर्ण

/* Caller should have vq mutex and device mutex. */
अटल bool vq_memory_access_ok(व्योम __user *log_base, काष्ठा vhost_iotlb *umem,
				पूर्णांक log_all)
अणु
	काष्ठा vhost_iotlb_map *map;

	अगर (!umem)
		वापस false;

	list_क्रम_each_entry(map, &umem->list, link) अणु
		अचिन्हित दीर्घ a = map->addr;

		अगर (vhost_overflow(map->addr, map->size))
			वापस false;


		अगर (!access_ok((व्योम __user *)a, map->size))
			वापस false;
		अन्यथा अगर (log_all && !log_access_ok(log_base,
						   map->start,
						   map->size))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत व्योम __user *vhost_vq_meta_fetch(काष्ठा vhost_virtqueue *vq,
					       u64 addr, अचिन्हित पूर्णांक size,
					       पूर्णांक type)
अणु
	स्थिर काष्ठा vhost_iotlb_map *map = vq->meta_iotlb[type];

	अगर (!map)
		वापस शून्य;

	वापस (व्योम __user *)(uपूर्णांकptr_t)(map->addr + addr - map->start);
पूर्ण

/* Can we चयन to this memory table? */
/* Caller should have device mutex but not vq mutex */
अटल bool memory_access_ok(काष्ठा vhost_dev *d, काष्ठा vhost_iotlb *umem,
			     पूर्णांक log_all)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < d->nvqs; ++i) अणु
		bool ok;
		bool log;

		mutex_lock(&d->vqs[i]->mutex);
		log = log_all || vhost_has_feature(d->vqs[i], VHOST_F_LOG_ALL);
		/* If ring is inactive, will check when it's enabled. */
		अगर (d->vqs[i]->निजी_data)
			ok = vq_memory_access_ok(d->vqs[i]->log_base,
						 umem, log);
		अन्यथा
			ok = true;
		mutex_unlock(&d->vqs[i]->mutex);
		अगर (!ok)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक translate_desc(काष्ठा vhost_virtqueue *vq, u64 addr, u32 len,
			  काष्ठा iovec iov[], पूर्णांक iov_size, पूर्णांक access);

अटल पूर्णांक vhost_copy_to_user(काष्ठा vhost_virtqueue *vq, व्योम __user *to,
			      स्थिर व्योम *from, अचिन्हित size)
अणु
	पूर्णांक ret;

	अगर (!vq->iotlb)
		वापस __copy_to_user(to, from, size);
	अन्यथा अणु
		/* This function should be called after iotlb
		 * prefetch, which means we're sure that all vq
		 * could be access through iotlb. So -EAGAIN should
		 * not happen in this हाल.
		 */
		काष्ठा iov_iter t;
		व्योम __user *uaddr = vhost_vq_meta_fetch(vq,
				     (u64)(uपूर्णांकptr_t)to, size,
				     VHOST_ADDR_USED);

		अगर (uaddr)
			वापस __copy_to_user(uaddr, from, size);

		ret = translate_desc(vq, (u64)(uपूर्णांकptr_t)to, size, vq->iotlb_iov,
				     ARRAY_SIZE(vq->iotlb_iov),
				     VHOST_ACCESS_WO);
		अगर (ret < 0)
			जाओ out;
		iov_iter_init(&t, WRITE, vq->iotlb_iov, ret, size);
		ret = copy_to_iter(from, size, &t);
		अगर (ret == size)
			ret = 0;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक vhost_copy_from_user(काष्ठा vhost_virtqueue *vq, व्योम *to,
				व्योम __user *from, अचिन्हित size)
अणु
	पूर्णांक ret;

	अगर (!vq->iotlb)
		वापस __copy_from_user(to, from, size);
	अन्यथा अणु
		/* This function should be called after iotlb
		 * prefetch, which means we're sure that vq
		 * could be access through iotlb. So -EAGAIN should
		 * not happen in this हाल.
		 */
		व्योम __user *uaddr = vhost_vq_meta_fetch(vq,
				     (u64)(uपूर्णांकptr_t)from, size,
				     VHOST_ADDR_DESC);
		काष्ठा iov_iter f;

		अगर (uaddr)
			वापस __copy_from_user(to, uaddr, size);

		ret = translate_desc(vq, (u64)(uपूर्णांकptr_t)from, size, vq->iotlb_iov,
				     ARRAY_SIZE(vq->iotlb_iov),
				     VHOST_ACCESS_RO);
		अगर (ret < 0) अणु
			vq_err(vq, "IOTLB translation failure: uaddr "
			       "%p size 0x%llx\n", from,
			       (अचिन्हित दीर्घ दीर्घ) size);
			जाओ out;
		पूर्ण
		iov_iter_init(&f, READ, vq->iotlb_iov, ret, size);
		ret = copy_from_iter(to, size, &f);
		अगर (ret == size)
			ret = 0;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम __user *__vhost_get_user_slow(काष्ठा vhost_virtqueue *vq,
					  व्योम __user *addr, अचिन्हित पूर्णांक size,
					  पूर्णांक type)
अणु
	पूर्णांक ret;

	ret = translate_desc(vq, (u64)(uपूर्णांकptr_t)addr, size, vq->iotlb_iov,
			     ARRAY_SIZE(vq->iotlb_iov),
			     VHOST_ACCESS_RO);
	अगर (ret < 0) अणु
		vq_err(vq, "IOTLB translation failure: uaddr "
			"%p size 0x%llx\n", addr,
			(अचिन्हित दीर्घ दीर्घ) size);
		वापस शून्य;
	पूर्ण

	अगर (ret != 1 || vq->iotlb_iov[0].iov_len != size) अणु
		vq_err(vq, "Non atomic userspace memory access: uaddr "
			"%p size 0x%llx\n", addr,
			(अचिन्हित दीर्घ दीर्घ) size);
		वापस शून्य;
	पूर्ण

	वापस vq->iotlb_iov[0].iov_base;
पूर्ण

/* This function should be called after iotlb
 * prefetch, which means we're sure that vq
 * could be access through iotlb. So -EAGAIN should
 * not happen in this हाल.
 */
अटल अंतरभूत व्योम __user *__vhost_get_user(काष्ठा vhost_virtqueue *vq,
					    व्योम __user *addr, अचिन्हित पूर्णांक size,
					    पूर्णांक type)
अणु
	व्योम __user *uaddr = vhost_vq_meta_fetch(vq,
			     (u64)(uपूर्णांकptr_t)addr, size, type);
	अगर (uaddr)
		वापस uaddr;

	वापस __vhost_get_user_slow(vq, addr, size, type);
पूर्ण

#घोषणा vhost_put_user(vq, x, ptr)		\
(अणु \
	पूर्णांक ret; \
	अगर (!vq->iotlb) अणु \
		ret = __put_user(x, ptr); \
	पूर्ण अन्यथा अणु \
		__typeof__(ptr) to = \
			(__typeof__(ptr)) __vhost_get_user(vq, ptr,	\
					  माप(*ptr), VHOST_ADDR_USED); \
		अगर (to != शून्य) \
			ret = __put_user(x, to); \
		अन्यथा \
			ret = -EFAULT;	\
	पूर्ण \
	ret; \
पूर्ण)

अटल अंतरभूत पूर्णांक vhost_put_avail_event(काष्ठा vhost_virtqueue *vq)
अणु
	वापस vhost_put_user(vq, cpu_to_vhost16(vq, vq->avail_idx),
			      vhost_avail_event(vq));
पूर्ण

अटल अंतरभूत पूर्णांक vhost_put_used(काष्ठा vhost_virtqueue *vq,
				 काष्ठा vring_used_elem *head, पूर्णांक idx,
				 पूर्णांक count)
अणु
	वापस vhost_copy_to_user(vq, vq->used->ring + idx, head,
				  count * माप(*head));
पूर्ण

अटल अंतरभूत पूर्णांक vhost_put_used_flags(काष्ठा vhost_virtqueue *vq)

अणु
	वापस vhost_put_user(vq, cpu_to_vhost16(vq, vq->used_flags),
			      &vq->used->flags);
पूर्ण

अटल अंतरभूत पूर्णांक vhost_put_used_idx(काष्ठा vhost_virtqueue *vq)

अणु
	वापस vhost_put_user(vq, cpu_to_vhost16(vq, vq->last_used_idx),
			      &vq->used->idx);
पूर्ण

#घोषणा vhost_get_user(vq, x, ptr, type)		\
(अणु \
	पूर्णांक ret; \
	अगर (!vq->iotlb) अणु \
		ret = __get_user(x, ptr); \
	पूर्ण अन्यथा अणु \
		__typeof__(ptr) from = \
			(__typeof__(ptr)) __vhost_get_user(vq, ptr, \
							   माप(*ptr), \
							   type); \
		अगर (from != शून्य) \
			ret = __get_user(x, from); \
		अन्यथा \
			ret = -EFAULT; \
	पूर्ण \
	ret; \
पूर्ण)

#घोषणा vhost_get_avail(vq, x, ptr) \
	vhost_get_user(vq, x, ptr, VHOST_ADDR_AVAIL)

#घोषणा vhost_get_used(vq, x, ptr) \
	vhost_get_user(vq, x, ptr, VHOST_ADDR_USED)

अटल व्योम vhost_dev_lock_vqs(काष्ठा vhost_dev *d)
अणु
	पूर्णांक i = 0;
	क्रम (i = 0; i < d->nvqs; ++i)
		mutex_lock_nested(&d->vqs[i]->mutex, i);
पूर्ण

अटल व्योम vhost_dev_unlock_vqs(काष्ठा vhost_dev *d)
अणु
	पूर्णांक i = 0;
	क्रम (i = 0; i < d->nvqs; ++i)
		mutex_unlock(&d->vqs[i]->mutex);
पूर्ण

अटल अंतरभूत पूर्णांक vhost_get_avail_idx(काष्ठा vhost_virtqueue *vq,
				      __virtio16 *idx)
अणु
	वापस vhost_get_avail(vq, *idx, &vq->avail->idx);
पूर्ण

अटल अंतरभूत पूर्णांक vhost_get_avail_head(काष्ठा vhost_virtqueue *vq,
				       __virtio16 *head, पूर्णांक idx)
अणु
	वापस vhost_get_avail(vq, *head,
			       &vq->avail->ring[idx & (vq->num - 1)]);
पूर्ण

अटल अंतरभूत पूर्णांक vhost_get_avail_flags(काष्ठा vhost_virtqueue *vq,
					__virtio16 *flags)
अणु
	वापस vhost_get_avail(vq, *flags, &vq->avail->flags);
पूर्ण

अटल अंतरभूत पूर्णांक vhost_get_used_event(काष्ठा vhost_virtqueue *vq,
				       __virtio16 *event)
अणु
	वापस vhost_get_avail(vq, *event, vhost_used_event(vq));
पूर्ण

अटल अंतरभूत पूर्णांक vhost_get_used_idx(काष्ठा vhost_virtqueue *vq,
				     __virtio16 *idx)
अणु
	वापस vhost_get_used(vq, *idx, &vq->used->idx);
पूर्ण

अटल अंतरभूत पूर्णांक vhost_get_desc(काष्ठा vhost_virtqueue *vq,
				 काष्ठा vring_desc *desc, पूर्णांक idx)
अणु
	वापस vhost_copy_from_user(vq, desc, vq->desc + idx, माप(*desc));
पूर्ण

अटल व्योम vhost_iotlb_notअगरy_vq(काष्ठा vhost_dev *d,
				  काष्ठा vhost_iotlb_msg *msg)
अणु
	काष्ठा vhost_msg_node *node, *n;

	spin_lock(&d->iotlb_lock);

	list_क्रम_each_entry_safe(node, n, &d->pending_list, node) अणु
		काष्ठा vhost_iotlb_msg *vq_msg = &node->msg.iotlb;
		अगर (msg->iova <= vq_msg->iova &&
		    msg->iova + msg->size - 1 >= vq_msg->iova &&
		    vq_msg->type == VHOST_IOTLB_MISS) अणु
			vhost_poll_queue(&node->vq->poll);
			list_del(&node->node);
			kमुक्त(node);
		पूर्ण
	पूर्ण

	spin_unlock(&d->iotlb_lock);
पूर्ण

अटल bool umem_access_ok(u64 uaddr, u64 size, पूर्णांक access)
अणु
	अचिन्हित दीर्घ a = uaddr;

	/* Make sure 64 bit math will not overflow. */
	अगर (vhost_overflow(uaddr, size))
		वापस false;

	अगर ((access & VHOST_ACCESS_RO) &&
	    !access_ok((व्योम __user *)a, size))
		वापस false;
	अगर ((access & VHOST_ACCESS_WO) &&
	    !access_ok((व्योम __user *)a, size))
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक vhost_process_iotlb_msg(काष्ठा vhost_dev *dev,
				   काष्ठा vhost_iotlb_msg *msg)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&dev->mutex);
	vhost_dev_lock_vqs(dev);
	चयन (msg->type) अणु
	हाल VHOST_IOTLB_UPDATE:
		अगर (!dev->iotlb) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (!umem_access_ok(msg->uaddr, msg->size, msg->perm)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		vhost_vq_meta_reset(dev);
		अगर (vhost_iotlb_add_range(dev->iotlb, msg->iova,
					  msg->iova + msg->size - 1,
					  msg->uaddr, msg->perm)) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		vhost_iotlb_notअगरy_vq(dev, msg);
		अवरोध;
	हाल VHOST_IOTLB_INVALIDATE:
		अगर (!dev->iotlb) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		vhost_vq_meta_reset(dev);
		vhost_iotlb_del_range(dev->iotlb, msg->iova,
				      msg->iova + msg->size - 1);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	vhost_dev_unlock_vqs(dev);
	mutex_unlock(&dev->mutex);

	वापस ret;
पूर्ण
sमाप_प्रकार vhost_chr_ग_लिखो_iter(काष्ठा vhost_dev *dev,
			     काष्ठा iov_iter *from)
अणु
	काष्ठा vhost_iotlb_msg msg;
	माप_प्रकार offset;
	पूर्णांक type, ret;

	ret = copy_from_iter(&type, माप(type), from);
	अगर (ret != माप(type)) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	चयन (type) अणु
	हाल VHOST_IOTLB_MSG:
		/* There maybe a hole after type क्रम V1 message type,
		 * so skip it here.
		 */
		offset = दुरत्व(काष्ठा vhost_msg, iotlb) - माप(पूर्णांक);
		अवरोध;
	हाल VHOST_IOTLB_MSG_V2:
		offset = माप(__u32);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	iov_iter_advance(from, offset);
	ret = copy_from_iter(&msg, माप(msg), from);
	अगर (ret != माप(msg)) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (dev->msg_handler)
		ret = dev->msg_handler(dev, &msg);
	अन्यथा
		ret = vhost_process_iotlb_msg(dev, &msg);
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ करोne;
	पूर्ण

	ret = (type == VHOST_IOTLB_MSG) ? माप(काष्ठा vhost_msg) :
	      माप(काष्ठा vhost_msg_v2);
करोne:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vhost_chr_ग_लिखो_iter);

__poll_t vhost_chr_poll(काष्ठा file *file, काष्ठा vhost_dev *dev,
			    poll_table *रुको)
अणु
	__poll_t mask = 0;

	poll_रुको(file, &dev->रुको, रुको);

	अगर (!list_empty(&dev->पढ़ो_list))
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण
EXPORT_SYMBOL(vhost_chr_poll);

sमाप_प्रकार vhost_chr_पढ़ो_iter(काष्ठा vhost_dev *dev, काष्ठा iov_iter *to,
			    पूर्णांक noblock)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा vhost_msg_node *node;
	sमाप_प्रकार ret = 0;
	अचिन्हित size = माप(काष्ठा vhost_msg);

	अगर (iov_iter_count(to) < size)
		वापस 0;

	जबतक (1) अणु
		अगर (!noblock)
			prepare_to_रुको(&dev->रुको, &रुको,
					TASK_INTERRUPTIBLE);

		node = vhost_dequeue_msg(dev, &dev->पढ़ो_list);
		अगर (node)
			अवरोध;
		अगर (noblock) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		अगर (!dev->iotlb) अणु
			ret = -EBADFD;
			अवरोध;
		पूर्ण

		schedule();
	पूर्ण

	अगर (!noblock)
		finish_रुको(&dev->रुको, &रुको);

	अगर (node) अणु
		काष्ठा vhost_iotlb_msg *msg;
		व्योम *start = &node->msg;

		चयन (node->msg.type) अणु
		हाल VHOST_IOTLB_MSG:
			size = माप(node->msg);
			msg = &node->msg.iotlb;
			अवरोध;
		हाल VHOST_IOTLB_MSG_V2:
			size = माप(node->msg_v2);
			msg = &node->msg_v2.iotlb;
			अवरोध;
		शेष:
			BUG();
			अवरोध;
		पूर्ण

		ret = copy_to_iter(start, size, to);
		अगर (ret != size || msg->type != VHOST_IOTLB_MISS) अणु
			kमुक्त(node);
			वापस ret;
		पूर्ण
		vhost_enqueue_msg(dev, &dev->pending_list, node);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_chr_पढ़ो_iter);

अटल पूर्णांक vhost_iotlb_miss(काष्ठा vhost_virtqueue *vq, u64 iova, पूर्णांक access)
अणु
	काष्ठा vhost_dev *dev = vq->dev;
	काष्ठा vhost_msg_node *node;
	काष्ठा vhost_iotlb_msg *msg;
	bool v2 = vhost_backend_has_feature(vq, VHOST_BACKEND_F_IOTLB_MSG_V2);

	node = vhost_new_msg(vq, v2 ? VHOST_IOTLB_MSG_V2 : VHOST_IOTLB_MSG);
	अगर (!node)
		वापस -ENOMEM;

	अगर (v2) अणु
		node->msg_v2.type = VHOST_IOTLB_MSG_V2;
		msg = &node->msg_v2.iotlb;
	पूर्ण अन्यथा अणु
		msg = &node->msg.iotlb;
	पूर्ण

	msg->type = VHOST_IOTLB_MISS;
	msg->iova = iova;
	msg->perm = access;

	vhost_enqueue_msg(dev, &dev->पढ़ो_list, node);

	वापस 0;
पूर्ण

अटल bool vq_access_ok(काष्ठा vhost_virtqueue *vq, अचिन्हित पूर्णांक num,
			 vring_desc_t __user *desc,
			 vring_avail_t __user *avail,
			 vring_used_t __user *used)

अणु
	/* If an IOTLB device is present, the vring addresses are
	 * GIOVAs. Access validation occurs at prefetch समय. */
	अगर (vq->iotlb)
		वापस true;

	वापस access_ok(desc, vhost_get_desc_size(vq, num)) &&
	       access_ok(avail, vhost_get_avail_size(vq, num)) &&
	       access_ok(used, vhost_get_used_size(vq, num));
पूर्ण

अटल व्योम vhost_vq_meta_update(काष्ठा vhost_virtqueue *vq,
				 स्थिर काष्ठा vhost_iotlb_map *map,
				 पूर्णांक type)
अणु
	पूर्णांक access = (type == VHOST_ADDR_USED) ?
		     VHOST_ACCESS_WO : VHOST_ACCESS_RO;

	अगर (likely(map->perm & access))
		vq->meta_iotlb[type] = map;
पूर्ण

अटल bool iotlb_access_ok(काष्ठा vhost_virtqueue *vq,
			    पूर्णांक access, u64 addr, u64 len, पूर्णांक type)
अणु
	स्थिर काष्ठा vhost_iotlb_map *map;
	काष्ठा vhost_iotlb *umem = vq->iotlb;
	u64 s = 0, size, orig_addr = addr, last = addr + len - 1;

	अगर (vhost_vq_meta_fetch(vq, addr, len, type))
		वापस true;

	जबतक (len > s) अणु
		map = vhost_iotlb_itree_first(umem, addr, last);
		अगर (map == शून्य || map->start > addr) अणु
			vhost_iotlb_miss(vq, addr, access);
			वापस false;
		पूर्ण अन्यथा अगर (!(map->perm & access)) अणु
			/* Report the possible access violation by
			 * request another translation from userspace.
			 */
			वापस false;
		पूर्ण

		size = map->size - addr + map->start;

		अगर (orig_addr == addr && size >= len)
			vhost_vq_meta_update(vq, map, type);

		s += size;
		addr += size;
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक vq_meta_prefetch(काष्ठा vhost_virtqueue *vq)
अणु
	अचिन्हित पूर्णांक num = vq->num;

	अगर (!vq->iotlb)
		वापस 1;

	वापस iotlb_access_ok(vq, VHOST_MAP_RO, (u64)(uपूर्णांकptr_t)vq->desc,
			       vhost_get_desc_size(vq, num), VHOST_ADDR_DESC) &&
	       iotlb_access_ok(vq, VHOST_MAP_RO, (u64)(uपूर्णांकptr_t)vq->avail,
			       vhost_get_avail_size(vq, num),
			       VHOST_ADDR_AVAIL) &&
	       iotlb_access_ok(vq, VHOST_MAP_WO, (u64)(uपूर्णांकptr_t)vq->used,
			       vhost_get_used_size(vq, num), VHOST_ADDR_USED);
पूर्ण
EXPORT_SYMBOL_GPL(vq_meta_prefetch);

/* Can we log ग_लिखोs? */
/* Caller should have device mutex but not vq mutex */
bool vhost_log_access_ok(काष्ठा vhost_dev *dev)
अणु
	वापस memory_access_ok(dev, dev->umem, 1);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_log_access_ok);

अटल bool vq_log_used_access_ok(काष्ठा vhost_virtqueue *vq,
				  व्योम __user *log_base,
				  bool log_used,
				  u64 log_addr)
अणु
	/* If an IOTLB device is present, log_addr is a GIOVA that
	 * will never be logged by log_used(). */
	अगर (vq->iotlb)
		वापस true;

	वापस !log_used || log_access_ok(log_base, log_addr,
					  vhost_get_used_size(vq, vq->num));
पूर्ण

/* Verअगरy access क्रम ग_लिखो logging. */
/* Caller should have vq mutex and device mutex */
अटल bool vq_log_access_ok(काष्ठा vhost_virtqueue *vq,
			     व्योम __user *log_base)
अणु
	वापस vq_memory_access_ok(log_base, vq->umem,
				   vhost_has_feature(vq, VHOST_F_LOG_ALL)) &&
		vq_log_used_access_ok(vq, log_base, vq->log_used, vq->log_addr);
पूर्ण

/* Can we start vq? */
/* Caller should have vq mutex and device mutex */
bool vhost_vq_access_ok(काष्ठा vhost_virtqueue *vq)
अणु
	अगर (!vq_log_access_ok(vq, vq->log_base))
		वापस false;

	वापस vq_access_ok(vq, vq->num, vq->desc, vq->avail, vq->used);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_vq_access_ok);

अटल दीर्घ vhost_set_memory(काष्ठा vhost_dev *d, काष्ठा vhost_memory __user *m)
अणु
	काष्ठा vhost_memory mem, *newmem;
	काष्ठा vhost_memory_region *region;
	काष्ठा vhost_iotlb *newumem, *oldumem;
	अचिन्हित दीर्घ size = दुरत्व(काष्ठा vhost_memory, regions);
	पूर्णांक i;

	अगर (copy_from_user(&mem, m, size))
		वापस -EFAULT;
	अगर (mem.padding)
		वापस -EOPNOTSUPP;
	अगर (mem.nregions > max_mem_regions)
		वापस -E2BIG;
	newmem = kvzalloc(काष्ठा_size(newmem, regions, mem.nregions),
			GFP_KERNEL);
	अगर (!newmem)
		वापस -ENOMEM;

	स_नकल(newmem, &mem, size);
	अगर (copy_from_user(newmem->regions, m->regions,
			   flex_array_size(newmem, regions, mem.nregions))) अणु
		kvमुक्त(newmem);
		वापस -EFAULT;
	पूर्ण

	newumem = iotlb_alloc();
	अगर (!newumem) अणु
		kvमुक्त(newmem);
		वापस -ENOMEM;
	पूर्ण

	क्रम (region = newmem->regions;
	     region < newmem->regions + mem.nregions;
	     region++) अणु
		अगर (vhost_iotlb_add_range(newumem,
					  region->guest_phys_addr,
					  region->guest_phys_addr +
					  region->memory_size - 1,
					  region->userspace_addr,
					  VHOST_MAP_RW))
			जाओ err;
	पूर्ण

	अगर (!memory_access_ok(d, newumem, 0))
		जाओ err;

	oldumem = d->umem;
	d->umem = newumem;

	/* All memory accesses are करोne under some VQ mutex. */
	क्रम (i = 0; i < d->nvqs; ++i) अणु
		mutex_lock(&d->vqs[i]->mutex);
		d->vqs[i]->umem = newumem;
		mutex_unlock(&d->vqs[i]->mutex);
	पूर्ण

	kvमुक्त(newmem);
	vhost_iotlb_मुक्त(oldumem);
	वापस 0;

err:
	vhost_iotlb_मुक्त(newumem);
	kvमुक्त(newmem);
	वापस -EFAULT;
पूर्ण

अटल दीर्घ vhost_vring_set_num(काष्ठा vhost_dev *d,
				काष्ठा vhost_virtqueue *vq,
				व्योम __user *argp)
अणु
	काष्ठा vhost_vring_state s;

	/* Resizing ring with an active backend?
	 * You करोn't want to करो that. */
	अगर (vq->निजी_data)
		वापस -EBUSY;

	अगर (copy_from_user(&s, argp, माप s))
		वापस -EFAULT;

	अगर (!s.num || s.num > 0xffff || (s.num & (s.num - 1)))
		वापस -EINVAL;
	vq->num = s.num;

	वापस 0;
पूर्ण

अटल दीर्घ vhost_vring_set_addr(काष्ठा vhost_dev *d,
				 काष्ठा vhost_virtqueue *vq,
				 व्योम __user *argp)
अणु
	काष्ठा vhost_vring_addr a;

	अगर (copy_from_user(&a, argp, माप a))
		वापस -EFAULT;
	अगर (a.flags & ~(0x1 << VHOST_VRING_F_LOG))
		वापस -EOPNOTSUPP;

	/* For 32bit, verअगरy that the top 32bits of the user
	   data are set to zero. */
	अगर ((u64)(अचिन्हित दीर्घ)a.desc_user_addr != a.desc_user_addr ||
	    (u64)(अचिन्हित दीर्घ)a.used_user_addr != a.used_user_addr ||
	    (u64)(अचिन्हित दीर्घ)a.avail_user_addr != a.avail_user_addr)
		वापस -EFAULT;

	/* Make sure it's safe to cast poपूर्णांकers to vring types. */
	BUILD_BUG_ON(__alignof__ *vq->avail > VRING_AVAIL_ALIGN_SIZE);
	BUILD_BUG_ON(__alignof__ *vq->used > VRING_USED_ALIGN_SIZE);
	अगर ((a.avail_user_addr & (VRING_AVAIL_ALIGN_SIZE - 1)) ||
	    (a.used_user_addr & (VRING_USED_ALIGN_SIZE - 1)) ||
	    (a.log_guest_addr & (VRING_USED_ALIGN_SIZE - 1)))
		वापस -EINVAL;

	/* We only verअगरy access here अगर backend is configured.
	 * If it is not, we करोn't as size might not have been setup.
	 * We will verअगरy when backend is configured. */
	अगर (vq->निजी_data) अणु
		अगर (!vq_access_ok(vq, vq->num,
			(व्योम __user *)(अचिन्हित दीर्घ)a.desc_user_addr,
			(व्योम __user *)(अचिन्हित दीर्घ)a.avail_user_addr,
			(व्योम __user *)(अचिन्हित दीर्घ)a.used_user_addr))
			वापस -EINVAL;

		/* Also validate log access क्रम used ring अगर enabled. */
		अगर (!vq_log_used_access_ok(vq, vq->log_base,
				a.flags & (0x1 << VHOST_VRING_F_LOG),
				a.log_guest_addr))
			वापस -EINVAL;
	पूर्ण

	vq->log_used = !!(a.flags & (0x1 << VHOST_VRING_F_LOG));
	vq->desc = (व्योम __user *)(अचिन्हित दीर्घ)a.desc_user_addr;
	vq->avail = (व्योम __user *)(अचिन्हित दीर्घ)a.avail_user_addr;
	vq->log_addr = a.log_guest_addr;
	vq->used = (व्योम __user *)(अचिन्हित दीर्घ)a.used_user_addr;

	वापस 0;
पूर्ण

अटल दीर्घ vhost_vring_set_num_addr(काष्ठा vhost_dev *d,
				     काष्ठा vhost_virtqueue *vq,
				     अचिन्हित पूर्णांक ioctl,
				     व्योम __user *argp)
अणु
	दीर्घ r;

	mutex_lock(&vq->mutex);

	चयन (ioctl) अणु
	हाल VHOST_SET_VRING_NUM:
		r = vhost_vring_set_num(d, vq, argp);
		अवरोध;
	हाल VHOST_SET_VRING_ADDR:
		r = vhost_vring_set_addr(d, vq, argp);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	mutex_unlock(&vq->mutex);

	वापस r;
पूर्ण
दीर्घ vhost_vring_ioctl(काष्ठा vhost_dev *d, अचिन्हित पूर्णांक ioctl, व्योम __user *argp)
अणु
	काष्ठा file *eventfp, *filep = शून्य;
	bool pollstart = false, pollstop = false;
	काष्ठा eventfd_ctx *ctx = शून्य;
	u32 __user *idxp = argp;
	काष्ठा vhost_virtqueue *vq;
	काष्ठा vhost_vring_state s;
	काष्ठा vhost_vring_file f;
	u32 idx;
	दीर्घ r;

	r = get_user(idx, idxp);
	अगर (r < 0)
		वापस r;
	अगर (idx >= d->nvqs)
		वापस -ENOBUFS;

	idx = array_index_nospec(idx, d->nvqs);
	vq = d->vqs[idx];

	अगर (ioctl == VHOST_SET_VRING_NUM ||
	    ioctl == VHOST_SET_VRING_ADDR) अणु
		वापस vhost_vring_set_num_addr(d, vq, ioctl, argp);
	पूर्ण

	mutex_lock(&vq->mutex);

	चयन (ioctl) अणु
	हाल VHOST_SET_VRING_BASE:
		/* Moving base with an active backend?
		 * You करोn't want to करो that. */
		अगर (vq->निजी_data) अणु
			r = -EBUSY;
			अवरोध;
		पूर्ण
		अगर (copy_from_user(&s, argp, माप s)) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (s.num > 0xffff) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण
		vq->last_avail_idx = s.num;
		/* Forget the cached index value. */
		vq->avail_idx = vq->last_avail_idx;
		अवरोध;
	हाल VHOST_GET_VRING_BASE:
		s.index = idx;
		s.num = vq->last_avail_idx;
		अगर (copy_to_user(argp, &s, माप s))
			r = -EFAULT;
		अवरोध;
	हाल VHOST_SET_VRING_KICK:
		अगर (copy_from_user(&f, argp, माप f)) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		eventfp = f.fd == VHOST_खाता_UNBIND ? शून्य : eventfd_fget(f.fd);
		अगर (IS_ERR(eventfp)) अणु
			r = PTR_ERR(eventfp);
			अवरोध;
		पूर्ण
		अगर (eventfp != vq->kick) अणु
			pollstop = (filep = vq->kick) != शून्य;
			pollstart = (vq->kick = eventfp) != शून्य;
		पूर्ण अन्यथा
			filep = eventfp;
		अवरोध;
	हाल VHOST_SET_VRING_CALL:
		अगर (copy_from_user(&f, argp, माप f)) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		ctx = f.fd == VHOST_खाता_UNBIND ? शून्य : eventfd_ctx_fdget(f.fd);
		अगर (IS_ERR(ctx)) अणु
			r = PTR_ERR(ctx);
			अवरोध;
		पूर्ण

		swap(ctx, vq->call_ctx.ctx);
		अवरोध;
	हाल VHOST_SET_VRING_ERR:
		अगर (copy_from_user(&f, argp, माप f)) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		ctx = f.fd == VHOST_खाता_UNBIND ? शून्य : eventfd_ctx_fdget(f.fd);
		अगर (IS_ERR(ctx)) अणु
			r = PTR_ERR(ctx);
			अवरोध;
		पूर्ण
		swap(ctx, vq->error_ctx);
		अवरोध;
	हाल VHOST_SET_VRING_ENDIAN:
		r = vhost_set_vring_endian(vq, argp);
		अवरोध;
	हाल VHOST_GET_VRING_ENDIAN:
		r = vhost_get_vring_endian(vq, idx, argp);
		अवरोध;
	हाल VHOST_SET_VRING_BUSYLOOP_TIMEOUT:
		अगर (copy_from_user(&s, argp, माप(s))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		vq->busyloop_समयout = s.num;
		अवरोध;
	हाल VHOST_GET_VRING_BUSYLOOP_TIMEOUT:
		s.index = idx;
		s.num = vq->busyloop_समयout;
		अगर (copy_to_user(argp, &s, माप(s)))
			r = -EFAULT;
		अवरोध;
	शेष:
		r = -ENOIOCTLCMD;
	पूर्ण

	अगर (pollstop && vq->handle_kick)
		vhost_poll_stop(&vq->poll);

	अगर (!IS_ERR_OR_शून्य(ctx))
		eventfd_ctx_put(ctx);
	अगर (filep)
		fput(filep);

	अगर (pollstart && vq->handle_kick)
		r = vhost_poll_start(&vq->poll, vq->kick);

	mutex_unlock(&vq->mutex);

	अगर (pollstop && vq->handle_kick)
		vhost_poll_flush(&vq->poll);
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_vring_ioctl);

पूर्णांक vhost_init_device_iotlb(काष्ठा vhost_dev *d, bool enabled)
अणु
	काष्ठा vhost_iotlb *niotlb, *oiotlb;
	पूर्णांक i;

	niotlb = iotlb_alloc();
	अगर (!niotlb)
		वापस -ENOMEM;

	oiotlb = d->iotlb;
	d->iotlb = niotlb;

	क्रम (i = 0; i < d->nvqs; ++i) अणु
		काष्ठा vhost_virtqueue *vq = d->vqs[i];

		mutex_lock(&vq->mutex);
		vq->iotlb = niotlb;
		__vhost_vq_meta_reset(vq);
		mutex_unlock(&vq->mutex);
	पूर्ण

	vhost_iotlb_मुक्त(oiotlb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_init_device_iotlb);

/* Caller must have device mutex */
दीर्घ vhost_dev_ioctl(काष्ठा vhost_dev *d, अचिन्हित पूर्णांक ioctl, व्योम __user *argp)
अणु
	काष्ठा eventfd_ctx *ctx;
	u64 p;
	दीर्घ r;
	पूर्णांक i, fd;

	/* If you are not the owner, you can become one */
	अगर (ioctl == VHOST_SET_OWNER) अणु
		r = vhost_dev_set_owner(d);
		जाओ करोne;
	पूर्ण

	/* You must be the owner to करो anything अन्यथा */
	r = vhost_dev_check_owner(d);
	अगर (r)
		जाओ करोne;

	चयन (ioctl) अणु
	हाल VHOST_SET_MEM_TABLE:
		r = vhost_set_memory(d, argp);
		अवरोध;
	हाल VHOST_SET_LOG_BASE:
		अगर (copy_from_user(&p, argp, माप p)) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		अगर ((u64)(अचिन्हित दीर्घ)p != p) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		क्रम (i = 0; i < d->nvqs; ++i) अणु
			काष्ठा vhost_virtqueue *vq;
			व्योम __user *base = (व्योम __user *)(अचिन्हित दीर्घ)p;
			vq = d->vqs[i];
			mutex_lock(&vq->mutex);
			/* If ring is inactive, will check when it's enabled. */
			अगर (vq->निजी_data && !vq_log_access_ok(vq, base))
				r = -EFAULT;
			अन्यथा
				vq->log_base = base;
			mutex_unlock(&vq->mutex);
		पूर्ण
		अवरोध;
	हाल VHOST_SET_LOG_FD:
		r = get_user(fd, (पूर्णांक __user *)argp);
		अगर (r < 0)
			अवरोध;
		ctx = fd == VHOST_खाता_UNBIND ? शून्य : eventfd_ctx_fdget(fd);
		अगर (IS_ERR(ctx)) अणु
			r = PTR_ERR(ctx);
			अवरोध;
		पूर्ण
		swap(ctx, d->log_ctx);
		क्रम (i = 0; i < d->nvqs; ++i) अणु
			mutex_lock(&d->vqs[i]->mutex);
			d->vqs[i]->log_ctx = d->log_ctx;
			mutex_unlock(&d->vqs[i]->mutex);
		पूर्ण
		अगर (ctx)
			eventfd_ctx_put(ctx);
		अवरोध;
	शेष:
		r = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
करोne:
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_dev_ioctl);

/* TODO: This is really inefficient.  We need something like get_user()
 * (inकाष्ठाion directly accesses the data, with an exception table entry
 * वापसing -EFAULT). See Documentation/x86/exception-tables.rst.
 */
अटल पूर्णांक set_bit_to_user(पूर्णांक nr, व्योम __user *addr)
अणु
	अचिन्हित दीर्घ log = (अचिन्हित दीर्घ)addr;
	काष्ठा page *page;
	व्योम *base;
	पूर्णांक bit = nr + (log % PAGE_SIZE) * 8;
	पूर्णांक r;

	r = pin_user_pages_fast(log, 1, FOLL_WRITE, &page);
	अगर (r < 0)
		वापस r;
	BUG_ON(r != 1);
	base = kmap_atomic(page);
	set_bit(bit, base);
	kunmap_atomic(base);
	unpin_user_pages_dirty_lock(&page, 1, true);
	वापस 0;
पूर्ण

अटल पूर्णांक log_ग_लिखो(व्योम __user *log_base,
		     u64 ग_लिखो_address, u64 ग_लिखो_length)
अणु
	u64 ग_लिखो_page = ग_लिखो_address / VHOST_PAGE_SIZE;
	पूर्णांक r;

	अगर (!ग_लिखो_length)
		वापस 0;
	ग_लिखो_length += ग_लिखो_address % VHOST_PAGE_SIZE;
	क्रम (;;) अणु
		u64 base = (u64)(अचिन्हित दीर्घ)log_base;
		u64 log = base + ग_लिखो_page / 8;
		पूर्णांक bit = ग_लिखो_page % 8;
		अगर ((u64)(अचिन्हित दीर्घ)log != log)
			वापस -EFAULT;
		r = set_bit_to_user(bit, (व्योम __user *)(अचिन्हित दीर्घ)log);
		अगर (r < 0)
			वापस r;
		अगर (ग_लिखो_length <= VHOST_PAGE_SIZE)
			अवरोध;
		ग_लिखो_length -= VHOST_PAGE_SIZE;
		ग_लिखो_page += 1;
	पूर्ण
	वापस r;
पूर्ण

अटल पूर्णांक log_ग_लिखो_hva(काष्ठा vhost_virtqueue *vq, u64 hva, u64 len)
अणु
	काष्ठा vhost_iotlb *umem = vq->umem;
	काष्ठा vhost_iotlb_map *u;
	u64 start, end, l, min;
	पूर्णांक r;
	bool hit = false;

	जबतक (len) अणु
		min = len;
		/* More than one GPAs can be mapped पूर्णांकo a single HVA. So
		 * iterate all possible umems here to be safe.
		 */
		list_क्रम_each_entry(u, &umem->list, link) अणु
			अगर (u->addr > hva - 1 + len ||
			    u->addr - 1 + u->size < hva)
				जारी;
			start = max(u->addr, hva);
			end = min(u->addr - 1 + u->size, hva - 1 + len);
			l = end - start + 1;
			r = log_ग_लिखो(vq->log_base,
				      u->start + start - u->addr,
				      l);
			अगर (r < 0)
				वापस r;
			hit = true;
			min = min(l, min);
		पूर्ण

		अगर (!hit)
			वापस -EFAULT;

		len -= min;
		hva += min;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक log_used(काष्ठा vhost_virtqueue *vq, u64 used_offset, u64 len)
अणु
	काष्ठा iovec *iov = vq->log_iov;
	पूर्णांक i, ret;

	अगर (!vq->iotlb)
		वापस log_ग_लिखो(vq->log_base, vq->log_addr + used_offset, len);

	ret = translate_desc(vq, (uपूर्णांकptr_t)vq->used + used_offset,
			     len, iov, 64, VHOST_ACCESS_WO);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ret; i++) अणु
		ret = log_ग_लिखो_hva(vq,	(uपूर्णांकptr_t)iov[i].iov_base,
				    iov[i].iov_len);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vhost_log_ग_लिखो(काष्ठा vhost_virtqueue *vq, काष्ठा vhost_log *log,
		    अचिन्हित पूर्णांक log_num, u64 len, काष्ठा iovec *iov, पूर्णांक count)
अणु
	पूर्णांक i, r;

	/* Make sure data written is seen beक्रमe log. */
	smp_wmb();

	अगर (vq->iotlb) अणु
		क्रम (i = 0; i < count; i++) अणु
			r = log_ग_लिखो_hva(vq, (uपूर्णांकptr_t)iov[i].iov_base,
					  iov[i].iov_len);
			अगर (r < 0)
				वापस r;
		पूर्ण
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < log_num; ++i) अणु
		u64 l = min(log[i].len, len);
		r = log_ग_लिखो(vq->log_base, log[i].addr, l);
		अगर (r < 0)
			वापस r;
		len -= l;
		अगर (!len) अणु
			अगर (vq->log_ctx)
				eventfd_संकेत(vq->log_ctx, 1);
			वापस 0;
		पूर्ण
	पूर्ण
	/* Length written exceeds what we have stored. This is a bug. */
	BUG();
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_log_ग_लिखो);

अटल पूर्णांक vhost_update_used_flags(काष्ठा vhost_virtqueue *vq)
अणु
	व्योम __user *used;
	अगर (vhost_put_used_flags(vq))
		वापस -EFAULT;
	अगर (unlikely(vq->log_used)) अणु
		/* Make sure the flag is seen beक्रमe log. */
		smp_wmb();
		/* Log used flag ग_लिखो. */
		used = &vq->used->flags;
		log_used(vq, (used - (व्योम __user *)vq->used),
			 माप vq->used->flags);
		अगर (vq->log_ctx)
			eventfd_संकेत(vq->log_ctx, 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vhost_update_avail_event(काष्ठा vhost_virtqueue *vq, u16 avail_event)
अणु
	अगर (vhost_put_avail_event(vq))
		वापस -EFAULT;
	अगर (unlikely(vq->log_used)) अणु
		व्योम __user *used;
		/* Make sure the event is seen beक्रमe log. */
		smp_wmb();
		/* Log avail event ग_लिखो */
		used = vhost_avail_event(vq);
		log_used(vq, (used - (व्योम __user *)vq->used),
			 माप *vhost_avail_event(vq));
		अगर (vq->log_ctx)
			eventfd_संकेत(vq->log_ctx, 1);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vhost_vq_init_access(काष्ठा vhost_virtqueue *vq)
अणु
	__virtio16 last_used_idx;
	पूर्णांक r;
	bool is_le = vq->is_le;

	अगर (!vq->निजी_data)
		वापस 0;

	vhost_init_is_le(vq);

	r = vhost_update_used_flags(vq);
	अगर (r)
		जाओ err;
	vq->संकेतled_used_valid = false;
	अगर (!vq->iotlb &&
	    !access_ok(&vq->used->idx, माप vq->used->idx)) अणु
		r = -EFAULT;
		जाओ err;
	पूर्ण
	r = vhost_get_used_idx(vq, &last_used_idx);
	अगर (r) अणु
		vq_err(vq, "Can't access used idx at %p\n",
		       &vq->used->idx);
		जाओ err;
	पूर्ण
	vq->last_used_idx = vhost16_to_cpu(vq, last_used_idx);
	वापस 0;

err:
	vq->is_le = is_le;
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_vq_init_access);

अटल पूर्णांक translate_desc(काष्ठा vhost_virtqueue *vq, u64 addr, u32 len,
			  काष्ठा iovec iov[], पूर्णांक iov_size, पूर्णांक access)
अणु
	स्थिर काष्ठा vhost_iotlb_map *map;
	काष्ठा vhost_dev *dev = vq->dev;
	काष्ठा vhost_iotlb *umem = dev->iotlb ? dev->iotlb : dev->umem;
	काष्ठा iovec *_iov;
	u64 s = 0;
	पूर्णांक ret = 0;

	जबतक ((u64)len > s) अणु
		u64 size;
		अगर (unlikely(ret >= iov_size)) अणु
			ret = -ENOBUFS;
			अवरोध;
		पूर्ण

		map = vhost_iotlb_itree_first(umem, addr, addr + len - 1);
		अगर (map == शून्य || map->start > addr) अणु
			अगर (umem != dev->iotlb) अणु
				ret = -EFAULT;
				अवरोध;
			पूर्ण
			ret = -EAGAIN;
			अवरोध;
		पूर्ण अन्यथा अगर (!(map->perm & access)) अणु
			ret = -EPERM;
			अवरोध;
		पूर्ण

		_iov = iov + ret;
		size = map->size - addr + map->start;
		_iov->iov_len = min((u64)len - s, size);
		_iov->iov_base = (व्योम __user *)(अचिन्हित दीर्घ)
				 (map->addr + addr - map->start);
		s += size;
		addr += size;
		++ret;
	पूर्ण

	अगर (ret == -EAGAIN)
		vhost_iotlb_miss(vq, addr, access);
	वापस ret;
पूर्ण

/* Each buffer in the virtqueues is actually a chain of descriptors.  This
 * function वापसs the next descriptor in the chain,
 * or -1U अगर we're at the end. */
अटल अचिन्हित next_desc(काष्ठा vhost_virtqueue *vq, काष्ठा vring_desc *desc)
अणु
	अचिन्हित पूर्णांक next;

	/* If this descriptor says it करोesn't chain, we're करोne. */
	अगर (!(desc->flags & cpu_to_vhost16(vq, VRING_DESC_F_NEXT)))
		वापस -1U;

	/* Check they're not leading us off end of descriptors. */
	next = vhost16_to_cpu(vq, READ_ONCE(desc->next));
	वापस next;
पूर्ण

अटल पूर्णांक get_indirect(काष्ठा vhost_virtqueue *vq,
			काष्ठा iovec iov[], अचिन्हित पूर्णांक iov_size,
			अचिन्हित पूर्णांक *out_num, अचिन्हित पूर्णांक *in_num,
			काष्ठा vhost_log *log, अचिन्हित पूर्णांक *log_num,
			काष्ठा vring_desc *indirect)
अणु
	काष्ठा vring_desc desc;
	अचिन्हित पूर्णांक i = 0, count, found = 0;
	u32 len = vhost32_to_cpu(vq, indirect->len);
	काष्ठा iov_iter from;
	पूर्णांक ret, access;

	/* Sanity check */
	अगर (unlikely(len % माप desc)) अणु
		vq_err(vq, "Invalid length in indirect descriptor: "
		       "len 0x%llx not multiple of 0x%zx\n",
		       (अचिन्हित दीर्घ दीर्घ)len,
		       माप desc);
		वापस -EINVAL;
	पूर्ण

	ret = translate_desc(vq, vhost64_to_cpu(vq, indirect->addr), len, vq->indirect,
			     UIO_MAXIOV, VHOST_ACCESS_RO);
	अगर (unlikely(ret < 0)) अणु
		अगर (ret != -EAGAIN)
			vq_err(vq, "Translation failure %d in indirect.\n", ret);
		वापस ret;
	पूर्ण
	iov_iter_init(&from, READ, vq->indirect, ret, len);
	count = len / माप desc;
	/* Buffers are chained via a 16 bit next field, so
	 * we can have at most 2^16 of these. */
	अगर (unlikely(count > अच_लघु_उच्च + 1)) अणु
		vq_err(vq, "Indirect buffer length too big: %d\n",
		       indirect->len);
		वापस -E2BIG;
	पूर्ण

	करो अणु
		अचिन्हित iov_count = *in_num + *out_num;
		अगर (unlikely(++found > count)) अणु
			vq_err(vq, "Loop detected: last one at %u "
			       "indirect size %u\n",
			       i, count);
			वापस -EINVAL;
		पूर्ण
		अगर (unlikely(!copy_from_iter_full(&desc, माप(desc), &from))) अणु
			vq_err(vq, "Failed indirect descriptor: idx %d, %zx\n",
			       i, (माप_प्रकार)vhost64_to_cpu(vq, indirect->addr) + i * माप desc);
			वापस -EINVAL;
		पूर्ण
		अगर (unlikely(desc.flags & cpu_to_vhost16(vq, VRING_DESC_F_INसूचीECT))) अणु
			vq_err(vq, "Nested indirect descriptor: idx %d, %zx\n",
			       i, (माप_प्रकार)vhost64_to_cpu(vq, indirect->addr) + i * माप desc);
			वापस -EINVAL;
		पूर्ण

		अगर (desc.flags & cpu_to_vhost16(vq, VRING_DESC_F_WRITE))
			access = VHOST_ACCESS_WO;
		अन्यथा
			access = VHOST_ACCESS_RO;

		ret = translate_desc(vq, vhost64_to_cpu(vq, desc.addr),
				     vhost32_to_cpu(vq, desc.len), iov + iov_count,
				     iov_size - iov_count, access);
		अगर (unlikely(ret < 0)) अणु
			अगर (ret != -EAGAIN)
				vq_err(vq, "Translation failure %d indirect idx %d\n",
					ret, i);
			वापस ret;
		पूर्ण
		/* If this is an input descriptor, increment that count. */
		अगर (access == VHOST_ACCESS_WO) अणु
			*in_num += ret;
			अगर (unlikely(log && ret)) अणु
				log[*log_num].addr = vhost64_to_cpu(vq, desc.addr);
				log[*log_num].len = vhost32_to_cpu(vq, desc.len);
				++*log_num;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* If it's an output descriptor, they're all supposed
			 * to come beक्रमe any input descriptors. */
			अगर (unlikely(*in_num)) अणु
				vq_err(vq, "Indirect descriptor "
				       "has out after in: idx %d\n", i);
				वापस -EINVAL;
			पूर्ण
			*out_num += ret;
		पूर्ण
	पूर्ण जबतक ((i = next_desc(vq, &desc)) != -1);
	वापस 0;
पूर्ण

/* This looks in the virtqueue and क्रम the first available buffer, and converts
 * it to an iovec क्रम convenient access.  Since descriptors consist of some
 * number of output then some number of input descriptors, it's actually two
 * iovecs, but we pack them पूर्णांकo one and note how many of each there were.
 *
 * This function वापसs the descriptor number found, or vq->num (which is
 * never a valid descriptor number) अगर none was found.  A negative code is
 * वापसed on error. */
पूर्णांक vhost_get_vq_desc(काष्ठा vhost_virtqueue *vq,
		      काष्ठा iovec iov[], अचिन्हित पूर्णांक iov_size,
		      अचिन्हित पूर्णांक *out_num, अचिन्हित पूर्णांक *in_num,
		      काष्ठा vhost_log *log, अचिन्हित पूर्णांक *log_num)
अणु
	काष्ठा vring_desc desc;
	अचिन्हित पूर्णांक i, head, found = 0;
	u16 last_avail_idx;
	__virtio16 avail_idx;
	__virtio16 ring_head;
	पूर्णांक ret, access;

	/* Check it isn't करोing very strange things with descriptor numbers. */
	last_avail_idx = vq->last_avail_idx;

	अगर (vq->avail_idx == vq->last_avail_idx) अणु
		अगर (unlikely(vhost_get_avail_idx(vq, &avail_idx))) अणु
			vq_err(vq, "Failed to access avail idx at %p\n",
				&vq->avail->idx);
			वापस -EFAULT;
		पूर्ण
		vq->avail_idx = vhost16_to_cpu(vq, avail_idx);

		अगर (unlikely((u16)(vq->avail_idx - last_avail_idx) > vq->num)) अणु
			vq_err(vq, "Guest moved used index from %u to %u",
				last_avail_idx, vq->avail_idx);
			वापस -EFAULT;
		पूर्ण

		/* If there's nothing new since last we looked, वापस
		 * invalid.
		 */
		अगर (vq->avail_idx == last_avail_idx)
			वापस vq->num;

		/* Only get avail ring entries after they have been
		 * exposed by guest.
		 */
		smp_rmb();
	पूर्ण

	/* Grab the next descriptor number they're advertising, and increment
	 * the index we've seen. */
	अगर (unlikely(vhost_get_avail_head(vq, &ring_head, last_avail_idx))) अणु
		vq_err(vq, "Failed to read head: idx %d address %p\n",
		       last_avail_idx,
		       &vq->avail->ring[last_avail_idx % vq->num]);
		वापस -EFAULT;
	पूर्ण

	head = vhost16_to_cpu(vq, ring_head);

	/* If their number is silly, that's an error. */
	अगर (unlikely(head >= vq->num)) अणु
		vq_err(vq, "Guest says index %u > %u is available",
		       head, vq->num);
		वापस -EINVAL;
	पूर्ण

	/* When we start there are none of either input nor output. */
	*out_num = *in_num = 0;
	अगर (unlikely(log))
		*log_num = 0;

	i = head;
	करो अणु
		अचिन्हित iov_count = *in_num + *out_num;
		अगर (unlikely(i >= vq->num)) अणु
			vq_err(vq, "Desc index is %u > %u, head = %u",
			       i, vq->num, head);
			वापस -EINVAL;
		पूर्ण
		अगर (unlikely(++found > vq->num)) अणु
			vq_err(vq, "Loop detected: last one at %u "
			       "vq size %u head %u\n",
			       i, vq->num, head);
			वापस -EINVAL;
		पूर्ण
		ret = vhost_get_desc(vq, &desc, i);
		अगर (unlikely(ret)) अणु
			vq_err(vq, "Failed to get descriptor: idx %d addr %p\n",
			       i, vq->desc + i);
			वापस -EFAULT;
		पूर्ण
		अगर (desc.flags & cpu_to_vhost16(vq, VRING_DESC_F_INसूचीECT)) अणु
			ret = get_indirect(vq, iov, iov_size,
					   out_num, in_num,
					   log, log_num, &desc);
			अगर (unlikely(ret < 0)) अणु
				अगर (ret != -EAGAIN)
					vq_err(vq, "Failure detected "
						"in indirect descriptor at idx %d\n", i);
				वापस ret;
			पूर्ण
			जारी;
		पूर्ण

		अगर (desc.flags & cpu_to_vhost16(vq, VRING_DESC_F_WRITE))
			access = VHOST_ACCESS_WO;
		अन्यथा
			access = VHOST_ACCESS_RO;
		ret = translate_desc(vq, vhost64_to_cpu(vq, desc.addr),
				     vhost32_to_cpu(vq, desc.len), iov + iov_count,
				     iov_size - iov_count, access);
		अगर (unlikely(ret < 0)) अणु
			अगर (ret != -EAGAIN)
				vq_err(vq, "Translation failure %d descriptor idx %d\n",
					ret, i);
			वापस ret;
		पूर्ण
		अगर (access == VHOST_ACCESS_WO) अणु
			/* If this is an input descriptor,
			 * increment that count. */
			*in_num += ret;
			अगर (unlikely(log && ret)) अणु
				log[*log_num].addr = vhost64_to_cpu(vq, desc.addr);
				log[*log_num].len = vhost32_to_cpu(vq, desc.len);
				++*log_num;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* If it's an output descriptor, they're all supposed
			 * to come beक्रमe any input descriptors. */
			अगर (unlikely(*in_num)) अणु
				vq_err(vq, "Descriptor has out after in: "
				       "idx %d\n", i);
				वापस -EINVAL;
			पूर्ण
			*out_num += ret;
		पूर्ण
	पूर्ण जबतक ((i = next_desc(vq, &desc)) != -1);

	/* On success, increment avail index. */
	vq->last_avail_idx++;

	/* Assume notअगरications from guest are disabled at this poपूर्णांक,
	 * अगर they aren't we would need to update avail_event index. */
	BUG_ON(!(vq->used_flags & VRING_USED_F_NO_NOTIFY));
	वापस head;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_get_vq_desc);

/* Reverse the effect of vhost_get_vq_desc. Useful क्रम error handling. */
व्योम vhost_discard_vq_desc(काष्ठा vhost_virtqueue *vq, पूर्णांक n)
अणु
	vq->last_avail_idx -= n;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_discard_vq_desc);

/* After we've used one of their buffers, we tell them about it.  We'll then
 * want to notअगरy the guest, using eventfd. */
पूर्णांक vhost_add_used(काष्ठा vhost_virtqueue *vq, अचिन्हित पूर्णांक head, पूर्णांक len)
अणु
	काष्ठा vring_used_elem heads = अणु
		cpu_to_vhost32(vq, head),
		cpu_to_vhost32(vq, len)
	पूर्ण;

	वापस vhost_add_used_n(vq, &heads, 1);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_add_used);

अटल पूर्णांक __vhost_add_used_n(काष्ठा vhost_virtqueue *vq,
			    काष्ठा vring_used_elem *heads,
			    अचिन्हित count)
अणु
	vring_used_elem_t __user *used;
	u16 old, new;
	पूर्णांक start;

	start = vq->last_used_idx & (vq->num - 1);
	used = vq->used->ring + start;
	अगर (vhost_put_used(vq, heads, start, count)) अणु
		vq_err(vq, "Failed to write used");
		वापस -EFAULT;
	पूर्ण
	अगर (unlikely(vq->log_used)) अणु
		/* Make sure data is seen beक्रमe log. */
		smp_wmb();
		/* Log used ring entry ग_लिखो. */
		log_used(vq, ((व्योम __user *)used - (व्योम __user *)vq->used),
			 count * माप *used);
	पूर्ण
	old = vq->last_used_idx;
	new = (vq->last_used_idx += count);
	/* If the driver never bothers to संकेत in a very दीर्घ जबतक,
	 * used index might wrap around. If that happens, invalidate
	 * संकेतled_used index we stored. TODO: make sure driver
	 * संकेतs at least once in 2^16 and हटाओ this. */
	अगर (unlikely((u16)(new - vq->संकेतled_used) < (u16)(new - old)))
		vq->संकेतled_used_valid = false;
	वापस 0;
पूर्ण

/* After we've used one of their buffers, we tell them about it.  We'll then
 * want to notअगरy the guest, using eventfd. */
पूर्णांक vhost_add_used_n(काष्ठा vhost_virtqueue *vq, काष्ठा vring_used_elem *heads,
		     अचिन्हित count)
अणु
	पूर्णांक start, n, r;

	start = vq->last_used_idx & (vq->num - 1);
	n = vq->num - start;
	अगर (n < count) अणु
		r = __vhost_add_used_n(vq, heads, n);
		अगर (r < 0)
			वापस r;
		heads += n;
		count -= n;
	पूर्ण
	r = __vhost_add_used_n(vq, heads, count);

	/* Make sure buffer is written beक्रमe we update index. */
	smp_wmb();
	अगर (vhost_put_used_idx(vq)) अणु
		vq_err(vq, "Failed to increment used idx");
		वापस -EFAULT;
	पूर्ण
	अगर (unlikely(vq->log_used)) अणु
		/* Make sure used idx is seen beक्रमe log. */
		smp_wmb();
		/* Log used index update. */
		log_used(vq, दुरत्व(काष्ठा vring_used, idx),
			 माप vq->used->idx);
		अगर (vq->log_ctx)
			eventfd_संकेत(vq->log_ctx, 1);
	पूर्ण
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_add_used_n);

अटल bool vhost_notअगरy(काष्ठा vhost_dev *dev, काष्ठा vhost_virtqueue *vq)
अणु
	__u16 old, new;
	__virtio16 event;
	bool v;
	/* Flush out used index updates. This is paired
	 * with the barrier that the Guest executes when enabling
	 * पूर्णांकerrupts. */
	smp_mb();

	अगर (vhost_has_feature(vq, VIRTIO_F_NOTIFY_ON_EMPTY) &&
	    unlikely(vq->avail_idx == vq->last_avail_idx))
		वापस true;

	अगर (!vhost_has_feature(vq, VIRTIO_RING_F_EVENT_IDX)) अणु
		__virtio16 flags;
		अगर (vhost_get_avail_flags(vq, &flags)) अणु
			vq_err(vq, "Failed to get flags");
			वापस true;
		पूर्ण
		वापस !(flags & cpu_to_vhost16(vq, VRING_AVAIL_F_NO_INTERRUPT));
	पूर्ण
	old = vq->संकेतled_used;
	v = vq->संकेतled_used_valid;
	new = vq->संकेतled_used = vq->last_used_idx;
	vq->संकेतled_used_valid = true;

	अगर (unlikely(!v))
		वापस true;

	अगर (vhost_get_used_event(vq, &event)) अणु
		vq_err(vq, "Failed to get used event idx");
		वापस true;
	पूर्ण
	वापस vring_need_event(vhost16_to_cpu(vq, event), new, old);
पूर्ण

/* This actually संकेतs the guest, using eventfd. */
व्योम vhost_संकेत(काष्ठा vhost_dev *dev, काष्ठा vhost_virtqueue *vq)
अणु
	/* Signal the Guest tell them we used something up. */
	अगर (vq->call_ctx.ctx && vhost_notअगरy(dev, vq))
		eventfd_संकेत(vq->call_ctx.ctx, 1);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_संकेत);

/* And here's the combo meal deal.  Supersize me! */
व्योम vhost_add_used_and_संकेत(काष्ठा vhost_dev *dev,
			       काष्ठा vhost_virtqueue *vq,
			       अचिन्हित पूर्णांक head, पूर्णांक len)
अणु
	vhost_add_used(vq, head, len);
	vhost_संकेत(dev, vq);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_add_used_and_संकेत);

/* multi-buffer version of vhost_add_used_and_संकेत */
व्योम vhost_add_used_and_संकेत_n(काष्ठा vhost_dev *dev,
				 काष्ठा vhost_virtqueue *vq,
				 काष्ठा vring_used_elem *heads, अचिन्हित count)
अणु
	vhost_add_used_n(vq, heads, count);
	vhost_संकेत(dev, vq);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_add_used_and_संकेत_n);

/* वापस true अगर we're sure that avaiable ring is empty */
bool vhost_vq_avail_empty(काष्ठा vhost_dev *dev, काष्ठा vhost_virtqueue *vq)
अणु
	__virtio16 avail_idx;
	पूर्णांक r;

	अगर (vq->avail_idx != vq->last_avail_idx)
		वापस false;

	r = vhost_get_avail_idx(vq, &avail_idx);
	अगर (unlikely(r))
		वापस false;
	vq->avail_idx = vhost16_to_cpu(vq, avail_idx);

	वापस vq->avail_idx == vq->last_avail_idx;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_vq_avail_empty);

/* OK, now we need to know about added descriptors. */
bool vhost_enable_notअगरy(काष्ठा vhost_dev *dev, काष्ठा vhost_virtqueue *vq)
अणु
	__virtio16 avail_idx;
	पूर्णांक r;

	अगर (!(vq->used_flags & VRING_USED_F_NO_NOTIFY))
		वापस false;
	vq->used_flags &= ~VRING_USED_F_NO_NOTIFY;
	अगर (!vhost_has_feature(vq, VIRTIO_RING_F_EVENT_IDX)) अणु
		r = vhost_update_used_flags(vq);
		अगर (r) अणु
			vq_err(vq, "Failed to enable notification at %p: %d\n",
			       &vq->used->flags, r);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		r = vhost_update_avail_event(vq, vq->avail_idx);
		अगर (r) अणु
			vq_err(vq, "Failed to update avail event index at %p: %d\n",
			       vhost_avail_event(vq), r);
			वापस false;
		पूर्ण
	पूर्ण
	/* They could have slipped one in as we were करोing that: make
	 * sure it's written, then check again. */
	smp_mb();
	r = vhost_get_avail_idx(vq, &avail_idx);
	अगर (r) अणु
		vq_err(vq, "Failed to check avail idx at %p: %d\n",
		       &vq->avail->idx, r);
		वापस false;
	पूर्ण

	वापस vhost16_to_cpu(vq, avail_idx) != vq->avail_idx;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_enable_notअगरy);

/* We करोn't need to be notअगरied again. */
व्योम vhost_disable_notअगरy(काष्ठा vhost_dev *dev, काष्ठा vhost_virtqueue *vq)
अणु
	पूर्णांक r;

	अगर (vq->used_flags & VRING_USED_F_NO_NOTIFY)
		वापस;
	vq->used_flags |= VRING_USED_F_NO_NOTIFY;
	अगर (!vhost_has_feature(vq, VIRTIO_RING_F_EVENT_IDX)) अणु
		r = vhost_update_used_flags(vq);
		अगर (r)
			vq_err(vq, "Failed to disable notification at %p: %d\n",
			       &vq->used->flags, r);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vhost_disable_notअगरy);

/* Create a new message. */
काष्ठा vhost_msg_node *vhost_new_msg(काष्ठा vhost_virtqueue *vq, पूर्णांक type)
अणु
	काष्ठा vhost_msg_node *node = kदो_स्मृति(माप *node, GFP_KERNEL);
	अगर (!node)
		वापस शून्य;

	/* Make sure all padding within the काष्ठाure is initialized. */
	स_रखो(&node->msg, 0, माप node->msg);
	node->vq = vq;
	node->msg.type = type;
	वापस node;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_new_msg);

व्योम vhost_enqueue_msg(काष्ठा vhost_dev *dev, काष्ठा list_head *head,
		       काष्ठा vhost_msg_node *node)
अणु
	spin_lock(&dev->iotlb_lock);
	list_add_tail(&node->node, head);
	spin_unlock(&dev->iotlb_lock);

	wake_up_पूर्णांकerruptible_poll(&dev->रुको, EPOLLIN | EPOLLRDNORM);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_enqueue_msg);

काष्ठा vhost_msg_node *vhost_dequeue_msg(काष्ठा vhost_dev *dev,
					 काष्ठा list_head *head)
अणु
	काष्ठा vhost_msg_node *node = शून्य;

	spin_lock(&dev->iotlb_lock);
	अगर (!list_empty(head)) अणु
		node = list_first_entry(head, काष्ठा vhost_msg_node,
					node);
		list_del(&node->node);
	पूर्ण
	spin_unlock(&dev->iotlb_lock);

	वापस node;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_dequeue_msg);

व्योम vhost_set_backend_features(काष्ठा vhost_dev *dev, u64 features)
अणु
	काष्ठा vhost_virtqueue *vq;
	पूर्णांक i;

	mutex_lock(&dev->mutex);
	क्रम (i = 0; i < dev->nvqs; ++i) अणु
		vq = dev->vqs[i];
		mutex_lock(&vq->mutex);
		vq->acked_backend_features = features;
		mutex_unlock(&vq->mutex);
	पूर्ण
	mutex_unlock(&dev->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_set_backend_features);

अटल पूर्णांक __init vhost_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास vhost_निकास(व्योम)
अणु
पूर्ण

module_init(vhost_init);
module_निकास(vhost_निकास);

MODULE_VERSION("0.0.1");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Michael S. Tsirkin");
MODULE_DESCRIPTION("Host kernel accelerator for virtio");
