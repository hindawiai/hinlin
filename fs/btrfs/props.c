<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Filipe David Borba Manana <fdmanana@gmail.com>
 */

#समावेश <linux/hashtable.h>
#समावेश "props.h"
#समावेश "btrfs_inode.h"
#समावेश "transaction.h"
#समावेश "ctree.h"
#समावेश "xattr.h"
#समावेश "compression.h"

#घोषणा BTRFS_PROP_HANDLERS_HT_BITS 8
अटल DEFINE_HASHTABLE(prop_handlers_ht, BTRFS_PROP_HANDLERS_HT_BITS);

काष्ठा prop_handler अणु
	काष्ठा hlist_node node;
	स्थिर अक्षर *xattr_name;
	पूर्णांक (*validate)(स्थिर अक्षर *value, माप_प्रकार len);
	पूर्णांक (*apply)(काष्ठा inode *inode, स्थिर अक्षर *value, माप_प्रकार len);
	स्थिर अक्षर *(*extract)(काष्ठा inode *inode);
	पूर्णांक inheritable;
पूर्ण;

अटल स्थिर काष्ठा hlist_head *find_prop_handlers_by_hash(स्थिर u64 hash)
अणु
	काष्ठा hlist_head *h;

	h = &prop_handlers_ht[hash_min(hash, BTRFS_PROP_HANDLERS_HT_BITS)];
	अगर (hlist_empty(h))
		वापस शून्य;

	वापस h;
पूर्ण

अटल स्थिर काष्ठा prop_handler *
find_prop_handler(स्थिर अक्षर *name,
		  स्थिर काष्ठा hlist_head *handlers)
अणु
	काष्ठा prop_handler *h;

	अगर (!handlers) अणु
		u64 hash = btrfs_name_hash(name, म_माप(name));

		handlers = find_prop_handlers_by_hash(hash);
		अगर (!handlers)
			वापस शून्य;
	पूर्ण

	hlist_क्रम_each_entry(h, handlers, node)
		अगर (!म_भेद(h->xattr_name, name))
			वापस h;

	वापस शून्य;
पूर्ण

पूर्णांक btrfs_validate_prop(स्थिर अक्षर *name, स्थिर अक्षर *value, माप_प्रकार value_len)
अणु
	स्थिर काष्ठा prop_handler *handler;

	अगर (म_माप(name) <= XATTR_BTRFS_PREFIX_LEN)
		वापस -EINVAL;

	handler = find_prop_handler(name, शून्य);
	अगर (!handler)
		वापस -EINVAL;

	अगर (value_len == 0)
		वापस 0;

	वापस handler->validate(value, value_len);
पूर्ण

पूर्णांक btrfs_set_prop(काष्ठा btrfs_trans_handle *trans, काष्ठा inode *inode,
		   स्थिर अक्षर *name, स्थिर अक्षर *value, माप_प्रकार value_len,
		   पूर्णांक flags)
अणु
	स्थिर काष्ठा prop_handler *handler;
	पूर्णांक ret;

	handler = find_prop_handler(name, शून्य);
	अगर (!handler)
		वापस -EINVAL;

	अगर (value_len == 0) अणु
		ret = btrfs_setxattr(trans, inode, handler->xattr_name,
				     शून्य, 0, flags);
		अगर (ret)
			वापस ret;

		ret = handler->apply(inode, शून्य, 0);
		ASSERT(ret == 0);

		वापस ret;
	पूर्ण

	ret = btrfs_setxattr(trans, inode, handler->xattr_name, value,
			     value_len, flags);
	अगर (ret)
		वापस ret;
	ret = handler->apply(inode, value, value_len);
	अगर (ret) अणु
		btrfs_setxattr(trans, inode, handler->xattr_name, शून्य,
			       0, flags);
		वापस ret;
	पूर्ण

	set_bit(BTRFS_INODE_HAS_PROPS, &BTRFS_I(inode)->runसमय_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक iterate_object_props(काष्ठा btrfs_root *root,
				काष्ठा btrfs_path *path,
				u64 objectid,
				व्योम (*iterator)(व्योम *,
						 स्थिर काष्ठा prop_handler *,
						 स्थिर अक्षर *,
						 माप_प्रकार),
				व्योम *ctx)
अणु
	पूर्णांक ret;
	अक्षर *name_buf = शून्य;
	अक्षर *value_buf = शून्य;
	पूर्णांक name_buf_len = 0;
	पूर्णांक value_buf_len = 0;

	जबतक (1) अणु
		काष्ठा btrfs_key key;
		काष्ठा btrfs_dir_item *di;
		काष्ठा extent_buffer *leaf;
		u32 total_len, cur, this_len;
		पूर्णांक slot;
		स्थिर काष्ठा hlist_head *handlers;

		slot = path->slots[0];
		leaf = path->nodes[0];

		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ out;
			अन्यथा अगर (ret > 0)
				अवरोध;
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, slot);
		अगर (key.objectid != objectid)
			अवरोध;
		अगर (key.type != BTRFS_XATTR_ITEM_KEY)
			अवरोध;

		handlers = find_prop_handlers_by_hash(key.offset);
		अगर (!handlers)
			जाओ next_slot;

		di = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_dir_item);
		cur = 0;
		total_len = btrfs_item_size_nr(leaf, slot);

		जबतक (cur < total_len) अणु
			u32 name_len = btrfs_dir_name_len(leaf, di);
			u32 data_len = btrfs_dir_data_len(leaf, di);
			अचिन्हित दीर्घ name_ptr, data_ptr;
			स्थिर काष्ठा prop_handler *handler;

			this_len = माप(*di) + name_len + data_len;
			name_ptr = (अचिन्हित दीर्घ)(di + 1);
			data_ptr = name_ptr + name_len;

			अगर (name_len <= XATTR_BTRFS_PREFIX_LEN ||
			    स_भेद_extent_buffer(leaf, XATTR_BTRFS_PREFIX,
						 name_ptr,
						 XATTR_BTRFS_PREFIX_LEN))
				जाओ next_dir_item;

			अगर (name_len >= name_buf_len) अणु
				kमुक्त(name_buf);
				name_buf_len = name_len + 1;
				name_buf = kदो_स्मृति(name_buf_len, GFP_NOFS);
				अगर (!name_buf) अणु
					ret = -ENOMEM;
					जाओ out;
				पूर्ण
			पूर्ण
			पढ़ो_extent_buffer(leaf, name_buf, name_ptr, name_len);
			name_buf[name_len] = '\0';

			handler = find_prop_handler(name_buf, handlers);
			अगर (!handler)
				जाओ next_dir_item;

			अगर (data_len > value_buf_len) अणु
				kमुक्त(value_buf);
				value_buf_len = data_len;
				value_buf = kदो_स्मृति(data_len, GFP_NOFS);
				अगर (!value_buf) अणु
					ret = -ENOMEM;
					जाओ out;
				पूर्ण
			पूर्ण
			पढ़ो_extent_buffer(leaf, value_buf, data_ptr, data_len);

			iterator(ctx, handler, value_buf, data_len);
next_dir_item:
			cur += this_len;
			di = (काष्ठा btrfs_dir_item *)((अक्षर *) di + this_len);
		पूर्ण

next_slot:
		path->slots[0]++;
	पूर्ण

	ret = 0;
out:
	btrfs_release_path(path);
	kमुक्त(name_buf);
	kमुक्त(value_buf);

	वापस ret;
पूर्ण

अटल व्योम inode_prop_iterator(व्योम *ctx,
				स्थिर काष्ठा prop_handler *handler,
				स्थिर अक्षर *value,
				माप_प्रकार len)
अणु
	काष्ठा inode *inode = ctx;
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	पूर्णांक ret;

	ret = handler->apply(inode, value, len);
	अगर (unlikely(ret))
		btrfs_warn(root->fs_info,
			   "error applying prop %s to ino %llu (root %llu): %d",
			   handler->xattr_name, btrfs_ino(BTRFS_I(inode)),
			   root->root_key.objectid, ret);
	अन्यथा
		set_bit(BTRFS_INODE_HAS_PROPS, &BTRFS_I(inode)->runसमय_flags);
पूर्ण

