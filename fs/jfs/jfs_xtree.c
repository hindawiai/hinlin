<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2005
 */
/*
 *	jfs_xtree.c: extent allocation descriptor B+-tree manager
 */

#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/seq_file.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_dinode.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_debug.h"

/*
 * xtree local flag
 */
#घोषणा XT_INSERT	0x00000001

/*
 *	xtree key/entry comparison: extent offset
 *
 * वापस:
 *	-1: k < start of extent
 *	 0: start_of_extent <= k <= end_of_extent
 *	 1: k > end_of_extent
 */
#घोषणा XT_CMP(CMP, K, X, OFFSET64)\
अणु\
	OFFSET64 = offsetXAD(X);\
	(CMP) = ((K) >= OFFSET64 + lengthXAD(X)) ? 1 :\
		((K) < OFFSET64) ? -1 : 0;\
पूर्ण

/* ग_लिखो a xad entry */
#घोषणा XT_PUTENTRY(XAD, FLAG, OFF, LEN, ADDR)\
अणु\
	(XAD)->flag = (FLAG);\
	XADoffset((XAD), (OFF));\
	XADlength((XAD), (LEN));\
	XADaddress((XAD), (ADDR));\
पूर्ण

#घोषणा XT_PAGE(IP, MP) BT_PAGE(IP, MP, xtpage_t, i_xtroot)

/* get page buffer क्रम specअगरied block address */
/* ToDo: Replace this ugly macro with a function */
#घोषणा XT_GETPAGE(IP, BN, MP, SIZE, P, RC)				\
करो अणु									\
	BT_GETPAGE(IP, BN, MP, xtpage_t, SIZE, P, RC, i_xtroot);	\
	अगर (!(RC)) अणु							\
		अगर ((le16_to_cpu((P)->header.nextindex) < XTENTRYSTART) || \
		    (le16_to_cpu((P)->header.nextindex) >		\
		     le16_to_cpu((P)->header.maxentry)) ||		\
		    (le16_to_cpu((P)->header.maxentry) >		\
		     (((BN) == 0) ? XTROOTMAXSLOT : PSIZE >> L2XTSLOTSIZE))) अणु \
			jfs_error((IP)->i_sb,				\
				  "XT_GETPAGE: xtree page corrupt\n");	\
			BT_PUTPAGE(MP);					\
			MP = शून्य;					\
			RC = -EIO;					\
		पूर्ण							\
	पूर्ण								\
पूर्ण जबतक (0)

/* क्रम consistency */
#घोषणा XT_PUTPAGE(MP) BT_PUTPAGE(MP)

#घोषणा XT_GETSEARCH(IP, LEAF, BN, MP, P, INDEX) \
	BT_GETSEARCH(IP, LEAF, BN, MP, xtpage_t, P, INDEX, i_xtroot)
/* xtree entry parameter descriptor */
काष्ठा xtsplit अणु
	काष्ठा metapage *mp;
	s16 index;
	u8 flag;
	s64 off;
	s64 addr;
	पूर्णांक len;
	काष्ठा pxdlist *pxdlist;
पूर्ण;


/*
 *	statistics
 */
#अगर_घोषित CONFIG_JFS_STATISTICS
अटल काष्ठा अणु
	uपूर्णांक search;
	uपूर्णांक fastSearch;
	uपूर्णांक split;
पूर्ण xtStat;
#पूर्ण_अगर


/*
 * क्रमward references
 */
अटल पूर्णांक xtSearch(काष्ठा inode *ip, s64 xoff, s64 *next, पूर्णांक *cmpp,
		    काष्ठा btstack * btstack, पूर्णांक flag);

अटल पूर्णांक xtSplitUp(tid_t tid,
		     काष्ठा inode *ip,
		     काष्ठा xtsplit * split, काष्ठा btstack * btstack);

अटल पूर्णांक xtSplitPage(tid_t tid, काष्ठा inode *ip, काष्ठा xtsplit * split,
		       काष्ठा metapage ** rmpp, s64 * rbnp);

अटल पूर्णांक xtSplitRoot(tid_t tid, काष्ठा inode *ip,
		       काष्ठा xtsplit * split, काष्ठा metapage ** rmpp);

#अगर_घोषित _STILL_TO_PORT
अटल पूर्णांक xtDeleteUp(tid_t tid, काष्ठा inode *ip, काष्ठा metapage * fmp,
		      xtpage_t * fp, काष्ठा btstack * btstack);

अटल पूर्णांक xtSearchNode(काष्ठा inode *ip,
			xad_t * xad,
			पूर्णांक *cmpp, काष्ठा btstack * btstack, पूर्णांक flag);

अटल पूर्णांक xtRelink(tid_t tid, काष्ठा inode *ip, xtpage_t * fp);
#पूर्ण_अगर				/*  _STILL_TO_PORT */

/*
 *	xtLookup()
 *
 * function: map a single page पूर्णांकo a physical extent;
 */
पूर्णांक xtLookup(काष्ठा inode *ip, s64 lstart,
	     s64 llen, पूर्णांक *pflag, s64 * paddr, s32 * plen, पूर्णांक no_check)
अणु
	पूर्णांक rc = 0;
	काष्ठा btstack btstack;
	पूर्णांक cmp;
	s64 bn;
	काष्ठा metapage *mp;
	xtpage_t *p;
	पूर्णांक index;
	xad_t *xad;
	s64 next, size, xoff, xend;
	पूर्णांक xlen;
	s64 xaddr;

	*paddr = 0;
	*plen = llen;

	अगर (!no_check) अणु
		/* is lookup offset beyond eof ? */
		size = ((u64) ip->i_size + (JFS_SBI(ip->i_sb)->bsize - 1)) >>
		    JFS_SBI(ip->i_sb)->l2bsize;
		अगर (lstart >= size)
			वापस 0;
	पूर्ण

	/*
	 * search क्रम the xad entry covering the logical extent
	 */
//search:
	अगर ((rc = xtSearch(ip, lstart, &next, &cmp, &btstack, 0))) अणु
		jfs_err("xtLookup: xtSearch returned %d", rc);
		वापस rc;
	पूर्ण

	/*
	 *	compute the physical extent covering logical extent
	 *
	 * N.B. search may have failed (e.g., hole in sparse file),
	 * and वापसed the index of the next entry.
	 */
	/* retrieve search result */
	XT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

	/* is xad found covering start of logical extent ?
	 * lstart is a page start address,
	 * i.e., lstart cannot start in a hole;
	 */
	अगर (cmp) अणु
		अगर (next)
			*plen = min(next - lstart, llen);
		जाओ out;
	पूर्ण

	/*
	 * lxd covered by xad
	 */
	xad = &p->xad[index];
	xoff = offsetXAD(xad);
	xlen = lengthXAD(xad);
	xend = xoff + xlen;
	xaddr = addressXAD(xad);

	/* initialize new pxd */
	*pflag = xad->flag;
	*paddr = xaddr + (lstart - xoff);
	/* a page must be fully covered by an xad */
	*plen = min(xend - lstart, llen);

      out:
	XT_PUTPAGE(mp);

	वापस rc;
पूर्ण

/*
 *	xtSearch()
 *
 * function:	search क्रम the xad entry covering specअगरied offset.
 *
 * parameters:
 *	ip	- file object;
 *	xoff	- extent offset;
 *	nextp	- address of next extent (अगर any) क्रम search miss
 *	cmpp	- comparison result:
 *	btstack - traverse stack;
 *	flag	- search process flag (XT_INSERT);
 *
 * वापसs:
 *	btstack contains (bn, index) of search path traversed to the entry.
 *	*cmpp is set to result of comparison with the entry वापसed.
 *	the page containing the entry is pinned at निकास.
 */
अटल पूर्णांक xtSearch(काष्ठा inode *ip, s64 xoff,	s64 *nextp,
		    पूर्णांक *cmpp, काष्ठा btstack * btstack, पूर्णांक flag)
अणु
	काष्ठा jfs_inode_info *jfs_ip = JFS_IP(ip);
	पूर्णांक rc = 0;
	पूर्णांक cmp = 1;		/* init क्रम empty page */
	s64 bn;			/* block number */
	काष्ठा metapage *mp;	/* page buffer */
	xtpage_t *p;		/* page */
	xad_t *xad;
	पूर्णांक base, index, lim, btindex;
	काष्ठा btframe *btsp;
	पूर्णांक nsplit = 0;		/* number of pages to split */
	s64 t64;
	s64 next = 0;

	INCREMENT(xtStat.search);

	BT_CLR(btstack);

	btstack->nsplit = 0;

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
		XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;

		/* try sequential access heuristics with the previous
		 * access entry in target leaf page:
		 * once search narrowed करोwn पूर्णांकo the target leaf,
		 * key must either match an entry in the leaf or
		 * key entry करोes not exist in the tree;
		 */
//fastSearch:
		अगर ((jfs_ip->btorder & BT_SEQUENTIAL) &&
		    (p->header.flag & BT_LEAF) &&
		    (index = jfs_ip->btindex) <
		    le16_to_cpu(p->header.nextindex)) अणु
			xad = &p->xad[index];
			t64 = offsetXAD(xad);
			अगर (xoff < t64 + lengthXAD(xad)) अणु
				अगर (xoff >= t64) अणु
					*cmpp = 0;
					जाओ out;
				पूर्ण

				/* stop sequential access heuristics */
				जाओ binarySearch;
			पूर्ण अन्यथा अणु	/* (t64 + lengthXAD(xad)) <= xoff */

				/* try next sequential entry */
				index++;
				अगर (index <
				    le16_to_cpu(p->header.nextindex)) अणु
					xad++;
					t64 = offsetXAD(xad);
					अगर (xoff < t64 + lengthXAD(xad)) अणु
						अगर (xoff >= t64) अणु
							*cmpp = 0;
							जाओ out;
						पूर्ण

						/* miss: key falls between
						 * previous and this entry
						 */
						*cmpp = 1;
						next = t64;
						जाओ out;
					पूर्ण

					/* (xoff >= t64 + lengthXAD(xad));
					 * matching entry may be further out:
					 * stop heuristic search
					 */
					/* stop sequential access heuristics */
					जाओ binarySearch;
				पूर्ण

				/* (index == p->header.nextindex);
				 * miss: key entry करोes not exist in
				 * the target leaf/tree
				 */
				*cmpp = 1;
				जाओ out;
			पूर्ण

			/*
			 * अगर hit, वापस index of the entry found, and
			 * अगर miss, where new entry with search key is
			 * to be inserted;
			 */
		      out:
			/* compute number of pages to split */
			अगर (flag & XT_INSERT) अणु
				अगर (p->header.nextindex ==	/* little-endian */
				    p->header.maxentry)
					nsplit++;
				अन्यथा
					nsplit = 0;
				btstack->nsplit = nsplit;
			पूर्ण

			/* save search result */
			btsp = btstack->top;
			btsp->bn = bn;
			btsp->index = index;
			btsp->mp = mp;

			/* update sequential access heuristics */
			jfs_ip->btindex = index;

			अगर (nextp)
				*nextp = next;

			INCREMENT(xtStat.fastSearch);
			वापस 0;
		पूर्ण

		/* well, ... full search now */
	      binarySearch:
		lim = le16_to_cpu(p->header.nextindex) - XTENTRYSTART;

		/*
		 * binary search with search key K on the current page
		 */
		क्रम (base = XTENTRYSTART; lim; lim >>= 1) अणु
			index = base + (lim >> 1);

			XT_CMP(cmp, xoff, &p->xad[index], t64);
			अगर (cmp == 0) अणु
				/*
				 *	search hit
				 */
				/* search hit - leaf page:
				 * वापस the entry found
				 */
				अगर (p->header.flag & BT_LEAF) अणु
					*cmpp = cmp;

					/* compute number of pages to split */
					अगर (flag & XT_INSERT) अणु
						अगर (p->header.nextindex ==
						    p->header.maxentry)
							nsplit++;
						अन्यथा
							nsplit = 0;
						btstack->nsplit = nsplit;
					पूर्ण

					/* save search result */
					btsp = btstack->top;
					btsp->bn = bn;
					btsp->index = index;
					btsp->mp = mp;

					/* init sequential access heuristics */
					btindex = jfs_ip->btindex;
					अगर (index == btindex ||
					    index == btindex + 1)
						jfs_ip->btorder = BT_SEQUENTIAL;
					अन्यथा
						jfs_ip->btorder = BT_RANDOM;
					jfs_ip->btindex = index;

					वापस 0;
				पूर्ण
				/* search hit - पूर्णांकernal page:
				 * descend/search its child page
				 */
				अगर (index < le16_to_cpu(p->header.nextindex)-1)
					next = offsetXAD(&p->xad[index + 1]);
				जाओ next;
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
		 * search key (K) and may be zero or maxentry index.
		 */
		अगर (base < le16_to_cpu(p->header.nextindex))
			next = offsetXAD(&p->xad[base]);
		/*
		 * search miss - leaf page:
		 *
		 * वापस location of entry (base) where new entry with
		 * search key K is to be inserted.
		 */
		अगर (p->header.flag & BT_LEAF) अणु
			*cmpp = cmp;

			/* compute number of pages to split */
			अगर (flag & XT_INSERT) अणु
				अगर (p->header.nextindex ==
				    p->header.maxentry)
					nsplit++;
				अन्यथा
					nsplit = 0;
				btstack->nsplit = nsplit;
			पूर्ण

			/* save search result */
			btsp = btstack->top;
			btsp->bn = bn;
			btsp->index = base;
			btsp->mp = mp;

			/* init sequential access heuristics */
			btindex = jfs_ip->btindex;
			अगर (base == btindex || base == btindex + 1)
				jfs_ip->btorder = BT_SEQUENTIAL;
			अन्यथा
				jfs_ip->btorder = BT_RANDOM;
			jfs_ip->btindex = base;

			अगर (nextp)
				*nextp = next;

			वापस 0;
		पूर्ण

		/*
		 * search miss - non-leaf page:
		 *
		 * अगर base is non-zero, decrement base by one to get the parent
		 * entry of the child page to search.
		 */
		index = base ? base - 1 : base;

		/*
		 * go करोwn to child page
		 */
	      next:
		/* update number of pages to split */
		अगर (p->header.nextindex == p->header.maxentry)
			nsplit++;
		अन्यथा
			nsplit = 0;

		/* push (bn, index) of the parent page/entry */
		अगर (BT_STACK_FULL(btstack)) अणु
			jfs_error(ip->i_sb, "stack overrun!\n");
			XT_PUTPAGE(mp);
			वापस -EIO;
		पूर्ण
		BT_PUSH(btstack, bn, index);

		/* get the child page block number */
		bn = addressXAD(&p->xad[index]);

		/* unpin the parent page */
		XT_PUTPAGE(mp);
	पूर्ण
पूर्ण

/*
 *	xtInsert()
 *
 * function:
 *
 * parameter:
 *	tid	- transaction id;
 *	ip	- file object;
 *	xflag	- extent flag (XAD_NOTRECORDED):
 *	xoff	- extent offset;
 *	xlen	- extent length;
 *	xaddrp	- extent address poपूर्णांकer (in/out):
 *		अगर (*xaddrp)
 *			caller allocated data extent at *xaddrp;
 *		अन्यथा
 *			allocate data extent and वापस its xaddr;
 *	flag	-
 *
 * वापस:
 */
पूर्णांक xtInsert(tid_t tid,		/* transaction id */
	     काष्ठा inode *ip, पूर्णांक xflag, s64 xoff, s32 xlen, s64 * xaddrp,
	     पूर्णांक flag)
