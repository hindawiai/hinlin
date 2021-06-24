<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* CacheFiles extended attribute management
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/xattr.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

अटल स्थिर अक्षर cachefiles_xattr_cache[] =
	XATTR_USER_PREFIX "CacheFiles.cache";

/*
 * check the type label on an object
 * - करोne using xattrs
 */
पूर्णांक cachefiles_check_object_type(काष्ठा cachefiles_object *object)
अणु
	काष्ठा dentry *dentry = object->dentry;
	अक्षर type[3], xtype[3];
	पूर्णांक ret;

	ASSERT(dentry);
	ASSERT(d_backing_inode(dentry));

	अगर (!object->fscache.cookie)
		म_नकल(type, "C3");
	अन्यथा
		snम_लिखो(type, 3, "%02x", object->fscache.cookie->def->type);

	_enter("%p{%s}", object, type);

	/* attempt to install a type label directly */
	ret = vfs_setxattr(&init_user_ns, dentry, cachefiles_xattr_cache, type,
			   2, XATTR_CREATE);
	अगर (ret == 0) अणु
		_debug("SET"); /* we succeeded */
		जाओ error;
	पूर्ण

	अगर (ret != -EEXIST) अणु
		pr_err("Can't set xattr on %pd [%lu] (err %d)\n",
		       dentry, d_backing_inode(dentry)->i_ino,
		       -ret);
		जाओ error;
	पूर्ण

	/* पढ़ो the current type label */
	ret = vfs_getxattr(&init_user_ns, dentry, cachefiles_xattr_cache, xtype,
			   3);
	अगर (ret < 0) अणु
		अगर (ret == -दुस्फल)
			जाओ bad_type_length;

		pr_err("Can't read xattr on %pd [%lu] (err %d)\n",
		       dentry, d_backing_inode(dentry)->i_ino,
		       -ret);
		जाओ error;
	पूर्ण

	/* check the type is what we're expecting */
	अगर (ret != 2)
		जाओ bad_type_length;

	अगर (xtype[0] != type[0] || xtype[1] != type[1])
		जाओ bad_type;

	ret = 0;

error:
	_leave(" = %d", ret);
	वापस ret;

bad_type_length:
	pr_err("Cache object %lu type xattr length incorrect\n",
	       d_backing_inode(dentry)->i_ino);
	ret = -EIO;
	जाओ error;

bad_type:
	xtype[2] = 0;
	pr_err("Cache object %pd [%lu] type %s not %s\n",
	       dentry, d_backing_inode(dentry)->i_ino,
	       xtype, type);
	ret = -EIO;
	जाओ error;
पूर्ण

/*
 * set the state xattr on a cache file
 */
पूर्णांक cachefiles_set_object_xattr(काष्ठा cachefiles_object *object,
				काष्ठा cachefiles_xattr *auxdata)
अणु
	काष्ठा dentry *dentry = object->dentry;
	पूर्णांक ret;

	ASSERT(dentry);

	_enter("%p,#%d", object, auxdata->len);

	/* attempt to install the cache metadata directly */
	_debug("SET #%u", auxdata->len);

	clear_bit(FSCACHE_COOKIE_AUX_UPDATED, &object->fscache.cookie->flags);
	ret = vfs_setxattr(&init_user_ns, dentry, cachefiles_xattr_cache,
			   &auxdata->type, auxdata->len, XATTR_CREATE);
	अगर (ret < 0 && ret != -ENOMEM)
		cachefiles_io_error_obj(
			object,
			"Failed to set xattr with error %d", ret);

	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * update the state xattr on a cache file
 */
पूर्णांक cachefiles_update_object_xattr(काष्ठा cachefiles_object *object,
				   काष्ठा cachefiles_xattr *auxdata)
अणु
	काष्ठा dentry *dentry = object->dentry;
	पूर्णांक ret;

	अगर (!dentry)
		वापस -ESTALE;

	_enter("%p,#%d", object, auxdata->len);

	/* attempt to install the cache metadata directly */
	_debug("SET #%u", auxdata->len);

	clear_bit(FSCACHE_COOKIE_AUX_UPDATED, &object->fscache.cookie->flags);
	ret = vfs_setxattr(&init_user_ns, dentry, cachefiles_xattr_cache,
			   &auxdata->type, auxdata->len, XATTR_REPLACE);
	अगर (ret < 0 && ret != -ENOMEM)
		cachefiles_io_error_obj(
			object,
			"Failed to update xattr with error %d", ret);

	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * check the consistency between the backing cache and the FS-Cache cookie
 */
