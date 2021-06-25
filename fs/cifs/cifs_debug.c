<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   fs/cअगरs_debug.c
 *
 *   Copyright (C) International Business Machines  Corp., 2000,2005
 *
 *   Modअगरied by Steve French (sfrench@us.ibm.com)
 */
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/uaccess.h>
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "cifsfs.h"
#समावेश "fs_context.h"
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
#समावेश "dfs_cache.h"
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
#समावेश "smbdirect.h"
#पूर्ण_अगर
#समावेश "cifs_swn.h"

व्योम
cअगरs_dump_mem(अक्षर *label, व्योम *data, पूर्णांक length)
अणु
	pr_debug("%s: dump of %d bytes of data at 0x%p\n", label, length, data);
	prपूर्णांक_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET, 16, 4,
		       data, length, true);
पूर्ण

व्योम cअगरs_dump_detail(व्योम *buf, काष्ठा TCP_Server_Info *server)
अणु
#अगर_घोषित CONFIG_CIFS_DEBUG2
	काष्ठा smb_hdr *smb = (काष्ठा smb_hdr *)buf;

	cअगरs_dbg(VFS, "Cmd: %d Err: 0x%x Flags: 0x%x Flgs2: 0x%x Mid: %d Pid: %d\n",
		 smb->Command, smb->Status.CअगरsError,
		 smb->Flags, smb->Flags2, smb->Mid, smb->Pid);
	cअगरs_dbg(VFS, "smb buf %p len %u\n", smb,
		 server->ops->calc_smb_size(smb, server));
#पूर्ण_अगर /* CONFIG_CIFS_DEBUG2 */
पूर्ण

व्योम cअगरs_dump_mids(काष्ठा TCP_Server_Info *server)
अणु
#अगर_घोषित CONFIG_CIFS_DEBUG2
	काष्ठा list_head *पंचांगp;
	काष्ठा mid_q_entry *mid_entry;

	अगर (server == शून्य)
		वापस;

	cअगरs_dbg(VFS, "Dump pending requests:\n");
	spin_lock(&GlobalMid_Lock);
	list_क्रम_each(पंचांगp, &server->pending_mid_q) अणु
		mid_entry = list_entry(पंचांगp, काष्ठा mid_q_entry, qhead);
		cअगरs_dbg(VFS, "State: %d Cmd: %d Pid: %d Cbdata: %p Mid %llu\n",
			 mid_entry->mid_state,
			 le16_to_cpu(mid_entry->command),
			 mid_entry->pid,
			 mid_entry->callback_data,
			 mid_entry->mid);
#अगर_घोषित CONFIG_CIFS_STATS2
		cअगरs_dbg(VFS, "IsLarge: %d buf: %p time rcv: %ld now: %ld\n",
			 mid_entry->large_buf,
			 mid_entry->resp_buf,
			 mid_entry->when_received,
			 jअगरfies);
#पूर्ण_अगर /* STATS2 */
		cअगरs_dbg(VFS, "IsMult: %d IsEnd: %d\n",
			 mid_entry->multiRsp, mid_entry->multiEnd);
		अगर (mid_entry->resp_buf) अणु
			cअगरs_dump_detail(mid_entry->resp_buf, server);
			cअगरs_dump_mem("existing buf: ",
				mid_entry->resp_buf, 62);
		पूर्ण
	पूर्ण
	spin_unlock(&GlobalMid_Lock);
#पूर्ण_अगर /* CONFIG_CIFS_DEBUG2 */
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम cअगरs_debug_tcon(काष्ठा seq_file *m, काष्ठा cअगरs_tcon *tcon)
अणु
	__u32 dev_type = le32_to_cpu(tcon->fsDevInfo.DeviceType);

	seq_म_लिखो(m, "%s Mounts: %d ", tcon->treeName, tcon->tc_count);
	अगर (tcon->nativeFileSystem)
		seq_म_लिखो(m, "Type: %s ", tcon->nativeFileSystem);
	seq_म_लिखो(m, "DevInfo: 0x%x Attributes: 0x%x\n\tPathComponentMax: %d Status: %d",
		   le32_to_cpu(tcon->fsDevInfo.DeviceCharacteristics),
		   le32_to_cpu(tcon->fsAttrInfo.Attributes),
		   le32_to_cpu(tcon->fsAttrInfo.MaxPathNameComponentLength),
		   tcon->tidStatus);
	अगर (dev_type == खाता_DEVICE_DISK)
		seq_माला_दो(m, " type: DISK ");
	अन्यथा अगर (dev_type == खाता_DEVICE_CD_ROM)
		seq_माला_दो(m, " type: CDROM ");
	अन्यथा
		seq_म_लिखो(m, " type: %d ", dev_type);

	seq_म_लिखो(m, "Serial Number: 0x%x", tcon->vol_serial_number);

	अगर ((tcon->seal) ||
	    (tcon->ses->session_flags & SMB2_SESSION_FLAG_ENCRYPT_DATA) ||
	    (tcon->share_flags & SHI1005_FLAGS_ENCRYPT_DATA))
		seq_म_लिखो(m, " Encrypted");
	अगर (tcon->noहाल)
		seq_म_लिखो(m, " nocase");
	अगर (tcon->unix_ext)
		seq_म_लिखो(m, " POSIX Extensions");
	अगर (tcon->ses->server->ops->dump_share_caps)
		tcon->ses->server->ops->dump_share_caps(m, tcon);
	अगर (tcon->use_witness)
		seq_माला_दो(m, " Witness");

	अगर (tcon->need_reconnect)
		seq_माला_दो(m, "\tDISCONNECTED ");
	seq_अ_दो(m, '\n');
पूर्ण

अटल व्योम
cअगरs_dump_channel(काष्ठा seq_file *m, पूर्णांक i, काष्ठा cअगरs_chan *chan)
अणु
	काष्ठा TCP_Server_Info *server = chan->server;

	seq_म_लिखो(m, "\n\n\t\tChannel: %d ConnectionId: 0x%llx"
		   "\n\t\tNumber of credits: %d Dialect 0x%x"
		   "\n\t\tTCP status: %d Instance: %d"
		   "\n\t\tLocal Users To Server: %d SecMode: 0x%x Req On Wire: %d"
		   "\n\t\tIn Send: %d In MaxReq Wait: %d",
		   i+1, server->conn_id,
		   server->credits,
		   server->dialect,
		   server->tcpStatus,
		   server->reconnect_instance,
		   server->srv_count,
		   server->sec_mode,
		   in_flight(server),
		   atomic_पढ़ो(&server->in_send),
		   atomic_पढ़ो(&server->num_रुकोers));
पूर्ण

अटल व्योम
cअगरs_dump_अगरace(काष्ठा seq_file *m, काष्ठा cअगरs_server_अगरace *अगरace)
अणु
	काष्ठा sockaddr_in *ipv4 = (काष्ठा sockaddr_in *)&अगरace->sockaddr;
	काष्ठा sockaddr_in6 *ipv6 = (काष्ठा sockaddr_in6 *)&अगरace->sockaddr;

	seq_म_लिखो(m, "\tSpeed: %zu bps\n", अगरace->speed);
	seq_माला_दो(m, "\t\tCapabilities: ");
	अगर (अगरace->rdma_capable)
		seq_माला_दो(m, "rdma ");
	अगर (अगरace->rss_capable)
		seq_माला_दो(m, "rss ");
	seq_अ_दो(m, '\n');
	अगर (अगरace->sockaddr.ss_family == AF_INET)
		seq_म_लिखो(m, "\t\tIPv4: %pI4\n", &ipv4->sin_addr);
	अन्यथा अगर (अगरace->sockaddr.ss_family == AF_INET6)
		seq_म_लिखो(m, "\t\tIPv6: %pI6\n", &ipv6->sin6_addr);
पूर्ण

अटल पूर्णांक cअगरs_debug_files_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा list_head *sपंचांगp, *पंचांगp, *पंचांगp1, *पंचांगp2;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरsFileInfo *cfile;

	seq_माला_दो(m, "# Version:1\n");
	seq_माला_दो(m, "# Format:\n");
	seq_माला_दो(m, "# <tree id> <persistent fid> <flags> <count> <pid> <uid>");
#अगर_घोषित CONFIG_CIFS_DEBUG2
	seq_म_लिखो(m, " <filename> <mid>\n");
#अन्यथा
	seq_म_लिखो(m, " <filename>\n");
#पूर्ण_अगर /* CIFS_DEBUG2 */
	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each(sपंचांगp, &cअगरs_tcp_ses_list) अणु
		server = list_entry(sपंचांगp, काष्ठा TCP_Server_Info,
				    tcp_ses_list);
		list_क्रम_each(पंचांगp, &server->smb_ses_list) अणु
			ses = list_entry(पंचांगp, काष्ठा cअगरs_ses, smb_ses_list);
			list_क्रम_each(पंचांगp1, &ses->tcon_list) अणु
				tcon = list_entry(पंचांगp1, काष्ठा cअगरs_tcon, tcon_list);
				spin_lock(&tcon->खोलो_file_lock);
				list_क्रम_each(पंचांगp2, &tcon->खोलोFileList) अणु
					cfile = list_entry(पंचांगp2, काष्ठा cअगरsFileInfo,
						     tlist);
					seq_म_लिखो(m,
						"0x%x 0x%llx 0x%x %d %d %d %pd",
						tcon->tid,
						cfile->fid.persistent_fid,
						cfile->f_flags,
						cfile->count,
						cfile->pid,
						from_kuid(&init_user_ns, cfile->uid),
						cfile->dentry);
#अगर_घोषित CONFIG_CIFS_DEBUG2
					seq_म_लिखो(m, " %llu\n", cfile->fid.mid);
#अन्यथा
					seq_म_लिखो(m, "\n");
#पूर्ण_अगर /* CIFS_DEBUG2 */
				पूर्ण
				spin_unlock(&tcon->खोलो_file_lock);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&cअगरs_tcp_ses_lock);
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल पूर्णांक cअगरs_debug_data_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा list_head *पंचांगp1, *पंचांगp2, *पंचांगp3;
	काष्ठा mid_q_entry *mid_entry;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;
	पूर्णांक c, i, j;

	seq_माला_दो(m,
		    "Display Internal CIFS Data Structures for Debugging\n"
		    "---------------------------------------------------\n");
	seq_म_लिखो(m, "CIFS Version %s\n", CIFS_VERSION);
	seq_म_लिखो(m, "Features:");
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	seq_म_लिखो(m, " DFS");
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_FSCACHE
	seq_म_लिखो(m, ",FSCACHE");
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	seq_म_लिखो(m, ",SMB_DIRECT");
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_STATS2
	seq_म_लिखो(m, ",STATS2");
#अन्यथा
	seq_म_लिखो(m, ",STATS");
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_DEBUG2
	seq_म_लिखो(m, ",DEBUG2");
#या_अगर defined(CONFIG_CIFS_DEBUG)
	seq_म_लिखो(m, ",DEBUG");
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_ALLOW_INSECURE_LEGACY
	seq_म_लिखो(m, ",ALLOW_INSECURE_LEGACY");
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
	seq_म_लिखो(m, ",WEAK_PW_HASH");
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_POSIX
	seq_म_लिखो(m, ",CIFS_POSIX");
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_UPCALL
	seq_म_लिखो(m, ",UPCALL(SPNEGO)");
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_XATTR
	seq_म_लिखो(m, ",XATTR");
