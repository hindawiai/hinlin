<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * V9FS cache definitions.
 *
 *  Copyright (C) 2009 by Abhishek Kulkarni <adkulkar@umail.iu.edu>
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <net/9p/9p.h>

#समावेश "v9fs.h"
#समावेश "cache.h"

#घोषणा CACHETAG_LEN  11

काष्ठा fscache_netfs v9fs_cache_netfs = अणु
	.name 		= "9p",
	.version 	= 0,
पूर्ण;

/**
 * v9fs_अक्रमom_cachetag - Generate a अक्रमom tag to be associated
 *			  with a new cache session.
 *
 * The value of jअगरfies is used क्रम a fairly अक्रमomly cache tag.
 */

अटल
पूर्णांक v9fs_अक्रमom_cachetag(काष्ठा v9fs_session_info *v9ses)
अणु
	v9ses->cachetag = kदो_स्मृति(CACHETAG_LEN, GFP_KERNEL);
	अगर (!v9ses->cachetag)
		वापस -ENOMEM;

	वापस scnम_लिखो(v9ses->cachetag, CACHETAG_LEN, "%lu", jअगरfies);
पूर्ण

स्थिर काष्ठा fscache_cookie_def v9fs_cache_session_index_def = अणु
	.name		= "9P.session",
	.type		= FSCACHE_COOKIE_TYPE_INDEX,
पूर्ण;

व्योम v9fs_cache_session_get_cookie(काष्ठा v9fs_session_info *v9ses)
अणु
	/* If no cache session tag was specअगरied, we generate a अक्रमom one. */
	अगर (!v9ses->cachetag) अणु
		अगर (v9fs_अक्रमom_cachetag(v9ses) < 0) अणु
			v9ses->fscache = शून्य;
			kमुक्त(v9ses->cachetag);
			v9ses->cachetag = शून्य;
			वापस;
		पूर्ण
	पूर्ण

	v9ses->fscache = fscache_acquire_cookie(v9fs_cache_netfs.primary_index,
						&v9fs_cache_session_index_def,
						v9ses->cachetag,
						म_माप(v9ses->cachetag),
						शून्य, 0,
						v9ses, 0, true);
	p9_debug(P9_DEBUG_FSC, "session %p get cookie %p\n",
		 v9ses, v9ses->fscache);
पूर्ण

व्योम v9fs_cache_session_put_cookie(काष्ठा v9fs_session_info *v9ses)
अणु
	p9_debug(P9_DEBUG_FSC, "session %p put cookie %p\n",
		 v9ses, v9ses->fscache);
	fscache_relinquish_cookie(v9ses->fscache, शून्य, false);
	v9ses->fscache = शून्य;
पूर्ण

अटल क्रमागत
fscache_checkaux v9fs_cache_inode_check_aux(व्योम *cookie_netfs_data,
					    स्थिर व्योम *buffer,
					    uपूर्णांक16_t buflen,
					    loff_t object_size)
अणु
	स्थिर काष्ठा v9fs_inode *v9inode = cookie_netfs_data;

	अगर (buflen != माप(v9inode->qid.version))
		वापस FSCACHE_CHECKAUX_OBSOLETE;

	अगर (स_भेद(buffer, &v9inode->qid.version,
		   माप(v9inode->qid.version)))
		वापस FSCACHE_CHECKAUX_OBSOLETE;

	वापस FSCACHE_CHECKAUX_OKAY;
पूर्ण

स्थिर काष्ठा fscache_cookie_def v9fs_cache_inode_index_def = अणु
	.name		= "9p.inode",
	.type		= FSCACHE_COOKIE_TYPE_DATAखाता,
	.check_aux	= v9fs_cache_inode_check_aux,
पूर्ण;

व्योम v9fs_cache_inode_get_cookie(काष्ठा inode *inode)
अणु
	काष्ठा v9fs_inode *v9inode;
	काष्ठा v9fs_session_info *v9ses;

	अगर (!S_ISREG(inode->i_mode))
		वापस;

	v9inode = V9FS_I(inode);
	अगर (v9inode->fscache)
		वापस;

	v9ses = v9fs_inode2v9ses(inode);
	v9inode->fscache = fscache_acquire_cookie(v9ses->fscache,
						  &v9fs_cache_inode_index_def,
						  &v9inode->qid.path,
						  माप(v9inode->qid.path),
						  &v9inode->qid.version,
						  माप(v9inode->qid.version),
						  v9inode,
						  i_size_पढ़ो(&v9inode->vfs_inode),
						  true);

	p9_debug(P9_DEBUG_FSC, "inode %p get cookie %p\n",
		 inode, v9inode->fscache);
पूर्ण

व्योम v9fs_cache_inode_put_cookie(काष्ठा inode *inode)
अणु
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);

	अगर (!v9inode->fscache)
		वापस;
	p9_debug(P9_DEBUG_FSC, "inode %p put cookie %p\n",
		 inode, v9inode->fscache);

	fscache_relinquish_cookie(v9inode->fscache, &v9inode->qid.version,
				  false);
	v9inode->fscache = शून्य;
पूर्ण

व्योम v9fs_cache_inode_flush_cookie(काष्ठा inode *inode)
अणु
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);

	अगर (!v9inode->fscache)
		वापस;
	p9_debug(P9_DEBUG_FSC, "inode %p flush cookie %p\n",
		 inode, v9inode->fscache);

	fscache_relinquish_cookie(v9inode->fscache, शून्य, true);
	v9inode->fscache = शून्य;
पूर्ण

व्योम v9fs_cache_inode_set_cookie(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);

	अगर (!v9inode->fscache)
		वापस;

	mutex_lock(&v9inode->fscache_lock);

	अगर ((filp->f_flags & O_ACCMODE) != O_RDONLY)
		v9fs_cache_inode_flush_cookie(inode);
	अन्यथा
		v9fs_cache_inode_get_cookie(inode);

	mutex_unlock(&v9inode->fscache_lock);
पूर्ण

व्योम v9fs_cache_inode_reset_cookie(काष्ठा inode *inode)
अणु
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा fscache_cookie *old;

	अगर (!v9inode->fscache)
		वापस;

	old = v9inode->fscache;

	mutex_lock(&v9inode->fscache_lock);
	fscache_relinquish_cookie(v9inode->fscache, शून्य, true);

	v9ses = v9fs_inode2v9ses(inode);
	v9inode->fscache = fscache_acquire_cookie(v9ses->fscache,
						  &v9fs_cache_inode_index_def,
						  &v9inode->qid.path,
						  माप(v9inode->qid.path),
						  &v9inode->qid.version,
						  माप(v9inode->qid.version),
						  v9inode,
						  i_size_पढ़ो(&v9inode->vfs_inode),
						  true);
	p9_debug(P9_DEBUG_FSC, "inode %p revalidating cookie old %p new %p\n",
		 inode, old, v9inode->fscache);

	mutex_unlock(&v9inode->fscache_lock);
पूर्ण

पूर्णांक __v9fs_fscache_release_page(काष्ठा page *page, gfp_t gfp)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);

	BUG_ON(!v9inode->fscache);

	वापस fscache_maybe_release_page(v9inode->fscache, page, gfp);
पूर्ण

व्योम __v9fs_fscache_invalidate_page(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);

	BUG_ON(!v9inode->fscache);

	अगर (PageFsCache(page)) अणु
		fscache_रुको_on_page_ग_लिखो(v9inode->fscache, page);
		BUG_ON(!PageLocked(page));
		fscache_uncache_page(v9inode->fscache, page);
	पूर्ण
पूर्ण

अटल व्योम v9fs_vfs_पढ़ोpage_complete(काष्ठा page *page, व्योम *data,
				       पूर्णांक error)
अणु
	अगर (!error)
		SetPageUptodate(page);

	unlock_page(page);
पूर्ण

/**
 * __v9fs_पढ़ोpage_from_fscache - पढ़ो a page from cache
 *
 * Returns 0 अगर the pages are in cache and a BIO is submitted,
 * 1 अगर the pages are not in cache and -error otherwise.
 */

पूर्णांक __v9fs_पढ़ोpage_from_fscache(काष्ठा inode *inode, काष्ठा page *page)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा v9fs_inode *v9inode = V9FS_I(inode);

	p9_debug(P9_DEBUG_FSC, "inode %p page %p\n", inode, page);
	अगर (!v9inode->fscache)
		वापस -ENOBUFS;

	ret = fscache_पढ़ो_or_alloc_page(v9inode->fscache,
					 page,
					 v9fs_vfs_पढ़ोpage_complete,
					 शून्य,
					 GFP_KERNEL);
	चयन (ret) अणु
	हाल -ENOBUFS:
	हाल -ENODATA:
		p9_debug(P9_DEBUG_FSC, "page/inode not in cache %d\n", ret);
		वापस 1;
	हाल 0:
		p9_debug(P9_DEBUG_FSC, "BIO submitted\n");
		वापस ret;
	शेष:
		p9_debug(P9_DEBUG_FSC, "ret %d\n", ret);
		वापस ret;
	पूर्ण
पूर्ण

/**
 * __v9fs_पढ़ोpages_from_fscache - पढ़ो multiple pages from cache
 *
 * Returns 0 अगर the pages are in cache and a BIO is submitted,
 * 1 अगर the pages are not in cache and -error otherwise.
 */

पूर्णांक __v9fs_पढ़ोpages_from_fscache(काष्ठा inode *inode,
				  काष्ठा address_space *mapping,
				  काष्ठा list_head *pages,
				  अचिन्हित *nr_pages)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा v9fs_inode *v9inode = V9FS_I(inode);

	p9_debug(P9_DEBUG_FSC, "inode %p pages %u\n", inode, *nr_pages);
	अगर (!v9inode->fscache)
		वापस -ENOBUFS;

	ret = fscache_पढ़ो_or_alloc_pages(v9inode->fscache,
					  mapping, pages, nr_pages,
					  v9fs_vfs_पढ़ोpage_complete,
					  शून्य,
					  mapping_gfp_mask(mapping));
	चयन (ret) अणु
	हाल -ENOBUFS:
	हाल -ENODATA:
		p9_debug(P9_DEBUG_FSC, "pages/inodes not in cache %d\n", ret);
		वापस 1;
	हाल 0:
		BUG_ON(!list_empty(pages));
		BUG_ON(*nr_pages != 0);
		p9_debug(P9_DEBUG_FSC, "BIO submitted\n");
		वापस ret;
	शेष:
		p9_debug(P9_DEBUG_FSC, "ret %d\n", ret);
		वापस ret;
	पूर्ण
पूर्ण

/**
 * __v9fs_पढ़ोpage_to_fscache - ग_लिखो a page to the cache
 *
 */

व्योम __v9fs_पढ़ोpage_to_fscache(काष्ठा inode *inode, काष्ठा page *page)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा v9fs_inode *v9inode = V9FS_I(inode);

	p9_debug(P9_DEBUG_FSC, "inode %p page %p\n", inode, page);
	ret = fscache_ग_लिखो_page(v9inode->fscache, page,
				 i_size_पढ़ो(&v9inode->vfs_inode), GFP_KERNEL);
	p9_debug(P9_DEBUG_FSC, "ret =  %d\n", ret);
	अगर (ret != 0)
		v9fs_uncache_page(inode, page);
पूर्ण

/*
 * रुको क्रम a page to complete writing to the cache
 */
व्योम __v9fs_fscache_रुको_on_page_ग_लिखो(काष्ठा inode *inode, काष्ठा page *page)
अणु
	स्थिर काष्ठा v9fs_inode *v9inode = V9FS_I(inode);
	p9_debug(P9_DEBUG_FSC, "inode %p page %p\n", inode, page);
	अगर (PageFsCache(page))
		fscache_रुको_on_page_ग_लिखो(v9inode->fscache, page);
पूर्ण
