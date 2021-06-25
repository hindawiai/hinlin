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
#समावेश <linux/fs.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/crc32.h>
#समावेश <linux/pagemap.h>
#समावेश "nodelist.h"

अटल व्योम jffs2_obsolete_node_frag(काष्ठा jffs2_sb_info *c,
				     काष्ठा jffs2_node_frag *this);

व्योम jffs2_add_fd_to_list(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_full_dirent *new, काष्ठा jffs2_full_dirent **list)
अणु
	काष्ठा jffs2_full_dirent **prev = list;

	dbg_dentlist("add dirent \"%s\", ino #%u\n", new->name, new->ino);

	जबतक ((*prev) && (*prev)->nhash <= new->nhash) अणु
		अगर ((*prev)->nhash == new->nhash && !म_भेद((*prev)->name, new->name)) अणु
			/* Duplicate. Free one */
			अगर (new->version < (*prev)->version) अणु
				dbg_dentlist("Eep! Marking new dirent node obsolete, old is \"%s\", ino #%u\n",
					(*prev)->name, (*prev)->ino);
				jffs2_mark_node_obsolete(c, new->raw);
				jffs2_मुक्त_full_dirent(new);
			पूर्ण अन्यथा अणु
				dbg_dentlist("marking old dirent \"%s\", ino #%u obsolete\n",
					(*prev)->name, (*prev)->ino);
				new->next = (*prev)->next;
				/* It may have been a 'placeholder' deletion dirent, 
				   अगर jffs2_can_mark_obsolete() (see jffs2_करो_unlink()) */
				अगर ((*prev)->raw)
					jffs2_mark_node_obsolete(c, ((*prev)->raw));
				jffs2_मुक्त_full_dirent(*prev);
				*prev = new;
			पूर्ण
			वापस;
		पूर्ण
		prev = &((*prev)->next);
	पूर्ण
	new->next = *prev;
	*prev = new;
पूर्ण

uपूर्णांक32_t jffs2_truncate_fragtree(काष्ठा jffs2_sb_info *c, काष्ठा rb_root *list, uपूर्णांक32_t size)
अणु
	काष्ठा jffs2_node_frag *frag = jffs2_lookup_node_frag(list, size);

	dbg_fragtree("truncating fragtree to 0x%08x bytes\n", size);

	/* We know frag->ofs <= size. That's what lookup करोes क्रम us */
	अगर (frag && frag->ofs != size) अणु
		अगर (frag->ofs+frag->size > size) अणु
			frag->size = size - frag->ofs;
		पूर्ण
		frag = frag_next(frag);
	पूर्ण
	जबतक (frag && frag->ofs >= size) अणु
		काष्ठा jffs2_node_frag *next = frag_next(frag);

		frag_erase(frag, list);
		jffs2_obsolete_node_frag(c, frag);
		frag = next;
	पूर्ण

	अगर (size == 0)
		वापस 0;

	frag = frag_last(list);

	/* Sanity check क्रम truncation to दीर्घer than we started with... */
	अगर (!frag)
		वापस 0;
	अगर (frag->ofs + frag->size < size)
		वापस frag->ofs + frag->size;

	/* If the last fragment starts at the RAM page boundary, it is
	 * REF_PRISTINE irrespective of its size. */
	अगर (frag->node && (frag->ofs & (PAGE_SIZE - 1)) == 0) अणु
		dbg_fragtree2("marking the last fragment 0x%08x-0x%08x REF_PRISTINE.\n",
			frag->ofs, frag->ofs + frag->size);
		frag->node->raw->flash_offset = ref_offset(frag->node->raw) | REF_PRISTINE;
	पूर्ण
	वापस size;
पूर्ण

अटल व्योम jffs2_obsolete_node_frag(काष्ठा jffs2_sb_info *c,
				     काष्ठा jffs2_node_frag *this)
अणु
	अगर (this->node) अणु
		this->node->frags--;
		अगर (!this->node->frags) अणु
			/* The node has no valid frags left. It's totally obsoleted */
			dbg_fragtree2("marking old node @0x%08x (0x%04x-0x%04x) obsolete\n",
				ref_offset(this->node->raw), this->node->ofs, this->node->ofs+this->node->size);
			jffs2_mark_node_obsolete(c, this->node->raw);
			jffs2_मुक्त_full_dnode(this->node);
		पूर्ण अन्यथा अणु
			dbg_fragtree2("marking old node @0x%08x (0x%04x-0x%04x) REF_NORMAL. frags is %d\n",
				ref_offset(this->node->raw), this->node->ofs, this->node->ofs+this->node->size, this->node->frags);
			mark_ref_normal(this->node->raw);
		पूर्ण

	पूर्ण
	jffs2_मुक्त_node_frag(this);
पूर्ण

अटल व्योम jffs2_fragtree_insert(काष्ठा jffs2_node_frag *newfrag, काष्ठा jffs2_node_frag *base)
अणु
	काष्ठा rb_node *parent = &base->rb;
	काष्ठा rb_node **link = &parent;

	dbg_fragtree2("insert frag (0x%04x-0x%04x)\n", newfrag->ofs, newfrag->ofs + newfrag->size);

	जबतक (*link) अणु
		parent = *link;
		base = rb_entry(parent, काष्ठा jffs2_node_frag, rb);

		अगर (newfrag->ofs > base->ofs)
			link = &base->rb.rb_right;
		अन्यथा अगर (newfrag->ofs < base->ofs)
			link = &base->rb.rb_left;
		अन्यथा अणु
			JFFS2_ERROR("duplicate frag at %08x (%p,%p)\n", newfrag->ofs, newfrag, base);
			BUG();
		पूर्ण
	पूर्ण

	rb_link_node(&newfrag->rb, &base->rb, link);
पूर्ण

/*
 * Allocate and initializes a new fragment.
 */
अटल काष्ठा jffs2_node_frag * new_fragment(काष्ठा jffs2_full_dnode *fn, uपूर्णांक32_t ofs, uपूर्णांक32_t size)
अणु
	काष्ठा jffs2_node_frag *newfrag;

	newfrag = jffs2_alloc_node_frag();
	अगर (likely(newfrag)) अणु
		newfrag->ofs = ofs;
		newfrag->size = size;
		newfrag->node = fn;
	पूर्ण अन्यथा अणु
		JFFS2_ERROR("cannot allocate a jffs2_node_frag object\n");
	पूर्ण

	वापस newfrag;
पूर्ण

/*
 * Called when there is no overlapping fragment exist. Inserts a hole beक्रमe the new
 * fragment and inserts the new fragment to the fragtree.
 */
अटल पूर्णांक no_overlapping_node(काष्ठा jffs2_sb_info *c, काष्ठा rb_root *root,
		 	       काष्ठा jffs2_node_frag *newfrag,
			       काष्ठा jffs2_node_frag *this, uपूर्णांक32_t lastend)
अणु
	अगर (lastend < newfrag->node->ofs) अणु
		/* put a hole in beक्रमe the new fragment */
		काष्ठा jffs2_node_frag *holefrag;

		holefrag= new_fragment(शून्य, lastend, newfrag->node->ofs - lastend);
		अगर (unlikely(!holefrag)) अणु
			jffs2_मुक्त_node_frag(newfrag);
			वापस -ENOMEM;
		पूर्ण

		अगर (this) अणु
			/* By definition, the 'this' node has no right-hand child,
			   because there are no frags with offset greater than it.
			   So that's where we want to put the hole */
			dbg_fragtree2("add hole frag %#04x-%#04x on the right of the new frag.\n",
				holefrag->ofs, holefrag->ofs + holefrag->size);
			rb_link_node(&holefrag->rb, &this->rb, &this->rb.rb_right);
		पूर्ण अन्यथा अणु
			dbg_fragtree2("Add hole frag %#04x-%#04x to the root of the tree.\n",
				holefrag->ofs, holefrag->ofs + holefrag->size);
			rb_link_node(&holefrag->rb, शून्य, &root->rb_node);
		पूर्ण
		rb_insert_color(&holefrag->rb, root);
		this = holefrag;
	पूर्ण

	अगर (this) अणु
		/* By definition, the 'this' node has no right-hand child,
		   because there are no frags with offset greater than it.
		   So that's where we want to put new fragment */
		dbg_fragtree2("add the new node at the right\n");
		rb_link_node(&newfrag->rb, &this->rb, &this->rb.rb_right);
	पूर्ण अन्यथा अणु
		dbg_fragtree2("insert the new node at the root of the tree\n");
		rb_link_node(&newfrag->rb, शून्य, &root->rb_node);
	पूर्ण
	rb_insert_color(&newfrag->rb, root);

	वापस 0;
पूर्ण

/* Doesn't set inode->i_size */
अटल पूर्णांक jffs2_add_frag_to_fragtree(काष्ठा jffs2_sb_info *c, काष्ठा rb_root *root, काष्ठा jffs2_node_frag *newfrag)
अणु
	काष्ठा jffs2_node_frag *this;
	uपूर्णांक32_t lastend;

	/* Skip all the nodes which are completed beक्रमe this one starts */
	this = jffs2_lookup_node_frag(root, newfrag->node->ofs);

	अगर (this) अणु
		dbg_fragtree2("lookup gave frag 0x%04x-0x%04x; phys 0x%08x (*%p)\n",
			  this->ofs, this->ofs+this->size, this->node?(ref_offset(this->node->raw)):0xffffffff, this);
		lastend = this->ofs + this->size;
	पूर्ण अन्यथा अणु
		dbg_fragtree2("lookup gave no frag\n");
		lastend = 0;
	पूर्ण

	/* See अगर we ran off the end of the fragtree */
	अगर (lastend <= newfrag->ofs) अणु
		/* We did */

		/* Check अगर 'this' node was on the same page as the new node.
		   If so, both 'this' and the new node get marked REF_NORMAL so
		   the GC can take a look.
		*/
		अगर (lastend && (lastend-1) >> PAGE_SHIFT == newfrag->ofs >> PAGE_SHIFT) अणु
			अगर (this->node)
				mark_ref_normal(this->node->raw);
			mark_ref_normal(newfrag->node->raw);
		पूर्ण

		वापस no_overlapping_node(c, root, newfrag, this, lastend);
	पूर्ण

	अगर (this->node)
		dbg_fragtree2("dealing with frag %u-%u, phys %#08x(%d).\n",
		this->ofs, this->ofs + this->size,
		ref_offset(this->node->raw), ref_flags(this->node->raw));
	अन्यथा
		dbg_fragtree2("dealing with hole frag %u-%u.\n",
		this->ofs, this->ofs + this->size);

	/* OK. 'this' is poपूर्णांकing at the first frag that newfrag->ofs at least partially obsoletes,
	 * - i.e. newfrag->ofs < this->ofs+this->size && newfrag->ofs >= this->ofs
	 */
	अगर (newfrag->ofs > this->ofs) अणु
		/* This node isn't completely obsoleted. The start of it reमुख्यs valid */

		/* Mark the new node and the partially covered node REF_NORMAL -- let
		   the GC take a look at them */
		mark_ref_normal(newfrag->node->raw);
		अगर (this->node)
			mark_ref_normal(this->node->raw);

		अगर (this->ofs + this->size > newfrag->ofs + newfrag->size) अणु
			/* The new node splits 'this' frag पूर्णांकo two */
			काष्ठा jffs2_node_frag *newfrag2;

			अगर (this->node)
				dbg_fragtree2("split old frag 0x%04x-0x%04x, phys 0x%08x\n",
					this->ofs, this->ofs+this->size, ref_offset(this->node->raw));
			अन्यथा
				dbg_fragtree2("split old hole frag 0x%04x-0x%04x\n",
					this->ofs, this->ofs+this->size);

			/* New second frag poपूर्णांकing to this's node */
			newfrag2 = new_fragment(this->node, newfrag->ofs + newfrag->size,
						this->ofs + this->size - newfrag->ofs - newfrag->size);
			अगर (unlikely(!newfrag2))
				वापस -ENOMEM;
			अगर (this->node)
				this->node->frags++;

			/* Adjust size of original 'this' */
			this->size = newfrag->ofs - this->ofs;

			/* Now, we know there's no node with offset
			   greater than this->ofs but smaller than
			   newfrag2->ofs or newfrag->ofs, क्रम obvious
			   reasons. So we can करो a tree insert from
			   'this' to insert newfrag, and a tree insert
			   from newfrag to insert newfrag2. */
			jffs2_fragtree_insert(newfrag, this);
			rb_insert_color(&newfrag->rb, root);

			jffs2_fragtree_insert(newfrag2, newfrag);
			rb_insert_color(&newfrag2->rb, root);

			वापस 0;
		पूर्ण
		/* New node just reduces 'this' frag in size, doesn't split it */
		this->size = newfrag->ofs - this->ofs;

		/* Again, we know it lives करोwn here in the tree */
		jffs2_fragtree_insert(newfrag, this);
		rb_insert_color(&newfrag->rb, root);
	पूर्ण अन्यथा अणु
		/* New frag starts at the same poपूर्णांक as 'this' used to. Replace
		   it in the tree without करोing a delete and insertion */
		dbg_fragtree2("inserting newfrag (*%p),%d-%d in before 'this' (*%p),%d-%d\n",
			  newfrag, newfrag->ofs, newfrag->ofs+newfrag->size, this, this->ofs, this->ofs+this->size);

		rb_replace_node(&this->rb, &newfrag->rb, root);

		अगर (newfrag->ofs + newfrag->size >= this->ofs+this->size) अणु
			dbg_fragtree2("obsoleting node frag %p (%x-%x)\n", this, this->ofs, this->ofs+this->size);
			jffs2_obsolete_node_frag(c, this);
		पूर्ण अन्यथा अणु
			this->ofs += newfrag->size;
			this->size -= newfrag->size;

			jffs2_fragtree_insert(this, newfrag);
			rb_insert_color(&this->rb, root);
			वापस 0;
		पूर्ण
	पूर्ण
	/* OK, now we have newfrag added in the correct place in the tree, but
	   frag_next(newfrag) may be a fragment which is overlapped by it
	*/
	जबतक ((this = frag_next(newfrag)) && newfrag->ofs + newfrag->size >= this->ofs + this->size) अणु
		/* 'this' frag is obsoleted completely. */
		dbg_fragtree2("obsoleting node frag %p (%x-%x) and removing from tree\n",
			this, this->ofs, this->ofs+this->size);
		rb_erase(&this->rb, root);
		jffs2_obsolete_node_frag(c, this);
	पूर्ण
	/* Now we're pointing at the first frag which isn't totally obsoleted by
	   the new frag */

	अगर (!this || newfrag->ofs + newfrag->size == this->ofs)
		वापस 0;

	/* Still some overlap but we करोn't need to move it in the tree */
	this->size = (this->ofs + this->size) - (newfrag->ofs + newfrag->size);
	this->ofs = newfrag->ofs + newfrag->size;

	/* And mark them REF_NORMAL so the GC takes a look at them */
	अगर (this->node)
		mark_ref_normal(this->node->raw);
	mark_ref_normal(newfrag->node->raw);

	वापस 0;