अणु
	पूर्णांक rc = 0;
	s64 xaddr, hपूर्णांक;
	काष्ठा metapage *mp;	/* meta-page buffer */
	xtpage_t *p;		/* base B+-tree index page */
	s64 bn;
	पूर्णांक index, nextindex;
	काष्ठा btstack btstack;	/* traverse stack */
	काष्ठा xtsplit split;	/* split inक्रमmation */
	xad_t *xad;
	पूर्णांक cmp;
	s64 next;
	काष्ठा tlock *tlck;
	काष्ठा xtlock *xtlck;

	jfs_info("xtInsert: nxoff:0x%lx nxlen:0x%x", (uदीर्घ) xoff, xlen);

	/*
	 *	search क्रम the entry location at which to insert:
	 *
	 * xtFastSearch() and xtSearch() both वापसs (leaf page
	 * pinned, index at which to insert).
	 * n.b. xtSearch() may वापस index of maxentry of
	 * the full page.
	 */
	अगर ((rc = xtSearch(ip, xoff, &next, &cmp, &btstack, XT_INSERT)))
		वापस rc;

	/* retrieve search result */
	XT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

	/* This test must follow XT_GETSEARCH since mp must be valid अगर
	 * we branch to out: */
	अगर ((cmp == 0) || (next && (xlen > next - xoff))) अणु
		rc = -EEXIST;
		जाओ out;
	पूर्ण

	/*
	 * allocate data extent requested
	 *
	 * allocation hपूर्णांक: last xad
	 */
	अगर ((xaddr = *xaddrp) == 0) अणु
		अगर (index > XTENTRYSTART) अणु
			xad = &p->xad[index - 1];
			hपूर्णांक = addressXAD(xad) + lengthXAD(xad) - 1;
		पूर्ण अन्यथा
			hपूर्णांक = 0;
		अगर ((rc = dquot_alloc_block(ip, xlen)))
			जाओ out;
		अगर ((rc = dbAlloc(ip, hपूर्णांक, (s64) xlen, &xaddr))) अणु
			dquot_मुक्त_block(ip, xlen);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 *	insert entry क्रम new extent
	 */
	xflag |= XAD_NEW;

	/*
	 *	अगर the leaf page is full, split the page and
	 *	propagate up the router entry क्रम the new page from split
	 *
	 * The xtSplitUp() will insert the entry and unpin the leaf page.
	 */
	nextindex = le16_to_cpu(p->header.nextindex);
	अगर (nextindex == le16_to_cpu(p->header.maxentry)) अणु
		split.mp = mp;
		split.index = index;
		split.flag = xflag;
		split.off = xoff;
		split.len = xlen;
		split.addr = xaddr;
		split.pxdlist = शून्य;
		अगर ((rc = xtSplitUp(tid, ip, &split, &btstack))) अणु
			/* unकरो data extent allocation */
			अगर (*xaddrp == 0) अणु
				dbFree(ip, xaddr, (s64) xlen);
				dquot_मुक्त_block(ip, xlen);
			पूर्ण
			वापस rc;
		पूर्ण

		*xaddrp = xaddr;
		वापस 0;
	पूर्ण

	/*
	 *	insert the new entry पूर्णांकo the leaf page
	 */
	/*
	 * acquire a transaction lock on the leaf page;
	 *
	 * action: xad insertion/extension;
	 */
	BT_MARK_सूचीTY(mp, ip);

	/* अगर insert पूर्णांकo middle, shअगरt right reमुख्यing entries. */
	अगर (index < nextindex)
		स_हटाओ(&p->xad[index + 1], &p->xad[index],
			(nextindex - index) * माप(xad_t));

	/* insert the new entry: mark the entry NEW */
	xad = &p->xad[index];
	XT_PUTENTRY(xad, xflag, xoff, xlen, xaddr);

	/* advance next available entry index */
	le16_add_cpu(&p->header.nextindex, 1);

	/* Don't log it अगर there are no links to the file */
	अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
		tlck = txLock(tid, ip, mp, tlckXTREE | tlckGROW);
		xtlck = (काष्ठा xtlock *) & tlck->lock;
		xtlck->lwm.offset =
		    (xtlck->lwm.offset) ? min(index,
					      (पूर्णांक)xtlck->lwm.offset) : index;
		xtlck->lwm.length =
		    le16_to_cpu(p->header.nextindex) - xtlck->lwm.offset;
	पूर्ण

	*xaddrp = xaddr;

      out:
	/* unpin the leaf page */
	XT_PUTPAGE(mp);

	वापस rc;
पूर्ण


/*
 *	xtSplitUp()
 *
 * function:
 *	split full pages as propagating insertion up the tree
 *
 * parameter:
 *	tid	- transaction id;
 *	ip	- file object;
 *	split	- entry parameter descriptor;
 *	btstack - traverse stack from xtSearch()
 *
 * वापस:
 */
अटल पूर्णांक
xtSplitUp(tid_t tid,
	  काष्ठा inode *ip, काष्ठा xtsplit * split, काष्ठा btstack * btstack)
अणु
	पूर्णांक rc = 0;
	काष्ठा metapage *smp;
	xtpage_t *sp;		/* split page */
	काष्ठा metapage *rmp;
	s64 rbn;		/* new right page block number */
	काष्ठा metapage *rcmp;
	xtpage_t *rcp;		/* right child page */
	s64 rcbn;		/* right child page block number */
	पूर्णांक skip;		/* index of entry of insertion */
	पूर्णांक nextindex;		/* next available entry index of p */
	काष्ठा btframe *parent;	/* parent page entry on traverse stack */
	xad_t *xad;
	s64 xaddr;
	पूर्णांक xlen;
	पूर्णांक nsplit;		/* number of pages split */
	काष्ठा pxdlist pxdlist;
	pxd_t *pxd;
	काष्ठा tlock *tlck;
	काष्ठा xtlock *xtlck;

	smp = split->mp;
	sp = XT_PAGE(ip, smp);

	/* is inode xtree root extension/अंतरभूत EA area मुक्त ? */
	अगर ((sp->header.flag & BT_ROOT) && (!S_ISसूची(ip->i_mode)) &&
	    (le16_to_cpu(sp->header.maxentry) < XTROOTMAXSLOT) &&
	    (JFS_IP(ip)->mode2 & INLINEEA)) अणु
		sp->header.maxentry = cpu_to_le16(XTROOTMAXSLOT);
		JFS_IP(ip)->mode2 &= ~INLINEEA;

		BT_MARK_सूचीTY(smp, ip);
		/*
		 * acquire a transaction lock on the leaf page;
		 *
		 * action: xad insertion/extension;
		 */

		/* अगर insert पूर्णांकo middle, shअगरt right reमुख्यing entries. */
		skip = split->index;
		nextindex = le16_to_cpu(sp->header.nextindex);
		अगर (skip < nextindex)
			स_हटाओ(&sp->xad[skip + 1], &sp->xad[skip],
				(nextindex - skip) * माप(xad_t));

		/* insert the new entry: mark the entry NEW */
		xad = &sp->xad[skip];
		XT_PUTENTRY(xad, split->flag, split->off, split->len,
			    split->addr);

		/* advance next available entry index */
		le16_add_cpu(&sp->header.nextindex, 1);

		/* Don't log it अगर there are no links to the file */
		अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
			tlck = txLock(tid, ip, smp, tlckXTREE | tlckGROW);
			xtlck = (काष्ठा xtlock *) & tlck->lock;
			xtlck->lwm.offset = (xtlck->lwm.offset) ?
			    min(skip, (पूर्णांक)xtlck->lwm.offset) : skip;
			xtlck->lwm.length =
			    le16_to_cpu(sp->header.nextindex) -
			    xtlck->lwm.offset;
		पूर्ण

		वापस 0;
	पूर्ण

	/*
	 * allocate new index blocks to cover index page split(s)
	 *
	 * allocation hपूर्णांक: ?
	 */
	अगर (split->pxdlist == शून्य) अणु
		nsplit = btstack->nsplit;
		split->pxdlist = &pxdlist;
		pxdlist.maxnpxd = pxdlist.npxd = 0;
		pxd = &pxdlist.pxd[0];
		xlen = JFS_SBI(ip->i_sb)->nbperpage;
		क्रम (; nsplit > 0; nsplit--, pxd++) अणु
			अगर ((rc = dbAlloc(ip, (s64) 0, (s64) xlen, &xaddr))
			    == 0) अणु
				PXDaddress(pxd, xaddr);
				PXDlength(pxd, xlen);

				pxdlist.maxnpxd++;

				जारी;
			पूर्ण

			/* unकरो allocation */

			XT_PUTPAGE(smp);
			वापस rc;
		पूर्ण
	पूर्ण

	/*
	 * Split leaf page <sp> पूर्णांकo <sp> and a new right page <rp>.
	 *
	 * The split routines insert the new entry पूर्णांकo the leaf page,
	 * and acquire txLock as appropriate.
	 * वापस <rp> pinned and its block number <rpbn>.
	 */
	rc = (sp->header.flag & BT_ROOT) ?
	    xtSplitRoot(tid, ip, split, &rmp) :
	    xtSplitPage(tid, ip, split, &rmp, &rbn);

	XT_PUTPAGE(smp);

	अगर (rc)
		वापस -EIO;
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
	 * There are a maximum of 3 pages pinned at any समय:
	 * right child, left parent and right parent (when the parent splits)
	 * to keep the child page pinned जबतक working on the parent.
	 * make sure that all pins are released at निकास.
	 */
	जबतक ((parent = BT_POP(btstack)) != शून्य) अणु
		/* parent page specअगरied by stack frame <parent> */

		/* keep current child pages <rcp> pinned */
		rcmp = rmp;
		rcbn = rbn;
		rcp = XT_PAGE(ip, rcmp);

		/*
		 * insert router entry in parent क्रम new right child page <rp>
		 */
		/* get/pin the parent page <sp> */
		XT_GETPAGE(ip, parent->bn, smp, PSIZE, sp, rc);
		अगर (rc) अणु
			XT_PUTPAGE(rcmp);
			वापस rc;
		पूर्ण

		/*
		 * The new key entry goes ONE AFTER the index of parent entry,
		 * because the split was to the right.
		 */
		skip = parent->index + 1;

		/*
		 * split or shअगरt right reमुख्यing entries of the parent page
		 */
		nextindex = le16_to_cpu(sp->header.nextindex);
		/*
		 * parent page is full - split the parent page
		 */
		अगर (nextindex == le16_to_cpu(sp->header.maxentry)) अणु
			/* init क्रम parent page split */
			split->mp = smp;
			split->index = skip;	/* index at insert */
			split->flag = XAD_NEW;
			split->off = offsetXAD(&rcp->xad[XTENTRYSTART]);
			split->len = JFS_SBI(ip->i_sb)->nbperpage;
			split->addr = rcbn;

			/* unpin previous right child page */
			XT_PUTPAGE(rcmp);

			/* The split routines insert the new entry,
			 * and acquire txLock as appropriate.
			 * वापस <rp> pinned and its block number <rpbn>.
			 */
			rc = (sp->header.flag & BT_ROOT) ?
			    xtSplitRoot(tid, ip, split, &rmp) :
			    xtSplitPage(tid, ip, split, &rmp, &rbn);
			अगर (rc) अणु
				XT_PUTPAGE(smp);
				वापस rc;
			पूर्ण

			XT_PUTPAGE(smp);
			/* keep new child page <rp> pinned */
		पूर्ण
		/*
		 * parent page is not full - insert in parent page
		 */
		अन्यथा अणु
			/*
			 * insert router entry in parent क्रम the right child
			 * page from the first entry of the right child page:
			 */
			/*
			 * acquire a transaction lock on the parent page;
			 *
			 * action: router xad insertion;
			 */
			BT_MARK_सूचीTY(smp, ip);

			/*
			 * अगर insert पूर्णांकo middle, shअगरt right reमुख्यing entries
			 */
			अगर (skip < nextindex)
				स_हटाओ(&sp->xad[skip + 1], &sp->xad[skip],
					(nextindex -
					 skip) << L2XTSLOTSIZE);

			/* insert the router entry */
			xad = &sp->xad[skip];
			XT_PUTENTRY(xad, XAD_NEW,
				    offsetXAD(&rcp->xad[XTENTRYSTART]),
				    JFS_SBI(ip->i_sb)->nbperpage, rcbn);

			/* advance next available entry index. */
			le16_add_cpu(&sp->header.nextindex, 1);

			/* Don't log it अगर there are no links to the file */
			अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
				tlck = txLock(tid, ip, smp,
					      tlckXTREE | tlckGROW);
				xtlck = (काष्ठा xtlock *) & tlck->lock;
				xtlck->lwm.offset = (xtlck->lwm.offset) ?
				    min(skip, (पूर्णांक)xtlck->lwm.offset) : skip;
				xtlck->lwm.length =
				    le16_to_cpu(sp->header.nextindex) -
				    xtlck->lwm.offset;
			पूर्ण

			/* unpin parent page */
			XT_PUTPAGE(smp);

			/* निकास propagate up */
			अवरोध;
		पूर्ण
	पूर्ण

	/* unpin current right page */
	XT_PUTPAGE(rmp);

	वापस 0;
पूर्ण


/*
 *	xtSplitPage()
 *
 * function:
 *	split a full non-root page पूर्णांकo
 *	original/split/left page and new right page
 *	i.e., the original/split page reमुख्यs as left page.
 *
 * parameter:
 *	पूर्णांक		tid,
 *	काष्ठा inode	*ip,
 *	काष्ठा xtsplit	*split,
 *	काष्ठा metapage	**rmpp,
 *	u64		*rbnp,
 *
 * वापस:
 *	Poपूर्णांकer to page in which to insert or शून्य on error.
 */
अटल पूर्णांक
xtSplitPage(tid_t tid, काष्ठा inode *ip,
	    काष्ठा xtsplit * split, काष्ठा metapage ** rmpp, s64 * rbnp)
