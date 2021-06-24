<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   drbd_receiver.c

   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2001-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 1999-2008, Philipp Reisner <philipp.reisner@linbit.com>.
   Copyright (C) 2002-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.

 */


#समावेश <linux/module.h>

#समावेश <linux/uaccess.h>
#समावेश <net/sock.h>

#समावेश <linux/drbd.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/in.h>
#समावेश <linux/mm.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/slab.h>
#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/pkt_sched.h>
#घोषणा __KERNEL_SYSCALLS__
#समावेश <linux/unistd.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/माला.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/part_स्थिति.स>
#समावेश "drbd_int.h"
#समावेश "drbd_protocol.h"
#समावेश "drbd_req.h"
#समावेश "drbd_vli.h"

#घोषणा PRO_FEATURES (DRBD_FF_TRIM|DRBD_FF_THIN_RESYNC|DRBD_FF_WSAME|DRBD_FF_WZEROES)

काष्ठा packet_info अणु
	क्रमागत drbd_packet cmd;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक vnr;
	व्योम *data;
पूर्ण;

क्रमागत finish_epoch अणु
	FE_STILL_LIVE,
	FE_DESTROYED,
	FE_RECYCLED,
पूर्ण;

अटल पूर्णांक drbd_करो_features(काष्ठा drbd_connection *connection);
अटल पूर्णांक drbd_करो_auth(काष्ठा drbd_connection *connection);
अटल पूर्णांक drbd_disconnected(काष्ठा drbd_peer_device *);
अटल व्योम conn_रुको_active_ee_empty(काष्ठा drbd_connection *connection);
अटल क्रमागत finish_epoch drbd_may_finish_epoch(काष्ठा drbd_connection *, काष्ठा drbd_epoch *, क्रमागत epoch_event);
अटल पूर्णांक e_end_block(काष्ठा drbd_work *, पूर्णांक);


#घोषणा GFP_TRY	(__GFP_HIGHMEM | __GFP_NOWARN)

/*
 * some helper functions to deal with single linked page lists,
 * page->निजी being our "next" poपूर्णांकer.
 */

/* If at least n pages are linked at head, get n pages off.
 * Otherwise, करोn't modअगरy head, and वापस शून्य.
 * Locking is the responsibility of the caller.
 */
अटल काष्ठा page *page_chain_del(काष्ठा page **head, पूर्णांक n)
अणु
	काष्ठा page *page;
	काष्ठा page *पंचांगp;

	BUG_ON(!n);
	BUG_ON(!head);

	page = *head;

	अगर (!page)
		वापस शून्य;

	जबतक (page) अणु
		पंचांगp = page_chain_next(page);
		अगर (--n == 0)
			अवरोध; /* found sufficient pages */
		अगर (पंचांगp == शून्य)
			/* insufficient pages, करोn't use any of them. */
			वापस शून्य;
		page = पंचांगp;
	पूर्ण

	/* add end of list marker क्रम the वापसed list */
	set_page_निजी(page, 0);
	/* actual वापस value, and adjusपंचांगent of head */
	page = *head;
	*head = पंचांगp;
	वापस page;
पूर्ण

/* may be used outside of locks to find the tail of a (usually लघु)
 * "private" page chain, beक्रमe adding it back to a global chain head
 * with page_chain_add() under a spinlock. */
अटल काष्ठा page *page_chain_tail(काष्ठा page *page, पूर्णांक *len)
अणु
	काष्ठा page *पंचांगp;
	पूर्णांक i = 1;
	जबतक ((पंचांगp = page_chain_next(page))) अणु
		++i;
		page = पंचांगp;
	पूर्ण
	अगर (len)
		*len = i;
	वापस page;
पूर्ण

अटल पूर्णांक page_chain_मुक्त(काष्ठा page *page)
अणु
	काष्ठा page *पंचांगp;
	पूर्णांक i = 0;
	page_chain_क्रम_each_safe(page, पंचांगp) अणु
		put_page(page);
		++i;
	पूर्ण
	वापस i;
पूर्ण

अटल व्योम page_chain_add(काष्ठा page **head,
		काष्ठा page *chain_first, काष्ठा page *chain_last)
अणु
#अगर 1
	काष्ठा page *पंचांगp;
	पंचांगp = page_chain_tail(chain_first, शून्य);
	BUG_ON(पंचांगp != chain_last);
#पूर्ण_अगर

	/* add chain to head */
	set_page_निजी(chain_last, (अचिन्हित दीर्घ)*head);
	*head = chain_first;
पूर्ण

अटल काष्ठा page *__drbd_alloc_pages(काष्ठा drbd_device *device,
				       अचिन्हित पूर्णांक number)
अणु
	काष्ठा page *page = शून्य;
	काष्ठा page *पंचांगp = शून्य;
	अचिन्हित पूर्णांक i = 0;

	/* Yes, testing drbd_pp_vacant outside the lock is racy.
	 * So what. It saves a spin_lock. */
	अगर (drbd_pp_vacant >= number) अणु
		spin_lock(&drbd_pp_lock);
		page = page_chain_del(&drbd_pp_pool, number);
		अगर (page)
			drbd_pp_vacant -= number;
		spin_unlock(&drbd_pp_lock);
		अगर (page)
			वापस page;
	पूर्ण

	/* GFP_TRY, because we must not cause arbitrary ग_लिखो-out: in a DRBD
	 * "criss-cross" setup, that might cause ग_लिखो-out on some other DRBD,
	 * which in turn might block on the other node at this very place.  */
	क्रम (i = 0; i < number; i++) अणु
		पंचांगp = alloc_page(GFP_TRY);
		अगर (!पंचांगp)
			अवरोध;
		set_page_निजी(पंचांगp, (अचिन्हित दीर्घ)page);
		page = पंचांगp;
	पूर्ण

	अगर (i == number)
		वापस page;

	/* Not enough pages immediately available this समय.
	 * No need to jump around here, drbd_alloc_pages will retry this
	 * function "soon". */
	अगर (page) अणु
		पंचांगp = page_chain_tail(page, शून्य);
		spin_lock(&drbd_pp_lock);
		page_chain_add(&drbd_pp_pool, page, पंचांगp);
		drbd_pp_vacant += i;
		spin_unlock(&drbd_pp_lock);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम reclaim_finished_net_peer_reqs(काष्ठा drbd_device *device,
					   काष्ठा list_head *to_be_मुक्तd)
अणु
	काष्ठा drbd_peer_request *peer_req, *पंचांगp;

	/* The EEs are always appended to the end of the list. Since
	   they are sent in order over the wire, they have to finish
	   in order. As soon as we see the first not finished we can
	   stop to examine the list... */

	list_क्रम_each_entry_safe(peer_req, पंचांगp, &device->net_ee, w.list) अणु
		अगर (drbd_peer_req_has_active_page(peer_req))
			अवरोध;
		list_move(&peer_req->w.list, to_be_मुक्तd);
	पूर्ण
पूर्ण

अटल व्योम drbd_reclaim_net_peer_reqs(काष्ठा drbd_device *device)
अणु
	LIST_HEAD(reclaimed);
	काष्ठा drbd_peer_request *peer_req, *t;

	spin_lock_irq(&device->resource->req_lock);
	reclaim_finished_net_peer_reqs(device, &reclaimed);
	spin_unlock_irq(&device->resource->req_lock);
	list_क्रम_each_entry_safe(peer_req, t, &reclaimed, w.list)
		drbd_मुक्त_net_peer_req(device, peer_req);
पूर्ण

