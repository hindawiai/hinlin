<शैली गुरु>
/*
 *  linux/fs/hfs/dir.c
 *
 * Copyright (C) 1995-1997  Paul H. Hargrove
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 * This file may be distributed under the terms of the GNU General Public License.
 *
 * This file contains directory-related functions independent of which
 * scheme is being used to represent विभाजनs.
 *
 * Based on the minix file प्रणाली code, (C) 1991, 1992 by Linus Torvalds
 */

#समावेश "hfs_fs.h"
#समावेश "btree.h"

/*
 * hfs_lookup()
 */
अटल काष्ठा dentry *hfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				 अचिन्हित पूर्णांक flags)
अणु
	hfs_cat_rec rec;
	काष्ठा hfs_find_data fd;
	काष्ठा inode *inode = शून्य;
	पूर्णांक res;

	res = hfs_find_init(HFS_SB(dir->i_sb)->cat_tree, &fd);
	अगर (res)
		वापस ERR_PTR(res);
	hfs_cat_build_key(dir->i_sb, fd.search_key, dir->i_ino, &dentry->d_name);
	res = hfs_brec_पढ़ो(&fd, &rec, माप(rec));
	अगर (res) अणु
		अगर (res != -ENOENT)
			inode = ERR_PTR(res);
	पूर्ण अन्यथा अणु
		inode = hfs_iget(dir->i_sb, &fd.search_key->cat, &rec);
		अगर (!inode)
			inode = ERR_PTR(-EACCES);
	पूर्ण
	hfs_find_निकास(&fd);
	वापस d_splice_alias(inode, dentry);
पूर्ण

/*
 * hfs_सूची_पढ़ो
 */
अटल पूर्णांक hfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक len, err;
	अक्षर strbuf[HFS_MAX_NAMELEN];
	जोड़ hfs_cat_rec entry;
	काष्ठा hfs_find_data fd;
	काष्ठा hfs_सूची_पढ़ो_data *rd;
	u16 type;

	अगर (ctx->pos >= inode->i_size)
		वापस 0;

	err = hfs_find_init(HFS_SB(sb)->cat_tree, &fd);
	अगर (err)
		वापस err;
	hfs_cat_build_key(sb, fd.search_key, inode->i_ino, शून्य);
	err = hfs_brec_find(&fd);
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

		hfs_bnode_पढ़ो(fd.bnode, &entry, fd.entryoffset, fd.entrylength);
		अगर (entry.type != HFS_CDR_THD) अणु
			pr_err("bad catalog folder thread\n");
			err = -EIO;
			जाओ out;
		पूर्ण
		//अगर (fd.entrylength < HFS_MIN_THREAD_SZ) अणु
		//	pr_err("truncated catalog thread\n");
		//	err = -EIO;
		//	जाओ out;
		//पूर्ण
		अगर (!dir_emit(ctx, "..", 2,
			    be32_to_cpu(entry.thपढ़ो.ParID), DT_सूची))
			जाओ out;
		ctx->pos = 2;
	पूर्ण
	अगर (ctx->pos >= inode->i_size)
		जाओ out;
	err = hfs_brec_जाओ(&fd, ctx->pos - 1);
	अगर (err)
		जाओ out;

	क्रम (;;) अणु
		अगर (be32_to_cpu(fd.key->cat.ParID) != inode->i_ino) अणु
			pr_err("walked past end of dir\n");
			err = -EIO;
			जाओ out;
		पूर्ण

		अगर (fd.entrylength > माप(entry) || fd.entrylength < 0) अणु
			err = -EIO;
			जाओ out;
		पूर्ण

		hfs_bnode_पढ़ो(fd.bnode, &entry, fd.entryoffset, fd.entrylength);
		type = entry.type;
		len = hfs_mac2asc(sb, strbuf, &fd.key->cat.CName);
		अगर (type == HFS_CDR_सूची) अणु
			अगर (fd.entrylength < माप(काष्ठा hfs_cat_dir)) अणु
				pr_err("small dir entry\n");
				err = -EIO;
				जाओ out;
			पूर्ण
			अगर (!dir_emit(ctx, strbuf, len,
				    be32_to_cpu(entry.dir.DirID), DT_सूची))
				अवरोध;
		पूर्ण अन्यथा अगर (type == HFS_CDR_FIL) अणु
			अगर (fd.entrylength < माप(काष्ठा hfs_cat_file)) अणु
				pr_err("small file entry\n");
				err = -EIO;
				जाओ out;
			पूर्ण
			अगर (!dir_emit(ctx, strbuf, len,
				    be32_to_cpu(entry.file.FlNum), DT_REG))
				अवरोध;
		पूर्ण अन्यथा अणु
			pr_err("bad catalog entry type %d\n", type);
			err = -EIO;
			जाओ out;
		पूर्ण
		ctx->pos++;
		अगर (ctx->pos >= inode->i_size)
			जाओ out;
		err = hfs_brec_जाओ(&fd, 1);
		अगर (err)
			जाओ out;
	पूर्ण
	rd = file->निजी_data;
	अगर (!rd) अणु
		rd = kदो_स्मृति(माप(काष्ठा hfs_सूची_पढ़ो_data), GFP_KERNEL);
		अगर (!rd) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		file->निजी_data = rd;
		rd->file = file;
		spin_lock(&HFS_I(inode)->खोलो_dir_lock);
		list_add(&rd->list, &HFS_I(inode)->खोलो_dir_list);
		spin_unlock(&HFS_I(inode)->खोलो_dir_lock);
	पूर्ण
	/*
	 * Can be करोne after the list insertion; exclusion with
	 * hfs_delete_cat() is provided by directory lock.
	 */
	स_नकल(&rd->key, &fd.key->cat, माप(काष्ठा hfs_cat_key));
out:
	hfs_find_निकास(&fd);
	वापस err;
पूर्ण

अटल पूर्णांक hfs_dir_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hfs_सूची_पढ़ो_data *rd = file->निजी_data;
	अगर (rd) अणु
		spin_lock(&HFS_I(inode)->खोलो_dir_lock);
		list_del(&rd->list);
		spin_unlock(&HFS_I(inode)->खोलो_dir_lock);
		kमुक्त(rd);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * hfs_create()
 *
 * This is the create() entry in the inode_operations काष्ठाure क्रम
 * regular HFS directories.  The purpose is to create a new file in
 * a directory and वापस a corresponding inode, given the inode क्रम
 * the directory and the name (and its length) of the new file.
 */
अटल पूर्णांक hfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा inode *inode;
	पूर्णांक res;

	inode = hfs_new_inode(dir, &dentry->d_name, mode);
	अगर (!inode)
		वापस -ENOMEM;

	res = hfs_cat_create(inode->i_ino, dir, &dentry->d_name, inode);
	अगर (res) अणु
		clear_nlink(inode);
		hfs_delete_inode(inode);
		iput(inode);
		वापस res;
	पूर्ण
	d_instantiate(dentry, inode);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

/*
 * hfs_सूची_गढ़ो()
 *
 * This is the सूची_गढ़ो() entry in the inode_operations काष्ठाure क्रम
 * regular HFS directories.  The purpose is to create a new directory
 * in a directory, given the inode क्रम the parent directory and the
 * name (and its length) of the new directory.
 */
अटल पूर्णांक hfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा inode *inode;
	पूर्णांक res;

	inode = hfs_new_inode(dir, &dentry->d_name, S_IFसूची | mode);
	अगर (!inode)
		वापस -ENOMEM;

	res = hfs_cat_create(inode->i_ino, dir, &dentry->d_name, inode);
	अगर (res) अणु
		clear_nlink(inode);
		hfs_delete_inode(inode);
		iput(inode);
		वापस res;
	पूर्ण
	d_instantiate(dentry, inode);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

/*
 * hfs_हटाओ()
 *
 * This serves as both unlink() and सूची_हटाओ() in the inode_operations
 * काष्ठाure क्रम regular HFS directories.  The purpose is to delete
 * an existing child, given the inode क्रम the parent directory and
 * the name (and its length) of the existing directory.
 *
 * HFS करोes not have hardlinks, so both सूची_हटाओ and unlink set the
 * link count to 0.  The only dअगरference is the emptiness check.
 */
अटल पूर्णांक hfs_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक res;

	अगर (S_ISसूची(inode->i_mode) && inode->i_size != 2)
		वापस -ENOTEMPTY;
	res = hfs_cat_delete(inode->i_ino, dir, &dentry->d_name);
	अगर (res)
		वापस res;
	clear_nlink(inode);
	inode->i_स_समय = current_समय(inode);
	hfs_delete_inode(inode);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

/*
 * hfs_नाम()
 *
 * This is the नाम() entry in the inode_operations काष्ठाure क्रम
 * regular HFS directories.  The purpose is to नाम an existing
 * file or directory, given the inode क्रम the current directory and
 * the name (and its length) of the existing file/directory and the
 * inode क्रम the new directory and the name (and its length) of the
 * new file/directory.
 * XXX: how करो you handle must_be dir?
 */
अटल पूर्णांक hfs_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		      काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		      काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक res;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	/* Unlink destination अगर it alपढ़ोy exists */
	अगर (d_really_is_positive(new_dentry)) अणु
		res = hfs_हटाओ(new_dir, new_dentry);
		अगर (res)
			वापस res;
	पूर्ण

	res = hfs_cat_move(d_inode(old_dentry)->i_ino,
			   old_dir, &old_dentry->d_name,
			   new_dir, &new_dentry->d_name);
	अगर (!res)
		hfs_cat_build_key(old_dir->i_sb,
				  (btree_key *)&HFS_I(d_inode(old_dentry))->cat_key,
				  new_dir->i_ino, &new_dentry->d_name);
	वापस res;
पूर्ण

स्थिर काष्ठा file_operations hfs_dir_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= hfs_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
	.release	= hfs_dir_release,
पूर्ण;

स्थिर काष्ठा inode_operations hfs_dir_inode_operations = अणु
	.create		= hfs_create,
	.lookup		= hfs_lookup,
	.unlink		= hfs_हटाओ,
	.सूची_गढ़ो		= hfs_सूची_गढ़ो,
	.सूची_हटाओ		= hfs_हटाओ,
	.नाम		= hfs_नाम,
	.setattr	= hfs_inode_setattr,
पूर्ण;
