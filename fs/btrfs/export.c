<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "btrfs_inode.h"
#समावेश "print-tree.h"
#समावेश "export.h"

#घोषणा BTRFS_FID_SIZE_NON_CONNECTABLE (दुरत्व(काष्ठा btrfs_fid, \
						 parent_objectid) / 4)
#घोषणा BTRFS_FID_SIZE_CONNECTABLE (दुरत्व(काष्ठा btrfs_fid, \
					     parent_root_objectid) / 4)
#घोषणा BTRFS_FID_SIZE_CONNECTABLE_ROOT (माप(काष्ठा btrfs_fid) / 4)

अटल पूर्णांक btrfs_encode_fh(काष्ठा inode *inode, u32 *fh, पूर्णांक *max_len,
			   काष्ठा inode *parent)
अणु
	काष्ठा btrfs_fid *fid = (काष्ठा btrfs_fid *)fh;
	पूर्णांक len = *max_len;
	पूर्णांक type;

	अगर (parent && (len < BTRFS_FID_SIZE_CONNECTABLE)) अणु
		*max_len = BTRFS_FID_SIZE_CONNECTABLE;
		वापस खाताID_INVALID;
	पूर्ण अन्यथा अगर (len < BTRFS_FID_SIZE_NON_CONNECTABLE) अणु
		*max_len = BTRFS_FID_SIZE_NON_CONNECTABLE;
		वापस खाताID_INVALID;
	पूर्ण

	len  = BTRFS_FID_SIZE_NON_CONNECTABLE;
	type = खाताID_BTRFS_WITHOUT_PARENT;

	fid->objectid = btrfs_ino(BTRFS_I(inode));
	fid->root_objectid = BTRFS_I(inode)->root->root_key.objectid;
	fid->gen = inode->i_generation;

	अगर (parent) अणु
		u64 parent_root_id;

		fid->parent_objectid = BTRFS_I(parent)->location.objectid;
		fid->parent_gen = parent->i_generation;
		parent_root_id = BTRFS_I(parent)->root->root_key.objectid;

		अगर (parent_root_id != fid->root_objectid) अणु
			fid->parent_root_objectid = parent_root_id;
			len = BTRFS_FID_SIZE_CONNECTABLE_ROOT;
			type = खाताID_BTRFS_WITH_PARENT_ROOT;
		पूर्ण अन्यथा अणु
			len = BTRFS_FID_SIZE_CONNECTABLE;
			type = खाताID_BTRFS_WITH_PARENT;
		पूर्ण
	पूर्ण

	*max_len = len;
	वापस type;
पूर्ण

काष्ठा dentry *btrfs_get_dentry(काष्ठा super_block *sb, u64 objectid,
				u64 root_objectid, u32 generation,
				पूर्णांक check_generation)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(sb);
	काष्ठा btrfs_root *root;
	काष्ठा inode *inode;

	अगर (objectid < BTRFS_FIRST_FREE_OBJECTID)
		वापस ERR_PTR(-ESTALE);

	root = btrfs_get_fs_root(fs_info, root_objectid, true);
	अगर (IS_ERR(root))
		वापस ERR_CAST(root);

	inode = btrfs_iget(sb, objectid, root);
	btrfs_put_root(root);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	अगर (check_generation && generation != inode->i_generation) अणु
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण

	वापस d_obtain_alias(inode);
पूर्ण

अटल काष्ठा dentry *btrfs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fh,
					 पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा btrfs_fid *fid = (काष्ठा btrfs_fid *) fh;
	u64 objectid, root_objectid;
	u32 generation;

	अगर (fh_type == खाताID_BTRFS_WITH_PARENT) अणु
		अगर (fh_len <  BTRFS_FID_SIZE_CONNECTABLE)
			वापस शून्य;
		root_objectid = fid->root_objectid;
	पूर्ण अन्यथा अगर (fh_type == खाताID_BTRFS_WITH_PARENT_ROOT) अणु
		अगर (fh_len < BTRFS_FID_SIZE_CONNECTABLE_ROOT)
			वापस शून्य;
		root_objectid = fid->parent_root_objectid;
	पूर्ण अन्यथा
		वापस शून्य;

	objectid = fid->parent_objectid;
	generation = fid->parent_gen;

	वापस btrfs_get_dentry(sb, objectid, root_objectid, generation, 1);
पूर्ण

अटल काष्ठा dentry *btrfs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fh,
					 पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा btrfs_fid *fid = (काष्ठा btrfs_fid *) fh;
	u64 objectid, root_objectid;
	u32 generation;

	अगर ((fh_type != खाताID_BTRFS_WITH_PARENT ||
	     fh_len < BTRFS_FID_SIZE_CONNECTABLE) &&
	    (fh_type != खाताID_BTRFS_WITH_PARENT_ROOT ||
	     fh_len < BTRFS_FID_SIZE_CONNECTABLE_ROOT) &&
	    (fh_type != खाताID_BTRFS_WITHOUT_PARENT ||
	     fh_len < BTRFS_FID_SIZE_NON_CONNECTABLE))
		वापस शून्य;

	objectid = fid->objectid;
	root_objectid = fid->root_objectid;
	generation = fid->gen;

	वापस btrfs_get_dentry(sb, objectid, root_objectid, generation, 1);
पूर्ण

काष्ठा dentry *btrfs_get_parent(काष्ठा dentry *child)
अणु
	काष्ठा inode *dir = d_inode(child);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dir->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_root_ref *ref;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस ERR_PTR(-ENOMEM);

	अगर (btrfs_ino(BTRFS_I(dir)) == BTRFS_FIRST_FREE_OBJECTID) अणु
		key.objectid = root->root_key.objectid;
		key.type = BTRFS_ROOT_BACKREF_KEY;
		key.offset = (u64)-1;
		root = fs_info->tree_root;
	पूर्ण अन्यथा अणु
		key.objectid = btrfs_ino(BTRFS_I(dir));
		key.type = BTRFS_INODE_REF_KEY;
		key.offset = (u64)-1;
	पूर्ण

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ fail;

	BUG_ON(ret == 0); /* Key with offset of -1 found */
	अगर (path->slots[0] == 0) अणु
		ret = -ENOENT;
		जाओ fail;
	पूर्ण

	path->slots[0]--;
	leaf = path->nodes[0];

	btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);
	अगर (found_key.objectid != key.objectid || found_key.type != key.type) अणु
		ret = -ENOENT;
		जाओ fail;
	पूर्ण

	अगर (found_key.type == BTRFS_ROOT_BACKREF_KEY) अणु
		ref = btrfs_item_ptr(leaf, path->slots[0],
				     काष्ठा btrfs_root_ref);
		key.objectid = btrfs_root_ref_dirid(leaf, ref);
	पूर्ण अन्यथा अणु
		key.objectid = found_key.offset;
	पूर्ण
	btrfs_मुक्त_path(path);

	अगर (found_key.type == BTRFS_ROOT_BACKREF_KEY) अणु
		वापस btrfs_get_dentry(fs_info->sb, key.objectid,
					found_key.offset, 0, 0);
	पूर्ण

	वापस d_obtain_alias(btrfs_iget(fs_info->sb, key.objectid, root));
fail:
	btrfs_मुक्त_path(path);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक btrfs_get_name(काष्ठा dentry *parent, अक्षर *name,
			  काष्ठा dentry *child)
अणु
	काष्ठा inode *inode = d_inode(child);
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा btrfs_inode_ref *iref;
	काष्ठा btrfs_root_ref *rref;
	काष्ठा extent_buffer *leaf;
	अचिन्हित दीर्घ name_ptr;
	काष्ठा btrfs_key key;
	पूर्णांक name_len;
	पूर्णांक ret;
	u64 ino;

	अगर (!S_ISसूची(dir->i_mode))
		वापस -EINVAL;

	ino = btrfs_ino(BTRFS_I(inode));

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	अगर (ino == BTRFS_FIRST_FREE_OBJECTID) अणु
		key.objectid = BTRFS_I(inode)->root->root_key.objectid;
		key.type = BTRFS_ROOT_BACKREF_KEY;
		key.offset = (u64)-1;
		root = fs_info->tree_root;
	पूर्ण अन्यथा अणु
		key.objectid = ino;
		key.offset = btrfs_ino(BTRFS_I(dir));
		key.type = BTRFS_INODE_REF_KEY;
	पूर्ण

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0) अणु
		btrfs_मुक्त_path(path);
		वापस ret;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		अगर (ino == BTRFS_FIRST_FREE_OBJECTID) अणु
			path->slots[0]--;
		पूर्ण अन्यथा अणु
			btrfs_मुक्त_path(path);
			वापस -ENOENT;
		पूर्ण
	पूर्ण
	leaf = path->nodes[0];

	अगर (ino == BTRFS_FIRST_FREE_OBJECTID) अणु
		rref = btrfs_item_ptr(leaf, path->slots[0],
				     काष्ठा btrfs_root_ref);
		name_ptr = (अचिन्हित दीर्घ)(rref + 1);
		name_len = btrfs_root_ref_name_len(leaf, rref);
	पूर्ण अन्यथा अणु
		iref = btrfs_item_ptr(leaf, path->slots[0],
				      काष्ठा btrfs_inode_ref);
		name_ptr = (अचिन्हित दीर्घ)(iref + 1);
		name_len = btrfs_inode_ref_name_len(leaf, iref);
	पूर्ण

	पढ़ो_extent_buffer(leaf, name, name_ptr, name_len);
	btrfs_मुक्त_path(path);

	/*
	 * have to add the null termination to make sure that reconnect_path
	 * माला_लो the right len क्रम म_माप
	 */
	name[name_len] = '\0';

	वापस 0;
पूर्ण

स्थिर काष्ठा export_operations btrfs_export_ops = अणु
	.encode_fh	= btrfs_encode_fh,
	.fh_to_dentry	= btrfs_fh_to_dentry,
	.fh_to_parent	= btrfs_fh_to_parent,
	.get_parent	= btrfs_get_parent,
	.get_name	= btrfs_get_name,
पूर्ण;
