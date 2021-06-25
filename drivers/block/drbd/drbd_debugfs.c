<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) "drbd debugfs: " fmt
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/list.h>

#समावेश "drbd_int.h"
#समावेश "drbd_req.h"
#समावेश "drbd_debugfs.h"


/**********************************************************************
 * Whenever you change the file क्रमmat, remember to bump the version. *
 **********************************************************************/

अटल काष्ठा dentry *drbd_debugfs_root;
अटल काष्ठा dentry *drbd_debugfs_version;
अटल काष्ठा dentry *drbd_debugfs_resources;
अटल काष्ठा dentry *drbd_debugfs_minors;

अटल व्योम seq_prपूर्णांक_age_or_dash(काष्ठा seq_file *m, bool valid, अचिन्हित दीर्घ dt)
अणु
	अगर (valid)
		seq_म_लिखो(m, "\t%d", jअगरfies_to_msecs(dt));
	अन्यथा
		seq_म_लिखो(m, "\t-");
पूर्ण

अटल व्योम __seq_prपूर्णांक_rq_state_bit(काष्ठा seq_file *m,
	bool is_set, अक्षर *sep, स्थिर अक्षर *set_name, स्थिर अक्षर *unset_name)
अणु
	अगर (is_set && set_name) अणु
		seq_अ_दो(m, *sep);
		seq_माला_दो(m, set_name);
		*sep = '|';
	पूर्ण अन्यथा अगर (!is_set && unset_name) अणु
		seq_अ_दो(m, *sep);
		seq_माला_दो(m, unset_name);
		*sep = '|';
	पूर्ण
पूर्ण

अटल व्योम seq_prपूर्णांक_rq_state_bit(काष्ठा seq_file *m,
	bool is_set, अक्षर *sep, स्थिर अक्षर *set_name)
अणु
	__seq_prपूर्णांक_rq_state_bit(m, is_set, sep, set_name, शून्य);
पूर्ण

/* pretty prपूर्णांक क्रमागत drbd_req_state_bits req->rq_state */
अटल व्योम seq_prपूर्णांक_request_state(काष्ठा seq_file *m, काष्ठा drbd_request *req)
अणु
	अचिन्हित पूर्णांक s = req->rq_state;
	अक्षर sep = ' ';
	seq_म_लिखो(m, "\t0x%08x", s);
	seq_म_लिखो(m, "\tmaster: %s", req->master_bio ? "pending" : "completed");

	/* RQ_WRITE ignored, alपढ़ोy reported */
	seq_माला_दो(m, "\tlocal:");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_IN_ACT_LOG, &sep, "in-AL");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_POSTPONED, &sep, "postponed");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_COMPLETION_SUSP, &sep, "suspended");
	sep = ' ';
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_LOCAL_PENDING, &sep, "pending");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_LOCAL_COMPLETED, &sep, "completed");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_LOCAL_ABORTED, &sep, "aborted");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_LOCAL_OK, &sep, "ok");
	अगर (sep == ' ')
		seq_माला_दो(m, " -");

	/* क्रम_each_connection ... */
	seq_म_लिखो(m, "\tnet:");
	sep = ' ';
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_NET_PENDING, &sep, "pending");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_NET_QUEUED, &sep, "queued");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_NET_SENT, &sep, "sent");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_NET_DONE, &sep, "done");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_NET_SIS, &sep, "sis");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_NET_OK, &sep, "ok");
	अगर (sep == ' ')
		seq_माला_दो(m, " -");

	seq_म_लिखो(m, " :");
	sep = ' ';
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_EXP_RECEIVE_ACK, &sep, "B");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_EXP_WRITE_ACK, &sep, "C");
	seq_prपूर्णांक_rq_state_bit(m, s & RQ_EXP_BARR_ACK, &sep, "barr");
	अगर (sep == ' ')
		seq_माला_दो(m, " -");
	seq_म_लिखो(m, "\n");
पूर्ण

अटल व्योम seq_prपूर्णांक_one_request(काष्ठा seq_file *m, काष्ठा drbd_request *req, अचिन्हित दीर्घ now)
अणु
	/* change anything here, fixup header below! */
	अचिन्हित पूर्णांक s = req->rq_state;

#घोषणा RQ_HDR_1 "epoch\tsector\tsize\trw"
	seq_म_लिखो(m, "0x%x\t%llu\t%u\t%s",
		req->epoch,
		(अचिन्हित दीर्घ दीर्घ)req->i.sector, req->i.size >> 9,
		(s & RQ_WRITE) ? "W" : "R");

#घोषणा RQ_HDR_2 "\tstart\tin AL\tsubmit"
	seq_म_लिखो(m, "\t%d", jअगरfies_to_msecs(now - req->start_jअगर));
	seq_prपूर्णांक_age_or_dash(m, s & RQ_IN_ACT_LOG, now - req->in_actlog_jअगर);
	seq_prपूर्णांक_age_or_dash(m, s & RQ_LOCAL_PENDING, now - req->pre_submit_jअगर);