#पूर्ण_अगर
	seq_म_लिखो(m, ",ACL");
#अगर_घोषित CONFIG_CIFS_SWN_UPCALL
	seq_माला_दो(m, ",WITNESS");
#पूर्ण_अगर
	seq_अ_दो(m, '\n');
	seq_म_लिखो(m, "CIFSMaxBufSize: %d\n", CIFSMaxBufSize);
	seq_म_लिखो(m, "Active VFS Requests: %d\n", GlobalTotalActiveXid);

	seq_म_लिखो(m, "\nServers: ");

	c = 0;
	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each(पंचांगp1, &cअगरs_tcp_ses_list) अणु
		server = list_entry(पंचांगp1, काष्ठा TCP_Server_Info,
				    tcp_ses_list);

		/* channel info will be prपूर्णांकed as a part of sessions below */
		अगर (server->is_channel)
			जारी;

		c++;
		seq_म_लिखो(m, "\n%d) ConnectionId: 0x%llx ",
			c, server->conn_id);

		अगर (server->hostname)
			seq_म_लिखो(m, "Hostname: %s ", server->hostname);
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
		अगर (!server->rdma)
			जाओ skip_rdma;

		अगर (!server->smbd_conn) अणु
			seq_म_लिखो(m, "\nSMBDirect transport not available");
			जाओ skip_rdma;
		पूर्ण

		seq_म_लिखो(m, "\nSMBDirect (in hex) protocol version: %x "
			"transport status: %x",
			server->smbd_conn->protocol,
			server->smbd_conn->transport_status);
		seq_म_लिखो(m, "\nConn receive_credit_max: %x "
			"send_credit_target: %x max_send_size: %x",
			server->smbd_conn->receive_credit_max,
			server->smbd_conn->send_credit_target,
			server->smbd_conn->max_send_size);
		seq_म_लिखो(m, "\nConn max_fragmented_recv_size: %x "
			"max_fragmented_send_size: %x max_receive_size:%x",
			server->smbd_conn->max_fragmented_recv_size,
			server->smbd_conn->max_fragmented_send_size,
			server->smbd_conn->max_receive_size);
		seq_म_लिखो(m, "\nConn keep_alive_interval: %x "
			"max_readwrite_size: %x rdma_readwrite_threshold: %x",
			server->smbd_conn->keep_alive_पूर्णांकerval,
			server->smbd_conn->max_पढ़ोग_लिखो_size,
			server->smbd_conn->rdma_पढ़ोग_लिखो_threshold);
		seq_म_लिखो(m, "\nDebug count_get_receive_buffer: %x "
			"count_put_receive_buffer: %x count_send_empty: %x",
			server->smbd_conn->count_get_receive_buffer,
			server->smbd_conn->count_put_receive_buffer,
			server->smbd_conn->count_send_empty);
		seq_म_लिखो(m, "\nRead Queue count_reassembly_queue: %x "
			"count_enqueue_reassembly_queue: %x "
			"count_dequeue_reassembly_queue: %x "
			"fragment_reassembly_remaining: %x "
			"reassembly_data_length: %x "
			"reassembly_queue_length: %x",
			server->smbd_conn->count_reassembly_queue,
			server->smbd_conn->count_enqueue_reassembly_queue,
			server->smbd_conn->count_dequeue_reassembly_queue,
			server->smbd_conn->fragment_reassembly_reमुख्यing,
			server->smbd_conn->reassembly_data_length,
			server->smbd_conn->reassembly_queue_length);
		seq_म_लिखो(m, "\nCurrent Credits send_credits: %x "
			"receive_credits: %x receive_credit_target: %x",
			atomic_पढ़ो(&server->smbd_conn->send_credits),
			atomic_पढ़ो(&server->smbd_conn->receive_credits),
			server->smbd_conn->receive_credit_target);
		seq_म_लिखो(m, "\nPending send_pending: %x ",
			atomic_पढ़ो(&server->smbd_conn->send_pending));
		seq_म_लिखो(m, "\nReceive buffers count_receive_queue: %x "
			"count_empty_packet_queue: %x",
			server->smbd_conn->count_receive_queue,
			server->smbd_conn->count_empty_packet_queue);
		seq_म_लिखो(m, "\nMR responder_resources: %x "
			"max_frmr_depth: %x mr_type: %x",
			server->smbd_conn->responder_resources,
			server->smbd_conn->max_frmr_depth,
			server->smbd_conn->mr_type);
		seq_म_लिखो(m, "\nMR mr_ready_count: %x mr_used_count: %x",
			atomic_पढ़ो(&server->smbd_conn->mr_पढ़ोy_count),
			atomic_पढ़ो(&server->smbd_conn->mr_used_count));
skip_rdma:
#पूर्ण_अगर
		seq_म_लिखो(m, "\nNumber of credits: %d Dialect 0x%x",
			server->credits,  server->dialect);
		अगर (server->compress_algorithm == SMB3_COMPRESS_LZNT1)
			seq_म_लिखो(m, " COMPRESS_LZNT1");
		अन्यथा अगर (server->compress_algorithm == SMB3_COMPRESS_LZ77)
			seq_म_लिखो(m, " COMPRESS_LZ77");
		अन्यथा अगर (server->compress_algorithm == SMB3_COMPRESS_LZ77_HUFF)
			seq_म_लिखो(m, " COMPRESS_LZ77_HUFF");
		अगर (server->sign)
			seq_म_लिखो(m, " signed");
		अगर (server->posix_ext_supported)
			seq_म_लिखो(m, " posix");

		अगर (server->rdma)
			seq_म_लिखो(m, "\nRDMA ");
		seq_म_लिखो(m, "\nTCP status: %d Instance: %d"
				"\nLocal Users To Server: %d SecMode: 0x%x Req On Wire: %d",
				server->tcpStatus,
				server->reconnect_instance,
				server->srv_count,
				server->sec_mode, in_flight(server));

		seq_म_लिखो(m, "\nIn Send: %d In MaxReq Wait: %d",
				atomic_पढ़ो(&server->in_send),
				atomic_पढ़ो(&server->num_रुकोers));

		seq_म_लिखो(m, "\n\n\tSessions: ");
		i = 0;
		list_क्रम_each(पंचांगp2, &server->smb_ses_list) अणु
			ses = list_entry(पंचांगp2, काष्ठा cअगरs_ses,
					 smb_ses_list);
			i++;
			अगर ((ses->serverDoमुख्य == शून्य) ||
				(ses->serverOS == शून्य) ||
				(ses->serverNOS == शून्य)) अणु
				seq_म_लिखो(m, "\n\t%d) Address: %s Uses: %d Capability: 0x%x\tSession Status: %d ",
					i, ses->ip_addr, ses->ses_count,
					ses->capabilities, ses->status);
				अगर (ses->session_flags & SMB2_SESSION_FLAG_IS_GUEST)
					seq_म_लिखो(m, "Guest ");
				अन्यथा अगर (ses->session_flags & SMB2_SESSION_FLAG_IS_शून्य)
					seq_म_लिखो(m, "Anonymous ");
			पूर्ण अन्यथा अणु
				seq_म_लिखो(m,
				    "\n\t%d) Name: %s  Domain: %s Uses: %d OS: %s "
				    "\n\tNOS: %s\tCapability: 0x%x"
					"\n\tSMB session status: %d ",
				i, ses->ip_addr, ses->serverDoमुख्य,
				ses->ses_count, ses->serverOS, ses->serverNOS,
				ses->capabilities, ses->status);
			पूर्ण

			seq_म_लिखो(m, "\n\tSecurity type: %s ",
				get_security_type_str(server->ops->select_sectype(server, ses->sectype)));

			/* dump session id helpful क्रम use with network trace */
			seq_म_लिखो(m, " SessionId: 0x%llx", ses->Suid);
			अगर (ses->session_flags & SMB2_SESSION_FLAG_ENCRYPT_DATA)
				seq_माला_दो(m, " encrypted");
			अगर (ses->sign)
				seq_माला_दो(m, " signed");

			seq_म_लिखो(m, "\n\tUser: %d Cred User: %d",
				   from_kuid(&init_user_ns, ses->linux_uid),
				   from_kuid(&init_user_ns, ses->cred_uid));

			अगर (ses->chan_count > 1) अणु
				seq_म_लिखो(m, "\n\n\tExtra Channels: %zu ",
					   ses->chan_count-1);
				क्रम (j = 1; j < ses->chan_count; j++)
					cअगरs_dump_channel(m, j, &ses->chans[j]);
			पूर्ण

			seq_माला_दो(m, "\n\n\tShares: ");
			j = 0;

			seq_म_लिखो(m, "\n\t%d) IPC: ", j);
			अगर (ses->tcon_ipc)
				cअगरs_debug_tcon(m, ses->tcon_ipc);
			अन्यथा
				seq_माला_दो(m, "none\n");

			list_क्रम_each(पंचांगp3, &ses->tcon_list) अणु
				tcon = list_entry(पंचांगp3, काष्ठा cअगरs_tcon,
						  tcon_list);
				++j;
				seq_म_लिखो(m, "\n\t%d) ", j);
				cअगरs_debug_tcon(m, tcon);
			पूर्ण

			spin_lock(&ses->अगरace_lock);
			अगर (ses->अगरace_count)
				seq_म_लिखो(m, "\n\n\tServer interfaces: %zu",
					   ses->अगरace_count);
			क्रम (j = 0; j < ses->अगरace_count; j++) अणु
				काष्ठा cअगरs_server_अगरace *अगरace;

				अगरace = &ses->अगरace_list[j];
				seq_म_लिखो(m, "\n\t%d)", j+1);
				cअगरs_dump_अगरace(m, अगरace);
				अगर (is_ses_using_अगरace(ses, अगरace))
					seq_माला_दो(m, "\t\t[CONNECTED]\n");
			पूर्ण
			spin_unlock(&ses->अगरace_lock);
		पूर्ण
		अगर (i == 0)
			seq_म_लिखो(m, "\n\t\t[NONE]");

		seq_माला_दो(m, "\n\n\tMIDs: ");
		spin_lock(&GlobalMid_Lock);
		list_क्रम_each(पंचांगp3, &server->pending_mid_q) अणु
			mid_entry = list_entry(पंचांगp3, काष्ठा mid_q_entry,
					qhead);
			seq_म_लिखो(m, "\n\tState: %d com: %d pid:"
					" %d cbdata: %p mid %llu\n",
					mid_entry->mid_state,
					le16_to_cpu(mid_entry->command),
					mid_entry->pid,
					mid_entry->callback_data,
					mid_entry->mid);
		पूर्ण
		spin_unlock(&GlobalMid_Lock);
		seq_म_लिखो(m, "\n--\n");
	पूर्ण
	अगर (c == 0)
		seq_म_लिखो(m, "\n\t[NONE]");

	spin_unlock(&cअगरs_tcp_ses_lock);
	seq_अ_दो(m, '\n');
	cअगरs_swn_dump(m);

	/* BB add code to dump additional info such as TCP session info now */
	वापस 0;
