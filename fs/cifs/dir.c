<शैली गुरु>
/*
 *   fs/cअगरs/dir.c
 *
 *   vfs operations that deal with dentries
 *
 *   Copyright (C) International Business Machines  Corp., 2002,2009
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
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/file.h>
#समावेश "cifsfs.h"
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_fs_sb.h"
#समावेश "cifs_unicode.h"
#समावेश "fs_context.h"
#समावेश "cifs_ioctl.h"

अटल व्योम
renew_parental_बारtamps(काष्ठा dentry *direntry)
अणु
	/* BB check अगर there is a way to get the kernel to करो this or अगर we
	   really need this */
	करो अणु
		cअगरs_set_समय(direntry, jअगरfies);
		direntry = direntry->d_parent;
	पूर्ण जबतक (!IS_ROOT(direntry));
पूर्ण

अक्षर *
cअगरs_build_path_to_root(काष्ठा smb3_fs_context *ctx, काष्ठा cअगरs_sb_info *cअगरs_sb,
			काष्ठा cअगरs_tcon *tcon, पूर्णांक add_treename)
अणु
	पूर्णांक pplen = ctx->prepath ? म_माप(ctx->prepath) + 1 : 0;
	पूर्णांक dfsplen;
	अक्षर *full_path = शून्य;

	/* अगर no prefix path, simply set path to the root of share to "" */
	अगर (pplen == 0) अणु
		full_path = kzalloc(1, GFP_KERNEL);
		वापस full_path;
	पूर्ण

	अगर (add_treename)
		dfsplen = strnlen(tcon->treeName, MAX_TREE_SIZE + 1);
	अन्यथा
		dfsplen = 0;

	full_path = kदो_स्मृति(dfsplen + pplen + 1, GFP_KERNEL);
	अगर (full_path == शून्य)
		वापस full_path;

	अगर (dfsplen)
		स_नकल(full_path, tcon->treeName, dfsplen);
	full_path[dfsplen] = CIFS_सूची_SEP(cअगरs_sb);
	स_नकल(full_path + dfsplen + 1, ctx->prepath, pplen);
	convert_delimiter(full_path, CIFS_सूची_SEP(cअगरs_sb));
	वापस full_path;
पूर्ण

/* Note: caller must मुक्त वापस buffer */
स्थिर अक्षर *
build_path_from_dentry(काष्ठा dentry *direntry, व्योम *page)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(direntry->d_sb);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	bool prefix = tcon->Flags & SMB_SHARE_IS_IN_DFS;

	वापस build_path_from_dentry_optional_prefix(direntry, page,
						      prefix);
पूर्ण

अक्षर *
build_path_from_dentry_optional_prefix(काष्ठा dentry *direntry, व्योम *page,
				       bool prefix)
अणु
	पूर्णांक dfsplen;
	पूर्णांक pplen = 0;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(direntry->d_sb);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	अक्षर dirsep = CIFS_सूची_SEP(cअगरs_sb);
	अक्षर *s;

	अगर (unlikely(!page))
		वापस ERR_PTR(-ENOMEM);

	अगर (prefix)
		dfsplen = strnlen(tcon->treeName, MAX_TREE_SIZE + 1);
	अन्यथा
		dfsplen = 0;

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_USE_PREFIX_PATH)
		pplen = cअगरs_sb->prepath ? म_माप(cअगरs_sb->prepath) + 1 : 0;

	s = dentry_path_raw(direntry, page, PAGE_SIZE);
	अगर (IS_ERR(s))
		वापस s;
	अगर (!s[1])	// क्रम root we want "", not "/"
		s++;
	अगर (s < (अक्षर *)page + pplen + dfsplen)
		वापस ERR_PTR(-ENAMETOOLONG);
	अगर (pplen) अणु
		cअगरs_dbg(FYI, "using cifs_sb prepath <%s>\n", cअगरs_sb->prepath);
		s -= pplen;
		स_नकल(s + 1, cअगरs_sb->prepath, pplen - 1);
		*s = '/';
	पूर्ण
	अगर (dirsep != '/') अणु
		/* BB test paths to Winकरोws with '/' in the midst of prepath */
		अक्षर *p;

		क्रम (p = s; *p; p++)
			अगर (*p == '/')
				*p = dirsep;
	पूर्ण
	अगर (dfsplen) अणु
		s -= dfsplen;
		स_नकल(s, tcon->treeName, dfsplen);
		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_POSIX_PATHS) अणु
			पूर्णांक i;
			क्रम (i = 0; i < dfsplen; i++) अणु
				अगर (s[i] == '\\')
					s[i] = '/';
			पूर्ण
		पूर्ण
	पूर्ण
	वापस s;