#घोषणा RQ_HDR_3 "\tsent\tacked\tdone"
	seq_prपूर्णांक_age_or_dash(m, s & RQ_NET_SENT, now - req->pre_send_jअगर);
	seq_prपूर्णांक_age_or_dash(m, (s & RQ_NET_SENT) && !(s & RQ_NET_PENDING), now - req->acked_jअगर);
	seq_prपूर्णांक_age_or_dash(m, s & RQ_NET_DONE, now - req->net_करोne_jअगर);

#घोषणा RQ_HDR_4 "\tstate\n"
	seq_prपूर्णांक_request_state(m, req);
पूर्ण
#घोषणा RQ_HDR RQ_HDR_1 RQ_HDR_2 RQ_HDR_3 RQ_HDR_4

अटल व्योम seq_prपूर्णांक_minor_vnr_req(काष्ठा seq_file *m, काष्ठा drbd_request *req, अचिन्हित दीर्घ now)
अणु
	seq_म_लिखो(m, "%u\t%u\t", req->device->minor, req->device->vnr);
	seq_prपूर्णांक_one_request(m, req, now);
पूर्ण

अटल व्योम seq_prपूर्णांक_resource_pending_meta_io(काष्ठा seq_file *m, काष्ठा drbd_resource *resource, अचिन्हित दीर्घ now)
अणु
	काष्ठा drbd_device *device;
	अचिन्हित पूर्णांक i;

	seq_माला_दो(m, "minor\tvnr\tstart\tsubmit\tintent\n");
	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&resource->devices, device, i) अणु
		काष्ठा drbd_md_io पंचांगp;
		/* In theory this is racy,
		 * in the sense that there could have been a
		 * drbd_md_put_buffer(); drbd_md_get_buffer();
		 * between accessing these members here.  */
		पंचांगp = device->md_io;
		अगर (atomic_पढ़ो(&पंचांगp.in_use)) अणु
			seq_म_लिखो(m, "%u\t%u\t%d\t",
				device->minor, device->vnr,
				jअगरfies_to_msecs(now - पंचांगp.start_jअगर));
			अगर (समय_beक्रमe(पंचांगp.submit_jअगर, पंचांगp.start_jअगर))
				seq_माला_दो(m, "-\t");
			अन्यथा
				seq_म_लिखो(m, "%d\t", jअगरfies_to_msecs(now - पंचांगp.submit_jअगर));
			seq_म_लिखो(m, "%s\n", पंचांगp.current_use);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम seq_prपूर्णांक_रुकोing_क्रम_AL(काष्ठा seq_file *m, काष्ठा drbd_resource *resource, अचिन्हित दीर्घ now)
अणु
	काष्ठा drbd_device *device;
	अचिन्हित पूर्णांक i;

	seq_माला_दो(m, "minor\tvnr\tage\t#waiting\n");
	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&resource->devices, device, i) अणु
		अचिन्हित दीर्घ jअगर;
		काष्ठा drbd_request *req;
		पूर्णांक n = atomic_पढ़ो(&device->ap_actlog_cnt);
		अगर (n) अणु
			spin_lock_irq(&device->resource->req_lock);
			req = list_first_entry_or_null(&device->pending_master_completion[1],
				काष्ठा drbd_request, req_pending_master_completion);
			/* अगर the oldest request करोes not रुको क्रम the activity log
			 * it is not पूर्णांकeresting क्रम us here */
			अगर (req && !(req->rq_state & RQ_IN_ACT_LOG))
				jअगर = req->start_jअगर;
			अन्यथा
				req = शून्य;
			spin_unlock_irq(&device->resource->req_lock);
		पूर्ण
		अगर (n) अणु
			seq_म_लिखो(m, "%u\t%u\t", device->minor, device->vnr);
			अगर (req)
				seq_म_लिखो(m, "%u\t", jअगरfies_to_msecs(now - jअगर));
			अन्यथा
				seq_माला_दो(m, "-\t");
			seq_म_लिखो(m, "%u\n", n);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम seq_prपूर्णांक_device_biपंचांगap_io(काष्ठा seq_file *m, काष्ठा drbd_device *device, अचिन्हित दीर्घ now)
अणु
	काष्ठा drbd_bm_aio_ctx *ctx;
	अचिन्हित दीर्घ start_jअगर;
	अचिन्हित पूर्णांक in_flight;
	अचिन्हित पूर्णांक flags;
	spin_lock_irq(&device->resource->req_lock);
	ctx = list_first_entry_or_null(&device->pending_biपंचांगap_io, काष्ठा drbd_bm_aio_ctx, list);
	अगर (ctx && ctx->करोne)
		ctx = शून्य;
	अगर (ctx) अणु
		start_jअगर = ctx->start_jअगर;
		in_flight = atomic_पढ़ो(&ctx->in_flight);
		flags = ctx->flags;
	पूर्ण
	spin_unlock_irq(&device->resource->req_lock);
	अगर (ctx) अणु
		seq_म_लिखो(m, "%u\t%u\t%c\t%u\t%u\n",
			device->minor, device->vnr,
			(flags & BM_AIO_READ) ? 'R' : 'W',
			jअगरfies_to_msecs(now - start_jअगर),
			in_flight);
	पूर्ण
पूर्ण

अटल व्योम seq_prपूर्णांक_resource_pending_biपंचांगap_io(काष्ठा seq_file *m, काष्ठा drbd_resource *resource, अचिन्हित दीर्घ now)
अणु
	काष्ठा drbd_device *device;
	अचिन्हित पूर्णांक i;

	seq_माला_दो(m, "minor\tvnr\trw\tage\t#in-flight\n");
	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&resource->devices, device, i) अणु
		seq_prपूर्णांक_device_biपंचांगap_io(m, device, now);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* pretty prपूर्णांक क्रमागत peer_req->flags */
अटल व्योम seq_prपूर्णांक_peer_request_flags(काष्ठा seq_file *m, काष्ठा drbd_peer_request *peer_req)
अणु
	अचिन्हित दीर्घ f = peer_req->flags;
	अक्षर sep = ' ';

	__seq_prपूर्णांक_rq_state_bit(m, f & EE_SUBMITTED, &sep, "submitted", "preparing");
	__seq_prपूर्णांक_rq_state_bit(m, f & EE_APPLICATION, &sep, "application", "internal");
	seq_prपूर्णांक_rq_state_bit(m, f & EE_CALL_AL_COMPLETE_IO, &sep, "in-AL");
	seq_prपूर्णांक_rq_state_bit(m, f & EE_SEND_WRITE_ACK, &sep, "C");
	seq_prपूर्णांक_rq_state_bit(m, f & EE_MAY_SET_IN_SYNC, &sep, "set-in-sync");
	seq_prपूर्णांक_rq_state_bit(m, f & EE_TRIM, &sep, "trim");
	seq_prपूर्णांक_rq_state_bit(m, f & EE_ZEROOUT, &sep, "zero-out");
	seq_prपूर्णांक_rq_state_bit(m, f & EE_WRITE_SAME, &sep, "write-same");
	seq_अ_दो(m, '\n');
पूर्ण

अटल व्योम seq_prपूर्णांक_peer_request(काष्ठा seq_file *m,
	काष्ठा drbd_device *device, काष्ठा list_head *lh,
	अचिन्हित दीर्घ now)
अणु
	bool reported_preparing = false;
	काष्ठा drbd_peer_request *peer_req;
	list_क्रम_each_entry(peer_req, lh, w.list) अणु
		अगर (reported_preparing && !(peer_req->flags & EE_SUBMITTED))
			जारी;

		अगर (device)
			seq_म_लिखो(m, "%u\t%u\t", device->minor, device->vnr);

		seq_म_लिखो(m, "%llu\t%u\t%c\t%u\t",
			(अचिन्हित दीर्घ दीर्घ)peer_req->i.sector, peer_req->i.size >> 9,
			(peer_req->flags & EE_WRITE) ? 'W' : 'R',
			jअगरfies_to_msecs(now - peer_req->submit_jअगर));
		seq_prपूर्णांक_peer_request_flags(m, peer_req);
		अगर (peer_req->flags & EE_SUBMITTED)
			अवरोध;
		अन्यथा
			reported_preparing = true;
	पूर्ण
पूर्ण

अटल व्योम seq_prपूर्णांक_device_peer_requests(काष्ठा seq_file *m,
	काष्ठा drbd_device *device, अचिन्हित दीर्घ now)
अणु
	seq_माला_दो(m, "minor\tvnr\tsector\tsize\trw\tage\tflags\n");
	spin_lock_irq(&device->resource->req_lock);
	seq_prपूर्णांक_peer_request(m, device, &device->active_ee, now);
	seq_prपूर्णांक_peer_request(m, device, &device->पढ़ो_ee, now);
	seq_prपूर्णांक_peer_request(m, device, &device->sync_ee, now);
	spin_unlock_irq(&device->resource->req_lock);
	अगर (test_bit(FLUSH_PENDING, &device->flags)) अणु
		seq_म_लिखो(m, "%u\t%u\t-\t-\tF\t%u\tflush\n",
			device->minor, device->vnr,
			jअगरfies_to_msecs(now - device->flush_jअगर));
	पूर्ण
पूर्ण

अटल व्योम seq_prपूर्णांक_resource_pending_peer_requests(काष्ठा seq_file *m,
	काष्ठा drbd_resource *resource, अचिन्हित दीर्घ now)
अणु
	काष्ठा drbd_device *device;
	अचिन्हित पूर्णांक i;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&resource->devices, device, i) अणु
		seq_prपूर्णांक_device_peer_requests(m, device, now);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम seq_prपूर्णांक_resource_transfer_log_summary(काष्ठा seq_file *m,
	काष्ठा drbd_resource *resource,
	काष्ठा drbd_connection *connection,
	अचिन्हित दीर्घ now)
अणु
	काष्ठा drbd_request *req;
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक show_state = 0;

	seq_माला_दो(m, "n\tdevice\tvnr\t" RQ_HDR);
	spin_lock_irq(&resource->req_lock);
	list_क्रम_each_entry(req, &connection->transfer_log, tl_requests) अणु
		अचिन्हित पूर्णांक पंचांगp = 0;
		अचिन्हित पूर्णांक s;
		++count;

		/* करोn't disable irq "forever" */
		अगर (!(count & 0x1ff)) अणु
			काष्ठा drbd_request *req_next;
			kref_get(&req->kref);
			spin_unlock_irq(&resource->req_lock);
			cond_resched();
			spin_lock_irq(&resource->req_lock);
			req_next = list_next_entry(req, tl_requests);
			अगर (kref_put(&req->kref, drbd_req_destroy))
				req = req_next;
			अगर (&req->tl_requests == &connection->transfer_log)
				अवरोध;
		पूर्ण

		s = req->rq_state;

		/* This is meant to summarize timing issues, to be able to tell
		 * local disk problems from network problems.
		 * Skip requests, अगर we have shown an even older request with
		 * similar aspects alपढ़ोy.  */
		अगर (req->master_bio == शून्य)
			पंचांगp |= 1;
		अगर ((s & RQ_LOCAL_MASK) && (s & RQ_LOCAL_PENDING))
			पंचांगp |= 2;
		अगर (s & RQ_NET_MASK) अणु
			अगर (!(s & RQ_NET_SENT))
				पंचांगp |= 4;
			अगर (s & RQ_NET_PENDING)
				पंचांगp |= 8;
			अगर (!(s & RQ_NET_DONE))
				पंचांगp |= 16;
		पूर्ण
		अगर ((पंचांगp & show_state) == पंचांगp)
			जारी;
		show_state |= पंचांगp;
		seq_म_लिखो(m, "%u\t", count);
		seq_prपूर्णांक_minor_vnr_req(m, req, now);
		अगर (show_state == 0x1f)
			अवरोध;
	पूर्ण
	spin_unlock_irq(&resource->req_lock);
पूर्ण

/* TODO: transfer_log and मित्रs should be moved to resource */
अटल पूर्णांक in_flight_summary_show(काष्ठा seq_file *m, व्योम *pos)
अणु
	काष्ठा drbd_resource *resource = m->निजी;
	काष्ठा drbd_connection *connection;
	अचिन्हित दीर्घ jअगर = jअगरfies;

	connection = first_connection(resource);
	/* This करोes not happen, actually.
	 * But be robust and prepare क्रम future code changes. */
	अगर (!connection || !kref_get_unless_zero(&connection->kref))
		वापस -ESTALE;

	/* BUMP me अगर you change the file क्रमmat/content/presentation */
	seq_म_लिखो(m, "v: %u\n\n", 0);

	seq_माला_दो(m, "oldest bitmap IO\n");
	seq_prपूर्णांक_resource_pending_biपंचांगap_io(m, resource, jअगर);
	seq_अ_दो(m, '\n');

	seq_माला_दो(m, "meta data IO\n");
	seq_prपूर्णांक_resource_pending_meta_io(m, resource, jअगर);
	seq_अ_दो(m, '\n');

	seq_माला_दो(m, "socket buffer stats\n");
	/* क्रम each connection ... once we have more than one */
	rcu_पढ़ो_lock();
	अगर (connection->data.socket) अणु
		/* खोलो coded SIOCINQ, the "relevant" part */
		काष्ठा tcp_sock *tp = tcp_sk(connection->data.socket->sk);
		पूर्णांक answ = tp->rcv_nxt - tp->copied_seq;
		seq_म_लिखो(m, "unread receive buffer: %u Byte\n", answ);
		/* खोलो coded SIOCOUTQ, the "relevant" part */
		answ = tp->ग_लिखो_seq - tp->snd_una;
		seq_म_लिखो(m, "unacked send buffer: %u Byte\n", answ);
	पूर्ण
	rcu_पढ़ो_unlock();
	seq_अ_दो(m, '\n');

	seq_माला_दो(m, "oldest peer requests\n");
	seq_prपूर्णांक_resource_pending_peer_requests(m, resource, jअगर);
	seq_अ_दो(m, '\n');

	seq_माला_दो(m, "application requests waiting for activity log\n");
	seq_prपूर्णांक_रुकोing_क्रम_AL(m, resource, jअगर);
	seq_अ_दो(m, '\n');

	seq_माला_दो(m, "oldest application requests\n");
	seq_prपूर्णांक_resource_transfer_log_summary(m, resource, connection, jअगर);
	seq_अ_दो(m, '\n');

	jअगर = jअगरfies - jअगर;
	अगर (jअगर)
		seq_म_लिखो(m, "generated in %d ms\n", jअगरfies_to_msecs(jअगर));
	kref_put(&connection->kref, drbd_destroy_connection);
	वापस 0;
