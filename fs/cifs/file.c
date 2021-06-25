<शैली गुरु>
/*
 *   fs/cअगरs/file.c
 *
 *   vfs operations that deal with files
 *
 *   Copyright (C) International Business Machines  Corp., 2002,2010
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *              Jeremy Allison (jra@samba.org)
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
#समावेश <linux/backing-dev.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/delay.h>
#समावेश <linux/mount.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/भाग64.h>
#समावेश "cifsfs.h"
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_unicode.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_fs_sb.h"
#समावेश "fscache.h"
#समावेश "smbdirect.h"
#समावेश "fs_context.h"
#समावेश "cifs_ioctl.h"

अटल अंतरभूत पूर्णांक cअगरs_convert_flags(अचिन्हित पूर्णांक flags)
अणु
	अगर ((flags & O_ACCMODE) == O_RDONLY)
		वापस GENERIC_READ;
	अन्यथा अगर ((flags & O_ACCMODE) == O_WRONLY)
		वापस GENERIC_WRITE;
	अन्यथा अगर ((flags & O_ACCMODE) == O_RDWR) अणु
		/* GENERIC_ALL is too much permission to request
		   can cause unnecessary access denied on create */
		/* वापस GENERIC_ALL; */
		वापस (GENERIC_READ | GENERIC_WRITE);
	पूर्ण

	वापस (READ_CONTROL | खाता_WRITE_ATTRIBUTES | खाता_READ_ATTRIBUTES |
		खाता_WRITE_EA | खाता_APPEND_DATA | खाता_WRITE_DATA |
		खाता_READ_DATA);
पूर्ण

अटल u32 cअगरs_posix_convert_flags(अचिन्हित पूर्णांक flags)
अणु
	u32 posix_flags = 0;

	अगर ((flags & O_ACCMODE) == O_RDONLY)
		posix_flags = SMB_O_RDONLY;
	अन्यथा अगर ((flags & O_ACCMODE) == O_WRONLY)
		posix_flags = SMB_O_WRONLY;
	अन्यथा अगर ((flags & O_ACCMODE) == O_RDWR)
		posix_flags = SMB_O_RDWR;

	अगर (flags & O_CREAT) अणु
		posix_flags |= SMB_O_CREAT;
		अगर (flags & O_EXCL)
			posix_flags |= SMB_O_EXCL;
	पूर्ण अन्यथा अगर (flags & O_EXCL)
		cअगरs_dbg(FYI, "Application %s pid %d has incorrectly set O_EXCL flag but not O_CREAT on file open. Ignoring O_EXCL\n",
			 current->comm, current->tgid);

	अगर (flags & O_TRUNC)
		posix_flags |= SMB_O_TRUNC;
	/* be safe and imply O_SYNC क्रम O_DSYNC */
	अगर (flags & O_DSYNC)
		posix_flags |= SMB_O_SYNC;
	अगर (flags & O_सूचीECTORY)
		posix_flags |= SMB_O_सूचीECTORY;
	अगर (flags & O_NOFOLLOW)
		posix_flags |= SMB_O_NOFOLLOW;
	अगर (flags & O_सूचीECT)
		posix_flags |= SMB_O_सूचीECT;

	वापस posix_flags;
पूर्ण

अटल अंतरभूत पूर्णांक cअगरs_get_disposition(अचिन्हित पूर्णांक flags)
अणु
	अगर ((flags & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL))
		वापस खाता_CREATE;
	अन्यथा अगर ((flags & (O_CREAT | O_TRUNC)) == (O_CREAT | O_TRUNC))
		वापस खाता_OVERWRITE_IF;
	अन्यथा अगर ((flags & O_CREAT) == O_CREAT)
		वापस खाता_OPEN_IF;
	अन्यथा अगर ((flags & O_TRUNC) == O_TRUNC)
		वापस खाता_OVERWRITE;
	अन्यथा
		वापस खाता_OPEN;
पूर्ण

पूर्णांक cअगरs_posix_खोलो(स्थिर अक्षर *full_path, काष्ठा inode **pinode,
			काष्ठा super_block *sb, पूर्णांक mode, अचिन्हित पूर्णांक f_flags,
			__u32 *poplock, __u16 *pnetfid, अचिन्हित पूर्णांक xid)
अणु
	पूर्णांक rc;
	खाता_UNIX_BASIC_INFO *presp_data;
	__u32 posix_flags = 0;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा cअगरs_fattr fattr;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;

	cअगरs_dbg(FYI, "posix open %s\n", full_path);

	presp_data = kzalloc(माप(खाता_UNIX_BASIC_INFO), GFP_KERNEL);
	अगर (presp_data == शून्य)
		वापस -ENOMEM;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink)) अणु
		rc = PTR_ERR(tlink);
		जाओ posix_खोलो_ret;
	पूर्ण

	tcon = tlink_tcon(tlink);
	mode &= ~current_umask();

	posix_flags = cअगरs_posix_convert_flags(f_flags);
	rc = CIFSPOSIXCreate(xid, tcon, posix_flags, mode, pnetfid, presp_data,
			     poplock, full_path, cअगरs_sb->local_nls,
			     cअगरs_remap(cअगरs_sb));
	cअगरs_put_tlink(tlink);

	अगर (rc)
		जाओ posix_खोलो_ret;

	अगर (presp_data->Type == cpu_to_le32(-1))
		जाओ posix_खोलो_ret; /* खोलो ok, caller करोes qpathinfo */

	अगर (!pinode)
		जाओ posix_खोलो_ret; /* caller करोes not need info */

	cअगरs_unix_basic_to_fattr(&fattr, presp_data, cअगरs_sb);

	/* get new inode and set it up */
	अगर (*pinode == शून्य) अणु
		cअगरs_fill_uniqueid(sb, &fattr);
		*pinode = cअगरs_iget(sb, &fattr);
		अगर (!*pinode) अणु
			rc = -ENOMEM;
			जाओ posix_खोलो_ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		cअगरs_revalidate_mapping(*pinode);
		rc = cअगरs_fattr_to_inode(*pinode, &fattr);
	पूर्ण

posix_खोलो_ret:
	kमुक्त(presp_data);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_nt_खोलो(स्थिर अक्षर *full_path, काष्ठा inode *inode, काष्ठा cअगरs_sb_info *cअगरs_sb,
	     काष्ठा cअगरs_tcon *tcon, अचिन्हित पूर्णांक f_flags, __u32 *oplock,
	     काष्ठा cअगरs_fid *fid, अचिन्हित पूर्णांक xid)
अणु
	पूर्णांक rc;
	पूर्णांक desired_access;
	पूर्णांक disposition;
	पूर्णांक create_options = CREATE_NOT_सूची;
	खाता_ALL_INFO *buf;
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	काष्ठा cअगरs_खोलो_parms oparms;

	अगर (!server->ops->खोलो)
		वापस -ENOSYS;

	desired_access = cअगरs_convert_flags(f_flags);

/*********************************************************************
 *  खोलो flag mapping table:
 *
 *	POSIX Flag            CIFS Disposition
 *	----------            ----------------
 *	O_CREAT               खाता_OPEN_IF
 *	O_CREAT | O_EXCL      खाता_CREATE
 *	O_CREAT | O_TRUNC     खाता_OVERWRITE_IF
 *	O_TRUNC               खाता_OVERWRITE
 *	none of the above     खाता_OPEN
 *
 *	Note that there is not a direct match between disposition
 *	खाता_SUPERSEDE (ie create whether or not file exists although
 *	O_CREAT | O_TRUNC is similar but truncates the existing
 *	file rather than creating a new file as खाता_SUPERSEDE करोes
 *	(which uses the attributes / metadata passed in on खोलो call)
 *?
 *?  O_SYNC is a reasonable match to CIFS ग_लिखोthrough flag
 *?  and the पढ़ो ग_लिखो flags match reasonably.  O_LARGEखाता
 *?  is irrelevant because largefile support is always used
 *?  by this client. Flags O_APPEND, O_सूचीECT, O_सूचीECTORY,
 *	 O_FASYNC, O_NOFOLLOW, O_NONBLOCK need further investigation
 *********************************************************************/

	disposition = cअगरs_get_disposition(f_flags);

	/* BB pass O_SYNC flag through on file attributes .. BB */

	buf = kदो_स्मृति(माप(खाता_ALL_INFO), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* O_SYNC also has bit क्रम O_DSYNC so following check picks up either */
	अगर (f_flags & O_SYNC)
		create_options |= CREATE_WRITE_THROUGH;

	अगर (f_flags & O_सूचीECT)
		create_options |= CREATE_NO_BUFFER;

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = desired_access;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, create_options);
	oparms.disposition = disposition;
	oparms.path = full_path;
	oparms.fid = fid;
	oparms.reconnect = false;

	rc = server->ops->खोलो(xid, &oparms, oplock, buf);

	अगर (rc)
		जाओ out;

	/* TODO: Add support क्रम calling posix query info but with passing in fid */
	अगर (tcon->unix_ext)
		rc = cअगरs_get_inode_info_unix(&inode, full_path, inode->i_sb,
					      xid);
	अन्यथा
		rc = cअगरs_get_inode_info(&inode, full_path, buf, inode->i_sb,
					 xid, fid);

	अगर (rc) अणु
		server->ops->बंद(xid, tcon, fid);
		अगर (rc == -ESTALE)
			rc = -EOPENSTALE;
	पूर्ण

out:
	kमुक्त(buf);
	वापस rc;
पूर्ण

अटल bool
cअगरs_has_mand_locks(काष्ठा cअगरsInodeInfo *cinode)
अणु
	काष्ठा cअगरs_fid_locks *cur;
	bool has_locks = false;

	करोwn_पढ़ो(&cinode->lock_sem);
	list_क्रम_each_entry(cur, &cinode->llist, llist) अणु
		अगर (!list_empty(&cur->locks)) अणु
			has_locks = true;
			अवरोध;
		पूर्ण
	पूर्ण
	up_पढ़ो(&cinode->lock_sem);
	वापस has_locks;
पूर्ण

व्योम
cअगरs_करोwn_ग_लिखो(काष्ठा rw_semaphore *sem)
अणु
	जबतक (!करोwn_ग_लिखो_trylock(sem))
		msleep(10);
पूर्ण

अटल व्योम cअगरsFileInfo_put_work(काष्ठा work_काष्ठा *work);

काष्ठा cअगरsFileInfo *
cअगरs_new_fileinfo(काष्ठा cअगरs_fid *fid, काष्ठा file *file,
		  काष्ठा tcon_link *tlink, __u32 oplock)
अणु
	काष्ठा dentry *dentry = file_dentry(file);
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(inode);
	काष्ठा cअगरsFileInfo *cfile;
	काष्ठा cअगरs_fid_locks *fdlocks;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(tlink);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;

	cfile = kzalloc(माप(काष्ठा cअगरsFileInfo), GFP_KERNEL);
	अगर (cfile == शून्य)
		वापस cfile;

	fdlocks = kzalloc(माप(काष्ठा cअगरs_fid_locks), GFP_KERNEL);
	अगर (!fdlocks) अणु
		kमुक्त(cfile);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&fdlocks->locks);
	fdlocks->cfile = cfile;
	cfile->llist = fdlocks;

	cfile->count = 1;
	cfile->pid = current->tgid;
	cfile->uid = current_fsuid();
	cfile->dentry = dget(dentry);
	cfile->f_flags = file->f_flags;
	cfile->invalidHandle = false;
	cfile->deferred_बंद_scheduled = false;
	cfile->tlink = cअगरs_get_tlink(tlink);
	INIT_WORK(&cfile->oplock_अवरोध, cअगरs_oplock_अवरोध);
	INIT_WORK(&cfile->put, cअगरsFileInfo_put_work);
	INIT_DELAYED_WORK(&cfile->deferred, smb2_deferred_work_बंद);
	mutex_init(&cfile->fh_mutex);
	spin_lock_init(&cfile->file_info_lock);

	cअगरs_sb_active(inode->i_sb);

	/*
	 * If the server वापसed a पढ़ो oplock and we have mandatory brlocks,
	 * set oplock level to None.
	 */
	अगर (server->ops->is_पढ़ो_op(oplock) && cअगरs_has_mand_locks(cinode)) अणु
		cअगरs_dbg(FYI, "Reset oplock val from read to None due to mand locks\n");
		oplock = 0;
	पूर्ण

	cअगरs_करोwn_ग_लिखो(&cinode->lock_sem);
	list_add(&fdlocks->llist, &cinode->llist);
	up_ग_लिखो(&cinode->lock_sem);

	spin_lock(&tcon->खोलो_file_lock);
	अगर (fid->pending_खोलो->oplock != CIFS_OPLOCK_NO_CHANGE && oplock)
		oplock = fid->pending_खोलो->oplock;
	list_del(&fid->pending_खोलो->olist);

	fid->purge_cache = false;
	server->ops->set_fid(cfile, fid, oplock);

	list_add(&cfile->tlist, &tcon->खोलोFileList);
	atomic_inc(&tcon->num_local_खोलोs);

	/* अगर पढ़ोable file instance put first in list*/
	spin_lock(&cinode->खोलो_file_lock);
	अगर (file->f_mode & FMODE_READ)
		list_add(&cfile->flist, &cinode->खोलोFileList);
	अन्यथा
		list_add_tail(&cfile->flist, &cinode->खोलोFileList);
	spin_unlock(&cinode->खोलो_file_lock);
	spin_unlock(&tcon->खोलो_file_lock);

	अगर (fid->purge_cache)
		cअगरs_zap_mapping(inode);

	file->निजी_data = cfile;
	वापस cfile;
पूर्ण

काष्ठा cअगरsFileInfo *
cअगरsFileInfo_get(काष्ठा cअगरsFileInfo *cअगरs_file)
अणु
	spin_lock(&cअगरs_file->file_info_lock);
	cअगरsFileInfo_get_locked(cअगरs_file);
	spin_unlock(&cअगरs_file->file_info_lock);
	वापस cअगरs_file;
पूर्ण

अटल व्योम cअगरsFileInfo_put_final(काष्ठा cअगरsFileInfo *cअगरs_file)
अणु
	काष्ठा inode *inode = d_inode(cअगरs_file->dentry);
	काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(inode);
	काष्ठा cअगरsLockInfo *li, *पंचांगp;
	काष्ठा super_block *sb = inode->i_sb;

	/*
	 * Delete any outstanding lock records. We'll lose them when the file
	 * is बंदd anyway.
	 */
	cअगरs_करोwn_ग_लिखो(&cअगरsi->lock_sem);
	list_क्रम_each_entry_safe(li, पंचांगp, &cअगरs_file->llist->locks, llist) अणु
		list_del(&li->llist);
		cअगरs_del_lock_रुकोers(li);
		kमुक्त(li);
	पूर्ण
	list_del(&cअगरs_file->llist->llist);
	kमुक्त(cअगरs_file->llist);
	up_ग_लिखो(&cअगरsi->lock_sem);

	cअगरs_put_tlink(cअगरs_file->tlink);
	dput(cअगरs_file->dentry);
	cअगरs_sb_deactive(sb);
	kमुक्त(cअगरs_file);
पूर्ण

अटल व्योम cअगरsFileInfo_put_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cअगरsFileInfo *cअगरs_file = container_of(work,
			काष्ठा cअगरsFileInfo, put);

	cअगरsFileInfo_put_final(cअगरs_file);
पूर्ण

/**
 * cअगरsFileInfo_put - release a reference of file priv data
 *
 * Always potentially रुको क्रम oplock handler. See _cअगरsFileInfo_put().
 *
 * @cअगरs_file:	cअगरs/smb3 specअगरic info (eg refcounts) क्रम an खोलो file
 */
व्योम cअगरsFileInfo_put(काष्ठा cअगरsFileInfo *cअगरs_file)
अणु
	_cअगरsFileInfo_put(cअगरs_file, true, true);
पूर्ण

/**
 * _cअगरsFileInfo_put - release a reference of file priv data
 *
 * This may involve closing the filehandle @cअगरs_file out on the
 * server. Must be called without holding tcon->खोलो_file_lock,
 * cinode->खोलो_file_lock and cअगरs_file->file_info_lock.
 *
 * If @रुको_क्रम_oplock_handler is true and we are releasing the last
 * reference, रुको क्रम any running oplock अवरोध handler of the file
 * and cancel any pending one.
 *
 * @cअगरs_file:	cअगरs/smb3 specअगरic info (eg refcounts) क्रम an खोलो file
 * @रुको_oplock_handler: must be false अगर called from oplock_अवरोध_handler
 * @offload:	not offloaded on बंद and oplock अवरोधs
 *
 */
व्योम _cअगरsFileInfo_put(काष्ठा cअगरsFileInfo *cअगरs_file,
		       bool रुको_oplock_handler, bool offload)
अणु
	काष्ठा inode *inode = d_inode(cअगरs_file->dentry);
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cअगरs_file->tlink);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_pending_खोलो खोलो;
	bool oplock_अवरोध_cancelled;

	spin_lock(&tcon->खोलो_file_lock);
	spin_lock(&cअगरsi->खोलो_file_lock);
	spin_lock(&cअगरs_file->file_info_lock);
	अगर (--cअगरs_file->count > 0) अणु
		spin_unlock(&cअगरs_file->file_info_lock);
		spin_unlock(&cअगरsi->खोलो_file_lock);
		spin_unlock(&tcon->खोलो_file_lock);
		वापस;
	पूर्ण
	spin_unlock(&cअगरs_file->file_info_lock);

	अगर (server->ops->get_lease_key)
		server->ops->get_lease_key(inode, &fid);

	/* store खोलो in pending खोलोs to make sure we करोn't miss lease अवरोध */
	cअगरs_add_pending_खोलो_locked(&fid, cअगरs_file->tlink, &खोलो);

	/* हटाओ it from the lists */
	list_del(&cअगरs_file->flist);
	list_del(&cअगरs_file->tlist);
	atomic_dec(&tcon->num_local_खोलोs);

	अगर (list_empty(&cअगरsi->खोलोFileList)) अणु
		cअगरs_dbg(FYI, "closing last open instance for inode %p\n",
			 d_inode(cअगरs_file->dentry));
		/*
		 * In strict cache mode we need invalidate mapping on the last
		 * बंद  because it may cause a error when we खोलो this file
		 * again and get at least level II oplock.
		 */
		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_STRICT_IO)
			set_bit(CIFS_INO_INVALID_MAPPING, &cअगरsi->flags);
		cअगरs_set_oplock_level(cअगरsi, 0);
	पूर्ण

	spin_unlock(&cअगरsi->खोलो_file_lock);
	spin_unlock(&tcon->खोलो_file_lock);

	oplock_अवरोध_cancelled = रुको_oplock_handler ?
		cancel_work_sync(&cअगरs_file->oplock_अवरोध) : false;

	अगर (!tcon->need_reconnect && !cअगरs_file->invalidHandle) अणु
		काष्ठा TCP_Server_Info *server = tcon->ses->server;
		अचिन्हित पूर्णांक xid;

		xid = get_xid();
		अगर (server->ops->बंद_getattr)
			server->ops->बंद_getattr(xid, tcon, cअगरs_file);
		अन्यथा अगर (server->ops->बंद)
			server->ops->बंद(xid, tcon, &cअगरs_file->fid);
		_मुक्त_xid(xid);
	पूर्ण

	अगर (oplock_अवरोध_cancelled)
		cअगरs_करोne_oplock_अवरोध(cअगरsi);

	cअगरs_del_pending_खोलो(&खोलो);

	अगर (offload)
		queue_work(fileinfo_put_wq, &cअगरs_file->put);
	अन्यथा
		cअगरsFileInfo_put_final(cअगरs_file);
पूर्ण

पूर्णांक cअगरs_खोलो(काष्ठा inode *inode, काष्ठा file *file)

अणु
	पूर्णांक rc = -EACCES;
	अचिन्हित पूर्णांक xid;
	__u32 oplock;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरsFileInfo *cfile = शून्य;
	व्योम *page;
	स्थिर अक्षर *full_path;
	bool posix_खोलो_ok = false;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_pending_खोलो खोलो;

	xid = get_xid();

	cअगरs_sb = CIFS_SB(inode->i_sb);
	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(cअगरs_sb))) अणु
		मुक्त_xid(xid);
		वापस -EIO;
	पूर्ण

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink)) अणु
		मुक्त_xid(xid);
		वापस PTR_ERR(tlink);
	पूर्ण
	tcon = tlink_tcon(tlink);
	server = tcon->ses->server;

	page = alloc_dentry_path();
	full_path = build_path_from_dentry(file_dentry(file), page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ out;
	पूर्ण

	cअगरs_dbg(FYI, "inode = 0x%p file flags are 0x%x for %s\n",
		 inode, file->f_flags, full_path);

	अगर (file->f_flags & O_सूचीECT &&
	    cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_STRICT_IO) अणु
		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_BRL)
			file->f_op = &cअगरs_file_direct_nobrl_ops;
		अन्यथा
			file->f_op = &cअगरs_file_direct_ops;
	पूर्ण

	/* Get the cached handle as SMB2 बंद is deferred */
	rc = cअगरs_get_पढ़ोable_path(tcon, full_path, &cfile);
	अगर (rc == 0) अणु
		अगर (file->f_flags == cfile->f_flags) अणु
			file->निजी_data = cfile;
			spin_lock(&CIFS_I(inode)->deferred_lock);
			cअगरs_del_deferred_बंद(cfile);
			spin_unlock(&CIFS_I(inode)->deferred_lock);
			जाओ out;
		पूर्ण अन्यथा अणु
			_cअगरsFileInfo_put(cfile, true, false);
		पूर्ण
	पूर्ण

	अगर (server->oplocks)
		oplock = REQ_OPLOCK;
	अन्यथा
		oplock = 0;

	अगर (!tcon->broken_posix_खोलो && tcon->unix_ext &&
	    cap_unix(tcon->ses) && (CIFS_UNIX_POSIX_PATH_OPS_CAP &
				le64_to_cpu(tcon->fsUnixInfo.Capability))) अणु
		/* can not refresh inode info since size could be stale */
		rc = cअगरs_posix_खोलो(full_path, &inode, inode->i_sb,
				cअगरs_sb->ctx->file_mode /* ignored */,
				file->f_flags, &oplock, &fid.netfid, xid);
		अगर (rc == 0) अणु
			cअगरs_dbg(FYI, "posix open succeeded\n");
			posix_खोलो_ok = true;
		पूर्ण अन्यथा अगर ((rc == -EINVAL) || (rc == -EOPNOTSUPP)) अणु
			अगर (tcon->ses->serverNOS)
				cअगरs_dbg(VFS, "server %s of type %s returned unexpected error on SMB posix open, disabling posix open support. Check if server update available.\n",
					 tcon->ses->ip_addr,
					 tcon->ses->serverNOS);
			tcon->broken_posix_खोलो = true;
		पूर्ण अन्यथा अगर ((rc != -EIO) && (rc != -EREMOTE) &&
			 (rc != -EOPNOTSUPP)) /* path not found or net err */
			जाओ out;
		/*
		 * Else fallthrough to retry खोलो the old way on network i/o
		 * or DFS errors.
		 */
	पूर्ण

	अगर (server->ops->get_lease_key)
		server->ops->get_lease_key(inode, &fid);

	cअगरs_add_pending_खोलो(&fid, tlink, &खोलो);

	अगर (!posix_खोलो_ok) अणु
		अगर (server->ops->get_lease_key)
			server->ops->get_lease_key(inode, &fid);

		rc = cअगरs_nt_खोलो(full_path, inode, cअगरs_sb, tcon,
				  file->f_flags, &oplock, &fid, xid);
		अगर (rc) अणु
			cअगरs_del_pending_खोलो(&खोलो);
			जाओ out;
		पूर्ण
	पूर्ण

	cfile = cअगरs_new_fileinfo(&fid, file, tlink, oplock);
	अगर (cfile == शून्य) अणु
		अगर (server->ops->बंद)
			server->ops->बंद(xid, tcon, &fid);
		cअगरs_del_pending_खोलो(&खोलो);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	cअगरs_fscache_set_inode_cookie(inode, file);

	अगर ((oplock & CIFS_CREATE_ACTION) && !posix_खोलो_ok && tcon->unix_ext) अणु
		/*
		 * Time to set mode which we can not set earlier due to
		 * problems creating new पढ़ो-only files.
		 */
		काष्ठा cअगरs_unix_set_info_args args = अणु
			.mode	= inode->i_mode,
			.uid	= INVALID_UID, /* no change */
			.gid	= INVALID_GID, /* no change */
			.स_समय	= NO_CHANGE_64,
			.aसमय	= NO_CHANGE_64,
			.mसमय	= NO_CHANGE_64,
			.device	= 0,
		पूर्ण;
		CIFSSMBUnixSetFileInfo(xid, tcon, &args, fid.netfid,
				       cfile->pid);
	पूर्ण

out:
	मुक्त_dentry_path(page);
	मुक्त_xid(xid);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

अटल पूर्णांक cअगरs_push_posix_locks(काष्ठा cअगरsFileInfo *cfile);

/*
 * Try to reacquire byte range locks that were released when session
 * to server was lost.
 */
अटल पूर्णांक
cअगरs_relock_file(काष्ठा cअगरsFileInfo *cfile)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(cfile->dentry->d_sb);
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cfile->tlink);
	पूर्णांक rc = 0;

	करोwn_पढ़ो_nested(&cinode->lock_sem, SINGLE_DEPTH_NESTING);
	अगर (cinode->can_cache_brlcks) अणु
		/* can cache locks - no need to relock */
		up_पढ़ो(&cinode->lock_sem);
		वापस rc;
	पूर्ण

	अगर (cap_unix(tcon->ses) &&
	    (CIFS_UNIX_FCNTL_CAP & le64_to_cpu(tcon->fsUnixInfo.Capability)) &&
	    ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NOPOSIXBRL) == 0))
		rc = cअगरs_push_posix_locks(cfile);
	अन्यथा
		rc = tcon->ses->server->ops->push_mand_locks(cfile);

	up_पढ़ो(&cinode->lock_sem);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_reखोलो_file(काष्ठा cअगरsFileInfo *cfile, bool can_flush)
अणु
	पूर्णांक rc = -EACCES;
	अचिन्हित पूर्णांक xid;
	__u32 oplock;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरsInodeInfo *cinode;
	काष्ठा inode *inode;
	व्योम *page;
	स्थिर अक्षर *full_path;
	पूर्णांक desired_access;
	पूर्णांक disposition = खाता_OPEN;
	पूर्णांक create_options = CREATE_NOT_सूची;
	काष्ठा cअगरs_खोलो_parms oparms;

	xid = get_xid();
	mutex_lock(&cfile->fh_mutex);
	अगर (!cfile->invalidHandle) अणु
		mutex_unlock(&cfile->fh_mutex);
		मुक्त_xid(xid);
		वापस 0;
	पूर्ण

	inode = d_inode(cfile->dentry);
	cअगरs_sb = CIFS_SB(inode->i_sb);
	tcon = tlink_tcon(cfile->tlink);
	server = tcon->ses->server;

	/*
	 * Can not grab नाम sem here because various ops, including those
	 * that alपढ़ोy have the नाम sem can end up causing ग_लिखोpage to get
	 * called and अगर the server was करोwn that means we end up here, and we
	 * can never tell अगर the caller alपढ़ोy has the नाम_sem.
	 */
	page = alloc_dentry_path();
	full_path = build_path_from_dentry(cfile->dentry, page);
	अगर (IS_ERR(full_path)) अणु
		mutex_unlock(&cfile->fh_mutex);
		मुक्त_dentry_path(page);
		मुक्त_xid(xid);
		वापस PTR_ERR(full_path);
	पूर्ण

	cअगरs_dbg(FYI, "inode = 0x%p file flags 0x%x for %s\n",
		 inode, cfile->f_flags, full_path);

	अगर (tcon->ses->server->oplocks)
		oplock = REQ_OPLOCK;
	अन्यथा
		oplock = 0;

	अगर (tcon->unix_ext && cap_unix(tcon->ses) &&
	    (CIFS_UNIX_POSIX_PATH_OPS_CAP &
				le64_to_cpu(tcon->fsUnixInfo.Capability))) अणु
		/*
		 * O_CREAT, O_EXCL and O_TRUNC alपढ़ोy had their effect on the
		 * original खोलो. Must mask them off क्रम a reखोलो.
		 */
		अचिन्हित पूर्णांक oflags = cfile->f_flags &
						~(O_CREAT | O_EXCL | O_TRUNC);

		rc = cअगरs_posix_खोलो(full_path, शून्य, inode->i_sb,
				     cअगरs_sb->ctx->file_mode /* ignored */,
				     oflags, &oplock, &cfile->fid.netfid, xid);
		अगर (rc == 0) अणु
			cअगरs_dbg(FYI, "posix reopen succeeded\n");
			oparms.reconnect = true;
			जाओ reखोलो_success;
		पूर्ण
		/*
		 * fallthrough to retry खोलो the old way on errors, especially
		 * in the reconnect path it is important to retry hard
		 */
	पूर्ण

	desired_access = cअगरs_convert_flags(cfile->f_flags);

	/* O_SYNC also has bit क्रम O_DSYNC so following check picks up either */
	अगर (cfile->f_flags & O_SYNC)
		create_options |= CREATE_WRITE_THROUGH;

	अगर (cfile->f_flags & O_सूचीECT)
		create_options |= CREATE_NO_BUFFER;

	अगर (server->ops->get_lease_key)
		server->ops->get_lease_key(inode, &cfile->fid);

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = desired_access;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, create_options);
	oparms.disposition = disposition;
	oparms.path = full_path;
	oparms.fid = &cfile->fid;
	oparms.reconnect = true;

	/*
	 * Can not refresh inode by passing in file_info buf to be वापसed by
	 * ops->खोलो and then calling get_inode_info with वापसed buf since
	 * file might have ग_लिखो behind data that needs to be flushed and server
	 * version of file size can be stale. If we knew क्रम sure that inode was
	 * not dirty locally we could करो this.
	 */
	rc = server->ops->खोलो(xid, &oparms, &oplock, शून्य);
	अगर (rc == -ENOENT && oparms.reconnect == false) अणु
		/* durable handle समयout is expired - खोलो the file again */
		rc = server->ops->खोलो(xid, &oparms, &oplock, शून्य);
		/* indicate that we need to relock the file */
		oparms.reconnect = true;
	पूर्ण

	अगर (rc) अणु
		mutex_unlock(&cfile->fh_mutex);
		cअगरs_dbg(FYI, "cifs_reopen returned 0x%x\n", rc);
		cअगरs_dbg(FYI, "oplock: %d\n", oplock);
		जाओ reखोलो_error_निकास;
	पूर्ण

reखोलो_success:
	cfile->invalidHandle = false;
	mutex_unlock(&cfile->fh_mutex);
	cinode = CIFS_I(inode);

	अगर (can_flush) अणु
		rc = filemap_ग_लिखो_and_रुको(inode->i_mapping);
		अगर (!is_पूर्णांकerrupt_error(rc))
			mapping_set_error(inode->i_mapping, rc);

		अगर (tcon->posix_extensions)
			rc = smb311_posix_get_inode_info(&inode, full_path, inode->i_sb, xid);
		अन्यथा अगर (tcon->unix_ext)
			rc = cअगरs_get_inode_info_unix(&inode, full_path,
						      inode->i_sb, xid);
		अन्यथा
			rc = cअगरs_get_inode_info(&inode, full_path, शून्य,
						 inode->i_sb, xid, शून्य);
	पूर्ण
	/*
	 * Else we are writing out data to server alपढ़ोy and could deadlock अगर
	 * we tried to flush data, and since we करो not know अगर we have data that
	 * would invalidate the current end of file on the server we can not go
	 * to the server to get the new inode info.
	 */

	/*
	 * If the server वापसed a पढ़ो oplock and we have mandatory brlocks,
	 * set oplock level to None.
	 */
	अगर (server->ops->is_पढ़ो_op(oplock) && cअगरs_has_mand_locks(cinode)) अणु
		cअगरs_dbg(FYI, "Reset oplock val from read to None due to mand locks\n");
		oplock = 0;
	पूर्ण

	server->ops->set_fid(cfile, &cfile->fid, oplock);
	अगर (oparms.reconnect)
		cअगरs_relock_file(cfile);

reखोलो_error_निकास:
	मुक्त_dentry_path(page);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

व्योम smb2_deferred_work_बंद(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cअगरsFileInfo *cfile = container_of(work,
			काष्ठा cअगरsFileInfo, deferred.work);

	spin_lock(&CIFS_I(d_inode(cfile->dentry))->deferred_lock);
	cअगरs_del_deferred_बंद(cfile);
	cfile->deferred_बंद_scheduled = false;
	spin_unlock(&CIFS_I(d_inode(cfile->dentry))->deferred_lock);
	_cअगरsFileInfo_put(cfile, true, false);
पूर्ण

पूर्णांक cअगरs_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा cअगरsFileInfo *cfile;
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(inode);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा cअगरs_deferred_बंद *dबंद;

	अगर (file->निजी_data != शून्य) अणु
		cfile = file->निजी_data;
		file->निजी_data = शून्य;
		dबंद = kदो_स्मृति(माप(काष्ठा cअगरs_deferred_बंद), GFP_KERNEL);
		अगर ((cinode->oplock == CIFS_CACHE_RHW_FLG) &&
		    cinode->lease_granted &&
		    dबंद) अणु
			अगर (test_bit(CIFS_INO_MODIFIED_ATTR, &cinode->flags))
				inode->i_स_समय = inode->i_mसमय = current_समय(inode);
			spin_lock(&cinode->deferred_lock);
			cअगरs_add_deferred_बंद(cfile, dबंद);
			अगर (cfile->deferred_बंद_scheduled &&
			    delayed_work_pending(&cfile->deferred)) अणु
				/*
				 * If there is no pending work, mod_delayed_work queues new work.
				 * So, Increase the ref count to aव्योम use-after-मुक्त.
				 */
				अगर (!mod_delayed_work(deferredबंद_wq,
						&cfile->deferred, cअगरs_sb->ctx->acregmax))
					cअगरsFileInfo_get(cfile);
			पूर्ण अन्यथा अणु
				/* Deferred बंद क्रम files */
				queue_delayed_work(deferredबंद_wq,
						&cfile->deferred, cअगरs_sb->ctx->acregmax);
				cfile->deferred_बंद_scheduled = true;
				spin_unlock(&cinode->deferred_lock);
				वापस 0;
			पूर्ण
			spin_unlock(&cinode->deferred_lock);
			_cअगरsFileInfo_put(cfile, true, false);
		पूर्ण अन्यथा अणु
			_cअगरsFileInfo_put(cfile, true, false);
			kमुक्त(dबंद);
		पूर्ण
	पूर्ण

	/* वापस code from the ->release op is always ignored */
	वापस 0;
पूर्ण

व्योम
cअगरs_reखोलो_persistent_handles(काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा cअगरsFileInfo *खोलो_file;
	काष्ठा list_head *पंचांगp;
	काष्ठा list_head *पंचांगp1;
	काष्ठा list_head पंचांगp_list;

	अगर (!tcon->use_persistent || !tcon->need_reखोलो_files)
		वापस;

	tcon->need_reखोलो_files = false;

	cअगरs_dbg(FYI, "Reopen persistent handles\n");
	INIT_LIST_HEAD(&पंचांगp_list);

	/* list all files खोलो on tree connection, reखोलो resilient handles  */
	spin_lock(&tcon->खोलो_file_lock);
	list_क्रम_each(पंचांगp, &tcon->खोलोFileList) अणु
		खोलो_file = list_entry(पंचांगp, काष्ठा cअगरsFileInfo, tlist);
		अगर (!खोलो_file->invalidHandle)
			जारी;
		cअगरsFileInfo_get(खोलो_file);
		list_add_tail(&खोलो_file->rlist, &पंचांगp_list);
	पूर्ण
	spin_unlock(&tcon->खोलो_file_lock);

	list_क्रम_each_safe(पंचांगp, पंचांगp1, &पंचांगp_list) अणु
		खोलो_file = list_entry(पंचांगp, काष्ठा cअगरsFileInfo, rlist);
		अगर (cअगरs_reखोलो_file(खोलो_file, false /* करो not flush */))
			tcon->need_reखोलो_files = true;
		list_del_init(&खोलो_file->rlist);
		cअगरsFileInfo_put(खोलो_file);
	पूर्ण
पूर्ण

पूर्णांक cअगरs_बंद_सूची(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरsFileInfo *cfile = file->निजी_data;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	अक्षर *buf;

	cअगरs_dbg(FYI, "Closedir inode = 0x%p\n", inode);

	अगर (cfile == शून्य)
		वापस rc;

	xid = get_xid();
	tcon = tlink_tcon(cfile->tlink);
	server = tcon->ses->server;

	cअगरs_dbg(FYI, "Freeing private data in close dir\n");
	spin_lock(&cfile->file_info_lock);
	अगर (server->ops->dir_needs_बंद(cfile)) अणु
		cfile->invalidHandle = true;
		spin_unlock(&cfile->file_info_lock);
		अगर (server->ops->बंद_dir)
			rc = server->ops->बंद_dir(xid, tcon, &cfile->fid);
		अन्यथा
			rc = -ENOSYS;
		cअगरs_dbg(FYI, "Closing uncompleted readdir with rc %d\n", rc);
		/* not much we can करो अगर it fails anyway, ignore rc */
		rc = 0;
	पूर्ण अन्यथा
		spin_unlock(&cfile->file_info_lock);

	buf = cfile->srch_inf.ntwrk_buf_start;
	अगर (buf) अणु
		cअगरs_dbg(FYI, "closedir free smb buf in srch struct\n");
		cfile->srch_inf.ntwrk_buf_start = शून्य;
		अगर (cfile->srch_inf.smallBuf)
			cअगरs_small_buf_release(buf);
		अन्यथा
			cअगरs_buf_release(buf);
	पूर्ण

	cअगरs_put_tlink(cfile->tlink);
	kमुक्त(file->निजी_data);
	file->निजी_data = शून्य;
	/* BB can we lock the fileकाष्ठा जबतक this is going on? */
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल काष्ठा cअगरsLockInfo *
cअगरs_lock_init(__u64 offset, __u64 length, __u8 type, __u16 flags)
अणु
	काष्ठा cअगरsLockInfo *lock =
		kदो_स्मृति(माप(काष्ठा cअगरsLockInfo), GFP_KERNEL);
	अगर (!lock)
		वापस lock;
	lock->offset = offset;
	lock->length = length;
	lock->type = type;
	lock->pid = current->tgid;
	lock->flags = flags;
	INIT_LIST_HEAD(&lock->blist);
	init_रुकोqueue_head(&lock->block_q);
	वापस lock;
पूर्ण

व्योम
cअगरs_del_lock_रुकोers(काष्ठा cअगरsLockInfo *lock)
अणु
	काष्ठा cअगरsLockInfo *li, *पंचांगp;
	list_क्रम_each_entry_safe(li, पंचांगp, &lock->blist, blist) अणु
		list_del_init(&li->blist);
		wake_up(&li->block_q);
	पूर्ण
पूर्ण

#घोषणा CIFS_LOCK_OP	0
#घोषणा CIFS_READ_OP	1
#घोषणा CIFS_WRITE_OP	2

/* @rw_check : 0 - no op, 1 - पढ़ो, 2 - ग_लिखो */
अटल bool
cअगरs_find_fid_lock_conflict(काष्ठा cअगरs_fid_locks *fdlocks, __u64 offset,
			    __u64 length, __u8 type, __u16 flags,
			    काष्ठा cअगरsFileInfo *cfile,
			    काष्ठा cअगरsLockInfo **conf_lock, पूर्णांक rw_check)
अणु
	काष्ठा cअगरsLockInfo *li;
	काष्ठा cअगरsFileInfo *cur_cfile = fdlocks->cfile;
	काष्ठा TCP_Server_Info *server = tlink_tcon(cfile->tlink)->ses->server;

	list_क्रम_each_entry(li, &fdlocks->locks, llist) अणु
		अगर (offset + length <= li->offset ||
		    offset >= li->offset + li->length)
			जारी;
		अगर (rw_check != CIFS_LOCK_OP && current->tgid == li->pid &&
		    server->ops->compare_fids(cfile, cur_cfile)) अणु
			/* shared lock prevents ग_लिखो op through the same fid */
			अगर (!(li->type & server->vals->shared_lock_type) ||
			    rw_check != CIFS_WRITE_OP)
				जारी;
		पूर्ण
		अगर ((type & server->vals->shared_lock_type) &&
		    ((server->ops->compare_fids(cfile, cur_cfile) &&
		     current->tgid == li->pid) || type == li->type))
			जारी;
		अगर (rw_check == CIFS_LOCK_OP &&
		    (flags & FL_OFDLCK) && (li->flags & FL_OFDLCK) &&
		    server->ops->compare_fids(cfile, cur_cfile))
			जारी;
		अगर (conf_lock)
			*conf_lock = li;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool
cअगरs_find_lock_conflict(काष्ठा cअगरsFileInfo *cfile, __u64 offset, __u64 length,
			__u8 type, __u16 flags,
			काष्ठा cअगरsLockInfo **conf_lock, पूर्णांक rw_check)
अणु
	bool rc = false;
	काष्ठा cअगरs_fid_locks *cur;
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));

	list_क्रम_each_entry(cur, &cinode->llist, llist) अणु
		rc = cअगरs_find_fid_lock_conflict(cur, offset, length, type,
						 flags, cfile, conf_lock,
						 rw_check);
		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Check अगर there is another lock that prevents us to set the lock (mandatory
 * style). If such a lock exists, update the flock काष्ठाure with its
 * properties. Otherwise, set the flock type to F_UNLCK अगर we can cache brlocks
 * or leave it the same अगर we can't. Returns 0 if we don't need to request to
 * the server or 1 otherwise.
 */
अटल पूर्णांक
cअगरs_lock_test(काष्ठा cअगरsFileInfo *cfile, __u64 offset, __u64 length,
	       __u8 type, काष्ठा file_lock *flock)
अणु
	पूर्णांक rc = 0;
	काष्ठा cअगरsLockInfo *conf_lock;
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	काष्ठा TCP_Server_Info *server = tlink_tcon(cfile->tlink)->ses->server;
	bool exist;

	करोwn_पढ़ो(&cinode->lock_sem);

	exist = cअगरs_find_lock_conflict(cfile, offset, length, type,
					flock->fl_flags, &conf_lock,
					CIFS_LOCK_OP);
	अगर (exist) अणु
		flock->fl_start = conf_lock->offset;
		flock->fl_end = conf_lock->offset + conf_lock->length - 1;
		flock->fl_pid = conf_lock->pid;
		अगर (conf_lock->type & server->vals->shared_lock_type)
			flock->fl_type = F_RDLCK;
		अन्यथा
			flock->fl_type = F_WRLCK;
	पूर्ण अन्यथा अगर (!cinode->can_cache_brlcks)
		rc = 1;
	अन्यथा
		flock->fl_type = F_UNLCK;

	up_पढ़ो(&cinode->lock_sem);
	वापस rc;
पूर्ण

अटल व्योम
cअगरs_lock_add(काष्ठा cअगरsFileInfo *cfile, काष्ठा cअगरsLockInfo *lock)
अणु
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	cअगरs_करोwn_ग_लिखो(&cinode->lock_sem);
	list_add_tail(&lock->llist, &cfile->llist->locks);
	up_ग_लिखो(&cinode->lock_sem);
पूर्ण

/*
 * Set the byte-range lock (mandatory style). Returns:
 * 1) 0, अगर we set the lock and करोn't need to request to the server;
 * 2) 1, अगर no locks prevent us but we need to request to the server;
 * 3) -EACCES, अगर there is a lock that prevents us and रुको is false.
 */
अटल पूर्णांक
cअगरs_lock_add_अगर(काष्ठा cअगरsFileInfo *cfile, काष्ठा cअगरsLockInfo *lock,
		 bool रुको)
अणु
	काष्ठा cअगरsLockInfo *conf_lock;
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	bool exist;
	पूर्णांक rc = 0;

try_again:
	exist = false;
	cअगरs_करोwn_ग_लिखो(&cinode->lock_sem);

	exist = cअगरs_find_lock_conflict(cfile, lock->offset, lock->length,
					lock->type, lock->flags, &conf_lock,
					CIFS_LOCK_OP);
	अगर (!exist && cinode->can_cache_brlcks) अणु
		list_add_tail(&lock->llist, &cfile->llist->locks);
		up_ग_लिखो(&cinode->lock_sem);
		वापस rc;
	पूर्ण

	अगर (!exist)
		rc = 1;
	अन्यथा अगर (!रुको)
		rc = -EACCES;
	अन्यथा अणु
		list_add_tail(&lock->blist, &conf_lock->blist);
		up_ग_लिखो(&cinode->lock_sem);
		rc = रुको_event_पूर्णांकerruptible(lock->block_q,
					(lock->blist.prev == &lock->blist) &&
					(lock->blist.next == &lock->blist));
		अगर (!rc)
			जाओ try_again;
		cअगरs_करोwn_ग_लिखो(&cinode->lock_sem);
		list_del_init(&lock->blist);
	पूर्ण

	up_ग_लिखो(&cinode->lock_sem);
	वापस rc;
पूर्ण

/*
 * Check अगर there is another lock that prevents us to set the lock (posix
 * style). If such a lock exists, update the flock काष्ठाure with its
 * properties. Otherwise, set the flock type to F_UNLCK अगर we can cache brlocks
 * or leave it the same अगर we can't. Returns 0 if we don't need to request to
 * the server or 1 otherwise.
 */
अटल पूर्णांक
cअगरs_posix_lock_test(काष्ठा file *file, काष्ठा file_lock *flock)
अणु
	पूर्णांक rc = 0;
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(file_inode(file));
	अचिन्हित अक्षर saved_type = flock->fl_type;

	अगर ((flock->fl_flags & FL_POSIX) == 0)
		वापस 1;

	करोwn_पढ़ो(&cinode->lock_sem);
	posix_test_lock(file, flock);

	अगर (flock->fl_type == F_UNLCK && !cinode->can_cache_brlcks) अणु
		flock->fl_type = saved_type;
		rc = 1;
	पूर्ण

	up_पढ़ो(&cinode->lock_sem);
	वापस rc;
पूर्ण

/*
 * Set the byte-range lock (posix style). Returns:
 * 1) <0, अगर the error occurs जबतक setting the lock;
 * 2) 0, अगर we set the lock and करोn't need to request to the server;
 * 3) खाता_LOCK_DEFERRED, अगर we will रुको क्रम some other file_lock;
 * 4) खाता_LOCK_DEFERRED + 1, अगर we need to request to the server.
 */
अटल पूर्णांक
cअगरs_posix_lock_set(काष्ठा file *file, काष्ठा file_lock *flock)
अणु
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(file_inode(file));
	पूर्णांक rc = खाता_LOCK_DEFERRED + 1;

	अगर ((flock->fl_flags & FL_POSIX) == 0)
		वापस rc;

	cअगरs_करोwn_ग_लिखो(&cinode->lock_sem);
	अगर (!cinode->can_cache_brlcks) अणु
		up_ग_लिखो(&cinode->lock_sem);
		वापस rc;
	पूर्ण

	rc = posix_lock_file(file, flock, शून्य);
	up_ग_लिखो(&cinode->lock_sem);
	वापस rc;
पूर्ण

पूर्णांक
cअगरs_push_mandatory_locks(काष्ठा cअगरsFileInfo *cfile)
अणु
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc = 0, stored_rc;
	काष्ठा cअगरsLockInfo *li, *पंचांगp;
	काष्ठा cअगरs_tcon *tcon;
	अचिन्हित पूर्णांक num, max_num, max_buf;
	LOCKING_ANDX_RANGE *buf, *cur;
	अटल स्थिर पूर्णांक types[] = अणु
		LOCKING_ANDX_LARGE_खाताS,
		LOCKING_ANDX_SHARED_LOCK | LOCKING_ANDX_LARGE_खाताS
	पूर्ण;
	पूर्णांक i;

	xid = get_xid();
	tcon = tlink_tcon(cfile->tlink);

	/*
	 * Accessing maxBuf is racy with cअगरs_reconnect - need to store value
	 * and check it beक्रमe using.
	 */
	max_buf = tcon->ses->server->maxBuf;
	अगर (max_buf < (माप(काष्ठा smb_hdr) + माप(LOCKING_ANDX_RANGE))) अणु
		मुक्त_xid(xid);
		वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(माप(काष्ठा smb_hdr) + माप(LOCKING_ANDX_RANGE) >
		     PAGE_SIZE);
	max_buf = min_t(अचिन्हित पूर्णांक, max_buf - माप(काष्ठा smb_hdr),
			PAGE_SIZE);
	max_num = (max_buf - माप(काष्ठा smb_hdr)) /
						माप(LOCKING_ANDX_RANGE);
	buf = kसुस्मृति(max_num, माप(LOCKING_ANDX_RANGE), GFP_KERNEL);
	अगर (!buf) अणु
		मुक्त_xid(xid);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		cur = buf;
		num = 0;
		list_क्रम_each_entry_safe(li, पंचांगp, &cfile->llist->locks, llist) अणु
			अगर (li->type != types[i])
				जारी;
			cur->Pid = cpu_to_le16(li->pid);
			cur->LengthLow = cpu_to_le32((u32)li->length);
			cur->LengthHigh = cpu_to_le32((u32)(li->length>>32));
			cur->OffsetLow = cpu_to_le32((u32)li->offset);
			cur->OffsetHigh = cpu_to_le32((u32)(li->offset>>32));
			अगर (++num == max_num) अणु
				stored_rc = cअगरs_lockv(xid, tcon,
						       cfile->fid.netfid,
						       (__u8)li->type, 0, num,
						       buf);
				अगर (stored_rc)
					rc = stored_rc;
				cur = buf;
				num = 0;
			पूर्ण अन्यथा
				cur++;
		पूर्ण

		अगर (num) अणु
			stored_rc = cअगरs_lockv(xid, tcon, cfile->fid.netfid,
					       (__u8)types[i], 0, num, buf);
			अगर (stored_rc)
				rc = stored_rc;
		पूर्ण
	पूर्ण

	kमुक्त(buf);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल __u32
hash_lockowner(fl_owner_t owner)
अणु
	वापस cअगरs_lock_secret ^ hash32_ptr((स्थिर व्योम *)owner);
पूर्ण

काष्ठा lock_to_push अणु
	काष्ठा list_head llist;
	__u64 offset;
	__u64 length;
	__u32 pid;
	__u16 netfid;
	__u8 type;
पूर्ण;

अटल पूर्णांक
cअगरs_push_posix_locks(काष्ठा cअगरsFileInfo *cfile)
अणु
	काष्ठा inode *inode = d_inode(cfile->dentry);
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cfile->tlink);
	काष्ठा file_lock *flock;
	काष्ठा file_lock_context *flctx = inode->i_flctx;
	अचिन्हित पूर्णांक count = 0, i;
	पूर्णांक rc = 0, xid, type;
	काष्ठा list_head locks_to_send, *el;
	काष्ठा lock_to_push *lck, *पंचांगp;
	__u64 length;

	xid = get_xid();

	अगर (!flctx)
		जाओ out;

	spin_lock(&flctx->flc_lock);
	list_क्रम_each(el, &flctx->flc_posix) अणु
		count++;
	पूर्ण
	spin_unlock(&flctx->flc_lock);

	INIT_LIST_HEAD(&locks_to_send);

	/*
	 * Allocating count locks is enough because no FL_POSIX locks can be
	 * added to the list जबतक we are holding cinode->lock_sem that
	 * protects locking operations of this inode.
	 */
	क्रम (i = 0; i < count; i++) अणु
		lck = kदो_स्मृति(माप(काष्ठा lock_to_push), GFP_KERNEL);
		अगर (!lck) अणु
			rc = -ENOMEM;
			जाओ err_out;
		पूर्ण
		list_add_tail(&lck->llist, &locks_to_send);
	पूर्ण

	el = locks_to_send.next;
	spin_lock(&flctx->flc_lock);
	list_क्रम_each_entry(flock, &flctx->flc_posix, fl_list) अणु
		अगर (el == &locks_to_send) अणु
			/*
			 * The list ended. We करोn't have enough allocated
			 * काष्ठाures - something is really wrong.
			 */
			cअगरs_dbg(VFS, "Can't push all brlocks!\n");
			अवरोध;
		पूर्ण
		length = 1 + flock->fl_end - flock->fl_start;
		अगर (flock->fl_type == F_RDLCK || flock->fl_type == F_SHLCK)
			type = CIFS_RDLCK;
		अन्यथा
			type = CIFS_WRLCK;
		lck = list_entry(el, काष्ठा lock_to_push, llist);
		lck->pid = hash_lockowner(flock->fl_owner);
		lck->netfid = cfile->fid.netfid;
		lck->length = length;
		lck->type = type;
		lck->offset = flock->fl_start;
	पूर्ण
	spin_unlock(&flctx->flc_lock);

	list_क्रम_each_entry_safe(lck, पंचांगp, &locks_to_send, llist) अणु
		पूर्णांक stored_rc;

		stored_rc = CIFSSMBPosixLock(xid, tcon, lck->netfid, lck->pid,
					     lck->offset, lck->length, शून्य,
					     lck->type, 0);
		अगर (stored_rc)
			rc = stored_rc;
		list_del(&lck->llist);
		kमुक्त(lck);
	पूर्ण

