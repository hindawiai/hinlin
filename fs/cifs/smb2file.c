<शैली गुरु>
/*
 *   fs/cअगरs/smb2file.c
 *
 *   Copyright (C) International Business Machines  Corp., 2002, 2011
 *   Author(s): Steve French (sfrench@us.ibm.com),
 *              Pavel Shilovsky ((pshilovsky@samba.org) 2012
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
#समावेश "smb2proto.h"

पूर्णांक
smb2_खोलो_file(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_खोलो_parms *oparms,
	       __u32 *oplock, खाता_ALL_INFO *buf)
अणु
	पूर्णांक rc;
	__le16 *smb2_path;
	काष्ठा smb2_file_all_info *smb2_data = शून्य;
	__u8 smb2_oplock;
	काष्ठा cअगरs_fid *fid = oparms->fid;
	काष्ठा network_resiliency_req nr_ioctl_req;

	smb2_path = cअगरs_convert_path_to_utf16(oparms->path, oparms->cअगरs_sb);
	अगर (smb2_path == शून्य) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	smb2_data = kzalloc(माप(काष्ठा smb2_file_all_info) + PATH_MAX * 2,
			    GFP_KERNEL);
	अगर (smb2_data == शून्य) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	oparms->desired_access |= खाता_READ_ATTRIBUTES;
	smb2_oplock = SMB2_OPLOCK_LEVEL_BATCH;

	rc = SMB2_खोलो(xid, oparms, smb2_path, &smb2_oplock, smb2_data, शून्य,
		       शून्य, शून्य);
	अगर (rc)
		जाओ out;


	अगर (oparms->tcon->use_resilient) अणु
		/* शेष समयout is 0, servers pick शेष (120 seconds) */
		nr_ioctl_req.Timeout =
			cpu_to_le32(oparms->tcon->handle_समयout);
		nr_ioctl_req.Reserved = 0;
		rc = SMB2_ioctl(xid, oparms->tcon, fid->persistent_fid,
			fid->अस्थिर_fid, FSCTL_LMR_REQUEST_RESILIENCY,
			true /* is_fsctl */,
			(अक्षर *)&nr_ioctl_req, माप(nr_ioctl_req),
			CIFSMaxBufSize, शून्य, शून्य /* no वापस info */);
		अगर (rc == -EOPNOTSUPP) अणु
			cअगरs_dbg(VFS,
			     "resiliency not supported by server, disabling\n");
			oparms->tcon->use_resilient = false;
		पूर्ण अन्यथा अगर (rc)
			cअगरs_dbg(FYI, "error %d setting resiliency\n", rc);

		rc = 0;
	पूर्ण

	अगर (buf) अणु
		/* अगर खोलो response करोes not have IndexNumber field - get it */
		अगर (smb2_data->IndexNumber == 0) अणु
			rc = SMB2_get_srv_num(xid, oparms->tcon,
				      fid->persistent_fid,
				      fid->अस्थिर_fid,
				      &smb2_data->IndexNumber);
			अगर (rc) अणु
				/*
				 * let get_inode_info disable server inode
				 * numbers
				 */
				smb2_data->IndexNumber = 0;
				rc = 0;
			पूर्ण
		पूर्ण
		move_smb2_info_to_cअगरs(buf, smb2_data);
	पूर्ण

	*oplock = smb2_oplock;
out:
	kमुक्त(smb2_data);
	kमुक्त(smb2_path);
	वापस rc;
पूर्ण

पूर्णांक
smb2_unlock_range(काष्ठा cअगरsFileInfo *cfile, काष्ठा file_lock *flock,
		  स्थिर अचिन्हित पूर्णांक xid)
अणु
	पूर्णांक rc = 0, stored_rc;
	अचिन्हित पूर्णांक max_num, num = 0, max_buf;
	काष्ठा smb2_lock_element *buf, *cur;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cfile->tlink);
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	काष्ठा cअगरsLockInfo *li, *पंचांगp;
	__u64 length = 1 + flock->fl_end - flock->fl_start;
	काष्ठा list_head पंचांगp_llist;

	INIT_LIST_HEAD(&पंचांगp_llist);

	/*
	 * Accessing maxBuf is racy with cअगरs_reconnect - need to store value
	 * and check it beक्रमe using.
	 */
	max_buf = tcon->ses->server->maxBuf;
	अगर (max_buf < माप(काष्ठा smb2_lock_element))
		वापस -EINVAL;

	BUILD_BUG_ON(माप(काष्ठा smb2_lock_element) > PAGE_SIZE);
	max_buf = min_t(अचिन्हित पूर्णांक, max_buf, PAGE_SIZE);
	max_num = max_buf / माप(काष्ठा smb2_lock_element);
	buf = kसुस्मृति(max_num, माप(काष्ठा smb2_lock_element), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	cur = buf;

	cअगरs_करोwn_ग_लिखो(&cinode->lock_sem);
	list_क्रम_each_entry_safe(li, पंचांगp, &cfile->llist->locks, llist) अणु
		अगर (flock->fl_start > li->offset ||
		    (flock->fl_start + length) <
		    (li->offset + li->length))
			जारी;
		अगर (current->tgid != li->pid)
			/*
			 * flock and OFD lock are associated with an खोलो
			 * file description, not the process.
			 */
			अगर (!(flock->fl_flags & (FL_FLOCK | FL_OFDLCK)))
				जारी;
		अगर (cinode->can_cache_brlcks) अणु
			/*
			 * We can cache brlock requests - simply हटाओ a lock
			 * from the file's list.
			 */
			list_del(&li->llist);
			cअगरs_del_lock_रुकोers(li);
			kमुक्त(li);
			जारी;
		पूर्ण
		cur->Length = cpu_to_le64(li->length);
		cur->Offset = cpu_to_le64(li->offset);
		cur->Flags = cpu_to_le32(SMB2_LOCKFLAG_UNLOCK);
		/*
		 * We need to save a lock here to let us add it again to the
		 * file's list अगर the unlock range request fails on the server.
		 */
		list_move(&li->llist, &पंचांगp_llist);
		अगर (++num == max_num) अणु
			stored_rc = smb2_lockv(xid, tcon,
					       cfile->fid.persistent_fid,
					       cfile->fid.अस्थिर_fid,
					       current->tgid, num, buf);
			अगर (stored_rc) अणु
				/*
				 * We failed on the unlock range request - add
				 * all locks from the पंचांगp list to the head of
				 * the file's list.
				 */
				cअगरs_move_llist(&पंचांगp_llist,
						&cfile->llist->locks);
				rc = stored_rc;
			पूर्ण अन्यथा
				/*
				 * The unlock range request succeed - मुक्त the
				 * पंचांगp list.
				 */
				cअगरs_मुक्त_llist(&पंचांगp_llist);
			cur = buf;
			num = 0;
		पूर्ण अन्यथा
			cur++;
	पूर्ण
	अगर (num) अणु
		stored_rc = smb2_lockv(xid, tcon, cfile->fid.persistent_fid,
				       cfile->fid.अस्थिर_fid, current->tgid,
				       num, buf);
		अगर (stored_rc) अणु
			cअगरs_move_llist(&पंचांगp_llist, &cfile->llist->locks);
			rc = stored_rc;
		पूर्ण अन्यथा
			cअगरs_मुक्त_llist(&पंचांगp_llist);
	पूर्ण
	up_ग_लिखो(&cinode->lock_sem);

	kमुक्त(buf);
	वापस rc;
पूर्ण

अटल पूर्णांक
smb2_push_mand_fdlocks(काष्ठा cअगरs_fid_locks *fdlocks, स्थिर अचिन्हित पूर्णांक xid,
		       काष्ठा smb2_lock_element *buf, अचिन्हित पूर्णांक max_num)
अणु
	पूर्णांक rc = 0, stored_rc;
	काष्ठा cअगरsFileInfo *cfile = fdlocks->cfile;
	काष्ठा cअगरsLockInfo *li;
	अचिन्हित पूर्णांक num = 0;
	काष्ठा smb2_lock_element *cur = buf;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cfile->tlink);

	list_क्रम_each_entry(li, &fdlocks->locks, llist) अणु
		cur->Length = cpu_to_le64(li->length);
		cur->Offset = cpu_to_le64(li->offset);
		cur->Flags = cpu_to_le32(li->type |
						SMB2_LOCKFLAG_FAIL_IMMEDIATELY);
		अगर (++num == max_num) अणु
			stored_rc = smb2_lockv(xid, tcon,
					       cfile->fid.persistent_fid,
					       cfile->fid.अस्थिर_fid,
					       current->tgid, num, buf);
			अगर (stored_rc)
				rc = stored_rc;
			cur = buf;
			num = 0;
		पूर्ण अन्यथा
			cur++;
	पूर्ण
	अगर (num) अणु
		stored_rc = smb2_lockv(xid, tcon,
				       cfile->fid.persistent_fid,
				       cfile->fid.अस्थिर_fid,
				       current->tgid, num, buf);
		अगर (stored_rc)
			rc = stored_rc;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक
smb2_push_mandatory_locks(काष्ठा cअगरsFileInfo *cfile)
अणु
	पूर्णांक rc = 0, stored_rc;
	अचिन्हित पूर्णांक xid;
	अचिन्हित पूर्णांक max_num, max_buf;
	काष्ठा smb2_lock_element *buf;
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	काष्ठा cअगरs_fid_locks *fdlocks;

	xid = get_xid();

	/*
	 * Accessing maxBuf is racy with cअगरs_reconnect - need to store value
	 * and check it क्रम zero beक्रमe using.
	 */
	max_buf = tlink_tcon(cfile->tlink)->ses->server->maxBuf;
	अगर (max_buf < माप(काष्ठा smb2_lock_element)) अणु
		मुक्त_xid(xid);
		वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(माप(काष्ठा smb2_lock_element) > PAGE_SIZE);
	max_buf = min_t(अचिन्हित पूर्णांक, max_buf, PAGE_SIZE);
	max_num = max_buf / माप(काष्ठा smb2_lock_element);
	buf = kसुस्मृति(max_num, माप(काष्ठा smb2_lock_element), GFP_KERNEL);
	अगर (!buf) अणु
		मुक्त_xid(xid);
		वापस -ENOMEM;
	पूर्ण

	list_क्रम_each_entry(fdlocks, &cinode->llist, llist) अणु
		stored_rc = smb2_push_mand_fdlocks(fdlocks, xid, buf, max_num);
		अगर (stored_rc)
			rc = stored_rc;
	पूर्ण

	kमुक्त(buf);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण
