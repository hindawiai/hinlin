<शैली गुरु>
/*
 *   fs/cअगरs/fscache.c - CIFS fileप्रणाली cache पूर्णांकerface
 *
 *   Copyright (c) 2010 Novell, Inc.
 *   Author(s): Suresh Jayaraman <sjayaraman@suse.de>
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#समावेश "fscache.h"
#समावेश "cifsglob.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_fs_sb.h"
#समावेश "cifsproto.h"

/*
 * Key layout of CIFS server cache index object
 */
काष्ठा cअगरs_server_key अणु
	काष्ठा अणु
		uपूर्णांक16_t	family;		/* address family */
		__be16		port;		/* IP port */
	पूर्ण hdr;
	जोड़ अणु
		काष्ठा in_addr	ipv4_addr;
		काष्ठा in6_addr	ipv6_addr;
	पूर्ण;
पूर्ण __packed;

/*
 * Get a cookie क्रम a server object keyed by अणुIPaddress,port,familyपूर्ण tuple
 */
व्योम cअगरs_fscache_get_client_cookie(काष्ठा TCP_Server_Info *server)
अणु
	स्थिर काष्ठा sockaddr *sa = (काष्ठा sockaddr *) &server->dstaddr;
	स्थिर काष्ठा sockaddr_in *addr = (काष्ठा sockaddr_in *) sa;
	स्थिर काष्ठा sockaddr_in6 *addr6 = (काष्ठा sockaddr_in6 *) sa;
	काष्ठा cअगरs_server_key key;
	uपूर्णांक16_t key_len = माप(key.hdr);

	स_रखो(&key, 0, माप(key));

	/*
	 * Should not be a problem as sin_family/sin6_family overlays
	 * sa_family field
	 */
	key.hdr.family = sa->sa_family;
	चयन (sa->sa_family) अणु
	हाल AF_INET:
		key.hdr.port = addr->sin_port;
		key.ipv4_addr = addr->sin_addr;
		key_len += माप(key.ipv4_addr);
		अवरोध;

	हाल AF_INET6:
		key.hdr.port = addr6->sin6_port;
		key.ipv6_addr = addr6->sin6_addr;
		key_len += माप(key.ipv6_addr);
		अवरोध;

	शेष:
		cअगरs_dbg(VFS, "Unknown network family '%d'\n", sa->sa_family);
		server->fscache = शून्य;
		वापस;
	पूर्ण

	server->fscache =
		fscache_acquire_cookie(cअगरs_fscache_netfs.primary_index,
				       &cअगरs_fscache_server_index_def,
				       &key, key_len,
				       शून्य, 0,
				       server, 0, true);
	cअगरs_dbg(FYI, "%s: (0x%p/0x%p)\n",
		 __func__, server, server->fscache);
पूर्ण

व्योम cअगरs_fscache_release_client_cookie(काष्ठा TCP_Server_Info *server)
अणु
	cअगरs_dbg(FYI, "%s: (0x%p/0x%p)\n",
		 __func__, server, server->fscache);
	fscache_relinquish_cookie(server->fscache, शून्य, false);
	server->fscache = शून्य;
पूर्ण

