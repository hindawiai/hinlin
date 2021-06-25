<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/crc32.h>
#समावेश <linux/compiler.h>
#समावेश "nodelist.h"
#समावेश "summary.h"
#समावेश "debug.h"

#घोषणा DEFAULT_EMPTY_SCAN_SIZE 256

#घोषणा noisy_prपूर्णांकk(noise, fmt, ...)					\
करो अणु									\
	अगर (*(noise)) अणु							\
		pr_notice(fmt, ##__VA_ARGS__);				\
		(*(noise))--;						\
		अगर (!(*(noise)))					\
			pr_notice("Further such events for this erase block will not be printed\n"); \
	पूर्ण								\
पूर्ण जबतक (0)

अटल uपूर्णांक32_t pseuकरो_अक्रमom;

अटल पूर्णांक jffs2_scan_eraseblock (काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				  अचिन्हित अक्षर *buf, uपूर्णांक32_t buf_size, काष्ठा jffs2_summary *s);

/* These helper functions _must_ increase ofs and also करो the dirty/used space accounting.
 * Returning an error will पात the mount - bad checksums etc. should just mark the space
 * as dirty.
 */
अटल पूर्णांक jffs2_scan_inode_node(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				 काष्ठा jffs2_raw_inode *ri, uपूर्णांक32_t ofs, काष्ठा jffs2_summary *s);
अटल पूर्णांक jffs2_scan_dirent_node(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				 काष्ठा jffs2_raw_dirent *rd, uपूर्णांक32_t ofs, काष्ठा jffs2_summary *s);

अटल अंतरभूत पूर्णांक min_मुक्त(काष्ठा jffs2_sb_info *c)
अणु
	uपूर्णांक32_t min = 2 * माप(काष्ठा jffs2_raw_inode);
#अगर_घोषित CONFIG_JFFS2_FS_WRITEBUFFER
	अगर (!jffs2_can_mark_obsolete(c) && min < c->wbuf_pagesize)
		वापस c->wbuf_pagesize;
#पूर्ण_अगर
	वापस min;

पूर्ण

अटल अंतरभूत uपूर्णांक32_t EMPTY_SCAN_SIZE(uपूर्णांक32_t sector_size) अणु
	अगर (sector_size < DEFAULT_EMPTY_SCAN_SIZE)
		वापस sector_size;
	अन्यथा
		वापस DEFAULT_EMPTY_SCAN_SIZE;
पूर्ण

अटल पूर्णांक file_dirty(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb)
अणु
	पूर्णांक ret;

	अगर ((ret = jffs2_pपुनः_स्मृति_raw_node_refs(c, jeb, 1)))
		वापस ret;
	अगर ((ret = jffs2_scan_dirty_space(c, jeb, jeb->मुक्त_size)))
		वापस ret;
	/* Turned wasted size पूर्णांकo dirty, since we apparently 
	   think it's recoverable now. */
	jeb->dirty_size += jeb->wasted_size;
	c->dirty_size += jeb->wasted_size;
	c->wasted_size -= jeb->wasted_size;
	jeb->wasted_size = 0;
	अगर (VERYसूचीTY(c, jeb->dirty_size)) अणु
		list_add(&jeb->list, &c->very_dirty_list);
	पूर्ण अन्यथा अणु
		list_add(&jeb->list, &c->dirty_list);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक jffs2_scan_medium(काष्ठा jffs2_sb_info *c)
अणु
	पूर्णांक i, ret;
	uपूर्णांक32_t empty_blocks = 0, bad_blocks = 0;
	अचिन्हित अक्षर *flashbuf = शून्य;
	uपूर्णांक32_t buf_size = 0;
	काष्ठा jffs2_summary *s = शून्य; /* summary info collected by the scan process */
#अगर_अघोषित __ECOS
	माप_प्रकार poपूर्णांकlen, try_size;

	ret = mtd_poपूर्णांक(c->mtd, 0, c->mtd->size, &poपूर्णांकlen,
			(व्योम **)&flashbuf, शून्य);
	अगर (!ret && poपूर्णांकlen < c->mtd->size) अणु
		/* Don't muck about if it won't let us poपूर्णांक to the whole flash */
		jffs2_dbg(1, "MTD point returned len too short: 0x%zx\n",
			  poपूर्णांकlen);
		mtd_unpoपूर्णांक(c->mtd, 0, poपूर्णांकlen);
		flashbuf = शून्य;
	पूर्ण
	अगर (ret && ret != -EOPNOTSUPP)
		jffs2_dbg(1, "MTD point failed %d\n", ret);
#पूर्ण_अगर
	अगर (!flashbuf) अणु
		/* For न_अंकD it's quicker to पढ़ो a whole eraseblock at a समय,
		   apparently */
		अगर (jffs2_cleanmarker_oob(c))
			try_size = c->sector_size;
		अन्यथा
			try_size = PAGE_SIZE;

		jffs2_dbg(1, "Trying to allocate readbuf of %zu "
			  "bytes\n", try_size);

		flashbuf = mtd_kदो_स्मृति_up_to(c->mtd, &try_size);
		अगर (!flashbuf)
			वापस -ENOMEM;

		jffs2_dbg(1, "Allocated readbuf of %zu bytes\n",
			  try_size);

		buf_size = (uपूर्णांक32_t)try_size;
	पूर्ण

	अगर (jffs2_sum_active()) अणु
		s = kzalloc(माप(काष्ठा jffs2_summary), GFP_KERNEL);
		अगर (!s) अणु
			JFFS2_WARNING("Can't allocate memory for summary\n");
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i=0; i<c->nr_blocks; i++) अणु
		काष्ठा jffs2_eraseblock *jeb = &c->blocks[i];

		cond_resched();

		/* reset summary info क्रम next eraseblock scan */
		jffs2_sum_reset_collected(s);

		ret = jffs2_scan_eraseblock(c, jeb, buf_size?flashbuf:(flashbuf+jeb->offset),
						buf_size, s);

		अगर (ret < 0)
			जाओ out;

		jffs2_dbg_acct_paranoia_check_nolock(c, jeb);

		/* Now decide which list to put it on */
		चयन(ret) अणु
		हाल BLK_STATE_ALLFF:
			/*
			 * Empty block.   Since we can't be sure it
			 * was entirely erased, we just queue it क्रम erase
			 * again.  It will be marked as such when the erase
			 * is complete.  Meanजबतक we still count it as empty
			 * क्रम later checks.
			 */
			empty_blocks++;
			list_add(&jeb->list, &c->erase_pending_list);
			c->nr_erasing_blocks++;
			अवरोध;

		हाल BLK_STATE_CLEANMARKER:
			/* Only a CLEANMARKER node is valid */
			अगर (!jeb->dirty_size) अणु
				/* It's actually मुक्त */
				list_add(&jeb->list, &c->मुक्त_list);
				c->nr_मुक्त_blocks++;
			पूर्ण अन्यथा अणु
				/* Dirt */
				jffs2_dbg(1, "Adding all-dirty block at 0x%08x to erase_pending_list\n",
					  jeb->offset);
				list_add(&jeb->list, &c->erase_pending_list);
				c->nr_erasing_blocks++;
			पूर्ण
			अवरोध;

		हाल BLK_STATE_CLEAN:
			/* Full (or almost full) of clean data. Clean list */
			list_add(&jeb->list, &c->clean_list);
			अवरोध;

		हाल BLK_STATE_PARTसूचीTY:
			/* Some data, but not full. Dirty list. */
			/* We want to remember the block with most मुक्त space
			and stick it in the 'nextblock' position to start writing to it. */
			अगर (jeb->मुक्त_size > min_मुक्त(c) &&
					(!c->nextblock || c->nextblock->मुक्त_size < jeb->मुक्त_size)) अणु
				/* Better candidate क्रम the next ग_लिखोs to go to */
				अगर (c->nextblock) अणु
					ret = file_dirty(c, c->nextblock);
					अगर (ret)
						जाओ out;
					/* deleting summary inक्रमmation of the old nextblock */
					jffs2_sum_reset_collected(c->summary);
				पूर्ण
				/* update collected summary inक्रमmation क्रम the current nextblock */
				jffs2_sum_move_collected(c, s);
				jffs2_dbg(1, "%s(): new nextblock = 0x%08x\n",
					  __func__, jeb->offset);
				c->nextblock = jeb;
			पूर्ण अन्यथा अणु
				ret = file_dirty(c, jeb);
				अगर (ret)
					जाओ out;
			पूर्ण
			अवरोध;

		हाल BLK_STATE_ALLसूचीTY:
			/* Nothing valid - not even a clean marker. Needs erasing. */
			/* For now we just put it on the erasing list. We'll start the erases later */
			jffs2_dbg(1, "Erase block at 0x%08x is not formatted. It will be erased\n",
				  jeb->offset);
			list_add(&jeb->list, &c->erase_pending_list);
			c->nr_erasing_blocks++;
			अवरोध;

		हाल BLK_STATE_BADBLOCK:
			jffs2_dbg(1, "Block at 0x%08x is bad\n", jeb->offset);
			list_add(&jeb->list, &c->bad_list);
			c->bad_size += c->sector_size;
			c->मुक्त_size -= c->sector_size;
			bad_blocks++;
			अवरोध;
		शेष:
			pr_warn("%s(): unknown block state\n", __func__);
			BUG();
		पूर्ण
	पूर्ण

	/* Nextblock dirty is always seen as wasted, because we cannot recycle it now */
	अगर (c->nextblock && (c->nextblock->dirty_size)) अणु
		c->nextblock->wasted_size += c->nextblock->dirty_size;
		c->wasted_size += c->nextblock->dirty_size;
		c->dirty_size -= c->nextblock->dirty_size;
		c->nextblock->dirty_size = 0;
	पूर्ण
#अगर_घोषित CONFIG_JFFS2_FS_WRITEBUFFER
	अगर (!jffs2_can_mark_obsolete(c) && c->wbuf_pagesize && c->nextblock && (c->nextblock->मुक्त_size % c->wbuf_pagesize)) अणु
		/* If we're going to start writing पूर्णांकo a block which alपढ़ोy
		   contains data, and the end of the data isn't page-aligned,
		   skip a little and align it. */

		uपूर्णांक32_t skip = c->nextblock->मुक्त_size % c->wbuf_pagesize;

		jffs2_dbg(1, "%s(): Skipping %d bytes in nextblock to ensure page alignment\n",
			  __func__, skip);
		jffs2_pपुनः_स्मृति_raw_node_refs(c, c->nextblock, 1);
		jffs2_scan_dirty_space(c, c->nextblock, skip);
	पूर्ण
#पूर्ण_अगर
	अगर (c->nr_erasing_blocks) अणु
		अगर (!c->used_size && !c->unchecked_size &&
			((c->nr_मुक्त_blocks+empty_blocks+bad_blocks) != c->nr_blocks || bad_blocks == c->nr_blocks)) अणु
			pr_notice("Cowardly refusing to erase blocks on filesystem with no valid JFFS2 nodes\n");
			pr_notice("empty_blocks %d, bad_blocks %d, c->nr_blocks %d\n",
				  empty_blocks, bad_blocks, c->nr_blocks);
			ret = -EIO;
			जाओ out;
		पूर्ण
		spin_lock(&c->erase_completion_lock);
		jffs2_garbage_collect_trigger(c);
		spin_unlock(&c->erase_completion_lock);
	पूर्ण
	ret = 0;
 out:
	अगर (buf_size)
		kमुक्त(flashbuf);
#अगर_अघोषित __ECOS
	अन्यथा
		mtd_unpoपूर्णांक(c->mtd, 0, c->mtd->size);
#पूर्ण_अगर
	kमुक्त(s);
	वापस ret;
पूर्ण

अटल पूर्णांक jffs2_fill_scan_buf(काष्ठा jffs2_sb_info *c, व्योम *buf,
			       uपूर्णांक32_t ofs, uपूर्णांक32_t len)
अणु
	पूर्णांक ret;
	माप_प्रकार retlen;

	ret = jffs2_flash_पढ़ो(c, ofs, len, &retlen, buf);
	अगर (ret) अणु
		jffs2_dbg(1, "mtd->read(0x%x bytes from 0x%x) returned %d\n",
			  len, ofs, ret);
		वापस ret;
	पूर्ण
	अगर (retlen < len) अणु
		jffs2_dbg(1, "Read at 0x%x gave only 0x%zx bytes\n",
			  ofs, retlen);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक jffs2_scan_classअगरy_jeb(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb)
अणु
	अगर ((jeb->used_size + jeb->unchecked_size) == PAD(c->cleanmarker_size) && !jeb->dirty_size
	    && (!jeb->first_node || !ref_next(jeb->first_node)) )
		वापस BLK_STATE_CLEANMARKER;

	/* move blocks with max 4 byte dirty space to cleanlist */
	अन्यथा अगर (!ISसूचीTY(c->sector_size - (jeb->used_size + jeb->unchecked_size))) अणु
		c->dirty_size -= jeb->dirty_size;
		c->wasted_size += jeb->dirty_size;
		jeb->wasted_size += jeb->dirty_size;
		jeb->dirty_size = 0;
		वापस BLK_STATE_CLEAN;
	पूर्ण अन्यथा अगर (jeb->used_size || jeb->unchecked_size)
		वापस BLK_STATE_PARTसूचीTY;
	अन्यथा
		वापस BLK_STATE_ALLसूचीTY;
