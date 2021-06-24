<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * V9FS cache definitions.
 *
 *  Copyright (C) 2009 by Abhishek Kulkarni <adkulkar@umail.iu.edu>
 */

#अगर_अघोषित _9P_CACHE_H
#घोषणा _9P_CACHE_H
#अगर_घोषित CONFIG_9P_FSCACHE
#समावेश <linux/fscache.h>
#समावेश <linux/spinlock.h>

बाह्य काष्ठा fscache_netfs v9fs_cache_netfs;
बाह्य स्थिर काष्ठा fscache_cookie_def v9fs_cache_session_index_def;
बाह्य स्थिर काष्ठा fscache_cookie_def v9fs_cache_inode_index_def;

बाह्य व्योम v9fs_cache_session_get_cookie(काष्ठा v9fs_session_info *v9ses);
बाह्य व्योम v9fs_cache_session_put_cookie(काष्ठा v9fs_session_info *v9ses);

बाह्य व्योम v9fs_cache_inode_get_cookie(काष्ठा inode *inode);
बाह्य व्योम v9fs_cache_inode_put_cookie(काष्ठा inode *inode);
बाह्य व्योम v9fs_cache_inode_flush_cookie(काष्ठा inode *inode);
बाह्य व्योम v9fs_cache_inode_set_cookie(काष्ठा inode *inode, काष्ठा file *filp);
बाह्य व्योम v9fs_cache_inode_reset_cookie(काष्ठा inode *inode);

बाह्य पूर्णांक __v9fs_cache_रेजिस्टर(व्योम);
बाह्य व्योम __v9fs_cache_unरेजिस्टर(व्योम);

बाह्य पूर्णांक __v9fs_fscache_release_page(काष्ठा page *page, gfp_t gfp);
बाह्य व्योम __v9fs_fscache_invalidate_page(काष्ठा page *page);
बाह्य पूर्णांक __v9fs_पढ़ोpage_from_fscache(काष्ठा inode *inode,
					काष्ठा page *page);
बाह्य पूर्णांक __v9fs_पढ़ोpages_from_fscache(काष्ठा inode *inode,
					 काष्ठा address_space *mapping,
					 काष्ठा list_head *pages,
					 अचिन्हित *nr_pages);
बाह्य व्योम __v9fs_पढ़ोpage_to_fscache(काष्ठा inode *inode, काष्ठा page *page);
बाह्य व्योम __v9fs_fscache_रुको_on_page_ग_लिखो(काष्ठा inode *inode,
					      काष्ठा page *page);

अटल अंतरभूत पूर्णांक v9fs_fscache_release_page(काष्ठा page *page,
					    gfp_t gfp)
अणु
	वापस __v9fs_fscache_release_page(page, gfp);
पूर्ण

अटल अंतरभूत व्योम v9fs_fscache_invalidate_page(काष्ठा page *page)
अणु
	__v9fs_fscache_invalidate_page(page);
पूर्ण

अटल अंतरभूत पूर्णांक v9fs_पढ़ोpage_from_fscache(काष्ठा inode *inode,
					     काष्ठा page *page)
अणु
	वापस __v9fs_पढ़ोpage_from_fscache(inode, page);
पूर्ण

अटल अंतरभूत पूर्णांक v9fs_पढ़ोpages_from_fscache(काष्ठा inode *inode,
					      काष्ठा address_space *mapping,
					      काष्ठा list_head *pages,
					      अचिन्हित *nr_pages)
अणु
	वापस __v9fs_पढ़ोpages_from_fscache(inode, mapping, pages,
					     nr_pages);
पूर्ण

अटल अंतरभूत व्योम v9fs_पढ़ोpage_to_fscache(काष्ठा inode *inode,
					    काष्ठा page *page)
अणु
	अगर (PageFsCache(page))
		__v9fs_पढ़ोpage_to_fscache(inode, page);
पूर्ण

अटल अंतरभूत व्योम v9fs_uncache_page(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);
	fscache_uncache_page(v9inode->fscache, page);
	BUG_ON(PageFsCache(page));
पूर्ण

अटल अंतरभूत व्योम v9fs_fscache_रुको_on_page_ग_लिखो(काष्ठा inode *inode,
						   काष्ठा page *page)
अणु
	वापस __v9fs_fscache_रुको_on_page_ग_लिखो(inode, page);
पूर्ण

#अन्यथा /* CONFIG_9P_FSCACHE */

अटल अंतरभूत व्योम v9fs_cache_inode_get_cookie(काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत व्योम v9fs_cache_inode_put_cookie(काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत व्योम v9fs_cache_inode_set_cookie(काष्ठा inode *inode, काष्ठा file *file)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक v9fs_fscache_release_page(काष्ठा page *page,
					    gfp_t gfp) अणु
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम v9fs_fscache_invalidate_page(काष्ठा page *page) अणुपूर्ण

अटल अंतरभूत पूर्णांक v9fs_पढ़ोpage_from_fscache(काष्ठा inode *inode,
					     काष्ठा page *page)
अणु
	वापस -ENOBUFS;
पूर्ण

अटल अंतरभूत पूर्णांक v9fs_पढ़ोpages_from_fscache(काष्ठा inode *inode,
					      काष्ठा address_space *mapping,
					      काष्ठा list_head *pages,
					      अचिन्हित *nr_pages)
अणु
	वापस -ENOBUFS;
पूर्ण

अटल अंतरभूत व्योम v9fs_पढ़ोpage_to_fscache(काष्ठा inode *inode,
					    काष्ठा page *page)
अणुपूर्ण

अटल अंतरभूत व्योम v9fs_uncache_page(काष्ठा inode *inode, काष्ठा page *page)
अणुपूर्ण

अटल अंतरभूत व्योम v9fs_fscache_रुको_on_page_ग_लिखो(काष्ठा inode *inode,
						   काष्ठा page *page)
अणु
	वापस;
पूर्ण

#पूर्ण_अगर /* CONFIG_9P_FSCACHE */
#पूर्ण_अगर /* _9P_CACHE_H */
