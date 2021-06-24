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
#समावेश <linux/fs.h>
#समावेश <linux/crc32.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/compiler.h>
#समावेश "nodelist.h"

/*
 * Check the data CRC of the node.
 *
 * Returns: 0 अगर the data CRC is correct;
 * 	    1 - अगर incorrect;
 *	    error code अगर an error occurred.
 */
अटल पूर्णांक check_node_data(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_पंचांगp_dnode_info *tn)
अणु
	काष्ठा jffs2_raw_node_ref *ref = tn->fn->raw;
	पूर्णांक err = 0, poपूर्णांकed = 0;
	काष्ठा jffs2_eraseblock *jeb;
	अचिन्हित अक्षर *buffer;
	uपूर्णांक32_t crc, ofs, len;
	माप_प्रकार retlen;

	BUG_ON(tn->csize == 0);

	/* Calculate how many bytes were alपढ़ोy checked */
	ofs = ref_offset(ref) + माप(काष्ठा jffs2_raw_inode);
	len = tn->csize;

	अगर (jffs2_is_ग_लिखोbuffered(c)) अणु
		पूर्णांक adj = ofs % c->wbuf_pagesize;
		अगर (likely(adj))
			adj = c->wbuf_pagesize - adj;

		अगर (adj >= tn->csize) अणु
			dbg_पढ़ोinode("no need to check node at %#08x, data length %u, data starts at %#08x - it has already been checked.\n",
				      ref_offset(ref), tn->csize, ofs);
			जाओ adj_acc;
		पूर्ण

		ofs += adj;
		len -= adj;
	पूर्ण

	dbg_पढ़ोinode("check node at %#08x, data length %u, partial CRC %#08x, correct CRC %#08x, data starts at %#08x, start checking from %#08x - %u bytes.\n",
		ref_offset(ref), tn->csize, tn->partial_crc, tn->data_crc, ofs - len, ofs, len);

#अगर_अघोषित __ECOS
	/* TODO: instead, incapsulate poपूर्णांक() stuff to jffs2_flash_पढ़ो(),
	 * adding and jffs2_flash_पढ़ो_end() पूर्णांकerface. */
	err = mtd_poपूर्णांक(c->mtd, ofs, len, &retlen, (व्योम **)&buffer, शून्य);
	अगर (!err && retlen < len) अणु
		JFFS2_WARNING("MTD point returned len too short: %zu instead of %u.\n", retlen, tn->csize);
		mtd_unpoपूर्णांक(c->mtd, ofs, retlen);
	पूर्ण अन्यथा अगर (err) अणु
		अगर (err != -EOPNOTSUPP)
			JFFS2_WARNING("MTD point failed: error code %d.\n", err);
	पूर्ण अन्यथा
		poपूर्णांकed = 1; /* succefully poपूर्णांकed to device */
#पूर्ण_अगर

	अगर (!poपूर्णांकed) अणु
		buffer = kदो_स्मृति(len, GFP_KERNEL);
		अगर (unlikely(!buffer))
			वापस -ENOMEM;

		/* TODO: this is very frequent pattern, make it a separate
		 * routine */
		err = jffs2_flash_पढ़ो(c, ofs, len, &retlen, buffer);
		अगर (err) अणु
			JFFS2_ERROR("can not read %d bytes from 0x%08x, error code: %d.\n", len, ofs, err);
			जाओ मुक्त_out;
		पूर्ण

		अगर (retlen != len) अणु
			JFFS2_ERROR("short read at %#08x: %zd instead of %d.\n", ofs, retlen, len);
			err = -EIO;
			जाओ मुक्त_out;
		पूर्ण
	पूर्ण

	/* Continue calculating CRC */
	crc = crc32(tn->partial_crc, buffer, len);
	अगर(!poपूर्णांकed)
		kमुक्त(buffer);
#अगर_अघोषित __ECOS
	अन्यथा
		mtd_unpoपूर्णांक(c->mtd, ofs, len);
#पूर्ण_अगर

	अगर (crc != tn->data_crc) अणु
		JFFS2_NOTICE("wrong data CRC in data node at 0x%08x: read %#08x, calculated %#08x.\n",
			     ref_offset(ref), tn->data_crc, crc);
		वापस 1;
	पूर्ण

adj_acc:
	jeb = &c->blocks[ref->flash_offset / c->sector_size];
	len = ref_totlen(c, jeb, ref);
	/* If it should be REF_NORMAL, it'll get marked as such when
	   we build the fragtree, लघुly. No need to worry about GC
	   moving it जबतक it's marked REF_PRISTINE -- GC won't happen
	   till we've finished checking every inode anyway. */
	ref->flash_offset |= REF_PRISTINE;
	/*
	 * Mark the node as having been checked and fix the
	 * accounting accordingly.
	 */
	spin_lock(&c->erase_completion_lock);
	jeb->used_size += len;
	jeb->unchecked_size -= len;
	c->used_size += len;
	c->unchecked_size -= len;
	jffs2_dbg_acct_paranoia_check_nolock(c, jeb);
	spin_unlock(&c->erase_completion_lock);

	वापस 0;

मुक्त_out:
	अगर(!poपूर्णांकed)
		kमुक्त(buffer);
#अगर_अघोषित __ECOS
	अन्यथा
		mtd_unpoपूर्णांक(c->mtd, ofs, len);
#पूर्ण_अगर
	वापस err;
पूर्ण

/*
 * Helper function क्रम jffs2_add_older_frag_to_fragtree().
 *
 * Checks the node अगर we are in the checking stage.
 */
अटल पूर्णांक check_tn_node(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_पंचांगp_dnode_info *tn)
अणु
	पूर्णांक ret;

	BUG_ON(ref_obsolete(tn->fn->raw));

	/* We only check the data CRC of unchecked nodes */
	अगर (ref_flags(tn->fn->raw) != REF_UNCHECKED)
		वापस 0;

	dbg_पढ़ोinode("check node %#04x-%#04x, phys offs %#08x\n",
		      tn->fn->ofs, tn->fn->ofs + tn->fn->size, ref_offset(tn->fn->raw));

	ret = check_node_data(c, tn);
	अगर (unlikely(ret < 0)) अणु
		JFFS2_ERROR("check_node_data() returned error: %d.\n",
			ret);
	पूर्ण अन्यथा अगर (unlikely(ret > 0)) अणु
		dbg_पढ़ोinode("CRC error, mark it obsolete.\n");
		jffs2_mark_node_obsolete(c, tn->fn->raw);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा jffs2_पंचांगp_dnode_info *jffs2_lookup_tn(काष्ठा rb_root *tn_root, uपूर्णांक32_t offset)
अणु
	काष्ठा rb_node *next;
	काष्ठा jffs2_पंचांगp_dnode_info *tn = शून्य;

	dbg_पढ़ोinode("root %p, offset %d\n", tn_root, offset);

	next = tn_root->rb_node;

	जबतक (next) अणु
		tn = rb_entry(next, काष्ठा jffs2_पंचांगp_dnode_info, rb);

		अगर (tn->fn->ofs < offset)
			next = tn->rb.rb_right;
		अन्यथा अगर (tn->fn->ofs >= offset)
			next = tn->rb.rb_left;
		अन्यथा
			अवरोध;
	पूर्ण

	वापस tn;
पूर्ण


अटल व्योम jffs2_समाप्त_tn(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_पंचांगp_dnode_info *tn)
अणु
	jffs2_mark_node_obsolete(c, tn->fn->raw);
	jffs2_मुक्त_full_dnode(tn->fn);
	jffs2_मुक्त_पंचांगp_dnode_info(tn);