पूर्ण

अटल sमाप_प्रकार cअगरs_stats_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	bool bv;
	पूर्णांक rc;
	काष्ठा list_head *पंचांगp1, *पंचांगp2, *पंचांगp3;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;

	rc = kstrtobool_from_user(buffer, count, &bv);
	अगर (rc == 0) अणु
#अगर_घोषित CONFIG_CIFS_STATS2
		पूर्णांक i;

		atomic_set(&totBufAllocCount, 0);
		atomic_set(&totSmBufAllocCount, 0);
#पूर्ण_अगर /* CONFIG_CIFS_STATS2 */
		atomic_set(&tcpSesReconnectCount, 0);
		atomic_set(&tconInfoReconnectCount, 0);

		spin_lock(&GlobalMid_Lock);
		GlobalMaxActiveXid = 0;
		GlobalCurrentXid = 0;
		spin_unlock(&GlobalMid_Lock);
		spin_lock(&cअगरs_tcp_ses_lock);
		list_क्रम_each(पंचांगp1, &cअगरs_tcp_ses_list) अणु
			server = list_entry(पंचांगp1, काष्ठा TCP_Server_Info,
					    tcp_ses_list);
			server->max_in_flight = 0;
#अगर_घोषित CONFIG_CIFS_STATS2
			क्रम (i = 0; i < NUMBER_OF_SMB2_COMMANDS; i++) अणु
				atomic_set(&server->num_cmds[i], 0);
				atomic_set(&server->smb2slowcmd[i], 0);
				server->समय_per_cmd[i] = 0;
				server->slowest_cmd[i] = 0;
				server->fastest_cmd[0] = 0;
			पूर्ण
#पूर्ण_अगर /* CONFIG_CIFS_STATS2 */
			list_क्रम_each(पंचांगp2, &server->smb_ses_list) अणु
				ses = list_entry(पंचांगp2, काष्ठा cअगरs_ses,
						 smb_ses_list);
				list_क्रम_each(पंचांगp3, &ses->tcon_list) अणु
					tcon = list_entry(पंचांगp3,
							  काष्ठा cअगरs_tcon,
							  tcon_list);
					atomic_set(&tcon->num_smbs_sent, 0);
					spin_lock(&tcon->stat_lock);
					tcon->bytes_पढ़ो = 0;
					tcon->bytes_written = 0;
					spin_unlock(&tcon->stat_lock);
					अगर (server->ops->clear_stats)
						server->ops->clear_stats(tcon);
				पूर्ण
			पूर्ण
		पूर्ण
		spin_unlock(&cअगरs_tcp_ses_lock);
	पूर्ण अन्यथा अणु
		वापस rc;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक cअगरs_stats_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;
#अगर_घोषित CONFIG_CIFS_STATS2
	पूर्णांक j;
#पूर्ण_अगर /* STATS2 */
	काष्ठा list_head *पंचांगp1, *पंचांगp2, *पंचांगp3;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;

	seq_म_लिखो(m, "Resources in use\nCIFS Session: %d\n",
			sesInfoAllocCount.counter);
	seq_म_लिखो(m, "Share (unique mount targets): %d\n",
			tconInfoAllocCount.counter);
	seq_म_लिखो(m, "SMB Request/Response Buffer: %d Pool size: %d\n",
			bufAllocCount.counter,
			cअगरs_min_rcv + tcpSesAllocCount.counter);
	seq_म_लिखो(m, "SMB Small Req/Resp Buffer: %d Pool size: %d\n",
			smBufAllocCount.counter, cअगरs_min_small);
#अगर_घोषित CONFIG_CIFS_STATS2
	seq_म_लिखो(m, "Total Large %d Small %d Allocations\n",
				atomic_पढ़ो(&totBufAllocCount),
				atomic_पढ़ो(&totSmBufAllocCount));
#पूर्ण_अगर /* CONFIG_CIFS_STATS2 */

	seq_म_लिखो(m, "Operations (MIDs): %d\n", atomic_पढ़ो(&midCount));
	seq_म_लिखो(m,
		"\n%d session %d share reconnects\n",
		tcpSesReconnectCount.counter, tconInfoReconnectCount.counter);

	seq_म_लिखो(m,
		"Total vfs operations: %d maximum at one time: %d\n",
		GlobalCurrentXid, GlobalMaxActiveXid);

	i = 0;
	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each(पंचांगp1, &cअगरs_tcp_ses_list) अणु
		server = list_entry(पंचांगp1, काष्ठा TCP_Server_Info,
				    tcp_ses_list);
		seq_म_लिखो(m, "\nMax requests in flight: %d", server->max_in_flight);
#अगर_घोषित CONFIG_CIFS_STATS2
		seq_माला_दो(m, "\nTotal time spent processing by command. Time ");
		seq_म_लिखो(m, "units are jiffies (%d per second)\n", HZ);
		seq_माला_दो(m, "  SMB3 CMD\tNumber\tTotal Time\tFastest\tSlowest\n");
		seq_माला_दो(m, "  --------\t------\t----------\t-------\t-------\n");
		क्रम (j = 0; j < NUMBER_OF_SMB2_COMMANDS; j++)
			seq_म_लिखो(m, "  %d\t\t%d\t%llu\t\t%u\t%u\n", j,
				atomic_पढ़ो(&server->num_cmds[j]),
				server->समय_per_cmd[j],
				server->fastest_cmd[j],
				server->slowest_cmd[j]);
		क्रम (j = 0; j < NUMBER_OF_SMB2_COMMANDS; j++)
			अगर (atomic_पढ़ो(&server->smb2slowcmd[j]))
				seq_म_लिखो(m, "  %d slow responses from %s for command %d\n",
					atomic_पढ़ो(&server->smb2slowcmd[j]),
					server->hostname, j);
