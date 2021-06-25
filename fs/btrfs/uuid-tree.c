<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STRATO AG 2013.  All rights reserved.
 */

#समावेश <linux/uuid.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "ctree.h"
#समावेश "transaction.h"
#समावेश "disk-io.h"
#समावेश "print-tree.h"


अटल व्योम btrfs_uuid_to_key(u8 *uuid, u8 type, काष्ठा btrfs_key *key)
अणु
	key->type = type;
	key->objectid = get_unaligned_le64(uuid);
	key->offset = get_unaligned_le64(uuid + माप(u64));
पूर्ण

/* वापस -ENOENT क्रम !found, < 0 क्रम errors, or 0 अगर an item was found */
अटल पूर्णांक btrfs_uuid_tree_lookup(काष्ठा btrfs_root *uuid_root, u8 *uuid,
				  u8 type, u64 subid)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा extent_buffer *eb;
	पूर्णांक slot;
	u32 item_size;
	अचिन्हित दीर्घ offset;
	काष्ठा btrfs_key key;

	अगर (WARN_ON_ONCE(!uuid_root)) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	btrfs_uuid_to_key(uuid, type, &key);
	ret = btrfs_search_slot(शून्य, uuid_root, &key, path, 0, 0);
	अगर (ret < 0) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	eb = path->nodes[0];
	slot = path->slots[0];
	item_size = btrfs_item_size_nr(eb, slot);
	offset = btrfs_item_ptr_offset(eb, slot);
	ret = -ENOENT;

	अगर (!IS_ALIGNED(item_size, माप(u64))) अणु
		btrfs_warn(uuid_root->fs_info,
			   "uuid item with illegal size %lu!",
			   (अचिन्हित दीर्घ)item_size);
		जाओ out;
	पूर्ण
	जबतक (item_size) अणु
		__le64 data;

		पढ़ो_extent_buffer(eb, &data, offset, माप(data));
		अगर (le64_to_cpu(data) == subid) अणु
			ret = 0;
			अवरोध;
		पूर्ण
		offset += माप(data);
		item_size -= माप(data);
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_uuid_tree_add(काष्ठा btrfs_trans_handle *trans, u8 *uuid, u8 type,
			u64 subid_cpu)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *uuid_root = fs_info->uuid_root;
	पूर्णांक ret;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *eb;
	पूर्णांक slot;
	अचिन्हित दीर्घ offset;
	__le64 subid_le;

	ret = btrfs_uuid_tree_lookup(uuid_root, uuid, type, subid_cpu);
	अगर (ret != -ENOENT)
		वापस ret;

	अगर (WARN_ON_ONCE(!uuid_root)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	btrfs_uuid_to_key(uuid, type, &key);

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = btrfs_insert_empty_item(trans, uuid_root, path, &key,
				      माप(subid_le));
	अगर (ret >= 0) अणु
		/* Add an item क्रम the type क्रम the first समय */
		eb = path->nodes[0];
		slot = path->slots[0];
		offset = btrfs_item_ptr_offset(eb, slot);
	पूर्ण अन्यथा अगर (ret == -EEXIST) अणु
		/*
		 * An item with that type alपढ़ोy exists.
		 * Extend the item and store the new subid at the end.
		 */
		btrfs_extend_item(path, माप(subid_le));
		eb = path->nodes[0];
		slot = path->slots[0];
		offset = btrfs_item_ptr_offset(eb, slot);
		offset += btrfs_item_size_nr(eb, slot) - माप(subid_le);
	पूर्ण अन्यथा अणु
		btrfs_warn(fs_info,
			   "insert uuid item failed %d (0x%016llx, 0x%016llx) type %u!",
			   ret, key.objectid, key.offset, type);
		जाओ out;
	पूर्ण

	ret = 0;
	subid_le = cpu_to_le64(subid_cpu);
	ग_लिखो_extent_buffer(eb, &subid_le, offset, माप(subid_le));
	btrfs_mark_buffer_dirty(eb);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_uuid_tree_हटाओ(काष्ठा btrfs_trans_handle *trans, u8 *uuid, u8 type,
			u64 subid)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *uuid_root = fs_info->uuid_root;
	पूर्णांक ret;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *eb;
	पूर्णांक slot;
	अचिन्हित दीर्घ offset;
	u32 item_size;
	अचिन्हित दीर्घ move_dst;
	अचिन्हित दीर्घ move_src;
	अचिन्हित दीर्घ move_len;

	अगर (WARN_ON_ONCE(!uuid_root)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	btrfs_uuid_to_key(uuid, type, &key);

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = btrfs_search_slot(trans, uuid_root, &key, path, -1, 1);
	अगर (ret < 0) अणु
		btrfs_warn(fs_info, "error %d while searching for uuid item!",
			   ret);
		जाओ out;
	पूर्ण
	अगर (ret > 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	eb = path->nodes[0];
	slot = path->slots[0];
	offset = btrfs_item_ptr_offset(eb, slot);
	item_size = btrfs_item_size_nr(eb, slot);
	अगर (!IS_ALIGNED(item_size, माप(u64))) अणु
		btrfs_warn(fs_info, "uuid item with illegal size %lu!",
			   (अचिन्हित दीर्घ)item_size);
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	जबतक (item_size) अणु
		__le64 पढ़ो_subid;

		पढ़ो_extent_buffer(eb, &पढ़ो_subid, offset, माप(पढ़ो_subid));
		अगर (le64_to_cpu(पढ़ो_subid) == subid)
			अवरोध;
		offset += माप(पढ़ो_subid);
		item_size -= माप(पढ़ो_subid);
	पूर्ण

	अगर (!item_size) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	item_size = btrfs_item_size_nr(eb, slot);
	अगर (item_size == माप(subid)) अणु
		ret = btrfs_del_item(trans, uuid_root, path);
		जाओ out;
	पूर्ण

	move_dst = offset;
	move_src = offset + माप(subid);
	move_len = item_size - (move_src - btrfs_item_ptr_offset(eb, slot));
	स_हटाओ_extent_buffer(eb, move_dst, move_src, move_len);
	btrfs_truncate_item(path, item_size - माप(subid), 1);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_uuid_iter_rem(काष्ठा btrfs_root *uuid_root, u8 *uuid, u8 type,
			       u64 subid)
अणु
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret;

	/* 1 - क्रम the uuid item */
	trans = btrfs_start_transaction(uuid_root, 1);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out;
	पूर्ण

	ret = btrfs_uuid_tree_हटाओ(trans, uuid, type, subid);
	btrfs_end_transaction(trans);

out:
	वापस ret;
पूर्ण

/*
 * Check अगर there's an matching subvolume क्रम given UUID
 *
 * Return:
 * 0	check succeeded, the entry is not outdated
 * > 0	अगर the check failed, the caller should हटाओ the entry
 * < 0	अगर an error occurred
 */
अटल पूर्णांक btrfs_check_uuid_tree_entry(काष्ठा btrfs_fs_info *fs_info,
				       u8 *uuid, u8 type, u64 subvolid)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_root *subvol_root;

	अगर (type != BTRFS_UUID_KEY_SUBVOL &&
	    type != BTRFS_UUID_KEY_RECEIVED_SUBVOL)
		जाओ out;

	subvol_root = btrfs_get_fs_root(fs_info, subvolid, true);
	अगर (IS_ERR(subvol_root)) अणु
		ret = PTR_ERR(subvol_root);
		अगर (ret == -ENOENT)
			ret = 1;
		जाओ out;
	पूर्ण

	चयन (type) अणु
	हाल BTRFS_UUID_KEY_SUBVOL:
		अगर (स_भेद(uuid, subvol_root->root_item.uuid, BTRFS_UUID_SIZE))
			ret = 1;
		अवरोध;
	हाल BTRFS_UUID_KEY_RECEIVED_SUBVOL:
		अगर (स_भेद(uuid, subvol_root->root_item.received_uuid,
			   BTRFS_UUID_SIZE))
			ret = 1;
		अवरोध;
	पूर्ण
	btrfs_put_root(subvol_root);
out:
	वापस ret;
पूर्ण

पूर्णांक btrfs_uuid_tree_iterate(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *root = fs_info->uuid_root;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path;
	पूर्णांक ret = 0;
	काष्ठा extent_buffer *leaf;
	पूर्णांक slot;
	u32 item_size;
	अचिन्हित दीर्घ offset;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	key.objectid = 0;
	key.type = 0;
	key.offset = 0;

again_search_slot:
	ret = btrfs_search_क्रमward(root, &key, path, BTRFS_OLDEST_GENERATION);
	अगर (ret) अणु
		अगर (ret > 0)
			ret = 0;
		जाओ out;
	पूर्ण

	जबतक (1) अणु
		अगर (btrfs_fs_closing(fs_info)) अणु
			ret = -EINTR;
			जाओ out;
		पूर्ण
		cond_resched();
		leaf = path->nodes[0];
		slot = path->slots[0];
		btrfs_item_key_to_cpu(leaf, &key, slot);

		अगर (key.type != BTRFS_UUID_KEY_SUBVOL &&
		    key.type != BTRFS_UUID_KEY_RECEIVED_SUBVOL)
			जाओ skip;

		offset = btrfs_item_ptr_offset(leaf, slot);
		item_size = btrfs_item_size_nr(leaf, slot);
		अगर (!IS_ALIGNED(item_size, माप(u64))) अणु
			btrfs_warn(fs_info,
				   "uuid item with illegal size %lu!",
				   (अचिन्हित दीर्घ)item_size);
			जाओ skip;
		पूर्ण
		जबतक (item_size) अणु
			u8 uuid[BTRFS_UUID_SIZE];
			__le64 subid_le;
			u64 subid_cpu;

			put_unaligned_le64(key.objectid, uuid);
			put_unaligned_le64(key.offset, uuid + माप(u64));
			पढ़ो_extent_buffer(leaf, &subid_le, offset,
					   माप(subid_le));
			subid_cpu = le64_to_cpu(subid_le);
			ret = btrfs_check_uuid_tree_entry(fs_info, uuid,
							  key.type, subid_cpu);
			अगर (ret < 0)
				जाओ out;
			अगर (ret > 0) अणु
				btrfs_release_path(path);
				ret = btrfs_uuid_iter_rem(root, uuid, key.type,
							  subid_cpu);
				अगर (ret == 0) अणु
					/*
					 * this might look inefficient, but the
					 * justअगरication is that it is an
					 * exception that check_func वापसs 1,
					 * and that in the regular हाल only one
					 * entry per UUID exists.
					 */
					जाओ again_search_slot;
				पूर्ण
				अगर (ret < 0 && ret != -ENOENT)
					जाओ out;
				key.offset++;
				जाओ again_search_slot;
			पूर्ण
			item_size -= माप(subid_le);
			offset += माप(subid_le);
		पूर्ण

skip:
		ret = btrfs_next_item(root, path);
		अगर (ret == 0)
			जारी;
		अन्यथा अगर (ret > 0)
			ret = 0;
		अवरोध;
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण
