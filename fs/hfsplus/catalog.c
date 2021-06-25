<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfsplus/catalog.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Handling of catalog records
 */


#समावेश "hfsplus_fs.h"
#समावेश "hfsplus_raw.h"

पूर्णांक hfsplus_cat_हाल_cmp_key(स्थिर hfsplus_btree_key *k1,
			     स्थिर hfsplus_btree_key *k2)
अणु
	__be32 k1p, k2p;

	k1p = k1->cat.parent;
	k2p = k2->cat.parent;
	अगर (k1p != k2p)
		वापस be32_to_cpu(k1p) < be32_to_cpu(k2p) ? -1 : 1;

	वापस hfsplus_strहालcmp(&k1->cat.name, &k2->cat.name);
पूर्ण

पूर्णांक hfsplus_cat_bin_cmp_key(स्थिर hfsplus_btree_key *k1,
			    स्थिर hfsplus_btree_key *k2)
अणु
	__be32 k1p, k2p;

	k1p = k1->cat.parent;
	k2p = k2->cat.parent;
	अगर (k1p != k2p)
		वापस be32_to_cpu(k1p) < be32_to_cpu(k2p) ? -1 : 1;

	वापस hfsplus_म_भेद(&k1->cat.name, &k2->cat.name);
पूर्ण

/* Generates key क्रम catalog file/folders record. */
पूर्णांक hfsplus_cat_build_key(काष्ठा super_block *sb,
		hfsplus_btree_key *key, u32 parent, स्थिर काष्ठा qstr *str)
अणु
	पूर्णांक len, err;

	key->cat.parent = cpu_to_be32(parent);
	err = hfsplus_asc2uni(sb, &key->cat.name, HFSPLUS_MAX_STRLEN,
			str->name, str->len);
	अगर (unlikely(err < 0))
		वापस err;

	len = be16_to_cpu(key->cat.name.length);
	key->key_len = cpu_to_be16(6 + 2 * len);
	वापस 0;
पूर्ण

/* Generates key क्रम catalog thपढ़ो record. */
व्योम hfsplus_cat_build_key_with_cnid(काष्ठा super_block *sb,
			hfsplus_btree_key *key, u32 parent)
अणु
	key->cat.parent = cpu_to_be32(parent);
	key->cat.name.length = 0;
	key->key_len = cpu_to_be16(6);
पूर्ण

अटल व्योम hfsplus_cat_build_key_uni(hfsplus_btree_key *key, u32 parent,
				      काष्ठा hfsplus_unistr *name)
अणु
	पूर्णांक uम_माप;

	uम_माप = be16_to_cpu(name->length);
	key->cat.parent = cpu_to_be32(parent);
	key->cat.name.length = cpu_to_be16(uम_माप);
	uम_माप *= 2;
	स_नकल(key->cat.name.unicode, name->unicode, uम_माप);
	key->key_len = cpu_to_be16(6 + uम_माप);
पूर्ण

व्योम hfsplus_cat_set_perms(काष्ठा inode *inode, काष्ठा hfsplus_perm *perms)
अणु
	अगर (inode->i_flags & S_IMMUTABLE)
		perms->rootflags |= HFSPLUS_FLG_IMMUTABLE;
	अन्यथा
		perms->rootflags &= ~HFSPLUS_FLG_IMMUTABLE;
	अगर (inode->i_flags & S_APPEND)
		perms->rootflags |= HFSPLUS_FLG_APPEND;
	अन्यथा
		perms->rootflags &= ~HFSPLUS_FLG_APPEND;

	perms->userflags = HFSPLUS_I(inode)->userflags;
	perms->mode = cpu_to_be16(inode->i_mode);
	perms->owner = cpu_to_be32(i_uid_पढ़ो(inode));
	perms->group = cpu_to_be32(i_gid_पढ़ो(inode));

	अगर (S_ISREG(inode->i_mode))
		perms->dev = cpu_to_be32(inode->i_nlink);
	अन्यथा अगर (S_ISBLK(inode->i_mode) || S_ISCHR(inode->i_mode))
		perms->dev = cpu_to_be32(inode->i_rdev);
	अन्यथा
		perms->dev = 0;
पूर्ण

अटल पूर्णांक hfsplus_cat_build_record(hfsplus_cat_entry *entry,
		u32 cnid, काष्ठा inode *inode)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(inode->i_sb);

	अगर (S_ISसूची(inode->i_mode)) अणु
		काष्ठा hfsplus_cat_folder *folder;

		folder = &entry->folder;
		स_रखो(folder, 0, माप(*folder));
		folder->type = cpu_to_be16(HFSPLUS_FOLDER);
		अगर (test_bit(HFSPLUS_SB_HFSX, &sbi->flags))
			folder->flags |= cpu_to_be16(HFSPLUS_HAS_FOLDER_COUNT);
		folder->id = cpu_to_be32(inode->i_ino);
		HFSPLUS_I(inode)->create_date =
			folder->create_date =
			folder->content_mod_date =
			folder->attribute_mod_date =
			folder->access_date = hfsp_now2mt();
		hfsplus_cat_set_perms(inode, &folder->permissions);
		अगर (inode == sbi->hidden_dir)
			/* invisible and namelocked */
			folder->user_info.frFlags = cpu_to_be16(0x5000);
		वापस माप(*folder);
	पूर्ण अन्यथा अणु
		काष्ठा hfsplus_cat_file *file;

		file = &entry->file;
		स_रखो(file, 0, माप(*file));
		file->type = cpu_to_be16(HFSPLUS_खाता);
		file->flags = cpu_to_be16(HFSPLUS_खाता_THREAD_EXISTS);
		file->id = cpu_to_be32(cnid);
		HFSPLUS_I(inode)->create_date =
			file->create_date =
			file->content_mod_date =
			file->attribute_mod_date =
			file->access_date = hfsp_now2mt();
		अगर (cnid == inode->i_ino) अणु
			hfsplus_cat_set_perms(inode, &file->permissions);
			अगर (S_ISLNK(inode->i_mode)) अणु
				file->user_info.fdType =
					cpu_to_be32(HFSP_SYMLINK_TYPE);
				file->user_info.fdCreator =
					cpu_to_be32(HFSP_SYMLINK_CREATOR);
			पूर्ण अन्यथा अणु
				file->user_info.fdType =
					cpu_to_be32(sbi->type);
				file->user_info.fdCreator =
					cpu_to_be32(sbi->creator);
			पूर्ण
			अगर (HFSPLUS_FLG_IMMUTABLE &
					(file->permissions.rootflags |
					file->permissions.userflags))
				file->flags |=
					cpu_to_be16(HFSPLUS_खाता_LOCKED);
		पूर्ण अन्यथा अणु
			file->user_info.fdType =
				cpu_to_be32(HFSP_HARDLINK_TYPE);
			file->user_info.fdCreator =
				cpu_to_be32(HFSP_HFSPLUS_CREATOR);
			file->user_info.fdFlags =
				cpu_to_be16(0x100);
			file->create_date =
				HFSPLUS_I(sbi->hidden_dir)->create_date;
			file->permissions.dev =
				cpu_to_be32(HFSPLUS_I(inode)->linkid);
		पूर्ण
		वापस माप(*file);
	पूर्ण
पूर्ण

अटल पूर्णांक hfsplus_fill_cat_thपढ़ो(काष्ठा super_block *sb,
				   hfsplus_cat_entry *entry, पूर्णांक type,
				   u32 parentid, स्थिर काष्ठा qstr *str)
अणु
	पूर्णांक err;

	entry->type = cpu_to_be16(type);
	entry->thपढ़ो.reserved = 0;
	entry->thपढ़ो.parentID = cpu_to_be32(parentid);
	err = hfsplus_asc2uni(sb, &entry->thपढ़ो.nodeName, HFSPLUS_MAX_STRLEN,
				str->name, str->len);
	अगर (unlikely(err < 0))
		वापस err;

	वापस 10 + be16_to_cpu(entry->thपढ़ो.nodeName.length) * 2;
पूर्ण

/* Try to get a catalog entry क्रम given catalog id */
पूर्णांक hfsplus_find_cat(काष्ठा super_block *sb, u32 cnid,
		     काष्ठा hfs_find_data *fd)
अणु
	hfsplus_cat_entry पंचांगp;
	पूर्णांक err;
	u16 type;

	hfsplus_cat_build_key_with_cnid(sb, fd->search_key, cnid);
	err = hfs_brec_पढ़ो(fd, &पंचांगp, माप(hfsplus_cat_entry));
	अगर (err)
		वापस err;

	type = be16_to_cpu(पंचांगp.type);
	अगर (type != HFSPLUS_FOLDER_THREAD && type != HFSPLUS_खाता_THREAD) अणु
		pr_err("found bad thread record in catalog\n");
		वापस -EIO;
	पूर्ण

	अगर (be16_to_cpu(पंचांगp.thपढ़ो.nodeName.length) > 255) अणु
		pr_err("catalog name length corrupted\n");
		वापस -EIO;
	पूर्ण

	hfsplus_cat_build_key_uni(fd->search_key,
		be32_to_cpu(पंचांगp.thपढ़ो.parentID),
		&पंचांगp.thपढ़ो.nodeName);
	वापस hfs_brec_find(fd, hfs_find_rec_by_key);
पूर्ण

अटल व्योम hfsplus_subfolders_inc(काष्ठा inode *dir)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(dir->i_sb);

	अगर (test_bit(HFSPLUS_SB_HFSX, &sbi->flags)) अणु
		/*
		 * Increment subfolder count. Note, the value is only meaningful
		 * क्रम folders with HFSPLUS_HAS_FOLDER_COUNT flag set.
		 */
		HFSPLUS_I(dir)->subfolders++;
	पूर्ण
पूर्ण

अटल व्योम hfsplus_subfolders_dec(काष्ठा inode *dir)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(dir->i_sb);

	अगर (test_bit(HFSPLUS_SB_HFSX, &sbi->flags)) अणु
		/*
		 * Decrement subfolder count. Note, the value is only meaningful
		 * क्रम folders with HFSPLUS_HAS_FOLDER_COUNT flag set.
		 *
		 * Check क्रम zero. Some subfolders may have been created
		 * by an implementation ignorant of this counter.
		 */
		अगर (HFSPLUS_I(dir)->subfolders)
			HFSPLUS_I(dir)->subfolders--;
	पूर्ण
पूर्ण

पूर्णांक hfsplus_create_cat(u32 cnid, काष्ठा inode *dir,
		स्थिर काष्ठा qstr *str, काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा hfs_find_data fd;
	hfsplus_cat_entry entry;
	पूर्णांक entry_size;
	पूर्णांक err;

	hfs_dbg(CAT_MOD, "create_cat: %s,%u(%d)\n",
		str->name, cnid, inode->i_nlink);
	err = hfs_find_init(HFSPLUS_SB(sb)->cat_tree, &fd);
	अगर (err)
		वापस err;

	/*
	 * Fail early and aव्योम ENOSPC during the btree operations. We may
	 * have to split the root node at most once.
	 */
	err = hfs_bmap_reserve(fd.tree, 2 * fd.tree->depth);
	अगर (err)
		जाओ err2;

	hfsplus_cat_build_key_with_cnid(sb, fd.search_key, cnid);
	entry_size = hfsplus_fill_cat_thपढ़ो(sb, &entry,
		S_ISसूची(inode->i_mode) ?
			HFSPLUS_FOLDER_THREAD : HFSPLUS_खाता_THREAD,
		dir->i_ino, str);
	अगर (unlikely(entry_size < 0)) अणु
		err = entry_size;
		जाओ err2;
	पूर्ण

	err = hfs_brec_find(&fd, hfs_find_rec_by_key);
	अगर (err != -ENOENT) अणु
		अगर (!err)
			err = -EEXIST;
		जाओ err2;
	पूर्ण
	err = hfs_brec_insert(&fd, &entry, entry_size);
	अगर (err)
		जाओ err2;

	err = hfsplus_cat_build_key(sb, fd.search_key, dir->i_ino, str);
	अगर (unlikely(err))
		जाओ err1;

	entry_size = hfsplus_cat_build_record(&entry, cnid, inode);
	err = hfs_brec_find(&fd, hfs_find_rec_by_key);
	अगर (err != -ENOENT) अणु
		/* panic? */
		अगर (!err)
			err = -EEXIST;
		जाओ err1;
	पूर्ण
	err = hfs_brec_insert(&fd, &entry, entry_size);
	अगर (err)
		जाओ err1;

	dir->i_size++;
	अगर (S_ISसूची(inode->i_mode))
		hfsplus_subfolders_inc(dir);
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	hfsplus_mark_inode_dirty(dir, HFSPLUS_I_CAT_सूचीTY);

	hfs_find_निकास(&fd);
	वापस 0;

err1:
	hfsplus_cat_build_key_with_cnid(sb, fd.search_key, cnid);
	अगर (!hfs_brec_find(&fd, hfs_find_rec_by_key))
		hfs_brec_हटाओ(&fd);
err2:
	hfs_find_निकास(&fd);
	वापस err;
पूर्ण

पूर्णांक hfsplus_delete_cat(u32 cnid, काष्ठा inode *dir, स्थिर काष्ठा qstr *str)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा hfs_find_data fd;
	काष्ठा hfsplus_विभाजन_raw विभाजन;
	काष्ठा list_head *pos;
	पूर्णांक err, off;
	u16 type;

	hfs_dbg(CAT_MOD, "delete_cat: %s,%u\n", str ? str->name : शून्य, cnid);
	err = hfs_find_init(HFSPLUS_SB(sb)->cat_tree, &fd);
	अगर (err)
		वापस err;

	/*
	 * Fail early and aव्योम ENOSPC during the btree operations. We may
	 * have to split the root node at most once.
	 */
	err = hfs_bmap_reserve(fd.tree, 2 * (पूर्णांक)fd.tree->depth - 2);
	अगर (err)
		जाओ out;

	अगर (!str) अणु
		पूर्णांक len;

		hfsplus_cat_build_key_with_cnid(sb, fd.search_key, cnid);
		err = hfs_brec_find(&fd, hfs_find_rec_by_key);
		अगर (err)
			जाओ out;

		off = fd.entryoffset +
			दुरत्व(काष्ठा hfsplus_cat_thपढ़ो, nodeName);
		fd.search_key->cat.parent = cpu_to_be32(dir->i_ino);
		hfs_bnode_पढ़ो(fd.bnode,
			&fd.search_key->cat.name.length, off, 2);
		len = be16_to_cpu(fd.search_key->cat.name.length) * 2;
		hfs_bnode_पढ़ो(fd.bnode,
			&fd.search_key->cat.name.unicode,
			off + 2, len);
		fd.search_key->key_len = cpu_to_be16(6 + len);
	पूर्ण अन्यथा अणु
		err = hfsplus_cat_build_key(sb, fd.search_key, dir->i_ino, str);
		अगर (unlikely(err))
			जाओ out;
	पूर्ण

	err = hfs_brec_find(&fd, hfs_find_rec_by_key);
	अगर (err)
		जाओ out;

	type = hfs_bnode_पढ़ो_u16(fd.bnode, fd.entryoffset);
	अगर (type == HFSPLUS_खाता) अणु
#अगर 0
		off = fd.entryoffset + दुरत्व(hfsplus_cat_file, data_विभाजन);
		hfs_bnode_पढ़ो(fd.bnode, &विभाजन, off, माप(विभाजन));
		hfsplus_मुक्त_विभाजन(sb, cnid, &विभाजन, HFSPLUS_TYPE_DATA);
#पूर्ण_अगर

		off = fd.entryoffset +
			दुरत्व(काष्ठा hfsplus_cat_file, rsrc_विभाजन);
		hfs_bnode_पढ़ो(fd.bnode, &विभाजन, off, माप(विभाजन));
		hfsplus_मुक्त_विभाजन(sb, cnid, &विभाजन, HFSPLUS_TYPE_RSRC);
	पूर्ण

	/* we only need to take spinlock क्रम exclusion with ->release() */
	spin_lock(&HFSPLUS_I(dir)->खोलो_dir_lock);
	list_क्रम_each(pos, &HFSPLUS_I(dir)->खोलो_dir_list) अणु
		काष्ठा hfsplus_सूची_पढ़ो_data *rd =
			list_entry(pos, काष्ठा hfsplus_सूची_पढ़ो_data, list);
		अगर (fd.tree->keycmp(fd.search_key, (व्योम *)&rd->key) < 0)
			rd->file->f_pos--;
	पूर्ण
	spin_unlock(&HFSPLUS_I(dir)->खोलो_dir_lock);

	err = hfs_brec_हटाओ(&fd);
	अगर (err)
		जाओ out;

	hfsplus_cat_build_key_with_cnid(sb, fd.search_key, cnid);
	err = hfs_brec_find(&fd, hfs_find_rec_by_key);
	अगर (err)
		जाओ out;

	err = hfs_brec_हटाओ(&fd);
	अगर (err)
		जाओ out;

	dir->i_size--;
	अगर (type == HFSPLUS_FOLDER)
		hfsplus_subfolders_dec(dir);
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	hfsplus_mark_inode_dirty(dir, HFSPLUS_I_CAT_सूचीTY);

	अगर (type == HFSPLUS_खाता || type == HFSPLUS_FOLDER) अणु
		अगर (HFSPLUS_SB(sb)->attr_tree)
			hfsplus_delete_all_attrs(dir, cnid);
	पूर्ण

out:
	hfs_find_निकास(&fd);

	वापस err;
पूर्ण

पूर्णांक hfsplus_नाम_cat(u32 cnid,
		       काष्ठा inode *src_dir, स्थिर काष्ठा qstr *src_name,
		       काष्ठा inode *dst_dir, स्थिर काष्ठा qstr *dst_name)
अणु
	काष्ठा super_block *sb = src_dir->i_sb;
	काष्ठा hfs_find_data src_fd, dst_fd;
	hfsplus_cat_entry entry;
	पूर्णांक entry_size, type;
	पूर्णांक err;

	hfs_dbg(CAT_MOD, "rename_cat: %u - %lu,%s - %lu,%s\n",
		cnid, src_dir->i_ino, src_name->name,
		dst_dir->i_ino, dst_name->name);
	err = hfs_find_init(HFSPLUS_SB(sb)->cat_tree, &src_fd);
	अगर (err)
		वापस err;
	dst_fd = src_fd;

	/*
	 * Fail early and aव्योम ENOSPC during the btree operations. We may
	 * have to split the root node at most twice.
	 */
	err = hfs_bmap_reserve(src_fd.tree, 4 * (पूर्णांक)src_fd.tree->depth - 1);
	अगर (err)
		जाओ out;

	/* find the old dir entry and पढ़ो the data */
	err = hfsplus_cat_build_key(sb, src_fd.search_key,
			src_dir->i_ino, src_name);
	अगर (unlikely(err))
		जाओ out;

	err = hfs_brec_find(&src_fd, hfs_find_rec_by_key);
	अगर (err)
		जाओ out;
	अगर (src_fd.entrylength > माप(entry) || src_fd.entrylength < 0) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	hfs_bnode_पढ़ो(src_fd.bnode, &entry, src_fd.entryoffset,
				src_fd.entrylength);
	type = be16_to_cpu(entry.type);

	/* create new dir entry with the data from the old entry */
	err = hfsplus_cat_build_key(sb, dst_fd.search_key,
			dst_dir->i_ino, dst_name);
	अगर (unlikely(err))
		जाओ out;

	err = hfs_brec_find(&dst_fd, hfs_find_rec_by_key);
	अगर (err != -ENOENT) अणु
		अगर (!err)
			err = -EEXIST;
		जाओ out;
	पूर्ण

	err = hfs_brec_insert(&dst_fd, &entry, src_fd.entrylength);
	अगर (err)
		जाओ out;
	dst_dir->i_size++;
	अगर (type == HFSPLUS_FOLDER)
		hfsplus_subfolders_inc(dst_dir);
	dst_dir->i_mसमय = dst_dir->i_स_समय = current_समय(dst_dir);

	/* finally हटाओ the old entry */
	err = hfsplus_cat_build_key(sb, src_fd.search_key,
			src_dir->i_ino, src_name);
	अगर (unlikely(err))
		जाओ out;

	err = hfs_brec_find(&src_fd, hfs_find_rec_by_key);
	अगर (err)
		जाओ out;
	err = hfs_brec_हटाओ(&src_fd);
	अगर (err)
		जाओ out;
	src_dir->i_size--;
	अगर (type == HFSPLUS_FOLDER)
		hfsplus_subfolders_dec(src_dir);
	src_dir->i_mसमय = src_dir->i_स_समय = current_समय(src_dir);

	/* हटाओ old thपढ़ो entry */
	hfsplus_cat_build_key_with_cnid(sb, src_fd.search_key, cnid);
	err = hfs_brec_find(&src_fd, hfs_find_rec_by_key);
	अगर (err)
		जाओ out;
	type = hfs_bnode_पढ़ो_u16(src_fd.bnode, src_fd.entryoffset);
	err = hfs_brec_हटाओ(&src_fd);
	अगर (err)
		जाओ out;

	/* create new thपढ़ो entry */
	hfsplus_cat_build_key_with_cnid(sb, dst_fd.search_key, cnid);
	entry_size = hfsplus_fill_cat_thपढ़ो(sb, &entry, type,
		dst_dir->i_ino, dst_name);
	अगर (unlikely(entry_size < 0)) अणु
		err = entry_size;
		जाओ out;
	पूर्ण

	err = hfs_brec_find(&dst_fd, hfs_find_rec_by_key);
	अगर (err != -ENOENT) अणु
		अगर (!err)
			err = -EEXIST;
		जाओ out;
	पूर्ण
	err = hfs_brec_insert(&dst_fd, &entry, entry_size);

	hfsplus_mark_inode_dirty(dst_dir, HFSPLUS_I_CAT_सूचीTY);
	hfsplus_mark_inode_dirty(src_dir, HFSPLUS_I_CAT_सूचीTY);
out:
	hfs_bnode_put(dst_fd.bnode);
	hfs_find_निकास(&src_fd);
	वापस err;
पूर्ण
