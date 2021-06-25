<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "print-tree.h"

काष्ठा root_name_map अणु
	u64 id;
	अक्षर name[16];
पूर्ण;

अटल स्थिर काष्ठा root_name_map root_map[] = अणु
	अणु BTRFS_ROOT_TREE_OBJECTID,		"ROOT_TREE"		पूर्ण,
	अणु BTRFS_EXTENT_TREE_OBJECTID,		"EXTENT_TREE"		पूर्ण,
	अणु BTRFS_CHUNK_TREE_OBJECTID,		"CHUNK_TREE"		पूर्ण,
	अणु BTRFS_DEV_TREE_OBJECTID,		"DEV_TREE"		पूर्ण,
	अणु BTRFS_FS_TREE_OBJECTID,		"FS_TREE"		पूर्ण,
	अणु BTRFS_CSUM_TREE_OBJECTID,		"CSUM_TREE"		पूर्ण,
	अणु BTRFS_TREE_LOG_OBJECTID,		"TREE_LOG"		पूर्ण,
	अणु BTRFS_QUOTA_TREE_OBJECTID,		"QUOTA_TREE"		पूर्ण,
	अणु BTRFS_UUID_TREE_OBJECTID,		"UUID_TREE"		पूर्ण,
	अणु BTRFS_FREE_SPACE_TREE_OBJECTID,	"FREE_SPACE_TREE"	पूर्ण,
	अणु BTRFS_DATA_RELOC_TREE_OBJECTID,	"DATA_RELOC_TREE"	पूर्ण,
पूर्ण;

स्थिर अक्षर *btrfs_root_name(स्थिर काष्ठा btrfs_key *key, अक्षर *buf)
अणु
	पूर्णांक i;

	अगर (key->objectid == BTRFS_TREE_RELOC_OBJECTID) अणु
		snम_लिखो(buf, BTRFS_ROOT_NAME_BUF_LEN,
			 "TREE_RELOC offset=%llu", key->offset);
		वापस buf;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(root_map); i++) अणु
		अगर (root_map[i].id == key->objectid)
			वापस root_map[i].name;
	पूर्ण

	snम_लिखो(buf, BTRFS_ROOT_NAME_BUF_LEN, "%llu", key->objectid);
	वापस buf;
पूर्ण

अटल व्योम prपूर्णांक_chunk(काष्ठा extent_buffer *eb, काष्ठा btrfs_chunk *chunk)
अणु
	पूर्णांक num_stripes = btrfs_chunk_num_stripes(eb, chunk);
	पूर्णांक i;
	pr_info("\t\tchunk length %llu owner %llu type %llu num_stripes %d\n",
	       btrfs_chunk_length(eb, chunk), btrfs_chunk_owner(eb, chunk),
	       btrfs_chunk_type(eb, chunk), num_stripes);
	क्रम (i = 0 ; i < num_stripes ; i++) अणु
		pr_info("\t\t\tstripe %d devid %llu offset %llu\n", i,
		      btrfs_stripe_devid_nr(eb, chunk, i),
		      btrfs_stripe_offset_nr(eb, chunk, i));
	पूर्ण
पूर्ण
अटल व्योम prपूर्णांक_dev_item(काष्ठा extent_buffer *eb,
			   काष्ठा btrfs_dev_item *dev_item)
अणु
	pr_info("\t\tdev item devid %llu total_bytes %llu bytes used %llu\n",
	       btrfs_device_id(eb, dev_item),
	       btrfs_device_total_bytes(eb, dev_item),
	       btrfs_device_bytes_used(eb, dev_item));
पूर्ण
अटल व्योम prपूर्णांक_extent_data_ref(काष्ठा extent_buffer *eb,
				  काष्ठा btrfs_extent_data_ref *ref)
अणु
	pr_cont("extent data backref root %llu objectid %llu offset %llu count %u\n",
	       btrfs_extent_data_ref_root(eb, ref),
	       btrfs_extent_data_ref_objectid(eb, ref),
	       btrfs_extent_data_ref_offset(eb, ref),
	       btrfs_extent_data_ref_count(eb, ref));
पूर्ण

अटल व्योम prपूर्णांक_extent_item(काष्ठा extent_buffer *eb, पूर्णांक slot, पूर्णांक type)
अणु
	काष्ठा btrfs_extent_item *ei;
	काष्ठा btrfs_extent_अंतरभूत_ref *iref;
	काष्ठा btrfs_extent_data_ref *dref;
	काष्ठा btrfs_shared_data_ref *sref;
	काष्ठा btrfs_disk_key key;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ ptr;
	u32 item_size = btrfs_item_size_nr(eb, slot);
	u64 flags;
	u64 offset;
	पूर्णांक ref_index = 0;

	अगर (unlikely(item_size < माप(*ei))) अणु
		btrfs_prपूर्णांक_v0_err(eb->fs_info);
		btrfs_handle_fs_error(eb->fs_info, -EINVAL, शून्य);
	पूर्ण

	ei = btrfs_item_ptr(eb, slot, काष्ठा btrfs_extent_item);
	flags = btrfs_extent_flags(eb, ei);

	pr_info("\t\textent refs %llu gen %llu flags %llu\n",
	       btrfs_extent_refs(eb, ei), btrfs_extent_generation(eb, ei),
	       flags);

	अगर ((type == BTRFS_EXTENT_ITEM_KEY) &&
	    flags & BTRFS_EXTENT_FLAG_TREE_BLOCK) अणु
		काष्ठा btrfs_tree_block_info *info;
		info = (काष्ठा btrfs_tree_block_info *)(ei + 1);
		btrfs_tree_block_key(eb, info, &key);
		pr_info("\t\ttree block key (%llu %u %llu) level %d\n",
		       btrfs_disk_key_objectid(&key), key.type,
		       btrfs_disk_key_offset(&key),
		       btrfs_tree_block_level(eb, info));
		iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)(info + 1);
	पूर्ण अन्यथा अणु
		iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)(ei + 1);
	पूर्ण

	ptr = (अचिन्हित दीर्घ)iref;
	end = (अचिन्हित दीर्घ)ei + item_size;
	जबतक (ptr < end) अणु
		iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)ptr;
		type = btrfs_extent_अंतरभूत_ref_type(eb, iref);
		offset = btrfs_extent_अंतरभूत_ref_offset(eb, iref);
		pr_info("\t\tref#%d: ", ref_index++);
		चयन (type) अणु
		हाल BTRFS_TREE_BLOCK_REF_KEY:
			pr_cont("tree block backref root %llu\n", offset);
			अवरोध;
		हाल BTRFS_SHARED_BLOCK_REF_KEY:
			pr_cont("shared block backref parent %llu\n", offset);
			/*
			 * offset is supposed to be a tree block which
			 * must be aligned to nodesize.
			 */
			अगर (!IS_ALIGNED(offset, eb->fs_info->sectorsize))
				pr_info(
			"\t\t\t(parent %llu not aligned to sectorsize %u)\n",
					offset, eb->fs_info->sectorsize);
			अवरोध;
		हाल BTRFS_EXTENT_DATA_REF_KEY:
			dref = (काष्ठा btrfs_extent_data_ref *)(&iref->offset);
			prपूर्णांक_extent_data_ref(eb, dref);
			अवरोध;
		हाल BTRFS_SHARED_DATA_REF_KEY:
			sref = (काष्ठा btrfs_shared_data_ref *)(iref + 1);
			pr_cont("shared data backref parent %llu count %u\n",
			       offset, btrfs_shared_data_ref_count(eb, sref));
			/*
			 * offset is supposed to be a tree block which
			 * must be aligned to nodesize.
			 */
			अगर (!IS_ALIGNED(offset, eb->fs_info->nodesize))
				pr_info(
			"\t\t\t(parent %llu not aligned to sectorsize %u)\n",
				     offset, eb->fs_info->sectorsize);
			अवरोध;
		शेष:
			pr_cont("(extent %llu has INVALID ref type %d)\n",
				  eb->start, type);
			वापस;
		पूर्ण
		ptr += btrfs_extent_अंतरभूत_ref_size(type);
	पूर्ण
	WARN_ON(ptr > end);