पूर्ण

/*
 * Don't allow path components दीर्घer than the server max.
 * Don't allow the separator अक्षरacter in a path component.
 * The VFS will not allow "/", but "\" is allowed by posix.
 */
अटल पूर्णांक
check_name(काष्ठा dentry *direntry, काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(direntry->d_sb);
	पूर्णांक i;

	अगर (unlikely(tcon->fsAttrInfo.MaxPathNameComponentLength &&
		     direntry->d_name.len >
		     le32_to_cpu(tcon->fsAttrInfo.MaxPathNameComponentLength)))
		वापस -ENAMETOOLONG;

	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_POSIX_PATHS)) अणु
		क्रम (i = 0; i < direntry->d_name.len; i++) अणु
			अगर (direntry->d_name.name[i] == '\\') अणु
				cअगरs_dbg(FYI, "Invalid file name\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/* Inode operations in similar order to how they appear in Linux file fs.h */

अटल पूर्णांक
cअगरs_करो_create(काष्ठा inode *inode, काष्ठा dentry *direntry, अचिन्हित पूर्णांक xid,
	       काष्ठा tcon_link *tlink, अचिन्हित oflags, umode_t mode,
	       __u32 *oplock, काष्ठा cअगरs_fid *fid)
अणु
	पूर्णांक rc = -ENOENT;
	पूर्णांक create_options = CREATE_NOT_सूची;
	पूर्णांक desired_access;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(tlink);
	स्थिर अक्षर *full_path;
	व्योम *page = alloc_dentry_path();
	खाता_ALL_INFO *buf = शून्य;
	काष्ठा inode *newinode = शून्य;
	पूर्णांक disposition;
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	काष्ठा cअगरs_खोलो_parms oparms;

	*oplock = 0;
	अगर (tcon->ses->server->oplocks)
		*oplock = REQ_OPLOCK;

	full_path = build_path_from_dentry(direntry, page);
	अगर (IS_ERR(full_path)) अणु
		मुक्त_dentry_path(page);
		वापस PTR_ERR(full_path);
	पूर्ण

	अगर (tcon->unix_ext && cap_unix(tcon->ses) && !tcon->broken_posix_खोलो &&
	    (CIFS_UNIX_POSIX_PATH_OPS_CAP &
			le64_to_cpu(tcon->fsUnixInfo.Capability))) अणु
		rc = cअगरs_posix_खोलो(full_path, &newinode, inode->i_sb, mode,
				     oflags, oplock, &fid->netfid, xid);
		चयन (rc) अणु
		हाल 0:
			अगर (newinode == शून्य) अणु
				/* query inode info */
				जाओ cअगरs_create_get_file_info;
			पूर्ण

			अगर (S_ISसूची(newinode->i_mode)) अणु
				CIFSSMBClose(xid, tcon, fid->netfid);
				iput(newinode);
				rc = -EISसूची;
				जाओ out;
			पूर्ण

			अगर (!S_ISREG(newinode->i_mode)) अणु
				/*
				 * The server may allow us to खोलो things like
				 * FIFOs, but the client isn't set up to deal
				 * with that. If it's not a regular file, just
				 * बंद it and proceed as अगर it were a normal
				 * lookup.
				 */
				CIFSSMBClose(xid, tcon, fid->netfid);
				जाओ cअगरs_create_get_file_info;
			पूर्ण
			/* success, no need to query */
			जाओ cअगरs_create_set_dentry;

		हाल -ENOENT:
			जाओ cअगरs_create_get_file_info;

		हाल -EIO:
		हाल -EINVAL:
			/*
			 * EIO could indicate that (posix खोलो) operation is not
			 * supported, despite what server claimed in capability
			 * negotiation.
			 *
			 * POSIX खोलो in samba versions 3.3.1 and earlier could
			 * incorrectly fail with invalid parameter.
			 */
			tcon->broken_posix_खोलो = true;
			अवरोध;

		हाल -EREMOTE:
		हाल -EOPNOTSUPP:
			/*
			 * EREMOTE indicates DFS junction, which is not handled
			 * in posix खोलो.  If either that or op not supported
			 * वापसed, follow the normal lookup.
			 */
			अवरोध;

		शेष:
			जाओ out;
		पूर्ण
		/*
		 * fallthrough to retry, using older खोलो call, this is हाल
		 * where server करोes not support this SMB level, and falsely
		 * claims capability (also get here क्रम DFS हाल which should be
		 * rare क्रम path not covered on files)
		 */
	पूर्ण

	desired_access = 0;
	अगर (OPEN_FMODE(oflags) & FMODE_READ)
		desired_access |= GENERIC_READ; /* is this too little? */
	अगर (OPEN_FMODE(oflags) & FMODE_WRITE)
		desired_access |= GENERIC_WRITE;

	disposition = खाता_OVERWRITE_IF;
	अगर ((oflags & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL))
		disposition = खाता_CREATE;
	अन्यथा अगर ((oflags & (O_CREAT | O_TRUNC)) == (O_CREAT | O_TRUNC))
		disposition = खाता_OVERWRITE_IF;
	अन्यथा अगर ((oflags & O_CREAT) == O_CREAT)
		disposition = खाता_OPEN_IF;
	अन्यथा
		cअगरs_dbg(FYI, "Create flag not set in create function\n");

	/*
	 * BB add processing to set equivalent of mode - e.g. via CreateX with
	 * ACLs
	 */

	अगर (!server->ops->खोलो) अणु
		rc = -ENOSYS;
		जाओ out;
	पूर्ण

	buf = kदो_स्मृति(माप(खाता_ALL_INFO), GFP_KERNEL);
	अगर (buf == शून्य) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * अगर we're not using unix extensions, see अगर we need to set
	 * ATTR_READONLY on the create call
	 */
	अगर (!tcon->unix_ext && (mode & S_IWUGO) == 0)
		create_options |= CREATE_OPTION_READONLY;

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = desired_access;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, create_options);
	oparms.disposition = disposition;
	oparms.path = full_path;
	oparms.fid = fid;
	oparms.reconnect = false;
	oparms.mode = mode;
	rc = server->ops->खोलो(xid, &oparms, oplock, buf);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "cifs_create returned 0x%x\n", rc);
		जाओ out;
	पूर्ण

	/*
	 * If Open reported that we actually created a file then we now have to
	 * set the mode अगर possible.
	 */
	अगर ((tcon->unix_ext) && (*oplock & CIFS_CREATE_ACTION)) अणु
		काष्ठा cअगरs_unix_set_info_args args = अणु
				.mode	= mode,
				.स_समय	= NO_CHANGE_64,
				.aसमय	= NO_CHANGE_64,
				.mसमय	= NO_CHANGE_64,
				.device	= 0,
		पूर्ण;

		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SET_UID) अणु
			args.uid = current_fsuid();
			अगर (inode->i_mode & S_ISGID)
				args.gid = inode->i_gid;
			अन्यथा
				args.gid = current_fsgid();
		पूर्ण अन्यथा अणु
			args.uid = INVALID_UID; /* no change */
			args.gid = INVALID_GID; /* no change */
		पूर्ण
		CIFSSMBUnixSetFileInfo(xid, tcon, &args, fid->netfid,
				       current->tgid);
	पूर्ण अन्यथा अणु
		/*
		 * BB implement mode setting via Winकरोws security
		 * descriptors e.g.
		 */
		/* CIFSSMBWinSetPerms(xid,tcon,path,mode,-1,-1,nls);*/

		/* Could set r/o करोs attribute अगर mode & 0222 == 0 */
	पूर्ण

cअगरs_create_get_file_info:
	/* server might mask mode so we have to query क्रम it */
	अगर (tcon->unix_ext)
		rc = cअगरs_get_inode_info_unix(&newinode, full_path, inode->i_sb,
					      xid);
	अन्यथा अणु
		/* TODO: Add support क्रम calling POSIX query info here, but passing in fid */
		rc = cअगरs_get_inode_info(&newinode, full_path, buf, inode->i_sb,
					 xid, fid);
		अगर (newinode) अणु
			अगर (server->ops->set_lease_key)
				server->ops->set_lease_key(newinode, fid);
			अगर ((*oplock & CIFS_CREATE_ACTION) && S_ISREG(newinode->i_mode)) अणु
				अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_DYNPERM)
					newinode->i_mode = mode;
				अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SET_UID) अणु
					newinode->i_uid = current_fsuid();
					अगर (inode->i_mode & S_ISGID)
						newinode->i_gid = inode->i_gid;
					अन्यथा
						newinode->i_gid = current_fsgid();
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

cअगरs_create_set_dentry:
	अगर (rc != 0) अणु
		cअगरs_dbg(FYI, "Create worked, get_inode_info failed rc = %d\n",
			 rc);
		जाओ out_err;
	पूर्ण

	अगर (S_ISसूची(newinode->i_mode)) अणु
		rc = -EISसूची;
		जाओ out_err;
	पूर्ण

	d_drop(direntry);
	d_add(direntry, newinode);

