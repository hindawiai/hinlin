<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004 Thomas Gleixner <tglx@linutronix.de>
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 * Modअगरied debugged and enhanced by Thomas Gleixner <tglx@linutronix.de>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/crc32.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sched.h>
#समावेश <linux/ग_लिखोback.h>

#समावेश "nodelist.h"

/* For testing ग_लिखो failures */
#अघोषित BREAKME
#अघोषित BREAKMEHEADER

#अगर_घोषित BREAKME
अटल अचिन्हित अक्षर *brokenbuf;
#पूर्ण_अगर

#घोषणा PAGE_DIV(x) ( ((अचिन्हित दीर्घ)(x) / (अचिन्हित दीर्घ)(c->wbuf_pagesize)) * (अचिन्हित दीर्घ)(c->wbuf_pagesize) )
#घोषणा PAGE_MOD(x) ( (अचिन्हित दीर्घ)(x) % (अचिन्हित दीर्घ)(c->wbuf_pagesize) )

/* max. erase failures beक्रमe we mark a block bad */
#घोषणा MAX_ERASE_FAILURES 	2

काष्ठा jffs2_inodirty अणु
	uपूर्णांक32_t ino;
	काष्ठा jffs2_inodirty *next;
पूर्ण;

अटल काष्ठा jffs2_inodirty inodirty_nomem;

अटल पूर्णांक jffs2_wbuf_pending_क्रम_ino(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t ino)
अणु
	काष्ठा jffs2_inodirty *this = c->wbuf_inodes;

	/* If a दो_स्मृति failed, consider _everything_ dirty */
	अगर (this == &inodirty_nomem)
		वापस 1;

	/* If ino == 0, _any_ non-GC ग_लिखोs mean 'yes' */
	अगर (this && !ino)
		वापस 1;

	/* Look to see अगर the inode in question is pending in the wbuf */
	जबतक (this) अणु
		अगर (this->ino == ino)
			वापस 1;
		this = this->next;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम jffs2_clear_wbuf_ino_list(काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा jffs2_inodirty *this;

	this = c->wbuf_inodes;

	अगर (this != &inodirty_nomem) अणु
		जबतक (this) अणु
			काष्ठा jffs2_inodirty *next = this->next;
			kमुक्त(this);
			this = next;
		पूर्ण
	पूर्ण
	c->wbuf_inodes = शून्य;
पूर्ण

अटल व्योम jffs2_wbuf_dirties_inode(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t ino)
अणु
	काष्ठा jffs2_inodirty *new;

	/* Schedule delayed ग_लिखो-buffer ग_लिखो-out */
	jffs2_dirty_trigger(c);

	अगर (jffs2_wbuf_pending_क्रम_ino(c, ino))
		वापस;

	new = kदो_स्मृति(माप(*new), GFP_KERNEL);
	अगर (!new) अणु
		jffs2_dbg(1, "No memory to allocate inodirty. Fallback to all considered dirty\n");
		jffs2_clear_wbuf_ino_list(c);
		c->wbuf_inodes = &inodirty_nomem;
		वापस;
	पूर्ण
	new->ino = ino;
	new->next = c->wbuf_inodes;
	c->wbuf_inodes = new;
	वापस;
पूर्ण

अटल अंतरभूत व्योम jffs2_refile_wbuf_blocks(काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा list_head *this, *next;
	अटल पूर्णांक n;

	अगर (list_empty(&c->erasable_pending_wbuf_list))
		वापस;

	list_क्रम_each_safe(this, next, &c->erasable_pending_wbuf_list) अणु
		काष्ठा jffs2_eraseblock *jeb = list_entry(this, काष्ठा jffs2_eraseblock, list);

		jffs2_dbg(1, "Removing eraseblock at 0x%08x from erasable_pending_wbuf_list...\n",
			  jeb->offset);
		list_del(this);
		अगर ((jअगरfies + (n++)) & 127) अणु
			/* Most of the समय, we just erase it immediately. Otherwise we
			   spend ages scanning it on mount, etc. */
			jffs2_dbg(1, "...and adding to erase_pending_list\n");
			list_add_tail(&jeb->list, &c->erase_pending_list);
			c->nr_erasing_blocks++;
			jffs2_garbage_collect_trigger(c);
		पूर्ण अन्यथा अणु
			/* Someबार, however, we leave it अन्यथाwhere so it करोesn't get
			   immediately reused, and we spपढ़ो the load a bit. */
			jffs2_dbg(1, "...and adding to erasable_list\n");
			list_add_tail(&jeb->list, &c->erasable_list);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा REखाता_NOTEMPTY 0
#घोषणा REखाता_ANYWAY   1

अटल व्योम jffs2_block_refile(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb, पूर्णांक allow_empty)
अणु
	jffs2_dbg(1, "About to refile bad block at %08x\n", jeb->offset);

	/* File the existing block on the bad_used_list.... */
	अगर (c->nextblock == jeb)
		c->nextblock = शून्य;
	अन्यथा /* Not sure this should ever happen... need more coffee */
		list_del(&jeb->list);
	अगर (jeb->first_node) अणु
		jffs2_dbg(1, "Refiling block at %08x to bad_used_list\n",
			  jeb->offset);
		list_add(&jeb->list, &c->bad_used_list);
	पूर्ण अन्यथा अणु
		BUG_ON(allow_empty == REखाता_NOTEMPTY);
		/* It has to have had some nodes or we couldn't be here */
		jffs2_dbg(1, "Refiling block at %08x to erase_pending_list\n",
			  jeb->offset);
		list_add(&jeb->list, &c->erase_pending_list);
		c->nr_erasing_blocks++;
		jffs2_garbage_collect_trigger(c);
	पूर्ण

	अगर (!jffs2_pपुनः_स्मृति_raw_node_refs(c, jeb, 1)) अणु
		uपूर्णांक32_t oldमुक्त = jeb->मुक्त_size;

		jffs2_link_node_ref(c, jeb, 
				    (jeb->offset+c->sector_size-oldमुक्त) | REF_OBSOLETE,
				    oldमुक्त, शून्य);
		/* convert to wasted */
		c->wasted_size += oldमुक्त;
		jeb->wasted_size += oldमुक्त;
		c->dirty_size -= oldमुक्त;
		jeb->dirty_size -= oldमुक्त;
	पूर्ण

	jffs2_dbg_dump_block_lists_nolock(c);
	jffs2_dbg_acct_sanity_check_nolock(c,jeb);
	jffs2_dbg_acct_paranoia_check_nolock(c, jeb);
पूर्ण

अटल काष्ठा jffs2_raw_node_ref **jffs2_incore_replace_raw(काष्ठा jffs2_sb_info *c,
							    काष्ठा jffs2_inode_info *f,
							    काष्ठा jffs2_raw_node_ref *raw,
							    जोड़ jffs2_node_जोड़ *node)
अणु
	काष्ठा jffs2_node_frag *frag;
	काष्ठा jffs2_full_dirent *fd;

	dbg_noderef("incore_replace_raw: node at %p is {%04x,%04x}\n",
		    node, je16_to_cpu(node->u.magic), je16_to_cpu(node->u.nodetype));

	BUG_ON(je16_to_cpu(node->u.magic) != 0x1985 &&
	       je16_to_cpu(node->u.magic) != 0);

	चयन (je16_to_cpu(node->u.nodetype)) अणु
	हाल JFFS2_NODETYPE_INODE:
		अगर (f->metadata && f->metadata->raw == raw) अणु
			dbg_noderef("Will replace ->raw in f->metadata at %p\n", f->metadata);
			वापस &f->metadata->raw;
		पूर्ण
		frag = jffs2_lookup_node_frag(&f->fragtree, je32_to_cpu(node->i.offset));
		BUG_ON(!frag);
		/* Find a frag which refers to the full_dnode we want to modअगरy */
		जबतक (!frag->node || frag->node->raw != raw) अणु
			frag = frag_next(frag);
			BUG_ON(!frag);
		पूर्ण
		dbg_noderef("Will replace ->raw in full_dnode at %p\n", frag->node);
		वापस &frag->node->raw;

	हाल JFFS2_NODETYPE_सूचीENT:
		क्रम (fd = f->dents; fd; fd = fd->next) अणु
			अगर (fd->raw == raw) अणु
				dbg_noderef("Will replace ->raw in full_dirent at %p\n", fd);
				वापस &fd->raw;
			पूर्ण
		पूर्ण
		BUG();

	शेष:
		dbg_noderef("Don't care about replacing raw for nodetype %x\n",
			    je16_to_cpu(node->u.nodetype));
		अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_JFFS2_FS_WBUF_VERIFY
अटल पूर्णांक jffs2_verअगरy_ग_लिखो(काष्ठा jffs2_sb_info *c, अचिन्हित अक्षर *buf,
			      uपूर्णांक32_t ofs)
अणु
	पूर्णांक ret;
	माप_प्रकार retlen;
	अक्षर *eccstr;

	ret = mtd_पढ़ो(c->mtd, ofs, c->wbuf_pagesize, &retlen, c->wbuf_verअगरy);
	अगर (ret && ret != -EUCLEAN && ret != -EBADMSG) अणु
		pr_warn("%s(): Read back of page at %08x failed: %d\n",
			__func__, c->wbuf_ofs, ret);
		वापस ret;
	पूर्ण अन्यथा अगर (retlen != c->wbuf_pagesize) अणु
		pr_warn("%s(): Read back of page at %08x gave short read: %zd not %d\n",
			__func__, ofs, retlen, c->wbuf_pagesize);
		वापस -EIO;
	पूर्ण
	अगर (!स_भेद(buf, c->wbuf_verअगरy, c->wbuf_pagesize))
		वापस 0;

	अगर (ret == -EUCLEAN)
		eccstr = "corrected";
	अन्यथा अगर (ret == -EBADMSG)
		eccstr = "correction failed";
	अन्यथा
		eccstr = "OK or unused";

	pr_warn("Write verify error (ECC %s) at %08x. Wrote:\n",
		eccstr, c->wbuf_ofs);
	prपूर्णांक_hex_dump(KERN_WARNING, "", DUMP_PREFIX_OFFSET, 16, 1,
		       c->wbuf, c->wbuf_pagesize, 0);

	pr_warn("Read back:\n");
	prपूर्णांक_hex_dump(KERN_WARNING, "", DUMP_PREFIX_OFFSET, 16, 1,
		       c->wbuf_verअगरy, c->wbuf_pagesize, 0);

	वापस -EIO;
पूर्ण
#अन्यथा
#घोषणा jffs2_verअगरy_ग_लिखो(c,b,o) (0)
#पूर्ण_अगर

/* Recover from failure to ग_लिखो wbuf. Recover the nodes up to the
 * wbuf, not the one which we were starting to try to ग_लिखो. */

अटल व्योम jffs2_wbuf_recover(काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा jffs2_eraseblock *jeb, *new_jeb;
	काष्ठा jffs2_raw_node_ref *raw, *next, *first_raw = शून्य;
	माप_प्रकार retlen;
	पूर्णांक ret;
	पूर्णांक nr_refile = 0;
	अचिन्हित अक्षर *buf;
	uपूर्णांक32_t start, end, ofs, len;

	jeb = &c->blocks[c->wbuf_ofs / c->sector_size];

	spin_lock(&c->erase_completion_lock);
	अगर (c->wbuf_ofs % c->mtd->erasesize)
		jffs2_block_refile(c, jeb, REखाता_NOTEMPTY);
	अन्यथा
		jffs2_block_refile(c, jeb, REखाता_ANYWAY);
	spin_unlock(&c->erase_completion_lock);

	BUG_ON(!ref_obsolete(jeb->last_node));

	/* Find the first node to be recovered, by skipping over every
	   node which ends beक्रमe the wbuf starts, or which is obsolete. */
	क्रम (next = raw = jeb->first_node; next; raw = next) अणु
		next = ref_next(raw);

		अगर (ref_obsolete(raw) || 
		    (next && ref_offset(next) <= c->wbuf_ofs)) अणु
			dbg_noderef("Skipping node at 0x%08x(%d)-0x%08x which is either before 0x%08x or obsolete\n",
				    ref_offset(raw), ref_flags(raw),
				    (ref_offset(raw) + ref_totlen(c, jeb, raw)),
				    c->wbuf_ofs);
			जारी;
		पूर्ण
		dbg_noderef("First node to be recovered is at 0x%08x(%d)-0x%08x\n",
			    ref_offset(raw), ref_flags(raw),
			    (ref_offset(raw) + ref_totlen(c, jeb, raw)));

		first_raw = raw;
		अवरोध;
	पूर्ण

	अगर (!first_raw) अणु
		/* All nodes were obsolete. Nothing to recover. */
		jffs2_dbg(1, "No non-obsolete nodes to be recovered. Just filing block bad\n");
		c->wbuf_len = 0;
		वापस;
	पूर्ण

	start = ref_offset(first_raw);
	end = ref_offset(jeb->last_node);
	nr_refile = 1;

	/* Count the number of refs which need to be copied */
	जबतक ((raw = ref_next(raw)) != jeb->last_node)
		nr_refile++;

	dbg_noderef("wbuf recover %08x-%08x (%d bytes in %d nodes)\n",
		    start, end, end - start, nr_refile);

	buf = शून्य;
	अगर (start < c->wbuf_ofs) अणु
		/* First affected node was alपढ़ोy partially written.
		 * Attempt to reपढ़ो the old data पूर्णांकo our buffer. */

		buf = kदो_स्मृति(end - start, GFP_KERNEL);
		अगर (!buf) अणु
			pr_crit("Malloc failure in wbuf recovery. Data loss ensues.\n");

			जाओ पढ़ो_failed;
		पूर्ण

		/* Do the पढ़ो... */
		ret = mtd_पढ़ो(c->mtd, start, c->wbuf_ofs - start, &retlen,
			       buf);

		/* ECC recovered ? */
		अगर ((ret == -EUCLEAN || ret == -EBADMSG) &&
		    (retlen == c->wbuf_ofs - start))
			ret = 0;

		अगर (ret || retlen != c->wbuf_ofs - start) अणु
			pr_crit("Old data are already lost in wbuf recovery. Data loss ensues.\n");

			kमुक्त(buf);
			buf = शून्य;
		पढ़ो_failed:
			first_raw = ref_next(first_raw);
			nr_refile--;
			जबतक (first_raw && ref_obsolete(first_raw)) अणु
				first_raw = ref_next(first_raw);
				nr_refile--;
			पूर्ण

			/* If this was the only node to be recovered, give up */
			अगर (!first_raw) अणु
				c->wbuf_len = 0;
				वापस;
			पूर्ण

			/* It wasn't. Go on and try to recover nodes complete in the wbuf */
			start = ref_offset(first_raw);
			dbg_noderef("wbuf now recover %08x-%08x (%d bytes in %d nodes)\n",
				    start, end, end - start, nr_refile);

		पूर्ण अन्यथा अणु
			/* Read succeeded. Copy the reमुख्यing data from the wbuf */
			स_नकल(buf + (c->wbuf_ofs - start), c->wbuf, end - c->wbuf_ofs);
		पूर्ण
	पूर्ण
	/* OK... we're to reग_लिखो (end-start) bytes of data from first_raw onwards.
	   Either 'buf' contains the data, or we find it in the wbuf */

	/* ... and get an allocation of space from a shiny new block instead */
	ret = jffs2_reserve_space_gc(c, end-start, &len, JFFS2_SUMMARY_NOSUM_SIZE);
	अगर (ret) अणु
		pr_warn("Failed to allocate space for wbuf recovery. Data loss ensues.\n");
		kमुक्त(buf);
		वापस;
	पूर्ण

	/* The summary is not recovered, so it must be disabled क्रम this erase block */
	jffs2_sum_disable_collecting(c->summary);

	ret = jffs2_pपुनः_स्मृति_raw_node_refs(c, c->nextblock, nr_refile);
	अगर (ret) अणु
		pr_warn("Failed to allocate node refs for wbuf recovery. Data loss ensues.\n");
		kमुक्त(buf);
		वापस;
	पूर्ण

	ofs = ग_लिखो_ofs(c);

	अगर (end-start >= c->wbuf_pagesize) अणु
		/* Need to करो another ग_लिखो immediately, but it's possible
		   that this is just because the wbuf itself is completely
		   full, and there's nothing earlier पढ़ो back from the
		   flash. Hence 'buf' isn't necessarily what we're writing
		   from. */
		अचिन्हित अक्षर *reग_लिखो_buf = buf?:c->wbuf;
		uपूर्णांक32_t toग_लिखो = (end-start) - ((end-start)%c->wbuf_pagesize);

		jffs2_dbg(1, "Write 0x%x bytes at 0x%08x in wbuf recover\n",
			  toग_लिखो, ofs);

#अगर_घोषित BREAKMEHEADER
		अटल पूर्णांक अवरोधme;
		अगर (अवरोधme++ == 20) अणु
			pr_notice("Faking write error at 0x%08x\n", ofs);
			अवरोधme = 0;
			mtd_ग_लिखो(c->mtd, ofs, toग_लिखो, &retlen, brokenbuf);
			ret = -EIO;
		पूर्ण अन्यथा
#पूर्ण_अगर
			ret = mtd_ग_लिखो(c->mtd, ofs, toग_लिखो, &retlen,
					reग_लिखो_buf);

		अगर (ret || retlen != toग_लिखो || jffs2_verअगरy_ग_लिखो(c, reग_लिखो_buf, ofs)) अणु
			/* Argh. We tried. Really we did. */
			pr_crit("Recovery of wbuf failed due to a second write error\n");
			kमुक्त(buf);

			अगर (retlen)
				jffs2_add_physical_node_ref(c, ofs | REF_OBSOLETE, ref_totlen(c, jeb, first_raw), शून्य);

			वापस;
		पूर्ण
		pr_notice("Recovery of wbuf succeeded to %08x\n", ofs);

		c->wbuf_len = (end - start) - toग_लिखो;
		c->wbuf_ofs = ofs + toग_लिखो;
		स_हटाओ(c->wbuf, reग_लिखो_buf + toग_लिखो, c->wbuf_len);
		/* Don't muck about with c->wbuf_inodes. False positives are harmless. */
	पूर्ण अन्यथा अणु
		/* OK, now we're left with the dregs in whichever buffer we're using */
		अगर (buf) अणु
			स_नकल(c->wbuf, buf, end-start);
		पूर्ण अन्यथा अणु
			स_हटाओ(c->wbuf, c->wbuf + (start - c->wbuf_ofs), end - start);
		पूर्ण
		c->wbuf_ofs = ofs;
		c->wbuf_len = end - start;
	पूर्ण

	/* Now sort out the jffs2_raw_node_refs, moving them from the old to the next block */
	new_jeb = &c->blocks[ofs / c->sector_size];

	spin_lock(&c->erase_completion_lock);
	क्रम (raw = first_raw; raw != jeb->last_node; raw = ref_next(raw)) अणु
		uपूर्णांक32_t rawlen = ref_totlen(c, jeb, raw);
		काष्ठा jffs2_inode_cache *ic;
		काष्ठा jffs2_raw_node_ref *new_ref;
		काष्ठा jffs2_raw_node_ref **adjust_ref = शून्य;
		काष्ठा jffs2_inode_info *f = शून्य;

		jffs2_dbg(1, "Refiling block of %08x at %08x(%d) to %08x\n",
			  rawlen, ref_offset(raw), ref_flags(raw), ofs);

		ic = jffs2_raw_ref_to_ic(raw);

		/* Ick. This XATTR mess should be fixed लघुly... */
		अगर (ic && ic->class == RAWNODE_CLASS_XATTR_DATUM) अणु
			काष्ठा jffs2_xattr_datum *xd = (व्योम *)ic;
			BUG_ON(xd->node != raw);
			adjust_ref = &xd->node;
			raw->next_in_ino = शून्य;
			ic = शून्य;
		पूर्ण अन्यथा अगर (ic && ic->class == RAWNODE_CLASS_XATTR_REF) अणु
			काष्ठा jffs2_xattr_datum *xr = (व्योम *)ic;
			BUG_ON(xr->node != raw);
			adjust_ref = &xr->node;
			raw->next_in_ino = शून्य;
			ic = शून्य;
		पूर्ण अन्यथा अगर (ic && ic->class == RAWNODE_CLASS_INODE_CACHE) अणु
			काष्ठा jffs2_raw_node_ref **p = &ic->nodes;

			/* Remove the old node from the per-inode list */
			जबतक (*p && *p != (व्योम *)ic) अणु
				अगर (*p == raw) अणु
					(*p) = (raw->next_in_ino);
					raw->next_in_ino = शून्य;
					अवरोध;
				पूर्ण
				p = &((*p)->next_in_ino);
			पूर्ण

			अगर (ic->state == INO_STATE_PRESENT && !ref_obsolete(raw)) अणु
				/* If it's an in-core inode, then we have to adjust any
				   full_dirent or full_dnode काष्ठाure to poपूर्णांक to the
				   new version instead of the old */
				f = jffs2_gc_fetch_inode(c, ic->ino, !ic->pino_nlink);
				अगर (IS_ERR(f)) अणु
					/* Should never happen; it _must_ be present */
					JFFS2_ERROR("Failed to iget() ino #%u, err %ld\n",
						    ic->ino, PTR_ERR(f));
					BUG();
				पूर्ण
				/* We करोn't lock f->sem. There's a number of ways we could
				   end up in here with it alपढ़ोy being locked, and nobody's
				   going to modअगरy it on us anyway because we hold the
				   alloc_sem. We're only changing one ->raw poपूर्णांकer too,
				   which we can get away with without upsetting पढ़ोers. */
				adjust_ref = jffs2_incore_replace_raw(c, f, raw,
								      (व्योम *)(buf?:c->wbuf) + (ref_offset(raw) - start));
			पूर्ण अन्यथा अगर (unlikely(ic->state != INO_STATE_PRESENT &&
					    ic->state != INO_STATE_CHECKEDABSENT &&
					    ic->state != INO_STATE_GC)) अणु
				JFFS2_ERROR("Inode #%u is in strange state %d!\n", ic->ino, ic->state);
				BUG();
			पूर्ण
		पूर्ण

		new_ref = jffs2_link_node_ref(c, new_jeb, ofs | ref_flags(raw), rawlen, ic);

		अगर (adjust_ref) अणु
			BUG_ON(*adjust_ref != raw);
			*adjust_ref = new_ref;
		पूर्ण
		अगर (f)
			jffs2_gc_release_inode(c, f);

		अगर (!ref_obsolete(raw)) अणु
			jeb->dirty_size += rawlen;
			jeb->used_size  -= rawlen;
			c->dirty_size += rawlen;
			c->used_size -= rawlen;
			raw->flash_offset = ref_offset(raw) | REF_OBSOLETE;
			BUG_ON(raw->next_in_ino);
		पूर्ण
		ofs += rawlen;
	पूर्ण

	kमुक्त(buf);

	/* Fix up the original jeb now it's on the bad_list */
	अगर (first_raw == jeb->first_node) अणु
		jffs2_dbg(1, "Failing block at %08x is now empty. Moving to erase_pending_list\n",
			  jeb->offset);
		list_move(&jeb->list, &c->erase_pending_list);
		c->nr_erasing_blocks++;
		jffs2_garbage_collect_trigger(c);
	पूर्ण

	jffs2_dbg_acct_sanity_check_nolock(c, jeb);
	jffs2_dbg_acct_paranoia_check_nolock(c, jeb);

	jffs2_dbg_acct_sanity_check_nolock(c, new_jeb);
	jffs2_dbg_acct_paranoia_check_nolock(c, new_jeb);

	spin_unlock(&c->erase_completion_lock);

	jffs2_dbg(1, "wbuf recovery completed OK. wbuf_ofs 0x%08x, len 0x%x\n",
		  c->wbuf_ofs, c->wbuf_len);

पूर्ण

/* Meaning of pad argument:
   0: Do not pad. Probably poपूर्णांकless - we only ever use this when we can't pad anyway.
   1: Pad, करो not adjust nextblock मुक्त_size
   2: Pad, adjust nextblock मुक्त_size
*/
#घोषणा NOPAD		0
#घोषणा PAD_NOACCOUNT	1
#घोषणा PAD_ACCOUNTING	2

अटल पूर्णांक __jffs2_flush_wbuf(काष्ठा jffs2_sb_info *c, पूर्णांक pad)
अणु
	काष्ठा jffs2_eraseblock *wbuf_jeb;
	पूर्णांक ret;
	माप_प्रकार retlen;

	/* Nothing to करो अगर not ग_लिखो-buffering the flash. In particular, we shouldn't
	   del_समयr() the समयr we never initialised. */
	अगर (!jffs2_is_ग_लिखोbuffered(c))
		वापस 0;

	अगर (!mutex_is_locked(&c->alloc_sem)) अणु
		pr_crit("jffs2_flush_wbuf() called with alloc_sem not locked!\n");
		BUG();
	पूर्ण

	अगर (!c->wbuf_len)	/* alपढ़ोy checked c->wbuf above */
		वापस 0;

	wbuf_jeb = &c->blocks[c->wbuf_ofs / c->sector_size];
	अगर (jffs2_pपुनः_स्मृति_raw_node_refs(c, wbuf_jeb, c->nextblock->allocated_refs + 1))
		वापस -ENOMEM;

	/* claim reमुख्यing space on the page
	   this happens, अगर we have a change to a new block,
	   or अगर fsync क्रमces us to flush the ग_लिखोbuffer.
	   अगर we have a चयन to next page, we will not have
	   enough reमुख्यing space क्रम this.
	*/
	अगर (pad ) अणु
		c->wbuf_len = PAD(c->wbuf_len);

		/* Pad with JFFS2_सूचीTY_BITMASK initially.  this helps out ECC'd NOR
		   with 8 byte page size */
		स_रखो(c->wbuf + c->wbuf_len, 0, c->wbuf_pagesize - c->wbuf_len);

		अगर ( c->wbuf_len + माप(काष्ठा jffs2_unknown_node) < c->wbuf_pagesize) अणु
			काष्ठा jffs2_unknown_node *padnode = (व्योम *)(c->wbuf + c->wbuf_len);
			padnode->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
			padnode->nodetype = cpu_to_je16(JFFS2_NODETYPE_PADDING);
			padnode->totlen = cpu_to_je32(c->wbuf_pagesize - c->wbuf_len);
			padnode->hdr_crc = cpu_to_je32(crc32(0, padnode, माप(*padnode)-4));
		पूर्ण
	पूर्ण
	/* अन्यथा jffs2_flash_ग_लिखोv has actually filled in the rest of the
	   buffer क्रम us, and will deal with the node refs etc. later. */

#अगर_घोषित BREAKME
	अटल पूर्णांक अवरोधme;
	अगर (अवरोधme++ == 20) अणु
		pr_notice("Faking write error at 0x%08x\n", c->wbuf_ofs);
		अवरोधme = 0;
		mtd_ग_लिखो(c->mtd, c->wbuf_ofs, c->wbuf_pagesize, &retlen,
			  brokenbuf);
		ret = -EIO;
	पूर्ण अन्यथा
#पूर्ण_अगर

		ret = mtd_ग_लिखो(c->mtd, c->wbuf_ofs, c->wbuf_pagesize,
				&retlen, c->wbuf);

	अगर (ret) अणु
		pr_warn("jffs2_flush_wbuf(): Write failed with %d\n", ret);
		जाओ wfail;
	पूर्ण अन्यथा अगर (retlen != c->wbuf_pagesize) अणु
		pr_warn("jffs2_flush_wbuf(): Write was short: %zd instead of %d\n",
			retlen, c->wbuf_pagesize);
		ret = -EIO;
		जाओ wfail;
	पूर्ण अन्यथा अगर ((ret = jffs2_verअगरy_ग_लिखो(c, c->wbuf, c->wbuf_ofs))) अणु
	wfail:
		jffs2_wbuf_recover(c);

		वापस ret;
	पूर्ण

	/* Adjust मुक्त size of the block अगर we padded. */
	अगर (pad) अणु
		uपूर्णांक32_t waste = c->wbuf_pagesize - c->wbuf_len;

		jffs2_dbg(1, "jffs2_flush_wbuf() adjusting free_size of %sblock at %08x\n",
			  (wbuf_jeb == c->nextblock) ? "next" : "",
			  wbuf_jeb->offset);

		/* wbuf_pagesize - wbuf_len is the amount of space that's to be
		   padded. If there is less मुक्त space in the block than that,
		   something screwed up */
		अगर (wbuf_jeb->मुक्त_size < waste) अणु
			pr_crit("jffs2_flush_wbuf(): Accounting error. wbuf at 0x%08x has 0x%03x bytes, 0x%03x left.\n",
				c->wbuf_ofs, c->wbuf_len, waste);
			pr_crit("jffs2_flush_wbuf(): But free_size for block at 0x%08x is only 0x%08x\n",
				wbuf_jeb->offset, wbuf_jeb->मुक्त_size);
			BUG();
		पूर्ण

		spin_lock(&c->erase_completion_lock);

		jffs2_link_node_ref(c, wbuf_jeb, (c->wbuf_ofs + c->wbuf_len) | REF_OBSOLETE, waste, शून्य);
		/* FIXME: that made it count as dirty. Convert to wasted */
		wbuf_jeb->dirty_size -= waste;
		c->dirty_size -= waste;
		wbuf_jeb->wasted_size += waste;
		c->wasted_size += waste;
	पूर्ण अन्यथा
		spin_lock(&c->erase_completion_lock);

	/* Stick any now-obsoleted blocks on the erase_pending_list */
	jffs2_refile_wbuf_blocks(c);
	jffs2_clear_wbuf_ino_list(c);
	spin_unlock(&c->erase_completion_lock);

	स_रखो(c->wbuf,0xff,c->wbuf_pagesize);
	/* adjust ग_लिखो buffer offset, अन्यथा we get a non contiguous ग_लिखो bug */
	c->wbuf_ofs += c->wbuf_pagesize;
	c->wbuf_len = 0;
	वापस 0;
पूर्ण

/* Trigger garbage collection to flush the ग_लिखो-buffer.
   If ino arg is zero, करो it अगर _any_ real (i.e. not GC) ग_लिखोs are
   outstanding. If ino arg non-zero, करो it only अगर a ग_लिखो क्रम the
   given inode is outstanding. */
पूर्णांक jffs2_flush_wbuf_gc(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t ino)
अणु
	uपूर्णांक32_t old_wbuf_ofs;
	uपूर्णांक32_t old_wbuf_len;
	पूर्णांक ret = 0;

	jffs2_dbg(1, "jffs2_flush_wbuf_gc() called for ino #%u...\n", ino);

	अगर (!c->wbuf)
		वापस 0;

	mutex_lock(&c->alloc_sem);
	अगर (!jffs2_wbuf_pending_क्रम_ino(c, ino)) अणु
		jffs2_dbg(1, "Ino #%d not pending in wbuf. Returning\n", ino);
		mutex_unlock(&c->alloc_sem);
		वापस 0;
	पूर्ण

	old_wbuf_ofs = c->wbuf_ofs;
	old_wbuf_len = c->wbuf_len;

	अगर (c->unchecked_size) अणु
		/* GC won't make any progress क्रम a जबतक */
		jffs2_dbg(1, "%s(): padding. Not finished checking\n",
			  __func__);
		करोwn_ग_लिखो(&c->wbuf_sem);
		ret = __jffs2_flush_wbuf(c, PAD_ACCOUNTING);
		/* retry flushing wbuf in हाल jffs2_wbuf_recover
		   left some data in the wbuf */
		अगर (ret)
			ret = __jffs2_flush_wbuf(c, PAD_ACCOUNTING);
		up_ग_लिखो(&c->wbuf_sem);
	पूर्ण अन्यथा जबतक (old_wbuf_len &&
		      old_wbuf_ofs == c->wbuf_ofs) अणु

		mutex_unlock(&c->alloc_sem);

		jffs2_dbg(1, "%s(): calls gc pass\n", __func__);

		ret = jffs2_garbage_collect_pass(c);
		अगर (ret) अणु
			/* GC failed. Flush it with padding instead */
			mutex_lock(&c->alloc_sem);
			करोwn_ग_लिखो(&c->wbuf_sem);
			ret = __jffs2_flush_wbuf(c, PAD_ACCOUNTING);
			/* retry flushing wbuf in हाल jffs2_wbuf_recover
			   left some data in the wbuf */
			अगर (ret)
				ret = __jffs2_flush_wbuf(c, PAD_ACCOUNTING);
			up_ग_लिखो(&c->wbuf_sem);
			अवरोध;
		पूर्ण
		mutex_lock(&c->alloc_sem);
	पूर्ण

	jffs2_dbg(1, "%s(): ends...\n", __func__);

	mutex_unlock(&c->alloc_sem);
	वापस ret;
पूर्ण

/* Pad ग_लिखो-buffer to end and ग_लिखो it, wasting space. */
पूर्णांक jffs2_flush_wbuf_pad(काष्ठा jffs2_sb_info *c)
अणु
	पूर्णांक ret;

	अगर (!c->wbuf)
		वापस 0;

	करोwn_ग_लिखो(&c->wbuf_sem);
	ret = __jffs2_flush_wbuf(c, PAD_NOACCOUNT);
	/* retry - maybe wbuf recover left some data in wbuf. */
	अगर (ret)
		ret = __jffs2_flush_wbuf(c, PAD_NOACCOUNT);
	up_ग_लिखो(&c->wbuf_sem);

	वापस ret;
पूर्ण

अटल माप_प्रकार jffs2_fill_wbuf(काष्ठा jffs2_sb_info *c, स्थिर uपूर्णांक8_t *buf,
			      माप_प्रकार len)
अणु
	अगर (len && !c->wbuf_len && (len >= c->wbuf_pagesize))
		वापस 0;

	अगर (len > (c->wbuf_pagesize - c->wbuf_len))
		len = c->wbuf_pagesize - c->wbuf_len;
	स_नकल(c->wbuf + c->wbuf_len, buf, len);
	c->wbuf_len += (uपूर्णांक32_t) len;
	वापस len;
पूर्ण

पूर्णांक jffs2_flash_ग_लिखोv(काष्ठा jffs2_sb_info *c, स्थिर काष्ठा kvec *invecs,
		       अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen,
		       uपूर्णांक32_t ino)
अणु
	काष्ठा jffs2_eraseblock *jeb;
	माप_प्रकार wbuf_retlen, करोnelen = 0;
	uपूर्णांक32_t outvec_to = to;
	पूर्णांक ret, invec;

	/* If not ग_लिखोbuffered flash, करोn't bother */
	अगर (!jffs2_is_ग_लिखोbuffered(c))
		वापस jffs2_flash_direct_ग_लिखोv(c, invecs, count, to, retlen);

	करोwn_ग_लिखो(&c->wbuf_sem);

	/* If wbuf_ofs is not initialized, set it to target address */
	अगर (c->wbuf_ofs == 0xFFFFFFFF) अणु
		c->wbuf_ofs = PAGE_DIV(to);
		c->wbuf_len = PAGE_MOD(to);
		स_रखो(c->wbuf,0xff,c->wbuf_pagesize);
	पूर्ण

	/*
	 * Sanity checks on target address.  It's permitted to ग_लिखो
	 * at PAD(c->wbuf_len+c->wbuf_ofs), and it's permitted to
	 * ग_लिखो at the beginning of a new erase block. Anything अन्यथा,
	 * and you die.  New block starts at xxx000c (0-b = block
	 * header)
	 */
	अगर (SECTOR_ADDR(to) != SECTOR_ADDR(c->wbuf_ofs)) अणु
		/* It's a ग_लिखो to a new block */
		अगर (c->wbuf_len) अणु
			jffs2_dbg(1, "%s(): to 0x%lx causes flush of wbuf at 0x%08x\n",
				  __func__, (अचिन्हित दीर्घ)to, c->wbuf_ofs);
			ret = __jffs2_flush_wbuf(c, PAD_NOACCOUNT);
			अगर (ret)
				जाओ outerr;
		पूर्ण
		/* set poपूर्णांकer to new block */
		c->wbuf_ofs = PAGE_DIV(to);
		c->wbuf_len = PAGE_MOD(to);
	पूर्ण

	अगर (to != PAD(c->wbuf_ofs + c->wbuf_len)) अणु
		/* We're not writing immediately after the ग_लिखोbuffer. Bad. */
		pr_crit("%s(): Non-contiguous write to %08lx\n",
			__func__, (अचिन्हित दीर्घ)to);
		अगर (c->wbuf_len)
			pr_crit("wbuf was previously %08x-%08x\n",
				c->wbuf_ofs, c->wbuf_ofs + c->wbuf_len);
		BUG();
	पूर्ण

	/* adjust alignment offset */
	अगर (c->wbuf_len != PAGE_MOD(to)) अणु
		c->wbuf_len = PAGE_MOD(to);
		/* take care of alignment to next page */
		अगर (!c->wbuf_len) अणु
			c->wbuf_len = c->wbuf_pagesize;
			ret = __jffs2_flush_wbuf(c, NOPAD);
			अगर (ret)
				जाओ outerr;
		पूर्ण
	पूर्ण

	क्रम (invec = 0; invec < count; invec++) अणु
		पूर्णांक vlen = invecs[invec].iov_len;
		uपूर्णांक8_t *v = invecs[invec].iov_base;

		wbuf_retlen = jffs2_fill_wbuf(c, v, vlen);

		अगर (c->wbuf_len == c->wbuf_pagesize) अणु
			ret = __jffs2_flush_wbuf(c, NOPAD);
			अगर (ret)
				जाओ outerr;
		पूर्ण
		vlen -= wbuf_retlen;
		outvec_to += wbuf_retlen;
		करोnelen += wbuf_retlen;
		v += wbuf_retlen;

		अगर (vlen >= c->wbuf_pagesize) अणु
			ret = mtd_ग_लिखो(c->mtd, outvec_to, PAGE_DIV(vlen),
					&wbuf_retlen, v);
			अगर (ret < 0 || wbuf_retlen != PAGE_DIV(vlen))
				जाओ outfile;

			vlen -= wbuf_retlen;
			outvec_to += wbuf_retlen;
			c->wbuf_ofs = outvec_to;
			करोnelen += wbuf_retlen;
			v += wbuf_retlen;
		पूर्ण

		wbuf_retlen = jffs2_fill_wbuf(c, v, vlen);
		अगर (c->wbuf_len == c->wbuf_pagesize) अणु
			ret = __jffs2_flush_wbuf(c, NOPAD);
			अगर (ret)
				जाओ outerr;
		पूर्ण

		outvec_to += wbuf_retlen;
		करोnelen += wbuf_retlen;
	पूर्ण

	/*
	 * If there's a remainder in the wbuf and it's a non-GC ग_लिखो,
	 * remember that the wbuf affects this ino
	 */
	*retlen = करोnelen;

	अगर (jffs2_sum_active()) अणु
		पूर्णांक res = jffs2_sum_add_kvec(c, invecs, count, (uपूर्णांक32_t) to);
		अगर (res)
			वापस res;
	पूर्ण

	अगर (c->wbuf_len && ino)
		jffs2_wbuf_dirties_inode(c, ino);

	ret = 0;
	up_ग_लिखो(&c->wbuf_sem);
	वापस ret;

outfile:
	/*
	 * At this poपूर्णांक we have no problem, c->wbuf is empty. However
	 * refile nextblock to aव्योम writing again to same address.
	 */

	spin_lock(&c->erase_completion_lock);

	jeb = &c->blocks[outvec_to / c->sector_size];
	jffs2_block_refile(c, jeb, REखाता_ANYWAY);

	spin_unlock(&c->erase_completion_lock);

outerr:
	*retlen = 0;
	up_ग_लिखो(&c->wbuf_sem);
	वापस ret;
पूर्ण

/*
 *	This is the entry क्रम flash ग_लिखो.
 *	Check, अगर we work on न_अंकD FLASH, अगर so build an kvec and ग_लिखो it via vritev
*/
पूर्णांक jffs2_flash_ग_लिखो(काष्ठा jffs2_sb_info *c, loff_t ofs, माप_प्रकार len,
		      माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा kvec vecs[1];

	अगर (!jffs2_is_ग_लिखोbuffered(c))
		वापस jffs2_flash_direct_ग_लिखो(c, ofs, len, retlen, buf);

	vecs[0].iov_base = (अचिन्हित अक्षर *) buf;
	vecs[0].iov_len = len;
	वापस jffs2_flash_ग_लिखोv(c, vecs, 1, ofs, retlen, 0);
पूर्ण

/*
	Handle पढ़ोback from ग_लिखोbuffer and ECC failure वापस
*/
पूर्णांक jffs2_flash_पढ़ो(काष्ठा jffs2_sb_info *c, loff_t ofs, माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	loff_t	orbf = 0, owbf = 0, lwbf = 0;
	पूर्णांक	ret;

	अगर (!jffs2_is_ग_लिखोbuffered(c))
		वापस mtd_पढ़ो(c->mtd, ofs, len, retlen, buf);

	/* Read flash */
	करोwn_पढ़ो(&c->wbuf_sem);
	ret = mtd_पढ़ो(c->mtd, ofs, len, retlen, buf);

	अगर ( (ret == -EBADMSG || ret == -EUCLEAN) && (*retlen == len) ) अणु
		अगर (ret == -EBADMSG)
			pr_warn("mtd->read(0x%zx bytes from 0x%llx) returned ECC error\n",
				len, ofs);
		/*
		 * We have the raw data without ECC correction in the buffer,
		 * maybe we are lucky and all data or parts are correct. We
		 * check the node.  If data are corrupted node check will sort
		 * it out.  We keep this block, it will fail on ग_लिखो or erase
		 * and the we mark it bad. Or should we करो that now? But we
		 * should give him a chance.  Maybe we had a प्रणाली crash or
		 * घातer loss beक्रमe the ecc ग_लिखो or a erase was completed.
		 * So we वापस success. :)
		 */
		ret = 0;
	पूर्ण

	/* अगर no ग_लिखोbuffer available or ग_लिखो buffer empty, वापस */
	अगर (!c->wbuf_pagesize || !c->wbuf_len)
		जाओ निकास;

	/* अगर we पढ़ो in a dअगरferent block, वापस */
	अगर (SECTOR_ADDR(ofs) != SECTOR_ADDR(c->wbuf_ofs))
		जाओ निकास;

	अगर (ofs >= c->wbuf_ofs) अणु
		owbf = (ofs - c->wbuf_ofs);	/* offset in ग_लिखो buffer */
		अगर (owbf > c->wbuf_len)		/* is पढ़ो beyond ग_लिखो buffer ? */
			जाओ निकास;
		lwbf = c->wbuf_len - owbf;	/* number of bytes to copy */
		अगर (lwbf > len)
			lwbf = len;
	पूर्ण अन्यथा अणु
		orbf = (c->wbuf_ofs - ofs);	/* offset in पढ़ो buffer */
		अगर (orbf > len)			/* is ग_लिखो beyond ग_लिखो buffer ? */
			जाओ निकास;
		lwbf = len - orbf;		/* number of bytes to copy */
		अगर (lwbf > c->wbuf_len)
			lwbf = c->wbuf_len;
	पूर्ण
	अगर (lwbf > 0)
		स_नकल(buf+orbf,c->wbuf+owbf,lwbf);

निकास:
	up_पढ़ो(&c->wbuf_sem);
	वापस ret;
पूर्ण

#घोषणा NR_OOB_SCAN_PAGES 4

/* For historical reasons we use only 8 bytes क्रम OOB clean marker */
#घोषणा OOB_CM_SIZE 8

अटल स्थिर काष्ठा jffs2_unknown_node oob_cleanmarker =
अणु
	.magic = स्थिरant_cpu_to_je16(JFFS2_MAGIC_BITMASK),
	.nodetype = स्थिरant_cpu_to_je16(JFFS2_NODETYPE_CLEANMARKER),
	.totlen = स्थिरant_cpu_to_je32(8)
पूर्ण;

/*
 * Check, अगर the out of band area is empty. This function knows about the clean
 * marker and अगर it is present in OOB, treats the OOB as empty anyway.
 */
पूर्णांक jffs2_check_oob_empty(काष्ठा jffs2_sb_info *c,
			  काष्ठा jffs2_eraseblock *jeb, पूर्णांक mode)
अणु
	पूर्णांक i, ret;
	पूर्णांक cmlen = min_t(पूर्णांक, c->oobavail, OOB_CM_SIZE);
	काष्ठा mtd_oob_ops ops;

	ops.mode = MTD_OPS_AUTO_OOB;
	ops.ooblen = NR_OOB_SCAN_PAGES * c->oobavail;
	ops.oobbuf = c->oobbuf;
	ops.len = ops.ooboffs = ops.retlen = ops.oobretlen = 0;
	ops.datbuf = शून्य;

	ret = mtd_पढ़ो_oob(c->mtd, jeb->offset, &ops);
	अगर ((ret && !mtd_is_bitflip(ret)) || ops.oobretlen != ops.ooblen) अणु
		pr_err("cannot read OOB for EB at %08x, requested %zd bytes, read %zd bytes, error %d\n",
		       jeb->offset, ops.ooblen, ops.oobretlen, ret);
		अगर (!ret || mtd_is_bitflip(ret))
			ret = -EIO;
		वापस ret;
	पूर्ण

	क्रम(i = 0; i < ops.ooblen; i++) अणु
		अगर (mode && i < cmlen)
			/* Yeah, we know about the cleanmarker */
			जारी;

		अगर (ops.oobbuf[i] != 0xFF) अणु
			jffs2_dbg(2, "Found %02x at %x in OOB for "
				  "%08x\n", ops.oobbuf[i], i, jeb->offset);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Check क्रम a valid cleanmarker.
 * Returns: 0 अगर a valid cleanmarker was found
 *	    1 अगर no cleanmarker was found
 *	    negative error code अगर an error occurred
 */
पूर्णांक jffs2_check_nand_cleanmarker(काष्ठा jffs2_sb_info *c,
				 काष्ठा jffs2_eraseblock *jeb)
अणु
	काष्ठा mtd_oob_ops ops;
	पूर्णांक ret, cmlen = min_t(पूर्णांक, c->oobavail, OOB_CM_SIZE);

	ops.mode = MTD_OPS_AUTO_OOB;
	ops.ooblen = cmlen;
	ops.oobbuf = c->oobbuf;
	ops.len = ops.ooboffs = ops.retlen = ops.oobretlen = 0;
	ops.datbuf = शून्य;

	ret = mtd_पढ़ो_oob(c->mtd, jeb->offset, &ops);
	अगर ((ret && !mtd_is_bitflip(ret)) || ops.oobretlen != ops.ooblen) अणु
		pr_err("cannot read OOB for EB at %08x, requested %zd bytes, read %zd bytes, error %d\n",
		       jeb->offset, ops.ooblen, ops.oobretlen, ret);
		अगर (!ret || mtd_is_bitflip(ret))
			ret = -EIO;
		वापस ret;
	पूर्ण

	वापस !!स_भेद(&oob_cleanmarker, c->oobbuf, cmlen);
पूर्ण

पूर्णांक jffs2_ग_लिखो_nand_cleanmarker(काष्ठा jffs2_sb_info *c,
				 काष्ठा jffs2_eraseblock *jeb)
अणु
	पूर्णांक ret;
	काष्ठा mtd_oob_ops ops;
	पूर्णांक cmlen = min_t(पूर्णांक, c->oobavail, OOB_CM_SIZE);

	ops.mode = MTD_OPS_AUTO_OOB;
	ops.ooblen = cmlen;
	ops.oobbuf = (uपूर्णांक8_t *)&oob_cleanmarker;
	ops.len = ops.ooboffs = ops.retlen = ops.oobretlen = 0;
	ops.datbuf = शून्य;

	ret = mtd_ग_लिखो_oob(c->mtd, jeb->offset, &ops);
	अगर (ret || ops.oobretlen != ops.ooblen) अणु
		pr_err("cannot write OOB for EB at %08x, requested %zd bytes, read %zd bytes, error %d\n",
		       jeb->offset, ops.ooblen, ops.oobretlen, ret);
		अगर (!ret)
			ret = -EIO;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * On न_अंकD we try to mark this block bad. If the block was erased more
 * than MAX_ERASE_FAILURES we mark it finally bad.
 * Don't care about failures. This block reमुख्यs on the erase-pending
 * or badblock list as दीर्घ as nobody manipulates the flash with
 * a bootloader or something like that.
 */

पूर्णांक jffs2_ग_लिखो_nand_badblock(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb, uपूर्णांक32_t bad_offset)
अणु
	पूर्णांक 	ret;

	/* अगर the count is < max, we try to ग_लिखो the counter to the 2nd page oob area */
	अगर( ++jeb->bad_count < MAX_ERASE_FAILURES)
		वापस 0;

	pr_warn("marking eraseblock at %08x as bad\n", bad_offset);
	ret = mtd_block_markbad(c->mtd, bad_offset);

	अगर (ret) अणु
		jffs2_dbg(1, "%s(): Write failed for block at %08x: error %d\n",
			  __func__, jeb->offset, ret);
		वापस ret;
	पूर्ण
	वापस 1;
पूर्ण

अटल काष्ठा jffs2_sb_info *work_to_sb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork;

	dwork = to_delayed_work(work);
	वापस container_of(dwork, काष्ठा jffs2_sb_info, wbuf_dwork);
पूर्ण

अटल व्योम delayed_wbuf_sync(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा jffs2_sb_info *c = work_to_sb(work);
	काष्ठा super_block *sb = OFNI_BS_2SFFJ(c);

	अगर (!sb_rकरोnly(sb)) अणु
		jffs2_dbg(1, "%s()\n", __func__);
		jffs2_flush_wbuf_gc(c, 0);
	पूर्ण
पूर्ण

व्योम jffs2_dirty_trigger(काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा super_block *sb = OFNI_BS_2SFFJ(c);
	अचिन्हित दीर्घ delay;

	अगर (sb_rकरोnly(sb))
		वापस;

	delay = msecs_to_jअगरfies(dirty_ग_लिखोback_पूर्णांकerval * 10);
	अगर (queue_delayed_work(प्रणाली_दीर्घ_wq, &c->wbuf_dwork, delay))
		jffs2_dbg(1, "%s()\n", __func__);
पूर्ण

पूर्णांक jffs2_nand_flash_setup(काष्ठा jffs2_sb_info *c)
अणु
	अगर (!c->mtd->oobsize)
		वापस 0;

	/* Cleanmarker is out-of-band, so अंतरभूत size zero */
	c->cleanmarker_size = 0;

	अगर (c->mtd->oobavail == 0) अणु
		pr_err("inconsistent device description\n");
		वापस -EINVAL;
	पूर्ण

	jffs2_dbg(1, "using OOB on NAND\n");

	c->oobavail = c->mtd->oobavail;

	/* Initialise ग_लिखो buffer */
	init_rwsem(&c->wbuf_sem);
	INIT_DELAYED_WORK(&c->wbuf_dwork, delayed_wbuf_sync);
	c->wbuf_pagesize = c->mtd->ग_लिखोsize;
	c->wbuf_ofs = 0xFFFFFFFF;

	c->wbuf = kदो_स्मृति(c->wbuf_pagesize, GFP_KERNEL);
	अगर (!c->wbuf)
		वापस -ENOMEM;

	c->oobbuf = kदो_स्मृति_array(NR_OOB_SCAN_PAGES, c->oobavail, GFP_KERNEL);
	अगर (!c->oobbuf) अणु
		kमुक्त(c->wbuf);
		वापस -ENOMEM;
	पूर्ण

#अगर_घोषित CONFIG_JFFS2_FS_WBUF_VERIFY
	c->wbuf_verअगरy = kदो_स्मृति(c->wbuf_pagesize, GFP_KERNEL);
	अगर (!c->wbuf_verअगरy) अणु
		kमुक्त(c->oobbuf);
		kमुक्त(c->wbuf);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम jffs2_nand_flash_cleanup(काष्ठा jffs2_sb_info *c)
अणु
#अगर_घोषित CONFIG_JFFS2_FS_WBUF_VERIFY
	kमुक्त(c->wbuf_verअगरy);
#पूर्ण_अगर
	kमुक्त(c->wbuf);
	kमुक्त(c->oobbuf);
पूर्ण

पूर्णांक jffs2_dataflash_setup(काष्ठा jffs2_sb_info *c) अणु
	c->cleanmarker_size = 0;		/* No cleanmarkers needed */

	/* Initialize ग_लिखो buffer */
	init_rwsem(&c->wbuf_sem);
	INIT_DELAYED_WORK(&c->wbuf_dwork, delayed_wbuf_sync);
	c->wbuf_pagesize =  c->mtd->erasesize;

	/* Find a suitable c->sector_size
	 * - Not too much sectors
	 * - Sectors have to be at least 4 K + some bytes
	 * - All known dataflashes have erase sizes of 528 or 1056
	 * - we take at least 8 eraseblocks and want to have at least 8K size
	 * - The concatenation should be a घातer of 2
	*/

	c->sector_size = 8 * c->mtd->erasesize;

	जबतक (c->sector_size < 8192) अणु
		c->sector_size *= 2;
	पूर्ण

	/* It may be necessary to adjust the flash size */
	c->flash_size = c->mtd->size;

	अगर ((c->flash_size % c->sector_size) != 0) अणु
		c->flash_size = (c->flash_size / c->sector_size) * c->sector_size;
		pr_warn("flash size adjusted to %dKiB\n", c->flash_size);
	पूर्ण

	c->wbuf_ofs = 0xFFFFFFFF;
	c->wbuf = kदो_स्मृति(c->wbuf_pagesize, GFP_KERNEL);
	अगर (!c->wbuf)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_JFFS2_FS_WBUF_VERIFY
	c->wbuf_verअगरy = kदो_स्मृति(c->wbuf_pagesize, GFP_KERNEL);
	अगर (!c->wbuf_verअगरy) अणु
		kमुक्त(c->wbuf);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर

	pr_info("write-buffering enabled buffer (%d) erasesize (%d)\n",
		c->wbuf_pagesize, c->sector_size);

	वापस 0;
पूर्ण

व्योम jffs2_dataflash_cleanup(काष्ठा jffs2_sb_info *c) अणु
#अगर_घोषित CONFIG_JFFS2_FS_WBUF_VERIFY
	kमुक्त(c->wbuf_verअगरy);
#पूर्ण_अगर
	kमुक्त(c->wbuf);
पूर्ण

पूर्णांक jffs2_nor_wbuf_flash_setup(काष्ठा jffs2_sb_info *c) अणु
	/* Cleanmarker currently occupies whole programming regions,
	 * either one or 2 क्रम 8Byte STMicro flashes. */
	c->cleanmarker_size = max(16u, c->mtd->ग_लिखोsize);

	/* Initialize ग_लिखो buffer */
	init_rwsem(&c->wbuf_sem);
	INIT_DELAYED_WORK(&c->wbuf_dwork, delayed_wbuf_sync);

	c->wbuf_pagesize = c->mtd->ग_लिखोsize;
	c->wbuf_ofs = 0xFFFFFFFF;

	c->wbuf = kदो_स्मृति(c->wbuf_pagesize, GFP_KERNEL);
	अगर (!c->wbuf)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_JFFS2_FS_WBUF_VERIFY
	c->wbuf_verअगरy = kदो_स्मृति(c->wbuf_pagesize, GFP_KERNEL);
	अगर (!c->wbuf_verअगरy) अणु
		kमुक्त(c->wbuf);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम jffs2_nor_wbuf_flash_cleanup(काष्ठा jffs2_sb_info *c) अणु
#अगर_घोषित CONFIG_JFFS2_FS_WBUF_VERIFY
	kमुक्त(c->wbuf_verअगरy);
#पूर्ण_अगर
	kमुक्त(c->wbuf);
पूर्ण

पूर्णांक jffs2_ubivol_setup(काष्ठा jffs2_sb_info *c) अणु
	c->cleanmarker_size = 0;

	अगर (c->mtd->ग_लिखोsize == 1)
		/* We करो not need ग_लिखो-buffer */
		वापस 0;

	init_rwsem(&c->wbuf_sem);
	INIT_DELAYED_WORK(&c->wbuf_dwork, delayed_wbuf_sync);

	c->wbuf_pagesize =  c->mtd->ग_लिखोsize;
	c->wbuf_ofs = 0xFFFFFFFF;
	c->wbuf = kदो_स्मृति(c->wbuf_pagesize, GFP_KERNEL);
	अगर (!c->wbuf)
		वापस -ENOMEM;

	pr_info("write-buffering enabled buffer (%d) erasesize (%d)\n",
		c->wbuf_pagesize, c->sector_size);

	वापस 0;
पूर्ण

व्योम jffs2_ubivol_cleanup(काष्ठा jffs2_sb_info *c) अणु
	kमुक्त(c->wbuf);
पूर्ण
