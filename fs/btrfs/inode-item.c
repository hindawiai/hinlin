<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "print-tree.h"

काष्ठा btrfs_inode_ref *btrfs_find_name_in_backref(काष्ठा extent_buffer *leaf,
						   पूर्णांक slot, स्थिर अक्षर *name,
						   पूर्णांक name_len)
अणु
	काष्ठा btrfs_inode_ref *ref;
	अचिन्हित दीर्घ ptr;
	अचिन्हित दीर्घ name_ptr;
	u32 item_size;
	u32 cur_offset = 0;
	पूर्णांक len;

	item_size = btrfs_item_size_nr(leaf, slot);
	ptr = btrfs_item_ptr_offset(leaf, slot);
	जबतक (cur_offset < item_size) अणु
		ref = (काष्ठा btrfs_inode_ref *)(ptr + cur_offset);
		len = btrfs_inode_ref_name_len(leaf, ref);
		name_ptr = (अचिन्हित दीर्घ)(ref + 1);
		cur_offset += len + माप(*ref);
		अगर (len != name_len)
			जारी;
		अगर (स_भेद_extent_buffer(leaf, name, name_ptr, name_len) == 0)
			वापस ref;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा btrfs_inode_extref *btrfs_find_name_in_ext_backref(
		काष्ठा extent_buffer *leaf, पूर्णांक slot, u64 ref_objectid,
		स्थिर अक्षर *name, पूर्णांक name_len)
अणु
	काष्ठा btrfs_inode_extref *extref;
	अचिन्हित दीर्घ ptr;
	अचिन्हित दीर्घ name_ptr;
	u32 item_size;
	u32 cur_offset = 0;
	पूर्णांक ref_name_len;

	item_size = btrfs_item_size_nr(leaf, slot);
	ptr = btrfs_item_ptr_offset(leaf, slot);

	/*
	 * Search all extended backrefs in this item. We're only
	 * looking through any collisions so most of the समय this is
	 * just going to compare against one buffer. If all is well,
	 * we'll वापस success and the inode ref object.
	 */
	जबतक (cur_offset < item_size) अणु
		extref = (काष्ठा btrfs_inode_extref *) (ptr + cur_offset);
		name_ptr = (अचिन्हित दीर्घ)(&extref->name);
		ref_name_len = btrfs_inode_extref_name_len(leaf, extref);

		अगर (ref_name_len == name_len &&
		    btrfs_inode_extref_parent(leaf, extref) == ref_objectid &&
		    (स_भेद_extent_buffer(leaf, name, name_ptr, name_len) == 0))
			वापस extref;

		cur_offset += ref_name_len + माप(*extref);
	पूर्ण
	वापस शून्य;
पूर्ण

/* Returns शून्य अगर no extref found */
काष्ठा btrfs_inode_extref *
btrfs_lookup_inode_extref(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_root *root,
			  काष्ठा btrfs_path *path,
			  स्थिर अक्षर *name, पूर्णांक name_len,
			  u64 inode_objectid, u64 ref_objectid, पूर्णांक ins_len,
			  पूर्णांक cow)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;

	key.objectid = inode_objectid;
	key.type = BTRFS_INODE_EXTREF_KEY;
	key.offset = btrfs_extref_hash(ref_objectid, name, name_len);

	ret = btrfs_search_slot(trans, root, &key, path, ins_len, cow);
	अगर (ret < 0)
		वापस ERR_PTR(ret);
	अगर (ret > 0)
		वापस शून्य;
	वापस btrfs_find_name_in_ext_backref(path->nodes[0], path->slots[0],
					      ref_objectid, name, name_len);

पूर्ण

अटल पूर्णांक btrfs_del_inode_extref(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_root *root,
				  स्थिर अक्षर *name, पूर्णांक name_len,
				  u64 inode_objectid, u64 ref_objectid,
				  u64 *index)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_inode_extref *extref;
	काष्ठा extent_buffer *leaf;
	पूर्णांक ret;
	पूर्णांक del_len = name_len + माप(*extref);
	अचिन्हित दीर्घ ptr;
	अचिन्हित दीर्घ item_start;
	u32 item_size;

	key.objectid = inode_objectid;
	key.type = BTRFS_INODE_EXTREF_KEY;
	key.offset = btrfs_extref_hash(ref_objectid, name, name_len);

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret > 0)
		ret = -ENOENT;
	अगर (ret < 0)
		जाओ out;

	/*
	 * Sanity check - did we find the right item क्रम this name?
	 * This should always succeed so error here will make the FS
	 * पढ़ोonly.
	 */
	extref = btrfs_find_name_in_ext_backref(path->nodes[0], path->slots[0],
						ref_objectid, name, name_len);
	अगर (!extref) अणु
		btrfs_handle_fs_error(root->fs_info, -ENOENT, शून्य);
		ret = -EROFS;
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	item_size = btrfs_item_size_nr(leaf, path->slots[0]);
	अगर (index)
		*index = btrfs_inode_extref_index(leaf, extref);

	अगर (del_len == item_size) अणु
		/*
		 * Common हाल only one ref in the item, हटाओ the
		 * whole item.
		 */
		ret = btrfs_del_item(trans, root, path);
		जाओ out;
	पूर्ण

	ptr = (अचिन्हित दीर्घ)extref;
	item_start = btrfs_item_ptr_offset(leaf, path->slots[0]);

	स_हटाओ_extent_buffer(leaf, ptr, ptr + del_len,
			      item_size - (ptr + del_len - item_start));

	btrfs_truncate_item(path, item_size - del_len, 1);

