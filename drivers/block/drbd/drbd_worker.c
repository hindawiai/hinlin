<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   drbd_worker.c

   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2001-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 1999-2008, Philipp Reisner <philipp.reisner@linbit.com>.
   Copyright (C) 2002-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.


*/

#समावेश <linux/module.h>
#समावेश <linux/drbd.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/रुको.h>
#समावेश <linux/mm.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/माला.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/part_स्थिति.स>

#समावेश "drbd_int.h"
#समावेश "drbd_protocol.h"
#समावेश "drbd_req.h"

अटल पूर्णांक make_ov_request(काष्ठा drbd_device *, पूर्णांक);
अटल पूर्णांक make_resync_request(काष्ठा drbd_device *, पूर्णांक);

/* endio handlers:
 *   drbd_md_endio (defined here)
 *   drbd_request_endio (defined here)
 *   drbd_peer_request_endio (defined here)
 *   drbd_bm_endio (defined in drbd_biपंचांगap.c)
 *
 * For all these callbacks, note the following:
 * The callbacks will be called in irq context by the IDE drivers,
 * and in Softirqs/Tasklets/BH context by the SCSI drivers.
 * Try to get the locking right :)
 *
 */

/* used क्रम synchronous meta data and biपंचांगap IO
 * submitted by drbd_md_sync_page_io()
 */
व्योम drbd_md_endio(काष्ठा bio *bio)
अणु
	काष्ठा drbd_device *device;

	device = bio->bi_निजी;
	device->md_io.error = blk_status_to_त्रुटि_सं(bio->bi_status);

	/* special हाल: drbd_md_पढ़ो() during drbd_adm_attach() */
	अगर (device->ldev)
		put_ldev(device);
	bio_put(bio);

	/* We grabbed an extra reference in _drbd_md_sync_page_io() to be able
	 * to समयout on the lower level device, and eventually detach from it.
	 * If this io completion runs after that समयout expired, this
	 * drbd_md_put_buffer() may allow us to finally try and re-attach.
	 * During normal operation, this only माला_दो that extra reference
	 * करोwn to 1 again.
	 * Make sure we first drop the reference, and only then संकेत
	 * completion, or we may (in drbd_al_पढ़ो_log()) cycle so fast पूर्णांकo the
	 * next drbd_md_sync_page_io(), that we trigger the
	 * ASSERT(atomic_पढ़ो(&device->md_io_in_use) == 1) there.
	 */
	drbd_md_put_buffer(device);
	device->md_io.करोne = 1;
	wake_up(&device->misc_रुको);
पूर्ण

/* पढ़ोs on behalf of the partner,
 * "submitted" by the receiver
 */
अटल व्योम drbd_endio_पढ़ो_sec_final(काष्ठा drbd_peer_request *peer_req) __releases(local)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा drbd_peer_device *peer_device = peer_req->peer_device;
	काष्ठा drbd_device *device = peer_device->device;

	spin_lock_irqsave(&device->resource->req_lock, flags);
	device->पढ़ो_cnt += peer_req->i.size >> 9;
	list_del(&peer_req->w.list);
	अगर (list_empty(&device->पढ़ो_ee))
		wake_up(&device->ee_रुको);
	अगर (test_bit(__EE_WAS_ERROR, &peer_req->flags))
		__drbd_chk_io_error(device, DRBD_READ_ERROR);
	spin_unlock_irqrestore(&device->resource->req_lock, flags);

	drbd_queue_work(&peer_device->connection->sender_work, &peer_req->w);
	put_ldev(device);
पूर्ण

/* ग_लिखोs on behalf of the partner, or resync ग_लिखोs,
 * "submitted" by the receiver, final stage.  */
व्योम drbd_endio_ग_लिखो_sec_final(काष्ठा drbd_peer_request *peer_req) __releases(local)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा drbd_peer_device *peer_device = peer_req->peer_device;
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा drbd_connection *connection = peer_device->connection;
	काष्ठा drbd_पूर्णांकerval i;
	पूर्णांक करो_wake;
	u64 block_id;
	पूर्णांक करो_al_complete_io;

	/* after we moved peer_req to करोne_ee,
	 * we may no दीर्घer access it,
	 * it may be मुक्तd/reused alपढ़ोy!
	 * (as soon as we release the req_lock) */
	i = peer_req->i;
	करो_al_complete_io = peer_req->flags & EE_CALL_AL_COMPLETE_IO;
	block_id = peer_req->block_id;
	peer_req->flags &= ~EE_CALL_AL_COMPLETE_IO;

	अगर (peer_req->flags & EE_WAS_ERROR) अणु
		/* In protocol != C, we usually करो not send ग_लिखो acks.
		 * In हाल of a ग_लिखो error, send the neg ack anyways. */
		अगर (!__test_and_set_bit(__EE_SEND_WRITE_ACK, &peer_req->flags))
			inc_unacked(device);
		drbd_set_out_of_sync(device, peer_req->i.sector, peer_req->i.size);
	पूर्ण

	spin_lock_irqsave(&device->resource->req_lock, flags);
	device->writ_cnt += peer_req->i.size >> 9;
	list_move_tail(&peer_req->w.list, &device->करोne_ee);

	/*
	 * Do not हटाओ from the ग_लिखो_requests tree here: we did not send the
	 * Ack yet and did not wake possibly रुकोing conflicting requests.
	 * Removed from the tree from "drbd_process_done_ee" within the
	 * appropriate dw.cb (e_end_block/e_end_resync_block) or from
	 * _drbd_clear_करोne_ee.
	 */

	करो_wake = list_empty(block_id == ID_SYNCER ? &device->sync_ee : &device->active_ee);

	/* FIXME करो we want to detach क्रम failed REQ_OP_DISCARD?
	 * ((peer_req->flags & (EE_WAS_ERROR|EE_TRIM)) == EE_WAS_ERROR) */
	अगर (peer_req->flags & EE_WAS_ERROR)
		__drbd_chk_io_error(device, DRBD_WRITE_ERROR);

	अगर (connection->cstate >= C_WF_REPORT_PARAMS) अणु
		kref_get(&device->kref); /* put is in drbd_send_acks_wf() */
		अगर (!queue_work(connection->ack_sender, &peer_device->send_acks_work))
			kref_put(&device->kref, drbd_destroy_device);
	पूर्ण
	spin_unlock_irqrestore(&device->resource->req_lock, flags);

	अगर (block_id == ID_SYNCER)
		drbd_rs_complete_io(device, i.sector);

	अगर (करो_wake)
		wake_up(&device->ee_रुको);

	अगर (करो_al_complete_io)
		drbd_al_complete_io(device, &i);

	put_ldev(device);
पूर्ण

/* ग_लिखोs on behalf of the partner, or resync ग_लिखोs,
 * "submitted" by the receiver.
 */
व्योम drbd_peer_request_endio(काष्ठा bio *bio)
अणु
	काष्ठा drbd_peer_request *peer_req = bio->bi_निजी;
	काष्ठा drbd_device *device = peer_req->peer_device->device;
	bool is_ग_लिखो = bio_data_dir(bio) == WRITE;
	bool is_discard = bio_op(bio) == REQ_OP_WRITE_ZEROES ||
			  bio_op(bio) == REQ_OP_DISCARD;

	अगर (bio->bi_status && __ratelimit(&drbd_ratelimit_state))
		drbd_warn(device, "%s: error=%d s=%llus\n",
				is_ग_लिखो ? (is_discard ? "discard" : "write")
					: "read", bio->bi_status,
				(अचिन्हित दीर्घ दीर्घ)peer_req->i.sector);

	अगर (bio->bi_status)
		set_bit(__EE_WAS_ERROR, &peer_req->flags);

	bio_put(bio); /* no need क्रम the bio anymore */
	अगर (atomic_dec_and_test(&peer_req->pending_bios)) अणु
		अगर (is_ग_लिखो)
			drbd_endio_ग_लिखो_sec_final(peer_req);
		अन्यथा
			drbd_endio_पढ़ो_sec_final(peer_req);
	पूर्ण
पूर्ण

अटल व्योम
drbd_panic_after_delayed_completion_of_पातed_request(काष्ठा drbd_device *device)
अणु
	panic("drbd%u %s/%u potential random memory corruption caused by delayed completion of aborted local request\n",
		device->minor, device->resource->name, device->vnr);
पूर्ण

/* पढ़ो, पढ़ोA or ग_लिखो requests on R_PRIMARY coming from drbd_make_request
 */
व्योम drbd_request_endio(काष्ठा bio *bio)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा drbd_request *req = bio->bi_निजी;
	काष्ठा drbd_device *device = req->device;
	काष्ठा bio_and_error m;
	क्रमागत drbd_req_event what;

	/* If this request was पातed locally beक्रमe,
	 * but now was completed "successfully",
	 * chances are that this caused arbitrary data corruption.
	 *
	 * "aborting" requests, or क्रमce-detaching the disk, is पूर्णांकended क्रम
	 * completely blocked/hung local backing devices which करो no दीर्घer
	 * complete requests at all, not even करो error completions.  In this
	 * situation, usually a hard-reset and failover is the only way out.
	 *
	 * By "aborting", basically faking a local error-completion,
	 * we allow क्रम a more graceful swichover by cleanly migrating services.
	 * Still the affected node has to be rebooted "soon".
	 *
	 * By completing these requests, we allow the upper layers to re-use
	 * the associated data pages.
	 *
	 * If later the local backing device "recovers", and now DMAs some data
	 * from disk पूर्णांकo the original request pages, in the best हाल it will
	 * just put अक्रमom data पूर्णांकo unused pages; but typically it will corrupt
	 * meanजबतक completely unrelated data, causing all sorts of damage.
	 *
	 * Which means delayed successful completion,
	 * especially क्रम READ requests,
	 * is a reason to panic().
	 *
	 * We assume that a delayed *error* completion is OK,
	 * though we still will complain noisily about it.
	 */
	अगर (unlikely(req->rq_state & RQ_LOCAL_ABORTED)) अणु
		अगर (__ratelimit(&drbd_ratelimit_state))
			drbd_emerg(device, "delayed completion of aborted local request; disk-timeout may be too aggressive\n");

		अगर (!bio->bi_status)
			drbd_panic_after_delayed_completion_of_पातed_request(device);
	पूर्ण

	/* to aव्योम recursion in __req_mod */
	अगर (unlikely(bio->bi_status)) अणु
		चयन (bio_op(bio)) अणु
		हाल REQ_OP_WRITE_ZEROES:
		हाल REQ_OP_DISCARD:
			अगर (bio->bi_status == BLK_STS_NOTSUPP)
				what = DISCARD_COMPLETED_NOTSUPP;
			अन्यथा
				what = DISCARD_COMPLETED_WITH_ERROR;
			अवरोध;
		हाल REQ_OP_READ:
			अगर (bio->bi_opf & REQ_RAHEAD)
				what = READ_AHEAD_COMPLETED_WITH_ERROR;
			अन्यथा
				what = READ_COMPLETED_WITH_ERROR;
			अवरोध;
		शेष:
			what = WRITE_COMPLETED_WITH_ERROR;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		what = COMPLETED_OK;
	पूर्ण

	req->निजी_bio = ERR_PTR(blk_status_to_त्रुटि_सं(bio->bi_status));
	bio_put(bio);

	/* not req_mod(), we need irqsave here! */
	spin_lock_irqsave(&device->resource->req_lock, flags);
	__req_mod(req, what, &m);
	spin_unlock_irqrestore(&device->resource->req_lock, flags);
	put_ldev(device);

	अगर (m.bio)
		complete_master_bio(device, &m);
पूर्ण

व्योम drbd_csum_ee(काष्ठा crypto_shash *tfm, काष्ठा drbd_peer_request *peer_req, व्योम *digest)
अणु
	SHASH_DESC_ON_STACK(desc, tfm);
	काष्ठा page *page = peer_req->pages;
	काष्ठा page *पंचांगp;
	अचिन्हित len;
	व्योम *src;

	desc->tfm = tfm;

	crypto_shash_init(desc);

	src = kmap_atomic(page);
	जबतक ((पंचांगp = page_chain_next(page))) अणु
		/* all but the last page will be fully used */
		crypto_shash_update(desc, src, PAGE_SIZE);
		kunmap_atomic(src);
		page = पंचांगp;
		src = kmap_atomic(page);
	पूर्ण
	/* and now the last, possibly only partially used page */
	len = peer_req->i.size & (PAGE_SIZE - 1);
	crypto_shash_update(desc, src, len ?: PAGE_SIZE);
	kunmap_atomic(src);

	crypto_shash_final(desc, digest);
	shash_desc_zero(desc);
पूर्ण

व्योम drbd_csum_bio(काष्ठा crypto_shash *tfm, काष्ठा bio *bio, व्योम *digest)
अणु
	SHASH_DESC_ON_STACK(desc, tfm);
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;

	desc->tfm = tfm;

	crypto_shash_init(desc);

	bio_क्रम_each_segment(bvec, bio, iter) अणु
		u8 *src;

		src = kmap_atomic(bvec.bv_page);
		crypto_shash_update(desc, src + bvec.bv_offset, bvec.bv_len);
		kunmap_atomic(src);

		/* REQ_OP_WRITE_SAME has only one segment,
		 * checksum the payload only once. */
		अगर (bio_op(bio) == REQ_OP_WRITE_SAME)
			अवरोध;
	पूर्ण
	crypto_shash_final(desc, digest);
	shash_desc_zero(desc);
पूर्ण

/* MAYBE merge common code with w_e_end_ov_req */
अटल पूर्णांक w_e_send_csum(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_peer_request *peer_req = container_of(w, काष्ठा drbd_peer_request, w);
	काष्ठा drbd_peer_device *peer_device = peer_req->peer_device;
	काष्ठा drbd_device *device = peer_device->device;
	पूर्णांक digest_size;
	व्योम *digest;
	पूर्णांक err = 0;

	अगर (unlikely(cancel))
		जाओ out;

	अगर (unlikely((peer_req->flags & EE_WAS_ERROR) != 0))
		जाओ out;

	digest_size = crypto_shash_digestsize(peer_device->connection->csums_tfm);
	digest = kदो_स्मृति(digest_size, GFP_NOIO);
	अगर (digest) अणु
		sector_t sector = peer_req->i.sector;
		अचिन्हित पूर्णांक size = peer_req->i.size;
		drbd_csum_ee(peer_device->connection->csums_tfm, peer_req, digest);
		/* Free peer_req and pages beक्रमe send.
		 * In हाल we block on congestion, we could otherwise run पूर्णांकo
		 * some distributed deadlock, अगर the other side blocks on
		 * congestion as well, because our receiver blocks in
		 * drbd_alloc_pages due to pp_in_use > max_buffers. */
		drbd_मुक्त_peer_req(device, peer_req);
		peer_req = शून्य;
		inc_rs_pending(device);
		err = drbd_send_drequest_csum(peer_device, sector, size,
					      digest, digest_size,
					      P_CSUM_RS_REQUEST);
		kमुक्त(digest);
	पूर्ण अन्यथा अणु
		drbd_err(device, "kmalloc() of digest failed.\n");
		err = -ENOMEM;
	पूर्ण

out:
	अगर (peer_req)
		drbd_मुक्त_peer_req(device, peer_req);

	अगर (unlikely(err))
		drbd_err(device, "drbd_send_drequest(..., csum) failed\n");
	वापस err;
पूर्ण

#घोषणा GFP_TRY	(__GFP_HIGHMEM | __GFP_NOWARN)

अटल पूर्णांक पढ़ो_क्रम_csum(काष्ठा drbd_peer_device *peer_device, sector_t sector, पूर्णांक size)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा drbd_peer_request *peer_req;

	अगर (!get_ldev(device))
		वापस -EIO;

	/* GFP_TRY, because अगर there is no memory available right now, this may
	 * be rescheduled क्रम later. It is "only" background resync, after all. */
	peer_req = drbd_alloc_peer_req(peer_device, ID_SYNCER /* unused */, sector,
				       size, size, GFP_TRY);
	अगर (!peer_req)
		जाओ defer;

	peer_req->w.cb = w_e_send_csum;
	spin_lock_irq(&device->resource->req_lock);
	list_add_tail(&peer_req->w.list, &device->पढ़ो_ee);
	spin_unlock_irq(&device->resource->req_lock);

	atomic_add(size >> 9, &device->rs_sect_ev);
	अगर (drbd_submit_peer_request(device, peer_req, REQ_OP_READ, 0,
				     DRBD_FAULT_RS_RD) == 0)
		वापस 0;

	/* If it failed because of ENOMEM, retry should help.  If it failed
	 * because bio_add_page failed (probably broken lower level driver),
	 * retry may or may not help.
	 * If it करोes not, you may need to क्रमce disconnect. */
	spin_lock_irq(&device->resource->req_lock);
	list_del(&peer_req->w.list);
	spin_unlock_irq(&device->resource->req_lock);

	drbd_मुक्त_peer_req(device, peer_req);
defer:
	put_ldev(device);
	वापस -EAGAIN;
पूर्ण

पूर्णांक w_resync_समयr(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_device *device =
		container_of(w, काष्ठा drbd_device, resync_work);

	चयन (device->state.conn) अणु
	हाल C_VERIFY_S:
		make_ov_request(device, cancel);
		अवरोध;
	हाल C_SYNC_TARGET:
		make_resync_request(device, cancel);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

व्योम resync_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा drbd_device *device = from_समयr(device, t, resync_समयr);

	drbd_queue_work_अगर_unqueued(
		&first_peer_device(device)->connection->sender_work,
		&device->resync_work);
पूर्ण

अटल व्योम fअगरo_set(काष्ठा fअगरo_buffer *fb, पूर्णांक value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < fb->size; i++)
		fb->values[i] = value;
पूर्ण

अटल पूर्णांक fअगरo_push(काष्ठा fअगरo_buffer *fb, पूर्णांक value)
अणु
	पूर्णांक ov;

	ov = fb->values[fb->head_index];
	fb->values[fb->head_index++] = value;

	अगर (fb->head_index >= fb->size)
		fb->head_index = 0;

	वापस ov;
पूर्ण

अटल व्योम fअगरo_add_val(काष्ठा fअगरo_buffer *fb, पूर्णांक value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < fb->size; i++)
		fb->values[i] += value;
पूर्ण

काष्ठा fअगरo_buffer *fअगरo_alloc(अचिन्हित पूर्णांक fअगरo_size)
अणु
	काष्ठा fअगरo_buffer *fb;

	fb = kzalloc(काष्ठा_size(fb, values, fअगरo_size), GFP_NOIO);
	अगर (!fb)
		वापस शून्य;

	fb->head_index = 0;
	fb->size = fअगरo_size;
	fb->total = 0;

	वापस fb;
पूर्ण

अटल पूर्णांक drbd_rs_controller(काष्ठा drbd_device *device, अचिन्हित पूर्णांक sect_in)
अणु
	काष्ठा disk_conf *dc;
	अचिन्हित पूर्णांक want;     /* The number of sectors we want in-flight */
	पूर्णांक req_sect; /* Number of sectors to request in this turn */
	पूर्णांक correction; /* Number of sectors more we need in-flight */
	पूर्णांक cps; /* correction per invocation of drbd_rs_controller() */
	पूर्णांक steps; /* Number of समय steps to plan ahead */
	पूर्णांक curr_corr;
	पूर्णांक max_sect;
	काष्ठा fअगरo_buffer *plan;

	dc = rcu_dereference(device->ldev->disk_conf);
	plan = rcu_dereference(device->rs_plan_s);

	steps = plan->size; /* (dc->c_plan_ahead * 10 * SLEEP_TIME) / HZ; */

	अगर (device->rs_in_flight + sect_in == 0) अणु /* At start of resync */
		want = ((dc->resync_rate * 2 * SLEEP_TIME) / HZ) * steps;
	पूर्ण अन्यथा अणु /* normal path */
		want = dc->c_fill_target ? dc->c_fill_target :
			sect_in * dc->c_delay_target * HZ / (SLEEP_TIME * 10);
	पूर्ण

	correction = want - device->rs_in_flight - plan->total;

	/* Plan ahead */
	cps = correction / steps;
	fअगरo_add_val(plan, cps);
	plan->total += cps * steps;

	/* What we करो in this step */
	curr_corr = fअगरo_push(plan, 0);
	plan->total -= curr_corr;

	req_sect = sect_in + curr_corr;
	अगर (req_sect < 0)
		req_sect = 0;

	max_sect = (dc->c_max_rate * 2 * SLEEP_TIME) / HZ;
	अगर (req_sect > max_sect)
		req_sect = max_sect;

	/*
	drbd_warn(device, "si=%u if=%d wa=%u co=%d st=%d cps=%d pl=%d cc=%d rs=%d\n",
		 sect_in, device->rs_in_flight, want, correction,
		 steps, cps, device->rs_planed, curr_corr, req_sect);
	*/

	वापस req_sect;
पूर्ण

अटल पूर्णांक drbd_rs_number_requests(काष्ठा drbd_device *device)
अणु
	अचिन्हित पूर्णांक sect_in;  /* Number of sectors that came in since the last turn */
	पूर्णांक number, mxb;

	sect_in = atomic_xchg(&device->rs_sect_in, 0);
	device->rs_in_flight -= sect_in;

	rcu_पढ़ो_lock();
	mxb = drbd_get_max_buffers(device) / 2;
	अगर (rcu_dereference(device->rs_plan_s)->size) अणु
		number = drbd_rs_controller(device, sect_in) >> (BM_BLOCK_SHIFT - 9);
		device->c_sync_rate = number * HZ * (BM_BLOCK_SIZE / 1024) / SLEEP_TIME;
	पूर्ण अन्यथा अणु
		device->c_sync_rate = rcu_dereference(device->ldev->disk_conf)->resync_rate;
		number = SLEEP_TIME * device->c_sync_rate  / ((BM_BLOCK_SIZE / 1024) * HZ);
	पूर्ण
	rcu_पढ़ो_unlock();

	/* Don't have more than "max-buffers"/2 in-flight.
	 * Otherwise we may cause the remote site to stall on drbd_alloc_pages(),
	 * potentially causing a distributed deadlock on congestion during
	 * online-verअगरy or (checksum-based) resync, अगर max-buffers,
	 * socket buffer sizes and resync rate settings are mis-configured. */

	/* note that "number" is in units of "BM_BLOCK_SIZE" (which is 4k),
	 * mxb (as used here, and in drbd_alloc_pages on the peer) is
	 * "number of pages" (typically also 4k),
	 * but "rs_in_flight" is in "sectors" (512 Byte). */
	अगर (mxb - device->rs_in_flight/8 < number)
		number = mxb - device->rs_in_flight/8;

	वापस number;
पूर्ण

अटल पूर्णांक make_resync_request(काष्ठा drbd_device *स्थिर device, पूर्णांक cancel)
अणु
	काष्ठा drbd_peer_device *स्थिर peer_device = first_peer_device(device);
	काष्ठा drbd_connection *स्थिर connection = peer_device ? peer_device->connection : शून्य;
	अचिन्हित दीर्घ bit;
	sector_t sector;
	स्थिर sector_t capacity = get_capacity(device->vdisk);
	पूर्णांक max_bio_size;
	पूर्णांक number, rollback_i, size;
	पूर्णांक align, requeue = 0;
	पूर्णांक i = 0;
	पूर्णांक discard_granularity = 0;

	अगर (unlikely(cancel))
		वापस 0;

	अगर (device->rs_total == 0) अणु
		/* empty resync? */
		drbd_resync_finished(device);
		वापस 0;
	पूर्ण

	अगर (!get_ldev(device)) अणु
		/* Since we only need to access device->rsync a
		   get_ldev_अगर_state(device,D_FAILED) would be sufficient, but
		   to जारी resync with a broken disk makes no sense at
		   all */
		drbd_err(device, "Disk broke down during resync!\n");
		वापस 0;
	पूर्ण

	अगर (connection->agreed_features & DRBD_FF_THIN_RESYNC) अणु
		rcu_पढ़ो_lock();
		discard_granularity = rcu_dereference(device->ldev->disk_conf)->rs_discard_granularity;
		rcu_पढ़ो_unlock();
	पूर्ण

	max_bio_size = queue_max_hw_sectors(device->rq_queue) << 9;
	number = drbd_rs_number_requests(device);
	अगर (number <= 0)
		जाओ requeue;

	क्रम (i = 0; i < number; i++) अणु
		/* Stop generating RS requests when half of the send buffer is filled,
		 * but notअगरy TCP that we'd like to have more space. */
		mutex_lock(&connection->data.mutex);
		अगर (connection->data.socket) अणु
			काष्ठा sock *sk = connection->data.socket->sk;
			पूर्णांक queued = sk->sk_wmem_queued;
			पूर्णांक sndbuf = sk->sk_sndbuf;
			अगर (queued > sndbuf / 2) अणु
				requeue = 1;
				अगर (sk->sk_socket)
					set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
			पूर्ण
		पूर्ण अन्यथा
			requeue = 1;
		mutex_unlock(&connection->data.mutex);
		अगर (requeue)
			जाओ requeue;

next_sector:
		size = BM_BLOCK_SIZE;
		bit  = drbd_bm_find_next(device, device->bm_resync_fo);

		अगर (bit == DRBD_END_OF_BITMAP) अणु
			device->bm_resync_fo = drbd_bm_bits(device);
			put_ldev(device);
			वापस 0;
		पूर्ण

		sector = BM_BIT_TO_SECT(bit);

		अगर (drbd_try_rs_begin_io(device, sector)) अणु
			device->bm_resync_fo = bit;
			जाओ requeue;
		पूर्ण
		device->bm_resync_fo = bit + 1;

		अगर (unlikely(drbd_bm_test_bit(device, bit) == 0)) अणु
			drbd_rs_complete_io(device, sector);
			जाओ next_sector;
		पूर्ण

#अगर DRBD_MAX_BIO_SIZE > BM_BLOCK_SIZE
		/* try to find some adjacent bits.
		 * we stop अगर we have alपढ़ोy the maximum req size.
		 *
		 * Additionally always align bigger requests, in order to
		 * be prepared क्रम all stripe sizes of software RAIDs.
		 */
		align = 1;
		rollback_i = i;
		जबतक (i < number) अणु
			अगर (size + BM_BLOCK_SIZE > max_bio_size)
				अवरोध;

			/* Be always aligned */
			अगर (sector & ((1<<(align+3))-1))
				अवरोध;

			अगर (discard_granularity && size == discard_granularity)
				अवरोध;

			/* करो not cross extent boundaries */
			अगर (((bit+1) & BM_BLOCKS_PER_BM_EXT_MASK) == 0)
				अवरोध;
			/* now, is it actually dirty, after all?
			 * caution, drbd_bm_test_bit is tri-state क्रम some
			 * obscure reason; ( b == 0 ) would get the out-of-band
			 * only accidentally right because of the "oddly sized"
			 * adjusपंचांगent below */
			अगर (drbd_bm_test_bit(device, bit+1) != 1)
				अवरोध;
			bit++;
			size += BM_BLOCK_SIZE;
			अगर ((BM_BLOCK_SIZE << align) <= size)
				align++;
			i++;
		पूर्ण
		/* अगर we merged some,
		 * reset the offset to start the next drbd_bm_find_next from */
		अगर (size > BM_BLOCK_SIZE)
			device->bm_resync_fo = bit + 1;
#पूर्ण_अगर

		/* adjust very last sectors, in हाल we are oddly sized */
		अगर (sector + (size>>9) > capacity)
			size = (capacity-sector)<<9;

		अगर (device->use_csums) अणु
			चयन (पढ़ो_क्रम_csum(peer_device, sector, size)) अणु
			हाल -EIO: /* Disk failure */
				put_ldev(device);
				वापस -EIO;
			हाल -EAGAIN: /* allocation failed, or ldev busy */
				drbd_rs_complete_io(device, sector);
				device->bm_resync_fo = BM_SECT_TO_BIT(sector);
				i = rollback_i;
				जाओ requeue;
			हाल 0:
				/* everything ok */
				अवरोध;
			शेष:
				BUG();
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक err;

			inc_rs_pending(device);
			err = drbd_send_drequest(peer_device,
						 size == discard_granularity ? P_RS_THIN_REQ : P_RS_DATA_REQUEST,
						 sector, size, ID_SYNCER);
			अगर (err) अणु
				drbd_err(device, "drbd_send_drequest() failed, aborting...\n");
				dec_rs_pending(device);
				put_ldev(device);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (device->bm_resync_fo >= drbd_bm_bits(device)) अणु
		/* last syncer _request_ was sent,
		 * but the P_RS_DATA_REPLY not yet received.  sync will end (and
		 * next sync group will resume), as soon as we receive the last
		 * resync data block, and the last bit is cleared.
		 * until then resync "work" is "inactive" ...
		 */
		put_ldev(device);
		वापस 0;
	पूर्ण

 requeue:
	device->rs_in_flight += (i << (BM_BLOCK_SHIFT - 9));
	mod_समयr(&device->resync_समयr, jअगरfies + SLEEP_TIME);
	put_ldev(device);
	वापस 0;
पूर्ण

अटल पूर्णांक make_ov_request(काष्ठा drbd_device *device, पूर्णांक cancel)
अणु
	पूर्णांक number, i, size;
	sector_t sector;
	स्थिर sector_t capacity = get_capacity(device->vdisk);
	bool stop_sector_reached = false;

	अगर (unlikely(cancel))
		वापस 1;

	number = drbd_rs_number_requests(device);

	sector = device->ov_position;
	क्रम (i = 0; i < number; i++) अणु
		अगर (sector >= capacity)
			वापस 1;

		/* We check क्रम "finished" only in the reply path:
		 * w_e_end_ov_reply().
		 * We need to send at least one request out. */
		stop_sector_reached = i > 0
			&& verअगरy_can_करो_stop_sector(device)
			&& sector >= device->ov_stop_sector;
		अगर (stop_sector_reached)
			अवरोध;

		size = BM_BLOCK_SIZE;

		अगर (drbd_try_rs_begin_io(device, sector)) अणु
			device->ov_position = sector;
			जाओ requeue;
		पूर्ण

		अगर (sector + (size>>9) > capacity)
			size = (capacity-sector)<<9;

		inc_rs_pending(device);
		अगर (drbd_send_ov_request(first_peer_device(device), sector, size)) अणु
			dec_rs_pending(device);
			वापस 0;
		पूर्ण
		sector += BM_SECT_PER_BIT;
	पूर्ण
	device->ov_position = sector;

 requeue:
	device->rs_in_flight += (i << (BM_BLOCK_SHIFT - 9));
	अगर (i == 0 || !stop_sector_reached)
		mod_समयr(&device->resync_समयr, jअगरfies + SLEEP_TIME);
	वापस 1;
पूर्ण

पूर्णांक w_ov_finished(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_device_work *dw =
		container_of(w, काष्ठा drbd_device_work, w);
	काष्ठा drbd_device *device = dw->device;
	kमुक्त(dw);
	ov_out_of_sync_prपूर्णांक(device);
	drbd_resync_finished(device);

	वापस 0;
पूर्ण

अटल पूर्णांक w_resync_finished(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_device_work *dw =
		container_of(w, काष्ठा drbd_device_work, w);
	काष्ठा drbd_device *device = dw->device;
	kमुक्त(dw);

	drbd_resync_finished(device);

	वापस 0;
पूर्ण

अटल व्योम ping_peer(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_connection *connection = first_peer_device(device)->connection;

	clear_bit(GOT_PING_ACK, &connection->flags);
	request_ping(connection);
	रुको_event(connection->ping_रुको,
		   test_bit(GOT_PING_ACK, &connection->flags) || device->state.conn < C_CONNECTED);
पूर्ण

पूर्णांक drbd_resync_finished(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_connection *connection = first_peer_device(device)->connection;
	अचिन्हित दीर्घ db, dt, dbdt;
	अचिन्हित दीर्घ n_oos;
	जोड़ drbd_state os, ns;
	काष्ठा drbd_device_work *dw;
	अक्षर *khelper_cmd = शून्य;
	पूर्णांक verअगरy_करोne = 0;

	/* Remove all elements from the resync LRU. Since future actions
	 * might set bits in the (मुख्य) biपंचांगap, then the entries in the
	 * resync LRU would be wrong. */
	अगर (drbd_rs_del_all(device)) अणु
		/* In हाल this is not possible now, most probably because
		 * there are P_RS_DATA_REPLY Packets lingering on the worker's
		 * queue (or even the पढ़ो operations क्रम those packets
		 * is not finished by now).   Retry in 100ms. */

		schedule_समयout_पूर्णांकerruptible(HZ / 10);
		dw = kदो_स्मृति(माप(काष्ठा drbd_device_work), GFP_ATOMIC);
		अगर (dw) अणु
			dw->w.cb = w_resync_finished;
			dw->device = device;
			drbd_queue_work(&connection->sender_work, &dw->w);
			वापस 1;
		पूर्ण
		drbd_err(device, "Warn failed to drbd_rs_del_all() and to kmalloc(dw).\n");
	पूर्ण

	dt = (jअगरfies - device->rs_start - device->rs_छोड़ोd) / HZ;
	अगर (dt <= 0)
		dt = 1;

	db = device->rs_total;
	/* adjust क्रम verअगरy start and stop sectors, respective reached position */
	अगर (device->state.conn == C_VERIFY_S || device->state.conn == C_VERIFY_T)
		db -= device->ov_left;

	dbdt = Bit2KB(db/dt);
	device->rs_छोड़ोd /= HZ;

	अगर (!get_ldev(device))
		जाओ out;

	ping_peer(device);

	spin_lock_irq(&device->resource->req_lock);
	os = drbd_पढ़ो_state(device);

	verअगरy_करोne = (os.conn == C_VERIFY_S || os.conn == C_VERIFY_T);

	/* This protects us against multiple calls (that can happen in the presence
	   of application IO), and against connectivity loss just beक्रमe we arrive here. */
	अगर (os.conn <= C_CONNECTED)
		जाओ out_unlock;

	ns = os;
	ns.conn = C_CONNECTED;

	drbd_info(device, "%s done (total %lu sec; paused %lu sec; %lu K/sec)\n",
	     verअगरy_करोne ? "Online verify" : "Resync",
	     dt + device->rs_छोड़ोd, device->rs_छोड़ोd, dbdt);

	n_oos = drbd_bm_total_weight(device);

	अगर (os.conn == C_VERIFY_S || os.conn == C_VERIFY_T) अणु
		अगर (n_oos) अणु
			drbd_alert(device, "Online verify found %lu %dk block out of sync!\n",
			      n_oos, Bit2KB(1));
			khelper_cmd = "out-of-sync";
		पूर्ण
	पूर्ण अन्यथा अणु
		D_ASSERT(device, (n_oos - device->rs_failed) == 0);

		अगर (os.conn == C_SYNC_TARGET || os.conn == C_PAUSED_SYNC_T)
			khelper_cmd = "after-resync-target";

		अगर (device->use_csums && device->rs_total) अणु
			स्थिर अचिन्हित दीर्घ s = device->rs_same_csum;
			स्थिर अचिन्हित दीर्घ t = device->rs_total;
			स्थिर पूर्णांक ratio =
				(t == 0)     ? 0 :
			(t < 100000) ? ((s*100)/t) : (s/(t/100));
			drbd_info(device, "%u %% had equal checksums, eliminated: %luK; "
			     "transferred %luK total %luK\n",
			     ratio,
			     Bit2KB(device->rs_same_csum),
			     Bit2KB(device->rs_total - device->rs_same_csum),
			     Bit2KB(device->rs_total));
		पूर्ण
	पूर्ण

	अगर (device->rs_failed) अणु
		drbd_info(device, "            %lu failed blocks\n", device->rs_failed);

		अगर (os.conn == C_SYNC_TARGET || os.conn == C_PAUSED_SYNC_T) अणु
			ns.disk = D_INCONSISTENT;
			ns.pdsk = D_UP_TO_DATE;
		पूर्ण अन्यथा अणु
			ns.disk = D_UP_TO_DATE;
			ns.pdsk = D_INCONSISTENT;
		पूर्ण
	पूर्ण अन्यथा अणु
		ns.disk = D_UP_TO_DATE;
		ns.pdsk = D_UP_TO_DATE;

		अगर (os.conn == C_SYNC_TARGET || os.conn == C_PAUSED_SYNC_T) अणु
			अगर (device->p_uuid) अणु
				पूर्णांक i;
				क्रम (i = UI_BITMAP ; i <= UI_HISTORY_END ; i++)
					_drbd_uuid_set(device, i, device->p_uuid[i]);
				drbd_uuid_set(device, UI_BITMAP, device->ldev->md.uuid[UI_CURRENT]);
				_drbd_uuid_set(device, UI_CURRENT, device->p_uuid[UI_CURRENT]);
			पूर्ण अन्यथा अणु
				drbd_err(device, "device->p_uuid is NULL! BUG\n");
			पूर्ण
		पूर्ण

		अगर (!(os.conn == C_VERIFY_S || os.conn == C_VERIFY_T)) अणु
			/* क्रम verअगरy runs, we करोn't update uuids here,
			 * so there would be nothing to report. */
			drbd_uuid_set_bm(device, 0UL);
			drbd_prपूर्णांक_uuids(device, "updated UUIDs");
			अगर (device->p_uuid) अणु
				/* Now the two UUID sets are equal, update what we
				 * know of the peer. */
				पूर्णांक i;
				क्रम (i = UI_CURRENT ; i <= UI_HISTORY_END ; i++)
					device->p_uuid[i] = device->ldev->md.uuid[i];
			पूर्ण
		पूर्ण
	पूर्ण

	_drbd_set_state(device, ns, CS_VERBOSE, शून्य);
out_unlock:
	spin_unlock_irq(&device->resource->req_lock);

	/* If we have been sync source, and have an effective fencing-policy,
	 * once *all* volumes are back in sync, call "unfence". */
	अगर (os.conn == C_SYNC_SOURCE) अणु
		क्रमागत drbd_disk_state disk_state = D_MASK;
		क्रमागत drbd_disk_state pdsk_state = D_MASK;
		क्रमागत drbd_fencing_p fp = FP_DONT_CARE;

		rcu_पढ़ो_lock();
		fp = rcu_dereference(device->ldev->disk_conf)->fencing;
		अगर (fp != FP_DONT_CARE) अणु
			काष्ठा drbd_peer_device *peer_device;
			पूर्णांक vnr;
			idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
				काष्ठा drbd_device *device = peer_device->device;
				disk_state = min_t(क्रमागत drbd_disk_state, disk_state, device->state.disk);
				pdsk_state = min_t(क्रमागत drbd_disk_state, pdsk_state, device->state.pdsk);
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
		अगर (disk_state == D_UP_TO_DATE && pdsk_state == D_UP_TO_DATE)
			conn_khelper(connection, "unfence-peer");
	पूर्ण

	put_ldev(device);
out:
	device->rs_total  = 0;
	device->rs_failed = 0;
	device->rs_छोड़ोd = 0;

	/* reset start sector, अगर we reached end of device */
	अगर (verअगरy_करोne && device->ov_left == 0)
		device->ov_start_sector = 0;

	drbd_md_sync(device);

	अगर (khelper_cmd)
		drbd_khelper(device, khelper_cmd);

	वापस 1;
पूर्ण

/* helper */
अटल व्योम move_to_net_ee_or_मुक्त(काष्ठा drbd_device *device, काष्ठा drbd_peer_request *peer_req)
अणु
	अगर (drbd_peer_req_has_active_page(peer_req)) अणु
		/* This might happen अगर sendpage() has not finished */
		पूर्णांक i = (peer_req->i.size + PAGE_SIZE -1) >> PAGE_SHIFT;
		atomic_add(i, &device->pp_in_use_by_net);
		atomic_sub(i, &device->pp_in_use);
		spin_lock_irq(&device->resource->req_lock);
		list_add_tail(&peer_req->w.list, &device->net_ee);
		spin_unlock_irq(&device->resource->req_lock);
		wake_up(&drbd_pp_रुको);
	पूर्ण अन्यथा
		drbd_मुक्त_peer_req(device, peer_req);
पूर्ण

/**
 * w_e_end_data_req() - Worker callback, to send a P_DATA_REPLY packet in response to a P_DATA_REQUEST
 * @w:		work object.
 * @cancel:	The connection will be बंदd anyways
 */
पूर्णांक w_e_end_data_req(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_peer_request *peer_req = container_of(w, काष्ठा drbd_peer_request, w);
	काष्ठा drbd_peer_device *peer_device = peer_req->peer_device;
	काष्ठा drbd_device *device = peer_device->device;
	पूर्णांक err;

	अगर (unlikely(cancel)) अणु
		drbd_मुक्त_peer_req(device, peer_req);
		dec_unacked(device);
		वापस 0;
	पूर्ण

	अगर (likely((peer_req->flags & EE_WAS_ERROR) == 0)) अणु
		err = drbd_send_block(peer_device, P_DATA_REPLY, peer_req);
	पूर्ण अन्यथा अणु
		अगर (__ratelimit(&drbd_ratelimit_state))
			drbd_err(device, "Sending NegDReply. sector=%llus.\n",
			    (अचिन्हित दीर्घ दीर्घ)peer_req->i.sector);

		err = drbd_send_ack(peer_device, P_NEG_DREPLY, peer_req);
	पूर्ण

	dec_unacked(device);

	move_to_net_ee_or_मुक्त(device, peer_req);

	अगर (unlikely(err))
		drbd_err(device, "drbd_send_block() failed\n");
	वापस err;
पूर्ण

अटल bool all_zero(काष्ठा drbd_peer_request *peer_req)
अणु
	काष्ठा page *page = peer_req->pages;
	अचिन्हित पूर्णांक len = peer_req->i.size;

	page_chain_क्रम_each(page) अणु
		अचिन्हित पूर्णांक l = min_t(अचिन्हित पूर्णांक, len, PAGE_SIZE);
		अचिन्हित पूर्णांक i, words = l / माप(दीर्घ);
		अचिन्हित दीर्घ *d;

		d = kmap_atomic(page);
		क्रम (i = 0; i < words; i++) अणु
			अगर (d[i]) अणु
				kunmap_atomic(d);
				वापस false;
			पूर्ण
		पूर्ण
		kunmap_atomic(d);
		len -= l;
	पूर्ण

	वापस true;
पूर्ण

/**
 * w_e_end_rsdata_req() - Worker callback to send a P_RS_DATA_REPLY packet in response to a P_RS_DATA_REQUEST
 * @w:		work object.
 * @cancel:	The connection will be बंदd anyways
 */
पूर्णांक w_e_end_rsdata_req(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_peer_request *peer_req = container_of(w, काष्ठा drbd_peer_request, w);
	काष्ठा drbd_peer_device *peer_device = peer_req->peer_device;
	काष्ठा drbd_device *device = peer_device->device;
	पूर्णांक err;

	अगर (unlikely(cancel)) अणु
		drbd_मुक्त_peer_req(device, peer_req);
		dec_unacked(device);
		वापस 0;
	पूर्ण

	अगर (get_ldev_अगर_state(device, D_FAILED)) अणु
		drbd_rs_complete_io(device, peer_req->i.sector);
		put_ldev(device);
	पूर्ण

	अगर (device->state.conn == C_AHEAD) अणु
		err = drbd_send_ack(peer_device, P_RS_CANCEL, peer_req);
	पूर्ण अन्यथा अगर (likely((peer_req->flags & EE_WAS_ERROR) == 0)) अणु
		अगर (likely(device->state.pdsk >= D_INCONSISTENT)) अणु
			inc_rs_pending(device);
			अगर (peer_req->flags & EE_RS_THIN_REQ && all_zero(peer_req))
				err = drbd_send_rs_deallocated(peer_device, peer_req);
			अन्यथा
				err = drbd_send_block(peer_device, P_RS_DATA_REPLY, peer_req);
		पूर्ण अन्यथा अणु
			अगर (__ratelimit(&drbd_ratelimit_state))
				drbd_err(device, "Not sending RSDataReply, "
				    "partner DISKLESS!\n");
			err = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (__ratelimit(&drbd_ratelimit_state))
			drbd_err(device, "Sending NegRSDReply. sector %llus.\n",
			    (अचिन्हित दीर्घ दीर्घ)peer_req->i.sector);

		err = drbd_send_ack(peer_device, P_NEG_RS_DREPLY, peer_req);

		/* update resync data with failure */
		drbd_rs_failed_io(device, peer_req->i.sector, peer_req->i.size);
	पूर्ण

	dec_unacked(device);

	move_to_net_ee_or_मुक्त(device, peer_req);

	अगर (unlikely(err))
		drbd_err(device, "drbd_send_block() failed\n");
	वापस err;
पूर्ण

पूर्णांक w_e_end_csum_rs_req(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_peer_request *peer_req = container_of(w, काष्ठा drbd_peer_request, w);
	काष्ठा drbd_peer_device *peer_device = peer_req->peer_device;
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा digest_info *di;
	पूर्णांक digest_size;
	व्योम *digest = शून्य;
	पूर्णांक err, eq = 0;

	अगर (unlikely(cancel)) अणु
		drbd_मुक्त_peer_req(device, peer_req);
		dec_unacked(device);
		वापस 0;
	पूर्ण

	अगर (get_ldev(device)) अणु
		drbd_rs_complete_io(device, peer_req->i.sector);
		put_ldev(device);
	पूर्ण

	di = peer_req->digest;

	अगर (likely((peer_req->flags & EE_WAS_ERROR) == 0)) अणु
		/* quick hack to try to aव्योम a race against reconfiguration.
		 * a real fix would be much more involved,
		 * पूर्णांकroducing more locking mechanisms */
		अगर (peer_device->connection->csums_tfm) अणु
			digest_size = crypto_shash_digestsize(peer_device->connection->csums_tfm);
			D_ASSERT(device, digest_size == di->digest_size);
			digest = kदो_स्मृति(digest_size, GFP_NOIO);
		पूर्ण
		अगर (digest) अणु
			drbd_csum_ee(peer_device->connection->csums_tfm, peer_req, digest);
			eq = !स_भेद(digest, di->digest, digest_size);
			kमुक्त(digest);
		पूर्ण

		अगर (eq) अणु
			drbd_set_in_sync(device, peer_req->i.sector, peer_req->i.size);
			/* rs_same_csums unit is BM_BLOCK_SIZE */
			device->rs_same_csum += peer_req->i.size >> BM_BLOCK_SHIFT;
			err = drbd_send_ack(peer_device, P_RS_IS_IN_SYNC, peer_req);
		पूर्ण अन्यथा अणु
			inc_rs_pending(device);
			peer_req->block_id = ID_SYNCER; /* By setting block_id, digest poपूर्णांकer becomes invalid! */
			peer_req->flags &= ~EE_HAS_DIGEST; /* This peer request no दीर्घer has a digest poपूर्णांकer */
			kमुक्त(di);
			err = drbd_send_block(peer_device, P_RS_DATA_REPLY, peer_req);
		पूर्ण
	पूर्ण अन्यथा अणु
		err = drbd_send_ack(peer_device, P_NEG_RS_DREPLY, peer_req);
		अगर (__ratelimit(&drbd_ratelimit_state))
			drbd_err(device, "Sending NegDReply. I guess it gets messy.\n");
	पूर्ण

	dec_unacked(device);
	move_to_net_ee_or_मुक्त(device, peer_req);

	अगर (unlikely(err))
		drbd_err(device, "drbd_send_block/ack() failed\n");
	वापस err;
पूर्ण

पूर्णांक w_e_end_ov_req(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_peer_request *peer_req = container_of(w, काष्ठा drbd_peer_request, w);
	काष्ठा drbd_peer_device *peer_device = peer_req->peer_device;
	काष्ठा drbd_device *device = peer_device->device;
	sector_t sector = peer_req->i.sector;
	अचिन्हित पूर्णांक size = peer_req->i.size;
	पूर्णांक digest_size;
	व्योम *digest;
	पूर्णांक err = 0;

	अगर (unlikely(cancel))
		जाओ out;

	digest_size = crypto_shash_digestsize(peer_device->connection->verअगरy_tfm);
	digest = kदो_स्मृति(digest_size, GFP_NOIO);
	अगर (!digest) अणु
		err = 1;	/* terminate the connection in हाल the allocation failed */
		जाओ out;
	पूर्ण

	अगर (likely(!(peer_req->flags & EE_WAS_ERROR)))
		drbd_csum_ee(peer_device->connection->verअगरy_tfm, peer_req, digest);
	अन्यथा
		स_रखो(digest, 0, digest_size);

	/* Free e and pages beक्रमe send.
	 * In हाल we block on congestion, we could otherwise run पूर्णांकo
	 * some distributed deadlock, अगर the other side blocks on
	 * congestion as well, because our receiver blocks in
	 * drbd_alloc_pages due to pp_in_use > max_buffers. */
	drbd_मुक्त_peer_req(device, peer_req);
	peer_req = शून्य;
	inc_rs_pending(device);
	err = drbd_send_drequest_csum(peer_device, sector, size, digest, digest_size, P_OV_REPLY);
	अगर (err)
		dec_rs_pending(device);
	kमुक्त(digest);

out:
	अगर (peer_req)
		drbd_मुक्त_peer_req(device, peer_req);
	dec_unacked(device);
	वापस err;
पूर्ण

व्योम drbd_ov_out_of_sync_found(काष्ठा drbd_device *device, sector_t sector, पूर्णांक size)
अणु
	अगर (device->ov_last_oos_start + device->ov_last_oos_size == sector) अणु
		device->ov_last_oos_size += size>>9;
	पूर्ण अन्यथा अणु
		device->ov_last_oos_start = sector;
		device->ov_last_oos_size = size>>9;
	पूर्ण
	drbd_set_out_of_sync(device, sector, size);
पूर्ण

पूर्णांक w_e_end_ov_reply(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_peer_request *peer_req = container_of(w, काष्ठा drbd_peer_request, w);
	काष्ठा drbd_peer_device *peer_device = peer_req->peer_device;
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा digest_info *di;
	व्योम *digest;
	sector_t sector = peer_req->i.sector;
	अचिन्हित पूर्णांक size = peer_req->i.size;
	पूर्णांक digest_size;
	पूर्णांक err, eq = 0;
	bool stop_sector_reached = false;

	अगर (unlikely(cancel)) अणु
		drbd_मुक्त_peer_req(device, peer_req);
		dec_unacked(device);
		वापस 0;
	पूर्ण

	/* after "cancel", because after drbd_disconnect/drbd_rs_cancel_all
	 * the resync lru has been cleaned up alपढ़ोy */
	अगर (get_ldev(device)) अणु
		drbd_rs_complete_io(device, peer_req->i.sector);
		put_ldev(device);
	पूर्ण

	di = peer_req->digest;

	अगर (likely((peer_req->flags & EE_WAS_ERROR) == 0)) अणु
		digest_size = crypto_shash_digestsize(peer_device->connection->verअगरy_tfm);
		digest = kदो_स्मृति(digest_size, GFP_NOIO);
		अगर (digest) अणु
			drbd_csum_ee(peer_device->connection->verअगरy_tfm, peer_req, digest);

			D_ASSERT(device, digest_size == di->digest_size);
			eq = !स_भेद(digest, di->digest, digest_size);
			kमुक्त(digest);
		पूर्ण
	पूर्ण

	/* Free peer_req and pages beक्रमe send.
	 * In हाल we block on congestion, we could otherwise run पूर्णांकo
	 * some distributed deadlock, अगर the other side blocks on
	 * congestion as well, because our receiver blocks in
	 * drbd_alloc_pages due to pp_in_use > max_buffers. */
	drbd_मुक्त_peer_req(device, peer_req);
	अगर (!eq)
		drbd_ov_out_of_sync_found(device, sector, size);
	अन्यथा
		ov_out_of_sync_prपूर्णांक(device);

	err = drbd_send_ack_ex(peer_device, P_OV_RESULT, sector, size,
			       eq ? ID_IN_SYNC : ID_OUT_OF_SYNC);

	dec_unacked(device);

	--device->ov_left;

	/* let's advance progress step marks only क्रम every other megabyte */
	अगर ((device->ov_left & 0x200) == 0x200)
		drbd_advance_rs_marks(device, device->ov_left);

	stop_sector_reached = verअगरy_can_करो_stop_sector(device) &&
		(sector + (size>>9)) >= device->ov_stop_sector;

	अगर (device->ov_left == 0 || stop_sector_reached) अणु
		ov_out_of_sync_prपूर्णांक(device);
		drbd_resync_finished(device);
	पूर्ण

	वापस err;
पूर्ण

/* FIXME
 * We need to track the number of pending barrier acks,
 * and to be able to रुको क्रम them.
 * See also comment in drbd_adm_attach beक्रमe drbd_suspend_io.
 */
अटल पूर्णांक drbd_send_barrier(काष्ठा drbd_connection *connection)
अणु
	काष्ठा p_barrier *p;
	काष्ठा drbd_socket *sock;

	sock = &connection->data;
	p = conn_prepare_command(connection, sock);
	अगर (!p)
		वापस -EIO;
	p->barrier = connection->send.current_epoch_nr;
	p->pad = 0;
	connection->send.current_epoch_ग_लिखोs = 0;
	connection->send.last_sent_barrier_jअगर = jअगरfies;

	वापस conn_send_command(connection, sock, P_BARRIER, माप(*p), शून्य, 0);
पूर्ण

अटल पूर्णांक pd_send_unplug_remote(काष्ठा drbd_peer_device *pd)
अणु
	काष्ठा drbd_socket *sock = &pd->connection->data;
	अगर (!drbd_prepare_command(pd, sock))
		वापस -EIO;
	वापस drbd_send_command(pd, sock, P_UNPLUG_REMOTE, 0, शून्य, 0);
पूर्ण

पूर्णांक w_send_ग_लिखो_hपूर्णांक(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_device *device =
		container_of(w, काष्ठा drbd_device, unplug_work);

	अगर (cancel)
		वापस 0;
	वापस pd_send_unplug_remote(first_peer_device(device));
पूर्ण

अटल व्योम re_init_अगर_first_ग_लिखो(काष्ठा drbd_connection *connection, अचिन्हित पूर्णांक epoch)
अणु
	अगर (!connection->send.seen_any_ग_लिखो_yet) अणु
		connection->send.seen_any_ग_लिखो_yet = true;
		connection->send.current_epoch_nr = epoch;
		connection->send.current_epoch_ग_लिखोs = 0;
		connection->send.last_sent_barrier_jअगर = jअगरfies;
	पूर्ण
पूर्ण

अटल व्योम maybe_send_barrier(काष्ठा drbd_connection *connection, अचिन्हित पूर्णांक epoch)
अणु
	/* re-init अगर first ग_लिखो on this connection */
	अगर (!connection->send.seen_any_ग_लिखो_yet)
		वापस;
	अगर (connection->send.current_epoch_nr != epoch) अणु
		अगर (connection->send.current_epoch_ग_लिखोs)
			drbd_send_barrier(connection);
		connection->send.current_epoch_nr = epoch;
	पूर्ण
पूर्ण

पूर्णांक w_send_out_of_sync(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_request *req = container_of(w, काष्ठा drbd_request, w);
	काष्ठा drbd_device *device = req->device;
	काष्ठा drbd_peer_device *स्थिर peer_device = first_peer_device(device);
	काष्ठा drbd_connection *स्थिर connection = peer_device->connection;
	पूर्णांक err;

	अगर (unlikely(cancel)) अणु
		req_mod(req, SEND_CANCELED);
		वापस 0;
	पूर्ण
	req->pre_send_jअगर = jअगरfies;

	/* this समय, no connection->send.current_epoch_ग_लिखोs++;
	 * If it was sent, it was the closing barrier क्रम the last
	 * replicated epoch, beक्रमe we went पूर्णांकo AHEAD mode.
	 * No more barriers will be sent, until we leave AHEAD mode again. */
	maybe_send_barrier(connection, req->epoch);

	err = drbd_send_out_of_sync(peer_device, req);
	req_mod(req, OOS_HANDED_TO_NETWORK);

	वापस err;
पूर्ण

/**
 * w_send_dblock() - Worker callback to send a P_DATA packet in order to mirror a ग_लिखो request
 * @w:		work object.
 * @cancel:	The connection will be बंदd anyways
 */
पूर्णांक w_send_dblock(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_request *req = container_of(w, काष्ठा drbd_request, w);
	काष्ठा drbd_device *device = req->device;
	काष्ठा drbd_peer_device *स्थिर peer_device = first_peer_device(device);
	काष्ठा drbd_connection *connection = peer_device->connection;
	bool करो_send_unplug = req->rq_state & RQ_UNPLUG;
	पूर्णांक err;

	अगर (unlikely(cancel)) अणु
		req_mod(req, SEND_CANCELED);
		वापस 0;
	पूर्ण
	req->pre_send_jअगर = jअगरfies;

	re_init_अगर_first_ग_लिखो(connection, req->epoch);
	maybe_send_barrier(connection, req->epoch);
	connection->send.current_epoch_ग_लिखोs++;

	err = drbd_send_dblock(peer_device, req);
	req_mod(req, err ? SEND_FAILED : HANDED_OVER_TO_NETWORK);

	अगर (करो_send_unplug && !err)
		pd_send_unplug_remote(peer_device);

	वापस err;
पूर्ण

/**
 * w_send_पढ़ो_req() - Worker callback to send a पढ़ो request (P_DATA_REQUEST) packet
 * @w:		work object.
 * @cancel:	The connection will be बंदd anyways
 */
पूर्णांक w_send_पढ़ो_req(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_request *req = container_of(w, काष्ठा drbd_request, w);
	काष्ठा drbd_device *device = req->device;
	काष्ठा drbd_peer_device *स्थिर peer_device = first_peer_device(device);
	काष्ठा drbd_connection *connection = peer_device->connection;
	bool करो_send_unplug = req->rq_state & RQ_UNPLUG;
	पूर्णांक err;

	अगर (unlikely(cancel)) अणु
		req_mod(req, SEND_CANCELED);
		वापस 0;
	पूर्ण
	req->pre_send_jअगर = jअगरfies;

	/* Even पढ़ो requests may बंद a ग_लिखो epoch,
	 * अगर there was any yet. */
	maybe_send_barrier(connection, req->epoch);

	err = drbd_send_drequest(peer_device, P_DATA_REQUEST, req->i.sector, req->i.size,
				 (अचिन्हित दीर्घ)req);

	req_mod(req, err ? SEND_FAILED : HANDED_OVER_TO_NETWORK);

	अगर (करो_send_unplug && !err)
		pd_send_unplug_remote(peer_device);

	वापस err;
पूर्ण

पूर्णांक w_restart_disk_io(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा drbd_request *req = container_of(w, काष्ठा drbd_request, w);
	काष्ठा drbd_device *device = req->device;

	अगर (bio_data_dir(req->master_bio) == WRITE && req->rq_state & RQ_IN_ACT_LOG)
		drbd_al_begin_io(device, &req->i);

	req->निजी_bio = bio_clone_fast(req->master_bio, GFP_NOIO,
					  &drbd_io_bio_set);
	bio_set_dev(req->निजी_bio, device->ldev->backing_bdev);
	req->निजी_bio->bi_निजी = req;
	req->निजी_bio->bi_end_io = drbd_request_endio;
	submit_bio_noacct(req->निजी_bio);

	वापस 0;
पूर्ण

अटल पूर्णांक _drbd_may_sync_now(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_device *odev = device;
	पूर्णांक resync_after;

	जबतक (1) अणु
		अगर (!odev->ldev || odev->state.disk == D_DISKLESS)
			वापस 1;
		rcu_पढ़ो_lock();
		resync_after = rcu_dereference(odev->ldev->disk_conf)->resync_after;
		rcu_पढ़ो_unlock();
		अगर (resync_after == -1)
			वापस 1;
		odev = minor_to_device(resync_after);
		अगर (!odev)
			वापस 1;
		अगर ((odev->state.conn >= C_SYNC_SOURCE &&
		     odev->state.conn <= C_PAUSED_SYNC_T) ||
		    odev->state.aftr_isp || odev->state.peer_isp ||
		    odev->state.user_isp)
			वापस 0;
	पूर्ण
पूर्ण

/**
 * drbd_छोड़ो_after() - Pause resync on all devices that may not resync now
 * @device:	DRBD device.
 *
 * Called from process context only (admin command and after_state_ch).
 */
अटल bool drbd_छोड़ो_after(काष्ठा drbd_device *device)
अणु
	bool changed = false;
	काष्ठा drbd_device *odev;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&drbd_devices, odev, i) अणु
		अगर (odev->state.conn == C_STANDALONE && odev->state.disk == D_DISKLESS)
			जारी;
		अगर (!_drbd_may_sync_now(odev) &&
		    _drbd_set_state(_NS(odev, aftr_isp, 1),
				    CS_HARD, शून्य) != SS_NOTHING_TO_DO)
			changed = true;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस changed;
पूर्ण

/**
 * drbd_resume_next() - Resume resync on all devices that may resync now
 * @device:	DRBD device.
 *
 * Called from process context only (admin command and worker).
 */
अटल bool drbd_resume_next(काष्ठा drbd_device *device)
अणु
	bool changed = false;
	काष्ठा drbd_device *odev;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&drbd_devices, odev, i) अणु
		अगर (odev->state.conn == C_STANDALONE && odev->state.disk == D_DISKLESS)
			जारी;
		अगर (odev->state.aftr_isp) अणु
			अगर (_drbd_may_sync_now(odev) &&
			    _drbd_set_state(_NS(odev, aftr_isp, 0),
					    CS_HARD, शून्य) != SS_NOTHING_TO_DO)
				changed = true;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस changed;
पूर्ण

व्योम resume_next_sg(काष्ठा drbd_device *device)
अणु
	lock_all_resources();
	drbd_resume_next(device);
	unlock_all_resources();
पूर्ण

व्योम suspend_other_sg(काष्ठा drbd_device *device)
अणु
	lock_all_resources();
	drbd_छोड़ो_after(device);
	unlock_all_resources();
पूर्ण

/* caller must lock_all_resources() */
क्रमागत drbd_ret_code drbd_resync_after_valid(काष्ठा drbd_device *device, पूर्णांक o_minor)
अणु
	काष्ठा drbd_device *odev;
	पूर्णांक resync_after;

	अगर (o_minor == -1)
		वापस NO_ERROR;
	अगर (o_minor < -1 || o_minor > MINORMASK)
		वापस ERR_RESYNC_AFTER;

	/* check क्रम loops */
	odev = minor_to_device(o_minor);
	जबतक (1) अणु
		अगर (odev == device)
			वापस ERR_RESYNC_AFTER_CYCLE;

		/* You are मुक्त to depend on diskless, non-existing,
		 * or not yet/no दीर्घer existing minors.
		 * We only reject dependency loops.
		 * We cannot follow the dependency chain beyond a detached or
		 * missing minor.
		 */
		अगर (!odev || !odev->ldev || odev->state.disk == D_DISKLESS)
			वापस NO_ERROR;

		rcu_पढ़ो_lock();
		resync_after = rcu_dereference(odev->ldev->disk_conf)->resync_after;
		rcu_पढ़ो_unlock();
		/* dependency chain ends here, no cycles. */
		अगर (resync_after == -1)
			वापस NO_ERROR;

		/* follow the dependency chain */
		odev = minor_to_device(resync_after);
	पूर्ण
पूर्ण

/* caller must lock_all_resources() */
व्योम drbd_resync_after_changed(काष्ठा drbd_device *device)
अणु
	पूर्णांक changed;

	करो अणु
		changed  = drbd_छोड़ो_after(device);
		changed |= drbd_resume_next(device);
	पूर्ण जबतक (changed);
पूर्ण

व्योम drbd_rs_controller_reset(काष्ठा drbd_device *device)
अणु
	काष्ठा gendisk *disk = device->ldev->backing_bdev->bd_disk;
	काष्ठा fअगरo_buffer *plan;

	atomic_set(&device->rs_sect_in, 0);
	atomic_set(&device->rs_sect_ev, 0);
	device->rs_in_flight = 0;
	device->rs_last_events =
		(पूर्णांक)part_stat_पढ़ो_accum(disk->part0, sectors);

	/* Updating the RCU रक्षित object in place is necessary since
	   this function माला_लो called from atomic context.
	   It is valid since all other updates also lead to an completely
	   empty fअगरo */
	rcu_पढ़ो_lock();
	plan = rcu_dereference(device->rs_plan_s);
	plan->total = 0;
	fअगरo_set(plan, 0);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम start_resync_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा drbd_device *device = from_समयr(device, t, start_resync_समयr);
	drbd_device_post_work(device, RS_START);
पूर्ण

अटल व्योम करो_start_resync(काष्ठा drbd_device *device)
अणु
	अगर (atomic_पढ़ो(&device->unacked_cnt) || atomic_पढ़ो(&device->rs_pending_cnt)) अणु
		drbd_warn(device, "postponing start_resync ...\n");
		device->start_resync_समयr.expires = jअगरfies + HZ/10;
		add_समयr(&device->start_resync_समयr);
		वापस;
	पूर्ण

	drbd_start_resync(device, C_SYNC_SOURCE);
	clear_bit(AHEAD_TO_SYNC_SOURCE, &device->flags);
पूर्ण

अटल bool use_checksum_based_resync(काष्ठा drbd_connection *connection, काष्ठा drbd_device *device)
अणु
	bool csums_after_crash_only;
	rcu_पढ़ो_lock();
	csums_after_crash_only = rcu_dereference(connection->net_conf)->csums_after_crash_only;
	rcu_पढ़ो_unlock();
	वापस connection->agreed_pro_version >= 89 &&		/* supported? */
		connection->csums_tfm &&			/* configured? */
		(csums_after_crash_only == false		/* use क्रम each resync? */
		 || test_bit(CRASHED_PRIMARY, &device->flags));	/* or only after Primary crash? */
पूर्ण

/**
 * drbd_start_resync() - Start the resync process
 * @device:	DRBD device.
 * @side:	Either C_SYNC_SOURCE or C_SYNC_TARGET
 *
 * This function might bring you directly पूर्णांकo one of the
 * C_PAUSED_SYNC_* states.
 */
व्योम drbd_start_resync(काष्ठा drbd_device *device, क्रमागत drbd_conns side)
अणु
	काष्ठा drbd_peer_device *peer_device = first_peer_device(device);
	काष्ठा drbd_connection *connection = peer_device ? peer_device->connection : शून्य;
	जोड़ drbd_state ns;
	पूर्णांक r;

	अगर (device->state.conn >= C_SYNC_SOURCE && device->state.conn < C_AHEAD) अणु
		drbd_err(device, "Resync already running!\n");
		वापस;
	पूर्ण

	अगर (!connection) अणु
		drbd_err(device, "No connection to peer, aborting!\n");
		वापस;
	पूर्ण

	अगर (!test_bit(B_RS_H_DONE, &device->flags)) अणु
		अगर (side == C_SYNC_TARGET) अणु
			/* Since application IO was locked out during C_WF_BITMAP_T and
			   C_WF_SYNC_UUID we are still unmodअगरied. Beक्रमe going to C_SYNC_TARGET
			   we check that we might make the data inconsistent. */
			r = drbd_khelper(device, "before-resync-target");
			r = (r >> 8) & 0xff;
			अगर (r > 0) अणु
				drbd_info(device, "before-resync-target handler returned %d, "
					 "dropping connection.\n", r);
				conn_request_state(connection, NS(conn, C_DISCONNECTING), CS_HARD);
				वापस;
			पूर्ण
		पूर्ण अन्यथा /* C_SYNC_SOURCE */ अणु
			r = drbd_khelper(device, "before-resync-source");
			r = (r >> 8) & 0xff;
			अगर (r > 0) अणु
				अगर (r == 3) अणु
					drbd_info(device, "before-resync-source handler returned %d, "
						 "ignoring. Old userland tools?", r);
				पूर्ण अन्यथा अणु
					drbd_info(device, "before-resync-source handler returned %d, "
						 "dropping connection.\n", r);
					conn_request_state(connection,
							   NS(conn, C_DISCONNECTING), CS_HARD);
					वापस;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (current == connection->worker.task) अणु
		/* The worker should not sleep रुकोing क्रम state_mutex,
		   that can take दीर्घ */
		अगर (!mutex_trylock(device->state_mutex)) अणु
			set_bit(B_RS_H_DONE, &device->flags);
			device->start_resync_समयr.expires = jअगरfies + HZ/5;
			add_समयr(&device->start_resync_समयr);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_lock(device->state_mutex);
	पूर्ण

	lock_all_resources();
	clear_bit(B_RS_H_DONE, &device->flags);
	/* Did some connection अवरोधage or IO error race with us? */
	अगर (device->state.conn < C_CONNECTED
	|| !get_ldev_अगर_state(device, D_NEGOTIATING)) अणु
		unlock_all_resources();
		जाओ out;
	पूर्ण

	ns = drbd_पढ़ो_state(device);

	ns.aftr_isp = !_drbd_may_sync_now(device);

	ns.conn = side;

	अगर (side == C_SYNC_TARGET)
		ns.disk = D_INCONSISTENT;
	अन्यथा /* side == C_SYNC_SOURCE */
		ns.pdsk = D_INCONSISTENT;

	r = _drbd_set_state(device, ns, CS_VERBOSE, शून्य);
	ns = drbd_पढ़ो_state(device);

	अगर (ns.conn < C_CONNECTED)
		r = SS_UNKNOWN_ERROR;

	अगर (r == SS_SUCCESS) अणु
		अचिन्हित दीर्घ tw = drbd_bm_total_weight(device);
		अचिन्हित दीर्घ now = jअगरfies;
		पूर्णांक i;

		device->rs_failed    = 0;
		device->rs_छोड़ोd    = 0;
		device->rs_same_csum = 0;
		device->rs_last_sect_ev = 0;
		device->rs_total     = tw;
		device->rs_start     = now;
		क्रम (i = 0; i < DRBD_SYNC_MARKS; i++) अणु
			device->rs_mark_left[i] = tw;
			device->rs_mark_समय[i] = now;
		पूर्ण
		drbd_छोड़ो_after(device);
		/* Forget potentially stale cached per resync extent bit-counts.
		 * Open coded drbd_rs_cancel_all(device), we alपढ़ोy have IRQs
		 * disabled, and know the disk state is ok. */
		spin_lock(&device->al_lock);
		lc_reset(device->resync);
		device->resync_locked = 0;
		device->resync_wenr = LC_FREE;
		spin_unlock(&device->al_lock);
	पूर्ण
	unlock_all_resources();

	अगर (r == SS_SUCCESS) अणु
		wake_up(&device->al_रुको); /* क्रम lc_reset() above */
		/* reset rs_last_bcast when a resync or verअगरy is started,
		 * to deal with potential jअगरfies wrap. */
		device->rs_last_bcast = jअगरfies - HZ;

		drbd_info(device, "Began resync as %s (will sync %lu KB [%lu bits set]).\n",
		     drbd_conn_str(ns.conn),
		     (अचिन्हित दीर्घ) device->rs_total << (BM_BLOCK_SHIFT-10),
		     (अचिन्हित दीर्घ) device->rs_total);
		अगर (side == C_SYNC_TARGET) अणु
			device->bm_resync_fo = 0;
			device->use_csums = use_checksum_based_resync(connection, device);
		पूर्ण अन्यथा अणु
			device->use_csums = false;
		पूर्ण

		/* Since protocol 96, we must serialize drbd_gen_and_send_sync_uuid
		 * with w_send_oos, or the sync target will get confused as to
		 * how much bits to resync.  We cannot करो that always, because क्रम an
		 * empty resync and protocol < 95, we need to करो it here, as we call
		 * drbd_resync_finished from here in that हाल.
		 * We drbd_gen_and_send_sync_uuid here क्रम protocol < 96,
		 * and from after_state_ch otherwise. */
		अगर (side == C_SYNC_SOURCE && connection->agreed_pro_version < 96)
			drbd_gen_and_send_sync_uuid(peer_device);

		अगर (connection->agreed_pro_version < 95 && device->rs_total == 0) अणु
			/* This still has a race (about when exactly the peers
			 * detect connection loss) that can lead to a full sync
			 * on next handshake. In 8.3.9 we fixed this with explicit
			 * resync-finished notअगरications, but the fix
			 * पूर्णांकroduces a protocol change.  Sleeping क्रम some
			 * समय दीर्घer than the ping पूर्णांकerval + समयout on the
			 * SyncSource, to give the SyncTarget the chance to
			 * detect connection loss, then रुकोing क्रम a ping
			 * response (implicit in drbd_resync_finished) reduces
			 * the race considerably, but करोes not solve it. */
			अगर (side == C_SYNC_SOURCE) अणु
				काष्ठा net_conf *nc;
				पूर्णांक समयo;

				rcu_पढ़ो_lock();
				nc = rcu_dereference(connection->net_conf);
				समयo = nc->ping_पूर्णांक * HZ + nc->ping_समयo * HZ / 9;
				rcu_पढ़ो_unlock();
				schedule_समयout_पूर्णांकerruptible(समयo);
			पूर्ण
			drbd_resync_finished(device);
		पूर्ण

		drbd_rs_controller_reset(device);
		/* ns.conn may alपढ़ोy be != device->state.conn,
		 * we may have been छोड़ोd in between, or become छोड़ोd until
		 * the समयr triggers.
		 * No matter, that is handled in resync_समयr_fn() */
		अगर (ns.conn == C_SYNC_TARGET)
			mod_समयr(&device->resync_समयr, jअगरfies);

		drbd_md_sync(device);
	पूर्ण
	put_ldev(device);
out:
	mutex_unlock(device->state_mutex);
पूर्ण

अटल व्योम update_on_disk_biपंचांगap(काष्ठा drbd_device *device, bool resync_करोne)
अणु
	काष्ठा sib_info sib = अणु .sib_reason = SIB_SYNC_PROGRESS, पूर्ण;
	device->rs_last_bcast = jअगरfies;

	अगर (!get_ldev(device))
		वापस;

	drbd_bm_ग_लिखो_lazy(device, 0);
	अगर (resync_करोne && is_sync_state(device->state.conn))
		drbd_resync_finished(device);

	drbd_bcast_event(device, &sib);
	/* update बारtamp, in हाल it took a जबतक to ग_लिखो out stuff */
	device->rs_last_bcast = jअगरfies;
	put_ldev(device);
पूर्ण

अटल व्योम drbd_ldev_destroy(काष्ठा drbd_device *device)
अणु
	lc_destroy(device->resync);
	device->resync = शून्य;
	lc_destroy(device->act_log);
	device->act_log = शून्य;

	__acquire(local);
	drbd_backing_dev_मुक्त(device, device->ldev);
	device->ldev = शून्य;
	__release(local);

	clear_bit(GOING_DISKLESS, &device->flags);
	wake_up(&device->misc_रुको);
पूर्ण

अटल व्योम go_diskless(काष्ठा drbd_device *device)
अणु
	D_ASSERT(device, device->state.disk == D_FAILED);
	/* we cannot निश्चित local_cnt == 0 here, as get_ldev_अगर_state will
	 * inc/dec it frequently. Once we are D_DISKLESS, no one will touch
	 * the रक्षित members anymore, though, so once put_ldev reaches zero
	 * again, it will be safe to मुक्त them. */

	/* Try to ग_लिखो changed biपंचांगap pages, पढ़ो errors may have just
	 * set some bits outside the area covered by the activity log.
	 *
	 * If we have an IO error during the biपंचांगap ग_लिखोout,
	 * we will want a full sync next समय, just in हाल.
	 * (Do we want a specअगरic meta data flag क्रम this?)
	 *
	 * If that करोes not make it to stable storage either,
	 * we cannot करो anything about that anymore.
	 *
	 * We still need to check अगर both biपंचांगap and ldev are present, we may
	 * end up here after a failed attach, beक्रमe ldev was even asचिन्हित.
	 */
	अगर (device->biपंचांगap && device->ldev) अणु
		/* An पूर्णांकerrupted resync or similar is allowed to recounts bits
		 * जबतक we detach.
		 * Any modअगरications would not be expected anymore, though.
		 */
		अगर (drbd_biपंचांगap_io_from_worker(device, drbd_bm_ग_लिखो,
					"detach", BM_LOCKED_TEST_ALLOWED)) अणु
			अगर (test_bit(WAS_READ_ERROR, &device->flags)) अणु
				drbd_md_set_flag(device, MDF_FULL_SYNC);
				drbd_md_sync(device);
			पूर्ण
		पूर्ण
	पूर्ण

	drbd_क्रमce_state(device, NS(disk, D_DISKLESS));
पूर्ण

अटल पूर्णांक करो_md_sync(काष्ठा drbd_device *device)
अणु
	drbd_warn(device, "md_sync_timer expired! Worker calls drbd_md_sync().\n");
	drbd_md_sync(device);
	वापस 0;
पूर्ण

/* only called from drbd_worker thपढ़ो, no locking */
व्योम __update_timing_details(
		काष्ठा drbd_thपढ़ो_timing_details *tdp,
		अचिन्हित पूर्णांक *cb_nr,
		व्योम *cb,
		स्थिर अक्षर *fn, स्थिर अचिन्हित पूर्णांक line)
अणु
	अचिन्हित पूर्णांक i = *cb_nr % DRBD_THREAD_DETAILS_HIST;
	काष्ठा drbd_thपढ़ो_timing_details *td = tdp + i;

	td->start_jअगर = jअगरfies;
	td->cb_addr = cb;
	td->caller_fn = fn;
	td->line = line;
	td->cb_nr = *cb_nr;

	i = (i+1) % DRBD_THREAD_DETAILS_HIST;
	td = tdp + i;
	स_रखो(td, 0, माप(*td));

	++(*cb_nr);
पूर्ण

अटल व्योम करो_device_work(काष्ठा drbd_device *device, स्थिर अचिन्हित दीर्घ toकरो)
अणु
	अगर (test_bit(MD_SYNC, &toकरो))
		करो_md_sync(device);
	अगर (test_bit(RS_DONE, &toकरो) ||
	    test_bit(RS_PROGRESS, &toकरो))
		update_on_disk_biपंचांगap(device, test_bit(RS_DONE, &toकरो));
	अगर (test_bit(GO_DISKLESS, &toकरो))
		go_diskless(device);
	अगर (test_bit(DESTROY_DISK, &toकरो))
		drbd_ldev_destroy(device);
	अगर (test_bit(RS_START, &toकरो))
		करो_start_resync(device);
पूर्ण

#घोषणा DRBD_DEVICE_WORK_MASK	\
	((1UL << GO_DISKLESS)	\
	|(1UL << DESTROY_DISK)	\
	|(1UL << MD_SYNC)	\
	|(1UL << RS_START)	\
	|(1UL << RS_PROGRESS)	\
	|(1UL << RS_DONE)	\
	)

अटल अचिन्हित दीर्घ get_work_bits(अचिन्हित दीर्घ *flags)
अणु
	अचिन्हित दीर्घ old, new;
	करो अणु
		old = *flags;
		new = old & ~DRBD_DEVICE_WORK_MASK;
	पूर्ण जबतक (cmpxchg(flags, old, new) != old);
	वापस old & DRBD_DEVICE_WORK_MASK;
पूर्ण

अटल व्योम करो_unqueued_work(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		अचिन्हित दीर्घ toकरो = get_work_bits(&device->flags);
		अगर (!toकरो)
			जारी;

		kref_get(&device->kref);
		rcu_पढ़ो_unlock();
		करो_device_work(device, toकरो);
		kref_put(&device->kref, drbd_destroy_device);
		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल bool dequeue_work_batch(काष्ठा drbd_work_queue *queue, काष्ठा list_head *work_list)
अणु
	spin_lock_irq(&queue->q_lock);
	list_splice_tail_init(&queue->q, work_list);
	spin_unlock_irq(&queue->q_lock);
	वापस !list_empty(work_list);
पूर्ण

अटल व्योम रुको_क्रम_work(काष्ठा drbd_connection *connection, काष्ठा list_head *work_list)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा net_conf *nc;
	पूर्णांक uncork, cork;

	dequeue_work_batch(&connection->sender_work, work_list);
	अगर (!list_empty(work_list))
		वापस;

	/* Still nothing to करो?
	 * Maybe we still need to बंद the current epoch,
	 * even अगर no new requests are queued yet.
	 *
	 * Also, poke TCP, just in हाल.
	 * Then रुको क्रम new work (or संकेत). */
	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	uncork = nc ? nc->tcp_cork : 0;
	rcu_पढ़ो_unlock();
	अगर (uncork) अणु
		mutex_lock(&connection->data.mutex);
		अगर (connection->data.socket)
			tcp_sock_set_cork(connection->data.socket->sk, false);
		mutex_unlock(&connection->data.mutex);
	पूर्ण

	क्रम (;;) अणु
		पूर्णांक send_barrier;
		prepare_to_रुको(&connection->sender_work.q_रुको, &रुको, TASK_INTERRUPTIBLE);
		spin_lock_irq(&connection->resource->req_lock);
		spin_lock(&connection->sender_work.q_lock);	/* FIXME get rid of this one? */
		अगर (!list_empty(&connection->sender_work.q))
			list_splice_tail_init(&connection->sender_work.q, work_list);
		spin_unlock(&connection->sender_work.q_lock);	/* FIXME get rid of this one? */
		अगर (!list_empty(work_list) || संकेत_pending(current)) अणु
			spin_unlock_irq(&connection->resource->req_lock);
			अवरोध;
		पूर्ण

		/* We found nothing new to करो, no to-be-communicated request,
		 * no other work item.  We may still need to बंद the last
		 * epoch.  Next incoming request epoch will be connection ->
		 * current transfer log epoch number.  If that is dअगरferent
		 * from the epoch of the last request we communicated, it is
		 * safe to send the epoch separating barrier now.
		 */
		send_barrier =
			atomic_पढ़ो(&connection->current_tle_nr) !=
			connection->send.current_epoch_nr;
		spin_unlock_irq(&connection->resource->req_lock);

		अगर (send_barrier)
			maybe_send_barrier(connection,
					connection->send.current_epoch_nr + 1);

		अगर (test_bit(DEVICE_WORK_PENDING, &connection->flags))
			अवरोध;

		/* drbd_send() may have called flush_संकेतs() */
		अगर (get_t_state(&connection->worker) != RUNNING)
			अवरोध;

		schedule();
		/* may be woken up क्रम other things but new work, too,
		 * e.g. अगर the current epoch got बंदd.
		 * In which हाल we send the barrier above. */
	पूर्ण
	finish_रुको(&connection->sender_work.q_रुको, &रुको);

	/* someone may have changed the config जबतक we have been रुकोing above. */
	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	cork = nc ? nc->tcp_cork : 0;
	rcu_पढ़ो_unlock();
	mutex_lock(&connection->data.mutex);
	अगर (connection->data.socket) अणु
		अगर (cork)
			tcp_sock_set_cork(connection->data.socket->sk, true);
		अन्यथा अगर (!uncork)
			tcp_sock_set_cork(connection->data.socket->sk, false);
	पूर्ण
	mutex_unlock(&connection->data.mutex);
पूर्ण

पूर्णांक drbd_worker(काष्ठा drbd_thपढ़ो *thi)
अणु
	काष्ठा drbd_connection *connection = thi->connection;
	काष्ठा drbd_work *w = शून्य;
	काष्ठा drbd_peer_device *peer_device;
	LIST_HEAD(work_list);
	पूर्णांक vnr;

	जबतक (get_t_state(thi) == RUNNING) अणु
		drbd_thपढ़ो_current_set_cpu(thi);

		अगर (list_empty(&work_list)) अणु
			update_worker_timing_details(connection, रुको_क्रम_work);
			रुको_क्रम_work(connection, &work_list);
		पूर्ण

		अगर (test_and_clear_bit(DEVICE_WORK_PENDING, &connection->flags)) अणु
			update_worker_timing_details(connection, करो_unqueued_work);
			करो_unqueued_work(connection);
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			flush_संकेतs(current);
			अगर (get_t_state(thi) == RUNNING) अणु
				drbd_warn(connection, "Worker got an unexpected signal\n");
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (get_t_state(thi) != RUNNING)
			अवरोध;

		अगर (!list_empty(&work_list)) अणु
			w = list_first_entry(&work_list, काष्ठा drbd_work, list);
			list_del_init(&w->list);
			update_worker_timing_details(connection, w->cb);
			अगर (w->cb(w, connection->cstate < C_WF_REPORT_PARAMS) == 0)
				जारी;
			अगर (connection->cstate >= C_WF_REPORT_PARAMS)
				conn_request_state(connection, NS(conn, C_NETWORK_FAILURE), CS_HARD);
		पूर्ण
	पूर्ण

	करो अणु
		अगर (test_and_clear_bit(DEVICE_WORK_PENDING, &connection->flags)) अणु
			update_worker_timing_details(connection, करो_unqueued_work);
			करो_unqueued_work(connection);
		पूर्ण
		अगर (!list_empty(&work_list)) अणु
			w = list_first_entry(&work_list, काष्ठा drbd_work, list);
			list_del_init(&w->list);
			update_worker_timing_details(connection, w->cb);
			w->cb(w, 1);
		पूर्ण अन्यथा
			dequeue_work_batch(&connection->sender_work, &work_list);
	पूर्ण जबतक (!list_empty(&work_list) || test_bit(DEVICE_WORK_PENDING, &connection->flags));

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		D_ASSERT(device, device->state.disk == D_DISKLESS && device->state.conn == C_STANDALONE);
		kref_get(&device->kref);
		rcu_पढ़ो_unlock();
		drbd_device_cleanup(device);
		kref_put(&device->kref, drbd_destroy_device);
		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण
