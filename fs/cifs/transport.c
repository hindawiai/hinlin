<शैली गुरु>
/*
 *   fs/cअगरs/transport.c
 *
 *   Copyright (C) International Business Machines  Corp., 2002,2008
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *   Jeremy Allison (jra@samba.org) 2006.
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <linux/gfp.h>
#समावेश <linux/रुको.h>
#समावेश <linux/net.h>
#समावेश <linux/delay.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/tcp.h>
#समावेश <linux/bvec.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/mempool.h>
#समावेश <linux/sched/संकेत.स>
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "smb2proto.h"
#समावेश "smbdirect.h"

/* Max number of iovectors we can use off the stack when sending requests. */
#घोषणा CIFS_MAX_IOV_SIZE 8

व्योम
cअगरs_wake_up_task(काष्ठा mid_q_entry *mid)
अणु
	wake_up_process(mid->callback_data);
पूर्ण

काष्ठा mid_q_entry *
AllocMidQEntry(स्थिर काष्ठा smb_hdr *smb_buffer, काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा mid_q_entry *temp;

	अगर (server == शून्य) अणु
		cअगरs_dbg(VFS, "Null TCP session in AllocMidQEntry\n");
		वापस शून्य;
	पूर्ण

	temp = mempool_alloc(cअगरs_mid_poolp, GFP_NOFS);
	स_रखो(temp, 0, माप(काष्ठा mid_q_entry));
	kref_init(&temp->refcount);
	temp->mid = get_mid(smb_buffer);
	temp->pid = current->pid;
	temp->command = cpu_to_le16(smb_buffer->Command);
	cअगरs_dbg(FYI, "For smb_command %d\n", smb_buffer->Command);
	/*	करो_समय_लोofday(&temp->when_sent);*/ /* easier to use jअगरfies */
	/* when mid allocated can be beक्रमe when sent */
	temp->when_alloc = jअगरfies;
	temp->server = server;

	/*
	 * The शेष is क्रम the mid to be synchronous, so the
	 * शेष callback just wakes up the current task.
	 */
	get_task_काष्ठा(current);
	temp->creator = current;
	temp->callback = cअगरs_wake_up_task;
	temp->callback_data = current;

	atomic_inc(&midCount);
	temp->mid_state = MID_REQUEST_ALLOCATED;
	वापस temp;
पूर्ण

अटल व्योम _cअगरs_mid_q_entry_release(काष्ठा kref *refcount)
अणु
	काष्ठा mid_q_entry *midEntry =
			container_of(refcount, काष्ठा mid_q_entry, refcount);
#अगर_घोषित CONFIG_CIFS_STATS2
	__le16 command = midEntry->server->vals->lock_cmd;
	__u16 smb_cmd = le16_to_cpu(midEntry->command);
	अचिन्हित दीर्घ now;
	अचिन्हित दीर्घ roundtrip_समय;
#पूर्ण_अगर
	काष्ठा TCP_Server_Info *server = midEntry->server;

	अगर (midEntry->resp_buf && (midEntry->mid_flags & MID_WAIT_CANCELLED) &&
	    midEntry->mid_state == MID_RESPONSE_RECEIVED &&
	    server->ops->handle_cancelled_mid)
		server->ops->handle_cancelled_mid(midEntry, server);

	midEntry->mid_state = MID_FREE;
	atomic_dec(&midCount);
	अगर (midEntry->large_buf)
		cअगरs_buf_release(midEntry->resp_buf);
	अन्यथा
		cअगरs_small_buf_release(midEntry->resp_buf);
#अगर_घोषित CONFIG_CIFS_STATS2
	now = jअगरfies;
	अगर (now < midEntry->when_alloc)
		cअगरs_server_dbg(VFS, "Invalid mid allocation time\n");
	roundtrip_समय = now - midEntry->when_alloc;

	अगर (smb_cmd < NUMBER_OF_SMB2_COMMANDS) अणु
		अगर (atomic_पढ़ो(&server->num_cmds[smb_cmd]) == 0) अणु
			server->slowest_cmd[smb_cmd] = roundtrip_समय;
			server->fastest_cmd[smb_cmd] = roundtrip_समय;
		पूर्ण अन्यथा अणु
			अगर (server->slowest_cmd[smb_cmd] < roundtrip_समय)
				server->slowest_cmd[smb_cmd] = roundtrip_समय;
			अन्यथा अगर (server->fastest_cmd[smb_cmd] > roundtrip_समय)
				server->fastest_cmd[smb_cmd] = roundtrip_समय;
		पूर्ण
		cअगरs_stats_inc(&server->num_cmds[smb_cmd]);
		server->समय_per_cmd[smb_cmd] += roundtrip_समय;
	पूर्ण
	/*
	 * commands taking दीर्घer than one second (शेष) can be indications
	 * that something is wrong, unless it is quite a slow link or a very
	 * busy server. Note that this calc is unlikely or impossible to wrap
	 * as दीर्घ as slow_rsp_threshold is not set way above recommended max
	 * value (32767 ie 9 hours) and is generally harmless even अगर wrong
	 * since only affects debug counters - so leaving the calc as simple
	 * comparison rather than करोing multiple conversions and overflow
	 * checks
	 */
	अगर ((slow_rsp_threshold != 0) &&
	    समय_after(now, midEntry->when_alloc + (slow_rsp_threshold * HZ)) &&
	    (midEntry->command != command)) अणु
		/*
		 * smb2slowcmd[NUMBER_OF_SMB2_COMMANDS] counts by command
		 * NB: le16_to_cpu वापसs अचिन्हित so can not be negative below
		 */
		अगर (smb_cmd < NUMBER_OF_SMB2_COMMANDS)
			cअगरs_stats_inc(&server->smb2slowcmd[smb_cmd]);

		trace_smb3_slow_rsp(smb_cmd, midEntry->mid, midEntry->pid,
			       midEntry->when_sent, midEntry->when_received);
		अगर (cअगरsFYI & CIFS_TIMER) अणु
			pr_debug("slow rsp: cmd %d mid %llu",
				 midEntry->command, midEntry->mid);
			cअगरs_info("A: 0x%lx S: 0x%lx R: 0x%lx\n",
				  now - midEntry->when_alloc,
				  now - midEntry->when_sent,
				  now - midEntry->when_received);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	put_task_काष्ठा(midEntry->creator);

	mempool_मुक्त(midEntry, cअगरs_mid_poolp);
पूर्ण

व्योम cअगरs_mid_q_entry_release(काष्ठा mid_q_entry *midEntry)
अणु
	spin_lock(&GlobalMid_Lock);
	kref_put(&midEntry->refcount, _cअगरs_mid_q_entry_release);
	spin_unlock(&GlobalMid_Lock);
पूर्ण

व्योम DeleteMidQEntry(काष्ठा mid_q_entry *midEntry)
अणु
	cअगरs_mid_q_entry_release(midEntry);
पूर्ण

व्योम
cअगरs_delete_mid(काष्ठा mid_q_entry *mid)
अणु
	spin_lock(&GlobalMid_Lock);
	अगर (!(mid->mid_flags & MID_DELETED)) अणु
		list_del_init(&mid->qhead);
		mid->mid_flags |= MID_DELETED;
	पूर्ण
	spin_unlock(&GlobalMid_Lock);

	DeleteMidQEntry(mid);
पूर्ण

/*
 * smb_send_kvec - send an array of kvecs to the server
 * @server:	Server to send the data to
 * @smb_msg:	Message to send
 * @sent:	amount of data sent on socket is stored here
 *
 * Our basic "send data to server" function. Should be called with srv_mutex
 * held. The caller is responsible क्रम handling the results.
 */
अटल पूर्णांक
smb_send_kvec(काष्ठा TCP_Server_Info *server, काष्ठा msghdr *smb_msg,
	      माप_प्रकार *sent)
अणु
	पूर्णांक rc = 0;
	पूर्णांक retries = 0;
	काष्ठा socket *ssocket = server->ssocket;

	*sent = 0;

	smb_msg->msg_name = (काष्ठा sockaddr *) &server->dstaddr;
	smb_msg->msg_namelen = माप(काष्ठा sockaddr);
	smb_msg->msg_control = शून्य;
	smb_msg->msg_controllen = 0;
	अगर (server->noblocksnd)
		smb_msg->msg_flags = MSG_DONTWAIT + MSG_NOSIGNAL;
	अन्यथा
		smb_msg->msg_flags = MSG_NOSIGNAL;

	जबतक (msg_data_left(smb_msg)) अणु
		/*
		 * If blocking send, we try 3 बार, since each can block
		 * क्रम 5 seconds. For nonblocking  we have to try more
		 * but रुको increasing amounts of समय allowing समय क्रम
		 * socket to clear.  The overall समय we रुको in either
		 * हाल to send on the socket is about 15 seconds.
		 * Similarly we रुको क्रम 15 seconds क्रम a response from
		 * the server in SendReceive[2] क्रम the server to send
		 * a response back क्रम most types of requests (except
		 * SMB Write past end of file which can be slow, and
		 * blocking lock operations). NFS रुकोs slightly दीर्घer
		 * than CIFS, but this can make it take दीर्घer क्रम
		 * nonresponsive servers to be detected and 15 seconds
		 * is more than enough समय क्रम modern networks to
		 * send a packet.  In most हालs अगर we fail to send
		 * after the retries we will समाप्त the socket and
		 * reconnect which may clear the network problem.
		 */
		rc = sock_sendmsg(ssocket, smb_msg);
		अगर (rc == -EAGAIN) अणु
			retries++;
			अगर (retries >= 14 ||
			    (!server->noblocksnd && (retries > 2))) अणु
				cअगरs_server_dbg(VFS, "sends on sock %p stuck for 15 seconds\n",
					 ssocket);
				वापस -EAGAIN;
			पूर्ण
			msleep(1 << retries);
			जारी;
		पूर्ण

		अगर (rc < 0)
			वापस rc;

		अगर (rc == 0) अणु
			/* should never happen, letting socket clear beक्रमe
			   retrying is our only obvious option here */
			cअगरs_server_dbg(VFS, "tcp sent no data\n");
			msleep(500);
			जारी;
		पूर्ण

		/* send was at least partially successful */
		*sent += rc;
		retries = 0; /* in हाल we get ENOSPC on the next send */
	पूर्ण
	वापस 0;
पूर्ण

अचिन्हित दीर्घ
smb_rqst_len(काष्ठा TCP_Server_Info *server, काष्ठा smb_rqst *rqst)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा kvec *iov;
	पूर्णांक nvec;
	अचिन्हित दीर्घ buflen = 0;

	अगर (server->vals->header_preamble_size == 0 &&
	    rqst->rq_nvec >= 2 && rqst->rq_iov[0].iov_len == 4) अणु
		iov = &rqst->rq_iov[1];
		nvec = rqst->rq_nvec - 1;
	पूर्ण अन्यथा अणु
		iov = rqst->rq_iov;
		nvec = rqst->rq_nvec;
	पूर्ण

	/* total up iov array first */
	क्रम (i = 0; i < nvec; i++)
		buflen += iov[i].iov_len;

	/*
	 * Add in the page array अगर there is one. The caller needs to make
	 * sure rq_offset and rq_tailsz are set correctly. If a buffer of
	 * multiple pages ends at page boundary, rq_tailsz needs to be set to
	 * PAGE_SIZE.
	 */
	अगर (rqst->rq_npages) अणु
		अगर (rqst->rq_npages == 1)
			buflen += rqst->rq_tailsz;
		अन्यथा अणु
			/*
			 * If there is more than one page, calculate the
			 * buffer length based on rq_offset and rq_tailsz
			 */
			buflen += rqst->rq_pagesz * (rqst->rq_npages - 1) -
					rqst->rq_offset;
			buflen += rqst->rq_tailsz;
		पूर्ण
	पूर्ण

	वापस buflen;
पूर्ण

अटल पूर्णांक
__smb_send_rqst(काष्ठा TCP_Server_Info *server, पूर्णांक num_rqst,
		काष्ठा smb_rqst *rqst)
अणु
	पूर्णांक rc = 0;
	काष्ठा kvec *iov;
	पूर्णांक n_vec;
	अचिन्हित पूर्णांक send_length = 0;
	अचिन्हित पूर्णांक i, j;
	sigset_t mask, oldmask;
	माप_प्रकार total_len = 0, sent, size;
	काष्ठा socket *ssocket = server->ssocket;
	काष्ठा msghdr smb_msg;
	__be32 rfc1002_marker;

	अगर (cअगरs_rdma_enabled(server)) अणु
		/* वापस -EAGAIN when connecting or reconnecting */
		rc = -EAGAIN;
		अगर (server->smbd_conn)
			rc = smbd_send(server, num_rqst, rqst);
		जाओ smbd_करोne;
	पूर्ण

	अगर (ssocket == शून्य)
		वापस -EAGAIN;

	अगर (fatal_संकेत_pending(current)) अणु
		cअगरs_dbg(FYI, "signal pending before send request\n");
		वापस -ERESTARTSYS;
	पूर्ण

	/* cork the socket */
	tcp_sock_set_cork(ssocket->sk, true);

	क्रम (j = 0; j < num_rqst; j++)
		send_length += smb_rqst_len(server, &rqst[j]);
	rfc1002_marker = cpu_to_be32(send_length);

	/*
	 * We should not allow संकेतs to पूर्णांकerrupt the network send because
	 * any partial send will cause session reconnects thus increasing
	 * latency of प्रणाली calls and overload a server with unnecessary
	 * requests.
	 */

	sigfillset(&mask);
	sigprocmask(SIG_BLOCK, &mask, &oldmask);

	/* Generate a rfc1002 marker क्रम SMB2+ */
	अगर (server->vals->header_preamble_size == 0) अणु
		काष्ठा kvec hiov = अणु
			.iov_base = &rfc1002_marker,
			.iov_len  = 4
		पूर्ण;
		iov_iter_kvec(&smb_msg.msg_iter, WRITE, &hiov, 1, 4);
		rc = smb_send_kvec(server, &smb_msg, &sent);
		अगर (rc < 0)
			जाओ unmask;

		total_len += sent;
		send_length += 4;
	पूर्ण

	cअगरs_dbg(FYI, "Sending smb: smb_len=%u\n", send_length);

	क्रम (j = 0; j < num_rqst; j++) अणु
		iov = rqst[j].rq_iov;
		n_vec = rqst[j].rq_nvec;

		size = 0;
		क्रम (i = 0; i < n_vec; i++) अणु
			dump_smb(iov[i].iov_base, iov[i].iov_len);
			size += iov[i].iov_len;
		पूर्ण

		iov_iter_kvec(&smb_msg.msg_iter, WRITE, iov, n_vec, size);

		rc = smb_send_kvec(server, &smb_msg, &sent);
		अगर (rc < 0)
			जाओ unmask;

		total_len += sent;

		/* now walk the page array and send each page in it */
		क्रम (i = 0; i < rqst[j].rq_npages; i++) अणु
			काष्ठा bio_vec bvec;

			bvec.bv_page = rqst[j].rq_pages[i];
			rqst_page_get_length(&rqst[j], i, &bvec.bv_len,
					     &bvec.bv_offset);

			iov_iter_bvec(&smb_msg.msg_iter, WRITE,
				      &bvec, 1, bvec.bv_len);
			rc = smb_send_kvec(server, &smb_msg, &sent);
			अगर (rc < 0)
				अवरोध;

			total_len += sent;
		पूर्ण
	पूर्ण

unmask:
	sigprocmask(SIG_SETMASK, &oldmask, शून्य);

	/*
	 * If संकेत is pending but we have alपढ़ोy sent the whole packet to
	 * the server we need to वापस success status to allow a corresponding
	 * mid entry to be kept in the pending requests queue thus allowing
	 * to handle responses from the server by the client.
	 *
	 * If only part of the packet has been sent there is no need to hide
	 * पूर्णांकerrupt because the session will be reconnected anyway, so there
	 * won't be any response from the server to handle.
	 */

	अगर (संकेत_pending(current) && (total_len != send_length)) अणु
		cअगरs_dbg(FYI, "signal is pending after attempt to send\n");
		rc = -ERESTARTSYS;
	पूर्ण

	/* uncork it */
	tcp_sock_set_cork(ssocket->sk, false);

	अगर ((total_len > 0) && (total_len != send_length)) अणु
		cअगरs_dbg(FYI, "partial send (wanted=%u sent=%zu): terminating session\n",
			 send_length, total_len);
		/*
		 * If we have only sent part of an SMB then the next SMB could
		 * be taken as the reमुख्यder of this one. We need to समाप्त the
		 * socket so the server throws away the partial SMB
		 */
		server->tcpStatus = CअगरsNeedReconnect;
		trace_smb3_partial_send_reconnect(server->CurrentMid,
						  server->conn_id, server->hostname);
	पूर्ण
smbd_करोne:
	अगर (rc < 0 && rc != -EINTR)
		cअगरs_server_dbg(VFS, "Error %d sending data on socket to server\n",
			 rc);
	अन्यथा अगर (rc > 0)
		rc = 0;

	वापस rc;
पूर्ण

अटल पूर्णांक
smb_send_rqst(काष्ठा TCP_Server_Info *server, पूर्णांक num_rqst,
	      काष्ठा smb_rqst *rqst, पूर्णांक flags)
अणु
	काष्ठा kvec iov;
	काष्ठा smb2_transक्रमm_hdr *tr_hdr;
	काष्ठा smb_rqst cur_rqst[MAX_COMPOUND];
	पूर्णांक rc;

	अगर (!(flags & CIFS_TRANSFORM_REQ))
		वापस __smb_send_rqst(server, num_rqst, rqst);

	अगर (num_rqst > MAX_COMPOUND - 1)
		वापस -ENOMEM;

	अगर (!server->ops->init_transक्रमm_rq) अणु
		cअगरs_server_dbg(VFS, "Encryption requested but transform callback is missing\n");
		वापस -EIO;
	पूर्ण

	tr_hdr = kदो_स्मृति(माप(*tr_hdr), GFP_NOFS);
	अगर (!tr_hdr)
		वापस -ENOMEM;

	स_रखो(&cur_rqst[0], 0, माप(cur_rqst));
	स_रखो(&iov, 0, माप(iov));
	स_रखो(tr_hdr, 0, माप(*tr_hdr));

	iov.iov_base = tr_hdr;
	iov.iov_len = माप(*tr_hdr);
	cur_rqst[0].rq_iov = &iov;
	cur_rqst[0].rq_nvec = 1;

	rc = server->ops->init_transक्रमm_rq(server, num_rqst + 1,
					    &cur_rqst[0], rqst);
	अगर (rc)
		जाओ out;

	rc = __smb_send_rqst(server, num_rqst + 1, &cur_rqst[0]);
	smb3_मुक्त_compound_rqst(num_rqst, &cur_rqst[1]);
out:
	kमुक्त(tr_hdr);
	वापस rc;
पूर्ण

पूर्णांक
smb_send(काष्ठा TCP_Server_Info *server, काष्ठा smb_hdr *smb_buffer,
	 अचिन्हित पूर्णांक smb_buf_length)
अणु
	काष्ठा kvec iov[2];
	काष्ठा smb_rqst rqst = अणु .rq_iov = iov,
				 .rq_nvec = 2 पूर्ण;

	iov[0].iov_base = smb_buffer;
	iov[0].iov_len = 4;
	iov[1].iov_base = (अक्षर *)smb_buffer + 4;
	iov[1].iov_len = smb_buf_length;

	वापस __smb_send_rqst(server, 1, &rqst);
पूर्ण

अटल पूर्णांक
रुको_क्रम_मुक्त_credits(काष्ठा TCP_Server_Info *server, स्थिर पूर्णांक num_credits,
		      स्थिर पूर्णांक समयout, स्थिर पूर्णांक flags,
		      अचिन्हित पूर्णांक *instance)
अणु
	दीर्घ rc;
	पूर्णांक *credits;
	पूर्णांक optype;
	दीर्घ पूर्णांक t;
	पूर्णांक scredits, in_flight;

	अगर (समयout < 0)
		t = MAX_JIFFY_OFFSET;
	अन्यथा
		t = msecs_to_jअगरfies(समयout);

	optype = flags & CIFS_OP_MASK;

	*instance = 0;

	credits = server->ops->get_credits_field(server, optype);
	/* Since an echo is alपढ़ोy inflight, no need to रुको to send another */
	अगर (*credits <= 0 && optype == CIFS_ECHO_OP)
		वापस -EAGAIN;

	spin_lock(&server->req_lock);
	अगर ((flags & CIFS_TIMEOUT_MASK) == CIFS_NON_BLOCKING) अणु
		/* oplock अवरोधs must not be held up */
		server->in_flight++;
		अगर (server->in_flight > server->max_in_flight)
			server->max_in_flight = server->in_flight;
		*credits -= 1;
		*instance = server->reconnect_instance;
		scredits = *credits;
		in_flight = server->in_flight;
		spin_unlock(&server->req_lock);

		trace_smb3_add_credits(server->CurrentMid,
				server->conn_id, server->hostname, scredits, -1, in_flight);
		cअगरs_dbg(FYI, "%s: remove %u credits total=%d\n",
				__func__, 1, scredits);

		वापस 0;
	पूर्ण

	जबतक (1) अणु
		अगर (*credits < num_credits) अणु
			scredits = *credits;
			spin_unlock(&server->req_lock);

			cअगरs_num_रुकोers_inc(server);
			rc = रुको_event_समाप्तable_समयout(server->request_q,
				has_credits(server, credits, num_credits), t);
			cअगरs_num_रुकोers_dec(server);
			अगर (!rc) अणु
				spin_lock(&server->req_lock);
				scredits = *credits;
				in_flight = server->in_flight;
				spin_unlock(&server->req_lock);

				trace_smb3_credit_समयout(server->CurrentMid,
						server->conn_id, server->hostname, scredits,
						num_credits, in_flight);
				cअगरs_server_dbg(VFS, "wait timed out after %d ms\n",
						समयout);
				वापस -EBUSY;
			पूर्ण
			अगर (rc == -ERESTARTSYS)
				वापस -ERESTARTSYS;
			spin_lock(&server->req_lock);
		पूर्ण अन्यथा अणु
			अगर (server->tcpStatus == CअगरsExiting) अणु
				spin_unlock(&server->req_lock);
				वापस -ENOENT;
			पूर्ण

			/*
			 * For normal commands, reserve the last MAX_COMPOUND
			 * credits to compound requests.
			 * Otherwise these compounds could be permanently
			 * starved क्रम credits by single-credit requests.
			 *
			 * To prevent spinning CPU, block this thपढ़ो until
			 * there are >MAX_COMPOUND credits available.
			 * But only करो this is we alपढ़ोy have a lot of
			 * credits in flight to aव्योम triggering this check
			 * क्रम servers that are slow to hand out credits on
			 * new sessions.
			 */
			अगर (!optype && num_credits == 1 &&
			    server->in_flight > 2 * MAX_COMPOUND &&
			    *credits <= MAX_COMPOUND) अणु
				spin_unlock(&server->req_lock);

				cअगरs_num_रुकोers_inc(server);
				rc = रुको_event_समाप्तable_समयout(
					server->request_q,
					has_credits(server, credits,
						    MAX_COMPOUND + 1),
					t);
				cअगरs_num_रुकोers_dec(server);
				अगर (!rc) अणु
					spin_lock(&server->req_lock);
					scredits = *credits;
					in_flight = server->in_flight;
					spin_unlock(&server->req_lock);

					trace_smb3_credit_समयout(
							server->CurrentMid,
							server->conn_id, server->hostname,
							scredits, num_credits, in_flight);
					cअगरs_server_dbg(VFS, "wait timed out after %d ms\n",
							समयout);
					वापस -EBUSY;
				पूर्ण
				अगर (rc == -ERESTARTSYS)
					वापस -ERESTARTSYS;
				spin_lock(&server->req_lock);
				जारी;
			पूर्ण

			/*
			 * Can not count locking commands against total
			 * as they are allowed to block on server.
			 */

			/* update # of requests on the wire to server */
			अगर ((flags & CIFS_TIMEOUT_MASK) != CIFS_BLOCKING_OP) अणु
				*credits -= num_credits;
				server->in_flight += num_credits;
				अगर (server->in_flight > server->max_in_flight)
					server->max_in_flight = server->in_flight;
				*instance = server->reconnect_instance;
			पूर्ण
			scredits = *credits;
			in_flight = server->in_flight;
			spin_unlock(&server->req_lock);

			trace_smb3_add_credits(server->CurrentMid,
					server->conn_id, server->hostname, scredits,
					-(num_credits), in_flight);
			cअगरs_dbg(FYI, "%s: remove %u credits total=%d\n",
					__func__, num_credits, scredits);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
रुको_क्रम_मुक्त_request(काष्ठा TCP_Server_Info *server, स्थिर पूर्णांक flags,
		      अचिन्हित पूर्णांक *instance)
अणु
	वापस रुको_क्रम_मुक्त_credits(server, 1, -1, flags,
				     instance);
पूर्ण

अटल पूर्णांक
रुको_क्रम_compound_request(काष्ठा TCP_Server_Info *server, पूर्णांक num,
			  स्थिर पूर्णांक flags, अचिन्हित पूर्णांक *instance)
अणु
	पूर्णांक *credits;
	पूर्णांक scredits, in_flight;

	credits = server->ops->get_credits_field(server, flags & CIFS_OP_MASK);

	spin_lock(&server->req_lock);
	scredits = *credits;
	in_flight = server->in_flight;

	अगर (*credits < num) अणु
		/*
		 * If the server is tight on resources or just gives us less
		 * credits क्रम other reasons (e.g. requests are coming out of
		 * order and the server delays granting more credits until it
		 * processes a missing mid) and we exhausted most available
		 * credits there may be situations when we try to send
		 * a compound request but we करोn't have enough credits. At this
		 * poपूर्णांक the client needs to decide अगर it should रुको क्रम
		 * additional credits or fail the request. If at least one
		 * request is in flight there is a high probability that the
		 * server will वापस enough credits to satisfy this compound
		 * request.
		 *
		 * Return immediately अगर no requests in flight since we will be
		 * stuck on रुकोing क्रम credits.
		 */
		अगर (server->in_flight == 0) अणु
			spin_unlock(&server->req_lock);
			trace_smb3_insufficient_credits(server->CurrentMid,
					server->conn_id, server->hostname, scredits,
					num, in_flight);
			cअगरs_dbg(FYI, "%s: %d requests in flight, needed %d total=%d\n",
					__func__, in_flight, num, scredits);
			वापस -EDEADLK;
		पूर्ण
	पूर्ण
	spin_unlock(&server->req_lock);

	वापस रुको_क्रम_मुक्त_credits(server, num, 60000, flags,
				     instance);
पूर्ण

पूर्णांक
cअगरs_रुको_mtu_credits(काष्ठा TCP_Server_Info *server, अचिन्हित पूर्णांक size,
		      अचिन्हित पूर्णांक *num, काष्ठा cअगरs_credits *credits)
अणु
	*num = size;
	credits->value = 0;
	credits->instance = server->reconnect_instance;
	वापस 0;
पूर्ण

अटल पूर्णांक allocate_mid(काष्ठा cअगरs_ses *ses, काष्ठा smb_hdr *in_buf,
			काष्ठा mid_q_entry **ppmidQ)
अणु
	अगर (ses->server->tcpStatus == CअगरsExiting) अणु
		वापस -ENOENT;
	पूर्ण

	अगर (ses->server->tcpStatus == CअगरsNeedReconnect) अणु
		cअगरs_dbg(FYI, "tcp session dead - return to caller to retry\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (ses->status == CअगरsNew) अणु
		अगर ((in_buf->Command != SMB_COM_SESSION_SETUP_ANDX) &&
			(in_buf->Command != SMB_COM_NEGOTIATE))
			वापस -EAGAIN;
		/* अन्यथा ok - we are setting up session */
	पूर्ण

	अगर (ses->status == CअगरsExiting) अणु
		/* check अगर SMB session is bad because we are setting it up */
		अगर (in_buf->Command != SMB_COM_LOGOFF_ANDX)
			वापस -EAGAIN;
		/* अन्यथा ok - we are shutting करोwn session */
	पूर्ण

	*ppmidQ = AllocMidQEntry(in_buf, ses->server);
	अगर (*ppmidQ == शून्य)
		वापस -ENOMEM;
	spin_lock(&GlobalMid_Lock);
	list_add_tail(&(*ppmidQ)->qhead, &ses->server->pending_mid_q);
	spin_unlock(&GlobalMid_Lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
रुको_क्रम_response(काष्ठा TCP_Server_Info *server, काष्ठा mid_q_entry *midQ)
अणु
	पूर्णांक error;

	error = रुको_event_मुक्तzeसमाप्तable_unsafe(server->response_q,
				    midQ->mid_state != MID_REQUEST_SUBMITTED);
	अगर (error < 0)
		वापस -ERESTARTSYS;

	वापस 0;
पूर्ण

काष्ठा mid_q_entry *
cअगरs_setup_async_request(काष्ठा TCP_Server_Info *server, काष्ठा smb_rqst *rqst)
अणु
	पूर्णांक rc;
	काष्ठा smb_hdr *hdr = (काष्ठा smb_hdr *)rqst->rq_iov[0].iov_base;
	काष्ठा mid_q_entry *mid;

	अगर (rqst->rq_iov[0].iov_len != 4 ||
	    rqst->rq_iov[0].iov_base + 4 != rqst->rq_iov[1].iov_base)
		वापस ERR_PTR(-EIO);

	/* enable signing अगर server requires it */
	अगर (server->sign)
		hdr->Flags2 |= SMBFLG2_SECURITY_SIGNATURE;

	mid = AllocMidQEntry(hdr, server);
	अगर (mid == शून्य)
		वापस ERR_PTR(-ENOMEM);

	rc = cअगरs_sign_rqst(rqst, server, &mid->sequence_number);
	अगर (rc) अणु
		DeleteMidQEntry(mid);
		वापस ERR_PTR(rc);
	पूर्ण

	वापस mid;
पूर्ण

/*
 * Send a SMB request and set the callback function in the mid to handle
 * the result. Caller is responsible क्रम dealing with समयouts.
 */
पूर्णांक
cअगरs_call_async(काष्ठा TCP_Server_Info *server, काष्ठा smb_rqst *rqst,
		mid_receive_t *receive, mid_callback_t *callback,
		mid_handle_t *handle, व्योम *cbdata, स्थिर पूर्णांक flags,
		स्थिर काष्ठा cअगरs_credits *exist_credits)
अणु
	पूर्णांक rc;
	काष्ठा mid_q_entry *mid;
	काष्ठा cअगरs_credits credits = अणु .value = 0, .instance = 0 पूर्ण;
	अचिन्हित पूर्णांक instance;
	पूर्णांक optype;

	optype = flags & CIFS_OP_MASK;

	अगर ((flags & CIFS_HAS_CREDITS) == 0) अणु
		rc = रुको_क्रम_मुक्त_request(server, flags, &instance);
		अगर (rc)
			वापस rc;
		credits.value = 1;
		credits.instance = instance;
	पूर्ण अन्यथा
		instance = exist_credits->instance;

	mutex_lock(&server->srv_mutex);

	/*
	 * We can't use credits obtained from the previous session to send this
	 * request. Check अगर there were reconnects after we obtained credits and
	 * वापस -EAGAIN in such हालs to let callers handle it.
	 */
	अगर (instance != server->reconnect_instance) अणु
		mutex_unlock(&server->srv_mutex);
		add_credits_and_wake_अगर(server, &credits, optype);
		वापस -EAGAIN;
	पूर्ण

	mid = server->ops->setup_async_request(server, rqst);
	अगर (IS_ERR(mid)) अणु
		mutex_unlock(&server->srv_mutex);
		add_credits_and_wake_अगर(server, &credits, optype);
		वापस PTR_ERR(mid);
	पूर्ण

	mid->receive = receive;
	mid->callback = callback;
	mid->callback_data = cbdata;
	mid->handle = handle;
	mid->mid_state = MID_REQUEST_SUBMITTED;

	/* put it on the pending_mid_q */
	spin_lock(&GlobalMid_Lock);
	list_add_tail(&mid->qhead, &server->pending_mid_q);
	spin_unlock(&GlobalMid_Lock);

	/*
	 * Need to store the समय in mid beक्रमe calling I/O. For call_async,
	 * I/O response may come back and मुक्त the mid entry on another thपढ़ो.
	 */
	cअगरs_save_when_sent(mid);
	cअगरs_in_send_inc(server);
	rc = smb_send_rqst(server, 1, rqst, flags);
	cअगरs_in_send_dec(server);

	अगर (rc < 0) अणु
		revert_current_mid(server, mid->credits);
		server->sequence_number -= 2;
		cअगरs_delete_mid(mid);
	पूर्ण

	mutex_unlock(&server->srv_mutex);

	अगर (rc == 0)
		वापस 0;

	add_credits_and_wake_अगर(server, &credits, optype);
	वापस rc;
पूर्ण

/*
 *
 * Send an SMB Request.  No response info (other than वापस code)
 * needs to be parsed.
 *
 * flags indicate the type of request buffer and how दीर्घ to रुको
 * and whether to log NT STATUS code (error) beक्रमe mapping it to POSIX error
 *
 */
पूर्णांक
SendReceiveNoRsp(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
		 अक्षर *in_buf, पूर्णांक flags)
अणु
	पूर्णांक rc;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov;
	पूर्णांक resp_buf_type;

	iov[0].iov_base = in_buf;
	iov[0].iov_len = get_rfc1002_length(in_buf) + 4;
	flags |= CIFS_NO_RSP_BUF;
	rc = SendReceive2(xid, ses, iov, 1, &resp_buf_type, flags, &rsp_iov);
	cअगरs_dbg(NOISY, "SendRcvNoRsp flags %d rc %d\n", flags, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_sync_mid_result(काष्ठा mid_q_entry *mid, काष्ठा TCP_Server_Info *server)
अणु
	पूर्णांक rc = 0;

	cअगरs_dbg(FYI, "%s: cmd=%d mid=%llu state=%d\n",
		 __func__, le16_to_cpu(mid->command), mid->mid, mid->mid_state);

	spin_lock(&GlobalMid_Lock);
	चयन (mid->mid_state) अणु
	हाल MID_RESPONSE_RECEIVED:
		spin_unlock(&GlobalMid_Lock);
		वापस rc;
	हाल MID_RETRY_NEEDED:
		rc = -EAGAIN;
		अवरोध;
	हाल MID_RESPONSE_MALFORMED:
		rc = -EIO;
		अवरोध;
	हाल MID_SHUTDOWN:
		rc = -EHOSTDOWN;
		अवरोध;
	शेष:
		अगर (!(mid->mid_flags & MID_DELETED)) अणु
			list_del_init(&mid->qhead);
			mid->mid_flags |= MID_DELETED;
		पूर्ण
		cअगरs_server_dbg(VFS, "%s: invalid mid state mid=%llu state=%d\n",
			 __func__, mid->mid, mid->mid_state);
		rc = -EIO;
	पूर्ण
	spin_unlock(&GlobalMid_Lock);

	DeleteMidQEntry(mid);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक
send_cancel(काष्ठा TCP_Server_Info *server, काष्ठा smb_rqst *rqst,
	    काष्ठा mid_q_entry *mid)
अणु
	वापस server->ops->send_cancel ?
				server->ops->send_cancel(server, rqst, mid) : 0;
पूर्ण

पूर्णांक
cअगरs_check_receive(काष्ठा mid_q_entry *mid, काष्ठा TCP_Server_Info *server,
		   bool log_error)
अणु
	अचिन्हित पूर्णांक len = get_rfc1002_length(mid->resp_buf) + 4;

	dump_smb(mid->resp_buf, min_t(u32, 92, len));

	/* convert the length पूर्णांकo a more usable क्रमm */
	अगर (server->sign) अणु
		काष्ठा kvec iov[2];
		पूर्णांक rc = 0;
		काष्ठा smb_rqst rqst = अणु .rq_iov = iov,
					 .rq_nvec = 2 पूर्ण;

		iov[0].iov_base = mid->resp_buf;
		iov[0].iov_len = 4;
		iov[1].iov_base = (अक्षर *)mid->resp_buf + 4;
		iov[1].iov_len = len - 4;
		/* FIXME: add code to समाप्त session */
		rc = cअगरs_verअगरy_signature(&rqst, server,
					   mid->sequence_number);
		अगर (rc)
			cअगरs_server_dbg(VFS, "SMB signature verification returned error = %d\n",
				 rc);
	पूर्ण

	/* BB special हाल reconnect tid and uid here? */
	वापस map_and_check_smb_error(mid, log_error);
पूर्ण

काष्ठा mid_q_entry *
cअगरs_setup_request(काष्ठा cअगरs_ses *ses, काष्ठा TCP_Server_Info *ignored,
		   काष्ठा smb_rqst *rqst)
अणु
	पूर्णांक rc;
	काष्ठा smb_hdr *hdr = (काष्ठा smb_hdr *)rqst->rq_iov[0].iov_base;
	काष्ठा mid_q_entry *mid;

	अगर (rqst->rq_iov[0].iov_len != 4 ||
	    rqst->rq_iov[0].iov_base + 4 != rqst->rq_iov[1].iov_base)
		वापस ERR_PTR(-EIO);

	rc = allocate_mid(ses, hdr, &mid);
	अगर (rc)
		वापस ERR_PTR(rc);
	rc = cअगरs_sign_rqst(rqst, ses->server, &mid->sequence_number);
	अगर (rc) अणु
		cअगरs_delete_mid(mid);
		वापस ERR_PTR(rc);
	पूर्ण
	वापस mid;
पूर्ण

अटल व्योम
cअगरs_compound_callback(काष्ठा mid_q_entry *mid)
अणु
	काष्ठा TCP_Server_Info *server = mid->server;
	काष्ठा cअगरs_credits credits;

	credits.value = server->ops->get_credits(mid);
	credits.instance = server->reconnect_instance;

	add_credits(server, &credits, mid->optype);
पूर्ण

अटल व्योम
cअगरs_compound_last_callback(काष्ठा mid_q_entry *mid)
अणु
	cअगरs_compound_callback(mid);
	cअगरs_wake_up_task(mid);
पूर्ण

अटल व्योम
cअगरs_cancelled_callback(काष्ठा mid_q_entry *mid)
अणु
	cअगरs_compound_callback(mid);
	DeleteMidQEntry(mid);
पूर्ण

/*
 * Return a channel (master अगर none) of @ses that can be used to send
 * regular requests.
 *
 * If we are currently binding a new channel (negprot/sess.setup),
 * वापस the new incomplete channel.
 */
काष्ठा TCP_Server_Info *cअगरs_pick_channel(काष्ठा cअगरs_ses *ses)
अणु
	uपूर्णांक index = 0;

	अगर (!ses)
		वापस शून्य;

	अगर (!ses->binding) अणु
		/* round robin */
		अगर (ses->chan_count > 1) अणु
			index = (uपूर्णांक)atomic_inc_वापस(&ses->chan_seq);
			index %= ses->chan_count;
		पूर्ण
		वापस ses->chans[index].server;
	पूर्ण अन्यथा अणु
		वापस cअगरs_ses_server(ses);
	पूर्ण
पूर्ण

पूर्णांक
compound_send_recv(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
		   काष्ठा TCP_Server_Info *server,
		   स्थिर पूर्णांक flags, स्थिर पूर्णांक num_rqst, काष्ठा smb_rqst *rqst,
		   पूर्णांक *resp_buf_type, काष्ठा kvec *resp_iov)
अणु
	पूर्णांक i, j, optype, rc = 0;
	काष्ठा mid_q_entry *midQ[MAX_COMPOUND];
	bool cancelled_mid[MAX_COMPOUND] = अणुfalseपूर्ण;
	काष्ठा cअगरs_credits credits[MAX_COMPOUND] = अणु
		अणु .value = 0, .instance = 0 पूर्ण
	पूर्ण;
	अचिन्हित पूर्णांक instance;
	अक्षर *buf;

	optype = flags & CIFS_OP_MASK;

	क्रम (i = 0; i < num_rqst; i++)
		resp_buf_type[i] = CIFS_NO_BUFFER;  /* no response buf yet */

	अगर (!ses || !ses->server || !server) अणु
		cअगरs_dbg(VFS, "Null session\n");
		वापस -EIO;
	पूर्ण

	अगर (server->tcpStatus == CअगरsExiting)
		वापस -ENOENT;

	/*
	 * Wait क्रम all the requests to become available.
	 * This approach still leaves the possibility to be stuck रुकोing क्रम
	 * credits अगर the server करोesn't grant credits to the outstanding
	 * requests and अगर the client is completely idle, not generating any
	 * other requests.
	 * This can be handled by the eventual session reconnect.
	 */
	rc = रुको_क्रम_compound_request(server, num_rqst, flags,
				       &instance);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < num_rqst; i++) अणु
		credits[i].value = 1;
		credits[i].instance = instance;
	पूर्ण

	/*
	 * Make sure that we sign in the same order that we send on this socket
	 * and aव्योम races inside tcp sendmsg code that could cause corruption
	 * of smb data.
	 */

	mutex_lock(&server->srv_mutex);

	/*
	 * All the parts of the compound chain beदीर्घ obtained credits from the
	 * same session. We can not use credits obtained from the previous
	 * session to send this request. Check अगर there were reconnects after
	 * we obtained credits and वापस -EAGAIN in such हालs to let callers
	 * handle it.
	 */
	अगर (instance != server->reconnect_instance) अणु
		mutex_unlock(&server->srv_mutex);
		क्रम (j = 0; j < num_rqst; j++)
			add_credits(server, &credits[j], optype);
		वापस -EAGAIN;
	पूर्ण

	क्रम (i = 0; i < num_rqst; i++) अणु
		midQ[i] = server->ops->setup_request(ses, server, &rqst[i]);
		अगर (IS_ERR(midQ[i])) अणु
			revert_current_mid(server, i);
			क्रम (j = 0; j < i; j++)
				cअगरs_delete_mid(midQ[j]);
			mutex_unlock(&server->srv_mutex);

			/* Update # of requests on wire to server */
			क्रम (j = 0; j < num_rqst; j++)
				add_credits(server, &credits[j], optype);
			वापस PTR_ERR(midQ[i]);
		पूर्ण

		midQ[i]->mid_state = MID_REQUEST_SUBMITTED;
		midQ[i]->optype = optype;
		/*
		 * Invoke callback क्रम every part of the compound chain
		 * to calculate credits properly. Wake up this thपढ़ो only when
		 * the last element is received.
		 */
		अगर (i < num_rqst - 1)
			midQ[i]->callback = cअगरs_compound_callback;
		अन्यथा
			midQ[i]->callback = cअगरs_compound_last_callback;
	पूर्ण
	cअगरs_in_send_inc(server);
	rc = smb_send_rqst(server, num_rqst, rqst, flags);
	cअगरs_in_send_dec(server);

	क्रम (i = 0; i < num_rqst; i++)
		cअगरs_save_when_sent(midQ[i]);

	अगर (rc < 0) अणु
		revert_current_mid(server, num_rqst);
		server->sequence_number -= 2;
	पूर्ण

	mutex_unlock(&server->srv_mutex);

	/*
	 * If sending failed क्रम some reason or it is an oplock अवरोध that we
	 * will not receive a response to - वापस credits back
	 */
	अगर (rc < 0 || (flags & CIFS_NO_SRV_RSP)) अणु
		क्रम (i = 0; i < num_rqst; i++)
			add_credits(server, &credits[i], optype);
		जाओ out;
	पूर्ण

	/*
	 * At this poपूर्णांक the request is passed to the network stack - we assume
	 * that any credits taken from the server काष्ठाure on the client have
	 * been spent and we can't वापस them back. Once we receive responses
	 * we will collect credits granted by the server in the mid callbacks
	 * and add those credits to the server काष्ठाure.
	 */

	/*
	 * Compounding is never used during session establish.
	 */
	अगर ((ses->status == CअगरsNew) || (optype & CIFS_NEG_OP) || (optype & CIFS_SESS_OP)) अणु
		mutex_lock(&server->srv_mutex);
		smb311_update_preauth_hash(ses, rqst[0].rq_iov,
					   rqst[0].rq_nvec);
		mutex_unlock(&server->srv_mutex);
	पूर्ण

	क्रम (i = 0; i < num_rqst; i++) अणु
		rc = रुको_क्रम_response(server, midQ[i]);
		अगर (rc != 0)
			अवरोध;
	पूर्ण
	अगर (rc != 0) अणु
		क्रम (; i < num_rqst; i++) अणु
			cअगरs_server_dbg(FYI, "Cancelling wait for mid %llu cmd: %d\n",
				 midQ[i]->mid, le16_to_cpu(midQ[i]->command));
			send_cancel(server, &rqst[i], midQ[i]);
			spin_lock(&GlobalMid_Lock);
			midQ[i]->mid_flags |= MID_WAIT_CANCELLED;
			अगर (midQ[i]->mid_state == MID_REQUEST_SUBMITTED) अणु
				midQ[i]->callback = cअगरs_cancelled_callback;
				cancelled_mid[i] = true;
				credits[i].value = 0;
			पूर्ण
			spin_unlock(&GlobalMid_Lock);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_rqst; i++) अणु
		अगर (rc < 0)
			जाओ out;

		rc = cअगरs_sync_mid_result(midQ[i], server);
		अगर (rc != 0) अणु
			/* mark this mid as cancelled to not मुक्त it below */
			cancelled_mid[i] = true;
			जाओ out;
		पूर्ण

		अगर (!midQ[i]->resp_buf ||
		    midQ[i]->mid_state != MID_RESPONSE_RECEIVED) अणु
			rc = -EIO;
			cअगरs_dbg(FYI, "Bad MID state?\n");
			जाओ out;
		पूर्ण

		buf = (अक्षर *)midQ[i]->resp_buf;
		resp_iov[i].iov_base = buf;
		resp_iov[i].iov_len = midQ[i]->resp_buf_size +
			server->vals->header_preamble_size;

		अगर (midQ[i]->large_buf)
			resp_buf_type[i] = CIFS_LARGE_BUFFER;
		अन्यथा
			resp_buf_type[i] = CIFS_SMALL_BUFFER;

		rc = server->ops->check_receive(midQ[i], server,
						     flags & CIFS_LOG_ERROR);

		/* mark it so buf will not be मुक्तd by cअगरs_delete_mid */
		अगर ((flags & CIFS_NO_RSP_BUF) == 0)
			midQ[i]->resp_buf = शून्य;

	पूर्ण

	/*
	 * Compounding is never used during session establish.
	 */
	अगर ((ses->status == CअगरsNew) || (optype & CIFS_NEG_OP) || (optype & CIFS_SESS_OP)) अणु
		काष्ठा kvec iov = अणु
			.iov_base = resp_iov[0].iov_base,
			.iov_len = resp_iov[0].iov_len
		पूर्ण;
		mutex_lock(&server->srv_mutex);
		smb311_update_preauth_hash(ses, &iov, 1);
		mutex_unlock(&server->srv_mutex);
	पूर्ण

out:
	/*
	 * This will dequeue all mids. After this it is important that the
	 * demultiplex_thपढ़ो will not process any of these mids any futher.
	 * This is prevented above by using a noop callback that will not
	 * wake this thपढ़ो except क्रम the very last PDU.
	 */
	क्रम (i = 0; i < num_rqst; i++) अणु
		अगर (!cancelled_mid[i])
			cअगरs_delete_mid(midQ[i]);
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक
cअगरs_send_recv(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
	       काष्ठा TCP_Server_Info *server,
	       काष्ठा smb_rqst *rqst, पूर्णांक *resp_buf_type, स्थिर पूर्णांक flags,
	       काष्ठा kvec *resp_iov)
अणु
	वापस compound_send_recv(xid, ses, server, flags, 1,
				  rqst, resp_buf_type, resp_iov);
पूर्ण

पूर्णांक
SendReceive2(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
	     काष्ठा kvec *iov, पूर्णांक n_vec, पूर्णांक *resp_buf_type /* ret */,
	     स्थिर पूर्णांक flags, काष्ठा kvec *resp_iov)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा kvec s_iov[CIFS_MAX_IOV_SIZE], *new_iov;
	पूर्णांक rc;

	अगर (n_vec + 1 > CIFS_MAX_IOV_SIZE) अणु
		new_iov = kदो_स्मृति_array(n_vec + 1, माप(काष्ठा kvec),
					GFP_KERNEL);
		अगर (!new_iov) अणु
			/* otherwise cअगरs_send_recv below sets resp_buf_type */
			*resp_buf_type = CIFS_NO_BUFFER;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा
		new_iov = s_iov;

	/* 1st iov is a RFC1001 length followed by the rest of the packet */
	स_नकल(new_iov + 1, iov, (माप(काष्ठा kvec) * n_vec));

	new_iov[0].iov_base = new_iov[1].iov_base;
	new_iov[0].iov_len = 4;
	new_iov[1].iov_base += 4;
	new_iov[1].iov_len -= 4;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = new_iov;
	rqst.rq_nvec = n_vec + 1;

	rc = cअगरs_send_recv(xid, ses, ses->server,
			    &rqst, resp_buf_type, flags, resp_iov);
	अगर (n_vec + 1 > CIFS_MAX_IOV_SIZE)
		kमुक्त(new_iov);
	वापस rc;
पूर्ण

पूर्णांक
SendReceive(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
	    काष्ठा smb_hdr *in_buf, काष्ठा smb_hdr *out_buf,
	    पूर्णांक *pbytes_वापसed, स्थिर पूर्णांक flags)
अणु
	पूर्णांक rc = 0;
	काष्ठा mid_q_entry *midQ;
	अचिन्हित पूर्णांक len = be32_to_cpu(in_buf->smb_buf_length);
	काष्ठा kvec iov = अणु .iov_base = in_buf, .iov_len = len पूर्ण;
	काष्ठा smb_rqst rqst = अणु .rq_iov = &iov, .rq_nvec = 1 पूर्ण;
	काष्ठा cअगरs_credits credits = अणु .value = 1, .instance = 0 पूर्ण;
	काष्ठा TCP_Server_Info *server;

	अगर (ses == शून्य) अणु
		cअगरs_dbg(VFS, "Null smb session\n");
		वापस -EIO;
	पूर्ण
	server = ses->server;
	अगर (server == शून्य) अणु
		cअगरs_dbg(VFS, "Null tcp session\n");
		वापस -EIO;
	पूर्ण

	अगर (server->tcpStatus == CअगरsExiting)
		वापस -ENOENT;

	/* Ensure that we करो not send more than 50 overlapping requests
	   to the same server. We may make this configurable later or
	   use ses->maxReq */

	अगर (len > CIFSMaxBufSize + MAX_CIFS_HDR_SIZE - 4) अणु
		cअगरs_server_dbg(VFS, "Invalid length, greater than maximum frame, %d\n",
				len);
		वापस -EIO;
	पूर्ण

	rc = रुको_क्रम_मुक्त_request(server, flags, &credits.instance);
	अगर (rc)
		वापस rc;

	/* make sure that we sign in the same order that we send on this socket
	   and aव्योम races inside tcp sendmsg code that could cause corruption
	   of smb data */

	mutex_lock(&server->srv_mutex);

	rc = allocate_mid(ses, in_buf, &midQ);
	अगर (rc) अणु
		mutex_unlock(&server->srv_mutex);
		/* Update # of requests on wire to server */
		add_credits(server, &credits, 0);
		वापस rc;
	पूर्ण

	rc = cअगरs_sign_smb(in_buf, server, &midQ->sequence_number);
	अगर (rc) अणु
		mutex_unlock(&server->srv_mutex);
		जाओ out;
	पूर्ण

	midQ->mid_state = MID_REQUEST_SUBMITTED;

	cअगरs_in_send_inc(server);
	rc = smb_send(server, in_buf, len);
	cअगरs_in_send_dec(server);
	cअगरs_save_when_sent(midQ);

	अगर (rc < 0)
		server->sequence_number -= 2;

	mutex_unlock(&server->srv_mutex);

	अगर (rc < 0)
		जाओ out;

	rc = रुको_क्रम_response(server, midQ);
	अगर (rc != 0) अणु
		send_cancel(server, &rqst, midQ);
		spin_lock(&GlobalMid_Lock);
		अगर (midQ->mid_state == MID_REQUEST_SUBMITTED) अणु
			/* no दीर्घer considered to be "in-flight" */
			midQ->callback = DeleteMidQEntry;
			spin_unlock(&GlobalMid_Lock);
			add_credits(server, &credits, 0);
			वापस rc;
		पूर्ण
		spin_unlock(&GlobalMid_Lock);
	पूर्ण

	rc = cअगरs_sync_mid_result(midQ, server);
	अगर (rc != 0) अणु
		add_credits(server, &credits, 0);
		वापस rc;
	पूर्ण

	अगर (!midQ->resp_buf || !out_buf ||
	    midQ->mid_state != MID_RESPONSE_RECEIVED) अणु
		rc = -EIO;
		cअगरs_server_dbg(VFS, "Bad MID state?\n");
		जाओ out;
	पूर्ण

	*pbytes_वापसed = get_rfc1002_length(midQ->resp_buf);
	स_नकल(out_buf, midQ->resp_buf, *pbytes_वापसed + 4);
	rc = cअगरs_check_receive(midQ, server, 0);
out:
	cअगरs_delete_mid(midQ);
	add_credits(server, &credits, 0);

	वापस rc;
पूर्ण

/* We send a LOCKINGX_CANCEL_LOCK to cause the Winकरोws
   blocking lock to वापस. */

अटल पूर्णांक
send_lock_cancel(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			काष्ठा smb_hdr *in_buf,
			काष्ठा smb_hdr *out_buf)
अणु
	पूर्णांक bytes_वापसed;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	LOCK_REQ *pSMB = (LOCK_REQ *)in_buf;

	/* We just modअगरy the current in_buf to change
	   the type of lock from LOCKING_ANDX_SHARED_LOCK
	   or LOCKING_ANDX_EXCLUSIVE_LOCK to
	   LOCKING_ANDX_CANCEL_LOCK. */

	pSMB->LockType = LOCKING_ANDX_CANCEL_LOCK|LOCKING_ANDX_LARGE_खाताS;
	pSMB->Timeout = 0;
	pSMB->hdr.Mid = get_next_mid(ses->server);

	वापस SendReceive(xid, ses, in_buf, out_buf,
			&bytes_वापसed, 0);
पूर्ण

पूर्णांक
SendReceiveBlockingLock(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	    काष्ठा smb_hdr *in_buf, काष्ठा smb_hdr *out_buf,
	    पूर्णांक *pbytes_वापसed)
अणु
	पूर्णांक rc = 0;
	पूर्णांक rstart = 0;
	काष्ठा mid_q_entry *midQ;
	काष्ठा cअगरs_ses *ses;
	अचिन्हित पूर्णांक len = be32_to_cpu(in_buf->smb_buf_length);
	काष्ठा kvec iov = अणु .iov_base = in_buf, .iov_len = len पूर्ण;
	काष्ठा smb_rqst rqst = अणु .rq_iov = &iov, .rq_nvec = 1 पूर्ण;
	अचिन्हित पूर्णांक instance;
	काष्ठा TCP_Server_Info *server;

	अगर (tcon == शून्य || tcon->ses == शून्य) अणु
		cअगरs_dbg(VFS, "Null smb session\n");
		वापस -EIO;
	पूर्ण
	ses = tcon->ses;
	server = ses->server;

	अगर (server == शून्य) अणु
		cअगरs_dbg(VFS, "Null tcp session\n");
		वापस -EIO;
	पूर्ण

	अगर (server->tcpStatus == CअगरsExiting)
		वापस -ENOENT;

	/* Ensure that we करो not send more than 50 overlapping requests
	   to the same server. We may make this configurable later or
	   use ses->maxReq */

	अगर (len > CIFSMaxBufSize + MAX_CIFS_HDR_SIZE - 4) अणु
		cअगरs_tcon_dbg(VFS, "Invalid length, greater than maximum frame, %d\n",
			      len);
		वापस -EIO;
	पूर्ण

	rc = रुको_क्रम_मुक्त_request(server, CIFS_BLOCKING_OP, &instance);
	अगर (rc)
		वापस rc;

	/* make sure that we sign in the same order that we send on this socket
	   and aव्योम races inside tcp sendmsg code that could cause corruption
	   of smb data */

	mutex_lock(&server->srv_mutex);

	rc = allocate_mid(ses, in_buf, &midQ);
	अगर (rc) अणु
		mutex_unlock(&server->srv_mutex);
		वापस rc;
	पूर्ण

	rc = cअगरs_sign_smb(in_buf, server, &midQ->sequence_number);
	अगर (rc) अणु
		cअगरs_delete_mid(midQ);
		mutex_unlock(&server->srv_mutex);
		वापस rc;
	पूर्ण

	midQ->mid_state = MID_REQUEST_SUBMITTED;
	cअगरs_in_send_inc(server);
	rc = smb_send(server, in_buf, len);
	cअगरs_in_send_dec(server);
	cअगरs_save_when_sent(midQ);

	अगर (rc < 0)
		server->sequence_number -= 2;

	mutex_unlock(&server->srv_mutex);

	अगर (rc < 0) अणु
		cअगरs_delete_mid(midQ);
		वापस rc;
	पूर्ण

	/* Wait क्रम a reply - allow संकेतs to पूर्णांकerrupt. */
	rc = रुको_event_पूर्णांकerruptible(server->response_q,
		(!(midQ->mid_state == MID_REQUEST_SUBMITTED)) ||
		((server->tcpStatus != CअगरsGood) &&
		 (server->tcpStatus != CअगरsNew)));

	/* Were we पूर्णांकerrupted by a संकेत ? */
	अगर ((rc == -ERESTARTSYS) &&
		(midQ->mid_state == MID_REQUEST_SUBMITTED) &&
		((server->tcpStatus == CअगरsGood) ||
		 (server->tcpStatus == CअगरsNew))) अणु

		अगर (in_buf->Command == SMB_COM_TRANSACTION2) अणु
			/* POSIX lock. We send a NT_CANCEL SMB to cause the
			   blocking lock to वापस. */
			rc = send_cancel(server, &rqst, midQ);
			अगर (rc) अणु
				cअगरs_delete_mid(midQ);
				वापस rc;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Winकरोws lock. We send a LOCKINGX_CANCEL_LOCK
			   to cause the blocking lock to वापस. */

			rc = send_lock_cancel(xid, tcon, in_buf, out_buf);

			/* If we get -ENOLCK back the lock may have
			   alपढ़ोy been हटाओd. Don't निकास in this हाल. */
			अगर (rc && rc != -ENOLCK) अणु
				cअगरs_delete_mid(midQ);
				वापस rc;
			पूर्ण
		पूर्ण

		rc = रुको_क्रम_response(server, midQ);
		अगर (rc) अणु
			send_cancel(server, &rqst, midQ);
			spin_lock(&GlobalMid_Lock);
			अगर (midQ->mid_state == MID_REQUEST_SUBMITTED) अणु
				/* no दीर्घer considered to be "in-flight" */
				midQ->callback = DeleteMidQEntry;
				spin_unlock(&GlobalMid_Lock);
				वापस rc;
			पूर्ण
			spin_unlock(&GlobalMid_Lock);
		पूर्ण

		/* We got the response - restart प्रणाली call. */
		rstart = 1;
	पूर्ण

	rc = cअगरs_sync_mid_result(midQ, server);
	अगर (rc != 0)
		वापस rc;

	/* rcvd frame is ok */
	अगर (out_buf == शून्य || midQ->mid_state != MID_RESPONSE_RECEIVED) अणु
		rc = -EIO;
		cअगरs_tcon_dbg(VFS, "Bad MID state?\n");
		जाओ out;
	पूर्ण

	*pbytes_वापसed = get_rfc1002_length(midQ->resp_buf);
	स_नकल(out_buf, midQ->resp_buf, *pbytes_वापसed + 4);
	rc = cअगरs_check_receive(midQ, server, 0);
out:
	cअगरs_delete_mid(midQ);
	अगर (rstart && rc == -EACCES)
		वापस -ERESTARTSYS;
	वापस rc;
पूर्ण
