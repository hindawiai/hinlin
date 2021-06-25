<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* NFS fileप्रणाली cache पूर्णांकerface
 *
 * Copyright (C) 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_fs_sb.h>
#समावेश <linux/in6.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/iversion.h>

#समावेश "internal.h"
#समावेश "iostat.h"
#समावेश "fscache.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_FSCACHE

अटल काष्ठा rb_root nfs_fscache_keys = RB_ROOT;
अटल DEFINE_SPINLOCK(nfs_fscache_keys_lock);

/*
 * Layout of the key क्रम an NFS server cache object.
 */
काष्ठा nfs_server_key अणु
	काष्ठा अणु
		uपूर्णांक16_t	nfsversion;		/* NFS protocol version */
		uपूर्णांक32_t	minorversion;		/* NFSv4 minor version */
		uपूर्णांक16_t	family;			/* address family */
		__be16		port;			/* IP port */
	पूर्ण hdr;
	जोड़ अणु
		काष्ठा in_addr	ipv4_addr;	/* IPv4 address */
		काष्ठा in6_addr ipv6_addr;	/* IPv6 address */
	पूर्ण;
पूर्ण __packed;

/*
 * Get the per-client index cookie क्रम an NFS client अगर the appropriate mount
 * flag was set
 * - We always try and get an index cookie क्रम the client, but get filehandle
 *   cookies on a per-superblock basis, depending on the mount flags
 */
व्योम nfs_fscache_get_client_cookie(काष्ठा nfs_client *clp)
अणु
	स्थिर काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *) &clp->cl_addr;
	स्थिर काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *) &clp->cl_addr;
	काष्ठा nfs_server_key key;
	uपूर्णांक16_t len = माप(key.hdr);

	स_रखो(&key, 0, माप(key));
	key.hdr.nfsversion = clp->rpc_ops->version;
	key.hdr.minorversion = clp->cl_minorversion;
	key.hdr.family = clp->cl_addr.ss_family;

	चयन (clp->cl_addr.ss_family) अणु
	हाल AF_INET:
		key.hdr.port = sin->sin_port;
		key.ipv4_addr = sin->sin_addr;
		len += माप(key.ipv4_addr);
		अवरोध;

	हाल AF_INET6:
		key.hdr.port = sin6->sin6_port;
		key.ipv6_addr = sin6->sin6_addr;
		len += माप(key.ipv6_addr);
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_WARNING "NFS: Unknown network family '%d'\n",
		       clp->cl_addr.ss_family);
		clp->fscache = शून्य;
		वापस;
	पूर्ण

	/* create a cache index क्रम looking up filehandles */
	clp->fscache = fscache_acquire_cookie(nfs_fscache_netfs.primary_index,
					      &nfs_fscache_server_index_def,
					      &key, len,
					      शून्य, 0,
					      clp, 0, true);
	dfprपूर्णांकk(FSCACHE, "NFS: get client cookie (0x%p/0x%p)\n",
		 clp, clp->fscache);
पूर्ण

/*
 * Dispose of a per-client cookie
 */
व्योम nfs_fscache_release_client_cookie(काष्ठा nfs_client *clp)
अणु
	dfprपूर्णांकk(FSCACHE, "NFS: releasing client cookie (0x%p/0x%p)\n",
		 clp, clp->fscache);

	fscache_relinquish_cookie(clp->fscache, शून्य, false);
	clp->fscache = शून्य;
पूर्ण

/*
 * Get the cache cookie क्रम an NFS superblock.  We have to handle
 * uniquअगरication here because the cache करोesn't करो it क्रम us.
 *
 * The शेष uniquअगरier is just an empty string, but it may be overridden
 * either by the 'fsc=xxx' option to mount, or by inheriting it from the parent
 * superblock across an स्वतःmount poपूर्णांक of some nature.
 */
व्योम nfs_fscache_get_super_cookie(काष्ठा super_block *sb, स्थिर अक्षर *uniq, पूर्णांक ulen)
अणु
	काष्ठा nfs_fscache_key *key, *xkey;
	काष्ठा nfs_server *nfss = NFS_SB(sb);
	काष्ठा rb_node **p, *parent;
	पूर्णांक dअगरf;

	nfss->fscache_key = शून्य;
	nfss->fscache = शून्य;
	अगर (!uniq) अणु
		uniq = "";
		ulen = 1;
	पूर्ण

	key = kzalloc(माप(*key) + ulen, GFP_KERNEL);
	अगर (!key)
		वापस;

	key->nfs_client = nfss->nfs_client;
	key->key.super.s_flags = sb->s_flags & NFS_SB_MASK;
	key->key.nfs_server.flags = nfss->flags;
	key->key.nfs_server.rsize = nfss->rsize;
	key->key.nfs_server.wsize = nfss->wsize;
	key->key.nfs_server.acregmin = nfss->acregmin;
	key->key.nfs_server.acregmax = nfss->acregmax;
	key->key.nfs_server.acdirmin = nfss->acdirmin;
	key->key.nfs_server.acdirmax = nfss->acdirmax;
	key->key.nfs_server.fsid = nfss->fsid;
	key->key.rpc_auth.au_flavor = nfss->client->cl_auth->au_flavor;

	key->key.uniq_len = ulen;
	स_नकल(key->key.uniquअगरier, uniq, ulen);

	spin_lock(&nfs_fscache_keys_lock);
	p = &nfs_fscache_keys.rb_node;
	parent = शून्य;
	जबतक (*p) अणु
		parent = *p;
		xkey = rb_entry(parent, काष्ठा nfs_fscache_key, node);

		अगर (key->nfs_client < xkey->nfs_client)
			जाओ go_left;
		अगर (key->nfs_client > xkey->nfs_client)
			जाओ go_right;

		dअगरf = स_भेद(&key->key, &xkey->key, माप(key->key));
		अगर (dअगरf < 0)
			जाओ go_left;
		अगर (dअगरf > 0)
			जाओ go_right;

		अगर (key->key.uniq_len == 0)
			जाओ non_unique;
		dअगरf = स_भेद(key->key.uniquअगरier,
			      xkey->key.uniquअगरier,
			      key->key.uniq_len);
		अगर (dअगरf < 0)
			जाओ go_left;
		अगर (dअगरf > 0)
			जाओ go_right;
		जाओ non_unique;

	go_left:
		p = &(*p)->rb_left;
		जारी;
	go_right:
		p = &(*p)->rb_right;
	पूर्ण

	rb_link_node(&key->node, parent, p);
	rb_insert_color(&key->node, &nfs_fscache_keys);
	spin_unlock(&nfs_fscache_keys_lock);
	nfss->fscache_key = key;

	/* create a cache index क्रम looking up filehandles */
	nfss->fscache = fscache_acquire_cookie(nfss->nfs_client->fscache,
					       &nfs_fscache_super_index_def,
					       &key->key,
					       माप(key->key) + ulen,
					       शून्य, 0,
					       nfss, 0, true);
	dfprपूर्णांकk(FSCACHE, "NFS: get superblock cookie (0x%p/0x%p)\n",
		 nfss, nfss->fscache);
	वापस;

non_unique:
	spin_unlock(&nfs_fscache_keys_lock);
	kमुक्त(key);
	nfss->fscache_key = शून्य;
	nfss->fscache = शून्य;
	prपूर्णांकk(KERN_WARNING "NFS:"
	       " Cache request denied due to non-unique superblock keys\n");
पूर्ण

/*
 * release a per-superblock cookie
 */
व्योम nfs_fscache_release_super_cookie(काष्ठा super_block *sb)
अणु
	काष्ठा nfs_server *nfss = NFS_SB(sb);

	dfprपूर्णांकk(FSCACHE, "NFS: releasing superblock cookie (0x%p/0x%p)\n",
		 nfss, nfss->fscache);

	fscache_relinquish_cookie(nfss->fscache, शून्य, false);
	nfss->fscache = शून्य;

	अगर (nfss->fscache_key) अणु
		spin_lock(&nfs_fscache_keys_lock);
		rb_erase(&nfss->fscache_key->node, &nfs_fscache_keys);
		spin_unlock(&nfs_fscache_keys_lock);
		kमुक्त(nfss->fscache_key);
		nfss->fscache_key = शून्य;
	पूर्ण