out:
	मुक्त_xid(xid);
	वापस rc;
err_out:
	list_क्रम_each_entry_safe(lck, पंचांगp, &locks_to_send, llist) अणु
		list_del(&lck->llist);
		kमुक्त(lck);
	पूर्ण
	जाओ out;
पूर्ण

अटल पूर्णांक
cअगरs_push_locks(काष्ठा cअगरsFileInfo *cfile)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(cfile->dentry->d_sb);
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cfile->tlink);
	पूर्णांक rc = 0;

	/* we are going to update can_cache_brlcks here - need a ग_लिखो access */
	cअगरs_करोwn_ग_लिखो(&cinode->lock_sem);
	अगर (!cinode->can_cache_brlcks) अणु
		up_ग_लिखो(&cinode->lock_sem);
		वापस rc;
	पूर्ण

	अगर (cap_unix(tcon->ses) &&
	    (CIFS_UNIX_FCNTL_CAP & le64_to_cpu(tcon->fsUnixInfo.Capability)) &&
	    ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NOPOSIXBRL) == 0))
		rc = cअगरs_push_posix_locks(cfile);
	अन्यथा
		rc = tcon->ses->server->ops->push_mand_locks(cfile);

	cinode->can_cache_brlcks = false;
	up_ग_लिखो(&cinode->lock_sem);
	वापस rc;
पूर्ण

अटल व्योम
cअगरs_पढ़ो_flock(काष्ठा file_lock *flock, __u32 *type, पूर्णांक *lock, पूर्णांक *unlock,
		bool *रुको_flag, काष्ठा TCP_Server_Info *server)
अणु
	अगर (flock->fl_flags & FL_POSIX)
		cअगरs_dbg(FYI, "Posix\n");
	अगर (flock->fl_flags & FL_FLOCK)
		cअगरs_dbg(FYI, "Flock\n");
	अगर (flock->fl_flags & FL_SLEEP) अणु
		cअगरs_dbg(FYI, "Blocking lock\n");
		*रुको_flag = true;
	पूर्ण
	अगर (flock->fl_flags & FL_ACCESS)
		cअगरs_dbg(FYI, "Process suspended by mandatory locking - not implemented yet\n");
	अगर (flock->fl_flags & FL_LEASE)
		cअगरs_dbg(FYI, "Lease on file - not implemented yet\n");
	अगर (flock->fl_flags &
	    (~(FL_POSIX | FL_FLOCK | FL_SLEEP |
	       FL_ACCESS | FL_LEASE | FL_CLOSE | FL_OFDLCK)))
		cअगरs_dbg(FYI, "Unknown lock flags 0x%x\n", flock->fl_flags);

	*type = server->vals->large_lock_type;
	अगर (flock->fl_type == F_WRLCK) अणु
		cअगरs_dbg(FYI, "F_WRLCK\n");
		*type |= server->vals->exclusive_lock_type;
		*lock = 1;
	पूर्ण अन्यथा अगर (flock->fl_type == F_UNLCK) अणु
		cअगरs_dbg(FYI, "F_UNLCK\n");
		*type |= server->vals->unlock_lock_type;
		*unlock = 1;
		/* Check अगर unlock includes more than one lock range */
	पूर्ण अन्यथा अगर (flock->fl_type == F_RDLCK) अणु
		cअगरs_dbg(FYI, "F_RDLCK\n");
		*type |= server->vals->shared_lock_type;
		*lock = 1;
	पूर्ण अन्यथा अगर (flock->fl_type == F_EXLCK) अणु
		cअगरs_dbg(FYI, "F_EXLCK\n");
		*type |= server->vals->exclusive_lock_type;
		*lock = 1;
	पूर्ण अन्यथा अगर (flock->fl_type == F_SHLCK) अणु
		cअगरs_dbg(FYI, "F_SHLCK\n");
		*type |= server->vals->shared_lock_type;
		*lock = 1;
	पूर्ण अन्यथा
		cअगरs_dbg(FYI, "Unknown type of lock\n");
पूर्ण

अटल पूर्णांक
cअगरs_getlk(काष्ठा file *file, काष्ठा file_lock *flock, __u32 type,
	   bool रुको_flag, bool posix_lck, अचिन्हित पूर्णांक xid)
अणु
	पूर्णांक rc = 0;
	__u64 length = 1 + flock->fl_end - flock->fl_start;
	काष्ठा cअगरsFileInfo *cfile = (काष्ठा cअगरsFileInfo *)file->निजी_data;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cfile->tlink);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	__u16 netfid = cfile->fid.netfid;

	अगर (posix_lck) अणु
		पूर्णांक posix_lock_type;

		rc = cअगरs_posix_lock_test(file, flock);
		अगर (!rc)
			वापस rc;

		अगर (type & server->vals->shared_lock_type)
			posix_lock_type = CIFS_RDLCK;
		अन्यथा
			posix_lock_type = CIFS_WRLCK;
		rc = CIFSSMBPosixLock(xid, tcon, netfid,
				      hash_lockowner(flock->fl_owner),
				      flock->fl_start, length, flock,
				      posix_lock_type, रुको_flag);
		वापस rc;
	पूर्ण

	rc = cअगरs_lock_test(cfile, flock->fl_start, length, type, flock);
	अगर (!rc)
		वापस rc;

	/* BB we could chain these पूर्णांकo one lock request BB */
	rc = server->ops->mand_lock(xid, cfile, flock->fl_start, length, type,
				    1, 0, false);
	अगर (rc == 0) अणु
		rc = server->ops->mand_lock(xid, cfile, flock->fl_start, length,
					    type, 0, 1, false);
		flock->fl_type = F_UNLCK;
		अगर (rc != 0)
			cअगरs_dbg(VFS, "Error unlocking previously locked range %d during test of lock\n",
				 rc);
		वापस 0;
	पूर्ण

	अगर (type & server->vals->shared_lock_type) अणु
		flock->fl_type = F_WRLCK;
		वापस 0;
	पूर्ण

	type &= ~server->vals->exclusive_lock_type;

	rc = server->ops->mand_lock(xid, cfile, flock->fl_start, length,
				    type | server->vals->shared_lock_type,
				    1, 0, false);
	अगर (rc == 0) अणु
		rc = server->ops->mand_lock(xid, cfile, flock->fl_start, length,
			type | server->vals->shared_lock_type, 0, 1, false);
		flock->fl_type = F_RDLCK;
		अगर (rc != 0)
			cअगरs_dbg(VFS, "Error unlocking previously locked range %d during test of lock\n",
				 rc);
	पूर्ण अन्यथा
		flock->fl_type = F_WRLCK;

	वापस 0;
पूर्ण

व्योम
cअगरs_move_llist(काष्ठा list_head *source, काष्ठा list_head *dest)
अणु
	काष्ठा list_head *li, *पंचांगp;
	list_क्रम_each_safe(li, पंचांगp, source)
		list_move(li, dest);
पूर्ण

व्योम
cअगरs_मुक्त_llist(काष्ठा list_head *llist)
अणु
	काष्ठा cअगरsLockInfo *li, *पंचांगp;
	list_क्रम_each_entry_safe(li, पंचांगp, llist, llist) अणु
		cअगरs_del_lock_रुकोers(li);
		list_del(&li->llist);
		kमुक्त(li);
	पूर्ण
पूर्ण

पूर्णांक
cअगरs_unlock_range(काष्ठा cअगरsFileInfo *cfile, काष्ठा file_lock *flock,
		  अचिन्हित पूर्णांक xid)
अणु
	पूर्णांक rc = 0, stored_rc;
	अटल स्थिर पूर्णांक types[] = अणु
		LOCKING_ANDX_LARGE_खाताS,
		LOCKING_ANDX_SHARED_LOCK | LOCKING_ANDX_LARGE_खाताS
	पूर्ण;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक max_num, num, max_buf;
	LOCKING_ANDX_RANGE *buf, *cur;
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
	अगर (max_buf < (माप(काष्ठा smb_hdr) + माप(LOCKING_ANDX_RANGE)))
		वापस -EINVAL;

	BUILD_BUG_ON(माप(काष्ठा smb_hdr) + माप(LOCKING_ANDX_RANGE) >
		     PAGE_SIZE);
	max_buf = min_t(अचिन्हित पूर्णांक, max_buf - माप(काष्ठा smb_hdr),
			PAGE_SIZE);
	max_num = (max_buf - माप(काष्ठा smb_hdr)) /
						माप(LOCKING_ANDX_RANGE);
	buf = kसुस्मृति(max_num, माप(LOCKING_ANDX_RANGE), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	cअगरs_करोwn_ग_लिखो(&cinode->lock_sem);
	क्रम (i = 0; i < 2; i++) अणु
		cur = buf;
		num = 0;
		list_क्रम_each_entry_safe(li, पंचांगp, &cfile->llist->locks, llist) अणु
			अगर (flock->fl_start > li->offset ||
			    (flock->fl_start + length) <
			    (li->offset + li->length))
				जारी;
			अगर (current->tgid != li->pid)
				जारी;
			अगर (types[i] != li->type)
				जारी;
			अगर (cinode->can_cache_brlcks) अणु
				/*
				 * We can cache brlock requests - simply हटाओ
				 * a lock from the file's list.
				 */
				list_del(&li->llist);
				cअगरs_del_lock_रुकोers(li);
				kमुक्त(li);
				जारी;
			पूर्ण
			cur->Pid = cpu_to_le16(li->pid);
			cur->LengthLow = cpu_to_le32((u32)li->length);
			cur->LengthHigh = cpu_to_le32((u32)(li->length>>32));
			cur->OffsetLow = cpu_to_le32((u32)li->offset);
			cur->OffsetHigh = cpu_to_le32((u32)(li->offset>>32));
			/*
			 * We need to save a lock here to let us add it again to
			 * the file's list अगर the unlock range request fails on
			 * the server.
			 */
			list_move(&li->llist, &पंचांगp_llist);
			अगर (++num == max_num) अणु
				stored_rc = cअगरs_lockv(xid, tcon,
						       cfile->fid.netfid,
						       li->type, num, 0, buf);
				अगर (stored_rc) अणु
					/*
					 * We failed on the unlock range
					 * request - add all locks from the पंचांगp
					 * list to the head of the file's list.
					 */
					cअगरs_move_llist(&पंचांगp_llist,
							&cfile->llist->locks);
					rc = stored_rc;
				पूर्ण अन्यथा
					/*
					 * The unlock range request succeed -
					 * मुक्त the पंचांगp list.
					 */
					cअगरs_मुक्त_llist(&पंचांगp_llist);
				cur = buf;
				num = 0;
			पूर्ण अन्यथा
				cur++;
		पूर्ण
		अगर (num) अणु
			stored_rc = cअगरs_lockv(xid, tcon, cfile->fid.netfid,
					       types[i], num, 0, buf);
			अगर (stored_rc) अणु
				cअगरs_move_llist(&पंचांगp_llist,
						&cfile->llist->locks);
				rc = stored_rc;
			पूर्ण अन्यथा
				cअगरs_मुक्त_llist(&पंचांगp_llist);
		पूर्ण
	पूर्ण

	up_ग_लिखो(&cinode->lock_sem);
	kमुक्त(buf);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_setlk(काष्ठा file *file, काष्ठा file_lock *flock, __u32 type,
	   bool रुको_flag, bool posix_lck, पूर्णांक lock, पूर्णांक unlock,
	   अचिन्हित पूर्णांक xid)
अणु
	पूर्णांक rc = 0;
	__u64 length = 1 + flock->fl_end - flock->fl_start;
	काष्ठा cअगरsFileInfo *cfile = (काष्ठा cअगरsFileInfo *)file->निजी_data;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cfile->tlink);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	काष्ठा inode *inode = d_inode(cfile->dentry);

	अगर (posix_lck) अणु
		पूर्णांक posix_lock_type;

		rc = cअगरs_posix_lock_set(file, flock);
		अगर (rc <= खाता_LOCK_DEFERRED)
			वापस rc;

		अगर (type & server->vals->shared_lock_type)
			posix_lock_type = CIFS_RDLCK;
		अन्यथा
			posix_lock_type = CIFS_WRLCK;

		अगर (unlock == 1)
			posix_lock_type = CIFS_UNLCK;

		rc = CIFSSMBPosixLock(xid, tcon, cfile->fid.netfid,
				      hash_lockowner(flock->fl_owner),
				      flock->fl_start, length,
				      शून्य, posix_lock_type, रुको_flag);
		जाओ out;
	पूर्ण

	अगर (lock) अणु
		काष्ठा cअगरsLockInfo *lock;

		lock = cअगरs_lock_init(flock->fl_start, length, type,
				      flock->fl_flags);
		अगर (!lock)
			वापस -ENOMEM;

		rc = cअगरs_lock_add_अगर(cfile, lock, रुको_flag);
		अगर (rc < 0) अणु
			kमुक्त(lock);
			वापस rc;
		पूर्ण
		अगर (!rc)
			जाओ out;

		/*
		 * Winकरोws 7 server can delay अवरोधing lease from पढ़ो to None
		 * अगर we set a byte-range lock on a file - अवरोध it explicitly
		 * beक्रमe sending the lock to the server to be sure the next
		 * पढ़ो won't conflict with non-overlapted locks due to
		 * pageपढ़ोing.
		 */
		अगर (!CIFS_CACHE_WRITE(CIFS_I(inode)) &&
					CIFS_CACHE_READ(CIFS_I(inode))) अणु
			cअगरs_zap_mapping(inode);
			cअगरs_dbg(FYI, "Set no oplock for inode=%p due to mand locks\n",
				 inode);
			CIFS_I(inode)->oplock = 0;
		पूर्ण

		rc = server->ops->mand_lock(xid, cfile, flock->fl_start, length,
					    type, 1, 0, रुको_flag);
		अगर (rc) अणु
			kमुक्त(lock);
			वापस rc;
		पूर्ण

		cअगरs_lock_add(cfile, lock);
	पूर्ण अन्यथा अगर (unlock)
		rc = server->ops->mand_unlock_range(cfile, flock, xid);

out:
	अगर ((flock->fl_flags & FL_POSIX) || (flock->fl_flags & FL_FLOCK)) अणु
		/*
		 * If this is a request to हटाओ all locks because we
		 * are closing the file, it करोesn't matter अगर the
		 * unlocking failed as both cअगरs.ko and the SMB server
		 * हटाओ the lock on file बंद
		 */
		अगर (rc) अणु
			cअगरs_dbg(VFS, "%s failed rc=%d\n", __func__, rc);
			अगर (!(flock->fl_flags & FL_CLOSE))
				वापस rc;
		पूर्ण
		rc = locks_lock_file_रुको(file, flock);
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक cअगरs_flock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	पूर्णांक rc, xid;
	पूर्णांक lock = 0, unlock = 0;
	bool रुको_flag = false;
	bool posix_lck = false;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरsFileInfo *cfile;
	__u32 type;

	rc = -EACCES;
	xid = get_xid();

	अगर (!(fl->fl_flags & FL_FLOCK))
		वापस -ENOLCK;

	cfile = (काष्ठा cअगरsFileInfo *)file->निजी_data;
	tcon = tlink_tcon(cfile->tlink);

	cअगरs_पढ़ो_flock(fl, &type, &lock, &unlock, &रुको_flag,
			tcon->ses->server);
	cअगरs_sb = CIFS_खाता_SB(file);

	अगर (cap_unix(tcon->ses) &&
	    (CIFS_UNIX_FCNTL_CAP & le64_to_cpu(tcon->fsUnixInfo.Capability)) &&
	    ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NOPOSIXBRL) == 0))
		posix_lck = true;

	अगर (!lock && !unlock) अणु
		/*
		 * अगर no lock or unlock then nothing to करो since we करो not
		 * know what it is
		 */
		मुक्त_xid(xid);
		वापस -EOPNOTSUPP;
	पूर्ण

	rc = cअगरs_setlk(file, fl, type, रुको_flag, posix_lck, lock, unlock,
			xid);
	मुक्त_xid(xid);
	वापस rc;


पूर्ण

पूर्णांक cअगरs_lock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *flock)
अणु
	पूर्णांक rc, xid;
	पूर्णांक lock = 0, unlock = 0;
	bool रुको_flag = false;
	bool posix_lck = false;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरsFileInfo *cfile;
	__u32 type;

	rc = -EACCES;
	xid = get_xid();

	cअगरs_dbg(FYI, "Lock parm: 0x%x flockflags: 0x%x flocktype: 0x%x start: %lld end: %lld\n",
		 cmd, flock->fl_flags, flock->fl_type,
		 flock->fl_start, flock->fl_end);

	cfile = (काष्ठा cअगरsFileInfo *)file->निजी_data;
	tcon = tlink_tcon(cfile->tlink);

	cअगरs_पढ़ो_flock(flock, &type, &lock, &unlock, &रुको_flag,
			tcon->ses->server);
	cअगरs_sb = CIFS_खाता_SB(file);

	अगर (cap_unix(tcon->ses) &&
	    (CIFS_UNIX_FCNTL_CAP & le64_to_cpu(tcon->fsUnixInfo.Capability)) &&
	    ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NOPOSIXBRL) == 0))
		posix_lck = true;
	/*
	 * BB add code here to normalize offset and length to account क्रम
	 * negative length which we can not accept over the wire.
	 */
	अगर (IS_GETLK(cmd)) अणु
		rc = cअगरs_getlk(file, flock, type, रुको_flag, posix_lck, xid);
		मुक्त_xid(xid);
		वापस rc;
	पूर्ण

	अगर (!lock && !unlock) अणु
		/*
		 * अगर no lock or unlock then nothing to करो since we करो not
		 * know what it is
		 */
		मुक्त_xid(xid);
		वापस -EOPNOTSUPP;
	पूर्ण

	rc = cअगरs_setlk(file, flock, type, रुको_flag, posix_lck, lock, unlock,
			xid);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

/*
 * update the file size (अगर needed) after a ग_लिखो. Should be called with
 * the inode->i_lock held
 */
व्योम
cअगरs_update_eof(काष्ठा cअगरsInodeInfo *cअगरsi, loff_t offset,
		      अचिन्हित पूर्णांक bytes_written)
अणु
	loff_t end_of_ग_लिखो = offset + bytes_written;

	अगर (end_of_ग_लिखो > cअगरsi->server_eof)
		cअगरsi->server_eof = end_of_ग_लिखो;
पूर्ण

अटल sमाप_प्रकार
cअगरs_ग_लिखो(काष्ठा cअगरsFileInfo *खोलो_file, __u32 pid, स्थिर अक्षर *ग_लिखो_data,
	   माप_प्रकार ग_लिखो_size, loff_t *offset)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक bytes_written = 0;
	अचिन्हित पूर्णांक total_written;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	अचिन्हित पूर्णांक xid;
	काष्ठा dentry *dentry = खोलो_file->dentry;
	काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(d_inode(dentry));
	काष्ठा cअगरs_io_parms io_parms = अणु0पूर्ण;

	cअगरs_dbg(FYI, "write %zd bytes to offset %lld of %pd\n",
		 ग_लिखो_size, *offset, dentry);

	tcon = tlink_tcon(खोलो_file->tlink);
	server = tcon->ses->server;

	अगर (!server->ops->sync_ग_लिखो)
		वापस -ENOSYS;

	xid = get_xid();

	क्रम (total_written = 0; ग_लिखो_size > total_written;
	     total_written += bytes_written) अणु
		rc = -EAGAIN;
		जबतक (rc == -EAGAIN) अणु
			काष्ठा kvec iov[2];
			अचिन्हित पूर्णांक len;

			अगर (खोलो_file->invalidHandle) अणु
				/* we could deadlock अगर we called
				   filemap_fdataरुको from here so tell
				   reखोलो_file not to flush data to
				   server now */
				rc = cअगरs_reखोलो_file(खोलो_file, false);
				अगर (rc != 0)
					अवरोध;
			पूर्ण

			len = min(server->ops->wp_retry_size(d_inode(dentry)),
				  (अचिन्हित पूर्णांक)ग_लिखो_size - total_written);
			/* iov[0] is reserved क्रम smb header */
			iov[1].iov_base = (अक्षर *)ग_लिखो_data + total_written;
			iov[1].iov_len = len;
			io_parms.pid = pid;
			io_parms.tcon = tcon;
			io_parms.offset = *offset;
			io_parms.length = len;
			rc = server->ops->sync_ग_लिखो(xid, &खोलो_file->fid,
					&io_parms, &bytes_written, iov, 1);
		पूर्ण
		अगर (rc || (bytes_written == 0)) अणु
			अगर (total_written)
				अवरोध;
			अन्यथा अणु
				मुक्त_xid(xid);
				वापस rc;
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_lock(&d_inode(dentry)->i_lock);
			cअगरs_update_eof(cअगरsi, *offset, bytes_written);
			spin_unlock(&d_inode(dentry)->i_lock);
			*offset += bytes_written;
		पूर्ण
	पूर्ण

	cअगरs_stats_bytes_written(tcon, total_written);

	अगर (total_written > 0) अणु
		spin_lock(&d_inode(dentry)->i_lock);
		अगर (*offset > d_inode(dentry)->i_size) अणु
			i_size_ग_लिखो(d_inode(dentry), *offset);
			d_inode(dentry)->i_blocks = (512 - 1 + *offset) >> 9;
		पूर्ण
		spin_unlock(&d_inode(dentry)->i_lock);
	पूर्ण
	mark_inode_dirty_sync(d_inode(dentry));
	मुक्त_xid(xid);
	वापस total_written;
पूर्ण

काष्ठा cअगरsFileInfo *find_पढ़ोable_file(काष्ठा cअगरsInodeInfo *cअगरs_inode,
					bool fsuid_only)
अणु
	काष्ठा cअगरsFileInfo *खोलो_file = शून्य;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(cअगरs_inode->vfs_inode.i_sb);

	/* only filter by fsuid on multiuser mounts */
	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MULTIUSER))
		fsuid_only = false;

	spin_lock(&cअगरs_inode->खोलो_file_lock);
	/* we could simply get the first_list_entry since ग_लिखो-only entries
	   are always at the end of the list but since the first entry might
	   have a बंद pending, we go through the whole list */
	list_क्रम_each_entry(खोलो_file, &cअगरs_inode->खोलोFileList, flist) अणु
		अगर (fsuid_only && !uid_eq(खोलो_file->uid, current_fsuid()))
			जारी;
		अगर (OPEN_FMODE(खोलो_file->f_flags) & FMODE_READ) अणु
			अगर ((!खोलो_file->invalidHandle)) अणु
				/* found a good file */
				/* lock it so it will not be बंदd on us */
				cअगरsFileInfo_get(खोलो_file);
				spin_unlock(&cअगरs_inode->खोलो_file_lock);
				वापस खोलो_file;
			पूर्ण /* अन्यथा might as well जारी, and look क्रम
			     another, or simply have the caller reखोलो it
			     again rather than trying to fix this handle */
		पूर्ण अन्यथा /* ग_लिखो only file */
			अवरोध; /* ग_लिखो only files are last so must be करोne */
	पूर्ण
	spin_unlock(&cअगरs_inode->खोलो_file_lock);
	वापस शून्य;
पूर्ण

/* Return -EBADF अगर no handle is found and general rc otherwise */
पूर्णांक
cअगरs_get_writable_file(काष्ठा cअगरsInodeInfo *cअगरs_inode, पूर्णांक flags,
		       काष्ठा cअगरsFileInfo **ret_file)
अणु
	काष्ठा cअगरsFileInfo *खोलो_file, *inv_file = शून्य;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	bool any_available = false;
	पूर्णांक rc = -EBADF;
	अचिन्हित पूर्णांक refind = 0;
	bool fsuid_only = flags & FIND_WR_FSUID_ONLY;
	bool with_delete = flags & FIND_WR_WITH_DELETE;
	*ret_file = शून्य;

	/*
	 * Having a null inode here (because mapping->host was set to zero by
	 * the VFS or MM) should not happen but we had reports of on oops (due
	 * to it being zero) during stress testहालs so we need to check क्रम it
	 */

	अगर (cअगरs_inode == शून्य) अणु
		cअगरs_dbg(VFS, "Null inode passed to cifs_writeable_file\n");
		dump_stack();
		वापस rc;
	पूर्ण

	cअगरs_sb = CIFS_SB(cअगरs_inode->vfs_inode.i_sb);

	/* only filter by fsuid on multiuser mounts */
	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MULTIUSER))
		fsuid_only = false;

	spin_lock(&cअगरs_inode->खोलो_file_lock);
refind_writable:
	अगर (refind > MAX_REOPEN_ATT) अणु
		spin_unlock(&cअगरs_inode->खोलो_file_lock);
		वापस rc;
	पूर्ण
	list_क्रम_each_entry(खोलो_file, &cअगरs_inode->खोलोFileList, flist) अणु
		अगर (!any_available && खोलो_file->pid != current->tgid)
			जारी;
		अगर (fsuid_only && !uid_eq(खोलो_file->uid, current_fsuid()))
			जारी;
		अगर (with_delete && !(खोलो_file->fid.access & DELETE))
			जारी;
		अगर (OPEN_FMODE(खोलो_file->f_flags) & FMODE_WRITE) अणु
			अगर (!खोलो_file->invalidHandle) अणु
				/* found a good writable file */
				cअगरsFileInfo_get(खोलो_file);
				spin_unlock(&cअगरs_inode->खोलो_file_lock);
				*ret_file = खोलो_file;
				वापस 0;
			पूर्ण अन्यथा अणु
				अगर (!inv_file)
					inv_file = खोलो_file;
			पूर्ण
		पूर्ण
	पूर्ण
	/* couldn't find useable FH with same pid, try any available */
	अगर (!any_available) अणु
		any_available = true;
		जाओ refind_writable;
	पूर्ण

	अगर (inv_file) अणु
		any_available = false;
		cअगरsFileInfo_get(inv_file);
	पूर्ण

	spin_unlock(&cअगरs_inode->खोलो_file_lock);

	अगर (inv_file) अणु
		rc = cअगरs_reखोलो_file(inv_file, false);
		अगर (!rc) अणु
			*ret_file = inv_file;
			वापस 0;
		पूर्ण

		spin_lock(&cअगरs_inode->खोलो_file_lock);
		list_move_tail(&inv_file->flist, &cअगरs_inode->खोलोFileList);
		spin_unlock(&cअगरs_inode->खोलो_file_lock);
		cअगरsFileInfo_put(inv_file);
		++refind;
		inv_file = शून्य;
		spin_lock(&cअगरs_inode->खोलो_file_lock);
		जाओ refind_writable;
	पूर्ण

	वापस rc;
पूर्ण

काष्ठा cअगरsFileInfo *
find_writable_file(काष्ठा cअगरsInodeInfo *cअगरs_inode, पूर्णांक flags)
अणु
	काष्ठा cअगरsFileInfo *cfile;
	पूर्णांक rc;

	rc = cअगरs_get_writable_file(cअगरs_inode, flags, &cfile);
	अगर (rc)
		cअगरs_dbg(FYI, "Couldn't find writable handle rc=%d\n", rc);

	वापस cfile;
पूर्ण

पूर्णांक
cअगरs_get_writable_path(काष्ठा cअगरs_tcon *tcon, स्थिर अक्षर *name,
		       पूर्णांक flags,
		       काष्ठा cअगरsFileInfo **ret_file)
अणु
	काष्ठा cअगरsFileInfo *cfile;
	व्योम *page = alloc_dentry_path();

	*ret_file = शून्य;

	spin_lock(&tcon->खोलो_file_lock);
	list_क्रम_each_entry(cfile, &tcon->खोलोFileList, tlist) अणु
		काष्ठा cअगरsInodeInfo *cinode;
		स्थिर अक्षर *full_path = build_path_from_dentry(cfile->dentry, page);
		अगर (IS_ERR(full_path)) अणु
			spin_unlock(&tcon->खोलो_file_lock);
			मुक्त_dentry_path(page);
			वापस PTR_ERR(full_path);
		पूर्ण
		अगर (म_भेद(full_path, name))
			जारी;

		cinode = CIFS_I(d_inode(cfile->dentry));
		spin_unlock(&tcon->खोलो_file_lock);
		मुक्त_dentry_path(page);
		वापस cअगरs_get_writable_file(cinode, flags, ret_file);
	पूर्ण

	spin_unlock(&tcon->खोलो_file_lock);
	मुक्त_dentry_path(page);
	वापस -ENOENT;
पूर्ण

पूर्णांक
cअगरs_get_पढ़ोable_path(काष्ठा cअगरs_tcon *tcon, स्थिर अक्षर *name,
		       काष्ठा cअगरsFileInfo **ret_file)
अणु
	काष्ठा cअगरsFileInfo *cfile;
	व्योम *page = alloc_dentry_path();

	*ret_file = शून्य;

	spin_lock(&tcon->खोलो_file_lock);
	list_क्रम_each_entry(cfile, &tcon->खोलोFileList, tlist) अणु
		काष्ठा cअगरsInodeInfo *cinode;
		स्थिर अक्षर *full_path = build_path_from_dentry(cfile->dentry, page);
		अगर (IS_ERR(full_path)) अणु
			spin_unlock(&tcon->खोलो_file_lock);
			मुक्त_dentry_path(page);
			वापस PTR_ERR(full_path);
		पूर्ण
		अगर (म_भेद(full_path, name))
			जारी;

		cinode = CIFS_I(d_inode(cfile->dentry));
		spin_unlock(&tcon->खोलो_file_lock);
		मुक्त_dentry_path(page);
		*ret_file = find_पढ़ोable_file(cinode, 0);
		वापस *ret_file ? 0 : -ENOENT;
	पूर्ण

	spin_unlock(&tcon->खोलो_file_lock);
	मुक्त_dentry_path(page);
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक cअगरs_partialpageग_लिखो(काष्ठा page *page, अचिन्हित from, अचिन्हित to)
अणु
	काष्ठा address_space *mapping = page->mapping;
	loff_t offset = (loff_t)page->index << PAGE_SHIFT;
	अक्षर *ग_लिखो_data;
	पूर्णांक rc = -EFAULT;
	पूर्णांक bytes_written = 0;
	काष्ठा inode *inode;
	काष्ठा cअगरsFileInfo *खोलो_file;

	अगर (!mapping || !mapping->host)
		वापस -EFAULT;

	inode = page->mapping->host;

	offset += (loff_t)from;
	ग_लिखो_data = kmap(page);
	ग_लिखो_data += from;

	अगर ((to > PAGE_SIZE) || (from > to)) अणु
		kunmap(page);
		वापस -EIO;
	पूर्ण

	/* racing with truncate? */
	अगर (offset > mapping->host->i_size) अणु
		kunmap(page);
		वापस 0; /* करोn't care */
	पूर्ण

	/* check to make sure that we are not extending the file */
	अगर (mapping->host->i_size - offset < (loff_t)to)
		to = (अचिन्हित)(mapping->host->i_size - offset);

	rc = cअगरs_get_writable_file(CIFS_I(mapping->host), FIND_WR_ANY,
				    &खोलो_file);
	अगर (!rc) अणु
		bytes_written = cअगरs_ग_लिखो(खोलो_file, खोलो_file->pid,
					   ग_लिखो_data, to - from, &offset);
		cअगरsFileInfo_put(खोलो_file);
		/* Does mm or vfs alपढ़ोy set बार? */
		inode->i_aसमय = inode->i_mसमय = current_समय(inode);
		अगर ((bytes_written > 0) && (offset))
			rc = 0;
		अन्यथा अगर (bytes_written < 0)
			rc = bytes_written;
		अन्यथा
			rc = -EFAULT;
	पूर्ण अन्यथा अणु
		cअगरs_dbg(FYI, "No writable handle for write page rc=%d\n", rc);
		अगर (!is_retryable_error(rc))
			rc = -EIO;
	पूर्ण

	kunmap(page);
	वापस rc;
पूर्ण

अटल काष्ठा cअगरs_ग_लिखोdata *
wdata_alloc_and_fillpages(pgoff_t tofind, काष्ठा address_space *mapping,
			  pgoff_t end, pgoff_t *index,
			  अचिन्हित पूर्णांक *found_pages)
अणु
	काष्ठा cअगरs_ग_लिखोdata *wdata;

	wdata = cअगरs_ग_लिखोdata_alloc((अचिन्हित पूर्णांक)tofind,
				     cअगरs_ग_लिखोv_complete);
	अगर (!wdata)
		वापस शून्य;

	*found_pages = find_get_pages_range_tag(mapping, index, end,
				PAGECACHE_TAG_सूचीTY, tofind, wdata->pages);
	वापस wdata;
पूर्ण

अटल अचिन्हित पूर्णांक
wdata_prepare_pages(काष्ठा cअगरs_ग_लिखोdata *wdata, अचिन्हित पूर्णांक found_pages,
		    काष्ठा address_space *mapping,
		    काष्ठा ग_लिखोback_control *wbc,
		    pgoff_t end, pgoff_t *index, pgoff_t *next, bool *करोne)
अणु
	अचिन्हित पूर्णांक nr_pages = 0, i;
	काष्ठा page *page;

	क्रम (i = 0; i < found_pages; i++) अणु
		page = wdata->pages[i];
		/*
		 * At this poपूर्णांक we hold neither the i_pages lock nor the
		 * page lock: the page may be truncated or invalidated
		 * (changing page->mapping to शून्य), or even swizzled
		 * back from swapper_space to पंचांगpfs file mapping
		 */

		अगर (nr_pages == 0)
			lock_page(page);
		अन्यथा अगर (!trylock_page(page))
			अवरोध;

		अगर (unlikely(page->mapping != mapping)) अणु
			unlock_page(page);
			अवरोध;
		पूर्ण

		अगर (!wbc->range_cyclic && page->index > end) अणु
			*करोne = true;
			unlock_page(page);
			अवरोध;
		पूर्ण

		अगर (*next && (page->index != *next)) अणु
			/* Not next consecutive page */
			unlock_page(page);
			अवरोध;
		पूर्ण

		अगर (wbc->sync_mode != WB_SYNC_NONE)
			रुको_on_page_ग_लिखोback(page);

		अगर (PageWriteback(page) ||
				!clear_page_dirty_क्रम_io(page)) अणु
			unlock_page(page);
			अवरोध;
		पूर्ण

		/*
		 * This actually clears the dirty bit in the radix tree.
		 * See cअगरs_ग_लिखोpage() क्रम more commentary.
		 */
		set_page_ग_लिखोback(page);
		अगर (page_offset(page) >= i_size_पढ़ो(mapping->host)) अणु
			*करोne = true;
			unlock_page(page);
			end_page_ग_लिखोback(page);
			अवरोध;
		पूर्ण

		wdata->pages[i] = page;
		*next = page->index + 1;
		++nr_pages;
	पूर्ण

	/* reset index to refind any pages skipped */
	अगर (nr_pages == 0)
		*index = wdata->pages[0]->index + 1;

	/* put any pages we aren't going to use */
	क्रम (i = nr_pages; i < found_pages; i++) अणु
		put_page(wdata->pages[i]);
		wdata->pages[i] = शून्य;
	पूर्ण

	वापस nr_pages;
पूर्ण

अटल पूर्णांक
wdata_send_pages(काष्ठा cअगरs_ग_लिखोdata *wdata, अचिन्हित पूर्णांक nr_pages,
		 काष्ठा address_space *mapping, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक rc;

	wdata->sync_mode = wbc->sync_mode;
	wdata->nr_pages = nr_pages;
	wdata->offset = page_offset(wdata->pages[0]);
	wdata->pagesz = PAGE_SIZE;
	wdata->tailsz = min(i_size_पढ़ो(mapping->host) -
			page_offset(wdata->pages[nr_pages - 1]),
			(loff_t)PAGE_SIZE);
	wdata->bytes = ((nr_pages - 1) * PAGE_SIZE) + wdata->tailsz;
	wdata->pid = wdata->cfile->pid;

	rc = adjust_credits(wdata->server, &wdata->credits, wdata->bytes);
	अगर (rc)
		वापस rc;

	अगर (wdata->cfile->invalidHandle)
		rc = -EAGAIN;
	अन्यथा
		rc = wdata->server->ops->async_ग_लिखोv(wdata,
						      cअगरs_ग_लिखोdata_release);

	वापस rc;
पूर्ण

अटल पूर्णांक cअगरs_ग_लिखोpages(काष्ठा address_space *mapping,
			   काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा TCP_Server_Info *server;
	bool करोne = false, scanned = false, range_whole = false;
	pgoff_t end, index;
	काष्ठा cअगरs_ग_लिखोdata *wdata;
	काष्ठा cअगरsFileInfo *cfile = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक saved_rc = 0;
	अचिन्हित पूर्णांक xid;

	/*
	 * If wsize is smaller than the page cache size, शेष to writing
	 * one page at a समय via cअगरs_ग_लिखोpage
	 */
	अगर (cअगरs_sb->ctx->wsize < PAGE_SIZE)
		वापस generic_ग_लिखोpages(mapping, wbc);

	xid = get_xid();
	अगर (wbc->range_cyclic) अणु
		index = mapping->ग_लिखोback_index; /* Start from prev offset */
		end = -1;
	पूर्ण अन्यथा अणु
		index = wbc->range_start >> PAGE_SHIFT;
		end = wbc->range_end >> PAGE_SHIFT;
		अगर (wbc->range_start == 0 && wbc->range_end == Lदीर्घ_उच्च)
			range_whole = true;
		scanned = true;
	पूर्ण
	server = cअगरs_pick_channel(cअगरs_sb_master_tcon(cअगरs_sb)->ses);

retry:
	जबतक (!करोne && index <= end) अणु
		अचिन्हित पूर्णांक i, nr_pages, found_pages, wsize;
		pgoff_t next = 0, tofind, saved_index = index;
		काष्ठा cअगरs_credits credits_on_stack;
		काष्ठा cअगरs_credits *credits = &credits_on_stack;
		पूर्णांक get_file_rc = 0;

		अगर (cfile)
			cअगरsFileInfo_put(cfile);

		rc = cअगरs_get_writable_file(CIFS_I(inode), FIND_WR_ANY, &cfile);

		/* in हाल of an error store it to वापस later */
		अगर (rc)
			get_file_rc = rc;

		rc = server->ops->रुको_mtu_credits(server, cअगरs_sb->ctx->wsize,
						   &wsize, credits);
		अगर (rc != 0) अणु
			करोne = true;
			अवरोध;
		पूर्ण

		tofind = min((wsize / PAGE_SIZE) - 1, end - index) + 1;

		wdata = wdata_alloc_and_fillpages(tofind, mapping, end, &index,
						  &found_pages);
		अगर (!wdata) अणु
			rc = -ENOMEM;
			करोne = true;
			add_credits_and_wake_अगर(server, credits, 0);
			अवरोध;
		पूर्ण

		अगर (found_pages == 0) अणु
			kref_put(&wdata->refcount, cअगरs_ग_लिखोdata_release);
			add_credits_and_wake_अगर(server, credits, 0);
			अवरोध;
		पूर्ण

		nr_pages = wdata_prepare_pages(wdata, found_pages, mapping, wbc,
					       end, &index, &next, &करोne);

		/* nothing to ग_लिखो? */
		अगर (nr_pages == 0) अणु
			kref_put(&wdata->refcount, cअगरs_ग_लिखोdata_release);
			add_credits_and_wake_अगर(server, credits, 0);
			जारी;
		पूर्ण

		wdata->credits = credits_on_stack;
		wdata->cfile = cfile;
		wdata->server = server;
		cfile = शून्य;

		अगर (!wdata->cfile) अणु
			cअगरs_dbg(VFS, "No writable handle in writepages rc=%d\n",
				 get_file_rc);
			अगर (is_retryable_error(get_file_rc))
				rc = get_file_rc;
			अन्यथा
				rc = -EBADF;
		पूर्ण अन्यथा
			rc = wdata_send_pages(wdata, nr_pages, mapping, wbc);

		क्रम (i = 0; i < nr_pages; ++i)
			unlock_page(wdata->pages[i]);

		/* send failure -- clean up the mess */
		अगर (rc != 0) अणु
			add_credits_and_wake_अगर(server, &wdata->credits, 0);
			क्रम (i = 0; i < nr_pages; ++i) अणु
				अगर (is_retryable_error(rc))
					redirty_page_क्रम_ग_लिखोpage(wbc,
							   wdata->pages[i]);
				अन्यथा
					SetPageError(wdata->pages[i]);
				end_page_ग_लिखोback(wdata->pages[i]);
				put_page(wdata->pages[i]);
			पूर्ण
			अगर (!is_retryable_error(rc))
				mapping_set_error(mapping, rc);
		पूर्ण
		kref_put(&wdata->refcount, cअगरs_ग_लिखोdata_release);

		अगर (wbc->sync_mode == WB_SYNC_ALL && rc == -EAGAIN) अणु
			index = saved_index;
			जारी;
		पूर्ण

		/* Return immediately अगर we received a संकेत during writing */
		अगर (is_पूर्णांकerrupt_error(rc)) अणु
			करोne = true;
			अवरोध;
		पूर्ण

		अगर (rc != 0 && saved_rc == 0)
			saved_rc = rc;

		wbc->nr_to_ग_लिखो -= nr_pages;
		अगर (wbc->nr_to_ग_लिखो <= 0)
			करोne = true;

		index = next;
	पूर्ण

	अगर (!scanned && !करोne) अणु
		/*
		 * We hit the last page and there is more work to be करोne: wrap
		 * back to the start of the file
		 */
		scanned = true;
		index = 0;
		जाओ retry;
	पूर्ण

	अगर (saved_rc != 0)
		rc = saved_rc;

	अगर (wbc->range_cyclic || (range_whole && wbc->nr_to_ग_लिखो > 0))
		mapping->ग_लिखोback_index = index;

	अगर (cfile)
		cअगरsFileInfo_put(cfile);
	मुक्त_xid(xid);
	/* Indication to update स_समय and mसमय as बंद is deferred */
	set_bit(CIFS_INO_MODIFIED_ATTR, &CIFS_I(inode)->flags);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_ग_लिखोpage_locked(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक xid;

	xid = get_xid();
/* BB add check क्रम wbc flags */
	get_page(page);
	अगर (!PageUptodate(page))
		cअगरs_dbg(FYI, "ppw - page not up to date\n");

	/*
	 * Set the "writeback" flag, and clear "dirty" in the radix tree.
	 *
	 * A ग_लिखोpage() implementation always needs to करो either this,
	 * or re-dirty the page with "redirty_page_for_writepage()" in
	 * the हाल of a failure.
	 *
	 * Just unlocking the page will cause the radix tree tag-bits
	 * to fail to update with the state of the page correctly.
	 */
	set_page_ग_लिखोback(page);
retry_ग_लिखो:
	rc = cअगरs_partialpageग_लिखो(page, 0, PAGE_SIZE);
	अगर (is_retryable_error(rc)) अणु
		अगर (wbc->sync_mode == WB_SYNC_ALL && rc == -EAGAIN)
			जाओ retry_ग_लिखो;
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
	पूर्ण अन्यथा अगर (rc != 0) अणु
		SetPageError(page);
		mapping_set_error(page->mapping, rc);
	पूर्ण अन्यथा अणु
		SetPageUptodate(page);
	पूर्ण
	end_page_ग_लिखोback(page);
	put_page(page);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल पूर्णांक cअगरs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक rc = cअगरs_ग_लिखोpage_locked(page, wbc);
	unlock_page(page);
	वापस rc;
पूर्ण

अटल पूर्णांक cअगरs_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	पूर्णांक rc;
	काष्ठा inode *inode = mapping->host;
	काष्ठा cअगरsFileInfo *cfile = file->निजी_data;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(cfile->dentry->d_sb);
	__u32 pid;

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_RWPIDFORWARD)
		pid = cfile->pid;
	अन्यथा
		pid = current->tgid;

	cअगरs_dbg(FYI, "write_end for page %p from pos %lld with %d bytes\n",
		 page, pos, copied);

	अगर (PageChecked(page)) अणु
		अगर (copied == len)
			SetPageUptodate(page);
		ClearPageChecked(page);
	पूर्ण अन्यथा अगर (!PageUptodate(page) && copied == PAGE_SIZE)
		SetPageUptodate(page);

	अगर (!PageUptodate(page)) अणु
		अक्षर *page_data;
		अचिन्हित offset = pos & (PAGE_SIZE - 1);
		अचिन्हित पूर्णांक xid;

		xid = get_xid();
		/* this is probably better than directly calling
		   partialpage_ग_लिखो since in this function the file handle is
		   known which we might as well	leverage */
		/* BB check अगर anything अन्यथा missing out of ppw
		   such as updating last ग_लिखो समय */
		page_data = kmap(page);
		rc = cअगरs_ग_लिखो(cfile, pid, page_data + offset, copied, &pos);
		/* अगर (rc < 0) should we set ग_लिखोbehind rc? */
		kunmap(page);

		मुक्त_xid(xid);
	पूर्ण अन्यथा अणु
		rc = copied;
		pos += copied;
		set_page_dirty(page);
	पूर्ण

	अगर (rc > 0) अणु
		spin_lock(&inode->i_lock);
		अगर (pos > inode->i_size) अणु
			i_size_ग_लिखो(inode, pos);
			inode->i_blocks = (512 - 1 + pos) >> 9;
		पूर्ण
		spin_unlock(&inode->i_lock);
	पूर्ण

	unlock_page(page);
	put_page(page);
	/* Indication to update स_समय and mसमय as बंद is deferred */
	set_bit(CIFS_INO_MODIFIED_ATTR, &CIFS_I(inode)->flags);

	वापस rc;
पूर्ण

पूर्णांक cअगरs_strict_fsync(काष्ठा file *file, loff_t start, loff_t end,
		      पूर्णांक datasync)
अणु
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc = 0;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरsFileInfo *smbfile = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);

	rc = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (rc) अणु
		trace_cअगरs_fsync_err(inode->i_ino, rc);
		वापस rc;
	पूर्ण

	xid = get_xid();

	cअगरs_dbg(FYI, "Sync file - name: %pD datasync: 0x%x\n",
		 file, datasync);

	अगर (!CIFS_CACHE_READ(CIFS_I(inode))) अणु
		rc = cअगरs_zap_mapping(inode);
		अगर (rc) अणु
			cअगरs_dbg(FYI, "rc: %d during invalidate phase\n", rc);
			rc = 0; /* करोn't care about it in fsync */
		पूर्ण
	पूर्ण

	tcon = tlink_tcon(smbfile->tlink);
	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NOSSYNC)) अणु
		server = tcon->ses->server;
		अगर (server->ops->flush)
			rc = server->ops->flush(xid, tcon, &smbfile->fid);
		अन्यथा
			rc = -ENOSYS;
	पूर्ण

	मुक्त_xid(xid);
	वापस rc;
पूर्ण

पूर्णांक cअगरs_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc = 0;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरsFileInfo *smbfile = file->निजी_data;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_खाता_SB(file);

	rc = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (rc) अणु
		trace_cअगरs_fsync_err(file_inode(file)->i_ino, rc);
		वापस rc;
	पूर्ण

	xid = get_xid();

	cअगरs_dbg(FYI, "Sync file - name: %pD datasync: 0x%x\n",
		 file, datasync);

	tcon = tlink_tcon(smbfile->tlink);
	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NOSSYNC)) अणु
		server = tcon->ses->server;
		अगर (server->ops->flush)
			rc = server->ops->flush(xid, tcon, &smbfile->fid);
		अन्यथा
			rc = -ENOSYS;
	पूर्ण

	मुक्त_xid(xid);
	वापस rc;
पूर्ण

/*
 * As file बंदs, flush all cached ग_लिखो data क्रम this inode checking
 * क्रम ग_लिखो behind errors.
 */
पूर्णांक cअगरs_flush(काष्ठा file *file, fl_owner_t id)
अणु
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक rc = 0;

	अगर (file->f_mode & FMODE_WRITE)
		rc = filemap_ग_लिखो_and_रुको(inode->i_mapping);

	cअगरs_dbg(FYI, "Flush inode %p file %p rc %d\n", inode, file, rc);
	अगर (rc)
		trace_cअगरs_flush_err(inode->i_ino, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_ग_लिखो_allocate_pages(काष्ठा page **pages, अचिन्हित दीर्घ num_pages)
अणु
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < num_pages; i++) अणु
		pages[i] = alloc_page(GFP_KERNEL|__GFP_HIGHMEM);
		अगर (!pages[i]) अणु
			/*
			 * save number of pages we have alपढ़ोy allocated and
			 * वापस with ENOMEM error
			 */
			num_pages = i;
			rc = -ENOMEM;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rc) अणु
		क्रम (i = 0; i < num_pages; i++)
			put_page(pages[i]);
	पूर्ण
	वापस rc;
पूर्ण

अटल अंतरभूत
माप_प्रकार get_numpages(स्थिर माप_प्रकार wsize, स्थिर माप_प्रकार len, माप_प्रकार *cur_len)
अणु
	माप_प्रकार num_pages;
	माप_प्रकार clen;

	clen = min_t(स्थिर माप_प्रकार, len, wsize);
	num_pages = DIV_ROUND_UP(clen, PAGE_SIZE);

	अगर (cur_len)
		*cur_len = clen;

	वापस num_pages;
पूर्ण

अटल व्योम
cअगरs_uncached_ग_लिखोdata_release(काष्ठा kref *refcount)
अणु
	पूर्णांक i;
	काष्ठा cअगरs_ग_लिखोdata *wdata = container_of(refcount,
					काष्ठा cअगरs_ग_लिखोdata, refcount);

	kref_put(&wdata->ctx->refcount, cअगरs_aio_ctx_release);
	क्रम (i = 0; i < wdata->nr_pages; i++)
		put_page(wdata->pages[i]);
	cअगरs_ग_लिखोdata_release(refcount);
पूर्ण

अटल व्योम collect_uncached_ग_लिखो_data(काष्ठा cअगरs_aio_ctx *ctx);

अटल व्योम
cअगरs_uncached_ग_लिखोv_complete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cअगरs_ग_लिखोdata *wdata = container_of(work,
					काष्ठा cअगरs_ग_लिखोdata, work);
	काष्ठा inode *inode = d_inode(wdata->cfile->dentry);
	काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(inode);

	spin_lock(&inode->i_lock);
	cअगरs_update_eof(cअगरsi, wdata->offset, wdata->bytes);
	अगर (cअगरsi->server_eof > inode->i_size)
		i_size_ग_लिखो(inode, cअगरsi->server_eof);
	spin_unlock(&inode->i_lock);

	complete(&wdata->करोne);
	collect_uncached_ग_लिखो_data(wdata->ctx);
	/* the below call can possibly मुक्त the last ref to aio ctx */
	kref_put(&wdata->refcount, cअगरs_uncached_ग_लिखोdata_release);
पूर्ण

अटल पूर्णांक
wdata_fill_from_iovec(काष्ठा cअगरs_ग_लिखोdata *wdata, काष्ठा iov_iter *from,
		      माप_प्रकार *len, अचिन्हित दीर्घ *num_pages)
अणु
	माप_प्रकार save_len, copied, bytes, cur_len = *len;
	अचिन्हित दीर्घ i, nr_pages = *num_pages;

	save_len = cur_len;
	क्रम (i = 0; i < nr_pages; i++) अणु
		bytes = min_t(स्थिर माप_प्रकार, cur_len, PAGE_SIZE);
		copied = copy_page_from_iter(wdata->pages[i], 0, bytes, from);
		cur_len -= copied;
		/*
		 * If we didn't copy as much as we expected, then that
		 * may mean we trod पूर्णांकo an unmapped area. Stop copying
		 * at that poपूर्णांक. On the next pass through the big
		 * loop, we'll likely end up getting a zero-length
		 * ग_लिखो and bailing out of it.
		 */
		अगर (copied < bytes)
			अवरोध;
	पूर्ण
	cur_len = save_len - cur_len;
	*len = cur_len;

	/*
	 * If we have no data to send, then that probably means that
	 * the copy above failed altogether. That's most likely because
	 * the address in the iovec was bogus. Return -EFAULT and let
	 * the caller मुक्त anything we allocated and bail out.
	 */
	अगर (!cur_len)
		वापस -EFAULT;

	/*
	 * i + 1 now represents the number of pages we actually used in
	 * the copy phase above.
	 */
	*num_pages = i + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक
cअगरs_resend_wdata(काष्ठा cअगरs_ग_लिखोdata *wdata, काष्ठा list_head *wdata_list,
	काष्ठा cअगरs_aio_ctx *ctx)
अणु
	अचिन्हित पूर्णांक wsize;
	काष्ठा cअगरs_credits credits;
	पूर्णांक rc;
	काष्ठा TCP_Server_Info *server = wdata->server;

	करो अणु
		अगर (wdata->cfile->invalidHandle) अणु
			rc = cअगरs_reखोलो_file(wdata->cfile, false);
			अगर (rc == -EAGAIN)
				जारी;
			अन्यथा अगर (rc)
				अवरोध;
		पूर्ण


		/*
		 * Wait क्रम credits to resend this wdata.
		 * Note: we are attempting to resend the whole wdata not in
		 * segments
		 */
		करो अणु
			rc = server->ops->रुको_mtu_credits(server, wdata->bytes,
						&wsize, &credits);
			अगर (rc)
				जाओ fail;

			अगर (wsize < wdata->bytes) अणु
				add_credits_and_wake_अगर(server, &credits, 0);
				msleep(1000);
			पूर्ण
		पूर्ण जबतक (wsize < wdata->bytes);
		wdata->credits = credits;

		rc = adjust_credits(server, &wdata->credits, wdata->bytes);

		अगर (!rc) अणु
			अगर (wdata->cfile->invalidHandle)
				rc = -EAGAIN;
			अन्यथा अणु
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
				अगर (wdata->mr) अणु
					wdata->mr->need_invalidate = true;
					smbd_deरेजिस्टर_mr(wdata->mr);
					wdata->mr = शून्य;
				पूर्ण
#पूर्ण_अगर
				rc = server->ops->async_ग_लिखोv(wdata,
					cअगरs_uncached_ग_लिखोdata_release);
			पूर्ण
		पूर्ण

		/* If the ग_लिखो was successfully sent, we are करोne */
		अगर (!rc) अणु
			list_add_tail(&wdata->list, wdata_list);
			वापस 0;
		पूर्ण

		/* Roll back credits and retry अगर needed */
		add_credits_and_wake_अगर(server, &wdata->credits, 0);
	पूर्ण जबतक (rc == -EAGAIN);

fail:
	kref_put(&wdata->refcount, cअगरs_uncached_ग_लिखोdata_release);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_ग_लिखो_from_iter(loff_t offset, माप_प्रकार len, काष्ठा iov_iter *from,
		     काष्ठा cअगरsFileInfo *खोलो_file,
		     काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा list_head *wdata_list,
		     काष्ठा cअगरs_aio_ctx *ctx)
अणु
	पूर्णांक rc = 0;
	माप_प्रकार cur_len;
	अचिन्हित दीर्घ nr_pages, num_pages, i;
	काष्ठा cअगरs_ग_लिखोdata *wdata;
	काष्ठा iov_iter saved_from = *from;
	loff_t saved_offset = offset;
	pid_t pid;
	काष्ठा TCP_Server_Info *server;
	काष्ठा page **pagevec;
	माप_प्रकार start;
	अचिन्हित पूर्णांक xid;

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_RWPIDFORWARD)
		pid = खोलो_file->pid;
	अन्यथा
		pid = current->tgid;

	server = cअगरs_pick_channel(tlink_tcon(खोलो_file->tlink)->ses);
	xid = get_xid();

	करो अणु
		अचिन्हित पूर्णांक wsize;
		काष्ठा cअगरs_credits credits_on_stack;
		काष्ठा cअगरs_credits *credits = &credits_on_stack;

		अगर (खोलो_file->invalidHandle) अणु
			rc = cअगरs_reखोलो_file(खोलो_file, false);
			अगर (rc == -EAGAIN)
				जारी;
			अन्यथा अगर (rc)
				अवरोध;
		पूर्ण

		rc = server->ops->रुको_mtu_credits(server, cअगरs_sb->ctx->wsize,
						   &wsize, credits);
		अगर (rc)
			अवरोध;

		cur_len = min_t(स्थिर माप_प्रकार, len, wsize);

		अगर (ctx->direct_io) अणु
			sमाप_प्रकार result;

			result = iov_iter_get_pages_alloc(
				from, &pagevec, cur_len, &start);
			अगर (result < 0) अणु
				cअगरs_dbg(VFS,
					 "direct_writev couldn't get user pages (rc=%zd) iter type %d iov_offset %zd count %zd\n",
					 result, iov_iter_type(from),
					 from->iov_offset, from->count);
				dump_stack();

				rc = result;
				add_credits_and_wake_अगर(server, credits, 0);
				अवरोध;
			पूर्ण
			cur_len = (माप_प्रकार)result;
			iov_iter_advance(from, cur_len);

			nr_pages =
				(cur_len + start + PAGE_SIZE - 1) / PAGE_SIZE;

			wdata = cअगरs_ग_लिखोdata_direct_alloc(pagevec,
					     cअगरs_uncached_ग_लिखोv_complete);
			अगर (!wdata) अणु
				rc = -ENOMEM;
				add_credits_and_wake_अगर(server, credits, 0);
				अवरोध;
			पूर्ण


			wdata->page_offset = start;
			wdata->tailsz =
				nr_pages > 1 ?
					cur_len - (PAGE_SIZE - start) -
					(nr_pages - 2) * PAGE_SIZE :
					cur_len;
		पूर्ण अन्यथा अणु
			nr_pages = get_numpages(wsize, len, &cur_len);
			wdata = cअगरs_ग_लिखोdata_alloc(nr_pages,
					     cअगरs_uncached_ग_लिखोv_complete);
			अगर (!wdata) अणु
				rc = -ENOMEM;
				add_credits_and_wake_अगर(server, credits, 0);
				अवरोध;
			पूर्ण

			rc = cअगरs_ग_लिखो_allocate_pages(wdata->pages, nr_pages);
			अगर (rc) अणु
				kvमुक्त(wdata->pages);
				kमुक्त(wdata);
				add_credits_and_wake_अगर(server, credits, 0);
				अवरोध;
			पूर्ण

			num_pages = nr_pages;
			rc = wdata_fill_from_iovec(
				wdata, from, &cur_len, &num_pages);
			अगर (rc) अणु
				क्रम (i = 0; i < nr_pages; i++)
					put_page(wdata->pages[i]);
				kvमुक्त(wdata->pages);
				kमुक्त(wdata);
				add_credits_and_wake_अगर(server, credits, 0);
				अवरोध;
			पूर्ण

			/*
			 * Bring nr_pages करोwn to the number of pages we
			 * actually used, and मुक्त any pages that we didn't use.
			 */
			क्रम ( ; nr_pages > num_pages; nr_pages--)
				put_page(wdata->pages[nr_pages - 1]);

			wdata->tailsz = cur_len - ((nr_pages - 1) * PAGE_SIZE);
		पूर्ण

		wdata->sync_mode = WB_SYNC_ALL;
		wdata->nr_pages = nr_pages;
		wdata->offset = (__u64)offset;
		wdata->cfile = cअगरsFileInfo_get(खोलो_file);
		wdata->server = server;
		wdata->pid = pid;
		wdata->bytes = cur_len;
		wdata->pagesz = PAGE_SIZE;
		wdata->credits = credits_on_stack;
		wdata->ctx = ctx;
		kref_get(&ctx->refcount);

		rc = adjust_credits(server, &wdata->credits, wdata->bytes);

		अगर (!rc) अणु
			अगर (wdata->cfile->invalidHandle)
				rc = -EAGAIN;
			अन्यथा
				rc = server->ops->async_ग_लिखोv(wdata,
					cअगरs_uncached_ग_लिखोdata_release);
		पूर्ण

		अगर (rc) अणु
			add_credits_and_wake_अगर(server, &wdata->credits, 0);
			kref_put(&wdata->refcount,
				 cअगरs_uncached_ग_लिखोdata_release);
			अगर (rc == -EAGAIN) अणु
				*from = saved_from;
				iov_iter_advance(from, offset - saved_offset);
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		list_add_tail(&wdata->list, wdata_list);
		offset += cur_len;
		len -= cur_len;
	पूर्ण जबतक (len > 0);

	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल व्योम collect_uncached_ग_लिखो_data(काष्ठा cअगरs_aio_ctx *ctx)
