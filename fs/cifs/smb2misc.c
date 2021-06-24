<शैली गुरु>
/*
 *   fs/cअगरs/smb2misc.c
 *
 *   Copyright (C) International Business Machines  Corp., 2002,2011
 *                 Etersoft, 2012
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *              Pavel Shilovsky (pshilovsky@samba.org) 2012
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
#समावेश <linux/प्रकार.स>
#समावेश "smb2pdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "smb2proto.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_unicode.h"
#समावेश "smb2status.h"
#समावेश "smb2glob.h"
#समावेश "nterr.h"

अटल पूर्णांक
check_smb2_hdr(काष्ठा smb2_sync_hdr *shdr, __u64 mid)
अणु
	__u64 wire_mid = le64_to_cpu(shdr->MessageId);

	/*
	 * Make sure that this really is an SMB, that it is a response,
	 * and that the message ids match.
	 */
	अगर ((shdr->ProtocolId == SMB2_PROTO_NUMBER) &&
	    (mid == wire_mid)) अणु
		अगर (shdr->Flags & SMB2_FLAGS_SERVER_TO_REसूची)
			वापस 0;
		अन्यथा अणु
			/* only one valid हाल where server sends us request */
			अगर (shdr->Command == SMB2_OPLOCK_BREAK)
				वापस 0;
			अन्यथा
				cअगरs_dbg(VFS, "Received Request not response\n");
		पूर्ण
	पूर्ण अन्यथा अणु /* bad signature or mid */
		अगर (shdr->ProtocolId != SMB2_PROTO_NUMBER)
			cअगरs_dbg(VFS, "Bad protocol string signature header %x\n",
				 le32_to_cpu(shdr->ProtocolId));
		अगर (mid != wire_mid)
			cअगरs_dbg(VFS, "Mids do not match: %llu and %llu\n",
				 mid, wire_mid);
	पूर्ण
	cअगरs_dbg(VFS, "Bad SMB detected. The Mid=%llu\n", wire_mid);
	वापस 1;
पूर्ण

/*
 *  The following table defines the expected "StructureSize" of SMB2 responses
 *  in order by SMB2 command.  This is similar to "wct" in SMB/CIFS responses.
 *
 *  Note that commands are defined in smb2pdu.h in le16 but the array below is
 *  indexed by command in host byte order
 */
अटल स्थिर __le16 smb2_rsp_काष्ठा_sizes[NUMBER_OF_SMB2_COMMANDS] = अणु
	/* SMB2_NEGOTIATE */ cpu_to_le16(65),
	/* SMB2_SESSION_SETUP */ cpu_to_le16(9),
	/* SMB2_LOGOFF */ cpu_to_le16(4),
	/* SMB2_TREE_CONNECT */ cpu_to_le16(16),
	/* SMB2_TREE_DISCONNECT */ cpu_to_le16(4),
	/* SMB2_CREATE */ cpu_to_le16(89),
	/* SMB2_CLOSE */ cpu_to_le16(60),
	/* SMB2_FLUSH */ cpu_to_le16(4),
	/* SMB2_READ */ cpu_to_le16(17),
	/* SMB2_WRITE */ cpu_to_le16(17),
	/* SMB2_LOCK */ cpu_to_le16(4),
	/* SMB2_IOCTL */ cpu_to_le16(49),
	/* BB CHECK this ... not listed in करोcumentation */
	/* SMB2_CANCEL */ cpu_to_le16(0),
	/* SMB2_ECHO */ cpu_to_le16(4),
	/* SMB2_QUERY_सूचीECTORY */ cpu_to_le16(9),
	/* SMB2_CHANGE_NOTIFY */ cpu_to_le16(9),
	/* SMB2_QUERY_INFO */ cpu_to_le16(9),
	/* SMB2_SET_INFO */ cpu_to_le16(2),
	/* BB FIXME can also be 44 क्रम lease अवरोध */
	/* SMB2_OPLOCK_BREAK */ cpu_to_le16(24)
पूर्ण;

#घोषणा SMB311_NEGPROT_BASE_SIZE (माप(काष्ठा smb2_sync_hdr) + माप(काष्ठा smb2_negotiate_rsp))

अटल __u32 get_neg_ctxt_len(काष्ठा smb2_sync_hdr *hdr, __u32 len,
			      __u32 non_ctxlen)
