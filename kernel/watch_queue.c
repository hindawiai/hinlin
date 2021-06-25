<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Watch queue and general notअगरication mechanism, built on pipes
 *
 * Copyright (C) 2020 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * See Documentation/watch_queue.rst
 */

#घोषणा pr_fmt(fmt) "watchq: " fmt
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/poll.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/file.h>
#समावेश <linux/security.h>
#समावेश <linux/cred.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/watch_queue.h>
#समावेश <linux/pipe_fs_i.h>

MODULE_DESCRIPTION("Watch queue");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");

#घोषणा WATCH_QUEUE_NOTE_SIZE 128
#घोषणा WATCH_QUEUE_NOTES_PER_PAGE (PAGE_SIZE / WATCH_QUEUE_NOTE_SIZE)

अटल व्योम watch_queue_pipe_buf_release(काष्ठा pipe_inode_info *pipe,
					 काष्ठा pipe_buffer *buf)
अणु
	काष्ठा watch_queue *wqueue = (काष्ठा watch_queue *)buf->निजी;
	काष्ठा page *page;
	अचिन्हित पूर्णांक bit;

	/* We need to work out which note within the page this refers to, but
	 * the note might have been maximum size, so merely ANDing the offset
	 * off करोesn't work.  OTOH, the note must've been more than zero size.
	 */
	bit = buf->offset + buf->len;
	अगर ((bit & (WATCH_QUEUE_NOTE_SIZE - 1)) == 0)
		bit -= WATCH_QUEUE_NOTE_SIZE;
	bit /= WATCH_QUEUE_NOTE_SIZE;

	page = buf->page;
	bit += page->index;

	set_bit(bit, wqueue->notes_biपंचांगap);
पूर्ण

// No try_steal function => no stealing
#घोषणा watch_queue_pipe_buf_try_steal शून्य

/* New data written to a pipe may be appended to a buffer with this type. */
अटल स्थिर काष्ठा pipe_buf_operations watch_queue_pipe_buf_ops = अणु
	.release	= watch_queue_pipe_buf_release,
	.try_steal	= watch_queue_pipe_buf_try_steal,
	.get		= generic_pipe_buf_get,
पूर्ण;

/*
 * Post a notअगरication to a watch queue.
 */
अटल bool post_one_notअगरication(काष्ठा watch_queue *wqueue,
				  काष्ठा watch_notअगरication *n)
अणु
	व्योम *p;
	काष्ठा pipe_inode_info *pipe = wqueue->pipe;
	काष्ठा pipe_buffer *buf;
	काष्ठा page *page;
	अचिन्हित पूर्णांक head, tail, mask, note, offset, len;
	bool करोne = false;

	अगर (!pipe)
		वापस false;

	spin_lock_irq(&pipe->rd_रुको.lock);

	अगर (wqueue->defunct)
		जाओ out;

	mask = pipe->ring_size - 1;
	head = pipe->head;
	tail = pipe->tail;
	अगर (pipe_full(head, tail, pipe->ring_size))
		जाओ lost;

	note = find_first_bit(wqueue->notes_biपंचांगap, wqueue->nr_notes);
	अगर (note >= wqueue->nr_notes)
		जाओ lost;

	page = wqueue->notes[note / WATCH_QUEUE_NOTES_PER_PAGE];
	offset = note % WATCH_QUEUE_NOTES_PER_PAGE * WATCH_QUEUE_NOTE_SIZE;
	get_page(page);
	len = n->info & WATCH_INFO_LENGTH;
	p = kmap_atomic(page);
	स_नकल(p + offset, n, len);
	kunmap_atomic(p);

	buf = &pipe->bufs[head & mask];
	buf->page = page;
	buf->निजी = (अचिन्हित दीर्घ)wqueue;
	buf->ops = &watch_queue_pipe_buf_ops;
	buf->offset = offset;
	buf->len = len;
	buf->flags = PIPE_BUF_FLAG_WHOLE;
	pipe->head = head + 1;

	अगर (!test_and_clear_bit(note, wqueue->notes_biपंचांगap)) अणु
		spin_unlock_irq(&pipe->rd_रुको.lock);
		BUG();
	पूर्ण
	wake_up_पूर्णांकerruptible_sync_poll_locked(&pipe->rd_रुको, EPOLLIN | EPOLLRDNORM);
	करोne = true;

out:
	spin_unlock_irq(&pipe->rd_रुको.lock);
	अगर (करोne)
		समाप्त_fasync(&pipe->fasync_पढ़ोers, SIGIO, POLL_IN);
	वापस करोne;

lost:
	buf = &pipe->bufs[(head - 1) & mask];
	buf->flags |= PIPE_BUF_FLAG_LOSS;
	जाओ out;
पूर्ण

/*
 * Apply filter rules to a notअगरication.
 */
अटल bool filter_watch_notअगरication(स्थिर काष्ठा watch_filter *wf,
				      स्थिर काष्ठा watch_notअगरication *n)
अणु
	स्थिर काष्ठा watch_type_filter *wt;
	अचिन्हित पूर्णांक st_bits = माप(wt->subtype_filter[0]) * 8;
	अचिन्हित पूर्णांक st_index = n->subtype / st_bits;
	अचिन्हित पूर्णांक st_bit = 1U << (n->subtype % st_bits);
	पूर्णांक i;

	अगर (!test_bit(n->type, wf->type_filter))
		वापस false;

	क्रम (i = 0; i < wf->nr_filters; i++) अणु
		wt = &wf->filters[i];
		अगर (n->type == wt->type &&
		    (wt->subtype_filter[st_index] & st_bit) &&
		    (n->info & wt->info_mask) == wt->info_filter)
			वापस true;
	पूर्ण

	वापस false; /* If there is a filter, the शेष is to reject. */
पूर्ण

/**
 * __post_watch_notअगरication - Post an event notअगरication
 * @wlist: The watch list to post the event to.
 * @n: The notअगरication record to post.
 * @cred: The creds of the process that triggered the notअगरication.
 * @id: The ID to match on the watch.
 *
 * Post a notअगरication of an event पूर्णांकo a set of watch queues and let the users
 * know.
 *
 * The size of the notअगरication should be set in n->info & WATCH_INFO_LENGTH and
 * should be in units of माप(*n).
 */
व्योम __post_watch_notअगरication(काष्ठा watch_list *wlist,
			       काष्ठा watch_notअगरication *n,
			       स्थिर काष्ठा cred *cred,
			       u64 id)
अणु
	स्थिर काष्ठा watch_filter *wf;
	काष्ठा watch_queue *wqueue;
	काष्ठा watch *watch;

	अगर (((n->info & WATCH_INFO_LENGTH) >> WATCH_INFO_LENGTH__SHIFT) == 0) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();

	hlist_क्रम_each_entry_rcu(watch, &wlist->watchers, list_node) अणु
		अगर (watch->id != id)
			जारी;
		n->info &= ~WATCH_INFO_ID;
		n->info |= watch->info_id;

		wqueue = rcu_dereference(watch->queue);
		wf = rcu_dereference(wqueue->filter);
		अगर (wf && !filter_watch_notअगरication(wf, n))
			जारी;

		अगर (security_post_notअगरication(watch->cred, cred, n) < 0)
			जारी;

		post_one_notअगरication(wqueue, n);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(__post_watch_notअगरication);

/*
 * Allocate sufficient pages to pपुनः_स्मृतिation क्रम the requested number of
 * notअगरications.
 */