पूर्ण

/*
 * Given an inode, probably with existing tree of fragments, add the new node
 * to the fragment tree.
 */
पूर्णांक jffs2_add_full_dnode_to_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f, काष्ठा jffs2_full_dnode *fn)
अणु
	पूर्णांक ret;
	काष्ठा jffs2_node_frag *newfrag;

	अगर (unlikely(!fn->size))
		वापस 0;

	newfrag = new_fragment(fn, fn->ofs, fn->size);
	अगर (unlikely(!newfrag))
		वापस -ENOMEM;
	newfrag->node->frags = 1;

	dbg_fragtree("adding node %#04x-%#04x @0x%08x on flash, newfrag *%p\n",
		  fn->ofs, fn->ofs+fn->size, ref_offset(fn->raw), newfrag);

	ret = jffs2_add_frag_to_fragtree(c, &f->fragtree, newfrag);
	अगर (unlikely(ret))
		वापस ret;

	/* If we now share a page with other nodes, mark either previous
	   or next node REF_NORMAL, as appropriate.  */
	अगर (newfrag->ofs & (PAGE_SIZE-1)) अणु
		काष्ठा jffs2_node_frag *prev = frag_prev(newfrag);

		mark_ref_normal(fn->raw);
		/* If we करोn't start at zero there's _always_ a previous */
		अगर (prev->node)
			mark_ref_normal(prev->node->raw);
	पूर्ण

	अगर ((newfrag->ofs+newfrag->size) & (PAGE_SIZE-1)) अणु
		काष्ठा jffs2_node_frag *next = frag_next(newfrag);

		अगर (next) अणु
			mark_ref_normal(fn->raw);
			अगर (next->node)
				mark_ref_normal(next->node->raw);
		पूर्ण
	पूर्ण
	jffs2_dbg_fragtree_paranoia_check_nolock(f);

	वापस 0;
पूर्ण

व्योम jffs2_set_inocache_state(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *ic, पूर्णांक state)
अणु
	spin_lock(&c->inocache_lock);
	ic->state = state;
	wake_up(&c->inocache_wq);
	spin_unlock(&c->inocache_lock);
पूर्ण

/* During mount, this needs no locking. During normal operation, its
   callers want to करो other stuff जबतक still holding the inocache_lock.
   Rather than पूर्णांकroducing special हाल get_ino_cache functions or
   callbacks, we just let the caller करो the locking itself. */

काष्ठा jffs2_inode_cache *jffs2_get_ino_cache(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t ino)
अणु
	काष्ठा jffs2_inode_cache *ret;

	ret = c->inocache_list[ino % c->inocache_hashsize];
	जबतक (ret && ret->ino < ino) अणु
		ret = ret->next;
	पूर्ण

	अगर (ret && ret->ino != ino)
		ret = शून्य;

	वापस ret;
पूर्ण

व्योम jffs2_add_ino_cache (काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *new)
अणु
	काष्ठा jffs2_inode_cache **prev;

	spin_lock(&c->inocache_lock);
	अगर (!new->ino)
		new->ino = ++c->highest_ino;

	dbg_inocache("add %p (ino #%u)\n", new, new->ino);

	prev = &c->inocache_list[new->ino % c->inocache_hashsize];

	जबतक ((*prev) && (*prev)->ino < new->ino) अणु
		prev = &(*prev)->next;
	पूर्ण
	new->next = *prev;
	*prev = new;

	spin_unlock(&c->inocache_lock);
पूर्ण

व्योम jffs2_del_ino_cache(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *old)
अणु
	काष्ठा jffs2_inode_cache **prev;

#अगर_घोषित CONFIG_JFFS2_FS_XATTR
	BUG_ON(old->xref);
#पूर्ण_अगर
	dbg_inocache("del %p (ino #%u)\n", old, old->ino);
	spin_lock(&c->inocache_lock);

	prev = &c->inocache_list[old->ino % c->inocache_hashsize];

	जबतक ((*prev) && (*prev)->ino < old->ino) अणु
		prev = &(*prev)->next;
	पूर्ण
	अगर ((*prev) == old) अणु
		*prev = old->next;
	पूर्ण

	/* Free it now unless it's in READING or CLEARING state, which
	   are the transitions upon पढ़ो_inode() and clear_inode(). The
	   rest of the समय we know nobody अन्यथा is looking at it, and
	   अगर it's held by read_inode() or clear_inode() they'll मुक्त it
	   क्रम themselves. */
	अगर (old->state != INO_STATE_READING && old->state != INO_STATE_CLEARING)
		jffs2_मुक्त_inode_cache(old);

	spin_unlock(&c->inocache_lock);
पूर्ण

व्योम jffs2_मुक्त_ino_caches(काष्ठा jffs2_sb_info *c)
अणु
	पूर्णांक i;
	काष्ठा jffs2_inode_cache *this, *next;

	क्रम (i=0; i < c->inocache_hashsize; i++) अणु
		this = c->inocache_list[i];
		जबतक (this) अणु
			next = this->next;
			jffs2_xattr_मुक्त_inode(c, this);
			jffs2_मुक्त_inode_cache(this);
			this = next;
		पूर्ण
		c->inocache_list[i] = शून्य;
	पूर्ण
पूर्ण

व्योम jffs2_मुक्त_raw_node_refs(काष्ठा jffs2_sb_info *c)
अणु
	पूर्णांक i;
	काष्ठा jffs2_raw_node_ref *this, *next;

	क्रम (i=0; i<c->nr_blocks; i++) अणु
		this = c->blocks[i].first_node;
		जबतक (this) अणु
			अगर (this[REFS_PER_BLOCK].flash_offset == REF_LINK_NODE)
				next = this[REFS_PER_BLOCK].next_in_ino;
			अन्यथा
				next = शून्य;

			jffs2_मुक्त_refblock(this);
			this = next;
		पूर्ण
		c->blocks[i].first_node = c->blocks[i].last_node = शून्य;
	पूर्ण
पूर्ण

काष्ठा jffs2_node_frag *jffs2_lookup_node_frag(काष्ठा rb_root *fragtree, uपूर्णांक32_t offset)
अणु
	/* The common हाल in lookup is that there will be a node
	   which precisely matches. So we go looking क्रम that first */
	काष्ठा rb_node *next;
	काष्ठा jffs2_node_frag *prev = शून्य;
	काष्ठा jffs2_node_frag *frag = शून्य;

	dbg_fragtree2("root %p, offset %d\n", fragtree, offset);

	next = fragtree->rb_node;

	जबतक(next) अणु
		frag = rb_entry(next, काष्ठा jffs2_node_frag, rb);

		अगर (frag->ofs + frag->size <= offset) अणु
			/* Remember the बंदst smaller match on the way करोwn */
			अगर (!prev || frag->ofs > prev->ofs)
				prev = frag;
			next = frag->rb.rb_right;
		पूर्ण अन्यथा अगर (frag->ofs > offset) अणु
			next = frag->rb.rb_left;
		पूर्ण अन्यथा अणु
			वापस frag;
		पूर्ण
	पूर्ण

	/* Exact match not found. Go back up looking at each parent,
	   and वापस the बंदst smaller one */

	अगर (prev)
		dbg_fragtree2("no match. Returning frag %#04x-%#04x, closest previous\n",
			  prev->ofs, prev->ofs+prev->size);
	अन्यथा
		dbg_fragtree2("returning NULL, empty fragtree\n");

	वापस prev;
पूर्ण

/* Pass 'c' argument to indicate that nodes should be marked obsolete as
   they're समाप्तed. */
व्योम jffs2_समाप्त_fragtree(काष्ठा rb_root *root, काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा jffs2_node_frag *frag, *next;

	dbg_fragtree("killing\n");
	rbtree_postorder_क्रम_each_entry_safe(frag, next, root, rb) अणु
		अगर (frag->node && !(--frag->node->frags)) अणु
			/* Not a hole, and it's the final reमुख्यing frag
			   of this node. Free the node */
			अगर (c)
				jffs2_mark_node_obsolete(c, frag->node->raw);

			jffs2_मुक्त_full_dnode(frag->node);
		पूर्ण

		jffs2_मुक्त_node_frag(frag);
		cond_resched();
	पूर्ण
पूर्ण

काष्ठा jffs2_raw_node_ref *jffs2_link_node_ref(काष्ठा jffs2_sb_info *c,
					       काष्ठा jffs2_eraseblock *jeb,
					       uपूर्णांक32_t ofs, uपूर्णांक32_t len,
					       काष्ठा jffs2_inode_cache *ic)
अणु
	काष्ठा jffs2_raw_node_ref *ref;

	BUG_ON(!jeb->allocated_refs);
	jeb->allocated_refs--;

	ref = jeb->last_node;

	dbg_noderef("Last node at %p is (%08x,%p)\n", ref, ref->flash_offset,
		    ref->next_in_ino);

	जबतक (ref->flash_offset != REF_EMPTY_NODE) अणु
		अगर (ref->flash_offset == REF_LINK_NODE)
			ref = ref->next_in_ino;
		अन्यथा
			ref++;
	पूर्ण

	dbg_noderef("New ref is %p (%08x becomes %08x,%p) len 0x%x\n", ref, 
		    ref->flash_offset, ofs, ref->next_in_ino, len);

	ref->flash_offset = ofs;

	अगर (!jeb->first_node) अणु
		jeb->first_node = ref;
		BUG_ON(ref_offset(ref) != jeb->offset);
	पूर्ण अन्यथा अगर (unlikely(ref_offset(ref) != jeb->offset + c->sector_size - jeb->मुक्त_size)) अणु
		uपूर्णांक32_t last_len = ref_totlen(c, jeb, jeb->last_node);

		JFFS2_ERROR("Adding new ref %p at (0x%08x-0x%08x) not immediately after previous (0x%08x-0x%08x)\n",
			    ref, ref_offset(ref), ref_offset(ref)+len,
			    ref_offset(jeb->last_node), 
			    ref_offset(jeb->last_node)+last_len);
		BUG();
	पूर्ण
	jeb->last_node = ref;

	अगर (ic) अणु
		ref->next_in_ino = ic->nodes;
		ic->nodes = ref;
	पूर्ण अन्यथा अणु
		ref->next_in_ino = शून्य;
	पूर्ण

	चयन(ref_flags(ref)) अणु
	हाल REF_UNCHECKED:
		c->unchecked_size += len;
		jeb->unchecked_size += len;
		अवरोध;

	हाल REF_NORMAL:
	हाल REF_PRISTINE:
		c->used_size += len;
		jeb->used_size += len;
		अवरोध;

	हाल REF_OBSOLETE:
		c->dirty_size += len;
		jeb->dirty_size += len;
		अवरोध;
	पूर्ण
	c->मुक्त_size -= len;
	jeb->मुक्त_size -= len;

#अगर_घोषित TEST_TOTLEN
	/* Set (and test) __totlen field... क्रम now */
	ref->__totlen = len;
	ref_totlen(c, jeb, ref);
#पूर्ण_अगर
	वापस ref;
पूर्ण

/* No locking, no reservation of 'ref'. Do not use on a live file प्रणाली */
पूर्णांक jffs2_scan_dirty_space(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
			   uपूर्णांक32_t size)
अणु
	अगर (!size)
		वापस 0;
	अगर (unlikely(size > jeb->मुक्त_size)) अणु
		pr_crit("Dirty space 0x%x larger then free_size 0x%x (wasted 0x%x)\n",
			size, jeb->मुक्त_size, jeb->wasted_size);
		BUG();
	पूर्ण
	/* REF_EMPTY_NODE is !obsolete, so that works OK */
	अगर (jeb->last_node && ref_obsolete(jeb->last_node)) अणु
#अगर_घोषित TEST_TOTLEN
		jeb->last_node->__totlen += size;
#पूर्ण_अगर
		c->dirty_size += size;
		c->मुक्त_size -= size;
		jeb->dirty_size += size;
		jeb->मुक्त_size -= size;
	पूर्ण अन्यथा अणु
		uपूर्णांक32_t ofs = jeb->offset + c->sector_size - jeb->मुक्त_size;
		ofs |= REF_OBSOLETE;

		jffs2_link_node_ref(c, jeb, ofs, size, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

/* Calculate totlen from surrounding nodes or eraseblock */
अटल अंतरभूत uपूर्णांक32_t __ref_totlen(काष्ठा jffs2_sb_info *c,
				    काष्ठा jffs2_eraseblock *jeb,
				    काष्ठा jffs2_raw_node_ref *ref)
अणु
	uपूर्णांक32_t ref_end;
	काष्ठा jffs2_raw_node_ref *next_ref = ref_next(ref);

	अगर (next_ref)
		ref_end = ref_offset(next_ref);
	अन्यथा अणु
		अगर (!jeb)
			jeb = &c->blocks[ref->flash_offset / c->sector_size];

		/* Last node in block. Use मुक्त_space */
		अगर (unlikely(ref != jeb->last_node)) अणु
			pr_crit("ref %p @0x%08x is not jeb->last_node (%p @0x%08x)\n",
				ref, ref_offset(ref), jeb->last_node,
				jeb->last_node ?
				ref_offset(jeb->last_node) : 0);
			BUG();
		पूर्ण
		ref_end = jeb->offset + c->sector_size - jeb->मुक्त_size;
	पूर्ण
	वापस ref_end - ref_offset(ref);
पूर्ण

uपूर्णांक32_t __jffs2_ref_totlen(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
			    काष्ठा jffs2_raw_node_ref *ref)
अणु
	uपूर्णांक32_t ret;

	ret = __ref_totlen(c, jeb, ref);

#अगर_घोषित TEST_TOTLEN
	अगर (unlikely(ret != ref->__totlen)) अणु
		अगर (!jeb)
			jeb = &c->blocks[ref->flash_offset / c->sector_size];

		pr_crit("Totlen for ref at %p (0x%08x-0x%08x) miscalculated as 0x%x instead of %x\n",
			ref, ref_offset(ref), ref_offset(ref) + ref->__totlen,
			ret, ref->__totlen);
		अगर (ref_next(ref)) अणु
			pr_crit("next %p (0x%08x-0x%08x)\n",
				ref_next(ref), ref_offset(ref_next(ref)),
				ref_offset(ref_next(ref)) + ref->__totlen);
		पूर्ण अन्यथा 
			pr_crit("No next ref. jeb->last_node is %p\n",
				jeb->last_node);

		pr_crit("jeb->wasted_size %x, dirty_size %x, used_size %x, free_size %x\n",
			jeb->wasted_size, jeb->dirty_size, jeb->used_size,
			jeb->मुक्त_size);

#अगर defined(JFFS2_DBG_DUMPS) || defined(JFFS2_DBG_PARANOIA_CHECKS)
		__jffs2_dbg_dump_node_refs_nolock(c, jeb);
#पूर्ण_अगर

		WARN_ON(1);

		ret = ref->__totlen;
	पूर्ण
#पूर्ण_अगर /* TEST_TOTLEN */
	वापस ret;
पूर्ण