पूर्णांक btrfs_load_inode_props(काष्ठा inode *inode, काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	u64 ino = btrfs_ino(BTRFS_I(inode));
	पूर्णांक ret;

	ret = iterate_object_props(root, path, ino, inode_prop_iterator, inode);

	वापस ret;
पूर्ण

अटल पूर्णांक prop_compression_validate(स्थिर अक्षर *value, माप_प्रकार len)
अणु
	अगर (!value)
		वापस 0;

	अगर (btrfs_compress_is_valid_type(value, len))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक prop_compression_apply(काष्ठा inode *inode, स्थिर अक्षर *value,
				  माप_प्रकार len)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	पूर्णांक type;

	अगर (len == 0) अणु
		BTRFS_I(inode)->flags |= BTRFS_INODE_NOCOMPRESS;
		BTRFS_I(inode)->flags &= ~BTRFS_INODE_COMPRESS;
		BTRFS_I(inode)->prop_compress = BTRFS_COMPRESS_NONE;

		वापस 0;
	पूर्ण

	अगर (!म_भेदन("lzo", value, 3)) अणु
		type = BTRFS_COMPRESS_LZO;
		btrfs_set_fs_incompat(fs_info, COMPRESS_LZO);
	पूर्ण अन्यथा अगर (!म_भेदन("zlib", value, 4)) अणु
		type = BTRFS_COMPRESS_ZLIB;
	पूर्ण अन्यथा अगर (!म_भेदन("zstd", value, 4)) अणु
		type = BTRFS_COMPRESS_ZSTD;
		btrfs_set_fs_incompat(fs_info, COMPRESS_ZSTD);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	BTRFS_I(inode)->flags &= ~BTRFS_INODE_NOCOMPRESS;
	BTRFS_I(inode)->flags |= BTRFS_INODE_COMPRESS;
	BTRFS_I(inode)->prop_compress = type;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *prop_compression_extract(काष्ठा inode *inode)
अणु
	चयन (BTRFS_I(inode)->prop_compress) अणु
	हाल BTRFS_COMPRESS_ZLIB:
	हाल BTRFS_COMPRESS_LZO:
	हाल BTRFS_COMPRESS_ZSTD:
		वापस btrfs_compress_type2str(BTRFS_I(inode)->prop_compress);
	शेष:
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा prop_handler prop_handlers[] = अणु
	अणु
		.xattr_name = XATTR_BTRFS_PREFIX "compression",
		.validate = prop_compression_validate,
		.apply = prop_compression_apply,
		.extract = prop_compression_extract,
		.inheritable = 1
	पूर्ण,
पूर्ण;

अटल पूर्णांक inherit_props(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा inode *inode,
			 काष्ठा inode *parent)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक ret;
	पूर्णांक i;
	bool need_reserve = false;

	अगर (!test_bit(BTRFS_INODE_HAS_PROPS,
		      &BTRFS_I(parent)->runसमय_flags))
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(prop_handlers); i++) अणु
		स्थिर काष्ठा prop_handler *h = &prop_handlers[i];
		स्थिर अक्षर *value;
		u64 num_bytes = 0;

		अगर (!h->inheritable)
			जारी;

		value = h->extract(parent);
		अगर (!value)
			जारी;

		/*
		 * This is not strictly necessary as the property should be
		 * valid, but in हाल it isn't, don't propagate it futher.
		 */
		ret = h->validate(value, म_माप(value));
		अगर (ret)
			जारी;

		/*
		 * Currently callers should be reserving 1 item क्रम properties,
		 * since we only have 1 property that we currently support.  If
		 * we add more in the future we need to try and reserve more
		 * space क्रम them.  But we should also revisit how we करो space
		 * reservations अगर we करो add more properties in the future.
		 */
		अगर (need_reserve) अणु
			num_bytes = btrfs_calc_insert_metadata_size(fs_info, 1);
			ret = btrfs_block_rsv_add(root, trans->block_rsv,
					num_bytes, BTRFS_RESERVE_NO_FLUSH);
			अगर (ret)
				वापस ret;
		पूर्ण

		ret = btrfs_setxattr(trans, inode, h->xattr_name, value,
				     म_माप(value), 0);
		अगर (!ret) अणु
			ret = h->apply(inode, value, म_माप(value));
			अगर (ret)
				btrfs_setxattr(trans, inode, h->xattr_name,
					       शून्य, 0, 0);
			अन्यथा
				set_bit(BTRFS_INODE_HAS_PROPS,
					&BTRFS_I(inode)->runसमय_flags);
		पूर्ण

		अगर (need_reserve) अणु
			btrfs_block_rsv_release(fs_info, trans->block_rsv,
					num_bytes, शून्य);
			अगर (ret)
				वापस ret;
		पूर्ण
		need_reserve = true;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक btrfs_inode_inherit_props(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा inode *inode,
			      काष्ठा inode *dir)
अणु
	अगर (!dir)
		वापस 0;

	वापस inherit_props(trans, inode, dir);
पूर्ण

पूर्णांक btrfs_subvol_inherit_props(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root,
			       काष्ठा btrfs_root *parent_root)
अणु
	काष्ठा super_block *sb = root->fs_info->sb;
	काष्ठा inode *parent_inode, *child_inode;
	पूर्णांक ret;

	parent_inode = btrfs_iget(sb, BTRFS_FIRST_FREE_OBJECTID, parent_root);
	अगर (IS_ERR(parent_inode))
		वापस PTR_ERR(parent_inode);

	child_inode = btrfs_iget(sb, BTRFS_FIRST_FREE_OBJECTID, root);
	अगर (IS_ERR(child_inode)) अणु
		iput(parent_inode);
		वापस PTR_ERR(child_inode);
	पूर्ण

	ret = inherit_props(trans, child_inode, parent_inode);
	iput(child_inode);
	iput(parent_inode);

	वापस ret;
पूर्ण

व्योम __init btrfs_props_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(prop_handlers); i++) अणु
		काष्ठा prop_handler *p = &prop_handlers[i];
		u64 h = btrfs_name_hash(p->xattr_name, म_माप(p->xattr_name));

		hash_add(prop_handlers_ht, &p->node, h);
	पूर्ण
पूर्ण

