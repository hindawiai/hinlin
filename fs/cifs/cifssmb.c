<शैली गुरु>
/*
 *   fs/cअगरs/cअगरssmb.c
 *
 *   Copyright (C) International Business Machines  Corp., 2002,2010
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 *   Contains the routines क्रम स्थिरructing the SMB PDUs themselves
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

 /* SMB/CIFS PDU handling routines here - except क्रम leftovers in connect.c   */
 /* These are mostly routines that operate on a pathname, or on a tree id     */
 /* (mounted volume), but there are eight handle based routines which must be */
 /* treated slightly dअगरferently क्रम reconnection purposes since we never     */
 /* want to reuse a stale file handle and only the caller knows the file info */

#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/vfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/uaccess.h>
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsacl.h"
#समावेश "cifsproto.h"
#समावेश "cifs_unicode.h"
#समावेश "cifs_debug.h"
#समावेश "smb2proto.h"
#समावेश "fscache.h"
#समावेश "smbdirect.h"
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
#समावेश "dfs_cache.h"
#पूर्ण_अगर

#अगर_घोषित CONFIG_CIFS_POSIX
अटल काष्ठा अणु
	पूर्णांक index;
	अक्षर *name;
पूर्ण protocols[] = अणु
#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
	अणुLANMAN_PROT, "\2LM1.2X002"पूर्ण,
	अणुLANMAN2_PROT, "\2LANMAN2.1"पूर्ण,
#पूर्ण_अगर /* weak password hashing क्रम legacy clients */
	अणुCIFS_PROT, "\2NT LM 0.12"पूर्ण,
	अणुPOSIX_PROT, "\2POSIX 2"पूर्ण,
	अणुBAD_PROT, "\2"पूर्ण
पूर्ण;
#अन्यथा
अटल काष्ठा अणु
	पूर्णांक index;
	अक्षर *name;
पूर्ण protocols[] = अणु
#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
	अणुLANMAN_PROT, "\2LM1.2X002"पूर्ण,
	अणुLANMAN2_PROT, "\2LANMAN2.1"पूर्ण,
#पूर्ण_अगर /* weak password hashing क्रम legacy clients */
	अणुCIFS_PROT, "\2NT LM 0.12"पूर्ण,
	अणुBAD_PROT, "\2"पूर्ण
पूर्ण;
#पूर्ण_अगर

/* define the number of elements in the cअगरs dialect array */
#अगर_घोषित CONFIG_CIFS_POSIX
#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
#घोषणा CIFS_NUM_PROT 4
#अन्यथा
#घोषणा CIFS_NUM_PROT 2
#पूर्ण_अगर /* CIFS_WEAK_PW_HASH */
#अन्यथा /* not posix */
#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
#घोषणा CIFS_NUM_PROT 3
#अन्यथा
#घोषणा CIFS_NUM_PROT 1
#पूर्ण_अगर /* CONFIG_CIFS_WEAK_PW_HASH */
#पूर्ण_अगर /* CIFS_POSIX */

/*
 * Mark as invalid, all खोलो files on tree connections since they
 * were बंदd when session to server was lost.
 */
व्योम
cअगरs_mark_खोलो_files_invalid(काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा cअगरsFileInfo *खोलो_file = शून्य;
	काष्ठा list_head *पंचांगp;
	काष्ठा list_head *पंचांगp1;

	/* list all files खोलो on tree connection and mark them invalid */
	spin_lock(&tcon->खोलो_file_lock);
	list_क्रम_each_safe(पंचांगp, पंचांगp1, &tcon->खोलोFileList) अणु
		खोलो_file = list_entry(पंचांगp, काष्ठा cअगरsFileInfo, tlist);
		खोलो_file->invalidHandle = true;
		खोलो_file->oplock_अवरोध_cancelled = true;
	पूर्ण
	spin_unlock(&tcon->खोलो_file_lock);

	mutex_lock(&tcon->crfid.fid_mutex);
	tcon->crfid.is_valid = false;
	/* cached handle is not valid, so SMB2_CLOSE won't be sent below */
	बंद_cached_dir_lease_locked(&tcon->crfid);
	स_रखो(tcon->crfid.fid, 0, माप(काष्ठा cअगरs_fid));
	mutex_unlock(&tcon->crfid.fid_mutex);

	/*
	 * BB Add call to invalidate_inodes(sb) क्रम all superblocks mounted
	 * to this tcon.
	 */
पूर्ण

/* reconnect the socket, tcon, and smb session अगर needed */
अटल पूर्णांक
cअगरs_reconnect_tcon(काष्ठा cअगरs_tcon *tcon, पूर्णांक smb_command)
अणु
	पूर्णांक rc;
	काष्ठा cअगरs_ses *ses;
	काष्ठा TCP_Server_Info *server;
	काष्ठा nls_table *nls_codepage;
	पूर्णांक retries;

	/*
	 * SMBs NegProt, SessSetup, uLogoff करो not have tcon yet so check क्रम
	 * tcp and smb session status करोne dअगरferently क्रम those three - in the
	 * calling routine
	 */
	अगर (!tcon)
		वापस 0;

	ses = tcon->ses;
	server = ses->server;

	/*
	 * only tree disconnect, खोलो, and ग_लिखो, (and ulogoff which करोes not
	 * have tcon) are allowed as we start क्रमce umount
	 */
	अगर (tcon->tidStatus == CअगरsExiting) अणु
		अगर (smb_command != SMB_COM_WRITE_ANDX &&
		    smb_command != SMB_COM_OPEN_ANDX &&
		    smb_command != SMB_COM_TREE_DISCONNECT) अणु
			cअगरs_dbg(FYI, "can not send cmd %d while umounting\n",
				 smb_command);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	retries = server->nr_tarमाला_लो;

	/*
	 * Give demultiplex thपढ़ो up to 10 seconds to each target available क्रम
	 * reconnect -- should be greater than cअगरs socket समयout which is 7
	 * seconds.
	 */
	जबतक (server->tcpStatus == CअगरsNeedReconnect) अणु
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

	अगर (!ses->need_reconnect && !tcon->need_reconnect)
		वापस 0;

	nls_codepage = load_nls_शेष();

	/*
	 * need to prevent multiple thपढ़ोs trying to simultaneously
	 * reconnect the same SMB session
	 */
	mutex_lock(&ses->session_mutex);

	/*
	 * Recheck after acquire mutex. If another thपढ़ो is negotiating
	 * and the server never sends an answer the socket will be बंदd
	 * and tcpStatus set to reconnect.
	 */
	अगर (server->tcpStatus == CअगरsNeedReconnect) अणु
		rc = -EHOSTDOWN;
		mutex_unlock(&ses->session_mutex);
		जाओ out;
	पूर्ण

	rc = cअगरs_negotiate_protocol(0, ses);
	अगर (rc == 0 && ses->need_reconnect)
		rc = cअगरs_setup_session(0, ses, nls_codepage);

	/* करो we need to reconnect tcon? */
	अगर (rc || !tcon->need_reconnect) अणु
		mutex_unlock(&ses->session_mutex);
		जाओ out;
	पूर्ण

	cअगरs_mark_खोलो_files_invalid(tcon);
	rc = cअगरs_tree_connect(0, tcon, nls_codepage);
	mutex_unlock(&ses->session_mutex);
	cअगरs_dbg(FYI, "reconnect tcon rc = %d\n", rc);

	अगर (rc) अणु
		pr_warn_once("reconnect tcon failed rc = %d\n", rc);
		जाओ out;
	पूर्ण

	atomic_inc(&tconInfoReconnectCount);

	/* tell server Unix caps we support */
	अगर (cap_unix(ses))
		reset_cअगरs_unix_caps(0, tcon, शून्य, शून्य);

	/*
	 * Removed call to reखोलो खोलो files here. It is safer (and faster) to
	 * reखोलो files one at a समय as needed in पढ़ो and ग_लिखो.
	 *
	 * FIXME: what about file locks? करोn't we need to reclaim them ASAP?
	 */

out:
	/*
	 * Check अगर handle based operation so we know whether we can जारी
	 * or not without वापसing to caller to reset file handle
	 */
	चयन (smb_command) अणु
	हाल SMB_COM_READ_ANDX:
	हाल SMB_COM_WRITE_ANDX:
	हाल SMB_COM_CLOSE:
	हाल SMB_COM_FIND_CLOSE2:
	हाल SMB_COM_LOCKING_ANDX:
		rc = -EAGAIN;
	पूर्ण

	unload_nls(nls_codepage);
	वापस rc;
पूर्ण

/* Allocate and वापस poपूर्णांकer to an SMB request buffer, and set basic
   SMB inक्रमmation in the SMB header.  If the वापस code is zero, this
   function must have filled in request_buf poपूर्णांकer */
अटल पूर्णांक
small_smb_init(पूर्णांक smb_command, पूर्णांक wct, काष्ठा cअगरs_tcon *tcon,
		व्योम **request_buf)
अणु
	पूर्णांक rc;

	rc = cअगरs_reconnect_tcon(tcon, smb_command);
	अगर (rc)
		वापस rc;

	*request_buf = cअगरs_small_buf_get();
	अगर (*request_buf == शून्य) अणु
		/* BB should we add a retry in here अगर not a ग_लिखोpage? */
		वापस -ENOMEM;
	पूर्ण

	header_assemble((काष्ठा smb_hdr *) *request_buf, smb_command,
			tcon, wct);

	अगर (tcon != शून्य)
		cअगरs_stats_inc(&tcon->num_smbs_sent);

	वापस 0;
पूर्ण

पूर्णांक
small_smb_init_no_tc(स्थिर पूर्णांक smb_command, स्थिर पूर्णांक wct,
		     काष्ठा cअगरs_ses *ses, व्योम **request_buf)
अणु
	पूर्णांक rc;
	काष्ठा smb_hdr *buffer;

	rc = small_smb_init(smb_command, wct, शून्य, request_buf);
	अगर (rc)
		वापस rc;

	buffer = (काष्ठा smb_hdr *)*request_buf;
	buffer->Mid = get_next_mid(ses->server);
	अगर (ses->capabilities & CAP_UNICODE)
		buffer->Flags2 |= SMBFLG2_UNICODE;
	अगर (ses->capabilities & CAP_STATUS32)
		buffer->Flags2 |= SMBFLG2_ERR_STATUS;

	/* uid, tid can stay at zero as set in header assemble */

	/* BB add support क्रम turning on the signing when
	this function is used after 1st of session setup requests */

	वापस rc;
पूर्ण

/* If the वापस code is zero, this function must fill in request_buf poपूर्णांकer */
अटल पूर्णांक
__smb_init(पूर्णांक smb_command, पूर्णांक wct, काष्ठा cअगरs_tcon *tcon,
			व्योम **request_buf, व्योम **response_buf)
अणु
	*request_buf = cअगरs_buf_get();
	अगर (*request_buf == शून्य) अणु
		/* BB should we add a retry in here अगर not a ग_लिखोpage? */
		वापस -ENOMEM;
	पूर्ण
    /* Although the original thought was we needed the response buf क्रम  */
    /* potential retries of smb operations it turns out we can determine */
    /* from the mid flags when the request buffer can be resent without  */
    /* having to use a second distinct buffer क्रम the response */
	अगर (response_buf)
		*response_buf = *request_buf;

	header_assemble((काष्ठा smb_hdr *) *request_buf, smb_command, tcon,
			wct);

	अगर (tcon != शून्य)
		cअगरs_stats_inc(&tcon->num_smbs_sent);

	वापस 0;
पूर्ण

/* If the वापस code is zero, this function must fill in request_buf poपूर्णांकer */
अटल पूर्णांक
smb_init(पूर्णांक smb_command, पूर्णांक wct, काष्ठा cअगरs_tcon *tcon,
	 व्योम **request_buf, व्योम **response_buf)
अणु
	पूर्णांक rc;

	rc = cअगरs_reconnect_tcon(tcon, smb_command);
	अगर (rc)
		वापस rc;

	वापस __smb_init(smb_command, wct, tcon, request_buf, response_buf);
पूर्ण

अटल पूर्णांक
smb_init_no_reconnect(पूर्णांक smb_command, पूर्णांक wct, काष्ठा cअगरs_tcon *tcon,
			व्योम **request_buf, व्योम **response_buf)
अणु
	अगर (tcon->ses->need_reconnect || tcon->need_reconnect)
		वापस -EHOSTDOWN;

	वापस __smb_init(smb_command, wct, tcon, request_buf, response_buf);
पूर्ण

अटल पूर्णांक validate_t2(काष्ठा smb_t2_rsp *pSMB)
अणु
	अचिन्हित पूर्णांक total_size;

	/* check क्रम plausible wct */
	अगर (pSMB->hdr.WordCount < 10)
		जाओ vt2_err;

	/* check क्रम parm and data offset going beyond end of smb */
	अगर (get_unaligned_le16(&pSMB->t2_rsp.ParameterOffset) > 1024 ||
	    get_unaligned_le16(&pSMB->t2_rsp.DataOffset) > 1024)
		जाओ vt2_err;

	total_size = get_unaligned_le16(&pSMB->t2_rsp.ParameterCount);
	अगर (total_size >= 512)
		जाओ vt2_err;

	/* check that bcc is at least as big as parms + data, and that it is
	 * less than negotiated smb buffer
	 */
	total_size += get_unaligned_le16(&pSMB->t2_rsp.DataCount);
	अगर (total_size > get_bcc(&pSMB->hdr) ||
	    total_size >= CIFSMaxBufSize + MAX_CIFS_HDR_SIZE)
		जाओ vt2_err;

	वापस 0;
vt2_err:
	cअगरs_dump_mem("Invalid transact2 SMB: ", (अक्षर *)pSMB,
		माप(काष्ठा smb_t2_rsp) + 16);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
decode_ext_sec_blob(काष्ठा cअगरs_ses *ses, NEGOTIATE_RSP *pSMBr)
अणु
	पूर्णांक	rc = 0;
	u16	count;
	अक्षर	*guid = pSMBr->u.extended_response.GUID;
	काष्ठा TCP_Server_Info *server = ses->server;

	count = get_bcc(&pSMBr->hdr);
	अगर (count < SMB1_CLIENT_GUID_SIZE)
		वापस -EIO;

	spin_lock(&cअगरs_tcp_ses_lock);
	अगर (server->srv_count > 1) अणु
		spin_unlock(&cअगरs_tcp_ses_lock);
		अगर (स_भेद(server->server_GUID, guid, SMB1_CLIENT_GUID_SIZE) != 0) अणु
			cअगरs_dbg(FYI, "server UID changed\n");
			स_नकल(server->server_GUID, guid, SMB1_CLIENT_GUID_SIZE);
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock(&cअगरs_tcp_ses_lock);
		स_नकल(server->server_GUID, guid, SMB1_CLIENT_GUID_SIZE);
	पूर्ण

	अगर (count == SMB1_CLIENT_GUID_SIZE) अणु
		server->sec_ntlmssp = true;
	पूर्ण अन्यथा अणु
		count -= SMB1_CLIENT_GUID_SIZE;
		rc = decode_negTokenInit(
			pSMBr->u.extended_response.SecurityBlob, count, server);
		अगर (rc != 1)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
cअगरs_enable_signing(काष्ठा TCP_Server_Info *server, bool mnt_sign_required)
अणु
	bool srv_sign_required = server->sec_mode & server->vals->signing_required;
	bool srv_sign_enabled = server->sec_mode & server->vals->signing_enabled;
	bool mnt_sign_enabled = global_secflags & CIFSSEC_MAY_SIGN;

	/*
	 * Is signing required by mnt options? If not then check
	 * global_secflags to see अगर it is there.
	 */
	अगर (!mnt_sign_required)
		mnt_sign_required = ((global_secflags & CIFSSEC_MUST_SIGN) ==
						CIFSSEC_MUST_SIGN);

	/*
	 * If signing is required then it's स्वतःmatically enabled too,
	 * otherwise, check to see अगर the secflags allow it.
	 */
	mnt_sign_enabled = mnt_sign_required ? mnt_sign_required :
				(global_secflags & CIFSSEC_MAY_SIGN);

	/* If server requires signing, करोes client allow it? */
	अगर (srv_sign_required) अणु
		अगर (!mnt_sign_enabled) अणु
			cअगरs_dbg(VFS, "Server requires signing, but it's disabled in SecurityFlags!\n");
			वापस -ENOTSUPP;
		पूर्ण
		server->sign = true;
	पूर्ण

	/* If client requires signing, करोes server allow it? */
	अगर (mnt_sign_required) अणु
		अगर (!srv_sign_enabled) अणु
			cअगरs_dbg(VFS, "Server does not support signing!\n");
			वापस -ENOTSUPP;
		पूर्ण
		server->sign = true;
	पूर्ण

	अगर (cअगरs_rdma_enabled(server) && server->sign)
		cअगरs_dbg(VFS, "Signing is enabled, and RDMA read/write will be disabled\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
अटल पूर्णांक
decode_lanman_negprot_rsp(काष्ठा TCP_Server_Info *server, NEGOTIATE_RSP *pSMBr)
अणु
	__s16 पंचांगp;
	काष्ठा lanman_neg_rsp *rsp = (काष्ठा lanman_neg_rsp *)pSMBr;

	अगर (server->dialect != LANMAN_PROT && server->dialect != LANMAN2_PROT)
		वापस -EOPNOTSUPP;

	server->sec_mode = le16_to_cpu(rsp->SecurityMode);
	server->maxReq = min_t(अचिन्हित पूर्णांक,
			       le16_to_cpu(rsp->MaxMpxCount),
			       cअगरs_max_pending);
	set_credits(server, server->maxReq);
	server->maxBuf = le16_to_cpu(rsp->MaxBufSize);
	/* set up max_पढ़ो क्रम पढ़ोpages check */
	server->max_पढ़ो = server->maxBuf;
	/* even though we करो not use raw we might as well set this
	accurately, in हाल we ever find a need क्रम it */
	अगर ((le16_to_cpu(rsp->RawMode) & RAW_ENABLE) == RAW_ENABLE) अणु
		server->max_rw = 0xFF00;
		server->capabilities = CAP_MPX_MODE | CAP_RAW_MODE;
	पूर्ण अन्यथा अणु
		server->max_rw = 0;/* करो not need to use raw anyway */
		server->capabilities = CAP_MPX_MODE;
	पूर्ण
	पंचांगp = (__s16)le16_to_cpu(rsp->ServerTimeZone);
	अगर (पंचांगp == -1) अणु
		/* OS/2 often करोes not set समयzone thereक्रमe
		 * we must use server समय to calc समय zone.
		 * Could deviate slightly from the right zone.
		 * Smallest defined समयzone dअगरference is 15 minutes
		 * (i.e. Nepal).  Rounding up/करोwn is करोne to match
		 * this requirement.
		 */
		पूर्णांक val, seconds, reमुख्य, result;
		काष्ठा बारpec64 ts;
		समय64_t utc = kसमय_get_real_seconds();
		ts = cnvrtDosUnixTm(rsp->SrvTime.Date,
				    rsp->SrvTime.Time, 0);
		cअगरs_dbg(FYI, "SrvTime %lld sec since 1970 (utc: %lld) diff: %lld\n",
			 ts.tv_sec, utc,
			 utc - ts.tv_sec);
		val = (पूर्णांक)(utc - ts.tv_sec);
		seconds = असल(val);
		result = (seconds / MIN_TZ_ADJ) * MIN_TZ_ADJ;
		reमुख्य = seconds % MIN_TZ_ADJ;
		अगर (reमुख्य >= (MIN_TZ_ADJ / 2))
			result += MIN_TZ_ADJ;
		अगर (val < 0)
			result = -result;
		server->समयAdj = result;
	पूर्ण अन्यथा अणु
		server->समयAdj = (पूर्णांक)पंचांगp;
		server->समयAdj *= 60; /* also in seconds */
	पूर्ण
	cअगरs_dbg(FYI, "server->timeAdj: %d seconds\n", server->समयAdj);


	/* BB get server समय क्रम समय conversions and add
	code to use it and समयzone since this is not UTC */

	अगर (rsp->EncryptionKeyLength ==
			cpu_to_le16(CIFS_CRYPTO_KEY_SIZE)) अणु
		स_नकल(server->cryptkey, rsp->EncryptionKey,
			CIFS_CRYPTO_KEY_SIZE);
	पूर्ण अन्यथा अगर (server->sec_mode & SECMODE_PW_ENCRYPT) अणु
		वापस -EIO; /* need cryptkey unless plain text */
	पूर्ण

	cअगरs_dbg(FYI, "LANMAN negotiated\n");
	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक
decode_lanman_negprot_rsp(काष्ठा TCP_Server_Info *server, NEGOTIATE_RSP *pSMBr)
अणु
	cअगरs_dbg(VFS, "mount failed, cifs module not built with CIFS_WEAK_PW_HASH support\n");
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

अटल bool
should_set_ext_sec_flag(क्रमागत securityEnum sectype)
अणु
	चयन (sectype) अणु
	हाल RawNTLMSSP:
	हाल Kerberos:
		वापस true;
	हाल Unspecअगरied:
		अगर (global_secflags &
		    (CIFSSEC_MAY_KRB5 | CIFSSEC_MAY_NTLMSSP))
			वापस true;
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

पूर्णांक
CIFSSMBNegotiate(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses)
अणु
	NEGOTIATE_REQ *pSMB;
	NEGOTIATE_RSP *pSMBr;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	पूर्णांक i;
	काष्ठा TCP_Server_Info *server = ses->server;
	u16 count;

	अगर (!server) अणु
		WARN(1, "%s: server is NULL!\n", __func__);
		वापस -EIO;
	पूर्ण

	rc = smb_init(SMB_COM_NEGOTIATE, 0, शून्य /* no tcon yet */ ,
		      (व्योम **) &pSMB, (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	pSMB->hdr.Mid = get_next_mid(server);
	pSMB->hdr.Flags2 |= (SMBFLG2_UNICODE | SMBFLG2_ERR_STATUS);

	अगर (should_set_ext_sec_flag(ses->sectype)) अणु
		cअगरs_dbg(FYI, "Requesting extended security\n");
		pSMB->hdr.Flags2 |= SMBFLG2_EXT_SEC;
	पूर्ण

	count = 0;
	/*
	 * We know that all the name entries in the protocols array
	 * are लघु (< 16 bytes anyway) and are NUL terminated.
	 */
	क्रम (i = 0; i < CIFS_NUM_PROT; i++) अणु
		माप_प्रकार len = म_माप(protocols[i].name) + 1;

		स_नकल(pSMB->DialectsArray+count, protocols[i].name, len);
		count += len;
	पूर्ण
	inc_rfc1001_len(pSMB, count);
	pSMB->ByteCount = cpu_to_le16(count);

	rc = SendReceive(xid, ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc != 0)
		जाओ neg_err_निकास;

	server->dialect = le16_to_cpu(pSMBr->DialectIndex);
	cअगरs_dbg(FYI, "Dialect: %d\n", server->dialect);
	/* Check wct = 1 error हाल */
	अगर ((pSMBr->hdr.WordCount < 13) || (server->dialect == BAD_PROT)) अणु
		/* core वापसs wct = 1, but we करो not ask क्रम core - otherwise
		small wct just comes when dialect index is -1 indicating we
		could not negotiate a common dialect */
		rc = -EOPNOTSUPP;
		जाओ neg_err_निकास;
	पूर्ण अन्यथा अगर (pSMBr->hdr.WordCount == 13) अणु
		server->negflavor = CIFS_NEGFLAVOR_LANMAN;
		rc = decode_lanman_negprot_rsp(server, pSMBr);
		जाओ signing_check;
	पूर्ण अन्यथा अगर (pSMBr->hdr.WordCount != 17) अणु
		/* unknown wct */
		rc = -EOPNOTSUPP;
		जाओ neg_err_निकास;
	पूर्ण
	/* अन्यथा wct == 17, NTLM or better */

	server->sec_mode = pSMBr->SecurityMode;
	अगर ((server->sec_mode & SECMODE_USER) == 0)
		cअगरs_dbg(FYI, "share mode security\n");

	/* one byte, so no need to convert this or EncryptionKeyLen from
	   little endian */
	server->maxReq = min_t(अचिन्हित पूर्णांक, le16_to_cpu(pSMBr->MaxMpxCount),
			       cअगरs_max_pending);
	set_credits(server, server->maxReq);
	/* probably no need to store and check maxvcs */
	server->maxBuf = le32_to_cpu(pSMBr->MaxBufferSize);
	/* set up max_पढ़ो क्रम पढ़ोpages check */
	server->max_पढ़ो = server->maxBuf;
	server->max_rw = le32_to_cpu(pSMBr->MaxRawSize);
	cअगरs_dbg(NOISY, "Max buf = %d\n", ses->server->maxBuf);
	server->capabilities = le32_to_cpu(pSMBr->Capabilities);
	server->समयAdj = (पूर्णांक)(__s16)le16_to_cpu(pSMBr->ServerTimeZone);
	server->समयAdj *= 60;

	अगर (pSMBr->EncryptionKeyLength == CIFS_CRYPTO_KEY_SIZE) अणु
		server->negflavor = CIFS_NEGFLAVOR_UNENCAP;
		स_नकल(ses->server->cryptkey, pSMBr->u.EncryptionKey,
		       CIFS_CRYPTO_KEY_SIZE);
	पूर्ण अन्यथा अगर (pSMBr->hdr.Flags2 & SMBFLG2_EXT_SEC ||
			server->capabilities & CAP_EXTENDED_SECURITY) अणु
		server->negflavor = CIFS_NEGFLAVOR_EXTENDED;
		rc = decode_ext_sec_blob(ses, pSMBr);
	पूर्ण अन्यथा अगर (server->sec_mode & SECMODE_PW_ENCRYPT) अणु
		rc = -EIO; /* no crypt key only अगर plain text pwd */
	पूर्ण अन्यथा अणु
		server->negflavor = CIFS_NEGFLAVOR_UNENCAP;
		server->capabilities &= ~CAP_EXTENDED_SECURITY;
	पूर्ण

signing_check:
	अगर (!rc)
		rc = cअगरs_enable_signing(server, ses->sign);
neg_err_निकास:
	cअगरs_buf_release(pSMB);

	cअगरs_dbg(FYI, "negprot rc %d\n", rc);
	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBTDis(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा smb_hdr *smb_buffer;
	पूर्णांक rc = 0;

	cअगरs_dbg(FYI, "In tree disconnect\n");

	/* BB: करो we need to check this? These should never be शून्य. */
	अगर ((tcon->ses == शून्य) || (tcon->ses->server == शून्य))
		वापस -EIO;

	/*
	 * No need to वापस error on this operation अगर tid invalidated and
	 * बंदd on server alपढ़ोy e.g. due to tcp session crashing. Also,
	 * the tcon is no दीर्घer on the list, so no need to take lock beक्रमe
	 * checking this.
	 */
	अगर ((tcon->need_reconnect) || (tcon->ses->need_reconnect))
		वापस 0;

	rc = small_smb_init(SMB_COM_TREE_DISCONNECT, 0, tcon,
			    (व्योम **)&smb_buffer);
	अगर (rc)
		वापस rc;

	rc = SendReceiveNoRsp(xid, tcon->ses, (अक्षर *)smb_buffer, 0);
	cअगरs_small_buf_release(smb_buffer);
	अगर (rc)
		cअगरs_dbg(FYI, "Tree disconnect failed %d\n", rc);

	/* No need to वापस error on this operation अगर tid invalidated and
	   बंदd on server alपढ़ोy e.g. due to tcp session crashing */
	अगर (rc == -EAGAIN)
		rc = 0;

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
cअगरs_echo_callback(काष्ठा mid_q_entry *mid)
अणु
	काष्ठा TCP_Server_Info *server = mid->callback_data;
	काष्ठा cअगरs_credits credits = अणु .value = 1, .instance = 0 पूर्ण;

	DeleteMidQEntry(mid);
	add_credits(server, &credits, CIFS_ECHO_OP);
पूर्ण

पूर्णांक
CIFSSMBEcho(काष्ठा TCP_Server_Info *server)
अणु
	ECHO_REQ *smb;
	पूर्णांक rc = 0;
	काष्ठा kvec iov[2];
	काष्ठा smb_rqst rqst = अणु .rq_iov = iov,
				 .rq_nvec = 2 पूर्ण;

	cअगरs_dbg(FYI, "In echo request\n");

	rc = small_smb_init(SMB_COM_ECHO, 0, शून्य, (व्योम **)&smb);
	अगर (rc)
		वापस rc;

	अगर (server->capabilities & CAP_UNICODE)
		smb->hdr.Flags2 |= SMBFLG2_UNICODE;

	/* set up echo request */
	smb->hdr.Tid = 0xffff;
	smb->hdr.WordCount = 1;
	put_unaligned_le16(1, &smb->EchoCount);
	put_bcc(1, &smb->hdr);
	smb->Data[0] = 'a';
	inc_rfc1001_len(smb, 3);

	iov[0].iov_len = 4;
	iov[0].iov_base = smb;
	iov[1].iov_len = get_rfc1002_length(smb);
	iov[1].iov_base = (अक्षर *)smb + 4;

	rc = cअगरs_call_async(server, &rqst, शून्य, cअगरs_echo_callback, शून्य,
			     server, CIFS_NON_BLOCKING | CIFS_ECHO_OP, शून्य);
	अगर (rc)
		cअगरs_dbg(FYI, "Echo request failed: %d\n", rc);

	cअगरs_small_buf_release(smb);

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBLogoff(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses)
अणु
	LOGOFF_ANDX_REQ *pSMB;
	पूर्णांक rc = 0;

	cअगरs_dbg(FYI, "In SMBLogoff for session disconnect\n");

	/*
	 * BB: करो we need to check validity of ses and server? They should
	 * always be valid since we have an active reference. If not, that
	 * should probably be a BUG()
	 */
	अगर (!ses || !ses->server)
		वापस -EIO;

	mutex_lock(&ses->session_mutex);
	अगर (ses->need_reconnect)
		जाओ session_alपढ़ोy_dead; /* no need to send SMBlogoff अगर uid
					      alपढ़ोy बंदd due to reconnect */
	rc = small_smb_init(SMB_COM_LOGOFF_ANDX, 2, शून्य, (व्योम **)&pSMB);
	अगर (rc) अणु
		mutex_unlock(&ses->session_mutex);
		वापस rc;
	पूर्ण

	pSMB->hdr.Mid = get_next_mid(ses->server);

	अगर (ses->server->sign)
		pSMB->hdr.Flags2 |= SMBFLG2_SECURITY_SIGNATURE;

	pSMB->hdr.Uid = ses->Suid;

	pSMB->AndXCommand = 0xFF;
	rc = SendReceiveNoRsp(xid, ses, (अक्षर *) pSMB, 0);
	cअगरs_small_buf_release(pSMB);
session_alपढ़ोy_dead:
	mutex_unlock(&ses->session_mutex);

	/* अगर session dead then we करो not need to करो ulogoff,
		since server बंदd smb session, no sense reporting
		error */
	अगर (rc == -EAGAIN)
		rc = 0;
	वापस rc;
पूर्ण

पूर्णांक
CIFSPOSIXDelFile(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		 स्थिर अक्षर *fileName, __u16 type,
		 स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
	TRANSACTION2_SPI_REQ *pSMB = शून्य;
	TRANSACTION2_SPI_RSP *pSMBr = शून्य;
	काष्ठा unlink_psx_rq *pRqD;
	पूर्णांक name_len;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, param_offset, offset, byte_count;

	cअगरs_dbg(FYI, "In POSIX delete\n");
PsxDelete:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->FileName, fileName,
				       PATH_MAX, nls_codepage, remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, fileName);
	पूर्ण

	params = 6 + name_len;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	pSMB->MaxDataCount = 0; /* BB द्विगुन check this with jra */
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_spi_req,
				Inक्रमmationLevel) - 4;
	offset = param_offset + params;

	/* Setup poपूर्णांकer to Request Data (inode type) */
	pRqD = (काष्ठा unlink_psx_rq *)(((अक्षर *)&pSMB->hdr.Protocol) + offset);
	pRqD->type = cpu_to_le16(type);
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_PATH_INFORMATION);
	byte_count = 3 /* pad */  + params + माप(काष्ठा unlink_psx_rq);

	pSMB->DataCount = cpu_to_le16(माप(काष्ठा unlink_psx_rq));
	pSMB->TotalDataCount = cpu_to_le16(माप(काष्ठा unlink_psx_rq));
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_POSIX_UNLINK);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc)
		cअगरs_dbg(FYI, "Posix delete returned %d\n", rc);
	cअगरs_buf_release(pSMB);

	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_deletes);

	अगर (rc == -EAGAIN)
		जाओ PsxDelete;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBDelFile(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, स्थिर अक्षर *name,
	       काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	DELETE_खाता_REQ *pSMB = शून्य;
	DELETE_खाता_RSP *pSMBr = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len;
	पूर्णांक remap = cअगरs_remap(cअगरs_sb);

DelFileRetry:
	rc = smb_init(SMB_COM_DELETE, 1, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len = cअगरsConvertToUTF16((__le16 *) pSMB->fileName, name,
					      PATH_MAX, cअगरs_sb->local_nls,
					      remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->fileName, name);
	पूर्ण
	pSMB->SearchAttributes =
	    cpu_to_le16(ATTR_READONLY | ATTR_HIDDEN | ATTR_SYSTEM);
	pSMB->BufferFormat = 0x04;
	inc_rfc1001_len(pSMB, name_len + 1);
	pSMB->ByteCount = cpu_to_le16(name_len + 1);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_deletes);
	अगर (rc)
		cअगरs_dbg(FYI, "Error in RMFile = %d\n", rc);

	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ DelFileRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBRmDir(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, स्थिर अक्षर *name,
	     काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	DELETE_सूचीECTORY_REQ *pSMB = शून्य;
	DELETE_सूचीECTORY_RSP *pSMBr = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len;
	पूर्णांक remap = cअगरs_remap(cअगरs_sb);

	cअगरs_dbg(FYI, "In CIFSSMBRmDir\n");
RmDirRetry:
	rc = smb_init(SMB_COM_DELETE_सूचीECTORY, 0, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len = cअगरsConvertToUTF16((__le16 *) pSMB->DirName, name,
					      PATH_MAX, cअगरs_sb->local_nls,
					      remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->DirName, name);
	पूर्ण

	pSMB->BufferFormat = 0x04;
	inc_rfc1001_len(pSMB, name_len + 1);
	pSMB->ByteCount = cpu_to_le16(name_len + 1);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_सूची_हटाओs);
	अगर (rc)
		cअगरs_dbg(FYI, "Error in RMDir = %d\n", rc);

	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ RmDirRetry;
	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBMkDir(स्थिर अचिन्हित पूर्णांक xid, काष्ठा inode *inode, umode_t mode,
	     काष्ठा cअगरs_tcon *tcon, स्थिर अक्षर *name,
	     काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	पूर्णांक rc = 0;
	CREATE_सूचीECTORY_REQ *pSMB = शून्य;
	CREATE_सूचीECTORY_RSP *pSMBr = शून्य;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len;
	पूर्णांक remap = cअगरs_remap(cअगरs_sb);

	cअगरs_dbg(FYI, "In CIFSSMBMkDir\n");
MkDirRetry:
	rc = smb_init(SMB_COM_CREATE_सूचीECTORY, 0, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len = cअगरsConvertToUTF16((__le16 *) pSMB->DirName, name,
					      PATH_MAX, cअगरs_sb->local_nls,
					      remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->DirName, name);
	पूर्ण

	pSMB->BufferFormat = 0x04;
	inc_rfc1001_len(pSMB, name_len + 1);
	pSMB->ByteCount = cpu_to_le16(name_len + 1);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_सूची_गढ़ोs);
	अगर (rc)
		cअगरs_dbg(FYI, "Error in Mkdir = %d\n", rc);

	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ MkDirRetry;
	वापस rc;
पूर्ण

पूर्णांक
CIFSPOSIXCreate(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		__u32 posix_flags, __u64 mode, __u16 *netfid,
		खाता_UNIX_BASIC_INFO *pRetData, __u32 *pOplock,
		स्थिर अक्षर *name, स्थिर काष्ठा nls_table *nls_codepage,
		पूर्णांक remap)
अणु
	TRANSACTION2_SPI_REQ *pSMB = शून्य;
	TRANSACTION2_SPI_RSP *pSMBr = शून्य;
	पूर्णांक name_len;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, param_offset, offset, byte_count, count;
	OPEN_PSX_REQ *pdata;
	OPEN_PSX_RSP *psx_rsp;

	cअगरs_dbg(FYI, "In POSIX Create\n");
PsxCreat:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->FileName, name,
				       PATH_MAX, nls_codepage, remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, name);
	पूर्ण

	params = 6 + name_len;
	count = माप(OPEN_PSX_REQ);
	pSMB->MaxParameterCount = cpu_to_le16(2);
	pSMB->MaxDataCount = cpu_to_le16(1000);	/* large enough */
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_spi_req,
				Inक्रमmationLevel) - 4;
	offset = param_offset + params;
	pdata = (OPEN_PSX_REQ *)(((अक्षर *)&pSMB->hdr.Protocol) + offset);
	pdata->Level = cpu_to_le16(SMB_QUERY_खाता_UNIX_BASIC);
	pdata->Permissions = cpu_to_le64(mode);
	pdata->PosixOpenFlags = cpu_to_le32(posix_flags);
	pdata->OpenFlags =  cpu_to_le32(*pOplock);
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_PATH_INFORMATION);
	byte_count = 3 /* pad */  + params + count;

	pSMB->DataCount = cpu_to_le16(count);
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_POSIX_OPEN);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Posix create returned %d\n", rc);
		जाओ psx_create_err;
	पूर्ण

	cअगरs_dbg(FYI, "copying inode info\n");
	rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

	अगर (rc || get_bcc(&pSMBr->hdr) < माप(OPEN_PSX_RSP)) अणु
		rc = -EIO;	/* bad smb */
		जाओ psx_create_err;
	पूर्ण

	/* copy वापस inक्रमmation to pRetData */
	psx_rsp = (OPEN_PSX_RSP *)((अक्षर *) &pSMBr->hdr.Protocol
			+ le16_to_cpu(pSMBr->t2.DataOffset));

	*pOplock = le16_to_cpu(psx_rsp->OplockFlags);
	अगर (netfid)
		*netfid = psx_rsp->Fid;   /* cअगरs fid stays in le */
	/* Let caller know file was created so we can set the mode. */
	/* Do we care about the CreateAction in any other हालs? */
	अगर (cpu_to_le32(खाता_CREATE) == psx_rsp->CreateAction)
		*pOplock |= CIFS_CREATE_ACTION;
	/* check to make sure response data is there */
	अगर (psx_rsp->ReturnedLevel != cpu_to_le16(SMB_QUERY_खाता_UNIX_BASIC)) अणु
		pRetData->Type = cpu_to_le32(-1); /* unknown */
		cअगरs_dbg(NOISY, "unknown type\n");
	पूर्ण अन्यथा अणु
		अगर (get_bcc(&pSMBr->hdr) < माप(OPEN_PSX_RSP)
					+ माप(खाता_UNIX_BASIC_INFO)) अणु
			cअगरs_dbg(VFS, "Open response data too small\n");
			pRetData->Type = cpu_to_le32(-1);
			जाओ psx_create_err;
		पूर्ण
		स_नकल((अक्षर *) pRetData,
			(अक्षर *)psx_rsp + माप(OPEN_PSX_RSP),
			माप(खाता_UNIX_BASIC_INFO));
	पूर्ण

