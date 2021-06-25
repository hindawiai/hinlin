<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   drbd_req.c

   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2001-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 1999-2008, Philipp Reisner <philipp.reisner@linbit.com>.
   Copyright (C) 2002-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.


 */

#समावेश <linux/module.h>

#समावेश <linux/slab.h>
#समावेश <linux/drbd.h>
#समावेश "drbd_int.h"
#समावेश "drbd_req.h"


अटल bool drbd_may_करो_local_पढ़ो(काष्ठा drbd_device *device, sector_t sector, पूर्णांक size);

अटल काष्ठा drbd_request *drbd_req_new(काष्ठा drbd_device *device, काष्ठा bio *bio_src)
अणु
	काष्ठा drbd_request *req;

	req = mempool_alloc(&drbd_request_mempool, GFP_NOIO);
	अगर (!req)
		वापस शून्य;
	स_रखो(req, 0, माप(*req));

	req->निजी_bio = bio_clone_fast(bio_src, GFP_NOIO, &drbd_io_bio_set);
	req->निजी_bio->bi_निजी = req;
	req->निजी_bio->bi_end_io = drbd_request_endio;

	req->rq_state = (bio_data_dir(bio_src) == WRITE ? RQ_WRITE : 0)
		      | (bio_op(bio_src) == REQ_OP_WRITE_SAME ? RQ_WSAME : 0)
		      | (bio_op(bio_src) == REQ_OP_WRITE_ZEROES ? RQ_ZEROES : 0)
		      | (bio_op(bio_src) == REQ_OP_DISCARD ? RQ_UNMAP : 0);
	req->device = device;
	req->master_bio = bio_src;
	req->epoch = 0;

	drbd_clear_पूर्णांकerval(&req->i);
	req->i.sector     = bio_src->bi_iter.bi_sector;
	req->i.size      = bio_src->bi_iter.bi_size;
	req->i.local = true;
	req->i.रुकोing = false;

	INIT_LIST_HEAD(&req->tl_requests);
	INIT_LIST_HEAD(&req->w.list);
	INIT_LIST_HEAD(&req->req_pending_master_completion);
	INIT_LIST_HEAD(&req->req_pending_local);

	/* one reference to be put by __drbd_make_request */
	atomic_set(&req->completion_ref, 1);
	/* one kref as दीर्घ as completion_ref > 0 */
	kref_init(&req->kref);
	वापस req;
पूर्ण

