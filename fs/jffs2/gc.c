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
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/crc32.h>
#समावेश <linux/compiler.h>
#समावेश <linux/स्थिति.स>
#समावेश "nodelist.h"
#समावेश "compr.h"

अटल पूर्णांक jffs2_garbage_collect_pristine(काष्ठा jffs2_sb_info *c,
					  काष्ठा jffs2_inode_cache *ic,
					  काष्ठा jffs2_raw_node_ref *raw);
अटल पूर्णांक jffs2_garbage_collect_metadata(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
					काष्ठा jffs2_inode_info *f, काष्ठा jffs2_full_dnode *fd);
अटल पूर्णांक jffs2_garbage_collect_dirent(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
					काष्ठा jffs2_inode_info *f, काष्ठा jffs2_full_dirent *fd);
अटल पूर्णांक jffs2_garbage_collect_deletion_dirent(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
					काष्ठा jffs2_inode_info *f, काष्ठा jffs2_full_dirent *fd);
अटल पूर्णांक jffs2_garbage_collect_hole(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				      काष्ठा jffs2_inode_info *f, काष्ठा jffs2_full_dnode *fn,
				      uपूर्णांक32_t start, uपूर्णांक32_t end);
अटल पूर्णांक jffs2_garbage_collect_dnode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				       काष्ठा jffs2_inode_info *f, काष्ठा jffs2_full_dnode *fn,
				       uपूर्णांक32_t start, uपूर्णांक32_t end);
अटल पूर्णांक jffs2_garbage_collect_live(काष्ठा jffs2_sb_info *c,  काष्ठा jffs2_eraseblock *jeb,
			       काष्ठा jffs2_raw_node_ref *raw, काष्ठा jffs2_inode_info *f);

