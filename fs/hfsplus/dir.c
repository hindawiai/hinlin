<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfsplus/dir.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Handling of directories
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/nls.h>

#समावेश "hfsplus_fs.h"
#समावेश "hfsplus_raw.h"
#समावेश "xattr.h"

अटल अंतरभूत व्योम hfsplus_instantiate(काष्ठा dentry *dentry,
				       काष्ठा inode *inode, u32 cnid)
अणु
	dentry->d_fsdata = (व्योम *)(अचिन्हित दीर्घ)cnid;
	d_instantiate(dentry, inode);
पूर्ण

/* Find the entry inside dir named dentry->d_name */
अटल काष्ठा dentry *hfsplus_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा hfs_find_data fd;
	काष्ठा super_block *sb;
	hfsplus_cat_entry entry;
	पूर्णांक err;
	u32 cnid, linkid = 0;
	u16 type;

	sb = dir->i_sb;

	dentry->d_fsdata = शून्य;
	err = hfs_find_init(HFSPLUS_SB(sb)->cat_tree, &fd);
	अगर (err)
		वापस ERR_PTR(err);
	err = hfsplus_cat_build_key(sb, fd.search_key, dir->i_ino,
			&dentry->d_name);
	अगर (unlikely(err < 0))
		जाओ fail;
again:
	err = hfs_brec_पढ़ो(&fd, &entry, माप(entry));
	अगर (err) अणु
		अगर (err == -ENOENT) अणु
			hfs_find_निकास(&fd);
			/* No such entry */
			inode = शून्य;
			जाओ out;
		पूर्ण
		जाओ fail;
	पूर्ण
	type = be16_to_cpu(entry.type);
	अगर (type == HFSPLUS_FOLDER) अणु
		अगर (fd.entrylength < माप(काष्ठा hfsplus_cat_folder)) अणु
			err = -EIO;
			जाओ fail;
		पूर्ण
		cnid = be32_to_cpu(entry.folder.id);
		dentry->d_fsdata = (व्योम *)(अचिन्हित दीर्घ)cnid;
	पूर्ण अन्यथा अगर (type == HFSPLUS_खाता) अणु
		अगर (fd.entrylength < माप(काष्ठा hfsplus_cat_file)) अणु
			err = -EIO;
			जाओ fail;
		पूर्ण
		cnid = be32_to_cpu(entry.file.id);
		अगर (entry.file.user_info.fdType ==
				cpu_to_be32(HFSP_HARDLINK_TYPE) &&
				entry.file.user_info.fdCreator ==
				cpu_to_be32(HFSP_HFSPLUS_CREATOR) &&
				HFSPLUS_SB(sb)->hidden_dir &&
				(entry.file.create_date ==
					HFSPLUS_I(HFSPLUS_SB(sb)->hidden_dir)->
						create_date ||
				entry.file.create_date ==
					HFSPLUS_I(d_inode(sb->s_root))->
						create_date)) अणु
			काष्ठा qstr str;
			अक्षर name[32];

			अगर (dentry->d_fsdata) अणु
				/*
				 * We found a link poपूर्णांकing to another link,
				 * so ignore it and treat it as regular file.
				 */
				cnid = (अचिन्हित दीर्घ)dentry->d_fsdata;
				linkid = 0;
			पूर्ण अन्यथा अणु
				dentry->d_fsdata = (व्योम *)(अचिन्हित दीर्घ)cnid;
				linkid =
					be32_to_cpu(entry.file.permissions.dev);
				str.len = प्र_लिखो(name, "iNode%d", linkid);
				str.name = name;
				err = hfsplus_cat_build_key(sb, fd.search_key,
					HFSPLUS_SB(sb)->hidden_dir->i_ino,
					&str);
				अगर (unlikely(err < 0))
					जाओ fail;
				जाओ again;
			पूर्ण
		पूर्ण अन्यथा अगर (!dentry->d_fsdata)
			dentry->d_fsdata = (व्योम *)(अचिन्हित दीर्घ)cnid;
	पूर्ण अन्यथा अणु
		pr_err("invalid catalog entry type in lookup\n");
		err = -EIO;
		जाओ fail;
	पूर्ण
	hfs_find_निकास(&fd);
	inode = hfsplus_iget(dir->i_sb, cnid);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	अगर (S_ISREG(inode->i_mode))
		HFSPLUS_I(inode)->linkid = linkid;
out:
	वापस d_splice_alias(inode, dentry);
fail:
	hfs_find_निकास(&fd);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक hfsplus_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक len, err;
	अक्षर *strbuf;
	hfsplus_cat_entry entry;
	काष्ठा hfs_find_data fd;
	काष्ठा hfsplus_सूची_पढ़ो_data *rd;
	u16 type;

	अगर (file->f_pos >= inode->i_size)
		वापस 0;

	err = hfs_find_init(HFSPLUS_SB(sb)->cat_tree, &fd);
	अगर (err)
		वापस err;
	strbuf = kदो_स्मृति(NLS_MAX_CHARSET_SIZE * HFSPLUS_MAX_STRLEN + 1, GFP_KERNEL);
	अगर (!strbuf) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	hfsplus_cat_build_key_with_cnid(sb, fd.search_key, inode->i_ino);
	err = hfs_brec_find(&fd, hfs_find_rec_by_key);
	अगर (err)
		जाओ out;

	अगर (ctx->pos == 0) अणु
		/* This is completely artअगरicial... */
		अगर (!dir_emit_करोt(file, ctx))
			जाओ out;
		ctx->pos = 1;
	पूर्ण
	अगर (ctx->pos == 1) अणु
		अगर (fd.entrylength > माप(entry) || fd.entrylength < 0) अणु
			err = -EIO;
			जाओ out;
		पूर्ण

		hfs_bnode_पढ़ो(fd.bnode, &entry, fd.entryoffset,
			fd.entrylength);
		अगर (be16_to_cpu(entry.type) != HFSPLUS_FOLDER_THREAD) अणु
			pr_err("bad catalog folder thread\n");
			err = -EIO;
			जाओ out;
		पूर्ण
		अगर (fd.entrylength < HFSPLUS_MIN_THREAD_SZ) अणु
			pr_err("truncated catalog thread\n");
			err = -EIO;
			जाओ out;
		पूर्ण
		अगर (!dir_emit(ctx, "..", 2,
			    be32_to_cpu(entry.thपढ़ो.parentID), DT_सूची))
			जाओ out;
		ctx->pos = 2;
	पूर्ण
	अगर (ctx->pos >= inode->i_size)
		जाओ out;
	err = hfs_brec_जाओ(&fd, ctx->pos - 1);
	अगर (err)
		जाओ out;
	क्रम (;;) अणु
		अगर (be32_to_cpu(fd.key->cat.parent) != inode->i_ino) अणु
			pr_err("walked past end of dir\n");
			err = -EIO;
			जाओ out;
		पूर्ण

		अगर (fd.entrylength > माप(entry) || fd.entrylength < 0) अणु
			err = -EIO;
			जाओ out;
		पूर्ण

		hfs_bnode_पढ़ो(fd.bnode, &entry, fd.entryoffset,
			fd.entrylength);
		type = be16_to_cpu(entry.type);
		len = NLS_MAX_CHARSET_SIZE * HFSPLUS_MAX_STRLEN;
		err = hfsplus_uni2asc(sb, &fd.key->cat.name, strbuf, &len);
		अगर (err)
			जाओ out;
		अगर (type == HFSPLUS_FOLDER) अणु
			अगर (fd.entrylength <
					माप(काष्ठा hfsplus_cat_folder)) अणु
				pr_err("small dir entry\n");
				err = -EIO;
				जाओ out;
			पूर्ण
			अगर (HFSPLUS_SB(sb)->hidden_dir &&
			    HFSPLUS_SB(sb)->hidden_dir->i_ino ==
					be32_to_cpu(entry.folder.id))
				जाओ next;
			अगर (!dir_emit(ctx, strbuf, len,
				    be32_to_cpu(entry.folder.id), DT_सूची))
				अवरोध;
		पूर्ण अन्यथा अगर (type == HFSPLUS_खाता) अणु
			u16 mode;
			अचिन्हित type = DT_UNKNOWN;

			अगर (fd.entrylength < माप(काष्ठा hfsplus_cat_file)) अणु
				pr_err("small file entry\n");
				err = -EIO;
				जाओ out;
			पूर्ण

			mode = be16_to_cpu(entry.file.permissions.mode);
			अगर (S_ISREG(mode))
				type = DT_REG;
			अन्यथा अगर (S_ISLNK(mode))
				type = DT_LNK;
			अन्यथा अगर (S_ISFIFO(mode))
				type = DT_FIFO;
			अन्यथा अगर (S_ISCHR(mode))
				type = DT_CHR;
			अन्यथा अगर (S_ISBLK(mode))
				type = DT_BLK;
			अन्यथा अगर (S_ISSOCK(mode))
				type = DT_SOCK;

			अगर (!dir_emit(ctx, strbuf, len,
				      be32_to_cpu(entry.file.id), type))
				अवरोध;
		पूर्ण अन्यथा अणु
			pr_err("bad catalog entry type\n");
			err = -EIO;
			जाओ out;
		पूर्ण