अटल व्योम drbd_हटाओ_request_पूर्णांकerval(काष्ठा rb_root *root,
					 काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_device *device = req->device;
	काष्ठा drbd_पूर्णांकerval *i = &req->i;

	drbd_हटाओ_पूर्णांकerval(root, i);

	/* Wake up any processes रुकोing क्रम this request to complete.  */
	अगर (i->रुकोing)
		wake_up(&device->misc_रुको);
पूर्ण

व्योम drbd_req_destroy(काष्ठा kref *kref)
अणु
	काष्ठा drbd_request *req = container_of(kref, काष्ठा drbd_request, kref);
	काष्ठा drbd_device *device = req->device;
	स्थिर अचिन्हित s = req->rq_state;

	अगर ((req->master_bio && !(s & RQ_POSTPONED)) ||
		atomic_पढ़ो(&req->completion_ref) ||
		(s & RQ_LOCAL_PENDING) ||
		((s & RQ_NET_MASK) && !(s & RQ_NET_DONE))) अणु
		drbd_err(device, "drbd_req_destroy: Logic BUG rq_state = 0x%x, completion_ref = %d\n",
				s, atomic_पढ़ो(&req->completion_ref));
		वापस;
	पूर्ण

	/* If called from mod_rq_state (expected normal हाल) or
	 * drbd_send_and_submit (the less likely normal path), this holds the
	 * req_lock, and req->tl_requests will typicaly be on ->transfer_log,
	 * though it may be still empty (never added to the transfer log).
	 *
	 * If called from करो_retry(), we करो NOT hold the req_lock, but we are
	 * still allowed to unconditionally list_del(&req->tl_requests),
	 * because it will be on a local on-stack list only. */
	list_del_init(&req->tl_requests);

	/* finally हटाओ the request from the conflict detection
	 * respective block_id verअगरication पूर्णांकerval tree. */
	अगर (!drbd_पूर्णांकerval_empty(&req->i)) अणु
		काष्ठा rb_root *root;

		अगर (s & RQ_WRITE)
			root = &device->ग_लिखो_requests;
		अन्यथा
			root = &device->पढ़ो_requests;
		drbd_हटाओ_request_पूर्णांकerval(root, req);
	पूर्ण अन्यथा अगर (s & (RQ_NET_MASK & ~RQ_NET_DONE) && req->i.size != 0)
		drbd_err(device, "drbd_req_destroy: Logic BUG: interval empty, but: rq_state=0x%x, sect=%llu, size=%u\n",
			s, (अचिन्हित दीर्घ दीर्घ)req->i.sector, req->i.size);

	/* अगर it was a ग_लिखो, we may have to set the corresponding
	 * bit(s) out-of-sync first. If it had a local part, we need to
	 * release the reference to the activity log. */
	अगर (s & RQ_WRITE) अणु
		/* Set out-of-sync unless both OK flags are set
		 * (local only or remote failed).
		 * Other places where we set out-of-sync:
		 * READ with local io-error */

		/* There is a special हाल:
		 * we may notice late that IO was suspended,
		 * and postpone, or schedule क्रम retry, a ग_लिखो,
		 * beक्रमe it even was submitted or sent.
		 * In that हाल we करो not want to touch the biपंचांगap at all.
		 */
		अगर ((s & (RQ_POSTPONED|RQ_LOCAL_MASK|RQ_NET_MASK)) != RQ_POSTPONED) अणु
			अगर (!(s & RQ_NET_OK) || !(s & RQ_LOCAL_OK))
				drbd_set_out_of_sync(device, req->i.sector, req->i.size);

			अगर ((s & RQ_NET_OK) && (s & RQ_LOCAL_OK) && (s & RQ_NET_SIS))
				drbd_set_in_sync(device, req->i.sector, req->i.size);
		पूर्ण

		/* one might be tempted to move the drbd_al_complete_io
		 * to the local io completion callback drbd_request_endio.
		 * but, अगर this was a mirror ग_लिखो, we may only
		 * drbd_al_complete_io after this is RQ_NET_DONE,
		 * otherwise the extent could be dropped from the al
		 * beक्रमe it has actually been written on the peer.
		 * अगर we crash beक्रमe our peer knows about the request,
		 * but after the extent has been dropped from the al,
		 * we would क्रमget to resync the corresponding extent.
		 */
		अगर (s & RQ_IN_ACT_LOG) अणु
			अगर (get_ldev_अगर_state(device, D_FAILED)) अणु
				drbd_al_complete_io(device, &req->i);
				put_ldev(device);
			पूर्ण अन्यथा अगर (__ratelimit(&drbd_ratelimit_state)) अणु
				drbd_warn(device, "Should have called drbd_al_complete_io(, %llu, %u), "
					 "but my Disk seems to have failed :(\n",
					 (अचिन्हित दीर्घ दीर्घ) req->i.sector, req->i.size);
			पूर्ण
		पूर्ण
	पूर्ण

	mempool_मुक्त(req, &drbd_request_mempool);
पूर्ण

अटल व्योम wake_all_senders(काष्ठा drbd_connection *connection)
अणु
	wake_up(&connection->sender_work.q_रुको);
पूर्ण

/* must hold resource->req_lock */
व्योम start_new_tl_epoch(काष्ठा drbd_connection *connection)
अणु
	/* no poपूर्णांक closing an epoch, अगर it is empty, anyways. */
	अगर (connection->current_tle_ग_लिखोs == 0)
		वापस;

	connection->current_tle_ग_लिखोs = 0;
	atomic_inc(&connection->current_tle_nr);
	wake_all_senders(connection);
पूर्ण

व्योम complete_master_bio(काष्ठा drbd_device *device,
		काष्ठा bio_and_error *m)
अणु
	m->bio->bi_status = त्रुटि_सं_to_blk_status(m->error);
	bio_endio(m->bio);
	dec_ap_bio(device);
पूर्ण


/* Helper क्रम __req_mod().
 * Set m->bio to the master bio, अगर it is fit to be completed,
 * or leave it alone (it is initialized to शून्य in __req_mod),
 * अगर it has alपढ़ोy been completed, or cannot be completed yet.
 * If m->bio is set, the error status to be वापसed is placed in m->error.
 */
अटल
व्योम drbd_req_complete(काष्ठा drbd_request *req, काष्ठा bio_and_error *m)
अणु
	स्थिर अचिन्हित s = req->rq_state;
	काष्ठा drbd_device *device = req->device;
	पूर्णांक error, ok;

	/* we must not complete the master bio, जबतक it is
	 *	still being processed by _drbd_send_zc_bio (drbd_send_dblock)
	 *	not yet acknowledged by the peer
	 *	not yet completed by the local io subप्रणाली
	 * these flags may get cleared in any order by
	 *	the worker,
	 *	the receiver,
	 *	the bio_endio completion callbacks.
	 */
	अगर ((s & RQ_LOCAL_PENDING && !(s & RQ_LOCAL_ABORTED)) ||
	    (s & RQ_NET_QUEUED) || (s & RQ_NET_PENDING) ||
	    (s & RQ_COMPLETION_SUSP)) अणु
		drbd_err(device, "drbd_req_complete: Logic BUG rq_state = 0x%x\n", s);
		वापस;
	पूर्ण

	अगर (!req->master_bio) अणु
		drbd_err(device, "drbd_req_complete: Logic BUG, master_bio == NULL!\n");
		वापस;
	पूर्ण

	/*
	 * figure out whether to report success or failure.
	 *
	 * report success when at least one of the operations succeeded.
	 * or, to put the other way,
	 * only report failure, when both operations failed.
	 *
	 * what to करो about the failures is handled अन्यथाwhere.
	 * what we need to करो here is just: complete the master_bio.
	 *
	 * local completion error, अगर any, has been stored as ERR_PTR
	 * in निजी_bio within drbd_request_endio.
	 */
	ok = (s & RQ_LOCAL_OK) || (s & RQ_NET_OK);
	error = PTR_ERR(req->निजी_bio);

	/* Beक्रमe we can संकेत completion to the upper layers,
	 * we may need to बंद the current transfer log epoch.
	 * We are within the request lock, so we can simply compare
	 * the request epoch number with the current transfer log
	 * epoch number.  If they match, increase the current_tle_nr,
	 * and reset the transfer log epoch ग_लिखो_cnt.
	 */
	अगर (op_is_ग_लिखो(bio_op(req->master_bio)) &&
	    req->epoch == atomic_पढ़ो(&first_peer_device(device)->connection->current_tle_nr))
		start_new_tl_epoch(first_peer_device(device)->connection);

	/* Update disk stats */
	bio_end_io_acct(req->master_bio, req->start_jअगर);

	/* If READ failed,
	 * have it be pushed back to the retry work queue,
	 * so it will re-enter __drbd_make_request(),
	 * and be re-asचिन्हित to a suitable local or remote path,
	 * or failed अगर we करो not have access to good data anymore.
	 *
	 * Unless it was failed early by __drbd_make_request(),
	 * because no path was available, in which हाल
	 * it was not even added to the transfer_log.
	 *
	 * पढ़ो-ahead may fail, and will not be retried.
	 *
	 * WRITE should have used all available paths alपढ़ोy.
	 */
	अगर (!ok &&
	    bio_op(req->master_bio) == REQ_OP_READ &&
	    !(req->master_bio->bi_opf & REQ_RAHEAD) &&
	    !list_empty(&req->tl_requests))
		req->rq_state |= RQ_POSTPONED;

	अगर (!(req->rq_state & RQ_POSTPONED)) अणु
		m->error = ok ? 0 : (error ?: -EIO);
		m->bio = req->master_bio;
		req->master_bio = शून्य;
		/* We leave it in the tree, to be able to verअगरy later
		 * ग_लिखो-acks in protocol != C during resync.
		 * But we mark it as "complete", so it won't be counted as
		 * conflict in a multi-primary setup. */
		req->i.completed = true;
	पूर्ण

	अगर (req->i.रुकोing)
		wake_up(&device->misc_रुको);

	/* Either we are about to complete to upper layers,
	 * or we will restart this request.
	 * In either हाल, the request object will be destroyed soon,
	 * so better हटाओ it from all lists. */
	list_del_init(&req->req_pending_master_completion);
पूर्ण

/* still holds resource->req_lock */
अटल व्योम drbd_req_put_completion_ref(काष्ठा drbd_request *req, काष्ठा bio_and_error *m, पूर्णांक put)
अणु
	काष्ठा drbd_device *device = req->device;
	D_ASSERT(device, m || (req->rq_state & RQ_POSTPONED));

	अगर (!put)
		वापस;

	अगर (!atomic_sub_and_test(put, &req->completion_ref))
		वापस;

	drbd_req_complete(req, m);

	/* local completion may still come in later,
	 * we need to keep the req object around. */
	अगर (req->rq_state & RQ_LOCAL_ABORTED)
		वापस;

	अगर (req->rq_state & RQ_POSTPONED) अणु
		/* करोn't destroy the req object just yet,
		 * but queue it क्रम retry */
		drbd_restart_request(req);
		वापस;
	पूर्ण

	kref_put(&req->kref, drbd_req_destroy);
पूर्ण

अटल व्योम set_अगर_null_req_next(काष्ठा drbd_peer_device *peer_device, काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_connection *connection = peer_device ? peer_device->connection : शून्य;
	अगर (!connection)
		वापस;
	अगर (connection->req_next == शून्य)
		connection->req_next = req;
पूर्ण

अटल व्योम advance_conn_req_next(काष्ठा drbd_peer_device *peer_device, काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_connection *connection = peer_device ? peer_device->connection : शून्य;
	अगर (!connection)
		वापस;
	अगर (connection->req_next != req)
		वापस;
	list_क्रम_each_entry_जारी(req, &connection->transfer_log, tl_requests) अणु
		स्थिर अचिन्हित s = req->rq_state;
		अगर (s & RQ_NET_QUEUED)
			अवरोध;
	पूर्ण
	अगर (&req->tl_requests == &connection->transfer_log)
		req = शून्य;
	connection->req_next = req;
पूर्ण

अटल व्योम set_अगर_null_req_ack_pending(काष्ठा drbd_peer_device *peer_device, काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_connection *connection = peer_device ? peer_device->connection : शून्य;
	अगर (!connection)
		वापस;
	अगर (connection->req_ack_pending == शून्य)
		connection->req_ack_pending = req;
पूर्ण

अटल व्योम advance_conn_req_ack_pending(काष्ठा drbd_peer_device *peer_device, काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_connection *connection = peer_device ? peer_device->connection : शून्य;
	अगर (!connection)
		वापस;
	अगर (connection->req_ack_pending != req)
		वापस;
	list_क्रम_each_entry_जारी(req, &connection->transfer_log, tl_requests) अणु
		स्थिर अचिन्हित s = req->rq_state;
		अगर ((s & RQ_NET_SENT) && (s & RQ_NET_PENDING))
			अवरोध;
	पूर्ण
	अगर (&req->tl_requests == &connection->transfer_log)
		req = शून्य;
	connection->req_ack_pending = req;
पूर्ण

अटल व्योम set_अगर_null_req_not_net_करोne(काष्ठा drbd_peer_device *peer_device, काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_connection *connection = peer_device ? peer_device->connection : शून्य;
	अगर (!connection)
		वापस;
	अगर (connection->req_not_net_करोne == शून्य)
		connection->req_not_net_करोne = req;
पूर्ण

अटल व्योम advance_conn_req_not_net_करोne(काष्ठा drbd_peer_device *peer_device, काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_connection *connection = peer_device ? peer_device->connection : शून्य;
	अगर (!connection)
		वापस;
	अगर (connection->req_not_net_करोne != req)
		वापस;
	list_क्रम_each_entry_जारी(req, &connection->transfer_log, tl_requests) अणु
		स्थिर अचिन्हित s = req->rq_state;
		अगर ((s & RQ_NET_SENT) && !(s & RQ_NET_DONE))
			अवरोध;
	पूर्ण
	अगर (&req->tl_requests == &connection->transfer_log)
		req = शून्य;
	connection->req_not_net_करोne = req;
पूर्ण

/* I'd like this to be the only place that manipulates
 * req->completion_ref and req->kref. */
अटल व्योम mod_rq_state(काष्ठा drbd_request *req, काष्ठा bio_and_error *m,
		पूर्णांक clear, पूर्णांक set)
अणु
	काष्ठा drbd_device *device = req->device;
	काष्ठा drbd_peer_device *peer_device = first_peer_device(device);
	अचिन्हित s = req->rq_state;
	पूर्णांक c_put = 0;

	अगर (drbd_suspended(device) && !((s | clear) & RQ_COMPLETION_SUSP))
		set |= RQ_COMPLETION_SUSP;

	/* apply */

	req->rq_state &= ~clear;
	req->rq_state |= set;

	/* no change? */
	अगर (req->rq_state == s)
		वापस;

	/* पूर्णांकent: get references */

	kref_get(&req->kref);

	अगर (!(s & RQ_LOCAL_PENDING) && (set & RQ_LOCAL_PENDING))
		atomic_inc(&req->completion_ref);

	अगर (!(s & RQ_NET_PENDING) && (set & RQ_NET_PENDING)) अणु
		inc_ap_pending(device);
		atomic_inc(&req->completion_ref);
	पूर्ण

	अगर (!(s & RQ_NET_QUEUED) && (set & RQ_NET_QUEUED)) अणु
		atomic_inc(&req->completion_ref);
		set_अगर_null_req_next(peer_device, req);
	पूर्ण

	अगर (!(s & RQ_EXP_BARR_ACK) && (set & RQ_EXP_BARR_ACK))
		kref_get(&req->kref); /* रुको क्रम the DONE */

	अगर (!(s & RQ_NET_SENT) && (set & RQ_NET_SENT)) अणु
		/* potentially alपढ़ोy completed in the ack_receiver thपढ़ो */
		अगर (!(s & RQ_NET_DONE)) अणु
			atomic_add(req->i.size >> 9, &device->ap_in_flight);
			set_अगर_null_req_not_net_करोne(peer_device, req);
		पूर्ण
		अगर (req->rq_state & RQ_NET_PENDING)
			set_अगर_null_req_ack_pending(peer_device, req);
	पूर्ण

	अगर (!(s & RQ_COMPLETION_SUSP) && (set & RQ_COMPLETION_SUSP))
		atomic_inc(&req->completion_ref);

	/* progress: put references */

	अगर ((s & RQ_COMPLETION_SUSP) && (clear & RQ_COMPLETION_SUSP))
		++c_put;

	अगर (!(s & RQ_LOCAL_ABORTED) && (set & RQ_LOCAL_ABORTED)) अणु
		D_ASSERT(device, req->rq_state & RQ_LOCAL_PENDING);
		++c_put;
	पूर्ण

	अगर ((s & RQ_LOCAL_PENDING) && (clear & RQ_LOCAL_PENDING)) अणु
		अगर (req->rq_state & RQ_LOCAL_ABORTED)
			kref_put(&req->kref, drbd_req_destroy);
		अन्यथा
			++c_put;
		list_del_init(&req->req_pending_local);
	पूर्ण

	अगर ((s & RQ_NET_PENDING) && (clear & RQ_NET_PENDING)) अणु
		dec_ap_pending(device);
		++c_put;
		req->acked_jअगर = jअगरfies;
		advance_conn_req_ack_pending(peer_device, req);
	पूर्ण

	अगर ((s & RQ_NET_QUEUED) && (clear & RQ_NET_QUEUED)) अणु
		++c_put;
		advance_conn_req_next(peer_device, req);
	पूर्ण

	अगर (!(s & RQ_NET_DONE) && (set & RQ_NET_DONE)) अणु
		अगर (s & RQ_NET_SENT)
			atomic_sub(req->i.size >> 9, &device->ap_in_flight);
		अगर (s & RQ_EXP_BARR_ACK)
			kref_put(&req->kref, drbd_req_destroy);
		req->net_करोne_jअगर = jअगरfies;

		/* in ahead/behind mode, or just in हाल,
		 * beक्रमe we finally destroy this request,
		 * the caching poपूर्णांकers must not reference it anymore */
		advance_conn_req_next(peer_device, req);
		advance_conn_req_ack_pending(peer_device, req);
		advance_conn_req_not_net_करोne(peer_device, req);
	पूर्ण

	/* potentially complete and destroy */

	/* If we made progress, retry conflicting peer requests, अगर any. */
	अगर (req->i.रुकोing)
		wake_up(&device->misc_रुको);

	drbd_req_put_completion_ref(req, m, c_put);
	kref_put(&req->kref, drbd_req_destroy);
पूर्ण

अटल व्योम drbd_report_io_error(काष्ठा drbd_device *device, काष्ठा drbd_request *req)
अणु
        अक्षर b[BDEVNAME_SIZE];

	अगर (!__ratelimit(&drbd_ratelimit_state))
		वापस;

	drbd_warn(device, "local %s IO error sector %llu+%u on %s\n",
			(req->rq_state & RQ_WRITE) ? "WRITE" : "READ",
			(अचिन्हित दीर्घ दीर्घ)req->i.sector,
			req->i.size >> 9,
			bdevname(device->ldev->backing_bdev, b));
पूर्ण

/* Helper क्रम HANDED_OVER_TO_NETWORK.
 * Is this a protocol A ग_लिखो (neither WRITE_ACK nor RECEIVE_ACK expected)?
 * Is it also still "PENDING"?
 * --> If so, clear PENDING and set NET_OK below.
 * If it is a protocol A ग_लिखो, but not RQ_PENDING anymore, neg-ack was faster
 * (and we must not set RQ_NET_OK) */
अटल अंतरभूत bool is_pending_ग_लिखो_protocol_A(काष्ठा drbd_request *req)
अणु
	वापस (req->rq_state &
		   (RQ_WRITE|RQ_NET_PENDING|RQ_EXP_WRITE_ACK|RQ_EXP_RECEIVE_ACK))
		== (RQ_WRITE|RQ_NET_PENDING);
पूर्ण

/* obviously this could be coded as many single functions
 * instead of one huge चयन,
 * or by putting the code directly in the respective locations
 * (as it has been beक्रमe).
 *
 * but having it this way
 *  enक्रमces that it is all in this one place, where it is easier to audit,
 *  it makes it obvious that whatever "event" "happens" to a request should
 *  happen "atomically" within the req_lock,
 *  and it enक्रमces that we have to think in a very काष्ठाured manner
 *  about the "events" that may happen to a request during its lअगरe समय ...
 */
पूर्णांक __req_mod(काष्ठा drbd_request *req, क्रमागत drbd_req_event what,
		काष्ठा bio_and_error *m)
अणु
	काष्ठा drbd_device *स्थिर device = req->device;
	काष्ठा drbd_peer_device *स्थिर peer_device = first_peer_device(device);
	काष्ठा drbd_connection *स्थिर connection = peer_device ? peer_device->connection : शून्य;
	काष्ठा net_conf *nc;
	पूर्णांक p, rv = 0;

	अगर (m)
		m->bio = शून्य;

	चयन (what) अणु
	शेष:
		drbd_err(device, "LOGIC BUG in %s:%u\n", __खाता__ , __LINE__);
		अवरोध;

	/* करोes not happen...
	 * initialization करोne in drbd_req_new
	हाल CREATED:
		अवरोध;
		*/

	हाल TO_BE_SENT: /* via network */
		/* reached via __drbd_make_request
		 * and from w_पढ़ो_retry_remote */
		D_ASSERT(device, !(req->rq_state & RQ_NET_MASK));
		rcu_पढ़ो_lock();
		nc = rcu_dereference(connection->net_conf);
		p = nc->wire_protocol;
		rcu_पढ़ो_unlock();
		req->rq_state |=
			p == DRBD_PROT_C ? RQ_EXP_WRITE_ACK :
			p == DRBD_PROT_B ? RQ_EXP_RECEIVE_ACK : 0;
		mod_rq_state(req, m, 0, RQ_NET_PENDING);
		अवरोध;

	हाल TO_BE_SUBMITTED: /* locally */
		/* reached via __drbd_make_request */
		D_ASSERT(device, !(req->rq_state & RQ_LOCAL_MASK));
		mod_rq_state(req, m, 0, RQ_LOCAL_PENDING);
		अवरोध;

	हाल COMPLETED_OK:
		अगर (req->rq_state & RQ_WRITE)
			device->writ_cnt += req->i.size >> 9;
		अन्यथा
			device->पढ़ो_cnt += req->i.size >> 9;

		mod_rq_state(req, m, RQ_LOCAL_PENDING,
				RQ_LOCAL_COMPLETED|RQ_LOCAL_OK);
		अवरोध;

	हाल ABORT_DISK_IO:
		mod_rq_state(req, m, 0, RQ_LOCAL_ABORTED);
		अवरोध;

	हाल WRITE_COMPLETED_WITH_ERROR:
		drbd_report_io_error(device, req);
		__drbd_chk_io_error(device, DRBD_WRITE_ERROR);
		mod_rq_state(req, m, RQ_LOCAL_PENDING, RQ_LOCAL_COMPLETED);
		अवरोध;

	हाल READ_COMPLETED_WITH_ERROR:
		drbd_set_out_of_sync(device, req->i.sector, req->i.size);
		drbd_report_io_error(device, req);
		__drbd_chk_io_error(device, DRBD_READ_ERROR);
		fallthrough;
	हाल READ_AHEAD_COMPLETED_WITH_ERROR:
		/* it is legal to fail पढ़ो-ahead, no __drbd_chk_io_error in that हाल. */
		mod_rq_state(req, m, RQ_LOCAL_PENDING, RQ_LOCAL_COMPLETED);
		अवरोध;

	हाल DISCARD_COMPLETED_NOTSUPP:
	हाल DISCARD_COMPLETED_WITH_ERROR:
		/* I'd rather not detach from local disk just because it
		 * failed a REQ_OP_DISCARD. */
		mod_rq_state(req, m, RQ_LOCAL_PENDING, RQ_LOCAL_COMPLETED);
		अवरोध;

	हाल QUEUE_FOR_NET_READ:
		/* READ, and
		 * no local disk,
		 * or target area marked as invalid,
		 * or just got an io-error. */
		/* from __drbd_make_request
		 * or from bio_endio during पढ़ो io-error recovery */

		/* So we can verअगरy the handle in the answer packet.
		 * Corresponding drbd_हटाओ_request_पूर्णांकerval is in
		 * drbd_req_complete() */
		D_ASSERT(device, drbd_पूर्णांकerval_empty(&req->i));
		drbd_insert_पूर्णांकerval(&device->पढ़ो_requests, &req->i);

		set_bit(UNPLUG_REMOTE, &device->flags);

		D_ASSERT(device, req->rq_state & RQ_NET_PENDING);
		D_ASSERT(device, (req->rq_state & RQ_LOCAL_MASK) == 0);
		mod_rq_state(req, m, 0, RQ_NET_QUEUED);
		req->w.cb = w_send_पढ़ो_req;
		drbd_queue_work(&connection->sender_work,
				&req->w);
		अवरोध;

	हाल QUEUE_FOR_NET_WRITE:
		/* निश्चित something? */
		/* from __drbd_make_request only */

		/* Corresponding drbd_हटाओ_request_पूर्णांकerval is in
		 * drbd_req_complete() */
		D_ASSERT(device, drbd_पूर्णांकerval_empty(&req->i));
		drbd_insert_पूर्णांकerval(&device->ग_लिखो_requests, &req->i);

		/* NOTE
		 * In हाल the req ended up on the transfer log beक्रमe being
		 * queued on the worker, it could lead to this request being
		 * missed during cleanup after connection loss.
		 * So we have to करो both operations here,
		 * within the same lock that protects the transfer log.
		 *
		 * _req_add_to_epoch(req); this has to be after the
		 * _maybe_start_new_epoch(req); which happened in
		 * __drbd_make_request, because we now may set the bit
		 * again ourselves to बंद the current epoch.
		 *
		 * Add req to the (now) current epoch (barrier). */

		/* otherwise we may lose an unplug, which may cause some remote
		 * io-scheduler समयout to expire, increasing maximum latency,
		 * hurting perक्रमmance. */
		set_bit(UNPLUG_REMOTE, &device->flags);

		/* queue work item to send data */
		D_ASSERT(device, req->rq_state & RQ_NET_PENDING);
		mod_rq_state(req, m, 0, RQ_NET_QUEUED|RQ_EXP_BARR_ACK);
		req->w.cb =  w_send_dblock;
		drbd_queue_work(&connection->sender_work,
				&req->w);

		/* बंद the epoch, in हाल it outgrew the limit */
		rcu_पढ़ो_lock();
		nc = rcu_dereference(connection->net_conf);
		p = nc->max_epoch_size;
		rcu_पढ़ो_unlock();
		अगर (connection->current_tle_ग_लिखोs >= p)
			start_new_tl_epoch(connection);

		अवरोध;

	हाल QUEUE_FOR_SEND_OOS:
		mod_rq_state(req, m, 0, RQ_NET_QUEUED);
		req->w.cb =  w_send_out_of_sync;
		drbd_queue_work(&connection->sender_work,
				&req->w);
		अवरोध;

	हाल READ_RETRY_REMOTE_CANCELED:
	हाल SEND_CANCELED:
	हाल SEND_FAILED:
		/* real cleanup will be करोne from tl_clear.  just update flags
		 * so it is no दीर्घer marked as on the worker queue */
		mod_rq_state(req, m, RQ_NET_QUEUED, 0);
		अवरोध;

	हाल HANDED_OVER_TO_NETWORK:
		/* निश्चित something? */
		अगर (is_pending_ग_लिखो_protocol_A(req))
			/* this is what is dangerous about protocol A:
			 * pretend it was successfully written on the peer. */
			mod_rq_state(req, m, RQ_NET_QUEUED|RQ_NET_PENDING,
						RQ_NET_SENT|RQ_NET_OK);
		अन्यथा
			mod_rq_state(req, m, RQ_NET_QUEUED, RQ_NET_SENT);
		/* It is still not yet RQ_NET_DONE until the
		 * corresponding epoch barrier got acked as well,
		 * so we know what to dirty on connection loss. */
		अवरोध;

	हाल OOS_HANDED_TO_NETWORK:
		/* Was not set PENDING, no दीर्घer QUEUED, so is now DONE
		 * as far as this connection is concerned. */
		mod_rq_state(req, m, RQ_NET_QUEUED, RQ_NET_DONE);
		अवरोध;

	हाल CONNECTION_LOST_WHILE_PENDING:
		/* transfer log cleanup after connection loss */
		mod_rq_state(req, m,
				RQ_NET_OK|RQ_NET_PENDING|RQ_COMPLETION_SUSP,
				RQ_NET_DONE);
		अवरोध;

	हाल CONFLICT_RESOLVED:
		/* क्रम superseded conflicting ग_लिखोs of multiple primaries,
		 * there is no need to keep anything in the tl, potential
		 * node crashes are covered by the activity log.
		 *
		 * If this request had been marked as RQ_POSTPONED beक्रमe,
		 * it will actually not be completed, but "restarted",
		 * resubmitted from the retry worker context. */
		D_ASSERT(device, req->rq_state & RQ_NET_PENDING);
		D_ASSERT(device, req->rq_state & RQ_EXP_WRITE_ACK);
		mod_rq_state(req, m, RQ_NET_PENDING, RQ_NET_DONE|RQ_NET_OK);
		अवरोध;

	हाल WRITE_ACKED_BY_PEER_AND_SIS:
		req->rq_state |= RQ_NET_SIS;
		fallthrough;
	हाल WRITE_ACKED_BY_PEER:
		/* Normal operation protocol C: successfully written on peer.
		 * During resync, even in protocol != C,
		 * we requested an explicit ग_लिखो ack anyways.
		 * Which means we cannot even निश्चित anything here.
		 * Nothing more to करो here.
		 * We want to keep the tl in place क्रम all protocols, to cater
		 * क्रम अस्थिर ग_लिखो-back caches on lower level devices. */
		जाओ ack_common;
	हाल RECV_ACKED_BY_PEER:
		D_ASSERT(device, req->rq_state & RQ_EXP_RECEIVE_ACK);
		/* protocol B; pretends to be successfully written on peer.
		 * see also notes above in HANDED_OVER_TO_NETWORK about
		 * protocol != C */
	ack_common:
		mod_rq_state(req, m, RQ_NET_PENDING, RQ_NET_OK);
		अवरोध;

	हाल POSTPONE_WRITE:
		D_ASSERT(device, req->rq_state & RQ_EXP_WRITE_ACK);
		/* If this node has alपढ़ोy detected the ग_लिखो conflict, the
		 * worker will be रुकोing on misc_रुको.  Wake it up once this
		 * request has completed locally.
		 */
		D_ASSERT(device, req->rq_state & RQ_NET_PENDING);
		req->rq_state |= RQ_POSTPONED;
		अगर (req->i.रुकोing)
			wake_up(&device->misc_रुको);
		/* Do not clear RQ_NET_PENDING. This request will make further
		 * progress via restart_conflicting_ग_लिखोs() or
		 * fail_postponed_requests(). Hopefully. */
		अवरोध;

	हाल NEG_ACKED:
		mod_rq_state(req, m, RQ_NET_OK|RQ_NET_PENDING, 0);
		अवरोध;

	हाल FAIL_FROZEN_DISK_IO:
		अगर (!(req->rq_state & RQ_LOCAL_COMPLETED))
			अवरोध;
		mod_rq_state(req, m, RQ_COMPLETION_SUSP, 0);
		अवरोध;

	हाल RESTART_FROZEN_DISK_IO:
		अगर (!(req->rq_state & RQ_LOCAL_COMPLETED))
			अवरोध;

		mod_rq_state(req, m,
				RQ_COMPLETION_SUSP|RQ_LOCAL_COMPLETED,
				RQ_LOCAL_PENDING);

		rv = MR_READ;
		अगर (bio_data_dir(req->master_bio) == WRITE)
			rv = MR_WRITE;

		get_ldev(device); /* always succeeds in this call path */
		req->w.cb = w_restart_disk_io;
		drbd_queue_work(&connection->sender_work,
				&req->w);
		अवरोध;

	हाल RESEND:
		/* Simply complete (local only) READs. */
		अगर (!(req->rq_state & RQ_WRITE) && !req->w.cb) अणु
			mod_rq_state(req, m, RQ_COMPLETION_SUSP, 0);
			अवरोध;
		पूर्ण

		/* If RQ_NET_OK is alपढ़ोy set, we got a P_WRITE_ACK or P_RECV_ACK
		   beक्रमe the connection loss (B&C only); only P_BARRIER_ACK
		   (or the local completion?) was missing when we suspended.
		   Throwing them out of the TL here by pretending we got a BARRIER_ACK.
		   During connection handshake, we ensure that the peer was not rebooted. */
		अगर (!(req->rq_state & RQ_NET_OK)) अणु
			/* FIXME could this possibly be a req->dw.cb == w_send_out_of_sync?
			 * in that हाल we must not set RQ_NET_PENDING. */

			mod_rq_state(req, m, RQ_COMPLETION_SUSP, RQ_NET_QUEUED|RQ_NET_PENDING);
			अगर (req->w.cb) अणु
				/* w.cb expected to be w_send_dblock, or w_send_पढ़ो_req */
				drbd_queue_work(&connection->sender_work,
						&req->w);
				rv = req->rq_state & RQ_WRITE ? MR_WRITE : MR_READ;
			पूर्ण /* अन्यथा: FIXME can this happen? */
			अवरोध;
		पूर्ण
		fallthrough;	/* to BARRIER_ACKED */

	हाल BARRIER_ACKED:
		/* barrier ack क्रम READ requests करोes not make sense */
		अगर (!(req->rq_state & RQ_WRITE))
			अवरोध;

		अगर (req->rq_state & RQ_NET_PENDING) अणु
			/* barrier came in beक्रमe all requests were acked.
			 * this is bad, because अगर the connection is lost now,
			 * we won't be able to clean them up... */
			drbd_err(device, "FIXME (BARRIER_ACKED but pending)\n");
		पूर्ण
		/* Allowed to complete requests, even जबतक suspended.
		 * As this is called क्रम all requests within a matching epoch,
		 * we need to filter, and only set RQ_NET_DONE क्रम those that
		 * have actually been on the wire. */
		mod_rq_state(req, m, RQ_COMPLETION_SUSP,
				(req->rq_state & RQ_NET_MASK) ? RQ_NET_DONE : 0);
		अवरोध;

	हाल DATA_RECEIVED:
		D_ASSERT(device, req->rq_state & RQ_NET_PENDING);
		mod_rq_state(req, m, RQ_NET_PENDING, RQ_NET_OK|RQ_NET_DONE);
		अवरोध;

	हाल QUEUE_AS_DRBD_BARRIER:
		start_new_tl_epoch(connection);
		mod_rq_state(req, m, 0, RQ_NET_OK|RQ_NET_DONE);
		अवरोध;
	पूर्ण

	वापस rv;
पूर्ण

/* we may करो a local पढ़ो अगर:
 * - we are consistent (of course),
 * - or we are generally inconsistent,
 *   BUT we are still/alपढ़ोy IN SYNC क्रम this area.
 *   since size may be bigger than BM_BLOCK_SIZE,
 *   we may need to check several bits.
 */
अटल bool drbd_may_करो_local_पढ़ो(काष्ठा drbd_device *device, sector_t sector, पूर्णांक size)
अणु
	अचिन्हित दीर्घ sbnr, ebnr;
	sector_t esector, nr_sectors;

	अगर (device->state.disk == D_UP_TO_DATE)
		वापस true;
	अगर (device->state.disk != D_INCONSISTENT)
		वापस false;
	esector = sector + (size >> 9) - 1;
	nr_sectors = get_capacity(device->vdisk);
	D_ASSERT(device, sector  < nr_sectors);
	D_ASSERT(device, esector < nr_sectors);

	sbnr = BM_SECT_TO_BIT(sector);
	ebnr = BM_SECT_TO_BIT(esector);

	वापस drbd_bm_count_bits(device, sbnr, ebnr) == 0;
पूर्ण

अटल bool remote_due_to_पढ़ो_balancing(काष्ठा drbd_device *device, sector_t sector,
		क्रमागत drbd_पढ़ो_balancing rbm)
अणु
	काष्ठा backing_dev_info *bdi;
	पूर्णांक stripe_shअगरt;

	चयन (rbm) अणु
	हाल RB_CONGESTED_REMOTE:
		bdi = device->ldev->backing_bdev->bd_disk->queue->backing_dev_info;
		वापस bdi_पढ़ो_congested(bdi);
	हाल RB_LEAST_PENDING:
		वापस atomic_पढ़ो(&device->local_cnt) >
			atomic_पढ़ो(&device->ap_pending_cnt) + atomic_पढ़ो(&device->rs_pending_cnt);
	हाल RB_32K_STRIPING:  /* stripe_shअगरt = 15 */
	हाल RB_64K_STRIPING:
	हाल RB_128K_STRIPING:
	हाल RB_256K_STRIPING:
	हाल RB_512K_STRIPING:
	हाल RB_1M_STRIPING:   /* stripe_shअगरt = 20 */
		stripe_shअगरt = (rbm - RB_32K_STRIPING + 15);
		वापस (sector >> (stripe_shअगरt - 9)) & 1;
	हाल RB_ROUND_ROBIN:
		वापस test_and_change_bit(READ_BALANCE_RR, &device->flags);
	हाल RB_PREFER_REMOTE:
		वापस true;
	हाल RB_PREFER_LOCAL:
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * complete_conflicting_ग_लिखोs  -  रुको क्रम any conflicting ग_लिखो requests
 *
 * The ग_लिखो_requests tree contains all active ग_लिखो requests which we
 * currently know about.  Wait क्रम any requests to complete which conflict with
 * the new one.
 *
 * Only way out: हटाओ the conflicting पूर्णांकervals from the tree.
 */
अटल व्योम complete_conflicting_ग_लिखोs(काष्ठा drbd_request *req)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा drbd_device *device = req->device;
	काष्ठा drbd_पूर्णांकerval *i;
	sector_t sector = req->i.sector;
	पूर्णांक size = req->i.size;

	क्रम (;;) अणु
		drbd_क्रम_each_overlap(i, &device->ग_लिखो_requests, sector, size) अणु
			/* Ignore, अगर alपढ़ोy completed to upper layers. */
			अगर (i->completed)
				जारी;
			/* Handle the first found overlap.  After the schedule
			 * we have to restart the tree walk. */
			अवरोध;
		पूर्ण
		अगर (!i)	/* अगर any */
			अवरोध;

		/* Indicate to wake up device->misc_रुको on progress.  */
		prepare_to_रुको(&device->misc_रुको, &रुको, TASK_UNINTERRUPTIBLE);
		i->रुकोing = true;
		spin_unlock_irq(&device->resource->req_lock);
		schedule();
		spin_lock_irq(&device->resource->req_lock);
	पूर्ण
	finish_रुको(&device->misc_रुको, &रुको);
पूर्ण

/* called within req_lock */
अटल व्योम maybe_pull_ahead(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_connection *connection = first_peer_device(device)->connection;
	काष्ठा net_conf *nc;
	bool congested = false;
	क्रमागत drbd_on_congestion on_congestion;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	on_congestion = nc ? nc->on_congestion : OC_BLOCK;
	rcu_पढ़ो_unlock();
	अगर (on_congestion == OC_BLOCK ||
	    connection->agreed_pro_version < 96)
		वापस;

	अगर (on_congestion == OC_PULL_AHEAD && device->state.conn == C_AHEAD)
		वापस; /* nothing to करो ... */

	/* If I करोn't even have good local storage, we can not reasonably try
	 * to pull ahead of the peer. We also need the local reference to make
	 * sure device->act_log is there.
	 */
	अगर (!get_ldev_अगर_state(device, D_UP_TO_DATE))
		वापस;

	अगर (nc->cong_fill &&
	    atomic_पढ़ो(&device->ap_in_flight) >= nc->cong_fill) अणु
		drbd_info(device, "Congestion-fill threshold reached\n");
		congested = true;
	पूर्ण

	अगर (device->act_log->used >= nc->cong_extents) अणु
		drbd_info(device, "Congestion-extents threshold reached\n");
		congested = true;
	पूर्ण

	अगर (congested) अणु
		/* start a new epoch क्रम non-mirrored ग_लिखोs */
		start_new_tl_epoch(first_peer_device(device)->connection);

		अगर (on_congestion == OC_PULL_AHEAD)
			_drbd_set_state(_NS(device, conn, C_AHEAD), 0, शून्य);
		अन्यथा  /*nc->on_congestion == OC_DISCONNECT */
			_drbd_set_state(_NS(device, conn, C_DISCONNECTING), 0, शून्य);
	पूर्ण
	put_ldev(device);
पूर्ण

/* If this वापसs false, and req->निजी_bio is still set,
 * this should be submitted locally.
 *
 * If it वापसs false, but req->निजी_bio is not set,
 * we करो not have access to good data :(
 *
 * Otherwise, this destroys req->निजी_bio, अगर any,
 * and वापसs true.
 */
अटल bool करो_remote_पढ़ो(काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_device *device = req->device;
	क्रमागत drbd_पढ़ो_balancing rbm;

	अगर (req->निजी_bio) अणु
		अगर (!drbd_may_करो_local_पढ़ो(device,
					req->i.sector, req->i.size)) अणु
			bio_put(req->निजी_bio);
			req->निजी_bio = शून्य;
			put_ldev(device);
		पूर्ण
	पूर्ण

	अगर (device->state.pdsk != D_UP_TO_DATE)
		वापस false;

	अगर (req->निजी_bio == शून्य)
		वापस true;

	/* TODO: improve पढ़ो balancing decisions, take पूर्णांकo account drbd
	 * protocol, pending requests etc. */

	rcu_पढ़ो_lock();
	rbm = rcu_dereference(device->ldev->disk_conf)->पढ़ो_balancing;
	rcu_पढ़ो_unlock();

	अगर (rbm == RB_PREFER_LOCAL && req->निजी_bio)
		वापस false; /* submit locally */

	अगर (remote_due_to_पढ़ो_balancing(device, req->i.sector, rbm)) अणु
		अगर (req->निजी_bio) अणु
			bio_put(req->निजी_bio);
			req->निजी_bio = शून्य;
			put_ldev(device);
		पूर्ण
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool drbd_should_करो_remote(जोड़ drbd_dev_state s)
अणु
	वापस s.pdsk == D_UP_TO_DATE ||
		(s.pdsk >= D_INCONSISTENT &&
		 s.conn >= C_WF_BITMAP_T &&
		 s.conn < C_AHEAD);
	/* Beक्रमe proto 96 that was >= CONNECTED instead of >= C_WF_BITMAP_T.
	   That is equivalent since beक्रमe 96 IO was frozen in the C_WF_BITMAP*
	   states. */
पूर्ण

अटल bool drbd_should_send_out_of_sync(जोड़ drbd_dev_state s)
अणु
	वापस s.conn == C_AHEAD || s.conn == C_WF_BITMAP_S;
	/* pdsk = D_INCONSISTENT as a consequence. Protocol 96 check not necessary
	   since we enter state C_AHEAD only अगर proto >= 96 */
पूर्ण

/* वापसs number of connections (== 1, क्रम drbd 8.4)
 * expected to actually ग_लिखो this data,
 * which करोes NOT include those that we are L_AHEAD क्रम. */
अटल पूर्णांक drbd_process_ग_लिखो_request(काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_device *device = req->device;
	पूर्णांक remote, send_oos;

	remote = drbd_should_करो_remote(device->state);
	send_oos = drbd_should_send_out_of_sync(device->state);

	/* Need to replicate ग_लिखोs.  Unless it is an empty flush,
	 * which is better mapped to a DRBD P_BARRIER packet,
	 * also क्रम drbd wire protocol compatibility reasons.
	 * If this was a flush, just start a new epoch.
	 * Unless the current epoch was empty anyways, or we are not currently
	 * replicating, in which हाल there is no poपूर्णांक. */
	अगर (unlikely(req->i.size == 0)) अणु
		/* The only size==0 bios we expect are empty flushes. */
		D_ASSERT(device, req->master_bio->bi_opf & REQ_PREFLUSH);
		अगर (remote)
			_req_mod(req, QUEUE_AS_DRBD_BARRIER);
		वापस remote;
	पूर्ण

	अगर (!remote && !send_oos)
		वापस 0;

	D_ASSERT(device, !(remote && send_oos));

	अगर (remote) अणु
		_req_mod(req, TO_BE_SENT);
		_req_mod(req, QUEUE_FOR_NET_WRITE);
	पूर्ण अन्यथा अगर (drbd_set_out_of_sync(device, req->i.sector, req->i.size))
		_req_mod(req, QUEUE_FOR_SEND_OOS);

	वापस remote;
पूर्ण

अटल व्योम drbd_process_discard_or_zeroes_req(काष्ठा drbd_request *req, पूर्णांक flags)
अणु
	पूर्णांक err = drbd_issue_discard_or_zero_out(req->device,
				req->i.sector, req->i.size >> 9, flags);
	अगर (err)
		req->निजी_bio->bi_status = BLK_STS_IOERR;
	bio_endio(req->निजी_bio);
पूर्ण

अटल व्योम
drbd_submit_req_निजी_bio(काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_device *device = req->device;
	काष्ठा bio *bio = req->निजी_bio;
	अचिन्हित पूर्णांक type;

	अगर (bio_op(bio) != REQ_OP_READ)
		type = DRBD_FAULT_DT_WR;
	अन्यथा अगर (bio->bi_opf & REQ_RAHEAD)
		type = DRBD_FAULT_DT_RA;
	अन्यथा
		type = DRBD_FAULT_DT_RD;

	bio_set_dev(bio, device->ldev->backing_bdev);

	/* State may have changed since we grabbed our reference on the
	 * ->ldev member. Double check, and लघु-circuit to endio.
	 * In हाल the last activity log transaction failed to get on
	 * stable storage, and this is a WRITE, we may not even submit
	 * this bio. */
	अगर (get_ldev(device)) अणु
		अगर (drbd_insert_fault(device, type))
			bio_io_error(bio);
		अन्यथा अगर (bio_op(bio) == REQ_OP_WRITE_ZEROES)
			drbd_process_discard_or_zeroes_req(req, EE_ZEROOUT |
			    ((bio->bi_opf & REQ_NOUNMAP) ? 0 : EE_TRIM));
		अन्यथा अगर (bio_op(bio) == REQ_OP_DISCARD)
			drbd_process_discard_or_zeroes_req(req, EE_TRIM);
		अन्यथा
			submit_bio_noacct(bio);
		put_ldev(device);
	पूर्ण अन्यथा
		bio_io_error(bio);
पूर्ण

अटल व्योम drbd_queue_ग_लिखो(काष्ठा drbd_device *device, काष्ठा drbd_request *req)
अणु
	spin_lock_irq(&device->resource->req_lock);
	list_add_tail(&req->tl_requests, &device->submit.ग_लिखोs);
	list_add_tail(&req->req_pending_master_completion,
			&device->pending_master_completion[1 /* WRITE */]);
	spin_unlock_irq(&device->resource->req_lock);
	queue_work(device->submit.wq, &device->submit.worker);
	/* करो_submit() may sleep पूर्णांकernally on al_रुको, too */
	wake_up(&device->al_रुको);
पूर्ण

/* वापसs the new drbd_request poपूर्णांकer, अगर the caller is expected to
 * drbd_send_and_submit() it (to save latency), or शून्य अगर we queued the
 * request on the submitter thपढ़ो.
 * Returns ERR_PTR(-ENOMEM) अगर we cannot allocate a drbd_request.
 */
अटल काष्ठा drbd_request *
drbd_request_prepare(काष्ठा drbd_device *device, काष्ठा bio *bio)
अणु
	स्थिर पूर्णांक rw = bio_data_dir(bio);
	काष्ठा drbd_request *req;

	/* allocate outside of all locks; */
	req = drbd_req_new(device, bio);
	अगर (!req) अणु
		dec_ap_bio(device);
		/* only pass the error to the upper layers.
		 * अगर user cannot handle io errors, that's not our business. */
		drbd_err(device, "could not kmalloc() req\n");
		bio->bi_status = BLK_STS_RESOURCE;
		bio_endio(bio);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* Update disk stats */
	req->start_jअगर = bio_start_io_acct(req->master_bio);

	अगर (!get_ldev(device)) अणु
		bio_put(req->निजी_bio);
		req->निजी_bio = शून्य;
	पूर्ण

	/* process discards always from our submitter thपढ़ो */
	अगर (bio_op(bio) == REQ_OP_WRITE_ZEROES ||
	    bio_op(bio) == REQ_OP_DISCARD)
		जाओ queue_क्रम_submitter_thपढ़ो;

	अगर (rw == WRITE && req->निजी_bio && req->i.size
	&& !test_bit(AL_SUSPENDED, &device->flags)) अणु
		अगर (!drbd_al_begin_io_fastpath(device, &req->i))
			जाओ queue_क्रम_submitter_thपढ़ो;
		req->rq_state |= RQ_IN_ACT_LOG;
		req->in_actlog_jअगर = jअगरfies;
	पूर्ण
	वापस req;

 queue_क्रम_submitter_thपढ़ो:
	atomic_inc(&device->ap_actlog_cnt);
	drbd_queue_ग_लिखो(device, req);
	वापस शून्य;
पूर्ण

/* Require at least one path to current data.
 * We करोn't want to allow ग_लिखोs on C_STANDALONE D_INCONSISTENT:
 * We would not allow to पढ़ो what was written,
 * we would not have bumped the data generation uuids,
 * we would cause data भागergence क्रम all the wrong reasons.
 *
 * If we करोn't see at least one D_UP_TO_DATE, we will fail this request,
 * which either वापसs EIO, or, अगर OND_SUSPEND_IO is set, suspends IO,
 * and queues क्रम retry later.
 */
अटल bool may_करो_ग_लिखोs(काष्ठा drbd_device *device)
अणु
	स्थिर जोड़ drbd_dev_state s = device->state;
	वापस s.disk == D_UP_TO_DATE || s.pdsk == D_UP_TO_DATE;
पूर्ण

काष्ठा drbd_plug_cb अणु
	काष्ठा blk_plug_cb cb;
	काष्ठा drbd_request *most_recent_req;
	/* करो we need more? */
पूर्ण;

अटल व्योम drbd_unplug(काष्ठा blk_plug_cb *cb, bool from_schedule)
अणु
	काष्ठा drbd_plug_cb *plug = container_of(cb, काष्ठा drbd_plug_cb, cb);
	काष्ठा drbd_resource *resource = plug->cb.data;
	काष्ठा drbd_request *req = plug->most_recent_req;

	kमुक्त(cb);
	अगर (!req)
		वापस;

	spin_lock_irq(&resource->req_lock);
	/* In हाल the sender did not process it yet, उठाओ the flag to
	 * have it followed with P_UNPLUG_REMOTE just after. */
	req->rq_state |= RQ_UNPLUG;
	/* but also queue a generic unplug */
	drbd_queue_unplug(req->device);
	kref_put(&req->kref, drbd_req_destroy);
	spin_unlock_irq(&resource->req_lock);
पूर्ण

अटल काष्ठा drbd_plug_cb* drbd_check_plugged(काष्ठा drbd_resource *resource)
अणु
	/* A lot of text to say
	 * वापस (काष्ठा drbd_plug_cb*)blk_check_plugged(); */
	काष्ठा drbd_plug_cb *plug;
	काष्ठा blk_plug_cb *cb = blk_check_plugged(drbd_unplug, resource, माप(*plug));

	अगर (cb)
		plug = container_of(cb, काष्ठा drbd_plug_cb, cb);
	अन्यथा
		plug = शून्य;
	वापस plug;
पूर्ण

अटल व्योम drbd_update_plug(काष्ठा drbd_plug_cb *plug, काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_request *पंचांगp = plug->most_recent_req;
	/* Will be sent to some peer.
	 * Remember to tag it with UNPLUG_REMOTE on unplug */
	kref_get(&req->kref);
	plug->most_recent_req = req;
	अगर (पंचांगp)
		kref_put(&पंचांगp->kref, drbd_req_destroy);
पूर्ण

अटल व्योम drbd_send_and_submit(काष्ठा drbd_device *device, काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_resource *resource = device->resource;
	स्थिर पूर्णांक rw = bio_data_dir(req->master_bio);
	काष्ठा bio_and_error m = अणु शून्य, पूर्ण;
	bool no_remote = false;
	bool submit_निजी_bio = false;

	spin_lock_irq(&resource->req_lock);
	अगर (rw == WRITE) अणु
		/* This may temporarily give up the req_lock,
		 * but will re-aquire it beक्रमe it वापसs here.
		 * Needs to be beक्रमe the check on drbd_suspended() */
		complete_conflicting_ग_लिखोs(req);
		/* no more giving up req_lock from now on! */

		/* check क्रम congestion, and potentially stop sending
		 * full data updates, but start sending "dirty bits" only. */
		maybe_pull_ahead(device);
	पूर्ण


	अगर (drbd_suspended(device)) अणु
		/* push back and retry: */
		req->rq_state |= RQ_POSTPONED;
		अगर (req->निजी_bio) अणु
			bio_put(req->निजी_bio);
			req->निजी_bio = शून्य;
			put_ldev(device);
		पूर्ण
		जाओ out;
	पूर्ण

	/* We fail READ early, अगर we can not serve it.
	 * We must करो this beक्रमe req is रेजिस्टरed on any lists.
	 * Otherwise, drbd_req_complete() will queue failed READ क्रम retry. */
	अगर (rw != WRITE) अणु
		अगर (!करो_remote_पढ़ो(req) && !req->निजी_bio)
			जाओ nodata;
	पूर्ण

	/* which transfer log epoch करोes this beदीर्घ to? */
	req->epoch = atomic_पढ़ो(&first_peer_device(device)->connection->current_tle_nr);

	/* no poपूर्णांक in adding empty flushes to the transfer log,
	 * they are mapped to drbd barriers alपढ़ोy. */
	अगर (likely(req->i.size!=0)) अणु
		अगर (rw == WRITE)
			first_peer_device(device)->connection->current_tle_ग_लिखोs++;

		list_add_tail(&req->tl_requests, &first_peer_device(device)->connection->transfer_log);
	पूर्ण

	अगर (rw == WRITE) अणु
		अगर (req->निजी_bio && !may_करो_ग_लिखोs(device)) अणु
			bio_put(req->निजी_bio);
			req->निजी_bio = शून्य;
			put_ldev(device);
			जाओ nodata;
		पूर्ण
		अगर (!drbd_process_ग_लिखो_request(req))
			no_remote = true;
	पूर्ण अन्यथा अणु
		/* We either have a निजी_bio, or we can पढ़ो from remote.
		 * Otherwise we had करोne the जाओ nodata above. */
		अगर (req->निजी_bio == शून्य) अणु
			_req_mod(req, TO_BE_SENT);
			_req_mod(req, QUEUE_FOR_NET_READ);
		पूर्ण अन्यथा
			no_remote = true;
	पूर्ण

	अगर (no_remote == false) अणु
		काष्ठा drbd_plug_cb *plug = drbd_check_plugged(resource);
		अगर (plug)
			drbd_update_plug(plug, req);
	पूर्ण

	/* If it took the fast path in drbd_request_prepare, add it here.
	 * The slow path has added it alपढ़ोy. */
	अगर (list_empty(&req->req_pending_master_completion))
		list_add_tail(&req->req_pending_master_completion,
			&device->pending_master_completion[rw == WRITE]);
	अगर (req->निजी_bio) अणु
		/* needs to be marked within the same spinlock */
		req->pre_submit_jअगर = jअगरfies;
		list_add_tail(&req->req_pending_local,
			&device->pending_completion[rw == WRITE]);
		_req_mod(req, TO_BE_SUBMITTED);
		/* but we need to give up the spinlock to submit */
		submit_निजी_bio = true;
	पूर्ण अन्यथा अगर (no_remote) अणु
nodata:
		अगर (__ratelimit(&drbd_ratelimit_state))
			drbd_err(device, "IO ERROR: neither local nor remote data, sector %llu+%u\n",
					(अचिन्हित दीर्घ दीर्घ)req->i.sector, req->i.size >> 9);
		/* A ग_लिखो may have been queued क्रम send_oos, however.
		 * So we can not simply मुक्त it, we must go through drbd_req_put_completion_ref() */
	पूर्ण

out:
	drbd_req_put_completion_ref(req, &m, 1);
	spin_unlock_irq(&resource->req_lock);

	/* Even though above is a kref_put(), this is safe.
	 * As दीर्घ as we still need to submit our निजी bio,
	 * we hold a completion ref, and the request cannot disappear.
	 * If however this request did not even have a निजी bio to submit
	 * (e.g. remote पढ़ो), req may alपढ़ोy be invalid now.
	 * That's why we cannot check on req->निजी_bio. */
	अगर (submit_निजी_bio)
		drbd_submit_req_निजी_bio(req);
	अगर (m.bio)
		complete_master_bio(device, &m);
पूर्ण

व्योम __drbd_make_request(काष्ठा drbd_device *device, काष्ठा bio *bio)
अणु
	काष्ठा drbd_request *req = drbd_request_prepare(device, bio);
	अगर (IS_ERR_OR_शून्य(req))
		वापस;
	drbd_send_and_submit(device, req);
पूर्ण

अटल व्योम submit_fast_path(काष्ठा drbd_device *device, काष्ठा list_head *incoming)
अणु
	काष्ठा blk_plug plug;
	काष्ठा drbd_request *req, *पंचांगp;

	blk_start_plug(&plug);
	list_क्रम_each_entry_safe(req, पंचांगp, incoming, tl_requests) अणु
		स्थिर पूर्णांक rw = bio_data_dir(req->master_bio);

		अगर (rw == WRITE /* rw != WRITE should not even end up here! */
		&& req->निजी_bio && req->i.size
		&& !test_bit(AL_SUSPENDED, &device->flags)) अणु
			अगर (!drbd_al_begin_io_fastpath(device, &req->i))
				जारी;

			req->rq_state |= RQ_IN_ACT_LOG;
			req->in_actlog_jअगर = jअगरfies;
			atomic_dec(&device->ap_actlog_cnt);
		पूर्ण

		list_del_init(&req->tl_requests);
		drbd_send_and_submit(device, req);
	पूर्ण
	blk_finish_plug(&plug);
पूर्ण

अटल bool prepare_al_transaction_nonblock(काष्ठा drbd_device *device,
					    काष्ठा list_head *incoming,
					    काष्ठा list_head *pending,
					    काष्ठा list_head *later)
अणु
	काष्ठा drbd_request *req;
	पूर्णांक wake = 0;
	पूर्णांक err;

	spin_lock_irq(&device->al_lock);
	जबतक ((req = list_first_entry_or_null(incoming, काष्ठा drbd_request, tl_requests))) अणु
		err = drbd_al_begin_io_nonblock(device, &req->i);
		अगर (err == -ENOBUFS)
			अवरोध;
		अगर (err == -EBUSY)
			wake = 1;
		अगर (err)
			list_move_tail(&req->tl_requests, later);
		अन्यथा
			list_move_tail(&req->tl_requests, pending);
	पूर्ण
	spin_unlock_irq(&device->al_lock);
	अगर (wake)
		wake_up(&device->al_रुको);
	वापस !list_empty(pending);
पूर्ण

अटल व्योम send_and_submit_pending(काष्ठा drbd_device *device, काष्ठा list_head *pending)
अणु
	काष्ठा blk_plug plug;
	काष्ठा drbd_request *req;

	blk_start_plug(&plug);
	जबतक ((req = list_first_entry_or_null(pending, काष्ठा drbd_request, tl_requests))) अणु
		req->rq_state |= RQ_IN_ACT_LOG;
		req->in_actlog_jअगर = jअगरfies;
		atomic_dec(&device->ap_actlog_cnt);
		list_del_init(&req->tl_requests);
		drbd_send_and_submit(device, req);
	पूर्ण
	blk_finish_plug(&plug);
पूर्ण

व्योम करो_submit(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा drbd_device *device = container_of(ws, काष्ठा drbd_device, submit.worker);
	LIST_HEAD(incoming);	/* from drbd_make_request() */
	LIST_HEAD(pending);	/* to be submitted after next AL-transaction commit */
	LIST_HEAD(busy);	/* blocked by resync requests */

	/* grab new incoming requests */
	spin_lock_irq(&device->resource->req_lock);
	list_splice_tail_init(&device->submit.ग_लिखोs, &incoming);
	spin_unlock_irq(&device->resource->req_lock);

	क्रम (;;) अणु
		DEFINE_WAIT(रुको);

		/* move used-to-be-busy back to front of incoming */
		list_splice_init(&busy, &incoming);
		submit_fast_path(device, &incoming);
		अगर (list_empty(&incoming))
			अवरोध;

		क्रम (;;) अणु
			prepare_to_रुको(&device->al_रुको, &रुको, TASK_UNINTERRUPTIBLE);

			list_splice_init(&busy, &incoming);
			prepare_al_transaction_nonblock(device, &incoming, &pending, &busy);
			अगर (!list_empty(&pending))
				अवरोध;

			schedule();

			/* If all currently "hot" activity log extents are kept busy by
			 * incoming requests, we still must not totally starve new
			 * requests to "cold" extents.
			 * Something left on &incoming means there had not been
			 * enough update slots available, and the activity log
			 * has been marked as "starving".
			 *
			 * Try again now, without looking क्रम new requests,
			 * effectively blocking all new requests until we made
			 * at least _some_ progress with what we currently have.
			 */
			अगर (!list_empty(&incoming))
				जारी;

			/* Nothing moved to pending, but nothing left
			 * on incoming: all moved to busy!
			 * Grab new and iterate. */
			spin_lock_irq(&device->resource->req_lock);
			list_splice_tail_init(&device->submit.ग_लिखोs, &incoming);
			spin_unlock_irq(&device->resource->req_lock);
		पूर्ण
		finish_रुको(&device->al_रुको, &रुको);

		/* If the transaction was full, beक्रमe all incoming requests
		 * had been processed, skip ahead to commit, and iterate
		 * without splicing in more incoming requests from upper layers.
		 *
		 * Else, अगर all incoming have been processed,
		 * they have become either "pending" (to be submitted after
		 * next transaction commit) or "busy" (blocked by resync).
		 *
		 * Maybe more was queued, जबतक we prepared the transaction?
		 * Try to stuff those पूर्णांकo this transaction as well.
		 * Be strictly non-blocking here,
		 * we alपढ़ोy have something to commit.
		 *
		 * Commit अगर we करोn't make any more progres.
		 */

		जबतक (list_empty(&incoming)) अणु
			LIST_HEAD(more_pending);
			LIST_HEAD(more_incoming);
			bool made_progress;

			/* It is ok to look outside the lock,
			 * it's only an optimization anyways */
			अगर (list_empty(&device->submit.ग_लिखोs))
				अवरोध;

			spin_lock_irq(&device->resource->req_lock);
			list_splice_tail_init(&device->submit.ग_लिखोs, &more_incoming);
			spin_unlock_irq(&device->resource->req_lock);

			अगर (list_empty(&more_incoming))
				अवरोध;

			made_progress = prepare_al_transaction_nonblock(device, &more_incoming, &more_pending, &busy);

			list_splice_tail_init(&more_pending, &pending);
			list_splice_tail_init(&more_incoming, &incoming);
			अगर (!made_progress)
				अवरोध;
		पूर्ण

		drbd_al_begin_io_commit(device);
		send_and_submit_pending(device, &pending);
	पूर्ण
पूर्ण

blk_qc_t drbd_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा drbd_device *device = bio->bi_bdev->bd_disk->निजी_data;

	blk_queue_split(&bio);

	/*
	 * what we "blindly" assume:
	 */
	D_ASSERT(device, IS_ALIGNED(bio->bi_iter.bi_size, 512));

	inc_ap_bio(device);
	__drbd_make_request(device, bio);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल bool net_समयout_reached(काष्ठा drbd_request *net_req,
		काष्ठा drbd_connection *connection,
		अचिन्हित दीर्घ now, अचिन्हित दीर्घ ent,
		अचिन्हित पूर्णांक ko_count, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा drbd_device *device = net_req->device;

	अगर (!समय_after(now, net_req->pre_send_jअगर + ent))
		वापस false;

	अगर (समय_in_range(now, connection->last_reconnect_jअगर, connection->last_reconnect_jअगर + ent))
		वापस false;

	अगर (net_req->rq_state & RQ_NET_PENDING) अणु
		drbd_warn(device, "Remote failed to finish a request within %ums > ko-count (%u) * timeout (%u * 0.1s)\n",
			jअगरfies_to_msecs(now - net_req->pre_send_jअगर), ko_count, समयout);
		वापस true;
	पूर्ण

	/* We received an ACK alपढ़ोy (or are using protocol A),
	 * but are रुकोing क्रम the epoch closing barrier ack.
	 * Check अगर we sent the barrier alपढ़ोy.  We should not blame the peer
	 * क्रम being unresponsive, अगर we did not even ask it yet. */
	अगर (net_req->epoch == connection->send.current_epoch_nr) अणु
		drbd_warn(device,
			"We did not send a P_BARRIER for %ums > ko-count (%u) * timeout (%u * 0.1s); drbd kernel thread blocked?\n",
			jअगरfies_to_msecs(now - net_req->pre_send_jअगर), ko_count, समयout);
		वापस false;
	पूर्ण

	/* Worst हाल: we may have been blocked क्रम whatever reason, then
	 * suddenly are able to send a lot of requests (and epoch separating
	 * barriers) in quick succession.
	 * The बारtamp of the net_req may be much too old and not correspond
	 * to the sending समय of the relevant unack'ed barrier packet, so
	 * would trigger a spurious समयout.  The latest barrier packet may
	 * have a too recent बारtamp to trigger the समयout, potentially miss
	 * a समयout.  Right now we करोn't have a place to conveniently store
	 * these बारtamps.
	 * But in this particular situation, the application requests are still
	 * completed to upper layers, DRBD should still "feel" responsive.
	 * No need yet to समाप्त this connection, it may still recover.
	 * If not, eventually we will have queued enough पूर्णांकo the network क्रम
	 * us to block. From that poपूर्णांक of view, the बारtamp of the last sent
	 * barrier packet is relevant enough.
	 */
	अगर (समय_after(now, connection->send.last_sent_barrier_jअगर + ent)) अणु
		drbd_warn(device, "Remote failed to answer a P_BARRIER (sent at %lu jif; now=%lu jif) within %ums > ko-count (%u) * timeout (%u * 0.1s)\n",
			connection->send.last_sent_barrier_jअगर, now,
			jअगरfies_to_msecs(now - connection->send.last_sent_barrier_jअगर), ko_count, समयout);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* A request is considered समयd out, अगर
 * - we have some effective समयout from the configuration,
 *   with some state restrictions applied,
 * - the oldest request is रुकोing क्रम a response from the network
 *   resp. the local disk,
 * - the oldest request is in fact older than the effective समयout,
 * - the connection was established (resp. disk was attached)
 *   क्रम दीर्घer than the समयout alपढ़ोy.
 * Note that क्रम 32bit jअगरfies and very stable connections/disks,
 * we may have a wrap around, which is catched by
 *   !समय_in_range(now, last_..._jअगर, last_..._jअगर + समयout).
 *
 * Side effect: once per 32bit wrap-around पूर्णांकerval, which means every
 * ~198 days with 250 HZ, we have a winकरोw where the समयout would need
 * to expire twice (worst हाल) to become effective. Good enough.
 */

व्योम request_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा drbd_device *device = from_समयr(device, t, request_समयr);
	काष्ठा drbd_connection *connection = first_peer_device(device)->connection;
	काष्ठा drbd_request *req_पढ़ो, *req_ग_लिखो, *req_peer; /* oldest request */
	काष्ठा net_conf *nc;
	अचिन्हित दीर्घ oldest_submit_jअगर;
	अचिन्हित दीर्घ ent = 0, dt = 0, et, nt; /* effective समयout = ko_count * समयout */
	अचिन्हित दीर्घ now;
	अचिन्हित पूर्णांक ko_count = 0, समयout = 0;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	अगर (nc && device->state.conn >= C_WF_REPORT_PARAMS) अणु
		ko_count = nc->ko_count;
		समयout = nc->समयout;
	पूर्ण

	अगर (get_ldev(device)) अणु /* implicit state.disk >= D_INCONSISTENT */
		dt = rcu_dereference(device->ldev->disk_conf)->disk_समयout * HZ / 10;
		put_ldev(device);
	पूर्ण
	rcu_पढ़ो_unlock();


	ent = समयout * HZ/10 * ko_count;
	et = min_not_zero(dt, ent);

	अगर (!et)
		वापस; /* Recurring समयr stopped */

	now = jअगरfies;
	nt = now + et;

	spin_lock_irq(&device->resource->req_lock);
	req_पढ़ो = list_first_entry_or_null(&device->pending_completion[0], काष्ठा drbd_request, req_pending_local);
	req_ग_लिखो = list_first_entry_or_null(&device->pending_completion[1], काष्ठा drbd_request, req_pending_local);

	/* maybe the oldest request रुकोing क्रम the peer is in fact still
	 * blocking in tcp sendmsg.  That's ok, though, that's handled via the
	 * socket send समयout, requesting a ping, and bumping ko-count in
	 * we_should_drop_the_connection().
	 */

	/* check the oldest request we did successfully sent,
	 * but which is still रुकोing क्रम an ACK. */
	req_peer = connection->req_ack_pending;

	/* अगर we करोn't have such request (e.g. protocoll A)
	 * check the oldest requests which is still रुकोing on its epoch
	 * closing barrier ack. */
	अगर (!req_peer)
		req_peer = connection->req_not_net_करोne;

	/* evaluate the oldest peer request only in one समयr! */
	अगर (req_peer && req_peer->device != device)
		req_peer = शून्य;

	/* करो we have something to evaluate? */
	अगर (req_peer == शून्य && req_ग_लिखो == शून्य && req_पढ़ो == शून्य)
		जाओ out;

	oldest_submit_jअगर =
		(req_ग_लिखो && req_पढ़ो)
		? ( समय_beक्रमe(req_ग_लिखो->pre_submit_jअगर, req_पढ़ो->pre_submit_jअगर)
		  ? req_ग_लिखो->pre_submit_jअगर : req_पढ़ो->pre_submit_jअगर )
		: req_ग_लिखो ? req_ग_लिखो->pre_submit_jअगर
		: req_पढ़ो ? req_पढ़ो->pre_submit_jअगर : now;

	अगर (ent && req_peer && net_समयout_reached(req_peer, connection, now, ent, ko_count, समयout))
		_conn_request_state(connection, NS(conn, C_TIMEOUT), CS_VERBOSE | CS_HARD);

	अगर (dt && oldest_submit_jअगर != now &&
		 समय_after(now, oldest_submit_jअगर + dt) &&
		!समय_in_range(now, device->last_reattach_jअगर, device->last_reattach_jअगर + dt)) अणु
		drbd_warn(device, "Local backing device failed to meet the disk-timeout\n");
		__drbd_chk_io_error(device, DRBD_FORCE_DETACH);
	पूर्ण

	/* Reschedule समयr क्रम the nearest not alपढ़ोy expired समयout.
	 * Fallback to now + min(effective network समयout, disk समयout). */
	ent = (ent && req_peer && समय_beक्रमe(now, req_peer->pre_send_jअगर + ent))
		? req_peer->pre_send_jअगर + ent : now + et;
	dt = (dt && oldest_submit_jअगर != now && समय_beक्रमe(now, oldest_submit_jअगर + dt))
		? oldest_submit_jअगर + dt : now + et;
	nt = समय_beक्रमe(ent, dt) ? ent : dt;
out:
	spin_unlock_irq(&device->resource->req_lock);
	mod_समयr(&device->request_समयr, nt);
पूर्ण