अणु
	__u16 neg_count;
	__u32 nc_offset, size_of_pad_beक्रमe_neg_ctxts;
	काष्ठा smb2_negotiate_rsp *pneg_rsp = (काष्ठा smb2_negotiate_rsp *)hdr;

	/* Negotiate contexts are only valid क्रम latest dialect SMB3.11 */
	neg_count = le16_to_cpu(pneg_rsp->NegotiateContextCount);
	अगर ((neg_count == 0) ||
	   (pneg_rsp->DialectRevision != cpu_to_le16(SMB311_PROT_ID)))
		वापस 0;

	/*
	 * अगर SPNEGO blob present (ie the RFC2478 GSS info which indicates
	 * which security mechanisms the server supports) make sure that
	 * the negotiate contexts start after it
	 */
	nc_offset = le32_to_cpu(pneg_rsp->NegotiateContextOffset);
	/*
	 * non_ctxlen is at least shdr->StructureSize + pdu->StructureSize2
	 * and the latter is 1 byte bigger than the fix-sized area of the
	 * NEGOTIATE response
	 */
	अगर (nc_offset + 1 < non_ctxlen) अणु
		pr_warn_once("Invalid negotiate context offset %d\n", nc_offset);
		वापस 0;
	पूर्ण अन्यथा अगर (nc_offset + 1 == non_ctxlen) अणु
		cअगरs_dbg(FYI, "no SPNEGO security blob in negprot rsp\n");
		size_of_pad_beक्रमe_neg_ctxts = 0;
	पूर्ण अन्यथा अगर (non_ctxlen == SMB311_NEGPROT_BASE_SIZE)
		/* has padding, but no SPNEGO blob */
		size_of_pad_beक्रमe_neg_ctxts = nc_offset - non_ctxlen + 1;
	अन्यथा
		size_of_pad_beक्रमe_neg_ctxts = nc_offset - non_ctxlen;

	/* Verअगरy that at least minimal negotiate contexts fit within frame */
	अगर (len < nc_offset + (neg_count * माप(काष्ठा smb2_neg_context))) अणु
		pr_warn_once("negotiate context goes beyond end\n");
		वापस 0;
	पूर्ण

	cअगरs_dbg(FYI, "length of negcontexts %d pad %d\n",
		len - nc_offset, size_of_pad_beक्रमe_neg_ctxts);

	/* length of negcontexts including pad from end of sec blob to them */
	वापस (len - nc_offset) + size_of_pad_beक्रमe_neg_ctxts;
पूर्ण

पूर्णांक
smb2_check_message(अक्षर *buf, अचिन्हित पूर्णांक len, काष्ठा TCP_Server_Info *srvr)
अणु
	काष्ठा smb2_sync_hdr *shdr = (काष्ठा smb2_sync_hdr *)buf;
	काष्ठा smb2_sync_pdu *pdu = (काष्ठा smb2_sync_pdu *)shdr;
	__u64 mid;
	__u32 clc_len;  /* calculated length */
	पूर्णांक command;
	पूर्णांक pdu_size = माप(काष्ठा smb2_sync_pdu);
	पूर्णांक hdr_size = माप(काष्ठा smb2_sync_hdr);

	/*
	 * Add function to करो table lookup of StructureSize by command
	 * ie Validate the wct via smb2_काष्ठा_sizes table above
	 */
	अगर (shdr->ProtocolId == SMB2_TRANSFORM_PROTO_NUM) अणु
		काष्ठा smb2_transक्रमm_hdr *thdr =
			(काष्ठा smb2_transक्रमm_hdr *)buf;
		काष्ठा cअगरs_ses *ses = शून्य;
		काष्ठा list_head *पंचांगp;

		/* decrypt frame now that it is completely पढ़ो in */
		spin_lock(&cअगरs_tcp_ses_lock);
		list_क्रम_each(पंचांगp, &srvr->smb_ses_list) अणु
			ses = list_entry(पंचांगp, काष्ठा cअगरs_ses, smb_ses_list);
			अगर (ses->Suid == thdr->SessionId)
				अवरोध;

			ses = शून्य;
		पूर्ण
		spin_unlock(&cअगरs_tcp_ses_lock);
		अगर (ses == शून्य) अणु
			cअगरs_dbg(VFS, "no decryption - session id not found\n");
			वापस 1;
		पूर्ण
	पूर्ण

	mid = le64_to_cpu(shdr->MessageId);
	अगर (len < pdu_size) अणु
		अगर ((len >= hdr_size)
		    && (shdr->Status != 0)) अणु
			pdu->StructureSize2 = 0;
			/*
			 * As with SMB/CIFS, on some error हालs servers may
			 * not वापस wct properly
			 */
			वापस 0;
		पूर्ण अन्यथा अणु
			cअगरs_dbg(VFS, "Length less than SMB header size\n");
		पूर्ण
		वापस 1;
	पूर्ण
	अगर (len > CIFSMaxBufSize + MAX_SMB2_HDR_SIZE) अणु
		cअगरs_dbg(VFS, "SMB length greater than maximum, mid=%llu\n",
			 mid);
		वापस 1;
	पूर्ण

	अगर (check_smb2_hdr(shdr, mid))
		वापस 1;

	अगर (shdr->StructureSize != SMB2_HEADER_STRUCTURE_SIZE) अणु
		cअगरs_dbg(VFS, "Invalid structure size %u\n",
			 le16_to_cpu(shdr->StructureSize));
		वापस 1;
	पूर्ण

	command = le16_to_cpu(shdr->Command);
	अगर (command >= NUMBER_OF_SMB2_COMMANDS) अणु
		cअगरs_dbg(VFS, "Invalid SMB2 command %d\n", command);
		वापस 1;
	पूर्ण

	अगर (smb2_rsp_काष्ठा_sizes[command] != pdu->StructureSize2) अणु
		अगर (command != SMB2_OPLOCK_BREAK_HE && (shdr->Status == 0 ||
		    pdu->StructureSize2 != SMB2_ERROR_STRUCTURE_SIZE2)) अणु
			/* error packets have 9 byte काष्ठाure size */
			cअगरs_dbg(VFS, "Invalid response size %u for command %d\n",
				 le16_to_cpu(pdu->StructureSize2), command);
			वापस 1;
		पूर्ण अन्यथा अगर (command == SMB2_OPLOCK_BREAK_HE
			   && (shdr->Status == 0)
			   && (le16_to_cpu(pdu->StructureSize2) != 44)
			   && (le16_to_cpu(pdu->StructureSize2) != 36)) अणु
			/* special हाल क्रम SMB2.1 lease अवरोध message */
			cअगरs_dbg(VFS, "Invalid response size %d for oplock break\n",
				 le16_to_cpu(pdu->StructureSize2));
			वापस 1;
		पूर्ण
	पूर्ण

	clc_len = smb2_calc_size(buf, srvr);

	अगर (shdr->Command == SMB2_NEGOTIATE)
		clc_len += get_neg_ctxt_len(shdr, len, clc_len);

	अगर (len != clc_len) अणु
		cअगरs_dbg(FYI, "Calculated size %u length %u mismatch mid %llu\n",
			 clc_len, len, mid);
		/* create failed on symlink */
		अगर (command == SMB2_CREATE_HE &&
		    shdr->Status == STATUS_STOPPED_ON_SYMLINK)
			वापस 0;
		/* Winकरोws 7 server वापसs 24 bytes more */
		अगर (clc_len + 24 == len && command == SMB2_OPLOCK_BREAK_HE)
			वापस 0;
		/* server can वापस one byte more due to implied bcc[0] */
		अगर (clc_len == len + 1)
			वापस 0;

		/*
		 * Some winकरोws servers (win2016) will pad also the final
		 * PDU in a compound to 8 bytes.
		 */
		अगर (((clc_len + 7) & ~7) == len)
			वापस 0;

		/*
		 * MacOS server pads after SMB2.1 ग_लिखो response with 3 bytes
		 * of junk. Other servers match RFC1001 len to actual
		 * SMB2/SMB3 frame length (header + smb2 response specअगरic data)
		 * Some winकरोws servers also pad up to 8 bytes when compounding.
		 */
		अगर (clc_len < len)
			वापस 0;

		pr_warn_once(
			"srv rsp too short, len %d not %d. cmd:%d mid:%llu\n",
			len, clc_len, command, mid);

		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * The size of the variable area depends on the offset and length fields
 * located in dअगरferent fields क्रम various SMB2 responses. SMB2 responses
 * with no variable length info, show an offset of zero क्रम the offset field.
 */
अटल स्थिर bool has_smb2_data_area[NUMBER_OF_SMB2_COMMANDS] = अणु
	/* SMB2_NEGOTIATE */ true,
	/* SMB2_SESSION_SETUP */ true,
	/* SMB2_LOGOFF */ false,
	/* SMB2_TREE_CONNECT */	false,
	/* SMB2_TREE_DISCONNECT */ false,
	/* SMB2_CREATE */ true,
	/* SMB2_CLOSE */ false,
	/* SMB2_FLUSH */ false,
	/* SMB2_READ */	true,
	/* SMB2_WRITE */ false,
	/* SMB2_LOCK */	false,
	/* SMB2_IOCTL */ true,
	/* SMB2_CANCEL */ false, /* BB CHECK this not listed in करोcumentation */
	/* SMB2_ECHO */ false,
	/* SMB2_QUERY_सूचीECTORY */ true,
	/* SMB2_CHANGE_NOTIFY */ true,
	/* SMB2_QUERY_INFO */ true,
	/* SMB2_SET_INFO */ false,
	/* SMB2_OPLOCK_BREAK */ false
पूर्ण;

/*
 * Returns the poपूर्णांकer to the beginning of the data area. Length of the data
 * area and the offset to it (from the beginning of the smb are also वापसed.
 */
अक्षर *
smb2_get_data_area_len(पूर्णांक *off, पूर्णांक *len, काष्ठा smb2_sync_hdr *shdr)
अणु
	*off = 0;
	*len = 0;

	/* error responses करो not have data area */
	अगर (shdr->Status && shdr->Status != STATUS_MORE_PROCESSING_REQUIRED &&
	    (((काष्ठा smb2_err_rsp *)shdr)->StructureSize) ==
						SMB2_ERROR_STRUCTURE_SIZE2)
		वापस शून्य;

	/*
	 * Following commands have data areas so we have to get the location
	 * of the data buffer offset and data buffer length क्रम the particular
	 * command.
	 */
	चयन (shdr->Command) अणु
	हाल SMB2_NEGOTIATE:
		*off = le16_to_cpu(
		  ((काष्ठा smb2_negotiate_rsp *)shdr)->SecurityBufferOffset);
		*len = le16_to_cpu(
		  ((काष्ठा smb2_negotiate_rsp *)shdr)->SecurityBufferLength);
		अवरोध;
	हाल SMB2_SESSION_SETUP:
		*off = le16_to_cpu(
		  ((काष्ठा smb2_sess_setup_rsp *)shdr)->SecurityBufferOffset);
		*len = le16_to_cpu(
		  ((काष्ठा smb2_sess_setup_rsp *)shdr)->SecurityBufferLength);
		अवरोध;
	हाल SMB2_CREATE:
		*off = le32_to_cpu(
		    ((काष्ठा smb2_create_rsp *)shdr)->CreateContextsOffset);
		*len = le32_to_cpu(
		    ((काष्ठा smb2_create_rsp *)shdr)->CreateContextsLength);
		अवरोध;
	हाल SMB2_QUERY_INFO:
		*off = le16_to_cpu(
		    ((काष्ठा smb2_query_info_rsp *)shdr)->OutputBufferOffset);
		*len = le32_to_cpu(
		    ((काष्ठा smb2_query_info_rsp *)shdr)->OutputBufferLength);
		अवरोध;
	हाल SMB2_READ:
		/* TODO: is this a bug ? */
		*off = ((काष्ठा smb2_पढ़ो_rsp *)shdr)->DataOffset;
		*len = le32_to_cpu(((काष्ठा smb2_पढ़ो_rsp *)shdr)->DataLength);
		अवरोध;
	हाल SMB2_QUERY_सूचीECTORY:
		*off = le16_to_cpu(
		  ((काष्ठा smb2_query_directory_rsp *)shdr)->OutputBufferOffset);
		*len = le32_to_cpu(
		  ((काष्ठा smb2_query_directory_rsp *)shdr)->OutputBufferLength);
		अवरोध;
	हाल SMB2_IOCTL:
		*off = le32_to_cpu(
		  ((काष्ठा smb2_ioctl_rsp *)shdr)->OutputOffset);
		*len = le32_to_cpu(
		  ((काष्ठा smb2_ioctl_rsp *)shdr)->OutputCount);
		अवरोध;
	हाल SMB2_CHANGE_NOTIFY:
		*off = le16_to_cpu(
		  ((काष्ठा smb2_change_notअगरy_rsp *)shdr)->OutputBufferOffset);
		*len = le32_to_cpu(
		  ((काष्ठा smb2_change_notअगरy_rsp *)shdr)->OutputBufferLength);
		अवरोध;
	शेष:
		cअगरs_dbg(VFS, "no length check for command %d\n", le16_to_cpu(shdr->Command));
		अवरोध;
	पूर्ण

	/*
	 * Invalid length or offset probably means data area is invalid, but
	 * we have little choice but to ignore the data area in this हाल.
	 */
	अगर (*off > 4096) अणु
		cअगरs_dbg(VFS, "offset %d too large, data area ignored\n", *off);
		*len = 0;
		*off = 0;
	पूर्ण अन्यथा अगर (*off < 0) अणु
		cअगरs_dbg(VFS, "negative offset %d to data invalid ignore data area\n",
			 *off);
		*off = 0;
		*len = 0;
	पूर्ण अन्यथा अगर (*len < 0) अणु
		cअगरs_dbg(VFS, "negative data length %d invalid, data area ignored\n",
			 *len);
		*len = 0;
	पूर्ण अन्यथा अगर (*len > 128 * 1024) अणु
		cअगरs_dbg(VFS, "data area larger than 128K: %d\n", *len);
		*len = 0;
	पूर्ण

	/* वापस poपूर्णांकer to beginning of data area, ie offset from SMB start */
	अगर ((*off != 0) && (*len != 0))
		वापस (अक्षर *)shdr + *off;
	अन्यथा
		वापस शून्य;
पूर्ण

/*
 * Calculate the size of the SMB message based on the fixed header
 * portion, the number of word parameters and the data portion of the message.
 */
अचिन्हित पूर्णांक
smb2_calc_size(व्योम *buf, काष्ठा TCP_Server_Info *srvr)
अणु
	काष्ठा smb2_sync_pdu *pdu = (काष्ठा smb2_sync_pdu *)buf;
	काष्ठा smb2_sync_hdr *shdr = &pdu->sync_hdr;
	पूर्णांक offset; /* the offset from the beginning of SMB to data area */
	पूर्णांक data_length; /* the length of the variable length data area */
	/* Structure Size has alपढ़ोy been checked to make sure it is 64 */
	पूर्णांक len = le16_to_cpu(shdr->StructureSize);

	/*
	 * StructureSize2, ie length of fixed parameter area has alपढ़ोy
	 * been checked to make sure it is the correct length.
	 */
	len += le16_to_cpu(pdu->StructureSize2);

	अगर (has_smb2_data_area[le16_to_cpu(shdr->Command)] == false)
		जाओ calc_size_निकास;

	smb2_get_data_area_len(&offset, &data_length, shdr);
	cअगरs_dbg(FYI, "SMB2 data length %d offset %d\n", data_length, offset);

	अगर (data_length > 0) अणु
		/*
		 * Check to make sure that data area begins after fixed area,
		 * Note that last byte of the fixed area is part of data area
		 * क्रम some commands, typically those with odd StructureSize,
		 * so we must add one to the calculation.
		 */
		अगर (offset + 1 < len) अणु
			cअगरs_dbg(VFS, "data area offset %d overlaps SMB2 header %d\n",
				 offset + 1, len);
			data_length = 0;
		पूर्ण अन्यथा अणु
			len = offset + data_length;
		पूर्ण
	पूर्ण
calc_size_निकास:
	cअगरs_dbg(FYI, "SMB2 len %d\n", len);
	वापस len;
पूर्ण

/* Note: caller must मुक्त वापस buffer */
__le16 *
cअगरs_convert_path_to_utf16(स्थिर अक्षर *from, काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	पूर्णांक len;
	स्थिर अक्षर *start_of_path;
	__le16 *to;
	पूर्णांक map_type;

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MAP_SFM_CHR)
		map_type = SFM_MAP_UNI_RSVD;
	अन्यथा अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MAP_SPECIAL_CHR)
		map_type = SFU_MAP_UNI_RSVD;
	अन्यथा
		map_type = NO_MAP_UNI_RSVD;

	/* Winकरोws करोesn't allow paths beginning with \ */
	अगर (from[0] == '\\')
		start_of_path = from + 1;

	/* SMB311 POSIX extensions paths करो not include leading slash */
	अन्यथा अगर (cअगरs_sb_master_tlink(cअगरs_sb) &&
		 cअगरs_sb_master_tcon(cअगरs_sb)->posix_extensions &&
		 (from[0] == '/')) अणु
		start_of_path = from + 1;
	पूर्ण अन्यथा
		start_of_path = from;

	to = cअगरs_strndup_to_utf16(start_of_path, PATH_MAX, &len,
				   cअगरs_sb->local_nls, map_type);
	वापस to;
पूर्ण

__le32
smb2_get_lease_state(काष्ठा cअगरsInodeInfo *cinode)
अणु
	__le32 lease = 0;

	अगर (CIFS_CACHE_WRITE(cinode))
		lease |= SMB2_LEASE_WRITE_CACHING;
	अगर (CIFS_CACHE_HANDLE(cinode))
		lease |= SMB2_LEASE_HANDLE_CACHING;
	अगर (CIFS_CACHE_READ(cinode))
		lease |= SMB2_LEASE_READ_CACHING;
	वापस lease;
पूर्ण

काष्ठा smb2_lease_अवरोध_work अणु
	काष्ठा work_काष्ठा lease_अवरोध;
	काष्ठा tcon_link *tlink;
	__u8 lease_key[16];
	__le32 lease_state;
पूर्ण;

अटल व्योम
cअगरs_ses_oplock_अवरोध(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smb2_lease_अवरोध_work *lw = container_of(work,
				काष्ठा smb2_lease_अवरोध_work, lease_अवरोध);
	पूर्णांक rc = 0;

	rc = SMB2_lease_अवरोध(0, tlink_tcon(lw->tlink), lw->lease_key,
			      lw->lease_state);

	cअगरs_dbg(FYI, "Lease release rc %d\n", rc);
	cअगरs_put_tlink(lw->tlink);
	kमुक्त(lw);
पूर्ण

अटल व्योम
smb2_queue_pending_खोलो_अवरोध(काष्ठा tcon_link *tlink, __u8 *lease_key,
			      __le32 new_lease_state)
अणु
	काष्ठा smb2_lease_अवरोध_work *lw;

	lw = kदो_स्मृति(माप(काष्ठा smb2_lease_अवरोध_work), GFP_KERNEL);
	अगर (!lw) अणु
		cअगरs_put_tlink(tlink);
		वापस;
	पूर्ण

	INIT_WORK(&lw->lease_अवरोध, cअगरs_ses_oplock_अवरोध);
	lw->tlink = tlink;
	lw->lease_state = new_lease_state;
	स_नकल(lw->lease_key, lease_key, SMB2_LEASE_KEY_SIZE);
	queue_work(cअगरsiod_wq, &lw->lease_अवरोध);
पूर्ण

अटल bool
smb2_tcon_has_lease(काष्ठा cअगरs_tcon *tcon, काष्ठा smb2_lease_अवरोध *rsp)
अणु
	__u8 lease_state;
	काष्ठा list_head *पंचांगp;
	काष्ठा cअगरsFileInfo *cfile;
	काष्ठा cअगरsInodeInfo *cinode;
	पूर्णांक ack_req = le32_to_cpu(rsp->Flags &
				  SMB2_NOTIFY_BREAK_LEASE_FLAG_ACK_REQUIRED);

	lease_state = le32_to_cpu(rsp->NewLeaseState);

	list_क्रम_each(पंचांगp, &tcon->खोलोFileList) अणु
		cfile = list_entry(पंचांगp, काष्ठा cअगरsFileInfo, tlist);
		cinode = CIFS_I(d_inode(cfile->dentry));

		अगर (स_भेद(cinode->lease_key, rsp->LeaseKey,
							SMB2_LEASE_KEY_SIZE))
			जारी;

		cअगरs_dbg(FYI, "found in the open list\n");
		cअगरs_dbg(FYI, "lease key match, lease break 0x%x\n",
			 lease_state);

		अगर (ack_req)
			cfile->oplock_अवरोध_cancelled = false;
		अन्यथा
			cfile->oplock_अवरोध_cancelled = true;

		set_bit(CIFS_INODE_PENDING_OPLOCK_BREAK, &cinode->flags);

		cfile->oplock_epoch = le16_to_cpu(rsp->Epoch);
		cfile->oplock_level = lease_state;

		cअगरs_queue_oplock_अवरोध(cfile);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा cअगरs_pending_खोलो *
smb2_tcon_find_pending_खोलो_lease(काष्ठा cअगरs_tcon *tcon,
				  काष्ठा smb2_lease_अवरोध *rsp)
अणु
	__u8 lease_state = le32_to_cpu(rsp->NewLeaseState);
	पूर्णांक ack_req = le32_to_cpu(rsp->Flags &
				  SMB2_NOTIFY_BREAK_LEASE_FLAG_ACK_REQUIRED);
	काष्ठा cअगरs_pending_खोलो *खोलो;
	काष्ठा cअगरs_pending_खोलो *found = शून्य;

	list_क्रम_each_entry(खोलो, &tcon->pending_खोलोs, olist) अणु
		अगर (स_भेद(खोलो->lease_key, rsp->LeaseKey,
			   SMB2_LEASE_KEY_SIZE))
			जारी;

		अगर (!found && ack_req) अणु
			found = खोलो;
		पूर्ण

		cअगरs_dbg(FYI, "found in the pending open list\n");
		cअगरs_dbg(FYI, "lease key match, lease break 0x%x\n",
			 lease_state);

		खोलो->oplock = lease_state;
	पूर्ण

	वापस found;
पूर्ण

अटल bool
smb2_is_valid_lease_अवरोध(अक्षर *buffer)
अणु
	काष्ठा smb2_lease_अवरोध *rsp = (काष्ठा smb2_lease_अवरोध *)buffer;
	काष्ठा list_head *पंचांगp, *पंचांगp1, *पंचांगp2;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरs_pending_खोलो *खोलो;

	cअगरs_dbg(FYI, "Checking for lease break\n");

	/* look up tcon based on tid & uid */
	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each(पंचांगp, &cअगरs_tcp_ses_list) अणु
		server = list_entry(पंचांगp, काष्ठा TCP_Server_Info, tcp_ses_list);

		list_क्रम_each(पंचांगp1, &server->smb_ses_list) अणु
			ses = list_entry(पंचांगp1, काष्ठा cअगरs_ses, smb_ses_list);

			list_क्रम_each(पंचांगp2, &ses->tcon_list) अणु
				tcon = list_entry(पंचांगp2, काष्ठा cअगरs_tcon,
						  tcon_list);
				spin_lock(&tcon->खोलो_file_lock);
				cअगरs_stats_inc(
				    &tcon->stats.cअगरs_stats.num_oplock_brks);
				अगर (smb2_tcon_has_lease(tcon, rsp)) अणु
					spin_unlock(&tcon->खोलो_file_lock);
					spin_unlock(&cअगरs_tcp_ses_lock);
					वापस true;
				पूर्ण
				खोलो = smb2_tcon_find_pending_खोलो_lease(tcon,
									 rsp);
				अगर (खोलो) अणु
					__u8 lease_key[SMB2_LEASE_KEY_SIZE];
					काष्ठा tcon_link *tlink;

					tlink = cअगरs_get_tlink(खोलो->tlink);
					स_नकल(lease_key, खोलो->lease_key,
					       SMB2_LEASE_KEY_SIZE);
					spin_unlock(&tcon->खोलो_file_lock);
					spin_unlock(&cअगरs_tcp_ses_lock);
					smb2_queue_pending_खोलो_अवरोध(tlink,
								      lease_key,
								      rsp->NewLeaseState);
					वापस true;
				पूर्ण
				spin_unlock(&tcon->खोलो_file_lock);

				अगर (tcon->crfid.is_valid &&
				    !स_भेद(rsp->LeaseKey,
					    tcon->crfid.fid->lease_key,
					    SMB2_LEASE_KEY_SIZE)) अणु
					tcon->crfid.समय = 0;
					INIT_WORK(&tcon->crfid.lease_अवरोध,
						  smb2_cached_lease_अवरोध);
					queue_work(cअगरsiod_wq,
						   &tcon->crfid.lease_अवरोध);
					spin_unlock(&cअगरs_tcp_ses_lock);
					वापस true;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&cअगरs_tcp_ses_lock);
	cअगरs_dbg(FYI, "Can not process lease break - no lease matched\n");
	वापस false;
पूर्ण

bool
smb2_is_valid_oplock_अवरोध(अक्षर *buffer, काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा smb2_oplock_अवरोध *rsp = (काष्ठा smb2_oplock_अवरोध *)buffer;
	काष्ठा list_head *पंचांगp, *पंचांगp1, *पंचांगp2;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरsInodeInfo *cinode;
	काष्ठा cअगरsFileInfo *cfile;

	cअगरs_dbg(FYI, "Checking for oplock break\n");

	अगर (rsp->sync_hdr.Command != SMB2_OPLOCK_BREAK)
		वापस false;

	अगर (rsp->StructureSize !=
				smb2_rsp_काष्ठा_sizes[SMB2_OPLOCK_BREAK_HE]) अणु
		अगर (le16_to_cpu(rsp->StructureSize) == 44)
			वापस smb2_is_valid_lease_अवरोध(buffer);
		अन्यथा
			वापस false;
	पूर्ण

	cअगरs_dbg(FYI, "oplock level 0x%x\n", rsp->OplockLevel);

	/* look up tcon based on tid & uid */
	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each(पंचांगp, &server->smb_ses_list) अणु
		ses = list_entry(पंचांगp, काष्ठा cअगरs_ses, smb_ses_list);

		list_क्रम_each(पंचांगp1, &ses->tcon_list) अणु
			tcon = list_entry(पंचांगp1, काष्ठा cअगरs_tcon, tcon_list);

			spin_lock(&tcon->खोलो_file_lock);
			list_क्रम_each(पंचांगp2, &tcon->खोलोFileList) अणु
				cfile = list_entry(पंचांगp2, काष्ठा cअगरsFileInfo,
						     tlist);
				अगर (rsp->PersistentFid !=
				    cfile->fid.persistent_fid ||
				    rsp->VolatileFid !=
				    cfile->fid.अस्थिर_fid)
					जारी;

				cअगरs_dbg(FYI, "file id match, oplock break\n");
				cअगरs_stats_inc(
				    &tcon->stats.cअगरs_stats.num_oplock_brks);
				cinode = CIFS_I(d_inode(cfile->dentry));
				spin_lock(&cfile->file_info_lock);
				अगर (!CIFS_CACHE_WRITE(cinode) &&
				    rsp->OplockLevel == SMB2_OPLOCK_LEVEL_NONE)
					cfile->oplock_अवरोध_cancelled = true;
				अन्यथा
					cfile->oplock_अवरोध_cancelled = false;

				set_bit(CIFS_INODE_PENDING_OPLOCK_BREAK,
					&cinode->flags);

				cfile->oplock_epoch = 0;
				cfile->oplock_level = rsp->OplockLevel;

				spin_unlock(&cfile->file_info_lock);

				cअगरs_queue_oplock_अवरोध(cfile);

				spin_unlock(&tcon->खोलो_file_lock);
				spin_unlock(&cअगरs_tcp_ses_lock);
				वापस true;
			पूर्ण
			spin_unlock(&tcon->खोलो_file_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&cअगरs_tcp_ses_lock);
	cअगरs_dbg(FYI, "No file id matched, oplock break ignored\n");
	वापस true;
पूर्ण

व्योम
smb2_cancelled_बंद_fid(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा बंद_cancelled_खोलो *cancelled = container_of(work,
					काष्ठा बंद_cancelled_खोलो, work);
	काष्ठा cअगरs_tcon *tcon = cancelled->tcon;
	पूर्णांक rc;

	अगर (cancelled->mid)
		cअगरs_tcon_dbg(VFS, "Close unmatched open for MID:%llu\n",
			      cancelled->mid);
	अन्यथा
		cअगरs_tcon_dbg(VFS, "Close interrupted close\n");

	rc = SMB2_बंद(0, tcon, cancelled->fid.persistent_fid,
			cancelled->fid.अस्थिर_fid);
	अगर (rc)
		cअगरs_tcon_dbg(VFS, "Close cancelled mid failed rc:%d\n", rc);

	cअगरs_put_tcon(tcon);
	kमुक्त(cancelled);
पूर्ण

/*
 * Caller should alपढ़ोy has an extra reference to @tcon
 * This function is used to queue work to बंद a handle to prevent leaks
 * on the server.
 * We handle two हालs. If an खोलो was पूर्णांकerrupted after we sent the
 * SMB2_CREATE to the server but beक्रमe we processed the reply, and second
 * अगर a बंद was पूर्णांकerrupted beक्रमe we sent the SMB2_CLOSE to the server.
 */
अटल पूर्णांक
__smb2_handle_cancelled_cmd(काष्ठा cअगरs_tcon *tcon, __u16 cmd, __u64 mid,
			    __u64 persistent_fid, __u64 अस्थिर_fid)
अणु
	काष्ठा बंद_cancelled_खोलो *cancelled;

	cancelled = kzalloc(माप(*cancelled), GFP_ATOMIC);
	अगर (!cancelled)
		वापस -ENOMEM;

	cancelled->fid.persistent_fid = persistent_fid;
	cancelled->fid.अस्थिर_fid = अस्थिर_fid;
	cancelled->tcon = tcon;
	cancelled->cmd = cmd;
	cancelled->mid = mid;
	INIT_WORK(&cancelled->work, smb2_cancelled_बंद_fid);
	WARN_ON(queue_work(cअगरsiod_wq, &cancelled->work) == false);

	वापस 0;
पूर्ण

पूर्णांक
smb2_handle_cancelled_बंद(काष्ठा cअगरs_tcon *tcon, __u64 persistent_fid,
			    __u64 अस्थिर_fid)
अणु
	पूर्णांक rc;

	cअगरs_dbg(FYI, "%s: tc_count=%d\n", __func__, tcon->tc_count);
	spin_lock(&cअगरs_tcp_ses_lock);
	अगर (tcon->tc_count <= 0) अणु
		काष्ठा TCP_Server_Info *server = शून्य;

		WARN_ONCE(tcon->tc_count < 0, "tcon refcount is negative");
		spin_unlock(&cअगरs_tcp_ses_lock);

		अगर (tcon->ses)
			server = tcon->ses->server;

		cअगरs_server_dbg(FYI, "tid=%u: tcon is closing, skipping async close retry of fid %llu %llu\n",
				tcon->tid, persistent_fid, अस्थिर_fid);

		वापस 0;
	पूर्ण
	tcon->tc_count++;
	spin_unlock(&cअगरs_tcp_ses_lock);

	rc = __smb2_handle_cancelled_cmd(tcon, SMB2_CLOSE_HE, 0,
					 persistent_fid, अस्थिर_fid);
	अगर (rc)
		cअगरs_put_tcon(tcon);

	वापस rc;
पूर्ण

पूर्णांक
smb2_handle_cancelled_mid(काष्ठा mid_q_entry *mid, काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा smb2_sync_hdr *sync_hdr = mid->resp_buf;
	काष्ठा smb2_create_rsp *rsp = mid->resp_buf;
	काष्ठा cअगरs_tcon *tcon;
	पूर्णांक rc;

	अगर ((mid->optype & CIFS_CP_CREATE_CLOSE_OP) || sync_hdr->Command != SMB2_CREATE ||
	    sync_hdr->Status != STATUS_SUCCESS)
		वापस 0;

	tcon = smb2_find_smb_tcon(server, sync_hdr->SessionId,
				  sync_hdr->TreeId);
	अगर (!tcon)
		वापस -ENOENT;

	rc = __smb2_handle_cancelled_cmd(tcon,
					 le16_to_cpu(sync_hdr->Command),
					 le64_to_cpu(sync_hdr->MessageId),
					 rsp->PersistentFileId,
					 rsp->VolatileFileId);
	अगर (rc)
		cअगरs_put_tcon(tcon);

	वापस rc;
पूर्ण

/**
 * smb311_update_preauth_hash - update @ses hash with the packet data in @iov
 *
 * Assumes @iov करोes not contain the rfc1002 length and iov[0] has the
 * SMB2 header.
 *
 * @ses:	server session काष्ठाure
 * @iov:	array containing the SMB request we will send to the server
 * @nvec:	number of array entries क्रम the iov
 */
पूर्णांक
smb311_update_preauth_hash(काष्ठा cअगरs_ses *ses, काष्ठा kvec *iov, पूर्णांक nvec)
अणु
	पूर्णांक i, rc;
	काष्ठा sdesc *d;
	काष्ठा smb2_sync_hdr *hdr;
	काष्ठा TCP_Server_Info *server = cअगरs_ses_server(ses);

	hdr = (काष्ठा smb2_sync_hdr *)iov[0].iov_base;
	/* neg prot are always taken */
	अगर (hdr->Command == SMB2_NEGOTIATE)
		जाओ ok;

	/*
	 * If we process a command which wasn't a negprot it means the
	 * neg prot was alपढ़ोy करोne, so the server dialect was set
	 * and we can test it. Preauth requires 3.1.1 क्रम now.
	 */
	अगर (server->dialect != SMB311_PROT_ID)
		वापस 0;

	अगर (hdr->Command != SMB2_SESSION_SETUP)
		वापस 0;

	/* skip last sess setup response */
	अगर ((hdr->Flags & SMB2_FLAGS_SERVER_TO_REसूची)
	    && (hdr->Status == NT_STATUS_OK
		|| (hdr->Status !=
		    cpu_to_le32(NT_STATUS_MORE_PROCESSING_REQUIRED))))
		वापस 0;

ok:
	rc = smb311_crypto_shash_allocate(server);
	अगर (rc)
		वापस rc;

	d = server->secmech.sdescsha512;
	rc = crypto_shash_init(&d->shash);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not init sha512 shash\n", __func__);
		वापस rc;
	पूर्ण

	rc = crypto_shash_update(&d->shash, ses->preauth_sha_hash,
				 SMB2_PREAUTH_HASH_SIZE);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not update sha512 shash\n", __func__);
		वापस rc;
	पूर्ण

	क्रम (i = 0; i < nvec; i++) अणु
		rc = crypto_shash_update(&d->shash,
					 iov[i].iov_base, iov[i].iov_len);
		अगर (rc) अणु
			cअगरs_dbg(VFS, "%s: Could not update sha512 shash\n",
				 __func__);
			वापस rc;
		पूर्ण
	पूर्ण

	rc = crypto_shash_final(&d->shash, ses->preauth_sha_hash);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not finalize sha512 shash\n",
			 __func__);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण
