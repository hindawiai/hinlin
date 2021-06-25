<शैली गुरु>
/*
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2005 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2005 PathScale, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/file.h>
#समावेश <linux/cdev.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/mm.h>

#समावेश <linux/uaccess.h>

#समावेश <rdma/ib.h>
#समावेश <rdma/uverbs_std_types.h>
#समावेश <rdma/rdma_netlink.h>

#समावेश "uverbs.h"
#समावेश "core_priv.h"
#समावेश "rdma_core.h"

MODULE_AUTHOR("Roland Dreier");
MODULE_DESCRIPTION("InfiniBand userspace verbs access");
MODULE_LICENSE("Dual BSD/GPL");

क्रमागत अणु
	IB_UVERBS_MAJOR       = 231,
	IB_UVERBS_BASE_MINOR  = 192,
	IB_UVERBS_MAX_DEVICES = RDMA_MAX_PORTS,
	IB_UVERBS_NUM_FIXED_MINOR = 32,
	IB_UVERBS_NUM_DYNAMIC_MINOR = IB_UVERBS_MAX_DEVICES - IB_UVERBS_NUM_FIXED_MINOR,
पूर्ण;

#घोषणा IB_UVERBS_BASE_DEV	MKDEV(IB_UVERBS_MAJOR, IB_UVERBS_BASE_MINOR)

अटल dev_t dynamic_uverbs_dev;
अटल काष्ठा class *uverbs_class;

अटल DEFINE_IDA(uverbs_ida);
अटल पूर्णांक ib_uverbs_add_one(काष्ठा ib_device *device);
अटल व्योम ib_uverbs_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data);

/*
 * Must be called with the ufile->device->disassociate_srcu held, and the lock
 * must be held until use of the ucontext is finished.
 */
काष्ठा ib_ucontext *ib_uverbs_get_ucontext_file(काष्ठा ib_uverbs_file *ufile)
अणु
	/*
	 * We करो not hold the hw_destroy_rwsem lock क्रम this flow, instead
	 * srcu is used. It करोes not matter अगर someone races this with
	 * get_context, we get शून्य or valid ucontext.
	 */
	काष्ठा ib_ucontext *ucontext = smp_load_acquire(&ufile->ucontext);

	अगर (!srcu_dereference(ufile->device->ib_dev,
			      &ufile->device->disassociate_srcu))
		वापस ERR_PTR(-EIO);

	अगर (!ucontext)
		वापस ERR_PTR(-EINVAL);

	वापस ucontext;
पूर्ण
EXPORT_SYMBOL(ib_uverbs_get_ucontext_file);

पूर्णांक uverbs_dealloc_mw(काष्ठा ib_mw *mw)
अणु
	काष्ठा ib_pd *pd = mw->pd;
	पूर्णांक ret;

	ret = mw->device->ops.dealloc_mw(mw);
	अगर (ret)
		वापस ret;

	atomic_dec(&pd->usecnt);
	kमुक्त(mw);
	वापस ret;
पूर्ण

अटल व्योम ib_uverbs_release_dev(काष्ठा device *device)
अणु
	काष्ठा ib_uverbs_device *dev =
			container_of(device, काष्ठा ib_uverbs_device, dev);

	uverbs_destroy_api(dev->uapi);
	cleanup_srcu_काष्ठा(&dev->disassociate_srcu);
	mutex_destroy(&dev->lists_mutex);
	mutex_destroy(&dev->xrcd_tree_mutex);
	kमुक्त(dev);
पूर्ण

व्योम ib_uverbs_release_ucq(काष्ठा ib_uverbs_completion_event_file *ev_file,
			   काष्ठा ib_ucq_object *uobj)
अणु
	काष्ठा ib_uverbs_event *evt, *पंचांगp;

	अगर (ev_file) अणु
		spin_lock_irq(&ev_file->ev_queue.lock);
		list_क्रम_each_entry_safe(evt, पंचांगp, &uobj->comp_list, obj_list) अणु
			list_del(&evt->list);
			kमुक्त(evt);
		पूर्ण
		spin_unlock_irq(&ev_file->ev_queue.lock);

		uverbs_uobject_put(&ev_file->uobj);
	पूर्ण

	ib_uverbs_release_uevent(&uobj->uevent);
पूर्ण

व्योम ib_uverbs_release_uevent(काष्ठा ib_uevent_object *uobj)
अणु
	काष्ठा ib_uverbs_async_event_file *async_file = uobj->event_file;
	काष्ठा ib_uverbs_event *evt, *पंचांगp;

	अगर (!async_file)
		वापस;

	spin_lock_irq(&async_file->ev_queue.lock);
	list_क्रम_each_entry_safe(evt, पंचांगp, &uobj->event_list, obj_list) अणु
		list_del(&evt->list);
		kमुक्त(evt);
	पूर्ण
	spin_unlock_irq(&async_file->ev_queue.lock);
	uverbs_uobject_put(&async_file->uobj);
पूर्ण

व्योम ib_uverbs_detach_umcast(काष्ठा ib_qp *qp,
			     काष्ठा ib_uqp_object *uobj)
अणु
	काष्ठा ib_uverbs_mcast_entry *mcast, *पंचांगp;

	list_क्रम_each_entry_safe(mcast, पंचांगp, &uobj->mcast_list, list) अणु
		ib_detach_mcast(qp, &mcast->gid, mcast->lid);
		list_del(&mcast->list);
		kमुक्त(mcast);
	पूर्ण
पूर्ण

अटल व्योम ib_uverbs_comp_dev(काष्ठा ib_uverbs_device *dev)
अणु
	complete(&dev->comp);
पूर्ण

