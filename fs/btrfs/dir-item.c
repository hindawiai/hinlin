<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"

/*
 * insert a name पूर्णांकo a directory, करोing overflow properly अगर there is a hash
 * collision.  data_size indicates how big the item inserted should be.  On
 * success a काष्ठा btrfs_dir_item poपूर्णांकer is वापसed, otherwise it is
 * an ERR_PTR.
 *
 * The name is not copied पूर्णांकo the dir item, you have to करो that yourself.
 */
अटल काष्ठा btrfs_dir_item *insert_with_overflow(काष्ठा btrfs_trans_handle
						   *trans,
						   काष्ठा btrfs_root *root,
						   काष्ठा btrfs_path *path,
						   काष्ठा btrfs_key *cpu_key,
						   u32 data_size,
						   स्थिर अक्षर *name,
						   पूर्णांक name_len)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक ret;
	अक्षर *ptr;
	काष्ठा btrfs_item *item;
	काष्ठा extent_buffer *leaf;

	ret = btrfs_insert_empty_item(trans, root, path, cpu_key, data_size);
	अगर (ret == -EEXIST) अणु
		काष्ठा btrfs_dir_item *di;
		di = btrfs_match_dir_item_name(fs_info, path, name, name_len);
		अगर (di)
			वापस ERR_PTR(-EEXIST);
		btrfs_extend_item(path, data_size);
	पूर्ण अन्यथा अगर (ret < 0)
		वापस ERR_PTR(ret);
	WARN_ON(ret > 0);
	leaf = path->nodes[0];
	item = btrfs_item_nr(path->slots[0]);
	ptr = btrfs_item_ptr(leaf, path->slots[0], अक्षर);
	BUG_ON(data_size > btrfs_item_size(leaf, item));
	ptr += btrfs_item_size(leaf, item) - data_size;
	वापस (काष्ठा btrfs_dir_item *)ptr;
पूर्ण

/*
 * xattrs work a lot like directories, this inserts an xattr item
 * पूर्णांकo the tree
 */
पूर्णांक btrfs_insert_xattr_item(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_root *root,
			    काष्ठा btrfs_path *path, u64 objectid,
			    स्थिर अक्षर *name, u16 name_len,
			    स्थिर व्योम *data, u16 data_len)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_dir_item *dir_item;
	अचिन्हित दीर्घ name_ptr, data_ptr;
	काष्ठा btrfs_key key, location;
	काष्ठा btrfs_disk_key disk_key;
	काष्ठा extent_buffer *leaf;
	u32 data_size;

	अगर (name_len + data_len > BTRFS_MAX_XATTR_SIZE(root->fs_info))
		वापस -ENOSPC;

	key.objectid = objectid;
	key.type = BTRFS_XATTR_ITEM_KEY;
	key.offset = btrfs_name_hash(name, name_len);

	data_size = माप(*dir_item) + name_len + data_len;
	dir_item = insert_with_overflow(trans, root, path, &key, data_size,
					name, name_len);
	अगर (IS_ERR(dir_item))
		वापस PTR_ERR(dir_item);
	स_रखो(&location, 0, माप(location));

	leaf = path->nodes[0];
	btrfs_cpu_key_to_disk(&disk_key, &location);
	btrfs_set_dir_item_key(leaf, dir_item, &disk_key);
	btrfs_set_dir_type(leaf, dir_item, BTRFS_FT_XATTR);
	btrfs_set_dir_name_len(leaf, dir_item, name_len);
	btrfs_set_dir_transid(leaf, dir_item, trans->transid);
	btrfs_set_dir_data_len(leaf, dir_item, data_len);
	name_ptr = (अचिन्हित दीर्घ)(dir_item + 1);
	data_ptr = (अचिन्हित दीर्घ)((अक्षर *)name_ptr + name_len);

	ग_लिखो_extent_buffer(leaf, name, name_ptr, name_len);
	ग_लिखो_extent_buffer(leaf, data, data_ptr, data_len);
	btrfs_mark_buffer_dirty(path->nodes[0]);

	वापस ret;
पूर्ण

/*
 * insert a directory item in the tree, करोing all the magic क्रम
 * both indexes. 'dir' indicates which objectid to insert it पूर्णांकo,
 * 'location' is the key to stuff into the directory item, 'type' is the
 * type of the inode we're pointing to, and 'index' is the sequence number
 * to use क्रम the second index (अगर one is created).
 * Will वापस 0 or -ENOMEM
 */
पूर्णांक btrfs_insert_dir_item(काष्ठा btrfs_trans_handle *trans, स्थिर अक्षर *name,
			  पूर्णांक name_len, काष्ठा btrfs_inode *dir,
			  काष्ठा btrfs_key *location, u8 type, u64 index)
अणु
	पूर्णांक ret = 0;
	पूर्णांक ret2 = 0;
	काष्ठा btrfs_root *root = dir->root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_dir_item *dir_item;
	काष्ठा extent_buffer *leaf;
	अचिन्हित दीर्घ name_ptr;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_disk_key disk_key;
	u32 data_size;

	key.objectid = btrfs_ino(dir);
	key.type = BTRFS_सूची_ITEM_KEY;
	key.offset = btrfs_name_hash(name, name_len);

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	btrfs_cpu_key_to_disk(&disk_key, location);

	data_size = माप(*dir_item) + name_len;
	dir_item = insert_with_overflow(trans, root, path, &key, data_size,
					name, name_len);
	अगर (IS_ERR(dir_item)) अणु
		ret = PTR_ERR(dir_item);
		अगर (ret == -EEXIST)
			जाओ second_insert;
		जाओ out_मुक्त;
	पूर्ण

	leaf = path->nodes[0];
	btrfs_set_dir_item_key(leaf, dir_item, &disk_key);
	btrfs_set_dir_type(leaf, dir_item, type);
	btrfs_set_dir_data_len(leaf, dir_item, 0);
	btrfs_set_dir_name_len(leaf, dir_item, name_len);
	btrfs_set_dir_transid(leaf, dir_item, trans->transid);
	name_ptr = (अचिन्हित दीर्घ)(dir_item + 1);

	ग_लिखो_extent_buffer(leaf, name, name_ptr, name_len);
	btrfs_mark_buffer_dirty(leaf);

second_insert:
	/* FIXME, use some real flag क्रम selecting the extra index */
	अगर (root == root->fs_info->tree_root) अणु
		ret = 0;
		जाओ out_मुक्त;
	पूर्ण
	btrfs_release_path(path);

	ret2 = btrfs_insert_delayed_dir_index(trans, name, name_len, dir,
					      &disk_key, type, index);
out_मुक्त:
	btrfs_मुक्त_path(path);
	अगर (ret)
		वापस ret;
	अगर (ret2)
		वापस ret2;
	वापस 0;
पूर्ण

/*
 * lookup a directory item based on name.  'dir' is the objectid
 * we're searching in, and 'mod' tells us अगर you plan on deleting the
 * item (use mod < 0) or changing the options (use mod > 0)
 */
काष्ठा btrfs_dir_item *btrfs_lookup_dir_item(काष्ठा btrfs_trans_handle *trans,
					     काष्ठा btrfs_root *root,
					     काष्ठा btrfs_path *path, u64 dir,
					     स्थिर अक्षर *name, पूर्णांक name_len,
					     पूर्णांक mod)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	पूर्णांक ins_len = mod < 0 ? -1 : 0;
	पूर्णांक cow = mod != 0;

	key.objectid = dir;
	key.type = BTRFS_सूची_ITEM_KEY;

	key.offset = btrfs_name_hash(name, name_len);

	ret = btrfs_search_slot(trans, root, &key, path, ins_len, cow);
	अगर (ret < 0)
		वापस ERR_PTR(ret);
	अगर (ret > 0)
		वापस शून्य;

	वापस btrfs_match_dir_item_name(root->fs_info, path, name, name_len);
पूर्ण

पूर्णांक btrfs_check_dir_item_collision(काष्ठा btrfs_root *root, u64 dir,
				   स्थिर अक्षर *name, पूर्णांक name_len)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_dir_item *di;
	पूर्णांक data_size;
	काष्ठा extent_buffer *leaf;
	पूर्णांक slot;
	काष्ठा btrfs_path *path;


	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = dir;
	key.type = BTRFS_सूची_ITEM_KEY;
	key.offset = btrfs_name_hash(name, name_len);

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);

	/* वापस back any errors */
	अगर (ret < 0)
		जाओ out;

	/* nothing found, we're safe */
	अगर (ret > 0) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/* we found an item, look क्रम our name in the item */
	di = btrfs_match_dir_item_name(root->fs_info, path, name, name_len);
	अगर (di) अणु
		/* our exact name was found */
		ret = -EEXIST;
		जाओ out;
	पूर्ण

	/*
	 * see अगर there is room in the item to insert this
	 * name
	 */
	data_size = माप(*di) + name_len;
	leaf = path->nodes[0];
	slot = path->slots[0];
	अगर (data_size + btrfs_item_size_nr(leaf, slot) +
	    माप(काष्ठा btrfs_item) > BTRFS_LEAF_DATA_SIZE(root->fs_info)) अणु
		ret = -EOVERFLOW;
	पूर्ण अन्यथा अणु
		/* plenty of insertion room */
		ret = 0;
	पूर्ण
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * lookup a directory item based on index.  'dir' is the objectid
 * we're searching in, and 'mod' tells us अगर you plan on deleting the
 * item (use mod < 0) or changing the options (use mod > 0)
 *
 * The name is used to make sure the index really poपूर्णांकs to the name you were
 * looking क्रम.
 */
काष्ठा btrfs_dir_item *
btrfs_lookup_dir_index_item(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_root *root,
			    काष्ठा btrfs_path *path, u64 dir,
			    u64 objectid, स्थिर अक्षर *name, पूर्णांक name_len,
			    पूर्णांक mod)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	पूर्णांक ins_len = mod < 0 ? -1 : 0;
	पूर्णांक cow = mod != 0;

	key.objectid = dir;
	key.type = BTRFS_सूची_INDEX_KEY;
	key.offset = objectid;

	ret = btrfs_search_slot(trans, root, &key, path, ins_len, cow);
	अगर (ret < 0)
		वापस ERR_PTR(ret);
	अगर (ret > 0)
		वापस ERR_PTR(-ENOENT);
	वापस btrfs_match_dir_item_name(root->fs_info, path, name, name_len);
पूर्ण

काष्ठा btrfs_dir_item *
btrfs_search_dir_index_item(काष्ठा btrfs_root *root,
			    काष्ठा btrfs_path *path, u64 dirid,
			    स्थिर अक्षर *name, पूर्णांक name_len)
अणु
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_key key;
	u32 nritems;
	पूर्णांक ret;

	key.objectid = dirid;
	key.type = BTRFS_सूची_INDEX_KEY;
	key.offset = 0;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	leaf = path->nodes[0];
	nritems = btrfs_header_nritems(leaf);

	जबतक (1) अणु
		अगर (path->slots[0] >= nritems) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				वापस ERR_PTR(ret);
			अगर (ret > 0)
				अवरोध;
			leaf = path->nodes[0];
			nritems = btrfs_header_nritems(leaf);
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		अगर (key.objectid != dirid || key.type != BTRFS_सूची_INDEX_KEY)
			अवरोध;

		di = btrfs_match_dir_item_name(root->fs_info, path,
					       name, name_len);
		अगर (di)
			वापस di;

		path->slots[0]++;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा btrfs_dir_item *btrfs_lookup_xattr(काष्ठा btrfs_trans_handle *trans,
					  काष्ठा btrfs_root *root,
					  काष्ठा btrfs_path *path, u64 dir,
					  स्थिर अक्षर *name, u16 name_len,
					  पूर्णांक mod)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	पूर्णांक ins_len = mod < 0 ? -1 : 0;
	पूर्णांक cow = mod != 0;

	key.objectid = dir;
	key.type = BTRFS_XATTR_ITEM_KEY;
	key.offset = btrfs_name_hash(name, name_len);
	ret = btrfs_search_slot(trans, root, &key, path, ins_len, cow);
	अगर (ret < 0)
		वापस ERR_PTR(ret);
	अगर (ret > 0)
		वापस शून्य;

	वापस btrfs_match_dir_item_name(root->fs_info, path, name, name_len);
पूर्ण

/*
 * helper function to look at the directory item poपूर्णांकed to by 'path'
 * this walks through all the entries in a dir item and finds one
 * क्रम a specअगरic name.
 */
काष्ठा btrfs_dir_item *btrfs_match_dir_item_name(काष्ठा btrfs_fs_info *fs_info,
						 काष्ठा btrfs_path *path,
						 स्थिर अक्षर *name, पूर्णांक name_len)
अणु
	काष्ठा btrfs_dir_item *dir_item;
	अचिन्हित दीर्घ name_ptr;
	u32 total_len;
	u32 cur = 0;
	u32 this_len;
	काष्ठा extent_buffer *leaf;

	leaf = path->nodes[0];
	dir_item = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_dir_item);

	total_len = btrfs_item_size_nr(leaf, path->slots[0]);
	जबतक (cur < total_len) अणु
		this_len = माप(*dir_item) +
			btrfs_dir_name_len(leaf, dir_item) +
			btrfs_dir_data_len(leaf, dir_item);
		name_ptr = (अचिन्हित दीर्घ)(dir_item + 1);

		अगर (btrfs_dir_name_len(leaf, dir_item) == name_len &&
		    स_भेद_extent_buffer(leaf, name, name_ptr, name_len) == 0)
			वापस dir_item;

		cur += this_len;
		dir_item = (काष्ठा btrfs_dir_item *)((अक्षर *)dir_item +
						     this_len);
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * given a poपूर्णांकer पूर्णांकo a directory item, delete it.  This
 * handles items that have more than one entry in them.
 */
पूर्णांक btrfs_delete_one_dir_name(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_root *root,
			      काष्ठा btrfs_path *path,
			      काष्ठा btrfs_dir_item *di)
अणु

	काष्ठा extent_buffer *leaf;
	u32 sub_item_len;
	u32 item_len;
	पूर्णांक ret = 0;

	leaf = path->nodes[0];
	sub_item_len = माप(*di) + btrfs_dir_name_len(leaf, di) +
		btrfs_dir_data_len(leaf, di);
	item_len = btrfs_item_size_nr(leaf, path->slots[0]);
	अगर (sub_item_len == item_len) अणु
		ret = btrfs_del_item(trans, root, path);
	पूर्ण अन्यथा अणु
		/* MARKER */
		अचिन्हित दीर्घ ptr = (अचिन्हित दीर्घ)di;
		अचिन्हित दीर्घ start;

		start = btrfs_item_ptr_offset(leaf, path->slots[0]);
		स_हटाओ_extent_buffer(leaf, ptr, ptr + sub_item_len,
			item_len - (ptr + sub_item_len - start));
		btrfs_truncate_item(path, item_len - sub_item_len, 1);
	पूर्ण
	वापस ret;
पूर्ण
