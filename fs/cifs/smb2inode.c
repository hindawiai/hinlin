<शैली गुरु>
/*
 *   fs/cअगरs/smb2inode.c
 *
 *   Copyright (C) International Business Machines  Corp., 2002, 2011
 *                 Etersoft, 2012
 *   Author(s): Pavel Shilovsky (pshilovsky@samba.org),
 *              Steve French (sfrench@us.ibm.com)
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
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <यंत्र/भाग64.h>
#समावेश "cifsfs.h"
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_fs_sb.h"
#समावेश "cifs_unicode.h"
#समावेश "fscache.h"
#समावेश "smb2glob.h"
#समावेश "smb2pdu.h"
#समावेश "smb2proto.h"

अटल व्योम
मुक्त_set_inf_compound(काष्ठा smb_rqst *rqst)
अणु
	अगर (rqst[1].rq_iov)
		SMB2_set_info_मुक्त(&rqst[1]);
	अगर (rqst[2].rq_iov)
		SMB2_बंद_मुक्त(&rqst[2]);
पूर्ण


काष्ठा cop_vars अणु
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा kvec rsp_iov[3];
	काष्ठा smb_rqst rqst[3];
	काष्ठा kvec खोलो_iov[SMB2_CREATE_IOV_SIZE];
	काष्ठा kvec qi_iov[1];
	काष्ठा kvec si_iov[SMB2_SET_INFO_IOV_SIZE];
	काष्ठा kvec बंद_iov[1];
	काष्ठा smb2_file_नाम_info नाम_info;
	काष्ठा smb2_file_link_info link_info;
पूर्ण;

अटल पूर्णांक
smb2_compound_op(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		 काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *full_path,
		 __u32 desired_access, __u32 create_disposition,
		 __u32 create_options, umode_t mode, व्योम *ptr, पूर्णांक command,
		 काष्ठा cअगरsFileInfo *cfile)
अणु
	काष्ठा cop_vars *vars = शून्य;
	काष्ठा kvec *rsp_iov;
	काष्ठा smb_rqst *rqst;
	पूर्णांक rc;
	__le16 *utf16_path = शून्य;
	__u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_ses *ses = tcon->ses;
	काष्ठा TCP_Server_Info *server;
	पूर्णांक num_rqst = 0;
	पूर्णांक resp_buftype[3];
	काष्ठा smb2_query_info_rsp *qi_rsp = शून्य;
	पूर्णांक flags = 0;
	__u8 delete_pending[8] = अणु1, 0, 0, 0, 0, 0, 0, 0पूर्ण;
	अचिन्हित पूर्णांक size[2];
	व्योम *data[2];
	पूर्णांक len;

	vars = kzalloc(माप(*vars), GFP_ATOMIC);
	अगर (vars == शून्य)
		वापस -ENOMEM;
	rqst = &vars->rqst[0];
	rsp_iov = &vars->rsp_iov[0];

	server = cअगरs_pick_channel(ses);

	अगर (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	resp_buftype[0] = resp_buftype[1] = resp_buftype[2] = CIFS_NO_BUFFER;

	/* We alपढ़ोy have a handle so we can skip the खोलो */
	अगर (cfile)
		जाओ after_खोलो;

	/* Open */
	utf16_path = cअगरs_convert_path_to_utf16(full_path, cअगरs_sb);
	अगर (!utf16_path) अणु
		rc = -ENOMEM;
		जाओ finished;
	पूर्ण

	vars->oparms.tcon = tcon;
	vars->oparms.desired_access = desired_access;
	vars->oparms.disposition = create_disposition;
	vars->oparms.create_options = cअगरs_create_options(cअगरs_sb, create_options);
	vars->oparms.fid = &fid;
	vars->oparms.reconnect = false;
	vars->oparms.mode = mode;
	vars->oparms.cअगरs_sb = cअगरs_sb;

	rqst[num_rqst].rq_iov = &vars->खोलो_iov[0];
	rqst[num_rqst].rq_nvec = SMB2_CREATE_IOV_SIZE;
	rc = SMB2_खोलो_init(tcon, server,
			    &rqst[num_rqst], &oplock, &vars->oparms,
			    utf16_path);
	kमुक्त(utf16_path);
	अगर (rc)
		जाओ finished;

	smb2_set_next_command(tcon, &rqst[num_rqst]);
 after_खोलो:
	num_rqst++;
	rc = 0;

	/* Operation */
	चयन (command) अणु
	हाल SMB2_OP_QUERY_INFO:
		rqst[num_rqst].rq_iov = &vars->qi_iov[0];
		rqst[num_rqst].rq_nvec = 1;

		अगर (cfile)
			rc = SMB2_query_info_init(tcon, server,
				&rqst[num_rqst],
				cfile->fid.persistent_fid,
				cfile->fid.अस्थिर_fid,
				खाता_ALL_INFORMATION,
				SMB2_O_INFO_खाता, 0,
				माप(काष्ठा smb2_file_all_info) +
					  PATH_MAX * 2, 0, शून्य);
		अन्यथा अणु
			rc = SMB2_query_info_init(tcon, server,
				&rqst[num_rqst],
				COMPOUND_FID,
				COMPOUND_FID,
				खाता_ALL_INFORMATION,
				SMB2_O_INFO_खाता, 0,
				माप(काष्ठा smb2_file_all_info) +
					  PATH_MAX * 2, 0, शून्य);
			अगर (!rc) अणु
				smb2_set_next_command(tcon, &rqst[num_rqst]);
				smb2_set_related(&rqst[num_rqst]);
			पूर्ण
		पूर्ण

		अगर (rc)
			जाओ finished;
		num_rqst++;
		trace_smb3_query_info_compound_enter(xid, ses->Suid, tcon->tid,
						     full_path);
		अवरोध;
	हाल SMB2_OP_POSIX_QUERY_INFO:
		rqst[num_rqst].rq_iov = &vars->qi_iov[0];
		rqst[num_rqst].rq_nvec = 1;

		अगर (cfile)
			rc = SMB2_query_info_init(tcon, server,
				&rqst[num_rqst],
				cfile->fid.persistent_fid,
				cfile->fid.अस्थिर_fid,
				SMB_FIND_खाता_POSIX_INFO,
				SMB2_O_INFO_खाता, 0,
				/* TBD: fix following to allow क्रम दीर्घer SIDs */
				माप(काष्ठा smb311_posix_qinfo *) + (PATH_MAX * 2) +
				(माप(काष्ठा cअगरs_sid) * 2), 0, शून्य);
		अन्यथा अणु
			rc = SMB2_query_info_init(tcon, server,
				&rqst[num_rqst],
				COMPOUND_FID,
				COMPOUND_FID,
				SMB_FIND_खाता_POSIX_INFO,
				SMB2_O_INFO_खाता, 0,
				माप(काष्ठा smb311_posix_qinfo *) + (PATH_MAX * 2) +
				(माप(काष्ठा cअगरs_sid) * 2), 0, शून्य);
			अगर (!rc) अणु
				smb2_set_next_command(tcon, &rqst[num_rqst]);
				smb2_set_related(&rqst[num_rqst]);
			पूर्ण
		पूर्ण

		अगर (rc)
			जाओ finished;
		num_rqst++;
		trace_smb3_posix_query_info_compound_enter(xid, ses->Suid, tcon->tid, full_path);
		अवरोध;
	हाल SMB2_OP_DELETE:
		trace_smb3_delete_enter(xid, ses->Suid, tcon->tid, full_path);
		अवरोध;
	हाल SMB2_OP_MKसूची:
		/*
		 * Directories are created through parameters in the
		 * SMB2_खोलो() call.
		 */
		trace_smb3_सूची_गढ़ो_enter(xid, ses->Suid, tcon->tid, full_path);
		अवरोध;
	हाल SMB2_OP_RMसूची:
		rqst[num_rqst].rq_iov = &vars->si_iov[0];
		rqst[num_rqst].rq_nvec = 1;

		size[0] = 1; /* माप __u8 See MS-FSCC section 2.4.11 */
		data[0] = &delete_pending[0];

		rc = SMB2_set_info_init(tcon, server,
					&rqst[num_rqst], COMPOUND_FID,
					COMPOUND_FID, current->tgid,
					खाता_DISPOSITION_INFORMATION,
					SMB2_O_INFO_खाता, 0, data, size);
		अगर (rc)
			जाओ finished;
		smb2_set_next_command(tcon, &rqst[num_rqst]);
		smb2_set_related(&rqst[num_rqst++]);
		trace_smb3_सूची_हटाओ_enter(xid, ses->Suid, tcon->tid, full_path);
		अवरोध;
	हाल SMB2_OP_SET_खातापूर्ण:
		rqst[num_rqst].rq_iov = &vars->si_iov[0];
		rqst[num_rqst].rq_nvec = 1;

		size[0] = 8; /* माप __le64 */
		data[0] = ptr;

		rc = SMB2_set_info_init(tcon, server,
					&rqst[num_rqst], COMPOUND_FID,
					COMPOUND_FID, current->tgid,
					खाता_END_OF_खाता_INFORMATION,
					SMB2_O_INFO_खाता, 0, data, size);
		अगर (rc)
			जाओ finished;
		smb2_set_next_command(tcon, &rqst[num_rqst]);
		smb2_set_related(&rqst[num_rqst++]);
		trace_smb3_set_eof_enter(xid, ses->Suid, tcon->tid, full_path);
		अवरोध;
	हाल SMB2_OP_SET_INFO:
		rqst[num_rqst].rq_iov = &vars->si_iov[0];
		rqst[num_rqst].rq_nvec = 1;


		size[0] = माप(खाता_BASIC_INFO);
		data[0] = ptr;

		अगर (cfile)
			rc = SMB2_set_info_init(tcon, server,
				&rqst[num_rqst],
				cfile->fid.persistent_fid,
				cfile->fid.अस्थिर_fid, current->tgid,
				खाता_BASIC_INFORMATION,
				SMB2_O_INFO_खाता, 0, data, size);
		अन्यथा अणु
			rc = SMB2_set_info_init(tcon, server,
				&rqst[num_rqst],
				COMPOUND_FID,
				COMPOUND_FID, current->tgid,
				खाता_BASIC_INFORMATION,
				SMB2_O_INFO_खाता, 0, data, size);
			अगर (!rc) अणु
				smb2_set_next_command(tcon, &rqst[num_rqst]);
				smb2_set_related(&rqst[num_rqst]);
			पूर्ण
		पूर्ण

		अगर (rc)
			जाओ finished;
		num_rqst++;
		trace_smb3_set_info_compound_enter(xid, ses->Suid, tcon->tid,
						   full_path);
		अवरोध;
	हाल SMB2_OP_RENAME:
		rqst[num_rqst].rq_iov = &vars->si_iov[0];
		rqst[num_rqst].rq_nvec = 2;

		len = (2 * UniStrnlen((ब_अक्षर_प्रकार *)ptr, PATH_MAX));

		vars->नाम_info.ReplaceIfExists = 1;
		vars->नाम_info.RootDirectory = 0;
		vars->नाम_info.FileNameLength = cpu_to_le32(len);

		size[0] = माप(काष्ठा smb2_file_नाम_info);
		data[0] = &vars->नाम_info;

		size[1] = len + 2 /* null */;
		data[1] = (__le16 *)ptr;

		अगर (cfile)
			rc = SMB2_set_info_init(tcon, server,
						&rqst[num_rqst],
						cfile->fid.persistent_fid,
						cfile->fid.अस्थिर_fid,
					current->tgid, खाता_RENAME_INFORMATION,
					SMB2_O_INFO_खाता, 0, data, size);
		अन्यथा अणु
			rc = SMB2_set_info_init(tcon, server,
					&rqst[num_rqst],
					COMPOUND_FID, COMPOUND_FID,
					current->tgid, खाता_RENAME_INFORMATION,
					SMB2_O_INFO_खाता, 0, data, size);
			अगर (!rc) अणु
				smb2_set_next_command(tcon, &rqst[num_rqst]);
				smb2_set_related(&rqst[num_rqst]);
			पूर्ण
		पूर्ण
		अगर (rc)
			जाओ finished;
		num_rqst++;
		trace_smb3_नाम_enter(xid, ses->Suid, tcon->tid, full_path);
		अवरोध;
	हाल SMB2_OP_HARDLINK:
		rqst[num_rqst].rq_iov = &vars->si_iov[0];
		rqst[num_rqst].rq_nvec = 2;

		len = (2 * UniStrnlen((ब_अक्षर_प्रकार *)ptr, PATH_MAX));

		vars->link_info.ReplaceIfExists = 0;
		vars->link_info.RootDirectory = 0;
		vars->link_info.FileNameLength = cpu_to_le32(len);

		size[0] = माप(काष्ठा smb2_file_link_info);
		data[0] = &vars->link_info;

		size[1] = len + 2 /* null */;
		data[1] = (__le16 *)ptr;

		rc = SMB2_set_info_init(tcon, server,
					&rqst[num_rqst], COMPOUND_FID,
					COMPOUND_FID, current->tgid,
					खाता_LINK_INFORMATION,
					SMB2_O_INFO_खाता, 0, data, size);
		अगर (rc)
			जाओ finished;
		smb2_set_next_command(tcon, &rqst[num_rqst]);
		smb2_set_related(&rqst[num_rqst++]);
		trace_smb3_hardlink_enter(xid, ses->Suid, tcon->tid, full_path);
		अवरोध;
	शेष:
		cअगरs_dbg(VFS, "Invalid command\n");
		rc = -EINVAL;
	पूर्ण
	अगर (rc)
		जाओ finished;

	/* We alपढ़ोy have a handle so we can skip the बंद */
	अगर (cfile)
		जाओ after_बंद;
	/* Close */
	flags |= CIFS_CP_CREATE_CLOSE_OP;
	rqst[num_rqst].rq_iov = &vars->बंद_iov[0];
	rqst[num_rqst].rq_nvec = 1;
	rc = SMB2_बंद_init(tcon, server,
			     &rqst[num_rqst], COMPOUND_FID,
			     COMPOUND_FID, false);
	smb2_set_related(&rqst[num_rqst]);
	अगर (rc)
		जाओ finished;
 after_बंद:
	num_rqst++;

	अगर (cfile) अणु
		cअगरsFileInfo_put(cfile);
		cfile = शून्य;
		rc = compound_send_recv(xid, ses, server,
					flags, num_rqst - 2,
					&rqst[1], &resp_buftype[1],
					&rsp_iov[1]);
	पूर्ण अन्यथा
		rc = compound_send_recv(xid, ses, server,
					flags, num_rqst,
					rqst, resp_buftype,
					rsp_iov);

 finished:
	अगर (cfile)
		cअगरsFileInfo_put(cfile);

	SMB2_खोलो_मुक्त(&rqst[0]);
	अगर (rc == -EREMCHG) अणु
		pr_warn_once("server share %s deleted\n", tcon->treeName);
		tcon->need_reconnect = true;
	पूर्ण

	चयन (command) अणु
	हाल SMB2_OP_QUERY_INFO:
		अगर (rc == 0) अणु
			qi_rsp = (काष्ठा smb2_query_info_rsp *)
				rsp_iov[1].iov_base;
			rc = smb2_validate_and_copy_iov(
				le16_to_cpu(qi_rsp->OutputBufferOffset),
				le32_to_cpu(qi_rsp->OutputBufferLength),
				&rsp_iov[1], माप(काष्ठा smb2_file_all_info),
				ptr);
		पूर्ण
		अगर (rqst[1].rq_iov)
			SMB2_query_info_मुक्त(&rqst[1]);
		अगर (rqst[2].rq_iov)
			SMB2_बंद_मुक्त(&rqst[2]);
		अगर (rc)
			trace_smb3_query_info_compound_err(xid,  ses->Suid,
						tcon->tid, rc);
		अन्यथा
			trace_smb3_query_info_compound_करोne(xid, ses->Suid,
						tcon->tid);
		अवरोध;
	हाल SMB2_OP_POSIX_QUERY_INFO:
		अगर (rc == 0) अणु
			qi_rsp = (काष्ठा smb2_query_info_rsp *)
				rsp_iov[1].iov_base;
			rc = smb2_validate_and_copy_iov(
				le16_to_cpu(qi_rsp->OutputBufferOffset),
				le32_to_cpu(qi_rsp->OutputBufferLength),
				&rsp_iov[1], माप(काष्ठा smb311_posix_qinfo) /* add SIDs */, ptr);
		पूर्ण
		अगर (rqst[1].rq_iov)
			SMB2_query_info_मुक्त(&rqst[1]);
		अगर (rqst[2].rq_iov)
			SMB2_बंद_मुक्त(&rqst[2]);
		अगर (rc)
			trace_smb3_posix_query_info_compound_err(xid,  ses->Suid, tcon->tid, rc);
		अन्यथा
			trace_smb3_posix_query_info_compound_करोne(xid, ses->Suid, tcon->tid);
		अवरोध;
	हाल SMB2_OP_DELETE:
		अगर (rc)
			trace_smb3_delete_err(xid,  ses->Suid, tcon->tid, rc);
		अन्यथा
			trace_smb3_delete_करोne(xid, ses->Suid, tcon->tid);
		अगर (rqst[1].rq_iov)
			SMB2_बंद_मुक्त(&rqst[1]);
		अवरोध;
	हाल SMB2_OP_MKसूची:
		अगर (rc)
			trace_smb3_सूची_गढ़ो_err(xid,  ses->Suid, tcon->tid, rc);
		अन्यथा
			trace_smb3_सूची_गढ़ो_करोne(xid, ses->Suid, tcon->tid);
		अगर (rqst[1].rq_iov)
			SMB2_बंद_मुक्त(&rqst[1]);
		अवरोध;
	हाल SMB2_OP_HARDLINK:
		अगर (rc)
			trace_smb3_hardlink_err(xid,  ses->Suid, tcon->tid, rc);
		अन्यथा
			trace_smb3_hardlink_करोne(xid, ses->Suid, tcon->tid);
		मुक्त_set_inf_compound(rqst);
		अवरोध;
	हाल SMB2_OP_RENAME:
		अगर (rc)
			trace_smb3_नाम_err(xid,  ses->Suid, tcon->tid, rc);
		अन्यथा
			trace_smb3_नाम_करोne(xid, ses->Suid, tcon->tid);
		मुक्त_set_inf_compound(rqst);
		अवरोध;
	हाल SMB2_OP_RMसूची:
		अगर (rc)
			trace_smb3_सूची_हटाओ_err(xid,  ses->Suid, tcon->tid, rc);
		अन्यथा
			trace_smb3_सूची_हटाओ_करोne(xid, ses->Suid, tcon->tid);
		मुक्त_set_inf_compound(rqst);
		अवरोध;
	हाल SMB2_OP_SET_खातापूर्ण:
		अगर (rc)
			trace_smb3_set_eof_err(xid,  ses->Suid, tcon->tid, rc);
		अन्यथा
			trace_smb3_set_eof_करोne(xid, ses->Suid, tcon->tid);
		मुक्त_set_inf_compound(rqst);
		अवरोध;
	हाल SMB2_OP_SET_INFO:
		अगर (rc)
			trace_smb3_set_info_compound_err(xid,  ses->Suid,
						tcon->tid, rc);
		अन्यथा
			trace_smb3_set_info_compound_करोne(xid, ses->Suid,
						tcon->tid);
		मुक्त_set_inf_compound(rqst);
		अवरोध;
	पूर्ण
	मुक्त_rsp_buf(resp_buftype[0], rsp_iov[0].iov_base);
	मुक्त_rsp_buf(resp_buftype[1], rsp_iov[1].iov_base);
	मुक्त_rsp_buf(resp_buftype[2], rsp_iov[2].iov_base);
	kमुक्त(vars);
	वापस rc;
पूर्ण

व्योम
move_smb2_info_to_cअगरs(खाता_ALL_INFO *dst, काष्ठा smb2_file_all_info *src)
अणु
	स_नकल(dst, src, (माप_प्रकार)(&src->CurrentByteOffset) - (माप_प्रकार)src);
	dst->CurrentByteOffset = src->CurrentByteOffset;
	dst->Mode = src->Mode;
	dst->AlignmentRequirement = src->AlignmentRequirement;
	dst->IndexNumber1 = 0; /* we करोn't use it */
पूर्ण

पूर्णांक
smb2_query_path_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *full_path,
		     खाता_ALL_INFO *data, bool *adjust_tz, bool *reparse)
अणु
	पूर्णांक rc;
	काष्ठा smb2_file_all_info *smb2_data;
	__u32 create_options = 0;
	काष्ठा cअगरsFileInfo *cfile;
	काष्ठा cached_fid *cfid = शून्य;

	*adjust_tz = false;
	*reparse = false;

	smb2_data = kzalloc(माप(काष्ठा smb2_file_all_info) + PATH_MAX * 2,
			    GFP_KERNEL);
	अगर (smb2_data == शून्य)
		वापस -ENOMEM;

	/* If it is a root and its handle is cached then use it */
	rc = खोलो_cached_dir(xid, tcon, full_path, cअगरs_sb, &cfid);
	अगर (!rc) अणु
		अगर (tcon->crfid.file_all_info_is_valid) अणु
			move_smb2_info_to_cअगरs(data,
					       &tcon->crfid.file_all_info);
		पूर्ण अन्यथा अणु
			rc = SMB2_query_info(xid, tcon,
					     cfid->fid->persistent_fid,
					     cfid->fid->अस्थिर_fid, smb2_data);
			अगर (!rc)
				move_smb2_info_to_cअगरs(data, smb2_data);
		पूर्ण
		बंद_cached_dir(cfid);
		जाओ out;
	पूर्ण

	cअगरs_get_पढ़ोable_path(tcon, full_path, &cfile);
	rc = smb2_compound_op(xid, tcon, cअगरs_sb, full_path,
			      खाता_READ_ATTRIBUTES, खाता_OPEN, create_options,
			      ACL_NO_MODE, smb2_data, SMB2_OP_QUERY_INFO, cfile);
	अगर (rc == -EOPNOTSUPP) अणु
		*reparse = true;
		create_options |= OPEN_REPARSE_POINT;

		/* Failed on a symbolic link - query a reparse poपूर्णांक info */
		rc = smb2_compound_op(xid, tcon, cअगरs_sb, full_path,
				      खाता_READ_ATTRIBUTES, खाता_OPEN,
				      create_options, ACL_NO_MODE,
				      smb2_data, SMB2_OP_QUERY_INFO, शून्य);
	पूर्ण
	अगर (rc)
		जाओ out;

	move_smb2_info_to_cअगरs(data, smb2_data);
out:
	kमुक्त(smb2_data);
	वापस rc;
पूर्ण


पूर्णांक
smb311_posix_query_path_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *full_path,
		     काष्ठा smb311_posix_qinfo *data, bool *adjust_tz, bool *reparse)
अणु
	पूर्णांक rc;
	__u32 create_options = 0;
	काष्ठा cअगरsFileInfo *cfile;
	काष्ठा smb311_posix_qinfo *smb2_data;

	*adjust_tz = false;
	*reparse = false;

	/* BB TODO: Make काष्ठा larger when add support क्रम parsing owner SIDs */
	smb2_data = kzalloc(माप(काष्ठा smb311_posix_qinfo),
			    GFP_KERNEL);
	अगर (smb2_data == शून्य)
		वापस -ENOMEM;

	/*
	 * BB TODO: Add support क्रम using the cached root handle.
	 * Create SMB2_query_posix_info worker function to करो non-compounded query
	 * when we alपढ़ोy have an खोलो file handle क्रम this. For now this is fast enough
	 * (always using the compounded version).
	 */

	cअगरs_get_पढ़ोable_path(tcon, full_path, &cfile);
	rc = smb2_compound_op(xid, tcon, cअगरs_sb, full_path,
			      खाता_READ_ATTRIBUTES, खाता_OPEN, create_options,
			      ACL_NO_MODE, smb2_data, SMB2_OP_POSIX_QUERY_INFO, cfile);
	अगर (rc == -EOPNOTSUPP) अणु
		/* BB TODO: When support क्रम special files added to Samba re-verअगरy this path */
		*reparse = true;
		create_options |= OPEN_REPARSE_POINT;

		/* Failed on a symbolic link - query a reparse poपूर्णांक info */
		rc = smb2_compound_op(xid, tcon, cअगरs_sb, full_path,
				      खाता_READ_ATTRIBUTES, खाता_OPEN,
				      create_options, ACL_NO_MODE,
				      smb2_data, SMB2_OP_POSIX_QUERY_INFO, शून्य);
	पूर्ण
	अगर (rc)
		जाओ out;

	 /* TODO: will need to allow क्रम the 2 SIDs when add support क्रम getting owner UID/GID */
	स_नकल(data, smb2_data, माप(काष्ठा smb311_posix_qinfo));

out:
	kमुक्त(smb2_data);
	वापस rc;
पूर्ण

पूर्णांक
smb2_सूची_गढ़ो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा inode *parent_inode, umode_t mode,
	   काष्ठा cअगरs_tcon *tcon, स्थिर अक्षर *name,
	   काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	वापस smb2_compound_op(xid, tcon, cअगरs_sb, name,
				खाता_WRITE_ATTRIBUTES, खाता_CREATE,
				CREATE_NOT_खाता, mode, शून्य, SMB2_OP_MKसूची,
				शून्य);
पूर्ण

व्योम
smb2_सूची_गढ़ो_setinfo(काष्ठा inode *inode, स्थिर अक्षर *name,
		   काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा cअगरs_tcon *tcon,
		   स्थिर अचिन्हित पूर्णांक xid)
अणु
	खाता_BASIC_INFO data;
	काष्ठा cअगरsInodeInfo *cअगरs_i;
	काष्ठा cअगरsFileInfo *cfile;
	u32 करोsattrs;
	पूर्णांक पंचांगprc;

	स_रखो(&data, 0, माप(data));
	cअगरs_i = CIFS_I(inode);
	करोsattrs = cअगरs_i->cअगरsAttrs | ATTR_READONLY;
	data.Attributes = cpu_to_le32(करोsattrs);
	cअगरs_get_writable_path(tcon, name, FIND_WR_ANY, &cfile);
	पंचांगprc = smb2_compound_op(xid, tcon, cअगरs_sb, name,
				 खाता_WRITE_ATTRIBUTES, खाता_CREATE,
				 CREATE_NOT_खाता, ACL_NO_MODE,
				 &data, SMB2_OP_SET_INFO, cfile);
	अगर (पंचांगprc == 0)
		cअगरs_i->cअगरsAttrs = करोsattrs;