पूर्ण
/*
 * This function is used when we पढ़ो an inode. Data nodes arrive in
 * arbitrary order -- they may be older or newer than the nodes which
 * are alपढ़ोy in the tree. Where overlaps occur, the older node can
 * be discarded as दीर्घ as the newer passes the CRC check. We करोn't
 * bother to keep track of holes in this rbtree, and neither करो we deal
 * with frags -- we can have multiple entries starting at the same
 * offset, and the one with the smallest length will come first in the
 * ordering.
 *
 * Returns 0 अगर the node was handled (including marking it obsolete)
 *	 < 0 an अगर error occurred
 */
अटल पूर्णांक jffs2_add_tn_to_tree(काष्ठा jffs2_sb_info *c,
				काष्ठा jffs2_पढ़ोinode_info *rii,
				काष्ठा jffs2_पंचांगp_dnode_info *tn)
अणु
	uपूर्णांक32_t fn_end = tn->fn->ofs + tn->fn->size;
	काष्ठा jffs2_पंचांगp_dnode_info *this, *ptn;

	dbg_पढ़ोinode("insert fragment %#04x-%#04x, ver %u at %08x\n", tn->fn->ofs, fn_end, tn->version, ref_offset(tn->fn->raw));

	/* If a node has zero dsize, we only have to keep it अगर it might be the
	   node with highest version -- i.e. the one which will end up as f->metadata.
	   Note that such nodes won't be REF_UNCHECKED since there are no data to
	   check anyway. */
	अगर (!tn->fn->size) अणु
		अगर (rii->mdata_tn) अणु
			अगर (rii->mdata_tn->version < tn->version) अणु
				/* We had a candidate mdata node alपढ़ोy */
				dbg_पढ़ोinode("kill old mdata with ver %d\n", rii->mdata_tn->version);
				jffs2_समाप्त_tn(c, rii->mdata_tn);
			पूर्ण अन्यथा अणु
				dbg_पढ़ोinode("kill new mdata with ver %d (older than existing %d\n",
					      tn->version, rii->mdata_tn->version);
				jffs2_समाप्त_tn(c, tn);
				वापस 0;
			पूर्ण
		पूर्ण
		rii->mdata_tn = tn;
		dbg_पढ़ोinode("keep new mdata with ver %d\n", tn->version);
		वापस 0;
	पूर्ण

	/* Find the earliest node which _may_ be relevant to this one */
	this = jffs2_lookup_tn(&rii->tn_root, tn->fn->ofs);
	अगर (this) अणु
		/* If the node is coincident with another at a lower address,
		   back up until the other node is found. It may be relevant */
		जबतक (this->overlapped) अणु
			ptn = tn_prev(this);
			अगर (!ptn) अणु
				/*
				 * We समाप्तed a node which set the overlapped
				 * flags during the scan. Fix it up.
				 */
				this->overlapped = 0;
				अवरोध;
			पूर्ण
			this = ptn;
		पूर्ण
		dbg_पढ़ोinode("'this' found %#04x-%#04x (%s)\n", this->fn->ofs, this->fn->ofs + this->fn->size, this->fn ? "data" : "hole");
	पूर्ण

	जबतक (this) अणु
		अगर (this->fn->ofs > fn_end)
			अवरोध;
		dbg_पढ़ोinode("Ponder this ver %d, 0x%x-0x%x\n",
			      this->version, this->fn->ofs, this->fn->size);

		अगर (this->version == tn->version) अणु
			/* Version number collision means REF_PRISTINE GC. Accept either of them
			   as दीर्घ as the CRC is correct. Check the one we have alपढ़ोy...  */
			अगर (!check_tn_node(c, this)) अणु
				/* The one we alपढ़ोy had was OK. Keep it and throw away the new one */
				dbg_पढ़ोinode("Like old node. Throw away new\n");
				jffs2_समाप्त_tn(c, tn);
				वापस 0;
			पूर्ण अन्यथा अणु
				/* Who cares अगर the new one is good; keep it क्रम now anyway. */
				dbg_पढ़ोinode("Like new node. Throw away old\n");
				rb_replace_node(&this->rb, &tn->rb, &rii->tn_root);
				jffs2_समाप्त_tn(c, this);
				/* Same overlapping from in front and behind */
				वापस 0;
			पूर्ण
		पूर्ण
		अगर (this->version < tn->version &&
		    this->fn->ofs >= tn->fn->ofs &&
		    this->fn->ofs + this->fn->size <= fn_end) अणु
			/* New node entirely overlaps 'this' */
			अगर (check_tn_node(c, tn)) अणु
				dbg_पढ़ोinode("new node bad CRC\n");
				jffs2_समाप्त_tn(c, tn);
				वापस 0;
			पूर्ण
			/* ... and is good. Kill 'this' and any subsequent nodes which are also overlapped */
			जबतक (this && this->fn->ofs + this->fn->size <= fn_end) अणु
				काष्ठा jffs2_पंचांगp_dnode_info *next = tn_next(this);
				अगर (this->version < tn->version) अणु
					tn_erase(this, &rii->tn_root);
					dbg_पढ़ोinode("Kill overlapped ver %d, 0x%x-0x%x\n",
						      this->version, this->fn->ofs,
						      this->fn->ofs+this->fn->size);
					jffs2_समाप्त_tn(c, this);
				पूर्ण
				this = next;
			पूर्ण
			dbg_पढ़ोinode("Done killing overlapped nodes\n");
			जारी;
		पूर्ण
		अगर (this->version > tn->version &&
		    this->fn->ofs <= tn->fn->ofs &&
		    this->fn->ofs+this->fn->size >= fn_end) अणु
			/* New node entirely overlapped by 'this' */
			अगर (!check_tn_node(c, this)) अणु
				dbg_पढ़ोinode("Good CRC on old node. Kill new\n");
				jffs2_समाप्त_tn(c, tn);
				वापस 0;
			पूर्ण
			/* ... but 'this' was bad. Replace it... */
			dbg_पढ़ोinode("Bad CRC on old overlapping node. Kill it\n");
			tn_erase(this, &rii->tn_root);
			jffs2_समाप्त_tn(c, this);
			अवरोध;
		पूर्ण

		this = tn_next(this);
	पूर्ण

	/* We neither completely obsoleted nor were completely
	   obsoleted by an earlier node. Insert पूर्णांकo the tree */
	अणु
		काष्ठा rb_node *parent;
		काष्ठा rb_node **link = &rii->tn_root.rb_node;
		काष्ठा jffs2_पंचांगp_dnode_info *insert_poपूर्णांक = शून्य;

		जबतक (*link) अणु
			parent = *link;
			insert_poपूर्णांक = rb_entry(parent, काष्ठा jffs2_पंचांगp_dnode_info, rb);
			अगर (tn->fn->ofs > insert_poपूर्णांक->fn->ofs)
				link = &insert_poपूर्णांक->rb.rb_right;
			अन्यथा अगर (tn->fn->ofs < insert_poपूर्णांक->fn->ofs ||
				 tn->fn->size < insert_poपूर्णांक->fn->size)
				link = &insert_poपूर्णांक->rb.rb_left;
			अन्यथा
				link = &insert_poपूर्णांक->rb.rb_right;
		पूर्ण
		rb_link_node(&tn->rb, &insert_poपूर्णांक->rb, link);
		rb_insert_color(&tn->rb, &rii->tn_root);
	पूर्ण

	/* If there's anything behind that overlaps us, note it */
	this = tn_prev(tn);
	अगर (this) अणु
		जबतक (1) अणु
			अगर (this->fn->ofs + this->fn->size > tn->fn->ofs) अणु
				dbg_पढ़ोinode("Node is overlapped by %p (v %d, 0x%x-0x%x)\n",
					      this, this->version, this->fn->ofs,
					      this->fn->ofs+this->fn->size);
				tn->overlapped = 1;
				अवरोध;
			पूर्ण
			अगर (!this->overlapped)
				अवरोध;

			ptn = tn_prev(this);
			अगर (!ptn) अणु
				/*
				 * We समाप्तed a node which set the overlapped
				 * flags during the scan. Fix it up.
				 */
				this->overlapped = 0;
				अवरोध;
			पूर्ण
			this = ptn;
		पूर्ण
	पूर्ण

	/* If the new node overlaps anything ahead, note it */
	this = tn_next(tn);
	जबतक (this && this->fn->ofs < fn_end) अणु
		this->overlapped = 1;
		dbg_पढ़ोinode("Node ver %d, 0x%x-0x%x is overlapped\n",
			      this->version, this->fn->ofs,
			      this->fn->ofs+this->fn->size);
		this = tn_next(this);
	पूर्ण
	वापस 0;
पूर्ण

/* Trivial function to हटाओ the last node in the tree. Which by definition
   has no right-hand child ै  so can be हटाओd just by making its left-hand
   child (अगर any) take its place under its parent. Since this is only करोne
   when we're consuming the whole tree, there's no need to use rb_erase()
   and let it worry about adjusting colours and balancing the tree. That
   would just be a waste of समय. */
अटल व्योम eat_last(काष्ठा rb_root *root, काष्ठा rb_node *node)
अणु
	काष्ठा rb_node *parent = rb_parent(node);
	काष्ठा rb_node **link;

	/* LAST! */
	BUG_ON(node->rb_right);

	अगर (!parent)
		link = &root->rb_node;
	अन्यथा अगर (node == parent->rb_left)
		link = &parent->rb_left;
	अन्यथा
		link = &parent->rb_right;

	*link = node->rb_left;
	अगर (node->rb_left)
		node->rb_left->__rb_parent_color = node->__rb_parent_color;
पूर्ण

/* We put the version tree in reverse order, so we can use the same eat_last()
   function that we use to consume the पंचांगpnode tree (tn_root). */
अटल व्योम ver_insert(काष्ठा rb_root *ver_root, काष्ठा jffs2_पंचांगp_dnode_info *tn)
अणु
	काष्ठा rb_node **link = &ver_root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा jffs2_पंचांगp_dnode_info *this_tn;

	जबतक (*link) अणु
		parent = *link;
		this_tn = rb_entry(parent, काष्ठा jffs2_पंचांगp_dnode_info, rb);

		अगर (tn->version > this_tn->version)
			link = &parent->rb_left;
		अन्यथा
			link = &parent->rb_right;
	पूर्ण
	dbg_पढ़ोinode("Link new node at %p (root is %p)\n", link, ver_root);
	rb_link_node(&tn->rb, parent, link);
	rb_insert_color(&tn->rb, ver_root);
पूर्ण

/* Build final, normal fragtree from tn tree. It करोesn't matter which order
   we add nodes to the real fragtree, as दीर्घ as they करोn't overlap. And
   having thrown away the majority of overlapped nodes as we went, there
   really shouldn't be many sets of nodes which करो overlap. If we start at
   the end, we can use the overlap markers -- we can just eat nodes which
   aren't overlapped, and when we encounter nodes which _करो_ overlap we
   sort them all पूर्णांकo a temporary tree in version order beक्रमe replaying them. */
अटल पूर्णांक jffs2_build_inode_fragtree(काष्ठा jffs2_sb_info *c,
				      काष्ठा jffs2_inode_info *f,
				      काष्ठा jffs2_पढ़ोinode_info *rii)
अणु
	काष्ठा jffs2_पंचांगp_dnode_info *pen, *last, *this;
	काष्ठा rb_root ver_root = RB_ROOT;
	uपूर्णांक32_t high_ver = 0;

	अगर (rii->mdata_tn) अणु
		dbg_पढ़ोinode("potential mdata is ver %d at %p\n", rii->mdata_tn->version, rii->mdata_tn);
		high_ver = rii->mdata_tn->version;
		rii->latest_ref = rii->mdata_tn->fn->raw;
	पूर्ण
#अगर_घोषित JFFS2_DBG_READINODE_MESSAGES
	this = tn_last(&rii->tn_root);
	जबतक (this) अणु
		dbg_पढ़ोinode("tn %p ver %d range 0x%x-0x%x ov %d\n", this, this->version, this->fn->ofs,
			      this->fn->ofs+this->fn->size, this->overlapped);
		this = tn_prev(this);
	पूर्ण
#पूर्ण_अगर
	pen = tn_last(&rii->tn_root);
	जबतक ((last = pen)) अणु
		pen = tn_prev(last);

		eat_last(&rii->tn_root, &last->rb);
		ver_insert(&ver_root, last);

		अगर (unlikely(last->overlapped)) अणु
			अगर (pen)
				जारी;
			/*
			 * We समाप्तed a node which set the overlapped
			 * flags during the scan. Fix it up.
			 */
			last->overlapped = 0;
		पूर्ण

		/* Now we have a bunch of nodes in reverse version
		   order, in the tree at ver_root. Most of the समय,
		   there'll actually be only one node in the 'tree',
		   in fact. */
		this = tn_last(&ver_root);

		जबतक (this) अणु
			काष्ठा jffs2_पंचांगp_dnode_info *vers_next;
			पूर्णांक ret;
			vers_next = tn_prev(this);
			eat_last(&ver_root, &this->rb);
			अगर (check_tn_node(c, this)) अणु
				dbg_पढ़ोinode("node ver %d, 0x%x-0x%x failed CRC\n",
					     this->version, this->fn->ofs,
					     this->fn->ofs+this->fn->size);
				jffs2_समाप्त_tn(c, this);
			पूर्ण अन्यथा अणु
				अगर (this->version > high_ver) अणु
					/* Note that this is dअगरferent from the other
					   highest_version, because this one is only
					   counting _valid_ nodes which could give the
					   latest inode metadata */
					high_ver = this->version;
					rii->latest_ref = this->fn->raw;
				पूर्ण
				dbg_पढ़ोinode("Add %p (v %d, 0x%x-0x%x, ov %d) to fragtree\n",
					     this, this->version, this->fn->ofs,
					     this->fn->ofs+this->fn->size, this->overlapped);

				ret = jffs2_add_full_dnode_to_inode(c, f, this->fn);
				अगर (ret) अणु
					/* Free the nodes in vers_root; let the caller
					   deal with the rest */
					JFFS2_ERROR("Add node to tree failed %d\n", ret);
					जबतक (1) अणु
						vers_next = tn_prev(this);
						अगर (check_tn_node(c, this))
							jffs2_mark_node_obsolete(c, this->fn->raw);
						jffs2_मुक्त_full_dnode(this->fn);
						jffs2_मुक्त_पंचांगp_dnode_info(this);
						this = vers_next;
						अगर (!this)
							अवरोध;
						eat_last(&ver_root, &vers_next->rb);
					पूर्ण
					वापस ret;
				पूर्ण
				jffs2_मुक्त_पंचांगp_dnode_info(this);
			पूर्ण
			this = vers_next;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम jffs2_मुक्त_पंचांगp_dnode_info_list(काष्ठा rb_root *list)
अणु
	काष्ठा jffs2_पंचांगp_dnode_info *tn, *next;

	rbtree_postorder_क्रम_each_entry_safe(tn, next, list, rb) अणु
			jffs2_मुक्त_full_dnode(tn->fn);
			jffs2_मुक्त_पंचांगp_dnode_info(tn);
	पूर्ण

	*list = RB_ROOT;
पूर्ण

अटल व्योम jffs2_मुक्त_full_dirent_list(काष्ठा jffs2_full_dirent *fd)
अणु
	काष्ठा jffs2_full_dirent *next;

	जबतक (fd) अणु
		next = fd->next;
		jffs2_मुक्त_full_dirent(fd);
		fd = next;
	पूर्ण
