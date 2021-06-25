<शैली गुरु>
/*
 *   fs/cअगरs/inode.c
 *
 *   Copyright (C) International Business Machines  Corp., 2002,2010
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
#समावेश <linux/pagemap.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/रुको_bit.h>
#समावेश <linux/fiemap.h>
#समावेश <यंत्र/भाग64.h>
#समावेश "cifsfs.h"
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "smb2proto.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_fs_sb.h"
#समावेश "cifs_unicode.h"
#समावेश "fscache.h"
#समावेश "fs_context.h"
#समावेश "cifs_ioctl.h"

अटल व्योम cअगरs_set_ops(काष्ठा inode *inode)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);

	चयन (inode->i_mode & S_IFMT) अणु
	हाल S_IFREG:
		inode->i_op = &cअगरs_file_inode_ops;
		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_सूचीECT_IO) अणु
			अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_BRL)
				inode->i_fop = &cअगरs_file_direct_nobrl_ops;
			अन्यथा
				inode->i_fop = &cअगरs_file_direct_ops;
		पूर्ण अन्यथा अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_STRICT_IO) अणु
			अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_BRL)
				inode->i_fop = &cअगरs_file_strict_nobrl_ops;
			अन्यथा
				inode->i_fop = &cअगरs_file_strict_ops;
		पूर्ण अन्यथा अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_BRL)
			inode->i_fop = &cअगरs_file_nobrl_ops;
		अन्यथा अणु /* not direct, send byte range locks */
			inode->i_fop = &cअगरs_file_ops;
		पूर्ण

		/* check अगर server can support पढ़ोpages */
		अगर (cअगरs_sb_master_tcon(cअगरs_sb)->ses->server->max_पढ़ो <
				PAGE_SIZE + MAX_CIFS_HDR_SIZE)
			inode->i_data.a_ops = &cअगरs_addr_ops_smallbuf;
		अन्यथा
			inode->i_data.a_ops = &cअगरs_addr_ops;
		अवरोध;
	हाल S_IFसूची:
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
		अगर (IS_AUTOMOUNT(inode)) अणु
			inode->i_op = &cअगरs_dfs_referral_inode_operations;
		पूर्ण अन्यथा अणु
#अन्यथा /* NO DFS support, treat as a directory */
		अणु
#पूर्ण_अगर
			inode->i_op = &cअगरs_dir_inode_ops;
			inode->i_fop = &cअगरs_dir_ops;
		पूर्ण
		अवरोध;
	हाल S_IFLNK:
		inode->i_op = &cअगरs_symlink_inode_ops;
		अवरोध;
	शेष:
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
		अवरोध;
	पूर्ण
पूर्ण

/* check inode attributes against fattr. If they करोn't match, tag the
 * inode क्रम cache invalidation
 */
अटल व्योम
cअगरs_revalidate_cache(काष्ठा inode *inode, काष्ठा cअगरs_fattr *fattr)
अणु
	काष्ठा cअगरsInodeInfo *cअगरs_i = CIFS_I(inode);

	cअगरs_dbg(FYI, "%s: revalidating inode %llu\n",
		 __func__, cअगरs_i->uniqueid);

	अगर (inode->i_state & I_NEW) अणु
		cअगरs_dbg(FYI, "%s: inode %llu is new\n",
			 __func__, cअगरs_i->uniqueid);
		वापस;
	पूर्ण

	/* करोn't bother with revalidation अगर we have an oplock */
	अगर (CIFS_CACHE_READ(cअगरs_i)) अणु
		cअगरs_dbg(FYI, "%s: inode %llu is oplocked\n",
			 __func__, cअगरs_i->uniqueid);
		वापस;
	पूर्ण

	 /* revalidate अगर mसमय or size have changed */
	fattr->cf_mसमय = बारtamp_truncate(fattr->cf_mसमय, inode);
	अगर (बारpec64_equal(&inode->i_mसमय, &fattr->cf_mसमय) &&
	    cअगरs_i->server_eof == fattr->cf_eof) अणु
		cअगरs_dbg(FYI, "%s: inode %llu is unchanged\n",
			 __func__, cअगरs_i->uniqueid);
		वापस;
	पूर्ण

	cअगरs_dbg(FYI, "%s: invalidating inode %llu mapping\n",
		 __func__, cअगरs_i->uniqueid);
	set_bit(CIFS_INO_INVALID_MAPPING, &cअगरs_i->flags);
पूर्ण

/*
 * copy nlink to the inode, unless it wasn't provided.  Provide
 * sane values अगर we करोn't have an existing one and none was provided
 */
अटल व्योम
cअगरs_nlink_fattr_to_inode(काष्ठा inode *inode, काष्ठा cअगरs_fattr *fattr)
अणु
	/*
	 * अगर we're in a situation where we can't trust what we
	 * got from the server (सूची_पढ़ो, some non-unix हालs)
	 * fake reasonable values
	 */
	अगर (fattr->cf_flags & CIFS_FATTR_UNKNOWN_NLINK) अणु
		/* only provide fake values on a new inode */
		अगर (inode->i_state & I_NEW) अणु
			अगर (fattr->cf_cअगरsattrs & ATTR_सूचीECTORY)
				set_nlink(inode, 2);
			अन्यथा
				set_nlink(inode, 1);
		पूर्ण
		वापस;
	पूर्ण

	/* we trust the server, so update it */
	set_nlink(inode, fattr->cf_nlink);
पूर्ण

/* populate an inode with info from a cअगरs_fattr काष्ठा */
पूर्णांक
cअगरs_fattr_to_inode(काष्ठा inode *inode, काष्ठा cअगरs_fattr *fattr)
अणु
	काष्ठा cअगरsInodeInfo *cअगरs_i = CIFS_I(inode);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);

	अगर (!(inode->i_state & I_NEW) &&
	    unlikely(inode_wrong_type(inode, fattr->cf_mode))) अणु
		CIFS_I(inode)->समय = 0; /* क्रमce reval */
		वापस -ESTALE;
	पूर्ण

	cअगरs_revalidate_cache(inode, fattr);

	spin_lock(&inode->i_lock);
	fattr->cf_mसमय = बारtamp_truncate(fattr->cf_mसमय, inode);
	fattr->cf_aसमय = बारtamp_truncate(fattr->cf_aसमय, inode);
	fattr->cf_स_समय = बारtamp_truncate(fattr->cf_स_समय, inode);
	/* we करो not want aसमय to be less than mसमय, it broke some apps */
	अगर (बारpec64_compare(&fattr->cf_aसमय, &fattr->cf_mसमय) < 0)
		inode->i_aसमय = fattr->cf_mसमय;
	अन्यथा
		inode->i_aसमय = fattr->cf_aसमय;
	inode->i_mसमय = fattr->cf_mसमय;
	inode->i_स_समय = fattr->cf_स_समय;
	inode->i_rdev = fattr->cf_rdev;
	cअगरs_nlink_fattr_to_inode(inode, fattr);
	inode->i_uid = fattr->cf_uid;
	inode->i_gid = fattr->cf_gid;

	/* अगर dynperm is set, करोn't clobber existing mode */
	अगर (inode->i_state & I_NEW ||
	    !(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_DYNPERM))
		inode->i_mode = fattr->cf_mode;

	cअगरs_i->cअगरsAttrs = fattr->cf_cअगरsattrs;

	अगर (fattr->cf_flags & CIFS_FATTR_NEED_REVAL)
		cअगरs_i->समय = 0;
	अन्यथा
		cअगरs_i->समय = jअगरfies;

	अगर (fattr->cf_flags & CIFS_FATTR_DELETE_PENDING)
		set_bit(CIFS_INO_DELETE_PENDING, &cअगरs_i->flags);
	अन्यथा
		clear_bit(CIFS_INO_DELETE_PENDING, &cअगरs_i->flags);

	cअगरs_i->server_eof = fattr->cf_eof;
	/*
	 * Can't safely change the file size here अगर the client is writing to
	 * it due to potential races.
	 */
	अगर (is_size_safe_to_change(cअगरs_i, fattr->cf_eof)) अणु
		i_size_ग_लिखो(inode, fattr->cf_eof);

		/*
		 * i_blocks is not related to (i_size / i_blksize),
		 * but instead 512 byte (2**9) size is required क्रम
		 * calculating num blocks.
		 */
		inode->i_blocks = (512 - 1 + fattr->cf_bytes) >> 9;
	पूर्ण
	spin_unlock(&inode->i_lock);

	अगर (fattr->cf_flags & CIFS_FATTR_DFS_REFERRAL)
		inode->i_flags |= S_AUTOMOUNT;
	अगर (inode->i_state & I_NEW)
		cअगरs_set_ops(inode);
	वापस 0;
पूर्ण

व्योम
cअगरs_fill_uniqueid(काष्ठा super_block *sb, काष्ठा cअगरs_fattr *fattr)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM)
		वापस;

	fattr->cf_uniqueid = iunique(sb, ROOT_I);
पूर्ण

/* Fill a cअगरs_fattr काष्ठा with info from खाता_UNIX_BASIC_INFO. */
व्योम
cअगरs_unix_basic_to_fattr(काष्ठा cअगरs_fattr *fattr, खाता_UNIX_BASIC_INFO *info,
			 काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	स_रखो(fattr, 0, माप(*fattr));
	fattr->cf_uniqueid = le64_to_cpu(info->UniqueId);
	fattr->cf_bytes = le64_to_cpu(info->NumOfBytes);
	fattr->cf_eof = le64_to_cpu(info->EndOfFile);

	fattr->cf_aसमय = cअगरs_NTसमयToUnix(info->LastAccessTime);
	fattr->cf_mसमय = cअगरs_NTसमयToUnix(info->LastModअगरicationTime);
	fattr->cf_स_समय = cअगरs_NTसमयToUnix(info->LastStatusChange);
	/* old POSIX extensions करोn't get create समय */

	fattr->cf_mode = le64_to_cpu(info->Permissions);

	/*
	 * Since we set the inode type below we need to mask off
	 * to aव्योम strange results अगर bits set above.
	 */
	fattr->cf_mode &= ~S_IFMT;
	चयन (le32_to_cpu(info->Type)) अणु
	हाल UNIX_खाता:
		fattr->cf_mode |= S_IFREG;
		fattr->cf_dtype = DT_REG;
		अवरोध;
	हाल UNIX_SYMLINK:
		fattr->cf_mode |= S_IFLNK;
		fattr->cf_dtype = DT_LNK;
		अवरोध;
	हाल UNIX_सूची:
		fattr->cf_mode |= S_IFसूची;
		fattr->cf_dtype = DT_सूची;
		अवरोध;
	हाल UNIX_CHARDEV:
		fattr->cf_mode |= S_IFCHR;
		fattr->cf_dtype = DT_CHR;
		fattr->cf_rdev = MKDEV(le64_to_cpu(info->DevMajor),
				       le64_to_cpu(info->DevMinor) & MINORMASK);
		अवरोध;
	हाल UNIX_BLOCKDEV:
		fattr->cf_mode |= S_IFBLK;
		fattr->cf_dtype = DT_BLK;
		fattr->cf_rdev = MKDEV(le64_to_cpu(info->DevMajor),
				       le64_to_cpu(info->DevMinor) & MINORMASK);
		अवरोध;
	हाल UNIX_FIFO:
		fattr->cf_mode |= S_IFIFO;
		fattr->cf_dtype = DT_FIFO;
		अवरोध;
	हाल UNIX_SOCKET:
		fattr->cf_mode |= S_IFSOCK;
		fattr->cf_dtype = DT_SOCK;
		अवरोध;
	शेष:
		/* safest to call it a file अगर we करो not know */
		fattr->cf_mode |= S_IFREG;
		fattr->cf_dtype = DT_REG;
		cअगरs_dbg(FYI, "unknown type %d\n", le32_to_cpu(info->Type));
		अवरोध;
	पूर्ण

	fattr->cf_uid = cअगरs_sb->ctx->linux_uid;
	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_OVERR_UID)) अणु
		u64 id = le64_to_cpu(info->Uid);
		अगर (id < ((uid_t)-1)) अणु
			kuid_t uid = make_kuid(&init_user_ns, id);
			अगर (uid_valid(uid))
				fattr->cf_uid = uid;
		पूर्ण
	पूर्ण
	
	fattr->cf_gid = cअगरs_sb->ctx->linux_gid;
	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_OVERR_GID)) अणु
		u64 id = le64_to_cpu(info->Gid);
		अगर (id < ((gid_t)-1)) अणु
			kgid_t gid = make_kgid(&init_user_ns, id);
			अगर (gid_valid(gid))
				fattr->cf_gid = gid;
		पूर्ण
	पूर्ण

	fattr->cf_nlink = le64_to_cpu(info->Nlinks);
पूर्ण

/*
 * Fill a cअगरs_fattr काष्ठा with fake inode info.
 *
 * Needed to setup cअगरs_fattr data क्रम the directory which is the
 * junction to the new submount (ie to setup the fake directory
 * which represents a DFS referral).
 */
अटल व्योम
cअगरs_create_dfs_fattr(काष्ठा cअगरs_fattr *fattr, काष्ठा super_block *sb)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);

	cअगरs_dbg(FYI, "creating fake fattr for DFS referral\n");

	स_रखो(fattr, 0, माप(*fattr));
	fattr->cf_mode = S_IFसूची | S_IXUGO | S_IRWXU;
	fattr->cf_uid = cअगरs_sb->ctx->linux_uid;
	fattr->cf_gid = cअगरs_sb->ctx->linux_gid;
	kसमय_get_coarse_real_ts64(&fattr->cf_mसमय);
	fattr->cf_aसमय = fattr->cf_स_समय = fattr->cf_mसमय;
	fattr->cf_nlink = 2;
	fattr->cf_flags = CIFS_FATTR_DFS_REFERRAL;
पूर्ण

