<शैली गुरु>
/*
 *   fs/cअगरs/fscache.h - CIFS fileप्रणाली cache पूर्णांकerface definitions
 *
 *   Copyright (c) 2010 Novell, Inc.
 *   Authors(s): Suresh Jayaraman (sjayaraman@suse.de>
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
#अगर_अघोषित _CIFS_FSCACHE_H
#घोषणा _CIFS_FSCACHE_H

#समावेश <linux/fscache.h>

#समावेश "cifsglob.h"

#अगर_घोषित CONFIG_CIFS_FSCACHE

/*
 * Auxiliary data attached to CIFS superblock within the cache
 */
काष्ठा cअगरs_fscache_super_auxdata अणु
	u64	resource_id;		/* unique server resource id */
	__le64	vol_create_समय;
	u32	vol_serial_number;
पूर्ण __packed;

/*
 * Auxiliary data attached to CIFS inode within the cache
 */
काष्ठा cअगरs_fscache_inode_auxdata अणु
	u64 last_ग_लिखो_समय_sec;
	u64 last_change_समय_sec;
	u32 last_ग_लिखो_समय_nsec;
	u32 last_change_समय_nsec;
	u64 eof;
पूर्ण;

/*
 * cache.c
 */
बाह्य काष्ठा fscache_netfs cअगरs_fscache_netfs;
बाह्य स्थिर काष्ठा fscache_cookie_def cअगरs_fscache_server_index_def;
बाह्य स्थिर काष्ठा fscache_cookie_def cअगरs_fscache_super_index_def;
बाह्य स्थिर काष्ठा fscache_cookie_def cअगरs_fscache_inode_object_def;

बाह्य पूर्णांक cअगरs_fscache_रेजिस्टर(व्योम);
बाह्य व्योम cअगरs_fscache_unरेजिस्टर(व्योम);

/*
 * fscache.c
 */
बाह्य व्योम cअगरs_fscache_get_client_cookie(काष्ठा TCP_Server_Info *);
बाह्य व्योम cअगरs_fscache_release_client_cookie(काष्ठा TCP_Server_Info *);
बाह्य व्योम cअगरs_fscache_get_super_cookie(काष्ठा cअगरs_tcon *);
बाह्य व्योम cअगरs_fscache_release_super_cookie(काष्ठा cअगरs_tcon *);

बाह्य व्योम cअगरs_fscache_release_inode_cookie(काष्ठा inode *);
बाह्य व्योम cअगरs_fscache_set_inode_cookie(काष्ठा inode *, काष्ठा file *);
बाह्य व्योम cअगरs_fscache_reset_inode_cookie(काष्ठा inode *);

बाह्य व्योम __cअगरs_fscache_invalidate_page(काष्ठा page *, काष्ठा inode *);
बाह्य पूर्णांक cअगरs_fscache_release_page(काष्ठा page *page, gfp_t gfp);
बाह्य पूर्णांक __cअगरs_पढ़ोpage_from_fscache(काष्ठा inode *, काष्ठा page *);
बाह्य पूर्णांक __cअगरs_पढ़ोpages_from_fscache(काष्ठा inode *,
					 काष्ठा address_space *,
					 काष्ठा list_head *,
					 अचिन्हित *);
बाह्य व्योम __cअगरs_fscache_पढ़ोpages_cancel(काष्ठा inode *, काष्ठा list_head *);

बाह्य व्योम __cअगरs_पढ़ोpage_to_fscache(काष्ठा inode *, काष्ठा page *);

अटल अंतरभूत व्योम cअगरs_fscache_invalidate_page(काष्ठा page *page,
					       काष्ठा inode *inode)
अणु
	अगर (PageFsCache(page))
		__cअगरs_fscache_invalidate_page(page, inode);
पूर्ण

अटल अंतरभूत पूर्णांक cअगरs_पढ़ोpage_from_fscache(काष्ठा inode *inode,
					     काष्ठा page *page)