पूर्ण

/* make sure at *खोलो* समय that the respective object won't go away. */
अटल पूर्णांक drbd_single_खोलो(काष्ठा file *file, पूर्णांक (*show)(काष्ठा seq_file *, व्योम *),
		                व्योम *data, काष्ठा kref *kref,
				व्योम (*release)(काष्ठा kref *))
अणु
	काष्ठा dentry *parent;
	पूर्णांक ret = -ESTALE;

	/* Are we still linked,
	 * or has debugfs_हटाओ() alपढ़ोy been called? */
	parent = file->f_path.dentry->d_parent;
	/* serialize with d_delete() */
	inode_lock(d_inode(parent));
	/* Make sure the object is still alive */
	अगर (simple_positive(file->f_path.dentry)
	&& kref_get_unless_zero(kref))
		ret = 0;
	inode_unlock(d_inode(parent));
	अगर (!ret) अणु
		ret = single_खोलो(file, show, data);
		अगर (ret)
			kref_put(kref, release);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक in_flight_summary_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drbd_resource *resource = inode->i_निजी;
	वापस drbd_single_खोलो(file, in_flight_summary_show, resource,
				&resource->kref, drbd_destroy_resource);
पूर्ण

अटल पूर्णांक in_flight_summary_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drbd_resource *resource = inode->i_निजी;
	kref_put(&resource->kref, drbd_destroy_resource);
	वापस single_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations in_flight_summary_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= in_flight_summary_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= in_flight_summary_release,
पूर्ण;

व्योम drbd_debugfs_resource_add(काष्ठा drbd_resource *resource)
अणु
	काष्ठा dentry *dentry;

	dentry = debugfs_create_dir(resource->name, drbd_debugfs_resources);
	resource->debugfs_res = dentry;

	dentry = debugfs_create_dir("volumes", resource->debugfs_res);
	resource->debugfs_res_volumes = dentry;

	dentry = debugfs_create_dir("connections", resource->debugfs_res);
	resource->debugfs_res_connections = dentry;

	dentry = debugfs_create_file("in_flight_summary", 0440,
				     resource->debugfs_res, resource,
				     &in_flight_summary_fops);
	resource->debugfs_res_in_flight_summary = dentry;
पूर्ण

अटल व्योम drbd_debugfs_हटाओ(काष्ठा dentry **dp)
अणु
	debugfs_हटाओ(*dp);
	*dp = शून्य;
पूर्ण

व्योम drbd_debugfs_resource_cleanup(काष्ठा drbd_resource *resource)
अणु
	/* it is ok to call debugfs_हटाओ(शून्य) */
	drbd_debugfs_हटाओ(&resource->debugfs_res_in_flight_summary);
	drbd_debugfs_हटाओ(&resource->debugfs_res_connections);
	drbd_debugfs_हटाओ(&resource->debugfs_res_volumes);
	drbd_debugfs_हटाओ(&resource->debugfs_res);
पूर्ण

अटल व्योम seq_prपूर्णांक_one_timing_detail(काष्ठा seq_file *m,
	स्थिर काष्ठा drbd_thपढ़ो_timing_details *tdp,
	अचिन्हित दीर्घ now)
अणु
	काष्ठा drbd_thपढ़ो_timing_details td;
	/* No locking...
	 * use temporary assignment to get at consistent data. */
	करो अणु
		td = *tdp;
	पूर्ण जबतक (td.cb_nr != tdp->cb_nr);
	अगर (!td.cb_addr)
		वापस;
	seq_म_लिखो(m, "%u\t%d\t%s:%u\t%ps\n",
			td.cb_nr,
			jअगरfies_to_msecs(now - td.start_jअगर),
			td.caller_fn, td.line,
			td.cb_addr);
पूर्ण

अटल व्योम seq_prपूर्णांक_timing_details(काष्ठा seq_file *m,
		स्थिर अक्षर *title,
		अचिन्हित पूर्णांक cb_nr, काष्ठा drbd_thपढ़ो_timing_details *tdp, अचिन्हित दीर्घ now)
अणु
	अचिन्हित पूर्णांक start_idx;
	अचिन्हित पूर्णांक i;

	seq_म_लिखो(m, "%s\n", title);
	/* If not much is going on, this will result in natural ordering.
	 * If it is very busy, we will possibly skip events, or even see wrap
	 * arounds, which could only be aव्योमed with locking.
	 */
	start_idx = cb_nr % DRBD_THREAD_DETAILS_HIST;
	क्रम (i = start_idx; i < DRBD_THREAD_DETAILS_HIST; i++)
		seq_prपूर्णांक_one_timing_detail(m, tdp+i, now);
	क्रम (i = 0; i < start_idx; i++)
		seq_prपूर्णांक_one_timing_detail(m, tdp+i, now);