पूर्ण

#अगर_घोषित CONFIG_JFFS2_FS_XATTR
अटल पूर्णांक jffs2_scan_xattr_node(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				 काष्ठा jffs2_raw_xattr *rx, uपूर्णांक32_t ofs,
				 काष्ठा jffs2_summary *s)
अणु
	काष्ठा jffs2_xattr_datum *xd;
	uपूर्णांक32_t xid, version, totlen, crc;
	पूर्णांक err;

	crc = crc32(0, rx, माप(काष्ठा jffs2_raw_xattr) - 4);
	अगर (crc != je32_to_cpu(rx->node_crc)) अणु
		JFFS2_WARNING("node CRC failed at %#08x, read=%#08x, calc=%#08x\n",
			      ofs, je32_to_cpu(rx->node_crc), crc);
		अगर ((err = jffs2_scan_dirty_space(c, jeb, je32_to_cpu(rx->totlen))))
			वापस err;
		वापस 0;
	पूर्ण

	xid = je32_to_cpu(rx->xid);
	version = je32_to_cpu(rx->version);

	totlen = PAD(माप(काष्ठा jffs2_raw_xattr)
			+ rx->name_len + 1 + je16_to_cpu(rx->value_len));
	अगर (totlen != je32_to_cpu(rx->totlen)) अणु
		JFFS2_WARNING("node length mismatch at %#08x, read=%u, calc=%u\n",
			      ofs, je32_to_cpu(rx->totlen), totlen);
		अगर ((err = jffs2_scan_dirty_space(c, jeb, je32_to_cpu(rx->totlen))))
			वापस err;
		वापस 0;
	पूर्ण

	xd = jffs2_setup_xattr_datum(c, xid, version);
	अगर (IS_ERR(xd))
		वापस PTR_ERR(xd);

	अगर (xd->version > version) अणु
		काष्ठा jffs2_raw_node_ref *raw
			= jffs2_link_node_ref(c, jeb, ofs | REF_PRISTINE, totlen, शून्य);
		raw->next_in_ino = xd->node->next_in_ino;
		xd->node->next_in_ino = raw;
	पूर्ण अन्यथा अणु
		xd->version = version;
		xd->xprefix = rx->xprefix;
		xd->name_len = rx->name_len;
		xd->value_len = je16_to_cpu(rx->value_len);
		xd->data_crc = je32_to_cpu(rx->data_crc);

		jffs2_link_node_ref(c, jeb, ofs | REF_PRISTINE, totlen, (व्योम *)xd);
	पूर्ण

	अगर (jffs2_sum_active())
		jffs2_sum_add_xattr_mem(s, rx, ofs - jeb->offset);
	dbg_xattr("scanning xdatum at %#08x (xid=%u, version=%u)\n",
		  ofs, xd->xid, xd->version);
	वापस 0;
पूर्ण

अटल पूर्णांक jffs2_scan_xref_node(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				काष्ठा jffs2_raw_xref *rr, uपूर्णांक32_t ofs,
				काष्ठा jffs2_summary *s)
अणु
	काष्ठा jffs2_xattr_ref *ref;
	uपूर्णांक32_t crc;
	पूर्णांक err;

	crc = crc32(0, rr, माप(*rr) - 4);
	अगर (crc != je32_to_cpu(rr->node_crc)) अणु
		JFFS2_WARNING("node CRC failed at %#08x, read=%#08x, calc=%#08x\n",
			      ofs, je32_to_cpu(rr->node_crc), crc);
		अगर ((err = jffs2_scan_dirty_space(c, jeb, PAD(je32_to_cpu(rr->totlen)))))
			वापस err;
		वापस 0;
	पूर्ण

	अगर (PAD(माप(काष्ठा jffs2_raw_xref)) != je32_to_cpu(rr->totlen)) अणु
		JFFS2_WARNING("node length mismatch at %#08x, read=%u, calc=%zd\n",
			      ofs, je32_to_cpu(rr->totlen),
			      PAD(माप(काष्ठा jffs2_raw_xref)));
		अगर ((err = jffs2_scan_dirty_space(c, jeb, je32_to_cpu(rr->totlen))))
			वापस err;
		वापस 0;
	पूर्ण

	ref = jffs2_alloc_xattr_ref();
	अगर (!ref)
		वापस -ENOMEM;

	/* BEFORE jffs2_build_xattr_subप्रणाली() called, 
	 * and AFTER xattr_ref is marked as a dead xref,
	 * ref->xid is used to store 32bit xid, xd is not used
	 * ref->ino is used to store 32bit inode-number, ic is not used
	 * Thoes variables are declared as जोड़, thus using those
	 * are exclusive. In a similar way, ref->next is temporarily
	 * used to chain all xattr_ref object. It's re-chained to
	 * jffs2_inode_cache in jffs2_build_xattr_subप्रणाली() correctly.
	 */
	ref->ino = je32_to_cpu(rr->ino);
	ref->xid = je32_to_cpu(rr->xid);
	ref->xseqno = je32_to_cpu(rr->xseqno);
	अगर (ref->xseqno > c->highest_xseqno)
		c->highest_xseqno = (ref->xseqno & ~XREF_DELETE_MARKER);
	ref->next = c->xref_temp;
	c->xref_temp = ref;

	jffs2_link_node_ref(c, jeb, ofs | REF_PRISTINE, PAD(je32_to_cpu(rr->totlen)), (व्योम *)ref);

	अगर (jffs2_sum_active())
		jffs2_sum_add_xref_mem(s, rr, ofs - jeb->offset);
	dbg_xattr("scan xref at %#08x (xid=%u, ino=%u)\n",
		  ofs, ref->xid, ref->ino);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Called with 'buf_size == 0' अगर buf is in fact a poपूर्णांकer _directly_ पूर्णांकo
   the flash, XIP-style */
अटल पूर्णांक jffs2_scan_eraseblock (काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				  अचिन्हित अक्षर *buf, uपूर्णांक32_t buf_size, काष्ठा jffs2_summary *s) अणु
	काष्ठा jffs2_unknown_node *node;
	काष्ठा jffs2_unknown_node crcnode;
	uपूर्णांक32_t ofs, prevofs, max_ofs;
	uपूर्णांक32_t hdr_crc, buf_ofs, buf_len;
	पूर्णांक err;
	पूर्णांक noise = 0;


#अगर_घोषित CONFIG_JFFS2_FS_WRITEBUFFER
	पूर्णांक cleanmarkerfound = 0;
#पूर्ण_अगर

	ofs = jeb->offset;
	prevofs = jeb->offset - 1;

	jffs2_dbg(1, "%s(): Scanning block at 0x%x\n", __func__, ofs);

#अगर_घोषित CONFIG_JFFS2_FS_WRITEBUFFER
	अगर (jffs2_cleanmarker_oob(c)) अणु
		पूर्णांक ret;

		अगर (mtd_block_isbad(c->mtd, jeb->offset))
			वापस BLK_STATE_BADBLOCK;

		ret = jffs2_check_nand_cleanmarker(c, jeb);
		jffs2_dbg(2, "jffs_check_nand_cleanmarker returned %d\n", ret);

		/* Even अगर it's not found, we still scan to see
		   अगर the block is empty. We use this inक्रमmation
		   to decide whether to erase it or not. */
		चयन (ret) अणु
		हाल 0:		cleanmarkerfound = 1; अवरोध;
		हाल 1: 	अवरोध;
		शेष: 	वापस ret;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (jffs2_sum_active()) अणु
		काष्ठा jffs2_sum_marker *sm;
		व्योम *sumptr = शून्य;
		uपूर्णांक32_t sumlen;
	      
		अगर (!buf_size) अणु
			/* XIP हाल. Just look, poपूर्णांक at the summary अगर it's there */
			sm = (व्योम *)buf + c->sector_size - माप(*sm);
			अगर (je32_to_cpu(sm->magic) == JFFS2_SUM_MAGIC) अणु
				sumptr = buf + je32_to_cpu(sm->offset);
				sumlen = c->sector_size - je32_to_cpu(sm->offset);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* If न_अंकD flash, पढ़ो a whole page of it. Else just the end */
			अगर (c->wbuf_pagesize)
				buf_len = c->wbuf_pagesize;
			अन्यथा
				buf_len = माप(*sm);

			/* Read as much as we want पूर्णांकo the _end_ of the pपुनः_स्मृतिated buffer */
			err = jffs2_fill_scan_buf(c, buf + buf_size - buf_len, 
						  jeb->offset + c->sector_size - buf_len,
						  buf_len);				
			अगर (err)
				वापस err;

			sm = (व्योम *)buf + buf_size - माप(*sm);
			अगर (je32_to_cpu(sm->magic) == JFFS2_SUM_MAGIC) अणु
				sumlen = c->sector_size - je32_to_cpu(sm->offset);
				sumptr = buf + buf_size - sumlen;

				/* sm->offset maybe wrong but MAGIC maybe right */
				अगर (sumlen > c->sector_size)
					जाओ full_scan;

				/* Now, make sure the summary itself is available */
				अगर (sumlen > buf_size) अणु
					/* Need to kदो_स्मृति क्रम this. */
					sumptr = kदो_स्मृति(sumlen, GFP_KERNEL);
					अगर (!sumptr)
						वापस -ENOMEM;
					स_नकल(sumptr + sumlen - buf_len, buf + buf_size - buf_len, buf_len);
				पूर्ण
				अगर (buf_len < sumlen) अणु
					/* Need to पढ़ो more so that the entire summary node is present */
					err = jffs2_fill_scan_buf(c, sumptr, 
								  jeb->offset + c->sector_size - sumlen,
								  sumlen - buf_len);				
					अगर (err) अणु
						अगर (sumlen > buf_size)
							kमुक्त(sumptr);
						वापस err;
					पूर्ण
				पूर्ण
			पूर्ण

		पूर्ण

		अगर (sumptr) अणु
			err = jffs2_sum_scan_sumnode(c, jeb, sumptr, sumlen, &pseuकरो_अक्रमom);

			अगर (buf_size && sumlen > buf_size)
				kमुक्त(sumptr);
			/* If it वापसs with a real error, bail. 
			   If it वापसs positive, that's a block classअगरication
			   (i.e. BLK_STATE_xxx) so वापस that too.
			   If it वापसs zero, fall through to full scan. */
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

full_scan:
	buf_ofs = jeb->offset;

	अगर (!buf_size) अणु
		/* This is the XIP हाल -- we're पढ़ोing _directly_ from the flash chip */
		buf_len = c->sector_size;
	पूर्ण अन्यथा अणु
		buf_len = EMPTY_SCAN_SIZE(c->sector_size);
		err = jffs2_fill_scan_buf(c, buf, buf_ofs, buf_len);
		अगर (err)
			वापस err;
	पूर्ण

	/* We temporarily use 'ofs' as a poपूर्णांकer पूर्णांकo the buffer/jeb */
	ofs = 0;
	max_ofs = EMPTY_SCAN_SIZE(c->sector_size);
	/* Scan only EMPTY_SCAN_SIZE of 0xFF beक्रमe declaring it's empty */
	जबतक(ofs < max_ofs && *(uपूर्णांक32_t *)(&buf[ofs]) == 0xFFFFFFFF)
		ofs += 4;

	अगर (ofs == max_ofs) अणु
#अगर_घोषित CONFIG_JFFS2_FS_WRITEBUFFER
		अगर (jffs2_cleanmarker_oob(c)) अणु
			/* scan oob, take care of cleanmarker */
			पूर्णांक ret = jffs2_check_oob_empty(c, jeb, cleanmarkerfound);
			jffs2_dbg(2, "jffs2_check_oob_empty returned %d\n",
				  ret);
			चयन (ret) अणु
			हाल 0:		वापस cleanmarkerfound ? BLK_STATE_CLEANMARKER : BLK_STATE_ALLFF;
			हाल 1: 	वापस BLK_STATE_ALLसूचीTY;
			शेष: 	वापस ret;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		jffs2_dbg(1, "Block at 0x%08x is empty (erased)\n",
			  jeb->offset);
		अगर (c->cleanmarker_size == 0)
			वापस BLK_STATE_CLEANMARKER;	/* करोn't bother with re-erase */
		अन्यथा
			वापस BLK_STATE_ALLFF;	/* OK to erase अगर all blocks are like this */
	पूर्ण
	अगर (ofs) अणु
		jffs2_dbg(1, "Free space at %08x ends at %08x\n", jeb->offset,
			  jeb->offset + ofs);
		अगर ((err = jffs2_pपुनः_स्मृति_raw_node_refs(c, jeb, 1)))
			वापस err;
		अगर ((err = jffs2_scan_dirty_space(c, jeb, ofs)))
			वापस err;
	पूर्ण

	/* Now ofs is a complete physical flash offset as it always was... */
	ofs += jeb->offset;

	noise = 10;

	dbg_summary("no summary found in jeb 0x%08x. Apply original scan.\n",jeb->offset);