/* Called with erase_completion_lock held */
अटल काष्ठा jffs2_eraseblock *jffs2_find_gc_block(काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा jffs2_eraseblock *ret;
	काष्ठा list_head *nextlist = शून्य;
	पूर्णांक n = jअगरfies % 128;

	/* Pick an eraseblock to garbage collect next. This is where we'll
	   put the clever wear-levelling algorithms. Eventually.  */
	/* We possibly want to favour the dirtier blocks more when the
	   number of मुक्त blocks is low. */
again:
	अगर (!list_empty(&c->bad_used_list) && c->nr_मुक्त_blocks > c->resv_blocks_gcbad) अणु
		jffs2_dbg(1, "Picking block from bad_used_list to GC next\n");
		nextlist = &c->bad_used_list;
	पूर्ण अन्यथा अगर (n < 50 && !list_empty(&c->erasable_list)) अणु
		/* Note that most of them will have gone directly to be erased.
		   So करोn't favour the erasable_list _too_ much. */
		jffs2_dbg(1, "Picking block from erasable_list to GC next\n");
		nextlist = &c->erasable_list;
	पूर्ण अन्यथा अगर (n < 110 && !list_empty(&c->very_dirty_list)) अणु
		/* Most of the समय, pick one off the very_dirty list */
		jffs2_dbg(1, "Picking block from very_dirty_list to GC next\n");
		nextlist = &c->very_dirty_list;
	पूर्ण अन्यथा अगर (n < 126 && !list_empty(&c->dirty_list)) अणु
		jffs2_dbg(1, "Picking block from dirty_list to GC next\n");
		nextlist = &c->dirty_list;
	पूर्ण अन्यथा अगर (!list_empty(&c->clean_list)) अणु
		jffs2_dbg(1, "Picking block from clean_list to GC next\n");
		nextlist = &c->clean_list;
	पूर्ण अन्यथा अगर (!list_empty(&c->dirty_list)) अणु
		jffs2_dbg(1, "Picking block from dirty_list to GC next (clean_list was empty)\n");

		nextlist = &c->dirty_list;
	पूर्ण अन्यथा अगर (!list_empty(&c->very_dirty_list)) अणु
		jffs2_dbg(1, "Picking block from very_dirty_list to GC next (clean_list and dirty_list were empty)\n");
		nextlist = &c->very_dirty_list;
	पूर्ण अन्यथा अगर (!list_empty(&c->erasable_list)) अणु
		jffs2_dbg(1, "Picking block from erasable_list to GC next (clean_list and {very_,}dirty_list were empty)\n");

		nextlist = &c->erasable_list;
	पूर्ण अन्यथा अगर (!list_empty(&c->erasable_pending_wbuf_list)) अणु
		/* There are blocks are wating क्रम the wbuf sync */
		jffs2_dbg(1, "Synching wbuf in order to reuse erasable_pending_wbuf_list blocks\n");
		spin_unlock(&c->erase_completion_lock);
		jffs2_flush_wbuf_pad(c);
		spin_lock(&c->erase_completion_lock);
		जाओ again;
	पूर्ण अन्यथा अणु
		/* Eep. All were empty */
		jffs2_dbg(1, "No clean, dirty _or_ erasable blocks to GC from! Where are they all?\n");
		वापस शून्य;
	पूर्ण

	ret = list_entry(nextlist->next, काष्ठा jffs2_eraseblock, list);
	list_del(&ret->list);
	c->gcblock = ret;
	ret->gc_node = ret->first_node;
	अगर (!ret->gc_node) अणु
		pr_warn("Eep. ret->gc_node for block at 0x%08x is NULL\n",
			ret->offset);
		BUG();
	पूर्ण

	/* Have we accidentally picked a clean block with wasted space ? */
	अगर (ret->wasted_size) अणु
		jffs2_dbg(1, "Converting wasted_size %08x to dirty_size\n",
			  ret->wasted_size);
		ret->dirty_size += ret->wasted_size;
		c->wasted_size -= ret->wasted_size;
		c->dirty_size += ret->wasted_size;
		ret->wasted_size = 0;
	पूर्ण

	वापस ret;
पूर्ण

/* jffs2_garbage_collect_pass
 * Make a single attempt to progress GC. Move one node, and possibly
 * start erasing one eraseblock.
 */
पूर्णांक jffs2_garbage_collect_pass(काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा jffs2_inode_info *f;
	काष्ठा jffs2_inode_cache *ic;
	काष्ठा jffs2_eraseblock *jeb;
	काष्ठा jffs2_raw_node_ref *raw;
	uपूर्णांक32_t gcblock_dirty;
	पूर्णांक ret = 0, inum, nlink;
	पूर्णांक xattr = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&c->alloc_sem))
		वापस -EINTR;


	क्रम (;;) अणु
		/* We can't start doing GC until we've finished checking
		   the node CRCs etc. */
		पूर्णांक bucket, want_ino;

		spin_lock(&c->erase_completion_lock);
		अगर (!c->unchecked_size)
			अवरोध;
		spin_unlock(&c->erase_completion_lock);

		अगर (!xattr)
			xattr = jffs2_verअगरy_xattr(c);

		spin_lock(&c->inocache_lock);
		/* Instead of करोing the inodes in numeric order, करोing a lookup
		 * in the hash क्रम each possible number, just walk the hash
		 * buckets of *existing* inodes. This means that we process
		 * them out-of-order, but it can be a lot faster अगर there's
		 * a sparse inode# space. Which there often is. */
		want_ino = c->check_ino;
		क्रम (bucket = c->check_ino % c->inocache_hashsize ; bucket < c->inocache_hashsize; bucket++) अणु
			क्रम (ic = c->inocache_list[bucket]; ic; ic = ic->next) अणु
				अगर (ic->ino < want_ino)
					जारी;

				अगर (ic->state != INO_STATE_CHECKEDABSENT &&
				    ic->state != INO_STATE_PRESENT)
					जाओ got_next; /* with inocache_lock held */

				jffs2_dbg(1, "Skipping ino #%u already checked\n",
					  ic->ino);
			पूर्ण
			want_ino = 0;
		पूर्ण

		/* Poपूर्णांक c->check_ino past the end of the last bucket. */
		c->check_ino = ((c->highest_ino + c->inocache_hashsize + 1) &
				~c->inocache_hashsize) - 1;

		spin_unlock(&c->inocache_lock);

		pr_crit("Checked all inodes but still 0x%x bytes of unchecked space?\n",
			c->unchecked_size);
		jffs2_dbg_dump_block_lists_nolock(c);
		mutex_unlock(&c->alloc_sem);
		वापस -ENOSPC;

	got_next:
		/* For next समय round the loop, we want c->checked_ino to indicate
		 * the *next* one we want to check. And since we're walking the
		 * buckets rather than करोing it sequentially, it's: */
		c->check_ino = ic->ino + c->inocache_hashsize;

		अगर (!ic->pino_nlink) अणु
			jffs2_dbg(1, "Skipping check of ino #%d with nlink/pino zero\n",
				  ic->ino);
			spin_unlock(&c->inocache_lock);
			jffs2_xattr_delete_inode(c, ic);
			जारी;
		पूर्ण
		चयन(ic->state) अणु
		हाल INO_STATE_CHECKEDABSENT:
		हाल INO_STATE_PRESENT:
			spin_unlock(&c->inocache_lock);
			जारी;

		हाल INO_STATE_GC:
		हाल INO_STATE_CHECKING:
			pr_warn("Inode #%u is in state %d during CRC check phase!\n",
				ic->ino, ic->state);
			spin_unlock(&c->inocache_lock);
			BUG();

		हाल INO_STATE_READING:
			/* We need to रुको क्रम it to finish, lest we move on
			   and trigger the BUG() above जबतक we haven't yet
			   finished checking all its nodes */
			jffs2_dbg(1, "Waiting for ino #%u to finish reading\n",
				  ic->ino);
			/* We need to come back again क्रम the _same_ inode. We've
			 made no progress in this हाल, but that should be OK */
			c->check_ino = ic->ino;

			mutex_unlock(&c->alloc_sem);
			sleep_on_spinunlock(&c->inocache_wq, &c->inocache_lock);
			वापस 0;

		शेष:
			BUG();

		हाल INO_STATE_UNCHECKED:
			;
		पूर्ण
		ic->state = INO_STATE_CHECKING;
		spin_unlock(&c->inocache_lock);

		jffs2_dbg(1, "%s(): triggering inode scan of ino#%u\n",
			  __func__, ic->ino);

		ret = jffs2_करो_crccheck_inode(c, ic);
		अगर (ret)
			pr_warn("Returned error for crccheck of ino #%u. Expect badness...\n",
				ic->ino);

		jffs2_set_inocache_state(c, ic, INO_STATE_CHECKEDABSENT);
		mutex_unlock(&c->alloc_sem);
		वापस ret;
	पूर्ण

	/* If there are any blocks which need erasing, erase them now */
	अगर (!list_empty(&c->erase_complete_list) ||
	    !list_empty(&c->erase_pending_list)) अणु
		spin_unlock(&c->erase_completion_lock);
		mutex_unlock(&c->alloc_sem);
		jffs2_dbg(1, "%s(): erasing pending blocks\n", __func__);
		अगर (jffs2_erase_pending_blocks(c, 1))
			वापस 0;

		jffs2_dbg(1, "No progress from erasing block; doing GC anyway\n");
		mutex_lock(&c->alloc_sem);
		spin_lock(&c->erase_completion_lock);
	पूर्ण

	/* First, work out which block we're garbage-collecting */
	jeb = c->gcblock;

	अगर (!jeb)
		jeb = jffs2_find_gc_block(c);

	अगर (!jeb) अणु
		/* Couldn't find a free block. But maybe we can just erase one and make 'progress'? */
		अगर (c->nr_erasing_blocks) अणु
			spin_unlock(&c->erase_completion_lock);
			mutex_unlock(&c->alloc_sem);
			वापस -EAGAIN;
		पूर्ण
		jffs2_dbg(1, "Couldn't find erase block to garbage collect!\n");
		spin_unlock(&c->erase_completion_lock);
		mutex_unlock(&c->alloc_sem);
		वापस -EIO;
	पूर्ण

	jffs2_dbg(1, "GC from block %08x, used_size %08x, dirty_size %08x, free_size %08x\n",
		  jeb->offset, jeb->used_size, jeb->dirty_size, jeb->मुक्त_size);
	D1(अगर (c->nextblock)
	   prपूर्णांकk(KERN_DEBUG "Nextblock at  %08x, used_size %08x, dirty_size %08x, wasted_size %08x, free_size %08x\n", c->nextblock->offset, c->nextblock->used_size, c->nextblock->dirty_size, c->nextblock->wasted_size, c->nextblock->मुक्त_size));

	अगर (!jeb->used_size) अणु
		mutex_unlock(&c->alloc_sem);
		जाओ eraseit;
	पूर्ण

	raw = jeb->gc_node;
	gcblock_dirty = jeb->dirty_size;

	जबतक(ref_obsolete(raw)) अणु
		jffs2_dbg(1, "Node at 0x%08x is obsolete... skipping\n",
			  ref_offset(raw));
		raw = ref_next(raw);
		अगर (unlikely(!raw)) अणु
			pr_warn("eep. End of raw list while still supposedly nodes to GC\n");
			pr_warn("erase block at 0x%08x. free_size 0x%08x, dirty_size 0x%08x, used_size 0x%08x\n",
				jeb->offset, jeb->मुक्त_size,
				jeb->dirty_size, jeb->used_size);
			jeb->gc_node = raw;
			spin_unlock(&c->erase_completion_lock);
			mutex_unlock(&c->alloc_sem);
			BUG();
		पूर्ण
	पूर्ण
	jeb->gc_node = raw;

	jffs2_dbg(1, "Going to garbage collect node at 0x%08x\n",
		  ref_offset(raw));

	अगर (!raw->next_in_ino) अणु
		/* Inode-less node. Clean marker, snapshot or something like that */
		spin_unlock(&c->erase_completion_lock);
		अगर (ref_flags(raw) == REF_PRISTINE) अणु
			/* It's an unknown node with JFFS2_FEATURE_RWCOMPAT_COPY */
			jffs2_garbage_collect_pristine(c, शून्य, raw);
		पूर्ण अन्यथा अणु
			/* Just mark it obsolete */
			jffs2_mark_node_obsolete(c, raw);
		पूर्ण
		mutex_unlock(&c->alloc_sem);
		जाओ eraseit_lock;
	पूर्ण

	ic = jffs2_raw_ref_to_ic(raw);

#अगर_घोषित CONFIG_JFFS2_FS_XATTR
	/* When 'ic' refers xattr_datum/xattr_ref, this node is GCed as xattr.
	 * We can decide whether this node is inode or xattr by ic->class.     */
	अगर (ic->class == RAWNODE_CLASS_XATTR_DATUM
	    || ic->class == RAWNODE_CLASS_XATTR_REF) अणु
		spin_unlock(&c->erase_completion_lock);

		अगर (ic->class == RAWNODE_CLASS_XATTR_DATUM) अणु
			ret = jffs2_garbage_collect_xattr_datum(c, (काष्ठा jffs2_xattr_datum *)ic, raw);
		पूर्ण अन्यथा अणु
			ret = jffs2_garbage_collect_xattr_ref(c, (काष्ठा jffs2_xattr_ref *)ic, raw);
		पूर्ण
		जाओ test_gcnode;
	पूर्ण
