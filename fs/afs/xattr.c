<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Extended attribute handling क्रम AFS.  We use xattrs to get and set metadata
 * instead of providing pioctl().
 *
 * Copyright (C) 2017 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/xattr.h>
#समावेश "internal.h"

/*
 * Deal with the result of a successful fetch ACL operation.
 */
अटल व्योम afs_acl_success(काष्ठा afs_operation *op)
अणु
	afs_vnode_commit_status(op, &op->file[0]);
पूर्ण

अटल व्योम afs_acl_put(काष्ठा afs_operation *op)
अणु
	kमुक्त(op->acl);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_fetch_acl_operation = अणु
	.issue_afs_rpc	= afs_fs_fetch_acl,
	.success	= afs_acl_success,
	.put		= afs_acl_put,
पूर्ण;

/*
 * Get a file's ACL.
 */
अटल पूर्णांक afs_xattr_get_acl(स्थिर काष्ठा xattr_handler *handler,
			     काष्ठा dentry *dentry,
			     काष्ठा inode *inode, स्थिर अक्षर *name,
			     व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	काष्ठा afs_acl *acl = शून्य;
	पूर्णांक ret;

	op = afs_alloc_operation(शून्य, vnode->volume);
	अगर (IS_ERR(op))
		वापस -ENOMEM;

	afs_op_set_vnode(op, 0, vnode);
	op->ops = &afs_fetch_acl_operation;

	afs_begin_vnode_operation(op);
	afs_रुको_क्रम_operation(op);
	acl = op->acl;
	op->acl = शून्य;
	ret = afs_put_operation(op);

	अगर (ret == 0) अणु
		ret = acl->size;
		अगर (size > 0) अणु
			अगर (acl->size <= size)
				स_नकल(buffer, acl->data, acl->size);
			अन्यथा
				ret = -दुस्फल;
		पूर्ण
	पूर्ण

	kमुक्त(acl);
	वापस ret;
पूर्ण

अटल bool afs_make_acl(काष्ठा afs_operation *op,
			 स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा afs_acl *acl;

	acl = kदो_स्मृति(माप(*acl) + size, GFP_KERNEL);
	अगर (!acl) अणु
		afs_op_nomem(op);
		वापस false;
	पूर्ण

	acl->size = size;
	स_नकल(acl->data, buffer, size);
	op->acl = acl;
	वापस true;
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_store_acl_operation = अणु
	.issue_afs_rpc	= afs_fs_store_acl,
	.success	= afs_acl_success,
	.put		= afs_acl_put,
पूर्ण;

/*
 * Set a file's AFS3 ACL.
 */
अटल पूर्णांक afs_xattr_set_acl(स्थिर काष्ठा xattr_handler *handler,
			     काष्ठा user_namespace *mnt_userns,
                             काष्ठा dentry *dentry,
                             काष्ठा inode *inode, स्थिर अक्षर *name,
                             स्थिर व्योम *buffer, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);

	अगर (flags == XATTR_CREATE)
		वापस -EINVAL;

	op = afs_alloc_operation(शून्य, vnode->volume);
	अगर (IS_ERR(op))
		वापस -ENOMEM;

	afs_op_set_vnode(op, 0, vnode);
	अगर (!afs_make_acl(op, buffer, size))
		वापस afs_put_operation(op);

	op->ops = &afs_store_acl_operation;
	वापस afs_करो_sync_operation(op);
पूर्ण

अटल स्थिर काष्ठा xattr_handler afs_xattr_afs_acl_handler = अणु
	.name   = "afs.acl",
	.get    = afs_xattr_get_acl,
	.set    = afs_xattr_set_acl,
पूर्ण;

अटल स्थिर काष्ठा afs_operation_ops yfs_fetch_opaque_acl_operation = अणु
	.issue_yfs_rpc	= yfs_fs_fetch_opaque_acl,
	.success	= afs_acl_success,
	/* Don't मुक्त op->yacl in .put here */
पूर्ण;

/*
 * Get a file's YFS ACL.
 */
अटल पूर्णांक afs_xattr_get_yfs(स्थिर काष्ठा xattr_handler *handler,
			     काष्ठा dentry *dentry,
			     काष्ठा inode *inode, स्थिर अक्षर *name,
			     व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	काष्ठा yfs_acl *yacl = शून्य;
	अक्षर buf[16], *data;
	पूर्णांक which = 0, dsize, ret = -ENOMEM;

	अगर (म_भेद(name, "acl") == 0)
		which = 0;
	अन्यथा अगर (म_भेद(name, "acl_inherited") == 0)
		which = 1;
	अन्यथा अगर (म_भेद(name, "acl_num_cleaned") == 0)
		which = 2;
	अन्यथा अगर (म_भेद(name, "vol_acl") == 0)
		which = 3;
	अन्यथा
		वापस -EOPNOTSUPP;

	yacl = kzalloc(माप(काष्ठा yfs_acl), GFP_KERNEL);
	अगर (!yacl)
		जाओ error;

	अगर (which == 0)
		yacl->flags |= YFS_ACL_WANT_ACL;
	अन्यथा अगर (which == 3)
		yacl->flags |= YFS_ACL_WANT_VOL_ACL;

	op = afs_alloc_operation(शून्य, vnode->volume);
	अगर (IS_ERR(op))
		जाओ error_yacl;

	afs_op_set_vnode(op, 0, vnode);
	op->yacl = yacl;
	op->ops = &yfs_fetch_opaque_acl_operation;

	afs_begin_vnode_operation(op);
	afs_रुको_क्रम_operation(op);
	ret = afs_put_operation(op);

	अगर (ret == 0) अणु
		चयन (which) अणु
		हाल 0:
			data = yacl->acl->data;
			dsize = yacl->acl->size;
			अवरोध;
		हाल 1:
			data = buf;
			dsize = scnम_लिखो(buf, माप(buf), "%u", yacl->inherit_flag);
			अवरोध;
		हाल 2:
			data = buf;
			dsize = scnम_लिखो(buf, माप(buf), "%u", yacl->num_cleaned);
			अवरोध;
		हाल 3:
			data = yacl->vol_acl->data;
			dsize = yacl->vol_acl->size;
			अवरोध;
		शेष:
			ret = -EOPNOTSUPP;
			जाओ error_yacl;
		पूर्ण

		ret = dsize;
		अगर (size > 0) अणु
			अगर (dsize <= size)
				स_नकल(buffer, data, dsize);
			अन्यथा
				ret = -दुस्फल;
		पूर्ण
	पूर्ण अन्यथा अगर (ret == -ENOTSUPP) अणु
		ret = -ENODATA;
	पूर्ण

error_yacl:
	yfs_मुक्त_opaque_acl(yacl);
error:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops yfs_store_opaque_acl2_operation = अणु
	.issue_yfs_rpc	= yfs_fs_store_opaque_acl2,
	.success	= afs_acl_success,
	.put		= afs_acl_put,
पूर्ण;

/*
 * Set a file's YFS ACL.
 */
अटल पूर्णांक afs_xattr_set_yfs(स्थिर काष्ठा xattr_handler *handler,
			     काष्ठा user_namespace *mnt_userns,
                             काष्ठा dentry *dentry,
                             काष्ठा inode *inode, स्थिर अक्षर *name,
                             स्थिर व्योम *buffer, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	पूर्णांक ret;

	अगर (flags == XATTR_CREATE ||
	    म_भेद(name, "acl") != 0)
		वापस -EINVAL;

	op = afs_alloc_operation(शून्य, vnode->volume);
	अगर (IS_ERR(op))
		वापस -ENOMEM;

	afs_op_set_vnode(op, 0, vnode);
	अगर (!afs_make_acl(op, buffer, size))
		वापस afs_put_operation(op);

	op->ops = &yfs_store_opaque_acl2_operation;
	ret = afs_करो_sync_operation(op);
	अगर (ret == -ENOTSUPP)
		ret = -ENODATA;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा xattr_handler afs_xattr_yfs_handler = अणु
	.prefix	= "afs.yfs.",
	.get	= afs_xattr_get_yfs,
	.set	= afs_xattr_set_yfs,
पूर्ण;

/*
 * Get the name of the cell on which a file resides.
 */
अटल पूर्णांक afs_xattr_get_cell(स्थिर काष्ठा xattr_handler *handler,
			      काष्ठा dentry *dentry,
			      काष्ठा inode *inode, स्थिर अक्षर *name,
			      व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	काष्ठा afs_cell *cell = vnode->volume->cell;
	माप_प्रकार namelen;

	namelen = cell->name_len;
	अगर (size == 0)
		वापस namelen;
	अगर (namelen > size)
		वापस -दुस्फल;
	स_नकल(buffer, cell->name, namelen);
	वापस namelen;
पूर्ण

अटल स्थिर काष्ठा xattr_handler afs_xattr_afs_cell_handler = अणु
	.name	= "afs.cell",
	.get	= afs_xattr_get_cell,
पूर्ण;

/*
 * Get the volume ID, vnode ID and vnode uniquअगरier of a file as a sequence of
 * hex numbers separated by colons.
 */
अटल पूर्णांक afs_xattr_get_fid(स्थिर काष्ठा xattr_handler *handler,
			     काष्ठा dentry *dentry,
			     काष्ठा inode *inode, स्थिर अक्षर *name,
			     व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	अक्षर text[16 + 1 + 24 + 1 + 8 + 1];
	माप_प्रकार len;

	/* The volume ID is 64-bit, the vnode ID is 96-bit and the
	 * uniquअगरier is 32-bit.
	 */
	len = scnम_लिखो(text, माप(text), "%llx:", vnode->fid.vid);
	अगर (vnode->fid.vnode_hi)
		len += scnम_लिखो(text + len, माप(text) - len, "%x%016llx",
				vnode->fid.vnode_hi, vnode->fid.vnode);
	अन्यथा
		len += scnम_लिखो(text + len, माप(text) - len, "%llx",
				 vnode->fid.vnode);
	len += scnम_लिखो(text + len, माप(text) - len, ":%x",
			 vnode->fid.unique);

	अगर (size == 0)
		वापस len;
	अगर (len > size)
		वापस -दुस्फल;
	स_नकल(buffer, text, len);
	वापस len;
पूर्ण

अटल स्थिर काष्ठा xattr_handler afs_xattr_afs_fid_handler = अणु
	.name	= "afs.fid",
	.get	= afs_xattr_get_fid,
पूर्ण;

/*
 * Get the name of the volume on which a file resides.
 */
अटल पूर्णांक afs_xattr_get_volume(स्थिर काष्ठा xattr_handler *handler,
			      काष्ठा dentry *dentry,
			      काष्ठा inode *inode, स्थिर अक्षर *name,
			      व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	स्थिर अक्षर *volname = vnode->volume->name;
	माप_प्रकार namelen;

	namelen = म_माप(volname);
	अगर (size == 0)
		वापस namelen;
	अगर (namelen > size)
		वापस -दुस्फल;
	स_नकल(buffer, volname, namelen);
	वापस namelen;
पूर्ण

अटल स्थिर काष्ठा xattr_handler afs_xattr_afs_volume_handler = अणु
	.name	= "afs.volume",
	.get	= afs_xattr_get_volume,
पूर्ण;

स्थिर काष्ठा xattr_handler *afs_xattr_handlers[] = अणु
	&afs_xattr_afs_acl_handler,
	&afs_xattr_afs_cell_handler,
	&afs_xattr_afs_fid_handler,
	&afs_xattr_afs_volume_handler,
	&afs_xattr_yfs_handler,		/* afs.yfs. prefix */
	शून्य
पूर्ण;