psx_create_err:
	cअगरs_buf_release(pSMB);

	अगर (posix_flags & SMB_O_सूचीECTORY)
		cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_posixसूची_गढ़ोs);
	अन्यथा
		cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_posixखोलोs);

	अगर (rc == -EAGAIN)
		जाओ PsxCreat;

	वापस rc;
पूर्ण

अटल __u16 convert_disposition(पूर्णांक disposition)
अणु
	__u16 ofun = 0;

	चयन (disposition) अणु
		हाल खाता_SUPERSEDE:
			ofun = SMBOPEN_OCREATE | SMBOPEN_OTRUNC;
			अवरोध;
		हाल खाता_OPEN:
			ofun = SMBOPEN_OAPPEND;
			अवरोध;
		हाल खाता_CREATE:
			ofun = SMBOPEN_OCREATE;
			अवरोध;
		हाल खाता_OPEN_IF:
			ofun = SMBOPEN_OCREATE | SMBOPEN_OAPPEND;
			अवरोध;
		हाल खाता_OVERWRITE:
			ofun = SMBOPEN_OTRUNC;
			अवरोध;
		हाल खाता_OVERWRITE_IF:
			ofun = SMBOPEN_OCREATE | SMBOPEN_OTRUNC;
			अवरोध;
		शेष:
			cअगरs_dbg(FYI, "unknown disposition %d\n", disposition);
			ofun =  SMBOPEN_OAPPEND; /* regular खोलो */
	पूर्ण
	वापस ofun;
पूर्ण

अटल पूर्णांक
access_flags_to_smbखोलो_mode(स्थिर पूर्णांक access_flags)
अणु
	पूर्णांक masked_flags = access_flags & (GENERIC_READ | GENERIC_WRITE);

	अगर (masked_flags == GENERIC_READ)
		वापस SMBOPEN_READ;
	अन्यथा अगर (masked_flags == GENERIC_WRITE)
		वापस SMBOPEN_WRITE;

	/* just go क्रम पढ़ो/ग_लिखो */
	वापस SMBOPEN_READWRITE;
पूर्ण

पूर्णांक
SMBLegacyOpen(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	    स्थिर अक्षर *fileName, स्थिर पूर्णांक खोलोDisposition,
	    स्थिर पूर्णांक access_flags, स्थिर पूर्णांक create_options, __u16 *netfid,
	    पूर्णांक *pOplock, खाता_ALL_INFO *pfile_info,
	    स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
	पूर्णांक rc = -EACCES;
	OPENX_REQ *pSMB = शून्य;
	OPENX_RSP *pSMBr = शून्य;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len;
	__u16 count;

OldOpenRetry:
	rc = smb_init(SMB_COM_OPEN_ANDX, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	pSMB->AndXCommand = 0xFF;       /* none */

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		count = 1;      /* account क्रम one byte pad to word boundary */
		name_len =
		   cअगरsConvertToUTF16((__le16 *) (pSMB->fileName + 1),
				      fileName, PATH_MAX, nls_codepage, remap);
		name_len++;     /* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		count = 0;      /* no pad */
		name_len = copy_path_name(pSMB->fileName, fileName);
	पूर्ण
	अगर (*pOplock & REQ_OPLOCK)
		pSMB->OpenFlags = cpu_to_le16(REQ_OPLOCK);
	अन्यथा अगर (*pOplock & REQ_BATCHOPLOCK)
		pSMB->OpenFlags = cpu_to_le16(REQ_BATCHOPLOCK);

	pSMB->OpenFlags |= cpu_to_le16(REQ_MORE_INFO);
	pSMB->Mode = cpu_to_le16(access_flags_to_smbखोलो_mode(access_flags));
	pSMB->Mode |= cpu_to_le16(0x40); /* deny none */
	/* set file as प्रणाली file अगर special file such
	   as fअगरo and server expecting SFU style and
	   no Unix extensions */

	अगर (create_options & CREATE_OPTION_SPECIAL)
		pSMB->FileAttributes = cpu_to_le16(ATTR_SYSTEM);
	अन्यथा /* BB FIXME BB */
		pSMB->FileAttributes = cpu_to_le16(0/*ATTR_NORMAL*/);

	अगर (create_options & CREATE_OPTION_READONLY)
		pSMB->FileAttributes |= cpu_to_le16(ATTR_READONLY);

	/* BB FIXME BB */
/*	pSMB->CreateOptions = cpu_to_le32(create_options &
						 CREATE_OPTIONS_MASK); */
	/* BB FIXME END BB */

	pSMB->Sattr = cpu_to_le16(ATTR_HIDDEN | ATTR_SYSTEM | ATTR_सूचीECTORY);
	pSMB->OpenFunction = cpu_to_le16(convert_disposition(खोलोDisposition));
	count += name_len;
	inc_rfc1001_len(pSMB, count);

	pSMB->ByteCount = cpu_to_le16(count);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			(काष्ठा smb_hdr *)pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_खोलोs);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Error in Open = %d\n", rc);
	पूर्ण अन्यथा अणु
	/* BB verअगरy अगर wct == 15 */

/*		*pOplock = pSMBr->OplockLevel; */ /* BB take from action field*/

		*netfid = pSMBr->Fid;   /* cअगरs fid stays in le */
		/* Let caller know file was created so we can set the mode. */
		/* Do we care about the CreateAction in any other हालs? */
	/* BB FIXME BB */
/*		अगर (cpu_to_le32(खाता_CREATE) == pSMBr->CreateAction)
			*pOplock |= CIFS_CREATE_ACTION; */
	/* BB FIXME END */

		अगर (pfile_info) अणु
			pfile_info->CreationTime = 0; /* BB convert CreateTime*/
			pfile_info->LastAccessTime = 0; /* BB fixme */
			pfile_info->LastWriteTime = 0; /* BB fixme */
			pfile_info->ChangeTime = 0;  /* BB fixme */
			pfile_info->Attributes =
				cpu_to_le32(le16_to_cpu(pSMBr->FileAttributes));
			/* the file_info buf is endian converted by caller */
			pfile_info->AllocationSize =
				cpu_to_le64(le32_to_cpu(pSMBr->EndOfFile));
			pfile_info->EndOfFile = pfile_info->AllocationSize;
			pfile_info->NumberOfLinks = cpu_to_le32(1);
			pfile_info->DeletePending = 0;
		पूर्ण
	पूर्ण

	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ OldOpenRetry;
	वापस rc;
पूर्ण

पूर्णांक
CIFS_खोलो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_खोलो_parms *oparms, पूर्णांक *oplock,
	  खाता_ALL_INFO *buf)
अणु
	पूर्णांक rc;
	OPEN_REQ *req = शून्य;
	OPEN_RSP *rsp = शून्य;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len;
	__u16 count;
	काष्ठा cअगरs_sb_info *cअगरs_sb = oparms->cअगरs_sb;
	काष्ठा cअगरs_tcon *tcon = oparms->tcon;
	पूर्णांक remap = cअगरs_remap(cअगरs_sb);
	स्थिर काष्ठा nls_table *nls = cअगरs_sb->local_nls;
	पूर्णांक create_options = oparms->create_options;
	पूर्णांक desired_access = oparms->desired_access;
	पूर्णांक disposition = oparms->disposition;
	स्थिर अक्षर *path = oparms->path;

खोलोRetry:
	rc = smb_init(SMB_COM_NT_CREATE_ANDX, 24, tcon, (व्योम **)&req,
		      (व्योम **)&rsp);
	अगर (rc)
		वापस rc;

	/* no commands go after this */
	req->AndXCommand = 0xFF;

	अगर (req->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		/* account क्रम one byte pad to word boundary */
		count = 1;
		name_len = cअगरsConvertToUTF16((__le16 *)(req->fileName + 1),
					      path, PATH_MAX, nls, remap);
		/* trailing null */
		name_len++;
		name_len *= 2;
		req->NameLength = cpu_to_le16(name_len);
	पूर्ण अन्यथा अणु
		/* BB improve check क्रम buffer overruns BB */
		/* no pad */
		count = 0;
		name_len = copy_path_name(req->fileName, path);
		req->NameLength = cpu_to_le16(name_len);
	पूर्ण

	अगर (*oplock & REQ_OPLOCK)
		req->OpenFlags = cpu_to_le32(REQ_OPLOCK);
	अन्यथा अगर (*oplock & REQ_BATCHOPLOCK)
		req->OpenFlags = cpu_to_le32(REQ_BATCHOPLOCK);

	req->DesiredAccess = cpu_to_le32(desired_access);
	req->AllocationSize = 0;

	/*
	 * Set file as प्रणाली file अगर special file such as fअगरo and server
	 * expecting SFU style and no Unix extensions.
	 */
	अगर (create_options & CREATE_OPTION_SPECIAL)
		req->FileAttributes = cpu_to_le32(ATTR_SYSTEM);
	अन्यथा
		req->FileAttributes = cpu_to_le32(ATTR_NORMAL);

	/*
	 * XP करोes not handle ATTR_POSIX_SEMANTICS but it helps speed up हाल
	 * sensitive checks क्रम other servers such as Samba.
	 */
	अगर (tcon->ses->capabilities & CAP_UNIX)
		req->FileAttributes |= cpu_to_le32(ATTR_POSIX_SEMANTICS);

	अगर (create_options & CREATE_OPTION_READONLY)
		req->FileAttributes |= cpu_to_le32(ATTR_READONLY);

	req->ShareAccess = cpu_to_le32(खाता_SHARE_ALL);
	req->CreateDisposition = cpu_to_le32(disposition);
	req->CreateOptions = cpu_to_le32(create_options & CREATE_OPTIONS_MASK);

	/* BB Expirement with various impersonation levels and verअगरy */
	req->ImpersonationLevel = cpu_to_le32(SECURITY_IMPERSONATION);
	req->SecurityFlags = SECURITY_CONTEXT_TRACKING|SECURITY_EFFECTIVE_ONLY;

	count += name_len;
	inc_rfc1001_len(req, count);

	req->ByteCount = cpu_to_le16(count);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *)req,
			 (काष्ठा smb_hdr *)rsp, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_खोलोs);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Error in Open = %d\n", rc);
		cअगरs_buf_release(req);
		अगर (rc == -EAGAIN)
			जाओ खोलोRetry;
		वापस rc;
	पूर्ण

	/* 1 byte no need to le_to_cpu */
	*oplock = rsp->OplockLevel;
	/* cअगरs fid stays in le */
	oparms->fid->netfid = rsp->Fid;
	oparms->fid->access = desired_access;

	/* Let caller know file was created so we can set the mode. */
	/* Do we care about the CreateAction in any other हालs? */
	अगर (cpu_to_le32(खाता_CREATE) == rsp->CreateAction)
		*oplock |= CIFS_CREATE_ACTION;

	अगर (buf) अणु
		/* copy from CreationTime to Attributes */
		स_नकल((अक्षर *)buf, (अक्षर *)&rsp->CreationTime, 36);
		/* the file_info buf is endian converted by caller */
		buf->AllocationSize = rsp->AllocationSize;
		buf->EndOfFile = rsp->EndOfFile;
		buf->NumberOfLinks = cpu_to_le32(1);
		buf->DeletePending = 0;
	पूर्ण

	cअगरs_buf_release(req);
	वापस rc;
पूर्ण

/*
 * Discard any reमुख्यing data in the current SMB. To करो this, we borrow the
 * current bigbuf.
 */
पूर्णांक
cअगरs_discard_reमुख्यing_data(काष्ठा TCP_Server_Info *server)
अणु
	अचिन्हित पूर्णांक rfclen = server->pdu_size;
	पूर्णांक reमुख्यing = rfclen + server->vals->header_preamble_size -
		server->total_पढ़ो;

	जबतक (reमुख्यing > 0) अणु
		पूर्णांक length;

		length = cअगरs_discard_from_socket(server,
				min_t(माप_प्रकार, reमुख्यing,
				      CIFSMaxBufSize + MAX_HEADER_SIZE(server)));
		अगर (length < 0)
			वापस length;
		server->total_पढ़ो += length;
		reमुख्यing -= length;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
__cअगरs_पढ़ोv_discard(काष्ठा TCP_Server_Info *server, काष्ठा mid_q_entry *mid,
		     bool malक्रमmed)
अणु
	पूर्णांक length;

	length = cअगरs_discard_reमुख्यing_data(server);
	dequeue_mid(mid, malक्रमmed);
	mid->resp_buf = server->smallbuf;
	server->smallbuf = शून्य;
	वापस length;
पूर्ण

अटल पूर्णांक
cअगरs_पढ़ोv_discard(काष्ठा TCP_Server_Info *server, काष्ठा mid_q_entry *mid)
अणु
	काष्ठा cअगरs_पढ़ोdata *rdata = mid->callback_data;

	वापस  __cअगरs_पढ़ोv_discard(server, mid, rdata->result);
पूर्ण

पूर्णांक
cअगरs_पढ़ोv_receive(काष्ठा TCP_Server_Info *server, काष्ठा mid_q_entry *mid)
अणु
	पूर्णांक length, len;
	अचिन्हित पूर्णांक data_offset, data_len;
	काष्ठा cअगरs_पढ़ोdata *rdata = mid->callback_data;
	अक्षर *buf = server->smallbuf;
	अचिन्हित पूर्णांक buflen = server->pdu_size +
		server->vals->header_preamble_size;
	bool use_rdma_mr = false;

	cअगरs_dbg(FYI, "%s: mid=%llu offset=%llu bytes=%u\n",
		 __func__, mid->mid, rdata->offset, rdata->bytes);

	/*
	 * पढ़ो the rest of READ_RSP header (sans Data array), or whatever we
	 * can अगर there's not enough data. At this point, we've पढ़ो करोwn to
	 * the Mid.
	 */
	len = min_t(अचिन्हित पूर्णांक, buflen, server->vals->पढ़ो_rsp_size) -
							HEADER_SIZE(server) + 1;

	length = cअगरs_पढ़ो_from_socket(server,
				       buf + HEADER_SIZE(server) - 1, len);
	अगर (length < 0)
		वापस length;
	server->total_पढ़ो += length;

	अगर (server->ops->is_session_expired &&
	    server->ops->is_session_expired(buf)) अणु
		cअगरs_reconnect(server);
		वापस -1;
	पूर्ण

	अगर (server->ops->is_status_pending &&
	    server->ops->is_status_pending(buf, server)) अणु
		cअगरs_discard_reमुख्यing_data(server);
		वापस -1;
	पूर्ण

	/* set up first two iov क्रम signature check and to get credits */
	rdata->iov[0].iov_base = buf;
	rdata->iov[0].iov_len = server->vals->header_preamble_size;
	rdata->iov[1].iov_base = buf + server->vals->header_preamble_size;
	rdata->iov[1].iov_len =
		server->total_पढ़ो - server->vals->header_preamble_size;
	cअगरs_dbg(FYI, "0: iov_base=%p iov_len=%zu\n",
		 rdata->iov[0].iov_base, rdata->iov[0].iov_len);
	cअगरs_dbg(FYI, "1: iov_base=%p iov_len=%zu\n",
		 rdata->iov[1].iov_base, rdata->iov[1].iov_len);

	/* Was the SMB पढ़ो successful? */
	rdata->result = server->ops->map_error(buf, false);
	अगर (rdata->result != 0) अणु
		cअगरs_dbg(FYI, "%s: server returned error %d\n",
			 __func__, rdata->result);
		/* normal error on पढ़ो response */
		वापस __cअगरs_पढ़ोv_discard(server, mid, false);
	पूर्ण

	/* Is there enough to get to the rest of the READ_RSP header? */
	अगर (server->total_पढ़ो < server->vals->पढ़ो_rsp_size) अणु
		cअगरs_dbg(FYI, "%s: server returned short header. got=%u expected=%zu\n",
			 __func__, server->total_पढ़ो,
			 server->vals->पढ़ो_rsp_size);
		rdata->result = -EIO;
		वापस cअगरs_पढ़ोv_discard(server, mid);
	पूर्ण

	data_offset = server->ops->पढ़ो_data_offset(buf) +
		server->vals->header_preamble_size;
	अगर (data_offset < server->total_पढ़ो) अणु
		/*
		 * win2k8 someबार sends an offset of 0 when the पढ़ो
		 * is beyond the खातापूर्ण. Treat it as अगर the data starts just after
		 * the header.
		 */
		cअगरs_dbg(FYI, "%s: data offset (%u) inside read response header\n",
			 __func__, data_offset);
		data_offset = server->total_पढ़ो;
	पूर्ण अन्यथा अगर (data_offset > MAX_CIFS_SMALL_BUFFER_SIZE) अणु
		/* data_offset is beyond the end of smallbuf */
		cअगरs_dbg(FYI, "%s: data offset (%u) beyond end of smallbuf\n",
			 __func__, data_offset);
		rdata->result = -EIO;
		वापस cअगरs_पढ़ोv_discard(server, mid);
	पूर्ण

	cअगरs_dbg(FYI, "%s: total_read=%u data_offset=%u\n",
		 __func__, server->total_पढ़ो, data_offset);

	len = data_offset - server->total_पढ़ो;
	अगर (len > 0) अणु
		/* पढ़ो any junk beक्रमe data पूर्णांकo the rest of smallbuf */
		length = cअगरs_पढ़ो_from_socket(server,
					       buf + server->total_पढ़ो, len);
		अगर (length < 0)
			वापस length;
		server->total_पढ़ो += length;
	पूर्ण

	/* how much data is in the response? */
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	use_rdma_mr = rdata->mr;
#पूर्ण_अगर
	data_len = server->ops->पढ़ो_data_length(buf, use_rdma_mr);
	अगर (!use_rdma_mr && (data_offset + data_len > buflen)) अणु
		/* data_len is corrupt -- discard frame */
		rdata->result = -EIO;
		वापस cअगरs_पढ़ोv_discard(server, mid);
	पूर्ण

	length = rdata->पढ़ो_पूर्णांकo_pages(server, rdata, data_len);
	अगर (length < 0)
		वापस length;

	server->total_पढ़ो += length;

	cअगरs_dbg(FYI, "total_read=%u buflen=%u remaining=%u\n",
		 server->total_पढ़ो, buflen, data_len);

	/* discard anything left over */
	अगर (server->total_पढ़ो < buflen)
		वापस cअगरs_पढ़ोv_discard(server, mid);

	dequeue_mid(mid, false);
	mid->resp_buf = server->smallbuf;
	server->smallbuf = शून्य;
	वापस length;
पूर्ण

अटल व्योम
cअगरs_पढ़ोv_callback(काष्ठा mid_q_entry *mid)
अणु
	काष्ठा cअगरs_पढ़ोdata *rdata = mid->callback_data;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(rdata->cfile->tlink);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	काष्ठा smb_rqst rqst = अणु .rq_iov = rdata->iov,
				 .rq_nvec = 2,
				 .rq_pages = rdata->pages,
				 .rq_offset = rdata->page_offset,
				 .rq_npages = rdata->nr_pages,
				 .rq_pagesz = rdata->pagesz,
				 .rq_tailsz = rdata->tailsz पूर्ण;
	काष्ठा cअगरs_credits credits = अणु .value = 1, .instance = 0 पूर्ण;

	cअगरs_dbg(FYI, "%s: mid=%llu state=%d result=%d bytes=%u\n",
		 __func__, mid->mid, mid->mid_state, rdata->result,
		 rdata->bytes);

	चयन (mid->mid_state) अणु
	हाल MID_RESPONSE_RECEIVED:
		/* result alपढ़ोy set, check signature */
		अगर (server->sign) अणु
			पूर्णांक rc = 0;

			rc = cअगरs_verअगरy_signature(&rqst, server,
						  mid->sequence_number);
			अगर (rc)
				cअगरs_dbg(VFS, "SMB signature verification returned error = %d\n",
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
	शेष:
		rdata->result = -EIO;
	पूर्ण

	queue_work(cअगरsiod_wq, &rdata->work);
	DeleteMidQEntry(mid);
	add_credits(server, &credits, 0);
पूर्ण

/* cअगरs_async_पढ़ोv - send an async ग_लिखो, and set up mid to handle result */
पूर्णांक
cअगरs_async_पढ़ोv(काष्ठा cअगरs_पढ़ोdata *rdata)
अणु
	पूर्णांक rc;
	READ_REQ *smb = शून्य;
	पूर्णांक wct;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(rdata->cfile->tlink);
	काष्ठा smb_rqst rqst = अणु .rq_iov = rdata->iov,
				 .rq_nvec = 2 पूर्ण;

	cअगरs_dbg(FYI, "%s: offset=%llu bytes=%u\n",
		 __func__, rdata->offset, rdata->bytes);

	अगर (tcon->ses->capabilities & CAP_LARGE_खाताS)
		wct = 12;
	अन्यथा अणु
		wct = 10; /* old style पढ़ो */
		अगर ((rdata->offset >> 32) > 0)  अणु
			/* can not handle this big offset क्रम old */
			वापस -EIO;
		पूर्ण
	पूर्ण

	rc = small_smb_init(SMB_COM_READ_ANDX, wct, tcon, (व्योम **)&smb);
	अगर (rc)
		वापस rc;

	smb->hdr.Pid = cpu_to_le16((__u16)rdata->pid);
	smb->hdr.PidHigh = cpu_to_le16((__u16)(rdata->pid >> 16));

	smb->AndXCommand = 0xFF;	/* none */
	smb->Fid = rdata->cfile->fid.netfid;
	smb->OffsetLow = cpu_to_le32(rdata->offset & 0xFFFFFFFF);
	अगर (wct == 12)
		smb->OffsetHigh = cpu_to_le32(rdata->offset >> 32);
	smb->Reमुख्यing = 0;
	smb->MaxCount = cpu_to_le16(rdata->bytes & 0xFFFF);
	smb->MaxCountHigh = cpu_to_le32(rdata->bytes >> 16);
	अगर (wct == 12)
		smb->ByteCount = 0;
	अन्यथा अणु
		/* old style पढ़ो */
		काष्ठा smb_com_पढ़ोx_req *smbr =
			(काष्ठा smb_com_पढ़ोx_req *)smb;
		smbr->ByteCount = 0;
	पूर्ण

	/* 4 क्रम RFC1001 length + 1 क्रम BCC */
	rdata->iov[0].iov_base = smb;
	rdata->iov[0].iov_len = 4;
	rdata->iov[1].iov_base = (अक्षर *)smb + 4;
	rdata->iov[1].iov_len = get_rfc1002_length(smb);

	kref_get(&rdata->refcount);
	rc = cअगरs_call_async(tcon->ses->server, &rqst, cअगरs_पढ़ोv_receive,
			     cअगरs_पढ़ोv_callback, शून्य, rdata, 0, शून्य);

	अगर (rc == 0)
		cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_पढ़ोs);
	अन्यथा
		kref_put(&rdata->refcount, cअगरs_पढ़ोdata_release);

	cअगरs_small_buf_release(smb);
	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBRead(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_io_parms *io_parms,
	    अचिन्हित पूर्णांक *nbytes, अक्षर **buf, पूर्णांक *pbuf_type)
अणु
	पूर्णांक rc = -EACCES;
	READ_REQ *pSMB = शून्य;
	READ_RSP *pSMBr = शून्य;
	अक्षर *pReadData = शून्य;
	पूर्णांक wct;
	पूर्णांक resp_buf_type = 0;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov;
	__u32 pid = io_parms->pid;
	__u16 netfid = io_parms->netfid;
	__u64 offset = io_parms->offset;
	काष्ठा cअगरs_tcon *tcon = io_parms->tcon;
	अचिन्हित पूर्णांक count = io_parms->length;

	cअगरs_dbg(FYI, "Reading %d bytes on fid %d\n", count, netfid);
	अगर (tcon->ses->capabilities & CAP_LARGE_खाताS)
		wct = 12;
	अन्यथा अणु
		wct = 10; /* old style पढ़ो */
		अगर ((offset >> 32) > 0)  अणु
			/* can not handle this big offset क्रम old */
			वापस -EIO;
		पूर्ण
	पूर्ण

	*nbytes = 0;
	rc = small_smb_init(SMB_COM_READ_ANDX, wct, tcon, (व्योम **) &pSMB);
	अगर (rc)
		वापस rc;

	pSMB->hdr.Pid = cpu_to_le16((__u16)pid);
	pSMB->hdr.PidHigh = cpu_to_le16((__u16)(pid >> 16));

	/* tcon and ses poपूर्णांकer are checked in smb_init */
	अगर (tcon->ses->server == शून्य)
		वापस -ECONNABORTED;

	pSMB->AndXCommand = 0xFF;       /* none */
	pSMB->Fid = netfid;
	pSMB->OffsetLow = cpu_to_le32(offset & 0xFFFFFFFF);
	अगर (wct == 12)
		pSMB->OffsetHigh = cpu_to_le32(offset >> 32);

	pSMB->Reमुख्यing = 0;
	pSMB->MaxCount = cpu_to_le16(count & 0xFFFF);
	pSMB->MaxCountHigh = cpu_to_le32(count >> 16);
	अगर (wct == 12)
		pSMB->ByteCount = 0;  /* no need to करो le conversion since 0 */
	अन्यथा अणु
		/* old style पढ़ो */
		काष्ठा smb_com_पढ़ोx_req *pSMBW =
			(काष्ठा smb_com_पढ़ोx_req *)pSMB;
		pSMBW->ByteCount = 0;
	पूर्ण

	iov[0].iov_base = (अक्षर *)pSMB;
	iov[0].iov_len = be32_to_cpu(pSMB->hdr.smb_buf_length) + 4;
	rc = SendReceive2(xid, tcon->ses, iov, 1, &resp_buf_type,
			  CIFS_LOG_ERROR, &rsp_iov);
	cअगरs_small_buf_release(pSMB);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_पढ़ोs);
	pSMBr = (READ_RSP *)rsp_iov.iov_base;
	अगर (rc) अणु
		cअगरs_dbg(VFS, "Send error in read = %d\n", rc);
	पूर्ण अन्यथा अणु
		पूर्णांक data_length = le16_to_cpu(pSMBr->DataLengthHigh);
		data_length = data_length << 16;
		data_length += le16_to_cpu(pSMBr->DataLength);
		*nbytes = data_length;

		/*check that DataLength would not go beyond end of SMB */
		अगर ((data_length > CIFSMaxBufSize)
				|| (data_length > count)) अणु
			cअगरs_dbg(FYI, "bad length %d for count %d\n",
				 data_length, count);
			rc = -EIO;
			*nbytes = 0;
		पूर्ण अन्यथा अणु
			pReadData = (अक्षर *) (&pSMBr->hdr.Protocol) +
					le16_to_cpu(pSMBr->DataOffset);
/*			अगर (rc = copy_to_user(buf, pReadData, data_length)) अणु
				cअगरs_dbg(VFS, "Faulting on read rc = %d\n",rc);
				rc = -EFAULT;
			पूर्ण*/ /* can not use copy_to_user when using page cache*/
			अगर (*buf)
				स_नकल(*buf, pReadData, data_length);
		पूर्ण
	पूर्ण

	अगर (*buf) अणु
		मुक्त_rsp_buf(resp_buf_type, rsp_iov.iov_base);
	पूर्ण अन्यथा अगर (resp_buf_type != CIFS_NO_BUFFER) अणु
		/* वापस buffer to caller to मुक्त */
		*buf = rsp_iov.iov_base;
		अगर (resp_buf_type == CIFS_SMALL_BUFFER)
			*pbuf_type = CIFS_SMALL_BUFFER;
		अन्यथा अगर (resp_buf_type == CIFS_LARGE_BUFFER)
			*pbuf_type = CIFS_LARGE_BUFFER;
	पूर्ण /* अन्यथा no valid buffer on वापस - leave as null */

	/* Note: On -EAGAIN error only caller can retry on handle based calls
		since file handle passed in no दीर्घer valid */
	वापस rc;
पूर्ण


पूर्णांक
CIFSSMBWrite(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_io_parms *io_parms,
	     अचिन्हित पूर्णांक *nbytes, स्थिर अक्षर *buf)
अणु
	पूर्णांक rc = -EACCES;
	WRITE_REQ *pSMB = शून्य;
	WRITE_RSP *pSMBr = शून्य;
	पूर्णांक bytes_वापसed, wct;
	__u32 bytes_sent;
	__u16 byte_count;
	__u32 pid = io_parms->pid;
	__u16 netfid = io_parms->netfid;
	__u64 offset = io_parms->offset;
	काष्ठा cअगरs_tcon *tcon = io_parms->tcon;
	अचिन्हित पूर्णांक count = io_parms->length;

	*nbytes = 0;

	/* cअगरs_dbg(FYI, "write at %lld %d bytes\n", offset, count);*/
	अगर (tcon->ses == शून्य)
		वापस -ECONNABORTED;

	अगर (tcon->ses->capabilities & CAP_LARGE_खाताS)
		wct = 14;
	अन्यथा अणु
		wct = 12;
		अगर ((offset >> 32) > 0) अणु
			/* can not handle big offset क्रम old srv */
			वापस -EIO;
		पूर्ण
	पूर्ण

	rc = smb_init(SMB_COM_WRITE_ANDX, wct, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	pSMB->hdr.Pid = cpu_to_le16((__u16)pid);
	pSMB->hdr.PidHigh = cpu_to_le16((__u16)(pid >> 16));

	/* tcon and ses poपूर्णांकer are checked in smb_init */
	अगर (tcon->ses->server == शून्य)
		वापस -ECONNABORTED;

	pSMB->AndXCommand = 0xFF;	/* none */
	pSMB->Fid = netfid;
	pSMB->OffsetLow = cpu_to_le32(offset & 0xFFFFFFFF);
	अगर (wct == 14)
		pSMB->OffsetHigh = cpu_to_le32(offset >> 32);

	pSMB->Reserved = 0xFFFFFFFF;
	pSMB->WriteMode = 0;
	pSMB->Reमुख्यing = 0;

	/* Can increase buffer size अगर buffer is big enough in some हालs ie we
	can send more अगर LARGE_WRITE_X capability वापसed by the server and अगर
	our buffer is big enough or अगर we convert to iovecs on socket ग_लिखोs
	and eliminate the copy to the CIFS buffer */
	अगर (tcon->ses->capabilities & CAP_LARGE_WRITE_X) अणु
		bytes_sent = min_t(स्थिर अचिन्हित पूर्णांक, CIFSMaxBufSize, count);
	पूर्ण अन्यथा अणु
		bytes_sent = (tcon->ses->server->maxBuf - MAX_CIFS_HDR_SIZE)
			 & ~0xFF;
	पूर्ण

	अगर (bytes_sent > count)
		bytes_sent = count;
	pSMB->DataOffset =
		cpu_to_le16(दुरत्व(काष्ठा smb_com_ग_लिखो_req, Data) - 4);
	अगर (buf)
		स_नकल(pSMB->Data, buf, bytes_sent);
	अन्यथा अगर (count != 0) अणु
		/* No buffer */
		cअगरs_buf_release(pSMB);
		वापस -EINVAL;
	पूर्ण /* अन्यथा setting file size with ग_लिखो of zero bytes */
	अगर (wct == 14)
		byte_count = bytes_sent + 1; /* pad */
	अन्यथा /* wct == 12 */
		byte_count = bytes_sent + 5; /* bigger pad, smaller smb hdr */

	pSMB->DataLengthLow = cpu_to_le16(bytes_sent & 0xFFFF);
	pSMB->DataLengthHigh = cpu_to_le16(bytes_sent >> 16);
	inc_rfc1001_len(pSMB, byte_count);

	अगर (wct == 14)
		pSMB->ByteCount = cpu_to_le16(byte_count);
	अन्यथा अणु /* old style ग_लिखो has byte count 4 bytes earlier
		  so 4 bytes pad  */
		काष्ठा smb_com_ग_लिखोx_req *pSMBW =
			(काष्ठा smb_com_ग_लिखोx_req *)pSMB;
		pSMBW->ByteCount = cpu_to_le16(byte_count);
	पूर्ण

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_ग_लिखोs);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in write = %d\n", rc);
	पूर्ण अन्यथा अणु
		*nbytes = le16_to_cpu(pSMBr->CountHigh);
		*nbytes = (*nbytes) << 16;
		*nbytes += le16_to_cpu(pSMBr->Count);

		/*
		 * Mask off high 16 bits when bytes written as वापसed by the
		 * server is greater than bytes requested by the client. Some
		 * OS/2 servers are known to set incorrect CountHigh values.
		 */
		अगर (*nbytes > count)
			*nbytes &= 0xFFFF;
	पूर्ण

	cअगरs_buf_release(pSMB);

	/* Note: On -EAGAIN error only caller can retry on handle based calls
		since file handle passed in no दीर्घer valid */

	वापस rc;
पूर्ण

व्योम
cअगरs_ग_लिखोdata_release(काष्ठा kref *refcount)
अणु
	काष्ठा cअगरs_ग_लिखोdata *wdata = container_of(refcount,
					काष्ठा cअगरs_ग_लिखोdata, refcount);
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	अगर (wdata->mr) अणु
		smbd_deरेजिस्टर_mr(wdata->mr);
		wdata->mr = शून्य;
	पूर्ण
#पूर्ण_अगर

	अगर (wdata->cfile)
		cअगरsFileInfo_put(wdata->cfile);

	kvमुक्त(wdata->pages);
	kमुक्त(wdata);
पूर्ण

/*
 * Write failed with a retryable error. Resend the ग_लिखो request. It's also
 * possible that the page was redirtied so re-clean the page.
 */
अटल व्योम
cअगरs_ग_लिखोv_requeue(काष्ठा cअगरs_ग_लिखोdata *wdata)
अणु
	पूर्णांक i, rc = 0;
	काष्ठा inode *inode = d_inode(wdata->cfile->dentry);
	काष्ठा TCP_Server_Info *server;
	अचिन्हित पूर्णांक rest_len;

	server = tlink_tcon(wdata->cfile->tlink)->ses->server;
	i = 0;
	rest_len = wdata->bytes;
	करो अणु
		काष्ठा cअगरs_ग_लिखोdata *wdata2;
		अचिन्हित पूर्णांक j, nr_pages, wsize, tailsz, cur_len;

		wsize = server->ops->wp_retry_size(inode);
		अगर (wsize < rest_len) अणु
			nr_pages = wsize / PAGE_SIZE;
			अगर (!nr_pages) अणु
				rc = -ENOTSUPP;
				अवरोध;
			पूर्ण
			cur_len = nr_pages * PAGE_SIZE;
			tailsz = PAGE_SIZE;
		पूर्ण अन्यथा अणु
			nr_pages = DIV_ROUND_UP(rest_len, PAGE_SIZE);
			cur_len = rest_len;
			tailsz = rest_len - (nr_pages - 1) * PAGE_SIZE;
		पूर्ण

		wdata2 = cअगरs_ग_लिखोdata_alloc(nr_pages, cअगरs_ग_लिखोv_complete);
		अगर (!wdata2) अणु
			rc = -ENOMEM;
			अवरोध;
		पूर्ण

		क्रम (j = 0; j < nr_pages; j++) अणु
			wdata2->pages[j] = wdata->pages[i + j];
			lock_page(wdata2->pages[j]);
			clear_page_dirty_क्रम_io(wdata2->pages[j]);
		पूर्ण

		wdata2->sync_mode = wdata->sync_mode;
		wdata2->nr_pages = nr_pages;
		wdata2->offset = page_offset(wdata2->pages[0]);
		wdata2->pagesz = PAGE_SIZE;
		wdata2->tailsz = tailsz;
		wdata2->bytes = cur_len;

		rc = cअगरs_get_writable_file(CIFS_I(inode), FIND_WR_ANY,
					    &wdata2->cfile);
		अगर (!wdata2->cfile) अणु
			cअगरs_dbg(VFS, "No writable handle to retry writepages rc=%d\n",
				 rc);
			अगर (!is_retryable_error(rc))
				rc = -EBADF;
		पूर्ण अन्यथा अणु
			wdata2->pid = wdata2->cfile->pid;
			rc = server->ops->async_ग_लिखोv(wdata2,
						       cअगरs_ग_लिखोdata_release);
		पूर्ण

		क्रम (j = 0; j < nr_pages; j++) अणु
			unlock_page(wdata2->pages[j]);
			अगर (rc != 0 && !is_retryable_error(rc)) अणु
				SetPageError(wdata2->pages[j]);
				end_page_ग_लिखोback(wdata2->pages[j]);
				put_page(wdata2->pages[j]);
			पूर्ण
		पूर्ण

		kref_put(&wdata2->refcount, cअगरs_ग_लिखोdata_release);
		अगर (rc) अणु
			अगर (is_retryable_error(rc))
				जारी;
			i += nr_pages;
			अवरोध;
		पूर्ण

		rest_len -= cur_len;
		i += nr_pages;
	पूर्ण जबतक (i < wdata->nr_pages);

	/* cleanup reमुख्यing pages from the original wdata */
	क्रम (; i < wdata->nr_pages; i++) अणु
		SetPageError(wdata->pages[i]);
		end_page_ग_लिखोback(wdata->pages[i]);
		put_page(wdata->pages[i]);
	पूर्ण

	अगर (rc != 0 && !is_retryable_error(rc))
		mapping_set_error(inode->i_mapping, rc);
	kref_put(&wdata->refcount, cअगरs_ग_लिखोdata_release);
पूर्ण

व्योम
cअगरs_ग_लिखोv_complete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cअगरs_ग_लिखोdata *wdata = container_of(work,
						काष्ठा cअगरs_ग_लिखोdata, work);
	काष्ठा inode *inode = d_inode(wdata->cfile->dentry);
	पूर्णांक i = 0;

	अगर (wdata->result == 0) अणु
		spin_lock(&inode->i_lock);
		cअगरs_update_eof(CIFS_I(inode), wdata->offset, wdata->bytes);
		spin_unlock(&inode->i_lock);
		cअगरs_stats_bytes_written(tlink_tcon(wdata->cfile->tlink),
					 wdata->bytes);
	पूर्ण अन्यथा अगर (wdata->sync_mode == WB_SYNC_ALL && wdata->result == -EAGAIN)
		वापस cअगरs_ग_लिखोv_requeue(wdata);

	क्रम (i = 0; i < wdata->nr_pages; i++) अणु
		काष्ठा page *page = wdata->pages[i];
		अगर (wdata->result == -EAGAIN)
			__set_page_dirty_nobuffers(page);
		अन्यथा अगर (wdata->result < 0)
			SetPageError(page);
		end_page_ग_लिखोback(page);
		put_page(page);
	पूर्ण
	अगर (wdata->result != -EAGAIN)
		mapping_set_error(inode->i_mapping, wdata->result);
	kref_put(&wdata->refcount, cअगरs_ग_लिखोdata_release);
पूर्ण

काष्ठा cअगरs_ग_लिखोdata *
cअगरs_ग_लिखोdata_alloc(अचिन्हित पूर्णांक nr_pages, work_func_t complete)
अणु
	काष्ठा page **pages =
		kसुस्मृति(nr_pages, माप(काष्ठा page *), GFP_NOFS);
	अगर (pages)
		वापस cअगरs_ग_लिखोdata_direct_alloc(pages, complete);

	वापस शून्य;
पूर्ण

काष्ठा cअगरs_ग_लिखोdata *
cअगरs_ग_लिखोdata_direct_alloc(काष्ठा page **pages, work_func_t complete)
अणु
	काष्ठा cअगरs_ग_लिखोdata *wdata;

	wdata = kzalloc(माप(*wdata), GFP_NOFS);
	अगर (wdata != शून्य) अणु
		wdata->pages = pages;
		kref_init(&wdata->refcount);
		INIT_LIST_HEAD(&wdata->list);
		init_completion(&wdata->करोne);
		INIT_WORK(&wdata->work, complete);
	पूर्ण
	वापस wdata;
पूर्ण

/*
 * Check the mid_state and signature on received buffer (अगर any), and queue the
 * workqueue completion task.
 */
अटल व्योम
cअगरs_ग_लिखोv_callback(काष्ठा mid_q_entry *mid)
अणु
	काष्ठा cअगरs_ग_लिखोdata *wdata = mid->callback_data;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(wdata->cfile->tlink);
	अचिन्हित पूर्णांक written;
	WRITE_RSP *smb = (WRITE_RSP *)mid->resp_buf;
	काष्ठा cअगरs_credits credits = अणु .value = 1, .instance = 0 पूर्ण;

	चयन (mid->mid_state) अणु
	हाल MID_RESPONSE_RECEIVED:
		wdata->result = cअगरs_check_receive(mid, tcon->ses->server, 0);
		अगर (wdata->result != 0)
			अवरोध;

		written = le16_to_cpu(smb->CountHigh);
		written <<= 16;
		written += le16_to_cpu(smb->Count);
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
	शेष:
		wdata->result = -EIO;
		अवरोध;
	पूर्ण

	queue_work(cअगरsiod_wq, &wdata->work);
	DeleteMidQEntry(mid);
	add_credits(tcon->ses->server, &credits, 0);
पूर्ण

/* cअगरs_async_ग_लिखोv - send an async ग_लिखो, and set up mid to handle result */
पूर्णांक
cअगरs_async_ग_लिखोv(काष्ठा cअगरs_ग_लिखोdata *wdata,
		  व्योम (*release)(काष्ठा kref *kref))
