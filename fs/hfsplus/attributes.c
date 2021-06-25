<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/hfsplus/attributes.c
 *
 * Vyacheslav Dubeyko <slava@dubeyko.com>
 *
 * Handling of records in attributes tree
 */

#समावेश "hfsplus_fs.h"
#समावेश "hfsplus_raw.h"

अटल काष्ठा kmem_cache *hfsplus_attr_tree_cachep;

पूर्णांक __init hfsplus_create_attr_tree_cache(व्योम)
अणु
	अगर (hfsplus_attr_tree_cachep)
		वापस -EEXIST;

	hfsplus_attr_tree_cachep =
		kmem_cache_create("hfsplus_attr_cache",
			माप(hfsplus_attr_entry), 0,
			SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!hfsplus_attr_tree_cachep)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम hfsplus_destroy_attr_tree_cache(व्योम)
अणु
	kmem_cache_destroy(hfsplus_attr_tree_cachep);
पूर्ण

पूर्णांक hfsplus_attr_bin_cmp_key(स्थिर hfsplus_btree_key *k1,
				स्थिर hfsplus_btree_key *k2)
अणु
	__be32 k1_cnid, k2_cnid;

	k1_cnid = k1->attr.cnid;
	k2_cnid = k2->attr.cnid;
	अगर (k1_cnid != k2_cnid)
		वापस be32_to_cpu(k1_cnid) < be32_to_cpu(k2_cnid) ? -1 : 1;

	वापस hfsplus_म_भेद(
			(स्थिर काष्ठा hfsplus_unistr *)&k1->attr.key_name,
			(स्थिर काष्ठा hfsplus_unistr *)&k2->attr.key_name);
पूर्ण

पूर्णांक hfsplus_attr_build_key(काष्ठा super_block *sb, hfsplus_btree_key *key,
			u32 cnid, स्थिर अक्षर *name)
अणु
	पूर्णांक len;

	स_रखो(key, 0, माप(काष्ठा hfsplus_attr_key));
	key->attr.cnid = cpu_to_be32(cnid);
	अगर (name) अणु
		पूर्णांक res = hfsplus_asc2uni(sb,
				(काष्ठा hfsplus_unistr *)&key->attr.key_name,
				HFSPLUS_ATTR_MAX_STRLEN, name, म_माप(name));
		अगर (res)
			वापस res;
		len = be16_to_cpu(key->attr.key_name.length);
	पूर्ण अन्यथा अणु
		key->attr.key_name.length = 0;
		len = 0;
	पूर्ण

	/* The length of the key, as stored in key_len field, करोes not include
	 * the size of the key_len field itself.
	 * So, दुरत्व(hfsplus_attr_key, key_name) is a trick because
	 * it takes पूर्णांकo consideration key_len field (__be16) of
	 * hfsplus_attr_key काष्ठाure instead of length field (__be16) of
	 * hfsplus_attr_unistr काष्ठाure.
	 */
	key->key_len =
		cpu_to_be16(दुरत्व(काष्ठा hfsplus_attr_key, key_name) +
				2 * len);

	वापस 0;
पूर्ण

hfsplus_attr_entry *hfsplus_alloc_attr_entry(व्योम)
अणु
	वापस kmem_cache_alloc(hfsplus_attr_tree_cachep, GFP_KERNEL);
पूर्ण

व्योम hfsplus_destroy_attr_entry(hfsplus_attr_entry *entry)
अणु
	अगर (entry)
		kmem_cache_मुक्त(hfsplus_attr_tree_cachep, entry);
पूर्ण

#घोषणा HFSPLUS_INVALID_ATTR_RECORD -1

अटल पूर्णांक hfsplus_attr_build_record(hfsplus_attr_entry *entry, पूर्णांक record_type,
				u32 cnid, स्थिर व्योम *value, माप_प्रकार size)
अणु
	अगर (record_type == HFSPLUS_ATTR_FORK_DATA) अणु
		/*
		 * Mac OS X supports only अंतरभूत data attributes.
		 * Do nothing
		 */
		स_रखो(entry, 0, माप(*entry));
		वापस माप(काष्ठा hfsplus_attr_विभाजन_data);
	पूर्ण अन्यथा अगर (record_type == HFSPLUS_ATTR_EXTENTS) अणु
		/*
		 * Mac OS X supports only अंतरभूत data attributes.
		 * Do nothing.
		 */
		स_रखो(entry, 0, माप(*entry));
		वापस माप(काष्ठा hfsplus_attr_extents);
	पूर्ण अन्यथा अगर (record_type == HFSPLUS_ATTR_INLINE_DATA) अणु
		u16 len;

		स_रखो(entry, 0, माप(काष्ठा hfsplus_attr_अंतरभूत_data));
		entry->अंतरभूत_data.record_type = cpu_to_be32(record_type);
		अगर (size <= HFSPLUS_MAX_INLINE_DATA_SIZE)
			len = size;
		अन्यथा
			वापस HFSPLUS_INVALID_ATTR_RECORD;
		entry->अंतरभूत_data.length = cpu_to_be16(len);
		स_नकल(entry->अंतरभूत_data.raw_bytes, value, len);
		/*
		 * Align len on two-byte boundary.
		 * It needs to add pad byte अगर we have odd len.
		 */
		len = round_up(len, 2);
		वापस दुरत्व(काष्ठा hfsplus_attr_अंतरभूत_data, raw_bytes) +
					len;
	पूर्ण अन्यथा /* invalid input */
		स_रखो(entry, 0, माप(*entry));

	वापस HFSPLUS_INVALID_ATTR_RECORD;
पूर्ण

पूर्णांक hfsplus_find_attr(काष्ठा super_block *sb, u32 cnid,
			स्थिर अक्षर *name, काष्ठा hfs_find_data *fd)
अणु
	पूर्णांक err = 0;

	hfs_dbg(ATTR_MOD, "find_attr: %s,%d\n", name ? name : शून्य, cnid);

	अगर (!HFSPLUS_SB(sb)->attr_tree) अणु
		pr_err("attributes file doesn't exist\n");
		वापस -EINVAL;
	पूर्ण

	अगर (name) अणु
		err = hfsplus_attr_build_key(sb, fd->search_key, cnid, name);
		अगर (err)
			जाओ failed_find_attr;
		err = hfs_brec_find(fd, hfs_find_rec_by_key);
		अगर (err)
			जाओ failed_find_attr;
	पूर्ण अन्यथा अणु
		err = hfsplus_attr_build_key(sb, fd->search_key, cnid, शून्य);
		अगर (err)
			जाओ failed_find_attr;
		err = hfs_brec_find(fd, hfs_find_1st_rec_by_cnid);
		अगर (err)
			जाओ failed_find_attr;
	पूर्ण

failed_find_attr:
	वापस err;
पूर्ण

पूर्णांक hfsplus_attr_exists(काष्ठा inode *inode, स्थिर अक्षर *name)
अणु
	पूर्णांक err = 0;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा hfs_find_data fd;

	अगर (!HFSPLUS_SB(sb)->attr_tree)
		वापस 0;

	err = hfs_find_init(HFSPLUS_SB(sb)->attr_tree, &fd);
	अगर (err)
		वापस 0;

	err = hfsplus_find_attr(sb, inode->i_ino, name, &fd);
	अगर (err)
		जाओ attr_not_found;

	hfs_find_निकास(&fd);
	वापस 1;

attr_not_found:
	hfs_find_निकास(&fd);
	वापस 0;
पूर्ण

पूर्णांक hfsplus_create_attr(काष्ठा inode *inode,
				स्थिर अक्षर *name,
				स्थिर व्योम *value, माप_प्रकार size)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा hfs_find_data fd;
	hfsplus_attr_entry *entry_ptr;
	पूर्णांक entry_size;
	पूर्णांक err;

	hfs_dbg(ATTR_MOD, "create_attr: %s,%ld\n",
		name ? name : शून्य, inode->i_ino);

	अगर (!HFSPLUS_SB(sb)->attr_tree) अणु
		pr_err("attributes file doesn't exist\n");
		वापस -EINVAL;
	पूर्ण

	entry_ptr = hfsplus_alloc_attr_entry();
	अगर (!entry_ptr)
		वापस -ENOMEM;

	err = hfs_find_init(HFSPLUS_SB(sb)->attr_tree, &fd);
	अगर (err)
		जाओ failed_init_create_attr;

	/* Fail early and aव्योम ENOSPC during the btree operation */
	err = hfs_bmap_reserve(fd.tree, fd.tree->depth + 1);
	अगर (err)
		जाओ failed_create_attr;

	अगर (name) अणु
		err = hfsplus_attr_build_key(sb, fd.search_key,
						inode->i_ino, name);
		अगर (err)
			जाओ failed_create_attr;
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		जाओ failed_create_attr;
	पूर्ण

	/* Mac OS X supports only अंतरभूत data attributes. */
	entry_size = hfsplus_attr_build_record(entry_ptr,
					HFSPLUS_ATTR_INLINE_DATA,
					inode->i_ino,
					value, size);
	अगर (entry_size == HFSPLUS_INVALID_ATTR_RECORD) अणु
		err = -EINVAL;
		जाओ failed_create_attr;
	पूर्ण

	err = hfs_brec_find(&fd, hfs_find_rec_by_key);
	अगर (err != -ENOENT) अणु
		अगर (!err)
			err = -EEXIST;
		जाओ failed_create_attr;
	पूर्ण

	err = hfs_brec_insert(&fd, entry_ptr, entry_size);
	अगर (err)
		जाओ failed_create_attr;

	hfsplus_mark_inode_dirty(inode, HFSPLUS_I_ATTR_सूचीTY);

