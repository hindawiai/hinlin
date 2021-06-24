<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Bind and unbind a cache from the fileप्रणाली backing it
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/completion.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/statfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/xattr.h>
#समावेश "internal.h"

अटल पूर्णांक cachefiles_daemon_add_cache(काष्ठा cachefiles_cache *caches);

/*
 * bind a directory as a cache
 */
पूर्णांक cachefiles_daemon_bind(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	_enter("{%u,%u,%u,%u,%u,%u},%s",
	       cache->frun_percent,
	       cache->fcull_percent,
	       cache->fstop_percent,
	       cache->brun_percent,
	       cache->bcull_percent,
	       cache->bstop_percent,
	       args);

	/* start by checking things over */
	ASSERT(cache->fstop_percent >= 0 &&
	       cache->fstop_percent < cache->fcull_percent &&
	       cache->fcull_percent < cache->frun_percent &&
	       cache->frun_percent  < 100);

	ASSERT(cache->bstop_percent >= 0 &&
	       cache->bstop_percent < cache->bcull_percent &&
	       cache->bcull_percent < cache->brun_percent &&
	       cache->brun_percent  < 100);

	अगर (*args) अणु
		pr_err("'bind' command doesn't take an argument\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!cache->rootस_नाम) अणु
		pr_err("No cache directory specified\n");
		वापस -EINVAL;
	पूर्ण

	/* करोn't permit alपढ़ोy bound caches to be re-bound */
	अगर (test_bit(CACHEखाताS_READY, &cache->flags)) अणु
		pr_err("Cache already bound\n");
		वापस -EBUSY;
	पूर्ण

	/* make sure we have copies of the tag and स_नाम strings */
	अगर (!cache->tag) अणु
		/* the tag string is released by the fops->release()
		 * function, so we करोn't release it on error here */
		cache->tag = kstrdup("CacheFiles", GFP_KERNEL);
		अगर (!cache->tag)
			वापस -ENOMEM;
	पूर्ण

	/* add the cache */
	वापस cachefiles_daemon_add_cache(cache);
पूर्ण

/*
 * add a cache
 */
अटल पूर्णांक cachefiles_daemon_add_cache(काष्ठा cachefiles_cache *cache)
अणु
	काष्ठा cachefiles_object *fsdef;
	काष्ठा path path;
	काष्ठा kstatfs stats;
	काष्ठा dentry *graveyard, *cachedir, *root;
	स्थिर काष्ठा cred *saved_cred;
	पूर्णांक ret;

	_enter("");

	/* we want to work under the module's security ID */
	ret = cachefiles_get_security_ID(cache);
	अगर (ret < 0)
		वापस ret;

	cachefiles_begin_secure(cache, &saved_cred);

	/* allocate the root index object */
	ret = -ENOMEM;

	fsdef = kmem_cache_alloc(cachefiles_object_jar, GFP_KERNEL);
	अगर (!fsdef)
		जाओ error_root_object;

	ASSERTCMP(fsdef->backer, ==, शून्य);

	atomic_set(&fsdef->usage, 1);
	fsdef->type = FSCACHE_COOKIE_TYPE_INDEX;

	_debug("- fsdef %p", fsdef);

	/* look up the directory at the root of the cache */
	ret = kern_path(cache->rootस_नाम, LOOKUP_सूचीECTORY, &path);
	अगर (ret < 0)
		जाओ error_खोलो_root;

	cache->mnt = path.mnt;
	root = path.dentry;

	ret = -EINVAL;
	अगर (mnt_user_ns(path.mnt) != &init_user_ns) अणु
		pr_warn("File cache on idmapped mounts not supported");
		जाओ error_unsupported;
	पूर्ण

	/* check parameters */
	ret = -EOPNOTSUPP;
	अगर (d_is_negative(root) ||
	    !d_backing_inode(root)->i_op->lookup ||
	    !d_backing_inode(root)->i_op->सूची_गढ़ो ||
	    !(d_backing_inode(root)->i_opflags & IOP_XATTR) ||
	    !root->d_sb->s_op->statfs ||
	    !root->d_sb->s_op->sync_fs)
		जाओ error_unsupported;

	ret = -EROFS;
	अगर (sb_rकरोnly(root->d_sb))
		जाओ error_unsupported;

	/* determine the security of the on-disk cache as this governs
	 * security ID of files we create */
	ret = cachefiles_determine_cache_security(cache, root, &saved_cred);
	अगर (ret < 0)
		जाओ error_unsupported;

	/* get the cache size and blocksize */
	ret = vfs_statfs(&path, &stats);
	अगर (ret < 0)
		जाओ error_unsupported;

	ret = -दुस्फल;
	अगर (stats.f_bsize <= 0)
		जाओ error_unsupported;

	ret = -EOPNOTSUPP;
	अगर (stats.f_bsize > PAGE_SIZE)
		जाओ error_unsupported;

	cache->bsize = stats.f_bsize;
	cache->bshअगरt = 0;
	अगर (stats.f_bsize < PAGE_SIZE)
		cache->bshअगरt = PAGE_SHIFT - ilog2(stats.f_bsize);

	_debug("blksize %u (shift %u)",
	       cache->bsize, cache->bshअगरt);

	_debug("size %llu, avail %llu",
	       (अचिन्हित दीर्घ दीर्घ) stats.f_blocks,
	       (अचिन्हित दीर्घ दीर्घ) stats.f_bavail);

	/* set up caching limits */
	करो_भाग(stats.f_files, 100);
	cache->fstop = stats.f_files * cache->fstop_percent;
	cache->fcull = stats.f_files * cache->fcull_percent;
	cache->frun  = stats.f_files * cache->frun_percent;

	_debug("limits {%llu,%llu,%llu} files",
	       (अचिन्हित दीर्घ दीर्घ) cache->frun,
	       (अचिन्हित दीर्घ दीर्घ) cache->fcull,
	       (अचिन्हित दीर्घ दीर्घ) cache->fstop);

	stats.f_blocks >>= cache->bshअगरt;
	करो_भाग(stats.f_blocks, 100);
	cache->bstop = stats.f_blocks * cache->bstop_percent;
	cache->bcull = stats.f_blocks * cache->bcull_percent;
	cache->brun  = stats.f_blocks * cache->brun_percent;

	_debug("limits {%llu,%llu,%llu} blocks",
	       (अचिन्हित दीर्घ दीर्घ) cache->brun,
	       (अचिन्हित दीर्घ दीर्घ) cache->bcull,
	       (अचिन्हित दीर्घ दीर्घ) cache->bstop);

	/* get the cache directory and check its type */
	cachedir = cachefiles_get_directory(cache, root, "cache");
	अगर (IS_ERR(cachedir)) अणु
		ret = PTR_ERR(cachedir);
		जाओ error_unsupported;
	पूर्ण

	fsdef->dentry = cachedir;
	fsdef->fscache.cookie = शून्य;

	ret = cachefiles_check_object_type(fsdef);
	अगर (ret < 0)
		जाओ error_unsupported;

	/* get the graveyard directory */
	graveyard = cachefiles_get_directory(cache, root, "graveyard");
	अगर (IS_ERR(graveyard)) अणु
		ret = PTR_ERR(graveyard);
		जाओ error_unsupported;
	पूर्ण

	cache->graveyard = graveyard;

	/* publish the cache */
	fscache_init_cache(&cache->cache,
			   &cachefiles_cache_ops,
			   "%s",
			   fsdef->dentry->d_sb->s_id);

	fscache_object_init(&fsdef->fscache, &fscache_fsdef_index,
			    &cache->cache);

	ret = fscache_add_cache(&cache->cache, &fsdef->fscache, cache->tag);
	अगर (ret < 0)
		जाओ error_add_cache;

	/* करोne */
	set_bit(CACHEखाताS_READY, &cache->flags);
	dput(root);

	pr_info("File cache on %s registered\n", cache->cache.identअगरier);

	/* check how much space the cache has */
	cachefiles_has_space(cache, 0, 0);
	cachefiles_end_secure(cache, saved_cred);
	वापस 0;

error_add_cache:
	dput(cache->graveyard);
	cache->graveyard = शून्य;
error_unsupported:
	mntput(cache->mnt);
	cache->mnt = शून्य;
	dput(fsdef->dentry);
	fsdef->dentry = शून्य;
	dput(root);
error_खोलो_root:
	kmem_cache_मुक्त(cachefiles_object_jar, fsdef);
error_root_object:
	cachefiles_end_secure(cache, saved_cred);
	pr_err("Failed to register: %d\n", ret);
	वापस ret;
पूर्ण

/*
 * unbind a cache on fd release
 */
व्योम cachefiles_daemon_unbind(काष्ठा cachefiles_cache *cache)
अणु
	_enter("");

	अगर (test_bit(CACHEखाताS_READY, &cache->flags)) अणु
		pr_info("File cache on %s unregistering\n",
			cache->cache.identअगरier);

		fscache_withdraw_cache(&cache->cache);
	पूर्ण

	dput(cache->graveyard);
	mntput(cache->mnt);

	kमुक्त(cache->rootस_नाम);
	kमुक्त(cache->secctx);
	kमुक्त(cache->tag);

	_leave("");
पूर्ण