व्योम ib_uverbs_release_file(काष्ठा kref *ref)
अणु
	काष्ठा ib_uverbs_file *file =
		container_of(ref, काष्ठा ib_uverbs_file, ref);
	काष्ठा ib_device *ib_dev;
	पूर्णांक srcu_key;

	release_ufile_idr_uobject(file);

	srcu_key = srcu_पढ़ो_lock(&file->device->disassociate_srcu);
	ib_dev = srcu_dereference(file->device->ib_dev,
				  &file->device->disassociate_srcu);
	अगर (ib_dev && !ib_dev->ops.disassociate_ucontext)
		module_put(ib_dev->ops.owner);
	srcu_पढ़ो_unlock(&file->device->disassociate_srcu, srcu_key);

	अगर (atomic_dec_and_test(&file->device->refcount))
		ib_uverbs_comp_dev(file->device);

	अगर (file->शेष_async_file)
		uverbs_uobject_put(&file->शेष_async_file->uobj);
	put_device(&file->device->dev);

	अगर (file->disassociate_page)
		__मुक्त_pages(file->disassociate_page, 0);
	mutex_destroy(&file->umap_lock);
	mutex_destroy(&file->ucontext_lock);
	kमुक्त(file);
पूर्ण

अटल sमाप_प्रकार ib_uverbs_event_पढ़ो(काष्ठा ib_uverbs_event_queue *ev_queue,
				    काष्ठा file *filp, अक्षर __user *buf,
				    माप_प्रकार count, loff_t *pos,
				    माप_प्रकार eventsz)
अणु
	काष्ठा ib_uverbs_event *event;
	पूर्णांक ret = 0;

	spin_lock_irq(&ev_queue->lock);

	जबतक (list_empty(&ev_queue->event_list)) अणु
		spin_unlock_irq(&ev_queue->lock);

		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		अगर (रुको_event_पूर्णांकerruptible(ev_queue->poll_रुको,
					     (!list_empty(&ev_queue->event_list) ||
					      ev_queue->is_बंदd)))
			वापस -ERESTARTSYS;

		spin_lock_irq(&ev_queue->lock);

		/* If device was disassociated and no event exists set an error */
		अगर (list_empty(&ev_queue->event_list) && ev_queue->is_बंदd) अणु
			spin_unlock_irq(&ev_queue->lock);
			वापस -EIO;
		पूर्ण
	पूर्ण

	event = list_entry(ev_queue->event_list.next, काष्ठा ib_uverbs_event, list);

	अगर (eventsz > count) अणु
		ret   = -EINVAL;
		event = शून्य;
	पूर्ण अन्यथा अणु
		list_del(ev_queue->event_list.next);
		अगर (event->counter) अणु
			++(*event->counter);
			list_del(&event->obj_list);
		पूर्ण
	पूर्ण

	spin_unlock_irq(&ev_queue->lock);

	अगर (event) अणु
		अगर (copy_to_user(buf, event, eventsz))
			ret = -EFAULT;
		अन्यथा
			ret = eventsz;
	पूर्ण

	kमुक्त(event);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ib_uverbs_async_event_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
					  माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा ib_uverbs_async_event_file *file = filp->निजी_data;

	वापस ib_uverbs_event_पढ़ो(&file->ev_queue, filp, buf, count, pos,
				    माप(काष्ठा ib_uverbs_async_event_desc));
पूर्ण

अटल sमाप_प्रकार ib_uverbs_comp_event_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
					 माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा ib_uverbs_completion_event_file *comp_ev_file =
		filp->निजी_data;

	वापस ib_uverbs_event_पढ़ो(&comp_ev_file->ev_queue, filp, buf, count,
				    pos,
				    माप(काष्ठा ib_uverbs_comp_event_desc));
पूर्ण

अटल __poll_t ib_uverbs_event_poll(काष्ठा ib_uverbs_event_queue *ev_queue,
					 काष्ठा file *filp,
					 काष्ठा poll_table_काष्ठा *रुको)
अणु
	__poll_t pollflags = 0;

	poll_रुको(filp, &ev_queue->poll_रुको, रुको);

	spin_lock_irq(&ev_queue->lock);
	अगर (!list_empty(&ev_queue->event_list))
		pollflags = EPOLLIN | EPOLLRDNORM;
	अन्यथा अगर (ev_queue->is_बंदd)
		pollflags = EPOLLERR;
	spin_unlock_irq(&ev_queue->lock);

	वापस pollflags;
पूर्ण

अटल __poll_t ib_uverbs_async_event_poll(काष्ठा file *filp,
					       काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा ib_uverbs_async_event_file *file = filp->निजी_data;

	वापस ib_uverbs_event_poll(&file->ev_queue, filp, रुको);
पूर्ण

अटल __poll_t ib_uverbs_comp_event_poll(काष्ठा file *filp,
					      काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा ib_uverbs_completion_event_file *comp_ev_file =
		filp->निजी_data;

	वापस ib_uverbs_event_poll(&comp_ev_file->ev_queue, filp, रुको);
पूर्ण

अटल पूर्णांक ib_uverbs_async_event_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on)
अणु
	काष्ठा ib_uverbs_async_event_file *file = filp->निजी_data;

	वापस fasync_helper(fd, filp, on, &file->ev_queue.async_queue);
पूर्ण

अटल पूर्णांक ib_uverbs_comp_event_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on)
अणु
	काष्ठा ib_uverbs_completion_event_file *comp_ev_file =
		filp->निजी_data;

	वापस fasync_helper(fd, filp, on, &comp_ev_file->ev_queue.async_queue);
पूर्ण

स्थिर काष्ठा file_operations uverbs_event_fops = अणु
	.owner	 = THIS_MODULE,
	.पढ़ो	 = ib_uverbs_comp_event_पढ़ो,
	.poll    = ib_uverbs_comp_event_poll,
	.release = uverbs_uobject_fd_release,
	.fasync  = ib_uverbs_comp_event_fasync,
	.llseek	 = no_llseek,
पूर्ण;

स्थिर काष्ठा file_operations uverbs_async_event_fops = अणु
	.owner	 = THIS_MODULE,
	.पढ़ो	 = ib_uverbs_async_event_पढ़ो,
	.poll    = ib_uverbs_async_event_poll,
	.release = uverbs_async_event_release,
	.fasync  = ib_uverbs_async_event_fasync,
	.llseek	 = no_llseek,