अणु
	पूर्णांक rc = 0;
	काष्ठा metapage *smp;
	xtpage_t *sp;
	काष्ठा metapage *rmp;
	xtpage_t *rp;		/* new right page allocated */
	s64 rbn;		/* new right page block number */
	काष्ठा metapage *mp;
	xtpage_t *p;
	s64 nextbn;
	पूर्णांक skip, maxentry, middle, righthalf, n;
	xad_t *xad;
	काष्ठा pxdlist *pxdlist;
	pxd_t *pxd;
	काष्ठा tlock *tlck;
	काष्ठा xtlock *sxtlck = शून्य, *rxtlck = शून्य;
	पूर्णांक quota_allocation = 0;

	smp = split->mp;
	sp = XT_PAGE(ip, smp);

	INCREMENT(xtStat.split);

	pxdlist = split->pxdlist;
	pxd = &pxdlist->pxd[pxdlist->npxd];
	pxdlist->npxd++;
	rbn = addressPXD(pxd);

	/* Allocate blocks to quota. */
	rc = dquot_alloc_block(ip, lengthPXD(pxd));
	अगर (rc)
		जाओ clean_up;

	quota_allocation += lengthPXD(pxd);

	/*
	 * allocate the new right page क्रम the split
	 */
	rmp = get_metapage(ip, rbn, PSIZE, 1);
	अगर (rmp == शून्य) अणु
		rc = -EIO;
		जाओ clean_up;
	पूर्ण

	jfs_info("xtSplitPage: ip:0x%p smp:0x%p rmp:0x%p", ip, smp, rmp);

	BT_MARK_सूचीTY(rmp, ip);
	/*
	 * action: new page;
	 */

	rp = (xtpage_t *) rmp->data;
	rp->header.self = *pxd;
	rp->header.flag = sp->header.flag & BT_TYPE;
	rp->header.maxentry = sp->header.maxentry;	/* little-endian */
	rp->header.nextindex = cpu_to_le16(XTENTRYSTART);

	BT_MARK_सूचीTY(smp, ip);
	/* Don't log it अगर there are no links to the file */
	अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
		/*
		 * acquire a transaction lock on the new right page;
		 */
		tlck = txLock(tid, ip, rmp, tlckXTREE | tlckNEW);
		rxtlck = (काष्ठा xtlock *) & tlck->lock;
		rxtlck->lwm.offset = XTENTRYSTART;
		/*
		 * acquire a transaction lock on the split page
		 */
		tlck = txLock(tid, ip, smp, tlckXTREE | tlckGROW);
		sxtlck = (काष्ठा xtlock *) & tlck->lock;
	पूर्ण

	/*
	 * initialize/update sibling poपूर्णांकers of <sp> and <rp>
	 */
	nextbn = le64_to_cpu(sp->header.next);
	rp->header.next = cpu_to_le64(nextbn);
	rp->header.prev = cpu_to_le64(addressPXD(&sp->header.self));
	sp->header.next = cpu_to_le64(rbn);

	skip = split->index;

	/*
	 *	sequential append at tail (after last entry of last page)
	 *
	 * अगर splitting the last page on a level because of appending
	 * a entry to it (skip is maxentry), it's likely that the access is
	 * sequential. adding an empty page on the side of the level is less
	 * work and can push the fill factor much higher than normal.
	 * अगर we're wrong it's no big deal -  we will करो the split the right
	 * way next समय.
	 * (it may look like it's equally easy to करो a similar hack क्रम
	 * reverse sorted data, that is, split the tree left, but it's not.
	 * Be my guest.)
	 */
	अगर (nextbn == 0 && skip == le16_to_cpu(sp->header.maxentry)) अणु
		/*
		 * acquire a transaction lock on the new/right page;
		 *
		 * action: xad insertion;
		 */
		/* insert entry at the first entry of the new right page */
		xad = &rp->xad[XTENTRYSTART];
		XT_PUTENTRY(xad, split->flag, split->off, split->len,
			    split->addr);

		rp->header.nextindex = cpu_to_le16(XTENTRYSTART + 1);

		अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
			/* rxtlck->lwm.offset = XTENTRYSTART; */
			rxtlck->lwm.length = 1;
		पूर्ण

		*rmpp = rmp;
		*rbnp = rbn;

		jfs_info("xtSplitPage: sp:0x%p rp:0x%p", sp, rp);
		वापस 0;
	पूर्ण

	/*
	 *	non-sequential insert (at possibly middle page)
	 */

	/*
	 * update previous poपूर्णांकer of old next/right page of <sp>
	 */
	अगर (nextbn != 0) अणु
		XT_GETPAGE(ip, nextbn, mp, PSIZE, p, rc);
		अगर (rc) अणु
			XT_PUTPAGE(rmp);
			जाओ clean_up;
		पूर्ण

		BT_MARK_सूचीTY(mp, ip);
		/*
		 * acquire a transaction lock on the next page;
		 *
		 * action:sibling poपूर्णांकer update;
		 */
		अगर (!test_cflag(COMMIT_Nolink, ip))
			tlck = txLock(tid, ip, mp, tlckXTREE | tlckRELINK);

		p->header.prev = cpu_to_le64(rbn);

		/* sibling page may have been updated previously, or
		 * it may be updated later;
		 */

		XT_PUTPAGE(mp);
	पूर्ण

	/*
	 * split the data between the split and new/right pages
	 */
	maxentry = le16_to_cpu(sp->header.maxentry);
	middle = maxentry >> 1;
	righthalf = maxentry - middle;

	/*
	 * skip index in old split/left page - insert पूर्णांकo left page:
	 */
	अगर (skip <= middle) अणु
		/* move right half of split page to the new right page */
		स_हटाओ(&rp->xad[XTENTRYSTART], &sp->xad[middle],
			righthalf << L2XTSLOTSIZE);

		/* shअगरt right tail of left half to make room क्रम new entry */
		अगर (skip < middle)
			स_हटाओ(&sp->xad[skip + 1], &sp->xad[skip],
				(middle - skip) << L2XTSLOTSIZE);

		/* insert new entry */
		xad = &sp->xad[skip];
		XT_PUTENTRY(xad, split->flag, split->off, split->len,
			    split->addr);

		/* update page header */
		sp->header.nextindex = cpu_to_le16(middle + 1);
		अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
			sxtlck->lwm.offset = (sxtlck->lwm.offset) ?
			    min(skip, (पूर्णांक)sxtlck->lwm.offset) : skip;
		पूर्ण

		rp->header.nextindex =
		    cpu_to_le16(XTENTRYSTART + righthalf);
	पूर्ण
	/*
	 * skip index in new right page - insert पूर्णांकo right page:
	 */
	अन्यथा अणु
		/* move left head of right half to right page */
		n = skip - middle;
		स_हटाओ(&rp->xad[XTENTRYSTART], &sp->xad[middle],
			n << L2XTSLOTSIZE);

		/* insert new entry */
		n += XTENTRYSTART;
		xad = &rp->xad[n];
		XT_PUTENTRY(xad, split->flag, split->off, split->len,
			    split->addr);

		/* move right tail of right half to right page */
		अगर (skip < maxentry)
			स_हटाओ(&rp->xad[n + 1], &sp->xad[skip],
				(maxentry - skip) << L2XTSLOTSIZE);

		/* update page header */
		sp->header.nextindex = cpu_to_le16(middle);
		अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
			sxtlck->lwm.offset = (sxtlck->lwm.offset) ?
			    min(middle, (पूर्णांक)sxtlck->lwm.offset) : middle;
		पूर्ण

		rp->header.nextindex = cpu_to_le16(XTENTRYSTART +
						   righthalf + 1);
	पूर्ण

	अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
		sxtlck->lwm.length = le16_to_cpu(sp->header.nextindex) -
		    sxtlck->lwm.offset;

		/* rxtlck->lwm.offset = XTENTRYSTART; */
		rxtlck->lwm.length = le16_to_cpu(rp->header.nextindex) -
		    XTENTRYSTART;
	पूर्ण

	*rmpp = rmp;
	*rbnp = rbn;

	jfs_info("xtSplitPage: sp:0x%p rp:0x%p", sp, rp);
	वापस rc;

      clean_up:

	/* Rollback quota allocation. */
	अगर (quota_allocation)
		dquot_मुक्त_block(ip, quota_allocation);

	वापस (rc);
पूर्ण


/*
 *	xtSplitRoot()
 *
 * function:
 *	split the full root page पूर्णांकo original/root/split page and new
 *	right page
 *	i.e., root reमुख्यs fixed in tree anchor (inode) and the root is
 *	copied to a single new right child page since root page <<
 *	non-root page, and the split root page contains a single entry
 *	क्रम the new right child page.
 *
 * parameter:
 *	पूर्णांक		tid,
 *	काष्ठा inode	*ip,
 *	काष्ठा xtsplit	*split,
 *	काष्ठा metapage	**rmpp)
 *
 * वापस:
 *	Poपूर्णांकer to page in which to insert or शून्य on error.
 */
अटल पूर्णांक
xtSplitRoot(tid_t tid,
	    काष्ठा inode *ip, काष्ठा xtsplit * split, काष्ठा metapage ** rmpp)
अणु
	xtpage_t *sp;
	काष्ठा metapage *rmp;
	xtpage_t *rp;
	s64 rbn;
	पूर्णांक skip, nextindex;
	xad_t *xad;
	pxd_t *pxd;
	काष्ठा pxdlist *pxdlist;
	काष्ठा tlock *tlck;
	काष्ठा xtlock *xtlck;
	पूर्णांक rc;

	sp = &JFS_IP(ip)->i_xtroot;

	INCREMENT(xtStat.split);

	/*
	 *	allocate a single (right) child page
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

	jfs_info("xtSplitRoot: ip:0x%p rmp:0x%p", ip, rmp);

	/*
	 * acquire a transaction lock on the new right page;
	 *
	 * action: new page;
	 */
	BT_MARK_सूचीTY(rmp, ip);

	rp = (xtpage_t *) rmp->data;
	rp->header.flag =
	    (sp->header.flag & BT_LEAF) ? BT_LEAF : BT_INTERNAL;
	rp->header.self = *pxd;
	rp->header.nextindex = cpu_to_le16(XTENTRYSTART);
	rp->header.maxentry = cpu_to_le16(PSIZE >> L2XTSLOTSIZE);

	/* initialize sibling poपूर्णांकers */
	rp->header.next = 0;
	rp->header.prev = 0;

	/*
	 * copy the in-line root page पूर्णांकo new right page extent
	 */
	nextindex = le16_to_cpu(sp->header.maxentry);
	स_हटाओ(&rp->xad[XTENTRYSTART], &sp->xad[XTENTRYSTART],
		(nextindex - XTENTRYSTART) << L2XTSLOTSIZE);

	/*
	 * insert the new entry पूर्णांकo the new right/child page
	 * (skip index in the new right page will not change)
	 */
	skip = split->index;
	/* अगर insert पूर्णांकo middle, shअगरt right reमुख्यing entries */
	अगर (skip != nextindex)
		स_हटाओ(&rp->xad[skip + 1], &rp->xad[skip],
			(nextindex - skip) * माप(xad_t));

	xad = &rp->xad[skip];
	XT_PUTENTRY(xad, split->flag, split->off, split->len, split->addr);

	/* update page header */
	rp->header.nextindex = cpu_to_le16(nextindex + 1);

	अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
		tlck = txLock(tid, ip, rmp, tlckXTREE | tlckNEW);
		xtlck = (काष्ठा xtlock *) & tlck->lock;
		xtlck->lwm.offset = XTENTRYSTART;
		xtlck->lwm.length = le16_to_cpu(rp->header.nextindex) -
		    XTENTRYSTART;
	पूर्ण

	/*
	 *	reset the root
	 *
	 * init root with the single entry क्रम the new right page
	 * set the 1st entry offset to 0, which क्रमce the left-most key
	 * at any level of the tree to be less than any search key.
	 */
	/*
	 * acquire a transaction lock on the root page (in-memory inode);
	 *
	 * action: root split;
	 */
	BT_MARK_सूचीTY(split->mp, ip);

	xad = &sp->xad[XTENTRYSTART];
	XT_PUTENTRY(xad, XAD_NEW, 0, JFS_SBI(ip->i_sb)->nbperpage, rbn);

	/* update page header of root */
	sp->header.flag &= ~BT_LEAF;
	sp->header.flag |= BT_INTERNAL;

	sp->header.nextindex = cpu_to_le16(XTENTRYSTART + 1);

	अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
		tlck = txLock(tid, ip, split->mp, tlckXTREE | tlckGROW);
		xtlck = (काष्ठा xtlock *) & tlck->lock;
		xtlck->lwm.offset = XTENTRYSTART;
		xtlck->lwm.length = 1;
	पूर्ण

	*rmpp = rmp;

	jfs_info("xtSplitRoot: sp:0x%p rp:0x%p", sp, rp);
	वापस 0;
पूर्ण


/*
 *	xtExtend()
 *
 * function: extend in-place;
 *
 * note: existing extent may or may not have been committed.
 * caller is responsible क्रम pager buffer cache update, and
 * working block allocation map update;
 * update pmap: alloc whole extended extent;
 */
पूर्णांक xtExtend(tid_t tid,		/* transaction id */
	     काष्ठा inode *ip, s64 xoff,	/* delta extent offset */
	     s32 xlen,		/* delta extent length */
	     पूर्णांक flag)
अणु
	पूर्णांक rc = 0;
	पूर्णांक cmp;
	काष्ठा metapage *mp;	/* meta-page buffer */
	xtpage_t *p;		/* base B+-tree index page */
	s64 bn;
	पूर्णांक index, nextindex, len;
	काष्ठा btstack btstack;	/* traverse stack */
	काष्ठा xtsplit split;	/* split inक्रमmation */
	xad_t *xad;
	s64 xaddr;
	काष्ठा tlock *tlck;
	काष्ठा xtlock *xtlck = शून्य;

	jfs_info("xtExtend: nxoff:0x%lx nxlen:0x%x", (uदीर्घ) xoff, xlen);

	/* there must exist extent to be extended */
	अगर ((rc = xtSearch(ip, xoff - 1, शून्य, &cmp, &btstack, XT_INSERT)))
		वापस rc;

	/* retrieve search result */
	XT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

	अगर (cmp != 0) अणु
		XT_PUTPAGE(mp);
		jfs_error(ip->i_sb, "xtSearch did not find extent\n");
		वापस -EIO;
	पूर्ण

	/* extension must be contiguous */
	xad = &p->xad[index];
	अगर ((offsetXAD(xad) + lengthXAD(xad)) != xoff) अणु
		XT_PUTPAGE(mp);
		jfs_error(ip->i_sb, "extension is not contiguous\n");
		वापस -EIO;
	पूर्ण

	/*
	 * acquire a transaction lock on the leaf page;
	 *
	 * action: xad insertion/extension;
	 */
	BT_MARK_सूचीTY(mp, ip);
	अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
		tlck = txLock(tid, ip, mp, tlckXTREE | tlckGROW);
		xtlck = (काष्ठा xtlock *) & tlck->lock;
	पूर्ण

	/* extend will overflow extent ? */
	xlen = lengthXAD(xad) + xlen;
	अगर ((len = xlen - MAXXLEN) <= 0)
		जाओ extendOld;

	/*
	 *	extent overflow: insert entry क्रम new extent
	 */
//insertNew:
	xoff = offsetXAD(xad) + MAXXLEN;
	xaddr = addressXAD(xad) + MAXXLEN;
	nextindex = le16_to_cpu(p->header.nextindex);

	/*
	 *	अगर the leaf page is full, insert the new entry and
	 *	propagate up the router entry क्रम the new page from split
	 *
	 * The xtSplitUp() will insert the entry and unpin the leaf page.
	 */
	अगर (nextindex == le16_to_cpu(p->header.maxentry)) अणु
		/* xtSpliUp() unpins leaf pages */
		split.mp = mp;
		split.index = index + 1;
		split.flag = XAD_NEW;
		split.off = xoff;	/* split offset */
		split.len = len;
		split.addr = xaddr;
		split.pxdlist = शून्य;
		अगर ((rc = xtSplitUp(tid, ip, &split, &btstack)))
			वापस rc;

		/* get back old page */
		XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;
		/*
		 * अगर leaf root has been split, original root has been
		 * copied to new child page, i.e., original entry now
		 * resides on the new child page;
		 */
		अगर (p->header.flag & BT_INTERNAL) अणु
			ASSERT(p->header.nextindex ==
			       cpu_to_le16(XTENTRYSTART + 1));
			xad = &p->xad[XTENTRYSTART];
			bn = addressXAD(xad);
			XT_PUTPAGE(mp);

			/* get new child page */
			XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
			अगर (rc)
				वापस rc;

			BT_MARK_सूचीTY(mp, ip);
			अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
				tlck = txLock(tid, ip, mp, tlckXTREE|tlckGROW);
				xtlck = (काष्ठा xtlock *) & tlck->lock;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 *	insert the new entry पूर्णांकo the leaf page
	 */
	अन्यथा अणु
		/* insert the new entry: mark the entry NEW */
		xad = &p->xad[index + 1];
		XT_PUTENTRY(xad, XAD_NEW, xoff, len, xaddr);

		/* advance next available entry index */
		le16_add_cpu(&p->header.nextindex, 1);
	पूर्ण

	/* get back old entry */
	xad = &p->xad[index];
	xlen = MAXXLEN;

	/*
	 * extend old extent
	 */
      extendOld:
	XADlength(xad, xlen);
	अगर (!(xad->flag & XAD_NEW))
		xad->flag |= XAD_EXTENDED;

	अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
		xtlck->lwm.offset =
		    (xtlck->lwm.offset) ? min(index,
					      (पूर्णांक)xtlck->lwm.offset) : index;
		xtlck->lwm.length =
		    le16_to_cpu(p->header.nextindex) - xtlck->lwm.offset;
	पूर्ण

	/* unpin the leaf page */
	XT_PUTPAGE(mp);

	वापस rc;
पूर्ण

#अगर_घोषित _NOTYET
/*
 *	xtTailgate()
 *
 * function: split existing 'tail' extent
 *	(split offset >= start offset of tail extent), and
 *	relocate and extend the split tail half;
 *
 * note: existing extent may or may not have been committed.
 * caller is responsible क्रम pager buffer cache update, and
 * working block allocation map update;
 * update pmap: मुक्त old split tail extent, alloc new extent;
 */
पूर्णांक xtTailgate(tid_t tid,		/* transaction id */
	       काष्ठा inode *ip, s64 xoff,	/* split/new extent offset */
	       s32 xlen,	/* new extent length */
	       s64 xaddr,	/* new extent address */
	       पूर्णांक flag)
अणु
	पूर्णांक rc = 0;
	पूर्णांक cmp;
	काष्ठा metapage *mp;	/* meta-page buffer */
	xtpage_t *p;		/* base B+-tree index page */
	s64 bn;
	पूर्णांक index, nextindex, llen, rlen;
	काष्ठा btstack btstack;	/* traverse stack */
	काष्ठा xtsplit split;	/* split inक्रमmation */
	xad_t *xad;
	काष्ठा tlock *tlck;
	काष्ठा xtlock *xtlck = 0;
	काष्ठा tlock *mtlck;
	काष्ठा maplock *pxdlock;

/*
म_लिखो("xtTailgate: nxoff:0x%lx nxlen:0x%x nxaddr:0x%lx\n",
	(uदीर्घ)xoff, xlen, (uदीर्घ)xaddr);
*/

	/* there must exist extent to be tailgated */
	अगर ((rc = xtSearch(ip, xoff, शून्य, &cmp, &btstack, XT_INSERT)))
		वापस rc;

	/* retrieve search result */
	XT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

	अगर (cmp != 0) अणु
		XT_PUTPAGE(mp);
		jfs_error(ip->i_sb, "couldn't find extent\n");
		वापस -EIO;
	पूर्ण

	/* entry found must be last entry */
	nextindex = le16_to_cpu(p->header.nextindex);
	अगर (index != nextindex - 1) अणु
		XT_PUTPAGE(mp);
		jfs_error(ip->i_sb, "the entry found is not the last entry\n");
		वापस -EIO;
	पूर्ण

	BT_MARK_सूचीTY(mp, ip);
	/*
	 * acquire tlock of the leaf page containing original entry
	 */
	अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
		tlck = txLock(tid, ip, mp, tlckXTREE | tlckGROW);
		xtlck = (काष्ठा xtlock *) & tlck->lock;
	पूर्ण

	/* completely replace extent ? */
	xad = &p->xad[index];
/*
म_लिखो("xtTailgate: xoff:0x%lx xlen:0x%x xaddr:0x%lx\n",
	(uदीर्घ)offsetXAD(xad), lengthXAD(xad), (uदीर्घ)addressXAD(xad));
*/
	अगर ((llen = xoff - offsetXAD(xad)) == 0)
		जाओ updateOld;

	/*
	 *	partially replace extent: insert entry क्रम new extent
	 */
//insertNew:
	/*
	 *	अगर the leaf page is full, insert the new entry and
	 *	propagate up the router entry क्रम the new page from split
	 *
	 * The xtSplitUp() will insert the entry and unpin the leaf page.
	 */
	अगर (nextindex == le16_to_cpu(p->header.maxentry)) अणु
		/* xtSpliUp() unpins leaf pages */
		split.mp = mp;
		split.index = index + 1;
		split.flag = XAD_NEW;
		split.off = xoff;	/* split offset */
		split.len = xlen;
		split.addr = xaddr;
		split.pxdlist = शून्य;
		अगर ((rc = xtSplitUp(tid, ip, &split, &btstack)))
			वापस rc;

		/* get back old page */
		XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;
		/*
		 * अगर leaf root has been split, original root has been
		 * copied to new child page, i.e., original entry now
		 * resides on the new child page;
		 */
		अगर (p->header.flag & BT_INTERNAL) अणु
			ASSERT(p->header.nextindex ==
			       cpu_to_le16(XTENTRYSTART + 1));
			xad = &p->xad[XTENTRYSTART];
			bn = addressXAD(xad);
			XT_PUTPAGE(mp);

			/* get new child page */
			XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
			अगर (rc)
				वापस rc;

			BT_MARK_सूचीTY(mp, ip);
			अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
				tlck = txLock(tid, ip, mp, tlckXTREE|tlckGROW);
				xtlck = (काष्ठा xtlock *) & tlck->lock;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 *	insert the new entry पूर्णांकo the leaf page
	 */
	अन्यथा अणु
		/* insert the new entry: mark the entry NEW */
		xad = &p->xad[index + 1];
		XT_PUTENTRY(xad, XAD_NEW, xoff, xlen, xaddr);

		/* advance next available entry index */
		le16_add_cpu(&p->header.nextindex, 1);
	पूर्ण

	/* get back old XAD */
	xad = &p->xad[index];

	/*
	 * truncate/relocate old extent at split offset
	 */
      updateOld:
	/* update dmap क्रम old/committed/truncated extent */
	rlen = lengthXAD(xad) - llen;
	अगर (!(xad->flag & XAD_NEW)) अणु
		/* मुक्त from PWMAP at commit */
		अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
			mtlck = txMaplock(tid, ip, tlckMAP);
			pxdlock = (काष्ठा maplock *) & mtlck->lock;
			pxdlock->flag = mlckFREEPXD;
			PXDaddress(&pxdlock->pxd, addressXAD(xad) + llen);
			PXDlength(&pxdlock->pxd, rlen);
			pxdlock->index = 1;
		पूर्ण
	पूर्ण अन्यथा
		/* मुक्त from WMAP */
		dbFree(ip, addressXAD(xad) + llen, (s64) rlen);

	अगर (llen)
		/* truncate */
		XADlength(xad, llen);
	अन्यथा
		/* replace */
		XT_PUTENTRY(xad, XAD_NEW, xoff, xlen, xaddr);

	अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
		xtlck->lwm.offset = (xtlck->lwm.offset) ?
		    min(index, (पूर्णांक)xtlck->lwm.offset) : index;
		xtlck->lwm.length = le16_to_cpu(p->header.nextindex) -
		    xtlck->lwm.offset;
	पूर्ण

	/* unpin the leaf page */
	XT_PUTPAGE(mp);

	वापस rc;
पूर्ण
#पूर्ण_अगर /* _NOTYET */

/*
 *	xtUpdate()
 *
 * function: update XAD;
 *
 *	update extent क्रम allocated_but_not_recorded or
 *	compressed extent;
 *
 * parameter:
 *	nxad	- new XAD;
 *		logical extent of the specअगरied XAD must be completely
 *		contained by an existing XAD;
 */
पूर्णांक xtUpdate(tid_t tid, काष्ठा inode *ip, xad_t * nxad)
अणु				/* new XAD */
	पूर्णांक rc = 0;
	पूर्णांक cmp;
	काष्ठा metapage *mp;	/* meta-page buffer */
	xtpage_t *p;		/* base B+-tree index page */
	s64 bn;
	पूर्णांक index0, index, newindex, nextindex;
	काष्ठा btstack btstack;	/* traverse stack */
	काष्ठा xtsplit split;	/* split inक्रमmation */
	xad_t *xad, *lxad, *rxad;
	पूर्णांक xflag;
	s64 nxoff, xoff;
	पूर्णांक nxlen, xlen, lxlen, rxlen;
	s64 nxaddr, xaddr;
	काष्ठा tlock *tlck;
	काष्ठा xtlock *xtlck = शून्य;
	पूर्णांक newpage = 0;

	/* there must exist extent to be tailgated */
	nxoff = offsetXAD(nxad);
	nxlen = lengthXAD(nxad);
	nxaddr = addressXAD(nxad);

	अगर ((rc = xtSearch(ip, nxoff, शून्य, &cmp, &btstack, XT_INSERT)))
		वापस rc;

	/* retrieve search result */
	XT_GETSEARCH(ip, btstack.top, bn, mp, p, index0);

	अगर (cmp != 0) अणु
		XT_PUTPAGE(mp);
		jfs_error(ip->i_sb, "Could not find extent\n");
		वापस -EIO;
	पूर्ण

	BT_MARK_सूचीTY(mp, ip);
	/*
	 * acquire tlock of the leaf page containing original entry
	 */
	अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
		tlck = txLock(tid, ip, mp, tlckXTREE | tlckGROW);
		xtlck = (काष्ठा xtlock *) & tlck->lock;
	पूर्ण

	xad = &p->xad[index0];
	xflag = xad->flag;
	xoff = offsetXAD(xad);
	xlen = lengthXAD(xad);
	xaddr = addressXAD(xad);

	/* nXAD must be completely contained within XAD */
	अगर ((xoff > nxoff) ||
	    (nxoff + nxlen > xoff + xlen)) अणु
		XT_PUTPAGE(mp);
		jfs_error(ip->i_sb,
			  "nXAD in not completely contained within XAD\n");
		वापस -EIO;
	पूर्ण

	index = index0;
	newindex = index + 1;
	nextindex = le16_to_cpu(p->header.nextindex);

#अगर_घोषित  _JFS_WIP_NOCOALESCE
	अगर (xoff < nxoff)
		जाओ updateRight;

	/*
	 * replace XAD with nXAD
	 */
      replace:			/* (nxoff == xoff) */
	अगर (nxlen == xlen) अणु
		/* replace XAD with nXAD:recorded */
		*xad = *nxad;
		xad->flag = xflag & ~XAD_NOTRECORDED;

		जाओ out;
	पूर्ण अन्यथा			/* (nxlen < xlen) */
		जाओ updateLeft;
#पूर्ण_अगर				/* _JFS_WIP_NOCOALESCE */

/* #अगर_घोषित _JFS_WIP_COALESCE */
	अगर (xoff < nxoff)
		जाओ coalesceRight;

	/*
	 * coalesce with left XAD
	 */
//coalesceLeft: /* (xoff == nxoff) */
	/* is XAD first entry of page ? */
	अगर (index == XTENTRYSTART)
		जाओ replace;

	/* is nXAD logically and physically contiguous with lXAD ? */
	lxad = &p->xad[index - 1];
	lxlen = lengthXAD(lxad);
	अगर (!(lxad->flag & XAD_NOTRECORDED) &&
	    (nxoff == offsetXAD(lxad) + lxlen) &&
	    (nxaddr == addressXAD(lxad) + lxlen) &&
	    (lxlen + nxlen < MAXXLEN)) अणु
		/* extend right lXAD */
		index0 = index - 1;
		XADlength(lxad, lxlen + nxlen);

		/* If we just merged two extents together, need to make sure the
		 * right extent माला_लो logged.  If the left one is marked XAD_NEW,
		 * then we know it will be logged.  Otherwise, mark as
		 * XAD_EXTENDED
		 */
		अगर (!(lxad->flag & XAD_NEW))
			lxad->flag |= XAD_EXTENDED;

		अगर (xlen > nxlen) अणु
			/* truncate XAD */
			XADoffset(xad, xoff + nxlen);
			XADlength(xad, xlen - nxlen);
			XADaddress(xad, xaddr + nxlen);
			जाओ out;
		पूर्ण अन्यथा अणु	/* (xlen == nxlen) */

			/* हटाओ XAD */
			अगर (index < nextindex - 1)
				स_हटाओ(&p->xad[index], &p->xad[index + 1],
					(nextindex - index -
					 1) << L2XTSLOTSIZE);

			p->header.nextindex =
			    cpu_to_le16(le16_to_cpu(p->header.nextindex) -
					1);

			index = index0;
			newindex = index + 1;
			nextindex = le16_to_cpu(p->header.nextindex);
			xoff = nxoff = offsetXAD(lxad);
			xlen = nxlen = lxlen + nxlen;
			xaddr = nxaddr = addressXAD(lxad);
			जाओ coalesceRight;
		पूर्ण
	पूर्ण

	/*
	 * replace XAD with nXAD
	 */
      replace:			/* (nxoff == xoff) */
	अगर (nxlen == xlen) अणु
		/* replace XAD with nXAD:recorded */
		*xad = *nxad;
		xad->flag = xflag & ~XAD_NOTRECORDED;

		जाओ coalesceRight;
	पूर्ण अन्यथा			/* (nxlen < xlen) */
		जाओ updateLeft;

	/*
	 * coalesce with right XAD
	 */
      coalesceRight:		/* (xoff <= nxoff) */
	/* is XAD last entry of page ? */
	अगर (newindex == nextindex) अणु
		अगर (xoff == nxoff)
			जाओ out;
		जाओ updateRight;
	पूर्ण

	/* is nXAD logically and physically contiguous with rXAD ? */
	rxad = &p->xad[index + 1];
	rxlen = lengthXAD(rxad);
	अगर (!(rxad->flag & XAD_NOTRECORDED) &&
	    (nxoff + nxlen == offsetXAD(rxad)) &&
	    (nxaddr + nxlen == addressXAD(rxad)) &&
	    (rxlen + nxlen < MAXXLEN)) अणु
		/* extend left rXAD */
		XADoffset(rxad, nxoff);
		XADlength(rxad, rxlen + nxlen);
		XADaddress(rxad, nxaddr);

		/* If we just merged two extents together, need to make sure
		 * the left extent माला_लो logged.  If the right one is marked
		 * XAD_NEW, then we know it will be logged.  Otherwise, mark as
		 * XAD_EXTENDED
		 */
		अगर (!(rxad->flag & XAD_NEW))
			rxad->flag |= XAD_EXTENDED;

		अगर (xlen > nxlen)
			/* truncate XAD */
			XADlength(xad, xlen - nxlen);
		अन्यथा अणु		/* (xlen == nxlen) */

			/* हटाओ XAD */
			स_हटाओ(&p->xad[index], &p->xad[index + 1],
				(nextindex - index - 1) << L2XTSLOTSIZE);

			p->header.nextindex =
			    cpu_to_le16(le16_to_cpu(p->header.nextindex) -
					1);
		पूर्ण

		जाओ out;
	पूर्ण अन्यथा अगर (xoff == nxoff)
		जाओ out;

	अगर (xoff >= nxoff) अणु
		XT_PUTPAGE(mp);
		jfs_error(ip->i_sb, "xoff >= nxoff\n");
		वापस -EIO;
	पूर्ण
