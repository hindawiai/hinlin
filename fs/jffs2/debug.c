<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/crc32.h>
#समावेश <linux/jffs2.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/slab.h>
#समावेश "nodelist.h"
#समावेश "debug.h"

#अगर_घोषित JFFS2_DBG_SANITY_CHECKS

व्योम
__jffs2_dbg_acct_sanity_check_nolock(काष्ठा jffs2_sb_info *c,
				     काष्ठा jffs2_eraseblock *jeb)
अणु
	अगर (unlikely(jeb && jeb->used_size + jeb->dirty_size +
			jeb->मुक्त_size + jeb->wasted_size +
			jeb->unchecked_size != c->sector_size)) अणु
		JFFS2_ERROR("eeep, space accounting for block at 0x%08x is screwed.\n", jeb->offset);
		JFFS2_ERROR("free %#08x + dirty %#08x + used %#08x + wasted %#08x + unchecked %#08x != total %#08x.\n",
			jeb->मुक्त_size, jeb->dirty_size, jeb->used_size,
			jeb->wasted_size, jeb->unchecked_size, c->sector_size);
		BUG();
	पूर्ण

	अगर (unlikely(c->used_size + c->dirty_size + c->मुक्त_size + c->erasing_size + c->bad_size
				+ c->wasted_size + c->unchecked_size != c->flash_size)) अणु
		JFFS2_ERROR("eeep, space accounting superblock info is screwed.\n");
		JFFS2_ERROR("free %#08x + dirty %#08x + used %#08x + erasing %#08x + bad %#08x + wasted %#08x + unchecked %#08x != total %#08x.\n",
			c->मुक्त_size, c->dirty_size, c->used_size, c->erasing_size, c->bad_size,
			c->wasted_size, c->unchecked_size, c->flash_size);
		BUG();
	पूर्ण
पूर्ण

व्योम
__jffs2_dbg_acct_sanity_check(काष्ठा jffs2_sb_info *c,
			      काष्ठा jffs2_eraseblock *jeb)
अणु
	spin_lock(&c->erase_completion_lock);
	jffs2_dbg_acct_sanity_check_nolock(c, jeb);
	spin_unlock(&c->erase_completion_lock);
पूर्ण

#पूर्ण_अगर /* JFFS2_DBG_SANITY_CHECKS */

#अगर_घोषित JFFS2_DBG_PARANOIA_CHECKS
/*
 * Check the fragtree.
 */
व्योम
__jffs2_dbg_fragtree_paranoia_check(काष्ठा jffs2_inode_info *f)
अणु
	mutex_lock(&f->sem);
	__jffs2_dbg_fragtree_paranoia_check_nolock(f);
	mutex_unlock(&f->sem);
पूर्ण

व्योम
__jffs2_dbg_fragtree_paranoia_check_nolock(काष्ठा jffs2_inode_info *f)
अणु
	काष्ठा jffs2_node_frag *frag;
	पूर्णांक bitched = 0;

	क्रम (frag = frag_first(&f->fragtree); frag; frag = frag_next(frag)) अणु
		काष्ठा jffs2_full_dnode *fn = frag->node;

		अगर (!fn || !fn->raw)
			जारी;

		अगर (ref_flags(fn->raw) == REF_PRISTINE) अणु
			अगर (fn->frags > 1) अणु
				JFFS2_ERROR("REF_PRISTINE node at 0x%08x had %d frags. Tell dwmw2.\n",
					ref_offset(fn->raw), fn->frags);
				bitched = 1;
			पूर्ण

			/* A hole node which isn't multi-page should be garbage-collected
			   and merged anyway, so we just check क्रम the frag size here,
			   rather than mucking around with actually पढ़ोing the node
			   and checking the compression type, which is the real way
			   to tell a hole node. */
			अगर (frag->ofs & (PAGE_SIZE-1) && frag_prev(frag)
					&& frag_prev(frag)->size < PAGE_SIZE && frag_prev(frag)->node) अणु
				JFFS2_ERROR("REF_PRISTINE node at 0x%08x had a previous non-hole frag in the same page. Tell dwmw2.\n",
					ref_offset(fn->raw));
				bitched = 1;
			पूर्ण

			अगर ((frag->ofs+frag->size) & (PAGE_SIZE-1) && frag_next(frag)
					&& frag_next(frag)->size < PAGE_SIZE && frag_next(frag)->node) अणु
				JFFS2_ERROR("REF_PRISTINE node at 0x%08x (%08x-%08x) had a following non-hole frag in the same page. Tell dwmw2.\n",
				       ref_offset(fn->raw), frag->ofs, frag->ofs+frag->size);
				bitched = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (bitched) अणु
		JFFS2_ERROR("fragtree is corrupted.\n");
		__jffs2_dbg_dump_fragtree_nolock(f);
		BUG();
	पूर्ण