पूर्ण

पूर्णांक
smb2_सूची_हटाओ(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, स्थिर अक्षर *name,
	   काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	वापस smb2_compound_op(xid, tcon, cअगरs_sb, name, DELETE, खाता_OPEN,
				CREATE_NOT_खाता, ACL_NO_MODE,
				शून्य, SMB2_OP_RMसूची, शून्य);
पूर्ण

पूर्णांक
smb2_unlink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, स्थिर अक्षर *name,
	    काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	वापस smb2_compound_op(xid, tcon, cअगरs_sb, name, DELETE, खाता_OPEN,
				CREATE_DELETE_ON_CLOSE | OPEN_REPARSE_POINT,
				ACL_NO_MODE, शून्य, SMB2_OP_DELETE, शून्य);
पूर्ण

अटल पूर्णांक
smb2_set_path_attr(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   स्थिर अक्षर *from_name, स्थिर अक्षर *to_name,
		   काष्ठा cअगरs_sb_info *cअगरs_sb, __u32 access, पूर्णांक command,
		   काष्ठा cअगरsFileInfo *cfile)
अणु
	__le16 *smb2_to_name = शून्य;
	पूर्णांक rc;

	smb2_to_name = cअगरs_convert_path_to_utf16(to_name, cअगरs_sb);
	अगर (smb2_to_name == शून्य) अणु
		rc = -ENOMEM;
		जाओ smb2_नाम_path;
	पूर्ण
	rc = smb2_compound_op(xid, tcon, cअगरs_sb, from_name, access,
			      खाता_OPEN, 0, ACL_NO_MODE, smb2_to_name,
			      command, cfile);
smb2_नाम_path:
	kमुक्त(smb2_to_name);
	वापस rc;
पूर्ण

पूर्णांक
smb2_नाम_path(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		 स्थिर अक्षर *from_name, स्थिर अक्षर *to_name,
		 काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	काष्ठा cअगरsFileInfo *cfile;

	cअगरs_get_writable_path(tcon, from_name, FIND_WR_WITH_DELETE, &cfile);

	वापस smb2_set_path_attr(xid, tcon, from_name, to_name,
				  cअगरs_sb, DELETE, SMB2_OP_RENAME, cfile);
पूर्ण

पूर्णांक
smb2_create_hardlink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     स्थिर अक्षर *from_name, स्थिर अक्षर *to_name,
		     काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	वापस smb2_set_path_attr(xid, tcon, from_name, to_name, cअगरs_sb,
				  खाता_READ_ATTRIBUTES, SMB2_OP_HARDLINK,
				  शून्य);
पूर्ण

पूर्णांक
smb2_set_path_size(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		   स्थिर अक्षर *full_path, __u64 size,
		   काष्ठा cअगरs_sb_info *cअगरs_sb, bool set_alloc)
अणु
	__le64 eof = cpu_to_le64(size);

	वापस smb2_compound_op(xid, tcon, cअगरs_sb, full_path,
				खाता_WRITE_DATA, खाता_OPEN, 0, ACL_NO_MODE,
				&eof, SMB2_OP_SET_खातापूर्ण, शून्य);
पूर्ण

पूर्णांक
smb2_set_file_info(काष्ठा inode *inode, स्थिर अक्षर *full_path,
		   खाता_BASIC_INFO *buf, स्थिर अचिन्हित पूर्णांक xid)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा tcon_link *tlink;
	पूर्णांक rc;

	अगर ((buf->CreationTime == 0) && (buf->LastAccessTime == 0) &&
	    (buf->LastWriteTime == 0) && (buf->ChangeTime == 0) &&
	    (buf->Attributes == 0))
		वापस 0; /* would be a no op, no sense sending this */

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);

	rc = smb2_compound_op(xid, tlink_tcon(tlink), cअगरs_sb, full_path,
			      खाता_WRITE_ATTRIBUTES, खाता_OPEN,
			      0, ACL_NO_MODE, buf, SMB2_OP_SET_INFO, शून्य);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण
