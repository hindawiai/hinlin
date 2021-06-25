<शैली गुरु>
/*
 *   fs/cअगरs/smb2pdu.c
 *
 *   Copyright (C) International Business Machines  Corp., 2009, 2013
 *                 Etersoft, 2012
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *              Pavel Shilovsky (pshilovsky@samba.org) 2012
 *
 *   Contains the routines क्रम स्थिरructing the SMB2 PDUs themselves
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

 /* SMB2 PDU handling routines here - except क्रम leftovers (eg session setup) */
 /* Note that there are handle based routines which must be		      */
 /* treated slightly dअगरferently क्रम reconnection purposes since we never     */
 /* want to reuse a stale file handle and only the caller knows the file info */

#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/vfs.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/uuid.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/xattr.h>
#समावेश "smb2pdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsacl.h"
#समावेश "cifsproto.h"
#समावेश "smb2proto.h"
#समावेश "cifs_unicode.h"
#समावेश "cifs_debug.h"
#समावेश "ntlmssp.h"
#समावेश "smb2status.h"
#समावेश "smb2glob.h"
#समावेश "cifspdu.h"
#समावेश "cifs_spnego.h"
#समावेश "smbdirect.h"
#समावेश "trace.h"
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
#समावेश "dfs_cache.h"
#पूर्ण_अगर

/*
 *  The following table defines the expected "StructureSize" of SMB2 requests
 *  in order by SMB2 command.  This is similar to "wct" in SMB/CIFS requests.
 *
 *  Note that commands are defined in smb2pdu.h in le16 but the array below is
 *  indexed by command in host byte order.
 */
अटल स्थिर पूर्णांक smb2_req_काष्ठा_sizes[NUMBER_OF_SMB2_COMMANDS] = अणु
	/* SMB2_NEGOTIATE */ 36,
	/* SMB2_SESSION_SETUP */ 25,
	/* SMB2_LOGOFF */ 4,
	/* SMB2_TREE_CONNECT */	9,
	/* SMB2_TREE_DISCONNECT */ 4,
	/* SMB2_CREATE */ 57,
	/* SMB2_CLOSE */ 24,
	/* SMB2_FLUSH */ 24,
	/* SMB2_READ */	49,
	/* SMB2_WRITE */ 49,
	/* SMB2_LOCK */	48,
	/* SMB2_IOCTL */ 57,
	/* SMB2_CANCEL */ 4,
	/* SMB2_ECHO */ 4,
	/* SMB2_QUERY_सूचीECTORY */ 33,
	/* SMB2_CHANGE_NOTIFY */ 32,
	/* SMB2_QUERY_INFO */ 41,
	/* SMB2_SET_INFO */ 33,
	/* SMB2_OPLOCK_BREAK */ 24 /* BB this is 36 क्रम LEASE_BREAK variant */
पूर्ण;

पूर्णांक smb3_encryption_required(स्थिर काष्ठा cअगरs_tcon *tcon)
अणु
	अगर (!tcon || !tcon->ses)
		वापस 0;
	अगर ((tcon->ses->session_flags & SMB2_SESSION_FLAG_ENCRYPT_DATA) ||
	    (tcon->share_flags & SHI1005_FLAGS_ENCRYPT_DATA))
		वापस 1;
	अगर (tcon->seal &&
	    (tcon->ses->server->capabilities & SMB2_GLOBAL_CAP_ENCRYPTION))
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम
smb2_hdr_assemble(काष्ठा smb2_sync_hdr *shdr, __le16 smb2_cmd,
		  स्थिर काष्ठा cअगरs_tcon *tcon,
		  काष्ठा TCP_Server_Info *server)
अणु
	shdr->ProtocolId = SMB2_PROTO_NUMBER;
	shdr->StructureSize = cpu_to_le16(64);
	shdr->Command = smb2_cmd;
	अगर (server) अणु
		spin_lock(&server->req_lock);
		/* Request up to 10 credits but करोn't go over the limit. */
		अगर (server->credits >= server->max_credits)
			shdr->CreditRequest = cpu_to_le16(0);
		अन्यथा
			shdr->CreditRequest = cpu_to_le16(
				min_t(पूर्णांक, server->max_credits -
						server->credits, 10));
		spin_unlock(&server->req_lock);
	पूर्ण अन्यथा अणु
		shdr->CreditRequest = cpu_to_le16(2);
	पूर्ण
	shdr->ProcessId = cpu_to_le32((__u16)current->tgid);

	अगर (!tcon)
		जाओ out;

	/* GLOBAL_CAP_LARGE_MTU will only be set अगर dialect > SMB2.02 */
	/* See sections 2.2.4 and 3.2.4.1.5 of MS-SMB2 */
	अगर (server && (server->capabilities & SMB2_GLOBAL_CAP_LARGE_MTU))
		shdr->CreditCharge = cpu_to_le16(1);
	/* अन्यथा CreditCharge MBZ */

	shdr->TreeId = tcon->tid;
	/* Uid is not converted */
	अगर (tcon->ses)
		shdr->SessionId = tcon->ses->Suid;

	/*
	 * If we would set SMB2_FLAGS_DFS_OPERATIONS on खोलो we also would have
	 * to pass the path on the Open SMB prefixed by \\server\share.
	 * Not sure when we would need to करो the augmented path (अगर ever) and
	 * setting this flag अवरोधs the SMB2 खोलो operation since it is
	 * illegal to send an empty path name (without \\server\share prefix)
	 * when the DFS flag is set in the SMB खोलो header. We could
	 * consider setting the flag on all operations other than खोलो
	 * but it is safer to net set it क्रम now.
	 */
/*	अगर (tcon->share_flags & SHI1005_FLAGS_DFS)
		shdr->Flags |= SMB2_FLAGS_DFS_OPERATIONS; */

	अगर (server && server->sign && !smb3_encryption_required(tcon))
		shdr->Flags |= SMB2_FLAGS_SIGNED;
out:
	वापस;
पूर्ण

अटल पूर्णांक
smb2_reconnect(__le16 smb2_command, काष्ठा cअगरs_tcon *tcon,
	       काष्ठा TCP_Server_Info *server)
अणु
	पूर्णांक rc;
	काष्ठा nls_table *nls_codepage;
	काष्ठा cअगरs_ses *ses;
	पूर्णांक retries;

	/*
	 * SMB2s NegProt, SessSetup, Logoff करो not have tcon yet so
	 * check क्रम tcp and smb session status करोne dअगरferently
	 * क्रम those three - in the calling routine.
	 */
	अगर (tcon == शून्य)
		वापस 0;

	अगर (smb2_command == SMB2_TREE_CONNECT)
		वापस 0;

	अगर (tcon->tidStatus == CअगरsExiting) अणु
		/*
		 * only tree disconnect, खोलो, and ग_लिखो,
		 * (and ulogoff which करोes not have tcon)
		 * are allowed as we start क्रमce umount.
		 */
		अगर ((smb2_command != SMB2_WRITE) &&
		   (smb2_command != SMB2_CREATE) &&
		   (smb2_command != SMB2_TREE_DISCONNECT)) अणु
			cअगरs_dbg(FYI, "can not send cmd %d while umounting\n",
				 smb2_command);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अगर ((!tcon->ses) || (tcon->ses->status == CअगरsExiting) ||
	    (!tcon->ses->server) || !server)
		वापस -EIO;

	ses = tcon->ses;
	retries = server->nr_tarमाला_लो;

	/*
	 * Give demultiplex thपढ़ो up to 10 seconds to each target available क्रम
	 * reconnect -- should be greater than cअगरs socket समयout which is 7
	 * seconds.
	 */
	जबतक (server->tcpStatus == CअगरsNeedReconnect) अणु
		/*
		 * Return to caller क्रम TREE_DISCONNECT and LOGOFF and CLOSE
		 * here since they are implicitly करोne when session drops.
		 */
		चयन (smb2_command) अणु
		/*
		 * BB Should we keep oplock अवरोध and add flush to exceptions?
		 */
		हाल SMB2_TREE_DISCONNECT:
		हाल SMB2_CANCEL:
		हाल SMB2_CLOSE:
		हाल SMB2_OPLOCK_BREAK:
			वापस -EAGAIN;
		पूर्ण

		rc = रुको_event_पूर्णांकerruptible_समयout(server->response_q,
						      (server->tcpStatus != CअगरsNeedReconnect),
						      10 * HZ);
		अगर (rc < 0) अणु
			cअगरs_dbg(FYI, "%s: aborting reconnect due to a received signal by the process\n",
				 __func__);
			वापस -ERESTARTSYS;
		पूर्ण

		/* are we still trying to reconnect? */
		अगर (server->tcpStatus != CअगरsNeedReconnect)
			अवरोध;

		अगर (retries && --retries)
			जारी;

		/*
		 * on "soft" mounts we रुको once. Hard mounts keep
		 * retrying until process is समाप्तed or server comes
		 * back on-line
		 */
		अगर (!tcon->retry) अणु
			cअगरs_dbg(FYI, "gave up waiting on reconnect in smb_init\n");
			वापस -EHOSTDOWN;
		पूर्ण
		retries = server->nr_tarमाला_लो;
	पूर्ण

	अगर (!tcon->ses->need_reconnect && !tcon->need_reconnect)
		वापस 0;

	nls_codepage = load_nls_शेष();

	/*
	 * need to prevent multiple thपढ़ोs trying to simultaneously reconnect
	 * the same SMB session
	 */
	mutex_lock(&tcon->ses->session_mutex);

	/*
	 * Recheck after acquire mutex. If another thपढ़ो is negotiating
	 * and the server never sends an answer the socket will be बंदd
	 * and tcpStatus set to reconnect.
	 */
	अगर (server->tcpStatus == CअगरsNeedReconnect) अणु
		rc = -EHOSTDOWN;
		mutex_unlock(&tcon->ses->session_mutex);
		जाओ out;
	पूर्ण

	/*
	 * If we are reconnecting an extra channel, bind
	 */
	अगर (server->is_channel) अणु
		ses->binding = true;
		ses->binding_chan = cअगरs_ses_find_chan(ses, server);
	पूर्ण

	rc = cअगरs_negotiate_protocol(0, tcon->ses);
	अगर (!rc && tcon->ses->need_reconnect) अणु
		rc = cअगरs_setup_session(0, tcon->ses, nls_codepage);
		अगर ((rc == -EACCES) && !tcon->retry) अणु
			rc = -EHOSTDOWN;
			ses->binding = false;
			ses->binding_chan = शून्य;
			mutex_unlock(&tcon->ses->session_mutex);
			जाओ failed;
		पूर्ण
	पूर्ण
	/*
	 * End of channel binding
	 */
	ses->binding = false;
	ses->binding_chan = शून्य;

	अगर (rc || !tcon->need_reconnect) अणु
		mutex_unlock(&tcon->ses->session_mutex);
		जाओ out;
	पूर्ण

	cअगरs_mark_खोलो_files_invalid(tcon);
	अगर (tcon->use_persistent)
		tcon->need_reखोलो_files = true;

	rc = cअगरs_tree_connect(0, tcon, nls_codepage);
	mutex_unlock(&tcon->ses->session_mutex);

	cअगरs_dbg(FYI, "reconnect tcon rc = %d\n", rc);
	अगर (rc) अणु
		/* If sess reconnected but tcon didn't, something strange ... */
		pr_warn_once("reconnect tcon failed rc = %d\n", rc);
		जाओ out;
	पूर्ण

	अगर (smb2_command != SMB2_INTERNAL_CMD)
		mod_delayed_work(cअगरsiod_wq, &server->reconnect, 0);

	atomic_inc(&tconInfoReconnectCount);
out:
	/*
	 * Check अगर handle based operation so we know whether we can जारी
	 * or not without वापसing to caller to reset file handle.
	 */
	/*
	 * BB Is flush करोne by server on drop of tcp session? Should we special
	 * हाल it and skip above?
	 */
	चयन (smb2_command) अणु
	हाल SMB2_FLUSH:
	हाल SMB2_READ:
	हाल SMB2_WRITE:
	हाल SMB2_LOCK:
	हाल SMB2_IOCTL:
	हाल SMB2_QUERY_सूचीECTORY:
	हाल SMB2_CHANGE_NOTIFY:
	हाल SMB2_QUERY_INFO:
	हाल SMB2_SET_INFO:
		rc = -EAGAIN;
	पूर्ण
failed:
	unload_nls(nls_codepage);
	वापस rc;
पूर्ण

अटल व्योम
fill_small_buf(__le16 smb2_command, काष्ठा cअगरs_tcon *tcon,
	       काष्ठा TCP_Server_Info *server,
	       व्योम *buf,
	       अचिन्हित पूर्णांक *total_len)
अणु
	काष्ठा smb2_sync_pdu *spdu = (काष्ठा smb2_sync_pdu *)buf;
	/* lookup word count ie StructureSize from table */
	__u16 parmsize = smb2_req_काष्ठा_sizes[le16_to_cpu(smb2_command)];

	/*
	 * smaller than SMALL_BUFFER_SIZE but bigger than fixed area of
	 * largest operations (Create)
	 */
	स_रखो(buf, 0, 256);

	smb2_hdr_assemble(&spdu->sync_hdr, smb2_command, tcon, server);
	spdu->StructureSize2 = cpu_to_le16(parmsize);

	*total_len = parmsize + माप(काष्ठा smb2_sync_hdr);
पूर्ण

/*
 * Allocate and वापस poपूर्णांकer to an SMB request hdr, and set basic
 * SMB inक्रमmation in the SMB header. If the वापस code is zero, this
 * function must have filled in request_buf poपूर्णांकer.
 */
अटल पूर्णांक __smb2_plain_req_init(__le16 smb2_command, काष्ठा cअगरs_tcon *tcon,
				 काष्ठा TCP_Server_Info *server,
				 व्योम **request_buf, अचिन्हित पूर्णांक *total_len)
अणु
	/* BB eventually चयन this to SMB2 specअगरic small buf size */
	अगर (smb2_command == SMB2_SET_INFO)
		*request_buf = cअगरs_buf_get();
	अन्यथा
		*request_buf = cअगरs_small_buf_get();
	अगर (*request_buf == शून्य) अणु
		/* BB should we add a retry in here अगर not a ग_लिखोpage? */
		वापस -ENOMEM;
	पूर्ण

	fill_small_buf(smb2_command, tcon, server,
		       (काष्ठा smb2_sync_hdr *)(*request_buf),
		       total_len);

	अगर (tcon != शून्य) अणु
		uपूर्णांक16_t com_code = le16_to_cpu(smb2_command);
		cअगरs_stats_inc(&tcon->stats.smb2_stats.smb2_com_sent[com_code]);
		cअगरs_stats_inc(&tcon->num_smbs_sent);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smb2_plain_req_init(__le16 smb2_command, काष्ठा cअगरs_tcon *tcon,
			       काष्ठा TCP_Server_Info *server,
			       व्योम **request_buf, अचिन्हित पूर्णांक *total_len)
अणु
	पूर्णांक rc;

	rc = smb2_reconnect(smb2_command, tcon, server);
	अगर (rc)
		वापस rc;

	वापस __smb2_plain_req_init(smb2_command, tcon, server, request_buf,
				     total_len);
पूर्ण

अटल पूर्णांक smb2_ioctl_req_init(u32 opcode, काष्ठा cअगरs_tcon *tcon,
			       काष्ठा TCP_Server_Info *server,
			       व्योम **request_buf, अचिन्हित पूर्णांक *total_len)
अणु
	/* Skip reconnect only क्रम FSCTL_VALIDATE_NEGOTIATE_INFO IOCTLs */
	अगर (opcode == FSCTL_VALIDATE_NEGOTIATE_INFO) अणु
		वापस __smb2_plain_req_init(SMB2_IOCTL, tcon, server,
					     request_buf, total_len);
	पूर्ण
	वापस smb2_plain_req_init(SMB2_IOCTL, tcon, server,
				   request_buf, total_len);
पूर्ण

/* For explanation of negotiate contexts see MS-SMB2 section 2.2.3.1 */

अटल व्योम
build_preauth_ctxt(काष्ठा smb2_preauth_neg_context *pneg_ctxt)
अणु
	pneg_ctxt->ContextType = SMB2_PREAUTH_INTEGRITY_CAPABILITIES;
	pneg_ctxt->DataLength = cpu_to_le16(38);
	pneg_ctxt->HashAlgorithmCount = cpu_to_le16(1);
	pneg_ctxt->SaltLength = cpu_to_le16(SMB311_LINUX_CLIENT_SALT_SIZE);
	get_अक्रमom_bytes(pneg_ctxt->Salt, SMB311_LINUX_CLIENT_SALT_SIZE);
	pneg_ctxt->HashAlgorithms = SMB2_PREAUTH_INTEGRITY_SHA512;
पूर्ण

अटल व्योम
build_compression_ctxt(काष्ठा smb2_compression_capabilities_context *pneg_ctxt)
अणु
	pneg_ctxt->ContextType = SMB2_COMPRESSION_CAPABILITIES;
	pneg_ctxt->DataLength =
		cpu_to_le16(माप(काष्ठा smb2_compression_capabilities_context)
			  - माप(काष्ठा smb2_neg_context));
	pneg_ctxt->CompressionAlgorithmCount = cpu_to_le16(3);
	pneg_ctxt->CompressionAlgorithms[0] = SMB3_COMPRESS_LZ77;
	pneg_ctxt->CompressionAlgorithms[1] = SMB3_COMPRESS_LZ77_HUFF;
	pneg_ctxt->CompressionAlgorithms[2] = SMB3_COMPRESS_LZNT1;
पूर्ण

अटल व्योम
build_encrypt_ctxt(काष्ठा smb2_encryption_neg_context *pneg_ctxt)
अणु
	pneg_ctxt->ContextType = SMB2_ENCRYPTION_CAPABILITIES;
	अगर (require_gcm_256) अणु
		pneg_ctxt->DataLength = cpu_to_le16(4); /* Cipher Count + 1 cipher */
		pneg_ctxt->CipherCount = cpu_to_le16(1);
		pneg_ctxt->Ciphers[0] = SMB2_ENCRYPTION_AES256_GCM;
	पूर्ण अन्यथा अगर (enable_gcm_256) अणु
		pneg_ctxt->DataLength = cpu_to_le16(8); /* Cipher Count + 3 ciphers */
		pneg_ctxt->CipherCount = cpu_to_le16(3);
		pneg_ctxt->Ciphers[0] = SMB2_ENCRYPTION_AES128_GCM;
		pneg_ctxt->Ciphers[1] = SMB2_ENCRYPTION_AES256_GCM;
		pneg_ctxt->Ciphers[2] = SMB2_ENCRYPTION_AES128_CCM;
	पूर्ण अन्यथा अणु
		pneg_ctxt->DataLength = cpu_to_le16(6); /* Cipher Count + 2 ciphers */
		pneg_ctxt->CipherCount = cpu_to_le16(2);
		pneg_ctxt->Ciphers[0] = SMB2_ENCRYPTION_AES128_GCM;
		pneg_ctxt->Ciphers[1] = SMB2_ENCRYPTION_AES128_CCM;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक
build_netname_ctxt(काष्ठा smb2_netname_neg_context *pneg_ctxt, अक्षर *hostname)
अणु
	काष्ठा nls_table *cp = load_nls_शेष();

	pneg_ctxt->ContextType = SMB2_NETNAME_NEGOTIATE_CONTEXT_ID;

	/* copy up to max of first 100 bytes of server name to NetName field */
	pneg_ctxt->DataLength = cpu_to_le16(2 * cअगरs_strtoUTF16(pneg_ctxt->NetName, hostname, 100, cp));
	/* context size is DataLength + minimal smb2_neg_context */
	वापस DIV_ROUND_UP(le16_to_cpu(pneg_ctxt->DataLength) +
			माप(काष्ठा smb2_neg_context), 8) * 8;
पूर्ण

अटल व्योम
build_posix_ctxt(काष्ठा smb2_posix_neg_context *pneg_ctxt)
अणु
	pneg_ctxt->ContextType = SMB2_POSIX_EXTENSIONS_AVAILABLE;
	pneg_ctxt->DataLength = cpu_to_le16(POSIX_CTXT_DATA_LEN);
	/* SMB2_CREATE_TAG_POSIX is "0x93AD25509CB411E7B42383DE968BCD7C" */
	pneg_ctxt->Name[0] = 0x93;
	pneg_ctxt->Name[1] = 0xAD;
	pneg_ctxt->Name[2] = 0x25;
	pneg_ctxt->Name[3] = 0x50;
	pneg_ctxt->Name[4] = 0x9C;
	pneg_ctxt->Name[5] = 0xB4;
	pneg_ctxt->Name[6] = 0x11;
	pneg_ctxt->Name[7] = 0xE7;
	pneg_ctxt->Name[8] = 0xB4;
	pneg_ctxt->Name[9] = 0x23;
	pneg_ctxt->Name[10] = 0x83;
	pneg_ctxt->Name[11] = 0xDE;
	pneg_ctxt->Name[12] = 0x96;
	pneg_ctxt->Name[13] = 0x8B;
	pneg_ctxt->Name[14] = 0xCD;
	pneg_ctxt->Name[15] = 0x7C;
पूर्ण

अटल व्योम
assemble_neg_contexts(काष्ठा smb2_negotiate_req *req,
		      काष्ठा TCP_Server_Info *server, अचिन्हित पूर्णांक *total_len)
अणु
	अक्षर *pneg_ctxt;
	अचिन्हित पूर्णांक ctxt_len;

	अगर (*total_len > 200) अणु
		/* In हाल length corrupted करोn't want to overrun smb buffer */
		cअगरs_server_dbg(VFS, "Bad frame length assembling neg contexts\n");
		वापस;
	पूर्ण

	/*
	 * round up total_len of fixed part of SMB3 negotiate request to 8
	 * byte boundary beक्रमe adding negotiate contexts
	 */
	*total_len = roundup(*total_len, 8);

	pneg_ctxt = (*total_len) + (अक्षर *)req;
	req->NegotiateContextOffset = cpu_to_le32(*total_len);

	build_preauth_ctxt((काष्ठा smb2_preauth_neg_context *)pneg_ctxt);
	ctxt_len = DIV_ROUND_UP(माप(काष्ठा smb2_preauth_neg_context), 8) * 8;
	*total_len += ctxt_len;
	pneg_ctxt += ctxt_len;

	build_encrypt_ctxt((काष्ठा smb2_encryption_neg_context *)pneg_ctxt);
	ctxt_len = DIV_ROUND_UP(माप(काष्ठा smb2_encryption_neg_context), 8) * 8;
	*total_len += ctxt_len;
	pneg_ctxt += ctxt_len;

	अगर (server->compress_algorithm) अणु
		build_compression_ctxt((काष्ठा smb2_compression_capabilities_context *)
				pneg_ctxt);
		ctxt_len = DIV_ROUND_UP(
			माप(काष्ठा smb2_compression_capabilities_context),
				8) * 8;
		*total_len += ctxt_len;
		pneg_ctxt += ctxt_len;
		req->NegotiateContextCount = cpu_to_le16(5);
	पूर्ण अन्यथा
		req->NegotiateContextCount = cpu_to_le16(4);

	ctxt_len = build_netname_ctxt((काष्ठा smb2_netname_neg_context *)pneg_ctxt,
					server->hostname);
	*total_len += ctxt_len;
	pneg_ctxt += ctxt_len;

	build_posix_ctxt((काष्ठा smb2_posix_neg_context *)pneg_ctxt);
	*total_len += माप(काष्ठा smb2_posix_neg_context);
पूर्ण

अटल व्योम decode_preauth_context(काष्ठा smb2_preauth_neg_context *ctxt)
अणु
	अचिन्हित पूर्णांक len = le16_to_cpu(ctxt->DataLength);

	/* If invalid preauth context warn but use what we requested, SHA-512 */
	अगर (len < MIN_PREAUTH_CTXT_DATA_LEN) अणु
		pr_warn_once("server sent bad preauth context\n");
		वापस;
	पूर्ण अन्यथा अगर (len < MIN_PREAUTH_CTXT_DATA_LEN + le16_to_cpu(ctxt->SaltLength)) अणु
		pr_warn_once("server sent invalid SaltLength\n");
		वापस;
	पूर्ण
	अगर (le16_to_cpu(ctxt->HashAlgorithmCount) != 1)
		pr_warn_once("Invalid SMB3 hash algorithm count\n");
	अगर (ctxt->HashAlgorithms != SMB2_PREAUTH_INTEGRITY_SHA512)
		pr_warn_once("unknown SMB3 hash algorithm\n");
पूर्ण

अटल व्योम decode_compress_ctx(काष्ठा TCP_Server_Info *server,
			 काष्ठा smb2_compression_capabilities_context *ctxt)
अणु
	अचिन्हित पूर्णांक len = le16_to_cpu(ctxt->DataLength);

	/* माप compress context is a one element compression capbility काष्ठा */
	अगर (len < 10) अणु
		pr_warn_once("server sent bad compression cntxt\n");
		वापस;
	पूर्ण
	अगर (le16_to_cpu(ctxt->CompressionAlgorithmCount) != 1) अणु
		pr_warn_once("Invalid SMB3 compress algorithm count\n");
		वापस;
	पूर्ण
	अगर (le16_to_cpu(ctxt->CompressionAlgorithms[0]) > 3) अणु
		pr_warn_once("unknown compression algorithm\n");
		वापस;
	पूर्ण
	server->compress_algorithm = ctxt->CompressionAlgorithms[0];
पूर्ण

अटल पूर्णांक decode_encrypt_ctx(काष्ठा TCP_Server_Info *server,
			      काष्ठा smb2_encryption_neg_context *ctxt)
अणु
	अचिन्हित पूर्णांक len = le16_to_cpu(ctxt->DataLength);

	cअगरs_dbg(FYI, "decode SMB3.11 encryption neg context of len %d\n", len);
	अगर (len < MIN_ENCRYPT_CTXT_DATA_LEN) अणु
		pr_warn_once("server sent bad crypto ctxt len\n");
		वापस -EINVAL;
	पूर्ण

	अगर (le16_to_cpu(ctxt->CipherCount) != 1) अणु
		pr_warn_once("Invalid SMB3.11 cipher count\n");
		वापस -EINVAL;
	पूर्ण
	cअगरs_dbg(FYI, "SMB311 cipher type:%d\n", le16_to_cpu(ctxt->Ciphers[0]));
	अगर (require_gcm_256) अणु
		अगर (ctxt->Ciphers[0] != SMB2_ENCRYPTION_AES256_GCM) अणु
			cअगरs_dbg(VFS, "Server does not support requested encryption type (AES256 GCM)\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अगर (ctxt->Ciphers[0] == 0) अणु
		/*
		 * e.g. अगर server only supported AES256_CCM (very unlikely)
		 * or server supported no encryption types or had all disabled.
		 * Since GLOBAL_CAP_ENCRYPTION will be not set, in the हाल
		 * in which mount requested encryption ("seal") checks later
		 * on during tree connection will वापस proper rc, but अगर
		 * seal not requested by client, since server is allowed to
		 * वापस 0 to indicate no supported cipher, we can't fail here
		 */
		server->cipher_type = 0;
		server->capabilities &= ~SMB2_GLOBAL_CAP_ENCRYPTION;
		pr_warn_once("Server does not support requested encryption types\n");
		वापस 0;
	पूर्ण अन्यथा अगर ((ctxt->Ciphers[0] != SMB2_ENCRYPTION_AES128_CCM) &&
		   (ctxt->Ciphers[0] != SMB2_ENCRYPTION_AES128_GCM) &&
		   (ctxt->Ciphers[0] != SMB2_ENCRYPTION_AES256_GCM)) अणु
		/* server वापसed a cipher we didn't ask क्रम */
		pr_warn_once("Invalid SMB3.11 cipher returned\n");
		वापस -EINVAL;
	पूर्ण
	server->cipher_type = ctxt->Ciphers[0];
	server->capabilities |= SMB2_GLOBAL_CAP_ENCRYPTION;
	वापस 0;
पूर्ण

अटल पूर्णांक smb311_decode_neg_context(काष्ठा smb2_negotiate_rsp *rsp,
				     काष्ठा TCP_Server_Info *server,
				     अचिन्हित पूर्णांक len_of_smb)
अणु
	काष्ठा smb2_neg_context *pctx;
	अचिन्हित पूर्णांक offset = le32_to_cpu(rsp->NegotiateContextOffset);
	अचिन्हित पूर्णांक ctxt_cnt = le16_to_cpu(rsp->NegotiateContextCount);
	अचिन्हित पूर्णांक len_of_ctxts, i;
	पूर्णांक rc = 0;

	cअगरs_dbg(FYI, "decoding %d negotiate contexts\n", ctxt_cnt);
	अगर (len_of_smb <= offset) अणु
		cअगरs_server_dbg(VFS, "Invalid response: negotiate context offset\n");
		वापस -EINVAL;
	पूर्ण

	len_of_ctxts = len_of_smb - offset;

	क्रम (i = 0; i < ctxt_cnt; i++) अणु
		पूर्णांक clen;
		/* check that offset is not beyond end of SMB */
		अगर (len_of_ctxts == 0)
			अवरोध;

		अगर (len_of_ctxts < माप(काष्ठा smb2_neg_context))
			अवरोध;

		pctx = (काष्ठा smb2_neg_context *)(offset + (अक्षर *)rsp);
		clen = le16_to_cpu(pctx->DataLength);
		अगर (clen > len_of_ctxts)
			अवरोध;

		अगर (pctx->ContextType == SMB2_PREAUTH_INTEGRITY_CAPABILITIES)
			decode_preauth_context(
				(काष्ठा smb2_preauth_neg_context *)pctx);
		अन्यथा अगर (pctx->ContextType == SMB2_ENCRYPTION_CAPABILITIES)
			rc = decode_encrypt_ctx(server,
				(काष्ठा smb2_encryption_neg_context *)pctx);
		अन्यथा अगर (pctx->ContextType == SMB2_COMPRESSION_CAPABILITIES)
			decode_compress_ctx(server,
				(काष्ठा smb2_compression_capabilities_context *)pctx);
		अन्यथा अगर (pctx->ContextType == SMB2_POSIX_EXTENSIONS_AVAILABLE)
			server->posix_ext_supported = true;
		अन्यथा
			cअगरs_server_dbg(VFS, "unknown negcontext of type %d ignored\n",
				le16_to_cpu(pctx->ContextType));

		अगर (rc)
			अवरोध;
		/* offsets must be 8 byte aligned */
		clen = (clen + 7) & ~0x7;
		offset += clen + माप(काष्ठा smb2_neg_context);
		len_of_ctxts -= clen;
	पूर्ण
	वापस rc;
पूर्ण

अटल काष्ठा create_posix *
create_posix_buf(umode_t mode)
अणु
	काष्ठा create_posix *buf;

	buf = kzalloc(माप(काष्ठा create_posix),
			GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	buf->ccontext.DataOffset =
		cpu_to_le16(दुरत्व(काष्ठा create_posix, Mode));
	buf->ccontext.DataLength = cpu_to_le32(4);
	buf->ccontext.NameOffset =
		cpu_to_le16(दुरत्व(काष्ठा create_posix, Name));
	buf->ccontext.NameLength = cpu_to_le16(16);

	/* SMB2_CREATE_TAG_POSIX is "0x93AD25509CB411E7B42383DE968BCD7C" */
	buf->Name[0] = 0x93;
	buf->Name[1] = 0xAD;
	buf->Name[2] = 0x25;
	buf->Name[3] = 0x50;
	buf->Name[4] = 0x9C;
	buf->Name[5] = 0xB4;
	buf->Name[6] = 0x11;
	buf->Name[7] = 0xE7;
	buf->Name[8] = 0xB4;
	buf->Name[9] = 0x23;
	buf->Name[10] = 0x83;
	buf->Name[11] = 0xDE;
	buf->Name[12] = 0x96;
	buf->Name[13] = 0x8B;
	buf->Name[14] = 0xCD;
	buf->Name[15] = 0x7C;
	buf->Mode = cpu_to_le32(mode);
	cअगरs_dbg(FYI, "mode on posix create 0%o\n", mode);
	वापस buf;
पूर्ण

अटल पूर्णांक
add_posix_context(काष्ठा kvec *iov, अचिन्हित पूर्णांक *num_iovec, umode_t mode)
अणु
	काष्ठा smb2_create_req *req = iov[0].iov_base;
	अचिन्हित पूर्णांक num = *num_iovec;

	iov[num].iov_base = create_posix_buf(mode);
	अगर (mode == ACL_NO_MODE)
		cअगरs_dbg(FYI, "Invalid mode\n");
	अगर (iov[num].iov_base == शून्य)
		वापस -ENOMEM;
	iov[num].iov_len = माप(काष्ठा create_posix);
	अगर (!req->CreateContextsOffset)
		req->CreateContextsOffset = cpu_to_le32(
				माप(काष्ठा smb2_create_req) +
				iov[num - 1].iov_len);
	le32_add_cpu(&req->CreateContextsLength, माप(काष्ठा create_posix));
	*num_iovec = num + 1;
	वापस 0;
पूर्ण


/*
 *
 *	SMB2 Worker functions follow:
 *
 *	The general काष्ठाure of the worker functions is:
 *	1) Call smb2_init (assembles SMB2 header)
 *	2) Initialize SMB2 command specअगरic fields in fixed length area of SMB
 *	3) Call smb_sendrcv2 (sends request on socket and रुकोs क्रम response)
 *	4) Decode SMB2 command specअगरic fields in the fixed length area
 *	5) Decode variable length data area (अगर any क्रम this SMB2 command type)
 *	6) Call मुक्त smb buffer
 *	7) वापस
 *
 */

पूर्णांक
SMB2_negotiate(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_negotiate_req *req;
	काष्ठा smb2_negotiate_rsp *rsp;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov;
	पूर्णांक rc = 0;
	पूर्णांक resp_buftype;
	काष्ठा TCP_Server_Info *server = cअगरs_ses_server(ses);
	पूर्णांक blob_offset, blob_length;
	अक्षर *security_blob;
	पूर्णांक flags = CIFS_NEG_OP;
	अचिन्हित पूर्णांक total_len;

	cअगरs_dbg(FYI, "Negotiate protocol\n");

	अगर (!server) अणु
		WARN(1, "%s: server is NULL!\n", __func__);
		वापस -EIO;
	पूर्ण

	rc = smb2_plain_req_init(SMB2_NEGOTIATE, शून्य, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	req->sync_hdr.SessionId = 0;

	स_रखो(server->preauth_sha_hash, 0, SMB2_PREAUTH_HASH_SIZE);
	स_रखो(ses->preauth_sha_hash, 0, SMB2_PREAUTH_HASH_SIZE);

	अगर (म_भेद(server->vals->version_string,
		   SMB3ANY_VERSION_STRING) == 0) अणु
		req->Dialects[0] = cpu_to_le16(SMB30_PROT_ID);
		req->Dialects[1] = cpu_to_le16(SMB302_PROT_ID);
		req->Dialects[2] = cpu_to_le16(SMB311_PROT_ID);
		req->DialectCount = cpu_to_le16(3);
		total_len += 6;
	पूर्ण अन्यथा अगर (म_भेद(server->vals->version_string,
		   SMBDEFAULT_VERSION_STRING) == 0) अणु
		req->Dialects[0] = cpu_to_le16(SMB21_PROT_ID);
		req->Dialects[1] = cpu_to_le16(SMB30_PROT_ID);
		req->Dialects[2] = cpu_to_le16(SMB302_PROT_ID);
		req->Dialects[3] = cpu_to_le16(SMB311_PROT_ID);
		req->DialectCount = cpu_to_le16(4);
		total_len += 8;
	पूर्ण अन्यथा अणु
		/* otherwise send specअगरic dialect */
		req->Dialects[0] = cpu_to_le16(server->vals->protocol_id);
		req->DialectCount = cpu_to_le16(1);
		total_len += 2;
	पूर्ण

	/* only one of SMB2 signing flags may be set in SMB2 request */
	अगर (ses->sign)
		req->SecurityMode = cpu_to_le16(SMB2_NEGOTIATE_SIGNING_REQUIRED);
	अन्यथा अगर (global_secflags & CIFSSEC_MAY_SIGN)
		req->SecurityMode = cpu_to_le16(SMB2_NEGOTIATE_SIGNING_ENABLED);
	अन्यथा
		req->SecurityMode = 0;

	req->Capabilities = cpu_to_le32(server->vals->req_capabilities);
	अगर (ses->chan_max > 1)
		req->Capabilities |= cpu_to_le32(SMB2_GLOBAL_CAP_MULTI_CHANNEL);

	/* ClientGUID must be zero क्रम SMB2.02 dialect */
	अगर (server->vals->protocol_id == SMB20_PROT_ID)
		स_रखो(req->ClientGUID, 0, SMB2_CLIENT_GUID_SIZE);
	अन्यथा अणु
		स_नकल(req->ClientGUID, server->client_guid,
			SMB2_CLIENT_GUID_SIZE);
		अगर ((server->vals->protocol_id == SMB311_PROT_ID) ||
		    (म_भेद(server->vals->version_string,
		     SMB3ANY_VERSION_STRING) == 0) ||
		    (म_भेद(server->vals->version_string,
		     SMBDEFAULT_VERSION_STRING) == 0))
			assemble_neg_contexts(req, server, &total_len);
	पूर्ण
	iov[0].iov_base = (अक्षर *)req;
	iov[0].iov_len = total_len;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags, &rsp_iov);
	cअगरs_small_buf_release(req);
	rsp = (काष्ठा smb2_negotiate_rsp *)rsp_iov.iov_base;
	/*
	 * No tcon so can't करो
	 * cअगरs_stats_inc(&tcon->stats.smb2_stats.smb2_com_fail[SMB2...]);
	 */
	अगर (rc == -EOPNOTSUPP) अणु
		cअगरs_server_dbg(VFS, "Dialect not supported by server. Consider  specifying vers=1.0 or vers=2.0 on mount for accessing older servers\n");
		जाओ neg_निकास;
	पूर्ण अन्यथा अगर (rc != 0)
		जाओ neg_निकास;

	अगर (म_भेद(server->vals->version_string,
		   SMB3ANY_VERSION_STRING) == 0) अणु
		अगर (rsp->DialectRevision == cpu_to_le16(SMB20_PROT_ID)) अणु
			cअगरs_server_dbg(VFS,
				"SMB2 dialect returned but not requested\n");
			वापस -EIO;
		पूर्ण अन्यथा अगर (rsp->DialectRevision == cpu_to_le16(SMB21_PROT_ID)) अणु
			cअगरs_server_dbg(VFS,
				"SMB2.1 dialect returned but not requested\n");
			वापस -EIO;
		पूर्ण अन्यथा अगर (rsp->DialectRevision == cpu_to_le16(SMB311_PROT_ID)) अणु
			/* ops set to 3.0 by शेष क्रम शेष so update */
			server->ops = &smb311_operations;
			server->vals = &smb311_values;
		पूर्ण
	पूर्ण अन्यथा अगर (म_भेद(server->vals->version_string,
		   SMBDEFAULT_VERSION_STRING) == 0) अणु
		अगर (rsp->DialectRevision == cpu_to_le16(SMB20_PROT_ID)) अणु
			cअगरs_server_dbg(VFS,
				"SMB2 dialect returned but not requested\n");
			वापस -EIO;
		पूर्ण अन्यथा अगर (rsp->DialectRevision == cpu_to_le16(SMB21_PROT_ID)) अणु
			/* ops set to 3.0 by शेष क्रम शेष so update */
			server->ops = &smb21_operations;
			server->vals = &smb21_values;
		पूर्ण अन्यथा अगर (rsp->DialectRevision == cpu_to_le16(SMB311_PROT_ID)) अणु
			server->ops = &smb311_operations;
			server->vals = &smb311_values;
		पूर्ण
	पूर्ण अन्यथा अगर (le16_to_cpu(rsp->DialectRevision) !=
				server->vals->protocol_id) अणु
		/* अगर requested single dialect ensure वापसed dialect matched */
		cअगरs_server_dbg(VFS, "Invalid 0x%x dialect returned: not requested\n",
				le16_to_cpu(rsp->DialectRevision));
		वापस -EIO;
	पूर्ण

	cअगरs_dbg(FYI, "mode 0x%x\n", rsp->SecurityMode);

	अगर (rsp->DialectRevision == cpu_to_le16(SMB20_PROT_ID))
		cअगरs_dbg(FYI, "negotiated smb2.0 dialect\n");
	अन्यथा अगर (rsp->DialectRevision == cpu_to_le16(SMB21_PROT_ID))
		cअगरs_dbg(FYI, "negotiated smb2.1 dialect\n");
	अन्यथा अगर (rsp->DialectRevision == cpu_to_le16(SMB30_PROT_ID))
		cअगरs_dbg(FYI, "negotiated smb3.0 dialect\n");
	अन्यथा अगर (rsp->DialectRevision == cpu_to_le16(SMB302_PROT_ID))
		cअगरs_dbg(FYI, "negotiated smb3.02 dialect\n");
	अन्यथा अगर (rsp->DialectRevision == cpu_to_le16(SMB311_PROT_ID))
		cअगरs_dbg(FYI, "negotiated smb3.1.1 dialect\n");
	अन्यथा अणु
		cअगरs_server_dbg(VFS, "Invalid dialect returned by server 0x%x\n",
				le16_to_cpu(rsp->DialectRevision));
		rc = -EIO;
		जाओ neg_निकास;
	पूर्ण
	server->dialect = le16_to_cpu(rsp->DialectRevision);

	/*
	 * Keep a copy of the hash after negprot. This hash will be
	 * the starting hash value क्रम all sessions made from this
	 * server.
	 */
	स_नकल(server->preauth_sha_hash, ses->preauth_sha_hash,
	       SMB2_PREAUTH_HASH_SIZE);

	/* SMB2 only has an extended negflavor */
	server->negflavor = CIFS_NEGFLAVOR_EXTENDED;
	/* set it to the maximum buffer size value we can send with 1 credit */
	server->maxBuf = min_t(अचिन्हित पूर्णांक, le32_to_cpu(rsp->MaxTransactSize),
			       SMB2_MAX_BUFFER_SIZE);
	server->max_पढ़ो = le32_to_cpu(rsp->MaxReadSize);
	server->max_ग_लिखो = le32_to_cpu(rsp->MaxWriteSize);
	server->sec_mode = le16_to_cpu(rsp->SecurityMode);
	अगर ((server->sec_mode & SMB2_SEC_MODE_FLAGS_ALL) != server->sec_mode)
		cअगरs_dbg(FYI, "Server returned unexpected security mode 0x%x\n",
				server->sec_mode);
	server->capabilities = le32_to_cpu(rsp->Capabilities);
	/* Internal types */
	server->capabilities |= SMB2_NT_FIND | SMB2_LARGE_खाताS;

	/*
	 * SMB3.0 supports only 1 cipher and करोesn't have a encryption neg context
	 * Set the cipher type manually.
	 */
	अगर (server->dialect == SMB30_PROT_ID && (server->capabilities & SMB2_GLOBAL_CAP_ENCRYPTION))
		server->cipher_type = SMB2_ENCRYPTION_AES128_CCM;

	security_blob = smb2_get_data_area_len(&blob_offset, &blob_length,
					       (काष्ठा smb2_sync_hdr *)rsp);
	/*
	 * See MS-SMB2 section 2.2.4: अगर no blob, client picks शेष which
	 * क्रम us will be
	 *	ses->sectype = RawNTLMSSP;
	 * but क्रम समय being this is our only auth choice so करोesn't matter.
	 * We just found a server which sets blob length to zero expecting raw.
	 */
	अगर (blob_length == 0) अणु
		cअगरs_dbg(FYI, "missing security blob on negprot\n");
		server->sec_ntlmssp = true;
	पूर्ण

	rc = cअगरs_enable_signing(server, ses->sign);
	अगर (rc)
		जाओ neg_निकास;
	अगर (blob_length) अणु
		rc = decode_negTokenInit(security_blob, blob_length, server);
		अगर (rc == 1)
			rc = 0;
		अन्यथा अगर (rc == 0)
			rc = -EIO;
	पूर्ण

	अगर (rsp->DialectRevision == cpu_to_le16(SMB311_PROT_ID)) अणु
		अगर (rsp->NegotiateContextCount)
			rc = smb311_decode_neg_context(rsp, server,
						       rsp_iov.iov_len);
		अन्यथा
			cअगरs_server_dbg(VFS, "Missing expected negotiate contexts\n");
	पूर्ण
neg_निकास:
	मुक्त_rsp_buf(resp_buftype, rsp);
	वापस rc;
पूर्ण

पूर्णांक smb3_validate_negotiate(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon)
अणु
	पूर्णांक rc;
	काष्ठा validate_negotiate_info_req *pneg_inbuf;
	काष्ठा validate_negotiate_info_rsp *pneg_rsp = शून्य;
	u32 rsplen;
	u32 inbuflen; /* max of 4 dialects */
	काष्ठा TCP_Server_Info *server = tcon->ses->server;

	cअगरs_dbg(FYI, "validate negotiate\n");

	/* In SMB3.11 preauth पूर्णांकegrity supersedes validate negotiate */
	अगर (server->dialect == SMB311_PROT_ID)
		वापस 0;

	/*
	 * validation ioctl must be चिन्हित, so no poपूर्णांक sending this अगर we
	 * can not sign it (ie are not known user).  Even अगर signing is not
	 * required (enabled but not negotiated), in those हालs we selectively
	 * sign just this, the first and only चिन्हित request on a connection.
	 * Having validation of negotiate info  helps reduce attack vectors.
	 */
	अगर (tcon->ses->session_flags & SMB2_SESSION_FLAG_IS_GUEST)
		वापस 0; /* validation requires signing */

	अगर (tcon->ses->user_name == शून्य) अणु
		cअगरs_dbg(FYI, "Can't validate negotiate: null user mount\n");
		वापस 0; /* validation requires signing */
	पूर्ण

	अगर (tcon->ses->session_flags & SMB2_SESSION_FLAG_IS_शून्य)
		cअगरs_tcon_dbg(VFS, "Unexpected null user (anonymous) auth flag sent by server\n");

	pneg_inbuf = kदो_स्मृति(माप(*pneg_inbuf), GFP_NOFS);
	अगर (!pneg_inbuf)
		वापस -ENOMEM;

	pneg_inbuf->Capabilities =
			cpu_to_le32(server->vals->req_capabilities);
	अगर (tcon->ses->chan_max > 1)
		pneg_inbuf->Capabilities |= cpu_to_le32(SMB2_GLOBAL_CAP_MULTI_CHANNEL);

	स_नकल(pneg_inbuf->Guid, server->client_guid,
					SMB2_CLIENT_GUID_SIZE);

	अगर (tcon->ses->sign)
		pneg_inbuf->SecurityMode =
			cpu_to_le16(SMB2_NEGOTIATE_SIGNING_REQUIRED);
	अन्यथा अगर (global_secflags & CIFSSEC_MAY_SIGN)
		pneg_inbuf->SecurityMode =
			cpu_to_le16(SMB2_NEGOTIATE_SIGNING_ENABLED);
	अन्यथा
		pneg_inbuf->SecurityMode = 0;


	अगर (म_भेद(server->vals->version_string,
		SMB3ANY_VERSION_STRING) == 0) अणु
		pneg_inbuf->Dialects[0] = cpu_to_le16(SMB30_PROT_ID);
		pneg_inbuf->Dialects[1] = cpu_to_le16(SMB302_PROT_ID);
		pneg_inbuf->Dialects[2] = cpu_to_le16(SMB311_PROT_ID);
		pneg_inbuf->DialectCount = cpu_to_le16(3);
		/* SMB 2.1 not included so subtract one dialect from len */
		inbuflen = माप(*pneg_inbuf) -
				(माप(pneg_inbuf->Dialects[0]));
	पूर्ण अन्यथा अगर (म_भेद(server->vals->version_string,
		SMBDEFAULT_VERSION_STRING) == 0) अणु
		pneg_inbuf->Dialects[0] = cpu_to_le16(SMB21_PROT_ID);
		pneg_inbuf->Dialects[1] = cpu_to_le16(SMB30_PROT_ID);
		pneg_inbuf->Dialects[2] = cpu_to_le16(SMB302_PROT_ID);
		pneg_inbuf->Dialects[3] = cpu_to_le16(SMB311_PROT_ID);
		pneg_inbuf->DialectCount = cpu_to_le16(4);
		/* काष्ठाure is big enough क्रम 4 dialects */
		inbuflen = माप(*pneg_inbuf);
	पूर्ण अन्यथा अणु
		/* otherwise specअगरic dialect was requested */
		pneg_inbuf->Dialects[0] =
			cpu_to_le16(server->vals->protocol_id);
		pneg_inbuf->DialectCount = cpu_to_le16(1);
		/* काष्ठाure is big enough क्रम 3 dialects, sending only 1 */
		inbuflen = माप(*pneg_inbuf) -
				माप(pneg_inbuf->Dialects[0]) * 2;
	पूर्ण

	rc = SMB2_ioctl(xid, tcon, NO_खाता_ID, NO_खाता_ID,
		FSCTL_VALIDATE_NEGOTIATE_INFO, true /* is_fsctl */,
		(अक्षर *)pneg_inbuf, inbuflen, CIFSMaxBufSize,
		(अक्षर **)&pneg_rsp, &rsplen);
	अगर (rc == -EOPNOTSUPP) अणु
		/*
		 * Old Winकरोws versions or Netapp SMB server can वापस
		 * not supported error. Client should accept it.
		 */
		cअगरs_tcon_dbg(VFS, "Server does not support validate negotiate\n");
		rc = 0;
		जाओ out_मुक्त_inbuf;
	पूर्ण अन्यथा अगर (rc != 0) अणु
		cअगरs_tcon_dbg(VFS, "validate protocol negotiate failed: %d\n",
			      rc);
		rc = -EIO;
		जाओ out_मुक्त_inbuf;
	पूर्ण

	rc = -EIO;
	अगर (rsplen != माप(*pneg_rsp)) अणु
		cअगरs_tcon_dbg(VFS, "Invalid protocol negotiate response size: %d\n",
			      rsplen);

		/* relax check since Mac वापसs max bufsize allowed on ioctl */
		अगर (rsplen > CIFSMaxBufSize || rsplen < माप(*pneg_rsp))
			जाओ out_मुक्त_rsp;
	पूर्ण

	/* check validate negotiate info response matches what we got earlier */
	अगर (pneg_rsp->Dialect != cpu_to_le16(server->dialect))
		जाओ vneg_out;

	अगर (pneg_rsp->SecurityMode != cpu_to_le16(server->sec_mode))
		जाओ vneg_out;

	/* करो not validate server guid because not saved at negprot समय yet */

	अगर ((le32_to_cpu(pneg_rsp->Capabilities) | SMB2_NT_FIND |
	      SMB2_LARGE_खाताS) != server->capabilities)
		जाओ vneg_out;

	/* validate negotiate successful */
	rc = 0;
	cअगरs_dbg(FYI, "validate negotiate info successful\n");
	जाओ out_मुक्त_rsp;

vneg_out:
	cअगरs_tcon_dbg(VFS, "protocol revalidation - security settings mismatch\n");
out_मुक्त_rsp:
	kमुक्त(pneg_rsp);
out_मुक्त_inbuf:
	kमुक्त(pneg_inbuf);
	वापस rc;
पूर्ण

क्रमागत securityEnum
smb2_select_sectype(काष्ठा TCP_Server_Info *server, क्रमागत securityEnum requested)
अणु
	चयन (requested) अणु
	हाल Kerberos:
	हाल RawNTLMSSP:
		वापस requested;
	हाल NTLMv2:
		वापस RawNTLMSSP;
	हाल Unspecअगरied:
		अगर (server->sec_ntlmssp &&
			(global_secflags & CIFSSEC_MAY_NTLMSSP))
			वापस RawNTLMSSP;
		अगर ((server->sec_kerberos || server->sec_mskerberos) &&
			(global_secflags & CIFSSEC_MAY_KRB5))
			वापस Kerberos;
		fallthrough;
	शेष:
		वापस Unspecअगरied;
	पूर्ण
पूर्ण

काष्ठा SMB2_sess_data अणु
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरs_ses *ses;
	काष्ठा nls_table *nls_cp;
	व्योम (*func)(काष्ठा SMB2_sess_data *);
	पूर्णांक result;
	u64 previous_session;

	/* we will send the SMB in three pieces:
	 * a fixed length beginning part, an optional
	 * SPNEGO blob (which can be zero length), and a
	 * last part which will include the strings
	 * and rest of bcc area. This allows us to aव्योम
	 * a large buffer 17K allocation
	 */
	पूर्णांक buf0_type;
	काष्ठा kvec iov[2];
पूर्ण;

अटल पूर्णांक
SMB2_sess_alloc_buffer(काष्ठा SMB2_sess_data *sess_data)
अणु
	पूर्णांक rc;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	काष्ठा smb2_sess_setup_req *req;
	काष्ठा TCP_Server_Info *server = cअगरs_ses_server(ses);
	अचिन्हित पूर्णांक total_len;

	rc = smb2_plain_req_init(SMB2_SESSION_SETUP, शून्य, server,
				 (व्योम **) &req,
				 &total_len);
	अगर (rc)
		वापस rc;

	अगर (sess_data->ses->binding) अणु
		req->sync_hdr.SessionId = sess_data->ses->Suid;
		req->sync_hdr.Flags |= SMB2_FLAGS_SIGNED;
		req->PreviousSessionId = 0;
		req->Flags = SMB2_SESSION_REQ_FLAG_BINDING;
	पूर्ण अन्यथा अणु
		/* First session, not a reauthenticate */
		req->sync_hdr.SessionId = 0;
		/*
		 * अगर reconnect, we need to send previous sess id
		 * otherwise it is 0
		 */
		req->PreviousSessionId = sess_data->previous_session;
		req->Flags = 0; /* MBZ */
	पूर्ण

	/* enough to enable echos and oplocks and one max size ग_लिखो */
	req->sync_hdr.CreditRequest = cpu_to_le16(130);

	/* only one of SMB2 signing flags may be set in SMB2 request */
	अगर (server->sign)
		req->SecurityMode = SMB2_NEGOTIATE_SIGNING_REQUIRED;
	अन्यथा अगर (global_secflags & CIFSSEC_MAY_SIGN) /* one flag unlike MUST_ */
		req->SecurityMode = SMB2_NEGOTIATE_SIGNING_ENABLED;
	अन्यथा
		req->SecurityMode = 0;

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	req->Capabilities = cpu_to_le32(SMB2_GLOBAL_CAP_DFS);
#अन्यथा
	req->Capabilities = 0;
#पूर्ण_अगर /* DFS_UPCALL */

	req->Channel = 0; /* MBZ */

	sess_data->iov[0].iov_base = (अक्षर *)req;
	/* 1 क्रम pad */
	sess_data->iov[0].iov_len = total_len - 1;
	/*
	 * This variable will be used to clear the buffer
	 * allocated above in हाल of any error in the calling function.
	 */
	sess_data->buf0_type = CIFS_SMALL_BUFFER;

	वापस 0;
पूर्ण

अटल व्योम
SMB2_sess_मुक्त_buffer(काष्ठा SMB2_sess_data *sess_data)
अणु
	मुक्त_rsp_buf(sess_data->buf0_type, sess_data->iov[0].iov_base);
	sess_data->buf0_type = CIFS_NO_BUFFER;
पूर्ण

अटल पूर्णांक
SMB2_sess_sendreceive(काष्ठा SMB2_sess_data *sess_data)
अणु
	पूर्णांक rc;
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_sess_setup_req *req = sess_data->iov[0].iov_base;
	काष्ठा kvec rsp_iov = अणु शून्य, 0 पूर्ण;

	/* Testing shows that buffer offset must be at location of Buffer[0] */
	req->SecurityBufferOffset =
		cpu_to_le16(माप(काष्ठा smb2_sess_setup_req) - 1 /* pad */);
	req->SecurityBufferLength = cpu_to_le16(sess_data->iov[1].iov_len);

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = sess_data->iov;
	rqst.rq_nvec = 2;

	/* BB add code to build os and lm fields */
	rc = cअगरs_send_recv(sess_data->xid, sess_data->ses,
			    cअगरs_ses_server(sess_data->ses),
			    &rqst,
			    &sess_data->buf0_type,
			    CIFS_LOG_ERROR | CIFS_SESS_OP, &rsp_iov);
	cअगरs_small_buf_release(sess_data->iov[0].iov_base);
	स_नकल(&sess_data->iov[0], &rsp_iov, माप(काष्ठा kvec));

	वापस rc;
पूर्ण

अटल पूर्णांक
SMB2_sess_establish_session(काष्ठा SMB2_sess_data *sess_data)
अणु
	पूर्णांक rc = 0;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_ses_server(ses);

	mutex_lock(&server->srv_mutex);
	अगर (server->ops->generate_signingkey) अणु
		rc = server->ops->generate_signingkey(ses);
		अगर (rc) अणु
			cअगरs_dbg(FYI,
				"SMB3 session key generation failed\n");
			mutex_unlock(&server->srv_mutex);
			वापस rc;
		पूर्ण
	पूर्ण
	अगर (!server->session_estab) अणु
		server->sequence_number = 0x2;
		server->session_estab = true;
	पूर्ण
	mutex_unlock(&server->srv_mutex);

	cअगरs_dbg(FYI, "SMB2/3 session established successfully\n");
	/* keep existing ses state अगर binding */
	अगर (!ses->binding) अणु
		spin_lock(&GlobalMid_Lock);
		ses->status = CअगरsGood;
		ses->need_reconnect = false;
		spin_unlock(&GlobalMid_Lock);
	पूर्ण

	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_CIFS_UPCALL
अटल व्योम
SMB2_auth_kerberos(काष्ठा SMB2_sess_data *sess_data)
अणु
	पूर्णांक rc;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	काष्ठा cअगरs_spnego_msg *msg;
	काष्ठा key *spnego_key = शून्य;
	काष्ठा smb2_sess_setup_rsp *rsp = शून्य;

	rc = SMB2_sess_alloc_buffer(sess_data);
	अगर (rc)
		जाओ out;

	spnego_key = cअगरs_get_spnego_key(ses);
	अगर (IS_ERR(spnego_key)) अणु
		rc = PTR_ERR(spnego_key);
		अगर (rc == -ENOKEY)
			cअगरs_dbg(VFS, "Verify user has a krb5 ticket and keyutils is installed\n");
		spnego_key = शून्य;
		जाओ out;
	पूर्ण

	msg = spnego_key->payload.data[0];
	/*
	 * check version field to make sure that cअगरs.upcall is
	 * sending us a response in an expected क्रमm
	 */
	अगर (msg->version != CIFS_SPNEGO_UPCALL_VERSION) अणु
		cअगरs_dbg(VFS, "bad cifs.upcall version. Expected %d got %d\n",
			 CIFS_SPNEGO_UPCALL_VERSION, msg->version);
		rc = -EKEYREJECTED;
		जाओ out_put_spnego_key;
	पूर्ण

	/* keep session key अगर binding */
	अगर (!ses->binding) अणु
		ses->auth_key.response = kmemdup(msg->data, msg->sesskey_len,
						 GFP_KERNEL);
		अगर (!ses->auth_key.response) अणु
			cअगरs_dbg(VFS, "Kerberos can't allocate (%u bytes) memory\n",
				 msg->sesskey_len);
			rc = -ENOMEM;
			जाओ out_put_spnego_key;
		पूर्ण
		ses->auth_key.len = msg->sesskey_len;
	पूर्ण

	sess_data->iov[1].iov_base = msg->data + msg->sesskey_len;
	sess_data->iov[1].iov_len = msg->secblob_len;

	rc = SMB2_sess_sendreceive(sess_data);
	अगर (rc)
		जाओ out_put_spnego_key;

	rsp = (काष्ठा smb2_sess_setup_rsp *)sess_data->iov[0].iov_base;
	/* keep session id and flags अगर binding */
	अगर (!ses->binding) अणु
		ses->Suid = rsp->sync_hdr.SessionId;
		ses->session_flags = le16_to_cpu(rsp->SessionFlags);
	पूर्ण

	rc = SMB2_sess_establish_session(sess_data);
out_put_spnego_key:
	key_invalidate(spnego_key);
	key_put(spnego_key);
out:
	sess_data->result = rc;
	sess_data->func = शून्य;
	SMB2_sess_मुक्त_buffer(sess_data);
पूर्ण
#अन्यथा
अटल व्योम
SMB2_auth_kerberos(काष्ठा SMB2_sess_data *sess_data)
अणु
	cअगरs_dbg(VFS, "Kerberos negotiated but upcall support disabled!\n");
	sess_data->result = -EOPNOTSUPP;
	sess_data->func = शून्य;
पूर्ण
#पूर्ण_अगर

अटल व्योम
SMB2_sess_auth_rawntlmssp_authenticate(काष्ठा SMB2_sess_data *sess_data);

अटल व्योम
SMB2_sess_auth_rawntlmssp_negotiate(काष्ठा SMB2_sess_data *sess_data)
अणु
	पूर्णांक rc;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	काष्ठा smb2_sess_setup_rsp *rsp = शून्य;
	अक्षर *ntlmssp_blob = शून्य;
	bool use_spnego = false; /* अन्यथा use raw ntlmssp */
	u16 blob_length = 0;

	/*
	 * If memory allocation is successful, caller of this function
	 * मुक्तs it.
	 */
	ses->ntlmssp = kदो_स्मृति(माप(काष्ठा ntlmssp_auth), GFP_KERNEL);
	अगर (!ses->ntlmssp) अणु
		rc = -ENOMEM;
		जाओ out_err;
	पूर्ण
	ses->ntlmssp->sesskey_per_smbsess = true;

	rc = SMB2_sess_alloc_buffer(sess_data);
	अगर (rc)
		जाओ out_err;

	ntlmssp_blob = kदो_स्मृति(माप(काष्ठा _NEGOTIATE_MESSAGE),
			       GFP_KERNEL);
	अगर (ntlmssp_blob == शून्य) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	build_ntlmssp_negotiate_blob(ntlmssp_blob, ses);
	अगर (use_spnego) अणु
		/* BB eventually need to add this */
		cअगरs_dbg(VFS, "spnego not supported for SMB2 yet\n");
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण अन्यथा अणु
		blob_length = माप(काष्ठा _NEGOTIATE_MESSAGE);
		/* with raw NTLMSSP we करोn't encapsulate in SPNEGO */
	पूर्ण
	sess_data->iov[1].iov_base = ntlmssp_blob;
	sess_data->iov[1].iov_len = blob_length;

	rc = SMB2_sess_sendreceive(sess_data);
	rsp = (काष्ठा smb2_sess_setup_rsp *)sess_data->iov[0].iov_base;

	/* If true, rc here is expected and not an error */
	अगर (sess_data->buf0_type != CIFS_NO_BUFFER &&
		rsp->sync_hdr.Status == STATUS_MORE_PROCESSING_REQUIRED)
		rc = 0;

	अगर (rc)
		जाओ out;

	अगर (दुरत्व(काष्ठा smb2_sess_setup_rsp, Buffer) !=
			le16_to_cpu(rsp->SecurityBufferOffset)) अणु
		cअगरs_dbg(VFS, "Invalid security buffer offset %d\n",
			le16_to_cpu(rsp->SecurityBufferOffset));
		rc = -EIO;
		जाओ out;
	पूर्ण
	rc = decode_ntlmssp_challenge(rsp->Buffer,
			le16_to_cpu(rsp->SecurityBufferLength), ses);
	अगर (rc)
		जाओ out;

	cअगरs_dbg(FYI, "rawntlmssp session setup challenge phase\n");

	/* keep existing ses id and flags अगर binding */
	अगर (!ses->binding) अणु
		ses->Suid = rsp->sync_hdr.SessionId;
		ses->session_flags = le16_to_cpu(rsp->SessionFlags);
	पूर्ण

out:
	kमुक्त(ntlmssp_blob);
	SMB2_sess_मुक्त_buffer(sess_data);
	अगर (!rc) अणु
		sess_data->result = 0;
		sess_data->func = SMB2_sess_auth_rawntlmssp_authenticate;
		वापस;
	पूर्ण
out_err:
	kमुक्त(ses->ntlmssp);
	ses->ntlmssp = शून्य;
	sess_data->result = rc;
	sess_data->func = शून्य;
पूर्ण

अटल व्योम
SMB2_sess_auth_rawntlmssp_authenticate(काष्ठा SMB2_sess_data *sess_data)
अणु
	पूर्णांक rc;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	काष्ठा smb2_sess_setup_req *req;
	काष्ठा smb2_sess_setup_rsp *rsp = शून्य;
	अचिन्हित अक्षर *ntlmssp_blob = शून्य;
	bool use_spnego = false; /* अन्यथा use raw ntlmssp */
	u16 blob_length = 0;

	rc = SMB2_sess_alloc_buffer(sess_data);
	अगर (rc)
		जाओ out;

	req = (काष्ठा smb2_sess_setup_req *) sess_data->iov[0].iov_base;
	req->sync_hdr.SessionId = ses->Suid;

	rc = build_ntlmssp_auth_blob(&ntlmssp_blob, &blob_length, ses,
					sess_data->nls_cp);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "build_ntlmssp_auth_blob failed %d\n", rc);
		जाओ out;
	पूर्ण

	अगर (use_spnego) अणु
		/* BB eventually need to add this */
		cअगरs_dbg(VFS, "spnego not supported for SMB2 yet\n");
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	sess_data->iov[1].iov_base = ntlmssp_blob;
	sess_data->iov[1].iov_len = blob_length;

	rc = SMB2_sess_sendreceive(sess_data);
	अगर (rc)
		जाओ out;

	rsp = (काष्ठा smb2_sess_setup_rsp *)sess_data->iov[0].iov_base;

	/* keep existing ses id and flags अगर binding */
	अगर (!ses->binding) अणु
		ses->Suid = rsp->sync_hdr.SessionId;
		ses->session_flags = le16_to_cpu(rsp->SessionFlags);
	पूर्ण

	rc = SMB2_sess_establish_session(sess_data);
#अगर_घोषित CONFIG_CIFS_DEBUG_DUMP_KEYS
	अगर (ses->server->dialect < SMB30_PROT_ID) अणु
		cअगरs_dbg(VFS, "%s: dumping generated SMB2 session keys\n", __func__);
		/*
		 * The session id is opaque in terms of endianness, so we can't
		 * prपूर्णांक it as a दीर्घ दीर्घ. we dump it as we got it on the wire
		 */
		cअगरs_dbg(VFS, "Session Id    %*ph\n", (पूर्णांक)माप(ses->Suid),
			 &ses->Suid);
		cअगरs_dbg(VFS, "Session Key   %*ph\n",
			 SMB2_NTLMV2_SESSKEY_SIZE, ses->auth_key.response);
		cअगरs_dbg(VFS, "Signing Key   %*ph\n",
			 SMB3_SIGN_KEY_SIZE, ses->auth_key.response);
	पूर्ण
#पूर्ण_अगर
out:
	kमुक्त(ntlmssp_blob);
	SMB2_sess_मुक्त_buffer(sess_data);
	kमुक्त(ses->ntlmssp);
	ses->ntlmssp = शून्य;
	sess_data->result = rc;
	sess_data->func = शून्य;
पूर्ण

अटल पूर्णांक
SMB2_select_sec(काष्ठा cअगरs_ses *ses, काष्ठा SMB2_sess_data *sess_data)
अणु
	पूर्णांक type;

	type = smb2_select_sectype(cअगरs_ses_server(ses), ses->sectype);
	cअगरs_dbg(FYI, "sess setup type %d\n", type);
	अगर (type == Unspecअगरied) अणु
		cअगरs_dbg(VFS, "Unable to select appropriate authentication method!\n");
		वापस -EINVAL;
	पूर्ण

	चयन (type) अणु
	हाल Kerberos:
		sess_data->func = SMB2_auth_kerberos;
		अवरोध;
	हाल RawNTLMSSP:
		sess_data->func = SMB2_sess_auth_rawntlmssp_negotiate;
		अवरोध;
	शेष:
		cअगरs_dbg(VFS, "secType %d not supported!\n", type);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
SMB2_sess_setup(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
		स्थिर काष्ठा nls_table *nls_cp)
अणु
	पूर्णांक rc = 0;
	काष्ठा TCP_Server_Info *server = cअगरs_ses_server(ses);
	काष्ठा SMB2_sess_data *sess_data;

	cअगरs_dbg(FYI, "Session Setup\n");

	अगर (!server) अणु
		WARN(1, "%s: server is NULL!\n", __func__);
		वापस -EIO;
	पूर्ण

	sess_data = kzalloc(माप(काष्ठा SMB2_sess_data), GFP_KERNEL);
	अगर (!sess_data)
		वापस -ENOMEM;

	rc = SMB2_select_sec(ses, sess_data);
	अगर (rc)
		जाओ out;
	sess_data->xid = xid;
	sess_data->ses = ses;
	sess_data->buf0_type = CIFS_NO_BUFFER;
	sess_data->nls_cp = (काष्ठा nls_table *) nls_cp;
	sess_data->previous_session = ses->Suid;

	/*
	 * Initialize the session hash with the server one.
	 */
	स_नकल(ses->preauth_sha_hash, server->preauth_sha_hash,
	       SMB2_PREAUTH_HASH_SIZE);

	जबतक (sess_data->func)
		sess_data->func(sess_data);

	अगर ((ses->session_flags & SMB2_SESSION_FLAG_IS_GUEST) && (ses->sign))
		cअगरs_server_dbg(VFS, "signing requested but authenticated as guest\n");
	rc = sess_data->result;
out:
	kमुक्त(sess_data);
	वापस rc;
पूर्ण

पूर्णांक
SMB2_logoff(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_logoff_req *req; /* response is also trivial काष्ठा */
	पूर्णांक rc = 0;
	काष्ठा TCP_Server_Info *server;
	पूर्णांक flags = 0;
	अचिन्हित पूर्णांक total_len;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov;
	पूर्णांक resp_buf_type;

	cअगरs_dbg(FYI, "disconnect session %p\n", ses);

	अगर (ses && (ses->server))
		server = ses->server;
	अन्यथा
		वापस -EIO;

	/* no need to send SMB logoff अगर uid alपढ़ोy बंदd due to reconnect */
	अगर (ses->need_reconnect)
		जाओ smb2_session_alपढ़ोy_dead;

	rc = smb2_plain_req_init(SMB2_LOGOFF, शून्य, ses->server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	 /* since no tcon, smb2_init can not करो this, so करो here */
	req->sync_hdr.SessionId = ses->Suid;

	अगर (ses->session_flags & SMB2_SESSION_FLAG_ENCRYPT_DATA)
		flags |= CIFS_TRANSFORM_REQ;
	अन्यथा अगर (server->sign)
		req->sync_hdr.Flags |= SMB2_FLAGS_SIGNED;

	flags |= CIFS_NO_RSP_BUF;

	iov[0].iov_base = (अक्षर *)req;
	iov[0].iov_len = total_len;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	rc = cअगरs_send_recv(xid, ses, ses->server,
			    &rqst, &resp_buf_type, flags, &rsp_iov);
	cअगरs_small_buf_release(req);
	/*
	 * No tcon so can't करो
	 * cअगरs_stats_inc(&tcon->stats.smb2_stats.smb2_com_fail[SMB2...]);
	 */

smb2_session_alपढ़ोy_dead:
	वापस rc;
पूर्ण

अटल अंतरभूत व्योम cअगरs_stats_fail_inc(काष्ठा cअगरs_tcon *tcon, uपूर्णांक16_t code)
अणु
	cअगरs_stats_inc(&tcon->stats.smb2_stats.smb2_com_failed[code]);
पूर्ण

#घोषणा MAX_SHARENAME_LENGTH (255 /* server */ + 80 /* share */ + 1 /* शून्य */)

/* These are similar values to what Winकरोws uses */
अटल अंतरभूत व्योम init_copy_chunk_शेषs(काष्ठा cअगरs_tcon *tcon)
अणु
	tcon->max_chunks = 256;
	tcon->max_bytes_chunk = 1048576;
	tcon->max_bytes_copy = 16777216;
पूर्ण

पूर्णांक
SMB2_tcon(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses, स्थिर अक्षर *tree,
	  काष्ठा cअगरs_tcon *tcon, स्थिर काष्ठा nls_table *cp)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_tree_connect_req *req;
	काष्ठा smb2_tree_connect_rsp *rsp = शून्य;
	काष्ठा kvec iov[2];
	काष्ठा kvec rsp_iov = अणु शून्य, 0 पूर्ण;
	पूर्णांक rc = 0;
	पूर्णांक resp_buftype;
	पूर्णांक unc_path_len;
	__le16 *unc_path = शून्य;
	पूर्णांक flags = 0;
	अचिन्हित पूर्णांक total_len;
	काष्ठा TCP_Server_Info *server;

	/* always use master channel */
	server = ses->server;

	cअगरs_dbg(FYI, "TCON\n");

	अगर (!server || !tree)
		वापस -EIO;

	unc_path = kदो_स्मृति(MAX_SHARENAME_LENGTH * 2, GFP_KERNEL);
	अगर (unc_path == शून्य)
		वापस -ENOMEM;

	unc_path_len = cअगरs_strtoUTF16(unc_path, tree, म_माप(tree), cp) + 1;
	unc_path_len *= 2;
	अगर (unc_path_len < 2) अणु
		kमुक्त(unc_path);
		वापस -EINVAL;
	पूर्ण

	/* SMB2 TREE_CONNECT request must be called with TreeId == 0 */
	tcon->tid = 0;
	atomic_set(&tcon->num_remote_खोलोs, 0);
	rc = smb2_plain_req_init(SMB2_TREE_CONNECT, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc) अणु
		kमुक्त(unc_path);
		वापस rc;
	पूर्ण

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	iov[0].iov_base = (अक्षर *)req;
	/* 1 क्रम pad */
	iov[0].iov_len = total_len - 1;

	/* Testing shows that buffer offset must be at location of Buffer[0] */
	req->PathOffset = cpu_to_le16(माप(काष्ठा smb2_tree_connect_req)
			- 1 /* pad */);
	req->PathLength = cpu_to_le16(unc_path_len - 2);
	iov[1].iov_base = unc_path;
	iov[1].iov_len = unc_path_len;

	/*
	 * 3.11 tcon req must be चिन्हित अगर not encrypted. See MS-SMB2 3.2.4.1.1
	 * unless it is guest or anonymous user. See MS-SMB2 3.2.5.3.1
	 * (Samba servers करोn't always set the flag so also check अगर null user)
	 */
	अगर ((server->dialect == SMB311_PROT_ID) &&
	    !smb3_encryption_required(tcon) &&
	    !(ses->session_flags &
		    (SMB2_SESSION_FLAG_IS_GUEST|SMB2_SESSION_FLAG_IS_शून्य)) &&
	    ((ses->user_name != शून्य) || (ses->sectype == Kerberos)))
		req->sync_hdr.Flags |= SMB2_FLAGS_SIGNED;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 2;

	/* Need 64 क्रम max size ग_लिखो so ask क्रम more in हाल not there yet */
	req->sync_hdr.CreditRequest = cpu_to_le16(64);

	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags, &rsp_iov);
	cअगरs_small_buf_release(req);
	rsp = (काष्ठा smb2_tree_connect_rsp *)rsp_iov.iov_base;
	trace_smb3_tcon(xid, tcon->tid, ses->Suid, tree, rc);
	अगर (rc != 0) अणु
		अगर (tcon) अणु
			cअगरs_stats_fail_inc(tcon, SMB2_TREE_CONNECT_HE);
			tcon->need_reconnect = true;
		पूर्ण
		जाओ tcon_error_निकास;
	पूर्ण

	चयन (rsp->ShareType) अणु
	हाल SMB2_SHARE_TYPE_DISK:
		cअगरs_dbg(FYI, "connection to disk share\n");
		अवरोध;
	हाल SMB2_SHARE_TYPE_PIPE:
		tcon->pipe = true;
		cअगरs_dbg(FYI, "connection to pipe share\n");
		अवरोध;
	हाल SMB2_SHARE_TYPE_PRINT:
		tcon->prपूर्णांक = true;
		cअगरs_dbg(FYI, "connection to printer\n");
		अवरोध;
	शेष:
		cअगरs_server_dbg(VFS, "unknown share type %d\n", rsp->ShareType);
		rc = -EOPNOTSUPP;
		जाओ tcon_error_निकास;
	पूर्ण

	tcon->share_flags = le32_to_cpu(rsp->ShareFlags);
	tcon->capabilities = rsp->Capabilities; /* we keep caps little endian */
	tcon->maximal_access = le32_to_cpu(rsp->MaximalAccess);
	tcon->tidStatus = CअगरsGood;
	tcon->need_reconnect = false;
	tcon->tid = rsp->sync_hdr.TreeId;
	strlcpy(tcon->treeName, tree, माप(tcon->treeName));

	अगर ((rsp->Capabilities & SMB2_SHARE_CAP_DFS) &&
	    ((tcon->share_flags & SHI1005_FLAGS_DFS) == 0))
		cअगरs_tcon_dbg(VFS, "DFS capability contradicts DFS flag\n");

	अगर (tcon->seal &&
	    !(server->capabilities & SMB2_GLOBAL_CAP_ENCRYPTION))
		cअगरs_tcon_dbg(VFS, "Encryption is requested but not supported\n");

	init_copy_chunk_शेषs(tcon);
	अगर (server->ops->validate_negotiate)
		rc = server->ops->validate_negotiate(xid, tcon);
tcon_निकास:

	मुक्त_rsp_buf(resp_buftype, rsp);
	kमुक्त(unc_path);
	वापस rc;

tcon_error_निकास:
	अगर (rsp && rsp->sync_hdr.Status == STATUS_BAD_NETWORK_NAME) अणु
		cअगरs_tcon_dbg(VFS, "BAD_NETWORK_NAME: %s\n", tree);
	पूर्ण
	जाओ tcon_निकास;
पूर्ण

पूर्णांक
SMB2_tdis(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_tree_disconnect_req *req; /* response is trivial */
	पूर्णांक rc = 0;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	पूर्णांक flags = 0;
	अचिन्हित पूर्णांक total_len;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov;
	पूर्णांक resp_buf_type;

	cअगरs_dbg(FYI, "Tree Disconnect\n");

	अगर (!ses || !(ses->server))
		वापस -EIO;

	अगर ((tcon->need_reconnect) || (tcon->ses->need_reconnect))
		वापस 0;

	बंद_cached_dir_lease(&tcon->crfid);

	rc = smb2_plain_req_init(SMB2_TREE_DISCONNECT, tcon, ses->server,
				 (व्योम **) &req,
				 &total_len);
	अगर (rc)
		वापस rc;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	flags |= CIFS_NO_RSP_BUF;

	iov[0].iov_base = (अक्षर *)req;
	iov[0].iov_len = total_len;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	rc = cअगरs_send_recv(xid, ses, ses->server,
			    &rqst, &resp_buf_type, flags, &rsp_iov);
	cअगरs_small_buf_release(req);
	अगर (rc)
		cअगरs_stats_fail_inc(tcon, SMB2_TREE_DISCONNECT_HE);

	वापस rc;
पूर्ण


अटल काष्ठा create_durable *
create_durable_buf(व्योम)
अणु
	काष्ठा create_durable *buf;

	buf = kzalloc(माप(काष्ठा create_durable), GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	buf->ccontext.DataOffset = cpu_to_le16(दुरत्व
					(काष्ठा create_durable, Data));
	buf->ccontext.DataLength = cpu_to_le32(16);
	buf->ccontext.NameOffset = cpu_to_le16(दुरत्व
				(काष्ठा create_durable, Name));
	buf->ccontext.NameLength = cpu_to_le16(4);
	/* SMB2_CREATE_DURABLE_HANDLE_REQUEST is "DHnQ" */
	buf->Name[0] = 'D';
	buf->Name[1] = 'H';
	buf->Name[2] = 'n';
	buf->Name[3] = 'Q';
	वापस buf;
पूर्ण

अटल काष्ठा create_durable *
create_reconnect_durable_buf(काष्ठा cअगरs_fid *fid)
अणु
	काष्ठा create_durable *buf;

	buf = kzalloc(माप(काष्ठा create_durable), GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	buf->ccontext.DataOffset = cpu_to_le16(दुरत्व
					(काष्ठा create_durable, Data));
	buf->ccontext.DataLength = cpu_to_le32(16);
	buf->ccontext.NameOffset = cpu_to_le16(दुरत्व
				(काष्ठा create_durable, Name));
	buf->ccontext.NameLength = cpu_to_le16(4);
	buf->Data.Fid.PersistentFileId = fid->persistent_fid;
	buf->Data.Fid.VolatileFileId = fid->अस्थिर_fid;
	/* SMB2_CREATE_DURABLE_HANDLE_RECONNECT is "DHnC" */
	buf->Name[0] = 'D';
	buf->Name[1] = 'H';
	buf->Name[2] = 'n';
	buf->Name[3] = 'C';
	वापस buf;
पूर्ण

अटल व्योम
parse_query_id_ctxt(काष्ठा create_context *cc, काष्ठा smb2_file_all_info *buf)
अणु
	काष्ठा create_on_disk_id *pdisk_id = (काष्ठा create_on_disk_id *)cc;

	cअगरs_dbg(FYI, "parse query id context 0x%llx 0x%llx\n",
		pdisk_id->DiskFileId, pdisk_id->VolumeId);
	buf->IndexNumber = pdisk_id->DiskFileId;
पूर्ण

अटल व्योम
parse_posix_ctxt(काष्ठा create_context *cc, काष्ठा smb2_file_all_info *info,
		 काष्ठा create_posix_rsp *posix)
अणु
	पूर्णांक sid_len;
	u8 *beg = (u8 *)cc + le16_to_cpu(cc->DataOffset);
	u8 *end = beg + le32_to_cpu(cc->DataLength);
	u8 *sid;

	स_रखो(posix, 0, माप(*posix));

	posix->nlink = le32_to_cpu(*(__le32 *)(beg + 0));
	posix->reparse_tag = le32_to_cpu(*(__le32 *)(beg + 4));
	posix->mode = le32_to_cpu(*(__le32 *)(beg + 8));

	sid = beg + 12;
	sid_len = posix_info_sid_size(sid, end);
	अगर (sid_len < 0) अणु
		cअगरs_dbg(VFS, "bad owner sid in posix create response\n");
		वापस;
	पूर्ण
	स_नकल(&posix->owner, sid, sid_len);

	sid = sid + sid_len;
	sid_len = posix_info_sid_size(sid, end);
	अगर (sid_len < 0) अणु
		cअगरs_dbg(VFS, "bad group sid in posix create response\n");
		वापस;
	पूर्ण
	स_नकल(&posix->group, sid, sid_len);

	cअगरs_dbg(FYI, "nlink=%d mode=%o reparse_tag=%x\n",
		 posix->nlink, posix->mode, posix->reparse_tag);
पूर्ण

व्योम
smb2_parse_contexts(काष्ठा TCP_Server_Info *server,
		    काष्ठा smb2_create_rsp *rsp,
		    अचिन्हित पूर्णांक *epoch, अक्षर *lease_key, __u8 *oplock,
		    काष्ठा smb2_file_all_info *buf,
		    काष्ठा create_posix_rsp *posix)
अणु
	अक्षर *data_offset;
	काष्ठा create_context *cc;
	अचिन्हित पूर्णांक next;
	अचिन्हित पूर्णांक reमुख्यing;
	अक्षर *name;
	अटल स्थिर अक्षर smb3_create_tag_posix[] = अणु
		0x93, 0xAD, 0x25, 0x50, 0x9C,
		0xB4, 0x11, 0xE7, 0xB4, 0x23, 0x83,
		0xDE, 0x96, 0x8B, 0xCD, 0x7C
	पूर्ण;

	*oplock = 0;
	data_offset = (अक्षर *)rsp + le32_to_cpu(rsp->CreateContextsOffset);
	reमुख्यing = le32_to_cpu(rsp->CreateContextsLength);
	cc = (काष्ठा create_context *)data_offset;

	/* Initialize inode number to 0 in हाल no valid data in qfid context */
	अगर (buf)
		buf->IndexNumber = 0;

	जबतक (reमुख्यing >= माप(काष्ठा create_context)) अणु
		name = le16_to_cpu(cc->NameOffset) + (अक्षर *)cc;
		अगर (le16_to_cpu(cc->NameLength) == 4 &&
		    म_भेदन(name, SMB2_CREATE_REQUEST_LEASE, 4) == 0)
			*oplock = server->ops->parse_lease_buf(cc, epoch,
							   lease_key);
		अन्यथा अगर (buf && (le16_to_cpu(cc->NameLength) == 4) &&
		    म_भेदन(name, SMB2_CREATE_QUERY_ON_DISK_ID, 4) == 0)
			parse_query_id_ctxt(cc, buf);
		अन्यथा अगर ((le16_to_cpu(cc->NameLength) == 16)) अणु
			अगर (posix &&
			    स_भेद(name, smb3_create_tag_posix, 16) == 0)
				parse_posix_ctxt(cc, buf, posix);
		पूर्ण
		/* अन्यथा अणु
			cअगरs_dbg(FYI, "Context not matched with len %d\n",
				le16_to_cpu(cc->NameLength));
			cअगरs_dump_mem("Cctxt name: ", name, 4);
		पूर्ण */

		next = le32_to_cpu(cc->Next);
		अगर (!next)
			अवरोध;
		reमुख्यing -= next;
		cc = (काष्ठा create_context *)((अक्षर *)cc + next);
	पूर्ण

	अगर (rsp->OplockLevel != SMB2_OPLOCK_LEVEL_LEASE)
		*oplock = rsp->OplockLevel;

	वापस;
पूर्ण

अटल पूर्णांक
add_lease_context(काष्ठा TCP_Server_Info *server, काष्ठा kvec *iov,
		  अचिन्हित पूर्णांक *num_iovec, u8 *lease_key, __u8 *oplock)
अणु
	काष्ठा smb2_create_req *req = iov[0].iov_base;
	अचिन्हित पूर्णांक num = *num_iovec;

	iov[num].iov_base = server->ops->create_lease_buf(lease_key, *oplock);
	अगर (iov[num].iov_base == शून्य)
		वापस -ENOMEM;
	iov[num].iov_len = server->vals->create_lease_size;
	req->RequestedOplockLevel = SMB2_OPLOCK_LEVEL_LEASE;
	अगर (!req->CreateContextsOffset)
		req->CreateContextsOffset = cpu_to_le32(
				माप(काष्ठा smb2_create_req) +
				iov[num - 1].iov_len);
	le32_add_cpu(&req->CreateContextsLength,
		     server->vals->create_lease_size);
	*num_iovec = num + 1;
	वापस 0;
पूर्ण

अटल काष्ठा create_durable_v2 *
create_durable_v2_buf(काष्ठा cअगरs_खोलो_parms *oparms)
अणु
	काष्ठा cअगरs_fid *pfid = oparms->fid;
	काष्ठा create_durable_v2 *buf;

	buf = kzalloc(माप(काष्ठा create_durable_v2), GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	buf->ccontext.DataOffset = cpu_to_le16(दुरत्व
					(काष्ठा create_durable_v2, dcontext));
	buf->ccontext.DataLength = cpu_to_le32(माप(काष्ठा durable_context_v2));
	buf->ccontext.NameOffset = cpu_to_le16(दुरत्व
				(काष्ठा create_durable_v2, Name));
	buf->ccontext.NameLength = cpu_to_le16(4);

	/*
	 * NB: Handle समयout शेषs to 0, which allows server to choose
	 * (most servers शेष to 120 seconds) and most clients शेष to 0.
	 * This can be overridden at mount ("handletimeout=") अगर the user wants
	 * a dअगरferent persistent (or resilient) handle समयout क्रम all खोलोs
	 * खोलोs on a particular SMB3 mount.
	 */
	buf->dcontext.Timeout = cpu_to_le32(oparms->tcon->handle_समयout);
	buf->dcontext.Flags = cpu_to_le32(SMB2_DHANDLE_FLAG_PERSISTENT);
	generate_अक्रमom_uuid(buf->dcontext.CreateGuid);
	स_नकल(pfid->create_guid, buf->dcontext.CreateGuid, 16);

	/* SMB2_CREATE_DURABLE_HANDLE_REQUEST is "DH2Q" */
	buf->Name[0] = 'D';
	buf->Name[1] = 'H';
	buf->Name[2] = '2';
	buf->Name[3] = 'Q';
	वापस buf;
पूर्ण

अटल काष्ठा create_durable_handle_reconnect_v2 *
create_reconnect_durable_v2_buf(काष्ठा cअगरs_fid *fid)
अणु
	काष्ठा create_durable_handle_reconnect_v2 *buf;

	buf = kzalloc(माप(काष्ठा create_durable_handle_reconnect_v2),
			GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	buf->ccontext.DataOffset =
		cpu_to_le16(दुरत्व(काष्ठा create_durable_handle_reconnect_v2,
				     dcontext));
	buf->ccontext.DataLength =
		cpu_to_le32(माप(काष्ठा durable_reconnect_context_v2));
	buf->ccontext.NameOffset =
		cpu_to_le16(दुरत्व(काष्ठा create_durable_handle_reconnect_v2,
			    Name));
	buf->ccontext.NameLength = cpu_to_le16(4);

	buf->dcontext.Fid.PersistentFileId = fid->persistent_fid;
	buf->dcontext.Fid.VolatileFileId = fid->अस्थिर_fid;
	buf->dcontext.Flags = cpu_to_le32(SMB2_DHANDLE_FLAG_PERSISTENT);
	स_नकल(buf->dcontext.CreateGuid, fid->create_guid, 16);

	/* SMB2_CREATE_DURABLE_HANDLE_RECONNECT_V2 is "DH2C" */
	buf->Name[0] = 'D';
	buf->Name[1] = 'H';
	buf->Name[2] = '2';
	buf->Name[3] = 'C';
	वापस buf;
पूर्ण

अटल पूर्णांक
add_durable_v2_context(काष्ठा kvec *iov, अचिन्हित पूर्णांक *num_iovec,
		    काष्ठा cअगरs_खोलो_parms *oparms)
अणु
	काष्ठा smb2_create_req *req = iov[0].iov_base;
	अचिन्हित पूर्णांक num = *num_iovec;

	iov[num].iov_base = create_durable_v2_buf(oparms);
	अगर (iov[num].iov_base == शून्य)
		वापस -ENOMEM;
	iov[num].iov_len = माप(काष्ठा create_durable_v2);
	अगर (!req->CreateContextsOffset)
		req->CreateContextsOffset =
			cpu_to_le32(माप(काष्ठा smb2_create_req) +
								iov[1].iov_len);
	le32_add_cpu(&req->CreateContextsLength, माप(काष्ठा create_durable_v2));
	*num_iovec = num + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक
add_durable_reconnect_v2_context(काष्ठा kvec *iov, अचिन्हित पूर्णांक *num_iovec,
		    काष्ठा cअगरs_खोलो_parms *oparms)
अणु
	काष्ठा smb2_create_req *req = iov[0].iov_base;
	अचिन्हित पूर्णांक num = *num_iovec;

	/* indicate that we करोn't need to relock the file */
	oparms->reconnect = false;

	iov[num].iov_base = create_reconnect_durable_v2_buf(oparms->fid);
	अगर (iov[num].iov_base == शून्य)
		वापस -ENOMEM;
	iov[num].iov_len = माप(काष्ठा create_durable_handle_reconnect_v2);
	अगर (!req->CreateContextsOffset)
		req->CreateContextsOffset =
			cpu_to_le32(माप(काष्ठा smb2_create_req) +
								iov[1].iov_len);
	le32_add_cpu(&req->CreateContextsLength,
			माप(काष्ठा create_durable_handle_reconnect_v2));
	*num_iovec = num + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक
add_durable_context(काष्ठा kvec *iov, अचिन्हित पूर्णांक *num_iovec,
		    काष्ठा cअगरs_खोलो_parms *oparms, bool use_persistent)
अणु
	काष्ठा smb2_create_req *req = iov[0].iov_base;
	अचिन्हित पूर्णांक num = *num_iovec;

	अगर (use_persistent) अणु
		अगर (oparms->reconnect)
			वापस add_durable_reconnect_v2_context(iov, num_iovec,
								oparms);
		अन्यथा
			वापस add_durable_v2_context(iov, num_iovec, oparms);
	पूर्ण

	अगर (oparms->reconnect) अणु
		iov[num].iov_base = create_reconnect_durable_buf(oparms->fid);
		/* indicate that we करोn't need to relock the file */
		oparms->reconnect = false;
	पूर्ण अन्यथा
		iov[num].iov_base = create_durable_buf();
	अगर (iov[num].iov_base == शून्य)
		वापस -ENOMEM;
	iov[num].iov_len = माप(काष्ठा create_durable);
	अगर (!req->CreateContextsOffset)
		req->CreateContextsOffset =
			cpu_to_le32(माप(काष्ठा smb2_create_req) +
								iov[1].iov_len);
	le32_add_cpu(&req->CreateContextsLength, माप(काष्ठा create_durable));
	*num_iovec = num + 1;
	वापस 0;
पूर्ण

/* See MS-SMB2 2.2.13.2.7 */
अटल काष्ठा crt_twarp_ctxt *
create_twarp_buf(__u64 समयwarp)
अणु
	काष्ठा crt_twarp_ctxt *buf;

	buf = kzalloc(माप(काष्ठा crt_twarp_ctxt), GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	buf->ccontext.DataOffset = cpu_to_le16(दुरत्व
					(काष्ठा crt_twarp_ctxt, Timestamp));
	buf->ccontext.DataLength = cpu_to_le32(8);
	buf->ccontext.NameOffset = cpu_to_le16(दुरत्व
				(काष्ठा crt_twarp_ctxt, Name));
	buf->ccontext.NameLength = cpu_to_le16(4);
	/* SMB2_CREATE_TIMEWARP_TOKEN is "TWrp" */
	buf->Name[0] = 'T';
	buf->Name[1] = 'W';
	buf->Name[2] = 'r';
	buf->Name[3] = 'p';
	buf->Timestamp = cpu_to_le64(समयwarp);
	वापस buf;
पूर्ण

/* See MS-SMB2 2.2.13.2.7 */
अटल पूर्णांक
add_twarp_context(काष्ठा kvec *iov, अचिन्हित पूर्णांक *num_iovec, __u64 समयwarp)
अणु
	काष्ठा smb2_create_req *req = iov[0].iov_base;
	अचिन्हित पूर्णांक num = *num_iovec;

	iov[num].iov_base = create_twarp_buf(समयwarp);
	अगर (iov[num].iov_base == शून्य)
		वापस -ENOMEM;
	iov[num].iov_len = माप(काष्ठा crt_twarp_ctxt);
	अगर (!req->CreateContextsOffset)
		req->CreateContextsOffset = cpu_to_le32(
				माप(काष्ठा smb2_create_req) +
				iov[num - 1].iov_len);
	le32_add_cpu(&req->CreateContextsLength, माप(काष्ठा crt_twarp_ctxt));
	*num_iovec = num + 1;
	वापस 0;
पूर्ण

/* See See http://technet.microsoft.com/en-us/library/hh509017(v=ws.10).aspx */
अटल व्योम setup_owner_group_sids(अक्षर *buf)
अणु
	काष्ठा owner_group_sids *sids = (काष्ठा owner_group_sids *)buf;

	/* Populate the user ownership fields S-1-5-88-1 */
	sids->owner.Revision = 1;
	sids->owner.NumAuth = 3;
	sids->owner.Authority[5] = 5;
	sids->owner.SubAuthorities[0] = cpu_to_le32(88);
	sids->owner.SubAuthorities[1] = cpu_to_le32(1);
	sids->owner.SubAuthorities[2] = cpu_to_le32(current_fsuid().val);

	/* Populate the group ownership fields S-1-5-88-2 */
	sids->group.Revision = 1;
	sids->group.NumAuth = 3;
	sids->group.Authority[5] = 5;
	sids->group.SubAuthorities[0] = cpu_to_le32(88);
	sids->group.SubAuthorities[1] = cpu_to_le32(2);
	sids->group.SubAuthorities[2] = cpu_to_le32(current_fsgid().val);

	cअगरs_dbg(FYI, "owner S-1-5-88-1-%d, group S-1-5-88-2-%d\n", current_fsuid().val, current_fsgid().val);
पूर्ण

/* See MS-SMB2 2.2.13.2.2 and MS-DTYP 2.4.6 */
अटल काष्ठा crt_sd_ctxt *
create_sd_buf(umode_t mode, bool set_owner, अचिन्हित पूर्णांक *len)
अणु
	काष्ठा crt_sd_ctxt *buf;
	__u8 *ptr, *aclptr;
	अचिन्हित पूर्णांक acelen, acl_size, ace_count;
	अचिन्हित पूर्णांक owner_offset = 0;
	अचिन्हित पूर्णांक group_offset = 0;
	काष्ठा smb3_acl acl;

	*len = roundup(माप(काष्ठा crt_sd_ctxt) + (माप(काष्ठा cअगरs_ace) * 4), 8);

	अगर (set_owner) अणु
		/* माप(काष्ठा owner_group_sids) is alपढ़ोy multiple of 8 so no need to round */
		*len += माप(काष्ठा owner_group_sids);
	पूर्ण

	buf = kzalloc(*len, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस buf;

	ptr = (__u8 *)&buf[1];
	अगर (set_owner) अणु
		/* offset fields are from beginning of security descriptor not of create context */
		owner_offset = ptr - (__u8 *)&buf->sd;
		buf->sd.OffsetOwner = cpu_to_le32(owner_offset);
		group_offset = owner_offset + दुरत्व(काष्ठा owner_group_sids, group);
		buf->sd.OffsetGroup = cpu_to_le32(group_offset);

		setup_owner_group_sids(ptr);
		ptr += माप(काष्ठा owner_group_sids);
	पूर्ण अन्यथा अणु
		buf->sd.OffsetOwner = 0;
		buf->sd.OffsetGroup = 0;
	पूर्ण

	buf->ccontext.DataOffset = cpu_to_le16(दुरत्व(काष्ठा crt_sd_ctxt, sd));
	buf->ccontext.NameOffset = cpu_to_le16(दुरत्व(काष्ठा crt_sd_ctxt, Name));
	buf->ccontext.NameLength = cpu_to_le16(4);
	/* SMB2_CREATE_SD_BUFFER_TOKEN is "SecD" */
	buf->Name[0] = 'S';
	buf->Name[1] = 'e';
	buf->Name[2] = 'c';
	buf->Name[3] = 'D';
	buf->sd.Revision = 1;  /* Must be one see MS-DTYP 2.4.6 */

	/*
	 * ACL is "self relative" ie ACL is stored in contiguous block of memory
	 * and "DP" ie the DACL is present
	 */
	buf->sd.Control = cpu_to_le16(ACL_CONTROL_SR | ACL_CONTROL_DP);

	/* offset owner, group and Sbz1 and SACL are all zero */
	buf->sd.OffsetDacl = cpu_to_le32(ptr - (__u8 *)&buf->sd);
	/* Ship the ACL क्रम now. we will copy it पूर्णांकo buf later. */
	aclptr = ptr;
	ptr += माप(काष्ठा cअगरs_acl);

	/* create one ACE to hold the mode embedded in reserved special SID */
	acelen = setup_special_mode_ACE((काष्ठा cअगरs_ace *)ptr, (__u64)mode);
	ptr += acelen;
	acl_size = acelen + माप(काष्ठा smb3_acl);
	ace_count = 1;

	अगर (set_owner) अणु
		/* we करो not need to पुनः_स्मृतिate buffer to add the two more ACEs. plenty of space */
		acelen = setup_special_user_owner_ACE((काष्ठा cअगरs_ace *)ptr);
		ptr += acelen;
		acl_size += acelen;
		ace_count += 1;
	पूर्ण

	/* and one more ACE to allow access क्रम authenticated users */
	acelen = setup_authusers_ACE((काष्ठा cअगरs_ace *)ptr);
	ptr += acelen;
	acl_size += acelen;
	ace_count += 1;

	acl.AclRevision = ACL_REVISION; /* See 2.4.4.1 of MS-DTYP */
	acl.AclSize = cpu_to_le16(acl_size);
	acl.AceCount = cpu_to_le16(ace_count);
	स_नकल(aclptr, &acl, माप(काष्ठा cअगरs_acl));

	buf->ccontext.DataLength = cpu_to_le32(ptr - (__u8 *)&buf->sd);
	*len = ptr - (__u8 *)buf;

	वापस buf;
पूर्ण

अटल पूर्णांक
add_sd_context(काष्ठा kvec *iov, अचिन्हित पूर्णांक *num_iovec, umode_t mode, bool set_owner)
अणु
	काष्ठा smb2_create_req *req = iov[0].iov_base;
	अचिन्हित पूर्णांक num = *num_iovec;
	अचिन्हित पूर्णांक len = 0;

	iov[num].iov_base = create_sd_buf(mode, set_owner, &len);
	अगर (iov[num].iov_base == शून्य)
		वापस -ENOMEM;
	iov[num].iov_len = len;
	अगर (!req->CreateContextsOffset)
		req->CreateContextsOffset = cpu_to_le32(
				माप(काष्ठा smb2_create_req) +
				iov[num - 1].iov_len);
	le32_add_cpu(&req->CreateContextsLength, len);
	*num_iovec = num + 1;
	वापस 0;
पूर्ण

अटल काष्ठा crt_query_id_ctxt *
create_query_id_buf(व्योम)
अणु
	काष्ठा crt_query_id_ctxt *buf;

	buf = kzalloc(माप(काष्ठा crt_query_id_ctxt), GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	buf->ccontext.DataOffset = cpu_to_le16(0);
	buf->ccontext.DataLength = cpu_to_le32(0);
	buf->ccontext.NameOffset = cpu_to_le16(दुरत्व
				(काष्ठा crt_query_id_ctxt, Name));
	buf->ccontext.NameLength = cpu_to_le16(4);
	/* SMB2_CREATE_QUERY_ON_DISK_ID is "QFid" */
	buf->Name[0] = 'Q';
	buf->Name[1] = 'F';
	buf->Name[2] = 'i';
	buf->Name[3] = 'd';
	वापस buf;
पूर्ण

/* See MS-SMB2 2.2.13.2.9 */
अटल पूर्णांक
add_query_id_context(काष्ठा kvec *iov, अचिन्हित पूर्णांक *num_iovec)
अणु
	काष्ठा smb2_create_req *req = iov[0].iov_base;
	अचिन्हित पूर्णांक num = *num_iovec;

	iov[num].iov_base = create_query_id_buf();
	अगर (iov[num].iov_base == शून्य)
		वापस -ENOMEM;
	iov[num].iov_len = माप(काष्ठा crt_query_id_ctxt);
	अगर (!req->CreateContextsOffset)
		req->CreateContextsOffset = cpu_to_le32(
				माप(काष्ठा smb2_create_req) +
				iov[num - 1].iov_len);
	le32_add_cpu(&req->CreateContextsLength, माप(काष्ठा crt_query_id_ctxt));
	*num_iovec = num + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक
alloc_path_with_tree_prefix(__le16 **out_path, पूर्णांक *out_size, पूर्णांक *out_len,
			    स्थिर अक्षर *treename, स्थिर __le16 *path)
अणु
	पूर्णांक treename_len, path_len;
	काष्ठा nls_table *cp;
	स्थिर __le16 sep[] = अणुcpu_to_le16('\\'), cpu_to_le16(0x0000)पूर्ण;

	/*
	 * skip leading "\\"
	 */
	treename_len = म_माप(treename);
	अगर (treename_len < 2 || !(treename[0] == '\\' && treename[1] == '\\'))
		वापस -EINVAL;

	treename += 2;
	treename_len -= 2;

	path_len = UniStrnlen((ब_अक्षर_प्रकार *)path, PATH_MAX);

	/*
	 * make room क्रम one path separator between the treename and
	 * path
	 */
	*out_len = treename_len + 1 + path_len;

	/*
	 * final path needs to be null-terminated UTF16 with a
	 * size aligned to 8
	 */

	*out_size = roundup((*out_len+1)*2, 8);
	*out_path = kzalloc(*out_size, GFP_KERNEL);
	अगर (!*out_path)
		वापस -ENOMEM;

	cp = load_nls_शेष();
	cअगरs_strtoUTF16(*out_path, treename, treename_len, cp);
	UniStrcat(*out_path, sep);
	UniStrcat(*out_path, path);
	unload_nls(cp);

	वापस 0;
पूर्ण

पूर्णांक smb311_posix_सूची_गढ़ो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा inode *inode,
			       umode_t mode, काष्ठा cअगरs_tcon *tcon,
			       स्थिर अक्षर *full_path,
			       काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_create_req *req;
	काष्ठा smb2_create_rsp *rsp = शून्य;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा kvec iov[3]; /* make sure at least one क्रम each खोलो context */
	काष्ठा kvec rsp_iov = अणुशून्य, 0पूर्ण;
	पूर्णांक resp_buftype;
	पूर्णांक uni_path_len;
	__le16 *copy_path = शून्य;
	पूर्णांक copy_size;
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक n_iov = 2;
	__u32 file_attributes = 0;
	अक्षर *pc_buf = शून्य;
	पूर्णांक flags = 0;
	अचिन्हित पूर्णांक total_len;
	__le16 *utf16_path = शून्य;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);

	cअगरs_dbg(FYI, "mkdir\n");

	/* resource #1: path allocation */
	utf16_path = cअगरs_convert_path_to_utf16(full_path, cअगरs_sb);
	अगर (!utf16_path)
		वापस -ENOMEM;

	अगर (!ses || !server) अणु
		rc = -EIO;
		जाओ err_मुक्त_path;
	पूर्ण

	/* resource #2: request */
	rc = smb2_plain_req_init(SMB2_CREATE, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		जाओ err_मुक्त_path;


	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	req->ImpersonationLevel = IL_IMPERSONATION;
	req->DesiredAccess = cpu_to_le32(खाता_WRITE_ATTRIBUTES);
	/* File attributes ignored on खोलो (used in create though) */
	req->FileAttributes = cpu_to_le32(file_attributes);
	req->ShareAccess = खाता_SHARE_ALL_LE;
	req->CreateDisposition = cpu_to_le32(खाता_CREATE);
	req->CreateOptions = cpu_to_le32(CREATE_NOT_खाता);

	iov[0].iov_base = (अक्षर *)req;
	/* -1 since last byte is buf[0] which is sent below (path) */
	iov[0].iov_len = total_len - 1;

	req->NameOffset = cpu_to_le16(माप(काष्ठा smb2_create_req));

	/* [MS-SMB2] 2.2.13 NameOffset:
	 * If SMB2_FLAGS_DFS_OPERATIONS is set in the Flags field of
	 * the SMB2 header, the file name includes a prefix that will
	 * be processed during DFS name normalization as specअगरied in
	 * section 3.3.5.9. Otherwise, the file name is relative to
	 * the share that is identअगरied by the TreeId in the SMB2
	 * header.
	 */
	अगर (tcon->share_flags & SHI1005_FLAGS_DFS) अणु
		पूर्णांक name_len;

		req->sync_hdr.Flags |= SMB2_FLAGS_DFS_OPERATIONS;
		rc = alloc_path_with_tree_prefix(&copy_path, &copy_size,
						 &name_len,
						 tcon->treeName, utf16_path);
		अगर (rc)
			जाओ err_मुक्त_req;

		req->NameLength = cpu_to_le16(name_len * 2);
		uni_path_len = copy_size;
		/* मुक्त beक्रमe overwriting resource */
		kमुक्त(utf16_path);
		utf16_path = copy_path;
	पूर्ण अन्यथा अणु
		uni_path_len = (2 * UniStrnlen((ब_अक्षर_प्रकार *)utf16_path, PATH_MAX)) + 2;
		/* MUST set path len (NameLength) to 0 खोलोing root of share */
		req->NameLength = cpu_to_le16(uni_path_len - 2);
		अगर (uni_path_len % 8 != 0) अणु
			copy_size = roundup(uni_path_len, 8);
			copy_path = kzalloc(copy_size, GFP_KERNEL);
			अगर (!copy_path) अणु
				rc = -ENOMEM;
				जाओ err_मुक्त_req;
			पूर्ण
			स_नकल((अक्षर *)copy_path, (स्थिर अक्षर *)utf16_path,
			       uni_path_len);
			uni_path_len = copy_size;
			/* मुक्त beक्रमe overwriting resource */
			kमुक्त(utf16_path);
			utf16_path = copy_path;
		पूर्ण
	पूर्ण

	iov[1].iov_len = uni_path_len;
	iov[1].iov_base = utf16_path;
	req->RequestedOplockLevel = SMB2_OPLOCK_LEVEL_NONE;

	अगर (tcon->posix_extensions) अणु
		/* resource #3: posix buf */
		rc = add_posix_context(iov, &n_iov, mode);
		अगर (rc)
			जाओ err_मुक्त_req;
		pc_buf = iov[n_iov-1].iov_base;
	पूर्ण


	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = n_iov;

	/* no need to inc num_remote_खोलोs because we बंद it just below */
	trace_smb3_posix_सूची_गढ़ो_enter(xid, tcon->tid, ses->Suid, CREATE_NOT_खाता,
				    खाता_WRITE_ATTRIBUTES);
	/* resource #4: response buffer */
	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags, &rsp_iov);
	अगर (rc) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_CREATE_HE);
		trace_smb3_posix_सूची_गढ़ो_err(xid, tcon->tid, ses->Suid,
					   CREATE_NOT_खाता,
					   खाता_WRITE_ATTRIBUTES, rc);
		जाओ err_मुक्त_rsp_buf;
	पूर्ण

	rsp = (काष्ठा smb2_create_rsp *)rsp_iov.iov_base;
	trace_smb3_posix_सूची_गढ़ो_करोne(xid, rsp->PersistentFileId, tcon->tid,
				    ses->Suid, CREATE_NOT_खाता,
				    खाता_WRITE_ATTRIBUTES);

	SMB2_बंद(xid, tcon, rsp->PersistentFileId, rsp->VolatileFileId);

	/* Eventually save off posix specअगरic response info and बारtaps */

err_मुक्त_rsp_buf:
	मुक्त_rsp_buf(resp_buftype, rsp);
	kमुक्त(pc_buf);
err_मुक्त_req:
	cअगरs_small_buf_release(req);
err_मुक्त_path:
	kमुक्त(utf16_path);
	वापस rc;
पूर्ण

पूर्णांक
SMB2_खोलो_init(काष्ठा cअगरs_tcon *tcon, काष्ठा TCP_Server_Info *server,
	       काष्ठा smb_rqst *rqst, __u8 *oplock,
	       काष्ठा cअगरs_खोलो_parms *oparms, __le16 *path)
अणु
	काष्ठा smb2_create_req *req;
	अचिन्हित पूर्णांक n_iov = 2;
	__u32 file_attributes = 0;
	पूर्णांक copy_size;
	पूर्णांक uni_path_len;
	अचिन्हित पूर्णांक total_len;
	काष्ठा kvec *iov = rqst->rq_iov;
	__le16 *copy_path;
	पूर्णांक rc;

	rc = smb2_plain_req_init(SMB2_CREATE, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	iov[0].iov_base = (अक्षर *)req;
	/* -1 since last byte is buf[0] which is sent below (path) */
	iov[0].iov_len = total_len - 1;

	अगर (oparms->create_options & CREATE_OPTION_READONLY)
		file_attributes |= ATTR_READONLY;
	अगर (oparms->create_options & CREATE_OPTION_SPECIAL)
		file_attributes |= ATTR_SYSTEM;

	req->ImpersonationLevel = IL_IMPERSONATION;
	req->DesiredAccess = cpu_to_le32(oparms->desired_access);
	/* File attributes ignored on खोलो (used in create though) */
	req->FileAttributes = cpu_to_le32(file_attributes);
	req->ShareAccess = खाता_SHARE_ALL_LE;

	req->CreateDisposition = cpu_to_le32(oparms->disposition);
	req->CreateOptions = cpu_to_le32(oparms->create_options & CREATE_OPTIONS_MASK);
	req->NameOffset = cpu_to_le16(माप(काष्ठा smb2_create_req));

	/* [MS-SMB2] 2.2.13 NameOffset:
	 * If SMB2_FLAGS_DFS_OPERATIONS is set in the Flags field of
	 * the SMB2 header, the file name includes a prefix that will
	 * be processed during DFS name normalization as specअगरied in
	 * section 3.3.5.9. Otherwise, the file name is relative to
	 * the share that is identअगरied by the TreeId in the SMB2
	 * header.
	 */
	अगर (tcon->share_flags & SHI1005_FLAGS_DFS) अणु
		पूर्णांक name_len;

		req->sync_hdr.Flags |= SMB2_FLAGS_DFS_OPERATIONS;
		rc = alloc_path_with_tree_prefix(&copy_path, &copy_size,
						 &name_len,
						 tcon->treeName, path);
		अगर (rc)
			वापस rc;
		req->NameLength = cpu_to_le16(name_len * 2);
		uni_path_len = copy_size;
		path = copy_path;
	पूर्ण अन्यथा अणु
		uni_path_len = (2 * UniStrnlen((ब_अक्षर_प्रकार *)path, PATH_MAX)) + 2;
		/* MUST set path len (NameLength) to 0 खोलोing root of share */
		req->NameLength = cpu_to_le16(uni_path_len - 2);
		copy_size = uni_path_len;
		अगर (copy_size % 8 != 0)
			copy_size = roundup(copy_size, 8);
		copy_path = kzalloc(copy_size, GFP_KERNEL);
		अगर (!copy_path)
			वापस -ENOMEM;
		स_नकल((अक्षर *)copy_path, (स्थिर अक्षर *)path,
		       uni_path_len);
		uni_path_len = copy_size;
		path = copy_path;
	पूर्ण

	iov[1].iov_len = uni_path_len;
	iov[1].iov_base = path;

	अगर ((!server->oplocks) || (tcon->no_lease))
		*oplock = SMB2_OPLOCK_LEVEL_NONE;

	अगर (!(server->capabilities & SMB2_GLOBAL_CAP_LEASING) ||
	    *oplock == SMB2_OPLOCK_LEVEL_NONE)
		req->RequestedOplockLevel = *oplock;
	अन्यथा अगर (!(server->capabilities & SMB2_GLOBAL_CAP_सूचीECTORY_LEASING) &&
		  (oparms->create_options & CREATE_NOT_खाता))
		req->RequestedOplockLevel = *oplock; /* no srv lease support */
	अन्यथा अणु
		rc = add_lease_context(server, iov, &n_iov,
				       oparms->fid->lease_key, oplock);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (*oplock == SMB2_OPLOCK_LEVEL_BATCH) अणु
		/* need to set Next field of lease context अगर we request it */
		अगर (server->capabilities & SMB2_GLOBAL_CAP_LEASING) अणु
			काष्ठा create_context *ccontext =
			    (काष्ठा create_context *)iov[n_iov-1].iov_base;
			ccontext->Next =
				cpu_to_le32(server->vals->create_lease_size);
		पूर्ण

		rc = add_durable_context(iov, &n_iov, oparms,
					tcon->use_persistent);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (tcon->posix_extensions) अणु
		अगर (n_iov > 2) अणु
			काष्ठा create_context *ccontext =
			    (काष्ठा create_context *)iov[n_iov-1].iov_base;
			ccontext->Next =
				cpu_to_le32(iov[n_iov-1].iov_len);
		पूर्ण

		rc = add_posix_context(iov, &n_iov, oparms->mode);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (tcon->snapshot_समय) अणु
		cअगरs_dbg(FYI, "adding snapshot context\n");
		अगर (n_iov > 2) अणु
			काष्ठा create_context *ccontext =
			    (काष्ठा create_context *)iov[n_iov-1].iov_base;
			ccontext->Next =
				cpu_to_le32(iov[n_iov-1].iov_len);
		पूर्ण

		rc = add_twarp_context(iov, &n_iov, tcon->snapshot_समय);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर ((oparms->disposition != खाता_OPEN) && (oparms->cअगरs_sb)) अणु
		bool set_mode;
		bool set_owner;

		अगर ((oparms->cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MODE_FROM_SID) &&
		    (oparms->mode != ACL_NO_MODE))
			set_mode = true;
		अन्यथा अणु
			set_mode = false;
			oparms->mode = ACL_NO_MODE;
		पूर्ण

		अगर (oparms->cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_UID_FROM_ACL)
			set_owner = true;
		अन्यथा
			set_owner = false;

		अगर (set_owner | set_mode) अणु
			अगर (n_iov > 2) अणु
				काष्ठा create_context *ccontext =
				    (काष्ठा create_context *)iov[n_iov-1].iov_base;
				ccontext->Next = cpu_to_le32(iov[n_iov-1].iov_len);
			पूर्ण

			cअगरs_dbg(FYI, "add sd with mode 0x%x\n", oparms->mode);
			rc = add_sd_context(iov, &n_iov, oparms->mode, set_owner);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण

	अगर (n_iov > 2) अणु
		काष्ठा create_context *ccontext =
			(काष्ठा create_context *)iov[n_iov-1].iov_base;
		ccontext->Next = cpu_to_le32(iov[n_iov-1].iov_len);
	पूर्ण
	add_query_id_context(iov, &n_iov);

	rqst->rq_nvec = n_iov;
	वापस 0;
पूर्ण

/* rq_iov[0] is the request and is released by cअगरs_small_buf_release().
 * All other vectors are मुक्तd by kमुक्त().
 */
व्योम
SMB2_खोलो_मुक्त(काष्ठा smb_rqst *rqst)
अणु
	पूर्णांक i;

	अगर (rqst && rqst->rq_iov) अणु
		cअगरs_small_buf_release(rqst->rq_iov[0].iov_base);
		क्रम (i = 1; i < rqst->rq_nvec; i++)
			अगर (rqst->rq_iov[i].iov_base != smb2_padding)
				kमुक्त(rqst->rq_iov[i].iov_base);
	पूर्ण
पूर्ण

पूर्णांक
SMB2_खोलो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_खोलो_parms *oparms, __le16 *path,
	  __u8 *oplock, काष्ठा smb2_file_all_info *buf,
	  काष्ठा create_posix_rsp *posix,
	  काष्ठा kvec *err_iov, पूर्णांक *buftype)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_create_rsp *rsp = शून्य;
	काष्ठा cअगरs_tcon *tcon = oparms->tcon;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	काष्ठा kvec iov[SMB2_CREATE_IOV_SIZE];
	काष्ठा kvec rsp_iov = अणुशून्य, 0पूर्ण;
	पूर्णांक resp_buftype = CIFS_NO_BUFFER;
	पूर्णांक rc = 0;
	पूर्णांक flags = 0;

	cअगरs_dbg(FYI, "create/open\n");
	अगर (!ses || !server)
		वापस -EIO;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	स_रखो(&iov, 0, माप(iov));
	rqst.rq_iov = iov;
	rqst.rq_nvec = SMB2_CREATE_IOV_SIZE;

	rc = SMB2_खोलो_init(tcon, server,
			    &rqst, oplock, oparms, path);
	अगर (rc)
		जाओ creat_निकास;

	trace_smb3_खोलो_enter(xid, tcon->tid, tcon->ses->Suid,
		oparms->create_options, oparms->desired_access);

	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags,
			    &rsp_iov);
	rsp = (काष्ठा smb2_create_rsp *)rsp_iov.iov_base;

	अगर (rc != 0) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_CREATE_HE);
		अगर (err_iov && rsp) अणु
			*err_iov = rsp_iov;
			*buftype = resp_buftype;
			resp_buftype = CIFS_NO_BUFFER;
			rsp = शून्य;
		पूर्ण
		trace_smb3_खोलो_err(xid, tcon->tid, ses->Suid,
				    oparms->create_options, oparms->desired_access, rc);
		अगर (rc == -EREMCHG) अणु
			pr_warn_once("server share %s deleted\n",
				     tcon->treeName);
			tcon->need_reconnect = true;
		पूर्ण
		जाओ creat_निकास;
	पूर्ण अन्यथा
		trace_smb3_खोलो_करोne(xid, rsp->PersistentFileId, tcon->tid,
				     ses->Suid, oparms->create_options,
				     oparms->desired_access);

	atomic_inc(&tcon->num_remote_खोलोs);
	oparms->fid->persistent_fid = rsp->PersistentFileId;
	oparms->fid->अस्थिर_fid = rsp->VolatileFileId;
	oparms->fid->access = oparms->desired_access;
#अगर_घोषित CONFIG_CIFS_DEBUG2
	oparms->fid->mid = le64_to_cpu(rsp->sync_hdr.MessageId);
#पूर्ण_अगर /* CIFS_DEBUG2 */

	अगर (buf) अणु
		स_नकल(buf, &rsp->CreationTime, 32);
		buf->AllocationSize = rsp->AllocationSize;
		buf->EndOfFile = rsp->EnकरोfFile;
		buf->Attributes = rsp->FileAttributes;
		buf->NumberOfLinks = cpu_to_le32(1);
		buf->DeletePending = 0;
	पूर्ण


	smb2_parse_contexts(server, rsp, &oparms->fid->epoch,
			    oparms->fid->lease_key, oplock, buf, posix);
creat_निकास:
	SMB2_खोलो_मुक्त(&rqst);
	मुक्त_rsp_buf(resp_buftype, rsp);
	वापस rc;
पूर्ण

पूर्णांक
SMB2_ioctl_init(काष्ठा cअगरs_tcon *tcon, काष्ठा TCP_Server_Info *server,
		काष्ठा smb_rqst *rqst,
		u64 persistent_fid, u64 अस्थिर_fid, u32 opcode,
		bool is_fsctl, अक्षर *in_data, u32 indatalen,
		__u32 max_response_size)
अणु
	काष्ठा smb2_ioctl_req *req;
	काष्ठा kvec *iov = rqst->rq_iov;
	अचिन्हित पूर्णांक total_len;
	पूर्णांक rc;
	अक्षर *in_data_buf;

	rc = smb2_ioctl_req_init(opcode, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	अगर (indatalen) अणु
		/*
		 * indatalen is usually small at a couple of bytes max, so
		 * just allocate through generic pool
		 */
		in_data_buf = kmemdup(in_data, indatalen, GFP_NOFS);
		अगर (!in_data_buf) अणु
			cअगरs_small_buf_release(req);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	req->CtlCode = cpu_to_le32(opcode);
	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = अस्थिर_fid;

	iov[0].iov_base = (अक्षर *)req;
	/*
	 * If no input data, the size of ioctl काष्ठा in
	 * protocol spec still includes a 1 byte data buffer,
	 * but अगर input data passed to ioctl, we करो not
	 * want to द्विगुन count this, so we करो not send
	 * the dummy one byte of data in iovec[0] अगर sending
	 * input data (in iovec[1]).
	 */
	अगर (indatalen) अणु
		req->InputCount = cpu_to_le32(indatalen);
		/* करो not set InputOffset अगर no input data */
		req->InputOffset =
		       cpu_to_le32(दुरत्व(काष्ठा smb2_ioctl_req, Buffer));
		rqst->rq_nvec = 2;
		iov[0].iov_len = total_len - 1;
		iov[1].iov_base = in_data_buf;
		iov[1].iov_len = indatalen;
	पूर्ण अन्यथा अणु
		rqst->rq_nvec = 1;
		iov[0].iov_len = total_len;
	पूर्ण

	req->OutputOffset = 0;
	req->OutputCount = 0; /* MBZ */

	/*
	 * In most हालs max_response_size is set to 16K (CIFSMaxBufSize)
	 * We Could increase शेष MaxOutputResponse, but that could require
	 * more credits. Winकरोws typically sets this smaller, but क्रम some
	 * ioctls it may be useful to allow server to send more. No poपूर्णांक
	 * limiting what the server can send as दीर्घ as fits in one credit
	 * We can not handle more than CIFS_MAX_BUF_SIZE yet but may want
	 * to increase this limit up in the future.
	 * Note that क्रम snapshot queries that servers like Azure expect that
	 * the first query be minimal size (and just used to get the number/size
	 * of previous versions) so response size must be specअगरied as EXACTLY
	 * माप(काष्ठा snapshot_array) which is 16 when rounded up to multiple
	 * of eight bytes.  Currently that is the only हाल where we set max
	 * response size smaller.
	 */
	req->MaxOutputResponse = cpu_to_le32(max_response_size);
	req->sync_hdr.CreditCharge =
		cpu_to_le16(DIV_ROUND_UP(max(indatalen, max_response_size),
					 SMB2_MAX_BUFFER_SIZE));
	अगर (is_fsctl)
		req->Flags = cpu_to_le32(SMB2_0_IOCTL_IS_FSCTL);
	अन्यथा
		req->Flags = 0;

	/* validate negotiate request must be चिन्हित - see MS-SMB2 3.2.5.5 */
	अगर (opcode == FSCTL_VALIDATE_NEGOTIATE_INFO)
		req->sync_hdr.Flags |= SMB2_FLAGS_SIGNED;

	वापस 0;
पूर्ण

व्योम
SMB2_ioctl_मुक्त(काष्ठा smb_rqst *rqst)
अणु
	पूर्णांक i;
	अगर (rqst && rqst->rq_iov) अणु
		cअगरs_small_buf_release(rqst->rq_iov[0].iov_base); /* request */
		क्रम (i = 1; i < rqst->rq_nvec; i++)
			अगर (rqst->rq_iov[i].iov_base != smb2_padding)
				kमुक्त(rqst->rq_iov[i].iov_base);
	पूर्ण
पूर्ण


/*
 *	SMB2 IOCTL is used क्रम both IOCTLs and FSCTLs
 */
पूर्णांक
SMB2_ioctl(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, u64 persistent_fid,
	   u64 अस्थिर_fid, u32 opcode, bool is_fsctl,
	   अक्षर *in_data, u32 indatalen, u32 max_out_data_len,
	   अक्षर **out_data, u32 *plen /* वापसed data len */)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_ioctl_rsp *rsp = शून्य;
	काष्ठा cअगरs_ses *ses;
	काष्ठा TCP_Server_Info *server;
	काष्ठा kvec iov[SMB2_IOCTL_IOV_SIZE];
	काष्ठा kvec rsp_iov = अणुशून्य, 0पूर्ण;
	पूर्णांक resp_buftype = CIFS_NO_BUFFER;
	पूर्णांक rc = 0;
	पूर्णांक flags = 0;

	cअगरs_dbg(FYI, "SMB2 IOCTL\n");

	अगर (out_data != शून्य)
		*out_data = शून्य;

	/* zero out वापसed data len, in हाल of error */
	अगर (plen)
		*plen = 0;

	अगर (!tcon)
		वापस -EIO;

	ses = tcon->ses;
	अगर (!ses)
		वापस -EIO;

	server = cअगरs_pick_channel(ses);
	अगर (!server)
		वापस -EIO;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	स_रखो(&iov, 0, माप(iov));
	rqst.rq_iov = iov;
	rqst.rq_nvec = SMB2_IOCTL_IOV_SIZE;

	rc = SMB2_ioctl_init(tcon, server,
			     &rqst, persistent_fid, अस्थिर_fid, opcode,
			     is_fsctl, in_data, indatalen, max_out_data_len);
	अगर (rc)
		जाओ ioctl_निकास;

	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags,
			    &rsp_iov);
	rsp = (काष्ठा smb2_ioctl_rsp *)rsp_iov.iov_base;

	अगर (rc != 0)
		trace_smb3_fsctl_err(xid, persistent_fid, tcon->tid,
				ses->Suid, 0, opcode, rc);

	अगर ((rc != 0) && (rc != -EINVAL) && (rc != -E2BIG)) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_IOCTL_HE);
		जाओ ioctl_निकास;
	पूर्ण अन्यथा अगर (rc == -EINVAL) अणु
		अगर ((opcode != FSCTL_SRV_COPYCHUNK_WRITE) &&
		    (opcode != FSCTL_SRV_COPYCHUNK)) अणु
			cअगरs_stats_fail_inc(tcon, SMB2_IOCTL_HE);
			जाओ ioctl_निकास;
		पूर्ण
	पूर्ण अन्यथा अगर (rc == -E2BIG) अणु
		अगर (opcode != FSCTL_QUERY_ALLOCATED_RANGES) अणु
			cअगरs_stats_fail_inc(tcon, SMB2_IOCTL_HE);
			जाओ ioctl_निकास;
		पूर्ण
	पूर्ण

	/* check अगर caller wants to look at वापस data or just वापस rc */
	अगर ((plen == शून्य) || (out_data == शून्य))
		जाओ ioctl_निकास;

	*plen = le32_to_cpu(rsp->OutputCount);

	/* We check क्रम obvious errors in the output buffer length and offset */
	अगर (*plen == 0)
		जाओ ioctl_निकास; /* server वापसed no data */
	अन्यथा अगर (*plen > rsp_iov.iov_len || *plen > 0xFF00) अणु
		cअगरs_tcon_dbg(VFS, "srv returned invalid ioctl length: %d\n", *plen);
		*plen = 0;
		rc = -EIO;
		जाओ ioctl_निकास;
	पूर्ण

	अगर (rsp_iov.iov_len - *plen < le32_to_cpu(rsp->OutputOffset)) अणु
		cअगरs_tcon_dbg(VFS, "Malformed ioctl resp: len %d offset %d\n", *plen,
			le32_to_cpu(rsp->OutputOffset));
		*plen = 0;
		rc = -EIO;
		जाओ ioctl_निकास;
	पूर्ण

	*out_data = kmemdup((अक्षर *)rsp + le32_to_cpu(rsp->OutputOffset),
			    *plen, GFP_KERNEL);
	अगर (*out_data == शून्य) अणु
		rc = -ENOMEM;
		जाओ ioctl_निकास;
	पूर्ण

ioctl_निकास:
	SMB2_ioctl_मुक्त(&rqst);
	मुक्त_rsp_buf(resp_buftype, rsp);
	वापस rc;
पूर्ण

/*
 *   Inभागidual callers to ioctl worker function follow
 */

पूर्णांक
SMB2_set_compression(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     u64 persistent_fid, u64 अस्थिर_fid)
अणु
	पूर्णांक rc;
	काष्ठा  compress_ioctl fsctl_input;
	अक्षर *ret_data = शून्य;

	fsctl_input.CompressionState =
			cpu_to_le16(COMPRESSION_FORMAT_DEFAULT);

	rc = SMB2_ioctl(xid, tcon, persistent_fid, अस्थिर_fid,
			FSCTL_SET_COMPRESSION, true /* is_fsctl */,
			(अक्षर *)&fsctl_input /* data input */,
			2 /* in data len */, CIFSMaxBufSize /* max out data */,
			&ret_data /* out data */, शून्य);

	cअगरs_dbg(FYI, "set compression rc %d\n", rc);

	वापस rc;
पूर्ण

पूर्णांक
SMB2_बंद_init(काष्ठा cअगरs_tcon *tcon, काष्ठा TCP_Server_Info *server,
		काष्ठा smb_rqst *rqst,
		u64 persistent_fid, u64 अस्थिर_fid, bool query_attrs)
अणु
	काष्ठा smb2_बंद_req *req;
	काष्ठा kvec *iov = rqst->rq_iov;
	अचिन्हित पूर्णांक total_len;
	पूर्णांक rc;

	rc = smb2_plain_req_init(SMB2_CLOSE, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = अस्थिर_fid;
	अगर (query_attrs)
		req->Flags = SMB2_CLOSE_FLAG_POSTQUERY_ATTRIB;
	अन्यथा
		req->Flags = 0;
	iov[0].iov_base = (अक्षर *)req;
	iov[0].iov_len = total_len;

	वापस 0;
पूर्ण

व्योम
SMB2_बंद_मुक्त(काष्ठा smb_rqst *rqst)
अणु
	अगर (rqst && rqst->rq_iov)
		cअगरs_small_buf_release(rqst->rq_iov[0].iov_base); /* request */
पूर्ण

पूर्णांक
__SMB2_बंद(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	     u64 persistent_fid, u64 अस्थिर_fid,
	     काष्ठा smb2_file_network_खोलो_info *pbuf)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_बंद_rsp *rsp = शून्य;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov;
	पूर्णांक resp_buftype = CIFS_NO_BUFFER;
	पूर्णांक rc = 0;
	पूर्णांक flags = 0;
	bool query_attrs = false;

	cअगरs_dbg(FYI, "Close\n");

	अगर (!ses || !server)
		वापस -EIO;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	स_रखो(&iov, 0, माप(iov));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	/* check अगर need to ask server to वापस बारtamps in बंद response */
	अगर (pbuf)
		query_attrs = true;

	trace_smb3_बंद_enter(xid, persistent_fid, tcon->tid, ses->Suid);
	rc = SMB2_बंद_init(tcon, server,
			     &rqst, persistent_fid, अस्थिर_fid,
			     query_attrs);
	अगर (rc)
		जाओ बंद_निकास;

	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags, &rsp_iov);
	rsp = (काष्ठा smb2_बंद_rsp *)rsp_iov.iov_base;

	अगर (rc != 0) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_CLOSE_HE);
		trace_smb3_बंद_err(xid, persistent_fid, tcon->tid, ses->Suid,
				     rc);
		जाओ बंद_निकास;
	पूर्ण अन्यथा अणु
		trace_smb3_बंद_करोne(xid, persistent_fid, tcon->tid,
				      ses->Suid);
		/*
		 * Note that have to subtract 4 since काष्ठा network_खोलो_info
		 * has a final 4 byte pad that बंद response करोes not have
		 */
		अगर (pbuf)
			स_नकल(pbuf, (अक्षर *)&rsp->CreationTime, माप(*pbuf) - 4);
	पूर्ण

	atomic_dec(&tcon->num_remote_खोलोs);
बंद_निकास:
	SMB2_बंद_मुक्त(&rqst);
	मुक्त_rsp_buf(resp_buftype, rsp);

	/* retry बंद in a worker thपढ़ो अगर this one is पूर्णांकerrupted */
	अगर (is_पूर्णांकerrupt_error(rc)) अणु
		पूर्णांक पंचांगp_rc;

		पंचांगp_rc = smb2_handle_cancelled_बंद(tcon, persistent_fid,
						     अस्थिर_fid);
		अगर (पंचांगp_rc)
			cअगरs_dbg(VFS, "handle cancelled close fid 0x%llx returned error %d\n",
				 persistent_fid, पंचांगp_rc);
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक
SMB2_बंद(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		u64 persistent_fid, u64 अस्थिर_fid)
अणु
	वापस __SMB2_बंद(xid, tcon, persistent_fid, अस्थिर_fid, शून्य);
पूर्ण

पूर्णांक
smb2_validate_iov(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक buffer_length,
		  काष्ठा kvec *iov, अचिन्हित पूर्णांक min_buf_size)
अणु
	अचिन्हित पूर्णांक smb_len = iov->iov_len;
	अक्षर *end_of_smb = smb_len + (अक्षर *)iov->iov_base;
	अक्षर *begin_of_buf = offset + (अक्षर *)iov->iov_base;
	अक्षर *end_of_buf = begin_of_buf + buffer_length;


	अगर (buffer_length < min_buf_size) अणु
		cअगरs_dbg(VFS, "buffer length %d smaller than minimum size %d\n",
			 buffer_length, min_buf_size);
		वापस -EINVAL;
	पूर्ण

	/* check अगर beyond RFC1001 maximum length */
	अगर ((smb_len > 0x7FFFFF) || (buffer_length > 0x7FFFFF)) अणु
		cअगरs_dbg(VFS, "buffer length %d or smb length %d too large\n",
			 buffer_length, smb_len);
		वापस -EINVAL;
	पूर्ण

	अगर ((begin_of_buf > end_of_smb) || (end_of_buf > end_of_smb)) अणु
		cअगरs_dbg(VFS, "Invalid server response, bad offset to data\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If SMB buffer fields are valid, copy पूर्णांकo temporary buffer to hold result.
 * Caller must मुक्त buffer.
 */
पूर्णांक
smb2_validate_and_copy_iov(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक buffer_length,
			   काष्ठा kvec *iov, अचिन्हित पूर्णांक minbufsize,
			   अक्षर *data)
अणु
	अक्षर *begin_of_buf = offset + (अक्षर *)iov->iov_base;
	पूर्णांक rc;

	अगर (!data)
		वापस -EINVAL;

	rc = smb2_validate_iov(offset, buffer_length, iov, minbufsize);
	अगर (rc)
		वापस rc;

	स_नकल(data, begin_of_buf, buffer_length);

	वापस 0;
पूर्ण

पूर्णांक
SMB2_query_info_init(काष्ठा cअगरs_tcon *tcon, काष्ठा TCP_Server_Info *server,
		     काष्ठा smb_rqst *rqst,
		     u64 persistent_fid, u64 अस्थिर_fid,
		     u8 info_class, u8 info_type, u32 additional_info,
		     माप_प्रकार output_len, माप_प्रकार input_len, व्योम *input)
अणु
	काष्ठा smb2_query_info_req *req;
	काष्ठा kvec *iov = rqst->rq_iov;
	अचिन्हित पूर्णांक total_len;
	पूर्णांक rc;

	rc = smb2_plain_req_init(SMB2_QUERY_INFO, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	req->InfoType = info_type;
	req->FileInfoClass = info_class;
	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = अस्थिर_fid;
	req->AdditionalInक्रमmation = cpu_to_le32(additional_info);

	req->OutputBufferLength = cpu_to_le32(output_len);
	अगर (input_len) अणु
		req->InputBufferLength = cpu_to_le32(input_len);
		/* total_len क्रम smb query request never बंद to le16 max */
		req->InputBufferOffset = cpu_to_le16(total_len - 1);
		स_नकल(req->Buffer, input, input_len);
	पूर्ण

	iov[0].iov_base = (अक्षर *)req;
	/* 1 क्रम Buffer */
	iov[0].iov_len = total_len - 1 + input_len;
	वापस 0;
पूर्ण

व्योम
SMB2_query_info_मुक्त(काष्ठा smb_rqst *rqst)
अणु
	अगर (rqst && rqst->rq_iov)
		cअगरs_small_buf_release(rqst->rq_iov[0].iov_base); /* request */
पूर्ण

अटल पूर्णांक
query_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	   u64 persistent_fid, u64 अस्थिर_fid, u8 info_class, u8 info_type,
	   u32 additional_info, माप_प्रकार output_len, माप_प्रकार min_len, व्योम **data,
		u32 *dlen)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_query_info_rsp *rsp = शून्य;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov;
	पूर्णांक rc = 0;
	पूर्णांक resp_buftype = CIFS_NO_BUFFER;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server;
	पूर्णांक flags = 0;
	bool allocated = false;

	cअगरs_dbg(FYI, "Query Info\n");

	अगर (!ses)
		वापस -EIO;
	server = cअगरs_pick_channel(ses);
	अगर (!server)
		वापस -EIO;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	स_रखो(&iov, 0, माप(iov));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	rc = SMB2_query_info_init(tcon, server,
				  &rqst, persistent_fid, अस्थिर_fid,
				  info_class, info_type, additional_info,
				  output_len, 0, शून्य);
	अगर (rc)
		जाओ qinf_निकास;

	trace_smb3_query_info_enter(xid, persistent_fid, tcon->tid,
				    ses->Suid, info_class, (__u32)info_type);

	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags, &rsp_iov);
	rsp = (काष्ठा smb2_query_info_rsp *)rsp_iov.iov_base;

	अगर (rc) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_QUERY_INFO_HE);
		trace_smb3_query_info_err(xid, persistent_fid, tcon->tid,
				ses->Suid, info_class, (__u32)info_type, rc);
		जाओ qinf_निकास;
	पूर्ण

	trace_smb3_query_info_करोne(xid, persistent_fid, tcon->tid,
				ses->Suid, info_class, (__u32)info_type);

	अगर (dlen) अणु
		*dlen = le32_to_cpu(rsp->OutputBufferLength);
		अगर (!*data) अणु
			*data = kदो_स्मृति(*dlen, GFP_KERNEL);
			अगर (!*data) अणु
				cअगरs_tcon_dbg(VFS,
					"Error %d allocating memory for acl\n",
					rc);
				*dlen = 0;
				rc = -ENOMEM;
				जाओ qinf_निकास;
			पूर्ण
			allocated = true;
		पूर्ण
	पूर्ण

	rc = smb2_validate_and_copy_iov(le16_to_cpu(rsp->OutputBufferOffset),
					le32_to_cpu(rsp->OutputBufferLength),
					&rsp_iov, min_len, *data);
	अगर (rc && allocated) अणु
		kमुक्त(*data);
		*data = शून्य;
		*dlen = 0;
	पूर्ण

qinf_निकास:
	SMB2_query_info_मुक्त(&rqst);
	मुक्त_rsp_buf(resp_buftype, rsp);
	वापस rc;
पूर्ण

पूर्णांक SMB2_query_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	u64 persistent_fid, u64 अस्थिर_fid, काष्ठा smb2_file_all_info *data)
अणु
	वापस query_info(xid, tcon, persistent_fid, अस्थिर_fid,
			  खाता_ALL_INFORMATION, SMB2_O_INFO_खाता, 0,
			  माप(काष्ठा smb2_file_all_info) + PATH_MAX * 2,
			  माप(काष्ठा smb2_file_all_info), (व्योम **)&data,
			  शून्य);
पूर्ण

पूर्णांक
SMB311_posix_query_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		u64 persistent_fid, u64 अस्थिर_fid, काष्ठा smb311_posix_qinfo *data, u32 *plen)
अणु
	माप_प्रकार output_len = माप(काष्ठा smb311_posix_qinfo *) +
			(माप(काष्ठा cअगरs_sid) * 2) + (PATH_MAX * 2);
	*plen = 0;

	वापस query_info(xid, tcon, persistent_fid, अस्थिर_fid,
			  SMB_FIND_खाता_POSIX_INFO, SMB2_O_INFO_खाता, 0,
			  output_len, माप(काष्ठा smb311_posix_qinfo), (व्योम **)&data, plen);
पूर्ण

पूर्णांक
SMB2_query_acl(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	       u64 persistent_fid, u64 अस्थिर_fid,
	       व्योम **data, u32 *plen, u32 extra_info)
अणु
	__u32 additional_info = OWNER_SECINFO | GROUP_SECINFO | DACL_SECINFO |
				extra_info;
	*plen = 0;

	वापस query_info(xid, tcon, persistent_fid, अस्थिर_fid,
			  0, SMB2_O_INFO_SECURITY, additional_info,
			  SMB2_MAX_BUFFER_SIZE, MIN_SEC_DESC_LEN, data, plen);
पूर्ण

पूर्णांक
SMB2_get_srv_num(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		 u64 persistent_fid, u64 अस्थिर_fid, __le64 *uniqueid)
अणु
	वापस query_info(xid, tcon, persistent_fid, अस्थिर_fid,
			  खाता_INTERNAL_INFORMATION, SMB2_O_INFO_खाता, 0,
			  माप(काष्ठा smb2_file_पूर्णांकernal_info),
			  माप(काष्ठा smb2_file_पूर्णांकernal_info),
			  (व्योम **)&uniqueid, शून्य);
पूर्ण

/*
 * CHANGE_NOTIFY Request is sent to get notअगरications on changes to a directory
 * See MS-SMB2 2.2.35 and 2.2.36
 */

अटल पूर्णांक
SMB2_notअगरy_init(स्थिर अचिन्हित पूर्णांक xid, काष्ठा smb_rqst *rqst,
		 काष्ठा cअगरs_tcon *tcon, काष्ठा TCP_Server_Info *server,
		 u64 persistent_fid, u64 अस्थिर_fid,
		 u32 completion_filter, bool watch_tree)
अणु
	काष्ठा smb2_change_notअगरy_req *req;
	काष्ठा kvec *iov = rqst->rq_iov;
	अचिन्हित पूर्णांक total_len;
	पूर्णांक rc;

	rc = smb2_plain_req_init(SMB2_CHANGE_NOTIFY, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = अस्थिर_fid;
	/* See note 354 of MS-SMB2, 64K max */
	req->OutputBufferLength =
		cpu_to_le32(SMB2_MAX_BUFFER_SIZE - MAX_SMB2_HDR_SIZE);
	req->CompletionFilter = cpu_to_le32(completion_filter);
	अगर (watch_tree)
		req->Flags = cpu_to_le16(SMB2_WATCH_TREE);
	अन्यथा
		req->Flags = 0;

	iov[0].iov_base = (अक्षर *)req;
	iov[0].iov_len = total_len;

	वापस 0;
पूर्ण

पूर्णांक
SMB2_change_notअगरy(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		u64 persistent_fid, u64 अस्थिर_fid, bool watch_tree,
		u32 completion_filter)
अणु
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	काष्ठा smb_rqst rqst;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov = अणुशून्य, 0पूर्ण;
	पूर्णांक resp_buftype = CIFS_NO_BUFFER;
	पूर्णांक flags = 0;
	पूर्णांक rc = 0;

	cअगरs_dbg(FYI, "change notify\n");
	अगर (!ses || !server)
		वापस -EIO;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	स_रखो(&iov, 0, माप(iov));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	rc = SMB2_notअगरy_init(xid, &rqst, tcon, server,
			      persistent_fid, अस्थिर_fid,
			      completion_filter, watch_tree);
	अगर (rc)
		जाओ cnotअगरy_निकास;

	trace_smb3_notअगरy_enter(xid, persistent_fid, tcon->tid, ses->Suid,
				(u8)watch_tree, completion_filter);
	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags, &rsp_iov);

	अगर (rc != 0) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_CHANGE_NOTIFY_HE);
		trace_smb3_notअगरy_err(xid, persistent_fid, tcon->tid, ses->Suid,
				(u8)watch_tree, completion_filter, rc);
	पूर्ण अन्यथा
		trace_smb3_notअगरy_करोne(xid, persistent_fid, tcon->tid,
				ses->Suid, (u8)watch_tree, completion_filter);

 cnotअगरy_निकास:
	अगर (rqst.rq_iov)
		cअगरs_small_buf_release(rqst.rq_iov[0].iov_base); /* request */
	मुक्त_rsp_buf(resp_buftype, rsp_iov.iov_base);
	वापस rc;
पूर्ण



/*
 * This is a no-op क्रम now. We're not really पूर्णांकerested in the reply, but
 * rather in the fact that the server sent one and that server->lstrp
 * माला_लो updated.
 *
 * FIXME: maybe we should consider checking that the reply matches request?
 */
अटल व्योम
smb2_echo_callback(काष्ठा mid_q_entry *mid)
अणु
	काष्ठा TCP_Server_Info *server = mid->callback_data;
	काष्ठा smb2_echo_rsp *rsp = (काष्ठा smb2_echo_rsp *)mid->resp_buf;
	काष्ठा cअगरs_credits credits = अणु .value = 0, .instance = 0 पूर्ण;

	अगर (mid->mid_state == MID_RESPONSE_RECEIVED
	    || mid->mid_state == MID_RESPONSE_MALFORMED) अणु
		credits.value = le16_to_cpu(rsp->sync_hdr.CreditRequest);
		credits.instance = server->reconnect_instance;
	पूर्ण

	DeleteMidQEntry(mid);
	add_credits(server, &credits, CIFS_ECHO_OP);
पूर्ण

व्योम smb2_reconnect_server(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा TCP_Server_Info *server = container_of(work,
					काष्ठा TCP_Server_Info, reconnect.work);
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon, *tcon2;
	काष्ठा list_head पंचांगp_list;
	पूर्णांक tcon_exist = false;
	पूर्णांक rc;
	पूर्णांक resched = false;


	/* Prevent simultaneous reconnects that can corrupt tcon->rlist list */
	mutex_lock(&server->reconnect_mutex);

	INIT_LIST_HEAD(&पंचांगp_list);
	cअगरs_dbg(FYI, "Need negotiate, reconnecting tcons\n");

	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each_entry(ses, &server->smb_ses_list, smb_ses_list) अणु
		list_क्रम_each_entry(tcon, &ses->tcon_list, tcon_list) अणु
			अगर (tcon->need_reconnect || tcon->need_reखोलो_files) अणु
				tcon->tc_count++;
				list_add_tail(&tcon->rlist, &पंचांगp_list);
				tcon_exist = true;
			पूर्ण
		पूर्ण
		/*
		 * IPC has the same lअगरeसमय as its session and uses its
		 * refcount.
		 */
		अगर (ses->tcon_ipc && ses->tcon_ipc->need_reconnect) अणु
			list_add_tail(&ses->tcon_ipc->rlist, &पंचांगp_list);
			tcon_exist = true;
			ses->ses_count++;
		पूर्ण
	पूर्ण
	/*
	 * Get the reference to server काष्ठा to be sure that the last call of
	 * cअगरs_put_tcon() in the loop below won't release the server poपूर्णांकer.
	 */
	अगर (tcon_exist)
		server->srv_count++;

	spin_unlock(&cअगरs_tcp_ses_lock);

	list_क्रम_each_entry_safe(tcon, tcon2, &पंचांगp_list, rlist) अणु
		rc = smb2_reconnect(SMB2_INTERNAL_CMD, tcon, server);
		अगर (!rc)
			cअगरs_reखोलो_persistent_handles(tcon);
		अन्यथा
			resched = true;
		list_del_init(&tcon->rlist);
		अगर (tcon->ipc)
			cअगरs_put_smb_ses(tcon->ses);
		अन्यथा
			cअगरs_put_tcon(tcon);
	पूर्ण

	cअगरs_dbg(FYI, "Reconnecting tcons finished\n");
	अगर (resched)
		queue_delayed_work(cअगरsiod_wq, &server->reconnect, 2 * HZ);
	mutex_unlock(&server->reconnect_mutex);

	/* now we can safely release srv काष्ठा */
	अगर (tcon_exist)
		cअगरs_put_tcp_session(server, 1);
पूर्ण

पूर्णांक
SMB2_echo(काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा smb2_echo_req *req;
	पूर्णांक rc = 0;
	काष्ठा kvec iov[1];
	काष्ठा smb_rqst rqst = अणु .rq_iov = iov,
				 .rq_nvec = 1 पूर्ण;
	अचिन्हित पूर्णांक total_len;

	cअगरs_dbg(FYI, "In echo request\n");

	अगर (server->tcpStatus == CअगरsNeedNegotiate) अणु
		/* No need to send echo on newly established connections */
		mod_delayed_work(cअगरsiod_wq, &server->reconnect, 0);
		वापस rc;
	पूर्ण

	rc = smb2_plain_req_init(SMB2_ECHO, शून्य, server,
				 (व्योम **)&req, &total_len);
	अगर (rc)
		वापस rc;

	req->sync_hdr.CreditRequest = cpu_to_le16(1);

	iov[0].iov_len = total_len;
	iov[0].iov_base = (अक्षर *)req;

	rc = cअगरs_call_async(server, &rqst, शून्य, smb2_echo_callback, शून्य,
			     server, CIFS_ECHO_OP, शून्य);
	अगर (rc)
		cअगरs_dbg(FYI, "Echo request failed: %d\n", rc);

	cअगरs_small_buf_release(req);
	वापस rc;
पूर्ण

व्योम
SMB2_flush_मुक्त(काष्ठा smb_rqst *rqst)
अणु
	अगर (rqst && rqst->rq_iov)
		cअगरs_small_buf_release(rqst->rq_iov[0].iov_base); /* request */
पूर्ण

पूर्णांक
SMB2_flush_init(स्थिर अचिन्हित पूर्णांक xid, काष्ठा smb_rqst *rqst,
		काष्ठा cअगरs_tcon *tcon, काष्ठा TCP_Server_Info *server,
		u64 persistent_fid, u64 अस्थिर_fid)
अणु
	काष्ठा smb2_flush_req *req;
	काष्ठा kvec *iov = rqst->rq_iov;
	अचिन्हित पूर्णांक total_len;
	पूर्णांक rc;

	rc = smb2_plain_req_init(SMB2_FLUSH, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = अस्थिर_fid;

	iov[0].iov_base = (अक्षर *)req;
	iov[0].iov_len = total_len;

	वापस 0;
पूर्ण

पूर्णांक
SMB2_flush(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, u64 persistent_fid,
	   u64 अस्थिर_fid)
अणु
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा smb_rqst rqst;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov = अणुशून्य, 0पूर्ण;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	पूर्णांक resp_buftype = CIFS_NO_BUFFER;
	पूर्णांक flags = 0;
	पूर्णांक rc = 0;

	cअगरs_dbg(FYI, "flush\n");
	अगर (!ses || !(ses->server))
		वापस -EIO;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	स_रखो(&iov, 0, माप(iov));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	rc = SMB2_flush_init(xid, &rqst, tcon, server,
			     persistent_fid, अस्थिर_fid);
	अगर (rc)
		जाओ flush_निकास;

	trace_smb3_flush_enter(xid, persistent_fid, tcon->tid, ses->Suid);
	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags, &rsp_iov);

	अगर (rc != 0) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_FLUSH_HE);
		trace_smb3_flush_err(xid, persistent_fid, tcon->tid, ses->Suid,
				     rc);
	पूर्ण अन्यथा
		trace_smb3_flush_करोne(xid, persistent_fid, tcon->tid,
				      ses->Suid);

 flush_निकास:
	SMB2_flush_मुक्त(&rqst);
	मुक्त_rsp_buf(resp_buftype, rsp_iov.iov_base);
	वापस rc;
पूर्ण

/*
 * To क्रमm a chain of पढ़ो requests, any पढ़ो requests after the first should
 * have the end_of_chain boolean set to true.
 */
अटल पूर्णांक
smb2_new_पढ़ो_req(व्योम **buf, अचिन्हित पूर्णांक *total_len,
	काष्ठा cअगरs_io_parms *io_parms, काष्ठा cअगरs_पढ़ोdata *rdata,
	अचिन्हित पूर्णांक reमुख्यing_bytes, पूर्णांक request_type)
अणु
	पूर्णांक rc = -EACCES;
	काष्ठा smb2_पढ़ो_plain_req *req = शून्य;
	काष्ठा smb2_sync_hdr *shdr;
	काष्ठा TCP_Server_Info *server = io_parms->server;

	rc = smb2_plain_req_init(SMB2_READ, io_parms->tcon, server,
				 (व्योम **) &req, total_len);
	अगर (rc)
		वापस rc;

	अगर (server == शून्य)
		वापस -ECONNABORTED;

	shdr = &req->sync_hdr;
	shdr->ProcessId = cpu_to_le32(io_parms->pid);

	req->PersistentFileId = io_parms->persistent_fid;
	req->VolatileFileId = io_parms->अस्थिर_fid;
	req->ReadChannelInfoOffset = 0; /* reserved */
	req->ReadChannelInfoLength = 0; /* reserved */
	req->Channel = 0; /* reserved */
	req->MinimumCount = 0;
	req->Length = cpu_to_le32(io_parms->length);
	req->Offset = cpu_to_le64(io_parms->offset);

	trace_smb3_पढ़ो_enter(0 /* xid */,
			io_parms->persistent_fid,
			io_parms->tcon->tid, io_parms->tcon->ses->Suid,
			io_parms->offset, io_parms->length);
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	/*
	 * If we want to करो a RDMA ग_लिखो, fill in and append
	 * smbd_buffer_descriptor_v1 to the end of पढ़ो request
	 */
	अगर (server->rdma && rdata && !server->sign &&
		rdata->bytes >= server->smbd_conn->rdma_पढ़ोग_लिखो_threshold) अणु

		काष्ठा smbd_buffer_descriptor_v1 *v1;
		bool need_invalidate = server->dialect == SMB30_PROT_ID;

		rdata->mr = smbd_रेजिस्टर_mr(
				server->smbd_conn, rdata->pages,
				rdata->nr_pages, rdata->page_offset,
				rdata->tailsz, true, need_invalidate);
		अगर (!rdata->mr)
			वापस -EAGAIN;

		req->Channel = SMB2_CHANNEL_RDMA_V1_INVALIDATE;
		अगर (need_invalidate)
			req->Channel = SMB2_CHANNEL_RDMA_V1;
		req->ReadChannelInfoOffset =
			cpu_to_le16(दुरत्व(काष्ठा smb2_पढ़ो_plain_req, Buffer));
		req->ReadChannelInfoLength =
			cpu_to_le16(माप(काष्ठा smbd_buffer_descriptor_v1));
		v1 = (काष्ठा smbd_buffer_descriptor_v1 *) &req->Buffer[0];
		v1->offset = cpu_to_le64(rdata->mr->mr->iova);
		v1->token = cpu_to_le32(rdata->mr->mr->rkey);
		v1->length = cpu_to_le32(rdata->mr->mr->length);

		*total_len += माप(*v1) - 1;
	पूर्ण
#पूर्ण_अगर
	अगर (request_type & CHAINED_REQUEST) अणु
		अगर (!(request_type & END_OF_CHAIN)) अणु
			/* next 8-byte aligned request */
			*total_len = DIV_ROUND_UP(*total_len, 8) * 8;
			shdr->NextCommand = cpu_to_le32(*total_len);
		पूर्ण अन्यथा /* END_OF_CHAIN */
			shdr->NextCommand = 0;
		अगर (request_type & RELATED_REQUEST) अणु
			shdr->Flags |= SMB2_FLAGS_RELATED_OPERATIONS;
			/*
			 * Related requests use info from previous पढ़ो request
			 * in chain.
			 */
			shdr->SessionId = 0xFFFFFFFFFFFFFFFF;
			shdr->TreeId = 0xFFFFFFFF;
			req->PersistentFileId = 0xFFFFFFFFFFFFFFFF;
			req->VolatileFileId = 0xFFFFFFFFFFFFFFFF;
		पूर्ण
	पूर्ण
	अगर (reमुख्यing_bytes > io_parms->length)
		req->Reमुख्यingBytes = cpu_to_le32(reमुख्यing_bytes);
	अन्यथा
		req->Reमुख्यingBytes = 0;

	*buf = req;
	वापस rc;
पूर्ण

अटल व्योम
smb2_पढ़ोv_callback(काष्ठा mid_q_entry *mid)
अणु
	काष्ठा cअगरs_पढ़ोdata *rdata = mid->callback_data;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(rdata->cfile->tlink);
	काष्ठा TCP_Server_Info *server = rdata->server;
	काष्ठा smb2_sync_hdr *shdr =
				(काष्ठा smb2_sync_hdr *)rdata->iov[0].iov_base;
	काष्ठा cअगरs_credits credits = अणु .value = 0, .instance = 0 पूर्ण;
	काष्ठा smb_rqst rqst = अणु .rq_iov = &rdata->iov[1],
				 .rq_nvec = 1,
				 .rq_pages = rdata->pages,
				 .rq_offset = rdata->page_offset,
				 .rq_npages = rdata->nr_pages,
				 .rq_pagesz = rdata->pagesz,
				 .rq_tailsz = rdata->tailsz पूर्ण;

	WARN_ONCE(rdata->server != mid->server,
		  "rdata server %p != mid server %p",
		  rdata->server, mid->server);

	cअगरs_dbg(FYI, "%s: mid=%llu state=%d result=%d bytes=%u\n",
		 __func__, mid->mid, mid->mid_state, rdata->result,
		 rdata->bytes);

	चयन (mid->mid_state) अणु
	हाल MID_RESPONSE_RECEIVED:
		credits.value = le16_to_cpu(shdr->CreditRequest);
		credits.instance = server->reconnect_instance;
		/* result alपढ़ोy set, check signature */
		अगर (server->sign && !mid->decrypted) अणु
			पूर्णांक rc;

			rc = smb2_verअगरy_signature(&rqst, server);
			अगर (rc)
				cअगरs_tcon_dbg(VFS, "SMB signature verification returned error = %d\n",
					 rc);
		पूर्ण
		/* FIXME: should this be counted toward the initiating task? */
		task_io_account_पढ़ो(rdata->got_bytes);
		cअगरs_stats_bytes_पढ़ो(tcon, rdata->got_bytes);
		अवरोध;
	हाल MID_REQUEST_SUBMITTED:
	हाल MID_RETRY_NEEDED:
		rdata->result = -EAGAIN;
		अगर (server->sign && rdata->got_bytes)
			/* reset bytes number since we can not check a sign */
			rdata->got_bytes = 0;
		/* FIXME: should this be counted toward the initiating task? */
		task_io_account_पढ़ो(rdata->got_bytes);
		cअगरs_stats_bytes_पढ़ो(tcon, rdata->got_bytes);
		अवरोध;
	हाल MID_RESPONSE_MALFORMED:
		credits.value = le16_to_cpu(shdr->CreditRequest);
		credits.instance = server->reconnect_instance;
		fallthrough;
	शेष:
		rdata->result = -EIO;
	पूर्ण
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	/*
	 * If this rdata has a memmory रेजिस्टरed, the MR can be मुक्तd
	 * MR needs to be मुक्तd as soon as I/O finishes to prevent deadlock
	 * because they have limited number and are used क्रम future I/Os
	 */
	अगर (rdata->mr) अणु
		smbd_deरेजिस्टर_mr(rdata->mr);
		rdata->mr = शून्य;
	पूर्ण
#पूर्ण_अगर
	अगर (rdata->result && rdata->result != -ENODATA) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_READ_HE);
		trace_smb3_पढ़ो_err(0 /* xid */,
				    rdata->cfile->fid.persistent_fid,
				    tcon->tid, tcon->ses->Suid, rdata->offset,
				    rdata->bytes, rdata->result);
	पूर्ण अन्यथा
		trace_smb3_पढ़ो_करोne(0 /* xid */,
				     rdata->cfile->fid.persistent_fid,
				     tcon->tid, tcon->ses->Suid,
				     rdata->offset, rdata->got_bytes);

	queue_work(cअगरsiod_wq, &rdata->work);
	DeleteMidQEntry(mid);
	add_credits(server, &credits, 0);
पूर्ण

/* smb2_async_पढ़ोv - send an async पढ़ो, and set up mid to handle result */
पूर्णांक
smb2_async_पढ़ोv(काष्ठा cअगरs_पढ़ोdata *rdata)
अणु
	पूर्णांक rc, flags = 0;
	अक्षर *buf;
	काष्ठा smb2_sync_hdr *shdr;
	काष्ठा cअगरs_io_parms io_parms;
	काष्ठा smb_rqst rqst = अणु .rq_iov = rdata->iov,
				 .rq_nvec = 1 पूर्ण;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(rdata->cfile->tlink);
	अचिन्हित पूर्णांक total_len;

	cअगरs_dbg(FYI, "%s: offset=%llu bytes=%u\n",
		 __func__, rdata->offset, rdata->bytes);

	अगर (!rdata->server)
		rdata->server = cअगरs_pick_channel(tcon->ses);

	io_parms.tcon = tlink_tcon(rdata->cfile->tlink);
	io_parms.server = server = rdata->server;
	io_parms.offset = rdata->offset;
	io_parms.length = rdata->bytes;
	io_parms.persistent_fid = rdata->cfile->fid.persistent_fid;
	io_parms.अस्थिर_fid = rdata->cfile->fid.अस्थिर_fid;
	io_parms.pid = rdata->pid;

	rc = smb2_new_पढ़ो_req(
		(व्योम **) &buf, &total_len, &io_parms, rdata, 0, 0);
	अगर (rc)
		वापस rc;

	अगर (smb3_encryption_required(io_parms.tcon))
		flags |= CIFS_TRANSFORM_REQ;

	rdata->iov[0].iov_base = buf;
	rdata->iov[0].iov_len = total_len;

	shdr = (काष्ठा smb2_sync_hdr *)buf;

	अगर (rdata->credits.value > 0) अणु
		shdr->CreditCharge = cpu_to_le16(DIV_ROUND_UP(rdata->bytes,
						SMB2_MAX_BUFFER_SIZE));
		shdr->CreditRequest = cpu_to_le16(le16_to_cpu(shdr->CreditCharge) + 8);

		rc = adjust_credits(server, &rdata->credits, rdata->bytes);
		अगर (rc)
			जाओ async_पढ़ोv_out;

		flags |= CIFS_HAS_CREDITS;
	पूर्ण

	kref_get(&rdata->refcount);
	rc = cअगरs_call_async(server, &rqst,
			     cअगरs_पढ़ोv_receive, smb2_पढ़ोv_callback,
			     smb3_handle_पढ़ो_data, rdata, flags,
			     &rdata->credits);
	अगर (rc) अणु
		kref_put(&rdata->refcount, cअगरs_पढ़ोdata_release);
		cअगरs_stats_fail_inc(io_parms.tcon, SMB2_READ_HE);
		trace_smb3_पढ़ो_err(0 /* xid */, io_parms.persistent_fid,
				    io_parms.tcon->tid,
				    io_parms.tcon->ses->Suid,
				    io_parms.offset, io_parms.length, rc);
	पूर्ण

async_पढ़ोv_out:
	cअगरs_small_buf_release(buf);
	वापस rc;
पूर्ण

पूर्णांक
SMB2_पढ़ो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_io_parms *io_parms,
	  अचिन्हित पूर्णांक *nbytes, अक्षर **buf, पूर्णांक *buf_type)