अणु
	काष्ठा cअगरs_ग_लिखोdata *wdata, *पंचांगp;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा dentry *dentry = ctx->cfile->dentry;
	पूर्णांक rc;

	tcon = tlink_tcon(ctx->cfile->tlink);
	cअगरs_sb = CIFS_SB(dentry->d_sb);

	mutex_lock(&ctx->aio_mutex);

	अगर (list_empty(&ctx->list)) अणु
		mutex_unlock(&ctx->aio_mutex);
		वापस;
	पूर्ण

	rc = ctx->rc;
	/*
	 * Wait क्रम and collect replies क्रम any successful sends in order of
	 * increasing offset. Once an error is hit, then वापस without रुकोing
	 * क्रम any more replies.
	 */
restart_loop:
	list_क्रम_each_entry_safe(wdata, पंचांगp, &ctx->list, list) अणु
		अगर (!rc) अणु
			अगर (!try_रुको_क्रम_completion(&wdata->करोne)) अणु
				mutex_unlock(&ctx->aio_mutex);
				वापस;
			पूर्ण

			अगर (wdata->result)
				rc = wdata->result;
			अन्यथा
				ctx->total_len += wdata->bytes;

			/* resend call अगर it's a retryable error */
			अगर (rc == -EAGAIN) अणु
				काष्ठा list_head पंचांगp_list;
				काष्ठा iov_iter पंचांगp_from = ctx->iter;

				INIT_LIST_HEAD(&पंचांगp_list);
				list_del_init(&wdata->list);

				अगर (ctx->direct_io)
					rc = cअगरs_resend_wdata(
						wdata, &पंचांगp_list, ctx);
				अन्यथा अणु
					iov_iter_advance(&पंचांगp_from,
						 wdata->offset - ctx->pos);

					rc = cअगरs_ग_लिखो_from_iter(wdata->offset,
						wdata->bytes, &पंचांगp_from,
						ctx->cfile, cअगरs_sb, &पंचांगp_list,
						ctx);

					kref_put(&wdata->refcount,
						cअगरs_uncached_ग_लिखोdata_release);
				पूर्ण

				list_splice(&पंचांगp_list, &ctx->list);
				जाओ restart_loop;
			पूर्ण
		पूर्ण
		list_del_init(&wdata->list);
		kref_put(&wdata->refcount, cअगरs_uncached_ग_लिखोdata_release);
	पूर्ण

	cअगरs_stats_bytes_written(tcon, ctx->total_len);
	set_bit(CIFS_INO_INVALID_MAPPING, &CIFS_I(dentry->d_inode)->flags);

	ctx->rc = (rc == 0) ? ctx->total_len : rc;

	mutex_unlock(&ctx->aio_mutex);

	अगर (ctx->iocb && ctx->iocb->ki_complete)
		ctx->iocb->ki_complete(ctx->iocb, ctx->rc, 0);
	अन्यथा
		complete(&ctx->करोne);
पूर्ण

अटल sमाप_प्रकार __cअगरs_ग_लिखोv(
	काष्ठा kiocb *iocb, काष्ठा iov_iter *from, bool direct)
अणु
	काष्ठा file *file = iocb->ki_filp;
	sमाप_प्रकार total_written = 0;
	काष्ठा cअगरsFileInfo *cfile;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा cअगरs_aio_ctx *ctx;
	काष्ठा iov_iter saved_from = *from;
	माप_प्रकार len = iov_iter_count(from);
	पूर्णांक rc;

	/*
	 * iov_iter_get_pages_alloc करोesn't work with ITER_KVEC.
	 * In this हाल, fall back to non-direct ग_लिखो function.
	 * this could be improved by getting pages directly in ITER_KVEC
	 */
	अगर (direct && iov_iter_is_kvec(from)) अणु
		cअगरs_dbg(FYI, "use non-direct cifs_writev for kvec I/O\n");
		direct = false;
	पूर्ण

	rc = generic_ग_लिखो_checks(iocb, from);
	अगर (rc <= 0)
		वापस rc;

	cअगरs_sb = CIFS_खाता_SB(file);
	cfile = file->निजी_data;
	tcon = tlink_tcon(cfile->tlink);

	अगर (!tcon->ses->server->ops->async_ग_लिखोv)
		वापस -ENOSYS;

	ctx = cअगरs_aio_ctx_alloc();
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->cfile = cअगरsFileInfo_get(cfile);

	अगर (!is_sync_kiocb(iocb))
		ctx->iocb = iocb;

	ctx->pos = iocb->ki_pos;

	अगर (direct) अणु
		ctx->direct_io = true;
		ctx->iter = *from;
		ctx->len = len;
	पूर्ण अन्यथा अणु
		rc = setup_aio_ctx_iter(ctx, from, WRITE);
		अगर (rc) अणु
			kref_put(&ctx->refcount, cअगरs_aio_ctx_release);
			वापस rc;
		पूर्ण
	पूर्ण

	/* grab a lock here due to पढ़ो response handlers can access ctx */
	mutex_lock(&ctx->aio_mutex);

	rc = cअगरs_ग_लिखो_from_iter(iocb->ki_pos, ctx->len, &saved_from,
				  cfile, cअगरs_sb, &ctx->list, ctx);

	/*
	 * If at least one ग_लिखो was successfully sent, then discard any rc
	 * value from the later ग_लिखोs. If the other ग_लिखो succeeds, then
	 * we'll end up वापसing whatever was written. If it fails, then
	 * we'll get a new rc value from that.
	 */
	अगर (!list_empty(&ctx->list))
		rc = 0;

	mutex_unlock(&ctx->aio_mutex);

	अगर (rc) अणु
		kref_put(&ctx->refcount, cअगरs_aio_ctx_release);
		वापस rc;
	पूर्ण

	अगर (!is_sync_kiocb(iocb)) अणु
		kref_put(&ctx->refcount, cअगरs_aio_ctx_release);
		वापस -EIOCBQUEUED;
	पूर्ण

	rc = रुको_क्रम_completion_समाप्तable(&ctx->करोne);
	अगर (rc) अणु
		mutex_lock(&ctx->aio_mutex);
		ctx->rc = rc = -EINTR;
		total_written = ctx->total_len;
		mutex_unlock(&ctx->aio_mutex);
	पूर्ण अन्यथा अणु
		rc = ctx->rc;
		total_written = ctx->total_len;
	पूर्ण

	kref_put(&ctx->refcount, cअगरs_aio_ctx_release);

	अगर (unlikely(!total_written))
		वापस rc;

	iocb->ki_pos += total_written;
	वापस total_written;
पूर्ण

sमाप_प्रकार cअगरs_direct_ग_लिखोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	वापस __cअगरs_ग_लिखोv(iocb, from, true);
पूर्ण

sमाप_प्रकार cअगरs_user_ग_लिखोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	वापस __cअगरs_ग_लिखोv(iocb, from, false);
पूर्ण

अटल sमाप_प्रकार
cअगरs_ग_लिखोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा cअगरsFileInfo *cfile = (काष्ठा cअगरsFileInfo *)file->निजी_data;
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(inode);
	काष्ठा TCP_Server_Info *server = tlink_tcon(cfile->tlink)->ses->server;
	sमाप_प्रकार rc;

	inode_lock(inode);
	/*
	 * We need to hold the sem to be sure nobody modअगरies lock list
	 * with a brlock that prevents writing.
	 */
	करोwn_पढ़ो(&cinode->lock_sem);

	rc = generic_ग_लिखो_checks(iocb, from);
	अगर (rc <= 0)
		जाओ out;

	अगर (!cअगरs_find_lock_conflict(cfile, iocb->ki_pos, iov_iter_count(from),
				     server->vals->exclusive_lock_type, 0,
				     शून्य, CIFS_WRITE_OP))
		rc = __generic_file_ग_लिखो_iter(iocb, from);
	अन्यथा
		rc = -EACCES;
out:
	up_पढ़ो(&cinode->lock_sem);
	inode_unlock(inode);

	अगर (rc > 0)
		rc = generic_ग_लिखो_sync(iocb, rc);
	वापस rc;
पूर्ण

sमाप_प्रकार
cअगरs_strict_ग_लिखोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(inode);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा cअगरsFileInfo *cfile = (काष्ठा cअगरsFileInfo *)
						iocb->ki_filp->निजी_data;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cfile->tlink);
	sमाप_प्रकार written;

	written = cअगरs_get_ग_लिखोr(cinode);
	अगर (written)
		वापस written;

	अगर (CIFS_CACHE_WRITE(cinode)) अणु
		अगर (cap_unix(tcon->ses) &&
		(CIFS_UNIX_FCNTL_CAP & le64_to_cpu(tcon->fsUnixInfo.Capability))
		  && ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NOPOSIXBRL) == 0)) अणु
			written = generic_file_ग_लिखो_iter(iocb, from);
			जाओ out;
		पूर्ण
		written = cअगरs_ग_लिखोv(iocb, from);
		जाओ out;
	पूर्ण
	/*
	 * For non-oplocked files in strict cache mode we need to ग_लिखो the data
	 * to the server exactly from the pos to pos+len-1 rather than flush all
	 * affected pages because it may cause a error with mandatory locks on
	 * these pages but not on the region from pos to ppos+len-1.
	 */
	written = cअगरs_user_ग_लिखोv(iocb, from);
	अगर (CIFS_CACHE_READ(cinode)) अणु
		/*
		 * We have पढ़ो level caching and we have just sent a ग_लिखो
		 * request to the server thus making data in the cache stale.
		 * Zap the cache and set oplock/lease level to NONE to aव्योम
		 * पढ़ोing stale data from the cache. All subsequent पढ़ो
		 * operations will पढ़ो new data from the server.
		 */
		cअगरs_zap_mapping(inode);
		cअगरs_dbg(FYI, "Set Oplock/Lease to NONE for inode=%p after write\n",
			 inode);
		cinode->oplock = 0;
	पूर्ण
out:
	cअगरs_put_ग_लिखोr(cinode);
	वापस written;
पूर्ण

अटल काष्ठा cअगरs_पढ़ोdata *
cअगरs_पढ़ोdata_direct_alloc(काष्ठा page **pages, work_func_t complete)
अणु
	काष्ठा cअगरs_पढ़ोdata *rdata;

	rdata = kzalloc(माप(*rdata), GFP_KERNEL);
	अगर (rdata != शून्य) अणु
		rdata->pages = pages;
		kref_init(&rdata->refcount);
		INIT_LIST_HEAD(&rdata->list);
		init_completion(&rdata->करोne);
		INIT_WORK(&rdata->work, complete);
	पूर्ण

	वापस rdata;
पूर्ण

अटल काष्ठा cअगरs_पढ़ोdata *
cअगरs_पढ़ोdata_alloc(अचिन्हित पूर्णांक nr_pages, work_func_t complete)
अणु
	काष्ठा page **pages =
		kसुस्मृति(nr_pages, माप(काष्ठा page *), GFP_KERNEL);
	काष्ठा cअगरs_पढ़ोdata *ret = शून्य;

	अगर (pages) अणु
		ret = cअगरs_पढ़ोdata_direct_alloc(pages, complete);
		अगर (!ret)
			kमुक्त(pages);
	पूर्ण

	वापस ret;
पूर्ण

व्योम
cअगरs_पढ़ोdata_release(काष्ठा kref *refcount)
अणु
	काष्ठा cअगरs_पढ़ोdata *rdata = container_of(refcount,
					काष्ठा cअगरs_पढ़ोdata, refcount);
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	अगर (rdata->mr) अणु
		smbd_deरेजिस्टर_mr(rdata->mr);
		rdata->mr = शून्य;
	पूर्ण
#पूर्ण_अगर
	अगर (rdata->cfile)
		cअगरsFileInfo_put(rdata->cfile);

	kvमुक्त(rdata->pages);
	kमुक्त(rdata);
पूर्ण

अटल पूर्णांक
cअगरs_पढ़ो_allocate_pages(काष्ठा cअगरs_पढ़ोdata *rdata, अचिन्हित पूर्णांक nr_pages)
अणु
	पूर्णांक rc = 0;
	काष्ठा page *page;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nr_pages; i++) अणु
		page = alloc_page(GFP_KERNEL|__GFP_HIGHMEM);
		अगर (!page) अणु
			rc = -ENOMEM;
			अवरोध;
		पूर्ण
		rdata->pages[i] = page;
	पूर्ण

	अगर (rc) अणु
		अचिन्हित पूर्णांक nr_page_failed = i;

		क्रम (i = 0; i < nr_page_failed; i++) अणु
			put_page(rdata->pages[i]);
			rdata->pages[i] = शून्य;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम
cअगरs_uncached_पढ़ोdata_release(काष्ठा kref *refcount)
अणु
	काष्ठा cअगरs_पढ़ोdata *rdata = container_of(refcount,
					काष्ठा cअगरs_पढ़ोdata, refcount);
	अचिन्हित पूर्णांक i;

	kref_put(&rdata->ctx->refcount, cअगरs_aio_ctx_release);
	क्रम (i = 0; i < rdata->nr_pages; i++) अणु
		put_page(rdata->pages[i]);
	पूर्ण
	cअगरs_पढ़ोdata_release(refcount);
पूर्ण

/**
 * cअगरs_पढ़ोdata_to_iov - copy data from pages in response to an iovec
 * @rdata:	the पढ़ोdata response with list of pages holding data
 * @iter:	destination क्रम our data
 *
 * This function copies data from a list of pages in a पढ़ोdata response पूर्णांकo
 * an array of iovecs. It will first calculate where the data should go
 * based on the info in the पढ़ोdata and then copy the data पूर्णांकo that spot.
 */
अटल पूर्णांक
cअगरs_पढ़ोdata_to_iov(काष्ठा cअगरs_पढ़ोdata *rdata, काष्ठा iov_iter *iter)
अणु
	माप_प्रकार reमुख्यing = rdata->got_bytes;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < rdata->nr_pages; i++) अणु
		काष्ठा page *page = rdata->pages[i];
		माप_प्रकार copy = min_t(माप_प्रकार, reमुख्यing, PAGE_SIZE);
		माप_प्रकार written;

		अगर (unlikely(iov_iter_is_pipe(iter))) अणु
			व्योम *addr = kmap_atomic(page);

			written = copy_to_iter(addr, copy, iter);
			kunmap_atomic(addr);
		पूर्ण अन्यथा
			written = copy_page_to_iter(page, 0, copy, iter);
		reमुख्यing -= written;
		अगर (written < copy && iov_iter_count(iter) > 0)
			अवरोध;
	पूर्ण
	वापस reमुख्यing ? -EFAULT : 0;
पूर्ण

अटल व्योम collect_uncached_पढ़ो_data(काष्ठा cअगरs_aio_ctx *ctx);

अटल व्योम
cअगरs_uncached_पढ़ोv_complete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cअगरs_पढ़ोdata *rdata = container_of(work,
						काष्ठा cअगरs_पढ़ोdata, work);

	complete(&rdata->करोne);
	collect_uncached_पढ़ो_data(rdata->ctx);
	/* the below call can possibly मुक्त the last ref to aio ctx */
	kref_put(&rdata->refcount, cअगरs_uncached_पढ़ोdata_release);
पूर्ण

अटल पूर्णांक
uncached_fill_pages(काष्ठा TCP_Server_Info *server,
		    काष्ठा cअगरs_पढ़ोdata *rdata, काष्ठा iov_iter *iter,
		    अचिन्हित पूर्णांक len)
अणु
	पूर्णांक result = 0;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक nr_pages = rdata->nr_pages;
	अचिन्हित पूर्णांक page_offset = rdata->page_offset;

	rdata->got_bytes = 0;
	rdata->tailsz = PAGE_SIZE;
	क्रम (i = 0; i < nr_pages; i++) अणु
		काष्ठा page *page = rdata->pages[i];
		माप_प्रकार n;
		अचिन्हित पूर्णांक segment_size = rdata->pagesz;

		अगर (i == 0)
			segment_size -= page_offset;
		अन्यथा
			page_offset = 0;


		अगर (len <= 0) अणु
			/* no need to hold page hostage */
			rdata->pages[i] = शून्य;
			rdata->nr_pages--;
			put_page(page);
			जारी;
		पूर्ण

		n = len;
		अगर (len >= segment_size)
			/* enough data to fill the page */
			n = segment_size;
		अन्यथा
			rdata->tailsz = len;
		len -= n;

		अगर (iter)
			result = copy_page_from_iter(
					page, page_offset, n, iter);
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
		अन्यथा अगर (rdata->mr)
			result = n;
#पूर्ण_अगर
		अन्यथा
			result = cअगरs_पढ़ो_page_from_socket(
					server, page, page_offset, n);
		अगर (result < 0)
			अवरोध;

		rdata->got_bytes += result;
	पूर्ण

	वापस rdata->got_bytes > 0 && result != -ECONNABORTED ?
						rdata->got_bytes : result;
पूर्ण

अटल पूर्णांक
cअगरs_uncached_पढ़ो_पूर्णांकo_pages(काष्ठा TCP_Server_Info *server,
			      काष्ठा cअगरs_पढ़ोdata *rdata, अचिन्हित पूर्णांक len)
अणु
	वापस uncached_fill_pages(server, rdata, शून्य, len);
पूर्ण

अटल पूर्णांक
cअगरs_uncached_copy_पूर्णांकo_pages(काष्ठा TCP_Server_Info *server,
			      काष्ठा cअगरs_पढ़ोdata *rdata,
			      काष्ठा iov_iter *iter)
अणु
	वापस uncached_fill_pages(server, rdata, iter, iter->count);
पूर्ण

अटल पूर्णांक cअगरs_resend_rdata(काष्ठा cअगरs_पढ़ोdata *rdata,
			काष्ठा list_head *rdata_list,
			काष्ठा cअगरs_aio_ctx *ctx)
अणु
	अचिन्हित पूर्णांक rsize;
	काष्ठा cअगरs_credits credits;
	पूर्णांक rc;
	काष्ठा TCP_Server_Info *server;

	/* XXX: should we pick a new channel here? */
	server = rdata->server;

	करो अणु
		अगर (rdata->cfile->invalidHandle) अणु
			rc = cअगरs_reखोलो_file(rdata->cfile, true);
			अगर (rc == -EAGAIN)
				जारी;
			अन्यथा अगर (rc)
				अवरोध;
		पूर्ण

		/*
		 * Wait क्रम credits to resend this rdata.
		 * Note: we are attempting to resend the whole rdata not in
		 * segments
		 */
		करो अणु
			rc = server->ops->रुको_mtu_credits(server, rdata->bytes,
						&rsize, &credits);

			अगर (rc)
				जाओ fail;

			अगर (rsize < rdata->bytes) अणु
				add_credits_and_wake_अगर(server, &credits, 0);
				msleep(1000);
			पूर्ण
		पूर्ण जबतक (rsize < rdata->bytes);
		rdata->credits = credits;

		rc = adjust_credits(server, &rdata->credits, rdata->bytes);
		अगर (!rc) अणु
			अगर (rdata->cfile->invalidHandle)
				rc = -EAGAIN;
			अन्यथा अणु
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
				अगर (rdata->mr) अणु
					rdata->mr->need_invalidate = true;
					smbd_deरेजिस्टर_mr(rdata->mr);
					rdata->mr = शून्य;
				पूर्ण
#पूर्ण_अगर
				rc = server->ops->async_पढ़ोv(rdata);
			पूर्ण
		पूर्ण

		/* If the पढ़ो was successfully sent, we are करोne */
		अगर (!rc) अणु
			/* Add to aio pending list */
			list_add_tail(&rdata->list, rdata_list);
			वापस 0;
		पूर्ण

		/* Roll back credits and retry अगर needed */
		add_credits_and_wake_अगर(server, &rdata->credits, 0);
	पूर्ण जबतक (rc == -EAGAIN);

fail:
	kref_put(&rdata->refcount, cअगरs_uncached_पढ़ोdata_release);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_send_async_पढ़ो(loff_t offset, माप_प्रकार len, काष्ठा cअगरsFileInfo *खोलो_file,
		     काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा list_head *rdata_list,
		     काष्ठा cअगरs_aio_ctx *ctx)
अणु
	काष्ठा cअगरs_पढ़ोdata *rdata;
	अचिन्हित पूर्णांक npages, rsize;
	काष्ठा cअगरs_credits credits_on_stack;
	काष्ठा cअगरs_credits *credits = &credits_on_stack;
	माप_प्रकार cur_len;
	पूर्णांक rc;
	pid_t pid;
	काष्ठा TCP_Server_Info *server;
	काष्ठा page **pagevec;
	माप_प्रकार start;
	काष्ठा iov_iter direct_iov = ctx->iter;

	server = cअगरs_pick_channel(tlink_tcon(खोलो_file->tlink)->ses);

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_RWPIDFORWARD)
		pid = खोलो_file->pid;
	अन्यथा
		pid = current->tgid;

	अगर (ctx->direct_io)
		iov_iter_advance(&direct_iov, offset - ctx->pos);

	करो अणु
		अगर (खोलो_file->invalidHandle) अणु
			rc = cअगरs_reखोलो_file(खोलो_file, true);
			अगर (rc == -EAGAIN)
				जारी;
			अन्यथा अगर (rc)
				अवरोध;
		पूर्ण

		rc = server->ops->रुको_mtu_credits(server, cअगरs_sb->ctx->rsize,
						   &rsize, credits);
		अगर (rc)
			अवरोध;

		cur_len = min_t(स्थिर माप_प्रकार, len, rsize);

		अगर (ctx->direct_io) अणु
			sमाप_प्रकार result;

			result = iov_iter_get_pages_alloc(
					&direct_iov, &pagevec,
					cur_len, &start);
			अगर (result < 0) अणु
				cअगरs_dbg(VFS,
					 "Couldn't get user pages (rc=%zd) iter type %d iov_offset %zd count %zd\n",
					 result, iov_iter_type(&direct_iov),
					 direct_iov.iov_offset,
					 direct_iov.count);
				dump_stack();

				rc = result;
				add_credits_and_wake_अगर(server, credits, 0);
				अवरोध;
			पूर्ण
			cur_len = (माप_प्रकार)result;
			iov_iter_advance(&direct_iov, cur_len);

			rdata = cअगरs_पढ़ोdata_direct_alloc(
					pagevec, cअगरs_uncached_पढ़ोv_complete);
			अगर (!rdata) अणु
				add_credits_and_wake_अगर(server, credits, 0);
				rc = -ENOMEM;
				अवरोध;
			पूर्ण

			npages = (cur_len + start + PAGE_SIZE-1) / PAGE_SIZE;
			rdata->page_offset = start;
			rdata->tailsz = npages > 1 ?
				cur_len-(PAGE_SIZE-start)-(npages-2)*PAGE_SIZE :
				cur_len;

		पूर्ण अन्यथा अणु

			npages = DIV_ROUND_UP(cur_len, PAGE_SIZE);
			/* allocate a पढ़ोdata काष्ठा */
			rdata = cअगरs_पढ़ोdata_alloc(npages,
					    cअगरs_uncached_पढ़ोv_complete);
			अगर (!rdata) अणु
				add_credits_and_wake_अगर(server, credits, 0);
				rc = -ENOMEM;
				अवरोध;
			पूर्ण

			rc = cअगरs_पढ़ो_allocate_pages(rdata, npages);
			अगर (rc) अणु
				kvमुक्त(rdata->pages);
				kमुक्त(rdata);
				add_credits_and_wake_अगर(server, credits, 0);
				अवरोध;
			पूर्ण

			rdata->tailsz = PAGE_SIZE;
		पूर्ण

		rdata->server = server;
		rdata->cfile = cअगरsFileInfo_get(खोलो_file);
		rdata->nr_pages = npages;
		rdata->offset = offset;
		rdata->bytes = cur_len;
		rdata->pid = pid;
		rdata->pagesz = PAGE_SIZE;
		rdata->पढ़ो_पूर्णांकo_pages = cअगरs_uncached_पढ़ो_पूर्णांकo_pages;
		rdata->copy_पूर्णांकo_pages = cअगरs_uncached_copy_पूर्णांकo_pages;
		rdata->credits = credits_on_stack;
		rdata->ctx = ctx;
		kref_get(&ctx->refcount);

		rc = adjust_credits(server, &rdata->credits, rdata->bytes);

		अगर (!rc) अणु
			अगर (rdata->cfile->invalidHandle)
				rc = -EAGAIN;
			अन्यथा
				rc = server->ops->async_पढ़ोv(rdata);
		पूर्ण

		अगर (rc) अणु
			add_credits_and_wake_अगर(server, &rdata->credits, 0);
			kref_put(&rdata->refcount,
				cअगरs_uncached_पढ़ोdata_release);
			अगर (rc == -EAGAIN) अणु
				iov_iter_revert(&direct_iov, cur_len);
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		list_add_tail(&rdata->list, rdata_list);
		offset += cur_len;
		len -= cur_len;
	पूर्ण जबतक (len > 0);

	वापस rc;
पूर्ण

अटल व्योम
collect_uncached_पढ़ो_data(काष्ठा cअगरs_aio_ctx *ctx)
अणु
	काष्ठा cअगरs_पढ़ोdata *rdata, *पंचांगp;
	काष्ठा iov_iter *to = &ctx->iter;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	पूर्णांक rc;

	cअगरs_sb = CIFS_SB(ctx->cfile->dentry->d_sb);

	mutex_lock(&ctx->aio_mutex);

	अगर (list_empty(&ctx->list)) अणु
		mutex_unlock(&ctx->aio_mutex);
		वापस;
	पूर्ण

	rc = ctx->rc;
	/* the loop below should proceed in the order of increasing offsets */
again:
	list_क्रम_each_entry_safe(rdata, पंचांगp, &ctx->list, list) अणु
		अगर (!rc) अणु
			अगर (!try_रुको_क्रम_completion(&rdata->करोne)) अणु
				mutex_unlock(&ctx->aio_mutex);
				वापस;
			पूर्ण

			अगर (rdata->result == -EAGAIN) अणु
				/* resend call अगर it's a retryable error */
				काष्ठा list_head पंचांगp_list;
				अचिन्हित पूर्णांक got_bytes = rdata->got_bytes;

				list_del_init(&rdata->list);
				INIT_LIST_HEAD(&पंचांगp_list);

				/*
				 * Got a part of data and then reconnect has
				 * happened -- fill the buffer and जारी
				 * पढ़ोing.
				 */
				अगर (got_bytes && got_bytes < rdata->bytes) अणु
					rc = 0;
					अगर (!ctx->direct_io)
						rc = cअगरs_पढ़ोdata_to_iov(rdata, to);
					अगर (rc) अणु
						kref_put(&rdata->refcount,
							cअगरs_uncached_पढ़ोdata_release);
						जारी;
					पूर्ण
				पूर्ण

				अगर (ctx->direct_io) अणु
					/*
					 * Re-use rdata as this is a
					 * direct I/O
					 */
					rc = cअगरs_resend_rdata(
						rdata,
						&पंचांगp_list, ctx);
				पूर्ण अन्यथा अणु
					rc = cअगरs_send_async_पढ़ो(
						rdata->offset + got_bytes,
						rdata->bytes - got_bytes,
						rdata->cfile, cअगरs_sb,
						&पंचांगp_list, ctx);

					kref_put(&rdata->refcount,
						cअगरs_uncached_पढ़ोdata_release);
				पूर्ण

				list_splice(&पंचांगp_list, &ctx->list);

				जाओ again;
			पूर्ण अन्यथा अगर (rdata->result)
				rc = rdata->result;
			अन्यथा अगर (!ctx->direct_io)
				rc = cअगरs_पढ़ोdata_to_iov(rdata, to);

			/* अगर there was a लघु पढ़ो -- discard anything left */
			अगर (rdata->got_bytes && rdata->got_bytes < rdata->bytes)
				rc = -ENODATA;

			ctx->total_len += rdata->got_bytes;
		पूर्ण
		list_del_init(&rdata->list);
		kref_put(&rdata->refcount, cअगरs_uncached_पढ़ोdata_release);
	पूर्ण

	अगर (!ctx->direct_io)
		ctx->total_len = ctx->len - iov_iter_count(to);

	/* mask nodata हाल */
	अगर (rc == -ENODATA)
		rc = 0;

	ctx->rc = (rc == 0) ? (sमाप_प्रकार)ctx->total_len : rc;

	mutex_unlock(&ctx->aio_mutex);

	अगर (ctx->iocb && ctx->iocb->ki_complete)
		ctx->iocb->ki_complete(ctx->iocb, ctx->rc, 0);
	अन्यथा
		complete(&ctx->करोne);
पूर्ण

अटल sमाप_प्रकार __cअगरs_पढ़ोv(
	काष्ठा kiocb *iocb, काष्ठा iov_iter *to, bool direct)
अणु
	माप_प्रकार len;
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा cअगरsFileInfo *cfile;
	काष्ठा cअगरs_tcon *tcon;
	sमाप_प्रकार rc, total_पढ़ो = 0;
	loff_t offset = iocb->ki_pos;
	काष्ठा cअगरs_aio_ctx *ctx;

	/*
	 * iov_iter_get_pages_alloc() करोesn't work with ITER_KVEC,
	 * fall back to data copy पढ़ो path
	 * this could be improved by getting pages directly in ITER_KVEC
	 */
	अगर (direct && iov_iter_is_kvec(to)) अणु
		cअगरs_dbg(FYI, "use non-direct cifs_user_readv for kvec I/O\n");
		direct = false;
	पूर्ण

	len = iov_iter_count(to);
	अगर (!len)
		वापस 0;

	cअगरs_sb = CIFS_खाता_SB(file);
	cfile = file->निजी_data;
	tcon = tlink_tcon(cfile->tlink);

	अगर (!tcon->ses->server->ops->async_पढ़ोv)
		वापस -ENOSYS;

	अगर ((file->f_flags & O_ACCMODE) == O_WRONLY)
		cअगरs_dbg(FYI, "attempting read on write only file instance\n");

	ctx = cअगरs_aio_ctx_alloc();
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->cfile = cअगरsFileInfo_get(cfile);

	अगर (!is_sync_kiocb(iocb))
		ctx->iocb = iocb;

	अगर (iter_is_iovec(to))
		ctx->should_dirty = true;

	अगर (direct) अणु
		ctx->pos = offset;
		ctx->direct_io = true;
		ctx->iter = *to;
		ctx->len = len;
	पूर्ण अन्यथा अणु
		rc = setup_aio_ctx_iter(ctx, to, READ);
		अगर (rc) अणु
			kref_put(&ctx->refcount, cअगरs_aio_ctx_release);
			वापस rc;
		पूर्ण
		len = ctx->len;
	पूर्ण

	/* grab a lock here due to पढ़ो response handlers can access ctx */
	mutex_lock(&ctx->aio_mutex);

	rc = cअगरs_send_async_पढ़ो(offset, len, cfile, cअगरs_sb, &ctx->list, ctx);

	/* अगर at least one पढ़ो request send succeeded, then reset rc */
	अगर (!list_empty(&ctx->list))
		rc = 0;

	mutex_unlock(&ctx->aio_mutex);

	अगर (rc) अणु
		kref_put(&ctx->refcount, cअगरs_aio_ctx_release);
		वापस rc;
	पूर्ण

	अगर (!is_sync_kiocb(iocb)) अणु
		kref_put(&ctx->refcount, cअगरs_aio_ctx_release);
		वापस -EIOCBQUEUED;
	पूर्ण

	rc = रुको_क्रम_completion_समाप्तable(&ctx->करोne);
	अगर (rc) अणु
		mutex_lock(&ctx->aio_mutex);
		ctx->rc = rc = -EINTR;
		total_पढ़ो = ctx->total_len;
		mutex_unlock(&ctx->aio_mutex);
	पूर्ण अन्यथा अणु
		rc = ctx->rc;
		total_पढ़ो = ctx->total_len;
	पूर्ण

	kref_put(&ctx->refcount, cअगरs_aio_ctx_release);

	अगर (total_पढ़ो) अणु
		iocb->ki_pos += total_पढ़ो;
		वापस total_पढ़ो;
	पूर्ण
	वापस rc;
पूर्ण

sमाप_प्रकार cअगरs_direct_पढ़ोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	वापस __cअगरs_पढ़ोv(iocb, to, true);
पूर्ण

sमाप_प्रकार cअगरs_user_पढ़ोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	वापस __cअगरs_पढ़ोv(iocb, to, false);
पूर्ण

sमाप_प्रकार
cअगरs_strict_पढ़ोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(inode);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा cअगरsFileInfo *cfile = (काष्ठा cअगरsFileInfo *)
						iocb->ki_filp->निजी_data;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cfile->tlink);
	पूर्णांक rc = -EACCES;

	/*
	 * In strict cache mode we need to पढ़ो from the server all the समय
	 * अगर we करोn't have level II oplock because the server can delay mसमय
	 * change - so we can't make a decision about inode invalidating.
	 * And we can also fail with pageपढ़ोing अगर there are mandatory locks
	 * on pages affected by this पढ़ो but not on the region from pos to
	 * pos+len-1.
	 */
	अगर (!CIFS_CACHE_READ(cinode))
		वापस cअगरs_user_पढ़ोv(iocb, to);

	अगर (cap_unix(tcon->ses) &&
	    (CIFS_UNIX_FCNTL_CAP & le64_to_cpu(tcon->fsUnixInfo.Capability)) &&
	    ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NOPOSIXBRL) == 0))
		वापस generic_file_पढ़ो_iter(iocb, to);

	/*
	 * We need to hold the sem to be sure nobody modअगरies lock list
	 * with a brlock that prevents पढ़ोing.
	 */
	करोwn_पढ़ो(&cinode->lock_sem);
	अगर (!cअगरs_find_lock_conflict(cfile, iocb->ki_pos, iov_iter_count(to),
				     tcon->ses->server->vals->shared_lock_type,
				     0, शून्य, CIFS_READ_OP))
		rc = generic_file_पढ़ो_iter(iocb, to);
	up_पढ़ो(&cinode->lock_sem);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार
cअगरs_पढ़ो(काष्ठा file *file, अक्षर *पढ़ो_data, माप_प्रकार पढ़ो_size, loff_t *offset)
अणु
	पूर्णांक rc = -EACCES;
	अचिन्हित पूर्णांक bytes_पढ़ो = 0;
	अचिन्हित पूर्णांक total_पढ़ो;
	अचिन्हित पूर्णांक current_पढ़ो_size;
	अचिन्हित पूर्णांक rsize;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	अचिन्हित पूर्णांक xid;
	अक्षर *cur_offset;
	काष्ठा cअगरsFileInfo *खोलो_file;
	काष्ठा cअगरs_io_parms io_parms = अणु0पूर्ण;
	पूर्णांक buf_type = CIFS_NO_BUFFER;
	__u32 pid;

	xid = get_xid();
	cअगरs_sb = CIFS_खाता_SB(file);

	/* FIXME: set up handlers क्रम larger पढ़ोs and/or convert to async */
	rsize = min_t(अचिन्हित पूर्णांक, cअगरs_sb->ctx->rsize, CIFSMaxBufSize);

	अगर (file->निजी_data == शून्य) अणु
		rc = -EBADF;
		मुक्त_xid(xid);
		वापस rc;
	पूर्ण
	खोलो_file = file->निजी_data;
	tcon = tlink_tcon(खोलो_file->tlink);
	server = cअगरs_pick_channel(tcon->ses);

	अगर (!server->ops->sync_पढ़ो) अणु
		मुक्त_xid(xid);
		वापस -ENOSYS;
	पूर्ण

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_RWPIDFORWARD)
		pid = खोलो_file->pid;
	अन्यथा
		pid = current->tgid;

	अगर ((file->f_flags & O_ACCMODE) == O_WRONLY)
		cअगरs_dbg(FYI, "attempting read on write only file instance\n");

	क्रम (total_पढ़ो = 0, cur_offset = पढ़ो_data; पढ़ो_size > total_पढ़ो;
	     total_पढ़ो += bytes_पढ़ो, cur_offset += bytes_पढ़ो) अणु
		करो अणु
			current_पढ़ो_size = min_t(uपूर्णांक, पढ़ो_size - total_पढ़ो,
						  rsize);
			/*
			 * For winकरोws me and 9x we करो not want to request more
			 * than it negotiated since it will refuse the पढ़ो
			 * then.
			 */
			अगर (!(tcon->ses->capabilities &
				tcon->ses->server->vals->cap_large_files)) अणु
				current_पढ़ो_size = min_t(uपूर्णांक,
					current_पढ़ो_size, CIFSMaxBufSize);
			पूर्ण
			अगर (खोलो_file->invalidHandle) अणु
				rc = cअगरs_reखोलो_file(खोलो_file, true);
				अगर (rc != 0)
					अवरोध;
			पूर्ण
			io_parms.pid = pid;
			io_parms.tcon = tcon;
			io_parms.offset = *offset;
			io_parms.length = current_पढ़ो_size;
			io_parms.server = server;
			rc = server->ops->sync_पढ़ो(xid, &खोलो_file->fid, &io_parms,
						    &bytes_पढ़ो, &cur_offset,
						    &buf_type);
		पूर्ण जबतक (rc == -EAGAIN);

		अगर (rc || (bytes_पढ़ो == 0)) अणु
			अगर (total_पढ़ो) अणु
				अवरोध;
			पूर्ण अन्यथा अणु
				मुक्त_xid(xid);
				वापस rc;
			पूर्ण
		पूर्ण अन्यथा अणु
			cअगरs_stats_bytes_पढ़ो(tcon, total_पढ़ो);
			*offset += bytes_पढ़ो;
		पूर्ण
	पूर्ण
	मुक्त_xid(xid);
	वापस total_पढ़ो;
पूर्ण

/*
 * If the page is mmap'ed into a process' page tables, then we need to make
 * sure that it करोesn't change जबतक being written back.
 */
अटल vm_fault_t
cअगरs_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page = vmf->page;

	lock_page(page);
	वापस VM_FAULT_LOCKED;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा cअगरs_file_vm_ops = अणु
	.fault = filemap_fault,
	.map_pages = filemap_map_pages,
	.page_mkग_लिखो = cअगरs_page_mkग_लिखो,
पूर्ण;

पूर्णांक cअगरs_file_strict_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक xid, rc = 0;
	काष्ठा inode *inode = file_inode(file);

	xid = get_xid();

	अगर (!CIFS_CACHE_READ(CIFS_I(inode)))
		rc = cअगरs_zap_mapping(inode);
	अगर (!rc)
		rc = generic_file_mmap(file, vma);
	अगर (!rc)
		vma->vm_ops = &cअगरs_file_vm_ops;

	मुक्त_xid(xid);
	वापस rc;
पूर्ण

पूर्णांक cअगरs_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक rc, xid;

	xid = get_xid();

	rc = cअगरs_revalidate_file(file);
	अगर (rc)
		cअगरs_dbg(FYI, "Validation prior to mmap failed, error=%d\n",
			 rc);
	अगर (!rc)
		rc = generic_file_mmap(file, vma);
	अगर (!rc)
		vma->vm_ops = &cअगरs_file_vm_ops;

	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल व्योम
cअगरs_पढ़ोv_complete(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित पूर्णांक i, got_bytes;
	काष्ठा cअगरs_पढ़ोdata *rdata = container_of(work,
						काष्ठा cअगरs_पढ़ोdata, work);

	got_bytes = rdata->got_bytes;
	क्रम (i = 0; i < rdata->nr_pages; i++) अणु
		काष्ठा page *page = rdata->pages[i];

		lru_cache_add(page);

		अगर (rdata->result == 0 ||
		    (rdata->result == -EAGAIN && got_bytes)) अणु
			flush_dcache_page(page);
			SetPageUptodate(page);
		पूर्ण

		unlock_page(page);

		अगर (rdata->result == 0 ||
		    (rdata->result == -EAGAIN && got_bytes))
			cअगरs_पढ़ोpage_to_fscache(rdata->mapping->host, page);

		got_bytes -= min_t(अचिन्हित पूर्णांक, PAGE_SIZE, got_bytes);

		put_page(page);
		rdata->pages[i] = शून्य;
	पूर्ण
	kref_put(&rdata->refcount, cअगरs_पढ़ोdata_release);
पूर्ण

अटल पूर्णांक
पढ़ोpages_fill_pages(काष्ठा TCP_Server_Info *server,
		     काष्ठा cअगरs_पढ़ोdata *rdata, काष्ठा iov_iter *iter,
		     अचिन्हित पूर्णांक len)
अणु
	पूर्णांक result = 0;
	अचिन्हित पूर्णांक i;
	u64 eof;
	pgoff_t eof_index;
	अचिन्हित पूर्णांक nr_pages = rdata->nr_pages;
	अचिन्हित पूर्णांक page_offset = rdata->page_offset;

	/* determine the eof that the server (probably) has */
	eof = CIFS_I(rdata->mapping->host)->server_eof;
	eof_index = eof ? (eof - 1) >> PAGE_SHIFT : 0;
	cअगरs_dbg(FYI, "eof=%llu eof_index=%lu\n", eof, eof_index);

	rdata->got_bytes = 0;
	rdata->tailsz = PAGE_SIZE;
	क्रम (i = 0; i < nr_pages; i++) अणु
		काष्ठा page *page = rdata->pages[i];
		अचिन्हित पूर्णांक to_पढ़ो = rdata->pagesz;
		माप_प्रकार n;

		अगर (i == 0)
			to_पढ़ो -= page_offset;
		अन्यथा
			page_offset = 0;

		n = to_पढ़ो;

		अगर (len >= to_पढ़ो) अणु
			len -= to_पढ़ो;
		पूर्ण अन्यथा अगर (len > 0) अणु
			/* enough क्रम partial page, fill and zero the rest */
			zero_user(page, len + page_offset, to_पढ़ो - len);
			n = rdata->tailsz = len;
			len = 0;
		पूर्ण अन्यथा अगर (page->index > eof_index) अणु
			/*
			 * The VFS will not try to करो पढ़ोahead past the
			 * i_size, but it's possible that we have outstanding
			 * ग_लिखोs with gaps in the middle and the i_size hasn't
			 * caught up yet. Populate those with zeroed out pages
			 * to prevent the VFS from repeatedly attempting to
			 * fill them until the ग_लिखोs are flushed.
			 */
			zero_user(page, 0, PAGE_SIZE);
			lru_cache_add(page);
			flush_dcache_page(page);
			SetPageUptodate(page);
			unlock_page(page);
			put_page(page);
			rdata->pages[i] = शून्य;
			rdata->nr_pages--;
			जारी;
		पूर्ण अन्यथा अणु
			/* no need to hold page hostage */
			lru_cache_add(page);
			unlock_page(page);
			put_page(page);
			rdata->pages[i] = शून्य;
			rdata->nr_pages--;
			जारी;
		पूर्ण

		अगर (iter)
			result = copy_page_from_iter(
					page, page_offset, n, iter);
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
		अन्यथा अगर (rdata->mr)
			result = n;
#पूर्ण_अगर
		अन्यथा
			result = cअगरs_पढ़ो_page_from_socket(
					server, page, page_offset, n);
		अगर (result < 0)
			अवरोध;

		rdata->got_bytes += result;
	पूर्ण

	वापस rdata->got_bytes > 0 && result != -ECONNABORTED ?
						rdata->got_bytes : result;
पूर्ण

अटल पूर्णांक
cअगरs_पढ़ोpages_पढ़ो_पूर्णांकo_pages(काष्ठा TCP_Server_Info *server,
			       काष्ठा cअगरs_पढ़ोdata *rdata, अचिन्हित पूर्णांक len)
अणु
	वापस पढ़ोpages_fill_pages(server, rdata, शून्य, len);
पूर्ण

अटल पूर्णांक
cअगरs_पढ़ोpages_copy_पूर्णांकo_pages(काष्ठा TCP_Server_Info *server,
			       काष्ठा cअगरs_पढ़ोdata *rdata,
			       काष्ठा iov_iter *iter)
अणु
	वापस पढ़ोpages_fill_pages(server, rdata, iter, iter->count);
पूर्ण

अटल पूर्णांक
पढ़ोpages_get_pages(काष्ठा address_space *mapping, काष्ठा list_head *page_list,
		    अचिन्हित पूर्णांक rsize, काष्ठा list_head *पंचांगplist,
		    अचिन्हित पूर्णांक *nr_pages, loff_t *offset, अचिन्हित पूर्णांक *bytes)
अणु
	काष्ठा page *page, *tpage;
	अचिन्हित पूर्णांक expected_index;
	पूर्णांक rc;
	gfp_t gfp = पढ़ोahead_gfp_mask(mapping);

	INIT_LIST_HEAD(पंचांगplist);

	page = lru_to_page(page_list);

	/*
	 * Lock the page and put it in the cache. Since no one अन्यथा
	 * should have access to this page, we're safe to simply set
	 * PG_locked without checking it first.
	 */
	__SetPageLocked(page);
	rc = add_to_page_cache_locked(page, mapping,
				      page->index, gfp);

	/* give up अगर we can't stick it in the cache */
	अगर (rc) अणु
		__ClearPageLocked(page);
		वापस rc;
	पूर्ण

	/* move first page to the पंचांगplist */
	*offset = (loff_t)page->index << PAGE_SHIFT;
	*bytes = PAGE_SIZE;
	*nr_pages = 1;
	list_move_tail(&page->lru, पंचांगplist);

	/* now try and add more pages onto the request */
	expected_index = page->index + 1;
	list_क्रम_each_entry_safe_reverse(page, tpage, page_list, lru) अणु
		/* discontinuity ? */
		अगर (page->index != expected_index)
			अवरोध;

		/* would this page push the पढ़ो over the rsize? */
		अगर (*bytes + PAGE_SIZE > rsize)
			अवरोध;

		__SetPageLocked(page);
		rc = add_to_page_cache_locked(page, mapping, page->index, gfp);
		अगर (rc) अणु
			__ClearPageLocked(page);
			अवरोध;
		पूर्ण
		list_move_tail(&page->lru, पंचांगplist);
		(*bytes) += PAGE_SIZE;
		expected_index++;
		(*nr_pages)++;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक cअगरs_पढ़ोpages(काष्ठा file *file, काष्ठा address_space *mapping,
	काष्ठा list_head *page_list, अचिन्हित num_pages)
अणु
	पूर्णांक rc;
	पूर्णांक err = 0;
	काष्ठा list_head पंचांगplist;
	काष्ठा cअगरsFileInfo *खोलो_file = file->निजी_data;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_खाता_SB(file);
	काष्ठा TCP_Server_Info *server;
	pid_t pid;
	अचिन्हित पूर्णांक xid;

	xid = get_xid();
	/*
	 * Reads as many pages as possible from fscache. Returns -ENOBUFS
	 * immediately अगर the cookie is negative
	 *
	 * After this poपूर्णांक, every page in the list might have PG_fscache set,
	 * so we will need to clean that up off of every page we करोn't use.
	 */
	rc = cअगरs_पढ़ोpages_from_fscache(mapping->host, mapping, page_list,
					 &num_pages);
	अगर (rc == 0) अणु
		मुक्त_xid(xid);
		वापस rc;
	पूर्ण

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_RWPIDFORWARD)
		pid = खोलो_file->pid;
	अन्यथा
		pid = current->tgid;

	rc = 0;
	server = cअगरs_pick_channel(tlink_tcon(खोलो_file->tlink)->ses);

	cअगरs_dbg(FYI, "%s: file=%p mapping=%p num_pages=%u\n",
		 __func__, file, mapping, num_pages);

	/*
	 * Start with the page at end of list and move it to निजी
	 * list. Do the same with any following pages until we hit
	 * the rsize limit, hit an index discontinuity, or run out of
	 * pages. Issue the async पढ़ो and then start the loop again
	 * until the list is empty.
	 *
	 * Note that list order is important. The page_list is in
	 * the order of declining indexes. When we put the pages in
	 * the rdata->pages, then we want them in increasing order.
	 */
	जबतक (!list_empty(page_list) && !err) अणु
		अचिन्हित पूर्णांक i, nr_pages, bytes, rsize;
		loff_t offset;
		काष्ठा page *page, *tpage;
		काष्ठा cअगरs_पढ़ोdata *rdata;
		काष्ठा cअगरs_credits credits_on_stack;
		काष्ठा cअगरs_credits *credits = &credits_on_stack;

		अगर (खोलो_file->invalidHandle) अणु
			rc = cअगरs_reखोलो_file(खोलो_file, true);
			अगर (rc == -EAGAIN)
				जारी;
			अन्यथा अगर (rc)
				अवरोध;
		पूर्ण

		rc = server->ops->रुको_mtu_credits(server, cअगरs_sb->ctx->rsize,
						   &rsize, credits);
		अगर (rc)
			अवरोध;

		/*
		 * Give up immediately अगर rsize is too small to पढ़ो an entire
		 * page. The VFS will fall back to पढ़ोpage. We should never
		 * reach this poपूर्णांक however since we set ra_pages to 0 when the
		 * rsize is smaller than a cache page.
		 */
		अगर (unlikely(rsize < PAGE_SIZE)) अणु
			add_credits_and_wake_अगर(server, credits, 0);
			मुक्त_xid(xid);
			वापस 0;
		पूर्ण

		nr_pages = 0;
		err = पढ़ोpages_get_pages(mapping, page_list, rsize, &पंचांगplist,
					 &nr_pages, &offset, &bytes);
		अगर (!nr_pages) अणु
			add_credits_and_wake_अगर(server, credits, 0);
			अवरोध;
		पूर्ण

		rdata = cअगरs_पढ़ोdata_alloc(nr_pages, cअगरs_पढ़ोv_complete);
		अगर (!rdata) अणु
			/* best to give up अगर we're out of mem */
			list_क्रम_each_entry_safe(page, tpage, &पंचांगplist, lru) अणु
				list_del(&page->lru);
				lru_cache_add(page);
				unlock_page(page);
				put_page(page);
			पूर्ण
			rc = -ENOMEM;
			add_credits_and_wake_अगर(server, credits, 0);
			अवरोध;
		पूर्ण

		rdata->cfile = cअगरsFileInfo_get(खोलो_file);
		rdata->server = server;
		rdata->mapping = mapping;
		rdata->offset = offset;
		rdata->bytes = bytes;
		rdata->pid = pid;
		rdata->pagesz = PAGE_SIZE;
		rdata->tailsz = PAGE_SIZE;
		rdata->पढ़ो_पूर्णांकo_pages = cअगरs_पढ़ोpages_पढ़ो_पूर्णांकo_pages;
		rdata->copy_पूर्णांकo_pages = cअगरs_पढ़ोpages_copy_पूर्णांकo_pages;
		rdata->credits = credits_on_stack;

		list_क्रम_each_entry_safe(page, tpage, &पंचांगplist, lru) अणु
			list_del(&page->lru);
			rdata->pages[rdata->nr_pages++] = page;
		पूर्ण

		rc = adjust_credits(server, &rdata->credits, rdata->bytes);

		अगर (!rc) अणु
			अगर (rdata->cfile->invalidHandle)
				rc = -EAGAIN;
			अन्यथा
				rc = server->ops->async_पढ़ोv(rdata);
		पूर्ण

		अगर (rc) अणु
			add_credits_and_wake_अगर(server, &rdata->credits, 0);
			क्रम (i = 0; i < rdata->nr_pages; i++) अणु
				page = rdata->pages[i];
				lru_cache_add(page);
				unlock_page(page);
				put_page(page);
			पूर्ण
			/* Fallback to the पढ़ोpage in error/reconnect हालs */
			kref_put(&rdata->refcount, cअगरs_पढ़ोdata_release);
			अवरोध;
		पूर्ण

		kref_put(&rdata->refcount, cअगरs_पढ़ोdata_release);
	पूर्ण

	/* Any pages that have been shown to fscache but didn't get added to
	 * the pagecache must be uncached beक्रमe they get वापसed to the
	 * allocator.
	 */
	cअगरs_fscache_पढ़ोpages_cancel(mapping->host, page_list);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

/*
 * cअगरs_पढ़ोpage_worker must be called with the page pinned
 */
अटल पूर्णांक cअगरs_पढ़ोpage_worker(काष्ठा file *file, काष्ठा page *page,
	loff_t *poffset)
अणु
	अक्षर *पढ़ो_data;
	पूर्णांक rc;

	/* Is the page cached? */
	rc = cअगरs_पढ़ोpage_from_fscache(file_inode(file), page);
	अगर (rc == 0)
		जाओ पढ़ो_complete;

	पढ़ो_data = kmap(page);
	/* क्रम पढ़ोs over a certain size could initiate async पढ़ो ahead */

	rc = cअगरs_पढ़ो(file, पढ़ो_data, PAGE_SIZE, poffset);

	अगर (rc < 0)
		जाओ io_error;
	अन्यथा
		cअगरs_dbg(FYI, "Bytes read %d\n", rc);

	/* we करो not want aसमय to be less than mसमय, it broke some apps */
	file_inode(file)->i_aसमय = current_समय(file_inode(file));
	अगर (बारpec64_compare(&(file_inode(file)->i_aसमय), &(file_inode(file)->i_mसमय)))
		file_inode(file)->i_aसमय = file_inode(file)->i_mसमय;
	अन्यथा
		file_inode(file)->i_aसमय = current_समय(file_inode(file));

	अगर (PAGE_SIZE > rc)
		स_रखो(पढ़ो_data + rc, 0, PAGE_SIZE - rc);

	flush_dcache_page(page);
	SetPageUptodate(page);

	/* send this page to the cache */
	cअगरs_पढ़ोpage_to_fscache(file_inode(file), page);

	rc = 0;

io_error:
	kunmap(page);
	unlock_page(page);

पढ़ो_complete:
	वापस rc;
पूर्ण

अटल पूर्णांक cअगरs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	loff_t offset = (loff_t)page->index << PAGE_SHIFT;
	पूर्णांक rc = -EACCES;
	अचिन्हित पूर्णांक xid;

	xid = get_xid();

	अगर (file->निजी_data == शून्य) अणु
		rc = -EBADF;
		मुक्त_xid(xid);
		वापस rc;
	पूर्ण

	cअगरs_dbg(FYI, "readpage %p at offset %d 0x%x\n",
		 page, (पूर्णांक)offset, (पूर्णांक)offset);

	rc = cअगरs_पढ़ोpage_worker(file, page, &offset);

	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल पूर्णांक is_inode_writable(काष्ठा cअगरsInodeInfo *cअगरs_inode)
अणु
	काष्ठा cअगरsFileInfo *खोलो_file;

	spin_lock(&cअगरs_inode->खोलो_file_lock);
	list_क्रम_each_entry(खोलो_file, &cअगरs_inode->खोलोFileList, flist) अणु
		अगर (OPEN_FMODE(खोलो_file->f_flags) & FMODE_WRITE) अणु
			spin_unlock(&cअगरs_inode->खोलो_file_lock);
			वापस 1;
		पूर्ण
	पूर्ण
	spin_unlock(&cअगरs_inode->खोलो_file_lock);
	वापस 0;
पूर्ण

/* We करो not want to update the file size from server क्रम inodes
   खोलो क्रम ग_लिखो - to aव्योम races with ग_लिखोpage extending
   the file - in the future we could consider allowing
   refreshing the inode only on increases in the file size
   but this is tricky to करो without racing with ग_लिखोbehind
   page caching in the current Linux kernel design */
bool is_size_safe_to_change(काष्ठा cअगरsInodeInfo *cअगरsInode, __u64 end_of_file)
अणु
	अगर (!cअगरsInode)
		वापस true;

	अगर (is_inode_writable(cअगरsInode)) अणु
		/* This inode is खोलो क्रम ग_लिखो at least once */
		काष्ठा cअगरs_sb_info *cअगरs_sb;

		cअगरs_sb = CIFS_SB(cअगरsInode->vfs_inode.i_sb);
		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_सूचीECT_IO) अणु
			/* since no page cache to corrupt on directio
			we can change size safely */
			वापस true;
		पूर्ण

		अगर (i_size_पढ़ो(&cअगरsInode->vfs_inode) < end_of_file)
			वापस true;

		वापस false;
	पूर्ण अन्यथा
		वापस true;
पूर्ण

अटल पूर्णांक cअगरs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक oncethru = 0;
	pgoff_t index = pos >> PAGE_SHIFT;
	loff_t offset = pos & (PAGE_SIZE - 1);
	loff_t page_start = pos & PAGE_MASK;
	loff_t i_size;
	काष्ठा page *page;
	पूर्णांक rc = 0;

	cअगरs_dbg(FYI, "write_begin from %lld len %d\n", (दीर्घ दीर्घ)pos, len);

start:
	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (PageUptodate(page))
		जाओ out;

	/*
	 * If we ग_लिखो a full page it will be up to date, no need to पढ़ो from
	 * the server. If the ग_लिखो is लघु, we'll end up करोing a sync ग_लिखो
	 * instead.
	 */
	अगर (len == PAGE_SIZE)
		जाओ out;

	/*
	 * optimize away the पढ़ो when we have an oplock, and we're not
	 * expecting to use any of the data we'd be पढ़ोing in. That
	 * is, when the page lies beyond the खातापूर्ण, or straddles the खातापूर्ण
	 * and the ग_लिखो will cover all of the existing data.
	 */
	अगर (CIFS_CACHE_READ(CIFS_I(mapping->host))) अणु
		i_size = i_size_पढ़ो(mapping->host);
		अगर (page_start >= i_size ||
		    (offset == 0 && (pos + len) >= i_size)) अणु
			zero_user_segments(page, 0, offset,
					   offset + len,
					   PAGE_SIZE);
			/*
			 * PageChecked means that the parts of the page
			 * to which we're not writing are considered up
			 * to date. Once the data is copied to the
			 * page, it can be set uptodate.
			 */
			SetPageChecked(page);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर ((file->f_flags & O_ACCMODE) != O_WRONLY && !oncethru) अणु
		/*
		 * might as well पढ़ो a page, it is fast enough. If we get
		 * an error, we करोn't need to वापस it. cअगरs_ग_लिखो_end will
		 * करो a sync ग_लिखो instead since PG_uptodate isn't set.
		 */
		cअगरs_पढ़ोpage_worker(file, page, &page_start);
		put_page(page);
		oncethru = 1;
		जाओ start;
	पूर्ण अन्यथा अणु
		/* we could try using another file handle अगर there is one -
		   but how would we lock it to prevent बंद of that handle
		   racing with this पढ़ो? In any हाल
		   this will be written out by ग_लिखो_end so is fine */
	पूर्ण
out:
	*pagep = page;
	वापस rc;
पूर्ण

अटल पूर्णांक cअगरs_release_page(काष्ठा page *page, gfp_t gfp)
अणु
	अगर (PagePrivate(page))
		वापस 0;

	वापस cअगरs_fscache_release_page(page, gfp);
पूर्ण

अटल व्योम cअगरs_invalidate_page(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				 अचिन्हित पूर्णांक length)
अणु
	काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(page->mapping->host);

	अगर (offset == 0 && length == PAGE_SIZE)
		cअगरs_fscache_invalidate_page(page, &cअगरsi->vfs_inode);
पूर्ण

अटल पूर्णांक cअगरs_launder_page(काष्ठा page *page)
अणु
	पूर्णांक rc = 0;
	loff_t range_start = page_offset(page);
	loff_t range_end = range_start + (loff_t)(PAGE_SIZE - 1);
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = WB_SYNC_ALL,
		.nr_to_ग_लिखो = 0,
		.range_start = range_start,
		.range_end = range_end,
	पूर्ण;

	cअगरs_dbg(FYI, "Launder page: %p\n", page);

	अगर (clear_page_dirty_क्रम_io(page))
		rc = cअगरs_ग_लिखोpage_locked(page, &wbc);

	cअगरs_fscache_invalidate_page(page, page->mapping->host);
	वापस rc;
पूर्ण

व्योम cअगरs_oplock_अवरोध(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cअगरsFileInfo *cfile = container_of(work, काष्ठा cअगरsFileInfo,
						  oplock_अवरोध);
	काष्ठा inode *inode = d_inode(cfile->dentry);
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(inode);
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cfile->tlink);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	पूर्णांक rc = 0;
	bool purge_cache = false;
	bool is_deferred = false;
	काष्ठा cअगरs_deferred_बंद *dबंद;

	रुको_on_bit(&cinode->flags, CIFS_INODE_PENDING_WRITERS,
			TASK_UNINTERRUPTIBLE);

	server->ops->करोwngrade_oplock(server, cinode, cfile->oplock_level,
				      cfile->oplock_epoch, &purge_cache);

	अगर (!CIFS_CACHE_WRITE(cinode) && CIFS_CACHE_READ(cinode) &&
						cअगरs_has_mand_locks(cinode)) अणु
		cअगरs_dbg(FYI, "Reset oplock to None for inode=%p due to mand locks\n",
			 inode);
		cinode->oplock = 0;
	पूर्ण

	अगर (inode && S_ISREG(inode->i_mode)) अणु
		अगर (CIFS_CACHE_READ(cinode))
			अवरोध_lease(inode, O_RDONLY);
		अन्यथा
			अवरोध_lease(inode, O_WRONLY);
		rc = filemap_fdataग_लिखो(inode->i_mapping);
		अगर (!CIFS_CACHE_READ(cinode) || purge_cache) अणु
			rc = filemap_fdataरुको(inode->i_mapping);
			mapping_set_error(inode->i_mapping, rc);
			cअगरs_zap_mapping(inode);
		पूर्ण
		cअगरs_dbg(FYI, "Oplock flush inode %p rc %d\n", inode, rc);
		अगर (CIFS_CACHE_WRITE(cinode))
			जाओ oplock_अवरोध_ack;
	पूर्ण

	rc = cअगरs_push_locks(cfile);
	अगर (rc)
		cअगरs_dbg(VFS, "Push locks rc = %d\n", rc);

oplock_अवरोध_ack:
	/*
	 * releasing stale oplock after recent reconnect of smb session using
	 * a now incorrect file handle is not a data पूर्णांकegrity issue but करो
	 * not bother sending an oplock release अगर session to server still is
	 * disconnected since oplock alपढ़ोy released by the server
	 */
	अगर (!cfile->oplock_अवरोध_cancelled) अणु
		rc = tcon->ses->server->ops->oplock_response(tcon, &cfile->fid,
							     cinode);
		cअगरs_dbg(FYI, "Oplock release rc = %d\n", rc);
	पूर्ण
	/*
	 * When oplock अवरोध is received and there are no active
	 * file handles but cached, then schedule deferred बंद immediately.
	 * So, new खोलो will not use cached handle.
	 */
	spin_lock(&CIFS_I(inode)->deferred_lock);
	is_deferred = cअगरs_is_deferred_बंद(cfile, &dबंद);
	अगर (is_deferred &&
	    cfile->deferred_बंद_scheduled &&
	    delayed_work_pending(&cfile->deferred)) अणु
		/*
		 * If there is no pending work, mod_delayed_work queues new work.
		 * So, Increase the ref count to aव्योम use-after-मुक्त.
		 */
		अगर (!mod_delayed_work(deferredबंद_wq, &cfile->deferred, 0))
			cअगरsFileInfo_get(cfile);
	पूर्ण
	spin_unlock(&CIFS_I(inode)->deferred_lock);
	_cअगरsFileInfo_put(cfile, false /* करो not रुको क्रम ourself */, false);
	cअगरs_करोne_oplock_अवरोध(cinode);
पूर्ण

/*
 * The presence of cअगरs_direct_io() in the address space ops vector
 * allowes खोलो() O_सूचीECT flags which would have failed otherwise.
 *
 * In the non-cached mode (mount with cache=none), we shunt off direct पढ़ो and ग_लिखो requests
 * so this method should never be called.
 *
 * Direct IO is not yet supported in the cached mode. 
 */
अटल sमाप_प्रकार
cअगरs_direct_io(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
        /*
         * FIXME
         * Eventually need to support direct IO क्रम non क्रमcedirectio mounts
         */
        वापस -EINVAL;
पूर्ण

अटल पूर्णांक cअगरs_swap_activate(काष्ठा swap_info_काष्ठा *sis,
			      काष्ठा file *swap_file, sector_t *span)
अणु
	काष्ठा cअगरsFileInfo *cfile = swap_file->निजी_data;
	काष्ठा inode *inode = swap_file->f_mapping->host;
	अचिन्हित दीर्घ blocks;
	दीर्घ दीर्घ isize;

	cअगरs_dbg(FYI, "swap activate\n");

	spin_lock(&inode->i_lock);
	blocks = inode->i_blocks;
	isize = inode->i_size;
	spin_unlock(&inode->i_lock);
	अगर (blocks*512 < isize) अणु
		pr_warn("swap activate: swapfile has holes\n");
		वापस -EINVAL;
	पूर्ण
	*span = sis->pages;

	pr_warn_once("Swap support over SMB3 is experimental\n");

	/*
	 * TODO: consider adding ACL (or करोcumenting how) to prevent other
	 * users (on this or other प्रणालीs) from पढ़ोing it
	 */


	/* TODO: add sk_set_meदो_स्मृति(inet) or similar */

	अगर (cfile)
		cfile->swapfile = true;
	/*
	 * TODO: Since file alपढ़ोy खोलो, we can't खोलो with DENY_ALL here
	 * but we could add call to grab a byte range lock to prevent others
	 * from पढ़ोing or writing the file
	 */

	वापस 0;
पूर्ण

अटल व्योम cअगरs_swap_deactivate(काष्ठा file *file)
अणु
	काष्ठा cअगरsFileInfo *cfile = file->निजी_data;

	cअगरs_dbg(FYI, "swap deactivate\n");

	/* TODO: unकरो sk_set_meदो_स्मृति(inet) will eventually be needed */

	अगर (cfile)
		cfile->swapfile = false;

	/* करो we need to unpin (or unlock) the file */
पूर्ण

स्थिर काष्ठा address_space_operations cअगरs_addr_ops = अणु
	.पढ़ोpage = cअगरs_पढ़ोpage,
	.पढ़ोpages = cअगरs_पढ़ोpages,
	.ग_लिखोpage = cअगरs_ग_लिखोpage,
	.ग_लिखोpages = cअगरs_ग_लिखोpages,
	.ग_लिखो_begin = cअगरs_ग_लिखो_begin,
	.ग_लिखो_end = cअगरs_ग_लिखो_end,
	.set_page_dirty = __set_page_dirty_nobuffers,
	.releasepage = cअगरs_release_page,
	.direct_IO = cअगरs_direct_io,
	.invalidatepage = cअगरs_invalidate_page,
	.launder_page = cअगरs_launder_page,
	/*
	 * TODO: investigate and अगर useful we could add an cअगरs_migratePage
	 * helper (under an CONFIG_MIGRATION) in the future, and also
	 * investigate and add an is_dirty_ग_लिखोback helper अगर needed
	 */
	.swap_activate = cअगरs_swap_activate,
	.swap_deactivate = cअगरs_swap_deactivate,
पूर्ण;

/*
 * cअगरs_पढ़ोpages requires the server to support a buffer large enough to
 * contain the header plus one complete page of data.  Otherwise, we need
 * to leave cअगरs_पढ़ोpages out of the address space operations.
 */
स्थिर काष्ठा address_space_operations cअगरs_addr_ops_smallbuf = अणु
	.पढ़ोpage = cअगरs_पढ़ोpage,
	.ग_लिखोpage = cअगरs_ग_लिखोpage,
	.ग_लिखोpages = cअगरs_ग_लिखोpages,
	.ग_लिखो_begin = cअगरs_ग_लिखो_begin,
	.ग_लिखो_end = cअगरs_ग_लिखो_end,
	.set_page_dirty = __set_page_dirty_nobuffers,
	.releasepage = cअगरs_release_page,
	.invalidatepage = cअगरs_invalidate_page,
	.launder_page = cअगरs_launder_page,
पूर्ण;