scan_more:
	जबतक(ofs < jeb->offset + c->sector_size) अणु

		jffs2_dbg_acct_paranoia_check_nolock(c, jeb);

		/* Make sure there are node refs available क्रम use */
		err = jffs2_pपुनः_स्मृति_raw_node_refs(c, jeb, 2);
		अगर (err)
			वापस err;

		cond_resched();

		अगर (ofs & 3) अणु
			pr_warn("Eep. ofs 0x%08x not word-aligned!\n", ofs);
			ofs = PAD(ofs);
			जारी;
		पूर्ण
		अगर (ofs == prevofs) अणु
			pr_warn("ofs 0x%08x has already been seen. Skipping\n",
				ofs);
			अगर ((err = jffs2_scan_dirty_space(c, jeb, 4)))
				वापस err;
			ofs += 4;
			जारी;
		पूर्ण
		prevofs = ofs;

		अगर (jeb->offset + c->sector_size < ofs + माप(*node)) अणु
			jffs2_dbg(1, "Fewer than %zd bytes left to end of block. (%x+%x<%x+%zx) Not reading\n",
				  माप(काष्ठा jffs2_unknown_node),
				  jeb->offset, c->sector_size, ofs,
				  माप(*node));
			अगर ((err = jffs2_scan_dirty_space(c, jeb, (jeb->offset + c->sector_size)-ofs)))
				वापस err;
			अवरोध;
		पूर्ण

		अगर (buf_ofs + buf_len < ofs + माप(*node)) अणु
			buf_len = min_t(uपूर्णांक32_t, buf_size, jeb->offset + c->sector_size - ofs);
			jffs2_dbg(1, "Fewer than %zd bytes (node header) left to end of buf. Reading 0x%x at 0x%08x\n",
				  माप(काष्ठा jffs2_unknown_node),
				  buf_len, ofs);
			err = jffs2_fill_scan_buf(c, buf, ofs, buf_len);
			अगर (err)
				वापस err;
			buf_ofs = ofs;
		पूर्ण

		node = (काष्ठा jffs2_unknown_node *)&buf[ofs-buf_ofs];

		अगर (*(uपूर्णांक32_t *)(&buf[ofs-buf_ofs]) == 0xffffffff) अणु
			uपूर्णांक32_t inbuf_ofs;
			uपूर्णांक32_t empty_start, scan_end;

			empty_start = ofs;
			ofs += 4;
			scan_end = min_t(uपूर्णांक32_t, EMPTY_SCAN_SIZE(c->sector_size)/8, buf_len);

			jffs2_dbg(1, "Found empty flash at 0x%08x\n", ofs);
		more_empty:
			inbuf_ofs = ofs - buf_ofs;
			जबतक (inbuf_ofs < scan_end) अणु
				अगर (unlikely(*(uपूर्णांक32_t *)(&buf[inbuf_ofs]) != 0xffffffff)) अणु
					pr_warn("Empty flash at 0x%08x ends at 0x%08x\n",
						empty_start, ofs);
					अगर ((err = jffs2_scan_dirty_space(c, jeb, ofs-empty_start)))
						वापस err;
					जाओ scan_more;
				पूर्ण

				inbuf_ofs+=4;
				ofs += 4;
			पूर्ण
			/* Ran off end. */
			jffs2_dbg(1, "Empty flash to end of buffer at 0x%08x\n",
				  ofs);

			/* If we're only checking the beginning of a block with a cleanmarker,
			   bail now */
			अगर (buf_ofs == jeb->offset && jeb->used_size == PAD(c->cleanmarker_size) &&
			    c->cleanmarker_size && !jeb->dirty_size && !ref_next(jeb->first_node)) अणु
				jffs2_dbg(1, "%d bytes at start of block seems clean... assuming all clean\n",
					  EMPTY_SCAN_SIZE(c->sector_size));
				वापस BLK_STATE_CLEANMARKER;
			पूर्ण
			अगर (!buf_size && (scan_end != buf_len)) अणु/* XIP/poपूर्णांक हाल */
				scan_end = buf_len;
				जाओ more_empty;
			पूर्ण
			
			/* See how much more there is to पढ़ो in this eraseblock... */
			buf_len = min_t(uपूर्णांक32_t, buf_size, jeb->offset + c->sector_size - ofs);
			अगर (!buf_len) अणु
				/* No more to पढ़ो. Break out of मुख्य loop without marking
				   this range of empty space as dirty (because it's not) */
				jffs2_dbg(1, "Empty flash at %08x runs to end of block. Treating as free_space\n",
					  empty_start);
				अवरोध;
			पूर्ण
			/* poपूर्णांक never reaches here */
			scan_end = buf_len;
			jffs2_dbg(1, "Reading another 0x%x at 0x%08x\n",
				  buf_len, ofs);
			err = jffs2_fill_scan_buf(c, buf, ofs, buf_len);
			अगर (err)
				वापस err;
			buf_ofs = ofs;
			जाओ more_empty;
		पूर्ण

		अगर (ofs == jeb->offset && je16_to_cpu(node->magic) == KSAMTIB_CIGAM_2SFFJ) अणु
			pr_warn("Magic bitmask is backwards at offset 0x%08x. Wrong endian filesystem?\n",
				ofs);
			अगर ((err = jffs2_scan_dirty_space(c, jeb, 4)))
				वापस err;
			ofs += 4;
			जारी;
		पूर्ण
		अगर (je16_to_cpu(node->magic) == JFFS2_सूचीTY_BITMASK) अणु
			jffs2_dbg(1, "Dirty bitmask at 0x%08x\n", ofs);
			अगर ((err = jffs2_scan_dirty_space(c, jeb, 4)))
				वापस err;
			ofs += 4;
			जारी;
		पूर्ण
		अगर (je16_to_cpu(node->magic) == JFFS2_OLD_MAGIC_BITMASK) अणु
			pr_warn("Old JFFS2 bitmask found at 0x%08x\n", ofs);
			pr_warn("You cannot use older JFFS2 filesystems with newer kernels\n");
			अगर ((err = jffs2_scan_dirty_space(c, jeb, 4)))
				वापस err;
			ofs += 4;
			जारी;
		पूर्ण
		अगर (je16_to_cpu(node->magic) != JFFS2_MAGIC_BITMASK) अणु
			/* OK. We're out of possibilities. Whinge and move on */
			noisy_prपूर्णांकk(&noise, "%s(): Magic bitmask 0x%04x not found at 0x%08x: 0x%04x instead\n",
				     __func__,
				     JFFS2_MAGIC_BITMASK, ofs,
				     je16_to_cpu(node->magic));
			अगर ((err = jffs2_scan_dirty_space(c, jeb, 4)))
				वापस err;
			ofs += 4;
			जारी;
		पूर्ण
		/* We seem to have a node of sorts. Check the CRC */
		crcnode.magic = node->magic;
		crcnode.nodetype = cpu_to_je16( je16_to_cpu(node->nodetype) | JFFS2_NODE_ACCURATE);
		crcnode.totlen = node->totlen;
		hdr_crc = crc32(0, &crcnode, माप(crcnode)-4);

		अगर (hdr_crc != je32_to_cpu(node->hdr_crc)) अणु
			noisy_prपूर्णांकk(&noise, "%s(): Node at 0x%08x {0x%04x, 0x%04x, 0x%08x) has invalid CRC 0x%08x (calculated 0x%08x)\n",
				     __func__,
				     ofs, je16_to_cpu(node->magic),
				     je16_to_cpu(node->nodetype),
				     je32_to_cpu(node->totlen),
				     je32_to_cpu(node->hdr_crc),
				     hdr_crc);
			अगर ((err = jffs2_scan_dirty_space(c, jeb, 4)))
				वापस err;
			ofs += 4;
			जारी;
		पूर्ण

		अगर (ofs + je32_to_cpu(node->totlen) > jeb->offset + c->sector_size) अणु
			/* Eep. Node goes over the end of the erase block. */
			pr_warn("Node at 0x%08x with length 0x%08x would run over the end of the erase block\n",
				ofs, je32_to_cpu(node->totlen));
			pr_warn("Perhaps the file system was created with the wrong erase size?\n");
			अगर ((err = jffs2_scan_dirty_space(c, jeb, 4)))
				वापस err;
			ofs += 4;
			जारी;
		पूर्ण

		अगर (!(je16_to_cpu(node->nodetype) & JFFS2_NODE_ACCURATE)) अणु
			/* Wheee. This is an obsoleted node */
			jffs2_dbg(2, "Node at 0x%08x is obsolete. Skipping\n",
				  ofs);
			अगर ((err = jffs2_scan_dirty_space(c, jeb, PAD(je32_to_cpu(node->totlen)))))
				वापस err;
			ofs += PAD(je32_to_cpu(node->totlen));
			जारी;
		पूर्ण

		चयन(je16_to_cpu(node->nodetype)) अणु
		हाल JFFS2_NODETYPE_INODE:
			अगर (buf_ofs + buf_len < ofs + माप(काष्ठा jffs2_raw_inode)) अणु
				buf_len = min_t(uपूर्णांक32_t, buf_size, jeb->offset + c->sector_size - ofs);
				jffs2_dbg(1, "Fewer than %zd bytes (inode node) left to end of buf. Reading 0x%x at 0x%08x\n",
					  माप(काष्ठा jffs2_raw_inode),
					  buf_len, ofs);
				err = jffs2_fill_scan_buf(c, buf, ofs, buf_len);
				अगर (err)
					वापस err;
				buf_ofs = ofs;
				node = (व्योम *)buf;
			पूर्ण
			err = jffs2_scan_inode_node(c, jeb, (व्योम *)node, ofs, s);
			अगर (err) वापस err;
			ofs += PAD(je32_to_cpu(node->totlen));
			अवरोध;

		हाल JFFS2_NODETYPE_सूचीENT:
			अगर (buf_ofs + buf_len < ofs + je32_to_cpu(node->totlen)) अणु
				buf_len = min_t(uपूर्णांक32_t, buf_size, jeb->offset + c->sector_size - ofs);
				jffs2_dbg(1, "Fewer than %d bytes (dirent node) left to end of buf. Reading 0x%x at 0x%08x\n",
					  je32_to_cpu(node->totlen), buf_len,
					  ofs);
				err = jffs2_fill_scan_buf(c, buf, ofs, buf_len);
				अगर (err)
					वापस err;
				buf_ofs = ofs;
				node = (व्योम *)buf;
			पूर्ण
			err = jffs2_scan_dirent_node(c, jeb, (व्योम *)node, ofs, s);
			अगर (err) वापस err;
			ofs += PAD(je32_to_cpu(node->totlen));
			अवरोध;