out:
	btrfs_मुक्त_path(path);

	वापस ret;
पूर्ण

पूर्णांक btrfs_del_inode_ref(काष्ठा btrfs_trans_handle *trans,
			काष्ठा btrfs_root *root,
			स्थिर अक्षर *name, पूर्णांक name_len,
			u64 inode_objectid, u64 ref_objectid, u64 *index)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_inode_ref *ref;
	काष्ठा extent_buffer *leaf;
	अचिन्हित दीर्घ ptr;
	अचिन्हित दीर्घ item_start;
	u32 item_size;
	u32 sub_item_len;
	पूर्णांक ret;
	पूर्णांक search_ext_refs = 0;
	पूर्णांक del_len = name_len + माप(*ref);

	key.objectid = inode_objectid;
	key.offset = ref_objectid;
	key.type = BTRFS_INODE_REF_KEY;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret > 0) अणु
		ret = -ENOENT;
		search_ext_refs = 1;
		जाओ out;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		जाओ out;
	पूर्ण

	ref = btrfs_find_name_in_backref(path->nodes[0], path->slots[0], name,
					 name_len);
	अगर (!ref) अणु
		ret = -ENOENT;
		search_ext_refs = 1;
		जाओ out;
	पूर्ण
	leaf = path->nodes[0];
	item_size = btrfs_item_size_nr(leaf, path->slots[0]);

	अगर (index)
		*index = btrfs_inode_ref_index(leaf, ref);

	अगर (del_len == item_size) अणु
		ret = btrfs_del_item(trans, root, path);
		जाओ out;
	पूर्ण
	ptr = (अचिन्हित दीर्घ)ref;
	sub_item_len = name_len + माप(*ref);
	item_start = btrfs_item_ptr_offset(leaf, path->slots[0]);
	स_हटाओ_extent_buffer(leaf, ptr, ptr + sub_item_len,
			      item_size - (ptr + sub_item_len - item_start));
	btrfs_truncate_item(path, item_size - sub_item_len, 1);
out:
	btrfs_मुक्त_path(path);

	अगर (search_ext_refs) अणु
		/*
		 * No refs were found, or we could not find the
		 * name in our ref array. Find and हटाओ the extended
		 * inode ref then.
		 */
		वापस btrfs_del_inode_extref(trans, root, name, name_len,
					      inode_objectid, ref_objectid, index);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * btrfs_insert_inode_extref() - Inserts an extended inode ref पूर्णांकo a tree.
 *
 * The caller must have checked against BTRFS_LINK_MAX alपढ़ोy.
 */
अटल पूर्णांक btrfs_insert_inode_extref(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_root *root,
				     स्थिर अक्षर *name, पूर्णांक name_len,
				     u64 inode_objectid, u64 ref_objectid, u64 index)
अणु
	काष्ठा btrfs_inode_extref *extref;
	पूर्णांक ret;
	पूर्णांक ins_len = name_len + माप(*extref);
	अचिन्हित दीर्घ ptr;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_item *item;

	key.objectid = inode_objectid;
	key.type = BTRFS_INODE_EXTREF_KEY;
	key.offset = btrfs_extref_hash(ref_objectid, name, name_len);

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_insert_empty_item(trans, root, path, &key,
				      ins_len);
	अगर (ret == -EEXIST) अणु
		अगर (btrfs_find_name_in_ext_backref(path->nodes[0],
						   path->slots[0],
						   ref_objectid,
						   name, name_len))
			जाओ out;

		btrfs_extend_item(path, ins_len);
		ret = 0;
	पूर्ण
	अगर (ret < 0)
		जाओ out;

	leaf = path->nodes[0];
	item = btrfs_item_nr(path->slots[0]);
	ptr = (अचिन्हित दीर्घ)btrfs_item_ptr(leaf, path->slots[0], अक्षर);
	ptr += btrfs_item_size(leaf, item) - ins_len;
	extref = (काष्ठा btrfs_inode_extref *)ptr;

	btrfs_set_inode_extref_name_len(path->nodes[0], extref, name_len);
	btrfs_set_inode_extref_index(path->nodes[0], extref, index);
	btrfs_set_inode_extref_parent(path->nodes[0], extref, ref_objectid);

	ptr = (अचिन्हित दीर्घ)&extref->name;
	ग_लिखो_extent_buffer(path->nodes[0], name, ptr, name_len);
	btrfs_mark_buffer_dirty(path->nodes[0]);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/* Will वापस 0, -ENOMEM, -EMLINK, or -EEXIST or anything from the CoW path */
पूर्णांक btrfs_insert_inode_ref(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root,
			   स्थिर अक्षर *name, पूर्णांक name_len,
			   u64 inode_objectid, u64 ref_objectid, u64 index)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_inode_ref *ref;
	अचिन्हित दीर्घ ptr;
	पूर्णांक ret;
	पूर्णांक ins_len = name_len + माप(*ref);

	key.objectid = inode_objectid;
	key.offset = ref_objectid;
	key.type = BTRFS_INODE_REF_KEY;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	path->skip_release_on_error = 1;
	ret = btrfs_insert_empty_item(trans, root, path, &key,
				      ins_len);
	अगर (ret == -EEXIST) अणु
		u32 old_size;
		ref = btrfs_find_name_in_backref(path->nodes[0], path->slots[0],
						 name, name_len);
		अगर (ref)
			जाओ out;

		old_size = btrfs_item_size_nr(path->nodes[0], path->slots[0]);
		btrfs_extend_item(path, ins_len);
		ref = btrfs_item_ptr(path->nodes[0], path->slots[0],
				     काष्ठा btrfs_inode_ref);
		ref = (काष्ठा btrfs_inode_ref *)((अचिन्हित दीर्घ)ref + old_size);
		btrfs_set_inode_ref_name_len(path->nodes[0], ref, name_len);
		btrfs_set_inode_ref_index(path->nodes[0], ref, index);
		ptr = (अचिन्हित दीर्घ)(ref + 1);
		ret = 0;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		अगर (ret == -EOVERFLOW) अणु
			अगर (btrfs_find_name_in_backref(path->nodes[0],
						       path->slots[0],
						       name, name_len))
				ret = -EEXIST;
			अन्यथा
				ret = -EMLINK;
		पूर्ण
		जाओ out;
	पूर्ण अन्यथा अणु
		ref = btrfs_item_ptr(path->nodes[0], path->slots[0],
				     काष्ठा btrfs_inode_ref);
		btrfs_set_inode_ref_name_len(path->nodes[0], ref, name_len);
		btrfs_set_inode_ref_index(path->nodes[0], ref, index);
		ptr = (अचिन्हित दीर्घ)(ref + 1);
	पूर्ण
	ग_लिखो_extent_buffer(path->nodes[0], name, ptr, name_len);
	btrfs_mark_buffer_dirty(path->nodes[0]);

out:
	btrfs_मुक्त_path(path);

	अगर (ret == -EMLINK) अणु
		काष्ठा btrfs_super_block *disk_super = fs_info->super_copy;
		/* We ran out of space in the ref array. Need to
		 * add an extended ref. */
		अगर (btrfs_super_incompat_flags(disk_super)
		    & BTRFS_FEATURE_INCOMPAT_EXTENDED_IREF)
			ret = btrfs_insert_inode_extref(trans, root, name,
							name_len,
							inode_objectid,
							ref_objectid, index);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक btrfs_insert_empty_inode(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root,
			     काष्ठा btrfs_path *path, u64 objectid)
अणु
	काष्ठा btrfs_key key;
	पूर्णांक ret;
	key.objectid = objectid;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;

	ret = btrfs_insert_empty_item(trans, root, path, &key,
				      माप(काष्ठा btrfs_inode_item));
	वापस ret;
पूर्ण

पूर्णांक btrfs_lookup_inode(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root
		       *root, काष्ठा btrfs_path *path,
		       काष्ठा btrfs_key *location, पूर्णांक mod)
अणु
	पूर्णांक ins_len = mod < 0 ? -1 : 0;
	पूर्णांक cow = mod != 0;
	पूर्णांक ret;
	पूर्णांक slot;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key found_key;

	ret = btrfs_search_slot(trans, root, location, path, ins_len, cow);
	अगर (ret > 0 && location->type == BTRFS_ROOT_ITEM_KEY &&
	    location->offset == (u64)-1 && path->slots[0] != 0) अणु
		slot = path->slots[0] - 1;
		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &found_key, slot);
		अगर (found_key.objectid == location->objectid &&
		    found_key.type == location->type) अणु
			path->slots[0]--;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
