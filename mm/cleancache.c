<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cleancache frontend
 *
 * This code provides the generic "frontend" layer to call a matching
 * "backend" driver implementation of cleancache.  See
 * Documentation/vm/cleancache.rst क्रम more inक्रमmation.
 *
 * Copyright (C) 2009-2010 Oracle Corp. All rights reserved.
 * Author: Dan Magenheimer
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/mm.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/cleancache.h>

/*
 * cleancache_ops is set by cleancache_रेजिस्टर_ops to contain the poपूर्णांकers
 * to the cleancache "backend" implementation functions.
 */
अटल स्थिर काष्ठा cleancache_ops *cleancache_ops __पढ़ो_mostly;

/*
 * Counters available via /sys/kernel/debug/cleancache (अगर debugfs is
 * properly configured.  These are क्रम inक्रमmation only so are not रक्षित
 * against increment races.
 */
अटल u64 cleancache_succ_माला_लो;
अटल u64 cleancache_failed_माला_लो;
अटल u64 cleancache_माला_दो;
अटल u64 cleancache_invalidates;

अटल व्योम cleancache_रेजिस्टर_ops_sb(काष्ठा super_block *sb, व्योम *unused)
अणु
	चयन (sb->cleancache_poolid) अणु
	हाल CLEANCACHE_NO_BACKEND:
		__cleancache_init_fs(sb);
		अवरोध;
	हाल CLEANCACHE_NO_BACKEND_SHARED:
		__cleancache_init_shared_fs(sb);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Register operations क्रम cleancache. Returns 0 on success.
 */
पूर्णांक cleancache_रेजिस्टर_ops(स्थिर काष्ठा cleancache_ops *ops)
अणु
	अगर (cmpxchg(&cleancache_ops, शून्य, ops))
		वापस -EBUSY;

	/*
	 * A cleancache backend can be built as a module and hence loaded after
	 * a cleancache enabled fileप्रणाली has called cleancache_init_fs. To
	 * handle such a scenario, here we call ->init_fs or ->init_shared_fs
	 * क्रम each active super block. To dअगरferentiate between local and
	 * shared fileप्रणालीs, we temporarily initialize sb->cleancache_poolid
	 * to CLEANCACHE_NO_BACKEND or CLEANCACHE_NO_BACKEND_SHARED
	 * respectively in हाल there is no backend रेजिस्टरed at the समय
	 * cleancache_init_fs or cleancache_init_shared_fs is called.
	 *
	 * Since fileप्रणालीs can be mounted concurrently with cleancache
	 * backend registration, we have to be careful to guarantee that all
	 * cleancache enabled fileप्रणालीs that has been mounted by the समय
	 * cleancache_रेजिस्टर_ops is called has got and all mounted later will
	 * get cleancache_poolid. This is assured by the following statements
	 * tied together:
	 *
	 * a) iterate_supers skips only those super blocks that has started
	 *    ->समाप्त_sb
	 *
	 * b) अगर iterate_supers encounters a super block that has not finished
	 *    ->mount yet, it रुकोs until it is finished
	 *
	 * c) cleancache_init_fs is called from ->mount and
	 *    cleancache_invalidate_fs is called from ->समाप्त_sb
	 *
	 * d) we call iterate_supers after cleancache_ops has been set
	 *
	 * From a) it follows that अगर iterate_supers skips a super block, then
	 * either the super block is alपढ़ोy dead, in which हाल we करो not need
	 * to bother initializing cleancache क्रम it, or it was mounted after we
	 * initiated iterate_supers. In the latter हाल, it must have seen
	 * cleancache_ops set according to d) and initialized cleancache from
	 * ->mount by itself according to c). This proves that we call
	 * ->init_fs at least once क्रम each active super block.
	 *
	 * From b) and c) it follows that अगर iterate_supers encounters a super
	 * block that has alपढ़ोy started ->init_fs, it will रुको until ->mount
	 * and hence ->init_fs has finished, then check cleancache_poolid, see
	 * that it has alपढ़ोy been set and thereक्रमe करो nothing. This proves
	 * that we call ->init_fs no more than once क्रम each super block.
	 *
	 * Combined together, the last two paragraphs prove the function
	 * correctness.
	 *
	 * Note that various cleancache callbacks may proceed beक्रमe this
	 * function is called or even concurrently with it, but since
	 * CLEANCACHE_NO_BACKEND is negative, they will all result in a noop
	 * until the corresponding ->init_fs has been actually called and
	 * cleancache_ops has been set.
	 */
	iterate_supers(cleancache_रेजिस्टर_ops_sb, शून्य);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cleancache_रेजिस्टर_ops);

