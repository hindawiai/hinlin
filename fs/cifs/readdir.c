<शैली गुरु>
/*
 *   fs/cअगरs/सूची_पढ़ो.c
 *
 *   Directory search handling
 *
 *   Copyright (C) International Business Machines  Corp., 2004, 2008
 *   Copyright (C) Red Hat, Inc., 2011
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
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_unicode.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_fs_sb.h"
#समावेश "cifsfs.h"
#समावेश "smb2proto.h"
#समावेश "fs_context.h"

/*
 * To be safe - क्रम UCS to UTF-8 with strings loaded with the rare दीर्घ
 * अक्षरacters alloc more to account क्रम such multibyte target UTF-8
 * अक्षरacters.
 */
#घोषणा UNICODE_NAME_MAX ((4 * NAME_MAX) + 2)

#अगर_घोषित CONFIG_CIFS_DEBUG2
अटल व्योम dump_cअगरs_file_काष्ठा(काष्ठा file *file, अक्षर *label)
अणु
	काष्ठा cअगरsFileInfo *cf;

	अगर (file) अणु
		cf = file->निजी_data;
		अगर (cf == शून्य) अणु
			cअगरs_dbg(FYI, "empty cifs private file data\n");
			वापस;
		पूर्ण
		अगर (cf->invalidHandle)
			cअगरs_dbg(FYI, "Invalid handle\n");
		अगर (cf->srch_inf.endOfSearch)
			cअगरs_dbg(FYI, "end of search\n");
		अगर (cf->srch_inf.emptyDir)
			cअगरs_dbg(FYI, "empty dir\n");
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dump_cअगरs_file_काष्ठा(काष्ठा file *file, अक्षर *label)
अणु
पूर्ण
#पूर्ण_अगर /* DEBUG2 */

/*
 * Attempt to preload the dcache with the results from the FIND_FIRST/NEXT
 *
 * Find the dentry that matches "name". If there isn't one, create one. If it's
 * a negative dentry or the uniqueid or filetype(mode) changed,
 * then drop it and recreate it.
 */
अटल व्योम
cअगरs_prime_dcache(काष्ठा dentry *parent, काष्ठा qstr *name,
		    काष्ठा cअगरs_fattr *fattr)
अणु
	काष्ठा dentry *dentry, *alias;
	काष्ठा inode *inode;
	काष्ठा super_block *sb = parent->d_sb;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);

	cअगरs_dbg(FYI, "%s: for %s\n", __func__, name->name);

	dentry = d_hash_and_lookup(parent, name);
	अगर (!dentry) अणु
		/*
		 * If we know that the inode will need to be revalidated
		 * immediately, then करोn't create a new dentry क्रम it.
		 * We'll end up करोing an on the wire call either way and
		 * this spares us an invalidation.
		 */
		अगर (fattr->cf_flags & CIFS_FATTR_NEED_REVAL)
			वापस;
retry:
		dentry = d_alloc_parallel(parent, name, &wq);
	पूर्ण
	अगर (IS_ERR(dentry))
		वापस;
	अगर (!d_in_lookup(dentry)) अणु
		inode = d_inode(dentry);
		अगर (inode) अणु
			अगर (d_mountpoपूर्णांक(dentry)) अणु
				dput(dentry);
				वापस;
			पूर्ण
			/*
			 * If we're generating inode numbers, then we don't
			 * want to clobber the existing one with the one that
			 * the सूची_पढ़ो code created.
			 */
			अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM))
				fattr->cf_uniqueid = CIFS_I(inode)->uniqueid;

			/* update inode in place
			 * अगर both i_ino and i_mode didn't change */
			अगर (CIFS_I(inode)->uniqueid == fattr->cf_uniqueid &&
			    cअगरs_fattr_to_inode(inode, fattr) == 0) अणु
				dput(dentry);
				वापस;
			पूर्ण
		पूर्ण
		d_invalidate(dentry);
		dput(dentry);
		जाओ retry;
	पूर्ण अन्यथा अणु
		inode = cअगरs_iget(sb, fattr);
		अगर (!inode)
			inode = ERR_PTR(-ENOMEM);
		alias = d_splice_alias(inode, dentry);
		d_lookup_करोne(dentry);
		अगर (alias && !IS_ERR(alias))
			dput(alias);
	पूर्ण
	dput(dentry);
पूर्ण

अटल bool reparse_file_needs_reval(स्थिर काष्ठा cअगरs_fattr *fattr)
अणु
	अगर (!(fattr->cf_cअगरsattrs & ATTR_REPARSE))
		वापस false;
	/*
	 * The DFS tags should be only पूर्णांकepreted by server side as per
	 * MS-FSCC 2.1.2.1, but let's include them anyway.
	 *
	 * Besides, अगर cf_cअगरstag is unset (0), then we still need it to be
	 * revalidated to know exactly what reparse poपूर्णांक it is.
	 */
	चयन (fattr->cf_cअगरstag) अणु
	हाल IO_REPARSE_TAG_DFS:
	हाल IO_REPARSE_TAG_DFSR:
	हाल IO_REPARSE_TAG_SYMLINK:
	हाल IO_REPARSE_TAG_NFS:
	हाल 0:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम
cअगरs_fill_common_info(काष्ठा cअगरs_fattr *fattr, काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	fattr->cf_uid = cअगरs_sb->ctx->linux_uid;
	fattr->cf_gid = cअगरs_sb->ctx->linux_gid;

	/*
	 * The IO_REPARSE_TAG_LX_ tags originally were used by WSL but they
	 * are preferred by the Linux client in some हालs since, unlike
	 * the NFS reparse tag (or EAs), they करोn't require an extra query
	 * to determine which type of special file they represent.
	 * TODO: go through all करोcumented  reparse tags to see अगर we can
	 * reasonably map some of them to directories vs. files vs. symlinks
	 */
	अगर (fattr->cf_cअगरsattrs & ATTR_सूचीECTORY) अणु
		fattr->cf_mode = S_IFसूची | cअगरs_sb->ctx->dir_mode;
		fattr->cf_dtype = DT_सूची;
	पूर्ण अन्यथा अगर (fattr->cf_cअगरstag == IO_REPARSE_TAG_LX_SYMLINK) अणु
		fattr->cf_mode |= S_IFLNK | cअगरs_sb->ctx->file_mode;
		fattr->cf_dtype = DT_LNK;
	पूर्ण अन्यथा अगर (fattr->cf_cअगरstag == IO_REPARSE_TAG_LX_FIFO) अणु
		fattr->cf_mode |= S_IFIFO | cअगरs_sb->ctx->file_mode;
		fattr->cf_dtype = DT_FIFO;
	पूर्ण अन्यथा अगर (fattr->cf_cअगरstag == IO_REPARSE_TAG_AF_UNIX) अणु
		fattr->cf_mode |= S_IFSOCK | cअगरs_sb->ctx->file_mode;
		fattr->cf_dtype = DT_SOCK;
	पूर्ण अन्यथा अगर (fattr->cf_cअगरstag == IO_REPARSE_TAG_LX_CHR) अणु
		fattr->cf_mode |= S_IFCHR | cअगरs_sb->ctx->file_mode;
		fattr->cf_dtype = DT_CHR;
	पूर्ण अन्यथा अगर (fattr->cf_cअगरstag == IO_REPARSE_TAG_LX_BLK) अणु
		fattr->cf_mode |= S_IFBLK | cअगरs_sb->ctx->file_mode;
		fattr->cf_dtype = DT_BLK;
	पूर्ण अन्यथा अणु /* TODO: should we mark some other reparse poपूर्णांकs (like DFSR) as directories? */
		fattr->cf_mode = S_IFREG | cअगरs_sb->ctx->file_mode;
		fattr->cf_dtype = DT_REG;
	पूर्ण

	/*
	 * We need to revalidate it further to make a decision about whether it
	 * is a symbolic link, DFS referral or a reparse poपूर्णांक with a direct
	 * access like junctions, deduplicated files, NFS symlinks.
	 */
	अगर (reparse_file_needs_reval(fattr))
		fattr->cf_flags |= CIFS_FATTR_NEED_REVAL;

	/* non-unix सूची_पढ़ो करोesn't provide nlink */
	fattr->cf_flags |= CIFS_FATTR_UNKNOWN_NLINK;

	अगर (fattr->cf_cअगरsattrs & ATTR_READONLY)
		fattr->cf_mode &= ~S_IWUGO;

	/*
	 * We of course करोn't get ACL info in FIND_FIRST/NEXT results, so
	 * mark it क्रम revalidation so that "ls -l" will look right. It might
	 * be super-slow, but अगर we करोn't करो this then the ownership of files
	 * may look wrong since the inodes may not have समयd out by the समय
	 * "ls" करोes a stat() call on them.
	 */
	अगर ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_CIFS_ACL) ||
	    (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MODE_FROM_SID))
		fattr->cf_flags |= CIFS_FATTR_NEED_REVAL;

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_UNX_EMUL &&
	    fattr->cf_cअगरsattrs & ATTR_SYSTEM) अणु
		अगर (fattr->cf_eof == 0)  अणु
			fattr->cf_mode &= ~S_IFMT;
			fattr->cf_mode |= S_IFIFO;
			fattr->cf_dtype = DT_FIFO;
		पूर्ण अन्यथा अणु
			/*
			 * trying to get the type and mode via SFU can be slow,
			 * so just call those regular files क्रम now, and mark
			 * क्रम reval
			 */
			fattr->cf_flags |= CIFS_FATTR_NEED_REVAL;
		पूर्ण
	पूर्ण
पूर्ण

/* Fill a cअगरs_fattr काष्ठा with info from SMB_FIND_खाता_POSIX_INFO. */
अटल व्योम
cअगरs_posix_to_fattr(काष्ठा cअगरs_fattr *fattr, काष्ठा smb2_posix_info *info,
		    काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	काष्ठा smb2_posix_info_parsed parsed;

	posix_info_parse(info, शून्य, &parsed);

	स_रखो(fattr, 0, माप(*fattr));
	fattr->cf_uniqueid = le64_to_cpu(info->Inode);
	fattr->cf_bytes = le64_to_cpu(info->AllocationSize);
	fattr->cf_eof = le64_to_cpu(info->EndOfFile);

	fattr->cf_aसमय = cअगरs_NTसमयToUnix(info->LastAccessTime);
	fattr->cf_mसमय = cअगरs_NTसमयToUnix(info->LastWriteTime);
	fattr->cf_स_समय = cअगरs_NTसमयToUnix(info->CreationTime);

	fattr->cf_nlink = le32_to_cpu(info->HardLinks);
	fattr->cf_cअगरsattrs = le32_to_cpu(info->DosAttributes);

	/*
	 * Since we set the inode type below we need to mask off
	 * to aव्योम strange results अगर bits set above.
	 * XXX: why not make server&client use the type bits?
	 */
	fattr->cf_mode = le32_to_cpu(info->Mode) & ~S_IFMT;

	cअगरs_dbg(FYI, "posix fattr: dev %d, reparse %d, mode %o\n",
		 le32_to_cpu(info->DeviceId),
		 le32_to_cpu(info->ReparseTag),
		 le32_to_cpu(info->Mode));

	अगर (fattr->cf_cअगरsattrs & ATTR_सूचीECTORY) अणु
		fattr->cf_mode |= S_IFसूची;
		fattr->cf_dtype = DT_सूची;
	पूर्ण अन्यथा अणु
		/*
		 * mark anything that is not a dir as regular
		 * file. special files should have the REPARSE
		 * attribute and will be marked as needing revaluation
		 */
		fattr->cf_mode |= S_IFREG;
		fattr->cf_dtype = DT_REG;
	पूर्ण

	अगर (reparse_file_needs_reval(fattr))
		fattr->cf_flags |= CIFS_FATTR_NEED_REVAL;

	sid_to_id(cअगरs_sb, &parsed.owner, fattr, SIDOWNER);
	sid_to_id(cअगरs_sb, &parsed.group, fattr, SIDGROUP);
पूर्ण

अटल व्योम __dir_info_to_fattr(काष्ठा cअगरs_fattr *fattr, स्थिर व्योम *info)
अणु
	स्थिर खाता_सूचीECTORY_INFO *fi = info;

	स_रखो(fattr, 0, माप(*fattr));
	fattr->cf_cअगरsattrs = le32_to_cpu(fi->ExtFileAttributes);
	fattr->cf_eof = le64_to_cpu(fi->EndOfFile);
	fattr->cf_bytes = le64_to_cpu(fi->AllocationSize);
	fattr->cf_createसमय = le64_to_cpu(fi->CreationTime);
	fattr->cf_aसमय = cअगरs_NTसमयToUnix(fi->LastAccessTime);
	fattr->cf_स_समय = cअगरs_NTसमयToUnix(fi->ChangeTime);
	fattr->cf_mसमय = cअगरs_NTसमयToUnix(fi->LastWriteTime);
पूर्ण

व्योम
cअगरs_dir_info_to_fattr(काष्ठा cअगरs_fattr *fattr, खाता_सूचीECTORY_INFO *info,
		       काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	__dir_info_to_fattr(fattr, info);
	cअगरs_fill_common_info(fattr, cअगरs_sb);
पूर्ण

अटल व्योम cअगरs_fulldir_info_to_fattr(काष्ठा cअगरs_fattr *fattr,
				       SEARCH_ID_FULL_सूची_INFO *info,
				       काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	__dir_info_to_fattr(fattr, info);

	/* See MS-FSCC 2.4.18 FileIdFullDirectoryInक्रमmation */
	अगर (fattr->cf_cअगरsattrs & ATTR_REPARSE)
		fattr->cf_cअगरstag = le32_to_cpu(info->EaSize);
	cअगरs_fill_common_info(fattr, cअगरs_sb);
पूर्ण

अटल व्योम
cअगरs_std_info_to_fattr(काष्ठा cअगरs_fattr *fattr, FIND_खाता_STANDARD_INFO *info,
		       काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	पूर्णांक offset = cअगरs_sb_master_tcon(cअगरs_sb)->ses->server->समयAdj;

	स_रखो(fattr, 0, माप(*fattr));
	fattr->cf_aसमय = cnvrtDosUnixTm(info->LastAccessDate,
					    info->LastAccessTime, offset);
	fattr->cf_स_समय = cnvrtDosUnixTm(info->LastWriteDate,
					    info->LastWriteTime, offset);
	fattr->cf_mसमय = cnvrtDosUnixTm(info->LastWriteDate,
					    info->LastWriteTime, offset);

	fattr->cf_cअगरsattrs = le16_to_cpu(info->Attributes);
	fattr->cf_bytes = le32_to_cpu(info->AllocationSize);
	fattr->cf_eof = le32_to_cpu(info->DataSize);

	cअगरs_fill_common_info(fattr, cअगरs_sb);
पूर्ण

/* BB eventually need to add the following helper function to
      resolve NT_STATUS_STOPPED_ON_SYMLINK वापस code when
      we try to करो FindFirst on (NTFS) directory symlinks */
/*
पूर्णांक get_symlink_reparse_path(अक्षर *full_path, काष्ठा cअगरs_sb_info *cअगरs_sb,
			     अचिन्हित पूर्णांक xid)
अणु
	__u16 fid;
	पूर्णांक len;
	पूर्णांक oplock = 0;
	पूर्णांक rc;
	काष्ठा cअगरs_tcon *ptcon = cअगरs_sb_tcon(cअगरs_sb);
	अक्षर *पंचांगpbuffer;

	rc = CIFSSMBOpen(xid, ptcon, full_path, खाता_OPEN, GENERIC_READ,
			OPEN_REPARSE_POINT, &fid, &oplock, शून्य,
			cअगरs_sb->local_nls,
			cअगरs_remap(cअगरs_sb);
	अगर (!rc) अणु
		पंचांगpbuffer = kदो_स्मृति(maxpath);
		rc = CIFSSMBQueryReparseLinkInfo(xid, ptcon, full_path,
				पंचांगpbuffer,
				maxpath -1,
				fid,
				cअगरs_sb->local_nls);
		अगर (CIFSSMBClose(xid, ptcon, fid)) अणु
			cअगरs_dbg(FYI, "Error closing temporary reparsepoint open\n");
		पूर्ण
	पूर्ण
पूर्ण
 */

अटल पूर्णांक
initiate_cअगरs_search(स्थिर अचिन्हित पूर्णांक xid, काष्ठा file *file,
		     स्थिर अक्षर *full_path)
अणु
	__u16 search_flags;
	पूर्णांक rc = 0;
	काष्ठा cअगरsFileInfo *cअगरsFile;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_खाता_SB(file);
	काष्ठा tcon_link *tlink = शून्य;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;

	अगर (file->निजी_data == शून्य) अणु
		tlink = cअगरs_sb_tlink(cअगरs_sb);
		अगर (IS_ERR(tlink))
			वापस PTR_ERR(tlink);

		cअगरsFile = kzalloc(माप(काष्ठा cअगरsFileInfo), GFP_KERNEL);
		अगर (cअगरsFile == शून्य) अणु
			rc = -ENOMEM;
			जाओ error_निकास;
		पूर्ण
		spin_lock_init(&cअगरsFile->file_info_lock);
		file->निजी_data = cअगरsFile;
		cअगरsFile->tlink = cअगरs_get_tlink(tlink);
		tcon = tlink_tcon(tlink);
	पूर्ण अन्यथा अणु
		cअगरsFile = file->निजी_data;
		tcon = tlink_tcon(cअगरsFile->tlink);
	पूर्ण

	server = tcon->ses->server;

	अगर (!server->ops->query_dir_first) अणु
		rc = -ENOSYS;
		जाओ error_निकास;
	पूर्ण

	cअगरsFile->invalidHandle = true;
	cअगरsFile->srch_inf.endOfSearch = false;

	cअगरs_dbg(FYI, "Full path: %s start at: %lld\n", full_path, file->f_pos);

ffirst_retry:
	/* test क्रम Unix extensions */
	/* but now check क्रम them on the share/mount not on the SMB session */
	/* अगर (cap_unix(tcon->ses) अणु */
	अगर (tcon->unix_ext)
		cअगरsFile->srch_inf.info_level = SMB_FIND_खाता_UNIX;
	अन्यथा अगर (tcon->posix_extensions)
		cअगरsFile->srch_inf.info_level = SMB_FIND_खाता_POSIX_INFO;
	अन्यथा अगर ((tcon->ses->capabilities &
		  tcon->ses->server->vals->cap_nt_find) == 0) अणु
		cअगरsFile->srch_inf.info_level = SMB_FIND_खाता_INFO_STANDARD;
	पूर्ण अन्यथा अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM) अणु
		cअगरsFile->srch_inf.info_level = SMB_FIND_खाता_ID_FULL_सूची_INFO;
	पूर्ण अन्यथा /* not srvinos - BB fixme add check क्रम backlevel? */ अणु
		cअगरsFile->srch_inf.info_level = SMB_FIND_खाता_सूचीECTORY_INFO;
	पूर्ण

	search_flags = CIFS_SEARCH_CLOSE_AT_END | CIFS_SEARCH_RETURN_RESUME;
	अगर (backup_cred(cअगरs_sb))
		search_flags |= CIFS_SEARCH_BACKUP_SEARCH;

	rc = server->ops->query_dir_first(xid, tcon, full_path, cअगरs_sb,
					  &cअगरsFile->fid, search_flags,
					  &cअगरsFile->srch_inf);

	अगर (rc == 0)
		cअगरsFile->invalidHandle = false;
	/* BB add following call to handle सूची_पढ़ो on new NTFS symlink errors
	अन्यथा अगर STATUS_STOPPED_ON_SYMLINK
		call get_symlink_reparse_path and retry with new path */
	अन्यथा अगर ((rc == -EOPNOTSUPP) &&
		(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM)) अणु
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_SERVER_INUM;
		जाओ ffirst_retry;
	पूर्ण
error_निकास:
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

/* वापस length of unicode string in bytes */
अटल पूर्णांक cअगरs_unicode_bytelen(स्थिर अक्षर *str)
अणु
	पूर्णांक len;
	स्थिर __le16 *ustr = (स्थिर __le16 *)str;

	क्रम (len = 0; len <= PATH_MAX; len++) अणु
		अगर (ustr[len] == 0)
			वापस len << 1;
	पूर्ण
	cअगरs_dbg(FYI, "Unicode string longer than PATH_MAX found\n");
	वापस len << 1;
पूर्ण

अटल अक्षर *nxt_dir_entry(अक्षर *old_entry, अक्षर *end_of_smb, पूर्णांक level)
अणु
	अक्षर *new_entry;
	खाता_सूचीECTORY_INFO *pDirInfo = (खाता_सूचीECTORY_INFO *)old_entry;

	अगर (level == SMB_FIND_खाता_INFO_STANDARD) अणु
		FIND_खाता_STANDARD_INFO *pfData;
		pfData = (FIND_खाता_STANDARD_INFO *)pDirInfo;

		new_entry = old_entry + माप(FIND_खाता_STANDARD_INFO) +
				pfData->FileNameLength;
	पूर्ण अन्यथा अणु
		u32 next_offset = le32_to_cpu(pDirInfo->NextEntryOffset);

		अगर (old_entry + next_offset < old_entry) अणु
			cअगरs_dbg(VFS, "Invalid offset %u\n", next_offset);
			वापस शून्य;
		पूर्ण
		new_entry = old_entry + next_offset;
	पूर्ण
	cअगरs_dbg(FYI, "new entry %p old entry %p\n", new_entry, old_entry);
	/* validate that new_entry is not past end of SMB */
	अगर (new_entry >= end_of_smb) अणु
		cअगरs_dbg(VFS, "search entry %p began after end of SMB %p old entry %p\n",
			 new_entry, end_of_smb, old_entry);
		वापस शून्य;
	पूर्ण अन्यथा अगर (((level == SMB_FIND_खाता_INFO_STANDARD) &&
		    (new_entry + माप(FIND_खाता_STANDARD_INFO) > end_of_smb))
		  || ((level != SMB_FIND_खाता_INFO_STANDARD) &&
		   (new_entry + माप(खाता_सूचीECTORY_INFO) > end_of_smb)))  अणु
		cअगरs_dbg(VFS, "search entry %p extends after end of SMB %p\n",
			 new_entry, end_of_smb);
		वापस शून्य;
	पूर्ण अन्यथा
		वापस new_entry;

पूर्ण

काष्ठा cअगरs_dirent अणु
	स्थिर अक्षर	*name;
	माप_प्रकार		namelen;
	u32		resume_key;
	u64		ino;
पूर्ण;

अटल व्योम cअगरs_fill_dirent_posix(काष्ठा cअगरs_dirent *de,
				   स्थिर काष्ठा smb2_posix_info *info)
अणु
	काष्ठा smb2_posix_info_parsed parsed;

	/* payload should have alपढ़ोy been checked at this poपूर्णांक */
	अगर (posix_info_parse(info, शून्य, &parsed) < 0) अणु
		cअगरs_dbg(VFS, "Invalid POSIX info payload\n");
		वापस;
	पूर्ण

	de->name = parsed.name;
	de->namelen = parsed.name_len;
	de->resume_key = info->Ignored;
	de->ino = le64_to_cpu(info->Inode);
पूर्ण

अटल व्योम cअगरs_fill_dirent_unix(काष्ठा cअगरs_dirent *de,
		स्थिर खाता_UNIX_INFO *info, bool is_unicode)
अणु
	de->name = &info->FileName[0];
	अगर (is_unicode)
		de->namelen = cअगरs_unicode_bytelen(de->name);
	अन्यथा
		de->namelen = strnlen(de->name, PATH_MAX);
	de->resume_key = info->ResumeKey;
	de->ino = le64_to_cpu(info->basic.UniqueId);
पूर्ण

अटल व्योम cअगरs_fill_dirent_dir(काष्ठा cअगरs_dirent *de,
		स्थिर खाता_सूचीECTORY_INFO *info)
अणु
	de->name = &info->FileName[0];
	de->namelen = le32_to_cpu(info->FileNameLength);
	de->resume_key = info->FileIndex;
पूर्ण

अटल व्योम cअगरs_fill_dirent_full(काष्ठा cअगरs_dirent *de,
		स्थिर खाता_FULL_सूचीECTORY_INFO *info)
अणु
	de->name = &info->FileName[0];
	de->namelen = le32_to_cpu(info->FileNameLength);
	de->resume_key = info->FileIndex;
पूर्ण

अटल व्योम cअगरs_fill_dirent_search(काष्ठा cअगरs_dirent *de,
		स्थिर SEARCH_ID_FULL_सूची_INFO *info)
अणु
	de->name = &info->FileName[0];
	de->namelen = le32_to_cpu(info->FileNameLength);
	de->resume_key = info->FileIndex;
	de->ino = le64_to_cpu(info->UniqueId);
पूर्ण

अटल व्योम cअगरs_fill_dirent_both(काष्ठा cअगरs_dirent *de,
		स्थिर खाता_BOTH_सूचीECTORY_INFO *info)
अणु
	de->name = &info->FileName[0];
	de->namelen = le32_to_cpu(info->FileNameLength);
	de->resume_key = info->FileIndex;
पूर्ण

अटल व्योम cअगरs_fill_dirent_std(काष्ठा cअगरs_dirent *de,
		स्थिर FIND_खाता_STANDARD_INFO *info)
अणु
	de->name = &info->FileName[0];
	/* one byte length, no endianess conversion */
	de->namelen = info->FileNameLength;
	de->resume_key = info->ResumeKey;
पूर्ण

अटल पूर्णांक cअगरs_fill_dirent(काष्ठा cअगरs_dirent *de, स्थिर व्योम *info,
		u16 level, bool is_unicode)
अणु
	स_रखो(de, 0, माप(*de));

	चयन (level) अणु
	हाल SMB_FIND_खाता_POSIX_INFO:
		cअगरs_fill_dirent_posix(de, info);
		अवरोध;
	हाल SMB_FIND_खाता_UNIX:
		cअगरs_fill_dirent_unix(de, info, is_unicode);
		अवरोध;
	हाल SMB_FIND_खाता_सूचीECTORY_INFO:
		cअगरs_fill_dirent_dir(de, info);
		अवरोध;
	हाल SMB_FIND_खाता_FULL_सूचीECTORY_INFO:
		cअगरs_fill_dirent_full(de, info);
		अवरोध;
	हाल SMB_FIND_खाता_ID_FULL_सूची_INFO:
		cअगरs_fill_dirent_search(de, info);
		अवरोध;
	हाल SMB_FIND_खाता_BOTH_सूचीECTORY_INFO:
		cअगरs_fill_dirent_both(de, info);
		अवरोध;
	हाल SMB_FIND_खाता_INFO_STANDARD:
		cअगरs_fill_dirent_std(de, info);
		अवरोध;
	शेष:
		cअगरs_dbg(FYI, "Unknown findfirst level %d\n", level);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा UNICODE_DOT cpu_to_le16(0x2e)

/* वापस 0 अगर no match and 1 क्रम . (current directory) and 2 क्रम .. (parent) */
अटल पूर्णांक cअगरs_entry_is_करोt(काष्ठा cअगरs_dirent *de, bool is_unicode)
अणु
	पूर्णांक rc = 0;

	अगर (!de->name)
		वापस 0;

	अगर (is_unicode) अणु
		__le16 *ufilename = (__le16 *)de->name;
		अगर (de->namelen == 2) अणु
			/* check क्रम . */
			अगर (ufilename[0] == UNICODE_DOT)
				rc = 1;
		पूर्ण अन्यथा अगर (de->namelen == 4) अणु
			/* check क्रम .. */
			अगर (ufilename[0] == UNICODE_DOT &&
			    ufilename[1] == UNICODE_DOT)
				rc = 2;
		पूर्ण
	पूर्ण अन्यथा /* ASCII */ अणु
		अगर (de->namelen == 1) अणु
			अगर (de->name[0] == '.')
				rc = 1;
		पूर्ण अन्यथा अगर (de->namelen == 2) अणु
			अगर (de->name[0] == '.' && de->name[1] == '.')
				rc = 2;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/* Check अगर directory that we are searching has changed so we can decide
   whether we can use the cached search results from the previous search */
अटल पूर्णांक is_dir_changed(काष्ठा file *file)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा cअगरsInodeInfo *cअगरsInfo = CIFS_I(inode);

	अगर (cअगरsInfo->समय == 0)
		वापस 1; /* directory was changed, perhaps due to unlink */
	अन्यथा
		वापस 0;

पूर्ण

अटल पूर्णांक cअगरs_save_resume_key(स्थिर अक्षर *current_entry,
	काष्ठा cअगरsFileInfo *file_info)
अणु
	काष्ठा cअगरs_dirent de;
	पूर्णांक rc;

	rc = cअगरs_fill_dirent(&de, current_entry, file_info->srch_inf.info_level,
			      file_info->srch_inf.unicode);
	अगर (!rc) अणु
		file_info->srch_inf.presume_name = de.name;
		file_info->srch_inf.resume_name_len = de.namelen;
		file_info->srch_inf.resume_key = de.resume_key;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Find the corresponding entry in the search. Note that the SMB server वापसs
 * search entries क्रम . and .. which complicates logic here अगर we choose to
 * parse क्रम them and we करो not assume that they are located in the findfirst
 * वापस buffer. We start counting in the buffer with entry 2 and increment क्रम
 * every entry (करो not increment क्रम . or .. entry).
 */
अटल पूर्णांक
find_cअगरs_entry(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon, loff_t pos,
		काष्ठा file *file, स्थिर अक्षर *full_path,
		अक्षर **current_entry, पूर्णांक *num_to_ret)
अणु
	__u16 search_flags;
	पूर्णांक rc = 0;
	पूर्णांक pos_in_buf = 0;
	loff_t first_entry_in_buffer;
	loff_t index_to_find = pos;
	काष्ठा cअगरsFileInfo *cfile = file->निजी_data;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_खाता_SB(file);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	/* check अगर index in the buffer */

	अगर (!server->ops->query_dir_first || !server->ops->query_dir_next)
		वापस -ENOSYS;

	अगर ((cfile == शून्य) || (current_entry == शून्य) || (num_to_ret == शून्य))
		वापस -ENOENT;

	*current_entry = शून्य;
	first_entry_in_buffer = cfile->srch_inf.index_of_last_entry -
					cfile->srch_inf.entries_in_buffer;

	/*
	 * If first entry in buf is zero then is first buffer
	 * in search response data which means it is likely . and ..
	 * will be in this buffer, although some servers करो not वापस
	 * . and .. क्रम the root of a drive and क्रम those we need
	 * to start two entries earlier.
	 */

	dump_cअगरs_file_काष्ठा(file, "In fce ");
	अगर (((index_to_find < cfile->srch_inf.index_of_last_entry) &&
	     is_dir_changed(file)) || (index_to_find < first_entry_in_buffer)) अणु
		/* बंद and restart search */
		cअगरs_dbg(FYI, "search backing up - close and restart search\n");
		spin_lock(&cfile->file_info_lock);
		अगर (server->ops->dir_needs_बंद(cfile)) अणु
			cfile->invalidHandle = true;
			spin_unlock(&cfile->file_info_lock);
			अगर (server->ops->बंद_dir)
				server->ops->बंद_dir(xid, tcon, &cfile->fid);
		पूर्ण अन्यथा
			spin_unlock(&cfile->file_info_lock);
		अगर (cfile->srch_inf.ntwrk_buf_start) अणु
			cअगरs_dbg(FYI, "freeing SMB ff cache buf on search rewind\n");
			अगर (cfile->srch_inf.smallBuf)
				cअगरs_small_buf_release(cfile->srch_inf.
						ntwrk_buf_start);
			अन्यथा
				cअगरs_buf_release(cfile->srch_inf.
						ntwrk_buf_start);
			cfile->srch_inf.ntwrk_buf_start = शून्य;
		पूर्ण
		rc = initiate_cअगरs_search(xid, file, full_path);
		अगर (rc) अणु
			cअगरs_dbg(FYI, "error %d reinitiating a search on rewind\n",
				 rc);
			वापस rc;
		पूर्ण
		/* FindFirst/Next set last_entry to शून्य on malक्रमmed reply */
		अगर (cfile->srch_inf.last_entry)
			cअगरs_save_resume_key(cfile->srch_inf.last_entry, cfile);
	पूर्ण

	search_flags = CIFS_SEARCH_CLOSE_AT_END | CIFS_SEARCH_RETURN_RESUME;
	अगर (backup_cred(cअगरs_sb))
		search_flags |= CIFS_SEARCH_BACKUP_SEARCH;

	जबतक ((index_to_find >= cfile->srch_inf.index_of_last_entry) &&
	       (rc == 0) && !cfile->srch_inf.endOfSearch) अणु
		cअगरs_dbg(FYI, "calling findnext2\n");
		rc = server->ops->query_dir_next(xid, tcon, &cfile->fid,
						 search_flags,
						 &cfile->srch_inf);
		/* FindFirst/Next set last_entry to शून्य on malक्रमmed reply */
		अगर (cfile->srch_inf.last_entry)
			cअगरs_save_resume_key(cfile->srch_inf.last_entry, cfile);
		अगर (rc)
			वापस -ENOENT;
	पूर्ण
	अगर (index_to_find < cfile->srch_inf.index_of_last_entry) अणु
		/* we found the buffer that contains the entry */
		/* scan and find it */
		पूर्णांक i;
		अक्षर *cur_ent;
		अक्षर *end_of_smb;

		अगर (cfile->srch_inf.ntwrk_buf_start == शून्य) अणु
			cअगरs_dbg(VFS, "ntwrk_buf_start is NULL during readdir\n");
			वापस -EIO;
		पूर्ण

		end_of_smb = cfile->srch_inf.ntwrk_buf_start +
			server->ops->calc_smb_size(
					cfile->srch_inf.ntwrk_buf_start,
					server);

		cur_ent = cfile->srch_inf.srch_entries_start;
		first_entry_in_buffer = cfile->srch_inf.index_of_last_entry
					- cfile->srch_inf.entries_in_buffer;
		pos_in_buf = index_to_find - first_entry_in_buffer;
		cअगरs_dbg(FYI, "found entry - pos_in_buf %d\n", pos_in_buf);

		क्रम (i = 0; (i < (pos_in_buf)) && (cur_ent != शून्य); i++) अणु
			/* go entry by entry figuring out which is first */
			cur_ent = nxt_dir_entry(cur_ent, end_of_smb,
						cfile->srch_inf.info_level);
		पूर्ण
		अगर ((cur_ent == शून्य) && (i < pos_in_buf)) अणु
			/* BB fixme - check अगर we should flag this error */
			cअगरs_dbg(VFS, "reached end of buf searching for pos in buf %d index to find %lld rc %d\n",
				 pos_in_buf, index_to_find, rc);
		पूर्ण
		rc = 0;
		*current_entry = cur_ent;
	पूर्ण अन्यथा अणु
		cअगरs_dbg(FYI, "index not in buffer - could not findnext into it\n");
		वापस 0;
	पूर्ण

	अगर (pos_in_buf >= cfile->srch_inf.entries_in_buffer) अणु
		cअगरs_dbg(FYI, "can not return entries pos_in_buf beyond last\n");
		*num_to_ret = 0;
	पूर्ण अन्यथा
		*num_to_ret = cfile->srch_inf.entries_in_buffer - pos_in_buf;

	वापस rc;
पूर्ण

अटल पूर्णांक cअगरs_filldir(अक्षर *find_entry, काष्ठा file *file,
		काष्ठा dir_context *ctx,
		अक्षर *scratch_buf, अचिन्हित पूर्णांक max_len)
अणु
	काष्ठा cअगरsFileInfo *file_info = file->निजी_data;
	काष्ठा super_block *sb = file_inode(file)->i_sb;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा cअगरs_dirent de = अणु शून्य, पूर्ण;
	काष्ठा cअगरs_fattr fattr;
	काष्ठा qstr name;
	पूर्णांक rc = 0;
	ino_t ino;

	rc = cअगरs_fill_dirent(&de, find_entry, file_info->srch_inf.info_level,
			      file_info->srch_inf.unicode);
	अगर (rc)
		वापस rc;

	अगर (de.namelen > max_len) अणु
		cअगरs_dbg(VFS, "bad search response length %zd past smb end\n",
			 de.namelen);
		वापस -EINVAL;
	पूर्ण

	/* skip . and .. since we added them first */
	अगर (cअगरs_entry_is_करोt(&de, file_info->srch_inf.unicode))
		वापस 0;

	अगर (file_info->srch_inf.unicode) अणु
		काष्ठा nls_table *nlt = cअगरs_sb->local_nls;
		पूर्णांक map_type;

		map_type = cअगरs_remap(cअगरs_sb);
		name.name = scratch_buf;
		name.len =
			cअगरs_from_utf16((अक्षर *)name.name, (__le16 *)de.name,
					UNICODE_NAME_MAX,
					min_t(माप_प्रकार, de.namelen,
					      (माप_प्रकार)max_len), nlt, map_type);
		name.len -= nls_nullsize(nlt);
	पूर्ण अन्यथा अणु
		name.name = de.name;
		name.len = de.namelen;
	पूर्ण

	चयन (file_info->srch_inf.info_level) अणु
	हाल SMB_FIND_खाता_POSIX_INFO:
		cअगरs_posix_to_fattr(&fattr,
				    (काष्ठा smb2_posix_info *)find_entry,
				    cअगरs_sb);
		अवरोध;
	हाल SMB_FIND_खाता_UNIX:
		cअगरs_unix_basic_to_fattr(&fattr,
					 &((खाता_UNIX_INFO *)find_entry)->basic,
					 cअगरs_sb);
		अवरोध;
	हाल SMB_FIND_खाता_INFO_STANDARD:
		cअगरs_std_info_to_fattr(&fattr,
				       (FIND_खाता_STANDARD_INFO *)find_entry,
				       cअगरs_sb);
		अवरोध;
	हाल SMB_FIND_खाता_ID_FULL_सूची_INFO:
		cअगरs_fulldir_info_to_fattr(&fattr,
					   (SEARCH_ID_FULL_सूची_INFO *)find_entry,
					   cअगरs_sb);
		अवरोध;
	शेष:
		cअगरs_dir_info_to_fattr(&fattr,
				       (खाता_सूचीECTORY_INFO *)find_entry,
				       cअगरs_sb);
		अवरोध;
	पूर्ण

	अगर (de.ino && (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM)) अणु
		fattr.cf_uniqueid = de.ino;
	पूर्ण अन्यथा अणु
		fattr.cf_uniqueid = iunique(sb, ROOT_I);
		cअगरs_स्वतःdisable_serverino(cअगरs_sb);
	पूर्ण

	अगर ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MF_SYMLINKS) &&
	    couldbe_mf_symlink(&fattr))
		/*
		 * trying to get the type and mode can be slow,
		 * so just call those regular files क्रम now, and mark
		 * क्रम reval
		 */
		fattr.cf_flags |= CIFS_FATTR_NEED_REVAL;

	cअगरs_prime_dcache(file_dentry(file), &name, &fattr);

	ino = cअगरs_uniqueid_to_ino_t(fattr.cf_uniqueid);
	वापस !dir_emit(ctx, name.name, name.len, ino, fattr.cf_dtype);
पूर्ण


पूर्णांक cअगरs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक xid;
	पूर्णांक i;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरsFileInfo *cअगरsFile = शून्य;
	अक्षर *current_entry;
	पूर्णांक num_to_fill = 0;
	अक्षर *पंचांगp_buf = शून्य;
	अक्षर *end_of_smb;
	अचिन्हित पूर्णांक max_len;
	स्थिर अक्षर *full_path;
	व्योम *page = alloc_dentry_path();

	xid = get_xid();

	full_path = build_path_from_dentry(file_dentry(file), page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ rddir2_निकास;
	पूर्ण

	/*
	 * Ensure FindFirst करोesn't fail before doing filldir() for '.' and
	 * '..'. Otherwise we won't be able to notअगरy VFS in हाल of failure.
	 */
	अगर (file->निजी_data == शून्य) अणु
		rc = initiate_cअगरs_search(xid, file, full_path);
		cअगरs_dbg(FYI, "initiate cifs search rc %d\n", rc);
		अगर (rc)
			जाओ rddir2_निकास;
	पूर्ण

	अगर (!dir_emit_करोts(file, ctx))
		जाओ rddir2_निकास;

	/* 1) If search is active,
		is in current search buffer?
		अगर it beक्रमe then restart search
		अगर after then keep searching till find it */

	cअगरsFile = file->निजी_data;
	अगर (cअगरsFile->srch_inf.endOfSearch) अणु
		अगर (cअगरsFile->srch_inf.emptyDir) अणु
			cअगरs_dbg(FYI, "End of search, empty dir\n");
			rc = 0;
			जाओ rddir2_निकास;
		पूर्ण
	पूर्ण /* अन्यथा अणु
		cअगरsFile->invalidHandle = true;
		tcon->ses->server->बंद(xid, tcon, &cअगरsFile->fid);
	पूर्ण */

	tcon = tlink_tcon(cअगरsFile->tlink);
	rc = find_cअगरs_entry(xid, tcon, ctx->pos, file, full_path,
			     &current_entry, &num_to_fill);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "fce error %d\n", rc);
		जाओ rddir2_निकास;
	पूर्ण अन्यथा अगर (current_entry != शून्य) अणु
		cअगरs_dbg(FYI, "entry %lld found\n", ctx->pos);
	पूर्ण अन्यथा अणु
		cअगरs_dbg(FYI, "Could not find entry\n");
		जाओ rddir2_निकास;
	पूर्ण
	cअगरs_dbg(FYI, "loop through %d times filling dir for net buf %p\n",
		 num_to_fill, cअगरsFile->srch_inf.ntwrk_buf_start);
	max_len = tcon->ses->server->ops->calc_smb_size(
			cअगरsFile->srch_inf.ntwrk_buf_start,
			tcon->ses->server);
	end_of_smb = cअगरsFile->srch_inf.ntwrk_buf_start + max_len;

	पंचांगp_buf = kदो_स्मृति(UNICODE_NAME_MAX, GFP_KERNEL);
	अगर (पंचांगp_buf == शून्य) अणु
		rc = -ENOMEM;
		जाओ rddir2_निकास;
	पूर्ण

	क्रम (i = 0; i < num_to_fill; i++) अणु
		अगर (current_entry == शून्य) अणु
			/* evaluate whether this हाल is an error */
			cअगरs_dbg(VFS, "past SMB end,  num to fill %d i %d\n",
				 num_to_fill, i);
			अवरोध;
		पूर्ण
		/*
		 * अगर buggy server वापसs . and .. late करो we want to
		 * check क्रम that here?
		 */
		*पंचांगp_buf = 0;
		rc = cअगरs_filldir(current_entry, file, ctx,
				  पंचांगp_buf, max_len);
		अगर (rc) अणु
			अगर (rc > 0)
				rc = 0;
			अवरोध;
		पूर्ण

		ctx->pos++;
		अगर (ctx->pos ==
			cअगरsFile->srch_inf.index_of_last_entry) अणु
			cअगरs_dbg(FYI, "last entry in buf at pos %lld %s\n",
				 ctx->pos, पंचांगp_buf);
			cअगरs_save_resume_key(current_entry, cअगरsFile);
			अवरोध;
		पूर्ण अन्यथा
			current_entry =
				nxt_dir_entry(current_entry, end_of_smb,
					cअगरsFile->srch_inf.info_level);
	पूर्ण
	kमुक्त(पंचांगp_buf);

rddir2_निकास:
	मुक्त_dentry_path(page);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण
