<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* CacheFiles security management
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/fs.h>
#समावेश <linux/cred.h>
#समावेश "internal.h"

/*
 * determine the security context within which we access the cache from within
 * the kernel
 */
पूर्णांक cachefiles_get_security_ID(काष्ठा cachefiles_cache *cache)
अणु
	काष्ठा cred *new;
	पूर्णांक ret;

	_enter("{%s}", cache->secctx);

	new = prepare_kernel_cred(current);
	अगर (!new) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	अगर (cache->secctx) अणु
		ret = set_security_override_from_ctx(new, cache->secctx);
		अगर (ret < 0) अणु
			put_cred(new);
			pr_err("Security denies permission to nominate security context: error %d\n",
			       ret);
			जाओ error;
		पूर्ण
	पूर्ण

	cache->cache_cred = new;
	ret = 0;
error:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * see अगर सूची_गढ़ो and create can be perक्रमmed in the root directory
 */
अटल पूर्णांक cachefiles_check_cache_dir(काष्ठा cachefiles_cache *cache,
				      काष्ठा dentry *root)
अणु
	पूर्णांक ret;

	ret = security_inode_सूची_गढ़ो(d_backing_inode(root), root, 0);
	अगर (ret < 0) अणु
		pr_err("Security denies permission to make dirs: error %d",
		       ret);
		वापस ret;
	पूर्ण

	ret = security_inode_create(d_backing_inode(root), root, 0);
	अगर (ret < 0)
		pr_err("Security denies permission to create files: error %d",
		       ret);

	वापस ret;
पूर्ण

/*
 * check the security details of the on-disk cache
 * - must be called with security override in क्रमce
 * - must वापस with a security override in क्रमce - even in the हाल of an
 *   error
 */
पूर्णांक cachefiles_determine_cache_security(काष्ठा cachefiles_cache *cache,
					काष्ठा dentry *root,
					स्थिर काष्ठा cred **_saved_cred)
अणु
	काष्ठा cred *new;
	पूर्णांक ret;

	_enter("");

	/* duplicate the cache creds क्रम COW (the override is currently in
	 * क्रमce, so we can use prepare_creds() to करो this) */
	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	cachefiles_end_secure(cache, *_saved_cred);

	/* use the cache root dir's security context as the basis with
	 * which create files */
	ret = set_create_files_as(new, d_backing_inode(root));
	अगर (ret < 0) अणु
		पात_creds(new);
		cachefiles_begin_secure(cache, _saved_cred);
		_leave(" = %d [cfa]", ret);
		वापस ret;
	पूर्ण

	put_cred(cache->cache_cred);
	cache->cache_cred = new;

	cachefiles_begin_secure(cache, _saved_cred);
	ret = cachefiles_check_cache_dir(cache, root);

	अगर (ret == -EOPNOTSUPP)
		ret = 0;
	_leave(" = %d", ret);
	वापस ret;
पूर्ण
