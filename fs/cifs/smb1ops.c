<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  SMB1 (CIFS) version specअगरic operations
 *
 *  Copyright (c) 2012, Jeff Layton <jlayton@redhat.com>
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/vfs.h>
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "cifspdu.h"
#समावेश "cifs_unicode.h"
#समावेश "fs_context.h"

/*
 * An NT cancel request header looks just like the original request except:
 *
 * The Command is SMB_COM_NT_CANCEL
 * The WordCount is zeroed out
 * The ByteCount is zeroed out
 *
 * This function mangles an existing request buffer पूर्णांकo a
 * SMB_COM_NT_CANCEL request and then sends it.
 */
अटल पूर्णांक
send_nt_cancel(काष्ठा TCP_Server_Info *server, काष्ठा smb_rqst *rqst,
	       काष्ठा mid_q_entry *mid)
अणु
	पूर्णांक rc = 0;
	काष्ठा smb_hdr *in_buf = (काष्ठा smb_hdr *)rqst->rq_iov[0].iov_base;

	/* -4 क्रम RFC1001 length and +2 क्रम BCC field */
	in_buf->smb_buf_length = cpu_to_be32(माप(काष्ठा smb_hdr) - 4  + 2);
	in_buf->Command = SMB_COM_NT_CANCEL;
	in_buf->WordCount = 0;
	put_bcc(0, in_buf);

	mutex_lock(&server->srv_mutex);
	rc = cअगरs_sign_smb(in_buf, server, &mid->sequence_number);
	अगर (rc) अणु
		mutex_unlock(&server->srv_mutex);
		वापस rc;
	पूर्ण

	/*
	 * The response to this call was alपढ़ोy factored पूर्णांकo the sequence
	 * number when the call went out, so we must adjust it back करोwnward
	 * after signing here.
	 */
	--server->sequence_number;
	rc = smb_send(server, in_buf, be32_to_cpu(in_buf->smb_buf_length));
	अगर (rc < 0)
		server->sequence_number--;

	mutex_unlock(&server->srv_mutex);

	cअगरs_dbg(FYI, "issued NT_CANCEL for mid %u, rc = %d\n",
		 get_mid(in_buf), rc);

	वापस rc;
पूर्ण

अटल bool
cअगरs_compare_fids(काष्ठा cअगरsFileInfo *ob1, काष्ठा cअगरsFileInfo *ob2)
अणु
	वापस ob1->fid.netfid == ob2->fid.netfid;
पूर्ण

अटल अचिन्हित पूर्णांक
cअगरs_पढ़ो_data_offset(अक्षर *buf)
अणु
	READ_RSP *rsp = (READ_RSP *)buf;
	वापस le16_to_cpu(rsp->DataOffset);
पूर्ण

अटल अचिन्हित पूर्णांक
cअगरs_पढ़ो_data_length(अक्षर *buf, bool in_reमुख्यing)
अणु
	READ_RSP *rsp = (READ_RSP *)buf;
	/* It's a bug पढ़ोing reमुख्यing data क्रम SMB1 packets */
	WARN_ON(in_reमुख्यing);
	वापस (le16_to_cpu(rsp->DataLengthHigh) << 16) +
	       le16_to_cpu(rsp->DataLength);
पूर्ण

अटल काष्ठा mid_q_entry *
cअगरs_find_mid(काष्ठा TCP_Server_Info *server, अक्षर *buffer)
अणु
	काष्ठा smb_hdr *buf = (काष्ठा smb_hdr *)buffer;
	काष्ठा mid_q_entry *mid;

	spin_lock(&GlobalMid_Lock);
	list_क्रम_each_entry(mid, &server->pending_mid_q, qhead) अणु
		अगर (compare_mid(mid->mid, buf) &&
		    mid->mid_state == MID_REQUEST_SUBMITTED &&
		    le16_to_cpu(mid->command) == buf->Command) अणु
			kref_get(&mid->refcount);
			spin_unlock(&GlobalMid_Lock);
			वापस mid;
		पूर्ण
	पूर्ण
	spin_unlock(&GlobalMid_Lock);
	वापस शून्य;
पूर्ण

अटल व्योम
cअगरs_add_credits(काष्ठा TCP_Server_Info *server,
		 स्थिर काष्ठा cअगरs_credits *credits, स्थिर पूर्णांक optype)
अणु
	spin_lock(&server->req_lock);
	server->credits += credits->value;
	server->in_flight--;
	spin_unlock(&server->req_lock);
	wake_up(&server->request_q);
पूर्ण

अटल व्योम
cअगरs_set_credits(काष्ठा TCP_Server_Info *server, स्थिर पूर्णांक val)
अणु
	spin_lock(&server->req_lock);
	server->credits = val;
	server->oplocks = val > 1 ? enable_oplocks : false;
	spin_unlock(&server->req_lock);
पूर्ण

अटल पूर्णांक *
cअगरs_get_credits_field(काष्ठा TCP_Server_Info *server, स्थिर पूर्णांक optype)
अणु
	वापस &server->credits;
पूर्ण

अटल अचिन्हित पूर्णांक
cअगरs_get_credits(काष्ठा mid_q_entry *mid)
अणु
	वापस 1;
पूर्ण

/*
 * Find a मुक्त multiplex id (SMB mid). Otherwise there could be
 * mid collisions which might cause problems, demultiplexing the
 * wrong response to this request. Multiplex ids could collide अगर
 * one of a series requests takes much दीर्घer than the others, or
 * अगर a very large number of दीर्घ lived requests (byte range
 * locks or FindNotअगरy requests) are pending. No more than
 * 64K-1 requests can be outstanding at one समय. If no
 * mids are available, वापस zero. A future optimization
 * could make the combination of mids and uid the key we use
 * to demultiplex on (rather than mid alone).
 * In addition to the above check, the cअगरs demultiplex
 * code alपढ़ोy used the command code as a secondary
 * check of the frame and अगर signing is negotiated the
 * response would be discarded अगर the mid were the same
 * but the signature was wrong. Since the mid is not put in the
 * pending queue until later (when it is about to be dispatched)
 * we करो have to limit the number of outstanding requests
 * to somewhat less than 64K-1 although it is hard to imagine
 * so many thपढ़ोs being in the vfs at one समय.
 */
अटल __u64
cअगरs_get_next_mid(काष्ठा TCP_Server_Info *server)
अणु
	__u64 mid = 0;
	__u16 last_mid, cur_mid;
	bool collision;

	spin_lock(&GlobalMid_Lock);

	/* mid is 16 bit only क्रम CIFS/SMB */
	cur_mid = (__u16)((server->CurrentMid) & 0xffff);
	/* we करो not want to loop क्रमever */
	last_mid = cur_mid;
	cur_mid++;
	/* aव्योम 0xFFFF MID */
	अगर (cur_mid == 0xffff)
		cur_mid++;

	/*
	 * This nested loop looks more expensive than it is.
	 * In practice the list of pending requests is लघु,
	 * fewer than 50, and the mids are likely to be unique
	 * on the first pass through the loop unless some request
	 * takes दीर्घer than the 64 thousand requests beक्रमe it
	 * (and it would also have to have been a request that
	 * did not समय out).
	 */
	जबतक (cur_mid != last_mid) अणु
		काष्ठा mid_q_entry *mid_entry;
		अचिन्हित पूर्णांक num_mids;

		collision = false;
		अगर (cur_mid == 0)
			cur_mid++;

		num_mids = 0;
		list_क्रम_each_entry(mid_entry, &server->pending_mid_q, qhead) अणु
			++num_mids;
			अगर (mid_entry->mid == cur_mid &&
			    mid_entry->mid_state == MID_REQUEST_SUBMITTED) अणु
				/* This mid is in use, try a dअगरferent one */
				collision = true;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * अगर we have more than 32k mids in the list, then something
		 * is very wrong. Possibly a local user is trying to DoS the
		 * box by issuing दीर्घ-running calls and SIGKILL'ing them. If
		 * we get to 2^16 mids then we're in big trouble as this
		 * function could loop क्रमever.
		 *
		 * Go ahead and assign out the mid in this situation, but क्रमce
		 * an eventual reconnect to clean out the pending_mid_q.
		 */
		अगर (num_mids > 32768)
			server->tcpStatus = CअगरsNeedReconnect;

		अगर (!collision) अणु
			mid = (__u64)cur_mid;
			server->CurrentMid = mid;
			अवरोध;
		पूर्ण
		cur_mid++;
	पूर्ण
	spin_unlock(&GlobalMid_Lock);
	वापस mid;
पूर्ण

/*
	वापस codes:
		0	not a transact2, or all data present
		>0	transact2 with that much data missing
		-EINVAL	invalid transact2
 */
अटल पूर्णांक
check2ndT2(अक्षर *buf)
अणु
	काष्ठा smb_hdr *pSMB = (काष्ठा smb_hdr *)buf;
	काष्ठा smb_t2_rsp *pSMBt;
	पूर्णांक reमुख्यing;
	__u16 total_data_size, data_in_this_rsp;

	अगर (pSMB->Command != SMB_COM_TRANSACTION2)
		वापस 0;

	/* check क्रम plausible wct, bcc and t2 data and parm sizes */
	/* check क्रम parm and data offset going beyond end of smb */
	अगर (pSMB->WordCount != 10) अणु /* coalesce_t2 depends on this */
		cअगरs_dbg(FYI, "Invalid transact2 word count\n");
		वापस -EINVAL;
	पूर्ण

	pSMBt = (काष्ठा smb_t2_rsp *)pSMB;

	total_data_size = get_unaligned_le16(&pSMBt->t2_rsp.TotalDataCount);
	data_in_this_rsp = get_unaligned_le16(&pSMBt->t2_rsp.DataCount);

	अगर (total_data_size == data_in_this_rsp)
		वापस 0;
	अन्यथा अगर (total_data_size < data_in_this_rsp) अणु
		cअगरs_dbg(FYI, "total data %d smaller than data in frame %d\n",
			 total_data_size, data_in_this_rsp);
		वापस -EINVAL;
	पूर्ण

	reमुख्यing = total_data_size - data_in_this_rsp;

	cअगरs_dbg(FYI, "missing %d bytes from transact2, check next response\n",
		 reमुख्यing);
	अगर (total_data_size > CIFSMaxBufSize) अणु
		cअगरs_dbg(VFS, "TotalDataSize %d is over maximum buffer %d\n",
			 total_data_size, CIFSMaxBufSize);
		वापस -EINVAL;
	पूर्ण
	वापस reमुख्यing;
पूर्ण