#अगर_घोषित CONFIG_JFFS2_FS_XATTR
		हाल JFFS2_NODETYPE_XATTR:
			अगर (buf_ofs + buf_len < ofs + je32_to_cpu(node->totlen)) अणु
				buf_len = min_t(uपूर्णांक32_t, buf_size, jeb->offset + c->sector_size - ofs);
				jffs2_dbg(1, "Fewer than %d bytes (xattr node) left to end of buf. Reading 0x%x at 0x%08x\n",
					  je32_to_cpu(node->totlen), buf_len,
					  ofs);
				err = jffs2_fill_scan_buf(c, buf, ofs, buf_len);
				अगर (err)
					वापस err;
				buf_ofs = ofs;
				node = (व्योम *)buf;
			पूर्ण
			err = jffs2_scan_xattr_node(c, jeb, (व्योम *)node, ofs, s);
			अगर (err)
				वापस err;
			ofs += PAD(je32_to_cpu(node->totlen));
			अवरोध;
		हाल JFFS2_NODETYPE_XREF:
			अगर (buf_ofs + buf_len < ofs + je32_to_cpu(node->totlen)) अणु
				buf_len = min_t(uपूर्णांक32_t, buf_size, jeb->offset + c->sector_size - ofs);
				jffs2_dbg(1, "Fewer than %d bytes (xref node) left to end of buf. Reading 0x%x at 0x%08x\n",
					  je32_to_cpu(node->totlen), buf_len,
					  ofs);
				err = jffs2_fill_scan_buf(c, buf, ofs, buf_len);
				अगर (err)
					वापस err;
				buf_ofs = ofs;
				node = (व्योम *)buf;
			पूर्ण
			err = jffs2_scan_xref_node(c, jeb, (व्योम *)node, ofs, s);
			अगर (err)
				वापस err;
			ofs += PAD(je32_to_cpu(node->totlen));
			अवरोध;
#पूर्ण_अगर	/* CONFIG_JFFS2_FS_XATTR */

		हाल JFFS2_NODETYPE_CLEANMARKER:
			jffs2_dbg(1, "CLEANMARKER node found at 0x%08x\n", ofs);
			अगर (je32_to_cpu(node->totlen) != c->cleanmarker_size) अणु
				pr_notice("CLEANMARKER node found at 0x%08x has totlen 0x%x != normal 0x%x\n",
					  ofs, je32_to_cpu(node->totlen),
					  c->cleanmarker_size);
				अगर ((err = jffs2_scan_dirty_space(c, jeb, PAD(माप(काष्ठा jffs2_unknown_node)))))
					वापस err;
				ofs += PAD(माप(काष्ठा jffs2_unknown_node));
			पूर्ण अन्यथा अगर (jeb->first_node) अणु
				pr_notice("CLEANMARKER node found at 0x%08x, not first node in block (0x%08x)\n",
					  ofs, jeb->offset);
				अगर ((err = jffs2_scan_dirty_space(c, jeb, PAD(माप(काष्ठा jffs2_unknown_node)))))
					वापस err;
				ofs += PAD(माप(काष्ठा jffs2_unknown_node));
			पूर्ण अन्यथा अणु
				jffs2_link_node_ref(c, jeb, ofs | REF_NORMAL, c->cleanmarker_size, शून्य);

				ofs += PAD(c->cleanmarker_size);
			पूर्ण
			अवरोध;

		हाल JFFS2_NODETYPE_PADDING:
			अगर (jffs2_sum_active())
				jffs2_sum_add_padding_mem(s, je32_to_cpu(node->totlen));
			अगर ((err = jffs2_scan_dirty_space(c, jeb, PAD(je32_to_cpu(node->totlen)))))
				वापस err;
			ofs += PAD(je32_to_cpu(node->totlen));
			अवरोध;

		शेष:
			चयन (je16_to_cpu(node->nodetype) & JFFS2_COMPAT_MASK) अणु
			हाल JFFS2_FEATURE_ROCOMPAT:
				pr_notice("Read-only compatible feature node (0x%04x) found at offset 0x%08x\n",
					  je16_to_cpu(node->nodetype), ofs);
				c->flags |= JFFS2_SB_FLAG_RO;
				अगर (!(jffs2_is_पढ़ोonly(c)))
					वापस -EROFS;
				अगर ((err = jffs2_scan_dirty_space(c, jeb, PAD(je32_to_cpu(node->totlen)))))
					वापस err;
				ofs += PAD(je32_to_cpu(node->totlen));
				अवरोध;

			हाल JFFS2_FEATURE_INCOMPAT:
				pr_notice("Incompatible feature node (0x%04x) found at offset 0x%08x\n",
					  je16_to_cpu(node->nodetype), ofs);
				वापस -EINVAL;

			हाल JFFS2_FEATURE_RWCOMPAT_DELETE:
				jffs2_dbg(1, "Unknown but compatible feature node (0x%04x) found at offset 0x%08x\n",
					  je16_to_cpu(node->nodetype), ofs);
				अगर ((err = jffs2_scan_dirty_space(c, jeb, PAD(je32_to_cpu(node->totlen)))))
					वापस err;
				ofs += PAD(je32_to_cpu(node->totlen));
				अवरोध;

			हाल JFFS2_FEATURE_RWCOMPAT_COPY: अणु
				jffs2_dbg(1, "Unknown but compatible feature node (0x%04x) found at offset 0x%08x\n",
					  je16_to_cpu(node->nodetype), ofs);

				jffs2_link_node_ref(c, jeb, ofs | REF_PRISTINE, PAD(je32_to_cpu(node->totlen)), शून्य);

				/* We can't summarise nodes we don't grok */
				jffs2_sum_disable_collecting(s);
				ofs += PAD(je32_to_cpu(node->totlen));
				अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (jffs2_sum_active()) अणु
		अगर (PAD(s->sum_size + JFFS2_SUMMARY_FRAME_SIZE) > jeb->मुक्त_size) अणु
			dbg_summary("There is not enough space for "
				"summary information, disabling for this jeb!\n");
			jffs2_sum_disable_collecting(s);
		पूर्ण
	पूर्ण

	jffs2_dbg(1, "Block at 0x%08x: free 0x%08x, dirty 0x%08x, unchecked 0x%08x, used 0x%08x, wasted 0x%08x\n",
		  jeb->offset, jeb->मुक्त_size, jeb->dirty_size,
		  jeb->unchecked_size, jeb->used_size, jeb->wasted_size);
	
	/* mark_node_obsolete can add to wasted !! */
	अगर (jeb->wasted_size) अणु
		jeb->dirty_size += jeb->wasted_size;
		c->dirty_size += jeb->wasted_size;
		c->wasted_size -= jeb->wasted_size;
		jeb->wasted_size = 0;
	पूर्ण

	वापस jffs2_scan_classअगरy_jeb(c, jeb);
पूर्ण

काष्ठा jffs2_inode_cache *jffs2_scan_make_ino_cache(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t ino)
अणु
	काष्ठा jffs2_inode_cache *ic;

	ic = jffs2_get_ino_cache(c, ino);
	अगर (ic)
		वापस ic;

	अगर (ino > c->highest_ino)
		c->highest_ino = ino;

	ic = jffs2_alloc_inode_cache();
	अगर (!ic) अणु
		pr_notice("%s(): allocation of inode cache failed\n", __func__);
		वापस शून्य;
	पूर्ण
	स_रखो(ic, 0, माप(*ic));

	ic->ino = ino;
	ic->nodes = (व्योम *)ic;
	jffs2_add_ino_cache(c, ic);
	अगर (ino == 1)
		ic->pino_nlink = 1;
	वापस ic;
पूर्ण

अटल पूर्णांक jffs2_scan_inode_node(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				 काष्ठा jffs2_raw_inode *ri, uपूर्णांक32_t ofs, काष्ठा jffs2_summary *s)
अणु
	काष्ठा jffs2_inode_cache *ic;
	uपूर्णांक32_t crc, ino = je32_to_cpu(ri->ino);

	jffs2_dbg(1, "%s(): Node at 0x%08x\n", __func__, ofs);

	/* We करो very little here now. Just check the ino# to which we should attribute
	   this node; we can करो all the CRC checking etc. later. There's a tradeoff here --
	   we used to scan the flash once only, पढ़ोing everything we want from it पूर्णांकo
	   memory, then building all our in-core data काष्ठाures and मुक्तing the extra
	   inक्रमmation. Now we allow the first part of the mount to complete a lot quicker,
	   but we have to go _back_ to the flash in order to finish the CRC checking, etc.
	   Which means that the _full_ amount of समय to get to proper ग_लिखो mode with GC
	   operational may actually be _दीर्घer_ than beक्रमe. Sucks to be me. */

	/* Check the node CRC in any हाल. */
	crc = crc32(0, ri, माप(*ri)-8);
	अगर (crc != je32_to_cpu(ri->node_crc)) अणु
		pr_notice("%s(): CRC failed on node at 0x%08x: Read 0x%08x, calculated 0x%08x\n",
			  __func__, ofs, je32_to_cpu(ri->node_crc), crc);
		/*
		 * We believe totlen because the CRC on the node
		 * _header_ was OK, just the node itself failed.
		 */
		वापस jffs2_scan_dirty_space(c, jeb,
					      PAD(je32_to_cpu(ri->totlen)));
	पूर्ण

	ic = jffs2_get_ino_cache(c, ino);
	अगर (!ic) अणु
		ic = jffs2_scan_make_ino_cache(c, ino);
		अगर (!ic)
			वापस -ENOMEM;
	पूर्ण

	/* Wheee. It worked */
	jffs2_link_node_ref(c, jeb, ofs | REF_UNCHECKED, PAD(je32_to_cpu(ri->totlen)), ic);

	jffs2_dbg(1, "Node is ino #%u, version %d. Range 0x%x-0x%x\n",
		  je32_to_cpu(ri->ino), je32_to_cpu(ri->version),
		  je32_to_cpu(ri->offset),
		  je32_to_cpu(ri->offset)+je32_to_cpu(ri->dsize));

	pseuकरो_अक्रमom += je32_to_cpu(ri->version);

	अगर (jffs2_sum_active()) अणु
		jffs2_sum_add_inode_mem(s, ri, ofs - jeb->offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jffs2_scan_dirent_node(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				  काष्ठा jffs2_raw_dirent *rd, uपूर्णांक32_t ofs, काष्ठा jffs2_summary *s)
अणु
	काष्ठा jffs2_full_dirent *fd;
	काष्ठा jffs2_inode_cache *ic;
	uपूर्णांक32_t checkedlen;
	uपूर्णांक32_t crc;
	पूर्णांक err;

	jffs2_dbg(1, "%s(): Node at 0x%08x\n", __func__, ofs);

	/* We करोn't get here unless the node is still valid, so we don't have to
	   mask in the ACCURATE bit any more. */
	crc = crc32(0, rd, माप(*rd)-8);

	अगर (crc != je32_to_cpu(rd->node_crc)) अणु
		pr_notice("%s(): Node CRC failed on node at 0x%08x: Read 0x%08x, calculated 0x%08x\n",
			  __func__, ofs, je32_to_cpu(rd->node_crc), crc);
		/* We believe totlen because the CRC on the node _header_ was OK, just the node itself failed. */
		अगर ((err = jffs2_scan_dirty_space(c, jeb, PAD(je32_to_cpu(rd->totlen)))))
			वापस err;
		वापस 0;
	पूर्ण

	pseuकरो_अक्रमom += je32_to_cpu(rd->version);

	/* Should never happen. Did. (OLPC trac #4184)*/
	checkedlen = strnlen(rd->name, rd->nsize);
	अगर (checkedlen < rd->nsize) अणु
		pr_err("Dirent at %08x has zeroes in name. Truncating to %d chars\n",
		       ofs, checkedlen);
	पूर्ण
	fd = jffs2_alloc_full_dirent(checkedlen+1);
	अगर (!fd) अणु
		वापस -ENOMEM;
	पूर्ण
	स_नकल(&fd->name, rd->name, checkedlen);
	fd->name[checkedlen] = 0;

	crc = crc32(0, fd->name, checkedlen);
	अगर (crc != je32_to_cpu(rd->name_crc)) अणु
		pr_notice("%s(): Name CRC failed on node at 0x%08x: Read 0x%08x, calculated 0x%08x\n",
			  __func__, ofs, je32_to_cpu(rd->name_crc), crc);
		jffs2_dbg(1, "Name for which CRC failed is (now) '%s', ino #%d\n",
			  fd->name, je32_to_cpu(rd->ino));
		jffs2_मुक्त_full_dirent(fd);
		/* FIXME: Why करो we believe totlen? */
		/* We believe totlen because the CRC on the node _header_ was OK, just the name failed. */
		अगर ((err = jffs2_scan_dirty_space(c, jeb, PAD(je32_to_cpu(rd->totlen)))))
			वापस err;
		वापस 0;
	पूर्ण
	ic = jffs2_scan_make_ino_cache(c, je32_to_cpu(rd->pino));
	अगर (!ic) अणु
		jffs2_मुक्त_full_dirent(fd);
		वापस -ENOMEM;
	पूर्ण

	fd->raw = jffs2_link_node_ref(c, jeb, ofs | dirent_node_state(rd),
				      PAD(je32_to_cpu(rd->totlen)), ic);

	fd->next = शून्य;
	fd->version = je32_to_cpu(rd->version);
	fd->ino = je32_to_cpu(rd->ino);
	fd->nhash = full_name_hash(शून्य, fd->name, checkedlen);
	fd->type = rd->type;
	jffs2_add_fd_to_list(c, fd, &ic->scan_dents);

	अगर (jffs2_sum_active()) अणु
		jffs2_sum_add_dirent_mem(s, rd, ofs - jeb->offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक count_list(काष्ठा list_head *l)
अणु
	uपूर्णांक32_t count = 0;
	काष्ठा list_head *पंचांगp;

	list_क्रम_each(पंचांगp, l) अणु
		count++;
	पूर्ण
	वापस count;
पूर्ण

/* Note: This अवरोधs अगर list_empty(head). I करोn't care. You
   might, अगर you copy this code and use it अन्यथाwhere :) */
अटल व्योम rotate_list(काष्ठा list_head *head, uपूर्णांक32_t count)
अणु
	काष्ठा list_head *n = head->next;

	list_del(head);
	जबतक(count--) अणु
		n = n->next;
	पूर्ण
	list_add(head, n);
पूर्ण

व्योम jffs2_rotate_lists(काष्ठा jffs2_sb_info *c)
अणु
	uपूर्णांक32_t x;
	uपूर्णांक32_t rotateby;

	x = count_list(&c->clean_list);
	अगर (x) अणु
		rotateby = pseuकरो_अक्रमom % x;
		rotate_list((&c->clean_list), rotateby);
	पूर्ण

	x = count_list(&c->very_dirty_list);
	अगर (x) अणु
		rotateby = pseuकरो_अक्रमom % x;
		rotate_list((&c->very_dirty_list), rotateby);
	पूर्ण

	x = count_list(&c->dirty_list);
	अगर (x) अणु
		rotateby = pseuकरो_अक्रमom % x;
		rotate_list((&c->dirty_list), rotateby);
	पूर्ण

	x = count_list(&c->erasable_list);
	अगर (x) अणु
		rotateby = pseuकरो_अक्रमom % x;
		rotate_list((&c->erasable_list), rotateby);
	पूर्ण

	अगर (c->nr_erasing_blocks) अणु
		rotateby = pseuकरो_अक्रमom % c->nr_erasing_blocks;
		rotate_list((&c->erase_pending_list), rotateby);
	पूर्ण

	अगर (c->nr_मुक्त_blocks) अणु
		rotateby = pseuकरो_अक्रमom % c->nr_मुक्त_blocks;
		rotate_list((&c->मुक्त_list), rotateby);
	पूर्ण
पूर्ण
