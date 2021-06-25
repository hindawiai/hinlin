<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* NFS fileप्रणाली cache पूर्णांकerface definitions
 *
 * Copyright (C) 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _NFS_FSCACHE_H
#घोषणा _NFS_FSCACHE_H

#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/nfs4_mount.h>
#समावेश <linux/fscache.h>

#अगर_घोषित CONFIG_NFS_FSCACHE

/*
 * set of NFS FS-Cache objects that क्रमm a superblock key
 */
काष्ठा nfs_fscache_key अणु
	काष्ठा rb_node		node;
	काष्ठा nfs_client	*nfs_client;	/* the server */

	/* the elements of the unique key - as used by nfs_compare_super() and
	 * nfs_compare_mount_options() to distinguish superblocks */
	काष्ठा अणु
		काष्ठा अणु
			अचिन्हित दीर्घ	s_flags;	/* various flags
							 * (& NFS_MS_MASK) */
		पूर्ण super;

		काष्ठा अणु
			काष्ठा nfs_fsid fsid;
			पूर्णांक		flags;
			अचिन्हित पूर्णांक	rsize;		/* पढ़ो size */
			अचिन्हित पूर्णांक	wsize;		/* ग_लिखो size */
			अचिन्हित पूर्णांक	acregmin;	/* attr cache समयouts */
			अचिन्हित पूर्णांक	acregmax;
			अचिन्हित पूर्णांक	acdirmin;
			अचिन्हित पूर्णांक	acdirmax;
		पूर्ण nfs_server;

		काष्ठा अणु
			rpc_authflavor_t au_flavor;
		पूर्ण rpc_auth;

		/* uniquअगरier - can be used अगर nfs_server.flags includes
		 * NFS_MOUNT_UNSHARED  */
		u8 uniq_len;
		अक्षर uniquअगरier[0];
	पूर्ण key;
पूर्ण;

/*
 * Definition of the auxiliary data attached to NFS inode storage objects
 * within the cache.
 *
 * The contents of this काष्ठा are recorded in the on-disk local cache in the
 * auxiliary data attached to the data storage object backing an inode.  This
 * permits coherency to be managed when a new inode binds to an alपढ़ोy extant
 * cache object.
 */
काष्ठा nfs_fscache_inode_auxdata अणु
	s64	mसमय_sec;
	s64	mसमय_nsec;
	s64	स_समय_sec;
	s64	स_समय_nsec;
	u64	change_attr;
पूर्ण;

/*
 * fscache-index.c
 */
बाह्य काष्ठा fscache_netfs nfs_fscache_netfs;
बाह्य स्थिर काष्ठा fscache_cookie_def nfs_fscache_server_index_def;
बाह्य स्थिर काष्ठा fscache_cookie_def nfs_fscache_super_index_def;
बाह्य स्थिर काष्ठा fscache_cookie_def nfs_fscache_inode_object_def;

बाह्य पूर्णांक nfs_fscache_रेजिस्टर(व्योम);
बाह्य व्योम nfs_fscache_unरेजिस्टर(व्योम);

/*
 * fscache.c
 */
बाह्य व्योम nfs_fscache_get_client_cookie(काष्ठा nfs_client *);
बाह्य व्योम nfs_fscache_release_client_cookie(काष्ठा nfs_client *);

बाह्य व्योम nfs_fscache_get_super_cookie(काष्ठा super_block *, स्थिर अक्षर *, पूर्णांक);
बाह्य व्योम nfs_fscache_release_super_cookie(काष्ठा super_block *);

बाह्य व्योम nfs_fscache_init_inode(काष्ठा inode *);
बाह्य व्योम nfs_fscache_clear_inode(काष्ठा inode *);
बाह्य व्योम nfs_fscache_खोलो_file(काष्ठा inode *, काष्ठा file *);

बाह्य व्योम __nfs_fscache_invalidate_page(काष्ठा page *, काष्ठा inode *);
बाह्य पूर्णांक nfs_fscache_release_page(काष्ठा page *, gfp_t);

बाह्य पूर्णांक __nfs_पढ़ोpage_from_fscache(काष्ठा nfs_खोलो_context *,
				       काष्ठा inode *, काष्ठा page *);
बाह्य पूर्णांक __nfs_पढ़ोpages_from_fscache(काष्ठा nfs_खोलो_context *,
					काष्ठा inode *, काष्ठा address_space *,
					काष्ठा list_head *, अचिन्हित *);
बाह्य व्योम __nfs_पढ़ोpage_to_fscache(काष्ठा inode *, काष्ठा page *, पूर्णांक);

/*
 * रुको क्रम a page to complete writing to the cache
 */
अटल अंतरभूत व्योम nfs_fscache_रुको_on_page_ग_लिखो(काष्ठा nfs_inode *nfsi,
						  काष्ठा page *page)
अणु
	अगर (PageFsCache(page))
		fscache_रुको_on_page_ग_लिखो(nfsi->fscache, page);
पूर्ण

/*
 * release the caching state associated with a page अगर undergoing complete page
 * invalidation
 */
अटल अंतरभूत व्योम nfs_fscache_invalidate_page(काष्ठा page *page,
					       काष्ठा inode *inode)
अणु
	अगर (PageFsCache(page))
		__nfs_fscache_invalidate_page(page, inode);
पूर्ण

/*
 * Retrieve a page from an inode data storage object.
 */
अटल अंतरभूत पूर्णांक nfs_पढ़ोpage_from_fscache(काष्ठा nfs_खोलो_context *ctx,
					    काष्ठा inode *inode,
					    काष्ठा page *page)
अणु
	अगर (NFS_I(inode)->fscache)
		वापस __nfs_पढ़ोpage_from_fscache(ctx, inode, page);
	वापस -ENOBUFS;
पूर्ण

/*
 * Retrieve a set of pages from an inode data storage object.
 */
अटल अंतरभूत पूर्णांक nfs_पढ़ोpages_from_fscache(काष्ठा nfs_खोलो_context *ctx,
					     काष्ठा inode *inode,
					     काष्ठा address_space *mapping,
					     काष्ठा list_head *pages,
					     अचिन्हित *nr_pages)
अणु
	अगर (NFS_I(inode)->fscache)
		वापस __nfs_पढ़ोpages_from_fscache(ctx, inode, mapping, pages,
						    nr_pages);
	वापस -ENOBUFS;
पूर्ण

/*
 * Store a page newly fetched from the server in an inode data storage object
 * in the cache.
 */
अटल अंतरभूत व्योम nfs_पढ़ोpage_to_fscache(काष्ठा inode *inode,
					   काष्ठा page *page,
					   पूर्णांक sync)
अणु
	अगर (PageFsCache(page))
		__nfs_पढ़ोpage_to_fscache(inode, page, sync);
पूर्ण

/*
 * Invalidate the contents of fscache क्रम this inode.  This will not sleep.
 */
अटल अंतरभूत व्योम nfs_fscache_invalidate(काष्ठा inode *inode)
अणु
	fscache_invalidate(NFS_I(inode)->fscache);
पूर्ण

/*
 * Wait क्रम an object to finish being invalidated.
 */
अटल अंतरभूत व्योम nfs_fscache_रुको_on_invalidate(काष्ठा inode *inode)
अणु
	fscache_रुको_on_invalidate(NFS_I(inode)->fscache);
पूर्ण

/*
 * indicate the client caching state as पढ़ोable text
 */
अटल अंतरभूत स्थिर अक्षर *nfs_server_fscache_state(काष्ठा nfs_server *server)
अणु
	अगर (server->fscache)
		वापस "yes";
	वापस "no ";
पूर्ण

#अन्यथा /* CONFIG_NFS_FSCACHE */
अटल अंतरभूत पूर्णांक nfs_fscache_रेजिस्टर(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम nfs_fscache_unरेजिस्टर(व्योम) अणुपूर्ण

अटल अंतरभूत व्योम nfs_fscache_get_client_cookie(काष्ठा nfs_client *clp) अणुपूर्ण
अटल अंतरभूत व्योम nfs_fscache_release_client_cookie(काष्ठा nfs_client *clp) अणुपूर्ण

अटल अंतरभूत व्योम nfs_fscache_release_super_cookie(काष्ठा super_block *sb) अणुपूर्ण

अटल अंतरभूत व्योम nfs_fscache_init_inode(काष्ठा inode *inode) अणुपूर्ण
अटल अंतरभूत व्योम nfs_fscache_clear_inode(काष्ठा inode *inode) अणुपूर्ण
अटल अंतरभूत व्योम nfs_fscache_खोलो_file(काष्ठा inode *inode,
					 काष्ठा file *filp) अणुपूर्ण

अटल अंतरभूत पूर्णांक nfs_fscache_release_page(काष्ठा page *page, gfp_t gfp)
अणु
	वापस 1; /* True: may release page */
पूर्ण
अटल अंतरभूत व्योम nfs_fscache_invalidate_page(काष्ठा page *page,
					       काष्ठा inode *inode) अणुपूर्ण
अटल अंतरभूत व्योम nfs_fscache_रुको_on_page_ग_लिखो(काष्ठा nfs_inode *nfsi,
						  काष्ठा page *page) अणुपूर्ण

अटल अंतरभूत पूर्णांक nfs_पढ़ोpage_from_fscache(काष्ठा nfs_खोलो_context *ctx,
					    काष्ठा inode *inode,
					    काष्ठा page *page)
अणु
	वापस -ENOBUFS;
पूर्ण
अटल अंतरभूत पूर्णांक nfs_पढ़ोpages_from_fscache(काष्ठा nfs_खोलो_context *ctx,
					     काष्ठा inode *inode,
					     काष्ठा address_space *mapping,
					     काष्ठा list_head *pages,
					     अचिन्हित *nr_pages)
अणु
	वापस -ENOBUFS;
पूर्ण
अटल अंतरभूत व्योम nfs_पढ़ोpage_to_fscache(काष्ठा inode *inode,
					   काष्ठा page *page, पूर्णांक sync) अणुपूर्ण


अटल अंतरभूत व्योम nfs_fscache_invalidate(काष्ठा inode *inode) अणुपूर्ण
अटल अंतरभूत व्योम nfs_fscache_रुको_on_invalidate(काष्ठा inode *inode) अणुपूर्ण

अटल अंतरभूत स्थिर अक्षर *nfs_server_fscache_state(काष्ठा nfs_server *server)
अणु
	वापस "no ";
पूर्ण

#पूर्ण_अगर /* CONFIG_NFS_FSCACHE */
#पूर्ण_अगर /* _NFS_FSCACHE_H */