पूर्णांक cachefiles_check_auxdata(काष्ठा cachefiles_object *object)
अणु
	काष्ठा cachefiles_xattr *auxbuf;
	क्रमागत fscache_checkaux validity;
	काष्ठा dentry *dentry = object->dentry;
	sमाप_प्रकार xlen;
	पूर्णांक ret;

	ASSERT(dentry);
	ASSERT(d_backing_inode(dentry));
	ASSERT(object->fscache.cookie->def->check_aux);

	auxbuf = kदो_स्मृति(माप(काष्ठा cachefiles_xattr) + 512, GFP_KERNEL);
	अगर (!auxbuf)
		वापस -ENOMEM;

	xlen = vfs_getxattr(&init_user_ns, dentry, cachefiles_xattr_cache,
			    &auxbuf->type, 512 + 1);
	ret = -ESTALE;
	अगर (xlen < 1 ||
	    auxbuf->type != object->fscache.cookie->def->type)
		जाओ error;

	xlen--;
	validity = fscache_check_aux(&object->fscache, &auxbuf->data, xlen,
				     i_size_पढ़ो(d_backing_inode(dentry)));
	अगर (validity != FSCACHE_CHECKAUX_OKAY)
		जाओ error;

	ret = 0;
error:
	kमुक्त(auxbuf);
	वापस ret;
पूर्ण

/*
 * check the state xattr on a cache file
 * - वापस -ESTALE अगर the object should be deleted
 */
पूर्णांक cachefiles_check_object_xattr(काष्ठा cachefiles_object *object,
				  काष्ठा cachefiles_xattr *auxdata)
अणु
	काष्ठा cachefiles_xattr *auxbuf;
	काष्ठा dentry *dentry = object->dentry;
	पूर्णांक ret;

	_enter("%p,#%d", object, auxdata->len);

	ASSERT(dentry);
	ASSERT(d_backing_inode(dentry));

	auxbuf = kदो_स्मृति(माप(काष्ठा cachefiles_xattr) + 512, cachefiles_gfp);
	अगर (!auxbuf) अणु
		_leave(" = -ENOMEM");
		वापस -ENOMEM;
	पूर्ण

	/* पढ़ो the current type label */
	ret = vfs_getxattr(&init_user_ns, dentry, cachefiles_xattr_cache,
			   &auxbuf->type, 512 + 1);
	अगर (ret < 0) अणु
		अगर (ret == -ENODATA)
			जाओ stale; /* no attribute - घातer went off
				     * mid-cull? */

		अगर (ret == -दुस्फल)
			जाओ bad_type_length;

		cachefiles_io_error_obj(object,
					"Can't read xattr on %lu (err %d)",
					d_backing_inode(dentry)->i_ino, -ret);
		जाओ error;
	पूर्ण

	/* check the on-disk object */
	अगर (ret < 1)
		जाओ bad_type_length;

	अगर (auxbuf->type != auxdata->type)
		जाओ stale;

	auxbuf->len = ret;

	/* consult the netfs */
	अगर (object->fscache.cookie->def->check_aux) अणु
		क्रमागत fscache_checkaux result;
		अचिन्हित पूर्णांक dlen;

		dlen = auxbuf->len - 1;

		_debug("checkaux %s #%u",
		       object->fscache.cookie->def->name, dlen);

		result = fscache_check_aux(&object->fscache,
					   &auxbuf->data, dlen,
					   i_size_पढ़ो(d_backing_inode(dentry)));

		चयन (result) अणु
			/* entry okay as is */
		हाल FSCACHE_CHECKAUX_OKAY:
			जाओ okay;

			/* entry requires update */
		हाल FSCACHE_CHECKAUX_NEEDS_UPDATE:
			अवरोध;

			/* entry requires deletion */
		हाल FSCACHE_CHECKAUX_OBSOLETE:
			जाओ stale;

		शेष:
			BUG();
		पूर्ण

		/* update the current label */
		ret = vfs_setxattr(&init_user_ns, dentry,
				   cachefiles_xattr_cache, &auxdata->type,
				   auxdata->len, XATTR_REPLACE);
		अगर (ret < 0) अणु
			cachefiles_io_error_obj(object,
						"Can't update xattr on %lu"
						" (error %d)",
						d_backing_inode(dentry)->i_ino, -ret);
			जाओ error;
		पूर्ण
	पूर्ण

okay:
	ret = 0;

error:
	kमुक्त(auxbuf);
	_leave(" = %d", ret);
	वापस ret;

bad_type_length:
	pr_err("Cache object %lu xattr length incorrect\n",
	       d_backing_inode(dentry)->i_ino);
	ret = -EIO;
	जाओ error;

stale:
	ret = -ESTALE;
	जाओ error;
पूर्ण

/*
 * हटाओ the object's xattr to mark it stale
 */
पूर्णांक cachefiles_हटाओ_object_xattr(काष्ठा cachefiles_cache *cache,
				   काष्ठा dentry *dentry)
अणु
	पूर्णांक ret;

	ret = vfs_हटाओxattr(&init_user_ns, dentry, cachefiles_xattr_cache);
	अगर (ret < 0) अणु
		अगर (ret == -ENOENT || ret == -ENODATA)
			ret = 0;
		अन्यथा अगर (ret != -ENOMEM)
			cachefiles_io_error(cache,
					    "Can't remove xattr from %lu"
					    " (error %d)",
					    d_backing_inode(dentry)->i_ino, -ret);
	पूर्ण

	_leave(" = %d", ret);
	वापस ret;
पूर्ण