दीर्घ watch_queue_set_size(काष्ठा pipe_inode_info *pipe, अचिन्हित पूर्णांक nr_notes)
अणु
	काष्ठा watch_queue *wqueue = pipe->watch_queue;
	काष्ठा page **pages;
	अचिन्हित दीर्घ *biपंचांगap;
	अचिन्हित दीर्घ user_bufs;
	अचिन्हित पूर्णांक bmsize;
	पूर्णांक ret, i, nr_pages;

	अगर (!wqueue)
		वापस -ENODEV;
	अगर (wqueue->notes)
		वापस -EBUSY;

	अगर (nr_notes < 1 ||
	    nr_notes > 512) /* TODO: choose a better hard limit */
		वापस -EINVAL;

	nr_pages = (nr_notes + WATCH_QUEUE_NOTES_PER_PAGE - 1);
	nr_pages /= WATCH_QUEUE_NOTES_PER_PAGE;
	user_bufs = account_pipe_buffers(pipe->user, pipe->nr_accounted, nr_pages);

	अगर (nr_pages > pipe->max_usage &&
	    (too_many_pipe_buffers_hard(user_bufs) ||
	     too_many_pipe_buffers_soft(user_bufs)) &&
	    pipe_is_unprivileged_user()) अणु
		ret = -EPERM;
		जाओ error;
	पूर्ण

	ret = pipe_resize_ring(pipe, nr_notes);
	अगर (ret < 0)
		जाओ error;

	pages = kसुस्मृति(माप(काष्ठा page *), nr_pages, GFP_KERNEL);
	अगर (!pages)
		जाओ error;

	क्रम (i = 0; i < nr_pages; i++) अणु
		pages[i] = alloc_page(GFP_KERNEL);
		अगर (!pages[i])
			जाओ error_p;
		pages[i]->index = i * WATCH_QUEUE_NOTES_PER_PAGE;
	पूर्ण

	bmsize = (nr_notes + BITS_PER_LONG - 1) / BITS_PER_LONG;
	bmsize *= माप(अचिन्हित दीर्घ);
	biपंचांगap = kदो_स्मृति(bmsize, GFP_KERNEL);
	अगर (!biपंचांगap)
		जाओ error_p;

	स_रखो(biपंचांगap, 0xff, bmsize);
	wqueue->notes = pages;
	wqueue->notes_biपंचांगap = biपंचांगap;
	wqueue->nr_pages = nr_pages;
	wqueue->nr_notes = nr_pages * WATCH_QUEUE_NOTES_PER_PAGE;
	वापस 0;

error_p:
	क्रम (i = 0; i < nr_pages; i++)
		__मुक्त_page(pages[i]);
	kमुक्त(pages);
error:
	(व्योम) account_pipe_buffers(pipe->user, nr_pages, pipe->nr_accounted);
	वापस ret;
पूर्ण

/*
 * Set the filter on a watch queue.
 */
दीर्घ watch_queue_set_filter(काष्ठा pipe_inode_info *pipe,
			    काष्ठा watch_notअगरication_filter __user *_filter)
अणु
	काष्ठा watch_notअगरication_type_filter *tf;
	काष्ठा watch_notअगरication_filter filter;
	काष्ठा watch_type_filter *q;
	काष्ठा watch_filter *wfilter;
	काष्ठा watch_queue *wqueue = pipe->watch_queue;
	पूर्णांक ret, nr_filter = 0, i;

	अगर (!wqueue)
		वापस -ENODEV;

	अगर (!_filter) अणु
		/* Remove the old filter */
		wfilter = शून्य;
		जाओ set;
	पूर्ण

	/* Grab the user's filter specअगरication */
	अगर (copy_from_user(&filter, _filter, माप(filter)) != 0)
		वापस -EFAULT;
	अगर (filter.nr_filters == 0 ||
	    filter.nr_filters > 16 ||
	    filter.__reserved != 0)
		वापस -EINVAL;

	tf = memdup_user(_filter->filters, filter.nr_filters * माप(*tf));
	अगर (IS_ERR(tf))
		वापस PTR_ERR(tf);

	ret = -EINVAL;
	क्रम (i = 0; i < filter.nr_filters; i++) अणु
		अगर ((tf[i].info_filter & ~tf[i].info_mask) ||
		    tf[i].info_mask & WATCH_INFO_LENGTH)
			जाओ err_filter;
		/* Ignore any unknown types */
		अगर (tf[i].type >= माप(wfilter->type_filter) * 8)
			जारी;
		nr_filter++;
	पूर्ण

	/* Now we need to build the पूर्णांकernal filter from only the relevant
	 * user-specअगरied filters.
	 */
	ret = -ENOMEM;
	wfilter = kzalloc(काष्ठा_size(wfilter, filters, nr_filter), GFP_KERNEL);
	अगर (!wfilter)
		जाओ err_filter;
	wfilter->nr_filters = nr_filter;

	q = wfilter->filters;
	क्रम (i = 0; i < filter.nr_filters; i++) अणु
		अगर (tf[i].type >= माप(wfilter->type_filter) * BITS_PER_LONG)
			जारी;

		q->type			= tf[i].type;
		q->info_filter		= tf[i].info_filter;
		q->info_mask		= tf[i].info_mask;
		q->subtype_filter[0]	= tf[i].subtype_filter[0];
		__set_bit(q->type, wfilter->type_filter);
		q++;
	पूर्ण

	kमुक्त(tf);
set:
	pipe_lock(pipe);
	wfilter = rcu_replace_poपूर्णांकer(wqueue->filter, wfilter,
				      lockdep_is_held(&pipe->mutex));
	pipe_unlock(pipe);
	अगर (wfilter)
		kमुक्त_rcu(wfilter, rcu);
	वापस 0;

err_filter:
	kमुक्त(tf);
	वापस ret;
पूर्ण

अटल व्योम __put_watch_queue(काष्ठा kref *kref)
अणु
	काष्ठा watch_queue *wqueue =
		container_of(kref, काष्ठा watch_queue, usage);
	काष्ठा watch_filter *wfilter;
	पूर्णांक i;

	क्रम (i = 0; i < wqueue->nr_pages; i++)
		__मुक्त_page(wqueue->notes[i]);

	wfilter = rcu_access_poपूर्णांकer(wqueue->filter);
	अगर (wfilter)
		kमुक्त_rcu(wfilter, rcu);
	kमुक्त_rcu(wqueue, rcu);
पूर्ण

/**
 * put_watch_queue - Dispose of a ref on a watchqueue.
 * @wqueue: The watch queue to unref.
 */
व्योम put_watch_queue(काष्ठा watch_queue *wqueue)
अणु
	kref_put(&wqueue->usage, __put_watch_queue);
पूर्ण
EXPORT_SYMBOL(put_watch_queue);

अटल व्योम मुक्त_watch(काष्ठा rcu_head *rcu)
अणु
	काष्ठा watch *watch = container_of(rcu, काष्ठा watch, rcu);

	put_watch_queue(rcu_access_poपूर्णांकer(watch->queue));
	atomic_dec(&watch->cred->user->nr_watches);
	put_cred(watch->cred);
पूर्ण

अटल व्योम __put_watch(काष्ठा kref *kref)
अणु
	काष्ठा watch *watch = container_of(kref, काष्ठा watch, usage);

	call_rcu(&watch->rcu, मुक्त_watch);
पूर्ण

/*
 * Discard a watch.
 */
अटल व्योम put_watch(काष्ठा watch *watch)
अणु
	kref_put(&watch->usage, __put_watch);
पूर्ण

/**
 * init_watch - Initialise a watch
 * @watch: The watch to initialise.
 * @wqueue: The queue to assign.
 *
 * Initialise a watch and set the watch queue.
 */
व्योम init_watch(काष्ठा watch *watch, काष्ठा watch_queue *wqueue)
अणु
	kref_init(&watch->usage);
	INIT_HLIST_NODE(&watch->list_node);
	INIT_HLIST_NODE(&watch->queue_node);
	rcu_assign_poपूर्णांकer(watch->queue, wqueue);
पूर्ण

/**
 * add_watch_to_object - Add a watch on an object to a watch list
 * @watch: The watch to add
 * @wlist: The watch list to add to
 *
 * @watch->queue must have been set to poपूर्णांक to the queue to post notअगरications
 * to and the watch list of the object to be watched.  @watch->cred must also
 * have been set to the appropriate credentials and a ref taken on them.
 *
 * The caller must pin the queue and the list both and must hold the list
 * locked against racing watch additions/removals.
 */
पूर्णांक add_watch_to_object(काष्ठा watch *watch, काष्ठा watch_list *wlist)
अणु
	काष्ठा watch_queue *wqueue = rcu_access_poपूर्णांकer(watch->queue);
	काष्ठा watch *w;

	hlist_क्रम_each_entry(w, &wlist->watchers, list_node) अणु
		काष्ठा watch_queue *wq = rcu_access_poपूर्णांकer(w->queue);
		अगर (wqueue == wq && watch->id == w->id)
			वापस -EBUSY;
	पूर्ण

	watch->cred = get_current_cred();
	rcu_assign_poपूर्णांकer(watch->watch_list, wlist);

	अगर (atomic_inc_वापस(&watch->cred->user->nr_watches) >
	    task_rlimit(current, RLIMIT_NOखाता)) अणु
		atomic_dec(&watch->cred->user->nr_watches);
		put_cred(watch->cred);
		वापस -EAGAIN;
	पूर्ण

	spin_lock_bh(&wqueue->lock);
	kref_get(&wqueue->usage);
	kref_get(&watch->usage);
	hlist_add_head(&watch->queue_node, &wqueue->watches);
	spin_unlock_bh(&wqueue->lock);

	hlist_add_head(&watch->list_node, &wlist->watchers);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(add_watch_to_object);

/**
 * हटाओ_watch_from_object - Remove a watch or all watches from an object.
 * @wlist: The watch list to हटाओ from
 * @wq: The watch queue of पूर्णांकerest (ignored अगर @all is true)
 * @id: The ID of the watch to हटाओ (ignored अगर @all is true)
 * @all: True to हटाओ all objects
 *
 * Remove a specअगरic watch or all watches from an object.  A notअगरication is
 * sent to the watcher to tell them that this happened.
 */
पूर्णांक हटाओ_watch_from_object(काष्ठा watch_list *wlist, काष्ठा watch_queue *wq,
			     u64 id, bool all)
अणु
	काष्ठा watch_notअगरication_removal n;
	काष्ठा watch_queue *wqueue;
	काष्ठा watch *watch;
	पूर्णांक ret = -EBADSLT;

	rcu_पढ़ो_lock();

again:
	spin_lock(&wlist->lock);
	hlist_क्रम_each_entry(watch, &wlist->watchers, list_node) अणु
		अगर (all ||
		    (watch->id == id && rcu_access_poपूर्णांकer(watch->queue) == wq))
			जाओ found;
	पूर्ण
	spin_unlock(&wlist->lock);
	जाओ out;

found:
	ret = 0;
	hlist_del_init_rcu(&watch->list_node);
	rcu_assign_poपूर्णांकer(watch->watch_list, शून्य);
	spin_unlock(&wlist->lock);

	/* We now own the reference on watch that used to beदीर्घ to wlist. */

	n.watch.type = WATCH_TYPE_META;
	n.watch.subtype = WATCH_META_REMOVAL_NOTIFICATION;
	n.watch.info = watch->info_id | watch_माप(n.watch);
	n.id = id;
	अगर (id != 0)
		n.watch.info = watch->info_id | watch_माप(n);

	wqueue = rcu_dereference(watch->queue);

	/* We करोn't need the watch list lock क्रम the next bit as RCU is
	 * protecting *wqueue from deallocation.
	 */
	अगर (wqueue) अणु
		post_one_notअगरication(wqueue, &n.watch);

		spin_lock_bh(&wqueue->lock);

		अगर (!hlist_unhashed(&watch->queue_node)) अणु
			hlist_del_init_rcu(&watch->queue_node);
			put_watch(watch);
		पूर्ण

		spin_unlock_bh(&wqueue->lock);
	पूर्ण

	अगर (wlist->release_watch) अणु
		व्योम (*release_watch)(काष्ठा watch *);

		release_watch = wlist->release_watch;
		rcu_पढ़ो_unlock();
		(*release_watch)(watch);
		rcu_पढ़ो_lock();
	पूर्ण
	put_watch(watch);

	अगर (all && !hlist_empty(&wlist->watchers))
		जाओ again;
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(हटाओ_watch_from_object);

