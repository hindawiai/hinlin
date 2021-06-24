<शैली गुरु>
/*
 *   fs/cअगरs/ioctl.c
 *
 *   vfs operations that deal with io control
 *
 *   Copyright (C) International Business Machines  Corp., 2005,2013
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
#समावेश <linux/file.h>
#समावेश <linux/mount.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "cifsfs.h"
#समावेश "cifs_ioctl.h"
#समावेश "smb2proto.h"
#समावेश "smb2glob.h"
#समावेश <linux/btrfs.h>

अटल दीर्घ cअगरs_ioctl_query_info(अचिन्हित पूर्णांक xid, काष्ठा file *filep,
				  अचिन्हित दीर्घ p)
अणु
	काष्ठा inode *inode = file_inode(filep);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	काष्ठा dentry *dentry = filep->f_path.dentry;
	स्थिर अचिन्हित अक्षर *path;
	व्योम *page = alloc_dentry_path();
	__le16 *utf16_path = शून्य, root_path;
	पूर्णांक rc = 0;

	path = build_path_from_dentry(dentry, page);
	अगर (IS_ERR(path)) अणु
		मुक्त_dentry_path(page);
		वापस PTR_ERR(path);
	पूर्ण

	cअगरs_dbg(FYI, "%s %s\n", __func__, path);

	अगर (!path[0]) अणु
		root_path = 0;
		utf16_path = &root_path;
	पूर्ण अन्यथा अणु
		utf16_path = cअगरs_convert_path_to_utf16(path + 1, cअगरs_sb);
		अगर (!utf16_path) अणु
			rc = -ENOMEM;
			जाओ ici_निकास;
		पूर्ण
	पूर्ण

	अगर (tcon->ses->server->ops->ioctl_query_info)
		rc = tcon->ses->server->ops->ioctl_query_info(
				xid, tcon, cअगरs_sb, utf16_path,
				filep->निजी_data ? 0 : 1, p);
	अन्यथा
		rc = -EOPNOTSUPP;

 ici_निकास:
	अगर (utf16_path != &root_path)
		kमुक्त(utf16_path);
	मुक्त_dentry_path(page);
	वापस rc;
पूर्ण

अटल दीर्घ cअगरs_ioctl_copychunk(अचिन्हित पूर्णांक xid, काष्ठा file *dst_file,
			अचिन्हित दीर्घ srcfd)
अणु
	पूर्णांक rc;
	काष्ठा fd src_file;
	काष्ठा inode *src_inode;

	cअगरs_dbg(FYI, "ioctl copychunk range\n");
	/* the destination must be खोलोed क्रम writing */
	अगर (!(dst_file->f_mode & FMODE_WRITE)) अणु
		cअगरs_dbg(FYI, "file target not open for write\n");
		वापस -EINVAL;
	पूर्ण

	/* check अगर target volume is पढ़ोonly and take reference */
	rc = mnt_want_ग_लिखो_file(dst_file);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "mnt_want_write failed with rc %d\n", rc);
		वापस rc;
	पूर्ण

	src_file = fdget(srcfd);
	अगर (!src_file.file) अणु
		rc = -EBADF;
		जाओ out_drop_ग_लिखो;
	पूर्ण

	अगर (src_file.file->f_op->unlocked_ioctl != cअगरs_ioctl) अणु
		rc = -EBADF;
		cअगरs_dbg(VFS, "src file seems to be from a different filesystem type\n");
		जाओ out_fput;
	पूर्ण

	src_inode = file_inode(src_file.file);
	rc = -EINVAL;
	अगर (S_ISसूची(src_inode->i_mode))
		जाओ out_fput;

	rc = cअगरs_file_copychunk_range(xid, src_file.file, 0, dst_file, 0,
					src_inode->i_size, 0);
	अगर (rc > 0)
		rc = 0;
out_fput:
	fdput(src_file);
out_drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(dst_file);
	वापस rc;
पूर्ण

अटल दीर्घ smb_mnt_get_fsinfo(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
				व्योम __user *arg)