failed_create_attr:
	hfs_find_निकास(&fd);

failed_init_create_attr:
	hfsplus_destroy_attr_entry(entry_ptr);
	वापस err;
पूर्ण

अटल पूर्णांक __hfsplus_delete_attr(काष्ठा inode *inode, u32 cnid,
					काष्ठा hfs_find_data *fd)
अणु
	पूर्णांक err = 0;
	__be32 found_cnid, record_type;

	hfs_bnode_पढ़ो(fd->bnode, &found_cnid,
			fd->keyoffset +
			दुरत्व(काष्ठा hfsplus_attr_key, cnid),
			माप(__be32));
	अगर (cnid != be32_to_cpu(found_cnid))
		वापस -ENOENT;

	hfs_bnode_पढ़ो(fd->bnode, &record_type,
			fd->entryoffset, माप(record_type));

	चयन (be32_to_cpu(record_type)) अणु
	हाल HFSPLUS_ATTR_INLINE_DATA:
		/* All is OK. Do nothing. */
		अवरोध;
	हाल HFSPLUS_ATTR_FORK_DATA:
	हाल HFSPLUS_ATTR_EXTENTS:
		pr_err("only inline data xattr are supported\n");
		वापस -EOPNOTSUPP;
	शेष:
		pr_err("invalid extended attribute record\n");
		वापस -ENOENT;
	पूर्ण

	/* Aव्योम btree corruption */
	hfs_bnode_पढ़ो(fd->bnode, fd->search_key,
			fd->keyoffset, fd->keylength);

	err = hfs_brec_हटाओ(fd);
	अगर (err)
		वापस err;

	hfsplus_mark_inode_dirty(inode, HFSPLUS_I_ATTR_सूचीTY);
	वापस err;
पूर्ण

पूर्णांक hfsplus_delete_attr(काष्ठा inode *inode, स्थिर अक्षर *name)
अणु
	पूर्णांक err = 0;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा hfs_find_data fd;

	hfs_dbg(ATTR_MOD, "delete_attr: %s,%ld\n",
		name ? name : शून्य, inode->i_ino);

	अगर (!HFSPLUS_SB(sb)->attr_tree) अणु
		pr_err("attributes file doesn't exist\n");
		वापस -EINVAL;
	पूर्ण

	err = hfs_find_init(HFSPLUS_SB(sb)->attr_tree, &fd);
	अगर (err)
		वापस err;

	/* Fail early and aव्योम ENOSPC during the btree operation */
	err = hfs_bmap_reserve(fd.tree, fd.tree->depth);
	अगर (err)
		जाओ out;

	अगर (name) अणु
		err = hfsplus_attr_build_key(sb, fd.search_key,
						inode->i_ino, name);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		pr_err("invalid extended attribute name\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = hfs_brec_find(&fd, hfs_find_rec_by_key);
	अगर (err)
		जाओ out;

	err = __hfsplus_delete_attr(inode, inode->i_ino, &fd);
	अगर (err)
		जाओ out;

out:
	hfs_find_निकास(&fd);
	वापस err;
पूर्ण

पूर्णांक hfsplus_delete_all_attrs(काष्ठा inode *dir, u32 cnid)
अणु
	पूर्णांक err = 0;
	काष्ठा hfs_find_data fd;

	hfs_dbg(ATTR_MOD, "delete_all_attrs: %d\n", cnid);

	अगर (!HFSPLUS_SB(dir->i_sb)->attr_tree) अणु
		pr_err("attributes file doesn't exist\n");
		वापस -EINVAL;
	पूर्ण

	err = hfs_find_init(HFSPLUS_SB(dir->i_sb)->attr_tree, &fd);
	अगर (err)
		वापस err;

	क्रम (;;) अणु
		err = hfsplus_find_attr(dir->i_sb, cnid, शून्य, &fd);
		अगर (err) अणु
			अगर (err != -ENOENT)
				pr_err("xattr search failed\n");
			जाओ end_delete_all;
		पूर्ण

		err = __hfsplus_delete_attr(dir, cnid, &fd);
		अगर (err)
			जाओ end_delete_all;
	पूर्ण

end_delete_all:
	hfs_find_निकास(&fd);
	वापस err;
पूर्ण