अणु
	काष्ठा smb_rqst rqst;
	पूर्णांक resp_buftype, rc;
	काष्ठा smb2_पढ़ो_plain_req *req = शून्य;
	काष्ठा smb2_पढ़ो_rsp *rsp = शून्य;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov;
	अचिन्हित पूर्णांक total_len;
	पूर्णांक flags = CIFS_LOG_ERROR;
	काष्ठा cअगरs_ses *ses = io_parms->tcon->ses;

	अगर (!io_parms->server)
		io_parms->server = cअगरs_pick_channel(io_parms->tcon->ses);

	*nbytes = 0;
	rc = smb2_new_पढ़ो_req((व्योम **)&req, &total_len, io_parms, शून्य, 0, 0);
	अगर (rc)
		वापस rc;

	अगर (smb3_encryption_required(io_parms->tcon))
		flags |= CIFS_TRANSFORM_REQ;

	iov[0].iov_base = (अक्षर *)req;
	iov[0].iov_len = total_len;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	rc = cअगरs_send_recv(xid, ses, io_parms->server,
			    &rqst, &resp_buftype, flags, &rsp_iov);
	rsp = (काष्ठा smb2_पढ़ो_rsp *)rsp_iov.iov_base;

	अगर (rc) अणु
		अगर (rc != -ENODATA) अणु
			cअगरs_stats_fail_inc(io_parms->tcon, SMB2_READ_HE);
			cअगरs_dbg(VFS, "Send error in read = %d\n", rc);
			trace_smb3_पढ़ो_err(xid, req->PersistentFileId,
					    io_parms->tcon->tid, ses->Suid,
					    io_parms->offset, io_parms->length,
					    rc);
		पूर्ण अन्यथा
			trace_smb3_पढ़ो_करोne(xid, req->PersistentFileId,
				    io_parms->tcon->tid, ses->Suid,
				    io_parms->offset, 0);
		मुक्त_rsp_buf(resp_buftype, rsp_iov.iov_base);
		cअगरs_small_buf_release(req);
		वापस rc == -ENODATA ? 0 : rc;
	पूर्ण अन्यथा
		trace_smb3_पढ़ो_करोne(xid, req->PersistentFileId,
				    io_parms->tcon->tid, ses->Suid,
				    io_parms->offset, io_parms->length);

	cअगरs_small_buf_release(req);

	*nbytes = le32_to_cpu(rsp->DataLength);
	अगर ((*nbytes > CIFS_MAX_MSGSIZE) ||
	    (*nbytes > io_parms->length)) अणु
		cअगरs_dbg(FYI, "bad length %d for count %d\n",
			 *nbytes, io_parms->length);
		rc = -EIO;
		*nbytes = 0;
	पूर्ण

	अगर (*buf) अणु
		स_नकल(*buf, (अक्षर *)rsp + rsp->DataOffset, *nbytes);
		मुक्त_rsp_buf(resp_buftype, rsp_iov.iov_base);
	पूर्ण अन्यथा अगर (resp_buftype != CIFS_NO_BUFFER) अणु
		*buf = rsp_iov.iov_base;
		अगर (resp_buftype == CIFS_SMALL_BUFFER)
			*buf_type = CIFS_SMALL_BUFFER;
		अन्यथा अगर (resp_buftype == CIFS_LARGE_BUFFER)
			*buf_type = CIFS_LARGE_BUFFER;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Check the mid_state and signature on received buffer (अगर any), and queue the
 * workqueue completion task.
 */
अटल व्योम
smb2_ग_लिखोv_callback(काष्ठा mid_q_entry *mid)
अणु
	काष्ठा cअगरs_ग_लिखोdata *wdata = mid->callback_data;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(wdata->cfile->tlink);
	काष्ठा TCP_Server_Info *server = wdata->server;
	अचिन्हित पूर्णांक written;
	काष्ठा smb2_ग_लिखो_rsp *rsp = (काष्ठा smb2_ग_लिखो_rsp *)mid->resp_buf;
	काष्ठा cअगरs_credits credits = अणु .value = 0, .instance = 0 पूर्ण;

	WARN_ONCE(wdata->server != mid->server,
		  "wdata server %p != mid server %p",
		  wdata->server, mid->server);

	चयन (mid->mid_state) अणु
	हाल MID_RESPONSE_RECEIVED:
		credits.value = le16_to_cpu(rsp->sync_hdr.CreditRequest);
		credits.instance = server->reconnect_instance;
		wdata->result = smb2_check_receive(mid, server, 0);
		अगर (wdata->result != 0)
			अवरोध;

		written = le32_to_cpu(rsp->DataLength);
		/*
		 * Mask off high 16 bits when bytes written as वापसed
		 * by the server is greater than bytes requested by the
		 * client. OS/2 servers are known to set incorrect
		 * CountHigh values.
		 */
		अगर (written > wdata->bytes)
			written &= 0xFFFF;

		अगर (written < wdata->bytes)
			wdata->result = -ENOSPC;
		अन्यथा
			wdata->bytes = written;
		अवरोध;
	हाल MID_REQUEST_SUBMITTED:
	हाल MID_RETRY_NEEDED:
		wdata->result = -EAGAIN;
		अवरोध;
	हाल MID_RESPONSE_MALFORMED:
		credits.value = le16_to_cpu(rsp->sync_hdr.CreditRequest);
		credits.instance = server->reconnect_instance;
		fallthrough;
	शेष:
		wdata->result = -EIO;
		अवरोध;
	पूर्ण
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	/*
	 * If this wdata has a memory रेजिस्टरed, the MR can be मुक्तd
	 * The number of MRs available is limited, it's important to recover
	 * used MR as soon as I/O is finished. Hold MR दीर्घer in the later
	 * I/O process can possibly result in I/O deadlock due to lack of MR
	 * to send request on I/O retry
	 */
	अगर (wdata->mr) अणु
		smbd_deरेजिस्टर_mr(wdata->mr);
		wdata->mr = शून्य;
	पूर्ण
#पूर्ण_अगर
	अगर (wdata->result) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_WRITE_HE);
		trace_smb3_ग_लिखो_err(0 /* no xid */,
				     wdata->cfile->fid.persistent_fid,
				     tcon->tid, tcon->ses->Suid, wdata->offset,
				     wdata->bytes, wdata->result);
		अगर (wdata->result == -ENOSPC)
			pr_warn_once("Out of space writing to %s\n",
				     tcon->treeName);
	पूर्ण अन्यथा
		trace_smb3_ग_लिखो_करोne(0 /* no xid */,
				      wdata->cfile->fid.persistent_fid,
				      tcon->tid, tcon->ses->Suid,
				      wdata->offset, wdata->bytes);

	queue_work(cअगरsiod_wq, &wdata->work);
	DeleteMidQEntry(mid);
	add_credits(server, &credits, 0);
पूर्ण

/* smb2_async_ग_लिखोv - send an async ग_लिखो, and set up mid to handle result */
पूर्णांक
smb2_async_ग_लिखोv(काष्ठा cअगरs_ग_लिखोdata *wdata,
		  व्योम (*release)(काष्ठा kref *kref))
अणु
	पूर्णांक rc = -EACCES, flags = 0;
	काष्ठा smb2_ग_लिखो_req *req = शून्य;
	काष्ठा smb2_sync_hdr *shdr;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(wdata->cfile->tlink);
	काष्ठा TCP_Server_Info *server = wdata->server;
	काष्ठा kvec iov[1];
	काष्ठा smb_rqst rqst = अणु पूर्ण;
	अचिन्हित पूर्णांक total_len;

	अगर (!wdata->server)
		server = wdata->server = cअगरs_pick_channel(tcon->ses);

	rc = smb2_plain_req_init(SMB2_WRITE, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	shdr = (काष्ठा smb2_sync_hdr *)req;
	shdr->ProcessId = cpu_to_le32(wdata->cfile->pid);

	req->PersistentFileId = wdata->cfile->fid.persistent_fid;
	req->VolatileFileId = wdata->cfile->fid.अस्थिर_fid;
	req->WriteChannelInfoOffset = 0;
	req->WriteChannelInfoLength = 0;
	req->Channel = 0;
	req->Offset = cpu_to_le64(wdata->offset);
	req->DataOffset = cpu_to_le16(
				दुरत्व(काष्ठा smb2_ग_लिखो_req, Buffer));
	req->Reमुख्यingBytes = 0;

	trace_smb3_ग_लिखो_enter(0 /* xid */, wdata->cfile->fid.persistent_fid,
		tcon->tid, tcon->ses->Suid, wdata->offset, wdata->bytes);
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	/*
	 * If we want to करो a server RDMA पढ़ो, fill in and append
	 * smbd_buffer_descriptor_v1 to the end of ग_लिखो request
	 */
	अगर (server->rdma && !server->sign && wdata->bytes >=
		server->smbd_conn->rdma_पढ़ोग_लिखो_threshold) अणु

		काष्ठा smbd_buffer_descriptor_v1 *v1;
		bool need_invalidate = server->dialect == SMB30_PROT_ID;

		wdata->mr = smbd_रेजिस्टर_mr(
				server->smbd_conn, wdata->pages,
				wdata->nr_pages, wdata->page_offset,
				wdata->tailsz, false, need_invalidate);
		अगर (!wdata->mr) अणु
			rc = -EAGAIN;
			जाओ async_ग_लिखोv_out;
		पूर्ण
		req->Length = 0;
		req->DataOffset = 0;
		अगर (wdata->nr_pages > 1)
			req->Reमुख्यingBytes =
				cpu_to_le32(
					(wdata->nr_pages - 1) * wdata->pagesz -
					wdata->page_offset + wdata->tailsz
				);
		अन्यथा
			req->Reमुख्यingBytes = cpu_to_le32(wdata->tailsz);
		req->Channel = SMB2_CHANNEL_RDMA_V1_INVALIDATE;
		अगर (need_invalidate)
			req->Channel = SMB2_CHANNEL_RDMA_V1;
		req->WriteChannelInfoOffset =
			cpu_to_le16(दुरत्व(काष्ठा smb2_ग_लिखो_req, Buffer));
		req->WriteChannelInfoLength =
			cpu_to_le16(माप(काष्ठा smbd_buffer_descriptor_v1));
		v1 = (काष्ठा smbd_buffer_descriptor_v1 *) &req->Buffer[0];
		v1->offset = cpu_to_le64(wdata->mr->mr->iova);
		v1->token = cpu_to_le32(wdata->mr->mr->rkey);
		v1->length = cpu_to_le32(wdata->mr->mr->length);
	पूर्ण
#पूर्ण_अगर
	iov[0].iov_len = total_len - 1;
	iov[0].iov_base = (अक्षर *)req;

	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;
	rqst.rq_pages = wdata->pages;
	rqst.rq_offset = wdata->page_offset;
	rqst.rq_npages = wdata->nr_pages;
	rqst.rq_pagesz = wdata->pagesz;
	rqst.rq_tailsz = wdata->tailsz;
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	अगर (wdata->mr) अणु
		iov[0].iov_len += माप(काष्ठा smbd_buffer_descriptor_v1);
		rqst.rq_npages = 0;
	पूर्ण
#पूर्ण_अगर
	cअगरs_dbg(FYI, "async write at %llu %u bytes\n",
		 wdata->offset, wdata->bytes);

#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	/* For RDMA पढ़ो, I/O size is in Reमुख्यingBytes not in Length */
	अगर (!wdata->mr)
		req->Length = cpu_to_le32(wdata->bytes);
#अन्यथा
	req->Length = cpu_to_le32(wdata->bytes);
#पूर्ण_अगर

	अगर (wdata->credits.value > 0) अणु
		shdr->CreditCharge = cpu_to_le16(DIV_ROUND_UP(wdata->bytes,
						    SMB2_MAX_BUFFER_SIZE));
		shdr->CreditRequest = cpu_to_le16(le16_to_cpu(shdr->CreditCharge) + 8);

		rc = adjust_credits(server, &wdata->credits, wdata->bytes);
		अगर (rc)
			जाओ async_ग_लिखोv_out;

		flags |= CIFS_HAS_CREDITS;
	पूर्ण

	kref_get(&wdata->refcount);
	rc = cअगरs_call_async(server, &rqst, शून्य, smb2_ग_लिखोv_callback, शून्य,
			     wdata, flags, &wdata->credits);

	अगर (rc) अणु
		trace_smb3_ग_लिखो_err(0 /* no xid */, req->PersistentFileId,
				     tcon->tid, tcon->ses->Suid, wdata->offset,
				     wdata->bytes, rc);
		kref_put(&wdata->refcount, release);
		cअगरs_stats_fail_inc(tcon, SMB2_WRITE_HE);
	पूर्ण

async_ग_लिखोv_out:
	cअगरs_small_buf_release(req);
	वापस rc;
पूर्ण

/*
 * SMB2_ग_लिखो function माला_लो iov poपूर्णांकer to kvec array with n_vec as a length.
 * The length field from io_parms must be at least 1 and indicates a number of
 * elements with data to ग_लिखो that begins with position 1 in iov array. All
 * data length is specअगरied by count.
 */
पूर्णांक
SMB2_ग_लिखो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_io_parms *io_parms,
	   अचिन्हित पूर्णांक *nbytes, काष्ठा kvec *iov, पूर्णांक n_vec)
अणु
	काष्ठा smb_rqst rqst;
	पूर्णांक rc = 0;
	काष्ठा smb2_ग_लिखो_req *req = शून्य;
	काष्ठा smb2_ग_लिखो_rsp *rsp = शून्य;
	पूर्णांक resp_buftype;
	काष्ठा kvec rsp_iov;
	पूर्णांक flags = 0;
	अचिन्हित पूर्णांक total_len;
	काष्ठा TCP_Server_Info *server;

	*nbytes = 0;

	अगर (n_vec < 1)
		वापस rc;

	अगर (!io_parms->server)
		io_parms->server = cअगरs_pick_channel(io_parms->tcon->ses);
	server = io_parms->server;
	अगर (server == शून्य)
		वापस -ECONNABORTED;

	rc = smb2_plain_req_init(SMB2_WRITE, io_parms->tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	अगर (smb3_encryption_required(io_parms->tcon))
		flags |= CIFS_TRANSFORM_REQ;

	req->sync_hdr.ProcessId = cpu_to_le32(io_parms->pid);

	req->PersistentFileId = io_parms->persistent_fid;
	req->VolatileFileId = io_parms->अस्थिर_fid;
	req->WriteChannelInfoOffset = 0;
	req->WriteChannelInfoLength = 0;
	req->Channel = 0;
	req->Length = cpu_to_le32(io_parms->length);
	req->Offset = cpu_to_le64(io_parms->offset);
	req->DataOffset = cpu_to_le16(
				दुरत्व(काष्ठा smb2_ग_लिखो_req, Buffer));
	req->Reमुख्यingBytes = 0;

	trace_smb3_ग_लिखो_enter(xid, io_parms->persistent_fid,
		io_parms->tcon->tid, io_parms->tcon->ses->Suid,
		io_parms->offset, io_parms->length);

	iov[0].iov_base = (अक्षर *)req;
	/* 1 क्रम Buffer */
	iov[0].iov_len = total_len - 1;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = n_vec + 1;

	rc = cअगरs_send_recv(xid, io_parms->tcon->ses, server,
			    &rqst,
			    &resp_buftype, flags, &rsp_iov);
	rsp = (काष्ठा smb2_ग_लिखो_rsp *)rsp_iov.iov_base;

	अगर (rc) अणु
		trace_smb3_ग_लिखो_err(xid, req->PersistentFileId,
				     io_parms->tcon->tid,
				     io_parms->tcon->ses->Suid,
				     io_parms->offset, io_parms->length, rc);
		cअगरs_stats_fail_inc(io_parms->tcon, SMB2_WRITE_HE);
		cअगरs_dbg(VFS, "Send error in write = %d\n", rc);
	पूर्ण अन्यथा अणु
		*nbytes = le32_to_cpu(rsp->DataLength);
		trace_smb3_ग_लिखो_करोne(xid, req->PersistentFileId,
				     io_parms->tcon->tid,
				     io_parms->tcon->ses->Suid,
				     io_parms->offset, *nbytes);
	पूर्ण

	cअगरs_small_buf_release(req);
	मुक्त_rsp_buf(resp_buftype, rsp);
	वापस rc;
पूर्ण

पूर्णांक posix_info_sid_size(स्थिर व्योम *beg, स्थिर व्योम *end)
अणु
	माप_प्रकार subauth;
	पूर्णांक total;

	अगर (beg + 1 > end)
		वापस -1;

	subauth = *(u8 *)(beg+1);
	अगर (subauth < 1 || subauth > 15)
		वापस -1;

	total = 1 + 1 + 6 + 4*subauth;
	अगर (beg + total > end)
		वापस -1;

	वापस total;
पूर्ण

पूर्णांक posix_info_parse(स्थिर व्योम *beg, स्थिर व्योम *end,
		     काष्ठा smb2_posix_info_parsed *out)

अणु
	पूर्णांक total_len = 0;
	पूर्णांक sid_len;
	पूर्णांक name_len;
	स्थिर व्योम *owner_sid;
	स्थिर व्योम *group_sid;
	स्थिर व्योम *name;

	/* अगर no end bound given, assume payload to be correct */
	अगर (!end) अणु
		स्थिर काष्ठा smb2_posix_info *p = beg;

		end = beg + le32_to_cpu(p->NextEntryOffset);
		/* last element will have a 0 offset, pick a sensible bound */
		अगर (end == beg)
			end += 0xFFFF;
	पूर्ण

	/* check base buf */
	अगर (beg + माप(काष्ठा smb2_posix_info) > end)
		वापस -1;
	total_len = माप(काष्ठा smb2_posix_info);

	/* check owner sid */
	owner_sid = beg + total_len;
	sid_len = posix_info_sid_size(owner_sid, end);
	अगर (sid_len < 0)
		वापस -1;
	total_len += sid_len;

	/* check group sid */
	group_sid = beg + total_len;
	sid_len = posix_info_sid_size(group_sid, end);
	अगर (sid_len < 0)
		वापस -1;
	total_len += sid_len;

	/* check name len */
	अगर (beg + total_len + 4 > end)
		वापस -1;
	name_len = le32_to_cpu(*(__le32 *)(beg + total_len));
	अगर (name_len < 1 || name_len > 0xFFFF)
		वापस -1;
	total_len += 4;

	/* check name */
	name = beg + total_len;
	अगर (name + name_len > end)
		वापस -1;
	total_len += name_len;

	अगर (out) अणु
		out->base = beg;
		out->size = total_len;
		out->name_len = name_len;
		out->name = name;
		स_नकल(&out->owner, owner_sid,
		       posix_info_sid_size(owner_sid, end));
		स_नकल(&out->group, group_sid,
		       posix_info_sid_size(group_sid, end));
	पूर्ण
	वापस total_len;
पूर्ण

अटल पूर्णांक posix_info_extra_size(स्थिर व्योम *beg, स्थिर व्योम *end)
अणु
	पूर्णांक len = posix_info_parse(beg, end, शून्य);

	अगर (len < 0)
		वापस -1;
	वापस len - माप(काष्ठा smb2_posix_info);
पूर्ण

अटल अचिन्हित पूर्णांक
num_entries(पूर्णांक infotype, अक्षर *bufstart, अक्षर *end_of_buf, अक्षर **lastentry,
	    माप_प्रकार size)
अणु
	पूर्णांक len;
	अचिन्हित पूर्णांक entrycount = 0;
	अचिन्हित पूर्णांक next_offset = 0;
	अक्षर *entryptr;
	खाता_सूचीECTORY_INFO *dir_info;

	अगर (bufstart == शून्य)
		वापस 0;

	entryptr = bufstart;

	जबतक (1) अणु
		अगर (entryptr + next_offset < entryptr ||
		    entryptr + next_offset > end_of_buf ||
		    entryptr + next_offset + size > end_of_buf) अणु
			cअगरs_dbg(VFS, "malformed search entry would overflow\n");
			अवरोध;
		पूर्ण

		entryptr = entryptr + next_offset;
		dir_info = (खाता_सूचीECTORY_INFO *)entryptr;

		अगर (infotype == SMB_FIND_खाता_POSIX_INFO)
			len = posix_info_extra_size(entryptr, end_of_buf);
		अन्यथा
			len = le32_to_cpu(dir_info->FileNameLength);

		अगर (len < 0 ||
		    entryptr + len < entryptr ||
		    entryptr + len > end_of_buf ||
		    entryptr + len + size > end_of_buf) अणु
			cअगरs_dbg(VFS, "directory entry name would overflow frame end of buf %p\n",
				 end_of_buf);
			अवरोध;
		पूर्ण

		*lastentry = entryptr;
		entrycount++;

		next_offset = le32_to_cpu(dir_info->NextEntryOffset);
		अगर (!next_offset)
			अवरोध;
	पूर्ण

	वापस entrycount;
पूर्ण

/*
 * Readdir/FindFirst
 */
पूर्णांक SMB2_query_directory_init(स्थिर अचिन्हित पूर्णांक xid,
			      काष्ठा cअगरs_tcon *tcon,
			      काष्ठा TCP_Server_Info *server,
			      काष्ठा smb_rqst *rqst,
			      u64 persistent_fid, u64 अस्थिर_fid,
			      पूर्णांक index, पूर्णांक info_level)
अणु
	काष्ठा smb2_query_directory_req *req;
	अचिन्हित अक्षर *bufptr;
	__le16 asteriks = cpu_to_le16('*');
	अचिन्हित पूर्णांक output_size = CIFSMaxBufSize -
		MAX_SMB2_CREATE_RESPONSE_SIZE -
		MAX_SMB2_CLOSE_RESPONSE_SIZE;
	अचिन्हित पूर्णांक total_len;
	काष्ठा kvec *iov = rqst->rq_iov;
	पूर्णांक len, rc;

	rc = smb2_plain_req_init(SMB2_QUERY_सूचीECTORY, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	चयन (info_level) अणु
	हाल SMB_FIND_खाता_सूचीECTORY_INFO:
		req->FileInक्रमmationClass = खाता_सूचीECTORY_INFORMATION;
		अवरोध;
	हाल SMB_FIND_खाता_ID_FULL_सूची_INFO:
		req->FileInक्रमmationClass = खाताID_FULL_सूचीECTORY_INFORMATION;
		अवरोध;
	हाल SMB_FIND_खाता_POSIX_INFO:
		req->FileInक्रमmationClass = SMB_FIND_खाता_POSIX_INFO;
		अवरोध;
	शेष:
		cअगरs_tcon_dbg(VFS, "info level %u isn't supported\n",
			info_level);
		वापस -EINVAL;
	पूर्ण

	req->FileIndex = cpu_to_le32(index);
	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = अस्थिर_fid;

	len = 0x2;
	bufptr = req->Buffer;
	स_नकल(bufptr, &asteriks, len);

	req->FileNameOffset =
		cpu_to_le16(माप(काष्ठा smb2_query_directory_req) - 1);
	req->FileNameLength = cpu_to_le16(len);
	/*
	 * BB could be 30 bytes or so दीर्घer अगर we used SMB2 specअगरic
	 * buffer lengths, but this is safe and बंद enough.
	 */
	output_size = min_t(अचिन्हित पूर्णांक, output_size, server->maxBuf);
	output_size = min_t(अचिन्हित पूर्णांक, output_size, 2 << 15);
	req->OutputBufferLength = cpu_to_le32(output_size);

	iov[0].iov_base = (अक्षर *)req;
	/* 1 क्रम Buffer */
	iov[0].iov_len = total_len - 1;

	iov[1].iov_base = (अक्षर *)(req->Buffer);
	iov[1].iov_len = len;

	trace_smb3_query_dir_enter(xid, persistent_fid, tcon->tid,
			tcon->ses->Suid, index, output_size);

	वापस 0;
पूर्ण

व्योम SMB2_query_directory_मुक्त(काष्ठा smb_rqst *rqst)
अणु
	अगर (rqst && rqst->rq_iov) अणु
		cअगरs_small_buf_release(rqst->rq_iov[0].iov_base); /* request */
	पूर्ण
पूर्ण

पूर्णांक
smb2_parse_query_directory(काष्ठा cअगरs_tcon *tcon,
			   काष्ठा kvec *rsp_iov,
			   पूर्णांक resp_buftype,
			   काष्ठा cअगरs_search_info *srch_inf)
अणु
	काष्ठा smb2_query_directory_rsp *rsp;
	माप_प्रकार info_buf_size;
	अक्षर *end_of_smb;
	पूर्णांक rc;

	rsp = (काष्ठा smb2_query_directory_rsp *)rsp_iov->iov_base;

	चयन (srch_inf->info_level) अणु
	हाल SMB_FIND_खाता_सूचीECTORY_INFO:
		info_buf_size = माप(खाता_सूचीECTORY_INFO) - 1;
		अवरोध;
	हाल SMB_FIND_खाता_ID_FULL_सूची_INFO:
		info_buf_size = माप(SEARCH_ID_FULL_सूची_INFO) - 1;
		अवरोध;
	हाल SMB_FIND_खाता_POSIX_INFO:
		/* note that posix payload are variable size */
		info_buf_size = माप(काष्ठा smb2_posix_info);
		अवरोध;
	शेष:
		cअगरs_tcon_dbg(VFS, "info level %u isn't supported\n",
			 srch_inf->info_level);
		वापस -EINVAL;
	पूर्ण

	rc = smb2_validate_iov(le16_to_cpu(rsp->OutputBufferOffset),
			       le32_to_cpu(rsp->OutputBufferLength), rsp_iov,
			       info_buf_size);
	अगर (rc) अणु
		cअगरs_tcon_dbg(VFS, "bad info payload");
		वापस rc;
	पूर्ण

	srch_inf->unicode = true;

	अगर (srch_inf->ntwrk_buf_start) अणु
		अगर (srch_inf->smallBuf)
			cअगरs_small_buf_release(srch_inf->ntwrk_buf_start);
		अन्यथा
			cअगरs_buf_release(srch_inf->ntwrk_buf_start);
	पूर्ण
	srch_inf->ntwrk_buf_start = (अक्षर *)rsp;
	srch_inf->srch_entries_start = srch_inf->last_entry =
		(अक्षर *)rsp + le16_to_cpu(rsp->OutputBufferOffset);
	end_of_smb = rsp_iov->iov_len + (अक्षर *)rsp;

	srch_inf->entries_in_buffer = num_entries(
		srch_inf->info_level,
		srch_inf->srch_entries_start,
		end_of_smb,
		&srch_inf->last_entry,
		info_buf_size);

	srch_inf->index_of_last_entry += srch_inf->entries_in_buffer;
	cअगरs_dbg(FYI, "num entries %d last_index %lld srch start %p srch end %p\n",
		 srch_inf->entries_in_buffer, srch_inf->index_of_last_entry,
		 srch_inf->srch_entries_start, srch_inf->last_entry);
	अगर (resp_buftype == CIFS_LARGE_BUFFER)
		srch_inf->smallBuf = false;
	अन्यथा अगर (resp_buftype == CIFS_SMALL_BUFFER)
		srch_inf->smallBuf = true;
	अन्यथा
		cअगरs_tcon_dbg(VFS, "Invalid search buffer type\n");

	वापस 0;
पूर्ण

पूर्णांक
SMB2_query_directory(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     u64 persistent_fid, u64 अस्थिर_fid, पूर्णांक index,
		     काष्ठा cअगरs_search_info *srch_inf)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा kvec iov[SMB2_QUERY_सूचीECTORY_IOV_SIZE];
	काष्ठा smb2_query_directory_rsp *rsp = शून्य;
	पूर्णांक resp_buftype = CIFS_NO_BUFFER;
	काष्ठा kvec rsp_iov;
	पूर्णांक rc = 0;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	पूर्णांक flags = 0;

	अगर (!ses || !(ses->server))
		वापस -EIO;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	स_रखो(&iov, 0, माप(iov));
	rqst.rq_iov = iov;
	rqst.rq_nvec = SMB2_QUERY_सूचीECTORY_IOV_SIZE;

	rc = SMB2_query_directory_init(xid, tcon, server,
				       &rqst, persistent_fid,
				       अस्थिर_fid, index,
				       srch_inf->info_level);
	अगर (rc)
		जाओ qdir_निकास;

	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags, &rsp_iov);
	rsp = (काष्ठा smb2_query_directory_rsp *)rsp_iov.iov_base;

	अगर (rc) अणु
		अगर (rc == -ENODATA &&
		    rsp->sync_hdr.Status == STATUS_NO_MORE_खाताS) अणु
			trace_smb3_query_dir_करोne(xid, persistent_fid,
				tcon->tid, tcon->ses->Suid, index, 0);
			srch_inf->endOfSearch = true;
			rc = 0;
		पूर्ण अन्यथा अणु
			trace_smb3_query_dir_err(xid, persistent_fid, tcon->tid,
				tcon->ses->Suid, index, 0, rc);
			cअगरs_stats_fail_inc(tcon, SMB2_QUERY_सूचीECTORY_HE);
		पूर्ण
		जाओ qdir_निकास;
	पूर्ण

	rc = smb2_parse_query_directory(tcon, &rsp_iov,	resp_buftype,
					srch_inf);
	अगर (rc) अणु
		trace_smb3_query_dir_err(xid, persistent_fid, tcon->tid,
			tcon->ses->Suid, index, 0, rc);
		जाओ qdir_निकास;
	पूर्ण
	resp_buftype = CIFS_NO_BUFFER;

	trace_smb3_query_dir_करोne(xid, persistent_fid, tcon->tid,
			tcon->ses->Suid, index, srch_inf->entries_in_buffer);

qdir_निकास:
	SMB2_query_directory_मुक्त(&rqst);
	मुक्त_rsp_buf(resp_buftype, rsp);
	वापस rc;
पूर्ण

पूर्णांक
SMB2_set_info_init(काष्ठा cअगरs_tcon *tcon, काष्ठा TCP_Server_Info *server,
		   काष्ठा smb_rqst *rqst,
		   u64 persistent_fid, u64 अस्थिर_fid, u32 pid,
		   u8 info_class, u8 info_type, u32 additional_info,
		   व्योम **data, अचिन्हित पूर्णांक *size)
अणु
	काष्ठा smb2_set_info_req *req;
	काष्ठा kvec *iov = rqst->rq_iov;
	अचिन्हित पूर्णांक i, total_len;
	पूर्णांक rc;

	rc = smb2_plain_req_init(SMB2_SET_INFO, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	req->sync_hdr.ProcessId = cpu_to_le32(pid);
	req->InfoType = info_type;
	req->FileInfoClass = info_class;
	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = अस्थिर_fid;
	req->AdditionalInक्रमmation = cpu_to_le32(additional_info);

	req->BufferOffset =
			cpu_to_le16(माप(काष्ठा smb2_set_info_req) - 1);
	req->BufferLength = cpu_to_le32(*size);

	स_नकल(req->Buffer, *data, *size);
	total_len += *size;

	iov[0].iov_base = (अक्षर *)req;
	/* 1 क्रम Buffer */
	iov[0].iov_len = total_len - 1;

	क्रम (i = 1; i < rqst->rq_nvec; i++) अणु
		le32_add_cpu(&req->BufferLength, size[i]);
		iov[i].iov_base = (अक्षर *)data[i];
		iov[i].iov_len = size[i];
	पूर्ण

	वापस 0;
पूर्ण

व्योम
SMB2_set_info_मुक्त(काष्ठा smb_rqst *rqst)
अणु
	अगर (rqst && rqst->rq_iov)
		cअगरs_buf_release(rqst->rq_iov[0].iov_base); /* request */
पूर्ण

अटल पूर्णांक
send_set_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	       u64 persistent_fid, u64 अस्थिर_fid, u32 pid, u8 info_class,
	       u8 info_type, u32 additional_info, अचिन्हित पूर्णांक num,
		व्योम **data, अचिन्हित पूर्णांक *size)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_set_info_rsp *rsp = शून्य;
	काष्ठा kvec *iov;
	काष्ठा kvec rsp_iov;
	पूर्णांक rc = 0;
	पूर्णांक resp_buftype;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	पूर्णांक flags = 0;

	अगर (!ses || !server)
		वापस -EIO;

	अगर (!num)
		वापस -EINVAL;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	iov = kदो_स्मृति_array(num, माप(काष्ठा kvec), GFP_KERNEL);
	अगर (!iov)
		वापस -ENOMEM;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = num;

	rc = SMB2_set_info_init(tcon, server,
				&rqst, persistent_fid, अस्थिर_fid, pid,
				info_class, info_type, additional_info,
				data, size);
	अगर (rc) अणु
		kमुक्त(iov);
		वापस rc;
	पूर्ण


	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags,
			    &rsp_iov);
	SMB2_set_info_मुक्त(&rqst);
	rsp = (काष्ठा smb2_set_info_rsp *)rsp_iov.iov_base;

	अगर (rc != 0) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_SET_INFO_HE);
		trace_smb3_set_info_err(xid, persistent_fid, tcon->tid,
				ses->Suid, info_class, (__u32)info_type, rc);
	पूर्ण

	मुक्त_rsp_buf(resp_buftype, rsp);
	kमुक्त(iov);
	वापस rc;
पूर्ण

पूर्णांक
SMB2_set_eof(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, u64 persistent_fid,
	     u64 अस्थिर_fid, u32 pid, __le64 *eof)
अणु
	काष्ठा smb2_file_eof_info info;
	व्योम *data;
	अचिन्हित पूर्णांक size;

	info.EndOfFile = *eof;

	data = &info;
	size = माप(काष्ठा smb2_file_eof_info);

	वापस send_set_info(xid, tcon, persistent_fid, अस्थिर_fid,
			pid, खाता_END_OF_खाता_INFORMATION, SMB2_O_INFO_खाता,
			0, 1, &data, &size);
पूर्ण

पूर्णांक
SMB2_set_acl(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		u64 persistent_fid, u64 अस्थिर_fid,
		काष्ठा cअगरs_ntsd *pnntsd, पूर्णांक pacllen, पूर्णांक aclflag)
अणु
	वापस send_set_info(xid, tcon, persistent_fid, अस्थिर_fid,
			current->tgid, 0, SMB2_O_INFO_SECURITY, aclflag,
			1, (व्योम **)&pnntsd, &pacllen);
पूर्ण

पूर्णांक
SMB2_set_ea(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	    u64 persistent_fid, u64 अस्थिर_fid,
	    काष्ठा smb2_file_full_ea_info *buf, पूर्णांक len)