पूर्ण

/* Returns first valid node after 'ref'. May return 'ref' */
अटल काष्ठा jffs2_raw_node_ref *jffs2_first_valid_node(काष्ठा jffs2_raw_node_ref *ref)
अणु
	जबतक (ref && ref->next_in_ino) अणु
		अगर (!ref_obsolete(ref))
			वापस ref;
		dbg_noderef("node at 0x%08x is obsoleted. Ignoring.\n", ref_offset(ref));
		ref = ref->next_in_ino;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Helper function क्रम jffs2_get_inode_nodes().
 * It is called every समय an directory entry node is found.
 *
 * Returns: 0 on success;
 * 	    negative error code on failure.
 */
अटल अंतरभूत पूर्णांक पढ़ो_direntry(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_raw_node_ref *ref,
				काष्ठा jffs2_raw_dirent *rd, माप_प्रकार पढ़ो,
				काष्ठा jffs2_पढ़ोinode_info *rii)
अणु
	काष्ठा jffs2_full_dirent *fd;
	uपूर्णांक32_t crc;

	/* Obsoleted. This cannot happen, surely? dwmw2 20020308 */
	BUG_ON(ref_obsolete(ref));

	crc = crc32(0, rd, माप(*rd) - 8);
	अगर (unlikely(crc != je32_to_cpu(rd->node_crc))) अणु
		JFFS2_NOTICE("header CRC failed on dirent node at %#08x: read %#08x, calculated %#08x\n",
			     ref_offset(ref), je32_to_cpu(rd->node_crc), crc);
		jffs2_mark_node_obsolete(c, ref);
		वापस 0;
	पूर्ण

	/* If we've never checked the CRCs on this node, check them now */
	अगर (ref_flags(ref) == REF_UNCHECKED) अणु
		काष्ठा jffs2_eraseblock *jeb;
		पूर्णांक len;

		/* Sanity check */
		अगर (unlikely(PAD((rd->nsize + माप(*rd))) != PAD(je32_to_cpu(rd->totlen)))) अणु
			JFFS2_ERROR("illegal nsize in node at %#08x: nsize %#02x, totlen %#04x\n",
				    ref_offset(ref), rd->nsize, je32_to_cpu(rd->totlen));
			jffs2_mark_node_obsolete(c, ref);
			वापस 0;
		पूर्ण

		jeb = &c->blocks[ref->flash_offset / c->sector_size];
		len = ref_totlen(c, jeb, ref);

		spin_lock(&c->erase_completion_lock);
		jeb->used_size += len;
		jeb->unchecked_size -= len;
		c->used_size += len;
		c->unchecked_size -= len;
		ref->flash_offset = ref_offset(ref) | dirent_node_state(rd);
		spin_unlock(&c->erase_completion_lock);
	पूर्ण

	fd = jffs2_alloc_full_dirent(rd->nsize + 1);
	अगर (unlikely(!fd))
		वापस -ENOMEM;

	fd->raw = ref;
	fd->version = je32_to_cpu(rd->version);
	fd->ino = je32_to_cpu(rd->ino);
	fd->type = rd->type;

	अगर (fd->version > rii->highest_version)
		rii->highest_version = fd->version;

	/* Pick out the mस_समय of the latest dirent */
	अगर(fd->version > rii->mस_समय_ver && je32_to_cpu(rd->mस_समय)) अणु
		rii->mस_समय_ver = fd->version;
		rii->latest_mस_समय = je32_to_cpu(rd->mस_समय);
	पूर्ण

	/*
	 * Copy as much of the name as possible from the raw
	 * dirent we've alपढ़ोy पढ़ो from the flash.
	 */
	अगर (पढ़ो > माप(*rd))
		स_नकल(&fd->name[0], &rd->name[0],
		       min_t(uपूर्णांक32_t, rd->nsize, (पढ़ो - माप(*rd)) ));

	/* Do we need to copy any more of the name directly from the flash? */
	अगर (rd->nsize + माप(*rd) > पढ़ो) अणु
		/* FIXME: poपूर्णांक() */
		पूर्णांक err;
		पूर्णांक alपढ़ोy = पढ़ो - माप(*rd);

		err = jffs2_flash_पढ़ो(c, (ref_offset(ref)) + पढ़ो,
				rd->nsize - alपढ़ोy, &पढ़ो, &fd->name[alपढ़ोy]);
		अगर (unlikely(पढ़ो != rd->nsize - alपढ़ोy) && likely(!err)) अणु
			jffs2_मुक्त_full_dirent(fd);
			JFFS2_ERROR("short read: wanted %d bytes, got %zd\n",
				    rd->nsize - alपढ़ोy, पढ़ो);
			वापस -EIO;
		पूर्ण

		अगर (unlikely(err)) अणु
			JFFS2_ERROR("read remainder of name: error %d\n", err);
			jffs2_मुक्त_full_dirent(fd);
			वापस -EIO;
		पूर्ण

#अगर_घोषित CONFIG_JFFS2_SUMMARY
		/*
		 * we use CONFIG_JFFS2_SUMMARY because without it, we
		 * have checked it जबतक mounting
		 */
		crc = crc32(0, fd->name, rd->nsize);
		अगर (unlikely(crc != je32_to_cpu(rd->name_crc))) अणु
			JFFS2_NOTICE("name CRC failed on dirent node at"
			   "%#08x: read %#08x,calculated %#08x\n",
			   ref_offset(ref), je32_to_cpu(rd->node_crc), crc);
			jffs2_mark_node_obsolete(c, ref);
			jffs2_मुक्त_full_dirent(fd);
			वापस 0;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	fd->nhash = full_name_hash(शून्य, fd->name, rd->nsize);
	fd->next = शून्य;
	fd->name[rd->nsize] = '\0';

	/*
	 * Wheee. We now have a complete jffs2_full_dirent काष्ठाure, with
	 * the name in it and everything. Link it पूर्णांकo the list
	 */
	jffs2_add_fd_to_list(c, fd, &rii->fds);

	वापस 0;
पूर्ण

/*
 * Helper function क्रम jffs2_get_inode_nodes().
 * It is called every समय an inode node is found.
 *
 * Returns: 0 on success (possibly after marking a bad node obsolete);
 * 	    negative error code on failure.
 */
अटल अंतरभूत पूर्णांक पढ़ो_dnode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_raw_node_ref *ref,
			     काष्ठा jffs2_raw_inode *rd, पूर्णांक rdlen,
			     काष्ठा jffs2_पढ़ोinode_info *rii)
