<शैली गुरु>
/*
 *   fs/cअगरs/connect.c
 *
 *   Copyright (C) International Business Machines  Corp., 2002,2011
 *   Author(s): Steve French (sfrench@us.ibm.com)
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
#समावेश <linux/net.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/utsname.h>
#समावेश <linux/mempool.h>
#समावेश <linux/delay.h>
#समावेश <linux/completion.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/namei.h>
#समावेश <linux/uuid.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/inet.h>
#समावेश <linux/module.h>
#समावेश <keys/user-type.h>
#समावेश <net/ipv6.h>
#समावेश <linux/parser.h>
#समावेश <linux/bvec.h>
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_unicode.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_fs_sb.h"
#समावेश "ntlmssp.h"
#समावेश "nterr.h"
#समावेश "rfc1002pdu.h"
#समावेश "fscache.h"
#समावेश "smb2proto.h"
#समावेश "smbdirect.h"
#समावेश "dns_resolve.h"
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
#समावेश "dfs_cache.h"
#पूर्ण_अगर
#समावेश "fs_context.h"
#समावेश "cifs_swn.h"

बाह्य mempool_t *cअगरs_req_poolp;
बाह्य bool disable_legacy_dialects;

/* FIXME: should these be tunable? */
#घोषणा TLINK_ERROR_EXPIRE	(1 * HZ)
#घोषणा TLINK_IDLE_EXPIRE	(600 * HZ)

/* Drop the connection to not overload the server */
#घोषणा NUM_STATUS_IO_TIMEOUT   5

अटल पूर्णांक ip_connect(काष्ठा TCP_Server_Info *server);
अटल पूर्णांक generic_ip_connect(काष्ठा TCP_Server_Info *server);
अटल व्योम tlink_rb_insert(काष्ठा rb_root *root, काष्ठा tcon_link *new_tlink);
अटल व्योम cअगरs_prune_tlinks(काष्ठा work_काष्ठा *work);

/*
 * Resolve hostname and set ip addr in tcp ses. Useful क्रम hostnames that may
 * get their ip addresses changed at some poपूर्णांक.
 *
 * This should be called with server->srv_mutex held.
 */
अटल पूर्णांक reconn_set_ipaddr_from_hostname(काष्ठा TCP_Server_Info *server)
अणु
	पूर्णांक rc;
	पूर्णांक len;
	अक्षर *unc, *ipaddr = शून्य;

	अगर (!server->hostname)
		वापस -EINVAL;

	len = म_माप(server->hostname) + 3;

	unc = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!unc) अणु
		cअगरs_dbg(FYI, "%s: failed to create UNC path\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	scnम_लिखो(unc, len, "\\\\%s", server->hostname);

	rc = dns_resolve_server_name_to_ip(unc, &ipaddr);
	kमुक्त(unc);

	अगर (rc < 0) अणु
		cअगरs_dbg(FYI, "%s: failed to resolve server part of %s to IP: %d\n",
			 __func__, server->hostname, rc);
		वापस rc;
	पूर्ण

	spin_lock(&cअगरs_tcp_ses_lock);
	rc = cअगरs_convert_address((काष्ठा sockaddr *)&server->dstaddr, ipaddr,
				  म_माप(ipaddr));
	spin_unlock(&cअगरs_tcp_ses_lock);
	kमुक्त(ipaddr);

	वापस !rc ? -1 : 0;
पूर्ण

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
/* These functions must be called with server->srv_mutex held */
अटल व्योम reconn_set_next_dfs_target(काष्ठा TCP_Server_Info *server,
				       काष्ठा cअगरs_sb_info *cअगरs_sb,
				       काष्ठा dfs_cache_tgt_list *tgt_list,
				       काष्ठा dfs_cache_tgt_iterator **tgt_it)
अणु
	स्थिर अक्षर *name;
	पूर्णांक rc;

	अगर (!cअगरs_sb || !cअगरs_sb->origin_fullpath)
		वापस;

	अगर (!*tgt_it) अणु
		*tgt_it = dfs_cache_get_tgt_iterator(tgt_list);
	पूर्ण अन्यथा अणु
		*tgt_it = dfs_cache_get_next_tgt(tgt_list, *tgt_it);
		अगर (!*tgt_it)
			*tgt_it = dfs_cache_get_tgt_iterator(tgt_list);
	पूर्ण

	cअगरs_dbg(FYI, "%s: UNC: %s\n", __func__, cअगरs_sb->origin_fullpath);

	name = dfs_cache_get_tgt_name(*tgt_it);

	kमुक्त(server->hostname);

	server->hostname = extract_hostname(name);
	अगर (IS_ERR(server->hostname)) अणु
		cअगरs_dbg(FYI,
			 "%s: failed to extract hostname from target: %ld\n",
			 __func__, PTR_ERR(server->hostname));
		वापस;
	पूर्ण

	rc = reconn_set_ipaddr_from_hostname(server);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "%s: failed to resolve hostname: %d\n",
			 __func__, rc);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक reconn_setup_dfs_tarमाला_लो(काष्ठा cअगरs_sb_info *cअगरs_sb,
					   काष्ठा dfs_cache_tgt_list *tl)
अणु
	अगर (!cअगरs_sb->origin_fullpath)
		वापस -EOPNOTSUPP;
	वापस dfs_cache_noreq_find(cअगरs_sb->origin_fullpath + 1, शून्य, tl);
पूर्ण
#पूर्ण_अगर

/*
 * cअगरs tcp session reconnection
 *
 * mark tcp session as reconnecting so temporarily locked
 * mark all smb sessions as reconnecting क्रम tcp session
 * reconnect tcp session
 * wake up रुकोers on reconnection? - (not needed currently)
 */
पूर्णांक
cअगरs_reconnect(काष्ठा TCP_Server_Info *server)
अणु
	पूर्णांक rc = 0;
	काष्ठा list_head *पंचांगp, *पंचांगp2;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा mid_q_entry *mid_entry;
	काष्ठा list_head retry_list;
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	काष्ठा super_block *sb = शून्य;
	काष्ठा cअगरs_sb_info *cअगरs_sb = शून्य;
	काष्ठा dfs_cache_tgt_list tgt_list = अणु0पूर्ण;
	काष्ठा dfs_cache_tgt_iterator *tgt_it = शून्य;
#पूर्ण_अगर

	spin_lock(&GlobalMid_Lock);
	server->nr_tarमाला_लो = 1;
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	spin_unlock(&GlobalMid_Lock);
	sb = cअगरs_get_tcp_super(server);
	अगर (IS_ERR(sb)) अणु
		rc = PTR_ERR(sb);
		cअगरs_dbg(FYI, "%s: will not do DFS failover: rc = %d\n",
			 __func__, rc);
		sb = शून्य;
	पूर्ण अन्यथा अणु
		cअगरs_sb = CIFS_SB(sb);
		rc = reconn_setup_dfs_tarमाला_लो(cअगरs_sb, &tgt_list);
		अगर (rc) अणु
			cअगरs_sb = शून्य;
			अगर (rc != -EOPNOTSUPP) अणु
				cअगरs_server_dbg(VFS, "%s: no target servers for DFS failover\n",
						__func__);
			पूर्ण
		पूर्ण अन्यथा अणु
			server->nr_tarमाला_लो = dfs_cache_get_nr_tgts(&tgt_list);
		पूर्ण
	पूर्ण
	cअगरs_dbg(FYI, "%s: will retry %d target(s)\n", __func__,
		 server->nr_tarमाला_लो);
	spin_lock(&GlobalMid_Lock);
#पूर्ण_अगर
	अगर (server->tcpStatus == CअगरsExiting) अणु
		/* the demux thपढ़ो will निकास normally
		next समय through the loop */
		spin_unlock(&GlobalMid_Lock);
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
		dfs_cache_मुक्त_tgts(&tgt_list);
		cअगरs_put_tcp_super(sb);
#पूर्ण_अगर
		wake_up(&server->response_q);
		वापस rc;
	पूर्ण अन्यथा
		server->tcpStatus = CअगरsNeedReconnect;
	spin_unlock(&GlobalMid_Lock);
	server->maxBuf = 0;
	server->max_पढ़ो = 0;

	cअगरs_dbg(FYI, "Mark tcp session as need reconnect\n");
	trace_smb3_reconnect(server->CurrentMid, server->conn_id, server->hostname);

	/* beक्रमe reconnecting the tcp session, mark the smb session (uid)
		and the tid bad so they are not used until reconnected */
	cअगरs_dbg(FYI, "%s: marking sessions and tcons for reconnect\n",
		 __func__);
	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each(पंचांगp, &server->smb_ses_list) अणु
		ses = list_entry(पंचांगp, काष्ठा cअगरs_ses, smb_ses_list);
		ses->need_reconnect = true;
		list_क्रम_each(पंचांगp2, &ses->tcon_list) अणु
			tcon = list_entry(पंचांगp2, काष्ठा cअगरs_tcon, tcon_list);
			tcon->need_reconnect = true;
		पूर्ण
		अगर (ses->tcon_ipc)
			ses->tcon_ipc->need_reconnect = true;
	पूर्ण
	spin_unlock(&cअगरs_tcp_ses_lock);

	/* करो not want to be sending data on a socket we are मुक्तing */
	cअगरs_dbg(FYI, "%s: tearing down socket\n", __func__);
	mutex_lock(&server->srv_mutex);
	अगर (server->ssocket) अणु
		cअगरs_dbg(FYI, "State: 0x%x Flags: 0x%lx\n",
			 server->ssocket->state, server->ssocket->flags);
		kernel_sock_shutकरोwn(server->ssocket, SHUT_WR);
		cअगरs_dbg(FYI, "Post shutdown state: 0x%x Flags: 0x%lx\n",
			 server->ssocket->state, server->ssocket->flags);
		sock_release(server->ssocket);
		server->ssocket = शून्य;
	पूर्ण
	server->sequence_number = 0;
	server->session_estab = false;
	kमुक्त(server->session_key.response);
	server->session_key.response = शून्य;
	server->session_key.len = 0;
	server->lstrp = jअगरfies;

	/* mark submitted MIDs क्रम retry and issue callback */
	INIT_LIST_HEAD(&retry_list);
	cअगरs_dbg(FYI, "%s: moving mids to private list\n", __func__);
	spin_lock(&GlobalMid_Lock);
	list_क्रम_each_safe(पंचांगp, पंचांगp2, &server->pending_mid_q) अणु
		mid_entry = list_entry(पंचांगp, काष्ठा mid_q_entry, qhead);
		kref_get(&mid_entry->refcount);
		अगर (mid_entry->mid_state == MID_REQUEST_SUBMITTED)
			mid_entry->mid_state = MID_RETRY_NEEDED;
		list_move(&mid_entry->qhead, &retry_list);
		mid_entry->mid_flags |= MID_DELETED;
	पूर्ण
	spin_unlock(&GlobalMid_Lock);
	mutex_unlock(&server->srv_mutex);

	cअगरs_dbg(FYI, "%s: issuing mid callbacks\n", __func__);
	list_क्रम_each_safe(पंचांगp, पंचांगp2, &retry_list) अणु
		mid_entry = list_entry(पंचांगp, काष्ठा mid_q_entry, qhead);
		list_del_init(&mid_entry->qhead);
		mid_entry->callback(mid_entry);
		cअगरs_mid_q_entry_release(mid_entry);
	पूर्ण

	अगर (cअगरs_rdma_enabled(server)) अणु
		mutex_lock(&server->srv_mutex);
		smbd_destroy(server);
		mutex_unlock(&server->srv_mutex);
	पूर्ण

	करो अणु
		try_to_मुक्तze();

		mutex_lock(&server->srv_mutex);


		अगर (!cअगरs_swn_set_server_dstaddr(server)) अणु
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
		अगर (cअगरs_sb && cअगरs_sb->origin_fullpath)
			/*
			 * Set up next DFS target server (अगर any) क्रम reconnect. If DFS
			 * feature is disabled, then we will retry last server we
			 * connected to beक्रमe.
			 */
			reconn_set_next_dfs_target(server, cअगरs_sb, &tgt_list, &tgt_it);
		अन्यथा अणु
#पूर्ण_अगर
			/*
			 * Resolve the hostname again to make sure that IP address is up-to-date.
			 */
			rc = reconn_set_ipaddr_from_hostname(server);
			अगर (rc) अणु
				cअगरs_dbg(FYI, "%s: failed to resolve hostname: %d\n",
						__func__, rc);
			पूर्ण

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
		पूर्ण
#पूर्ण_अगर


		पूर्ण

		अगर (cअगरs_rdma_enabled(server))
			rc = smbd_reconnect(server);
		अन्यथा
			rc = generic_ip_connect(server);
		अगर (rc) अणु
			cअगरs_dbg(FYI, "reconnect error %d\n", rc);
			mutex_unlock(&server->srv_mutex);
			msleep(3000);
		पूर्ण अन्यथा अणु
			atomic_inc(&tcpSesReconnectCount);
			set_credits(server, 1);
			spin_lock(&GlobalMid_Lock);
			अगर (server->tcpStatus != CअगरsExiting)
				server->tcpStatus = CअगरsNeedNegotiate;
			spin_unlock(&GlobalMid_Lock);
			cअगरs_swn_reset_server_dstaddr(server);
			mutex_unlock(&server->srv_mutex);
		पूर्ण
	पूर्ण जबतक (server->tcpStatus == CअगरsNeedReconnect);

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	अगर (tgt_it) अणु
		rc = dfs_cache_noreq_update_tgthपूर्णांक(cअगरs_sb->origin_fullpath + 1,
						    tgt_it);
		अगर (rc) अणु
			cअगरs_server_dbg(VFS, "%s: failed to update DFS target hint: rc = %d\n",
				 __func__, rc);
		पूर्ण
		rc = dfs_cache_update_vol(cअगरs_sb->origin_fullpath, server);
		अगर (rc) अणु
			cअगरs_server_dbg(VFS, "%s: failed to update vol info in DFS cache: rc = %d\n",
				 __func__, rc);
		पूर्ण
		dfs_cache_मुक्त_tgts(&tgt_list);

	पूर्ण

	cअगरs_put_tcp_super(sb);
#पूर्ण_अगर
	अगर (server->tcpStatus == CअगरsNeedNegotiate)
		mod_delayed_work(cअगरsiod_wq, &server->echo, 0);

	wake_up(&server->response_q);
	वापस rc;
पूर्ण

