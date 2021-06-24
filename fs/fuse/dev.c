<शैली गुरु>
/*
  FUSE: Fileप्रणाली in Userspace
  Copyright (C) 2001-2008  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
*/

#समावेश "fuse_i.h"

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uपन.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/pipe_fs_i.h>
#समावेश <linux/swap.h>
#समावेश <linux/splice.h>
#समावेश <linux/sched.h>

MODULE_ALIAS_MISCDEV(FUSE_MINOR);
MODULE_ALIAS("devname:fuse");

/* Ordinary requests have even IDs, जबतक पूर्णांकerrupts IDs are odd */
#घोषणा FUSE_INT_REQ_BIT (1ULL << 0)
#घोषणा FUSE_REQ_ID_STEP (1ULL << 1)

अटल काष्ठा kmem_cache *fuse_req_cachep;

अटल काष्ठा fuse_dev *fuse_get_dev(काष्ठा file *file)
अणु
	/*
	 * Lockless access is OK, because file->निजी data is set
	 * once during mount and is valid until the file is released.
	 */
	वापस READ_ONCE(file->निजी_data);
पूर्ण

अटल व्योम fuse_request_init(काष्ठा fuse_mount *fm, काष्ठा fuse_req *req)
अणु
	INIT_LIST_HEAD(&req->list);
	INIT_LIST_HEAD(&req->पूर्णांकr_entry);
	init_रुकोqueue_head(&req->रुकोq);
	refcount_set(&req->count, 1);
	__set_bit(FR_PENDING, &req->flags);
	req->fm = fm;
पूर्ण

अटल काष्ठा fuse_req *fuse_request_alloc(काष्ठा fuse_mount *fm, gfp_t flags)
अणु
	काष्ठा fuse_req *req = kmem_cache_zalloc(fuse_req_cachep, flags);
	अगर (req)
		fuse_request_init(fm, req);

	वापस req;
पूर्ण

अटल व्योम fuse_request_मुक्त(काष्ठा fuse_req *req)
अणु
	kmem_cache_मुक्त(fuse_req_cachep, req);
पूर्ण

अटल व्योम __fuse_get_request(काष्ठा fuse_req *req)
अणु
	refcount_inc(&req->count);
पूर्ण

/* Must be called with > 1 refcount */
अटल व्योम __fuse_put_request(काष्ठा fuse_req *req)
अणु
	refcount_dec(&req->count);
पूर्ण

व्योम fuse_set_initialized(काष्ठा fuse_conn *fc)
अणु
	/* Make sure stores beक्रमe this are seen on another CPU */
	smp_wmb();
	fc->initialized = 1;
पूर्ण

अटल bool fuse_block_alloc(काष्ठा fuse_conn *fc, bool क्रम_background)
अणु
	वापस !fc->initialized || (क्रम_background && fc->blocked);
पूर्ण

अटल व्योम fuse_drop_रुकोing(काष्ठा fuse_conn *fc)
अणु
	/*
	 * lockess check of fc->connected is okay, because atomic_dec_and_test()
	 * provides a memory barrier mached with the one in fuse_रुको_पातed()
	 * to ensure no wake-up is missed.
	 */
	अगर (atomic_dec_and_test(&fc->num_रुकोing) &&
	    !READ_ONCE(fc->connected)) अणु
		/* wake up पातers */
		wake_up_all(&fc->blocked_रुकोq);
	पूर्ण
पूर्ण

अटल व्योम fuse_put_request(काष्ठा fuse_req *req);

अटल काष्ठा fuse_req *fuse_get_req(काष्ठा fuse_mount *fm, bool क्रम_background)
अणु
	काष्ठा fuse_conn *fc = fm->fc;
	काष्ठा fuse_req *req;
	पूर्णांक err;
	atomic_inc(&fc->num_रुकोing);

	अगर (fuse_block_alloc(fc, क्रम_background)) अणु
		err = -EINTR;
		अगर (रुको_event_समाप्तable_exclusive(fc->blocked_रुकोq,
				!fuse_block_alloc(fc, क्रम_background)))
			जाओ out;
	पूर्ण
	/* Matches smp_wmb() in fuse_set_initialized() */
	smp_rmb();

	err = -ENOTCONN;
	अगर (!fc->connected)
		जाओ out;

	err = -ECONNREFUSED;
	अगर (fc->conn_error)
		जाओ out;

	req = fuse_request_alloc(fm, GFP_KERNEL);
	err = -ENOMEM;
	अगर (!req) अणु
		अगर (क्रम_background)
			wake_up(&fc->blocked_रुकोq);
		जाओ out;
	पूर्ण

	req->in.h.uid = from_kuid(fc->user_ns, current_fsuid());
	req->in.h.gid = from_kgid(fc->user_ns, current_fsgid());
	req->in.h.pid = pid_nr_ns(task_pid(current), fc->pid_ns);

	__set_bit(FR_WAITING, &req->flags);
	अगर (क्रम_background)
		__set_bit(FR_BACKGROUND, &req->flags);

	अगर (unlikely(req->in.h.uid == ((uid_t)-1) ||
		     req->in.h.gid == ((gid_t)-1))) अणु
		fuse_put_request(req);
		वापस ERR_PTR(-EOVERFLOW);
	पूर्ण
	वापस req;

 out:
	fuse_drop_रुकोing(fc);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम fuse_put_request(काष्ठा fuse_req *req)
अणु
	काष्ठा fuse_conn *fc = req->fm->fc;

	अगर (refcount_dec_and_test(&req->count)) अणु
		अगर (test_bit(FR_BACKGROUND, &req->flags)) अणु
			/*
			 * We get here in the unlikely हाल that a background
			 * request was allocated but not sent
			 */
			spin_lock(&fc->bg_lock);
			अगर (!fc->blocked)
				wake_up(&fc->blocked_रुकोq);
			spin_unlock(&fc->bg_lock);
		पूर्ण

		अगर (test_bit(FR_WAITING, &req->flags)) अणु
			__clear_bit(FR_WAITING, &req->flags);
			fuse_drop_रुकोing(fc);
		पूर्ण

		fuse_request_मुक्त(req);
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक fuse_len_args(अचिन्हित पूर्णांक numargs, काष्ठा fuse_arg *args)
अणु
	अचिन्हित nbytes = 0;
	अचिन्हित i;

	क्रम (i = 0; i < numargs; i++)
		nbytes += args[i].size;

	वापस nbytes;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_len_args);

u64 fuse_get_unique(काष्ठा fuse_iqueue *fiq)
अणु
	fiq->reqctr += FUSE_REQ_ID_STEP;
	वापस fiq->reqctr;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_get_unique);

अटल अचिन्हित पूर्णांक fuse_req_hash(u64 unique)
अणु
	वापस hash_दीर्घ(unique & ~FUSE_INT_REQ_BIT, FUSE_PQ_HASH_BITS);
पूर्ण

/**
 * A new request is available, wake fiq->रुकोq
 */
अटल व्योम fuse_dev_wake_and_unlock(काष्ठा fuse_iqueue *fiq)
__releases(fiq->lock)
अणु
	wake_up(&fiq->रुकोq);
	समाप्त_fasync(&fiq->fasync, SIGIO, POLL_IN);
	spin_unlock(&fiq->lock);
पूर्ण

स्थिर काष्ठा fuse_iqueue_ops fuse_dev_fiq_ops = अणु
	.wake_क्रमget_and_unlock		= fuse_dev_wake_and_unlock,
	.wake_पूर्णांकerrupt_and_unlock	= fuse_dev_wake_and_unlock,
	.wake_pending_and_unlock	= fuse_dev_wake_and_unlock,
पूर्ण;
EXPORT_SYMBOL_GPL(fuse_dev_fiq_ops);

अटल व्योम queue_request_and_unlock(काष्ठा fuse_iqueue *fiq,
				     काष्ठा fuse_req *req)
__releases(fiq->lock)
अणु
	req->in.h.len = माप(काष्ठा fuse_in_header) +
		fuse_len_args(req->args->in_numargs,
			      (काष्ठा fuse_arg *) req->args->in_args);
	list_add_tail(&req->list, &fiq->pending);
	fiq->ops->wake_pending_and_unlock(fiq);
पूर्ण

व्योम fuse_queue_क्रमget(काष्ठा fuse_conn *fc, काष्ठा fuse_क्रमget_link *क्रमget,
		       u64 nodeid, u64 nlookup)
अणु
	काष्ठा fuse_iqueue *fiq = &fc->iq;

	क्रमget->क्रमget_one.nodeid = nodeid;
	क्रमget->क्रमget_one.nlookup = nlookup;

	spin_lock(&fiq->lock);
	अगर (fiq->connected) अणु
		fiq->क्रमget_list_tail->next = क्रमget;
		fiq->क्रमget_list_tail = क्रमget;
		fiq->ops->wake_क्रमget_and_unlock(fiq);
	पूर्ण अन्यथा अणु
		kमुक्त(क्रमget);
		spin_unlock(&fiq->lock);
	पूर्ण
पूर्ण

अटल व्योम flush_bg_queue(काष्ठा fuse_conn *fc)
अणु
	काष्ठा fuse_iqueue *fiq = &fc->iq;

	जबतक (fc->active_background < fc->max_background &&
	       !list_empty(&fc->bg_queue)) अणु
		काष्ठा fuse_req *req;

		req = list_first_entry(&fc->bg_queue, काष्ठा fuse_req, list);
		list_del(&req->list);
		fc->active_background++;
		spin_lock(&fiq->lock);
		req->in.h.unique = fuse_get_unique(fiq);
		queue_request_and_unlock(fiq, req);
	पूर्ण
पूर्ण

/*
 * This function is called when a request is finished.  Either a reply
 * has arrived or it was पातed (and not yet sent) or some error
 * occurred during communication with userspace, or the device file
 * was बंदd.  The requester thपढ़ो is woken up (अगर still रुकोing),
 * the 'end' callback is called अगर given, अन्यथा the reference to the
 * request is released
 */
