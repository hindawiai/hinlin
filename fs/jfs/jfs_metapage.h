<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2002
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */
#अगर_अघोषित	_H_JFS_METAPAGE
#घोषणा _H_JFS_METAPAGE

#समावेश <linux/pagemap.h>

काष्ठा metapage अणु
	/* Common logsyncblk prefix (see jfs_logmgr.h) */
	u16 xflag;
	u16 unused;
	lid_t lid;
	पूर्णांक lsn;
	काष्ठा list_head synclist;
	/* End of logsyncblk prefix */

	अचिन्हित दीर्घ flag;	/* See Below */
	अचिन्हित दीर्घ count;	/* Reference count */
	व्योम *data;		/* Data poपूर्णांकer */
	sector_t index;		/* block address of page */
	रुको_queue_head_t रुको;

	/* implementation */
	काष्ठा page *page;
	काष्ठा super_block *sb;
	अचिन्हित पूर्णांक logical_size;

	/* Journal management */
	पूर्णांक clsn;
	पूर्णांक nohomeok;
	काष्ठा jfs_log *log;
पूर्ण;

/* metapage flag */
#घोषणा META_locked	0
#घोषणा META_dirty	2
#घोषणा META_sync	3
#घोषणा META_discard	4
#घोषणा META_क्रमceग_लिखो	5
#घोषणा META_io		6

#घोषणा mark_metapage_dirty(mp) set_bit(META_dirty, &(mp)->flag)

/* function prototypes */
बाह्य पूर्णांक metapage_init(व्योम);
बाह्य व्योम metapage_निकास(व्योम);
बाह्य काष्ठा metapage *__get_metapage(काष्ठा inode *inode,
				  अचिन्हित दीर्घ lblock, अचिन्हित पूर्णांक size,
				  पूर्णांक असलolute, अचिन्हित दीर्घ new);

#घोषणा पढ़ो_metapage(inode, lblock, size, असलolute)\
	 __get_metapage(inode, lblock, size, असलolute, false)

#घोषणा get_metapage(inode, lblock, size, असलolute)\
	 __get_metapage(inode, lblock, size, असलolute, true)

बाह्य व्योम release_metapage(काष्ठा metapage *);
बाह्य व्योम grab_metapage(काष्ठा metapage *);
बाह्य व्योम क्रमce_metapage(काष्ठा metapage *);

/*
 * hold_metapage and put_metapage are used in conjunction.  The page lock
 * is not dropped between the two, so no other thपढ़ोs can get or release
 * the metapage
 */
बाह्य व्योम hold_metapage(काष्ठा metapage *);
बाह्य व्योम put_metapage(काष्ठा metapage *);

अटल अंतरभूत व्योम ग_लिखो_metapage(काष्ठा metapage *mp)
अणु
	set_bit(META_dirty, &mp->flag);
	release_metapage(mp);
पूर्ण

अटल अंतरभूत व्योम flush_metapage(काष्ठा metapage *mp)
अणु
	set_bit(META_sync, &mp->flag);
	ग_लिखो_metapage(mp);
पूर्ण

अटल अंतरभूत व्योम discard_metapage(काष्ठा metapage *mp)
अणु
	clear_bit(META_dirty, &mp->flag);
	set_bit(META_discard, &mp->flag);
	release_metapage(mp);
पूर्ण

अटल अंतरभूत व्योम metapage_nohomeok(काष्ठा metapage *mp)
अणु
	काष्ठा page *page = mp->page;
	lock_page(page);
	अगर (!mp->nohomeok++) अणु
		mark_metapage_dirty(mp);
		get_page(page);
		रुको_on_page_ग_लिखोback(page);
	पूर्ण
	unlock_page(page);
पूर्ण

/*
 * This serializes access to mp->lsn when metapages are added to logsynclist
 * without setting nohomeok.  i.e. updating imap & dmap
 */
अटल अंतरभूत व्योम metapage_रुको_क्रम_io(काष्ठा metapage *mp)
अणु
	अगर (test_bit(META_io, &mp->flag))
		रुको_on_page_ग_लिखोback(mp->page);
पूर्ण

/*
 * This is called when alपढ़ोy holding the metapage
 */
अटल अंतरभूत व्योम _metapage_homeok(काष्ठा metapage *mp)
अणु
	अगर (!--mp->nohomeok)
		put_page(mp->page);
पूर्ण

अटल अंतरभूत व्योम metapage_homeok(काष्ठा metapage *mp)
अणु
	hold_metapage(mp);
	_metapage_homeok(mp);
	put_metapage(mp);
पूर्ण

बाह्य स्थिर काष्ठा address_space_operations jfs_metapage_aops;

/*
 * This routines invalidate all pages क्रम an extent.
 */
बाह्य व्योम __invalidate_metapages(काष्ठा inode *, s64, पूर्णांक);
#घोषणा invalidate_pxd_metapages(ip, pxd) \
	__invalidate_metapages((ip), addressPXD(&(pxd)), lengthPXD(&(pxd)))
#घोषणा invalidate_dxd_metapages(ip, dxd) \
	__invalidate_metapages((ip), addressDXD(&(dxd)), lengthDXD(&(dxd)))
#घोषणा invalidate_xad_metapages(ip, xad) \
	__invalidate_metapages((ip), addressXAD(&(xad)), lengthXAD(&(xad)))

#पूर्ण_अगर				/* _H_JFS_METAPAGE */