अटल पूर्णांक
coalesce_t2(अक्षर *second_buf, काष्ठा smb_hdr *target_hdr)
अणु
	काष्ठा smb_t2_rsp *pSMBs = (काष्ठा smb_t2_rsp *)second_buf;
	काष्ठा smb_t2_rsp *pSMBt  = (काष्ठा smb_t2_rsp *)target_hdr;
	अक्षर *data_area_of_tgt;
	अक्षर *data_area_of_src;
	पूर्णांक reमुख्यing;
	अचिन्हित पूर्णांक byte_count, total_in_tgt;
	__u16 tgt_total_cnt, src_total_cnt, total_in_src;

	src_total_cnt = get_unaligned_le16(&pSMBs->t2_rsp.TotalDataCount);
	tgt_total_cnt = get_unaligned_le16(&pSMBt->t2_rsp.TotalDataCount);

	अगर (tgt_total_cnt != src_total_cnt)
		cअगरs_dbg(FYI, "total data count of primary and secondary t2 differ source=%hu target=%hu\n",
			 src_total_cnt, tgt_total_cnt);

	total_in_tgt = get_unaligned_le16(&pSMBt->t2_rsp.DataCount);

	reमुख्यing = tgt_total_cnt - total_in_tgt;

	अगर (reमुख्यing < 0) अणु
		cअगरs_dbg(FYI, "Server sent too much data. tgt_total_cnt=%hu total_in_tgt=%u\n",
			 tgt_total_cnt, total_in_tgt);
		वापस -EPROTO;
	पूर्ण

	अगर (reमुख्यing == 0) अणु
		/* nothing to करो, ignore */
		cअगरs_dbg(FYI, "no more data remains\n");
		वापस 0;
	पूर्ण

	total_in_src = get_unaligned_le16(&pSMBs->t2_rsp.DataCount);
	अगर (reमुख्यing < total_in_src)
		cअगरs_dbg(FYI, "transact2 2nd response contains too much data\n");

	/* find end of first SMB data area */
	data_area_of_tgt = (अक्षर *)&pSMBt->hdr.Protocol +
				get_unaligned_le16(&pSMBt->t2_rsp.DataOffset);

	/* validate target area */
	data_area_of_src = (अक्षर *)&pSMBs->hdr.Protocol +
				get_unaligned_le16(&pSMBs->t2_rsp.DataOffset);

	data_area_of_tgt += total_in_tgt;

	total_in_tgt += total_in_src;
	/* is the result too big क्रम the field? */
	अगर (total_in_tgt > अच_लघु_उच्च) अणु
		cअगरs_dbg(FYI, "coalesced DataCount too large (%u)\n",
			 total_in_tgt);
		वापस -EPROTO;
	पूर्ण
	put_unaligned_le16(total_in_tgt, &pSMBt->t2_rsp.DataCount);

	/* fix up the BCC */
	byte_count = get_bcc(target_hdr);
	byte_count += total_in_src;
	/* is the result too big क्रम the field? */
	अगर (byte_count > अच_लघु_उच्च) अणु
		cअगरs_dbg(FYI, "coalesced BCC too large (%u)\n", byte_count);
		वापस -EPROTO;
	पूर्ण
	put_bcc(byte_count, target_hdr);

	byte_count = be32_to_cpu(target_hdr->smb_buf_length);
	byte_count += total_in_src;
	/* करोn't allow buffer to overflow */
	अगर (byte_count > CIFSMaxBufSize + MAX_CIFS_HDR_SIZE - 4) अणु
		cअगरs_dbg(FYI, "coalesced BCC exceeds buffer size (%u)\n",
			 byte_count);
		वापस -ENOBUFS;
	पूर्ण
	target_hdr->smb_buf_length = cpu_to_be32(byte_count);

	/* copy second buffer पूर्णांकo end of first buffer */
	स_नकल(data_area_of_tgt, data_area_of_src, total_in_src);

	अगर (reमुख्यing != total_in_src) अणु
		/* more responses to go */
		cअगरs_dbg(FYI, "waiting for more secondary responses\n");
		वापस 1;
	पूर्ण

	/* we are करोne */
	cअगरs_dbg(FYI, "found the last secondary response\n");
	वापस 0;
पूर्ण

अटल व्योम
cअगरs_करोwngrade_oplock(काष्ठा TCP_Server_Info *server,
		      काष्ठा cअगरsInodeInfo *cinode, __u32 oplock,
		      अचिन्हित पूर्णांक epoch, bool *purge_cache)
अणु
	cअगरs_set_oplock_level(cinode, oplock);
पूर्ण

अटल bool
cअगरs_check_trans2(काष्ठा mid_q_entry *mid, काष्ठा TCP_Server_Info *server,
		  अक्षर *buf, पूर्णांक malक्रमmed)
अणु
	अगर (malक्रमmed)
		वापस false;
	अगर (check2ndT2(buf) <= 0)
		वापस false;
	mid->multiRsp = true;
	अगर (mid->resp_buf) अणु
		/* merge response - fix up 1st*/
		malक्रमmed = coalesce_t2(buf, mid->resp_buf);
		अगर (malक्रमmed > 0)
			वापस true;
		/* All parts received or packet is malक्रमmed. */
		mid->multiEnd = true;
		dequeue_mid(mid, malक्रमmed);
		वापस true;
	पूर्ण
	अगर (!server->large_buf) अणु
		/*FIXME: चयन to alपढ़ोy allocated largebuf?*/
		cअगरs_dbg(VFS, "1st trans2 resp needs bigbuf\n");
	पूर्ण अन्यथा अणु
		/* Have first buffer */
		mid->resp_buf = buf;
		mid->large_buf = true;
		server->bigbuf = शून्य;
	पूर्ण
	वापस true;
पूर्ण

अटल bool
cअगरs_need_neg(काष्ठा TCP_Server_Info *server)
अणु
	वापस server->maxBuf == 0;
पूर्ण

अटल पूर्णांक
cअगरs_negotiate(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses)
अणु
	पूर्णांक rc;
	rc = CIFSSMBNegotiate(xid, ses);
	अगर (rc == -EAGAIN) अणु
		/* retry only once on 1st समय connection */
		set_credits(ses->server, 1);
		rc = CIFSSMBNegotiate(xid, ses);
		अगर (rc == -EAGAIN)
			rc = -EHOSTDOWN;
	पूर्ण
	वापस rc;
पूर्ण

अटल अचिन्हित पूर्णांक
cअगरs_negotiate_wsize(काष्ठा cअगरs_tcon *tcon, काष्ठा smb3_fs_context *ctx)
अणु
	__u64 unix_cap = le64_to_cpu(tcon->fsUnixInfo.Capability);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	अचिन्हित पूर्णांक wsize;

	/* start with specअगरied wsize, or शेष */
	अगर (ctx->wsize)
		wsize = ctx->wsize;
	अन्यथा अगर (tcon->unix_ext && (unix_cap & CIFS_UNIX_LARGE_WRITE_CAP))
		wsize = CIFS_DEFAULT_IOSIZE;
	अन्यथा
		wsize = CIFS_DEFAULT_NON_POSIX_WSIZE;

	/* can server support 24-bit ग_लिखो sizes? (via UNIX extensions) */
	अगर (!tcon->unix_ext || !(unix_cap & CIFS_UNIX_LARGE_WRITE_CAP))
		wsize = min_t(अचिन्हित पूर्णांक, wsize, CIFS_MAX_RFC1002_WSIZE);

	/*
	 * no CAP_LARGE_WRITE_X or is signing enabled without CAP_UNIX set?
	 * Limit it to max buffer offered by the server, minus the size of the
	 * WRITEX header, not including the 4 byte RFC1001 length.
	 */
	अगर (!(server->capabilities & CAP_LARGE_WRITE_X) ||
	    (!(server->capabilities & CAP_UNIX) && server->sign))
		wsize = min_t(अचिन्हित पूर्णांक, wsize,
				server->maxBuf - माप(WRITE_REQ) + 4);

	/* hard limit of CIFS_MAX_WSIZE */
	wsize = min_t(अचिन्हित पूर्णांक, wsize, CIFS_MAX_WSIZE);

	वापस wsize;
पूर्ण

अटल अचिन्हित पूर्णांक
cअगरs_negotiate_rsize(काष्ठा cअगरs_tcon *tcon, काष्ठा smb3_fs_context *ctx)
अणु
	__u64 unix_cap = le64_to_cpu(tcon->fsUnixInfo.Capability);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	अचिन्हित पूर्णांक rsize, defsize;

	/*
	 * Set शेष value...
	 *
	 * HACK alert! Ancient servers have very small buffers. Even though
	 * MS-CIFS indicates that servers are only limited by the client's
	 * bufsize क्रम पढ़ोs, testing against win98se shows that it throws
	 * INVALID_PARAMETER errors अगर you try to request too large a पढ़ो.
	 * OS/2 just sends back लघु पढ़ोs.
	 *
	 * If the server करोesn't advertise CAP_LARGE_READ_X, then assume that
	 * it can't handle a पढ़ो request larger than its MaxBufferSize either.
	 */
	अगर (tcon->unix_ext && (unix_cap & CIFS_UNIX_LARGE_READ_CAP))
		defsize = CIFS_DEFAULT_IOSIZE;
	अन्यथा अगर (server->capabilities & CAP_LARGE_READ_X)
		defsize = CIFS_DEFAULT_NON_POSIX_RSIZE;
	अन्यथा
		defsize = server->maxBuf - माप(READ_RSP);

	rsize = ctx->rsize ? ctx->rsize : defsize;

	/*
	 * no CAP_LARGE_READ_X? Then MS-CIFS states that we must limit this to
	 * the client's MaxBufferSize.
	 */
	अगर (!(server->capabilities & CAP_LARGE_READ_X))
		rsize = min_t(अचिन्हित पूर्णांक, CIFSMaxBufSize, rsize);

	/* hard limit of CIFS_MAX_RSIZE */
	rsize = min_t(अचिन्हित पूर्णांक, rsize, CIFS_MAX_RSIZE);

	वापस rsize;
पूर्ण

अटल व्योम
cअगरs_qfs_tcon(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	      काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	CIFSSMBQFSDeviceInfo(xid, tcon);
	CIFSSMBQFSAttributeInfo(xid, tcon);
पूर्ण

अटल पूर्णांक
cअगरs_is_path_accessible(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *full_path)
अणु
	पूर्णांक rc;
	खाता_ALL_INFO *file_info;

	file_info = kदो_स्मृति(माप(खाता_ALL_INFO), GFP_KERNEL);
	अगर (file_info == शून्य)
		वापस -ENOMEM;

	rc = CIFSSMBQPathInfo(xid, tcon, full_path, file_info,
			      0 /* not legacy */, cअगरs_sb->local_nls,
			      cअगरs_remap(cअगरs_sb));

	अगर (rc == -EOPNOTSUPP || rc == -EINVAL)
		rc = SMBQueryInक्रमmation(xid, tcon, full_path, file_info,
				cअगरs_sb->local_nls, cअगरs_remap(cअगरs_sb));
	kमुक्त(file_info);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_query_path_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *full_path,
		     खाता_ALL_INFO *data, bool *adjustTZ, bool *symlink)
अणु
	पूर्णांक rc;

	*symlink = false;

	/* could करो find first instead but this वापसs more info */
	rc = CIFSSMBQPathInfo(xid, tcon, full_path, data, 0 /* not legacy */,
			      cअगरs_sb->local_nls, cअगरs_remap(cअगरs_sb));
	/*
	 * BB optimize code so we करो not make the above call when server claims
	 * no NT SMB support and the above call failed at least once - set flag
	 * in tcon or mount.
	 */
	अगर ((rc == -EOPNOTSUPP) || (rc == -EINVAL)) अणु
		rc = SMBQueryInक्रमmation(xid, tcon, full_path, data,
					 cअगरs_sb->local_nls,
					 cअगरs_remap(cअगरs_sb));
		*adjustTZ = true;
	पूर्ण

	अगर (!rc && (le32_to_cpu(data->Attributes) & ATTR_REPARSE)) अणु
		पूर्णांक पंचांगprc;
		पूर्णांक oplock = 0;
		काष्ठा cअगरs_fid fid;
		काष्ठा cअगरs_खोलो_parms oparms;

		oparms.tcon = tcon;
		oparms.cअगरs_sb = cअगरs_sb;
		oparms.desired_access = खाता_READ_ATTRIBUTES;
		oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
		oparms.disposition = खाता_OPEN;
		oparms.path = full_path;
		oparms.fid = &fid;
		oparms.reconnect = false;

		/* Need to check अगर this is a symbolic link or not */
		पंचांगprc = CIFS_खोलो(xid, &oparms, &oplock, शून्य);
		अगर (पंचांगprc == -EOPNOTSUPP)
			*symlink = true;
		अन्यथा अगर (पंचांगprc == 0)
			CIFSSMBClose(xid, tcon, fid.netfid);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_get_srv_inum(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		  काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *full_path,
		  u64 *uniqueid, खाता_ALL_INFO *data)