पूर्ण

अटल व्योम prपूर्णांक_uuid_item(काष्ठा extent_buffer *l, अचिन्हित दीर्घ offset,
			    u32 item_size)
अणु
	अगर (!IS_ALIGNED(item_size, माप(u64))) अणु
		pr_warn("BTRFS: uuid item with illegal size %lu!\n",
			(अचिन्हित दीर्घ)item_size);
		वापस;
	पूर्ण
	जबतक (item_size) अणु
		__le64 subvol_id;

		पढ़ो_extent_buffer(l, &subvol_id, offset, माप(subvol_id));
		pr_info("\t\tsubvol_id %llu\n", le64_to_cpu(subvol_id));
		item_size -= माप(u64);
		offset += माप(u64);
	पूर्ण
पूर्ण

/*
 * Helper to output refs and locking status of extent buffer.  Useful to debug
 * race condition related problems.
 */
अटल व्योम prपूर्णांक_eb_refs_lock(काष्ठा extent_buffer *eb)
अणु
#अगर_घोषित CONFIG_BTRFS_DEBUG
	btrfs_info(eb->fs_info, "refs %u lock_owner %u current %u",
		   atomic_पढ़ो(&eb->refs), eb->lock_owner, current->pid);
#पूर्ण_अगर
पूर्ण

व्योम btrfs_prपूर्णांक_leaf(काष्ठा extent_buffer *l)
अणु
	काष्ठा btrfs_fs_info *fs_info;
	पूर्णांक i;
	u32 type, nr;
	काष्ठा btrfs_item *item;
	काष्ठा btrfs_root_item *ri;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_inode_item *ii;
	काष्ठा btrfs_block_group_item *bi;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा btrfs_extent_data_ref *dref;
	काष्ठा btrfs_shared_data_ref *sref;
	काष्ठा btrfs_dev_extent *dev_extent;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;

	अगर (!l)
		वापस;

	fs_info = l->fs_info;
	nr = btrfs_header_nritems(l);

	btrfs_info(fs_info,
		   "leaf %llu gen %llu total ptrs %d free space %d owner %llu",
		   btrfs_header_bytenr(l), btrfs_header_generation(l), nr,
		   btrfs_leaf_मुक्त_space(l), btrfs_header_owner(l));
	prपूर्णांक_eb_refs_lock(l);
	क्रम (i = 0 ; i < nr ; i++) अणु
		item = btrfs_item_nr(i);
		btrfs_item_key_to_cpu(l, &key, i);
		type = key.type;
		pr_info("\titem %d key (%llu %u %llu) itemoff %d itemsize %d\n",
			i, key.objectid, type, key.offset,
			btrfs_item_offset(l, item), btrfs_item_size(l, item));
		चयन (type) अणु
		हाल BTRFS_INODE_ITEM_KEY:
			ii = btrfs_item_ptr(l, i, काष्ठा btrfs_inode_item);
			pr_info("\t\tinode generation %llu size %llu mode %o\n",
			       btrfs_inode_generation(l, ii),
			       btrfs_inode_size(l, ii),
			       btrfs_inode_mode(l, ii));
			अवरोध;
		हाल BTRFS_सूची_ITEM_KEY:
			di = btrfs_item_ptr(l, i, काष्ठा btrfs_dir_item);
			btrfs_dir_item_key_to_cpu(l, di, &found_key);
			pr_info("\t\tdir oid %llu type %u\n",
				found_key.objectid,
				btrfs_dir_type(l, di));
			अवरोध;
		हाल BTRFS_ROOT_ITEM_KEY:
			ri = btrfs_item_ptr(l, i, काष्ठा btrfs_root_item);
			pr_info("\t\troot data bytenr %llu refs %u\n",
				btrfs_disk_root_bytenr(l, ri),
				btrfs_disk_root_refs(l, ri));
			अवरोध;
		हाल BTRFS_EXTENT_ITEM_KEY:
		हाल BTRFS_METADATA_ITEM_KEY:
			prपूर्णांक_extent_item(l, i, type);
			अवरोध;
		हाल BTRFS_TREE_BLOCK_REF_KEY:
			pr_info("\t\ttree block backref\n");
			अवरोध;
		हाल BTRFS_SHARED_BLOCK_REF_KEY:
			pr_info("\t\tshared block backref\n");
			अवरोध;
		हाल BTRFS_EXTENT_DATA_REF_KEY:
			dref = btrfs_item_ptr(l, i,
					      काष्ठा btrfs_extent_data_ref);
			prपूर्णांक_extent_data_ref(l, dref);
			अवरोध;
		हाल BTRFS_SHARED_DATA_REF_KEY:
			sref = btrfs_item_ptr(l, i,
					      काष्ठा btrfs_shared_data_ref);
			pr_info("\t\tshared data backref count %u\n",
			       btrfs_shared_data_ref_count(l, sref));
			अवरोध;
		हाल BTRFS_EXTENT_DATA_KEY:
			fi = btrfs_item_ptr(l, i,
					    काष्ठा btrfs_file_extent_item);
			अगर (btrfs_file_extent_type(l, fi) ==
			    BTRFS_खाता_EXTENT_INLINE) अणु
				pr_info("\t\tinline extent data size %llu\n",
				       btrfs_file_extent_ram_bytes(l, fi));
				अवरोध;
			पूर्ण
			pr_info("\t\textent data disk bytenr %llu nr %llu\n",
			       btrfs_file_extent_disk_bytenr(l, fi),
			       btrfs_file_extent_disk_num_bytes(l, fi));
			pr_info("\t\textent data offset %llu nr %llu ram %llu\n",
			       btrfs_file_extent_offset(l, fi),
			       btrfs_file_extent_num_bytes(l, fi),
			       btrfs_file_extent_ram_bytes(l, fi));
			अवरोध;
		हाल BTRFS_EXTENT_REF_V0_KEY:
			btrfs_prपूर्णांक_v0_err(fs_info);
			btrfs_handle_fs_error(fs_info, -EINVAL, शून्य);
			अवरोध;
		हाल BTRFS_BLOCK_GROUP_ITEM_KEY:
			bi = btrfs_item_ptr(l, i,
					    काष्ठा btrfs_block_group_item);
			pr_info(
		   "\t\tblock group used %llu chunk_objectid %llu flags %llu\n",
				btrfs_block_group_used(l, bi),
				btrfs_block_group_chunk_objectid(l, bi),
				btrfs_block_group_flags(l, bi));
			अवरोध;
		हाल BTRFS_CHUNK_ITEM_KEY:
			prपूर्णांक_chunk(l, btrfs_item_ptr(l, i,
						      काष्ठा btrfs_chunk));
			अवरोध;
		हाल BTRFS_DEV_ITEM_KEY:
			prपूर्णांक_dev_item(l, btrfs_item_ptr(l, i,
					काष्ठा btrfs_dev_item));
			अवरोध;
		हाल BTRFS_DEV_EXTENT_KEY:
			dev_extent = btrfs_item_ptr(l, i,
						    काष्ठा btrfs_dev_extent);
			pr_info("\t\tdev extent chunk_tree %llu\n\t\tchunk objectid %llu chunk offset %llu length %llu\n",
			       btrfs_dev_extent_chunk_tree(l, dev_extent),
			       btrfs_dev_extent_chunk_objectid(l, dev_extent),
			       btrfs_dev_extent_chunk_offset(l, dev_extent),
			       btrfs_dev_extent_length(l, dev_extent));
			अवरोध;
		हाल BTRFS_PERSISTENT_ITEM_KEY:
			pr_info("\t\tpersistent item objectid %llu offset %llu\n",
					key.objectid, key.offset);
			चयन (key.objectid) अणु
			हाल BTRFS_DEV_STATS_OBJECTID:
				pr_info("\t\tdevice stats\n");
				अवरोध;
			शेष:
				pr_info("\t\tunknown persistent item\n");
			पूर्ण
			अवरोध;
		हाल BTRFS_TEMPORARY_ITEM_KEY:
			pr_info("\t\ttemporary item objectid %llu offset %llu\n",
					key.objectid, key.offset);
			चयन (key.objectid) अणु
			हाल BTRFS_BALANCE_OBJECTID:
				pr_info("\t\tbalance status\n");
				अवरोध;
			शेष:
				pr_info("\t\tunknown temporary item\n");
			पूर्ण
			अवरोध;
		हाल BTRFS_DEV_REPLACE_KEY:
			pr_info("\t\tdev replace\n");
			अवरोध;
		हाल BTRFS_UUID_KEY_SUBVOL:
		हाल BTRFS_UUID_KEY_RECEIVED_SUBVOL:
			prपूर्णांक_uuid_item(l, btrfs_item_ptr_offset(l, i),
					btrfs_item_size_nr(l, i));
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम btrfs_prपूर्णांक_tree(काष्ठा extent_buffer *c, bool follow)
अणु
	काष्ठा btrfs_fs_info *fs_info;
	पूर्णांक i; u32 nr;
	काष्ठा btrfs_key key;
	पूर्णांक level;

	अगर (!c)
		वापस;
	fs_info = c->fs_info;
	nr = btrfs_header_nritems(c);
	level = btrfs_header_level(c);
	अगर (level == 0) अणु
		btrfs_prपूर्णांक_leaf(c);
		वापस;
	पूर्ण
	btrfs_info(fs_info,
		   "node %llu level %d gen %llu total ptrs %d free spc %u owner %llu",
		   btrfs_header_bytenr(c), level, btrfs_header_generation(c),
		   nr, (u32)BTRFS_NODEPTRS_PER_BLOCK(fs_info) - nr,
		   btrfs_header_owner(c));
	prपूर्णांक_eb_refs_lock(c);
	क्रम (i = 0; i < nr; i++) अणु
		btrfs_node_key_to_cpu(c, &key, i);
		pr_info("\tkey %d (%llu %u %llu) block %llu gen %llu\n",
		       i, key.objectid, key.type, key.offset,
		       btrfs_node_blockptr(c, i),
		       btrfs_node_ptr_generation(c, i));
	पूर्ण
	अगर (!follow)
		वापस;
	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा btrfs_key first_key;
		काष्ठा extent_buffer *next;

		btrfs_node_key_to_cpu(c, &first_key, i);
		next = पढ़ो_tree_block(fs_info, btrfs_node_blockptr(c, i),
				       btrfs_header_owner(c),
				       btrfs_node_ptr_generation(c, i),
				       level - 1, &first_key);
		अगर (IS_ERR(next)) अणु
			जारी;
		पूर्ण अन्यथा अगर (!extent_buffer_uptodate(next)) अणु
			मुक्त_extent_buffer(next);
			जारी;
		पूर्ण

		अगर (btrfs_is_leaf(next) &&
		   level != 1)
			BUG();
		अगर (btrfs_header_level(next) !=
		       level - 1)
			BUG();
		btrfs_prपूर्णांक_tree(next, follow);
		मुक्त_extent_buffer(next);
	पूर्ण
पूर्ण