#पूर्ण_अगर

	/* We need to hold the inocache. Either the erase_completion_lock or
	   the inocache_lock are sufficient; we trade करोwn since the inocache_lock
	   causes less contention. */
	spin_lock(&c->inocache_lock);

	spin_unlock(&c->erase_completion_lock);

	jffs2_dbg(1, "%s(): collecting from block @0x%08x. Node @0x%08x(%d), ino #%u\n",
		  __func__, jeb->offset, ref_offset(raw), ref_flags(raw),
		  ic->ino);

	/* Three possibilities:
	   1. Inode is alपढ़ोy in-core. We must iget it and करो proper
	      updating to its fragtree, etc.
	   2. Inode is not in-core, node is REF_PRISTINE. We lock the
	      inocache to prevent a पढ़ो_inode(), copy the node पूर्णांकact.
	   3. Inode is not in-core, node is not pristine. We must iget()
	      and take the slow path.
	*/

	चयन(ic->state) अणु
	हाल INO_STATE_CHECKEDABSENT:
		/* It's been checked, but it's not currently in-core.
		   We can just copy any pristine nodes, but have
		   to prevent anyone अन्यथा from करोing पढ़ो_inode() जबतक
		   we're at it, so we set the state accordingly */
		अगर (ref_flags(raw) == REF_PRISTINE)
			ic->state = INO_STATE_GC;
		अन्यथा अणु
			jffs2_dbg(1, "Ino #%u is absent but node not REF_PRISTINE. Reading.\n",
				  ic->ino);
		पूर्ण
		अवरोध;

	हाल INO_STATE_PRESENT:
		/* It's in-core. GC must iget() it. */
		अवरोध;

	हाल INO_STATE_UNCHECKED:
	हाल INO_STATE_CHECKING:
	हाल INO_STATE_GC:
		/* Should never happen. We should have finished checking
		   by the समय we actually start करोing any GC, and since
		   we're holding the alloc_sem, no other garbage collection
		   can happen.
		*/
		pr_crit("Inode #%u already in state %d in jffs2_garbage_collect_pass()!\n",
			ic->ino, ic->state);
		mutex_unlock(&c->alloc_sem);
		spin_unlock(&c->inocache_lock);
		BUG();

	हाल INO_STATE_READING:
		/* Someone's currently trying to पढ़ो it. We must रुको क्रम
		   them to finish and then go through the full iget() route
		   to करो the GC. However, someबार पढ़ो_inode() needs to get
		   the alloc_sem() (क्रम marking nodes invalid) so we must
		   drop the alloc_sem beक्रमe sleeping. */

		mutex_unlock(&c->alloc_sem);
		jffs2_dbg(1, "%s(): waiting for ino #%u in state %d\n",
			  __func__, ic->ino, ic->state);
		sleep_on_spinunlock(&c->inocache_wq, &c->inocache_lock);
		/* And because we dropped the alloc_sem we must start again from the
		   beginning. Ponder chance of livelock here -- we're वापसing success
		   without actually making any progress.

		   Q: What are the chances that the inode is back in INO_STATE_READING
		   again by the समय we next enter this function? And that this happens
		   enough बार to cause a real delay?

		   A: Small enough that I करोn't care :)
		*/
		वापस 0;
	पूर्ण

	/* OK. Now अगर the inode is in state INO_STATE_GC, we are going to copy the
	   node पूर्णांकact, and we करोn't have to muck about with the fragtree etc.
	   because we know it's not in-core. If it _was_ in-core, we go through
	   all the iget() crap anyway */

	अगर (ic->state == INO_STATE_GC) अणु
		spin_unlock(&c->inocache_lock);

		ret = jffs2_garbage_collect_pristine(c, ic, raw);

		spin_lock(&c->inocache_lock);
		ic->state = INO_STATE_CHECKEDABSENT;
		wake_up(&c->inocache_wq);

		अगर (ret != -EBADFD) अणु
			spin_unlock(&c->inocache_lock);
			जाओ test_gcnode;
		पूर्ण

		/* Fall through अगर it wanted us to, with inocache_lock held */
	पूर्ण

	/* Prevent the fairly unlikely race where the gcblock is
	   entirely obsoleted by the final बंद of a file which had
	   the only valid nodes in the block, followed by erasure,
	   followed by मुक्तing of the ic because the erased block(s)
	   held _all_ the nodes of that inode.... never been seen but
	   it's vaguely possible. */

	inum = ic->ino;
	nlink = ic->pino_nlink;
	spin_unlock(&c->inocache_lock);

	f = jffs2_gc_fetch_inode(c, inum, !nlink);
	अगर (IS_ERR(f)) अणु
		ret = PTR_ERR(f);
		जाओ release_sem;
	पूर्ण
	अगर (!f) अणु
		ret = 0;
		जाओ release_sem;
	पूर्ण

	ret = jffs2_garbage_collect_live(c, jeb, raw, f);

	jffs2_gc_release_inode(c, f);

 test_gcnode:
	अगर (jeb->dirty_size == gcblock_dirty && !ref_obsolete(jeb->gc_node)) अणु
		/* Eep. This really should never happen. GC is broken */
		pr_err("Error garbage collecting node at %08x!\n",
		       ref_offset(jeb->gc_node));
		ret = -ENOSPC;
	पूर्ण
 release_sem:
	mutex_unlock(&c->alloc_sem);

 eraseit_lock:
	/* If we've finished this block, start it erasing */
	spin_lock(&c->erase_completion_lock);

 eraseit:
	अगर (c->gcblock && !c->gcblock->used_size) अणु
		jffs2_dbg(1, "Block at 0x%08x completely obsoleted by GC. Moving to erase_pending_list\n",
			  c->gcblock->offset);
		/* We're GC'ing an empty block? */
		list_add_tail(&c->gcblock->list, &c->erase_pending_list);
		c->gcblock = शून्य;
		c->nr_erasing_blocks++;
		jffs2_garbage_collect_trigger(c);
	पूर्ण
	spin_unlock(&c->erase_completion_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक jffs2_garbage_collect_live(काष्ठा jffs2_sb_info *c,  काष्ठा jffs2_eraseblock *jeb,
				      काष्ठा jffs2_raw_node_ref *raw, काष्ठा jffs2_inode_info *f)
अणु
	काष्ठा jffs2_node_frag *frag;
	काष्ठा jffs2_full_dnode *fn = शून्य;
	काष्ठा jffs2_full_dirent *fd;
	uपूर्णांक32_t start = 0, end = 0, nrfrags = 0;
	पूर्णांक ret = 0;

	mutex_lock(&f->sem);

	/* Now we have the lock क्रम this inode. Check that it's still the one at the head
	   of the list. */

	spin_lock(&c->erase_completion_lock);

	अगर (c->gcblock != jeb) अणु
		spin_unlock(&c->erase_completion_lock);
		jffs2_dbg(1, "GC block is no longer gcblock. Restart\n");
		जाओ upnout;
	पूर्ण
	अगर (ref_obsolete(raw)) अणु
		spin_unlock(&c->erase_completion_lock);
		jffs2_dbg(1, "node to be GC'd was obsoleted in the meantime.\n");
		/* They'll call again */
		जाओ upnout;
	पूर्ण
	spin_unlock(&c->erase_completion_lock);

	/* OK. Looks safe. And nobody can get us now because we have the semaphore. Move the block */
	अगर (f->metadata && f->metadata->raw == raw) अणु
		fn = f->metadata;
		ret = jffs2_garbage_collect_metadata(c, jeb, f, fn);
		जाओ upnout;
	पूर्ण

	/* FIXME. Read node and करो lookup? */
	क्रम (frag = frag_first(&f->fragtree); frag; frag = frag_next(frag)) अणु
		अगर (frag->node && frag->node->raw == raw) अणु
			fn = frag->node;
			end = frag->ofs + frag->size;
			अगर (!nrfrags++)
				start = frag->ofs;
			अगर (nrfrags == frag->node->frags)
				अवरोध; /* We've found them all */
		पूर्ण
	पूर्ण
	अगर (fn) अणु
		अगर (ref_flags(raw) == REF_PRISTINE) अणु
			ret = jffs2_garbage_collect_pristine(c, f->inocache, raw);
			अगर (!ret) अणु
				/* Urgh. Return it sensibly. */
				frag->node->raw = f->inocache->nodes;
			पूर्ण
			अगर (ret != -EBADFD)
				जाओ upnout;
		पूर्ण
		/* We found a datanode. Do the GC */
		अगर((start >> PAGE_SHIFT) < ((end-1) >> PAGE_SHIFT)) अणु
			/* It crosses a page boundary. Thereक्रमe, it must be a hole. */
			ret = jffs2_garbage_collect_hole(c, jeb, f, fn, start, end);
		पूर्ण अन्यथा अणु
			/* It could still be a hole. But we GC the page this way anyway */
			ret = jffs2_garbage_collect_dnode(c, jeb, f, fn, start, end);
		पूर्ण
		जाओ upnout;
	पूर्ण

	/* Wasn't a dnode. Try dirent */
	क्रम (fd = f->dents; fd; fd=fd->next) अणु
		अगर (fd->raw == raw)
			अवरोध;
	पूर्ण

	अगर (fd && fd->ino) अणु
		ret = jffs2_garbage_collect_dirent(c, jeb, f, fd);
	पूर्ण अन्यथा अगर (fd) अणु
		ret = jffs2_garbage_collect_deletion_dirent(c, jeb, f, fd);
	पूर्ण अन्यथा अणु
		pr_warn("Raw node at 0x%08x wasn't in node lists for ino #%u\n",
			ref_offset(raw), f->inocache->ino);
		अगर (ref_obsolete(raw)) अणु
			pr_warn("But it's obsolete so we don't mind too much\n");
		पूर्ण अन्यथा अणु
			jffs2_dbg_dump_node(c, ref_offset(raw));
			BUG();
		पूर्ण
	पूर्ण
 upnout:
	mutex_unlock(&f->sem);

	वापस ret;
पूर्ण

अटल पूर्णांक jffs2_garbage_collect_pristine(काष्ठा jffs2_sb_info *c,
					  काष्ठा jffs2_inode_cache *ic,
					  काष्ठा jffs2_raw_node_ref *raw)
अणु
	जोड़ jffs2_node_जोड़ *node;
	माप_प्रकार retlen;
	पूर्णांक ret;
	uपूर्णांक32_t phys_ofs, alloclen;
	uपूर्णांक32_t crc, rawlen;
	पूर्णांक retried = 0;

	jffs2_dbg(1, "Going to GC REF_PRISTINE node at 0x%08x\n",
		  ref_offset(raw));

	alloclen = rawlen = ref_totlen(c, c->gcblock, raw);

	/* Ask क्रम a small amount of space (or the totlen अगर smaller) because we
	   करोn't want to क्रमce wastage of the end of a block अगर splitting would
	   work. */
	अगर (ic && alloclen > माप(काष्ठा jffs2_raw_inode) + JFFS2_MIN_DATA_LEN)
		alloclen = माप(काष्ठा jffs2_raw_inode) + JFFS2_MIN_DATA_LEN;

	ret = jffs2_reserve_space_gc(c, alloclen, &alloclen, rawlen);
	/* 'rawlen' is not the exact summary size; it is only an upper estimation */

	अगर (ret)
		वापस ret;

	अगर (alloclen < rawlen) अणु
		/* Doesn't fit untouched. We'll go the old route and split it */
		वापस -EBADFD;
	पूर्ण

	node = kदो_स्मृति(rawlen, GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;

	ret = jffs2_flash_पढ़ो(c, ref_offset(raw), rawlen, &retlen, (अक्षर *)node);
	अगर (!ret && retlen != rawlen)
		ret = -EIO;
	अगर (ret)
		जाओ out_node;

	crc = crc32(0, node, माप(काष्ठा jffs2_unknown_node)-4);
	अगर (je32_to_cpu(node->u.hdr_crc) != crc) अणु
		pr_warn("Header CRC failed on REF_PRISTINE node at 0x%08x: Read 0x%08x, calculated 0x%08x\n",
			ref_offset(raw), je32_to_cpu(node->u.hdr_crc), crc);
		जाओ bail;
	पूर्ण

	चयन(je16_to_cpu(node->u.nodetype)) अणु
	हाल JFFS2_NODETYPE_INODE:
		crc = crc32(0, node, माप(node->i)-8);
		अगर (je32_to_cpu(node->i.node_crc) != crc) अणु
			pr_warn("Node CRC failed on REF_PRISTINE data node at 0x%08x: Read 0x%08x, calculated 0x%08x\n",
				ref_offset(raw), je32_to_cpu(node->i.node_crc),
				crc);
			जाओ bail;
		पूर्ण

		अगर (je32_to_cpu(node->i.dsize)) अणु
			crc = crc32(0, node->i.data, je32_to_cpu(node->i.csize));
			अगर (je32_to_cpu(node->i.data_crc) != crc) अणु
				pr_warn("Data CRC failed on REF_PRISTINE data node at 0x%08x: Read 0x%08x, calculated 0x%08x\n",
					ref_offset(raw),
					je32_to_cpu(node->i.data_crc), crc);
				जाओ bail;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल JFFS2_NODETYPE_सूचीENT:
		crc = crc32(0, node, माप(node->d)-8);
		अगर (je32_to_cpu(node->d.node_crc) != crc) अणु
			pr_warn("Node CRC failed on REF_PRISTINE dirent node at 0x%08x: Read 0x%08x, calculated 0x%08x\n",
				ref_offset(raw),
				je32_to_cpu(node->d.node_crc), crc);
			जाओ bail;
		पूर्ण

		अगर (strnlen(node->d.name, node->d.nsize) != node->d.nsize) अणु
			pr_warn("Name in dirent node at 0x%08x contains zeroes\n",
				ref_offset(raw));
			जाओ bail;
		पूर्ण

		अगर (node->d.nsize) अणु
			crc = crc32(0, node->d.name, node->d.nsize);
			अगर (je32_to_cpu(node->d.name_crc) != crc) अणु
				pr_warn("Name CRC failed on REF_PRISTINE dirent node at 0x%08x: Read 0x%08x, calculated 0x%08x\n",
					ref_offset(raw),
					je32_to_cpu(node->d.name_crc), crc);
				जाओ bail;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		/* If it's inode-less, we don't _know_ what it is. Just copy it पूर्णांकact */
		अगर (ic) अणु
			pr_warn("Unknown node type for REF_PRISTINE node at 0x%08x: 0x%04x\n",
				ref_offset(raw), je16_to_cpu(node->u.nodetype));
			जाओ bail;
		पूर्ण
	पूर्ण

	/* OK, all the CRCs are good; this node can just be copied as-is. */
 retry:
	phys_ofs = ग_लिखो_ofs(c);

	ret = jffs2_flash_ग_लिखो(c, phys_ofs, rawlen, &retlen, (अक्षर *)node);

	अगर (ret || (retlen != rawlen)) अणु
		pr_notice("Write of %d bytes at 0x%08x failed. returned %d, retlen %zd\n",
			  rawlen, phys_ofs, ret, retlen);
		अगर (retlen) अणु
			jffs2_add_physical_node_ref(c, phys_ofs | REF_OBSOLETE, rawlen, शून्य);
		पूर्ण अन्यथा अणु
			pr_notice("Not marking the space at 0x%08x as dirty because the flash driver returned retlen zero\n",
				  phys_ofs);
		पूर्ण
		अगर (!retried) अणु
			/* Try to पुनः_स्मृतिate space and retry */
			uपूर्णांक32_t dummy;
			काष्ठा jffs2_eraseblock *jeb = &c->blocks[phys_ofs / c->sector_size];

			retried = 1;

			jffs2_dbg(1, "Retrying failed write of REF_PRISTINE node.\n");

			jffs2_dbg_acct_sanity_check(c,jeb);
			jffs2_dbg_acct_paranoia_check(c, jeb);

			ret = jffs2_reserve_space_gc(c, rawlen, &dummy, rawlen);
						/* this is not the exact summary size of it,
							it is only an upper estimation */

			अगर (!ret) अणु
				jffs2_dbg(1, "Allocated space at 0x%08x to retry failed write.\n",
					  phys_ofs);

				jffs2_dbg_acct_sanity_check(c,jeb);
				jffs2_dbg_acct_paranoia_check(c, jeb);

				जाओ retry;
			पूर्ण
			jffs2_dbg(1, "Failed to allocate space to retry failed write: %d!\n",
				  ret);
		पूर्ण

		अगर (!ret)
			ret = -EIO;
		जाओ out_node;
	पूर्ण
	jffs2_add_physical_node_ref(c, phys_ofs | REF_PRISTINE, rawlen, ic);

	jffs2_mark_node_obsolete(c, raw);
	jffs2_dbg(1, "WHEEE! GC REF_PRISTINE node at 0x%08x succeeded\n",
		  ref_offset(raw));

 out_node:
	kमुक्त(node);
	वापस ret;
 bail:
	ret = -EBADFD;
	जाओ out_node;
पूर्ण

अटल पूर्णांक jffs2_garbage_collect_metadata(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
					काष्ठा jffs2_inode_info *f, काष्ठा jffs2_full_dnode *fn)
अणु
	काष्ठा jffs2_full_dnode *new_fn;
	काष्ठा jffs2_raw_inode ri;
	काष्ठा jffs2_node_frag *last_frag;
	जोड़ jffs2_device_node dev;
	अक्षर *mdata = शून्य;
	पूर्णांक mdatalen = 0;
	uपूर्णांक32_t alloclen, ilen;
	पूर्णांक ret;

	अगर (S_ISBLK(JFFS2_F_I_MODE(f)) ||
	    S_ISCHR(JFFS2_F_I_MODE(f)) ) अणु
		/* For these, we करोn't actually need to पढ़ो the old node */
		mdatalen = jffs2_encode_dev(&dev, JFFS2_F_I_RDEV(f));
		mdata = (अक्षर *)&dev;
		jffs2_dbg(1, "%s(): Writing %d bytes of kdev_t\n",
			  __func__, mdatalen);
	पूर्ण अन्यथा अगर (S_ISLNK(JFFS2_F_I_MODE(f))) अणु
		mdatalen = fn->size;
		mdata = kदो_स्मृति(fn->size, GFP_KERNEL);
		अगर (!mdata) अणु
			pr_warn("kmalloc of mdata failed in jffs2_garbage_collect_metadata()\n");
			वापस -ENOMEM;
		पूर्ण
		ret = jffs2_पढ़ो_dnode(c, f, fn, mdata, 0, mdatalen);
		अगर (ret) अणु
			pr_warn("read of old metadata failed in jffs2_garbage_collect_metadata(): %d\n",
				ret);
			kमुक्त(mdata);
			वापस ret;
		पूर्ण
		jffs2_dbg(1, "%s(): Writing %d bites of symlink target\n",
			  __func__, mdatalen);

	पूर्ण

	ret = jffs2_reserve_space_gc(c, माप(ri) + mdatalen, &alloclen,
				JFFS2_SUMMARY_INODE_SIZE);
	अगर (ret) अणु
		pr_warn("jffs2_reserve_space_gc of %zd bytes for garbage_collect_metadata failed: %d\n",
			माप(ri) + mdatalen, ret);
		जाओ out;
	पूर्ण

	last_frag = frag_last(&f->fragtree);
	अगर (last_frag)
		/* Fetch the inode length from the fragtree rather then
		 * from i_size since i_size may have not been updated yet */
		ilen = last_frag->ofs + last_frag->size;
	अन्यथा
		ilen = JFFS2_F_I_SIZE(f);

	स_रखो(&ri, 0, माप(ri));
	ri.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	ri.nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
	ri.totlen = cpu_to_je32(माप(ri) + mdatalen);
	ri.hdr_crc = cpu_to_je32(crc32(0, &ri, माप(काष्ठा jffs2_unknown_node)-4));

	ri.ino = cpu_to_je32(f->inocache->ino);
	ri.version = cpu_to_je32(++f->highest_version);
	ri.mode = cpu_to_jemode(JFFS2_F_I_MODE(f));
	ri.uid = cpu_to_je16(JFFS2_F_I_UID(f));
	ri.gid = cpu_to_je16(JFFS2_F_I_GID(f));
	ri.isize = cpu_to_je32(ilen);
	ri.aसमय = cpu_to_je32(JFFS2_F_I_ATIME(f));
	ri.स_समय = cpu_to_je32(JFFS2_F_I_CTIME(f));
	ri.mसमय = cpu_to_je32(JFFS2_F_I_MTIME(f));
	ri.offset = cpu_to_je32(0);
	ri.csize = cpu_to_je32(mdatalen);
	ri.dsize = cpu_to_je32(mdatalen);
	ri.compr = JFFS2_COMPR_NONE;
	ri.node_crc = cpu_to_je32(crc32(0, &ri, माप(ri)-8));
	ri.data_crc = cpu_to_je32(crc32(0, mdata, mdatalen));

	new_fn = jffs2_ग_लिखो_dnode(c, f, &ri, mdata, mdatalen, ALLOC_GC);

	अगर (IS_ERR(new_fn)) अणु
		pr_warn("Error writing new dnode: %ld\n", PTR_ERR(new_fn));
		ret = PTR_ERR(new_fn);
		जाओ out;
	पूर्ण
	jffs2_mark_node_obsolete(c, fn->raw);
	jffs2_मुक्त_full_dnode(fn);
	f->metadata = new_fn;
 out:
	अगर (S_ISLNK(JFFS2_F_I_MODE(f)))
		kमुक्त(mdata);
	वापस ret;
पूर्ण

अटल पूर्णांक jffs2_garbage_collect_dirent(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
					काष्ठा jffs2_inode_info *f, काष्ठा jffs2_full_dirent *fd)
अणु
	काष्ठा jffs2_full_dirent *new_fd;
	काष्ठा jffs2_raw_dirent rd;
	uपूर्णांक32_t alloclen;
	पूर्णांक ret;

	rd.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	rd.nodetype = cpu_to_je16(JFFS2_NODETYPE_सूचीENT);
	rd.nsize = म_माप(fd->name);
	rd.totlen = cpu_to_je32(माप(rd) + rd.nsize);
	rd.hdr_crc = cpu_to_je32(crc32(0, &rd, माप(काष्ठा jffs2_unknown_node)-4));

	rd.pino = cpu_to_je32(f->inocache->ino);
	rd.version = cpu_to_je32(++f->highest_version);
	rd.ino = cpu_to_je32(fd->ino);
	/* If the बार on this inode were set by explicit uसमय() they can be dअगरferent,
	   so refrain from splatting them. */
	अगर (JFFS2_F_I_MTIME(f) == JFFS2_F_I_CTIME(f))
		rd.mस_समय = cpu_to_je32(JFFS2_F_I_MTIME(f));
	अन्यथा
		rd.mस_समय = cpu_to_je32(0);
	rd.type = fd->type;
	rd.node_crc = cpu_to_je32(crc32(0, &rd, माप(rd)-8));
	rd.name_crc = cpu_to_je32(crc32(0, fd->name, rd.nsize));

	ret = jffs2_reserve_space_gc(c, माप(rd)+rd.nsize, &alloclen,
				JFFS2_SUMMARY_सूचीENT_SIZE(rd.nsize));
	अगर (ret) अणु
		pr_warn("jffs2_reserve_space_gc of %zd bytes for garbage_collect_dirent failed: %d\n",
			माप(rd)+rd.nsize, ret);
		वापस ret;
	पूर्ण
	new_fd = jffs2_ग_लिखो_dirent(c, f, &rd, fd->name, rd.nsize, ALLOC_GC);

	अगर (IS_ERR(new_fd)) अणु
		pr_warn("jffs2_write_dirent in garbage_collect_dirent failed: %ld\n",
			PTR_ERR(new_fd));
		वापस PTR_ERR(new_fd);
	पूर्ण
	jffs2_add_fd_to_list(c, new_fd, &f->dents);
	वापस 0;
पूर्ण

अटल पूर्णांक jffs2_garbage_collect_deletion_dirent(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
					काष्ठा jffs2_inode_info *f, काष्ठा jffs2_full_dirent *fd)
अणु
	काष्ठा jffs2_full_dirent **fdp = &f->dents;
	पूर्णांक found = 0;

	/* On a medium where we can't actually mark nodes obsolete
	   pernamently, such as न_अंकD flash, we need to work out
	   whether this deletion dirent is still needed to actively
	   delete a 'real' dirent with the same name that's still
	   somewhere अन्यथा on the flash. */
	अगर (!jffs2_can_mark_obsolete(c)) अणु
		काष्ठा jffs2_raw_dirent *rd;
		काष्ठा jffs2_raw_node_ref *raw;
		पूर्णांक ret;
		माप_प्रकार retlen;
		पूर्णांक name_len = म_माप(fd->name);
		uपूर्णांक32_t name_crc = crc32(0, fd->name, name_len);
		uपूर्णांक32_t rawlen = ref_totlen(c, jeb, fd->raw);

		rd = kदो_स्मृति(rawlen, GFP_KERNEL);
		अगर (!rd)
			वापस -ENOMEM;

		/* Prevent the erase code from nicking the obsolete node refs जबतक
		   we're looking at them. I really don't like this extra lock but
		   can't see any alternative. Suggestions on a postcard to... */
		mutex_lock(&c->erase_मुक्त_sem);

		क्रम (raw = f->inocache->nodes; raw != (व्योम *)f->inocache; raw = raw->next_in_ino) अणु

			cond_resched();

			/* We only care about obsolete ones */
			अगर (!(ref_obsolete(raw)))
				जारी;

			/* Any dirent with the same name is going to have the same length... */
			अगर (ref_totlen(c, शून्य, raw) != rawlen)
				जारी;

			/* Doesn't matter if there's one in the same erase block. We're going to
			   delete it too at the same समय. */
			अगर (SECTOR_ADDR(raw->flash_offset) == SECTOR_ADDR(fd->raw->flash_offset))
				जारी;

			jffs2_dbg(1, "Check potential deletion dirent at %08x\n",
				  ref_offset(raw));

			/* This is an obsolete node beदीर्घing to the same directory, and it's of the right
			   length. We need to take a बंदr look...*/
			ret = jffs2_flash_पढ़ो(c, ref_offset(raw), rawlen, &retlen, (अक्षर *)rd);
			अगर (ret) अणु
				pr_warn("%s(): Read error (%d) reading obsolete node at %08x\n",
					__func__, ret, ref_offset(raw));
				/* If we can't read it, we don't need to जारी to obsolete it. Continue */
				जारी;
			पूर्ण
			अगर (retlen != rawlen) अणु
				pr_warn("%s(): Short read (%zd not %u) reading header from obsolete node at %08x\n",
					__func__, retlen, rawlen,
					ref_offset(raw));
				जारी;
			पूर्ण

			अगर (je16_to_cpu(rd->nodetype) != JFFS2_NODETYPE_सूचीENT)
				जारी;

			/* If the name CRC करोesn't match, skip */
			अगर (je32_to_cpu(rd->name_crc) != name_crc)
				जारी;

			/* If the name length करोesn't match, or it's another deletion dirent, skip */
			अगर (rd->nsize != name_len || !je32_to_cpu(rd->ino))
				जारी;

			/* OK, check the actual name now */
			अगर (स_भेद(rd->name, fd->name, name_len))
				जारी;

			/* OK. The name really करोes match. There really is still an older node on
			   the flash which our deletion dirent obsoletes. So we have to ग_लिखो out
			   a new deletion dirent to replace it */
			mutex_unlock(&c->erase_मुक्त_sem);

			jffs2_dbg(1, "Deletion dirent at %08x still obsoletes real dirent \"%s\" at %08x for ino #%u\n",
				  ref_offset(fd->raw), fd->name,
				  ref_offset(raw), je32_to_cpu(rd->ino));
			kमुक्त(rd);

			वापस jffs2_garbage_collect_dirent(c, jeb, f, fd);
		पूर्ण

		mutex_unlock(&c->erase_मुक्त_sem);
		kमुक्त(rd);
	पूर्ण

	/* FIXME: If we're deleting a dirent which contains the current mसमय and स_समय,
	   we should update the metadata node with those बार accordingly */

	/* No need क्रम it any more. Just mark it obsolete and हटाओ it from the list */
	जबतक (*fdp) अणु
		अगर ((*fdp) == fd) अणु
			found = 1;
			*fdp = fd->next;
			अवरोध;
		पूर्ण
		fdp = &(*fdp)->next;
	पूर्ण
	अगर (!found) अणु
		pr_warn("Deletion dirent \"%s\" not found in list for ino #%u\n",
			fd->name, f->inocache->ino);
	पूर्ण
	jffs2_mark_node_obsolete(c, fd->raw);
	jffs2_मुक्त_full_dirent(fd);
	वापस 0;
पूर्ण

अटल पूर्णांक jffs2_garbage_collect_hole(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				      काष्ठा jffs2_inode_info *f, काष्ठा jffs2_full_dnode *fn,
				      uपूर्णांक32_t start, uपूर्णांक32_t end)
अणु
	काष्ठा jffs2_raw_inode ri;
	काष्ठा jffs2_node_frag *frag;
	काष्ठा jffs2_full_dnode *new_fn;
	uपूर्णांक32_t alloclen, ilen;
	पूर्णांक ret;

	jffs2_dbg(1, "Writing replacement hole node for ino #%u from offset 0x%x to 0x%x\n",
		  f->inocache->ino, start, end);

	स_रखो(&ri, 0, माप(ri));

	अगर(fn->frags > 1) अणु
		माप_प्रकार पढ़ोlen;
		uपूर्णांक32_t crc;
		/* It's partially obsoleted by a later ग_लिखो. So we have to
		   ग_लिखो it out again with the _same_ version as beक्रमe */
		ret = jffs2_flash_पढ़ो(c, ref_offset(fn->raw), माप(ri), &पढ़ोlen, (अक्षर *)&ri);
		अगर (पढ़ोlen != माप(ri) || ret) अणु
			pr_warn("Node read failed in jffs2_garbage_collect_hole. Ret %d, retlen %zd. Data will be lost by writing new hole node\n",
				ret, पढ़ोlen);
			जाओ fill;
		पूर्ण
		अगर (je16_to_cpu(ri.nodetype) != JFFS2_NODETYPE_INODE) अणु
			pr_warn("%s(): Node at 0x%08x had node type 0x%04x instead of JFFS2_NODETYPE_INODE(0x%04x)\n",
				__func__, ref_offset(fn->raw),
				je16_to_cpu(ri.nodetype), JFFS2_NODETYPE_INODE);
			वापस -EIO;
		पूर्ण
		अगर (je32_to_cpu(ri.totlen) != माप(ri)) अणु
			pr_warn("%s(): Node at 0x%08x had totlen 0x%x instead of expected 0x%zx\n",
				__func__, ref_offset(fn->raw),
				je32_to_cpu(ri.totlen), माप(ri));
			वापस -EIO;
		पूर्ण
		crc = crc32(0, &ri, माप(ri)-8);
		अगर (crc != je32_to_cpu(ri.node_crc)) अणु
			pr_warn("%s: Node at 0x%08x had CRC 0x%08x which doesn't match calculated CRC 0x%08x\n",
				__func__, ref_offset(fn->raw),
				je32_to_cpu(ri.node_crc), crc);
			/* FIXME: We could possibly deal with this by writing new holes क्रम each frag */
			pr_warn("Data in the range 0x%08x to 0x%08x of inode #%u will be lost\n",
				start, end, f->inocache->ino);
			जाओ fill;
		पूर्ण
		अगर (ri.compr != JFFS2_COMPR_ZERO) अणु
			pr_warn("%s(): Node 0x%08x wasn't a hole node!\n",
				__func__, ref_offset(fn->raw));
			pr_warn("Data in the range 0x%08x to 0x%08x of inode #%u will be lost\n",
				start, end, f->inocache->ino);
			जाओ fill;
		पूर्ण
	पूर्ण अन्यथा अणु
	fill:
		ri.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
		ri.nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
		ri.totlen = cpu_to_je32(माप(ri));
		ri.hdr_crc = cpu_to_je32(crc32(0, &ri, माप(काष्ठा jffs2_unknown_node)-4));

		ri.ino = cpu_to_je32(f->inocache->ino);
		ri.version = cpu_to_je32(++f->highest_version);
		ri.offset = cpu_to_je32(start);
		ri.dsize = cpu_to_je32(end - start);
		ri.csize = cpu_to_je32(0);
		ri.compr = JFFS2_COMPR_ZERO;
	पूर्ण

	frag = frag_last(&f->fragtree);
	अगर (frag)
		/* Fetch the inode length from the fragtree rather then
		 * from i_size since i_size may have not been updated yet */
		ilen = frag->ofs + frag->size;
	अन्यथा
		ilen = JFFS2_F_I_SIZE(f);

	ri.mode = cpu_to_jemode(JFFS2_F_I_MODE(f));
	ri.uid = cpu_to_je16(JFFS2_F_I_UID(f));
	ri.gid = cpu_to_je16(JFFS2_F_I_GID(f));
	ri.isize = cpu_to_je32(ilen);
	ri.aसमय = cpu_to_je32(JFFS2_F_I_ATIME(f));
	ri.स_समय = cpu_to_je32(JFFS2_F_I_CTIME(f));
	ri.mसमय = cpu_to_je32(JFFS2_F_I_MTIME(f));
	ri.data_crc = cpu_to_je32(0);
	ri.node_crc = cpu_to_je32(crc32(0, &ri, माप(ri)-8));

	ret = jffs2_reserve_space_gc(c, माप(ri), &alloclen,
				     JFFS2_SUMMARY_INODE_SIZE);
	अगर (ret) अणु
		pr_warn("jffs2_reserve_space_gc of %zd bytes for garbage_collect_hole failed: %d\n",
			माप(ri), ret);
		वापस ret;
	पूर्ण
	new_fn = jffs2_ग_लिखो_dnode(c, f, &ri, शून्य, 0, ALLOC_GC);

	अगर (IS_ERR(new_fn)) अणु
		pr_warn("Error writing new hole node: %ld\n", PTR_ERR(new_fn));
		वापस PTR_ERR(new_fn);
	पूर्ण
	अगर (je32_to_cpu(ri.version) == f->highest_version) अणु
		jffs2_add_full_dnode_to_inode(c, f, new_fn);
		अगर (f->metadata) अणु
			jffs2_mark_node_obsolete(c, f->metadata->raw);
			jffs2_मुक्त_full_dnode(f->metadata);
			f->metadata = शून्य;
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * We should only get here in the हाल where the node we are
	 * replacing had more than one frag, so we kept the same version
	 * number as beक्रमe. (Except in हाल of error -- see 'goto fill;'
	 * above.)
	 */
	D1(अगर(unlikely(fn->frags <= 1)) अणु
			pr_warn("%s(): Replacing fn with %d frag(s) but new ver %d != highest_version %d of ino #%d\n",
				__func__, fn->frags, je32_to_cpu(ri.version),
				f->highest_version, je32_to_cpu(ri.ino));
	पूर्ण);

	/* This is a partially-overlapped hole node. Mark it REF_NORMAL not REF_PRISTINE */
	mark_ref_normal(new_fn->raw);

	क्रम (frag = jffs2_lookup_node_frag(&f->fragtree, fn->ofs);
	     frag; frag = frag_next(frag)) अणु
		अगर (frag->ofs > fn->size + fn->ofs)
			अवरोध;
		अगर (frag->node == fn) अणु
			frag->node = new_fn;
			new_fn->frags++;
			fn->frags--;
		पूर्ण
	पूर्ण
	अगर (fn->frags) अणु
		pr_warn("%s(): Old node still has frags!\n", __func__);
		BUG();
	पूर्ण
	अगर (!new_fn->frags) अणु
		pr_warn("%s(): New node has no frags!\n", __func__);
		BUG();
	पूर्ण

	jffs2_mark_node_obsolete(c, fn->raw);
	jffs2_मुक्त_full_dnode(fn);

	वापस 0;
पूर्ण

अटल पूर्णांक jffs2_garbage_collect_dnode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *orig_jeb,
				       काष्ठा jffs2_inode_info *f, काष्ठा jffs2_full_dnode *fn,
				       uपूर्णांक32_t start, uपूर्णांक32_t end)
अणु
	काष्ठा inode *inode = OFNI_EDONI_2SFFJ(f);
	काष्ठा jffs2_full_dnode *new_fn;
	काष्ठा jffs2_raw_inode ri;
	uपूर्णांक32_t alloclen, offset, orig_end, orig_start;
	पूर्णांक ret = 0;
	अचिन्हित अक्षर *comprbuf = शून्य, *ग_लिखोbuf;
	काष्ठा page *page;
	अचिन्हित अक्षर *pg_ptr;

	स_रखो(&ri, 0, माप(ri));

	jffs2_dbg(1, "Writing replacement dnode for ino #%u from offset 0x%x to 0x%x\n",
		  f->inocache->ino, start, end);

	orig_end = end;
	orig_start = start;

	अगर (c->nr_मुक्त_blocks + c->nr_erasing_blocks > c->resv_blocks_gcmerge) अणु
		/* Attempt to करो some merging. But only expand to cover logically
		   adjacent frags अगर the block containing them is alपढ़ोy considered
		   to be dirty. Otherwise we end up with GC just going round in
		   circles dirtying the nodes it alपढ़ोy wrote out, especially
		   on न_अंकD where we have small eraseblocks and hence a much higher
		   chance of nodes having to be split to cross boundaries. */

		काष्ठा jffs2_node_frag *frag;
		uपूर्णांक32_t min, max;

		min = start & ~(PAGE_SIZE-1);
		max = min + PAGE_SIZE;

		frag = jffs2_lookup_node_frag(&f->fragtree, start);

		/* BUG_ON(!frag) but that'll happen anyway... */

		BUG_ON(frag->ofs != start);

		/* First grow करोwn... */
		जबतक((frag = frag_prev(frag)) && frag->ofs >= min) अणु

			/* If the previous frag करोesn't even reach the beginning, there's
			   excessive fragmentation. Just merge. */
			अगर (frag->ofs > min) अणु
				jffs2_dbg(1, "Expanding down to cover partial frag (0x%x-0x%x)\n",
					  frag->ofs, frag->ofs+frag->size);
				start = frag->ofs;
				जारी;
			पूर्ण
			/* OK. This frag holds the first byte of the page. */
			अगर (!frag->node || !frag->node->raw) अणु
				jffs2_dbg(1, "First frag in page is hole (0x%x-0x%x). Not expanding down.\n",
					  frag->ofs, frag->ofs+frag->size);
				अवरोध;
			पूर्ण अन्यथा अणु

				/* OK, it's a frag which extends to the beginning of the page. Does it live
				   in a block which is still considered clean? If so, करोn't obsolete it.
				   If not, cover it anyway. */

				काष्ठा jffs2_raw_node_ref *raw = frag->node->raw;
				काष्ठा jffs2_eraseblock *jeb;

				jeb = &c->blocks[raw->flash_offset / c->sector_size];

				अगर (jeb == c->gcblock) अणु
					jffs2_dbg(1, "Expanding down to cover frag (0x%x-0x%x) in gcblock at %08x\n",
						  frag->ofs,
						  frag->ofs + frag->size,
						  ref_offset(raw));
					start = frag->ofs;
					अवरोध;
				पूर्ण
				अगर (!ISसूचीTY(jeb->dirty_size + jeb->wasted_size)) अणु
					jffs2_dbg(1, "Not expanding down to cover frag (0x%x-0x%x) in clean block %08x\n",
						  frag->ofs,
						  frag->ofs + frag->size,
						  jeb->offset);
					अवरोध;
				पूर्ण

				jffs2_dbg(1, "Expanding down to cover frag (0x%x-0x%x) in dirty block %08x\n",
					  frag->ofs,
					  frag->ofs + frag->size,
					  jeb->offset);
				start = frag->ofs;
				अवरोध;
			पूर्ण
		पूर्ण

		/* ... then up */

		/* Find last frag which is actually part of the node we're to GC. */
		frag = jffs2_lookup_node_frag(&f->fragtree, end-1);

		जबतक((frag = frag_next(frag)) && frag->ofs+frag->size <= max) अणु

			/* If the previous frag करोesn't even reach the beginning, there's lots
			   of fragmentation. Just merge. */
			अगर (frag->ofs+frag->size < max) अणु
				jffs2_dbg(1, "Expanding up to cover partial frag (0x%x-0x%x)\n",
					  frag->ofs, frag->ofs+frag->size);
				end = frag->ofs + frag->size;
				जारी;
			पूर्ण

			अगर (!frag->node || !frag->node->raw) अणु
				jffs2_dbg(1, "Last frag in page is hole (0x%x-0x%x). Not expanding up.\n",
					  frag->ofs, frag->ofs+frag->size);
				अवरोध;
			पूर्ण अन्यथा अणु

				/* OK, it's a frag which extends to the beginning of the page. Does it live
				   in a block which is still considered clean? If so, करोn't obsolete it.
				   If not, cover it anyway. */

				काष्ठा jffs2_raw_node_ref *raw = frag->node->raw;
				काष्ठा jffs2_eraseblock *jeb;

				jeb = &c->blocks[raw->flash_offset / c->sector_size];

				अगर (jeb == c->gcblock) अणु
					jffs2_dbg(1, "Expanding up to cover frag (0x%x-0x%x) in gcblock at %08x\n",
						  frag->ofs,
						  frag->ofs + frag->size,
						  ref_offset(raw));
					end = frag->ofs + frag->size;
					अवरोध;
				पूर्ण
				अगर (!ISसूचीTY(jeb->dirty_size + jeb->wasted_size)) अणु
					jffs2_dbg(1, "Not expanding up to cover frag (0x%x-0x%x) in clean block %08x\n",
						  frag->ofs,
						  frag->ofs + frag->size,
						  jeb->offset);
					अवरोध;
				पूर्ण

				jffs2_dbg(1, "Expanding up to cover frag (0x%x-0x%x) in dirty block %08x\n",
					  frag->ofs,
					  frag->ofs + frag->size,
					  jeb->offset);
				end = frag->ofs + frag->size;
				अवरोध;
			पूर्ण
		पूर्ण
		jffs2_dbg(1, "Expanded dnode to write from (0x%x-0x%x) to (0x%x-0x%x)\n",
			  orig_start, orig_end, start, end);

		D1(BUG_ON(end > frag_last(&f->fragtree)->ofs + frag_last(&f->fragtree)->size));
		BUG_ON(end < orig_end);
		BUG_ON(start > orig_start);
	पूर्ण

	/* The rules state that we must obtain the page lock *beक्रमe* f->sem, so
	 * drop f->sem temporarily. Since we also hold c->alloc_sem, nothing's
	 * actually going to *change* so we're safe; we only allow पढ़ोing.
	 *
	 * It is important to note that jffs2_ग_लिखो_begin() will ensure that its
	 * page is marked Uptodate beक्रमe allocating space. That means that अगर we
	 * end up here trying to GC the *same* page that jffs2_ग_लिखो_begin() is
	 * trying to ग_लिखो out, पढ़ो_cache_page() will not deadlock. */
	mutex_unlock(&f->sem);
	page = पढ़ो_cache_page(inode->i_mapping, start >> PAGE_SHIFT,
			       jffs2_करो_पढ़ोpage_unlock, inode);
	अगर (IS_ERR(page)) अणु
		pr_warn("read_cache_page() returned error: %ld\n",
			PTR_ERR(page));
		mutex_lock(&f->sem);
		वापस PTR_ERR(page);
	पूर्ण

	pg_ptr = kmap(page);
	mutex_lock(&f->sem);

	offset = start;
	जबतक(offset < orig_end) अणु
		uपूर्णांक32_t datalen;
		uपूर्णांक32_t cdatalen;
		uपूर्णांक16_t comprtype = JFFS2_COMPR_NONE;

		ret = jffs2_reserve_space_gc(c, माप(ri) + JFFS2_MIN_DATA_LEN,
					&alloclen, JFFS2_SUMMARY_INODE_SIZE);

		अगर (ret) अणु
			pr_warn("jffs2_reserve_space_gc of %zd bytes for garbage_collect_dnode failed: %d\n",
				माप(ri) + JFFS2_MIN_DATA_LEN, ret);
			अवरोध;
		पूर्ण
		cdatalen = min_t(uपूर्णांक32_t, alloclen - माप(ri), end - offset);
		datalen = end - offset;

		ग_लिखोbuf = pg_ptr + (offset & (PAGE_SIZE -1));

		comprtype = jffs2_compress(c, f, ग_लिखोbuf, &comprbuf, &datalen, &cdatalen);

		ri.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
		ri.nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
		ri.totlen = cpu_to_je32(माप(ri) + cdatalen);
		ri.hdr_crc = cpu_to_je32(crc32(0, &ri, माप(काष्ठा jffs2_unknown_node)-4));

		ri.ino = cpu_to_je32(f->inocache->ino);
		ri.version = cpu_to_je32(++f->highest_version);
		ri.mode = cpu_to_jemode(JFFS2_F_I_MODE(f));
		ri.uid = cpu_to_je16(JFFS2_F_I_UID(f));
		ri.gid = cpu_to_je16(JFFS2_F_I_GID(f));
		ri.isize = cpu_to_je32(JFFS2_F_I_SIZE(f));
		ri.aसमय = cpu_to_je32(JFFS2_F_I_ATIME(f));
		ri.स_समय = cpu_to_je32(JFFS2_F_I_CTIME(f));
		ri.mसमय = cpu_to_je32(JFFS2_F_I_MTIME(f));
		ri.offset = cpu_to_je32(offset);
		ri.csize = cpu_to_je32(cdatalen);
		ri.dsize = cpu_to_je32(datalen);
		ri.compr = comprtype & 0xff;
		ri.usercompr = (comprtype >> 8) & 0xff;
		ri.node_crc = cpu_to_je32(crc32(0, &ri, माप(ri)-8));
		ri.data_crc = cpu_to_je32(crc32(0, comprbuf, cdatalen));

		new_fn = jffs2_ग_लिखो_dnode(c, f, &ri, comprbuf, cdatalen, ALLOC_GC);

		jffs2_मुक्त_comprbuf(comprbuf, ग_लिखोbuf);

		अगर (IS_ERR(new_fn)) अणु
			pr_warn("Error writing new dnode: %ld\n",
				PTR_ERR(new_fn));
			ret = PTR_ERR(new_fn);
			अवरोध;
		पूर्ण
		ret = jffs2_add_full_dnode_to_inode(c, f, new_fn);
		offset += datalen;
		अगर (f->metadata) अणु
			jffs2_mark_node_obsolete(c, f->metadata->raw);
			jffs2_मुक्त_full_dnode(f->metadata);
			f->metadata = शून्य;
		पूर्ण
	पूर्ण

	kunmap(page);
	put_page(page);
	वापस ret;
पूर्ण