पूर्ण

अटल पूर्णांक callback_history_show(काष्ठा seq_file *m, व्योम *ignored)
अणु
	काष्ठा drbd_connection *connection = m->निजी;
	अचिन्हित दीर्घ jअगर = jअगरfies;

	/* BUMP me अगर you change the file क्रमmat/content/presentation */
	seq_म_लिखो(m, "v: %u\n\n", 0);

	seq_माला_दो(m, "n\tage\tcallsite\tfn\n");
	seq_prपूर्णांक_timing_details(m, "worker", connection->w_cb_nr, connection->w_timing_details, jअगर);
	seq_prपूर्णांक_timing_details(m, "receiver", connection->r_cb_nr, connection->r_timing_details, jअगर);
	वापस 0;
पूर्ण

अटल पूर्णांक callback_history_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drbd_connection *connection = inode->i_निजी;
	वापस drbd_single_खोलो(file, callback_history_show, connection,
				&connection->kref, drbd_destroy_connection);
पूर्ण

अटल पूर्णांक callback_history_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drbd_connection *connection = inode->i_निजी;
	kref_put(&connection->kref, drbd_destroy_connection);
	वापस single_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations connection_callback_history_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= callback_history_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= callback_history_release,
पूर्ण;

अटल पूर्णांक connection_oldest_requests_show(काष्ठा seq_file *m, व्योम *ignored)
अणु
	काष्ठा drbd_connection *connection = m->निजी;
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा drbd_request *r1, *r2;

	/* BUMP me अगर you change the file क्रमmat/content/presentation */
	seq_म_लिखो(m, "v: %u\n\n", 0);

	spin_lock_irq(&connection->resource->req_lock);
	r1 = connection->req_next;
	अगर (r1)
		seq_prपूर्णांक_minor_vnr_req(m, r1, now);
	r2 = connection->req_ack_pending;
	अगर (r2 && r2 != r1) अणु
		r1 = r2;
		seq_prपूर्णांक_minor_vnr_req(m, r1, now);
	पूर्ण
	r2 = connection->req_not_net_करोne;
	अगर (r2 && r2 != r1)
		seq_prपूर्णांक_minor_vnr_req(m, r2, now);
	spin_unlock_irq(&connection->resource->req_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक connection_oldest_requests_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drbd_connection *connection = inode->i_निजी;
	वापस drbd_single_खोलो(file, connection_oldest_requests_show, connection,
				&connection->kref, drbd_destroy_connection);
पूर्ण

अटल पूर्णांक connection_oldest_requests_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drbd_connection *connection = inode->i_निजी;
	kref_put(&connection->kref, drbd_destroy_connection);
	वापस single_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations connection_oldest_requests_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= connection_oldest_requests_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= connection_oldest_requests_release,
पूर्ण;

व्योम drbd_debugfs_connection_add(काष्ठा drbd_connection *connection)
अणु
	काष्ठा dentry *conns_dir = connection->resource->debugfs_res_connections;
	काष्ठा dentry *dentry;

	/* Once we enable mutliple peers,
	 * these connections will have descriptive names.
	 * For now, it is just the one connection to the (only) "peer". */
	dentry = debugfs_create_dir("peer", conns_dir);
	connection->debugfs_conn = dentry;

	dentry = debugfs_create_file("callback_history", 0440,
				     connection->debugfs_conn, connection,
				     &connection_callback_history_fops);
	connection->debugfs_conn_callback_history = dentry;

	dentry = debugfs_create_file("oldest_requests", 0440,
				     connection->debugfs_conn, connection,
				     &connection_oldest_requests_fops);
	connection->debugfs_conn_oldest_requests = dentry;
पूर्ण

व्योम drbd_debugfs_connection_cleanup(काष्ठा drbd_connection *connection)
अणु
	drbd_debugfs_हटाओ(&connection->debugfs_conn_callback_history);
	drbd_debugfs_हटाओ(&connection->debugfs_conn_oldest_requests);
	drbd_debugfs_हटाओ(&connection->debugfs_conn);
पूर्ण

अटल व्योम resync_dump_detail(काष्ठा seq_file *m, काष्ठा lc_element *e)
अणु
       काष्ठा bm_extent *bme = lc_entry(e, काष्ठा bm_extent, lce);

       seq_म_लिखो(m, "%5d %s %s %s", bme->rs_left,
		  test_bit(BME_NO_WRITES, &bme->flags) ? "NO_WRITES" : "---------",
		  test_bit(BME_LOCKED, &bme->flags) ? "LOCKED" : "------",
		  test_bit(BME_PRIORITY, &bme->flags) ? "PRIORITY" : "--------"
		  );
पूर्ण

अटल पूर्णांक device_resync_extents_show(काष्ठा seq_file *m, व्योम *ignored)
अणु
	काष्ठा drbd_device *device = m->निजी;

	/* BUMP me अगर you change the file क्रमmat/content/presentation */
	seq_म_लिखो(m, "v: %u\n\n", 0);

	अगर (get_ldev_अगर_state(device, D_FAILED)) अणु
		lc_seq_म_लिखो_stats(m, device->resync);
		lc_seq_dump_details(m, device->resync, "rs_left flags", resync_dump_detail);
		put_ldev(device);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक device_act_log_extents_show(काष्ठा seq_file *m, व्योम *ignored)
अणु
	काष्ठा drbd_device *device = m->निजी;

	/* BUMP me अगर you change the file क्रमmat/content/presentation */
	seq_म_लिखो(m, "v: %u\n\n", 0);

	अगर (get_ldev_अगर_state(device, D_FAILED)) अणु
		lc_seq_म_लिखो_stats(m, device->act_log);
		lc_seq_dump_details(m, device->act_log, "", शून्य);
		put_ldev(device);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक device_oldest_requests_show(काष्ठा seq_file *m, व्योम *ignored)
अणु
	काष्ठा drbd_device *device = m->निजी;
	काष्ठा drbd_resource *resource = device->resource;
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा drbd_request *r1, *r2;
	पूर्णांक i;

	/* BUMP me अगर you change the file क्रमmat/content/presentation */
	seq_म_लिखो(m, "v: %u\n\n", 0);

	seq_माला_दो(m, RQ_HDR);
	spin_lock_irq(&resource->req_lock);
	/* WRITE, then READ */
	क्रम (i = 1; i >= 0; --i) अणु
		r1 = list_first_entry_or_null(&device->pending_master_completion[i],
			काष्ठा drbd_request, req_pending_master_completion);
		r2 = list_first_entry_or_null(&device->pending_completion[i],
			काष्ठा drbd_request, req_pending_local);
		अगर (r1)
			seq_prपूर्णांक_one_request(m, r1, now);
		अगर (r2 && r2 != r1)
			seq_prपूर्णांक_one_request(m, r2, now);
	पूर्ण
	spin_unlock_irq(&resource->req_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक device_data_gen_id_show(काष्ठा seq_file *m, व्योम *ignored)
अणु
	काष्ठा drbd_device *device = m->निजी;
	काष्ठा drbd_md *md;
	क्रमागत drbd_uuid_index idx;

	अगर (!get_ldev_अगर_state(device, D_FAILED))
		वापस -ENODEV;

	md = &device->ldev->md;
	spin_lock_irq(&md->uuid_lock);
	क्रम (idx = UI_CURRENT; idx <= UI_HISTORY_END; idx++) अणु
		seq_म_लिखो(m, "0x%016llX\n", md->uuid[idx]);
	पूर्ण
	spin_unlock_irq(&md->uuid_lock);
	put_ldev(device);
	वापस 0;
पूर्ण

अटल पूर्णांक device_ed_gen_id_show(काष्ठा seq_file *m, व्योम *ignored)
अणु
	काष्ठा drbd_device *device = m->निजी;
	seq_म_लिखो(m, "0x%016llX\n", (अचिन्हित दीर्घ दीर्घ)device->ed_uuid);
	वापस 0;
पूर्ण

#घोषणा drbd_debugfs_device_attr(name)						\
अटल पूर्णांक device_ ## name ## _खोलो(काष्ठा inode *inode, काष्ठा file *file)	\
अणु										\
	काष्ठा drbd_device *device = inode->i_निजी;				\
	वापस drbd_single_खोलो(file, device_ ## name ## _show, device,		\
				&device->kref, drbd_destroy_device);		\
पूर्ण										\
अटल पूर्णांक device_ ## name ## _release(काष्ठा inode *inode, काष्ठा file *file)	\
अणु										\
	काष्ठा drbd_device *device = inode->i_निजी;				\
	kref_put(&device->kref, drbd_destroy_device);				\
	वापस single_release(inode, file);					\
पूर्ण										\
अटल स्थिर काष्ठा file_operations device_ ## name ## _fops = अणु		\
	.owner		= THIS_MODULE,						\
	.खोलो		= device_ ## name ## _खोलो,				\
	.पढ़ो		= seq_पढ़ो,						\
	.llseek		= seq_lseek,						\
	.release	= device_ ## name ## _release,				\
पूर्ण;

drbd_debugfs_device_attr(oldest_requests)
drbd_debugfs_device_attr(act_log_extents)
drbd_debugfs_device_attr(resync_extents)
drbd_debugfs_device_attr(data_gen_id)
drbd_debugfs_device_attr(ed_gen_id)

व्योम drbd_debugfs_device_add(काष्ठा drbd_device *device)
अणु
	काष्ठा dentry *vols_dir = device->resource->debugfs_res_volumes;
	अक्षर minor_buf[8]; /* MINORMASK, MINORBITS == 20; */
	अक्षर vnr_buf[8];   /* volume number vnr is even 16 bit only; */
	अक्षर *slink_name = शून्य;

	काष्ठा dentry *dentry;
	अगर (!vols_dir || !drbd_debugfs_minors)
		वापस;

	snम_लिखो(vnr_buf, माप(vnr_buf), "%u", device->vnr);
	dentry = debugfs_create_dir(vnr_buf, vols_dir);
	device->debugfs_vol = dentry;

	snम_लिखो(minor_buf, माप(minor_buf), "%u", device->minor);
	slink_name = kaप्र_लिखो(GFP_KERNEL, "../resources/%s/volumes/%u",
			device->resource->name, device->vnr);
	अगर (!slink_name)
		जाओ fail;
	dentry = debugfs_create_symlink(minor_buf, drbd_debugfs_minors, slink_name);
	device->debugfs_minor = dentry;
	kमुक्त(slink_name);
	slink_name = शून्य;

#घोषणा DCF(name)	करो अणु					\
	dentry = debugfs_create_file(#name, 0440,	\
			device->debugfs_vol, device,		\
			&device_ ## name ## _fops);		\
	device->debugfs_vol_ ## name = dentry;			\
	पूर्ण जबतक (0)

	DCF(oldest_requests);
	DCF(act_log_extents);
	DCF(resync_extents);
	DCF(data_gen_id);
	DCF(ed_gen_id);
#अघोषित DCF
	वापस;

fail:
	drbd_debugfs_device_cleanup(device);
	drbd_err(device, "failed to create debugfs entries\n");
पूर्ण

व्योम drbd_debugfs_device_cleanup(काष्ठा drbd_device *device)
अणु
	drbd_debugfs_हटाओ(&device->debugfs_minor);
	drbd_debugfs_हटाओ(&device->debugfs_vol_oldest_requests);
	drbd_debugfs_हटाओ(&device->debugfs_vol_act_log_extents);
	drbd_debugfs_हटाओ(&device->debugfs_vol_resync_extents);
	drbd_debugfs_हटाओ(&device->debugfs_vol_data_gen_id);
	drbd_debugfs_हटाओ(&device->debugfs_vol_ed_gen_id);
	drbd_debugfs_हटाओ(&device->debugfs_vol);
पूर्ण

व्योम drbd_debugfs_peer_device_add(काष्ठा drbd_peer_device *peer_device)
अणु
	काष्ठा dentry *conn_dir = peer_device->connection->debugfs_conn;
	काष्ठा dentry *dentry;
	अक्षर vnr_buf[8];

	snम_लिखो(vnr_buf, माप(vnr_buf), "%u", peer_device->device->vnr);
	dentry = debugfs_create_dir(vnr_buf, conn_dir);
	peer_device->debugfs_peer_dev = dentry;
पूर्ण

व्योम drbd_debugfs_peer_device_cleanup(काष्ठा drbd_peer_device *peer_device)
अणु
	drbd_debugfs_हटाओ(&peer_device->debugfs_peer_dev);
पूर्ण

अटल पूर्णांक drbd_version_show(काष्ठा seq_file *m, व्योम *ignored)
अणु
	seq_म_लिखो(m, "# %s\n", drbd_buildtag());
	seq_म_लिखो(m, "VERSION=%s\n", REL_VERSION);
	seq_म_लिखो(m, "API_VERSION=%u\n", API_VERSION);
	seq_म_लिखो(m, "PRO_VERSION_MIN=%u\n", PRO_VERSION_MIN);
	seq_म_लिखो(m, "PRO_VERSION_MAX=%u\n", PRO_VERSION_MAX);
	वापस 0;
पूर्ण

अटल पूर्णांक drbd_version_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, drbd_version_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations drbd_version_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drbd_version_खोलो,
	.llseek = seq_lseek,
	.पढ़ो = seq_पढ़ो,
	.release = single_release,
पूर्ण;

/* not __निकास, may be indirectly called
 * from the module-load-failure path as well. */
व्योम drbd_debugfs_cleanup(व्योम)
अणु
	drbd_debugfs_हटाओ(&drbd_debugfs_resources);
	drbd_debugfs_हटाओ(&drbd_debugfs_minors);
	drbd_debugfs_हटाओ(&drbd_debugfs_version);
	drbd_debugfs_हटाओ(&drbd_debugfs_root);
पूर्ण

व्योम __init drbd_debugfs_init(व्योम)
अणु
	काष्ठा dentry *dentry;

	dentry = debugfs_create_dir("drbd", शून्य);
	drbd_debugfs_root = dentry;

	dentry = debugfs_create_file("version", 0444, drbd_debugfs_root, शून्य, &drbd_version_fops);
	drbd_debugfs_version = dentry;

	dentry = debugfs_create_dir("resources", drbd_debugfs_root);
	drbd_debugfs_resources = dentry;

	dentry = debugfs_create_dir("minors", drbd_debugfs_root);
	drbd_debugfs_minors = dentry;
पूर्ण