next:
		ctx->pos++;
		अगर (ctx->pos >= inode->i_size)
			जाओ out;
		err = hfs_brec_जाओ(&fd, 1);
		अगर (err)
			जाओ out;
	पूर्ण
	rd = file->निजी_data;
	अगर (!rd) अणु
		rd = kदो_स्मृति(माप(काष्ठा hfsplus_सूची_पढ़ो_data), GFP_KERNEL);
		अगर (!rd) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		file->निजी_data = rd;
		rd->file = file;
		spin_lock(&HFSPLUS_I(inode)->खोलो_dir_lock);
		list_add(&rd->list, &HFSPLUS_I(inode)->खोलो_dir_list);
		spin_unlock(&HFSPLUS_I(inode)->खोलो_dir_lock);
	पूर्ण
	/*
	 * Can be करोne after the list insertion; exclusion with
	 * hfsplus_delete_cat() is provided by directory lock.
	 */
	स_नकल(&rd->key, fd.key, माप(काष्ठा hfsplus_cat_key));
out:
	kमुक्त(strbuf);
	hfs_find_निकास(&fd);
	वापस err;
पूर्ण

अटल पूर्णांक hfsplus_dir_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hfsplus_सूची_पढ़ो_data *rd = file->निजी_data;
	अगर (rd) अणु
		spin_lock(&HFSPLUS_I(inode)->खोलो_dir_lock);
		list_del(&rd->list);
		spin_unlock(&HFSPLUS_I(inode)->खोलो_dir_lock);
		kमुक्त(rd);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hfsplus_link(काष्ठा dentry *src_dentry, काष्ठा inode *dst_dir,
			काष्ठा dentry *dst_dentry)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(dst_dir->i_sb);
	काष्ठा inode *inode = d_inode(src_dentry);
	काष्ठा inode *src_dir = d_inode(src_dentry->d_parent);
	काष्ठा qstr str;
	अक्षर name[32];
	u32 cnid, id;
	पूर्णांक res;

	अगर (HFSPLUS_IS_RSRC(inode))
		वापस -EPERM;
	अगर (!S_ISREG(inode->i_mode))
		वापस -EPERM;

	mutex_lock(&sbi->vh_mutex);
	अगर (inode->i_ino == (u32)(अचिन्हित दीर्घ)src_dentry->d_fsdata) अणु
		क्रम (;;) अणु
			get_अक्रमom_bytes(&id, माप(cnid));
			id &= 0x3fffffff;
			str.name = name;
			str.len = प्र_लिखो(name, "iNode%d", id);
			res = hfsplus_नाम_cat(inode->i_ino,
						 src_dir, &src_dentry->d_name,
						 sbi->hidden_dir, &str);
			अगर (!res)
				अवरोध;
			अगर (res != -EEXIST)
				जाओ out;
		पूर्ण
		HFSPLUS_I(inode)->linkid = id;
		cnid = sbi->next_cnid++;
		src_dentry->d_fsdata = (व्योम *)(अचिन्हित दीर्घ)cnid;
		res = hfsplus_create_cat(cnid, src_dir,
			&src_dentry->d_name, inode);
		अगर (res)
			/* panic? */
			जाओ out;
		sbi->file_count++;
	पूर्ण
	cnid = sbi->next_cnid++;
	res = hfsplus_create_cat(cnid, dst_dir, &dst_dentry->d_name, inode);
	अगर (res)
		जाओ out;

	inc_nlink(inode);
	hfsplus_instantiate(dst_dentry, inode, cnid);
	ihold(inode);
	inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
	sbi->file_count++;
	hfsplus_mark_mdb_dirty(dst_dir->i_sb);
