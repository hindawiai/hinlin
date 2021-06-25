<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/hfsplus/xattr.c
 *
 * Vyacheslav Dubeyko <slava@dubeyko.com>
 *
 * Logic of processing extended attributes
 */

#समावेश "hfsplus_fs.h"
#समावेश <linux/nls.h>
#समावेश "xattr.h"

अटल पूर्णांक hfsplus_हटाओxattr(काष्ठा inode *inode, स्थिर अक्षर *name);

स्थिर काष्ठा xattr_handler *hfsplus_xattr_handlers[] = अणु
	&hfsplus_xattr_osx_handler,
	&hfsplus_xattr_user_handler,
	&hfsplus_xattr_trusted_handler,
	&hfsplus_xattr_security_handler,
	शून्य
पूर्ण;

अटल पूर्णांक म_भेद_xattr_finder_info(स्थिर अक्षर *name)
अणु
	अगर (name) अणु
		वापस म_भेदन(name, HFSPLUS_XATTR_FINDER_INFO_NAME,
				माप(HFSPLUS_XATTR_FINDER_INFO_NAME));
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक म_भेद_xattr_acl(स्थिर अक्षर *name)
अणु
	अगर (name) अणु
		वापस म_भेदन(name, HFSPLUS_XATTR_ACL_NAME,
				माप(HFSPLUS_XATTR_ACL_NAME));
	पूर्ण
	वापस -1;
पूर्ण

