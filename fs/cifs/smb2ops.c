<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  SMB2 version specअगरic operations
 *
 *  Copyright (c) 2012, Jeff Layton <jlayton@redhat.com>
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/vfs.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/uuid.h>
#समावेश <linux/sort.h>
#समावेश <crypto/aead.h>
#समावेश <linux/fiemap.h>
#समावेश "cifsfs.h"
#समावेश "cifsglob.h"
#समावेश "smb2pdu.h"
#समावेश "smb2proto.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_unicode.h"
#समावेश "smb2status.h"
#समावेश "smb2glob.h"
#समावेश "cifs_ioctl.h"
#समावेश "smbdirect.h"
#समावेश "fs_context.h"

/* Change credits क्रम dअगरferent ops and वापस the total number of credits */
अटल पूर्णांक
change_conf(काष्ठा TCP_Server_Info *server)
अणु
	server->credits += server->echo_credits + server->oplock_credits;
	server->oplock_credits = server->echo_credits = 0;
	चयन (server->credits) अणु
	हाल 0:
		वापस 0;
	हाल 1:
		server->echoes = false;
		server->oplocks = false;
		अवरोध;
	हाल 2:
		server->echoes = true;
		server->oplocks = false;
		server->echo_credits = 1;
		अवरोध;
	शेष:
		server->echoes = true;
		अगर (enable_oplocks) अणु
			server->oplocks = true;
			server->oplock_credits = 1;
		पूर्ण अन्यथा
			server->oplocks = false;

		server->echo_credits = 1;
	पूर्ण
	server->credits -= server->echo_credits + server->oplock_credits;
	वापस server->credits + server->echo_credits + server->oplock_credits;
पूर्ण

अटल व्योम
smb2_add_credits(काष्ठा TCP_Server_Info *server,
		 स्थिर काष्ठा cअगरs_credits *credits, स्थिर पूर्णांक optype)
अणु
	पूर्णांक *val, rc = -1;
	पूर्णांक scredits, in_flight;
	अचिन्हित पूर्णांक add = credits->value;
	अचिन्हित पूर्णांक instance = credits->instance;
	bool reconnect_detected = false;
	bool reconnect_with_invalid_credits = false;

	spin_lock(&server->req_lock);
	val = server->ops->get_credits_field(server, optype);

	/* eg found हाल where ग_लिखो overlapping reconnect messed up credits */
	अगर (((optype & CIFS_OP_MASK) == CIFS_NEG_OP) && (*val != 0))
		reconnect_with_invalid_credits = true;

	अगर ((instance == 0) || (instance == server->reconnect_instance))
		*val += add;
	अन्यथा
		reconnect_detected = true;

	अगर (*val > 65000) अणु
		*val = 65000; /* Don't get near 64K credits, aव्योम srv bugs */
		pr_warn_once("server overflowed SMB3 credits\n");
	पूर्ण
	server->in_flight--;
	अगर (server->in_flight == 0 &&
	   ((optype & CIFS_OP_MASK) != CIFS_NEG_OP) &&
	   ((optype & CIFS_OP_MASK) != CIFS_SESS_OP))
		rc = change_conf(server);
	/*
	 * Someबार server वापसs 0 credits on oplock अवरोध ack - we need to
	 * rebalance credits in this हाल.
	 */
	अन्यथा अगर (server->in_flight > 0 && server->oplock_credits == 0 &&
		 server->oplocks) अणु
		अगर (server->credits > 1) अणु
			server->credits--;
			server->oplock_credits++;
		पूर्ण
	पूर्ण
	scredits = *val;
	in_flight = server->in_flight;
	spin_unlock(&server->req_lock);
	wake_up(&server->request_q);

	अगर (reconnect_detected) अणु
		trace_smb3_reconnect_detected(server->CurrentMid,
			server->conn_id, server->hostname, scredits, add, in_flight);

		cअगरs_dbg(FYI, "trying to put %d credits from the old server instance %d\n",
			 add, instance);
	पूर्ण

	अगर (reconnect_with_invalid_credits) अणु
		trace_smb3_reconnect_with_invalid_credits(server->CurrentMid,
			server->conn_id, server->hostname, scredits, add, in_flight);
		cअगरs_dbg(FYI, "Negotiate operation when server credits is non-zero. Optype: %d, server credits: %d, credits added: %d\n",
			 optype, scredits, add);
	पूर्ण

	अगर (server->tcpStatus == CअगरsNeedReconnect
	    || server->tcpStatus == CअगरsExiting)
		वापस;

	चयन (rc) अणु
	हाल -1:
		/* change_conf hasn't been executed */
		अवरोध;
	हाल 0:
		cअगरs_server_dbg(VFS, "Possible client or server bug - zero credits\n");
		अवरोध;
	हाल 1:
		cअगरs_server_dbg(VFS, "disabling echoes and oplocks\n");
		अवरोध;
	हाल 2:
		cअगरs_dbg(FYI, "disabling oplocks\n");
		अवरोध;
	शेष:
		/* change_conf rebalanced credits क्रम dअगरferent types */
		अवरोध;
	पूर्ण

	trace_smb3_add_credits(server->CurrentMid,
			server->conn_id, server->hostname, scredits, add, in_flight);
	cअगरs_dbg(FYI, "%s: added %u credits total=%d\n", __func__, add, scredits);
पूर्ण

अटल व्योम
smb2_set_credits(काष्ठा TCP_Server_Info *server, स्थिर पूर्णांक val)
अणु
	पूर्णांक scredits, in_flight;

	spin_lock(&server->req_lock);
	server->credits = val;
	अगर (val == 1)
		server->reconnect_instance++;
	scredits = server->credits;
	in_flight = server->in_flight;
	spin_unlock(&server->req_lock);

	trace_smb3_set_credits(server->CurrentMid,
			server->conn_id, server->hostname, scredits, val, in_flight);
	cअगरs_dbg(FYI, "%s: set %u credits\n", __func__, val);

	/* करोn't log जबतक holding the lock */
	अगर (val == 1)
		cअगरs_dbg(FYI, "set credits to 1 due to smb2 reconnect\n");
पूर्ण

अटल पूर्णांक *
smb2_get_credits_field(काष्ठा TCP_Server_Info *server, स्थिर पूर्णांक optype)
अणु
	चयन (optype) अणु
	हाल CIFS_ECHO_OP:
		वापस &server->echo_credits;
	हाल CIFS_OBREAK_OP:
		वापस &server->oplock_credits;
	शेष:
		वापस &server->credits;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक
smb2_get_credits(काष्ठा mid_q_entry *mid)
अणु
	वापस mid->credits_received;
पूर्ण

अटल पूर्णांक
smb2_रुको_mtu_credits(काष्ठा TCP_Server_Info *server, अचिन्हित पूर्णांक size,
		      अचिन्हित पूर्णांक *num, काष्ठा cअगरs_credits *credits)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक scredits, in_flight;

	spin_lock(&server->req_lock);
	जबतक (1) अणु
		अगर (server->credits <= 0) अणु
			spin_unlock(&server->req_lock);
			cअगरs_num_रुकोers_inc(server);
			rc = रुको_event_समाप्तable(server->request_q,
				has_credits(server, &server->credits, 1));
			cअगरs_num_रुकोers_dec(server);
			अगर (rc)
				वापस rc;
			spin_lock(&server->req_lock);
		पूर्ण अन्यथा अणु
			अगर (server->tcpStatus == CअगरsExiting) अणु
				spin_unlock(&server->req_lock);
				वापस -ENOENT;
			पूर्ण

			scredits = server->credits;
			/* can deadlock with reखोलो */
			अगर (scredits <= 8) अणु
				*num = SMB2_MAX_BUFFER_SIZE;
				credits->value = 0;
				credits->instance = 0;
				अवरोध;
			पूर्ण

			/* leave some credits क्रम reखोलो and other ops */
			scredits -= 8;
			*num = min_t(अचिन्हित पूर्णांक, size,
				     scredits * SMB2_MAX_BUFFER_SIZE);

			credits->value =
				DIV_ROUND_UP(*num, SMB2_MAX_BUFFER_SIZE);
			credits->instance = server->reconnect_instance;
			server->credits -= credits->value;
			server->in_flight++;
			अगर (server->in_flight > server->max_in_flight)
				server->max_in_flight = server->in_flight;
			अवरोध;
		पूर्ण
	पूर्ण
	scredits = server->credits;
	in_flight = server->in_flight;
	spin_unlock(&server->req_lock);

	trace_smb3_add_credits(server->CurrentMid,
			server->conn_id, server->hostname, scredits, -(credits->value), in_flight);
	cअगरs_dbg(FYI, "%s: removed %u credits total=%d\n",
			__func__, credits->value, scredits);

	वापस rc;
पूर्ण

अटल पूर्णांक
smb2_adjust_credits(काष्ठा TCP_Server_Info *server,
		    काष्ठा cअगरs_credits *credits,
		    स्थिर अचिन्हित पूर्णांक payload_size)
अणु
	पूर्णांक new_val = DIV_ROUND_UP(payload_size, SMB2_MAX_BUFFER_SIZE);
	पूर्णांक scredits, in_flight;

	अगर (!credits->value || credits->value == new_val)
		वापस 0;

	अगर (credits->value < new_val) अणु
		trace_smb3_too_many_credits(server->CurrentMid,
				server->conn_id, server->hostname, 0, credits->value - new_val, 0);
		cअगरs_server_dbg(VFS, "request has less credits (%d) than required (%d)",
				credits->value, new_val);

		वापस -ENOTSUPP;
	पूर्ण

	spin_lock(&server->req_lock);

	अगर (server->reconnect_instance != credits->instance) अणु
		scredits = server->credits;
		in_flight = server->in_flight;
		spin_unlock(&server->req_lock);

		trace_smb3_reconnect_detected(server->CurrentMid,
			server->conn_id, server->hostname, scredits,
			credits->value - new_val, in_flight);
		cअगरs_server_dbg(VFS, "trying to return %d credits to old session\n",
			 credits->value - new_val);
		वापस -EAGAIN;
	पूर्ण

	server->credits += credits->value - new_val;
	scredits = server->credits;
	in_flight = server->in_flight;
	spin_unlock(&server->req_lock);
	wake_up(&server->request_q);

	trace_smb3_add_credits(server->CurrentMid,
			server->conn_id, server->hostname, scredits,
			credits->value - new_val, in_flight);
	cअगरs_dbg(FYI, "%s: adjust added %u credits total=%d\n",
			__func__, credits->value - new_val, scredits);

	credits->value = new_val;

	वापस 0;
पूर्ण

अटल __u64
smb2_get_next_mid(काष्ठा TCP_Server_Info *server)
अणु
	__u64 mid;
	/* क्रम SMB2 we need the current value */
	spin_lock(&GlobalMid_Lock);
	mid = server->CurrentMid++;
	spin_unlock(&GlobalMid_Lock);
	वापस mid;
पूर्ण

अटल व्योम
smb2_revert_current_mid(काष्ठा TCP_Server_Info *server, स्थिर अचिन्हित पूर्णांक val)
अणु
	spin_lock(&GlobalMid_Lock);
	अगर (server->CurrentMid >= val)
		server->CurrentMid -= val;
	spin_unlock(&GlobalMid_Lock);
पूर्ण

अटल काष्ठा mid_q_entry *
__smb2_find_mid(काष्ठा TCP_Server_Info *server, अक्षर *buf, bool dequeue)
अणु
	काष्ठा mid_q_entry *mid;
	काष्ठा smb2_sync_hdr *shdr = (काष्ठा smb2_sync_hdr *)buf;
	__u64 wire_mid = le64_to_cpu(shdr->MessageId);

	अगर (shdr->ProtocolId == SMB2_TRANSFORM_PROTO_NUM) अणु
		cअगरs_server_dbg(VFS, "Encrypted frame parsing not supported yet\n");
		वापस शून्य;
	पूर्ण

	spin_lock(&GlobalMid_Lock);
	list_क्रम_each_entry(mid, &server->pending_mid_q, qhead) अणु
		अगर ((mid->mid == wire_mid) &&
		    (mid->mid_state == MID_REQUEST_SUBMITTED) &&
		    (mid->command == shdr->Command)) अणु
			kref_get(&mid->refcount);
			अगर (dequeue) अणु
				list_del_init(&mid->qhead);
				mid->mid_flags |= MID_DELETED;
			पूर्ण
			spin_unlock(&GlobalMid_Lock);
			वापस mid;
		पूर्ण
	पूर्ण
	spin_unlock(&GlobalMid_Lock);
	वापस शून्य;
पूर्ण

अटल काष्ठा mid_q_entry *
smb2_find_mid(काष्ठा TCP_Server_Info *server, अक्षर *buf)
अणु
	वापस __smb2_find_mid(server, buf, false);
पूर्ण

अटल काष्ठा mid_q_entry *
smb2_find_dequeue_mid(काष्ठा TCP_Server_Info *server, अक्षर *buf)
अणु
	वापस __smb2_find_mid(server, buf, true);
पूर्ण

अटल व्योम
smb2_dump_detail(व्योम *buf, काष्ठा TCP_Server_Info *server)
अणु
#अगर_घोषित CONFIG_CIFS_DEBUG2
	काष्ठा smb2_sync_hdr *shdr = (काष्ठा smb2_sync_hdr *)buf;

	cअगरs_server_dbg(VFS, "Cmd: %d Err: 0x%x Flags: 0x%x Mid: %llu Pid: %d\n",
		 shdr->Command, shdr->Status, shdr->Flags, shdr->MessageId,
		 shdr->ProcessId);
	cअगरs_server_dbg(VFS, "smb buf %p len %u\n", buf,
		 server->ops->calc_smb_size(buf, server));
#पूर्ण_अगर
पूर्ण

अटल bool
smb2_need_neg(काष्ठा TCP_Server_Info *server)
अणु
	वापस server->max_पढ़ो == 0;
पूर्ण

अटल पूर्णांक
smb2_negotiate(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses)
अणु
	पूर्णांक rc;

	cअगरs_ses_server(ses)->CurrentMid = 0;
	rc = SMB2_negotiate(xid, ses);
	/* BB we probably करोn't need to retry with modern servers */
	अगर (rc == -EAGAIN)
		rc = -EHOSTDOWN;
	वापस rc;
पूर्ण

अटल अचिन्हित पूर्णांक
smb2_negotiate_wsize(काष्ठा cअगरs_tcon *tcon, काष्ठा smb3_fs_context *ctx)
अणु
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	अचिन्हित पूर्णांक wsize;

	/* start with specअगरied wsize, or शेष */
	wsize = ctx->wsize ? ctx->wsize : CIFS_DEFAULT_IOSIZE;
	wsize = min_t(अचिन्हित पूर्णांक, wsize, server->max_ग_लिखो);
	अगर (!(server->capabilities & SMB2_GLOBAL_CAP_LARGE_MTU))
		wsize = min_t(अचिन्हित पूर्णांक, wsize, SMB2_MAX_BUFFER_SIZE);

	वापस wsize;
पूर्ण

अटल अचिन्हित पूर्णांक
smb3_negotiate_wsize(काष्ठा cअगरs_tcon *tcon, काष्ठा smb3_fs_context *ctx)
अणु
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	अचिन्हित पूर्णांक wsize;

	/* start with specअगरied wsize, or शेष */
	wsize = ctx->wsize ? ctx->wsize : SMB3_DEFAULT_IOSIZE;
	wsize = min_t(अचिन्हित पूर्णांक, wsize, server->max_ग_लिखो);
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	अगर (server->rdma) अणु
		अगर (server->sign)
			/*
			 * Account क्रम SMB2 data transfer packet header and
			 * possible encryption header
			 */
			wsize = min_t(अचिन्हित पूर्णांक,
				wsize,
				server->smbd_conn->max_fragmented_send_size -
					SMB2_READWRITE_PDU_HEADER_SIZE -
					माप(काष्ठा smb2_transक्रमm_hdr));
		अन्यथा
			wsize = min_t(अचिन्हित पूर्णांक,
				wsize, server->smbd_conn->max_पढ़ोग_लिखो_size);
	पूर्ण
#पूर्ण_अगर
	अगर (!(server->capabilities & SMB2_GLOBAL_CAP_LARGE_MTU))
		wsize = min_t(अचिन्हित पूर्णांक, wsize, SMB2_MAX_BUFFER_SIZE);

	वापस wsize;
पूर्ण

अटल अचिन्हित पूर्णांक
smb2_negotiate_rsize(काष्ठा cअगरs_tcon *tcon, काष्ठा smb3_fs_context *ctx)
अणु
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	अचिन्हित पूर्णांक rsize;

	/* start with specअगरied rsize, or शेष */
	rsize = ctx->rsize ? ctx->rsize : CIFS_DEFAULT_IOSIZE;
	rsize = min_t(अचिन्हित पूर्णांक, rsize, server->max_पढ़ो);

	अगर (!(server->capabilities & SMB2_GLOBAL_CAP_LARGE_MTU))
		rsize = min_t(अचिन्हित पूर्णांक, rsize, SMB2_MAX_BUFFER_SIZE);

	वापस rsize;
पूर्ण

अटल अचिन्हित पूर्णांक
smb3_negotiate_rsize(काष्ठा cअगरs_tcon *tcon, काष्ठा smb3_fs_context *ctx)
अणु
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	अचिन्हित पूर्णांक rsize;

	/* start with specअगरied rsize, or शेष */
	rsize = ctx->rsize ? ctx->rsize : SMB3_DEFAULT_IOSIZE;
	rsize = min_t(अचिन्हित पूर्णांक, rsize, server->max_पढ़ो);
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	अगर (server->rdma) अणु
		अगर (server->sign)
			/*
			 * Account क्रम SMB2 data transfer packet header and
			 * possible encryption header
			 */
			rsize = min_t(अचिन्हित पूर्णांक,
				rsize,
				server->smbd_conn->max_fragmented_recv_size -
					SMB2_READWRITE_PDU_HEADER_SIZE -
					माप(काष्ठा smb2_transक्रमm_hdr));
		अन्यथा
			rsize = min_t(अचिन्हित पूर्णांक,
				rsize, server->smbd_conn->max_पढ़ोग_लिखो_size);
	पूर्ण
#पूर्ण_अगर

	अगर (!(server->capabilities & SMB2_GLOBAL_CAP_LARGE_MTU))
		rsize = min_t(अचिन्हित पूर्णांक, rsize, SMB2_MAX_BUFFER_SIZE);

	वापस rsize;
पूर्ण

अटल पूर्णांक
parse_server_पूर्णांकerfaces(काष्ठा network_पूर्णांकerface_info_ioctl_rsp *buf,
			माप_प्रकार buf_len,
			काष्ठा cअगरs_server_अगरace **अगरace_list,
			माप_प्रकार *अगरace_count)
अणु
	काष्ठा network_पूर्णांकerface_info_ioctl_rsp *p;
	काष्ठा sockaddr_in *addr4;
	काष्ठा sockaddr_in6 *addr6;
	काष्ठा अगरace_info_ipv4 *p4;
	काष्ठा अगरace_info_ipv6 *p6;
	काष्ठा cअगरs_server_अगरace *info;
	sमाप_प्रकार bytes_left;
	माप_प्रकार next = 0;
	पूर्णांक nb_अगरace = 0;
	पूर्णांक rc = 0;

	*अगरace_list = शून्य;
	*अगरace_count = 0;

	/*
	 * Fist pass: count and sanity check
	 */

	bytes_left = buf_len;
	p = buf;
	जबतक (bytes_left >= माप(*p)) अणु
		nb_अगरace++;
		next = le32_to_cpu(p->Next);
		अगर (!next) अणु
			bytes_left -= माप(*p);
			अवरोध;
		पूर्ण
		p = (काष्ठा network_पूर्णांकerface_info_ioctl_rsp *)((u8 *)p+next);
		bytes_left -= next;
	पूर्ण

	अगर (!nb_अगरace) अणु
		cअगरs_dbg(VFS, "%s: malformed interface info\n", __func__);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* Azure rounds the buffer size up 8, to a 16 byte boundary */
	अगर ((bytes_left > 8) || p->Next)
		cअगरs_dbg(VFS, "%s: incomplete interface info\n", __func__);


	/*
	 * Second pass: extract info to पूर्णांकernal काष्ठाure
	 */

	*अगरace_list = kसुस्मृति(nb_अगरace, माप(**अगरace_list), GFP_KERNEL);
	अगर (!*अगरace_list) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	info = *अगरace_list;
	bytes_left = buf_len;
	p = buf;
	जबतक (bytes_left >= माप(*p)) अणु
		info->speed = le64_to_cpu(p->LinkSpeed);
		info->rdma_capable = le32_to_cpu(p->Capability & RDMA_CAPABLE);
		info->rss_capable = le32_to_cpu(p->Capability & RSS_CAPABLE);

		cअगरs_dbg(FYI, "%s: adding iface %zu\n", __func__, *अगरace_count);
		cअगरs_dbg(FYI, "%s: speed %zu bps\n", __func__, info->speed);
		cअगरs_dbg(FYI, "%s: capabilities 0x%08x\n", __func__,
			 le32_to_cpu(p->Capability));

		चयन (p->Family) अणु
		/*
		 * The kernel and wire socket काष्ठाures have the same
		 * layout and use network byte order but make the
		 * conversion explicit in हाल either one changes.
		 */
		हाल INTERNETWORK:
			addr4 = (काष्ठा sockaddr_in *)&info->sockaddr;
			p4 = (काष्ठा अगरace_info_ipv4 *)p->Buffer;
			addr4->sin_family = AF_INET;
			स_नकल(&addr4->sin_addr, &p4->IPv4Address, 4);

			/* [MS-SMB2] 2.2.32.5.1.1 Clients MUST ignore these */
			addr4->sin_port = cpu_to_be16(CIFS_PORT);

			cअगरs_dbg(FYI, "%s: ipv4 %pI4\n", __func__,
				 &addr4->sin_addr);
			अवरोध;
		हाल INTERNETWORKV6:
			addr6 =	(काष्ठा sockaddr_in6 *)&info->sockaddr;
			p6 = (काष्ठा अगरace_info_ipv6 *)p->Buffer;
			addr6->sin6_family = AF_INET6;
			स_नकल(&addr6->sin6_addr, &p6->IPv6Address, 16);

			/* [MS-SMB2] 2.2.32.5.1.2 Clients MUST ignore these */
			addr6->sin6_flowinfo = 0;
			addr6->sin6_scope_id = 0;
			addr6->sin6_port = cpu_to_be16(CIFS_PORT);

			cअगरs_dbg(FYI, "%s: ipv6 %pI6\n", __func__,
				 &addr6->sin6_addr);
			अवरोध;
		शेष:
			cअगरs_dbg(VFS,
				 "%s: skipping unsupported socket family\n",
				 __func__);
			जाओ next_अगरace;
		पूर्ण

		(*अगरace_count)++;
		info++;
next_अगरace:
		next = le32_to_cpu(p->Next);
		अगर (!next)
			अवरोध;
		p = (काष्ठा network_पूर्णांकerface_info_ioctl_rsp *)((u8 *)p+next);
		bytes_left -= next;
	पूर्ण

	अगर (!*अगरace_count) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

out:
	अगर (rc) अणु
		kमुक्त(*अगरace_list);
		*अगरace_count = 0;
		*अगरace_list = शून्य;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक compare_अगरace(स्थिर व्योम *ia, स्थिर व्योम *ib)
अणु
	स्थिर काष्ठा cअगरs_server_अगरace *a = (काष्ठा cअगरs_server_अगरace *)ia;
	स्थिर काष्ठा cअगरs_server_अगरace *b = (काष्ठा cअगरs_server_अगरace *)ib;

	वापस a->speed == b->speed ? 0 : (a->speed > b->speed ? -1 : 1);
पूर्ण

अटल पूर्णांक
SMB3_request_पूर्णांकerfaces(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक ret_data_len = 0;
	काष्ठा network_पूर्णांकerface_info_ioctl_rsp *out_buf = शून्य;
	काष्ठा cअगरs_server_अगरace *अगरace_list;
	माप_प्रकार अगरace_count;
	काष्ठा cअगरs_ses *ses = tcon->ses;

	rc = SMB2_ioctl(xid, tcon, NO_खाता_ID, NO_खाता_ID,
			FSCTL_QUERY_NETWORK_INTERFACE_INFO, true /* is_fsctl */,
			शून्य /* no data input */, 0 /* no data input */,
			CIFSMaxBufSize, (अक्षर **)&out_buf, &ret_data_len);
	अगर (rc == -EOPNOTSUPP) अणु
		cअगरs_dbg(FYI,
			 "server does not support query network interfaces\n");
		जाओ out;
	पूर्ण अन्यथा अगर (rc != 0) अणु
		cअगरs_tcon_dbg(VFS, "error %d on ioctl to get interface list\n", rc);
		जाओ out;
	पूर्ण

	rc = parse_server_पूर्णांकerfaces(out_buf, ret_data_len,
				     &अगरace_list, &अगरace_count);
	अगर (rc)
		जाओ out;

	/* sort पूर्णांकerfaces from fastest to slowest */
	sort(अगरace_list, अगरace_count, माप(*अगरace_list), compare_अगरace, शून्य);

	spin_lock(&ses->अगरace_lock);
	kमुक्त(ses->अगरace_list);
	ses->अगरace_list = अगरace_list;
	ses->अगरace_count = अगरace_count;
	ses->अगरace_last_update = jअगरfies;
	spin_unlock(&ses->अगरace_lock);

out:
	kमुक्त(out_buf);
	वापस rc;
पूर्ण

अटल व्योम
smb2_बंद_cached_fid(काष्ठा kref *ref)
अणु
	काष्ठा cached_fid *cfid = container_of(ref, काष्ठा cached_fid,
					       refcount);

	अगर (cfid->is_valid) अणु
		cअगरs_dbg(FYI, "clear cached root file handle\n");
		SMB2_बंद(0, cfid->tcon, cfid->fid->persistent_fid,
			   cfid->fid->अस्थिर_fid);
		cfid->is_valid = false;
		cfid->file_all_info_is_valid = false;
		cfid->has_lease = false;
		अगर (cfid->dentry) अणु
			dput(cfid->dentry);
			cfid->dentry = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

व्योम बंद_cached_dir(काष्ठा cached_fid *cfid)
अणु
	mutex_lock(&cfid->fid_mutex);
	kref_put(&cfid->refcount, smb2_बंद_cached_fid);
	mutex_unlock(&cfid->fid_mutex);
पूर्ण

व्योम बंद_cached_dir_lease_locked(काष्ठा cached_fid *cfid)
अणु
	अगर (cfid->has_lease) अणु
		cfid->has_lease = false;
		kref_put(&cfid->refcount, smb2_बंद_cached_fid);
	पूर्ण
पूर्ण

व्योम बंद_cached_dir_lease(काष्ठा cached_fid *cfid)
अणु
	mutex_lock(&cfid->fid_mutex);
	बंद_cached_dir_lease_locked(cfid);
	mutex_unlock(&cfid->fid_mutex);
पूर्ण

व्योम
smb2_cached_lease_अवरोध(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cached_fid *cfid = container_of(work,
				काष्ठा cached_fid, lease_अवरोध);

	बंद_cached_dir_lease(cfid);
पूर्ण

/*
 * Open the and cache a directory handle.
 * Only supported क्रम the root handle.
 */
पूर्णांक खोलो_cached_dir(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		स्थिर अक्षर *path,
		काष्ठा cअगरs_sb_info *cअगरs_sb,
		काष्ठा cached_fid **cfid)
अणु
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = ses->server;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा smb2_create_rsp *o_rsp = शून्य;
	काष्ठा smb2_query_info_rsp *qi_rsp = शून्य;
	पूर्णांक resp_buftype[2];
	काष्ठा smb_rqst rqst[2];
	काष्ठा kvec rsp_iov[2];
	काष्ठा kvec खोलो_iov[SMB2_CREATE_IOV_SIZE];
	काष्ठा kvec qi_iov[1];
	पूर्णांक rc, flags = 0;
	__le16 utf16_path = 0; /* Null - since an खोलो of top of share */
	u8 oplock = SMB2_OPLOCK_LEVEL_II;
	काष्ठा cअगरs_fid *pfid;
	काष्ठा dentry *dentry;

	अगर (tcon->nohandlecache)
		वापस -ENOTSUPP;

	अगर (cअगरs_sb->root == शून्य)
		वापस -ENOENT;

	अगर (म_माप(path))
		वापस -ENOENT;

	dentry = cअगरs_sb->root;

	mutex_lock(&tcon->crfid.fid_mutex);
	अगर (tcon->crfid.is_valid) अणु
		cअगरs_dbg(FYI, "found a cached root file handle\n");
		*cfid = &tcon->crfid;
		kref_get(&tcon->crfid.refcount);
		mutex_unlock(&tcon->crfid.fid_mutex);
		वापस 0;
	पूर्ण

	/*
	 * We करो not hold the lock क्रम the खोलो because in हाल
	 * SMB2_खोलो needs to reconnect, it will end up calling
	 * cअगरs_mark_खोलो_files_invalid() which takes the lock again
	 * thus causing a deadlock
	 */

	mutex_unlock(&tcon->crfid.fid_mutex);

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	अगर (!server->ops->new_lease_key)
		वापस -EIO;

	pfid = tcon->crfid.fid;
	server->ops->new_lease_key(pfid);

	स_रखो(rqst, 0, माप(rqst));
	resp_buftype[0] = resp_buftype[1] = CIFS_NO_BUFFER;
	स_रखो(rsp_iov, 0, माप(rsp_iov));

	/* Open */
	स_रखो(&खोलो_iov, 0, माप(खोलो_iov));
	rqst[0].rq_iov = खोलो_iov;
	rqst[0].rq_nvec = SMB2_CREATE_IOV_SIZE;

	oparms.tcon = tcon;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.desired_access = खाता_READ_ATTRIBUTES;
	oparms.disposition = खाता_OPEN;
	oparms.fid = pfid;
	oparms.reconnect = false;

	rc = SMB2_खोलो_init(tcon, server,
			    &rqst[0], &oplock, &oparms, &utf16_path);
	अगर (rc)
		जाओ oshr_मुक्त;
	smb2_set_next_command(tcon, &rqst[0]);

	स_रखो(&qi_iov, 0, माप(qi_iov));
	rqst[1].rq_iov = qi_iov;
	rqst[1].rq_nvec = 1;

	rc = SMB2_query_info_init(tcon, server,
				  &rqst[1], COMPOUND_FID,
				  COMPOUND_FID, खाता_ALL_INFORMATION,
				  SMB2_O_INFO_खाता, 0,
				  माप(काष्ठा smb2_file_all_info) +
				  PATH_MAX * 2, 0, शून्य);
	अगर (rc)
		जाओ oshr_मुक्त;

	smb2_set_related(&rqst[1]);

	rc = compound_send_recv(xid, ses, server,
				flags, 2, rqst,
				resp_buftype, rsp_iov);
	mutex_lock(&tcon->crfid.fid_mutex);

	/*
	 * Now we need to check again as the cached root might have
	 * been successfully re-खोलोed from a concurrent process
	 */

	अगर (tcon->crfid.is_valid) अणु
		/* work was alपढ़ोy करोne */

		/* stash fids क्रम बंद() later */
		काष्ठा cअगरs_fid fid = अणु
			.persistent_fid = pfid->persistent_fid,
			.अस्थिर_fid = pfid->अस्थिर_fid,
		पूर्ण;

		/*
		 * caller expects this func to set the fid in crfid to valid
		 * cached root, so increment the refcount.
		 */
		kref_get(&tcon->crfid.refcount);

		mutex_unlock(&tcon->crfid.fid_mutex);

		अगर (rc == 0) अणु
			/* बंद extra handle outside of crit sec */
			SMB2_बंद(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid);
		पूर्ण
		rc = 0;
		जाओ oshr_मुक्त;
	पूर्ण

	/* Cached root is still invalid, जारी normaly */

	अगर (rc) अणु
		अगर (rc == -EREMCHG) अणु
			tcon->need_reconnect = true;
			pr_warn_once("server share %s deleted\n",
				     tcon->treeName);
		पूर्ण
		जाओ oshr_निकास;
	पूर्ण

	atomic_inc(&tcon->num_remote_खोलोs);

	o_rsp = (काष्ठा smb2_create_rsp *)rsp_iov[0].iov_base;
	oparms.fid->persistent_fid = o_rsp->PersistentFileId;
	oparms.fid->अस्थिर_fid = o_rsp->VolatileFileId;
#अगर_घोषित CONFIG_CIFS_DEBUG2
	oparms.fid->mid = le64_to_cpu(o_rsp->sync_hdr.MessageId);
#पूर्ण_अगर /* CIFS_DEBUG2 */

	tcon->crfid.tcon = tcon;
	tcon->crfid.is_valid = true;
	tcon->crfid.dentry = dentry;
	dget(dentry);
	kref_init(&tcon->crfid.refcount);

	/* BB TBD check to see अगर oplock level check can be हटाओd below */
	अगर (o_rsp->OplockLevel == SMB2_OPLOCK_LEVEL_LEASE) अणु
		/*
		 * See commit 2f94a3125b87. Increment the refcount when we
		 * get a lease क्रम root, release it अगर lease अवरोध occurs
		 */
		kref_get(&tcon->crfid.refcount);
		tcon->crfid.has_lease = true;
		smb2_parse_contexts(server, o_rsp,
				&oparms.fid->epoch,
				    oparms.fid->lease_key, &oplock,
				    शून्य, शून्य);
	पूर्ण अन्यथा
		जाओ oshr_निकास;

	qi_rsp = (काष्ठा smb2_query_info_rsp *)rsp_iov[1].iov_base;
	अगर (le32_to_cpu(qi_rsp->OutputBufferLength) < माप(काष्ठा smb2_file_all_info))
		जाओ oshr_निकास;
	अगर (!smb2_validate_and_copy_iov(
				le16_to_cpu(qi_rsp->OutputBufferOffset),
				माप(काष्ठा smb2_file_all_info),
				&rsp_iov[1], माप(काष्ठा smb2_file_all_info),
				(अक्षर *)&tcon->crfid.file_all_info))
		tcon->crfid.file_all_info_is_valid = true;
	tcon->crfid.समय = jअगरfies;


oshr_निकास:
	mutex_unlock(&tcon->crfid.fid_mutex);
oshr_मुक्त:
	SMB2_खोलो_मुक्त(&rqst[0]);
	SMB2_query_info_मुक्त(&rqst[1]);
	मुक्त_rsp_buf(resp_buftype[0], rsp_iov[0].iov_base);
	मुक्त_rsp_buf(resp_buftype[1], rsp_iov[1].iov_base);
	अगर (rc == 0)
		*cfid = &tcon->crfid;
	वापस rc;
पूर्ण

पूर्णांक खोलो_cached_dir_by_dentry(काष्ठा cअगरs_tcon *tcon,
			      काष्ठा dentry *dentry,
			      काष्ठा cached_fid **cfid)
अणु
	mutex_lock(&tcon->crfid.fid_mutex);
	अगर (tcon->crfid.dentry == dentry) अणु
		cअगरs_dbg(FYI, "found a cached root file handle by dentry\n");
		*cfid = &tcon->crfid;
		kref_get(&tcon->crfid.refcount);
		mutex_unlock(&tcon->crfid.fid_mutex);
		वापस 0;
	पूर्ण
	mutex_unlock(&tcon->crfid.fid_mutex);
	वापस -ENOENT;
पूर्ण

अटल व्योम
smb3_qfs_tcon(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	      काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	पूर्णांक rc;
	__le16 srch_path = 0; /* Null - खोलो root of share */
	u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_fid fid;
	काष्ठा cached_fid *cfid = शून्य;

	oparms.tcon = tcon;
	oparms.desired_access = खाता_READ_ATTRIBUTES;
	oparms.disposition = खाता_OPEN;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = खोलो_cached_dir(xid, tcon, "", cअगरs_sb, &cfid);
	अगर (rc == 0)
		स_नकल(&fid, cfid->fid, माप(काष्ठा cअगरs_fid));
	अन्यथा
		rc = SMB2_खोलो(xid, &oparms, &srch_path, &oplock, शून्य, शून्य,
			       शून्य, शून्य);
	अगर (rc)
		वापस;

	SMB3_request_पूर्णांकerfaces(xid, tcon);

	SMB2_QFS_attr(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid,
			FS_ATTRIBUTE_INFORMATION);
	SMB2_QFS_attr(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid,
			FS_DEVICE_INFORMATION);
	SMB2_QFS_attr(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid,
			FS_VOLUME_INFORMATION);
	SMB2_QFS_attr(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid,
			FS_SECTOR_SIZE_INFORMATION); /* SMB3 specअगरic */
	अगर (cfid == शून्य)
		SMB2_बंद(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid);
	अन्यथा
		बंद_cached_dir(cfid);
पूर्ण

अटल व्योम
smb2_qfs_tcon(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	      काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	पूर्णांक rc;
	__le16 srch_path = 0; /* Null - खोलो root of share */
	u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_fid fid;

	oparms.tcon = tcon;
	oparms.desired_access = खाता_READ_ATTRIBUTES;
	oparms.disposition = खाता_OPEN;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = SMB2_खोलो(xid, &oparms, &srch_path, &oplock, शून्य, शून्य,
		       शून्य, शून्य);
	अगर (rc)
		वापस;

	SMB2_QFS_attr(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid,
			FS_ATTRIBUTE_INFORMATION);
	SMB2_QFS_attr(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid,
			FS_DEVICE_INFORMATION);
	SMB2_बंद(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid);
पूर्ण

अटल पूर्णांक
smb2_is_path_accessible(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *full_path)
अणु
	पूर्णांक rc;
	__le16 *utf16_path;
	__u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_fid fid;

	अगर ((*full_path == 0) && tcon->crfid.is_valid)
		वापस 0;

	utf16_path = cअगरs_convert_path_to_utf16(full_path, cअगरs_sb);
	अगर (!utf16_path)
		वापस -ENOMEM;

	oparms.tcon = tcon;
	oparms.desired_access = खाता_READ_ATTRIBUTES;
	oparms.disposition = खाता_OPEN;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = SMB2_खोलो(xid, &oparms, utf16_path, &oplock, शून्य, शून्य, शून्य,
		       शून्य);
	अगर (rc) अणु
		kमुक्त(utf16_path);
		वापस rc;
	पूर्ण

	rc = SMB2_बंद(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid);
	kमुक्त(utf16_path);
	वापस rc;
पूर्ण

अटल पूर्णांक
smb2_get_srv_inum(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		  काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *full_path,
		  u64 *uniqueid, खाता_ALL_INFO *data)
अणु
	*uniqueid = le64_to_cpu(data->IndexNumber);
	वापस 0;
पूर्ण

अटल पूर्णांक
smb2_query_file_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     काष्ठा cअगरs_fid *fid, खाता_ALL_INFO *data)
अणु
	पूर्णांक rc;
	काष्ठा smb2_file_all_info *smb2_data;

	smb2_data = kzalloc(माप(काष्ठा smb2_file_all_info) + PATH_MAX * 2,
			    GFP_KERNEL);
	अगर (smb2_data == शून्य)
		वापस -ENOMEM;

	rc = SMB2_query_info(xid, tcon, fid->persistent_fid, fid->अस्थिर_fid,
			     smb2_data);
	अगर (!rc)
		move_smb2_info_to_cअगरs(data, smb2_data);
	kमुक्त(smb2_data);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_CIFS_XATTR
अटल sमाप_प्रकार
move_smb2_ea_to_cअगरs(अक्षर *dst, माप_प्रकार dst_size,
		     काष्ठा smb2_file_full_ea_info *src, माप_प्रकार src_size,
		     स्थिर अचिन्हित अक्षर *ea_name)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक ea_name_len = ea_name ? म_माप(ea_name) : 0;
	अक्षर *name, *value;
	माप_प्रकार buf_size = dst_size;
	माप_प्रकार name_len, value_len, user_name_len;

	जबतक (src_size > 0) अणु
		name = &src->ea_data[0];
		name_len = (माप_प्रकार)src->ea_name_length;
		value = &src->ea_data[src->ea_name_length + 1];
		value_len = (माप_प्रकार)le16_to_cpu(src->ea_value_length);

		अगर (name_len == 0)
			अवरोध;

		अगर (src_size < 8 + name_len + 1 + value_len) अणु
			cअगरs_dbg(FYI, "EA entry goes beyond length of list\n");
			rc = -EIO;
			जाओ out;
		पूर्ण

		अगर (ea_name) अणु
			अगर (ea_name_len == name_len &&
			    स_भेद(ea_name, name, name_len) == 0) अणु
				rc = value_len;
				अगर (dst_size == 0)
					जाओ out;
				अगर (dst_size < value_len) अणु
					rc = -दुस्फल;
					जाओ out;
				पूर्ण
				स_नकल(dst, value, value_len);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* 'user.' plus a terminating null */
			user_name_len = 5 + 1 + name_len;

			अगर (buf_size == 0) अणु
				/* skip copy - calc size only */
				rc += user_name_len;
			पूर्ण अन्यथा अगर (dst_size >= user_name_len) अणु
				dst_size -= user_name_len;
				स_नकल(dst, "user.", 5);
				dst += 5;
				स_नकल(dst, src->ea_data, name_len);
				dst += name_len;
				*dst = 0;
				++dst;
				rc += user_name_len;
			पूर्ण अन्यथा अणु
				/* stop beक्रमe overrun buffer */
				rc = -दुस्फल;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!src->next_entry_offset)
			अवरोध;

		अगर (src_size < le32_to_cpu(src->next_entry_offset)) अणु
			/* stop beक्रमe overrun buffer */
			rc = -दुस्फल;
			अवरोध;
		पूर्ण
		src_size -= le32_to_cpu(src->next_entry_offset);
		src = (व्योम *)((अक्षर *)src +
			       le32_to_cpu(src->next_entry_offset));
	पूर्ण

	/* didn't find the named attribute */
	अगर (ea_name)
		rc = -ENODATA;

out:
	वापस (sमाप_प्रकार)rc;
पूर्ण

अटल sमाप_प्रकार
smb2_query_eas(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	       स्थिर अचिन्हित अक्षर *path, स्थिर अचिन्हित अक्षर *ea_name,
	       अक्षर *ea_data, माप_प्रकार buf_size,
	       काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	पूर्णांक rc;
	__le16 *utf16_path;
	काष्ठा kvec rsp_iov = अणुशून्य, 0पूर्ण;
	पूर्णांक buftype = CIFS_NO_BUFFER;
	काष्ठा smb2_query_info_rsp *rsp;
	काष्ठा smb2_file_full_ea_info *info = शून्य;

	utf16_path = cअगरs_convert_path_to_utf16(path, cअगरs_sb);
	अगर (!utf16_path)
		वापस -ENOMEM;

	rc = smb2_query_info_compound(xid, tcon, utf16_path,
				      खाता_READ_EA,
				      खाता_FULL_EA_INFORMATION,
				      SMB2_O_INFO_खाता,
				      CIFSMaxBufSize -
				      MAX_SMB2_CREATE_RESPONSE_SIZE -
				      MAX_SMB2_CLOSE_RESPONSE_SIZE,
				      &rsp_iov, &buftype, cअगरs_sb);
	अगर (rc) अणु
		/*
		 * If ea_name is शून्य (listxattr) and there are no EAs,
		 * वापस 0 as it's not an error. Otherwise, the specअगरied
		 * ea_name was not found.
		 */
		अगर (!ea_name && rc == -ENODATA)
			rc = 0;
		जाओ qeas_निकास;
	पूर्ण

	rsp = (काष्ठा smb2_query_info_rsp *)rsp_iov.iov_base;
	rc = smb2_validate_iov(le16_to_cpu(rsp->OutputBufferOffset),
			       le32_to_cpu(rsp->OutputBufferLength),
			       &rsp_iov,
			       माप(काष्ठा smb2_file_full_ea_info));
	अगर (rc)
		जाओ qeas_निकास;

	info = (काष्ठा smb2_file_full_ea_info *)(
			le16_to_cpu(rsp->OutputBufferOffset) + (अक्षर *)rsp);
	rc = move_smb2_ea_to_cअगरs(ea_data, buf_size, info,
			le32_to_cpu(rsp->OutputBufferLength), ea_name);

 qeas_निकास:
	kमुक्त(utf16_path);
	मुक्त_rsp_buf(buftype, rsp_iov.iov_base);
	वापस rc;
पूर्ण


अटल पूर्णांक
smb2_set_ea(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	    स्थिर अक्षर *path, स्थिर अक्षर *ea_name, स्थिर व्योम *ea_value,
	    स्थिर __u16 ea_value_len, स्थिर काष्ठा nls_table *nls_codepage,
	    काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	__le16 *utf16_path = शून्य;
	पूर्णांक ea_name_len = म_माप(ea_name);
	पूर्णांक flags = CIFS_CP_CREATE_CLOSE_OP;
	पूर्णांक len;
	काष्ठा smb_rqst rqst[3];
	पूर्णांक resp_buftype[3];
	काष्ठा kvec rsp_iov[3];
	काष्ठा kvec खोलो_iov[SMB2_CREATE_IOV_SIZE];
	काष्ठा cअगरs_खोलो_parms oparms;
	__u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा cअगरs_fid fid;
	काष्ठा kvec si_iov[SMB2_SET_INFO_IOV_SIZE];
	अचिन्हित पूर्णांक size[1];
	व्योम *data[1];
	काष्ठा smb2_file_full_ea_info *ea = शून्य;
	काष्ठा kvec बंद_iov[1];
	काष्ठा smb2_query_info_rsp *rsp;
	पूर्णांक rc, used_len = 0;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	अगर (ea_name_len > 255)
		वापस -EINVAL;

	utf16_path = cअगरs_convert_path_to_utf16(path, cअगरs_sb);
	अगर (!utf16_path)
		वापस -ENOMEM;

	स_रखो(rqst, 0, माप(rqst));
	resp_buftype[0] = resp_buftype[1] = resp_buftype[2] = CIFS_NO_BUFFER;
	स_रखो(rsp_iov, 0, माप(rsp_iov));

	अगर (ses->server->ops->query_all_EAs) अणु
		अगर (!ea_value) अणु
			rc = ses->server->ops->query_all_EAs(xid, tcon, path,
							     ea_name, शून्य, 0,
							     cअगरs_sb);
			अगर (rc == -ENODATA)
				जाओ sea_निकास;
		पूर्ण अन्यथा अणु
			/* If we are adding a attribute we should first check
			 * अगर there will be enough space available to store
			 * the new EA. If not we should not add it since we
			 * would not be able to even पढ़ो the EAs back.
			 */
			rc = smb2_query_info_compound(xid, tcon, utf16_path,
				      खाता_READ_EA,
				      खाता_FULL_EA_INFORMATION,
				      SMB2_O_INFO_खाता,
				      CIFSMaxBufSize -
				      MAX_SMB2_CREATE_RESPONSE_SIZE -
				      MAX_SMB2_CLOSE_RESPONSE_SIZE,
				      &rsp_iov[1], &resp_buftype[1], cअगरs_sb);
			अगर (rc == 0) अणु
				rsp = (काष्ठा smb2_query_info_rsp *)rsp_iov[1].iov_base;
				used_len = le32_to_cpu(rsp->OutputBufferLength);
			पूर्ण
			मुक्त_rsp_buf(resp_buftype[1], rsp_iov[1].iov_base);
			resp_buftype[1] = CIFS_NO_BUFFER;
			स_रखो(&rsp_iov[1], 0, माप(rsp_iov[1]));
			rc = 0;

			/* Use a fudge factor of 256 bytes in हाल we collide
			 * with a dअगरferent set_EAs command.
			 */
			अगर(CIFSMaxBufSize - MAX_SMB2_CREATE_RESPONSE_SIZE -
			   MAX_SMB2_CLOSE_RESPONSE_SIZE - 256 <
			   used_len + ea_name_len + ea_value_len + 1) अणु
				rc = -ENOSPC;
				जाओ sea_निकास;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Open */
	स_रखो(&खोलो_iov, 0, माप(खोलो_iov));
	rqst[0].rq_iov = खोलो_iov;
	rqst[0].rq_nvec = SMB2_CREATE_IOV_SIZE;

	स_रखो(&oparms, 0, माप(oparms));
	oparms.tcon = tcon;
	oparms.desired_access = खाता_WRITE_EA;
	oparms.disposition = खाता_OPEN;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = SMB2_खोलो_init(tcon, server,
			    &rqst[0], &oplock, &oparms, utf16_path);
	अगर (rc)
		जाओ sea_निकास;
	smb2_set_next_command(tcon, &rqst[0]);


	/* Set Info */
	स_रखो(&si_iov, 0, माप(si_iov));
	rqst[1].rq_iov = si_iov;
	rqst[1].rq_nvec = 1;

	len = माप(*ea) + ea_name_len + ea_value_len + 1;
	ea = kzalloc(len, GFP_KERNEL);
	अगर (ea == शून्य) अणु
		rc = -ENOMEM;
		जाओ sea_निकास;
	पूर्ण

	ea->ea_name_length = ea_name_len;
	ea->ea_value_length = cpu_to_le16(ea_value_len);
	स_नकल(ea->ea_data, ea_name, ea_name_len + 1);
	स_नकल(ea->ea_data + ea_name_len + 1, ea_value, ea_value_len);

	size[0] = len;
	data[0] = ea;

	rc = SMB2_set_info_init(tcon, server,
				&rqst[1], COMPOUND_FID,
				COMPOUND_FID, current->tgid,
				खाता_FULL_EA_INFORMATION,
				SMB2_O_INFO_खाता, 0, data, size);
	smb2_set_next_command(tcon, &rqst[1]);
	smb2_set_related(&rqst[1]);


	/* Close */
	स_रखो(&बंद_iov, 0, माप(बंद_iov));
	rqst[2].rq_iov = बंद_iov;
	rqst[2].rq_nvec = 1;
	rc = SMB2_बंद_init(tcon, server,
			     &rqst[2], COMPOUND_FID, COMPOUND_FID, false);
	smb2_set_related(&rqst[2]);

	rc = compound_send_recv(xid, ses, server,
				flags, 3, rqst,
				resp_buftype, rsp_iov);
	/* no need to bump num_remote_खोलोs because handle immediately बंदd */

 sea_निकास:
	kमुक्त(ea);
	kमुक्त(utf16_path);
	SMB2_खोलो_मुक्त(&rqst[0]);
	SMB2_set_info_मुक्त(&rqst[1]);
	SMB2_बंद_मुक्त(&rqst[2]);
	मुक्त_rsp_buf(resp_buftype[0], rsp_iov[0].iov_base);
	मुक्त_rsp_buf(resp_buftype[1], rsp_iov[1].iov_base);
	मुक्त_rsp_buf(resp_buftype[2], rsp_iov[2].iov_base);
	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल bool
smb2_can_echo(काष्ठा TCP_Server_Info *server)
अणु
	वापस server->echoes;
पूर्ण

अटल व्योम
smb2_clear_stats(काष्ठा cअगरs_tcon *tcon)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUMBER_OF_SMB2_COMMANDS; i++) अणु
		atomic_set(&tcon->stats.smb2_stats.smb2_com_sent[i], 0);
		atomic_set(&tcon->stats.smb2_stats.smb2_com_failed[i], 0);
	पूर्ण
पूर्ण

अटल व्योम
smb2_dump_share_caps(काष्ठा seq_file *m, काष्ठा cअगरs_tcon *tcon)
अणु
	seq_माला_दो(m, "\n\tShare Capabilities:");
	अगर (tcon->capabilities & SMB2_SHARE_CAP_DFS)
		seq_माला_दो(m, " DFS,");
	अगर (tcon->capabilities & SMB2_SHARE_CAP_CONTINUOUS_AVAILABILITY)
		seq_माला_दो(m, " CONTINUOUS AVAILABILITY,");
	अगर (tcon->capabilities & SMB2_SHARE_CAP_SCALEOUT)
		seq_माला_दो(m, " SCALEOUT,");
	अगर (tcon->capabilities & SMB2_SHARE_CAP_CLUSTER)
		seq_माला_दो(m, " CLUSTER,");
	अगर (tcon->capabilities & SMB2_SHARE_CAP_ASYMMETRIC)
		seq_माला_दो(m, " ASYMMETRIC,");
	अगर (tcon->capabilities == 0)
		seq_माला_दो(m, " None");
	अगर (tcon->ss_flags & SSINFO_FLAGS_ALIGNED_DEVICE)
		seq_माला_दो(m, " Aligned,");
	अगर (tcon->ss_flags & SSINFO_FLAGS_PARTITION_ALIGNED_ON_DEVICE)
		seq_माला_दो(m, " Partition Aligned,");
	अगर (tcon->ss_flags & SSINFO_FLAGS_NO_SEEK_PENALTY)
		seq_माला_दो(m, " SSD,");
	अगर (tcon->ss_flags & SSINFO_FLAGS_TRIM_ENABLED)
		seq_माला_दो(m, " TRIM-support,");

	seq_म_लिखो(m, "\tShare Flags: 0x%x", tcon->share_flags);
	seq_म_लिखो(m, "\n\ttid: 0x%x", tcon->tid);
	अगर (tcon->perf_sector_size)
		seq_म_लिखो(m, "\tOptimal sector size: 0x%x",
			   tcon->perf_sector_size);
	seq_म_लिखो(m, "\tMaximal Access: 0x%x", tcon->maximal_access);
पूर्ण

अटल व्योम
smb2_prपूर्णांक_stats(काष्ठा seq_file *m, काष्ठा cअगरs_tcon *tcon)
अणु
	atomic_t *sent = tcon->stats.smb2_stats.smb2_com_sent;
	atomic_t *failed = tcon->stats.smb2_stats.smb2_com_failed;

	/*
	 *  Can't display SMB2_NEGOTIATE, SESSION_SETUP, LOGOFF, CANCEL and ECHO
	 *  totals (requests sent) since those SMBs are per-session not per tcon
	 */
	seq_म_लिखो(m, "\nBytes read: %llu  Bytes written: %llu",
		   (दीर्घ दीर्घ)(tcon->bytes_पढ़ो),
		   (दीर्घ दीर्घ)(tcon->bytes_written));
	seq_म_लिखो(m, "\nOpen files: %d total (local), %d open on server",
		   atomic_पढ़ो(&tcon->num_local_खोलोs),
		   atomic_पढ़ो(&tcon->num_remote_खोलोs));
	seq_म_लिखो(m, "\nTreeConnects: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_TREE_CONNECT_HE]),
		   atomic_पढ़ो(&failed[SMB2_TREE_CONNECT_HE]));
	seq_म_लिखो(m, "\nTreeDisconnects: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_TREE_DISCONNECT_HE]),
		   atomic_पढ़ो(&failed[SMB2_TREE_DISCONNECT_HE]));
	seq_म_लिखो(m, "\nCreates: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_CREATE_HE]),
		   atomic_पढ़ो(&failed[SMB2_CREATE_HE]));
	seq_म_लिखो(m, "\nCloses: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_CLOSE_HE]),
		   atomic_पढ़ो(&failed[SMB2_CLOSE_HE]));
	seq_म_लिखो(m, "\nFlushes: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_FLUSH_HE]),
		   atomic_पढ़ो(&failed[SMB2_FLUSH_HE]));
	seq_म_लिखो(m, "\nReads: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_READ_HE]),
		   atomic_पढ़ो(&failed[SMB2_READ_HE]));
	seq_म_लिखो(m, "\nWrites: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_WRITE_HE]),
		   atomic_पढ़ो(&failed[SMB2_WRITE_HE]));
	seq_म_लिखो(m, "\nLocks: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_LOCK_HE]),
		   atomic_पढ़ो(&failed[SMB2_LOCK_HE]));
	seq_म_लिखो(m, "\nIOCTLs: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_IOCTL_HE]),
		   atomic_पढ़ो(&failed[SMB2_IOCTL_HE]));
	seq_म_लिखो(m, "\nQueryDirectories: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_QUERY_सूचीECTORY_HE]),
		   atomic_पढ़ो(&failed[SMB2_QUERY_सूचीECTORY_HE]));
	seq_म_लिखो(m, "\nChangeNotifies: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_CHANGE_NOTIFY_HE]),
		   atomic_पढ़ो(&failed[SMB2_CHANGE_NOTIFY_HE]));
	seq_म_लिखो(m, "\nQueryInfos: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_QUERY_INFO_HE]),
		   atomic_पढ़ो(&failed[SMB2_QUERY_INFO_HE]));
	seq_म_लिखो(m, "\nSetInfos: %d total %d failed",
		   atomic_पढ़ो(&sent[SMB2_SET_INFO_HE]),
		   atomic_पढ़ो(&failed[SMB2_SET_INFO_HE]));
	seq_म_लिखो(m, "\nOplockBreaks: %d sent %d failed",
		   atomic_पढ़ो(&sent[SMB2_OPLOCK_BREAK_HE]),
		   atomic_पढ़ो(&failed[SMB2_OPLOCK_BREAK_HE]));
पूर्ण

अटल व्योम
smb2_set_fid(काष्ठा cअगरsFileInfo *cfile, काष्ठा cअगरs_fid *fid, __u32 oplock)
अणु
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	काष्ठा TCP_Server_Info *server = tlink_tcon(cfile->tlink)->ses->server;

	cfile->fid.persistent_fid = fid->persistent_fid;
	cfile->fid.अस्थिर_fid = fid->अस्थिर_fid;
	cfile->fid.access = fid->access;
#अगर_घोषित CONFIG_CIFS_DEBUG2
	cfile->fid.mid = fid->mid;
#पूर्ण_अगर /* CIFS_DEBUG2 */
	server->ops->set_oplock_level(cinode, oplock, fid->epoch,
				      &fid->purge_cache);
	cinode->can_cache_brlcks = CIFS_CACHE_WRITE(cinode);
	स_नकल(cfile->fid.create_guid, fid->create_guid, 16);
पूर्ण

अटल व्योम
smb2_बंद_file(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		काष्ठा cअगरs_fid *fid)
अणु
	SMB2_बंद(xid, tcon, fid->persistent_fid, fid->अस्थिर_fid);
पूर्ण

अटल व्योम
smb2_बंद_getattr(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   काष्ठा cअगरsFileInfo *cfile)
अणु
	काष्ठा smb2_file_network_खोलो_info file_inf;
	काष्ठा inode *inode;
	पूर्णांक rc;

	rc = __SMB2_बंद(xid, tcon, cfile->fid.persistent_fid,
		   cfile->fid.अस्थिर_fid, &file_inf);
	अगर (rc)
		वापस;

	inode = d_inode(cfile->dentry);

	spin_lock(&inode->i_lock);
	CIFS_I(inode)->समय = jअगरfies;

	/* Creation समय should not need to be updated on बंद */
	अगर (file_inf.LastWriteTime)
		inode->i_mसमय = cअगरs_NTसमयToUnix(file_inf.LastWriteTime);
	अगर (file_inf.ChangeTime)
		inode->i_स_समय = cअगरs_NTसमयToUnix(file_inf.ChangeTime);
	अगर (file_inf.LastAccessTime)
		inode->i_aसमय = cअगरs_NTसमयToUnix(file_inf.LastAccessTime);

	/*
	 * i_blocks is not related to (i_size / i_blksize),
	 * but instead 512 byte (2**9) size is required क्रम
	 * calculating num blocks.
	 */
	अगर (le64_to_cpu(file_inf.AllocationSize) > 4096)
		inode->i_blocks =
			(512 - 1 + le64_to_cpu(file_inf.AllocationSize)) >> 9;

	/* End of file and Attributes should not have to be updated on बंद */
	spin_unlock(&inode->i_lock);
पूर्ण

अटल पूर्णांक
SMB2_request_res_key(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     u64 persistent_fid, u64 अस्थिर_fid,
		     काष्ठा copychunk_ioctl *pcchunk)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक ret_data_len;
	काष्ठा resume_key_req *res_key;

	rc = SMB2_ioctl(xid, tcon, persistent_fid, अस्थिर_fid,
			FSCTL_SRV_REQUEST_RESUME_KEY, true /* is_fsctl */,
			शून्य, 0 /* no input */, CIFSMaxBufSize,
			(अक्षर **)&res_key, &ret_data_len);

	अगर (rc == -EOPNOTSUPP) अणु
		pr_warn_once("Server share %s does not support copy range\n", tcon->treeName);
		जाओ req_res_key_निकास;
	पूर्ण अन्यथा अगर (rc) अणु
		cअगरs_tcon_dbg(VFS, "refcpy ioctl error %d getting resume key\n", rc);
		जाओ req_res_key_निकास;
	पूर्ण
	अगर (ret_data_len < माप(काष्ठा resume_key_req)) अणु
		cअगरs_tcon_dbg(VFS, "Invalid refcopy resume key length\n");
		rc = -EINVAL;
		जाओ req_res_key_निकास;
	पूर्ण
	स_नकल(pcchunk->SourceKey, res_key->ResumeKey, COPY_CHUNK_RES_KEY_SIZE);

req_res_key_निकास:
	kमुक्त(res_key);
	वापस rc;
पूर्ण

काष्ठा iqi_vars अणु
	काष्ठा smb_rqst rqst[3];
	काष्ठा kvec rsp_iov[3];
	काष्ठा kvec खोलो_iov[SMB2_CREATE_IOV_SIZE];
	काष्ठा kvec qi_iov[1];
	काष्ठा kvec io_iov[SMB2_IOCTL_IOV_SIZE];
	काष्ठा kvec si_iov[SMB2_SET_INFO_IOV_SIZE];
	काष्ठा kvec बंद_iov[1];
पूर्ण;

अटल पूर्णांक
smb2_ioctl_query_info(स्थिर अचिन्हित पूर्णांक xid,
		      काष्ठा cअगरs_tcon *tcon,
		      काष्ठा cअगरs_sb_info *cअगरs_sb,
		      __le16 *path, पूर्णांक is_dir,
		      अचिन्हित दीर्घ p)
अणु
	काष्ठा iqi_vars *vars;
	काष्ठा smb_rqst *rqst;
	काष्ठा kvec *rsp_iov;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	अक्षर __user *arg = (अक्षर __user *)p;
	काष्ठा smb_query_info qi;
	काष्ठा smb_query_info __user *pqi;
	पूर्णांक rc = 0;
	पूर्णांक flags = CIFS_CP_CREATE_CLOSE_OP;
	काष्ठा smb2_query_info_rsp *qi_rsp = शून्य;
	काष्ठा smb2_ioctl_rsp *io_rsp = शून्य;
	व्योम *buffer = शून्य;
	पूर्णांक resp_buftype[3];
	काष्ठा cअगरs_खोलो_parms oparms;
	u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा cअगरs_fid fid;
	अचिन्हित पूर्णांक size[2];
	व्योम *data[2];
	पूर्णांक create_options = is_dir ? CREATE_NOT_खाता : CREATE_NOT_सूची;

	vars = kzalloc(माप(*vars), GFP_ATOMIC);
	अगर (vars == शून्य)
		वापस -ENOMEM;
	rqst = &vars->rqst[0];
	rsp_iov = &vars->rsp_iov[0];

	resp_buftype[0] = resp_buftype[1] = resp_buftype[2] = CIFS_NO_BUFFER;

	अगर (copy_from_user(&qi, arg, माप(काष्ठा smb_query_info)))
		जाओ e_fault;

	अगर (qi.output_buffer_length > 1024) अणु
		kमुक्त(vars);
		वापस -EINVAL;
	पूर्ण

	अगर (!ses || !server) अणु
		kमुक्त(vars);
		वापस -EIO;
	पूर्ण

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	buffer = memdup_user(arg + माप(काष्ठा smb_query_info),
			     qi.output_buffer_length);
	अगर (IS_ERR(buffer)) अणु
		kमुक्त(vars);
		वापस PTR_ERR(buffer);
	पूर्ण

	/* Open */
	rqst[0].rq_iov = &vars->खोलो_iov[0];
	rqst[0].rq_nvec = SMB2_CREATE_IOV_SIZE;

	स_रखो(&oparms, 0, माप(oparms));
	oparms.tcon = tcon;
	oparms.disposition = खाता_OPEN;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, create_options);
	oparms.fid = &fid;
	oparms.reconnect = false;

	अगर (qi.flags & PASSTHRU_FSCTL) अणु
		चयन (qi.info_type & FSCTL_DEVICE_ACCESS_MASK) अणु
		हाल FSCTL_DEVICE_ACCESS_खाता_READ_WRITE_ACCESS:
			oparms.desired_access = खाता_READ_DATA | खाता_WRITE_DATA | खाता_READ_ATTRIBUTES | SYNCHRONIZE;
			अवरोध;
		हाल FSCTL_DEVICE_ACCESS_खाता_ANY_ACCESS:
			oparms.desired_access = GENERIC_ALL;
			अवरोध;
		हाल FSCTL_DEVICE_ACCESS_खाता_READ_ACCESS:
			oparms.desired_access = GENERIC_READ;
			अवरोध;
		हाल FSCTL_DEVICE_ACCESS_खाता_WRITE_ACCESS:
			oparms.desired_access = GENERIC_WRITE;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (qi.flags & PASSTHRU_SET_INFO) अणु
		oparms.desired_access = GENERIC_WRITE;
	पूर्ण अन्यथा अणु
		oparms.desired_access = खाता_READ_ATTRIBUTES | READ_CONTROL;
	पूर्ण

	rc = SMB2_खोलो_init(tcon, server,
			    &rqst[0], &oplock, &oparms, path);
	अगर (rc)
		जाओ iqinf_निकास;
	smb2_set_next_command(tcon, &rqst[0]);

	/* Query */
	अगर (qi.flags & PASSTHRU_FSCTL) अणु
		/* Can eventually relax perm check since server enक्रमces too */
		अगर (!capable(CAP_SYS_ADMIN))
			rc = -EPERM;
		अन्यथा  अणु
			rqst[1].rq_iov = &vars->io_iov[0];
			rqst[1].rq_nvec = SMB2_IOCTL_IOV_SIZE;

			rc = SMB2_ioctl_init(tcon, server,
					     &rqst[1],
					     COMPOUND_FID, COMPOUND_FID,
					     qi.info_type, true, buffer,
					     qi.output_buffer_length,
					     CIFSMaxBufSize -
					     MAX_SMB2_CREATE_RESPONSE_SIZE -
					     MAX_SMB2_CLOSE_RESPONSE_SIZE);
		पूर्ण
	पूर्ण अन्यथा अगर (qi.flags == PASSTHRU_SET_INFO) अणु
		/* Can eventually relax perm check since server enक्रमces too */
		अगर (!capable(CAP_SYS_ADMIN))
			rc = -EPERM;
		अन्यथा  अणु
			rqst[1].rq_iov = &vars->si_iov[0];
			rqst[1].rq_nvec = 1;

			size[0] = 8;
			data[0] = buffer;

			rc = SMB2_set_info_init(tcon, server,
					&rqst[1],
					COMPOUND_FID, COMPOUND_FID,
					current->tgid,
					खाता_END_OF_खाता_INFORMATION,
					SMB2_O_INFO_खाता, 0, data, size);
		पूर्ण
	पूर्ण अन्यथा अगर (qi.flags == PASSTHRU_QUERY_INFO) अणु
		rqst[1].rq_iov = &vars->qi_iov[0];
		rqst[1].rq_nvec = 1;

		rc = SMB2_query_info_init(tcon, server,
				  &rqst[1], COMPOUND_FID,
				  COMPOUND_FID, qi.file_info_class,
				  qi.info_type, qi.additional_inक्रमmation,
				  qi.input_buffer_length,
				  qi.output_buffer_length, buffer);
	पूर्ण अन्यथा अणु /* unknown flags */
		cअगरs_tcon_dbg(VFS, "Invalid passthru query flags: 0x%x\n",
			      qi.flags);
		rc = -EINVAL;
	पूर्ण

	अगर (rc)
		जाओ iqinf_निकास;
	smb2_set_next_command(tcon, &rqst[1]);
	smb2_set_related(&rqst[1]);

	/* Close */
	rqst[2].rq_iov = &vars->बंद_iov[0];
	rqst[2].rq_nvec = 1;

	rc = SMB2_बंद_init(tcon, server,
			     &rqst[2], COMPOUND_FID, COMPOUND_FID, false);
	अगर (rc)
		जाओ iqinf_निकास;
	smb2_set_related(&rqst[2]);

	rc = compound_send_recv(xid, ses, server,
				flags, 3, rqst,
				resp_buftype, rsp_iov);
	अगर (rc)
		जाओ iqinf_निकास;

	/* No need to bump num_remote_खोलोs since handle immediately बंदd */
	अगर (qi.flags & PASSTHRU_FSCTL) अणु
		pqi = (काष्ठा smb_query_info __user *)arg;
		io_rsp = (काष्ठा smb2_ioctl_rsp *)rsp_iov[1].iov_base;
		अगर (le32_to_cpu(io_rsp->OutputCount) < qi.input_buffer_length)
			qi.input_buffer_length = le32_to_cpu(io_rsp->OutputCount);
		अगर (qi.input_buffer_length > 0 &&
		    le32_to_cpu(io_rsp->OutputOffset) + qi.input_buffer_length
		    > rsp_iov[1].iov_len)
			जाओ e_fault;

		अगर (copy_to_user(&pqi->input_buffer_length,
				 &qi.input_buffer_length,
				 माप(qi.input_buffer_length)))
			जाओ e_fault;

		अगर (copy_to_user((व्योम __user *)pqi + माप(काष्ठा smb_query_info),
				 (स्थिर व्योम *)io_rsp + le32_to_cpu(io_rsp->OutputOffset),
				 qi.input_buffer_length))
			जाओ e_fault;
	पूर्ण अन्यथा अणु
		pqi = (काष्ठा smb_query_info __user *)arg;
		qi_rsp = (काष्ठा smb2_query_info_rsp *)rsp_iov[1].iov_base;
		अगर (le32_to_cpu(qi_rsp->OutputBufferLength) < qi.input_buffer_length)
			qi.input_buffer_length = le32_to_cpu(qi_rsp->OutputBufferLength);
		अगर (copy_to_user(&pqi->input_buffer_length,
				 &qi.input_buffer_length,
				 माप(qi.input_buffer_length)))
			जाओ e_fault;

		अगर (copy_to_user(pqi + 1, qi_rsp->Buffer,
				 qi.input_buffer_length))
			जाओ e_fault;
	पूर्ण

 iqinf_निकास:
	cअगरs_small_buf_release(rqst[0].rq_iov[0].iov_base);
	cअगरs_small_buf_release(rqst[1].rq_iov[0].iov_base);
	cअगरs_small_buf_release(rqst[2].rq_iov[0].iov_base);
	मुक्त_rsp_buf(resp_buftype[0], rsp_iov[0].iov_base);
	मुक्त_rsp_buf(resp_buftype[1], rsp_iov[1].iov_base);
	मुक्त_rsp_buf(resp_buftype[2], rsp_iov[2].iov_base);
	kमुक्त(vars);
	kमुक्त(buffer);
	वापस rc;

e_fault:
	rc = -EFAULT;
	जाओ iqinf_निकास;
पूर्ण

अटल sमाप_प्रकार
smb2_copychunk_range(स्थिर अचिन्हित पूर्णांक xid,
			काष्ठा cअगरsFileInfo *srcfile,
			काष्ठा cअगरsFileInfo *trgtfile, u64 src_off,
			u64 len, u64 dest_off)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक ret_data_len;
	काष्ठा copychunk_ioctl *pcchunk;
	काष्ठा copychunk_ioctl_rsp *retbuf = शून्य;
	काष्ठा cअगरs_tcon *tcon;
	पूर्णांक chunks_copied = 0;
	bool chunk_sizes_updated = false;
	sमाप_प्रकार bytes_written, total_bytes_written = 0;

	pcchunk = kदो_स्मृति(माप(काष्ठा copychunk_ioctl), GFP_KERNEL);

	अगर (pcchunk == शून्य)
		वापस -ENOMEM;

	cअगरs_dbg(FYI, "%s: about to call request res key\n", __func__);
	/* Request a key from the server to identअगरy the source of the copy */
	rc = SMB2_request_res_key(xid, tlink_tcon(srcfile->tlink),
				srcfile->fid.persistent_fid,
				srcfile->fid.अस्थिर_fid, pcchunk);

	/* Note: request_res_key sets res_key null only अगर rc !=0 */
	अगर (rc)
		जाओ cchunk_out;

	/* For now array only one chunk दीर्घ, will make more flexible later */
	pcchunk->ChunkCount = cpu_to_le32(1);
	pcchunk->Reserved = 0;
	pcchunk->Reserved2 = 0;

	tcon = tlink_tcon(trgtfile->tlink);

	जबतक (len > 0) अणु
		pcchunk->SourceOffset = cpu_to_le64(src_off);
		pcchunk->TargetOffset = cpu_to_le64(dest_off);
		pcchunk->Length =
			cpu_to_le32(min_t(u32, len, tcon->max_bytes_chunk));

		/* Request server copy to target from src identअगरied by key */
		kमुक्त(retbuf);
		retbuf = शून्य;
		rc = SMB2_ioctl(xid, tcon, trgtfile->fid.persistent_fid,
			trgtfile->fid.अस्थिर_fid, FSCTL_SRV_COPYCHUNK_WRITE,
			true /* is_fsctl */, (अक्षर *)pcchunk,
			माप(काष्ठा copychunk_ioctl),	CIFSMaxBufSize,
			(अक्षर **)&retbuf, &ret_data_len);
		अगर (rc == 0) अणु
			अगर (ret_data_len !=
					माप(काष्ठा copychunk_ioctl_rsp)) अणु
				cअगरs_tcon_dbg(VFS, "Invalid cchunk response size\n");
				rc = -EIO;
				जाओ cchunk_out;
			पूर्ण
			अगर (retbuf->TotalBytesWritten == 0) अणु
				cअगरs_dbg(FYI, "no bytes copied\n");
				rc = -EIO;
				जाओ cchunk_out;
			पूर्ण
			/*
			 * Check अगर server claimed to ग_लिखो more than we asked
			 */
			अगर (le32_to_cpu(retbuf->TotalBytesWritten) >
			    le32_to_cpu(pcchunk->Length)) अणु
				cअगरs_tcon_dbg(VFS, "Invalid copy chunk response\n");
				rc = -EIO;
				जाओ cchunk_out;
			पूर्ण
			अगर (le32_to_cpu(retbuf->ChunksWritten) != 1) अणु
				cअगरs_tcon_dbg(VFS, "Invalid num chunks written\n");
				rc = -EIO;
				जाओ cchunk_out;
			पूर्ण
			chunks_copied++;

			bytes_written = le32_to_cpu(retbuf->TotalBytesWritten);
			src_off += bytes_written;
			dest_off += bytes_written;
			len -= bytes_written;
			total_bytes_written += bytes_written;

			cअगरs_dbg(FYI, "Chunks %d PartialChunk %d Total %zu\n",
				le32_to_cpu(retbuf->ChunksWritten),
				le32_to_cpu(retbuf->ChunkBytesWritten),
				bytes_written);
		पूर्ण अन्यथा अगर (rc == -EINVAL) अणु
			अगर (ret_data_len != माप(काष्ठा copychunk_ioctl_rsp))
				जाओ cchunk_out;

			cअगरs_dbg(FYI, "MaxChunks %d BytesChunk %d MaxCopy %d\n",
				le32_to_cpu(retbuf->ChunksWritten),
				le32_to_cpu(retbuf->ChunkBytesWritten),
				le32_to_cpu(retbuf->TotalBytesWritten));

			/*
			 * Check अगर this is the first request using these sizes,
			 * (ie check अगर copy succeed once with original sizes
			 * and check अगर the server gave us dअगरferent sizes after
			 * we alपढ़ोy updated max sizes on previous request).
			 * अगर not then why is the server वापसing an error now
			 */
			अगर ((chunks_copied != 0) || chunk_sizes_updated)
				जाओ cchunk_out;

			/* Check that server is not asking us to grow size */
			अगर (le32_to_cpu(retbuf->ChunkBytesWritten) <
					tcon->max_bytes_chunk)
				tcon->max_bytes_chunk =
					le32_to_cpu(retbuf->ChunkBytesWritten);
			अन्यथा
				जाओ cchunk_out; /* server gave us bogus size */

			/* No need to change MaxChunks since alपढ़ोy set to 1 */
			chunk_sizes_updated = true;
		पूर्ण अन्यथा
			जाओ cchunk_out;
	पूर्ण

cchunk_out:
	kमुक्त(pcchunk);
	kमुक्त(retbuf);
	अगर (rc)
		वापस rc;
	अन्यथा
		वापस total_bytes_written;
पूर्ण

अटल पूर्णांक
smb2_flush_file(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		काष्ठा cअगरs_fid *fid)
अणु
	वापस SMB2_flush(xid, tcon, fid->persistent_fid, fid->अस्थिर_fid);
पूर्ण

अटल अचिन्हित पूर्णांक
smb2_पढ़ो_data_offset(अक्षर *buf)
अणु
	काष्ठा smb2_पढ़ो_rsp *rsp = (काष्ठा smb2_पढ़ो_rsp *)buf;

	वापस rsp->DataOffset;
पूर्ण

अटल अचिन्हित पूर्णांक
smb2_पढ़ो_data_length(अक्षर *buf, bool in_reमुख्यing)
अणु
	काष्ठा smb2_पढ़ो_rsp *rsp = (काष्ठा smb2_पढ़ो_rsp *)buf;

	अगर (in_reमुख्यing)
		वापस le32_to_cpu(rsp->DataReमुख्यing);

	वापस le32_to_cpu(rsp->DataLength);
पूर्ण


अटल पूर्णांक
smb2_sync_पढ़ो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_fid *pfid,
	       काष्ठा cअगरs_io_parms *parms, अचिन्हित पूर्णांक *bytes_पढ़ो,
	       अक्षर **buf, पूर्णांक *buf_type)
अणु
	parms->persistent_fid = pfid->persistent_fid;
	parms->अस्थिर_fid = pfid->अस्थिर_fid;
	वापस SMB2_पढ़ो(xid, parms, bytes_पढ़ो, buf, buf_type);
पूर्ण

अटल पूर्णांक
smb2_sync_ग_लिखो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_fid *pfid,
		काष्ठा cअगरs_io_parms *parms, अचिन्हित पूर्णांक *written,
		काष्ठा kvec *iov, अचिन्हित दीर्घ nr_segs)