अटल व्योम conn_reclaim_net_peer_reqs(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		अगर (!atomic_पढ़ो(&device->pp_in_use_by_net))
			जारी;

		kref_get(&device->kref);
		rcu_पढ़ो_unlock();
		drbd_reclaim_net_peer_reqs(device);
		kref_put(&device->kref, drbd_destroy_device);
		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * drbd_alloc_pages() - Returns @number pages, retries क्रमever (or until संकेतled)
 * @peer_device:	DRBD device.
 * @number:		number of pages requested
 * @retry:		whether to retry, अगर not enough pages are available right now
 *
 * Tries to allocate number pages, first from our own page pool, then from
 * the kernel.
 * Possibly retry until DRBD मुक्तs sufficient pages somewhere अन्यथा.
 *
 * If this allocation would exceed the max_buffers setting, we throttle
 * allocation (schedule_समयout) to give the प्रणाली some room to breathe.
 *
 * We करो not use max-buffers as hard limit, because it could lead to
 * congestion and further to a distributed deadlock during online-verअगरy or
 * (checksum based) resync, अगर the max-buffers, socket buffer sizes and
 * resync-rate settings are mis-configured.
 *
 * Returns a page chain linked via page->निजी.
 */
काष्ठा page *drbd_alloc_pages(काष्ठा drbd_peer_device *peer_device, अचिन्हित पूर्णांक number,
			      bool retry)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा page *page = शून्य;
	काष्ठा net_conf *nc;
	DEFINE_WAIT(रुको);
	अचिन्हित पूर्णांक mxb;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(peer_device->connection->net_conf);
	mxb = nc ? nc->max_buffers : 1000000;
	rcu_पढ़ो_unlock();

	अगर (atomic_पढ़ो(&device->pp_in_use) < mxb)
		page = __drbd_alloc_pages(device, number);

	/* Try to keep the fast path fast, but occasionally we need
	 * to reclaim the pages we lended to the network stack. */
	अगर (page && atomic_पढ़ो(&device->pp_in_use_by_net) > 512)
		drbd_reclaim_net_peer_reqs(device);

	जबतक (page == शून्य) अणु
		prepare_to_रुको(&drbd_pp_रुको, &रुको, TASK_INTERRUPTIBLE);

		drbd_reclaim_net_peer_reqs(device);

		अगर (atomic_पढ़ो(&device->pp_in_use) < mxb) अणु
			page = __drbd_alloc_pages(device, number);
			अगर (page)
				अवरोध;
		पूर्ण

		अगर (!retry)
			अवरोध;

		अगर (संकेत_pending(current)) अणु
			drbd_warn(device, "drbd_alloc_pages interrupted!\n");
			अवरोध;
		पूर्ण

		अगर (schedule_समयout(HZ/10) == 0)
			mxb = अच_पूर्णांक_उच्च;
	पूर्ण
	finish_रुको(&drbd_pp_रुको, &रुको);

	अगर (page)
		atomic_add(number, &device->pp_in_use);
	वापस page;
पूर्ण

/* Must not be used from irq, as that may deadlock: see drbd_alloc_pages.
 * Is also used from inside an other spin_lock_irq(&resource->req_lock);
 * Either links the page chain back to the global pool,
 * or वापसs all pages to the प्रणाली. */
अटल व्योम drbd_मुक्त_pages(काष्ठा drbd_device *device, काष्ठा page *page, पूर्णांक is_net)
अणु
	atomic_t *a = is_net ? &device->pp_in_use_by_net : &device->pp_in_use;
	पूर्णांक i;

	अगर (page == शून्य)
		वापस;

	अगर (drbd_pp_vacant > (DRBD_MAX_BIO_SIZE/PAGE_SIZE) * drbd_minor_count)
		i = page_chain_मुक्त(page);
	अन्यथा अणु
		काष्ठा page *पंचांगp;
		पंचांगp = page_chain_tail(page, &i);
		spin_lock(&drbd_pp_lock);
		page_chain_add(&drbd_pp_pool, page, पंचांगp);
		drbd_pp_vacant += i;
		spin_unlock(&drbd_pp_lock);
	पूर्ण
	i = atomic_sub_वापस(i, a);
	अगर (i < 0)
		drbd_warn(device, "ASSERTION FAILED: %s: %d < 0\n",
			is_net ? "pp_in_use_by_net" : "pp_in_use", i);
	wake_up(&drbd_pp_रुको);
पूर्ण

/*
You need to hold the req_lock:
 _drbd_रुको_ee_list_empty()

You must not have the req_lock:
 drbd_मुक्त_peer_req()
 drbd_alloc_peer_req()
 drbd_मुक्त_peer_reqs()
 drbd_ee_fix_bhs()
 drbd_finish_peer_reqs()
 drbd_clear_करोne_ee()
 drbd_रुको_ee_list_empty()
*/

/* normal: payload_size == request size (bi_size)
 * w_same: payload_size == logical_block_size
 * trim: payload_size == 0 */
काष्ठा drbd_peer_request *
drbd_alloc_peer_req(काष्ठा drbd_peer_device *peer_device, u64 id, sector_t sector,
		    अचिन्हित पूर्णांक request_size, अचिन्हित पूर्णांक payload_size, gfp_t gfp_mask) __must_hold(local)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा drbd_peer_request *peer_req;
	काष्ठा page *page = शून्य;
	अचिन्हित nr_pages = (payload_size + PAGE_SIZE -1) >> PAGE_SHIFT;

	अगर (drbd_insert_fault(device, DRBD_FAULT_AL_EE))
		वापस शून्य;

	peer_req = mempool_alloc(&drbd_ee_mempool, gfp_mask & ~__GFP_HIGHMEM);
	अगर (!peer_req) अणु
		अगर (!(gfp_mask & __GFP_NOWARN))
			drbd_err(device, "%s: allocation failed\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर (nr_pages) अणु
		page = drbd_alloc_pages(peer_device, nr_pages,
					gfpflags_allow_blocking(gfp_mask));
		अगर (!page)
			जाओ fail;
	पूर्ण

	स_रखो(peer_req, 0, माप(*peer_req));
	INIT_LIST_HEAD(&peer_req->w.list);
	drbd_clear_पूर्णांकerval(&peer_req->i);
	peer_req->i.size = request_size;
	peer_req->i.sector = sector;
	peer_req->submit_jअगर = jअगरfies;
	peer_req->peer_device = peer_device;
	peer_req->pages = page;
	/*
	 * The block_id is opaque to the receiver.  It is not endianness
	 * converted, and sent back to the sender unchanged.
	 */
	peer_req->block_id = id;

	वापस peer_req;

 fail:
	mempool_मुक्त(peer_req, &drbd_ee_mempool);
	वापस शून्य;
पूर्ण

व्योम __drbd_मुक्त_peer_req(काष्ठा drbd_device *device, काष्ठा drbd_peer_request *peer_req,
		       पूर्णांक is_net)
अणु
	might_sleep();
	अगर (peer_req->flags & EE_HAS_DIGEST)
		kमुक्त(peer_req->digest);
	drbd_मुक्त_pages(device, peer_req->pages, is_net);
	D_ASSERT(device, atomic_पढ़ो(&peer_req->pending_bios) == 0);
	D_ASSERT(device, drbd_पूर्णांकerval_empty(&peer_req->i));
	अगर (!expect(!(peer_req->flags & EE_CALL_AL_COMPLETE_IO))) अणु
		peer_req->flags &= ~EE_CALL_AL_COMPLETE_IO;
		drbd_al_complete_io(device, &peer_req->i);
	पूर्ण
	mempool_मुक्त(peer_req, &drbd_ee_mempool);
पूर्ण

पूर्णांक drbd_मुक्त_peer_reqs(काष्ठा drbd_device *device, काष्ठा list_head *list)
अणु
	LIST_HEAD(work_list);
	काष्ठा drbd_peer_request *peer_req, *t;
	पूर्णांक count = 0;
	पूर्णांक is_net = list == &device->net_ee;

	spin_lock_irq(&device->resource->req_lock);
	list_splice_init(list, &work_list);
	spin_unlock_irq(&device->resource->req_lock);

	list_क्रम_each_entry_safe(peer_req, t, &work_list, w.list) अणु
		__drbd_मुक्त_peer_req(device, peer_req, is_net);
		count++;
	पूर्ण
	वापस count;
पूर्ण

/*
 * See also comments in _req_mod(,BARRIER_ACKED) and receive_Barrier.
 */
अटल पूर्णांक drbd_finish_peer_reqs(काष्ठा drbd_device *device)
अणु
	LIST_HEAD(work_list);
	LIST_HEAD(reclaimed);
	काष्ठा drbd_peer_request *peer_req, *t;
	पूर्णांक err = 0;

	spin_lock_irq(&device->resource->req_lock);
	reclaim_finished_net_peer_reqs(device, &reclaimed);
	list_splice_init(&device->करोne_ee, &work_list);
	spin_unlock_irq(&device->resource->req_lock);

	list_क्रम_each_entry_safe(peer_req, t, &reclaimed, w.list)
		drbd_मुक्त_net_peer_req(device, peer_req);

	/* possible callbacks here:
	 * e_end_block, and e_end_resync_block, e_send_superseded.
	 * all ignore the last argument.
	 */
	list_क्रम_each_entry_safe(peer_req, t, &work_list, w.list) अणु
		पूर्णांक err2;

		/* list_del not necessary, next/prev members not touched */
		err2 = peer_req->w.cb(&peer_req->w, !!err);
		अगर (!err)
			err = err2;
		drbd_मुक्त_peer_req(device, peer_req);
	पूर्ण
	wake_up(&device->ee_रुको);

	वापस err;
पूर्ण

अटल व्योम _drbd_रुको_ee_list_empty(काष्ठा drbd_device *device,
				     काष्ठा list_head *head)
अणु
	DEFINE_WAIT(रुको);

	/* aव्योमs spin_lock/unlock
	 * and calling prepare_to_रुको in the fast path */
	जबतक (!list_empty(head)) अणु
		prepare_to_रुको(&device->ee_रुको, &रुको, TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(&device->resource->req_lock);
		io_schedule();
		finish_रुको(&device->ee_रुको, &रुको);
		spin_lock_irq(&device->resource->req_lock);
	पूर्ण
पूर्ण

अटल व्योम drbd_रुको_ee_list_empty(काष्ठा drbd_device *device,
				    काष्ठा list_head *head)
अणु
	spin_lock_irq(&device->resource->req_lock);
	_drbd_रुको_ee_list_empty(device, head);
	spin_unlock_irq(&device->resource->req_lock);
पूर्ण

अटल पूर्णांक drbd_recv_लघु(काष्ठा socket *sock, व्योम *buf, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा kvec iov = अणु
		.iov_base = buf,
		.iov_len = size,
	पूर्ण;
	काष्ठा msghdr msg = अणु
		.msg_flags = (flags ? flags : MSG_WAITALL | MSG_NOSIGNAL)
	पूर्ण;
	iov_iter_kvec(&msg.msg_iter, READ, &iov, 1, size);
	वापस sock_recvmsg(sock, &msg, msg.msg_flags);
पूर्ण

अटल पूर्णांक drbd_recv(काष्ठा drbd_connection *connection, व्योम *buf, माप_प्रकार size)
अणु
	पूर्णांक rv;

	rv = drbd_recv_लघु(connection->data.socket, buf, size, 0);

	अगर (rv < 0) अणु
		अगर (rv == -ECONNRESET)
			drbd_info(connection, "sock was reset by peer\n");
		अन्यथा अगर (rv != -ERESTARTSYS)
			drbd_err(connection, "sock_recvmsg returned %d\n", rv);
	पूर्ण अन्यथा अगर (rv == 0) अणु
		अगर (test_bit(DISCONNECT_SENT, &connection->flags)) अणु
			दीर्घ t;
			rcu_पढ़ो_lock();
			t = rcu_dereference(connection->net_conf)->ping_समयo * HZ/10;
			rcu_पढ़ो_unlock();

			t = रुको_event_समयout(connection->ping_रुको, connection->cstate < C_WF_REPORT_PARAMS, t);

			अगर (t)
				जाओ out;
		पूर्ण
		drbd_info(connection, "sock was shut down by peer\n");
	पूर्ण

	अगर (rv != size)
		conn_request_state(connection, NS(conn, C_BROKEN_PIPE), CS_HARD);

out:
	वापस rv;
पूर्ण

अटल पूर्णांक drbd_recv_all(काष्ठा drbd_connection *connection, व्योम *buf, माप_प्रकार size)
अणु
	पूर्णांक err;

	err = drbd_recv(connection, buf, size);
	अगर (err != size) अणु
		अगर (err >= 0)
			err = -EIO;
	पूर्ण अन्यथा
		err = 0;
	वापस err;
पूर्ण

अटल पूर्णांक drbd_recv_all_warn(काष्ठा drbd_connection *connection, व्योम *buf, माप_प्रकार size)
अणु
	पूर्णांक err;

	err = drbd_recv_all(connection, buf, size);
	अगर (err && !संकेत_pending(current))
		drbd_warn(connection, "short read (expected size %d)\n", (पूर्णांक)size);
	वापस err;
पूर्ण

/* quoting tcp(7):
 *   On inभागidual connections, the socket buffer size must be set prior to the
 *   listen(2) or connect(2) calls in order to have it take effect.
 * This is our wrapper to करो so.
 */
अटल व्योम drbd_रखो_बफsize(काष्ठा socket *sock, अचिन्हित पूर्णांक snd,
		अचिन्हित पूर्णांक rcv)
अणु
	/* खोलो coded SO_SNDBUF, SO_RCVBUF */
	अगर (snd) अणु
		sock->sk->sk_sndbuf = snd;
		sock->sk->sk_userlocks |= SOCK_SNDBUF_LOCK;
	पूर्ण
	अगर (rcv) अणु
		sock->sk->sk_rcvbuf = rcv;
		sock->sk->sk_userlocks |= SOCK_RCVBUF_LOCK;
	पूर्ण
पूर्ण

अटल काष्ठा socket *drbd_try_connect(काष्ठा drbd_connection *connection)
अणु
	स्थिर अक्षर *what;
	काष्ठा socket *sock;
	काष्ठा sockaddr_in6 src_in6;
	काष्ठा sockaddr_in6 peer_in6;
	काष्ठा net_conf *nc;
	पूर्णांक err, peer_addr_len, my_addr_len;
	पूर्णांक sndbuf_size, rcvbuf_size, connect_पूर्णांक;
	पूर्णांक disconnect_on_error = 1;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	अगर (!nc) अणु
		rcu_पढ़ो_unlock();
		वापस शून्य;
	पूर्ण
	sndbuf_size = nc->sndbuf_size;
	rcvbuf_size = nc->rcvbuf_size;
	connect_पूर्णांक = nc->connect_पूर्णांक;
	rcu_पढ़ो_unlock();

	my_addr_len = min_t(पूर्णांक, connection->my_addr_len, माप(src_in6));
	स_नकल(&src_in6, &connection->my_addr, my_addr_len);

	अगर (((काष्ठा sockaddr *)&connection->my_addr)->sa_family == AF_INET6)
		src_in6.sin6_port = 0;
	अन्यथा
		((काष्ठा sockaddr_in *)&src_in6)->sin_port = 0; /* AF_INET & AF_SCI */

	peer_addr_len = min_t(पूर्णांक, connection->peer_addr_len, माप(src_in6));
	स_नकल(&peer_in6, &connection->peer_addr, peer_addr_len);

	what = "sock_create_kern";
	err = sock_create_kern(&init_net, ((काष्ठा sockaddr *)&src_in6)->sa_family,
			       SOCK_STREAM, IPPROTO_TCP, &sock);
	अगर (err < 0) अणु
		sock = शून्य;
		जाओ out;
	पूर्ण

	sock->sk->sk_rcvसमयo =
	sock->sk->sk_sndसमयo = connect_पूर्णांक * HZ;
	drbd_रखो_बफsize(sock, sndbuf_size, rcvbuf_size);

       /* explicitly bind to the configured IP as source IP
	*  क्रम the outgoing connections.
	*  This is needed क्रम multihomed hosts and to be
	*  able to use lo: पूर्णांकerfaces क्रम drbd.
	* Make sure to use 0 as port number, so linux selects
	*  a मुक्त one dynamically.
	*/
	what = "bind before connect";
	err = sock->ops->bind(sock, (काष्ठा sockaddr *) &src_in6, my_addr_len);
	अगर (err < 0)
		जाओ out;

	/* connect may fail, peer not yet available.
	 * stay C_WF_CONNECTION, करोn't go Disconnecting! */
	disconnect_on_error = 0;
	what = "connect";
	err = sock->ops->connect(sock, (काष्ठा sockaddr *) &peer_in6, peer_addr_len, 0);

out:
	अगर (err < 0) अणु
		अगर (sock) अणु
			sock_release(sock);
			sock = शून्य;
		पूर्ण
		चयन (-err) अणु
			/* समयout, busy, संकेत pending */
		हाल ETIMEDOUT: हाल EAGAIN: हाल EINPROGRESS:
		हाल EINTR: हाल ERESTARTSYS:
			/* peer not (yet) available, network problem */
		हाल ECONNREFUSED: हाल ENETUNREACH:
		हाल EHOSTDOWN:    हाल EHOSTUNREACH:
			disconnect_on_error = 0;
			अवरोध;
		शेष:
			drbd_err(connection, "%s failed, err = %d\n", what, err);
		पूर्ण
		अगर (disconnect_on_error)
			conn_request_state(connection, NS(conn, C_DISCONNECTING), CS_HARD);
	पूर्ण

	वापस sock;
पूर्ण

काष्ठा accept_रुको_data अणु
	काष्ठा drbd_connection *connection;
	काष्ठा socket *s_listen;
	काष्ठा completion करोor_bell;
	व्योम (*original_sk_state_change)(काष्ठा sock *sk);

पूर्ण;

अटल व्योम drbd_incoming_connection(काष्ठा sock *sk)
अणु
	काष्ठा accept_रुको_data *ad = sk->sk_user_data;
	व्योम (*state_change)(काष्ठा sock *sk);

	state_change = ad->original_sk_state_change;
	अगर (sk->sk_state == TCP_ESTABLISHED)
		complete(&ad->करोor_bell);
	state_change(sk);
पूर्ण

अटल पूर्णांक prepare_listen_socket(काष्ठा drbd_connection *connection, काष्ठा accept_रुको_data *ad)
अणु
	पूर्णांक err, sndbuf_size, rcvbuf_size, my_addr_len;
	काष्ठा sockaddr_in6 my_addr;
	काष्ठा socket *s_listen;
	काष्ठा net_conf *nc;
	स्थिर अक्षर *what;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	अगर (!nc) अणु
		rcu_पढ़ो_unlock();
		वापस -EIO;
	पूर्ण
	sndbuf_size = nc->sndbuf_size;
	rcvbuf_size = nc->rcvbuf_size;
	rcu_पढ़ो_unlock();

	my_addr_len = min_t(पूर्णांक, connection->my_addr_len, माप(काष्ठा sockaddr_in6));
	स_नकल(&my_addr, &connection->my_addr, my_addr_len);

	what = "sock_create_kern";
	err = sock_create_kern(&init_net, ((काष्ठा sockaddr *)&my_addr)->sa_family,
			       SOCK_STREAM, IPPROTO_TCP, &s_listen);
	अगर (err) अणु
		s_listen = शून्य;
		जाओ out;
	पूर्ण

	s_listen->sk->sk_reuse = SK_CAN_REUSE; /* SO_REUSEADDR */
	drbd_रखो_बफsize(s_listen, sndbuf_size, rcvbuf_size);

	what = "bind before listen";
	err = s_listen->ops->bind(s_listen, (काष्ठा sockaddr *)&my_addr, my_addr_len);
	अगर (err < 0)
		जाओ out;

	ad->s_listen = s_listen;
	ग_लिखो_lock_bh(&s_listen->sk->sk_callback_lock);
	ad->original_sk_state_change = s_listen->sk->sk_state_change;
	s_listen->sk->sk_state_change = drbd_incoming_connection;
	s_listen->sk->sk_user_data = ad;
	ग_लिखो_unlock_bh(&s_listen->sk->sk_callback_lock);

	what = "listen";
	err = s_listen->ops->listen(s_listen, 5);
	अगर (err < 0)
		जाओ out;

	वापस 0;
out:
	अगर (s_listen)
		sock_release(s_listen);
	अगर (err < 0) अणु
		अगर (err != -EAGAIN && err != -EINTR && err != -ERESTARTSYS) अणु
			drbd_err(connection, "%s failed, err = %d\n", what, err);
			conn_request_state(connection, NS(conn, C_DISCONNECTING), CS_HARD);
		पूर्ण
	पूर्ण

	वापस -EIO;
पूर्ण

अटल व्योम unरेजिस्टर_state_change(काष्ठा sock *sk, काष्ठा accept_रुको_data *ad)
अणु
	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	sk->sk_state_change = ad->original_sk_state_change;
	sk->sk_user_data = शून्य;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल काष्ठा socket *drbd_रुको_क्रम_connect(काष्ठा drbd_connection *connection, काष्ठा accept_रुको_data *ad)
अणु
	पूर्णांक समयo, connect_पूर्णांक, err = 0;
	काष्ठा socket *s_estab = शून्य;
	काष्ठा net_conf *nc;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	अगर (!nc) अणु
		rcu_पढ़ो_unlock();
		वापस शून्य;
	पूर्ण
	connect_पूर्णांक = nc->connect_पूर्णांक;
	rcu_पढ़ो_unlock();

	समयo = connect_पूर्णांक * HZ;
	/* 28.5% अक्रमom jitter */
	समयo += (pअक्रमom_u32() & 1) ? समयo / 7 : -समयo / 7;

	err = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ad->करोor_bell, समयo);
	अगर (err <= 0)
		वापस शून्य;

	err = kernel_accept(ad->s_listen, &s_estab, 0);
	अगर (err < 0) अणु
		अगर (err != -EAGAIN && err != -EINTR && err != -ERESTARTSYS) अणु
			drbd_err(connection, "accept failed, err = %d\n", err);
			conn_request_state(connection, NS(conn, C_DISCONNECTING), CS_HARD);
		पूर्ण
	पूर्ण

	अगर (s_estab)
		unरेजिस्टर_state_change(s_estab->sk, ad);

	वापस s_estab;
पूर्ण

अटल पूर्णांक decode_header(काष्ठा drbd_connection *, व्योम *, काष्ठा packet_info *);

अटल पूर्णांक send_first_packet(काष्ठा drbd_connection *connection, काष्ठा drbd_socket *sock,
			     क्रमागत drbd_packet cmd)
अणु
	अगर (!conn_prepare_command(connection, sock))
		वापस -EIO;
	वापस conn_send_command(connection, sock, cmd, 0, शून्य, 0);
पूर्ण

अटल पूर्णांक receive_first_packet(काष्ठा drbd_connection *connection, काष्ठा socket *sock)
अणु
	अचिन्हित पूर्णांक header_size = drbd_header_size(connection);
	काष्ठा packet_info pi;
	काष्ठा net_conf *nc;
	पूर्णांक err;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	अगर (!nc) अणु
		rcu_पढ़ो_unlock();
		वापस -EIO;
	पूर्ण
	sock->sk->sk_rcvसमयo = nc->ping_समयo * 4 * HZ / 10;
	rcu_पढ़ो_unlock();

	err = drbd_recv_लघु(sock, connection->data.rbuf, header_size, 0);
	अगर (err != header_size) अणु
		अगर (err >= 0)
			err = -EIO;
		वापस err;
	पूर्ण
	err = decode_header(connection, connection->data.rbuf, &pi);
	अगर (err)
		वापस err;
	वापस pi.cmd;
पूर्ण

/**
 * drbd_socket_okay() - Free the socket अगर its connection is not okay
 * @sock:	poपूर्णांकer to the poपूर्णांकer to the socket.
 */
अटल bool drbd_socket_okay(काष्ठा socket **sock)
अणु
	पूर्णांक rr;
	अक्षर tb[4];

	अगर (!*sock)
		वापस false;

	rr = drbd_recv_लघु(*sock, tb, 4, MSG_DONTWAIT | MSG_PEEK);

	अगर (rr > 0 || rr == -EAGAIN) अणु
		वापस true;
	पूर्ण अन्यथा अणु
		sock_release(*sock);
		*sock = शून्य;
		वापस false;
	पूर्ण
पूर्ण

अटल bool connection_established(काष्ठा drbd_connection *connection,
				   काष्ठा socket **sock1,
				   काष्ठा socket **sock2)
अणु
	काष्ठा net_conf *nc;
	पूर्णांक समयout;
	bool ok;

	अगर (!*sock1 || !*sock2)
		वापस false;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	समयout = (nc->sock_check_समयo ?: nc->ping_समयo) * HZ / 10;
	rcu_पढ़ो_unlock();
	schedule_समयout_पूर्णांकerruptible(समयout);

	ok = drbd_socket_okay(sock1);
	ok = drbd_socket_okay(sock2) && ok;

	वापस ok;
पूर्ण

/* Gets called अगर a connection is established, or अगर a new minor माला_लो created
   in a connection */
पूर्णांक drbd_connected(काष्ठा drbd_peer_device *peer_device)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	पूर्णांक err;

	atomic_set(&device->packet_seq, 0);
	device->peer_seq = 0;

	device->state_mutex = peer_device->connection->agreed_pro_version < 100 ?
		&peer_device->connection->cstate_mutex :
		&device->own_state_mutex;

	err = drbd_send_sync_param(peer_device);
	अगर (!err)
		err = drbd_send_sizes(peer_device, 0, 0);
	अगर (!err)
		err = drbd_send_uuids(peer_device);
	अगर (!err)
		err = drbd_send_current_state(peer_device);
	clear_bit(USE_DEGR_WFC_T, &device->flags);
	clear_bit(RESIZE_PENDING, &device->flags);
	atomic_set(&device->ap_in_flight, 0);
	mod_समयr(&device->request_समयr, jअगरfies + HZ); /* just start it here. */
	वापस err;
पूर्ण

/*
 * वापस values:
 *   1 yes, we have a valid connection
 *   0 oops, did not work out, please try again
 *  -1 peer talks dअगरferent language,
 *     no poपूर्णांक in trying again, please go standalone.
 *  -2 We करो not have a network config...
 */
अटल पूर्णांक conn_connect(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_socket sock, msock;
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा net_conf *nc;
	पूर्णांक vnr, समयout, h;
	bool discard_my_data, ok;
	क्रमागत drbd_state_rv rv;
	काष्ठा accept_रुको_data ad = अणु
		.connection = connection,
		.करोor_bell = COMPLETION_INITIALIZER_ONSTACK(ad.करोor_bell),
	पूर्ण;

	clear_bit(DISCONNECT_SENT, &connection->flags);
	अगर (conn_request_state(connection, NS(conn, C_WF_CONNECTION), CS_VERBOSE) < SS_SUCCESS)
		वापस -2;

	mutex_init(&sock.mutex);
	sock.sbuf = connection->data.sbuf;
	sock.rbuf = connection->data.rbuf;
	sock.socket = शून्य;
	mutex_init(&msock.mutex);
	msock.sbuf = connection->meta.sbuf;
	msock.rbuf = connection->meta.rbuf;
	msock.socket = शून्य;

	/* Assume that the peer only understands protocol 80 until we know better.  */
	connection->agreed_pro_version = 80;

	अगर (prepare_listen_socket(connection, &ad))
		वापस 0;

	करो अणु
		काष्ठा socket *s;

		s = drbd_try_connect(connection);
		अगर (s) अणु
			अगर (!sock.socket) अणु
				sock.socket = s;
				send_first_packet(connection, &sock, P_INITIAL_DATA);
			पूर्ण अन्यथा अगर (!msock.socket) अणु
				clear_bit(RESOLVE_CONFLICTS, &connection->flags);
				msock.socket = s;
				send_first_packet(connection, &msock, P_INITIAL_META);
			पूर्ण अन्यथा अणु
				drbd_err(connection, "Logic error in conn_connect()\n");
				जाओ out_release_sockets;
			पूर्ण
		पूर्ण

		अगर (connection_established(connection, &sock.socket, &msock.socket))
			अवरोध;

retry:
		s = drbd_रुको_क्रम_connect(connection, &ad);
		अगर (s) अणु
			पूर्णांक fp = receive_first_packet(connection, s);
			drbd_socket_okay(&sock.socket);
			drbd_socket_okay(&msock.socket);
			चयन (fp) अणु
			हाल P_INITIAL_DATA:
				अगर (sock.socket) अणु
					drbd_warn(connection, "initial packet S crossed\n");
					sock_release(sock.socket);
					sock.socket = s;
					जाओ अक्रमomize;
				पूर्ण
				sock.socket = s;
				अवरोध;
			हाल P_INITIAL_META:
				set_bit(RESOLVE_CONFLICTS, &connection->flags);
				अगर (msock.socket) अणु
					drbd_warn(connection, "initial packet M crossed\n");
					sock_release(msock.socket);
					msock.socket = s;
					जाओ अक्रमomize;
				पूर्ण
				msock.socket = s;
				अवरोध;
			शेष:
				drbd_warn(connection, "Error receiving initial packet\n");
				sock_release(s);
अक्रमomize:
				अगर (pअक्रमom_u32() & 1)
					जाओ retry;
			पूर्ण
		पूर्ण

		अगर (connection->cstate <= C_DISCONNECTING)
			जाओ out_release_sockets;
		अगर (संकेत_pending(current)) अणु
			flush_संकेतs(current);
			smp_rmb();
			अगर (get_t_state(&connection->receiver) == EXITING)
				जाओ out_release_sockets;
		पूर्ण

		ok = connection_established(connection, &sock.socket, &msock.socket);
	पूर्ण जबतक (!ok);

	अगर (ad.s_listen)
		sock_release(ad.s_listen);

	sock.socket->sk->sk_reuse = SK_CAN_REUSE; /* SO_REUSEADDR */
	msock.socket->sk->sk_reuse = SK_CAN_REUSE; /* SO_REUSEADDR */

	sock.socket->sk->sk_allocation = GFP_NOIO;
	msock.socket->sk->sk_allocation = GFP_NOIO;

	sock.socket->sk->sk_priority = TC_PRIO_INTERACTIVE_BULK;
	msock.socket->sk->sk_priority = TC_PRIO_INTERACTIVE;

	/* NOT YET ...
	 * sock.socket->sk->sk_sndसमयo = connection->net_conf->समयout*HZ/10;
	 * sock.socket->sk->sk_rcvसमयo = MAX_SCHEDULE_TIMEOUT;
	 * first set it to the P_CONNECTION_FEATURES समयout,
	 * which we set to 4x the configured ping_समयout. */
	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);

	sock.socket->sk->sk_sndसमयo =
	sock.socket->sk->sk_rcvसमयo = nc->ping_समयo*4*HZ/10;

	msock.socket->sk->sk_rcvसमयo = nc->ping_पूर्णांक*HZ;
	समयout = nc->समयout * HZ / 10;
	discard_my_data = nc->discard_my_data;
	rcu_पढ़ो_unlock();

	msock.socket->sk->sk_sndसमयo = समयout;

	/* we करोn't want delays.
	 * we use TCP_CORK where appropriate, though */
	tcp_sock_set_nodelay(sock.socket->sk);
	tcp_sock_set_nodelay(msock.socket->sk);

	connection->data.socket = sock.socket;
	connection->meta.socket = msock.socket;
	connection->last_received = jअगरfies;

	h = drbd_करो_features(connection);
	अगर (h <= 0)
		वापस h;

	अगर (connection->cram_hmac_tfm) अणु
		/* drbd_request_state(device, NS(conn, WFAuth)); */
		चयन (drbd_करो_auth(connection)) अणु
		हाल -1:
			drbd_err(connection, "Authentication of peer failed\n");
			वापस -1;
		हाल 0:
			drbd_err(connection, "Authentication of peer failed, trying again.\n");
			वापस 0;
		पूर्ण
	पूर्ण

	connection->data.socket->sk->sk_sndसमयo = समयout;
	connection->data.socket->sk->sk_rcvसमयo = MAX_SCHEDULE_TIMEOUT;

	अगर (drbd_send_protocol(connection) == -EOPNOTSUPP)
		वापस -1;

	/* Prevent a race between resync-handshake and
	 * being promoted to Primary.
	 *
	 * Grab and release the state mutex, so we know that any current
	 * drbd_set_role() is finished, and any incoming drbd_set_role
	 * will see the STATE_SENT flag, and रुको क्रम it to be cleared.
	 */
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr)
		mutex_lock(peer_device->device->state_mutex);

	/* aव्योम a race with conn_request_state( C_DISCONNECTING ) */
	spin_lock_irq(&connection->resource->req_lock);
	set_bit(STATE_SENT, &connection->flags);
	spin_unlock_irq(&connection->resource->req_lock);

	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr)
		mutex_unlock(peer_device->device->state_mutex);

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		kref_get(&device->kref);
		rcu_पढ़ो_unlock();

		अगर (discard_my_data)
			set_bit(DISCARD_MY_DATA, &device->flags);
		अन्यथा
			clear_bit(DISCARD_MY_DATA, &device->flags);

		drbd_connected(peer_device);
		kref_put(&device->kref, drbd_destroy_device);
		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();

	rv = conn_request_state(connection, NS(conn, C_WF_REPORT_PARAMS), CS_VERBOSE);
	अगर (rv < SS_SUCCESS || connection->cstate != C_WF_REPORT_PARAMS) अणु
		clear_bit(STATE_SENT, &connection->flags);
		वापस 0;
	पूर्ण

	drbd_thपढ़ो_start(&connection->ack_receiver);
	/* खोलोcoded create_singlethपढ़ो_workqueue(),
	 * to be able to use क्रमmat string arguments */
	connection->ack_sender =
		alloc_ordered_workqueue("drbd_as_%s", WQ_MEM_RECLAIM, connection->resource->name);
	अगर (!connection->ack_sender) अणु
		drbd_err(connection, "Failed to create workqueue ack_sender\n");
		वापस 0;
	पूर्ण

	mutex_lock(&connection->resource->conf_update);
	/* The discard_my_data flag is a single-shot modअगरier to the next
	 * connection attempt, the handshake of which is now well underway.
	 * No need क्रम rcu style copying of the whole काष्ठा
	 * just to clear a single value. */
	connection->net_conf->discard_my_data = 0;
	mutex_unlock(&connection->resource->conf_update);

	वापस h;

out_release_sockets:
	अगर (ad.s_listen)
		sock_release(ad.s_listen);
	अगर (sock.socket)
		sock_release(sock.socket);
	अगर (msock.socket)
		sock_release(msock.socket);
	वापस -1;
पूर्ण

अटल पूर्णांक decode_header(काष्ठा drbd_connection *connection, व्योम *header, काष्ठा packet_info *pi)
अणु
	अचिन्हित पूर्णांक header_size = drbd_header_size(connection);

	अगर (header_size == माप(काष्ठा p_header100) &&
	    *(__be32 *)header == cpu_to_be32(DRBD_MAGIC_100)) अणु
		काष्ठा p_header100 *h = header;
		अगर (h->pad != 0) अणु
			drbd_err(connection, "Header padding is not zero\n");
			वापस -EINVAL;
		पूर्ण
		pi->vnr = be16_to_cpu(h->volume);
		pi->cmd = be16_to_cpu(h->command);
		pi->size = be32_to_cpu(h->length);
	पूर्ण अन्यथा अगर (header_size == माप(काष्ठा p_header95) &&
		   *(__be16 *)header == cpu_to_be16(DRBD_MAGIC_BIG)) अणु
		काष्ठा p_header95 *h = header;
		pi->cmd = be16_to_cpu(h->command);
		pi->size = be32_to_cpu(h->length);
		pi->vnr = 0;
	पूर्ण अन्यथा अगर (header_size == माप(काष्ठा p_header80) &&
		   *(__be32 *)header == cpu_to_be32(DRBD_MAGIC)) अणु
		काष्ठा p_header80 *h = header;
		pi->cmd = be16_to_cpu(h->command);
		pi->size = be16_to_cpu(h->length);
		pi->vnr = 0;
	पूर्ण अन्यथा अणु
		drbd_err(connection, "Wrong magic value 0x%08x in protocol version %d\n",
			 be32_to_cpu(*(__be32 *)header),
			 connection->agreed_pro_version);
		वापस -EINVAL;
	पूर्ण
	pi->data = header + header_size;
	वापस 0;
पूर्ण

अटल व्योम drbd_unplug_all_devices(काष्ठा drbd_connection *connection)
अणु
	अगर (current->plug == &connection->receiver_plug) अणु
		blk_finish_plug(&connection->receiver_plug);
		blk_start_plug(&connection->receiver_plug);
	पूर्ण /* अन्यथा: maybe just schedule() ?? */
पूर्ण

अटल पूर्णांक drbd_recv_header(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	व्योम *buffer = connection->data.rbuf;
	पूर्णांक err;

	err = drbd_recv_all_warn(connection, buffer, drbd_header_size(connection));
	अगर (err)
		वापस err;

	err = decode_header(connection, buffer, pi);
	connection->last_received = jअगरfies;

	वापस err;
पूर्ण

अटल पूर्णांक drbd_recv_header_maybe_unplug(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	व्योम *buffer = connection->data.rbuf;
	अचिन्हित पूर्णांक size = drbd_header_size(connection);
	पूर्णांक err;

	err = drbd_recv_लघु(connection->data.socket, buffer, size, MSG_NOSIGNAL|MSG_DONTWAIT);
	अगर (err != size) अणु
		/* If we have nothing in the receive buffer now, to reduce
		 * application latency, try to drain the backend queues as
		 * quickly as possible, and let remote TCP know what we have
		 * received so far. */
		अगर (err == -EAGAIN) अणु
			tcp_sock_set_quickack(connection->data.socket->sk, 2);
			drbd_unplug_all_devices(connection);
		पूर्ण
		अगर (err > 0) अणु
			buffer += err;
			size -= err;
		पूर्ण
		err = drbd_recv_all_warn(connection, buffer, size);
		अगर (err)
			वापस err;
	पूर्ण

	err = decode_header(connection, connection->data.rbuf, pi);
	connection->last_received = jअगरfies;

	वापस err;
पूर्ण
/* This is blkdev_issue_flush, but asynchronous.
 * We want to submit to all component volumes in parallel,
 * then रुको क्रम all completions.
 */
काष्ठा issue_flush_context अणु
	atomic_t pending;
	पूर्णांक error;
	काष्ठा completion करोne;
पूर्ण;
काष्ठा one_flush_context अणु
	काष्ठा drbd_device *device;
	काष्ठा issue_flush_context *ctx;
पूर्ण;

अटल व्योम one_flush_endio(काष्ठा bio *bio)
अणु
	काष्ठा one_flush_context *octx = bio->bi_निजी;
	काष्ठा drbd_device *device = octx->device;
	काष्ठा issue_flush_context *ctx = octx->ctx;

	अगर (bio->bi_status) अणु
		ctx->error = blk_status_to_त्रुटि_सं(bio->bi_status);
		drbd_info(device, "local disk FLUSH FAILED with status %d\n", bio->bi_status);
	पूर्ण
	kमुक्त(octx);
	bio_put(bio);

	clear_bit(FLUSH_PENDING, &device->flags);
	put_ldev(device);
	kref_put(&device->kref, drbd_destroy_device);

	अगर (atomic_dec_and_test(&ctx->pending))
		complete(&ctx->करोne);
पूर्ण

अटल व्योम submit_one_flush(काष्ठा drbd_device *device, काष्ठा issue_flush_context *ctx)
अणु
	काष्ठा bio *bio = bio_alloc(GFP_NOIO, 0);
	काष्ठा one_flush_context *octx = kदो_स्मृति(माप(*octx), GFP_NOIO);
	अगर (!bio || !octx) अणु
		drbd_warn(device, "Could not allocate a bio, CANNOT ISSUE FLUSH\n");
		/* FIXME: what अन्यथा can I करो now?  disconnecting or detaching
		 * really करोes not help to improve the state of the world, either.
		 */
		kमुक्त(octx);
		अगर (bio)
			bio_put(bio);

		ctx->error = -ENOMEM;
		put_ldev(device);
		kref_put(&device->kref, drbd_destroy_device);
		वापस;
	पूर्ण

	octx->device = device;
	octx->ctx = ctx;
	bio_set_dev(bio, device->ldev->backing_bdev);
	bio->bi_निजी = octx;
	bio->bi_end_io = one_flush_endio;
	bio->bi_opf = REQ_OP_FLUSH | REQ_PREFLUSH;

	device->flush_jअगर = jअगरfies;
	set_bit(FLUSH_PENDING, &device->flags);
	atomic_inc(&ctx->pending);
	submit_bio(bio);
पूर्ण

अटल व्योम drbd_flush(काष्ठा drbd_connection *connection)
अणु
	अगर (connection->resource->ग_लिखो_ordering >= WO_BDEV_FLUSH) अणु
		काष्ठा drbd_peer_device *peer_device;
		काष्ठा issue_flush_context ctx;
		पूर्णांक vnr;

		atomic_set(&ctx.pending, 1);
		ctx.error = 0;
		init_completion(&ctx.करोne);

		rcu_पढ़ो_lock();
		idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
			काष्ठा drbd_device *device = peer_device->device;

			अगर (!get_ldev(device))
				जारी;
			kref_get(&device->kref);
			rcu_पढ़ो_unlock();

			submit_one_flush(device, &ctx);

			rcu_पढ़ो_lock();
		पूर्ण
		rcu_पढ़ो_unlock();

		/* Do we want to add a समयout,
		 * अगर disk-समयout is set? */
		अगर (!atomic_dec_and_test(&ctx.pending))
			रुको_क्रम_completion(&ctx.करोne);

		अगर (ctx.error) अणु
			/* would rather check on EOPNOTSUPP, but that is not reliable.
			 * करोn't try again क्रम ANY वापस value != 0
			 * अगर (rv == -EOPNOTSUPP) */
			/* Any error is alपढ़ोy reported by bio_endio callback. */
			drbd_bump_ग_लिखो_ordering(connection->resource, शून्य, WO_DRAIN_IO);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * drbd_may_finish_epoch() - Applies an epoch_event to the epoch's state, eventually finishes it.
 * @connection:	DRBD connection.
 * @epoch:	Epoch object.
 * @ev:		Epoch event.
 */
अटल क्रमागत finish_epoch drbd_may_finish_epoch(काष्ठा drbd_connection *connection,
					       काष्ठा drbd_epoch *epoch,
					       क्रमागत epoch_event ev)
अणु
	पूर्णांक epoch_size;
	काष्ठा drbd_epoch *next_epoch;
	क्रमागत finish_epoch rv = FE_STILL_LIVE;

	spin_lock(&connection->epoch_lock);
	करो अणु
		next_epoch = शून्य;

		epoch_size = atomic_पढ़ो(&epoch->epoch_size);

		चयन (ev & ~EV_CLEANUP) अणु
		हाल EV_PUT:
			atomic_dec(&epoch->active);
			अवरोध;
		हाल EV_GOT_BARRIER_NR:
			set_bit(DE_HAVE_BARRIER_NUMBER, &epoch->flags);
			अवरोध;
		हाल EV_BECAME_LAST:
			/* nothing to करो*/
			अवरोध;
		पूर्ण

		अगर (epoch_size != 0 &&
		    atomic_पढ़ो(&epoch->active) == 0 &&
		    (test_bit(DE_HAVE_BARRIER_NUMBER, &epoch->flags) || ev & EV_CLEANUP)) अणु
			अगर (!(ev & EV_CLEANUP)) अणु
				spin_unlock(&connection->epoch_lock);
				drbd_send_b_ack(epoch->connection, epoch->barrier_nr, epoch_size);
				spin_lock(&connection->epoch_lock);
			पूर्ण
#अगर 0
			/* FIXME: dec unacked on connection, once we have
			 * something to count pending connection packets in. */
			अगर (test_bit(DE_HAVE_BARRIER_NUMBER, &epoch->flags))
				dec_unacked(epoch->connection);
#पूर्ण_अगर

			अगर (connection->current_epoch != epoch) अणु
				next_epoch = list_entry(epoch->list.next, काष्ठा drbd_epoch, list);
				list_del(&epoch->list);
				ev = EV_BECAME_LAST | (ev & EV_CLEANUP);
				connection->epochs--;
				kमुक्त(epoch);

				अगर (rv == FE_STILL_LIVE)
					rv = FE_DESTROYED;
			पूर्ण अन्यथा अणु
				epoch->flags = 0;
				atomic_set(&epoch->epoch_size, 0);
				/* atomic_set(&epoch->active, 0); is alपढ़ोy zero */
				अगर (rv == FE_STILL_LIVE)
					rv = FE_RECYCLED;
			पूर्ण
		पूर्ण

		अगर (!next_epoch)
			अवरोध;

		epoch = next_epoch;
	पूर्ण जबतक (1);

	spin_unlock(&connection->epoch_lock);

	वापस rv;
पूर्ण

अटल क्रमागत ग_लिखो_ordering_e
max_allowed_wo(काष्ठा drbd_backing_dev *bdev, क्रमागत ग_लिखो_ordering_e wo)
अणु
	काष्ठा disk_conf *dc;

	dc = rcu_dereference(bdev->disk_conf);

	अगर (wo == WO_BDEV_FLUSH && !dc->disk_flushes)
		wo = WO_DRAIN_IO;
	अगर (wo == WO_DRAIN_IO && !dc->disk_drain)
		wo = WO_NONE;

	वापस wo;
पूर्ण

/*
 * drbd_bump_ग_लिखो_ordering() - Fall back to an other ग_लिखो ordering method
 * @wo:		Write ordering method to try.
 */
व्योम drbd_bump_ग_लिखो_ordering(काष्ठा drbd_resource *resource, काष्ठा drbd_backing_dev *bdev,
			      क्रमागत ग_लिखो_ordering_e wo)
अणु
	काष्ठा drbd_device *device;
	क्रमागत ग_लिखो_ordering_e pwo;
	पूर्णांक vnr;
	अटल अक्षर *ग_लिखो_ordering_str[] = अणु
		[WO_NONE] = "none",
		[WO_DRAIN_IO] = "drain",
		[WO_BDEV_FLUSH] = "flush",
	पूर्ण;

	pwo = resource->ग_लिखो_ordering;
	अगर (wo != WO_BDEV_FLUSH)
		wo = min(pwo, wo);
	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&resource->devices, device, vnr) अणु
		अगर (get_ldev(device)) अणु
			wo = max_allowed_wo(device->ldev, wo);
			अगर (device->ldev == bdev)
				bdev = शून्य;
			put_ldev(device);
		पूर्ण
	पूर्ण

	अगर (bdev)
		wo = max_allowed_wo(bdev, wo);

	rcu_पढ़ो_unlock();

	resource->ग_लिखो_ordering = wo;
	अगर (pwo != resource->ग_लिखो_ordering || wo == WO_BDEV_FLUSH)
		drbd_info(resource, "Method to ensure write ordering: %s\n", ग_लिखो_ordering_str[resource->ग_लिखो_ordering]);
पूर्ण

/*
 * Mapping "discard" to ZEROOUT with UNMAP करोes not work क्रम us:
 * Drivers have to "announce" q->limits.max_ग_लिखो_zeroes_sectors, or it
 * will directly go to fallback mode, submitting normal ग_लिखोs, and
 * never even try to UNMAP.
 *
 * And dm-thin करोes not करो this (yet), mostly because in general it has
 * to assume that "skip_block_zeroing" is set.  See also:
 * https://www.mail-archive.com/dm-devel%40redhat.com/msg07965.hपंचांगl
 * https://www.redhat.com/archives/dm-devel/2018-January/msg00271.hपंचांगl
 *
 * We *may* ignore the discard-zeroes-data setting, अगर so configured.
 *
 * Assumption is that this "discard_zeroes_data=0" is only because the backend
 * may ignore partial unaligned discards.
 *
 * LVM/DM thin as of at least
 *   LVM version:     2.02.115(2)-RHEL7 (2015-01-28)
 *   Library version: 1.02.93-RHEL7 (2015-01-28)
 *   Driver version:  4.29.0
 * still behaves this way.
 *
 * For unaligned (wrt. alignment and granularity) or too small discards,
 * we zero-out the initial (and/or) trailing unaligned partial chunks,
 * but discard all the aligned full chunks.
 *
 * At least क्रम LVM/DM thin, with skip_block_zeroing=false,
 * the result is effectively "discard_zeroes_data=1".
 */
/* flags: EE_TRIM|EE_ZEROOUT */
पूर्णांक drbd_issue_discard_or_zero_out(काष्ठा drbd_device *device, sector_t start, अचिन्हित पूर्णांक nr_sectors, पूर्णांक flags)
अणु
	काष्ठा block_device *bdev = device->ldev->backing_bdev;
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	sector_t पंचांगp, nr;
	अचिन्हित पूर्णांक max_discard_sectors, granularity;
	पूर्णांक alignment;
	पूर्णांक err = 0;

	अगर ((flags & EE_ZEROOUT) || !(flags & EE_TRIM))
		जाओ zero_out;

	/* Zero-sector (unknown) and one-sector granularities are the same.  */
	granularity = max(q->limits.discard_granularity >> 9, 1U);
	alignment = (bdev_discard_alignment(bdev) >> 9) % granularity;

	max_discard_sectors = min(q->limits.max_discard_sectors, (1U << 22));
	max_discard_sectors -= max_discard_sectors % granularity;
	अगर (unlikely(!max_discard_sectors))
		जाओ zero_out;

	अगर (nr_sectors < granularity)
		जाओ zero_out;

	पंचांगp = start;
	अगर (sector_भाग(पंचांगp, granularity) != alignment) अणु
		अगर (nr_sectors < 2*granularity)
			जाओ zero_out;
		/* start + gran - (start + gran - align) % gran */
		पंचांगp = start + granularity - alignment;
		पंचांगp = start + granularity - sector_भाग(पंचांगp, granularity);

		nr = पंचांगp - start;
		/* करोn't flag BLKDEV_ZERO_NOUNMAP, we don't know how many
		 * layers are below us, some may have smaller granularity */
		err |= blkdev_issue_zeroout(bdev, start, nr, GFP_NOIO, 0);
		nr_sectors -= nr;
		start = पंचांगp;
	पूर्ण
	जबतक (nr_sectors >= max_discard_sectors) अणु
		err |= blkdev_issue_discard(bdev, start, max_discard_sectors, GFP_NOIO, 0);
		nr_sectors -= max_discard_sectors;
		start += max_discard_sectors;
	पूर्ण
	अगर (nr_sectors) अणु
		/* max_discard_sectors is अचिन्हित पूर्णांक (and a multiple of
		 * granularity, we made sure of that above alपढ़ोy);
		 * nr is < max_discard_sectors;
		 * I करोn't need sector_भाग here, even though nr is sector_t */
		nr = nr_sectors;
		nr -= (अचिन्हित पूर्णांक)nr % granularity;
		अगर (nr) अणु
			err |= blkdev_issue_discard(bdev, start, nr, GFP_NOIO, 0);
			nr_sectors -= nr;
			start += nr;
		पूर्ण
	पूर्ण
 zero_out:
	अगर (nr_sectors) अणु
		err |= blkdev_issue_zeroout(bdev, start, nr_sectors, GFP_NOIO,
				(flags & EE_TRIM) ? 0 : BLKDEV_ZERO_NOUNMAP);
	पूर्ण
	वापस err != 0;
पूर्ण

अटल bool can_करो_reliable_discards(काष्ठा drbd_device *device)
अणु
	काष्ठा request_queue *q = bdev_get_queue(device->ldev->backing_bdev);
	काष्ठा disk_conf *dc;
	bool can_करो;

	अगर (!blk_queue_discard(q))
		वापस false;

	rcu_पढ़ो_lock();
	dc = rcu_dereference(device->ldev->disk_conf);
	can_करो = dc->discard_zeroes_अगर_aligned;
	rcu_पढ़ो_unlock();
	वापस can_करो;
पूर्ण

अटल व्योम drbd_issue_peer_discard_or_zero_out(काष्ठा drbd_device *device, काष्ठा drbd_peer_request *peer_req)
अणु
	/* If the backend cannot discard, or करोes not guarantee
	 * पढ़ो-back zeroes in discarded ranges, we fall back to
	 * zero-out.  Unless configuration specअगरically requested
	 * otherwise. */
	अगर (!can_करो_reliable_discards(device))
		peer_req->flags |= EE_ZEROOUT;

	अगर (drbd_issue_discard_or_zero_out(device, peer_req->i.sector,
	    peer_req->i.size >> 9, peer_req->flags & (EE_ZEROOUT|EE_TRIM)))
		peer_req->flags |= EE_WAS_ERROR;
	drbd_endio_ग_लिखो_sec_final(peer_req);
पूर्ण

अटल व्योम drbd_issue_peer_wsame(काष्ठा drbd_device *device,
				  काष्ठा drbd_peer_request *peer_req)
अणु
	काष्ठा block_device *bdev = device->ldev->backing_bdev;
	sector_t s = peer_req->i.sector;
	sector_t nr = peer_req->i.size >> 9;
	अगर (blkdev_issue_ग_लिखो_same(bdev, s, nr, GFP_NOIO, peer_req->pages))
		peer_req->flags |= EE_WAS_ERROR;
	drbd_endio_ग_लिखो_sec_final(peer_req);
पूर्ण


/*
 * drbd_submit_peer_request()
 * @device:	DRBD device.
 * @peer_req:	peer request
 *
 * May spपढ़ो the pages to multiple bios,
 * depending on bio_add_page restrictions.
 *
 * Returns 0 अगर all bios have been submitted,
 * -ENOMEM अगर we could not allocate enough bios,
 * -ENOSPC (any better suggestion?) अगर we have not been able to bio_add_page a
 *  single page to an empty bio (which should never happen and likely indicates
 *  that the lower level IO stack is in some way broken). This has been observed
 *  on certain Xen deployments.
 */
/* TODO allocate from our own bio_set. */
पूर्णांक drbd_submit_peer_request(काष्ठा drbd_device *device,
			     काष्ठा drbd_peer_request *peer_req,
			     स्थिर अचिन्हित op, स्थिर अचिन्हित op_flags,
			     स्थिर पूर्णांक fault_type)
अणु
	काष्ठा bio *bios = शून्य;
	काष्ठा bio *bio;
	काष्ठा page *page = peer_req->pages;
	sector_t sector = peer_req->i.sector;
	अचिन्हित data_size = peer_req->i.size;
	अचिन्हित n_bios = 0;
	अचिन्हित nr_pages = (data_size + PAGE_SIZE -1) >> PAGE_SHIFT;
	पूर्णांक err = -ENOMEM;

	/* TRIM/DISCARD: क्रम now, always use the helper function
	 * blkdev_issue_zeroout(..., discard=true).
	 * It's synchronous, but it करोes the right thing wrt. bio splitting.
	 * Correctness first, perक्रमmance later.  Next step is to code an
	 * asynchronous variant of the same.
	 */
	अगर (peer_req->flags & (EE_TRIM|EE_WRITE_SAME|EE_ZEROOUT)) अणु
		/* रुको क्रम all pending IO completions, beक्रमe we start
		 * zeroing things out. */
		conn_रुको_active_ee_empty(peer_req->peer_device->connection);
		/* add it to the active list now,
		 * so we can find it to present it in debugfs */
		peer_req->submit_jअगर = jअगरfies;
		peer_req->flags |= EE_SUBMITTED;

		/* If this was a resync request from receive_rs_deallocated(),
		 * it is alपढ़ोy on the sync_ee list */
		अगर (list_empty(&peer_req->w.list)) अणु
			spin_lock_irq(&device->resource->req_lock);
			list_add_tail(&peer_req->w.list, &device->active_ee);
			spin_unlock_irq(&device->resource->req_lock);
		पूर्ण

		अगर (peer_req->flags & (EE_TRIM|EE_ZEROOUT))
			drbd_issue_peer_discard_or_zero_out(device, peer_req);
		अन्यथा /* EE_WRITE_SAME */
			drbd_issue_peer_wsame(device, peer_req);
		वापस 0;
	पूर्ण

	/* In most हालs, we will only need one bio.  But in हाल the lower
	 * level restrictions happen to be dअगरferent at this offset on this
	 * side than those of the sending peer, we may need to submit the
	 * request in more than one bio.
	 *
	 * Plain bio_alloc is good enough here, this is no DRBD पूर्णांकernally
	 * generated bio, but a bio allocated on behalf of the peer.
	 */
next_bio:
	bio = bio_alloc(GFP_NOIO, nr_pages);
	अगर (!bio) अणु
		drbd_err(device, "submit_ee: Allocation of a bio failed (nr_pages=%u)\n", nr_pages);
		जाओ fail;
	पूर्ण
	/* > peer_req->i.sector, unless this is the first bio */
	bio->bi_iter.bi_sector = sector;
	bio_set_dev(bio, device->ldev->backing_bdev);
	bio_set_op_attrs(bio, op, op_flags);
	bio->bi_निजी = peer_req;
	bio->bi_end_io = drbd_peer_request_endio;

	bio->bi_next = bios;
	bios = bio;
	++n_bios;

	page_chain_क्रम_each(page) अणु
		अचिन्हित len = min_t(अचिन्हित, data_size, PAGE_SIZE);
		अगर (!bio_add_page(bio, page, len, 0))
			जाओ next_bio;
		data_size -= len;
		sector += len >> 9;
		--nr_pages;
	पूर्ण
	D_ASSERT(device, data_size == 0);
	D_ASSERT(device, page == शून्य);

	atomic_set(&peer_req->pending_bios, n_bios);
	/* क्रम debugfs: update बारtamp, mark as submitted */
	peer_req->submit_jअगर = jअगरfies;
	peer_req->flags |= EE_SUBMITTED;
	करो अणु
		bio = bios;
		bios = bios->bi_next;
		bio->bi_next = शून्य;

		drbd_submit_bio_noacct(device, fault_type, bio);
	पूर्ण जबतक (bios);
	वापस 0;

fail:
	जबतक (bios) अणु
		bio = bios;
		bios = bios->bi_next;
		bio_put(bio);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम drbd_हटाओ_epoch_entry_पूर्णांकerval(काष्ठा drbd_device *device,
					     काष्ठा drbd_peer_request *peer_req)
अणु
	काष्ठा drbd_पूर्णांकerval *i = &peer_req->i;

	drbd_हटाओ_पूर्णांकerval(&device->ग_लिखो_requests, i);
	drbd_clear_पूर्णांकerval(i);

	/* Wake up any processes रुकोing क्रम this peer request to complete.  */
	अगर (i->रुकोing)
		wake_up(&device->misc_रुको);
पूर्ण

अटल व्योम conn_रुको_active_ee_empty(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;

		kref_get(&device->kref);
		rcu_पढ़ो_unlock();
		drbd_रुको_ee_list_empty(device, &device->active_ee);
		kref_put(&device->kref, drbd_destroy_device);
		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक receive_Barrier(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	पूर्णांक rv;
	काष्ठा p_barrier *p = pi->data;
	काष्ठा drbd_epoch *epoch;

	/* FIXME these are unacked on connection,
	 * not a specअगरic (peer)device.
	 */
	connection->current_epoch->barrier_nr = p->barrier;
	connection->current_epoch->connection = connection;
	rv = drbd_may_finish_epoch(connection, connection->current_epoch, EV_GOT_BARRIER_NR);

	/* P_BARRIER_ACK may imply that the corresponding extent is dropped from
	 * the activity log, which means it would not be resynced in हाल the
	 * R_PRIMARY crashes now.
	 * Thereक्रमe we must send the barrier_ack after the barrier request was
	 * completed. */
	चयन (connection->resource->ग_लिखो_ordering) अणु
	हाल WO_NONE:
		अगर (rv == FE_RECYCLED)
			वापस 0;

		/* receiver context, in the ग_लिखोout path of the other node.
		 * aव्योम potential distributed deadlock */
		epoch = kदो_स्मृति(माप(काष्ठा drbd_epoch), GFP_NOIO);
		अगर (epoch)
			अवरोध;
		अन्यथा
			drbd_warn(connection, "Allocation of an epoch failed, slowing down\n");
		fallthrough;

	हाल WO_BDEV_FLUSH:
	हाल WO_DRAIN_IO:
		conn_रुको_active_ee_empty(connection);
		drbd_flush(connection);

		अगर (atomic_पढ़ो(&connection->current_epoch->epoch_size)) अणु
			epoch = kदो_स्मृति(माप(काष्ठा drbd_epoch), GFP_NOIO);
			अगर (epoch)
				अवरोध;
		पूर्ण

		वापस 0;
	शेष:
		drbd_err(connection, "Strangeness in connection->write_ordering %d\n",
			 connection->resource->ग_लिखो_ordering);
		वापस -EIO;
	पूर्ण

	epoch->flags = 0;
	atomic_set(&epoch->epoch_size, 0);
	atomic_set(&epoch->active, 0);

	spin_lock(&connection->epoch_lock);
	अगर (atomic_पढ़ो(&connection->current_epoch->epoch_size)) अणु
		list_add(&epoch->list, &connection->current_epoch->list);
		connection->current_epoch = epoch;
		connection->epochs++;
	पूर्ण अन्यथा अणु
		/* The current_epoch got recycled जबतक we allocated this one... */
		kमुक्त(epoch);
	पूर्ण
	spin_unlock(&connection->epoch_lock);

	वापस 0;
पूर्ण

/* quick wrapper in हाल payload size != request_size (ग_लिखो same) */
अटल व्योम drbd_csum_ee_size(काष्ठा crypto_shash *h,
			      काष्ठा drbd_peer_request *r, व्योम *d,
			      अचिन्हित पूर्णांक payload_size)
अणु
	अचिन्हित पूर्णांक पंचांगp = r->i.size;
	r->i.size = payload_size;
	drbd_csum_ee(h, r, d);
	r->i.size = पंचांगp;
पूर्ण

/* used from receive_RSDataReply (recv_resync_पढ़ो)
 * and from receive_Data.
 * data_size: actual payload ("data in")
 * 	क्रम normal ग_लिखोs that is bi_size.
 * 	क्रम discards, that is zero.
 * 	क्रम ग_लिखो same, it is logical_block_size.
 * both trim and ग_लिखो same have the bi_size ("data len to be affected")
 * as extra argument in the packet header.
 */
अटल काष्ठा drbd_peer_request *
पढ़ो_in_block(काष्ठा drbd_peer_device *peer_device, u64 id, sector_t sector,
	      काष्ठा packet_info *pi) __must_hold(local)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	स्थिर sector_t capacity = get_capacity(device->vdisk);
	काष्ठा drbd_peer_request *peer_req;
	काष्ठा page *page;
	पूर्णांक digest_size, err;
	अचिन्हित पूर्णांक data_size = pi->size, ds;
	व्योम *dig_in = peer_device->connection->पूर्णांक_dig_in;
	व्योम *dig_vv = peer_device->connection->पूर्णांक_dig_vv;
	अचिन्हित दीर्घ *data;
	काष्ठा p_trim *trim = (pi->cmd == P_TRIM) ? pi->data : शून्य;
	काष्ठा p_trim *zeroes = (pi->cmd == P_ZEROES) ? pi->data : शून्य;
	काष्ठा p_trim *wsame = (pi->cmd == P_WSAME) ? pi->data : शून्य;

	digest_size = 0;
	अगर (!trim && peer_device->connection->peer_पूर्णांकegrity_tfm) अणु
		digest_size = crypto_shash_digestsize(peer_device->connection->peer_पूर्णांकegrity_tfm);
		/*
		 * FIXME: Receive the incoming digest पूर्णांकo the receive buffer
		 *	  here, together with its काष्ठा p_data?
		 */
		err = drbd_recv_all_warn(peer_device->connection, dig_in, digest_size);
		अगर (err)
			वापस शून्य;
		data_size -= digest_size;
	पूर्ण

	/* assume request_size == data_size, but special हाल trim and wsame. */
	ds = data_size;
	अगर (trim) अणु
		अगर (!expect(data_size == 0))
			वापस शून्य;
		ds = be32_to_cpu(trim->size);
	पूर्ण अन्यथा अगर (zeroes) अणु
		अगर (!expect(data_size == 0))
			वापस शून्य;
		ds = be32_to_cpu(zeroes->size);
	पूर्ण अन्यथा अगर (wsame) अणु
		अगर (data_size != queue_logical_block_size(device->rq_queue)) अणु
			drbd_err(peer_device, "data size (%u) != drbd logical block size (%u)\n",
				data_size, queue_logical_block_size(device->rq_queue));
			वापस शून्य;
		पूर्ण
		अगर (data_size != bdev_logical_block_size(device->ldev->backing_bdev)) अणु
			drbd_err(peer_device, "data size (%u) != backend logical block size (%u)\n",
				data_size, bdev_logical_block_size(device->ldev->backing_bdev));
			वापस शून्य;
		पूर्ण
		ds = be32_to_cpu(wsame->size);
	पूर्ण

	अगर (!expect(IS_ALIGNED(ds, 512)))
		वापस शून्य;
	अगर (trim || wsame || zeroes) अणु
		अगर (!expect(ds <= (DRBD_MAX_BBIO_SECTORS << 9)))
			वापस शून्य;
	पूर्ण अन्यथा अगर (!expect(ds <= DRBD_MAX_BIO_SIZE))
		वापस शून्य;

	/* even though we trust out peer,
	 * we someबार have to द्विगुन check. */
	अगर (sector + (ds>>9) > capacity) अणु
		drbd_err(device, "request from peer beyond end of local disk: "
			"capacity: %llus < sector: %llus + size: %u\n",
			(अचिन्हित दीर्घ दीर्घ)capacity,
			(अचिन्हित दीर्घ दीर्घ)sector, ds);
		वापस शून्य;
	पूर्ण

	/* GFP_NOIO, because we must not cause arbitrary ग_लिखो-out: in a DRBD
	 * "criss-cross" setup, that might cause ग_लिखो-out on some other DRBD,
	 * which in turn might block on the other node at this very place.  */
	peer_req = drbd_alloc_peer_req(peer_device, id, sector, ds, data_size, GFP_NOIO);
	अगर (!peer_req)
		वापस शून्य;

	peer_req->flags |= EE_WRITE;
	अगर (trim) अणु
		peer_req->flags |= EE_TRIM;
		वापस peer_req;
	पूर्ण
	अगर (zeroes) अणु
		peer_req->flags |= EE_ZEROOUT;
		वापस peer_req;
	पूर्ण
	अगर (wsame)
		peer_req->flags |= EE_WRITE_SAME;

	/* receive payload size bytes पूर्णांकo page chain */
	ds = data_size;
	page = peer_req->pages;
	page_chain_क्रम_each(page) अणु
		अचिन्हित len = min_t(पूर्णांक, ds, PAGE_SIZE);
		data = kmap(page);
		err = drbd_recv_all_warn(peer_device->connection, data, len);
		अगर (drbd_insert_fault(device, DRBD_FAULT_RECEIVE)) अणु
			drbd_err(device, "Fault injection: Corrupting data on receive\n");
			data[0] = data[0] ^ (अचिन्हित दीर्घ)-1;
		पूर्ण
		kunmap(page);
		अगर (err) अणु
			drbd_मुक्त_peer_req(device, peer_req);
			वापस शून्य;
		पूर्ण
		ds -= len;
	पूर्ण

	अगर (digest_size) अणु
		drbd_csum_ee_size(peer_device->connection->peer_पूर्णांकegrity_tfm, peer_req, dig_vv, data_size);
		अगर (स_भेद(dig_in, dig_vv, digest_size)) अणु
			drbd_err(device, "Digest integrity check FAILED: %llus +%u\n",
				(अचिन्हित दीर्घ दीर्घ)sector, data_size);
			drbd_मुक्त_peer_req(device, peer_req);
			वापस शून्य;
		पूर्ण
	पूर्ण
	device->recv_cnt += data_size >> 9;
	वापस peer_req;
पूर्ण

/* drbd_drain_block() just takes a data block
 * out of the socket input buffer, and discards it.
 */
अटल पूर्णांक drbd_drain_block(काष्ठा drbd_peer_device *peer_device, पूर्णांक data_size)
अणु
	काष्ठा page *page;
	पूर्णांक err = 0;
	व्योम *data;

	अगर (!data_size)
		वापस 0;

	page = drbd_alloc_pages(peer_device, 1, 1);

	data = kmap(page);
	जबतक (data_size) अणु
		अचिन्हित पूर्णांक len = min_t(पूर्णांक, data_size, PAGE_SIZE);

		err = drbd_recv_all_warn(peer_device->connection, data, len);
		अगर (err)
			अवरोध;
		data_size -= len;
	पूर्ण
	kunmap(page);
	drbd_मुक्त_pages(peer_device->device, page, 0);
	वापस err;
पूर्ण

अटल पूर्णांक recv_dless_पढ़ो(काष्ठा drbd_peer_device *peer_device, काष्ठा drbd_request *req,
			   sector_t sector, पूर्णांक data_size)
अणु
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;
	काष्ठा bio *bio;
	पूर्णांक digest_size, err, expect;
	व्योम *dig_in = peer_device->connection->पूर्णांक_dig_in;
	व्योम *dig_vv = peer_device->connection->पूर्णांक_dig_vv;

	digest_size = 0;
	अगर (peer_device->connection->peer_पूर्णांकegrity_tfm) अणु
		digest_size = crypto_shash_digestsize(peer_device->connection->peer_पूर्णांकegrity_tfm);
		err = drbd_recv_all_warn(peer_device->connection, dig_in, digest_size);
		अगर (err)
			वापस err;
		data_size -= digest_size;
	पूर्ण

	/* optimistically update recv_cnt.  अगर receiving fails below,
	 * we disconnect anyways, and counters will be reset. */
	peer_device->device->recv_cnt += data_size>>9;

	bio = req->master_bio;
	D_ASSERT(peer_device->device, sector == bio->bi_iter.bi_sector);

	bio_क्रम_each_segment(bvec, bio, iter) अणु
		व्योम *mapped = kmap(bvec.bv_page) + bvec.bv_offset;
		expect = min_t(पूर्णांक, data_size, bvec.bv_len);
		err = drbd_recv_all_warn(peer_device->connection, mapped, expect);
		kunmap(bvec.bv_page);
		अगर (err)
			वापस err;
		data_size -= expect;
	पूर्ण

	अगर (digest_size) अणु
		drbd_csum_bio(peer_device->connection->peer_पूर्णांकegrity_tfm, bio, dig_vv);
		अगर (स_भेद(dig_in, dig_vv, digest_size)) अणु
			drbd_err(peer_device, "Digest integrity check FAILED. Broken NICs?\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	D_ASSERT(peer_device->device, data_size == 0);
	वापस 0;
पूर्ण

/*
 * e_end_resync_block() is called in ack_sender context via
 * drbd_finish_peer_reqs().
 */
अटल पूर्णांक e_end_resync_block(काष्ठा drbd_work *w, पूर्णांक unused)
अणु
	काष्ठा drbd_peer_request *peer_req =
		container_of(w, काष्ठा drbd_peer_request, w);
	काष्ठा drbd_peer_device *peer_device = peer_req->peer_device;
	काष्ठा drbd_device *device = peer_device->device;
	sector_t sector = peer_req->i.sector;
	पूर्णांक err;

	D_ASSERT(device, drbd_पूर्णांकerval_empty(&peer_req->i));

	अगर (likely((peer_req->flags & EE_WAS_ERROR) == 0)) अणु
		drbd_set_in_sync(device, sector, peer_req->i.size);
		err = drbd_send_ack(peer_device, P_RS_WRITE_ACK, peer_req);
	पूर्ण अन्यथा अणु
		/* Record failure to sync */
		drbd_rs_failed_io(device, sector, peer_req->i.size);

		err  = drbd_send_ack(peer_device, P_NEG_ACK, peer_req);
	पूर्ण
	dec_unacked(device);

	वापस err;
पूर्ण

अटल पूर्णांक recv_resync_पढ़ो(काष्ठा drbd_peer_device *peer_device, sector_t sector,
			    काष्ठा packet_info *pi) __releases(local)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा drbd_peer_request *peer_req;

	peer_req = पढ़ो_in_block(peer_device, ID_SYNCER, sector, pi);
	अगर (!peer_req)
		जाओ fail;

	dec_rs_pending(device);

	inc_unacked(device);
	/* corresponding dec_unacked() in e_end_resync_block()
	 * respective _drbd_clear_करोne_ee */

	peer_req->w.cb = e_end_resync_block;
	peer_req->submit_jअगर = jअगरfies;

	spin_lock_irq(&device->resource->req_lock);
	list_add_tail(&peer_req->w.list, &device->sync_ee);
	spin_unlock_irq(&device->resource->req_lock);

	atomic_add(pi->size >> 9, &device->rs_sect_ev);
	अगर (drbd_submit_peer_request(device, peer_req, REQ_OP_WRITE, 0,
				     DRBD_FAULT_RS_WR) == 0)
		वापस 0;

	/* करोn't care क्रम the reason here */
	drbd_err(device, "submit failed, triggering re-connect\n");
	spin_lock_irq(&device->resource->req_lock);
	list_del(&peer_req->w.list);
	spin_unlock_irq(&device->resource->req_lock);

	drbd_मुक्त_peer_req(device, peer_req);
fail:
	put_ldev(device);
	वापस -EIO;
पूर्ण

अटल काष्ठा drbd_request *
find_request(काष्ठा drbd_device *device, काष्ठा rb_root *root, u64 id,
	     sector_t sector, bool missing_ok, स्थिर अक्षर *func)
अणु
	काष्ठा drbd_request *req;

	/* Request object according to our peer */
	req = (काष्ठा drbd_request *)(अचिन्हित दीर्घ)id;
	अगर (drbd_contains_पूर्णांकerval(root, sector, &req->i) && req->i.local)
		वापस req;
	अगर (!missing_ok) अणु
		drbd_err(device, "%s: failed to find request 0x%lx, sector %llus\n", func,
			(अचिन्हित दीर्घ)id, (अचिन्हित दीर्घ दीर्घ)sector);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक receive_DataReply(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा drbd_request *req;
	sector_t sector;
	पूर्णांक err;
	काष्ठा p_data *p = pi->data;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	sector = be64_to_cpu(p->sector);

	spin_lock_irq(&device->resource->req_lock);
	req = find_request(device, &device->पढ़ो_requests, p->block_id, sector, false, __func__);
	spin_unlock_irq(&device->resource->req_lock);
	अगर (unlikely(!req))
		वापस -EIO;

	/* hlist_del(&req->collision) is करोne in _req_may_be_करोne, to aव्योम
	 * special casing it there क्रम the various failure हालs.
	 * still no race with drbd_fail_pending_पढ़ोs */
	err = recv_dless_पढ़ो(peer_device, req, sector, pi->size);
	अगर (!err)
		req_mod(req, DATA_RECEIVED);
	/* अन्यथा: nothing. handled from drbd_disconnect...
	 * I करोn't think we may complete this just yet
	 * in हाल we are "on-disconnect: freeze" */

	वापस err;
पूर्ण

अटल पूर्णांक receive_RSDataReply(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	sector_t sector;
	पूर्णांक err;
	काष्ठा p_data *p = pi->data;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	sector = be64_to_cpu(p->sector);
	D_ASSERT(device, p->block_id == ID_SYNCER);

	अगर (get_ldev(device)) अणु
		/* data is submitted to disk within recv_resync_पढ़ो.
		 * corresponding put_ldev करोne below on error,
		 * or in drbd_peer_request_endio. */
		err = recv_resync_पढ़ो(peer_device, sector, pi);
	पूर्ण अन्यथा अणु
		अगर (__ratelimit(&drbd_ratelimit_state))
			drbd_err(device, "Can not write resync data to local disk.\n");

		err = drbd_drain_block(peer_device, pi->size);

		drbd_send_ack_dp(peer_device, P_NEG_ACK, p, pi->size);
	पूर्ण

	atomic_add(pi->size >> 9, &device->rs_sect_in);

	वापस err;
पूर्ण

अटल व्योम restart_conflicting_ग_लिखोs(काष्ठा drbd_device *device,
				       sector_t sector, पूर्णांक size)
अणु
	काष्ठा drbd_पूर्णांकerval *i;
	काष्ठा drbd_request *req;

	drbd_क्रम_each_overlap(i, &device->ग_लिखो_requests, sector, size) अणु
		अगर (!i->local)
			जारी;
		req = container_of(i, काष्ठा drbd_request, i);
		अगर (req->rq_state & RQ_LOCAL_PENDING ||
		    !(req->rq_state & RQ_POSTPONED))
			जारी;
		/* as it is RQ_POSTPONED, this will cause it to
		 * be queued on the retry workqueue. */
		__req_mod(req, CONFLICT_RESOLVED, शून्य);
	पूर्ण
पूर्ण

/*
 * e_end_block() is called in ack_sender context via drbd_finish_peer_reqs().
 */
अटल पूर्णांक e_end_block(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_peer_request *peer_req =
		container_of(w, काष्ठा drbd_peer_request, w);
	काष्ठा drbd_peer_device *peer_device = peer_req->peer_device;
	काष्ठा drbd_device *device = peer_device->device;
	sector_t sector = peer_req->i.sector;
	पूर्णांक err = 0, pcmd;

	अगर (peer_req->flags & EE_SEND_WRITE_ACK) अणु
		अगर (likely((peer_req->flags & EE_WAS_ERROR) == 0)) अणु
			pcmd = (device->state.conn >= C_SYNC_SOURCE &&
				device->state.conn <= C_PAUSED_SYNC_T &&
				peer_req->flags & EE_MAY_SET_IN_SYNC) ?
				P_RS_WRITE_ACK : P_WRITE_ACK;
			err = drbd_send_ack(peer_device, pcmd, peer_req);
			अगर (pcmd == P_RS_WRITE_ACK)
				drbd_set_in_sync(device, sector, peer_req->i.size);
		पूर्ण अन्यथा अणु
			err = drbd_send_ack(peer_device, P_NEG_ACK, peer_req);
			/* we expect it to be marked out of sync anyways...
			 * maybe निश्चित this?  */
		पूर्ण
		dec_unacked(device);
	पूर्ण

	/* we delete from the conflict detection hash _after_ we sent out the
	 * P_WRITE_ACK / P_NEG_ACK, to get the sequence number right.  */
	अगर (peer_req->flags & EE_IN_INTERVAL_TREE) अणु
		spin_lock_irq(&device->resource->req_lock);
		D_ASSERT(device, !drbd_पूर्णांकerval_empty(&peer_req->i));
		drbd_हटाओ_epoch_entry_पूर्णांकerval(device, peer_req);
		अगर (peer_req->flags & EE_RESTART_REQUESTS)
			restart_conflicting_ग_लिखोs(device, sector, peer_req->i.size);
		spin_unlock_irq(&device->resource->req_lock);
	पूर्ण अन्यथा
		D_ASSERT(device, drbd_पूर्णांकerval_empty(&peer_req->i));

	drbd_may_finish_epoch(peer_device->connection, peer_req->epoch, EV_PUT + (cancel ? EV_CLEANUP : 0));

	वापस err;
पूर्ण

अटल पूर्णांक e_send_ack(काष्ठा drbd_work *w, क्रमागत drbd_packet ack)
अणु
	काष्ठा drbd_peer_request *peer_req =
		container_of(w, काष्ठा drbd_peer_request, w);
	काष्ठा drbd_peer_device *peer_device = peer_req->peer_device;
	पूर्णांक err;

	err = drbd_send_ack(peer_device, ack, peer_req);
	dec_unacked(peer_device->device);

	वापस err;
पूर्ण

अटल पूर्णांक e_send_superseded(काष्ठा drbd_work *w, पूर्णांक unused)
अणु
	वापस e_send_ack(w, P_SUPERSEDED);
पूर्ण

अटल पूर्णांक e_send_retry_ग_लिखो(काष्ठा drbd_work *w, पूर्णांक unused)
अणु
	काष्ठा drbd_peer_request *peer_req =
		container_of(w, काष्ठा drbd_peer_request, w);
	काष्ठा drbd_connection *connection = peer_req->peer_device->connection;

	वापस e_send_ack(w, connection->agreed_pro_version >= 100 ?
			     P_RETRY_WRITE : P_SUPERSEDED);
पूर्ण

अटल bool seq_greater(u32 a, u32 b)
अणु
	/*
	 * We assume 32-bit wrap-around here.
	 * For 24-bit wrap-around, we would have to shअगरt:
	 *  a <<= 8; b <<= 8;
	 */
	वापस (s32)a - (s32)b > 0;
पूर्ण

अटल u32 seq_max(u32 a, u32 b)
अणु
	वापस seq_greater(a, b) ? a : b;
पूर्ण

अटल व्योम update_peer_seq(काष्ठा drbd_peer_device *peer_device, अचिन्हित पूर्णांक peer_seq)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	अचिन्हित पूर्णांक newest_peer_seq;

	अगर (test_bit(RESOLVE_CONFLICTS, &peer_device->connection->flags)) अणु
		spin_lock(&device->peer_seq_lock);
		newest_peer_seq = seq_max(device->peer_seq, peer_seq);
		device->peer_seq = newest_peer_seq;
		spin_unlock(&device->peer_seq_lock);
		/* wake up only अगर we actually changed device->peer_seq */
		अगर (peer_seq == newest_peer_seq)
			wake_up(&device->seq_रुको);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक overlaps(sector_t s1, पूर्णांक l1, sector_t s2, पूर्णांक l2)
अणु
	वापस !((s1 + (l1>>9) <= s2) || (s1 >= s2 + (l2>>9)));
पूर्ण

/* maybe change sync_ee पूर्णांकo पूर्णांकerval trees as well? */
अटल bool overlapping_resync_ग_लिखो(काष्ठा drbd_device *device, काष्ठा drbd_peer_request *peer_req)
अणु
	काष्ठा drbd_peer_request *rs_req;
	bool rv = false;

	spin_lock_irq(&device->resource->req_lock);
	list_क्रम_each_entry(rs_req, &device->sync_ee, w.list) अणु
		अगर (overlaps(peer_req->i.sector, peer_req->i.size,
			     rs_req->i.sector, rs_req->i.size)) अणु
			rv = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&device->resource->req_lock);

	वापस rv;
पूर्ण

/* Called from receive_Data.
 * Synchronize packets on sock with packets on msock.
 *
 * This is here so even when a P_DATA packet traveling via sock overtook an Ack
 * packet traveling on msock, they are still processed in the order they have
 * been sent.
 *
 * Note: we करोn't care क्रम Ack packets overtaking P_DATA packets.
 *
 * In हाल packet_seq is larger than device->peer_seq number, there are
 * outstanding packets on the msock. We रुको क्रम them to arrive.
 * In हाल we are the logically next packet, we update device->peer_seq
 * ourselves. Correctly handles 32bit wrap around.
 *
 * Assume we have a 10 GBit connection, that is about 1<<30 byte per second,
 * about 1<<21 sectors per second. So "worst" हाल, we have 1<<3 == 8 seconds
 * क्रम the 24bit wrap (historical atomic_t guarantee on some archs), and we have
 * 1<<9 == 512 seconds aka ages क्रम the 32bit wrap around...
 *
 * वापसs 0 अगर we may process the packet,
 * -ERESTARTSYS अगर we were पूर्णांकerrupted (by disconnect संकेत). */
अटल पूर्णांक रुको_क्रम_and_update_peer_seq(काष्ठा drbd_peer_device *peer_device, स्थिर u32 peer_seq)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	DEFINE_WAIT(रुको);
	दीर्घ समयout;
	पूर्णांक ret = 0, tp;

	अगर (!test_bit(RESOLVE_CONFLICTS, &peer_device->connection->flags))
		वापस 0;

	spin_lock(&device->peer_seq_lock);
	क्रम (;;) अणु
		अगर (!seq_greater(peer_seq - 1, device->peer_seq)) अणु
			device->peer_seq = seq_max(device->peer_seq, peer_seq);
			अवरोध;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		rcu_पढ़ो_lock();
		tp = rcu_dereference(peer_device->connection->net_conf)->two_primaries;
		rcu_पढ़ो_unlock();

		अगर (!tp)
			अवरोध;

		/* Only need to रुको अगर two_primaries is enabled */
		prepare_to_रुको(&device->seq_रुको, &रुको, TASK_INTERRUPTIBLE);
		spin_unlock(&device->peer_seq_lock);
		rcu_पढ़ो_lock();
		समयout = rcu_dereference(peer_device->connection->net_conf)->ping_समयo*HZ/10;
		rcu_पढ़ो_unlock();
		समयout = schedule_समयout(समयout);
		spin_lock(&device->peer_seq_lock);
		अगर (!समयout) अणु
			ret = -ETIMEDOUT;
			drbd_err(device, "Timed out waiting for missing ack packets; disconnecting\n");
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&device->peer_seq_lock);
	finish_रुको(&device->seq_रुको, &रुको);
	वापस ret;
पूर्ण

/* see also bio_flags_to_wire()
 * DRBD_REQ_*, because we need to semantically map the flags to data packet
 * flags and back. We may replicate to other kernel versions. */
अटल अचिन्हित दीर्घ wire_flags_to_bio_flags(u32 dpf)
अणु
	वापस  (dpf & DP_RW_SYNC ? REQ_SYNC : 0) |
		(dpf & DP_FUA ? REQ_FUA : 0) |
		(dpf & DP_FLUSH ? REQ_PREFLUSH : 0);
पूर्ण

अटल अचिन्हित दीर्घ wire_flags_to_bio_op(u32 dpf)
अणु
	अगर (dpf & DP_ZEROES)
		वापस REQ_OP_WRITE_ZEROES;
	अगर (dpf & DP_DISCARD)
		वापस REQ_OP_DISCARD;
	अगर (dpf & DP_WSAME)
		वापस REQ_OP_WRITE_SAME;
	अन्यथा
		वापस REQ_OP_WRITE;
पूर्ण

अटल व्योम fail_postponed_requests(काष्ठा drbd_device *device, sector_t sector,
				    अचिन्हित पूर्णांक size)
अणु
	काष्ठा drbd_पूर्णांकerval *i;

    repeat:
	drbd_क्रम_each_overlap(i, &device->ग_लिखो_requests, sector, size) अणु
		काष्ठा drbd_request *req;
		काष्ठा bio_and_error m;

		अगर (!i->local)
			जारी;
		req = container_of(i, काष्ठा drbd_request, i);
		अगर (!(req->rq_state & RQ_POSTPONED))
			जारी;
		req->rq_state &= ~RQ_POSTPONED;
		__req_mod(req, NEG_ACKED, &m);
		spin_unlock_irq(&device->resource->req_lock);
		अगर (m.bio)
			complete_master_bio(device, &m);
		spin_lock_irq(&device->resource->req_lock);
		जाओ repeat;
	पूर्ण
पूर्ण

अटल पूर्णांक handle_ग_लिखो_conflicts(काष्ठा drbd_device *device,
				  काष्ठा drbd_peer_request *peer_req)
अणु
	काष्ठा drbd_connection *connection = peer_req->peer_device->connection;
	bool resolve_conflicts = test_bit(RESOLVE_CONFLICTS, &connection->flags);
	sector_t sector = peer_req->i.sector;
	स्थिर अचिन्हित पूर्णांक size = peer_req->i.size;
	काष्ठा drbd_पूर्णांकerval *i;
	bool equal;
	पूर्णांक err;

	/*
	 * Inserting the peer request पूर्णांकo the ग_लिखो_requests tree will prevent
	 * new conflicting local requests from being added.
	 */
	drbd_insert_पूर्णांकerval(&device->ग_लिखो_requests, &peer_req->i);

    repeat:
	drbd_क्रम_each_overlap(i, &device->ग_लिखो_requests, sector, size) अणु
		अगर (i == &peer_req->i)
			जारी;
		अगर (i->completed)
			जारी;

		अगर (!i->local) अणु
			/*
			 * Our peer has sent a conflicting remote request; this
			 * should not happen in a two-node setup.  Wait क्रम the
			 * earlier peer request to complete.
			 */
			err = drbd_रुको_misc(device, i);
			अगर (err)
				जाओ out;
			जाओ repeat;
		पूर्ण

		equal = i->sector == sector && i->size == size;
		अगर (resolve_conflicts) अणु
			/*
			 * If the peer request is fully contained within the
			 * overlapping request, it can be considered overwritten
			 * and thus superseded; otherwise, it will be retried
			 * once all overlapping requests have completed.
			 */
			bool superseded = i->sector <= sector && i->sector +
				       (i->size >> 9) >= sector + (size >> 9);

			अगर (!equal)
				drbd_alert(device, "Concurrent writes detected: "
					       "local=%llus +%u, remote=%llus +%u, "
					       "assuming %s came first\n",
					  (अचिन्हित दीर्घ दीर्घ)i->sector, i->size,
					  (अचिन्हित दीर्घ दीर्घ)sector, size,
					  superseded ? "local" : "remote");

			peer_req->w.cb = superseded ? e_send_superseded :
						   e_send_retry_ग_लिखो;
			list_add_tail(&peer_req->w.list, &device->करोne_ee);
			queue_work(connection->ack_sender, &peer_req->peer_device->send_acks_work);

			err = -ENOENT;
			जाओ out;
		पूर्ण अन्यथा अणु
			काष्ठा drbd_request *req =
				container_of(i, काष्ठा drbd_request, i);

			अगर (!equal)
				drbd_alert(device, "Concurrent writes detected: "
					       "local=%llus +%u, remote=%llus +%u\n",
					  (अचिन्हित दीर्घ दीर्घ)i->sector, i->size,
					  (अचिन्हित दीर्घ दीर्घ)sector, size);

			अगर (req->rq_state & RQ_LOCAL_PENDING ||
			    !(req->rq_state & RQ_POSTPONED)) अणु
				/*
				 * Wait क्रम the node with the discard flag to
				 * decide अगर this request has been superseded
				 * or needs to be retried.
				 * Requests that have been superseded will
				 * disappear from the ग_लिखो_requests tree.
				 *
				 * In addition, रुको क्रम the conflicting
				 * request to finish locally beक्रमe submitting
				 * the conflicting peer request.
				 */
				err = drbd_रुको_misc(device, &req->i);
				अगर (err) अणु
					_conn_request_state(connection, NS(conn, C_TIMEOUT), CS_HARD);
					fail_postponed_requests(device, sector, size);
					जाओ out;
				पूर्ण
				जाओ repeat;
			पूर्ण
			/*
			 * Remember to restart the conflicting requests after
			 * the new peer request has completed.
			 */
			peer_req->flags |= EE_RESTART_REQUESTS;
		पूर्ण
	पूर्ण
	err = 0;

    out:
	अगर (err)
		drbd_हटाओ_epoch_entry_पूर्णांकerval(device, peer_req);
	वापस err;
पूर्ण

/* mirrored ग_लिखो */
अटल पूर्णांक receive_Data(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा net_conf *nc;
	sector_t sector;
	काष्ठा drbd_peer_request *peer_req;
	काष्ठा p_data *p = pi->data;
	u32 peer_seq = be32_to_cpu(p->seq_num);
	पूर्णांक op, op_flags;
	u32 dp_flags;
	पूर्णांक err, tp;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	अगर (!get_ldev(device)) अणु
		पूर्णांक err2;

		err = रुको_क्रम_and_update_peer_seq(peer_device, peer_seq);
		drbd_send_ack_dp(peer_device, P_NEG_ACK, p, pi->size);
		atomic_inc(&connection->current_epoch->epoch_size);
		err2 = drbd_drain_block(peer_device, pi->size);
		अगर (!err)
			err = err2;
		वापस err;
	पूर्ण

	/*
	 * Corresponding put_ldev करोne either below (on various errors), or in
	 * drbd_peer_request_endio, अगर we successfully submit the data at the
	 * end of this function.
	 */

	sector = be64_to_cpu(p->sector);
	peer_req = पढ़ो_in_block(peer_device, p->block_id, sector, pi);
	अगर (!peer_req) अणु
		put_ldev(device);
		वापस -EIO;
	पूर्ण

	peer_req->w.cb = e_end_block;
	peer_req->submit_jअगर = jअगरfies;
	peer_req->flags |= EE_APPLICATION;

	dp_flags = be32_to_cpu(p->dp_flags);
	op = wire_flags_to_bio_op(dp_flags);
	op_flags = wire_flags_to_bio_flags(dp_flags);
	अगर (pi->cmd == P_TRIM) अणु
		D_ASSERT(peer_device, peer_req->i.size > 0);
		D_ASSERT(peer_device, op == REQ_OP_DISCARD);
		D_ASSERT(peer_device, peer_req->pages == शून्य);
		/* need to play safe: an older DRBD sender
		 * may mean zero-out जबतक sending P_TRIM. */
		अगर (0 == (connection->agreed_features & DRBD_FF_WZEROES))
			peer_req->flags |= EE_ZEROOUT;
	पूर्ण अन्यथा अगर (pi->cmd == P_ZEROES) अणु
		D_ASSERT(peer_device, peer_req->i.size > 0);
		D_ASSERT(peer_device, op == REQ_OP_WRITE_ZEROES);
		D_ASSERT(peer_device, peer_req->pages == शून्य);
		/* Do (not) pass करोwn BLKDEV_ZERO_NOUNMAP? */
		अगर (dp_flags & DP_DISCARD)
			peer_req->flags |= EE_TRIM;
	पूर्ण अन्यथा अगर (peer_req->pages == शून्य) अणु
		D_ASSERT(device, peer_req->i.size == 0);
		D_ASSERT(device, dp_flags & DP_FLUSH);
	पूर्ण

	अगर (dp_flags & DP_MAY_SET_IN_SYNC)
		peer_req->flags |= EE_MAY_SET_IN_SYNC;

	spin_lock(&connection->epoch_lock);
	peer_req->epoch = connection->current_epoch;
	atomic_inc(&peer_req->epoch->epoch_size);
	atomic_inc(&peer_req->epoch->active);
	spin_unlock(&connection->epoch_lock);

	rcu_पढ़ो_lock();
	nc = rcu_dereference(peer_device->connection->net_conf);
	tp = nc->two_primaries;
	अगर (peer_device->connection->agreed_pro_version < 100) अणु
		चयन (nc->wire_protocol) अणु
		हाल DRBD_PROT_C:
			dp_flags |= DP_SEND_WRITE_ACK;
			अवरोध;
		हाल DRBD_PROT_B:
			dp_flags |= DP_SEND_RECEIVE_ACK;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (dp_flags & DP_SEND_WRITE_ACK) अणु
		peer_req->flags |= EE_SEND_WRITE_ACK;
		inc_unacked(device);
		/* corresponding dec_unacked() in e_end_block()
		 * respective _drbd_clear_करोne_ee */
	पूर्ण

	अगर (dp_flags & DP_SEND_RECEIVE_ACK) अणु
		/* I really करोn't like it that the receiver thपढ़ो
		 * sends on the msock, but anyways */
		drbd_send_ack(peer_device, P_RECV_ACK, peer_req);
	पूर्ण

	अगर (tp) अणु
		/* two primaries implies protocol C */
		D_ASSERT(device, dp_flags & DP_SEND_WRITE_ACK);
		peer_req->flags |= EE_IN_INTERVAL_TREE;
		err = रुको_क्रम_and_update_peer_seq(peer_device, peer_seq);
		अगर (err)
			जाओ out_पूर्णांकerrupted;
		spin_lock_irq(&device->resource->req_lock);
		err = handle_ग_लिखो_conflicts(device, peer_req);
		अगर (err) अणु
			spin_unlock_irq(&device->resource->req_lock);
			अगर (err == -ENOENT) अणु
				put_ldev(device);
				वापस 0;
			पूर्ण
			जाओ out_पूर्णांकerrupted;
		पूर्ण
	पूर्ण अन्यथा अणु
		update_peer_seq(peer_device, peer_seq);
		spin_lock_irq(&device->resource->req_lock);
	पूर्ण
	/* TRIM and WRITE_SAME are processed synchronously,
	 * we रुको क्रम all pending requests, respectively रुको क्रम
	 * active_ee to become empty in drbd_submit_peer_request();
	 * better not add ourselves here. */
	अगर ((peer_req->flags & (EE_TRIM|EE_WRITE_SAME|EE_ZEROOUT)) == 0)
		list_add_tail(&peer_req->w.list, &device->active_ee);
	spin_unlock_irq(&device->resource->req_lock);

	अगर (device->state.conn == C_SYNC_TARGET)
		रुको_event(device->ee_रुको, !overlapping_resync_ग_लिखो(device, peer_req));

	अगर (device->state.pdsk < D_INCONSISTENT) अणु
		/* In हाल we have the only disk of the cluster, */
		drbd_set_out_of_sync(device, peer_req->i.sector, peer_req->i.size);
		peer_req->flags &= ~EE_MAY_SET_IN_SYNC;
		drbd_al_begin_io(device, &peer_req->i);
		peer_req->flags |= EE_CALL_AL_COMPLETE_IO;
	पूर्ण

	err = drbd_submit_peer_request(device, peer_req, op, op_flags,
				       DRBD_FAULT_DT_WR);
	अगर (!err)
		वापस 0;

	/* करोn't care क्रम the reason here */
	drbd_err(device, "submit failed, triggering re-connect\n");
	spin_lock_irq(&device->resource->req_lock);
	list_del(&peer_req->w.list);
	drbd_हटाओ_epoch_entry_पूर्णांकerval(device, peer_req);
	spin_unlock_irq(&device->resource->req_lock);
	अगर (peer_req->flags & EE_CALL_AL_COMPLETE_IO) अणु
		peer_req->flags &= ~EE_CALL_AL_COMPLETE_IO;
		drbd_al_complete_io(device, &peer_req->i);
	पूर्ण

out_पूर्णांकerrupted:
	drbd_may_finish_epoch(connection, peer_req->epoch, EV_PUT | EV_CLEANUP);
	put_ldev(device);
	drbd_मुक्त_peer_req(device, peer_req);
	वापस err;
पूर्ण

/* We may throttle resync, अगर the lower device seems to be busy,
 * and current sync rate is above c_min_rate.
 *
 * To decide whether or not the lower device is busy, we use a scheme similar
 * to MD RAID is_mddev_idle(): अगर the partition stats reveal "significant"
 * (more than 64 sectors) of activity we cannot account क्रम with our own resync
 * activity, it obviously is "busy".
 *
 * The current sync rate used here uses only the most recent two step marks,
 * to have a लघु समय average so we can react faster.
 */
bool drbd_rs_should_slow_करोwn(काष्ठा drbd_device *device, sector_t sector,
		bool throttle_अगर_app_is_रुकोing)
अणु
	काष्ठा lc_element *पंचांगp;
	bool throttle = drbd_rs_c_min_rate_throttle(device);

	अगर (!throttle || throttle_अगर_app_is_रुकोing)
		वापस throttle;

	spin_lock_irq(&device->al_lock);
	पंचांगp = lc_find(device->resync, BM_SECT_TO_EXT(sector));
	अगर (पंचांगp) अणु
		काष्ठा bm_extent *bm_ext = lc_entry(पंचांगp, काष्ठा bm_extent, lce);
		अगर (test_bit(BME_PRIORITY, &bm_ext->flags))
			throttle = false;
		/* Do not slow करोwn अगर app IO is alपढ़ोy रुकोing क्रम this extent,
		 * and our progress is necessary क्रम application IO to complete. */
	पूर्ण
	spin_unlock_irq(&device->al_lock);

	वापस throttle;
पूर्ण

bool drbd_rs_c_min_rate_throttle(काष्ठा drbd_device *device)
अणु
	काष्ठा gendisk *disk = device->ldev->backing_bdev->bd_disk;
	अचिन्हित दीर्घ db, dt, dbdt;
	अचिन्हित पूर्णांक c_min_rate;
	पूर्णांक curr_events;

	rcu_पढ़ो_lock();
	c_min_rate = rcu_dereference(device->ldev->disk_conf)->c_min_rate;
	rcu_पढ़ो_unlock();

	/* feature disabled? */
	अगर (c_min_rate == 0)
		वापस false;

	curr_events = (पूर्णांक)part_stat_पढ़ो_accum(disk->part0, sectors) -
			atomic_पढ़ो(&device->rs_sect_ev);

	अगर (atomic_पढ़ो(&device->ap_actlog_cnt)
	    || curr_events - device->rs_last_events > 64) अणु
		अचिन्हित दीर्घ rs_left;
		पूर्णांक i;

		device->rs_last_events = curr_events;

		/* sync speed average over the last 2*DRBD_SYNC_MARK_STEP,
		 * approx. */
		i = (device->rs_last_mark + DRBD_SYNC_MARKS-1) % DRBD_SYNC_MARKS;

		अगर (device->state.conn == C_VERIFY_S || device->state.conn == C_VERIFY_T)
			rs_left = device->ov_left;
		अन्यथा
			rs_left = drbd_bm_total_weight(device) - device->rs_failed;

		dt = ((दीर्घ)jअगरfies - (दीर्घ)device->rs_mark_समय[i]) / HZ;
		अगर (!dt)
			dt++;
		db = device->rs_mark_left[i] - rs_left;
		dbdt = Bit2KB(db/dt);

		अगर (dbdt > c_min_rate)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक receive_DataRequest(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	sector_t sector;
	sector_t capacity;
	काष्ठा drbd_peer_request *peer_req;
	काष्ठा digest_info *di = शून्य;
	पूर्णांक size, verb;
	अचिन्हित पूर्णांक fault_type;
	काष्ठा p_block_req *p =	pi->data;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;
	capacity = get_capacity(device->vdisk);

	sector = be64_to_cpu(p->sector);
	size   = be32_to_cpu(p->blksize);

	अगर (size <= 0 || !IS_ALIGNED(size, 512) || size > DRBD_MAX_BIO_SIZE) अणु
		drbd_err(device, "%s:%d: sector: %llus, size: %u\n", __खाता__, __LINE__,
				(अचिन्हित दीर्घ दीर्घ)sector, size);
		वापस -EINVAL;
	पूर्ण
	अगर (sector + (size>>9) > capacity) अणु
		drbd_err(device, "%s:%d: sector: %llus, size: %u\n", __खाता__, __LINE__,
				(अचिन्हित दीर्घ दीर्घ)sector, size);
		वापस -EINVAL;
	पूर्ण

	अगर (!get_ldev_अगर_state(device, D_UP_TO_DATE)) अणु
		verb = 1;
		चयन (pi->cmd) अणु
		हाल P_DATA_REQUEST:
			drbd_send_ack_rp(peer_device, P_NEG_DREPLY, p);
			अवरोध;
		हाल P_RS_THIN_REQ:
		हाल P_RS_DATA_REQUEST:
		हाल P_CSUM_RS_REQUEST:
		हाल P_OV_REQUEST:
			drbd_send_ack_rp(peer_device, P_NEG_RS_DREPLY , p);
			अवरोध;
		हाल P_OV_REPLY:
			verb = 0;
			dec_rs_pending(device);
			drbd_send_ack_ex(peer_device, P_OV_RESULT, sector, size, ID_IN_SYNC);
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अगर (verb && __ratelimit(&drbd_ratelimit_state))
			drbd_err(device, "Can not satisfy peer's read request, "
			    "no local data.\n");

		/* drain possibly payload */
		वापस drbd_drain_block(peer_device, pi->size);
	पूर्ण

	/* GFP_NOIO, because we must not cause arbitrary ग_लिखो-out: in a DRBD
	 * "criss-cross" setup, that might cause ग_लिखो-out on some other DRBD,
	 * which in turn might block on the other node at this very place.  */
	peer_req = drbd_alloc_peer_req(peer_device, p->block_id, sector, size,
			size, GFP_NOIO);
	अगर (!peer_req) अणु
		put_ldev(device);
		वापस -ENOMEM;
	पूर्ण

	चयन (pi->cmd) अणु
	हाल P_DATA_REQUEST:
		peer_req->w.cb = w_e_end_data_req;
		fault_type = DRBD_FAULT_DT_RD;
		/* application IO, करोn't drbd_rs_begin_io */
		peer_req->flags |= EE_APPLICATION;
		जाओ submit;

	हाल P_RS_THIN_REQ:
		/* If at some poपूर्णांक in the future we have a smart way to
		   find out अगर this data block is completely deallocated,
		   then we would करो something smarter here than पढ़ोing
		   the block... */
		peer_req->flags |= EE_RS_THIN_REQ;
		fallthrough;
	हाल P_RS_DATA_REQUEST:
		peer_req->w.cb = w_e_end_rsdata_req;
		fault_type = DRBD_FAULT_RS_RD;
		/* used in the sector offset progress display */
		device->bm_resync_fo = BM_SECT_TO_BIT(sector);
		अवरोध;

	हाल P_OV_REPLY:
	हाल P_CSUM_RS_REQUEST:
		fault_type = DRBD_FAULT_RS_RD;
		di = kदो_स्मृति(माप(*di) + pi->size, GFP_NOIO);
		अगर (!di)
			जाओ out_मुक्त_e;

		di->digest_size = pi->size;
		di->digest = (((अक्षर *)di)+माप(काष्ठा digest_info));

		peer_req->digest = di;
		peer_req->flags |= EE_HAS_DIGEST;

		अगर (drbd_recv_all(peer_device->connection, di->digest, pi->size))
			जाओ out_मुक्त_e;

		अगर (pi->cmd == P_CSUM_RS_REQUEST) अणु
			D_ASSERT(device, peer_device->connection->agreed_pro_version >= 89);
			peer_req->w.cb = w_e_end_csum_rs_req;
			/* used in the sector offset progress display */
			device->bm_resync_fo = BM_SECT_TO_BIT(sector);
			/* remember to report stats in drbd_resync_finished */
			device->use_csums = true;
		पूर्ण अन्यथा अगर (pi->cmd == P_OV_REPLY) अणु
			/* track progress, we may need to throttle */
			atomic_add(size >> 9, &device->rs_sect_in);
			peer_req->w.cb = w_e_end_ov_reply;
			dec_rs_pending(device);
			/* drbd_rs_begin_io करोne when we sent this request,
			 * but accounting still needs to be करोne. */
			जाओ submit_क्रम_resync;
		पूर्ण
		अवरोध;

	हाल P_OV_REQUEST:
		अगर (device->ov_start_sector == ~(sector_t)0 &&
		    peer_device->connection->agreed_pro_version >= 90) अणु
			अचिन्हित दीर्घ now = jअगरfies;
			पूर्णांक i;
			device->ov_start_sector = sector;
			device->ov_position = sector;
			device->ov_left = drbd_bm_bits(device) - BM_SECT_TO_BIT(sector);
			device->rs_total = device->ov_left;
			क्रम (i = 0; i < DRBD_SYNC_MARKS; i++) अणु
				device->rs_mark_left[i] = device->ov_left;
				device->rs_mark_समय[i] = now;
			पूर्ण
			drbd_info(device, "Online Verify start sector: %llu\n",
					(अचिन्हित दीर्घ दीर्घ)sector);
		पूर्ण
		peer_req->w.cb = w_e_end_ov_req;
		fault_type = DRBD_FAULT_RS_RD;
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	/* Throttle, drbd_rs_begin_io and submit should become asynchronous
	 * wrt the receiver, but it is not as straightक्रमward as it may seem.
	 * Various places in the resync start and stop logic assume resync
	 * requests are processed in order, requeuing this on the worker thपढ़ो
	 * पूर्णांकroduces a bunch of new code क्रम synchronization between thपढ़ोs.
	 *
	 * Unlimited throttling beक्रमe drbd_rs_begin_io may stall the resync
	 * "forever", throttling after drbd_rs_begin_io will lock that extent
	 * क्रम application ग_लिखोs क्रम the same समय.  For now, just throttle
	 * here, where the rest of the code expects the receiver to sleep क्रम
	 * a जबतक, anyways.
	 */

	/* Throttle beक्रमe drbd_rs_begin_io, as that locks out application IO;
	 * this defers syncer requests क्रम some समय, beक्रमe letting at least
	 * on request through.  The resync controller on the receiving side
	 * will adapt to the incoming rate accordingly.
	 *
	 * We cannot throttle here अगर remote is Primary/SyncTarget:
	 * we would also throttle its application पढ़ोs.
	 * In that हाल, throttling is करोne on the SyncTarget only.
	 */

	/* Even though this may be a resync request, we करो add to "read_ee";
	 * "sync_ee" is only used क्रम resync WRITEs.
	 * Add to list early, so debugfs can find this request
	 * even अगर we have to sleep below. */
	spin_lock_irq(&device->resource->req_lock);
	list_add_tail(&peer_req->w.list, &device->पढ़ो_ee);
	spin_unlock_irq(&device->resource->req_lock);

	update_receiver_timing_details(connection, drbd_rs_should_slow_करोwn);
	अगर (device->state.peer != R_PRIMARY
	&& drbd_rs_should_slow_करोwn(device, sector, false))
		schedule_समयout_unपूर्णांकerruptible(HZ/10);
	update_receiver_timing_details(connection, drbd_rs_begin_io);
	अगर (drbd_rs_begin_io(device, sector))
		जाओ out_मुक्त_e;

submit_क्रम_resync:
	atomic_add(size >> 9, &device->rs_sect_ev);

submit:
	update_receiver_timing_details(connection, drbd_submit_peer_request);
	inc_unacked(device);
	अगर (drbd_submit_peer_request(device, peer_req, REQ_OP_READ, 0,
				     fault_type) == 0)
		वापस 0;

	/* करोn't care क्रम the reason here */
	drbd_err(device, "submit failed, triggering re-connect\n");

out_मुक्त_e:
	spin_lock_irq(&device->resource->req_lock);
	list_del(&peer_req->w.list);
	spin_unlock_irq(&device->resource->req_lock);
	/* no drbd_rs_complete_io(), we are dropping the connection anyways */

	put_ldev(device);
	drbd_मुक्त_peer_req(device, peer_req);
	वापस -EIO;
पूर्ण

/*
 * drbd_asb_recover_0p  -  Recover after split-brain with no reमुख्यing primaries
 */
अटल पूर्णांक drbd_asb_recover_0p(काष्ठा drbd_peer_device *peer_device) __must_hold(local)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	पूर्णांक self, peer, rv = -100;
	अचिन्हित दीर्घ ch_self, ch_peer;
	क्रमागत drbd_after_sb_p after_sb_0p;

	self = device->ldev->md.uuid[UI_BITMAP] & 1;
	peer = device->p_uuid[UI_BITMAP] & 1;

	ch_peer = device->p_uuid[UI_SIZE];
	ch_self = device->comm_bm_set;

	rcu_पढ़ो_lock();
	after_sb_0p = rcu_dereference(peer_device->connection->net_conf)->after_sb_0p;
	rcu_पढ़ो_unlock();
	चयन (after_sb_0p) अणु
	हाल ASB_CONSENSUS:
	हाल ASB_DISCARD_SECONDARY:
	हाल ASB_CALL_HELPER:
	हाल ASB_VIOLENTLY:
		drbd_err(device, "Configuration error.\n");
		अवरोध;
	हाल ASB_DISCONNECT:
		अवरोध;
	हाल ASB_DISCARD_YOUNGER_PRI:
		अगर (self == 0 && peer == 1) अणु
			rv = -1;
			अवरोध;
		पूर्ण
		अगर (self == 1 && peer == 0) अणु
			rv =  1;
			अवरोध;
		पूर्ण
		fallthrough;	/* to one of the other strategies */
	हाल ASB_DISCARD_OLDER_PRI:
		अगर (self == 0 && peer == 1) अणु
			rv = 1;
			अवरोध;
		पूर्ण
		अगर (self == 1 && peer == 0) अणु
			rv = -1;
			अवरोध;
		पूर्ण
		/* Else fall through to one of the other strategies... */
		drbd_warn(device, "Discard younger/older primary did not find a decision\n"
		     "Using discard-least-changes instead\n");
		fallthrough;
	हाल ASB_DISCARD_ZERO_CHG:
		अगर (ch_peer == 0 && ch_self == 0) अणु
			rv = test_bit(RESOLVE_CONFLICTS, &peer_device->connection->flags)
				? -1 : 1;
			अवरोध;
		पूर्ण अन्यथा अणु
			अगर (ch_peer == 0) अणु rv =  1; अवरोध; पूर्ण
			अगर (ch_self == 0) अणु rv = -1; अवरोध; पूर्ण
		पूर्ण
		अगर (after_sb_0p == ASB_DISCARD_ZERO_CHG)
			अवरोध;
		fallthrough;
	हाल ASB_DISCARD_LEAST_CHG:
		अगर	(ch_self < ch_peer)
			rv = -1;
		अन्यथा अगर (ch_self > ch_peer)
			rv =  1;
		अन्यथा /* ( ch_self == ch_peer ) */
		     /* Well, then use something अन्यथा. */
			rv = test_bit(RESOLVE_CONFLICTS, &peer_device->connection->flags)
				? -1 : 1;
		अवरोध;
	हाल ASB_DISCARD_LOCAL:
		rv = -1;
		अवरोध;
	हाल ASB_DISCARD_REMOTE:
		rv =  1;
	पूर्ण

	वापस rv;
पूर्ण

/*
 * drbd_asb_recover_1p  -  Recover after split-brain with one reमुख्यing primary
 */
अटल पूर्णांक drbd_asb_recover_1p(काष्ठा drbd_peer_device *peer_device) __must_hold(local)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	पूर्णांक hg, rv = -100;
	क्रमागत drbd_after_sb_p after_sb_1p;

	rcu_पढ़ो_lock();
	after_sb_1p = rcu_dereference(peer_device->connection->net_conf)->after_sb_1p;
	rcu_पढ़ो_unlock();
	चयन (after_sb_1p) अणु
	हाल ASB_DISCARD_YOUNGER_PRI:
	हाल ASB_DISCARD_OLDER_PRI:
	हाल ASB_DISCARD_LEAST_CHG:
	हाल ASB_DISCARD_LOCAL:
	हाल ASB_DISCARD_REMOTE:
	हाल ASB_DISCARD_ZERO_CHG:
		drbd_err(device, "Configuration error.\n");
		अवरोध;
	हाल ASB_DISCONNECT:
		अवरोध;
	हाल ASB_CONSENSUS:
		hg = drbd_asb_recover_0p(peer_device);
		अगर (hg == -1 && device->state.role == R_SECONDARY)
			rv = hg;
		अगर (hg == 1  && device->state.role == R_PRIMARY)
			rv = hg;
		अवरोध;
	हाल ASB_VIOLENTLY:
		rv = drbd_asb_recover_0p(peer_device);
		अवरोध;
	हाल ASB_DISCARD_SECONDARY:
		वापस device->state.role == R_PRIMARY ? 1 : -1;
	हाल ASB_CALL_HELPER:
		hg = drbd_asb_recover_0p(peer_device);
		अगर (hg == -1 && device->state.role == R_PRIMARY) अणु
			क्रमागत drbd_state_rv rv2;

			 /* drbd_change_state() करोes not sleep जबतक in SS_IN_TRANSIENT_STATE,
			  * we might be here in C_WF_REPORT_PARAMS which is transient.
			  * we करो not need to रुको क्रम the after state change work either. */
			rv2 = drbd_change_state(device, CS_VERBOSE, NS(role, R_SECONDARY));
			अगर (rv2 != SS_SUCCESS) अणु
				drbd_khelper(device, "pri-lost-after-sb");
			पूर्ण अन्यथा अणु
				drbd_warn(device, "Successfully gave up primary role.\n");
				rv = hg;
			पूर्ण
		पूर्ण अन्यथा
			rv = hg;
	पूर्ण

	वापस rv;
पूर्ण

/*
 * drbd_asb_recover_2p  -  Recover after split-brain with two reमुख्यing primaries
 */
अटल पूर्णांक drbd_asb_recover_2p(काष्ठा drbd_peer_device *peer_device) __must_hold(local)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	पूर्णांक hg, rv = -100;
	क्रमागत drbd_after_sb_p after_sb_2p;

	rcu_पढ़ो_lock();
	after_sb_2p = rcu_dereference(peer_device->connection->net_conf)->after_sb_2p;
	rcu_पढ़ो_unlock();
	चयन (after_sb_2p) अणु
	हाल ASB_DISCARD_YOUNGER_PRI:
	हाल ASB_DISCARD_OLDER_PRI:
	हाल ASB_DISCARD_LEAST_CHG:
	हाल ASB_DISCARD_LOCAL:
	हाल ASB_DISCARD_REMOTE:
	हाल ASB_CONSENSUS:
	हाल ASB_DISCARD_SECONDARY:
	हाल ASB_DISCARD_ZERO_CHG:
		drbd_err(device, "Configuration error.\n");
		अवरोध;
	हाल ASB_VIOLENTLY:
		rv = drbd_asb_recover_0p(peer_device);
		अवरोध;
	हाल ASB_DISCONNECT:
		अवरोध;
	हाल ASB_CALL_HELPER:
		hg = drbd_asb_recover_0p(peer_device);
		अगर (hg == -1) अणु
			क्रमागत drbd_state_rv rv2;

			 /* drbd_change_state() करोes not sleep जबतक in SS_IN_TRANSIENT_STATE,
			  * we might be here in C_WF_REPORT_PARAMS which is transient.
			  * we करो not need to रुको क्रम the after state change work either. */
			rv2 = drbd_change_state(device, CS_VERBOSE, NS(role, R_SECONDARY));
			अगर (rv2 != SS_SUCCESS) अणु
				drbd_khelper(device, "pri-lost-after-sb");
			पूर्ण अन्यथा अणु
				drbd_warn(device, "Successfully gave up primary role.\n");
				rv = hg;
			पूर्ण
		पूर्ण अन्यथा
			rv = hg;
	पूर्ण

	वापस rv;
पूर्ण

अटल व्योम drbd_uuid_dump(काष्ठा drbd_device *device, अक्षर *text, u64 *uuid,
			   u64 bits, u64 flags)
अणु
	अगर (!uuid) अणु
		drbd_info(device, "%s uuid info vanished while I was looking!\n", text);
		वापस;
	पूर्ण
	drbd_info(device, "%s %016llX:%016llX:%016llX:%016llX bits:%llu flags:%llX\n",
	     text,
	     (अचिन्हित दीर्घ दीर्घ)uuid[UI_CURRENT],
	     (अचिन्हित दीर्घ दीर्घ)uuid[UI_BITMAP],
	     (अचिन्हित दीर्घ दीर्घ)uuid[UI_HISTORY_START],
	     (अचिन्हित दीर्घ दीर्घ)uuid[UI_HISTORY_END],
	     (अचिन्हित दीर्घ दीर्घ)bits,
	     (अचिन्हित दीर्घ दीर्घ)flags);
पूर्ण

/*
  100	after split brain try स्वतः recover
    2	C_SYNC_SOURCE set BitMap
    1	C_SYNC_SOURCE use BitMap
    0	no Sync
   -1	C_SYNC_TARGET use BitMap
   -2	C_SYNC_TARGET set BitMap
 -100	after split brain, disconnect
-1000	unrelated data
-1091   requires proto 91
-1096   requires proto 96
 */

अटल पूर्णांक drbd_uuid_compare(काष्ठा drbd_device *स्थिर device, क्रमागत drbd_role स्थिर peer_role, पूर्णांक *rule_nr) __must_hold(local)
अणु
	काष्ठा drbd_peer_device *स्थिर peer_device = first_peer_device(device);
	काष्ठा drbd_connection *स्थिर connection = peer_device ? peer_device->connection : शून्य;
	u64 self, peer;
	पूर्णांक i, j;

	self = device->ldev->md.uuid[UI_CURRENT] & ~((u64)1);
	peer = device->p_uuid[UI_CURRENT] & ~((u64)1);

	*rule_nr = 10;
	अगर (self == UUID_JUST_CREATED && peer == UUID_JUST_CREATED)
		वापस 0;

	*rule_nr = 20;
	अगर ((self == UUID_JUST_CREATED || self == (u64)0) &&
	     peer != UUID_JUST_CREATED)
		वापस -2;

	*rule_nr = 30;
	अगर (self != UUID_JUST_CREATED &&
	    (peer == UUID_JUST_CREATED || peer == (u64)0))
		वापस 2;

	अगर (self == peer) अणु
		पूर्णांक rct, dc; /* roles at crash समय */

		अगर (device->p_uuid[UI_BITMAP] == (u64)0 && device->ldev->md.uuid[UI_BITMAP] != (u64)0) अणु

			अगर (connection->agreed_pro_version < 91)
				वापस -1091;

			अगर ((device->ldev->md.uuid[UI_BITMAP] & ~((u64)1)) == (device->p_uuid[UI_HISTORY_START] & ~((u64)1)) &&
			    (device->ldev->md.uuid[UI_HISTORY_START] & ~((u64)1)) == (device->p_uuid[UI_HISTORY_START + 1] & ~((u64)1))) अणु
				drbd_info(device, "was SyncSource, missed the resync finished event, corrected myself:\n");
				drbd_uuid_move_history(device);
				device->ldev->md.uuid[UI_HISTORY_START] = device->ldev->md.uuid[UI_BITMAP];
				device->ldev->md.uuid[UI_BITMAP] = 0;

				drbd_uuid_dump(device, "self", device->ldev->md.uuid,
					       device->state.disk >= D_NEGOTIATING ? drbd_bm_total_weight(device) : 0, 0);
				*rule_nr = 34;
			पूर्ण अन्यथा अणु
				drbd_info(device, "was SyncSource (peer failed to write sync_uuid)\n");
				*rule_nr = 36;
			पूर्ण

			वापस 1;
		पूर्ण

		अगर (device->ldev->md.uuid[UI_BITMAP] == (u64)0 && device->p_uuid[UI_BITMAP] != (u64)0) अणु

			अगर (connection->agreed_pro_version < 91)
				वापस -1091;

			अगर ((device->ldev->md.uuid[UI_HISTORY_START] & ~((u64)1)) == (device->p_uuid[UI_BITMAP] & ~((u64)1)) &&
			    (device->ldev->md.uuid[UI_HISTORY_START + 1] & ~((u64)1)) == (device->p_uuid[UI_HISTORY_START] & ~((u64)1))) अणु
				drbd_info(device, "was SyncTarget, peer missed the resync finished event, corrected peer:\n");

				device->p_uuid[UI_HISTORY_START + 1] = device->p_uuid[UI_HISTORY_START];
				device->p_uuid[UI_HISTORY_START] = device->p_uuid[UI_BITMAP];
				device->p_uuid[UI_BITMAP] = 0UL;

				drbd_uuid_dump(device, "peer", device->p_uuid, device->p_uuid[UI_SIZE], device->p_uuid[UI_FLAGS]);
				*rule_nr = 35;
			पूर्ण अन्यथा अणु
				drbd_info(device, "was SyncTarget (failed to write sync_uuid)\n");
				*rule_nr = 37;
			पूर्ण

			वापस -1;
		पूर्ण

		/* Common घातer [off|failure] */
		rct = (test_bit(CRASHED_PRIMARY, &device->flags) ? 1 : 0) +
			(device->p_uuid[UI_FLAGS] & 2);
		/* lowest bit is set when we were primary,
		 * next bit (weight 2) is set when peer was primary */
		*rule_nr = 40;

		/* Neither has the "crashed primary" flag set,
		 * only a replication link hickup. */
		अगर (rct == 0)
			वापस 0;

		/* Current UUID equal and no biपंचांगap uuid; करोes not necessarily
		 * mean this was a "simultaneous hard crash", maybe IO was
		 * frozen, so no UUID-bump happened.
		 * This is a protocol change, overload DRBD_FF_WSAME as flag
		 * क्रम "new-enough" peer DRBD version. */
		अगर (device->state.role == R_PRIMARY || peer_role == R_PRIMARY) अणु
			*rule_nr = 41;
			अगर (!(connection->agreed_features & DRBD_FF_WSAME)) अणु
				drbd_warn(peer_device, "Equivalent unrotated UUIDs, but current primary present.\n");
				वापस -(0x10000 | PRO_VERSION_MAX | (DRBD_FF_WSAME << 8));
			पूर्ण
			अगर (device->state.role == R_PRIMARY && peer_role == R_PRIMARY) अणु
				/* At least one has the "crashed primary" bit set,
				 * both are primary now, but neither has rotated its UUIDs?
				 * "Can not happen." */
				drbd_err(peer_device, "Equivalent unrotated UUIDs, but both are primary. Can not resolve this.\n");
				वापस -100;
			पूर्ण
			अगर (device->state.role == R_PRIMARY)
				वापस 1;
			वापस -1;
		पूर्ण

		/* Both are secondary.
		 * Really looks like recovery from simultaneous hard crash.
		 * Check which had been primary beक्रमe, and arbitrate. */
		चयन (rct) अणु
		हाल 0: /* !self_pri && !peer_pri */ वापस 0; /* alपढ़ोy handled */
		हाल 1: /*  self_pri && !peer_pri */ वापस 1;
		हाल 2: /* !self_pri &&  peer_pri */ वापस -1;
		हाल 3: /*  self_pri &&  peer_pri */
			dc = test_bit(RESOLVE_CONFLICTS, &connection->flags);
			वापस dc ? -1 : 1;
		पूर्ण
	पूर्ण

	*rule_nr = 50;
	peer = device->p_uuid[UI_BITMAP] & ~((u64)1);
	अगर (self == peer)
		वापस -1;

	*rule_nr = 51;
	peer = device->p_uuid[UI_HISTORY_START] & ~((u64)1);
	अगर (self == peer) अणु
		अगर (connection->agreed_pro_version < 96 ?
		    (device->ldev->md.uuid[UI_HISTORY_START] & ~((u64)1)) ==
		    (device->p_uuid[UI_HISTORY_START + 1] & ~((u64)1)) :
		    peer + UUID_NEW_BM_OFFSET == (device->p_uuid[UI_BITMAP] & ~((u64)1))) अणु
			/* The last P_SYNC_UUID did not get though. Unकरो the last start of
			   resync as sync source modअगरications of the peer's UUIDs. */

			अगर (connection->agreed_pro_version < 91)
				वापस -1091;

			device->p_uuid[UI_BITMAP] = device->p_uuid[UI_HISTORY_START];
			device->p_uuid[UI_HISTORY_START] = device->p_uuid[UI_HISTORY_START + 1];

			drbd_info(device, "Lost last syncUUID packet, corrected:\n");
			drbd_uuid_dump(device, "peer", device->p_uuid, device->p_uuid[UI_SIZE], device->p_uuid[UI_FLAGS]);

			वापस -1;
		पूर्ण
	पूर्ण

	*rule_nr = 60;
	self = device->ldev->md.uuid[UI_CURRENT] & ~((u64)1);
	क्रम (i = UI_HISTORY_START; i <= UI_HISTORY_END; i++) अणु
		peer = device->p_uuid[i] & ~((u64)1);
		अगर (self == peer)
			वापस -2;
	पूर्ण

	*rule_nr = 70;
	self = device->ldev->md.uuid[UI_BITMAP] & ~((u64)1);
	peer = device->p_uuid[UI_CURRENT] & ~((u64)1);
	अगर (self == peer)
		वापस 1;

	*rule_nr = 71;
	self = device->ldev->md.uuid[UI_HISTORY_START] & ~((u64)1);
	अगर (self == peer) अणु
		अगर (connection->agreed_pro_version < 96 ?
		    (device->ldev->md.uuid[UI_HISTORY_START + 1] & ~((u64)1)) ==
		    (device->p_uuid[UI_HISTORY_START] & ~((u64)1)) :
		    self + UUID_NEW_BM_OFFSET == (device->ldev->md.uuid[UI_BITMAP] & ~((u64)1))) अणु
			/* The last P_SYNC_UUID did not get though. Unकरो the last start of
			   resync as sync source modअगरications of our UUIDs. */

			अगर (connection->agreed_pro_version < 91)
				वापस -1091;

			__drbd_uuid_set(device, UI_BITMAP, device->ldev->md.uuid[UI_HISTORY_START]);
			__drbd_uuid_set(device, UI_HISTORY_START, device->ldev->md.uuid[UI_HISTORY_START + 1]);

			drbd_info(device, "Last syncUUID did not get through, corrected:\n");
			drbd_uuid_dump(device, "self", device->ldev->md.uuid,
				       device->state.disk >= D_NEGOTIATING ? drbd_bm_total_weight(device) : 0, 0);

			वापस 1;
		पूर्ण
	पूर्ण


	*rule_nr = 80;
	peer = device->p_uuid[UI_CURRENT] & ~((u64)1);
	क्रम (i = UI_HISTORY_START; i <= UI_HISTORY_END; i++) अणु
		self = device->ldev->md.uuid[i] & ~((u64)1);
		अगर (self == peer)
			वापस 2;
	पूर्ण

	*rule_nr = 90;
	self = device->ldev->md.uuid[UI_BITMAP] & ~((u64)1);
	peer = device->p_uuid[UI_BITMAP] & ~((u64)1);
	अगर (self == peer && self != ((u64)0))
		वापस 100;

	*rule_nr = 100;
	क्रम (i = UI_HISTORY_START; i <= UI_HISTORY_END; i++) अणु
		self = device->ldev->md.uuid[i] & ~((u64)1);
		क्रम (j = UI_HISTORY_START; j <= UI_HISTORY_END; j++) अणु
			peer = device->p_uuid[j] & ~((u64)1);
			अगर (self == peer)
				वापस -100;
		पूर्ण
	पूर्ण

	वापस -1000;
पूर्ण

/* drbd_sync_handshake() वापसs the new conn state on success, or
   CONN_MASK (-1) on failure.
 */
अटल क्रमागत drbd_conns drbd_sync_handshake(काष्ठा drbd_peer_device *peer_device,
					   क्रमागत drbd_role peer_role,
					   क्रमागत drbd_disk_state peer_disk) __must_hold(local)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	क्रमागत drbd_conns rv = C_MASK;
	क्रमागत drbd_disk_state mydisk;
	काष्ठा net_conf *nc;
	पूर्णांक hg, rule_nr, rr_conflict, tentative, always_asbp;

	mydisk = device->state.disk;
	अगर (mydisk == D_NEGOTIATING)
		mydisk = device->new_state_पंचांगp.disk;

	drbd_info(device, "drbd_sync_handshake:\n");

	spin_lock_irq(&device->ldev->md.uuid_lock);
	drbd_uuid_dump(device, "self", device->ldev->md.uuid, device->comm_bm_set, 0);
	drbd_uuid_dump(device, "peer", device->p_uuid,
		       device->p_uuid[UI_SIZE], device->p_uuid[UI_FLAGS]);

	hg = drbd_uuid_compare(device, peer_role, &rule_nr);
	spin_unlock_irq(&device->ldev->md.uuid_lock);

	drbd_info(device, "uuid_compare()=%d by rule %d\n", hg, rule_nr);

	अगर (hg == -1000) अणु
		drbd_alert(device, "Unrelated data, aborting!\n");
		वापस C_MASK;
	पूर्ण
	अगर (hg < -0x10000) अणु
		पूर्णांक proto, fflags;
		hg = -hg;
		proto = hg & 0xff;
		fflags = (hg >> 8) & 0xff;
		drbd_alert(device, "To resolve this both sides have to support at least protocol %d and feature flags 0x%x\n",
					proto, fflags);
		वापस C_MASK;
	पूर्ण
	अगर (hg < -1000) अणु
		drbd_alert(device, "To resolve this both sides have to support at least protocol %d\n", -hg - 1000);
		वापस C_MASK;
	पूर्ण

	अगर    ((mydisk == D_INCONSISTENT && peer_disk > D_INCONSISTENT) ||
	    (peer_disk == D_INCONSISTENT && mydisk    > D_INCONSISTENT)) अणु
		पूर्णांक f = (hg == -100) || असल(hg) == 2;
		hg = mydisk > D_INCONSISTENT ? 1 : -1;
		अगर (f)
			hg = hg*2;
		drbd_info(device, "Becoming sync %s due to disk states.\n",
		     hg > 0 ? "source" : "target");
	पूर्ण

	अगर (असल(hg) == 100)
		drbd_khelper(device, "initial-split-brain");

	rcu_पढ़ो_lock();
	nc = rcu_dereference(peer_device->connection->net_conf);
	always_asbp = nc->always_asbp;
	rr_conflict = nc->rr_conflict;
	tentative = nc->tentative;
	rcu_पढ़ो_unlock();

	अगर (hg == 100 || (hg == -100 && always_asbp)) अणु
		पूर्णांक pcount = (device->state.role == R_PRIMARY)
			   + (peer_role == R_PRIMARY);
		पूर्णांक क्रमced = (hg == -100);

		चयन (pcount) अणु
		हाल 0:
			hg = drbd_asb_recover_0p(peer_device);
			अवरोध;
		हाल 1:
			hg = drbd_asb_recover_1p(peer_device);
			अवरोध;
		हाल 2:
			hg = drbd_asb_recover_2p(peer_device);
			अवरोध;
		पूर्ण
		अगर (असल(hg) < 100) अणु
			drbd_warn(device, "Split-Brain detected, %d primaries, "
			     "automatically solved. Sync from %s node\n",
			     pcount, (hg < 0) ? "peer" : "this");
			अगर (क्रमced) अणु
				drbd_warn(device, "Doing a full sync, since"
				     " UUIDs where ambiguous.\n");
				hg = hg*2;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (hg == -100) अणु
		अगर (test_bit(DISCARD_MY_DATA, &device->flags) && !(device->p_uuid[UI_FLAGS]&1))
			hg = -1;
		अगर (!test_bit(DISCARD_MY_DATA, &device->flags) && (device->p_uuid[UI_FLAGS]&1))
			hg = 1;

		अगर (असल(hg) < 100)
			drbd_warn(device, "Split-Brain detected, manually solved. "
			     "Sync from %s node\n",
			     (hg < 0) ? "peer" : "this");
	पूर्ण

	अगर (hg == -100) अणु
		/* FIXME this log message is not correct अगर we end up here
		 * after an attempted attach on a diskless node.
		 * We just refuse to attach -- well, we drop the "connection"
		 * to that disk, in a way... */
		drbd_alert(device, "Split-Brain detected but unresolved, dropping connection!\n");
		drbd_khelper(device, "split-brain");
		वापस C_MASK;
	पूर्ण

	अगर (hg > 0 && mydisk <= D_INCONSISTENT) अणु
		drbd_err(device, "I shall become SyncSource, but I am inconsistent!\n");
		वापस C_MASK;
	पूर्ण

	अगर (hg < 0 && /* by पूर्णांकention we करो not use mydisk here. */
	    device->state.role == R_PRIMARY && device->state.disk >= D_CONSISTENT) अणु
		चयन (rr_conflict) अणु
		हाल ASB_CALL_HELPER:
			drbd_khelper(device, "pri-lost");
			fallthrough;
		हाल ASB_DISCONNECT:
			drbd_err(device, "I shall become SyncTarget, but I am primary!\n");
			वापस C_MASK;
		हाल ASB_VIOLENTLY:
			drbd_warn(device, "Becoming SyncTarget, violating the stable-data"
			     "assumption\n");
		पूर्ण
	पूर्ण

	अगर (tentative || test_bit(CONN_DRY_RUN, &peer_device->connection->flags)) अणु
		अगर (hg == 0)
			drbd_info(device, "dry-run connect: No resync, would become Connected immediately.\n");
		अन्यथा
			drbd_info(device, "dry-run connect: Would become %s, doing a %s resync.",
				 drbd_conn_str(hg > 0 ? C_SYNC_SOURCE : C_SYNC_TARGET),
				 असल(hg) >= 2 ? "full" : "bit-map based");
		वापस C_MASK;
	पूर्ण

	अगर (असल(hg) >= 2) अणु
		drbd_info(device, "Writing the whole bitmap, full sync required after drbd_sync_handshake.\n");
		अगर (drbd_biपंचांगap_io(device, &drbd_bmio_set_n_ग_लिखो, "set_n_write from sync_handshake",
					BM_LOCKED_SET_ALLOWED))
			वापस C_MASK;
	पूर्ण

	अगर (hg > 0) अणु /* become sync source. */
		rv = C_WF_BITMAP_S;
	पूर्ण अन्यथा अगर (hg < 0) अणु /* become sync target */
		rv = C_WF_BITMAP_T;
	पूर्ण अन्यथा अणु
		rv = C_CONNECTED;
		अगर (drbd_bm_total_weight(device)) अणु
			drbd_info(device, "No resync, but %lu bits in bitmap!\n",
			     drbd_bm_total_weight(device));
		पूर्ण
	पूर्ण

	वापस rv;
पूर्ण

अटल क्रमागत drbd_after_sb_p convert_after_sb(क्रमागत drbd_after_sb_p peer)
अणु
	/* ASB_DISCARD_REMOTE - ASB_DISCARD_LOCAL is valid */
	अगर (peer == ASB_DISCARD_REMOTE)
		वापस ASB_DISCARD_LOCAL;

	/* any other things with ASB_DISCARD_REMOTE or ASB_DISCARD_LOCAL are invalid */
	अगर (peer == ASB_DISCARD_LOCAL)
		वापस ASB_DISCARD_REMOTE;

	/* everything अन्यथा is valid अगर they are equal on both sides. */
	वापस peer;
पूर्ण

अटल पूर्णांक receive_protocol(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा p_protocol *p = pi->data;
	क्रमागत drbd_after_sb_p p_after_sb_0p, p_after_sb_1p, p_after_sb_2p;
	पूर्णांक p_proto, p_discard_my_data, p_two_primaries, cf;
	काष्ठा net_conf *nc, *old_net_conf, *new_net_conf = शून्य;
	अक्षर पूर्णांकegrity_alg[SHARED_SECRET_MAX] = "";
	काष्ठा crypto_shash *peer_पूर्णांकegrity_tfm = शून्य;
	व्योम *पूर्णांक_dig_in = शून्य, *पूर्णांक_dig_vv = शून्य;

	p_proto		= be32_to_cpu(p->protocol);
	p_after_sb_0p	= be32_to_cpu(p->after_sb_0p);
	p_after_sb_1p	= be32_to_cpu(p->after_sb_1p);
	p_after_sb_2p	= be32_to_cpu(p->after_sb_2p);
	p_two_primaries = be32_to_cpu(p->two_primaries);
	cf		= be32_to_cpu(p->conn_flags);
	p_discard_my_data = cf & CF_DISCARD_MY_DATA;

	अगर (connection->agreed_pro_version >= 87) अणु
		पूर्णांक err;

		अगर (pi->size > माप(पूर्णांकegrity_alg))
			वापस -EIO;
		err = drbd_recv_all(connection, पूर्णांकegrity_alg, pi->size);
		अगर (err)
			वापस err;
		पूर्णांकegrity_alg[SHARED_SECRET_MAX - 1] = 0;
	पूर्ण

	अगर (pi->cmd != P_PROTOCOL_UPDATE) अणु
		clear_bit(CONN_DRY_RUN, &connection->flags);

		अगर (cf & CF_DRY_RUN)
			set_bit(CONN_DRY_RUN, &connection->flags);

		rcu_पढ़ो_lock();
		nc = rcu_dereference(connection->net_conf);

		अगर (p_proto != nc->wire_protocol) अणु
			drbd_err(connection, "incompatible %s settings\n", "protocol");
			जाओ disconnect_rcu_unlock;
		पूर्ण

		अगर (convert_after_sb(p_after_sb_0p) != nc->after_sb_0p) अणु
			drbd_err(connection, "incompatible %s settings\n", "after-sb-0pri");
			जाओ disconnect_rcu_unlock;
		पूर्ण

		अगर (convert_after_sb(p_after_sb_1p) != nc->after_sb_1p) अणु
			drbd_err(connection, "incompatible %s settings\n", "after-sb-1pri");
			जाओ disconnect_rcu_unlock;
		पूर्ण

		अगर (convert_after_sb(p_after_sb_2p) != nc->after_sb_2p) अणु
			drbd_err(connection, "incompatible %s settings\n", "after-sb-2pri");
			जाओ disconnect_rcu_unlock;
		पूर्ण

		अगर (p_discard_my_data && nc->discard_my_data) अणु
			drbd_err(connection, "incompatible %s settings\n", "discard-my-data");
			जाओ disconnect_rcu_unlock;
		पूर्ण

		अगर (p_two_primaries != nc->two_primaries) अणु
			drbd_err(connection, "incompatible %s settings\n", "allow-two-primaries");
			जाओ disconnect_rcu_unlock;
		पूर्ण

		अगर (म_भेद(पूर्णांकegrity_alg, nc->पूर्णांकegrity_alg)) अणु
			drbd_err(connection, "incompatible %s settings\n", "data-integrity-alg");
			जाओ disconnect_rcu_unlock;
		पूर्ण

		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (पूर्णांकegrity_alg[0]) अणु
		पूर्णांक hash_size;

		/*
		 * We can only change the peer data पूर्णांकegrity algorithm
		 * here.  Changing our own data पूर्णांकegrity algorithm
		 * requires that we send a P_PROTOCOL_UPDATE packet at
		 * the same समय; otherwise, the peer has no way to
		 * tell between which packets the algorithm should
		 * change.
		 */

		peer_पूर्णांकegrity_tfm = crypto_alloc_shash(पूर्णांकegrity_alg, 0, 0);
		अगर (IS_ERR(peer_पूर्णांकegrity_tfm)) अणु
			peer_पूर्णांकegrity_tfm = शून्य;
			drbd_err(connection, "peer data-integrity-alg %s not supported\n",
				 पूर्णांकegrity_alg);
			जाओ disconnect;
		पूर्ण

		hash_size = crypto_shash_digestsize(peer_पूर्णांकegrity_tfm);
		पूर्णांक_dig_in = kदो_स्मृति(hash_size, GFP_KERNEL);
		पूर्णांक_dig_vv = kदो_स्मृति(hash_size, GFP_KERNEL);
		अगर (!(पूर्णांक_dig_in && पूर्णांक_dig_vv)) अणु
			drbd_err(connection, "Allocation of buffers for data integrity checking failed\n");
			जाओ disconnect;
		पूर्ण
	पूर्ण

	new_net_conf = kदो_स्मृति(माप(काष्ठा net_conf), GFP_KERNEL);
	अगर (!new_net_conf) अणु
		drbd_err(connection, "Allocation of new net_conf failed\n");
		जाओ disconnect;
	पूर्ण

	mutex_lock(&connection->data.mutex);
	mutex_lock(&connection->resource->conf_update);
	old_net_conf = connection->net_conf;
	*new_net_conf = *old_net_conf;

	new_net_conf->wire_protocol = p_proto;
	new_net_conf->after_sb_0p = convert_after_sb(p_after_sb_0p);
	new_net_conf->after_sb_1p = convert_after_sb(p_after_sb_1p);
	new_net_conf->after_sb_2p = convert_after_sb(p_after_sb_2p);
	new_net_conf->two_primaries = p_two_primaries;

	rcu_assign_poपूर्णांकer(connection->net_conf, new_net_conf);
	mutex_unlock(&connection->resource->conf_update);
	mutex_unlock(&connection->data.mutex);

	crypto_मुक्त_shash(connection->peer_पूर्णांकegrity_tfm);
	kमुक्त(connection->पूर्णांक_dig_in);
	kमुक्त(connection->पूर्णांक_dig_vv);
	connection->peer_पूर्णांकegrity_tfm = peer_पूर्णांकegrity_tfm;
	connection->पूर्णांक_dig_in = पूर्णांक_dig_in;
	connection->पूर्णांक_dig_vv = पूर्णांक_dig_vv;

	अगर (म_भेद(old_net_conf->पूर्णांकegrity_alg, पूर्णांकegrity_alg))
		drbd_info(connection, "peer data-integrity-alg: %s\n",
			  पूर्णांकegrity_alg[0] ? पूर्णांकegrity_alg : "(none)");

	synchronize_rcu();
	kमुक्त(old_net_conf);
	वापस 0;

disconnect_rcu_unlock:
	rcu_पढ़ो_unlock();
disconnect:
	crypto_मुक्त_shash(peer_पूर्णांकegrity_tfm);
	kमुक्त(पूर्णांक_dig_in);
	kमुक्त(पूर्णांक_dig_vv);
	conn_request_state(connection, NS(conn, C_DISCONNECTING), CS_HARD);
	वापस -EIO;
पूर्ण

/* helper function
 * input: alg name, feature name
 * वापस: शून्य (alg name was "")
 *         ERR_PTR(error) अगर something goes wrong
 *         or the crypto hash ptr, अगर it worked out ok. */
अटल काष्ठा crypto_shash *drbd_crypto_alloc_digest_safe(
		स्थिर काष्ठा drbd_device *device,
		स्थिर अक्षर *alg, स्थिर अक्षर *name)
अणु
	काष्ठा crypto_shash *tfm;

	अगर (!alg[0])
		वापस शून्य;

	tfm = crypto_alloc_shash(alg, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		drbd_err(device, "Can not allocate \"%s\" as %s (reason: %ld)\n",
			alg, name, PTR_ERR(tfm));
		वापस tfm;
	पूर्ण
	वापस tfm;
पूर्ण

अटल पूर्णांक ignore_reमुख्यing_packet(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	व्योम *buffer = connection->data.rbuf;
	पूर्णांक size = pi->size;

	जबतक (size) अणु
		पूर्णांक s = min_t(पूर्णांक, size, DRBD_SOCKET_BUFFER_SIZE);
		s = drbd_recv(connection, buffer, s);
		अगर (s <= 0) अणु
			अगर (s < 0)
				वापस s;
			अवरोध;
		पूर्ण
		size -= s;
	पूर्ण
	अगर (size)
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * config_unknown_volume  -  device configuration command क्रम unknown volume
 *
 * When a device is added to an existing connection, the node on which the
 * device is added first will send configuration commands to its peer but the
 * peer will not know about the device yet.  It will warn and ignore these
 * commands.  Once the device is added on the second node, the second node will
 * send the same device configuration commands, but in the other direction.
 *
 * (We can also end up here अगर drbd is misconfigured.)
 */
अटल पूर्णांक config_unknown_volume(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	drbd_warn(connection, "%s packet received for volume %u, which is not configured locally\n",
		  cmdname(pi->cmd), pi->vnr);
	वापस ignore_reमुख्यing_packet(connection, pi);
पूर्ण

अटल पूर्णांक receive_SyncParam(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_rs_param_95 *p;
	अचिन्हित पूर्णांक header_size, data_size, exp_max_sz;
	काष्ठा crypto_shash *verअगरy_tfm = शून्य;
	काष्ठा crypto_shash *csums_tfm = शून्य;
	काष्ठा net_conf *old_net_conf, *new_net_conf = शून्य;
	काष्ठा disk_conf *old_disk_conf = शून्य, *new_disk_conf = शून्य;
	स्थिर पूर्णांक apv = connection->agreed_pro_version;
	काष्ठा fअगरo_buffer *old_plan = शून्य, *new_plan = शून्य;
	अचिन्हित पूर्णांक fअगरo_size = 0;
	पूर्णांक err;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस config_unknown_volume(connection, pi);
	device = peer_device->device;

	exp_max_sz  = apv <= 87 ? माप(काष्ठा p_rs_param)
		    : apv == 88 ? माप(काष्ठा p_rs_param)
					+ SHARED_SECRET_MAX
		    : apv <= 94 ? माप(काष्ठा p_rs_param_89)
		    : /* apv >= 95 */ माप(काष्ठा p_rs_param_95);

	अगर (pi->size > exp_max_sz) अणु
		drbd_err(device, "SyncParam packet too long: received %u, expected <= %u bytes\n",
		    pi->size, exp_max_sz);
		वापस -EIO;
	पूर्ण

	अगर (apv <= 88) अणु
		header_size = माप(काष्ठा p_rs_param);
		data_size = pi->size - header_size;
	पूर्ण अन्यथा अगर (apv <= 94) अणु
		header_size = माप(काष्ठा p_rs_param_89);
		data_size = pi->size - header_size;
		D_ASSERT(device, data_size == 0);
	पूर्ण अन्यथा अणु
		header_size = माप(काष्ठा p_rs_param_95);
		data_size = pi->size - header_size;
		D_ASSERT(device, data_size == 0);
	पूर्ण

	/* initialize verअगरy_alg and csums_alg */
	p = pi->data;
	स_रखो(p->verअगरy_alg, 0, 2 * SHARED_SECRET_MAX);

	err = drbd_recv_all(peer_device->connection, p, header_size);
	अगर (err)
		वापस err;

	mutex_lock(&connection->resource->conf_update);
	old_net_conf = peer_device->connection->net_conf;
	अगर (get_ldev(device)) अणु
		new_disk_conf = kzalloc(माप(काष्ठा disk_conf), GFP_KERNEL);
		अगर (!new_disk_conf) अणु
			put_ldev(device);
			mutex_unlock(&connection->resource->conf_update);
			drbd_err(device, "Allocation of new disk_conf failed\n");
			वापस -ENOMEM;
		पूर्ण

		old_disk_conf = device->ldev->disk_conf;
		*new_disk_conf = *old_disk_conf;

		new_disk_conf->resync_rate = be32_to_cpu(p->resync_rate);
	पूर्ण

	अगर (apv >= 88) अणु
		अगर (apv == 88) अणु
			अगर (data_size > SHARED_SECRET_MAX || data_size == 0) अणु
				drbd_err(device, "verify-alg of wrong size, "
					"peer wants %u, accepting only up to %u byte\n",
					data_size, SHARED_SECRET_MAX);
				err = -EIO;
				जाओ reconnect;
			पूर्ण

			err = drbd_recv_all(peer_device->connection, p->verअगरy_alg, data_size);
			अगर (err)
				जाओ reconnect;
			/* we expect NUL terminated string */
			/* but just in हाल someone tries to be evil */
			D_ASSERT(device, p->verअगरy_alg[data_size-1] == 0);
			p->verअगरy_alg[data_size-1] = 0;

		पूर्ण अन्यथा /* apv >= 89 */ अणु
			/* we still expect NUL terminated strings */
			/* but just in हाल someone tries to be evil */
			D_ASSERT(device, p->verअगरy_alg[SHARED_SECRET_MAX-1] == 0);
			D_ASSERT(device, p->csums_alg[SHARED_SECRET_MAX-1] == 0);
			p->verअगरy_alg[SHARED_SECRET_MAX-1] = 0;
			p->csums_alg[SHARED_SECRET_MAX-1] = 0;
		पूर्ण

		अगर (म_भेद(old_net_conf->verअगरy_alg, p->verअगरy_alg)) अणु
			अगर (device->state.conn == C_WF_REPORT_PARAMS) अणु
				drbd_err(device, "Different verify-alg settings. me=\"%s\" peer=\"%s\"\n",
				    old_net_conf->verअगरy_alg, p->verअगरy_alg);
				जाओ disconnect;
			पूर्ण
			verअगरy_tfm = drbd_crypto_alloc_digest_safe(device,
					p->verअगरy_alg, "verify-alg");
			अगर (IS_ERR(verअगरy_tfm)) अणु
				verअगरy_tfm = शून्य;
				जाओ disconnect;
			पूर्ण
		पूर्ण

		अगर (apv >= 89 && म_भेद(old_net_conf->csums_alg, p->csums_alg)) अणु
			अगर (device->state.conn == C_WF_REPORT_PARAMS) अणु
				drbd_err(device, "Different csums-alg settings. me=\"%s\" peer=\"%s\"\n",
				    old_net_conf->csums_alg, p->csums_alg);
				जाओ disconnect;
			पूर्ण
			csums_tfm = drbd_crypto_alloc_digest_safe(device,
					p->csums_alg, "csums-alg");
			अगर (IS_ERR(csums_tfm)) अणु
				csums_tfm = शून्य;
				जाओ disconnect;
			पूर्ण
		पूर्ण

		अगर (apv > 94 && new_disk_conf) अणु
			new_disk_conf->c_plan_ahead = be32_to_cpu(p->c_plan_ahead);
			new_disk_conf->c_delay_target = be32_to_cpu(p->c_delay_target);
			new_disk_conf->c_fill_target = be32_to_cpu(p->c_fill_target);
			new_disk_conf->c_max_rate = be32_to_cpu(p->c_max_rate);

			fअगरo_size = (new_disk_conf->c_plan_ahead * 10 * SLEEP_TIME) / HZ;
			अगर (fअगरo_size != device->rs_plan_s->size) अणु
				new_plan = fअगरo_alloc(fअगरo_size);
				अगर (!new_plan) अणु
					drbd_err(device, "kmalloc of fifo_buffer failed");
					put_ldev(device);
					जाओ disconnect;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (verअगरy_tfm || csums_tfm) अणु
			new_net_conf = kzalloc(माप(काष्ठा net_conf), GFP_KERNEL);
			अगर (!new_net_conf) अणु
				drbd_err(device, "Allocation of new net_conf failed\n");
				जाओ disconnect;
			पूर्ण

			*new_net_conf = *old_net_conf;

			अगर (verअगरy_tfm) अणु
				म_नकल(new_net_conf->verअगरy_alg, p->verअगरy_alg);
				new_net_conf->verअगरy_alg_len = म_माप(p->verअगरy_alg) + 1;
				crypto_मुक्त_shash(peer_device->connection->verअगरy_tfm);
				peer_device->connection->verअगरy_tfm = verअगरy_tfm;
				drbd_info(device, "using verify-alg: \"%s\"\n", p->verअगरy_alg);
			पूर्ण
			अगर (csums_tfm) अणु
				म_नकल(new_net_conf->csums_alg, p->csums_alg);
				new_net_conf->csums_alg_len = म_माप(p->csums_alg) + 1;
				crypto_मुक्त_shash(peer_device->connection->csums_tfm);
				peer_device->connection->csums_tfm = csums_tfm;
				drbd_info(device, "using csums-alg: \"%s\"\n", p->csums_alg);
			पूर्ण
			rcu_assign_poपूर्णांकer(connection->net_conf, new_net_conf);
		पूर्ण
	पूर्ण

	अगर (new_disk_conf) अणु
		rcu_assign_poपूर्णांकer(device->ldev->disk_conf, new_disk_conf);
		put_ldev(device);
	पूर्ण

	अगर (new_plan) अणु
		old_plan = device->rs_plan_s;
		rcu_assign_poपूर्णांकer(device->rs_plan_s, new_plan);
	पूर्ण

	mutex_unlock(&connection->resource->conf_update);
	synchronize_rcu();
	अगर (new_net_conf)
		kमुक्त(old_net_conf);
	kमुक्त(old_disk_conf);
	kमुक्त(old_plan);

	वापस 0;

reconnect:
	अगर (new_disk_conf) अणु
		put_ldev(device);
		kमुक्त(new_disk_conf);
	पूर्ण
	mutex_unlock(&connection->resource->conf_update);
	वापस -EIO;

disconnect:
	kमुक्त(new_plan);
	अगर (new_disk_conf) अणु
		put_ldev(device);
		kमुक्त(new_disk_conf);
	पूर्ण
	mutex_unlock(&connection->resource->conf_update);
	/* just क्रम completeness: actually not needed,
	 * as this is not reached अगर csums_tfm was ok. */
	crypto_मुक्त_shash(csums_tfm);
	/* but मुक्त the verअगरy_tfm again, अगर csums_tfm did not work out */
	crypto_मुक्त_shash(verअगरy_tfm);
	conn_request_state(peer_device->connection, NS(conn, C_DISCONNECTING), CS_HARD);
	वापस -EIO;
पूर्ण

/* warn अगर the arguments dअगरfer by more than 12.5% */
अटल व्योम warn_अगर_dअगरfer_considerably(काष्ठा drbd_device *device,
	स्थिर अक्षर *s, sector_t a, sector_t b)
अणु
	sector_t d;
	अगर (a == 0 || b == 0)
		वापस;
	d = (a > b) ? (a - b) : (b - a);
	अगर (d > (a>>3) || d > (b>>3))
		drbd_warn(device, "Considerable difference in %s: %llus vs. %llus\n", s,
		     (अचिन्हित दीर्घ दीर्घ)a, (अचिन्हित दीर्घ दीर्घ)b);
पूर्ण

अटल पूर्णांक receive_sizes(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_sizes *p = pi->data;
	काष्ठा o_qlim *o = (connection->agreed_features & DRBD_FF_WSAME) ? p->qlim : शून्य;
	क्रमागत determine_dev_size dd = DS_UNCHANGED;
	sector_t p_size, p_usize, p_csize, my_usize;
	sector_t new_size, cur_size;
	पूर्णांक ldsc = 0; /* local disk size changed */
	क्रमागत dds_flags ddsf;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस config_unknown_volume(connection, pi);
	device = peer_device->device;
	cur_size = get_capacity(device->vdisk);

	p_size = be64_to_cpu(p->d_size);
	p_usize = be64_to_cpu(p->u_size);
	p_csize = be64_to_cpu(p->c_size);

	/* just store the peer's disk size क्रम now.
	 * we still need to figure out whether we accept that. */
	device->p_size = p_size;

	अगर (get_ldev(device)) अणु
		rcu_पढ़ो_lock();
		my_usize = rcu_dereference(device->ldev->disk_conf)->disk_size;
		rcu_पढ़ो_unlock();

		warn_अगर_dअगरfer_considerably(device, "lower level device sizes",
			   p_size, drbd_get_max_capacity(device->ldev));
		warn_अगर_dअगरfer_considerably(device, "user requested size",
					    p_usize, my_usize);

		/* अगर this is the first connect, or an otherwise expected
		 * param exchange, choose the minimum */
		अगर (device->state.conn == C_WF_REPORT_PARAMS)
			p_usize = min_not_zero(my_usize, p_usize);

		/* Never shrink a device with usable data during connect,
		 * or "attach" on the peer.
		 * But allow online shrinking अगर we are connected. */
		new_size = drbd_new_dev_size(device, device->ldev, p_usize, 0);
		अगर (new_size < cur_size &&
		    device->state.disk >= D_OUTDATED &&
		    (device->state.conn < C_CONNECTED || device->state.pdsk == D_DISKLESS)) अणु
			drbd_err(device, "The peer's disk size is too small! (%llu < %llu sectors)\n",
					(अचिन्हित दीर्घ दीर्घ)new_size, (अचिन्हित दीर्घ दीर्घ)cur_size);
			conn_request_state(peer_device->connection, NS(conn, C_DISCONNECTING), CS_HARD);
			put_ldev(device);
			वापस -EIO;
		पूर्ण

		अगर (my_usize != p_usize) अणु
			काष्ठा disk_conf *old_disk_conf, *new_disk_conf = शून्य;

			new_disk_conf = kzalloc(माप(काष्ठा disk_conf), GFP_KERNEL);
			अगर (!new_disk_conf) अणु
				drbd_err(device, "Allocation of new disk_conf failed\n");
				put_ldev(device);
				वापस -ENOMEM;
			पूर्ण

			mutex_lock(&connection->resource->conf_update);
			old_disk_conf = device->ldev->disk_conf;
			*new_disk_conf = *old_disk_conf;
			new_disk_conf->disk_size = p_usize;

			rcu_assign_poपूर्णांकer(device->ldev->disk_conf, new_disk_conf);
			mutex_unlock(&connection->resource->conf_update);
			synchronize_rcu();
			kमुक्त(old_disk_conf);

			drbd_info(device, "Peer sets u_size to %lu sectors (old: %lu)\n",
				 (अचिन्हित दीर्घ)p_usize, (अचिन्हित दीर्घ)my_usize);
		पूर्ण

		put_ldev(device);
	पूर्ण

	device->peer_max_bio_size = be32_to_cpu(p->max_bio_size);
	/* Leave drbd_reconsider_queue_parameters() beक्रमe drbd_determine_dev_size().
	   In हाल we cleared the QUEUE_FLAG_DISCARD from our queue in
	   drbd_reconsider_queue_parameters(), we can be sure that after
	   drbd_determine_dev_size() no REQ_DISCARDs are in the queue. */

	ddsf = be16_to_cpu(p->dds_flags);
	अगर (get_ldev(device)) अणु
		drbd_reconsider_queue_parameters(device, device->ldev, o);
		dd = drbd_determine_dev_size(device, ddsf, शून्य);
		put_ldev(device);
		अगर (dd == DS_ERROR)
			वापस -EIO;
		drbd_md_sync(device);
	पूर्ण अन्यथा अणु
		/*
		 * I am diskless, need to accept the peer's *current* size.
		 * I must NOT accept the peers backing disk size,
		 * it may have been larger than mine all aदीर्घ...
		 *
		 * At this poपूर्णांक, the peer knows more about my disk, or at
		 * least about what we last agreed upon, than myself.
		 * So अगर his c_size is less than his d_size, the most likely
		 * reason is that *my* d_size was smaller last समय we checked.
		 *
		 * However, अगर he sends a zero current size,
		 * take his (user-capped or) backing disk size anyways.
		 *
		 * Unless of course he करोes not have a disk himself.
		 * In which हाल we ignore this completely.
		 */
		sector_t new_size = p_csize ?: p_usize ?: p_size;
		drbd_reconsider_queue_parameters(device, शून्य, o);
		अगर (new_size == 0) अणु
			/* Ignore, peer करोes not know nothing. */
		पूर्ण अन्यथा अगर (new_size == cur_size) अणु
			/* nothing to करो */
		पूर्ण अन्यथा अगर (cur_size != 0 && p_size == 0) अणु
			drbd_warn(device, "Ignored diskless peer device size (peer:%llu != me:%llu sectors)!\n",
					(अचिन्हित दीर्घ दीर्घ)new_size, (अचिन्हित दीर्घ दीर्घ)cur_size);
		पूर्ण अन्यथा अगर (new_size < cur_size && device->state.role == R_PRIMARY) अणु
			drbd_err(device, "The peer's device size is too small! (%llu < %llu sectors); demote me first!\n",
					(अचिन्हित दीर्घ दीर्घ)new_size, (अचिन्हित दीर्घ दीर्घ)cur_size);
			conn_request_state(peer_device->connection, NS(conn, C_DISCONNECTING), CS_HARD);
			वापस -EIO;
		पूर्ण अन्यथा अणु
			/* I believe the peer, अगर
			 *  - I करोn't have a current size myself
			 *  - we agree on the size anyways
			 *  - I करो have a current size, am Secondary,
			 *    and he has the only disk
			 *  - I करो have a current size, am Primary,
			 *    and he has the only disk,
			 *    which is larger than my current size
			 */
			drbd_set_my_capacity(device, new_size);
		पूर्ण
	पूर्ण

	अगर (get_ldev(device)) अणु
		अगर (device->ldev->known_size != drbd_get_capacity(device->ldev->backing_bdev)) अणु
			device->ldev->known_size = drbd_get_capacity(device->ldev->backing_bdev);
			ldsc = 1;
		पूर्ण

		put_ldev(device);
	पूर्ण

	अगर (device->state.conn > C_WF_REPORT_PARAMS) अणु
		अगर (be64_to_cpu(p->c_size) != get_capacity(device->vdisk) ||
		    ldsc) अणु
			/* we have dअगरferent sizes, probably peer
			 * needs to know my new size... */
			drbd_send_sizes(peer_device, 0, ddsf);
		पूर्ण
		अगर (test_and_clear_bit(RESIZE_PENDING, &device->flags) ||
		    (dd == DS_GREW && device->state.conn == C_CONNECTED)) अणु
			अगर (device->state.pdsk >= D_INCONSISTENT &&
			    device->state.disk >= D_INCONSISTENT) अणु
				अगर (ddsf & DDSF_NO_RESYNC)
					drbd_info(device, "Resync of new storage suppressed with --assume-clean\n");
				अन्यथा
					resync_after_online_grow(device);
			पूर्ण अन्यथा
				set_bit(RESYNC_AFTER_NEG, &device->flags);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक receive_uuids(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_uuids *p = pi->data;
	u64 *p_uuid;
	पूर्णांक i, updated_uuids = 0;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस config_unknown_volume(connection, pi);
	device = peer_device->device;

	p_uuid = kदो_स्मृति_array(UI_EXTENDED_SIZE, माप(*p_uuid), GFP_NOIO);
	अगर (!p_uuid) अणु
		drbd_err(device, "kmalloc of p_uuid failed\n");
		वापस false;
	पूर्ण

	क्रम (i = UI_CURRENT; i < UI_EXTENDED_SIZE; i++)
		p_uuid[i] = be64_to_cpu(p->uuid[i]);

	kमुक्त(device->p_uuid);
	device->p_uuid = p_uuid;

	अगर ((device->state.conn < C_CONNECTED || device->state.pdsk == D_DISKLESS) &&
	    device->state.disk < D_INCONSISTENT &&
	    device->state.role == R_PRIMARY &&
	    (device->ed_uuid & ~((u64)1)) != (p_uuid[UI_CURRENT] & ~((u64)1))) अणु
		drbd_err(device, "Can only connect to data with current UUID=%016llX\n",
		    (अचिन्हित दीर्घ दीर्घ)device->ed_uuid);
		conn_request_state(peer_device->connection, NS(conn, C_DISCONNECTING), CS_HARD);
		वापस -EIO;
	पूर्ण

	अगर (get_ldev(device)) अणु
		पूर्णांक skip_initial_sync =
			device->state.conn == C_CONNECTED &&
			peer_device->connection->agreed_pro_version >= 90 &&
			device->ldev->md.uuid[UI_CURRENT] == UUID_JUST_CREATED &&
			(p_uuid[UI_FLAGS] & 8);
		अगर (skip_initial_sync) अणु
			drbd_info(device, "Accepted new current UUID, preparing to skip initial sync\n");
			drbd_biपंचांगap_io(device, &drbd_bmio_clear_n_ग_लिखो,
					"clear_n_write from receive_uuids",
					BM_LOCKED_TEST_ALLOWED);
			_drbd_uuid_set(device, UI_CURRENT, p_uuid[UI_CURRENT]);
			_drbd_uuid_set(device, UI_BITMAP, 0);
			_drbd_set_state(_NS2(device, disk, D_UP_TO_DATE, pdsk, D_UP_TO_DATE),
					CS_VERBOSE, शून्य);
			drbd_md_sync(device);
			updated_uuids = 1;
		पूर्ण
		put_ldev(device);
	पूर्ण अन्यथा अगर (device->state.disk < D_INCONSISTENT &&
		   device->state.role == R_PRIMARY) अणु
		/* I am a diskless primary, the peer just created a new current UUID
		   क्रम me. */
		updated_uuids = drbd_set_ed_uuid(device, p_uuid[UI_CURRENT]);
	पूर्ण

	/* Beक्रमe we test क्रम the disk state, we should रुको until an eventually
	   ongoing cluster wide state change is finished. That is important अगर
	   we are primary and are detaching from our disk. We need to see the
	   new disk state... */
	mutex_lock(device->state_mutex);
	mutex_unlock(device->state_mutex);
	अगर (device->state.conn >= C_CONNECTED && device->state.disk < D_INCONSISTENT)
		updated_uuids |= drbd_set_ed_uuid(device, p_uuid[UI_CURRENT]);

	अगर (updated_uuids)
		drbd_prपूर्णांक_uuids(device, "receiver updated UUIDs to");

	वापस 0;
पूर्ण

/**
 * convert_state() - Converts the peer's view of the cluster state to our poपूर्णांक of view
 * @ps:		The state as seen by the peer.
 */
अटल जोड़ drbd_state convert_state(जोड़ drbd_state ps)
अणु
	जोड़ drbd_state ms;

	अटल क्रमागत drbd_conns c_tab[] = अणु
		[C_WF_REPORT_PARAMS] = C_WF_REPORT_PARAMS,
		[C_CONNECTED] = C_CONNECTED,

		[C_STARTING_SYNC_S] = C_STARTING_SYNC_T,
		[C_STARTING_SYNC_T] = C_STARTING_SYNC_S,
		[C_DISCONNECTING] = C_TEAR_DOWN, /* C_NETWORK_FAILURE, */
		[C_VERIFY_S]       = C_VERIFY_T,
		[C_MASK]   = C_MASK,
	पूर्ण;

	ms.i = ps.i;

	ms.conn = c_tab[ps.conn];
	ms.peer = ps.role;
	ms.role = ps.peer;
	ms.pdsk = ps.disk;
	ms.disk = ps.pdsk;
	ms.peer_isp = (ps.aftr_isp | ps.user_isp);

	वापस ms;
पूर्ण

अटल पूर्णांक receive_req_state(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_req_state *p = pi->data;
	जोड़ drbd_state mask, val;
	क्रमागत drbd_state_rv rv;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	mask.i = be32_to_cpu(p->mask);
	val.i = be32_to_cpu(p->val);

	अगर (test_bit(RESOLVE_CONFLICTS, &peer_device->connection->flags) &&
	    mutex_is_locked(device->state_mutex)) अणु
		drbd_send_sr_reply(peer_device, SS_CONCURRENT_ST_CHG);
		वापस 0;
	पूर्ण

	mask = convert_state(mask);
	val = convert_state(val);

	rv = drbd_change_state(device, CS_VERBOSE, mask, val);
	drbd_send_sr_reply(peer_device, rv);

	drbd_md_sync(device);

	वापस 0;
पूर्ण

अटल पूर्णांक receive_req_conn_state(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा p_req_state *p = pi->data;
	जोड़ drbd_state mask, val;
	क्रमागत drbd_state_rv rv;

	mask.i = be32_to_cpu(p->mask);
	val.i = be32_to_cpu(p->val);

	अगर (test_bit(RESOLVE_CONFLICTS, &connection->flags) &&
	    mutex_is_locked(&connection->cstate_mutex)) अणु
		conn_send_sr_reply(connection, SS_CONCURRENT_ST_CHG);
		वापस 0;
	पूर्ण

	mask = convert_state(mask);
	val = convert_state(val);

	rv = conn_request_state(connection, mask, val, CS_VERBOSE | CS_LOCAL_ONLY | CS_IGN_OUTD_FAIL);
	conn_send_sr_reply(connection, rv);

	वापस 0;
पूर्ण

अटल पूर्णांक receive_state(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_state *p = pi->data;
	जोड़ drbd_state os, ns, peer_state;
	क्रमागत drbd_disk_state real_peer_disk;
	क्रमागत chg_state_flags cs_flags;
	पूर्णांक rv;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस config_unknown_volume(connection, pi);
	device = peer_device->device;

	peer_state.i = be32_to_cpu(p->state);

	real_peer_disk = peer_state.disk;
	अगर (peer_state.disk == D_NEGOTIATING) अणु
		real_peer_disk = device->p_uuid[UI_FLAGS] & 4 ? D_INCONSISTENT : D_CONSISTENT;
		drbd_info(device, "real peer disk state = %s\n", drbd_disk_str(real_peer_disk));
	पूर्ण

	spin_lock_irq(&device->resource->req_lock);
 retry:
	os = ns = drbd_पढ़ो_state(device);
	spin_unlock_irq(&device->resource->req_lock);

	/* If some other part of the code (ack_receiver thपढ़ो, समयout)
	 * alपढ़ोy decided to बंद the connection again,
	 * we must not "re-establish" it here. */
	अगर (os.conn <= C_TEAR_DOWN)
		वापस -ECONNRESET;

	/* If this is the "end of sync" confirmation, usually the peer disk
	 * transitions from D_INCONSISTENT to D_UP_TO_DATE. For empty (0 bits
	 * set) resync started in PausedSyncT, or अगर the timing of छोड़ो-/
	 * unछोड़ो-sync events has been "just right", the peer disk may
	 * transition from D_CONSISTENT to D_UP_TO_DATE as well.
	 */
	अगर ((os.pdsk == D_INCONSISTENT || os.pdsk == D_CONSISTENT) &&
	    real_peer_disk == D_UP_TO_DATE &&
	    os.conn > C_CONNECTED && os.disk == D_UP_TO_DATE) अणु
		/* If we are (becoming) SyncSource, but peer is still in sync
		 * preparation, ignore its uptodate-ness to aव्योम flapping, it
		 * will change to inconsistent once the peer reaches active
		 * syncing states.
		 * It may have changed syncer-छोड़ोd flags, however, so we
		 * cannot ignore this completely. */
		अगर (peer_state.conn > C_CONNECTED &&
		    peer_state.conn < C_SYNC_SOURCE)
			real_peer_disk = D_INCONSISTENT;

		/* अगर peer_state changes to connected at the same समय,
		 * it explicitly notअगरies us that it finished resync.
		 * Maybe we should finish it up, too? */
		अन्यथा अगर (os.conn >= C_SYNC_SOURCE &&
			 peer_state.conn == C_CONNECTED) अणु
			अगर (drbd_bm_total_weight(device) <= device->rs_failed)
				drbd_resync_finished(device);
			वापस 0;
		पूर्ण
	पूर्ण

	/* explicit verअगरy finished notअगरication, stop sector reached. */
	अगर (os.conn == C_VERIFY_T && os.disk == D_UP_TO_DATE &&
	    peer_state.conn == C_CONNECTED && real_peer_disk == D_UP_TO_DATE) अणु
		ov_out_of_sync_prपूर्णांक(device);
		drbd_resync_finished(device);
		वापस 0;
	पूर्ण

	/* peer says his disk is inconsistent, जबतक we think it is uptodate,
	 * and this happens जबतक the peer still thinks we have a sync going on,
	 * but we think we are alपढ़ोy करोne with the sync.
	 * We ignore this to aव्योम flapping pdsk.
	 * This should not happen, अगर the peer is a recent version of drbd. */
	अगर (os.pdsk == D_UP_TO_DATE && real_peer_disk == D_INCONSISTENT &&
	    os.conn == C_CONNECTED && peer_state.conn > C_SYNC_SOURCE)
		real_peer_disk = D_UP_TO_DATE;

	अगर (ns.conn == C_WF_REPORT_PARAMS)
		ns.conn = C_CONNECTED;

	अगर (peer_state.conn == C_AHEAD)
		ns.conn = C_BEHIND;

	/* TODO:
	 * अगर (primary and diskless and peer uuid != effective uuid)
	 *     पात attach on peer;
	 *
	 * If this node करोes not have good data, was alपढ़ोy connected, but
	 * the peer did a late attach only now, trying to "negotiate" with me,
	 * AND I am currently Primary, possibly frozen, with some specअगरic
	 * "effective" uuid, this should never be reached, really, because
	 * we first send the uuids, then the current state.
	 *
	 * In this scenario, we alपढ़ोy dropped the connection hard
	 * when we received the unsuitable uuids (receive_uuids().
	 *
	 * Should we want to change this, that is: not drop the connection in
	 * receive_uuids() alपढ़ोy, then we would need to add a branch here
	 * that पातs the attach of "unsuitable uuids" on the peer in हाल
	 * this node is currently Diskless Primary.
	 */

	अगर (device->p_uuid && peer_state.disk >= D_NEGOTIATING &&
	    get_ldev_अगर_state(device, D_NEGOTIATING)) अणु
		पूर्णांक cr; /* consider resync */

		/* अगर we established a new connection */
		cr  = (os.conn < C_CONNECTED);
		/* अगर we had an established connection
		 * and one of the nodes newly attaches a disk */
		cr |= (os.conn == C_CONNECTED &&
		       (peer_state.disk == D_NEGOTIATING ||
			os.disk == D_NEGOTIATING));
		/* अगर we have both been inconsistent, and the peer has been
		 * क्रमced to be UpToDate with --क्रमce */
		cr |= test_bit(CONSIDER_RESYNC, &device->flags);
		/* अगर we had been plain connected, and the admin requested to
		 * start a sync by "invalidate" or "invalidate-remote" */
		cr |= (os.conn == C_CONNECTED &&
				(peer_state.conn >= C_STARTING_SYNC_S &&
				 peer_state.conn <= C_WF_BITMAP_T));

		अगर (cr)
			ns.conn = drbd_sync_handshake(peer_device, peer_state.role, real_peer_disk);

		put_ldev(device);
		अगर (ns.conn == C_MASK) अणु
			ns.conn = C_CONNECTED;
			अगर (device->state.disk == D_NEGOTIATING) अणु
				drbd_क्रमce_state(device, NS(disk, D_FAILED));
			पूर्ण अन्यथा अगर (peer_state.disk == D_NEGOTIATING) अणु
				drbd_err(device, "Disk attach process on the peer node was aborted.\n");
				peer_state.disk = D_DISKLESS;
				real_peer_disk = D_DISKLESS;
			पूर्ण अन्यथा अणु
				अगर (test_and_clear_bit(CONN_DRY_RUN, &peer_device->connection->flags))
					वापस -EIO;
				D_ASSERT(device, os.conn == C_WF_REPORT_PARAMS);
				conn_request_state(peer_device->connection, NS(conn, C_DISCONNECTING), CS_HARD);
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock_irq(&device->resource->req_lock);
	अगर (os.i != drbd_पढ़ो_state(device).i)
		जाओ retry;
	clear_bit(CONSIDER_RESYNC, &device->flags);
	ns.peer = peer_state.role;
	ns.pdsk = real_peer_disk;
	ns.peer_isp = (peer_state.aftr_isp | peer_state.user_isp);
	अगर ((ns.conn == C_CONNECTED || ns.conn == C_WF_BITMAP_S) && ns.disk == D_NEGOTIATING)
		ns.disk = device->new_state_पंचांगp.disk;
	cs_flags = CS_VERBOSE + (os.conn < C_CONNECTED && ns.conn >= C_CONNECTED ? 0 : CS_HARD);
	अगर (ns.pdsk == D_CONSISTENT && drbd_suspended(device) && ns.conn == C_CONNECTED && os.conn < C_CONNECTED &&
	    test_bit(NEW_CUR_UUID, &device->flags)) अणु
		/* Do not allow tl_restart(RESEND) क्रम a rebooted peer. We can only allow this
		   क्रम temporal network outages! */
		spin_unlock_irq(&device->resource->req_lock);
		drbd_err(device, "Aborting Connect, can not thaw IO with an only Consistent peer\n");
		tl_clear(peer_device->connection);
		drbd_uuid_new_current(device);
		clear_bit(NEW_CUR_UUID, &device->flags);
		conn_request_state(peer_device->connection, NS2(conn, C_PROTOCOL_ERROR, susp, 0), CS_HARD);
		वापस -EIO;
	पूर्ण
	rv = _drbd_set_state(device, ns, cs_flags, शून्य);
	ns = drbd_पढ़ो_state(device);
	spin_unlock_irq(&device->resource->req_lock);

	अगर (rv < SS_SUCCESS) अणु
		conn_request_state(peer_device->connection, NS(conn, C_DISCONNECTING), CS_HARD);
		वापस -EIO;
	पूर्ण

	अगर (os.conn > C_WF_REPORT_PARAMS) अणु
		अगर (ns.conn > C_CONNECTED && peer_state.conn <= C_CONNECTED &&
		    peer_state.disk != D_NEGOTIATING ) अणु
			/* we want resync, peer has not yet decided to sync... */
			/* Nowadays only used when क्रमcing a node पूर्णांकo primary role and
			   setting its disk to UpToDate with that */
			drbd_send_uuids(peer_device);
			drbd_send_current_state(peer_device);
		पूर्ण
	पूर्ण

	clear_bit(DISCARD_MY_DATA, &device->flags);

	drbd_md_sync(device); /* update connected indicator, la_size_sect, ... */

	वापस 0;
पूर्ण

अटल पूर्णांक receive_sync_uuid(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_rs_uuid *p = pi->data;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	रुको_event(device->misc_रुको,
		   device->state.conn == C_WF_SYNC_UUID ||
		   device->state.conn == C_BEHIND ||
		   device->state.conn < C_CONNECTED ||
		   device->state.disk < D_NEGOTIATING);

	/* D_ASSERT(device,  device->state.conn == C_WF_SYNC_UUID ); */

	/* Here the _drbd_uuid_ functions are right, current should
	   _not_ be rotated पूर्णांकo the history */
	अगर (get_ldev_अगर_state(device, D_NEGOTIATING)) अणु
		_drbd_uuid_set(device, UI_CURRENT, be64_to_cpu(p->uuid));
		_drbd_uuid_set(device, UI_BITMAP, 0UL);

		drbd_prपूर्णांक_uuids(device, "updated sync uuid");
		drbd_start_resync(device, C_SYNC_TARGET);

		put_ldev(device);
	पूर्ण अन्यथा
		drbd_err(device, "Ignoring SyncUUID packet!\n");

	वापस 0;
पूर्ण

/*
 * receive_biपंचांगap_plain
 *
 * Return 0 when करोne, 1 when another iteration is needed, and a negative error
 * code upon failure.
 */
अटल पूर्णांक
receive_biपंचांगap_plain(काष्ठा drbd_peer_device *peer_device, अचिन्हित पूर्णांक size,
		     अचिन्हित दीर्घ *p, काष्ठा bm_xfer_ctx *c)
अणु
	अचिन्हित पूर्णांक data_size = DRBD_SOCKET_BUFFER_SIZE -
				 drbd_header_size(peer_device->connection);
	अचिन्हित पूर्णांक num_words = min_t(माप_प्रकार, data_size / माप(*p),
				       c->bm_words - c->word_offset);
	अचिन्हित पूर्णांक want = num_words * माप(*p);
	पूर्णांक err;

	अगर (want != size) अणु
		drbd_err(peer_device, "%s:want (%u) != size (%u)\n", __func__, want, size);
		वापस -EIO;
	पूर्ण
	अगर (want == 0)
		वापस 0;
	err = drbd_recv_all(peer_device->connection, p, want);
	अगर (err)
		वापस err;

	drbd_bm_merge_lel(peer_device->device, c->word_offset, num_words, p);

	c->word_offset += num_words;
	c->bit_offset = c->word_offset * BITS_PER_LONG;
	अगर (c->bit_offset > c->bm_bits)
		c->bit_offset = c->bm_bits;

	वापस 1;
पूर्ण

अटल क्रमागत drbd_biपंचांगap_code dcbp_get_code(काष्ठा p_compressed_bm *p)
अणु
	वापस (क्रमागत drbd_biपंचांगap_code)(p->encoding & 0x0f);
पूर्ण

अटल पूर्णांक dcbp_get_start(काष्ठा p_compressed_bm *p)
अणु
	वापस (p->encoding & 0x80) != 0;
पूर्ण

अटल पूर्णांक dcbp_get_pad_bits(काष्ठा p_compressed_bm *p)
अणु
	वापस (p->encoding >> 4) & 0x7;
पूर्ण

/*
 * recv_bm_rle_bits
 *
 * Return 0 when करोne, 1 when another iteration is needed, and a negative error
 * code upon failure.
 */
अटल पूर्णांक
recv_bm_rle_bits(काष्ठा drbd_peer_device *peer_device,
		काष्ठा p_compressed_bm *p,
		 काष्ठा bm_xfer_ctx *c,
		 अचिन्हित पूर्णांक len)
अणु
	काष्ठा bitstream bs;
	u64 look_ahead;
	u64 rl;
	u64 पंचांगp;
	अचिन्हित दीर्घ s = c->bit_offset;
	अचिन्हित दीर्घ e;
	पूर्णांक toggle = dcbp_get_start(p);
	पूर्णांक have;
	पूर्णांक bits;

	bitstream_init(&bs, p->code, len, dcbp_get_pad_bits(p));

	bits = bitstream_get_bits(&bs, &look_ahead, 64);
	अगर (bits < 0)
		वापस -EIO;

	क्रम (have = bits; have > 0; s += rl, toggle = !toggle) अणु
		bits = vli_decode_bits(&rl, look_ahead);
		अगर (bits <= 0)
			वापस -EIO;

		अगर (toggle) अणु
			e = s + rl -1;
			अगर (e >= c->bm_bits) अणु
				drbd_err(peer_device, "bitmap overflow (e:%lu) while decoding bm RLE packet\n", e);
				वापस -EIO;
			पूर्ण
			_drbd_bm_set_bits(peer_device->device, s, e);
		पूर्ण

		अगर (have < bits) अणु
			drbd_err(peer_device, "bitmap decoding error: h:%d b:%d la:0x%08llx l:%u/%u\n",
				have, bits, look_ahead,
				(अचिन्हित पूर्णांक)(bs.cur.b - p->code),
				(अचिन्हित पूर्णांक)bs.buf_len);
			वापस -EIO;
		पूर्ण
		/* अगर we consumed all 64 bits, assign 0; >> 64 is "undefined"; */
		अगर (likely(bits < 64))
			look_ahead >>= bits;
		अन्यथा
			look_ahead = 0;
		have -= bits;

		bits = bitstream_get_bits(&bs, &पंचांगp, 64 - have);
		अगर (bits < 0)
			वापस -EIO;
		look_ahead |= पंचांगp << have;
		have += bits;
	पूर्ण

	c->bit_offset = s;
	bm_xfer_ctx_bit_to_word_offset(c);

	वापस (s != c->bm_bits);
पूर्ण

/*
 * decode_biपंचांगap_c
 *
 * Return 0 when करोne, 1 when another iteration is needed, and a negative error
 * code upon failure.
 */
अटल पूर्णांक
decode_biपंचांगap_c(काष्ठा drbd_peer_device *peer_device,
		काष्ठा p_compressed_bm *p,
		काष्ठा bm_xfer_ctx *c,
		अचिन्हित पूर्णांक len)
अणु
	अगर (dcbp_get_code(p) == RLE_VLI_Bits)
		वापस recv_bm_rle_bits(peer_device, p, c, len - माप(*p));

	/* other variants had been implemented क्रम evaluation,
	 * but have been dropped as this one turned out to be "best"
	 * during all our tests. */

	drbd_err(peer_device, "receive_bitmap_c: unknown encoding %u\n", p->encoding);
	conn_request_state(peer_device->connection, NS(conn, C_PROTOCOL_ERROR), CS_HARD);
	वापस -EIO;
पूर्ण

व्योम INFO_bm_xfer_stats(काष्ठा drbd_device *device,
		स्थिर अक्षर *direction, काष्ठा bm_xfer_ctx *c)
अणु
	/* what would it take to transfer it "plaintext" */
	अचिन्हित पूर्णांक header_size = drbd_header_size(first_peer_device(device)->connection);
	अचिन्हित पूर्णांक data_size = DRBD_SOCKET_BUFFER_SIZE - header_size;
	अचिन्हित पूर्णांक plain =
		header_size * (DIV_ROUND_UP(c->bm_words, data_size) + 1) +
		c->bm_words * माप(अचिन्हित दीर्घ);
	अचिन्हित पूर्णांक total = c->bytes[0] + c->bytes[1];
	अचिन्हित पूर्णांक r;

	/* total can not be zero. but just in हाल: */
	अगर (total == 0)
		वापस;

	/* करोn't report अगर not compressed */
	अगर (total >= plain)
		वापस;

	/* total < plain. check क्रम overflow, still */
	r = (total > अच_पूर्णांक_उच्च/1000) ? (total / (plain/1000))
		                    : (1000 * total / plain);

	अगर (r > 1000)
		r = 1000;

	r = 1000 - r;
	drbd_info(device, "%s bitmap stats [Bytes(packets)]: plain %u(%u), RLE %u(%u), "
	     "total %u; compression: %u.%u%%\n",
			direction,
			c->bytes[1], c->packets[1],
			c->bytes[0], c->packets[0],
			total, r/10, r % 10);
पूर्ण

/* Since we are processing the bitfield from lower addresses to higher,
   it करोes not matter अगर the process it in 32 bit chunks or 64 bit
   chunks as दीर्घ as it is little endian. (Understand it as byte stream,
   beginning with the lowest byte...) If we would use big endian
   we would need to process it from the highest address to the lowest,
   in order to be agnostic to the 32 vs 64 bits issue.

   वापसs 0 on failure, 1 अगर we successfully received it. */
अटल पूर्णांक receive_biपंचांगap(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा bm_xfer_ctx c;
	पूर्णांक err;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	drbd_bm_lock(device, "receive bitmap", BM_LOCKED_SET_ALLOWED);
	/* you are supposed to send additional out-of-sync inक्रमmation
	 * अगर you actually set bits during this phase */

	c = (काष्ठा bm_xfer_ctx) अणु
		.bm_bits = drbd_bm_bits(device),
		.bm_words = drbd_bm_words(device),
	पूर्ण;

	क्रम(;;) अणु
		अगर (pi->cmd == P_BITMAP)
			err = receive_biपंचांगap_plain(peer_device, pi->size, pi->data, &c);
		अन्यथा अगर (pi->cmd == P_COMPRESSED_BITMAP) अणु
			/* MAYBE: sanity check that we speak proto >= 90,
			 * and the feature is enabled! */
			काष्ठा p_compressed_bm *p = pi->data;

			अगर (pi->size > DRBD_SOCKET_BUFFER_SIZE - drbd_header_size(connection)) अणु
				drbd_err(device, "ReportCBitmap packet too large\n");
				err = -EIO;
				जाओ out;
			पूर्ण
			अगर (pi->size <= माप(*p)) अणु
				drbd_err(device, "ReportCBitmap packet too small (l:%u)\n", pi->size);
				err = -EIO;
				जाओ out;
			पूर्ण
			err = drbd_recv_all(peer_device->connection, p, pi->size);
			अगर (err)
			       जाओ out;
			err = decode_biपंचांगap_c(peer_device, p, &c, pi->size);
		पूर्ण अन्यथा अणु
			drbd_warn(device, "receive_bitmap: cmd neither ReportBitMap nor ReportCBitMap (is 0x%x)", pi->cmd);
			err = -EIO;
			जाओ out;
		पूर्ण

		c.packets[pi->cmd == P_BITMAP]++;
		c.bytes[pi->cmd == P_BITMAP] += drbd_header_size(connection) + pi->size;

		अगर (err <= 0) अणु
			अगर (err < 0)
				जाओ out;
			अवरोध;
		पूर्ण
		err = drbd_recv_header(peer_device->connection, pi);
		अगर (err)
			जाओ out;
	पूर्ण

	INFO_bm_xfer_stats(device, "receive", &c);

	अगर (device->state.conn == C_WF_BITMAP_T) अणु
		क्रमागत drbd_state_rv rv;

		err = drbd_send_biपंचांगap(device);
		अगर (err)
			जाओ out;
		/* Omit CS_ORDERED with this state transition to aव्योम deadlocks. */
		rv = _drbd_request_state(device, NS(conn, C_WF_SYNC_UUID), CS_VERBOSE);
		D_ASSERT(device, rv == SS_SUCCESS);
	पूर्ण अन्यथा अगर (device->state.conn != C_WF_BITMAP_S) अणु
		/* admin may have requested C_DISCONNECTING,
		 * other thपढ़ोs may have noticed network errors */
		drbd_info(device, "unexpected cstate (%s) in receive_bitmap\n",
		    drbd_conn_str(device->state.conn));
	पूर्ण
	err = 0;

 out:
	drbd_bm_unlock(device);
	अगर (!err && device->state.conn == C_WF_BITMAP_S)
		drbd_start_resync(device, C_SYNC_SOURCE);
	वापस err;
पूर्ण

अटल पूर्णांक receive_skip(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	drbd_warn(connection, "skipping unknown optional packet type %d, l: %d!\n",
		 pi->cmd, pi->size);

	वापस ignore_reमुख्यing_packet(connection, pi);
पूर्ण

अटल पूर्णांक receive_UnplugRemote(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	/* Make sure we've acked all the TCP data associated
	 * with the data requests being unplugged */
	tcp_sock_set_quickack(connection->data.socket->sk, 2);
	वापस 0;
पूर्ण

अटल पूर्णांक receive_out_of_sync(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_block_desc *p = pi->data;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	चयन (device->state.conn) अणु
	हाल C_WF_SYNC_UUID:
	हाल C_WF_BITMAP_T:
	हाल C_BEHIND:
			अवरोध;
	शेष:
		drbd_err(device, "ASSERT FAILED cstate = %s, expected: WFSyncUUID|WFBitMapT|Behind\n",
				drbd_conn_str(device->state.conn));
	पूर्ण

	drbd_set_out_of_sync(device, be64_to_cpu(p->sector), be32_to_cpu(p->blksize));

	वापस 0;
पूर्ण

अटल पूर्णांक receive_rs_deallocated(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा p_block_desc *p = pi->data;
	काष्ठा drbd_device *device;
	sector_t sector;
	पूर्णांक size, err = 0;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	sector = be64_to_cpu(p->sector);
	size = be32_to_cpu(p->blksize);

	dec_rs_pending(device);

	अगर (get_ldev(device)) अणु
		काष्ठा drbd_peer_request *peer_req;
		स्थिर पूर्णांक op = REQ_OP_WRITE_ZEROES;

		peer_req = drbd_alloc_peer_req(peer_device, ID_SYNCER, sector,
					       size, 0, GFP_NOIO);
		अगर (!peer_req) अणु
			put_ldev(device);
			वापस -ENOMEM;
		पूर्ण

		peer_req->w.cb = e_end_resync_block;
		peer_req->submit_jअगर = jअगरfies;
		peer_req->flags |= EE_TRIM;

		spin_lock_irq(&device->resource->req_lock);
		list_add_tail(&peer_req->w.list, &device->sync_ee);
		spin_unlock_irq(&device->resource->req_lock);

		atomic_add(pi->size >> 9, &device->rs_sect_ev);
		err = drbd_submit_peer_request(device, peer_req, op, 0, DRBD_FAULT_RS_WR);

		अगर (err) अणु
			spin_lock_irq(&device->resource->req_lock);
			list_del(&peer_req->w.list);
			spin_unlock_irq(&device->resource->req_lock);

			drbd_मुक्त_peer_req(device, peer_req);
			put_ldev(device);
			err = 0;
			जाओ fail;
		पूर्ण

		inc_unacked(device);

		/* No put_ldev() here. Gets called in drbd_endio_ग_लिखो_sec_final(),
		   as well as drbd_rs_complete_io() */
	पूर्ण अन्यथा अणु
	fail:
		drbd_rs_complete_io(device, sector);
		drbd_send_ack_ex(peer_device, P_NEG_ACK, sector, size, ID_SYNCER);
	पूर्ण

	atomic_add(size >> 9, &device->rs_sect_in);

	वापस err;
पूर्ण

काष्ठा data_cmd अणु
	पूर्णांक expect_payload;
	अचिन्हित पूर्णांक pkt_size;
	पूर्णांक (*fn)(काष्ठा drbd_connection *, काष्ठा packet_info *);
पूर्ण;

अटल काष्ठा data_cmd drbd_cmd_handler[] = अणु
	[P_DATA]	    = अणु 1, माप(काष्ठा p_data), receive_Data पूर्ण,
	[P_DATA_REPLY]	    = अणु 1, माप(काष्ठा p_data), receive_DataReply पूर्ण,
	[P_RS_DATA_REPLY]   = अणु 1, माप(काष्ठा p_data), receive_RSDataReply पूर्ण ,
	[P_BARRIER]	    = अणु 0, माप(काष्ठा p_barrier), receive_Barrier पूर्ण ,
	[P_BITMAP]	    = अणु 1, 0, receive_biपंचांगap पूर्ण ,
	[P_COMPRESSED_BITMAP] = अणु 1, 0, receive_biपंचांगap पूर्ण ,
	[P_UNPLUG_REMOTE]   = अणु 0, 0, receive_UnplugRemote पूर्ण,
	[P_DATA_REQUEST]    = अणु 0, माप(काष्ठा p_block_req), receive_DataRequest पूर्ण,
	[P_RS_DATA_REQUEST] = अणु 0, माप(काष्ठा p_block_req), receive_DataRequest पूर्ण,
	[P_SYNC_PARAM]	    = अणु 1, 0, receive_SyncParam पूर्ण,
	[P_SYNC_PARAM89]    = अणु 1, 0, receive_SyncParam पूर्ण,
	[P_PROTOCOL]        = अणु 1, माप(काष्ठा p_protocol), receive_protocol पूर्ण,
	[P_UUIDS]	    = अणु 0, माप(काष्ठा p_uuids), receive_uuids पूर्ण,
	[P_SIZES]	    = अणु 0, माप(काष्ठा p_sizes), receive_sizes पूर्ण,
	[P_STATE]	    = अणु 0, माप(काष्ठा p_state), receive_state पूर्ण,
	[P_STATE_CHG_REQ]   = अणु 0, माप(काष्ठा p_req_state), receive_req_state पूर्ण,
	[P_SYNC_UUID]       = अणु 0, माप(काष्ठा p_rs_uuid), receive_sync_uuid पूर्ण,
	[P_OV_REQUEST]      = अणु 0, माप(काष्ठा p_block_req), receive_DataRequest पूर्ण,
	[P_OV_REPLY]        = अणु 1, माप(काष्ठा p_block_req), receive_DataRequest पूर्ण,
	[P_CSUM_RS_REQUEST] = अणु 1, माप(काष्ठा p_block_req), receive_DataRequest पूर्ण,
	[P_RS_THIN_REQ]     = अणु 0, माप(काष्ठा p_block_req), receive_DataRequest पूर्ण,
	[P_DELAY_PROBE]     = अणु 0, माप(काष्ठा p_delay_probe93), receive_skip पूर्ण,
	[P_OUT_OF_SYNC]     = अणु 0, माप(काष्ठा p_block_desc), receive_out_of_sync पूर्ण,
	[P_CONN_ST_CHG_REQ] = अणु 0, माप(काष्ठा p_req_state), receive_req_conn_state पूर्ण,
	[P_PROTOCOL_UPDATE] = अणु 1, माप(काष्ठा p_protocol), receive_protocol पूर्ण,
	[P_TRIM]	    = अणु 0, माप(काष्ठा p_trim), receive_Data पूर्ण,
	[P_ZEROES]	    = अणु 0, माप(काष्ठा p_trim), receive_Data पूर्ण,
	[P_RS_DEALLOCATED]  = अणु 0, माप(काष्ठा p_block_desc), receive_rs_deallocated पूर्ण,
	[P_WSAME]	    = अणु 1, माप(काष्ठा p_wsame), receive_Data पूर्ण,
पूर्ण;

अटल व्योम drbdd(काष्ठा drbd_connection *connection)
अणु
	काष्ठा packet_info pi;
	माप_प्रकार shs; /* sub header size */
	पूर्णांक err;

	जबतक (get_t_state(&connection->receiver) == RUNNING) अणु
		काष्ठा data_cmd स्थिर *cmd;

		drbd_thपढ़ो_current_set_cpu(&connection->receiver);
		update_receiver_timing_details(connection, drbd_recv_header_maybe_unplug);
		अगर (drbd_recv_header_maybe_unplug(connection, &pi))
			जाओ err_out;

		cmd = &drbd_cmd_handler[pi.cmd];
		अगर (unlikely(pi.cmd >= ARRAY_SIZE(drbd_cmd_handler) || !cmd->fn)) अणु
			drbd_err(connection, "Unexpected data packet %s (0x%04x)",
				 cmdname(pi.cmd), pi.cmd);
			जाओ err_out;
		पूर्ण

		shs = cmd->pkt_size;
		अगर (pi.cmd == P_SIZES && connection->agreed_features & DRBD_FF_WSAME)
			shs += माप(काष्ठा o_qlim);
		अगर (pi.size > shs && !cmd->expect_payload) अणु
			drbd_err(connection, "No payload expected %s l:%d\n",
				 cmdname(pi.cmd), pi.size);
			जाओ err_out;
		पूर्ण
		अगर (pi.size < shs) अणु
			drbd_err(connection, "%s: unexpected packet size, expected:%d received:%d\n",
				 cmdname(pi.cmd), (पूर्णांक)shs, pi.size);
			जाओ err_out;
		पूर्ण

		अगर (shs) अणु
			update_receiver_timing_details(connection, drbd_recv_all_warn);
			err = drbd_recv_all_warn(connection, pi.data, shs);
			अगर (err)
				जाओ err_out;
			pi.size -= shs;
		पूर्ण

		update_receiver_timing_details(connection, cmd->fn);
		err = cmd->fn(connection, &pi);
		अगर (err) अणु
			drbd_err(connection, "error receiving %s, e: %d l: %d!\n",
				 cmdname(pi.cmd), err, pi.size);
			जाओ err_out;
		पूर्ण
	पूर्ण
	वापस;

    err_out:
	conn_request_state(connection, NS(conn, C_PROTOCOL_ERROR), CS_HARD);
पूर्ण

अटल व्योम conn_disconnect(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_peer_device *peer_device;
	क्रमागत drbd_conns oc;
	पूर्णांक vnr;

	अगर (connection->cstate == C_STANDALONE)
		वापस;

	/* We are about to start the cleanup after connection loss.
	 * Make sure drbd_make_request knows about that.
	 * Usually we should be in some network failure state alपढ़ोy,
	 * but just in हाल we are not, we fix it up here.
	 */
	conn_request_state(connection, NS(conn, C_NETWORK_FAILURE), CS_HARD);

	/* ack_receiver करोes not clean up anything. it must not पूर्णांकerfere, either */
	drbd_thपढ़ो_stop(&connection->ack_receiver);
	अगर (connection->ack_sender) अणु
		destroy_workqueue(connection->ack_sender);
		connection->ack_sender = शून्य;
	पूर्ण
	drbd_मुक्त_sock(connection);

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		kref_get(&device->kref);
		rcu_पढ़ो_unlock();
		drbd_disconnected(peer_device);
		kref_put(&device->kref, drbd_destroy_device);
		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!list_empty(&connection->current_epoch->list))
		drbd_err(connection, "ASSERTION FAILED: connection->current_epoch->list not empty\n");
	/* ok, no more ee's on the fly, it is safe to reset the epoch_size */
	atomic_set(&connection->current_epoch->epoch_size, 0);
	connection->send.seen_any_ग_लिखो_yet = false;

	drbd_info(connection, "Connection closed\n");

	अगर (conn_highest_role(connection) == R_PRIMARY && conn_highest_pdsk(connection) >= D_UNKNOWN)
		conn_try_outdate_peer_async(connection);

	spin_lock_irq(&connection->resource->req_lock);
	oc = connection->cstate;
	अगर (oc >= C_UNCONNECTED)
		_conn_request_state(connection, NS(conn, C_UNCONNECTED), CS_VERBOSE);

	spin_unlock_irq(&connection->resource->req_lock);

	अगर (oc == C_DISCONNECTING)
		conn_request_state(connection, NS(conn, C_STANDALONE), CS_VERBOSE | CS_HARD);
पूर्ण

अटल पूर्णांक drbd_disconnected(काष्ठा drbd_peer_device *peer_device)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	अचिन्हित पूर्णांक i;

	/* रुको क्रम current activity to cease. */
	spin_lock_irq(&device->resource->req_lock);
	_drbd_रुको_ee_list_empty(device, &device->active_ee);
	_drbd_रुको_ee_list_empty(device, &device->sync_ee);
	_drbd_रुको_ee_list_empty(device, &device->पढ़ो_ee);
	spin_unlock_irq(&device->resource->req_lock);

	/* We करो not have data काष्ठाures that would allow us to
	 * get the rs_pending_cnt करोwn to 0 again.
	 *  * On C_SYNC_TARGET we करो not have any data काष्ठाures describing
	 *    the pending RSDataRequest's we have sent.
	 *  * On C_SYNC_SOURCE there is no data काष्ठाure that tracks
	 *    the P_RS_DATA_REPLY blocks that we sent to the SyncTarget.
	 *  And no, it is not the sum of the reference counts in the
	 *  resync_LRU. The resync_LRU tracks the whole operation including
	 *  the disk-IO, जबतक the rs_pending_cnt only tracks the blocks
	 *  on the fly. */
	drbd_rs_cancel_all(device);
	device->rs_total = 0;
	device->rs_failed = 0;
	atomic_set(&device->rs_pending_cnt, 0);
	wake_up(&device->misc_रुको);

	del_समयr_sync(&device->resync_समयr);
	resync_समयr_fn(&device->resync_समयr);

	/* रुको क्रम all w_e_end_data_req, w_e_end_rsdata_req, w_send_barrier,
	 * w_make_resync_request etc. which may still be on the worker queue
	 * to be "canceled" */
	drbd_flush_workqueue(&peer_device->connection->sender_work);

	drbd_finish_peer_reqs(device);

	/* This second workqueue flush is necessary, since drbd_finish_peer_reqs()
	   might have issued a work again. The one beक्रमe drbd_finish_peer_reqs() is
	   necessary to reclain net_ee in drbd_finish_peer_reqs(). */
	drbd_flush_workqueue(&peer_device->connection->sender_work);

	/* need to करो it again, drbd_finish_peer_reqs() may have populated it
	 * again via drbd_try_clear_on_disk_bm(). */
	drbd_rs_cancel_all(device);

	kमुक्त(device->p_uuid);
	device->p_uuid = शून्य;

	अगर (!drbd_suspended(device))
		tl_clear(peer_device->connection);

	drbd_md_sync(device);

	अगर (get_ldev(device)) अणु
		drbd_biपंचांगap_io(device, &drbd_bm_ग_लिखो_copy_pages,
				"write from disconnected", BM_LOCKED_CHANGE_ALLOWED);
		put_ldev(device);
	पूर्ण

	/* tcp_बंद and release of sendpage pages can be deferred.  I करोn't
	 * want to use SO_LINGER, because apparently it can be deferred क्रम
	 * more than 20 seconds (दीर्घest समय I checked).
	 *
	 * Actually we करोn't care क्रम exactly when the network stack करोes its
	 * put_page(), but release our reference on these pages right here.
	 */
	i = drbd_मुक्त_peer_reqs(device, &device->net_ee);
	अगर (i)
		drbd_info(device, "net_ee not empty, killed %u entries\n", i);
	i = atomic_पढ़ो(&device->pp_in_use_by_net);
	अगर (i)
		drbd_info(device, "pp_in_use_by_net = %d, expected 0\n", i);
	i = atomic_पढ़ो(&device->pp_in_use);
	अगर (i)
		drbd_info(device, "pp_in_use = %d, expected 0\n", i);

	D_ASSERT(device, list_empty(&device->पढ़ो_ee));
	D_ASSERT(device, list_empty(&device->active_ee));
	D_ASSERT(device, list_empty(&device->sync_ee));
	D_ASSERT(device, list_empty(&device->करोne_ee));

	वापस 0;
पूर्ण

/*
 * We support PRO_VERSION_MIN to PRO_VERSION_MAX. The protocol version
 * we can agree on is stored in agreed_pro_version.
 *
 * feature flags and the reserved array should be enough room क्रम future
 * enhancements of the handshake protocol, and possible plugins...
 *
 * क्रम now, they are expected to be zero, but ignored.
 */
अटल पूर्णांक drbd_send_features(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_connection_features *p;

	sock = &connection->data;
	p = conn_prepare_command(connection, sock);
	अगर (!p)
		वापस -EIO;
	स_रखो(p, 0, माप(*p));
	p->protocol_min = cpu_to_be32(PRO_VERSION_MIN);
	p->protocol_max = cpu_to_be32(PRO_VERSION_MAX);
	p->feature_flags = cpu_to_be32(PRO_FEATURES);
	वापस conn_send_command(connection, sock, P_CONNECTION_FEATURES, माप(*p), शून्य, 0);
पूर्ण

/*
 * वापस values:
 *   1 yes, we have a valid connection
 *   0 oops, did not work out, please try again
 *  -1 peer talks dअगरferent language,
 *     no poपूर्णांक in trying again, please go standalone.
 */
अटल पूर्णांक drbd_करो_features(काष्ठा drbd_connection *connection)
अणु
	/* ASSERT current == connection->receiver ... */
	काष्ठा p_connection_features *p;
	स्थिर पूर्णांक expect = माप(काष्ठा p_connection_features);
	काष्ठा packet_info pi;
	पूर्णांक err;

	err = drbd_send_features(connection);
	अगर (err)
		वापस 0;

	err = drbd_recv_header(connection, &pi);
	अगर (err)
		वापस 0;

	अगर (pi.cmd != P_CONNECTION_FEATURES) अणु
		drbd_err(connection, "expected ConnectionFeatures packet, received: %s (0x%04x)\n",
			 cmdname(pi.cmd), pi.cmd);
		वापस -1;
	पूर्ण

	अगर (pi.size != expect) अणु
		drbd_err(connection, "expected ConnectionFeatures length: %u, received: %u\n",
		     expect, pi.size);
		वापस -1;
	पूर्ण

	p = pi.data;
	err = drbd_recv_all_warn(connection, p, expect);
	अगर (err)
		वापस 0;

	p->protocol_min = be32_to_cpu(p->protocol_min);
	p->protocol_max = be32_to_cpu(p->protocol_max);
	अगर (p->protocol_max == 0)
		p->protocol_max = p->protocol_min;

	अगर (PRO_VERSION_MAX < p->protocol_min ||
	    PRO_VERSION_MIN > p->protocol_max)
		जाओ incompat;

	connection->agreed_pro_version = min_t(पूर्णांक, PRO_VERSION_MAX, p->protocol_max);
	connection->agreed_features = PRO_FEATURES & be32_to_cpu(p->feature_flags);

	drbd_info(connection, "Handshake successful: "
	     "Agreed network protocol version %d\n", connection->agreed_pro_version);

	drbd_info(connection, "Feature flags enabled on protocol level: 0x%x%s%s%s%s.\n",
		  connection->agreed_features,
		  connection->agreed_features & DRBD_FF_TRIM ? " TRIM" : "",
		  connection->agreed_features & DRBD_FF_THIN_RESYNC ? " THIN_RESYNC" : "",
		  connection->agreed_features & DRBD_FF_WSAME ? " WRITE_SAME" : "",
		  connection->agreed_features & DRBD_FF_WZEROES ? " WRITE_ZEROES" :
		  connection->agreed_features ? "" : " none");

	वापस 1;

 incompat:
	drbd_err(connection, "incompatible DRBD dialects: "
	    "I support %d-%d, peer supports %d-%d\n",
	    PRO_VERSION_MIN, PRO_VERSION_MAX,
	    p->protocol_min, p->protocol_max);
	वापस -1;
पूर्ण

#अगर !defined(CONFIG_CRYPTO_HMAC) && !defined(CONFIG_CRYPTO_HMAC_MODULE)
अटल पूर्णांक drbd_करो_auth(काष्ठा drbd_connection *connection)
अणु
	drbd_err(connection, "This kernel was build without CONFIG_CRYPTO_HMAC.\n");
	drbd_err(connection, "You need to disable 'cram-hmac-alg' in drbd.conf.\n");
	वापस -1;
पूर्ण
#अन्यथा
#घोषणा CHALLENGE_LEN 64

/* Return value:
	1 - auth succeeded,
	0 - failed, try again (network error),
	-1 - auth failed, करोn't try again.
*/

अटल पूर्णांक drbd_करो_auth(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_socket *sock;
	अक्षर my_challenge[CHALLENGE_LEN];  /* 64 Bytes... */
	अक्षर *response = शून्य;
	अक्षर *right_response = शून्य;
	अक्षर *peers_ch = शून्य;
	अचिन्हित पूर्णांक key_len;
	अक्षर secret[SHARED_SECRET_MAX]; /* 64 byte */
	अचिन्हित पूर्णांक resp_size;
	काष्ठा shash_desc *desc;
	काष्ठा packet_info pi;
	काष्ठा net_conf *nc;
	पूर्णांक err, rv;

	/* FIXME: Put the challenge/response पूर्णांकo the pपुनः_स्मृतिated socket buffer.  */

	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	key_len = म_माप(nc->shared_secret);
	स_नकल(secret, nc->shared_secret, key_len);
	rcu_पढ़ो_unlock();

	desc = kदो_स्मृति(माप(काष्ठा shash_desc) +
		       crypto_shash_descsize(connection->cram_hmac_tfm),
		       GFP_KERNEL);
	अगर (!desc) अणु
		rv = -1;
		जाओ fail;
	पूर्ण
	desc->tfm = connection->cram_hmac_tfm;

	rv = crypto_shash_setkey(connection->cram_hmac_tfm, (u8 *)secret, key_len);
	अगर (rv) अणु
		drbd_err(connection, "crypto_shash_setkey() failed with %d\n", rv);
		rv = -1;
		जाओ fail;
	पूर्ण

	get_अक्रमom_bytes(my_challenge, CHALLENGE_LEN);

	sock = &connection->data;
	अगर (!conn_prepare_command(connection, sock)) अणु
		rv = 0;
		जाओ fail;
	पूर्ण
	rv = !conn_send_command(connection, sock, P_AUTH_CHALLENGE, 0,
				my_challenge, CHALLENGE_LEN);
	अगर (!rv)
		जाओ fail;

	err = drbd_recv_header(connection, &pi);
	अगर (err) अणु
		rv = 0;
		जाओ fail;
	पूर्ण

	अगर (pi.cmd != P_AUTH_CHALLENGE) अणु
		drbd_err(connection, "expected AuthChallenge packet, received: %s (0x%04x)\n",
			 cmdname(pi.cmd), pi.cmd);
		rv = -1;
		जाओ fail;
	पूर्ण

	अगर (pi.size > CHALLENGE_LEN * 2) अणु
		drbd_err(connection, "expected AuthChallenge payload too big.\n");
		rv = -1;
		जाओ fail;
	पूर्ण

	अगर (pi.size < CHALLENGE_LEN) अणु
		drbd_err(connection, "AuthChallenge payload too small.\n");
		rv = -1;
		जाओ fail;
	पूर्ण

	peers_ch = kदो_स्मृति(pi.size, GFP_NOIO);
	अगर (peers_ch == शून्य) अणु
		drbd_err(connection, "kmalloc of peers_ch failed\n");
		rv = -1;
		जाओ fail;
	पूर्ण

	err = drbd_recv_all_warn(connection, peers_ch, pi.size);
	अगर (err) अणु
		rv = 0;
		जाओ fail;
	पूर्ण

	अगर (!स_भेद(my_challenge, peers_ch, CHALLENGE_LEN)) अणु
		drbd_err(connection, "Peer presented the same challenge!\n");
		rv = -1;
		जाओ fail;
	पूर्ण

	resp_size = crypto_shash_digestsize(connection->cram_hmac_tfm);
	response = kदो_स्मृति(resp_size, GFP_NOIO);
	अगर (response == शून्य) अणु
		drbd_err(connection, "kmalloc of response failed\n");
		rv = -1;
		जाओ fail;
	पूर्ण

	rv = crypto_shash_digest(desc, peers_ch, pi.size, response);
	अगर (rv) अणु
		drbd_err(connection, "crypto_hash_digest() failed with %d\n", rv);
		rv = -1;
		जाओ fail;
	पूर्ण

	अगर (!conn_prepare_command(connection, sock)) अणु
		rv = 0;
		जाओ fail;
	पूर्ण
	rv = !conn_send_command(connection, sock, P_AUTH_RESPONSE, 0,
				response, resp_size);
	अगर (!rv)
		जाओ fail;

	err = drbd_recv_header(connection, &pi);
	अगर (err) अणु
		rv = 0;
		जाओ fail;
	पूर्ण

	अगर (pi.cmd != P_AUTH_RESPONSE) अणु
		drbd_err(connection, "expected AuthResponse packet, received: %s (0x%04x)\n",
			 cmdname(pi.cmd), pi.cmd);
		rv = 0;
		जाओ fail;
	पूर्ण

	अगर (pi.size != resp_size) अणु
		drbd_err(connection, "expected AuthResponse payload of wrong size\n");
		rv = 0;
		जाओ fail;
	पूर्ण

	err = drbd_recv_all_warn(connection, response , resp_size);
	अगर (err) अणु
		rv = 0;
		जाओ fail;
	पूर्ण

	right_response = kदो_स्मृति(resp_size, GFP_NOIO);
	अगर (right_response == शून्य) अणु
		drbd_err(connection, "kmalloc of right_response failed\n");
		rv = -1;
		जाओ fail;
	पूर्ण

	rv = crypto_shash_digest(desc, my_challenge, CHALLENGE_LEN,
				 right_response);
	अगर (rv) अणु
		drbd_err(connection, "crypto_hash_digest() failed with %d\n", rv);
		rv = -1;
		जाओ fail;
	पूर्ण

	rv = !स_भेद(response, right_response, resp_size);

	अगर (rv)
		drbd_info(connection, "Peer authenticated using %d bytes HMAC\n",
		     resp_size);
	अन्यथा
		rv = -1;

 fail:
	kमुक्त(peers_ch);
	kमुक्त(response);
	kमुक्त(right_response);
	अगर (desc) अणु
		shash_desc_zero(desc);
		kमुक्त(desc);
	पूर्ण

	वापस rv;
पूर्ण
#पूर्ण_अगर

पूर्णांक drbd_receiver(काष्ठा drbd_thपढ़ो *thi)
अणु
	काष्ठा drbd_connection *connection = thi->connection;
	पूर्णांक h;

	drbd_info(connection, "receiver (re)started\n");

	करो अणु
		h = conn_connect(connection);
		अगर (h == 0) अणु
			conn_disconnect(connection);
			schedule_समयout_पूर्णांकerruptible(HZ);
		पूर्ण
		अगर (h == -1) अणु
			drbd_warn(connection, "Discarding network configuration.\n");
			conn_request_state(connection, NS(conn, C_DISCONNECTING), CS_HARD);
		पूर्ण
	पूर्ण जबतक (h == 0);

	अगर (h > 0) अणु
		blk_start_plug(&connection->receiver_plug);
		drbdd(connection);
		blk_finish_plug(&connection->receiver_plug);
	पूर्ण

	conn_disconnect(connection);

	drbd_info(connection, "receiver terminated\n");
	वापस 0;
पूर्ण

/* ********* acknowledge sender ******** */

अटल पूर्णांक got_conn_RqSReply(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा p_req_state_reply *p = pi->data;
	पूर्णांक retcode = be32_to_cpu(p->retcode);

	अगर (retcode >= SS_SUCCESS) अणु
		set_bit(CONN_WD_ST_CHG_OKAY, &connection->flags);
	पूर्ण अन्यथा अणु
		set_bit(CONN_WD_ST_CHG_FAIL, &connection->flags);
		drbd_err(connection, "Requested state change failed by peer: %s (%d)\n",
			 drbd_set_st_err_str(retcode), retcode);
	पूर्ण
	wake_up(&connection->ping_रुको);

	वापस 0;
पूर्ण

अटल पूर्णांक got_RqSReply(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_req_state_reply *p = pi->data;
	पूर्णांक retcode = be32_to_cpu(p->retcode);

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	अगर (test_bit(CONN_WD_ST_CHG_REQ, &connection->flags)) अणु
		D_ASSERT(device, connection->agreed_pro_version < 100);
		वापस got_conn_RqSReply(connection, pi);
	पूर्ण

	अगर (retcode >= SS_SUCCESS) अणु
		set_bit(CL_ST_CHG_SUCCESS, &device->flags);
	पूर्ण अन्यथा अणु
		set_bit(CL_ST_CHG_FAIL, &device->flags);
		drbd_err(device, "Requested state change failed by peer: %s (%d)\n",
			drbd_set_st_err_str(retcode), retcode);
	पूर्ण
	wake_up(&device->state_रुको);

	वापस 0;
पूर्ण

अटल पूर्णांक got_Ping(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	वापस drbd_send_ping_ack(connection);

पूर्ण

अटल पूर्णांक got_PingAck(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	/* restore idle समयout */
	connection->meta.socket->sk->sk_rcvसमयo = connection->net_conf->ping_पूर्णांक*HZ;
	अगर (!test_and_set_bit(GOT_PING_ACK, &connection->flags))
		wake_up(&connection->ping_रुको);

	वापस 0;
पूर्ण

अटल पूर्णांक got_IsInSync(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_block_ack *p = pi->data;
	sector_t sector = be64_to_cpu(p->sector);
	पूर्णांक blksize = be32_to_cpu(p->blksize);

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	D_ASSERT(device, peer_device->connection->agreed_pro_version >= 89);

	update_peer_seq(peer_device, be32_to_cpu(p->seq_num));

	अगर (get_ldev(device)) अणु
		drbd_rs_complete_io(device, sector);
		drbd_set_in_sync(device, sector, blksize);
		/* rs_same_csums is supposed to count in units of BM_BLOCK_SIZE */
		device->rs_same_csum += (blksize >> BM_BLOCK_SHIFT);
		put_ldev(device);
	पूर्ण
	dec_rs_pending(device);
	atomic_add(blksize >> 9, &device->rs_sect_in);

	वापस 0;
पूर्ण

अटल पूर्णांक
validate_req_change_req_state(काष्ठा drbd_device *device, u64 id, sector_t sector,
			      काष्ठा rb_root *root, स्थिर अक्षर *func,
			      क्रमागत drbd_req_event what, bool missing_ok)
अणु
	काष्ठा drbd_request *req;
	काष्ठा bio_and_error m;

	spin_lock_irq(&device->resource->req_lock);
	req = find_request(device, root, id, sector, missing_ok, func);
	अगर (unlikely(!req)) अणु
		spin_unlock_irq(&device->resource->req_lock);
		वापस -EIO;
	पूर्ण
	__req_mod(req, what, &m);
	spin_unlock_irq(&device->resource->req_lock);

	अगर (m.bio)
		complete_master_bio(device, &m);
	वापस 0;
पूर्ण

अटल पूर्णांक got_BlockAck(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_block_ack *p = pi->data;
	sector_t sector = be64_to_cpu(p->sector);
	पूर्णांक blksize = be32_to_cpu(p->blksize);
	क्रमागत drbd_req_event what;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	update_peer_seq(peer_device, be32_to_cpu(p->seq_num));

	अगर (p->block_id == ID_SYNCER) अणु
		drbd_set_in_sync(device, sector, blksize);
		dec_rs_pending(device);
		वापस 0;
	पूर्ण
	चयन (pi->cmd) अणु
	हाल P_RS_WRITE_ACK:
		what = WRITE_ACKED_BY_PEER_AND_SIS;
		अवरोध;
	हाल P_WRITE_ACK:
		what = WRITE_ACKED_BY_PEER;
		अवरोध;
	हाल P_RECV_ACK:
		what = RECV_ACKED_BY_PEER;
		अवरोध;
	हाल P_SUPERSEDED:
		what = CONFLICT_RESOLVED;
		अवरोध;
	हाल P_RETRY_WRITE:
		what = POSTPONE_WRITE;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस validate_req_change_req_state(device, p->block_id, sector,
					     &device->ग_लिखो_requests, __func__,
					     what, false);
पूर्ण

अटल पूर्णांक got_NegAck(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_block_ack *p = pi->data;
	sector_t sector = be64_to_cpu(p->sector);
	पूर्णांक size = be32_to_cpu(p->blksize);
	पूर्णांक err;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	update_peer_seq(peer_device, be32_to_cpu(p->seq_num));

	अगर (p->block_id == ID_SYNCER) अणु
		dec_rs_pending(device);
		drbd_rs_failed_io(device, sector, size);
		वापस 0;
	पूर्ण

	err = validate_req_change_req_state(device, p->block_id, sector,
					    &device->ग_लिखो_requests, __func__,
					    NEG_ACKED, true);
	अगर (err) अणु
		/* Protocol A has no P_WRITE_ACKs, but has P_NEG_ACKs.
		   The master bio might alपढ़ोy be completed, thereक्रमe the
		   request is no दीर्घer in the collision hash. */
		/* In Protocol B we might alपढ़ोy have got a P_RECV_ACK
		   but then get a P_NEG_ACK afterwards. */
		drbd_set_out_of_sync(device, sector, size);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक got_NegDReply(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_block_ack *p = pi->data;
	sector_t sector = be64_to_cpu(p->sector);

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	update_peer_seq(peer_device, be32_to_cpu(p->seq_num));

	drbd_err(device, "Got NegDReply; Sector %llus, len %u.\n",
	    (अचिन्हित दीर्घ दीर्घ)sector, be32_to_cpu(p->blksize));

	वापस validate_req_change_req_state(device, p->block_id, sector,
					     &device->पढ़ो_requests, __func__,
					     NEG_ACKED, false);
पूर्ण

अटल पूर्णांक got_NegRSDReply(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	sector_t sector;
	पूर्णांक size;
	काष्ठा p_block_ack *p = pi->data;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	sector = be64_to_cpu(p->sector);
	size = be32_to_cpu(p->blksize);

	update_peer_seq(peer_device, be32_to_cpu(p->seq_num));

	dec_rs_pending(device);

	अगर (get_ldev_अगर_state(device, D_FAILED)) अणु
		drbd_rs_complete_io(device, sector);
		चयन (pi->cmd) अणु
		हाल P_NEG_RS_DREPLY:
			drbd_rs_failed_io(device, sector, size);
			अवरोध;
		हाल P_RS_CANCEL:
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		put_ldev(device);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक got_BarrierAck(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा p_barrier_ack *p = pi->data;
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	tl_release(connection, p->barrier, be32_to_cpu(p->set_size));

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;

		अगर (device->state.conn == C_AHEAD &&
		    atomic_पढ़ो(&device->ap_in_flight) == 0 &&
		    !test_and_set_bit(AHEAD_TO_SYNC_SOURCE, &device->flags)) अणु
			device->start_resync_समयr.expires = jअगरfies + HZ;
			add_समयr(&device->start_resync_समयr);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक got_OVResult(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_device *device;
	काष्ठा p_block_ack *p = pi->data;
	काष्ठा drbd_device_work *dw;
	sector_t sector;
	पूर्णांक size;

	peer_device = conn_peer_device(connection, pi->vnr);
	अगर (!peer_device)
		वापस -EIO;
	device = peer_device->device;

	sector = be64_to_cpu(p->sector);
	size = be32_to_cpu(p->blksize);

	update_peer_seq(peer_device, be32_to_cpu(p->seq_num));

	अगर (be64_to_cpu(p->block_id) == ID_OUT_OF_SYNC)
		drbd_ov_out_of_sync_found(device, sector, size);
	अन्यथा
		ov_out_of_sync_prपूर्णांक(device);

	अगर (!get_ldev(device))
		वापस 0;

	drbd_rs_complete_io(device, sector);
	dec_rs_pending(device);

	--device->ov_left;

	/* let's advance progress step marks only क्रम every other megabyte */
	अगर ((device->ov_left & 0x200) == 0x200)
		drbd_advance_rs_marks(device, device->ov_left);

	अगर (device->ov_left == 0) अणु
		dw = kदो_स्मृति(माप(*dw), GFP_NOIO);
		अगर (dw) अणु
			dw->w.cb = w_ov_finished;
			dw->device = device;
			drbd_queue_work(&peer_device->connection->sender_work, &dw->w);
		पूर्ण अन्यथा अणु
			drbd_err(device, "kmalloc(dw) failed.");
			ov_out_of_sync_prपूर्णांक(device);
			drbd_resync_finished(device);
		पूर्ण
	पूर्ण
	put_ldev(device);
	वापस 0;
पूर्ण

अटल पूर्णांक got_skip(काष्ठा drbd_connection *connection, काष्ठा packet_info *pi)
अणु
	वापस 0;
पूर्ण

काष्ठा meta_sock_cmd अणु
	माप_प्रकार pkt_size;
	पूर्णांक (*fn)(काष्ठा drbd_connection *connection, काष्ठा packet_info *);
पूर्ण;

अटल व्योम set_rcvसमयo(काष्ठा drbd_connection *connection, bool ping_समयout)
अणु
	दीर्घ t;
	काष्ठा net_conf *nc;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	t = ping_समयout ? nc->ping_समयo : nc->ping_पूर्णांक;
	rcu_पढ़ो_unlock();

	t *= HZ;
	अगर (ping_समयout)
		t /= 10;

	connection->meta.socket->sk->sk_rcvसमयo = t;
पूर्ण

अटल व्योम set_ping_समयout(काष्ठा drbd_connection *connection)
अणु
	set_rcvसमयo(connection, 1);
पूर्ण

अटल व्योम set_idle_समयout(काष्ठा drbd_connection *connection)
अणु
	set_rcvसमयo(connection, 0);
पूर्ण

अटल काष्ठा meta_sock_cmd ack_receiver_tbl[] = अणु
	[P_PING]	    = अणु 0, got_Ping पूर्ण,
	[P_PING_ACK]	    = अणु 0, got_PingAck पूर्ण,
	[P_RECV_ACK]	    = अणु माप(काष्ठा p_block_ack), got_BlockAck पूर्ण,
	[P_WRITE_ACK]	    = अणु माप(काष्ठा p_block_ack), got_BlockAck पूर्ण,
	[P_RS_WRITE_ACK]    = अणु माप(काष्ठा p_block_ack), got_BlockAck पूर्ण,
	[P_SUPERSEDED]   = अणु माप(काष्ठा p_block_ack), got_BlockAck पूर्ण,
	[P_NEG_ACK]	    = अणु माप(काष्ठा p_block_ack), got_NegAck पूर्ण,
	[P_NEG_DREPLY]	    = अणु माप(काष्ठा p_block_ack), got_NegDReply पूर्ण,
	[P_NEG_RS_DREPLY]   = अणु माप(काष्ठा p_block_ack), got_NegRSDReply पूर्ण,
	[P_OV_RESULT]	    = अणु माप(काष्ठा p_block_ack), got_OVResult पूर्ण,
	[P_BARRIER_ACK]	    = अणु माप(काष्ठा p_barrier_ack), got_BarrierAck पूर्ण,
	[P_STATE_CHG_REPLY] = अणु माप(काष्ठा p_req_state_reply), got_RqSReply पूर्ण,
	[P_RS_IS_IN_SYNC]   = अणु माप(काष्ठा p_block_ack), got_IsInSync पूर्ण,
	[P_DELAY_PROBE]     = अणु माप(काष्ठा p_delay_probe93), got_skip पूर्ण,
	[P_RS_CANCEL]       = अणु माप(काष्ठा p_block_ack), got_NegRSDReply पूर्ण,
	[P_CONN_ST_CHG_REPLY]=अणु माप(काष्ठा p_req_state_reply), got_conn_RqSReply पूर्ण,
	[P_RETRY_WRITE]	    = अणु माप(काष्ठा p_block_ack), got_BlockAck पूर्ण,
पूर्ण;

पूर्णांक drbd_ack_receiver(काष्ठा drbd_thपढ़ो *thi)
अणु
	काष्ठा drbd_connection *connection = thi->connection;
	काष्ठा meta_sock_cmd *cmd = शून्य;
	काष्ठा packet_info pi;
	अचिन्हित दीर्घ pre_recv_jअगर;
	पूर्णांक rv;
	व्योम *buf    = connection->meta.rbuf;
	पूर्णांक received = 0;
	अचिन्हित पूर्णांक header_size = drbd_header_size(connection);
	पूर्णांक expect   = header_size;
	bool ping_समयout_active = false;

	sched_set_fअगरo_low(current);

	जबतक (get_t_state(thi) == RUNNING) अणु
		drbd_thपढ़ो_current_set_cpu(thi);

		conn_reclaim_net_peer_reqs(connection);

		अगर (test_and_clear_bit(SEND_PING, &connection->flags)) अणु
			अगर (drbd_send_ping(connection)) अणु
				drbd_err(connection, "drbd_send_ping has failed\n");
				जाओ reconnect;
			पूर्ण
			set_ping_समयout(connection);
			ping_समयout_active = true;
		पूर्ण

		pre_recv_jअगर = jअगरfies;
		rv = drbd_recv_लघु(connection->meta.socket, buf, expect-received, 0);

		/* Note:
		 * -EINTR	 (on meta) we got a संकेत
		 * -EAGAIN	 (on meta) rcvसमयo expired
		 * -ECONNRESET	 other side बंदd the connection
		 * -ERESTARTSYS  (on data) we got a संकेत
		 * rv <  0	 other than above: unexpected error!
		 * rv == expected: full header or command
		 * rv <  expected: "woken" by संकेत during receive
		 * rv == 0	 : "connection shut down by peer"
		 */
		अगर (likely(rv > 0)) अणु
			received += rv;
			buf	 += rv;
		पूर्ण अन्यथा अगर (rv == 0) अणु
			अगर (test_bit(DISCONNECT_SENT, &connection->flags)) अणु
				दीर्घ t;
				rcu_पढ़ो_lock();
				t = rcu_dereference(connection->net_conf)->ping_समयo * HZ/10;
				rcu_पढ़ो_unlock();

				t = रुको_event_समयout(connection->ping_रुको,
						       connection->cstate < C_WF_REPORT_PARAMS,
						       t);
				अगर (t)
					अवरोध;
			पूर्ण
			drbd_err(connection, "meta connection shut down by peer.\n");
			जाओ reconnect;
		पूर्ण अन्यथा अगर (rv == -EAGAIN) अणु
			/* If the data socket received something meanजबतक,
			 * that is good enough: peer is still alive. */
			अगर (समय_after(connection->last_received, pre_recv_jअगर))
				जारी;
			अगर (ping_समयout_active) अणु
				drbd_err(connection, "PingAck did not arrive in time.\n");
				जाओ reconnect;
			पूर्ण
			set_bit(SEND_PING, &connection->flags);
			जारी;
		पूर्ण अन्यथा अगर (rv == -EINTR) अणु
			/* maybe drbd_thपढ़ो_stop(): the जबतक condition will notice.
			 * maybe woken क्रम send_ping: we'll send a ping above,
			 * and change the rcvसमयo */
			flush_संकेतs(current);
			जारी;
		पूर्ण अन्यथा अणु
			drbd_err(connection, "sock_recvmsg returned %d\n", rv);
			जाओ reconnect;
		पूर्ण

		अगर (received == expect && cmd == शून्य) अणु
			अगर (decode_header(connection, connection->meta.rbuf, &pi))
				जाओ reconnect;
			cmd = &ack_receiver_tbl[pi.cmd];
			अगर (pi.cmd >= ARRAY_SIZE(ack_receiver_tbl) || !cmd->fn) अणु
				drbd_err(connection, "Unexpected meta packet %s (0x%04x)\n",
					 cmdname(pi.cmd), pi.cmd);
				जाओ disconnect;
			पूर्ण
			expect = header_size + cmd->pkt_size;
			अगर (pi.size != expect - header_size) अणु
				drbd_err(connection, "Wrong packet size on meta (c: %d, l: %d)\n",
					pi.cmd, pi.size);
				जाओ reconnect;
			पूर्ण
		पूर्ण
		अगर (received == expect) अणु
			bool err;

			err = cmd->fn(connection, &pi);
			अगर (err) अणु
				drbd_err(connection, "%ps failed\n", cmd->fn);
				जाओ reconnect;
			पूर्ण

			connection->last_received = jअगरfies;

			अगर (cmd == &ack_receiver_tbl[P_PING_ACK]) अणु
				set_idle_समयout(connection);
				ping_समयout_active = false;
			पूर्ण

			buf	 = connection->meta.rbuf;
			received = 0;
			expect	 = header_size;
			cmd	 = शून्य;
		पूर्ण
	पूर्ण

	अगर (0) अणु
reconnect:
		conn_request_state(connection, NS(conn, C_NETWORK_FAILURE), CS_HARD);
		conn_md_sync(connection);
	पूर्ण
	अगर (0) अणु
disconnect:
		conn_request_state(connection, NS(conn, C_DISCONNECTING), CS_HARD);
	पूर्ण

	drbd_info(connection, "ack_receiver terminated\n");

	वापस 0;
पूर्ण

व्योम drbd_send_acks_wf(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा drbd_peer_device *peer_device =
		container_of(ws, काष्ठा drbd_peer_device, send_acks_work);
	काष्ठा drbd_connection *connection = peer_device->connection;
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा net_conf *nc;
	पूर्णांक tcp_cork, err;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	tcp_cork = nc->tcp_cork;
	rcu_पढ़ो_unlock();

	अगर (tcp_cork)
		tcp_sock_set_cork(connection->meta.socket->sk, true);

	err = drbd_finish_peer_reqs(device);
	kref_put(&device->kref, drbd_destroy_device);
	/* get is in drbd_endio_ग_लिखो_sec_final(). That is necessary to keep the
	   काष्ठा work_काष्ठा send_acks_work alive, which is in the peer_device object */

	अगर (err) अणु
		conn_request_state(connection, NS(conn, C_NETWORK_FAILURE), CS_HARD);
		वापस;
	पूर्ण

	अगर (tcp_cork)
		tcp_sock_set_cork(connection->meta.socket->sk, false);

	वापस;
पूर्ण