पूर्ण;

व्योम ib_uverbs_comp_handler(काष्ठा ib_cq *cq, व्योम *cq_context)
अणु
	काष्ठा ib_uverbs_event_queue   *ev_queue = cq_context;
	काष्ठा ib_ucq_object	       *uobj;
	काष्ठा ib_uverbs_event	       *entry;
	अचिन्हित दीर्घ			flags;

	अगर (!ev_queue)
		वापस;

	spin_lock_irqsave(&ev_queue->lock, flags);
	अगर (ev_queue->is_बंदd) अणु
		spin_unlock_irqrestore(&ev_queue->lock, flags);
		वापस;
	पूर्ण

	entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
	अगर (!entry) अणु
		spin_unlock_irqrestore(&ev_queue->lock, flags);
		वापस;
	पूर्ण

	uobj = cq->uobject;

	entry->desc.comp.cq_handle = cq->uobject->uevent.uobject.user_handle;
	entry->counter		   = &uobj->comp_events_reported;

	list_add_tail(&entry->list, &ev_queue->event_list);
	list_add_tail(&entry->obj_list, &uobj->comp_list);
	spin_unlock_irqrestore(&ev_queue->lock, flags);

	wake_up_पूर्णांकerruptible(&ev_queue->poll_रुको);
	समाप्त_fasync(&ev_queue->async_queue, SIGIO, POLL_IN);
पूर्ण

व्योम ib_uverbs_async_handler(काष्ठा ib_uverbs_async_event_file *async_file,
			     __u64 element, __u64 event,
			     काष्ठा list_head *obj_list, u32 *counter)
अणु
	काष्ठा ib_uverbs_event *entry;
	अचिन्हित दीर्घ flags;

	अगर (!async_file)
		वापस;

	spin_lock_irqsave(&async_file->ev_queue.lock, flags);
	अगर (async_file->ev_queue.is_बंदd) अणु
		spin_unlock_irqrestore(&async_file->ev_queue.lock, flags);
		वापस;
	पूर्ण

	entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
	अगर (!entry) अणु
		spin_unlock_irqrestore(&async_file->ev_queue.lock, flags);
		वापस;
	पूर्ण

	entry->desc.async.element = element;
	entry->desc.async.event_type = event;
	entry->desc.async.reserved = 0;
	entry->counter = counter;

	list_add_tail(&entry->list, &async_file->ev_queue.event_list);
	अगर (obj_list)
		list_add_tail(&entry->obj_list, obj_list);
	spin_unlock_irqrestore(&async_file->ev_queue.lock, flags);

	wake_up_पूर्णांकerruptible(&async_file->ev_queue.poll_रुको);
	समाप्त_fasync(&async_file->ev_queue.async_queue, SIGIO, POLL_IN);
पूर्ण

अटल व्योम uverbs_uobj_event(काष्ठा ib_uevent_object *eobj,
			      काष्ठा ib_event *event)
अणु
	ib_uverbs_async_handler(eobj->event_file,
				eobj->uobject.user_handle, event->event,
				&eobj->event_list, &eobj->events_reported);
पूर्ण

व्योम ib_uverbs_cq_event_handler(काष्ठा ib_event *event, व्योम *context_ptr)
अणु
	uverbs_uobj_event(&event->element.cq->uobject->uevent, event);
पूर्ण

व्योम ib_uverbs_qp_event_handler(काष्ठा ib_event *event, व्योम *context_ptr)
अणु
	/* क्रम XRC target qp's, check that qp is live */
	अगर (!event->element.qp->uobject)
		वापस;

	uverbs_uobj_event(&event->element.qp->uobject->uevent, event);
पूर्ण

व्योम ib_uverbs_wq_event_handler(काष्ठा ib_event *event, व्योम *context_ptr)
अणु
	uverbs_uobj_event(&event->element.wq->uobject->uevent, event);
पूर्ण

व्योम ib_uverbs_srq_event_handler(काष्ठा ib_event *event, व्योम *context_ptr)
अणु
	uverbs_uobj_event(&event->element.srq->uobject->uevent, event);
पूर्ण

अटल व्योम ib_uverbs_event_handler(काष्ठा ib_event_handler *handler,
				    काष्ठा ib_event *event)
अणु
	ib_uverbs_async_handler(
		container_of(handler, काष्ठा ib_uverbs_async_event_file,
			     event_handler),
		event->element.port_num, event->event, शून्य, शून्य);
पूर्ण

व्योम ib_uverbs_init_event_queue(काष्ठा ib_uverbs_event_queue *ev_queue)
अणु
	spin_lock_init(&ev_queue->lock);
	INIT_LIST_HEAD(&ev_queue->event_list);
	init_रुकोqueue_head(&ev_queue->poll_रुको);
	ev_queue->is_बंदd   = 0;
	ev_queue->async_queue = शून्य;
पूर्ण

व्योम ib_uverbs_init_async_event_file(
	काष्ठा ib_uverbs_async_event_file *async_file)
अणु
	काष्ठा ib_uverbs_file *uverbs_file = async_file->uobj.ufile;
	काष्ठा ib_device *ib_dev = async_file->uobj.context->device;

	ib_uverbs_init_event_queue(&async_file->ev_queue);

	/* The first async_event_file becomes the शेष one क्रम the file. */
	mutex_lock(&uverbs_file->ucontext_lock);
	अगर (!uverbs_file->शेष_async_file) अणु
		/* Pairs with the put in ib_uverbs_release_file */
		uverbs_uobject_get(&async_file->uobj);
		smp_store_release(&uverbs_file->शेष_async_file, async_file);
	पूर्ण
	mutex_unlock(&uverbs_file->ucontext_lock);

	INIT_IB_EVENT_HANDLER(&async_file->event_handler, ib_dev,
			      ib_uverbs_event_handler);
	ib_रेजिस्टर_event_handler(&async_file->event_handler);
पूर्ण

अटल sमाप_प्रकार verअगरy_hdr(काष्ठा ib_uverbs_cmd_hdr *hdr,
			  काष्ठा ib_uverbs_ex_cmd_hdr *ex_hdr, माप_प्रकार count,
			  स्थिर काष्ठा uverbs_api_ग_लिखो_method *method_elm)
अणु
	अगर (method_elm->is_ex) अणु
		count -= माप(*hdr) + माप(*ex_hdr);

		अगर ((hdr->in_words + ex_hdr->provider_in_words) * 8 != count)
			वापस -EINVAL;

		अगर (hdr->in_words * 8 < method_elm->req_size)
			वापस -ENOSPC;

		अगर (ex_hdr->cmd_hdr_reserved)
			वापस -EINVAL;

		अगर (ex_hdr->response) अणु
			अगर (!hdr->out_words && !ex_hdr->provider_out_words)
				वापस -EINVAL;

			अगर (hdr->out_words * 8 < method_elm->resp_size)
				वापस -ENOSPC;

			अगर (!access_ok(u64_to_user_ptr(ex_hdr->response),
				       (hdr->out_words + ex_hdr->provider_out_words) * 8))
				वापस -EFAULT;
		पूर्ण अन्यथा अणु
			अगर (hdr->out_words || ex_hdr->provider_out_words)
				वापस -EINVAL;
		पूर्ण

		वापस 0;
	पूर्ण

	/* not extended command */
	अगर (hdr->in_words * 4 != count)
		वापस -EINVAL;

	अगर (count < method_elm->req_size + माप(hdr)) अणु
		/*
		 * rdma-core v18 and v19 have a bug where they send DESTROY_CQ
		 * with a 16 byte ग_लिखो instead of 24. Old kernels didn't
		 * check the size so they allowed this. Now that the size is
		 * checked provide a compatibility work around to not अवरोध
		 * those userspaces.
		 */
		अगर (hdr->command == IB_USER_VERBS_CMD_DESTROY_CQ &&
		    count == 16) अणु
			hdr->in_words = 6;
			वापस 0;
		पूर्ण
		वापस -ENOSPC;
	पूर्ण
	अगर (hdr->out_words * 4 < method_elm->resp_size)
		वापस -ENOSPC;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ib_uverbs_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा ib_uverbs_file *file = filp->निजी_data;
	स्थिर काष्ठा uverbs_api_ग_लिखो_method *method_elm;
	काष्ठा uverbs_api *uapi = file->device->uapi;
	काष्ठा ib_uverbs_ex_cmd_hdr ex_hdr;
	काष्ठा ib_uverbs_cmd_hdr hdr;
	काष्ठा uverbs_attr_bundle bundle;
	पूर्णांक srcu_key;
	sमाप_प्रकार ret;

	अगर (!ib_safe_file_access(filp)) अणु
		pr_err_once("uverbs_write: process %d (%s) changed security contexts after opening file descriptor, this is not allowed.\n",
			    task_tgid_vnr(current), current->comm);
		वापस -EACCES;
	पूर्ण

	अगर (count < माप(hdr))
		वापस -EINVAL;

	अगर (copy_from_user(&hdr, buf, माप(hdr)))
		वापस -EFAULT;

	method_elm = uapi_get_method(uapi, hdr.command);
	अगर (IS_ERR(method_elm))
		वापस PTR_ERR(method_elm);

	अगर (method_elm->is_ex) अणु
		अगर (count < (माप(hdr) + माप(ex_hdr)))
			वापस -EINVAL;
		अगर (copy_from_user(&ex_hdr, buf + माप(hdr), माप(ex_hdr)))
			वापस -EFAULT;
	पूर्ण

	ret = verअगरy_hdr(&hdr, &ex_hdr, count, method_elm);
	अगर (ret)
		वापस ret;

	srcu_key = srcu_पढ़ो_lock(&file->device->disassociate_srcu);

	buf += माप(hdr);

	स_रखो(bundle.attr_present, 0, माप(bundle.attr_present));
	bundle.ufile = file;
	bundle.context = शून्य; /* only valid अगर bundle has uobject */
	bundle.uobject = शून्य;
	अगर (!method_elm->is_ex) अणु
		माप_प्रकार in_len = hdr.in_words * 4 - माप(hdr);
		माप_प्रकार out_len = hdr.out_words * 4;
		u64 response = 0;

		अगर (method_elm->has_udata) अणु
			bundle.driver_udata.inlen =
				in_len - method_elm->req_size;
			in_len = method_elm->req_size;
			अगर (bundle.driver_udata.inlen)
				bundle.driver_udata.inbuf = buf + in_len;
			अन्यथा
				bundle.driver_udata.inbuf = शून्य;
		पूर्ण अन्यथा अणु
			स_रखो(&bundle.driver_udata, 0,
			       माप(bundle.driver_udata));
		पूर्ण

		अगर (method_elm->has_resp) अणु
			/*
			 * The macros check that अगर has_resp is set
			 * then the command request काष्ठाure starts
			 * with a '__aligned u64 response' member.
			 */
			ret = get_user(response, (स्थिर u64 __user *)buf);
			अगर (ret)
				जाओ out_unlock;

			अगर (method_elm->has_udata) अणु
				bundle.driver_udata.outlen =
					out_len - method_elm->resp_size;
				out_len = method_elm->resp_size;
				अगर (bundle.driver_udata.outlen)
					bundle.driver_udata.outbuf =
						u64_to_user_ptr(response +
								out_len);
				अन्यथा
					bundle.driver_udata.outbuf = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			bundle.driver_udata.outlen = 0;
			bundle.driver_udata.outbuf = शून्य;
		पूर्ण

		ib_uverbs_init_udata_buf_or_null(
			&bundle.ucore, buf, u64_to_user_ptr(response),
			in_len, out_len);
	पूर्ण अन्यथा अणु
		buf += माप(ex_hdr);

		ib_uverbs_init_udata_buf_or_null(&bundle.ucore, buf,
					u64_to_user_ptr(ex_hdr.response),
					hdr.in_words * 8, hdr.out_words * 8);

		ib_uverbs_init_udata_buf_or_null(
			&bundle.driver_udata, buf + bundle.ucore.inlen,
			u64_to_user_ptr(ex_hdr.response) + bundle.ucore.outlen,
			ex_hdr.provider_in_words * 8,
			ex_hdr.provider_out_words * 8);

	पूर्ण

	ret = method_elm->handler(&bundle);
	अगर (bundle.uobject)
		uverbs_finalize_object(bundle.uobject, UVERBS_ACCESS_NEW, true,
				       !ret, &bundle);