व्योम fuse_request_end(काष्ठा fuse_req *req)
अणु
	काष्ठा fuse_mount *fm = req->fm;
	काष्ठा fuse_conn *fc = fm->fc;
	काष्ठा fuse_iqueue *fiq = &fc->iq;

	अगर (test_and_set_bit(FR_FINISHED, &req->flags))
		जाओ put_request;

	/*
	 * test_and_set_bit() implies smp_mb() between bit
	 * changing and below पूर्णांकr_entry check. Pairs with
	 * smp_mb() from queue_पूर्णांकerrupt().
	 */
	अगर (!list_empty(&req->पूर्णांकr_entry)) अणु
		spin_lock(&fiq->lock);
		list_del_init(&req->पूर्णांकr_entry);
		spin_unlock(&fiq->lock);
	पूर्ण
	WARN_ON(test_bit(FR_PENDING, &req->flags));
	WARN_ON(test_bit(FR_SENT, &req->flags));
	अगर (test_bit(FR_BACKGROUND, &req->flags)) अणु
		spin_lock(&fc->bg_lock);
		clear_bit(FR_BACKGROUND, &req->flags);
		अगर (fc->num_background == fc->max_background) अणु
			fc->blocked = 0;
			wake_up(&fc->blocked_रुकोq);
		पूर्ण अन्यथा अगर (!fc->blocked) अणु
			/*
			 * Wake up next रुकोer, अगर any.  It's okay to use
			 * रुकोqueue_active(), as we've alपढ़ोy synced up
			 * fc->blocked with रुकोers with the wake_up() call
			 * above.
			 */
			अगर (रुकोqueue_active(&fc->blocked_रुकोq))
				wake_up(&fc->blocked_रुकोq);
		पूर्ण

		अगर (fc->num_background == fc->congestion_threshold && fm->sb) अणु
			clear_bdi_congested(fm->sb->s_bdi, BLK_RW_SYNC);
			clear_bdi_congested(fm->sb->s_bdi, BLK_RW_ASYNC);
		पूर्ण
		fc->num_background--;
		fc->active_background--;
		flush_bg_queue(fc);
		spin_unlock(&fc->bg_lock);
	पूर्ण अन्यथा अणु
		/* Wake up रुकोer sleeping in request_रुको_answer() */
		wake_up(&req->रुकोq);
	पूर्ण

	अगर (test_bit(FR_ASYNC, &req->flags))
		req->args->end(fm, req->args, req->out.h.error);
put_request:
	fuse_put_request(req);
पूर्ण
EXPORT_SYMBOL_GPL(fuse_request_end);

अटल पूर्णांक queue_पूर्णांकerrupt(काष्ठा fuse_req *req)
अणु
	काष्ठा fuse_iqueue *fiq = &req->fm->fc->iq;

	spin_lock(&fiq->lock);
	/* Check क्रम we've sent request to पूर्णांकerrupt this req */
	अगर (unlikely(!test_bit(FR_INTERRUPTED, &req->flags))) अणु
		spin_unlock(&fiq->lock);
		वापस -EINVAL;
	पूर्ण

	अगर (list_empty(&req->पूर्णांकr_entry)) अणु
		list_add_tail(&req->पूर्णांकr_entry, &fiq->पूर्णांकerrupts);
		/*
		 * Pairs with smp_mb() implied by test_and_set_bit()
		 * from fuse_request_end().
		 */
		smp_mb();
		अगर (test_bit(FR_FINISHED, &req->flags)) अणु
			list_del_init(&req->पूर्णांकr_entry);
			spin_unlock(&fiq->lock);
			वापस 0;
		पूर्ण
		fiq->ops->wake_पूर्णांकerrupt_and_unlock(fiq);
	पूर्ण अन्यथा अणु
		spin_unlock(&fiq->lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम request_रुको_answer(काष्ठा fuse_req *req)
अणु
	काष्ठा fuse_conn *fc = req->fm->fc;
	काष्ठा fuse_iqueue *fiq = &fc->iq;
	पूर्णांक err;

	अगर (!fc->no_पूर्णांकerrupt) अणु
		/* Any संकेत may पूर्णांकerrupt this */
		err = रुको_event_पूर्णांकerruptible(req->रुकोq,
					test_bit(FR_FINISHED, &req->flags));
		अगर (!err)
			वापस;

		set_bit(FR_INTERRUPTED, &req->flags);
		/* matches barrier in fuse_dev_करो_पढ़ो() */
		smp_mb__after_atomic();
		अगर (test_bit(FR_SENT, &req->flags))
			queue_पूर्णांकerrupt(req);
	पूर्ण

	अगर (!test_bit(FR_FORCE, &req->flags)) अणु
		/* Only fatal संकेतs may पूर्णांकerrupt this */
		err = रुको_event_समाप्तable(req->रुकोq,
					test_bit(FR_FINISHED, &req->flags));
		अगर (!err)
			वापस;

		spin_lock(&fiq->lock);
		/* Request is not yet in userspace, bail out */
		अगर (test_bit(FR_PENDING, &req->flags)) अणु
			list_del(&req->list);
			spin_unlock(&fiq->lock);
			__fuse_put_request(req);
			req->out.h.error = -EINTR;
			वापस;
		पूर्ण
		spin_unlock(&fiq->lock);
	पूर्ण

	/*
	 * Either request is alपढ़ोy in userspace, or it was क्रमced.
	 * Wait it out.
	 */
	रुको_event(req->रुकोq, test_bit(FR_FINISHED, &req->flags));
पूर्ण

अटल व्योम __fuse_request_send(काष्ठा fuse_req *req)
अणु
	काष्ठा fuse_iqueue *fiq = &req->fm->fc->iq;

	BUG_ON(test_bit(FR_BACKGROUND, &req->flags));
	spin_lock(&fiq->lock);
	अगर (!fiq->connected) अणु
		spin_unlock(&fiq->lock);
		req->out.h.error = -ENOTCONN;
	पूर्ण अन्यथा अणु
		req->in.h.unique = fuse_get_unique(fiq);
		/* acquire extra reference, since request is still needed
		   after fuse_request_end() */
		__fuse_get_request(req);
		queue_request_and_unlock(fiq, req);

		request_रुको_answer(req);
		/* Pairs with smp_wmb() in fuse_request_end() */
		smp_rmb();
	पूर्ण
पूर्ण

अटल व्योम fuse_adjust_compat(काष्ठा fuse_conn *fc, काष्ठा fuse_args *args)
अणु
	अगर (fc->minor < 4 && args->opcode == FUSE_STATFS)
		args->out_args[0].size = FUSE_COMPAT_STATFS_SIZE;

	अगर (fc->minor < 9) अणु
		चयन (args->opcode) अणु
		हाल FUSE_LOOKUP:
		हाल FUSE_CREATE:
		हाल FUSE_MKNOD:
		हाल FUSE_MKसूची:
		हाल FUSE_SYMLINK:
		हाल FUSE_LINK:
			args->out_args[0].size = FUSE_COMPAT_ENTRY_OUT_SIZE;
			अवरोध;
		हाल FUSE_GETATTR:
		हाल FUSE_SETATTR:
			args->out_args[0].size = FUSE_COMPAT_ATTR_OUT_SIZE;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (fc->minor < 12) अणु
		चयन (args->opcode) अणु
		हाल FUSE_CREATE:
			args->in_args[0].size = माप(काष्ठा fuse_खोलो_in);
			अवरोध;
		हाल FUSE_MKNOD:
			args->in_args[0].size = FUSE_COMPAT_MKNOD_IN_SIZE;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fuse_क्रमce_creds(काष्ठा fuse_req *req)
अणु
	काष्ठा fuse_conn *fc = req->fm->fc;

	req->in.h.uid = from_kuid_munged(fc->user_ns, current_fsuid());
	req->in.h.gid = from_kgid_munged(fc->user_ns, current_fsgid());
	req->in.h.pid = pid_nr_ns(task_pid(current), fc->pid_ns);
पूर्ण

अटल व्योम fuse_args_to_req(काष्ठा fuse_req *req, काष्ठा fuse_args *args)
अणु
	req->in.h.opcode = args->opcode;
	req->in.h.nodeid = args->nodeid;
	req->args = args;
	अगर (args->end)
		__set_bit(FR_ASYNC, &req->flags);
पूर्ण

sमाप_प्रकार fuse_simple_request(काष्ठा fuse_mount *fm, काष्ठा fuse_args *args)
अणु
	काष्ठा fuse_conn *fc = fm->fc;
	काष्ठा fuse_req *req;
	sमाप_प्रकार ret;

	अगर (args->क्रमce) अणु
		atomic_inc(&fc->num_रुकोing);
		req = fuse_request_alloc(fm, GFP_KERNEL | __GFP_NOFAIL);

		अगर (!args->nocreds)
			fuse_क्रमce_creds(req);

		__set_bit(FR_WAITING, &req->flags);
		__set_bit(FR_FORCE, &req->flags);
	पूर्ण अन्यथा अणु
		WARN_ON(args->nocreds);
		req = fuse_get_req(fm, false);
		अगर (IS_ERR(req))
			वापस PTR_ERR(req);
	पूर्ण

	/* Needs to be करोne after fuse_get_req() so that fc->minor is valid */
	fuse_adjust_compat(fc, args);
	fuse_args_to_req(req, args);

	अगर (!args->noreply)
		__set_bit(FR_ISREPLY, &req->flags);
	__fuse_request_send(req);
	ret = req->out.h.error;
	अगर (!ret && args->out_argvar) अणु
		BUG_ON(args->out_numargs == 0);
		ret = args->out_args[args->out_numargs - 1].size;
	पूर्ण
	fuse_put_request(req);

	वापस ret;
पूर्ण

अटल bool fuse_request_queue_background(काष्ठा fuse_req *req)
अणु
	काष्ठा fuse_mount *fm = req->fm;
	काष्ठा fuse_conn *fc = fm->fc;
	bool queued = false;

	WARN_ON(!test_bit(FR_BACKGROUND, &req->flags));
	अगर (!test_bit(FR_WAITING, &req->flags)) अणु
		__set_bit(FR_WAITING, &req->flags);
		atomic_inc(&fc->num_रुकोing);
	पूर्ण
	__set_bit(FR_ISREPLY, &req->flags);
	spin_lock(&fc->bg_lock);
	अगर (likely(fc->connected)) अणु
		fc->num_background++;
		अगर (fc->num_background == fc->max_background)
			fc->blocked = 1;
		अगर (fc->num_background == fc->congestion_threshold && fm->sb) अणु
			set_bdi_congested(fm->sb->s_bdi, BLK_RW_SYNC);
			set_bdi_congested(fm->sb->s_bdi, BLK_RW_ASYNC);
		पूर्ण
		list_add_tail(&req->list, &fc->bg_queue);
		flush_bg_queue(fc);
		queued = true;
	पूर्ण
	spin_unlock(&fc->bg_lock);

	वापस queued;
पूर्ण

पूर्णांक fuse_simple_background(काष्ठा fuse_mount *fm, काष्ठा fuse_args *args,
			    gfp_t gfp_flags)
अणु
	काष्ठा fuse_req *req;

	अगर (args->क्रमce) अणु
		WARN_ON(!args->nocreds);
		req = fuse_request_alloc(fm, gfp_flags);
		अगर (!req)
			वापस -ENOMEM;
		__set_bit(FR_BACKGROUND, &req->flags);
	पूर्ण अन्यथा अणु
		WARN_ON(args->nocreds);
		req = fuse_get_req(fm, true);
		अगर (IS_ERR(req))
			वापस PTR_ERR(req);
	पूर्ण

	fuse_args_to_req(req, args);

	अगर (!fuse_request_queue_background(req)) अणु
		fuse_put_request(req);
		वापस -ENOTCONN;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_simple_background);

अटल पूर्णांक fuse_simple_notअगरy_reply(काष्ठा fuse_mount *fm,
				    काष्ठा fuse_args *args, u64 unique)
अणु
	काष्ठा fuse_req *req;
	काष्ठा fuse_iqueue *fiq = &fm->fc->iq;
	पूर्णांक err = 0;

	req = fuse_get_req(fm, false);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	__clear_bit(FR_ISREPLY, &req->flags);
	req->in.h.unique = unique;

	fuse_args_to_req(req, args);

	spin_lock(&fiq->lock);
	अगर (fiq->connected) अणु
		queue_request_and_unlock(fiq, req);
	पूर्ण अन्यथा अणु
		err = -ENODEV;
		spin_unlock(&fiq->lock);
		fuse_put_request(req);
	पूर्ण

	वापस err;
पूर्ण

/*
 * Lock the request.  Up to the next unlock_request() there mustn't be
 * anything that could cause a page-fault.  If the request was alपढ़ोy
 * पातed bail out.
 */
अटल पूर्णांक lock_request(काष्ठा fuse_req *req)
अणु
	पूर्णांक err = 0;
	अगर (req) अणु
		spin_lock(&req->रुकोq.lock);
		अगर (test_bit(FR_ABORTED, &req->flags))
			err = -ENOENT;
		अन्यथा
			set_bit(FR_LOCKED, &req->flags);
		spin_unlock(&req->रुकोq.lock);
	पूर्ण
	वापस err;
पूर्ण

/*
 * Unlock request.  If it was पातed जबतक locked, caller is responsible
 * क्रम unlocking and ending the request.
 */
अटल पूर्णांक unlock_request(काष्ठा fuse_req *req)
अणु
	पूर्णांक err = 0;
	अगर (req) अणु
		spin_lock(&req->रुकोq.lock);
		अगर (test_bit(FR_ABORTED, &req->flags))
			err = -ENOENT;
		अन्यथा
			clear_bit(FR_LOCKED, &req->flags);
		spin_unlock(&req->रुकोq.lock);
	पूर्ण
	वापस err;
पूर्ण

काष्ठा fuse_copy_state अणु
	पूर्णांक ग_लिखो;
	काष्ठा fuse_req *req;
	काष्ठा iov_iter *iter;
	काष्ठा pipe_buffer *pipebufs;
	काष्ठा pipe_buffer *currbuf;
	काष्ठा pipe_inode_info *pipe;
	अचिन्हित दीर्घ nr_segs;
	काष्ठा page *pg;
	अचिन्हित len;
	अचिन्हित offset;
	अचिन्हित move_pages:1;
पूर्ण;

अटल व्योम fuse_copy_init(काष्ठा fuse_copy_state *cs, पूर्णांक ग_लिखो,
			   काष्ठा iov_iter *iter)
अणु
	स_रखो(cs, 0, माप(*cs));
	cs->ग_लिखो = ग_लिखो;
	cs->iter = iter;
पूर्ण

/* Unmap and put previous page of userspace buffer */
अटल व्योम fuse_copy_finish(काष्ठा fuse_copy_state *cs)
अणु
	अगर (cs->currbuf) अणु
		काष्ठा pipe_buffer *buf = cs->currbuf;

		अगर (cs->ग_लिखो)
			buf->len = PAGE_SIZE - cs->len;
		cs->currbuf = शून्य;
	पूर्ण अन्यथा अगर (cs->pg) अणु
		अगर (cs->ग_लिखो) अणु
			flush_dcache_page(cs->pg);
			set_page_dirty_lock(cs->pg);
		पूर्ण
		put_page(cs->pg);
	पूर्ण
	cs->pg = शून्य;
पूर्ण

/*
 * Get another pagefull of userspace buffer, and map it to kernel
 * address space, and lock request
 */
अटल पूर्णांक fuse_copy_fill(काष्ठा fuse_copy_state *cs)
अणु
	काष्ठा page *page;
	पूर्णांक err;

	err = unlock_request(cs->req);
	अगर (err)
		वापस err;

	fuse_copy_finish(cs);
	अगर (cs->pipebufs) अणु
		काष्ठा pipe_buffer *buf = cs->pipebufs;

		अगर (!cs->ग_लिखो) अणु
			err = pipe_buf_confirm(cs->pipe, buf);
			अगर (err)
				वापस err;

			BUG_ON(!cs->nr_segs);
			cs->currbuf = buf;
			cs->pg = buf->page;
			cs->offset = buf->offset;
			cs->len = buf->len;
			cs->pipebufs++;
			cs->nr_segs--;
		पूर्ण अन्यथा अणु
			अगर (cs->nr_segs >= cs->pipe->max_usage)
				वापस -EIO;

			page = alloc_page(GFP_HIGHUSER);
			अगर (!page)
				वापस -ENOMEM;

			buf->page = page;
			buf->offset = 0;
			buf->len = 0;

			cs->currbuf = buf;
			cs->pg = page;
			cs->offset = 0;
			cs->len = PAGE_SIZE;
			cs->pipebufs++;
			cs->nr_segs++;
		पूर्ण
	पूर्ण अन्यथा अणु
		माप_प्रकार off;
		err = iov_iter_get_pages(cs->iter, &page, PAGE_SIZE, 1, &off);
		अगर (err < 0)
			वापस err;
		BUG_ON(!err);
		cs->len = err;
		cs->offset = off;
		cs->pg = page;
		iov_iter_advance(cs->iter, err);
	पूर्ण

	वापस lock_request(cs->req);
पूर्ण

/* Do as much copy to/from userspace buffer as we can */
अटल पूर्णांक fuse_copy_करो(काष्ठा fuse_copy_state *cs, व्योम **val, अचिन्हित *size)
अणु
	अचिन्हित ncpy = min(*size, cs->len);
	अगर (val) अणु
		व्योम *pgaddr = kmap_atomic(cs->pg);
		व्योम *buf = pgaddr + cs->offset;

		अगर (cs->ग_लिखो)
			स_नकल(buf, *val, ncpy);
		अन्यथा
			स_नकल(*val, buf, ncpy);

		kunmap_atomic(pgaddr);
		*val += ncpy;
	पूर्ण
	*size -= ncpy;
	cs->len -= ncpy;
	cs->offset += ncpy;
	वापस ncpy;
पूर्ण

अटल पूर्णांक fuse_check_page(काष्ठा page *page)
अणु
	अगर (page_mapcount(page) ||
	    page->mapping != शून्य ||
	    (page->flags & PAGE_FLAGS_CHECK_AT_PREP &
	     ~(1 << PG_locked |
	       1 << PG_referenced |
	       1 << PG_uptodate |
	       1 << PG_lru |
	       1 << PG_active |
	       1 << PG_reclaim |
	       1 << PG_रुकोers))) अणु
		dump_page(page, "fuse: trying to steal weird page");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fuse_try_move_page(काष्ठा fuse_copy_state *cs, काष्ठा page **pagep)
अणु
	पूर्णांक err;
	काष्ठा page *oldpage = *pagep;
	काष्ठा page *newpage;
	काष्ठा pipe_buffer *buf = cs->pipebufs;

	get_page(oldpage);
	err = unlock_request(cs->req);
	अगर (err)
		जाओ out_put_old;

	fuse_copy_finish(cs);

	err = pipe_buf_confirm(cs->pipe, buf);
	अगर (err)
		जाओ out_put_old;

	BUG_ON(!cs->nr_segs);
	cs->currbuf = buf;
	cs->len = buf->len;
	cs->pipebufs++;
	cs->nr_segs--;

	अगर (cs->len != PAGE_SIZE)
		जाओ out_fallback;

	अगर (!pipe_buf_try_steal(cs->pipe, buf))
		जाओ out_fallback;

	newpage = buf->page;

	अगर (!PageUptodate(newpage))
		SetPageUptodate(newpage);

	ClearPageMappedToDisk(newpage);

	अगर (fuse_check_page(newpage) != 0)
		जाओ out_fallback_unlock;

	/*
	 * This is a new and locked page, it shouldn't be mapped or
	 * have any special flags on it
	 */
	अगर (WARN_ON(page_mapped(oldpage)))
		जाओ out_fallback_unlock;
	अगर (WARN_ON(page_has_निजी(oldpage)))
		जाओ out_fallback_unlock;
	अगर (WARN_ON(PageDirty(oldpage) || PageWriteback(oldpage)))
		जाओ out_fallback_unlock;
	अगर (WARN_ON(PageMlocked(oldpage)))
		जाओ out_fallback_unlock;

	replace_page_cache_page(oldpage, newpage);

	get_page(newpage);

	अगर (!(buf->flags & PIPE_BUF_FLAG_LRU))
		lru_cache_add(newpage);

	err = 0;
	spin_lock(&cs->req->रुकोq.lock);
	अगर (test_bit(FR_ABORTED, &cs->req->flags))
		err = -ENOENT;
	अन्यथा
		*pagep = newpage;
	spin_unlock(&cs->req->रुकोq.lock);

	अगर (err) अणु
		unlock_page(newpage);
		put_page(newpage);
		जाओ out_put_old;
	पूर्ण

	unlock_page(oldpage);
	/* Drop ref क्रम ap->pages[] array */
	put_page(oldpage);
	cs->len = 0;

	err = 0;
out_put_old:
	/* Drop ref obtained in this function */
	put_page(oldpage);
	वापस err;

out_fallback_unlock:
	unlock_page(newpage);
out_fallback:
	cs->pg = buf->page;
	cs->offset = buf->offset;

	err = lock_request(cs->req);
	अगर (!err)
		err = 1;

	जाओ out_put_old;
पूर्ण

अटल पूर्णांक fuse_ref_page(काष्ठा fuse_copy_state *cs, काष्ठा page *page,
			 अचिन्हित offset, अचिन्हित count)
अणु
	काष्ठा pipe_buffer *buf;
	पूर्णांक err;

	अगर (cs->nr_segs >= cs->pipe->max_usage)
		वापस -EIO;

	get_page(page);
	err = unlock_request(cs->req);
	अगर (err) अणु
		put_page(page);
		वापस err;
	पूर्ण

	fuse_copy_finish(cs);

	buf = cs->pipebufs;
	buf->page = page;
	buf->offset = offset;
	buf->len = count;

	cs->pipebufs++;
	cs->nr_segs++;
	cs->len = 0;

	वापस 0;
पूर्ण

/*
 * Copy a page in the request to/from the userspace buffer.  Must be
 * करोne atomically
 */
अटल पूर्णांक fuse_copy_page(काष्ठा fuse_copy_state *cs, काष्ठा page **pagep,
			  अचिन्हित offset, अचिन्हित count, पूर्णांक zeroing)
अणु
	पूर्णांक err;
	काष्ठा page *page = *pagep;

	अगर (page && zeroing && count < PAGE_SIZE)
		clear_highpage(page);

	जबतक (count) अणु
		अगर (cs->ग_लिखो && cs->pipebufs && page) अणु
			वापस fuse_ref_page(cs, page, offset, count);
		पूर्ण अन्यथा अगर (!cs->len) अणु
			अगर (cs->move_pages && page &&
			    offset == 0 && count == PAGE_SIZE) अणु
				err = fuse_try_move_page(cs, pagep);
				अगर (err <= 0)
					वापस err;
			पूर्ण अन्यथा अणु
				err = fuse_copy_fill(cs);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण
		अगर (page) अणु
			व्योम *mapaddr = kmap_atomic(page);
			व्योम *buf = mapaddr + offset;
			offset += fuse_copy_करो(cs, &buf, &count);
			kunmap_atomic(mapaddr);
		पूर्ण अन्यथा
			offset += fuse_copy_करो(cs, शून्य, &count);
	पूर्ण
	अगर (page && !cs->ग_लिखो)
		flush_dcache_page(page);
	वापस 0;
पूर्ण

/* Copy pages in the request to/from userspace buffer */
अटल पूर्णांक fuse_copy_pages(काष्ठा fuse_copy_state *cs, अचिन्हित nbytes,
			   पूर्णांक zeroing)
अणु
	अचिन्हित i;
	काष्ठा fuse_req *req = cs->req;
	काष्ठा fuse_args_pages *ap = container_of(req->args, typeof(*ap), args);


	क्रम (i = 0; i < ap->num_pages && (nbytes || zeroing); i++) अणु
		पूर्णांक err;
		अचिन्हित पूर्णांक offset = ap->descs[i].offset;
		अचिन्हित पूर्णांक count = min(nbytes, ap->descs[i].length);

		err = fuse_copy_page(cs, &ap->pages[i], offset, count, zeroing);
		अगर (err)
			वापस err;

		nbytes -= count;
	पूर्ण
	वापस 0;
पूर्ण

/* Copy a single argument in the request to/from userspace buffer */
अटल पूर्णांक fuse_copy_one(काष्ठा fuse_copy_state *cs, व्योम *val, अचिन्हित size)
अणु
	जबतक (size) अणु
		अगर (!cs->len) अणु
			पूर्णांक err = fuse_copy_fill(cs);
			अगर (err)
				वापस err;
		पूर्ण
		fuse_copy_करो(cs, &val, &size);
	पूर्ण
	वापस 0;
पूर्ण

/* Copy request arguments to/from userspace buffer */
अटल पूर्णांक fuse_copy_args(काष्ठा fuse_copy_state *cs, अचिन्हित numargs,
			  अचिन्हित argpages, काष्ठा fuse_arg *args,
			  पूर्णांक zeroing)
अणु
	पूर्णांक err = 0;
	अचिन्हित i;

	क्रम (i = 0; !err && i < numargs; i++)  अणु
		काष्ठा fuse_arg *arg = &args[i];
		अगर (i == numargs - 1 && argpages)
			err = fuse_copy_pages(cs, arg->size, zeroing);
		अन्यथा
			err = fuse_copy_one(cs, arg->value, arg->size);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक क्रमget_pending(काष्ठा fuse_iqueue *fiq)
अणु
	वापस fiq->क्रमget_list_head.next != शून्य;
पूर्ण

अटल पूर्णांक request_pending(काष्ठा fuse_iqueue *fiq)
अणु
	वापस !list_empty(&fiq->pending) || !list_empty(&fiq->पूर्णांकerrupts) ||
		क्रमget_pending(fiq);
पूर्ण

/*
 * Transfer an पूर्णांकerrupt request to userspace
 *
 * Unlike other requests this is assembled on demand, without a need
 * to allocate a separate fuse_req काष्ठाure.
 *
 * Called with fiq->lock held, releases it
 */
अटल पूर्णांक fuse_पढ़ो_पूर्णांकerrupt(काष्ठा fuse_iqueue *fiq,
			       काष्ठा fuse_copy_state *cs,
			       माप_प्रकार nbytes, काष्ठा fuse_req *req)
__releases(fiq->lock)
अणु
	काष्ठा fuse_in_header ih;
	काष्ठा fuse_पूर्णांकerrupt_in arg;
	अचिन्हित reqsize = माप(ih) + माप(arg);
	पूर्णांक err;

	list_del_init(&req->पूर्णांकr_entry);
	स_रखो(&ih, 0, माप(ih));
	स_रखो(&arg, 0, माप(arg));
	ih.len = reqsize;
	ih.opcode = FUSE_INTERRUPT;
	ih.unique = (req->in.h.unique | FUSE_INT_REQ_BIT);
	arg.unique = req->in.h.unique;

	spin_unlock(&fiq->lock);
	अगर (nbytes < reqsize)
		वापस -EINVAL;

	err = fuse_copy_one(cs, &ih, माप(ih));
	अगर (!err)
		err = fuse_copy_one(cs, &arg, माप(arg));
	fuse_copy_finish(cs);

	वापस err ? err : reqsize;
पूर्ण

काष्ठा fuse_क्रमget_link *fuse_dequeue_क्रमget(काष्ठा fuse_iqueue *fiq,
					     अचिन्हित पूर्णांक max,
					     अचिन्हित पूर्णांक *countp)
अणु
	काष्ठा fuse_क्रमget_link *head = fiq->क्रमget_list_head.next;
	काष्ठा fuse_क्रमget_link **newhead = &head;
	अचिन्हित count;

	क्रम (count = 0; *newhead != शून्य && count < max; count++)
		newhead = &(*newhead)->next;

	fiq->क्रमget_list_head.next = *newhead;
	*newhead = शून्य;
	अगर (fiq->क्रमget_list_head.next == शून्य)
		fiq->क्रमget_list_tail = &fiq->क्रमget_list_head;

	अगर (countp != शून्य)
		*countp = count;

	वापस head;
पूर्ण
EXPORT_SYMBOL(fuse_dequeue_क्रमget);

अटल पूर्णांक fuse_पढ़ो_single_क्रमget(काष्ठा fuse_iqueue *fiq,
				   काष्ठा fuse_copy_state *cs,
				   माप_प्रकार nbytes)
__releases(fiq->lock)
अणु
	पूर्णांक err;
	काष्ठा fuse_क्रमget_link *क्रमget = fuse_dequeue_क्रमget(fiq, 1, शून्य);
	काष्ठा fuse_क्रमget_in arg = अणु
		.nlookup = क्रमget->क्रमget_one.nlookup,
	पूर्ण;
	काष्ठा fuse_in_header ih = अणु
		.opcode = FUSE_FORGET,
		.nodeid = क्रमget->क्रमget_one.nodeid,
		.unique = fuse_get_unique(fiq),
		.len = माप(ih) + माप(arg),
	पूर्ण;

	spin_unlock(&fiq->lock);
	kमुक्त(क्रमget);
	अगर (nbytes < ih.len)
		वापस -EINVAL;

	err = fuse_copy_one(cs, &ih, माप(ih));
	अगर (!err)
		err = fuse_copy_one(cs, &arg, माप(arg));
	fuse_copy_finish(cs);

	अगर (err)
		वापस err;

	वापस ih.len;
पूर्ण

अटल पूर्णांक fuse_पढ़ो_batch_क्रमget(काष्ठा fuse_iqueue *fiq,
				   काष्ठा fuse_copy_state *cs, माप_प्रकार nbytes)