अणु

	parms->persistent_fid = pfid->persistent_fid;
	parms->अस्थिर_fid = pfid->अस्थिर_fid;
	वापस SMB2_ग_लिखो(xid, parms, written, iov, nr_segs);
पूर्ण

/* Set or clear the SPARSE_खाता attribute based on value passed in setsparse */
अटल bool smb2_set_sparse(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		काष्ठा cअगरsFileInfo *cfile, काष्ठा inode *inode, __u8 setsparse)
अणु
	काष्ठा cअगरsInodeInfo *cअगरsi;
	पूर्णांक rc;

	cअगरsi = CIFS_I(inode);

	/* अगर file alपढ़ोy sparse करोn't bother setting sparse again */
	अगर ((cअगरsi->cअगरsAttrs & खाता_ATTRIBUTE_SPARSE_खाता) && setsparse)
		वापस true; /* alपढ़ोy sparse */

	अगर (!(cअगरsi->cअगरsAttrs & खाता_ATTRIBUTE_SPARSE_खाता) && !setsparse)
		वापस true; /* alपढ़ोy not sparse */

	/*
	 * Can't check क्रम sparse support on share the usual way via the
	 * FS attribute info (खाता_SUPPORTS_SPARSE_खाताS) on the share
	 * since Samba server करोesn't set the flag on the share, yet
	 * supports the set sparse FSCTL and वापसs sparse correctly
	 * in the file attributes. If we fail setting sparse though we
	 * mark that server करोes not support sparse files क्रम this share
	 * to aव्योम repeatedly sending the unsupported fsctl to server
	 * अगर the file is repeatedly extended.
	 */
	अगर (tcon->broken_sparse_sup)
		वापस false;

	rc = SMB2_ioctl(xid, tcon, cfile->fid.persistent_fid,
			cfile->fid.अस्थिर_fid, FSCTL_SET_SPARSE,
			true /* is_fctl */,
			&setsparse, 1, CIFSMaxBufSize, शून्य, शून्य);
	अगर (rc) अणु
		tcon->broken_sparse_sup = true;
		cअगरs_dbg(FYI, "set sparse rc = %d\n", rc);
		वापस false;
	पूर्ण

	अगर (setsparse)
		cअगरsi->cअगरsAttrs |= खाता_ATTRIBUTE_SPARSE_खाता;
	अन्यथा
		cअगरsi->cअगरsAttrs &= (~खाता_ATTRIBUTE_SPARSE_खाता);

	वापस true;
पूर्ण

अटल पूर्णांक
smb2_set_file_size(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   काष्ठा cअगरsFileInfo *cfile, __u64 size, bool set_alloc)
अणु
	__le64 eof = cpu_to_le64(size);
	काष्ठा inode *inode;

	/*
	 * If extending file more than one page make sparse. Many Linux fs
	 * make files sparse by शेष when extending via ftruncate
	 */
	inode = d_inode(cfile->dentry);

	अगर (!set_alloc && (size > inode->i_size + 8192)) अणु
		__u8 set_sparse = 1;

		/* whether set sparse succeeds or not, extend the file */
		smb2_set_sparse(xid, tcon, cfile, inode, set_sparse);
	पूर्ण

	वापस SMB2_set_eof(xid, tcon, cfile->fid.persistent_fid,
			    cfile->fid.अस्थिर_fid, cfile->pid, &eof);
पूर्ण

अटल पूर्णांक
smb2_duplicate_extents(स्थिर अचिन्हित पूर्णांक xid,
			काष्ठा cअगरsFileInfo *srcfile,
			काष्ठा cअगरsFileInfo *trgtfile, u64 src_off,
			u64 len, u64 dest_off)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक ret_data_len;
	काष्ठा inode *inode;
	काष्ठा duplicate_extents_to_file dup_ext_buf;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(trgtfile->tlink);

	/* server fileays advertise duplicate extent support with this flag */
	अगर ((le32_to_cpu(tcon->fsAttrInfo.Attributes) &
	     खाता_SUPPORTS_BLOCK_REFCOUNTING) == 0)
		वापस -EOPNOTSUPP;

	dup_ext_buf.VolatileFileHandle = srcfile->fid.अस्थिर_fid;
	dup_ext_buf.PersistentFileHandle = srcfile->fid.persistent_fid;
	dup_ext_buf.SourceFileOffset = cpu_to_le64(src_off);
	dup_ext_buf.TargetFileOffset = cpu_to_le64(dest_off);
	dup_ext_buf.ByteCount = cpu_to_le64(len);
	cअगरs_dbg(FYI, "Duplicate extents: src off %lld dst off %lld len %lld\n",
		src_off, dest_off, len);

	inode = d_inode(trgtfile->dentry);
	अगर (inode->i_size < dest_off + len) अणु
		rc = smb2_set_file_size(xid, tcon, trgtfile, dest_off + len, false);
		अगर (rc)
			जाओ duplicate_extents_out;

		/*
		 * Although also could set plausible allocation size (i_blocks)
		 * here in addition to setting the file size, in reflink
		 * it is likely that the target file is sparse. Its allocation
		 * size will be queried on next revalidate, but it is important
		 * to make sure that file's cached size is updated immediately
		 */
		cअगरs_setsize(inode, dest_off + len);
	पूर्ण
	rc = SMB2_ioctl(xid, tcon, trgtfile->fid.persistent_fid,
			trgtfile->fid.अस्थिर_fid,
			FSCTL_DUPLICATE_EXTENTS_TO_खाता,
			true /* is_fsctl */,
			(अक्षर *)&dup_ext_buf,
			माप(काष्ठा duplicate_extents_to_file),
			CIFSMaxBufSize, शून्य,
			&ret_data_len);

	अगर (ret_data_len > 0)
		cअगरs_dbg(FYI, "Non-zero response length in duplicate extents\n");

duplicate_extents_out:
	वापस rc;
पूर्ण

अटल पूर्णांक
smb2_set_compression(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   काष्ठा cअगरsFileInfo *cfile)
अणु
	वापस SMB2_set_compression(xid, tcon, cfile->fid.persistent_fid,
			    cfile->fid.अस्थिर_fid);
पूर्ण

अटल पूर्णांक
smb3_set_पूर्णांकegrity(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   काष्ठा cअगरsFileInfo *cfile)
अणु
	काष्ठा fsctl_set_पूर्णांकegrity_inक्रमmation_req पूर्णांकegr_info;
	अचिन्हित पूर्णांक ret_data_len;

	पूर्णांकegr_info.ChecksumAlgorithm = cpu_to_le16(CHECKSUM_TYPE_UNCHANGED);
	पूर्णांकegr_info.Flags = 0;
	पूर्णांकegr_info.Reserved = 0;

	वापस SMB2_ioctl(xid, tcon, cfile->fid.persistent_fid,
			cfile->fid.अस्थिर_fid,
			FSCTL_SET_INTEGRITY_INFORMATION,
			true /* is_fsctl */,
			(अक्षर *)&पूर्णांकegr_info,
			माप(काष्ठा fsctl_set_पूर्णांकegrity_inक्रमmation_req),
			CIFSMaxBufSize, शून्य,
			&ret_data_len);

पूर्ण

/* GMT Token is @GMT-YYYY.MM.DD-HH.MM.SS Unicode which is 48 bytes + null */
#घोषणा GMT_TOKEN_SIZE 50

#घोषणा MIN_SNAPSHOT_ARRAY_SIZE 16 /* See MS-SMB2 section 3.3.5.15.1 */

/*
 * Input buffer contains (empty) काष्ठा smb_snapshot array with size filled in
 * For output see काष्ठा SRV_SNAPSHOT_ARRAY in MS-SMB2 section 2.2.32.2
 */
अटल पूर्णांक
smb3_क्रमागत_snapshots(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   काष्ठा cअगरsFileInfo *cfile, व्योम __user *ioc_buf)
अणु
	अक्षर *retbuf = शून्य;
	अचिन्हित पूर्णांक ret_data_len = 0;
	पूर्णांक rc;
	u32 max_response_size;
	काष्ठा smb_snapshot_array snapshot_in;

	/*
	 * On the first query to क्रमागतerate the list of snapshots available
	 * क्रम this volume the buffer begins with 0 (number of snapshots
	 * which can be वापसed is zero since at that poपूर्णांक we करो not know
	 * how big the buffer needs to be). On the second query,
	 * it (ret_data_len) is set to number of snapshots so we can
	 * know to set the maximum response size larger (see below).
	 */
	अगर (get_user(ret_data_len, (अचिन्हित पूर्णांक __user *)ioc_buf))
		वापस -EFAULT;

	/*
	 * Note that क्रम snapshot queries that servers like Azure expect that
	 * the first query be minimal size (and just used to get the number/size
	 * of previous versions) so response size must be specअगरied as EXACTLY
	 * माप(काष्ठा snapshot_array) which is 16 when rounded up to multiple
	 * of eight bytes.
	 */
	अगर (ret_data_len == 0)
		max_response_size = MIN_SNAPSHOT_ARRAY_SIZE;
	अन्यथा
		max_response_size = CIFSMaxBufSize;

	rc = SMB2_ioctl(xid, tcon, cfile->fid.persistent_fid,
			cfile->fid.अस्थिर_fid,
			FSCTL_SRV_ENUMERATE_SNAPSHOTS,
			true /* is_fsctl */,
			शून्य, 0 /* no input data */, max_response_size,
			(अक्षर **)&retbuf,
			&ret_data_len);
	cअगरs_dbg(FYI, "enum snaphots ioctl returned %d and ret buflen is %d\n",
			rc, ret_data_len);
	अगर (rc)
		वापस rc;

	अगर (ret_data_len && (ioc_buf != शून्य) && (retbuf != शून्य)) अणु
		/* Fixup buffer */
		अगर (copy_from_user(&snapshot_in, ioc_buf,
		    माप(काष्ठा smb_snapshot_array))) अणु
			rc = -EFAULT;
			kमुक्त(retbuf);
			वापस rc;
		पूर्ण

		/*
		 * Check क्रम min size, ie not large enough to fit even one GMT
		 * token (snapshot).  On the first ioctl some users may pass in
		 * smaller size (or zero) to simply get the size of the array
		 * so the user space caller can allocate sufficient memory
		 * and retry the ioctl again with larger array size sufficient
		 * to hold all of the snapshot GMT tokens on the second try.
		 */
		अगर (snapshot_in.snapshot_array_size < GMT_TOKEN_SIZE)
			ret_data_len = माप(काष्ठा smb_snapshot_array);

		/*
		 * We वापस काष्ठा SRV_SNAPSHOT_ARRAY, followed by
		 * the snapshot array (of 50 byte GMT tokens) each
		 * representing an available previous version of the data
		 */
		अगर (ret_data_len > (snapshot_in.snapshot_array_size +
					माप(काष्ठा smb_snapshot_array)))
			ret_data_len = snapshot_in.snapshot_array_size +
					माप(काष्ठा smb_snapshot_array);

		अगर (copy_to_user(ioc_buf, retbuf, ret_data_len))
			rc = -EFAULT;
	पूर्ण

	kमुक्त(retbuf);
	वापस rc;