अणु
	पूर्णांक rc = -EACCES;
	WRITE_REQ *smb = शून्य;
	पूर्णांक wct;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(wdata->cfile->tlink);
	काष्ठा kvec iov[2];
	काष्ठा smb_rqst rqst = अणु पूर्ण;

	अगर (tcon->ses->capabilities & CAP_LARGE_खाताS) अणु
		wct = 14;
	पूर्ण अन्यथा अणु
		wct = 12;
		अगर (wdata->offset >> 32 > 0) अणु
			/* can not handle big offset क्रम old srv */
			वापस -EIO;
		पूर्ण
	पूर्ण

	rc = small_smb_init(SMB_COM_WRITE_ANDX, wct, tcon, (व्योम **)&smb);
	अगर (rc)
		जाओ async_ग_लिखोv_out;

	smb->hdr.Pid = cpu_to_le16((__u16)wdata->pid);
	smb->hdr.PidHigh = cpu_to_le16((__u16)(wdata->pid >> 16));

	smb->AndXCommand = 0xFF;	/* none */
	smb->Fid = wdata->cfile->fid.netfid;
	smb->OffsetLow = cpu_to_le32(wdata->offset & 0xFFFFFFFF);
	अगर (wct == 14)
		smb->OffsetHigh = cpu_to_le32(wdata->offset >> 32);
	smb->Reserved = 0xFFFFFFFF;
	smb->WriteMode = 0;
	smb->Reमुख्यing = 0;

	smb->DataOffset =
	    cpu_to_le16(दुरत्व(काष्ठा smb_com_ग_लिखो_req, Data) - 4);

	/* 4 क्रम RFC1001 length + 1 क्रम BCC */
	iov[0].iov_len = 4;
	iov[0].iov_base = smb;
	iov[1].iov_len = get_rfc1002_length(smb) + 1;
	iov[1].iov_base = (अक्षर *)smb + 4;

	rqst.rq_iov = iov;
	rqst.rq_nvec = 2;
	rqst.rq_pages = wdata->pages;
	rqst.rq_offset = wdata->page_offset;
	rqst.rq_npages = wdata->nr_pages;
	rqst.rq_pagesz = wdata->pagesz;
	rqst.rq_tailsz = wdata->tailsz;

	cअगरs_dbg(FYI, "async write at %llu %u bytes\n",
		 wdata->offset, wdata->bytes);

	smb->DataLengthLow = cpu_to_le16(wdata->bytes & 0xFFFF);
	smb->DataLengthHigh = cpu_to_le16(wdata->bytes >> 16);

	अगर (wct == 14) अणु
		inc_rfc1001_len(&smb->hdr, wdata->bytes + 1);
		put_bcc(wdata->bytes + 1, &smb->hdr);
	पूर्ण अन्यथा अणु
		/* wct == 12 */
		काष्ठा smb_com_ग_लिखोx_req *smbw =
				(काष्ठा smb_com_ग_लिखोx_req *)smb;
		inc_rfc1001_len(&smbw->hdr, wdata->bytes + 5);
		put_bcc(wdata->bytes + 5, &smbw->hdr);
		iov[1].iov_len += 4; /* pad bigger by four bytes */
	पूर्ण

	kref_get(&wdata->refcount);
	rc = cअगरs_call_async(tcon->ses->server, &rqst, शून्य,
			     cअगरs_ग_लिखोv_callback, शून्य, wdata, 0, शून्य);

	अगर (rc == 0)
		cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_ग_लिखोs);
	अन्यथा
		kref_put(&wdata->refcount, release);

async_ग_लिखोv_out:
	cअगरs_small_buf_release(smb);
	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBWrite2(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_io_parms *io_parms,
	      अचिन्हित पूर्णांक *nbytes, काष्ठा kvec *iov, पूर्णांक n_vec)
अणु
	पूर्णांक rc;
	WRITE_REQ *pSMB = शून्य;
	पूर्णांक wct;
	पूर्णांक smb_hdr_len;
	पूर्णांक resp_buf_type = 0;
	__u32 pid = io_parms->pid;
	__u16 netfid = io_parms->netfid;
	__u64 offset = io_parms->offset;
	काष्ठा cअगरs_tcon *tcon = io_parms->tcon;
	अचिन्हित पूर्णांक count = io_parms->length;
	काष्ठा kvec rsp_iov;

	*nbytes = 0;

	cअगरs_dbg(FYI, "write2 at %lld %d bytes\n", (दीर्घ दीर्घ)offset, count);

	अगर (tcon->ses->capabilities & CAP_LARGE_खाताS) अणु
		wct = 14;
	पूर्ण अन्यथा अणु
		wct = 12;
		अगर ((offset >> 32) > 0) अणु
			/* can not handle big offset क्रम old srv */
			वापस -EIO;
		पूर्ण
	पूर्ण
	rc = small_smb_init(SMB_COM_WRITE_ANDX, wct, tcon, (व्योम **) &pSMB);
	अगर (rc)
		वापस rc;

	pSMB->hdr.Pid = cpu_to_le16((__u16)pid);
	pSMB->hdr.PidHigh = cpu_to_le16((__u16)(pid >> 16));

	/* tcon and ses poपूर्णांकer are checked in smb_init */
	अगर (tcon->ses->server == शून्य)
		वापस -ECONNABORTED;

	pSMB->AndXCommand = 0xFF;	/* none */
	pSMB->Fid = netfid;
	pSMB->OffsetLow = cpu_to_le32(offset & 0xFFFFFFFF);
	अगर (wct == 14)
		pSMB->OffsetHigh = cpu_to_le32(offset >> 32);
	pSMB->Reserved = 0xFFFFFFFF;
	pSMB->WriteMode = 0;
	pSMB->Reमुख्यing = 0;

	pSMB->DataOffset =
	    cpu_to_le16(दुरत्व(काष्ठा smb_com_ग_लिखो_req, Data) - 4);

	pSMB->DataLengthLow = cpu_to_le16(count & 0xFFFF);
	pSMB->DataLengthHigh = cpu_to_le16(count >> 16);
	/* header + 1 byte pad */
	smb_hdr_len = be32_to_cpu(pSMB->hdr.smb_buf_length) + 1;
	अगर (wct == 14)
		inc_rfc1001_len(pSMB, count + 1);
	अन्यथा /* wct == 12 */
		inc_rfc1001_len(pSMB, count + 5); /* smb data starts later */
	अगर (wct == 14)
		pSMB->ByteCount = cpu_to_le16(count + 1);
	अन्यथा /* wct == 12 */ /* bigger pad, smaller smb hdr, keep offset ok */ अणु
		काष्ठा smb_com_ग_लिखोx_req *pSMBW =
				(काष्ठा smb_com_ग_लिखोx_req *)pSMB;
		pSMBW->ByteCount = cpu_to_le16(count + 5);
	पूर्ण
	iov[0].iov_base = pSMB;
	अगर (wct == 14)
		iov[0].iov_len = smb_hdr_len + 4;
	अन्यथा /* wct == 12 pad bigger by four bytes */
		iov[0].iov_len = smb_hdr_len + 8;

	rc = SendReceive2(xid, tcon->ses, iov, n_vec + 1, &resp_buf_type, 0,
			  &rsp_iov);
	cअगरs_small_buf_release(pSMB);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_ग_लिखोs);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error Write2 = %d\n", rc);
	पूर्ण अन्यथा अगर (resp_buf_type == 0) अणु
		/* presumably this can not happen, but best to be safe */
		rc = -EIO;
	पूर्ण अन्यथा अणु
		WRITE_RSP *pSMBr = (WRITE_RSP *)rsp_iov.iov_base;
		*nbytes = le16_to_cpu(pSMBr->CountHigh);
		*nbytes = (*nbytes) << 16;
		*nbytes += le16_to_cpu(pSMBr->Count);

		/*
		 * Mask off high 16 bits when bytes written as वापसed by the
		 * server is greater than bytes requested by the client. OS/2
		 * servers are known to set incorrect CountHigh values.
		 */
		अगर (*nbytes > count)
			*nbytes &= 0xFFFF;
	पूर्ण

	मुक्त_rsp_buf(resp_buf_type, rsp_iov.iov_base);

	/* Note: On -EAGAIN error only caller can retry on handle based calls
		since file handle passed in no दीर्घer valid */

	वापस rc;
पूर्ण

पूर्णांक cअगरs_lockv(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	       स्थिर __u16 netfid, स्थिर __u8 lock_type, स्थिर __u32 num_unlock,
	       स्थिर __u32 num_lock, LOCKING_ANDX_RANGE *buf)
अणु
	पूर्णांक rc = 0;
	LOCK_REQ *pSMB = शून्य;
	काष्ठा kvec iov[2];
	काष्ठा kvec rsp_iov;
	पूर्णांक resp_buf_type;
	__u16 count;

	cअगरs_dbg(FYI, "cifs_lockv num lock %d num unlock %d\n",
		 num_lock, num_unlock);

	rc = small_smb_init(SMB_COM_LOCKING_ANDX, 8, tcon, (व्योम **) &pSMB);
	अगर (rc)
		वापस rc;

	pSMB->Timeout = 0;
	pSMB->NumberOfLocks = cpu_to_le16(num_lock);
	pSMB->NumberOfUnlocks = cpu_to_le16(num_unlock);
	pSMB->LockType = lock_type;
	pSMB->AndXCommand = 0xFF; /* none */
	pSMB->Fid = netfid; /* netfid stays le */

	count = (num_unlock + num_lock) * माप(LOCKING_ANDX_RANGE);
	inc_rfc1001_len(pSMB, count);
	pSMB->ByteCount = cpu_to_le16(count);

	iov[0].iov_base = (अक्षर *)pSMB;
	iov[0].iov_len = be32_to_cpu(pSMB->hdr.smb_buf_length) + 4 -
			 (num_unlock + num_lock) * माप(LOCKING_ANDX_RANGE);
	iov[1].iov_base = (अक्षर *)buf;
	iov[1].iov_len = (num_unlock + num_lock) * माप(LOCKING_ANDX_RANGE);

	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_locks);
	rc = SendReceive2(xid, tcon->ses, iov, 2, &resp_buf_type,
			  CIFS_NO_RSP_BUF, &rsp_iov);
	cअगरs_small_buf_release(pSMB);
	अगर (rc)
		cअगरs_dbg(FYI, "Send error in cifs_lockv = %d\n", rc);

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBLock(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	    स्थिर __u16 smb_file_id, स्थिर __u32 netpid, स्थिर __u64 len,
	    स्थिर __u64 offset, स्थिर __u32 numUnlock,
	    स्थिर __u32 numLock, स्थिर __u8 lockType,
	    स्थिर bool रुकोFlag, स्थिर __u8 oplock_level)
अणु
	पूर्णांक rc = 0;
	LOCK_REQ *pSMB = शून्य;
/*	LOCK_RSP *pSMBr = शून्य; */ /* No response data other than rc to parse */
	पूर्णांक bytes_वापसed;
	पूर्णांक flags = 0;
	__u16 count;

	cअगरs_dbg(FYI, "CIFSSMBLock timeout %d numLock %d\n",
		 (पूर्णांक)रुकोFlag, numLock);
	rc = small_smb_init(SMB_COM_LOCKING_ANDX, 8, tcon, (व्योम **) &pSMB);

	अगर (rc)
		वापस rc;

	अगर (lockType == LOCKING_ANDX_OPLOCK_RELEASE) अणु
		/* no response expected */
		flags = CIFS_NO_SRV_RSP | CIFS_NON_BLOCKING | CIFS_OBREAK_OP;
		pSMB->Timeout = 0;
	पूर्ण अन्यथा अगर (रुकोFlag) अणु
		flags = CIFS_BLOCKING_OP; /* blocking operation, no समयout */
		pSMB->Timeout = cpu_to_le32(-1);/* blocking - करो not समय out */
	पूर्ण अन्यथा अणु
		pSMB->Timeout = 0;
	पूर्ण

	pSMB->NumberOfLocks = cpu_to_le16(numLock);
	pSMB->NumberOfUnlocks = cpu_to_le16(numUnlock);
	pSMB->LockType = lockType;
	pSMB->OplockLevel = oplock_level;
	pSMB->AndXCommand = 0xFF;	/* none */
	pSMB->Fid = smb_file_id; /* netfid stays le */

	अगर ((numLock != 0) || (numUnlock != 0)) अणु
		pSMB->Locks[0].Pid = cpu_to_le16(netpid);
		/* BB where to store pid high? */
		pSMB->Locks[0].LengthLow = cpu_to_le32((u32)len);
		pSMB->Locks[0].LengthHigh = cpu_to_le32((u32)(len>>32));
		pSMB->Locks[0].OffsetLow = cpu_to_le32((u32)offset);
		pSMB->Locks[0].OffsetHigh = cpu_to_le32((u32)(offset>>32));
		count = माप(LOCKING_ANDX_RANGE);
	पूर्ण अन्यथा अणु
		/* oplock अवरोध */
		count = 0;
	पूर्ण
	inc_rfc1001_len(pSMB, count);
	pSMB->ByteCount = cpu_to_le16(count);

	अगर (रुकोFlag)
		rc = SendReceiveBlockingLock(xid, tcon, (काष्ठा smb_hdr *) pSMB,
			(काष्ठा smb_hdr *) pSMB, &bytes_वापसed);
	अन्यथा
		rc = SendReceiveNoRsp(xid, tcon->ses, (अक्षर *)pSMB, flags);
	cअगरs_small_buf_release(pSMB);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_locks);
	अगर (rc)
		cअगरs_dbg(FYI, "Send error in Lock = %d\n", rc);

	/* Note: On -EAGAIN error only caller can retry on handle based calls
	since file handle passed in no दीर्घer valid */
	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBPosixLock(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		स्थिर __u16 smb_file_id, स्थिर __u32 netpid,
		स्थिर loff_t start_offset, स्थिर __u64 len,
		काष्ठा file_lock *pLockData, स्थिर __u16 lock_type,
		स्थिर bool रुकोFlag)
अणु
	काष्ठा smb_com_transaction2_sfi_req *pSMB  = शून्य;
	काष्ठा smb_com_transaction2_sfi_rsp *pSMBr = शून्य;
	काष्ठा cअगरs_posix_lock *parm_data;
	पूर्णांक rc = 0;
	पूर्णांक समयout = 0;
	पूर्णांक bytes_वापसed = 0;
	पूर्णांक resp_buf_type = 0;
	__u16 params, param_offset, offset, byte_count, count;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov;

	cअगरs_dbg(FYI, "Posix Lock\n");

	rc = small_smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB);

	अगर (rc)
		वापस rc;

	pSMBr = (काष्ठा smb_com_transaction2_sfi_rsp *)pSMB;

	params = 6;
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_sfi_req, Fid) - 4;
	offset = param_offset + params;

	count = माप(काष्ठा cअगरs_posix_lock);
	pSMB->MaxParameterCount = cpu_to_le16(2);
	pSMB->MaxDataCount = cpu_to_le16(1000); /* BB find max SMB from sess */
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	अगर (pLockData)
		pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_खाता_INFORMATION);
	अन्यथा
		pSMB->SubCommand = cpu_to_le16(TRANS2_SET_खाता_INFORMATION);
	byte_count = 3 /* pad */  + params + count;
	pSMB->DataCount = cpu_to_le16(count);
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	parm_data = (काष्ठा cअगरs_posix_lock *)
			(((अक्षर *) &pSMB->hdr.Protocol) + offset);

	parm_data->lock_type = cpu_to_le16(lock_type);
	अगर (रुकोFlag) अणु
		समयout = CIFS_BLOCKING_OP; /* blocking operation, no समयout */
		parm_data->lock_flags = cpu_to_le16(1);
		pSMB->Timeout = cpu_to_le32(-1);
	पूर्ण अन्यथा
		pSMB->Timeout = 0;

	parm_data->pid = cpu_to_le32(netpid);
	parm_data->start = cpu_to_le64(start_offset);
	parm_data->length = cpu_to_le64(len);  /* normalize negative numbers */

	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->Fid = smb_file_id;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_SET_POSIX_LOCK);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);
	अगर (रुकोFlag) अणु
		rc = SendReceiveBlockingLock(xid, tcon, (काष्ठा smb_hdr *) pSMB,
			(काष्ठा smb_hdr *) pSMBr, &bytes_वापसed);
	पूर्ण अन्यथा अणु
		iov[0].iov_base = (अक्षर *)pSMB;
		iov[0].iov_len = be32_to_cpu(pSMB->hdr.smb_buf_length) + 4;
		rc = SendReceive2(xid, tcon->ses, iov, 1 /* num iovecs */,
				&resp_buf_type, समयout, &rsp_iov);
		pSMBr = (काष्ठा smb_com_transaction2_sfi_rsp *)rsp_iov.iov_base;
	पूर्ण
	cअगरs_small_buf_release(pSMB);

	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in Posix Lock = %d\n", rc);
	पूर्ण अन्यथा अगर (pLockData) अणु
		/* lock काष्ठाure can be वापसed on get */
		__u16 data_offset;
		__u16 data_count;
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

		अगर (rc || get_bcc(&pSMBr->hdr) < माप(*parm_data)) अणु
			rc = -EIO;      /* bad smb */
			जाओ plk_err_निकास;
		पूर्ण
		data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
		data_count  = le16_to_cpu(pSMBr->t2.DataCount);
		अगर (data_count < माप(काष्ठा cअगरs_posix_lock)) अणु
			rc = -EIO;
			जाओ plk_err_निकास;
		पूर्ण
		parm_data = (काष्ठा cअगरs_posix_lock *)
			((अक्षर *)&pSMBr->hdr.Protocol + data_offset);
		अगर (parm_data->lock_type == cpu_to_le16(CIFS_UNLCK))
			pLockData->fl_type = F_UNLCK;
		अन्यथा अणु
			अगर (parm_data->lock_type ==
					cpu_to_le16(CIFS_RDLCK))
				pLockData->fl_type = F_RDLCK;
			अन्यथा अगर (parm_data->lock_type ==
					cpu_to_le16(CIFS_WRLCK))
				pLockData->fl_type = F_WRLCK;

			pLockData->fl_start = le64_to_cpu(parm_data->start);
			pLockData->fl_end = pLockData->fl_start +
					le64_to_cpu(parm_data->length) - 1;
			pLockData->fl_pid = -le32_to_cpu(parm_data->pid);
		पूर्ण
	पूर्ण

plk_err_निकास:
	मुक्त_rsp_buf(resp_buf_type, rsp_iov.iov_base);

	/* Note: On -EAGAIN error only caller can retry on handle based calls
	   since file handle passed in no दीर्घer valid */

	वापस rc;
पूर्ण


पूर्णांक
CIFSSMBClose(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, पूर्णांक smb_file_id)
अणु
	पूर्णांक rc = 0;
	CLOSE_REQ *pSMB = शून्य;
	cअगरs_dbg(FYI, "In CIFSSMBClose\n");

/* करो not retry on dead session on बंद */
	rc = small_smb_init(SMB_COM_CLOSE, 3, tcon, (व्योम **) &pSMB);
	अगर (rc == -EAGAIN)
		वापस 0;
	अगर (rc)
		वापस rc;

	pSMB->FileID = (__u16) smb_file_id;
	pSMB->LastWriteTime = 0xFFFFFFFF;
	pSMB->ByteCount = 0;
	rc = SendReceiveNoRsp(xid, tcon->ses, (अक्षर *) pSMB, 0);
	cअगरs_small_buf_release(pSMB);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_बंदs);
	अगर (rc) अणु
		अगर (rc != -EINTR) अणु
			/* EINTR is expected when user ctl-c to समाप्त app */
			cअगरs_dbg(VFS, "Send error in Close = %d\n", rc);
		पूर्ण
	पूर्ण

	/* Since session is dead, file will be बंदd on server alपढ़ोy */
	अगर (rc == -EAGAIN)
		rc = 0;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBFlush(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, पूर्णांक smb_file_id)
अणु
	पूर्णांक rc = 0;
	FLUSH_REQ *pSMB = शून्य;
	cअगरs_dbg(FYI, "In CIFSSMBFlush\n");

	rc = small_smb_init(SMB_COM_FLUSH, 1, tcon, (व्योम **) &pSMB);
	अगर (rc)
		वापस rc;

	pSMB->FileID = (__u16) smb_file_id;
	pSMB->ByteCount = 0;
	rc = SendReceiveNoRsp(xid, tcon->ses, (अक्षर *) pSMB, 0);
	cअगरs_small_buf_release(pSMB);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_flushes);
	अगर (rc)
		cअगरs_dbg(VFS, "Send error in Flush = %d\n", rc);

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBRename(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	      स्थिर अक्षर *from_name, स्थिर अक्षर *to_name,
	      काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	पूर्णांक rc = 0;
	RENAME_REQ *pSMB = शून्य;
	RENAME_RSP *pSMBr = शून्य;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len, name_len2;
	__u16 count;
	पूर्णांक remap = cअगरs_remap(cअगरs_sb);

	cअगरs_dbg(FYI, "In CIFSSMBRename\n");
नामRetry:
	rc = smb_init(SMB_COM_RENAME, 1, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	pSMB->BufferFormat = 0x04;
	pSMB->SearchAttributes =
	    cpu_to_le16(ATTR_READONLY | ATTR_HIDDEN | ATTR_SYSTEM |
			ATTR_सूचीECTORY);

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len = cअगरsConvertToUTF16((__le16 *) pSMB->OldFileName,
					      from_name, PATH_MAX,
					      cअगरs_sb->local_nls, remap);
		name_len++;	/* trailing null */
		name_len *= 2;
		pSMB->OldFileName[name_len] = 0x04;	/* pad */
	/* protocol requires ASCII signature byte on Unicode string */
		pSMB->OldFileName[name_len + 1] = 0x00;
		name_len2 =
		    cअगरsConvertToUTF16((__le16 *)&pSMB->OldFileName[name_len+2],
				       to_name, PATH_MAX, cअगरs_sb->local_nls,
				       remap);
		name_len2 += 1 /* trailing null */  + 1 /* Signature word */ ;
		name_len2 *= 2;	/* convert to bytes */
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->OldFileName, from_name);
		name_len2 = copy_path_name(pSMB->OldFileName+name_len+1, to_name);
		pSMB->OldFileName[name_len] = 0x04;  /* 2nd buffer क्रमmat */
		name_len2++;	/* signature byte */
	पूर्ण

	count = 1 /* 1st signature byte */  + name_len + name_len2;
	inc_rfc1001_len(pSMB, count);
	pSMB->ByteCount = cpu_to_le16(count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_नामs);
	अगर (rc)
		cअगरs_dbg(FYI, "Send error in rename = %d\n", rc);

	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ नामRetry;

	वापस rc;
पूर्ण

पूर्णांक CIFSSMBRenameOpenFile(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *pTcon,
		पूर्णांक netfid, स्थिर अक्षर *target_name,
		स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
	काष्ठा smb_com_transaction2_sfi_req *pSMB  = शून्य;
	काष्ठा smb_com_transaction2_sfi_rsp *pSMBr = शून्य;
	काष्ठा set_file_नाम *नाम_info;
	अक्षर *data_offset;
	अक्षर dummy_string[30];
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	पूर्णांक len_of_str;
	__u16 params, param_offset, offset, count, byte_count;

	cअगरs_dbg(FYI, "Rename to File by handle\n");
	rc = smb_init(SMB_COM_TRANSACTION2, 15, pTcon, (व्योम **) &pSMB,
			(व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	params = 6;
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_sfi_req, Fid) - 4;
	offset = param_offset + params;

	data_offset = (अक्षर *) (&pSMB->hdr.Protocol) + offset;
	नाम_info = (काष्ठा set_file_नाम *) data_offset;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	pSMB->MaxDataCount = cpu_to_le16(1000); /* BB find max SMB from sess */
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_खाता_INFORMATION);
	byte_count = 3 /* pad */  + params;
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->DataOffset = cpu_to_le16(offset);
	/* स्थिरruct अक्रमom name ".cifs_tmp<inodenum><mid>" */
	नाम_info->overग_लिखो = cpu_to_le32(1);
	नाम_info->root_fid  = 0;
	/* unicode only call */
	अगर (target_name == शून्य) अणु
		प्र_लिखो(dummy_string, "cifs%x", pSMB->hdr.Mid);
		len_of_str =
			cअगरsConvertToUTF16((__le16 *)नाम_info->target_name,
					dummy_string, 24, nls_codepage, remap);
	पूर्ण अन्यथा अणु
		len_of_str =
			cअगरsConvertToUTF16((__le16 *)नाम_info->target_name,
					target_name, PATH_MAX, nls_codepage,
					remap);
	पूर्ण
	नाम_info->target_name_len = cpu_to_le32(2 * len_of_str);
	count = 12 /* माप(काष्ठा set_file_नाम) */ + (2 * len_of_str);
	byte_count += count;
	pSMB->DataCount = cpu_to_le16(count);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->Fid = netfid;
	pSMB->Inक्रमmationLevel =
		cpu_to_le16(SMB_SET_खाता_RENAME_INFORMATION);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);
	rc = SendReceive(xid, pTcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&pTcon->stats.cअगरs_stats.num_t2नामs);
	अगर (rc)
		cअगरs_dbg(FYI, "Send error in Rename (by file handle) = %d\n",
			 rc);

	cअगरs_buf_release(pSMB);

	/* Note: On -EAGAIN error only caller can retry on handle based calls
		since file handle passed in no दीर्घer valid */

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBCopy(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	    स्थिर अक्षर *fromName, स्थिर __u16 target_tid, स्थिर अक्षर *toName,
	    स्थिर पूर्णांक flags, स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
	पूर्णांक rc = 0;
	COPY_REQ *pSMB = शून्य;
	COPY_RSP *pSMBr = शून्य;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len, name_len2;
	__u16 count;

	cअगरs_dbg(FYI, "In CIFSSMBCopy\n");
copyRetry:
	rc = smb_init(SMB_COM_COPY, 1, tcon, (व्योम **) &pSMB,
			(व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	pSMB->BufferFormat = 0x04;
	pSMB->Tid2 = target_tid;

	pSMB->Flags = cpu_to_le16(flags & COPY_TREE);

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len = cअगरsConvertToUTF16((__le16 *) pSMB->OldFileName,
					      fromName, PATH_MAX, nls_codepage,
					      remap);
		name_len++;     /* trailing null */
		name_len *= 2;
		pSMB->OldFileName[name_len] = 0x04;     /* pad */
		/* protocol requires ASCII signature byte on Unicode string */
		pSMB->OldFileName[name_len + 1] = 0x00;
		name_len2 =
		    cअगरsConvertToUTF16((__le16 *)&pSMB->OldFileName[name_len+2],
				       toName, PATH_MAX, nls_codepage, remap);
		name_len2 += 1 /* trailing null */  + 1 /* Signature word */ ;
		name_len2 *= 2; /* convert to bytes */
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->OldFileName, fromName);
		pSMB->OldFileName[name_len] = 0x04;  /* 2nd buffer क्रमmat */
		name_len2 = copy_path_name(pSMB->OldFileName+name_len+1, toName);
		name_len2++;    /* signature byte */
	पूर्ण

	count = 1 /* 1st signature byte */  + name_len + name_len2;
	inc_rfc1001_len(pSMB, count);
	pSMB->ByteCount = cpu_to_le16(count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
		(काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in copy = %d with %d files copied\n",
			 rc, le16_to_cpu(pSMBr->CopyCount));
	पूर्ण
	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ copyRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSUnixCreateSymLink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		      स्थिर अक्षर *fromName, स्थिर अक्षर *toName,
		      स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
	TRANSACTION2_SPI_REQ *pSMB = शून्य;
	TRANSACTION2_SPI_RSP *pSMBr = शून्य;
	अक्षर *data_offset;
	पूर्णांक name_len;
	पूर्णांक name_len_target;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, param_offset, offset, byte_count;

	cअगरs_dbg(FYI, "In Symlink Unix style\n");
createSymLinkRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->FileName, fromName,
				/* find define क्रम this maxpathcomponent */
					PATH_MAX, nls_codepage, remap);
		name_len++;	/* trailing null */
		name_len *= 2;

	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, fromName);
	पूर्ण
	params = 6 + name_len;
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_spi_req,
				Inक्रमmationLevel) - 4;
	offset = param_offset + params;

	data_offset = (अक्षर *) (&pSMB->hdr.Protocol) + offset;
	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len_target =
		    cअगरsConvertToUTF16((__le16 *) data_offset, toName,
				/* find define क्रम this maxpathcomponent */
					PATH_MAX, nls_codepage, remap);
		name_len_target++;	/* trailing null */
		name_len_target *= 2;
	पूर्ण अन्यथा अणु
		name_len_target = copy_path_name(data_offset, toName);
	पूर्ण

	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find exact max on data count below from sess */
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_PATH_INFORMATION);
	byte_count = 3 /* pad */  + params + name_len_target;
	pSMB->DataCount = cpu_to_le16(name_len_target);
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_SET_खाता_UNIX_LINK);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_symlinks);
	अगर (rc)
		cअगरs_dbg(FYI, "Send error in SetPathInfo create symlink = %d\n",
			 rc);

	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ createSymLinkRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSUnixCreateHardLink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		       स्थिर अक्षर *fromName, स्थिर अक्षर *toName,
		       स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
	TRANSACTION2_SPI_REQ *pSMB = शून्य;
	TRANSACTION2_SPI_RSP *pSMBr = शून्य;
	अक्षर *data_offset;
	पूर्णांक name_len;
	पूर्णांक name_len_target;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, param_offset, offset, byte_count;

	cअगरs_dbg(FYI, "In Create Hard link Unix style\n");
createHardLinkRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len = cअगरsConvertToUTF16((__le16 *) pSMB->FileName, toName,
					      PATH_MAX, nls_codepage, remap);
		name_len++;	/* trailing null */
		name_len *= 2;

	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, toName);
	पूर्ण
	params = 6 + name_len;
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_spi_req,
				Inक्रमmationLevel) - 4;
	offset = param_offset + params;

	data_offset = (अक्षर *) (&pSMB->hdr.Protocol) + offset;
	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len_target =
		    cअगरsConvertToUTF16((__le16 *) data_offset, fromName,
				       PATH_MAX, nls_codepage, remap);
		name_len_target++;	/* trailing null */
		name_len_target *= 2;
	पूर्ण अन्यथा अणु
		name_len_target = copy_path_name(data_offset, fromName);
	पूर्ण

	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find exact max on data count below from sess*/
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_PATH_INFORMATION);
	byte_count = 3 /* pad */  + params + name_len_target;
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->DataCount = cpu_to_le16(name_len_target);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_SET_खाता_UNIX_HLINK);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_hardlinks);
	अगर (rc)
		cअगरs_dbg(FYI, "Send error in SetPathInfo (hard link) = %d\n",
			 rc);

	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ createHardLinkRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSCreateHardLink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   स्थिर अक्षर *from_name, स्थिर अक्षर *to_name,
		   काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	पूर्णांक rc = 0;
	NT_RENAME_REQ *pSMB = शून्य;
	RENAME_RSP *pSMBr = शून्य;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len, name_len2;
	__u16 count;
	पूर्णांक remap = cअगरs_remap(cअगरs_sb);

	cअगरs_dbg(FYI, "In CIFSCreateHardLink\n");
winCreateHardLinkRetry:

	rc = smb_init(SMB_COM_NT_RENAME, 4, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	pSMB->SearchAttributes =
	    cpu_to_le16(ATTR_READONLY | ATTR_HIDDEN | ATTR_SYSTEM |
			ATTR_सूचीECTORY);
	pSMB->Flags = cpu_to_le16(CREATE_HARD_LINK);
	pSMB->ClusterCount = 0;

	pSMB->BufferFormat = 0x04;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->OldFileName, from_name,
				       PATH_MAX, cअगरs_sb->local_nls, remap);
		name_len++;	/* trailing null */
		name_len *= 2;

		/* protocol specअगरies ASCII buffer क्रमmat (0x04) क्रम unicode */
		pSMB->OldFileName[name_len] = 0x04;
		pSMB->OldFileName[name_len + 1] = 0x00; /* pad */
		name_len2 =
		    cअगरsConvertToUTF16((__le16 *)&pSMB->OldFileName[name_len+2],
				       to_name, PATH_MAX, cअगरs_sb->local_nls,
				       remap);
		name_len2 += 1 /* trailing null */  + 1 /* Signature word */ ;
		name_len2 *= 2;	/* convert to bytes */
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->OldFileName, from_name);
		pSMB->OldFileName[name_len] = 0x04;	/* 2nd buffer क्रमmat */
		name_len2 = copy_path_name(pSMB->OldFileName+name_len+1, to_name);
		name_len2++;	/* signature byte */
	पूर्ण

	count = 1 /* string type byte */  + name_len + name_len2;
	inc_rfc1001_len(pSMB, count);
	pSMB->ByteCount = cpu_to_le16(count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_hardlinks);
	अगर (rc)
		cअगरs_dbg(FYI, "Send error in hard link (NT rename) = %d\n", rc);

	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ winCreateHardLinkRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBUnixQuerySymLink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर अचिन्हित अक्षर *searchName, अक्षर **symlinkinfo,
			स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
/* SMB_QUERY_खाता_UNIX_LINK */
	TRANSACTION2_QPI_REQ *pSMB = शून्य;
	TRANSACTION2_QPI_RSP *pSMBr = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len;
	__u16 params, byte_count;
	अक्षर *data_start;

	cअगरs_dbg(FYI, "In QPathSymLinkInfo (Unix) for path %s\n", searchName);

querySymLinkRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
			cअगरsConvertToUTF16((__le16 *) pSMB->FileName,
					   searchName, PATH_MAX, nls_codepage,
					   remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, searchName);
	पूर्ण

	params = 2 /* level */  + 4 /* rsrvd */  + name_len /* incl null */ ;
	pSMB->TotalDataCount = 0;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	pSMB->MaxDataCount = cpu_to_le16(CIFSMaxBufSize);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	pSMB->ParameterOffset = cpu_to_le16(दुरत्व(
	काष्ठा smb_com_transaction2_qpi_req, Inक्रमmationLevel) - 4);
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_PATH_INFORMATION);
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_खाता_UNIX_LINK);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in QuerySymLinkInfo = %d\n", rc);
	पूर्ण अन्यथा अणु
		/* decode response */

		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);
		/* BB also check enough total bytes वापसed */
		अगर (rc || get_bcc(&pSMBr->hdr) < 2)
			rc = -EIO;
		अन्यथा अणु
			bool is_unicode;
			u16 count = le16_to_cpu(pSMBr->t2.DataCount);

			data_start = ((अक्षर *) &pSMBr->hdr.Protocol) +
					   le16_to_cpu(pSMBr->t2.DataOffset);

			अगर (pSMBr->hdr.Flags2 & SMBFLG2_UNICODE)
				is_unicode = true;
			अन्यथा
				is_unicode = false;

			/* BB FIXME investigate remapping reserved अक्षरs here */
			*symlinkinfo = cअगरs_strndup_from_utf16(data_start,
					count, is_unicode, nls_codepage);
			अगर (!*symlinkinfo)
				rc = -ENOMEM;
		पूर्ण
	पूर्ण
	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ querySymLinkRetry;
	वापस rc;
पूर्ण

/*
 *	Recent Winकरोws versions now create symlinks more frequently
 *	and they use the "reparse point" mechanism below.  We can of course
 *	करो symlinks nicely to Samba and other servers which support the
 *	CIFS Unix Extensions and we can also करो SFU symlinks and "client only"
 *	"MF" symlinks optionally, but क्रम recent Winकरोws we really need to
 *	reenable the code below and fix the cअगरs_symlink callers to handle this.
 *	In the पूर्णांकerim this code has been moved to its own config option so
 *	it is not compiled in by शेष until callers fixed up and more tested.
 */
पूर्णांक
CIFSSMBQuerySymLink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		    __u16 fid, अक्षर **symlinkinfo,
		    स्थिर काष्ठा nls_table *nls_codepage)
अणु
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	काष्ठा smb_com_transaction_ioctl_req *pSMB;
	काष्ठा smb_com_transaction_ioctl_rsp *pSMBr;
	bool is_unicode;
	अचिन्हित पूर्णांक sub_len;
	अक्षर *sub_start;
	काष्ठा reparse_symlink_data *reparse_buf;
	काष्ठा reparse_posix_data *posix_buf;
	__u32 data_offset, data_count;
	अक्षर *end_of_smb;

	cअगरs_dbg(FYI, "In Windows reparse style QueryLink for fid %u\n", fid);
	rc = smb_init(SMB_COM_NT_TRANSACT, 23, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	pSMB->TotalParameterCount = 0 ;
	pSMB->TotalDataCount = 0;
	pSMB->MaxParameterCount = cpu_to_le32(2);
	/* BB find exact data count max from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le32(CIFSMaxBufSize & 0xFFFFFF00);
	pSMB->MaxSetupCount = 4;
	pSMB->Reserved = 0;
	pSMB->ParameterOffset = 0;
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 4;
	pSMB->SubCommand = cpu_to_le16(NT_TRANSACT_IOCTL);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->FunctionCode = cpu_to_le32(FSCTL_GET_REPARSE_POINT);
	pSMB->IsFsctl = 1; /* FSCTL */
	pSMB->IsRootFlag = 0;
	pSMB->Fid = fid; /* file handle always le */
	pSMB->ByteCount = 0;

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in QueryReparseLinkInfo = %d\n", rc);
		जाओ qreparse_out;
	पूर्ण

	data_offset = le32_to_cpu(pSMBr->DataOffset);
	data_count = le32_to_cpu(pSMBr->DataCount);
	अगर (get_bcc(&pSMBr->hdr) < 2 || data_offset > 512) अणु
		/* BB also check enough total bytes वापसed */
		rc = -EIO;	/* bad smb */
		जाओ qreparse_out;
	पूर्ण
	अगर (!data_count || (data_count > 2048)) अणु
		rc = -EIO;
		cअगरs_dbg(FYI, "Invalid return data count on get reparse info ioctl\n");
		जाओ qreparse_out;
	पूर्ण
	end_of_smb = 2 + get_bcc(&pSMBr->hdr) + (अक्षर *)&pSMBr->ByteCount;
	reparse_buf = (काष्ठा reparse_symlink_data *)
				((अक्षर *)&pSMBr->hdr.Protocol + data_offset);
	अगर ((अक्षर *)reparse_buf >= end_of_smb) अणु
		rc = -EIO;
		जाओ qreparse_out;
	पूर्ण
	अगर (reparse_buf->ReparseTag == cpu_to_le32(IO_REPARSE_TAG_NFS)) अणु
		cअगरs_dbg(FYI, "NFS style reparse tag\n");
		posix_buf =  (काष्ठा reparse_posix_data *)reparse_buf;

		अगर (posix_buf->InodeType != cpu_to_le64(NFS_SPECखाता_LNK)) अणु
			cअगरs_dbg(FYI, "unsupported file type 0x%llx\n",
				 le64_to_cpu(posix_buf->InodeType));
			rc = -EOPNOTSUPP;
			जाओ qreparse_out;
		पूर्ण
		is_unicode = true;
		sub_len = le16_to_cpu(reparse_buf->ReparseDataLength);
		अगर (posix_buf->PathBuffer + sub_len > end_of_smb) अणु
			cअगरs_dbg(FYI, "reparse buf beyond SMB\n");
			rc = -EIO;
			जाओ qreparse_out;
		पूर्ण
		*symlinkinfo = cअगरs_strndup_from_utf16(posix_buf->PathBuffer,
				sub_len, is_unicode, nls_codepage);
		जाओ qreparse_out;
	पूर्ण अन्यथा अगर (reparse_buf->ReparseTag !=
			cpu_to_le32(IO_REPARSE_TAG_SYMLINK)) अणु
		rc = -EOPNOTSUPP;
		जाओ qreparse_out;
	पूर्ण

	/* Reparse tag is NTFS symlink */
	sub_start = le16_to_cpu(reparse_buf->SubstituteNameOffset) +
				reparse_buf->PathBuffer;
	sub_len = le16_to_cpu(reparse_buf->SubstituteNameLength);
	अगर (sub_start + sub_len > end_of_smb) अणु
		cअगरs_dbg(FYI, "reparse buf beyond SMB\n");
		rc = -EIO;
		जाओ qreparse_out;
	पूर्ण
	अगर (pSMBr->hdr.Flags2 & SMBFLG2_UNICODE)
		is_unicode = true;
	अन्यथा
		is_unicode = false;

	/* BB FIXME investigate remapping reserved अक्षरs here */
	*symlinkinfo = cअगरs_strndup_from_utf16(sub_start, sub_len, is_unicode,
					       nls_codepage);
	अगर (!*symlinkinfo)
		rc = -ENOMEM;
qreparse_out:
	cअगरs_buf_release(pSMB);

	/*
	 * Note: On -EAGAIN error only caller can retry on handle based calls
	 * since file handle passed in no दीर्घer valid.
	 */
	वापस rc;
पूर्ण

पूर्णांक
CIFSSMB_set_compression(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		    __u16 fid)
अणु
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	काष्ठा smb_com_transaction_compr_ioctl_req *pSMB;
	काष्ठा smb_com_transaction_ioctl_rsp *pSMBr;

	cअगरs_dbg(FYI, "Set compression for %u\n", fid);
	rc = smb_init(SMB_COM_NT_TRANSACT, 23, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	pSMB->compression_state = cpu_to_le16(COMPRESSION_FORMAT_DEFAULT);

	pSMB->TotalParameterCount = 0;
	pSMB->TotalDataCount = cpu_to_le32(2);
	pSMB->MaxParameterCount = 0;
	pSMB->MaxDataCount = 0;
	pSMB->MaxSetupCount = 4;
	pSMB->Reserved = 0;
	pSMB->ParameterOffset = 0;
	pSMB->DataCount = cpu_to_le32(2);
	pSMB->DataOffset =
		cpu_to_le32(दुरत्व(काष्ठा smb_com_transaction_compr_ioctl_req,
				compression_state) - 4);  /* 84 */
	pSMB->SetupCount = 4;
	pSMB->SubCommand = cpu_to_le16(NT_TRANSACT_IOCTL);
	pSMB->ParameterCount = 0;
	pSMB->FunctionCode = cpu_to_le32(FSCTL_SET_COMPRESSION);
	pSMB->IsFsctl = 1; /* FSCTL */
	pSMB->IsRootFlag = 0;
	pSMB->Fid = fid; /* file handle always le */
	/* 3 byte pad, followed by 2 byte compress state */
	pSMB->ByteCount = cpu_to_le16(5);
	inc_rfc1001_len(pSMB, 5);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc)
		cअगरs_dbg(FYI, "Send error in SetCompression = %d\n", rc);

	cअगरs_buf_release(pSMB);

	/*
	 * Note: On -EAGAIN error only caller can retry on handle based calls
	 * since file handle passed in no दीर्घer valid.
	 */
	वापस rc;
पूर्ण


#अगर_घोषित CONFIG_CIFS_POSIX

/*Convert an Access Control Entry from wire क्रमmat to local POSIX xattr क्रमmat*/
अटल व्योम cअगरs_convert_ace(काष्ठा posix_acl_xattr_entry *ace,
			     काष्ठा cअगरs_posix_ace *cअगरs_ace)
अणु
	/* u8 cअगरs fields करो not need le conversion */
	ace->e_perm = cpu_to_le16(cअगरs_ace->cअगरs_e_perm);
	ace->e_tag  = cpu_to_le16(cअगरs_ace->cअगरs_e_tag);
	ace->e_id   = cpu_to_le32(le64_to_cpu(cअगरs_ace->cअगरs_uid));
/*
	cअगरs_dbg(FYI, "perm %d tag %d id %d\n",
		 ace->e_perm, ace->e_tag, ace->e_id);
*/

	वापस;
पूर्ण

/* Convert ACL from CIFS POSIX wire क्रमmat to local Linux POSIX ACL xattr */
अटल पूर्णांक cअगरs_copy_posix_acl(अक्षर *trgt, अक्षर *src, स्थिर पूर्णांक buflen,
			       स्थिर पूर्णांक acl_type, स्थिर पूर्णांक size_of_data_area)
अणु
	पूर्णांक size =  0;
	पूर्णांक i;
	__u16 count;
	काष्ठा cअगरs_posix_ace *pACE;
	काष्ठा cअगरs_posix_acl *cअगरs_acl = (काष्ठा cअगरs_posix_acl *)src;
	काष्ठा posix_acl_xattr_header *local_acl = (व्योम *)trgt;

	अगर (le16_to_cpu(cअगरs_acl->version) != CIFS_ACL_VERSION)
		वापस -EOPNOTSUPP;

	अगर (acl_type == ACL_TYPE_ACCESS) अणु
		count = le16_to_cpu(cअगरs_acl->access_entry_count);
		pACE = &cअगरs_acl->ace_array[0];
		size = माप(काष्ठा cअगरs_posix_acl);
		size += माप(काष्ठा cअगरs_posix_ace) * count;
		/* check अगर we would go beyond end of SMB */
		अगर (size_of_data_area < size) अणु
			cअगरs_dbg(FYI, "bad CIFS POSIX ACL size %d vs. %d\n",
				 size_of_data_area, size);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (acl_type == ACL_TYPE_DEFAULT) अणु
		count = le16_to_cpu(cअगरs_acl->access_entry_count);
		size = माप(काष्ठा cअगरs_posix_acl);
		size += माप(काष्ठा cअगरs_posix_ace) * count;
/* skip past access ACEs to get to शेष ACEs */
		pACE = &cअगरs_acl->ace_array[count];
		count = le16_to_cpu(cअगरs_acl->शेष_entry_count);
		size += माप(काष्ठा cअगरs_posix_ace) * count;
		/* check अगर we would go beyond end of SMB */
		अगर (size_of_data_area < size)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* illegal type */
		वापस -EINVAL;
	पूर्ण

	size = posix_acl_xattr_size(count);
	अगर ((buflen == 0) || (local_acl == शून्य)) अणु
		/* used to query ACL EA size */
	पूर्ण अन्यथा अगर (size > buflen) अणु
		वापस -दुस्फल;
	पूर्ण अन्यथा /* buffer big enough */ अणु
		काष्ठा posix_acl_xattr_entry *ace = (व्योम *)(local_acl + 1);

		local_acl->a_version = cpu_to_le32(POSIX_ACL_XATTR_VERSION);
		क्रम (i = 0; i < count ; i++) अणु
			cअगरs_convert_ace(&ace[i], pACE);
			pACE++;
		पूर्ण
	पूर्ण
	वापस size;
पूर्ण

अटल व्योम convert_ace_to_cअगरs_ace(काष्ठा cअगरs_posix_ace *cअगरs_ace,
				     स्थिर काष्ठा posix_acl_xattr_entry *local_ace)
अणु
	cअगरs_ace->cअगरs_e_perm = le16_to_cpu(local_ace->e_perm);
	cअगरs_ace->cअगरs_e_tag =  le16_to_cpu(local_ace->e_tag);
	/* BB is there a better way to handle the large uid? */
	अगर (local_ace->e_id == cpu_to_le32(-1)) अणु
	/* Probably no need to le convert -1 on any arch but can not hurt */
		cअगरs_ace->cअगरs_uid = cpu_to_le64(-1);
	पूर्ण अन्यथा
		cअगरs_ace->cअगरs_uid = cpu_to_le64(le32_to_cpu(local_ace->e_id));
/*
	cअगरs_dbg(FYI, "perm %d tag %d id %d\n",
		 ace->e_perm, ace->e_tag, ace->e_id);
*/
पूर्ण

/* Convert ACL from local Linux POSIX xattr to CIFS POSIX ACL wire क्रमmat */
अटल __u16 ACL_to_cअगरs_posix(अक्षर *parm_data, स्थिर अक्षर *pACL,
			       स्थिर पूर्णांक buflen, स्थिर पूर्णांक acl_type)
अणु
	__u16 rc = 0;
	काष्ठा cअगरs_posix_acl *cअगरs_acl = (काष्ठा cअगरs_posix_acl *)parm_data;
	काष्ठा posix_acl_xattr_header *local_acl = (व्योम *)pACL;
	काष्ठा posix_acl_xattr_entry *ace = (व्योम *)(local_acl + 1);
	पूर्णांक count;
	पूर्णांक i;

	अगर ((buflen == 0) || (pACL == शून्य) || (cअगरs_acl == शून्य))
		वापस 0;

	count = posix_acl_xattr_count((माप_प्रकार)buflen);
	cअगरs_dbg(FYI, "setting acl with %d entries from buf of length %d and version of %d\n",
		 count, buflen, le32_to_cpu(local_acl->a_version));
	अगर (le32_to_cpu(local_acl->a_version) != 2) अणु
		cअगरs_dbg(FYI, "unknown POSIX ACL version %d\n",
			 le32_to_cpu(local_acl->a_version));
		वापस 0;
	पूर्ण
	cअगरs_acl->version = cpu_to_le16(1);
	अगर (acl_type == ACL_TYPE_ACCESS) अणु
		cअगरs_acl->access_entry_count = cpu_to_le16(count);
		cअगरs_acl->शेष_entry_count = cpu_to_le16(0xFFFF);
	पूर्ण अन्यथा अगर (acl_type == ACL_TYPE_DEFAULT) अणु
		cअगरs_acl->शेष_entry_count = cpu_to_le16(count);
		cअगरs_acl->access_entry_count = cpu_to_le16(0xFFFF);
	पूर्ण अन्यथा अणु
		cअगरs_dbg(FYI, "unknown ACL type %d\n", acl_type);
		वापस 0;
	पूर्ण
	क्रम (i = 0; i < count; i++)
		convert_ace_to_cअगरs_ace(&cअगरs_acl->ace_array[i], &ace[i]);
	अगर (rc == 0) अणु
		rc = (__u16)(count * माप(काष्ठा cअगरs_posix_ace));
		rc += माप(काष्ठा cअगरs_posix_acl);
		/* BB add check to make sure ACL करोes not overflow SMB */
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBGetPosixACL(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   स्थिर अचिन्हित अक्षर *searchName,
		   अक्षर *acl_inf, स्थिर पूर्णांक buflen, स्थिर पूर्णांक acl_type,
		   स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
/* SMB_QUERY_POSIX_ACL */
	TRANSACTION2_QPI_REQ *pSMB = शून्य;
	TRANSACTION2_QPI_RSP *pSMBr = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len;
	__u16 params, byte_count;

	cअगरs_dbg(FYI, "In GetPosixACL (Unix) for path %s\n", searchName);

queryAclRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		(व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
			cअगरsConvertToUTF16((__le16 *) pSMB->FileName,
					   searchName, PATH_MAX, nls_codepage,
					   remap);
		name_len++;     /* trailing null */
		name_len *= 2;
		pSMB->FileName[name_len] = 0;
		pSMB->FileName[name_len+1] = 0;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, searchName);
	पूर्ण

	params = 2 /* level */  + 4 /* rsrvd */  + name_len /* incl null */ ;
	pSMB->TotalDataCount = 0;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find exact max data count below from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(4000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	pSMB->ParameterOffset = cpu_to_le16(
		दुरत्व(काष्ठा smb_com_transaction2_qpi_req,
			 Inक्रमmationLevel) - 4);
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_PATH_INFORMATION);
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_POSIX_ACL);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
		(काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_acl_get);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in Query POSIX ACL = %d\n", rc);
	पूर्ण अन्यथा अणु
		/* decode response */

		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);
		/* BB also check enough total bytes वापसed */
		अगर (rc || get_bcc(&pSMBr->hdr) < 2)
			rc = -EIO;      /* bad smb */
		अन्यथा अणु
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
			__u16 count = le16_to_cpu(pSMBr->t2.DataCount);
			rc = cअगरs_copy_posix_acl(acl_inf,
				(अक्षर *)&pSMBr->hdr.Protocol+data_offset,
				buflen, acl_type, count);
		पूर्ण
	पूर्ण
	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ queryAclRetry;
	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBSetPosixACL(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   स्थिर अचिन्हित अक्षर *fileName,
		   स्थिर अक्षर *local_acl, स्थिर पूर्णांक buflen,
		   स्थिर पूर्णांक acl_type,
		   स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
	काष्ठा smb_com_transaction2_spi_req *pSMB = शून्य;
	काष्ठा smb_com_transaction2_spi_rsp *pSMBr = शून्य;
	अक्षर *parm_data;
	पूर्णांक name_len;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, byte_count, data_count, param_offset, offset;

	cअगरs_dbg(FYI, "In SetPosixACL (Unix) for path %s\n", fileName);
setAclRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;
	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
			cअगरsConvertToUTF16((__le16 *) pSMB->FileName, fileName,
					   PATH_MAX, nls_codepage, remap);
		name_len++;     /* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, fileName);
	पूर्ण
	params = 6 + name_len;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find max SMB size from sess */
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_spi_req,
				Inक्रमmationLevel) - 4;
	offset = param_offset + params;
	parm_data = ((अक्षर *) &pSMB->hdr.Protocol) + offset;
	pSMB->ParameterOffset = cpu_to_le16(param_offset);

	/* convert to on the wire क्रमmat क्रम POSIX ACL */
	data_count = ACL_to_cअगरs_posix(parm_data, local_acl, buflen, acl_type);

	अगर (data_count == 0) अणु
		rc = -EOPNOTSUPP;
		जाओ setACLerrorExit;
	पूर्ण
	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_PATH_INFORMATION);
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_SET_POSIX_ACL);
	byte_count = 3 /* pad */  + params + data_count;
	pSMB->DataCount = cpu_to_le16(data_count);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc)
		cअगरs_dbg(FYI, "Set POSIX ACL returned %d\n", rc);

setACLerrorExit:
	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ setAclRetry;
	वापस rc;
पूर्ण

/* BB fix tअसल in this function FIXME BB */
पूर्णांक
CIFSGetExtAttr(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	       स्थिर पूर्णांक netfid, __u64 *pExtAttrBits, __u64 *pMask)
अणु
	पूर्णांक rc = 0;
	काष्ठा smb_t2_qfi_req *pSMB = शून्य;
	काष्ठा smb_t2_qfi_rsp *pSMBr = शून्य;
	पूर्णांक bytes_वापसed;
	__u16 params, byte_count;

	cअगरs_dbg(FYI, "In GetExtAttr\n");
	अगर (tcon == शून्य)
		वापस -ENODEV;

GetExtAttrRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
			(व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	params = 2 /* level */ + 2 /* fid */;
	pSMB->t2.TotalDataCount = 0;
	pSMB->t2.MaxParameterCount = cpu_to_le16(4);
	/* BB find exact max data count below from sess काष्ठाure BB */
	pSMB->t2.MaxDataCount = cpu_to_le16(4000);
	pSMB->t2.MaxSetupCount = 0;
	pSMB->t2.Reserved = 0;
	pSMB->t2.Flags = 0;
	pSMB->t2.Timeout = 0;
	pSMB->t2.Reserved2 = 0;
	pSMB->t2.ParameterOffset = cpu_to_le16(दुरत्व(काष्ठा smb_t2_qfi_req,
					       Fid) - 4);
	pSMB->t2.DataCount = 0;
	pSMB->t2.DataOffset = 0;
	pSMB->t2.SetupCount = 1;
	pSMB->t2.Reserved3 = 0;
	pSMB->t2.SubCommand = cpu_to_le16(TRANS2_QUERY_खाता_INFORMATION);
	byte_count = params + 1 /* pad */ ;
	pSMB->t2.TotalParameterCount = cpu_to_le16(params);
	pSMB->t2.ParameterCount = pSMB->t2.TotalParameterCount;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_ATTR_FLAGS);
	pSMB->Pad = 0;
	pSMB->Fid = netfid;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->t2.ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "error %d in GetExtAttr\n", rc);
	पूर्ण अन्यथा अणु
		/* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);
		/* BB also check enough total bytes वापसed */
		अगर (rc || get_bcc(&pSMBr->hdr) < 2)
			/* If rc should we check क्रम EOPNOSUPP and
			   disable the srvino flag? or in caller? */
			rc = -EIO;      /* bad smb */
		अन्यथा अणु
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
			__u16 count = le16_to_cpu(pSMBr->t2.DataCount);
			काष्ठा file_chattr_info *pfinfo;
			/* BB Do we need a cast or hash here ? */
			अगर (count != 16) अणु
				cअगरs_dbg(FYI, "Invalid size ret in GetExtAttr\n");
				rc = -EIO;
				जाओ GetExtAttrOut;
			पूर्ण
			pfinfo = (काष्ठा file_chattr_info *)
				 (data_offset + (अक्षर *) &pSMBr->hdr.Protocol);
			*pExtAttrBits = le64_to_cpu(pfinfo->mode);
			*pMask = le64_to_cpu(pfinfo->mask);
		पूर्ण
	पूर्ण
GetExtAttrOut:
	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ GetExtAttrRetry;
	वापस rc;
पूर्ण

#पूर्ण_अगर /* CONFIG_POSIX */

/*
 * Initialize NT TRANSACT SMB पूर्णांकo small smb request buffer.  This assumes that
 * all NT TRANSACTS that we init here have total parm and data under about 400
 * bytes (to fit in small cअगरs buffer size), which is the हाल so far, it
 * easily fits. NB: Setup words themselves and ByteCount MaxSetupCount (size of
 * वापसed setup area) and MaxParameterCount (वापसed parms size) must be set
 * by caller
 */
अटल पूर्णांक
smb_init_nttransact(स्थिर __u16 sub_command, स्थिर पूर्णांक setup_count,
		   स्थिर पूर्णांक parm_len, काष्ठा cअगरs_tcon *tcon,
		   व्योम **ret_buf)
अणु
	पूर्णांक rc;
	__u32 temp_offset;
	काष्ठा smb_com_ntransact_req *pSMB;

	rc = small_smb_init(SMB_COM_NT_TRANSACT, 19 + setup_count, tcon,
				(व्योम **)&pSMB);
	अगर (rc)
		वापस rc;
	*ret_buf = (व्योम *)pSMB;
	pSMB->Reserved = 0;
	pSMB->TotalParameterCount = cpu_to_le32(parm_len);
	pSMB->TotalDataCount  = 0;
	pSMB->MaxDataCount = cpu_to_le32(CIFSMaxBufSize & 0xFFFFFF00);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->DataCount  = pSMB->TotalDataCount;
	temp_offset = दुरत्व(काष्ठा smb_com_ntransact_req, Parms) +
			(setup_count * 2) - 4 /* क्रम rfc1001 length itself */;
	pSMB->ParameterOffset = cpu_to_le32(temp_offset);
	pSMB->DataOffset = cpu_to_le32(temp_offset + parm_len);
	pSMB->SetupCount = setup_count; /* no need to le convert byte fields */
	pSMB->SubCommand = cpu_to_le16(sub_command);
	वापस 0;
पूर्ण

अटल पूर्णांक
validate_ntransact(अक्षर *buf, अक्षर **ppparm, अक्षर **ppdata,
		   __u32 *pparmlen, __u32 *pdatalen)
अणु
	अक्षर *end_of_smb;
	__u32 data_count, data_offset, parm_count, parm_offset;
	काष्ठा smb_com_ntransact_rsp *pSMBr;
	u16 bcc;

	*pdatalen = 0;
	*pparmlen = 0;

	अगर (buf == शून्य)
		वापस -EINVAL;

	pSMBr = (काष्ठा smb_com_ntransact_rsp *)buf;

	bcc = get_bcc(&pSMBr->hdr);
	end_of_smb = 2 /* माप byte count */ + bcc +
			(अक्षर *)&pSMBr->ByteCount;

	data_offset = le32_to_cpu(pSMBr->DataOffset);
	data_count = le32_to_cpu(pSMBr->DataCount);
	parm_offset = le32_to_cpu(pSMBr->ParameterOffset);
	parm_count = le32_to_cpu(pSMBr->ParameterCount);

	*ppparm = (अक्षर *)&pSMBr->hdr.Protocol + parm_offset;
	*ppdata = (अक्षर *)&pSMBr->hdr.Protocol + data_offset;

	/* should we also check that parm and data areas करो not overlap? */
	अगर (*ppparm > end_of_smb) अणु
		cअगरs_dbg(FYI, "parms start after end of smb\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (parm_count + *ppparm > end_of_smb) अणु
		cअगरs_dbg(FYI, "parm end after end of smb\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (*ppdata > end_of_smb) अणु
		cअगरs_dbg(FYI, "data starts after end of smb\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (data_count + *ppdata > end_of_smb) अणु
		cअगरs_dbg(FYI, "data %p + count %d (%p) past smb end %p start %p\n",
			 *ppdata, data_count, (data_count + *ppdata),
			 end_of_smb, pSMBr);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (parm_count + data_count > bcc) अणु
		cअगरs_dbg(FYI, "parm count and data count larger than SMB\n");
		वापस -EINVAL;
	पूर्ण
	*pdatalen = data_count;
	*pparmlen = parm_count;
	वापस 0;
पूर्ण

/* Get Security Descriptor (by handle) from remote server क्रम a file or dir */
पूर्णांक
CIFSSMBGetCIFSACL(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, __u16 fid,
		  काष्ठा cअगरs_ntsd **acl_inf, __u32 *pbuflen)
अणु
	पूर्णांक rc = 0;
	पूर्णांक buf_type = 0;
	QUERY_SEC_DESC_REQ *pSMB;
	काष्ठा kvec iov[1];
	काष्ठा kvec rsp_iov;

	cअगरs_dbg(FYI, "GetCifsACL\n");

	*pbuflen = 0;
	*acl_inf = शून्य;

	rc = smb_init_nttransact(NT_TRANSACT_QUERY_SECURITY_DESC, 0,
			8 /* parm len */, tcon, (व्योम **) &pSMB);
	अगर (rc)
		वापस rc;

	pSMB->MaxParameterCount = cpu_to_le32(4);
	/* BB TEST with big acls that might need to be e.g. larger than 16K */
	pSMB->MaxSetupCount = 0;
	pSMB->Fid = fid; /* file handle always le */
	pSMB->AclFlags = cpu_to_le32(CIFS_ACL_OWNER | CIFS_ACL_GROUP |
				     CIFS_ACL_DACL);
	pSMB->ByteCount = cpu_to_le16(11); /* 3 bytes pad + 8 bytes parm */
	inc_rfc1001_len(pSMB, 11);
	iov[0].iov_base = (अक्षर *)pSMB;
	iov[0].iov_len = be32_to_cpu(pSMB->hdr.smb_buf_length) + 4;

	rc = SendReceive2(xid, tcon->ses, iov, 1 /* num iovec */, &buf_type,
			  0, &rsp_iov);
	cअगरs_small_buf_release(pSMB);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_acl_get);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in QuerySecDesc = %d\n", rc);
	पूर्ण अन्यथा अणु                /* decode response */
		__le32 *parm;
		__u32 parm_len;
		__u32 acl_len;
		काष्ठा smb_com_ntransact_rsp *pSMBr;
		अक्षर *pdata;

/* validate_nttransact */
		rc = validate_ntransact(rsp_iov.iov_base, (अक्षर **)&parm,
					&pdata, &parm_len, pbuflen);
		अगर (rc)
			जाओ qsec_out;
		pSMBr = (काष्ठा smb_com_ntransact_rsp *)rsp_iov.iov_base;

		cअगरs_dbg(FYI, "smb %p parm %p data %p\n",
			 pSMBr, parm, *acl_inf);

		अगर (le32_to_cpu(pSMBr->ParameterCount) != 4) अणु
			rc = -EIO;      /* bad smb */
			*pbuflen = 0;
			जाओ qsec_out;
		पूर्ण

/* BB check that data area is minimum length and as big as acl_len */

		acl_len = le32_to_cpu(*parm);
		अगर (acl_len != *pbuflen) अणु
			cअगरs_dbg(VFS, "acl length %d does not match %d\n",
				 acl_len, *pbuflen);
			अगर (*pbuflen > acl_len)
				*pbuflen = acl_len;
		पूर्ण

		/* check अगर buffer is big enough क्रम the acl
		   header followed by the smallest SID */
		अगर ((*pbuflen < माप(काष्ठा cअगरs_ntsd) + 8) ||
		    (*pbuflen >= 64 * 1024)) अणु
			cअगरs_dbg(VFS, "bad acl length %d\n", *pbuflen);
			rc = -EINVAL;
			*pbuflen = 0;
		पूर्ण अन्यथा अणु
			*acl_inf = kmemdup(pdata, *pbuflen, GFP_KERNEL);
			अगर (*acl_inf == शून्य) अणु
				*pbuflen = 0;
				rc = -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण
qsec_out:
	मुक्त_rsp_buf(buf_type, rsp_iov.iov_base);
	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBSetCIFSACL(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, __u16 fid,
			काष्ठा cअगरs_ntsd *pntsd, __u32 acllen, पूर्णांक aclflag)
अणु
	__u16 byte_count, param_count, data_count, param_offset, data_offset;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	SET_SEC_DESC_REQ *pSMB = शून्य;
	व्योम *pSMBr;

setCअगरsAclRetry:
	rc = smb_init(SMB_COM_NT_TRANSACT, 19, tcon, (व्योम **) &pSMB, &pSMBr);
	अगर (rc)
		वापस rc;

	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;

	param_count = 8;
	param_offset = दुरत्व(काष्ठा smb_com_transaction_ssec_req, Fid) - 4;
	data_count = acllen;
	data_offset = param_offset + param_count;
	byte_count = 3 /* pad */  + param_count;

	pSMB->DataCount = cpu_to_le32(data_count);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->MaxParameterCount = cpu_to_le32(4);
	pSMB->MaxDataCount = cpu_to_le32(16384);
	pSMB->ParameterCount = cpu_to_le32(param_count);
	pSMB->ParameterOffset = cpu_to_le32(param_offset);
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->DataOffset = cpu_to_le32(data_offset);
	pSMB->SetupCount = 0;
	pSMB->SubCommand = cpu_to_le16(NT_TRANSACT_SET_SECURITY_DESC);
	pSMB->ByteCount = cpu_to_le16(byte_count+data_count);

	pSMB->Fid = fid; /* file handle always le */
	pSMB->Reserved2 = 0;
	pSMB->AclFlags = cpu_to_le32(aclflag);

	अगर (pntsd && acllen) अणु
		स_नकल((अक्षर *)pSMBr + दुरत्व(काष्ठा smb_hdr, Protocol) +
				data_offset, pntsd, acllen);
		inc_rfc1001_len(pSMB, byte_count + data_count);
	पूर्ण अन्यथा
		inc_rfc1001_len(pSMB, byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
		(काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);

	cअगरs_dbg(FYI, "SetCIFSACL bytes_returned: %d, rc: %d\n",
		 bytes_वापसed, rc);
	अगर (rc)
		cअगरs_dbg(FYI, "Set CIFS ACL returned %d\n", rc);
	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ setCअगरsAclRetry;

	वापस (rc);
पूर्ण


/* Legacy Query Path Inक्रमmation call क्रम lookup to old servers such
   as Win9x/WinME */
पूर्णांक
SMBQueryInक्रमmation(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		    स्थिर अक्षर *search_name, खाता_ALL_INFO *data,
		    स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
	QUERY_INFORMATION_REQ *pSMB;
	QUERY_INFORMATION_RSP *pSMBr;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len;

	cअगरs_dbg(FYI, "In SMBQPath path %s\n", search_name);
QInfRetry:
	rc = smb_init(SMB_COM_QUERY_INFORMATION, 0, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
			cअगरsConvertToUTF16((__le16 *) pSMB->FileName,
					   search_name, PATH_MAX, nls_codepage,
					   remap);
		name_len++;     /* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, search_name);
	पूर्ण
	pSMB->BufferFormat = 0x04;
	name_len++; /* account क्रम buffer type byte */
	inc_rfc1001_len(pSMB, (__u16)name_len);
	pSMB->ByteCount = cpu_to_le16(name_len);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in QueryInfo = %d\n", rc);
	पूर्ण अन्यथा अगर (data) अणु
		काष्ठा बारpec64 ts;
		__u32 समय = le32_to_cpu(pSMBr->last_ग_लिखो_समय);

		/* decode response */
		/* BB FIXME - add समय zone adjusपंचांगent BB */
		स_रखो(data, 0, माप(खाता_ALL_INFO));
		ts.tv_nsec = 0;
		ts.tv_sec = समय;
		/* decode समय fields */
		data->ChangeTime = cpu_to_le64(cअगरs_UnixTimeToNT(ts));
		data->LastWriteTime = data->ChangeTime;
		data->LastAccessTime = 0;
		data->AllocationSize =
			cpu_to_le64(le32_to_cpu(pSMBr->size));
		data->EndOfFile = data->AllocationSize;
		data->Attributes =
			cpu_to_le32(le16_to_cpu(pSMBr->attr));
	पूर्ण अन्यथा
		rc = -EIO; /* bad buffer passed in */

	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ QInfRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBQFileInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		 u16 netfid, खाता_ALL_INFO *pFindData)
अणु
	काष्ठा smb_t2_qfi_req *pSMB = शून्य;
	काष्ठा smb_t2_qfi_rsp *pSMBr = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	__u16 params, byte_count;

QFileInfoRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	params = 2 /* level */ + 2 /* fid */;
	pSMB->t2.TotalDataCount = 0;
	pSMB->t2.MaxParameterCount = cpu_to_le16(4);
	/* BB find exact max data count below from sess काष्ठाure BB */
	pSMB->t2.MaxDataCount = cpu_to_le16(CIFSMaxBufSize);
	pSMB->t2.MaxSetupCount = 0;
	pSMB->t2.Reserved = 0;
	pSMB->t2.Flags = 0;
	pSMB->t2.Timeout = 0;
	pSMB->t2.Reserved2 = 0;
	pSMB->t2.ParameterOffset = cpu_to_le16(दुरत्व(काष्ठा smb_t2_qfi_req,
					       Fid) - 4);
	pSMB->t2.DataCount = 0;
	pSMB->t2.DataOffset = 0;
	pSMB->t2.SetupCount = 1;
	pSMB->t2.Reserved3 = 0;
	pSMB->t2.SubCommand = cpu_to_le16(TRANS2_QUERY_खाता_INFORMATION);
	byte_count = params + 1 /* pad */ ;
	pSMB->t2.TotalParameterCount = cpu_to_le16(params);
	pSMB->t2.ParameterCount = pSMB->t2.TotalParameterCount;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_खाता_ALL_INFO);
	pSMB->Pad = 0;
	pSMB->Fid = netfid;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->t2.ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in QFileInfo = %d\n", rc);
	पूर्ण अन्यथा अणु		/* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

		अगर (rc) /* BB add स्वतः retry on EOPNOTSUPP? */
			rc = -EIO;
		अन्यथा अगर (get_bcc(&pSMBr->hdr) < 40)
			rc = -EIO;	/* bad smb */
		अन्यथा अगर (pFindData) अणु
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
			स_नकल((अक्षर *) pFindData,
			       (अक्षर *) &pSMBr->hdr.Protocol +
			       data_offset, माप(खाता_ALL_INFO));
		पूर्ण अन्यथा
		    rc = -ENOMEM;
	पूर्ण
	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ QFileInfoRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBQPathInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		 स्थिर अक्षर *search_name, खाता_ALL_INFO *data,
		 पूर्णांक legacy /* old style infolevel */,
		 स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
	/* level 263 SMB_QUERY_खाता_ALL_INFO */
	TRANSACTION2_QPI_REQ *pSMB = शून्य;
	TRANSACTION2_QPI_RSP *pSMBr = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len;
	__u16 params, byte_count;

	/* cअगरs_dbg(FYI, "In QPathInfo path %s\n", search_name); */
QPathInfoRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->FileName, search_name,
				       PATH_MAX, nls_codepage, remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, search_name);
	पूर्ण

	params = 2 /* level */ + 4 /* reserved */ + name_len /* includes NUL */;
	pSMB->TotalDataCount = 0;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find exact max SMB PDU from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(4000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	pSMB->ParameterOffset = cpu_to_le16(दुरत्व(
	काष्ठा smb_com_transaction2_qpi_req, Inक्रमmationLevel) - 4);
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_PATH_INFORMATION);
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	अगर (legacy)
		pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_INFO_STANDARD);
	अन्यथा
		pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_खाता_ALL_INFO);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in QPathInfo = %d\n", rc);
	पूर्ण अन्यथा अणु		/* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

		अगर (rc) /* BB add स्वतः retry on EOPNOTSUPP? */
			rc = -EIO;
		अन्यथा अगर (!legacy && get_bcc(&pSMBr->hdr) < 40)
			rc = -EIO;	/* bad smb */
		अन्यथा अगर (legacy && get_bcc(&pSMBr->hdr) < 24)
			rc = -EIO;  /* 24 or 26 expected but we करो not पढ़ो
					last field */
		अन्यथा अगर (data) अणु
			पूर्णांक size;
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);

			/*
			 * On legacy responses we करो not पढ़ो the last field,
			 * EAsize, क्रमtunately since it varies by subdialect and
			 * also note it dअगरfers on Set vs Get, ie two bytes or 4
			 * bytes depending but we करोn't care here.
			 */
			अगर (legacy)
				size = माप(खाता_INFO_STANDARD);
			अन्यथा
				size = माप(खाता_ALL_INFO);
			स_नकल((अक्षर *) data, (अक्षर *) &pSMBr->hdr.Protocol +
			       data_offset, size);
		पूर्ण अन्यथा
		    rc = -ENOMEM;
	पूर्ण
	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ QPathInfoRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBUnixQFileInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		 u16 netfid, खाता_UNIX_BASIC_INFO *pFindData)
अणु
	काष्ठा smb_t2_qfi_req *pSMB = शून्य;
	काष्ठा smb_t2_qfi_rsp *pSMBr = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	__u16 params, byte_count;

UnixQFileInfoRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	params = 2 /* level */ + 2 /* fid */;
	pSMB->t2.TotalDataCount = 0;
	pSMB->t2.MaxParameterCount = cpu_to_le16(4);
	/* BB find exact max data count below from sess काष्ठाure BB */
	pSMB->t2.MaxDataCount = cpu_to_le16(CIFSMaxBufSize);
	pSMB->t2.MaxSetupCount = 0;
	pSMB->t2.Reserved = 0;
	pSMB->t2.Flags = 0;
	pSMB->t2.Timeout = 0;
	pSMB->t2.Reserved2 = 0;
	pSMB->t2.ParameterOffset = cpu_to_le16(दुरत्व(काष्ठा smb_t2_qfi_req,
					       Fid) - 4);
	pSMB->t2.DataCount = 0;
	pSMB->t2.DataOffset = 0;
	pSMB->t2.SetupCount = 1;
	pSMB->t2.Reserved3 = 0;
	pSMB->t2.SubCommand = cpu_to_le16(TRANS2_QUERY_खाता_INFORMATION);
	byte_count = params + 1 /* pad */ ;
	pSMB->t2.TotalParameterCount = cpu_to_le16(params);
	pSMB->t2.ParameterCount = pSMB->t2.TotalParameterCount;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_खाता_UNIX_BASIC);
	pSMB->Pad = 0;
	pSMB->Fid = netfid;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->t2.ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in UnixQFileInfo = %d\n", rc);
	पूर्ण अन्यथा अणु		/* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

		अगर (rc || get_bcc(&pSMBr->hdr) < माप(खाता_UNIX_BASIC_INFO)) अणु
			cअगरs_dbg(VFS, "Malformed FILE_UNIX_BASIC_INFO response. Unix Extensions can be disabled on mount by specifying the nosfu mount option.\n");
			rc = -EIO;	/* bad smb */
		पूर्ण अन्यथा अणु
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
			स_नकल((अक्षर *) pFindData,
			       (अक्षर *) &pSMBr->hdr.Protocol +
			       data_offset,
			       माप(खाता_UNIX_BASIC_INFO));
		पूर्ण
	पूर्ण

	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ UnixQFileInfoRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBUnixQPathInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     स्थिर अचिन्हित अक्षर *searchName,
		     खाता_UNIX_BASIC_INFO *pFindData,
		     स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
/* SMB_QUERY_खाता_UNIX_BASIC */
	TRANSACTION2_QPI_REQ *pSMB = शून्य;
	TRANSACTION2_QPI_RSP *pSMBr = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	पूर्णांक name_len;
	__u16 params, byte_count;

	cअगरs_dbg(FYI, "In QPathInfo (Unix) the path %s\n", searchName);
UnixQPathInfoRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->FileName, searchName,
				       PATH_MAX, nls_codepage, remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, searchName);
	पूर्ण

	params = 2 /* level */ + 4 /* reserved */ + name_len /* includes NUL */;
	pSMB->TotalDataCount = 0;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find exact max SMB PDU from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(4000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	pSMB->ParameterOffset = cpu_to_le16(दुरत्व(
	काष्ठा smb_com_transaction2_qpi_req, Inक्रमmationLevel) - 4);
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_PATH_INFORMATION);
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_खाता_UNIX_BASIC);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in UnixQPathInfo = %d\n", rc);
	पूर्ण अन्यथा अणु		/* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

		अगर (rc || get_bcc(&pSMBr->hdr) < माप(खाता_UNIX_BASIC_INFO)) अणु
			cअगरs_dbg(VFS, "Malformed FILE_UNIX_BASIC_INFO response. Unix Extensions can be disabled on mount by specifying the nosfu mount option.\n");
			rc = -EIO;	/* bad smb */
		पूर्ण अन्यथा अणु
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
			स_नकल((अक्षर *) pFindData,
			       (अक्षर *) &pSMBr->hdr.Protocol +
			       data_offset,
			       माप(खाता_UNIX_BASIC_INFO));
		पूर्ण
	पूर्ण
	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ UnixQPathInfoRetry;

	वापस rc;
पूर्ण

/* xid, tcon, searchName and codepage are input parms, rest are वापसed */
पूर्णांक
CIFSFindFirst(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	      स्थिर अक्षर *searchName, काष्ठा cअगरs_sb_info *cअगरs_sb,
	      __u16 *pnetfid, __u16 search_flags,
	      काष्ठा cअगरs_search_info *psrch_inf, bool msearch)
अणु
/* level 257 SMB_ */
	TRANSACTION2_FFIRST_REQ *pSMB = शून्य;
	TRANSACTION2_FFIRST_RSP *pSMBr = शून्य;
	T2_FFIRST_RSP_PARMS *parms;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	पूर्णांक name_len, remap;
	__u16 params, byte_count;
	काष्ठा nls_table *nls_codepage;

	cअगरs_dbg(FYI, "In FindFirst for %s\n", searchName);

findFirstRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	nls_codepage = cअगरs_sb->local_nls;
	remap = cअगरs_remap(cअगरs_sb);

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->FileName, searchName,
				       PATH_MAX, nls_codepage, remap);
		/* We can not add the asterik earlier in हाल
		it got remapped to 0xF03A as अगर it were part of the
		directory name instead of a wildcard */
		name_len *= 2;
		अगर (msearch) अणु
			pSMB->FileName[name_len] = CIFS_सूची_SEP(cअगरs_sb);
			pSMB->FileName[name_len+1] = 0;
			pSMB->FileName[name_len+2] = '*';
			pSMB->FileName[name_len+3] = 0;
			name_len += 4; /* now the trailing null */
			/* null terminate just in हाल */
			pSMB->FileName[name_len] = 0;
			pSMB->FileName[name_len+1] = 0;
			name_len += 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, searchName);
		अगर (msearch) अणु
			अगर (WARN_ON_ONCE(name_len > PATH_MAX-2))
				name_len = PATH_MAX-2;
			/* overग_लिखो nul byte */
			pSMB->FileName[name_len-1] = CIFS_सूची_SEP(cअगरs_sb);
			pSMB->FileName[name_len] = '*';
			pSMB->FileName[name_len+1] = 0;
			name_len += 2;
		पूर्ण
	पूर्ण

	params = 12 + name_len /* includes null */ ;
	pSMB->TotalDataCount = 0;	/* no EAs */
	pSMB->MaxParameterCount = cpu_to_le16(10);
	pSMB->MaxDataCount = cpu_to_le16(CIFSMaxBufSize & 0xFFFFFF00);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(
	      दुरत्व(काष्ठा smb_com_transaction2_ffirst_req, SearchAttributes)
		- 4);
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;	/* one byte, no need to make endian neutral */
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_FIND_FIRST);
	pSMB->SearchAttributes =
	    cpu_to_le16(ATTR_READONLY | ATTR_HIDDEN | ATTR_SYSTEM |
			ATTR_सूचीECTORY);
	pSMB->SearchCount = cpu_to_le16(CIFSMaxBufSize/माप(खाता_UNIX_INFO));
	pSMB->SearchFlags = cpu_to_le16(search_flags);
	pSMB->Inक्रमmationLevel = cpu_to_le16(psrch_inf->info_level);

	/* BB what should we set StorageType to? Does it matter? BB */
	pSMB->SearchStorageType = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_ffirst);

	अगर (rc) अणु/* BB add logic to retry regular search अगर Unix search
			rejected unexpectedly by server */
		/* BB Add code to handle unsupported level rc */
		cअगरs_dbg(FYI, "Error in FindFirst = %d\n", rc);

		cअगरs_buf_release(pSMB);

		/* BB eventually could optimize out मुक्त and पुनः_स्मृति of buf */
		/*    क्रम this हाल */
		अगर (rc == -EAGAIN)
			जाओ findFirstRetry;
	पूर्ण अन्यथा अणु /* decode response */
		/* BB remember to मुक्त buffer अगर error BB */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);
		अगर (rc == 0) अणु
			अचिन्हित पूर्णांक lnoff;

			अगर (pSMBr->hdr.Flags2 & SMBFLG2_UNICODE)
				psrch_inf->unicode = true;
			अन्यथा
				psrch_inf->unicode = false;

			psrch_inf->ntwrk_buf_start = (अक्षर *)pSMBr;
			psrch_inf->smallBuf = false;
			psrch_inf->srch_entries_start =
				(अक्षर *) &pSMBr->hdr.Protocol +
					le16_to_cpu(pSMBr->t2.DataOffset);
			parms = (T2_FFIRST_RSP_PARMS *)((अक्षर *) &pSMBr->hdr.Protocol +
			       le16_to_cpu(pSMBr->t2.ParameterOffset));

			अगर (parms->EnकरोfSearch)
				psrch_inf->endOfSearch = true;
			अन्यथा
				psrch_inf->endOfSearch = false;

			psrch_inf->entries_in_buffer =
					le16_to_cpu(parms->SearchCount);
			psrch_inf->index_of_last_entry = 2 /* skip . and .. */ +
				psrch_inf->entries_in_buffer;
			lnoff = le16_to_cpu(parms->LastNameOffset);
			अगर (CIFSMaxBufSize < lnoff) अणु
				cअगरs_dbg(VFS, "ignoring corrupt resume name\n");
				psrch_inf->last_entry = शून्य;
				वापस rc;
			पूर्ण

			psrch_inf->last_entry = psrch_inf->srch_entries_start +
							lnoff;

			अगर (pnetfid)
				*pnetfid = parms->SearchHandle;
		पूर्ण अन्यथा अणु
			cअगरs_buf_release(pSMB);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक CIFSFindNext(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		 __u16 searchHandle, __u16 search_flags,
		 काष्ठा cअगरs_search_info *psrch_inf)
अणु
	TRANSACTION2_FNEXT_REQ *pSMB = शून्य;
	TRANSACTION2_FNEXT_RSP *pSMBr = शून्य;
	T2_FNEXT_RSP_PARMS *parms;
	अक्षर *response_data;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	अचिन्हित पूर्णांक name_len;
	__u16 params, byte_count;

	cअगरs_dbg(FYI, "In FindNext\n");

	अगर (psrch_inf->endOfSearch)
		वापस -ENOENT;

	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		(व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	params = 14; /* includes 2 bytes of null string, converted to LE below*/
	byte_count = 0;
	pSMB->TotalDataCount = 0;       /* no EAs */
	pSMB->MaxParameterCount = cpu_to_le16(8);
	pSMB->MaxDataCount = cpu_to_le16(CIFSMaxBufSize & 0xFFFFFF00);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	pSMB->ParameterOffset =  cpu_to_le16(
	      दुरत्व(काष्ठा smb_com_transaction2_fnext_req,SearchHandle) - 4);
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_FIND_NEXT);
	pSMB->SearchHandle = searchHandle;      /* always kept as le */
	pSMB->SearchCount =
		cpu_to_le16(CIFSMaxBufSize / माप(खाता_UNIX_INFO));
	pSMB->Inक्रमmationLevel = cpu_to_le16(psrch_inf->info_level);
	pSMB->ResumeKey = psrch_inf->resume_key;
	pSMB->SearchFlags = cpu_to_le16(search_flags);

	name_len = psrch_inf->resume_name_len;
	params += name_len;
	अगर (name_len < PATH_MAX) अणु
		स_नकल(pSMB->ResumeFileName, psrch_inf->presume_name, name_len);
		byte_count += name_len;
		/* 14 byte parm len above enough क्रम 2 byte null terminator */
		pSMB->ResumeFileName[name_len] = 0;
		pSMB->ResumeFileName[name_len+1] = 0;
	पूर्ण अन्यथा अणु
		rc = -EINVAL;
		जाओ FNext2_err_निकास;
	पूर्ण
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			(काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_fnext);
	अगर (rc) अणु
		अगर (rc == -EBADF) अणु
			psrch_inf->endOfSearch = true;
			cअगरs_buf_release(pSMB);
			rc = 0; /* search probably was बंदd at end of search*/
		पूर्ण अन्यथा
			cअगरs_dbg(FYI, "FindNext returned = %d\n", rc);
	पूर्ण अन्यथा अणु                /* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

		अगर (rc == 0) अणु
			अचिन्हित पूर्णांक lnoff;

			/* BB fixme add lock क्रम file (srch_info) काष्ठा here */
			अगर (pSMBr->hdr.Flags2 & SMBFLG2_UNICODE)
				psrch_inf->unicode = true;
			अन्यथा
				psrch_inf->unicode = false;
			response_data = (अक्षर *) &pSMBr->hdr.Protocol +
			       le16_to_cpu(pSMBr->t2.ParameterOffset);
			parms = (T2_FNEXT_RSP_PARMS *)response_data;
			response_data = (अक्षर *)&pSMBr->hdr.Protocol +
				le16_to_cpu(pSMBr->t2.DataOffset);
			अगर (psrch_inf->smallBuf)
				cअगरs_small_buf_release(
					psrch_inf->ntwrk_buf_start);
			अन्यथा
				cअगरs_buf_release(psrch_inf->ntwrk_buf_start);
			psrch_inf->srch_entries_start = response_data;
			psrch_inf->ntwrk_buf_start = (अक्षर *)pSMB;
			psrch_inf->smallBuf = false;
			अगर (parms->EnकरोfSearch)
				psrch_inf->endOfSearch = true;
			अन्यथा
				psrch_inf->endOfSearch = false;
			psrch_inf->entries_in_buffer =
						le16_to_cpu(parms->SearchCount);
			psrch_inf->index_of_last_entry +=
				psrch_inf->entries_in_buffer;
			lnoff = le16_to_cpu(parms->LastNameOffset);
			अगर (CIFSMaxBufSize < lnoff) अणु
				cअगरs_dbg(VFS, "ignoring corrupt resume name\n");
				psrch_inf->last_entry = शून्य;
				वापस rc;
			पूर्ण अन्यथा
				psrch_inf->last_entry =
					psrch_inf->srch_entries_start + lnoff;

/*  cअगरs_dbg(FYI, "fnxt2 entries in buf %d index_of_last %d\n",
    psrch_inf->entries_in_buffer, psrch_inf->index_of_last_entry); */

			/* BB fixme add unlock here */
		पूर्ण

	पूर्ण

	/* BB On error, should we leave previous search buf (and count and
	last entry fields) पूर्णांकact or मुक्त the previous one? */

	/* Note: On -EAGAIN error only caller can retry on handle based calls
	since file handle passed in no दीर्घer valid */
FNext2_err_निकास:
	अगर (rc != 0)
		cअगरs_buf_release(pSMB);
	वापस rc;
पूर्ण

पूर्णांक
CIFSFindClose(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	      स्थिर __u16 searchHandle)
अणु
	पूर्णांक rc = 0;
	FINDCLOSE_REQ *pSMB = शून्य;

	cअगरs_dbg(FYI, "In CIFSSMBFindClose\n");
	rc = small_smb_init(SMB_COM_FIND_CLOSE2, 1, tcon, (व्योम **)&pSMB);

	/* no sense वापसing error अगर session restarted
		as file handle has been बंदd */
	अगर (rc == -EAGAIN)
		वापस 0;
	अगर (rc)
		वापस rc;

	pSMB->FileID = searchHandle;
	pSMB->ByteCount = 0;
	rc = SendReceiveNoRsp(xid, tcon->ses, (अक्षर *) pSMB, 0);
	cअगरs_small_buf_release(pSMB);
	अगर (rc)
		cअगरs_dbg(VFS, "Send error in FindClose = %d\n", rc);

	cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_ख_बंद);

	/* Since session is dead, search handle बंदd on server alपढ़ोy */
	अगर (rc == -EAGAIN)
		rc = 0;

	वापस rc;
पूर्ण

पूर्णांक
CIFSGetSrvInodeNumber(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		      स्थिर अक्षर *search_name, __u64 *inode_number,
		      स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
	पूर्णांक rc = 0;
	TRANSACTION2_QPI_REQ *pSMB = शून्य;
	TRANSACTION2_QPI_RSP *pSMBr = शून्य;
	पूर्णांक name_len, bytes_वापसed;
	__u16 params, byte_count;

	cअगरs_dbg(FYI, "In GetSrvInodeNum for %s\n", search_name);
	अगर (tcon == शून्य)
		वापस -ENODEV;

GetInodeNumberRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
			cअगरsConvertToUTF16((__le16 *) pSMB->FileName,
					   search_name, PATH_MAX, nls_codepage,
					   remap);
		name_len++;     /* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, search_name);
	पूर्ण

	params = 2 /* level */  + 4 /* rsrvd */  + name_len /* incl null */ ;
	pSMB->TotalDataCount = 0;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find exact max data count below from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(4000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	pSMB->ParameterOffset = cpu_to_le16(दुरत्व(
		काष्ठा smb_com_transaction2_qpi_req, Inक्रमmationLevel) - 4);
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_PATH_INFORMATION);
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_खाता_INTERNAL_INFO);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
		(काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "error %d in QueryInternalInfo\n", rc);
	पूर्ण अन्यथा अणु
		/* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);
		/* BB also check enough total bytes वापसed */
		अगर (rc || get_bcc(&pSMBr->hdr) < 2)
			/* If rc should we check क्रम EOPNOSUPP and
			disable the srvino flag? or in caller? */
			rc = -EIO;      /* bad smb */
		अन्यथा अणु
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
			__u16 count = le16_to_cpu(pSMBr->t2.DataCount);
			काष्ठा file_पूर्णांकernal_info *pfinfo;
			/* BB Do we need a cast or hash here ? */
			अगर (count < 8) अणु
				cअगरs_dbg(FYI, "Invalid size ret in QryIntrnlInf\n");
				rc = -EIO;
				जाओ GetInodeNumOut;
			पूर्ण
			pfinfo = (काष्ठा file_पूर्णांकernal_info *)
				(data_offset + (अक्षर *) &pSMBr->hdr.Protocol);
			*inode_number = le64_to_cpu(pfinfo->UniqueId);
		पूर्ण
	पूर्ण
GetInodeNumOut:
	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ GetInodeNumberRetry;
	वापस rc;
पूर्ण

पूर्णांक
CIFSGetDFSRefer(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
		स्थिर अक्षर *search_name, काष्ठा dfs_info3_param **target_nodes,
		अचिन्हित पूर्णांक *num_of_nodes,
		स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
/* TRANS2_GET_DFS_REFERRAL */
	TRANSACTION2_GET_DFS_REFER_REQ *pSMB = शून्य;
	TRANSACTION2_GET_DFS_REFER_RSP *pSMBr = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	पूर्णांक name_len;
	__u16 params, byte_count;
	*num_of_nodes = 0;
	*target_nodes = शून्य;

	cअगरs_dbg(FYI, "In GetDFSRefer the path %s\n", search_name);
	अगर (ses == शून्य || ses->tcon_ipc == शून्य)
		वापस -ENODEV;

getDFSRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, ses->tcon_ipc, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	/* server poपूर्णांकer checked in called function,
	but should never be null here anyway */
	pSMB->hdr.Mid = get_next_mid(ses->server);
	pSMB->hdr.Tid = ses->tcon_ipc->tid;
	pSMB->hdr.Uid = ses->Suid;
	अगर (ses->capabilities & CAP_STATUS32)
		pSMB->hdr.Flags2 |= SMBFLG2_ERR_STATUS;
	अगर (ses->capabilities & CAP_DFS)
		pSMB->hdr.Flags2 |= SMBFLG2_DFS;

	अगर (ses->capabilities & CAP_UNICODE) अणु
		pSMB->hdr.Flags2 |= SMBFLG2_UNICODE;
		name_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->RequestFileName,
				       search_name, PATH_MAX, nls_codepage,
				       remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु	/* BB improve the check क्रम buffer overruns BB */
		name_len = copy_path_name(pSMB->RequestFileName, search_name);
	पूर्ण

	अगर (ses->server->sign)
		pSMB->hdr.Flags2 |= SMBFLG2_SECURITY_SIGNATURE;

	pSMB->hdr.Uid = ses->Suid;

	params = 2 /* level */  + name_len /*includes null */ ;
	pSMB->TotalDataCount = 0;
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->MaxParameterCount = 0;
	/* BB find exact max SMB PDU from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(4000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	pSMB->ParameterOffset = cpu_to_le16(दुरत्व(
	  काष्ठा smb_com_transaction2_get_dfs_refer_req, MaxReferralLevel) - 4);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_GET_DFS_REFERRAL);
	byte_count = params + 3 /* pad */ ;
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->MaxReferralLevel = cpu_to_le16(3);
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in GetDFSRefer = %d\n", rc);
		जाओ GetDFSRefExit;
	पूर्ण
	rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

	/* BB Also check अगर enough total bytes वापसed? */
	अगर (rc || get_bcc(&pSMBr->hdr) < 17) अणु
		rc = -EIO;      /* bad smb */
		जाओ GetDFSRefExit;
	पूर्ण

	cअगरs_dbg(FYI, "Decoding GetDFSRefer response BCC: %d  Offset %d\n",
		 get_bcc(&pSMBr->hdr), le16_to_cpu(pSMBr->t2.DataOffset));

	/* parse वापसed result पूर्णांकo more usable क्रमm */
	rc = parse_dfs_referrals(&pSMBr->dfs_data,
				 le16_to_cpu(pSMBr->t2.DataCount),
				 num_of_nodes, target_nodes, nls_codepage,
				 remap, search_name,
				 (pSMBr->hdr.Flags2 & SMBFLG2_UNICODE) != 0);

GetDFSRefExit:
	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ getDFSRetry;

	वापस rc;
पूर्ण

/* Query File System Info such as मुक्त space to old servers such as Win 9x */
पूर्णांक
SMBOldQFSInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	      काष्ठा kstatfs *FSData)
अणु
/* level 0x01 SMB_QUERY_खाता_SYSTEM_INFO */
	TRANSACTION2_QFSI_REQ *pSMB = शून्य;
	TRANSACTION2_QFSI_RSP *pSMBr = शून्य;
	खाता_SYSTEM_ALLOC_INFO *response_data;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, byte_count;

	cअगरs_dbg(FYI, "OldQFSInfo\n");
oldQFSInfoRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		(व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	params = 2;     /* level */
	pSMB->TotalDataCount = 0;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(दुरत्व(
	काष्ठा smb_com_transaction2_qfsi_req, Inक्रमmationLevel) - 4);
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_FS_INFORMATION);
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_INFO_ALLOCATION);
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
		(काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in QFSInfo = %d\n", rc);
	पूर्ण अन्यथा अणु                /* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

		अगर (rc || get_bcc(&pSMBr->hdr) < 18)
			rc = -EIO;      /* bad smb */
		अन्यथा अणु
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
			cअगरs_dbg(FYI, "qfsinf resp BCC: %d  Offset %d\n",
				 get_bcc(&pSMBr->hdr), data_offset);

			response_data = (खाता_SYSTEM_ALLOC_INFO *)
				(((अक्षर *) &pSMBr->hdr.Protocol) + data_offset);
			FSData->f_bsize =
				le16_to_cpu(response_data->BytesPerSector) *
				le32_to_cpu(response_data->
					SectorsPerAllocationUnit);
			/*
			 * much prefer larger but अगर server करोesn't report
			 * a valid size than 4K is a reasonable minimum
			 */
			अगर (FSData->f_bsize < 512)
				FSData->f_bsize = 4096;

			FSData->f_blocks =
			       le32_to_cpu(response_data->TotalAllocationUnits);
			FSData->f_bमुक्त = FSData->f_bavail =
				le32_to_cpu(response_data->FreeAllocationUnits);
			cअगरs_dbg(FYI, "Blocks: %lld  Free: %lld Block size %ld\n",
				 (अचिन्हित दीर्घ दीर्घ)FSData->f_blocks,
				 (अचिन्हित दीर्घ दीर्घ)FSData->f_bमुक्त,
				 FSData->f_bsize);
		पूर्ण
	पूर्ण
	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ oldQFSInfoRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBQFSInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	       काष्ठा kstatfs *FSData)
अणु
/* level 0x103 SMB_QUERY_खाता_SYSTEM_INFO */
	TRANSACTION2_QFSI_REQ *pSMB = शून्य;
	TRANSACTION2_QFSI_RSP *pSMBr = शून्य;
	खाता_SYSTEM_INFO *response_data;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, byte_count;

	cअगरs_dbg(FYI, "In QFSInfo\n");
QFSInfoRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	params = 2;	/* level */
	pSMB->TotalDataCount = 0;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(दुरत्व(
		काष्ठा smb_com_transaction2_qfsi_req, Inक्रमmationLevel) - 4);
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_FS_INFORMATION);
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_FS_SIZE_INFO);
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in QFSInfo = %d\n", rc);
	पूर्ण अन्यथा अणु		/* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

		अगर (rc || get_bcc(&pSMBr->hdr) < 24)
			rc = -EIO;	/* bad smb */
		अन्यथा अणु
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);

			response_data =
			    (खाता_SYSTEM_INFO
			     *) (((अक्षर *) &pSMBr->hdr.Protocol) +
				 data_offset);
			FSData->f_bsize =
			    le32_to_cpu(response_data->BytesPerSector) *
			    le32_to_cpu(response_data->
					SectorsPerAllocationUnit);
			/*
			 * much prefer larger but अगर server करोesn't report
			 * a valid size than 4K is a reasonable minimum
			 */
			अगर (FSData->f_bsize < 512)
				FSData->f_bsize = 4096;

			FSData->f_blocks =
			    le64_to_cpu(response_data->TotalAllocationUnits);
			FSData->f_bमुक्त = FSData->f_bavail =
			    le64_to_cpu(response_data->FreeAllocationUnits);
			cअगरs_dbg(FYI, "Blocks: %lld  Free: %lld Block size %ld\n",
				 (अचिन्हित दीर्घ दीर्घ)FSData->f_blocks,
				 (अचिन्हित दीर्घ दीर्घ)FSData->f_bमुक्त,
				 FSData->f_bsize);
		पूर्ण
	पूर्ण
	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ QFSInfoRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBQFSAttributeInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon)
अणु
/* level 0x105  SMB_QUERY_खाता_SYSTEM_INFO */
	TRANSACTION2_QFSI_REQ *pSMB = शून्य;
	TRANSACTION2_QFSI_RSP *pSMBr = शून्य;
	खाता_SYSTEM_ATTRIBUTE_INFO *response_data;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, byte_count;

	cअगरs_dbg(FYI, "In QFSAttributeInfo\n");
QFSAttributeRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	params = 2;	/* level */
	pSMB->TotalDataCount = 0;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find exact max SMB PDU from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(दुरत्व(
		काष्ठा smb_com_transaction2_qfsi_req, Inक्रमmationLevel) - 4);
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_FS_INFORMATION);
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_FS_ATTRIBUTE_INFO);
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "Send error in QFSAttributeInfo = %d\n", rc);
	पूर्ण अन्यथा अणु		/* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

		अगर (rc || get_bcc(&pSMBr->hdr) < 13) अणु
			/* BB also check अगर enough bytes वापसed */
			rc = -EIO;	/* bad smb */
		पूर्ण अन्यथा अणु
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
			response_data =
			    (खाता_SYSTEM_ATTRIBUTE_INFO
			     *) (((अक्षर *) &pSMBr->hdr.Protocol) +
				 data_offset);
			स_नकल(&tcon->fsAttrInfo, response_data,
			       माप(खाता_SYSTEM_ATTRIBUTE_INFO));
		पूर्ण
	पूर्ण
	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ QFSAttributeRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBQFSDeviceInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon)
अणु
/* level 0x104 SMB_QUERY_खाता_SYSTEM_INFO */
	TRANSACTION2_QFSI_REQ *pSMB = शून्य;
	TRANSACTION2_QFSI_RSP *pSMBr = शून्य;
	खाता_SYSTEM_DEVICE_INFO *response_data;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, byte_count;

	cअगरs_dbg(FYI, "In QFSDeviceInfo\n");
QFSDeviceRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	params = 2;	/* level */
	pSMB->TotalDataCount = 0;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find exact max SMB PDU from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(दुरत्व(
		काष्ठा smb_com_transaction2_qfsi_req, Inक्रमmationLevel) - 4);

	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_FS_INFORMATION);
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_FS_DEVICE_INFO);
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in QFSDeviceInfo = %d\n", rc);
	पूर्ण अन्यथा अणु		/* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

		अगर (rc || get_bcc(&pSMBr->hdr) <
			  माप(खाता_SYSTEM_DEVICE_INFO))
			rc = -EIO;	/* bad smb */
		अन्यथा अणु
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
			response_data =
			    (खाता_SYSTEM_DEVICE_INFO *)
				(((अक्षर *) &pSMBr->hdr.Protocol) +
				 data_offset);
			स_नकल(&tcon->fsDevInfo, response_data,
			       माप(खाता_SYSTEM_DEVICE_INFO));
		पूर्ण
	पूर्ण
	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ QFSDeviceRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBQFSUnixInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon)
अणु
/* level 0x200  SMB_QUERY_CIFS_UNIX_INFO */
	TRANSACTION2_QFSI_REQ *pSMB = शून्य;
	TRANSACTION2_QFSI_RSP *pSMBr = शून्य;
	खाता_SYSTEM_UNIX_INFO *response_data;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, byte_count;

	cअगरs_dbg(FYI, "In QFSUnixInfo\n");
QFSUnixRetry:
	rc = smb_init_no_reconnect(SMB_COM_TRANSACTION2, 15, tcon,
				   (व्योम **) &pSMB, (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	params = 2;	/* level */
	pSMB->TotalDataCount = 0;
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find exact max SMB PDU from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(100);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	byte_count = params + 1 /* pad */ ;
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(दुरत्व(काष्ठा
			smb_com_transaction2_qfsi_req, Inक्रमmationLevel) - 4);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_FS_INFORMATION);
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_CIFS_UNIX_INFO);
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "Send error in QFSUnixInfo = %d\n", rc);
	पूर्ण अन्यथा अणु		/* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

		अगर (rc || get_bcc(&pSMBr->hdr) < 13) अणु
			rc = -EIO;	/* bad smb */
		पूर्ण अन्यथा अणु
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
			response_data =
			    (खाता_SYSTEM_UNIX_INFO
			     *) (((अक्षर *) &pSMBr->hdr.Protocol) +
				 data_offset);
			स_नकल(&tcon->fsUnixInfo, response_data,
			       माप(खाता_SYSTEM_UNIX_INFO));
		पूर्ण
	पूर्ण
	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ QFSUnixRetry;


	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBSetFSUnixInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, __u64 cap)
अणु
/* level 0x200  SMB_SET_CIFS_UNIX_INFO */
	TRANSACTION2_SETFSI_REQ *pSMB = शून्य;
	TRANSACTION2_SETFSI_RSP *pSMBr = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, param_offset, offset, byte_count;

	cअगरs_dbg(FYI, "In SETFSUnixInfo\n");
SETFSUnixRetry:
	/* BB चयन to small buf init to save memory */
	rc = smb_init_no_reconnect(SMB_COM_TRANSACTION2, 15, tcon,
					(व्योम **) &pSMB, (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	params = 4;	/* 2 bytes zero followed by info level. */
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_setfsi_req, FileNum)
				- 4;
	offset = param_offset + params;

	pSMB->MaxParameterCount = cpu_to_le16(4);
	/* BB find exact max SMB PDU from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(100);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_FS_INFORMATION);
	byte_count = 1 /* pad */ + params + 12;

	pSMB->DataCount = cpu_to_le16(12);
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->DataOffset = cpu_to_le16(offset);

	/* Params. */
	pSMB->FileNum = 0;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_SET_CIFS_UNIX_INFO);

	/* Data. */
	pSMB->ClientUnixMajor = cpu_to_le16(CIFS_UNIX_MAJOR_VERSION);
	pSMB->ClientUnixMinor = cpu_to_le16(CIFS_UNIX_MINOR_VERSION);
	pSMB->ClientUnixCap = cpu_to_le64(cap);

	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "Send error in SETFSUnixInfo = %d\n", rc);
	पूर्ण अन्यथा अणु		/* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);
		अगर (rc)
			rc = -EIO;	/* bad smb */
	पूर्ण
	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ SETFSUnixRetry;

	वापस rc;
पूर्ण



पूर्णांक
CIFSSMBQFSPosixInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   काष्ठा kstatfs *FSData)
अणु
/* level 0x201  SMB_QUERY_CIFS_POSIX_INFO */
	TRANSACTION2_QFSI_REQ *pSMB = शून्य;
	TRANSACTION2_QFSI_RSP *pSMBr = शून्य;
	खाता_SYSTEM_POSIX_INFO *response_data;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, byte_count;

	cअगरs_dbg(FYI, "In QFSPosixInfo\n");
QFSPosixRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	params = 2;	/* level */
	pSMB->TotalDataCount = 0;
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find exact max SMB PDU from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(100);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	byte_count = params + 1 /* pad */ ;
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(दुरत्व(काष्ठा
			smb_com_transaction2_qfsi_req, Inक्रमmationLevel) - 4);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_FS_INFORMATION);
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_QUERY_POSIX_FS_INFO);
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in QFSUnixInfo = %d\n", rc);
	पूर्ण अन्यथा अणु		/* decode response */
		rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);

		अगर (rc || get_bcc(&pSMBr->hdr) < 13) अणु
			rc = -EIO;	/* bad smb */
		पूर्ण अन्यथा अणु
			__u16 data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
			response_data =
			    (खाता_SYSTEM_POSIX_INFO
			     *) (((अक्षर *) &pSMBr->hdr.Protocol) +
				 data_offset);
			FSData->f_bsize =
					le32_to_cpu(response_data->BlockSize);
			/*
			 * much prefer larger but अगर server करोesn't report
			 * a valid size than 4K is a reasonable minimum
			 */
			अगर (FSData->f_bsize < 512)
				FSData->f_bsize = 4096;

			FSData->f_blocks =
					le64_to_cpu(response_data->TotalBlocks);
			FSData->f_bमुक्त =
			    le64_to_cpu(response_data->BlocksAvail);
			अगर (response_data->UserBlocksAvail == cpu_to_le64(-1)) अणु
				FSData->f_bavail = FSData->f_bमुक्त;
			पूर्ण अन्यथा अणु
				FSData->f_bavail =
				    le64_to_cpu(response_data->UserBlocksAvail);
			पूर्ण
			अगर (response_data->TotalFileNodes != cpu_to_le64(-1))
				FSData->f_files =
				     le64_to_cpu(response_data->TotalFileNodes);
			अगर (response_data->FreeFileNodes != cpu_to_le64(-1))
				FSData->f_fमुक्त =
				      le64_to_cpu(response_data->FreeFileNodes);
		पूर्ण
	पूर्ण
	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ QFSPosixRetry;

	वापस rc;
पूर्ण


/*
 * We can not use ग_लिखो of zero bytes trick to set file size due to need क्रम
 * large file support. Also note that this SetPathInfo is preferred to
 * SetFileInfo based method in next routine which is only needed to work around
 * a sharing violation bugin Samba which this routine can run पूर्णांकo.
 */
पूर्णांक
CIFSSMBSetखातापूर्ण(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	      स्थिर अक्षर *file_name, __u64 size, काष्ठा cअगरs_sb_info *cअगरs_sb,
	      bool set_allocation)
अणु
	काष्ठा smb_com_transaction2_spi_req *pSMB = शून्य;
	काष्ठा smb_com_transaction2_spi_rsp *pSMBr = शून्य;
	काष्ठा file_end_of_file_info *parm_data;
	पूर्णांक name_len;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	पूर्णांक remap = cअगरs_remap(cअगरs_sb);

	__u16 params, byte_count, data_count, param_offset, offset;

	cअगरs_dbg(FYI, "In SetEOF\n");
Setखातापूर्णRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->FileName, file_name,
				       PATH_MAX, cअगरs_sb->local_nls, remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, file_name);
	पूर्ण
	params = 6 + name_len;
	data_count = माप(काष्ठा file_end_of_file_info);
	pSMB->MaxParameterCount = cpu_to_le16(2);
	pSMB->MaxDataCount = cpu_to_le16(4100);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_spi_req,
				Inक्रमmationLevel) - 4;
	offset = param_offset + params;
	अगर (set_allocation) अणु
		अगर (tcon->ses->capabilities & CAP_INFOLEVEL_PASSTHRU)
			pSMB->Inक्रमmationLevel =
				cpu_to_le16(SMB_SET_खाता_ALLOCATION_INFO2);
		अन्यथा
			pSMB->Inक्रमmationLevel =
				cpu_to_le16(SMB_SET_खाता_ALLOCATION_INFO);
	पूर्ण अन्यथा /* Set File Size */  अणु
	    अगर (tcon->ses->capabilities & CAP_INFOLEVEL_PASSTHRU)
		    pSMB->Inक्रमmationLevel =
				cpu_to_le16(SMB_SET_खाता_END_OF_खाता_INFO2);
	    अन्यथा
		    pSMB->Inक्रमmationLevel =
				cpu_to_le16(SMB_SET_खाता_END_OF_खाता_INFO);
	पूर्ण

	parm_data =
	    (काष्ठा file_end_of_file_info *) (((अक्षर *) &pSMB->hdr.Protocol) +
				       offset);
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_PATH_INFORMATION);
	byte_count = 3 /* pad */  + params + data_count;
	pSMB->DataCount = cpu_to_le16(data_count);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	parm_data->FileSize = cpu_to_le64(size);
	pSMB->ByteCount = cpu_to_le16(byte_count);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc)
		cअगरs_dbg(FYI, "SetPathInfo (file size) returned %d\n", rc);

	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ Setखातापूर्णRetry;

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBSetFileSize(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   काष्ठा cअगरsFileInfo *cfile, __u64 size, bool set_allocation)
अणु
	काष्ठा smb_com_transaction2_sfi_req *pSMB  = शून्य;
	काष्ठा file_end_of_file_info *parm_data;
	पूर्णांक rc = 0;
	__u16 params, param_offset, offset, byte_count, count;

	cअगरs_dbg(FYI, "SetFileSize (via SetFileInfo) %lld\n",
		 (दीर्घ दीर्घ)size);
	rc = small_smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB);

	अगर (rc)
		वापस rc;

	pSMB->hdr.Pid = cpu_to_le16((__u16)cfile->pid);
	pSMB->hdr.PidHigh = cpu_to_le16((__u16)(cfile->pid >> 16));

	params = 6;
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_sfi_req, Fid) - 4;
	offset = param_offset + params;

	count = माप(काष्ठा file_end_of_file_info);
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find exact max SMB PDU from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_खाता_INFORMATION);
	byte_count = 3 /* pad */  + params + count;
	pSMB->DataCount = cpu_to_le16(count);
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	parm_data =
		(काष्ठा file_end_of_file_info *) (((अक्षर *) &pSMB->hdr.Protocol)
				+ offset);
	pSMB->DataOffset = cpu_to_le16(offset);
	parm_data->FileSize = cpu_to_le64(size);
	pSMB->Fid = cfile->fid.netfid;
	अगर (set_allocation) अणु
		अगर (tcon->ses->capabilities & CAP_INFOLEVEL_PASSTHRU)
			pSMB->Inक्रमmationLevel =
				cpu_to_le16(SMB_SET_खाता_ALLOCATION_INFO2);
		अन्यथा
			pSMB->Inक्रमmationLevel =
				cpu_to_le16(SMB_SET_खाता_ALLOCATION_INFO);
	पूर्ण अन्यथा /* Set File Size */  अणु
	    अगर (tcon->ses->capabilities & CAP_INFOLEVEL_PASSTHRU)
		    pSMB->Inक्रमmationLevel =
				cpu_to_le16(SMB_SET_खाता_END_OF_खाता_INFO2);
	    अन्यथा
		    pSMB->Inक्रमmationLevel =
				cpu_to_le16(SMB_SET_खाता_END_OF_खाता_INFO);
	पूर्ण
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);
	rc = SendReceiveNoRsp(xid, tcon->ses, (अक्षर *) pSMB, 0);
	cअगरs_small_buf_release(pSMB);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in SetFileInfo (SetFileSize) = %d\n",
			 rc);
	पूर्ण

	/* Note: On -EAGAIN error only caller can retry on handle based calls
		since file handle passed in no दीर्घer valid */

	वापस rc;
पूर्ण

/* Some legacy servers such as NT4 require that the file बार be set on
   an खोलो handle, rather than by pathname - this is awkward due to
   potential access conflicts on the खोलो, but it is unaव्योमable क्रम these
   old servers since the only other choice is to go from 100 nanosecond DCE
   समय and resort to the original setpathinfo level which takes the ancient
   DOS समय क्रमmat with 2 second granularity */
पूर्णांक
CIFSSMBSetFileInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		    स्थिर खाता_BASIC_INFO *data, __u16 fid, __u32 pid_of_खोलोer)
अणु
	काष्ठा smb_com_transaction2_sfi_req *pSMB  = शून्य;
	अक्षर *data_offset;
	पूर्णांक rc = 0;
	__u16 params, param_offset, offset, byte_count, count;

	cअगरs_dbg(FYI, "Set Times (via SetFileInfo)\n");
	rc = small_smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB);

	अगर (rc)
		वापस rc;

	pSMB->hdr.Pid = cpu_to_le16((__u16)pid_of_खोलोer);
	pSMB->hdr.PidHigh = cpu_to_le16((__u16)(pid_of_खोलोer >> 16));

	params = 6;
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_sfi_req, Fid) - 4;
	offset = param_offset + params;

	data_offset = (अक्षर *)pSMB +
			दुरत्व(काष्ठा smb_hdr, Protocol) + offset;

	count = माप(खाता_BASIC_INFO);
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find max SMB PDU from sess */
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_खाता_INFORMATION);
	byte_count = 3 /* pad */  + params + count;
	pSMB->DataCount = cpu_to_le16(count);
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->Fid = fid;
	अगर (tcon->ses->capabilities & CAP_INFOLEVEL_PASSTHRU)
		pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_SET_खाता_BASIC_INFO2);
	अन्यथा
		pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_SET_खाता_BASIC_INFO);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);
	स_नकल(data_offset, data, माप(खाता_BASIC_INFO));
	rc = SendReceiveNoRsp(xid, tcon->ses, (अक्षर *) pSMB, 0);
	cअगरs_small_buf_release(pSMB);
	अगर (rc)
		cअगरs_dbg(FYI, "Send error in Set Time (SetFileInfo) = %d\n",
			 rc);

	/* Note: On -EAGAIN error only caller can retry on handle based calls
		since file handle passed in no दीर्घer valid */

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBSetFileDisposition(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			  bool delete_file, __u16 fid, __u32 pid_of_खोलोer)
अणु
	काष्ठा smb_com_transaction2_sfi_req *pSMB  = शून्य;
	अक्षर *data_offset;
	पूर्णांक rc = 0;
	__u16 params, param_offset, offset, byte_count, count;

	cअगरs_dbg(FYI, "Set File Disposition (via SetFileInfo)\n");
	rc = small_smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB);

	अगर (rc)
		वापस rc;

	pSMB->hdr.Pid = cpu_to_le16((__u16)pid_of_खोलोer);
	pSMB->hdr.PidHigh = cpu_to_le16((__u16)(pid_of_खोलोer >> 16));

	params = 6;
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_sfi_req, Fid) - 4;
	offset = param_offset + params;

	data_offset = (अक्षर *) (&pSMB->hdr.Protocol) + offset;

	count = 1;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find max SMB PDU from sess */
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_खाता_INFORMATION);
	byte_count = 3 /* pad */  + params + count;
	pSMB->DataCount = cpu_to_le16(count);
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->Fid = fid;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_SET_खाता_DISPOSITION_INFO);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);
	*data_offset = delete_file ? 1 : 0;
	rc = SendReceiveNoRsp(xid, tcon->ses, (अक्षर *) pSMB, 0);
	cअगरs_small_buf_release(pSMB);
	अगर (rc)
		cअगरs_dbg(FYI, "Send error in SetFileDisposition = %d\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक
CIFSSMBSetPathInfoFB(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     स्थिर अक्षर *fileName, स्थिर खाता_BASIC_INFO *data,
		     स्थिर काष्ठा nls_table *nls_codepage,
		     काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	पूर्णांक oplock = 0;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_fid fid;
	पूर्णांक rc;

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = GENERIC_WRITE;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.disposition = खाता_OPEN;
	oparms.path = fileName;
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = CIFS_खोलो(xid, &oparms, &oplock, शून्य);
	अगर (rc)
		जाओ out;

	rc = CIFSSMBSetFileInfo(xid, tcon, data, fid.netfid, current->tgid);
	CIFSSMBClose(xid, tcon, fid.netfid);
out:

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBSetPathInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   स्थिर अक्षर *fileName, स्थिर खाता_BASIC_INFO *data,
		   स्थिर काष्ठा nls_table *nls_codepage,
		     काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	TRANSACTION2_SPI_REQ *pSMB = शून्य;
	TRANSACTION2_SPI_RSP *pSMBr = शून्य;
	पूर्णांक name_len;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	अक्षर *data_offset;
	__u16 params, param_offset, offset, byte_count, count;
	पूर्णांक remap = cअगरs_remap(cअगरs_sb);

	cअगरs_dbg(FYI, "In SetTimes\n");

SetTimesRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->FileName, fileName,
				       PATH_MAX, nls_codepage, remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, fileName);
	पूर्ण

	params = 6 + name_len;
	count = माप(खाता_BASIC_INFO);
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find max SMB PDU from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_spi_req,
				Inक्रमmationLevel) - 4;
	offset = param_offset + params;
	data_offset = (अक्षर *) (&pSMB->hdr.Protocol) + offset;
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_PATH_INFORMATION);
	byte_count = 3 /* pad */  + params + count;

	pSMB->DataCount = cpu_to_le16(count);
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	अगर (tcon->ses->capabilities & CAP_INFOLEVEL_PASSTHRU)
		pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_SET_खाता_BASIC_INFO2);
	अन्यथा
		pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_SET_खाता_BASIC_INFO);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	स_नकल(data_offset, data, माप(खाता_BASIC_INFO));
	pSMB->ByteCount = cpu_to_le16(byte_count);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc)
		cअगरs_dbg(FYI, "SetPathInfo (times) returned %d\n", rc);

	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ SetTimesRetry;

	अगर (rc == -EOPNOTSUPP)
		वापस CIFSSMBSetPathInfoFB(xid, tcon, fileName, data,
					    nls_codepage, cअगरs_sb);

	वापस rc;
पूर्ण

अटल व्योम
cअगरs_fill_unix_set_info(खाता_UNIX_BASIC_INFO *data_offset,
			स्थिर काष्ठा cअगरs_unix_set_info_args *args)
अणु
	u64 uid = NO_CHANGE_64, gid = NO_CHANGE_64;
	u64 mode = args->mode;

	अगर (uid_valid(args->uid))
		uid = from_kuid(&init_user_ns, args->uid);
	अगर (gid_valid(args->gid))
		gid = from_kgid(&init_user_ns, args->gid);

	/*
	 * Samba server ignores set of file size to zero due to bugs in some
	 * older clients, but we should be precise - we use SetFileSize to
	 * set file size and करो not want to truncate file size to zero
	 * accidentally as happened on one Samba server beta by putting
	 * zero instead of -1 here
	 */
	data_offset->EndOfFile = cpu_to_le64(NO_CHANGE_64);
	data_offset->NumOfBytes = cpu_to_le64(NO_CHANGE_64);
	data_offset->LastStatusChange = cpu_to_le64(args->स_समय);
	data_offset->LastAccessTime = cpu_to_le64(args->aसमय);
	data_offset->LastModअगरicationTime = cpu_to_le64(args->mसमय);
	data_offset->Uid = cpu_to_le64(uid);
	data_offset->Gid = cpu_to_le64(gid);
	/* better to leave device as zero when it is  */
	data_offset->DevMajor = cpu_to_le64(MAJOR(args->device));
	data_offset->DevMinor = cpu_to_le64(MINOR(args->device));
	data_offset->Permissions = cpu_to_le64(mode);

	अगर (S_ISREG(mode))
		data_offset->Type = cpu_to_le32(UNIX_खाता);
	अन्यथा अगर (S_ISसूची(mode))
		data_offset->Type = cpu_to_le32(UNIX_सूची);
	अन्यथा अगर (S_ISLNK(mode))
		data_offset->Type = cpu_to_le32(UNIX_SYMLINK);
	अन्यथा अगर (S_ISCHR(mode))
		data_offset->Type = cpu_to_le32(UNIX_CHARDEV);
	अन्यथा अगर (S_ISBLK(mode))
		data_offset->Type = cpu_to_le32(UNIX_BLOCKDEV);
	अन्यथा अगर (S_ISFIFO(mode))
		data_offset->Type = cpu_to_le32(UNIX_FIFO);
	अन्यथा अगर (S_ISSOCK(mode))
		data_offset->Type = cpu_to_le32(UNIX_SOCKET);
पूर्ण

पूर्णांक
CIFSSMBUnixSetFileInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		       स्थिर काष्ठा cअगरs_unix_set_info_args *args,
		       u16 fid, u32 pid_of_खोलोer)
अणु
	काष्ठा smb_com_transaction2_sfi_req *pSMB  = शून्य;
	अक्षर *data_offset;
	पूर्णांक rc = 0;
	u16 params, param_offset, offset, byte_count, count;

	cअगरs_dbg(FYI, "Set Unix Info (via SetFileInfo)\n");
	rc = small_smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB);

	अगर (rc)
		वापस rc;

	pSMB->hdr.Pid = cpu_to_le16((__u16)pid_of_खोलोer);
	pSMB->hdr.PidHigh = cpu_to_le16((__u16)(pid_of_खोलोer >> 16));

	params = 6;
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_sfi_req, Fid) - 4;
	offset = param_offset + params;

	data_offset = (अक्षर *)pSMB +
			दुरत्व(काष्ठा smb_hdr, Protocol) + offset;

	count = माप(खाता_UNIX_BASIC_INFO);

	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find max SMB PDU from sess */
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_खाता_INFORMATION);
	byte_count = 3 /* pad */  + params + count;
	pSMB->DataCount = cpu_to_le16(count);
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->Fid = fid;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_SET_खाता_UNIX_BASIC);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	cअगरs_fill_unix_set_info((खाता_UNIX_BASIC_INFO *)data_offset, args);

	rc = SendReceiveNoRsp(xid, tcon->ses, (अक्षर *) pSMB, 0);
	cअगरs_small_buf_release(pSMB);
	अगर (rc)
		cअगरs_dbg(FYI, "Send error in Set Time (SetFileInfo) = %d\n",
			 rc);

	/* Note: On -EAGAIN error only caller can retry on handle based calls
		since file handle passed in no दीर्घer valid */

	वापस rc;
पूर्ण

पूर्णांक
CIFSSMBUnixSetPathInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		       स्थिर अक्षर *file_name,
		       स्थिर काष्ठा cअगरs_unix_set_info_args *args,
		       स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap)
अणु
	TRANSACTION2_SPI_REQ *pSMB = शून्य;
	TRANSACTION2_SPI_RSP *pSMBr = शून्य;
	पूर्णांक name_len;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	खाता_UNIX_BASIC_INFO *data_offset;
	__u16 params, param_offset, offset, count, byte_count;

	cअगरs_dbg(FYI, "In SetUID/GID/Mode\n");
setPermsRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->FileName, file_name,
				       PATH_MAX, nls_codepage, remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, file_name);
	पूर्ण

	params = 6 + name_len;
	count = माप(खाता_UNIX_BASIC_INFO);
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find max SMB PDU from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_spi_req,
				Inक्रमmationLevel) - 4;
	offset = param_offset + params;
	data_offset =
	    (खाता_UNIX_BASIC_INFO *) ((अक्षर *) &pSMB->hdr.Protocol +
				      offset);
	स_रखो(data_offset, 0, count);
	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_PATH_INFORMATION);
	byte_count = 3 /* pad */  + params + count;
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->DataCount = cpu_to_le16(count);
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_SET_खाता_UNIX_BASIC);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);

	cअगरs_fill_unix_set_info(data_offset, args);

	pSMB->ByteCount = cpu_to_le16(byte_count);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc)
		cअगरs_dbg(FYI, "SetPathInfo (perms) returned %d\n", rc);

	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ setPermsRetry;
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_CIFS_XATTR
/*
 * Do a path-based QUERY_ALL_EAS call and parse the result. This is a common
 * function used by listxattr and getxattr type calls. When ea_name is set,
 * it looks क्रम that attribute name and stuffs that value पूर्णांकo the EAData
 * buffer. When ea_name is शून्य, it stuffs a list of attribute names पूर्णांकo the
 * buffer. In both हालs, the वापस value is either the length of the
 * resulting data or a negative error code. If EAData is a शून्य poपूर्णांकer then
 * the data isn't copied to it, but the length is वापसed.
 */
sमाप_प्रकार
CIFSSMBQAllEAs(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		स्थिर अचिन्हित अक्षर *searchName, स्थिर अचिन्हित अक्षर *ea_name,
		अक्षर *EAData, माप_प्रकार buf_size,
		काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
		/* BB assumes one setup word */
	TRANSACTION2_QPI_REQ *pSMB = शून्य;
	TRANSACTION2_QPI_RSP *pSMBr = शून्य;
	पूर्णांक remap = cअगरs_remap(cअगरs_sb);
	काष्ठा nls_table *nls_codepage = cअगरs_sb->local_nls;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed;
	पूर्णांक list_len;
	काष्ठा fealist *ea_response_data;
	काष्ठा fea *temp_fea;
	अक्षर *temp_ptr;
	अक्षर *end_of_smb;
	__u16 params, byte_count, data_offset;
	अचिन्हित पूर्णांक ea_name_len = ea_name ? म_माप(ea_name) : 0;

	cअगरs_dbg(FYI, "In Query All EAs path %s\n", searchName);
QAllEAsRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		list_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->FileName, searchName,
				       PATH_MAX, nls_codepage, remap);
		list_len++;	/* trailing null */
		list_len *= 2;
	पूर्ण अन्यथा अणु
		list_len = copy_path_name(pSMB->FileName, searchName);
	पूर्ण

	params = 2 /* level */ + 4 /* reserved */ + list_len /* includes NUL */;
	pSMB->TotalDataCount = 0;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find exact max SMB PDU from sess काष्ठाure BB */
	pSMB->MaxDataCount = cpu_to_le16(CIFSMaxBufSize);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	pSMB->ParameterOffset = cpu_to_le16(दुरत्व(
	काष्ठा smb_com_transaction2_qpi_req, Inक्रमmationLevel) - 4);
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_QUERY_PATH_INFORMATION);
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->Inक्रमmationLevel = cpu_to_le16(SMB_INFO_QUERY_ALL_EAS);
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "Send error in QueryAllEAs = %d\n", rc);
		जाओ QAllEAsOut;
	पूर्ण


	/* BB also check enough total bytes वापसed */
	/* BB we need to improve the validity checking
	of these trans2 responses */

	rc = validate_t2((काष्ठा smb_t2_rsp *)pSMBr);
	अगर (rc || get_bcc(&pSMBr->hdr) < 4) अणु
		rc = -EIO;	/* bad smb */
		जाओ QAllEAsOut;
	पूर्ण

	/* check that length of list is not more than bcc */
	/* check that each entry करोes not go beyond length
	   of list */
	/* check that each element of each entry करोes not
	   go beyond end of list */
	/* validate_trans2_offsets() */
	/* BB check अगर start of smb + data_offset > &bcc+ bcc */

	data_offset = le16_to_cpu(pSMBr->t2.DataOffset);
	ea_response_data = (काष्ठा fealist *)
				(((अक्षर *) &pSMBr->hdr.Protocol) + data_offset);

	list_len = le32_to_cpu(ea_response_data->list_len);
	cअगरs_dbg(FYI, "ea length %d\n", list_len);
	अगर (list_len <= 8) अणु
		cअगरs_dbg(FYI, "empty EA list returned from server\n");
		/* didn't find the named attribute */
		अगर (ea_name)
			rc = -ENODATA;
		जाओ QAllEAsOut;
	पूर्ण

	/* make sure list_len करोesn't go past end of SMB */
	end_of_smb = (अक्षर *)pByteArea(&pSMBr->hdr) + get_bcc(&pSMBr->hdr);
	अगर ((अक्षर *)ea_response_data + list_len > end_of_smb) अणु
		cअगरs_dbg(FYI, "EA list appears to go beyond SMB\n");
		rc = -EIO;
		जाओ QAllEAsOut;
	पूर्ण

	/* account क्रम ea list len */
	list_len -= 4;
	temp_fea = ea_response_data->list;
	temp_ptr = (अक्षर *)temp_fea;
	जबतक (list_len > 0) अणु
		अचिन्हित पूर्णांक name_len;
		__u16 value_len;

		list_len -= 4;
		temp_ptr += 4;
		/* make sure we can पढ़ो name_len and value_len */
		अगर (list_len < 0) अणु
			cअगरs_dbg(FYI, "EA entry goes beyond length of list\n");
			rc = -EIO;
			जाओ QAllEAsOut;
		पूर्ण

		name_len = temp_fea->name_len;
		value_len = le16_to_cpu(temp_fea->value_len);
		list_len -= name_len + 1 + value_len;
		अगर (list_len < 0) अणु
			cअगरs_dbg(FYI, "EA entry goes beyond length of list\n");
			rc = -EIO;
			जाओ QAllEAsOut;
		पूर्ण

		अगर (ea_name) अणु
			अगर (ea_name_len == name_len &&
			    स_भेद(ea_name, temp_ptr, name_len) == 0) अणु
				temp_ptr += name_len + 1;
				rc = value_len;
				अगर (buf_size == 0)
					जाओ QAllEAsOut;
				अगर ((माप_प्रकार)value_len > buf_size) अणु
					rc = -दुस्फल;
					जाओ QAllEAsOut;
				पूर्ण
				स_नकल(EAData, temp_ptr, value_len);
				जाओ QAllEAsOut;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* account क्रम prefix user. and trailing null */
			rc += (5 + 1 + name_len);
			अगर (rc < (पूर्णांक) buf_size) अणु
				स_नकल(EAData, "user.", 5);
				EAData += 5;
				स_नकल(EAData, temp_ptr, name_len);
				EAData += name_len;
				/* null terminate name */
				*EAData = 0;
				++EAData;
			पूर्ण अन्यथा अगर (buf_size == 0) अणु
				/* skip copy - calc size only */
			पूर्ण अन्यथा अणु
				/* stop beक्रमe overrun buffer */
				rc = -दुस्फल;
				अवरोध;
			पूर्ण
		पूर्ण
		temp_ptr += name_len + 1 + value_len;
		temp_fea = (काष्ठा fea *)temp_ptr;
	पूर्ण

	/* didn't find the named attribute */
	अगर (ea_name)
		rc = -ENODATA;

QAllEAsOut:
	cअगरs_buf_release(pSMB);
	अगर (rc == -EAGAIN)
		जाओ QAllEAsRetry;

	वापस (sमाप_प्रकार)rc;
पूर्ण

पूर्णांक
CIFSSMBSetEA(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	     स्थिर अक्षर *fileName, स्थिर अक्षर *ea_name, स्थिर व्योम *ea_value,
	     स्थिर __u16 ea_value_len, स्थिर काष्ठा nls_table *nls_codepage,
	     काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	काष्ठा smb_com_transaction2_spi_req *pSMB = शून्य;
	काष्ठा smb_com_transaction2_spi_rsp *pSMBr = शून्य;
	काष्ठा fealist *parm_data;
	पूर्णांक name_len;
	पूर्णांक rc = 0;
	पूर्णांक bytes_वापसed = 0;
	__u16 params, param_offset, byte_count, offset, count;
	पूर्णांक remap = cअगरs_remap(cअगरs_sb);

	cअगरs_dbg(FYI, "In SetEA\n");
SetEARetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (व्योम **) &pSMB,
		      (व्योम **) &pSMBr);
	अगर (rc)
		वापस rc;

	अगर (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) अणु
		name_len =
		    cअगरsConvertToUTF16((__le16 *) pSMB->FileName, fileName,
				       PATH_MAX, nls_codepage, remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	पूर्ण अन्यथा अणु
		name_len = copy_path_name(pSMB->FileName, fileName);
	पूर्ण

	params = 6 + name_len;

	/* करोne calculating parms using name_len of file name,
	now use name_len to calculate length of ea name
	we are going to create in the inode xattrs */
	अगर (ea_name == शून्य)
		name_len = 0;
	अन्यथा
		name_len = strnlen(ea_name, 255);

	count = माप(*parm_data) + ea_value_len + name_len;
	pSMB->MaxParameterCount = cpu_to_le16(2);
	/* BB find max SMB PDU from sess */
	pSMB->MaxDataCount = cpu_to_le16(1000);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	param_offset = दुरत्व(काष्ठा smb_com_transaction2_spi_req,
				Inक्रमmationLevel) - 4;
	offset = param_offset + params;
	pSMB->Inक्रमmationLevel =
		cpu_to_le16(SMB_SET_खाता_EA);

	parm_data = (व्योम *)pSMB + दुरत्व(काष्ठा smb_hdr, Protocol) + offset;
	pSMB->ParameterOffset = cpu_to_le16(param_offset);
	pSMB->DataOffset = cpu_to_le16(offset);
	pSMB->SetupCount = 1;
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_SET_PATH_INFORMATION);
	byte_count = 3 /* pad */  + params + count;
	pSMB->DataCount = cpu_to_le16(count);
	parm_data->list_len = cpu_to_le32(count);
	parm_data->list[0].EA_flags = 0;
	/* we checked above that name len is less than 255 */
	parm_data->list[0].name_len = (__u8)name_len;
	/* EA names are always ASCII */
	अगर (ea_name)
		म_नकलन(parm_data->list[0].name, ea_name, name_len);
	parm_data->list[0].name[name_len] = 0;
	parm_data->list[0].value_len = cpu_to_le16(ea_value_len);
	/* caller ensures that ea_value_len is less than 64K but
	we need to ensure that it fits within the smb */

	/*BB add length check to see अगर it would fit in
	     negotiated SMB buffer size BB */
	/* अगर (ea_value_len > buffer_size - 512 (enough क्रम header)) */
	अगर (ea_value_len)
		स_नकल(parm_data->list[0].name+name_len+1,
		       ea_value, ea_value_len);

	pSMB->TotalDataCount = pSMB->DataCount;
	pSMB->ParameterCount = cpu_to_le16(params);
	pSMB->TotalParameterCount = pSMB->ParameterCount;
	pSMB->Reserved4 = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);
	rc = SendReceive(xid, tcon->ses, (काष्ठा smb_hdr *) pSMB,
			 (काष्ठा smb_hdr *) pSMBr, &bytes_वापसed, 0);
	अगर (rc)
		cअगरs_dbg(FYI, "SetPathInfo (EA) returned %d\n", rc);

	cअगरs_buf_release(pSMB);

	अगर (rc == -EAGAIN)
		जाओ SetEARetry;

	वापस rc;
पूर्ण
#पूर्ण_अगर