अणु
	/*
	 * We can not use the IndexNumber field by शेष from Winकरोws or
	 * Samba (in ALL_INFO buf) but we can request it explicitly. The SNIA
	 * CIFS spec claims that this value is unique within the scope of a
	 * share, and the winकरोws करोcs hपूर्णांक that it's actually unique
	 * per-machine.
	 *
	 * There may be higher info levels that work but are there Winकरोws
	 * server or network appliances क्रम which IndexNumber field is not
	 * guaranteed unique?
	 */
	वापस CIFSGetSrvInodeNumber(xid, tcon, full_path, uniqueid,
				     cअगरs_sb->local_nls,
				     cअगरs_remap(cअगरs_sb));
पूर्ण

अटल पूर्णांक
cअगरs_query_file_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     काष्ठा cअगरs_fid *fid, खाता_ALL_INFO *data)
अणु
	वापस CIFSSMBQFileInfo(xid, tcon, fid->netfid, data);
पूर्ण

अटल व्योम
cअगरs_clear_stats(काष्ठा cअगरs_tcon *tcon)
अणु
	atomic_set(&tcon->stats.cअगरs_stats.num_ग_लिखोs, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_पढ़ोs, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_flushes, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_oplock_brks, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_खोलोs, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_posixखोलोs, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_posixसूची_गढ़ोs, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_बंदs, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_deletes, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_सूची_गढ़ोs, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_सूची_हटाओs, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_नामs, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_t2नामs, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_ffirst, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_fnext, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_ख_बंद, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_hardlinks, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_symlinks, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_locks, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_acl_get, 0);
	atomic_set(&tcon->stats.cअगरs_stats.num_acl_set, 0);
पूर्ण

अटल व्योम
cअगरs_prपूर्णांक_stats(काष्ठा seq_file *m, काष्ठा cअगरs_tcon *tcon)
अणु
	seq_म_लिखो(m, " Oplocks breaks: %d",
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_oplock_brks));
	seq_म_लिखो(m, "\nReads:  %d Bytes: %llu",
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_पढ़ोs),
		   (दीर्घ दीर्घ)(tcon->bytes_पढ़ो));
	seq_म_लिखो(m, "\nWrites: %d Bytes: %llu",
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_ग_लिखोs),
		   (दीर्घ दीर्घ)(tcon->bytes_written));
	seq_म_लिखो(m, "\nFlushes: %d",
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_flushes));
	seq_म_लिखो(m, "\nLocks: %d HardLinks: %d Symlinks: %d",
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_locks),
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_hardlinks),
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_symlinks));
	seq_म_लिखो(m, "\nOpens: %d Closes: %d Deletes: %d",
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_खोलोs),
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_बंदs),
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_deletes));
	seq_म_लिखो(m, "\nPosix Opens: %d Posix Mkdirs: %d",
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_posixखोलोs),
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_posixसूची_गढ़ोs));
	seq_म_लिखो(m, "\nMkdirs: %d Rmdirs: %d",
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_सूची_गढ़ोs),
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_सूची_हटाओs));
	seq_म_लिखो(m, "\nRenames: %d T2 Renames %d",
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_नामs),
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_t2नामs));
	seq_म_लिखो(m, "\nFindFirst: %d FNext %d FClose %d",
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_ffirst),
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_fnext),
		   atomic_पढ़ो(&tcon->stats.cअगरs_stats.num_ख_बंद));
पूर्ण

अटल व्योम
cअगरs_सूची_गढ़ो_setinfo(काष्ठा inode *inode, स्थिर अक्षर *full_path,
		   काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा cअगरs_tcon *tcon,
		   स्थिर अचिन्हित पूर्णांक xid)
अणु
	खाता_BASIC_INFO info;
	काष्ठा cअगरsInodeInfo *cअगरsInode;
	u32 करोsattrs;
	पूर्णांक rc;

	स_रखो(&info, 0, माप(info));
	cअगरsInode = CIFS_I(inode);
	करोsattrs = cअगरsInode->cअगरsAttrs|ATTR_READONLY;
	info.Attributes = cpu_to_le32(करोsattrs);
	rc = CIFSSMBSetPathInfo(xid, tcon, full_path, &info, cअगरs_sb->local_nls,
				cअगरs_sb);
	अगर (rc == 0)
		cअगरsInode->cअगरsAttrs = करोsattrs;
पूर्ण

अटल पूर्णांक
cअगरs_खोलो_file(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_खोलो_parms *oparms,
	       __u32 *oplock, खाता_ALL_INFO *buf)
अणु
	अगर (!(oparms->tcon->ses->capabilities & CAP_NT_SMBS))
		वापस SMBLegacyOpen(xid, oparms->tcon, oparms->path,
				     oparms->disposition,
				     oparms->desired_access,
				     oparms->create_options,
				     &oparms->fid->netfid, oplock, buf,
				     oparms->cअगरs_sb->local_nls,
				     cअगरs_remap(oparms->cअगरs_sb));
	वापस CIFS_खोलो(xid, oparms, oplock, buf);
पूर्ण

अटल व्योम
cअगरs_set_fid(काष्ठा cअगरsFileInfo *cfile, काष्ठा cअगरs_fid *fid, __u32 oplock)
अणु
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	cfile->fid.netfid = fid->netfid;
	cअगरs_set_oplock_level(cinode, oplock);
	cinode->can_cache_brlcks = CIFS_CACHE_WRITE(cinode);
पूर्ण

अटल व्योम
cअगरs_बंद_file(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		काष्ठा cअगरs_fid *fid)
अणु
	CIFSSMBClose(xid, tcon, fid->netfid);
पूर्ण

अटल पूर्णांक
cअगरs_flush_file(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		काष्ठा cअगरs_fid *fid)
अणु
	वापस CIFSSMBFlush(xid, tcon, fid->netfid);
पूर्ण

अटल पूर्णांक
cअगरs_sync_पढ़ो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_fid *pfid,
	       काष्ठा cअगरs_io_parms *parms, अचिन्हित पूर्णांक *bytes_पढ़ो,
	       अक्षर **buf, पूर्णांक *buf_type)
अणु
	parms->netfid = pfid->netfid;
	वापस CIFSSMBRead(xid, parms, bytes_पढ़ो, buf, buf_type);
पूर्ण

अटल पूर्णांक
cअगरs_sync_ग_लिखो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_fid *pfid,
		काष्ठा cअगरs_io_parms *parms, अचिन्हित पूर्णांक *written,
		काष्ठा kvec *iov, अचिन्हित दीर्घ nr_segs)
अणु

	parms->netfid = pfid->netfid;
	वापस CIFSSMBWrite2(xid, parms, written, iov, nr_segs);
पूर्ण

अटल पूर्णांक
smb_set_file_info(काष्ठा inode *inode, स्थिर अक्षर *full_path,
		  खाता_BASIC_INFO *buf, स्थिर अचिन्हित पूर्णांक xid)
अणु
	पूर्णांक oplock = 0;
	पूर्णांक rc;
	__u32 netpid;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरsFileInfo *खोलो_file;
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(inode);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा tcon_link *tlink = शून्य;
	काष्ठा cअगरs_tcon *tcon;

	/* अगर the file is alपढ़ोy खोलो क्रम ग_लिखो, just use that fileid */
	खोलो_file = find_writable_file(cinode, FIND_WR_FSUID_ONLY);
	अगर (खोलो_file) अणु
		fid.netfid = खोलो_file->fid.netfid;
		netpid = खोलो_file->pid;
		tcon = tlink_tcon(खोलो_file->tlink);
		जाओ set_via_filehandle;
	पूर्ण

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink)) अणु
		rc = PTR_ERR(tlink);
		tlink = शून्य;
		जाओ out;
	पूर्ण
	tcon = tlink_tcon(tlink);

	rc = CIFSSMBSetPathInfo(xid, tcon, full_path, buf, cअगरs_sb->local_nls,
				cअगरs_sb);
	अगर (rc == 0) अणु
		cinode->cअगरsAttrs = le32_to_cpu(buf->Attributes);
		जाओ out;
	पूर्ण अन्यथा अगर (rc != -EOPNOTSUPP && rc != -EINVAL) अणु
		जाओ out;
	पूर्ण

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = SYNCHRONIZE | खाता_WRITE_ATTRIBUTES;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, CREATE_NOT_सूची);
	oparms.disposition = खाता_OPEN;
	oparms.path = full_path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	cअगरs_dbg(FYI, "calling SetFileInfo since SetPathInfo for times not supported by this server\n");
	rc = CIFS_खोलो(xid, &oparms, &oplock, शून्य);
	अगर (rc != 0) अणु
		अगर (rc == -EIO)
			rc = -EINVAL;
		जाओ out;
	पूर्ण

	netpid = current->tgid;

set_via_filehandle:
	rc = CIFSSMBSetFileInfo(xid, tcon, buf, fid.netfid, netpid);
	अगर (!rc)
		cinode->cअगरsAttrs = le32_to_cpu(buf->Attributes);

	अगर (खोलो_file == शून्य)
		CIFSSMBClose(xid, tcon, fid.netfid);
	अन्यथा
		cअगरsFileInfo_put(खोलो_file);
out:
	अगर (tlink != शून्य)
		cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_set_compression(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   काष्ठा cअगरsFileInfo *cfile)
अणु
	वापस CIFSSMB_set_compression(xid, tcon, cfile->fid.netfid);
पूर्ण

अटल पूर्णांक
cअगरs_query_dir_first(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     स्थिर अक्षर *path, काष्ठा cअगरs_sb_info *cअगरs_sb,
		     काष्ठा cअगरs_fid *fid, __u16 search_flags,
		     काष्ठा cअगरs_search_info *srch_inf)
अणु
	पूर्णांक rc;

	rc = CIFSFindFirst(xid, tcon, path, cअगरs_sb,
			   &fid->netfid, search_flags, srch_inf, true);
	अगर (rc)
		cअगरs_dbg(FYI, "find first failed=%d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_query_dir_next(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		    काष्ठा cअगरs_fid *fid, __u16 search_flags,
		    काष्ठा cअगरs_search_info *srch_inf)
अणु
	वापस CIFSFindNext(xid, tcon, fid->netfid, search_flags, srch_inf);
पूर्ण

अटल पूर्णांक
cअगरs_बंद_dir(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	       काष्ठा cअगरs_fid *fid)
अणु
	वापस CIFSFindClose(xid, tcon, fid->netfid);
पूर्ण

अटल पूर्णांक
cअगरs_oplock_response(काष्ठा cअगरs_tcon *tcon, काष्ठा cअगरs_fid *fid,
		     काष्ठा cअगरsInodeInfo *cinode)
अणु
	वापस CIFSSMBLock(0, tcon, fid->netfid, current->tgid, 0, 0, 0, 0,
			   LOCKING_ANDX_OPLOCK_RELEASE, false,
			   CIFS_CACHE_READ(cinode) ? 1 : 0);
पूर्ण

अटल पूर्णांक
cअगरs_queryfs(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
	     काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा kstatfs *buf)
अणु
	पूर्णांक rc = -EOPNOTSUPP;

	buf->f_type = CIFS_MAGIC_NUMBER;

	/*
	 * We could add a second check क्रम a QFS Unix capability bit
	 */
	अगर ((tcon->ses->capabilities & CAP_UNIX) &&
	    (CIFS_POSIX_EXTENSIONS & le64_to_cpu(tcon->fsUnixInfo.Capability)))
		rc = CIFSSMBQFSPosixInfo(xid, tcon, buf);

	/*
	 * Only need to call the old QFSInfo अगर failed on newer one,
	 * e.g. by OS/2.
	 **/
	अगर (rc && (tcon->ses->capabilities & CAP_NT_SMBS))
		rc = CIFSSMBQFSInfo(xid, tcon, buf);

	/*
	 * Some old Winकरोws servers also करो not support level 103, retry with
	 * older level one अगर old server failed the previous call or we
	 * bypassed it because we detected that this was an older LANMAN sess
	 */
	अगर (rc)
		rc = SMBOldQFSInfo(xid, tcon, buf);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_mand_lock(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरsFileInfo *cfile, __u64 offset,
	       __u64 length, __u32 type, पूर्णांक lock, पूर्णांक unlock, bool रुको)
अणु
	वापस CIFSSMBLock(xid, tlink_tcon(cfile->tlink), cfile->fid.netfid,
			   current->tgid, length, offset, unlock, lock,
			   (__u8)type, रुको, 0);
पूर्ण

अटल पूर्णांक
cअगरs_unix_dfs_पढ़ोlink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		       स्थिर अचिन्हित अक्षर *searchName, अक्षर **symlinkinfo,
		       स्थिर काष्ठा nls_table *nls_codepage)
अणु
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	पूर्णांक rc;
	काष्ठा dfs_info3_param referral = अणु0पूर्ण;

	rc = get_dfs_path(xid, tcon->ses, searchName, nls_codepage, &referral,
			  0);

	अगर (!rc) अणु
		*symlinkinfo = kstrdup(referral.node_name, GFP_KERNEL);
		मुक्त_dfs_info_param(&referral);
		अगर (!*symlinkinfo)
			rc = -ENOMEM;
	पूर्ण
	वापस rc;
#अन्यथा /* No DFS support */
	वापस -EREMOTE;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
cअगरs_query_symlink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *full_path,
		   अक्षर **target_path, bool is_reparse_poपूर्णांक)
अणु
	पूर्णांक rc;
	पूर्णांक oplock = 0;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;

	cअगरs_dbg(FYI, "%s: path: %s\n", __func__, full_path);

	अगर (is_reparse_poपूर्णांक) अणु
		cअगरs_dbg(VFS, "reparse points not handled for SMB1 symlinks\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Check क्रम unix extensions */
	अगर (cap_unix(tcon->ses)) अणु
		rc = CIFSSMBUnixQuerySymLink(xid, tcon, full_path, target_path,
					     cअगरs_sb->local_nls,
					     cअगरs_remap(cअगरs_sb));
		अगर (rc == -EREMOTE)
			rc = cअगरs_unix_dfs_पढ़ोlink(xid, tcon, full_path,
						    target_path,
						    cअगरs_sb->local_nls);

		जाओ out;
	पूर्ण

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = खाता_READ_ATTRIBUTES;
	oparms.create_options = cअगरs_create_options(cअगरs_sb,
						    OPEN_REPARSE_POINT);
	oparms.disposition = खाता_OPEN;
	oparms.path = full_path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = CIFS_खोलो(xid, &oparms, &oplock, शून्य);
	अगर (rc)
		जाओ out;

	rc = CIFSSMBQuerySymLink(xid, tcon, fid.netfid, target_path,
				 cअगरs_sb->local_nls);
	अगर (rc)
		जाओ out_बंद;

	convert_delimiter(*target_path, '/');
out_बंद:
	CIFSSMBClose(xid, tcon, fid.netfid);
out:
	अगर (!rc)
		cअगरs_dbg(FYI, "%s: target path: %s\n", __func__, *target_path);
	वापस rc;
पूर्ण

अटल bool
cअगरs_is_पढ़ो_op(__u32 oplock)
अणु
	वापस oplock == OPLOCK_READ;
पूर्ण

अटल अचिन्हित पूर्णांक
cअगरs_wp_retry_size(काष्ठा inode *inode)
अणु
	वापस CIFS_SB(inode->i_sb)->ctx->wsize;
पूर्ण

अटल bool
cअगरs_dir_needs_बंद(काष्ठा cअगरsFileInfo *cfile)
अणु
	वापस !cfile->srch_inf.endOfSearch && !cfile->invalidHandle;
पूर्ण

अटल bool
cअगरs_can_echo(काष्ठा TCP_Server_Info *server)
अणु
	अगर (server->tcpStatus == CअगरsGood)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक
cअगरs_make_node(अचिन्हित पूर्णांक xid, काष्ठा inode *inode,
	       काष्ठा dentry *dentry, काष्ठा cअगरs_tcon *tcon,
	       स्थिर अक्षर *full_path, umode_t mode, dev_t dev)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा inode *newinode = शून्य;
	पूर्णांक rc = -EPERM;
	खाता_ALL_INFO *buf = शून्य;
	काष्ठा cअगरs_io_parms io_parms;
	__u32 oplock = 0;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;
	अचिन्हित पूर्णांक bytes_written;
	काष्ठा win_dev *pdev;
	काष्ठा kvec iov[2];

	अगर (tcon->unix_ext) अणु
		/*
		 * SMB1 Unix Extensions: requires server support but
		 * works with all special files
		 */
		काष्ठा cअगरs_unix_set_info_args args = अणु
			.mode	= mode & ~current_umask(),
			.स_समय	= NO_CHANGE_64,
			.aसमय	= NO_CHANGE_64,
			.mसमय	= NO_CHANGE_64,
			.device	= dev,
		पूर्ण;
		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SET_UID) अणु
			args.uid = current_fsuid();
			args.gid = current_fsgid();
		पूर्ण अन्यथा अणु
			args.uid = INVALID_UID; /* no change */
			args.gid = INVALID_GID; /* no change */
		पूर्ण
		rc = CIFSSMBUnixSetPathInfo(xid, tcon, full_path, &args,
					    cअगरs_sb->local_nls,
					    cअगरs_remap(cअगरs_sb));
		अगर (rc)
			जाओ out;

		rc = cअगरs_get_inode_info_unix(&newinode, full_path,
					      inode->i_sb, xid);

		अगर (rc == 0)
			d_instantiate(dentry, newinode);
		जाओ out;
	पूर्ण

	/*
	 * SMB1 SFU emulation: should work with all servers, but only
	 * support block and अक्षर device (no socket & fअगरo)
	 */
	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_UNX_EMUL))
		जाओ out;

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



काष्ठा smb_version_operations smb1_operations = अणु
	.send_cancel = send_nt_cancel,
	.compare_fids = cअगरs_compare_fids,
	.setup_request = cअगरs_setup_request,
	.setup_async_request = cअगरs_setup_async_request,
	.check_receive = cअगरs_check_receive,
	.add_credits = cअगरs_add_credits,
	.set_credits = cअगरs_set_credits,
	.get_credits_field = cअगरs_get_credits_field,
	.get_credits = cअगरs_get_credits,
	.रुको_mtu_credits = cअगरs_रुको_mtu_credits,
	.get_next_mid = cअगरs_get_next_mid,
	.पढ़ो_data_offset = cअगरs_पढ़ो_data_offset,
	.पढ़ो_data_length = cअगरs_पढ़ो_data_length,
	.map_error = map_smb_to_linux_error,
	.find_mid = cअगरs_find_mid,
	.check_message = checkSMB,
	.dump_detail = cअगरs_dump_detail,
	.clear_stats = cअगरs_clear_stats,
	.prपूर्णांक_stats = cअगरs_prपूर्णांक_stats,
	.is_oplock_अवरोध = is_valid_oplock_अवरोध,
	.करोwngrade_oplock = cअगरs_करोwngrade_oplock,
	.check_trans2 = cअगरs_check_trans2,
	.need_neg = cअगरs_need_neg,
	.negotiate = cअगरs_negotiate,
	.negotiate_wsize = cअगरs_negotiate_wsize,
	.negotiate_rsize = cअगरs_negotiate_rsize,
	.sess_setup = CIFS_SessSetup,
	.logoff = CIFSSMBLogoff,
	.tree_connect = CIFSTCon,
	.tree_disconnect = CIFSSMBTDis,
	.get_dfs_refer = CIFSGetDFSRefer,
	.qfs_tcon = cअगरs_qfs_tcon,
	.is_path_accessible = cअगरs_is_path_accessible,
	.can_echo = cअगरs_can_echo,
	.query_path_info = cअगरs_query_path_info,
	.query_file_info = cअगरs_query_file_info,
	.get_srv_inum = cअगरs_get_srv_inum,
	.set_path_size = CIFSSMBSetखातापूर्ण,
	.set_file_size = CIFSSMBSetFileSize,
	.set_file_info = smb_set_file_info,
	.set_compression = cअगरs_set_compression,
	.echo = CIFSSMBEcho,
	.सूची_गढ़ो = CIFSSMBMkDir,
	.सूची_गढ़ो_setinfo = cअगरs_सूची_गढ़ो_setinfo,
	.सूची_हटाओ = CIFSSMBRmDir,
	.unlink = CIFSSMBDelFile,
	.नाम_pending_delete = cअगरs_नाम_pending_delete,
	.नाम = CIFSSMBRename,
	.create_hardlink = CIFSCreateHardLink,
	.query_symlink = cअगरs_query_symlink,
	.खोलो = cअगरs_खोलो_file,
	.set_fid = cअगरs_set_fid,
	.बंद = cअगरs_बंद_file,
	.flush = cअगरs_flush_file,
	.async_पढ़ोv = cअगरs_async_पढ़ोv,
	.async_ग_लिखोv = cअगरs_async_ग_लिखोv,
	.sync_पढ़ो = cअगरs_sync_पढ़ो,
	.sync_ग_लिखो = cअगरs_sync_ग_लिखो,
	.query_dir_first = cअगरs_query_dir_first,
	.query_dir_next = cअगरs_query_dir_next,
	.बंद_dir = cअगरs_बंद_dir,
	.calc_smb_size = smbCalcSize,
	.oplock_response = cअगरs_oplock_response,
	.queryfs = cअगरs_queryfs,
	.mand_lock = cअगरs_mand_lock,
	.mand_unlock_range = cअगरs_unlock_range,
	.push_mand_locks = cअगरs_push_mandatory_locks,
	.query_mf_symlink = cअगरs_query_mf_symlink,
	.create_mf_symlink = cअगरs_create_mf_symlink,
	.is_पढ़ो_op = cअगरs_is_पढ़ो_op,
	.wp_retry_size = cअगरs_wp_retry_size,
	.dir_needs_बंद = cअगरs_dir_needs_बंद,
	.select_sectype = cअगरs_select_sectype,
#अगर_घोषित CONFIG_CIFS_XATTR
	.query_all_EAs = CIFSSMBQAllEAs,
	.set_EA = CIFSSMBSetEA,
#पूर्ण_अगर /* CIFS_XATTR */
	.get_acl = get_cअगरs_acl,
	.get_acl_by_fid = get_cअगरs_acl_by_fid,
	.set_acl = set_cअगरs_acl,
	.make_node = cअगरs_make_node,
पूर्ण;

काष्ठा smb_version_values smb1_values = अणु
	.version_string = SMB1_VERSION_STRING,
	.protocol_id = SMB10_PROT_ID,
	.large_lock_type = LOCKING_ANDX_LARGE_खाताS,
	.exclusive_lock_type = 0,
	.shared_lock_type = LOCKING_ANDX_SHARED_LOCK,
	.unlock_lock_type = 0,
	.header_preamble_size = 4,
	.header_size = माप(काष्ठा smb_hdr),
	.max_header_size = MAX_CIFS_HDR_SIZE,
	.पढ़ो_rsp_size = माप(READ_RSP),
	.lock_cmd = cpu_to_le16(SMB_COM_LOCKING_ANDX),
	.cap_unix = CAP_UNIX,
	.cap_nt_find = CAP_NT_SMBS | CAP_NT_FIND,
	.cap_large_files = CAP_LARGE_खाताS,
	.signing_enabled = SECMODE_SIGN_ENABLED,
	.signing_required = SECMODE_SIGN_REQUIRED,
पूर्ण;