अटल पूर्णांक
cअगरs_get_file_info_unix(काष्ठा file *filp)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक xid;
	खाता_UNIX_BASIC_INFO find_data;
	काष्ठा cअगरs_fattr fattr;
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा cअगरsFileInfo *cfile = filp->निजी_data;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cfile->tlink);

	xid = get_xid();
	rc = CIFSSMBUnixQFileInfo(xid, tcon, cfile->fid.netfid, &find_data);
	अगर (!rc) अणु
		cअगरs_unix_basic_to_fattr(&fattr, &find_data, cअगरs_sb);
	पूर्ण अन्यथा अगर (rc == -EREMOTE) अणु
		cअगरs_create_dfs_fattr(&fattr, inode->i_sb);
		rc = 0;
	पूर्ण

	rc = cअगरs_fattr_to_inode(inode, &fattr);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

पूर्णांक cअगरs_get_inode_info_unix(काष्ठा inode **pinode,
			     स्थिर अचिन्हित अक्षर *full_path,
			     काष्ठा super_block *sb, अचिन्हित पूर्णांक xid)
अणु
	पूर्णांक rc;
	खाता_UNIX_BASIC_INFO find_data;
	काष्ठा cअगरs_fattr fattr;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);

	cअगरs_dbg(FYI, "Getting info on %s\n", full_path);

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);

	/* could have करोne a find first instead but this वापसs more info */
	rc = CIFSSMBUnixQPathInfo(xid, tcon, full_path, &find_data,
				  cअगरs_sb->local_nls, cअगरs_remap(cअगरs_sb));
	cअगरs_put_tlink(tlink);

	अगर (!rc) अणु
		cअगरs_unix_basic_to_fattr(&fattr, &find_data, cअगरs_sb);
	पूर्ण अन्यथा अगर (rc == -EREMOTE) अणु
		cअगरs_create_dfs_fattr(&fattr, sb);
		rc = 0;
	पूर्ण अन्यथा अणु
		वापस rc;
	पूर्ण

	/* check क्रम Minshall+French symlinks */
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MF_SYMLINKS) अणु
		पूर्णांक पंचांगprc = check_mf_symlink(xid, tcon, cअगरs_sb, &fattr,
					     full_path);
		अगर (पंचांगprc)
			cअगरs_dbg(FYI, "check_mf_symlink: %d\n", पंचांगprc);
	पूर्ण

	अगर (*pinode == शून्य) अणु
		/* get new inode */
		cअगरs_fill_uniqueid(sb, &fattr);
		*pinode = cअगरs_iget(sb, &fattr);
		अगर (!*pinode)
			rc = -ENOMEM;
	पूर्ण अन्यथा अणु
		/* we alपढ़ोy have inode, update it */

		/* अगर uniqueid is dअगरferent, वापस error */
		अगर (unlikely(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM &&
		    CIFS_I(*pinode)->uniqueid != fattr.cf_uniqueid)) अणु
			CIFS_I(*pinode)->समय = 0; /* क्रमce reval */
			rc = -ESTALE;
			जाओ cgiiu_निकास;
		पूर्ण

		/* अगर filetype is dअगरferent, वापस error */
		rc = cअगरs_fattr_to_inode(*pinode, &fattr);
	पूर्ण

cgiiu_निकास:
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_sfu_type(काष्ठा cअगरs_fattr *fattr, स्थिर अक्षर *path,
	      काष्ठा cअगरs_sb_info *cअगरs_sb, अचिन्हित पूर्णांक xid)
अणु
	पूर्णांक rc;
	__u32 oplock;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_io_parms io_parms = अणु0पूर्ण;
	अक्षर buf[24];
	अचिन्हित पूर्णांक bytes_पढ़ो;
	अक्षर *pbuf;
	पूर्णांक buf_type = CIFS_NO_BUFFER;

	pbuf = buf;

	fattr->cf_mode &= ~S_IFMT;

	अगर (fattr->cf_eof == 0) अणु
		fattr->cf_mode |= S_IFIFO;
		fattr->cf_dtype = DT_FIFO;
		वापस 0;
	पूर्ण अन्यथा अगर (fattr->cf_eof < 8) अणु
		fattr->cf_mode |= S_IFREG;
		fattr->cf_dtype = DT_REG;
		वापस -EINVAL;	 /* EOPNOTSUPP? */
	पूर्ण

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = GENERIC_READ;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, CREATE_NOT_सूची);
	oparms.disposition = खाता_OPEN;
	oparms.path = path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	अगर (tcon->ses->server->oplocks)
		oplock = REQ_OPLOCK;
	अन्यथा
		oplock = 0;
	rc = tcon->ses->server->ops->खोलो(xid, &oparms, &oplock, शून्य);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "check sfu type of %s, open rc = %d\n", path, rc);
		cअगरs_put_tlink(tlink);
		वापस rc;
	पूर्ण

	/* Read header */
	io_parms.netfid = fid.netfid;
	io_parms.pid = current->tgid;
	io_parms.tcon = tcon;
	io_parms.offset = 0;
	io_parms.length = 24;

	rc = tcon->ses->server->ops->sync_पढ़ो(xid, &fid, &io_parms,
					&bytes_पढ़ो, &pbuf, &buf_type);
	अगर ((rc == 0) && (bytes_पढ़ो >= 8)) अणु
		अगर (स_भेद("IntxBLK", pbuf, 8) == 0) अणु
			cअगरs_dbg(FYI, "Block device\n");
			fattr->cf_mode |= S_IFBLK;
			fattr->cf_dtype = DT_BLK;
			अगर (bytes_पढ़ो == 24) अणु
				/* we have enough to decode dev num */
				__u64 mjr; /* major */
				__u64 mnr; /* minor */
				mjr = le64_to_cpu(*(__le64 *)(pbuf+8));
				mnr = le64_to_cpu(*(__le64 *)(pbuf+16));
				fattr->cf_rdev = MKDEV(mjr, mnr);
			पूर्ण
		पूर्ण अन्यथा अगर (स_भेद("IntxCHR", pbuf, 8) == 0) अणु
			cअगरs_dbg(FYI, "Char device\n");
			fattr->cf_mode |= S_IFCHR;
			fattr->cf_dtype = DT_CHR;
			अगर (bytes_पढ़ो == 24) अणु
				/* we have enough to decode dev num */
				__u64 mjr; /* major */
				__u64 mnr; /* minor */
				mjr = le64_to_cpu(*(__le64 *)(pbuf+8));
				mnr = le64_to_cpu(*(__le64 *)(pbuf+16));
				fattr->cf_rdev = MKDEV(mjr, mnr);
			पूर्ण
		पूर्ण अन्यथा अगर (स_भेद("IntxLNK", pbuf, 7) == 0) अणु
			cअगरs_dbg(FYI, "Symlink\n");
			fattr->cf_mode |= S_IFLNK;
			fattr->cf_dtype = DT_LNK;
		पूर्ण अन्यथा अणु
			fattr->cf_mode |= S_IFREG; /* file? */
			fattr->cf_dtype = DT_REG;
			rc = -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		fattr->cf_mode |= S_IFREG; /* then it is a file */
		fattr->cf_dtype = DT_REG;
		rc = -EOPNOTSUPP; /* or some unknown SFU type */
	पूर्ण

	tcon->ses->server->ops->बंद(xid, tcon, &fid);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

#घोषणा SFBITS_MASK (S_ISVTX | S_ISGID | S_ISUID)  /* SETखाताBITS valid bits */

/*
 * Fetch mode bits as provided by SFU.
 *
 * FIXME: Doesn't this clobber the type bit we got from cअगरs_sfu_type ?
 */
अटल पूर्णांक cअगरs_sfu_mode(काष्ठा cअगरs_fattr *fattr, स्थिर अचिन्हित अक्षर *path,
			 काष्ठा cअगरs_sb_info *cअगरs_sb, अचिन्हित पूर्णांक xid)
अणु
#अगर_घोषित CONFIG_CIFS_XATTR
	sमाप_प्रकार rc;
	अक्षर ea_value[4];
	__u32 mode;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);

	अगर (tcon->ses->server->ops->query_all_EAs == शून्य) अणु
		cअगरs_put_tlink(tlink);
		वापस -EOPNOTSUPP;
	पूर्ण

	rc = tcon->ses->server->ops->query_all_EAs(xid, tcon, path,
			"SETFILEBITS", ea_value, 4 /* size of buf */,
			cअगरs_sb);
	cअगरs_put_tlink(tlink);
	अगर (rc < 0)
		वापस (पूर्णांक)rc;
	अन्यथा अगर (rc > 3) अणु
		mode = le32_to_cpu(*((__le32 *)ea_value));
		fattr->cf_mode &= ~SFBITS_MASK;
		cअगरs_dbg(FYI, "special bits 0%o org mode 0%o\n",
			 mode, fattr->cf_mode);
		fattr->cf_mode = (mode & SFBITS_MASK) | fattr->cf_mode;
		cअगरs_dbg(FYI, "special mode bits 0%o\n", mode);
	पूर्ण

	वापस 0;
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

/* Fill a cअगरs_fattr काष्ठा with info from POSIX info काष्ठा */
अटल व्योम
smb311_posix_info_to_fattr(काष्ठा cअगरs_fattr *fattr, काष्ठा smb311_posix_qinfo *info,
			   काष्ठा super_block *sb, bool adjust_tz, bool symlink)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);

	स_रखो(fattr, 0, माप(*fattr));

	/* no fattr->flags to set */
	fattr->cf_cअगरsattrs = le32_to_cpu(info->DosAttributes);
	fattr->cf_uniqueid = le64_to_cpu(info->Inode);

	अगर (info->LastAccessTime)
		fattr->cf_aसमय = cअगरs_NTसमयToUnix(info->LastAccessTime);
	अन्यथा
		kसमय_get_coarse_real_ts64(&fattr->cf_aसमय);

	fattr->cf_स_समय = cअगरs_NTसमयToUnix(info->ChangeTime);
	fattr->cf_mसमय = cअगरs_NTसमयToUnix(info->LastWriteTime);

	अगर (adjust_tz) अणु
		fattr->cf_स_समय.tv_sec += tcon->ses->server->समयAdj;
		fattr->cf_mसमय.tv_sec += tcon->ses->server->समयAdj;
	पूर्ण

	fattr->cf_eof = le64_to_cpu(info->EndOfFile);
	fattr->cf_bytes = le64_to_cpu(info->AllocationSize);
	fattr->cf_createसमय = le64_to_cpu(info->CreationTime);

	fattr->cf_nlink = le32_to_cpu(info->HardLinks);
	fattr->cf_mode = (umode_t) le32_to_cpu(info->Mode);
	/* The srv fs device id is overridden on network mount so setting rdev isn't needed here */
	/* fattr->cf_rdev = le32_to_cpu(info->DeviceId); */

	अगर (symlink) अणु
		fattr->cf_mode |= S_IFLNK;
		fattr->cf_dtype = DT_LNK;
	पूर्ण अन्यथा अगर (fattr->cf_cअगरsattrs & ATTR_सूचीECTORY) अणु
		fattr->cf_mode |= S_IFसूची;
		fattr->cf_dtype = DT_सूची;
	पूर्ण अन्यथा अणु /* file */
		fattr->cf_mode |= S_IFREG;
		fattr->cf_dtype = DT_REG;
	पूर्ण
	/* अन्यथा अगर reparse poपूर्णांक ... TODO: add support क्रम FIFO and blk dev; special file types */

	fattr->cf_uid = cअगरs_sb->ctx->linux_uid; /* TODO: map uid and gid from SID */
	fattr->cf_gid = cअगरs_sb->ctx->linux_gid;

	cअगरs_dbg(FYI, "POSIX query info: mode 0x%x uniqueid 0x%llx nlink %d\n",
		fattr->cf_mode, fattr->cf_uniqueid, fattr->cf_nlink);
पूर्ण


/* Fill a cअगरs_fattr काष्ठा with info from खाता_ALL_INFO */
अटल व्योम
cअगरs_all_info_to_fattr(काष्ठा cअगरs_fattr *fattr, खाता_ALL_INFO *info,
		       काष्ठा super_block *sb, bool adjust_tz,
		       bool symlink, u32 reparse_tag)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);

	स_रखो(fattr, 0, माप(*fattr));
	fattr->cf_cअगरsattrs = le32_to_cpu(info->Attributes);
	अगर (info->DeletePending)
		fattr->cf_flags |= CIFS_FATTR_DELETE_PENDING;

	अगर (info->LastAccessTime)
		fattr->cf_aसमय = cअगरs_NTसमयToUnix(info->LastAccessTime);
	अन्यथा
		kसमय_get_coarse_real_ts64(&fattr->cf_aसमय);

	fattr->cf_स_समय = cअगरs_NTसमयToUnix(info->ChangeTime);
	fattr->cf_mसमय = cअगरs_NTसमयToUnix(info->LastWriteTime);

	अगर (adjust_tz) अणु
		fattr->cf_स_समय.tv_sec += tcon->ses->server->समयAdj;
		fattr->cf_mसमय.tv_sec += tcon->ses->server->समयAdj;
	पूर्ण

	fattr->cf_eof = le64_to_cpu(info->EndOfFile);
	fattr->cf_bytes = le64_to_cpu(info->AllocationSize);
	fattr->cf_createसमय = le64_to_cpu(info->CreationTime);

	fattr->cf_nlink = le32_to_cpu(info->NumberOfLinks);
	अगर (reparse_tag == IO_REPARSE_TAG_LX_SYMLINK) अणु
		fattr->cf_mode |= S_IFLNK | cअगरs_sb->ctx->file_mode;
		fattr->cf_dtype = DT_LNK;
	पूर्ण अन्यथा अगर (reparse_tag == IO_REPARSE_TAG_LX_FIFO) अणु
		fattr->cf_mode |= S_IFIFO | cअगरs_sb->ctx->file_mode;
		fattr->cf_dtype = DT_FIFO;
	पूर्ण अन्यथा अगर (reparse_tag == IO_REPARSE_TAG_AF_UNIX) अणु
		fattr->cf_mode |= S_IFSOCK | cअगरs_sb->ctx->file_mode;
		fattr->cf_dtype = DT_SOCK;
	पूर्ण अन्यथा अगर (reparse_tag == IO_REPARSE_TAG_LX_CHR) अणु
		fattr->cf_mode |= S_IFCHR | cअगरs_sb->ctx->file_mode;
		fattr->cf_dtype = DT_CHR;
	पूर्ण अन्यथा अगर (reparse_tag == IO_REPARSE_TAG_LX_BLK) अणु
		fattr->cf_mode |= S_IFBLK | cअगरs_sb->ctx->file_mode;
		fattr->cf_dtype = DT_BLK;
	पूर्ण अन्यथा अगर (symlink) अणु /* TODO add more reparse tag checks */
		fattr->cf_mode = S_IFLNK;
		fattr->cf_dtype = DT_LNK;
	पूर्ण अन्यथा अगर (fattr->cf_cअगरsattrs & ATTR_सूचीECTORY) अणु
		fattr->cf_mode = S_IFसूची | cअगरs_sb->ctx->dir_mode;
		fattr->cf_dtype = DT_सूची;
		/*
		 * Server can वापस wrong NumberOfLinks value क्रम directories
		 * when Unix extensions are disabled - fake it.
		 */
		अगर (!tcon->unix_ext)
			fattr->cf_flags |= CIFS_FATTR_UNKNOWN_NLINK;
	पूर्ण अन्यथा अणु
		fattr->cf_mode = S_IFREG | cअगरs_sb->ctx->file_mode;
		fattr->cf_dtype = DT_REG;

		/* clear ग_लिखो bits अगर ATTR_READONLY is set */
		अगर (fattr->cf_cअगरsattrs & ATTR_READONLY)
			fattr->cf_mode &= ~(S_IWUGO);

		/*
		 * Don't accept zero nlink from non-unix servers unless
		 * delete is pending.  Instead mark it as unknown.
		 */
		अगर ((fattr->cf_nlink < 1) && !tcon->unix_ext &&
		    !info->DeletePending) अणु
			cअगरs_dbg(VFS, "bogus file nlink value %u\n",
				 fattr->cf_nlink);
			fattr->cf_flags |= CIFS_FATTR_UNKNOWN_NLINK;
		पूर्ण
	पूर्ण

	fattr->cf_uid = cअगरs_sb->ctx->linux_uid;
	fattr->cf_gid = cअगरs_sb->ctx->linux_gid;
पूर्ण

अटल पूर्णांक
cअगरs_get_file_info(काष्ठा file *filp)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक xid;
	खाता_ALL_INFO find_data;
	काष्ठा cअगरs_fattr fattr;
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा cअगरsFileInfo *cfile = filp->निजी_data;
	काष्ठा cअगरs_tcon *tcon = tlink_tcon(cfile->tlink);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;

	अगर (!server->ops->query_file_info)
		वापस -ENOSYS;

	xid = get_xid();
	rc = server->ops->query_file_info(xid, tcon, &cfile->fid, &find_data);
	चयन (rc) अणु
	हाल 0:
		/* TODO: add support to query reparse tag */
		cअगरs_all_info_to_fattr(&fattr, &find_data, inode->i_sb, false,
				       false, 0 /* no reparse tag */);
		अवरोध;
	हाल -EREMOTE:
		cअगरs_create_dfs_fattr(&fattr, inode->i_sb);
		rc = 0;
		अवरोध;
	हाल -EOPNOTSUPP:
	हाल -EINVAL:
		/*
		 * FIXME: legacy server -- fall back to path-based call?
		 * क्रम now, just skip revalidating and mark inode क्रम
		 * immediate reval.
		 */
		rc = 0;
		CIFS_I(inode)->समय = 0;
		जाओ cgfi_निकास;
	शेष:
		जाओ cgfi_निकास;
	पूर्ण

	/*
	 * करोn't bother with SFU junk here -- just mark inode as needing
	 * revalidation.
	 */
	fattr.cf_uniqueid = CIFS_I(inode)->uniqueid;
	fattr.cf_flags |= CIFS_FATTR_NEED_REVAL;
	/* अगर filetype is dअगरferent, वापस error */
	rc = cअगरs_fattr_to_inode(inode, &fattr);
cgfi_निकास:
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

/* Simple function to वापस a 64 bit hash of string.  Rarely called */
अटल __u64 simple_hashstr(स्थिर अक्षर *str)
अणु
	स्थिर __u64 hash_mult =  1125899906842597ULL; /* a big enough prime */
	__u64 hash = 0;

	जबतक (*str)
		hash = (hash + (__u64) *str++) * hash_mult;

	वापस hash;
पूर्ण

/**
 * cअगरs_backup_query_path_info - SMB1 fallback code to get ino
 *
 * Fallback code to get file metadata when we करोn't have access to
 * full_path (EACCES) and have backup creds.
 *
 * @xid:	transaction id used to identअगरy original request in logs
 * @tcon:	inक्रमmation about the server share we have mounted
 * @sb:	the superblock stores info such as disk space available
 * @full_path:	name of the file we are getting the metadata क्रम
 * @resp_buf:	will be set to cअगरs resp buf and needs to be मुक्तd with
 * 		cअगरs_buf_release() when करोne with @data
 * @data:	will be set to search info result buffer
 */
अटल पूर्णांक
cअगरs_backup_query_path_info(पूर्णांक xid,
			    काष्ठा cअगरs_tcon *tcon,
			    काष्ठा super_block *sb,
			    स्थिर अक्षर *full_path,
			    व्योम **resp_buf,
			    खाता_ALL_INFO **data)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा cअगरs_search_info info = अणु0पूर्ण;
	u16 flags;
	पूर्णांक rc;

	*resp_buf = शून्य;
	info.endOfSearch = false;
	अगर (tcon->unix_ext)
		info.info_level = SMB_FIND_खाता_UNIX;
	अन्यथा अगर ((tcon->ses->capabilities &
		  tcon->ses->server->vals->cap_nt_find) == 0)
		info.info_level = SMB_FIND_खाता_INFO_STANDARD;
	अन्यथा अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM)
		info.info_level = SMB_FIND_खाता_ID_FULL_सूची_INFO;
	अन्यथा /* no srvino useful क्रम fallback to some netapp */
		info.info_level = SMB_FIND_खाता_सूचीECTORY_INFO;

	flags = CIFS_SEARCH_CLOSE_ALWAYS |
		CIFS_SEARCH_CLOSE_AT_END |
		CIFS_SEARCH_BACKUP_SEARCH;

	rc = CIFSFindFirst(xid, tcon, full_path,
			   cअगरs_sb, शून्य, flags, &info, false);
	अगर (rc)
		वापस rc;

	*resp_buf = (व्योम *)info.ntwrk_buf_start;
	*data = (खाता_ALL_INFO *)info.srch_entries_start;
	वापस 0;
पूर्ण

अटल व्योम
cअगरs_set_fattr_ino(पूर्णांक xid,
		   काष्ठा cअगरs_tcon *tcon,
		   काष्ठा super_block *sb,
		   काष्ठा inode **inode,
		   स्थिर अक्षर *full_path,
		   खाता_ALL_INFO *data,
		   काष्ठा cअगरs_fattr *fattr)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	पूर्णांक rc;

	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM)) अणु
		अगर (*inode)
			fattr->cf_uniqueid = CIFS_I(*inode)->uniqueid;
		अन्यथा
			fattr->cf_uniqueid = iunique(sb, ROOT_I);
		वापस;
	पूर्ण

	/*
	 * If we have an inode pass a शून्य tcon to ensure we करोn't
	 * make a round trip to the server. This only works क्रम SMB2+.
	 */
	rc = server->ops->get_srv_inum(xid,
				       *inode ? शून्य : tcon,
				       cअगरs_sb, full_path,
				       &fattr->cf_uniqueid,
				       data);
	अगर (rc) अणु
		/*
		 * If that fails reuse existing ino or generate one
		 * and disable server ones
		 */
		अगर (*inode)
			fattr->cf_uniqueid = CIFS_I(*inode)->uniqueid;
		अन्यथा अणु
			fattr->cf_uniqueid = iunique(sb, ROOT_I);
			cअगरs_स्वतःdisable_serverino(cअगरs_sb);
		पूर्ण
		वापस;
	पूर्ण

	/* If no errors, check क्रम zero root inode (invalid) */
	अगर (fattr->cf_uniqueid == 0 && म_माप(full_path) == 0) अणु
		cअगरs_dbg(FYI, "Invalid (0) inodenum\n");
		अगर (*inode) अणु
			/* reuse */
			fattr->cf_uniqueid = CIFS_I(*inode)->uniqueid;
		पूर्ण अन्यथा अणु
			/* make an ino by hashing the UNC */
			fattr->cf_flags |= CIFS_FATTR_FAKE_ROOT_INO;
			fattr->cf_uniqueid = simple_hashstr(tcon->treeName);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत bool is_inode_cache_good(काष्ठा inode *ino)
अणु
	वापस ino && CIFS_CACHE_READ(CIFS_I(ino)) && CIFS_I(ino)->समय != 0;
पूर्ण

पूर्णांक
cअगरs_get_inode_info(काष्ठा inode **inode,
		    स्थिर अक्षर *full_path,
		    खाता_ALL_INFO *in_data,
		    काष्ठा super_block *sb, पूर्णांक xid,
		    स्थिर काष्ठा cअगरs_fid *fid)
अणु

	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	bool adjust_tz = false;
	काष्ठा cअगरs_fattr fattr = अणु0पूर्ण;
	bool is_reparse_poपूर्णांक = false;
	खाता_ALL_INFO *data = in_data;
	खाता_ALL_INFO *पंचांगp_data = शून्य;
	व्योम *smb1_backup_rsp_buf = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक पंचांगprc = 0;
	__u32 reparse_tag = 0;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);
	server = tcon->ses->server;

	/*
	 * 1. Fetch file metadata अगर not provided (data)
	 */

	अगर (!data) अणु
		अगर (is_inode_cache_good(*inode)) अणु
			cअगरs_dbg(FYI, "No need to revalidate cached inode sizes\n");
			जाओ out;
		पूर्ण
		पंचांगp_data = kदो_स्मृति(माप(खाता_ALL_INFO), GFP_KERNEL);
		अगर (!पंचांगp_data) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		rc = server->ops->query_path_info(xid, tcon, cअगरs_sb,
						 full_path, पंचांगp_data,
						 &adjust_tz, &is_reparse_poपूर्णांक);
		data = पंचांगp_data;
	पूर्ण

	/*
	 * 2. Convert it to पूर्णांकernal cअगरs metadata (fattr)
	 */

	चयन (rc) अणु
	हाल 0:
		/*
		 * If the file is a reparse poपूर्णांक, it is more complicated
		 * since we have to check अगर its reparse tag matches a known
		 * special file type e.g. symlink or fअगरo or अक्षर etc.
		 */
		अगर ((le32_to_cpu(data->Attributes) & ATTR_REPARSE) &&
		    server->ops->query_reparse_tag) अणु
			rc = server->ops->query_reparse_tag(xid, tcon, cअगरs_sb,
						full_path, &reparse_tag);
			cअगरs_dbg(FYI, "reparse tag 0x%x\n", reparse_tag);
		पूर्ण
		cअगरs_all_info_to_fattr(&fattr, data, sb, adjust_tz,
				       is_reparse_poपूर्णांक, reparse_tag);
		अवरोध;
	हाल -EREMOTE:
		/* DFS link, no metadata available on this server */
		cअगरs_create_dfs_fattr(&fattr, sb);
		rc = 0;
		अवरोध;
	हाल -EACCES:
		/*
		 * perm errors, try again with backup flags अगर possible
		 *
		 * For SMB2 and later the backup पूर्णांकent flag
		 * is alपढ़ोy sent अगर needed on खोलो and there
		 * is no path based FindFirst operation to use
		 * to retry with
		 */
		अगर (backup_cred(cअगरs_sb) && is_smb1_server(server)) अणु
			/* क्रम easier पढ़ोing */
			खाता_सूचीECTORY_INFO *fdi;
			SEARCH_ID_FULL_सूची_INFO *si;

			rc = cअगरs_backup_query_path_info(xid, tcon, sb,
							 full_path,
							 &smb1_backup_rsp_buf,
							 &data);
			अगर (rc)
				जाओ out;

			fdi = (खाता_सूचीECTORY_INFO *)data;
			si = (SEARCH_ID_FULL_सूची_INFO *)data;

			cअगरs_dir_info_to_fattr(&fattr, fdi, cअगरs_sb);
			fattr.cf_uniqueid = le64_to_cpu(si->UniqueId);
			/* uniqueid set, skip get inum step */
			जाओ handle_mnt_opt;
		पूर्ण अन्यथा अणु
			/* nothing we can करो, bail out */
			जाओ out;
		पूर्ण
		अवरोध;
	शेष:
		cअगरs_dbg(FYI, "%s: unhandled err rc %d\n", __func__, rc);
		जाओ out;
	पूर्ण

	/*
	 * 3. Get or update inode number (fattr.cf_uniqueid)
	 */

	cअगरs_set_fattr_ino(xid, tcon, sb, inode, full_path, data, &fattr);

	/*
	 * 4. Tweak fattr based on mount options
	 */

handle_mnt_opt:
	/* query क्रम SFU type info अगर supported and needed */
	अगर (fattr.cf_cअगरsattrs & ATTR_SYSTEM &&
	    cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_UNX_EMUL) अणु
		पंचांगprc = cअगरs_sfu_type(&fattr, full_path, cअगरs_sb, xid);
		अगर (पंचांगprc)
			cअगरs_dbg(FYI, "cifs_sfu_type failed: %d\n", पंचांगprc);
	पूर्ण

	/* fill in 0777 bits from ACL */
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MODE_FROM_SID) अणु
		rc = cअगरs_acl_to_fattr(cअगरs_sb, &fattr, *inode, true,
				       full_path, fid);
		अगर (rc == -EREMOTE)
			rc = 0;
		अगर (rc) अणु
			cअगरs_dbg(FYI, "%s: Get mode from SID failed. rc=%d\n",
				 __func__, rc);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_CIFS_ACL) अणु
		rc = cअगरs_acl_to_fattr(cअगरs_sb, &fattr, *inode, false,
				       full_path, fid);
		अगर (rc == -EREMOTE)
			rc = 0;
		अगर (rc) अणु
			cअगरs_dbg(FYI, "%s: Getting ACL failed with error: %d\n",
				 __func__, rc);
			जाओ out;
		पूर्ण
	पूर्ण

	/* fill in reमुख्यing high mode bits e.g. SUID, VTX */
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_UNX_EMUL)
		cअगरs_sfu_mode(&fattr, full_path, cअगरs_sb, xid);

	/* check क्रम Minshall+French symlinks */
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MF_SYMLINKS) अणु
		पंचांगprc = check_mf_symlink(xid, tcon, cअगरs_sb, &fattr,
					 full_path);
		अगर (पंचांगprc)
			cअगरs_dbg(FYI, "check_mf_symlink: %d\n", पंचांगprc);
	पूर्ण

	/*
	 * 5. Update inode with final fattr data
	 */

	अगर (!*inode) अणु
		*inode = cअगरs_iget(sb, &fattr);
		अगर (!*inode)
			rc = -ENOMEM;
	पूर्ण अन्यथा अणु
		/* we alपढ़ोy have inode, update it */

		/* अगर uniqueid is dअगरferent, वापस error */
		अगर (unlikely(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM &&
		    CIFS_I(*inode)->uniqueid != fattr.cf_uniqueid)) अणु
			CIFS_I(*inode)->समय = 0; /* क्रमce reval */
			rc = -ESTALE;
			जाओ out;
		पूर्ण
		/* अगर filetype is dअगरferent, वापस error */
		rc = cअगरs_fattr_to_inode(*inode, &fattr);
	पूर्ण
out:
	cअगरs_buf_release(smb1_backup_rsp_buf);
	cअगरs_put_tlink(tlink);
	kमुक्त(पंचांगp_data);
	वापस rc;
पूर्ण

पूर्णांक
smb311_posix_get_inode_info(काष्ठा inode **inode,
		    स्थिर अक्षर *full_path,
		    काष्ठा super_block *sb, अचिन्हित पूर्णांक xid)
अणु
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	bool adjust_tz = false;
	काष्ठा cअगरs_fattr fattr = अणु0पूर्ण;
	bool symlink = false;
	काष्ठा smb311_posix_qinfo *data = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक पंचांगprc = 0;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);

	/*
	 * 1. Fetch file metadata
	 */

	अगर (is_inode_cache_good(*inode)) अणु
		cअगरs_dbg(FYI, "No need to revalidate cached inode sizes\n");
		जाओ out;
	पूर्ण
	data = kदो_स्मृति(माप(काष्ठा smb311_posix_qinfo), GFP_KERNEL);
	अगर (!data) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	rc = smb311_posix_query_path_info(xid, tcon, cअगरs_sb,
						  full_path, data,
						  &adjust_tz, &symlink);

	/*
	 * 2. Convert it to पूर्णांकernal cअगरs metadata (fattr)
	 */

	चयन (rc) अणु
	हाल 0:
		smb311_posix_info_to_fattr(&fattr, data, sb, adjust_tz, symlink);
		अवरोध;
	हाल -EREMOTE:
		/* DFS link, no metadata available on this server */
		cअगरs_create_dfs_fattr(&fattr, sb);
		rc = 0;
		अवरोध;
	हाल -EACCES:
		/*
		 * For SMB2 and later the backup पूर्णांकent flag
		 * is alपढ़ोy sent अगर needed on खोलो and there
		 * is no path based FindFirst operation to use
		 * to retry with so nothing we can करो, bail out
		 */
		जाओ out;
	शेष:
		cअगरs_dbg(FYI, "%s: unhandled err rc %d\n", __func__, rc);
		जाओ out;
	पूर्ण


	/*
	 * 3. Tweak fattr based on mount options
	 */

	/* check क्रम Minshall+French symlinks */
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MF_SYMLINKS) अणु
		पंचांगprc = check_mf_symlink(xid, tcon, cअगरs_sb, &fattr,
					 full_path);
		अगर (पंचांगprc)
			cअगरs_dbg(FYI, "check_mf_symlink: %d\n", पंचांगprc);
	पूर्ण

	/*
	 * 4. Update inode with final fattr data
	 */

	अगर (!*inode) अणु
		*inode = cअगरs_iget(sb, &fattr);
		अगर (!*inode)
			rc = -ENOMEM;
	पूर्ण अन्यथा अणु
		/* we alपढ़ोy have inode, update it */

		/* अगर uniqueid is dअगरferent, वापस error */
		अगर (unlikely(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM &&
		    CIFS_I(*inode)->uniqueid != fattr.cf_uniqueid)) अणु
			CIFS_I(*inode)->समय = 0; /* क्रमce reval */
			rc = -ESTALE;
			जाओ out;
		पूर्ण

		/* अगर filetype is dअगरferent, वापस error */
		rc = cअगरs_fattr_to_inode(*inode, &fattr);
	पूर्ण
out:
	cअगरs_put_tlink(tlink);
	kमुक्त(data);
	वापस rc;
पूर्ण


अटल स्थिर काष्ठा inode_operations cअगरs_ipc_inode_ops = अणु
	.lookup = cअगरs_lookup,
पूर्ण;

अटल पूर्णांक
cअगरs_find_inode(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा cअगरs_fattr *fattr = (काष्ठा cअगरs_fattr *) opaque;

	/* करोn't match inode with dअगरferent uniqueid */
	अगर (CIFS_I(inode)->uniqueid != fattr->cf_uniqueid)
		वापस 0;

	/* use createसमय like an i_generation field */
	अगर (CIFS_I(inode)->createसमय != fattr->cf_createसमय)
		वापस 0;

	/* करोn't match inode of dअगरferent type */
	अगर (inode_wrong_type(inode, fattr->cf_mode))
		वापस 0;

	/* अगर it's not a directory or has no dentries, then flag it */
	अगर (S_ISसूची(inode->i_mode) && !hlist_empty(&inode->i_dentry))
		fattr->cf_flags |= CIFS_FATTR_INO_COLLISION;

	वापस 1;
पूर्ण

अटल पूर्णांक
cअगरs_init_inode(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा cअगरs_fattr *fattr = (काष्ठा cअगरs_fattr *) opaque;

	CIFS_I(inode)->uniqueid = fattr->cf_uniqueid;
	CIFS_I(inode)->createसमय = fattr->cf_createसमय;
	वापस 0;
पूर्ण

/*
 * walk dentry list क्रम an inode and report whether it has aliases that
 * are hashed. We use this to determine अगर a directory inode can actually
 * be used.
 */
अटल bool
inode_has_hashed_dentries(काष्ठा inode *inode)
अणु
	काष्ठा dentry *dentry;

	spin_lock(&inode->i_lock);
	hlist_क्रम_each_entry(dentry, &inode->i_dentry, d_u.d_alias) अणु
		अगर (!d_unhashed(dentry) || IS_ROOT(dentry)) अणु
			spin_unlock(&inode->i_lock);
			वापस true;
		पूर्ण
	पूर्ण
	spin_unlock(&inode->i_lock);
	वापस false;
पूर्ण

/* Given fattrs, get a corresponding inode */
काष्ठा inode *
cअगरs_iget(काष्ठा super_block *sb, काष्ठा cअगरs_fattr *fattr)
अणु
	अचिन्हित दीर्घ hash;
	काष्ठा inode *inode;

retry_iget5_locked:
	cअगरs_dbg(FYI, "looking for uniqueid=%llu\n", fattr->cf_uniqueid);

	/* hash करोwn to 32-bits on 32-bit arch */
	hash = cअगरs_uniqueid_to_ino_t(fattr->cf_uniqueid);

	inode = iget5_locked(sb, hash, cअगरs_find_inode, cअगरs_init_inode, fattr);
	अगर (inode) अणु
		/* was there a potentially problematic inode collision? */
		अगर (fattr->cf_flags & CIFS_FATTR_INO_COLLISION) अणु
			fattr->cf_flags &= ~CIFS_FATTR_INO_COLLISION;

			अगर (inode_has_hashed_dentries(inode)) अणु
				cअगरs_स्वतःdisable_serverino(CIFS_SB(sb));
				iput(inode);
				fattr->cf_uniqueid = iunique(sb, ROOT_I);
				जाओ retry_iget5_locked;
			पूर्ण
		पूर्ण

		/* can't fail - see cअगरs_find_inode() */
		cअगरs_fattr_to_inode(inode, fattr);
		अगर (sb->s_flags & SB_NOATIME)
			inode->i_flags |= S_NOATIME | S_NOCMTIME;
		अगर (inode->i_state & I_NEW) अणु
			inode->i_ino = hash;
#अगर_घोषित CONFIG_CIFS_FSCACHE
			/* initialize per-inode cache cookie poपूर्णांकer */
			CIFS_I(inode)->fscache = शून्य;
#पूर्ण_अगर
			unlock_new_inode(inode);
		पूर्ण
	पूर्ण

	वापस inode;
पूर्ण

/* माला_लो root inode */
काष्ठा inode *cअगरs_root_iget(काष्ठा super_block *sb)
अणु
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा inode *inode = शून्य;
	दीर्घ rc;
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	अक्षर *path = शून्य;
	पूर्णांक len;

	अगर ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_USE_PREFIX_PATH)
	    && cअगरs_sb->prepath) अणु
		len = म_माप(cअगरs_sb->prepath);
		path = kzalloc(len + 2 /* leading sep + null */, GFP_KERNEL);
		अगर (path == शून्य)
			वापस ERR_PTR(-ENOMEM);
		path[0] = '/';
		स_नकल(path+1, cअगरs_sb->prepath, len);
	पूर्ण अन्यथा अणु
		path = kstrdup("", GFP_KERNEL);
		अगर (path == शून्य)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	xid = get_xid();
	अगर (tcon->unix_ext) अणु
		rc = cअगरs_get_inode_info_unix(&inode, path, sb, xid);
		/* some servers mistakenly claim POSIX support */
		अगर (rc != -EOPNOTSUPP)
			जाओ iget_no_retry;
		cअगरs_dbg(VFS, "server does not support POSIX extensions\n");
		tcon->unix_ext = false;
	पूर्ण

	convert_delimiter(path, CIFS_सूची_SEP(cअगरs_sb));
	अगर (tcon->posix_extensions)
		rc = smb311_posix_get_inode_info(&inode, path, sb, xid);
	अन्यथा
		rc = cअगरs_get_inode_info(&inode, path, शून्य, sb, xid, शून्य);

iget_no_retry:
	अगर (!inode) अणु
		inode = ERR_PTR(rc);
		जाओ out;
	पूर्ण

#अगर_घोषित CONFIG_CIFS_FSCACHE
	/* populate tcon->resource_id */
	tcon->resource_id = CIFS_I(inode)->uniqueid;
#पूर्ण_अगर

	अगर (rc && tcon->pipe) अणु
		cअगरs_dbg(FYI, "ipc connection - fake read inode\n");
		spin_lock(&inode->i_lock);
		inode->i_mode |= S_IFसूची;
		set_nlink(inode, 2);
		inode->i_op = &cअगरs_ipc_inode_ops;
		inode->i_fop = &simple_dir_operations;
		inode->i_uid = cअगरs_sb->ctx->linux_uid;
		inode->i_gid = cअगरs_sb->ctx->linux_gid;
		spin_unlock(&inode->i_lock);
	पूर्ण अन्यथा अगर (rc) अणु
		iget_failed(inode);
		inode = ERR_PTR(rc);
	पूर्ण

out:
	kमुक्त(path);
	मुक्त_xid(xid);
	वापस inode;
पूर्ण

पूर्णांक
cअगरs_set_file_info(काष्ठा inode *inode, काष्ठा iattr *attrs, अचिन्हित पूर्णांक xid,
		   स्थिर अक्षर *full_path, __u32 करोsattr)
अणु
	bool set_समय = false;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा TCP_Server_Info *server;
	खाता_BASIC_INFO	info_buf;

	अगर (attrs == शून्य)
		वापस -EINVAL;

	server = cअगरs_sb_master_tcon(cअगरs_sb)->ses->server;
	अगर (!server->ops->set_file_info)
		वापस -ENOSYS;

	info_buf.Pad = 0;

	अगर (attrs->ia_valid & ATTR_ATIME) अणु
		set_समय = true;
		info_buf.LastAccessTime =
			cpu_to_le64(cअगरs_UnixTimeToNT(attrs->ia_aसमय));
	पूर्ण अन्यथा
		info_buf.LastAccessTime = 0;

	अगर (attrs->ia_valid & ATTR_MTIME) अणु
		set_समय = true;
		info_buf.LastWriteTime =
		    cpu_to_le64(cअगरs_UnixTimeToNT(attrs->ia_mसमय));
	पूर्ण अन्यथा
		info_buf.LastWriteTime = 0;

	/*
	 * Samba throws this field away, but winकरोws may actually use it.
	 * Do not set स_समय unless other समय stamps are changed explicitly
	 * (i.e. by uबार()) since we would then have a mix of client and
	 * server बार.
	 */
	अगर (set_समय && (attrs->ia_valid & ATTR_CTIME)) अणु
		cअगरs_dbg(FYI, "CIFS - CTIME changed\n");
		info_buf.ChangeTime =
		    cpu_to_le64(cअगरs_UnixTimeToNT(attrs->ia_स_समय));
	पूर्ण अन्यथा
		info_buf.ChangeTime = 0;

	info_buf.CreationTime = 0;	/* करोn't change */
	info_buf.Attributes = cpu_to_le32(करोsattr);

	वापस server->ops->set_file_info(inode, full_path, &info_buf, xid);
पूर्ण