पूर्ण

अटल व्योम nfs_fscache_update_auxdata(काष्ठा nfs_fscache_inode_auxdata *auxdata,
				  काष्ठा nfs_inode *nfsi)
अणु
	स_रखो(auxdata, 0, माप(*auxdata));
	auxdata->mसमय_sec  = nfsi->vfs_inode.i_mसमय.tv_sec;
	auxdata->mसमय_nsec = nfsi->vfs_inode.i_mसमय.tv_nsec;
	auxdata->स_समय_sec  = nfsi->vfs_inode.i_स_समय.tv_sec;
	auxdata->स_समय_nsec = nfsi->vfs_inode.i_स_समय.tv_nsec;

	अगर (NFS_SERVER(&nfsi->vfs_inode)->nfs_client->rpc_ops->version == 4)
		auxdata->change_attr = inode_peek_iversion_raw(&nfsi->vfs_inode);
पूर्ण

/*
 * Initialise the per-inode cache cookie poपूर्णांकer क्रम an NFS inode.
 */
व्योम nfs_fscache_init_inode(काष्ठा inode *inode)
अणु
	काष्ठा nfs_fscache_inode_auxdata auxdata;
	काष्ठा nfs_server *nfss = NFS_SERVER(inode);
	काष्ठा nfs_inode *nfsi = NFS_I(inode);

	nfsi->fscache = शून्य;
	अगर (!(nfss->fscache && S_ISREG(inode->i_mode)))
		वापस;

	nfs_fscache_update_auxdata(&auxdata, nfsi);

	nfsi->fscache = fscache_acquire_cookie(NFS_SB(inode->i_sb)->fscache,
					       &nfs_fscache_inode_object_def,
					       nfsi->fh.data, nfsi->fh.size,
					       &auxdata, माप(auxdata),
					       nfsi, nfsi->vfs_inode.i_size, false);
पूर्ण

/*
 * Release a per-inode cookie.
 */
व्योम nfs_fscache_clear_inode(काष्ठा inode *inode)
अणु
	काष्ठा nfs_fscache_inode_auxdata auxdata;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा fscache_cookie *cookie = nfs_i_fscache(inode);

	dfprपूर्णांकk(FSCACHE, "NFS: clear cookie (0x%p/0x%p)\n", nfsi, cookie);

	nfs_fscache_update_auxdata(&auxdata, nfsi);
	fscache_relinquish_cookie(cookie, &auxdata, false);
	nfsi->fscache = शून्य;
पूर्ण

अटल bool nfs_fscache_can_enable(व्योम *data)
अणु
	काष्ठा inode *inode = data;

	वापस !inode_is_खोलो_क्रम_ग_लिखो(inode);
पूर्ण

/*
 * Enable or disable caching क्रम a file that is being खोलोed as appropriate.
 * The cookie is allocated when the inode is initialised, but is not enabled at
 * that समय.  Enablement is deferred to file-खोलो समय to aव्योम stat() and
 * access() thrashing the cache.
 *
 * For now, with NFS, only regular files that are खोलो पढ़ो-only will be able
 * to use the cache.
 *
 * We enable the cache क्रम an inode अगर we खोलो it पढ़ो-only and it isn't
 * currently खोलो क्रम writing.  We disable the cache अगर the inode is खोलो
 * ग_लिखो-only.
 *
 * The caller uses the file काष्ठा to pin i_ग_लिखोcount on the inode beक्रमe
 * calling us when a file is खोलोed क्रम writing, so we can make use of that.
 *
 * Note that this may be invoked multiple बार in parallel by parallel
 * nfs_खोलो() functions.
 */
व्योम nfs_fscache_खोलो_file(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा nfs_fscache_inode_auxdata auxdata;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा fscache_cookie *cookie = nfs_i_fscache(inode);

	अगर (!fscache_cookie_valid(cookie))
		वापस;

	nfs_fscache_update_auxdata(&auxdata, nfsi);

	अगर (inode_is_खोलो_क्रम_ग_लिखो(inode)) अणु
		dfprपूर्णांकk(FSCACHE, "NFS: nfsi 0x%p disabling cache\n", nfsi);
		clear_bit(NFS_INO_FSCACHE, &nfsi->flags);
		fscache_disable_cookie(cookie, &auxdata, true);
		fscache_uncache_all_inode_pages(cookie, inode);
	पूर्ण अन्यथा अणु
		dfprपूर्णांकk(FSCACHE, "NFS: nfsi 0x%p enabling cache\n", nfsi);
		fscache_enable_cookie(cookie, &auxdata, nfsi->vfs_inode.i_size,
				      nfs_fscache_can_enable, inode);
		अगर (fscache_cookie_enabled(cookie))
			set_bit(NFS_INO_FSCACHE, &NFS_I(inode)->flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nfs_fscache_खोलो_file);

/*
 * Release the caching state associated with a page, अगर the page isn't busy
 * पूर्णांकeracting with the cache.
 * - Returns true (can release page) or false (page busy).
 */
पूर्णांक nfs_fscache_release_page(काष्ठा page *page, gfp_t gfp)
अणु
	अगर (PageFsCache(page)) अणु
		काष्ठा fscache_cookie *cookie = nfs_i_fscache(page->mapping->host);

		BUG_ON(!cookie);
		dfprपूर्णांकk(FSCACHE, "NFS: fscache releasepage (0x%p/0x%p/0x%p)\n",
			 cookie, page, NFS_I(page->mapping->host));

		अगर (!fscache_maybe_release_page(cookie, page, gfp))
			वापस 0;

		nfs_inc_fscache_stats(page->mapping->host,
				      NFSIOS_FSCACHE_PAGES_UNCACHED);
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Release the caching state associated with a page अगर undergoing complete page
 * invalidation.
 */
व्योम __nfs_fscache_invalidate_page(काष्ठा page *page, काष्ठा inode *inode)
अणु
	काष्ठा fscache_cookie *cookie = nfs_i_fscache(inode);

	BUG_ON(!cookie);

	dfprपूर्णांकk(FSCACHE, "NFS: fscache invalidatepage (0x%p/0x%p/0x%p)\n",
		 cookie, page, NFS_I(inode));

	fscache_रुको_on_page_ग_लिखो(cookie, page);

	BUG_ON(!PageLocked(page));
	fscache_uncache_page(cookie, page);
	nfs_inc_fscache_stats(page->mapping->host,
			      NFSIOS_FSCACHE_PAGES_UNCACHED);
पूर्ण

/*
 * Handle completion of a page being पढ़ो from the cache.
 * - Called in process (keventd) context.
 */
अटल व्योम nfs_पढ़ोpage_from_fscache_complete(काष्ठा page *page,
					       व्योम *context,
					       पूर्णांक error)
अणु
	dfprपूर्णांकk(FSCACHE,
		 "NFS: readpage_from_fscache_complete (0x%p/0x%p/%d)\n",
		 page, context, error);

	/* अगर the पढ़ो completes with an error, we just unlock the page and let
	 * the VM reissue the पढ़ोpage */
	अगर (!error) अणु
		SetPageUptodate(page);
		unlock_page(page);
	पूर्ण
पूर्ण

/*
 * Retrieve a page from fscache
 */
पूर्णांक __nfs_पढ़ोpage_from_fscache(काष्ठा nfs_खोलो_context *ctx,
				काष्ठा inode *inode, काष्ठा page *page)
अणु
	पूर्णांक ret;

	dfprपूर्णांकk(FSCACHE,
		 "NFS: readpage_from_fscache(fsc:%p/p:%p(i:%lx f:%lx)/0x%p)\n",
		 nfs_i_fscache(inode), page, page->index, page->flags, inode);

	ret = fscache_पढ़ो_or_alloc_page(nfs_i_fscache(inode),
					 page,
					 nfs_पढ़ोpage_from_fscache_complete,
					 ctx,
					 GFP_KERNEL);

	चयन (ret) अणु
	हाल 0: /* पढ़ो BIO submitted (page in fscache) */
		dfprपूर्णांकk(FSCACHE,
			 "NFS:    readpage_from_fscache: BIO submitted\n");
		nfs_inc_fscache_stats(inode, NFSIOS_FSCACHE_PAGES_READ_OK);
		वापस ret;

	हाल -ENOBUFS: /* inode not in cache */
	हाल -ENODATA: /* page not in cache */
		nfs_inc_fscache_stats(inode, NFSIOS_FSCACHE_PAGES_READ_FAIL);
		dfprपूर्णांकk(FSCACHE,
			 "NFS:    readpage_from_fscache %d\n", ret);
		वापस 1;

	शेष:
		dfprपूर्णांकk(FSCACHE, "NFS:    readpage_from_fscache %d\n", ret);
		nfs_inc_fscache_stats(inode, NFSIOS_FSCACHE_PAGES_READ_FAIL);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Retrieve a set of pages from fscache
 */
पूर्णांक __nfs_पढ़ोpages_from_fscache(काष्ठा nfs_खोलो_context *ctx,
				 काष्ठा inode *inode,
				 काष्ठा address_space *mapping,
				 काष्ठा list_head *pages,
				 अचिन्हित *nr_pages)
अणु
	अचिन्हित npages = *nr_pages;
	पूर्णांक ret;

	dfprपूर्णांकk(FSCACHE, "NFS: nfs_getpages_from_fscache (0x%p/%u/0x%p)\n",
		 nfs_i_fscache(inode), npages, inode);

	ret = fscache_पढ़ो_or_alloc_pages(nfs_i_fscache(inode),
					  mapping, pages, nr_pages,
					  nfs_पढ़ोpage_from_fscache_complete,
					  ctx,
					  mapping_gfp_mask(mapping));
	अगर (*nr_pages < npages)
		nfs_add_fscache_stats(inode, NFSIOS_FSCACHE_PAGES_READ_OK,
				      npages);
	अगर (*nr_pages > 0)
		nfs_add_fscache_stats(inode, NFSIOS_FSCACHE_PAGES_READ_FAIL,
				      *nr_pages);

	चयन (ret) अणु
	हाल 0: /* पढ़ो submitted to the cache क्रम all pages */
		BUG_ON(!list_empty(pages));
		BUG_ON(*nr_pages != 0);
		dfprपूर्णांकk(FSCACHE,
			 "NFS: nfs_getpages_from_fscache: submitted\n");

		वापस ret;

	हाल -ENOBUFS: /* some pages aren't cached and can't be */
	हाल -ENODATA: /* some pages aren't cached */
		dfprपूर्णांकk(FSCACHE,
			 "NFS: nfs_getpages_from_fscache: no page: %d\n", ret);
		वापस 1;

	शेष:
		dfprपूर्णांकk(FSCACHE,
			 "NFS: nfs_getpages_from_fscache: ret  %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Store a newly fetched page in fscache
 * - PG_fscache must be set on the page
 */
व्योम __nfs_पढ़ोpage_to_fscache(काष्ठा inode *inode, काष्ठा page *page, पूर्णांक sync)
अणु
	पूर्णांक ret;

	dfprपूर्णांकk(FSCACHE,
		 "NFS: readpage_to_fscache(fsc:%p/p:%p(i:%lx f:%lx)/%d)\n",
		 nfs_i_fscache(inode), page, page->index, page->flags, sync);

	ret = fscache_ग_लिखो_page(nfs_i_fscache(inode), page,
				 inode->i_size, GFP_KERNEL);
	dfprपूर्णांकk(FSCACHE,
		 "NFS:     readpage_to_fscache: p:%p(i:%lu f:%lx) ret %d\n",
		 page, page->index, page->flags, ret);

	अगर (ret != 0) अणु
		fscache_uncache_page(nfs_i_fscache(inode), page);
		nfs_inc_fscache_stats(inode,
				      NFSIOS_FSCACHE_PAGES_WRITTEN_FAIL);
		nfs_inc_fscache_stats(inode, NFSIOS_FSCACHE_PAGES_UNCACHED);
	पूर्ण अन्यथा अणु
		nfs_inc_fscache_stats(inode,
				      NFSIOS_FSCACHE_PAGES_WRITTEN_OK);
	पूर्ण
पूर्ण