पूर्ण

/*
 * Check अगर the flash contains all 0xFF beक्रमe we start writing.
 */
व्योम
__jffs2_dbg_preग_लिखो_paranoia_check(काष्ठा jffs2_sb_info *c,
				    uपूर्णांक32_t ofs, पूर्णांक len)
अणु
	माप_प्रकार retlen;
	पूर्णांक ret, i;
	अचिन्हित अक्षर *buf;

	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buf)
		वापस;

	ret = jffs2_flash_पढ़ो(c, ofs, len, &retlen, buf);
	अगर (ret || (retlen != len)) अणु
		JFFS2_WARNING("read %d bytes failed or short. ret %d, retlen %zd.\n",
				len, ret, retlen);
		kमुक्त(buf);
		वापस;
	पूर्ण

	ret = 0;
	क्रम (i = 0; i < len; i++)
		अगर (buf[i] != 0xff)
			ret = 1;

	अगर (ret) अणु
		JFFS2_ERROR("argh, about to write node to %#08x on flash, but there are data already there. The first corrupted byte is at %#08x offset.\n",
			ofs, ofs + i);
		__jffs2_dbg_dump_buffer(buf, len, ofs);
		kमुक्त(buf);
		BUG();
	पूर्ण

	kमुक्त(buf);
पूर्ण

व्योम __jffs2_dbg_superblock_counts(काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा jffs2_eraseblock *jeb;
	uपूर्णांक32_t मुक्त = 0, dirty = 0, used = 0, wasted = 0,
		erasing = 0, bad = 0, unchecked = 0;
	पूर्णांक nr_counted = 0;
	पूर्णांक dump = 0;

	अगर (c->gcblock) अणु
		nr_counted++;
		मुक्त += c->gcblock->मुक्त_size;
		dirty += c->gcblock->dirty_size;
		used += c->gcblock->used_size;
		wasted += c->gcblock->wasted_size;
		unchecked += c->gcblock->unchecked_size;
	पूर्ण
	अगर (c->nextblock) अणु
		nr_counted++;
		मुक्त += c->nextblock->मुक्त_size;
		dirty += c->nextblock->dirty_size;
		used += c->nextblock->used_size;
		wasted += c->nextblock->wasted_size;
		unchecked += c->nextblock->unchecked_size;
	पूर्ण
	list_क्रम_each_entry(jeb, &c->clean_list, list) अणु
		nr_counted++;
		मुक्त += jeb->मुक्त_size;
		dirty += jeb->dirty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	पूर्ण
	list_क्रम_each_entry(jeb, &c->very_dirty_list, list) अणु
		nr_counted++;
		मुक्त += jeb->मुक्त_size;
		dirty += jeb->dirty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	पूर्ण
	list_क्रम_each_entry(jeb, &c->dirty_list, list) अणु
		nr_counted++;
		मुक्त += jeb->मुक्त_size;
		dirty += jeb->dirty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	पूर्ण
	list_क्रम_each_entry(jeb, &c->erasable_list, list) अणु
		nr_counted++;
		मुक्त += jeb->मुक्त_size;
		dirty += jeb->dirty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	पूर्ण
	list_क्रम_each_entry(jeb, &c->erasable_pending_wbuf_list, list) अणु
		nr_counted++;
		मुक्त += jeb->मुक्त_size;
		dirty += jeb->dirty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	पूर्ण
	list_क्रम_each_entry(jeb, &c->erase_pending_list, list) अणु
		nr_counted++;
		मुक्त += jeb->मुक्त_size;
		dirty += jeb->dirty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	पूर्ण
	list_क्रम_each_entry(jeb, &c->मुक्त_list, list) अणु
		nr_counted++;
		मुक्त += jeb->मुक्त_size;
		dirty += jeb->dirty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	पूर्ण
	list_क्रम_each_entry(jeb, &c->bad_used_list, list) अणु
		nr_counted++;
		मुक्त += jeb->मुक्त_size;
		dirty += jeb->dirty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	पूर्ण

	list_क्रम_each_entry(jeb, &c->erasing_list, list) अणु
		nr_counted++;
		erasing += c->sector_size;
	पूर्ण
	list_क्रम_each_entry(jeb, &c->erase_checking_list, list) अणु
		nr_counted++;
		erasing += c->sector_size;
	पूर्ण
	list_क्रम_each_entry(jeb, &c->erase_complete_list, list) अणु
		nr_counted++;
		erasing += c->sector_size;
	पूर्ण
	list_क्रम_each_entry(jeb, &c->bad_list, list) अणु
		nr_counted++;
		bad += c->sector_size;
	पूर्ण

#घोषणा check(sz)							\
करो अणु									\
	अगर (sz != c->sz##_size) अणु					\
		pr_warn("%s_size mismatch counted 0x%x, c->%s_size 0x%x\n", \
			#sz, sz, #sz, c->sz##_size);			\
		dump = 1;						\
	पूर्ण								\
पूर्ण जबतक (0)

	check(मुक्त);
	check(dirty);
	check(used);
	check(wasted);
	check(unchecked);
	check(bad);
	check(erasing);

#अघोषित check

	अगर (nr_counted != c->nr_blocks) अणु
		pr_warn("%s counted only 0x%x blocks of 0x%x. Where are the others?\n",
			__func__, nr_counted, c->nr_blocks);
		dump = 1;
	पूर्ण

	अगर (dump) अणु
		__jffs2_dbg_dump_block_lists_nolock(c);
		BUG();
	पूर्ण
पूर्ण

/*
 * Check the space accounting and node_ref list correctness क्रम the JFFS2 erasable block 'jeb'.
 */
व्योम
__jffs2_dbg_acct_paranoia_check(काष्ठा jffs2_sb_info *c,
				काष्ठा jffs2_eraseblock *jeb)
अणु
	spin_lock(&c->erase_completion_lock);
	__jffs2_dbg_acct_paranoia_check_nolock(c, jeb);
	spin_unlock(&c->erase_completion_lock);
पूर्ण

व्योम
__jffs2_dbg_acct_paranoia_check_nolock(काष्ठा jffs2_sb_info *c,
				       काष्ठा jffs2_eraseblock *jeb)
अणु
	uपूर्णांक32_t my_used_size = 0;
	uपूर्णांक32_t my_unchecked_size = 0;
	uपूर्णांक32_t my_dirty_size = 0;
	काष्ठा jffs2_raw_node_ref *ref2 = jeb->first_node;

	जबतक (ref2) अणु
		uपूर्णांक32_t totlen = ref_totlen(c, jeb, ref2);

		अगर (ref_offset(ref2) < jeb->offset ||
				ref_offset(ref2) > jeb->offset + c->sector_size) अणु
			JFFS2_ERROR("node_ref %#08x shouldn't be in block at %#08x.\n",
				ref_offset(ref2), jeb->offset);
			जाओ error;

		पूर्ण
		अगर (ref_flags(ref2) == REF_UNCHECKED)
			my_unchecked_size += totlen;
		अन्यथा अगर (!ref_obsolete(ref2))
			my_used_size += totlen;
		अन्यथा
			my_dirty_size += totlen;

		अगर ((!ref_next(ref2)) != (ref2 == jeb->last_node)) अणु
			JFFS2_ERROR("node_ref for node at %#08x (mem %p) has next at %#08x (mem %p), last_node is at %#08x (mem %p).\n",
				    ref_offset(ref2), ref2, ref_offset(ref_next(ref2)), ref_next(ref2),
				    ref_offset(jeb->last_node), jeb->last_node);
			जाओ error;
		पूर्ण
		ref2 = ref_next(ref2);
	पूर्ण

	अगर (my_used_size != jeb->used_size) अणु
		JFFS2_ERROR("Calculated used size %#08x != stored used size %#08x.\n",
			my_used_size, jeb->used_size);
		जाओ error;
	पूर्ण

	अगर (my_unchecked_size != jeb->unchecked_size) अणु
		JFFS2_ERROR("Calculated unchecked size %#08x != stored unchecked size %#08x.\n",
			my_unchecked_size, jeb->unchecked_size);
		जाओ error;
	पूर्ण

#अगर 0
	/* This should work when we implement ref->__totlen elemination */
	अगर (my_dirty_size != jeb->dirty_size + jeb->wasted_size) अणु
		JFFS2_ERROR("Calculated dirty+wasted size %#08x != stored dirty + wasted size %#08x\n",
			my_dirty_size, jeb->dirty_size + jeb->wasted_size);
		जाओ error;
	पूर्ण

	अगर (jeb->मुक्त_size == 0
		&& my_used_size + my_unchecked_size + my_dirty_size != c->sector_size) अणु
		JFFS2_ERROR("The sum of all nodes in block (%#x) != size of block (%#x)\n",
			my_used_size + my_unchecked_size + my_dirty_size,
			c->sector_size);
		जाओ error;
	पूर्ण
#पूर्ण_अगर

	अगर (!(c->flags & (JFFS2_SB_FLAG_BUILDING|JFFS2_SB_FLAG_SCANNING)))
		__jffs2_dbg_superblock_counts(c);

	वापस;

error:
	__jffs2_dbg_dump_node_refs_nolock(c, jeb);
	__jffs2_dbg_dump_jeb_nolock(jeb);
	__jffs2_dbg_dump_block_lists_nolock(c);
	BUG();

पूर्ण
#पूर्ण_अगर /* JFFS2_DBG_PARANOIA_CHECKS */

#अगर defined(JFFS2_DBG_DUMPS) || defined(JFFS2_DBG_PARANOIA_CHECKS)
/*
 * Dump the node_refs of the 'jeb' JFFS2 eraseblock.
 */
व्योम
__jffs2_dbg_dump_node_refs(काष्ठा jffs2_sb_info *c,
			   काष्ठा jffs2_eraseblock *jeb)
अणु
	spin_lock(&c->erase_completion_lock);
	__jffs2_dbg_dump_node_refs_nolock(c, jeb);
	spin_unlock(&c->erase_completion_lock);
पूर्ण

व्योम
__jffs2_dbg_dump_node_refs_nolock(काष्ठा jffs2_sb_info *c,
				  काष्ठा jffs2_eraseblock *jeb)
अणु
	काष्ठा jffs2_raw_node_ref *ref;
	पूर्णांक i = 0;

	prपूर्णांकk(JFFS2_DBG_MSG_PREFIX " Dump node_refs of the eraseblock %#08x\n", jeb->offset);
	अगर (!jeb->first_node) अणु
		prपूर्णांकk(JFFS2_DBG_MSG_PREFIX " no nodes in the eraseblock %#08x\n", jeb->offset);
		वापस;
	पूर्ण

	prपूर्णांकk(JFFS2_DBG);
	क्रम (ref = jeb->first_node; ; ref = ref_next(ref)) अणु
		prपूर्णांकk("%#08x", ref_offset(ref));
#अगर_घोषित TEST_TOTLEN
		prपूर्णांकk("(%x)", ref->__totlen);
#पूर्ण_अगर
		अगर (ref_next(ref))
			prपूर्णांकk("->");
		अन्यथा
			अवरोध;
		अगर (++i == 4) अणु
			i = 0;
			prपूर्णांकk("\n" JFFS2_DBG);
		पूर्ण
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

/*
 * Dump an eraseblock's space accounting.
 */
व्योम
__jffs2_dbg_dump_jeb(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb)
अणु
	spin_lock(&c->erase_completion_lock);
	__jffs2_dbg_dump_jeb_nolock(jeb);
	spin_unlock(&c->erase_completion_lock);
पूर्ण

व्योम
__jffs2_dbg_dump_jeb_nolock(काष्ठा jffs2_eraseblock *jeb)
अणु
	अगर (!jeb)
		वापस;

	prपूर्णांकk(JFFS2_DBG_MSG_PREFIX " dump space accounting for the eraseblock at %#08x:\n",
			jeb->offset);

	prपूर्णांकk(JFFS2_DBG "used_size: %#08x\n",		jeb->used_size);
	prपूर्णांकk(JFFS2_DBG "dirty_size: %#08x\n",		jeb->dirty_size);
	prपूर्णांकk(JFFS2_DBG "wasted_size: %#08x\n",	jeb->wasted_size);
	prपूर्णांकk(JFFS2_DBG "unchecked_size: %#08x\n",	jeb->unchecked_size);
	prपूर्णांकk(JFFS2_DBG "free_size: %#08x\n",		jeb->मुक्त_size);
पूर्ण

व्योम
__jffs2_dbg_dump_block_lists(काष्ठा jffs2_sb_info *c)
अणु
	spin_lock(&c->erase_completion_lock);
	__jffs2_dbg_dump_block_lists_nolock(c);
	spin_unlock(&c->erase_completion_lock);
पूर्ण

व्योम
__jffs2_dbg_dump_block_lists_nolock(काष्ठा jffs2_sb_info *c)
अणु
	prपूर्णांकk(JFFS2_DBG_MSG_PREFIX " dump JFFS2 blocks lists:\n");

	prपूर्णांकk(JFFS2_DBG "flash_size: %#08x\n",		c->flash_size);
	prपूर्णांकk(JFFS2_DBG "used_size: %#08x\n",		c->used_size);
	prपूर्णांकk(JFFS2_DBG "dirty_size: %#08x\n",		c->dirty_size);
	prपूर्णांकk(JFFS2_DBG "wasted_size: %#08x\n",	c->wasted_size);
	prपूर्णांकk(JFFS2_DBG "unchecked_size: %#08x\n",	c->unchecked_size);
	prपूर्णांकk(JFFS2_DBG "free_size: %#08x\n",		c->मुक्त_size);
	prपूर्णांकk(JFFS2_DBG "erasing_size: %#08x\n",	c->erasing_size);
	prपूर्णांकk(JFFS2_DBG "bad_size: %#08x\n",		c->bad_size);
	prपूर्णांकk(JFFS2_DBG "sector_size: %#08x\n",	c->sector_size);
	prपूर्णांकk(JFFS2_DBG "jffs2_reserved_blocks size: %#08x\n",
				c->sector_size * c->resv_blocks_ग_लिखो);

	अगर (c->nextblock)
		prपूर्णांकk(JFFS2_DBG "nextblock: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
			c->nextblock->offset, c->nextblock->used_size,
			c->nextblock->dirty_size, c->nextblock->wasted_size,
			c->nextblock->unchecked_size, c->nextblock->मुक्त_size);
	अन्यथा
		prपूर्णांकk(JFFS2_DBG "nextblock: NULL\n");

	अगर (c->gcblock)
		prपूर्णांकk(JFFS2_DBG "gcblock: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
			c->gcblock->offset, c->gcblock->used_size, c->gcblock->dirty_size,
			c->gcblock->wasted_size, c->gcblock->unchecked_size, c->gcblock->मुक्त_size);
	अन्यथा
		prपूर्णांकk(JFFS2_DBG "gcblock: NULL\n");

	अगर (list_empty(&c->clean_list)) अणु
		prपूर्णांकk(JFFS2_DBG "clean_list: empty\n");
	पूर्ण अन्यथा अणु
		काष्ठा list_head *this;
		पूर्णांक numblocks = 0;
		uपूर्णांक32_t dirty = 0;

		list_क्रम_each(this, &c->clean_list) अणु
			काष्ठा jffs2_eraseblock *jeb = list_entry(this, काष्ठा jffs2_eraseblock, list);
			numblocks ++;
			dirty += jeb->wasted_size;
			अगर (!(jeb->used_size == 0 && jeb->dirty_size == 0 && jeb->wasted_size == 0)) अणु
				prपूर्णांकk(JFFS2_DBG "clean_list: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
					jeb->offset, jeb->used_size, jeb->dirty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->मुक्त_size);
			पूर्ण
		पूर्ण

		prपूर्णांकk (JFFS2_DBG "Contains %d blocks with total wasted size %u, average wasted size: %u\n",
			numblocks, dirty, dirty / numblocks);
	पूर्ण

	अगर (list_empty(&c->very_dirty_list)) अणु
		prपूर्णांकk(JFFS2_DBG "very_dirty_list: empty\n");
	पूर्ण अन्यथा अणु
		काष्ठा list_head *this;
		पूर्णांक numblocks = 0;
		uपूर्णांक32_t dirty = 0;

		list_क्रम_each(this, &c->very_dirty_list) अणु
			काष्ठा jffs2_eraseblock *jeb = list_entry(this, काष्ठा jffs2_eraseblock, list);

			numblocks ++;
			dirty += jeb->dirty_size;
			अगर (!(jeb->used_size == 0 && jeb->dirty_size == 0 && jeb->wasted_size == 0)) अणु
				prपूर्णांकk(JFFS2_DBG "very_dirty_list: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
					jeb->offset, jeb->used_size, jeb->dirty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->मुक्त_size);
			पूर्ण
		पूर्ण

		prपूर्णांकk (JFFS2_DBG "Contains %d blocks with total dirty size %u, average dirty size: %u\n",
			numblocks, dirty, dirty / numblocks);
	पूर्ण

	अगर (list_empty(&c->dirty_list)) अणु
		prपूर्णांकk(JFFS2_DBG "dirty_list: empty\n");
	पूर्ण अन्यथा अणु
		काष्ठा list_head *this;
		पूर्णांक numblocks = 0;
		uपूर्णांक32_t dirty = 0;

		list_क्रम_each(this, &c->dirty_list) अणु
			काष्ठा jffs2_eraseblock *jeb = list_entry(this, काष्ठा jffs2_eraseblock, list);

			numblocks ++;
			dirty += jeb->dirty_size;
			अगर (!(jeb->used_size == 0 && jeb->dirty_size == 0 && jeb->wasted_size == 0)) अणु
				prपूर्णांकk(JFFS2_DBG "dirty_list: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
					jeb->offset, jeb->used_size, jeb->dirty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->मुक्त_size);
			पूर्ण
		पूर्ण

		prपूर्णांकk (JFFS2_DBG "contains %d blocks with total dirty size %u, average dirty size: %u\n",
			numblocks, dirty, dirty / numblocks);
	पूर्ण

	अगर (list_empty(&c->erasable_list)) अणु
		prपूर्णांकk(JFFS2_DBG "erasable_list: empty\n");
	पूर्ण अन्यथा अणु
		काष्ठा list_head *this;

		list_क्रम_each(this, &c->erasable_list) अणु
			काष्ठा jffs2_eraseblock *jeb = list_entry(this, काष्ठा jffs2_eraseblock, list);

			अगर (!(jeb->used_size == 0 && jeb->dirty_size == 0 && jeb->wasted_size == 0)) अणु
				prपूर्णांकk(JFFS2_DBG "erasable_list: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
					jeb->offset, jeb->used_size, jeb->dirty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->मुक्त_size);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (list_empty(&c->erasing_list)) अणु
		prपूर्णांकk(JFFS2_DBG "erasing_list: empty\n");
	पूर्ण अन्यथा अणु
		काष्ठा list_head *this;

		list_क्रम_each(this, &c->erasing_list) अणु
			काष्ठा jffs2_eraseblock *jeb = list_entry(this, काष्ठा jffs2_eraseblock, list);

			अगर (!(jeb->used_size == 0 && jeb->dirty_size == 0 && jeb->wasted_size == 0)) अणु
				prपूर्णांकk(JFFS2_DBG "erasing_list: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
					jeb->offset, jeb->used_size, jeb->dirty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->मुक्त_size);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (list_empty(&c->erase_checking_list)) अणु
		prपूर्णांकk(JFFS2_DBG "erase_checking_list: empty\n");
	पूर्ण अन्यथा अणु
		काष्ठा list_head *this;

		list_क्रम_each(this, &c->erase_checking_list) अणु
			काष्ठा jffs2_eraseblock *jeb = list_entry(this, काष्ठा jffs2_eraseblock, list);

			अगर (!(jeb->used_size == 0 && jeb->dirty_size == 0 && jeb->wasted_size == 0)) अणु
				prपूर्णांकk(JFFS2_DBG "erase_checking_list: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
					jeb->offset, jeb->used_size, jeb->dirty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->मुक्त_size);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (list_empty(&c->erase_pending_list)) अणु
		prपूर्णांकk(JFFS2_DBG "erase_pending_list: empty\n");
	पूर्ण अन्यथा अणु
		काष्ठा list_head *this;

		list_क्रम_each(this, &c->erase_pending_list) अणु
			काष्ठा jffs2_eraseblock *jeb = list_entry(this, काष्ठा jffs2_eraseblock, list);

			अगर (!(jeb->used_size == 0 && jeb->dirty_size == 0 && jeb->wasted_size == 0)) अणु
				prपूर्णांकk(JFFS2_DBG "erase_pending_list: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
					jeb->offset, jeb->used_size, jeb->dirty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->मुक्त_size);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (list_empty(&c->erasable_pending_wbuf_list)) अणु
		prपूर्णांकk(JFFS2_DBG "erasable_pending_wbuf_list: empty\n");
	पूर्ण अन्यथा अणु
		काष्ठा list_head *this;

		list_क्रम_each(this, &c->erasable_pending_wbuf_list) अणु
			काष्ठा jffs2_eraseblock *jeb = list_entry(this, काष्ठा jffs2_eraseblock, list);

			अगर (!(jeb->used_size == 0 && jeb->dirty_size == 0 && jeb->wasted_size == 0)) अणु
				prपूर्णांकk(JFFS2_DBG "erasable_pending_wbuf_list: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
					jeb->offset, jeb->used_size, jeb->dirty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->मुक्त_size);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (list_empty(&c->मुक्त_list)) अणु
		prपूर्णांकk(JFFS2_DBG "free_list: empty\n");
	पूर्ण अन्यथा अणु
		काष्ठा list_head *this;

		list_क्रम_each(this, &c->मुक्त_list) अणु
			काष्ठा jffs2_eraseblock *jeb = list_entry(this, काष्ठा jffs2_eraseblock, list);

			अगर (!(jeb->used_size == 0 && jeb->dirty_size == 0 && jeb->wasted_size == 0)) अणु
				prपूर्णांकk(JFFS2_DBG "free_list: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
					jeb->offset, jeb->used_size, jeb->dirty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->मुक्त_size);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (list_empty(&c->bad_list)) अणु
		prपूर्णांकk(JFFS2_DBG "bad_list: empty\n");
	पूर्ण अन्यथा अणु
		काष्ठा list_head *this;

		list_क्रम_each(this, &c->bad_list) अणु
			काष्ठा jffs2_eraseblock *jeb = list_entry(this, काष्ठा jffs2_eraseblock, list);

			अगर (!(jeb->used_size == 0 && jeb->dirty_size == 0 && jeb->wasted_size == 0)) अणु
				prपूर्णांकk(JFFS2_DBG "bad_list: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
					jeb->offset, jeb->used_size, jeb->dirty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->मुक्त_size);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (list_empty(&c->bad_used_list)) अणु
		prपूर्णांकk(JFFS2_DBG "bad_used_list: empty\n");
	पूर्ण अन्यथा अणु
		काष्ठा list_head *this;

		list_क्रम_each(this, &c->bad_used_list) अणु
			काष्ठा jffs2_eraseblock *jeb = list_entry(this, काष्ठा jffs2_eraseblock, list);

			अगर (!(jeb->used_size == 0 && jeb->dirty_size == 0 && jeb->wasted_size == 0)) अणु
				prपूर्णांकk(JFFS2_DBG "bad_used_list: %#08x (used %#08x, dirty %#08x, wasted %#08x, unchecked %#08x, free %#08x)\n",
					jeb->offset, jeb->used_size, jeb->dirty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->मुक्त_size);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम
__jffs2_dbg_dump_fragtree(काष्ठा jffs2_inode_info *f)
अणु
	mutex_lock(&f->sem);
	jffs2_dbg_dump_fragtree_nolock(f);
	mutex_unlock(&f->sem);
पूर्ण

व्योम
__jffs2_dbg_dump_fragtree_nolock(काष्ठा jffs2_inode_info *f)
अणु
	काष्ठा jffs2_node_frag *this = frag_first(&f->fragtree);
	uपूर्णांक32_t lastofs = 0;
	पूर्णांक buggy = 0;

	prपूर्णांकk(JFFS2_DBG_MSG_PREFIX " dump fragtree of ino #%u\n", f->inocache->ino);
	जबतक(this) अणु
		अगर (this->node)
			prपूर्णांकk(JFFS2_DBG "frag %#04x-%#04x: %#08x(%d) on flash (*%p), left (%p), right (%p), parent (%p)\n",
				this->ofs, this->ofs+this->size, ref_offset(this->node->raw),
				ref_flags(this->node->raw), this, frag_left(this), frag_right(this),
				frag_parent(this));
		अन्यथा
			prपूर्णांकk(JFFS2_DBG "frag %#04x-%#04x: hole (*%p). left (%p), right (%p), parent (%p)\n",
				this->ofs, this->ofs+this->size, this, frag_left(this),
				frag_right(this), frag_parent(this));
		अगर (this->ofs != lastofs)
			buggy = 1;
		lastofs = this->ofs + this->size;
		this = frag_next(this);
	पूर्ण

	अगर (f->metadata)
		prपूर्णांकk(JFFS2_DBG "metadata at 0x%08x\n", ref_offset(f->metadata->raw));

	अगर (buggy) अणु
		JFFS2_ERROR("frag tree got a hole in it.\n");
		BUG();
	पूर्ण
पूर्ण

#घोषणा JFFS2_BUFDUMP_BYTES_PER_LINE	32
व्योम
__jffs2_dbg_dump_buffer(अचिन्हित अक्षर *buf, पूर्णांक len, uपूर्णांक32_t offs)
अणु
	पूर्णांक skip;
	पूर्णांक i;

	prपूर्णांकk(JFFS2_DBG_MSG_PREFIX " dump from offset %#08x to offset %#08x (%x bytes).\n",
		offs, offs + len, len);
	i = skip = offs % JFFS2_BUFDUMP_BYTES_PER_LINE;
	offs = offs & ~(JFFS2_BUFDUMP_BYTES_PER_LINE - 1);

	अगर (skip != 0)
		prपूर्णांकk(JFFS2_DBG "%#08x: ", offs);

	जबतक (skip--)
		prपूर्णांकk("   ");

	जबतक (i < len) अणु
		अगर ((i % JFFS2_BUFDUMP_BYTES_PER_LINE) == 0 && i != len -1) अणु
			अगर (i != 0)
				prपूर्णांकk("\n");
			offs += JFFS2_BUFDUMP_BYTES_PER_LINE;
			prपूर्णांकk(JFFS2_DBG "%0#8x: ", offs);
		पूर्ण

		prपूर्णांकk("%02x ", buf[i]);

		i += 1;
	पूर्ण

	prपूर्णांकk("\n");
पूर्ण

/*
 * Dump a JFFS2 node.
 */
व्योम
__jffs2_dbg_dump_node(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t ofs)
अणु
	जोड़ jffs2_node_जोड़ node;
	पूर्णांक len = माप(जोड़ jffs2_node_जोड़);
	माप_प्रकार retlen;
	uपूर्णांक32_t crc;
	पूर्णांक ret;

	prपूर्णांकk(JFFS2_DBG_MSG_PREFIX " dump node at offset %#08x.\n", ofs);

	ret = jffs2_flash_पढ़ो(c, ofs, len, &retlen, (अचिन्हित अक्षर *)&node);
	अगर (ret || (retlen != len)) अणु
		JFFS2_ERROR("read %d bytes failed or short. ret %d, retlen %zd.\n",
			len, ret, retlen);
		वापस;
	पूर्ण

	prपूर्णांकk(JFFS2_DBG "magic:\t%#04x\n", je16_to_cpu(node.u.magic));
	prपूर्णांकk(JFFS2_DBG "nodetype:\t%#04x\n", je16_to_cpu(node.u.nodetype));
	prपूर्णांकk(JFFS2_DBG "totlen:\t%#08x\n", je32_to_cpu(node.u.totlen));
	prपूर्णांकk(JFFS2_DBG "hdr_crc:\t%#08x\n", je32_to_cpu(node.u.hdr_crc));

	crc = crc32(0, &node.u, माप(node.u) - 4);
	अगर (crc != je32_to_cpu(node.u.hdr_crc)) अणु
		JFFS2_ERROR("wrong common header CRC.\n");
		वापस;
	पूर्ण

	अगर (je16_to_cpu(node.u.magic) != JFFS2_MAGIC_BITMASK &&
		je16_to_cpu(node.u.magic) != JFFS2_OLD_MAGIC_BITMASK)
	अणु
		JFFS2_ERROR("wrong node magic: %#04x instead of %#04x.\n",
			je16_to_cpu(node.u.magic), JFFS2_MAGIC_BITMASK);
		वापस;
	पूर्ण

	चयन(je16_to_cpu(node.u.nodetype)) अणु

	हाल JFFS2_NODETYPE_INODE:

		prपूर्णांकk(JFFS2_DBG "the node is inode node\n");
		prपूर्णांकk(JFFS2_DBG "ino:\t%#08x\n", je32_to_cpu(node.i.ino));
		prपूर्णांकk(JFFS2_DBG "version:\t%#08x\n", je32_to_cpu(node.i.version));
		prपूर्णांकk(JFFS2_DBG "mode:\t%#08x\n", node.i.mode.m);
		prपूर्णांकk(JFFS2_DBG "uid:\t%#04x\n", je16_to_cpu(node.i.uid));
		prपूर्णांकk(JFFS2_DBG "gid:\t%#04x\n", je16_to_cpu(node.i.gid));
		prपूर्णांकk(JFFS2_DBG "isize:\t%#08x\n", je32_to_cpu(node.i.isize));
		prपूर्णांकk(JFFS2_DBG "atime:\t%#08x\n", je32_to_cpu(node.i.aसमय));
		prपूर्णांकk(JFFS2_DBG "mtime:\t%#08x\n", je32_to_cpu(node.i.mसमय));
		prपूर्णांकk(JFFS2_DBG "ctime:\t%#08x\n", je32_to_cpu(node.i.स_समय));
		prपूर्णांकk(JFFS2_DBG "offset:\t%#08x\n", je32_to_cpu(node.i.offset));
		prपूर्णांकk(JFFS2_DBG "csize:\t%#08x\n", je32_to_cpu(node.i.csize));
		prपूर्णांकk(JFFS2_DBG "dsize:\t%#08x\n", je32_to_cpu(node.i.dsize));
		prपूर्णांकk(JFFS2_DBG "compr:\t%#02x\n", node.i.compr);
		prपूर्णांकk(JFFS2_DBG "usercompr:\t%#02x\n", node.i.usercompr);
		prपूर्णांकk(JFFS2_DBG "flags:\t%#04x\n", je16_to_cpu(node.i.flags));
		prपूर्णांकk(JFFS2_DBG "data_crc:\t%#08x\n", je32_to_cpu(node.i.data_crc));
		prपूर्णांकk(JFFS2_DBG "node_crc:\t%#08x\n", je32_to_cpu(node.i.node_crc));

		crc = crc32(0, &node.i, माप(node.i) - 8);
		अगर (crc != je32_to_cpu(node.i.node_crc)) अणु
			JFFS2_ERROR("wrong node header CRC.\n");
			वापस;
		पूर्ण
		अवरोध;

	हाल JFFS2_NODETYPE_सूचीENT:

		prपूर्णांकk(JFFS2_DBG "the node is dirent node\n");
		prपूर्णांकk(JFFS2_DBG "pino:\t%#08x\n", je32_to_cpu(node.d.pino));
		prपूर्णांकk(JFFS2_DBG "version:\t%#08x\n", je32_to_cpu(node.d.version));
		prपूर्णांकk(JFFS2_DBG "ino:\t%#08x\n", je32_to_cpu(node.d.ino));
		prपूर्णांकk(JFFS2_DBG "mctime:\t%#08x\n", je32_to_cpu(node.d.mस_समय));
		prपूर्णांकk(JFFS2_DBG "nsize:\t%#02x\n", node.d.nsize);
		prपूर्णांकk(JFFS2_DBG "type:\t%#02x\n", node.d.type);
		prपूर्णांकk(JFFS2_DBG "node_crc:\t%#08x\n", je32_to_cpu(node.d.node_crc));
		prपूर्णांकk(JFFS2_DBG "name_crc:\t%#08x\n", je32_to_cpu(node.d.name_crc));

		node.d.name[node.d.nsize] = '\0';
		prपूर्णांकk(JFFS2_DBG "name:\t\"%s\"\n", node.d.name);

		crc = crc32(0, &node.d, माप(node.d) - 8);
		अगर (crc != je32_to_cpu(node.d.node_crc)) अणु
			JFFS2_ERROR("wrong node header CRC.\n");
			वापस;
		पूर्ण
		अवरोध;

	शेष:
		prपूर्णांकk(JFFS2_DBG "node type is unknown\n");
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* JFFS2_DBG_DUMPS || JFFS2_DBG_PARANOIA_CHECKS */