अणु
	अगर (CIFS_I(inode)->fscache)
		वापस __cअगरs_पढ़ोpage_from_fscache(inode, page);

	वापस -ENOBUFS;
पूर्ण

अटल अंतरभूत पूर्णांक cअगरs_पढ़ोpages_from_fscache(काष्ठा inode *inode,
					      काष्ठा address_space *mapping,
					      काष्ठा list_head *pages,
					      अचिन्हित *nr_pages)
अणु
	अगर (CIFS_I(inode)->fscache)
		वापस __cअगरs_पढ़ोpages_from_fscache(inode, mapping, pages,
						     nr_pages);
	वापस -ENOBUFS;
पूर्ण

अटल अंतरभूत व्योम cअगरs_पढ़ोpage_to_fscache(काष्ठा inode *inode,
					    काष्ठा page *page)
अणु
	अगर (PageFsCache(page))
		__cअगरs_पढ़ोpage_to_fscache(inode, page);
पूर्ण

अटल अंतरभूत व्योम cअगरs_fscache_पढ़ोpages_cancel(काष्ठा inode *inode,
						 काष्ठा list_head *pages)
अणु
	अगर (CIFS_I(inode)->fscache)
		वापस __cअगरs_fscache_पढ़ोpages_cancel(inode, pages);
पूर्ण

#अन्यथा /* CONFIG_CIFS_FSCACHE */
अटल अंतरभूत पूर्णांक cअगरs_fscache_रेजिस्टर(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम cअगरs_fscache_unरेजिस्टर(व्योम) अणुपूर्ण

अटल अंतरभूत व्योम
cअगरs_fscache_get_client_cookie(काष्ठा TCP_Server_Info *server) अणुपूर्ण
अटल अंतरभूत व्योम
cअगरs_fscache_release_client_cookie(काष्ठा TCP_Server_Info *server) अणुपूर्ण
अटल अंतरभूत व्योम cअगरs_fscache_get_super_cookie(काष्ठा cअगरs_tcon *tcon) अणुपूर्ण
अटल अंतरभूत व्योम
cअगरs_fscache_release_super_cookie(काष्ठा cअगरs_tcon *tcon) अणुपूर्ण

अटल अंतरभूत व्योम cअगरs_fscache_release_inode_cookie(काष्ठा inode *inode) अणुपूर्ण
अटल अंतरभूत व्योम cअगरs_fscache_set_inode_cookie(काष्ठा inode *inode,
						 काष्ठा file *filp) अणुपूर्ण
अटल अंतरभूत व्योम cअगरs_fscache_reset_inode_cookie(काष्ठा inode *inode) अणुपूर्ण
अटल अंतरभूत पूर्णांक cअगरs_fscache_release_page(काष्ठा page *page, gfp_t gfp)
अणु
	वापस 1; /* May release page */
पूर्ण

अटल अंतरभूत व्योम cअगरs_fscache_invalidate_page(काष्ठा page *page,
			काष्ठा inode *inode) अणुपूर्ण
अटल अंतरभूत पूर्णांक
cअगरs_पढ़ोpage_from_fscache(काष्ठा inode *inode, काष्ठा page *page)
अणु
	वापस -ENOBUFS;
पूर्ण

अटल अंतरभूत पूर्णांक cअगरs_पढ़ोpages_from_fscache(काष्ठा inode *inode,
					      काष्ठा address_space *mapping,
					      काष्ठा list_head *pages,
					      अचिन्हित *nr_pages)
अणु
	वापस -ENOBUFS;
पूर्ण

अटल अंतरभूत व्योम cअगरs_पढ़ोpage_to_fscache(काष्ठा inode *inode,
			काष्ठा page *page) अणुपूर्ण

अटल अंतरभूत व्योम cअगरs_fscache_पढ़ोpages_cancel(काष्ठा inode *inode,
						 काष्ठा list_head *pages)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_CIFS_FSCACHE */

#पूर्ण_अगर /* _CIFS_FSCACHE_H */