अणु
	वापस send_set_info(xid, tcon, persistent_fid, अस्थिर_fid,
		current->tgid, खाता_FULL_EA_INFORMATION, SMB2_O_INFO_खाता,
		0, 1, (व्योम **)&buf, &len);
पूर्ण

पूर्णांक
SMB2_oplock_अवरोध(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		  स्थिर u64 persistent_fid, स्थिर u64 अस्थिर_fid,
		  __u8 oplock_level)
अणु
	काष्ठा smb_rqst rqst;
	पूर्णांक rc;
	काष्ठा smb2_oplock_अवरोध *req = शून्य;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	पूर्णांक flags = CIFS_OBREAK_OP;
	अचिन्हित पूर्णांक total_len;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov;
	पूर्णांक resp_buf_type;

	cअगरs_dbg(FYI, "SMB2_oplock_break\n");
	rc = smb2_plain_req_init(SMB2_OPLOCK_BREAK, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	req->VolatileFid = अस्थिर_fid;
	req->PersistentFid = persistent_fid;
	req->OplockLevel = oplock_level;
	req->sync_hdr.CreditRequest = cpu_to_le16(1);

	flags |= CIFS_NO_RSP_BUF;

	iov[0].iov_base = (अक्षर *)req;
	iov[0].iov_len = total_len;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buf_type, flags, &rsp_iov);
	cअगरs_small_buf_release(req);

	अगर (rc) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_OPLOCK_BREAK_HE);
		cअगरs_dbg(FYI, "Send error in Oplock Break = %d\n", rc);
	पूर्ण

	वापस rc;
पूर्ण

व्योम
smb2_copy_fs_info_to_kstatfs(काष्ठा smb2_fs_full_size_info *pfs_inf,
			     काष्ठा kstatfs *kst)
अणु
	kst->f_bsize = le32_to_cpu(pfs_inf->BytesPerSector) *
			  le32_to_cpu(pfs_inf->SectorsPerAllocationUnit);
	kst->f_blocks = le64_to_cpu(pfs_inf->TotalAllocationUnits);
	kst->f_bमुक्त  = kst->f_bavail =
			le64_to_cpu(pfs_inf->CallerAvailableAllocationUnits);
	वापस;
पूर्ण

अटल व्योम
copy_posix_fs_info_to_kstatfs(खाता_SYSTEM_POSIX_INFO *response_data,
			काष्ठा kstatfs *kst)
अणु
	kst->f_bsize = le32_to_cpu(response_data->BlockSize);
	kst->f_blocks = le64_to_cpu(response_data->TotalBlocks);
	kst->f_bमुक्त =  le64_to_cpu(response_data->BlocksAvail);
	अगर (response_data->UserBlocksAvail == cpu_to_le64(-1))
		kst->f_bavail = kst->f_bमुक्त;
	अन्यथा
		kst->f_bavail = le64_to_cpu(response_data->UserBlocksAvail);
	अगर (response_data->TotalFileNodes != cpu_to_le64(-1))
		kst->f_files = le64_to_cpu(response_data->TotalFileNodes);
	अगर (response_data->FreeFileNodes != cpu_to_le64(-1))
		kst->f_fमुक्त = le64_to_cpu(response_data->FreeFileNodes);

	वापस;
पूर्ण

अटल पूर्णांक
build_qfs_info_req(काष्ठा kvec *iov, काष्ठा cअगरs_tcon *tcon,
		   काष्ठा TCP_Server_Info *server,
		   पूर्णांक level, पूर्णांक outbuf_len, u64 persistent_fid,
		   u64 अस्थिर_fid)
अणु
	पूर्णांक rc;
	काष्ठा smb2_query_info_req *req;
	अचिन्हित पूर्णांक total_len;

	cअगरs_dbg(FYI, "Query FSInfo level %d\n", level);

	अगर ((tcon->ses == शून्य) || server == शून्य)
		वापस -EIO;

	rc = smb2_plain_req_init(SMB2_QUERY_INFO, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	req->InfoType = SMB2_O_INFO_खाताSYSTEM;
	req->FileInfoClass = level;
	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = अस्थिर_fid;
	/* 1 क्रम pad */
	req->InputBufferOffset =
			cpu_to_le16(माप(काष्ठा smb2_query_info_req) - 1);
	req->OutputBufferLength = cpu_to_le32(
		outbuf_len + माप(काष्ठा smb2_query_info_rsp) - 1);

	iov->iov_base = (अक्षर *)req;
	iov->iov_len = total_len;
	वापस 0;
पूर्ण

पूर्णांक
SMB311_posix_qfs_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	      u64 persistent_fid, u64 अस्थिर_fid, काष्ठा kstatfs *fsdata)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_query_info_rsp *rsp = शून्य;
	काष्ठा kvec iov;
	काष्ठा kvec rsp_iov;
	पूर्णांक rc = 0;
	पूर्णांक resp_buftype;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	खाता_SYSTEM_POSIX_INFO *info = शून्य;
	पूर्णांक flags = 0;

	rc = build_qfs_info_req(&iov, tcon, server,
				FS_POSIX_INFORMATION,
				माप(खाता_SYSTEM_POSIX_INFO),
				persistent_fid, अस्थिर_fid);
	अगर (rc)
		वापस rc;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = &iov;
	rqst.rq_nvec = 1;

	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags, &rsp_iov);
	cअगरs_small_buf_release(iov.iov_base);
	अगर (rc) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_QUERY_INFO_HE);
		जाओ posix_qfsinf_निकास;
	पूर्ण
	rsp = (काष्ठा smb2_query_info_rsp *)rsp_iov.iov_base;

	info = (खाता_SYSTEM_POSIX_INFO *)(
		le16_to_cpu(rsp->OutputBufferOffset) + (अक्षर *)rsp);
	rc = smb2_validate_iov(le16_to_cpu(rsp->OutputBufferOffset),
			       le32_to_cpu(rsp->OutputBufferLength), &rsp_iov,
			       माप(खाता_SYSTEM_POSIX_INFO));
	अगर (!rc)
		copy_posix_fs_info_to_kstatfs(info, fsdata);

posix_qfsinf_निकास:
	मुक्त_rsp_buf(resp_buftype, rsp_iov.iov_base);
	वापस rc;
पूर्ण

पूर्णांक
SMB2_QFS_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	      u64 persistent_fid, u64 अस्थिर_fid, काष्ठा kstatfs *fsdata)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_query_info_rsp *rsp = शून्य;
	काष्ठा kvec iov;
	काष्ठा kvec rsp_iov;
	पूर्णांक rc = 0;
	पूर्णांक resp_buftype;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	काष्ठा smb2_fs_full_size_info *info = शून्य;
	पूर्णांक flags = 0;

	rc = build_qfs_info_req(&iov, tcon, server,
				FS_FULL_SIZE_INFORMATION,
				माप(काष्ठा smb2_fs_full_size_info),
				persistent_fid, अस्थिर_fid);
	अगर (rc)
		वापस rc;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = &iov;
	rqst.rq_nvec = 1;

	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags, &rsp_iov);
	cअगरs_small_buf_release(iov.iov_base);
	अगर (rc) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_QUERY_INFO_HE);
		जाओ qfsinf_निकास;
	पूर्ण
	rsp = (काष्ठा smb2_query_info_rsp *)rsp_iov.iov_base;

	info = (काष्ठा smb2_fs_full_size_info *)(
		le16_to_cpu(rsp->OutputBufferOffset) + (अक्षर *)rsp);
	rc = smb2_validate_iov(le16_to_cpu(rsp->OutputBufferOffset),
			       le32_to_cpu(rsp->OutputBufferLength), &rsp_iov,
			       माप(काष्ठा smb2_fs_full_size_info));
	अगर (!rc)
		smb2_copy_fs_info_to_kstatfs(info, fsdata);

qfsinf_निकास:
	मुक्त_rsp_buf(resp_buftype, rsp_iov.iov_base);
	वापस rc;
पूर्ण

पूर्णांक
SMB2_QFS_attr(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	      u64 persistent_fid, u64 अस्थिर_fid, पूर्णांक level)
अणु
	काष्ठा smb_rqst rqst;
	काष्ठा smb2_query_info_rsp *rsp = शून्य;
	काष्ठा kvec iov;
	काष्ठा kvec rsp_iov;
	पूर्णांक rc = 0;
	पूर्णांक resp_buftype, max_len, min_len;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(ses);
	अचिन्हित पूर्णांक rsp_len, offset;
	पूर्णांक flags = 0;

	अगर (level == FS_DEVICE_INFORMATION) अणु
		max_len = माप(खाता_SYSTEM_DEVICE_INFO);
		min_len = माप(खाता_SYSTEM_DEVICE_INFO);
	पूर्ण अन्यथा अगर (level == FS_ATTRIBUTE_INFORMATION) अणु
		max_len = माप(खाता_SYSTEM_ATTRIBUTE_INFO);
		min_len = MIN_FS_ATTR_INFO_SIZE;
	पूर्ण अन्यथा अगर (level == FS_SECTOR_SIZE_INFORMATION) अणु
		max_len = माप(काष्ठा smb3_fs_ss_info);
		min_len = माप(काष्ठा smb3_fs_ss_info);
	पूर्ण अन्यथा अगर (level == FS_VOLUME_INFORMATION) अणु
		max_len = माप(काष्ठा smb3_fs_vol_info) + MAX_VOL_LABEL_LEN;
		min_len = माप(काष्ठा smb3_fs_vol_info);
	पूर्ण अन्यथा अणु
		cअगरs_dbg(FYI, "Invalid qfsinfo level %d\n", level);
		वापस -EINVAL;
	पूर्ण

	rc = build_qfs_info_req(&iov, tcon, server,
				level, max_len,
				persistent_fid, अस्थिर_fid);
	अगर (rc)
		वापस rc;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = &iov;
	rqst.rq_nvec = 1;

	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buftype, flags, &rsp_iov);
	cअगरs_small_buf_release(iov.iov_base);
	अगर (rc) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_QUERY_INFO_HE);
		जाओ qfsattr_निकास;
	पूर्ण
	rsp = (काष्ठा smb2_query_info_rsp *)rsp_iov.iov_base;

	rsp_len = le32_to_cpu(rsp->OutputBufferLength);
	offset = le16_to_cpu(rsp->OutputBufferOffset);
	rc = smb2_validate_iov(offset, rsp_len, &rsp_iov, min_len);
	अगर (rc)
		जाओ qfsattr_निकास;

	अगर (level == FS_ATTRIBUTE_INFORMATION)
		स_नकल(&tcon->fsAttrInfo, offset
			+ (अक्षर *)rsp, min_t(अचिन्हित पूर्णांक,
			rsp_len, max_len));
	अन्यथा अगर (level == FS_DEVICE_INFORMATION)
		स_नकल(&tcon->fsDevInfo, offset
			+ (अक्षर *)rsp, माप(खाता_SYSTEM_DEVICE_INFO));
	अन्यथा अगर (level == FS_SECTOR_SIZE_INFORMATION) अणु
		काष्ठा smb3_fs_ss_info *ss_info = (काष्ठा smb3_fs_ss_info *)
			(offset + (अक्षर *)rsp);
		tcon->ss_flags = le32_to_cpu(ss_info->Flags);
		tcon->perf_sector_size =
			le32_to_cpu(ss_info->PhysicalBytesPerSectorForPerf);
	पूर्ण अन्यथा अगर (level == FS_VOLUME_INFORMATION) अणु
		काष्ठा smb3_fs_vol_info *vol_info = (काष्ठा smb3_fs_vol_info *)
			(offset + (अक्षर *)rsp);
		tcon->vol_serial_number = vol_info->VolumeSerialNumber;
		tcon->vol_create_समय = vol_info->VolumeCreationTime;
	पूर्ण

qfsattr_निकास:
	मुक्त_rsp_buf(resp_buftype, rsp_iov.iov_base);
	वापस rc;
पूर्ण

पूर्णांक
smb2_lockv(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	   स्थिर __u64 persist_fid, स्थिर __u64 अस्थिर_fid, स्थिर __u32 pid,
	   स्थिर __u32 num_lock, काष्ठा smb2_lock_element *buf)
अणु
	काष्ठा smb_rqst rqst;
	पूर्णांक rc = 0;
	काष्ठा smb2_lock_req *req = शून्य;
	काष्ठा kvec iov[2];
	काष्ठा kvec rsp_iov;
	पूर्णांक resp_buf_type;
	अचिन्हित पूर्णांक count;
	पूर्णांक flags = CIFS_NO_RSP_BUF;
	अचिन्हित पूर्णांक total_len;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(tcon->ses);

	cअगरs_dbg(FYI, "smb2_lockv num lock %d\n", num_lock);

	rc = smb2_plain_req_init(SMB2_LOCK, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	req->sync_hdr.ProcessId = cpu_to_le32(pid);
	req->LockCount = cpu_to_le16(num_lock);

	req->PersistentFileId = persist_fid;
	req->VolatileFileId = अस्थिर_fid;

	count = num_lock * माप(काष्ठा smb2_lock_element);

	iov[0].iov_base = (अक्षर *)req;
	iov[0].iov_len = total_len - माप(काष्ठा smb2_lock_element);
	iov[1].iov_base = (अक्षर *)buf;
	iov[1].iov_len = count;

	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_locks);

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 2;

	rc = cअगरs_send_recv(xid, tcon->ses, server,
			    &rqst, &resp_buf_type, flags,
			    &rsp_iov);
	cअगरs_small_buf_release(req);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in smb2_lockv = %d\n", rc);
		cअगरs_stats_fail_inc(tcon, SMB2_LOCK_HE);
		trace_smb3_lock_err(xid, persist_fid, tcon->tid,
				    tcon->ses->Suid, rc);
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक
SMB2_lock(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	  स्थिर __u64 persist_fid, स्थिर __u64 अस्थिर_fid, स्थिर __u32 pid,
	  स्थिर __u64 length, स्थिर __u64 offset, स्थिर __u32 lock_flags,
	  स्थिर bool रुको)
अणु
	काष्ठा smb2_lock_element lock;

	lock.Offset = cpu_to_le64(offset);
	lock.Length = cpu_to_le64(length);
	lock.Flags = cpu_to_le32(lock_flags);
	अगर (!रुको && lock_flags != SMB2_LOCKFLAG_UNLOCK)
		lock.Flags |= cpu_to_le32(SMB2_LOCKFLAG_FAIL_IMMEDIATELY);

	वापस smb2_lockv(xid, tcon, persist_fid, अस्थिर_fid, pid, 1, &lock);
पूर्ण

पूर्णांक
SMB2_lease_अवरोध(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		 __u8 *lease_key, स्थिर __le32 lease_state)
अणु
	काष्ठा smb_rqst rqst;
	पूर्णांक rc;
	काष्ठा smb2_lease_ack *req = शून्य;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	पूर्णांक flags = CIFS_OBREAK_OP;
	अचिन्हित पूर्णांक total_len;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov;
	पूर्णांक resp_buf_type;
	__u64 *please_key_high;
	__u64 *please_key_low;
	काष्ठा TCP_Server_Info *server = cअगरs_pick_channel(tcon->ses);

	cअगरs_dbg(FYI, "SMB2_lease_break\n");
	rc = smb2_plain_req_init(SMB2_OPLOCK_BREAK, tcon, server,
				 (व्योम **) &req, &total_len);
	अगर (rc)
		वापस rc;

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	req->sync_hdr.CreditRequest = cpu_to_le16(1);
	req->StructureSize = cpu_to_le16(36);
	total_len += 12;

	स_नकल(req->LeaseKey, lease_key, 16);
	req->LeaseState = lease_state;

	flags |= CIFS_NO_RSP_BUF;

	iov[0].iov_base = (अक्षर *)req;
	iov[0].iov_len = total_len;

	स_रखो(&rqst, 0, माप(काष्ठा smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	rc = cअगरs_send_recv(xid, ses, server,
			    &rqst, &resp_buf_type, flags, &rsp_iov);
	cअगरs_small_buf_release(req);

	please_key_low = (__u64 *)lease_key;
	please_key_high = (__u64 *)(lease_key+8);
	अगर (rc) अणु
		cअगरs_stats_fail_inc(tcon, SMB2_OPLOCK_BREAK_HE);
		trace_smb3_lease_err(le32_to_cpu(lease_state), tcon->tid,
			ses->Suid, *please_key_low, *please_key_high, rc);
		cअगरs_dbg(FYI, "Send error in Lease Break = %d\n", rc);
	पूर्ण अन्यथा
		trace_smb3_lease_करोne(le32_to_cpu(lease_state), tcon->tid,
			ses->Suid, *please_key_low, *please_key_high);

	वापस rc;
पूर्ण
