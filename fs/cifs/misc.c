<शैली गुरु>
/*
 *   fs/cअगरs/misc.c
 *
 *   Copyright (C) International Business Machines  Corp., 2002,2008
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

#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mempool.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "smberr.h"
#समावेश "nterr.h"
#समावेश "cifs_unicode.h"
#समावेश "smb2pdu.h"
#समावेश "cifsfs.h"
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
#समावेश "dns_resolve.h"
#पूर्ण_अगर
#समावेश "fs_context.h"

बाह्य mempool_t *cअगरs_sm_req_poolp;
बाह्य mempool_t *cअगरs_req_poolp;

/* The xid serves as a useful identअगरier क्रम each incoming vfs request,
   in a similar way to the mid which is useful to track each sent smb,
   and CurrentXid can also provide a running counter (although it
   will eventually wrap past zero) of the total vfs operations handled
   since the cअगरs fs was mounted */

अचिन्हित पूर्णांक
_get_xid(व्योम)
अणु
	अचिन्हित पूर्णांक xid;

	spin_lock(&GlobalMid_Lock);
	GlobalTotalActiveXid++;

	/* keep high water mark क्रम number of simultaneous ops in fileप्रणाली */
	अगर (GlobalTotalActiveXid > GlobalMaxActiveXid)
		GlobalMaxActiveXid = GlobalTotalActiveXid;
	अगर (GlobalTotalActiveXid > 65000)
		cअगरs_dbg(FYI, "warning: more than 65000 requests active\n");
	xid = GlobalCurrentXid++;
	spin_unlock(&GlobalMid_Lock);
	वापस xid;
पूर्ण

व्योम
_मुक्त_xid(अचिन्हित पूर्णांक xid)
अणु
	spin_lock(&GlobalMid_Lock);
	/* अगर (GlobalTotalActiveXid == 0)
		BUG(); */
	GlobalTotalActiveXid--;
	spin_unlock(&GlobalMid_Lock);
पूर्ण

काष्ठा cअगरs_ses *
sesInfoAlloc(व्योम)
अणु
	काष्ठा cअगरs_ses *ret_buf;

	ret_buf = kzalloc(माप(काष्ठा cअगरs_ses), GFP_KERNEL);
	अगर (ret_buf) अणु
		atomic_inc(&sesInfoAllocCount);
		ret_buf->status = CअगरsNew;
		++ret_buf->ses_count;
		INIT_LIST_HEAD(&ret_buf->smb_ses_list);
		INIT_LIST_HEAD(&ret_buf->tcon_list);
		mutex_init(&ret_buf->session_mutex);
		spin_lock_init(&ret_buf->अगरace_lock);
	पूर्ण
	वापस ret_buf;
पूर्ण

व्योम
sesInfoFree(काष्ठा cअगरs_ses *buf_to_मुक्त)
अणु
	अगर (buf_to_मुक्त == शून्य) अणु
		cअगरs_dbg(FYI, "Null buffer passed to sesInfoFree\n");
		वापस;
	पूर्ण

	atomic_dec(&sesInfoAllocCount);
	kमुक्त(buf_to_मुक्त->serverOS);
	kमुक्त(buf_to_मुक्त->serverDoमुख्य);
	kमुक्त(buf_to_मुक्त->serverNOS);
	kमुक्त_sensitive(buf_to_मुक्त->password);
	kमुक्त(buf_to_मुक्त->user_name);
	kमुक्त(buf_to_मुक्त->करोमुख्यName);
	kमुक्त_sensitive(buf_to_मुक्त->auth_key.response);
	kमुक्त(buf_to_मुक्त->अगरace_list);
	kमुक्त_sensitive(buf_to_मुक्त);
पूर्ण

काष्ठा cअगरs_tcon *
tconInfoAlloc(व्योम)
अणु
	काष्ठा cअगरs_tcon *ret_buf;

	ret_buf = kzalloc(माप(*ret_buf), GFP_KERNEL);
	अगर (!ret_buf)
		वापस शून्य;
	ret_buf->crfid.fid = kzalloc(माप(*ret_buf->crfid.fid), GFP_KERNEL);
	अगर (!ret_buf->crfid.fid) अणु
		kमुक्त(ret_buf);
		वापस शून्य;
	पूर्ण

	atomic_inc(&tconInfoAllocCount);
	ret_buf->tidStatus = CअगरsNew;
	++ret_buf->tc_count;
	INIT_LIST_HEAD(&ret_buf->खोलोFileList);
	INIT_LIST_HEAD(&ret_buf->tcon_list);
	spin_lock_init(&ret_buf->खोलो_file_lock);
	mutex_init(&ret_buf->crfid.fid_mutex);
	spin_lock_init(&ret_buf->stat_lock);
	atomic_set(&ret_buf->num_local_खोलोs, 0);
	atomic_set(&ret_buf->num_remote_खोलोs, 0);

	वापस ret_buf;
पूर्ण

व्योम
tconInfoFree(काष्ठा cअगरs_tcon *buf_to_मुक्त)
अणु
	अगर (buf_to_मुक्त == शून्य) अणु
		cअगरs_dbg(FYI, "Null buffer passed to tconInfoFree\n");
		वापस;
	पूर्ण
	atomic_dec(&tconInfoAllocCount);
	kमुक्त(buf_to_मुक्त->nativeFileSystem);
	kमुक्त_sensitive(buf_to_मुक्त->password);
	kमुक्त(buf_to_मुक्त->crfid.fid);
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	kमुक्त(buf_to_मुक्त->dfs_path);
#पूर्ण_अगर
	kमुक्त(buf_to_मुक्त);
पूर्ण

काष्ठा smb_hdr *
cअगरs_buf_get(व्योम)
अणु
	काष्ठा smb_hdr *ret_buf = शून्य;
	/*
	 * SMB2 header is bigger than CIFS one - no problems to clean some
	 * more bytes क्रम CIFS.
	 */
	माप_प्रकार buf_size = माप(काष्ठा smb2_sync_hdr);

	/*
	 * We could use negotiated size instead of max_msgsize -
	 * but it may be more efficient to always alloc same size
	 * albeit slightly larger than necessary and maxbuffersize
	 * शेषs to this and can not be bigger.
	 */
	ret_buf = mempool_alloc(cअगरs_req_poolp, GFP_NOFS);

	/* clear the first few header bytes */
	/* क्रम most paths, more is cleared in header_assemble */
	स_रखो(ret_buf, 0, buf_size + 3);
	atomic_inc(&bufAllocCount);