out_unlock:
	srcu_पढ़ो_unlock(&file->device->disassociate_srcu, srcu_key);
	वापस (ret) ? : count;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा rdma_umap_ops;

अटल पूर्णांक ib_uverbs_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा ib_uverbs_file *file = filp->निजी_data;
	काष्ठा ib_ucontext *ucontext;
	पूर्णांक ret = 0;
	पूर्णांक srcu_key;

	srcu_key = srcu_पढ़ो_lock(&file->device->disassociate_srcu);
	ucontext = ib_uverbs_get_ucontext_file(file);
	अगर (IS_ERR(ucontext)) अणु
		ret = PTR_ERR(ucontext);
		जाओ out;
	पूर्ण
	vma->vm_ops = &rdma_umap_ops;
	ret = ucontext->device->ops.mmap(ucontext, vma);
out:
	srcu_पढ़ो_unlock(&file->device->disassociate_srcu, srcu_key);
	वापस ret;
पूर्ण

/*
 * The VMA has been dup'd, initialize the vm_निजी_data with a new tracking
 * काष्ठा
 */
अटल व्योम rdma_umap_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा ib_uverbs_file *ufile = vma->vm_file->निजी_data;
	काष्ठा rdma_umap_priv *opriv = vma->vm_निजी_data;
	काष्ठा rdma_umap_priv *priv;

	अगर (!opriv)
		वापस;

	/* We are racing with disassociation */
	अगर (!करोwn_पढ़ो_trylock(&ufile->hw_destroy_rwsem))
		जाओ out_zap;
	/*
	 * Disassociation alपढ़ोy completed, the VMA should alपढ़ोy be zapped.
	 */
	अगर (!ufile->ucontext)
		जाओ out_unlock;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		जाओ out_unlock;
	rdma_umap_priv_init(priv, vma, opriv->entry);

	up_पढ़ो(&ufile->hw_destroy_rwsem);
	वापस;

out_unlock:
	up_पढ़ो(&ufile->hw_destroy_rwsem);
out_zap:
	/*
	 * We can't allow the VMA to be created with the actual IO pages, that
	 * would अवरोध our API contract, and it can't be stopped at this
	 * poपूर्णांक, so zap it.
	 */
	vma->vm_निजी_data = शून्य;
	zap_vma_ptes(vma, vma->vm_start, vma->vm_end - vma->vm_start);
पूर्ण

अटल व्योम rdma_umap_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा ib_uverbs_file *ufile = vma->vm_file->निजी_data;
	काष्ठा rdma_umap_priv *priv = vma->vm_निजी_data;

	अगर (!priv)
		वापस;

	/*
	 * The vma holds a reference on the काष्ठा file that created it, which
	 * in turn means that the ib_uverbs_file is guaranteed to exist at
	 * this poपूर्णांक.
	 */
	mutex_lock(&ufile->umap_lock);
	अगर (priv->entry)
		rdma_user_mmap_entry_put(priv->entry);

	list_del(&priv->list);
	mutex_unlock(&ufile->umap_lock);
	kमुक्त(priv);
पूर्ण

/*
 * Once the zap_vma_ptes has been called touches to the VMA will come here and
 * we वापस a dummy writable zero page क्रम all the pfns.
 */
अटल vm_fault_t rdma_umap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा ib_uverbs_file *ufile = vmf->vma->vm_file->निजी_data;
	काष्ठा rdma_umap_priv *priv = vmf->vma->vm_निजी_data;
	vm_fault_t ret = 0;

	अगर (!priv)
		वापस VM_FAULT_SIGBUS;

	/* Read only pages can just use the प्रणाली zero page. */
	अगर (!(vmf->vma->vm_flags & (VM_WRITE | VM_MAYWRITE))) अणु
		vmf->page = ZERO_PAGE(vmf->address);
		get_page(vmf->page);
		वापस 0;
	पूर्ण

	mutex_lock(&ufile->umap_lock);
	अगर (!ufile->disassociate_page)
		ufile->disassociate_page =
			alloc_pages(vmf->gfp_mask | __GFP_ZERO, 0);

	अगर (ufile->disassociate_page) अणु
		/*
		 * This VMA is क्रमced to always be shared so this करोesn't have
		 * to worry about COW.
		 */
		vmf->page = ufile->disassociate_page;
		get_page(vmf->page);
	पूर्ण अन्यथा अणु
		ret = VM_FAULT_SIGBUS;
	पूर्ण
	mutex_unlock(&ufile->umap_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा rdma_umap_ops = अणु
	.खोलो = rdma_umap_खोलो,
	.बंद = rdma_umap_बंद,
	.fault = rdma_umap_fault,
पूर्ण;

व्योम uverbs_user_mmap_disassociate(काष्ठा ib_uverbs_file *ufile)
अणु
	काष्ठा rdma_umap_priv *priv, *next_priv;

	lockdep_निश्चित_held(&ufile->hw_destroy_rwsem);

	जबतक (1) अणु
		काष्ठा mm_काष्ठा *mm = शून्य;

		/* Get an arbitrary mm poपूर्णांकer that hasn't been cleaned yet */
		mutex_lock(&ufile->umap_lock);
		जबतक (!list_empty(&ufile->umaps)) अणु
			पूर्णांक ret;

			priv = list_first_entry(&ufile->umaps,
						काष्ठा rdma_umap_priv, list);
			mm = priv->vma->vm_mm;
			ret = mmget_not_zero(mm);
			अगर (!ret) अणु
				list_del_init(&priv->list);
				अगर (priv->entry) अणु
					rdma_user_mmap_entry_put(priv->entry);
					priv->entry = शून्य;
				पूर्ण
				mm = शून्य;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण
		mutex_unlock(&ufile->umap_lock);
		अगर (!mm)
			वापस;

		/*
		 * The umap_lock is nested under mmap_lock since it used within
		 * the vma_ops callbacks, so we have to clean the list one mm
		 * at a समय to get the lock ordering right. Typically there
		 * will only be one mm, so no big deal.
		 */
		mmap_पढ़ो_lock(mm);
		mutex_lock(&ufile->umap_lock);
		list_क्रम_each_entry_safe (priv, next_priv, &ufile->umaps,
					  list) अणु
			काष्ठा vm_area_काष्ठा *vma = priv->vma;

			अगर (vma->vm_mm != mm)
				जारी;
			list_del_init(&priv->list);

			zap_vma_ptes(vma, vma->vm_start,
				     vma->vm_end - vma->vm_start);

			अगर (priv->entry) अणु
				rdma_user_mmap_entry_put(priv->entry);
				priv->entry = शून्य;
			पूर्ण
		पूर्ण
		mutex_unlock(&ufile->umap_lock);
		mmap_पढ़ो_unlock(mm);
		mmput(mm);
	पूर्ण
पूर्ण

/*
 * ib_uverbs_खोलो() करोes not need the BKL:
 *
 *  - the ib_uverbs_device काष्ठाures are properly reference counted and
 *    everything अन्यथा is purely local to the file being created, so
 *    races against other खोलो calls are not a problem;
 *  - there is no ioctl method to race against;
 *  - the खोलो method will either immediately run -ENXIO, or all
 *    required initialization will be करोne.
 */
अटल पूर्णांक ib_uverbs_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ib_uverbs_device *dev;
	काष्ठा ib_uverbs_file *file;
	काष्ठा ib_device *ib_dev;
	पूर्णांक ret;
	पूर्णांक module_dependent;
	पूर्णांक srcu_key;

	dev = container_of(inode->i_cdev, काष्ठा ib_uverbs_device, cdev);
	अगर (!atomic_inc_not_zero(&dev->refcount))
		वापस -ENXIO;

	get_device(&dev->dev);
	srcu_key = srcu_पढ़ो_lock(&dev->disassociate_srcu);
	mutex_lock(&dev->lists_mutex);
	ib_dev = srcu_dereference(dev->ib_dev,
				  &dev->disassociate_srcu);
	अगर (!ib_dev) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण

	अगर (!rdma_dev_access_netns(ib_dev, current->nsproxy->net_ns)) अणु
		ret = -EPERM;
		जाओ err;
	पूर्ण

	/* In हाल IB device supports disassociate ucontext, there is no hard
	 * dependency between uverbs device and its low level device.
	 */
	module_dependent = !(ib_dev->ops.disassociate_ucontext);

	अगर (module_dependent) अणु
		अगर (!try_module_get(ib_dev->ops.owner)) अणु
			ret = -ENODEV;
			जाओ err;
		पूर्ण
	पूर्ण

	file = kzalloc(माप(*file), GFP_KERNEL);
	अगर (!file) अणु
		ret = -ENOMEM;
		अगर (module_dependent)
			जाओ err_module;

		जाओ err;
	पूर्ण

	file->device	 = dev;
	kref_init(&file->ref);
	mutex_init(&file->ucontext_lock);

	spin_lock_init(&file->uobjects_lock);
	INIT_LIST_HEAD(&file->uobjects);
	init_rwsem(&file->hw_destroy_rwsem);
	mutex_init(&file->umap_lock);
	INIT_LIST_HEAD(&file->umaps);

	filp->निजी_data = file;
	list_add_tail(&file->list, &dev->uverbs_file_list);
	mutex_unlock(&dev->lists_mutex);
	srcu_पढ़ो_unlock(&dev->disassociate_srcu, srcu_key);

	setup_ufile_idr_uobject(file);

	वापस stream_खोलो(inode, filp);

err_module:
	module_put(ib_dev->ops.owner);

err:
	mutex_unlock(&dev->lists_mutex);
	srcu_पढ़ो_unlock(&dev->disassociate_srcu, srcu_key);
	अगर (atomic_dec_and_test(&dev->refcount))
		ib_uverbs_comp_dev(dev);

	put_device(&dev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ib_uverbs_file *file = filp->निजी_data;

	uverbs_destroy_ufile_hw(file, RDMA_REMOVE_CLOSE);

	mutex_lock(&file->device->lists_mutex);
	list_del_init(&file->list);
	mutex_unlock(&file->device->lists_mutex);

	kref_put(&file->ref, ib_uverbs_release_file);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations uverbs_fops = अणु
	.owner	 = THIS_MODULE,
	.ग_लिखो	 = ib_uverbs_ग_लिखो,
	.खोलो	 = ib_uverbs_खोलो,
	.release = ib_uverbs_बंद,
	.llseek	 = no_llseek,
	.unlocked_ioctl = ib_uverbs_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;

अटल स्थिर काष्ठा file_operations uverbs_mmap_fops = अणु
	.owner	 = THIS_MODULE,
	.ग_लिखो	 = ib_uverbs_ग_लिखो,
	.mmap    = ib_uverbs_mmap,
	.खोलो	 = ib_uverbs_खोलो,
	.release = ib_uverbs_बंद,
	.llseek	 = no_llseek,
	.unlocked_ioctl = ib_uverbs_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;

अटल पूर्णांक ib_uverbs_get_nl_info(काष्ठा ib_device *ibdev, व्योम *client_data,
				 काष्ठा ib_client_nl_info *res)
अणु
	काष्ठा ib_uverbs_device *uverbs_dev = client_data;
	पूर्णांक ret;

	अगर (res->port != -1)
		वापस -EINVAL;

	res->abi = ibdev->ops.uverbs_abi_ver;
	res->cdev = &uverbs_dev->dev;

	/*
	 * To support DRIVER_ID binding in userspace some of the driver need
	 * upgrading to expose their PCI dependent revision inक्रमmation
	 * through get_context instead of relying on modalias matching. When
	 * the drivers are fixed they can drop this flag.
	 */
	अगर (!ibdev->ops.uverbs_no_driver_id_binding) अणु
		ret = nla_put_u32(res->nl_msg, RDMA_NLDEV_ATTR_UVERBS_DRIVER_ID,
				  ibdev->ops.driver_id);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा ib_client uverbs_client = अणु
	.name   = "uverbs",
	.no_kverbs_req = true,
	.add    = ib_uverbs_add_one,
	.हटाओ = ib_uverbs_हटाओ_one,
	.get_nl_info = ib_uverbs_get_nl_info,
पूर्ण;
MODULE_ALIAS_RDMA_CLIENT("uverbs");

अटल sमाप_प्रकार ibdev_show(काष्ठा device *device, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा ib_uverbs_device *dev =
			container_of(device, काष्ठा ib_uverbs_device, dev);
	पूर्णांक ret = -ENODEV;
	पूर्णांक srcu_key;
	काष्ठा ib_device *ib_dev;

	srcu_key = srcu_पढ़ो_lock(&dev->disassociate_srcu);
	ib_dev = srcu_dereference(dev->ib_dev, &dev->disassociate_srcu);
	अगर (ib_dev)
		ret = sysfs_emit(buf, "%s\n", dev_name(&ib_dev->dev));
	srcu_पढ़ो_unlock(&dev->disassociate_srcu, srcu_key);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(ibdev);

अटल sमाप_प्रकार abi_version_show(काष्ठा device *device,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ib_uverbs_device *dev =
			container_of(device, काष्ठा ib_uverbs_device, dev);
	पूर्णांक ret = -ENODEV;
	पूर्णांक srcu_key;
	काष्ठा ib_device *ib_dev;

	srcu_key = srcu_पढ़ो_lock(&dev->disassociate_srcu);
	ib_dev = srcu_dereference(dev->ib_dev, &dev->disassociate_srcu);
	अगर (ib_dev)
		ret = sysfs_emit(buf, "%u\n", ib_dev->ops.uverbs_abi_ver);
	srcu_पढ़ो_unlock(&dev->disassociate_srcu, srcu_key);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(abi_version);

अटल काष्ठा attribute *ib_dev_attrs[] = अणु
	&dev_attr_abi_version.attr,
	&dev_attr_ibdev.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dev_attr_group = अणु
	.attrs = ib_dev_attrs,
पूर्ण;

अटल CLASS_ATTR_STRING(abi_version, S_IRUGO,
			 __stringअगरy(IB_USER_VERBS_ABI_VERSION));

अटल पूर्णांक ib_uverbs_create_uapi(काष्ठा ib_device *device,
				 काष्ठा ib_uverbs_device *uverbs_dev)
अणु
	काष्ठा uverbs_api *uapi;

	uapi = uverbs_alloc_api(device);
	अगर (IS_ERR(uapi))
		वापस PTR_ERR(uapi);

	uverbs_dev->uapi = uapi;
	वापस 0;
पूर्ण

अटल पूर्णांक ib_uverbs_add_one(काष्ठा ib_device *device)
अणु
	पूर्णांक devnum;
	dev_t base;
	काष्ठा ib_uverbs_device *uverbs_dev;
	पूर्णांक ret;

	अगर (!device->ops.alloc_ucontext)
		वापस -EOPNOTSUPP;

	uverbs_dev = kzalloc(माप(*uverbs_dev), GFP_KERNEL);
	अगर (!uverbs_dev)
		वापस -ENOMEM;

	ret = init_srcu_काष्ठा(&uverbs_dev->disassociate_srcu);
	अगर (ret) अणु
		kमुक्त(uverbs_dev);
		वापस -ENOMEM;
	पूर्ण

	device_initialize(&uverbs_dev->dev);
	uverbs_dev->dev.class = uverbs_class;
	uverbs_dev->dev.parent = device->dev.parent;
	uverbs_dev->dev.release = ib_uverbs_release_dev;
	uverbs_dev->groups[0] = &dev_attr_group;
	uverbs_dev->dev.groups = uverbs_dev->groups;
	atomic_set(&uverbs_dev->refcount, 1);
	init_completion(&uverbs_dev->comp);
	uverbs_dev->xrcd_tree = RB_ROOT;
	mutex_init(&uverbs_dev->xrcd_tree_mutex);
	mutex_init(&uverbs_dev->lists_mutex);
	INIT_LIST_HEAD(&uverbs_dev->uverbs_file_list);
	rcu_assign_poपूर्णांकer(uverbs_dev->ib_dev, device);
	uverbs_dev->num_comp_vectors = device->num_comp_vectors;

	devnum = ida_alloc_max(&uverbs_ida, IB_UVERBS_MAX_DEVICES - 1,
			       GFP_KERNEL);
	अगर (devnum < 0) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	uverbs_dev->devnum = devnum;
	अगर (devnum >= IB_UVERBS_NUM_FIXED_MINOR)
		base = dynamic_uverbs_dev + devnum - IB_UVERBS_NUM_FIXED_MINOR;
	अन्यथा
		base = IB_UVERBS_BASE_DEV + devnum;

	ret = ib_uverbs_create_uapi(device, uverbs_dev);
	अगर (ret)
		जाओ err_uapi;

	uverbs_dev->dev.devt = base;
	dev_set_name(&uverbs_dev->dev, "uverbs%d", uverbs_dev->devnum);

	cdev_init(&uverbs_dev->cdev,
		  device->ops.mmap ? &uverbs_mmap_fops : &uverbs_fops);
	uverbs_dev->cdev.owner = THIS_MODULE;

	ret = cdev_device_add(&uverbs_dev->cdev, &uverbs_dev->dev);
	अगर (ret)
		जाओ err_uapi;

	ib_set_client_data(device, &uverbs_client, uverbs_dev);
	वापस 0;

err_uapi:
	ida_मुक्त(&uverbs_ida, devnum);
err:
	अगर (atomic_dec_and_test(&uverbs_dev->refcount))
		ib_uverbs_comp_dev(uverbs_dev);
	रुको_क्रम_completion(&uverbs_dev->comp);
	put_device(&uverbs_dev->dev);
	वापस ret;
पूर्ण

अटल व्योम ib_uverbs_मुक्त_hw_resources(काष्ठा ib_uverbs_device *uverbs_dev,
					काष्ठा ib_device *ib_dev)
अणु
	काष्ठा ib_uverbs_file *file;

	/* Pending running commands to terminate */
	uverbs_disassociate_api_pre(uverbs_dev);

	mutex_lock(&uverbs_dev->lists_mutex);
	जबतक (!list_empty(&uverbs_dev->uverbs_file_list)) अणु
		file = list_first_entry(&uverbs_dev->uverbs_file_list,
					काष्ठा ib_uverbs_file, list);
		list_del_init(&file->list);
		kref_get(&file->ref);

		/* We must release the mutex beक्रमe going ahead and calling
		 * uverbs_cleanup_ufile, as it might end up indirectly calling
		 * uverbs_बंद, क्रम example due to मुक्तing the resources (e.g
		 * mmput).
		 */
		mutex_unlock(&uverbs_dev->lists_mutex);

		uverbs_destroy_ufile_hw(file, RDMA_REMOVE_DRIVER_REMOVE);
		kref_put(&file->ref, ib_uverbs_release_file);

		mutex_lock(&uverbs_dev->lists_mutex);
	पूर्ण
	mutex_unlock(&uverbs_dev->lists_mutex);

	uverbs_disassociate_api(uverbs_dev->uapi);
पूर्ण

अटल व्योम ib_uverbs_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data)
अणु
	काष्ठा ib_uverbs_device *uverbs_dev = client_data;
	पूर्णांक रुको_clients = 1;

	cdev_device_del(&uverbs_dev->cdev, &uverbs_dev->dev);
	ida_मुक्त(&uverbs_ida, uverbs_dev->devnum);

	अगर (device->ops.disassociate_ucontext) अणु
		/* We disassociate HW resources and immediately वापस.
		 * Userspace will see a EIO त्रुटि_सं क्रम all future access.
		 * Upon वापसing, ib_device may be मुक्तd पूर्णांकernally and is not
		 * valid any more.
		 * uverbs_device is still available until all clients बंद
		 * their files, then the uverbs device ref count will be zero
		 * and its resources will be मुक्तd.
		 * Note: At this poपूर्णांक no more files can be खोलोed since the
		 * cdev was deleted, however active clients can still issue
		 * commands and बंद their खोलो files.
		 */
		ib_uverbs_मुक्त_hw_resources(uverbs_dev, device);
		रुको_clients = 0;
	पूर्ण

	अगर (atomic_dec_and_test(&uverbs_dev->refcount))
		ib_uverbs_comp_dev(uverbs_dev);
	अगर (रुको_clients)
		रुको_क्रम_completion(&uverbs_dev->comp);

	put_device(&uverbs_dev->dev);
पूर्ण

अटल अक्षर *uverbs_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	अगर (mode)
		*mode = 0666;
	वापस kaप्र_लिखो(GFP_KERNEL, "infiniband/%s", dev_name(dev));
पूर्ण

अटल पूर्णांक __init ib_uverbs_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_chrdev_region(IB_UVERBS_BASE_DEV,
				     IB_UVERBS_NUM_FIXED_MINOR,
				     "infiniband_verbs");
	अगर (ret) अणु
		pr_err("user_verbs: couldn't register device number\n");
		जाओ out;
	पूर्ण

	ret = alloc_chrdev_region(&dynamic_uverbs_dev, 0,
				  IB_UVERBS_NUM_DYNAMIC_MINOR,
				  "infiniband_verbs");
	अगर (ret) अणु
		pr_err("couldn't register dynamic device number\n");
		जाओ out_alloc;
	पूर्ण

	uverbs_class = class_create(THIS_MODULE, "infiniband_verbs");
	अगर (IS_ERR(uverbs_class)) अणु
		ret = PTR_ERR(uverbs_class);
		pr_err("user_verbs: couldn't create class infiniband_verbs\n");
		जाओ out_chrdev;
	पूर्ण

	uverbs_class->devnode = uverbs_devnode;

	ret = class_create_file(uverbs_class, &class_attr_abi_version.attr);
	अगर (ret) अणु
		pr_err("user_verbs: couldn't create abi_version attribute\n");
		जाओ out_class;
	पूर्ण

	ret = ib_रेजिस्टर_client(&uverbs_client);
	अगर (ret) अणु
		pr_err("user_verbs: couldn't register client\n");
		जाओ out_class;
	पूर्ण

	वापस 0;

out_class:
	class_destroy(uverbs_class);

out_chrdev:
	unरेजिस्टर_chrdev_region(dynamic_uverbs_dev,
				 IB_UVERBS_NUM_DYNAMIC_MINOR);

out_alloc:
	unरेजिस्टर_chrdev_region(IB_UVERBS_BASE_DEV,
				 IB_UVERBS_NUM_FIXED_MINOR);

out:
	वापस ret;
पूर्ण

अटल व्योम __निकास ib_uverbs_cleanup(व्योम)
अणु
	ib_unरेजिस्टर_client(&uverbs_client);
	class_destroy(uverbs_class);
	unरेजिस्टर_chrdev_region(IB_UVERBS_BASE_DEV,
				 IB_UVERBS_NUM_FIXED_MINOR);
	unरेजिस्टर_chrdev_region(dynamic_uverbs_dev,
				 IB_UVERBS_NUM_DYNAMIC_MINOR);
	mmu_notअगरier_synchronize();
पूर्ण

module_init(ib_uverbs_init);
module_निकास(ib_uverbs_cleanup);