अटल bool is_known_namespace(स्थिर अक्षर *name)
अणु
	अगर (म_भेदन(name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN) &&
	    म_भेदन(name, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN) &&
	    म_भेदन(name, XATTR_SECURITY_PREFIX, XATTR_SECURITY_PREFIX_LEN) &&
	    म_भेदन(name, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम hfsplus_init_header_node(काष्ठा inode *attr_file,
					u32 clump_size,
					अक्षर *buf, u16 node_size)
अणु
	काष्ठा hfs_bnode_desc *desc;
	काष्ठा hfs_btree_header_rec *head;
	u16 offset;
	__be16 *rec_offsets;
	u32 hdr_node_map_rec_bits;
	अक्षर *bmp;
	u32 used_nodes;
	u32 used_bmp_bytes;
	u64 पंचांगp;

	hfs_dbg(ATTR_MOD, "init_hdr_attr_file: clump %u, node_size %u\n",
		clump_size, node_size);

	/* The end of the node contains list of record offsets */
	rec_offsets = (__be16 *)(buf + node_size);

	desc = (काष्ठा hfs_bnode_desc *)buf;
	desc->type = HFS_NODE_HEADER;
	desc->num_recs = cpu_to_be16(HFSPLUS_BTREE_HDR_NODE_RECS_COUNT);
	offset = माप(काष्ठा hfs_bnode_desc);
	*--rec_offsets = cpu_to_be16(offset);

	head = (काष्ठा hfs_btree_header_rec *)(buf + offset);
	head->node_size = cpu_to_be16(node_size);
	पंचांगp = i_size_पढ़ो(attr_file);
	करो_भाग(पंचांगp, node_size);
	head->node_count = cpu_to_be32(पंचांगp);
	head->मुक्त_nodes = cpu_to_be32(be32_to_cpu(head->node_count) - 1);
	head->clump_size = cpu_to_be32(clump_size);
	head->attributes |= cpu_to_be32(HFS_TREE_BIGKEYS | HFS_TREE_VARIDXKEYS);
	head->max_key_len = cpu_to_be16(HFSPLUS_ATTR_KEYLEN - माप(u16));
	offset += माप(काष्ठा hfs_btree_header_rec);
	*--rec_offsets = cpu_to_be16(offset);
	offset += HFSPLUS_BTREE_HDR_USER_BYTES;
	*--rec_offsets = cpu_to_be16(offset);

	hdr_node_map_rec_bits = 8 * (node_size - offset - (4 * माप(u16)));
	अगर (be32_to_cpu(head->node_count) > hdr_node_map_rec_bits) अणु
		u32 map_node_bits;
		u32 map_nodes;

		desc->next = cpu_to_be32(be32_to_cpu(head->leaf_tail) + 1);
		map_node_bits = 8 * (node_size - माप(काष्ठा hfs_bnode_desc) -
					(2 * माप(u16)) - 2);
		map_nodes = (be32_to_cpu(head->node_count) -
				hdr_node_map_rec_bits +
				(map_node_bits - 1)) / map_node_bits;
		be32_add_cpu(&head->मुक्त_nodes, 0 - map_nodes);
	पूर्ण

	bmp = buf + offset;
	used_nodes =
		be32_to_cpu(head->node_count) - be32_to_cpu(head->मुक्त_nodes);
	used_bmp_bytes = used_nodes / 8;
	अगर (used_bmp_bytes) अणु
		स_रखो(bmp, 0xFF, used_bmp_bytes);
		bmp += used_bmp_bytes;
		used_nodes %= 8;
	पूर्ण
	*bmp = ~(0xFF >> used_nodes);
	offset += hdr_node_map_rec_bits / 8;
	*--rec_offsets = cpu_to_be16(offset);
पूर्ण

अटल पूर्णांक hfsplus_create_attributes_file(काष्ठा super_block *sb)
अणु
	पूर्णांक err = 0;
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	काष्ठा inode *attr_file;
	काष्ठा hfsplus_inode_info *hip;
	u32 clump_size;
	u16 node_size = HFSPLUS_ATTR_TREE_NODE_SIZE;
	अक्षर *buf;
	पूर्णांक index, written;
	काष्ठा address_space *mapping;
	काष्ठा page *page;
	पूर्णांक old_state = HFSPLUS_EMPTY_ATTR_TREE;

	hfs_dbg(ATTR_MOD, "create_attr_file: ino %d\n", HFSPLUS_ATTR_CNID);

check_attr_tree_state_again:
	चयन (atomic_पढ़ो(&sbi->attr_tree_state)) अणु
	हाल HFSPLUS_EMPTY_ATTR_TREE:
		अगर (old_state != atomic_cmpxchg(&sbi->attr_tree_state,
						old_state,
						HFSPLUS_CREATING_ATTR_TREE))
			जाओ check_attr_tree_state_again;
		अवरोध;
	हाल HFSPLUS_CREATING_ATTR_TREE:
		/*
		 * This state means that another thपढ़ो is in process
		 * of AttributesFile creation. Theoretically, it is
		 * possible to be here. But really __setxattr() method
		 * first of all calls hfs_find_init() क्रम lookup in
		 * B-tree of CatalogFile. This method locks mutex of
		 * CatalogFile's B-tree. As a result, अगर some thपढ़ो
		 * is inside AttributedFile creation operation then
		 * another thपढ़ोs will be रुकोing unlocking of
		 * CatalogFile's B-tree's mutex. However, अगर code will
		 * change then we will वापस error code (-EAGAIN) from
		 * here. Really, it means that first try to set of xattr
		 * fails with error but second attempt will have success.
		 */
		वापस -EAGAIN;
	हाल HFSPLUS_VALID_ATTR_TREE:
		वापस 0;
	हाल HFSPLUS_FAILED_ATTR_TREE:
		वापस -EOPNOTSUPP;
	शेष:
		BUG();
	पूर्ण

	attr_file = hfsplus_iget(sb, HFSPLUS_ATTR_CNID);
	अगर (IS_ERR(attr_file)) अणु
		pr_err("failed to load attributes file\n");
		वापस PTR_ERR(attr_file);
	पूर्ण

	BUG_ON(i_size_पढ़ो(attr_file) != 0);

	hip = HFSPLUS_I(attr_file);

	clump_size = hfsplus_calc_btree_clump_size(sb->s_blocksize,
						    node_size,
						    sbi->sect_count,
						    HFSPLUS_ATTR_CNID);

	mutex_lock(&hip->extents_lock);
	hip->clump_blocks = clump_size >> sbi->alloc_blksz_shअगरt;
	mutex_unlock(&hip->extents_lock);

	अगर (sbi->मुक्त_blocks <= (hip->clump_blocks << 1)) अणु
		err = -ENOSPC;
		जाओ end_attr_file_creation;
	पूर्ण

	जबतक (hip->alloc_blocks < hip->clump_blocks) अणु
		err = hfsplus_file_extend(attr_file, false);
		अगर (unlikely(err)) अणु
			pr_err("failed to extend attributes file\n");
			जाओ end_attr_file_creation;
		पूर्ण
		hip->phys_size = attr_file->i_size =
			(loff_t)hip->alloc_blocks << sbi->alloc_blksz_shअगरt;
		hip->fs_blocks = hip->alloc_blocks << sbi->fs_shअगरt;
		inode_set_bytes(attr_file, attr_file->i_size);
	पूर्ण

	buf = kzalloc(node_size, GFP_NOFS);
	अगर (!buf) अणु
		pr_err("failed to allocate memory for header node\n");
		err = -ENOMEM;
		जाओ end_attr_file_creation;
	पूर्ण

	hfsplus_init_header_node(attr_file, clump_size, buf, node_size);

	mapping = attr_file->i_mapping;

	index = 0;
	written = 0;
	क्रम (; written < node_size; index++, written += PAGE_SIZE) अणु
		व्योम *kaddr;

		page = पढ़ो_mapping_page(mapping, index, शून्य);
		अगर (IS_ERR(page)) अणु
			err = PTR_ERR(page);
			जाओ failed_header_node_init;
		पूर्ण

		kaddr = kmap_atomic(page);
		स_नकल(kaddr, buf + written,
			min_t(माप_प्रकार, PAGE_SIZE, node_size - written));
		kunmap_atomic(kaddr);

		set_page_dirty(page);
		put_page(page);
	पूर्ण

	hfsplus_mark_inode_dirty(attr_file, HFSPLUS_I_ATTR_सूचीTY);

	sbi->attr_tree = hfs_btree_खोलो(sb, HFSPLUS_ATTR_CNID);
	अगर (!sbi->attr_tree)
		pr_err("failed to load attributes file\n");

failed_header_node_init:
	kमुक्त(buf);

end_attr_file_creation:
	iput(attr_file);

	अगर (!err)
		atomic_set(&sbi->attr_tree_state, HFSPLUS_VALID_ATTR_TREE);
	अन्यथा अगर (err == -ENOSPC)
		atomic_set(&sbi->attr_tree_state, HFSPLUS_EMPTY_ATTR_TREE);
	अन्यथा
		atomic_set(&sbi->attr_tree_state, HFSPLUS_FAILED_ATTR_TREE);

	वापस err;
पूर्ण

पूर्णांक __hfsplus_setxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक err = 0;
	काष्ठा hfs_find_data cat_fd;
	hfsplus_cat_entry entry;
	u16 cat_entry_flags, cat_entry_type;
	u16 folder_finderinfo_len = माप(काष्ठा DInfo) +
					माप(काष्ठा DXInfo);
	u16 file_finderinfo_len = माप(काष्ठा FInfo) +
					माप(काष्ठा FXInfo);

	अगर ((!S_ISREG(inode->i_mode) &&
			!S_ISसूची(inode->i_mode)) ||
				HFSPLUS_IS_RSRC(inode))
		वापस -EOPNOTSUPP;

	अगर (value == शून्य)
		वापस hfsplus_हटाओxattr(inode, name);

	err = hfs_find_init(HFSPLUS_SB(inode->i_sb)->cat_tree, &cat_fd);
	अगर (err) अणु
		pr_err("can't init xattr find struct\n");
		वापस err;
	पूर्ण

	err = hfsplus_find_cat(inode->i_sb, inode->i_ino, &cat_fd);
	अगर (err) अणु
		pr_err("catalog searching failed\n");
		जाओ end_setxattr;
	पूर्ण

	अगर (!म_भेद_xattr_finder_info(name)) अणु
		अगर (flags & XATTR_CREATE) अणु
			pr_err("xattr exists yet\n");
			err = -EOPNOTSUPP;
			जाओ end_setxattr;
		पूर्ण
		hfs_bnode_पढ़ो(cat_fd.bnode, &entry, cat_fd.entryoffset,
					माप(hfsplus_cat_entry));
		अगर (be16_to_cpu(entry.type) == HFSPLUS_FOLDER) अणु
			अगर (size == folder_finderinfo_len) अणु
				स_नकल(&entry.folder.user_info, value,
						folder_finderinfo_len);
				hfs_bnode_ग_लिखो(cat_fd.bnode, &entry,
					cat_fd.entryoffset,
					माप(काष्ठा hfsplus_cat_folder));
				hfsplus_mark_inode_dirty(inode,
						HFSPLUS_I_CAT_सूचीTY);
			पूर्ण अन्यथा अणु
				err = -दुस्फल;
				जाओ end_setxattr;
			पूर्ण
		पूर्ण अन्यथा अगर (be16_to_cpu(entry.type) == HFSPLUS_खाता) अणु
			अगर (size == file_finderinfo_len) अणु
				स_नकल(&entry.file.user_info, value,
						file_finderinfo_len);
				hfs_bnode_ग_लिखो(cat_fd.bnode, &entry,
					cat_fd.entryoffset,
					माप(काष्ठा hfsplus_cat_file));
				hfsplus_mark_inode_dirty(inode,
						HFSPLUS_I_CAT_सूचीTY);
			पूर्ण अन्यथा अणु
				err = -दुस्फल;
				जाओ end_setxattr;
			पूर्ण
		पूर्ण अन्यथा अणु
			err = -EOPNOTSUPP;
			जाओ end_setxattr;
		पूर्ण
		जाओ end_setxattr;
	पूर्ण

	अगर (!HFSPLUS_SB(inode->i_sb)->attr_tree) अणु
		err = hfsplus_create_attributes_file(inode->i_sb);
		अगर (unlikely(err))
			जाओ end_setxattr;
	पूर्ण

	अगर (hfsplus_attr_exists(inode, name)) अणु
		अगर (flags & XATTR_CREATE) अणु
			pr_err("xattr exists yet\n");
			err = -EOPNOTSUPP;
			जाओ end_setxattr;
		पूर्ण
		err = hfsplus_delete_attr(inode, name);
		अगर (err)
			जाओ end_setxattr;
		err = hfsplus_create_attr(inode, name, value, size);
		अगर (err)
			जाओ end_setxattr;
	पूर्ण अन्यथा अणु
		अगर (flags & XATTR_REPLACE) अणु
			pr_err("cannot replace xattr\n");
			err = -EOPNOTSUPP;
			जाओ end_setxattr;
		पूर्ण
		err = hfsplus_create_attr(inode, name, value, size);
		अगर (err)
			जाओ end_setxattr;
	पूर्ण

	cat_entry_type = hfs_bnode_पढ़ो_u16(cat_fd.bnode, cat_fd.entryoffset);
	अगर (cat_entry_type == HFSPLUS_FOLDER) अणु
		cat_entry_flags = hfs_bnode_पढ़ो_u16(cat_fd.bnode,
				    cat_fd.entryoffset +
				    दुरत्व(काष्ठा hfsplus_cat_folder, flags));
		cat_entry_flags |= HFSPLUS_XATTR_EXISTS;
		अगर (!म_भेद_xattr_acl(name))
			cat_entry_flags |= HFSPLUS_ACL_EXISTS;
		hfs_bnode_ग_लिखो_u16(cat_fd.bnode, cat_fd.entryoffset +
				दुरत्व(काष्ठा hfsplus_cat_folder, flags),
				cat_entry_flags);
		hfsplus_mark_inode_dirty(inode, HFSPLUS_I_CAT_सूचीTY);
	पूर्ण अन्यथा अगर (cat_entry_type == HFSPLUS_खाता) अणु
		cat_entry_flags = hfs_bnode_पढ़ो_u16(cat_fd.bnode,
				    cat_fd.entryoffset +
				    दुरत्व(काष्ठा hfsplus_cat_file, flags));
		cat_entry_flags |= HFSPLUS_XATTR_EXISTS;
		अगर (!म_भेद_xattr_acl(name))
			cat_entry_flags |= HFSPLUS_ACL_EXISTS;
		hfs_bnode_ग_लिखो_u16(cat_fd.bnode, cat_fd.entryoffset +
				    दुरत्व(काष्ठा hfsplus_cat_file, flags),
				    cat_entry_flags);
		hfsplus_mark_inode_dirty(inode, HFSPLUS_I_CAT_सूचीTY);
	पूर्ण अन्यथा अणु
		pr_err("invalid catalog entry type\n");
		err = -EIO;
		जाओ end_setxattr;
	पूर्ण

end_setxattr:
	hfs_find_निकास(&cat_fd);
	वापस err;
पूर्ण

अटल पूर्णांक name_len(स्थिर अक्षर *xattr_name, पूर्णांक xattr_name_len)
अणु
	पूर्णांक len = xattr_name_len + 1;

	अगर (!is_known_namespace(xattr_name))
		len += XATTR_MAC_OSX_PREFIX_LEN;

	वापस len;
पूर्ण

अटल पूर्णांक copy_name(अक्षर *buffer, स्थिर अक्षर *xattr_name, पूर्णांक name_len)
अणु
	पूर्णांक len = name_len;
	पूर्णांक offset = 0;

	अगर (!is_known_namespace(xattr_name)) अणु
		स_नकल(buffer, XATTR_MAC_OSX_PREFIX, XATTR_MAC_OSX_PREFIX_LEN);
		offset += XATTR_MAC_OSX_PREFIX_LEN;
		len += XATTR_MAC_OSX_PREFIX_LEN;
	पूर्ण

	म_नकलन(buffer + offset, xattr_name, name_len);
	स_रखो(buffer + offset + name_len, 0, 1);
	len += 1;

	वापस len;
पूर्ण

पूर्णांक hfsplus_setxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
		     स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags,
		     स्थिर अक्षर *prefix, माप_प्रकार prefixlen)
अणु
	अक्षर *xattr_name;
	पूर्णांक res;

	xattr_name = kदो_स्मृति(NLS_MAX_CHARSET_SIZE * HFSPLUS_ATTR_MAX_STRLEN + 1,
		GFP_KERNEL);
	अगर (!xattr_name)
		वापस -ENOMEM;
	म_नकल(xattr_name, prefix);
	म_नकल(xattr_name + prefixlen, name);
	res = __hfsplus_setxattr(inode, xattr_name, value, size, flags);
	kमुक्त(xattr_name);
	वापस res;
पूर्ण

अटल sमाप_प्रकार hfsplus_getxattr_finder_info(काष्ठा inode *inode,
						व्योम *value, माप_प्रकार size)
अणु
	sमाप_प्रकार res = 0;
	काष्ठा hfs_find_data fd;
	u16 entry_type;
	u16 folder_rec_len = माप(काष्ठा DInfo) + माप(काष्ठा DXInfo);
	u16 file_rec_len = माप(काष्ठा FInfo) + माप(काष्ठा FXInfo);
	u16 record_len = max(folder_rec_len, file_rec_len);
	u8 folder_finder_info[माप(काष्ठा DInfo) + माप(काष्ठा DXInfo)];
	u8 file_finder_info[माप(काष्ठा FInfo) + माप(काष्ठा FXInfo)];

	अगर (size >= record_len) अणु
		res = hfs_find_init(HFSPLUS_SB(inode->i_sb)->cat_tree, &fd);
		अगर (res) अणु
			pr_err("can't init xattr find struct\n");
			वापस res;
		पूर्ण
		res = hfsplus_find_cat(inode->i_sb, inode->i_ino, &fd);
		अगर (res)
			जाओ end_getxattr_finder_info;
		entry_type = hfs_bnode_पढ़ो_u16(fd.bnode, fd.entryoffset);

		अगर (entry_type == HFSPLUS_FOLDER) अणु
			hfs_bnode_पढ़ो(fd.bnode, folder_finder_info,
				fd.entryoffset +
				दुरत्व(काष्ठा hfsplus_cat_folder, user_info),
				folder_rec_len);
			स_नकल(value, folder_finder_info, folder_rec_len);
			res = folder_rec_len;
		पूर्ण अन्यथा अगर (entry_type == HFSPLUS_खाता) अणु
			hfs_bnode_पढ़ो(fd.bnode, file_finder_info,
				fd.entryoffset +
				दुरत्व(काष्ठा hfsplus_cat_file, user_info),
				file_rec_len);
			स_नकल(value, file_finder_info, file_rec_len);
			res = file_rec_len;
		पूर्ण अन्यथा अणु
			res = -EOPNOTSUPP;
			जाओ end_getxattr_finder_info;
		पूर्ण
	पूर्ण अन्यथा
		res = size ? -दुस्फल : record_len;

end_getxattr_finder_info:
	अगर (size >= record_len)
		hfs_find_निकास(&fd);
	वापस res;
पूर्ण

sमाप_प्रकार __hfsplus_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			 व्योम *value, माप_प्रकार size)
अणु
	काष्ठा hfs_find_data fd;
	hfsplus_attr_entry *entry;
	__be32 xattr_record_type;
	u32 record_type;
	u16 record_length = 0;
	sमाप_प्रकार res = 0;

	अगर ((!S_ISREG(inode->i_mode) &&
			!S_ISसूची(inode->i_mode)) ||
				HFSPLUS_IS_RSRC(inode))
		वापस -EOPNOTSUPP;

	अगर (!म_भेद_xattr_finder_info(name))
		वापस hfsplus_getxattr_finder_info(inode, value, size);

	अगर (!HFSPLUS_SB(inode->i_sb)->attr_tree)
		वापस -EOPNOTSUPP;

	entry = hfsplus_alloc_attr_entry();
	अगर (!entry) अणु
		pr_err("can't allocate xattr entry\n");
		वापस -ENOMEM;
	पूर्ण

	res = hfs_find_init(HFSPLUS_SB(inode->i_sb)->attr_tree, &fd);
	अगर (res) अणु
		pr_err("can't init xattr find struct\n");
		जाओ failed_getxattr_init;
	पूर्ण

	res = hfsplus_find_attr(inode->i_sb, inode->i_ino, name, &fd);
	अगर (res) अणु
		अगर (res == -ENOENT)
			res = -ENODATA;
		अन्यथा
			pr_err("xattr searching failed\n");
		जाओ out;
	पूर्ण

	hfs_bnode_पढ़ो(fd.bnode, &xattr_record_type,
			fd.entryoffset, माप(xattr_record_type));
	record_type = be32_to_cpu(xattr_record_type);
	अगर (record_type == HFSPLUS_ATTR_INLINE_DATA) अणु
		record_length = hfs_bnode_पढ़ो_u16(fd.bnode,
				fd.entryoffset +
				दुरत्व(काष्ठा hfsplus_attr_अंतरभूत_data,
				length));
		अगर (record_length > HFSPLUS_MAX_INLINE_DATA_SIZE) अणु
			pr_err("invalid xattr record size\n");
			res = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (record_type == HFSPLUS_ATTR_FORK_DATA ||
			record_type == HFSPLUS_ATTR_EXTENTS) अणु
		pr_err("only inline data xattr are supported\n");
		res = -EOPNOTSUPP;
		जाओ out;
	पूर्ण अन्यथा अणु
		pr_err("invalid xattr record\n");
		res = -EIO;
		जाओ out;
	पूर्ण

	अगर (size) अणु
		hfs_bnode_पढ़ो(fd.bnode, entry, fd.entryoffset,
				दुरत्व(काष्ठा hfsplus_attr_अंतरभूत_data,
					raw_bytes) + record_length);
	पूर्ण

	अगर (size >= record_length) अणु
		स_नकल(value, entry->अंतरभूत_data.raw_bytes, record_length);
		res = record_length;
	पूर्ण अन्यथा
		res = size ? -दुस्फल : record_length;

