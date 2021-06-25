<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Red Hat.  All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/xattr.h>
#समावेश <linux/security.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/iversion.h>
#समावेश <linux/sched/mm.h>
#समावेश "ctree.h"
#समावेश "btrfs_inode.h"
#समावेश "transaction.h"
#समावेश "xattr.h"
#समावेश "disk-io.h"
#समावेश "props.h"
#समावेश "locking.h"

पूर्णांक btrfs_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
				व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ data_ptr;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	/* lookup the xattr by name */
	di = btrfs_lookup_xattr(शून्य, root, path, btrfs_ino(BTRFS_I(inode)),
			name, म_माप(name), 0);
	अगर (!di) अणु
		ret = -ENODATA;
		जाओ out;
	पूर्ण अन्यथा अगर (IS_ERR(di)) अणु
		ret = PTR_ERR(di);
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	/* अगर size is 0, that means we want the size of the attr */
	अगर (!size) अणु
		ret = btrfs_dir_data_len(leaf, di);
		जाओ out;
	पूर्ण

	/* now get the data out of our dir_item */
	अगर (btrfs_dir_data_len(leaf, di) > size) अणु
		ret = -दुस्फल;
		जाओ out;
	पूर्ण

	/*
	 * The way things are packed पूर्णांकo the leaf is like this
	 * |काष्ठा btrfs_dir_item|name|data|
	 * where name is the xattr name, so security.foo, and data is the
	 * content of the xattr.  data_ptr poपूर्णांकs to the location in memory
	 * where the data starts in the in memory leaf
	 */
	data_ptr = (अचिन्हित दीर्घ)((अक्षर *)(di + 1) +
				   btrfs_dir_name_len(leaf, di));
	पढ़ो_extent_buffer(leaf, buffer, data_ptr,
			   btrfs_dir_data_len(leaf, di));
	ret = btrfs_dir_data_len(leaf, di);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_setxattr(काष्ठा btrfs_trans_handle *trans, काष्ठा inode *inode,
		   स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा btrfs_dir_item *di = शून्य;
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_path *path;
	माप_प्रकार name_len = म_माप(name);
	पूर्णांक ret = 0;

	ASSERT(trans);

	अगर (name_len + size > BTRFS_MAX_XATTR_SIZE(root->fs_info))
		वापस -ENOSPC;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	path->skip_release_on_error = 1;

	अगर (!value) अणु
		di = btrfs_lookup_xattr(trans, root, path,
				btrfs_ino(BTRFS_I(inode)), name, name_len, -1);
		अगर (!di && (flags & XATTR_REPLACE))
			ret = -ENODATA;
		अन्यथा अगर (IS_ERR(di))
			ret = PTR_ERR(di);
		अन्यथा अगर (di)
			ret = btrfs_delete_one_dir_name(trans, root, path, di);
		जाओ out;
	पूर्ण

	/*
	 * For a replace we can't just करो the insert blindly.
	 * Do a lookup first (पढ़ो-only btrfs_search_slot), and वापस अगर xattr
	 * करोesn't exist. If it exists, fall करोwn below to the insert/replace
	 * path - we can't race with a concurrent xattr delete, because the VFS
	 * locks the inode's i_mutex beक्रमe calling setxattr or हटाओxattr.
	 */
	अगर (flags & XATTR_REPLACE) अणु
		ASSERT(inode_is_locked(inode));
		di = btrfs_lookup_xattr(शून्य, root, path,
				btrfs_ino(BTRFS_I(inode)), name, name_len, 0);
		अगर (!di)
			ret = -ENODATA;
		अन्यथा अगर (IS_ERR(di))
			ret = PTR_ERR(di);
		अगर (ret)
			जाओ out;
		btrfs_release_path(path);
		di = शून्य;
	पूर्ण

	ret = btrfs_insert_xattr_item(trans, root, path, btrfs_ino(BTRFS_I(inode)),
				      name, name_len, value, size);
	अगर (ret == -EOVERFLOW) अणु
		/*
		 * We have an existing item in a leaf, split_leaf couldn't
		 * expand it. That item might have or not a dir_item that
		 * matches our target xattr, so lets check.
		 */
		ret = 0;
		btrfs_निश्चित_tree_locked(path->nodes[0]);
		di = btrfs_match_dir_item_name(fs_info, path, name, name_len);
		अगर (!di && !(flags & XATTR_REPLACE)) अणु
			ret = -ENOSPC;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (ret == -EEXIST) अणु
		ret = 0;
		di = btrfs_match_dir_item_name(fs_info, path, name, name_len);
		ASSERT(di); /* logic error */
	पूर्ण अन्यथा अगर (ret) अणु
		जाओ out;
	पूर्ण

	अगर (di && (flags & XATTR_CREATE)) अणु
		ret = -EEXIST;
		जाओ out;
	पूर्ण

	अगर (di) अणु
		/*
		 * We're करोing a replace, and it must be atomic, that is, at
		 * any poपूर्णांक in समय we have either the old or the new xattr
		 * value in the tree. We करोn't want पढ़ोers (getxattr and
		 * listxattrs) to miss a value, this is specially important
		 * क्रम ACLs.
		 */
		स्थिर पूर्णांक slot = path->slots[0];
		काष्ठा extent_buffer *leaf = path->nodes[0];
		स्थिर u16 old_data_len = btrfs_dir_data_len(leaf, di);
		स्थिर u32 item_size = btrfs_item_size_nr(leaf, slot);
		स्थिर u32 data_size = माप(*di) + name_len + size;
		काष्ठा btrfs_item *item;
		अचिन्हित दीर्घ data_ptr;
		अक्षर *ptr;

		अगर (size > old_data_len) अणु
			अगर (btrfs_leaf_मुक्त_space(leaf) <
			    (size - old_data_len)) अणु
				ret = -ENOSPC;
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (old_data_len + name_len + माप(*di) == item_size) अणु
			/* No other xattrs packed in the same leaf item. */
			अगर (size > old_data_len)
				btrfs_extend_item(path, size - old_data_len);
			अन्यथा अगर (size < old_data_len)
				btrfs_truncate_item(path, data_size, 1);
		पूर्ण अन्यथा अणु
			/* There are other xattrs packed in the same item. */
			ret = btrfs_delete_one_dir_name(trans, root, path, di);
			अगर (ret)
				जाओ out;
			btrfs_extend_item(path, data_size);
		पूर्ण

		item = btrfs_item_nr(slot);
		ptr = btrfs_item_ptr(leaf, slot, अक्षर);
		ptr += btrfs_item_size(leaf, item) - data_size;
		di = (काष्ठा btrfs_dir_item *)ptr;
		btrfs_set_dir_data_len(leaf, di, size);
		data_ptr = ((अचिन्हित दीर्घ)(di + 1)) + name_len;
		ग_लिखो_extent_buffer(leaf, value, data_ptr, size);
		btrfs_mark_buffer_dirty(leaf);
	पूर्ण अन्यथा अणु
		/*
		 * Insert, and we had space क्रम the xattr, so path->slots[0] is
		 * where our xattr dir_item is and btrfs_insert_xattr_item()
		 * filled it.
		 */
	पूर्ण
out:
	btrfs_मुक्त_path(path);
	अगर (!ret) अणु
		set_bit(BTRFS_INODE_COPY_EVERYTHING,
			&BTRFS_I(inode)->runसमय_flags);
		clear_bit(BTRFS_INODE_NO_XATTRS, &BTRFS_I(inode)->runसमय_flags);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * @value: "" makes the attribute to empty, शून्य हटाओs it
 */
पूर्णांक btrfs_setxattr_trans(काष्ठा inode *inode, स्थिर अक्षर *name,
			 स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_trans_handle *trans;
	स्थिर bool start_trans = (current->journal_info == शून्य);
	पूर्णांक ret;

	अगर (start_trans) अणु
		/*
		 * 1 unit क्रम inserting/updating/deleting the xattr
		 * 1 unit क्रम the inode item update
		 */
		trans = btrfs_start_transaction(root, 2);
		अगर (IS_ERR(trans))
			वापस PTR_ERR(trans);
	पूर्ण अन्यथा अणु
		/*
		 * This can happen when smack is enabled and a directory is being
		 * created. It happens through d_instantiate_new(), which calls
		 * smack_d_instantiate(), which in turn calls __vfs_setxattr() to
		 * set the transmute xattr (XATTR_NAME_SMACKTRANSMUTE) on the
		 * inode. We have alपढ़ोy reserved space क्रम the xattr and inode
		 * update at btrfs_सूची_गढ़ो(), so just use the transaction handle.
		 * We करोn't join or start a transaction, as that will reset the
		 * block_rsv of the handle and trigger a warning क्रम the start
		 * हाल.
		 */
		ASSERT(म_भेदन(name, XATTR_SECURITY_PREFIX,
			       XATTR_SECURITY_PREFIX_LEN) == 0);
		trans = current->journal_info;
	पूर्ण

	ret = btrfs_setxattr(trans, inode, name, value, size, flags);
	अगर (ret)
		जाओ out;

	inode_inc_iversion(inode);
	inode->i_स_समय = current_समय(inode);
	ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
	BUG_ON(ret);
out:
	अगर (start_trans)
		btrfs_end_transaction(trans);
	वापस ret;
पूर्ण

sमाप_प्रकार btrfs_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार size)
अणु
	काष्ठा btrfs_key key;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_path *path;
	पूर्णांक ret = 0;
	माप_प्रकार total_size = 0, size_left = size;

	/*
	 * ok we want all objects associated with this id.
	 * NOTE: we set key.offset = 0; because we want to start with the
	 * first xattr that we find and walk क्रमward
	 */
	key.objectid = btrfs_ino(BTRFS_I(inode));
	key.type = BTRFS_XATTR_ITEM_KEY;
	key.offset = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	path->पढ़ोa = READA_FORWARD;

	/* search क्रम our xattrs */
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ err;

	जबतक (1) अणु
		काष्ठा extent_buffer *leaf;
		पूर्णांक slot;
		काष्ठा btrfs_dir_item *di;
		काष्ठा btrfs_key found_key;
		u32 item_size;
		u32 cur;

		leaf = path->nodes[0];
		slot = path->slots[0];

		/* this is where we start walking through the path */
		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			/*
			 * अगर we've reached the last slot in this leaf we need
			 * to go to the next leaf and reset everything
			 */
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ err;
			अन्यथा अगर (ret > 0)
				अवरोध;
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &found_key, slot);

		/* check to make sure this item is what we want */
		अगर (found_key.objectid != key.objectid)
			अवरोध;
		अगर (found_key.type > BTRFS_XATTR_ITEM_KEY)
			अवरोध;
		अगर (found_key.type < BTRFS_XATTR_ITEM_KEY)
			जाओ next_item;

		di = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_dir_item);
		item_size = btrfs_item_size_nr(leaf, slot);
		cur = 0;
		जबतक (cur < item_size) अणु
			u16 name_len = btrfs_dir_name_len(leaf, di);
			u16 data_len = btrfs_dir_data_len(leaf, di);
			u32 this_len = माप(*di) + name_len + data_len;
			अचिन्हित दीर्घ name_ptr = (अचिन्हित दीर्घ)(di + 1);

			total_size += name_len + 1;
			/*
			 * We are just looking क्रम how big our buffer needs to
			 * be.
			 */
			अगर (!size)
				जाओ next;

			अगर (!buffer || (name_len + 1) > size_left) अणु
				ret = -दुस्फल;
				जाओ err;
			पूर्ण

			पढ़ो_extent_buffer(leaf, buffer, name_ptr, name_len);
			buffer[name_len] = '\0';

			size_left -= name_len + 1;
			buffer += name_len + 1;
next:
			cur += this_len;
			di = (काष्ठा btrfs_dir_item *)((अक्षर *)di + this_len);
		पूर्ण
next_item:
		path->slots[0]++;
	पूर्ण
	ret = total_size;

err:
	btrfs_मुक्त_path(path);

	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_xattr_handler_get(स्थिर काष्ठा xattr_handler *handler,
				   काष्ठा dentry *unused, काष्ठा inode *inode,
				   स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	name = xattr_full_name(handler, name);
	वापस btrfs_getxattr(inode, name, buffer, size);
पूर्ण

अटल पूर्णांक btrfs_xattr_handler_set(स्थिर काष्ठा xattr_handler *handler,
				   काष्ठा user_namespace *mnt_userns,
				   काष्ठा dentry *unused, काष्ठा inode *inode,
				   स्थिर अक्षर *name, स्थिर व्योम *buffer,
				   माप_प्रकार size, पूर्णांक flags)
अणु
	name = xattr_full_name(handler, name);
	वापस btrfs_setxattr_trans(inode, name, buffer, size, flags);
पूर्ण

अटल पूर्णांक btrfs_xattr_handler_set_prop(स्थिर काष्ठा xattr_handler *handler,
					काष्ठा user_namespace *mnt_userns,
					काष्ठा dentry *unused, काष्ठा inode *inode,
					स्थिर अक्षर *name, स्थिर व्योम *value,
					माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;

	name = xattr_full_name(handler, name);
	ret = btrfs_validate_prop(name, value, size);
	अगर (ret)
		वापस ret;

	trans = btrfs_start_transaction(root, 2);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	ret = btrfs_set_prop(trans, inode, name, value, size, flags);
	अगर (!ret) अणु
		inode_inc_iversion(inode);
		inode->i_स_समय = current_समय(inode);
		ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
		BUG_ON(ret);
	पूर्ण

	btrfs_end_transaction(trans);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा xattr_handler btrfs_security_xattr_handler = अणु
	.prefix = XATTR_SECURITY_PREFIX,
	.get = btrfs_xattr_handler_get,
	.set = btrfs_xattr_handler_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler btrfs_trusted_xattr_handler = अणु
	.prefix = XATTR_TRUSTED_PREFIX,
	.get = btrfs_xattr_handler_get,
	.set = btrfs_xattr_handler_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler btrfs_user_xattr_handler = अणु
	.prefix = XATTR_USER_PREFIX,
	.get = btrfs_xattr_handler_get,
	.set = btrfs_xattr_handler_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler btrfs_btrfs_xattr_handler = अणु
	.prefix = XATTR_BTRFS_PREFIX,
	.get = btrfs_xattr_handler_get,
	.set = btrfs_xattr_handler_set_prop,
पूर्ण;

स्थिर काष्ठा xattr_handler *btrfs_xattr_handlers[] = अणु
	&btrfs_security_xattr_handler,
#अगर_घोषित CONFIG_BTRFS_FS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	&btrfs_trusted_xattr_handler,
	&btrfs_user_xattr_handler,
	&btrfs_btrfs_xattr_handler,
	शून्य,
पूर्ण;

अटल पूर्णांक btrfs_initxattrs(काष्ठा inode *inode,
			    स्थिर काष्ठा xattr *xattr_array, व्योम *fs_निजी)
अणु
	काष्ठा btrfs_trans_handle *trans = fs_निजी;
	स्थिर काष्ठा xattr *xattr;
	अचिन्हित पूर्णांक nofs_flag;
	अक्षर *name;
	पूर्णांक err = 0;

	/*
	 * We're holding a transaction handle, so use a NOFS memory allocation
	 * context to aव्योम deadlock अगर reclaim happens.
	 */
	nofs_flag = meदो_स्मृति_nofs_save();
	क्रम (xattr = xattr_array; xattr->name != शून्य; xattr++) अणु
		name = kदो_स्मृति(XATTR_SECURITY_PREFIX_LEN +
			       म_माप(xattr->name) + 1, GFP_KERNEL);
		अगर (!name) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण
		म_नकल(name, XATTR_SECURITY_PREFIX);
		म_नकल(name + XATTR_SECURITY_PREFIX_LEN, xattr->name);
		err = btrfs_setxattr(trans, inode, name, xattr->value,
				     xattr->value_len, 0);
		kमुक्त(name);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	meदो_स्मृति_nofs_restore(nofs_flag);
	वापस err;
पूर्ण

पूर्णांक btrfs_xattr_security_init(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा inode *inode, काष्ठा inode *dir,
			      स्थिर काष्ठा qstr *qstr)
अणु
	वापस security_inode_init_security(inode, dir, qstr,
					    &btrfs_initxattrs, trans);
पूर्ण