पूर्ण



अटल पूर्णांक
smb3_notअगरy(स्थिर अचिन्हित पूर्णांक xid, काष्ठा file *pfile,
	    व्योम __user *ioc_buf)
अणु
	काष्ठा smb3_notअगरy notअगरy;
	काष्ठा dentry *dentry = pfile->f_path.dentry;
	काष्ठा inode *inode = file_inode(pfile);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_tcon *tcon;
	स्थिर अचिन्हित अक्षर *path;
	व्योम *page = alloc_dentry_path();
	__le16 *utf16_path = शून्य;
	u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	पूर्णांक rc = 0;

	path = build_path_from_dentry(dentry, page);
	अगर (IS_ERR(path)) अणु
		rc = PTR_ERR(path);
		जाओ notअगरy_निकास;
	पूर्ण

	utf16_path = cअगरs_convert_path_to_utf16(path, cअगरs_sb);
	अगर (utf16_path == शून्य) अणु
		rc = -ENOMEM;
		जाओ notअगरy_निकास;
	पूर्ण

	अगर (copy_from_user(&notअगरy, ioc_buf, माप(काष्ठा smb3_notअगरy))) अणु
		rc = -EFAULT;
		जाओ notअगरy_निकास;
	पूर्ण

	tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	oparms.tcon = tcon;
	oparms.desired_access = खाता_READ_ATTRIBUTES | खाता_READ_DATA;
	oparms.disposition = खाता_OPEN;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = SMB2_खोलो(xid, &oparms, utf16_path, &oplock, शून्य, शून्य, शून्य,
		       शून्य);
	अगर (rc)
		जाओ notअगरy_निकास;

	rc = SMB2_change_notअगरy(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid,
				notअगरy.watch_tree, notअगरy.completion_filter);

	SMB2_बंद(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid);

	cअगरs_dbg(FYI, "change notify for path %s rc %d\n", path, rc);

notअगरy_निकास:
	मुक्त_dentry_path(page);
	kमुक्त(utf16_path);
	वापस rc;
पूर्ण

अटल पूर्णांक
smb2_query_dir_first(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     स्थिर अक्षर *path, काष्ठा cअगरs_sb_info *cअगरs_sb,
		     काष्ठा cअगरs_fid *fid, __u16 search_flags,
		     काष्ठा cअगरs_search_info *srch_inf)
अणु
	__le16 *utf16_path;
	काष्ठा smb_rqst rqst[2];
	काष्ठा kvec rsp_iov[2];
	पूर्णांक resp_buftype[2];
	काष्ठा kvec खोलो_iov[SMB2_CREATE_IOV_SIZE];
	काष्ठा kvec qd_iov[SMB2_QUERY_सूचीECTORY_IOV_SIZE];
	पूर्णांक rc, flags = 0;
	u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा smb2_query_directory_rsp *qd_rsp = शून्य;
	काष्ठा smb2_create_rsp *op_rsp = शून्य;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(tcon->ses);

	utf16_path = cअगरs_convert_path_to_utf16(path, cअगरs_sb);
	अगर (!utf16_path)
		वापस -ENOMEM;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(rqst, 0, माप(rqst));
	resp_buftype[0] = resp_buftype[1] = CIFS_NO_BUFFER;
	स_रखो(rsp_iov, 0, माप(rsp_iov));

	/* Open */
	स_रखो(&खोलो_iov, 0, माप(खोलो_iov));
	rqst[0].rq_iov = खोलो_iov;
	rqst[0].rq_nvec = SMB2_CREATE_IOV_SIZE;

	oparms.tcon = tcon;
	oparms.desired_access = खाता_READ_ATTRIBUTES | खाता_READ_DATA;
	oparms.disposition = खाता_OPEN;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.fid = fid;
	oparms.reconnect = false;

	rc = SMB2_खोलो_init(tcon, server,
			    &rqst[0], &oplock, &oparms, utf16_path);
	अगर (rc)
		जाओ qdf_मुक्त;
	smb2_set_next_command(tcon, &rqst[0]);

	/* Query directory */
	srch_inf->entries_in_buffer = 0;
	srch_inf->index_of_last_entry = 2;

	स_रखो(&qd_iov, 0, माप(qd_iov));
	rqst[1].rq_iov = qd_iov;
	rqst[1].rq_nvec = SMB2_QUERY_सूचीECTORY_IOV_SIZE;

	rc = SMB2_query_directory_init(xid, tcon, server,
				       &rqst[1],
				       COMPOUND_FID, COMPOUND_FID,
				       0, srch_inf->info_level);
	अगर (rc)
		जाओ qdf_मुक्त;

	smb2_set_related(&rqst[1]);

	rc = compound_send_recv(xid, tcon->ses, server,
				flags, 2, rqst,
				resp_buftype, rsp_iov);

	/* If the खोलो failed there is nothing to करो */
	op_rsp = (काष्ठा smb2_create_rsp *)rsp_iov[0].iov_base;
	अगर (op_rsp == शून्य || op_rsp->sync_hdr.Status != STATUS_SUCCESS) अणु
		cअगरs_dbg(FYI, "query_dir_first: open failed rc=%d\n", rc);
		जाओ qdf_मुक्त;
	पूर्ण
	fid->persistent_fid = op_rsp->PersistentFileId;
	fid->अस्थिर_fid = op_rsp->VolatileFileId;

	/* Anything अन्यथा than ENODATA means a genuine error */
	अगर (rc && rc != -ENODATA) अणु
		SMB2_बंद(xid, tcon, fid->persistent_fid, fid->अस्थिर_fid);
		cअगरs_dbg(FYI, "query_dir_first: query directory failed rc=%d\n", rc);
		trace_smb3_query_dir_err(xid, fid->persistent_fid,
					 tcon->tid, tcon->ses->Suid, 0, 0, rc);
		जाओ qdf_मुक्त;
	पूर्ण

	atomic_inc(&tcon->num_remote_खोलोs);

	qd_rsp = (काष्ठा smb2_query_directory_rsp *)rsp_iov[1].iov_base;
	अगर (qd_rsp->sync_hdr.Status == STATUS_NO_MORE_खाताS) अणु
		trace_smb3_query_dir_करोne(xid, fid->persistent_fid,
					  tcon->tid, tcon->ses->Suid, 0, 0);
		srch_inf->endOfSearch = true;
		rc = 0;
		जाओ qdf_मुक्त;
	पूर्ण

	rc = smb2_parse_query_directory(tcon, &rsp_iov[1], resp_buftype[1],
					srch_inf);
	अगर (rc) अणु
		trace_smb3_query_dir_err(xid, fid->persistent_fid, tcon->tid,
			tcon->ses->Suid, 0, 0, rc);
		जाओ qdf_मुक्त;
	पूर्ण
	resp_buftype[1] = CIFS_NO_BUFFER;

	trace_smb3_query_dir_करोne(xid, fid->persistent_fid, tcon->tid,
			tcon->ses->Suid, 0, srch_inf->entries_in_buffer);

 qdf_मुक्त:
	kमुक्त(utf16_path);
	SMB2_खोलो_मुक्त(&rqst[0]);
	SMB2_query_directory_मुक्त(&rqst[1]);
	मुक्त_rsp_buf(resp_buftype[0], rsp_iov[0].iov_base);
	मुक्त_rsp_buf(resp_buftype[1], rsp_iov[1].iov_base);
	वापस rc;
पूर्ण

अटल पूर्णांक
smb2_query_dir_next(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		    काष्ठा cअगरs_fid *fid, __u16 search_flags,
		    काष्ठा cअगरs_search_info *srch_inf)
अणु
	वापस SMB2_query_directory(xid, tcon, fid->persistent_fid,
				    fid->अस्थिर_fid, 0, srch_inf);
पूर्ण

अटल पूर्णांक
smb2_बंद_dir(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	       काष्ठा cअगरs_fid *fid)
अणु
	वापस SMB2_बंद(xid, tcon, fid->persistent_fid, fid->अस्थिर_fid);
पूर्ण

/*
 * If we negotiate SMB2 protocol and get STATUS_PENDING - update
 * the number of credits and वापस true. Otherwise - वापस false.
 */