अणु
	पूर्णांक rc = 0;
	काष्ठा smb_mnt_fs_info *fsinf;

	fsinf = kzalloc(माप(काष्ठा smb_mnt_fs_info), GFP_KERNEL);
	अगर (fsinf == शून्य)
		वापस -ENOMEM;

	fsinf->version = 1;
	fsinf->protocol_id = tcon->ses->server->vals->protocol_id;
	fsinf->device_अक्षरacteristics =
			le32_to_cpu(tcon->fsDevInfo.DeviceCharacteristics);
	fsinf->device_type = le32_to_cpu(tcon->fsDevInfo.DeviceType);
	fsinf->fs_attributes = le32_to_cpu(tcon->fsAttrInfo.Attributes);
	fsinf->max_path_component =
		le32_to_cpu(tcon->fsAttrInfo.MaxPathNameComponentLength);
	fsinf->vol_serial_number = tcon->vol_serial_number;
	fsinf->vol_create_समय = le64_to_cpu(tcon->vol_create_समय);
	fsinf->share_flags = tcon->share_flags;
	fsinf->share_caps = le32_to_cpu(tcon->capabilities);
	fsinf->sector_flags = tcon->ss_flags;
	fsinf->optimal_sector_size = tcon->perf_sector_size;
	fsinf->max_bytes_chunk = tcon->max_bytes_chunk;
	fsinf->maximal_access = tcon->maximal_access;
	fsinf->cअगरs_posix_caps = le64_to_cpu(tcon->fsUnixInfo.Capability);

	अगर (copy_to_user(arg, fsinf, माप(काष्ठा smb_mnt_fs_info)))
		rc = -EFAULT;

	kमुक्त(fsinf);
	वापस rc;
पूर्ण

अटल पूर्णांक cअगरs_shutकरोwn(काष्ठा super_block *sb, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cअगरs_sb_info *sbi = CIFS_SB(sb);
	__u32 flags;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (get_user(flags, (__u32 __user *)arg))
		वापस -EFAULT;

	अगर (flags > CIFS_GOING_FLAGS_NOLOGFLUSH)
		वापस -EINVAL;

	अगर (cअगरs_क्रमced_shutकरोwn(sbi))
		वापस 0;

	cअगरs_dbg(VFS, "shut down requested (%d)", flags);
/*	trace_cअगरs_shutकरोwn(sb, flags);*/

	/*
	 * see:
	 *   https://man7.org/linux/man-pages/man2/ioctl_xfs_goingकरोwn.2.hपंचांगl
	 * क्रम more inक्रमmation and description of original पूर्णांकent of the flags
	 */
	चयन (flags) अणु
	/*
	 * We could add support later क्रम शेष flag which requires:
	 *     "Flush all dirty data and metadata to disk"
	 * would need to call syncfs or equivalent to flush page cache क्रम
	 * the mount and then issue fsync to server (अगर nostrictsync not set)
	 */
	हाल CIFS_GOING_FLAGS_DEFAULT:
		cअगरs_dbg(FYI, "shutdown with default flag not supported\n");
		वापस -EINVAL;
	/*
	 * FLAGS_LOGFLUSH is easy since it asks to ग_लिखो out metadata (not
	 * data) but metadata ग_लिखोs are not cached on the client, so can treat
	 * it similarly to NOLOGFLUSH
	 */
	हाल CIFS_GOING_FLAGS_LOGFLUSH:
	हाल CIFS_GOING_FLAGS_NOLOGFLUSH:
		sbi->mnt_cअगरs_flags |= CIFS_MOUNT_SHUTDOWN;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cअगरs_dump_full_key(काष्ठा cअगरs_tcon *tcon, काष्ठा smb3_full_key_debug_info __user *in)
अणु
	काष्ठा smb3_full_key_debug_info out;
	काष्ठा cअगरs_ses *ses;
	पूर्णांक rc = 0;
	bool found = false;
	u8 __user *end;

	अगर (!smb3_encryption_required(tcon)) अणु
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/* copy user input पूर्णांकo our output buffer */
	अगर (copy_from_user(&out, in, माप(out))) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!out.session_id) अणु
		/* अगर ses id is 0, use current user session */
		ses = tcon->ses;
	पूर्ण अन्यथा अणु
		/* otherwise अगर a session id is given, look क्रम it in all our sessions */
		काष्ठा cअगरs_ses *ses_it = शून्य;
		काष्ठा TCP_Server_Info *server_it = शून्य;

		spin_lock(&cअगरs_tcp_ses_lock);
		list_क्रम_each_entry(server_it, &cअगरs_tcp_ses_list, tcp_ses_list) अणु
			list_क्रम_each_entry(ses_it, &server_it->smb_ses_list, smb_ses_list) अणु
				अगर (ses_it->Suid == out.session_id) अणु
					ses = ses_it;
					/*
					 * since we are using the session outside the crit
					 * section, we need to make sure it won't be released
					 * so increment its refcount
					 */
					ses->ses_count++;
					found = true;
					जाओ search_end;
				पूर्ण
			पूर्ण
		पूर्ण
search_end:
		spin_unlock(&cअगरs_tcp_ses_lock);
		अगर (!found) अणु
			rc = -ENOENT;
			जाओ out;
		पूर्ण
	पूर्ण

	चयन (ses->server->cipher_type) अणु
	हाल SMB2_ENCRYPTION_AES128_CCM:
	हाल SMB2_ENCRYPTION_AES128_GCM:
		out.session_key_length = CIFS_SESS_KEY_SIZE;
		out.server_in_key_length = out.server_out_key_length = SMB3_GCM128_CRYPTKEY_SIZE;
		अवरोध;
	हाल SMB2_ENCRYPTION_AES256_CCM:
	हाल SMB2_ENCRYPTION_AES256_GCM:
		out.session_key_length = CIFS_SESS_KEY_SIZE;
		out.server_in_key_length = out.server_out_key_length = SMB3_GCM256_CRYPTKEY_SIZE;
		अवरोध;
	शेष:
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/* check अगर user buffer is big enough to store all the keys */
	अगर (out.in_size < माप(out) + out.session_key_length + out.server_in_key_length
	    + out.server_out_key_length) अणु
		rc = -ENOBUFS;
		जाओ out;
	पूर्ण

	out.session_id = ses->Suid;
	out.cipher_type = le16_to_cpu(ses->server->cipher_type);

	/* overग_लिखो user input with our output */
	अगर (copy_to_user(in, &out, माप(out))) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* append all the keys at the end of the user buffer */
	end = in->data;
	अगर (copy_to_user(end, ses->auth_key.response, out.session_key_length)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	end += out.session_key_length;

	अगर (copy_to_user(end, ses->smb3encryptionkey, out.server_in_key_length)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	end += out.server_in_key_length;

	अगर (copy_to_user(end, ses->smb3decryptionkey, out.server_out_key_length)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

out:
	अगर (found)
		cअगरs_put_smb_ses(ses);
	वापस rc;
पूर्ण

दीर्घ cअगरs_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक command, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filep);
	काष्ठा smb3_key_debug_info pkey_inf;
	पूर्णांक rc = -ENOTTY; /* strange error - but the precedent */
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरsFileInfo *pSMBFile = filep->निजी_data;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	__u64	ExtAttrBits = 0;
	__u64   caps;

	xid = get_xid();

	cअगरs_dbg(FYI, "cifs ioctl 0x%x\n", command);
	चयन (command) अणु
		हाल FS_IOC_GETFLAGS:
			अगर (pSMBFile == शून्य)
				अवरोध;
			tcon = tlink_tcon(pSMBFile->tlink);
			caps = le64_to_cpu(tcon->fsUnixInfo.Capability);
#अगर_घोषित CONFIG_CIFS_POSIX
			अगर (CIFS_UNIX_EXTATTR_CAP & caps) अणु
				__u64	ExtAttrMask = 0;
				rc = CIFSGetExtAttr(xid, tcon,
						    pSMBFile->fid.netfid,
						    &ExtAttrBits, &ExtAttrMask);
				अगर (rc == 0)
					rc = put_user(ExtAttrBits &
						FS_FL_USER_VISIBLE,
						(पूर्णांक __user *)arg);
				अगर (rc != EOPNOTSUPP)
					अवरोध;
			पूर्ण
#पूर्ण_अगर /* CONFIG_CIFS_POSIX */
			rc = 0;
			अगर (CIFS_I(inode)->cअगरsAttrs & ATTR_COMPRESSED) अणु
				/* add in the compressed bit */
				ExtAttrBits = FS_COMPR_FL;
				rc = put_user(ExtAttrBits & FS_FL_USER_VISIBLE,
					      (पूर्णांक __user *)arg);
			पूर्ण
			अवरोध;
		हाल FS_IOC_SETFLAGS:
			अगर (pSMBFile == शून्य)
				अवरोध;
			tcon = tlink_tcon(pSMBFile->tlink);
			caps = le64_to_cpu(tcon->fsUnixInfo.Capability);

			अगर (get_user(ExtAttrBits, (पूर्णांक __user *)arg)) अणु
				rc = -EFAULT;
				अवरोध;
			पूर्ण

			/*
			 * अगर (CIFS_UNIX_EXTATTR_CAP & caps)
			 *	rc = CIFSSetExtAttr(xid, tcon,
			 *		       pSMBFile->fid.netfid,
			 *		       extAttrBits,
			 *		       &ExtAttrMask);
			 * अगर (rc != EOPNOTSUPP)
			 *	अवरोध;
			 */

			/* Currently only flag we can set is compressed flag */
			अगर ((ExtAttrBits & FS_COMPR_FL) == 0)
				अवरोध;

			/* Try to set compress flag */
			अगर (tcon->ses->server->ops->set_compression) अणु
				rc = tcon->ses->server->ops->set_compression(
							xid, tcon, pSMBFile);
				cअगरs_dbg(FYI, "set compress flag rc %d\n", rc);
			पूर्ण
			अवरोध;
		हाल CIFS_IOC_COPYCHUNK_खाता:
			rc = cअगरs_ioctl_copychunk(xid, filep, arg);
			अवरोध;
		हाल CIFS_QUERY_INFO:
			rc = cअगरs_ioctl_query_info(xid, filep, arg);
			अवरोध;
		हाल CIFS_IOC_SET_INTEGRITY:
			अगर (pSMBFile == शून्य)
				अवरोध;
			tcon = tlink_tcon(pSMBFile->tlink);
			अगर (tcon->ses->server->ops->set_पूर्णांकegrity)
				rc = tcon->ses->server->ops->set_पूर्णांकegrity(xid,
						tcon, pSMBFile);
			अन्यथा
				rc = -EOPNOTSUPP;
			अवरोध;
		हाल CIFS_IOC_GET_MNT_INFO:
			अगर (pSMBFile == शून्य)
				अवरोध;
			tcon = tlink_tcon(pSMBFile->tlink);
			rc = smb_mnt_get_fsinfo(xid, tcon, (व्योम __user *)arg);
			अवरोध;
		हाल CIFS_ENUMERATE_SNAPSHOTS:
			अगर (pSMBFile == शून्य)
				अवरोध;
			अगर (arg == 0) अणु
				rc = -EINVAL;
				जाओ cअगरs_ioc_निकास;
			पूर्ण
			tcon = tlink_tcon(pSMBFile->tlink);
			अगर (tcon->ses->server->ops->क्रमागत_snapshots)
				rc = tcon->ses->server->ops->क्रमागत_snapshots(xid, tcon,
						pSMBFile, (व्योम __user *)arg);
			अन्यथा
				rc = -EOPNOTSUPP;
			अवरोध;
		हाल CIFS_DUMP_KEY:
			/*
			 * Dump encryption keys. This is an old ioctl that only
			 * handles AES-128-अणुCCM,GCMपूर्ण.
			 */
			अगर (pSMBFile == शून्य)
				अवरोध;
			अगर (!capable(CAP_SYS_ADMIN)) अणु
				rc = -EACCES;
				अवरोध;
			पूर्ण

			tcon = tlink_tcon(pSMBFile->tlink);
			अगर (!smb3_encryption_required(tcon)) अणु
				rc = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			pkey_inf.cipher_type =
				le16_to_cpu(tcon->ses->server->cipher_type);
			pkey_inf.Suid = tcon->ses->Suid;
			स_नकल(pkey_inf.auth_key, tcon->ses->auth_key.response,
					16 /* SMB2_NTLMV2_SESSKEY_SIZE */);
			स_नकल(pkey_inf.smb3decryptionkey,
			      tcon->ses->smb3decryptionkey, SMB3_SIGN_KEY_SIZE);
			स_नकल(pkey_inf.smb3encryptionkey,
			      tcon->ses->smb3encryptionkey, SMB3_SIGN_KEY_SIZE);
			अगर (copy_to_user((व्योम __user *)arg, &pkey_inf,
					माप(काष्ठा smb3_key_debug_info)))
				rc = -EFAULT;
			अन्यथा
				rc = 0;
			अवरोध;
		हाल CIFS_DUMP_FULL_KEY:
			/*
			 * Dump encryption keys (handles any key sizes)
			 */
			अगर (pSMBFile == शून्य)
				अवरोध;
			अगर (!capable(CAP_SYS_ADMIN)) अणु
				rc = -EACCES;
				अवरोध;
			पूर्ण
			tcon = tlink_tcon(pSMBFile->tlink);
			rc = cअगरs_dump_full_key(tcon, (व्योम __user *)arg);
			अवरोध;
		हाल CIFS_IOC_NOTIFY:
			अगर (!S_ISसूची(inode->i_mode)) अणु
				/* Notअगरy can only be करोne on directories */
				rc = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			cअगरs_sb = CIFS_SB(inode->i_sb);
			tlink = cअगरs_sb_tlink(cअगरs_sb);
			अगर (IS_ERR(tlink)) अणु
				rc = PTR_ERR(tlink);
				अवरोध;
			पूर्ण
			tcon = tlink_tcon(tlink);
			अगर (tcon && tcon->ses->server->ops->notअगरy) अणु
				rc = tcon->ses->server->ops->notअगरy(xid,
						filep, (व्योम __user *)arg);
				cअगरs_dbg(FYI, "ioctl notify rc %d\n", rc);
			पूर्ण अन्यथा
				rc = -EOPNOTSUPP;
			cअगरs_put_tlink(tlink);
			अवरोध;
		हाल CIFS_IOC_SHUTDOWN:
			rc = cअगरs_shutकरोwn(inode->i_sb, arg);
			अवरोध;
		शेष:
			cअगरs_dbg(FYI, "unsupported ioctl\n");
			अवरोध;
	पूर्ण
cअगरs_ioc_निकास:
	मुक्त_xid(xid);
	वापस rc;
पूर्ण