out:
	hfs_find_निकास(&fd);

failed_getxattr_init:
	hfsplus_destroy_attr_entry(entry);
	वापस res;
पूर्ण

sमाप_प्रकार hfsplus_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			 व्योम *value, माप_प्रकार size,
			 स्थिर अक्षर *prefix, माप_प्रकार prefixlen)
अणु
	पूर्णांक res;
	अक्षर *xattr_name;

	xattr_name = kदो_स्मृति(NLS_MAX_CHARSET_SIZE * HFSPLUS_ATTR_MAX_STRLEN + 1,
			     GFP_KERNEL);
	अगर (!xattr_name)
		वापस -ENOMEM;

	म_नकल(xattr_name, prefix);
	म_नकल(xattr_name + prefixlen, name);

	res = __hfsplus_getxattr(inode, xattr_name, value, size);
	kमुक्त(xattr_name);
	वापस res;

पूर्ण

अटल अंतरभूत पूर्णांक can_list(स्थिर अक्षर *xattr_name)
अणु
	अगर (!xattr_name)
		वापस 0;

	वापस म_भेदन(xattr_name, XATTR_TRUSTED_PREFIX,
			XATTR_TRUSTED_PREFIX_LEN) ||
				capable(CAP_SYS_ADMIN);
पूर्ण