अटल bool
smb2_is_status_pending(अक्षर *buf, काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा smb2_sync_hdr *shdr = (काष्ठा smb2_sync_hdr *)buf;
	पूर्णांक scredits, in_flight;

	अगर (shdr->Status != STATUS_PENDING)
		वापस false;

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
		cअगरs_dbg(FYI, "%s: status pending add %u credits total=%d\n",
				__func__, le16_to_cpu(shdr->CreditRequest), scredits);
	पूर्ण

	वापस true;
पूर्ण

अटल bool
smb2_is_session_expired(अक्षर *buf)
अणु
	काष्ठा smb2_sync_hdr *shdr = (काष्ठा smb2_sync_hdr *)buf;

	अगर (shdr->Status != STATUS_NETWORK_SESSION_EXPIRED &&
	    shdr->Status != STATUS_USER_SESSION_DELETED)
		वापस false;

	trace_smb3_ses_expired(shdr->TreeId, shdr->SessionId,
			       le16_to_cpu(shdr->Command),
			       le64_to_cpu(shdr->MessageId));
	cअगरs_dbg(FYI, "Session expired or deleted\n");

	वापस true;
पूर्ण

अटल bool
smb2_is_status_io_समयout(अक्षर *buf)
अणु
	काष्ठा smb2_sync_hdr *shdr = (काष्ठा smb2_sync_hdr *)buf;

	अगर (shdr->Status == STATUS_IO_TIMEOUT)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम
smb2_is_network_name_deleted(अक्षर *buf, काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा smb2_sync_hdr *shdr = (काष्ठा smb2_sync_hdr *)buf;
	काष्ठा list_head *पंचांगp, *पंचांगp1;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;

	अगर (shdr->Status != STATUS_NETWORK_NAME_DELETED)
		वापस;

	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each(पंचांगp, &server->smb_ses_list) अणु
		ses = list_entry(पंचांगp, काष्ठा cअगरs_ses, smb_ses_list);
		list_क्रम_each(पंचांगp1, &ses->tcon_list) अणु
			tcon = list_entry(पंचांगp1, काष्ठा cअगरs_tcon, tcon_list);
			अगर (tcon->tid == shdr->TreeId) अणु
				tcon->need_reconnect = true;
				spin_unlock(&cअगरs_tcp_ses_lock);
				pr_warn_once("Server share %s deleted.\n",
					     tcon->treeName);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&cअगरs_tcp_ses_lock);
पूर्ण

अटल पूर्णांक
smb2_oplock_response(काष्ठा cअगरs_tcon *tcon, काष्ठा cअगरs_fid *fid,
		     काष्ठा cअगरsInodeInfo *cinode)
अणु
	अगर (tcon->ses->server->capabilities & SMB2_GLOBAL_CAP_LEASING)
		वापस SMB2_lease_अवरोध(0, tcon, cinode->lease_key,
					smb2_get_lease_state(cinode));

	वापस SMB2_oplock_अवरोध(0, tcon, fid->persistent_fid,
				 fid->अस्थिर_fid,
				 CIFS_CACHE_READ(cinode) ? 1 : 0);
पूर्ण

व्योम
smb2_set_related(काष्ठा smb_rqst *rqst)
अणु
	काष्ठा smb2_sync_hdr *shdr;

	shdr = (काष्ठा smb2_sync_hdr *)(rqst->rq_iov[0].iov_base);
	अगर (shdr == शून्य) अणु
		cअगरs_dbg(FYI, "shdr NULL in smb2_set_related\n");
		वापस;
	पूर्ण
	shdr->Flags |= SMB2_FLAGS_RELATED_OPERATIONS;
पूर्ण

अक्षर smb2_padding[7] = अणु0, 0, 0, 0, 0, 0, 0पूर्ण;

व्योम
smb2_set_next_command(काष्ठा cअगरs_tcon *tcon, काष्ठा smb_rqst *rqst)
अणु
	काष्ठा smb2_sync_hdr *shdr;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = ses->server;
	अचिन्हित दीर्घ len = smb_rqst_len(server, rqst);
	पूर्णांक i, num_padding;

	shdr = (काष्ठा smb2_sync_hdr *)(rqst->rq_iov[0].iov_base);
	अगर (shdr == शून्य) अणु
		cअगरs_dbg(FYI, "shdr NULL in smb2_set_next_command\n");
		वापस;
	पूर्ण

	/* SMB headers in a compound are 8 byte aligned. */

	/* No padding needed */
	अगर (!(len & 7))
		जाओ finished;

	num_padding = 8 - (len & 7);
	अगर (!smb3_encryption_required(tcon)) अणु
		/*
		 * If we करो not have encryption then we can just add an extra
		 * iov क्रम the padding.
		 */
		rqst->rq_iov[rqst->rq_nvec].iov_base = smb2_padding;
		rqst->rq_iov[rqst->rq_nvec].iov_len = num_padding;
		rqst->rq_nvec++;
		len += num_padding;
	पूर्ण अन्यथा अणु
		/*
		 * We can not add a small padding iov क्रम the encryption हाल
		 * because the encryption framework can not handle the padding
		 * iovs.
		 * We have to flatten this पूर्णांकo a single buffer and add
		 * the padding to it.
		 */
		क्रम (i = 1; i < rqst->rq_nvec; i++) अणु
			स_नकल(rqst->rq_iov[0].iov_base +
			       rqst->rq_iov[0].iov_len,
			       rqst->rq_iov[i].iov_base,
			       rqst->rq_iov[i].iov_len);
			rqst->rq_iov[0].iov_len += rqst->rq_iov[i].iov_len;
		पूर्ण
		स_रखो(rqst->rq_iov[0].iov_base + rqst->rq_iov[0].iov_len,
		       0, num_padding);
		rqst->rq_iov[0].iov_len += num_padding;
		len += num_padding;
		rqst->rq_nvec = 1;
	पूर्ण

 finished:
	shdr->NextCommand = cpu_to_le32(len);
पूर्ण

/*
 * Passes the query info response back to the caller on success.
 * Caller need to मुक्त this with मुक्त_rsp_buf().
 */
पूर्णांक
smb2_query_info_compound(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			 __le16 *utf16_path, u32 desired_access,
			 u32 class, u32 type, u32 output_len,
			 काष्ठा kvec *rsp, पूर्णांक *buftype,
			 काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	पूर्णांक flags = CIFS_CP_CREATE_CLOSE_OP;
	काष्ठा smb_rqst rqst[3];
	पूर्णांक resp_buftype[3];
	काष्ठा kvec rsp_iov[3];
	काष्ठा kvec खोलो_iov[SMB2_CREATE_IOV_SIZE];
	काष्ठा kvec qi_iov[1];
	काष्ठा kvec बंद_iov[1];
	u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_fid fid;
	पूर्णांक rc;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(rqst, 0, माप(rqst));
	resp_buftype[0] = resp_buftype[1] = resp_buftype[2] = CIFS_NO_BUFFER;
	स_रखो(rsp_iov, 0, माप(rsp_iov));

	स_रखो(&खोलो_iov, 0, माप(खोलो_iov));
	rqst[0].rq_iov = खोलो_iov;
	rqst[0].rq_nvec = SMB2_CREATE_IOV_SIZE;

	oparms.tcon = tcon;
	oparms.desired_access = desired_access;
	oparms.disposition = खाता_OPEN;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = SMB2_खोलो_init(tcon, server,
			    &rqst[0], &oplock, &oparms, utf16_path);
	अगर (rc)
		जाओ qic_निकास;
	smb2_set_next_command(tcon, &rqst[0]);

	स_रखो(&qi_iov, 0, माप(qi_iov));
	rqst[1].rq_iov = qi_iov;
	rqst[1].rq_nvec = 1;

	rc = SMB2_query_info_init(tcon, server,
				  &rqst[1], COMPOUND_FID, COMPOUND_FID,
				  class, type, 0,
				  output_len, 0,
				  शून्य);
	अगर (rc)
		जाओ qic_निकास;
	smb2_set_next_command(tcon, &rqst[1]);
	smb2_set_related(&rqst[1]);

	स_रखो(&बंद_iov, 0, माप(बंद_iov));
	rqst[2].rq_iov = बंद_iov;
	rqst[2].rq_nvec = 1;

	rc = SMB2_बंद_init(tcon, server,
			     &rqst[2], COMPOUND_FID, COMPOUND_FID, false);
	अगर (rc)
		जाओ qic_निकास;
	smb2_set_related(&rqst[2]);

	rc = compound_send_recv(xid, ses, server,
				flags, 3, rqst,
				resp_buftype, rsp_iov);
	अगर (rc) अणु
		मुक्त_rsp_buf(resp_buftype[1], rsp_iov[1].iov_base);
		अगर (rc == -EREMCHG) अणु
			tcon->need_reconnect = true;
			pr_warn_once("server share %s deleted\n",
				     tcon->treeName);
		पूर्ण
		जाओ qic_निकास;
	पूर्ण
	*rsp = rsp_iov[1];
	*buftype = resp_buftype[1];

 qic_निकास:
	SMB2_खोलो_मुक्त(&rqst[0]);
	SMB2_query_info_मुक्त(&rqst[1]);
	SMB2_बंद_मुक्त(&rqst[2]);
	मुक्त_rsp_buf(resp_buftype[0], rsp_iov[0].iov_base);
	मुक्त_rsp_buf(resp_buftype[2], rsp_iov[2].iov_base);
	वापस rc;
पूर्ण

अटल पूर्णांक
smb2_queryfs(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	     काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा kstatfs *buf)
अणु
	काष्ठा smb2_query_info_rsp *rsp;
	काष्ठा smb2_fs_full_size_info *info = शून्य;
	__le16 utf16_path = 0; /* Null - खोलो root of share */
	काष्ठा kvec rsp_iov = अणुशून्य, 0पूर्ण;
	पूर्णांक buftype = CIFS_NO_BUFFER;
	पूर्णांक rc;


	rc = smb2_query_info_compound(xid, tcon, &utf16_path,
				      खाता_READ_ATTRIBUTES,
				      FS_FULL_SIZE_INFORMATION,
				      SMB2_O_INFO_खाताSYSTEM,
				      माप(काष्ठा smb2_fs_full_size_info),
				      &rsp_iov, &buftype, cअगरs_sb);
	अगर (rc)
		जाओ qfs_निकास;

	rsp = (काष्ठा smb2_query_info_rsp *)rsp_iov.iov_base;
	buf->f_type = SMB2_MAGIC_NUMBER;
	info = (काष्ठा smb2_fs_full_size_info *)(
		le16_to_cpu(rsp->OutputBufferOffset) + (अक्षर *)rsp);
	rc = smb2_validate_iov(le16_to_cpu(rsp->OutputBufferOffset),
			       le32_to_cpu(rsp->OutputBufferLength),
			       &rsp_iov,
			       माप(काष्ठा smb2_fs_full_size_info));
	अगर (!rc)
		smb2_copy_fs_info_to_kstatfs(info, buf);

qfs_निकास:
	मुक्त_rsp_buf(buftype, rsp_iov.iov_base);
	वापस rc;
पूर्ण

अटल पूर्णांक
smb311_queryfs(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	       काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा kstatfs *buf)
अणु
	पूर्णांक rc;
	__le16 srch_path = 0; /* Null - खोलो root of share */
	u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_fid fid;

	अगर (!tcon->posix_extensions)
		वापस smb2_queryfs(xid, tcon, cअगरs_sb, buf);

	oparms.tcon = tcon;
	oparms.desired_access = खाता_READ_ATTRIBUTES;
	oparms.disposition = खाता_OPEN;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = SMB2_खोलो(xid, &oparms, &srch_path, &oplock, शून्य, शून्य,
		       शून्य, शून्य);
	अगर (rc)
		वापस rc;

	rc = SMB311_posix_qfs_info(xid, tcon, fid.persistent_fid,
				   fid.अस्थिर_fid, buf);
	buf->f_type = SMB2_MAGIC_NUMBER;
	SMB2_बंद(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid);
	वापस rc;
पूर्ण

अटल bool
smb2_compare_fids(काष्ठा cअगरsFileInfo *ob1, काष्ठा cअगरsFileInfo *ob2)
अणु
	वापस ob1->fid.persistent_fid == ob2->fid.persistent_fid &&
	       ob1->fid.अस्थिर_fid == ob2->fid.अस्थिर_fid;
पूर्ण

अटल पूर्णांक
smb2_mand_lock(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरsFileInfo *cfile, __u64 offset,
	       __u64 length, __u32 type, पूर्णांक lock, पूर्णांक unlock, bool रुको)
अणु
	अगर (unlock && !lock)
		type = SMB2_LOCKFLAG_UNLOCK;
	वापस SMB2_lock(xid, tlink_tcon(cfile->tlink),
			 cfile->fid.persistent_fid, cfile->fid.अस्थिर_fid,
			 current->tgid, length, offset, type, रुको);
पूर्ण

अटल व्योम
smb2_get_lease_key(काष्ठा inode *inode, काष्ठा cअगरs_fid *fid)
अणु
	स_नकल(fid->lease_key, CIFS_I(inode)->lease_key, SMB2_LEASE_KEY_SIZE);
पूर्ण

अटल व्योम
smb2_set_lease_key(काष्ठा inode *inode, काष्ठा cअगरs_fid *fid)
अणु
	स_नकल(CIFS_I(inode)->lease_key, fid->lease_key, SMB2_LEASE_KEY_SIZE);
पूर्ण

अटल व्योम
smb2_new_lease_key(काष्ठा cअगरs_fid *fid)
अणु
	generate_अक्रमom_uuid(fid->lease_key);
पूर्ण

अटल पूर्णांक
smb2_get_dfs_refer(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
		   स्थिर अक्षर *search_name,
		   काष्ठा dfs_info3_param **target_nodes,
		   अचिन्हित पूर्णांक *num_of_nodes,
		   स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
	पूर्णांक rc;
	__le16 *utf16_path = शून्य;
	पूर्णांक utf16_path_len = 0;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा fsctl_get_dfs_referral_req *dfs_req = शून्य;
	काष्ठा get_dfs_referral_rsp *dfs_rsp = शून्य;
	u32 dfs_req_size = 0, dfs_rsp_size = 0;

	cअगरs_dbg(FYI, "%s: path: %s\n", __func__, search_name);

	/*
	 * Try to use the IPC tcon, otherwise just use any
	 */
	tcon = ses->tcon_ipc;
	अगर (tcon == शून्य) अणु
		spin_lock(&cअगरs_tcp_ses_lock);
		tcon = list_first_entry_or_null(&ses->tcon_list,
						काष्ठा cअगरs_tcon,
						tcon_list);
		अगर (tcon)
			tcon->tc_count++;
		spin_unlock(&cअगरs_tcp_ses_lock);
	पूर्ण

	अगर (tcon == शून्य) अणु
		cअगरs_dbg(VFS, "session %p has no tcon available for a dfs referral request\n",
			 ses);
		rc = -ENOTCONN;
		जाओ out;
	पूर्ण

	utf16_path = cअगरs_strndup_to_utf16(search_name, PATH_MAX,
					   &utf16_path_len,
					   nls_codepage, remap);
	अगर (!utf16_path) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	dfs_req_size = माप(*dfs_req) + utf16_path_len;
	dfs_req = kzalloc(dfs_req_size, GFP_KERNEL);
	अगर (!dfs_req) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Highest DFS referral version understood */
	dfs_req->MaxReferralLevel = DFS_VERSION;

	/* Path to resolve in an UTF-16 null-terminated string */
	स_नकल(dfs_req->RequestFileName, utf16_path, utf16_path_len);

	करो अणु
		rc = SMB2_ioctl(xid, tcon, NO_खाता_ID, NO_खाता_ID,
				FSCTL_DFS_GET_REFERRALS,
				true /* is_fsctl */,
				(अक्षर *)dfs_req, dfs_req_size, CIFSMaxBufSize,
				(अक्षर **)&dfs_rsp, &dfs_rsp_size);
	पूर्ण जबतक (rc == -EAGAIN);

	अगर (rc) अणु
		अगर ((rc != -ENOENT) && (rc != -EOPNOTSUPP))
			cअगरs_tcon_dbg(VFS, "ioctl error in %s rc=%d\n", __func__, rc);
		जाओ out;
	पूर्ण

	rc = parse_dfs_referrals(dfs_rsp, dfs_rsp_size,
				 num_of_nodes, target_nodes,
				 nls_codepage, remap, search_name,
				 true /* is_unicode */);
	अगर (rc) अणु
		cअगरs_tcon_dbg(VFS, "parse error in %s rc=%d\n", __func__, rc);
		जाओ out;
	पूर्ण

 out:
	अगर (tcon && !tcon->ipc) अणु
		/* ipc tcons are not refcounted */
		spin_lock(&cअगरs_tcp_ses_lock);
		tcon->tc_count--;
		spin_unlock(&cअगरs_tcp_ses_lock);
	पूर्ण
	kमुक्त(utf16_path);
	kमुक्त(dfs_req);
	kमुक्त(dfs_rsp);
	वापस rc;
पूर्ण

अटल पूर्णांक
parse_reparse_posix(काष्ठा reparse_posix_data *symlink_buf,
		      u32 plen, अक्षर **target_path,
		      काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	अचिन्हित पूर्णांक len;

	/* See MS-FSCC 2.1.2.6 क्रम the 'NFS' style reparse tags */
	len = le16_to_cpu(symlink_buf->ReparseDataLength);

	अगर (le64_to_cpu(symlink_buf->InodeType) != NFS_SPECखाता_LNK) अणु
		cअगरs_dbg(VFS, "%lld not a supported symlink type\n",
			le64_to_cpu(symlink_buf->InodeType));
		वापस -EOPNOTSUPP;
	पूर्ण

	*target_path = cअगरs_strndup_from_utf16(
				symlink_buf->PathBuffer,
				len, true, cअगरs_sb->local_nls);
	अगर (!(*target_path))
		वापस -ENOMEM;

	convert_delimiter(*target_path, '/');
	cअगरs_dbg(FYI, "%s: target path: %s\n", __func__, *target_path);

	वापस 0;
पूर्ण

अटल पूर्णांक
parse_reparse_symlink(काष्ठा reparse_symlink_data_buffer *symlink_buf,
		      u32 plen, अक्षर **target_path,
		      काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	अचिन्हित पूर्णांक sub_len;
	अचिन्हित पूर्णांक sub_offset;

	/* We handle Symbolic Link reparse tag here. See: MS-FSCC 2.1.2.4 */

	sub_offset = le16_to_cpu(symlink_buf->SubstituteNameOffset);
	sub_len = le16_to_cpu(symlink_buf->SubstituteNameLength);
	अगर (sub_offset + 20 > plen ||
	    sub_offset + sub_len + 20 > plen) अणु
		cअगरs_dbg(VFS, "srv returned malformed symlink buffer\n");
		वापस -EIO;
	पूर्ण

	*target_path = cअगरs_strndup_from_utf16(
				symlink_buf->PathBuffer + sub_offset,
				sub_len, true, cअगरs_sb->local_nls);
	अगर (!(*target_path))
		वापस -ENOMEM;

	convert_delimiter(*target_path, '/');
	cअगरs_dbg(FYI, "%s: target path: %s\n", __func__, *target_path);

	वापस 0;
पूर्ण

अटल पूर्णांक
parse_reparse_poपूर्णांक(काष्ठा reparse_data_buffer *buf,
		    u32 plen, अक्षर **target_path,
		    काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	अगर (plen < माप(काष्ठा reparse_data_buffer)) अणु
		cअगरs_dbg(VFS, "reparse buffer is too small. Must be at least 8 bytes but was %d\n",
			 plen);
		वापस -EIO;
	पूर्ण

	अगर (plen < le16_to_cpu(buf->ReparseDataLength) +
	    माप(काष्ठा reparse_data_buffer)) अणु
		cअगरs_dbg(VFS, "srv returned invalid reparse buf length: %d\n",
			 plen);
		वापस -EIO;
	पूर्ण

	/* See MS-FSCC 2.1.2 */
	चयन (le32_to_cpu(buf->ReparseTag)) अणु
	हाल IO_REPARSE_TAG_NFS:
		वापस parse_reparse_posix(
			(काष्ठा reparse_posix_data *)buf,
			plen, target_path, cअगरs_sb);
	हाल IO_REPARSE_TAG_SYMLINK:
		वापस parse_reparse_symlink(
			(काष्ठा reparse_symlink_data_buffer *)buf,
			plen, target_path, cअगरs_sb);
	शेष:
		cअगरs_dbg(VFS, "srv returned unknown symlink buffer tag:0x%08x\n",
			 le32_to_cpu(buf->ReparseTag));
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

#घोषणा SMB2_SYMLINK_STRUCT_SIZE \
	(माप(काष्ठा smb2_err_rsp) - 1 + माप(काष्ठा smb2_symlink_err_rsp))

अटल पूर्णांक
smb2_query_symlink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *full_path,
		   अक्षर **target_path, bool is_reparse_poपूर्णांक)
अणु
	पूर्णांक rc;
	__le16 *utf16_path = शून्य;
	__u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_fid fid;
	काष्ठा kvec err_iov = अणुशून्य, 0पूर्ण;
	काष्ठा smb2_err_rsp *err_buf = शून्य;
	काष्ठा smb2_symlink_err_rsp *symlink;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(tcon->ses);
	अचिन्हित पूर्णांक sub_len;
	अचिन्हित पूर्णांक sub_offset;
	अचिन्हित पूर्णांक prपूर्णांक_len;
	अचिन्हित पूर्णांक prपूर्णांक_offset;
	पूर्णांक flags = CIFS_CP_CREATE_CLOSE_OP;
	काष्ठा smb_rqst rqst[3];
	पूर्णांक resp_buftype[3];
	काष्ठा kvec rsp_iov[3];
	काष्ठा kvec खोलो_iov[SMB2_CREATE_IOV_SIZE];
	काष्ठा kvec io_iov[SMB2_IOCTL_IOV_SIZE];
	काष्ठा kvec बंद_iov[1];
	काष्ठा smb2_create_rsp *create_rsp;
	काष्ठा smb2_ioctl_rsp *ioctl_rsp;
	काष्ठा reparse_data_buffer *reparse_buf;
	पूर्णांक create_options = is_reparse_poपूर्णांक ? OPEN_REPARSE_POINT : 0;
	u32 plen;

	cअगरs_dbg(FYI, "%s: path: %s\n", __func__, full_path);

	*target_path = शून्य;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(rqst, 0, माप(rqst));
	resp_buftype[0] = resp_buftype[1] = resp_buftype[2] = CIFS_NO_BUFFER;
	स_रखो(rsp_iov, 0, माप(rsp_iov));

	utf16_path = cअगरs_convert_path_to_utf16(full_path, cअगरs_sb);
	अगर (!utf16_path)
		वापस -ENOMEM;

	/* Open */
	स_रखो(&खोलो_iov, 0, माप(खोलो_iov));
	rqst[0].rq_iov = खोलो_iov;
	rqst[0].rq_nvec = SMB2_CREATE_IOV_SIZE;

	स_रखो(&oparms, 0, माप(oparms));
	oparms.tcon = tcon;
	oparms.desired_access = खाता_READ_ATTRIBUTES;
	oparms.disposition = खाता_OPEN;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, create_options);
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = SMB2_खोलो_init(tcon, server,
			    &rqst[0], &oplock, &oparms, utf16_path);
	अगर (rc)
		जाओ querty_निकास;
	smb2_set_next_command(tcon, &rqst[0]);


	/* IOCTL */
	स_रखो(&io_iov, 0, माप(io_iov));
	rqst[1].rq_iov = io_iov;
	rqst[1].rq_nvec = SMB2_IOCTL_IOV_SIZE;

	rc = SMB2_ioctl_init(tcon, server,
			     &rqst[1], fid.persistent_fid,
			     fid.अस्थिर_fid, FSCTL_GET_REPARSE_POINT,
			     true /* is_fctl */, शून्य, 0,
			     CIFSMaxBufSize -
			     MAX_SMB2_CREATE_RESPONSE_SIZE -
			     MAX_SMB2_CLOSE_RESPONSE_SIZE);
	अगर (rc)
		जाओ querty_निकास;

	smb2_set_next_command(tcon, &rqst[1]);
	smb2_set_related(&rqst[1]);


	/* Close */
	स_रखो(&बंद_iov, 0, माप(बंद_iov));
	rqst[2].rq_iov = बंद_iov;
	rqst[2].rq_nvec = 1;

	rc = SMB2_बंद_init(tcon, server,
			     &rqst[2], COMPOUND_FID, COMPOUND_FID, false);
	अगर (rc)
		जाओ querty_निकास;

	smb2_set_related(&rqst[2]);

	rc = compound_send_recv(xid, tcon->ses, server,
				flags, 3, rqst,
				resp_buftype, rsp_iov);

	create_rsp = rsp_iov[0].iov_base;
	अगर (create_rsp && create_rsp->sync_hdr.Status)
		err_iov = rsp_iov[0];
	ioctl_rsp = rsp_iov[1].iov_base;

	/*
	 * Open was successful and we got an ioctl response.
	 */
	अगर ((rc == 0) && (is_reparse_poपूर्णांक)) अणु
		/* See MS-FSCC 2.3.23 */

		reparse_buf = (काष्ठा reparse_data_buffer *)
			((अक्षर *)ioctl_rsp +
			 le32_to_cpu(ioctl_rsp->OutputOffset));
		plen = le32_to_cpu(ioctl_rsp->OutputCount);

		अगर (plen + le32_to_cpu(ioctl_rsp->OutputOffset) >
		    rsp_iov[1].iov_len) अणु
			cअगरs_tcon_dbg(VFS, "srv returned invalid ioctl len: %d\n",
				 plen);
			rc = -EIO;
			जाओ querty_निकास;
		पूर्ण

		rc = parse_reparse_poपूर्णांक(reparse_buf, plen, target_path,
					 cअगरs_sb);
		जाओ querty_निकास;
	पूर्ण

	अगर (!rc || !err_iov.iov_base) अणु
		rc = -ENOENT;
		जाओ querty_निकास;
	पूर्ण

	err_buf = err_iov.iov_base;
	अगर (le32_to_cpu(err_buf->ByteCount) < माप(काष्ठा smb2_symlink_err_rsp) ||
	    err_iov.iov_len < SMB2_SYMLINK_STRUCT_SIZE) अणु
		rc = -EINVAL;
		जाओ querty_निकास;
	पूर्ण

	symlink = (काष्ठा smb2_symlink_err_rsp *)err_buf->ErrorData;
	अगर (le32_to_cpu(symlink->SymLinkErrorTag) != SYMLINK_ERROR_TAG ||
	    le32_to_cpu(symlink->ReparseTag) != IO_REPARSE_TAG_SYMLINK) अणु
		rc = -EINVAL;
		जाओ querty_निकास;
	पूर्ण

	/* खोलो must fail on symlink - reset rc */
	rc = 0;
	sub_len = le16_to_cpu(symlink->SubstituteNameLength);
	sub_offset = le16_to_cpu(symlink->SubstituteNameOffset);
	prपूर्णांक_len = le16_to_cpu(symlink->Prपूर्णांकNameLength);
	prपूर्णांक_offset = le16_to_cpu(symlink->Prपूर्णांकNameOffset);

	अगर (err_iov.iov_len < SMB2_SYMLINK_STRUCT_SIZE + sub_offset + sub_len) अणु
		rc = -EINVAL;
		जाओ querty_निकास;
	पूर्ण

	अगर (err_iov.iov_len <
	    SMB2_SYMLINK_STRUCT_SIZE + prपूर्णांक_offset + prपूर्णांक_len) अणु
		rc = -EINVAL;
		जाओ querty_निकास;
	पूर्ण

	*target_path = cअगरs_strndup_from_utf16(
				(अक्षर *)symlink->PathBuffer + sub_offset,
				sub_len, true, cअगरs_sb->local_nls);
	अगर (!(*target_path)) अणु
		rc = -ENOMEM;
		जाओ querty_निकास;
	पूर्ण
	convert_delimiter(*target_path, '/');
	cअगरs_dbg(FYI, "%s: target path: %s\n", __func__, *target_path);

 querty_निकास:
	cअगरs_dbg(FYI, "query symlink rc %d\n", rc);
	kमुक्त(utf16_path);
	SMB2_खोलो_मुक्त(&rqst[0]);
	SMB2_ioctl_मुक्त(&rqst[1]);
	SMB2_बंद_मुक्त(&rqst[2]);
	मुक्त_rsp_buf(resp_buftype[0], rsp_iov[0].iov_base);
	मुक्त_rsp_buf(resp_buftype[1], rsp_iov[1].iov_base);
	मुक्त_rsp_buf(resp_buftype[2], rsp_iov[2].iov_base);
	वापस rc;
पूर्ण

पूर्णांक
smb2_query_reparse_tag(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *full_path,
		   __u32 *tag)
अणु
	पूर्णांक rc;
	__le16 *utf16_path = शून्य;
	__u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_fid fid;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(tcon->ses);
	पूर्णांक flags = CIFS_CP_CREATE_CLOSE_OP;
	काष्ठा smb_rqst rqst[3];
	पूर्णांक resp_buftype[3];
	काष्ठा kvec rsp_iov[3];
	काष्ठा kvec खोलो_iov[SMB2_CREATE_IOV_SIZE];
	काष्ठा kvec io_iov[SMB2_IOCTL_IOV_SIZE];
	काष्ठा kvec बंद_iov[1];
	काष्ठा smb2_ioctl_rsp *ioctl_rsp;
	काष्ठा reparse_data_buffer *reparse_buf;
	u32 plen;

	cअगरs_dbg(FYI, "%s: path: %s\n", __func__, full_path);

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(rqst, 0, माप(rqst));
	resp_buftype[0] = resp_buftype[1] = resp_buftype[2] = CIFS_NO_BUFFER;
	स_रखो(rsp_iov, 0, माप(rsp_iov));

	utf16_path = cअगरs_convert_path_to_utf16(full_path, cअगरs_sb);
	अगर (!utf16_path)
		वापस -ENOMEM;

	/*
	 * setup smb2खोलो - TODO add optimization to call cअगरs_get_पढ़ोable_path
	 * to see अगर there is a handle alपढ़ोy खोलो that we can use
	 */
	स_रखो(&खोलो_iov, 0, माप(खोलो_iov));
	rqst[0].rq_iov = खोलो_iov;
	rqst[0].rq_nvec = SMB2_CREATE_IOV_SIZE;

	स_रखो(&oparms, 0, माप(oparms));
	oparms.tcon = tcon;
	oparms.desired_access = खाता_READ_ATTRIBUTES;
	oparms.disposition = खाता_OPEN;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, OPEN_REPARSE_POINT);
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = SMB2_खोलो_init(tcon, server,
			    &rqst[0], &oplock, &oparms, utf16_path);
	अगर (rc)
		जाओ query_rp_निकास;
	smb2_set_next_command(tcon, &rqst[0]);


	/* IOCTL */
	स_रखो(&io_iov, 0, माप(io_iov));
	rqst[1].rq_iov = io_iov;
	rqst[1].rq_nvec = SMB2_IOCTL_IOV_SIZE;

	rc = SMB2_ioctl_init(tcon, server,
			     &rqst[1], COMPOUND_FID,
			     COMPOUND_FID, FSCTL_GET_REPARSE_POINT,
			     true /* is_fctl */, शून्य, 0,
			     CIFSMaxBufSize -
			     MAX_SMB2_CREATE_RESPONSE_SIZE -
			     MAX_SMB2_CLOSE_RESPONSE_SIZE);
	अगर (rc)
		जाओ query_rp_निकास;

	smb2_set_next_command(tcon, &rqst[1]);
	smb2_set_related(&rqst[1]);


	/* Close */
	स_रखो(&बंद_iov, 0, माप(बंद_iov));
	rqst[2].rq_iov = बंद_iov;
	rqst[2].rq_nvec = 1;

	rc = SMB2_बंद_init(tcon, server,
			     &rqst[2], COMPOUND_FID, COMPOUND_FID, false);
	अगर (rc)
		जाओ query_rp_निकास;

	smb2_set_related(&rqst[2]);

	rc = compound_send_recv(xid, tcon->ses, server,
				flags, 3, rqst,
				resp_buftype, rsp_iov);

	ioctl_rsp = rsp_iov[1].iov_base;

	/*
	 * Open was successful and we got an ioctl response.
	 */
	अगर (rc == 0) अणु
		/* See MS-FSCC 2.3.23 */

		reparse_buf = (काष्ठा reparse_data_buffer *)
			((अक्षर *)ioctl_rsp +
			 le32_to_cpu(ioctl_rsp->OutputOffset));
		plen = le32_to_cpu(ioctl_rsp->OutputCount);

		अगर (plen + le32_to_cpu(ioctl_rsp->OutputOffset) >
		    rsp_iov[1].iov_len) अणु
			cअगरs_tcon_dbg(FYI, "srv returned invalid ioctl len: %d\n",
				 plen);
			rc = -EIO;
			जाओ query_rp_निकास;
		पूर्ण
		*tag = le32_to_cpu(reparse_buf->ReparseTag);
	पूर्ण

 query_rp_निकास:
	kमुक्त(utf16_path);
	SMB2_खोलो_मुक्त(&rqst[0]);
	SMB2_ioctl_मुक्त(&rqst[1]);
	SMB2_बंद_मुक्त(&rqst[2]);
	मुक्त_rsp_buf(resp_buftype[0], rsp_iov[0].iov_base);
	मुक्त_rsp_buf(resp_buftype[1], rsp_iov[1].iov_base);
	मुक्त_rsp_buf(resp_buftype[2], rsp_iov[2].iov_base);
	वापस rc;
पूर्ण

अटल काष्ठा cअगरs_ntsd *
get_smb2_acl_by_fid(काष्ठा cअगरs_sb_info *cअगरs_sb,
		    स्थिर काष्ठा cअगरs_fid *cअगरsfid, u32 *pacllen, u32 info)
अणु
	काष्ठा cअगरs_ntsd *pntsd = शून्य;
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc = -EOPNOTSUPP;
	काष्ठा tcon_link *tlink = cअगरs_sb_tlink(cअगरs_sb);

	अगर (IS_ERR(tlink))
		वापस ERR_CAST(tlink);

	xid = get_xid();
	cअगरs_dbg(FYI, "trying to get acl\n");

	rc = SMB2_query_acl(xid, tlink_tcon(tlink), cअगरsfid->persistent_fid,
			    cअगरsfid->अस्थिर_fid, (व्योम **)&pntsd, pacllen,
			    info);
	मुक्त_xid(xid);

	cअगरs_put_tlink(tlink);

	cअगरs_dbg(FYI, "%s: rc = %d ACL len %d\n", __func__, rc, *pacllen);
	अगर (rc)
		वापस ERR_PTR(rc);
	वापस pntsd;

पूर्ण

अटल काष्ठा cअगरs_ntsd *
get_smb2_acl_by_path(काष्ठा cअगरs_sb_info *cअगरs_sb,
		     स्थिर अक्षर *path, u32 *pacllen, u32 info)
अणु
	काष्ठा cअगरs_ntsd *pntsd = शून्य;
	u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा tcon_link *tlink = cअगरs_sb_tlink(cअगरs_sb);
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;
	__le16 *utf16_path;

	cअगरs_dbg(FYI, "get smb3 acl for path %s\n", path);
	अगर (IS_ERR(tlink))
		वापस ERR_CAST(tlink);

	tcon = tlink_tcon(tlink);
	xid = get_xid();

	utf16_path = cअगरs_convert_path_to_utf16(path, cअगरs_sb);
	अगर (!utf16_path) अणु
		rc = -ENOMEM;
		मुक्त_xid(xid);
		वापस ERR_PTR(rc);
	पूर्ण

	oparms.tcon = tcon;
	oparms.desired_access = READ_CONTROL;
	oparms.disposition = खाता_OPEN;
	/*
	 * When querying an ACL, even अगर the file is a symlink we want to खोलो
	 * the source not the target, and so the protocol requires that the
	 * client specअगरy this flag when खोलोing a reparse poपूर्णांक
	 */
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0) | OPEN_REPARSE_POINT;
	oparms.fid = &fid;
	oparms.reconnect = false;

	अगर (info & SACL_SECINFO)
		oparms.desired_access |= SYSTEM_SECURITY;

	rc = SMB2_खोलो(xid, &oparms, utf16_path, &oplock, शून्य, शून्य, शून्य,
		       शून्य);
	kमुक्त(utf16_path);
	अगर (!rc) अणु
		rc = SMB2_query_acl(xid, tlink_tcon(tlink), fid.persistent_fid,
				    fid.अस्थिर_fid, (व्योम **)&pntsd, pacllen,
				    info);
		SMB2_बंद(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid);
	पूर्ण

	cअगरs_put_tlink(tlink);
	मुक्त_xid(xid);

	cअगरs_dbg(FYI, "%s: rc = %d ACL len %d\n", __func__, rc, *pacllen);
	अगर (rc)
		वापस ERR_PTR(rc);
	वापस pntsd;
पूर्ण

अटल पूर्णांक
set_smb2_acl(काष्ठा cअगरs_ntsd *pnntsd, __u32 acllen,
		काष्ठा inode *inode, स्थिर अक्षर *path, पूर्णांक aclflag)
अणु
	u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc, access_flags = 0;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा tcon_link *tlink = cअगरs_sb_tlink(cअगरs_sb);
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;
	__le16 *utf16_path;

	cअगरs_dbg(FYI, "set smb3 acl for path %s\n", path);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);

	tcon = tlink_tcon(tlink);
	xid = get_xid();

	अगर (aclflag & CIFS_ACL_OWNER || aclflag & CIFS_ACL_GROUP)
		access_flags |= WRITE_OWNER;
	अगर (aclflag & CIFS_ACL_SACL)
		access_flags |= SYSTEM_SECURITY;
	अगर (aclflag & CIFS_ACL_DACL)
		access_flags |= WRITE_DAC;

	utf16_path = cअगरs_convert_path_to_utf16(path, cअगरs_sb);
	अगर (!utf16_path) अणु
		rc = -ENOMEM;
		मुक्त_xid(xid);
		वापस rc;
	पूर्ण

	oparms.tcon = tcon;
	oparms.desired_access = access_flags;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.disposition = खाता_OPEN;
	oparms.path = path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = SMB2_खोलो(xid, &oparms, utf16_path, &oplock, शून्य, शून्य,
		       शून्य, शून्य);
	kमुक्त(utf16_path);
	अगर (!rc) अणु
		rc = SMB2_set_acl(xid, tlink_tcon(tlink), fid.persistent_fid,
			    fid.अस्थिर_fid, pnntsd, acllen, aclflag);
		SMB2_बंद(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid);
	पूर्ण

	cअगरs_put_tlink(tlink);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

/* Retrieve an ACL from the server */
अटल काष्ठा cअगरs_ntsd *
get_smb2_acl(काष्ठा cअगरs_sb_info *cअगरs_sb,
	     काष्ठा inode *inode, स्थिर अक्षर *path,
	     u32 *pacllen, u32 info)
अणु
	काष्ठा cअगरs_ntsd *pntsd = शून्य;
	काष्ठा cअगरsFileInfo *खोलो_file = शून्य;

	अगर (inode && !(info & SACL_SECINFO))
		खोलो_file = find_पढ़ोable_file(CIFS_I(inode), true);
	अगर (!खोलो_file || (info & SACL_SECINFO))
		वापस get_smb2_acl_by_path(cअगरs_sb, path, pacllen, info);

	pntsd = get_smb2_acl_by_fid(cअगरs_sb, &खोलो_file->fid, pacllen, info);
	cअगरsFileInfo_put(खोलो_file);
	वापस pntsd;
पूर्ण

अटल दीर्घ smb3_zero_range(काष्ठा file *file, काष्ठा cअगरs_tcon *tcon,
			    loff_t offset, loff_t len, bool keep_size)
अणु
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा inode *inode;
	काष्ठा cअगरsInodeInfo *cअगरsi;
	काष्ठा cअगरsFileInfo *cfile = file->निजी_data;
	काष्ठा file_zero_data_inक्रमmation fsctl_buf;
	दीर्घ rc;
	अचिन्हित पूर्णांक xid;
	__le64 eof;

	xid = get_xid();

	inode = d_inode(cfile->dentry);
	cअगरsi = CIFS_I(inode);

	trace_smb3_zero_enter(xid, cfile->fid.persistent_fid, tcon->tid,
			      ses->Suid, offset, len);

	/*
	 * We zero the range through ioctl, so we need हटाओ the page caches
	 * first, otherwise the data may be inconsistent with the server.
	 */
	truncate_pagecache_range(inode, offset, offset + len - 1);

	/* अगर file not oplocked can't be sure whether asking to extend size */
	अगर (!CIFS_CACHE_READ(cअगरsi))
		अगर (keep_size == false) अणु
			rc = -EOPNOTSUPP;
			trace_smb3_zero_err(xid, cfile->fid.persistent_fid,
				tcon->tid, ses->Suid, offset, len, rc);
			मुक्त_xid(xid);
			वापस rc;
		पूर्ण

	cअगरs_dbg(FYI, "Offset %lld len %lld\n", offset, len);

	fsctl_buf.FileOffset = cpu_to_le64(offset);
	fsctl_buf.BeyondFinalZero = cpu_to_le64(offset + len);

	rc = SMB2_ioctl(xid, tcon, cfile->fid.persistent_fid,
			cfile->fid.अस्थिर_fid, FSCTL_SET_ZERO_DATA, true,
			(अक्षर *)&fsctl_buf,
			माप(काष्ठा file_zero_data_inक्रमmation),
			0, शून्य, शून्य);
	अगर (rc)
		जाओ zero_range_निकास;

	/*
	 * करो we also need to change the size of the file?
	 */
	अगर (keep_size == false && i_size_पढ़ो(inode) < offset + len) अणु
		eof = cpu_to_le64(offset + len);
		rc = SMB2_set_eof(xid, tcon, cfile->fid.persistent_fid,
				  cfile->fid.अस्थिर_fid, cfile->pid, &eof);
	पूर्ण

 zero_range_निकास:
	मुक्त_xid(xid);
	अगर (rc)
		trace_smb3_zero_err(xid, cfile->fid.persistent_fid, tcon->tid,
			      ses->Suid, offset, len, rc);
	अन्यथा
		trace_smb3_zero_करोne(xid, cfile->fid.persistent_fid, tcon->tid,
			      ses->Suid, offset, len);
	वापस rc;
पूर्ण

अटल दीर्घ smb3_punch_hole(काष्ठा file *file, काष्ठा cअगरs_tcon *tcon,
			    loff_t offset, loff_t len)
अणु
	काष्ठा inode *inode;
	काष्ठा cअगरsFileInfo *cfile = file->निजी_data;
	काष्ठा file_zero_data_inक्रमmation fsctl_buf;
	दीर्घ rc;
	अचिन्हित पूर्णांक xid;
	__u8 set_sparse = 1;

	xid = get_xid();

	inode = d_inode(cfile->dentry);

	/* Need to make file sparse, अगर not alपढ़ोy, beक्रमe मुक्तing range. */
	/* Consider adding equivalent क्रम compressed since it could also work */
	अगर (!smb2_set_sparse(xid, tcon, cfile, inode, set_sparse)) अणु
		rc = -EOPNOTSUPP;
		मुक्त_xid(xid);
		वापस rc;
	पूर्ण

	/*
	 * We implement the punch hole through ioctl, so we need हटाओ the page
	 * caches first, otherwise the data may be inconsistent with the server.
	 */
	truncate_pagecache_range(inode, offset, offset + len - 1);

	cअगरs_dbg(FYI, "Offset %lld len %lld\n", offset, len);

	fsctl_buf.FileOffset = cpu_to_le64(offset);
	fsctl_buf.BeyondFinalZero = cpu_to_le64(offset + len);

	rc = SMB2_ioctl(xid, tcon, cfile->fid.persistent_fid,
			cfile->fid.अस्थिर_fid, FSCTL_SET_ZERO_DATA,
			true /* is_fctl */, (अक्षर *)&fsctl_buf,
			माप(काष्ठा file_zero_data_inक्रमmation),
			CIFSMaxBufSize, शून्य, शून्य);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल दीर्घ smb3_simple_falloc(काष्ठा file *file, काष्ठा cअगरs_tcon *tcon,
			    loff_t off, loff_t len, bool keep_size)
अणु
	काष्ठा inode *inode;
	काष्ठा cअगरsInodeInfo *cअगरsi;
	काष्ठा cअगरsFileInfo *cfile = file->निजी_data;
	दीर्घ rc = -EOPNOTSUPP;
	अचिन्हित पूर्णांक xid;
	__le64 eof;

	xid = get_xid();

	inode = d_inode(cfile->dentry);
	cअगरsi = CIFS_I(inode);

	trace_smb3_falloc_enter(xid, cfile->fid.persistent_fid, tcon->tid,
				tcon->ses->Suid, off, len);
	/* अगर file not oplocked can't be sure whether asking to extend size */
	अगर (!CIFS_CACHE_READ(cअगरsi))
		अगर (keep_size == false) अणु
			trace_smb3_falloc_err(xid, cfile->fid.persistent_fid,
				tcon->tid, tcon->ses->Suid, off, len, rc);
			मुक्त_xid(xid);
			वापस rc;
		पूर्ण

	/*
	 * Extending the file
	 */
	अगर ((keep_size == false) && i_size_पढ़ो(inode) < off + len) अणु
		rc = inode_newsize_ok(inode, off + len);
		अगर (rc)
			जाओ out;

		अगर ((cअगरsi->cअगरsAttrs & खाता_ATTRIBUTE_SPARSE_खाता) == 0)
			smb2_set_sparse(xid, tcon, cfile, inode, false);

		eof = cpu_to_le64(off + len);
		rc = SMB2_set_eof(xid, tcon, cfile->fid.persistent_fid,
				  cfile->fid.अस्थिर_fid, cfile->pid, &eof);
		अगर (rc == 0) अणु
			cअगरsi->server_eof = off + len;
			cअगरs_setsize(inode, off + len);
			cअगरs_truncate_page(inode->i_mapping, inode->i_size);
			truncate_setsize(inode, off + len);
		पूर्ण
		जाओ out;
	पूर्ण

	/*
	 * Files are non-sparse by शेष so falloc may be a no-op
	 * Must check अगर file sparse. If not sparse, and since we are not
	 * extending then no need to करो anything since file alपढ़ोy allocated
	 */
	अगर ((cअगरsi->cअगरsAttrs & खाता_ATTRIBUTE_SPARSE_खाता) == 0) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	अगर ((keep_size == true) || (i_size_पढ़ो(inode) >= off + len)) अणु
		/*
		 * Check अगर falloc starts within first few pages of file
		 * and ends within a few pages of the end of file to
		 * ensure that most of file is being क्रमced to be
		 * fallocated now. If so then setting whole file sparse
		 * ie potentially making a few extra pages at the beginning
		 * or end of the file non-sparse via set_sparse is harmless.
		 */
		अगर ((off > 8192) || (off + len + 8192 < i_size_पढ़ो(inode))) अणु
			rc = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
	पूर्ण

	smb2_set_sparse(xid, tcon, cfile, inode, false);
	rc = 0;

out:
	अगर (rc)
		trace_smb3_falloc_err(xid, cfile->fid.persistent_fid, tcon->tid,
				tcon->ses->Suid, off, len, rc);
	अन्यथा
		trace_smb3_falloc_करोne(xid, cfile->fid.persistent_fid, tcon->tid,
				tcon->ses->Suid, off, len);

	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल दीर्घ smb3_collapse_range(काष्ठा file *file, काष्ठा cअगरs_tcon *tcon,
			    loff_t off, loff_t len)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरsFileInfo *cfile = file->निजी_data;
	__le64 eof;

	xid = get_xid();

	अगर (off >= i_size_पढ़ो(file->f_inode) ||
	    off + len >= i_size_पढ़ो(file->f_inode)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	rc = smb2_copychunk_range(xid, cfile, cfile, off + len,
				  i_size_पढ़ो(file->f_inode) - off - len, off);
	अगर (rc < 0)
		जाओ out;

	eof = cpu_to_le64(i_size_पढ़ो(file->f_inode) - len);
	rc = SMB2_set_eof(xid, tcon, cfile->fid.persistent_fid,
			  cfile->fid.अस्थिर_fid, cfile->pid, &eof);
	अगर (rc < 0)
		जाओ out;

	rc = 0;
 out:
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल दीर्घ smb3_insert_range(काष्ठा file *file, काष्ठा cअगरs_tcon *tcon,
			      loff_t off, loff_t len)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरsFileInfo *cfile = file->निजी_data;
	__le64 eof;
	__u64  count;

	xid = get_xid();

	अगर (off >= i_size_पढ़ो(file->f_inode)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	count = i_size_पढ़ो(file->f_inode) - off;
	eof = cpu_to_le64(i_size_पढ़ो(file->f_inode) + len);

	rc = SMB2_set_eof(xid, tcon, cfile->fid.persistent_fid,
			  cfile->fid.अस्थिर_fid, cfile->pid, &eof);
	अगर (rc < 0)
		जाओ out;

	rc = smb2_copychunk_range(xid, cfile, cfile, off, count, off + len);
	अगर (rc < 0)
		जाओ out;

	rc = smb3_zero_range(file, tcon, off, len, 1);
	अगर (rc < 0)
		जाओ out;

	rc = 0;
 out:
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल loff_t smb3_llseek(काष्ठा file *file, काष्ठा cअगरs_tcon *tcon, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा cअगरsFileInfo *wrcfile, *cfile = file->निजी_data;
	काष्ठा cअगरsInodeInfo *cअगरsi;
	काष्ठा inode *inode;
	पूर्णांक rc = 0;
	काष्ठा file_allocated_range_buffer in_data, *out_data = शून्य;
	u32 out_data_len;
	अचिन्हित पूर्णांक xid;

	अगर (whence != SEEK_HOLE && whence != SEEK_DATA)
		वापस generic_file_llseek(file, offset, whence);

	inode = d_inode(cfile->dentry);
	cअगरsi = CIFS_I(inode);

	अगर (offset < 0 || offset >= i_size_पढ़ो(inode))
		वापस -ENXIO;

	xid = get_xid();
	/*
	 * We need to be sure that all dirty pages are written as they
	 * might fill holes on the server.
	 * Note that we also MUST flush any written pages since at least
	 * some servers (Winकरोws2016) will not reflect recent ग_लिखोs in
	 * QUERY_ALLOCATED_RANGES until SMB2_flush is called.
	 */
	wrcfile = find_writable_file(cअगरsi, FIND_WR_ANY);
	अगर (wrcfile) अणु
		filemap_ग_लिखो_and_रुको(inode->i_mapping);
		smb2_flush_file(xid, tcon, &wrcfile->fid);
		cअगरsFileInfo_put(wrcfile);
	पूर्ण

	अगर (!(cअगरsi->cअगरsAttrs & खाता_ATTRIBUTE_SPARSE_खाता)) अणु
		अगर (whence == SEEK_HOLE)
			offset = i_size_पढ़ो(inode);
		जाओ lseek_निकास;
	पूर्ण

	in_data.file_offset = cpu_to_le64(offset);
	in_data.length = cpu_to_le64(i_size_पढ़ो(inode));

	rc = SMB2_ioctl(xid, tcon, cfile->fid.persistent_fid,
			cfile->fid.अस्थिर_fid,
			FSCTL_QUERY_ALLOCATED_RANGES, true,
			(अक्षर *)&in_data, माप(in_data),
			माप(काष्ठा file_allocated_range_buffer),
			(अक्षर **)&out_data, &out_data_len);
	अगर (rc == -E2BIG)
		rc = 0;
	अगर (rc)
		जाओ lseek_निकास;

	अगर (whence == SEEK_HOLE && out_data_len == 0)
		जाओ lseek_निकास;

	अगर (whence == SEEK_DATA && out_data_len == 0) अणु
		rc = -ENXIO;
		जाओ lseek_निकास;
	पूर्ण

	अगर (out_data_len < माप(काष्ठा file_allocated_range_buffer)) अणु
		rc = -EINVAL;
		जाओ lseek_निकास;
	पूर्ण
	अगर (whence == SEEK_DATA) अणु
		offset = le64_to_cpu(out_data->file_offset);
		जाओ lseek_निकास;
	पूर्ण
	अगर (offset < le64_to_cpu(out_data->file_offset))
		जाओ lseek_निकास;

	offset = le64_to_cpu(out_data->file_offset) + le64_to_cpu(out_data->length);

 lseek_निकास:
	मुक्त_xid(xid);
	kमुक्त(out_data);
	अगर (!rc)
		वापस vfs_setpos(file, offset, inode->i_sb->s_maxbytes);
	अन्यथा
		वापस rc;
पूर्ण

अटल पूर्णांक smb3_fiemap(काष्ठा cअगरs_tcon *tcon,
		       काष्ठा cअगरsFileInfo *cfile,
		       काष्ठा fiemap_extent_info *fei, u64 start, u64 len)
अणु
	अचिन्हित पूर्णांक xid;
	काष्ठा file_allocated_range_buffer in_data, *out_data;
	u32 out_data_len;
	पूर्णांक i, num, rc, flags, last_blob;
	u64 next;

	rc = fiemap_prep(d_inode(cfile->dentry), fei, start, &len, 0);
	अगर (rc)
		वापस rc;

	xid = get_xid();
 again:
	in_data.file_offset = cpu_to_le64(start);
	in_data.length = cpu_to_le64(len);

	rc = SMB2_ioctl(xid, tcon, cfile->fid.persistent_fid,
			cfile->fid.अस्थिर_fid,
			FSCTL_QUERY_ALLOCATED_RANGES, true,
			(अक्षर *)&in_data, माप(in_data),
			1024 * माप(काष्ठा file_allocated_range_buffer),
			(अक्षर **)&out_data, &out_data_len);
	अगर (rc == -E2BIG) अणु
		last_blob = 0;
		rc = 0;
	पूर्ण अन्यथा
		last_blob = 1;
	अगर (rc)
		जाओ out;

	अगर (out_data_len && out_data_len < माप(काष्ठा file_allocated_range_buffer)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (out_data_len % माप(काष्ठा file_allocated_range_buffer)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	num = out_data_len / माप(काष्ठा file_allocated_range_buffer);
	क्रम (i = 0; i < num; i++) अणु
		flags = 0;
		अगर (i == num - 1 && last_blob)
			flags |= FIEMAP_EXTENT_LAST;

		rc = fiemap_fill_next_extent(fei,
				le64_to_cpu(out_data[i].file_offset),
				le64_to_cpu(out_data[i].file_offset),
				le64_to_cpu(out_data[i].length),
				flags);
		अगर (rc < 0)
			जाओ out;
		अगर (rc == 1) अणु
			rc = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!last_blob) अणु
		next = le64_to_cpu(out_data[num - 1].file_offset) +
		  le64_to_cpu(out_data[num - 1].length);
		len = len - (next - start);
		start = next;
		जाओ again;
	पूर्ण

 out:
	मुक्त_xid(xid);
	kमुक्त(out_data);
	वापस rc;
पूर्ण

अटल दीर्घ smb3_fallocate(काष्ठा file *file, काष्ठा cअगरs_tcon *tcon, पूर्णांक mode,
			   loff_t off, loff_t len)
अणु
	/* KEEP_SIZE alपढ़ोy checked क्रम by करो_fallocate */
	अगर (mode & FALLOC_FL_PUNCH_HOLE)
		वापस smb3_punch_hole(file, tcon, off, len);
	अन्यथा अगर (mode & FALLOC_FL_ZERO_RANGE) अणु
		अगर (mode & FALLOC_FL_KEEP_SIZE)
			वापस smb3_zero_range(file, tcon, off, len, true);
		वापस smb3_zero_range(file, tcon, off, len, false);
	पूर्ण अन्यथा अगर (mode == FALLOC_FL_KEEP_SIZE)
		वापस smb3_simple_falloc(file, tcon, off, len, true);
	अन्यथा अगर (mode == FALLOC_FL_COLLAPSE_RANGE)
		वापस smb3_collapse_range(file, tcon, off, len);
	अन्यथा अगर (mode == FALLOC_FL_INSERT_RANGE)
		वापस smb3_insert_range(file, tcon, off, len);
	अन्यथा अगर (mode == 0)
		वापस smb3_simple_falloc(file, tcon, off, len, false);

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम
smb2_करोwngrade_oplock(काष्ठा TCP_Server_Info *server,
		      काष्ठा cअगरsInodeInfo *cinode, __u32 oplock,
		      अचिन्हित पूर्णांक epoch, bool *purge_cache)
अणु
	server->ops->set_oplock_level(cinode, oplock, 0, शून्य);
पूर्ण

अटल व्योम
smb21_set_oplock_level(काष्ठा cअगरsInodeInfo *cinode, __u32 oplock,
		       अचिन्हित पूर्णांक epoch, bool *purge_cache);

अटल व्योम
smb3_करोwngrade_oplock(काष्ठा TCP_Server_Info *server,
		       काष्ठा cअगरsInodeInfo *cinode, __u32 oplock,
		       अचिन्हित पूर्णांक epoch, bool *purge_cache)
अणु
	अचिन्हित पूर्णांक old_state = cinode->oplock;
	अचिन्हित पूर्णांक old_epoch = cinode->epoch;
	अचिन्हित पूर्णांक new_state;

	अगर (epoch > old_epoch) अणु
		smb21_set_oplock_level(cinode, oplock, 0, शून्य);
		cinode->epoch = epoch;
	पूर्ण

	new_state = cinode->oplock;
	*purge_cache = false;

	अगर ((old_state & CIFS_CACHE_READ_FLG) != 0 &&
	    (new_state & CIFS_CACHE_READ_FLG) == 0)
		*purge_cache = true;
	अन्यथा अगर (old_state == new_state && (epoch - old_epoch > 1))
		*purge_cache = true;
पूर्ण

अटल व्योम
smb2_set_oplock_level(काष्ठा cअगरsInodeInfo *cinode, __u32 oplock,
		      अचिन्हित पूर्णांक epoch, bool *purge_cache)
अणु
	oplock &= 0xFF;
	cinode->lease_granted = false;
	अगर (oplock == SMB2_OPLOCK_LEVEL_NOCHANGE)
		वापस;
	अगर (oplock == SMB2_OPLOCK_LEVEL_BATCH) अणु
		cinode->oplock = CIFS_CACHE_RHW_FLG;
		cअगरs_dbg(FYI, "Batch Oplock granted on inode %p\n",
			 &cinode->vfs_inode);
	पूर्ण अन्यथा अगर (oplock == SMB2_OPLOCK_LEVEL_EXCLUSIVE) अणु
		cinode->oplock = CIFS_CACHE_RW_FLG;
		cअगरs_dbg(FYI, "Exclusive Oplock granted on inode %p\n",
			 &cinode->vfs_inode);
	पूर्ण अन्यथा अगर (oplock == SMB2_OPLOCK_LEVEL_II) अणु
		cinode->oplock = CIFS_CACHE_READ_FLG;
		cअगरs_dbg(FYI, "Level II Oplock granted on inode %p\n",
			 &cinode->vfs_inode);
	पूर्ण अन्यथा
		cinode->oplock = 0;
पूर्ण

अटल व्योम
smb21_set_oplock_level(काष्ठा cअगरsInodeInfo *cinode, __u32 oplock,
		       अचिन्हित पूर्णांक epoch, bool *purge_cache)
अणु
	अक्षर message[5] = अणु0पूर्ण;
	अचिन्हित पूर्णांक new_oplock = 0;

	oplock &= 0xFF;
	cinode->lease_granted = true;
	अगर (oplock == SMB2_OPLOCK_LEVEL_NOCHANGE)
		वापस;

	/* Check अगर the server granted an oplock rather than a lease */
	अगर (oplock & SMB2_OPLOCK_LEVEL_EXCLUSIVE)
		वापस smb2_set_oplock_level(cinode, oplock, epoch,
					     purge_cache);

	अगर (oplock & SMB2_LEASE_READ_CACHING_HE) अणु
		new_oplock |= CIFS_CACHE_READ_FLG;
		म_जोड़ो(message, "R");
	पूर्ण
	अगर (oplock & SMB2_LEASE_HANDLE_CACHING_HE) अणु
		new_oplock |= CIFS_CACHE_HANDLE_FLG;
		म_जोड़ो(message, "H");
	पूर्ण
	अगर (oplock & SMB2_LEASE_WRITE_CACHING_HE) अणु
		new_oplock |= CIFS_CACHE_WRITE_FLG;
		म_जोड़ो(message, "W");
	पूर्ण
	अगर (!new_oplock)
		म_नकलन(message, "None", माप(message));

	cinode->oplock = new_oplock;
	cअगरs_dbg(FYI, "%s Lease granted on inode %p\n", message,
		 &cinode->vfs_inode);
पूर्ण

अटल व्योम
smb3_set_oplock_level(काष्ठा cअगरsInodeInfo *cinode, __u32 oplock,
		      अचिन्हित पूर्णांक epoch, bool *purge_cache)
अणु
	अचिन्हित पूर्णांक old_oplock = cinode->oplock;

	smb21_set_oplock_level(cinode, oplock, epoch, purge_cache);

	अगर (purge_cache) अणु
		*purge_cache = false;
		अगर (old_oplock == CIFS_CACHE_READ_FLG) अणु
			अगर (cinode->oplock == CIFS_CACHE_READ_FLG &&
			    (epoch - cinode->epoch > 0))
				*purge_cache = true;
			अन्यथा अगर (cinode->oplock == CIFS_CACHE_RH_FLG &&
				 (epoch - cinode->epoch > 1))
				*purge_cache = true;
			अन्यथा अगर (cinode->oplock == CIFS_CACHE_RHW_FLG &&
				 (epoch - cinode->epoch > 1))
				*purge_cache = true;
			अन्यथा अगर (cinode->oplock == 0 &&
				 (epoch - cinode->epoch > 0))
				*purge_cache = true;
		पूर्ण अन्यथा अगर (old_oplock == CIFS_CACHE_RH_FLG) अणु
			अगर (cinode->oplock == CIFS_CACHE_RH_FLG &&
			    (epoch - cinode->epoch > 0))
				*purge_cache = true;
			अन्यथा अगर (cinode->oplock == CIFS_CACHE_RHW_FLG &&
				 (epoch - cinode->epoch > 1))
				*purge_cache = true;
		पूर्ण
		cinode->epoch = epoch;
	पूर्ण
पूर्ण

अटल bool
smb2_is_पढ़ो_op(__u32 oplock)
अणु
	वापस oplock == SMB2_OPLOCK_LEVEL_II;
पूर्ण

अटल bool
smb21_is_पढ़ो_op(__u32 oplock)
अणु
	वापस (oplock & SMB2_LEASE_READ_CACHING_HE) &&
	       !(oplock & SMB2_LEASE_WRITE_CACHING_HE);
पूर्ण

अटल __le32
map_oplock_to_lease(u8 oplock)
अणु
	अगर (oplock == SMB2_OPLOCK_LEVEL_EXCLUSIVE)
		वापस SMB2_LEASE_WRITE_CACHING | SMB2_LEASE_READ_CACHING;
	अन्यथा अगर (oplock == SMB2_OPLOCK_LEVEL_II)
		वापस SMB2_LEASE_READ_CACHING;
	अन्यथा अगर (oplock == SMB2_OPLOCK_LEVEL_BATCH)
		वापस SMB2_LEASE_HANDLE_CACHING | SMB2_LEASE_READ_CACHING |
		       SMB2_LEASE_WRITE_CACHING;
	वापस 0;
पूर्ण

अटल अक्षर *
smb2_create_lease_buf(u8 *lease_key, u8 oplock)
अणु
	काष्ठा create_lease *buf;

	buf = kzalloc(माप(काष्ठा create_lease), GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	स_नकल(&buf->lcontext.LeaseKey, lease_key, SMB2_LEASE_KEY_SIZE);
	buf->lcontext.LeaseState = map_oplock_to_lease(oplock);

	buf->ccontext.DataOffset = cpu_to_le16(दुरत्व
					(काष्ठा create_lease, lcontext));
	buf->ccontext.DataLength = cpu_to_le32(माप(काष्ठा lease_context));
	buf->ccontext.NameOffset = cpu_to_le16(दुरत्व
				(काष्ठा create_lease, Name));
	buf->ccontext.NameLength = cpu_to_le16(4);
	/* SMB2_CREATE_REQUEST_LEASE is "RqLs" */
	buf->Name[0] = 'R';
	buf->Name[1] = 'q';
	buf->Name[2] = 'L';
	buf->Name[3] = 's';
	वापस (अक्षर *)buf;
पूर्ण

अटल अक्षर *
smb3_create_lease_buf(u8 *lease_key, u8 oplock)
अणु
	काष्ठा create_lease_v2 *buf;

	buf = kzalloc(माप(काष्ठा create_lease_v2), GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	स_नकल(&buf->lcontext.LeaseKey, lease_key, SMB2_LEASE_KEY_SIZE);
	buf->lcontext.LeaseState = map_oplock_to_lease(oplock);

	buf->ccontext.DataOffset = cpu_to_le16(दुरत्व
					(काष्ठा create_lease_v2, lcontext));
	buf->ccontext.DataLength = cpu_to_le32(माप(काष्ठा lease_context_v2));
	buf->ccontext.NameOffset = cpu_to_le16(दुरत्व
				(काष्ठा create_lease_v2, Name));
	buf->ccontext.NameLength = cpu_to_le16(4);
	/* SMB2_CREATE_REQUEST_LEASE is "RqLs" */
	buf->Name[0] = 'R';
	buf->Name[1] = 'q';
	buf->Name[2] = 'L';
	buf->Name[3] = 's';
	वापस (अक्षर *)buf;
पूर्ण

अटल __u8
smb2_parse_lease_buf(व्योम *buf, अचिन्हित पूर्णांक *epoch, अक्षर *lease_key)
अणु
	काष्ठा create_lease *lc = (काष्ठा create_lease *)buf;

	*epoch = 0; /* not used */
	अगर (lc->lcontext.LeaseFlags & SMB2_LEASE_FLAG_BREAK_IN_PROGRESS)
		वापस SMB2_OPLOCK_LEVEL_NOCHANGE;
	वापस le32_to_cpu(lc->lcontext.LeaseState);
पूर्ण

अटल __u8
smb3_parse_lease_buf(व्योम *buf, अचिन्हित पूर्णांक *epoch, अक्षर *lease_key)
अणु
	काष्ठा create_lease_v2 *lc = (काष्ठा create_lease_v2 *)buf;

	*epoch = le16_to_cpu(lc->lcontext.Epoch);
	अगर (lc->lcontext.LeaseFlags & SMB2_LEASE_FLAG_BREAK_IN_PROGRESS)
		वापस SMB2_OPLOCK_LEVEL_NOCHANGE;
	अगर (lease_key)
		स_नकल(lease_key, &lc->lcontext.LeaseKey, SMB2_LEASE_KEY_SIZE);
	वापस le32_to_cpu(lc->lcontext.LeaseState);
पूर्ण

अटल अचिन्हित पूर्णांक
smb2_wp_retry_size(काष्ठा inode *inode)
अणु
	वापस min_t(अचिन्हित पूर्णांक, CIFS_SB(inode->i_sb)->ctx->wsize,
		     SMB2_MAX_BUFFER_SIZE);
पूर्ण

अटल bool
smb2_dir_needs_बंद(काष्ठा cअगरsFileInfo *cfile)
अणु
	वापस !cfile->invalidHandle;
पूर्ण

अटल व्योम
fill_transक्रमm_hdr(काष्ठा smb2_transक्रमm_hdr *tr_hdr, अचिन्हित पूर्णांक orig_len,
		   काष्ठा smb_rqst *old_rq, __le16 cipher_type)
अणु
	काष्ठा smb2_sync_hdr *shdr =
			(काष्ठा smb2_sync_hdr *)old_rq->rq_iov[0].iov_base;

	स_रखो(tr_hdr, 0, माप(काष्ठा smb2_transक्रमm_hdr));
	tr_hdr->ProtocolId = SMB2_TRANSFORM_PROTO_NUM;
	tr_hdr->OriginalMessageSize = cpu_to_le32(orig_len);
	tr_hdr->Flags = cpu_to_le16(0x01);
	अगर ((cipher_type == SMB2_ENCRYPTION_AES128_GCM) ||
	    (cipher_type == SMB2_ENCRYPTION_AES256_GCM))
		get_अक्रमom_bytes(&tr_hdr->Nonce, SMB3_AES_GCM_NONCE);
	अन्यथा
		get_अक्रमom_bytes(&tr_hdr->Nonce, SMB3_AES_CCM_NONCE);
	स_नकल(&tr_hdr->SessionId, &shdr->SessionId, 8);
पूर्ण

/* We can not use the normal sg_set_buf() as we will someबार pass a
 * stack object as buf.
 */
अटल अंतरभूत व्योम smb2_sg_set_buf(काष्ठा scatterlist *sg, स्थिर व्योम *buf,
				   अचिन्हित पूर्णांक buflen)
अणु
	व्योम *addr;
	/*
	 * VMAP_STACK (at least) माला_दो stack पूर्णांकo the vदो_स्मृति address space
	 */
	अगर (is_vदो_स्मृति_addr(buf))
		addr = vदो_स्मृति_to_page(buf);
	अन्यथा
		addr = virt_to_page(buf);
	sg_set_page(sg, addr, buflen, offset_in_page(buf));
पूर्ण

/* Assumes the first rqst has a transक्रमm header as the first iov.
 * I.e.
 * rqst[0].rq_iov[0]  is transक्रमm header
 * rqst[0].rq_iov[1+] data to be encrypted/decrypted
 * rqst[1+].rq_iov[0+] data to be encrypted/decrypted
 */
अटल काष्ठा scatterlist *
init_sg(पूर्णांक num_rqst, काष्ठा smb_rqst *rqst, u8 *sign)
अणु
	अचिन्हित पूर्णांक sg_len;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक j;
	अचिन्हित पूर्णांक idx = 0;
	पूर्णांक skip;

	sg_len = 1;
	क्रम (i = 0; i < num_rqst; i++)
		sg_len += rqst[i].rq_nvec + rqst[i].rq_npages;

	sg = kदो_स्मृति_array(sg_len, माप(काष्ठा scatterlist), GFP_KERNEL);
	अगर (!sg)
		वापस शून्य;

	sg_init_table(sg, sg_len);
	क्रम (i = 0; i < num_rqst; i++) अणु
		क्रम (j = 0; j < rqst[i].rq_nvec; j++) अणु
			/*
			 * The first rqst has a transक्रमm header where the
			 * first 20 bytes are not part of the encrypted blob
			 */
			skip = (i == 0) && (j == 0) ? 20 : 0;
			smb2_sg_set_buf(&sg[idx++],
					rqst[i].rq_iov[j].iov_base + skip,
					rqst[i].rq_iov[j].iov_len - skip);
			पूर्ण

		क्रम (j = 0; j < rqst[i].rq_npages; j++) अणु
			अचिन्हित पूर्णांक len, offset;

			rqst_page_get_length(&rqst[i], j, &len, &offset);
			sg_set_page(&sg[idx++], rqst[i].rq_pages[j], len, offset);
		पूर्ण
	पूर्ण
	smb2_sg_set_buf(&sg[idx], sign, SMB2_SIGNATURE_SIZE);
	वापस sg;
पूर्ण

अटल पूर्णांक
smb2_get_enc_key(काष्ठा TCP_Server_Info *server, __u64 ses_id, पूर्णांक enc, u8 *key)
अणु
	काष्ठा cअगरs_ses *ses;
	u8 *ses_enc_key;

	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each_entry(server, &cअगरs_tcp_ses_list, tcp_ses_list) अणु
		list_क्रम_each_entry(ses, &server->smb_ses_list, smb_ses_list) अणु
			अगर (ses->Suid == ses_id) अणु
				ses_enc_key = enc ? ses->smb3encryptionkey :
					ses->smb3decryptionkey;
				स_नकल(key, ses_enc_key, SMB3_ENC_DEC_KEY_SIZE);
				spin_unlock(&cअगरs_tcp_ses_lock);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&cअगरs_tcp_ses_lock);

	वापस -EAGAIN;
पूर्ण
/*
 * Encrypt or decrypt @rqst message. @rqst[0] has the following क्रमmat:
 * iov[0]   - transक्रमm header (associate data),
 * iov[1-N] - SMB2 header and pages - data to encrypt.
 * On success वापस encrypted data in iov[1-N] and pages, leave iov[0]
 * untouched.
 */
अटल पूर्णांक
crypt_message(काष्ठा TCP_Server_Info *server, पूर्णांक num_rqst,
	      काष्ठा smb_rqst *rqst, पूर्णांक enc)
अणु
	काष्ठा smb2_transक्रमm_hdr *tr_hdr =
		(काष्ठा smb2_transक्रमm_hdr *)rqst[0].rq_iov[0].iov_base;
	अचिन्हित पूर्णांक assoc_data_len = माप(काष्ठा smb2_transक्रमm_hdr) - 20;
	पूर्णांक rc = 0;
	काष्ठा scatterlist *sg;
	u8 sign[SMB2_SIGNATURE_SIZE] = अणुपूर्ण;
	u8 key[SMB3_ENC_DEC_KEY_SIZE];
	काष्ठा aead_request *req;
	अक्षर *iv;
	अचिन्हित पूर्णांक iv_len;
	DECLARE_CRYPTO_WAIT(रुको);
	काष्ठा crypto_aead *tfm;
	अचिन्हित पूर्णांक crypt_len = le32_to_cpu(tr_hdr->OriginalMessageSize);

	rc = smb2_get_enc_key(server, tr_hdr->SessionId, enc, key);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Could not get %scryption key\n", __func__,
			 enc ? "en" : "de");
		वापस rc;
	पूर्ण

	rc = smb3_crypto_aead_allocate(server);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: crypto alloc failed\n", __func__);
		वापस rc;
	पूर्ण

	tfm = enc ? server->secmech.ccmaesencrypt :
						server->secmech.ccmaesdecrypt;

	अगर ((server->cipher_type == SMB2_ENCRYPTION_AES256_CCM) ||
		(server->cipher_type == SMB2_ENCRYPTION_AES256_GCM))
		rc = crypto_aead_setkey(tfm, key, SMB3_GCM256_CRYPTKEY_SIZE);
	अन्यथा
		rc = crypto_aead_setkey(tfm, key, SMB3_GCM128_CRYPTKEY_SIZE);

	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Failed to set aead key %d\n", __func__, rc);
		वापस rc;
	पूर्ण

	rc = crypto_aead_setauthsize(tfm, SMB2_SIGNATURE_SIZE);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Failed to set authsize %d\n", __func__, rc);
		वापस rc;
	पूर्ण

	req = aead_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		cअगरs_server_dbg(VFS, "%s: Failed to alloc aead request\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	अगर (!enc) अणु
		स_नकल(sign, &tr_hdr->Signature, SMB2_SIGNATURE_SIZE);
		crypt_len += SMB2_SIGNATURE_SIZE;
	पूर्ण

	sg = init_sg(num_rqst, rqst, sign);
	अगर (!sg) अणु
		cअगरs_server_dbg(VFS, "%s: Failed to init sg\n", __func__);
		rc = -ENOMEM;
		जाओ मुक्त_req;
	पूर्ण

	iv_len = crypto_aead_ivsize(tfm);
	iv = kzalloc(iv_len, GFP_KERNEL);
	अगर (!iv) अणु
		cअगरs_server_dbg(VFS, "%s: Failed to alloc iv\n", __func__);
		rc = -ENOMEM;
		जाओ मुक्त_sg;
	पूर्ण

	अगर ((server->cipher_type == SMB2_ENCRYPTION_AES128_GCM) ||
	    (server->cipher_type == SMB2_ENCRYPTION_AES256_GCM))
		स_नकल(iv, (अक्षर *)tr_hdr->Nonce, SMB3_AES_GCM_NONCE);
	अन्यथा अणु
		iv[0] = 3;
		स_नकल(iv + 1, (अक्षर *)tr_hdr->Nonce, SMB3_AES_CCM_NONCE);
	पूर्ण

	aead_request_set_crypt(req, sg, sg, crypt_len, iv);
	aead_request_set_ad(req, assoc_data_len);

	aead_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				  crypto_req_करोne, &रुको);

	rc = crypto_रुको_req(enc ? crypto_aead_encrypt(req)
				: crypto_aead_decrypt(req), &रुको);

	अगर (!rc && enc)
		स_नकल(&tr_hdr->Signature, sign, SMB2_SIGNATURE_SIZE);

	kमुक्त(iv);
मुक्त_sg:
	kमुक्त(sg);
मुक्त_req:
	kमुक्त(req);
	वापस rc;
पूर्ण

व्योम
smb3_मुक्त_compound_rqst(पूर्णांक num_rqst, काष्ठा smb_rqst *rqst)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < num_rqst; i++) अणु
		अगर (rqst[i].rq_pages) अणु
			क्रम (j = rqst[i].rq_npages - 1; j >= 0; j--)
				put_page(rqst[i].rq_pages[j]);
			kमुक्त(rqst[i].rq_pages);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This function will initialize new_rq and encrypt the content.
 * The first entry, new_rq[0], only contains a single iov which contains
 * a smb2_transक्रमm_hdr and is pre-allocated by the caller.
 * This function then populates new_rq[1+] with the content from olq_rq[0+].
 *
 * The end result is an array of smb_rqst काष्ठाures where the first काष्ठाure
 * only contains a single iov क्रम the transक्रमm header which we then can pass
 * to crypt_message().
 *
 * new_rq[0].rq_iov[0] :  smb2_transक्रमm_hdr pre-allocated by the caller
 * new_rq[1+].rq_iov[*] == old_rq[0+].rq_iov[*] : SMB2/3 requests
 */
अटल पूर्णांक
smb3_init_transक्रमm_rq(काष्ठा TCP_Server_Info *server, पूर्णांक num_rqst,
		       काष्ठा smb_rqst *new_rq, काष्ठा smb_rqst *old_rq)
अणु
	काष्ठा page **pages;
	काष्ठा smb2_transक्रमm_hdr *tr_hdr = new_rq[0].rq_iov[0].iov_base;
	अचिन्हित पूर्णांक npages;
	अचिन्हित पूर्णांक orig_len = 0;
	पूर्णांक i, j;
	पूर्णांक rc = -ENOMEM;

	क्रम (i = 1; i < num_rqst; i++) अणु
		npages = old_rq[i - 1].rq_npages;
		pages = kदो_स्मृति_array(npages, माप(काष्ठा page *),
				      GFP_KERNEL);
		अगर (!pages)
			जाओ err_मुक्त;

		new_rq[i].rq_pages = pages;
		new_rq[i].rq_npages = npages;
		new_rq[i].rq_offset = old_rq[i - 1].rq_offset;
		new_rq[i].rq_pagesz = old_rq[i - 1].rq_pagesz;
		new_rq[i].rq_tailsz = old_rq[i - 1].rq_tailsz;
		new_rq[i].rq_iov = old_rq[i - 1].rq_iov;
		new_rq[i].rq_nvec = old_rq[i - 1].rq_nvec;

		orig_len += smb_rqst_len(server, &old_rq[i - 1]);

		क्रम (j = 0; j < npages; j++) अणु
			pages[j] = alloc_page(GFP_KERNEL|__GFP_HIGHMEM);
			अगर (!pages[j])
				जाओ err_मुक्त;
		पूर्ण

		/* copy pages क्रमm the old */
		क्रम (j = 0; j < npages; j++) अणु
			अक्षर *dst, *src;
			अचिन्हित पूर्णांक offset, len;

			rqst_page_get_length(&new_rq[i], j, &len, &offset);

			dst = (अक्षर *) kmap(new_rq[i].rq_pages[j]) + offset;
			src = (अक्षर *) kmap(old_rq[i - 1].rq_pages[j]) + offset;

			स_नकल(dst, src, len);
			kunmap(new_rq[i].rq_pages[j]);
			kunmap(old_rq[i - 1].rq_pages[j]);
		पूर्ण
	पूर्ण

	/* fill the 1st iov with a transक्रमm header */
	fill_transक्रमm_hdr(tr_hdr, orig_len, old_rq, server->cipher_type);

	rc = crypt_message(server, num_rqst, new_rq, 1);
	cअगरs_dbg(FYI, "Encrypt message returned %d\n", rc);
	अगर (rc)
		जाओ err_मुक्त;

	वापस rc;

err_मुक्त:
	smb3_मुक्त_compound_rqst(num_rqst - 1, &new_rq[1]);
	वापस rc;
पूर्ण

अटल पूर्णांक
smb3_is_transक्रमm_hdr(व्योम *buf)
अणु
	काष्ठा smb2_transक्रमm_hdr *trhdr = buf;

	वापस trhdr->ProtocolId == SMB2_TRANSFORM_PROTO_NUM;
पूर्ण

अटल पूर्णांक
decrypt_raw_data(काष्ठा TCP_Server_Info *server, अक्षर *buf,
		 अचिन्हित पूर्णांक buf_data_size, काष्ठा page **pages,
		 अचिन्हित पूर्णांक npages, अचिन्हित पूर्णांक page_data_size,
		 bool is_offloaded)
अणु
	काष्ठा kvec iov[2];
	काष्ठा smb_rqst rqst = अणुशून्यपूर्ण;
	पूर्णांक rc;

	iov[0].iov_base = buf;
	iov[0].iov_len = माप(काष्ठा smb2_transक्रमm_hdr);
	iov[1].iov_base = buf + माप(काष्ठा smb2_transक्रमm_hdr);
	iov[1].iov_len = buf_data_size;

	rqst.rq_iov = iov;
	rqst.rq_nvec = 2;
	rqst.rq_pages = pages;
	rqst.rq_npages = npages;
	rqst.rq_pagesz = PAGE_SIZE;
	rqst.rq_tailsz = (page_data_size % PAGE_SIZE) ? : PAGE_SIZE;

	rc = crypt_message(server, 1, &rqst, 0);
	cअगरs_dbg(FYI, "Decrypt message returned %d\n", rc);

	अगर (rc)
		वापस rc;

	स_हटाओ(buf, iov[1].iov_base, buf_data_size);

	अगर (!is_offloaded)
		server->total_पढ़ो = buf_data_size + page_data_size;

	वापस rc;
पूर्ण

अटल पूर्णांक
पढ़ो_data_पूर्णांकo_pages(काष्ठा TCP_Server_Info *server, काष्ठा page **pages,
		     अचिन्हित पूर्णांक npages, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;
	पूर्णांक length;

	क्रम (i = 0; i < npages; i++) अणु
		काष्ठा page *page = pages[i];
		माप_प्रकार n;

		n = len;
		अगर (len >= PAGE_SIZE) अणु
			/* enough data to fill the page */
			n = PAGE_SIZE;
			len -= n;
		पूर्ण अन्यथा अणु
			zero_user(page, len, PAGE_SIZE - len);
			len = 0;
		पूर्ण
		length = cअगरs_पढ़ो_page_from_socket(server, page, 0, n);
		अगर (length < 0)
			वापस length;
		server->total_पढ़ो += length;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
init_पढ़ो_bvec(काष्ठा page **pages, अचिन्हित पूर्णांक npages, अचिन्हित पूर्णांक data_size,
	       अचिन्हित पूर्णांक cur_off, काष्ठा bio_vec **page_vec)
अणु
	काष्ठा bio_vec *bvec;
	पूर्णांक i;

	bvec = kसुस्मृति(npages, माप(काष्ठा bio_vec), GFP_KERNEL);
	अगर (!bvec)
		वापस -ENOMEM;

	क्रम (i = 0; i < npages; i++) अणु
		bvec[i].bv_page = pages[i];
		bvec[i].bv_offset = (i == 0) ? cur_off : 0;
		bvec[i].bv_len = min_t(अचिन्हित पूर्णांक, PAGE_SIZE, data_size);
		data_size -= bvec[i].bv_len;
	पूर्ण

	अगर (data_size != 0) अणु
		cअगरs_dbg(VFS, "%s: something went wrong\n", __func__);
		kमुक्त(bvec);
		वापस -EIO;
	पूर्ण

	*page_vec = bvec;
	वापस 0;
पूर्ण

अटल पूर्णांक
handle_पढ़ो_data(काष्ठा TCP_Server_Info *server, काष्ठा mid_q_entry *mid,
		 अक्षर *buf, अचिन्हित पूर्णांक buf_len, काष्ठा page **pages,
		 अचिन्हित पूर्णांक npages, अचिन्हित पूर्णांक page_data_size,
		 bool is_offloaded)
अणु
	अचिन्हित पूर्णांक data_offset;
	अचिन्हित पूर्णांक data_len;
	अचिन्हित पूर्णांक cur_off;
	अचिन्हित पूर्णांक cur_page_idx;
	अचिन्हित पूर्णांक pad_len;
	काष्ठा cअगरs_पढ़ोdata *rdata = mid->callback_data;
	काष्ठा smb2_sync_hdr *shdr = (काष्ठा smb2_sync_hdr *)buf;
	काष्ठा bio_vec *bvec = शून्य;
	काष्ठा iov_iter iter;
	काष्ठा kvec iov;
	पूर्णांक length;
	bool use_rdma_mr = false;

	अगर (shdr->Command != SMB2_READ) अणु
		cअगरs_server_dbg(VFS, "only big read responses are supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (server->ops->is_session_expired &&
	    server->ops->is_session_expired(buf)) अणु
		अगर (!is_offloaded)
			cअगरs_reconnect(server);
		वापस -1;
	पूर्ण

	अगर (server->ops->is_status_pending &&
			server->ops->is_status_pending(buf, server))
		वापस -1;

	/* set up first two iov to get credits */
	rdata->iov[0].iov_base = buf;
	rdata->iov[0].iov_len = 0;
	rdata->iov[1].iov_base = buf;
	rdata->iov[1].iov_len =
		min_t(अचिन्हित पूर्णांक, buf_len, server->vals->पढ़ो_rsp_size);
	cअगरs_dbg(FYI, "0: iov_base=%p iov_len=%zu\n",
		 rdata->iov[0].iov_base, rdata->iov[0].iov_len);
	cअगरs_dbg(FYI, "1: iov_base=%p iov_len=%zu\n",
		 rdata->iov[1].iov_base, rdata->iov[1].iov_len);

	rdata->result = server->ops->map_error(buf, true);
	अगर (rdata->result != 0) अणु
		cअगरs_dbg(FYI, "%s: server returned error %d\n",
			 __func__, rdata->result);
		/* normal error on पढ़ो response */
		अगर (is_offloaded)
			mid->mid_state = MID_RESPONSE_RECEIVED;
		अन्यथा
			dequeue_mid(mid, false);
		वापस 0;
	पूर्ण

	data_offset = server->ops->पढ़ो_data_offset(buf);
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	use_rdma_mr = rdata->mr;
#पूर्ण_अगर
	data_len = server->ops->पढ़ो_data_length(buf, use_rdma_mr);

	अगर (data_offset < server->vals->पढ़ो_rsp_size) अणु
		/*
		 * win2k8 someबार sends an offset of 0 when the पढ़ो
		 * is beyond the खातापूर्ण. Treat it as अगर the data starts just after
		 * the header.
		 */
		cअगरs_dbg(FYI, "%s: data offset (%u) inside read response header\n",
			 __func__, data_offset);
		data_offset = server->vals->पढ़ो_rsp_size;
	पूर्ण अन्यथा अगर (data_offset > MAX_CIFS_SMALL_BUFFER_SIZE) अणु
		/* data_offset is beyond the end of smallbuf */
		cअगरs_dbg(FYI, "%s: data offset (%u) beyond end of smallbuf\n",
			 __func__, data_offset);
		rdata->result = -EIO;
		अगर (is_offloaded)
			mid->mid_state = MID_RESPONSE_MALFORMED;
		अन्यथा
			dequeue_mid(mid, rdata->result);
		वापस 0;
	पूर्ण

	pad_len = data_offset - server->vals->पढ़ो_rsp_size;

	अगर (buf_len <= data_offset) अणु
		/* पढ़ो response payload is in pages */
		cur_page_idx = pad_len / PAGE_SIZE;
		cur_off = pad_len % PAGE_SIZE;

		अगर (cur_page_idx != 0) अणु
			/* data offset is beyond the 1st page of response */
			cअगरs_dbg(FYI, "%s: data offset (%u) beyond 1st page of response\n",
				 __func__, data_offset);
			rdata->result = -EIO;
			अगर (is_offloaded)
				mid->mid_state = MID_RESPONSE_MALFORMED;
			अन्यथा
				dequeue_mid(mid, rdata->result);
			वापस 0;
		पूर्ण

		अगर (data_len > page_data_size - pad_len) अणु
			/* data_len is corrupt -- discard frame */
			rdata->result = -EIO;
			अगर (is_offloaded)
				mid->mid_state = MID_RESPONSE_MALFORMED;
			अन्यथा
				dequeue_mid(mid, rdata->result);
			वापस 0;
		पूर्ण

		rdata->result = init_पढ़ो_bvec(pages, npages, page_data_size,
					       cur_off, &bvec);
		अगर (rdata->result != 0) अणु
			अगर (is_offloaded)
				mid->mid_state = MID_RESPONSE_MALFORMED;
			अन्यथा
				dequeue_mid(mid, rdata->result);
			वापस 0;
		पूर्ण

		iov_iter_bvec(&iter, WRITE, bvec, npages, data_len);
	पूर्ण अन्यथा अगर (buf_len >= data_offset + data_len) अणु
		/* पढ़ो response payload is in buf */
		WARN_ONCE(npages > 0, "read data can be either in buf or in pages");
		iov.iov_base = buf + data_offset;
		iov.iov_len = data_len;
		iov_iter_kvec(&iter, WRITE, &iov, 1, data_len);
	पूर्ण अन्यथा अणु
		/* पढ़ो response payload cannot be in both buf and pages */
		WARN_ONCE(1, "buf can not contain only a part of read data");
		rdata->result = -EIO;
		अगर (is_offloaded)
			mid->mid_state = MID_RESPONSE_MALFORMED;
		अन्यथा
			dequeue_mid(mid, rdata->result);
		वापस 0;
	पूर्ण

	length = rdata->copy_पूर्णांकo_pages(server, rdata, &iter);

	kमुक्त(bvec);

	अगर (length < 0)
		वापस length;

	अगर (is_offloaded)
		mid->mid_state = MID_RESPONSE_RECEIVED;
	अन्यथा
		dequeue_mid(mid, false);
	वापस length;
पूर्ण

काष्ठा smb2_decrypt_work अणु
	काष्ठा work_काष्ठा decrypt;
	काष्ठा TCP_Server_Info *server;
	काष्ठा page **ppages;
	अक्षर *buf;
	अचिन्हित पूर्णांक npages;
	अचिन्हित पूर्णांक len;
पूर्ण;


अटल व्योम smb2_decrypt_offload(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smb2_decrypt_work *dw = container_of(work,
				काष्ठा smb2_decrypt_work, decrypt);
	पूर्णांक i, rc;
	काष्ठा mid_q_entry *mid;

	rc = decrypt_raw_data(dw->server, dw->buf, dw->server->vals->पढ़ो_rsp_size,
			      dw->ppages, dw->npages, dw->len, true);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "error decrypting rc=%d\n", rc);
		जाओ मुक्त_pages;
	पूर्ण

	dw->server->lstrp = jअगरfies;
	mid = smb2_find_dequeue_mid(dw->server, dw->buf);
	अगर (mid == शून्य)
		cअगरs_dbg(FYI, "mid not found\n");
	अन्यथा अणु
		mid->decrypted = true;
		rc = handle_पढ़ो_data(dw->server, mid, dw->buf,
				      dw->server->vals->पढ़ो_rsp_size,
				      dw->ppages, dw->npages, dw->len,
				      true);
		अगर (rc >= 0) अणु
#अगर_घोषित CONFIG_CIFS_STATS2
			mid->when_received = jअगरfies;
#पूर्ण_अगर
			अगर (dw->server->ops->is_network_name_deleted)
				dw->server->ops->is_network_name_deleted(dw->buf,
									 dw->server);

			mid->callback(mid);
		पूर्ण अन्यथा अणु
			spin_lock(&GlobalMid_Lock);
			अगर (dw->server->tcpStatus == CअगरsNeedReconnect) अणु
				mid->mid_state = MID_RETRY_NEEDED;
				spin_unlock(&GlobalMid_Lock);
				mid->callback(mid);
			पूर्ण अन्यथा अणु
				mid->mid_state = MID_REQUEST_SUBMITTED;
				mid->mid_flags &= ~(MID_DELETED);
				list_add_tail(&mid->qhead,
					&dw->server->pending_mid_q);
				spin_unlock(&GlobalMid_Lock);
			पूर्ण
		पूर्ण
		cअगरs_mid_q_entry_release(mid);
	पूर्ण

मुक्त_pages:
	क्रम (i = dw->npages-1; i >= 0; i--)
		put_page(dw->ppages[i]);

	kमुक्त(dw->ppages);
	cअगरs_small_buf_release(dw->buf);
	kमुक्त(dw);
पूर्ण


अटल पूर्णांक
receive_encrypted_पढ़ो(काष्ठा TCP_Server_Info *server, काष्ठा mid_q_entry **mid,
		       पूर्णांक *num_mids)
अणु
	अक्षर *buf = server->smallbuf;
	काष्ठा smb2_transक्रमm_hdr *tr_hdr = (काष्ठा smb2_transक्रमm_hdr *)buf;
	अचिन्हित पूर्णांक npages;
	काष्ठा page **pages;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक buflen = server->pdu_size;
	पूर्णांक rc;
	पूर्णांक i = 0;
	काष्ठा smb2_decrypt_work *dw;

	*num_mids = 1;
	len = min_t(अचिन्हित पूर्णांक, buflen, server->vals->पढ़ो_rsp_size +
		माप(काष्ठा smb2_transक्रमm_hdr)) - HEADER_SIZE(server) + 1;

	rc = cअगरs_पढ़ो_from_socket(server, buf + HEADER_SIZE(server) - 1, len);
	अगर (rc < 0)
		वापस rc;
	server->total_पढ़ो += rc;

	len = le32_to_cpu(tr_hdr->OriginalMessageSize) -
		server->vals->पढ़ो_rsp_size;
	npages = DIV_ROUND_UP(len, PAGE_SIZE);

	pages = kदो_स्मृति_array(npages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages) अणु
		rc = -ENOMEM;
		जाओ discard_data;
	पूर्ण

	क्रम (; i < npages; i++) अणु
		pages[i] = alloc_page(GFP_KERNEL|__GFP_HIGHMEM);
		अगर (!pages[i]) अणु
			rc = -ENOMEM;
			जाओ discard_data;
		पूर्ण
	पूर्ण

	/* पढ़ो पढ़ो data पूर्णांकo pages */
	rc = पढ़ो_data_पूर्णांकo_pages(server, pages, npages, len);
	अगर (rc)
		जाओ मुक्त_pages;

	rc = cअगरs_discard_reमुख्यing_data(server);
	अगर (rc)
		जाओ मुक्त_pages;

	/*
	 * For large पढ़ोs, offload to dअगरferent thपढ़ो क्रम better perक्रमmance,
	 * use more cores decrypting which can be expensive
	 */

	अगर ((server->min_offload) && (server->in_flight > 1) &&
	    (server->pdu_size >= server->min_offload)) अणु
		dw = kदो_स्मृति(माप(काष्ठा smb2_decrypt_work), GFP_KERNEL);
		अगर (dw == शून्य)
			जाओ non_offloaded_decrypt;

		dw->buf = server->smallbuf;
		server->smallbuf = (अक्षर *)cअगरs_small_buf_get();

		INIT_WORK(&dw->decrypt, smb2_decrypt_offload);

		dw->npages = npages;
		dw->server = server;
		dw->ppages = pages;
		dw->len = len;
		queue_work(decrypt_wq, &dw->decrypt);
		*num_mids = 0; /* worker thपढ़ो takes care of finding mid */
		वापस -1;
	पूर्ण

non_offloaded_decrypt:
	rc = decrypt_raw_data(server, buf, server->vals->पढ़ो_rsp_size,
			      pages, npages, len, false);
	अगर (rc)
		जाओ मुक्त_pages;

	*mid = smb2_find_mid(server, buf);
	अगर (*mid == शून्य)
		cअगरs_dbg(FYI, "mid not found\n");
	अन्यथा अणु
		cअगरs_dbg(FYI, "mid found\n");
		(*mid)->decrypted = true;
		rc = handle_पढ़ो_data(server, *mid, buf,
				      server->vals->पढ़ो_rsp_size,
				      pages, npages, len, false);
		अगर (rc >= 0) अणु
			अगर (server->ops->is_network_name_deleted) अणु
				server->ops->is_network_name_deleted(buf,
								server);
			पूर्ण
		पूर्ण
	पूर्ण

मुक्त_pages:
	क्रम (i = i - 1; i >= 0; i--)
		put_page(pages[i]);
	kमुक्त(pages);
	वापस rc;
discard_data:
	cअगरs_discard_reमुख्यing_data(server);
	जाओ मुक्त_pages;
पूर्ण

अटल पूर्णांक
receive_encrypted_standard(काष्ठा TCP_Server_Info *server,
			   काष्ठा mid_q_entry **mids, अक्षर **bufs,
			   पूर्णांक *num_mids)
अणु
	पूर्णांक ret, length;
	अक्षर *buf = server->smallbuf;
	काष्ठा smb2_sync_hdr *shdr;
	अचिन्हित पूर्णांक pdu_length = server->pdu_size;
	अचिन्हित पूर्णांक buf_size;
	काष्ठा mid_q_entry *mid_entry;
	पूर्णांक next_is_large;
	अक्षर *next_buffer = शून्य;

	*num_mids = 0;

	/* चयन to large buffer अगर too big क्रम a small one */
	अगर (pdu_length > MAX_CIFS_SMALL_BUFFER_SIZE) अणु
		server->large_buf = true;
		स_नकल(server->bigbuf, buf, server->total_पढ़ो);
		buf = server->bigbuf;
	पूर्ण

	/* now पढ़ो the rest */
	length = cअगरs_पढ़ो_from_socket(server, buf + HEADER_SIZE(server) - 1,
				pdu_length - HEADER_SIZE(server) + 1);
	अगर (length < 0)
		वापस length;
	server->total_पढ़ो += length;

	buf_size = pdu_length - माप(काष्ठा smb2_transक्रमm_hdr);
	length = decrypt_raw_data(server, buf, buf_size, शून्य, 0, 0, false);
	अगर (length)
		वापस length;

	next_is_large = server->large_buf;
one_more:
	shdr = (काष्ठा smb2_sync_hdr *)buf;
	अगर (shdr->NextCommand) अणु
		अगर (next_is_large)
			next_buffer = (अक्षर *)cअगरs_buf_get();
		अन्यथा
			next_buffer = (अक्षर *)cअगरs_small_buf_get();
		स_नकल(next_buffer,
		       buf + le32_to_cpu(shdr->NextCommand),
		       pdu_length - le32_to_cpu(shdr->NextCommand));
	पूर्ण

	mid_entry = smb2_find_mid(server, buf);
	अगर (mid_entry == शून्य)
		cअगरs_dbg(FYI, "mid not found\n");
	अन्यथा अणु
		cअगरs_dbg(FYI, "mid found\n");
		mid_entry->decrypted = true;
		mid_entry->resp_buf_size = server->pdu_size;
	पूर्ण

	अगर (*num_mids >= MAX_COMPOUND) अणु
		cअगरs_server_dbg(VFS, "too many PDUs in compound\n");
		वापस -1;
	पूर्ण
	bufs[*num_mids] = buf;
	mids[(*num_mids)++] = mid_entry;

	अगर (mid_entry && mid_entry->handle)
		ret = mid_entry->handle(server, mid_entry);
	अन्यथा
		ret = cअगरs_handle_standard(server, mid_entry);

	अगर (ret == 0 && shdr->NextCommand) अणु
		pdu_length -= le32_to_cpu(shdr->NextCommand);
		server->large_buf = next_is_large;
		अगर (next_is_large)
			server->bigbuf = buf = next_buffer;
		अन्यथा
			server->smallbuf = buf = next_buffer;
		जाओ one_more;
	पूर्ण अन्यथा अगर (ret != 0) अणु
		/*
		 * ret != 0 here means that we didn't get to handle_mid() thus
		 * server->smallbuf and server->bigbuf are still valid. We need
		 * to मुक्त next_buffer because it is not going to be used
		 * anywhere.
		 */
		अगर (next_is_large)
			मुक्त_rsp_buf(CIFS_LARGE_BUFFER, next_buffer);
		अन्यथा
			मुक्त_rsp_buf(CIFS_SMALL_BUFFER, next_buffer);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
smb3_receive_transक्रमm(काष्ठा TCP_Server_Info *server,
		       काष्ठा mid_q_entry **mids, अक्षर **bufs, पूर्णांक *num_mids)
अणु
	अक्षर *buf = server->smallbuf;
	अचिन्हित पूर्णांक pdu_length = server->pdu_size;
	काष्ठा smb2_transक्रमm_hdr *tr_hdr = (काष्ठा smb2_transक्रमm_hdr *)buf;
	अचिन्हित पूर्णांक orig_len = le32_to_cpu(tr_hdr->OriginalMessageSize);

	अगर (pdu_length < माप(काष्ठा smb2_transक्रमm_hdr) +
						माप(काष्ठा smb2_sync_hdr)) अणु
		cअगरs_server_dbg(VFS, "Transform message is too small (%u)\n",
			 pdu_length);
		cअगरs_reconnect(server);
		वापस -ECONNABORTED;
	पूर्ण

	अगर (pdu_length < orig_len + माप(काष्ठा smb2_transक्रमm_hdr)) अणु
		cअगरs_server_dbg(VFS, "Transform message is broken\n");
		cअगरs_reconnect(server);
		वापस -ECONNABORTED;
	पूर्ण

	/* TODO: add support क्रम compounds containing READ. */
	अगर (pdu_length > CIFSMaxBufSize + MAX_HEADER_SIZE(server)) अणु
		वापस receive_encrypted_पढ़ो(server, &mids[0], num_mids);
	पूर्ण

	वापस receive_encrypted_standard(server, mids, bufs, num_mids);
पूर्ण

पूर्णांक
smb3_handle_पढ़ो_data(काष्ठा TCP_Server_Info *server, काष्ठा mid_q_entry *mid)
अणु
	अक्षर *buf = server->large_buf ? server->bigbuf : server->smallbuf;

	वापस handle_पढ़ो_data(server, mid, buf, server->pdu_size,
				शून्य, 0, 0, false);
पूर्ण

अटल पूर्णांक
smb2_next_header(अक्षर *buf)
अणु
	काष्ठा smb2_sync_hdr *hdr = (काष्ठा smb2_sync_hdr *)buf;
	काष्ठा smb2_transक्रमm_hdr *t_hdr = (काष्ठा smb2_transक्रमm_hdr *)buf;

	अगर (hdr->ProtocolId == SMB2_TRANSFORM_PROTO_NUM)
		वापस माप(काष्ठा smb2_transक्रमm_hdr) +
		  le32_to_cpu(t_hdr->OriginalMessageSize);

	वापस le32_to_cpu(hdr->NextCommand);
पूर्ण

अटल पूर्णांक
smb2_make_node(अचिन्हित पूर्णांक xid, काष्ठा inode *inode,
	       काष्ठा dentry *dentry, काष्ठा cअगरs_tcon *tcon,
	       स्थिर अक्षर *full_path, umode_t mode, dev_t dev)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	पूर्णांक rc = -EPERM;
	खाता_ALL_INFO *buf = शून्य;
	काष्ठा cअगरs_io_parms io_parms = अणु0पूर्ण;
	__u32 oplock = 0;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;
	अचिन्हित पूर्णांक bytes_written;
	काष्ठा win_dev *pdev;
	काष्ठा kvec iov[2];

	/*
	 * Check अगर mounted with mount parm 'sfu' mount parm.
	 * SFU emulation should work with all servers, but only
	 * supports block and अक्षर device (no socket & fअगरo),
	 * and was used by शेष in earlier versions of Winकरोws
	 */
	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_UNX_EMUL))
		जाओ out;

	/*
	 * TODO: Add ability to create instead via reparse poपूर्णांक. Winकरोws (e.g.
	 * their current NFS server) uses this approach to expose special files
	 * over SMB2/SMB3 and Samba will करो this with SMB3.1.1 POSIX Extensions
	 */

	अगर (!S_ISCHR(mode) && !S_ISBLK(mode))
		जाओ out;

	cअगरs_dbg(FYI, "sfu compat create special file\n");

	buf = kदो_स्मृति(माप(खाता_ALL_INFO), GFP_KERNEL);
	अगर (buf == शून्य) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = GENERIC_WRITE;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, CREATE_NOT_सूची |
						    CREATE_OPTION_SPECIAL);
	oparms.disposition = खाता_CREATE;
	oparms.path = full_path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	अगर (tcon->ses->server->oplocks)
		oplock = REQ_OPLOCK;
	अन्यथा
		oplock = 0;
	rc = tcon->ses->server->ops->खोलो(xid, &oparms, &oplock, buf);
	अगर (rc)
		जाओ out;

	/*
	 * BB Do not bother to decode buf since no local inode yet to put
	 * बारtamps in, but we can reuse it safely.
	 */

	pdev = (काष्ठा win_dev *)buf;
	io_parms.pid = current->tgid;
	io_parms.tcon = tcon;
	io_parms.offset = 0;
	io_parms.length = माप(काष्ठा win_dev);
	iov[1].iov_base = buf;
	iov[1].iov_len = माप(काष्ठा win_dev);
	अगर (S_ISCHR(mode)) अणु
		स_नकल(pdev->type, "IntxCHR", 8);
		pdev->major = cpu_to_le64(MAJOR(dev));
		pdev->minor = cpu_to_le64(MINOR(dev));
		rc = tcon->ses->server->ops->sync_ग_लिखो(xid, &fid, &io_parms,
							&bytes_written, iov, 1);
	पूर्ण अन्यथा अगर (S_ISBLK(mode)) अणु
		स_नकल(pdev->type, "IntxBLK", 8);
		pdev->major = cpu_to_le64(MAJOR(dev));
		pdev->minor = cpu_to_le64(MINOR(dev));
		rc = tcon->ses->server->ops->sync_ग_लिखो(xid, &fid, &io_parms,
							&bytes_written, iov, 1);
	पूर्ण
	tcon->ses->server->ops->बंद(xid, tcon, &fid);
	d_drop(dentry);

	/* FIXME: add code here to set EAs */
out:
	kमुक्त(buf);
	वापस rc;
पूर्ण


काष्ठा smb_version_operations smb20_operations = अणु
	.compare_fids = smb2_compare_fids,
	.setup_request = smb2_setup_request,
	.setup_async_request = smb2_setup_async_request,
	.check_receive = smb2_check_receive,
	.add_credits = smb2_add_credits,
	.set_credits = smb2_set_credits,
	.get_credits_field = smb2_get_credits_field,
	.get_credits = smb2_get_credits,
	.रुको_mtu_credits = cअगरs_रुको_mtu_credits,
	.get_next_mid = smb2_get_next_mid,
	.revert_current_mid = smb2_revert_current_mid,
	.पढ़ो_data_offset = smb2_पढ़ो_data_offset,
	.पढ़ो_data_length = smb2_पढ़ो_data_length,
	.map_error = map_smb2_to_linux_error,
	.find_mid = smb2_find_mid,
	.check_message = smb2_check_message,
	.dump_detail = smb2_dump_detail,
	.clear_stats = smb2_clear_stats,
	.prपूर्णांक_stats = smb2_prपूर्णांक_stats,
	.is_oplock_अवरोध = smb2_is_valid_oplock_अवरोध,
	.handle_cancelled_mid = smb2_handle_cancelled_mid,
	.करोwngrade_oplock = smb2_करोwngrade_oplock,
	.need_neg = smb2_need_neg,
	.negotiate = smb2_negotiate,
	.negotiate_wsize = smb2_negotiate_wsize,
	.negotiate_rsize = smb2_negotiate_rsize,
	.sess_setup = SMB2_sess_setup,
	.logoff = SMB2_logoff,
	.tree_connect = SMB2_tcon,
	.tree_disconnect = SMB2_tdis,
	.qfs_tcon = smb2_qfs_tcon,
	.is_path_accessible = smb2_is_path_accessible,
	.can_echo = smb2_can_echo,
	.echo = SMB2_echo,
	.query_path_info = smb2_query_path_info,
	.get_srv_inum = smb2_get_srv_inum,
	.query_file_info = smb2_query_file_info,
	.set_path_size = smb2_set_path_size,
	.set_file_size = smb2_set_file_size,
	.set_file_info = smb2_set_file_info,
	.set_compression = smb2_set_compression,
	.सूची_गढ़ो = smb2_सूची_गढ़ो,
	.सूची_गढ़ो_setinfo = smb2_सूची_गढ़ो_setinfo,
	.सूची_हटाओ = smb2_सूची_हटाओ,
	.unlink = smb2_unlink,
	.नाम = smb2_नाम_path,
	.create_hardlink = smb2_create_hardlink,
	.query_symlink = smb2_query_symlink,
	.query_mf_symlink = smb3_query_mf_symlink,
	.create_mf_symlink = smb3_create_mf_symlink,
	.खोलो = smb2_खोलो_file,
	.set_fid = smb2_set_fid,
	.बंद = smb2_बंद_file,
	.flush = smb2_flush_file,
	.async_पढ़ोv = smb2_async_पढ़ोv,
	.async_ग_लिखोv = smb2_async_ग_लिखोv,
	.sync_पढ़ो = smb2_sync_पढ़ो,
	.sync_ग_लिखो = smb2_sync_ग_लिखो,
	.query_dir_first = smb2_query_dir_first,
	.query_dir_next = smb2_query_dir_next,
	.बंद_dir = smb2_बंद_dir,
	.calc_smb_size = smb2_calc_size,
	.is_status_pending = smb2_is_status_pending,
	.is_session_expired = smb2_is_session_expired,
	.oplock_response = smb2_oplock_response,
	.queryfs = smb2_queryfs,
	.mand_lock = smb2_mand_lock,
	.mand_unlock_range = smb2_unlock_range,
	.push_mand_locks = smb2_push_mandatory_locks,
	.get_lease_key = smb2_get_lease_key,
	.set_lease_key = smb2_set_lease_key,
	.new_lease_key = smb2_new_lease_key,
	.calc_signature = smb2_calc_signature,
	.is_पढ़ो_op = smb2_is_पढ़ो_op,
	.set_oplock_level = smb2_set_oplock_level,
	.create_lease_buf = smb2_create_lease_buf,
	.parse_lease_buf = smb2_parse_lease_buf,
	.copychunk_range = smb2_copychunk_range,
	.wp_retry_size = smb2_wp_retry_size,
	.dir_needs_बंद = smb2_dir_needs_बंद,
	.get_dfs_refer = smb2_get_dfs_refer,
	.select_sectype = smb2_select_sectype,
#अगर_घोषित CONFIG_CIFS_XATTR
	.query_all_EAs = smb2_query_eas,
	.set_EA = smb2_set_ea,
#पूर्ण_अगर /* CIFS_XATTR */
	.get_acl = get_smb2_acl,
	.get_acl_by_fid = get_smb2_acl_by_fid,
	.set_acl = set_smb2_acl,
	.next_header = smb2_next_header,
	.ioctl_query_info = smb2_ioctl_query_info,
	.make_node = smb2_make_node,
	.fiemap = smb3_fiemap,
	.llseek = smb3_llseek,
	.is_status_io_समयout = smb2_is_status_io_समयout,
	.is_network_name_deleted = smb2_is_network_name_deleted,
पूर्ण;

काष्ठा smb_version_operations smb21_operations = अणु
	.compare_fids = smb2_compare_fids,
	.setup_request = smb2_setup_request,
	.setup_async_request = smb2_setup_async_request,
	.check_receive = smb2_check_receive,
	.add_credits = smb2_add_credits,
	.set_credits = smb2_set_credits,
	.get_credits_field = smb2_get_credits_field,
	.get_credits = smb2_get_credits,
	.रुको_mtu_credits = smb2_रुको_mtu_credits,
	.adjust_credits = smb2_adjust_credits,
	.get_next_mid = smb2_get_next_mid,
	.revert_current_mid = smb2_revert_current_mid,
	.पढ़ो_data_offset = smb2_पढ़ो_data_offset,
	.पढ़ो_data_length = smb2_पढ़ो_data_length,
	.map_error = map_smb2_to_linux_error,
	.find_mid = smb2_find_mid,
	.check_message = smb2_check_message,
	.dump_detail = smb2_dump_detail,
	.clear_stats = smb2_clear_stats,
	.prपूर्णांक_stats = smb2_prपूर्णांक_stats,
	.is_oplock_अवरोध = smb2_is_valid_oplock_अवरोध,
	.handle_cancelled_mid = smb2_handle_cancelled_mid,
	.करोwngrade_oplock = smb2_करोwngrade_oplock,
	.need_neg = smb2_need_neg,
	.negotiate = smb2_negotiate,
	.negotiate_wsize = smb2_negotiate_wsize,
	.negotiate_rsize = smb2_negotiate_rsize,
	.sess_setup = SMB2_sess_setup,
	.logoff = SMB2_logoff,
	.tree_connect = SMB2_tcon,
	.tree_disconnect = SMB2_tdis,
	.qfs_tcon = smb2_qfs_tcon,
	.is_path_accessible = smb2_is_path_accessible,
	.can_echo = smb2_can_echo,
	.echo = SMB2_echo,
	.query_path_info = smb2_query_path_info,
	.get_srv_inum = smb2_get_srv_inum,
	.query_file_info = smb2_query_file_info,
	.set_path_size = smb2_set_path_size,
	.set_file_size = smb2_set_file_size,
	.set_file_info = smb2_set_file_info,
	.set_compression = smb2_set_compression,
	.सूची_गढ़ो = smb2_सूची_गढ़ो,
	.सूची_गढ़ो_setinfo = smb2_सूची_गढ़ो_setinfo,
	.सूची_हटाओ = smb2_सूची_हटाओ,
	.unlink = smb2_unlink,
	.नाम = smb2_नाम_path,
	.create_hardlink = smb2_create_hardlink,
	.query_symlink = smb2_query_symlink,
	.query_mf_symlink = smb3_query_mf_symlink,
	.create_mf_symlink = smb3_create_mf_symlink,
	.खोलो = smb2_खोलो_file,
	.set_fid = smb2_set_fid,
	.बंद = smb2_बंद_file,
	.flush = smb2_flush_file,
	.async_पढ़ोv = smb2_async_पढ़ोv,
	.async_ग_लिखोv = smb2_async_ग_लिखोv,
	.sync_पढ़ो = smb2_sync_पढ़ो,
	.sync_ग_लिखो = smb2_sync_ग_लिखो,
	.query_dir_first = smb2_query_dir_first,
	.query_dir_next = smb2_query_dir_next,
	.बंद_dir = smb2_बंद_dir,
	.calc_smb_size = smb2_calc_size,
	.is_status_pending = smb2_is_status_pending,
	.is_session_expired = smb2_is_session_expired,
	.oplock_response = smb2_oplock_response,
	.queryfs = smb2_queryfs,
	.mand_lock = smb2_mand_lock,
	.mand_unlock_range = smb2_unlock_range,
	.push_mand_locks = smb2_push_mandatory_locks,
	.get_lease_key = smb2_get_lease_key,
	.set_lease_key = smb2_set_lease_key,
	.new_lease_key = smb2_new_lease_key,
	.calc_signature = smb2_calc_signature,
	.is_पढ़ो_op = smb21_is_पढ़ो_op,
	.set_oplock_level = smb21_set_oplock_level,
	.create_lease_buf = smb2_create_lease_buf,
	.parse_lease_buf = smb2_parse_lease_buf,
	.copychunk_range = smb2_copychunk_range,
	.wp_retry_size = smb2_wp_retry_size,
	.dir_needs_बंद = smb2_dir_needs_बंद,
	.क्रमागत_snapshots = smb3_क्रमागत_snapshots,
	.notअगरy = smb3_notअगरy,
	.get_dfs_refer = smb2_get_dfs_refer,
	.select_sectype = smb2_select_sectype,
#अगर_घोषित CONFIG_CIFS_XATTR
	.query_all_EAs = smb2_query_eas,
	.set_EA = smb2_set_ea,
#पूर्ण_अगर /* CIFS_XATTR */
	.get_acl = get_smb2_acl,
	.get_acl_by_fid = get_smb2_acl_by_fid,
	.set_acl = set_smb2_acl,
	.next_header = smb2_next_header,
	.ioctl_query_info = smb2_ioctl_query_info,
	.make_node = smb2_make_node,
	.fiemap = smb3_fiemap,
	.llseek = smb3_llseek,
	.is_status_io_समयout = smb2_is_status_io_समयout,
	.is_network_name_deleted = smb2_is_network_name_deleted,
पूर्ण;

काष्ठा smb_version_operations smb30_operations = अणु
	.compare_fids = smb2_compare_fids,
	.setup_request = smb2_setup_request,
	.setup_async_request = smb2_setup_async_request,
	.check_receive = smb2_check_receive,
	.add_credits = smb2_add_credits,
	.set_credits = smb2_set_credits,
	.get_credits_field = smb2_get_credits_field,
	.get_credits = smb2_get_credits,
	.रुको_mtu_credits = smb2_रुको_mtu_credits,
	.adjust_credits = smb2_adjust_credits,
	.get_next_mid = smb2_get_next_mid,
	.revert_current_mid = smb2_revert_current_mid,
	.पढ़ो_data_offset = smb2_पढ़ो_data_offset,
	.पढ़ो_data_length = smb2_पढ़ो_data_length,
	.map_error = map_smb2_to_linux_error,
	.find_mid = smb2_find_mid,
	.check_message = smb2_check_message,
	.dump_detail = smb2_dump_detail,
	.clear_stats = smb2_clear_stats,
	.prपूर्णांक_stats = smb2_prपूर्णांक_stats,
	.dump_share_caps = smb2_dump_share_caps,
	.is_oplock_अवरोध = smb2_is_valid_oplock_अवरोध,
	.handle_cancelled_mid = smb2_handle_cancelled_mid,
	.करोwngrade_oplock = smb3_करोwngrade_oplock,
	.need_neg = smb2_need_neg,
	.negotiate = smb2_negotiate,
	.negotiate_wsize = smb3_negotiate_wsize,
	.negotiate_rsize = smb3_negotiate_rsize,
	.sess_setup = SMB2_sess_setup,
	.logoff = SMB2_logoff,
	.tree_connect = SMB2_tcon,
	.tree_disconnect = SMB2_tdis,
	.qfs_tcon = smb3_qfs_tcon,
	.is_path_accessible = smb2_is_path_accessible,
	.can_echo = smb2_can_echo,
	.echo = SMB2_echo,
	.query_path_info = smb2_query_path_info,
	/* WSL tags पूर्णांकroduced दीर्घ after smb2.1, enable क्रम SMB3, 3.11 only */
	.query_reparse_tag = smb2_query_reparse_tag,
	.get_srv_inum = smb2_get_srv_inum,
	.query_file_info = smb2_query_file_info,
	.set_path_size = smb2_set_path_size,
	.set_file_size = smb2_set_file_size,
	.set_file_info = smb2_set_file_info,
	.set_compression = smb2_set_compression,
	.सूची_गढ़ो = smb2_सूची_गढ़ो,
	.सूची_गढ़ो_setinfo = smb2_सूची_गढ़ो_setinfo,
	.सूची_हटाओ = smb2_सूची_हटाओ,
	.unlink = smb2_unlink,
	.नाम = smb2_नाम_path,
	.create_hardlink = smb2_create_hardlink,
	.query_symlink = smb2_query_symlink,
	.query_mf_symlink = smb3_query_mf_symlink,
	.create_mf_symlink = smb3_create_mf_symlink,
	.खोलो = smb2_खोलो_file,
	.set_fid = smb2_set_fid,
	.बंद = smb2_बंद_file,
	.बंद_getattr = smb2_बंद_getattr,
	.flush = smb2_flush_file,
	.async_पढ़ोv = smb2_async_पढ़ोv,
	.async_ग_लिखोv = smb2_async_ग_लिखोv,
	.sync_पढ़ो = smb2_sync_पढ़ो,
	.sync_ग_लिखो = smb2_sync_ग_लिखो,
	.query_dir_first = smb2_query_dir_first,
	.query_dir_next = smb2_query_dir_next,
	.बंद_dir = smb2_बंद_dir,
	.calc_smb_size = smb2_calc_size,
	.is_status_pending = smb2_is_status_pending,
	.is_session_expired = smb2_is_session_expired,
	.oplock_response = smb2_oplock_response,
	.queryfs = smb2_queryfs,
	.mand_lock = smb2_mand_lock,
	.mand_unlock_range = smb2_unlock_range,
	.push_mand_locks = smb2_push_mandatory_locks,
	.get_lease_key = smb2_get_lease_key,
	.set_lease_key = smb2_set_lease_key,
	.new_lease_key = smb2_new_lease_key,
	.generate_signingkey = generate_smb30signingkey,
	.calc_signature = smb3_calc_signature,
	.set_पूर्णांकegrity  = smb3_set_पूर्णांकegrity,
	.is_पढ़ो_op = smb21_is_पढ़ो_op,
	.set_oplock_level = smb3_set_oplock_level,
	.create_lease_buf = smb3_create_lease_buf,
	.parse_lease_buf = smb3_parse_lease_buf,
	.copychunk_range = smb2_copychunk_range,
	.duplicate_extents = smb2_duplicate_extents,
	.validate_negotiate = smb3_validate_negotiate,
	.wp_retry_size = smb2_wp_retry_size,
	.dir_needs_बंद = smb2_dir_needs_बंद,
	.fallocate = smb3_fallocate,
	.क्रमागत_snapshots = smb3_क्रमागत_snapshots,
	.notअगरy = smb3_notअगरy,
	.init_transक्रमm_rq = smb3_init_transक्रमm_rq,
	.is_transक्रमm_hdr = smb3_is_transक्रमm_hdr,
	.receive_transक्रमm = smb3_receive_transक्रमm,
	.get_dfs_refer = smb2_get_dfs_refer,
	.select_sectype = smb2_select_sectype,
#अगर_घोषित CONFIG_CIFS_XATTR
	.query_all_EAs = smb2_query_eas,
	.set_EA = smb2_set_ea,
#पूर्ण_अगर /* CIFS_XATTR */
	.get_acl = get_smb2_acl,
	.get_acl_by_fid = get_smb2_acl_by_fid,
	.set_acl = set_smb2_acl,
	.next_header = smb2_next_header,
	.ioctl_query_info = smb2_ioctl_query_info,
	.make_node = smb2_make_node,
	.fiemap = smb3_fiemap,
	.llseek = smb3_llseek,
	.is_status_io_समयout = smb2_is_status_io_समयout,
	.is_network_name_deleted = smb2_is_network_name_deleted,
पूर्ण;

काष्ठा smb_version_operations smb311_operations = अणु
	.compare_fids = smb2_compare_fids,
	.setup_request = smb2_setup_request,
	.setup_async_request = smb2_setup_async_request,
	.check_receive = smb2_check_receive,
	.add_credits = smb2_add_credits,
	.set_credits = smb2_set_credits,
	.get_credits_field = smb2_get_credits_field,
	.get_credits = smb2_get_credits,
	.रुको_mtu_credits = smb2_रुको_mtu_credits,
	.adjust_credits = smb2_adjust_credits,
	.get_next_mid = smb2_get_next_mid,
	.revert_current_mid = smb2_revert_current_mid,
	.पढ़ो_data_offset = smb2_पढ़ो_data_offset,
	.पढ़ो_data_length = smb2_पढ़ो_data_length,
	.map_error = map_smb2_to_linux_error,
	.find_mid = smb2_find_mid,
	.check_message = smb2_check_message,
	.dump_detail = smb2_dump_detail,
	.clear_stats = smb2_clear_stats,
	.prपूर्णांक_stats = smb2_prपूर्णांक_stats,
	.dump_share_caps = smb2_dump_share_caps,
	.is_oplock_अवरोध = smb2_is_valid_oplock_अवरोध,
	.handle_cancelled_mid = smb2_handle_cancelled_mid,
	.करोwngrade_oplock = smb3_करोwngrade_oplock,
	.need_neg = smb2_need_neg,
	.negotiate = smb2_negotiate,
	.negotiate_wsize = smb3_negotiate_wsize,
	.negotiate_rsize = smb3_negotiate_rsize,
	.sess_setup = SMB2_sess_setup,
	.logoff = SMB2_logoff,
	.tree_connect = SMB2_tcon,
	.tree_disconnect = SMB2_tdis,
	.qfs_tcon = smb3_qfs_tcon,
	.is_path_accessible = smb2_is_path_accessible,
	.can_echo = smb2_can_echo,
	.echo = SMB2_echo,
	.query_path_info = smb2_query_path_info,
	.query_reparse_tag = smb2_query_reparse_tag,
	.get_srv_inum = smb2_get_srv_inum,
	.query_file_info = smb2_query_file_info,
	.set_path_size = smb2_set_path_size,
	.set_file_size = smb2_set_file_size,
	.set_file_info = smb2_set_file_info,
	.set_compression = smb2_set_compression,
	.सूची_गढ़ो = smb2_सूची_गढ़ो,
	.सूची_गढ़ो_setinfo = smb2_सूची_गढ़ो_setinfo,
	.posix_सूची_गढ़ो = smb311_posix_सूची_गढ़ो,
	.सूची_हटाओ = smb2_सूची_हटाओ,
	.unlink = smb2_unlink,
	.नाम = smb2_नाम_path,
	.create_hardlink = smb2_create_hardlink,
	.query_symlink = smb2_query_symlink,
	.query_mf_symlink = smb3_query_mf_symlink,
	.create_mf_symlink = smb3_create_mf_symlink,
	.खोलो = smb2_खोलो_file,
	.set_fid = smb2_set_fid,
	.बंद = smb2_बंद_file,
	.बंद_getattr = smb2_बंद_getattr,
	.flush = smb2_flush_file,
	.async_पढ़ोv = smb2_async_पढ़ोv,
	.async_ग_लिखोv = smb2_async_ग_लिखोv,
	.sync_पढ़ो = smb2_sync_पढ़ो,
	.sync_ग_लिखो = smb2_sync_ग_लिखो,
	.query_dir_first = smb2_query_dir_first,
	.query_dir_next = smb2_query_dir_next,
	.बंद_dir = smb2_बंद_dir,
	.calc_smb_size = smb2_calc_size,
	.is_status_pending = smb2_is_status_pending,
	.is_session_expired = smb2_is_session_expired,
	.oplock_response = smb2_oplock_response,
	.queryfs = smb311_queryfs,
	.mand_lock = smb2_mand_lock,
	.mand_unlock_range = smb2_unlock_range,
	.push_mand_locks = smb2_push_mandatory_locks,
	.get_lease_key = smb2_get_lease_key,
	.set_lease_key = smb2_set_lease_key,
	.new_lease_key = smb2_new_lease_key,
	.generate_signingkey = generate_smb311signingkey,
	.calc_signature = smb3_calc_signature,
	.set_पूर्णांकegrity  = smb3_set_पूर्णांकegrity,
	.is_पढ़ो_op = smb21_is_पढ़ो_op,
	.set_oplock_level = smb3_set_oplock_level,
	.create_lease_buf = smb3_create_lease_buf,
	.parse_lease_buf = smb3_parse_lease_buf,
	.copychunk_range = smb2_copychunk_range,
	.duplicate_extents = smb2_duplicate_extents,
/*	.validate_negotiate = smb3_validate_negotiate, */ /* not used in 3.11 */
	.wp_retry_size = smb2_wp_retry_size,
	.dir_needs_बंद = smb2_dir_needs_बंद,
	.fallocate = smb3_fallocate,
	.क्रमागत_snapshots = smb3_क्रमागत_snapshots,
	.notअगरy = smb3_notअगरy,
	.init_transक्रमm_rq = smb3_init_transक्रमm_rq,
	.is_transक्रमm_hdr = smb3_is_transक्रमm_hdr,
	.receive_transक्रमm = smb3_receive_transक्रमm,
	.get_dfs_refer = smb2_get_dfs_refer,
	.select_sectype = smb2_select_sectype,
#अगर_घोषित CONFIG_CIFS_XATTR
	.query_all_EAs = smb2_query_eas,
	.set_EA = smb2_set_ea,
#पूर्ण_अगर /* CIFS_XATTR */
	.get_acl = get_smb2_acl,
	.get_acl_by_fid = get_smb2_acl_by_fid,
	.set_acl = set_smb2_acl,
	.next_header = smb2_next_header,
	.ioctl_query_info = smb2_ioctl_query_info,
	.make_node = smb2_make_node,
	.fiemap = smb3_fiemap,
	.llseek = smb3_llseek,
	.is_status_io_समयout = smb2_is_status_io_समयout,
	.is_network_name_deleted = smb2_is_network_name_deleted,
पूर्ण;

काष्ठा smb_version_values smb20_values = अणु
	.version_string = SMB20_VERSION_STRING,
	.protocol_id = SMB20_PROT_ID,
	.req_capabilities = 0, /* MBZ */
	.large_lock_type = 0,
	.exclusive_lock_type = SMB2_LOCKFLAG_EXCLUSIVE_LOCK,
	.shared_lock_type = SMB2_LOCKFLAG_SHARED_LOCK,
	.unlock_lock_type = SMB2_LOCKFLAG_UNLOCK,
	.header_size = माप(काष्ठा smb2_sync_hdr),
	.header_preamble_size = 0,
	.max_header_size = MAX_SMB2_HDR_SIZE,
	.पढ़ो_rsp_size = माप(काष्ठा smb2_पढ़ो_rsp) - 1,
	.lock_cmd = SMB2_LOCK,
	.cap_unix = 0,
	.cap_nt_find = SMB2_NT_FIND,
	.cap_large_files = SMB2_LARGE_खाताS,
	.signing_enabled = SMB2_NEGOTIATE_SIGNING_ENABLED | SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.signing_required = SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.create_lease_size = माप(काष्ठा create_lease),
पूर्ण;

काष्ठा smb_version_values smb21_values = अणु
	.version_string = SMB21_VERSION_STRING,
	.protocol_id = SMB21_PROT_ID,
	.req_capabilities = 0, /* MBZ on negotiate req until SMB3 dialect */
	.large_lock_type = 0,
	.exclusive_lock_type = SMB2_LOCKFLAG_EXCLUSIVE_LOCK,
	.shared_lock_type = SMB2_LOCKFLAG_SHARED_LOCK,
	.unlock_lock_type = SMB2_LOCKFLAG_UNLOCK,
	.header_size = माप(काष्ठा smb2_sync_hdr),
	.header_preamble_size = 0,
	.max_header_size = MAX_SMB2_HDR_SIZE,
	.पढ़ो_rsp_size = माप(काष्ठा smb2_पढ़ो_rsp) - 1,
	.lock_cmd = SMB2_LOCK,
	.cap_unix = 0,
	.cap_nt_find = SMB2_NT_FIND,
	.cap_large_files = SMB2_LARGE_खाताS,
	.signing_enabled = SMB2_NEGOTIATE_SIGNING_ENABLED | SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.signing_required = SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.create_lease_size = माप(काष्ठा create_lease),
पूर्ण;

काष्ठा smb_version_values smb3any_values = अणु
	.version_string = SMB3ANY_VERSION_STRING,
	.protocol_id = SMB302_PROT_ID, /* करोesn't matter, send protocol array */
	.req_capabilities = SMB2_GLOBAL_CAP_DFS | SMB2_GLOBAL_CAP_LEASING | SMB2_GLOBAL_CAP_LARGE_MTU | SMB2_GLOBAL_CAP_PERSISTENT_HANDLES | SMB2_GLOBAL_CAP_ENCRYPTION | SMB2_GLOBAL_CAP_सूचीECTORY_LEASING,
	.large_lock_type = 0,
	.exclusive_lock_type = SMB2_LOCKFLAG_EXCLUSIVE_LOCK,
	.shared_lock_type = SMB2_LOCKFLAG_SHARED_LOCK,
	.unlock_lock_type = SMB2_LOCKFLAG_UNLOCK,
	.header_size = माप(काष्ठा smb2_sync_hdr),
	.header_preamble_size = 0,
	.max_header_size = MAX_SMB2_HDR_SIZE,
	.पढ़ो_rsp_size = माप(काष्ठा smb2_पढ़ो_rsp) - 1,
	.lock_cmd = SMB2_LOCK,
	.cap_unix = 0,
	.cap_nt_find = SMB2_NT_FIND,
	.cap_large_files = SMB2_LARGE_खाताS,
	.signing_enabled = SMB2_NEGOTIATE_SIGNING_ENABLED | SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.signing_required = SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.create_lease_size = माप(काष्ठा create_lease_v2),
पूर्ण;

काष्ठा smb_version_values smbशेष_values = अणु
	.version_string = SMBDEFAULT_VERSION_STRING,
	.protocol_id = SMB302_PROT_ID, /* करोesn't matter, send protocol array */
	.req_capabilities = SMB2_GLOBAL_CAP_DFS | SMB2_GLOBAL_CAP_LEASING | SMB2_GLOBAL_CAP_LARGE_MTU | SMB2_GLOBAL_CAP_PERSISTENT_HANDLES | SMB2_GLOBAL_CAP_ENCRYPTION | SMB2_GLOBAL_CAP_सूचीECTORY_LEASING,
	.large_lock_type = 0,
	.exclusive_lock_type = SMB2_LOCKFLAG_EXCLUSIVE_LOCK,
	.shared_lock_type = SMB2_LOCKFLAG_SHARED_LOCK,
	.unlock_lock_type = SMB2_LOCKFLAG_UNLOCK,
	.header_size = माप(काष्ठा smb2_sync_hdr),
	.header_preamble_size = 0,
	.max_header_size = MAX_SMB2_HDR_SIZE,
	.पढ़ो_rsp_size = माप(काष्ठा smb2_पढ़ो_rsp) - 1,
	.lock_cmd = SMB2_LOCK,
	.cap_unix = 0,
	.cap_nt_find = SMB2_NT_FIND,
	.cap_large_files = SMB2_LARGE_खाताS,
	.signing_enabled = SMB2_NEGOTIATE_SIGNING_ENABLED | SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.signing_required = SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.create_lease_size = माप(काष्ठा create_lease_v2),
पूर्ण;

काष्ठा smb_version_values smb30_values = अणु
	.version_string = SMB30_VERSION_STRING,
	.protocol_id = SMB30_PROT_ID,
	.req_capabilities = SMB2_GLOBAL_CAP_DFS | SMB2_GLOBAL_CAP_LEASING | SMB2_GLOBAL_CAP_LARGE_MTU | SMB2_GLOBAL_CAP_PERSISTENT_HANDLES | SMB2_GLOBAL_CAP_ENCRYPTION | SMB2_GLOBAL_CAP_सूचीECTORY_LEASING,
	.large_lock_type = 0,
	.exclusive_lock_type = SMB2_LOCKFLAG_EXCLUSIVE_LOCK,
	.shared_lock_type = SMB2_LOCKFLAG_SHARED_LOCK,
	.unlock_lock_type = SMB2_LOCKFLAG_UNLOCK,
	.header_size = माप(काष्ठा smb2_sync_hdr),
	.header_preamble_size = 0,
	.max_header_size = MAX_SMB2_HDR_SIZE,
	.पढ़ो_rsp_size = माप(काष्ठा smb2_पढ़ो_rsp) - 1,
	.lock_cmd = SMB2_LOCK,
	.cap_unix = 0,
	.cap_nt_find = SMB2_NT_FIND,
	.cap_large_files = SMB2_LARGE_खाताS,
	.signing_enabled = SMB2_NEGOTIATE_SIGNING_ENABLED | SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.signing_required = SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.create_lease_size = माप(काष्ठा create_lease_v2),
पूर्ण;

काष्ठा smb_version_values smb302_values = अणु
	.version_string = SMB302_VERSION_STRING,
	.protocol_id = SMB302_PROT_ID,
	.req_capabilities = SMB2_GLOBAL_CAP_DFS | SMB2_GLOBAL_CAP_LEASING | SMB2_GLOBAL_CAP_LARGE_MTU | SMB2_GLOBAL_CAP_PERSISTENT_HANDLES | SMB2_GLOBAL_CAP_ENCRYPTION | SMB2_GLOBAL_CAP_सूचीECTORY_LEASING,
	.large_lock_type = 0,
	.exclusive_lock_type = SMB2_LOCKFLAG_EXCLUSIVE_LOCK,
	.shared_lock_type = SMB2_LOCKFLAG_SHARED_LOCK,
	.unlock_lock_type = SMB2_LOCKFLAG_UNLOCK,
	.header_size = माप(काष्ठा smb2_sync_hdr),
	.header_preamble_size = 0,
	.max_header_size = MAX_SMB2_HDR_SIZE,
	.पढ़ो_rsp_size = माप(काष्ठा smb2_पढ़ो_rsp) - 1,
	.lock_cmd = SMB2_LOCK,
	.cap_unix = 0,
	.cap_nt_find = SMB2_NT_FIND,
	.cap_large_files = SMB2_LARGE_खाताS,
	.signing_enabled = SMB2_NEGOTIATE_SIGNING_ENABLED | SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.signing_required = SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.create_lease_size = माप(काष्ठा create_lease_v2),
पूर्ण;

काष्ठा smb_version_values smb311_values = अणु
	.version_string = SMB311_VERSION_STRING,
	.protocol_id = SMB311_PROT_ID,
	.req_capabilities = SMB2_GLOBAL_CAP_DFS | SMB2_GLOBAL_CAP_LEASING | SMB2_GLOBAL_CAP_LARGE_MTU | SMB2_GLOBAL_CAP_PERSISTENT_HANDLES | SMB2_GLOBAL_CAP_ENCRYPTION | SMB2_GLOBAL_CAP_सूचीECTORY_LEASING,
	.large_lock_type = 0,
	.exclusive_lock_type = SMB2_LOCKFLAG_EXCLUSIVE_LOCK,
	.shared_lock_type = SMB2_LOCKFLAG_SHARED_LOCK,
	.unlock_lock_type = SMB2_LOCKFLAG_UNLOCK,
	.header_size = माप(काष्ठा smb2_sync_hdr),
	.header_preamble_size = 0,
	.max_header_size = MAX_SMB2_HDR_SIZE,
	.पढ़ो_rsp_size = माप(काष्ठा smb2_पढ़ो_rsp) - 1,
	.lock_cmd = SMB2_LOCK,
	.cap_unix = 0,
	.cap_nt_find = SMB2_NT_FIND,
	.cap_large_files = SMB2_LARGE_खाताS,
	.signing_enabled = SMB2_NEGOTIATE_SIGNING_ENABLED | SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.signing_required = SMB2_NEGOTIATE_SIGNING_REQUIRED,
	.create_lease_size = माप(काष्ठा create_lease_v2),
पूर्ण;
