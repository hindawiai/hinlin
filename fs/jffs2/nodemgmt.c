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
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/compiler.h>
#समावेश <linux/sched/संकेत.स>
#समावेश "nodelist.h"
#समावेश "debug.h"

/*
 * Check whether the user is allowed to ग_लिखो.
 */
अटल पूर्णांक jffs2_rp_can_ग_लिखो(काष्ठा jffs2_sb_info *c)
अणु
	uपूर्णांक32_t avail;
	काष्ठा jffs2_mount_opts *opts = &c->mount_opts;

	avail = c->dirty_size + c->मुक्त_size + c->unchecked_size +
		c->erasing_size - c->resv_blocks_ग_लिखो * c->sector_size
		- c->nospc_dirty_size;

	अगर (avail < 2 * opts->rp_size)
		jffs2_dbg(1, "rpsize %u, dirty_size %u, free_size %u, "
			  "erasing_size %u, unchecked_size %u, "
			  "nr_erasing_blocks %u, avail %u, resrv %u\n",
			  opts->rp_size, c->dirty_size, c->मुक्त_size,
			  c->erasing_size, c->unchecked_size,
			  c->nr_erasing_blocks, avail, c->nospc_dirty_size);

	अगर (avail > opts->rp_size)
		वापस 1;

	/* Always allow root */
	अगर (capable(CAP_SYS_RESOURCE))
		वापस 1;

	jffs2_dbg(1, "forbid writing\n");
	वापस 0;
पूर्ण

/**
 *	jffs2_reserve_space - request physical space to ग_लिखो nodes to flash
 *	@c: superblock info
 *	@minsize: Minimum acceptable size of allocation
 *	@len: Returned value of allocation length
 *	@prio: Allocation type - ALLOC_अणुNORMAL,DELETIONपूर्ण
 *
 *	Requests a block of physical space on the flash. Returns zero क्रम success
 *	and माला_दो 'len' पूर्णांकo the appropriate place, or वापसs -ENOSPC or other 
 *	error अगर appropriate. Doesn't return len since that's 
 *
 *	If it वापसs zero, jffs2_reserve_space() also करोwns the per-fileप्रणाली
 *	allocation semaphore, to prevent more than one allocation from being
 *	active at any समय. The semaphore is later released by jffs2_commit_allocation()
 *
 *	jffs2_reserve_space() may trigger garbage collection in order to make room
 *	क्रम the requested allocation.
 */

अटल पूर्णांक jffs2_करो_reserve_space(काष्ठा jffs2_sb_info *c,  uपूर्णांक32_t minsize,
				  uपूर्णांक32_t *len, uपूर्णांक32_t sumsize);

पूर्णांक jffs2_reserve_space(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t minsize,
			uपूर्णांक32_t *len, पूर्णांक prio, uपूर्णांक32_t sumsize)
अणु
	पूर्णांक ret = -EAGAIN;
	पूर्णांक blocksneeded = c->resv_blocks_ग_लिखो;
	/* align it */
	minsize = PAD(minsize);

	jffs2_dbg(1, "%s(): Requested 0x%x bytes\n", __func__, minsize);
	mutex_lock(&c->alloc_sem);

	jffs2_dbg(1, "%s(): alloc sem got\n", __func__);

	spin_lock(&c->erase_completion_lock);

	/*
	 * Check अगर the मुक्त space is greater then size of the reserved pool.
	 * If not, only allow root to proceed with writing.
	 */
	अगर (prio != ALLOC_DELETION && !jffs2_rp_can_ग_लिखो(c)) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	/* this needs a little more thought (true <tglx> :)) */
	जबतक(ret == -EAGAIN) अणु
		जबतक(c->nr_मुक्त_blocks + c->nr_erasing_blocks < blocksneeded) अणु
			uपूर्णांक32_t dirty, avail;

			/* calculate real dirty size
			 * dirty_size contains blocks on erase_pending_list
			 * those blocks are counted in c->nr_erasing_blocks.
			 * If one block is actually erased, it is not दीर्घer counted as dirty_space
			 * but it is counted in c->nr_erasing_blocks, so we add it and subtract it
			 * with c->nr_erasing_blocks * c->sector_size again.
			 * Blocks on erasable_list are counted as dirty_size, but not in c->nr_erasing_blocks
			 * This helps us to क्रमce gc and pick eventually a clean block to spपढ़ो the load.
			 * We add unchecked_size here, as we hopefully will find some space to use.
			 * This will affect the sum only once, as gc first finishes checking
			 * of nodes.
			 */
			dirty = c->dirty_size + c->erasing_size - c->nr_erasing_blocks * c->sector_size + c->unchecked_size;
			अगर (dirty < c->nospc_dirty_size) अणु
				अगर (prio == ALLOC_DELETION && c->nr_मुक्त_blocks + c->nr_erasing_blocks >= c->resv_blocks_deletion) अणु
					jffs2_dbg(1, "%s(): Low on dirty space to GC, but it's a deletion. Allowing...\n",
						  __func__);
					अवरोध;
				पूर्ण
				jffs2_dbg(1, "dirty size 0x%08x + unchecked_size 0x%08x < nospc_dirty_size 0x%08x, returning -ENOSPC\n",
					  dirty, c->unchecked_size,
					  c->sector_size);

				spin_unlock(&c->erase_completion_lock);
				mutex_unlock(&c->alloc_sem);
				वापस -ENOSPC;
			पूर्ण

			/* Calc possibly available space. Possibly available means that we
			 * करोn't know, अगर unchecked size contains obsoleted nodes, which could give us some
			 * more usable space. This will affect the sum only once, as gc first finishes checking
			 * of nodes.
			 + Return -ENOSPC, अगर the maximum possibly available space is less or equal than
			 * blocksneeded * sector_size.
			 * This blocks endless gc looping on a fileप्रणाली, which is nearly full, even अगर
			 * the check above passes.
			 */
			avail = c->मुक्त_size + c->dirty_size + c->erasing_size + c->unchecked_size;
			अगर ( (avail / c->sector_size) <= blocksneeded) अणु
				अगर (prio == ALLOC_DELETION && c->nr_मुक्त_blocks + c->nr_erasing_blocks >= c->resv_blocks_deletion) अणु
					jffs2_dbg(1, "%s(): Low on possibly available space, but it's a deletion. Allowing...\n",
						  __func__);
					अवरोध;
				पूर्ण

				jffs2_dbg(1, "max. available size 0x%08x  < blocksneeded * sector_size 0x%08x, returning -ENOSPC\n",
					  avail, blocksneeded * c->sector_size);
				spin_unlock(&c->erase_completion_lock);
				mutex_unlock(&c->alloc_sem);
				वापस -ENOSPC;
			पूर्ण

			mutex_unlock(&c->alloc_sem);

			jffs2_dbg(1, "Triggering GC pass. nr_free_blocks %d, nr_erasing_blocks %d, free_size 0x%08x, dirty_size 0x%08x, wasted_size 0x%08x, used_size 0x%08x, erasing_size 0x%08x, bad_size 0x%08x (total 0x%08x of 0x%08x)\n",
				  c->nr_मुक्त_blocks, c->nr_erasing_blocks,
				  c->मुक्त_size, c->dirty_size, c->wasted_size,
				  c->used_size, c->erasing_size, c->bad_size,
				  c->मुक्त_size + c->dirty_size +
				  c->wasted_size + c->used_size +
				  c->erasing_size + c->bad_size,
				  c->flash_size);
			spin_unlock(&c->erase_completion_lock);

			ret = jffs2_garbage_collect_pass(c);

			अगर (ret == -EAGAIN) अणु
				spin_lock(&c->erase_completion_lock);
				अगर (c->nr_erasing_blocks &&
				    list_empty(&c->erase_pending_list) &&
				    list_empty(&c->erase_complete_list)) अणु
					DECLARE_WAITQUEUE(रुको, current);
					set_current_state(TASK_UNINTERRUPTIBLE);
					add_रुको_queue(&c->erase_रुको, &रुको);
					jffs2_dbg(1, "%s waiting for erase to complete\n",
						  __func__);
					spin_unlock(&c->erase_completion_lock);

					schedule();
					हटाओ_रुको_queue(&c->erase_रुको, &रुको);
				पूर्ण अन्यथा
					spin_unlock(&c->erase_completion_lock);
			पूर्ण अन्यथा अगर (ret)
				वापस ret;

			cond_resched();

			अगर (संकेत_pending(current))
				वापस -EINTR;

			mutex_lock(&c->alloc_sem);
			spin_lock(&c->erase_completion_lock);
		पूर्ण

		ret = jffs2_करो_reserve_space(c, minsize, len, sumsize);
		अगर (ret) अणु
			jffs2_dbg(1, "%s(): ret is %d\n", __func__, ret);
		पूर्ण
	पूर्ण

out:
	spin_unlock(&c->erase_completion_lock);
	अगर (!ret)
		ret = jffs2_pपुनः_स्मृति_raw_node_refs(c, c->nextblock, 1);
	अगर (ret)
		mutex_unlock(&c->alloc_sem);
	वापस ret;
पूर्ण

पूर्णांक jffs2_reserve_space_gc(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t minsize,
			   uपूर्णांक32_t *len, uपूर्णांक32_t sumsize)
अणु
	पूर्णांक ret;
	minsize = PAD(minsize);

	jffs2_dbg(1, "%s(): Requested 0x%x bytes\n", __func__, minsize);

	जबतक (true) अणु
		spin_lock(&c->erase_completion_lock);
		ret = jffs2_करो_reserve_space(c, minsize, len, sumsize);
		अगर (ret) अणु
			jffs2_dbg(1, "%s(): looping, ret is %d\n",
				  __func__, ret);
		पूर्ण
		spin_unlock(&c->erase_completion_lock);

		अगर (ret == -EAGAIN)
			cond_resched();
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (!ret)
		ret = jffs2_pपुनः_स्मृति_raw_node_refs(c, c->nextblock, 1);

	वापस ret;
पूर्ण


/* Classअगरy nextblock (clean, dirty of verydirty) and क्रमce to select an other one */

अटल व्योम jffs2_बंद_nextblock(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb)
अणु

	अगर (c->nextblock == शून्य) अणु
		jffs2_dbg(1, "%s(): Erase block at 0x%08x has already been placed in a list\n",
			  __func__, jeb->offset);
		वापस;
	पूर्ण
	/* Check, अगर we have a dirty block now, or अगर it was dirty alपढ़ोy */
	अगर (ISसूचीTY (jeb->wasted_size + jeb->dirty_size)) अणु
		c->dirty_size += jeb->wasted_size;
		c->wasted_size -= jeb->wasted_size;
		jeb->dirty_size += jeb->wasted_size;
		jeb->wasted_size = 0;
		अगर (VERYसूचीTY(c, jeb->dirty_size)) अणु
			jffs2_dbg(1, "Adding full erase block at 0x%08x to very_dirty_list (free 0x%08x, dirty 0x%08x, used 0x%08x\n",
				  jeb->offset, jeb->मुक्त_size, jeb->dirty_size,
				  jeb->used_size);
			list_add_tail(&jeb->list, &c->very_dirty_list);
		पूर्ण अन्यथा अणु
			jffs2_dbg(1, "Adding full erase block at 0x%08x to dirty_list (free 0x%08x, dirty 0x%08x, used 0x%08x\n",
				  jeb->offset, jeb->मुक्त_size, jeb->dirty_size,
				  jeb->used_size);
			list_add_tail(&jeb->list, &c->dirty_list);
		पूर्ण
	पूर्ण अन्यथा अणु
		jffs2_dbg(1, "Adding full erase block at 0x%08x to clean_list (free 0x%08x, dirty 0x%08x, used 0x%08x\n",
			  jeb->offset, jeb->मुक्त_size, jeb->dirty_size,
			  jeb->used_size);
		list_add_tail(&jeb->list, &c->clean_list);
	पूर्ण
	c->nextblock = शून्य;

पूर्ण

/* Select a new jeb क्रम nextblock */

अटल पूर्णांक jffs2_find_nextblock(काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा list_head *next;

	/* Take the next block off the 'free' list */

	अगर (list_empty(&c->मुक्त_list)) अणु

		अगर (!c->nr_erasing_blocks &&
			!list_empty(&c->erasable_list)) अणु
			काष्ठा jffs2_eraseblock *ejeb;

			ejeb = list_entry(c->erasable_list.next, काष्ठा jffs2_eraseblock, list);
			list_move_tail(&ejeb->list, &c->erase_pending_list);
			c->nr_erasing_blocks++;
			jffs2_garbage_collect_trigger(c);
			jffs2_dbg(1, "%s(): Triggering erase of erasable block at 0x%08x\n",
				  __func__, ejeb->offset);
		पूर्ण

		अगर (!c->nr_erasing_blocks &&
			!list_empty(&c->erasable_pending_wbuf_list)) अणु
			jffs2_dbg(1, "%s(): Flushing write buffer\n",
				  __func__);
			/* c->nextblock is शून्य, no update to c->nextblock allowed */
			spin_unlock(&c->erase_completion_lock);
			jffs2_flush_wbuf_pad(c);
			spin_lock(&c->erase_completion_lock);
			/* Have another go. It'll be on the erasable_list now */
			वापस -EAGAIN;
		पूर्ण

		अगर (!c->nr_erasing_blocks) अणु
			/* Ouch. We're in GC, or we wouldn't have got here.
			   And there's no space left. At all. */
			pr_crit("Argh. No free space left for GC. nr_erasing_blocks is %d. nr_free_blocks is %d. (erasableempty: %s, erasingempty: %s, erasependingempty: %s)\n",
				c->nr_erasing_blocks, c->nr_मुक्त_blocks,
				list_empty(&c->erasable_list) ? "yes" : "no",
				list_empty(&c->erasing_list) ? "yes" : "no",
				list_empty(&c->erase_pending_list) ? "yes" : "no");
			वापस -ENOSPC;
		पूर्ण

		spin_unlock(&c->erase_completion_lock);
		/* Don't रुको क्रम it; just erase one right now */
		jffs2_erase_pending_blocks(c, 1);
		spin_lock(&c->erase_completion_lock);

		/* An erase may have failed, decreasing the
		   amount of मुक्त space available. So we must
		   restart from the beginning */
		वापस -EAGAIN;
	पूर्ण

	next = c->मुक्त_list.next;
	list_del(next);
	c->nextblock = list_entry(next, काष्ठा jffs2_eraseblock, list);
	c->nr_मुक्त_blocks--;

	jffs2_sum_reset_collected(c->summary); /* reset collected summary */

#अगर_घोषित CONFIG_JFFS2_FS_WRITEBUFFER
	/* adjust ग_लिखो buffer offset, अन्यथा we get a non contiguous ग_लिखो bug */
	अगर (!(c->wbuf_ofs % c->sector_size) && !c->wbuf_len)
		c->wbuf_ofs = 0xffffffff;
#पूर्ण_अगर

	jffs2_dbg(1, "%s(): new nextblock = 0x%08x\n",
		  __func__, c->nextblock->offset);

	वापस 0;
पूर्ण

/* Called with alloc sem _and_ erase_completion_lock */
अटल पूर्णांक jffs2_करो_reserve_space(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t minsize,
				  uपूर्णांक32_t *len, uपूर्णांक32_t sumsize)
अणु
	काष्ठा jffs2_eraseblock *jeb = c->nextblock;
	uपूर्णांक32_t reserved_size;				/* क्रम summary inक्रमmation at the end of the jeb */
	पूर्णांक ret;

 restart:
	reserved_size = 0;

	अगर (jffs2_sum_active() && (sumsize != JFFS2_SUMMARY_NOSUM_SIZE)) अणु
							/* NOSUM_SIZE means not to generate summary */

		अगर (jeb) अणु
			reserved_size = PAD(sumsize + c->summary->sum_size + JFFS2_SUMMARY_FRAME_SIZE);
			dbg_summary("minsize=%d , jeb->free=%d ,"
						"summary->size=%d , sumsize=%d\n",
						minsize, jeb->मुक्त_size,
						c->summary->sum_size, sumsize);
		पूर्ण

		/* Is there enough space क्रम writing out the current node, or we have to
		   ग_लिखो out summary inक्रमmation now, बंद this jeb and select new nextblock? */
		अगर (jeb && (PAD(minsize) + PAD(c->summary->sum_size + sumsize +
					JFFS2_SUMMARY_FRAME_SIZE) > jeb->मुक्त_size)) अणु

			/* Has summary been disabled क्रम this jeb? */
			अगर (jffs2_sum_is_disabled(c->summary)) अणु
				sumsize = JFFS2_SUMMARY_NOSUM_SIZE;
				जाओ restart;
			पूर्ण

			/* Writing out the collected summary inक्रमmation */
			dbg_summary("generating summary for 0x%08x.\n", jeb->offset);
			ret = jffs2_sum_ग_लिखो_sumnode(c);

			अगर (ret)
				वापस ret;

			अगर (jffs2_sum_is_disabled(c->summary)) अणु
				/* jffs2_ग_लिखो_sumnode() couldn't ग_लिखो out the summary inक्रमmation
				   diabling summary क्रम this jeb and मुक्त the collected inक्रमmation
				 */
				sumsize = JFFS2_SUMMARY_NOSUM_SIZE;
				जाओ restart;
			पूर्ण

			jffs2_बंद_nextblock(c, jeb);
			jeb = शून्य;
			/* keep always valid value in reserved_size */
			reserved_size = PAD(sumsize + c->summary->sum_size + JFFS2_SUMMARY_FRAME_SIZE);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (jeb && minsize > jeb->मुक्त_size) अणु
			uपूर्णांक32_t waste;

			/* Skip the end of this block and file it as having some dirty space */
			/* If there's a pending ग_लिखो to it, flush now */

			अगर (jffs2_wbuf_dirty(c)) अणु
				spin_unlock(&c->erase_completion_lock);
				jffs2_dbg(1, "%s(): Flushing write buffer\n",
					  __func__);
				jffs2_flush_wbuf_pad(c);
				spin_lock(&c->erase_completion_lock);
				jeb = c->nextblock;
				जाओ restart;
			पूर्ण

			spin_unlock(&c->erase_completion_lock);

			ret = jffs2_pपुनः_स्मृति_raw_node_refs(c, jeb, 1);

			/* Just lock it again and जारी. Nothing much can change because
			   we hold c->alloc_sem anyway. In fact, it's not entirely clear why
			   we hold c->erase_completion_lock in the majority of this function...
			   but that's a question क्रम another (more caffeine-rich) day. */
			spin_lock(&c->erase_completion_lock);

			अगर (ret)
				वापस ret;

			waste = jeb->मुक्त_size;
			jffs2_link_node_ref(c, jeb,
					    (jeb->offset + c->sector_size - waste) | REF_OBSOLETE,
					    waste, शून्य);
			/* FIXME: that made it count as dirty. Convert to wasted */
			jeb->dirty_size -= waste;
			c->dirty_size -= waste;
			jeb->wasted_size += waste;
			c->wasted_size += waste;

			jffs2_बंद_nextblock(c, jeb);
			jeb = शून्य;
		पूर्ण
	पूर्ण

	अगर (!jeb) अणु

		ret = jffs2_find_nextblock(c);
		अगर (ret)
			वापस ret;

		jeb = c->nextblock;

		अगर (jeb->मुक्त_size != c->sector_size - c->cleanmarker_size) अणु
			pr_warn("Eep. Block 0x%08x taken from free_list had free_size of 0x%08x!!\n",
				jeb->offset, jeb->मुक्त_size);
			जाओ restart;
		पूर्ण
	पूर्ण
	/* OK, jeb (==c->nextblock) is now poपूर्णांकing at a block which definitely has
	   enough space */
	*len = jeb->मुक्त_size - reserved_size;

	अगर (c->cleanmarker_size && jeb->used_size == c->cleanmarker_size &&
	    !jeb->first_node->next_in_ino) अणु
		/* Only node in it beक्रमehand was a CLEANMARKER node (we think).
		   So mark it obsolete now that there's going to be another node
		   in the block. This will reduce used_size to zero but We've
		   alपढ़ोy set c->nextblock so that jffs2_mark_node_obsolete()
		   won't try to refile it to the dirty_list.
		*/
		spin_unlock(&c->erase_completion_lock);
		jffs2_mark_node_obsolete(c, jeb->first_node);
		spin_lock(&c->erase_completion_lock);
	पूर्ण

	jffs2_dbg(1, "%s(): Giving 0x%x bytes at 0x%x\n",
		  __func__,
		  *len, jeb->offset + (c->sector_size - jeb->मुक्त_size));
	वापस 0;
पूर्ण

/**
 *	jffs2_add_physical_node_ref - add a physical node reference to the list
 *	@c: superblock info
 *	@new: new node reference to add
 *	@len: length of this physical node
 *
 *	Should only be used to report nodes क्रम which space has been allocated
 *	by jffs2_reserve_space.
 *
 *	Must be called with the alloc_sem held.
 */

काष्ठा jffs2_raw_node_ref *jffs2_add_physical_node_ref(काष्ठा jffs2_sb_info *c,
						       uपूर्णांक32_t ofs, uपूर्णांक32_t len,
						       काष्ठा jffs2_inode_cache *ic)
अणु
	काष्ठा jffs2_eraseblock *jeb;
	काष्ठा jffs2_raw_node_ref *new;

	jeb = &c->blocks[ofs / c->sector_size];

	jffs2_dbg(1, "%s(): Node at 0x%x(%d), size 0x%x\n",
		  __func__, ofs & ~3, ofs & 3, len);
#अगर 1
	/* Allow non-obsolete nodes only to be added at the end of c->nextblock, 
	   अगर c->nextblock is set. Note that wbuf.c will file obsolete nodes
	   even after refiling c->nextblock */
	अगर ((c->nextblock || ((ofs & 3) != REF_OBSOLETE))
	    && (jeb != c->nextblock || (ofs & ~3) != jeb->offset + (c->sector_size - jeb->मुक्त_size))) अणु
		pr_warn("argh. node added in wrong place at 0x%08x(%d)\n",
			ofs & ~3, ofs & 3);
		अगर (c->nextblock)
			pr_warn("nextblock 0x%08x", c->nextblock->offset);
		अन्यथा
			pr_warn("No nextblock");
		pr_cont(", expected at %08x\n",
			jeb->offset + (c->sector_size - jeb->मुक्त_size));
		वापस ERR_PTR(-EINVAL);
	पूर्ण
#पूर्ण_अगर
	spin_lock(&c->erase_completion_lock);

	new = jffs2_link_node_ref(c, jeb, ofs, len, ic);

	अगर (!jeb->मुक्त_size && !jeb->dirty_size && !ISसूचीTY(jeb->wasted_size)) अणु
		/* If it lives on the dirty_list, jffs2_reserve_space will put it there */
		jffs2_dbg(1, "Adding full erase block at 0x%08x to clean_list (free 0x%08x, dirty 0x%08x, used 0x%08x\n",
			  jeb->offset, jeb->मुक्त_size, jeb->dirty_size,
			  jeb->used_size);
		अगर (jffs2_wbuf_dirty(c)) अणु
			/* Flush the last ग_लिखो in the block अगर it's outstanding */
			spin_unlock(&c->erase_completion_lock);
			jffs2_flush_wbuf_pad(c);
			spin_lock(&c->erase_completion_lock);
		पूर्ण

		list_add_tail(&jeb->list, &c->clean_list);
		c->nextblock = शून्य;
	पूर्ण
	jffs2_dbg_acct_sanity_check_nolock(c,jeb);
	jffs2_dbg_acct_paranoia_check_nolock(c, jeb);

	spin_unlock(&c->erase_completion_lock);

	वापस new;
पूर्ण


व्योम jffs2_complete_reservation(काष्ठा jffs2_sb_info *c)
अणु
	jffs2_dbg(1, "jffs2_complete_reservation()\n");
	spin_lock(&c->erase_completion_lock);
	jffs2_garbage_collect_trigger(c);
	spin_unlock(&c->erase_completion_lock);
	mutex_unlock(&c->alloc_sem);
पूर्ण

अटल अंतरभूत पूर्णांक on_list(काष्ठा list_head *obj, काष्ठा list_head *head)
अणु
	काष्ठा list_head *this;

	list_क्रम_each(this, head) अणु
		अगर (this == obj) अणु
			jffs2_dbg(1, "%p is on list at %p\n", obj, head);
			वापस 1;

		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम jffs2_mark_node_obsolete(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_raw_node_ref *ref)
अणु
	काष्ठा jffs2_eraseblock *jeb;
	पूर्णांक blocknr;
	काष्ठा jffs2_unknown_node n;
	पूर्णांक ret, addedsize;
	माप_प्रकार retlen;
	uपूर्णांक32_t मुक्तd_len;

	अगर(unlikely(!ref)) अणु
		pr_notice("EEEEEK. jffs2_mark_node_obsolete called with NULL node\n");
		वापस;
	पूर्ण
	अगर (ref_obsolete(ref)) अणु
		jffs2_dbg(1, "%s(): called with already obsolete node at 0x%08x\n",
			  __func__, ref_offset(ref));
		वापस;
	पूर्ण
	blocknr = ref->flash_offset / c->sector_size;
	अगर (blocknr >= c->nr_blocks) अणु
		pr_notice("raw node at 0x%08x is off the end of device!\n",
			  ref->flash_offset);
		BUG();
	पूर्ण
	jeb = &c->blocks[blocknr];

	अगर (jffs2_can_mark_obsolete(c) && !jffs2_is_पढ़ोonly(c) &&
	    !(c->flags & (JFFS2_SB_FLAG_SCANNING | JFFS2_SB_FLAG_BUILDING))) अणु
		/* Hm. This may confuse अटल lock analysis. If any of the above
		   three conditions is false, we're going to वापस from this
		   function without actually obliterating any nodes or मुक्तing
		   any jffs2_raw_node_refs. So we करोn't need to stop erases from
		   happening, or protect against people holding an obsolete
		   jffs2_raw_node_ref without the erase_completion_lock. */
		mutex_lock(&c->erase_मुक्त_sem);
	पूर्ण

	spin_lock(&c->erase_completion_lock);

	मुक्तd_len = ref_totlen(c, jeb, ref);

	अगर (ref_flags(ref) == REF_UNCHECKED) अणु
		D1(अगर (unlikely(jeb->unchecked_size < मुक्तd_len)) अणु
				pr_notice("raw unchecked node of size 0x%08x freed from erase block %d at 0x%08x, but unchecked_size was already 0x%08x\n",
					  मुक्तd_len, blocknr,
					  ref->flash_offset, jeb->used_size);
			BUG();
		पूर्ण)
			jffs2_dbg(1, "Obsoleting previously unchecked node at 0x%08x of len %x\n",
				  ref_offset(ref), मुक्तd_len);
		jeb->unchecked_size -= मुक्तd_len;
		c->unchecked_size -= मुक्तd_len;
	पूर्ण अन्यथा अणु
		D1(अगर (unlikely(jeb->used_size < मुक्तd_len)) अणु
				pr_notice("raw node of size 0x%08x freed from erase block %d at 0x%08x, but used_size was already 0x%08x\n",
					  मुक्तd_len, blocknr,
					  ref->flash_offset, jeb->used_size);
			BUG();
		पूर्ण)
			jffs2_dbg(1, "Obsoleting node at 0x%08x of len %#x: ",
				  ref_offset(ref), मुक्तd_len);
		jeb->used_size -= मुक्तd_len;
		c->used_size -= मुक्तd_len;
	पूर्ण

	// Take care, that wasted size is taken पूर्णांकo concern
	अगर ((jeb->dirty_size || ISसूचीTY(jeb->wasted_size + मुक्तd_len)) && jeb != c->nextblock) अणु
		jffs2_dbg(1, "Dirtying\n");
		addedsize = मुक्तd_len;
		jeb->dirty_size += मुक्तd_len;
		c->dirty_size += मुक्तd_len;

		/* Convert wasted space to dirty, अगर not a bad block */
		अगर (jeb->wasted_size) अणु
			अगर (on_list(&jeb->list, &c->bad_used_list)) अणु
				jffs2_dbg(1, "Leaving block at %08x on the bad_used_list\n",
					  jeb->offset);
				addedsize = 0; /* To fool the refiling code later */
			पूर्ण अन्यथा अणु
				jffs2_dbg(1, "Converting %d bytes of wasted space to dirty in block at %08x\n",
					  jeb->wasted_size, jeb->offset);
				addedsize += jeb->wasted_size;
				jeb->dirty_size += jeb->wasted_size;
				c->dirty_size += jeb->wasted_size;
				c->wasted_size -= jeb->wasted_size;
				jeb->wasted_size = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		jffs2_dbg(1, "Wasting\n");
		addedsize = 0;
		jeb->wasted_size += मुक्तd_len;
		c->wasted_size += मुक्तd_len;
	पूर्ण
	ref->flash_offset = ref_offset(ref) | REF_OBSOLETE;

	jffs2_dbg_acct_sanity_check_nolock(c, jeb);
	jffs2_dbg_acct_paranoia_check_nolock(c, jeb);

	अगर (c->flags & JFFS2_SB_FLAG_SCANNING) अणु
		/* Flash scanning is in progress. Don't muck about with the block
		   lists because they're not ready yet, and don't actually
		   obliterate nodes that look obsolete. If they weren't
		   marked obsolete on the flash at the समय they _became_
		   obsolete, there was probably a reason क्रम that. */
		spin_unlock(&c->erase_completion_lock);
		/* We didn't lock the erase_मुक्त_sem */
		वापस;
	पूर्ण

	अगर (jeb == c->nextblock) अणु
		jffs2_dbg(2, "Not moving nextblock 0x%08x to dirty/erase_pending list\n",
			  jeb->offset);
	पूर्ण अन्यथा अगर (!jeb->used_size && !jeb->unchecked_size) अणु
		अगर (jeb == c->gcblock) अणु
			jffs2_dbg(1, "gcblock at 0x%08x completely dirtied. Clearing gcblock...\n",
				  jeb->offset);
			c->gcblock = शून्य;
		पूर्ण अन्यथा अणु
			jffs2_dbg(1, "Eraseblock at 0x%08x completely dirtied. Removing from (dirty?) list...\n",
				  jeb->offset);
			list_del(&jeb->list);
		पूर्ण
		अगर (jffs2_wbuf_dirty(c)) अणु
			jffs2_dbg(1, "...and adding to erasable_pending_wbuf_list\n");
			list_add_tail(&jeb->list, &c->erasable_pending_wbuf_list);
		पूर्ण अन्यथा अणु
			अगर (jअगरfies & 127) अणु
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
		jffs2_dbg(1, "Done OK\n");
	पूर्ण अन्यथा अगर (jeb == c->gcblock) अणु
		jffs2_dbg(2, "Not moving gcblock 0x%08x to dirty_list\n",
			  jeb->offset);
	पूर्ण अन्यथा अगर (ISसूचीTY(jeb->dirty_size) && !ISसूचीTY(jeb->dirty_size - addedsize)) अणु
		jffs2_dbg(1, "Eraseblock at 0x%08x is freshly dirtied. Removing from clean list...\n",
			  jeb->offset);
		list_del(&jeb->list);
		jffs2_dbg(1, "...and adding to dirty_list\n");
		list_add_tail(&jeb->list, &c->dirty_list);
	पूर्ण अन्यथा अगर (VERYसूचीTY(c, jeb->dirty_size) &&
		   !VERYसूचीTY(c, jeb->dirty_size - addedsize)) अणु
		jffs2_dbg(1, "Eraseblock at 0x%08x is now very dirty. Removing from dirty list...\n",
			  jeb->offset);
		list_del(&jeb->list);
		jffs2_dbg(1, "...and adding to very_dirty_list\n");
		list_add_tail(&jeb->list, &c->very_dirty_list);
	पूर्ण अन्यथा अणु
		jffs2_dbg(1, "Eraseblock at 0x%08x not moved anywhere. (free 0x%08x, dirty 0x%08x, used 0x%08x)\n",
			  jeb->offset, jeb->मुक्त_size, jeb->dirty_size,
			  jeb->used_size);
	पूर्ण

	spin_unlock(&c->erase_completion_lock);

	अगर (!jffs2_can_mark_obsolete(c) || jffs2_is_पढ़ोonly(c) ||
		(c->flags & JFFS2_SB_FLAG_BUILDING)) अणु
		/* We didn't lock the erase_मुक्त_sem */
		वापस;
	पूर्ण

	/* The erase_मुक्त_sem is locked, and has been since beक्रमe we marked the node obsolete
	   and potentially put its eraseblock onto the erase_pending_list. Thus, we know that
	   the block hasn't _already_ been erased, and that 'ref' itself hasn't been मुक्तd yet
	   by jffs2_मुक्त_jeb_node_refs() in erase.c. Which is nice. */

	jffs2_dbg(1, "obliterating obsoleted node at 0x%08x\n",
		  ref_offset(ref));
	ret = jffs2_flash_पढ़ो(c, ref_offset(ref), माप(n), &retlen, (अक्षर *)&n);
	अगर (ret) अणु
		pr_warn("Read error reading from obsoleted node at 0x%08x: %d\n",
			ref_offset(ref), ret);
		जाओ out_erase_sem;
	पूर्ण
	अगर (retlen != माप(n)) अणु
		pr_warn("Short read from obsoleted node at 0x%08x: %zd\n",
			ref_offset(ref), retlen);
		जाओ out_erase_sem;
	पूर्ण
	अगर (PAD(je32_to_cpu(n.totlen)) != PAD(मुक्तd_len)) अणु
		pr_warn("Node totlen on flash (0x%08x) != totlen from node ref (0x%08x)\n",
			je32_to_cpu(n.totlen), मुक्तd_len);
		जाओ out_erase_sem;
	पूर्ण
	अगर (!(je16_to_cpu(n.nodetype) & JFFS2_NODE_ACCURATE)) अणु
		jffs2_dbg(1, "Node at 0x%08x was already marked obsolete (nodetype 0x%04x)\n",
			  ref_offset(ref), je16_to_cpu(n.nodetype));
		जाओ out_erase_sem;
	पूर्ण
	/* XXX FIXME: This is ugly now */
	n.nodetype = cpu_to_je16(je16_to_cpu(n.nodetype) & ~JFFS2_NODE_ACCURATE);
	ret = jffs2_flash_ग_लिखो(c, ref_offset(ref), माप(n), &retlen, (अक्षर *)&n);
	अगर (ret) अणु
		pr_warn("Write error in obliterating obsoleted node at 0x%08x: %d\n",
			ref_offset(ref), ret);
		जाओ out_erase_sem;
	पूर्ण
	अगर (retlen != माप(n)) अणु
		pr_warn("Short write in obliterating obsoleted node at 0x%08x: %zd\n",
			ref_offset(ref), retlen);
		जाओ out_erase_sem;
	पूर्ण

	/* Nodes which have been marked obsolete no दीर्घer need to be
	   associated with any inode. Remove them from the per-inode list.

	   Note we can't करो this क्रम न_अंकD at the moment because we need
	   obsolete dirent nodes to stay on the lists, because of the
	   horridness in jffs2_garbage_collect_deletion_dirent(). Also
	   because we delete the inocache, and on न_अंकD we need that to
	   stay around until all the nodes are actually erased, in order
	   to stop us from giving the same inode number to another newly
	   created inode. */
	अगर (ref->next_in_ino) अणु
		काष्ठा jffs2_inode_cache *ic;
		काष्ठा jffs2_raw_node_ref **p;

		spin_lock(&c->erase_completion_lock);

		ic = jffs2_raw_ref_to_ic(ref);
		क्रम (p = &ic->nodes; (*p) != ref; p = &((*p)->next_in_ino))
			;

		*p = ref->next_in_ino;
		ref->next_in_ino = शून्य;

		चयन (ic->class) अणु
#अगर_घोषित CONFIG_JFFS2_FS_XATTR
			हाल RAWNODE_CLASS_XATTR_DATUM:
				jffs2_release_xattr_datum(c, (काष्ठा jffs2_xattr_datum *)ic);
				अवरोध;
			हाल RAWNODE_CLASS_XATTR_REF:
				jffs2_release_xattr_ref(c, (काष्ठा jffs2_xattr_ref *)ic);
				अवरोध;
#पूर्ण_अगर
			शेष:
				अगर (ic->nodes == (व्योम *)ic && ic->pino_nlink == 0)
					jffs2_del_ino_cache(c, ic);
				अवरोध;
		पूर्ण
		spin_unlock(&c->erase_completion_lock);
	पूर्ण

 out_erase_sem:
	mutex_unlock(&c->erase_मुक्त_sem);
पूर्ण

पूर्णांक jffs2_thपढ़ो_should_wake(काष्ठा jffs2_sb_info *c)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t dirty;
	पूर्णांक nr_very_dirty = 0;
	काष्ठा jffs2_eraseblock *jeb;

	अगर (!list_empty(&c->erase_complete_list) ||
	    !list_empty(&c->erase_pending_list))
		वापस 1;

	अगर (c->unchecked_size) अणु
		jffs2_dbg(1, "jffs2_thread_should_wake(): unchecked_size %d, check_ino #%d\n",
			  c->unchecked_size, c->check_ino);
		वापस 1;
	पूर्ण

	/* dirty_size contains blocks on erase_pending_list
	 * those blocks are counted in c->nr_erasing_blocks.
	 * If one block is actually erased, it is not दीर्घer counted as dirty_space
	 * but it is counted in c->nr_erasing_blocks, so we add it and subtract it
	 * with c->nr_erasing_blocks * c->sector_size again.
	 * Blocks on erasable_list are counted as dirty_size, but not in c->nr_erasing_blocks
	 * This helps us to क्रमce gc and pick eventually a clean block to spपढ़ो the load.
	 */
	dirty = c->dirty_size + c->erasing_size - c->nr_erasing_blocks * c->sector_size;

	अगर (c->nr_मुक्त_blocks + c->nr_erasing_blocks < c->resv_blocks_gctrigger &&
			(dirty > c->nospc_dirty_size))
		ret = 1;

	list_क्रम_each_entry(jeb, &c->very_dirty_list, list) अणु
		nr_very_dirty++;
		अगर (nr_very_dirty == c->vdirty_blocks_gctrigger) अणु
			ret = 1;
			/* In debug mode, actually go through and count them all */
			D1(जारी);
			अवरोध;
		पूर्ण
	पूर्ण

	jffs2_dbg(1, "%s(): nr_free_blocks %d, nr_erasing_blocks %d, dirty_size 0x%x, vdirty_blocks %d: %s\n",
		  __func__, c->nr_मुक्त_blocks, c->nr_erasing_blocks,
		  c->dirty_size, nr_very_dirty, ret ? "yes" : "no");

	वापस ret;
पूर्ण