अटल sमाप_प्रकार hfsplus_listxattr_finder_info(काष्ठा dentry *dentry,
						अक्षर *buffer, माप_प्रकार size)
अणु
	sमाप_प्रकार res = 0;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा hfs_find_data fd;
	u16 entry_type;
	u8 folder_finder_info[माप(काष्ठा DInfo) + माप(काष्ठा DXInfo)];
	u8 file_finder_info[माप(काष्ठा FInfo) + माप(काष्ठा FXInfo)];
	अचिन्हित दीर्घ len, found_bit;
	पूर्णांक xattr_name_len, symbols_count;

	res = hfs_find_init(HFSPLUS_SB(inode->i_sb)->cat_tree, &fd);
	अगर (res) अणु
		pr_err("can't init xattr find struct\n");
		वापस res;
	पूर्ण

	res = hfsplus_find_cat(inode->i_sb, inode->i_ino, &fd);
	अगर (res)
		जाओ end_listxattr_finder_info;

	entry_type = hfs_bnode_पढ़ो_u16(fd.bnode, fd.entryoffset);
	अगर (entry_type == HFSPLUS_FOLDER) अणु
		len = माप(काष्ठा DInfo) + माप(काष्ठा DXInfo);
		hfs_bnode_पढ़ो(fd.bnode, folder_finder_info,
				fd.entryoffset +
				दुरत्व(काष्ठा hfsplus_cat_folder, user_info),
				len);
		found_bit = find_first_bit((व्योम *)folder_finder_info, len*8);
	पूर्ण अन्यथा अगर (entry_type == HFSPLUS_खाता) अणु
		len = माप(काष्ठा FInfo) + माप(काष्ठा FXInfo);
		hfs_bnode_पढ़ो(fd.bnode, file_finder_info,
				fd.entryoffset +
				दुरत्व(काष्ठा hfsplus_cat_file, user_info),
				len);
		found_bit = find_first_bit((व्योम *)file_finder_info, len*8);
	पूर्ण अन्यथा अणु
		res = -EOPNOTSUPP;
		जाओ end_listxattr_finder_info;
	पूर्ण

	अगर (found_bit >= (len*8))
		res = 0;
	अन्यथा अणु
		symbols_count = माप(HFSPLUS_XATTR_FINDER_INFO_NAME) - 1;
		xattr_name_len =
			name_len(HFSPLUS_XATTR_FINDER_INFO_NAME, symbols_count);
		अगर (!buffer || !size) अणु
			अगर (can_list(HFSPLUS_XATTR_FINDER_INFO_NAME))
				res = xattr_name_len;
		पूर्ण अन्यथा अगर (can_list(HFSPLUS_XATTR_FINDER_INFO_NAME)) अणु
			अगर (size < xattr_name_len)
				res = -दुस्फल;
			अन्यथा अणु
				res = copy_name(buffer,
						HFSPLUS_XATTR_FINDER_INFO_NAME,
						symbols_count);
			पूर्ण
		पूर्ण
	पूर्ण