__releases(fiq->lock)
अणु
	पूर्णांक err;
	अचिन्हित max_क्रममाला_लो;
	अचिन्हित count;
	काष्ठा fuse_क्रमget_link *head;
	काष्ठा fuse_batch_क्रमget_in arg = अणु .count = 0 पूर्ण;
	काष्ठा fuse_in_header ih = अणु
		.opcode = FUSE_BATCH_FORGET,
		.unique = fuse_get_unique(fiq),
		.len = माप(ih) + माप(arg),
	पूर्ण;

	अगर (nbytes < ih.len) अणु
		spin_unlock(&fiq->lock);
		वापस -EINVAL;
	पूर्ण

	max_क्रममाला_लो = (nbytes - ih.len) / माप(काष्ठा fuse_क्रमget_one);
	head = fuse_dequeue_क्रमget(fiq, max_क्रममाला_लो, &count);
	spin_unlock(&fiq->lock);

	arg.count = count;
	ih.len += count * माप(काष्ठा fuse_क्रमget_one);
	err = fuse_copy_one(cs, &ih, माप(ih));
	अगर (!err)
		err = fuse_copy_one(cs, &arg, माप(arg));

	जबतक (head) अणु
		काष्ठा fuse_क्रमget_link *क्रमget = head;

		अगर (!err) अणु
			err = fuse_copy_one(cs, &क्रमget->क्रमget_one,
					    माप(क्रमget->क्रमget_one));
		पूर्ण
		head = क्रमget->next;
		kमुक्त(क्रमget);
	पूर्ण

	fuse_copy_finish(cs);

	अगर (err)
		वापस err;

	वापस ih.len;
पूर्ण

अटल पूर्णांक fuse_पढ़ो_क्रमget(काष्ठा fuse_conn *fc, काष्ठा fuse_iqueue *fiq,
			    काष्ठा fuse_copy_state *cs,
			    माप_प्रकार nbytes)
__releases(fiq->lock)
अणु
	अगर (fc->minor < 16 || fiq->क्रमget_list_head.next->next == शून्य)
		वापस fuse_पढ़ो_single_क्रमget(fiq, cs, nbytes);
	अन्यथा
		वापस fuse_पढ़ो_batch_क्रमget(fiq, cs, nbytes);
पूर्ण

/*
 * Read a single request पूर्णांकo the userspace fileप्रणाली's buffer.  This
 * function रुकोs until a request is available, then हटाओs it from
 * the pending list and copies request data to userspace buffer.  If
 * no reply is needed (FORGET) or request has been पातed or there
 * was an error during the copying then it's finished by calling
 * fuse_request_end().  Otherwise add it to the processing list, and set
 * the 'sent' flag.
 */
अटल sमाप_प्रकार fuse_dev_करो_पढ़ो(काष्ठा fuse_dev *fud, काष्ठा file *file,
				काष्ठा fuse_copy_state *cs, माप_प्रकार nbytes)
अणु
	sमाप_प्रकार err;
	काष्ठा fuse_conn *fc = fud->fc;
	काष्ठा fuse_iqueue *fiq = &fc->iq;
	काष्ठा fuse_pqueue *fpq = &fud->pq;
	काष्ठा fuse_req *req;
	काष्ठा fuse_args *args;
	अचिन्हित reqsize;
	अचिन्हित पूर्णांक hash;

	/*
	 * Require sane minimum पढ़ो buffer - that has capacity क्रम fixed part
	 * of any request header + negotiated max_ग_लिखो room क्रम data.
	 *
	 * Historically libfuse reserves 4K क्रम fixed header room, but e.g.
	 * GlusterFS reserves only 80 bytes
	 *
	 *	= `माप(fuse_in_header) + माप(fuse_ग_लिखो_in)`
	 *
	 * which is the असलolute minimum any sane fileप्रणाली should be using
	 * क्रम header room.
	 */
	अगर (nbytes < max_t(माप_प्रकार, FUSE_MIN_READ_BUFFER,
			   माप(काष्ठा fuse_in_header) +
			   माप(काष्ठा fuse_ग_लिखो_in) +
			   fc->max_ग_लिखो))
		वापस -EINVAL;

 restart:
	क्रम (;;) अणु
		spin_lock(&fiq->lock);
		अगर (!fiq->connected || request_pending(fiq))
			अवरोध;
		spin_unlock(&fiq->lock);

		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		err = रुको_event_पूर्णांकerruptible_exclusive(fiq->रुकोq,
				!fiq->connected || request_pending(fiq));
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!fiq->connected) अणु
		err = fc->पातed ? -ECONNABORTED : -ENODEV;
		जाओ err_unlock;
	पूर्ण

	अगर (!list_empty(&fiq->पूर्णांकerrupts)) अणु
		req = list_entry(fiq->पूर्णांकerrupts.next, काष्ठा fuse_req,
				 पूर्णांकr_entry);
		वापस fuse_पढ़ो_पूर्णांकerrupt(fiq, cs, nbytes, req);
	पूर्ण

	अगर (क्रमget_pending(fiq)) अणु
		अगर (list_empty(&fiq->pending) || fiq->क्रमget_batch-- > 0)
			वापस fuse_पढ़ो_क्रमget(fc, fiq, cs, nbytes);

		अगर (fiq->क्रमget_batch <= -8)
			fiq->क्रमget_batch = 16;
	पूर्ण

	req = list_entry(fiq->pending.next, काष्ठा fuse_req, list);
	clear_bit(FR_PENDING, &req->flags);
	list_del_init(&req->list);
	spin_unlock(&fiq->lock);

	args = req->args;
	reqsize = req->in.h.len;

	/* If request is too large, reply with an error and restart the पढ़ो */
	अगर (nbytes < reqsize) अणु
		req->out.h.error = -EIO;
		/* SETXATTR is special, since it may contain too large data */
		अगर (args->opcode == FUSE_SETXATTR)
			req->out.h.error = -E2BIG;
		fuse_request_end(req);
		जाओ restart;
	पूर्ण
	spin_lock(&fpq->lock);
	list_add(&req->list, &fpq->io);
	spin_unlock(&fpq->lock);
	cs->req = req;
	err = fuse_copy_one(cs, &req->in.h, माप(req->in.h));
	अगर (!err)
		err = fuse_copy_args(cs, args->in_numargs, args->in_pages,
				     (काष्ठा fuse_arg *) args->in_args, 0);
	fuse_copy_finish(cs);
	spin_lock(&fpq->lock);
	clear_bit(FR_LOCKED, &req->flags);
	अगर (!fpq->connected) अणु
		err = fc->पातed ? -ECONNABORTED : -ENODEV;
		जाओ out_end;
	पूर्ण
	अगर (err) अणु
		req->out.h.error = -EIO;
		जाओ out_end;
	पूर्ण
	अगर (!test_bit(FR_ISREPLY, &req->flags)) अणु
		err = reqsize;
		जाओ out_end;
	पूर्ण
	hash = fuse_req_hash(req->in.h.unique);
	list_move_tail(&req->list, &fpq->processing[hash]);
	__fuse_get_request(req);
	set_bit(FR_SENT, &req->flags);
	spin_unlock(&fpq->lock);
	/* matches barrier in request_रुको_answer() */
	smp_mb__after_atomic();
	अगर (test_bit(FR_INTERRUPTED, &req->flags))
		queue_पूर्णांकerrupt(req);
	fuse_put_request(req);

	वापस reqsize;

out_end:
	अगर (!test_bit(FR_PRIVATE, &req->flags))
		list_del_init(&req->list);
	spin_unlock(&fpq->lock);
	fuse_request_end(req);
	वापस err;

 err_unlock:
	spin_unlock(&fiq->lock);
	वापस err;
पूर्ण

अटल पूर्णांक fuse_dev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 * The fuse device's file's निजी_data is used to hold
	 * the fuse_conn(ection) when it is mounted, and is used to
	 * keep track of whether the file has been mounted alपढ़ोy.
	 */
	file->निजी_data = शून्य;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार fuse_dev_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा fuse_copy_state cs;
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा fuse_dev *fud = fuse_get_dev(file);

	अगर (!fud)
		वापस -EPERM;

	अगर (!iter_is_iovec(to))
		वापस -EINVAL;

	fuse_copy_init(&cs, 1, to);

	वापस fuse_dev_करो_पढ़ो(fud, file, &cs, iov_iter_count(to));
पूर्ण

अटल sमाप_प्रकार fuse_dev_splice_पढ़ो(काष्ठा file *in, loff_t *ppos,
				    काष्ठा pipe_inode_info *pipe,
				    माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक total, ret;
	पूर्णांक page_nr = 0;
	काष्ठा pipe_buffer *bufs;
	काष्ठा fuse_copy_state cs;
	काष्ठा fuse_dev *fud = fuse_get_dev(in);

	अगर (!fud)
		वापस -EPERM;

	bufs = kvदो_स्मृति_array(pipe->max_usage, माप(काष्ठा pipe_buffer),
			      GFP_KERNEL);
	अगर (!bufs)
		वापस -ENOMEM;

	fuse_copy_init(&cs, 1, शून्य);
	cs.pipebufs = bufs;
	cs.pipe = pipe;
	ret = fuse_dev_करो_पढ़ो(fud, in, &cs, len);
	अगर (ret < 0)
		जाओ out;

	अगर (pipe_occupancy(pipe->head, pipe->tail) + cs.nr_segs > pipe->max_usage) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	क्रम (ret = total = 0; page_nr < cs.nr_segs; total += ret) अणु
		/*
		 * Need to be careful about this.  Having buf->ops in module
		 * code can Oops अगर the buffer persists after module unload.
		 */
		bufs[page_nr].ops = &nosteal_pipe_buf_ops;
		bufs[page_nr].flags = 0;
		ret = add_to_pipe(pipe, &bufs[page_nr++]);
		अगर (unlikely(ret < 0))
			अवरोध;
	पूर्ण
	अगर (total)
		ret = total;
out:
	क्रम (; page_nr < cs.nr_segs; page_nr++)
		put_page(bufs[page_nr].page);

	kvमुक्त(bufs);
	वापस ret;
पूर्ण

अटल पूर्णांक fuse_notअगरy_poll(काष्ठा fuse_conn *fc, अचिन्हित पूर्णांक size,
			    काष्ठा fuse_copy_state *cs)
अणु
	काष्ठा fuse_notअगरy_poll_wakeup_out outarg;
	पूर्णांक err = -EINVAL;

	अगर (size != माप(outarg))
		जाओ err;

	err = fuse_copy_one(cs, &outarg, माप(outarg));
	अगर (err)
		जाओ err;

	fuse_copy_finish(cs);
	वापस fuse_notअगरy_poll_wakeup(fc, &outarg);

err:
	fuse_copy_finish(cs);
	वापस err;
पूर्ण

अटल पूर्णांक fuse_notअगरy_inval_inode(काष्ठा fuse_conn *fc, अचिन्हित पूर्णांक size,
				   काष्ठा fuse_copy_state *cs)
अणु
	काष्ठा fuse_notअगरy_inval_inode_out outarg;
	पूर्णांक err = -EINVAL;

	अगर (size != माप(outarg))
		जाओ err;

	err = fuse_copy_one(cs, &outarg, माप(outarg));
	अगर (err)
		जाओ err;
	fuse_copy_finish(cs);

	करोwn_पढ़ो(&fc->समाप्तsb);
	err = fuse_reverse_inval_inode(fc, outarg.ino,
				       outarg.off, outarg.len);
	up_पढ़ो(&fc->समाप्तsb);
	वापस err;

err:
	fuse_copy_finish(cs);
	वापस err;
पूर्ण

अटल पूर्णांक fuse_notअगरy_inval_entry(काष्ठा fuse_conn *fc, अचिन्हित पूर्णांक size,
				   काष्ठा fuse_copy_state *cs)
अणु
	काष्ठा fuse_notअगरy_inval_entry_out outarg;
	पूर्णांक err = -ENOMEM;
	अक्षर *buf;
	काष्ठा qstr name;

	buf = kzalloc(FUSE_NAME_MAX + 1, GFP_KERNEL);
	अगर (!buf)
		जाओ err;

	err = -EINVAL;
	अगर (size < माप(outarg))
		जाओ err;

	err = fuse_copy_one(cs, &outarg, माप(outarg));
	अगर (err)
		जाओ err;

	err = -ENAMETOOLONG;
	अगर (outarg.namelen > FUSE_NAME_MAX)
		जाओ err;

	err = -EINVAL;
	अगर (size != माप(outarg) + outarg.namelen + 1)
		जाओ err;

	name.name = buf;
	name.len = outarg.namelen;
	err = fuse_copy_one(cs, buf, outarg.namelen + 1);
	अगर (err)
		जाओ err;
	fuse_copy_finish(cs);
	buf[outarg.namelen] = 0;

	करोwn_पढ़ो(&fc->समाप्तsb);
	err = fuse_reverse_inval_entry(fc, outarg.parent, 0, &name);
	up_पढ़ो(&fc->समाप्तsb);
	kमुक्त(buf);
	वापस err;

err:
	kमुक्त(buf);
	fuse_copy_finish(cs);
	वापस err;
पूर्ण

अटल पूर्णांक fuse_notअगरy_delete(काष्ठा fuse_conn *fc, अचिन्हित पूर्णांक size,
			      काष्ठा fuse_copy_state *cs)
अणु
	काष्ठा fuse_notअगरy_delete_out outarg;
	पूर्णांक err = -ENOMEM;
	अक्षर *buf;
	काष्ठा qstr name;

	buf = kzalloc(FUSE_NAME_MAX + 1, GFP_KERNEL);
	अगर (!buf)
		जाओ err;

	err = -EINVAL;
	अगर (size < माप(outarg))
		जाओ err;

	err = fuse_copy_one(cs, &outarg, माप(outarg));
	अगर (err)
		जाओ err;

	err = -ENAMETOOLONG;
	अगर (outarg.namelen > FUSE_NAME_MAX)
		जाओ err;

	err = -EINVAL;
	अगर (size != माप(outarg) + outarg.namelen + 1)
		जाओ err;

	name.name = buf;
	name.len = outarg.namelen;
	err = fuse_copy_one(cs, buf, outarg.namelen + 1);
	अगर (err)
		जाओ err;
	fuse_copy_finish(cs);
	buf[outarg.namelen] = 0;

	करोwn_पढ़ो(&fc->समाप्तsb);
	err = fuse_reverse_inval_entry(fc, outarg.parent, outarg.child, &name);
	up_पढ़ो(&fc->समाप्तsb);
	kमुक्त(buf);
	वापस err;

err:
	kमुक्त(buf);
	fuse_copy_finish(cs);
	वापस err;
पूर्ण

अटल पूर्णांक fuse_notअगरy_store(काष्ठा fuse_conn *fc, अचिन्हित पूर्णांक size,
			     काष्ठा fuse_copy_state *cs)
अणु
	काष्ठा fuse_notअगरy_store_out outarg;
	काष्ठा inode *inode;
	काष्ठा address_space *mapping;
	u64 nodeid;
	पूर्णांक err;
	pgoff_t index;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक num;
	loff_t file_size;
	loff_t end;

	err = -EINVAL;
	अगर (size < माप(outarg))
		जाओ out_finish;

	err = fuse_copy_one(cs, &outarg, माप(outarg));
	अगर (err)
		जाओ out_finish;

	err = -EINVAL;
	अगर (size - माप(outarg) != outarg.size)
		जाओ out_finish;

	nodeid = outarg.nodeid;

	करोwn_पढ़ो(&fc->समाप्तsb);

	err = -ENOENT;
	inode = fuse_ilookup(fc, nodeid,  शून्य);
	अगर (!inode)
		जाओ out_up_समाप्तsb;

	mapping = inode->i_mapping;
	index = outarg.offset >> PAGE_SHIFT;
	offset = outarg.offset & ~PAGE_MASK;
	file_size = i_size_पढ़ो(inode);
	end = outarg.offset + outarg.size;
	अगर (end > file_size) अणु
		file_size = end;
		fuse_ग_लिखो_update_size(inode, file_size);
	पूर्ण

	num = outarg.size;
	जबतक (num) अणु
		काष्ठा page *page;
		अचिन्हित पूर्णांक this_num;

		err = -ENOMEM;
		page = find_or_create_page(mapping, index,
					   mapping_gfp_mask(mapping));
		अगर (!page)
			जाओ out_iput;

		this_num = min_t(अचिन्हित, num, PAGE_SIZE - offset);
		err = fuse_copy_page(cs, &page, offset, this_num, 0);
		अगर (!err && offset == 0 &&
		    (this_num == PAGE_SIZE || file_size == end))
			SetPageUptodate(page);
		unlock_page(page);
		put_page(page);

		अगर (err)
			जाओ out_iput;

		num -= this_num;
		offset = 0;
		index++;
	पूर्ण

	err = 0;

out_iput:
	iput(inode);
out_up_समाप्तsb:
	up_पढ़ो(&fc->समाप्तsb);
out_finish:
	fuse_copy_finish(cs);
	वापस err;
पूर्ण

काष्ठा fuse_retrieve_args अणु
	काष्ठा fuse_args_pages ap;
	काष्ठा fuse_notअगरy_retrieve_in inarg;
पूर्ण;

अटल व्योम fuse_retrieve_end(काष्ठा fuse_mount *fm, काष्ठा fuse_args *args,
			      पूर्णांक error)
अणु
	काष्ठा fuse_retrieve_args *ra =
		container_of(args, typeof(*ra), ap.args);

	release_pages(ra->ap.pages, ra->ap.num_pages);
	kमुक्त(ra);
पूर्ण

अटल पूर्णांक fuse_retrieve(काष्ठा fuse_mount *fm, काष्ठा inode *inode,
			 काष्ठा fuse_notअगरy_retrieve_out *outarg)
अणु
	पूर्णांक err;
	काष्ठा address_space *mapping = inode->i_mapping;
	pgoff_t index;
	loff_t file_size;
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक offset;
	माप_प्रकार total_len = 0;
	अचिन्हित पूर्णांक num_pages;
	काष्ठा fuse_conn *fc = fm->fc;
	काष्ठा fuse_retrieve_args *ra;
	माप_प्रकार args_size = माप(*ra);
	काष्ठा fuse_args_pages *ap;
	काष्ठा fuse_args *args;

	offset = outarg->offset & ~PAGE_MASK;
	file_size = i_size_पढ़ो(inode);

	num = min(outarg->size, fc->max_ग_लिखो);
	अगर (outarg->offset > file_size)
		num = 0;
	अन्यथा अगर (outarg->offset + num > file_size)
		num = file_size - outarg->offset;

	num_pages = (num + offset + PAGE_SIZE - 1) >> PAGE_SHIFT;
	num_pages = min(num_pages, fc->max_pages);

	args_size += num_pages * (माप(ap->pages[0]) + माप(ap->descs[0]));

	ra = kzalloc(args_size, GFP_KERNEL);
	अगर (!ra)
		वापस -ENOMEM;

	ap = &ra->ap;
	ap->pages = (व्योम *) (ra + 1);
	ap->descs = (व्योम *) (ap->pages + num_pages);

	args = &ap->args;
	args->nodeid = outarg->nodeid;
	args->opcode = FUSE_NOTIFY_REPLY;
	args->in_numargs = 2;
	args->in_pages = true;
	args->end = fuse_retrieve_end;

	index = outarg->offset >> PAGE_SHIFT;

	जबतक (num && ap->num_pages < num_pages) अणु
		काष्ठा page *page;
		अचिन्हित पूर्णांक this_num;

		page = find_get_page(mapping, index);
		अगर (!page)
			अवरोध;

		this_num = min_t(अचिन्हित, num, PAGE_SIZE - offset);
		ap->pages[ap->num_pages] = page;
		ap->descs[ap->num_pages].offset = offset;
		ap->descs[ap->num_pages].length = this_num;
		ap->num_pages++;

		offset = 0;
		num -= this_num;
		total_len += this_num;
		index++;
	पूर्ण
	ra->inarg.offset = outarg->offset;
	ra->inarg.size = total_len;
	args->in_args[0].size = माप(ra->inarg);
	args->in_args[0].value = &ra->inarg;
	args->in_args[1].size = total_len;

	err = fuse_simple_notअगरy_reply(fm, args, outarg->notअगरy_unique);
	अगर (err)
		fuse_retrieve_end(fm, args, err);

	वापस err;
पूर्ण

अटल पूर्णांक fuse_notअगरy_retrieve(काष्ठा fuse_conn *fc, अचिन्हित पूर्णांक size,
				काष्ठा fuse_copy_state *cs)
अणु
	काष्ठा fuse_notअगरy_retrieve_out outarg;
	काष्ठा fuse_mount *fm;
	काष्ठा inode *inode;
	u64 nodeid;
	पूर्णांक err;

	err = -EINVAL;
	अगर (size != माप(outarg))
		जाओ copy_finish;

	err = fuse_copy_one(cs, &outarg, माप(outarg));
	अगर (err)
		जाओ copy_finish;

	fuse_copy_finish(cs);

	करोwn_पढ़ो(&fc->समाप्तsb);
	err = -ENOENT;
	nodeid = outarg.nodeid;

	inode = fuse_ilookup(fc, nodeid, &fm);
	अगर (inode) अणु
		err = fuse_retrieve(fm, inode, &outarg);
		iput(inode);
	पूर्ण
	up_पढ़ो(&fc->समाप्तsb);

	वापस err;

copy_finish:
	fuse_copy_finish(cs);
	वापस err;
पूर्ण

अटल पूर्णांक fuse_notअगरy(काष्ठा fuse_conn *fc, क्रमागत fuse_notअगरy_code code,
		       अचिन्हित पूर्णांक size, काष्ठा fuse_copy_state *cs)
अणु
	/* Don't try to move pages (yet) */
	cs->move_pages = 0;

	चयन (code) अणु
	हाल FUSE_NOTIFY_POLL:
		वापस fuse_notअगरy_poll(fc, size, cs);

	हाल FUSE_NOTIFY_INVAL_INODE:
		वापस fuse_notअगरy_inval_inode(fc, size, cs);

	हाल FUSE_NOTIFY_INVAL_ENTRY:
		वापस fuse_notअगरy_inval_entry(fc, size, cs);

	हाल FUSE_NOTIFY_STORE:
		वापस fuse_notअगरy_store(fc, size, cs);

	हाल FUSE_NOTIFY_RETRIEVE:
		वापस fuse_notअगरy_retrieve(fc, size, cs);

	हाल FUSE_NOTIFY_DELETE:
		वापस fuse_notअगरy_delete(fc, size, cs);

	शेष:
		fuse_copy_finish(cs);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Look up request on processing list by unique ID */
अटल काष्ठा fuse_req *request_find(काष्ठा fuse_pqueue *fpq, u64 unique)
अणु
	अचिन्हित पूर्णांक hash = fuse_req_hash(unique);
	काष्ठा fuse_req *req;

	list_क्रम_each_entry(req, &fpq->processing[hash], list) अणु
		अगर (req->in.h.unique == unique)
			वापस req;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक copy_out_args(काष्ठा fuse_copy_state *cs, काष्ठा fuse_args *args,
			 अचिन्हित nbytes)
अणु
	अचिन्हित reqsize = माप(काष्ठा fuse_out_header);

	reqsize += fuse_len_args(args->out_numargs, args->out_args);

	अगर (reqsize < nbytes || (reqsize > nbytes && !args->out_argvar))
		वापस -EINVAL;
	अन्यथा अगर (reqsize > nbytes) अणु
		काष्ठा fuse_arg *lastarg = &args->out_args[args->out_numargs-1];
		अचिन्हित dअगरfsize = reqsize - nbytes;

		अगर (dअगरfsize > lastarg->size)
			वापस -EINVAL;
		lastarg->size -= dअगरfsize;
	पूर्ण
	वापस fuse_copy_args(cs, args->out_numargs, args->out_pages,
			      args->out_args, args->page_zeroing);
पूर्ण

/*
 * Write a single reply to a request.  First the header is copied from
 * the ग_लिखो buffer.  The request is then searched on the processing
 * list by the unique ID found in the header.  If found, then हटाओ
 * it from the list and copy the rest of the buffer to the request.
 * The request is finished by calling fuse_request_end().
 */
अटल sमाप_प्रकार fuse_dev_करो_ग_लिखो(काष्ठा fuse_dev *fud,
				 काष्ठा fuse_copy_state *cs, माप_प्रकार nbytes)
अणु
	पूर्णांक err;
	काष्ठा fuse_conn *fc = fud->fc;
	काष्ठा fuse_pqueue *fpq = &fud->pq;
	काष्ठा fuse_req *req;
	काष्ठा fuse_out_header oh;

	err = -EINVAL;
	अगर (nbytes < माप(काष्ठा fuse_out_header))
		जाओ out;

	err = fuse_copy_one(cs, &oh, माप(oh));
	अगर (err)
		जाओ copy_finish;

	err = -EINVAL;
	अगर (oh.len != nbytes)
		जाओ copy_finish;

	/*
	 * Zero oh.unique indicates unsolicited notअगरication message
	 * and error contains notअगरication code.
	 */
	अगर (!oh.unique) अणु
		err = fuse_notअगरy(fc, oh.error, nbytes - माप(oh), cs);
		जाओ out;
	पूर्ण

	err = -EINVAL;
	अगर (oh.error <= -1000 || oh.error > 0)
		जाओ copy_finish;

	spin_lock(&fpq->lock);
	req = शून्य;
	अगर (fpq->connected)
		req = request_find(fpq, oh.unique & ~FUSE_INT_REQ_BIT);

	err = -ENOENT;
	अगर (!req) अणु
		spin_unlock(&fpq->lock);
		जाओ copy_finish;
	पूर्ण

	/* Is it an पूर्णांकerrupt reply ID? */
	अगर (oh.unique & FUSE_INT_REQ_BIT) अणु
		__fuse_get_request(req);
		spin_unlock(&fpq->lock);

		err = 0;
		अगर (nbytes != माप(काष्ठा fuse_out_header))
			err = -EINVAL;
		अन्यथा अगर (oh.error == -ENOSYS)
			fc->no_पूर्णांकerrupt = 1;
		अन्यथा अगर (oh.error == -EAGAIN)
			err = queue_पूर्णांकerrupt(req);

		fuse_put_request(req);

		जाओ copy_finish;
	पूर्ण

	clear_bit(FR_SENT, &req->flags);
	list_move(&req->list, &fpq->io);
	req->out.h = oh;
	set_bit(FR_LOCKED, &req->flags);
	spin_unlock(&fpq->lock);
	cs->req = req;
	अगर (!req->args->page_replace)
		cs->move_pages = 0;

	अगर (oh.error)
		err = nbytes != माप(oh) ? -EINVAL : 0;
	अन्यथा
		err = copy_out_args(cs, req->args, nbytes);
	fuse_copy_finish(cs);

	spin_lock(&fpq->lock);
	clear_bit(FR_LOCKED, &req->flags);
	अगर (!fpq->connected)
		err = -ENOENT;
	अन्यथा अगर (err)
		req->out.h.error = -EIO;
	अगर (!test_bit(FR_PRIVATE, &req->flags))
		list_del_init(&req->list);
	spin_unlock(&fpq->lock);

	fuse_request_end(req);
out:
	वापस err ? err : nbytes;

copy_finish:
	fuse_copy_finish(cs);
	जाओ out;
पूर्ण

अटल sमाप_प्रकार fuse_dev_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा fuse_copy_state cs;
	काष्ठा fuse_dev *fud = fuse_get_dev(iocb->ki_filp);

	अगर (!fud)
		वापस -EPERM;

	अगर (!iter_is_iovec(from))
		वापस -EINVAL;

	fuse_copy_init(&cs, 0, from);

	वापस fuse_dev_करो_ग_लिखो(fud, &cs, iov_iter_count(from));
पूर्ण

अटल sमाप_प्रकार fuse_dev_splice_ग_लिखो(काष्ठा pipe_inode_info *pipe,
				     काष्ठा file *out, loff_t *ppos,
				     माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक head, tail, mask, count;
	अचिन्हित nbuf;
	अचिन्हित idx;
	काष्ठा pipe_buffer *bufs;
	काष्ठा fuse_copy_state cs;
	काष्ठा fuse_dev *fud;
	माप_प्रकार rem;
	sमाप_प्रकार ret;

	fud = fuse_get_dev(out);
	अगर (!fud)
		वापस -EPERM;

	pipe_lock(pipe);

	head = pipe->head;
	tail = pipe->tail;
	mask = pipe->ring_size - 1;
	count = head - tail;

	bufs = kvदो_स्मृति_array(count, माप(काष्ठा pipe_buffer), GFP_KERNEL);
	अगर (!bufs) अणु
		pipe_unlock(pipe);
		वापस -ENOMEM;
	पूर्ण

	nbuf = 0;
	rem = 0;
	क्रम (idx = tail; idx != head && rem < len; idx++)
		rem += pipe->bufs[idx & mask].len;

	ret = -EINVAL;
	अगर (rem < len)
		जाओ out_मुक्त;

	rem = len;
	जबतक (rem) अणु
		काष्ठा pipe_buffer *ibuf;
		काष्ठा pipe_buffer *obuf;

		अगर (WARN_ON(nbuf >= count || tail == head))
			जाओ out_मुक्त;

		ibuf = &pipe->bufs[tail & mask];
		obuf = &bufs[nbuf];

		अगर (rem >= ibuf->len) अणु
			*obuf = *ibuf;
			ibuf->ops = शून्य;
			tail++;
			pipe->tail = tail;
		पूर्ण अन्यथा अणु
			अगर (!pipe_buf_get(pipe, ibuf))
				जाओ out_मुक्त;

			*obuf = *ibuf;
			obuf->flags &= ~PIPE_BUF_FLAG_GIFT;
			obuf->len = rem;
			ibuf->offset += obuf->len;
			ibuf->len -= obuf->len;
		पूर्ण
		nbuf++;
		rem -= obuf->len;
	पूर्ण
	pipe_unlock(pipe);

	fuse_copy_init(&cs, 0, शून्य);
	cs.pipebufs = bufs;
	cs.nr_segs = nbuf;
	cs.pipe = pipe;

	अगर (flags & SPLICE_F_MOVE)
		cs.move_pages = 1;

	ret = fuse_dev_करो_ग_लिखो(fud, &cs, len);

	pipe_lock(pipe);
out_मुक्त:
	क्रम (idx = 0; idx < nbuf; idx++)
		pipe_buf_release(pipe, &bufs[idx]);
	pipe_unlock(pipe);

	kvमुक्त(bufs);
	वापस ret;
पूर्ण

अटल __poll_t fuse_dev_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t mask = EPOLLOUT | EPOLLWRNORM;
	काष्ठा fuse_iqueue *fiq;
	काष्ठा fuse_dev *fud = fuse_get_dev(file);

	अगर (!fud)
		वापस EPOLLERR;

	fiq = &fud->fc->iq;
	poll_रुको(file, &fiq->रुकोq, रुको);

	spin_lock(&fiq->lock);
	अगर (!fiq->connected)
		mask = EPOLLERR;
	अन्यथा अगर (request_pending(fiq))
		mask |= EPOLLIN | EPOLLRDNORM;
	spin_unlock(&fiq->lock);

	वापस mask;
पूर्ण

/* Abort all requests on the given list (pending or processing) */
अटल व्योम end_requests(काष्ठा list_head *head)
अणु
	जबतक (!list_empty(head)) अणु
		काष्ठा fuse_req *req;
		req = list_entry(head->next, काष्ठा fuse_req, list);
		req->out.h.error = -ECONNABORTED;
		clear_bit(FR_SENT, &req->flags);
		list_del_init(&req->list);
		fuse_request_end(req);
	पूर्ण
पूर्ण

अटल व्योम end_polls(काष्ठा fuse_conn *fc)
अणु
	काष्ठा rb_node *p;

	p = rb_first(&fc->polled_files);

	जबतक (p) अणु
		काष्ठा fuse_file *ff;
		ff = rb_entry(p, काष्ठा fuse_file, polled_node);
		wake_up_पूर्णांकerruptible_all(&ff->poll_रुको);

		p = rb_next(p);
	पूर्ण
पूर्ण

/*
 * Abort all requests.
 *
 * Emergency निकास in हाल of a malicious or accidental deadlock, or just a hung
 * fileप्रणाली.
 *
 * The same effect is usually achievable through समाप्तing the fileप्रणाली daemon
 * and all users of the fileप्रणाली.  The exception is the combination of an
 * asynchronous request and the tricky deadlock (see
 * Documentation/fileप्रणालीs/fuse.rst).
 *
 * Aborting requests under I/O goes as follows: 1: Separate out unlocked
 * requests, they should be finished off immediately.  Locked requests will be
 * finished after unlock; see unlock_request(). 2: Finish off the unlocked
 * requests.  It is possible that some request will finish beक्रमe we can.  This
 * is OK, the request will in that हाल be हटाओd from the list beक्रमe we touch
 * it.
 */
व्योम fuse_पात_conn(काष्ठा fuse_conn *fc)
अणु
	काष्ठा fuse_iqueue *fiq = &fc->iq;

	spin_lock(&fc->lock);
	अगर (fc->connected) अणु
		काष्ठा fuse_dev *fud;
		काष्ठा fuse_req *req, *next;
		LIST_HEAD(to_end);
		अचिन्हित पूर्णांक i;

		/* Background queuing checks fc->connected under bg_lock */
		spin_lock(&fc->bg_lock);
		fc->connected = 0;
		spin_unlock(&fc->bg_lock);

		fuse_set_initialized(fc);
		list_क्रम_each_entry(fud, &fc->devices, entry) अणु
			काष्ठा fuse_pqueue *fpq = &fud->pq;

			spin_lock(&fpq->lock);
			fpq->connected = 0;
			list_क्रम_each_entry_safe(req, next, &fpq->io, list) अणु
				req->out.h.error = -ECONNABORTED;
				spin_lock(&req->रुकोq.lock);
				set_bit(FR_ABORTED, &req->flags);
				अगर (!test_bit(FR_LOCKED, &req->flags)) अणु
					set_bit(FR_PRIVATE, &req->flags);
					__fuse_get_request(req);
					list_move(&req->list, &to_end);
				पूर्ण
				spin_unlock(&req->रुकोq.lock);
			पूर्ण
			क्रम (i = 0; i < FUSE_PQ_HASH_SIZE; i++)
				list_splice_tail_init(&fpq->processing[i],
						      &to_end);
			spin_unlock(&fpq->lock);
		पूर्ण
		spin_lock(&fc->bg_lock);
		fc->blocked = 0;
		fc->max_background = अच_पूर्णांक_उच्च;
		flush_bg_queue(fc);
		spin_unlock(&fc->bg_lock);

		spin_lock(&fiq->lock);
		fiq->connected = 0;
		list_क्रम_each_entry(req, &fiq->pending, list)
			clear_bit(FR_PENDING, &req->flags);
		list_splice_tail_init(&fiq->pending, &to_end);
		जबतक (क्रमget_pending(fiq))
			kमुक्त(fuse_dequeue_क्रमget(fiq, 1, शून्य));
		wake_up_all(&fiq->रुकोq);
		spin_unlock(&fiq->lock);
		समाप्त_fasync(&fiq->fasync, SIGIO, POLL_IN);
		end_polls(fc);
		wake_up_all(&fc->blocked_रुकोq);
		spin_unlock(&fc->lock);

		end_requests(&to_end);
	पूर्ण अन्यथा अणु
		spin_unlock(&fc->lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fuse_पात_conn);

व्योम fuse_रुको_पातed(काष्ठा fuse_conn *fc)
अणु
	/* matches implicit memory barrier in fuse_drop_रुकोing() */
	smp_mb();
	रुको_event(fc->blocked_रुकोq, atomic_पढ़ो(&fc->num_रुकोing) == 0);
पूर्ण

पूर्णांक fuse_dev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fuse_dev *fud = fuse_get_dev(file);

	अगर (fud) अणु
		काष्ठा fuse_conn *fc = fud->fc;
		काष्ठा fuse_pqueue *fpq = &fud->pq;
		LIST_HEAD(to_end);
		अचिन्हित पूर्णांक i;

		spin_lock(&fpq->lock);
		WARN_ON(!list_empty(&fpq->io));
		क्रम (i = 0; i < FUSE_PQ_HASH_SIZE; i++)
			list_splice_init(&fpq->processing[i], &to_end);
		spin_unlock(&fpq->lock);

		end_requests(&to_end);

		/* Are we the last खोलो device? */
		अगर (atomic_dec_and_test(&fc->dev_count)) अणु
			WARN_ON(fc->iq.fasync != शून्य);
			fuse_पात_conn(fc);
		पूर्ण
		fuse_dev_मुक्त(fud);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_dev_release);

अटल पूर्णांक fuse_dev_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा fuse_dev *fud = fuse_get_dev(file);

	अगर (!fud)
		वापस -EPERM;

	/* No locking - fasync_helper करोes its own locking */
	वापस fasync_helper(fd, file, on, &fud->fc->iq.fasync);
पूर्ण

अटल पूर्णांक fuse_device_clone(काष्ठा fuse_conn *fc, काष्ठा file *new)
अणु
	काष्ठा fuse_dev *fud;

	अगर (new->निजी_data)
		वापस -EINVAL;

	fud = fuse_dev_alloc_install(fc);
	अगर (!fud)
		वापस -ENOMEM;

	new->निजी_data = fud;
	atomic_inc(&fc->dev_count);

	वापस 0;
पूर्ण

अटल दीर्घ fuse_dev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			   अचिन्हित दीर्घ arg)
अणु
	पूर्णांक res;
	पूर्णांक oldfd;
	काष्ठा fuse_dev *fud = शून्य;

	चयन (cmd) अणु
	हाल FUSE_DEV_IOC_CLONE:
		res = -EFAULT;
		अगर (!get_user(oldfd, (__u32 __user *)arg)) अणु
			काष्ठा file *old = fget(oldfd);

			res = -EINVAL;
			अगर (old) अणु
				/*
				 * Check against file->f_op because CUSE
				 * uses the same ioctl handler.
				 */
				अगर (old->f_op == file->f_op &&
				    old->f_cred->user_ns == file->f_cred->user_ns)
					fud = fuse_get_dev(old);

				अगर (fud) अणु
					mutex_lock(&fuse_mutex);
					res = fuse_device_clone(fud->fc, file);
					mutex_unlock(&fuse_mutex);
				पूर्ण
				fput(old);
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		res = -ENOTTY;
		अवरोध;
	पूर्ण
	वापस res;