out:
	mutex_unlock(&sbi->vh_mutex);
	वापस res;
पूर्ण

अटल पूर्णांक hfsplus_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(dir->i_sb);
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा qstr str;
	अक्षर name[32];
	u32 cnid;
	पूर्णांक res;

	अगर (HFSPLUS_IS_RSRC(inode))
		वापस -EPERM;

	mutex_lock(&sbi->vh_mutex);
	cnid = (u32)(अचिन्हित दीर्घ)dentry->d_fsdata;
	अगर (inode->i_ino == cnid &&
	    atomic_पढ़ो(&HFSPLUS_I(inode)->खोलोcnt)) अणु
		str.name = name;
		str.len = प्र_लिखो(name, "temp%lu", inode->i_ino);
		res = hfsplus_नाम_cat(inode->i_ino,
					 dir, &dentry->d_name,
					 sbi->hidden_dir, &str);
		अगर (!res) अणु
			inode->i_flags |= S_DEAD;
			drop_nlink(inode);
		पूर्ण
		जाओ out;
	पूर्ण
	res = hfsplus_delete_cat(cnid, dir, &dentry->d_name);
	अगर (res)
		जाओ out;

	अगर (inode->i_nlink > 0)
		drop_nlink(inode);
	अगर (inode->i_ino == cnid)
		clear_nlink(inode);
	अगर (!inode->i_nlink) अणु
		अगर (inode->i_ino != cnid) अणु
			sbi->file_count--;
			अगर (!atomic_पढ़ो(&HFSPLUS_I(inode)->खोलोcnt)) अणु
				res = hfsplus_delete_cat(inode->i_ino,
							 sbi->hidden_dir,
							 शून्य);
				अगर (!res)
					hfsplus_delete_inode(inode);
			पूर्ण अन्यथा
				inode->i_flags |= S_DEAD;
		पूर्ण अन्यथा
			hfsplus_delete_inode(inode);
	पूर्ण अन्यथा
		sbi->file_count--;
	inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
out:
	mutex_unlock(&sbi->vh_mutex);
	वापस res;
पूर्ण

अटल पूर्णांक hfsplus_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(dir->i_sb);
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक res;

	अगर (inode->i_size != 2)
		वापस -ENOTEMPTY;

	mutex_lock(&sbi->vh_mutex);
	res = hfsplus_delete_cat(inode->i_ino, dir, &dentry->d_name);
	अगर (res)
		जाओ out;
	clear_nlink(inode);
	inode->i_स_समय = current_समय(inode);
	hfsplus_delete_inode(inode);
	mark_inode_dirty(inode);
out:
	mutex_unlock(&sbi->vh_mutex);
	वापस res;
पूर्ण

अटल पूर्णांक hfsplus_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			   काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(dir->i_sb);
	काष्ठा inode *inode;
	पूर्णांक res = -ENOMEM;

	mutex_lock(&sbi->vh_mutex);
	inode = hfsplus_new_inode(dir->i_sb, dir, S_IFLNK | S_IRWXUGO);
	अगर (!inode)
		जाओ out;

	res = page_symlink(inode, symname, म_माप(symname) + 1);
	अगर (res)
		जाओ out_err;

	res = hfsplus_create_cat(inode->i_ino, dir, &dentry->d_name, inode);
	अगर (res)
		जाओ out_err;

	res = hfsplus_init_security(inode, dir, &dentry->d_name);
	अगर (res == -EOPNOTSUPP)
		res = 0; /* Operation is not supported. */
	अन्यथा अगर (res) अणु
		/* Try to delete anyway without error analysis. */
		hfsplus_delete_cat(inode->i_ino, dir, &dentry->d_name);
		जाओ out_err;
	पूर्ण

	hfsplus_instantiate(dentry, inode, inode->i_ino);
	mark_inode_dirty(inode);
	जाओ out;

out_err:
	clear_nlink(inode);
	hfsplus_delete_inode(inode);
	iput(inode);
out:
	mutex_unlock(&sbi->vh_mutex);
	वापस res;
पूर्ण

अटल पूर्णांक hfsplus_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			 काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(dir->i_sb);
	काष्ठा inode *inode;
	पूर्णांक res = -ENOMEM;

	mutex_lock(&sbi->vh_mutex);
	inode = hfsplus_new_inode(dir->i_sb, dir, mode);
	अगर (!inode)
		जाओ out;

	अगर (S_ISBLK(mode) || S_ISCHR(mode) || S_ISFIFO(mode) || S_ISSOCK(mode))
		init_special_inode(inode, mode, rdev);

	res = hfsplus_create_cat(inode->i_ino, dir, &dentry->d_name, inode);
	अगर (res)
		जाओ failed_mknod;

	res = hfsplus_init_security(inode, dir, &dentry->d_name);
	अगर (res == -EOPNOTSUPP)
		res = 0; /* Operation is not supported. */
	अन्यथा अगर (res) अणु
		/* Try to delete anyway without error analysis. */
		hfsplus_delete_cat(inode->i_ino, dir, &dentry->d_name);
		जाओ failed_mknod;
	पूर्ण

	hfsplus_instantiate(dentry, inode, inode->i_ino);
	mark_inode_dirty(inode);
	जाओ out;

failed_mknod:
	clear_nlink(inode);
	hfsplus_delete_inode(inode);
	iput(inode);
out:
	mutex_unlock(&sbi->vh_mutex);
	वापस res;
पूर्ण

अटल पूर्णांक hfsplus_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			  काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	वापस hfsplus_mknod(&init_user_ns, dir, dentry, mode, 0);
पूर्ण

अटल पूर्णांक hfsplus_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			 काष्ठा dentry *dentry, umode_t mode)
अणु
	वापस hfsplus_mknod(&init_user_ns, dir, dentry, mode | S_IFसूची, 0);
पूर्ण

अटल पूर्णांक hfsplus_नाम(काष्ठा user_namespace *mnt_userns,
			  काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			  काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			  अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक res;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	/* Unlink destination अगर it alपढ़ोy exists */
	अगर (d_really_is_positive(new_dentry)) अणु
		अगर (d_is_dir(new_dentry))
			res = hfsplus_सूची_हटाओ(new_dir, new_dentry);
		अन्यथा
			res = hfsplus_unlink(new_dir, new_dentry);
		अगर (res)
			वापस res;
	पूर्ण

	res = hfsplus_नाम_cat((u32)(अचिन्हित दीर्घ)old_dentry->d_fsdata,
				 old_dir, &old_dentry->d_name,
				 new_dir, &new_dentry->d_name);
	अगर (!res)
		new_dentry->d_fsdata = old_dentry->d_fsdata;
	वापस res;
पूर्ण

स्थिर काष्ठा inode_operations hfsplus_dir_inode_operations = अणु
	.lookup			= hfsplus_lookup,
	.create			= hfsplus_create,
	.link			= hfsplus_link,
	.unlink			= hfsplus_unlink,
	.सूची_गढ़ो			= hfsplus_सूची_गढ़ो,
	.सूची_हटाओ			= hfsplus_सूची_हटाओ,
	.symlink		= hfsplus_symlink,
	.mknod			= hfsplus_mknod,
	.नाम			= hfsplus_नाम,
	.getattr		= hfsplus_getattr,
	.listxattr		= hfsplus_listxattr,
	.fileattr_get		= hfsplus_fileattr_get,
	.fileattr_set		= hfsplus_fileattr_set,
पूर्ण;

स्थिर काष्ठा file_operations hfsplus_dir_operations = अणु
	.fsync		= hfsplus_file_fsync,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= hfsplus_सूची_पढ़ो,
	.unlocked_ioctl = hfsplus_ioctl,
	.llseek		= generic_file_llseek,
	.release	= hfsplus_dir_release,
पूर्ण;