end_listxattr_finder_info:
	hfs_find_निकास(&fd);

	वापस res;
पूर्ण

sमाप_प्रकार hfsplus_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार size)
अणु
	sमाप_प्रकार err;
	sमाप_प्रकार res = 0;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा hfs_find_data fd;
	u16 key_len = 0;
	काष्ठा hfsplus_attr_key attr_key;
	अक्षर *strbuf;
	पूर्णांक xattr_name_len;

	अगर ((!S_ISREG(inode->i_mode) &&
			!S_ISसूची(inode->i_mode)) ||
				HFSPLUS_IS_RSRC(inode))
		वापस -EOPNOTSUPP;

	res = hfsplus_listxattr_finder_info(dentry, buffer, size);
	अगर (res < 0)
		वापस res;
	अन्यथा अगर (!HFSPLUS_SB(inode->i_sb)->attr_tree)
		वापस (res == 0) ? -EOPNOTSUPP : res;

	err = hfs_find_init(HFSPLUS_SB(inode->i_sb)->attr_tree, &fd);
	अगर (err) अणु
		pr_err("can't init xattr find struct\n");
		वापस err;
	पूर्ण

	strbuf = kदो_स्मृति(NLS_MAX_CHARSET_SIZE * HFSPLUS_ATTR_MAX_STRLEN +
			XATTR_MAC_OSX_PREFIX_LEN + 1, GFP_KERNEL);
	अगर (!strbuf) अणु
		res = -ENOMEM;
		जाओ out;
	पूर्ण

	err = hfsplus_find_attr(inode->i_sb, inode->i_ino, शून्य, &fd);
	अगर (err) अणु
		अगर (err == -ENOENT) अणु
			अगर (res == 0)
				res = -ENODATA;
			जाओ end_listxattr;
		पूर्ण अन्यथा अणु
			res = err;
			जाओ end_listxattr;
		पूर्ण
	पूर्ण

	क्रम (;;) अणु
		key_len = hfs_bnode_पढ़ो_u16(fd.bnode, fd.keyoffset);
		अगर (key_len == 0 || key_len > fd.tree->max_key_len) अणु
			pr_err("invalid xattr key length: %d\n", key_len);
			res = -EIO;
			जाओ end_listxattr;
		पूर्ण

		hfs_bnode_पढ़ो(fd.bnode, &attr_key,
				fd.keyoffset, key_len + माप(key_len));

		अगर (be32_to_cpu(attr_key.cnid) != inode->i_ino)
			जाओ end_listxattr;

		xattr_name_len = NLS_MAX_CHARSET_SIZE * HFSPLUS_ATTR_MAX_STRLEN;
		अगर (hfsplus_uni2asc(inode->i_sb,
			(स्थिर काष्ठा hfsplus_unistr *)&fd.key->attr.key_name,
					strbuf, &xattr_name_len)) अणु
			pr_err("unicode conversion failed\n");
			res = -EIO;
			जाओ end_listxattr;
		पूर्ण

		अगर (!buffer || !size) अणु
			अगर (can_list(strbuf))
				res += name_len(strbuf, xattr_name_len);
		पूर्ण अन्यथा अगर (can_list(strbuf)) अणु
			अगर (size < (res + name_len(strbuf, xattr_name_len))) अणु
				res = -दुस्फल;
				जाओ end_listxattr;
			पूर्ण अन्यथा
				res += copy_name(buffer + res,
						strbuf, xattr_name_len);
		पूर्ण

		अगर (hfs_brec_जाओ(&fd, 1))
			जाओ end_listxattr;
	पूर्ण

end_listxattr:
	kमुक्त(strbuf);
out:
	hfs_find_निकास(&fd);
	वापस res;
पूर्ण

अटल पूर्णांक hfsplus_हटाओxattr(काष्ठा inode *inode, स्थिर अक्षर *name)
अणु
	पूर्णांक err = 0;
	काष्ठा hfs_find_data cat_fd;
	u16 flags;
	u16 cat_entry_type;
	पूर्णांक is_xattr_acl_deleted = 0;
	पूर्णांक is_all_xattrs_deleted = 0;

	अगर (!HFSPLUS_SB(inode->i_sb)->attr_tree)
		वापस -EOPNOTSUPP;

	अगर (!म_भेद_xattr_finder_info(name))
		वापस -EOPNOTSUPP;

	err = hfs_find_init(HFSPLUS_SB(inode->i_sb)->cat_tree, &cat_fd);
	अगर (err) अणु
		pr_err("can't init xattr find struct\n");
		वापस err;
	पूर्ण

	err = hfsplus_find_cat(inode->i_sb, inode->i_ino, &cat_fd);
	अगर (err) अणु
		pr_err("catalog searching failed\n");
		जाओ end_हटाओxattr;
	पूर्ण

	err = hfsplus_delete_attr(inode, name);
	अगर (err)
		जाओ end_हटाओxattr;

	is_xattr_acl_deleted = !म_भेद_xattr_acl(name);
	is_all_xattrs_deleted = !hfsplus_attr_exists(inode, शून्य);

	अगर (!is_xattr_acl_deleted && !is_all_xattrs_deleted)
		जाओ end_हटाओxattr;

	cat_entry_type = hfs_bnode_पढ़ो_u16(cat_fd.bnode, cat_fd.entryoffset);

	अगर (cat_entry_type == HFSPLUS_FOLDER) अणु
		flags = hfs_bnode_पढ़ो_u16(cat_fd.bnode, cat_fd.entryoffset +
				दुरत्व(काष्ठा hfsplus_cat_folder, flags));
		अगर (is_xattr_acl_deleted)
			flags &= ~HFSPLUS_ACL_EXISTS;
		अगर (is_all_xattrs_deleted)
			flags &= ~HFSPLUS_XATTR_EXISTS;
		hfs_bnode_ग_लिखो_u16(cat_fd.bnode, cat_fd.entryoffset +
				दुरत्व(काष्ठा hfsplus_cat_folder, flags),
				flags);
		hfsplus_mark_inode_dirty(inode, HFSPLUS_I_CAT_सूचीTY);
	पूर्ण अन्यथा अगर (cat_entry_type == HFSPLUS_खाता) अणु
		flags = hfs_bnode_पढ़ो_u16(cat_fd.bnode, cat_fd.entryoffset +
				दुरत्व(काष्ठा hfsplus_cat_file, flags));
		अगर (is_xattr_acl_deleted)
			flags &= ~HFSPLUS_ACL_EXISTS;
		अगर (is_all_xattrs_deleted)
			flags &= ~HFSPLUS_XATTR_EXISTS;
		hfs_bnode_ग_लिखो_u16(cat_fd.bnode, cat_fd.entryoffset +
				दुरत्व(काष्ठा hfsplus_cat_file, flags),
				flags);
		hfsplus_mark_inode_dirty(inode, HFSPLUS_I_CAT_सूचीTY);
	पूर्ण अन्यथा अणु
		pr_err("invalid catalog entry type\n");
		err = -EIO;
		जाओ end_हटाओxattr;
	पूर्ण

end_हटाओxattr:
	hfs_find_निकास(&cat_fd);
	वापस err;
पूर्ण

अटल पूर्णांक hfsplus_osx_getxattr(स्थिर काष्ठा xattr_handler *handler,
				काष्ठा dentry *unused, काष्ठा inode *inode,
				स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	/*
	 * Don't allow retrieving properly prefixed attributes
	 * by prepending them with "osx."
	 */
	अगर (is_known_namespace(name))
		वापस -EOPNOTSUPP;

	/*
	 * osx is the namespace we use to indicate an unprefixed
	 * attribute on the fileप्रणाली (like the ones that OS X
	 * creates), so we pass the name through unmodअगरied (after
	 * ensuring it करोesn't conflict with another namespace).
	 */
	वापस __hfsplus_getxattr(inode, name, buffer, size);
पूर्ण

अटल पूर्णांक hfsplus_osx_setxattr(स्थिर काष्ठा xattr_handler *handler,
				काष्ठा user_namespace *mnt_userns,
				काष्ठा dentry *unused, काष्ठा inode *inode,
				स्थिर अक्षर *name, स्थिर व्योम *buffer,
				माप_प्रकार size, पूर्णांक flags)
अणु
	/*
	 * Don't allow setting properly prefixed attributes
	 * by prepending them with "osx."
	 */
	अगर (is_known_namespace(name))
		वापस -EOPNOTSUPP;

	/*
	 * osx is the namespace we use to indicate an unprefixed
	 * attribute on the fileप्रणाली (like the ones that OS X
	 * creates), so we pass the name through unmodअगरied (after
	 * ensuring it करोesn't conflict with another namespace).
	 */
	वापस __hfsplus_setxattr(inode, name, buffer, size, flags);
पूर्ण

स्थिर काष्ठा xattr_handler hfsplus_xattr_osx_handler = अणु
	.prefix	= XATTR_MAC_OSX_PREFIX,
	.get	= hfsplus_osx_getxattr,
	.set	= hfsplus_osx_setxattr,
पूर्ण;