पूर्ण

स्थिर काष्ठा file_operations fuse_dev_operations = अणु
	.owner		= THIS_MODULE,
	.खोलो		= fuse_dev_खोलो,
	.llseek		= no_llseek,
	.पढ़ो_iter	= fuse_dev_पढ़ो,
	.splice_पढ़ो	= fuse_dev_splice_पढ़ो,
	.ग_लिखो_iter	= fuse_dev_ग_लिखो,
	.splice_ग_लिखो	= fuse_dev_splice_ग_लिखो,
	.poll		= fuse_dev_poll,
	.release	= fuse_dev_release,
	.fasync		= fuse_dev_fasync,
	.unlocked_ioctl = fuse_dev_ioctl,
	.compat_ioctl   = compat_ptr_ioctl,
पूर्ण;
EXPORT_SYMBOL_GPL(fuse_dev_operations);

अटल काष्ठा miscdevice fuse_miscdevice = अणु
	.minor = FUSE_MINOR,
	.name  = "fuse",
	.fops = &fuse_dev_operations,
पूर्ण;

पूर्णांक __init fuse_dev_init(व्योम)
अणु
	पूर्णांक err = -ENOMEM;
	fuse_req_cachep = kmem_cache_create("fuse_request",
					    माप(काष्ठा fuse_req),
					    0, 0, शून्य);
	अगर (!fuse_req_cachep)
		जाओ out;

	err = misc_रेजिस्टर(&fuse_miscdevice);
	अगर (err)
		जाओ out_cache_clean;

	वापस 0;

 out_cache_clean:
	kmem_cache_destroy(fuse_req_cachep);
 out:
	वापस err;
पूर्ण

व्योम fuse_dev_cleanup(व्योम)
अणु
	misc_deरेजिस्टर(&fuse_miscdevice);
	kmem_cache_destroy(fuse_req_cachep);
पूर्ण