व्योम cअगरs_fscache_get_super_cookie(काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	अक्षर *shaनाम;
	काष्ठा cअगरs_fscache_super_auxdata auxdata;

	shaनाम = extract_shaनाम(tcon->treeName);
	अगर (IS_ERR(shaनाम)) अणु
		cअगरs_dbg(FYI, "%s: couldn't extract sharename\n", __func__);
		tcon->fscache = शून्य;
		वापस;
	पूर्ण

	स_रखो(&auxdata, 0, माप(auxdata));
	auxdata.resource_id = tcon->resource_id;
	auxdata.vol_create_समय = tcon->vol_create_समय;
	auxdata.vol_serial_number = tcon->vol_serial_number;

	tcon->fscache =
		fscache_acquire_cookie(server->fscache,
				       &cअगरs_fscache_super_index_def,
				       shaनाम, म_माप(shaनाम),
				       &auxdata, माप(auxdata),
				       tcon, 0, true);
	kमुक्त(shaनाम);
	cअगरs_dbg(FYI, "%s: (0x%p/0x%p)\n",
		 __func__, server->fscache, tcon->fscache);
पूर्ण

व्योम cअगरs_fscache_release_super_cookie(काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा cअगरs_fscache_super_auxdata auxdata;

	स_रखो(&auxdata, 0, माप(auxdata));
	auxdata.resource_id = tcon->resource_id;
	auxdata.vol_create_समय = tcon->vol_create_समय;
	auxdata.vol_serial_number = tcon->vol_serial_number;

	cअगरs_dbg(FYI, "%s: (0x%p)\n", __func__, tcon->fscache);
	fscache_relinquish_cookie(tcon->fscache, &auxdata, false);
	tcon->fscache = शून्य;
पूर्ण

अटल व्योम cअगरs_fscache_acquire_inode_cookie(काष्ठा cअगरsInodeInfo *cअगरsi,
					      काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा cअगरs_fscache_inode_auxdata auxdata;

	स_रखो(&auxdata, 0, माप(auxdata));
	auxdata.eof = cअगरsi->server_eof;
	auxdata.last_ग_लिखो_समय_sec = cअगरsi->vfs_inode.i_mसमय.tv_sec;
	auxdata.last_change_समय_sec = cअगरsi->vfs_inode.i_स_समय.tv_sec;
	auxdata.last_ग_लिखो_समय_nsec = cअगरsi->vfs_inode.i_mसमय.tv_nsec;
	auxdata.last_change_समय_nsec = cअगरsi->vfs_inode.i_स_समय.tv_nsec;

	cअगरsi->fscache =
		fscache_acquire_cookie(tcon->fscache,
				       &cअगरs_fscache_inode_object_def,
				       &cअगरsi->uniqueid, माप(cअगरsi->uniqueid),
				       &auxdata, माप(auxdata),
				       cअगरsi, cअगरsi->vfs_inode.i_size, true);
पूर्ण

अटल व्योम cअगरs_fscache_enable_inode_cookie(काष्ठा inode *inode)
अणु
	काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(inode);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);

	अगर (cअगरsi->fscache)
		वापस;

	अगर (!(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_FSCACHE))
		वापस;

	cअगरs_fscache_acquire_inode_cookie(cअगरsi, tcon);

	cअगरs_dbg(FYI, "%s: got FH cookie (0x%p/0x%p)\n",
		 __func__, tcon->fscache, cअगरsi->fscache);
पूर्ण

व्योम cअगरs_fscache_release_inode_cookie(काष्ठा inode *inode)
अणु
	काष्ठा cअगरs_fscache_inode_auxdata auxdata;
	काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(inode);

	अगर (cअगरsi->fscache) अणु
		स_रखो(&auxdata, 0, माप(auxdata));
		auxdata.eof = cअगरsi->server_eof;
		auxdata.last_ग_लिखो_समय_sec = cअगरsi->vfs_inode.i_mसमय.tv_sec;
		auxdata.last_change_समय_sec = cअगरsi->vfs_inode.i_स_समय.tv_sec;
		auxdata.last_ग_लिखो_समय_nsec = cअगरsi->vfs_inode.i_mसमय.tv_nsec;
		auxdata.last_change_समय_nsec = cअगरsi->vfs_inode.i_स_समय.tv_nsec;

		cअगरs_dbg(FYI, "%s: (0x%p)\n", __func__, cअगरsi->fscache);
		fscache_relinquish_cookie(cअगरsi->fscache, &auxdata, false);
		cअगरsi->fscache = शून्य;
	पूर्ण
पूर्ण

अटल व्योम cअगरs_fscache_disable_inode_cookie(काष्ठा inode *inode)
अणु
	काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(inode);

	अगर (cअगरsi->fscache) अणु
		cअगरs_dbg(FYI, "%s: (0x%p)\n", __func__, cअगरsi->fscache);
		fscache_uncache_all_inode_pages(cअगरsi->fscache, inode);
		fscache_relinquish_cookie(cअगरsi->fscache, शून्य, true);
		cअगरsi->fscache = शून्य;
	पूर्ण
पूर्ण

व्योम cअगरs_fscache_set_inode_cookie(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अगर ((filp->f_flags & O_ACCMODE) != O_RDONLY)
		cअगरs_fscache_disable_inode_cookie(inode);
	अन्यथा
		cअगरs_fscache_enable_inode_cookie(inode);
पूर्ण

व्योम cअगरs_fscache_reset_inode_cookie(काष्ठा inode *inode)
अणु
	काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(inode);
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	काष्ठा fscache_cookie *old = cअगरsi->fscache;

	अगर (cअगरsi->fscache) अणु
		/* retire the current fscache cache and get a new one */
		fscache_relinquish_cookie(cअगरsi->fscache, शून्य, true);

		cअगरs_fscache_acquire_inode_cookie(cअगरsi, tcon);
		cअगरs_dbg(FYI, "%s: new cookie 0x%p oldcookie 0x%p\n",
			 __func__, cअगरsi->fscache, old);
	पूर्ण
पूर्ण

पूर्णांक cअगरs_fscache_release_page(काष्ठा page *page, gfp_t gfp)
अणु
	अगर (PageFsCache(page)) अणु
		काष्ठा inode *inode = page->mapping->host;
		काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(inode);

		cअगरs_dbg(FYI, "%s: (0x%p/0x%p)\n",
			 __func__, page, cअगरsi->fscache);
		अगर (!fscache_maybe_release_page(cअगरsi->fscache, page, gfp))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम cअगरs_पढ़ोpage_from_fscache_complete(काष्ठा page *page, व्योम *ctx,
						पूर्णांक error)
अणु
	cअगरs_dbg(FYI, "%s: (0x%p/%d)\n", __func__, page, error);
	अगर (!error)
		SetPageUptodate(page);
	unlock_page(page);
पूर्ण

/*
 * Retrieve a page from FS-Cache
 */
पूर्णांक __cअगरs_पढ़ोpage_from_fscache(काष्ठा inode *inode, काष्ठा page *page)
अणु
	पूर्णांक ret;

	cअगरs_dbg(FYI, "%s: (fsc:%p, p:%p, i:0x%p\n",
		 __func__, CIFS_I(inode)->fscache, page, inode);
	ret = fscache_पढ़ो_or_alloc_page(CIFS_I(inode)->fscache, page,
					 cअगरs_पढ़ोpage_from_fscache_complete,
					 शून्य,
					 GFP_KERNEL);
	चयन (ret) अणु

	हाल 0: /* page found in fscache, पढ़ो submitted */
		cअगरs_dbg(FYI, "%s: submitted\n", __func__);
		वापस ret;
	हाल -ENOBUFS:	/* page won't be cached */
	हाल -ENODATA:	/* page not in cache */
		cअगरs_dbg(FYI, "%s: %d\n", __func__, ret);
		वापस 1;

	शेष:
		cअगरs_dbg(VFS, "unknown error ret = %d\n", ret);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Retrieve a set of pages from FS-Cache
 */
पूर्णांक __cअगरs_पढ़ोpages_from_fscache(काष्ठा inode *inode,
				काष्ठा address_space *mapping,
				काष्ठा list_head *pages,
				अचिन्हित *nr_pages)
अणु
	पूर्णांक ret;

	cअगरs_dbg(FYI, "%s: (0x%p/%u/0x%p)\n",
		 __func__, CIFS_I(inode)->fscache, *nr_pages, inode);
	ret = fscache_पढ़ो_or_alloc_pages(CIFS_I(inode)->fscache, mapping,
					  pages, nr_pages,
					  cअगरs_पढ़ोpage_from_fscache_complete,
					  शून्य,
					  mapping_gfp_mask(mapping));
	चयन (ret) अणु
	हाल 0:	/* पढ़ो submitted to the cache क्रम all pages */
		cअगरs_dbg(FYI, "%s: submitted\n", __func__);
		वापस ret;

	हाल -ENOBUFS:	/* some pages are not cached and can't be */
	हाल -ENODATA:	/* some pages are not cached */
		cअगरs_dbg(FYI, "%s: no page\n", __func__);
		वापस 1;

	शेष:
		cअगरs_dbg(FYI, "unknown error ret = %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

व्योम __cअगरs_पढ़ोpage_to_fscache(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(inode);
	पूर्णांक ret;

	cअगरs_dbg(FYI, "%s: (fsc: %p, p: %p, i: %p)\n",
		 __func__, cअगरsi->fscache, page, inode);
	ret = fscache_ग_लिखो_page(cअगरsi->fscache, page,
				 cअगरsi->vfs_inode.i_size, GFP_KERNEL);
	अगर (ret != 0)
		fscache_uncache_page(cअगरsi->fscache, page);
पूर्ण

व्योम __cअगरs_fscache_पढ़ोpages_cancel(काष्ठा inode *inode, काष्ठा list_head *pages)
अणु
	cअगरs_dbg(FYI, "%s: (fsc: %p, i: %p)\n",
		 __func__, CIFS_I(inode)->fscache, inode);
	fscache_पढ़ोpages_cancel(CIFS_I(inode)->fscache, pages);
पूर्ण

व्योम __cअगरs_fscache_invalidate_page(काष्ठा page *page, काष्ठा inode *inode)
अणु
	काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(inode);
	काष्ठा fscache_cookie *cookie = cअगरsi->fscache;

	cअगरs_dbg(FYI, "%s: (0x%p/0x%p)\n", __func__, page, cookie);
	fscache_रुको_on_page_ग_लिखो(cookie, page);
	fscache_uncache_page(cookie, page);
पूर्ण