अणु
	काष्ठा jffs2_पंचांगp_dnode_info *tn;
	uपूर्णांक32_t len, csize;
	पूर्णांक ret = 0;
	uपूर्णांक32_t crc;

	/* Obsoleted. This cannot happen, surely? dwmw2 20020308 */
	BUG_ON(ref_obsolete(ref));

	crc = crc32(0, rd, माप(*rd) - 8);
	अगर (unlikely(crc != je32_to_cpu(rd->node_crc))) अणु
		JFFS2_NOTICE("node CRC failed on dnode at %#08x: read %#08x, calculated %#08x\n",
			     ref_offset(ref), je32_to_cpu(rd->node_crc), crc);
		jffs2_mark_node_obsolete(c, ref);
		वापस 0;
	पूर्ण

	tn = jffs2_alloc_पंचांगp_dnode_info();
	अगर (!tn) अणु
		JFFS2_ERROR("failed to allocate tn (%zu bytes).\n", माप(*tn));
		वापस -ENOMEM;
	पूर्ण

	tn->partial_crc = 0;
	csize = je32_to_cpu(rd->csize);

	/* If we've never checked the CRCs on this node, check them now */
	अगर (ref_flags(ref) == REF_UNCHECKED) अणु

		/* Sanity checks */
		अगर (unlikely(je32_to_cpu(rd->offset) > je32_to_cpu(rd->isize)) ||
		    unlikely(PAD(je32_to_cpu(rd->csize) + माप(*rd)) != PAD(je32_to_cpu(rd->totlen)))) अणु
			JFFS2_WARNING("inode node header CRC is corrupted at %#08x\n", ref_offset(ref));
			jffs2_dbg_dump_node(c, ref_offset(ref));
			jffs2_mark_node_obsolete(c, ref);
			जाओ मुक्त_out;
		पूर्ण

		अगर (jffs2_is_ग_लिखोbuffered(c) && csize != 0) अणु
			/* At this poपूर्णांक we are supposed to check the data CRC
			 * of our unchecked node. But thus far, we करो not
			 * know whether the node is valid or obsolete. To
			 * figure this out, we need to walk all the nodes of
			 * the inode and build the inode fragtree. We करोn't
			 * want to spend समय checking data of nodes which may
			 * later be found to be obsolete. So we put off the full
			 * data CRC checking until we have पढ़ो all the inode
			 * nodes and have started building the fragtree.
			 *
			 * The fragtree is being built starting with nodes
			 * having the highest version number, so we'll be able
			 * to detect whether a node is valid (i.e., it is not
			 * overlapped by a node with higher version) or not.
			 * And we'll be able to check only those nodes, which
			 * are not obsolete.
			 *
			 * Of course, this optimization only makes sense in हाल
			 * of न_अंकD flashes (or other flashes with
			 * !jffs2_can_mark_obsolete()), since on NOR flashes
			 * nodes are marked obsolete physically.
			 *
			 * Since न_अंकD flashes (or other flashes with
			 * jffs2_is_ग_लिखोbuffered(c)) are anyway पढ़ो by
			 * fractions of c->wbuf_pagesize, and we have just पढ़ो
			 * the node header, it is likely that the starting part
			 * of the node data is also पढ़ो when we पढ़ो the
			 * header. So we करोn't mind to check the CRC of the
			 * starting part of the data of the node now, and check
			 * the second part later (in jffs2_check_node_data()).
			 * Of course, we will not need to re-पढ़ो and re-check
			 * the न_अंकD page which we have just पढ़ो. This is why we
			 * पढ़ो the whole न_अंकD page at jffs2_get_inode_nodes(),
			 * जबतक we needed only the node header.
			 */
			अचिन्हित अक्षर *buf;

			/* 'buf' will poपूर्णांक to the start of data */
			buf = (अचिन्हित अक्षर *)rd + माप(*rd);
			/* len will be the पढ़ो data length */
			len = min_t(uपूर्णांक32_t, rdlen - माप(*rd), csize);
			tn->partial_crc = crc32(0, buf, len);

			dbg_पढ़ोinode("Calculates CRC (%#08x) for %d bytes, csize %d\n", tn->partial_crc, len, csize);

			/* If we actually calculated the whole data CRC
			 * and it is wrong, drop the node. */
			अगर (len >= csize && unlikely(tn->partial_crc != je32_to_cpu(rd->data_crc))) अणु
				JFFS2_NOTICE("wrong data CRC in data node at 0x%08x: read %#08x, calculated %#08x.\n",
					ref_offset(ref), tn->partial_crc, je32_to_cpu(rd->data_crc));
				jffs2_mark_node_obsolete(c, ref);
				जाओ मुक्त_out;
			पूर्ण

		पूर्ण अन्यथा अगर (csize == 0) अणु
			/*
			 * We checked the header CRC. If the node has no data, adjust
			 * the space accounting now. For other nodes this will be करोne
			 * later either when the node is marked obsolete or when its
			 * data is checked.
			 */
			काष्ठा jffs2_eraseblock *jeb;

			dbg_पढ़ोinode("the node has no data.\n");
			jeb = &c->blocks[ref->flash_offset / c->sector_size];
			len = ref_totlen(c, jeb, ref);

			spin_lock(&c->erase_completion_lock);
			jeb->used_size += len;
			jeb->unchecked_size -= len;
			c->used_size += len;
			c->unchecked_size -= len;
			ref->flash_offset = ref_offset(ref) | REF_NORMAL;
			spin_unlock(&c->erase_completion_lock);
		पूर्ण
	पूर्ण

	tn->fn = jffs2_alloc_full_dnode();
	अगर (!tn->fn) अणु
		JFFS2_ERROR("alloc fn failed\n");
		ret = -ENOMEM;
		जाओ मुक्त_out;
	पूर्ण

	tn->version = je32_to_cpu(rd->version);
	tn->fn->ofs = je32_to_cpu(rd->offset);
	tn->data_crc = je32_to_cpu(rd->data_crc);
	tn->csize = csize;
	tn->fn->raw = ref;
	tn->overlapped = 0;

	अगर (tn->version > rii->highest_version)
		rii->highest_version = tn->version;

	/* There was a bug where we wrote hole nodes out with
	   csize/dsize swapped. Deal with it */
	अगर (rd->compr == JFFS2_COMPR_ZERO && !je32_to_cpu(rd->dsize) && csize)
		tn->fn->size = csize;
	अन्यथा // normal हाल...
		tn->fn->size = je32_to_cpu(rd->dsize);

	dbg_पढ़ोinode2("dnode @%08x: ver %u, offset %#04x, dsize %#04x, csize %#04x\n",
		       ref_offset(ref), je32_to_cpu(rd->version),
		       je32_to_cpu(rd->offset), je32_to_cpu(rd->dsize), csize);

	ret = jffs2_add_tn_to_tree(c, rii, tn);

	अगर (ret) अणु
		jffs2_मुक्त_full_dnode(tn->fn);
	मुक्त_out:
		jffs2_मुक्त_पंचांगp_dnode_info(tn);
		वापस ret;
	पूर्ण
#अगर_घोषित JFFS2_DBG_READINODE2_MESSAGES
	dbg_पढ़ोinode2("After adding ver %d:\n", je32_to_cpu(rd->version));
	tn = tn_first(&rii->tn_root);
	जबतक (tn) अणु
		dbg_पढ़ोinode2("%p: v %d r 0x%x-0x%x ov %d\n",
			       tn, tn->version, tn->fn->ofs,
			       tn->fn->ofs+tn->fn->size, tn->overlapped);
		tn = tn_next(tn);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Helper function क्रम jffs2_get_inode_nodes().
 * It is called every समय an unknown node is found.
 *
 * Returns: 0 on success;
 * 	    negative error code on failure.
 */
अटल अंतरभूत पूर्णांक पढ़ो_unknown(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_raw_node_ref *ref, काष्ठा jffs2_unknown_node *un)
अणु
	/* We करोn't mark unknown nodes as REF_UNCHECKED */
	अगर (ref_flags(ref) == REF_UNCHECKED) अणु
		JFFS2_ERROR("REF_UNCHECKED but unknown node at %#08x\n",
			    ref_offset(ref));
		JFFS2_ERROR("Node is {%04x,%04x,%08x,%08x}. Please report this error.\n",
			    je16_to_cpu(un->magic), je16_to_cpu(un->nodetype),
			    je32_to_cpu(un->totlen), je32_to_cpu(un->hdr_crc));
		jffs2_mark_node_obsolete(c, ref);
		वापस 0;
	पूर्ण

	un->nodetype = cpu_to_je16(JFFS2_NODE_ACCURATE | je16_to_cpu(un->nodetype));

	चयन(je16_to_cpu(un->nodetype) & JFFS2_COMPAT_MASK) अणु

	हाल JFFS2_FEATURE_INCOMPAT:
		JFFS2_ERROR("unknown INCOMPAT nodetype %#04X at %#08x\n",
			    je16_to_cpu(un->nodetype), ref_offset(ref));
		/* EEP */
		BUG();
		अवरोध;

	हाल JFFS2_FEATURE_ROCOMPAT:
		JFFS2_ERROR("unknown ROCOMPAT nodetype %#04X at %#08x\n",
			    je16_to_cpu(un->nodetype), ref_offset(ref));
		BUG_ON(!(c->flags & JFFS2_SB_FLAG_RO));
		अवरोध;

	हाल JFFS2_FEATURE_RWCOMPAT_COPY:
		JFFS2_NOTICE("unknown RWCOMPAT_COPY nodetype %#04X at %#08x\n",
			     je16_to_cpu(un->nodetype), ref_offset(ref));
		अवरोध;

	हाल JFFS2_FEATURE_RWCOMPAT_DELETE:
		JFFS2_NOTICE("unknown RWCOMPAT_DELETE nodetype %#04X at %#08x\n",
			     je16_to_cpu(un->nodetype), ref_offset(ref));
		jffs2_mark_node_obsolete(c, ref);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Helper function क्रम jffs2_get_inode_nodes().
 * The function detects whether more data should be पढ़ो and पढ़ोs it अगर yes.
 *
 * Returns: 0 on success;
 * 	    negative error code on failure.
 */
अटल पूर्णांक पढ़ो_more(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_raw_node_ref *ref,
		     पूर्णांक needed_len, पूर्णांक *rdlen, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक err, to_पढ़ो = needed_len - *rdlen;
	माप_प्रकार retlen;
	uपूर्णांक32_t offs;

	अगर (jffs2_is_ग_लिखोbuffered(c)) अणु
		पूर्णांक rem = to_पढ़ो % c->wbuf_pagesize;

		अगर (rem)
			to_पढ़ो += c->wbuf_pagesize - rem;
	पूर्ण

	/* We need to पढ़ो more data */
	offs = ref_offset(ref) + *rdlen;

	dbg_पढ़ोinode("read more %d bytes\n", to_पढ़ो);

	err = jffs2_flash_पढ़ो(c, offs, to_पढ़ो, &retlen, buf + *rdlen);
	अगर (err) अणु
		JFFS2_ERROR("can not read %d bytes from 0x%08x, "
			"error code: %d.\n", to_पढ़ो, offs, err);
		वापस err;
	पूर्ण

	अगर (retlen < to_पढ़ो) अणु
		JFFS2_ERROR("short read at %#08x: %zu instead of %d.\n",
				offs, retlen, to_पढ़ो);
		वापस -EIO;
	पूर्ण

	*rdlen += to_पढ़ो;
	वापस 0;
पूर्ण

/* Get पंचांगp_dnode_info and full_dirent क्रम all non-obsolete nodes associated
   with this ino. Perक्रमm a preliminary ordering on data nodes, throwing away
   those which are completely obsoleted by newer ones. The naथ/ve approach we
   use to take of just वापसing them _all_ in version order will cause us to
   run out of memory in certain degenerate हालs. */
अटल पूर्णांक jffs2_get_inode_nodes(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
				 काष्ठा jffs2_पढ़ोinode_info *rii)
अणु
	काष्ठा jffs2_raw_node_ref *ref, *valid_ref;
	अचिन्हित अक्षर *buf = शून्य;
	जोड़ jffs2_node_जोड़ *node;
	माप_प्रकार retlen;
	पूर्णांक len, err;

	rii->mस_समय_ver = 0;

	dbg_पढ़ोinode("ino #%u\n", f->inocache->ino);

	/* FIXME: in हाल of NOR and available ->poपूर्णांक() this
	 * needs to be fixed. */
	len = माप(जोड़ jffs2_node_जोड़) + c->wbuf_pagesize;
	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	spin_lock(&c->erase_completion_lock);
	valid_ref = jffs2_first_valid_node(f->inocache->nodes);
	अगर (!valid_ref && f->inocache->ino != 1)
		JFFS2_WARNING("Eep. No valid nodes for ino #%u.\n", f->inocache->ino);
	जबतक (valid_ref) अणु
		/* We can hold a poपूर्णांकer to a non-obsolete node without the spinlock,
		   but _obsolete_ nodes may disappear at any समय, अगर the block
		   they're in gets erased. So if we mark 'ref' obsolete while we're
		   not holding the lock, it can go away immediately. For that reason,
		   we find the next valid node first, beक्रमe processing 'ref'.
		*/
		ref = valid_ref;
		valid_ref = jffs2_first_valid_node(ref->next_in_ino);
		spin_unlock(&c->erase_completion_lock);

		cond_resched();

		/*
		 * At this poपूर्णांक we करोn't know the type of the node we're going
		 * to पढ़ो, so we करो not know the size of its header. In order
		 * to minimize the amount of flash IO we assume the header is
		 * of size = JFFS2_MIN_NODE_HEADER.
		 */
		len = JFFS2_MIN_NODE_HEADER;
		अगर (jffs2_is_ग_लिखोbuffered(c)) अणु
			पूर्णांक end, rem;

			/*
			 * We are about to पढ़ो JFFS2_MIN_NODE_HEADER bytes,
			 * but this flash has some minimal I/O unit. It is
			 * possible that we'll need to पढ़ो more soon, so पढ़ो
			 * up to the next min. I/O unit, in order not to
			 * re-पढ़ो the same min. I/O unit twice.
			 */
			end = ref_offset(ref) + len;
			rem = end % c->wbuf_pagesize;
			अगर (rem)
				end += c->wbuf_pagesize - rem;
			len = end - ref_offset(ref);
		पूर्ण

		dbg_पढ़ोinode("read %d bytes at %#08x(%d).\n", len, ref_offset(ref), ref_flags(ref));

		/* FIXME: poपूर्णांक() */
		err = jffs2_flash_पढ़ो(c, ref_offset(ref), len, &retlen, buf);
		अगर (err) अणु
			JFFS2_ERROR("can not read %d bytes from 0x%08x, error code: %d.\n", len, ref_offset(ref), err);
			जाओ मुक्त_out;
		पूर्ण

		अगर (retlen < len) अणु
			JFFS2_ERROR("short read at %#08x: %zu instead of %d.\n", ref_offset(ref), retlen, len);
			err = -EIO;
			जाओ मुक्त_out;
		पूर्ण

		node = (जोड़ jffs2_node_जोड़ *)buf;

		/* No need to mask in the valid bit; it shouldn't be invalid */
		अगर (je32_to_cpu(node->u.hdr_crc) != crc32(0, node, माप(node->u)-4)) अणु
			JFFS2_NOTICE("Node header CRC failed at %#08x. {%04x,%04x,%08x,%08x}\n",
				     ref_offset(ref), je16_to_cpu(node->u.magic),
				     je16_to_cpu(node->u.nodetype),
				     je32_to_cpu(node->u.totlen),
				     je32_to_cpu(node->u.hdr_crc));
			jffs2_dbg_dump_node(c, ref_offset(ref));
			jffs2_mark_node_obsolete(c, ref);
			जाओ cont;
		पूर्ण
		अगर (je16_to_cpu(node->u.magic) != JFFS2_MAGIC_BITMASK) अणु
			/* Not a JFFS2 node, whinge and move on */
			JFFS2_NOTICE("Wrong magic bitmask 0x%04x in node header at %#08x.\n",
				     je16_to_cpu(node->u.magic), ref_offset(ref));
			jffs2_mark_node_obsolete(c, ref);
			जाओ cont;
		पूर्ण

		चयन (je16_to_cpu(node->u.nodetype)) अणु

		हाल JFFS2_NODETYPE_सूचीENT:

			अगर (JFFS2_MIN_NODE_HEADER < माप(काष्ठा jffs2_raw_dirent) &&
			    len < माप(काष्ठा jffs2_raw_dirent)) अणु
				err = पढ़ो_more(c, ref, माप(काष्ठा jffs2_raw_dirent), &len, buf);
				अगर (unlikely(err))
					जाओ मुक्त_out;
			पूर्ण

			err = पढ़ो_direntry(c, ref, &node->d, retlen, rii);
			अगर (unlikely(err))
				जाओ मुक्त_out;

			अवरोध;

		हाल JFFS2_NODETYPE_INODE:

			अगर (JFFS2_MIN_NODE_HEADER < माप(काष्ठा jffs2_raw_inode) &&
			    len < माप(काष्ठा jffs2_raw_inode)) अणु
				err = पढ़ो_more(c, ref, माप(काष्ठा jffs2_raw_inode), &len, buf);
				अगर (unlikely(err))
					जाओ मुक्त_out;
			पूर्ण

			err = पढ़ो_dnode(c, ref, &node->i, len, rii);
			अगर (unlikely(err))
				जाओ मुक्त_out;

			अवरोध;

		शेष:
			अगर (JFFS2_MIN_NODE_HEADER < माप(काष्ठा jffs2_unknown_node) &&
			    len < माप(काष्ठा jffs2_unknown_node)) अणु
				err = पढ़ो_more(c, ref, माप(काष्ठा jffs2_unknown_node), &len, buf);
				अगर (unlikely(err))
					जाओ मुक्त_out;
			पूर्ण

			err = पढ़ो_unknown(c, ref, &node->u);
			अगर (unlikely(err))
				जाओ मुक्त_out;

		पूर्ण
	cont:
		spin_lock(&c->erase_completion_lock);
	पूर्ण

	spin_unlock(&c->erase_completion_lock);
	kमुक्त(buf);

	f->highest_version = rii->highest_version;

	dbg_पढ़ोinode("nodes of inode #%u were read, the highest version is %u, latest_mctime %u, mctime_ver %u.\n",
		      f->inocache->ino, rii->highest_version, rii->latest_mस_समय,
		      rii->mस_समय_ver);
	वापस 0;

 मुक्त_out:
	jffs2_मुक्त_पंचांगp_dnode_info_list(&rii->tn_root);
	jffs2_मुक्त_full_dirent_list(rii->fds);
	rii->fds = शून्य;
	kमुक्त(buf);
	वापस err;
पूर्ण

अटल पूर्णांक jffs2_करो_पढ़ो_inode_पूर्णांकernal(काष्ठा jffs2_sb_info *c,
					काष्ठा jffs2_inode_info *f,
					काष्ठा jffs2_raw_inode *latest_node)
अणु
	काष्ठा jffs2_पढ़ोinode_info rii;
	uपूर्णांक32_t crc, new_size;
	माप_प्रकार retlen;
	पूर्णांक ret;

	dbg_पढ़ोinode("ino #%u pino/nlink is %d\n", f->inocache->ino,
		      f->inocache->pino_nlink);

	स_रखो(&rii, 0, माप(rii));

	/* Grab all nodes relevant to this ino */
	ret = jffs2_get_inode_nodes(c, f, &rii);

	अगर (ret) अणु
		JFFS2_ERROR("cannot read nodes for ino %u, returned error is %d\n", f->inocache->ino, ret);
		अगर (f->inocache->state == INO_STATE_READING)
			jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
		वापस ret;
	पूर्ण

	ret = jffs2_build_inode_fragtree(c, f, &rii);
	अगर (ret) अणु
		JFFS2_ERROR("Failed to build final fragtree for inode #%u: error %d\n",
			    f->inocache->ino, ret);
		अगर (f->inocache->state == INO_STATE_READING)
			jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
		jffs2_मुक्त_पंचांगp_dnode_info_list(&rii.tn_root);
		/* FIXME: We could at least crc-check them all */
		अगर (rii.mdata_tn) अणु
			jffs2_मुक्त_full_dnode(rii.mdata_tn->fn);
			jffs2_मुक्त_पंचांगp_dnode_info(rii.mdata_tn);
			rii.mdata_tn = शून्य;
		पूर्ण
		वापस ret;
	पूर्ण

	अगर (rii.mdata_tn) अणु
		अगर (rii.mdata_tn->fn->raw == rii.latest_ref) अणु
			f->metadata = rii.mdata_tn->fn;
			jffs2_मुक्त_पंचांगp_dnode_info(rii.mdata_tn);
		पूर्ण अन्यथा अणु
			jffs2_समाप्त_tn(c, rii.mdata_tn);
		पूर्ण
		rii.mdata_tn = शून्य;
	पूर्ण

	f->dents = rii.fds;

	jffs2_dbg_fragtree_paranoia_check_nolock(f);

	अगर (unlikely(!rii.latest_ref)) अणु
		/* No data nodes क्रम this inode. */
		अगर (f->inocache->ino != 1) अणु
			JFFS2_WARNING("no data nodes found for ino #%u\n", f->inocache->ino);
			अगर (!rii.fds) अणु
				अगर (f->inocache->state == INO_STATE_READING)
					jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
				वापस -EIO;
			पूर्ण
			JFFS2_NOTICE("but it has children so we fake some modes for it\n");
		पूर्ण
		latest_node->mode = cpu_to_jemode(S_IFसूची|S_IRUGO|S_IWUSR|S_IXUGO);
		latest_node->version = cpu_to_je32(0);
		latest_node->aसमय = latest_node->स_समय = latest_node->mसमय = cpu_to_je32(0);
		latest_node->isize = cpu_to_je32(0);
		latest_node->gid = cpu_to_je16(0);
		latest_node->uid = cpu_to_je16(0);
		अगर (f->inocache->state == INO_STATE_READING)
			jffs2_set_inocache_state(c, f->inocache, INO_STATE_PRESENT);
		वापस 0;
	पूर्ण

	ret = jffs2_flash_पढ़ो(c, ref_offset(rii.latest_ref), माप(*latest_node), &retlen, (व्योम *)latest_node);
	अगर (ret || retlen != माप(*latest_node)) अणु
		JFFS2_ERROR("failed to read from flash: error %d, %zd of %zd bytes read\n",
			ret, retlen, माप(*latest_node));
		/* FIXME: If this fails, there seems to be a memory leak. Find it. */
		वापस ret ? ret : -EIO;
	पूर्ण

	crc = crc32(0, latest_node, माप(*latest_node)-8);
	अगर (crc != je32_to_cpu(latest_node->node_crc)) अणु
		JFFS2_ERROR("CRC failed for read_inode of inode %u at physical location 0x%x\n",
			f->inocache->ino, ref_offset(rii.latest_ref));
		वापस -EIO;
	पूर्ण

	चयन(jemode_to_cpu(latest_node->mode) & S_IFMT) अणु
	हाल S_IFसूची:
		अगर (rii.mस_समय_ver > je32_to_cpu(latest_node->version)) अणु
			/* The बार in the latest_node are actually older than
			   mस_समय in the latest dirent. Cheat. */
			latest_node->स_समय = latest_node->mसमय = cpu_to_je32(rii.latest_mस_समय);
		पूर्ण
		अवरोध;


	हाल S_IFREG:
		/* If it was a regular file, truncate it to the latest node's isize */
		new_size = jffs2_truncate_fragtree(c, &f->fragtree, je32_to_cpu(latest_node->isize));
		अगर (new_size != je32_to_cpu(latest_node->isize)) अणु
			JFFS2_WARNING("Truncating ino #%u to %d bytes failed because it only had %d bytes to start with!\n",
				      f->inocache->ino, je32_to_cpu(latest_node->isize), new_size);
			latest_node->isize = cpu_to_je32(new_size);
		पूर्ण
		अवरोध;

	हाल S_IFLNK:
		/* Hack to work around broken isize in old symlink code.
		   Remove this when dwmw2 comes to his senses and stops
		   symlinks from being an entirely gratuitous special
		   हाल. */
		अगर (!je32_to_cpu(latest_node->isize))
			latest_node->isize = latest_node->dsize;

		अगर (f->inocache->state != INO_STATE_CHECKING) अणु
			/* Symlink's inode data is the target path. Read it and
			 * keep in RAM to facilitate quick follow symlink
			 * operation. */
			uपूर्णांक32_t csize = je32_to_cpu(latest_node->csize);
			अगर (csize > JFFS2_MAX_NAME_LEN)
				वापस -ENAMETOOLONG;
			f->target = kदो_स्मृति(csize + 1, GFP_KERNEL);
			अगर (!f->target) अणु
				JFFS2_ERROR("can't allocate %u bytes of memory for the symlink target path cache\n", csize);
				वापस -ENOMEM;
			पूर्ण

			ret = jffs2_flash_पढ़ो(c, ref_offset(rii.latest_ref) + माप(*latest_node),
					       csize, &retlen, (अक्षर *)f->target);

			अगर (ret || retlen != csize) अणु
				अगर (retlen != csize)
					ret = -EIO;
				kमुक्त(f->target);
				f->target = शून्य;
				वापस ret;
			पूर्ण

			f->target[csize] = '\0';
			dbg_पढ़ोinode("symlink's target '%s' cached\n", f->target);
		पूर्ण

		fallthrough;

	हाल S_IFBLK:
	हाल S_IFCHR:
		/* Certain inode types should have only one data node, and it's
		   kept as the metadata node */
		अगर (f->metadata) अणु
			JFFS2_ERROR("Argh. Special inode #%u with mode 0%o had metadata node\n",
			       f->inocache->ino, jemode_to_cpu(latest_node->mode));
			वापस -EIO;
		पूर्ण
		अगर (!frag_first(&f->fragtree)) अणु
			JFFS2_ERROR("Argh. Special inode #%u with mode 0%o has no fragments\n",
			       f->inocache->ino, jemode_to_cpu(latest_node->mode));
			वापस -EIO;
		पूर्ण
		/* ASSERT: f->fraglist != शून्य */
		अगर (frag_next(frag_first(&f->fragtree))) अणु
			JFFS2_ERROR("Argh. Special inode #%u with mode 0x%x had more than one node\n",
			       f->inocache->ino, jemode_to_cpu(latest_node->mode));
			/* FIXME: Deal with it - check crc32, check क्रम duplicate node, check बार and discard the older one */
			वापस -EIO;
		पूर्ण
		/* OK. We're happy */
		f->metadata = frag_first(&f->fragtree)->node;
		jffs2_मुक्त_node_frag(frag_first(&f->fragtree));
		f->fragtree = RB_ROOT;
		अवरोध;
	पूर्ण
	अगर (f->inocache->state == INO_STATE_READING)
		jffs2_set_inocache_state(c, f->inocache, INO_STATE_PRESENT);

	वापस 0;
पूर्ण

/* Scan the list of all nodes present क्रम this ino, build map of versions, etc. */
पूर्णांक jffs2_करो_पढ़ो_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
			uपूर्णांक32_t ino, काष्ठा jffs2_raw_inode *latest_node)
अणु
	dbg_पढ़ोinode("read inode #%u\n", ino);

 retry_inocache:
	spin_lock(&c->inocache_lock);
	f->inocache = jffs2_get_ino_cache(c, ino);

	अगर (f->inocache) अणु
		/* Check its state. We may need to रुको beक्रमe we can use it */
		चयन(f->inocache->state) अणु
		हाल INO_STATE_UNCHECKED:
		हाल INO_STATE_CHECKEDABSENT:
			f->inocache->state = INO_STATE_READING;
			अवरोध;

		हाल INO_STATE_CHECKING:
		हाल INO_STATE_GC:
			/* If it's in either of these states, we need
			   to रुको क्रम whoever's got it to finish and
			   put it back. */
			dbg_पढ़ोinode("waiting for ino #%u in state %d\n", ino, f->inocache->state);
			sleep_on_spinunlock(&c->inocache_wq, &c->inocache_lock);
			जाओ retry_inocache;

		हाल INO_STATE_READING:
		हाल INO_STATE_PRESENT:
			/* Eep. This should never happen. It can
			happen अगर Linux calls पढ़ो_inode() again
			beक्रमe clear_inode() has finished though. */
			JFFS2_ERROR("Eep. Trying to read_inode #%u when it's already in state %d!\n", ino, f->inocache->state);
			/* Fail. That's probably better than allowing it to succeed */
			f->inocache = शून्य;
			अवरोध;

		शेष:
			BUG();
		पूर्ण
	पूर्ण
	spin_unlock(&c->inocache_lock);

	अगर (!f->inocache && ino == 1) अणु
		/* Special हाल - no root inode on medium */
		f->inocache = jffs2_alloc_inode_cache();
		अगर (!f->inocache) अणु
			JFFS2_ERROR("cannot allocate inocache for root inode\n");
			वापस -ENOMEM;
		पूर्ण
		dbg_पढ़ोinode("creating inocache for root inode\n");
		स_रखो(f->inocache, 0, माप(काष्ठा jffs2_inode_cache));
		f->inocache->ino = f->inocache->pino_nlink = 1;
		f->inocache->nodes = (काष्ठा jffs2_raw_node_ref *)f->inocache;
		f->inocache->state = INO_STATE_READING;
		jffs2_add_ino_cache(c, f->inocache);
	पूर्ण
	अगर (!f->inocache) अणु
		JFFS2_ERROR("requested to read a nonexistent ino %u\n", ino);
		वापस -ENOENT;
	पूर्ण

	वापस jffs2_करो_पढ़ो_inode_पूर्णांकernal(c, f, latest_node);
पूर्ण

पूर्णांक jffs2_करो_crccheck_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *ic)
अणु
	काष्ठा jffs2_raw_inode n;
	काष्ठा jffs2_inode_info *f = kzalloc(माप(*f), GFP_KERNEL);
	पूर्णांक ret;

	अगर (!f)
		वापस -ENOMEM;

	mutex_init(&f->sem);
	mutex_lock(&f->sem);
	f->inocache = ic;

	ret = jffs2_करो_पढ़ो_inode_पूर्णांकernal(c, f, &n);
	mutex_unlock(&f->sem);
	jffs2_करो_clear_inode(c, f);
	jffs2_xattr_करो_crccheck_inode(c, ic);
	kमुक्त (f);
	वापस ret;
पूर्ण

व्योम jffs2_करो_clear_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f)
अणु
	काष्ठा jffs2_full_dirent *fd, *fds;
	पूर्णांक deleted;

	jffs2_xattr_delete_inode(c, f->inocache);
	mutex_lock(&f->sem);
	deleted = f->inocache && !f->inocache->pino_nlink;

	अगर (f->inocache && f->inocache->state != INO_STATE_CHECKING)
		jffs2_set_inocache_state(c, f->inocache, INO_STATE_CLEARING);

	अगर (f->metadata) अणु
		अगर (deleted)
			jffs2_mark_node_obsolete(c, f->metadata->raw);
		jffs2_मुक्त_full_dnode(f->metadata);
	पूर्ण

	jffs2_समाप्त_fragtree(&f->fragtree, deleted?c:शून्य);

	fds = f->dents;
	जबतक(fds) अणु
		fd = fds;
		fds = fd->next;
		jffs2_मुक्त_full_dirent(fd);
	पूर्ण

	अगर (f->inocache && f->inocache->state != INO_STATE_CHECKING) अणु
		jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
		अगर (f->inocache->nodes == (व्योम *)f->inocache)
			jffs2_del_ino_cache(c, f->inocache);
	पूर्ण

	mutex_unlock(&f->sem);
पूर्ण
