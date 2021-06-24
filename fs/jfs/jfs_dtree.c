<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 */

/*
 *	jfs_dtree.c: directory B+-tree manager
 *
 * B+-tree with variable length key directory:
 *
 * each directory page is काष्ठाured as an array of 32-byte
 * directory entry slots initialized as a मुक्तlist
 * to aव्योम search/compaction of मुक्त space at insertion.
 * when an entry is inserted, a number of slots are allocated
 * from the मुक्तlist as required to store variable length data
 * of the entry; when the entry is deleted, slots of the entry
 * are वापसed to मुक्तlist.
 *
 * leaf entry stores full name as key and file serial number
 * (aka inode number) as data.
 * पूर्णांकernal/router entry stores sufffix compressed name
 * as key and simple extent descriptor as data.
 *
 * each directory page मुख्यtains a sorted entry index table
 * which stores the start slot index of sorted entries
 * to allow binary search on the table.
 *
 * directory starts as a root/leaf page in on-disk inode
 * अंतरभूत data area.
 * when it becomes full, it starts a leaf of a बाह्यal extent
 * of length of 1 block. each समय the first leaf becomes full,
 * it is extended rather than split (its size is द्विगुनd),
 * until its length becoms 4 KBytes, from then the extent is split
 * with new 4 Kbyte extent when it becomes full
 * to reduce बाह्यal fragmentation of small directories.
 *
 * blah, blah, blah, क्रम linear scan of directory in pieces by
 * सूची_पढ़ो().
 *
 *
 *	हाल-insensitive directory file प्रणाली
 *
 * names are stored in हाल-sensitive way in leaf entry.
 * but stored, searched and compared in हाल-insensitive (upperहाल) order
 * (i.e., both search key and entry key are folded क्रम search/compare):
 * (note that हाल-sensitive order is BROKEN in storage, e.g.,
 *  sensitive: Ad, aB, aC, aD -> insensitive: aB, aC, aD, Ad
 *
 *  entries which folds to the same key makes up a equivalent class
 *  whose members are stored as contiguous cluster (may cross page boundary)
 *  but whose order is arbitrary and acts as duplicate, e.g.,
 *  abc, Abc, aBc, abC)
 *
 * once match is found at leaf, requires scan क्रमward/backward
 * either क्रम, in हाल-insensitive search, duplicate
 * or क्रम, in हाल-sensitive search, क्रम exact match
 *
 * router entry must be created/stored in हाल-insensitive way
 * in पूर्णांकernal entry:
 * (right most key of left page and left most key of right page
 * are folded, and its suffix compression is propagated as router
 * key in parent)
 * (e.g., अगर split occurs <abc> and <aBd>, <ABD> trather than <aB>
 * should be made the router key क्रम the split)
 *
 * हाल-insensitive search:
 *
 *	fold search key;
 *
 *	हाल-insensitive search of B-tree:
 *	क्रम पूर्णांकernal entry, router key is alपढ़ोy folded;
 *	क्रम leaf entry, fold the entry key beक्रमe comparison.
 *
 *	अगर (leaf entry हाल-insensitive match found)
 *		अगर (next entry satisfies हाल-insensitive match)
 *			वापस EDUPLICATE;
 *		अगर (prev entry satisfies हाल-insensitive match)
 *			वापस EDUPLICATE;
 *		वापस match;
 *	अन्यथा
 *		वापस no match;
 *
 *	serialization:
 * target directory inode lock is being held on entry/निकास
 * of all मुख्य directory service routines.
 *
 *	log based recovery:
 */

#समावेश <linux/fs.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/slab.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_unicode.h"
#समावेश "jfs_debug.h"

/* dtree split parameter */
काष्ठा dtsplit अणु
	काष्ठा metapage *mp;
	s16 index;
	s16 nslot;
	काष्ठा component_name *key;
	ddata_t *data;
	काष्ठा pxdlist *pxdlist;
पूर्ण;

#घोषणा DT_PAGE(IP, MP) BT_PAGE(IP, MP, dtpage_t, i_dtroot)

/* get page buffer क्रम specअगरied block address */
#घोषणा DT_GETPAGE(IP, BN, MP, SIZE, P, RC)				\
करो अणु									\
	BT_GETPAGE(IP, BN, MP, dtpage_t, SIZE, P, RC, i_dtroot);	\
	अगर (!(RC)) अणु							\
		अगर (((P)->header.nextindex >				\
		     (((BN) == 0) ? DTROOTMAXSLOT : (P)->header.maxslot)) || \
		    ((BN) && ((P)->header.maxslot > DTPAGEMAXSLOT))) अणु	\
			BT_PUTPAGE(MP);					\
			jfs_error((IP)->i_sb,				\
				  "DT_GETPAGE: dtree page corrupt\n");	\
			MP = शून्य;					\
			RC = -EIO;					\
		पूर्ण							\
	पूर्ण								\
पूर्ण जबतक (0)

/* क्रम consistency */
#घोषणा DT_PUTPAGE(MP) BT_PUTPAGE(MP)

#घोषणा DT_GETSEARCH(IP, LEAF, BN, MP, P, INDEX) \
	BT_GETSEARCH(IP, LEAF, BN, MP, dtpage_t, P, INDEX, i_dtroot)

/*
 * क्रमward references
 */
अटल पूर्णांक dtSplitUp(tid_t tid, काष्ठा inode *ip,
		     काष्ठा dtsplit * split, काष्ठा btstack * btstack);

अटल पूर्णांक dtSplitPage(tid_t tid, काष्ठा inode *ip, काष्ठा dtsplit * split,
		       काष्ठा metapage ** rmpp, dtpage_t ** rpp, pxd_t * rxdp);

अटल पूर्णांक dtExtendPage(tid_t tid, काष्ठा inode *ip,
			काष्ठा dtsplit * split, काष्ठा btstack * btstack);

अटल पूर्णांक dtSplitRoot(tid_t tid, काष्ठा inode *ip,
		       काष्ठा dtsplit * split, काष्ठा metapage ** rmpp);

अटल पूर्णांक dtDeleteUp(tid_t tid, काष्ठा inode *ip, काष्ठा metapage * fmp,
		      dtpage_t * fp, काष्ठा btstack * btstack);

अटल पूर्णांक dtRelink(tid_t tid, काष्ठा inode *ip, dtpage_t * p);

अटल पूर्णांक dtReadFirst(काष्ठा inode *ip, काष्ठा btstack * btstack);

अटल पूर्णांक dtReadNext(काष्ठा inode *ip,
		      loff_t * offset, काष्ठा btstack * btstack);

अटल पूर्णांक dtCompare(काष्ठा component_name * key, dtpage_t * p, पूर्णांक si);

अटल पूर्णांक ciCompare(काष्ठा component_name * key, dtpage_t * p, पूर्णांक si,
		     पूर्णांक flag);

अटल व्योम dtGetKey(dtpage_t * p, पूर्णांक i, काष्ठा component_name * key,
		     पूर्णांक flag);

अटल पूर्णांक ciGetLeafPrefixKey(dtpage_t * lp, पूर्णांक li, dtpage_t * rp,
			      पूर्णांक ri, काष्ठा component_name * key, पूर्णांक flag);

अटल व्योम dtInsertEntry(dtpage_t * p, पूर्णांक index, काष्ठा component_name * key,
			  ddata_t * data, काष्ठा dt_lock **);

अटल व्योम dtMoveEntry(dtpage_t * sp, पूर्णांक si, dtpage_t * dp,
			काष्ठा dt_lock ** sdtlock, काष्ठा dt_lock ** ddtlock,
			पूर्णांक करो_index);

अटल व्योम dtDeleteEntry(dtpage_t * p, पूर्णांक fi, काष्ठा dt_lock ** dtlock);

अटल व्योम dtTruncateEntry(dtpage_t * p, पूर्णांक ti, काष्ठा dt_lock ** dtlock);

अटल व्योम dtLinelockFreelist(dtpage_t * p, पूर्णांक m, काष्ठा dt_lock ** dtlock);

#घोषणा ciToUpper(c)	UniStrupr((c)->name)

/*
 *	पढ़ो_index_page()
 *
 *	Reads a page of a directory's index table.
 *	Having metadata mapped पूर्णांकo the directory inode's address space
 *	presents a multitude of problems.  We aव्योम this by mapping to
 *	the असलolute address space outside of the *_metapage routines
 */
अटल काष्ठा metapage *पढ़ो_index_page(काष्ठा inode *inode, s64 blkno)
अणु
	पूर्णांक rc;
	s64 xaddr;
	पूर्णांक xflag;
	s32 xlen;

	rc = xtLookup(inode, blkno, 1, &xflag, &xaddr, &xlen, 1);
	अगर (rc || (xaddr == 0))
		वापस शून्य;

	वापस पढ़ो_metapage(inode, xaddr, PSIZE, 1);
पूर्ण

/*
 *	get_index_page()
 *
 *	Same as get_index_page(), but get's a new page without पढ़ोing
 */
अटल काष्ठा metapage *get_index_page(काष्ठा inode *inode, s64 blkno)
अणु
	पूर्णांक rc;
	s64 xaddr;
	पूर्णांक xflag;
	s32 xlen;

	rc = xtLookup(inode, blkno, 1, &xflag, &xaddr, &xlen, 1);
	अगर (rc || (xaddr == 0))
		वापस शून्य;

	वापस get_metapage(inode, xaddr, PSIZE, 1);
पूर्ण

/*
 *	find_index()
 *
 *	Returns dtree page containing directory table entry क्रम specअगरied
 *	index and poपूर्णांकer to its entry.
 *
 *	mp must be released by caller.
 */
अटल काष्ठा dir_table_slot *find_index(काष्ठा inode *ip, u32 index,
					 काष्ठा metapage ** mp, s64 *lblock)
अणु
	काष्ठा jfs_inode_info *jfs_ip = JFS_IP(ip);
	s64 blkno;
	s64 offset;
	पूर्णांक page_offset;
	काष्ठा dir_table_slot *slot;
	अटल पूर्णांक maxWarnings = 10;

	अगर (index < 2) अणु
		अगर (maxWarnings) अणु
			jfs_warn("find_entry called with index = %d", index);
			maxWarnings--;
		पूर्ण
		वापस शून्य;
	पूर्ण

	अगर (index >= jfs_ip->next_index) अणु
		jfs_warn("find_entry called with index >= next_index");
		वापस शून्य;
	पूर्ण

	अगर (jfs_dirtable_अंतरभूत(ip)) अणु
		/*
		 * Inline directory table
		 */
		*mp = शून्य;
		slot = &jfs_ip->i_dirtable[index - 2];
	पूर्ण अन्यथा अणु
		offset = (index - 2) * माप(काष्ठा dir_table_slot);
		page_offset = offset & (PSIZE - 1);
		blkno = ((offset + 1) >> L2PSIZE) <<
		    JFS_SBI(ip->i_sb)->l2nbperpage;

		अगर (*mp && (*lblock != blkno)) अणु
			release_metapage(*mp);
			*mp = शून्य;
		पूर्ण
		अगर (!(*mp)) अणु
			*lblock = blkno;
			*mp = पढ़ो_index_page(ip, blkno);
		पूर्ण
		अगर (!(*mp)) अणु
			jfs_err("free_index: error reading directory table");
			वापस शून्य;
		पूर्ण

		slot =
		    (काष्ठा dir_table_slot *) ((अक्षर *) (*mp)->data +
					       page_offset);
	पूर्ण
	वापस slot;
पूर्ण

अटल अंतरभूत व्योम lock_index(tid_t tid, काष्ठा inode *ip, काष्ठा metapage * mp,
			      u32 index)
अणु
	काष्ठा tlock *tlck;
	काष्ठा linelock *llck;
	काष्ठा lv *lv;

	tlck = txLock(tid, ip, mp, tlckDATA);
	llck = (काष्ठा linelock *) tlck->lock;

	अगर (llck->index >= llck->maxcnt)
		llck = txLinelock(llck);
	lv = &llck->lv[llck->index];

	/*
	 *	Linelock slot size is twice the size of directory table
	 *	slot size.  512 entries per page.
	 */
	lv->offset = ((index - 2) & 511) >> 1;
	lv->length = 1;
	llck->index++;
पूर्ण

/*
 *	add_index()
 *
 *	Adds an entry to the directory index table.  This is used to provide
 *	each directory entry with a persistent index in which to resume
 *	directory traversals
 */
अटल u32 add_index(tid_t tid, काष्ठा inode *ip, s64 bn, पूर्णांक slot)
अणु
	काष्ठा super_block *sb = ip->i_sb;
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	काष्ठा jfs_inode_info *jfs_ip = JFS_IP(ip);
	u64 blkno;
	काष्ठा dir_table_slot *dirtab_slot;
	u32 index;
	काष्ठा linelock *llck;
	काष्ठा lv *lv;
	काष्ठा metapage *mp;
	s64 offset;
	uपूर्णांक page_offset;
	काष्ठा tlock *tlck;
	s64 xaddr;

	ASSERT(DO_INDEX(ip));

	अगर (jfs_ip->next_index < 2) अणु
		jfs_warn("add_index: next_index = %d.  Resetting!",
			   jfs_ip->next_index);
		jfs_ip->next_index = 2;
	पूर्ण

	index = jfs_ip->next_index++;

	अगर (index <= MAX_INLINE_सूचीTABLE_ENTRY) अणु
		/*
		 * i_size reflects size of index table, or 8 bytes per entry.
		 */
		ip->i_size = (loff_t) (index - 1) << 3;

		/*
		 * dir table fits अंतरभूत within inode
		 */
		dirtab_slot = &jfs_ip->i_dirtable[index-2];
		dirtab_slot->flag = सूची_INDEX_VALID;
		dirtab_slot->slot = slot;
		DTSaddress(dirtab_slot, bn);

		set_cflag(COMMIT_Dirtable, ip);

		वापस index;
	पूर्ण
	अगर (index == (MAX_INLINE_सूचीTABLE_ENTRY + 1)) अणु
		काष्ठा dir_table_slot temp_table[12];

		/*
		 * It's समय to move the अंतरभूत table to an बाह्यal
		 * page and begin to build the xtree
		 */
		अगर (dquot_alloc_block(ip, sbi->nbperpage))
			जाओ clean_up;
		अगर (dbAlloc(ip, 0, sbi->nbperpage, &xaddr)) अणु
			dquot_मुक्त_block(ip, sbi->nbperpage);
			जाओ clean_up;
		पूर्ण

		/*
		 * Save the table, we're going to overग_लिखो it with the
		 * xtree root
		 */
		स_नकल(temp_table, &jfs_ip->i_dirtable, माप(temp_table));

		/*
		 * Initialize empty x-tree
		 */
		xtInitRoot(tid, ip);

		/*
		 * Add the first block to the xtree
		 */
		अगर (xtInsert(tid, ip, 0, 0, sbi->nbperpage, &xaddr, 0)) अणु
			/* This really shouldn't fail */
			jfs_warn("add_index: xtInsert failed!");
			स_नकल(&jfs_ip->i_dirtable, temp_table,
			       माप (temp_table));
			dbFree(ip, xaddr, sbi->nbperpage);
			dquot_मुक्त_block(ip, sbi->nbperpage);
			जाओ clean_up;
		पूर्ण
		ip->i_size = PSIZE;

		mp = get_index_page(ip, 0);
		अगर (!mp) अणु
			jfs_err("add_index: get_metapage failed!");
			xtTruncate(tid, ip, 0, COMMIT_PWMAP);
			स_नकल(&jfs_ip->i_dirtable, temp_table,
			       माप (temp_table));
			जाओ clean_up;
		पूर्ण
		tlck = txLock(tid, ip, mp, tlckDATA);
		llck = (काष्ठा linelock *) & tlck->lock;
		ASSERT(llck->index == 0);
		lv = &llck->lv[0];

		lv->offset = 0;
		lv->length = 6;	/* tlckDATA slot size is 16 bytes */
		llck->index++;

		स_नकल(mp->data, temp_table, माप(temp_table));

		mark_metapage_dirty(mp);
		release_metapage(mp);

		/*
		 * Logging is now directed by xtree tlocks
		 */
		clear_cflag(COMMIT_Dirtable, ip);
	पूर्ण

	offset = (index - 2) * माप(काष्ठा dir_table_slot);
	page_offset = offset & (PSIZE - 1);
	blkno = ((offset + 1) >> L2PSIZE) << sbi->l2nbperpage;
	अगर (page_offset == 0) अणु
		/*
		 * This will be the beginning of a new page
		 */
		xaddr = 0;
		अगर (xtInsert(tid, ip, 0, blkno, sbi->nbperpage, &xaddr, 0)) अणु
			jfs_warn("add_index: xtInsert failed!");
			जाओ clean_up;
		पूर्ण
		ip->i_size += PSIZE;

		अगर ((mp = get_index_page(ip, blkno)))
			स_रखो(mp->data, 0, PSIZE);	/* Just looks better */
		अन्यथा
			xtTruncate(tid, ip, offset, COMMIT_PWMAP);
	पूर्ण अन्यथा
		mp = पढ़ो_index_page(ip, blkno);

	अगर (!mp) अणु
		jfs_err("add_index: get/read_metapage failed!");
		जाओ clean_up;
	पूर्ण

	lock_index(tid, ip, mp, index);

	dirtab_slot =
	    (काष्ठा dir_table_slot *) ((अक्षर *) mp->data + page_offset);
	dirtab_slot->flag = सूची_INDEX_VALID;
	dirtab_slot->slot = slot;
	DTSaddress(dirtab_slot, bn);

	mark_metapage_dirty(mp);
	release_metapage(mp);

	वापस index;

      clean_up:

	jfs_ip->next_index--;

	वापस 0;
पूर्ण

/*
 *	मुक्त_index()
 *
 *	Marks an entry to the directory index table as मुक्त.
 */
अटल व्योम मुक्त_index(tid_t tid, काष्ठा inode *ip, u32 index, u32 next)
अणु
	काष्ठा dir_table_slot *dirtab_slot;
	s64 lblock;
	काष्ठा metapage *mp = शून्य;

	dirtab_slot = find_index(ip, index, &mp, &lblock);

	अगर (!dirtab_slot)
		वापस;

	dirtab_slot->flag = सूची_INDEX_FREE;
	dirtab_slot->slot = dirtab_slot->addr1 = 0;
	dirtab_slot->addr2 = cpu_to_le32(next);

	अगर (mp) अणु
		lock_index(tid, ip, mp, index);
		mark_metapage_dirty(mp);
		release_metapage(mp);
	पूर्ण अन्यथा
		set_cflag(COMMIT_Dirtable, ip);
पूर्ण

/*
 *	modअगरy_index()
 *
 *	Changes an entry in the directory index table
 */
अटल व्योम modअगरy_index(tid_t tid, काष्ठा inode *ip, u32 index, s64 bn,
			 पूर्णांक slot, काष्ठा metapage ** mp, s64 *lblock)
अणु
	काष्ठा dir_table_slot *dirtab_slot;

	dirtab_slot = find_index(ip, index, mp, lblock);

	अगर (!dirtab_slot)
		वापस;

	DTSaddress(dirtab_slot, bn);
	dirtab_slot->slot = slot;

	अगर (*mp) अणु
		lock_index(tid, ip, *mp, index);
		mark_metapage_dirty(*mp);
	पूर्ण अन्यथा
		set_cflag(COMMIT_Dirtable, ip);
पूर्ण

/*
 *	पढ़ो_index()
 *
 *	पढ़ोs a directory table slot
 */
अटल पूर्णांक पढ़ो_index(काष्ठा inode *ip, u32 index,
		     काष्ठा dir_table_slot * dirtab_slot)
अणु
	s64 lblock;
	काष्ठा metapage *mp = शून्य;
	काष्ठा dir_table_slot *slot;

	slot = find_index(ip, index, &mp, &lblock);
	अगर (!slot) अणु
		वापस -EIO;
	पूर्ण

	स_नकल(dirtab_slot, slot, माप(काष्ठा dir_table_slot));

	अगर (mp)
		release_metapage(mp);

	वापस 0;
पूर्ण

/*
 *	dtSearch()
 *
 * function:
 *	Search क्रम the entry with specअगरied key
 *
 * parameter:
 *
 * वापस: 0 - search result on stack, leaf page pinned;
 *	   त्रुटि_सं - I/O error
 */
पूर्णांक dtSearch(काष्ठा inode *ip, काष्ठा component_name * key, ino_t * data,
	     काष्ठा btstack * btstack, पूर्णांक flag)
अणु
	पूर्णांक rc = 0;
	पूर्णांक cmp = 1;		/* init क्रम empty page */
	s64 bn;
	काष्ठा metapage *mp;
	dtpage_t *p;
	s8 *stbl;
	पूर्णांक base, index, lim;
	काष्ठा btframe *btsp;
	pxd_t *pxd;
	पूर्णांक psize = 288;	/* initial in-line directory */
	ino_t inumber;
	काष्ठा component_name ciKey;
	काष्ठा super_block *sb = ip->i_sb;

	ciKey.name = kदो_स्मृति_array(JFS_NAME_MAX + 1, माप(ब_अक्षर_प्रकार),
				   GFP_NOFS);
	अगर (!ciKey.name) अणु
		rc = -ENOMEM;
		जाओ dtSearch_Exit2;
	पूर्ण


	/* upperहाल search key क्रम c-i directory */
	UniStrcpy(ciKey.name, key->name);
	ciKey.namlen = key->namlen;

	/* only upperहाल अगर हाल-insensitive support is on */
	अगर ((JFS_SBI(sb)->mntflag & JFS_OS2) == JFS_OS2) अणु
		ciToUpper(&ciKey);
	पूर्ण
	BT_CLR(btstack);	/* reset stack */

	/* init level count क्रम max pages to split */
	btstack->nsplit = 1;

	/*
	 *	search करोwn tree from root:
	 *
	 * between two consecutive entries of <Ki, Pi> and <Kj, Pj> of
	 * पूर्णांकernal page, child page Pi contains entry with k, Ki <= K < Kj.
	 *
	 * अगर entry with search key K is not found
	 * पूर्णांकernal page search find the entry with largest key Ki
	 * less than K which poपूर्णांक to the child page to search;
	 * leaf page search find the entry with smallest key Kj
	 * greater than K so that the वापसed index is the position of
	 * the entry to be shअगरted right क्रम insertion of new entry.
	 * क्रम empty tree, search key is greater than any key of the tree.
	 *
	 * by convention, root bn = 0.
	 */
	क्रम (bn = 0;;) अणु
		/* get/pin the page to search */
		DT_GETPAGE(ip, bn, mp, psize, p, rc);
		अगर (rc)
			जाओ dtSearch_Exit1;

		/* get sorted entry table of the page */
		stbl = DT_GETSTBL(p);

		/*
		 * binary search with search key K on the current page.
		 */
		क्रम (base = 0, lim = p->header.nextindex; lim; lim >>= 1) अणु
			index = base + (lim >> 1);

			अगर (p->header.flag & BT_LEAF) अणु
				/* upperहाल leaf name to compare */
				cmp =
				    ciCompare(&ciKey, p, stbl[index],
					      JFS_SBI(sb)->mntflag);
			पूर्ण अन्यथा अणु
				/* router key is in upperहाल */

				cmp = dtCompare(&ciKey, p, stbl[index]);


			पूर्ण
			अगर (cmp == 0) अणु
				/*
				 *	search hit
				 */
				/* search hit - leaf page:
				 * वापस the entry found
				 */
				अगर (p->header.flag & BT_LEAF) अणु
					inumber = le32_to_cpu(
			((काष्ठा ldtentry *) & p->slot[stbl[index]])->inumber);

					/*
					 * search क्रम JFS_LOOKUP
					 */
					अगर (flag == JFS_LOOKUP) अणु
						*data = inumber;
						rc = 0;
						जाओ out;
					पूर्ण

					/*
					 * search क्रम JFS_CREATE
					 */
					अगर (flag == JFS_CREATE) अणु
						*data = inumber;
						rc = -EEXIST;
						जाओ out;
					पूर्ण

					/*
					 * search क्रम JFS_REMOVE or JFS_RENAME
					 */
					अगर ((flag == JFS_REMOVE ||
					     flag == JFS_RENAME) &&
					    *data != inumber) अणु
						rc = -ESTALE;
						जाओ out;
					पूर्ण

					/*
					 * JFS_REMOVE|JFS_FINDसूची|JFS_RENAME
					 */
					/* save search result */
					*data = inumber;
					btsp = btstack->top;
					btsp->bn = bn;
					btsp->index = index;
					btsp->mp = mp;

					rc = 0;
					जाओ dtSearch_Exit1;
				पूर्ण

				/* search hit - पूर्णांकernal page:
				 * descend/search its child page
				 */
				जाओ getChild;
			पूर्ण

			अगर (cmp > 0) अणु
				base = index + 1;
				--lim;
			पूर्ण
		पूर्ण

		/*
		 *	search miss
		 *
		 * base is the smallest index with key (Kj) greater than
		 * search key (K) and may be zero or (maxindex + 1) index.
		 */
		/*
		 * search miss - leaf page
		 *
		 * वापस location of entry (base) where new entry with
		 * search key K is to be inserted.
		 */
		अगर (p->header.flag & BT_LEAF) अणु
			/*
			 * search क्रम JFS_LOOKUP, JFS_REMOVE, or JFS_RENAME
			 */
			अगर (flag == JFS_LOOKUP || flag == JFS_REMOVE ||
			    flag == JFS_RENAME) अणु
				rc = -ENOENT;
				जाओ out;
			पूर्ण

			/*
			 * search क्रम JFS_CREATE|JFS_FINDसूची:
			 *
			 * save search result
			 */
			*data = 0;
			btsp = btstack->top;
			btsp->bn = bn;
			btsp->index = base;
			btsp->mp = mp;

			rc = 0;
			जाओ dtSearch_Exit1;
		पूर्ण

		/*
		 * search miss - पूर्णांकernal page
		 *
		 * अगर base is non-zero, decrement base by one to get the parent
		 * entry of the child page to search.
		 */
		index = base ? base - 1 : base;

		/*
		 * go करोwn to child page
		 */
	      getChild:
		/* update max. number of pages to split */
		अगर (BT_STACK_FULL(btstack)) अणु
			/* Something's corrupted, mark fileप्रणाली dirty so
			 * chkdsk will fix it.
			 */
			jfs_error(sb, "stack overrun!\n");
			BT_STACK_DUMP(btstack);
			rc = -EIO;
			जाओ out;
		पूर्ण
		btstack->nsplit++;

		/* push (bn, index) of the parent page/entry */
		BT_PUSH(btstack, bn, index);

		/* get the child page block number */
		pxd = (pxd_t *) & p->slot[stbl[index]];
		bn = addressPXD(pxd);
		psize = lengthPXD(pxd) << JFS_SBI(ip->i_sb)->l2bsize;

		/* unpin the parent page */
		DT_PUTPAGE(mp);
	पूर्ण

      out:
	DT_PUTPAGE(mp);

      dtSearch_Exit1:

	kमुक्त(ciKey.name);

      dtSearch_Exit2:

	वापस rc;
पूर्ण


/*
 *	dtInsert()
 *
 * function: insert an entry to directory tree
 *
 * parameter:
 *
 * वापस: 0 - success;
 *	   त्रुटि_सं - failure;
 */
पूर्णांक dtInsert(tid_t tid, काष्ठा inode *ip,
	 काष्ठा component_name * name, ino_t * fsn, काष्ठा btstack * btstack)
अणु
	पूर्णांक rc = 0;
	काष्ठा metapage *mp;	/* meta-page buffer */
	dtpage_t *p;		/* base B+-tree index page */
	s64 bn;
	पूर्णांक index;
	काष्ठा dtsplit split;	/* split inक्रमmation */
	ddata_t data;
	काष्ठा dt_lock *dtlck;
	पूर्णांक n;
	काष्ठा tlock *tlck;
	काष्ठा lv *lv;

	/*
	 *	retrieve search result
	 *
	 * dtSearch() वापसs (leaf page pinned, index at which to insert).
	 * n.b. dtSearch() may वापस index of (maxindex + 1) of
	 * the full page.
	 */
	DT_GETSEARCH(ip, btstack->top, bn, mp, p, index);

	/*
	 *	insert entry क्रम new key
	 */
	अगर (DO_INDEX(ip)) अणु
		अगर (JFS_IP(ip)->next_index == सूचीEND) अणु
			DT_PUTPAGE(mp);
			वापस -EMLINK;
		पूर्ण
		n = NDTLEAF(name->namlen);
		data.leaf.tid = tid;
		data.leaf.ip = ip;
	पूर्ण अन्यथा अणु
		n = NDTLEAF_LEGACY(name->namlen);
		data.leaf.ip = शून्य;	/* signअगरies legacy directory क्रमmat */
	पूर्ण
	data.leaf.ino = *fsn;

	/*
	 *	leaf page करोes not have enough room क्रम new entry:
	 *
	 *	extend/split the leaf page;
	 *
	 * dtSplitUp() will insert the entry and unpin the leaf page.
	 */
	अगर (n > p->header.मुक्तcnt) अणु
		split.mp = mp;
		split.index = index;
		split.nslot = n;
		split.key = name;
		split.data = &data;
		rc = dtSplitUp(tid, ip, &split, btstack);
		वापस rc;
	पूर्ण

	/*
	 *	leaf page करोes have enough room क्रम new entry:
	 *
	 *	insert the new data entry पूर्णांकo the leaf page;
	 */
	BT_MARK_सूचीTY(mp, ip);
	/*
	 * acquire a transaction lock on the leaf page
	 */
	tlck = txLock(tid, ip, mp, tlckDTREE | tlckENTRY);
	dtlck = (काष्ठा dt_lock *) & tlck->lock;
	ASSERT(dtlck->index == 0);
	lv = & dtlck->lv[0];

	/* linelock header */
	lv->offset = 0;
	lv->length = 1;
	dtlck->index++;

	dtInsertEntry(p, index, name, &data, &dtlck);

	/* linelock stbl of non-root leaf page */
	अगर (!(p->header.flag & BT_ROOT)) अणु
		अगर (dtlck->index >= dtlck->maxcnt)
			dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
		lv = & dtlck->lv[dtlck->index];
		n = index >> L2DTSLOTSIZE;
		lv->offset = p->header.stblindex + n;
		lv->length =
		    ((p->header.nextindex - 1) >> L2DTSLOTSIZE) - n + 1;
		dtlck->index++;
	पूर्ण

	/* unpin the leaf page */
	DT_PUTPAGE(mp);

	वापस 0;
पूर्ण


/*
 *	dtSplitUp()
 *
 * function: propagate insertion bottom up;
 *
 * parameter:
 *
 * वापस: 0 - success;
 *	   त्रुटि_सं - failure;
 *	leaf page unpinned;
 */
अटल पूर्णांक dtSplitUp(tid_t tid,
	  काष्ठा inode *ip, काष्ठा dtsplit * split, काष्ठा btstack * btstack)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	पूर्णांक rc = 0;
	काष्ठा metapage *smp;
	dtpage_t *sp;		/* split page */
	काष्ठा metapage *rmp;
	dtpage_t *rp;		/* new right page split from sp */
	pxd_t rpxd;		/* new right page extent descriptor */
	काष्ठा metapage *lmp;
	dtpage_t *lp;		/* left child page */
	पूर्णांक skip;		/* index of entry of insertion */
	काष्ठा btframe *parent;	/* parent page entry on traverse stack */
	s64 xaddr, nxaddr;
	पूर्णांक xlen, xsize;
	काष्ठा pxdlist pxdlist;
	pxd_t *pxd;
	काष्ठा component_name key = अणु 0, शून्य पूर्ण;
	ddata_t *data = split->data;
	पूर्णांक n;
	काष्ठा dt_lock *dtlck;
	काष्ठा tlock *tlck;
	काष्ठा lv *lv;
	पूर्णांक quota_allocation = 0;

	/* get split page */
	smp = split->mp;
	sp = DT_PAGE(ip, smp);

	key.name = kदो_स्मृति_array(JFS_NAME_MAX + 2, माप(ब_अक्षर_प्रकार), GFP_NOFS);
	अगर (!key.name) अणु
		DT_PUTPAGE(smp);
		rc = -ENOMEM;
		जाओ dtSplitUp_Exit;
	पूर्ण

	/*
	 *	split leaf page
	 *
	 * The split routines insert the new entry, and
	 * acquire txLock as appropriate.
	 */
	/*
	 *	split root leaf page:
	 */
	अगर (sp->header.flag & BT_ROOT) अणु
		/*
		 * allocate a single extent child page
		 */
		xlen = 1;
		n = sbi->bsize >> L2DTSLOTSIZE;
		n -= (n + 31) >> L2DTSLOTSIZE;	/* stbl size */
		n -= DTROOTMAXSLOT - sp->header.मुक्तcnt; /* header + entries */
		अगर (n <= split->nslot)
			xlen++;
		अगर ((rc = dbAlloc(ip, 0, (s64) xlen, &xaddr))) अणु
			DT_PUTPAGE(smp);
			जाओ मुक्तKeyName;
		पूर्ण

		pxdlist.maxnpxd = 1;
		pxdlist.npxd = 0;
		pxd = &pxdlist.pxd[0];
		PXDaddress(pxd, xaddr);
		PXDlength(pxd, xlen);
		split->pxdlist = &pxdlist;
		rc = dtSplitRoot(tid, ip, split, &rmp);

		अगर (rc)
			dbFree(ip, xaddr, xlen);
		अन्यथा
			DT_PUTPAGE(rmp);

		DT_PUTPAGE(smp);

		अगर (!DO_INDEX(ip))
			ip->i_size = xlen << sbi->l2bsize;

		जाओ मुक्तKeyName;
	पूर्ण

	/*
	 *	extend first leaf page
	 *
	 * extend the 1st extent अगर less than buffer page size
	 * (dtExtendPage() reurns leaf page unpinned)
	 */
	pxd = &sp->header.self;
	xlen = lengthPXD(pxd);
	xsize = xlen << sbi->l2bsize;
	अगर (xsize < PSIZE) अणु
		xaddr = addressPXD(pxd);
		n = xsize >> L2DTSLOTSIZE;
		n -= (n + 31) >> L2DTSLOTSIZE;	/* stbl size */
		अगर ((n + sp->header.मुक्तcnt) <= split->nslot)
			n = xlen + (xlen << 1);
		अन्यथा
			n = xlen;

		/* Allocate blocks to quota. */
		rc = dquot_alloc_block(ip, n);
		अगर (rc)
			जाओ extendOut;
		quota_allocation += n;

		अगर ((rc = dbReAlloc(sbi->ipbmap, xaddr, (s64) xlen,
				    (s64) n, &nxaddr)))
			जाओ extendOut;

		pxdlist.maxnpxd = 1;
		pxdlist.npxd = 0;
		pxd = &pxdlist.pxd[0];
		PXDaddress(pxd, nxaddr);
		PXDlength(pxd, xlen + n);
		split->pxdlist = &pxdlist;
		अगर ((rc = dtExtendPage(tid, ip, split, btstack))) अणु
			nxaddr = addressPXD(pxd);
			अगर (xaddr != nxaddr) अणु
				/* मुक्त relocated extent */
				xlen = lengthPXD(pxd);
				dbFree(ip, nxaddr, (s64) xlen);
			पूर्ण अन्यथा अणु
				/* मुक्त extended delta */
				xlen = lengthPXD(pxd) - n;
				xaddr = addressPXD(pxd) + xlen;
				dbFree(ip, xaddr, (s64) n);
			पूर्ण
		पूर्ण अन्यथा अगर (!DO_INDEX(ip))
			ip->i_size = lengthPXD(pxd) << sbi->l2bsize;


	      extendOut:
		DT_PUTPAGE(smp);
		जाओ मुक्तKeyName;
	पूर्ण

	/*
	 *	split leaf page <sp> पूर्णांकo <sp> and a new right page <rp>.
	 *
	 * वापस <rp> pinned and its extent descriptor <rpxd>
	 */
	/*
	 * allocate new directory page extent and
	 * new index page(s) to cover page split(s)
	 *
	 * allocation hपूर्णांक: ?
	 */
	n = btstack->nsplit;
	pxdlist.maxnpxd = pxdlist.npxd = 0;
	xlen = sbi->nbperpage;
	क्रम (pxd = pxdlist.pxd; n > 0; n--, pxd++) अणु
		अगर ((rc = dbAlloc(ip, 0, (s64) xlen, &xaddr)) == 0) अणु
			PXDaddress(pxd, xaddr);
			PXDlength(pxd, xlen);
			pxdlist.maxnpxd++;
			जारी;
		पूर्ण

		DT_PUTPAGE(smp);

		/* unकरो allocation */
		जाओ splitOut;
	पूर्ण

	split->pxdlist = &pxdlist;
	अगर ((rc = dtSplitPage(tid, ip, split, &rmp, &rp, &rpxd))) अणु
		DT_PUTPAGE(smp);

		/* unकरो allocation */
		जाओ splitOut;
	पूर्ण

	अगर (!DO_INDEX(ip))
		ip->i_size += PSIZE;

	/*
	 * propagate up the router entry क्रम the leaf page just split
	 *
	 * insert a router entry क्रम the new page पूर्णांकo the parent page,
	 * propagate the insert/split up the tree by walking back the stack
	 * of (bn of parent page, index of child page entry in parent page)
	 * that were traversed during the search क्रम the page that split.
	 *
	 * the propagation of insert/split up the tree stops अगर the root
	 * splits or the page inserted पूर्णांकo करोesn't have to split to hold
	 * the new entry.
	 *
	 * the parent entry क्रम the split page reमुख्यs the same, and
	 * a new entry is inserted at its right with the first key and
	 * block number of the new right page.
	 *
	 * There are a maximum of 4 pages pinned at any समय:
	 * two children, left parent and right parent (when the parent splits).
	 * keep the child pages pinned जबतक working on the parent.
	 * make sure that all pins are released at निकास.
	 */
	जबतक ((parent = BT_POP(btstack)) != शून्य) अणु
		/* parent page specअगरied by stack frame <parent> */

		/* keep current child pages (<lp>, <rp>) pinned */
		lmp = smp;
		lp = sp;

		/*
		 * insert router entry in parent क्रम new right child page <rp>
		 */
		/* get the parent page <sp> */
		DT_GETPAGE(ip, parent->bn, smp, PSIZE, sp, rc);
		अगर (rc) अणु
			DT_PUTPAGE(lmp);
			DT_PUTPAGE(rmp);
			जाओ splitOut;
		पूर्ण

		/*
		 * The new key entry goes ONE AFTER the index of parent entry,
		 * because the split was to the right.
		 */
		skip = parent->index + 1;

		/*
		 * compute the key क्रम the router entry
		 *
		 * key suffix compression:
		 * क्रम पूर्णांकernal pages that have leaf pages as children,
		 * retain only what's needed to distinguish between
		 * the new entry and the entry on the page to its left.
		 * If the keys compare equal, retain the entire key.
		 *
		 * note that compression is perक्रमmed only at computing
		 * router key at the lowest पूर्णांकernal level.
		 * further compression of the key between pairs of higher
		 * level पूर्णांकernal pages loses too much inक्रमmation and
		 * the search may fail.
		 * (e.g., two adjacent leaf pages of अणुa, ..., xपूर्ण अणुxx, ...,पूर्ण
		 * results in two adjacent parent entries (a)(xx).
		 * अगर split occurs between these two entries, and
		 * अगर compression is applied, the router key of parent entry
		 * of right page (x) will भागert search क्रम x पूर्णांकo right
		 * subtree and miss x in the left subtree.)
		 *
		 * the entire key must be retained क्रम the next-to-lefपंचांगost
		 * पूर्णांकernal key at any level of the tree, or search may fail
		 * (e.g., ?)
		 */
		चयन (rp->header.flag & BT_TYPE) अणु
		हाल BT_LEAF:
			/*
			 * compute the length of prefix क्रम suffix compression
			 * between last entry of left page and first entry
			 * of right page
			 */
			अगर ((sp->header.flag & BT_ROOT && skip > 1) ||
			    sp->header.prev != 0 || skip > 1) अणु
				/* compute upperहाल router prefix key */
				rc = ciGetLeafPrefixKey(lp,
							lp->header.nextindex-1,
							rp, 0, &key,
							sbi->mntflag);
				अगर (rc) अणु
					DT_PUTPAGE(lmp);
					DT_PUTPAGE(rmp);
					DT_PUTPAGE(smp);
					जाओ splitOut;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* next to lefपंचांगost entry of
				   lowest पूर्णांकernal level */

				/* compute upperहाल router key */
				dtGetKey(rp, 0, &key, sbi->mntflag);
				key.name[key.namlen] = 0;

				अगर ((sbi->mntflag & JFS_OS2) == JFS_OS2)
					ciToUpper(&key);
			पूर्ण

			n = NDTINTERNAL(key.namlen);
			अवरोध;

		हाल BT_INTERNAL:
			dtGetKey(rp, 0, &key, sbi->mntflag);
			n = NDTINTERNAL(key.namlen);
			अवरोध;

		शेष:
			jfs_err("dtSplitUp(): UFO!");
			अवरोध;
		पूर्ण

		/* unpin left child page */
		DT_PUTPAGE(lmp);

		/*
		 * compute the data क्रम the router entry
		 */
		data->xd = rpxd;	/* child page xd */

		/*
		 * parent page is full - split the parent page
		 */
		अगर (n > sp->header.मुक्तcnt) अणु
			/* init क्रम parent page split */
			split->mp = smp;
			split->index = skip;	/* index at insert */
			split->nslot = n;
			split->key = &key;
			/* split->data = data; */

			/* unpin right child page */
			DT_PUTPAGE(rmp);

			/* The split routines insert the new entry,
			 * acquire txLock as appropriate.
			 * वापस <rp> pinned and its block number <rbn>.
			 */
			rc = (sp->header.flag & BT_ROOT) ?
			    dtSplitRoot(tid, ip, split, &rmp) :
			    dtSplitPage(tid, ip, split, &rmp, &rp, &rpxd);
			अगर (rc) अणु
				DT_PUTPAGE(smp);
				जाओ splitOut;
			पूर्ण

			/* smp and rmp are pinned */
		पूर्ण
		/*
		 * parent page is not full - insert router entry in parent page
		 */
		अन्यथा अणु
			BT_MARK_सूचीTY(smp, ip);
			/*
			 * acquire a transaction lock on the parent page
			 */
			tlck = txLock(tid, ip, smp, tlckDTREE | tlckENTRY);
			dtlck = (काष्ठा dt_lock *) & tlck->lock;
			ASSERT(dtlck->index == 0);
			lv = & dtlck->lv[0];

			/* linelock header */
			lv->offset = 0;
			lv->length = 1;
			dtlck->index++;

			/* linelock stbl of non-root parent page */
			अगर (!(sp->header.flag & BT_ROOT)) अणु
				lv++;
				n = skip >> L2DTSLOTSIZE;
				lv->offset = sp->header.stblindex + n;
				lv->length =
				    ((sp->header.nextindex -
				      1) >> L2DTSLOTSIZE) - n + 1;
				dtlck->index++;
			पूर्ण

			dtInsertEntry(sp, skip, &key, data, &dtlck);

			/* निकास propagate up */
			अवरोध;
		पूर्ण
	पूर्ण

	/* unpin current split and its right page */
	DT_PUTPAGE(smp);
	DT_PUTPAGE(rmp);

	/*
	 * मुक्त reमुख्यing extents allocated क्रम split
	 */
      splitOut:
	n = pxdlist.npxd;
	pxd = &pxdlist.pxd[n];
	क्रम (; n < pxdlist.maxnpxd; n++, pxd++)
		dbFree(ip, addressPXD(pxd), (s64) lengthPXD(pxd));

      मुक्तKeyName:
	kमुक्त(key.name);

	/* Rollback quota allocation */
	अगर (rc && quota_allocation)
		dquot_मुक्त_block(ip, quota_allocation);

      dtSplitUp_Exit:

	वापस rc;
पूर्ण


/*
 *	dtSplitPage()
 *
 * function: Split a non-root page of a btree.
 *
 * parameter:
 *
 * वापस: 0 - success;
 *	   त्रुटि_सं - failure;
 *	वापस split and new page pinned;
 */
अटल पूर्णांक dtSplitPage(tid_t tid, काष्ठा inode *ip, काष्ठा dtsplit * split,
	    काष्ठा metapage ** rmpp, dtpage_t ** rpp, pxd_t * rpxdp)
अणु
	पूर्णांक rc = 0;
	काष्ठा metapage *smp;
	dtpage_t *sp;
	काष्ठा metapage *rmp;
	dtpage_t *rp;		/* new right page allocated */
	s64 rbn;		/* new right page block number */
	काष्ठा metapage *mp;
	dtpage_t *p;
	s64 nextbn;
	काष्ठा pxdlist *pxdlist;
	pxd_t *pxd;
	पूर्णांक skip, nextindex, half, left, nxt, off, si;
	काष्ठा ldtentry *ldtentry;
	काष्ठा idtentry *idtentry;
	u8 *stbl;
	काष्ठा dtslot *f;
	पूर्णांक fsi, stblsize;
	पूर्णांक n;
	काष्ठा dt_lock *sdtlck, *rdtlck;
	काष्ठा tlock *tlck;
	काष्ठा dt_lock *dtlck;
	काष्ठा lv *slv, *rlv, *lv;

	/* get split page */
	smp = split->mp;
	sp = DT_PAGE(ip, smp);

	/*
	 * allocate the new right page क्रम the split
	 */
	pxdlist = split->pxdlist;
	pxd = &pxdlist->pxd[pxdlist->npxd];
	pxdlist->npxd++;
	rbn = addressPXD(pxd);
	rmp = get_metapage(ip, rbn, PSIZE, 1);
	अगर (rmp == शून्य)
		वापस -EIO;

	/* Allocate blocks to quota. */
	rc = dquot_alloc_block(ip, lengthPXD(pxd));
	अगर (rc) अणु
		release_metapage(rmp);
		वापस rc;
	पूर्ण

	jfs_info("dtSplitPage: ip:0x%p smp:0x%p rmp:0x%p", ip, smp, rmp);

	BT_MARK_सूचीTY(rmp, ip);
	/*
	 * acquire a transaction lock on the new right page
	 */
	tlck = txLock(tid, ip, rmp, tlckDTREE | tlckNEW);
	rdtlck = (काष्ठा dt_lock *) & tlck->lock;

	rp = (dtpage_t *) rmp->data;
	*rpp = rp;
	rp->header.self = *pxd;

	BT_MARK_सूचीTY(smp, ip);
	/*
	 * acquire a transaction lock on the split page
	 *
	 * action:
	 */
	tlck = txLock(tid, ip, smp, tlckDTREE | tlckENTRY);
	sdtlck = (काष्ठा dt_lock *) & tlck->lock;

	/* linelock header of split page */
	ASSERT(sdtlck->index == 0);
	slv = & sdtlck->lv[0];
	slv->offset = 0;
	slv->length = 1;
	sdtlck->index++;

	/*
	 * initialize/update sibling poपूर्णांकers between sp and rp
	 */
	nextbn = le64_to_cpu(sp->header.next);
	rp->header.next = cpu_to_le64(nextbn);
	rp->header.prev = cpu_to_le64(addressPXD(&sp->header.self));
	sp->header.next = cpu_to_le64(rbn);

	/*
	 * initialize new right page
	 */
	rp->header.flag = sp->header.flag;

	/* compute sorted entry table at start of extent data area */
	rp->header.nextindex = 0;
	rp->header.stblindex = 1;

	n = PSIZE >> L2DTSLOTSIZE;
	rp->header.maxslot = n;
	stblsize = (n + 31) >> L2DTSLOTSIZE;	/* in unit of slot */

	/* init मुक्तlist */
	fsi = rp->header.stblindex + stblsize;
	rp->header.मुक्तlist = fsi;
	rp->header.मुक्तcnt = rp->header.maxslot - fsi;

	/*
	 *	sequential append at tail: append without split
	 *
	 * If splitting the last page on a level because of appending
	 * a entry to it (skip is maxentry), it's likely that the access is
	 * sequential. Adding an empty page on the side of the level is less
	 * work and can push the fill factor much higher than normal.
	 * If we're wrong it's no big deal, we'll just करो the split the right
	 * way next समय.
	 * (It may look like it's equally easy to करो a similar hack क्रम
	 * reverse sorted data, that is, split the tree left,
	 * but it's not. Be my guest.)
	 */
	अगर (nextbn == 0 && split->index == sp->header.nextindex) अणु
		/* linelock header + stbl (first slot) of new page */
		rlv = & rdtlck->lv[rdtlck->index];
		rlv->offset = 0;
		rlv->length = 2;
		rdtlck->index++;

		/*
		 * initialize मुक्तlist of new right page
		 */
		f = &rp->slot[fsi];
		क्रम (fsi++; fsi < rp->header.maxslot; f++, fsi++)
			f->next = fsi;
		f->next = -1;

		/* insert entry at the first entry of the new right page */
		dtInsertEntry(rp, 0, split->key, split->data, &rdtlck);

		जाओ out;
	पूर्ण

	/*
	 *	non-sequential insert (at possibly middle page)
	 */

	/*
	 * update prev poपूर्णांकer of previous right sibling page;
	 */
	अगर (nextbn != 0) अणु
		DT_GETPAGE(ip, nextbn, mp, PSIZE, p, rc);
		अगर (rc) अणु
			discard_metapage(rmp);
			वापस rc;
		पूर्ण

		BT_MARK_सूचीTY(mp, ip);
		/*
		 * acquire a transaction lock on the next page
		 */
		tlck = txLock(tid, ip, mp, tlckDTREE | tlckRELINK);
		jfs_info("dtSplitPage: tlck = 0x%p, ip = 0x%p, mp=0x%p",
			tlck, ip, mp);
		dtlck = (काष्ठा dt_lock *) & tlck->lock;

		/* linelock header of previous right sibling page */
		lv = & dtlck->lv[dtlck->index];
		lv->offset = 0;
		lv->length = 1;
		dtlck->index++;

		p->header.prev = cpu_to_le64(rbn);

		DT_PUTPAGE(mp);
	पूर्ण

	/*
	 * split the data between the split and right pages.
	 */
	skip = split->index;
	half = (PSIZE >> L2DTSLOTSIZE) >> 1;	/* swag */
	left = 0;

	/*
	 *	compute fill factor क्रम split pages
	 *
	 * <nxt> traces the next entry to move to rp
	 * <off> traces the next entry to stay in sp
	 */
	stbl = (u8 *) & sp->slot[sp->header.stblindex];
	nextindex = sp->header.nextindex;
	क्रम (nxt = off = 0; nxt < nextindex; ++off) अणु
		अगर (off == skip)
			/* check क्रम fill factor with new entry size */
			n = split->nslot;
		अन्यथा अणु
			si = stbl[nxt];
			चयन (sp->header.flag & BT_TYPE) अणु
			हाल BT_LEAF:
				ldtentry = (काष्ठा ldtentry *) & sp->slot[si];
				अगर (DO_INDEX(ip))
					n = NDTLEAF(ldtentry->namlen);
				अन्यथा
					n = NDTLEAF_LEGACY(ldtentry->
							   namlen);
				अवरोध;

			हाल BT_INTERNAL:
				idtentry = (काष्ठा idtentry *) & sp->slot[si];
				n = NDTINTERNAL(idtentry->namlen);
				अवरोध;

			शेष:
				अवरोध;
			पूर्ण

			++nxt;	/* advance to next entry to move in sp */
		पूर्ण

		left += n;
		अगर (left >= half)
			अवरोध;
	पूर्ण

	/* <nxt> poins to the 1st entry to move */

	/*
	 *	move entries to right page
	 *
	 * dtMoveEntry() initializes rp and reserves entry क्रम insertion
	 *
	 * split page moved out entries are linelocked;
	 * new/right page moved in entries are linelocked;
	 */
	/* linelock header + stbl of new right page */
	rlv = & rdtlck->lv[rdtlck->index];
	rlv->offset = 0;
	rlv->length = 5;
	rdtlck->index++;

	dtMoveEntry(sp, nxt, rp, &sdtlck, &rdtlck, DO_INDEX(ip));

	sp->header.nextindex = nxt;

	/*
	 * finalize मुक्तlist of new right page
	 */
	fsi = rp->header.मुक्तlist;
	f = &rp->slot[fsi];
	क्रम (fsi++; fsi < rp->header.maxslot; f++, fsi++)
		f->next = fsi;
	f->next = -1;

	/*
	 * Update directory index table क्रम entries now in right page
	 */
	अगर ((rp->header.flag & BT_LEAF) && DO_INDEX(ip)) अणु
		s64 lblock;

		mp = शून्य;
		stbl = DT_GETSTBL(rp);
		क्रम (n = 0; n < rp->header.nextindex; n++) अणु
			ldtentry = (काष्ठा ldtentry *) & rp->slot[stbl[n]];
			modअगरy_index(tid, ip, le32_to_cpu(ldtentry->index),
				     rbn, n, &mp, &lblock);
		पूर्ण
		अगर (mp)
			release_metapage(mp);
	पूर्ण

	/*
	 * the skipped index was on the left page,
	 */
	अगर (skip <= off) अणु
		/* insert the new entry in the split page */
		dtInsertEntry(sp, skip, split->key, split->data, &sdtlck);

		/* linelock stbl of split page */
		अगर (sdtlck->index >= sdtlck->maxcnt)
			sdtlck = (काष्ठा dt_lock *) txLinelock(sdtlck);
		slv = & sdtlck->lv[sdtlck->index];
		n = skip >> L2DTSLOTSIZE;
		slv->offset = sp->header.stblindex + n;
		slv->length =
		    ((sp->header.nextindex - 1) >> L2DTSLOTSIZE) - n + 1;
		sdtlck->index++;
	पूर्ण
	/*
	 * the skipped index was on the right page,
	 */
	अन्यथा अणु
		/* adjust the skip index to reflect the new position */
		skip -= nxt;

		/* insert the new entry in the right page */
		dtInsertEntry(rp, skip, split->key, split->data, &rdtlck);
	पूर्ण

      out:
	*rmpp = rmp;
	*rpxdp = *pxd;

	वापस rc;
पूर्ण


/*
 *	dtExtendPage()
 *
 * function: extend 1st/only directory leaf page
 *
 * parameter:
 *
 * वापस: 0 - success;
 *	   त्रुटि_सं - failure;
 *	वापस extended page pinned;
 */
अटल पूर्णांक dtExtendPage(tid_t tid,
	     काष्ठा inode *ip, काष्ठा dtsplit * split, काष्ठा btstack * btstack)
अणु
	काष्ठा super_block *sb = ip->i_sb;
	पूर्णांक rc;
	काष्ठा metapage *smp, *pmp, *mp;
	dtpage_t *sp, *pp;
	काष्ठा pxdlist *pxdlist;
	pxd_t *pxd, *tpxd;
	पूर्णांक xlen, xsize;
	पूर्णांक newstblindex, newstblsize;
	पूर्णांक oldstblindex, oldstblsize;
	पूर्णांक fsi, last;
	काष्ठा dtslot *f;
	काष्ठा btframe *parent;
	पूर्णांक n;
	काष्ठा dt_lock *dtlck;
	s64 xaddr, txaddr;
	काष्ठा tlock *tlck;
	काष्ठा pxd_lock *pxdlock;
	काष्ठा lv *lv;
	uपूर्णांक type;
	काष्ठा ldtentry *ldtentry;
	u8 *stbl;

	/* get page to extend */
	smp = split->mp;
	sp = DT_PAGE(ip, smp);

	/* get parent/root page */
	parent = BT_POP(btstack);
	DT_GETPAGE(ip, parent->bn, pmp, PSIZE, pp, rc);
	अगर (rc)
		वापस (rc);

	/*
	 *	extend the extent
	 */
	pxdlist = split->pxdlist;
	pxd = &pxdlist->pxd[pxdlist->npxd];
	pxdlist->npxd++;

	xaddr = addressPXD(pxd);
	tpxd = &sp->header.self;
	txaddr = addressPXD(tpxd);
	/* in-place extension */
	अगर (xaddr == txaddr) अणु
		type = tlckEXTEND;
	पूर्ण
	/* relocation */
	अन्यथा अणु
		type = tlckNEW;

		/* save moved extent descriptor क्रम later मुक्त */
		tlck = txMaplock(tid, ip, tlckDTREE | tlckRELOCATE);
		pxdlock = (काष्ठा pxd_lock *) & tlck->lock;
		pxdlock->flag = mlckFREEPXD;
		pxdlock->pxd = sp->header.self;
		pxdlock->index = 1;

		/*
		 * Update directory index table to reflect new page address
		 */
		अगर (DO_INDEX(ip)) अणु
			s64 lblock;

			mp = शून्य;
			stbl = DT_GETSTBL(sp);
			क्रम (n = 0; n < sp->header.nextindex; n++) अणु
				ldtentry =
				    (काष्ठा ldtentry *) & sp->slot[stbl[n]];
				modअगरy_index(tid, ip,
					     le32_to_cpu(ldtentry->index),
					     xaddr, n, &mp, &lblock);
			पूर्ण
			अगर (mp)
				release_metapage(mp);
		पूर्ण
	पूर्ण

	/*
	 *	extend the page
	 */
	sp->header.self = *pxd;

	jfs_info("dtExtendPage: ip:0x%p smp:0x%p sp:0x%p", ip, smp, sp);

	BT_MARK_सूचीTY(smp, ip);
	/*
	 * acquire a transaction lock on the extended/leaf page
	 */
	tlck = txLock(tid, ip, smp, tlckDTREE | type);
	dtlck = (काष्ठा dt_lock *) & tlck->lock;
	lv = & dtlck->lv[0];

	/* update buffer extent descriptor of extended page */
	xlen = lengthPXD(pxd);
	xsize = xlen << JFS_SBI(sb)->l2bsize;

	/*
	 * copy old stbl to new stbl at start of extended area
	 */
	oldstblindex = sp->header.stblindex;
	oldstblsize = (sp->header.maxslot + 31) >> L2DTSLOTSIZE;
	newstblindex = sp->header.maxslot;
	n = xsize >> L2DTSLOTSIZE;
	newstblsize = (n + 31) >> L2DTSLOTSIZE;
	स_नकल(&sp->slot[newstblindex], &sp->slot[oldstblindex],
	       sp->header.nextindex);

	/*
	 * in-line extension: linelock old area of extended page
	 */
	अगर (type == tlckEXTEND) अणु
		/* linelock header */
		lv->offset = 0;
		lv->length = 1;
		dtlck->index++;
		lv++;

		/* linelock new stbl of extended page */
		lv->offset = newstblindex;
		lv->length = newstblsize;
	पूर्ण
	/*
	 * relocation: linelock whole relocated area
	 */
	अन्यथा अणु
		lv->offset = 0;
		lv->length = sp->header.maxslot + newstblsize;
	पूर्ण

	dtlck->index++;

	sp->header.maxslot = n;
	sp->header.stblindex = newstblindex;
	/* sp->header.nextindex reमुख्यs the same */

	/*
	 * add old stbl region at head of मुक्तlist
	 */
	fsi = oldstblindex;
	f = &sp->slot[fsi];
	last = sp->header.मुक्तlist;
	क्रम (n = 0; n < oldstblsize; n++, fsi++, f++) अणु
		f->next = last;
		last = fsi;
	पूर्ण
	sp->header.मुक्तlist = last;
	sp->header.मुक्तcnt += oldstblsize;

	/*
	 * append मुक्त region of newly extended area at tail of मुक्तlist
	 */
	/* init मुक्त region of newly extended area */
	fsi = n = newstblindex + newstblsize;
	f = &sp->slot[fsi];
	क्रम (fsi++; fsi < sp->header.maxslot; f++, fsi++)
		f->next = fsi;
	f->next = -1;

	/* append new मुक्त region at tail of old मुक्तlist */
	fsi = sp->header.मुक्तlist;
	अगर (fsi == -1)
		sp->header.मुक्तlist = n;
	अन्यथा अणु
		करो अणु
			f = &sp->slot[fsi];
			fsi = f->next;
		पूर्ण जबतक (fsi != -1);

		f->next = n;
	पूर्ण

	sp->header.मुक्तcnt += sp->header.maxslot - n;

	/*
	 * insert the new entry
	 */
	dtInsertEntry(sp, split->index, split->key, split->data, &dtlck);

	BT_MARK_सूचीTY(pmp, ip);
	/*
	 * linelock any मुक्तslots residing in old extent
	 */
	अगर (type == tlckEXTEND) अणु
		n = sp->header.maxslot >> 2;
		अगर (sp->header.मुक्तlist < n)
			dtLinelockFreelist(sp, n, &dtlck);
	पूर्ण

	/*
	 *	update parent entry on the parent/root page
	 */
	/*
	 * acquire a transaction lock on the parent/root page
	 */
	tlck = txLock(tid, ip, pmp, tlckDTREE | tlckENTRY);
	dtlck = (काष्ठा dt_lock *) & tlck->lock;
	lv = & dtlck->lv[dtlck->index];

	/* linelock parent entry - 1st slot */
	lv->offset = 1;
	lv->length = 1;
	dtlck->index++;

	/* update the parent pxd क्रम page extension */
	tpxd = (pxd_t *) & pp->slot[1];
	*tpxd = *pxd;

	DT_PUTPAGE(pmp);
	वापस 0;
पूर्ण


/*
 *	dtSplitRoot()
 *
 * function:
 *	split the full root page पूर्णांकo
 *	original/root/split page and new right page
 *	i.e., root reमुख्यs fixed in tree anchor (inode) and
 *	the root is copied to a single new right child page
 *	since root page << non-root page, and
 *	the split root page contains a single entry क्रम the
 *	new right child page.
 *
 * parameter:
 *
 * वापस: 0 - success;
 *	   त्रुटि_सं - failure;
 *	वापस new page pinned;
 */
अटल पूर्णांक dtSplitRoot(tid_t tid,
	    काष्ठा inode *ip, काष्ठा dtsplit * split, काष्ठा metapage ** rmpp)
अणु
	काष्ठा super_block *sb = ip->i_sb;
	काष्ठा metapage *smp;
	dtroot_t *sp;
	काष्ठा metapage *rmp;
	dtpage_t *rp;
	s64 rbn;
	पूर्णांक xlen;
	पूर्णांक xsize;
	काष्ठा dtslot *f;
	s8 *stbl;
	पूर्णांक fsi, stblsize, n;
	काष्ठा idtentry *s;
	pxd_t *ppxd;
	काष्ठा pxdlist *pxdlist;
	pxd_t *pxd;
	काष्ठा dt_lock *dtlck;
	काष्ठा tlock *tlck;
	काष्ठा lv *lv;
	पूर्णांक rc;

	/* get split root page */
	smp = split->mp;
	sp = &JFS_IP(ip)->i_dtroot;

	/*
	 *	allocate/initialize a single (right) child page
	 *
	 * N.B. at first split, a one (or two) block to fit new entry
	 * is allocated; at subsequent split, a full page is allocated;
	 */
	pxdlist = split->pxdlist;
	pxd = &pxdlist->pxd[pxdlist->npxd];
	pxdlist->npxd++;
	rbn = addressPXD(pxd);
	xlen = lengthPXD(pxd);
	xsize = xlen << JFS_SBI(sb)->l2bsize;
	rmp = get_metapage(ip, rbn, xsize, 1);
	अगर (!rmp)
		वापस -EIO;

	rp = rmp->data;

	/* Allocate blocks to quota. */
	rc = dquot_alloc_block(ip, lengthPXD(pxd));
	अगर (rc) अणु
		release_metapage(rmp);
		वापस rc;
	पूर्ण

	BT_MARK_सूचीTY(rmp, ip);
	/*
	 * acquire a transaction lock on the new right page
	 */
	tlck = txLock(tid, ip, rmp, tlckDTREE | tlckNEW);
	dtlck = (काष्ठा dt_lock *) & tlck->lock;

	rp->header.flag =
	    (sp->header.flag & BT_LEAF) ? BT_LEAF : BT_INTERNAL;
	rp->header.self = *pxd;

	/* initialize sibling poपूर्णांकers */
	rp->header.next = 0;
	rp->header.prev = 0;

	/*
	 *	move in-line root page पूर्णांकo new right page extent
	 */
	/* linelock header + copied entries + new stbl (1st slot) in new page */
	ASSERT(dtlck->index == 0);
	lv = & dtlck->lv[0];
	lv->offset = 0;
	lv->length = 10;	/* 1 + 8 + 1 */
	dtlck->index++;

	n = xsize >> L2DTSLOTSIZE;
	rp->header.maxslot = n;
	stblsize = (n + 31) >> L2DTSLOTSIZE;

	/* copy old stbl to new stbl at start of extended area */
	rp->header.stblindex = DTROOTMAXSLOT;
	stbl = (s8 *) & rp->slot[DTROOTMAXSLOT];
	स_नकल(stbl, sp->header.stbl, sp->header.nextindex);
	rp->header.nextindex = sp->header.nextindex;

	/* copy old data area to start of new data area */
	स_नकल(&rp->slot[1], &sp->slot[1], IDATASIZE);

	/*
	 * append मुक्त region of newly extended area at tail of मुक्तlist
	 */
	/* init मुक्त region of newly extended area */
	fsi = n = DTROOTMAXSLOT + stblsize;
	f = &rp->slot[fsi];
	क्रम (fsi++; fsi < rp->header.maxslot; f++, fsi++)
		f->next = fsi;
	f->next = -1;

	/* append new मुक्त region at tail of old मुक्तlist */
	fsi = sp->header.मुक्तlist;
	अगर (fsi == -1)
		rp->header.मुक्तlist = n;
	अन्यथा अणु
		rp->header.मुक्तlist = fsi;

		करो अणु
			f = &rp->slot[fsi];
			fsi = f->next;
		पूर्ण जबतक (fsi != -1);

		f->next = n;
	पूर्ण

	rp->header.मुक्तcnt = sp->header.मुक्तcnt + rp->header.maxslot - n;

	/*
	 * Update directory index table क्रम entries now in right page
	 */
	अगर ((rp->header.flag & BT_LEAF) && DO_INDEX(ip)) अणु
		s64 lblock;
		काष्ठा metapage *mp = शून्य;
		काष्ठा ldtentry *ldtentry;

		stbl = DT_GETSTBL(rp);
		क्रम (n = 0; n < rp->header.nextindex; n++) अणु
			ldtentry = (काष्ठा ldtentry *) & rp->slot[stbl[n]];
			modअगरy_index(tid, ip, le32_to_cpu(ldtentry->index),
				     rbn, n, &mp, &lblock);
		पूर्ण
		अगर (mp)
			release_metapage(mp);
	पूर्ण
	/*
	 * insert the new entry पूर्णांकo the new right/child page
	 * (skip index in the new right page will not change)
	 */
	dtInsertEntry(rp, split->index, split->key, split->data, &dtlck);

	/*
	 *	reset parent/root page
	 *
	 * set the 1st entry offset to 0, which क्रमce the left-most key
	 * at any level of the tree to be less than any search key.
	 *
	 * The btree comparison code guarantees that the left-most key on any
	 * level of the tree is never used, so it करोesn't need to be filled in.
	 */
	BT_MARK_सूचीTY(smp, ip);
	/*
	 * acquire a transaction lock on the root page (in-memory inode)
	 */
	tlck = txLock(tid, ip, smp, tlckDTREE | tlckNEW | tlckBTROOT);
	dtlck = (काष्ठा dt_lock *) & tlck->lock;

	/* linelock root */
	ASSERT(dtlck->index == 0);
	lv = & dtlck->lv[0];
	lv->offset = 0;
	lv->length = DTROOTMAXSLOT;
	dtlck->index++;

	/* update page header of root */
	अगर (sp->header.flag & BT_LEAF) अणु
		sp->header.flag &= ~BT_LEAF;
		sp->header.flag |= BT_INTERNAL;
	पूर्ण

	/* init the first entry */
	s = (काष्ठा idtentry *) & sp->slot[DTENTRYSTART];
	ppxd = (pxd_t *) s;
	*ppxd = *pxd;
	s->next = -1;
	s->namlen = 0;

	stbl = sp->header.stbl;
	stbl[0] = DTENTRYSTART;
	sp->header.nextindex = 1;

	/* init मुक्तlist */
	fsi = DTENTRYSTART + 1;
	f = &sp->slot[fsi];

	/* init मुक्त region of reमुख्यing area */
	क्रम (fsi++; fsi < DTROOTMAXSLOT; f++, fsi++)
		f->next = fsi;
	f->next = -1;

	sp->header.मुक्तlist = DTENTRYSTART + 1;
	sp->header.मुक्तcnt = DTROOTMAXSLOT - (DTENTRYSTART + 1);

	*rmpp = rmp;

	वापस 0;
पूर्ण


/*
 *	dtDelete()
 *
 * function: delete the entry(s) referenced by a key.
 *
 * parameter:
 *
 * वापस:
 */
पूर्णांक dtDelete(tid_t tid,
	 काष्ठा inode *ip, काष्ठा component_name * key, ino_t * ino, पूर्णांक flag)
अणु
	पूर्णांक rc = 0;
	s64 bn;
	काष्ठा metapage *mp, *imp;
	dtpage_t *p;
	पूर्णांक index;
	काष्ठा btstack btstack;
	काष्ठा dt_lock *dtlck;
	काष्ठा tlock *tlck;
	काष्ठा lv *lv;
	पूर्णांक i;
	काष्ठा ldtentry *ldtentry;
	u8 *stbl;
	u32 table_index, next_index;
	काष्ठा metapage *nmp;
	dtpage_t *np;

	/*
	 *	search क्रम the entry to delete:
	 *
	 * dtSearch() वापसs (leaf page pinned, index at which to delete).
	 */
	अगर ((rc = dtSearch(ip, key, ino, &btstack, flag)))
		वापस rc;

	/* retrieve search result */
	DT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

	/*
	 * We need to find put the index of the next entry पूर्णांकo the
	 * directory index table in order to resume a सूची_पढ़ो from this
	 * entry.
	 */
	अगर (DO_INDEX(ip)) अणु
		stbl = DT_GETSTBL(p);
		ldtentry = (काष्ठा ldtentry *) & p->slot[stbl[index]];
		table_index = le32_to_cpu(ldtentry->index);
		अगर (index == (p->header.nextindex - 1)) अणु
			/*
			 * Last entry in this leaf page
			 */
			अगर ((p->header.flag & BT_ROOT)
			    || (p->header.next == 0))
				next_index = -1;
			अन्यथा अणु
				/* Read next leaf page */
				DT_GETPAGE(ip, le64_to_cpu(p->header.next),
					   nmp, PSIZE, np, rc);
				अगर (rc)
					next_index = -1;
				अन्यथा अणु
					stbl = DT_GETSTBL(np);
					ldtentry =
					    (काष्ठा ldtentry *) & np->
					    slot[stbl[0]];
					next_index =
					    le32_to_cpu(ldtentry->index);
					DT_PUTPAGE(nmp);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			ldtentry =
			    (काष्ठा ldtentry *) & p->slot[stbl[index + 1]];
			next_index = le32_to_cpu(ldtentry->index);
		पूर्ण
		मुक्त_index(tid, ip, table_index, next_index);
	पूर्ण
	/*
	 * the leaf page becomes empty, delete the page
	 */
	अगर (p->header.nextindex == 1) अणु
		/* delete empty page */
		rc = dtDeleteUp(tid, ip, mp, p, &btstack);
	पूर्ण
	/*
	 * the leaf page has other entries reमुख्यing:
	 *
	 * delete the entry from the leaf page.
	 */
	अन्यथा अणु
		BT_MARK_सूचीTY(mp, ip);
		/*
		 * acquire a transaction lock on the leaf page
		 */
		tlck = txLock(tid, ip, mp, tlckDTREE | tlckENTRY);
		dtlck = (काष्ठा dt_lock *) & tlck->lock;

		/*
		 * Do not assume that dtlck->index will be zero.  During a
		 * नाम within a directory, this transaction may have
		 * modअगरied this page alपढ़ोy when adding the new entry.
		 */

		/* linelock header */
		अगर (dtlck->index >= dtlck->maxcnt)
			dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
		lv = & dtlck->lv[dtlck->index];
		lv->offset = 0;
		lv->length = 1;
		dtlck->index++;

		/* linelock stbl of non-root leaf page */
		अगर (!(p->header.flag & BT_ROOT)) अणु
			अगर (dtlck->index >= dtlck->maxcnt)
				dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
			lv = & dtlck->lv[dtlck->index];
			i = index >> L2DTSLOTSIZE;
			lv->offset = p->header.stblindex + i;
			lv->length =
			    ((p->header.nextindex - 1) >> L2DTSLOTSIZE) -
			    i + 1;
			dtlck->index++;
		पूर्ण

		/* मुक्त the leaf entry */
		dtDeleteEntry(p, index, &dtlck);

		/*
		 * Update directory index table क्रम entries moved in stbl
		 */
		अगर (DO_INDEX(ip) && index < p->header.nextindex) अणु
			s64 lblock;

			imp = शून्य;
			stbl = DT_GETSTBL(p);
			क्रम (i = index; i < p->header.nextindex; i++) अणु
				ldtentry =
				    (काष्ठा ldtentry *) & p->slot[stbl[i]];
				modअगरy_index(tid, ip,
					     le32_to_cpu(ldtentry->index),
					     bn, i, &imp, &lblock);
			पूर्ण
			अगर (imp)
				release_metapage(imp);
		पूर्ण

		DT_PUTPAGE(mp);
	पूर्ण

	वापस rc;
पूर्ण


/*
 *	dtDeleteUp()
 *
 * function:
 *	मुक्त empty pages as propagating deletion up the tree
 *
 * parameter:
 *
 * वापस:
 */
अटल पूर्णांक dtDeleteUp(tid_t tid, काष्ठा inode *ip,
	   काष्ठा metapage * fmp, dtpage_t * fp, काष्ठा btstack * btstack)
अणु
	पूर्णांक rc = 0;
	काष्ठा metapage *mp;
	dtpage_t *p;
	पूर्णांक index, nextindex;
	पूर्णांक xlen;
	काष्ठा btframe *parent;
	काष्ठा dt_lock *dtlck;
	काष्ठा tlock *tlck;
	काष्ठा lv *lv;
	काष्ठा pxd_lock *pxdlock;
	पूर्णांक i;

	/*
	 *	keep the root leaf page which has become empty
	 */
	अगर (BT_IS_ROOT(fmp)) अणु
		/*
		 * reset the root
		 *
		 * dtInitRoot() acquires txlock on the root
		 */
		dtInitRoot(tid, ip, PARENT(ip));

		DT_PUTPAGE(fmp);

		वापस 0;
	पूर्ण

	/*
	 *	मुक्त the non-root leaf page
	 */
	/*
	 * acquire a transaction lock on the page
	 *
	 * ग_लिखो FREEXTENT|NOREDOPAGE log record
	 * N.B. linelock is overlaid as मुक्तd extent descriptor, and
	 * the buffer page is मुक्तd;
	 */
	tlck = txMaplock(tid, ip, tlckDTREE | tlckFREE);
	pxdlock = (काष्ठा pxd_lock *) & tlck->lock;
	pxdlock->flag = mlckFREEPXD;
	pxdlock->pxd = fp->header.self;
	pxdlock->index = 1;

	/* update sibling poपूर्णांकers */
	अगर ((rc = dtRelink(tid, ip, fp))) अणु
		BT_PUTPAGE(fmp);
		वापस rc;
	पूर्ण

	xlen = lengthPXD(&fp->header.self);

	/* Free quota allocation. */
	dquot_मुक्त_block(ip, xlen);

	/* मुक्त/invalidate its buffer page */
	discard_metapage(fmp);

	/*
	 *	propagate page deletion up the directory tree
	 *
	 * If the delete from the parent page makes it empty,
	 * जारी all the way up the tree.
	 * stop अगर the root page is reached (which is never deleted) or
	 * अगर the entry deletion करोes not empty the page.
	 */
	जबतक ((parent = BT_POP(btstack)) != शून्य) अणु
		/* pin the parent page <sp> */
		DT_GETPAGE(ip, parent->bn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;

		/*
		 * मुक्त the extent of the child page deleted
		 */
		index = parent->index;

		/*
		 * delete the entry क्रम the child page from parent
		 */
		nextindex = p->header.nextindex;

		/*
		 * the parent has the single entry being deleted:
		 *
		 * मुक्त the parent page which has become empty.
		 */
		अगर (nextindex == 1) अणु
			/*
			 * keep the root पूर्णांकernal page which has become empty
			 */
			अगर (p->header.flag & BT_ROOT) अणु
				/*
				 * reset the root
				 *
				 * dtInitRoot() acquires txlock on the root
				 */
				dtInitRoot(tid, ip, PARENT(ip));

				DT_PUTPAGE(mp);

				वापस 0;
			पूर्ण
			/*
			 * मुक्त the parent page
			 */
			अन्यथा अणु
				/*
				 * acquire a transaction lock on the page
				 *
				 * ग_लिखो FREEXTENT|NOREDOPAGE log record
				 */
				tlck =
				    txMaplock(tid, ip,
					      tlckDTREE | tlckFREE);
				pxdlock = (काष्ठा pxd_lock *) & tlck->lock;
				pxdlock->flag = mlckFREEPXD;
				pxdlock->pxd = p->header.self;
				pxdlock->index = 1;

				/* update sibling poपूर्णांकers */
				अगर ((rc = dtRelink(tid, ip, p))) अणु
					DT_PUTPAGE(mp);
					वापस rc;
				पूर्ण

				xlen = lengthPXD(&p->header.self);

				/* Free quota allocation */
				dquot_मुक्त_block(ip, xlen);

				/* मुक्त/invalidate its buffer page */
				discard_metapage(mp);

				/* propagate up */
				जारी;
			पूर्ण
		पूर्ण

		/*
		 * the parent has other entries reमुख्यing:
		 *
		 * delete the router entry from the parent page.
		 */
		BT_MARK_सूचीTY(mp, ip);
		/*
		 * acquire a transaction lock on the page
		 *
		 * action: router entry deletion
		 */
		tlck = txLock(tid, ip, mp, tlckDTREE | tlckENTRY);
		dtlck = (काष्ठा dt_lock *) & tlck->lock;

		/* linelock header */
		अगर (dtlck->index >= dtlck->maxcnt)
			dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
		lv = & dtlck->lv[dtlck->index];
		lv->offset = 0;
		lv->length = 1;
		dtlck->index++;

		/* linelock stbl of non-root leaf page */
		अगर (!(p->header.flag & BT_ROOT)) अणु
			अगर (dtlck->index < dtlck->maxcnt)
				lv++;
			अन्यथा अणु
				dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
				lv = & dtlck->lv[0];
			पूर्ण
			i = index >> L2DTSLOTSIZE;
			lv->offset = p->header.stblindex + i;
			lv->length =
			    ((p->header.nextindex - 1) >> L2DTSLOTSIZE) -
			    i + 1;
			dtlck->index++;
		पूर्ण

		/* मुक्त the router entry */
		dtDeleteEntry(p, index, &dtlck);

		/* reset key of new lefपंचांगost entry of level (क्रम consistency) */
		अगर (index == 0 &&
		    ((p->header.flag & BT_ROOT) || p->header.prev == 0))
			dtTruncateEntry(p, 0, &dtlck);

		/* unpin the parent page */
		DT_PUTPAGE(mp);

		/* निकास propagation up */
		अवरोध;
	पूर्ण

	अगर (!DO_INDEX(ip))
		ip->i_size -= PSIZE;

	वापस 0;
पूर्ण

#अगर_घोषित _NOTYET
/*
 * NAME:	dtRelocate()
 *
 * FUNCTION:	relocate dtpage (पूर्णांकernal or leaf) of directory;
 *		This function is मुख्यly used by defragfs utility.
 */
पूर्णांक dtRelocate(tid_t tid, काष्ठा inode *ip, s64 lmxaddr, pxd_t * opxd,
	       s64 nxaddr)
अणु
	पूर्णांक rc = 0;
	काष्ठा metapage *mp, *pmp, *lmp, *rmp;
	dtpage_t *p, *pp, *rp = 0, *lp= 0;
	s64 bn;
	पूर्णांक index;
	काष्ठा btstack btstack;
	pxd_t *pxd;
	s64 oxaddr, nextbn, prevbn;
	पूर्णांक xlen, xsize;
	काष्ठा tlock *tlck;
	काष्ठा dt_lock *dtlck;
	काष्ठा pxd_lock *pxdlock;
	s8 *stbl;
	काष्ठा lv *lv;

	oxaddr = addressPXD(opxd);
	xlen = lengthPXD(opxd);

	jfs_info("dtRelocate: lmxaddr:%Ld xaddr:%Ld:%Ld xlen:%d",
		   (दीर्घ दीर्घ)lmxaddr, (दीर्घ दीर्घ)oxaddr, (दीर्घ दीर्घ)nxaddr,
		   xlen);

	/*
	 *	1. get the पूर्णांकernal parent dtpage covering
	 *	router entry क्रम the tartget page to be relocated;
	 */
	rc = dtSearchNode(ip, lmxaddr, opxd, &btstack);
	अगर (rc)
		वापस rc;

	/* retrieve search result */
	DT_GETSEARCH(ip, btstack.top, bn, pmp, pp, index);
	jfs_info("dtRelocate: parent router entry validated.");

	/*
	 *	2. relocate the target dtpage
	 */
	/* पढ़ो in the target page from src extent */
	DT_GETPAGE(ip, oxaddr, mp, PSIZE, p, rc);
	अगर (rc) अणु
		/* release the pinned parent page */
		DT_PUTPAGE(pmp);
		वापस rc;
	पूर्ण

	/*
	 * पढ़ो in sibling pages अगर any to update sibling poपूर्णांकers;
	 */
	rmp = शून्य;
	अगर (p->header.next) अणु
		nextbn = le64_to_cpu(p->header.next);
		DT_GETPAGE(ip, nextbn, rmp, PSIZE, rp, rc);
		अगर (rc) अणु
			DT_PUTPAGE(mp);
			DT_PUTPAGE(pmp);
			वापस (rc);
		पूर्ण
	पूर्ण

	lmp = शून्य;
	अगर (p->header.prev) अणु
		prevbn = le64_to_cpu(p->header.prev);
		DT_GETPAGE(ip, prevbn, lmp, PSIZE, lp, rc);
		अगर (rc) अणु
			DT_PUTPAGE(mp);
			DT_PUTPAGE(pmp);
			अगर (rmp)
				DT_PUTPAGE(rmp);
			वापस (rc);
		पूर्ण
	पूर्ण

	/* at this poपूर्णांक, all xtpages to be updated are in memory */

	/*
	 * update sibling poपूर्णांकers of sibling dtpages अगर any;
	 */
	अगर (lmp) अणु
		tlck = txLock(tid, ip, lmp, tlckDTREE | tlckRELINK);
		dtlck = (काष्ठा dt_lock *) & tlck->lock;
		/* linelock header */
		ASSERT(dtlck->index == 0);
		lv = & dtlck->lv[0];
		lv->offset = 0;
		lv->length = 1;
		dtlck->index++;

		lp->header.next = cpu_to_le64(nxaddr);
		DT_PUTPAGE(lmp);
	पूर्ण

	अगर (rmp) अणु
		tlck = txLock(tid, ip, rmp, tlckDTREE | tlckRELINK);
		dtlck = (काष्ठा dt_lock *) & tlck->lock;
		/* linelock header */
		ASSERT(dtlck->index == 0);
		lv = & dtlck->lv[0];
		lv->offset = 0;
		lv->length = 1;
		dtlck->index++;

		rp->header.prev = cpu_to_le64(nxaddr);
		DT_PUTPAGE(rmp);
	पूर्ण

	/*
	 * update the target dtpage to be relocated
	 *
	 * ग_लिखो LOG_REDOPAGE of LOG_NEW type क्रम dst page
	 * क्रम the whole target page (logreकरो() will apply
	 * after image and update bmap क्रम allocation of the
	 * dst extent), and update bmap क्रम allocation of
	 * the dst extent;
	 */
	tlck = txLock(tid, ip, mp, tlckDTREE | tlckNEW);
	dtlck = (काष्ठा dt_lock *) & tlck->lock;
	/* linelock header */
	ASSERT(dtlck->index == 0);
	lv = & dtlck->lv[0];

	/* update the self address in the dtpage header */
	pxd = &p->header.self;
	PXDaddress(pxd, nxaddr);

	/* the dst page is the same as the src page, i.e.,
	 * linelock क्रम afterimage of the whole page;
	 */
	lv->offset = 0;
	lv->length = p->header.maxslot;
	dtlck->index++;

	/* update the buffer extent descriptor of the dtpage */
	xsize = xlen << JFS_SBI(ip->i_sb)->l2bsize;

	/* unpin the relocated page */
	DT_PUTPAGE(mp);
	jfs_info("dtRelocate: target dtpage relocated.");

	/* the moved extent is dtpage, then a LOG_NOREDOPAGE log rec
	 * needs to be written (in logreकरो(), the LOG_NOREDOPAGE log rec
	 * will also क्रमce a bmap update ).
	 */

	/*
	 *	3. acquire maplock क्रम the source extent to be मुक्तd;
	 */
	/* क्रम dtpage relocation, ग_लिखो a LOG_NOREDOPAGE record
	 * क्रम the source dtpage (logreकरो() will init NoReकरोPage
	 * filter and will also update bmap क्रम मुक्त of the source
	 * dtpage), and upadte bmap क्रम मुक्त of the source dtpage;
	 */
	tlck = txMaplock(tid, ip, tlckDTREE | tlckFREE);
	pxdlock = (काष्ठा pxd_lock *) & tlck->lock;
	pxdlock->flag = mlckFREEPXD;
	PXDaddress(&pxdlock->pxd, oxaddr);
	PXDlength(&pxdlock->pxd, xlen);
	pxdlock->index = 1;

	/*
	 *	4. update the parent router entry क्रम relocation;
	 *
	 * acquire tlck क्रम the parent entry covering the target dtpage;
	 * ग_लिखो LOG_REDOPAGE to apply after image only;
	 */
	jfs_info("dtRelocate: update parent router entry.");
	tlck = txLock(tid, ip, pmp, tlckDTREE | tlckENTRY);
	dtlck = (काष्ठा dt_lock *) & tlck->lock;
	lv = & dtlck->lv[dtlck->index];

	/* update the PXD with the new address */
	stbl = DT_GETSTBL(pp);
	pxd = (pxd_t *) & pp->slot[stbl[index]];
	PXDaddress(pxd, nxaddr);
	lv->offset = stbl[index];
	lv->length = 1;
	dtlck->index++;

	/* unpin the parent dtpage */
	DT_PUTPAGE(pmp);

	वापस rc;
पूर्ण

/*
 * NAME:	dtSearchNode()
 *
 * FUNCTION:	Search क्रम an dtpage containing a specअगरied address
 *		This function is मुख्यly used by defragfs utility.
 *
 * NOTE:	Search result on stack, the found page is pinned at निकास.
 *		The result page must be an पूर्णांकernal dtpage.
 *		lmxaddr give the address of the left most page of the
 *		dtree level, in which the required dtpage resides.
 */
अटल पूर्णांक dtSearchNode(काष्ठा inode *ip, s64 lmxaddr, pxd_t * kpxd,
			काष्ठा btstack * btstack)
अणु
	पूर्णांक rc = 0;
	s64 bn;
	काष्ठा metapage *mp;
	dtpage_t *p;
	पूर्णांक psize = 288;	/* initial in-line directory */
	s8 *stbl;
	पूर्णांक i;
	pxd_t *pxd;
	काष्ठा btframe *btsp;

	BT_CLR(btstack);	/* reset stack */

	/*
	 *	descend tree to the level with specअगरied lefपंचांगost page
	 *
	 *  by convention, root bn = 0.
	 */
	क्रम (bn = 0;;) अणु
		/* get/pin the page to search */
		DT_GETPAGE(ip, bn, mp, psize, p, rc);
		अगर (rc)
			वापस rc;

		/* करोes the xaddr of lefपंचांगost page of the levevl
		 * matches levevl search key ?
		 */
		अगर (p->header.flag & BT_ROOT) अणु
			अगर (lmxaddr == 0)
				अवरोध;
		पूर्ण अन्यथा अगर (addressPXD(&p->header.self) == lmxaddr)
			अवरोध;

		/*
		 * descend करोwn to lefपंचांगost child page
		 */
		अगर (p->header.flag & BT_LEAF) अणु
			DT_PUTPAGE(mp);
			वापस -ESTALE;
		पूर्ण

		/* get the lefपंचांगost entry */
		stbl = DT_GETSTBL(p);
		pxd = (pxd_t *) & p->slot[stbl[0]];

		/* get the child page block address */
		bn = addressPXD(pxd);
		psize = lengthPXD(pxd) << JFS_SBI(ip->i_sb)->l2bsize;
		/* unpin the parent page */
		DT_PUTPAGE(mp);
	पूर्ण

	/*
	 *	search each page at the current levevl
	 */
      loop:
	stbl = DT_GETSTBL(p);
	क्रम (i = 0; i < p->header.nextindex; i++) अणु
		pxd = (pxd_t *) & p->slot[stbl[i]];

		/* found the specअगरied router entry */
		अगर (addressPXD(pxd) == addressPXD(kpxd) &&
		    lengthPXD(pxd) == lengthPXD(kpxd)) अणु
			btsp = btstack->top;
			btsp->bn = bn;
			btsp->index = i;
			btsp->mp = mp;

			वापस 0;
		पूर्ण
	पूर्ण

	/* get the right sibling page अगर any */
	अगर (p->header.next)
		bn = le64_to_cpu(p->header.next);
	अन्यथा अणु
		DT_PUTPAGE(mp);
		वापस -ESTALE;
	पूर्ण

	/* unpin current page */
	DT_PUTPAGE(mp);

	/* get the right sibling page */
	DT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
	अगर (rc)
		वापस rc;

	जाओ loop;
पूर्ण
#पूर्ण_अगर /* _NOTYET */

/*
 *	dtRelink()
 *
 * function:
 *	link around a मुक्तd page.
 *
 * parameter:
 *	fp:	page to be मुक्तd
 *
 * वापस:
 */
अटल पूर्णांक dtRelink(tid_t tid, काष्ठा inode *ip, dtpage_t * p)
अणु
	पूर्णांक rc;
	काष्ठा metapage *mp;
	s64 nextbn, prevbn;
	काष्ठा tlock *tlck;
	काष्ठा dt_lock *dtlck;
	काष्ठा lv *lv;

	nextbn = le64_to_cpu(p->header.next);
	prevbn = le64_to_cpu(p->header.prev);

	/* update prev poपूर्णांकer of the next page */
	अगर (nextbn != 0) अणु
		DT_GETPAGE(ip, nextbn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;

		BT_MARK_सूचीTY(mp, ip);
		/*
		 * acquire a transaction lock on the next page
		 *
		 * action: update prev poपूर्णांकer;
		 */
		tlck = txLock(tid, ip, mp, tlckDTREE | tlckRELINK);
		jfs_info("dtRelink nextbn: tlck = 0x%p, ip = 0x%p, mp=0x%p",
			tlck, ip, mp);
		dtlck = (काष्ठा dt_lock *) & tlck->lock;

		/* linelock header */
		अगर (dtlck->index >= dtlck->maxcnt)
			dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
		lv = & dtlck->lv[dtlck->index];
		lv->offset = 0;
		lv->length = 1;
		dtlck->index++;

		p->header.prev = cpu_to_le64(prevbn);
		DT_PUTPAGE(mp);
	पूर्ण

	/* update next poपूर्णांकer of the previous page */
	अगर (prevbn != 0) अणु
		DT_GETPAGE(ip, prevbn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;

		BT_MARK_सूचीTY(mp, ip);
		/*
		 * acquire a transaction lock on the prev page
		 *
		 * action: update next poपूर्णांकer;
		 */
		tlck = txLock(tid, ip, mp, tlckDTREE | tlckRELINK);
		jfs_info("dtRelink prevbn: tlck = 0x%p, ip = 0x%p, mp=0x%p",
			tlck, ip, mp);
		dtlck = (काष्ठा dt_lock *) & tlck->lock;

		/* linelock header */
		अगर (dtlck->index >= dtlck->maxcnt)
			dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
		lv = & dtlck->lv[dtlck->index];
		lv->offset = 0;
		lv->length = 1;
		dtlck->index++;

		p->header.next = cpu_to_le64(nextbn);
		DT_PUTPAGE(mp);
	पूर्ण

	वापस 0;
पूर्ण


/*
 *	dtInitRoot()
 *
 * initialize directory root (अंतरभूत in inode)
 */
व्योम dtInitRoot(tid_t tid, काष्ठा inode *ip, u32 iकरोtकरोt)
अणु
	काष्ठा jfs_inode_info *jfs_ip = JFS_IP(ip);
	dtroot_t *p;
	पूर्णांक fsi;
	काष्ठा dtslot *f;
	काष्ठा tlock *tlck;
	काष्ठा dt_lock *dtlck;
	काष्ठा lv *lv;
	u16 xflag_save;

	/*
	 * If this was previously an non-empty directory, we need to हटाओ
	 * the old directory table.
	 */
	अगर (DO_INDEX(ip)) अणु
		अगर (!jfs_dirtable_अंतरभूत(ip)) अणु
			काष्ठा tblock *tblk = tid_to_tblock(tid);
			/*
			 * We're playing games with the tid's xflag.  If
			 * we're removing a regular file, the file's xtree
			 * is committed with COMMIT_PMAP, but we always
			 * commit the directories xtree with COMMIT_PWMAP.
			 */
			xflag_save = tblk->xflag;
			tblk->xflag = 0;
			/*
			 * xtTruncate isn't guaranteed to fully truncate
			 * the xtree.  The caller needs to check i_size
			 * after committing the transaction to see अगर
			 * additional truncation is needed.  The
			 * COMMIT_Stale flag tells caller that we
			 * initiated the truncation.
			 */
			xtTruncate(tid, ip, 0, COMMIT_PWMAP);
			set_cflag(COMMIT_Stale, ip);

			tblk->xflag = xflag_save;
		पूर्ण अन्यथा
			ip->i_size = 1;

		jfs_ip->next_index = 2;
	पूर्ण अन्यथा
		ip->i_size = IDATASIZE;

	/*
	 * acquire a transaction lock on the root
	 *
	 * action: directory initialization;
	 */
	tlck = txLock(tid, ip, (काष्ठा metapage *) & jfs_ip->bxflag,
		      tlckDTREE | tlckENTRY | tlckBTROOT);
	dtlck = (काष्ठा dt_lock *) & tlck->lock;

	/* linelock root */
	ASSERT(dtlck->index == 0);
	lv = & dtlck->lv[0];
	lv->offset = 0;
	lv->length = DTROOTMAXSLOT;
	dtlck->index++;

	p = &jfs_ip->i_dtroot;

	p->header.flag = DXD_INDEX | BT_ROOT | BT_LEAF;

	p->header.nextindex = 0;

	/* init मुक्तlist */
	fsi = 1;
	f = &p->slot[fsi];

	/* init data area of root */
	क्रम (fsi++; fsi < DTROOTMAXSLOT; f++, fsi++)
		f->next = fsi;
	f->next = -1;

	p->header.मुक्तlist = 1;
	p->header.मुक्तcnt = 8;

	/* init '..' entry */
	p->header.iकरोtकरोt = cpu_to_le32(iकरोtकरोt);

	वापस;
पूर्ण

/*
 *	add_missing_indices()
 *
 * function: Fix dtree page in which one or more entries has an invalid index.
 *	     fsck.jfs should really fix this, but it currently करोes not.
 *	     Called from jfs_सूची_पढ़ो when bad index is detected.
 */
अटल व्योम add_missing_indices(काष्ठा inode *inode, s64 bn)
अणु
	काष्ठा ldtentry *d;
	काष्ठा dt_lock *dtlck;
	पूर्णांक i;
	uपूर्णांक index;
	काष्ठा lv *lv;
	काष्ठा metapage *mp;
	dtpage_t *p;
	पूर्णांक rc;
	s8 *stbl;
	tid_t tid;
	काष्ठा tlock *tlck;

	tid = txBegin(inode->i_sb, 0);

	DT_GETPAGE(inode, bn, mp, PSIZE, p, rc);

	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "DT_GETPAGE failed!\n");
		जाओ end;
	पूर्ण
	BT_MARK_सूचीTY(mp, inode);

	ASSERT(p->header.flag & BT_LEAF);

	tlck = txLock(tid, inode, mp, tlckDTREE | tlckENTRY);
	अगर (BT_IS_ROOT(mp))
		tlck->type |= tlckBTROOT;

	dtlck = (काष्ठा dt_lock *) &tlck->lock;

	stbl = DT_GETSTBL(p);
	क्रम (i = 0; i < p->header.nextindex; i++) अणु
		d = (काष्ठा ldtentry *) &p->slot[stbl[i]];
		index = le32_to_cpu(d->index);
		अगर ((index < 2) || (index >= JFS_IP(inode)->next_index)) अणु
			d->index = cpu_to_le32(add_index(tid, inode, bn, i));
			अगर (dtlck->index >= dtlck->maxcnt)
				dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
			lv = &dtlck->lv[dtlck->index];
			lv->offset = stbl[i];
			lv->length = 1;
			dtlck->index++;
		पूर्ण
	पूर्ण

	DT_PUTPAGE(mp);
	(व्योम) txCommit(tid, 1, &inode, 0);
end:
	txEnd(tid);
पूर्ण

/*
 * Buffer to hold directory entry info जबतक traversing a dtree page
 * beक्रमe being fed to the filldir function
 */
काष्ठा jfs_dirent अणु
	loff_t position;
	पूर्णांक ino;
	u16 name_len;
	अक्षर name[];
पूर्ण;

/*
 * function to determine next variable-sized jfs_dirent in buffer
 */
अटल अंतरभूत काष्ठा jfs_dirent *next_jfs_dirent(काष्ठा jfs_dirent *dirent)
अणु
	वापस (काष्ठा jfs_dirent *)
		((अक्षर *)dirent +
		 ((माप (काष्ठा jfs_dirent) + dirent->name_len + 1 +
		   माप (loff_t) - 1) &
		  ~(माप (loff_t) - 1)));
पूर्ण

/*
 *	jfs_सूची_पढ़ो()
 *
 * function: पढ़ो directory entries sequentially
 *	from the specअगरied entry offset
 *
 * parameter:
 *
 * वापस: offset = (pn, index) of start entry
 *	of next jfs_सूची_पढ़ो()/dtRead()
 */
पूर्णांक jfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *ip = file_inode(file);
	काष्ठा nls_table *codepage = JFS_SBI(ip->i_sb)->nls_tab;
	पूर्णांक rc = 0;
	loff_t dtpos;	/* legacy OS/2 style position */
	काष्ठा dtoffset अणु
		s16 pn;
		s16 index;
		s32 unused;
	पूर्ण *dtoffset = (काष्ठा dtoffset *) &dtpos;
	s64 bn;
	काष्ठा metapage *mp;
	dtpage_t *p;
	पूर्णांक index;
	s8 *stbl;
	काष्ठा btstack btstack;
	पूर्णांक i, next;
	काष्ठा ldtentry *d;
	काष्ठा dtslot *t;
	पूर्णांक d_namleft, len, outlen;
	अचिन्हित दीर्घ dirent_buf;
	अक्षर *name_ptr;
	u32 dir_index;
	पूर्णांक करो_index = 0;
	uपूर्णांक loop_count = 0;
	काष्ठा jfs_dirent *jfs_dirent;
	पूर्णांक jfs_dirents;
	पूर्णांक overflow, fix_page, page_fixed = 0;
	अटल पूर्णांक unique_pos = 2;	/* If we can't fix broken index */

	अगर (ctx->pos == सूचीEND)
		वापस 0;

	अगर (DO_INDEX(ip)) अणु
		/*
		 * persistent index is stored in directory entries.
		 * Special हालs:	 0 = .
		 *			 1 = ..
		 *			-1 = End of directory
		 */
		करो_index = 1;

		dir_index = (u32) ctx->pos;

		/*
		 * NFSv4 reserves cookies 1 and 2 क्रम . and .. so the value
		 * we वापस to the vfs is one greater than the one we use
		 * पूर्णांकernally.
		 */
		अगर (dir_index)
			dir_index--;

		अगर (dir_index > 1) अणु
			काष्ठा dir_table_slot dirtab_slot;

			अगर (dtEmpty(ip) ||
			    (dir_index >= JFS_IP(ip)->next_index)) अणु
				/* Stale position.  Directory has shrunk */
				ctx->pos = सूचीEND;
				वापस 0;
			पूर्ण
		      repeat:
			rc = पढ़ो_index(ip, dir_index, &dirtab_slot);
			अगर (rc) अणु
				ctx->pos = सूचीEND;
				वापस rc;
			पूर्ण
			अगर (dirtab_slot.flag == सूची_INDEX_FREE) अणु
				अगर (loop_count++ > JFS_IP(ip)->next_index) अणु
					jfs_err("jfs_readdir detected infinite loop!");
					ctx->pos = सूचीEND;
					वापस 0;
				पूर्ण
				dir_index = le32_to_cpu(dirtab_slot.addr2);
				अगर (dir_index == -1) अणु
					ctx->pos = सूचीEND;
					वापस 0;
				पूर्ण
				जाओ repeat;
			पूर्ण
			bn = addressDTS(&dirtab_slot);
			index = dirtab_slot.slot;
			DT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
			अगर (rc) अणु
				ctx->pos = सूचीEND;
				वापस 0;
			पूर्ण
			अगर (p->header.flag & BT_INTERNAL) अणु
				jfs_err("jfs_readdir: bad index table");
				DT_PUTPAGE(mp);
				ctx->pos = सूचीEND;
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (dir_index == 0) अणु
				/*
				 * self "."
				 */
				ctx->pos = 1;
				अगर (!dir_emit(ctx, ".", 1, ip->i_ino, DT_सूची))
					वापस 0;
			पूर्ण
			/*
			 * parent ".."
			 */
			ctx->pos = 2;
			अगर (!dir_emit(ctx, "..", 2, PARENT(ip), DT_सूची))
				वापस 0;

			/*
			 * Find first entry of left-most leaf
			 */
			अगर (dtEmpty(ip)) अणु
				ctx->pos = सूचीEND;
				वापस 0;
			पूर्ण

			अगर ((rc = dtReadFirst(ip, &btstack)))
				वापस rc;

			DT_GETSEARCH(ip, btstack.top, bn, mp, p, index);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Legacy fileप्रणाली - OS/2 & Linux JFS < 0.3.6
		 *
		 * pn = 0; index = 1:	First entry "."
		 * pn = 0; index = 2:	Second entry ".."
		 * pn > 0:		Real entries, pn=1 -> lefपंचांगost page
		 * pn = index = -1:	No more entries
		 */
		dtpos = ctx->pos;
		अगर (dtpos < 2) अणु
			/* build "." entry */
			ctx->pos = 1;
			अगर (!dir_emit(ctx, ".", 1, ip->i_ino, DT_सूची))
				वापस 0;
			dtoffset->index = 2;
			ctx->pos = dtpos;
		पूर्ण

		अगर (dtoffset->pn == 0) अणु
			अगर (dtoffset->index == 2) अणु
				/* build ".." entry */
				अगर (!dir_emit(ctx, "..", 2, PARENT(ip), DT_सूची))
					वापस 0;
			पूर्ण अन्यथा अणु
				jfs_err("jfs_readdir called with invalid offset!");
			पूर्ण
			dtoffset->pn = 1;
			dtoffset->index = 0;
			ctx->pos = dtpos;
		पूर्ण

		अगर (dtEmpty(ip)) अणु
			ctx->pos = सूचीEND;
			वापस 0;
		पूर्ण

		अगर ((rc = dtReadNext(ip, &ctx->pos, &btstack))) अणु
			jfs_err("jfs_readdir: unexpected rc = %d from dtReadNext",
				rc);
			ctx->pos = सूचीEND;
			वापस 0;
		पूर्ण
		/* get start leaf page and index */
		DT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

		/* offset beyond directory eof ? */
		अगर (bn < 0) अणु
			ctx->pos = सूचीEND;
			वापस 0;
		पूर्ण
	पूर्ण

	dirent_buf = __get_मुक्त_page(GFP_KERNEL);
	अगर (dirent_buf == 0) अणु
		DT_PUTPAGE(mp);
		jfs_warn("jfs_readdir: __get_free_page failed!");
		ctx->pos = सूचीEND;
		वापस -ENOMEM;
	पूर्ण

	जबतक (1) अणु
		jfs_dirent = (काष्ठा jfs_dirent *) dirent_buf;
		jfs_dirents = 0;
		overflow = fix_page = 0;

		stbl = DT_GETSTBL(p);

		क्रम (i = index; i < p->header.nextindex; i++) अणु
			d = (काष्ठा ldtentry *) & p->slot[stbl[i]];

			अगर (((दीर्घ) jfs_dirent + d->namlen + 1) >
			    (dirent_buf + PAGE_SIZE)) अणु
				/* DBCS codepages could overrun dirent_buf */
				index = i;
				overflow = 1;
				अवरोध;
			पूर्ण

			d_namleft = d->namlen;
			name_ptr = jfs_dirent->name;
			jfs_dirent->ino = le32_to_cpu(d->inumber);

			अगर (करो_index) अणु
				len = min(d_namleft, DTLHDRDATALEN);
				jfs_dirent->position = le32_to_cpu(d->index);
				/*
				 * d->index should always be valid, but it
				 * isn't.  fsck.jfs doesn't create the
				 * directory index क्रम the lost+found
				 * directory.  Rather than let it go,
				 * we can try to fix it.
				 */
				अगर ((jfs_dirent->position < 2) ||
				    (jfs_dirent->position >=
				     JFS_IP(ip)->next_index)) अणु
					अगर (!page_fixed && !isReadOnly(ip)) अणु
						fix_page = 1;
						/*
						 * setting overflow and setting
						 * index to i will cause the
						 * same page to be processed
						 * again starting here
						 */
						overflow = 1;
						index = i;
						अवरोध;
					पूर्ण
					jfs_dirent->position = unique_pos++;
				पूर्ण
				/*
				 * We add 1 to the index because we may
				 * use a value of 2 पूर्णांकernally, and NFSv4
				 * करोesn't like that.
				 */
				jfs_dirent->position++;
			पूर्ण अन्यथा अणु
				jfs_dirent->position = dtpos;
				len = min(d_namleft, DTLHDRDATALEN_LEGACY);
			पूर्ण

			/* copy the name of head/only segment */
			outlen = jfs_strfromUCS_le(name_ptr, d->name, len,
						   codepage);
			jfs_dirent->name_len = outlen;

			/* copy name in the additional segment(s) */
			next = d->next;
			जबतक (next >= 0) अणु
				t = (काष्ठा dtslot *) & p->slot[next];
				name_ptr += outlen;
				d_namleft -= len;
				/* Sanity Check */
				अगर (d_namleft == 0) अणु
					jfs_error(ip->i_sb,
						  "JFS:Dtree error: ino = %ld, bn=%lld, index = %d\n",
						  (दीर्घ)ip->i_ino,
						  (दीर्घ दीर्घ)bn,
						  i);
					जाओ skip_one;
				पूर्ण
				len = min(d_namleft, DTSLOTDATALEN);
				outlen = jfs_strfromUCS_le(name_ptr, t->name,
							   len, codepage);
				jfs_dirent->name_len += outlen;

				next = t->next;
			पूर्ण

			jfs_dirents++;
			jfs_dirent = next_jfs_dirent(jfs_dirent);
skip_one:
			अगर (!करो_index)
				dtoffset->index++;
		पूर्ण

		अगर (!overflow) अणु
			/* Poपूर्णांक to next leaf page */
			अगर (p->header.flag & BT_ROOT)
				bn = 0;
			अन्यथा अणु
				bn = le64_to_cpu(p->header.next);
				index = 0;
				/* update offset (pn:index) क्रम new page */
				अगर (!करो_index) अणु
					dtoffset->pn++;
					dtoffset->index = 0;
				पूर्ण
			पूर्ण
			page_fixed = 0;
		पूर्ण

		/* unpin previous leaf page */
		DT_PUTPAGE(mp);

		jfs_dirent = (काष्ठा jfs_dirent *) dirent_buf;
		जबतक (jfs_dirents--) अणु
			ctx->pos = jfs_dirent->position;
			अगर (!dir_emit(ctx, jfs_dirent->name,
				    jfs_dirent->name_len,
				    jfs_dirent->ino, DT_UNKNOWN))
				जाओ out;
			jfs_dirent = next_jfs_dirent(jfs_dirent);
		पूर्ण

		अगर (fix_page) अणु
			add_missing_indices(ip, bn);
			page_fixed = 1;
		पूर्ण

		अगर (!overflow && (bn == 0)) अणु
			ctx->pos = सूचीEND;
			अवरोध;
		पूर्ण

		DT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
		अगर (rc) अणु
			मुक्त_page(dirent_buf);
			वापस rc;
		पूर्ण
	पूर्ण

      out:
	मुक्त_page(dirent_buf);

	वापस rc;
पूर्ण


/*
 *	dtReadFirst()
 *
 * function: get the lefपंचांगost page of the directory
 */
अटल पूर्णांक dtReadFirst(काष्ठा inode *ip, काष्ठा btstack * btstack)
अणु
	पूर्णांक rc = 0;
	s64 bn;
	पूर्णांक psize = 288;	/* initial in-line directory */
	काष्ठा metapage *mp;
	dtpage_t *p;
	s8 *stbl;
	काष्ठा btframe *btsp;
	pxd_t *xd;

	BT_CLR(btstack);	/* reset stack */

	/*
	 *	descend lefपंचांगost path of the tree
	 *
	 * by convention, root bn = 0.
	 */
	क्रम (bn = 0;;) अणु
		DT_GETPAGE(ip, bn, mp, psize, p, rc);
		अगर (rc)
			वापस rc;

		/*
		 * lefपंचांगost leaf page
		 */
		अगर (p->header.flag & BT_LEAF) अणु
			/* वापस lefपंचांगost entry */
			btsp = btstack->top;
			btsp->bn = bn;
			btsp->index = 0;
			btsp->mp = mp;

			वापस 0;
		पूर्ण

		/*
		 * descend करोwn to lefपंचांगost child page
		 */
		अगर (BT_STACK_FULL(btstack)) अणु
			DT_PUTPAGE(mp);
			jfs_error(ip->i_sb, "btstack overrun\n");
			BT_STACK_DUMP(btstack);
			वापस -EIO;
		पूर्ण
		/* push (bn, index) of the parent page/entry */
		BT_PUSH(btstack, bn, 0);

		/* get the lefपंचांगost entry */
		stbl = DT_GETSTBL(p);
		xd = (pxd_t *) & p->slot[stbl[0]];

		/* get the child page block address */
		bn = addressPXD(xd);
		psize = lengthPXD(xd) << JFS_SBI(ip->i_sb)->l2bsize;

		/* unpin the parent page */
		DT_PUTPAGE(mp);
	पूर्ण
पूर्ण


/*
 *	dtReadNext()
 *
 * function: get the page of the specअगरied offset (pn:index)
 *
 * वापस: अगर (offset > eof), bn = -1;
 *
 * note: अगर index > nextindex of the target leaf page,
 * start with 1st entry of next leaf page;
 */
अटल पूर्णांक dtReadNext(काष्ठा inode *ip, loff_t * offset,
		      काष्ठा btstack * btstack)
अणु
	पूर्णांक rc = 0;
	काष्ठा dtoffset अणु
		s16 pn;
		s16 index;
		s32 unused;
	पूर्ण *dtoffset = (काष्ठा dtoffset *) offset;
	s64 bn;
	काष्ठा metapage *mp;
	dtpage_t *p;
	पूर्णांक index;
	पूर्णांक pn;
	s8 *stbl;
	काष्ठा btframe *btsp, *parent;
	pxd_t *xd;

	/*
	 * get lefपंचांगost leaf page pinned
	 */
	अगर ((rc = dtReadFirst(ip, btstack)))
		वापस rc;

	/* get leaf page */
	DT_GETSEARCH(ip, btstack->top, bn, mp, p, index);

	/* get the start offset (pn:index) */
	pn = dtoffset->pn - 1;	/* Now pn = 0 represents lefपंचांगost leaf */
	index = dtoffset->index;

	/* start at lefपंचांगost page ? */
	अगर (pn == 0) अणु
		/* offset beyond eof ? */
		अगर (index < p->header.nextindex)
			जाओ out;

		अगर (p->header.flag & BT_ROOT) अणु
			bn = -1;
			जाओ out;
		पूर्ण

		/* start with 1st entry of next leaf page */
		dtoffset->pn++;
		dtoffset->index = index = 0;
		जाओ a;
	पूर्ण

	/* start at non-lefपंचांगost page: scan parent pages क्रम large pn */
	अगर (p->header.flag & BT_ROOT) अणु
		bn = -1;
		जाओ out;
	पूर्ण

	/* start after next leaf page ? */
	अगर (pn > 1)
		जाओ b;

	/* get leaf page pn = 1 */
      a:
	bn = le64_to_cpu(p->header.next);

	/* unpin leaf page */
	DT_PUTPAGE(mp);

	/* offset beyond eof ? */
	अगर (bn == 0) अणु
		bn = -1;
		जाओ out;
	पूर्ण

	जाओ c;

	/*
	 * scan last पूर्णांकernal page level to get target leaf page
	 */
      b:
	/* unpin lefपंचांगost leaf page */
	DT_PUTPAGE(mp);

	/* get left most parent page */
	btsp = btstack->top;
	parent = btsp - 1;
	bn = parent->bn;
	DT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
	अगर (rc)
		वापस rc;

	/* scan parent pages at last पूर्णांकernal page level */
	जबतक (pn >= p->header.nextindex) अणु
		pn -= p->header.nextindex;

		/* get next parent page address */
		bn = le64_to_cpu(p->header.next);

		/* unpin current parent page */
		DT_PUTPAGE(mp);

		/* offset beyond eof ? */
		अगर (bn == 0) अणु
			bn = -1;
			जाओ out;
		पूर्ण

		/* get next parent page */
		DT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;

		/* update parent page stack frame */
		parent->bn = bn;
	पूर्ण

	/* get leaf page address */
	stbl = DT_GETSTBL(p);
	xd = (pxd_t *) & p->slot[stbl[pn]];
	bn = addressPXD(xd);

	/* unpin parent page */
	DT_PUTPAGE(mp);

	/*
	 * get target leaf page
	 */
      c:
	DT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
	अगर (rc)
		वापस rc;

	/*
	 * leaf page has been completed:
	 * start with 1st entry of next leaf page
	 */
	अगर (index >= p->header.nextindex) अणु
		bn = le64_to_cpu(p->header.next);

		/* unpin leaf page */
		DT_PUTPAGE(mp);

		/* offset beyond eof ? */
		अगर (bn == 0) अणु
			bn = -1;
			जाओ out;
		पूर्ण

		/* get next leaf page */
		DT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;

		/* start with 1st entry of next leaf page */
		dtoffset->pn++;
		dtoffset->index = 0;
	पूर्ण

      out:
	/* वापस target leaf page pinned */
	btsp = btstack->top;
	btsp->bn = bn;
	btsp->index = dtoffset->index;
	btsp->mp = mp;

	वापस 0;
पूर्ण


/*
 *	dtCompare()
 *
 * function: compare search key with an पूर्णांकernal entry
 *
 * वापस:
 *	< 0 अगर k is < record
 *	= 0 अगर k is = record
 *	> 0 अगर k is > record
 */
अटल पूर्णांक dtCompare(काष्ठा component_name * key,	/* search key */
		     dtpage_t * p,	/* directory page */
		     पूर्णांक si)
अणु				/* entry slot index */
	ब_अक्षर_प्रकार *kname;
	__le16 *name;
	पूर्णांक klen, namlen, len, rc;
	काष्ठा idtentry *ih;
	काष्ठा dtslot *t;

	/*
	 * क्रमce the left-most key on पूर्णांकernal pages, at any level of
	 * the tree, to be less than any search key.
	 * this obviates having to update the lefपंचांगost key on an पूर्णांकernal
	 * page when the user inserts a new key in the tree smaller than
	 * anything that has been stored.
	 *
	 * (? अगर/when dtSearch() narrows करोwn to 1st entry (index = 0),
	 * at any पूर्णांकernal page at any level of the tree,
	 * it descends to child of the entry anyway -
	 * ? make the entry as min size dummy entry)
	 *
	 * अगर (e->index == 0 && h->prevpg == P_INVALID && !(h->flags & BT_LEAF))
	 * वापस (1);
	 */

	kname = key->name;
	klen = key->namlen;

	ih = (काष्ठा idtentry *) & p->slot[si];
	si = ih->next;
	name = ih->name;
	namlen = ih->namlen;
	len = min(namlen, DTIHDRDATALEN);

	/* compare with head/only segment */
	len = min(klen, len);
	अगर ((rc = UniStrncmp_le(kname, name, len)))
		वापस rc;

	klen -= len;
	namlen -= len;

	/* compare with additional segment(s) */
	kname += len;
	जबतक (klen > 0 && namlen > 0) अणु
		/* compare with next name segment */
		t = (काष्ठा dtslot *) & p->slot[si];
		len = min(namlen, DTSLOTDATALEN);
		len = min(klen, len);
		name = t->name;
		अगर ((rc = UniStrncmp_le(kname, name, len)))
			वापस rc;

		klen -= len;
		namlen -= len;
		kname += len;
		si = t->next;
	पूर्ण

	वापस (klen - namlen);
पूर्ण




/*
 *	ciCompare()
 *
 * function: compare search key with an (leaf/पूर्णांकernal) entry
 *
 * वापस:
 *	< 0 अगर k is < record
 *	= 0 अगर k is = record
 *	> 0 अगर k is > record
 */
अटल पूर्णांक ciCompare(काष्ठा component_name * key,	/* search key */
		     dtpage_t * p,	/* directory page */
		     पूर्णांक si,	/* entry slot index */
		     पूर्णांक flag)
अणु
	ब_अक्षर_प्रकार *kname, x;
	__le16 *name;
	पूर्णांक klen, namlen, len, rc;
	काष्ठा ldtentry *lh;
	काष्ठा idtentry *ih;
	काष्ठा dtslot *t;
	पूर्णांक i;

	/*
	 * क्रमce the left-most key on पूर्णांकernal pages, at any level of
	 * the tree, to be less than any search key.
	 * this obviates having to update the lefपंचांगost key on an पूर्णांकernal
	 * page when the user inserts a new key in the tree smaller than
	 * anything that has been stored.
	 *
	 * (? अगर/when dtSearch() narrows करोwn to 1st entry (index = 0),
	 * at any पूर्णांकernal page at any level of the tree,
	 * it descends to child of the entry anyway -
	 * ? make the entry as min size dummy entry)
	 *
	 * अगर (e->index == 0 && h->prevpg == P_INVALID && !(h->flags & BT_LEAF))
	 * वापस (1);
	 */

	kname = key->name;
	klen = key->namlen;

	/*
	 * leaf page entry
	 */
	अगर (p->header.flag & BT_LEAF) अणु
		lh = (काष्ठा ldtentry *) & p->slot[si];
		si = lh->next;
		name = lh->name;
		namlen = lh->namlen;
		अगर (flag & JFS_सूची_INDEX)
			len = min(namlen, DTLHDRDATALEN);
		अन्यथा
			len = min(namlen, DTLHDRDATALEN_LEGACY);
	पूर्ण
	/*
	 * पूर्णांकernal page entry
	 */
	अन्यथा अणु
		ih = (काष्ठा idtentry *) & p->slot[si];
		si = ih->next;
		name = ih->name;
		namlen = ih->namlen;
		len = min(namlen, DTIHDRDATALEN);
	पूर्ण

	/* compare with head/only segment */
	len = min(klen, len);
	क्रम (i = 0; i < len; i++, kname++, name++) अणु
		/* only upperहाल अगर हाल-insensitive support is on */
		अगर ((flag & JFS_OS2) == JFS_OS2)
			x = UniToupper(le16_to_cpu(*name));
		अन्यथा
			x = le16_to_cpu(*name);
		अगर ((rc = *kname - x))
			वापस rc;
	पूर्ण

	klen -= len;
	namlen -= len;

	/* compare with additional segment(s) */
	जबतक (klen > 0 && namlen > 0) अणु
		/* compare with next name segment */
		t = (काष्ठा dtslot *) & p->slot[si];
		len = min(namlen, DTSLOTDATALEN);
		len = min(klen, len);
		name = t->name;
		क्रम (i = 0; i < len; i++, kname++, name++) अणु
			/* only upperहाल अगर हाल-insensitive support is on */
			अगर ((flag & JFS_OS2) == JFS_OS2)
				x = UniToupper(le16_to_cpu(*name));
			अन्यथा
				x = le16_to_cpu(*name);

			अगर ((rc = *kname - x))
				वापस rc;
		पूर्ण

		klen -= len;
		namlen -= len;
		si = t->next;
	पूर्ण

	वापस (klen - namlen);
पूर्ण


/*
 *	ciGetLeafPrefixKey()
 *
 * function: compute prefix of suffix compression
 *	     from two adjacent leaf entries
 *	     across page boundary
 *
 * वापस: non-zero on error
 *
 */
अटल पूर्णांक ciGetLeafPrefixKey(dtpage_t * lp, पूर्णांक li, dtpage_t * rp,
			       पूर्णांक ri, काष्ठा component_name * key, पूर्णांक flag)
अणु
	पूर्णांक klen, namlen;
	ब_अक्षर_प्रकार *pl, *pr, *kname;
	काष्ठा component_name lkey;
	काष्ठा component_name rkey;

	lkey.name = kदो_स्मृति_array(JFS_NAME_MAX + 1, माप(ब_अक्षर_प्रकार),
					GFP_KERNEL);
	अगर (lkey.name == शून्य)
		वापस -ENOMEM;

	rkey.name = kदो_स्मृति_array(JFS_NAME_MAX + 1, माप(ब_अक्षर_प्रकार),
					GFP_KERNEL);
	अगर (rkey.name == शून्य) अणु
		kमुक्त(lkey.name);
		वापस -ENOMEM;
	पूर्ण

	/* get left and right key */
	dtGetKey(lp, li, &lkey, flag);
	lkey.name[lkey.namlen] = 0;

	अगर ((flag & JFS_OS2) == JFS_OS2)
		ciToUpper(&lkey);

	dtGetKey(rp, ri, &rkey, flag);
	rkey.name[rkey.namlen] = 0;


	अगर ((flag & JFS_OS2) == JFS_OS2)
		ciToUpper(&rkey);

	/* compute prefix */
	klen = 0;
	kname = key->name;
	namlen = min(lkey.namlen, rkey.namlen);
	क्रम (pl = lkey.name, pr = rkey.name;
	     namlen; pl++, pr++, namlen--, klen++, kname++) अणु
		*kname = *pr;
		अगर (*pl != *pr) अणु
			key->namlen = klen + 1;
			जाओ मुक्त_names;
		पूर्ण
	पूर्ण

	/* l->namlen <= r->namlen since l <= r */
	अगर (lkey.namlen < rkey.namlen) अणु
		*kname = *pr;
		key->namlen = klen + 1;
	पूर्ण अन्यथा			/* l->namelen == r->namelen */
		key->namlen = klen;

मुक्त_names:
	kमुक्त(lkey.name);
	kमुक्त(rkey.name);
	वापस 0;
पूर्ण



/*
 *	dtGetKey()
 *
 * function: get key of the entry
 */
अटल व्योम dtGetKey(dtpage_t * p, पूर्णांक i,	/* entry index */
		     काष्ठा component_name * key, पूर्णांक flag)
अणु
	पूर्णांक si;
	s8 *stbl;
	काष्ठा ldtentry *lh;
	काष्ठा idtentry *ih;
	काष्ठा dtslot *t;
	पूर्णांक namlen, len;
	ब_अक्षर_प्रकार *kname;
	__le16 *name;

	/* get entry */
	stbl = DT_GETSTBL(p);
	si = stbl[i];
	अगर (p->header.flag & BT_LEAF) अणु
		lh = (काष्ठा ldtentry *) & p->slot[si];
		si = lh->next;
		namlen = lh->namlen;
		name = lh->name;
		अगर (flag & JFS_सूची_INDEX)
			len = min(namlen, DTLHDRDATALEN);
		अन्यथा
			len = min(namlen, DTLHDRDATALEN_LEGACY);
	पूर्ण अन्यथा अणु
		ih = (काष्ठा idtentry *) & p->slot[si];
		si = ih->next;
		namlen = ih->namlen;
		name = ih->name;
		len = min(namlen, DTIHDRDATALEN);
	पूर्ण

	key->namlen = namlen;
	kname = key->name;

	/*
	 * move head/only segment
	 */
	UniStrncpy_from_le(kname, name, len);

	/*
	 * move additional segment(s)
	 */
	जबतक (si >= 0) अणु
		/* get next segment */
		t = &p->slot[si];
		kname += len;
		namlen -= len;
		len = min(namlen, DTSLOTDATALEN);
		UniStrncpy_from_le(kname, t->name, len);

		si = t->next;
	पूर्ण
पूर्ण


/*
 *	dtInsertEntry()
 *
 * function: allocate मुक्त slot(s) and
 *	     ग_लिखो a leaf/पूर्णांकernal entry
 *
 * वापस: entry slot index
 */
अटल व्योम dtInsertEntry(dtpage_t * p, पूर्णांक index, काष्ठा component_name * key,
			  ddata_t * data, काष्ठा dt_lock ** dtlock)
अणु
	काष्ठा dtslot *h, *t;
	काष्ठा ldtentry *lh = शून्य;
	काष्ठा idtentry *ih = शून्य;
	पूर्णांक hsi, fsi, klen, len, nextindex;
	ब_अक्षर_प्रकार *kname;
	__le16 *name;
	s8 *stbl;
	pxd_t *xd;
	काष्ठा dt_lock *dtlck = *dtlock;
	काष्ठा lv *lv;
	पूर्णांक xsi, n;
	s64 bn = 0;
	काष्ठा metapage *mp = शून्य;

	klen = key->namlen;
	kname = key->name;

	/* allocate a मुक्त slot */
	hsi = fsi = p->header.मुक्तlist;
	h = &p->slot[fsi];
	p->header.मुक्तlist = h->next;
	--p->header.मुक्तcnt;

	/* खोलो new linelock */
	अगर (dtlck->index >= dtlck->maxcnt)
		dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);

	lv = & dtlck->lv[dtlck->index];
	lv->offset = hsi;

	/* ग_लिखो head/only segment */
	अगर (p->header.flag & BT_LEAF) अणु
		lh = (काष्ठा ldtentry *) h;
		lh->next = h->next;
		lh->inumber = cpu_to_le32(data->leaf.ino);
		lh->namlen = klen;
		name = lh->name;
		अगर (data->leaf.ip) अणु
			len = min(klen, DTLHDRDATALEN);
			अगर (!(p->header.flag & BT_ROOT))
				bn = addressPXD(&p->header.self);
			lh->index = cpu_to_le32(add_index(data->leaf.tid,
							  data->leaf.ip,
							  bn, index));
		पूर्ण अन्यथा
			len = min(klen, DTLHDRDATALEN_LEGACY);
	पूर्ण अन्यथा अणु
		ih = (काष्ठा idtentry *) h;
		ih->next = h->next;
		xd = (pxd_t *) ih;
		*xd = data->xd;
		ih->namlen = klen;
		name = ih->name;
		len = min(klen, DTIHDRDATALEN);
	पूर्ण

	UniStrncpy_to_le(name, kname, len);

	n = 1;
	xsi = hsi;

	/* ग_लिखो additional segment(s) */
	t = h;
	klen -= len;
	जबतक (klen) अणु
		/* get मुक्त slot */
		fsi = p->header.मुक्तlist;
		t = &p->slot[fsi];
		p->header.मुक्तlist = t->next;
		--p->header.मुक्तcnt;

		/* is next slot contiguous ? */
		अगर (fsi != xsi + 1) अणु
			/* बंद current linelock */
			lv->length = n;
			dtlck->index++;

			/* खोलो new linelock */
			अगर (dtlck->index < dtlck->maxcnt)
				lv++;
			अन्यथा अणु
				dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
				lv = & dtlck->lv[0];
			पूर्ण

			lv->offset = fsi;
			n = 0;
		पूर्ण

		kname += len;
		len = min(klen, DTSLOTDATALEN);
		UniStrncpy_to_le(t->name, kname, len);

		n++;
		xsi = fsi;
		klen -= len;
	पूर्ण

	/* बंद current linelock */
	lv->length = n;
	dtlck->index++;

	*dtlock = dtlck;

	/* terminate last/only segment */
	अगर (h == t) अणु
		/* single segment entry */
		अगर (p->header.flag & BT_LEAF)
			lh->next = -1;
		अन्यथा
			ih->next = -1;
	पूर्ण अन्यथा
		/* multi-segment entry */
		t->next = -1;

	/* अगर insert पूर्णांकo middle, shअगरt right succeeding entries in stbl */
	stbl = DT_GETSTBL(p);
	nextindex = p->header.nextindex;
	अगर (index < nextindex) अणु
		स_हटाओ(stbl + index + 1, stbl + index, nextindex - index);

		अगर ((p->header.flag & BT_LEAF) && data->leaf.ip) अणु
			s64 lblock;

			/*
			 * Need to update slot number क्रम entries that moved
			 * in the stbl
			 */
			mp = शून्य;
			क्रम (n = index + 1; n <= nextindex; n++) अणु
				lh = (काष्ठा ldtentry *) & (p->slot[stbl[n]]);
				modअगरy_index(data->leaf.tid, data->leaf.ip,
					     le32_to_cpu(lh->index), bn, n,
					     &mp, &lblock);
			पूर्ण
			अगर (mp)
				release_metapage(mp);
		पूर्ण
	पूर्ण

	stbl[index] = hsi;

	/* advance next available entry index of stbl */
	++p->header.nextindex;
पूर्ण


/*
 *	dtMoveEntry()
 *
 * function: move entries from split/left page to new/right page
 *
 *	nextindex of dst page and मुक्तlist/मुक्तcnt of both pages
 *	are updated.
 */
अटल व्योम dtMoveEntry(dtpage_t * sp, पूर्णांक si, dtpage_t * dp,
			काष्ठा dt_lock ** sdtlock, काष्ठा dt_lock ** ddtlock,
			पूर्णांक करो_index)
अणु
	पूर्णांक ssi, next;		/* src slot index */
	पूर्णांक di;			/* dst entry index */
	पूर्णांक dsi;		/* dst slot index */
	s8 *sstbl, *dstbl;	/* sorted entry table */
	पूर्णांक snamlen, len;
	काष्ठा ldtentry *slh, *dlh = शून्य;
	काष्ठा idtentry *sih, *dih = शून्य;
	काष्ठा dtslot *h, *s, *d;
	काष्ठा dt_lock *sdtlck = *sdtlock, *ddtlck = *ddtlock;
	काष्ठा lv *slv, *dlv;
	पूर्णांक xssi, ns, nd;
	पूर्णांक sfsi;

	sstbl = (s8 *) & sp->slot[sp->header.stblindex];
	dstbl = (s8 *) & dp->slot[dp->header.stblindex];

	dsi = dp->header.मुक्तlist;	/* first (whole page) मुक्त slot */
	sfsi = sp->header.मुक्तlist;

	/* linelock destination entry slot */
	dlv = & ddtlck->lv[ddtlck->index];
	dlv->offset = dsi;

	/* linelock source entry slot */
	slv = & sdtlck->lv[sdtlck->index];
	slv->offset = sstbl[si];
	xssi = slv->offset - 1;

	/*
	 * move entries
	 */
	ns = nd = 0;
	क्रम (di = 0; si < sp->header.nextindex; si++, di++) अणु
		ssi = sstbl[si];
		dstbl[di] = dsi;

		/* is next slot contiguous ? */
		अगर (ssi != xssi + 1) अणु
			/* बंद current linelock */
			slv->length = ns;
			sdtlck->index++;

			/* खोलो new linelock */
			अगर (sdtlck->index < sdtlck->maxcnt)
				slv++;
			अन्यथा अणु
				sdtlck = (काष्ठा dt_lock *) txLinelock(sdtlck);
				slv = & sdtlck->lv[0];
			पूर्ण

			slv->offset = ssi;
			ns = 0;
		पूर्ण

		/*
		 * move head/only segment of an entry
		 */
		/* get dst slot */
		h = d = &dp->slot[dsi];

		/* get src slot and move */
		s = &sp->slot[ssi];
		अगर (sp->header.flag & BT_LEAF) अणु
			/* get source entry */
			slh = (काष्ठा ldtentry *) s;
			dlh = (काष्ठा ldtentry *) h;
			snamlen = slh->namlen;

			अगर (करो_index) अणु
				len = min(snamlen, DTLHDRDATALEN);
				dlh->index = slh->index; /* little-endian */
			पूर्ण अन्यथा
				len = min(snamlen, DTLHDRDATALEN_LEGACY);

			स_नकल(dlh, slh, 6 + len * 2);

			next = slh->next;

			/* update dst head/only segment next field */
			dsi++;
			dlh->next = dsi;
		पूर्ण अन्यथा अणु
			sih = (काष्ठा idtentry *) s;
			snamlen = sih->namlen;

			len = min(snamlen, DTIHDRDATALEN);
			dih = (काष्ठा idtentry *) h;
			स_नकल(dih, sih, 10 + len * 2);
			next = sih->next;

			dsi++;
			dih->next = dsi;
		पूर्ण

		/* मुक्त src head/only segment */
		s->next = sfsi;
		s->cnt = 1;
		sfsi = ssi;

		ns++;
		nd++;
		xssi = ssi;

		/*
		 * move additional segment(s) of the entry
		 */
		snamlen -= len;
		जबतक ((ssi = next) >= 0) अणु
			/* is next slot contiguous ? */
			अगर (ssi != xssi + 1) अणु
				/* बंद current linelock */
				slv->length = ns;
				sdtlck->index++;

				/* खोलो new linelock */
				अगर (sdtlck->index < sdtlck->maxcnt)
					slv++;
				अन्यथा अणु
					sdtlck =
					    (काष्ठा dt_lock *)
					    txLinelock(sdtlck);
					slv = & sdtlck->lv[0];
				पूर्ण

				slv->offset = ssi;
				ns = 0;
			पूर्ण

			/* get next source segment */
			s = &sp->slot[ssi];

			/* get next destination मुक्त slot */
			d++;

			len = min(snamlen, DTSLOTDATALEN);
			UniStrncpy_le(d->name, s->name, len);

			ns++;
			nd++;
			xssi = ssi;

			dsi++;
			d->next = dsi;

			/* मुक्त source segment */
			next = s->next;
			s->next = sfsi;
			s->cnt = 1;
			sfsi = ssi;

			snamlen -= len;
		पूर्ण		/* end जबतक */

		/* terminate dst last/only segment */
		अगर (h == d) अणु
			/* single segment entry */
			अगर (dp->header.flag & BT_LEAF)
				dlh->next = -1;
			अन्यथा
				dih->next = -1;
		पूर्ण अन्यथा
			/* multi-segment entry */
			d->next = -1;
	पूर्ण			/* end क्रम */

	/* बंद current linelock */
	slv->length = ns;
	sdtlck->index++;
	*sdtlock = sdtlck;

	dlv->length = nd;
	ddtlck->index++;
	*ddtlock = ddtlck;

	/* update source header */
	sp->header.मुक्तlist = sfsi;
	sp->header.मुक्तcnt += nd;

	/* update destination header */
	dp->header.nextindex = di;

	dp->header.मुक्तlist = dsi;
	dp->header.मुक्तcnt -= nd;
पूर्ण


/*
 *	dtDeleteEntry()
 *
 * function: मुक्त a (leaf/पूर्णांकernal) entry
 *
 * log मुक्तlist header, stbl, and each segment slot of entry
 * (even though last/only segment next field is modअगरied,
 * physical image logging requires all segment slots of
 * the entry logged to aव्योम applying previous updates
 * to the same slots)
 */
अटल व्योम dtDeleteEntry(dtpage_t * p, पूर्णांक fi, काष्ठा dt_lock ** dtlock)
अणु
	पूर्णांक fsi;		/* मुक्त entry slot index */
	s8 *stbl;
	काष्ठा dtslot *t;
	पूर्णांक si, मुक्तcnt;
	काष्ठा dt_lock *dtlck = *dtlock;
	काष्ठा lv *lv;
	पूर्णांक xsi, n;

	/* get मुक्त entry slot index */
	stbl = DT_GETSTBL(p);
	fsi = stbl[fi];

	/* खोलो new linelock */
	अगर (dtlck->index >= dtlck->maxcnt)
		dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
	lv = & dtlck->lv[dtlck->index];

	lv->offset = fsi;

	/* get the head/only segment */
	t = &p->slot[fsi];
	अगर (p->header.flag & BT_LEAF)
		si = ((काष्ठा ldtentry *) t)->next;
	अन्यथा
		si = ((काष्ठा idtentry *) t)->next;
	t->next = si;
	t->cnt = 1;

	n = मुक्तcnt = 1;
	xsi = fsi;

	/* find the last/only segment */
	जबतक (si >= 0) अणु
		/* is next slot contiguous ? */
		अगर (si != xsi + 1) अणु
			/* बंद current linelock */
			lv->length = n;
			dtlck->index++;

			/* खोलो new linelock */
			अगर (dtlck->index < dtlck->maxcnt)
				lv++;
			अन्यथा अणु
				dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
				lv = & dtlck->lv[0];
			पूर्ण

			lv->offset = si;
			n = 0;
		पूर्ण

		n++;
		xsi = si;
		मुक्तcnt++;

		t = &p->slot[si];
		t->cnt = 1;
		si = t->next;
	पूर्ण

	/* बंद current linelock */
	lv->length = n;
	dtlck->index++;

	*dtlock = dtlck;

	/* update मुक्तlist */
	t->next = p->header.मुक्तlist;
	p->header.मुक्तlist = fsi;
	p->header.मुक्तcnt += मुक्तcnt;

	/* अगर delete from middle,
	 * shअगरt left the succedding entries in the stbl
	 */
	si = p->header.nextindex;
	अगर (fi < si - 1)
		स_हटाओ(&stbl[fi], &stbl[fi + 1], si - fi - 1);

	p->header.nextindex--;
पूर्ण


/*
 *	dtTruncateEntry()
 *
 * function: truncate a (leaf/पूर्णांकernal) entry
 *
 * log मुक्तlist header, stbl, and each segment slot of entry
 * (even though last/only segment next field is modअगरied,
 * physical image logging requires all segment slots of
 * the entry logged to aव्योम applying previous updates
 * to the same slots)
 */
अटल व्योम dtTruncateEntry(dtpage_t * p, पूर्णांक ti, काष्ठा dt_lock ** dtlock)
अणु
	पूर्णांक tsi;		/* truncate entry slot index */
	s8 *stbl;
	काष्ठा dtslot *t;
	पूर्णांक si, मुक्तcnt;
	काष्ठा dt_lock *dtlck = *dtlock;
	काष्ठा lv *lv;
	पूर्णांक fsi, xsi, n;

	/* get मुक्त entry slot index */
	stbl = DT_GETSTBL(p);
	tsi = stbl[ti];

	/* खोलो new linelock */
	अगर (dtlck->index >= dtlck->maxcnt)
		dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
	lv = & dtlck->lv[dtlck->index];

	lv->offset = tsi;

	/* get the head/only segment */
	t = &p->slot[tsi];
	ASSERT(p->header.flag & BT_INTERNAL);
	((काष्ठा idtentry *) t)->namlen = 0;
	si = ((काष्ठा idtentry *) t)->next;
	((काष्ठा idtentry *) t)->next = -1;

	n = 1;
	मुक्तcnt = 0;
	fsi = si;
	xsi = tsi;

	/* find the last/only segment */
	जबतक (si >= 0) अणु
		/* is next slot contiguous ? */
		अगर (si != xsi + 1) अणु
			/* बंद current linelock */
			lv->length = n;
			dtlck->index++;

			/* खोलो new linelock */
			अगर (dtlck->index < dtlck->maxcnt)
				lv++;
			अन्यथा अणु
				dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
				lv = & dtlck->lv[0];
			पूर्ण

			lv->offset = si;
			n = 0;
		पूर्ण

		n++;
		xsi = si;
		मुक्तcnt++;

		t = &p->slot[si];
		t->cnt = 1;
		si = t->next;
	पूर्ण

	/* बंद current linelock */
	lv->length = n;
	dtlck->index++;

	*dtlock = dtlck;

	/* update मुक्तlist */
	अगर (मुक्तcnt == 0)
		वापस;
	t->next = p->header.मुक्तlist;
	p->header.मुक्तlist = fsi;
	p->header.मुक्तcnt += मुक्तcnt;
पूर्ण


/*
 *	dtLinelockFreelist()
 */
अटल व्योम dtLinelockFreelist(dtpage_t * p,	/* directory page */
			       पूर्णांक m,	/* max slot index */
			       काष्ठा dt_lock ** dtlock)
अणु
	पूर्णांक fsi;		/* मुक्त entry slot index */
	काष्ठा dtslot *t;
	पूर्णांक si;
	काष्ठा dt_lock *dtlck = *dtlock;
	काष्ठा lv *lv;
	पूर्णांक xsi, n;

	/* get मुक्त entry slot index */
	fsi = p->header.मुक्तlist;

	/* खोलो new linelock */
	अगर (dtlck->index >= dtlck->maxcnt)
		dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
	lv = & dtlck->lv[dtlck->index];

	lv->offset = fsi;

	n = 1;
	xsi = fsi;

	t = &p->slot[fsi];
	si = t->next;

	/* find the last/only segment */
	जबतक (si < m && si >= 0) अणु
		/* is next slot contiguous ? */
		अगर (si != xsi + 1) अणु
			/* बंद current linelock */
			lv->length = n;
			dtlck->index++;

			/* खोलो new linelock */
			अगर (dtlck->index < dtlck->maxcnt)
				lv++;
			अन्यथा अणु
				dtlck = (काष्ठा dt_lock *) txLinelock(dtlck);
				lv = & dtlck->lv[0];
			पूर्ण

			lv->offset = si;
			n = 0;
		पूर्ण

		n++;
		xsi = si;

		t = &p->slot[si];
		si = t->next;
	पूर्ण

	/* बंद current linelock */
	lv->length = n;
	dtlck->index++;

	*dtlock = dtlck;
पूर्ण


/*
 * NAME: dtModअगरy
 *
 * FUNCTION: Modअगरy the inode number part of a directory entry
 *
 * PARAMETERS:
 *	tid	- Transaction id
 *	ip	- Inode of parent directory
 *	key	- Name of entry to be modअगरied
 *	orig_ino	- Original inode number expected in entry
 *	new_ino	- New inode number to put पूर्णांकo entry
 *	flag	- JFS_RENAME
 *
 * RETURNS:
 *	-ESTALE	- If entry found करोes not match orig_ino passed in
 *	-ENOENT	- If no entry can be found to match key
 *	0	- If successfully modअगरied entry
 */
पूर्णांक dtModअगरy(tid_t tid, काष्ठा inode *ip,
	 काष्ठा component_name * key, ino_t * orig_ino, ino_t new_ino, पूर्णांक flag)
अणु
	पूर्णांक rc;
	s64 bn;
	काष्ठा metapage *mp;
	dtpage_t *p;
	पूर्णांक index;
	काष्ठा btstack btstack;
	काष्ठा tlock *tlck;
	काष्ठा dt_lock *dtlck;
	काष्ठा lv *lv;
	s8 *stbl;
	पूर्णांक entry_si;		/* entry slot index */
	काष्ठा ldtentry *entry;

	/*
	 *	search क्रम the entry to modअगरy:
	 *
	 * dtSearch() वापसs (leaf page pinned, index at which to modअगरy).
	 */
	अगर ((rc = dtSearch(ip, key, orig_ino, &btstack, flag)))
		वापस rc;

	/* retrieve search result */
	DT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

	BT_MARK_सूचीTY(mp, ip);
	/*
	 * acquire a transaction lock on the leaf page of named entry
	 */
	tlck = txLock(tid, ip, mp, tlckDTREE | tlckENTRY);
	dtlck = (काष्ठा dt_lock *) & tlck->lock;

	/* get slot index of the entry */
	stbl = DT_GETSTBL(p);
	entry_si = stbl[index];

	/* linelock entry */
	ASSERT(dtlck->index == 0);
	lv = & dtlck->lv[0];
	lv->offset = entry_si;
	lv->length = 1;
	dtlck->index++;

	/* get the head/only segment */
	entry = (काष्ठा ldtentry *) & p->slot[entry_si];

	/* substitute the inode number of the entry */
	entry->inumber = cpu_to_le32(new_ino);

	/* unpin the leaf page */
	DT_PUTPAGE(mp);

	वापस 0;
पूर्ण
