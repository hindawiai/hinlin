<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Ceph cache definitions.
 *
 *  Copyright (C) 2013 by Adfin Solutions, Inc. All Rights Reserved.
 *  Written by Milosz Tanski (milosz@adfin.com)
 */

#अगर_अघोषित _CEPH_CACHE_H
#घोषणा _CEPH_CACHE_H

#समावेश <linux/netfs.h>

#अगर_घोषित CONFIG_CEPH_FSCACHE

बाह्य काष्ठा fscache_netfs ceph_cache_netfs;

पूर्णांक ceph_fscache_रेजिस्टर(व्योम);
व्योम ceph_fscache_unरेजिस्टर(व्योम);

पूर्णांक ceph_fscache_रेजिस्टर_fs(काष्ठा ceph_fs_client* fsc, काष्ठा fs_context *fc);
व्योम ceph_fscache_unरेजिस्टर_fs(काष्ठा ceph_fs_client* fsc);

व्योम ceph_fscache_रेजिस्टर_inode_cookie(काष्ठा inode *inode);
व्योम ceph_fscache_unरेजिस्टर_inode_cookie(काष्ठा ceph_inode_info* ci);
व्योम ceph_fscache_file_set_cookie(काष्ठा inode *inode, काष्ठा file *filp);
व्योम ceph_fscache_revalidate_cookie(काष्ठा ceph_inode_info *ci);

पूर्णांक ceph_पढ़ोpage_from_fscache(काष्ठा inode *inode, काष्ठा page *page);
पूर्णांक ceph_पढ़ोpages_from_fscache(काष्ठा inode *inode,
				काष्ठा address_space *mapping,
				काष्ठा list_head *pages,
				अचिन्हित *nr_pages);

अटल अंतरभूत व्योम ceph_fscache_inode_init(काष्ठा ceph_inode_info *ci)
अणु
	ci->fscache = शून्य;
पूर्ण

अटल अंतरभूत काष्ठा fscache_cookie *ceph_fscache_cookie(काष्ठा ceph_inode_info *ci)
अणु
	वापस ci->fscache;
पूर्ण

अटल अंतरभूत व्योम ceph_fscache_invalidate(काष्ठा inode *inode)
अणु
	fscache_invalidate(ceph_inode(inode)->fscache);
पूर्ण

अटल अंतरभूत bool ceph_is_cache_enabled(काष्ठा inode *inode)
अणु
	काष्ठा fscache_cookie *cookie = ceph_fscache_cookie(ceph_inode(inode));

	अगर (!cookie)
		वापस false;
	वापस fscache_cookie_enabled(cookie);
पूर्ण

अटल अंतरभूत पूर्णांक ceph_begin_cache_operation(काष्ठा netfs_पढ़ो_request *rreq)
अणु
	काष्ठा fscache_cookie *cookie = ceph_fscache_cookie(ceph_inode(rreq->inode));

	वापस fscache_begin_पढ़ो_operation(rreq, cookie);
पूर्ण
#अन्यथा

अटल अंतरभूत पूर्णांक ceph_fscache_रेजिस्टर(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ceph_fscache_unरेजिस्टर(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ceph_fscache_रेजिस्टर_fs(काष्ठा ceph_fs_client* fsc,
					   काष्ठा fs_context *fc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ceph_fscache_unरेजिस्टर_fs(काष्ठा ceph_fs_client* fsc)
अणु
पूर्ण

अटल अंतरभूत व्योम ceph_fscache_inode_init(काष्ठा ceph_inode_info *ci)
अणु
पूर्ण

अटल अंतरभूत काष्ठा fscache_cookie *ceph_fscache_cookie(काष्ठा ceph_inode_info *ci)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम ceph_fscache_रेजिस्टर_inode_cookie(काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत व्योम ceph_fscache_unरेजिस्टर_inode_cookie(काष्ठा ceph_inode_info* ci)
अणु
पूर्ण

अटल अंतरभूत व्योम ceph_fscache_file_set_cookie(काष्ठा inode *inode,
						काष्ठा file *filp)
अणु
पूर्ण

अटल अंतरभूत व्योम ceph_fscache_invalidate(काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत bool ceph_is_cache_enabled(काष्ठा inode *inode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक ceph_begin_cache_operation(काष्ठा netfs_पढ़ो_request *rreq)
अणु
	वापस -ENOBUFS;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _CEPH_CACHE_H */