/*
 * Open the given file (अगर it isn't alपढ़ोy), set the DELETE_ON_CLOSE bit
 * and नाम it to a अक्रमom name that hopefully won't conflict with
 * anything अन्यथा.
 */
पूर्णांक
cअगरs_नाम_pending_delete(स्थिर अक्षर *full_path, काष्ठा dentry *dentry,
			   स्थिर अचिन्हित पूर्णांक xid)
अणु
	पूर्णांक oplock = 0;
	पूर्णांक rc;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा cअगरsInodeInfo *cअगरsInode = CIFS_I(inode);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;
	__u32 करोsattr, origattr;
	खाता_BASIC_INFO *info_buf = शून्य;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);

	/*
	 * We cannot नाम the file अगर the server करोesn't support
	 * CAP_INFOLEVEL_PASSTHRU
	 */
	अगर (!(tcon->ses->capabilities & CAP_INFOLEVEL_PASSTHRU)) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = DELETE | खाता_WRITE_ATTRIBUTES;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, CREATE_NOT_सूची);
	oparms.disposition = खाता_OPEN;
	oparms.path = full_path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = CIFS_खोलो(xid, &oparms, &oplock, शून्य);
	अगर (rc != 0)
		जाओ out;

	origattr = cअगरsInode->cअगरsAttrs;
	अगर (origattr == 0)
		origattr |= ATTR_NORMAL;

	करोsattr = origattr & ~ATTR_READONLY;
	अगर (करोsattr == 0)
		करोsattr |= ATTR_NORMAL;
	करोsattr |= ATTR_HIDDEN;

	/* set ATTR_HIDDEN and clear ATTR_READONLY, but only अगर needed */
	अगर (करोsattr != origattr) अणु
		info_buf = kzalloc(माप(*info_buf), GFP_KERNEL);
		अगर (info_buf == शून्य) अणु
			rc = -ENOMEM;
			जाओ out_बंद;
		पूर्ण
		info_buf->Attributes = cpu_to_le32(करोsattr);
		rc = CIFSSMBSetFileInfo(xid, tcon, info_buf, fid.netfid,
					current->tgid);
		/* although we would like to mark the file hidden
 		   अगर that fails we will still try to नाम it */
		अगर (!rc)
			cअगरsInode->cअगरsAttrs = करोsattr;
		अन्यथा
			करोsattr = origattr; /* since not able to change them */
	पूर्ण

	/* नाम the file */
	rc = CIFSSMBRenameOpenFile(xid, tcon, fid.netfid, शून्य,
				   cअगरs_sb->local_nls,
				   cअगरs_remap(cअगरs_sb));
	अगर (rc != 0) अणु
		rc = -EBUSY;
		जाओ unकरो_setattr;
	पूर्ण

	/* try to set DELETE_ON_CLOSE */
	अगर (!test_bit(CIFS_INO_DELETE_PENDING, &cअगरsInode->flags)) अणु
		rc = CIFSSMBSetFileDisposition(xid, tcon, true, fid.netfid,
					       current->tgid);
		/*
		 * some samba versions वापस -ENOENT when we try to set the
		 * file disposition here. Likely a samba bug, but work around
		 * it क्रम now. This means that some cअगरsXXX files may hang
		 * around after they shouldn't.
		 *
		 * BB: हटाओ this hack after more servers have the fix
		 */
		अगर (rc == -ENOENT)
			rc = 0;
		अन्यथा अगर (rc != 0) अणु
			rc = -EBUSY;
			जाओ unकरो_नाम;
		पूर्ण
		set_bit(CIFS_INO_DELETE_PENDING, &cअगरsInode->flags);
	पूर्ण

out_बंद:
	CIFSSMBClose(xid, tcon, fid.netfid);
out:
	kमुक्त(info_buf);
	cअगरs_put_tlink(tlink);
	वापस rc;

	/*
	 * reset everything back to the original state. Don't bother
	 * dealing with errors here since we can't करो anything about
	 * them anyway.
	 */
unकरो_नाम:
	CIFSSMBRenameOpenFile(xid, tcon, fid.netfid, dentry->d_name.name,
				cअगरs_sb->local_nls, cअगरs_remap(cअगरs_sb));
unकरो_setattr:
	अगर (करोsattr != origattr) अणु
		info_buf->Attributes = cpu_to_le32(origattr);
		अगर (!CIFSSMBSetFileInfo(xid, tcon, info_buf, fid.netfid,
					current->tgid))
			cअगरsInode->cअगरsAttrs = origattr;
	पूर्ण

	जाओ out_बंद;
पूर्ण

/* copied from fs/nfs/dir.c with small changes */
अटल व्योम
cअगरs_drop_nlink(काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	अगर (inode->i_nlink > 0)
		drop_nlink(inode);
	spin_unlock(&inode->i_lock);
पूर्ण

/*
 * If d_inode(dentry) is null (usually meaning the cached dentry
 * is a negative dentry) then we would attempt a standard SMB delete, but
 * अगर that fails we can not attempt the fall back mechanisms on EACCES
 * but will वापस the EACCES to the caller. Note that the VFS करोes not call
 * unlink on negative dentries currently.
 */
पूर्णांक cअगरs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक xid;
	स्थिर अक्षर *full_path;
	व्योम *page;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा cअगरsInodeInfo *cअगरs_inode;
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	काष्ठा iattr *attrs = शून्य;
	__u32 करोsattr = 0, origattr = 0;

	cअगरs_dbg(FYI, "cifs_unlink, dir=0x%p, dentry=0x%p\n", dir, dentry);

	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(cअगरs_sb)))
		वापस -EIO;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);
	server = tcon->ses->server;

	xid = get_xid();
	page = alloc_dentry_path();

	अगर (tcon->nodelete) अणु
		rc = -EACCES;
		जाओ unlink_out;
	पूर्ण

	/* Unlink can be called from नाम so we can not take the
	 * sb->s_vfs_नाम_mutex here */
	full_path = build_path_from_dentry(dentry, page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ unlink_out;
	पूर्ण

	cअगरs_बंद_all_deferred_files(tcon);
	अगर (cap_unix(tcon->ses) && (CIFS_UNIX_POSIX_PATH_OPS_CAP &
				le64_to_cpu(tcon->fsUnixInfo.Capability))) अणु
		rc = CIFSPOSIXDelFile(xid, tcon, full_path,
			SMB_POSIX_UNLINK_खाता_TARGET, cअगरs_sb->local_nls,
			cअगरs_remap(cअगरs_sb));
		cअगरs_dbg(FYI, "posix del rc %d\n", rc);
		अगर ((rc == 0) || (rc == -ENOENT))
			जाओ psx_del_no_retry;
	पूर्ण

retry_std_delete:
	अगर (!server->ops->unlink) अणु
		rc = -ENOSYS;
		जाओ psx_del_no_retry;
	पूर्ण

	rc = server->ops->unlink(xid, tcon, full_path, cअगरs_sb);

psx_del_no_retry:
	अगर (!rc) अणु
		अगर (inode)
			cअगरs_drop_nlink(inode);
	पूर्ण अन्यथा अगर (rc == -ENOENT) अणु
		d_drop(dentry);
	पूर्ण अन्यथा अगर (rc == -EBUSY) अणु
		अगर (server->ops->नाम_pending_delete) अणु
			rc = server->ops->नाम_pending_delete(full_path,
								dentry, xid);
			अगर (rc == 0)
				cअगरs_drop_nlink(inode);
		पूर्ण
	पूर्ण अन्यथा अगर ((rc == -EACCES) && (करोsattr == 0) && inode) अणु
		attrs = kzalloc(माप(*attrs), GFP_KERNEL);
		अगर (attrs == शून्य) अणु
			rc = -ENOMEM;
			जाओ out_reval;
		पूर्ण

		/* try to reset करोs attributes */
		cअगरs_inode = CIFS_I(inode);
		origattr = cअगरs_inode->cअगरsAttrs;
		अगर (origattr == 0)
			origattr |= ATTR_NORMAL;
		करोsattr = origattr & ~ATTR_READONLY;
		अगर (करोsattr == 0)
			करोsattr |= ATTR_NORMAL;
		करोsattr |= ATTR_HIDDEN;

		rc = cअगरs_set_file_info(inode, attrs, xid, full_path, करोsattr);
		अगर (rc != 0)
			जाओ out_reval;

		जाओ retry_std_delete;
	पूर्ण

	/* unकरो the setattr अगर we errored out and it's needed */
	अगर (rc != 0 && करोsattr != 0)
		cअगरs_set_file_info(inode, attrs, xid, full_path, origattr);

out_reval:
	अगर (inode) अणु
		cअगरs_inode = CIFS_I(inode);
		cअगरs_inode->समय = 0;	/* will क्रमce revalidate to get info
					   when needed */
		inode->i_स_समय = current_समय(inode);
	पूर्ण
	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	cअगरs_inode = CIFS_I(dir);
	CIFS_I(dir)->समय = 0;	/* क्रमce revalidate of dir as well */
unlink_out:
	मुक्त_dentry_path(page);
	kमुक्त(attrs);
	मुक्त_xid(xid);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_सूची_गढ़ो_qinfo(काष्ठा inode *parent, काष्ठा dentry *dentry, umode_t mode,
		 स्थिर अक्षर *full_path, काष्ठा cअगरs_sb_info *cअगरs_sb,
		 काष्ठा cअगरs_tcon *tcon, स्थिर अचिन्हित पूर्णांक xid)
अणु
	पूर्णांक rc = 0;
	काष्ठा inode *inode = शून्य;

	अगर (tcon->posix_extensions)
		rc = smb311_posix_get_inode_info(&inode, full_path, parent->i_sb, xid);
	अन्यथा अगर (tcon->unix_ext)
		rc = cअगरs_get_inode_info_unix(&inode, full_path, parent->i_sb,
					      xid);
	अन्यथा
		rc = cअगरs_get_inode_info(&inode, full_path, शून्य, parent->i_sb,
					 xid, शून्य);

	अगर (rc)
		वापस rc;

	अगर (!S_ISसूची(inode->i_mode)) अणु
		/*
		 * सूची_गढ़ो succeeded, but another client has managed to हटाओ the
		 * sucker and replace it with non-directory.  Return success,
		 * but करोn't leave the child in dcache.
		 */
		 iput(inode);
		 d_drop(dentry);
		 वापस 0;
	पूर्ण
	/*
	 * setting nlink not necessary except in हालs where we failed to get it
	 * from the server or was set bogus. Also, since this is a bअक्रम new
	 * inode, no need to grab the i_lock beक्रमe setting the i_nlink.
	 */
	अगर (inode->i_nlink < 2)
		set_nlink(inode, 2);
	mode &= ~current_umask();
	/* must turn on setgid bit अगर parent dir has it */
	अगर (parent->i_mode & S_ISGID)
		mode |= S_ISGID;

	अगर (tcon->unix_ext) अणु
		काष्ठा cअगरs_unix_set_info_args args = अणु
			.mode	= mode,
			.स_समय	= NO_CHANGE_64,
			.aसमय	= NO_CHANGE_64,
			.mसमय	= NO_CHANGE_64,
			.device	= 0,
		पूर्ण;
		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SET_UID) अणु
			args.uid = current_fsuid();
			अगर (parent->i_mode & S_ISGID)
				args.gid = parent->i_gid;
			अन्यथा
				args.gid = current_fsgid();
		पूर्ण अन्यथा अणु
			args.uid = INVALID_UID; /* no change */
			args.gid = INVALID_GID; /* no change */
		पूर्ण
		CIFSSMBUnixSetPathInfo(xid, tcon, full_path, &args,
				       cअगरs_sb->local_nls,
				       cअगरs_remap(cअगरs_sb));
	पूर्ण अन्यथा अणु
		काष्ठा TCP_Server_Info *server = tcon->ses->server;
		अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_CIFS_ACL) &&
		    (mode & S_IWUGO) == 0 && server->ops->सूची_गढ़ो_setinfo)
			server->ops->सूची_गढ़ो_setinfo(inode, full_path, cअगरs_sb,
						   tcon, xid);
		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_DYNPERM)
			inode->i_mode = (mode | S_IFसूची);

		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SET_UID) अणु
			inode->i_uid = current_fsuid();
			अगर (inode->i_mode & S_ISGID)
				inode->i_gid = parent->i_gid;
			अन्यथा
				inode->i_gid = current_fsgid();
		पूर्ण
	पूर्ण
	d_instantiate(dentry, inode);
	वापस 0;
पूर्ण

अटल पूर्णांक
cअगरs_posix_सूची_गढ़ो(काष्ठा inode *inode, काष्ठा dentry *dentry, umode_t mode,
		 स्थिर अक्षर *full_path, काष्ठा cअगरs_sb_info *cअगरs_sb,
		 काष्ठा cअगरs_tcon *tcon, स्थिर अचिन्हित पूर्णांक xid)
अणु
	पूर्णांक rc = 0;
	u32 oplock = 0;
	खाता_UNIX_BASIC_INFO *info = शून्य;
	काष्ठा inode *newinode = शून्य;
	काष्ठा cअगरs_fattr fattr;

	info = kzalloc(माप(खाता_UNIX_BASIC_INFO), GFP_KERNEL);
	अगर (info == शून्य) अणु
		rc = -ENOMEM;
		जाओ posix_सूची_गढ़ो_out;
	पूर्ण

	mode &= ~current_umask();
	rc = CIFSPOSIXCreate(xid, tcon, SMB_O_सूचीECTORY | SMB_O_CREAT, mode,
			     शून्य /* netfid */, info, &oplock, full_path,
			     cअगरs_sb->local_nls, cअगरs_remap(cअगरs_sb));
	अगर (rc == -EOPNOTSUPP)
		जाओ posix_सूची_गढ़ो_out;
	अन्यथा अगर (rc) अणु
		cअगरs_dbg(FYI, "posix mkdir returned 0x%x\n", rc);
		d_drop(dentry);
		जाओ posix_सूची_गढ़ो_out;
	पूर्ण

	अगर (info->Type == cpu_to_le32(-1))
		/* no वापस info, go query क्रम it */
		जाओ posix_सूची_गढ़ो_get_info;
	/*
	 * BB check (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SET_UID ) to see अगर
	 * need to set uid/gid.
	 */

	cअगरs_unix_basic_to_fattr(&fattr, info, cअगरs_sb);
	cअगरs_fill_uniqueid(inode->i_sb, &fattr);
	newinode = cअगरs_iget(inode->i_sb, &fattr);
	अगर (!newinode)
		जाओ posix_सूची_गढ़ो_get_info;

	d_instantiate(dentry, newinode);

#अगर_घोषित CONFIG_CIFS_DEBUG2
	cअगरs_dbg(FYI, "instantiated dentry %p %pd to inode %p\n",
		 dentry, dentry, newinode);

	अगर (newinode->i_nlink != 2)
		cअगरs_dbg(FYI, "unexpected number of links %d\n",
			 newinode->i_nlink);
#पूर्ण_अगर

posix_सूची_गढ़ो_out:
	kमुक्त(info);
	वापस rc;
posix_सूची_गढ़ो_get_info:
	rc = cअगरs_सूची_गढ़ो_qinfo(inode, dentry, mode, full_path, cअगरs_sb, tcon,
			      xid);
	जाओ posix_सूची_गढ़ो_out;
पूर्ण

पूर्णांक cअगरs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
	       काष्ठा dentry *direntry, umode_t mode)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	स्थिर अक्षर *full_path;
	व्योम *page;

	cअगरs_dbg(FYI, "In cifs_mkdir, mode = %04ho inode = 0x%p\n",
		 mode, inode);

	cअगरs_sb = CIFS_SB(inode->i_sb);
	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(cअगरs_sb)))
		वापस -EIO;
	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);

	xid = get_xid();

	page = alloc_dentry_path();
	full_path = build_path_from_dentry(direntry, page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ सूची_गढ़ो_out;
	पूर्ण

	server = tcon->ses->server;

	अगर ((server->ops->posix_सूची_गढ़ो) && (tcon->posix_extensions)) अणु
		rc = server->ops->posix_सूची_गढ़ो(xid, inode, mode, tcon, full_path,
					      cअगरs_sb);
		d_drop(direntry); /* क्रम समय being always refresh inode info */
		जाओ सूची_गढ़ो_out;
	पूर्ण

	अगर (cap_unix(tcon->ses) && (CIFS_UNIX_POSIX_PATH_OPS_CAP &
				le64_to_cpu(tcon->fsUnixInfo.Capability))) अणु
		rc = cअगरs_posix_सूची_गढ़ो(inode, direntry, mode, full_path, cअगरs_sb,
				      tcon, xid);
		अगर (rc != -EOPNOTSUPP)
			जाओ सूची_गढ़ो_out;
	पूर्ण

	अगर (!server->ops->सूची_गढ़ो) अणु
		rc = -ENOSYS;
		जाओ सूची_गढ़ो_out;
	पूर्ण

	/* BB add setting the equivalent of mode via CreateX w/ACLs */
	rc = server->ops->सूची_गढ़ो(xid, inode, mode, tcon, full_path, cअगरs_sb);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "cifs_mkdir returned 0x%x\n", rc);
		d_drop(direntry);
		जाओ सूची_गढ़ो_out;
	पूर्ण

	/* TODO: skip this क्रम smb2/smb3 */
	rc = cअगरs_सूची_गढ़ो_qinfo(inode, direntry, mode, full_path, cअगरs_sb, tcon,
			      xid);
सूची_गढ़ो_out:
	/*
	 * Force revalidate to get parent dir info when needed since cached
	 * attributes are invalid now.
	 */
	CIFS_I(inode)->समय = 0;
	मुक्त_dentry_path(page);
	मुक्त_xid(xid);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

पूर्णांक cअगरs_सूची_हटाओ(काष्ठा inode *inode, काष्ठा dentry *direntry)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	स्थिर अक्षर *full_path;
	व्योम *page = alloc_dentry_path();
	काष्ठा cअगरsInodeInfo *cअगरsInode;

	cअगरs_dbg(FYI, "cifs_rmdir, inode = 0x%p\n", inode);

	xid = get_xid();

	full_path = build_path_from_dentry(direntry, page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ सूची_हटाओ_निकास;
	पूर्ण

	cअगरs_sb = CIFS_SB(inode->i_sb);
	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(cअगरs_sb))) अणु
		rc = -EIO;
		जाओ सूची_हटाओ_निकास;
	पूर्ण

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink)) अणु
		rc = PTR_ERR(tlink);
		जाओ सूची_हटाओ_निकास;
	पूर्ण
	tcon = tlink_tcon(tlink);
	server = tcon->ses->server;

	अगर (!server->ops->सूची_हटाओ) अणु
		rc = -ENOSYS;
		cअगरs_put_tlink(tlink);
		जाओ सूची_हटाओ_निकास;
	पूर्ण

	अगर (tcon->nodelete) अणु
		rc = -EACCES;
		cअगरs_put_tlink(tlink);
		जाओ सूची_हटाओ_निकास;
	पूर्ण

	rc = server->ops->सूची_हटाओ(xid, tcon, full_path, cअगरs_sb);
	cअगरs_put_tlink(tlink);

	अगर (!rc) अणु
		spin_lock(&d_inode(direntry)->i_lock);
		i_size_ग_लिखो(d_inode(direntry), 0);
		clear_nlink(d_inode(direntry));
		spin_unlock(&d_inode(direntry)->i_lock);
	पूर्ण

	cअगरsInode = CIFS_I(d_inode(direntry));
	/* क्रमce revalidate to go get info when needed */
	cअगरsInode->समय = 0;

	cअगरsInode = CIFS_I(inode);
	/*
	 * Force revalidate to get parent dir info when needed since cached
	 * attributes are invalid now.
	 */
	cअगरsInode->समय = 0;

	d_inode(direntry)->i_स_समय = inode->i_स_समय = inode->i_mसमय =
		current_समय(inode);

सूची_हटाओ_निकास:
	मुक्त_dentry_path(page);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_करो_नाम(स्थिर अचिन्हित पूर्णांक xid, काष्ठा dentry *from_dentry,
	       स्थिर अक्षर *from_path, काष्ठा dentry *to_dentry,
	       स्थिर अक्षर *to_path)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(from_dentry->d_sb);
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;
	पूर्णांक oplock, rc;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);
	server = tcon->ses->server;

	अगर (!server->ops->नाम)
		वापस -ENOSYS;

	/* try path-based नाम first */
	rc = server->ops->नाम(xid, tcon, from_path, to_path, cअगरs_sb);

	/*
	 * Don't bother with नाम by filehandle unless file is busy and
	 * source. Note that cross directory moves करो not work with
	 * नाम by filehandle to various Winकरोws servers.
	 */
	अगर (rc == 0 || rc != -EBUSY)
		जाओ करो_नाम_निकास;

	/* Don't fall back to using SMB on SMB 2+ mount */
	अगर (server->vals->protocol_id != 0)
		जाओ करो_नाम_निकास;

	/* खोलो-file नामs करोn't work across directories */
	अगर (to_dentry->d_parent != from_dentry->d_parent)
		जाओ करो_नाम_निकास;

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	/* खोलो the file to be नामd -- we need DELETE perms */
	oparms.desired_access = DELETE;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, CREATE_NOT_सूची);
	oparms.disposition = खाता_OPEN;
	oparms.path = from_path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = CIFS_खोलो(xid, &oparms, &oplock, शून्य);
	अगर (rc == 0) अणु
		rc = CIFSSMBRenameOpenFile(xid, tcon, fid.netfid,
				(स्थिर अक्षर *) to_dentry->d_name.name,
				cअगरs_sb->local_nls, cअगरs_remap(cअगरs_sb));
		CIFSSMBClose(xid, tcon, fid.netfid);
	पूर्ण
करो_नाम_निकास:
	अगर (rc == 0)
		d_move(from_dentry, to_dentry);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

पूर्णांक
cअगरs_नाम2(काष्ठा user_namespace *mnt_userns, काष्ठा inode *source_dir,
	     काष्ठा dentry *source_dentry, काष्ठा inode *target_dir,
	     काष्ठा dentry *target_dentry, अचिन्हित पूर्णांक flags)
अणु
	स्थिर अक्षर *from_name, *to_name;
	व्योम *page1, *page2;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;
	खाता_UNIX_BASIC_INFO *info_buf_source = शून्य;
	खाता_UNIX_BASIC_INFO *info_buf_target;
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc, पंचांगprc;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	cअगरs_sb = CIFS_SB(source_dir->i_sb);
	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(cअगरs_sb)))
		वापस -EIO;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);

	page1 = alloc_dentry_path();
	page2 = alloc_dentry_path();
	xid = get_xid();

	from_name = build_path_from_dentry(source_dentry, page1);
	अगर (IS_ERR(from_name)) अणु
		rc = PTR_ERR(from_name);
		जाओ cअगरs_नाम_निकास;
	पूर्ण

	to_name = build_path_from_dentry(target_dentry, page2);
	अगर (IS_ERR(to_name)) अणु
		rc = PTR_ERR(to_name);
		जाओ cअगरs_नाम_निकास;
	पूर्ण

	cअगरs_बंद_all_deferred_files(tcon);
	rc = cअगरs_करो_नाम(xid, source_dentry, from_name, target_dentry,
			    to_name);

	/*
	 * No-replace is the natural behavior क्रम CIFS, so skip unlink hacks.
	 */
	अगर (flags & RENAME_NOREPLACE)
		जाओ cअगरs_नाम_निकास;

	अगर (rc == -EEXIST && tcon->unix_ext) अणु
		/*
		 * Are src and dst hardlinks of same inode? We can only tell
		 * with unix extensions enabled.
		 */
		info_buf_source =
			kदो_स्मृति_array(2, माप(खाता_UNIX_BASIC_INFO),
					GFP_KERNEL);
		अगर (info_buf_source == शून्य) अणु
			rc = -ENOMEM;
			जाओ cअगरs_नाम_निकास;
		पूर्ण

		info_buf_target = info_buf_source + 1;
		पंचांगprc = CIFSSMBUnixQPathInfo(xid, tcon, from_name,
					     info_buf_source,
					     cअगरs_sb->local_nls,
					     cअगरs_remap(cअगरs_sb));
		अगर (पंचांगprc != 0)
			जाओ unlink_target;

		पंचांगprc = CIFSSMBUnixQPathInfo(xid, tcon, to_name,
					     info_buf_target,
					     cअगरs_sb->local_nls,
					     cअगरs_remap(cअगरs_sb));

		अगर (पंचांगprc == 0 && (info_buf_source->UniqueId ==
				   info_buf_target->UniqueId)) अणु
			/* same file, POSIX says that this is a noop */
			rc = 0;
			जाओ cअगरs_नाम_निकास;
		पूर्ण
	पूर्ण
	/*
	 * अन्यथा ... BB we could add the same check क्रम Winकरोws by
	 * checking the UniqueId via खाता_INTERNAL_INFO
	 */

unlink_target:
	/* Try unlinking the target dentry अगर it's not negative */
	अगर (d_really_is_positive(target_dentry) && (rc == -EACCES || rc == -EEXIST)) अणु
		अगर (d_is_dir(target_dentry))
			पंचांगprc = cअगरs_सूची_हटाओ(target_dir, target_dentry);
		अन्यथा
			पंचांगprc = cअगरs_unlink(target_dir, target_dentry);
		अगर (पंचांगprc)
			जाओ cअगरs_नाम_निकास;
		rc = cअगरs_करो_नाम(xid, source_dentry, from_name,
				    target_dentry, to_name);
	पूर्ण

	/* क्रमce revalidate to go get info when needed */
	CIFS_I(source_dir)->समय = CIFS_I(target_dir)->समय = 0;

	source_dir->i_स_समय = source_dir->i_mसमय = target_dir->i_स_समय =
		target_dir->i_mसमय = current_समय(source_dir);

cअगरs_नाम_निकास:
	kमुक्त(info_buf_source);
	मुक्त_dentry_path(page2);
	मुक्त_dentry_path(page1);
	मुक्त_xid(xid);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

अटल bool
cअगरs_dentry_needs_reval(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा cअगरsInodeInfo *cअगरs_i = CIFS_I(inode);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	काष्ठा cached_fid *cfid = शून्य;

	अगर (cअगरs_i->समय == 0)
		वापस true;

	अगर (CIFS_CACHE_READ(cअगरs_i))
		वापस false;

	अगर (!lookupCacheEnabled)
		वापस true;

	अगर (!खोलो_cached_dir_by_dentry(tcon, dentry->d_parent, &cfid)) अणु
		mutex_lock(&cfid->fid_mutex);
		अगर (cfid->समय && cअगरs_i->समय > cfid->समय) अणु
			mutex_unlock(&cfid->fid_mutex);
			बंद_cached_dir(cfid);
			वापस false;
		पूर्ण
		mutex_unlock(&cfid->fid_mutex);
		बंद_cached_dir(cfid);
	पूर्ण
	/*
	 * depending on inode type, check अगर attribute caching disabled क्रम
	 * files or directories
	 */
	अगर (S_ISसूची(inode->i_mode)) अणु
		अगर (!cअगरs_sb->ctx->acdirmax)
			वापस true;
		अगर (!समय_in_range(jअगरfies, cअगरs_i->समय,
				   cअगरs_i->समय + cअगरs_sb->ctx->acdirmax))
			वापस true;
	पूर्ण अन्यथा अणु /* file */
		अगर (!cअगरs_sb->ctx->acregmax)
			वापस true;
		अगर (!समय_in_range(jअगरfies, cअगरs_i->समय,
				   cअगरs_i->समय + cअगरs_sb->ctx->acregmax))
			वापस true;
	पूर्ण

	/* hardlinked files w/ noserverino get "special" treaपंचांगent */
	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM) &&
	    S_ISREG(inode->i_mode) && inode->i_nlink != 1)
		वापस true;

	वापस false;
पूर्ण

/*
 * Zap the cache. Called when invalid_mapping flag is set.
 */
पूर्णांक
cअगरs_invalidate_mapping(काष्ठा inode *inode)
अणु
	पूर्णांक rc = 0;

	अगर (inode->i_mapping && inode->i_mapping->nrpages != 0) अणु
		rc = invalidate_inode_pages2(inode->i_mapping);
		अगर (rc)
			cअगरs_dbg(VFS, "%s: Could not invalidate inode %p\n",
				 __func__, inode);
	पूर्ण

	cअगरs_fscache_reset_inode_cookie(inode);
	वापस rc;
पूर्ण

/**
 * cअगरs_रुको_bit_समाप्तable - helper क्रम functions that are sleeping on bit locks
 *
 * @key:	currently unused
 * @mode:	the task state to sleep in
 */
अटल पूर्णांक
cअगरs_रुको_bit_समाप्तable(काष्ठा रुको_bit_key *key, पूर्णांक mode)
अणु
	मुक्तzable_schedule_unsafe();
	अगर (संकेत_pending_state(mode, current))
		वापस -ERESTARTSYS;
	वापस 0;
पूर्ण

पूर्णांक
cअगरs_revalidate_mapping(काष्ठा inode *inode)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ *flags = &CIFS_I(inode)->flags;

	/* swapfiles are not supposed to be shared */
	अगर (IS_SWAPखाता(inode))
		वापस 0;

	rc = रुको_on_bit_lock_action(flags, CIFS_INO_LOCK, cअगरs_रुको_bit_समाप्तable,
				     TASK_KILLABLE);
	अगर (rc)
		वापस rc;

	अगर (test_and_clear_bit(CIFS_INO_INVALID_MAPPING, flags)) अणु
		rc = cअगरs_invalidate_mapping(inode);
		अगर (rc)
			set_bit(CIFS_INO_INVALID_MAPPING, flags);
	पूर्ण

	clear_bit_unlock(CIFS_INO_LOCK, flags);
	smp_mb__after_atomic();
	wake_up_bit(flags, CIFS_INO_LOCK);

	वापस rc;
पूर्ण

पूर्णांक
cअगरs_zap_mapping(काष्ठा inode *inode)
अणु
	set_bit(CIFS_INO_INVALID_MAPPING, &CIFS_I(inode)->flags);
	वापस cअगरs_revalidate_mapping(inode);
पूर्ण

पूर्णांक cअगरs_revalidate_file_attr(काष्ठा file *filp)
अणु
	पूर्णांक rc = 0;
	काष्ठा dentry *dentry = file_dentry(filp);
	काष्ठा cअगरsFileInfo *cfile = (काष्ठा cअगरsFileInfo *) filp->निजी_data;

	अगर (!cअगरs_dentry_needs_reval(dentry))
		वापस rc;

	अगर (tlink_tcon(cfile->tlink)->unix_ext)
		rc = cअगरs_get_file_info_unix(filp);
	अन्यथा
		rc = cअगरs_get_file_info(filp);

	वापस rc;
पूर्ण

पूर्णांक cअगरs_revalidate_dentry_attr(काष्ठा dentry *dentry)
अणु
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc = 0;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा super_block *sb = dentry->d_sb;
	स्थिर अक्षर *full_path;
	व्योम *page;
	पूर्णांक count = 0;

	अगर (inode == शून्य)
		वापस -ENOENT;

	अगर (!cअगरs_dentry_needs_reval(dentry))
		वापस rc;

	xid = get_xid();

	page = alloc_dentry_path();
	full_path = build_path_from_dentry(dentry, page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ out;
	पूर्ण

	cअगरs_dbg(FYI, "Update attributes: %s inode 0x%p count %d dentry: 0x%p d_time %ld jiffies %ld\n",
		 full_path, inode, inode->i_count.counter,
		 dentry, cअगरs_get_समय(dentry), jअगरfies);

again:
	अगर (cअगरs_sb_master_tcon(CIFS_SB(sb))->posix_extensions)
		rc = smb311_posix_get_inode_info(&inode, full_path, sb, xid);
	अन्यथा अगर (cअगरs_sb_master_tcon(CIFS_SB(sb))->unix_ext)
		rc = cअगरs_get_inode_info_unix(&inode, full_path, sb, xid);
	अन्यथा
		rc = cअगरs_get_inode_info(&inode, full_path, शून्य, sb,
					 xid, शून्य);
	अगर (rc == -EAGAIN && count++ < 10)
		जाओ again;
out:
	मुक्त_dentry_path(page);
	मुक्त_xid(xid);

	वापस rc;
पूर्ण

पूर्णांक cअगरs_revalidate_file(काष्ठा file *filp)
अणु
	पूर्णांक rc;
	काष्ठा inode *inode = file_inode(filp);

	rc = cअगरs_revalidate_file_attr(filp);
	अगर (rc)
		वापस rc;

	वापस cअगरs_revalidate_mapping(inode);
पूर्ण

/* revalidate a dentry's inode attributes */
पूर्णांक cअगरs_revalidate_dentry(काष्ठा dentry *dentry)
अणु
	पूर्णांक rc;
	काष्ठा inode *inode = d_inode(dentry);

	rc = cअगरs_revalidate_dentry_attr(dentry);
	अगर (rc)
		वापस rc;

	वापस cअगरs_revalidate_mapping(inode);
पूर्ण

पूर्णांक cअगरs_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		 काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(dentry->d_sb);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक rc;

	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(CIFS_SB(inode->i_sb))))
		वापस -EIO;

	/*
	 * We need to be sure that all dirty pages are written and the server
	 * has actual स_समय, mसमय and file length.
	 */
	अगर ((request_mask & (STATX_CTIME | STATX_MTIME | STATX_SIZE | STATX_BLOCKS)) &&
	    !CIFS_CACHE_READ(CIFS_I(inode)) &&
	    inode->i_mapping && inode->i_mapping->nrpages != 0) अणु
		rc = filemap_fdataरुको(inode->i_mapping);
		अगर (rc) अणु
			mapping_set_error(inode->i_mapping, rc);
			वापस rc;
		पूर्ण
	पूर्ण

	अगर ((flags & AT_STATX_SYNC_TYPE) == AT_STATX_FORCE_SYNC)
		CIFS_I(inode)->समय = 0; /* क्रमce revalidate */

	/*
	 * If the caller करोesn't require syncing, only sync अगर
	 * necessary (e.g. due to earlier truncate or setattr
	 * invalidating the cached metadata)
	 */
	अगर (((flags & AT_STATX_SYNC_TYPE) != AT_STATX_DONT_SYNC) ||
	    (CIFS_I(inode)->समय == 0)) अणु
		rc = cअगरs_revalidate_dentry_attr(dentry);
		अगर (rc)
			वापस rc;
	पूर्ण

	generic_fillattr(&init_user_ns, inode, stat);
	stat->blksize = cअगरs_sb->ctx->bsize;
	stat->ino = CIFS_I(inode)->uniqueid;

	/* old CIFS Unix Extensions करोesn't वापस create समय */
	अगर (CIFS_I(inode)->createसमय) अणु
		stat->result_mask |= STATX_BTIME;
		stat->bसमय =
		      cअगरs_NTसमयToUnix(cpu_to_le64(CIFS_I(inode)->createसमय));
	पूर्ण

	stat->attributes_mask |= (STATX_ATTR_COMPRESSED | STATX_ATTR_ENCRYPTED);
	अगर (CIFS_I(inode)->cअगरsAttrs & खाता_ATTRIBUTE_COMPRESSED)
		stat->attributes |= STATX_ATTR_COMPRESSED;
	अगर (CIFS_I(inode)->cअगरsAttrs & खाता_ATTRIBUTE_ENCRYPTED)
		stat->attributes |= STATX_ATTR_ENCRYPTED;

	/*
	 * If on a multiuser mount without unix extensions or cअगरsacl being
	 * enabled, and the admin hasn't overridden them, set the ownership
	 * to the fsuid/fsgid of the current process.
	 */
	अगर ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MULTIUSER) &&
	    !(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_CIFS_ACL) &&
	    !tcon->unix_ext) अणु
		अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_OVERR_UID))
			stat->uid = current_fsuid();
		अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_OVERR_GID))
			stat->gid = current_fsgid();
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cअगरs_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fei, u64 start,
		u64 len)
अणु
	काष्ठा cअगरsInodeInfo *cअगरs_i = CIFS_I(inode);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(cअगरs_i->vfs_inode.i_sb);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	काष्ठा cअगरsFileInfo *cfile;
	पूर्णांक rc;

	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(cअगरs_sb)))
		वापस -EIO;

	/*
	 * We need to be sure that all dirty pages are written as they
	 * might fill holes on the server.
	 */
	अगर (!CIFS_CACHE_READ(CIFS_I(inode)) && inode->i_mapping &&
	    inode->i_mapping->nrpages != 0) अणु
		rc = filemap_fdataरुको(inode->i_mapping);
		अगर (rc) अणु
			mapping_set_error(inode->i_mapping, rc);
			वापस rc;
		पूर्ण
	पूर्ण

	cfile = find_पढ़ोable_file(cअगरs_i, false);
	अगर (cfile == शून्य)
		वापस -EINVAL;

	अगर (server->ops->fiemap) अणु
		rc = server->ops->fiemap(tcon, cfile, fei, start, len);
		cअगरsFileInfo_put(cfile);
		वापस rc;
	पूर्ण

	cअगरsFileInfo_put(cfile);
	वापस -ENOTSUPP;
पूर्ण

पूर्णांक cअगरs_truncate_page(काष्ठा address_space *mapping, loff_t from)
अणु
	pgoff_t index = from >> PAGE_SHIFT;
	अचिन्हित offset = from & (PAGE_SIZE - 1);
	काष्ठा page *page;
	पूर्णांक rc = 0;

	page = grab_cache_page(mapping, index);
	अगर (!page)
		वापस -ENOMEM;

	zero_user_segment(page, offset, PAGE_SIZE);
	unlock_page(page);
	put_page(page);
	वापस rc;
पूर्ण

व्योम cअगरs_setsize(काष्ठा inode *inode, loff_t offset)
अणु
	काष्ठा cअगरsInodeInfo *cअगरs_i = CIFS_I(inode);

	spin_lock(&inode->i_lock);
	i_size_ग_लिखो(inode, offset);
	spin_unlock(&inode->i_lock);

	/* Cached inode must be refreshed on truncate */
	cअगरs_i->समय = 0;
	truncate_pagecache(inode, offset);
पूर्ण

अटल पूर्णांक
cअगरs_set_file_size(काष्ठा inode *inode, काष्ठा iattr *attrs,
		   अचिन्हित पूर्णांक xid, स्थिर अक्षर *full_path)
अणु
	पूर्णांक rc;
	काष्ठा cअगरsFileInfo *खोलो_file;
	काष्ठा cअगरsInodeInfo *cअगरsInode = CIFS_I(inode);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा tcon_link *tlink = शून्य;
	काष्ठा cअगरs_tcon *tcon = शून्य;
	काष्ठा TCP_Server_Info *server;

	/*
	 * To aव्योम spurious oplock अवरोधs from server, in the हाल of
	 * inodes that we alपढ़ोy have खोलो, aव्योम करोing path based
	 * setting of file size अगर we can करो it by handle.
	 * This keeps our caching token (oplock) and aव्योमs समयouts
	 * when the local oplock अवरोध takes दीर्घer to flush
	 * ग_लिखोbehind data than the SMB समयout क्रम the SetPathInfo
	 * request would allow
	 */
	खोलो_file = find_writable_file(cअगरsInode, FIND_WR_FSUID_ONLY);
	अगर (खोलो_file) अणु
		tcon = tlink_tcon(खोलो_file->tlink);
		server = tcon->ses->server;
		अगर (server->ops->set_file_size)
			rc = server->ops->set_file_size(xid, tcon, खोलो_file,
							attrs->ia_size, false);
		अन्यथा
			rc = -ENOSYS;
		cअगरsFileInfo_put(खोलो_file);
		cअगरs_dbg(FYI, "SetFSize for attrs rc = %d\n", rc);
	पूर्ण अन्यथा
		rc = -EINVAL;

	अगर (!rc)
		जाओ set_size_out;

	अगर (tcon == शून्य) अणु
		tlink = cअगरs_sb_tlink(cअगरs_sb);
		अगर (IS_ERR(tlink))
			वापस PTR_ERR(tlink);
		tcon = tlink_tcon(tlink);
		server = tcon->ses->server;
	पूर्ण

	/*
	 * Set file size by pathname rather than by handle either because no
	 * valid, ग_लिखोable file handle क्रम it was found or because there was
	 * an error setting it by handle.
	 */
	अगर (server->ops->set_path_size)
		rc = server->ops->set_path_size(xid, tcon, full_path,
						attrs->ia_size, cअगरs_sb, false);
	अन्यथा
		rc = -ENOSYS;
	cअगरs_dbg(FYI, "SetEOF by path (setattrs) rc = %d\n", rc);

	अगर (tlink)
		cअगरs_put_tlink(tlink);

set_size_out:
	अगर (rc == 0) अणु
		cअगरsInode->server_eof = attrs->ia_size;
		cअगरs_setsize(inode, attrs->ia_size);
		/*
		 * i_blocks is not related to (i_size / i_blksize), but instead
		 * 512 byte (2**9) size is required क्रम calculating num blocks.
		 * Until we can query the server क्रम actual allocation size,
		 * this is best estimate we have क्रम blocks allocated क्रम a file
		 * Number of blocks must be rounded up so size 1 is not 0 blocks
		 */
		inode->i_blocks = (512 - 1 + attrs->ia_size) >> 9;

		/*
		 * The man page of truncate says अगर the size changed,
		 * then the st_स_समय and st_mसमय fields क्रम the file
		 * are updated.
		 */
		attrs->ia_स_समय = attrs->ia_mसमय = current_समय(inode);
		attrs->ia_valid |= ATTR_CTIME | ATTR_MTIME;

		cअगरs_truncate_page(inode->i_mapping, inode->i_size);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_setattr_unix(काष्ठा dentry *direntry, काष्ठा iattr *attrs)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक xid;
	स्थिर अक्षर *full_path;
	व्योम *page = alloc_dentry_path();
	काष्ठा inode *inode = d_inode(direntry);
	काष्ठा cअगरsInodeInfo *cअगरsInode = CIFS_I(inode);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *pTcon;
	काष्ठा cअगरs_unix_set_info_args *args = शून्य;
	काष्ठा cअगरsFileInfo *खोलो_file;

	cअगरs_dbg(FYI, "setattr_unix on file %pd attrs->ia_valid=0x%x\n",
		 direntry, attrs->ia_valid);

	xid = get_xid();

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_PERM)
		attrs->ia_valid |= ATTR_FORCE;

	rc = setattr_prepare(&init_user_ns, direntry, attrs);
	अगर (rc < 0)
		जाओ out;

	full_path = build_path_from_dentry(direntry, page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ out;
	पूर्ण

	/*
	 * Attempt to flush data beक्रमe changing attributes. We need to करो
	 * this क्रम ATTR_SIZE and ATTR_MTIME क्रम sure, and अगर we change the
	 * ownership or mode then we may also need to करो this. Here, we take
	 * the safe way out and just करो the flush on all setattr requests. If
	 * the flush वापसs error, store it to report later and जारी.
	 *
	 * BB: This should be smarter. Why bother flushing pages that
	 * will be truncated anyway? Also, should we error out here अगर
	 * the flush वापसs error?
	 */
	rc = filemap_ग_लिखो_and_रुको(inode->i_mapping);
	अगर (is_पूर्णांकerrupt_error(rc)) अणु
		rc = -ERESTARTSYS;
		जाओ out;
	पूर्ण

	mapping_set_error(inode->i_mapping, rc);
	rc = 0;

	अगर (attrs->ia_valid & ATTR_SIZE) अणु
		rc = cअगरs_set_file_size(inode, attrs, xid, full_path);
		अगर (rc != 0)
			जाओ out;
	पूर्ण

	/* skip mode change अगर it's just क्रम clearing setuid/setgid */
	अगर (attrs->ia_valid & (ATTR_KILL_SUID|ATTR_KILL_SGID))
		attrs->ia_valid &= ~ATTR_MODE;

	args = kदो_स्मृति(माप(*args), GFP_KERNEL);
	अगर (args == शून्य) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* set up the काष्ठा */
	अगर (attrs->ia_valid & ATTR_MODE)
		args->mode = attrs->ia_mode;
	अन्यथा
		args->mode = NO_CHANGE_64;

	अगर (attrs->ia_valid & ATTR_UID)
		args->uid = attrs->ia_uid;
	अन्यथा
		args->uid = INVALID_UID; /* no change */

	अगर (attrs->ia_valid & ATTR_GID)
		args->gid = attrs->ia_gid;
	अन्यथा
		args->gid = INVALID_GID; /* no change */

	अगर (attrs->ia_valid & ATTR_ATIME)
		args->aसमय = cअगरs_UnixTimeToNT(attrs->ia_aसमय);
	अन्यथा
		args->aसमय = NO_CHANGE_64;

	अगर (attrs->ia_valid & ATTR_MTIME)
		args->mसमय = cअगरs_UnixTimeToNT(attrs->ia_mसमय);
	अन्यथा
		args->mसमय = NO_CHANGE_64;

	अगर (attrs->ia_valid & ATTR_CTIME)
		args->स_समय = cअगरs_UnixTimeToNT(attrs->ia_स_समय);
	अन्यथा
		args->स_समय = NO_CHANGE_64;

	args->device = 0;
	खोलो_file = find_writable_file(cअगरsInode, FIND_WR_FSUID_ONLY);
	अगर (खोलो_file) अणु
		u16 nfid = खोलो_file->fid.netfid;
		u32 npid = खोलो_file->pid;
		pTcon = tlink_tcon(खोलो_file->tlink);
		rc = CIFSSMBUnixSetFileInfo(xid, pTcon, args, nfid, npid);
		cअगरsFileInfo_put(खोलो_file);
	पूर्ण अन्यथा अणु
		tlink = cअगरs_sb_tlink(cअगरs_sb);
		अगर (IS_ERR(tlink)) अणु
			rc = PTR_ERR(tlink);
			जाओ out;
		पूर्ण
		pTcon = tlink_tcon(tlink);
		rc = CIFSSMBUnixSetPathInfo(xid, pTcon, full_path, args,
				    cअगरs_sb->local_nls,
				    cअगरs_remap(cअगरs_sb));
		cअगरs_put_tlink(tlink);
	पूर्ण

	अगर (rc)
		जाओ out;

	अगर ((attrs->ia_valid & ATTR_SIZE) &&
	    attrs->ia_size != i_size_पढ़ो(inode))
		truncate_setsize(inode, attrs->ia_size);

	setattr_copy(&init_user_ns, inode, attrs);
	mark_inode_dirty(inode);

	/* क्रमce revalidate when any of these बार are set since some
	   of the fs types (eg ext3, fat) करो not have fine enough
	   समय granularity to match protocol, and we करो not have a
	   a way (yet) to query the server fs's समय granularity (and
	   whether it rounds बार करोwn).
	*/
	अगर (attrs->ia_valid & (ATTR_MTIME | ATTR_CTIME))
		cअगरsInode->समय = 0;
out:
	kमुक्त(args);
	मुक्त_dentry_path(page);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल पूर्णांक
cअगरs_setattr_nounix(काष्ठा dentry *direntry, काष्ठा iattr *attrs)
अणु
	अचिन्हित पूर्णांक xid;
	kuid_t uid = INVALID_UID;
	kgid_t gid = INVALID_GID;
	काष्ठा inode *inode = d_inode(direntry);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा cअगरsInodeInfo *cअगरsInode = CIFS_I(inode);
	काष्ठा cअगरsFileInfo *wfile;
	काष्ठा cअगरs_tcon *tcon;
	स्थिर अक्षर *full_path;
	व्योम *page = alloc_dentry_path();
	पूर्णांक rc = -EACCES;
	__u32 करोsattr = 0;
	__u64 mode = NO_CHANGE_64;

	xid = get_xid();

	cअगरs_dbg(FYI, "setattr on file %pd attrs->ia_valid 0x%x\n",
		 direntry, attrs->ia_valid);

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_PERM)
		attrs->ia_valid |= ATTR_FORCE;

	rc = setattr_prepare(&init_user_ns, direntry, attrs);
	अगर (rc < 0)
		जाओ cअगरs_setattr_निकास;

	full_path = build_path_from_dentry(direntry, page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ cअगरs_setattr_निकास;
	पूर्ण

	/*
	 * Attempt to flush data beक्रमe changing attributes. We need to करो
	 * this क्रम ATTR_SIZE and ATTR_MTIME.  If the flush of the data
	 * वापसs error, store it to report later and जारी.
	 *
	 * BB: This should be smarter. Why bother flushing pages that
	 * will be truncated anyway? Also, should we error out here अगर
	 * the flush वापसs error? Do we need to check क्रम ATTR_MTIME_SET flag?
	 */
	अगर (attrs->ia_valid & (ATTR_MTIME | ATTR_SIZE | ATTR_CTIME)) अणु
		rc = filemap_ग_लिखो_and_रुको(inode->i_mapping);
		अगर (is_पूर्णांकerrupt_error(rc)) अणु
			rc = -ERESTARTSYS;
			जाओ cअगरs_setattr_निकास;
		पूर्ण
		mapping_set_error(inode->i_mapping, rc);
	पूर्ण

	rc = 0;

	अगर ((attrs->ia_valid & ATTR_MTIME) &&
	    !(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NOSSYNC)) अणु
		rc = cअगरs_get_writable_file(cअगरsInode, FIND_WR_ANY, &wfile);
		अगर (!rc) अणु
			tcon = tlink_tcon(wfile->tlink);
			rc = tcon->ses->server->ops->flush(xid, tcon, &wfile->fid);
			cअगरsFileInfo_put(wfile);
			अगर (rc)
				जाओ cअगरs_setattr_निकास;
		पूर्ण अन्यथा अगर (rc != -EBADF)
			जाओ cअगरs_setattr_निकास;
		अन्यथा
			rc = 0;
	पूर्ण

	अगर (attrs->ia_valid & ATTR_SIZE) अणु
		rc = cअगरs_set_file_size(inode, attrs, xid, full_path);
		अगर (rc != 0)
			जाओ cअगरs_setattr_निकास;
	पूर्ण

	अगर (attrs->ia_valid & ATTR_UID)
		uid = attrs->ia_uid;

	अगर (attrs->ia_valid & ATTR_GID)
		gid = attrs->ia_gid;

	अगर ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_CIFS_ACL) ||
	    (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MODE_FROM_SID)) अणु
		अगर (uid_valid(uid) || gid_valid(gid)) अणु
			mode = NO_CHANGE_64;
			rc = id_mode_to_cअगरs_acl(inode, full_path, &mode,
							uid, gid);
			अगर (rc) अणु
				cअगरs_dbg(FYI, "%s: Setting id failed with error: %d\n",
					 __func__, rc);
				जाओ cअगरs_setattr_निकास;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SET_UID))
		attrs->ia_valid &= ~(ATTR_UID | ATTR_GID);

	/* skip mode change अगर it's just क्रम clearing setuid/setgid */
	अगर (attrs->ia_valid & (ATTR_KILL_SUID|ATTR_KILL_SGID))
		attrs->ia_valid &= ~ATTR_MODE;

	अगर (attrs->ia_valid & ATTR_MODE) अणु
		mode = attrs->ia_mode;
		rc = 0;
		अगर ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_CIFS_ACL) ||
		    (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MODE_FROM_SID)) अणु
			rc = id_mode_to_cअगरs_acl(inode, full_path, &mode,
						INVALID_UID, INVALID_GID);
			अगर (rc) अणु
				cअगरs_dbg(FYI, "%s: Setting ACL failed with error: %d\n",
					 __func__, rc);
				जाओ cअगरs_setattr_निकास;
			पूर्ण

			/*
			 * In हाल of CIFS_MOUNT_CIFS_ACL, we cannot support all modes.
			 * Pick up the actual mode bits that were set.
			 */
			अगर (mode != attrs->ia_mode)
				attrs->ia_mode = mode;
		पूर्ण अन्यथा
		अगर (((mode & S_IWUGO) == 0) &&
		    (cअगरsInode->cअगरsAttrs & ATTR_READONLY) == 0) अणु

			करोsattr = cअगरsInode->cअगरsAttrs | ATTR_READONLY;

			/* fix up mode अगर we're not using dynperm */
			अगर ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_DYNPERM) == 0)
				attrs->ia_mode = inode->i_mode & ~S_IWUGO;
		पूर्ण अन्यथा अगर ((mode & S_IWUGO) &&
			   (cअगरsInode->cअगरsAttrs & ATTR_READONLY)) अणु

			करोsattr = cअगरsInode->cअगरsAttrs & ~ATTR_READONLY;
			/* Attributes of 0 are ignored */
			अगर (करोsattr == 0)
				करोsattr |= ATTR_NORMAL;

			/* reset local inode permissions to normal */
			अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_DYNPERM)) अणु
				attrs->ia_mode &= ~(S_IALLUGO);
				अगर (S_ISसूची(inode->i_mode))
					attrs->ia_mode |=
						cअगरs_sb->ctx->dir_mode;
				अन्यथा
					attrs->ia_mode |=
						cअगरs_sb->ctx->file_mode;
			पूर्ण
		पूर्ण अन्यथा अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_DYNPERM)) अणु
			/* ignore mode change - ATTR_READONLY hasn't changed */
			attrs->ia_valid &= ~ATTR_MODE;
		पूर्ण
	पूर्ण

	अगर (attrs->ia_valid & (ATTR_MTIME|ATTR_ATIME|ATTR_CTIME) ||
	    ((attrs->ia_valid & ATTR_MODE) && करोsattr)) अणु
		rc = cअगरs_set_file_info(inode, attrs, xid, full_path, करोsattr);
		/* BB: check क्रम rc = -EOPNOTSUPP and चयन to legacy mode */

		/* Even अगर error on समय set, no sense failing the call अगर
		the server would set the समय to a reasonable value anyway,
		and this check ensures that we are not being called from
		sys_uबार in which हाल we ought to fail the call back to
		the user when the server rejects the call */
		अगर ((rc) && (attrs->ia_valid &
				(ATTR_MODE | ATTR_GID | ATTR_UID | ATTR_SIZE)))
			rc = 0;
	पूर्ण

	/* करो not need local check to inode_check_ok since the server करोes
	   that */
	अगर (rc)
		जाओ cअगरs_setattr_निकास;

	अगर ((attrs->ia_valid & ATTR_SIZE) &&
	    attrs->ia_size != i_size_पढ़ो(inode))
		truncate_setsize(inode, attrs->ia_size);

	setattr_copy(&init_user_ns, inode, attrs);
	mark_inode_dirty(inode);

cअगरs_setattr_निकास:
	मुक्त_xid(xid);
	मुक्त_dentry_path(page);
	वापस rc;
पूर्ण

पूर्णांक
cअगरs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *direntry,
	     काष्ठा iattr *attrs)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(direntry->d_sb);
	काष्ठा cअगरs_tcon *pTcon = cअगरs_sb_master_tcon(cअगरs_sb);
	पूर्णांक rc, retries = 0;

	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(cअगरs_sb)))
		वापस -EIO;

	करो अणु
		अगर (pTcon->unix_ext)
			rc = cअगरs_setattr_unix(direntry, attrs);
		अन्यथा
			rc = cअगरs_setattr_nounix(direntry, attrs);
		retries++;
	पूर्ण जबतक (is_retryable_error(rc) && retries < 2);

	/* BB: add cअगरs_setattr_legacy क्रम really old servers */
	वापस rc;
पूर्ण