out:
	kमुक्त(buf);
	मुक्त_dentry_path(page);
	वापस rc;

out_err:
	अगर (server->ops->बंद)
		server->ops->बंद(xid, tcon, fid);
	अगर (newinode)
		iput(newinode);
	जाओ out;
पूर्ण

पूर्णांक
cअगरs_atomic_खोलो(काष्ठा inode *inode, काष्ठा dentry *direntry,
		 काष्ठा file *file, अचिन्हित oflags, umode_t mode)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक xid;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_pending_खोलो खोलो;
	__u32 oplock;
	काष्ठा cअगरsFileInfo *file_info;

	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(CIFS_SB(inode->i_sb))))
		वापस -EIO;

	/*
	 * Posix खोलो is only called (at lookup समय) क्रम file create now. For
	 * खोलोs (rather than creates), because we करो not know अगर it is a file
	 * or directory yet, and current Samba no दीर्घer allows us to करो posix
	 * खोलो on dirs, we could end up wasting an खोलो call on what turns out
	 * to be a dir. For file खोलोs, we रुको to call posix खोलो till
	 * cअगरs_खोलो.  It could be added to atomic_खोलो in the future but the
	 * perक्रमmance tradeoff of the extra network request when EISसूची or
	 * EACCES is वापसed would have to be weighed against the 50% reduction
	 * in network traffic in the other paths.
	 */
	अगर (!(oflags & O_CREAT)) अणु
		काष्ठा dentry *res;

		/*
		 * Check क्रम hashed negative dentry. We have alपढ़ोy revalidated
		 * the dentry and it is fine. No need to perक्रमm another lookup.
		 */
		अगर (!d_in_lookup(direntry))
			वापस -ENOENT;

		res = cअगरs_lookup(inode, direntry, 0);
		अगर (IS_ERR(res))
			वापस PTR_ERR(res);

		वापस finish_no_खोलो(file, res);
	पूर्ण

	xid = get_xid();

	cअगरs_dbg(FYI, "parent inode = 0x%p name is: %pd and dentry = 0x%p\n",
		 inode, direntry, direntry);

	tlink = cअगरs_sb_tlink(CIFS_SB(inode->i_sb));
	अगर (IS_ERR(tlink)) अणु
		rc = PTR_ERR(tlink);
		जाओ out_मुक्त_xid;
	पूर्ण

	tcon = tlink_tcon(tlink);

	rc = check_name(direntry, tcon);
	अगर (rc)
		जाओ out;

	server = tcon->ses->server;

	अगर (server->ops->new_lease_key)
		server->ops->new_lease_key(&fid);

	cअगरs_add_pending_खोलो(&fid, tlink, &खोलो);

	rc = cअगरs_करो_create(inode, direntry, xid, tlink, oflags, mode,
			    &oplock, &fid);

	अगर (rc) अणु
		cअगरs_del_pending_खोलो(&खोलो);
		जाओ out;
	पूर्ण

	अगर ((oflags & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL))
		file->f_mode |= FMODE_CREATED;

	rc = finish_खोलो(file, direntry, generic_file_खोलो);
	अगर (rc) अणु
		अगर (server->ops->बंद)
			server->ops->बंद(xid, tcon, &fid);
		cअगरs_del_pending_खोलो(&खोलो);
		जाओ out;
	पूर्ण

	अगर (file->f_flags & O_सूचीECT &&
	    CIFS_SB(inode->i_sb)->mnt_cअगरs_flags & CIFS_MOUNT_STRICT_IO) अणु
		अगर (CIFS_SB(inode->i_sb)->mnt_cअगरs_flags & CIFS_MOUNT_NO_BRL)
			file->f_op = &cअगरs_file_direct_nobrl_ops;
		अन्यथा
			file->f_op = &cअगरs_file_direct_ops;
		पूर्ण

	file_info = cअगरs_new_fileinfo(&fid, file, tlink, oplock);
	अगर (file_info == शून्य) अणु
		अगर (server->ops->बंद)
			server->ops->बंद(xid, tcon, &fid);
		cअगरs_del_pending_खोलो(&खोलो);
		rc = -ENOMEM;
	पूर्ण

out:
	cअगरs_put_tlink(tlink);
out_मुक्त_xid:
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

पूर्णांक cअगरs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		काष्ठा dentry *direntry, umode_t mode, bool excl)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक xid = get_xid();
	/*
	 * BB below access is probably too much क्रम mknod to request
	 *    but we have to करो query and setpathinfo so requesting
	 *    less could fail (unless we want to request getatr and setatr
	 *    permissions (only).  At least क्रम POSIX we करो not have to
	 *    request so much.
	 */
	अचिन्हित oflags = O_EXCL | O_CREAT | O_RDWR;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरs_fid fid;
	__u32 oplock;

	cअगरs_dbg(FYI, "cifs_create parent inode = 0x%p name is: %pd and dentry = 0x%p\n",
		 inode, direntry, direntry);

	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(CIFS_SB(inode->i_sb))))
		वापस -EIO;

	tlink = cअगरs_sb_tlink(CIFS_SB(inode->i_sb));
	rc = PTR_ERR(tlink);
	अगर (IS_ERR(tlink))
		जाओ out_मुक्त_xid;

	tcon = tlink_tcon(tlink);
	server = tcon->ses->server;

	अगर (server->ops->new_lease_key)
		server->ops->new_lease_key(&fid);

	rc = cअगरs_करो_create(inode, direntry, xid, tlink, oflags, mode,
			    &oplock, &fid);
	अगर (!rc && server->ops->बंद)
		server->ops->बंद(xid, tcon, &fid);

	cअगरs_put_tlink(tlink);
out_मुक्त_xid:
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

पूर्णांक cअगरs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
	       काष्ठा dentry *direntry, umode_t mode, dev_t device_number)
अणु
	पूर्णांक rc = -EPERM;
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;
	स्थिर अक्षर *full_path;
	व्योम *page;

	अगर (!old_valid_dev(device_number))
		वापस -EINVAL;

	cअगरs_sb = CIFS_SB(inode->i_sb);
	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(cअगरs_sb)))
		वापस -EIO;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);

	page = alloc_dentry_path();
	tcon = tlink_tcon(tlink);
	xid = get_xid();

	full_path = build_path_from_dentry(direntry, page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ mknod_out;
	पूर्ण

	rc = tcon->ses->server->ops->make_node(xid, inode, direntry, tcon,
					       full_path, mode,
					       device_number);

mknod_out:
	मुक्त_dentry_path(page);
	मुक्त_xid(xid);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

काष्ठा dentry *
cअगरs_lookup(काष्ठा inode *parent_dir_inode, काष्ठा dentry *direntry,
	    अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc = 0; /* to get around spurious gcc warning, set to zero here */
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *pTcon;
	काष्ठा inode *newInode = शून्य;
	स्थिर अक्षर *full_path;
	व्योम *page;

	xid = get_xid();

	cअगरs_dbg(FYI, "parent inode = 0x%p name is: %pd and dentry = 0x%p\n",
		 parent_dir_inode, direntry, direntry);

	/* check whether path exists */

	cअगरs_sb = CIFS_SB(parent_dir_inode->i_sb);
	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink)) अणु
		मुक्त_xid(xid);
		वापस ERR_CAST(tlink);
	पूर्ण
	pTcon = tlink_tcon(tlink);

	rc = check_name(direntry, pTcon);
	अगर (unlikely(rc)) अणु
		cअगरs_put_tlink(tlink);
		मुक्त_xid(xid);
		वापस ERR_PTR(rc);
	पूर्ण

	/* can not grab the नाम sem here since it would
	deadlock in the हालs (beginning of sys_नाम itself)
	in which we alपढ़ोy have the sb नाम sem */
	page = alloc_dentry_path();
	full_path = build_path_from_dentry(direntry, page);
	अगर (IS_ERR(full_path)) अणु
		cअगरs_put_tlink(tlink);
		मुक्त_xid(xid);
		मुक्त_dentry_path(page);
		वापस ERR_CAST(full_path);
	पूर्ण

	अगर (d_really_is_positive(direntry)) अणु
		cअगरs_dbg(FYI, "non-NULL inode in lookup\n");
	पूर्ण अन्यथा अणु
		cअगरs_dbg(FYI, "NULL inode in lookup\n");
	पूर्ण
	cअगरs_dbg(FYI, "Full path: %s inode = 0x%p\n",
		 full_path, d_inode(direntry));

	अगर (pTcon->posix_extensions)
		rc = smb311_posix_get_inode_info(&newInode, full_path, parent_dir_inode->i_sb, xid);
	अन्यथा अगर (pTcon->unix_ext) अणु
		rc = cअगरs_get_inode_info_unix(&newInode, full_path,
					      parent_dir_inode->i_sb, xid);
	पूर्ण अन्यथा अणु
		rc = cअगरs_get_inode_info(&newInode, full_path, शून्य,
				parent_dir_inode->i_sb, xid, शून्य);
	पूर्ण

	अगर (rc == 0) अणु
		/* since paths are not looked up by component - the parent
		   directories are presumed to be good here */
		renew_parental_बारtamps(direntry);
	पूर्ण अन्यथा अगर (rc == -ENOENT) अणु
		cअगरs_set_समय(direntry, jअगरfies);
		newInode = शून्य;
	पूर्ण अन्यथा अणु
		अगर (rc != -EACCES) अणु
			cअगरs_dbg(FYI, "Unexpected lookup error %d\n", rc);
			/* We special हाल check क्रम Access Denied - since that
			is a common वापस code */
		पूर्ण
		newInode = ERR_PTR(rc);
	पूर्ण
	मुक्त_dentry_path(page);
	cअगरs_put_tlink(tlink);
	मुक्त_xid(xid);
	वापस d_splice_alias(newInode, direntry);
पूर्ण

अटल पूर्णांक
cअगरs_d_revalidate(काष्ठा dentry *direntry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	पूर्णांक rc;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	अगर (d_really_is_positive(direntry)) अणु
		inode = d_inode(direntry);
		अगर ((flags & LOOKUP_REVAL) && !CIFS_CACHE_READ(CIFS_I(inode)))
			CIFS_I(inode)->समय = 0; /* क्रमce reval */

		rc = cअगरs_revalidate_dentry(direntry);
		अगर (rc) अणु
			cअगरs_dbg(FYI, "cifs_revalidate_dentry failed with rc=%d", rc);
			चयन (rc) अणु
			हाल -ENOENT:
			हाल -ESTALE:
				/*
				 * Those errors mean the dentry is invalid
				 * (file was deleted or recreated)
				 */
				वापस 0;
			शेष:
				/*
				 * Otherwise some unexpected error happened
				 * report it as-is to VFS layer
				 */
				वापस rc;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			/*
			 * If the inode wasn't known to be a dfs entry when
			 * the dentry was instantiated, such as when created
			 * via ->सूची_पढ़ो(), it needs to be set now since the
			 * attributes will have been updated by
			 * cअगरs_revalidate_dentry().
			 */
			अगर (IS_AUTOMOUNT(inode) &&
			   !(direntry->d_flags & DCACHE_NEED_AUTOMOUNT)) अणु
				spin_lock(&direntry->d_lock);
				direntry->d_flags |= DCACHE_NEED_AUTOMOUNT;
				spin_unlock(&direntry->d_lock);
			पूर्ण

			वापस 1;
		पूर्ण
	पूर्ण

	/*
	 * This may be nfsd (or something), anyway, we can't see the
	 * पूर्णांकent of this. So, since this can be क्रम creation, drop it.
	 */
	अगर (!flags)
		वापस 0;

	/*
	 * Drop the negative dentry, in order to make sure to use the
	 * हाल sensitive name which is specअगरied by user अगर this is
	 * क्रम creation.
	 */
	अगर (flags & (LOOKUP_CREATE | LOOKUP_RENAME_TARGET))
		वापस 0;

	अगर (समय_after(jअगरfies, cअगरs_get_समय(direntry) + HZ) || !lookupCacheEnabled)
		वापस 0;

	वापस 1;
पूर्ण

/* अटल पूर्णांक cअगरs_d_delete(काष्ठा dentry *direntry)
अणु
	पूर्णांक rc = 0;

	cअगरs_dbg(FYI, "In cifs d_delete, name = %pd\n", direntry);

	वापस rc;
पूर्ण     */

स्थिर काष्ठा dentry_operations cअगरs_dentry_ops = अणु
	.d_revalidate = cअगरs_d_revalidate,
	.d_स्वतःmount = cअगरs_dfs_d_स्वतःmount,
/* d_delete:       cअगरs_d_delete,      */ /* not needed except क्रम debugging */
पूर्ण;

अटल पूर्णांक cअगरs_ci_hash(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *q)
अणु
	काष्ठा nls_table *codepage = CIFS_SB(dentry->d_sb)->local_nls;
	अचिन्हित दीर्घ hash;
	ब_अक्षर_प्रकार c;
	पूर्णांक i, अक्षरlen;

	hash = init_name_hash(dentry);
	क्रम (i = 0; i < q->len; i += अक्षरlen) अणु
		अक्षरlen = codepage->अक्षर2uni(&q->name[i], q->len - i, &c);
		/* error out अगर we can't convert the अक्षरacter */
		अगर (unlikely(अक्षरlen < 0))
			वापस अक्षरlen;
		hash = partial_name_hash(cअगरs_बड़े(c), hash);
	पूर्ण
	q->hash = end_name_hash(hash);

	वापस 0;
पूर्ण

अटल पूर्णांक cअगरs_ci_compare(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा nls_table *codepage = CIFS_SB(dentry->d_sb)->local_nls;
	ब_अक्षर_प्रकार c1, c2;
	पूर्णांक i, l1, l2;

	/*
	 * We make the assumption here that upperहाल अक्षरacters in the local
	 * codepage are always the same length as their lowerहाल counterparts.
	 *
	 * If that's ever not the हाल, then this will fail to match it.
	 */
	अगर (name->len != len)
		वापस 1;

	क्रम (i = 0; i < len; i += l1) अणु
		/* Convert अक्षरacters in both strings to UTF-16. */
		l1 = codepage->अक्षर2uni(&str[i], len - i, &c1);
		l2 = codepage->अक्षर2uni(&name->name[i], name->len - i, &c2);

		/*
		 * If we can't convert either अक्षरacter, just declare it to
		 * be 1 byte दीर्घ and compare the original byte.
		 */
		अगर (unlikely(l1 < 0 && l2 < 0)) अणु
			अगर (str[i] != name->name[i])
				वापस 1;
			l1 = 1;
			जारी;
		पूर्ण

		/*
		 * Here, we again ass|u|me that upper/lowerहाल versions of
		 * a अक्षरacter are the same length in the local NLS.
		 */
		अगर (l1 != l2)
			वापस 1;

		/* Now compare upperहाल versions of these अक्षरacters */
		अगर (cअगरs_बड़े(c1) != cअगरs_बड़े(c2))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा dentry_operations cअगरs_ci_dentry_ops = अणु
	.d_revalidate = cअगरs_d_revalidate,
	.d_hash = cअगरs_ci_hash,
	.d_compare = cअगरs_ci_compare,
	.d_स्वतःmount = cअगरs_dfs_d_स्वतःmount,
पूर्ण;
