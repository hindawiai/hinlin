<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Network block device - make block devices work over TCP
 *
 * Note that you can not swap over this thing, yet. Seems to work but
 * deadlocks someबार - you can not swap over TCP in general.
 * 
 * Copyright 1997-2000, 2008 Pavel Machek <pavel@ucw.cz>
 * Parts copyright 2001 Steven Whitehouse <steve@chygwyn.com>
 *
 * (part of code stolen from loop.c)
 */

#समावेश <linux/major.h>

#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/bपन.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/file.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/mutex.h>
#समावेश <linux/compiler.h>
#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <linux/net.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/types.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/blk-mq.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/types.h>

#समावेश <linux/nbd.h>
#समावेश <linux/nbd-netlink.h>
#समावेश <net/genetlink.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/nbd.h>

अटल DEFINE_IDR(nbd_index_idr);
अटल DEFINE_MUTEX(nbd_index_mutex);
अटल पूर्णांक nbd_total_devices = 0;

काष्ठा nbd_sock अणु
	काष्ठा socket *sock;
	काष्ठा mutex tx_lock;
	काष्ठा request *pending;
	पूर्णांक sent;
	bool dead;
	पूर्णांक fallback_index;
	पूर्णांक cookie;
पूर्ण;

काष्ठा recv_thपढ़ो_args अणु
	काष्ठा work_काष्ठा work;
	काष्ठा nbd_device *nbd;
	पूर्णांक index;
पूर्ण;

काष्ठा link_dead_args अणु
	काष्ठा work_काष्ठा work;
	पूर्णांक index;
पूर्ण;

#घोषणा NBD_RT_TIMEDOUT			0
#घोषणा NBD_RT_DISCONNECT_REQUESTED	1
#घोषणा NBD_RT_DISCONNECTED		2
#घोषणा NBD_RT_HAS_PID_खाता		3
#घोषणा NBD_RT_HAS_CONFIG_REF		4
#घोषणा NBD_RT_BOUND			5
#घोषणा NBD_RT_DISCONNECT_ON_CLOSE	6

#घोषणा NBD_DESTROY_ON_DISCONNECT	0
#घोषणा NBD_DISCONNECT_REQUESTED	1

काष्ठा nbd_config अणु
	u32 flags;
	अचिन्हित दीर्घ runसमय_flags;
	u64 dead_conn_समयout;

	काष्ठा nbd_sock **socks;
	पूर्णांक num_connections;
	atomic_t live_connections;
	रुको_queue_head_t conn_रुको;

	atomic_t recv_thपढ़ोs;
	रुको_queue_head_t recv_wq;
	loff_t blksize;
	loff_t bytesize;
#अगर IS_ENABLED(CONFIG_DEBUG_FS)
	काष्ठा dentry *dbg_dir;
#पूर्ण_अगर
पूर्ण;

काष्ठा nbd_device अणु
	काष्ठा blk_mq_tag_set tag_set;

	पूर्णांक index;
	refcount_t config_refs;
	refcount_t refs;
	काष्ठा nbd_config *config;
	काष्ठा mutex config_lock;
	काष्ठा gendisk *disk;
	काष्ठा workqueue_काष्ठा *recv_workq;

	काष्ठा list_head list;
	काष्ठा task_काष्ठा *task_recv;
	काष्ठा task_काष्ठा *task_setup;

	काष्ठा completion *destroy_complete;
	अचिन्हित दीर्घ flags;
पूर्ण;

#घोषणा NBD_CMD_REQUEUED	1

काष्ठा nbd_cmd अणु
	काष्ठा nbd_device *nbd;
	काष्ठा mutex lock;
	पूर्णांक index;
	पूर्णांक cookie;
	पूर्णांक retries;
	blk_status_t status;
	अचिन्हित दीर्घ flags;
	u32 cmd_cookie;
पूर्ण;

#अगर IS_ENABLED(CONFIG_DEBUG_FS)
अटल काष्ठा dentry *nbd_dbg_dir;
#पूर्ण_अगर

#घोषणा nbd_name(nbd) ((nbd)->disk->disk_name)

#घोषणा NBD_MAGIC 0x68797548

#घोषणा NBD_DEF_BLKSIZE 1024

अटल अचिन्हित पूर्णांक nbds_max = 16;
अटल पूर्णांक max_part = 16;
अटल पूर्णांक part_shअगरt;

अटल पूर्णांक nbd_dev_dbg_init(काष्ठा nbd_device *nbd);
अटल व्योम nbd_dev_dbg_बंद(काष्ठा nbd_device *nbd);
अटल व्योम nbd_config_put(काष्ठा nbd_device *nbd);
अटल व्योम nbd_connect_reply(काष्ठा genl_info *info, पूर्णांक index);
अटल पूर्णांक nbd_genl_status(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
अटल व्योम nbd_dead_link_work(काष्ठा work_काष्ठा *work);
अटल व्योम nbd_disconnect_and_put(काष्ठा nbd_device *nbd);

अटल अंतरभूत काष्ठा device *nbd_to_dev(काष्ठा nbd_device *nbd)
अणु
	वापस disk_to_dev(nbd->disk);
पूर्ण

अटल व्योम nbd_requeue_cmd(काष्ठा nbd_cmd *cmd)
अणु
	काष्ठा request *req = blk_mq_rq_from_pdu(cmd);

	अगर (!test_and_set_bit(NBD_CMD_REQUEUED, &cmd->flags))
		blk_mq_requeue_request(req, true);
पूर्ण

#घोषणा NBD_COOKIE_BITS 32

अटल u64 nbd_cmd_handle(काष्ठा nbd_cmd *cmd)
अणु
	काष्ठा request *req = blk_mq_rq_from_pdu(cmd);
	u32 tag = blk_mq_unique_tag(req);
	u64 cookie = cmd->cmd_cookie;

	वापस (cookie << NBD_COOKIE_BITS) | tag;
पूर्ण

अटल u32 nbd_handle_to_tag(u64 handle)
अणु
	वापस (u32)handle;
पूर्ण

अटल u32 nbd_handle_to_cookie(u64 handle)
अणु
	वापस (u32)(handle >> NBD_COOKIE_BITS);
पूर्ण

अटल स्थिर अक्षर *nbdcmd_to_ascii(पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल  NBD_CMD_READ: वापस "read";
	हाल NBD_CMD_WRITE: वापस "write";
	हाल  NBD_CMD_DISC: वापस "disconnect";
	हाल NBD_CMD_FLUSH: वापस "flush";
	हाल  NBD_CMD_TRIM: वापस "trim/discard";
	पूर्ण
	वापस "invalid";
पूर्ण

अटल sमाप_प्रकार pid_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	काष्ठा nbd_device *nbd = (काष्ठा nbd_device *)disk->निजी_data;

	वापस प्र_लिखो(buf, "%d\n", task_pid_nr(nbd->task_recv));
पूर्ण

अटल स्थिर काष्ठा device_attribute pid_attr = अणु
	.attr = अणु .name = "pid", .mode = 0444पूर्ण,
	.show = pid_show,
पूर्ण;

अटल व्योम nbd_dev_हटाओ(काष्ठा nbd_device *nbd)
अणु
	काष्ठा gendisk *disk = nbd->disk;
	काष्ठा request_queue *q;

	अगर (disk) अणु
		q = disk->queue;
		del_gendisk(disk);
		blk_cleanup_queue(q);
		blk_mq_मुक्त_tag_set(&nbd->tag_set);
		disk->निजी_data = शून्य;
		put_disk(disk);
	पूर्ण

	/*
	 * Place this in the last just beक्रमe the nbd is मुक्तd to
	 * make sure that the disk and the related kobject are also
	 * totally हटाओd to aव्योम duplicate creation of the same
	 * one.
	 */
	अगर (test_bit(NBD_DESTROY_ON_DISCONNECT, &nbd->flags) && nbd->destroy_complete)
		complete(nbd->destroy_complete);

	kमुक्त(nbd);
पूर्ण

अटल व्योम nbd_put(काष्ठा nbd_device *nbd)
अणु
	अगर (refcount_dec_and_mutex_lock(&nbd->refs,
					&nbd_index_mutex)) अणु
		idr_हटाओ(&nbd_index_idr, nbd->index);
		nbd_dev_हटाओ(nbd);
		mutex_unlock(&nbd_index_mutex);
	पूर्ण
पूर्ण

अटल पूर्णांक nbd_disconnected(काष्ठा nbd_config *config)
अणु
	वापस test_bit(NBD_RT_DISCONNECTED, &config->runसमय_flags) ||
		test_bit(NBD_RT_DISCONNECT_REQUESTED, &config->runसमय_flags);
पूर्ण

अटल व्योम nbd_mark_nsock_dead(काष्ठा nbd_device *nbd, काष्ठा nbd_sock *nsock,
				पूर्णांक notअगरy)
अणु
	अगर (!nsock->dead && notअगरy && !nbd_disconnected(nbd->config)) अणु
		काष्ठा link_dead_args *args;
		args = kदो_स्मृति(माप(काष्ठा link_dead_args), GFP_NOIO);
		अगर (args) अणु
			INIT_WORK(&args->work, nbd_dead_link_work);
			args->index = nbd->index;
			queue_work(प्रणाली_wq, &args->work);
		पूर्ण
	पूर्ण
	अगर (!nsock->dead) अणु
		kernel_sock_shutकरोwn(nsock->sock, SHUT_RDWR);
		अगर (atomic_dec_वापस(&nbd->config->live_connections) == 0) अणु
			अगर (test_and_clear_bit(NBD_RT_DISCONNECT_REQUESTED,
					       &nbd->config->runसमय_flags)) अणु
				set_bit(NBD_RT_DISCONNECTED,
					&nbd->config->runसमय_flags);
				dev_info(nbd_to_dev(nbd),
					"Disconnected due to user request.\n");
			पूर्ण
		पूर्ण
	पूर्ण
	nsock->dead = true;
	nsock->pending = शून्य;
	nsock->sent = 0;
पूर्ण

अटल व्योम nbd_size_clear(काष्ठा nbd_device *nbd)
अणु
	अगर (nbd->config->bytesize) अणु
		set_capacity(nbd->disk, 0);
		kobject_uevent(&nbd_to_dev(nbd)->kobj, KOBJ_CHANGE);
	पूर्ण
पूर्ण

अटल पूर्णांक nbd_set_size(काष्ठा nbd_device *nbd, loff_t bytesize,
		loff_t blksize)
अणु
	अगर (!blksize)
		blksize = NBD_DEF_BLKSIZE;
	अगर (blksize < 512 || blksize > PAGE_SIZE || !is_घातer_of_2(blksize))
		वापस -EINVAL;

	nbd->config->bytesize = bytesize;
	nbd->config->blksize = blksize;

	अगर (!nbd->task_recv)
		वापस 0;

	अगर (nbd->config->flags & NBD_FLAG_SEND_TRIM) अणु
		nbd->disk->queue->limits.discard_granularity = blksize;
		nbd->disk->queue->limits.discard_alignment = blksize;
		blk_queue_max_discard_sectors(nbd->disk->queue, अच_पूर्णांक_उच्च);
	पूर्ण
	blk_queue_logical_block_size(nbd->disk->queue, blksize);
	blk_queue_physical_block_size(nbd->disk->queue, blksize);

	अगर (max_part)
		set_bit(GD_NEED_PART_SCAN, &nbd->disk->state);
	अगर (!set_capacity_and_notअगरy(nbd->disk, bytesize >> 9))
		kobject_uevent(&nbd_to_dev(nbd)->kobj, KOBJ_CHANGE);
	वापस 0;
पूर्ण

अटल व्योम nbd_complete_rq(काष्ठा request *req)
अणु
	काष्ठा nbd_cmd *cmd = blk_mq_rq_to_pdu(req);

	dev_dbg(nbd_to_dev(cmd->nbd), "request %p: %s\n", req,
		cmd->status ? "failed" : "done");

	blk_mq_end_request(req, cmd->status);
पूर्ण

/*
 * Forcibly shutकरोwn the socket causing all listeners to error
 */
अटल व्योम sock_shutकरोwn(काष्ठा nbd_device *nbd)
अणु
	काष्ठा nbd_config *config = nbd->config;
	पूर्णांक i;

	अगर (config->num_connections == 0)
		वापस;
	अगर (test_and_set_bit(NBD_RT_DISCONNECTED, &config->runसमय_flags))
		वापस;

	क्रम (i = 0; i < config->num_connections; i++) अणु
		काष्ठा nbd_sock *nsock = config->socks[i];
		mutex_lock(&nsock->tx_lock);
		nbd_mark_nsock_dead(nbd, nsock, 0);
		mutex_unlock(&nsock->tx_lock);
	पूर्ण
	dev_warn(disk_to_dev(nbd->disk), "shutting down sockets\n");
पूर्ण

अटल u32 req_to_nbd_cmd_type(काष्ठा request *req)
अणु
	चयन (req_op(req)) अणु
	हाल REQ_OP_DISCARD:
		वापस NBD_CMD_TRIM;
	हाल REQ_OP_FLUSH:
		वापस NBD_CMD_FLUSH;
	हाल REQ_OP_WRITE:
		वापस NBD_CMD_WRITE;
	हाल REQ_OP_READ:
		वापस NBD_CMD_READ;
	शेष:
		वापस U32_MAX;
	पूर्ण
पूर्ण

अटल क्रमागत blk_eh_समयr_वापस nbd_xmit_समयout(काष्ठा request *req,
						 bool reserved)
अणु
	काष्ठा nbd_cmd *cmd = blk_mq_rq_to_pdu(req);
	काष्ठा nbd_device *nbd = cmd->nbd;
	काष्ठा nbd_config *config;

	अगर (!mutex_trylock(&cmd->lock))
		वापस BLK_EH_RESET_TIMER;

	अगर (!refcount_inc_not_zero(&nbd->config_refs)) अणु
		cmd->status = BLK_STS_TIMEOUT;
		mutex_unlock(&cmd->lock);
		जाओ करोne;
	पूर्ण
	config = nbd->config;

	अगर (config->num_connections > 1 ||
	    (config->num_connections == 1 && nbd->tag_set.समयout)) अणु
		dev_err_ratelimited(nbd_to_dev(nbd),
				    "Connection timed out, retrying (%d/%d alive)\n",
				    atomic_पढ़ो(&config->live_connections),
				    config->num_connections);
		/*
		 * Hooray we have more connections, requeue this IO, the submit
		 * path will put it on a real connection. Or अगर only one
		 * connection is configured, the submit path will रुको util
		 * a new connection is reconfigured or util dead समयout.
		 */
		अगर (config->socks) अणु
			अगर (cmd->index < config->num_connections) अणु
				काष्ठा nbd_sock *nsock =
					config->socks[cmd->index];
				mutex_lock(&nsock->tx_lock);
				/* We can have multiple outstanding requests, so
				 * we करोn't want to mark the nsock dead if we've
				 * alपढ़ोy reconnected with a new socket, so
				 * only mark it dead अगर its the same socket we
				 * were sent out on.
				 */
				अगर (cmd->cookie == nsock->cookie)
					nbd_mark_nsock_dead(nbd, nsock, 1);
				mutex_unlock(&nsock->tx_lock);
			पूर्ण
			mutex_unlock(&cmd->lock);
			nbd_requeue_cmd(cmd);
			nbd_config_put(nbd);
			वापस BLK_EH_DONE;
		पूर्ण
	पूर्ण

	अगर (!nbd->tag_set.समयout) अणु
		/*
		 * Userspace sets समयout=0 to disable socket disconnection,
		 * so just warn and reset the समयr.
		 */
		काष्ठा nbd_sock *nsock = config->socks[cmd->index];
		cmd->retries++;
		dev_info(nbd_to_dev(nbd), "Possible stuck request %p: control (%s@%llu,%uB). Runtime %u seconds\n",
			req, nbdcmd_to_ascii(req_to_nbd_cmd_type(req)),
			(अचिन्हित दीर्घ दीर्घ)blk_rq_pos(req) << 9,
			blk_rq_bytes(req), (req->समयout / HZ) * cmd->retries);

		mutex_lock(&nsock->tx_lock);
		अगर (cmd->cookie != nsock->cookie) अणु
			nbd_requeue_cmd(cmd);
			mutex_unlock(&nsock->tx_lock);
			mutex_unlock(&cmd->lock);
			nbd_config_put(nbd);
			वापस BLK_EH_DONE;
		पूर्ण
		mutex_unlock(&nsock->tx_lock);
		mutex_unlock(&cmd->lock);
		nbd_config_put(nbd);
		वापस BLK_EH_RESET_TIMER;
	पूर्ण

	dev_err_ratelimited(nbd_to_dev(nbd), "Connection timed out\n");
	set_bit(NBD_RT_TIMEDOUT, &config->runसमय_flags);
	cmd->status = BLK_STS_IOERR;
	mutex_unlock(&cmd->lock);
	sock_shutकरोwn(nbd);
	nbd_config_put(nbd);
करोne:
	blk_mq_complete_request(req);
	वापस BLK_EH_DONE;
पूर्ण

/*
 *  Send or receive packet.
 */
अटल पूर्णांक sock_xmit(काष्ठा nbd_device *nbd, पूर्णांक index, पूर्णांक send,
		     काष्ठा iov_iter *iter, पूर्णांक msg_flags, पूर्णांक *sent)
अणु
	काष्ठा nbd_config *config = nbd->config;
	काष्ठा socket *sock = config->socks[index]->sock;
	पूर्णांक result;
	काष्ठा msghdr msg;
	अचिन्हित पूर्णांक noreclaim_flag;

	अगर (unlikely(!sock)) अणु
		dev_err_ratelimited(disk_to_dev(nbd->disk),
			"Attempted %s on closed socket in sock_xmit\n",
			(send ? "send" : "recv"));
		वापस -EINVAL;
	पूर्ण

	msg.msg_iter = *iter;

	noreclaim_flag = meदो_स्मृति_noreclaim_save();
	करो अणु
		sock->sk->sk_allocation = GFP_NOIO | __GFP_MEMALLOC;
		msg.msg_name = शून्य;
		msg.msg_namelen = 0;
		msg.msg_control = शून्य;
		msg.msg_controllen = 0;
		msg.msg_flags = msg_flags | MSG_NOSIGNAL;

		अगर (send)
			result = sock_sendmsg(sock, &msg);
		अन्यथा
			result = sock_recvmsg(sock, &msg, msg.msg_flags);

		अगर (result <= 0) अणु
			अगर (result == 0)
				result = -EPIPE; /* लघु पढ़ो */
			अवरोध;
		पूर्ण
		अगर (sent)
			*sent += result;
	पूर्ण जबतक (msg_data_left(&msg));

	meदो_स्मृति_noreclaim_restore(noreclaim_flag);

	वापस result;
पूर्ण

/*
 * Dअगरferent settings क्रम sk->sk_sndसमयo can result in dअगरferent वापस values
 * अगर there is a संकेत pending when we enter sendmsg, because reasons?
 */
अटल अंतरभूत पूर्णांक was_पूर्णांकerrupted(पूर्णांक result)
अणु
	वापस result == -ERESTARTSYS || result == -EINTR;
पूर्ण

/* always call with the tx_lock held */
अटल पूर्णांक nbd_send_cmd(काष्ठा nbd_device *nbd, काष्ठा nbd_cmd *cmd, पूर्णांक index)
अणु
	काष्ठा request *req = blk_mq_rq_from_pdu(cmd);
	काष्ठा nbd_config *config = nbd->config;
	काष्ठा nbd_sock *nsock = config->socks[index];
	पूर्णांक result;
	काष्ठा nbd_request request = अणु.magic = htonl(NBD_REQUEST_MAGIC)पूर्ण;
	काष्ठा kvec iov = अणु.iov_base = &request, .iov_len = माप(request)पूर्ण;
	काष्ठा iov_iter from;
	अचिन्हित दीर्घ size = blk_rq_bytes(req);
	काष्ठा bio *bio;
	u64 handle;
	u32 type;
	u32 nbd_cmd_flags = 0;
	पूर्णांक sent = nsock->sent, skip = 0;

	iov_iter_kvec(&from, WRITE, &iov, 1, माप(request));

	type = req_to_nbd_cmd_type(req);
	अगर (type == U32_MAX)
		वापस -EIO;

	अगर (rq_data_dir(req) == WRITE &&
	    (config->flags & NBD_FLAG_READ_ONLY)) अणु
		dev_err_ratelimited(disk_to_dev(nbd->disk),
				    "Write on read-only\n");
		वापस -EIO;
	पूर्ण

	अगर (req->cmd_flags & REQ_FUA)
		nbd_cmd_flags |= NBD_CMD_FLAG_FUA;

	/* We did a partial send previously, and we at least sent the whole
	 * request काष्ठा, so just go and send the rest of the pages in the
	 * request.
	 */
	अगर (sent) अणु
		अगर (sent >= माप(request)) अणु
			skip = sent - माप(request);

			/* initialize handle क्रम tracing purposes */
			handle = nbd_cmd_handle(cmd);

			जाओ send_pages;
		पूर्ण
		iov_iter_advance(&from, sent);
	पूर्ण अन्यथा अणु
		cmd->cmd_cookie++;
	पूर्ण
	cmd->index = index;
	cmd->cookie = nsock->cookie;
	cmd->retries = 0;
	request.type = htonl(type | nbd_cmd_flags);
	अगर (type != NBD_CMD_FLUSH) अणु
		request.from = cpu_to_be64((u64)blk_rq_pos(req) << 9);
		request.len = htonl(size);
	पूर्ण
	handle = nbd_cmd_handle(cmd);
	स_नकल(request.handle, &handle, माप(handle));

	trace_nbd_send_request(&request, nbd->index, blk_mq_rq_from_pdu(cmd));

	dev_dbg(nbd_to_dev(nbd), "request %p: sending control (%s@%llu,%uB)\n",
		req, nbdcmd_to_ascii(type),
		(अचिन्हित दीर्घ दीर्घ)blk_rq_pos(req) << 9, blk_rq_bytes(req));
	result = sock_xmit(nbd, index, 1, &from,
			(type == NBD_CMD_WRITE) ? MSG_MORE : 0, &sent);
	trace_nbd_header_sent(req, handle);
	अगर (result <= 0) अणु
		अगर (was_पूर्णांकerrupted(result)) अणु
			/* If we havne't sent anything we can just वापस BUSY,
			 * however अगर we have sent something we need to make
			 * sure we only allow this req to be sent until we are
			 * completely करोne.
			 */
			अगर (sent) अणु
				nsock->pending = req;
				nsock->sent = sent;
			पूर्ण
			set_bit(NBD_CMD_REQUEUED, &cmd->flags);
			वापस BLK_STS_RESOURCE;
		पूर्ण
		dev_err_ratelimited(disk_to_dev(nbd->disk),
			"Send control failed (result %d)\n", result);
		वापस -EAGAIN;
	पूर्ण
send_pages:
	अगर (type != NBD_CMD_WRITE)
		जाओ out;

	bio = req->bio;
	जबतक (bio) अणु
		काष्ठा bio *next = bio->bi_next;
		काष्ठा bvec_iter iter;
		काष्ठा bio_vec bvec;

		bio_क्रम_each_segment(bvec, bio, iter) अणु
			bool is_last = !next && bio_iter_last(bvec, iter);
			पूर्णांक flags = is_last ? 0 : MSG_MORE;

			dev_dbg(nbd_to_dev(nbd), "request %p: sending %d bytes data\n",
				req, bvec.bv_len);
			iov_iter_bvec(&from, WRITE, &bvec, 1, bvec.bv_len);
			अगर (skip) अणु
				अगर (skip >= iov_iter_count(&from)) अणु
					skip -= iov_iter_count(&from);
					जारी;
				पूर्ण
				iov_iter_advance(&from, skip);
				skip = 0;
			पूर्ण
			result = sock_xmit(nbd, index, 1, &from, flags, &sent);
			अगर (result <= 0) अणु
				अगर (was_पूर्णांकerrupted(result)) अणु
					/* We've alपढ़ोy sent the header, we
					 * have no choice but to set pending and
					 * वापस BUSY.
					 */
					nsock->pending = req;
					nsock->sent = sent;
					set_bit(NBD_CMD_REQUEUED, &cmd->flags);
					वापस BLK_STS_RESOURCE;
				पूर्ण
				dev_err(disk_to_dev(nbd->disk),
					"Send data failed (result %d)\n",
					result);
				वापस -EAGAIN;
			पूर्ण
			/*
			 * The completion might alपढ़ोy have come in,
			 * so अवरोध क्रम the last one instead of letting
			 * the iterator करो it. This prevents use-after-मुक्त
			 * of the bio.
			 */
			अगर (is_last)
				अवरोध;
		पूर्ण
		bio = next;
	पूर्ण
out:
	trace_nbd_payload_sent(req, handle);
	nsock->pending = शून्य;
	nsock->sent = 0;
	वापस 0;
पूर्ण

/* शून्य वापसed = something went wrong, inक्रमm userspace */
अटल काष्ठा nbd_cmd *nbd_पढ़ो_stat(काष्ठा nbd_device *nbd, पूर्णांक index)
अणु
	काष्ठा nbd_config *config = nbd->config;
	पूर्णांक result;
	काष्ठा nbd_reply reply;
	काष्ठा nbd_cmd *cmd;
	काष्ठा request *req = शून्य;
	u64 handle;
	u16 hwq;
	u32 tag;
	काष्ठा kvec iov = अणु.iov_base = &reply, .iov_len = माप(reply)पूर्ण;
	काष्ठा iov_iter to;
	पूर्णांक ret = 0;

	reply.magic = 0;
	iov_iter_kvec(&to, READ, &iov, 1, माप(reply));
	result = sock_xmit(nbd, index, 0, &to, MSG_WAITALL, शून्य);
	अगर (result <= 0) अणु
		अगर (!nbd_disconnected(config))
			dev_err(disk_to_dev(nbd->disk),
				"Receive control failed (result %d)\n", result);
		वापस ERR_PTR(result);
	पूर्ण

	अगर (ntohl(reply.magic) != NBD_REPLY_MAGIC) अणु
		dev_err(disk_to_dev(nbd->disk), "Wrong magic (0x%lx)\n",
				(अचिन्हित दीर्घ)ntohl(reply.magic));
		वापस ERR_PTR(-EPROTO);
	पूर्ण

	स_नकल(&handle, reply.handle, माप(handle));
	tag = nbd_handle_to_tag(handle);
	hwq = blk_mq_unique_tag_to_hwq(tag);
	अगर (hwq < nbd->tag_set.nr_hw_queues)
		req = blk_mq_tag_to_rq(nbd->tag_set.tags[hwq],
				       blk_mq_unique_tag_to_tag(tag));
	अगर (!req || !blk_mq_request_started(req)) अणु
		dev_err(disk_to_dev(nbd->disk), "Unexpected reply (%d) %p\n",
			tag, req);
		वापस ERR_PTR(-ENOENT);
	पूर्ण
	trace_nbd_header_received(req, handle);
	cmd = blk_mq_rq_to_pdu(req);

	mutex_lock(&cmd->lock);
	अगर (cmd->cmd_cookie != nbd_handle_to_cookie(handle)) अणु
		dev_err(disk_to_dev(nbd->disk), "Double reply on req %p, cmd_cookie %u, handle cookie %u\n",
			req, cmd->cmd_cookie, nbd_handle_to_cookie(handle));
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	अगर (cmd->status != BLK_STS_OK) अणु
		dev_err(disk_to_dev(nbd->disk), "Command already handled %p\n",
			req);
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	अगर (test_bit(NBD_CMD_REQUEUED, &cmd->flags)) अणु
		dev_err(disk_to_dev(nbd->disk), "Raced with timeout on req %p\n",
			req);
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	अगर (ntohl(reply.error)) अणु
		dev_err(disk_to_dev(nbd->disk), "Other side returned error (%d)\n",
			ntohl(reply.error));
		cmd->status = BLK_STS_IOERR;
		जाओ out;
	पूर्ण

	dev_dbg(nbd_to_dev(nbd), "request %p: got reply\n", req);
	अगर (rq_data_dir(req) != WRITE) अणु
		काष्ठा req_iterator iter;
		काष्ठा bio_vec bvec;

		rq_क्रम_each_segment(bvec, req, iter) अणु
			iov_iter_bvec(&to, READ, &bvec, 1, bvec.bv_len);
			result = sock_xmit(nbd, index, 0, &to, MSG_WAITALL, शून्य);
			अगर (result <= 0) अणु
				dev_err(disk_to_dev(nbd->disk), "Receive data failed (result %d)\n",
					result);
				/*
				 * If we've disconnected, we need to make sure we
				 * complete this request, otherwise error out
				 * and let the समयout stuff handle resubmitting
				 * this request onto another connection.
				 */
				अगर (nbd_disconnected(config)) अणु
					cmd->status = BLK_STS_IOERR;
					जाओ out;
				पूर्ण
				ret = -EIO;
				जाओ out;
			पूर्ण
			dev_dbg(nbd_to_dev(nbd), "request %p: got %d bytes data\n",
				req, bvec.bv_len);
		पूर्ण
	पूर्ण
out:
	trace_nbd_payload_received(req, handle);
	mutex_unlock(&cmd->lock);
	वापस ret ? ERR_PTR(ret) : cmd;
पूर्ण

अटल व्योम recv_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा recv_thपढ़ो_args *args = container_of(work,
						     काष्ठा recv_thपढ़ो_args,
						     work);
	काष्ठा nbd_device *nbd = args->nbd;
	काष्ठा nbd_config *config = nbd->config;
	काष्ठा nbd_cmd *cmd;
	काष्ठा request *rq;

	जबतक (1) अणु
		cmd = nbd_पढ़ो_stat(nbd, args->index);
		अगर (IS_ERR(cmd)) अणु
			काष्ठा nbd_sock *nsock = config->socks[args->index];

			mutex_lock(&nsock->tx_lock);
			nbd_mark_nsock_dead(nbd, nsock, 1);
			mutex_unlock(&nsock->tx_lock);
			अवरोध;
		पूर्ण

		rq = blk_mq_rq_from_pdu(cmd);
		अगर (likely(!blk_should_fake_समयout(rq->q)))
			blk_mq_complete_request(rq);
	पूर्ण
	nbd_config_put(nbd);
	atomic_dec(&config->recv_thपढ़ोs);
	wake_up(&config->recv_wq);
	kमुक्त(args);
पूर्ण

अटल bool nbd_clear_req(काष्ठा request *req, व्योम *data, bool reserved)
अणु
	काष्ठा nbd_cmd *cmd = blk_mq_rq_to_pdu(req);

	mutex_lock(&cmd->lock);
	cmd->status = BLK_STS_IOERR;
	mutex_unlock(&cmd->lock);

	blk_mq_complete_request(req);
	वापस true;
पूर्ण

अटल व्योम nbd_clear_que(काष्ठा nbd_device *nbd)
अणु
	blk_mq_quiesce_queue(nbd->disk->queue);
	blk_mq_tagset_busy_iter(&nbd->tag_set, nbd_clear_req, शून्य);
	blk_mq_unquiesce_queue(nbd->disk->queue);
	dev_dbg(disk_to_dev(nbd->disk), "queue cleared\n");
पूर्ण

अटल पूर्णांक find_fallback(काष्ठा nbd_device *nbd, पूर्णांक index)
अणु
	काष्ठा nbd_config *config = nbd->config;
	पूर्णांक new_index = -1;
	काष्ठा nbd_sock *nsock = config->socks[index];
	पूर्णांक fallback = nsock->fallback_index;

	अगर (test_bit(NBD_RT_DISCONNECTED, &config->runसमय_flags))
		वापस new_index;

	अगर (config->num_connections <= 1) अणु
		dev_err_ratelimited(disk_to_dev(nbd->disk),
				    "Dead connection, failed to find a fallback\n");
		वापस new_index;
	पूर्ण

	अगर (fallback >= 0 && fallback < config->num_connections &&
	    !config->socks[fallback]->dead)
		वापस fallback;

	अगर (nsock->fallback_index < 0 ||
	    nsock->fallback_index >= config->num_connections ||
	    config->socks[nsock->fallback_index]->dead) अणु
		पूर्णांक i;
		क्रम (i = 0; i < config->num_connections; i++) अणु
			अगर (i == index)
				जारी;
			अगर (!config->socks[i]->dead) अणु
				new_index = i;
				अवरोध;
			पूर्ण
		पूर्ण
		nsock->fallback_index = new_index;
		अगर (new_index < 0) अणु
			dev_err_ratelimited(disk_to_dev(nbd->disk),
					    "Dead connection, failed to find a fallback\n");
			वापस new_index;
		पूर्ण
	पूर्ण
	new_index = nsock->fallback_index;
	वापस new_index;
पूर्ण

अटल पूर्णांक रुको_क्रम_reconnect(काष्ठा nbd_device *nbd)
अणु
	काष्ठा nbd_config *config = nbd->config;
	अगर (!config->dead_conn_समयout)
		वापस 0;
	अगर (test_bit(NBD_RT_DISCONNECTED, &config->runसमय_flags))
		वापस 0;
	वापस रुको_event_समयout(config->conn_रुको,
				  atomic_पढ़ो(&config->live_connections) > 0,
				  config->dead_conn_समयout) > 0;
पूर्ण

अटल पूर्णांक nbd_handle_cmd(काष्ठा nbd_cmd *cmd, पूर्णांक index)
अणु
	काष्ठा request *req = blk_mq_rq_from_pdu(cmd);
	काष्ठा nbd_device *nbd = cmd->nbd;
	काष्ठा nbd_config *config;
	काष्ठा nbd_sock *nsock;
	पूर्णांक ret;

	अगर (!refcount_inc_not_zero(&nbd->config_refs)) अणु
		dev_err_ratelimited(disk_to_dev(nbd->disk),
				    "Socks array is empty\n");
		blk_mq_start_request(req);
		वापस -EINVAL;
	पूर्ण
	config = nbd->config;

	अगर (index >= config->num_connections) अणु
		dev_err_ratelimited(disk_to_dev(nbd->disk),
				    "Attempted send on invalid socket\n");
		nbd_config_put(nbd);
		blk_mq_start_request(req);
		वापस -EINVAL;
	पूर्ण
	cmd->status = BLK_STS_OK;
again:
	nsock = config->socks[index];
	mutex_lock(&nsock->tx_lock);
	अगर (nsock->dead) अणु
		पूर्णांक old_index = index;
		index = find_fallback(nbd, index);
		mutex_unlock(&nsock->tx_lock);
		अगर (index < 0) अणु
			अगर (रुको_क्रम_reconnect(nbd)) अणु
				index = old_index;
				जाओ again;
			पूर्ण
			/* All the sockets should alपढ़ोy be करोwn at this poपूर्णांक,
			 * we just want to make sure that DISCONNECTED is set so
			 * any requests that come in that were queue'ed रुकोing
			 * क्रम the reconnect समयr करोn't trigger the समयr again
			 * and instead just error out.
			 */
			sock_shutकरोwn(nbd);
			nbd_config_put(nbd);
			blk_mq_start_request(req);
			वापस -EIO;
		पूर्ण
		जाओ again;
	पूर्ण

	/* Handle the हाल that we have a pending request that was partially
	 * transmitted that _has_ to be serviced first.  We need to call requeue
	 * here so that it माला_लो put _after_ the request that is alपढ़ोy on the
	 * dispatch list.
	 */
	blk_mq_start_request(req);
	अगर (unlikely(nsock->pending && nsock->pending != req)) अणु
		nbd_requeue_cmd(cmd);
		ret = 0;
		जाओ out;
	पूर्ण
	/*
	 * Some failures are related to the link going करोwn, so anything that
	 * वापसs EAGAIN can be retried on a dअगरferent socket.
	 */
	ret = nbd_send_cmd(nbd, cmd, index);
	अगर (ret == -EAGAIN) अणु
		dev_err_ratelimited(disk_to_dev(nbd->disk),
				    "Request send failed, requeueing\n");
		nbd_mark_nsock_dead(nbd, nsock, 1);
		nbd_requeue_cmd(cmd);
		ret = 0;
	पूर्ण
out:
	mutex_unlock(&nsock->tx_lock);
	nbd_config_put(nbd);
	वापस ret;
पूर्ण

अटल blk_status_t nbd_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
			स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा nbd_cmd *cmd = blk_mq_rq_to_pdu(bd->rq);
	पूर्णांक ret;

	/*
	 * Since we look at the bio's to send the request over the network we
	 * need to make sure the completion work करोesn't mark this request करोne
	 * beक्रमe we are करोne करोing our send.  This keeps us from dereferencing
	 * मुक्तd data अगर we have particularly fast completions (ie we get the
	 * completion beक्रमe we निकास sock_xmit on the last bvec) or in the हाल
	 * that the server is misbehaving (or there was an error) beक्रमe we're
	 * करोne sending everything over the wire.
	 */
	mutex_lock(&cmd->lock);
	clear_bit(NBD_CMD_REQUEUED, &cmd->flags);

	/* We can be called directly from the user space process, which means we
	 * could possibly have संकेतs pending so our sendmsg will fail.  In
	 * this हाल we need to वापस that we are busy, otherwise error out as
	 * appropriate.
	 */
	ret = nbd_handle_cmd(cmd, hctx->queue_num);
	अगर (ret < 0)
		ret = BLK_STS_IOERR;
	अन्यथा अगर (!ret)
		ret = BLK_STS_OK;
	mutex_unlock(&cmd->lock);

	वापस ret;
पूर्ण

अटल काष्ठा socket *nbd_get_socket(काष्ठा nbd_device *nbd, अचिन्हित दीर्घ fd,
				     पूर्णांक *err)
अणु
	काष्ठा socket *sock;

	*err = 0;
	sock = sockfd_lookup(fd, err);
	अगर (!sock)
		वापस शून्य;

	अगर (sock->ops->shutकरोwn == sock_no_shutकरोwn) अणु
		dev_err(disk_to_dev(nbd->disk), "Unsupported socket: shutdown callout must be supported.\n");
		*err = -EINVAL;
		sockfd_put(sock);
		वापस शून्य;
	पूर्ण

	वापस sock;
पूर्ण

अटल पूर्णांक nbd_add_socket(काष्ठा nbd_device *nbd, अचिन्हित दीर्घ arg,
			  bool netlink)
अणु
	काष्ठा nbd_config *config = nbd->config;
	काष्ठा socket *sock;
	काष्ठा nbd_sock **socks;
	काष्ठा nbd_sock *nsock;
	पूर्णांक err;

	sock = nbd_get_socket(nbd, arg, &err);
	अगर (!sock)
		वापस err;

	/*
	 * We need to make sure we करोn't get any errant requests while we're
	 * पुनः_स्मृतिating the ->socks array.
	 */
	blk_mq_मुक्तze_queue(nbd->disk->queue);

	अगर (!netlink && !nbd->task_setup &&
	    !test_bit(NBD_RT_BOUND, &config->runसमय_flags))
		nbd->task_setup = current;

	अगर (!netlink &&
	    (nbd->task_setup != current ||
	     test_bit(NBD_RT_BOUND, &config->runसमय_flags))) अणु
		dev_err(disk_to_dev(nbd->disk),
			"Device being setup by another task");
		err = -EBUSY;
		जाओ put_socket;
	पूर्ण

	nsock = kzalloc(माप(*nsock), GFP_KERNEL);
	अगर (!nsock) अणु
		err = -ENOMEM;
		जाओ put_socket;
	पूर्ण

	socks = kपुनः_स्मृति(config->socks, (config->num_connections + 1) *
			 माप(काष्ठा nbd_sock *), GFP_KERNEL);
	अगर (!socks) अणु
		kमुक्त(nsock);
		err = -ENOMEM;
		जाओ put_socket;
	पूर्ण

	config->socks = socks;

	nsock->fallback_index = -1;
	nsock->dead = false;
	mutex_init(&nsock->tx_lock);
	nsock->sock = sock;
	nsock->pending = शून्य;
	nsock->sent = 0;
	nsock->cookie = 0;
	socks[config->num_connections++] = nsock;
	atomic_inc(&config->live_connections);
	blk_mq_unमुक्तze_queue(nbd->disk->queue);

	वापस 0;

put_socket:
	blk_mq_unमुक्तze_queue(nbd->disk->queue);
	sockfd_put(sock);
	वापस err;
पूर्ण

अटल पूर्णांक nbd_reconnect_socket(काष्ठा nbd_device *nbd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा nbd_config *config = nbd->config;
	काष्ठा socket *sock, *old;
	काष्ठा recv_thपढ़ो_args *args;
	पूर्णांक i;
	पूर्णांक err;

	sock = nbd_get_socket(nbd, arg, &err);
	अगर (!sock)
		वापस err;

	args = kzalloc(माप(*args), GFP_KERNEL);
	अगर (!args) अणु
		sockfd_put(sock);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < config->num_connections; i++) अणु
		काष्ठा nbd_sock *nsock = config->socks[i];

		अगर (!nsock->dead)
			जारी;

		mutex_lock(&nsock->tx_lock);
		अगर (!nsock->dead) अणु
			mutex_unlock(&nsock->tx_lock);
			जारी;
		पूर्ण
		sk_set_meदो_स्मृति(sock->sk);
		अगर (nbd->tag_set.समयout)
			sock->sk->sk_sndसमयo = nbd->tag_set.समयout;
		atomic_inc(&config->recv_thपढ़ोs);
		refcount_inc(&nbd->config_refs);
		old = nsock->sock;
		nsock->fallback_index = -1;
		nsock->sock = sock;
		nsock->dead = false;
		INIT_WORK(&args->work, recv_work);
		args->index = i;
		args->nbd = nbd;
		nsock->cookie++;
		mutex_unlock(&nsock->tx_lock);
		sockfd_put(old);

		clear_bit(NBD_RT_DISCONNECTED, &config->runसमय_flags);

		/* We take the tx_mutex in an error path in the recv_work, so we
		 * need to queue_work outside of the tx_mutex.
		 */
		queue_work(nbd->recv_workq, &args->work);

		atomic_inc(&config->live_connections);
		wake_up(&config->conn_रुको);
		वापस 0;
	पूर्ण
	sockfd_put(sock);
	kमुक्त(args);
	वापस -ENOSPC;
पूर्ण

अटल व्योम nbd_bdev_reset(काष्ठा block_device *bdev)
अणु
	अगर (bdev->bd_खोलोers > 1)
		वापस;
	set_capacity(bdev->bd_disk, 0);
पूर्ण

अटल व्योम nbd_parse_flags(काष्ठा nbd_device *nbd)
अणु
	काष्ठा nbd_config *config = nbd->config;
	अगर (config->flags & NBD_FLAG_READ_ONLY)
		set_disk_ro(nbd->disk, true);
	अन्यथा
		set_disk_ro(nbd->disk, false);
	अगर (config->flags & NBD_FLAG_SEND_TRIM)
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, nbd->disk->queue);
	अगर (config->flags & NBD_FLAG_SEND_FLUSH) अणु
		अगर (config->flags & NBD_FLAG_SEND_FUA)
			blk_queue_ग_लिखो_cache(nbd->disk->queue, true, true);
		अन्यथा
			blk_queue_ग_लिखो_cache(nbd->disk->queue, true, false);
	पूर्ण
	अन्यथा
		blk_queue_ग_लिखो_cache(nbd->disk->queue, false, false);
पूर्ण

अटल व्योम send_disconnects(काष्ठा nbd_device *nbd)
अणु
	काष्ठा nbd_config *config = nbd->config;
	काष्ठा nbd_request request = अणु
		.magic = htonl(NBD_REQUEST_MAGIC),
		.type = htonl(NBD_CMD_DISC),
	पूर्ण;
	काष्ठा kvec iov = अणु.iov_base = &request, .iov_len = माप(request)पूर्ण;
	काष्ठा iov_iter from;
	पूर्णांक i, ret;

	क्रम (i = 0; i < config->num_connections; i++) अणु
		काष्ठा nbd_sock *nsock = config->socks[i];

		iov_iter_kvec(&from, WRITE, &iov, 1, माप(request));
		mutex_lock(&nsock->tx_lock);
		ret = sock_xmit(nbd, i, 1, &from, 0, शून्य);
		अगर (ret <= 0)
			dev_err(disk_to_dev(nbd->disk),
				"Send disconnect failed %d\n", ret);
		mutex_unlock(&nsock->tx_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक nbd_disconnect(काष्ठा nbd_device *nbd)
अणु
	काष्ठा nbd_config *config = nbd->config;

	dev_info(disk_to_dev(nbd->disk), "NBD_DISCONNECT\n");
	set_bit(NBD_RT_DISCONNECT_REQUESTED, &config->runसमय_flags);
	set_bit(NBD_DISCONNECT_REQUESTED, &nbd->flags);
	send_disconnects(nbd);
	वापस 0;
पूर्ण

अटल व्योम nbd_clear_sock(काष्ठा nbd_device *nbd)
अणु
	sock_shutकरोwn(nbd);
	nbd_clear_que(nbd);
	nbd->task_setup = शून्य;
पूर्ण

अटल व्योम nbd_config_put(काष्ठा nbd_device *nbd)
अणु
	अगर (refcount_dec_and_mutex_lock(&nbd->config_refs,
					&nbd->config_lock)) अणु
		काष्ठा nbd_config *config = nbd->config;
		nbd_dev_dbg_बंद(nbd);
		nbd_size_clear(nbd);
		अगर (test_and_clear_bit(NBD_RT_HAS_PID_खाता,
				       &config->runसमय_flags))
			device_हटाओ_file(disk_to_dev(nbd->disk), &pid_attr);
		nbd->task_recv = शून्य;
		nbd_clear_sock(nbd);
		अगर (config->num_connections) अणु
			पूर्णांक i;
			क्रम (i = 0; i < config->num_connections; i++) अणु
				sockfd_put(config->socks[i]->sock);
				kमुक्त(config->socks[i]);
			पूर्ण
			kमुक्त(config->socks);
		पूर्ण
		kमुक्त(nbd->config);
		nbd->config = शून्य;

		अगर (nbd->recv_workq)
			destroy_workqueue(nbd->recv_workq);
		nbd->recv_workq = शून्य;

		nbd->tag_set.समयout = 0;
		nbd->disk->queue->limits.discard_granularity = 0;
		nbd->disk->queue->limits.discard_alignment = 0;
		blk_queue_max_discard_sectors(nbd->disk->queue, अच_पूर्णांक_उच्च);
		blk_queue_flag_clear(QUEUE_FLAG_DISCARD, nbd->disk->queue);

		mutex_unlock(&nbd->config_lock);
		nbd_put(nbd);
		module_put(THIS_MODULE);
	पूर्ण
पूर्ण

अटल पूर्णांक nbd_start_device(काष्ठा nbd_device *nbd)
अणु
	काष्ठा nbd_config *config = nbd->config;
	पूर्णांक num_connections = config->num_connections;
	पूर्णांक error = 0, i;

	अगर (nbd->task_recv)
		वापस -EBUSY;
	अगर (!config->socks)
		वापस -EINVAL;
	अगर (num_connections > 1 &&
	    !(config->flags & NBD_FLAG_CAN_MULTI_CONN)) अणु
		dev_err(disk_to_dev(nbd->disk), "server does not support multiple connections per device.\n");
		वापस -EINVAL;
	पूर्ण

	nbd->recv_workq = alloc_workqueue("knbd%d-recv",
					  WQ_MEM_RECLAIM | WQ_HIGHPRI |
					  WQ_UNBOUND, 0, nbd->index);
	अगर (!nbd->recv_workq) अणु
		dev_err(disk_to_dev(nbd->disk), "Could not allocate knbd recv work queue.\n");
		वापस -ENOMEM;
	पूर्ण

	blk_mq_update_nr_hw_queues(&nbd->tag_set, config->num_connections);
	nbd->task_recv = current;

	nbd_parse_flags(nbd);

	error = device_create_file(disk_to_dev(nbd->disk), &pid_attr);
	अगर (error) अणु
		dev_err(disk_to_dev(nbd->disk), "device_create_file failed!\n");
		वापस error;
	पूर्ण
	set_bit(NBD_RT_HAS_PID_खाता, &config->runसमय_flags);

	nbd_dev_dbg_init(nbd);
	क्रम (i = 0; i < num_connections; i++) अणु
		काष्ठा recv_thपढ़ो_args *args;

		args = kzalloc(माप(*args), GFP_KERNEL);
		अगर (!args) अणु
			sock_shutकरोwn(nbd);
			/*
			 * If num_connections is m (2 < m),
			 * and NO.1 ~ NO.n(1 < n < m) kzallocs are successful.
			 * But NO.(n + 1) failed. We still have n recv thपढ़ोs.
			 * So, add flush_workqueue here to prevent recv thपढ़ोs
			 * dropping the last config_refs and trying to destroy
			 * the workqueue from inside the workqueue.
			 */
			अगर (i)
				flush_workqueue(nbd->recv_workq);
			वापस -ENOMEM;
		पूर्ण
		sk_set_meदो_स्मृति(config->socks[i]->sock->sk);
		अगर (nbd->tag_set.समयout)
			config->socks[i]->sock->sk->sk_sndसमयo =
				nbd->tag_set.समयout;
		atomic_inc(&config->recv_thपढ़ोs);
		refcount_inc(&nbd->config_refs);
		INIT_WORK(&args->work, recv_work);
		args->nbd = nbd;
		args->index = i;
		queue_work(nbd->recv_workq, &args->work);
	पूर्ण
	वापस nbd_set_size(nbd, config->bytesize, config->blksize);
पूर्ण

अटल पूर्णांक nbd_start_device_ioctl(काष्ठा nbd_device *nbd, काष्ठा block_device *bdev)
अणु
	काष्ठा nbd_config *config = nbd->config;
	पूर्णांक ret;

	ret = nbd_start_device(nbd);
	अगर (ret)
		वापस ret;

	अगर (max_part)
		set_bit(GD_NEED_PART_SCAN, &nbd->disk->state);
	mutex_unlock(&nbd->config_lock);
	ret = रुको_event_पूर्णांकerruptible(config->recv_wq,
					 atomic_पढ़ो(&config->recv_thपढ़ोs) == 0);
	अगर (ret)
		sock_shutकरोwn(nbd);
	flush_workqueue(nbd->recv_workq);

	mutex_lock(&nbd->config_lock);
	nbd_bdev_reset(bdev);
	/* user requested, ignore socket errors */
	अगर (test_bit(NBD_RT_DISCONNECT_REQUESTED, &config->runसमय_flags))
		ret = 0;
	अगर (test_bit(NBD_RT_TIMEDOUT, &config->runसमय_flags))
		ret = -ETIMEDOUT;
	वापस ret;
पूर्ण

अटल व्योम nbd_clear_sock_ioctl(काष्ठा nbd_device *nbd,
				 काष्ठा block_device *bdev)
अणु
	sock_shutकरोwn(nbd);
	__invalidate_device(bdev, true);
	nbd_bdev_reset(bdev);
	अगर (test_and_clear_bit(NBD_RT_HAS_CONFIG_REF,
			       &nbd->config->runसमय_flags))
		nbd_config_put(nbd);
पूर्ण

अटल व्योम nbd_set_cmd_समयout(काष्ठा nbd_device *nbd, u64 समयout)
अणु
	nbd->tag_set.समयout = समयout * HZ;
	अगर (समयout)
		blk_queue_rq_समयout(nbd->disk->queue, समयout * HZ);
	अन्यथा
		blk_queue_rq_समयout(nbd->disk->queue, 30 * HZ);
पूर्ण

/* Must be called with config_lock held */
अटल पूर्णांक __nbd_ioctl(काष्ठा block_device *bdev, काष्ठा nbd_device *nbd,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा nbd_config *config = nbd->config;

	चयन (cmd) अणु
	हाल NBD_DISCONNECT:
		वापस nbd_disconnect(nbd);
	हाल NBD_CLEAR_SOCK:
		nbd_clear_sock_ioctl(nbd, bdev);
		वापस 0;
	हाल NBD_SET_SOCK:
		वापस nbd_add_socket(nbd, arg, false);
	हाल NBD_SET_BLKSIZE:
		वापस nbd_set_size(nbd, config->bytesize, arg);
	हाल NBD_SET_SIZE:
		वापस nbd_set_size(nbd, arg, config->blksize);
	हाल NBD_SET_SIZE_BLOCKS:
		वापस nbd_set_size(nbd, arg * config->blksize,
				    config->blksize);
	हाल NBD_SET_TIMEOUT:
		nbd_set_cmd_समयout(nbd, arg);
		वापस 0;

	हाल NBD_SET_FLAGS:
		config->flags = arg;
		वापस 0;
	हाल NBD_DO_IT:
		वापस nbd_start_device_ioctl(nbd, bdev);
	हाल NBD_CLEAR_QUE:
		/*
		 * This is क्रम compatibility only.  The queue is always cleared
		 * by NBD_DO_IT or NBD_CLEAR_SOCK.
		 */
		वापस 0;
	हाल NBD_PRINT_DEBUG:
		/*
		 * For compatibility only, we no दीर्घer keep a list of
		 * outstanding requests.
		 */
		वापस 0;
	पूर्ण
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक nbd_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा nbd_device *nbd = bdev->bd_disk->निजी_data;
	काष्ठा nbd_config *config = nbd->config;
	पूर्णांक error = -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	/* The block layer will pass back some non-nbd ioctls in हाल we have
	 * special handling क्रम them, but we करोn't so just वापस an error.
	 */
	अगर (_IOC_TYPE(cmd) != 0xab)
		वापस -EINVAL;

	mutex_lock(&nbd->config_lock);

	/* Don't allow ioctl operations on a nbd device that was created with
	 * netlink, unless it's DISCONNECT or CLEAR_SOCK, which are fine.
	 */
	अगर (!test_bit(NBD_RT_BOUND, &config->runसमय_flags) ||
	    (cmd == NBD_DISCONNECT || cmd == NBD_CLEAR_SOCK))
		error = __nbd_ioctl(bdev, nbd, cmd, arg);
	अन्यथा
		dev_err(nbd_to_dev(nbd), "Cannot use ioctl interface on a netlink controlled device.\n");
	mutex_unlock(&nbd->config_lock);
	वापस error;
पूर्ण

अटल काष्ठा nbd_config *nbd_alloc_config(व्योम)
अणु
	काष्ठा nbd_config *config;

	config = kzalloc(माप(काष्ठा nbd_config), GFP_NOFS);
	अगर (!config)
		वापस शून्य;
	atomic_set(&config->recv_thपढ़ोs, 0);
	init_रुकोqueue_head(&config->recv_wq);
	init_रुकोqueue_head(&config->conn_रुको);
	config->blksize = NBD_DEF_BLKSIZE;
	atomic_set(&config->live_connections, 0);
	try_module_get(THIS_MODULE);
	वापस config;
पूर्ण

अटल पूर्णांक nbd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा nbd_device *nbd;
	पूर्णांक ret = 0;

	mutex_lock(&nbd_index_mutex);
	nbd = bdev->bd_disk->निजी_data;
	अगर (!nbd) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण
	अगर (!refcount_inc_not_zero(&nbd->refs)) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण
	अगर (!refcount_inc_not_zero(&nbd->config_refs)) अणु
		काष्ठा nbd_config *config;

		mutex_lock(&nbd->config_lock);
		अगर (refcount_inc_not_zero(&nbd->config_refs)) अणु
			mutex_unlock(&nbd->config_lock);
			जाओ out;
		पूर्ण
		config = nbd->config = nbd_alloc_config();
		अगर (!config) अणु
			ret = -ENOMEM;
			mutex_unlock(&nbd->config_lock);
			जाओ out;
		पूर्ण
		refcount_set(&nbd->config_refs, 1);
		refcount_inc(&nbd->refs);
		mutex_unlock(&nbd->config_lock);
		अगर (max_part)
			set_bit(GD_NEED_PART_SCAN, &bdev->bd_disk->state);
	पूर्ण अन्यथा अगर (nbd_disconnected(nbd->config)) अणु
		अगर (max_part)
			set_bit(GD_NEED_PART_SCAN, &bdev->bd_disk->state);
	पूर्ण
out:
	mutex_unlock(&nbd_index_mutex);
	वापस ret;
पूर्ण

अटल व्योम nbd_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा nbd_device *nbd = disk->निजी_data;

	अगर (test_bit(NBD_RT_DISCONNECT_ON_CLOSE, &nbd->config->runसमय_flags) &&
			disk->part0->bd_खोलोers == 0)
		nbd_disconnect_and_put(nbd);

	nbd_config_put(nbd);
	nbd_put(nbd);
पूर्ण

अटल स्थिर काष्ठा block_device_operations nbd_fops =
अणु
	.owner =	THIS_MODULE,
	.खोलो =		nbd_खोलो,
	.release =	nbd_release,
	.ioctl =	nbd_ioctl,
	.compat_ioctl =	nbd_ioctl,
पूर्ण;

#अगर IS_ENABLED(CONFIG_DEBUG_FS)

अटल पूर्णांक nbd_dbg_tasks_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा nbd_device *nbd = s->निजी;

	अगर (nbd->task_recv)
		seq_म_लिखो(s, "recv: %d\n", task_pid_nr(nbd->task_recv));

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(nbd_dbg_tasks);

अटल पूर्णांक nbd_dbg_flags_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा nbd_device *nbd = s->निजी;
	u32 flags = nbd->config->flags;

	seq_म_लिखो(s, "Hex: 0x%08x\n\n", flags);

	seq_माला_दो(s, "Known flags:\n");

	अगर (flags & NBD_FLAG_HAS_FLAGS)
		seq_माला_दो(s, "NBD_FLAG_HAS_FLAGS\n");
	अगर (flags & NBD_FLAG_READ_ONLY)
		seq_माला_दो(s, "NBD_FLAG_READ_ONLY\n");
	अगर (flags & NBD_FLAG_SEND_FLUSH)
		seq_माला_दो(s, "NBD_FLAG_SEND_FLUSH\n");
	अगर (flags & NBD_FLAG_SEND_FUA)
		seq_माला_दो(s, "NBD_FLAG_SEND_FUA\n");
	अगर (flags & NBD_FLAG_SEND_TRIM)
		seq_माला_दो(s, "NBD_FLAG_SEND_TRIM\n");

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(nbd_dbg_flags);

अटल पूर्णांक nbd_dev_dbg_init(काष्ठा nbd_device *nbd)
अणु
	काष्ठा dentry *dir;
	काष्ठा nbd_config *config = nbd->config;

	अगर (!nbd_dbg_dir)
		वापस -EIO;

	dir = debugfs_create_dir(nbd_name(nbd), nbd_dbg_dir);
	अगर (!dir) अणु
		dev_err(nbd_to_dev(nbd), "Failed to create debugfs dir for '%s'\n",
			nbd_name(nbd));
		वापस -EIO;
	पूर्ण
	config->dbg_dir = dir;

	debugfs_create_file("tasks", 0444, dir, nbd, &nbd_dbg_tasks_fops);
	debugfs_create_u64("size_bytes", 0444, dir, &config->bytesize);
	debugfs_create_u32("timeout", 0444, dir, &nbd->tag_set.समयout);
	debugfs_create_u64("blocksize", 0444, dir, &config->blksize);
	debugfs_create_file("flags", 0444, dir, nbd, &nbd_dbg_flags_fops);

	वापस 0;
पूर्ण

अटल व्योम nbd_dev_dbg_बंद(काष्ठा nbd_device *nbd)
अणु
	debugfs_हटाओ_recursive(nbd->config->dbg_dir);
पूर्ण

अटल पूर्णांक nbd_dbg_init(व्योम)
अणु
	काष्ठा dentry *dbg_dir;

	dbg_dir = debugfs_create_dir("nbd", शून्य);
	अगर (!dbg_dir)
		वापस -EIO;

	nbd_dbg_dir = dbg_dir;

	वापस 0;
पूर्ण

अटल व्योम nbd_dbg_बंद(व्योम)
अणु
	debugfs_हटाओ_recursive(nbd_dbg_dir);
पूर्ण

#अन्यथा  /* IS_ENABLED(CONFIG_DEBUG_FS) */

अटल पूर्णांक nbd_dev_dbg_init(काष्ठा nbd_device *nbd)
अणु
	वापस 0;
पूर्ण

अटल व्योम nbd_dev_dbg_बंद(काष्ठा nbd_device *nbd)
अणु
पूर्ण

अटल पूर्णांक nbd_dbg_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम nbd_dbg_बंद(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक nbd_init_request(काष्ठा blk_mq_tag_set *set, काष्ठा request *rq,
			    अचिन्हित पूर्णांक hctx_idx, अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा nbd_cmd *cmd = blk_mq_rq_to_pdu(rq);
	cmd->nbd = set->driver_data;
	cmd->flags = 0;
	mutex_init(&cmd->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops nbd_mq_ops = अणु
	.queue_rq	= nbd_queue_rq,
	.complete	= nbd_complete_rq,
	.init_request	= nbd_init_request,
	.समयout	= nbd_xmit_समयout,
पूर्ण;

अटल पूर्णांक nbd_dev_add(पूर्णांक index)
अणु
	काष्ठा nbd_device *nbd;
	काष्ठा gendisk *disk;
	काष्ठा request_queue *q;
	पूर्णांक err = -ENOMEM;

	nbd = kzalloc(माप(काष्ठा nbd_device), GFP_KERNEL);
	अगर (!nbd)
		जाओ out;

	disk = alloc_disk(1 << part_shअगरt);
	अगर (!disk)
		जाओ out_मुक्त_nbd;

	अगर (index >= 0) अणु
		err = idr_alloc(&nbd_index_idr, nbd, index, index + 1,
				GFP_KERNEL);
		अगर (err == -ENOSPC)
			err = -EEXIST;
	पूर्ण अन्यथा अणु
		err = idr_alloc(&nbd_index_idr, nbd, 0, 0, GFP_KERNEL);
		अगर (err >= 0)
			index = err;
	पूर्ण
	अगर (err < 0)
		जाओ out_मुक्त_disk;

	nbd->index = index;
	nbd->disk = disk;
	nbd->tag_set.ops = &nbd_mq_ops;
	nbd->tag_set.nr_hw_queues = 1;
	nbd->tag_set.queue_depth = 128;
	nbd->tag_set.numa_node = NUMA_NO_NODE;
	nbd->tag_set.cmd_size = माप(काष्ठा nbd_cmd);
	nbd->tag_set.flags = BLK_MQ_F_SHOULD_MERGE |
		BLK_MQ_F_BLOCKING;
	nbd->tag_set.driver_data = nbd;
	nbd->destroy_complete = शून्य;

	err = blk_mq_alloc_tag_set(&nbd->tag_set);
	अगर (err)
		जाओ out_मुक्त_idr;

	q = blk_mq_init_queue(&nbd->tag_set);
	अगर (IS_ERR(q)) अणु
		err = PTR_ERR(q);
		जाओ out_मुक्त_tags;
	पूर्ण
	disk->queue = q;

	/*
	 * Tell the block layer that we are not a rotational device
	 */
	blk_queue_flag_set(QUEUE_FLAG_NONROT, disk->queue);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, disk->queue);
	disk->queue->limits.discard_granularity = 0;
	disk->queue->limits.discard_alignment = 0;
	blk_queue_max_discard_sectors(disk->queue, 0);
	blk_queue_max_segment_size(disk->queue, अच_पूर्णांक_उच्च);
	blk_queue_max_segments(disk->queue, अच_लघु_उच्च);
	blk_queue_max_hw_sectors(disk->queue, 65536);
	disk->queue->limits.max_sectors = 256;

	mutex_init(&nbd->config_lock);
	refcount_set(&nbd->config_refs, 0);
	refcount_set(&nbd->refs, 1);
	INIT_LIST_HEAD(&nbd->list);
	disk->major = NBD_MAJOR;
	disk->first_minor = index << part_shअगरt;
	disk->fops = &nbd_fops;
	disk->निजी_data = nbd;
	प्र_लिखो(disk->disk_name, "nbd%d", index);
	add_disk(disk);
	nbd_total_devices++;
	वापस index;

out_मुक्त_tags:
	blk_mq_मुक्त_tag_set(&nbd->tag_set);
out_मुक्त_idr:
	idr_हटाओ(&nbd_index_idr, index);
out_मुक्त_disk:
	put_disk(disk);
out_मुक्त_nbd:
	kमुक्त(nbd);
out:
	वापस err;
पूर्ण

अटल पूर्णांक find_मुक्त_cb(पूर्णांक id, व्योम *ptr, व्योम *data)
अणु
	काष्ठा nbd_device *nbd = ptr;
	काष्ठा nbd_device **found = data;

	अगर (!refcount_पढ़ो(&nbd->config_refs)) अणु
		*found = nbd;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Netlink पूर्णांकerface. */
अटल स्थिर काष्ठा nla_policy nbd_attr_policy[NBD_ATTR_MAX + 1] = अणु
	[NBD_ATTR_INDEX]		=	अणु .type = NLA_U32 पूर्ण,
	[NBD_ATTR_SIZE_BYTES]		=	अणु .type = NLA_U64 पूर्ण,
	[NBD_ATTR_BLOCK_SIZE_BYTES]	=	अणु .type = NLA_U64 पूर्ण,
	[NBD_ATTR_TIMEOUT]		=	अणु .type = NLA_U64 पूर्ण,
	[NBD_ATTR_SERVER_FLAGS]		=	अणु .type = NLA_U64 पूर्ण,
	[NBD_ATTR_CLIENT_FLAGS]		=	अणु .type = NLA_U64 पूर्ण,
	[NBD_ATTR_SOCKETS]		=	अणु .type = NLA_NESTEDपूर्ण,
	[NBD_ATTR_DEAD_CONN_TIMEOUT]	=	अणु .type = NLA_U64 पूर्ण,
	[NBD_ATTR_DEVICE_LIST]		=	अणु .type = NLA_NESTEDपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy nbd_sock_policy[NBD_SOCK_MAX + 1] = अणु
	[NBD_SOCK_FD]			=	अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/* We करोn't use this right now since we don't parse the incoming list, but we
 * still want it here so userspace knows what to expect.
 */
अटल स्थिर काष्ठा nla_policy __attribute__((unused))
nbd_device_policy[NBD_DEVICE_ATTR_MAX + 1] = अणु
	[NBD_DEVICE_INDEX]		=	अणु .type = NLA_U32 पूर्ण,
	[NBD_DEVICE_CONNECTED]		=	अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक nbd_genl_size_set(काष्ठा genl_info *info, काष्ठा nbd_device *nbd)
अणु
	काष्ठा nbd_config *config = nbd->config;
	u64 bsize = config->blksize;
	u64 bytes = config->bytesize;

	अगर (info->attrs[NBD_ATTR_SIZE_BYTES])
		bytes = nla_get_u64(info->attrs[NBD_ATTR_SIZE_BYTES]);

	अगर (info->attrs[NBD_ATTR_BLOCK_SIZE_BYTES])
		bsize = nla_get_u64(info->attrs[NBD_ATTR_BLOCK_SIZE_BYTES]);

	अगर (bytes != config->bytesize || bsize != config->blksize)
		वापस nbd_set_size(nbd, bytes, bsize);
	वापस 0;
पूर्ण

अटल पूर्णांक nbd_genl_connect(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	DECLARE_COMPLETION_ONSTACK(destroy_complete);
	काष्ठा nbd_device *nbd = शून्य;
	काष्ठा nbd_config *config;
	पूर्णांक index = -1;
	पूर्णांक ret;
	bool put_dev = false;

	अगर (!netlink_capable(skb, CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (info->attrs[NBD_ATTR_INDEX])
		index = nla_get_u32(info->attrs[NBD_ATTR_INDEX]);
	अगर (!info->attrs[NBD_ATTR_SOCKETS]) अणु
		prपूर्णांकk(KERN_ERR "nbd: must specify at least one socket\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!info->attrs[NBD_ATTR_SIZE_BYTES]) अणु
		prपूर्णांकk(KERN_ERR "nbd: must specify a size in bytes for the device\n");
		वापस -EINVAL;
	पूर्ण
again:
	mutex_lock(&nbd_index_mutex);
	अगर (index == -1) अणु
		ret = idr_क्रम_each(&nbd_index_idr, &find_मुक्त_cb, &nbd);
		अगर (ret == 0) अणु
			पूर्णांक new_index;
			new_index = nbd_dev_add(-1);
			अगर (new_index < 0) अणु
				mutex_unlock(&nbd_index_mutex);
				prपूर्णांकk(KERN_ERR "nbd: failed to add new device\n");
				वापस new_index;
			पूर्ण
			nbd = idr_find(&nbd_index_idr, new_index);
		पूर्ण
	पूर्ण अन्यथा अणु
		nbd = idr_find(&nbd_index_idr, index);
		अगर (!nbd) अणु
			ret = nbd_dev_add(index);
			अगर (ret < 0) अणु
				mutex_unlock(&nbd_index_mutex);
				prपूर्णांकk(KERN_ERR "nbd: failed to add new device\n");
				वापस ret;
			पूर्ण
			nbd = idr_find(&nbd_index_idr, index);
		पूर्ण
	पूर्ण
	अगर (!nbd) अणु
		prपूर्णांकk(KERN_ERR "nbd: couldn't find device at index %d\n",
		       index);
		mutex_unlock(&nbd_index_mutex);
		वापस -EINVAL;
	पूर्ण

	अगर (test_bit(NBD_DESTROY_ON_DISCONNECT, &nbd->flags) &&
	    test_bit(NBD_DISCONNECT_REQUESTED, &nbd->flags)) अणु
		nbd->destroy_complete = &destroy_complete;
		mutex_unlock(&nbd_index_mutex);

		/* Wait untill the the nbd stuff is totally destroyed */
		रुको_क्रम_completion(&destroy_complete);
		जाओ again;
	पूर्ण

	अगर (!refcount_inc_not_zero(&nbd->refs)) अणु
		mutex_unlock(&nbd_index_mutex);
		अगर (index == -1)
			जाओ again;
		prपूर्णांकk(KERN_ERR "nbd: device at index %d is going down\n",
		       index);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(&nbd_index_mutex);

	mutex_lock(&nbd->config_lock);
	अगर (refcount_पढ़ो(&nbd->config_refs)) अणु
		mutex_unlock(&nbd->config_lock);
		nbd_put(nbd);
		अगर (index == -1)
			जाओ again;
		prपूर्णांकk(KERN_ERR "nbd: nbd%d already in use\n", index);
		वापस -EBUSY;
	पूर्ण
	अगर (WARN_ON(nbd->config)) अणु
		mutex_unlock(&nbd->config_lock);
		nbd_put(nbd);
		वापस -EINVAL;
	पूर्ण
	config = nbd->config = nbd_alloc_config();
	अगर (!nbd->config) अणु
		mutex_unlock(&nbd->config_lock);
		nbd_put(nbd);
		prपूर्णांकk(KERN_ERR "nbd: couldn't allocate config\n");
		वापस -ENOMEM;
	पूर्ण
	refcount_set(&nbd->config_refs, 1);
	set_bit(NBD_RT_BOUND, &config->runसमय_flags);

	ret = nbd_genl_size_set(info, nbd);
	अगर (ret)
		जाओ out;

	अगर (info->attrs[NBD_ATTR_TIMEOUT])
		nbd_set_cmd_समयout(nbd,
				    nla_get_u64(info->attrs[NBD_ATTR_TIMEOUT]));
	अगर (info->attrs[NBD_ATTR_DEAD_CONN_TIMEOUT]) अणु
		config->dead_conn_समयout =
			nla_get_u64(info->attrs[NBD_ATTR_DEAD_CONN_TIMEOUT]);
		config->dead_conn_समयout *= HZ;
	पूर्ण
	अगर (info->attrs[NBD_ATTR_SERVER_FLAGS])
		config->flags =
			nla_get_u64(info->attrs[NBD_ATTR_SERVER_FLAGS]);
	अगर (info->attrs[NBD_ATTR_CLIENT_FLAGS]) अणु
		u64 flags = nla_get_u64(info->attrs[NBD_ATTR_CLIENT_FLAGS]);
		अगर (flags & NBD_CFLAG_DESTROY_ON_DISCONNECT) अणु
			/*
			 * We have 1 ref to keep the device around, and then 1
			 * ref क्रम our current operation here, which will be
			 * inherited by the config.  If we alपढ़ोy have
			 * DESTROY_ON_DISCONNECT set then we know we करोn't have
			 * that extra ref alपढ़ोy held so we करोn't need the
			 * put_dev.
			 */
			अगर (!test_and_set_bit(NBD_DESTROY_ON_DISCONNECT,
					      &nbd->flags))
				put_dev = true;
		पूर्ण अन्यथा अणु
			अगर (test_and_clear_bit(NBD_DESTROY_ON_DISCONNECT,
					       &nbd->flags))
				refcount_inc(&nbd->refs);
		पूर्ण
		अगर (flags & NBD_CFLAG_DISCONNECT_ON_CLOSE) अणु
			set_bit(NBD_RT_DISCONNECT_ON_CLOSE,
				&config->runसमय_flags);
		पूर्ण
	पूर्ण

	अगर (info->attrs[NBD_ATTR_SOCKETS]) अणु
		काष्ठा nlattr *attr;
		पूर्णांक rem, fd;

		nla_क्रम_each_nested(attr, info->attrs[NBD_ATTR_SOCKETS],
				    rem) अणु
			काष्ठा nlattr *socks[NBD_SOCK_MAX+1];

			अगर (nla_type(attr) != NBD_SOCK_ITEM) अणु
				prपूर्णांकk(KERN_ERR "nbd: socks must be embedded in a SOCK_ITEM attr\n");
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			ret = nla_parse_nested_deprecated(socks, NBD_SOCK_MAX,
							  attr,
							  nbd_sock_policy,
							  info->extack);
			अगर (ret != 0) अणु
				prपूर्णांकk(KERN_ERR "nbd: error processing sock list\n");
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (!socks[NBD_SOCK_FD])
				जारी;
			fd = (पूर्णांक)nla_get_u32(socks[NBD_SOCK_FD]);
			ret = nbd_add_socket(nbd, fd, true);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण
	ret = nbd_start_device(nbd);
out:
	mutex_unlock(&nbd->config_lock);
	अगर (!ret) अणु
		set_bit(NBD_RT_HAS_CONFIG_REF, &config->runसमय_flags);
		refcount_inc(&nbd->config_refs);
		nbd_connect_reply(info, nbd->index);
	पूर्ण
	nbd_config_put(nbd);
	अगर (put_dev)
		nbd_put(nbd);
	वापस ret;
पूर्ण

अटल व्योम nbd_disconnect_and_put(काष्ठा nbd_device *nbd)
अणु
	mutex_lock(&nbd->config_lock);
	nbd_disconnect(nbd);
	nbd_clear_sock(nbd);
	mutex_unlock(&nbd->config_lock);
	/*
	 * Make sure recv thपढ़ो has finished, so it करोes not drop the last
	 * config ref and try to destroy the workqueue from inside the work
	 * queue.
	 */
	अगर (nbd->recv_workq)
		flush_workqueue(nbd->recv_workq);
	अगर (test_and_clear_bit(NBD_RT_HAS_CONFIG_REF,
			       &nbd->config->runसमय_flags))
		nbd_config_put(nbd);
पूर्ण

अटल पूर्णांक nbd_genl_disconnect(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nbd_device *nbd;
	पूर्णांक index;

	अगर (!netlink_capable(skb, CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!info->attrs[NBD_ATTR_INDEX]) अणु
		prपूर्णांकk(KERN_ERR "nbd: must specify an index to disconnect\n");
		वापस -EINVAL;
	पूर्ण
	index = nla_get_u32(info->attrs[NBD_ATTR_INDEX]);
	mutex_lock(&nbd_index_mutex);
	nbd = idr_find(&nbd_index_idr, index);
	अगर (!nbd) अणु
		mutex_unlock(&nbd_index_mutex);
		prपूर्णांकk(KERN_ERR "nbd: couldn't find device at index %d\n",
		       index);
		वापस -EINVAL;
	पूर्ण
	अगर (!refcount_inc_not_zero(&nbd->refs)) अणु
		mutex_unlock(&nbd_index_mutex);
		prपूर्णांकk(KERN_ERR "nbd: device at index %d is going down\n",
		       index);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(&nbd_index_mutex);
	अगर (!refcount_inc_not_zero(&nbd->config_refs))
		जाओ put_nbd;
	nbd_disconnect_and_put(nbd);
	nbd_config_put(nbd);
put_nbd:
	nbd_put(nbd);
	वापस 0;
पूर्ण

अटल पूर्णांक nbd_genl_reconfigure(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nbd_device *nbd = शून्य;
	काष्ठा nbd_config *config;
	पूर्णांक index;
	पूर्णांक ret = 0;
	bool put_dev = false;

	अगर (!netlink_capable(skb, CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!info->attrs[NBD_ATTR_INDEX]) अणु
		prपूर्णांकk(KERN_ERR "nbd: must specify a device to reconfigure\n");
		वापस -EINVAL;
	पूर्ण
	index = nla_get_u32(info->attrs[NBD_ATTR_INDEX]);
	mutex_lock(&nbd_index_mutex);
	nbd = idr_find(&nbd_index_idr, index);
	अगर (!nbd) अणु
		mutex_unlock(&nbd_index_mutex);
		prपूर्णांकk(KERN_ERR "nbd: couldn't find a device at index %d\n",
		       index);
		वापस -EINVAL;
	पूर्ण
	अगर (!refcount_inc_not_zero(&nbd->refs)) अणु
		mutex_unlock(&nbd_index_mutex);
		prपूर्णांकk(KERN_ERR "nbd: device at index %d is going down\n",
		       index);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(&nbd_index_mutex);

	अगर (!refcount_inc_not_zero(&nbd->config_refs)) अणु
		dev_err(nbd_to_dev(nbd),
			"not configured, cannot reconfigure\n");
		nbd_put(nbd);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&nbd->config_lock);
	config = nbd->config;
	अगर (!test_bit(NBD_RT_BOUND, &config->runसमय_flags) ||
	    !nbd->task_recv) अणु
		dev_err(nbd_to_dev(nbd),
			"not configured, cannot reconfigure\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = nbd_genl_size_set(info, nbd);
	अगर (ret)
		जाओ out;

	अगर (info->attrs[NBD_ATTR_TIMEOUT])
		nbd_set_cmd_समयout(nbd,
				    nla_get_u64(info->attrs[NBD_ATTR_TIMEOUT]));
	अगर (info->attrs[NBD_ATTR_DEAD_CONN_TIMEOUT]) अणु
		config->dead_conn_समयout =
			nla_get_u64(info->attrs[NBD_ATTR_DEAD_CONN_TIMEOUT]);
		config->dead_conn_समयout *= HZ;
	पूर्ण
	अगर (info->attrs[NBD_ATTR_CLIENT_FLAGS]) अणु
		u64 flags = nla_get_u64(info->attrs[NBD_ATTR_CLIENT_FLAGS]);
		अगर (flags & NBD_CFLAG_DESTROY_ON_DISCONNECT) अणु
			अगर (!test_and_set_bit(NBD_DESTROY_ON_DISCONNECT,
					      &nbd->flags))
				put_dev = true;
		पूर्ण अन्यथा अणु
			अगर (test_and_clear_bit(NBD_DESTROY_ON_DISCONNECT,
					       &nbd->flags))
				refcount_inc(&nbd->refs);
		पूर्ण

		अगर (flags & NBD_CFLAG_DISCONNECT_ON_CLOSE) अणु
			set_bit(NBD_RT_DISCONNECT_ON_CLOSE,
					&config->runसमय_flags);
		पूर्ण अन्यथा अणु
			clear_bit(NBD_RT_DISCONNECT_ON_CLOSE,
					&config->runसमय_flags);
		पूर्ण
	पूर्ण

	अगर (info->attrs[NBD_ATTR_SOCKETS]) अणु
		काष्ठा nlattr *attr;
		पूर्णांक rem, fd;

		nla_क्रम_each_nested(attr, info->attrs[NBD_ATTR_SOCKETS],
				    rem) अणु
			काष्ठा nlattr *socks[NBD_SOCK_MAX+1];

			अगर (nla_type(attr) != NBD_SOCK_ITEM) अणु
				prपूर्णांकk(KERN_ERR "nbd: socks must be embedded in a SOCK_ITEM attr\n");
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			ret = nla_parse_nested_deprecated(socks, NBD_SOCK_MAX,
							  attr,
							  nbd_sock_policy,
							  info->extack);
			अगर (ret != 0) अणु
				prपूर्णांकk(KERN_ERR "nbd: error processing sock list\n");
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (!socks[NBD_SOCK_FD])
				जारी;
			fd = (पूर्णांक)nla_get_u32(socks[NBD_SOCK_FD]);
			ret = nbd_reconnect_socket(nbd, fd);
			अगर (ret) अणु
				अगर (ret == -ENOSPC)
					ret = 0;
				जाओ out;
			पूर्ण
			dev_info(nbd_to_dev(nbd), "reconnected socket\n");
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&nbd->config_lock);
	nbd_config_put(nbd);
	nbd_put(nbd);
	अगर (put_dev)
		nbd_put(nbd);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops nbd_connect_genl_ops[] = अणु
	अणु
		.cmd	= NBD_CMD_CONNECT,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= nbd_genl_connect,
	पूर्ण,
	अणु
		.cmd	= NBD_CMD_DISCONNECT,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= nbd_genl_disconnect,
	पूर्ण,
	अणु
		.cmd	= NBD_CMD_RECONFIGURE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= nbd_genl_reconfigure,
	पूर्ण,
	अणु
		.cmd	= NBD_CMD_STATUS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= nbd_genl_status,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group nbd_mcast_grps[] = अणु
	अणु .name = NBD_GENL_MCAST_GROUP_NAME, पूर्ण,
पूर्ण;

अटल काष्ठा genl_family nbd_genl_family __ro_after_init = अणु
	.hdrsize	= 0,
	.name		= NBD_GENL_FAMILY_NAME,
	.version	= NBD_GENL_VERSION,
	.module		= THIS_MODULE,
	.small_ops	= nbd_connect_genl_ops,
	.n_small_ops	= ARRAY_SIZE(nbd_connect_genl_ops),
	.maxattr	= NBD_ATTR_MAX,
	.policy = nbd_attr_policy,
	.mcgrps		= nbd_mcast_grps,
	.n_mcgrps	= ARRAY_SIZE(nbd_mcast_grps),
पूर्ण;

अटल पूर्णांक populate_nbd_status(काष्ठा nbd_device *nbd, काष्ठा sk_buff *reply)
अणु
	काष्ठा nlattr *dev_opt;
	u8 connected = 0;
	पूर्णांक ret;

	/* This is a little racey, but क्रम status it's ok.  The
	 * reason we करोn't take a ref here is because we can't
	 * take a ref in the index == -1 हाल as we would need
	 * to put under the nbd_index_mutex, which could
	 * deadlock अगर we are configured to हटाओ ourselves
	 * once we're disconnected.
	 */
	अगर (refcount_पढ़ो(&nbd->config_refs))
		connected = 1;
	dev_opt = nla_nest_start_noflag(reply, NBD_DEVICE_ITEM);
	अगर (!dev_opt)
		वापस -EMSGSIZE;
	ret = nla_put_u32(reply, NBD_DEVICE_INDEX, nbd->index);
	अगर (ret)
		वापस -EMSGSIZE;
	ret = nla_put_u8(reply, NBD_DEVICE_CONNECTED,
			 connected);
	अगर (ret)
		वापस -EMSGSIZE;
	nla_nest_end(reply, dev_opt);
	वापस 0;
पूर्ण

अटल पूर्णांक status_cb(पूर्णांक id, व्योम *ptr, व्योम *data)
अणु
	काष्ठा nbd_device *nbd = ptr;
	वापस populate_nbd_status(nbd, (काष्ठा sk_buff *)data);
पूर्ण

अटल पूर्णांक nbd_genl_status(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *dev_list;
	काष्ठा sk_buff *reply;
	व्योम *reply_head;
	माप_प्रकार msg_size;
	पूर्णांक index = -1;
	पूर्णांक ret = -ENOMEM;

	अगर (info->attrs[NBD_ATTR_INDEX])
		index = nla_get_u32(info->attrs[NBD_ATTR_INDEX]);

	mutex_lock(&nbd_index_mutex);

	msg_size = nla_total_size(nla_attr_size(माप(u32)) +
				  nla_attr_size(माप(u8)));
	msg_size *= (index == -1) ? nbd_total_devices : 1;

	reply = genlmsg_new(msg_size, GFP_KERNEL);
	अगर (!reply)
		जाओ out;
	reply_head = genlmsg_put_reply(reply, info, &nbd_genl_family, 0,
				       NBD_CMD_STATUS);
	अगर (!reply_head) अणु
		nlmsg_मुक्त(reply);
		जाओ out;
	पूर्ण

	dev_list = nla_nest_start_noflag(reply, NBD_ATTR_DEVICE_LIST);
	अगर (index == -1) अणु
		ret = idr_क्रम_each(&nbd_index_idr, &status_cb, reply);
		अगर (ret) अणु
			nlmsg_मुक्त(reply);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा nbd_device *nbd;
		nbd = idr_find(&nbd_index_idr, index);
		अगर (nbd) अणु
			ret = populate_nbd_status(nbd, reply);
			अगर (ret) अणु
				nlmsg_मुक्त(reply);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	nla_nest_end(reply, dev_list);
	genlmsg_end(reply, reply_head);
	ret = genlmsg_reply(reply, info);
out:
	mutex_unlock(&nbd_index_mutex);
	वापस ret;
पूर्ण

अटल व्योम nbd_connect_reply(काष्ठा genl_info *info, पूर्णांक index)
अणु
	काष्ठा sk_buff *skb;
	व्योम *msg_head;
	पूर्णांक ret;

	skb = genlmsg_new(nla_total_size(माप(u32)), GFP_KERNEL);
	अगर (!skb)
		वापस;
	msg_head = genlmsg_put_reply(skb, info, &nbd_genl_family, 0,
				     NBD_CMD_CONNECT);
	अगर (!msg_head) अणु
		nlmsg_मुक्त(skb);
		वापस;
	पूर्ण
	ret = nla_put_u32(skb, NBD_ATTR_INDEX, index);
	अगर (ret) अणु
		nlmsg_मुक्त(skb);
		वापस;
	पूर्ण
	genlmsg_end(skb, msg_head);
	genlmsg_reply(skb, info);
पूर्ण

अटल व्योम nbd_mcast_index(पूर्णांक index)
अणु
	काष्ठा sk_buff *skb;
	व्योम *msg_head;
	पूर्णांक ret;

	skb = genlmsg_new(nla_total_size(माप(u32)), GFP_KERNEL);
	अगर (!skb)
		वापस;
	msg_head = genlmsg_put(skb, 0, 0, &nbd_genl_family, 0,
				     NBD_CMD_LINK_DEAD);
	अगर (!msg_head) अणु
		nlmsg_मुक्त(skb);
		वापस;
	पूर्ण
	ret = nla_put_u32(skb, NBD_ATTR_INDEX, index);
	अगर (ret) अणु
		nlmsg_मुक्त(skb);
		वापस;
	पूर्ण
	genlmsg_end(skb, msg_head);
	genlmsg_multicast(&nbd_genl_family, skb, 0, 0, GFP_KERNEL);
पूर्ण

अटल व्योम nbd_dead_link_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा link_dead_args *args = container_of(work, काष्ठा link_dead_args,
						   work);
	nbd_mcast_index(args->index);
	kमुक्त(args);
पूर्ण

अटल पूर्णांक __init nbd_init(व्योम)
अणु
	पूर्णांक i;

	BUILD_BUG_ON(माप(काष्ठा nbd_request) != 28);

	अगर (max_part < 0) अणु
		prपूर्णांकk(KERN_ERR "nbd: max_part must be >= 0\n");
		वापस -EINVAL;
	पूर्ण

	part_shअगरt = 0;
	अगर (max_part > 0) अणु
		part_shअगरt = fls(max_part);

		/*
		 * Adjust max_part according to part_shअगरt as it is exported
		 * to user space so that user can know the max number of
		 * partition kernel should be able to manage.
		 *
		 * Note that -1 is required because partition 0 is reserved
		 * क्रम the whole disk.
		 */
		max_part = (1UL << part_shअगरt) - 1;
	पूर्ण

	अगर ((1UL << part_shअगरt) > DISK_MAX_PARTS)
		वापस -EINVAL;

	अगर (nbds_max > 1UL << (MINORBITS - part_shअगरt))
		वापस -EINVAL;

	अगर (रेजिस्टर_blkdev(NBD_MAJOR, "nbd"))
		वापस -EIO;

	अगर (genl_रेजिस्टर_family(&nbd_genl_family)) अणु
		unरेजिस्टर_blkdev(NBD_MAJOR, "nbd");
		वापस -EINVAL;
	पूर्ण
	nbd_dbg_init();

	mutex_lock(&nbd_index_mutex);
	क्रम (i = 0; i < nbds_max; i++)
		nbd_dev_add(i);
	mutex_unlock(&nbd_index_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक nbd_निकास_cb(पूर्णांक id, व्योम *ptr, व्योम *data)
अणु
	काष्ठा list_head *list = (काष्ठा list_head *)data;
	काष्ठा nbd_device *nbd = ptr;

	list_add_tail(&nbd->list, list);
	वापस 0;
पूर्ण

अटल व्योम __निकास nbd_cleanup(व्योम)
अणु
	काष्ठा nbd_device *nbd;
	LIST_HEAD(del_list);

	nbd_dbg_बंद();

	mutex_lock(&nbd_index_mutex);
	idr_क्रम_each(&nbd_index_idr, &nbd_निकास_cb, &del_list);
	mutex_unlock(&nbd_index_mutex);

	जबतक (!list_empty(&del_list)) अणु
		nbd = list_first_entry(&del_list, काष्ठा nbd_device, list);
		list_del_init(&nbd->list);
		अगर (refcount_पढ़ो(&nbd->refs) != 1)
			prपूर्णांकk(KERN_ERR "nbd: possibly leaking a device\n");
		nbd_put(nbd);
	पूर्ण

	idr_destroy(&nbd_index_idr);
	genl_unरेजिस्टर_family(&nbd_genl_family);
	unरेजिस्टर_blkdev(NBD_MAJOR, "nbd");
पूर्ण

module_init(nbd_init);
module_निकास(nbd_cleanup);

MODULE_DESCRIPTION("Network Block Device");
MODULE_LICENSE("GPL");

module_param(nbds_max, पूर्णांक, 0444);
MODULE_PARM_DESC(nbds_max, "number of network block devices to initialize (default: 16)");
module_param(max_part, पूर्णांक, 0444);
MODULE_PARM_DESC(max_part, "number of partitions per device (default: 16)");