/* Called by a cleancache-enabled fileप्रणाली at समय of mount */
व्योम __cleancache_init_fs(काष्ठा super_block *sb)
अणु
	पूर्णांक pool_id = CLEANCACHE_NO_BACKEND;

	अगर (cleancache_ops) अणु
		pool_id = cleancache_ops->init_fs(PAGE_SIZE);
		अगर (pool_id < 0)
			pool_id = CLEANCACHE_NO_POOL;
	पूर्ण
	sb->cleancache_poolid = pool_id;
पूर्ण
EXPORT_SYMBOL(__cleancache_init_fs);

/* Called by a cleancache-enabled clustered fileप्रणाली at समय of mount */
व्योम __cleancache_init_shared_fs(काष्ठा super_block *sb)
अणु
	पूर्णांक pool_id = CLEANCACHE_NO_BACKEND_SHARED;

	अगर (cleancache_ops) अणु
		pool_id = cleancache_ops->init_shared_fs(&sb->s_uuid, PAGE_SIZE);
		अगर (pool_id < 0)
			pool_id = CLEANCACHE_NO_POOL;
	पूर्ण
	sb->cleancache_poolid = pool_id;
पूर्ण
EXPORT_SYMBOL(__cleancache_init_shared_fs);

/*
 * If the fileप्रणाली uses exportable filehandles, use the filehandle as
 * the key, अन्यथा use the inode number.
 */
अटल पूर्णांक cleancache_get_key(काष्ठा inode *inode,
			      काष्ठा cleancache_filekey *key)
अणु
	पूर्णांक (*fhfn)(काष्ठा inode *, __u32 *fh, पूर्णांक *, काष्ठा inode *);
	पूर्णांक len = 0, maxlen = CLEANCACHE_KEY_MAX;
	काष्ठा super_block *sb = inode->i_sb;

	key->u.ino = inode->i_ino;
	अगर (sb->s_export_op != शून्य) अणु
		fhfn = sb->s_export_op->encode_fh;
		अगर  (fhfn) अणु
			len = (*fhfn)(inode, &key->u.fh[0], &maxlen, शून्य);
			अगर (len <= खाताID_ROOT || len == खाताID_INVALID)
				वापस -1;
			अगर (maxlen > CLEANCACHE_KEY_MAX)
				वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * "Get" data from cleancache associated with the poolid/inode/index
 * that were specअगरied when the data was put to cleanache and, अगर
 * successful, use it to fill the specअगरied page with data and वापस 0.
 * The pageframe is unchanged and वापसs -1 अगर the get fails.
 * Page must be locked by caller.
 *
 * The function has two checks beक्रमe any action is taken - whether
 * a backend is रेजिस्टरed and whether the sb->cleancache_poolid
 * is correct.
 */
पूर्णांक __cleancache_get_page(काष्ठा page *page)
अणु
	पूर्णांक ret = -1;
	पूर्णांक pool_id;
	काष्ठा cleancache_filekey key = अणु .u.key = अणु 0 पूर्ण पूर्ण;

	अगर (!cleancache_ops) अणु
		cleancache_failed_माला_लो++;
		जाओ out;
	पूर्ण

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	pool_id = page->mapping->host->i_sb->cleancache_poolid;
	अगर (pool_id < 0)
		जाओ out;

	अगर (cleancache_get_key(page->mapping->host, &key) < 0)
		जाओ out;

	ret = cleancache_ops->get_page(pool_id, key, page->index, page);
	अगर (ret == 0)
		cleancache_succ_माला_लो++;
	अन्यथा
		cleancache_failed_माला_लो++;
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__cleancache_get_page);

/*
 * "Put" data from a page to cleancache and associate it with the
 * (previously-obtained per-fileप्रणाली) poolid and the page's,
 * inode and page index.  Page must be locked.  Note that a put_page
 * always "succeeds", though a subsequent get_page may succeed or fail.
 *
 * The function has two checks beक्रमe any action is taken - whether
 * a backend is रेजिस्टरed and whether the sb->cleancache_poolid
 * is correct.
 */
व्योम __cleancache_put_page(काष्ठा page *page)
अणु
	पूर्णांक pool_id;
	काष्ठा cleancache_filekey key = अणु .u.key = अणु 0 पूर्ण पूर्ण;

	अगर (!cleancache_ops) अणु
		cleancache_माला_दो++;
		वापस;
	पूर्ण

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	pool_id = page->mapping->host->i_sb->cleancache_poolid;
	अगर (pool_id >= 0 &&
		cleancache_get_key(page->mapping->host, &key) >= 0) अणु
		cleancache_ops->put_page(pool_id, key, page->index, page);
		cleancache_माला_दो++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__cleancache_put_page);

/*
 * Invalidate any data from cleancache associated with the poolid and the
 * page's inode and page index so that a subsequent "get" will fail.
 *
 * The function has two checks beक्रमe any action is taken - whether
 * a backend is रेजिस्टरed and whether the sb->cleancache_poolid
 * is correct.
 */
व्योम __cleancache_invalidate_page(काष्ठा address_space *mapping,
					काष्ठा page *page)
अणु
	/* careful... page->mapping is शून्य someबार when this is called */
	पूर्णांक pool_id = mapping->host->i_sb->cleancache_poolid;
	काष्ठा cleancache_filekey key = अणु .u.key = अणु 0 पूर्ण पूर्ण;

	अगर (!cleancache_ops)
		वापस;

	अगर (pool_id >= 0) अणु
		VM_BUG_ON_PAGE(!PageLocked(page), page);
		अगर (cleancache_get_key(mapping->host, &key) >= 0) अणु
			cleancache_ops->invalidate_page(pool_id,
					key, page->index);
			cleancache_invalidates++;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__cleancache_invalidate_page);

/*
 * Invalidate all data from cleancache associated with the poolid and the
 * mappings's inode so that all subsequent माला_लो to this poolid/inode
 * will fail.
 *
 * The function has two checks beक्रमe any action is taken - whether
 * a backend is रेजिस्टरed and whether the sb->cleancache_poolid
 * is correct.
 */
व्योम __cleancache_invalidate_inode(काष्ठा address_space *mapping)
अणु
	पूर्णांक pool_id = mapping->host->i_sb->cleancache_poolid;
	काष्ठा cleancache_filekey key = अणु .u.key = अणु 0 पूर्ण पूर्ण;

	अगर (!cleancache_ops)
		वापस;

	अगर (pool_id >= 0 && cleancache_get_key(mapping->host, &key) >= 0)
		cleancache_ops->invalidate_inode(pool_id, key);
पूर्ण
EXPORT_SYMBOL(__cleancache_invalidate_inode);

/*
 * Called by any cleancache-enabled fileप्रणाली at समय of unmount;
 * note that pool_id is surrendered and may be वापसed by a subsequent
 * cleancache_init_fs or cleancache_init_shared_fs.
 */
व्योम __cleancache_invalidate_fs(काष्ठा super_block *sb)
अणु
	पूर्णांक pool_id;

	pool_id = sb->cleancache_poolid;
	sb->cleancache_poolid = CLEANCACHE_NO_POOL;

	अगर (cleancache_ops && pool_id >= 0)
		cleancache_ops->invalidate_fs(pool_id);
पूर्ण
EXPORT_SYMBOL(__cleancache_invalidate_fs);

अटल पूर्णांक __init init_cleancache(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *root = debugfs_create_dir("cleancache", शून्य);

	debugfs_create_u64("succ_gets", 0444, root, &cleancache_succ_माला_लो);
	debugfs_create_u64("failed_gets", 0444, root, &cleancache_failed_माला_लो);
	debugfs_create_u64("puts", 0444, root, &cleancache_माला_दो);
	debugfs_create_u64("invalidates", 0444, root, &cleancache_invalidates);
#पूर्ण_अगर
	वापस 0;
पूर्ण
module_init(init_cleancache)