/* #पूर्ण_अगर _JFS_WIP_COALESCE */

	/*
	 * split XAD पूर्णांकo (lXAD, nXAD):
	 *
	 *          |---nXAD--->
	 * --|----------XAD----------|--
	 *   |-lXAD-|
	 */
      updateRight:		/* (xoff < nxoff) */
	/* truncate old XAD as lXAD:not_recorded */
	xad = &p->xad[index];
	XADlength(xad, nxoff - xoff);

	/* insert nXAD:recorded */
	अगर (nextindex == le16_to_cpu(p->header.maxentry)) अणु

		/* xtSpliUp() unpins leaf pages */
		split.mp = mp;
		split.index = newindex;
		split.flag = xflag & ~XAD_NOTRECORDED;
		split.off = nxoff;
		split.len = nxlen;
		split.addr = nxaddr;
		split.pxdlist = शून्य;
		अगर ((rc = xtSplitUp(tid, ip, &split, &btstack)))
			वापस rc;

		/* get back old page */
		XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;
		/*
		 * अगर leaf root has been split, original root has been
		 * copied to new child page, i.e., original entry now
		 * resides on the new child page;
		 */
		अगर (p->header.flag & BT_INTERNAL) अणु
			ASSERT(p->header.nextindex ==
			       cpu_to_le16(XTENTRYSTART + 1));
			xad = &p->xad[XTENTRYSTART];
			bn = addressXAD(xad);
			XT_PUTPAGE(mp);

			/* get new child page */
			XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
			अगर (rc)
				वापस rc;

			BT_MARK_सूचीTY(mp, ip);
			अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
				tlck = txLock(tid, ip, mp, tlckXTREE|tlckGROW);
				xtlck = (काष्ठा xtlock *) & tlck->lock;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* is nXAD on new page ? */
			अगर (newindex >
			    (le16_to_cpu(p->header.maxentry) >> 1)) अणु
				newindex =
				    newindex -
				    le16_to_cpu(p->header.nextindex) +
				    XTENTRYSTART;
				newpage = 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* अगर insert पूर्णांकo middle, shअगरt right reमुख्यing entries */
		अगर (newindex < nextindex)
			स_हटाओ(&p->xad[newindex + 1], &p->xad[newindex],
				(nextindex - newindex) << L2XTSLOTSIZE);

		/* insert the entry */
		xad = &p->xad[newindex];
		*xad = *nxad;
		xad->flag = xflag & ~XAD_NOTRECORDED;

		/* advance next available entry index. */
		p->header.nextindex =
		    cpu_to_le16(le16_to_cpu(p->header.nextindex) + 1);
	पूर्ण

	/*
	 * करोes nXAD क्रमce 3-way split ?
	 *
	 *          |---nXAD--->|
	 * --|----------XAD-------------|--
	 *   |-lXAD-|           |-rXAD -|
	 */
	अगर (nxoff + nxlen == xoff + xlen)
		जाओ out;

	/* reorient nXAD as XAD क्रम further split XAD पूर्णांकo (nXAD, rXAD) */
	अगर (newpage) अणु
		/* बंद out old page */
		अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
			xtlck->lwm.offset = (xtlck->lwm.offset) ?
			    min(index0, (पूर्णांक)xtlck->lwm.offset) : index0;
			xtlck->lwm.length =
			    le16_to_cpu(p->header.nextindex) -
			    xtlck->lwm.offset;
		पूर्ण

		bn = le64_to_cpu(p->header.next);
		XT_PUTPAGE(mp);

		/* get new right page */
		XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;

		BT_MARK_सूचीTY(mp, ip);
		अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
			tlck = txLock(tid, ip, mp, tlckXTREE | tlckGROW);
			xtlck = (काष्ठा xtlock *) & tlck->lock;
		पूर्ण

		index0 = index = newindex;
	पूर्ण अन्यथा
		index++;

	newindex = index + 1;
	nextindex = le16_to_cpu(p->header.nextindex);
	xlen = xlen - (nxoff - xoff);
	xoff = nxoff;
	xaddr = nxaddr;

	/* recompute split pages */
	अगर (nextindex == le16_to_cpu(p->header.maxentry)) अणु
		XT_PUTPAGE(mp);

		अगर ((rc = xtSearch(ip, nxoff, शून्य, &cmp, &btstack, XT_INSERT)))
			वापस rc;

		/* retrieve search result */
		XT_GETSEARCH(ip, btstack.top, bn, mp, p, index0);

		अगर (cmp != 0) अणु
			XT_PUTPAGE(mp);
			jfs_error(ip->i_sb, "xtSearch failed\n");
			वापस -EIO;
		पूर्ण

		अगर (index0 != index) अणु
			XT_PUTPAGE(mp);
			jfs_error(ip->i_sb, "unexpected value of index\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	/*
	 * split XAD पूर्णांकo (nXAD, rXAD)
	 *
	 *          ---nXAD---|
	 * --|----------XAD----------|--
	 *                    |-rXAD-|
	 */
      updateLeft:		/* (nxoff == xoff) && (nxlen < xlen) */
	/* update old XAD with nXAD:recorded */
	xad = &p->xad[index];
	*xad = *nxad;
	xad->flag = xflag & ~XAD_NOTRECORDED;

	/* insert rXAD:not_recorded */
	xoff = xoff + nxlen;
	xlen = xlen - nxlen;
	xaddr = xaddr + nxlen;
	अगर (nextindex == le16_to_cpu(p->header.maxentry)) अणु
/*
म_लिखो("xtUpdate.updateLeft.split p:0x%p\n", p);
*/
		/* xtSpliUp() unpins leaf pages */
		split.mp = mp;
		split.index = newindex;
		split.flag = xflag;
		split.off = xoff;
		split.len = xlen;
		split.addr = xaddr;
		split.pxdlist = शून्य;
		अगर ((rc = xtSplitUp(tid, ip, &split, &btstack)))
			वापस rc;

		/* get back old page */
		XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;

		/*
		 * अगर leaf root has been split, original root has been
		 * copied to new child page, i.e., original entry now
		 * resides on the new child page;
		 */
		अगर (p->header.flag & BT_INTERNAL) अणु
			ASSERT(p->header.nextindex ==
			       cpu_to_le16(XTENTRYSTART + 1));
			xad = &p->xad[XTENTRYSTART];
			bn = addressXAD(xad);
			XT_PUTPAGE(mp);

			/* get new child page */
			XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
			अगर (rc)
				वापस rc;

			BT_MARK_सूचीTY(mp, ip);
			अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
				tlck = txLock(tid, ip, mp, tlckXTREE|tlckGROW);
				xtlck = (काष्ठा xtlock *) & tlck->lock;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* अगर insert पूर्णांकo middle, shअगरt right reमुख्यing entries */
		अगर (newindex < nextindex)
			स_हटाओ(&p->xad[newindex + 1], &p->xad[newindex],
				(nextindex - newindex) << L2XTSLOTSIZE);

		/* insert the entry */
		xad = &p->xad[newindex];
		XT_PUTENTRY(xad, xflag, xoff, xlen, xaddr);

		/* advance next available entry index. */
		p->header.nextindex =
		    cpu_to_le16(le16_to_cpu(p->header.nextindex) + 1);
	पूर्ण

      out:
	अगर (!test_cflag(COMMIT_Nolink, ip)) अणु
		xtlck->lwm.offset = (xtlck->lwm.offset) ?
		    min(index0, (पूर्णांक)xtlck->lwm.offset) : index0;
		xtlck->lwm.length = le16_to_cpu(p->header.nextindex) -
		    xtlck->lwm.offset;
	पूर्ण

	/* unpin the leaf page */
	XT_PUTPAGE(mp);

	वापस rc;
पूर्ण


/*
 *	xtAppend()
 *
 * function: grow in append mode from contiguous region specअगरied ;
 *
 * parameter:
 *	tid		- transaction id;
 *	ip		- file object;
 *	xflag		- extent flag:
 *	xoff		- extent offset;
 *	maxblocks	- max extent length;
 *	xlen		- extent length (in/out);
 *	xaddrp		- extent address poपूर्णांकer (in/out):
 *	flag		-
 *
 * वापस:
 */
पूर्णांक xtAppend(tid_t tid,		/* transaction id */
	     काष्ठा inode *ip, पूर्णांक xflag, s64 xoff, s32 maxblocks,
	     s32 * xlenp,	/* (in/out) */
	     s64 * xaddrp,	/* (in/out) */
	     पूर्णांक flag)
अणु
	पूर्णांक rc = 0;
	काष्ठा metapage *mp;	/* meta-page buffer */
	xtpage_t *p;		/* base B+-tree index page */
	s64 bn, xaddr;
	पूर्णांक index, nextindex;
	काष्ठा btstack btstack;	/* traverse stack */
	काष्ठा xtsplit split;	/* split inक्रमmation */
	xad_t *xad;
	पूर्णांक cmp;
	काष्ठा tlock *tlck;
	काष्ठा xtlock *xtlck;
	पूर्णांक nsplit, nblocks, xlen;
	काष्ठा pxdlist pxdlist;
	pxd_t *pxd;
	s64 next;

	xaddr = *xaddrp;
	xlen = *xlenp;
	jfs_info("xtAppend: xoff:0x%lx maxblocks:%d xlen:%d xaddr:0x%lx",
		 (uदीर्घ) xoff, maxblocks, xlen, (uदीर्घ) xaddr);

	/*
	 *	search क्रम the entry location at which to insert:
	 *
	 * xtFastSearch() and xtSearch() both वापसs (leaf page
	 * pinned, index at which to insert).
	 * n.b. xtSearch() may वापस index of maxentry of
	 * the full page.
	 */
	अगर ((rc = xtSearch(ip, xoff, &next, &cmp, &btstack, XT_INSERT)))
		वापस rc;

	/* retrieve search result */
	XT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

	अगर (cmp == 0) अणु
		rc = -EEXIST;
		जाओ out;
	पूर्ण

	अगर (next)
		xlen = min(xlen, (पूर्णांक)(next - xoff));
//insert:
	/*
	 *	insert entry क्रम new extent
	 */
	xflag |= XAD_NEW;

	/*
	 *	अगर the leaf page is full, split the page and
	 *	propagate up the router entry क्रम the new page from split
	 *
	 * The xtSplitUp() will insert the entry and unpin the leaf page.
	 */
	nextindex = le16_to_cpu(p->header.nextindex);
	अगर (nextindex < le16_to_cpu(p->header.maxentry))
		जाओ insertLeaf;

	/*
	 * allocate new index blocks to cover index page split(s)
	 */
	nsplit = btstack.nsplit;
	split.pxdlist = &pxdlist;
	pxdlist.maxnpxd = pxdlist.npxd = 0;
	pxd = &pxdlist.pxd[0];
	nblocks = JFS_SBI(ip->i_sb)->nbperpage;
	क्रम (; nsplit > 0; nsplit--, pxd++, xaddr += nblocks, maxblocks -= nblocks) अणु
		अगर ((rc = dbAllocBottomUp(ip, xaddr, (s64) nblocks)) == 0) अणु
			PXDaddress(pxd, xaddr);
			PXDlength(pxd, nblocks);

			pxdlist.maxnpxd++;

			जारी;
		पूर्ण

		/* unकरो allocation */

		जाओ out;
	पूर्ण

	xlen = min(xlen, maxblocks);

	/*
	 * allocate data extent requested
	 */
	अगर ((rc = dbAllocBottomUp(ip, xaddr, (s64) xlen)))
		जाओ out;

	split.mp = mp;
	split.index = index;
	split.flag = xflag;
	split.off = xoff;
	split.len = xlen;
	split.addr = xaddr;
	अगर ((rc = xtSplitUp(tid, ip, &split, &btstack))) अणु
		/* unकरो data extent allocation */
		dbFree(ip, *xaddrp, (s64) * xlenp);

		वापस rc;
	पूर्ण

	*xaddrp = xaddr;
	*xlenp = xlen;
	वापस 0;

	/*
	 *	insert the new entry पूर्णांकo the leaf page
	 */
      insertLeaf:
	/*
	 * allocate data extent requested
	 */
	अगर ((rc = dbAllocBottomUp(ip, xaddr, (s64) xlen)))
		जाओ out;

	BT_MARK_सूचीTY(mp, ip);
	/*
	 * acquire a transaction lock on the leaf page;
	 *
	 * action: xad insertion/extension;
	 */
	tlck = txLock(tid, ip, mp, tlckXTREE | tlckGROW);
	xtlck = (काष्ठा xtlock *) & tlck->lock;

	/* insert the new entry: mark the entry NEW */
	xad = &p->xad[index];
	XT_PUTENTRY(xad, xflag, xoff, xlen, xaddr);

	/* advance next available entry index */
	le16_add_cpu(&p->header.nextindex, 1);

	xtlck->lwm.offset =
	    (xtlck->lwm.offset) ? min(index,(पूर्णांक) xtlck->lwm.offset) : index;
	xtlck->lwm.length = le16_to_cpu(p->header.nextindex) -
	    xtlck->lwm.offset;

	*xaddrp = xaddr;
	*xlenp = xlen;

      out:
	/* unpin the leaf page */
	XT_PUTPAGE(mp);

	वापस rc;
पूर्ण
#अगर_घोषित _STILL_TO_PORT

/* - TBD क्रम defragmentaion/reorganization -
 *
 *	xtDelete()
 *
 * function:
 *	delete the entry with the specअगरied key.
 *
 *	N.B.: whole extent of the entry is assumed to be deleted.
 *
 * parameter:
 *
 * वापस:
 *	ENOENT: अगर the entry is not found.
 *
 * exception:
 */
पूर्णांक xtDelete(tid_t tid, काष्ठा inode *ip, s64 xoff, s32 xlen, पूर्णांक flag)
अणु
	पूर्णांक rc = 0;
	काष्ठा btstack btstack;
	पूर्णांक cmp;
	s64 bn;
	काष्ठा metapage *mp;
	xtpage_t *p;
	पूर्णांक index, nextindex;
	काष्ठा tlock *tlck;
	काष्ठा xtlock *xtlck;

	/*
	 * find the matching entry; xtSearch() pins the page
	 */
	अगर ((rc = xtSearch(ip, xoff, शून्य, &cmp, &btstack, 0)))
		वापस rc;

	XT_GETSEARCH(ip, btstack.top, bn, mp, p, index);
	अगर (cmp) अणु
		/* unpin the leaf page */
		XT_PUTPAGE(mp);
		वापस -ENOENT;
	पूर्ण

	/*
	 * delete the entry from the leaf page
	 */
	nextindex = le16_to_cpu(p->header.nextindex);
	le16_add_cpu(&p->header.nextindex, -1);

	/*
	 * अगर the leaf page bocome empty, मुक्त the page
	 */
	अगर (p->header.nextindex == cpu_to_le16(XTENTRYSTART))
		वापस (xtDeleteUp(tid, ip, mp, p, &btstack));

	BT_MARK_सूचीTY(mp, ip);
	/*
	 * acquire a transaction lock on the leaf page;
	 *
	 * action:xad deletion;
	 */
	tlck = txLock(tid, ip, mp, tlckXTREE);
	xtlck = (काष्ठा xtlock *) & tlck->lock;
	xtlck->lwm.offset =
	    (xtlck->lwm.offset) ? min(index, xtlck->lwm.offset) : index;

	/* अगर delete from middle, shअगरt left/compact the reमुख्यing entries */
	अगर (index < nextindex - 1)
		स_हटाओ(&p->xad[index], &p->xad[index + 1],
			(nextindex - index - 1) * माप(xad_t));

	XT_PUTPAGE(mp);

	वापस 0;
पूर्ण


/* - TBD क्रम defragmentaion/reorganization -
 *
 *	xtDeleteUp()
 *
 * function:
 *	मुक्त empty pages as propagating deletion up the tree
 *
 * parameter:
 *
 * वापस:
 */
अटल पूर्णांक
xtDeleteUp(tid_t tid, काष्ठा inode *ip,
	   काष्ठा metapage * fmp, xtpage_t * fp, काष्ठा btstack * btstack)
अणु
	पूर्णांक rc = 0;
	काष्ठा metapage *mp;
	xtpage_t *p;
	पूर्णांक index, nextindex;
	s64 xaddr;
	पूर्णांक xlen;
	काष्ठा btframe *parent;
	काष्ठा tlock *tlck;
	काष्ठा xtlock *xtlck;

	/*
	 * keep root leaf page which has become empty
	 */
	अगर (fp->header.flag & BT_ROOT) अणु
		/* keep the root page */
		fp->header.flag &= ~BT_INTERNAL;
		fp->header.flag |= BT_LEAF;
		fp->header.nextindex = cpu_to_le16(XTENTRYSTART);

		/* XT_PUTPAGE(fmp); */

		वापस 0;
	पूर्ण

	/*
	 * मुक्त non-root leaf page
	 */
	अगर ((rc = xtRelink(tid, ip, fp))) अणु
		XT_PUTPAGE(fmp);
		वापस rc;
	पूर्ण

	xaddr = addressPXD(&fp->header.self);
	xlen = lengthPXD(&fp->header.self);
	/* मुक्त the page extent */
	dbFree(ip, xaddr, (s64) xlen);

	/* मुक्त the buffer page */
	discard_metapage(fmp);

	/*
	 * propagate page deletion up the index tree
	 *
	 * If the delete from the parent page makes it empty,
	 * जारी all the way up the tree.
	 * stop अगर the root page is reached (which is never deleted) or
	 * अगर the entry deletion करोes not empty the page.
	 */
	जबतक ((parent = BT_POP(btstack)) != शून्य) अणु
		/* get/pin the parent page <sp> */
		XT_GETPAGE(ip, parent->bn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;

		index = parent->index;

		/* delete the entry क्रम the मुक्तd child page from parent.
		 */
		nextindex = le16_to_cpu(p->header.nextindex);

		/*
		 * the parent has the single entry being deleted:
		 * मुक्त the parent page which has become empty.
		 */
		अगर (nextindex == 1) अणु
			अगर (p->header.flag & BT_ROOT) अणु
				/* keep the root page */
				p->header.flag &= ~BT_INTERNAL;
				p->header.flag |= BT_LEAF;
				p->header.nextindex =
				    cpu_to_le16(XTENTRYSTART);

				/* XT_PUTPAGE(mp); */

				अवरोध;
			पूर्ण अन्यथा अणु
				/* मुक्त the parent page */
				अगर ((rc = xtRelink(tid, ip, p)))
					वापस rc;

				xaddr = addressPXD(&p->header.self);
				/* मुक्त the page extent */
				dbFree(ip, xaddr,
				       (s64) JFS_SBI(ip->i_sb)->nbperpage);

				/* unpin/मुक्त the buffer page */
				discard_metapage(mp);

				/* propagate up */
				जारी;
			पूर्ण
		पूर्ण
		/*
		 * the parent has other entries reमुख्यing:
		 * delete the router entry from the parent page.
		 */
		अन्यथा अणु
			BT_MARK_सूचीTY(mp, ip);
			/*
			 * acquire a transaction lock on the leaf page;
			 *
			 * action:xad deletion;
			 */
			tlck = txLock(tid, ip, mp, tlckXTREE);
			xtlck = (काष्ठा xtlock *) & tlck->lock;
			xtlck->lwm.offset =
			    (xtlck->lwm.offset) ? min(index,
						      xtlck->lwm.
						      offset) : index;

			/* अगर delete from middle,
			 * shअगरt left/compact the reमुख्यing entries in the page
			 */
			अगर (index < nextindex - 1)
				स_हटाओ(&p->xad[index], &p->xad[index + 1],
					(nextindex - index -
					 1) << L2XTSLOTSIZE);

			le16_add_cpu(&p->header.nextindex, -1);
			jfs_info("xtDeleteUp(entry): 0x%lx[%d]",
				 (uदीर्घ) parent->bn, index);
		पूर्ण

		/* unpin the parent page */
		XT_PUTPAGE(mp);

		/* निकास propagation up */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * NAME:	xtRelocate()
 *
 * FUNCTION:	relocate xtpage or data extent of regular file;
 *		This function is मुख्यly used by defragfs utility.
 *
 * NOTE:	This routine करोes not have the logic to handle
 *		uncommitted allocated extent. The caller should call
 *		txCommit() to commit all the allocation beक्रमe call
 *		this routine.
 */
पूर्णांक
xtRelocate(tid_t tid, काष्ठा inode * ip, xad_t * oxad,	/* old XAD */
	   s64 nxaddr,		/* new xaddr */
	   पूर्णांक xtype)
अणु				/* extent type: XTPAGE or DATAEXT */
	पूर्णांक rc = 0;
	काष्ठा tblock *tblk;
	काष्ठा tlock *tlck;
	काष्ठा xtlock *xtlck;
	काष्ठा metapage *mp, *pmp, *lmp, *rmp;	/* meta-page buffer */
	xtpage_t *p, *pp, *rp, *lp;	/* base B+-tree index page */
	xad_t *xad;
	pxd_t *pxd;
	s64 xoff, xsize;
	पूर्णांक xlen;
	s64 oxaddr, sxaddr, dxaddr, nextbn, prevbn;
	cbuf_t *cp;
	s64 offset, nbytes, nbrd, pno;
	पूर्णांक nb, npages, nblks;
	s64 bn;
	पूर्णांक cmp;
	पूर्णांक index;
	काष्ठा pxd_lock *pxdlock;
	काष्ठा btstack btstack;	/* traverse stack */

	xtype = xtype & EXTENT_TYPE;

	xoff = offsetXAD(oxad);
	oxaddr = addressXAD(oxad);
	xlen = lengthXAD(oxad);

	/* validate extent offset */
	offset = xoff << JFS_SBI(ip->i_sb)->l2bsize;
	अगर (offset >= ip->i_size)
		वापस -ESTALE;	/* stale extent */

	jfs_info("xtRelocate: xtype:%d xoff:0x%lx xlen:0x%x xaddr:0x%lx:0x%lx",
		 xtype, (uदीर्घ) xoff, xlen, (uदीर्घ) oxaddr, (uदीर्घ) nxaddr);

	/*
	 *	1. get and validate the parent xtpage/xad entry
	 *	covering the source extent to be relocated;
	 */
	अगर (xtype == DATAEXT) अणु
		/* search in leaf entry */
		rc = xtSearch(ip, xoff, शून्य, &cmp, &btstack, 0);
		अगर (rc)
			वापस rc;

		/* retrieve search result */
		XT_GETSEARCH(ip, btstack.top, bn, pmp, pp, index);

		अगर (cmp) अणु
			XT_PUTPAGE(pmp);
			वापस -ESTALE;
		पूर्ण

		/* validate क्रम exact match with a single entry */
		xad = &pp->xad[index];
		अगर (addressXAD(xad) != oxaddr || lengthXAD(xad) != xlen) अणु
			XT_PUTPAGE(pmp);
			वापस -ESTALE;
		पूर्ण
	पूर्ण अन्यथा अणु		/* (xtype == XTPAGE) */

		/* search in पूर्णांकernal entry */
		rc = xtSearchNode(ip, oxad, &cmp, &btstack, 0);
		अगर (rc)
			वापस rc;

		/* retrieve search result */
		XT_GETSEARCH(ip, btstack.top, bn, pmp, pp, index);

		अगर (cmp) अणु
			XT_PUTPAGE(pmp);
			वापस -ESTALE;
		पूर्ण

		/* xtSearchNode() validated क्रम exact match with a single entry
		 */
		xad = &pp->xad[index];
	पूर्ण
	jfs_info("xtRelocate: parent xad entry validated.");

	/*
	 *	2. relocate the extent
	 */
	अगर (xtype == DATAEXT) अणु
		/* अगर the extent is allocated-but-not-recorded
		 * there is no real data to be moved in this extent,
		 */
		अगर (xad->flag & XAD_NOTRECORDED)
			जाओ out;
		अन्यथा
			/* release xtpage क्रम cmRead()/xtLookup() */
			XT_PUTPAGE(pmp);

		/*
		 *	cmRelocate()
		 *
		 * copy target data pages to be relocated;
		 *
		 * data extent must start at page boundary and
		 * multiple of page size (except the last data extent);
		 * पढ़ो in each page of the source data extent पूर्णांकo cbuf,
		 * update the cbuf extent descriptor of the page to be
		 * homeward bound to new dst data extent
		 * copy the data from the old extent to new extent.
		 * copy is essential क्रम compressed files to aव्योम problems
		 * that can arise अगर there was a change in compression
		 * algorithms.
		 * it is a good strategy because it may disrupt cache
		 * policy to keep the pages in memory afterwards.
		 */
		offset = xoff << JFS_SBI(ip->i_sb)->l2bsize;
		निश्चित((offset & CM_OFFSET) == 0);
		nbytes = xlen << JFS_SBI(ip->i_sb)->l2bsize;
		pno = offset >> CM_L2BSIZE;
		npages = (nbytes + (CM_BSIZE - 1)) >> CM_L2BSIZE;
/*
		npages = ((offset + nbytes - 1) >> CM_L2BSIZE) -
			  (offset >> CM_L2BSIZE) + 1;
*/
		sxaddr = oxaddr;
		dxaddr = nxaddr;

		/* process the request one cache buffer at a समय */
		क्रम (nbrd = 0; nbrd < nbytes; nbrd += nb,
		     offset += nb, pno++, npages--) अणु
			/* compute page size */
			nb = min(nbytes - nbrd, CM_BSIZE);

			/* get the cache buffer of the page */
			अगर (rc = cmRead(ip, offset, npages, &cp))
				अवरोध;

			निश्चित(addressPXD(&cp->cm_pxd) == sxaddr);
			निश्चित(!cp->cm_modअगरied);

			/* bind buffer with the new extent address */
			nblks = nb >> JFS_IP(ip->i_sb)->l2bsize;
			cmSetXD(ip, cp, pno, dxaddr, nblks);

			/* release the cbuf, mark it as modअगरied */
			cmPut(cp, true);

			dxaddr += nblks;
			sxaddr += nblks;
		पूर्ण

		/* get back parent page */
		अगर ((rc = xtSearch(ip, xoff, शून्य, &cmp, &btstack, 0)))
			वापस rc;

		XT_GETSEARCH(ip, btstack.top, bn, pmp, pp, index);
		jfs_info("xtRelocate: target data extent relocated.");
	पूर्ण अन्यथा अणु		/* (xtype == XTPAGE) */

		/*
		 * पढ़ो in the target xtpage from the source extent;
		 */
		XT_GETPAGE(ip, oxaddr, mp, PSIZE, p, rc);
		अगर (rc) अणु
			XT_PUTPAGE(pmp);
			वापस rc;
		पूर्ण

		/*
		 * पढ़ो in sibling pages अगर any to update sibling poपूर्णांकers;
		 */
		rmp = शून्य;
		अगर (p->header.next) अणु
			nextbn = le64_to_cpu(p->header.next);
			XT_GETPAGE(ip, nextbn, rmp, PSIZE, rp, rc);
			अगर (rc) अणु
				XT_PUTPAGE(pmp);
				XT_PUTPAGE(mp);
				वापस (rc);
			पूर्ण
		पूर्ण

		lmp = शून्य;
		अगर (p->header.prev) अणु
			prevbn = le64_to_cpu(p->header.prev);
			XT_GETPAGE(ip, prevbn, lmp, PSIZE, lp, rc);
			अगर (rc) अणु
				XT_PUTPAGE(pmp);
				XT_PUTPAGE(mp);
				अगर (rmp)
					XT_PUTPAGE(rmp);
				वापस (rc);
			पूर्ण
		पूर्ण

		/* at this poपूर्णांक, all xtpages to be updated are in memory */

		/*
		 * update sibling poपूर्णांकers of sibling xtpages अगर any;
		 */
		अगर (lmp) अणु
			BT_MARK_सूचीTY(lmp, ip);
			tlck = txLock(tid, ip, lmp, tlckXTREE | tlckRELINK);
			lp->header.next = cpu_to_le64(nxaddr);
			XT_PUTPAGE(lmp);
		पूर्ण

		अगर (rmp) अणु
			BT_MARK_सूचीTY(rmp, ip);
			tlck = txLock(tid, ip, rmp, tlckXTREE | tlckRELINK);
			rp->header.prev = cpu_to_le64(nxaddr);
			XT_PUTPAGE(rmp);
		पूर्ण

		/*
		 * update the target xtpage to be relocated
		 *
		 * update the self address of the target page
		 * and ग_लिखो to destination extent;
		 * reकरो image covers the whole xtpage since it is new page
		 * to the destination extent;
		 * update of bmap क्रम the मुक्त of source extent
		 * of the target xtpage itself:
		 * update of bmap क्रम the allocation of destination extent
		 * of the target xtpage itself:
		 * update of bmap क्रम the extents covered by xad entries in
		 * the target xtpage is not necessary since they are not
		 * updated;
		 * अगर not committed beक्रमe this relocation,
		 * target page may contain XAD_NEW entries which must
		 * be scanned क्रम bmap update (logreकरो() always
		 * scan xtpage REDOPAGE image क्रम bmap update);
		 * अगर committed beक्रमe this relocation (tlckRELOCATE),
		 * scan may be skipped by commit() and logreकरो();
		 */
		BT_MARK_सूचीTY(mp, ip);
		/* tlckNEW init xtlck->lwm.offset = XTENTRYSTART; */
		tlck = txLock(tid, ip, mp, tlckXTREE | tlckNEW);
		xtlck = (काष्ठा xtlock *) & tlck->lock;

		/* update the self address in the xtpage header */
		pxd = &p->header.self;
		PXDaddress(pxd, nxaddr);

		/* linelock क्रम the after image of the whole page */
		xtlck->lwm.length =
		    le16_to_cpu(p->header.nextindex) - xtlck->lwm.offset;

		/* update the buffer extent descriptor of target xtpage */
		xsize = xlen << JFS_SBI(ip->i_sb)->l2bsize;
		bmSetXD(mp, nxaddr, xsize);

		/* unpin the target page to new homeward bound */
		XT_PUTPAGE(mp);
		jfs_info("xtRelocate: target xtpage relocated.");
	पूर्ण

	/*
	 *	3. acquire maplock क्रम the source extent to be मुक्तd;
	 *
	 * acquire a maplock saving the src relocated extent address;
	 * to मुक्त of the extent at commit समय;
	 */
      out:
	/* अगर DATAEXT relocation, ग_लिखो a LOG_UPDATEMAP record क्रम
	 * मुक्त PXD of the source data extent (logreकरो() will update
	 * bmap क्रम मुक्त of source data extent), and update bmap क्रम
	 * मुक्त of the source data extent;
	 */
	अगर (xtype == DATAEXT)
		tlck = txMaplock(tid, ip, tlckMAP);
	/* अगर XTPAGE relocation, ग_लिखो a LOG_NOREDOPAGE record
	 * क्रम the source xtpage (logreकरो() will init NoReकरोPage
	 * filter and will also update bmap क्रम मुक्त of the source
	 * xtpage), and update bmap क्रम मुक्त of the source xtpage;
	 * N.B. We use tlckMAP instead of tlkcXTREE because there
	 *      is no buffer associated with this lock since the buffer
	 *      has been redirected to the target location.
	 */
	अन्यथा			/* (xtype == XTPAGE) */
		tlck = txMaplock(tid, ip, tlckMAP | tlckRELOCATE);

	pxdlock = (काष्ठा pxd_lock *) & tlck->lock;
	pxdlock->flag = mlckFREEPXD;
	PXDaddress(&pxdlock->pxd, oxaddr);
	PXDlength(&pxdlock->pxd, xlen);
	pxdlock->index = 1;

	/*
	 *	4. update the parent xad entry क्रम relocation;
	 *
	 * acquire tlck क्रम the parent entry with XAD_NEW as entry
	 * update which will ग_लिखो LOG_REDOPAGE and update bmap क्रम
	 * allocation of XAD_NEW destination extent;
	 */
	jfs_info("xtRelocate: update parent xad entry.");
	BT_MARK_सूचीTY(pmp, ip);
	tlck = txLock(tid, ip, pmp, tlckXTREE | tlckGROW);
	xtlck = (काष्ठा xtlock *) & tlck->lock;

	/* update the XAD with the new destination extent; */
	xad = &pp->xad[index];
	xad->flag |= XAD_NEW;
	XADaddress(xad, nxaddr);

	xtlck->lwm.offset = min(index, xtlck->lwm.offset);
	xtlck->lwm.length = le16_to_cpu(pp->header.nextindex) -
	    xtlck->lwm.offset;

	/* unpin the parent xtpage */
	XT_PUTPAGE(pmp);

	वापस rc;
पूर्ण


/*
 *	xtSearchNode()
 *
 * function:	search क्रम the पूर्णांकernal xad entry covering specअगरied extent.
 *		This function is मुख्यly used by defragfs utility.
 *
 * parameters:
 *	ip	- file object;
 *	xad	- extent to find;
 *	cmpp	- comparison result:
 *	btstack - traverse stack;
 *	flag	- search process flag;
 *
 * वापसs:
 *	btstack contains (bn, index) of search path traversed to the entry.
 *	*cmpp is set to result of comparison with the entry वापसed.
 *	the page containing the entry is pinned at निकास.
 */
अटल पूर्णांक xtSearchNode(काष्ठा inode *ip, xad_t * xad,	/* required XAD entry */
			पूर्णांक *cmpp, काष्ठा btstack * btstack, पूर्णांक flag)
अणु
	पूर्णांक rc = 0;
	s64 xoff, xaddr;
	पूर्णांक xlen;
	पूर्णांक cmp = 1;		/* init क्रम empty page */
	s64 bn;			/* block number */
	काष्ठा metapage *mp;	/* meta-page buffer */
	xtpage_t *p;		/* page */
	पूर्णांक base, index, lim;
	काष्ठा btframe *btsp;
	s64 t64;

	BT_CLR(btstack);

	xoff = offsetXAD(xad);
	xlen = lengthXAD(xad);
	xaddr = addressXAD(xad);

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
		XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;
		अगर (p->header.flag & BT_LEAF) अणु
			XT_PUTPAGE(mp);
			वापस -ESTALE;
		पूर्ण

		lim = le16_to_cpu(p->header.nextindex) - XTENTRYSTART;

		/*
		 * binary search with search key K on the current page
		 */
		क्रम (base = XTENTRYSTART; lim; lim >>= 1) अणु
			index = base + (lim >> 1);

			XT_CMP(cmp, xoff, &p->xad[index], t64);
			अगर (cmp == 0) अणु
				/*
				 *	search hit
				 *
				 * verअगरy क्रम exact match;
				 */
				अगर (xaddr == addressXAD(&p->xad[index]) &&
				    xoff == offsetXAD(&p->xad[index])) अणु
					*cmpp = cmp;

					/* save search result */
					btsp = btstack->top;
					btsp->bn = bn;
					btsp->index = index;
					btsp->mp = mp;

					वापस 0;
				पूर्ण

				/* descend/search its child page */
				जाओ next;
			पूर्ण

			अगर (cmp > 0) अणु
				base = index + 1;
				--lim;
			पूर्ण
		पूर्ण

		/*
		 *	search miss - non-leaf page:
		 *
		 * base is the smallest index with key (Kj) greater than
		 * search key (K) and may be zero or maxentry index.
		 * अगर base is non-zero, decrement base by one to get the parent
		 * entry of the child page to search.
		 */
		index = base ? base - 1 : base;

		/*
		 * go करोwn to child page
		 */
	      next:
		/* get the child page block number */
		bn = addressXAD(&p->xad[index]);

		/* unpin the parent page */
		XT_PUTPAGE(mp);
	पूर्ण
पूर्ण


/*
 *	xtRelink()
 *
 * function:
 *	link around a मुक्तd page.
 *
 * Parameter:
 *	पूर्णांक		tid,
 *	काष्ठा inode	*ip,
 *	xtpage_t	*p)
 *
 * वापसs:
 */
अटल पूर्णांक xtRelink(tid_t tid, काष्ठा inode *ip, xtpage_t * p)
अणु
	पूर्णांक rc = 0;
	काष्ठा metapage *mp;
	s64 nextbn, prevbn;
	काष्ठा tlock *tlck;

	nextbn = le64_to_cpu(p->header.next);
	prevbn = le64_to_cpu(p->header.prev);

	/* update prev poपूर्णांकer of the next page */
	अगर (nextbn != 0) अणु
		XT_GETPAGE(ip, nextbn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;

		/*
		 * acquire a transaction lock on the page;
		 *
		 * action: update prev poपूर्णांकer;
		 */
		BT_MARK_सूचीTY(mp, ip);
		tlck = txLock(tid, ip, mp, tlckXTREE | tlckRELINK);

		/* the page may alपढ़ोy have been tlock'd */

		p->header.prev = cpu_to_le64(prevbn);

		XT_PUTPAGE(mp);
	पूर्ण

	/* update next poपूर्णांकer of the previous page */
	अगर (prevbn != 0) अणु
		XT_GETPAGE(ip, prevbn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;

		/*
		 * acquire a transaction lock on the page;
		 *
		 * action: update next poपूर्णांकer;
		 */
		BT_MARK_सूचीTY(mp, ip);
		tlck = txLock(tid, ip, mp, tlckXTREE | tlckRELINK);

		/* the page may alपढ़ोy have been tlock'd */

		p->header.next = le64_to_cpu(nextbn);

		XT_PUTPAGE(mp);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर				/*  _STILL_TO_PORT */


/*
 *	xtInitRoot()
 *
 * initialize file root (अंतरभूत in inode)
 */
व्योम xtInitRoot(tid_t tid, काष्ठा inode *ip)
अणु
	xtpage_t *p;

	/*
	 * acquire a transaction lock on the root
	 *
	 * action:
	 */
	txLock(tid, ip, (काष्ठा metapage *) &JFS_IP(ip)->bxflag,
		      tlckXTREE | tlckNEW);
	p = &JFS_IP(ip)->i_xtroot;

	p->header.flag = DXD_INDEX | BT_ROOT | BT_LEAF;
	p->header.nextindex = cpu_to_le16(XTENTRYSTART);

	अगर (S_ISसूची(ip->i_mode))
		p->header.maxentry = cpu_to_le16(XTROOTINITSLOT_सूची);
	अन्यथा अणु
		p->header.maxentry = cpu_to_le16(XTROOTINITSLOT);
		ip->i_size = 0;
	पूर्ण


	वापस;
पूर्ण


/*
 * We can run पूर्णांकo a deadlock truncating a file with a large number of
 * xtree pages (large fragmented file).  A robust fix would entail a
 * reservation प्रणाली where we would reserve a number of metadata pages
 * and tlocks which we would be guaranteed without a deadlock.  Without
 * this, a partial fix is to limit number of metadata pages we will lock
 * in a single transaction.  Currently we will truncate the file so that
 * no more than 50 leaf pages will be locked.  The caller of xtTruncate
 * will be responsible क्रम ensuring that the current transaction माला_लो
 * committed, and that subsequent transactions are created to truncate
 * the file further अगर needed.
 */
#घोषणा MAX_TRUNCATE_LEAVES 50

/*
 *	xtTruncate()
 *
 * function:
 *	traverse क्रम truncation logging backward bottom up;
 *	terminate at the last extent entry at the current subtree
 *	root page covering new करोwn size.
 *	truncation may occur within the last extent entry.
 *
 * parameter:
 *	पूर्णांक		tid,
 *	काष्ठा inode	*ip,
 *	s64		newsize,
 *	पूर्णांक		type)	अणुPWMAP, PMAP, WMAP; DELETE, TRUNCATEपूर्ण
 *
 * वापस:
 *
 * note:
 *	PWMAP:
 *	 1. truncate (non-COMMIT_NOLINK file)
 *	    by jfs_truncate() or jfs_खोलो(O_TRUNC):
 *	    xtree is updated;
 *	 2. truncate index table of directory when last entry हटाओd
 *	map update via tlock at commit समय;
 *	PMAP:
 *	 Call xtTruncate_pmap instead
 *	WMAP:
 *	 1. हटाओ (मुक्त zero link count) on last reference release
 *	    (pmap has been मुक्तd at commit zero link count);
 *	 2. truncate (COMMIT_NOLINK file, i.e., पंचांगp file):
 *	    xtree is updated;
 *	 map update directly at truncation समय;
 *
 *	अगर (DELETE)
 *		no LOG_NOREDOPAGE is required (NOREDOखाता is sufficient);
 *	अन्यथा अगर (TRUNCATE)
 *		must ग_लिखो LOG_NOREDOPAGE क्रम deleted index page;
 *
 * pages may alपढ़ोy have been tlocked by anonymous transactions
 * during file growth (i.e., ग_लिखो) beक्रमe truncation;
 *
 * except last truncated entry, deleted entries reमुख्यs as is
 * in the page (nextindex is updated) क्रम other use
 * (e.g., log/update allocation map): this aव्योम copying the page
 * info but delay मुक्त of pages;
 *
 */
s64 xtTruncate(tid_t tid, काष्ठा inode *ip, s64 newsize, पूर्णांक flag)
अणु
	पूर्णांक rc = 0;
	s64 teof;
	काष्ठा metapage *mp;
	xtpage_t *p;
	s64 bn;
	पूर्णांक index, nextindex;
	xad_t *xad;
	s64 xoff, xaddr;
	पूर्णांक xlen, len, मुक्तxlen;
	काष्ठा btstack btstack;
	काष्ठा btframe *parent;
	काष्ठा tblock *tblk = शून्य;
	काष्ठा tlock *tlck = शून्य;
	काष्ठा xtlock *xtlck = शून्य;
	काष्ठा xdlistlock xadlock;	/* maplock क्रम COMMIT_WMAP */
	काष्ठा pxd_lock *pxdlock;		/* maplock क्रम COMMIT_WMAP */
	s64 nमुक्तd;
	पूर्णांक मुक्तd, log;
	पूर्णांक locked_leaves = 0;

	/* save object truncation type */
	अगर (tid) अणु
		tblk = tid_to_tblock(tid);
		tblk->xflag |= flag;
	पूर्ण

	nमुक्तd = 0;

	flag &= COMMIT_MAP;
	निश्चित(flag != COMMIT_PMAP);

	अगर (flag == COMMIT_PWMAP)
		log = 1;
	अन्यथा अणु
		log = 0;
		xadlock.flag = mlckFREEXADLIST;
		xadlock.index = 1;
	पूर्ण

	/*
	 * अगर the newsize is not an पूर्णांकegral number of pages,
	 * the file between newsize and next page boundary will
	 * be cleared.
	 * अगर truncating पूर्णांकo a file hole, it will cause
	 * a full block to be allocated क्रम the logical block.
	 */

	/*
	 * release page blocks of truncated region <teof, eof>
	 *
	 * मुक्त the data blocks from the leaf index blocks.
	 * delete the parent index entries corresponding to
	 * the मुक्तd child data/index blocks.
	 * मुक्त the index blocks themselves which aren't needed
	 * in new sized file.
	 *
	 * index blocks are updated only अगर the blocks are to be
	 * retained in the new sized file.
	 * अगर type is PMAP, the data and index pages are NOT
	 * मुक्तd, and the data and index blocks are NOT मुक्तd
	 * from working map.
	 * (this will allow जारीd access of data/index of
	 * temporary file (zerolink count file truncated to zero-length)).
	 */
	teof = (newsize + (JFS_SBI(ip->i_sb)->bsize - 1)) >>
	    JFS_SBI(ip->i_sb)->l2bsize;

	/* clear stack */
	BT_CLR(&btstack);

	/*
	 * start with root
	 *
	 * root resides in the inode
	 */
	bn = 0;

	/*
	 * first access of each page:
	 */
      getPage:
	XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
	अगर (rc)
		वापस rc;

	/* process entries backward from last index */
	index = le16_to_cpu(p->header.nextindex) - 1;


	/* Since this is the righपंचांगost page at this level, and we may have
	 * alपढ़ोy मुक्तd a page that was क्रमmerly to the right, let's make
	 * sure that the next poपूर्णांकer is zero.
	 */
	अगर (p->header.next) अणु
		अगर (log)
			/*
			 * Make sure this change to the header is logged.
			 * If we really truncate this leaf, the flag
			 * will be changed to tlckTRUNCATE
			 */
			tlck = txLock(tid, ip, mp, tlckXTREE|tlckGROW);
		BT_MARK_सूचीTY(mp, ip);
		p->header.next = 0;
	पूर्ण

	अगर (p->header.flag & BT_INTERNAL)
		जाओ getChild;

	/*
	 *	leaf page
	 */
	मुक्तd = 0;

	/* करोes region covered by leaf page precede Teof ? */
	xad = &p->xad[index];
	xoff = offsetXAD(xad);
	xlen = lengthXAD(xad);
	अगर (teof >= xoff + xlen) अणु
		XT_PUTPAGE(mp);
		जाओ getParent;
	पूर्ण

	/* (re)acquire tlock of the leaf page */
	अगर (log) अणु
		अगर (++locked_leaves > MAX_TRUNCATE_LEAVES) अणु
			/*
			 * We need to limit the size of the transaction
			 * to aव्योम exhausting pagecache & tlocks
			 */
			XT_PUTPAGE(mp);
			newsize = (xoff + xlen) << JFS_SBI(ip->i_sb)->l2bsize;
			जाओ getParent;
		पूर्ण
		tlck = txLock(tid, ip, mp, tlckXTREE);
		tlck->type = tlckXTREE | tlckTRUNCATE;
		xtlck = (काष्ठा xtlock *) & tlck->lock;
		xtlck->hwm.offset = le16_to_cpu(p->header.nextindex) - 1;
	पूर्ण
	BT_MARK_सूचीTY(mp, ip);

	/*
	 * scan backward leaf page entries
	 */
	क्रम (; index >= XTENTRYSTART; index--) अणु
		xad = &p->xad[index];
		xoff = offsetXAD(xad);
		xlen = lengthXAD(xad);
		xaddr = addressXAD(xad);

		/*
		 * The "data" क्रम a directory is indexed by the block
		 * device's address space.  This metadata must be invalidated
		 * here
		 */
		अगर (S_ISसूची(ip->i_mode) && (teof == 0))
			invalidate_xad_metapages(ip, *xad);
		/*
		 * entry beyond eof: जारी scan of current page
		 *          xad
		 * ---|---=======------->
		 *   eof
		 */
		अगर (teof < xoff) अणु
			nमुक्तd += xlen;
			जारी;
		पूर्ण

		/*
		 * (xoff <= teof): last entry to be deleted from page;
		 * If other entries reमुख्य in page: keep and update the page.
		 */

		/*
		 * eof == entry_start: delete the entry
		 *           xad
		 * -------|=======------->
		 *       eof
		 *
		 */
		अगर (teof == xoff) अणु
			nमुक्तd += xlen;

			अगर (index == XTENTRYSTART)
				अवरोध;

			nextindex = index;
		पूर्ण
		/*
		 * eof within the entry: truncate the entry.
		 *          xad
		 * -------===|===------->
		 *          eof
		 */
		अन्यथा अगर (teof < xoff + xlen) अणु
			/* update truncated entry */
			len = teof - xoff;
			मुक्तxlen = xlen - len;
			XADlength(xad, len);

			/* save pxd of truncated extent in tlck */
			xaddr += len;
			अगर (log) अणु	/* COMMIT_PWMAP */
				xtlck->lwm.offset = (xtlck->lwm.offset) ?
				    min(index, (पूर्णांक)xtlck->lwm.offset) : index;
				xtlck->lwm.length = index + 1 -
				    xtlck->lwm.offset;
				xtlck->twm.offset = index;
				pxdlock = (काष्ठा pxd_lock *) & xtlck->pxdlock;
				pxdlock->flag = mlckFREEPXD;
				PXDaddress(&pxdlock->pxd, xaddr);
				PXDlength(&pxdlock->pxd, मुक्तxlen);
			पूर्ण
			/* मुक्त truncated extent */
			अन्यथा अणु	/* COMMIT_WMAP */

				pxdlock = (काष्ठा pxd_lock *) & xadlock;
				pxdlock->flag = mlckFREEPXD;
				PXDaddress(&pxdlock->pxd, xaddr);
				PXDlength(&pxdlock->pxd, मुक्तxlen);
				txFreeMap(ip, pxdlock, शून्य, COMMIT_WMAP);

				/* reset map lock */
				xadlock.flag = mlckFREEXADLIST;
			पूर्ण

			/* current entry is new last entry; */
			nextindex = index + 1;

			nमुक्तd += मुक्तxlen;
		पूर्ण
		/*
		 * eof beyond the entry:
		 *          xad
		 * -------=======---|--->
		 *                 eof
		 */
		अन्यथा अणु		/* (xoff + xlen < teof) */

			nextindex = index + 1;
		पूर्ण

		अगर (nextindex < le16_to_cpu(p->header.nextindex)) अणु
			अगर (!log) अणु	/* COMMIT_WAMP */
				xadlock.xdlist = &p->xad[nextindex];
				xadlock.count =
				    le16_to_cpu(p->header.nextindex) -
				    nextindex;
				txFreeMap(ip, (काष्ठा maplock *) & xadlock,
					  शून्य, COMMIT_WMAP);
			पूर्ण
			p->header.nextindex = cpu_to_le16(nextindex);
		पूर्ण

		XT_PUTPAGE(mp);

		/* निश्चित(मुक्तd == 0); */
		जाओ getParent;
	पूर्ण			/* end scan of leaf page entries */

	मुक्तd = 1;

	/*
	 * leaf page become empty: मुक्त the page अगर type != PMAP
	 */
	अगर (log) अणु		/* COMMIT_PWMAP */
		/* txCommit() with tlckFREE:
		 * मुक्त data extents covered by leaf [XTENTRYSTART:hwm);
		 * invalidate leaf अगर COMMIT_PWMAP;
		 * अगर (TRUNCATE), will ग_लिखो LOG_NOREDOPAGE;
		 */
		tlck->type = tlckXTREE | tlckFREE;
	पूर्ण अन्यथा अणु		/* COMMIT_WAMP */

		/* मुक्त data extents covered by leaf */
		xadlock.xdlist = &p->xad[XTENTRYSTART];
		xadlock.count =
		    le16_to_cpu(p->header.nextindex) - XTENTRYSTART;
		txFreeMap(ip, (काष्ठा maplock *) & xadlock, शून्य, COMMIT_WMAP);
	पूर्ण

	अगर (p->header.flag & BT_ROOT) अणु
		p->header.flag &= ~BT_INTERNAL;
		p->header.flag |= BT_LEAF;
		p->header.nextindex = cpu_to_le16(XTENTRYSTART);

		XT_PUTPAGE(mp);	/* debug */
		जाओ out;
	पूर्ण अन्यथा अणु
		अगर (log) अणु	/* COMMIT_PWMAP */
			/* page will be invalidated at tx completion
			 */
			XT_PUTPAGE(mp);
		पूर्ण अन्यथा अणु	/* COMMIT_WMAP */

			अगर (mp->lid)
				lid_to_tlock(mp->lid)->flag |= tlckFREELOCK;

			/* invalidate empty leaf page */
			discard_metapage(mp);
		पूर्ण
	पूर्ण

	/*
	 * the leaf page become empty: delete the parent entry
	 * क्रम the leaf page अगर the parent page is to be kept
	 * in the new sized file.
	 */

	/*
	 * go back up to the parent page
	 */
      getParent:
	/* pop/restore parent entry क्रम the current child page */
	अगर ((parent = BT_POP(&btstack)) == शून्य)
		/* current page must have been root */
		जाओ out;

	/* get back the parent page */
	bn = parent->bn;
	XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
	अगर (rc)
		वापस rc;

	index = parent->index;

	/*
	 * child page was not empty:
	 */
	अगर (मुक्तd == 0) अणु
		/* has any entry deleted from parent ? */
		अगर (index < le16_to_cpu(p->header.nextindex) - 1) अणु
			/* (re)acquire tlock on the parent page */
			अगर (log) अणु	/* COMMIT_PWMAP */
				/* txCommit() with tlckTRUNCATE:
				 * मुक्त child extents covered by parent [);
				 */
				tlck = txLock(tid, ip, mp, tlckXTREE);
				xtlck = (काष्ठा xtlock *) & tlck->lock;
				अगर (!(tlck->type & tlckTRUNCATE)) अणु
					xtlck->hwm.offset =
					    le16_to_cpu(p->header.
							nextindex) - 1;
					tlck->type =
					    tlckXTREE | tlckTRUNCATE;
				पूर्ण
			पूर्ण अन्यथा अणु	/* COMMIT_WMAP */

				/* मुक्त child extents covered by parent */
				xadlock.xdlist = &p->xad[index + 1];
				xadlock.count =
				    le16_to_cpu(p->header.nextindex) -
				    index - 1;
				txFreeMap(ip, (काष्ठा maplock *) & xadlock,
					  शून्य, COMMIT_WMAP);
			पूर्ण
			BT_MARK_सूचीTY(mp, ip);

			p->header.nextindex = cpu_to_le16(index + 1);
		पूर्ण
		XT_PUTPAGE(mp);
		जाओ getParent;
	पूर्ण

	/*
	 * child page was empty:
	 */
	nमुक्तd += lengthXAD(&p->xad[index]);

	/*
	 * During working map update, child page's tlock must be handled
	 * beक्रमe parent's.  This is because the parent's tlock will cause
	 * the child's disk space to be marked available in the wmap, so
	 * it's important that the child page be released by that समय.
	 *
	 * ToDo:  tlocks should be on करोubly-linked list, so we can
	 * quickly हटाओ it and add it to the end.
	 */

	/*
	 * Move parent page's tlock to the end of the tid's tlock list
	 */
	अगर (log && mp->lid && (tblk->last != mp->lid) &&
	    lid_to_tlock(mp->lid)->tid) अणु
		lid_t lid = mp->lid;
		काष्ठा tlock *prev;

		tlck = lid_to_tlock(lid);

		अगर (tblk->next == lid)
			tblk->next = tlck->next;
		अन्यथा अणु
			क्रम (prev = lid_to_tlock(tblk->next);
			     prev->next != lid;
			     prev = lid_to_tlock(prev->next)) अणु
				निश्चित(prev->next);
			पूर्ण
			prev->next = tlck->next;
		पूर्ण
		lid_to_tlock(tblk->last)->next = lid;
		tlck->next = 0;
		tblk->last = lid;
	पूर्ण

	/*
	 * parent page become empty: मुक्त the page
	 */
	अगर (index == XTENTRYSTART) अणु
		अगर (log) अणु	/* COMMIT_PWMAP */
			/* txCommit() with tlckFREE:
			 * मुक्त child extents covered by parent;
			 * invalidate parent अगर COMMIT_PWMAP;
			 */
			tlck = txLock(tid, ip, mp, tlckXTREE);
			xtlck = (काष्ठा xtlock *) & tlck->lock;
			xtlck->hwm.offset =
			    le16_to_cpu(p->header.nextindex) - 1;
			tlck->type = tlckXTREE | tlckFREE;
		पूर्ण अन्यथा अणु	/* COMMIT_WMAP */

			/* मुक्त child extents covered by parent */
			xadlock.xdlist = &p->xad[XTENTRYSTART];
			xadlock.count =
			    le16_to_cpu(p->header.nextindex) -
			    XTENTRYSTART;
			txFreeMap(ip, (काष्ठा maplock *) & xadlock, शून्य,
				  COMMIT_WMAP);
		पूर्ण
		BT_MARK_सूचीTY(mp, ip);

		अगर (p->header.flag & BT_ROOT) अणु
			p->header.flag &= ~BT_INTERNAL;
			p->header.flag |= BT_LEAF;
			p->header.nextindex = cpu_to_le16(XTENTRYSTART);
			अगर (le16_to_cpu(p->header.maxentry) == XTROOTMAXSLOT) अणु
				/*
				 * Shrink root करोwn to allow अंतरभूत
				 * EA (otherwise fsck complains)
				 */
				p->header.maxentry =
				    cpu_to_le16(XTROOTINITSLOT);
				JFS_IP(ip)->mode2 |= INLINEEA;
			पूर्ण

			XT_PUTPAGE(mp);	/* debug */
			जाओ out;
		पूर्ण अन्यथा अणु
			अगर (log) अणु	/* COMMIT_PWMAP */
				/* page will be invalidated at tx completion
				 */
				XT_PUTPAGE(mp);
			पूर्ण अन्यथा अणु	/* COMMIT_WMAP */

				अगर (mp->lid)
					lid_to_tlock(mp->lid)->flag |=
						tlckFREELOCK;

				/* invalidate parent page */
				discard_metapage(mp);
			पूर्ण

			/* parent has become empty and मुक्तd:
			 * go back up to its parent page
			 */
			/* मुक्तd = 1; */
			जाओ getParent;
		पूर्ण
	पूर्ण
	/*
	 * parent page still has entries क्रम front region;
	 */
	अन्यथा अणु
		/* try truncate region covered by preceding entry
		 * (process backward)
		 */
		index--;

		/* go back करोwn to the child page corresponding
		 * to the entry
		 */
		जाओ getChild;
	पूर्ण

	/*
	 *	पूर्णांकernal page: go करोwn to child page of current entry
	 */
      getChild:
	/* save current parent entry क्रम the child page */
	अगर (BT_STACK_FULL(&btstack)) अणु
		jfs_error(ip->i_sb, "stack overrun!\n");
		XT_PUTPAGE(mp);
		वापस -EIO;
	पूर्ण
	BT_PUSH(&btstack, bn, index);

	/* get child page */
	xad = &p->xad[index];
	bn = addressXAD(xad);

	/*
	 * first access of each पूर्णांकernal entry:
	 */
	/* release parent page */
	XT_PUTPAGE(mp);

	/* process the child page */
	जाओ getPage;

      out:
	/*
	 * update file resource stat
	 */
	/* set size
	 */
	अगर (S_ISसूची(ip->i_mode) && !newsize)
		ip->i_size = 1;	/* fsck hates zero-length directories */
	अन्यथा
		ip->i_size = newsize;

	/* update quota allocation to reflect मुक्तd blocks */
	dquot_मुक्त_block(ip, nमुक्तd);

	/*
	 * मुक्त tlock of invalidated pages
	 */
	अगर (flag == COMMIT_WMAP)
		txFreelock(ip);

	वापस newsize;
पूर्ण


/*
 *	xtTruncate_pmap()
 *
 * function:
 *	Perक्रमm truncate to zero length क्रम deleted file, leaving the
 *	xtree and working map untouched.  This allows the file to
 *	be accessed via खोलो file handles, जबतक the delete of the file
 *	is committed to disk.
 *
 * parameter:
 *	tid_t		tid,
 *	काष्ठा inode	*ip,
 *	s64		committed_size)
 *
 * वापस: new committed size
 *
 * note:
 *
 *	To aव्योम deadlock by holding too many transaction locks, the
 *	truncation may be broken up पूर्णांकo multiple transactions.
 *	The committed_size keeps track of part of the file has been
 *	मुक्तd from the pmaps.
 */
s64 xtTruncate_pmap(tid_t tid, काष्ठा inode *ip, s64 committed_size)
अणु
	s64 bn;
	काष्ठा btstack btstack;
	पूर्णांक cmp;
	पूर्णांक index;
	पूर्णांक locked_leaves = 0;
	काष्ठा metapage *mp;
	xtpage_t *p;
	काष्ठा btframe *parent;
	पूर्णांक rc;
	काष्ठा tblock *tblk;
	काष्ठा tlock *tlck = शून्य;
	xad_t *xad;
	पूर्णांक xlen;
	s64 xoff;
	काष्ठा xtlock *xtlck = शून्य;

	/* save object truncation type */
	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_PMAP;

	/* clear stack */
	BT_CLR(&btstack);

	अगर (committed_size) अणु
		xoff = (committed_size >> JFS_SBI(ip->i_sb)->l2bsize) - 1;
		rc = xtSearch(ip, xoff, शून्य, &cmp, &btstack, 0);
		अगर (rc)
			वापस rc;

		XT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

		अगर (cmp != 0) अणु
			XT_PUTPAGE(mp);
			jfs_error(ip->i_sb, "did not find extent\n");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * start with root
		 *
		 * root resides in the inode
		 */
		bn = 0;

		/*
		 * first access of each page:
		 */
      getPage:
		XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
		अगर (rc)
			वापस rc;

		/* process entries backward from last index */
		index = le16_to_cpu(p->header.nextindex) - 1;

		अगर (p->header.flag & BT_INTERNAL)
			जाओ getChild;
	पूर्ण

	/*
	 *	leaf page
	 */

	अगर (++locked_leaves > MAX_TRUNCATE_LEAVES) अणु
		/*
		 * We need to limit the size of the transaction
		 * to aव्योम exhausting pagecache & tlocks
		 */
		xad = &p->xad[index];
		xoff = offsetXAD(xad);
		xlen = lengthXAD(xad);
		XT_PUTPAGE(mp);
		वापस (xoff + xlen) << JFS_SBI(ip->i_sb)->l2bsize;
	पूर्ण
	tlck = txLock(tid, ip, mp, tlckXTREE);
	tlck->type = tlckXTREE | tlckFREE;
	xtlck = (काष्ठा xtlock *) & tlck->lock;
	xtlck->hwm.offset = index;


	XT_PUTPAGE(mp);

	/*
	 * go back up to the parent page
	 */
      getParent:
	/* pop/restore parent entry क्रम the current child page */
	अगर ((parent = BT_POP(&btstack)) == शून्य)
		/* current page must have been root */
		जाओ out;

	/* get back the parent page */
	bn = parent->bn;
	XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
	अगर (rc)
		वापस rc;

	index = parent->index;

	/*
	 * parent page become empty: मुक्त the page
	 */
	अगर (index == XTENTRYSTART) अणु
		/* txCommit() with tlckFREE:
		 * मुक्त child extents covered by parent;
		 * invalidate parent अगर COMMIT_PWMAP;
		 */
		tlck = txLock(tid, ip, mp, tlckXTREE);
		xtlck = (काष्ठा xtlock *) & tlck->lock;
		xtlck->hwm.offset = le16_to_cpu(p->header.nextindex) - 1;
		tlck->type = tlckXTREE | tlckFREE;

		XT_PUTPAGE(mp);

		अगर (p->header.flag & BT_ROOT) अणु

			जाओ out;
		पूर्ण अन्यथा अणु
			जाओ getParent;
		पूर्ण
	पूर्ण
	/*
	 * parent page still has entries क्रम front region;
	 */
	अन्यथा
		index--;
	/*
	 *	पूर्णांकernal page: go करोwn to child page of current entry
	 */
      getChild:
	/* save current parent entry क्रम the child page */
	अगर (BT_STACK_FULL(&btstack)) अणु
		jfs_error(ip->i_sb, "stack overrun!\n");
		XT_PUTPAGE(mp);
		वापस -EIO;
	पूर्ण
	BT_PUSH(&btstack, bn, index);

	/* get child page */
	xad = &p->xad[index];
	bn = addressXAD(xad);

	/*
	 * first access of each पूर्णांकernal entry:
	 */
	/* release parent page */
	XT_PUTPAGE(mp);

	/* process the child page */
	जाओ getPage;

      out:

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_JFS_STATISTICS
पूर्णांक jfs_xtstat_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m,
		       "JFS Xtree statistics\n"
		       "====================\n"
		       "searches = %d\n"
		       "fast searches = %d\n"
		       "splits = %d\n",
		       xtStat.search,
		       xtStat.fastSearch,
		       xtStat.split);
	वापस 0;
पूर्ण
#पूर्ण_अगर
