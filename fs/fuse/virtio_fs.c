<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * virtio-fs: Virtio Fileप्रणाली
 * Copyright (C) 2018 Red Hat, Inc.
 */

#समावेश <linux/fs.h>
#समावेश <linux/dax.h>
#समावेश <linux/pci.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/module.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/uपन.स>
#समावेश "fuse_i.h"

/* Used to help calculate the FUSE connection's max_pages limit for a request's
 * size. Parts of the काष्ठा fuse_req are sliced पूर्णांकo scattergather lists in
 * addition to the pages used, so this can help account क्रम that overhead.
 */
#घोषणा FUSE_HEADER_OVERHEAD    4

/* List of virtio-fs device instances and a lock क्रम the list. Also provides
 * mutual exclusion in device removal and mounting path
 */
अटल DEFINE_MUTEX(virtio_fs_mutex);
अटल LIST_HEAD(virtio_fs_instances);

क्रमागत अणु
	VQ_HIPRIO,
	VQ_REQUEST
पूर्ण;

#घोषणा VQ_NAME_LEN	24

/* Per-virtqueue state */
काष्ठा virtio_fs_vq अणु
	spinlock_t lock;
	काष्ठा virtqueue *vq;     /* रक्षित by ->lock */
	काष्ठा work_काष्ठा करोne_work;
	काष्ठा list_head queued_reqs;
	काष्ठा list_head end_reqs;	/* End these requests */
	काष्ठा delayed_work dispatch_work;
	काष्ठा fuse_dev *fud;
	bool connected;
	दीर्घ in_flight;
	काष्ठा completion in_flight_zero; /* No inflight requests */
	अक्षर name[VQ_NAME_LEN];
पूर्ण ____cacheline_aligned_in_smp;

/* A virtio-fs device instance */
काष्ठा virtio_fs अणु
	काष्ठा kref refcount;
	काष्ठा list_head list;    /* on virtio_fs_instances */
	अक्षर *tag;
	काष्ठा virtio_fs_vq *vqs;
	अचिन्हित पूर्णांक nvqs;               /* number of virtqueues */
	अचिन्हित पूर्णांक num_request_queues; /* number of request queues */
	काष्ठा dax_device *dax_dev;

	/* DAX memory winकरोw where file contents are mapped */
	व्योम *winकरोw_kaddr;
	phys_addr_t winकरोw_phys_addr;
	माप_प्रकार winकरोw_len;
पूर्ण;

काष्ठा virtio_fs_क्रमget_req अणु
	काष्ठा fuse_in_header ih;
	काष्ठा fuse_क्रमget_in arg;
पूर्ण;

काष्ठा virtio_fs_क्रमget अणु
	/* This request can be temporarily queued on virt queue */
	काष्ठा list_head list;
	काष्ठा virtio_fs_क्रमget_req req;
पूर्ण;

काष्ठा virtio_fs_req_work अणु
	काष्ठा fuse_req *req;
	काष्ठा virtio_fs_vq *fsvq;
	काष्ठा work_काष्ठा करोne_work;
पूर्ण;

अटल पूर्णांक virtio_fs_enqueue_req(काष्ठा virtio_fs_vq *fsvq,
				 काष्ठा fuse_req *req, bool in_flight);

क्रमागत अणु
	OPT_DAX,
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec virtio_fs_parameters[] = अणु
	fsparam_flag("dax", OPT_DAX),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक virtio_fs_parse_param(काष्ठा fs_context *fc,
				 काष्ठा fs_parameter *param)
अणु
	काष्ठा fs_parse_result result;
	काष्ठा fuse_fs_context *ctx = fc->fs_निजी;
	पूर्णांक opt;

	opt = fs_parse(fc, virtio_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल OPT_DAX:
		ctx->dax = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम virtio_fs_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	काष्ठा fuse_fs_context *ctx = fc->fs_निजी;

	kमुक्त(ctx);
पूर्ण

अटल अंतरभूत काष्ठा virtio_fs_vq *vq_to_fsvq(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_fs *fs = vq->vdev->priv;

	वापस &fs->vqs[vq->index];
पूर्ण

/* Should be called with fsvq->lock held. */
अटल अंतरभूत व्योम inc_in_flight_req(काष्ठा virtio_fs_vq *fsvq)
अणु
	fsvq->in_flight++;
पूर्ण

/* Should be called with fsvq->lock held. */
अटल अंतरभूत व्योम dec_in_flight_req(काष्ठा virtio_fs_vq *fsvq)
अणु
	WARN_ON(fsvq->in_flight <= 0);
	fsvq->in_flight--;
	अगर (!fsvq->in_flight)
		complete(&fsvq->in_flight_zero);
पूर्ण

अटल व्योम release_virtio_fs_obj(काष्ठा kref *ref)
अणु
	काष्ठा virtio_fs *vfs = container_of(ref, काष्ठा virtio_fs, refcount);

	kमुक्त(vfs->vqs);
	kमुक्त(vfs);
पूर्ण

/* Make sure virtiofs_mutex is held */
अटल व्योम virtio_fs_put(काष्ठा virtio_fs *fs)
अणु
	kref_put(&fs->refcount, release_virtio_fs_obj);
पूर्ण

अटल व्योम virtio_fs_fiq_release(काष्ठा fuse_iqueue *fiq)
अणु
	काष्ठा virtio_fs *vfs = fiq->priv;

	mutex_lock(&virtio_fs_mutex);
	virtio_fs_put(vfs);
	mutex_unlock(&virtio_fs_mutex);
पूर्ण

अटल व्योम virtio_fs_drain_queue(काष्ठा virtio_fs_vq *fsvq)
अणु
	WARN_ON(fsvq->in_flight < 0);

	/* Wait क्रम in flight requests to finish.*/
	spin_lock(&fsvq->lock);
	अगर (fsvq->in_flight) अणु
		/* We are holding virtio_fs_mutex. There should not be any
		 * रुकोers रुकोing क्रम completion.
		 */
		reinit_completion(&fsvq->in_flight_zero);
		spin_unlock(&fsvq->lock);
		रुको_क्रम_completion(&fsvq->in_flight_zero);
	पूर्ण अन्यथा अणु
		spin_unlock(&fsvq->lock);
	पूर्ण

	flush_work(&fsvq->करोne_work);
	flush_delayed_work(&fsvq->dispatch_work);
पूर्ण

अटल व्योम virtio_fs_drain_all_queues_locked(काष्ठा virtio_fs *fs)
अणु
	काष्ठा virtio_fs_vq *fsvq;
	पूर्णांक i;

	क्रम (i = 0; i < fs->nvqs; i++) अणु
		fsvq = &fs->vqs[i];
		virtio_fs_drain_queue(fsvq);
	पूर्ण
पूर्ण

अटल व्योम virtio_fs_drain_all_queues(काष्ठा virtio_fs *fs)
अणु
	/* Provides mutual exclusion between ->हटाओ and ->समाप्त_sb
	 * paths. We करोn't want both of these draining queue at the
	 * same समय. Current completion logic reinits completion
	 * and that means there should not be any other thपढ़ो
	 * करोing reinit or रुकोing क्रम completion alपढ़ोy.
	 */
	mutex_lock(&virtio_fs_mutex);
	virtio_fs_drain_all_queues_locked(fs);
	mutex_unlock(&virtio_fs_mutex);
पूर्ण

अटल व्योम virtio_fs_start_all_queues(काष्ठा virtio_fs *fs)
अणु
	काष्ठा virtio_fs_vq *fsvq;
	पूर्णांक i;

	क्रम (i = 0; i < fs->nvqs; i++) अणु
		fsvq = &fs->vqs[i];
		spin_lock(&fsvq->lock);
		fsvq->connected = true;
		spin_unlock(&fsvq->lock);
	पूर्ण
पूर्ण

/* Add a new instance to the list or वापस -EEXIST अगर tag name exists*/
अटल पूर्णांक virtio_fs_add_instance(काष्ठा virtio_fs *fs)
अणु
	काष्ठा virtio_fs *fs2;
	bool duplicate = false;

	mutex_lock(&virtio_fs_mutex);

	list_क्रम_each_entry(fs2, &virtio_fs_instances, list) अणु
		अगर (म_भेद(fs->tag, fs2->tag) == 0)
			duplicate = true;
	पूर्ण

	अगर (!duplicate)
		list_add_tail(&fs->list, &virtio_fs_instances);

	mutex_unlock(&virtio_fs_mutex);

	अगर (duplicate)
		वापस -EEXIST;
	वापस 0;
पूर्ण

/* Return the virtio_fs with a given tag, or शून्य */
अटल काष्ठा virtio_fs *virtio_fs_find_instance(स्थिर अक्षर *tag)
अणु
	काष्ठा virtio_fs *fs;

	mutex_lock(&virtio_fs_mutex);

	list_क्रम_each_entry(fs, &virtio_fs_instances, list) अणु
		अगर (म_भेद(fs->tag, tag) == 0) अणु
			kref_get(&fs->refcount);
			जाओ found;
		पूर्ण
	पूर्ण

	fs = शून्य; /* not found */

found:
	mutex_unlock(&virtio_fs_mutex);

	वापस fs;
पूर्ण

अटल व्योम virtio_fs_मुक्त_devs(काष्ठा virtio_fs *fs)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < fs->nvqs; i++) अणु
		काष्ठा virtio_fs_vq *fsvq = &fs->vqs[i];

		अगर (!fsvq->fud)
			जारी;

		fuse_dev_मुक्त(fsvq->fud);
		fsvq->fud = शून्य;
	पूर्ण
पूर्ण

/* Read fileप्रणाली name from virtio config पूर्णांकo fs->tag (must kमुक्त()). */
अटल पूर्णांक virtio_fs_पढ़ो_tag(काष्ठा virtio_device *vdev, काष्ठा virtio_fs *fs)
अणु
	अक्षर tag_buf[माप_field(काष्ठा virtio_fs_config, tag)];
	अक्षर *end;
	माप_प्रकार len;

	virtio_cपढ़ो_bytes(vdev, दुरत्व(काष्ठा virtio_fs_config, tag),
			   &tag_buf, माप(tag_buf));
	end = स_प्रथम(tag_buf, '\0', माप(tag_buf));
	अगर (end == tag_buf)
		वापस -EINVAL; /* empty tag */
	अगर (!end)
		end = &tag_buf[माप(tag_buf)];

	len = end - tag_buf;
	fs->tag = devm_kदो_स्मृति(&vdev->dev, len + 1, GFP_KERNEL);
	अगर (!fs->tag)
		वापस -ENOMEM;
	स_नकल(fs->tag, tag_buf, len);
	fs->tag[len] = '\0';
	वापस 0;
पूर्ण

/* Work function क्रम hiprio completion */
अटल व्योम virtio_fs_hiprio_करोne_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_fs_vq *fsvq = container_of(work, काष्ठा virtio_fs_vq,
						 करोne_work);
	काष्ठा virtqueue *vq = fsvq->vq;

	/* Free completed FUSE_FORGET requests */
	spin_lock(&fsvq->lock);
	करो अणु
		अचिन्हित पूर्णांक len;
		व्योम *req;

		virtqueue_disable_cb(vq);

		जबतक ((req = virtqueue_get_buf(vq, &len)) != शून्य) अणु
			kमुक्त(req);
			dec_in_flight_req(fsvq);
		पूर्ण
	पूर्ण जबतक (!virtqueue_enable_cb(vq) && likely(!virtqueue_is_broken(vq)));
	spin_unlock(&fsvq->lock);
पूर्ण

अटल व्योम virtio_fs_request_dispatch_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fuse_req *req;
	काष्ठा virtio_fs_vq *fsvq = container_of(work, काष्ठा virtio_fs_vq,
						 dispatch_work.work);
	पूर्णांक ret;

	pr_debug("virtio-fs: worker %s called.\n", __func__);
	जबतक (1) अणु
		spin_lock(&fsvq->lock);
		req = list_first_entry_or_null(&fsvq->end_reqs, काष्ठा fuse_req,
					       list);
		अगर (!req) अणु
			spin_unlock(&fsvq->lock);
			अवरोध;
		पूर्ण

		list_del_init(&req->list);
		spin_unlock(&fsvq->lock);
		fuse_request_end(req);
	पूर्ण

	/* Dispatch pending requests */
	जबतक (1) अणु
		spin_lock(&fsvq->lock);
		req = list_first_entry_or_null(&fsvq->queued_reqs,
					       काष्ठा fuse_req, list);
		अगर (!req) अणु
			spin_unlock(&fsvq->lock);
			वापस;
		पूर्ण
		list_del_init(&req->list);
		spin_unlock(&fsvq->lock);

		ret = virtio_fs_enqueue_req(fsvq, req, true);
		अगर (ret < 0) अणु
			अगर (ret == -ENOMEM || ret == -ENOSPC) अणु
				spin_lock(&fsvq->lock);
				list_add_tail(&req->list, &fsvq->queued_reqs);
				schedule_delayed_work(&fsvq->dispatch_work,
						      msecs_to_jअगरfies(1));
				spin_unlock(&fsvq->lock);
				वापस;
			पूर्ण
			req->out.h.error = ret;
			spin_lock(&fsvq->lock);
			dec_in_flight_req(fsvq);
			spin_unlock(&fsvq->lock);
			pr_err("virtio-fs: virtio_fs_enqueue_req() failed %d\n",
			       ret);
			fuse_request_end(req);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Returns 1 अगर queue is full and sender should रुको a bit beक्रमe sending
 * next request, 0 otherwise.
 */
अटल पूर्णांक send_क्रमget_request(काष्ठा virtio_fs_vq *fsvq,
			       काष्ठा virtio_fs_क्रमget *क्रमget,
			       bool in_flight)
अणु
	काष्ठा scatterlist sg;
	काष्ठा virtqueue *vq;
	पूर्णांक ret = 0;
	bool notअगरy;
	काष्ठा virtio_fs_क्रमget_req *req = &क्रमget->req;

	spin_lock(&fsvq->lock);
	अगर (!fsvq->connected) अणु
		अगर (in_flight)
			dec_in_flight_req(fsvq);
		kमुक्त(क्रमget);
		जाओ out;
	पूर्ण

	sg_init_one(&sg, req, माप(*req));
	vq = fsvq->vq;
	dev_dbg(&vq->vdev->dev, "%s\n", __func__);

	ret = virtqueue_add_outbuf(vq, &sg, 1, क्रमget, GFP_ATOMIC);
	अगर (ret < 0) अणु
		अगर (ret == -ENOMEM || ret == -ENOSPC) अणु
			pr_debug("virtio-fs: Could not queue FORGET: err=%d. Will try later\n",
				 ret);
			list_add_tail(&क्रमget->list, &fsvq->queued_reqs);
			schedule_delayed_work(&fsvq->dispatch_work,
					      msecs_to_jअगरfies(1));
			अगर (!in_flight)
				inc_in_flight_req(fsvq);
			/* Queue is full */
			ret = 1;
		पूर्ण अन्यथा अणु
			pr_debug("virtio-fs: Could not queue FORGET: err=%d. Dropping it.\n",
				 ret);
			kमुक्त(क्रमget);
			अगर (in_flight)
				dec_in_flight_req(fsvq);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (!in_flight)
		inc_in_flight_req(fsvq);
	notअगरy = virtqueue_kick_prepare(vq);
	spin_unlock(&fsvq->lock);

	अगर (notअगरy)
		virtqueue_notअगरy(vq);
	वापस ret;
out:
	spin_unlock(&fsvq->lock);
	वापस ret;
पूर्ण

अटल व्योम virtio_fs_hiprio_dispatch_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_fs_क्रमget *क्रमget;
	काष्ठा virtio_fs_vq *fsvq = container_of(work, काष्ठा virtio_fs_vq,
						 dispatch_work.work);
	pr_debug("virtio-fs: worker %s called.\n", __func__);
	जबतक (1) अणु
		spin_lock(&fsvq->lock);
		क्रमget = list_first_entry_or_null(&fsvq->queued_reqs,
					काष्ठा virtio_fs_क्रमget, list);
		अगर (!क्रमget) अणु
			spin_unlock(&fsvq->lock);
			वापस;
		पूर्ण

		list_del(&क्रमget->list);
		spin_unlock(&fsvq->lock);
		अगर (send_क्रमget_request(fsvq, क्रमget, true))
			वापस;
	पूर्ण
पूर्ण

/* Allocate and copy args पूर्णांकo req->argbuf */
अटल पूर्णांक copy_args_to_argbuf(काष्ठा fuse_req *req)
अणु
	काष्ठा fuse_args *args = req->args;
	अचिन्हित पूर्णांक offset = 0;
	अचिन्हित पूर्णांक num_in;
	अचिन्हित पूर्णांक num_out;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक i;

	num_in = args->in_numargs - args->in_pages;
	num_out = args->out_numargs - args->out_pages;
	len = fuse_len_args(num_in, (काष्ठा fuse_arg *) args->in_args) +
	      fuse_len_args(num_out, args->out_args);

	req->argbuf = kदो_स्मृति(len, GFP_ATOMIC);
	अगर (!req->argbuf)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_in; i++) अणु
		स_नकल(req->argbuf + offset,
		       args->in_args[i].value,
		       args->in_args[i].size);
		offset += args->in_args[i].size;
	पूर्ण

	वापस 0;
पूर्ण

/* Copy args out of and मुक्त req->argbuf */
अटल व्योम copy_args_from_argbuf(काष्ठा fuse_args *args, काष्ठा fuse_req *req)
अणु
	अचिन्हित पूर्णांक reमुख्यing;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक num_in;
	अचिन्हित पूर्णांक num_out;
	अचिन्हित पूर्णांक i;

	reमुख्यing = req->out.h.len - माप(req->out.h);
	num_in = args->in_numargs - args->in_pages;
	num_out = args->out_numargs - args->out_pages;
	offset = fuse_len_args(num_in, (काष्ठा fuse_arg *)args->in_args);

	क्रम (i = 0; i < num_out; i++) अणु
		अचिन्हित पूर्णांक argsize = args->out_args[i].size;

		अगर (args->out_argvar &&
		    i == args->out_numargs - 1 &&
		    argsize > reमुख्यing) अणु
			argsize = reमुख्यing;
		पूर्ण

		स_नकल(args->out_args[i].value, req->argbuf + offset, argsize);
		offset += argsize;

		अगर (i != args->out_numargs - 1)
			reमुख्यing -= argsize;
	पूर्ण

	/* Store the actual size of the variable-length arg */
	अगर (args->out_argvar)
		args->out_args[args->out_numargs - 1].size = reमुख्यing;

	kमुक्त(req->argbuf);
	req->argbuf = शून्य;
पूर्ण

/* Work function क्रम request completion */
अटल व्योम virtio_fs_request_complete(काष्ठा fuse_req *req,
				       काष्ठा virtio_fs_vq *fsvq)
अणु
	काष्ठा fuse_pqueue *fpq = &fsvq->fud->pq;
	काष्ठा fuse_args *args;
	काष्ठा fuse_args_pages *ap;
	अचिन्हित पूर्णांक len, i, thislen;
	काष्ठा page *page;

	/*
	 * TODO verअगरy that server properly follows FUSE protocol
	 * (oh.uniq, oh.len)
	 */
	args = req->args;
	copy_args_from_argbuf(args, req);

	अगर (args->out_pages && args->page_zeroing) अणु
		len = args->out_args[args->out_numargs - 1].size;
		ap = container_of(args, typeof(*ap), args);
		क्रम (i = 0; i < ap->num_pages; i++) अणु
			thislen = ap->descs[i].length;
			अगर (len < thislen) अणु
				WARN_ON(ap->descs[i].offset);
				page = ap->pages[i];
				zero_user_segment(page, len, thislen);
				len = 0;
			पूर्ण अन्यथा अणु
				len -= thislen;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock(&fpq->lock);
	clear_bit(FR_SENT, &req->flags);
	spin_unlock(&fpq->lock);

	fuse_request_end(req);
	spin_lock(&fsvq->lock);
	dec_in_flight_req(fsvq);
	spin_unlock(&fsvq->lock);
पूर्ण

अटल व्योम virtio_fs_complete_req_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_fs_req_work *w =
		container_of(work, typeof(*w), करोne_work);

	virtio_fs_request_complete(w->req, w->fsvq);
	kमुक्त(w);
पूर्ण

अटल व्योम virtio_fs_requests_करोne_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_fs_vq *fsvq = container_of(work, काष्ठा virtio_fs_vq,
						 करोne_work);
	काष्ठा fuse_pqueue *fpq = &fsvq->fud->pq;
	काष्ठा virtqueue *vq = fsvq->vq;
	काष्ठा fuse_req *req;
	काष्ठा fuse_req *next;
	अचिन्हित पूर्णांक len;
	LIST_HEAD(reqs);

	/* Collect completed requests off the virtqueue */
	spin_lock(&fsvq->lock);
	करो अणु
		virtqueue_disable_cb(vq);

		जबतक ((req = virtqueue_get_buf(vq, &len)) != शून्य) अणु
			spin_lock(&fpq->lock);
			list_move_tail(&req->list, &reqs);
			spin_unlock(&fpq->lock);
		पूर्ण
	पूर्ण जबतक (!virtqueue_enable_cb(vq) && likely(!virtqueue_is_broken(vq)));
	spin_unlock(&fsvq->lock);

	/* End requests */
	list_क्रम_each_entry_safe(req, next, &reqs, list) अणु
		list_del_init(&req->list);

		/* blocking async request completes in a worker context */
		अगर (req->args->may_block) अणु
			काष्ठा virtio_fs_req_work *w;

			w = kzalloc(माप(*w), GFP_NOFS | __GFP_NOFAIL);
			INIT_WORK(&w->करोne_work, virtio_fs_complete_req_work);
			w->fsvq = fsvq;
			w->req = req;
			schedule_work(&w->करोne_work);
		पूर्ण अन्यथा अणु
			virtio_fs_request_complete(req, fsvq);
		पूर्ण
	पूर्ण
पूर्ण

/* Virtqueue पूर्णांकerrupt handler */
अटल व्योम virtio_fs_vq_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_fs_vq *fsvq = vq_to_fsvq(vq);

	dev_dbg(&vq->vdev->dev, "%s %s\n", __func__, fsvq->name);

	schedule_work(&fsvq->करोne_work);
पूर्ण

अटल व्योम virtio_fs_init_vq(काष्ठा virtio_fs_vq *fsvq, अक्षर *name,
			      पूर्णांक vq_type)
अणु
	म_नकलन(fsvq->name, name, VQ_NAME_LEN);
	spin_lock_init(&fsvq->lock);
	INIT_LIST_HEAD(&fsvq->queued_reqs);
	INIT_LIST_HEAD(&fsvq->end_reqs);
	init_completion(&fsvq->in_flight_zero);

	अगर (vq_type == VQ_REQUEST) अणु
		INIT_WORK(&fsvq->करोne_work, virtio_fs_requests_करोne_work);
		INIT_DELAYED_WORK(&fsvq->dispatch_work,
				  virtio_fs_request_dispatch_work);
	पूर्ण अन्यथा अणु
		INIT_WORK(&fsvq->करोne_work, virtio_fs_hiprio_करोne_work);
		INIT_DELAYED_WORK(&fsvq->dispatch_work,
				  virtio_fs_hiprio_dispatch_work);
	पूर्ण
पूर्ण

/* Initialize virtqueues */
अटल पूर्णांक virtio_fs_setup_vqs(काष्ठा virtio_device *vdev,
			       काष्ठा virtio_fs *fs)
अणु
	काष्ठा virtqueue **vqs;
	vq_callback_t **callbacks;
	स्थिर अक्षर **names;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	virtio_cपढ़ो_le(vdev, काष्ठा virtio_fs_config, num_request_queues,
			&fs->num_request_queues);
	अगर (fs->num_request_queues == 0)
		वापस -EINVAL;

	fs->nvqs = VQ_REQUEST + fs->num_request_queues;
	fs->vqs = kसुस्मृति(fs->nvqs, माप(fs->vqs[VQ_HIPRIO]), GFP_KERNEL);
	अगर (!fs->vqs)
		वापस -ENOMEM;

	vqs = kदो_स्मृति_array(fs->nvqs, माप(vqs[VQ_HIPRIO]), GFP_KERNEL);
	callbacks = kदो_स्मृति_array(fs->nvqs, माप(callbacks[VQ_HIPRIO]),
					GFP_KERNEL);
	names = kदो_स्मृति_array(fs->nvqs, माप(names[VQ_HIPRIO]), GFP_KERNEL);
	अगर (!vqs || !callbacks || !names) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Initialize the hiprio/क्रमget request virtqueue */
	callbacks[VQ_HIPRIO] = virtio_fs_vq_करोne;
	virtio_fs_init_vq(&fs->vqs[VQ_HIPRIO], "hiprio", VQ_HIPRIO);
	names[VQ_HIPRIO] = fs->vqs[VQ_HIPRIO].name;

	/* Initialize the requests virtqueues */
	क्रम (i = VQ_REQUEST; i < fs->nvqs; i++) अणु
		अक्षर vq_name[VQ_NAME_LEN];

		snम_लिखो(vq_name, VQ_NAME_LEN, "requests.%u", i - VQ_REQUEST);
		virtio_fs_init_vq(&fs->vqs[i], vq_name, VQ_REQUEST);
		callbacks[i] = virtio_fs_vq_करोne;
		names[i] = fs->vqs[i].name;
	पूर्ण

	ret = virtio_find_vqs(vdev, fs->nvqs, vqs, callbacks, names, शून्य);
	अगर (ret < 0)
		जाओ out;

	क्रम (i = 0; i < fs->nvqs; i++)
		fs->vqs[i].vq = vqs[i];

	virtio_fs_start_all_queues(fs);
out:
	kमुक्त(names);
	kमुक्त(callbacks);
	kमुक्त(vqs);
	अगर (ret)
		kमुक्त(fs->vqs);
	वापस ret;
पूर्ण

/* Free virtqueues (device must alपढ़ोy be reset) */
अटल व्योम virtio_fs_cleanup_vqs(काष्ठा virtio_device *vdev,
				  काष्ठा virtio_fs *fs)
अणु
	vdev->config->del_vqs(vdev);
पूर्ण

/* Map a winकरोw offset to a page frame number.  The winकरोw offset will have
 * been produced by .iomap_begin(), which maps a file offset to a winकरोw
 * offset.
 */
अटल दीर्घ virtio_fs_direct_access(काष्ठा dax_device *dax_dev, pgoff_t pgoff,
				    दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn)
अणु
	काष्ठा virtio_fs *fs = dax_get_निजी(dax_dev);
	phys_addr_t offset = PFN_PHYS(pgoff);
	माप_प्रकार max_nr_pages = fs->winकरोw_len/PAGE_SIZE - pgoff;

	अगर (kaddr)
		*kaddr = fs->winकरोw_kaddr + offset;
	अगर (pfn)
		*pfn = phys_to_pfn_t(fs->winकरोw_phys_addr + offset,
					PFN_DEV | PFN_MAP);
	वापस nr_pages > max_nr_pages ? max_nr_pages : nr_pages;
पूर्ण

अटल माप_प्रकार virtio_fs_copy_from_iter(काष्ठा dax_device *dax_dev,
				       pgoff_t pgoff, व्योम *addr,
				       माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	वापस copy_from_iter(addr, bytes, i);
पूर्ण

अटल माप_प्रकार virtio_fs_copy_to_iter(काष्ठा dax_device *dax_dev,
				       pgoff_t pgoff, व्योम *addr,
				       माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	वापस copy_to_iter(addr, bytes, i);
पूर्ण

अटल पूर्णांक virtio_fs_zero_page_range(काष्ठा dax_device *dax_dev,
				     pgoff_t pgoff, माप_प्रकार nr_pages)
अणु
	दीर्घ rc;
	व्योम *kaddr;

	rc = dax_direct_access(dax_dev, pgoff, nr_pages, &kaddr, शून्य);
	अगर (rc < 0)
		वापस rc;
	स_रखो(kaddr, 0, nr_pages << PAGE_SHIFT);
	dax_flush(dax_dev, kaddr, nr_pages << PAGE_SHIFT);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dax_operations virtio_fs_dax_ops = अणु
	.direct_access = virtio_fs_direct_access,
	.copy_from_iter = virtio_fs_copy_from_iter,
	.copy_to_iter = virtio_fs_copy_to_iter,
	.zero_page_range = virtio_fs_zero_page_range,
पूर्ण;

अटल व्योम virtio_fs_cleanup_dax(व्योम *data)
अणु
	काष्ठा dax_device *dax_dev = data;

	समाप्त_dax(dax_dev);
	put_dax(dax_dev);
पूर्ण

अटल पूर्णांक virtio_fs_setup_dax(काष्ठा virtio_device *vdev, काष्ठा virtio_fs *fs)
अणु
	काष्ठा virtio_shm_region cache_reg;
	काष्ठा dev_pagemap *pgmap;
	bool have_cache;

	अगर (!IS_ENABLED(CONFIG_FUSE_DAX))
		वापस 0;

	/* Get cache region */
	have_cache = virtio_get_shm_region(vdev, &cache_reg,
					   (u8)VIRTIO_FS_SHMCAP_ID_CACHE);
	अगर (!have_cache) अणु
		dev_notice(&vdev->dev, "%s: No cache capability\n", __func__);
		वापस 0;
	पूर्ण

	अगर (!devm_request_mem_region(&vdev->dev, cache_reg.addr, cache_reg.len,
				     dev_name(&vdev->dev))) अणु
		dev_warn(&vdev->dev, "could not reserve region addr=0x%llx len=0x%llx\n",
			 cache_reg.addr, cache_reg.len);
		वापस -EBUSY;
	पूर्ण

	dev_notice(&vdev->dev, "Cache len: 0x%llx @ 0x%llx\n", cache_reg.len,
		   cache_reg.addr);

	pgmap = devm_kzalloc(&vdev->dev, माप(*pgmap), GFP_KERNEL);
	अगर (!pgmap)
		वापस -ENOMEM;

	pgmap->type = MEMORY_DEVICE_FS_DAX;

	/* Ideally we would directly use the PCI BAR resource but
	 * devm_memremap_pages() wants its own copy in pgmap.  So
	 * initialize a काष्ठा resource from scratch (only the start
	 * and end fields will be used).
	 */
	pgmap->range = (काष्ठा range) अणु
		.start = (phys_addr_t) cache_reg.addr,
		.end = (phys_addr_t) cache_reg.addr + cache_reg.len - 1,
	पूर्ण;
	pgmap->nr_range = 1;

	fs->winकरोw_kaddr = devm_memremap_pages(&vdev->dev, pgmap);
	अगर (IS_ERR(fs->winकरोw_kaddr))
		वापस PTR_ERR(fs->winकरोw_kaddr);

	fs->winकरोw_phys_addr = (phys_addr_t) cache_reg.addr;
	fs->winकरोw_len = (phys_addr_t) cache_reg.len;

	dev_dbg(&vdev->dev, "%s: window kaddr 0x%px phys_addr 0x%llx len 0x%llx\n",
		__func__, fs->winकरोw_kaddr, cache_reg.addr, cache_reg.len);

	fs->dax_dev = alloc_dax(fs, शून्य, &virtio_fs_dax_ops, 0);
	अगर (IS_ERR(fs->dax_dev))
		वापस PTR_ERR(fs->dax_dev);

	वापस devm_add_action_or_reset(&vdev->dev, virtio_fs_cleanup_dax,
					fs->dax_dev);
पूर्ण

अटल पूर्णांक virtio_fs_probe(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_fs *fs;
	पूर्णांक ret;

	fs = kzalloc(माप(*fs), GFP_KERNEL);
	अगर (!fs)
		वापस -ENOMEM;
	kref_init(&fs->refcount);
	vdev->priv = fs;

	ret = virtio_fs_पढ़ो_tag(vdev, fs);
	अगर (ret < 0)
		जाओ out;

	ret = virtio_fs_setup_vqs(vdev, fs);
	अगर (ret < 0)
		जाओ out;

	/* TODO vq affinity */

	ret = virtio_fs_setup_dax(vdev, fs);
	अगर (ret < 0)
		जाओ out_vqs;

	/* Bring the device online in हाल the fileप्रणाली is mounted and
	 * requests need to be sent beक्रमe we वापस.
	 */
	virtio_device_पढ़ोy(vdev);

	ret = virtio_fs_add_instance(fs);
	अगर (ret < 0)
		जाओ out_vqs;

	वापस 0;

out_vqs:
	vdev->config->reset(vdev);
	virtio_fs_cleanup_vqs(vdev, fs);
	kमुक्त(fs->vqs);

out:
	vdev->priv = शून्य;
	kमुक्त(fs);
	वापस ret;
पूर्ण

अटल व्योम virtio_fs_stop_all_queues(काष्ठा virtio_fs *fs)
अणु
	काष्ठा virtio_fs_vq *fsvq;
	पूर्णांक i;

	क्रम (i = 0; i < fs->nvqs; i++) अणु
		fsvq = &fs->vqs[i];
		spin_lock(&fsvq->lock);
		fsvq->connected = false;
		spin_unlock(&fsvq->lock);
	पूर्ण
पूर्ण

अटल व्योम virtio_fs_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_fs *fs = vdev->priv;

	mutex_lock(&virtio_fs_mutex);
	/* This device is going away. No one should get new reference */
	list_del_init(&fs->list);
	virtio_fs_stop_all_queues(fs);
	virtio_fs_drain_all_queues_locked(fs);
	vdev->config->reset(vdev);
	virtio_fs_cleanup_vqs(vdev, fs);

	vdev->priv = शून्य;
	/* Put device reference on virtio_fs object */
	virtio_fs_put(fs);
	mutex_unlock(&virtio_fs_mutex);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक virtio_fs_मुक्तze(काष्ठा virtio_device *vdev)
अणु
	/* TODO need to save state here */
	pr_warn("virtio-fs: suspend/resume not yet supported\n");
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक virtio_fs_restore(काष्ठा virtio_device *vdev)
अणु
	 /* TODO need to restore state here */
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_FS, VIRTIO_DEV_ANY_ID पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक feature_table[] = अणुपूर्ण;

अटल काष्ठा virtio_driver virtio_fs_driver = अणु
	.driver.name		= KBUILD_MODNAME,
	.driver.owner		= THIS_MODULE,
	.id_table		= id_table,
	.feature_table		= feature_table,
	.feature_table_size	= ARRAY_SIZE(feature_table),
	.probe			= virtio_fs_probe,
	.हटाओ			= virtio_fs_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.मुक्तze			= virtio_fs_मुक्तze,
	.restore		= virtio_fs_restore,
#पूर्ण_अगर
पूर्ण;

अटल व्योम virtio_fs_wake_क्रमget_and_unlock(काष्ठा fuse_iqueue *fiq)
__releases(fiq->lock)
अणु
	काष्ठा fuse_क्रमget_link *link;
	काष्ठा virtio_fs_क्रमget *क्रमget;
	काष्ठा virtio_fs_क्रमget_req *req;
	काष्ठा virtio_fs *fs;
	काष्ठा virtio_fs_vq *fsvq;
	u64 unique;

	link = fuse_dequeue_क्रमget(fiq, 1, शून्य);
	unique = fuse_get_unique(fiq);

	fs = fiq->priv;
	fsvq = &fs->vqs[VQ_HIPRIO];
	spin_unlock(&fiq->lock);

	/* Allocate a buffer क्रम the request */
	क्रमget = kदो_स्मृति(माप(*क्रमget), GFP_NOFS | __GFP_NOFAIL);
	req = &क्रमget->req;

	req->ih = (काष्ठा fuse_in_header)अणु
		.opcode = FUSE_FORGET,
		.nodeid = link->क्रमget_one.nodeid,
		.unique = unique,
		.len = माप(*req),
	पूर्ण;
	req->arg = (काष्ठा fuse_क्रमget_in)अणु
		.nlookup = link->क्रमget_one.nlookup,
	पूर्ण;

	send_क्रमget_request(fsvq, क्रमget, false);
	kमुक्त(link);
पूर्ण

अटल व्योम virtio_fs_wake_पूर्णांकerrupt_and_unlock(काष्ठा fuse_iqueue *fiq)
__releases(fiq->lock)
अणु
	/*
	 * TODO पूर्णांकerrupts.
	 *
	 * Normal fs operations on a local fileप्रणालीs aren't पूर्णांकerruptible.
	 * Exceptions are blocking lock operations; क्रम example fcntl(F_SETLKW)
	 * with shared lock between host and guest.
	 */
	spin_unlock(&fiq->lock);
पूर्ण

/* Count number of scatter-gather elements required */
अटल अचिन्हित पूर्णांक sg_count_fuse_pages(काष्ठा fuse_page_desc *page_descs,
				       अचिन्हित पूर्णांक num_pages,
				       अचिन्हित पूर्णांक total_len)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक this_len;

	क्रम (i = 0; i < num_pages && total_len; i++) अणु
		this_len =  min(page_descs[i].length, total_len);
		total_len -= this_len;
	पूर्ण

	वापस i;
पूर्ण

/* Return the number of scatter-gather list elements required */
अटल अचिन्हित पूर्णांक sg_count_fuse_req(काष्ठा fuse_req *req)
अणु
	काष्ठा fuse_args *args = req->args;
	काष्ठा fuse_args_pages *ap = container_of(args, typeof(*ap), args);
	अचिन्हित पूर्णांक size, total_sgs = 1 /* fuse_in_header */;

	अगर (args->in_numargs - args->in_pages)
		total_sgs += 1;

	अगर (args->in_pages) अणु
		size = args->in_args[args->in_numargs - 1].size;
		total_sgs += sg_count_fuse_pages(ap->descs, ap->num_pages,
						 size);
	पूर्ण

	अगर (!test_bit(FR_ISREPLY, &req->flags))
		वापस total_sgs;

	total_sgs += 1 /* fuse_out_header */;

	अगर (args->out_numargs - args->out_pages)
		total_sgs += 1;

	अगर (args->out_pages) अणु
		size = args->out_args[args->out_numargs - 1].size;
		total_sgs += sg_count_fuse_pages(ap->descs, ap->num_pages,
						 size);
	पूर्ण

	वापस total_sgs;
पूर्ण

/* Add pages to scatter-gather list and वापस number of elements used */
अटल अचिन्हित पूर्णांक sg_init_fuse_pages(काष्ठा scatterlist *sg,
				       काष्ठा page **pages,
				       काष्ठा fuse_page_desc *page_descs,
				       अचिन्हित पूर्णांक num_pages,
				       अचिन्हित पूर्णांक total_len)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक this_len;

	क्रम (i = 0; i < num_pages && total_len; i++) अणु
		sg_init_table(&sg[i], 1);
		this_len =  min(page_descs[i].length, total_len);
		sg_set_page(&sg[i], pages[i], this_len, page_descs[i].offset);
		total_len -= this_len;
	पूर्ण

	वापस i;
पूर्ण

/* Add args to scatter-gather list and वापस number of elements used */
अटल अचिन्हित पूर्णांक sg_init_fuse_args(काष्ठा scatterlist *sg,
				      काष्ठा fuse_req *req,
				      काष्ठा fuse_arg *args,
				      अचिन्हित पूर्णांक numargs,
				      bool argpages,
				      व्योम *argbuf,
				      अचिन्हित पूर्णांक *len_used)
अणु
	काष्ठा fuse_args_pages *ap = container_of(req->args, typeof(*ap), args);
	अचिन्हित पूर्णांक total_sgs = 0;
	अचिन्हित पूर्णांक len;

	len = fuse_len_args(numargs - argpages, args);
	अगर (len)
		sg_init_one(&sg[total_sgs++], argbuf, len);

	अगर (argpages)
		total_sgs += sg_init_fuse_pages(&sg[total_sgs],
						ap->pages, ap->descs,
						ap->num_pages,
						args[numargs - 1].size);

	अगर (len_used)
		*len_used = len;

	वापस total_sgs;
पूर्ण

/* Add a request to a virtqueue and kick the device */
अटल पूर्णांक virtio_fs_enqueue_req(काष्ठा virtio_fs_vq *fsvq,
				 काष्ठा fuse_req *req, bool in_flight)
अणु
	/* requests need at least 4 elements */
	काष्ठा scatterlist *stack_sgs[6];
	काष्ठा scatterlist stack_sg[ARRAY_SIZE(stack_sgs)];
	काष्ठा scatterlist **sgs = stack_sgs;
	काष्ठा scatterlist *sg = stack_sg;
	काष्ठा virtqueue *vq;
	काष्ठा fuse_args *args = req->args;
	अचिन्हित पूर्णांक argbuf_used = 0;
	अचिन्हित पूर्णांक out_sgs = 0;
	अचिन्हित पूर्णांक in_sgs = 0;
	अचिन्हित पूर्णांक total_sgs;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;
	bool notअगरy;
	काष्ठा fuse_pqueue *fpq;

	/* Does the sglist fit on the stack? */
	total_sgs = sg_count_fuse_req(req);
	अगर (total_sgs > ARRAY_SIZE(stack_sgs)) अणु
		sgs = kदो_स्मृति_array(total_sgs, माप(sgs[0]), GFP_ATOMIC);
		sg = kदो_स्मृति_array(total_sgs, माप(sg[0]), GFP_ATOMIC);
		अगर (!sgs || !sg) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Use a bounce buffer since stack args cannot be mapped */
	ret = copy_args_to_argbuf(req);
	अगर (ret < 0)
		जाओ out;

	/* Request elements */
	sg_init_one(&sg[out_sgs++], &req->in.h, माप(req->in.h));
	out_sgs += sg_init_fuse_args(&sg[out_sgs], req,
				     (काष्ठा fuse_arg *)args->in_args,
				     args->in_numargs, args->in_pages,
				     req->argbuf, &argbuf_used);

	/* Reply elements */
	अगर (test_bit(FR_ISREPLY, &req->flags)) अणु
		sg_init_one(&sg[out_sgs + in_sgs++],
			    &req->out.h, माप(req->out.h));
		in_sgs += sg_init_fuse_args(&sg[out_sgs + in_sgs], req,
					    args->out_args, args->out_numargs,
					    args->out_pages,
					    req->argbuf + argbuf_used, शून्य);
	पूर्ण

	WARN_ON(out_sgs + in_sgs != total_sgs);

	क्रम (i = 0; i < total_sgs; i++)
		sgs[i] = &sg[i];

	spin_lock(&fsvq->lock);

	अगर (!fsvq->connected) अणु
		spin_unlock(&fsvq->lock);
		ret = -ENOTCONN;
		जाओ out;
	पूर्ण

	vq = fsvq->vq;
	ret = virtqueue_add_sgs(vq, sgs, out_sgs, in_sgs, req, GFP_ATOMIC);
	अगर (ret < 0) अणु
		spin_unlock(&fsvq->lock);
		जाओ out;
	पूर्ण

	/* Request successfully sent. */
	fpq = &fsvq->fud->pq;
	spin_lock(&fpq->lock);
	list_add_tail(&req->list, fpq->processing);
	spin_unlock(&fpq->lock);
	set_bit(FR_SENT, &req->flags);
	/* matches barrier in request_रुको_answer() */
	smp_mb__after_atomic();

	अगर (!in_flight)
		inc_in_flight_req(fsvq);
	notअगरy = virtqueue_kick_prepare(vq);

	spin_unlock(&fsvq->lock);

	अगर (notअगरy)
		virtqueue_notअगरy(vq);

out:
	अगर (ret < 0 && req->argbuf) अणु
		kमुक्त(req->argbuf);
		req->argbuf = शून्य;
	पूर्ण
	अगर (sgs != stack_sgs) अणु
		kमुक्त(sgs);
		kमुक्त(sg);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम virtio_fs_wake_pending_and_unlock(काष्ठा fuse_iqueue *fiq)
__releases(fiq->lock)
अणु
	अचिन्हित पूर्णांक queue_id = VQ_REQUEST; /* TODO multiqueue */
	काष्ठा virtio_fs *fs;
	काष्ठा fuse_req *req;
	काष्ठा virtio_fs_vq *fsvq;
	पूर्णांक ret;

	WARN_ON(list_empty(&fiq->pending));
	req = list_last_entry(&fiq->pending, काष्ठा fuse_req, list);
	clear_bit(FR_PENDING, &req->flags);
	list_del_init(&req->list);
	WARN_ON(!list_empty(&fiq->pending));
	spin_unlock(&fiq->lock);

	fs = fiq->priv;

	pr_debug("%s: opcode %u unique %#llx nodeid %#llx in.len %u out.len %u\n",
		  __func__, req->in.h.opcode, req->in.h.unique,
		 req->in.h.nodeid, req->in.h.len,
		 fuse_len_args(req->args->out_numargs, req->args->out_args));

	fsvq = &fs->vqs[queue_id];
	ret = virtio_fs_enqueue_req(fsvq, req, false);
	अगर (ret < 0) अणु
		अगर (ret == -ENOMEM || ret == -ENOSPC) अणु
			/*
			 * Virtqueue full. Retry submission from worker
			 * context as we might be holding fc->bg_lock.
			 */
			spin_lock(&fsvq->lock);
			list_add_tail(&req->list, &fsvq->queued_reqs);
			inc_in_flight_req(fsvq);
			schedule_delayed_work(&fsvq->dispatch_work,
						msecs_to_jअगरfies(1));
			spin_unlock(&fsvq->lock);
			वापस;
		पूर्ण
		req->out.h.error = ret;
		pr_err("virtio-fs: virtio_fs_enqueue_req() failed %d\n", ret);

		/* Can't end request in submission context. Use a worker */
		spin_lock(&fsvq->lock);
		list_add_tail(&req->list, &fsvq->end_reqs);
		schedule_delayed_work(&fsvq->dispatch_work, 0);
		spin_unlock(&fsvq->lock);
		वापस;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा fuse_iqueue_ops virtio_fs_fiq_ops = अणु
	.wake_क्रमget_and_unlock		= virtio_fs_wake_क्रमget_and_unlock,
	.wake_पूर्णांकerrupt_and_unlock	= virtio_fs_wake_पूर्णांकerrupt_and_unlock,
	.wake_pending_and_unlock	= virtio_fs_wake_pending_and_unlock,
	.release			= virtio_fs_fiq_release,
पूर्ण;

अटल अंतरभूत व्योम virtio_fs_ctx_set_शेषs(काष्ठा fuse_fs_context *ctx)
अणु
	ctx->rooपंचांगode = S_IFसूची;
	ctx->शेष_permissions = 1;
	ctx->allow_other = 1;
	ctx->max_पढ़ो = अच_पूर्णांक_उच्च;
	ctx->blksize = 512;
	ctx->destroy = true;
	ctx->no_control = true;
	ctx->no_क्रमce_umount = true;
पूर्ण

अटल पूर्णांक virtio_fs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fsc)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount_super(sb);
	काष्ठा fuse_conn *fc = fm->fc;
	काष्ठा virtio_fs *fs = fc->iq.priv;
	काष्ठा fuse_fs_context *ctx = fsc->fs_निजी;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	virtio_fs_ctx_set_शेषs(ctx);
	mutex_lock(&virtio_fs_mutex);

	/* After holding mutex, make sure virtiofs device is still there.
	 * Though we are holding a reference to it, drive ->हटाओ might
	 * still have cleaned up भव queues. In that हाल bail out.
	 */
	err = -EINVAL;
	अगर (list_empty(&fs->list)) अणु
		pr_info("virtio-fs: tag <%s> not found\n", fs->tag);
		जाओ err;
	पूर्ण

	err = -ENOMEM;
	/* Allocate fuse_dev क्रम hiprio and notअगरication queues */
	क्रम (i = 0; i < fs->nvqs; i++) अणु
		काष्ठा virtio_fs_vq *fsvq = &fs->vqs[i];

		fsvq->fud = fuse_dev_alloc();
		अगर (!fsvq->fud)
			जाओ err_मुक्त_fuse_devs;
	पूर्ण

	/* virtiofs allocates and installs its own fuse devices */
	ctx->fudptr = शून्य;
	अगर (ctx->dax) अणु
		अगर (!fs->dax_dev) अणु
			err = -EINVAL;
			pr_err("virtio-fs: dax can't be enabled as filesystem"
			       " device does not support it.\n");
			जाओ err_मुक्त_fuse_devs;
		पूर्ण
		ctx->dax_dev = fs->dax_dev;
	पूर्ण
	err = fuse_fill_super_common(sb, ctx);
	अगर (err < 0)
		जाओ err_मुक्त_fuse_devs;

	क्रम (i = 0; i < fs->nvqs; i++) अणु
		काष्ठा virtio_fs_vq *fsvq = &fs->vqs[i];

		fuse_dev_install(fsvq->fud, fc);
	पूर्ण

	/* Previous unmount will stop all queues. Start these again */
	virtio_fs_start_all_queues(fs);
	fuse_send_init(fm);
	mutex_unlock(&virtio_fs_mutex);
	वापस 0;

err_मुक्त_fuse_devs:
	virtio_fs_मुक्त_devs(fs);
err:
	mutex_unlock(&virtio_fs_mutex);
	वापस err;
पूर्ण

अटल व्योम virtio_fs_conn_destroy(काष्ठा fuse_mount *fm)
अणु
	काष्ठा fuse_conn *fc = fm->fc;
	काष्ठा virtio_fs *vfs = fc->iq.priv;
	काष्ठा virtio_fs_vq *fsvq = &vfs->vqs[VQ_HIPRIO];

	/* Stop dax worker. Soon evict_inodes() will be called which
	 * will मुक्त all memory ranges beदीर्घing to all inodes.
	 */
	अगर (IS_ENABLED(CONFIG_FUSE_DAX))
		fuse_dax_cancel_work(fc);

	/* Stop क्रमget queue. Soon destroy will be sent */
	spin_lock(&fsvq->lock);
	fsvq->connected = false;
	spin_unlock(&fsvq->lock);
	virtio_fs_drain_all_queues(vfs);

	fuse_conn_destroy(fm);

	/* fuse_conn_destroy() must have sent destroy. Stop all queues
	 * and drain one more समय and मुक्त fuse devices. Freeing fuse
	 * devices will drop their reference on fuse_conn and that in
	 * turn will drop its reference on virtio_fs object.
	 */
	virtio_fs_stop_all_queues(vfs);
	virtio_fs_drain_all_queues(vfs);
	virtio_fs_मुक्त_devs(vfs);
पूर्ण

अटल व्योम virtio_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount_super(sb);
	bool last;

	/* If mount failed, we can still be called without any fc */
	अगर (fm) अणु
		last = fuse_mount_हटाओ(fm);
		अगर (last)
			virtio_fs_conn_destroy(fm);
	पूर्ण
	समाप्त_anon_super(sb);
पूर्ण

अटल पूर्णांक virtio_fs_test_super(काष्ठा super_block *sb,
				काष्ठा fs_context *fsc)
अणु
	काष्ठा fuse_mount *fsc_fm = fsc->s_fs_info;
	काष्ठा fuse_mount *sb_fm = get_fuse_mount_super(sb);

	वापस fsc_fm->fc->iq.priv == sb_fm->fc->iq.priv;
पूर्ण

अटल पूर्णांक virtio_fs_get_tree(काष्ठा fs_context *fsc)
अणु
	काष्ठा virtio_fs *fs;
	काष्ठा super_block *sb;
	काष्ठा fuse_conn *fc = शून्य;
	काष्ठा fuse_mount *fm;
	अचिन्हित पूर्णांक virtqueue_size;
	पूर्णांक err = -EIO;

	/* This माला_लो a reference on virtio_fs object. This ptr माला_लो installed
	 * in fc->iq->priv. Once fuse_conn is going away, it calls ->put()
	 * to drop the reference to this object.
	 */
	fs = virtio_fs_find_instance(fsc->source);
	अगर (!fs) अणु
		pr_info("virtio-fs: tag <%s> not found\n", fsc->source);
		वापस -EINVAL;
	पूर्ण

	virtqueue_size = virtqueue_get_vring_size(fs->vqs[VQ_REQUEST].vq);
	अगर (WARN_ON(virtqueue_size <= FUSE_HEADER_OVERHEAD))
		जाओ out_err;

	err = -ENOMEM;
	fc = kzalloc(माप(काष्ठा fuse_conn), GFP_KERNEL);
	अगर (!fc)
		जाओ out_err;

	fm = kzalloc(माप(काष्ठा fuse_mount), GFP_KERNEL);
	अगर (!fm)
		जाओ out_err;

	fuse_conn_init(fc, fm, fsc->user_ns, &virtio_fs_fiq_ops, fs);
	fc->release = fuse_मुक्त_conn;
	fc->delete_stale = true;
	fc->स्वतः_submounts = true;

	/* Tell FUSE to split requests that exceed the virtqueue's size */
	fc->max_pages_limit = min_t(अचिन्हित पूर्णांक, fc->max_pages_limit,
				    virtqueue_size - FUSE_HEADER_OVERHEAD);

	fsc->s_fs_info = fm;
	sb = sget_fc(fsc, virtio_fs_test_super, set_anon_super_fc);
	अगर (fsc->s_fs_info) अणु
		fuse_conn_put(fc);
		kमुक्त(fm);
	पूर्ण
	अगर (IS_ERR(sb))
		वापस PTR_ERR(sb);

	अगर (!sb->s_root) अणु
		err = virtio_fs_fill_super(sb, fsc);
		अगर (err) अणु
			fuse_conn_put(fc);
			kमुक्त(fm);
			sb->s_fs_info = शून्य;
			deactivate_locked_super(sb);
			वापस err;
		पूर्ण

		sb->s_flags |= SB_ACTIVE;
	पूर्ण

	WARN_ON(fsc->root);
	fsc->root = dget(sb->s_root);
	वापस 0;

out_err:
	kमुक्त(fc);
	mutex_lock(&virtio_fs_mutex);
	virtio_fs_put(fs);
	mutex_unlock(&virtio_fs_mutex);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा fs_context_operations virtio_fs_context_ops = अणु
	.मुक्त		= virtio_fs_मुक्त_fc,
	.parse_param	= virtio_fs_parse_param,
	.get_tree	= virtio_fs_get_tree,
पूर्ण;

अटल पूर्णांक virtio_fs_init_fs_context(काष्ठा fs_context *fsc)
अणु
	काष्ठा fuse_fs_context *ctx;

	ctx = kzalloc(माप(काष्ठा fuse_fs_context), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	fsc->fs_निजी = ctx;
	fsc->ops = &virtio_fs_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type virtio_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "virtiofs",
	.init_fs_context = virtio_fs_init_fs_context,
	.समाप्त_sb	= virtio_समाप्त_sb,
पूर्ण;

अटल पूर्णांक __init virtio_fs_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_virtio_driver(&virtio_fs_driver);
	अगर (ret < 0)
		वापस ret;

	ret = रेजिस्टर_fileप्रणाली(&virtio_fs_type);
	अगर (ret < 0) अणु
		unरेजिस्टर_virtio_driver(&virtio_fs_driver);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(virtio_fs_init);

अटल व्योम __निकास virtio_fs_निकास(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&virtio_fs_type);
	unरेजिस्टर_virtio_driver(&virtio_fs_driver);
पूर्ण
module_निकास(virtio_fs_निकास);

MODULE_AUTHOR("Stefan Hajnoczi <stefanha@redhat.com>");
MODULE_DESCRIPTION("Virtio Filesystem");
MODULE_LICENSE("GPL");
MODULE_ALIAS_FS(KBUILD_MODNAME);
MODULE_DEVICE_TABLE(virtio, id_table);