/*
 * Remove all the watches that are contributory to a queue.  This has the
 * potential to race with removal of the watches by the deकाष्ठाion of the
 * objects being watched or with the distribution of notअगरications.
 */
व्योम watch_queue_clear(काष्ठा watch_queue *wqueue)
अणु
	काष्ठा watch_list *wlist;
	काष्ठा watch *watch;
	bool release;

	rcu_पढ़ो_lock();
	spin_lock_bh(&wqueue->lock);

	/* Prevent new additions and prevent notअगरications from happening */
	wqueue->defunct = true;

	जबतक (!hlist_empty(&wqueue->watches)) अणु
		watch = hlist_entry(wqueue->watches.first, काष्ठा watch, queue_node);
		hlist_del_init_rcu(&watch->queue_node);
		/* We now own a ref on the watch. */
		spin_unlock_bh(&wqueue->lock);

		/* We can't करो the next bit under the queue lock as we need to
		 * get the list lock - which would cause a deadlock अगर someone
		 * was removing from the opposite direction at the same समय or
		 * posting a notअगरication.
		 */
		wlist = rcu_dereference(watch->watch_list);
		अगर (wlist) अणु
			व्योम (*release_watch)(काष्ठा watch *);

			spin_lock(&wlist->lock);

			release = !hlist_unhashed(&watch->list_node);
			अगर (release) अणु
				hlist_del_init_rcu(&watch->list_node);
				rcu_assign_poपूर्णांकer(watch->watch_list, शून्य);

				/* We now own a second ref on the watch. */
			पूर्ण

			release_watch = wlist->release_watch;
			spin_unlock(&wlist->lock);

			अगर (release) अणु
				अगर (release_watch) अणु
					rcu_पढ़ो_unlock();
					/* This might need to call dput(), so
					 * we have to drop all the locks.
					 */
					(*release_watch)(watch);
					rcu_पढ़ो_lock();
				पूर्ण
				put_watch(watch);
			पूर्ण
		पूर्ण

		put_watch(watch);
		spin_lock_bh(&wqueue->lock);
	पूर्ण

	spin_unlock_bh(&wqueue->lock);
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * get_watch_queue - Get a watch queue from its file descriptor.
 * @fd: The fd to query.
 */
काष्ठा watch_queue *get_watch_queue(पूर्णांक fd)
अणु
	काष्ठा pipe_inode_info *pipe;
	काष्ठा watch_queue *wqueue = ERR_PTR(-EINVAL);
	काष्ठा fd f;

	f = fdget(fd);
	अगर (f.file) अणु
		pipe = get_pipe_info(f.file, false);
		अगर (pipe && pipe->watch_queue) अणु
			wqueue = pipe->watch_queue;
			kref_get(&wqueue->usage);
		पूर्ण
		fdput(f);
	पूर्ण

	वापस wqueue;
पूर्ण
EXPORT_SYMBOL(get_watch_queue);

/*
 * Initialise a watch queue
 */
पूर्णांक watch_queue_init(काष्ठा pipe_inode_info *pipe)
अणु
	काष्ठा watch_queue *wqueue;

	wqueue = kzalloc(माप(*wqueue), GFP_KERNEL);
	अगर (!wqueue)
		वापस -ENOMEM;

	wqueue->pipe = pipe;
	kref_init(&wqueue->usage);
	spin_lock_init(&wqueue->lock);
	INIT_HLIST_HEAD(&wqueue->watches);

	pipe->watch_queue = wqueue;
	वापस 0;
पूर्ण