अटल व्योम
cअगरs_echo_request(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक rc;
	काष्ठा TCP_Server_Info *server = container_of(work,
					काष्ठा TCP_Server_Info, echo.work);

	/*
	 * We cannot send an echo अगर it is disabled.
	 * Also, no need to ping अगर we got a response recently.
	 */

	अगर (server->tcpStatus == CअगरsNeedReconnect ||
	    server->tcpStatus == CअगरsExiting ||
	    server->tcpStatus == CअगरsNew ||
	    (server->ops->can_echo && !server->ops->can_echo(server)) ||
	    समय_beक्रमe(jअगरfies, server->lstrp + server->echo_पूर्णांकerval - HZ))
		जाओ requeue_echo;

	rc = server->ops->echo ? server->ops->echo(server) : -ENOSYS;
	अगर (rc)
		cअगरs_dbg(FYI, "Unable to send echo request to server: %s\n",
			 server->hostname);

	/* Check witness registrations */
	cअगरs_swn_check();

requeue_echo:
	queue_delayed_work(cअगरsiod_wq, &server->echo, server->echo_पूर्णांकerval);
पूर्ण

अटल bool
allocate_buffers(काष्ठा TCP_Server_Info *server)
अणु
	अगर (!server->bigbuf) अणु
		server->bigbuf = (अक्षर *)cअगरs_buf_get();
		अगर (!server->bigbuf) अणु
			cअगरs_server_dbg(VFS, "No memory for large SMB response\n");
			msleep(3000);
			/* retry will check अगर निकासing */
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अगर (server->large_buf) अणु
		/* we are reusing a dirty large buf, clear its start */
		स_रखो(server->bigbuf, 0, HEADER_SIZE(server));
	पूर्ण

	अगर (!server->smallbuf) अणु
		server->smallbuf = (अक्षर *)cअगरs_small_buf_get();
		अगर (!server->smallbuf) अणु
			cअगरs_server_dbg(VFS, "No memory for SMB response\n");
			msleep(1000);
			/* retry will check अगर निकासing */
			वापस false;
		पूर्ण
		/* beginning of smb buffer is cleared in our buf_get */
	पूर्ण अन्यथा अणु
		/* अगर existing small buf clear beginning */
		स_रखो(server->smallbuf, 0, HEADER_SIZE(server));
	पूर्ण

	वापस true;
पूर्ण

अटल bool
server_unresponsive(काष्ठा TCP_Server_Info *server)
अणु
	/*
	 * We need to रुको 3 echo पूर्णांकervals to make sure we handle such
	 * situations right:
	 * 1s  client sends a normal SMB request
	 * 2s  client माला_लो a response
	 * 30s echo workqueue job pops, and decides we got a response recently
	 *     and करोn't need to send another
	 * ...
	 * 65s kernel_recvmsg बार out, and we see that we haven't gotten
	 *     a response in >60s.
	 */
	अगर ((server->tcpStatus == CअगरsGood ||
	    server->tcpStatus == CअगरsNeedNegotiate) &&
	    (!server->ops->can_echo || server->ops->can_echo(server)) &&
	    समय_after(jअगरfies, server->lstrp + 3 * server->echo_पूर्णांकerval)) अणु
		cअगरs_server_dbg(VFS, "has not responded in %lu seconds. Reconnecting...\n",
			 (3 * server->echo_पूर्णांकerval) / HZ);
		cअगरs_reconnect(server);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत bool
zero_credits(काष्ठा TCP_Server_Info *server)
अणु
	पूर्णांक val;

	spin_lock(&server->req_lock);
	val = server->credits + server->echo_credits + server->oplock_credits;
	अगर (server->in_flight == 0 && val == 0) अणु
		spin_unlock(&server->req_lock);
		वापस true;
	पूर्ण
	spin_unlock(&server->req_lock);
	वापस false;
पूर्ण

अटल पूर्णांक
cअगरs_पढ़ोv_from_socket(काष्ठा TCP_Server_Info *server, काष्ठा msghdr *smb_msg)
अणु
	पूर्णांक length = 0;
	पूर्णांक total_पढ़ो;

	smb_msg->msg_control = शून्य;
	smb_msg->msg_controllen = 0;

	क्रम (total_पढ़ो = 0; msg_data_left(smb_msg); total_पढ़ो += length) अणु
		try_to_मुक्तze();

		/* reconnect अगर no credits and no requests in flight */
		अगर (zero_credits(server)) अणु
			cअगरs_reconnect(server);
			वापस -ECONNABORTED;
		पूर्ण

		अगर (server_unresponsive(server))
			वापस -ECONNABORTED;
		अगर (cअगरs_rdma_enabled(server) && server->smbd_conn)
			length = smbd_recv(server->smbd_conn, smb_msg);
		अन्यथा
			length = sock_recvmsg(server->ssocket, smb_msg, 0);

		अगर (server->tcpStatus == CअगरsExiting)
			वापस -ESHUTDOWN;

		अगर (server->tcpStatus == CअगरsNeedReconnect) अणु
			cअगरs_reconnect(server);
			वापस -ECONNABORTED;
		पूर्ण

		अगर (length == -ERESTARTSYS ||
		    length == -EAGAIN ||
		    length == -EINTR) अणु
			/*
			 * Minimum sleep to prevent looping, allowing socket
			 * to clear and app thपढ़ोs to set tcpStatus
			 * CअगरsNeedReconnect अगर server hung.
			 */
			usleep_range(1000, 2000);
			length = 0;
			जारी;
		पूर्ण

		अगर (length <= 0) अणु
			cअगरs_dbg(FYI, "Received no data or error: %d\n", length);
			cअगरs_reconnect(server);
			वापस -ECONNABORTED;
		पूर्ण
	पूर्ण
	वापस total_पढ़ो;
पूर्ण

पूर्णांक
cअगरs_पढ़ो_from_socket(काष्ठा TCP_Server_Info *server, अक्षर *buf,
		      अचिन्हित पूर्णांक to_पढ़ो)
अणु
	काष्ठा msghdr smb_msg;
	काष्ठा kvec iov = अणु.iov_base = buf, .iov_len = to_पढ़ोपूर्ण;
	iov_iter_kvec(&smb_msg.msg_iter, READ, &iov, 1, to_पढ़ो);

	वापस cअगरs_पढ़ोv_from_socket(server, &smb_msg);
पूर्ण

sमाप_प्रकार
cअगरs_discard_from_socket(काष्ठा TCP_Server_Info *server, माप_प्रकार to_पढ़ो)
अणु
	काष्ठा msghdr smb_msg;

	/*
	 *  iov_iter_discard alपढ़ोy sets smb_msg.type and count and iov_offset
	 *  and cअगरs_पढ़ोv_from_socket sets msg_control and msg_controllen
	 *  so little to initialize in काष्ठा msghdr
	 */
	smb_msg.msg_name = शून्य;
	smb_msg.msg_namelen = 0;
	iov_iter_discard(&smb_msg.msg_iter, READ, to_पढ़ो);

	वापस cअगरs_पढ़ोv_from_socket(server, &smb_msg);
पूर्ण

पूर्णांक
cअगरs_पढ़ो_page_from_socket(काष्ठा TCP_Server_Info *server, काष्ठा page *page,
	अचिन्हित पूर्णांक page_offset, अचिन्हित पूर्णांक to_पढ़ो)
अणु
	काष्ठा msghdr smb_msg;
	काष्ठा bio_vec bv = अणु
		.bv_page = page, .bv_len = to_पढ़ो, .bv_offset = page_offsetपूर्ण;
	iov_iter_bvec(&smb_msg.msg_iter, READ, &bv, 1, to_पढ़ो);
	वापस cअगरs_पढ़ोv_from_socket(server, &smb_msg);
पूर्ण

अटल bool
is_smb_response(काष्ठा TCP_Server_Info *server, अचिन्हित अक्षर type)
अणु
	/*
	 * The first byte big endian of the length field,
	 * is actually not part of the length but the type
	 * with the most common, zero, as regular data.
	 */
	चयन (type) अणु
	हाल RFC1002_SESSION_MESSAGE:
		/* Regular SMB response */
		वापस true;
	हाल RFC1002_SESSION_KEEP_ALIVE:
		cअगरs_dbg(FYI, "RFC 1002 session keep alive\n");
		अवरोध;
	हाल RFC1002_POSITIVE_SESSION_RESPONSE:
		cअगरs_dbg(FYI, "RFC 1002 positive session response\n");
		अवरोध;
	हाल RFC1002_NEGATIVE_SESSION_RESPONSE:
		/*
		 * We get this from Winकरोws 98 instead of an error on
		 * SMB negprot response.
		 */
		cअगरs_dbg(FYI, "RFC 1002 negative session response\n");
		/* give server a second to clean up */
		msleep(1000);
		/*
		 * Always try 445 first on reconnect since we get NACK
		 * on some अगर we ever connected to port 139 (the NACK
		 * is since we करो not begin with RFC1001 session
		 * initialize frame).
		 */
		cअगरs_set_port((काष्ठा sockaddr *)&server->dstaddr, CIFS_PORT);
		cअगरs_reconnect(server);
		अवरोध;
	शेष:
		cअगरs_server_dbg(VFS, "RFC 1002 unknown response type 0x%x\n", type);
		cअगरs_reconnect(server);
	पूर्ण

	वापस false;
पूर्ण

व्योम
dequeue_mid(काष्ठा mid_q_entry *mid, bool malक्रमmed)
अणु
#अगर_घोषित CONFIG_CIFS_STATS2
	mid->when_received = jअगरfies;
#पूर्ण_अगर
	spin_lock(&GlobalMid_Lock);
	अगर (!malक्रमmed)
		mid->mid_state = MID_RESPONSE_RECEIVED;
	अन्यथा
		mid->mid_state = MID_RESPONSE_MALFORMED;
	/*
	 * Trying to handle/dequeue a mid after the send_recv()
	 * function has finished processing it is a bug.
	 */
	अगर (mid->mid_flags & MID_DELETED)
		pr_warn_once("trying to dequeue a deleted mid\n");
	अन्यथा अणु
		list_del_init(&mid->qhead);
		mid->mid_flags |= MID_DELETED;
	पूर्ण
	spin_unlock(&GlobalMid_Lock);
पूर्ण

अटल अचिन्हित पूर्णांक
smb2_get_credits_from_hdr(अक्षर *buffer, काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा smb2_sync_hdr *shdr = (काष्ठा smb2_sync_hdr *)buffer;

	/*
	 * SMB1 करोes not use credits.
	 */
	अगर (server->vals->header_preamble_size)
		वापस 0;

	वापस le16_to_cpu(shdr->CreditRequest);
पूर्ण

अटल व्योम
handle_mid(काष्ठा mid_q_entry *mid, काष्ठा TCP_Server_Info *server,
	   अक्षर *buf, पूर्णांक malक्रमmed)
अणु
	अगर (server->ops->check_trans2 &&
	    server->ops->check_trans2(mid, server, buf, malक्रमmed))
		वापस;
	mid->credits_received = smb2_get_credits_from_hdr(buf, server);
	mid->resp_buf = buf;
	mid->large_buf = server->large_buf;
	/* Was previous buf put in mpx काष्ठा क्रम multi-rsp? */
	अगर (!mid->multiRsp) अणु
		/* smb buffer will be मुक्तd by user thपढ़ो */
		अगर (server->large_buf)
			server->bigbuf = शून्य;
		अन्यथा
			server->smallbuf = शून्य;
	पूर्ण
	dequeue_mid(mid, malक्रमmed);
पूर्ण

अटल व्योम clean_demultiplex_info(काष्ठा TCP_Server_Info *server)
अणु
	पूर्णांक length;

	/* take it off the list, अगर it's not alपढ़ोy */
	spin_lock(&cअगरs_tcp_ses_lock);
	list_del_init(&server->tcp_ses_list);
	spin_unlock(&cअगरs_tcp_ses_lock);

	cancel_delayed_work_sync(&server->echo);

	spin_lock(&GlobalMid_Lock);
	server->tcpStatus = CअगरsExiting;
	spin_unlock(&GlobalMid_Lock);
	wake_up_all(&server->response_q);

	/* check अगर we have blocked requests that need to मुक्त */
	spin_lock(&server->req_lock);
	अगर (server->credits <= 0)
		server->credits = 1;
	spin_unlock(&server->req_lock);
	/*
	 * Although there should not be any requests blocked on this queue it
	 * can not hurt to be paranoid and try to wake up requests that may
	 * haven been blocked when more than 50 at समय were on the wire to the
	 * same server - they now will see the session is in निकास state and get
	 * out of SendReceive.
	 */
	wake_up_all(&server->request_q);
	/* give those requests समय to निकास */
	msleep(125);
	अगर (cअगरs_rdma_enabled(server))
		smbd_destroy(server);
	अगर (server->ssocket) अणु
		sock_release(server->ssocket);
		server->ssocket = शून्य;
	पूर्ण

	अगर (!list_empty(&server->pending_mid_q)) अणु
		काष्ठा list_head dispose_list;
		काष्ठा mid_q_entry *mid_entry;
		काष्ठा list_head *पंचांगp, *पंचांगp2;

		INIT_LIST_HEAD(&dispose_list);
		spin_lock(&GlobalMid_Lock);
		list_क्रम_each_safe(पंचांगp, पंचांगp2, &server->pending_mid_q) अणु
			mid_entry = list_entry(पंचांगp, काष्ठा mid_q_entry, qhead);
			cअगरs_dbg(FYI, "Clearing mid %llu\n", mid_entry->mid);
			kref_get(&mid_entry->refcount);
			mid_entry->mid_state = MID_SHUTDOWN;
			list_move(&mid_entry->qhead, &dispose_list);
			mid_entry->mid_flags |= MID_DELETED;
		पूर्ण
		spin_unlock(&GlobalMid_Lock);

		/* now walk dispose list and issue callbacks */
		list_क्रम_each_safe(पंचांगp, पंचांगp2, &dispose_list) अणु
			mid_entry = list_entry(पंचांगp, काष्ठा mid_q_entry, qhead);
			cअगरs_dbg(FYI, "Callback mid %llu\n", mid_entry->mid);
			list_del_init(&mid_entry->qhead);
			mid_entry->callback(mid_entry);
			cअगरs_mid_q_entry_release(mid_entry);
		पूर्ण
		/* 1/8th of sec is more than enough समय क्रम them to निकास */
		msleep(125);
	पूर्ण

	अगर (!list_empty(&server->pending_mid_q)) अणु
		/*
		 * mpx thपढ़ोs have not निकासed yet give them at least the smb
		 * send समयout समय क्रम दीर्घ ops.
		 *
		 * Due to delays on oplock अवरोध requests, we need to रुको at
		 * least 45 seconds beक्रमe giving up on a request getting a
		 * response and going ahead and समाप्तing cअगरsd.
		 */
		cअगरs_dbg(FYI, "Wait for exit from demultiplex thread\n");
		msleep(46000);
		/*
		 * If thपढ़ोs still have not निकासed they are probably never
		 * coming home not much अन्यथा we can करो but मुक्त the memory.
		 */
	पूर्ण

	kमुक्त(server->hostname);
	kमुक्त(server);

	length = atomic_dec_वापस(&tcpSesAllocCount);
	अगर (length > 0)
		mempool_resize(cअगरs_req_poolp, length + cअगरs_min_rcv);
पूर्ण

अटल पूर्णांक
standard_receive3(काष्ठा TCP_Server_Info *server, काष्ठा mid_q_entry *mid)
अणु
	पूर्णांक length;
	अक्षर *buf = server->smallbuf;
	अचिन्हित पूर्णांक pdu_length = server->pdu_size;

	/* make sure this will fit in a large buffer */
	अगर (pdu_length > CIFSMaxBufSize + MAX_HEADER_SIZE(server) -
		server->vals->header_preamble_size) अणु
		cअगरs_server_dbg(VFS, "SMB response too long (%u bytes)\n", pdu_length);
		cअगरs_reconnect(server);
		वापस -ECONNABORTED;
	पूर्ण

	/* चयन to large buffer अगर too big क्रम a small one */
	अगर (pdu_length > MAX_CIFS_SMALL_BUFFER_SIZE - 4) अणु
		server->large_buf = true;
		स_नकल(server->bigbuf, buf, server->total_पढ़ो);
		buf = server->bigbuf;
	पूर्ण

	/* now पढ़ो the rest */
	length = cअगरs_पढ़ो_from_socket(server, buf + HEADER_SIZE(server) - 1,
				       pdu_length - HEADER_SIZE(server) + 1
				       + server->vals->header_preamble_size);

	अगर (length < 0)
		वापस length;
	server->total_पढ़ो += length;

	dump_smb(buf, server->total_पढ़ो);

	वापस cअगरs_handle_standard(server, mid);
पूर्ण

पूर्णांक
cअगरs_handle_standard(काष्ठा TCP_Server_Info *server, काष्ठा mid_q_entry *mid)
अणु
	अक्षर *buf = server->large_buf ? server->bigbuf : server->smallbuf;
	पूर्णांक length;

	/*
	 * We know that we received enough to get to the MID as we
	 * checked the pdu_length earlier. Now check to see
	 * अगर the rest of the header is OK. We borrow the length
	 * var क्रम the rest of the loop to aव्योम a new stack var.
	 *
	 * 48 bytes is enough to display the header and a little bit
	 * पूर्णांकo the payload क्रम debugging purposes.
	 */
	length = server->ops->check_message(buf, server->total_पढ़ो, server);
	अगर (length != 0)
		cअगरs_dump_mem("Bad SMB: ", buf,
			min_t(अचिन्हित पूर्णांक, server->total_पढ़ो, 48));

	अगर (server->ops->is_session_expired &&
	    server->ops->is_session_expired(buf)) अणु
		cअगरs_reconnect(server);
		वापस -1;
	पूर्ण

	अगर (server->ops->is_status_pending &&
	    server->ops->is_status_pending(buf, server))
		वापस -1;

	अगर (!mid)
		वापस length;

	handle_mid(mid, server, buf, length);
	वापस 0;
पूर्ण

अटल व्योम
smb2_add_credits_from_hdr(अक्षर *buffer, काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा smb2_sync_hdr *shdr = (काष्ठा smb2_sync_hdr *)buffer;
	पूर्णांक scredits, in_flight;

	/*
	 * SMB1 करोes not use credits.
	 */
	अगर (server->vals->header_preamble_size)
		वापस;

	अगर (shdr->CreditRequest) अणु
		spin_lock(&server->req_lock);
		server->credits += le16_to_cpu(shdr->CreditRequest);
		scredits = server->credits;
		in_flight = server->in_flight;
		spin_unlock(&server->req_lock);
		wake_up(&server->request_q);

		trace_smb3_add_credits(server->CurrentMid,
				server->conn_id, server->hostname, scredits,
				le16_to_cpu(shdr->CreditRequest), in_flight);
		cअगरs_server_dbg(FYI, "%s: added %u credits total=%d\n",
				__func__, le16_to_cpu(shdr->CreditRequest),
				scredits);
	पूर्ण
पूर्ण


अटल पूर्णांक
cअगरs_demultiplex_thपढ़ो(व्योम *p)
अणु
	पूर्णांक i, num_mids, length;
	काष्ठा TCP_Server_Info *server = p;
	अचिन्हित पूर्णांक pdu_length;
	अचिन्हित पूर्णांक next_offset;
	अक्षर *buf = शून्य;
	काष्ठा task_काष्ठा *task_to_wake = शून्य;
	काष्ठा mid_q_entry *mids[MAX_COMPOUND];
	अक्षर *bufs[MAX_COMPOUND];
	अचिन्हित पूर्णांक noreclaim_flag, num_io_समयout = 0;

	noreclaim_flag = meदो_स्मृति_noreclaim_save();
	cअगरs_dbg(FYI, "Demultiplex PID: %d\n", task_pid_nr(current));

	length = atomic_inc_वापस(&tcpSesAllocCount);
	अगर (length > 1)
		mempool_resize(cअगरs_req_poolp, length + cअगरs_min_rcv);

	set_मुक्तzable();
	allow_kernel_संकेत(SIGKILL);
	जबतक (server->tcpStatus != CअगरsExiting) अणु
		अगर (try_to_मुक्तze())
			जारी;

		अगर (!allocate_buffers(server))
			जारी;

		server->large_buf = false;
		buf = server->smallbuf;
		pdu_length = 4; /* enough to get RFC1001 header */

		length = cअगरs_पढ़ो_from_socket(server, buf, pdu_length);
		अगर (length < 0)
			जारी;

		अगर (server->vals->header_preamble_size == 0)
			server->total_पढ़ो = 0;
		अन्यथा
			server->total_पढ़ो = length;

		/*
		 * The right amount was पढ़ो from socket - 4 bytes,
		 * so we can now पूर्णांकerpret the length field.
		 */
		pdu_length = get_rfc1002_length(buf);

		cअगरs_dbg(FYI, "RFC1002 header 0x%x\n", pdu_length);
		अगर (!is_smb_response(server, buf[0]))
			जारी;
next_pdu:
		server->pdu_size = pdu_length;

		/* make sure we have enough to get to the MID */
		अगर (server->pdu_size < HEADER_SIZE(server) - 1 -
		    server->vals->header_preamble_size) अणु
			cअगरs_server_dbg(VFS, "SMB response too short (%u bytes)\n",
				 server->pdu_size);
			cअगरs_reconnect(server);
			जारी;
		पूर्ण

		/* पढ़ो करोwn to the MID */
		length = cअगरs_पढ़ो_from_socket(server,
			     buf + server->vals->header_preamble_size,
			     HEADER_SIZE(server) - 1
			     - server->vals->header_preamble_size);
		अगर (length < 0)
			जारी;
		server->total_पढ़ो += length;

		अगर (server->ops->next_header) अणु
			next_offset = server->ops->next_header(buf);
			अगर (next_offset)
				server->pdu_size = next_offset;
		पूर्ण

		स_रखो(mids, 0, माप(mids));
		स_रखो(bufs, 0, माप(bufs));
		num_mids = 0;

		अगर (server->ops->is_transक्रमm_hdr &&
		    server->ops->receive_transक्रमm &&
		    server->ops->is_transक्रमm_hdr(buf)) अणु
			length = server->ops->receive_transक्रमm(server,
								mids,
								bufs,
								&num_mids);
		पूर्ण अन्यथा अणु
			mids[0] = server->ops->find_mid(server, buf);
			bufs[0] = buf;
			num_mids = 1;

			अगर (!mids[0] || !mids[0]->receive)
				length = standard_receive3(server, mids[0]);
			अन्यथा
				length = mids[0]->receive(server, mids[0]);
		पूर्ण

		अगर (length < 0) अणु
			क्रम (i = 0; i < num_mids; i++)
				अगर (mids[i])
					cअगरs_mid_q_entry_release(mids[i]);
			जारी;
		पूर्ण

		अगर (server->ops->is_status_io_समयout &&
		    server->ops->is_status_io_समयout(buf)) अणु
			num_io_समयout++;
			अगर (num_io_समयout > NUM_STATUS_IO_TIMEOUT) अणु
				cअगरs_reconnect(server);
				num_io_समयout = 0;
				जारी;
			पूर्ण
		पूर्ण

		server->lstrp = jअगरfies;

		क्रम (i = 0; i < num_mids; i++) अणु
			अगर (mids[i] != शून्य) अणु
				mids[i]->resp_buf_size = server->pdu_size;

				अगर (bufs[i] && server->ops->is_network_name_deleted)
					server->ops->is_network_name_deleted(bufs[i],
									server);

				अगर (!mids[i]->multiRsp || mids[i]->multiEnd)
					mids[i]->callback(mids[i]);

				cअगरs_mid_q_entry_release(mids[i]);
			पूर्ण अन्यथा अगर (server->ops->is_oplock_अवरोध &&
				   server->ops->is_oplock_अवरोध(bufs[i],
								server)) अणु
				smb2_add_credits_from_hdr(bufs[i], server);
				cअगरs_dbg(FYI, "Received oplock break\n");
			पूर्ण अन्यथा अणु
				cअगरs_server_dbg(VFS, "No task to wake, unknown frame received! NumMids %d\n",
						atomic_पढ़ो(&midCount));
				cअगरs_dump_mem("Received Data is: ", bufs[i],
					      HEADER_SIZE(server));
				smb2_add_credits_from_hdr(bufs[i], server);
#अगर_घोषित CONFIG_CIFS_DEBUG2
				अगर (server->ops->dump_detail)
					server->ops->dump_detail(bufs[i],
								 server);
				cअगरs_dump_mids(server);
#पूर्ण_अगर /* CIFS_DEBUG2 */
			पूर्ण
		पूर्ण

		अगर (pdu_length > server->pdu_size) अणु
			अगर (!allocate_buffers(server))
				जारी;
			pdu_length -= server->pdu_size;
			server->total_पढ़ो = 0;
			server->large_buf = false;
			buf = server->smallbuf;
			जाओ next_pdu;
		पूर्ण
	पूर्ण /* end जबतक !EXITING */

	/* buffer usually मुक्तd in मुक्त_mid - need to मुक्त it here on निकास */
	cअगरs_buf_release(server->bigbuf);
	अगर (server->smallbuf) /* no sense logging a debug message अगर शून्य */
		cअगरs_small_buf_release(server->smallbuf);

	task_to_wake = xchg(&server->tsk, शून्य);
	clean_demultiplex_info(server);

	/* अगर server->tsk was शून्य then रुको क्रम a संकेत beक्रमe निकासing */
	अगर (!task_to_wake) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		जबतक (!संकेत_pending(current)) अणु
			schedule();
			set_current_state(TASK_INTERRUPTIBLE);
		पूर्ण
		set_current_state(TASK_RUNNING);
	पूर्ण

	meदो_स्मृति_noreclaim_restore(noreclaim_flag);
	module_put_and_निकास(0);
पूर्ण

/**
 * Returns true अगर srcaddr isn't specified and rhs isn't specअगरied, or
 * अगर srcaddr is specअगरied and matches the IP address of the rhs argument
 */
bool
cअगरs_match_ipaddr(काष्ठा sockaddr *srcaddr, काष्ठा sockaddr *rhs)
अणु
	चयन (srcaddr->sa_family) अणु
	हाल AF_UNSPEC:
		वापस (rhs->sa_family == AF_UNSPEC);
	हाल AF_INET: अणु
		काष्ठा sockaddr_in *saddr4 = (काष्ठा sockaddr_in *)srcaddr;
		काष्ठा sockaddr_in *vaddr4 = (काष्ठा sockaddr_in *)rhs;
		वापस (saddr4->sin_addr.s_addr == vaddr4->sin_addr.s_addr);
	पूर्ण
	हाल AF_INET6: अणु
		काष्ठा sockaddr_in6 *saddr6 = (काष्ठा sockaddr_in6 *)srcaddr;
		काष्ठा sockaddr_in6 *vaddr6 = (काष्ठा sockaddr_in6 *)rhs;
		वापस ipv6_addr_equal(&saddr6->sin6_addr, &vaddr6->sin6_addr);
	पूर्ण
	शेष:
		WARN_ON(1);
		वापस false; /* करोn't expect to be here */
	पूर्ण
पूर्ण

/*
 * If no port is specअगरied in addr काष्ठाure, we try to match with 445 port
 * and अगर it fails - with 139 ports. It should be called only अगर address
 * families of server and addr are equal.
 */
अटल bool
match_port(काष्ठा TCP_Server_Info *server, काष्ठा sockaddr *addr)
अणु
	__be16 port, *sport;

	/* SMBDirect manages its own ports, करोn't match it here */
	अगर (server->rdma)
		वापस true;

	चयन (addr->sa_family) अणु
	हाल AF_INET:
		sport = &((काष्ठा sockaddr_in *) &server->dstaddr)->sin_port;
		port = ((काष्ठा sockaddr_in *) addr)->sin_port;
		अवरोध;
	हाल AF_INET6:
		sport = &((काष्ठा sockaddr_in6 *) &server->dstaddr)->sin6_port;
		port = ((काष्ठा sockaddr_in6 *) addr)->sin6_port;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस false;
	पूर्ण

	अगर (!port) अणु
		port = htons(CIFS_PORT);
		अगर (port == *sport)
			वापस true;

		port = htons(RFC1001_PORT);
	पूर्ण

	वापस port == *sport;
पूर्ण

अटल bool
match_address(काष्ठा TCP_Server_Info *server, काष्ठा sockaddr *addr,
	      काष्ठा sockaddr *srcaddr)
अणु
	चयन (addr->sa_family) अणु
	हाल AF_INET: अणु
		काष्ठा sockaddr_in *addr4 = (काष्ठा sockaddr_in *)addr;
		काष्ठा sockaddr_in *srv_addr4 =
					(काष्ठा sockaddr_in *)&server->dstaddr;

		अगर (addr4->sin_addr.s_addr != srv_addr4->sin_addr.s_addr)
			वापस false;
		अवरोध;
	पूर्ण
	हाल AF_INET6: अणु
		काष्ठा sockaddr_in6 *addr6 = (काष्ठा sockaddr_in6 *)addr;
		काष्ठा sockaddr_in6 *srv_addr6 =
					(काष्ठा sockaddr_in6 *)&server->dstaddr;

		अगर (!ipv6_addr_equal(&addr6->sin6_addr,
				     &srv_addr6->sin6_addr))
			वापस false;
		अगर (addr6->sin6_scope_id != srv_addr6->sin6_scope_id)
			वापस false;
		अवरोध;
	पूर्ण
	शेष:
		WARN_ON(1);
		वापस false; /* करोn't expect to be here */
	पूर्ण

	अगर (!cअगरs_match_ipaddr(srcaddr, (काष्ठा sockaddr *)&server->srcaddr))
		वापस false;

	वापस true;
पूर्ण

अटल bool
match_security(काष्ठा TCP_Server_Info *server, काष्ठा smb3_fs_context *ctx)
अणु
	/*
	 * The select_sectype function should either वापस the ctx->sectype
	 * that was specअगरied, or "Unspecified" अगर that sectype was not
	 * compatible with the given NEGOTIATE request.
	 */
	अगर (server->ops->select_sectype(server, ctx->sectype)
	     == Unspecअगरied)
		वापस false;

	/*
	 * Now check अगर signing mode is acceptable. No need to check
	 * global_secflags at this poपूर्णांक since अगर MUST_SIGN is set then
	 * the server->sign had better be too.
	 */
	अगर (ctx->sign && !server->sign)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक match_server(काष्ठा TCP_Server_Info *server, काष्ठा smb3_fs_context *ctx)
अणु
	काष्ठा sockaddr *addr = (काष्ठा sockaddr *)&ctx->dstaddr;

	अगर (ctx->nosharesock)
		वापस 0;

	/* If multidialect negotiation see अगर existing sessions match one */
	अगर (म_भेद(ctx->vals->version_string, SMB3ANY_VERSION_STRING) == 0) अणु
		अगर (server->vals->protocol_id < SMB30_PROT_ID)
			वापस 0;
	पूर्ण अन्यथा अगर (म_भेद(ctx->vals->version_string,
		   SMBDEFAULT_VERSION_STRING) == 0) अणु
		अगर (server->vals->protocol_id < SMB21_PROT_ID)
			वापस 0;
	पूर्ण अन्यथा अगर ((server->vals != ctx->vals) || (server->ops != ctx->ops))
		वापस 0;

	अगर (!net_eq(cअगरs_net_ns(server), current->nsproxy->net_ns))
		वापस 0;

	अगर (!match_address(server, addr,
			   (काष्ठा sockaddr *)&ctx->srcaddr))
		वापस 0;

	अगर (!match_port(server, addr))
		वापस 0;

	अगर (!match_security(server, ctx))
		वापस 0;

	अगर (server->echo_पूर्णांकerval != ctx->echo_पूर्णांकerval * HZ)
		वापस 0;

	अगर (server->rdma != ctx->rdma)
		वापस 0;

	अगर (server->ignore_signature != ctx->ignore_signature)
		वापस 0;

	अगर (server->min_offload != ctx->min_offload)
		वापस 0;

	वापस 1;
पूर्ण

काष्ठा TCP_Server_Info *
cअगरs_find_tcp_session(काष्ठा smb3_fs_context *ctx)
अणु
	काष्ठा TCP_Server_Info *server;

	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each_entry(server, &cअगरs_tcp_ses_list, tcp_ses_list) अणु
		/*
		 * Skip ses channels since they're only handled in lower layers
		 * (e.g. cअगरs_send_recv).
		 */
		अगर (server->is_channel || !match_server(server, ctx))
			जारी;

		++server->srv_count;
		spin_unlock(&cअगरs_tcp_ses_lock);
		cअगरs_dbg(FYI, "Existing tcp session with server found\n");
		वापस server;
	पूर्ण
	spin_unlock(&cअगरs_tcp_ses_lock);
	वापस शून्य;
पूर्ण

व्योम
cअगरs_put_tcp_session(काष्ठा TCP_Server_Info *server, पूर्णांक from_reconnect)
अणु
	काष्ठा task_काष्ठा *task;

	spin_lock(&cअगरs_tcp_ses_lock);
	अगर (--server->srv_count > 0) अणु
		spin_unlock(&cअगरs_tcp_ses_lock);
		वापस;
	पूर्ण

	put_net(cअगरs_net_ns(server));

	list_del_init(&server->tcp_ses_list);
	spin_unlock(&cअगरs_tcp_ses_lock);

	cancel_delayed_work_sync(&server->echo);

	अगर (from_reconnect)
		/*
		 * Aव्योम deadlock here: reconnect work calls
		 * cअगरs_put_tcp_session() at its end. Need to be sure
		 * that reconnect work करोes nothing with server poपूर्णांकer after
		 * that step.
		 */
		cancel_delayed_work(&server->reconnect);
	अन्यथा
		cancel_delayed_work_sync(&server->reconnect);

	spin_lock(&GlobalMid_Lock);
	server->tcpStatus = CअगरsExiting;
	spin_unlock(&GlobalMid_Lock);

	cअगरs_crypto_secmech_release(server);
	cअगरs_fscache_release_client_cookie(server);

	kमुक्त(server->session_key.response);
	server->session_key.response = शून्य;
	server->session_key.len = 0;

	task = xchg(&server->tsk, शून्य);
	अगर (task)
		send_sig(SIGKILL, task, 1);
पूर्ण

काष्ठा TCP_Server_Info *
cअगरs_get_tcp_session(काष्ठा smb3_fs_context *ctx)
अणु
	काष्ठा TCP_Server_Info *tcp_ses = शून्य;
	पूर्णांक rc;

	cअगरs_dbg(FYI, "UNC: %s\n", ctx->UNC);

	/* see अगर we alपढ़ोy have a matching tcp_ses */
	tcp_ses = cअगरs_find_tcp_session(ctx);
	अगर (tcp_ses)
		वापस tcp_ses;

	tcp_ses = kzalloc(माप(काष्ठा TCP_Server_Info), GFP_KERNEL);
	अगर (!tcp_ses) अणु
		rc = -ENOMEM;
		जाओ out_err;
	पूर्ण

	tcp_ses->ops = ctx->ops;
	tcp_ses->vals = ctx->vals;
	cअगरs_set_net_ns(tcp_ses, get_net(current->nsproxy->net_ns));
	tcp_ses->hostname = extract_hostname(ctx->UNC);
	अगर (IS_ERR(tcp_ses->hostname)) अणु
		rc = PTR_ERR(tcp_ses->hostname);
		जाओ out_err_crypto_release;
	पूर्ण

	tcp_ses->conn_id = atomic_inc_वापस(&tcpSesNextId);
	tcp_ses->noblockcnt = ctx->rootfs;
	tcp_ses->noblocksnd = ctx->noblocksnd || ctx->rootfs;
	tcp_ses->noस्वतःtune = ctx->noस्वतःtune;
	tcp_ses->tcp_nodelay = ctx->sockopt_tcp_nodelay;
	tcp_ses->rdma = ctx->rdma;
	tcp_ses->in_flight = 0;
	tcp_ses->max_in_flight = 0;
	tcp_ses->credits = 1;
	init_रुकोqueue_head(&tcp_ses->response_q);
	init_रुकोqueue_head(&tcp_ses->request_q);
	INIT_LIST_HEAD(&tcp_ses->pending_mid_q);
	mutex_init(&tcp_ses->srv_mutex);
	स_नकल(tcp_ses->workstation_RFC1001_name,
		ctx->source_rfc1001_name, RFC1001_NAME_LEN_WITH_शून्य);
	स_नकल(tcp_ses->server_RFC1001_name,
		ctx->target_rfc1001_name, RFC1001_NAME_LEN_WITH_शून्य);
	tcp_ses->session_estab = false;
	tcp_ses->sequence_number = 0;
	tcp_ses->reconnect_instance = 1;
	tcp_ses->lstrp = jअगरfies;
	tcp_ses->compress_algorithm = cpu_to_le16(ctx->compression);
	spin_lock_init(&tcp_ses->req_lock);
	INIT_LIST_HEAD(&tcp_ses->tcp_ses_list);
	INIT_LIST_HEAD(&tcp_ses->smb_ses_list);
	INIT_DELAYED_WORK(&tcp_ses->echo, cअगरs_echo_request);
	INIT_DELAYED_WORK(&tcp_ses->reconnect, smb2_reconnect_server);
	mutex_init(&tcp_ses->reconnect_mutex);
	स_नकल(&tcp_ses->srcaddr, &ctx->srcaddr,
	       माप(tcp_ses->srcaddr));
	स_नकल(&tcp_ses->dstaddr, &ctx->dstaddr,
		माप(tcp_ses->dstaddr));
	अगर (ctx->use_client_guid)
		स_नकल(tcp_ses->client_guid, ctx->client_guid,
		       SMB2_CLIENT_GUID_SIZE);
	अन्यथा
		generate_अक्रमom_uuid(tcp_ses->client_guid);
	/*
	 * at this poपूर्णांक we are the only ones with the poपूर्णांकer
	 * to the काष्ठा since the kernel thपढ़ो not created yet
	 * no need to spinlock this init of tcpStatus or srv_count
	 */
	tcp_ses->tcpStatus = CअगरsNew;
	++tcp_ses->srv_count;

	अगर (ctx->echo_पूर्णांकerval >= SMB_ECHO_INTERVAL_MIN &&
		ctx->echo_पूर्णांकerval <= SMB_ECHO_INTERVAL_MAX)
		tcp_ses->echo_पूर्णांकerval = ctx->echo_पूर्णांकerval * HZ;
	अन्यथा
		tcp_ses->echo_पूर्णांकerval = SMB_ECHO_INTERVAL_DEFAULT * HZ;
	अगर (tcp_ses->rdma) अणु
#अगर_अघोषित CONFIG_CIFS_SMB_सूचीECT
		cअगरs_dbg(VFS, "CONFIG_CIFS_SMB_DIRECT is not enabled\n");
		rc = -ENOENT;
		जाओ out_err_crypto_release;
#पूर्ण_अगर
		tcp_ses->smbd_conn = smbd_get_connection(
			tcp_ses, (काष्ठा sockaddr *)&ctx->dstaddr);
		अगर (tcp_ses->smbd_conn) अणु
			cअगरs_dbg(VFS, "RDMA transport established\n");
			rc = 0;
			जाओ smbd_connected;
		पूर्ण अन्यथा अणु
			rc = -ENOENT;
			जाओ out_err_crypto_release;
		पूर्ण
	पूर्ण
	rc = ip_connect(tcp_ses);
	अगर (rc < 0) अणु
		cअगरs_dbg(VFS, "Error connecting to socket. Aborting operation.\n");
		जाओ out_err_crypto_release;
	पूर्ण
smbd_connected:
	/*
	 * since we're in a cअगरs function alपढ़ोy, we know that
	 * this will succeed. No need क्रम try_module_get().
	 */
	__module_get(THIS_MODULE);
	tcp_ses->tsk = kthपढ़ो_run(cअगरs_demultiplex_thपढ़ो,
				  tcp_ses, "cifsd");
	अगर (IS_ERR(tcp_ses->tsk)) अणु
		rc = PTR_ERR(tcp_ses->tsk);
		cअगरs_dbg(VFS, "error %d create cifsd thread\n", rc);
		module_put(THIS_MODULE);
		जाओ out_err_crypto_release;
	पूर्ण
	tcp_ses->min_offload = ctx->min_offload;
	tcp_ses->tcpStatus = CअगरsNeedNegotiate;

	अगर ((ctx->max_credits < 20) || (ctx->max_credits > 60000))
		tcp_ses->max_credits = SMB2_MAX_CREDITS_AVAILABLE;
	अन्यथा
		tcp_ses->max_credits = ctx->max_credits;

	tcp_ses->nr_tarमाला_लो = 1;
	tcp_ses->ignore_signature = ctx->ignore_signature;
	/* thपढ़ो spawned, put it on the list */
	spin_lock(&cअगरs_tcp_ses_lock);
	list_add(&tcp_ses->tcp_ses_list, &cअगरs_tcp_ses_list);
	spin_unlock(&cअगरs_tcp_ses_lock);

	cअगरs_fscache_get_client_cookie(tcp_ses);

	/* queue echo request delayed work */
	queue_delayed_work(cअगरsiod_wq, &tcp_ses->echo, tcp_ses->echo_पूर्णांकerval);

	वापस tcp_ses;

out_err_crypto_release:
	cअगरs_crypto_secmech_release(tcp_ses);

	put_net(cअगरs_net_ns(tcp_ses));

out_err:
	अगर (tcp_ses) अणु
		अगर (!IS_ERR(tcp_ses->hostname))
			kमुक्त(tcp_ses->hostname);
		अगर (tcp_ses->ssocket)
			sock_release(tcp_ses->ssocket);
		kमुक्त(tcp_ses);
	पूर्ण
	वापस ERR_PTR(rc);
पूर्ण

अटल पूर्णांक match_session(काष्ठा cअगरs_ses *ses, काष्ठा smb3_fs_context *ctx)
अणु
	अगर (ctx->sectype != Unspecअगरied &&
	    ctx->sectype != ses->sectype)
		वापस 0;

	/*
	 * If an existing session is limited to less channels than
	 * requested, it should not be reused
	 */
	अगर (ses->chan_max < ctx->max_channels)
		वापस 0;

	चयन (ses->sectype) अणु
	हाल Kerberos:
		अगर (!uid_eq(ctx->cred_uid, ses->cred_uid))
			वापस 0;
		अवरोध;
	शेष:
		/* शून्य username means anonymous session */
		अगर (ses->user_name == शून्य) अणु
			अगर (!ctx->nullauth)
				वापस 0;
			अवरोध;
		पूर्ण

		/* anything अन्यथा takes username/password */
		अगर (म_भेदन(ses->user_name,
			    ctx->username ? ctx->username : "",
			    CIFS_MAX_USERNAME_LEN))
			वापस 0;
		अगर ((ctx->username && म_माप(ctx->username) != 0) &&
		    ses->password != शून्य &&
		    म_भेदन(ses->password,
			    ctx->password ? ctx->password : "",
			    CIFS_MAX_PASSWORD_LEN))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/**
 * cअगरs_setup_ipc - helper to setup the IPC tcon क्रम the session
 *
 * A new IPC connection is made and stored in the session
 * tcon_ipc. The IPC tcon has the same lअगरeसमय as the session.
 */
अटल पूर्णांक
cअगरs_setup_ipc(काष्ठा cअगरs_ses *ses, काष्ठा smb3_fs_context *ctx)
अणु
	पूर्णांक rc = 0, xid;
	काष्ठा cअगरs_tcon *tcon;
	अक्षर unc[SERVER_NAME_LENGTH + माप("//x/IPC$")] = अणु0पूर्ण;
	bool seal = false;
	काष्ठा TCP_Server_Info *server = ses->server;

	/*
	 * If the mount request that resulted in the creation of the
	 * session requires encryption, क्रमce IPC to be encrypted too.
	 */
	अगर (ctx->seal) अणु
		अगर (server->capabilities & SMB2_GLOBAL_CAP_ENCRYPTION)
			seal = true;
		अन्यथा अणु
			cअगरs_server_dbg(VFS,
				 "IPC: server doesn't support encryption\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	tcon = tconInfoAlloc();
	अगर (tcon == शून्य)
		वापस -ENOMEM;

	scnम_लिखो(unc, माप(unc), "\\\\%s\\IPC$", server->hostname);

	xid = get_xid();
	tcon->ses = ses;
	tcon->ipc = true;
	tcon->seal = seal;
	rc = server->ops->tree_connect(xid, ses, unc, tcon, ctx->local_nls);
	मुक्त_xid(xid);

	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "failed to connect to IPC (rc=%d)\n", rc);
		tconInfoFree(tcon);
		जाओ out;
	पूर्ण

	cअगरs_dbg(FYI, "IPC tcon rc = %d ipc tid = %d\n", rc, tcon->tid);

	ses->tcon_ipc = tcon;
out:
	वापस rc;
पूर्ण

/**
 * cअगरs_मुक्त_ipc - helper to release the session IPC tcon
 *
 * Needs to be called everyसमय a session is destroyed
 */
अटल पूर्णांक
cअगरs_मुक्त_ipc(काष्ठा cअगरs_ses *ses)
अणु
	पूर्णांक rc = 0, xid;
	काष्ठा cअगरs_tcon *tcon = ses->tcon_ipc;

	अगर (tcon == शून्य)
		वापस 0;

	अगर (ses->server->ops->tree_disconnect) अणु
		xid = get_xid();
		rc = ses->server->ops->tree_disconnect(xid, tcon);
		मुक्त_xid(xid);
	पूर्ण

	अगर (rc)
		cअगरs_dbg(FYI, "failed to disconnect IPC tcon (rc=%d)\n", rc);

	tconInfoFree(tcon);
	ses->tcon_ipc = शून्य;
	वापस rc;
पूर्ण

अटल काष्ठा cअगरs_ses *
cअगरs_find_smb_ses(काष्ठा TCP_Server_Info *server, काष्ठा smb3_fs_context *ctx)
अणु
	काष्ठा cअगरs_ses *ses;

	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each_entry(ses, &server->smb_ses_list, smb_ses_list) अणु
		अगर (ses->status == CअगरsExiting)
			जारी;
		अगर (!match_session(ses, ctx))
			जारी;
		++ses->ses_count;
		spin_unlock(&cअगरs_tcp_ses_lock);
		वापस ses;
	पूर्ण
	spin_unlock(&cअगरs_tcp_ses_lock);
	वापस शून्य;
पूर्ण

व्योम cअगरs_put_smb_ses(काष्ठा cअगरs_ses *ses)
अणु
	अचिन्हित पूर्णांक rc, xid;
	काष्ठा TCP_Server_Info *server = ses->server;

	cअगरs_dbg(FYI, "%s: ses_count=%d\n", __func__, ses->ses_count);

	spin_lock(&cअगरs_tcp_ses_lock);
	अगर (ses->status == CअगरsExiting) अणु
		spin_unlock(&cअगरs_tcp_ses_lock);
		वापस;
	पूर्ण
	अगर (--ses->ses_count > 0) अणु
		spin_unlock(&cअगरs_tcp_ses_lock);
		वापस;
	पूर्ण
	अगर (ses->status == CअगरsGood)
		ses->status = CअगरsExiting;
	spin_unlock(&cअगरs_tcp_ses_lock);

	cअगरs_मुक्त_ipc(ses);

	अगर (ses->status == CअगरsExiting && server->ops->logoff) अणु
		xid = get_xid();
		rc = server->ops->logoff(xid, ses);
		अगर (rc)
			cअगरs_server_dbg(VFS, "%s: Session Logoff failure rc=%d\n",
				__func__, rc);
		_मुक्त_xid(xid);
	पूर्ण

	spin_lock(&cअगरs_tcp_ses_lock);
	list_del_init(&ses->smb_ses_list);
	spin_unlock(&cअगरs_tcp_ses_lock);

	/* बंद any extra channels */
	अगर (ses->chan_count > 1) अणु
		पूर्णांक i;

		क्रम (i = 1; i < ses->chan_count; i++)
			cअगरs_put_tcp_session(ses->chans[i].server, 0);
	पूर्ण

	sesInfoFree(ses);
	cअगरs_put_tcp_session(server, 0);
पूर्ण

#अगर_घोषित CONFIG_KEYS

/* म_माप("cifs:a:") + CIFS_MAX_DOMAINNAME_LEN + 1 */
#घोषणा CIFSCREDS_DESC_SIZE (7 + CIFS_MAX_DOMAINNAME_LEN + 1)

/* Populate username and pw fields from keyring अगर possible */
अटल पूर्णांक
cअगरs_set_cअगरscreds(काष्ठा smb3_fs_context *ctx, काष्ठा cअगरs_ses *ses)
अणु
	पूर्णांक rc = 0;
	पूर्णांक is_करोमुख्य = 0;
	स्थिर अक्षर *delim, *payload;
	अक्षर *desc;
	sमाप_प्रकार len;
	काष्ठा key *key;
	काष्ठा TCP_Server_Info *server = ses->server;
	काष्ठा sockaddr_in *sa;
	काष्ठा sockaddr_in6 *sa6;
	स्थिर काष्ठा user_key_payload *upayload;

	desc = kदो_स्मृति(CIFSCREDS_DESC_SIZE, GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	/* try to find an address key first */
	चयन (server->dstaddr.ss_family) अणु
	हाल AF_INET:
		sa = (काष्ठा sockaddr_in *)&server->dstaddr;
		प्र_लिखो(desc, "cifs:a:%pI4", &sa->sin_addr.s_addr);
		अवरोध;
	हाल AF_INET6:
		sa6 = (काष्ठा sockaddr_in6 *)&server->dstaddr;
		प्र_लिखो(desc, "cifs:a:%pI6c", &sa6->sin6_addr.s6_addr);
		अवरोध;
	शेष:
		cअगरs_dbg(FYI, "Bad ss_family (%hu)\n",
			 server->dstaddr.ss_family);
		rc = -EINVAL;
		जाओ out_err;
	पूर्ण

	cअगरs_dbg(FYI, "%s: desc=%s\n", __func__, desc);
	key = request_key(&key_type_logon, desc, "");
	अगर (IS_ERR(key)) अणु
		अगर (!ses->करोमुख्यName) अणु
			cअगरs_dbg(FYI, "domainName is NULL\n");
			rc = PTR_ERR(key);
			जाओ out_err;
		पूर्ण

		/* didn't work, try to find a करोमुख्य key */
		प्र_लिखो(desc, "cifs:d:%s", ses->करोमुख्यName);
		cअगरs_dbg(FYI, "%s: desc=%s\n", __func__, desc);
		key = request_key(&key_type_logon, desc, "");
		अगर (IS_ERR(key)) अणु
			rc = PTR_ERR(key);
			जाओ out_err;
		पूर्ण
		is_करोमुख्य = 1;
	पूर्ण

	करोwn_पढ़ो(&key->sem);
	upayload = user_key_payload_locked(key);
	अगर (IS_ERR_OR_शून्य(upayload)) अणु
		rc = upayload ? PTR_ERR(upayload) : -EINVAL;
		जाओ out_key_put;
	पूर्ण

	/* find first : in payload */
	payload = upayload->data;
	delim = strnchr(payload, upayload->datalen, ':');
	cअगरs_dbg(FYI, "payload=%s\n", payload);
	अगर (!delim) अणु
		cअगरs_dbg(FYI, "Unable to find ':' in payload (datalen=%d)\n",
			 upayload->datalen);
		rc = -EINVAL;
		जाओ out_key_put;
	पूर्ण

	len = delim - payload;
	अगर (len > CIFS_MAX_USERNAME_LEN || len <= 0) अणु
		cअगरs_dbg(FYI, "Bad value from username search (len=%zd)\n",
			 len);
		rc = -EINVAL;
		जाओ out_key_put;
	पूर्ण

	ctx->username = kstrndup(payload, len, GFP_KERNEL);
	अगर (!ctx->username) अणु
		cअगरs_dbg(FYI, "Unable to allocate %zd bytes for username\n",
			 len);
		rc = -ENOMEM;
		जाओ out_key_put;
	पूर्ण
	cअगरs_dbg(FYI, "%s: username=%s\n", __func__, ctx->username);

	len = key->datalen - (len + 1);
	अगर (len > CIFS_MAX_PASSWORD_LEN || len <= 0) अणु
		cअगरs_dbg(FYI, "Bad len for password search (len=%zd)\n", len);
		rc = -EINVAL;
		kमुक्त(ctx->username);
		ctx->username = शून्य;
		जाओ out_key_put;
	पूर्ण

	++delim;
	ctx->password = kstrndup(delim, len, GFP_KERNEL);
	अगर (!ctx->password) अणु
		cअगरs_dbg(FYI, "Unable to allocate %zd bytes for password\n",
			 len);
		rc = -ENOMEM;
		kमुक्त(ctx->username);
		ctx->username = शून्य;
		जाओ out_key_put;
	पूर्ण

	/*
	 * If we have a करोमुख्य key then we must set the करोमुख्यName in the
	 * क्रम the request.
	 */
	अगर (is_करोमुख्य && ses->करोमुख्यName) अणु
		ctx->करोमुख्यname = kstrdup(ses->करोमुख्यName, GFP_KERNEL);
		अगर (!ctx->करोमुख्यname) अणु
			cअगरs_dbg(FYI, "Unable to allocate %zd bytes for domain\n",
				 len);
			rc = -ENOMEM;
			kमुक्त(ctx->username);
			ctx->username = शून्य;
			kमुक्त_sensitive(ctx->password);
			ctx->password = शून्य;
			जाओ out_key_put;
		पूर्ण
	पूर्ण

out_key_put:
	up_पढ़ो(&key->sem);
	key_put(key);
out_err:
	kमुक्त(desc);
	cअगरs_dbg(FYI, "%s: returning %d\n", __func__, rc);
	वापस rc;
पूर्ण
#अन्यथा /* ! CONFIG_KEYS */
अटल अंतरभूत पूर्णांक
cअगरs_set_cअगरscreds(काष्ठा smb3_fs_context *ctx __attribute__((unused)),
		   काष्ठा cअगरs_ses *ses __attribute__((unused)))
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर /* CONFIG_KEYS */

/**
 * cअगरs_get_smb_ses - get a session matching @ctx data from @server
 *
 * This function assumes it is being called from cअगरs_mount() where we
 * alपढ़ोy got a server reference (server refcount +1). See
 * cअगरs_get_tcon() क्रम refcount explanations.
 */
काष्ठा cअगरs_ses *
cअगरs_get_smb_ses(काष्ठा TCP_Server_Info *server, काष्ठा smb3_fs_context *ctx)
अणु
	पूर्णांक rc = -ENOMEM;
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरs_ses *ses;
	काष्ठा sockaddr_in *addr = (काष्ठा sockaddr_in *)&server->dstaddr;
	काष्ठा sockaddr_in6 *addr6 = (काष्ठा sockaddr_in6 *)&server->dstaddr;

	xid = get_xid();

	ses = cअगरs_find_smb_ses(server, ctx);
	अगर (ses) अणु
		cअगरs_dbg(FYI, "Existing smb sess found (status=%d)\n",
			 ses->status);

		mutex_lock(&ses->session_mutex);
		rc = cअगरs_negotiate_protocol(xid, ses);
		अगर (rc) अणु
			mutex_unlock(&ses->session_mutex);
			/* problem -- put our ses reference */
			cअगरs_put_smb_ses(ses);
			मुक्त_xid(xid);
			वापस ERR_PTR(rc);
		पूर्ण
		अगर (ses->need_reconnect) अणु
			cअगरs_dbg(FYI, "Session needs reconnect\n");
			rc = cअगरs_setup_session(xid, ses,
						ctx->local_nls);
			अगर (rc) अणु
				mutex_unlock(&ses->session_mutex);
				/* problem -- put our reference */
				cअगरs_put_smb_ses(ses);
				मुक्त_xid(xid);
				वापस ERR_PTR(rc);
			पूर्ण
		पूर्ण
		mutex_unlock(&ses->session_mutex);

		/* existing SMB ses has a server reference alपढ़ोy */
		cअगरs_put_tcp_session(server, 0);
		मुक्त_xid(xid);
		वापस ses;
	पूर्ण

	cअगरs_dbg(FYI, "Existing smb sess not found\n");
	ses = sesInfoAlloc();
	अगर (ses == शून्य)
		जाओ get_ses_fail;

	/* new SMB session uses our server ref */
	ses->server = server;
	अगर (server->dstaddr.ss_family == AF_INET6)
		प्र_लिखो(ses->ip_addr, "%pI6", &addr6->sin6_addr);
	अन्यथा
		प्र_लिखो(ses->ip_addr, "%pI4", &addr->sin_addr);

	अगर (ctx->username) अणु
		ses->user_name = kstrdup(ctx->username, GFP_KERNEL);
		अगर (!ses->user_name)
			जाओ get_ses_fail;
	पूर्ण

	/* ctx->password मुक्तd at unmount */
	अगर (ctx->password) अणु
		ses->password = kstrdup(ctx->password, GFP_KERNEL);
		अगर (!ses->password)
			जाओ get_ses_fail;
	पूर्ण
	अगर (ctx->करोमुख्यname) अणु
		ses->करोमुख्यName = kstrdup(ctx->करोमुख्यname, GFP_KERNEL);
		अगर (!ses->करोमुख्यName)
			जाओ get_ses_fail;
	पूर्ण
	अगर (ctx->करोमुख्यस्वतः)
		ses->करोमुख्यAuto = ctx->करोमुख्यस्वतः;
	ses->cred_uid = ctx->cred_uid;
	ses->linux_uid = ctx->linux_uid;

	ses->sectype = ctx->sectype;
	ses->sign = ctx->sign;
	mutex_lock(&ses->session_mutex);

	/* add server as first channel */
	ses->chans[0].server = server;
	ses->chan_count = 1;
	ses->chan_max = ctx->multichannel ? ctx->max_channels:1;

	rc = cअगरs_negotiate_protocol(xid, ses);
	अगर (!rc)
		rc = cअगरs_setup_session(xid, ses, ctx->local_nls);

	/* each channel uses a dअगरferent signing key */
	स_नकल(ses->chans[0].signkey, ses->smb3signingkey,
	       माप(ses->smb3signingkey));

	mutex_unlock(&ses->session_mutex);
	अगर (rc)
		जाओ get_ses_fail;

	/* success, put it on the list and add it as first channel */
	spin_lock(&cअगरs_tcp_ses_lock);
	list_add(&ses->smb_ses_list, &server->smb_ses_list);
	spin_unlock(&cअगरs_tcp_ses_lock);

	मुक्त_xid(xid);

	cअगरs_setup_ipc(ses, ctx);

	वापस ses;

get_ses_fail:
	sesInfoFree(ses);
	मुक्त_xid(xid);
	वापस ERR_PTR(rc);
पूर्ण

अटल पूर्णांक match_tcon(काष्ठा cअगरs_tcon *tcon, काष्ठा smb3_fs_context *ctx)
अणु
	अगर (tcon->tidStatus == CअगरsExiting)
		वापस 0;
	अगर (म_भेदन(tcon->treeName, ctx->UNC, MAX_TREE_SIZE))
		वापस 0;
	अगर (tcon->seal != ctx->seal)
		वापस 0;
	अगर (tcon->snapshot_समय != ctx->snapshot_समय)
		वापस 0;
	अगर (tcon->handle_समयout != ctx->handle_समयout)
		वापस 0;
	अगर (tcon->no_lease != ctx->no_lease)
		वापस 0;
	अगर (tcon->nodelete != ctx->nodelete)
		वापस 0;
	वापस 1;
पूर्ण

अटल काष्ठा cअगरs_tcon *
cअगरs_find_tcon(काष्ठा cअगरs_ses *ses, काष्ठा smb3_fs_context *ctx)
अणु
	काष्ठा list_head *पंचांगp;
	काष्ठा cअगरs_tcon *tcon;

	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each(पंचांगp, &ses->tcon_list) अणु
		tcon = list_entry(पंचांगp, काष्ठा cअगरs_tcon, tcon_list);
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
		अगर (tcon->dfs_path)
			जारी;
#पूर्ण_अगर
		अगर (!match_tcon(tcon, ctx))
			जारी;
		++tcon->tc_count;
		spin_unlock(&cअगरs_tcp_ses_lock);
		वापस tcon;
	पूर्ण
	spin_unlock(&cअगरs_tcp_ses_lock);
	वापस शून्य;
पूर्ण

व्योम
cअगरs_put_tcon(काष्ठा cअगरs_tcon *tcon)
अणु
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरs_ses *ses;

	/*
	 * IPC tcon share the lअगरeसमय of their session and are
	 * destroyed in the session put function
	 */
	अगर (tcon == शून्य || tcon->ipc)
		वापस;

	ses = tcon->ses;
	cअगरs_dbg(FYI, "%s: tc_count=%d\n", __func__, tcon->tc_count);
	spin_lock(&cअगरs_tcp_ses_lock);
	अगर (--tcon->tc_count > 0) अणु
		spin_unlock(&cअगरs_tcp_ses_lock);
		वापस;
	पूर्ण

	अगर (tcon->use_witness) अणु
		पूर्णांक rc;

		rc = cअगरs_swn_unरेजिस्टर(tcon);
		अगर (rc < 0) अणु
			cअगरs_dbg(VFS, "%s: Failed to unregister for witness notifications: %d\n",
					__func__, rc);
		पूर्ण
	पूर्ण

	list_del_init(&tcon->tcon_list);
	spin_unlock(&cअगरs_tcp_ses_lock);

	xid = get_xid();
	अगर (ses->server->ops->tree_disconnect)
		ses->server->ops->tree_disconnect(xid, tcon);
	_मुक्त_xid(xid);

	cअगरs_fscache_release_super_cookie(tcon);
	tconInfoFree(tcon);
	cअगरs_put_smb_ses(ses);
पूर्ण

/**
 * cअगरs_get_tcon - get a tcon matching @ctx data from @ses
 *
 * - tcon refcount is the number of mount poपूर्णांकs using the tcon.
 * - ses refcount is the number of tcon using the session.
 *
 * 1. This function assumes it is being called from cअगरs_mount() where
 *    we alपढ़ोy got a session reference (ses refcount +1).
 *
 * 2. Since we're in the context of adding a mount poपूर्णांक, the end
 *    result should be either:
 *
 * a) a new tcon alपढ़ोy allocated with refcount=1 (1 mount poपूर्णांक) and
 *    its session refcount incremented (1 new tcon). This +1 was
 *    alपढ़ोy करोne in (1).
 *
 * b) an existing tcon with refcount+1 (add a mount poपूर्णांक to it) and
 *    identical ses refcount (no new tcon). Because of (1) we need to
 *    decrement the ses refcount.
 */
अटल काष्ठा cअगरs_tcon *
cअगरs_get_tcon(काष्ठा cअगरs_ses *ses, काष्ठा smb3_fs_context *ctx)
अणु
	पूर्णांक rc, xid;
	काष्ठा cअगरs_tcon *tcon;

	tcon = cअगरs_find_tcon(ses, ctx);
	अगर (tcon) अणु
		/*
		 * tcon has refcount alपढ़ोy incremented but we need to
		 * decrement extra ses reference gotten by caller (हाल b)
		 */
		cअगरs_dbg(FYI, "Found match on UNC path\n");
		cअगरs_put_smb_ses(ses);
		वापस tcon;
	पूर्ण

	अगर (!ses->server->ops->tree_connect) अणु
		rc = -ENOSYS;
		जाओ out_fail;
	पूर्ण

	tcon = tconInfoAlloc();
	अगर (tcon == शून्य) अणु
		rc = -ENOMEM;
		जाओ out_fail;
	पूर्ण

	अगर (ctx->snapshot_समय) अणु
		अगर (ses->server->vals->protocol_id == 0) अणु
			cअगरs_dbg(VFS,
			     "Use SMB2 or later for snapshot mount option\n");
			rc = -EOPNOTSUPP;
			जाओ out_fail;
		पूर्ण अन्यथा
			tcon->snapshot_समय = ctx->snapshot_समय;
	पूर्ण

	अगर (ctx->handle_समयout) अणु
		अगर (ses->server->vals->protocol_id == 0) अणु
			cअगरs_dbg(VFS,
			     "Use SMB2.1 or later for handle timeout option\n");
			rc = -EOPNOTSUPP;
			जाओ out_fail;
		पूर्ण अन्यथा
			tcon->handle_समयout = ctx->handle_समयout;
	पूर्ण

	tcon->ses = ses;
	अगर (ctx->password) अणु
		tcon->password = kstrdup(ctx->password, GFP_KERNEL);
		अगर (!tcon->password) अणु
			rc = -ENOMEM;
			जाओ out_fail;
		पूर्ण
	पूर्ण

	अगर (ctx->seal) अणु
		अगर (ses->server->vals->protocol_id == 0) अणु
			cअगरs_dbg(VFS,
				 "SMB3 or later required for encryption\n");
			rc = -EOPNOTSUPP;
			जाओ out_fail;
		पूर्ण अन्यथा अगर (tcon->ses->server->capabilities &
					SMB2_GLOBAL_CAP_ENCRYPTION)
			tcon->seal = true;
		अन्यथा अणु
			cअगरs_dbg(VFS, "Encryption is not supported on share\n");
			rc = -EOPNOTSUPP;
			जाओ out_fail;
		पूर्ण
	पूर्ण

	अगर (ctx->linux_ext) अणु
		अगर (ses->server->posix_ext_supported) अणु
			tcon->posix_extensions = true;
			pr_warn_once("SMB3.11 POSIX Extensions are experimental\n");
		पूर्ण अन्यथा अणु
			cअगरs_dbg(VFS, "Server does not support mounting with posix SMB3.11 extensions\n");
			rc = -EOPNOTSUPP;
			जाओ out_fail;
		पूर्ण
	पूर्ण

	/*
	 * BB Do we need to wrap session_mutex around this TCon call and Unix
	 * SetFS as we करो on SessSetup and reconnect?
	 */
	xid = get_xid();
	rc = ses->server->ops->tree_connect(xid, ses, ctx->UNC, tcon,
					    ctx->local_nls);
	मुक्त_xid(xid);
	cअगरs_dbg(FYI, "Tcon rc = %d\n", rc);
	अगर (rc)
		जाओ out_fail;

	tcon->use_persistent = false;
	/* check अगर SMB2 or later, CIFS करोes not support persistent handles */
	अगर (ctx->persistent) अणु
		अगर (ses->server->vals->protocol_id == 0) अणु
			cअगरs_dbg(VFS,
			     "SMB3 or later required for persistent handles\n");
			rc = -EOPNOTSUPP;
			जाओ out_fail;
		पूर्ण अन्यथा अगर (ses->server->capabilities &
			   SMB2_GLOBAL_CAP_PERSISTENT_HANDLES)
			tcon->use_persistent = true;
		अन्यथा /* persistent handles requested but not supported */ अणु
			cअगरs_dbg(VFS,
				"Persistent handles not supported on share\n");
			rc = -EOPNOTSUPP;
			जाओ out_fail;
		पूर्ण
	पूर्ण अन्यथा अगर ((tcon->capabilities & SMB2_SHARE_CAP_CONTINUOUS_AVAILABILITY)
	     && (ses->server->capabilities & SMB2_GLOBAL_CAP_PERSISTENT_HANDLES)
	     && (ctx->nopersistent == false)) अणु
		cअगरs_dbg(FYI, "enabling persistent handles\n");
		tcon->use_persistent = true;
	पूर्ण अन्यथा अगर (ctx->resilient) अणु
		अगर (ses->server->vals->protocol_id == 0) अणु
			cअगरs_dbg(VFS,
			     "SMB2.1 or later required for resilient handles\n");
			rc = -EOPNOTSUPP;
			जाओ out_fail;
		पूर्ण
		tcon->use_resilient = true;
	पूर्ण

	tcon->use_witness = false;
	अगर (IS_ENABLED(CONFIG_CIFS_SWN_UPCALL) && ctx->witness) अणु
		अगर (ses->server->vals->protocol_id >= SMB30_PROT_ID) अणु
			अगर (tcon->capabilities & SMB2_SHARE_CAP_CLUSTER) अणु
				/*
				 * Set witness in use flag in first place
				 * to retry registration in the echo task
				 */
				tcon->use_witness = true;
				/* And try to रेजिस्टर immediately */
				rc = cअगरs_swn_रेजिस्टर(tcon);
				अगर (rc < 0) अणु
					cअगरs_dbg(VFS, "Failed to register for witness notifications: %d\n", rc);
					जाओ out_fail;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* TODO: try to extend क्रम non-cluster uses (eg multichannel) */
				cअगरs_dbg(VFS, "witness requested on mount but no CLUSTER capability on share\n");
				rc = -EOPNOTSUPP;
				जाओ out_fail;
			पूर्ण
		पूर्ण अन्यथा अणु
			cअगरs_dbg(VFS, "SMB3 or later required for witness option\n");
			rc = -EOPNOTSUPP;
			जाओ out_fail;
		पूर्ण
	पूर्ण

	/* If the user really knows what they are करोing they can override */
	अगर (tcon->share_flags & SMB2_SHAREFLAG_NO_CACHING) अणु
		अगर (ctx->cache_ro)
			cअगरs_dbg(VFS, "cache=ro requested on mount but NO_CACHING flag set on share\n");
		अन्यथा अगर (ctx->cache_rw)
			cअगरs_dbg(VFS, "cache=singleclient requested on mount but NO_CACHING flag set on share\n");
	पूर्ण

	अगर (ctx->no_lease) अणु
		अगर (ses->server->vals->protocol_id == 0) अणु
			cअगरs_dbg(VFS,
				"SMB2 or later required for nolease option\n");
			rc = -EOPNOTSUPP;
			जाओ out_fail;
		पूर्ण अन्यथा
			tcon->no_lease = ctx->no_lease;
	पूर्ण

	/*
	 * We can have only one retry value क्रम a connection to a share so क्रम
	 * resources mounted more than once to the same server share the last
	 * value passed in क्रम the retry flag is used.
	 */
	tcon->retry = ctx->retry;
	tcon->noहाल = ctx->noहाल;
	अगर (ses->server->capabilities & SMB2_GLOBAL_CAP_सूचीECTORY_LEASING)
		tcon->nohandlecache = ctx->nohandlecache;
	अन्यथा
		tcon->nohandlecache = true;
	tcon->nodelete = ctx->nodelete;
	tcon->local_lease = ctx->local_lease;
	INIT_LIST_HEAD(&tcon->pending_खोलोs);

	spin_lock(&cअगरs_tcp_ses_lock);
	list_add(&tcon->tcon_list, &ses->tcon_list);
	spin_unlock(&cअगरs_tcp_ses_lock);

	cअगरs_fscache_get_super_cookie(tcon);

	वापस tcon;

out_fail:
	tconInfoFree(tcon);
	वापस ERR_PTR(rc);
पूर्ण

व्योम
cअगरs_put_tlink(काष्ठा tcon_link *tlink)
अणु
	अगर (!tlink || IS_ERR(tlink))
		वापस;

	अगर (!atomic_dec_and_test(&tlink->tl_count) ||
	    test_bit(TCON_LINK_IN_TREE, &tlink->tl_flags)) अणु
		tlink->tl_समय = jअगरfies;
		वापस;
	पूर्ण

	अगर (!IS_ERR(tlink_tcon(tlink)))
		cअगरs_put_tcon(tlink_tcon(tlink));
	kमुक्त(tlink);
	वापस;
पूर्ण

अटल पूर्णांक
compare_mount_options(काष्ठा super_block *sb, काष्ठा cअगरs_mnt_data *mnt_data)
अणु
	काष्ठा cअगरs_sb_info *old = CIFS_SB(sb);
	काष्ठा cअगरs_sb_info *new = mnt_data->cअगरs_sb;
	अचिन्हित पूर्णांक oldflags = old->mnt_cअगरs_flags & CIFS_MOUNT_MASK;
	अचिन्हित पूर्णांक newflags = new->mnt_cअगरs_flags & CIFS_MOUNT_MASK;

	अगर ((sb->s_flags & CIFS_MS_MASK) != (mnt_data->flags & CIFS_MS_MASK))
		वापस 0;

	अगर (old->mnt_cअगरs_serverino_स्वतःdisabled)
		newflags &= ~CIFS_MOUNT_SERVER_INUM;

	अगर (oldflags != newflags)
		वापस 0;

	/*
	 * We want to share sb only अगर we करोn't specअगरy an r/wsize or
	 * specअगरied r/wsize is greater than or equal to existing one.
	 */
	अगर (new->ctx->wsize && new->ctx->wsize < old->ctx->wsize)
		वापस 0;

	अगर (new->ctx->rsize && new->ctx->rsize < old->ctx->rsize)
		वापस 0;

	अगर (!uid_eq(old->ctx->linux_uid, new->ctx->linux_uid) ||
	    !gid_eq(old->ctx->linux_gid, new->ctx->linux_gid))
		वापस 0;

	अगर (old->ctx->file_mode != new->ctx->file_mode ||
	    old->ctx->dir_mode != new->ctx->dir_mode)
		वापस 0;

	अगर (म_भेद(old->local_nls->अक्षरset, new->local_nls->अक्षरset))
		वापस 0;

	अगर (old->ctx->acregmax != new->ctx->acregmax)
		वापस 0;
	अगर (old->ctx->acdirmax != new->ctx->acdirmax)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक
match_prepath(काष्ठा super_block *sb, काष्ठा cअगरs_mnt_data *mnt_data)
अणु
	काष्ठा cअगरs_sb_info *old = CIFS_SB(sb);
	काष्ठा cअगरs_sb_info *new = mnt_data->cअगरs_sb;
	bool old_set = (old->mnt_cअगरs_flags & CIFS_MOUNT_USE_PREFIX_PATH) &&
		old->prepath;
	bool new_set = (new->mnt_cअगरs_flags & CIFS_MOUNT_USE_PREFIX_PATH) &&
		new->prepath;

	अगर (old_set && new_set && !म_भेद(new->prepath, old->prepath))
		वापस 1;
	अन्यथा अगर (!old_set && !new_set)
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक
cअगरs_match_super(काष्ठा super_block *sb, व्योम *data)
अणु
	काष्ठा cअगरs_mnt_data *mnt_data = (काष्ठा cअगरs_mnt_data *)data;
	काष्ठा smb3_fs_context *ctx;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा TCP_Server_Info *tcp_srv;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा tcon_link *tlink;
	पूर्णांक rc = 0;

	spin_lock(&cअगरs_tcp_ses_lock);
	cअगरs_sb = CIFS_SB(sb);
	tlink = cअगरs_get_tlink(cअगरs_sb_master_tlink(cअगरs_sb));
	अगर (IS_ERR(tlink)) अणु
		spin_unlock(&cअगरs_tcp_ses_lock);
		वापस rc;
	पूर्ण
	tcon = tlink_tcon(tlink);
	ses = tcon->ses;
	tcp_srv = ses->server;

	ctx = mnt_data->ctx;

	अगर (!match_server(tcp_srv, ctx) ||
	    !match_session(ses, ctx) ||
	    !match_tcon(tcon, ctx) ||
	    !match_prepath(sb, mnt_data)) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	rc = compare_mount_options(sb, mnt_data);
out:
	spin_unlock(&cअगरs_tcp_ses_lock);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
अटल काष्ठा lock_class_key cअगरs_key[2];
अटल काष्ठा lock_class_key cअगरs_slock_key[2];

अटल अंतरभूत व्योम
cअगरs_reclassअगरy_socket4(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	BUG_ON(!sock_allow_reclassअगरication(sk));
	sock_lock_init_class_and_name(sk, "slock-AF_INET-CIFS",
		&cअगरs_slock_key[0], "sk_lock-AF_INET-CIFS", &cअगरs_key[0]);
पूर्ण

अटल अंतरभूत व्योम
cअगरs_reclassअगरy_socket6(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	BUG_ON(!sock_allow_reclassअगरication(sk));
	sock_lock_init_class_and_name(sk, "slock-AF_INET6-CIFS",
		&cअगरs_slock_key[1], "sk_lock-AF_INET6-CIFS", &cअगरs_key[1]);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
cअगरs_reclassअगरy_socket4(काष्ठा socket *sock)
अणु
पूर्ण

अटल अंतरभूत व्योम
cअगरs_reclassअगरy_socket6(काष्ठा socket *sock)
अणु
पूर्ण
#पूर्ण_अगर

/* See RFC1001 section 14 on representation of Netbios names */
अटल व्योम rfc1002mangle(अक्षर *target, अक्षर *source, अचिन्हित पूर्णांक length)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < (length); i++) अणु
		/* mask a nibble at a समय and encode */
		target[j] = 'A' + (0x0F & (source[i] >> 4));
		target[j+1] = 'A' + (0x0F & source[i]);
		j += 2;
	पूर्ण

पूर्ण

अटल पूर्णांक
bind_socket(काष्ठा TCP_Server_Info *server)
अणु
	पूर्णांक rc = 0;
	अगर (server->srcaddr.ss_family != AF_UNSPEC) अणु
		/* Bind to the specअगरied local IP address */
		काष्ठा socket *socket = server->ssocket;
		rc = socket->ops->bind(socket,
				       (काष्ठा sockaddr *) &server->srcaddr,
				       माप(server->srcaddr));
		अगर (rc < 0) अणु
			काष्ठा sockaddr_in *saddr4;
			काष्ठा sockaddr_in6 *saddr6;
			saddr4 = (काष्ठा sockaddr_in *)&server->srcaddr;
			saddr6 = (काष्ठा sockaddr_in6 *)&server->srcaddr;
			अगर (saddr6->sin6_family == AF_INET6)
				cअगरs_server_dbg(VFS, "Failed to bind to: %pI6c, error: %d\n",
					 &saddr6->sin6_addr, rc);
			अन्यथा
				cअगरs_server_dbg(VFS, "Failed to bind to: %pI4, error: %d\n",
					 &saddr4->sin_addr.s_addr, rc);
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक
ip_rfc1001_connect(काष्ठा TCP_Server_Info *server)
अणु
	पूर्णांक rc = 0;
	/*
	 * some servers require RFC1001 sessinit beक्रमe sending
	 * negprot - BB check reconnection in हाल where second
	 * sessinit is sent but no second negprot
	 */
	काष्ठा rfc1002_session_packet *ses_init_buf;
	काष्ठा smb_hdr *smb_buf;
	ses_init_buf = kzalloc(माप(काष्ठा rfc1002_session_packet),
			       GFP_KERNEL);
	अगर (ses_init_buf) अणु
		ses_init_buf->trailer.session_req.called_len = 32;

		अगर (server->server_RFC1001_name[0] != 0)
			rfc1002mangle(ses_init_buf->trailer.
				      session_req.called_name,
				      server->server_RFC1001_name,
				      RFC1001_NAME_LEN_WITH_शून्य);
		अन्यथा
			rfc1002mangle(ses_init_buf->trailer.
				      session_req.called_name,
				      DEFAULT_CIFS_CALLED_NAME,
				      RFC1001_NAME_LEN_WITH_शून्य);

		ses_init_buf->trailer.session_req.calling_len = 32;

		/*
		 * calling name ends in null (byte 16) from old smb
		 * convention.
		 */
		अगर (server->workstation_RFC1001_name[0] != 0)
			rfc1002mangle(ses_init_buf->trailer.
				      session_req.calling_name,
				      server->workstation_RFC1001_name,
				      RFC1001_NAME_LEN_WITH_शून्य);
		अन्यथा
			rfc1002mangle(ses_init_buf->trailer.
				      session_req.calling_name,
				      "LINUX_CIFS_CLNT",
				      RFC1001_NAME_LEN_WITH_शून्य);

		ses_init_buf->trailer.session_req.scope1 = 0;
		ses_init_buf->trailer.session_req.scope2 = 0;
		smb_buf = (काष्ठा smb_hdr *)ses_init_buf;

		/* माप RFC1002_SESSION_REQUEST with no scope */
		smb_buf->smb_buf_length = cpu_to_be32(0x81000044);
		rc = smb_send(server, smb_buf, 0x44);
		kमुक्त(ses_init_buf);
		/*
		 * RFC1001 layer in at least one server
		 * requires very लघु अवरोध beक्रमe negprot
		 * presumably because not expecting negprot
		 * to follow so fast.  This is a simple
		 * solution that works without
		 * complicating the code and causes no
		 * signअगरicant slowing करोwn on mount
		 * क्रम everyone अन्यथा
		 */
		usleep_range(1000, 2000);
	पूर्ण
	/*
	 * अन्यथा the negprot may still work without this
	 * even though दो_स्मृति failed
	 */

	वापस rc;
पूर्ण

अटल पूर्णांक
generic_ip_connect(काष्ठा TCP_Server_Info *server)
अणु
	पूर्णांक rc = 0;
	__be16 sport;
	पूर्णांक slen, sfamily;
	काष्ठा socket *socket = server->ssocket;
	काष्ठा sockaddr *saddr;

	saddr = (काष्ठा sockaddr *) &server->dstaddr;

	अगर (server->dstaddr.ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *ipv6 = (काष्ठा sockaddr_in6 *)&server->dstaddr;

		sport = ipv6->sin6_port;
		slen = माप(काष्ठा sockaddr_in6);
		sfamily = AF_INET6;
		cअगरs_dbg(FYI, "%s: connecting to [%pI6]:%d\n", __func__, &ipv6->sin6_addr,
				ntohs(sport));
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in *ipv4 = (काष्ठा sockaddr_in *)&server->dstaddr;

		sport = ipv4->sin_port;
		slen = माप(काष्ठा sockaddr_in);
		sfamily = AF_INET;
		cअगरs_dbg(FYI, "%s: connecting to %pI4:%d\n", __func__, &ipv4->sin_addr,
				ntohs(sport));
	पूर्ण

	अगर (socket == शून्य) अणु
		rc = __sock_create(cअगरs_net_ns(server), sfamily, SOCK_STREAM,
				   IPPROTO_TCP, &socket, 1);
		अगर (rc < 0) अणु
			cअगरs_server_dbg(VFS, "Error %d creating socket\n", rc);
			server->ssocket = शून्य;
			वापस rc;
		पूर्ण

		/* BB other socket options to set KEEPALIVE, NODELAY? */
		cअगरs_dbg(FYI, "Socket created\n");
		server->ssocket = socket;
		socket->sk->sk_allocation = GFP_NOFS;
		अगर (sfamily == AF_INET6)
			cअगरs_reclassअगरy_socket6(socket);
		अन्यथा
			cअगरs_reclassअगरy_socket4(socket);
	पूर्ण

	rc = bind_socket(server);
	अगर (rc < 0)
		वापस rc;

	/*
	 * Eventually check क्रम other socket options to change from
	 * the शेष. sock_setsockopt not used because it expects
	 * user space buffer
	 */
	socket->sk->sk_rcvसमयo = 7 * HZ;
	socket->sk->sk_sndसमयo = 5 * HZ;

	/* make the bufsizes depend on wsize/rsize and max requests */
	अगर (server->noस्वतःtune) अणु
		अगर (socket->sk->sk_sndbuf < (200 * 1024))
			socket->sk->sk_sndbuf = 200 * 1024;
		अगर (socket->sk->sk_rcvbuf < (140 * 1024))
			socket->sk->sk_rcvbuf = 140 * 1024;
	पूर्ण

	अगर (server->tcp_nodelay)
		tcp_sock_set_nodelay(socket->sk);

	cअगरs_dbg(FYI, "sndbuf %d rcvbuf %d rcvtimeo 0x%lx\n",
		 socket->sk->sk_sndbuf,
		 socket->sk->sk_rcvbuf, socket->sk->sk_rcvसमयo);

	rc = socket->ops->connect(socket, saddr, slen,
				  server->noblockcnt ? O_NONBLOCK : 0);
	/*
	 * When mounting SMB root file प्रणालीs, we करो not want to block in
	 * connect. Otherwise bail out and then let cअगरs_reconnect() perक्रमm
	 * reconnect failover - अगर possible.
	 */
	अगर (server->noblockcnt && rc == -EINPROGRESS)
		rc = 0;
	अगर (rc < 0) अणु
		cअगरs_dbg(FYI, "Error %d connecting to server\n", rc);
		sock_release(socket);
		server->ssocket = शून्य;
		वापस rc;
	पूर्ण

	अगर (sport == htons(RFC1001_PORT))
		rc = ip_rfc1001_connect(server);

	वापस rc;
पूर्ण

अटल पूर्णांक
ip_connect(काष्ठा TCP_Server_Info *server)
अणु
	__be16 *sport;
	काष्ठा sockaddr_in6 *addr6 = (काष्ठा sockaddr_in6 *)&server->dstaddr;
	काष्ठा sockaddr_in *addr = (काष्ठा sockaddr_in *)&server->dstaddr;

	अगर (server->dstaddr.ss_family == AF_INET6)
		sport = &addr6->sin6_port;
	अन्यथा
		sport = &addr->sin_port;

	अगर (*sport == 0) अणु
		पूर्णांक rc;

		/* try with 445 port at first */
		*sport = htons(CIFS_PORT);

		rc = generic_ip_connect(server);
		अगर (rc >= 0)
			वापस rc;

		/* अगर it failed, try with 139 port */
		*sport = htons(RFC1001_PORT);
	पूर्ण

	वापस generic_ip_connect(server);
पूर्ण

व्योम reset_cअगरs_unix_caps(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			  काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा smb3_fs_context *ctx)
अणु
	/*
	 * If we are reconnecting then should we check to see अगर
	 * any requested capabilities changed locally e.g. via
	 * remount but we can not करो much about it here
	 * अगर they have (even अगर we could detect it by the following)
	 * Perhaps we could add a backpoपूर्णांकer to array of sb from tcon
	 * or अगर we change to make all sb to same share the same
	 * sb as NFS - then we only have one backpoपूर्णांकer to sb.
	 * What अगर we wanted to mount the server share twice once with
	 * and once without posixacls or posix paths?
	 */
	__u64 saved_cap = le64_to_cpu(tcon->fsUnixInfo.Capability);

	अगर (ctx && ctx->no_linux_ext) अणु
		tcon->fsUnixInfo.Capability = 0;
		tcon->unix_ext = 0; /* Unix Extensions disabled */
		cअगरs_dbg(FYI, "Linux protocol extensions disabled\n");
		वापस;
	पूर्ण अन्यथा अगर (ctx)
		tcon->unix_ext = 1; /* Unix Extensions supported */

	अगर (!tcon->unix_ext) अणु
		cअगरs_dbg(FYI, "Unix extensions disabled so not set on reconnect\n");
		वापस;
	पूर्ण

	अगर (!CIFSSMBQFSUnixInfo(xid, tcon)) अणु
		__u64 cap = le64_to_cpu(tcon->fsUnixInfo.Capability);
		cअगरs_dbg(FYI, "unix caps which server supports %lld\n", cap);
		/*
		 * check क्रम reconnect हाल in which we करो not
		 * want to change the mount behavior अगर we can aव्योम it
		 */
		अगर (ctx == शून्य) अणु
			/*
			 * turn off POSIX ACL and PATHNAMES अगर not set
			 * originally at mount समय
			 */
			अगर ((saved_cap & CIFS_UNIX_POSIX_ACL_CAP) == 0)
				cap &= ~CIFS_UNIX_POSIX_ACL_CAP;
			अगर ((saved_cap & CIFS_UNIX_POSIX_PATHNAMES_CAP) == 0) अणु
				अगर (cap & CIFS_UNIX_POSIX_PATHNAMES_CAP)
					cअगरs_dbg(VFS, "POSIXPATH support change\n");
				cap &= ~CIFS_UNIX_POSIX_PATHNAMES_CAP;
			पूर्ण अन्यथा अगर ((cap & CIFS_UNIX_POSIX_PATHNAMES_CAP) == 0) अणु
				cअगरs_dbg(VFS, "possible reconnect error\n");
				cअगरs_dbg(VFS, "server disabled POSIX path support\n");
			पूर्ण
		पूर्ण

		अगर (cap & CIFS_UNIX_TRANSPORT_ENCRYPTION_MANDATORY_CAP)
			cअगरs_dbg(VFS, "per-share encryption not supported yet\n");

		cap &= CIFS_UNIX_CAP_MASK;
		अगर (ctx && ctx->no_psx_acl)
			cap &= ~CIFS_UNIX_POSIX_ACL_CAP;
		अन्यथा अगर (CIFS_UNIX_POSIX_ACL_CAP & cap) अणु
			cअगरs_dbg(FYI, "negotiated posix acl support\n");
			अगर (cअगरs_sb)
				cअगरs_sb->mnt_cअगरs_flags |=
					CIFS_MOUNT_POSIXACL;
		पूर्ण

		अगर (ctx && ctx->posix_paths == 0)
			cap &= ~CIFS_UNIX_POSIX_PATHNAMES_CAP;
		अन्यथा अगर (cap & CIFS_UNIX_POSIX_PATHNAMES_CAP) अणु
			cअगरs_dbg(FYI, "negotiate posix pathnames\n");
			अगर (cअगरs_sb)
				cअगरs_sb->mnt_cअगरs_flags |=
					CIFS_MOUNT_POSIX_PATHS;
		पूर्ण

		cअगरs_dbg(FYI, "Negotiate caps 0x%x\n", (पूर्णांक)cap);
#अगर_घोषित CONFIG_CIFS_DEBUG2
		अगर (cap & CIFS_UNIX_FCNTL_CAP)
			cअगरs_dbg(FYI, "FCNTL cap\n");
		अगर (cap & CIFS_UNIX_EXTATTR_CAP)
			cअगरs_dbg(FYI, "EXTATTR cap\n");
		अगर (cap & CIFS_UNIX_POSIX_PATHNAMES_CAP)
			cअगरs_dbg(FYI, "POSIX path cap\n");
		अगर (cap & CIFS_UNIX_XATTR_CAP)
			cअगरs_dbg(FYI, "XATTR cap\n");
		अगर (cap & CIFS_UNIX_POSIX_ACL_CAP)
			cअगरs_dbg(FYI, "POSIX ACL cap\n");
		अगर (cap & CIFS_UNIX_LARGE_READ_CAP)
			cअगरs_dbg(FYI, "very large read cap\n");
		अगर (cap & CIFS_UNIX_LARGE_WRITE_CAP)
			cअगरs_dbg(FYI, "very large write cap\n");
		अगर (cap & CIFS_UNIX_TRANSPORT_ENCRYPTION_CAP)
			cअगरs_dbg(FYI, "transport encryption cap\n");
		अगर (cap & CIFS_UNIX_TRANSPORT_ENCRYPTION_MANDATORY_CAP)
			cअगरs_dbg(FYI, "mandatory transport encryption cap\n");
#पूर्ण_अगर /* CIFS_DEBUG2 */
		अगर (CIFSSMBSetFSUnixInfo(xid, tcon, cap)) अणु
			अगर (ctx == शून्य)
				cअगरs_dbg(FYI, "resetting capabilities failed\n");
			अन्यथा
				cअगरs_dbg(VFS, "Negotiating Unix capabilities with the server failed. Consider mounting with the Unix Extensions disabled if problems are found by specifying the nounix mount option.\n");

		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक cअगरs_setup_cअगरs_sb(काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	काष्ठा smb3_fs_context *ctx = cअगरs_sb->ctx;

	INIT_DELAYED_WORK(&cअगरs_sb->prune_tlinks, cअगरs_prune_tlinks);

	spin_lock_init(&cअगरs_sb->tlink_tree_lock);
	cअगरs_sb->tlink_tree = RB_ROOT;

	cअगरs_dbg(FYI, "file mode: %04ho  dir mode: %04ho\n",
		 ctx->file_mode, ctx->dir_mode);

	/* this is needed क्रम ASCII cp to Unicode converts */
	अगर (ctx->ioअक्षरset == शून्य) अणु
		/* load_nls_शेष cannot वापस null */
		cअगरs_sb->local_nls = load_nls_शेष();
	पूर्ण अन्यथा अणु
		cअगरs_sb->local_nls = load_nls(ctx->ioअक्षरset);
		अगर (cअगरs_sb->local_nls == शून्य) अणु
			cअगरs_dbg(VFS, "CIFS mount error: iocharset %s not found\n",
				 ctx->ioअक्षरset);
			वापस -ELIBACC;
		पूर्ण
	पूर्ण
	ctx->local_nls = cअगरs_sb->local_nls;

	smb3_update_mnt_flags(cअगरs_sb);

	अगर (ctx->direct_io)
		cअगरs_dbg(FYI, "mounting share using direct i/o\n");
	अगर (ctx->cache_ro) अणु
		cअगरs_dbg(VFS, "mounting share with read only caching. Ensure that the share will not be modified while in use.\n");
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_RO_CACHE;
	पूर्ण अन्यथा अगर (ctx->cache_rw) अणु
		cअगरs_dbg(VFS, "mounting share in single client RW caching mode. Ensure that no other systems will be accessing the share.\n");
		cअगरs_sb->mnt_cअगरs_flags |= (CIFS_MOUNT_RO_CACHE |
					    CIFS_MOUNT_RW_CACHE);
	पूर्ण

	अगर ((ctx->cअगरs_acl) && (ctx->dynperm))
		cअगरs_dbg(VFS, "mount option dynperm ignored if cifsacl mount option supported\n");

	अगर (ctx->prepath) अणु
		cअगरs_sb->prepath = kstrdup(ctx->prepath, GFP_KERNEL);
		अगर (cअगरs_sb->prepath == शून्य)
			वापस -ENOMEM;
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_USE_PREFIX_PATH;
	पूर्ण

	वापस 0;
पूर्ण

/* Release all succeed connections */
अटल अंतरभूत व्योम mount_put_conns(काष्ठा cअगरs_sb_info *cअगरs_sb,
				   अचिन्हित पूर्णांक xid,
				   काष्ठा TCP_Server_Info *server,
				   काष्ठा cअगरs_ses *ses, काष्ठा cअगरs_tcon *tcon)
अणु
	पूर्णांक rc = 0;

	अगर (tcon)
		cअगरs_put_tcon(tcon);
	अन्यथा अगर (ses)
		cअगरs_put_smb_ses(ses);
	अन्यथा अगर (server)
		cअगरs_put_tcp_session(server, 0);
	cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_POSIX_PATHS;
	मुक्त_xid(xid);
पूर्ण

/* Get connections क्रम tcp, ses and tcon */
अटल पूर्णांक mount_get_conns(काष्ठा smb3_fs_context *ctx, काष्ठा cअगरs_sb_info *cअगरs_sb,
			   अचिन्हित पूर्णांक *xid,
			   काष्ठा TCP_Server_Info **nserver,
			   काष्ठा cअगरs_ses **nses, काष्ठा cअगरs_tcon **ntcon)
अणु
	पूर्णांक rc = 0;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;

	*nserver = शून्य;
	*nses = शून्य;
	*ntcon = शून्य;

	*xid = get_xid();

	/* get a reference to a tcp session */
	server = cअगरs_get_tcp_session(ctx);
	अगर (IS_ERR(server)) अणु
		rc = PTR_ERR(server);
		वापस rc;
	पूर्ण

	*nserver = server;

	/* get a reference to a SMB session */
	ses = cअगरs_get_smb_ses(server, ctx);
	अगर (IS_ERR(ses)) अणु
		rc = PTR_ERR(ses);
		वापस rc;
	पूर्ण

	*nses = ses;

	अगर ((ctx->persistent == true) && (!(ses->server->capabilities &
					    SMB2_GLOBAL_CAP_PERSISTENT_HANDLES))) अणु
		cअगरs_server_dbg(VFS, "persistent handles not supported by server\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* search क्रम existing tcon to this server share */
	tcon = cअगरs_get_tcon(ses, ctx);
	अगर (IS_ERR(tcon)) अणु
		rc = PTR_ERR(tcon);
		वापस rc;
	पूर्ण

	*ntcon = tcon;

	/* अगर new SMB3.11 POSIX extensions are supported करो not remap / and \ */
	अगर (tcon->posix_extensions)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_POSIX_PATHS;

	/* tell server which Unix caps we support */
	अगर (cap_unix(tcon->ses)) अणु
		/*
		 * reset of caps checks mount to see अगर unix extensions disabled
		 * क्रम just this mount.
		 */
		reset_cअगरs_unix_caps(*xid, tcon, cअगरs_sb, ctx);
		अगर ((tcon->ses->server->tcpStatus == CअगरsNeedReconnect) &&
		    (le64_to_cpu(tcon->fsUnixInfo.Capability) &
		     CIFS_UNIX_TRANSPORT_ENCRYPTION_MANDATORY_CAP))
			वापस -EACCES;
	पूर्ण अन्यथा
		tcon->unix_ext = 0; /* server करोes not support them */

	/* करो not care अगर a following call succeed - inक्रमmational */
	अगर (!tcon->pipe && server->ops->qfs_tcon) अणु
		server->ops->qfs_tcon(*xid, tcon, cअगरs_sb);
		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_RO_CACHE) अणु
			अगर (tcon->fsDevInfo.DeviceCharacteristics &
			    cpu_to_le32(खाता_READ_ONLY_DEVICE))
				cअगरs_dbg(VFS, "mounted to read only share\n");
			अन्यथा अगर ((cअगरs_sb->mnt_cअगरs_flags &
				  CIFS_MOUNT_RW_CACHE) == 0)
				cअगरs_dbg(VFS, "read only mount of RW share\n");
			/* no need to log a RW mount of a typical RW share */
		पूर्ण
	पूर्ण

	/*
	 * Clamp the rsize/wsize mount arguments अगर they are too big क्रम the server
	 * and set the rsize/wsize to the negotiated values अगर not passed in by
	 * the user on mount
	 */
	अगर ((cअगरs_sb->ctx->wsize == 0) ||
	    (cअगरs_sb->ctx->wsize > server->ops->negotiate_wsize(tcon, ctx)))
		cअगरs_sb->ctx->wsize = server->ops->negotiate_wsize(tcon, ctx);
	अगर ((cअगरs_sb->ctx->rsize == 0) ||
	    (cअगरs_sb->ctx->rsize > server->ops->negotiate_rsize(tcon, ctx)))
		cअगरs_sb->ctx->rsize = server->ops->negotiate_rsize(tcon, ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक mount_setup_tlink(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा cअगरs_ses *ses,
			     काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा tcon_link *tlink;

	/* hang the tcon off of the superblock */
	tlink = kzalloc(माप(*tlink), GFP_KERNEL);
	अगर (tlink == शून्य)
		वापस -ENOMEM;

	tlink->tl_uid = ses->linux_uid;
	tlink->tl_tcon = tcon;
	tlink->tl_समय = jअगरfies;
	set_bit(TCON_LINK_MASTER, &tlink->tl_flags);
	set_bit(TCON_LINK_IN_TREE, &tlink->tl_flags);

	cअगरs_sb->master_tlink = tlink;
	spin_lock(&cअगरs_sb->tlink_tree_lock);
	tlink_rb_insert(&cअगरs_sb->tlink_tree, tlink);
	spin_unlock(&cअगरs_sb->tlink_tree_lock);

	queue_delayed_work(cअगरsiod_wq, &cअगरs_sb->prune_tlinks,
				TLINK_IDLE_EXPIRE);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
/*
 * cअगरs_build_path_to_root वापसs full path to root when we करो not have an
 * existing connection (tcon)
 */
अटल अक्षर *
build_unc_path_to_root(स्थिर काष्ठा smb3_fs_context *ctx,
		       स्थिर काष्ठा cअगरs_sb_info *cअगरs_sb, bool useppath)
अणु
	अक्षर *full_path, *pos;
	अचिन्हित पूर्णांक pplen = useppath && ctx->prepath ?
		म_माप(ctx->prepath) + 1 : 0;
	अचिन्हित पूर्णांक unc_len = strnlen(ctx->UNC, MAX_TREE_SIZE + 1);

	अगर (unc_len > MAX_TREE_SIZE)
		वापस ERR_PTR(-EINVAL);

	full_path = kदो_स्मृति(unc_len + pplen + 1, GFP_KERNEL);
	अगर (full_path == शून्य)
		वापस ERR_PTR(-ENOMEM);

	स_नकल(full_path, ctx->UNC, unc_len);
	pos = full_path + unc_len;

	अगर (pplen) अणु
		*pos = CIFS_सूची_SEP(cअगरs_sb);
		स_नकल(pos + 1, ctx->prepath, pplen);
		pos += pplen;
	पूर्ण

	*pos = '\0'; /* add trailing null */
	convert_delimiter(full_path, CIFS_सूची_SEP(cअगरs_sb));
	cअगरs_dbg(FYI, "%s: full_path=%s\n", __func__, full_path);
	वापस full_path;
पूर्ण

/**
 * expand_dfs_referral - Perक्रमm a dfs referral query and update the cअगरs_sb
 *
 * If a referral is found, cअगरs_sb->ctx->mount_options will be (re-)allocated
 * to a string containing updated options क्रम the submount.  Otherwise it
 * will be left untouched.
 *
 * Returns the rc from get_dfs_path to the caller, which can be used to
 * determine whether there were referrals.
 */
अटल पूर्णांक
expand_dfs_referral(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
		    काष्ठा smb3_fs_context *ctx, काष्ठा cअगरs_sb_info *cअगरs_sb,
		    अक्षर *ref_path)
अणु
	पूर्णांक rc;
	काष्ठा dfs_info3_param referral = अणु0पूर्ण;
	अक्षर *full_path = शून्य, *mdata = शून्य;

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_DFS)
		वापस -EREMOTE;

	full_path = build_unc_path_to_root(ctx, cअगरs_sb, true);
	अगर (IS_ERR(full_path))
		वापस PTR_ERR(full_path);

	rc = dfs_cache_find(xid, ses, cअगरs_sb->local_nls, cअगरs_remap(cअगरs_sb),
			    ref_path, &referral, शून्य);
	अगर (!rc) अणु
		अक्षर *fake_devname = शून्य;

		mdata = cअगरs_compose_mount_options(cअगरs_sb->ctx->mount_options,
						   full_path + 1, &referral,
						   &fake_devname);
		मुक्त_dfs_info_param(&referral);

		अगर (IS_ERR(mdata)) अणु
			rc = PTR_ERR(mdata);
			mdata = शून्य;
		पूर्ण अन्यथा अणु
			/*
			 * We can not clear out the whole काष्ठाure since we
			 * no दीर्घer have an explicit function to parse
			 * a mount-string. Instead we need to clear out the
			 * inभागidual fields that are no दीर्घer valid.
			 */
			kमुक्त(ctx->prepath);
			ctx->prepath = शून्य;
			rc = cअगरs_setup_volume_info(ctx, mdata, fake_devname);
		पूर्ण
		kमुक्त(fake_devname);
		kमुक्त(cअगरs_sb->ctx->mount_options);
		cअगरs_sb->ctx->mount_options = mdata;
	पूर्ण
	kमुक्त(full_path);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक get_next_dfs_tgt(स्थिर अक्षर *path,
				   काष्ठा dfs_cache_tgt_list *tgt_list,
				   काष्ठा dfs_cache_tgt_iterator **tgt_it)
अणु
	अगर (!*tgt_it)
		*tgt_it = dfs_cache_get_tgt_iterator(tgt_list);
	अन्यथा
		*tgt_it = dfs_cache_get_next_tgt(tgt_list, *tgt_it);
	वापस !*tgt_it ? -EHOSTDOWN : 0;
पूर्ण

अटल पूर्णांक update_vol_info(स्थिर काष्ठा dfs_cache_tgt_iterator *tgt_it,
			   काष्ठा smb3_fs_context *fake_ctx, काष्ठा smb3_fs_context *ctx)
अणु
	स्थिर अक्षर *tgt = dfs_cache_get_tgt_name(tgt_it);
	पूर्णांक len = म_माप(tgt) + 2;
	अक्षर *new_unc;

	new_unc = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!new_unc)
		वापस -ENOMEM;
	scnम_लिखो(new_unc, len, "\\%s", tgt);

	kमुक्त(ctx->UNC);
	ctx->UNC = new_unc;

	अगर (fake_ctx->prepath) अणु
		kमुक्त(ctx->prepath);
		ctx->prepath = fake_ctx->prepath;
		fake_ctx->prepath = शून्य;
	पूर्ण
	स_नकल(&ctx->dstaddr, &fake_ctx->dstaddr, माप(ctx->dstaddr));

	वापस 0;
पूर्ण

अटल पूर्णांक करो_dfs_failover(स्थिर अक्षर *path, स्थिर अक्षर *full_path, काष्ठा cअगरs_sb_info *cअगरs_sb,
			   काष्ठा smb3_fs_context *ctx, काष्ठा cअगरs_ses *root_ses,
			   अचिन्हित पूर्णांक *xid, काष्ठा TCP_Server_Info **server,
			   काष्ठा cअगरs_ses **ses, काष्ठा cअगरs_tcon **tcon)
अणु
	पूर्णांक rc;
	काष्ठा dfs_cache_tgt_list tgt_list = अणु0पूर्ण;
	काष्ठा dfs_cache_tgt_iterator *tgt_it = शून्य;
	काष्ठा smb3_fs_context पंचांगp_ctx = अणुशून्यपूर्ण;

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_DFS)
		वापस -EOPNOTSUPP;

	cअगरs_dbg(FYI, "%s: path=%s full_path=%s\n", __func__, path, full_path);

	rc = dfs_cache_noreq_find(path, शून्य, &tgt_list);
	अगर (rc)
		वापस rc;
	/*
	 * We use a 'tmp_ctx' here because we need pass it करोwn to the mount_अणुget,putपूर्ण functions to
	 * test connection against new DFS tarमाला_लो.
	 */
	rc = smb3_fs_context_dup(&पंचांगp_ctx, ctx);
	अगर (rc)
		जाओ out;

	क्रम (;;) अणु
		काष्ठा dfs_info3_param ref = अणु0पूर्ण;
		अक्षर *fake_devname = शून्य, *mdata = शून्य;

		/* Get next DFS target server - अगर any */
		rc = get_next_dfs_tgt(path, &tgt_list, &tgt_it);
		अगर (rc)
			अवरोध;

		rc = dfs_cache_get_tgt_referral(path, tgt_it, &ref);
		अगर (rc)
			अवरोध;

		cअगरs_dbg(FYI, "%s: old ctx: UNC=%s prepath=%s\n", __func__, पंचांगp_ctx.UNC,
			 पंचांगp_ctx.prepath);

		mdata = cअगरs_compose_mount_options(cअगरs_sb->ctx->mount_options, full_path + 1, &ref,
						   &fake_devname);
		मुक्त_dfs_info_param(&ref);

		अगर (IS_ERR(mdata)) अणु
			rc = PTR_ERR(mdata);
			mdata = शून्य;
		पूर्ण अन्यथा
			rc = cअगरs_setup_volume_info(&पंचांगp_ctx, mdata, fake_devname);

		kमुक्त(mdata);
		kमुक्त(fake_devname);

		अगर (rc)
			अवरोध;

		cअगरs_dbg(FYI, "%s: new ctx: UNC=%s prepath=%s\n", __func__, पंचांगp_ctx.UNC,
			 पंचांगp_ctx.prepath);

		mount_put_conns(cअगरs_sb, *xid, *server, *ses, *tcon);
		rc = mount_get_conns(&पंचांगp_ctx, cअगरs_sb, xid, server, ses, tcon);
		अगर (!rc || (*server && *ses)) अणु
			/*
			 * We were able to connect to new target server. Update current context with
			 * new target server.
			 */
			rc = update_vol_info(tgt_it, &पंचांगp_ctx, ctx);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!rc) अणु
		cअगरs_dbg(FYI, "%s: final ctx: UNC=%s prepath=%s\n", __func__, पंचांगp_ctx.UNC,
			 पंचांगp_ctx.prepath);
		/*
		 * Update DFS target hपूर्णांक in DFS referral cache with the target server we
		 * successfully reconnected to.
		 */
		rc = dfs_cache_update_tgthपूर्णांक(*xid, root_ses ? root_ses : *ses, cअगरs_sb->local_nls,
					      cअगरs_remap(cअगरs_sb), path, tgt_it);
	पूर्ण

out:
	smb3_cleanup_fs_context_contents(&पंचांगp_ctx);
	dfs_cache_मुक्त_tgts(&tgt_list);
	वापस rc;
पूर्ण
#पूर्ण_अगर

/* TODO: all callers to this are broken. We are not parsing mount_options here
 * we should pass a clone of the original context?
 */
पूर्णांक
cअगरs_setup_volume_info(काष्ठा smb3_fs_context *ctx, स्थिर अक्षर *mntopts, स्थिर अक्षर *devname)
अणु
	पूर्णांक rc;

	अगर (devname) अणु
		cअगरs_dbg(FYI, "%s: devname=%s\n", __func__, devname);
		rc = smb3_parse_devname(devname, ctx);
		अगर (rc) अणु
			cअगरs_dbg(VFS, "%s: failed to parse %s: %d\n", __func__, devname, rc);
			वापस rc;
		पूर्ण
	पूर्ण

	अगर (mntopts) अणु
		अक्षर *ip;

		rc = smb3_parse_opt(mntopts, "ip", &ip);
		अगर (rc) अणु
			cअगरs_dbg(VFS, "%s: failed to parse ip options: %d\n", __func__, rc);
			वापस rc;
		पूर्ण

		rc = cअगरs_convert_address((काष्ठा sockaddr *)&ctx->dstaddr, ip, म_माप(ip));
		kमुक्त(ip);
		अगर (!rc) अणु
			cअगरs_dbg(VFS, "%s: failed to convert ip address\n", __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (ctx->nullauth) अणु
		cअगरs_dbg(FYI, "Anonymous login\n");
		kमुक्त(ctx->username);
		ctx->username = शून्य;
	पूर्ण अन्यथा अगर (ctx->username) अणु
		/* BB fixme parse क्रम करोमुख्य name here */
		cअगरs_dbg(FYI, "Username: %s\n", ctx->username);
	पूर्ण अन्यथा अणु
		cअगरs_dbg(VFS, "No username specified\n");
	/* In userspace mount helper we can get user name from alternate
	   locations such as env variables and files on disk */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
cअगरs_are_all_path_components_accessible(काष्ठा TCP_Server_Info *server,
					अचिन्हित पूर्णांक xid,
					काष्ठा cअगरs_tcon *tcon,
					काष्ठा cअगरs_sb_info *cअगरs_sb,
					अक्षर *full_path,
					पूर्णांक added_treename)
अणु
	पूर्णांक rc;
	अक्षर *s;
	अक्षर sep, पंचांगp;
	पूर्णांक skip = added_treename ? 1 : 0;

	sep = CIFS_सूची_SEP(cअगरs_sb);
	s = full_path;

	rc = server->ops->is_path_accessible(xid, tcon, cअगरs_sb, "");
	जबतक (rc == 0) अणु
		/* skip separators */
		जबतक (*s == sep)
			s++;
		अगर (!*s)
			अवरोध;
		/* next separator */
		जबतक (*s && *s != sep)
			s++;
		/*
		 * अगर the treename is added, we then have to skip the first
		 * part within the separators
		 */
		अगर (skip) अणु
			skip = 0;
			जारी;
		पूर्ण
		/*
		 * temporarily null-terminate the path at the end of
		 * the current component
		 */
		पंचांगp = *s;
		*s = 0;
		rc = server->ops->is_path_accessible(xid, tcon, cअगरs_sb,
						     full_path);
		*s = पंचांगp;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Check अगर path is remote (e.g. a DFS share). Return -EREMOTE अगर it is,
 * otherwise 0.
 */
अटल पूर्णांक is_path_remote(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा smb3_fs_context *ctx,
			  स्थिर अचिन्हित पूर्णांक xid,
			  काष्ठा TCP_Server_Info *server,
			  काष्ठा cअगरs_tcon *tcon)
अणु
	पूर्णांक rc;
	अक्षर *full_path;

	अगर (!server->ops->is_path_accessible)
		वापस -EOPNOTSUPP;

	/*
	 * cअगरs_build_path_to_root works only when we have a valid tcon
	 */
	full_path = cअगरs_build_path_to_root(ctx, cअगरs_sb, tcon,
					    tcon->Flags & SMB_SHARE_IS_IN_DFS);
	अगर (full_path == शून्य)
		वापस -ENOMEM;

	cअगरs_dbg(FYI, "%s: full_path: %s\n", __func__, full_path);

	rc = server->ops->is_path_accessible(xid, tcon, cअगरs_sb,
					     full_path);
	अगर (rc != 0 && rc != -EREMOTE) अणु
		kमुक्त(full_path);
		वापस rc;
	पूर्ण

	अगर (rc != -EREMOTE) अणु
		rc = cअगरs_are_all_path_components_accessible(server, xid, tcon,
			cअगरs_sb, full_path, tcon->Flags & SMB_SHARE_IS_IN_DFS);
		अगर (rc != 0) अणु
			cअगरs_server_dbg(VFS, "cannot query dirs between root and final path, enabling CIFS_MOUNT_USE_PREFIX_PATH\n");
			cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_USE_PREFIX_PATH;
			rc = 0;
		पूर्ण
	पूर्ण

	kमुक्त(full_path);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
अटल व्योम set_root_ses(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा cअगरs_ses *ses,
			 काष्ठा cअगरs_ses **root_ses)
अणु
	अगर (ses) अणु
		spin_lock(&cअगरs_tcp_ses_lock);
		ses->ses_count++;
		अगर (ses->tcon_ipc)
			ses->tcon_ipc->remap = cअगरs_remap(cअगरs_sb);
		spin_unlock(&cअगरs_tcp_ses_lock);
	पूर्ण
	*root_ses = ses;
पूर्ण

अटल व्योम put_root_ses(काष्ठा cअगरs_ses *ses)
अणु
	अगर (ses)
		cअगरs_put_smb_ses(ses);
पूर्ण

/* Set up next dfs prefix path in @dfs_path */
अटल पूर्णांक next_dfs_prepath(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा smb3_fs_context *ctx,
			    स्थिर अचिन्हित पूर्णांक xid, काष्ठा TCP_Server_Info *server,
			    काष्ठा cअगरs_tcon *tcon, अक्षर **dfs_path)
अणु
	अक्षर *path, *npath;
	पूर्णांक added_treename = is_tcon_dfs(tcon);
	पूर्णांक rc;

	path = cअगरs_build_path_to_root(ctx, cअगरs_sb, tcon, added_treename);
	अगर (!path)
		वापस -ENOMEM;

	rc = is_path_remote(cअगरs_sb, ctx, xid, server, tcon);
	अगर (rc == -EREMOTE) अणु
		काष्ठा smb3_fs_context v = अणुशून्यपूर्ण;
		/* अगर @path contains a tree name, skip it in the prefix path */
		अगर (added_treename) अणु
			rc = smb3_parse_devname(path, &v);
			अगर (rc)
				जाओ out;
			npath = build_unc_path_to_root(&v, cअगरs_sb, true);
			smb3_cleanup_fs_context_contents(&v);
		पूर्ण अन्यथा अणु
			v.UNC = ctx->UNC;
			v.prepath = path + 1;
			npath = build_unc_path_to_root(&v, cअगरs_sb, true);
		पूर्ण

		अगर (IS_ERR(npath)) अणु
			rc = PTR_ERR(npath);
			जाओ out;
		पूर्ण

		kमुक्त(*dfs_path);
		*dfs_path = npath;
		rc = -EREMOTE;
	पूर्ण

out:
	kमुक्त(path);
	वापस rc;
पूर्ण

/* Check अगर resolved tarमाला_लो can handle any DFS referrals */
अटल पूर्णांक is_referral_server(स्थिर अक्षर *ref_path, काष्ठा cअगरs_tcon *tcon, bool *ref_server)
अणु
	पूर्णांक rc;
	काष्ठा dfs_info3_param ref = अणु0पूर्ण;

	अगर (is_tcon_dfs(tcon)) अणु
		*ref_server = true;
	पूर्ण अन्यथा अणु
		cअगरs_dbg(FYI, "%s: ref_path=%s\n", __func__, ref_path);

		rc = dfs_cache_noreq_find(ref_path, &ref, शून्य);
		अगर (rc) अणु
			cअगरs_dbg(VFS, "%s: dfs_cache_noreq_find: failed (rc=%d)\n", __func__, rc);
			वापस rc;
		पूर्ण
		cअगरs_dbg(FYI, "%s: ref.flags=0x%x\n", __func__, ref.flags);
		/*
		 * Check अगर all tarमाला_लो are capable of handling DFS referrals as per
		 * MS-DFSC 2.2.4 RESP_GET_DFS_REFERRAL.
		 */
		*ref_server = !!(ref.flags & DFSREF_REFERRAL_SERVER);
		मुक्त_dfs_info_param(&ref);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cअगरs_mount(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा smb3_fs_context *ctx)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक xid;
	काष्ठा TCP_Server_Info *server = शून्य;
	काष्ठा cअगरs_ses *ses = शून्य, *root_ses = शून्य;
	काष्ठा cअगरs_tcon *tcon = शून्य;
	पूर्णांक count = 0;
	अक्षर *ref_path = शून्य, *full_path = शून्य;
	अक्षर *oldmnt = शून्य;
	अक्षर *mntdata = शून्य;
	bool ref_server = false;

	rc = mount_get_conns(ctx, cअगरs_sb, &xid, &server, &ses, &tcon);
	/*
	 * If called with 'nodfs' mount option, then skip DFS resolving.  Otherwise unconditionally
	 * try to get an DFS referral (even cached) to determine whether it is an DFS mount.
	 *
	 * Skip prefix path to provide support क्रम DFS referrals from w2k8 servers which करोn't seem
	 * to respond with PATH_NOT_COVERED to requests that include the prefix.
	 */
	अगर ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_DFS) ||
	    dfs_cache_find(xid, ses, cअगरs_sb->local_nls, cअगरs_remap(cअगरs_sb), ctx->UNC + 1, शून्य,
			   शून्य)) अणु
		अगर (rc)
			जाओ error;
		/* Check अगर it is fully accessible and then mount it */
		rc = is_path_remote(cअगरs_sb, ctx, xid, server, tcon);
		अगर (!rc)
			जाओ out;
		अगर (rc != -EREMOTE)
			जाओ error;
	पूर्ण
	/* Save mount options */
	mntdata = kstrdup(cअगरs_sb->ctx->mount_options, GFP_KERNEL);
	अगर (!mntdata) अणु
		rc = -ENOMEM;
		जाओ error;
	पूर्ण
	/* Get path of DFS root */
	ref_path = build_unc_path_to_root(ctx, cअगरs_sb, false);
	अगर (IS_ERR(ref_path)) अणु
		rc = PTR_ERR(ref_path);
		ref_path = शून्य;
		जाओ error;
	पूर्ण

	set_root_ses(cअगरs_sb, ses, &root_ses);
	करो अणु
		/* Save full path of last DFS path we used to resolve final target server */
		kमुक्त(full_path);
		full_path = build_unc_path_to_root(ctx, cअगरs_sb, !!count);
		अगर (IS_ERR(full_path)) अणु
			rc = PTR_ERR(full_path);
			full_path = शून्य;
			अवरोध;
		पूर्ण
		/* Chase referral */
		oldmnt = cअगरs_sb->ctx->mount_options;
		rc = expand_dfs_referral(xid, root_ses, ctx, cअगरs_sb, ref_path + 1);
		अगर (rc)
			अवरोध;
		/* Connect to new DFS target only अगर we were redirected */
		अगर (oldmnt != cअगरs_sb->ctx->mount_options) अणु
			mount_put_conns(cअगरs_sb, xid, server, ses, tcon);
			rc = mount_get_conns(ctx, cअगरs_sb, &xid, &server, &ses, &tcon);
		पूर्ण
		अगर (rc && !server && !ses) अणु
			/* Failed to connect. Try to connect to other tarमाला_लो in the referral. */
			rc = करो_dfs_failover(ref_path + 1, full_path, cअगरs_sb, ctx, root_ses, &xid,
					     &server, &ses, &tcon);
		पूर्ण
		अगर (rc == -EACCES || rc == -EOPNOTSUPP || !server || !ses)
			अवरोध;
		अगर (!tcon)
			जारी;

		/* Make sure that requests go through new root servers */
		rc = is_referral_server(ref_path + 1, tcon, &ref_server);
		अगर (rc)
			अवरोध;
		अगर (ref_server) अणु
			put_root_ses(root_ses);
			set_root_ses(cअगरs_sb, ses, &root_ses);
		पूर्ण

		/* Get next dfs path and then जारी chasing them अगर -EREMOTE */
		rc = next_dfs_prepath(cअगरs_sb, ctx, xid, server, tcon, &ref_path);
		/* Prevent recursion on broken link referrals */
		अगर (rc == -EREMOTE && ++count > MAX_NESTED_LINKS)
			rc = -ELOOP;
	पूर्ण जबतक (rc == -EREMOTE);

	अगर (rc)
		जाओ error;
	put_root_ses(root_ses);
	root_ses = शून्य;
	kमुक्त(ref_path);
	ref_path = शून्य;
	/*
	 * Store DFS full path in both superblock and tree connect काष्ठाures.
	 *
	 * For DFS root mounts, the prefix path (cअगरs_sb->prepath) is preserved during reconnect so
	 * only the root path is set in cअगरs_sb->origin_fullpath and tcon->dfs_path. And क्रम DFS
	 * links, the prefix path is included in both and may be changed during reconnect.  See
	 * cअगरs_tree_connect().
	 */
	cअगरs_sb->origin_fullpath = kstrdup(full_path, GFP_KERNEL);
	अगर (!cअगरs_sb->origin_fullpath) अणु
		rc = -ENOMEM;
		जाओ error;
	पूर्ण
	spin_lock(&cअगरs_tcp_ses_lock);
	tcon->dfs_path = full_path;
	full_path = शून्य;
	tcon->remap = cअगरs_remap(cअगरs_sb);
	spin_unlock(&cअगरs_tcp_ses_lock);

	/* Add original context क्रम DFS cache to be used when refreshing referrals */
	rc = dfs_cache_add_vol(mntdata, ctx, cअगरs_sb->origin_fullpath);
	अगर (rc)
		जाओ error;
	/*
	 * After reconnecting to a dअगरferent server, unique ids won't
	 * match anymore, so we disable serverino. This prevents
	 * dentry revalidation to think the dentry are stale (ESTALE).
	 */
	cअगरs_स्वतःdisable_serverino(cअगरs_sb);
	/*
	 * Force the use of prefix path to support failover on DFS paths that
	 * resolve to tarमाला_लो that have dअगरferent prefix paths.
	 */
	cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_USE_PREFIX_PATH;
	kमुक्त(cअगरs_sb->prepath);
	cअगरs_sb->prepath = ctx->prepath;
	ctx->prepath = शून्य;

out:
	मुक्त_xid(xid);
	cअगरs_try_adding_channels(cअगरs_sb, ses);
	वापस mount_setup_tlink(cअगरs_sb, ses, tcon);

error:
	kमुक्त(ref_path);
	kमुक्त(full_path);
	kमुक्त(mntdata);
	kमुक्त(cअगरs_sb->origin_fullpath);
	put_root_ses(root_ses);
	mount_put_conns(cअगरs_sb, xid, server, ses, tcon);
	वापस rc;
पूर्ण
#अन्यथा
पूर्णांक cअगरs_mount(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा smb3_fs_context *ctx)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;

	rc = mount_get_conns(ctx, cअगरs_sb, &xid, &server, &ses, &tcon);
	अगर (rc)
		जाओ error;

	अगर (tcon) अणु
		rc = is_path_remote(cअगरs_sb, ctx, xid, server, tcon);
		अगर (rc == -EREMOTE)
			rc = -EOPNOTSUPP;
		अगर (rc)
			जाओ error;
	पूर्ण

	मुक्त_xid(xid);

	वापस mount_setup_tlink(cअगरs_sb, ses, tcon);

error:
	mount_put_conns(cअगरs_sb, xid, server, ses, tcon);
	वापस rc;
पूर्ण
#पूर्ण_अगर

/*
 * Issue a TREE_CONNECT request.
 */
पूर्णांक
CIFSTCon(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
	 स्थिर अक्षर *tree, काष्ठा cअगरs_tcon *tcon,
	 स्थिर काष्ठा nls_table *nls_codepage)
अणु
	काष्ठा smb_hdr *smb_buffer;
	काष्ठा smb_hdr *smb_buffer_response;
	TCONX_REQ *pSMB;
	TCONX_RSP *pSMBr;
	अचिन्हित अक्षर *bcc_ptr;
	पूर्णांक rc = 0;
	पूर्णांक length;
	__u16 bytes_left, count;

	अगर (ses == शून्य)
		वापस -EIO;

	smb_buffer = cअगरs_buf_get();
	अगर (smb_buffer == शून्य)
		वापस -ENOMEM;

	smb_buffer_response = smb_buffer;

	header_assemble(smb_buffer, SMB_COM_TREE_CONNECT_ANDX,
			शून्य /*no tid */ , 4 /*wct */ );

	smb_buffer->Mid = get_next_mid(ses->server);
	smb_buffer->Uid = ses->Suid;
	pSMB = (TCONX_REQ *) smb_buffer;
	pSMBr = (TCONX_RSP *) smb_buffer_response;

	pSMB->AndXCommand = 0xFF;
	pSMB->Flags = cpu_to_le16(TCON_EXTENDED_SECINFO);
	bcc_ptr = &pSMB->Password[0];
	अगर (tcon->pipe || (ses->server->sec_mode & SECMODE_USER)) अणु
		pSMB->PasswordLength = cpu_to_le16(1);	/* minimum */
		*bcc_ptr = 0; /* password is null byte */
		bcc_ptr++;              /* skip password */
		/* alपढ़ोy aligned so no need to करो it below */
	पूर्ण अन्यथा अणु
		pSMB->PasswordLength = cpu_to_le16(CIFS_AUTH_RESP_SIZE);
		/* BB FIXME add code to fail this अगर NTLMv2 or Kerberos
		   specअगरied as required (when that support is added to
		   the vfs in the future) as only NTLM or the much
		   weaker LANMAN (which we करो not send by शेष) is accepted
		   by Samba (not sure whether other servers allow
		   NTLMv2 password here) */
#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
		अगर ((global_secflags & CIFSSEC_MAY_LANMAN) &&
		    (ses->sectype == LANMAN))
			calc_lanman_hash(tcon->password, ses->server->cryptkey,
					 ses->server->sec_mode &
					    SECMODE_PW_ENCRYPT ? true : false,
					 bcc_ptr);
		अन्यथा
#पूर्ण_अगर /* CIFS_WEAK_PW_HASH */
		rc = SMBNTencrypt(tcon->password, ses->server->cryptkey,
					bcc_ptr, nls_codepage);
		अगर (rc) अणु
			cअगरs_dbg(FYI, "%s Can't generate NTLM rsp. Error: %d\n",
				 __func__, rc);
			cअगरs_buf_release(smb_buffer);
			वापस rc;
		पूर्ण

		bcc_ptr += CIFS_AUTH_RESP_SIZE;
		अगर (ses->capabilities & CAP_UNICODE) अणु
			/* must align unicode strings */
			*bcc_ptr = 0; /* null byte password */
			bcc_ptr++;
		पूर्ण
	पूर्ण

	अगर (ses->server->sign)
		smb_buffer->Flags2 |= SMBFLG2_SECURITY_SIGNATURE;

	अगर (ses->capabilities & CAP_STATUS32) अणु
		smb_buffer->Flags2 |= SMBFLG2_ERR_STATUS;
	पूर्ण
	अगर (ses->capabilities & CAP_DFS) अणु
		smb_buffer->Flags2 |= SMBFLG2_DFS;
	पूर्ण
	अगर (ses->capabilities & CAP_UNICODE) अणु
		smb_buffer->Flags2 |= SMBFLG2_UNICODE;
		length =
		    cअगरs_strtoUTF16((__le16 *) bcc_ptr, tree,
			6 /* max utf8 अक्षर length in bytes */ *
			(/* server len*/ + 256 /* share len */), nls_codepage);
		bcc_ptr += 2 * length;	/* convert num 16 bit words to bytes */
		bcc_ptr += 2;	/* skip trailing null */
	पूर्ण अन्यथा अणु		/* ASCII */
		म_नकल(bcc_ptr, tree);
		bcc_ptr += म_माप(tree) + 1;
	पूर्ण
	म_नकल(bcc_ptr, "?????");
	bcc_ptr += म_माप("?????");
	bcc_ptr += 1;
	count = bcc_ptr - &pSMB->Password[0];
	be32_add_cpu(&pSMB->hdr.smb_buf_length, count);
	pSMB->ByteCount = cpu_to_le16(count);

	rc = SendReceive(xid, ses, smb_buffer, smb_buffer_response, &length,
			 0);

	/* above now करोne in SendReceive */
	अगर (rc == 0) अणु
		bool is_unicode;

		tcon->tidStatus = CअगरsGood;
		tcon->need_reconnect = false;
		tcon->tid = smb_buffer_response->Tid;
		bcc_ptr = pByteArea(smb_buffer_response);
		bytes_left = get_bcc(smb_buffer_response);
		length = strnlen(bcc_ptr, bytes_left - 2);
		अगर (smb_buffer->Flags2 & SMBFLG2_UNICODE)
			is_unicode = true;
		अन्यथा
			is_unicode = false;


		/* skip service field (NB: this field is always ASCII) */
		अगर (length == 3) अणु
			अगर ((bcc_ptr[0] == 'I') && (bcc_ptr[1] == 'P') &&
			    (bcc_ptr[2] == 'C')) अणु
				cअगरs_dbg(FYI, "IPC connection\n");
				tcon->ipc = true;
				tcon->pipe = true;
			पूर्ण
		पूर्ण अन्यथा अगर (length == 2) अणु
			अगर ((bcc_ptr[0] == 'A') && (bcc_ptr[1] == ':')) अणु
				/* the most common हाल */
				cअगरs_dbg(FYI, "disk share connection\n");
			पूर्ण
		पूर्ण
		bcc_ptr += length + 1;
		bytes_left -= (length + 1);
		strlcpy(tcon->treeName, tree, माप(tcon->treeName));

		/* mostly inक्रमmational -- no need to fail on error here */
		kमुक्त(tcon->nativeFileSystem);
		tcon->nativeFileSystem = cअगरs_strndup_from_utf16(bcc_ptr,
						      bytes_left, is_unicode,
						      nls_codepage);

		cअगरs_dbg(FYI, "nativeFileSystem=%s\n", tcon->nativeFileSystem);

		अगर ((smb_buffer_response->WordCount == 3) ||
			 (smb_buffer_response->WordCount == 7))
			/* field is in same location */
			tcon->Flags = le16_to_cpu(pSMBr->OptionalSupport);
		अन्यथा
			tcon->Flags = 0;
		cअगरs_dbg(FYI, "Tcon flags: 0x%x\n", tcon->Flags);
	पूर्ण

	cअगरs_buf_release(smb_buffer);
	वापस rc;
पूर्ण

अटल व्योम delayed_मुक्त(काष्ठा rcu_head *p)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = container_of(p, काष्ठा cअगरs_sb_info, rcu);

	unload_nls(cअगरs_sb->local_nls);
	smb3_cleanup_fs_context(cअगरs_sb->ctx);
	kमुक्त(cअगरs_sb);
पूर्ण

व्योम
cअगरs_umount(काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	काष्ठा rb_root *root = &cअगरs_sb->tlink_tree;
	काष्ठा rb_node *node;
	काष्ठा tcon_link *tlink;

	cancel_delayed_work_sync(&cअगरs_sb->prune_tlinks);

	spin_lock(&cअगरs_sb->tlink_tree_lock);
	जबतक ((node = rb_first(root))) अणु
		tlink = rb_entry(node, काष्ठा tcon_link, tl_rbnode);
		cअगरs_get_tlink(tlink);
		clear_bit(TCON_LINK_IN_TREE, &tlink->tl_flags);
		rb_erase(node, root);

		spin_unlock(&cअगरs_sb->tlink_tree_lock);
		cअगरs_put_tlink(tlink);
		spin_lock(&cअगरs_sb->tlink_tree_lock);
	पूर्ण
	spin_unlock(&cअगरs_sb->tlink_tree_lock);

	kमुक्त(cअगरs_sb->prepath);
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	dfs_cache_del_vol(cअगरs_sb->origin_fullpath);
	kमुक्त(cअगरs_sb->origin_fullpath);
#पूर्ण_अगर
	call_rcu(&cअगरs_sb->rcu, delayed_मुक्त);
पूर्ण

पूर्णांक
cअगरs_negotiate_protocol(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses)
अणु
	पूर्णांक rc = 0;
	काष्ठा TCP_Server_Info *server = cअगरs_ses_server(ses);

	अगर (!server->ops->need_neg || !server->ops->negotiate)
		वापस -ENOSYS;

	/* only send once per connect */
	अगर (!server->ops->need_neg(server))
		वापस 0;

	rc = server->ops->negotiate(xid, ses);
	अगर (rc == 0) अणु
		spin_lock(&GlobalMid_Lock);
		अगर (server->tcpStatus == CअगरsNeedNegotiate)
			server->tcpStatus = CअगरsGood;
		अन्यथा
			rc = -EHOSTDOWN;
		spin_unlock(&GlobalMid_Lock);
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक
cअगरs_setup_session(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
		   काष्ठा nls_table *nls_info)
अणु
	पूर्णांक rc = -ENOSYS;
	काष्ठा TCP_Server_Info *server = cअगरs_ses_server(ses);

	अगर (!ses->binding) अणु
		ses->capabilities = server->capabilities;
		अगर (!linuxExtEnabled)
			ses->capabilities &= (~server->vals->cap_unix);

		अगर (ses->auth_key.response) अणु
			cअगरs_dbg(FYI, "Free previous auth_key.response = %p\n",
				 ses->auth_key.response);
			kमुक्त(ses->auth_key.response);
			ses->auth_key.response = शून्य;
			ses->auth_key.len = 0;
		पूर्ण
	पूर्ण

	cअगरs_dbg(FYI, "Security Mode: 0x%x Capabilities: 0x%x TimeAdjust: %d\n",
		 server->sec_mode, server->capabilities, server->समयAdj);

	अगर (server->ops->sess_setup)
		rc = server->ops->sess_setup(xid, ses, nls_info);

	अगर (rc)
		cअगरs_server_dbg(VFS, "Send error in SessSetup = %d\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_set_vol_auth(काष्ठा smb3_fs_context *ctx, काष्ठा cअगरs_ses *ses)
अणु
	ctx->sectype = ses->sectype;

	/* krb5 is special, since we करोn't need username or pw */
	अगर (ctx->sectype == Kerberos)
		वापस 0;

	वापस cअगरs_set_cअगरscreds(ctx, ses);
पूर्ण

अटल काष्ठा cअगरs_tcon *
cअगरs_स्थिरruct_tcon(काष्ठा cअगरs_sb_info *cअगरs_sb, kuid_t fsuid)
अणु
	पूर्णांक rc;
	काष्ठा cअगरs_tcon *master_tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon = शून्य;
	काष्ठा smb3_fs_context *ctx;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (ctx == शून्य)
		वापस ERR_PTR(-ENOMEM);

	ctx->local_nls = cअगरs_sb->local_nls;
	ctx->linux_uid = fsuid;
	ctx->cred_uid = fsuid;
	ctx->UNC = master_tcon->treeName;
	ctx->retry = master_tcon->retry;
	ctx->noहाल = master_tcon->noहाल;
	ctx->nohandlecache = master_tcon->nohandlecache;
	ctx->local_lease = master_tcon->local_lease;
	ctx->no_lease = master_tcon->no_lease;
	ctx->resilient = master_tcon->use_resilient;
	ctx->persistent = master_tcon->use_persistent;
	ctx->handle_समयout = master_tcon->handle_समयout;
	ctx->no_linux_ext = !master_tcon->unix_ext;
	ctx->linux_ext = master_tcon->posix_extensions;
	ctx->sectype = master_tcon->ses->sectype;
	ctx->sign = master_tcon->ses->sign;
	ctx->seal = master_tcon->seal;
	ctx->witness = master_tcon->use_witness;

	rc = cअगरs_set_vol_auth(ctx, master_tcon->ses);
	अगर (rc) अणु
		tcon = ERR_PTR(rc);
		जाओ out;
	पूर्ण

	/* get a reference क्रम the same TCP session */
	spin_lock(&cअगरs_tcp_ses_lock);
	++master_tcon->ses->server->srv_count;
	spin_unlock(&cअगरs_tcp_ses_lock);

	ses = cअगरs_get_smb_ses(master_tcon->ses->server, ctx);
	अगर (IS_ERR(ses)) अणु
		tcon = (काष्ठा cअगरs_tcon *)ses;
		cअगरs_put_tcp_session(master_tcon->ses->server, 0);
		जाओ out;
	पूर्ण

	tcon = cअगरs_get_tcon(ses, ctx);
	अगर (IS_ERR(tcon)) अणु
		cअगरs_put_smb_ses(ses);
		जाओ out;
	पूर्ण

	अगर (cap_unix(ses))
		reset_cअगरs_unix_caps(0, tcon, शून्य, ctx);

out:
	kमुक्त(ctx->username);
	kमुक्त_sensitive(ctx->password);
	kमुक्त(ctx);

	वापस tcon;
पूर्ण

काष्ठा cअगरs_tcon *
cअगरs_sb_master_tcon(काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	वापस tlink_tcon(cअगरs_sb_master_tlink(cअगरs_sb));
पूर्ण

/* find and वापस a tlink with given uid */
अटल काष्ठा tcon_link *
tlink_rb_search(काष्ठा rb_root *root, kuid_t uid)
अणु
	काष्ठा rb_node *node = root->rb_node;
	काष्ठा tcon_link *tlink;

	जबतक (node) अणु
		tlink = rb_entry(node, काष्ठा tcon_link, tl_rbnode);

		अगर (uid_gt(tlink->tl_uid, uid))
			node = node->rb_left;
		अन्यथा अगर (uid_lt(tlink->tl_uid, uid))
			node = node->rb_right;
		अन्यथा
			वापस tlink;
	पूर्ण
	वापस शून्य;
पूर्ण

/* insert a tcon_link पूर्णांकo the tree */
अटल व्योम
tlink_rb_insert(काष्ठा rb_root *root, काष्ठा tcon_link *new_tlink)
अणु
	काष्ठा rb_node **new = &(root->rb_node), *parent = शून्य;
	काष्ठा tcon_link *tlink;

	जबतक (*new) अणु
		tlink = rb_entry(*new, काष्ठा tcon_link, tl_rbnode);
		parent = *new;

		अगर (uid_gt(tlink->tl_uid, new_tlink->tl_uid))
			new = &((*new)->rb_left);
		अन्यथा
			new = &((*new)->rb_right);
	पूर्ण

	rb_link_node(&new_tlink->tl_rbnode, parent, new);
	rb_insert_color(&new_tlink->tl_rbnode, root);
पूर्ण

/*
 * Find or स्थिरruct an appropriate tcon given a cअगरs_sb and the fsuid of the
 * current task.
 *
 * If the superblock करोesn't refer to a multiuser mount, then just वापस
 * the master tcon क्रम the mount.
 *
 * First, search the rbtree क्रम an existing tcon क्रम this fsuid. If one
 * exists, then check to see अगर it's pending स्थिरruction. If it is then रुको
 * क्रम स्थिरruction to complete. Once it's no दीर्घer pending, check to see अगर
 * it failed and either वापस an error or retry स्थिरruction, depending on
 * the समयout.
 *
 * If one करोesn't exist then insert a new tcon_link काष्ठा पूर्णांकo the tree and
 * try to स्थिरruct a new one.
 */
काष्ठा tcon_link *
cअगरs_sb_tlink(काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	पूर्णांक ret;
	kuid_t fsuid = current_fsuid();
	काष्ठा tcon_link *tlink, *newtlink;

	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MULTIUSER))
		वापस cअगरs_get_tlink(cअगरs_sb_master_tlink(cअगरs_sb));

	spin_lock(&cअगरs_sb->tlink_tree_lock);
	tlink = tlink_rb_search(&cअगरs_sb->tlink_tree, fsuid);
	अगर (tlink)
		cअगरs_get_tlink(tlink);
	spin_unlock(&cअगरs_sb->tlink_tree_lock);

	अगर (tlink == शून्य) अणु
		newtlink = kzalloc(माप(*tlink), GFP_KERNEL);
		अगर (newtlink == शून्य)
			वापस ERR_PTR(-ENOMEM);
		newtlink->tl_uid = fsuid;
		newtlink->tl_tcon = ERR_PTR(-EACCES);
		set_bit(TCON_LINK_PENDING, &newtlink->tl_flags);
		set_bit(TCON_LINK_IN_TREE, &newtlink->tl_flags);
		cअगरs_get_tlink(newtlink);

		spin_lock(&cअगरs_sb->tlink_tree_lock);
		/* was one inserted after previous search? */
		tlink = tlink_rb_search(&cअगरs_sb->tlink_tree, fsuid);
		अगर (tlink) अणु
			cअगरs_get_tlink(tlink);
			spin_unlock(&cअगरs_sb->tlink_tree_lock);
			kमुक्त(newtlink);
			जाओ रुको_क्रम_स्थिरruction;
		पूर्ण
		tlink = newtlink;
		tlink_rb_insert(&cअगरs_sb->tlink_tree, tlink);
		spin_unlock(&cअगरs_sb->tlink_tree_lock);
	पूर्ण अन्यथा अणु
रुको_क्रम_स्थिरruction:
		ret = रुको_on_bit(&tlink->tl_flags, TCON_LINK_PENDING,
				  TASK_INTERRUPTIBLE);
		अगर (ret) अणु
			cअगरs_put_tlink(tlink);
			वापस ERR_PTR(-ERESTARTSYS);
		पूर्ण

		/* अगर it's good, वापस it */
		अगर (!IS_ERR(tlink->tl_tcon))
			वापस tlink;

		/* वापस error अगर we tried this alपढ़ोy recently */
		अगर (समय_beक्रमe(jअगरfies, tlink->tl_समय + TLINK_ERROR_EXPIRE)) अणु
			cअगरs_put_tlink(tlink);
			वापस ERR_PTR(-EACCES);
		पूर्ण

		अगर (test_and_set_bit(TCON_LINK_PENDING, &tlink->tl_flags))
			जाओ रुको_क्रम_स्थिरruction;
	पूर्ण

	tlink->tl_tcon = cअगरs_स्थिरruct_tcon(cअगरs_sb, fsuid);
	clear_bit(TCON_LINK_PENDING, &tlink->tl_flags);
	wake_up_bit(&tlink->tl_flags, TCON_LINK_PENDING);

	अगर (IS_ERR(tlink->tl_tcon)) अणु
		cअगरs_put_tlink(tlink);
		वापस ERR_PTR(-EACCES);
	पूर्ण

	वापस tlink;
पूर्ण

/*
 * periodic workqueue job that scans tcon_tree क्रम a superblock and बंदs
 * out tcons.
 */
अटल व्योम
cअगरs_prune_tlinks(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = container_of(work, काष्ठा cअगरs_sb_info,
						    prune_tlinks.work);
	काष्ठा rb_root *root = &cअगरs_sb->tlink_tree;
	काष्ठा rb_node *node;
	काष्ठा rb_node *पंचांगp;
	काष्ठा tcon_link *tlink;

	/*
	 * Because we drop the spinlock in the loop in order to put the tlink
	 * it's not guarded against removal of links from the tree. The only
	 * places that हटाओ entries from the tree are this function and
	 * umounts. Because this function is non-reentrant and is canceled
	 * beक्रमe umount can proceed, this is safe.
	 */
	spin_lock(&cअगरs_sb->tlink_tree_lock);
	node = rb_first(root);
	जबतक (node != शून्य) अणु
		पंचांगp = node;
		node = rb_next(पंचांगp);
		tlink = rb_entry(पंचांगp, काष्ठा tcon_link, tl_rbnode);

		अगर (test_bit(TCON_LINK_MASTER, &tlink->tl_flags) ||
		    atomic_पढ़ो(&tlink->tl_count) != 0 ||
		    समय_after(tlink->tl_समय + TLINK_IDLE_EXPIRE, jअगरfies))
			जारी;

		cअगरs_get_tlink(tlink);
		clear_bit(TCON_LINK_IN_TREE, &tlink->tl_flags);
		rb_erase(पंचांगp, root);

		spin_unlock(&cअगरs_sb->tlink_tree_lock);
		cअगरs_put_tlink(tlink);
		spin_lock(&cअगरs_sb->tlink_tree_lock);
	पूर्ण
	spin_unlock(&cअगरs_sb->tlink_tree_lock);

	queue_delayed_work(cअगरsiod_wq, &cअगरs_sb->prune_tlinks,
				TLINK_IDLE_EXPIRE);
पूर्ण

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
पूर्णांक cअगरs_tree_connect(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, स्थिर काष्ठा nls_table *nlsc)
अणु
	पूर्णांक rc;
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	स्थिर काष्ठा smb_version_operations *ops = server->ops;
	काष्ठा dfs_cache_tgt_list tl;
	काष्ठा dfs_cache_tgt_iterator *it = शून्य;
	अक्षर *tree;
	स्थिर अक्षर *tcp_host;
	माप_प्रकार tcp_host_len;
	स्थिर अक्षर *dfs_host;
	माप_प्रकार dfs_host_len;
	अक्षर *share = शून्य, *prefix = शून्य;
	काष्ठा dfs_info3_param ref = अणु0पूर्ण;
	bool isroot;

	tree = kzalloc(MAX_TREE_SIZE, GFP_KERNEL);
	अगर (!tree)
		वापस -ENOMEM;

	अगर (!tcon->dfs_path) अणु
		अगर (tcon->ipc) अणु
			scnम_लिखो(tree, MAX_TREE_SIZE, "\\\\%s\\IPC$", server->hostname);
			rc = ops->tree_connect(xid, tcon->ses, tree, tcon, nlsc);
		पूर्ण अन्यथा अणु
			rc = ops->tree_connect(xid, tcon->ses, tcon->treeName, tcon, nlsc);
		पूर्ण
		जाओ out;
	पूर्ण

	rc = dfs_cache_noreq_find(tcon->dfs_path + 1, &ref, &tl);
	अगर (rc)
		जाओ out;
	isroot = ref.server_type == DFS_TYPE_ROOT;
	मुक्त_dfs_info_param(&ref);

	extract_unc_hostname(server->hostname, &tcp_host, &tcp_host_len);

	क्रम (it = dfs_cache_get_tgt_iterator(&tl); it; it = dfs_cache_get_next_tgt(&tl, it)) अणु
		bool target_match;

		kमुक्त(share);
		kमुक्त(prefix);
		share = शून्य;
		prefix = शून्य;

		rc = dfs_cache_get_tgt_share(tcon->dfs_path + 1, it, &share, &prefix);
		अगर (rc) अणु
			cअगरs_dbg(VFS, "%s: failed to parse target share %d\n",
				 __func__, rc);
			जारी;
		पूर्ण

		extract_unc_hostname(share, &dfs_host, &dfs_host_len);

		अगर (dfs_host_len != tcp_host_len
		    || strnहालcmp(dfs_host, tcp_host, dfs_host_len) != 0) अणु
			cअगरs_dbg(FYI, "%s: %.*s doesn't match %.*s\n", __func__, (पूर्णांक)dfs_host_len,
				 dfs_host, (पूर्णांक)tcp_host_len, tcp_host);

			rc = match_target_ip(server, dfs_host, dfs_host_len, &target_match);
			अगर (rc) अणु
				cअगरs_dbg(VFS, "%s: failed to match target ip: %d\n", __func__, rc);
				अवरोध;
			पूर्ण

			अगर (!target_match) अणु
				cअगरs_dbg(FYI, "%s: skipping target\n", __func__);
				जारी;
			पूर्ण
		पूर्ण

		अगर (tcon->ipc) अणु
			scnम_लिखो(tree, MAX_TREE_SIZE, "\\\\%s\\IPC$", share);
			rc = ops->tree_connect(xid, tcon->ses, tree, tcon, nlsc);
		पूर्ण अन्यथा अणु
			scnम_लिखो(tree, MAX_TREE_SIZE, "\\%s", share);
			rc = ops->tree_connect(xid, tcon->ses, tree, tcon, nlsc);
			/* Only handle prefix paths of DFS link tarमाला_लो */
			अगर (!rc && !isroot) अणु
				rc = update_super_prepath(tcon, prefix);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (rc == -EREMOTE)
			अवरोध;
	पूर्ण

	kमुक्त(share);
	kमुक्त(prefix);

	अगर (!rc) अणु
		अगर (it)
			rc = dfs_cache_noreq_update_tgthपूर्णांक(tcon->dfs_path + 1, it);
		अन्यथा
			rc = -ENOENT;
	पूर्ण
	dfs_cache_मुक्त_tgts(&tl);
out:
	kमुक्त(tree);
	वापस rc;
पूर्ण
#अन्यथा
पूर्णांक cअगरs_tree_connect(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, स्थिर काष्ठा nls_table *nlsc)
अणु
	स्थिर काष्ठा smb_version_operations *ops = tcon->ses->server->ops;

	वापस ops->tree_connect(xid, tcon->ses, tcon->treeName, tcon, nlsc);
पूर्ण
#पूर्ण_अगर