#पूर्ण_अगर /* STATS2 */
		list_क्रम_each(पंचांगp2, &server->smb_ses_list) अणु
			ses = list_entry(पंचांगp2, काष्ठा cअगरs_ses,
					 smb_ses_list);
			list_क्रम_each(पंचांगp3, &ses->tcon_list) अणु
				tcon = list_entry(पंचांगp3,
						  काष्ठा cअगरs_tcon,
						  tcon_list);
				i++;
				seq_म_लिखो(m, "\n%d) %s", i, tcon->treeName);
				अगर (tcon->need_reconnect)
					seq_माला_दो(m, "\tDISCONNECTED ");
				seq_म_लिखो(m, "\nSMBs: %d",
					   atomic_पढ़ो(&tcon->num_smbs_sent));
				अगर (server->ops->prपूर्णांक_stats)
					server->ops->prपूर्णांक_stats(m, tcon);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&cअगरs_tcp_ses_lock);

	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल पूर्णांक cअगरs_stats_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, cअगरs_stats_proc_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops cअगरs_stats_proc_ops = अणु
	.proc_खोलो	= cअगरs_stats_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= cअगरs_stats_proc_ग_लिखो,
पूर्ण;

#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
#घोषणा PROC_खाता_DEFINE(name) \
अटल sमाप_प्रकार name##_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer, \
	माप_प्रकार count, loff_t *ppos) \
अणु \
	पूर्णांक rc; \
	rc = kstrtoपूर्णांक_from_user(buffer, count, 10, & name); \
	अगर (rc) \
		वापस rc; \
	वापस count; \
पूर्ण \
अटल पूर्णांक name##_proc_show(काष्ठा seq_file *m, व्योम *v) \
अणु \
	seq_म_लिखो(m, "%d\n", name ); \
	वापस 0; \
पूर्ण \
अटल पूर्णांक name##_खोलो(काष्ठा inode *inode, काष्ठा file *file) \
अणु \
	वापस single_खोलो(file, name##_proc_show, शून्य); \
पूर्ण \
\
अटल स्थिर काष्ठा proc_ops cअगरs_##name##_proc_fops = अणु \
	.proc_खोलो	= name##_खोलो, \
	.proc_पढ़ो	= seq_पढ़ो, \
	.proc_lseek	= seq_lseek, \
	.proc_release	= single_release, \
	.proc_ग_लिखो	= name##_ग_लिखो, \
पूर्ण

PROC_खाता_DEFINE(rdma_पढ़ोग_लिखो_threshold);
PROC_खाता_DEFINE(smbd_max_frmr_depth);
PROC_खाता_DEFINE(smbd_keep_alive_पूर्णांकerval);
PROC_खाता_DEFINE(smbd_max_receive_size);
PROC_खाता_DEFINE(smbd_max_fragmented_recv_size);
PROC_खाता_DEFINE(smbd_max_send_size);
PROC_खाता_DEFINE(smbd_send_credit_target);
PROC_खाता_DEFINE(smbd_receive_credit_max);
#पूर्ण_अगर

अटल काष्ठा proc_dir_entry *proc_fs_cअगरs;
अटल स्थिर काष्ठा proc_ops cअगरsFYI_proc_ops;
अटल स्थिर काष्ठा proc_ops cअगरs_lookup_cache_proc_ops;
अटल स्थिर काष्ठा proc_ops traceSMB_proc_ops;
अटल स्थिर काष्ठा proc_ops cअगरs_security_flags_proc_ops;
अटल स्थिर काष्ठा proc_ops cअगरs_linux_ext_proc_ops;
अटल स्थिर काष्ठा proc_ops cअगरs_mount_params_proc_ops;

व्योम
cअगरs_proc_init(व्योम)
अणु
	proc_fs_cअगरs = proc_सूची_गढ़ो("fs/cifs", शून्य);
	अगर (proc_fs_cअगरs == शून्य)
		वापस;

	proc_create_single("DebugData", 0, proc_fs_cअगरs,
			cअगरs_debug_data_proc_show);

	proc_create_single("open_files", 0400, proc_fs_cअगरs,
			cअगरs_debug_files_proc_show);

	proc_create("Stats", 0644, proc_fs_cअगरs, &cअगरs_stats_proc_ops);
	proc_create("cifsFYI", 0644, proc_fs_cअगरs, &cअगरsFYI_proc_ops);
	proc_create("traceSMB", 0644, proc_fs_cअगरs, &traceSMB_proc_ops);
	proc_create("LinuxExtensionsEnabled", 0644, proc_fs_cअगरs,
		    &cअगरs_linux_ext_proc_ops);
	proc_create("SecurityFlags", 0644, proc_fs_cअगरs,
		    &cअगरs_security_flags_proc_ops);
	proc_create("LookupCacheEnabled", 0644, proc_fs_cअगरs,
		    &cअगरs_lookup_cache_proc_ops);

	proc_create("mount_params", 0444, proc_fs_cअगरs, &cअगरs_mount_params_proc_ops);

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	proc_create("dfscache", 0644, proc_fs_cअगरs, &dfscache_proc_ops);
#पूर्ण_अगर

#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	proc_create("rdma_readwrite_threshold", 0644, proc_fs_cअगरs,
		&cअगरs_rdma_पढ़ोग_लिखो_threshold_proc_fops);
	proc_create("smbd_max_frmr_depth", 0644, proc_fs_cअगरs,
		&cअगरs_smbd_max_frmr_depth_proc_fops);
	proc_create("smbd_keep_alive_interval", 0644, proc_fs_cअगरs,
		&cअगरs_smbd_keep_alive_पूर्णांकerval_proc_fops);
	proc_create("smbd_max_receive_size", 0644, proc_fs_cअगरs,
		&cअगरs_smbd_max_receive_size_proc_fops);
	proc_create("smbd_max_fragmented_recv_size", 0644, proc_fs_cअगरs,
		&cअगरs_smbd_max_fragmented_recv_size_proc_fops);
	proc_create("smbd_max_send_size", 0644, proc_fs_cअगरs,
		&cअगरs_smbd_max_send_size_proc_fops);
	proc_create("smbd_send_credit_target", 0644, proc_fs_cअगरs,
		&cअगरs_smbd_send_credit_target_proc_fops);
	proc_create("smbd_receive_credit_max", 0644, proc_fs_cअगरs,
		&cअगरs_smbd_receive_credit_max_proc_fops);
#पूर्ण_अगर
पूर्ण

व्योम
cअगरs_proc_clean(व्योम)
अणु
	अगर (proc_fs_cअगरs == शून्य)
		वापस;

	हटाओ_proc_entry("DebugData", proc_fs_cअगरs);
	हटाओ_proc_entry("open_files", proc_fs_cअगरs);
	हटाओ_proc_entry("cifsFYI", proc_fs_cअगरs);
	हटाओ_proc_entry("traceSMB", proc_fs_cअगरs);
	हटाओ_proc_entry("Stats", proc_fs_cअगरs);
	हटाओ_proc_entry("SecurityFlags", proc_fs_cअगरs);
	हटाओ_proc_entry("LinuxExtensionsEnabled", proc_fs_cअगरs);
	हटाओ_proc_entry("LookupCacheEnabled", proc_fs_cअगरs);
	हटाओ_proc_entry("mount_params", proc_fs_cअगरs);

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	हटाओ_proc_entry("dfscache", proc_fs_cअगरs);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	हटाओ_proc_entry("rdma_readwrite_threshold", proc_fs_cअगरs);
	हटाओ_proc_entry("smbd_max_frmr_depth", proc_fs_cअगरs);
	हटाओ_proc_entry("smbd_keep_alive_interval", proc_fs_cअगरs);
	हटाओ_proc_entry("smbd_max_receive_size", proc_fs_cअगरs);
	हटाओ_proc_entry("smbd_max_fragmented_recv_size", proc_fs_cअगरs);
	हटाओ_proc_entry("smbd_max_send_size", proc_fs_cअगरs);
	हटाओ_proc_entry("smbd_send_credit_target", proc_fs_cअगरs);
	हटाओ_proc_entry("smbd_receive_credit_max", proc_fs_cअगरs);
#पूर्ण_अगर
	हटाओ_proc_entry("fs/cifs", शून्य);
पूर्ण

अटल पूर्णांक cअगरsFYI_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%d\n", cअगरsFYI);
	वापस 0;
पूर्ण

अटल पूर्णांक cअगरsFYI_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, cअगरsFYI_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार cअगरsFYI_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
		माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर c[2] = अणु '\0' पूर्ण;
	bool bv;
	पूर्णांक rc;

	rc = get_user(c[0], buffer);
	अगर (rc)
		वापस rc;
	अगर (strtobool(c, &bv) == 0)
		cअगरsFYI = bv;
	अन्यथा अगर ((c[0] > '1') && (c[0] <= '9'))
		cअगरsFYI = (पूर्णांक) (c[0] - '0'); /* see cअगरs_debug.h क्रम meanings */
	अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops cअगरsFYI_proc_ops = अणु
	.proc_खोलो	= cअगरsFYI_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= cअगरsFYI_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक cअगरs_linux_ext_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%d\n", linuxExtEnabled);
	वापस 0;
पूर्ण

अटल पूर्णांक cअगरs_linux_ext_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, cअगरs_linux_ext_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार cअगरs_linux_ext_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक rc;

	rc = kstrtobool_from_user(buffer, count, &linuxExtEnabled);
	अगर (rc)
		वापस rc;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops cअगरs_linux_ext_proc_ops = अणु
	.proc_खोलो	= cअगरs_linux_ext_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= cअगरs_linux_ext_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक cअगरs_lookup_cache_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%d\n", lookupCacheEnabled);
	वापस 0;
पूर्ण

अटल पूर्णांक cअगरs_lookup_cache_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, cअगरs_lookup_cache_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार cअगरs_lookup_cache_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक rc;

	rc = kstrtobool_from_user(buffer, count, &lookupCacheEnabled);
	अगर (rc)
		वापस rc;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops cअगरs_lookup_cache_proc_ops = अणु
	.proc_खोलो	= cअगरs_lookup_cache_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= cअगरs_lookup_cache_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक traceSMB_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%d\n", traceSMB);
	वापस 0;
पूर्ण

अटल पूर्णांक traceSMB_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, traceSMB_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार traceSMB_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
		माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक rc;

	rc = kstrtobool_from_user(buffer, count, &traceSMB);
	अगर (rc)
		वापस rc;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops traceSMB_proc_ops = अणु
	.proc_खोलो	= traceSMB_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= traceSMB_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक cअगरs_security_flags_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "0x%x\n", global_secflags);
	वापस 0;
पूर्ण

अटल पूर्णांक cअगरs_security_flags_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, cअगरs_security_flags_proc_show, शून्य);
पूर्ण

/*
 * Ensure that अगर someone sets a MUST flag, that we disable all other MAY
 * flags except क्रम the ones corresponding to the given MUST flag. If there are
 * multiple MUST flags, then try to prefer more secure ones.
 */
अटल व्योम
cअगरs_security_flags_handle_must_flags(अचिन्हित पूर्णांक *flags)
अणु
	अचिन्हित पूर्णांक signflags = *flags & CIFSSEC_MUST_SIGN;

	अगर ((*flags & CIFSSEC_MUST_KRB5) == CIFSSEC_MUST_KRB5)
		*flags = CIFSSEC_MUST_KRB5;
	अन्यथा अगर ((*flags & CIFSSEC_MUST_NTLMSSP) == CIFSSEC_MUST_NTLMSSP)
		*flags = CIFSSEC_MUST_NTLMSSP;
	अन्यथा अगर ((*flags & CIFSSEC_MUST_NTLMV2) == CIFSSEC_MUST_NTLMV2)
		*flags = CIFSSEC_MUST_NTLMV2;
	अन्यथा अगर ((*flags & CIFSSEC_MUST_NTLM) == CIFSSEC_MUST_NTLM)
		*flags = CIFSSEC_MUST_NTLM;
	अन्यथा अगर (CIFSSEC_MUST_LANMAN &&
		 (*flags & CIFSSEC_MUST_LANMAN) == CIFSSEC_MUST_LANMAN)
		*flags = CIFSSEC_MUST_LANMAN;
	अन्यथा अगर (CIFSSEC_MUST_PLNTXT &&
		 (*flags & CIFSSEC_MUST_PLNTXT) == CIFSSEC_MUST_PLNTXT)
		*flags = CIFSSEC_MUST_PLNTXT;

	*flags |= signflags;
पूर्ण

अटल sमाप_प्रकार cअगरs_security_flags_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक flags;
	अक्षर flags_string[12];
	bool bv;

	अगर ((count < 1) || (count > 11))
		वापस -EINVAL;

	स_रखो(flags_string, 0, 12);

	अगर (copy_from_user(flags_string, buffer, count))
		वापस -EFAULT;

	अगर (count < 3) अणु
		/* single अक्षर or single अक्षर followed by null */
		अगर (strtobool(flags_string, &bv) == 0) अणु
			global_secflags = bv ? CIFSSEC_MAX : CIFSSEC_DEF;
			वापस count;
		पूर्ण अन्यथा अगर (!है_अंक(flags_string[0])) अणु
			cअगरs_dbg(VFS, "Invalid SecurityFlags: %s\n",
					flags_string);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* अन्यथा we have a number */
	rc = kstrtouपूर्णांक(flags_string, 0, &flags);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "Invalid SecurityFlags: %s\n",
				flags_string);
		वापस rc;
	पूर्ण

	cअगरs_dbg(FYI, "sec flags 0x%x\n", flags);

	अगर (flags == 0)  अणु
		cअगरs_dbg(VFS, "Invalid SecurityFlags: %s\n", flags_string);
		वापस -EINVAL;
	पूर्ण

	अगर (flags & ~CIFSSEC_MASK) अणु
		cअगरs_dbg(VFS, "Unsupported security flags: 0x%x\n",
			 flags & ~CIFSSEC_MASK);
		वापस -EINVAL;
	पूर्ण

	cअगरs_security_flags_handle_must_flags(&flags);

	/* flags look ok - update the global security flags क्रम cअगरs module */
	global_secflags = flags;
	अगर (global_secflags & CIFSSEC_MUST_SIGN) अणु
		/* requiring signing implies signing is allowed */
		global_secflags |= CIFSSEC_MAY_SIGN;
		cअगरs_dbg(FYI, "packet signing now required\n");
	पूर्ण अन्यथा अगर ((global_secflags & CIFSSEC_MAY_SIGN) == 0) अणु
		cअगरs_dbg(FYI, "packet signing disabled\n");
	पूर्ण
	/* BB should we turn on MAY flags क्रम other MUST options? */
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops cअगरs_security_flags_proc_ops = अणु
	.proc_खोलो	= cअगरs_security_flags_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= cअगरs_security_flags_proc_ग_लिखो,
पूर्ण;

/* To make it easier to debug, can help to show mount params */
अटल पूर्णांक cअगरs_mount_params_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	स्थिर काष्ठा fs_parameter_spec *p;
	स्थिर अक्षर *type;

	क्रम (p = smb3_fs_parameters; p->name; p++) अणु
		/* cannot use चयन with poपूर्णांकers... */
		अगर (!p->type) अणु
			अगर (p->flags == fs_param_neg_with_no)
				type = "noflag";
			अन्यथा
				type = "flag";
		पूर्ण अन्यथा अगर (p->type == fs_param_is_bool)
			type = "bool";
		अन्यथा अगर (p->type == fs_param_is_u32)
			type = "u32";
		अन्यथा अगर (p->type == fs_param_is_u64)
			type = "u64";
		अन्यथा अगर (p->type == fs_param_is_string)
			type = "string";
		अन्यथा
			type = "unknown";

		seq_म_लिखो(m, "%s:%s\n", p->name, type);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cअगरs_mount_params_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, cअगरs_mount_params_proc_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops cअगरs_mount_params_proc_ops = अणु
	.proc_खोलो	= cअगरs_mount_params_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	/* No need क्रम ग_लिखो क्रम now */
	/* .proc_ग_लिखो	= cअगरs_mount_params_proc_ग_लिखो, */
पूर्ण;

#अन्यथा
अंतरभूत व्योम cअगरs_proc_init(व्योम)
अणु
पूर्ण

अंतरभूत व्योम cअगरs_proc_clean(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* PROC_FS */
