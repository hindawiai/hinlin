<शैली गुरु>
/*
 *  linux/fs/hfs/catalog.c
 *
 * Copyright (C) 1995-1997  Paul H. Hargrove
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 * This file may be distributed under the terms of the GNU General Public License.
 *
 * This file contains the functions related to the catalog B-tree.
 *
 * Cache code shamelessly stolen from
 *     linux/fs/inode.c Copyright (C) 1991, 1992  Linus Torvalds
 *     re-shamelessly stolen Copyright (C) 1997 Linus Torvalds
 */

#समावेश "hfs_fs.h"
#समावेश "btree.h"

/*
 * hfs_cat_build_key()
 *
 * Given the ID of the parent and the name build a search key.
 */
व्योम hfs_cat_build_key(काष्ठा super_block *sb, btree_key *key, u32 parent, स्थिर काष्ठा qstr *name)
अणु
	key->cat.reserved = 0;
	key->cat.ParID = cpu_to_be32(parent);
	अगर (name) अणु
		hfs_asc2mac(sb, &key->cat.CName, name);
		key->key_len = 6 + key->cat.CName.len;
	पूर्ण अन्यथा अणु
		स_रखो(&key->cat.CName, 0, माप(काष्ठा hfs_name));
		key->key_len = 6;
	पूर्ण
पूर्ण

अटल पूर्णांक hfs_cat_build_record(hfs_cat_rec *rec, u32 cnid, काष्ठा inode *inode)
अणु
	__be32 mसमय = hfs_mसमय();

	स_रखो(rec, 0, माप(*rec));
	अगर (S_ISसूची(inode->i_mode)) अणु
		rec->type = HFS_CDR_सूची;
		rec->dir.DirID = cpu_to_be32(cnid);
		rec->dir.CrDat = mसमय;
		rec->dir.MdDat = mसमय;
		rec->dir.BkDat = 0;
		rec->dir.UsrInfo.frView = cpu_to_be16(0xff);
		वापस माप(काष्ठा hfs_cat_dir);
	पूर्ण अन्यथा अणु
		/* init some fields क्रम the file record */
		rec->type = HFS_CDR_FIL;
		rec->file.Flags = HFS_FIL_USED | HFS_FIL_THD;
		अगर (!(inode->i_mode & S_IWUSR))
			rec->file.Flags |= HFS_FIL_LOCK;
		rec->file.FlNum = cpu_to_be32(cnid);
		rec->file.CrDat = mसमय;
		rec->file.MdDat = mसमय;
		rec->file.BkDat = 0;
		rec->file.UsrWds.fdType = HFS_SB(inode->i_sb)->s_type;
		rec->file.UsrWds.fdCreator = HFS_SB(inode->i_sb)->s_creator;
		वापस माप(काष्ठा hfs_cat_file);
	पूर्ण
पूर्ण

अटल पूर्णांक hfs_cat_build_thपढ़ो(काष्ठा super_block *sb,
				hfs_cat_rec *rec, पूर्णांक type,
				u32 parentid, स्थिर काष्ठा qstr *name)
अणु
	rec->type = type;
	स_रखो(rec->thपढ़ो.reserved, 0, माप(rec->thपढ़ो.reserved));
	rec->thपढ़ो.ParID = cpu_to_be32(parentid);
	hfs_asc2mac(sb, &rec->thपढ़ो.CName, name);
	वापस माप(काष्ठा hfs_cat_thपढ़ो);
पूर्ण

/*
 * create_entry()
 *
 * Add a new file or directory to the catalog B-tree and
 * वापस a (काष्ठा hfs_cat_entry) क्रम it in '*result'.
 */
पूर्णांक hfs_cat_create(u32 cnid, काष्ठा inode *dir, स्थिर काष्ठा qstr *str, काष्ठा inode *inode)
अणु
	काष्ठा hfs_find_data fd;
	काष्ठा super_block *sb;
	जोड़ hfs_cat_rec entry;
	पूर्णांक entry_size;
	पूर्णांक err;

	hfs_dbg(CAT_MOD, "create_cat: %s,%u(%d)\n",
		str->name, cnid, inode->i_nlink);
	अगर (dir->i_size >= HFS_MAX_VALENCE)
		वापस -ENOSPC;

	sb = dir->i_sb;
	err = hfs_find_init(HFS_SB(sb)->cat_tree, &fd);
	अगर (err)
		वापस err;

	/*
	 * Fail early and aव्योम ENOSPC during the btree operations. We may
	 * have to split the root node at most once.
	 */
	err = hfs_bmap_reserve(fd.tree, 2 * fd.tree->depth);
	अगर (err)
		जाओ err2;

	hfs_cat_build_key(sb, fd.search_key, cnid, शून्य);
	entry_size = hfs_cat_build_thपढ़ो(sb, &entry, S_ISसूची(inode->i_mode) ?
			HFS_CDR_THD : HFS_CDR_FTH,
			dir->i_ino, str);
	err = hfs_brec_find(&fd);
	अगर (err != -ENOENT) अणु
		अगर (!err)
			err = -EEXIST;
		जाओ err2;
	पूर्ण
	err = hfs_brec_insert(&fd, &entry, entry_size);
	अगर (err)
		जाओ err2;

	hfs_cat_build_key(sb, fd.search_key, dir->i_ino, str);
	entry_size = hfs_cat_build_record(&entry, cnid, inode);
	err = hfs_brec_find(&fd);
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
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	mark_inode_dirty(dir);
	hfs_find_निकास(&fd);
	वापस 0;

err1:
	hfs_cat_build_key(sb, fd.search_key, cnid, शून्य);
	अगर (!hfs_brec_find(&fd))
		hfs_brec_हटाओ(&fd);
err2:
	hfs_find_निकास(&fd);
	वापस err;
पूर्ण

/*
 * hfs_cat_compare()
 *
 * Description:
 *   This is the comparison function used क्रम the catalog B-tree.  In
 *   comparing catalog B-tree entries, the parent id is the most
 *   signअगरicant field (compared as अचिन्हित पूर्णांकs).  The name field is
 *   the least signअगरicant (compared in "Macintosh lexical order",
 *   see hfs_म_भेद() in string.c)
 * Input Variable(s):
 *   काष्ठा hfs_cat_key *key1: poपूर्णांकer to the first key to compare
 *   काष्ठा hfs_cat_key *key2: poपूर्णांकer to the second key to compare
 * Output Variable(s):
 *   NONE
 * Returns:
 *   पूर्णांक: negative अगर key1<key2, positive अगर key1>key2, and 0 अगर key1==key2
 * Preconditions:
 *   key1 and key2 poपूर्णांक to "valid" (काष्ठा hfs_cat_key)s.
 * Postconditions:
 *   This function has no side-effects
 */
पूर्णांक hfs_cat_keycmp(स्थिर btree_key *key1, स्थिर btree_key *key2)
अणु
	__be32 k1p, k2p;

	k1p = key1->cat.ParID;
	k2p = key2->cat.ParID;

	अगर (k1p != k2p)
		वापस be32_to_cpu(k1p) < be32_to_cpu(k2p) ? -1 : 1;

	वापस hfs_म_भेद(key1->cat.CName.name, key1->cat.CName.len,
			  key2->cat.CName.name, key2->cat.CName.len);
पूर्ण

/* Try to get a catalog entry क्रम given catalog id */
// move to पढ़ो_super???
पूर्णांक hfs_cat_find_brec(काष्ठा super_block *sb, u32 cnid,
		      काष्ठा hfs_find_data *fd)
अणु
	hfs_cat_rec rec;
	पूर्णांक res, len, type;

	hfs_cat_build_key(sb, fd->search_key, cnid, शून्य);
	res = hfs_brec_पढ़ो(fd, &rec, माप(rec));
	अगर (res)
		वापस res;

	type = rec.type;
	अगर (type != HFS_CDR_THD && type != HFS_CDR_FTH) अणु
		pr_err("found bad thread record in catalog\n");
		वापस -EIO;
	पूर्ण

	fd->search_key->cat.ParID = rec.thपढ़ो.ParID;
	len = fd->search_key->cat.CName.len = rec.thपढ़ो.CName.len;
	अगर (len > HFS_NAMELEN) अणु
		pr_err("bad catalog namelength\n");
		वापस -EIO;
	पूर्ण
	स_नकल(fd->search_key->cat.CName.name, rec.thपढ़ो.CName.name, len);
	वापस hfs_brec_find(fd);
पूर्ण


/*
 * hfs_cat_delete()
 *
 * Delete the indicated file or directory.
 * The associated thपढ़ो is also हटाओd unless ('with_thread'==0).
 */
पूर्णांक hfs_cat_delete(u32 cnid, काष्ठा inode *dir, स्थिर काष्ठा qstr *str)
अणु
	काष्ठा super_block *sb;
	काष्ठा hfs_find_data fd;
	काष्ठा hfs_सूची_पढ़ो_data *rd;
	पूर्णांक res, type;

	hfs_dbg(CAT_MOD, "delete_cat: %s,%u\n", str ? str->name : शून्य, cnid);
	sb = dir->i_sb;
	res = hfs_find_init(HFS_SB(sb)->cat_tree, &fd);
	अगर (res)
		वापस res;

	hfs_cat_build_key(sb, fd.search_key, dir->i_ino, str);
	res = hfs_brec_find(&fd);
	अगर (res)
		जाओ out;

	type = hfs_bnode_पढ़ो_u8(fd.bnode, fd.entryoffset);
	अगर (type == HFS_CDR_FIL) अणु
		काष्ठा hfs_cat_file file;
		hfs_bnode_पढ़ो(fd.bnode, &file, fd.entryoffset, माप(file));
		अगर (be32_to_cpu(file.FlNum) == cnid) अणु
#अगर 0
			hfs_मुक्त_विभाजन(sb, &file, HFS_FK_DATA);
#पूर्ण_अगर
			hfs_मुक्त_विभाजन(sb, &file, HFS_FK_RSRC);
		पूर्ण
	पूर्ण

	/* we only need to take spinlock क्रम exclusion with ->release() */
	spin_lock(&HFS_I(dir)->खोलो_dir_lock);
	list_क्रम_each_entry(rd, &HFS_I(dir)->खोलो_dir_list, list) अणु
		अगर (fd.tree->keycmp(fd.search_key, (व्योम *)&rd->key) < 0)
			rd->file->f_pos--;
	पूर्ण
	spin_unlock(&HFS_I(dir)->खोलो_dir_lock);

	res = hfs_brec_हटाओ(&fd);
	अगर (res)
		जाओ out;

	hfs_cat_build_key(sb, fd.search_key, cnid, शून्य);
	res = hfs_brec_find(&fd);
	अगर (!res) अणु
		res = hfs_brec_हटाओ(&fd);
		अगर (res)
			जाओ out;
	पूर्ण

	dir->i_size--;
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	mark_inode_dirty(dir);
	res = 0;
out:
	hfs_find_निकास(&fd);

	वापस res;
पूर्ण

/*
 * hfs_cat_move()
 *
 * Rename a file or directory, possibly to a new directory.
 * If the destination exists it is हटाओd and a
 * (काष्ठा hfs_cat_entry) क्रम it is वापसed in '*result'.
 */
पूर्णांक hfs_cat_move(u32 cnid, काष्ठा inode *src_dir, स्थिर काष्ठा qstr *src_name,
		 काष्ठा inode *dst_dir, स्थिर काष्ठा qstr *dst_name)
अणु
	काष्ठा super_block *sb;
	काष्ठा hfs_find_data src_fd, dst_fd;
	जोड़ hfs_cat_rec entry;
	पूर्णांक entry_size, type;
	पूर्णांक err;

	hfs_dbg(CAT_MOD, "rename_cat: %u - %lu,%s - %lu,%s\n",
		cnid, src_dir->i_ino, src_name->name,
		dst_dir->i_ino, dst_name->name);
	sb = src_dir->i_sb;
	err = hfs_find_init(HFS_SB(sb)->cat_tree, &src_fd);
	अगर (err)
		वापस err;
	dst_fd = src_fd;

	/*
	 * Fail early and aव्योम ENOSPC during the btree operations. We may
	 * have to split the root node at most once.
	 */
	err = hfs_bmap_reserve(src_fd.tree, 2 * src_fd.tree->depth);
	अगर (err)
		जाओ out;

	/* find the old dir entry and पढ़ो the data */
	hfs_cat_build_key(sb, src_fd.search_key, src_dir->i_ino, src_name);
	err = hfs_brec_find(&src_fd);
	अगर (err)
		जाओ out;
	अगर (src_fd.entrylength > माप(entry) || src_fd.entrylength < 0) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	hfs_bnode_पढ़ो(src_fd.bnode, &entry, src_fd.entryoffset,
			    src_fd.entrylength);

	/* create new dir entry with the data from the old entry */
	hfs_cat_build_key(sb, dst_fd.search_key, dst_dir->i_ino, dst_name);
	err = hfs_brec_find(&dst_fd);
	अगर (err != -ENOENT) अणु
		अगर (!err)
			err = -EEXIST;
		जाओ out;
	पूर्ण

	err = hfs_brec_insert(&dst_fd, &entry, src_fd.entrylength);
	अगर (err)
		जाओ out;
	dst_dir->i_size++;
	dst_dir->i_mसमय = dst_dir->i_स_समय = current_समय(dst_dir);
	mark_inode_dirty(dst_dir);

	/* finally हटाओ the old entry */
	hfs_cat_build_key(sb, src_fd.search_key, src_dir->i_ino, src_name);
	err = hfs_brec_find(&src_fd);
	अगर (err)
		जाओ out;
	err = hfs_brec_हटाओ(&src_fd);
	अगर (err)
		जाओ out;
	src_dir->i_size--;
	src_dir->i_mसमय = src_dir->i_स_समय = current_समय(src_dir);
	mark_inode_dirty(src_dir);

	type = entry.type;
	अगर (type == HFS_CDR_FIL && !(entry.file.Flags & HFS_FIL_THD))
		जाओ out;

	/* हटाओ old thपढ़ो entry */
	hfs_cat_build_key(sb, src_fd.search_key, cnid, शून्य);
	err = hfs_brec_find(&src_fd);
	अगर (err)
		जाओ out;
	err = hfs_brec_हटाओ(&src_fd);
	अगर (err)
		जाओ out;

	/* create new thपढ़ो entry */
	hfs_cat_build_key(sb, dst_fd.search_key, cnid, शून्य);
	entry_size = hfs_cat_build_thपढ़ो(sb, &entry, type == HFS_CDR_FIL ? HFS_CDR_FTH : HFS_CDR_THD,
					dst_dir->i_ino, dst_name);
	err = hfs_brec_find(&dst_fd);
	अगर (err != -ENOENT) अणु
		अगर (!err)
			err = -EEXIST;
		जाओ out;
	पूर्ण
	err = hfs_brec_insert(&dst_fd, &entry, entry_size);
out:
	hfs_bnode_put(dst_fd.bnode);
	hfs_find_निकास(&src_fd);
	वापस err;
पूर्ण