#अगर_घोषित CONFIG_CIFS_STATS2
	atomic_inc(&totBufAllocCount);
#पूर्ण_अगर /* CONFIG_CIFS_STATS2 */

	वापस ret_buf;
पूर्ण

व्योम
cअगरs_buf_release(व्योम *buf_to_मुक्त)
अणु
	अगर (buf_to_मुक्त == शून्य) अणु
		/* cअगरs_dbg(FYI, "Null buffer passed to cifs_buf_release\n");*/
		वापस;
	पूर्ण
	mempool_मुक्त(buf_to_मुक्त, cअगरs_req_poolp);

	atomic_dec(&bufAllocCount);
	वापस;
पूर्ण

काष्ठा smb_hdr *
cअगरs_small_buf_get(व्योम)
अणु
	काष्ठा smb_hdr *ret_buf = शून्य;

/* We could use negotiated size instead of max_msgsize -
   but it may be more efficient to always alloc same size
   albeit slightly larger than necessary and maxbuffersize
   शेषs to this and can not be bigger */
	ret_buf = mempool_alloc(cअगरs_sm_req_poolp, GFP_NOFS);
	/* No need to clear memory here, cleared in header assemble */
	/*	स_रखो(ret_buf, 0, माप(काष्ठा smb_hdr) + 27);*/
	atomic_inc(&smBufAllocCount);
#अगर_घोषित CONFIG_CIFS_STATS2
	atomic_inc(&totSmBufAllocCount);
#पूर्ण_अगर /* CONFIG_CIFS_STATS2 */

	वापस ret_buf;
पूर्ण

व्योम
cअगरs_small_buf_release(व्योम *buf_to_मुक्त)
अणु

	अगर (buf_to_मुक्त == शून्य) अणु
		cअगरs_dbg(FYI, "Null buffer passed to cifs_small_buf_release\n");
		वापस;
	पूर्ण
	mempool_मुक्त(buf_to_मुक्त, cअगरs_sm_req_poolp);

	atomic_dec(&smBufAllocCount);
	वापस;
पूर्ण

व्योम
मुक्त_rsp_buf(पूर्णांक resp_buftype, व्योम *rsp)
अणु
	अगर (resp_buftype == CIFS_SMALL_BUFFER)
		cअगरs_small_buf_release(rsp);
	अन्यथा अगर (resp_buftype == CIFS_LARGE_BUFFER)
		cअगरs_buf_release(rsp);
पूर्ण

/* NB: MID can not be set अगर treeCon not passed in, in that
   हाल it is responsbility of caller to set the mid */
व्योम
header_assemble(काष्ठा smb_hdr *buffer, अक्षर smb_command /* command */ ,
		स्थिर काष्ठा cअगरs_tcon *treeCon, पूर्णांक word_count
		/* length of fixed section (word count) in two byte units  */)
अणु
	अक्षर *temp = (अक्षर *) buffer;

	स_रखो(temp, 0, 256); /* bigger than MAX_CIFS_HDR_SIZE */

	buffer->smb_buf_length = cpu_to_be32(
	    (2 * word_count) + माप(काष्ठा smb_hdr) -
	    4 /*  RFC 1001 length field करोes not count */  +
	    2 /* क्रम bcc field itself */) ;

	buffer->Protocol[0] = 0xFF;
	buffer->Protocol[1] = 'S';
	buffer->Protocol[2] = 'M';
	buffer->Protocol[3] = 'B';
	buffer->Command = smb_command;
	buffer->Flags = 0x00;	/* हाल sensitive */
	buffer->Flags2 = SMBFLG2_KNOWS_LONG_NAMES;
	buffer->Pid = cpu_to_le16((__u16)current->tgid);
	buffer->PidHigh = cpu_to_le16((__u16)(current->tgid >> 16));
	अगर (treeCon) अणु
		buffer->Tid = treeCon->tid;
		अगर (treeCon->ses) अणु
			अगर (treeCon->ses->capabilities & CAP_UNICODE)
				buffer->Flags2 |= SMBFLG2_UNICODE;
			अगर (treeCon->ses->capabilities & CAP_STATUS32)
				buffer->Flags2 |= SMBFLG2_ERR_STATUS;

			/* Uid is not converted */
			buffer->Uid = treeCon->ses->Suid;
			buffer->Mid = get_next_mid(treeCon->ses->server);
		पूर्ण
		अगर (treeCon->Flags & SMB_SHARE_IS_IN_DFS)
			buffer->Flags2 |= SMBFLG2_DFS;
		अगर (treeCon->noहाल)
			buffer->Flags  |= SMBFLG_CASELESS;
		अगर ((treeCon->ses) && (treeCon->ses->server))
			अगर (treeCon->ses->server->sign)
				buffer->Flags2 |= SMBFLG2_SECURITY_SIGNATURE;
	पूर्ण

/*  endian conversion of flags is now करोne just beक्रमe sending */
	buffer->WordCount = (अक्षर) word_count;
	वापस;
पूर्ण

अटल पूर्णांक
check_smb_hdr(काष्ठा smb_hdr *smb)
अणु
	/* करोes it have the right SMB "signature" ? */
	अगर (*(__le32 *) smb->Protocol != cpu_to_le32(0x424d53ff)) अणु
		cअगरs_dbg(VFS, "Bad protocol string signature header 0x%x\n",
			 *(अचिन्हित पूर्णांक *)smb->Protocol);
		वापस 1;
	पूर्ण

	/* अगर it's a response then accept */
	अगर (smb->Flags & SMBFLG_RESPONSE)
		वापस 0;

	/* only one valid हाल where server sends us request */
	अगर (smb->Command == SMB_COM_LOCKING_ANDX)
		वापस 0;

	cअगरs_dbg(VFS, "Server sent request, not response. mid=%u\n",
		 get_mid(smb));
	वापस 1;
पूर्ण

पूर्णांक
checkSMB(अक्षर *buf, अचिन्हित पूर्णांक total_पढ़ो, काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा smb_hdr *smb = (काष्ठा smb_hdr *)buf;
	__u32 rfclen = be32_to_cpu(smb->smb_buf_length);
	__u32 clc_len;  /* calculated length */
	cअगरs_dbg(FYI, "checkSMB Length: 0x%x, smb_buf_length: 0x%x\n",
		 total_पढ़ो, rfclen);

	/* is this frame too small to even get to a BCC? */
	अगर (total_पढ़ो < 2 + माप(काष्ठा smb_hdr)) अणु
		अगर ((total_पढ़ो >= माप(काष्ठा smb_hdr) - 1)
			    && (smb->Status.CअगरsError != 0)) अणु
			/* it's an error वापस */
			smb->WordCount = 0;
			/* some error हालs करो not वापस wct and bcc */
			वापस 0;
		पूर्ण अन्यथा अगर ((total_पढ़ो == माप(काष्ठा smb_hdr) + 1) &&
				(smb->WordCount == 0)) अणु
			अक्षर *पंचांगp = (अक्षर *)smb;
			/* Need to work around a bug in two servers here */
			/* First, check अगर the part of bcc they sent was zero */
			अगर (पंचांगp[माप(काष्ठा smb_hdr)] == 0) अणु
				/* some servers वापस only half of bcc
				 * on simple responses (wct, bcc both zero)
				 * in particular have seen this on
				 * ulogoffX and FindClose. This leaves
				 * one byte of bcc potentially unitialized
				 */
				/* zero rest of bcc */
				पंचांगp[माप(काष्ठा smb_hdr)+1] = 0;
				वापस 0;
			पूर्ण
			cअगरs_dbg(VFS, "rcvd invalid byte count (bcc)\n");
		पूर्ण अन्यथा अणु
			cअगरs_dbg(VFS, "Length less than smb header size\n");
		पूर्ण
		वापस -EIO;
	पूर्ण

	/* otherwise, there is enough to get to the BCC */
	अगर (check_smb_hdr(smb))
		वापस -EIO;
	clc_len = smbCalcSize(smb, server);

	अगर (4 + rfclen != total_पढ़ो) अणु
		cअगरs_dbg(VFS, "Length read does not match RFC1001 length %d\n",
			 rfclen);
		वापस -EIO;
	पूर्ण

	अगर (4 + rfclen != clc_len) अणु
		__u16 mid = get_mid(smb);
		/* check अगर bcc wrapped around क्रम large पढ़ो responses */
		अगर ((rfclen > 64 * 1024) && (rfclen > clc_len)) अणु
			/* check अगर lengths match mod 64K */
			अगर (((4 + rfclen) & 0xFFFF) == (clc_len & 0xFFFF))
				वापस 0; /* bcc wrapped */
		पूर्ण
		cअगरs_dbg(FYI, "Calculated size %u vs length %u mismatch for mid=%u\n",
			 clc_len, 4 + rfclen, mid);

		अगर (4 + rfclen < clc_len) अणु
			cअगरs_dbg(VFS, "RFC1001 size %u smaller than SMB for mid=%u\n",
				 rfclen, mid);
			वापस -EIO;
		पूर्ण अन्यथा अगर (rfclen > clc_len + 512) अणु
			/*
			 * Some servers (Winकरोws XP in particular) send more
			 * data than the lengths in the SMB packet would
			 * indicate on certain calls (byte range locks and
			 * trans2 find first calls in particular). While the
			 * client can handle such a frame by ignoring the
			 * trailing data, we choose limit the amount of extra
			 * data to 512 bytes.
			 */
			cअगरs_dbg(VFS, "RFC1001 size %u more than 512 bytes larger than SMB for mid=%u\n",
				 rfclen, mid);
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

bool
is_valid_oplock_अवरोध(अक्षर *buffer, काष्ठा TCP_Server_Info *srv)
अणु
	काष्ठा smb_hdr *buf = (काष्ठा smb_hdr *)buffer;
	काष्ठा smb_com_lock_req *pSMB = (काष्ठा smb_com_lock_req *)buf;
	काष्ठा list_head *पंचांगp, *पंचांगp1, *पंचांगp2;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरsInodeInfo *pCअगरsInode;
	काष्ठा cअगरsFileInfo *netfile;

	cअगरs_dbg(FYI, "Checking for oplock break or dnotify response\n");
	अगर ((pSMB->hdr.Command == SMB_COM_NT_TRANSACT) &&
	   (pSMB->hdr.Flags & SMBFLG_RESPONSE)) अणु
		काष्ठा smb_com_transaction_change_notअगरy_rsp *pSMBr =
			(काष्ठा smb_com_transaction_change_notअगरy_rsp *)buf;
		काष्ठा file_notअगरy_inक्रमmation *pnotअगरy;
		__u32 data_offset = 0;
		माप_प्रकार len = srv->total_पढ़ो - माप(pSMBr->hdr.smb_buf_length);

		अगर (get_bcc(buf) > माप(काष्ठा file_notअगरy_inक्रमmation)) अणु
			data_offset = le32_to_cpu(pSMBr->DataOffset);

			अगर (data_offset >
			    len - माप(काष्ठा file_notअगरy_inक्रमmation)) अणु
				cअगरs_dbg(FYI, "Invalid data_offset %u\n",
					 data_offset);
				वापस true;
			पूर्ण
			pnotअगरy = (काष्ठा file_notअगरy_inक्रमmation *)
				((अक्षर *)&pSMBr->hdr.Protocol + data_offset);
			cअगरs_dbg(FYI, "dnotify on %s Action: 0x%x\n",
				 pnotअगरy->FileName, pnotअगरy->Action);
			/*   cअगरs_dump_mem("Rcvd notify Data: ",buf,
				माप(काष्ठा smb_hdr)+60); */
			वापस true;
		पूर्ण
		अगर (pSMBr->hdr.Status.CअगरsError) अणु
			cअगरs_dbg(FYI, "notify err 0x%x\n",
				 pSMBr->hdr.Status.CअगरsError);
			वापस true;
		पूर्ण
		वापस false;
	पूर्ण
	अगर (pSMB->hdr.Command != SMB_COM_LOCKING_ANDX)
		वापस false;
	अगर (pSMB->hdr.Flags & SMBFLG_RESPONSE) अणु
		/* no sense logging error on invalid handle on oplock
		   अवरोध - harmless race between बंद request and oplock
		   अवरोध response is expected from समय to समय writing out
		   large dirty files cached on the client */
		अगर ((NT_STATUS_INVALID_HANDLE) ==
		   le32_to_cpu(pSMB->hdr.Status.CअगरsError)) अणु
			cअगरs_dbg(FYI, "Invalid handle on oplock break\n");
			वापस true;
		पूर्ण अन्यथा अगर (ERRbadfid ==
		   le16_to_cpu(pSMB->hdr.Status.DosError.Error)) अणु
			वापस true;
		पूर्ण अन्यथा अणु
			वापस false; /* on valid oplock brk we get "request" */
		पूर्ण
	पूर्ण
	अगर (pSMB->hdr.WordCount != 8)
		वापस false;

	cअगरs_dbg(FYI, "oplock type 0x%x level 0x%x\n",
		 pSMB->LockType, pSMB->OplockLevel);
	अगर (!(pSMB->LockType & LOCKING_ANDX_OPLOCK_RELEASE))
		वापस false;

	/* look up tcon based on tid & uid */
	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each(पंचांगp, &srv->smb_ses_list) अणु
		ses = list_entry(पंचांगp, काष्ठा cअगरs_ses, smb_ses_list);
		list_क्रम_each(पंचांगp1, &ses->tcon_list) अणु
			tcon = list_entry(पंचांगp1, काष्ठा cअगरs_tcon, tcon_list);
			अगर (tcon->tid != buf->Tid)
				जारी;

			cअगरs_stats_inc(&tcon->stats.cअगरs_stats.num_oplock_brks);
			spin_lock(&tcon->खोलो_file_lock);
			list_क्रम_each(पंचांगp2, &tcon->खोलोFileList) अणु
				netfile = list_entry(पंचांगp2, काष्ठा cअगरsFileInfo,
						     tlist);
				अगर (pSMB->Fid != netfile->fid.netfid)
					जारी;

				cअगरs_dbg(FYI, "file id match, oplock break\n");
				pCअगरsInode = CIFS_I(d_inode(netfile->dentry));

				set_bit(CIFS_INODE_PENDING_OPLOCK_BREAK,
					&pCअगरsInode->flags);

				netfile->oplock_epoch = 0;
				netfile->oplock_level = pSMB->OplockLevel;
				netfile->oplock_अवरोध_cancelled = false;
				cअगरs_queue_oplock_अवरोध(netfile);

				spin_unlock(&tcon->खोलो_file_lock);
				spin_unlock(&cअगरs_tcp_ses_lock);
				वापस true;
			पूर्ण
			spin_unlock(&tcon->खोलो_file_lock);
			spin_unlock(&cअगरs_tcp_ses_lock);
			cअगरs_dbg(FYI, "No matching file for oplock break\n");
			वापस true;
		पूर्ण
	पूर्ण
	spin_unlock(&cअगरs_tcp_ses_lock);
	cअगरs_dbg(FYI, "Can not process oplock break for non-existent connection\n");
	वापस true;
पूर्ण

व्योम
dump_smb(व्योम *buf, पूर्णांक smb_buf_length)
अणु
	अगर (traceSMB == 0)
		वापस;

	prपूर्णांक_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_NONE, 8, 2, buf,
		       smb_buf_length, true);
पूर्ण

व्योम
cअगरs_स्वतःdisable_serverino(काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM) अणु
		काष्ठा cअगरs_tcon *tcon = शून्य;

		अगर (cअगरs_sb->master_tlink)
			tcon = cअगरs_sb_master_tcon(cअगरs_sb);

		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_SERVER_INUM;
		cअगरs_sb->mnt_cअगरs_serverino_स्वतःdisabled = true;
		cअगरs_dbg(VFS, "Autodisabling the use of server inode numbers on %s\n",
			 tcon ? tcon->treeName : "new server");
		cअगरs_dbg(VFS, "The server doesn't seem to support them properly or the files might be on different servers (DFS)\n");
		cअगरs_dbg(VFS, "Hardlinks will not be recognized on this mount. Consider mounting with the \"noserverino\" option to silence this message.\n");

	पूर्ण
पूर्ण

व्योम cअगरs_set_oplock_level(काष्ठा cअगरsInodeInfo *cinode, __u32 oplock)
अणु
	oplock &= 0xF;

	अगर (oplock == OPLOCK_EXCLUSIVE) अणु
		cinode->oplock = CIFS_CACHE_WRITE_FLG | CIFS_CACHE_READ_FLG;
		cअगरs_dbg(FYI, "Exclusive Oplock granted on inode %p\n",
			 &cinode->vfs_inode);
	पूर्ण अन्यथा अगर (oplock == OPLOCK_READ) अणु
		cinode->oplock = CIFS_CACHE_READ_FLG;
		cअगरs_dbg(FYI, "Level II Oplock granted on inode %p\n",
			 &cinode->vfs_inode);
	पूर्ण अन्यथा
		cinode->oplock = 0;
पूर्ण

/*
 * We रुको क्रम oplock अवरोधs to be processed beक्रमe we attempt to perक्रमm
 * ग_लिखोs.
 */
पूर्णांक cअगरs_get_ग_लिखोr(काष्ठा cअगरsInodeInfo *cinode)
अणु
	पूर्णांक rc;

start:
	rc = रुको_on_bit(&cinode->flags, CIFS_INODE_PENDING_OPLOCK_BREAK,
			 TASK_KILLABLE);
	अगर (rc)
		वापस rc;

	spin_lock(&cinode->ग_लिखोrs_lock);
	अगर (!cinode->ग_लिखोrs)
		set_bit(CIFS_INODE_PENDING_WRITERS, &cinode->flags);
	cinode->ग_लिखोrs++;
	/* Check to see अगर we have started servicing an oplock अवरोध */
	अगर (test_bit(CIFS_INODE_PENDING_OPLOCK_BREAK, &cinode->flags)) अणु
		cinode->ग_लिखोrs--;
		अगर (cinode->ग_लिखोrs == 0) अणु
			clear_bit(CIFS_INODE_PENDING_WRITERS, &cinode->flags);
			wake_up_bit(&cinode->flags, CIFS_INODE_PENDING_WRITERS);
		पूर्ण
		spin_unlock(&cinode->ग_लिखोrs_lock);
		जाओ start;
	पूर्ण
	spin_unlock(&cinode->ग_लिखोrs_lock);
	वापस 0;
पूर्ण

व्योम cअगरs_put_ग_लिखोr(काष्ठा cअगरsInodeInfo *cinode)
अणु
	spin_lock(&cinode->ग_लिखोrs_lock);
	cinode->ग_लिखोrs--;
	अगर (cinode->ग_लिखोrs == 0) अणु
		clear_bit(CIFS_INODE_PENDING_WRITERS, &cinode->flags);
		wake_up_bit(&cinode->flags, CIFS_INODE_PENDING_WRITERS);
	पूर्ण
	spin_unlock(&cinode->ग_लिखोrs_lock);
पूर्ण

/**
 * cअगरs_queue_oplock_अवरोध - queue the oplock अवरोध handler क्रम cfile
 *
 * This function is called from the demultiplex thपढ़ो when it
 * receives an oplock अवरोध क्रम @cfile.
 *
 * Assumes the tcon->खोलो_file_lock is held.
 * Assumes cfile->file_info_lock is NOT held.
 */
व्योम cअगरs_queue_oplock_अवरोध(काष्ठा cअगरsFileInfo *cfile)
अणु
	/*
	 * Bump the handle refcount now जबतक we hold the
	 * खोलो_file_lock to enक्रमce the validity of it क्रम the oplock
	 * अवरोध handler. The matching put is करोne at the end of the
	 * handler.
	 */
	cअगरsFileInfo_get(cfile);

	queue_work(cअगरsoplockd_wq, &cfile->oplock_अवरोध);
पूर्ण

व्योम cअगरs_करोne_oplock_अवरोध(काष्ठा cअगरsInodeInfo *cinode)
अणु
	clear_bit(CIFS_INODE_PENDING_OPLOCK_BREAK, &cinode->flags);
	wake_up_bit(&cinode->flags, CIFS_INODE_PENDING_OPLOCK_BREAK);
पूर्ण

bool
backup_cred(काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_CIFS_BACKUPUID) अणु
		अगर (uid_eq(cअगरs_sb->ctx->backupuid, current_fsuid()))
			वापस true;
	पूर्ण
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_CIFS_BACKUPGID) अणु
		अगर (in_group_p(cअगरs_sb->ctx->backupgid))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम
cअगरs_del_pending_खोलो(काष्ठा cअगरs_pending_खोलो *खोलो)
अणु
	spin_lock(&tlink_tcon(खोलो->tlink)->खोलो_file_lock);
	list_del(&खोलो->olist);
	spin_unlock(&tlink_tcon(खोलो->tlink)->खोलो_file_lock);
पूर्ण

व्योम
cअगरs_add_pending_खोलो_locked(काष्ठा cअगरs_fid *fid, काष्ठा tcon_link *tlink,
			     काष्ठा cअगरs_pending_खोलो *खोलो)
अणु
	स_नकल(खोलो->lease_key, fid->lease_key, SMB2_LEASE_KEY_SIZE);
	खोलो->oplock = CIFS_OPLOCK_NO_CHANGE;
	खोलो->tlink = tlink;
	fid->pending_खोलो = खोलो;
	list_add_tail(&खोलो->olist, &tlink_tcon(tlink)->pending_खोलोs);
पूर्ण

व्योम
cअगरs_add_pending_खोलो(काष्ठा cअगरs_fid *fid, काष्ठा tcon_link *tlink,
		      काष्ठा cअगरs_pending_खोलो *खोलो)
अणु
	spin_lock(&tlink_tcon(tlink)->खोलो_file_lock);
	cअगरs_add_pending_खोलो_locked(fid, tlink, खोलो);
	spin_unlock(&tlink_tcon(खोलो->tlink)->खोलो_file_lock);
पूर्ण

/*
 * Critical section which runs after acquiring deferred_lock.
 * As there is no reference count on cअगरs_deferred_बंद, pdबंद
 * should not be used outside deferred_lock.
 */
bool
cअगरs_is_deferred_बंद(काष्ठा cअगरsFileInfo *cfile, काष्ठा cअगरs_deferred_बंद **pdबंद)
अणु
	काष्ठा cअगरs_deferred_बंद *dबंद;

	list_क्रम_each_entry(dबंद, &CIFS_I(d_inode(cfile->dentry))->deferred_बंदs, dlist) अणु
		अगर ((dबंद->netfid == cfile->fid.netfid) &&
			(dबंद->persistent_fid == cfile->fid.persistent_fid) &&
			(dबंद->अस्थिर_fid == cfile->fid.अस्थिर_fid)) अणु
			*pdबंद = dबंद;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/*
 * Critical section which runs after acquiring deferred_lock.
 */
व्योम
cअगरs_add_deferred_बंद(काष्ठा cअगरsFileInfo *cfile, काष्ठा cअगरs_deferred_बंद *dबंद)
अणु
	bool is_deferred = false;
	काष्ठा cअगरs_deferred_बंद *pdबंद;

	is_deferred = cअगरs_is_deferred_बंद(cfile, &pdबंद);
	अगर (is_deferred) अणु
		kमुक्त(dबंद);
		वापस;
	पूर्ण

	dबंद->tlink = cfile->tlink;
	dबंद->netfid = cfile->fid.netfid;
	dबंद->persistent_fid = cfile->fid.persistent_fid;
	dबंद->अस्थिर_fid = cfile->fid.अस्थिर_fid;
	list_add_tail(&dबंद->dlist, &CIFS_I(d_inode(cfile->dentry))->deferred_बंदs);
पूर्ण

/*
 * Critical section which runs after acquiring deferred_lock.
 */
व्योम
cअगरs_del_deferred_बंद(काष्ठा cअगरsFileInfo *cfile)
अणु
	bool is_deferred = false;
	काष्ठा cअगरs_deferred_बंद *dबंद;

	is_deferred = cअगरs_is_deferred_बंद(cfile, &dबंद);
	अगर (!is_deferred)
		वापस;
	list_del(&dबंद->dlist);
	kमुक्त(dबंद);
पूर्ण

व्योम
cअगरs_बंद_deferred_file(काष्ठा cअगरsInodeInfo *cअगरs_inode)
अणु
	काष्ठा cअगरsFileInfo *cfile = शून्य;
	काष्ठा cअगरs_deferred_बंद *dबंद;

	list_क्रम_each_entry(cfile, &cअगरs_inode->खोलोFileList, flist) अणु
		spin_lock(&cअगरs_inode->deferred_lock);
		अगर (cअगरs_is_deferred_बंद(cfile, &dबंद))
			mod_delayed_work(deferredबंद_wq, &cfile->deferred, 0);
		spin_unlock(&cअगरs_inode->deferred_lock);
	पूर्ण
पूर्ण

व्योम
cअगरs_बंद_all_deferred_files(काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा cअगरsFileInfo *cfile;
	काष्ठा list_head *पंचांगp;

	spin_lock(&tcon->खोलो_file_lock);
	list_क्रम_each(पंचांगp, &tcon->खोलोFileList) अणु
		cfile = list_entry(पंचांगp, काष्ठा cअगरsFileInfo, tlist);
		अगर (delayed_work_pending(&cfile->deferred)) अणु
			/*
			 * If there is no pending work, mod_delayed_work queues new work.
			 * So, Increase the ref count to aव्योम use-after-मुक्त.
			 */
			अगर (!mod_delayed_work(deferredबंद_wq, &cfile->deferred, 0))
				cअगरsFileInfo_get(cfile);
		पूर्ण
	पूर्ण
	spin_unlock(&tcon->खोलो_file_lock);
पूर्ण

/* parses DFS refferal V3 काष्ठाure
 * caller is responsible क्रम मुक्तing target_nodes
 * वापसs:
 * - on success - 0
 * - on failure - त्रुटि_सं
 */
पूर्णांक
parse_dfs_referrals(काष्ठा get_dfs_referral_rsp *rsp, u32 rsp_size,
		    अचिन्हित पूर्णांक *num_of_nodes,
		    काष्ठा dfs_info3_param **target_nodes,
		    स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap,
		    स्थिर अक्षर *searchName, bool is_unicode)
अणु
	पूर्णांक i, rc = 0;
	अक्षर *data_end;
	काष्ठा dfs_referral_level_3 *ref;

	*num_of_nodes = le16_to_cpu(rsp->NumberOfReferrals);

	अगर (*num_of_nodes < 1) अणु
		cअगरs_dbg(VFS, "num_referrals: must be at least > 0, but we get num_referrals = %d\n",
			 *num_of_nodes);
		rc = -EINVAL;
		जाओ parse_DFS_referrals_निकास;
	पूर्ण

	ref = (काष्ठा dfs_referral_level_3 *) &(rsp->referrals);
	अगर (ref->VersionNumber != cpu_to_le16(3)) अणु
		cअगरs_dbg(VFS, "Referrals of V%d version are not supported, should be V3\n",
			 le16_to_cpu(ref->VersionNumber));
		rc = -EINVAL;
		जाओ parse_DFS_referrals_निकास;
	पूर्ण

	/* get the upper boundary of the resp buffer */
	data_end = (अक्षर *)rsp + rsp_size;

	cअगरs_dbg(FYI, "num_referrals: %d dfs flags: 0x%x ...\n",
		 *num_of_nodes, le32_to_cpu(rsp->DFSFlags));

	*target_nodes = kसुस्मृति(*num_of_nodes, माप(काष्ठा dfs_info3_param),
				GFP_KERNEL);
	अगर (*target_nodes == शून्य) अणु
		rc = -ENOMEM;
		जाओ parse_DFS_referrals_निकास;
	पूर्ण

	/* collect necessary data from referrals */
	क्रम (i = 0; i < *num_of_nodes; i++) अणु
		अक्षर *temp;
		पूर्णांक max_len;
		काष्ठा dfs_info3_param *node = (*target_nodes)+i;

		node->flags = le32_to_cpu(rsp->DFSFlags);
		अगर (is_unicode) अणु
			__le16 *पंचांगp = kदो_स्मृति(म_माप(searchName)*2 + 2,
						GFP_KERNEL);
			अगर (पंचांगp == शून्य) अणु
				rc = -ENOMEM;
				जाओ parse_DFS_referrals_निकास;
			पूर्ण
			cअगरsConvertToUTF16((__le16 *) पंचांगp, searchName,
					   PATH_MAX, nls_codepage, remap);
			node->path_consumed = cअगरs_utf16_bytes(पंचांगp,
					le16_to_cpu(rsp->PathConsumed),
					nls_codepage);
			kमुक्त(पंचांगp);
		पूर्ण अन्यथा
			node->path_consumed = le16_to_cpu(rsp->PathConsumed);

		node->server_type = le16_to_cpu(ref->ServerType);
		node->ref_flag = le16_to_cpu(ref->ReferralEntryFlags);

		/* copy DfsPath */
		temp = (अक्षर *)ref + le16_to_cpu(ref->DfsPathOffset);
		max_len = data_end - temp;
		node->path_name = cअगरs_strndup_from_utf16(temp, max_len,
						is_unicode, nls_codepage);
		अगर (!node->path_name) अणु
			rc = -ENOMEM;
			जाओ parse_DFS_referrals_निकास;
		पूर्ण

		/* copy link target UNC */
		temp = (अक्षर *)ref + le16_to_cpu(ref->NetworkAddressOffset);
		max_len = data_end - temp;
		node->node_name = cअगरs_strndup_from_utf16(temp, max_len,
						is_unicode, nls_codepage);
		अगर (!node->node_name) अणु
			rc = -ENOMEM;
			जाओ parse_DFS_referrals_निकास;
		पूर्ण

		node->ttl = le32_to_cpu(ref->TimeToLive);

		ref++;
	पूर्ण

parse_DFS_referrals_निकास:
	अगर (rc) अणु
		मुक्त_dfs_info_array(*target_nodes, *num_of_nodes);
		*target_nodes = शून्य;
		*num_of_nodes = 0;
	पूर्ण
	वापस rc;
पूर्ण

काष्ठा cअगरs_aio_ctx *
cअगरs_aio_ctx_alloc(व्योम)
अणु
	काष्ठा cअगरs_aio_ctx *ctx;

	/*
	 * Must use kzalloc to initialize ctx->bv to शून्य and ctx->direct_io
	 * to false so that we know when we have to unreference pages within
	 * cअगरs_aio_ctx_release()
	 */
	ctx = kzalloc(माप(काष्ठा cअगरs_aio_ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	INIT_LIST_HEAD(&ctx->list);
	mutex_init(&ctx->aio_mutex);
	init_completion(&ctx->करोne);
	kref_init(&ctx->refcount);
	वापस ctx;
पूर्ण

व्योम
cअगरs_aio_ctx_release(काष्ठा kref *refcount)
अणु
	काष्ठा cअगरs_aio_ctx *ctx = container_of(refcount,
					काष्ठा cअगरs_aio_ctx, refcount);

	cअगरsFileInfo_put(ctx->cfile);

	/*
	 * ctx->bv is only set अगर setup_aio_ctx_iter() was call successfuly
	 * which means that iov_iter_get_pages() was a success and thus that
	 * we have taken reference on pages.
	 */
	अगर (ctx->bv) अणु
		अचिन्हित i;

		क्रम (i = 0; i < ctx->npages; i++) अणु
			अगर (ctx->should_dirty)
				set_page_dirty(ctx->bv[i].bv_page);
			put_page(ctx->bv[i].bv_page);
		पूर्ण
		kvमुक्त(ctx->bv);
	पूर्ण

	kमुक्त(ctx);
पूर्ण

#घोषणा CIFS_AIO_KMALLOC_LIMIT (1024 * 1024)

पूर्णांक
setup_aio_ctx_iter(काष्ठा cअगरs_aio_ctx *ctx, काष्ठा iov_iter *iter, पूर्णांक rw)
अणु
	sमाप_प्रकार rc;
	अचिन्हित पूर्णांक cur_npages;
	अचिन्हित पूर्णांक npages = 0;
	अचिन्हित पूर्णांक i;
	माप_प्रकार len;
	माप_प्रकार count = iov_iter_count(iter);
	अचिन्हित पूर्णांक saved_len;
	माप_प्रकार start;
	अचिन्हित पूर्णांक max_pages = iov_iter_npages(iter, पूर्णांक_उच्च);
	काष्ठा page **pages = शून्य;
	काष्ठा bio_vec *bv = शून्य;

	अगर (iov_iter_is_kvec(iter)) अणु
		स_नकल(&ctx->iter, iter, माप(*iter));
		ctx->len = count;
		iov_iter_advance(iter, count);
		वापस 0;
	पूर्ण

	अगर (array_size(max_pages, माप(*bv)) <= CIFS_AIO_KMALLOC_LIMIT)
		bv = kदो_स्मृति_array(max_pages, माप(*bv), GFP_KERNEL);

	अगर (!bv) अणु
		bv = vदो_स्मृति(array_size(max_pages, माप(*bv)));
		अगर (!bv)
			वापस -ENOMEM;
	पूर्ण

	अगर (array_size(max_pages, माप(*pages)) <= CIFS_AIO_KMALLOC_LIMIT)
		pages = kदो_स्मृति_array(max_pages, माप(*pages), GFP_KERNEL);

	अगर (!pages) अणु
		pages = vदो_स्मृति(array_size(max_pages, माप(*pages)));
		अगर (!pages) अणु
			kvमुक्त(bv);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	saved_len = count;

	जबतक (count && npages < max_pages) अणु
		rc = iov_iter_get_pages(iter, pages, count, max_pages, &start);
		अगर (rc < 0) अणु
			cअगरs_dbg(VFS, "Couldn't get user pages (rc=%zd)\n", rc);
			अवरोध;
		पूर्ण

		अगर (rc > count) अणु
			cअगरs_dbg(VFS, "get pages rc=%zd more than %zu\n", rc,
				 count);
			अवरोध;
		पूर्ण

		iov_iter_advance(iter, rc);
		count -= rc;
		rc += start;
		cur_npages = DIV_ROUND_UP(rc, PAGE_SIZE);

		अगर (npages + cur_npages > max_pages) अणु
			cअगरs_dbg(VFS, "out of vec array capacity (%u vs %u)\n",
				 npages + cur_npages, max_pages);
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < cur_npages; i++) अणु
			len = rc > PAGE_SIZE ? PAGE_SIZE : rc;
			bv[npages + i].bv_page = pages[i];
			bv[npages + i].bv_offset = start;
			bv[npages + i].bv_len = len - start;
			rc -= len;
			start = 0;
		पूर्ण

		npages += cur_npages;
	पूर्ण

	kvमुक्त(pages);
	ctx->bv = bv;
	ctx->len = saved_len - count;
	ctx->npages = npages;
	iov_iter_bvec(&ctx->iter, rw, ctx->bv, npages, ctx->len);
	वापस 0;
पूर्ण

/**
 * cअगरs_alloc_hash - allocate hash and hash context together
 *
 * The caller has to make sure @sdesc is initialized to either शून्य or
 * a valid context. Both can be मुक्तd via cअगरs_मुक्त_hash().
 */
पूर्णांक
cअगरs_alloc_hash(स्थिर अक्षर *name,
		काष्ठा crypto_shash **shash, काष्ठा sdesc **sdesc)
अणु
	पूर्णांक rc = 0;
	माप_प्रकार size;

	अगर (*sdesc != शून्य)
		वापस 0;

	*shash = crypto_alloc_shash(name, 0, 0);
	अगर (IS_ERR(*shash)) अणु
		cअगरs_dbg(VFS, "Could not allocate crypto %s\n", name);
		rc = PTR_ERR(*shash);
		*shash = शून्य;
		*sdesc = शून्य;
		वापस rc;
	पूर्ण

	size = माप(काष्ठा shash_desc) + crypto_shash_descsize(*shash);
	*sdesc = kदो_स्मृति(size, GFP_KERNEL);
	अगर (*sdesc == शून्य) अणु
		cअगरs_dbg(VFS, "no memory left to allocate crypto %s\n", name);
		crypto_मुक्त_shash(*shash);
		*shash = शून्य;
		वापस -ENOMEM;
	पूर्ण

	(*sdesc)->shash.tfm = *shash;
	वापस 0;
पूर्ण

/**
 * cअगरs_मुक्त_hash - मुक्त hash and hash context together
 *
 * Freeing a शून्य hash or context is safe.
 */
व्योम
cअगरs_मुक्त_hash(काष्ठा crypto_shash **shash, काष्ठा sdesc **sdesc)
अणु
	kमुक्त(*sdesc);
	*sdesc = शून्य;
	अगर (*shash)
		crypto_मुक्त_shash(*shash);
	*shash = शून्य;
पूर्ण

/**
 * rqst_page_get_length - obtain the length and offset क्रम a page in smb_rqst
 * Input: rqst - a smb_rqst, page - a page index क्रम rqst
 * Output: *len - the length क्रम this page, *offset - the offset क्रम this page
 */
व्योम rqst_page_get_length(काष्ठा smb_rqst *rqst, अचिन्हित पूर्णांक page,
				अचिन्हित पूर्णांक *len, अचिन्हित पूर्णांक *offset)
अणु
	*len = rqst->rq_pagesz;
	*offset = (page == 0) ? rqst->rq_offset : 0;

	अगर (rqst->rq_npages == 1 || page == rqst->rq_npages-1)
		*len = rqst->rq_tailsz;
	अन्यथा अगर (page == 0)
		*len = rqst->rq_pagesz - rqst->rq_offset;
पूर्ण

व्योम extract_unc_hostname(स्थिर अक्षर *unc, स्थिर अक्षर **h, माप_प्रकार *len)
अणु
	स्थिर अक्षर *end;

	/* skip initial slashes */
	जबतक (*unc && (*unc == '\\' || *unc == '/'))
		unc++;

	end = unc;

	जबतक (*end && !(*end == '\\' || *end == '/'))
		end++;

	*h = unc;
	*len = end - unc;
पूर्ण

/**
 * copy_path_name - copy src path to dst, possibly truncating
 *
 * वापसs number of bytes written (including trailing nul)
 */
पूर्णांक copy_path_name(अक्षर *dst, स्थिर अक्षर *src)
अणु
	पूर्णांक name_len;

	/*
	 * PATH_MAX includes nul, so अगर म_माप(src) >= PATH_MAX it
	 * will truncate and म_माप(dst) will be PATH_MAX-1
	 */
	name_len = strscpy(dst, src, PATH_MAX);
	अगर (WARN_ON_ONCE(name_len < 0))
		name_len = PATH_MAX-1;

	/* we count the trailing nul */
	name_len++;
	वापस name_len;
पूर्ण

काष्ठा super_cb_data अणु
	व्योम *data;
	काष्ठा super_block *sb;
पूर्ण;

अटल व्योम tcp_super_cb(काष्ठा super_block *sb, व्योम *arg)
अणु
	काष्ठा super_cb_data *sd = arg;
	काष्ठा TCP_Server_Info *server = sd->data;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा cअगरs_tcon *tcon;

	अगर (sd->sb)
		वापस;

	cअगरs_sb = CIFS_SB(sb);
	tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	अगर (tcon->ses->server == server)
		sd->sb = sb;
पूर्ण

अटल काष्ठा super_block *__cअगरs_get_super(व्योम (*f)(काष्ठा super_block *, व्योम *),
					    व्योम *data)
अणु
	काष्ठा super_cb_data sd = अणु
		.data = data,
		.sb = शून्य,
	पूर्ण;

	iterate_supers_type(&cअगरs_fs_type, f, &sd);

	अगर (!sd.sb)
		वापस ERR_PTR(-EINVAL);
	/*
	 * Grab an active reference in order to prevent स्वतःmounts (DFS links)
	 * of expiring and then मुक्तing up our cअगरs superblock poपूर्णांकer जबतक
	 * we're करोing failover.
	 */
	cअगरs_sb_active(sd.sb);
	वापस sd.sb;
पूर्ण

अटल व्योम __cअगरs_put_super(काष्ठा super_block *sb)
अणु
	अगर (!IS_ERR_OR_शून्य(sb))
		cअगरs_sb_deactive(sb);
पूर्ण

काष्ठा super_block *cअगरs_get_tcp_super(काष्ठा TCP_Server_Info *server)
अणु
	वापस __cअगरs_get_super(tcp_super_cb, server);
पूर्ण

व्योम cअगरs_put_tcp_super(काष्ठा super_block *sb)
अणु
	__cअगरs_put_super(sb);
पूर्ण

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
पूर्णांक match_target_ip(काष्ठा TCP_Server_Info *server,
		    स्थिर अक्षर *share, माप_प्रकार share_len,
		    bool *result)
अणु
	पूर्णांक rc;
	अक्षर *target, *tip = शून्य;
	काष्ठा sockaddr tipaddr;

	*result = false;

	target = kzalloc(share_len + 3, GFP_KERNEL);
	अगर (!target) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	scnम_लिखो(target, share_len + 3, "\\\\%.*s", (पूर्णांक)share_len, share);

	cअगरs_dbg(FYI, "%s: target name: %s\n", __func__, target + 2);

	rc = dns_resolve_server_name_to_ip(target, &tip);
	अगर (rc < 0)
		जाओ out;

	cअगरs_dbg(FYI, "%s: target ip: %s\n", __func__, tip);

	अगर (!cअगरs_convert_address(&tipaddr, tip, म_माप(tip))) अणु
		cअगरs_dbg(VFS, "%s: failed to convert target ip address\n",
			 __func__);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	*result = cअगरs_match_ipaddr((काष्ठा sockaddr *)&server->dstaddr,
				    &tipaddr);
	cअगरs_dbg(FYI, "%s: ip addresses match: %u\n", __func__, *result);
	rc = 0;

out:
	kमुक्त(target);
	kमुक्त(tip);

	वापस rc;
पूर्ण

अटल व्योम tcon_super_cb(काष्ठा super_block *sb, व्योम *arg)
अणु
	काष्ठा super_cb_data *sd = arg;
	काष्ठा cअगरs_tcon *tcon = sd->data;
	काष्ठा cअगरs_sb_info *cअगरs_sb;

	अगर (sd->sb)
		वापस;

	cअगरs_sb = CIFS_SB(sb);
	अगर (tcon->dfs_path && cअगरs_sb->origin_fullpath &&
	    !strहालcmp(tcon->dfs_path, cअगरs_sb->origin_fullpath))
		sd->sb = sb;
पूर्ण

अटल अंतरभूत काष्ठा super_block *cअगरs_get_tcon_super(काष्ठा cअगरs_tcon *tcon)
अणु
	वापस __cअगरs_get_super(tcon_super_cb, tcon);
पूर्ण

अटल अंतरभूत व्योम cअगरs_put_tcon_super(काष्ठा super_block *sb)
अणु
	__cअगरs_put_super(sb);
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा super_block *cअगरs_get_tcon_super(काष्ठा cअगरs_tcon *tcon)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम cअगरs_put_tcon_super(काष्ठा super_block *sb)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक update_super_prepath(काष्ठा cअगरs_tcon *tcon, अक्षर *prefix)
अणु
	काष्ठा super_block *sb;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	पूर्णांक rc = 0;

	sb = cअगरs_get_tcon_super(tcon);
	अगर (IS_ERR(sb))
		वापस PTR_ERR(sb);

	cअगरs_sb = CIFS_SB(sb);

	kमुक्त(cअगरs_sb->prepath);

	अगर (prefix && *prefix) अणु
		cअगरs_sb->prepath = kstrdup(prefix, GFP_ATOMIC);
		अगर (!cअगरs_sb->prepath) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		convert_delimiter(cअगरs_sb->prepath, CIFS_सूची_SEP(cअगरs_sb));
	पूर्ण अन्यथा
		cअगरs_sb->prepath = शून्य;

	cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_USE_PREFIX_PATH;

out:
	cअगरs_put_tcon_super(sb);
	वापस rc;
पूर्ण
