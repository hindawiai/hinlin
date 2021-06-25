<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of UBIFS.
 *
 * Copyright (C) 2006-2008 Nokia Corporation.
 *
 * Author: Adrian Hunter
 */

#समावेश "ubifs.h"

/*
 * An orphan is an inode number whose inode node has been committed to the index
 * with a link count of zero. That happens when an खोलो file is deleted
 * (unlinked) and then a commit is run. In the normal course of events the inode
 * would be deleted when the file is बंदd. However in the हाल of an unclean
 * unmount, orphans need to be accounted क्रम. After an unclean unmount, the
 * orphans' inodes must be deleted which means either scanning the entire index
 * looking क्रम them, or keeping a list on flash somewhere. This unit implements
 * the latter approach.
 *
 * The orphan area is a fixed number of LEBs situated between the LPT area and
 * the मुख्य area. The number of orphan area LEBs is specअगरied when the file
 * प्रणाली is created. The minimum number is 1. The size of the orphan area
 * should be so that it can hold the maximum number of orphans that are expected
 * to ever exist at one समय.
 *
 * The number of orphans that can fit in a LEB is:
 *
 *         (c->leb_size - UBIFS_ORPH_NODE_SZ) / माप(__le64)
 *
 * For example: a 15872 byte LEB can fit 1980 orphans so 1 LEB may be enough.
 *
 * Orphans are accumulated in a rb-tree. When an inode's link count drops to
 * zero, the inode number is added to the rb-tree. It is हटाओd from the tree
 * when the inode is deleted.  Any new orphans that are in the orphan tree when
 * the commit is run, are written to the orphan area in 1 or more orphan nodes.
 * If the orphan area is full, it is consolidated to make space.  There is
 * always enough space because validation prevents the user from creating more
 * than the maximum number of orphans allowed.
 */

अटल पूर्णांक dbg_check_orphans(काष्ठा ubअगरs_info *c);

अटल काष्ठा ubअगरs_orphan *orphan_add(काष्ठा ubअगरs_info *c, ino_t inum,
				       काष्ठा ubअगरs_orphan *parent_orphan)
अणु
	काष्ठा ubअगरs_orphan *orphan, *o;
	काष्ठा rb_node **p, *parent = शून्य;

	orphan = kzalloc(माप(काष्ठा ubअगरs_orphan), GFP_NOFS);
	अगर (!orphan)
		वापस ERR_PTR(-ENOMEM);
	orphan->inum = inum;
	orphan->new = 1;
	INIT_LIST_HEAD(&orphan->child_list);

	spin_lock(&c->orphan_lock);
	अगर (c->tot_orphans >= c->max_orphans) अणु
		spin_unlock(&c->orphan_lock);
		kमुक्त(orphan);
		वापस ERR_PTR(-ENखाता);
	पूर्ण
	p = &c->orph_tree.rb_node;
	जबतक (*p) अणु
		parent = *p;
		o = rb_entry(parent, काष्ठा ubअगरs_orphan, rb);
		अगर (inum < o->inum)
			p = &(*p)->rb_left;
		अन्यथा अगर (inum > o->inum)
			p = &(*p)->rb_right;
		अन्यथा अणु
			ubअगरs_err(c, "orphaned twice");
			spin_unlock(&c->orphan_lock);
			kमुक्त(orphan);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण
	c->tot_orphans += 1;
	c->new_orphans += 1;
	rb_link_node(&orphan->rb, parent, p);
	rb_insert_color(&orphan->rb, &c->orph_tree);
	list_add_tail(&orphan->list, &c->orph_list);
	list_add_tail(&orphan->new_list, &c->orph_new);

	अगर (parent_orphan) अणु
		list_add_tail(&orphan->child_list,
			      &parent_orphan->child_list);
	पूर्ण

	spin_unlock(&c->orphan_lock);
	dbg_gen("ino %lu", (अचिन्हित दीर्घ)inum);
	वापस orphan;
पूर्ण

अटल काष्ठा ubअगरs_orphan *lookup_orphan(काष्ठा ubअगरs_info *c, ino_t inum)
अणु
	काष्ठा ubअगरs_orphan *o;
	काष्ठा rb_node *p;

	p = c->orph_tree.rb_node;
	जबतक (p) अणु
		o = rb_entry(p, काष्ठा ubअगरs_orphan, rb);
		अगर (inum < o->inum)
			p = p->rb_left;
		अन्यथा अगर (inum > o->inum)
			p = p->rb_right;
		अन्यथा अणु
			वापस o;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम __orphan_drop(काष्ठा ubअगरs_info *c, काष्ठा ubअगरs_orphan *o)
अणु
	rb_erase(&o->rb, &c->orph_tree);
	list_del(&o->list);
	c->tot_orphans -= 1;

	अगर (o->new) अणु
		list_del(&o->new_list);
		c->new_orphans -= 1;
	पूर्ण

	kमुक्त(o);
पूर्ण

अटल व्योम orphan_delete(काष्ठा ubअगरs_info *c, काष्ठा ubअगरs_orphan *orph)
अणु
	अगर (orph->del) अणु
		dbg_gen("deleted twice ino %lu", (अचिन्हित दीर्घ)orph->inum);
		वापस;
	पूर्ण

	अगर (orph->cmt) अणु
		orph->del = 1;
		orph->dnext = c->orph_dnext;
		c->orph_dnext = orph;
		dbg_gen("delete later ino %lu", (अचिन्हित दीर्घ)orph->inum);
		वापस;
	पूर्ण

	__orphan_drop(c, orph);
पूर्ण

/**
 * ubअगरs_add_orphan - add an orphan.
 * @c: UBIFS file-प्रणाली description object
 * @inum: orphan inode number
 *
 * Add an orphan. This function is called when an inodes link count drops to
 * zero.
 */
पूर्णांक ubअगरs_add_orphan(काष्ठा ubअगरs_info *c, ino_t inum)
अणु
	पूर्णांक err = 0;
	ino_t xattr_inum;
	जोड़ ubअगरs_key key;
	काष्ठा ubअगरs_dent_node *xent, *pxent = शून्य;
	काष्ठा fscrypt_name nm = अणु0पूर्ण;
	काष्ठा ubअगरs_orphan *xattr_orphan;
	काष्ठा ubअगरs_orphan *orphan;

	orphan = orphan_add(c, inum, शून्य);
	अगर (IS_ERR(orphan))
		वापस PTR_ERR(orphan);

	lowest_xent_key(c, &key, inum);
	जबतक (1) अणु
		xent = ubअगरs_tnc_next_ent(c, &key, &nm);
		अगर (IS_ERR(xent)) अणु
			err = PTR_ERR(xent);
			अगर (err == -ENOENT)
				अवरोध;
			kमुक्त(pxent);
			वापस err;
		पूर्ण

		fname_name(&nm) = xent->name;
		fname_len(&nm) = le16_to_cpu(xent->nlen);
		xattr_inum = le64_to_cpu(xent->inum);

		xattr_orphan = orphan_add(c, xattr_inum, orphan);
		अगर (IS_ERR(xattr_orphan)) अणु
			kमुक्त(pxent);
			kमुक्त(xent);
			वापस PTR_ERR(xattr_orphan);
		पूर्ण

		kमुक्त(pxent);
		pxent = xent;
		key_पढ़ो(c, &xent->key, &key);
	पूर्ण
	kमुक्त(pxent);

	वापस 0;
पूर्ण

/**
 * ubअगरs_delete_orphan - delete an orphan.
 * @c: UBIFS file-प्रणाली description object
 * @inum: orphan inode number
 *
 * Delete an orphan. This function is called when an inode is deleted.
 */
व्योम ubअगरs_delete_orphan(काष्ठा ubअगरs_info *c, ino_t inum)
अणु
	काष्ठा ubअगरs_orphan *orph, *child_orph, *पंचांगp_o;

	spin_lock(&c->orphan_lock);

	orph = lookup_orphan(c, inum);
	अगर (!orph) अणु
		spin_unlock(&c->orphan_lock);
		ubअगरs_err(c, "missing orphan ino %lu", (अचिन्हित दीर्घ)inum);
		dump_stack();

		वापस;
	पूर्ण

	list_क्रम_each_entry_safe(child_orph, पंचांगp_o, &orph->child_list, child_list) अणु
		list_del(&child_orph->child_list);
		orphan_delete(c, child_orph);
	पूर्ण
	
	orphan_delete(c, orph);

	spin_unlock(&c->orphan_lock);
पूर्ण

/**
 * ubअगरs_orphan_start_commit - start commit of orphans.
 * @c: UBIFS file-प्रणाली description object
 *
 * Start commit of orphans.
 */
पूर्णांक ubअगरs_orphan_start_commit(काष्ठा ubअगरs_info *c)
अणु
	काष्ठा ubअगरs_orphan *orphan, **last;

	spin_lock(&c->orphan_lock);
	last = &c->orph_cnext;
	list_क्रम_each_entry(orphan, &c->orph_new, new_list) अणु
		ubअगरs_निश्चित(c, orphan->new);
		ubअगरs_निश्चित(c, !orphan->cmt);
		orphan->new = 0;
		orphan->cmt = 1;
		*last = orphan;
		last = &orphan->cnext;
	पूर्ण
	*last = शून्य;
	c->cmt_orphans = c->new_orphans;
	c->new_orphans = 0;
	dbg_cmt("%d orphans to commit", c->cmt_orphans);
	INIT_LIST_HEAD(&c->orph_new);
	अगर (c->tot_orphans == 0)
		c->no_orphs = 1;
	अन्यथा
		c->no_orphs = 0;
	spin_unlock(&c->orphan_lock);
	वापस 0;
पूर्ण

/**
 * avail_orphs - calculate available space.
 * @c: UBIFS file-प्रणाली description object
 *
 * This function वापसs the number of orphans that can be written in the
 * available space.
 */
अटल पूर्णांक avail_orphs(काष्ठा ubअगरs_info *c)
अणु
	पूर्णांक avail_lebs, avail, gap;

	avail_lebs = c->orph_lebs - (c->ohead_lnum - c->orph_first) - 1;
	avail = avail_lebs *
	       ((c->leb_size - UBIFS_ORPH_NODE_SZ) / माप(__le64));
	gap = c->leb_size - c->ohead_offs;
	अगर (gap >= UBIFS_ORPH_NODE_SZ + माप(__le64))
		avail += (gap - UBIFS_ORPH_NODE_SZ) / माप(__le64);
	वापस avail;
पूर्ण

/**
 * tot_avail_orphs - calculate total space.
 * @c: UBIFS file-प्रणाली description object
 *
 * This function वापसs the number of orphans that can be written in half
 * the total space. That leaves half the space क्रम adding new orphans.
 */
अटल पूर्णांक tot_avail_orphs(काष्ठा ubअगरs_info *c)
अणु
	पूर्णांक avail_lebs, avail;

	avail_lebs = c->orph_lebs;
	avail = avail_lebs *
	       ((c->leb_size - UBIFS_ORPH_NODE_SZ) / माप(__le64));
	वापस avail / 2;
पूर्ण

/**
 * करो_ग_लिखो_orph_node - ग_लिखो a node to the orphan head.
 * @c: UBIFS file-प्रणाली description object
 * @len: length of node
 * @atomic: ग_लिखो atomically
 *
 * This function ग_लिखोs a node to the orphan head from the orphan buffer. If
 * %atomic is not zero, then the ग_लिखो is करोne atomically. On success, %0 is
 * वापसed, otherwise a negative error code is वापसed.
 */
अटल पूर्णांक करो_ग_लिखो_orph_node(काष्ठा ubअगरs_info *c, पूर्णांक len, पूर्णांक atomic)
अणु
	पूर्णांक err = 0;

	अगर (atomic) अणु
		ubअगरs_निश्चित(c, c->ohead_offs == 0);
		ubअगरs_prepare_node(c, c->orph_buf, len, 1);
		len = ALIGN(len, c->min_io_size);
		err = ubअगरs_leb_change(c, c->ohead_lnum, c->orph_buf, len);
	पूर्ण अन्यथा अणु
		अगर (c->ohead_offs == 0) अणु
			/* Ensure LEB has been unmapped */
			err = ubअगरs_leb_unmap(c, c->ohead_lnum);
			अगर (err)
				वापस err;
		पूर्ण
		err = ubअगरs_ग_लिखो_node(c, c->orph_buf, len, c->ohead_lnum,
				       c->ohead_offs);
	पूर्ण
	वापस err;
पूर्ण

/**
 * ग_लिखो_orph_node - ग_लिखो an orphan node.
 * @c: UBIFS file-प्रणाली description object
 * @atomic: ग_लिखो atomically
 *
 * This function builds an orphan node from the cnext list and ग_लिखोs it to the
 * orphan head. On success, %0 is वापसed, otherwise a negative error code
 * is वापसed.
 */
अटल पूर्णांक ग_लिखो_orph_node(काष्ठा ubअगरs_info *c, पूर्णांक atomic)
अणु
	काष्ठा ubअगरs_orphan *orphan, *cnext;
	काष्ठा ubअगरs_orph_node *orph;
	पूर्णांक gap, err, len, cnt, i;

	ubअगरs_निश्चित(c, c->cmt_orphans > 0);
	gap = c->leb_size - c->ohead_offs;
	अगर (gap < UBIFS_ORPH_NODE_SZ + माप(__le64)) अणु
		c->ohead_lnum += 1;
		c->ohead_offs = 0;
		gap = c->leb_size;
		अगर (c->ohead_lnum > c->orph_last) अणु
			/*
			 * We limit the number of orphans so that this should
			 * never happen.
			 */
			ubअगरs_err(c, "out of space in orphan area");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	cnt = (gap - UBIFS_ORPH_NODE_SZ) / माप(__le64);
	अगर (cnt > c->cmt_orphans)
		cnt = c->cmt_orphans;
	len = UBIFS_ORPH_NODE_SZ + cnt * माप(__le64);
	ubअगरs_निश्चित(c, c->orph_buf);
	orph = c->orph_buf;
	orph->ch.node_type = UBIFS_ORPH_NODE;
	spin_lock(&c->orphan_lock);
	cnext = c->orph_cnext;
	क्रम (i = 0; i < cnt; i++) अणु
		orphan = cnext;
		ubअगरs_निश्चित(c, orphan->cmt);
		orph->inos[i] = cpu_to_le64(orphan->inum);
		orphan->cmt = 0;
		cnext = orphan->cnext;
		orphan->cnext = शून्य;
	पूर्ण
	c->orph_cnext = cnext;
	c->cmt_orphans -= cnt;
	spin_unlock(&c->orphan_lock);
	अगर (c->cmt_orphans)
		orph->cmt_no = cpu_to_le64(c->cmt_no);
	अन्यथा
		/* Mark the last node of the commit */
		orph->cmt_no = cpu_to_le64((c->cmt_no) | (1ULL << 63));
	ubअगरs_निश्चित(c, c->ohead_offs + len <= c->leb_size);
	ubअगरs_निश्चित(c, c->ohead_lnum >= c->orph_first);
	ubअगरs_निश्चित(c, c->ohead_lnum <= c->orph_last);
	err = करो_ग_लिखो_orph_node(c, len, atomic);
	c->ohead_offs += ALIGN(len, c->min_io_size);
	c->ohead_offs = ALIGN(c->ohead_offs, 8);
	वापस err;
पूर्ण

/**
 * ग_लिखो_orph_nodes - ग_लिखो orphan nodes until there are no more to commit.
 * @c: UBIFS file-प्रणाली description object
 * @atomic: ग_लिखो atomically
 *
 * This function ग_लिखोs orphan nodes क्रम all the orphans to commit. On success,
 * %0 is वापसed, otherwise a negative error code is वापसed.
 */
अटल पूर्णांक ग_लिखो_orph_nodes(काष्ठा ubअगरs_info *c, पूर्णांक atomic)
अणु
	पूर्णांक err;

	जबतक (c->cmt_orphans > 0) अणु
		err = ग_लिखो_orph_node(c, atomic);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (atomic) अणु
		पूर्णांक lnum;

		/* Unmap any unused LEBs after consolidation */
		क्रम (lnum = c->ohead_lnum + 1; lnum <= c->orph_last; lnum++) अणु
			err = ubअगरs_leb_unmap(c, lnum);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * consolidate - consolidate the orphan area.
 * @c: UBIFS file-प्रणाली description object
 *
 * This function enables consolidation by putting all the orphans पूर्णांकo the list
 * to commit. The list is in the order that the orphans were added, and the
 * LEBs are written atomically in order, so at no समय can orphans be lost by
 * an unclean unmount.
 *
 * This function वापसs %0 on success and a negative error code on failure.
 */
अटल पूर्णांक consolidate(काष्ठा ubअगरs_info *c)
अणु
	पूर्णांक tot_avail = tot_avail_orphs(c), err = 0;

	spin_lock(&c->orphan_lock);
	dbg_cmt("there is space for %d orphans and there are %d",
		tot_avail, c->tot_orphans);
	अगर (c->tot_orphans - c->new_orphans <= tot_avail) अणु
		काष्ठा ubअगरs_orphan *orphan, **last;
		पूर्णांक cnt = 0;

		/* Change the cnext list to include all non-new orphans */
		last = &c->orph_cnext;
		list_क्रम_each_entry(orphan, &c->orph_list, list) अणु
			अगर (orphan->new)
				जारी;
			orphan->cmt = 1;
			*last = orphan;
			last = &orphan->cnext;
			cnt += 1;
		पूर्ण
		*last = शून्य;
		ubअगरs_निश्चित(c, cnt == c->tot_orphans - c->new_orphans);
		c->cmt_orphans = cnt;
		c->ohead_lnum = c->orph_first;
		c->ohead_offs = 0;
	पूर्ण अन्यथा अणु
		/*
		 * We limit the number of orphans so that this should
		 * never happen.
		 */
		ubअगरs_err(c, "out of space in orphan area");
		err = -EINVAL;
	पूर्ण
	spin_unlock(&c->orphan_lock);
	वापस err;
पूर्ण

/**
 * commit_orphans - commit orphans.
 * @c: UBIFS file-प्रणाली description object
 *
 * This function commits orphans to flash. On success, %0 is वापसed,
 * otherwise a negative error code is वापसed.
 */
अटल पूर्णांक commit_orphans(काष्ठा ubअगरs_info *c)
अणु
	पूर्णांक avail, atomic = 0, err;

	ubअगरs_निश्चित(c, c->cmt_orphans > 0);
	avail = avail_orphs(c);
	अगर (avail < c->cmt_orphans) अणु
		/* Not enough space to ग_लिखो new orphans, so consolidate */
		err = consolidate(c);
		अगर (err)
			वापस err;
		atomic = 1;
	पूर्ण
	err = ग_लिखो_orph_nodes(c, atomic);
	वापस err;
पूर्ण

/**
 * erase_deleted - erase the orphans marked क्रम deletion.
 * @c: UBIFS file-प्रणाली description object
 *
 * During commit, the orphans being committed cannot be deleted, so they are
 * marked क्रम deletion and deleted by this function. Also, the recovery
 * adds समाप्तed orphans to the deletion list, and thereक्रमe they are deleted
 * here too.
 */
अटल व्योम erase_deleted(काष्ठा ubअगरs_info *c)
अणु
	काष्ठा ubअगरs_orphan *orphan, *dnext;

	spin_lock(&c->orphan_lock);
	dnext = c->orph_dnext;
	जबतक (dnext) अणु
		orphan = dnext;
		dnext = orphan->dnext;
		ubअगरs_निश्चित(c, !orphan->new);
		ubअगरs_निश्चित(c, orphan->del);
		rb_erase(&orphan->rb, &c->orph_tree);
		list_del(&orphan->list);
		c->tot_orphans -= 1;
		dbg_gen("deleting orphan ino %lu", (अचिन्हित दीर्घ)orphan->inum);
		kमुक्त(orphan);
	पूर्ण
	c->orph_dnext = शून्य;
	spin_unlock(&c->orphan_lock);
पूर्ण

/**
 * ubअगरs_orphan_end_commit - end commit of orphans.
 * @c: UBIFS file-प्रणाली description object
 *
 * End commit of orphans.
 */
पूर्णांक ubअगरs_orphan_end_commit(काष्ठा ubअगरs_info *c)
अणु
	पूर्णांक err;

	अगर (c->cmt_orphans != 0) अणु
		err = commit_orphans(c);
		अगर (err)
			वापस err;
	पूर्ण
	erase_deleted(c);
	err = dbg_check_orphans(c);
	वापस err;
पूर्ण

/**
 * ubअगरs_clear_orphans - erase all LEBs used क्रम orphans.
 * @c: UBIFS file-प्रणाली description object
 *
 * If recovery is not required, then the orphans from the previous session
 * are not needed. This function locates the LEBs used to record
 * orphans, and un-maps them.
 */
पूर्णांक ubअगरs_clear_orphans(काष्ठा ubअगरs_info *c)
अणु
	पूर्णांक lnum, err;

	क्रम (lnum = c->orph_first; lnum <= c->orph_last; lnum++) अणु
		err = ubअगरs_leb_unmap(c, lnum);
		अगर (err)
			वापस err;
	पूर्ण
	c->ohead_lnum = c->orph_first;
	c->ohead_offs = 0;
	वापस 0;
पूर्ण

/**
 * insert_dead_orphan - insert an orphan.
 * @c: UBIFS file-प्रणाली description object
 * @inum: orphan inode number
 *
 * This function is a helper to the 'do_kill_orphans()' function. The orphan
 * must be kept until the next commit, so it is added to the rb-tree and the
 * deletion list.
 */
अटल पूर्णांक insert_dead_orphan(काष्ठा ubअगरs_info *c, ino_t inum)
अणु
	काष्ठा ubअगरs_orphan *orphan, *o;
	काष्ठा rb_node **p, *parent = शून्य;

	orphan = kzalloc(माप(काष्ठा ubअगरs_orphan), GFP_KERNEL);
	अगर (!orphan)
		वापस -ENOMEM;
	orphan->inum = inum;

	p = &c->orph_tree.rb_node;
	जबतक (*p) अणु
		parent = *p;
		o = rb_entry(parent, काष्ठा ubअगरs_orphan, rb);
		अगर (inum < o->inum)
			p = &(*p)->rb_left;
		अन्यथा अगर (inum > o->inum)
			p = &(*p)->rb_right;
		अन्यथा अणु
			/* Alपढ़ोy added - no problem */
			kमुक्त(orphan);
			वापस 0;
		पूर्ण
	पूर्ण
	c->tot_orphans += 1;
	rb_link_node(&orphan->rb, parent, p);
	rb_insert_color(&orphan->rb, &c->orph_tree);
	list_add_tail(&orphan->list, &c->orph_list);
	orphan->del = 1;
	orphan->dnext = c->orph_dnext;
	c->orph_dnext = orphan;
	dbg_mnt("ino %lu, new %d, tot %d", (अचिन्हित दीर्घ)inum,
		c->new_orphans, c->tot_orphans);
	वापस 0;
पूर्ण

/**
 * करो_समाप्त_orphans - हटाओ orphan inodes from the index.
 * @c: UBIFS file-प्रणाली description object
 * @sleb: scanned LEB
 * @last_cmt_no: cmt_no of last orphan node पढ़ो is passed and वापसed here
 * @outofdate: whether the LEB is out of date is वापसed here
 * @last_flagged: whether the end orphan node is encountered
 *
 * This function is a helper to the 'kill_orphans()' function. It goes through
 * every orphan node in a LEB and क्रम every inode number recorded, हटाओs
 * all keys क्रम that inode from the TNC.
 */
अटल पूर्णांक करो_समाप्त_orphans(काष्ठा ubअगरs_info *c, काष्ठा ubअगरs_scan_leb *sleb,
			   अचिन्हित दीर्घ दीर्घ *last_cmt_no, पूर्णांक *outofdate,
			   पूर्णांक *last_flagged)
अणु
	काष्ठा ubअगरs_scan_node *snod;
	काष्ठा ubअगरs_orph_node *orph;
	काष्ठा ubअगरs_ino_node *ino = शून्य;
	अचिन्हित दीर्घ दीर्घ cmt_no;
	ino_t inum;
	पूर्णांक i, n, err, first = 1;

	ino = kदो_स्मृति(UBIFS_MAX_INO_NODE_SZ, GFP_NOFS);
	अगर (!ino)
		वापस -ENOMEM;

	list_क्रम_each_entry(snod, &sleb->nodes, list) अणु
		अगर (snod->type != UBIFS_ORPH_NODE) अणु
			ubअगरs_err(c, "invalid node type %d in orphan area at %d:%d",
				  snod->type, sleb->lnum, snod->offs);
			ubअगरs_dump_node(c, snod->node,
					c->leb_size - snod->offs);
			err = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		orph = snod->node;

		/* Check commit number */
		cmt_no = le64_to_cpu(orph->cmt_no) & Lदीर्घ_उच्च;
		/*
		 * The commit number on the master node may be less, because
		 * of a failed commit. If there are several failed commits in a
		 * row, the commit number written on orphan nodes will जारी
		 * to increase (because the commit number is adjusted here) even
		 * though the commit number on the master node stays the same
		 * because the master node has not been re-written.
		 */
		अगर (cmt_no > c->cmt_no)
			c->cmt_no = cmt_no;
		अगर (cmt_no < *last_cmt_no && *last_flagged) अणु
			/*
			 * The last orphan node had a higher commit number and
			 * was flagged as the last written क्रम that commit
			 * number. That makes this orphan node, out of date.
			 */
			अगर (!first) अणु
				ubअगरs_err(c, "out of order commit number %llu in orphan node at %d:%d",
					  cmt_no, sleb->lnum, snod->offs);
				ubअगरs_dump_node(c, snod->node,
						c->leb_size - snod->offs);
				err = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण
			dbg_rcvry("out of date LEB %d", sleb->lnum);
			*outofdate = 1;
			err = 0;
			जाओ out_मुक्त;
		पूर्ण

		अगर (first)
			first = 0;

		n = (le32_to_cpu(orph->ch.len) - UBIFS_ORPH_NODE_SZ) >> 3;
		क्रम (i = 0; i < n; i++) अणु
			जोड़ ubअगरs_key key1, key2;

			inum = le64_to_cpu(orph->inos[i]);

			ino_key_init(c, &key1, inum);
			err = ubअगरs_tnc_lookup(c, &key1, ino);
			अगर (err && err != -ENOENT)
				जाओ out_मुक्त;

			/*
			 * Check whether an inode can really get deleted.
			 * linkat() with O_TMPखाता allows rebirth of an inode.
			 */
			अगर (err == 0 && ino->nlink == 0) अणु
				dbg_rcvry("deleting orphaned inode %lu",
					  (अचिन्हित दीर्घ)inum);

				lowest_ino_key(c, &key1, inum);
				highest_ino_key(c, &key2, inum);

				err = ubअगरs_tnc_हटाओ_range(c, &key1, &key2);
				अगर (err)
					जाओ out_ro;
			पूर्ण

			err = insert_dead_orphan(c, inum);
			अगर (err)
				जाओ out_मुक्त;
		पूर्ण

		*last_cmt_no = cmt_no;
		अगर (le64_to_cpu(orph->cmt_no) & (1ULL << 63)) अणु
			dbg_rcvry("last orph node for commit %llu at %d:%d",
				  cmt_no, sleb->lnum, snod->offs);
			*last_flagged = 1;
		पूर्ण अन्यथा
			*last_flagged = 0;
	पूर्ण

	err = 0;
out_मुक्त:
	kमुक्त(ino);
	वापस err;

out_ro:
	ubअगरs_ro_mode(c, err);
	kमुक्त(ino);
	वापस err;
पूर्ण

/**
 * समाप्त_orphans - हटाओ all orphan inodes from the index.
 * @c: UBIFS file-प्रणाली description object
 *
 * If recovery is required, then orphan inodes recorded during the previous
 * session (which ended with an unclean unmount) must be deleted from the index.
 * This is करोne by updating the TNC, but since the index is not updated until
 * the next commit, the LEBs where the orphan inक्रमmation is recorded are not
 * erased until the next commit.
 */
अटल पूर्णांक समाप्त_orphans(काष्ठा ubअगरs_info *c)
अणु
	अचिन्हित दीर्घ दीर्घ last_cmt_no = 0;
	पूर्णांक lnum, err = 0, outofdate = 0, last_flagged = 0;

	c->ohead_lnum = c->orph_first;
	c->ohead_offs = 0;
	/* Check no-orphans flag and skip this अगर no orphans */
	अगर (c->no_orphs) अणु
		dbg_rcvry("no orphans");
		वापस 0;
	पूर्ण
	/*
	 * Orph nodes always start at c->orph_first and are written to each
	 * successive LEB in turn. Generally unused LEBs will have been unmapped
	 * but may contain out of date orphan nodes अगर the unmap didn't go
	 * through. In addition, the last orphan node written क्रम each commit is
	 * marked (top bit of orph->cmt_no is set to 1). It is possible that
	 * there are orphan nodes from the next commit (i.e. the commit did not
	 * complete successfully). In that हाल, no orphans will have been lost
	 * due to the way that orphans are written, and any orphans added will
	 * be valid orphans anyway and so can be deleted.
	 */
	क्रम (lnum = c->orph_first; lnum <= c->orph_last; lnum++) अणु
		काष्ठा ubअगरs_scan_leb *sleb;

		dbg_rcvry("LEB %d", lnum);
		sleb = ubअगरs_scan(c, lnum, 0, c->sbuf, 1);
		अगर (IS_ERR(sleb)) अणु
			अगर (PTR_ERR(sleb) == -EUCLEAN)
				sleb = ubअगरs_recover_leb(c, lnum, 0,
							 c->sbuf, -1);
			अगर (IS_ERR(sleb)) अणु
				err = PTR_ERR(sleb);
				अवरोध;
			पूर्ण
		पूर्ण
		err = करो_समाप्त_orphans(c, sleb, &last_cmt_no, &outofdate,
				      &last_flagged);
		अगर (err || outofdate) अणु
			ubअगरs_scan_destroy(sleb);
			अवरोध;
		पूर्ण
		अगर (sleb->endpt) अणु
			c->ohead_lnum = lnum;
			c->ohead_offs = sleb->endpt;
		पूर्ण
		ubअगरs_scan_destroy(sleb);
	पूर्ण
	वापस err;
पूर्ण

/**
 * ubअगरs_mount_orphans - delete orphan inodes and erase LEBs that recorded them.
 * @c: UBIFS file-प्रणाली description object
 * @unclean: indicates recovery from unclean unmount
 * @पढ़ो_only: indicates पढ़ो only mount
 *
 * This function is called when mounting to erase orphans from the previous
 * session. If UBIFS was not unmounted cleanly, then the inodes recorded as
 * orphans are deleted.
 */
पूर्णांक ubअगरs_mount_orphans(काष्ठा ubअगरs_info *c, पूर्णांक unclean, पूर्णांक पढ़ो_only)
अणु
	पूर्णांक err = 0;

	c->max_orphans = tot_avail_orphs(c);

	अगर (!पढ़ो_only) अणु
		c->orph_buf = vदो_स्मृति(c->leb_size);
		अगर (!c->orph_buf)
			वापस -ENOMEM;
	पूर्ण

	अगर (unclean)
		err = समाप्त_orphans(c);
	अन्यथा अगर (!पढ़ो_only)
		err = ubअगरs_clear_orphans(c);

	वापस err;
पूर्ण

/*
 * Everything below is related to debugging.
 */

काष्ठा check_orphan अणु
	काष्ठा rb_node rb;
	ino_t inum;
पूर्ण;

काष्ठा check_info अणु
	अचिन्हित दीर्घ last_ino;
	अचिन्हित दीर्घ tot_inos;
	अचिन्हित दीर्घ missing;
	अचिन्हित दीर्घ दीर्घ leaf_cnt;
	काष्ठा ubअगरs_ino_node *node;
	काष्ठा rb_root root;
पूर्ण;

अटल bool dbg_find_orphan(काष्ठा ubअगरs_info *c, ino_t inum)
अणु
	bool found = false;

	spin_lock(&c->orphan_lock);
	found = !!lookup_orphan(c, inum);
	spin_unlock(&c->orphan_lock);

	वापस found;
पूर्ण

अटल पूर्णांक dbg_ins_check_orphan(काष्ठा rb_root *root, ino_t inum)
अणु
	काष्ठा check_orphan *orphan, *o;
	काष्ठा rb_node **p, *parent = शून्य;

	orphan = kzalloc(माप(काष्ठा check_orphan), GFP_NOFS);
	अगर (!orphan)
		वापस -ENOMEM;
	orphan->inum = inum;

	p = &root->rb_node;
	जबतक (*p) अणु
		parent = *p;
		o = rb_entry(parent, काष्ठा check_orphan, rb);
		अगर (inum < o->inum)
			p = &(*p)->rb_left;
		अन्यथा अगर (inum > o->inum)
			p = &(*p)->rb_right;
		अन्यथा अणु
			kमुक्त(orphan);
			वापस 0;
		पूर्ण
	पूर्ण
	rb_link_node(&orphan->rb, parent, p);
	rb_insert_color(&orphan->rb, root);
	वापस 0;
पूर्ण

अटल पूर्णांक dbg_find_check_orphan(काष्ठा rb_root *root, ino_t inum)
अणु
	काष्ठा check_orphan *o;
	काष्ठा rb_node *p;

	p = root->rb_node;
	जबतक (p) अणु
		o = rb_entry(p, काष्ठा check_orphan, rb);
		अगर (inum < o->inum)
			p = p->rb_left;
		अन्यथा अगर (inum > o->inum)
			p = p->rb_right;
		अन्यथा
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dbg_मुक्त_check_tree(काष्ठा rb_root *root)
अणु
	काष्ठा check_orphan *o, *n;

	rbtree_postorder_क्रम_each_entry_safe(o, n, root, rb)
		kमुक्त(o);
पूर्ण

अटल पूर्णांक dbg_orphan_check(काष्ठा ubअगरs_info *c, काष्ठा ubअगरs_zbranch *zbr,
			    व्योम *priv)
अणु
	काष्ठा check_info *ci = priv;
	ino_t inum;
	पूर्णांक err;

	inum = key_inum(c, &zbr->key);
	अगर (inum != ci->last_ino) अणु
		/* Lowest node type is the inode node, so it comes first */
		अगर (key_type(c, &zbr->key) != UBIFS_INO_KEY)
			ubअगरs_err(c, "found orphan node ino %lu, type %d",
				  (अचिन्हित दीर्घ)inum, key_type(c, &zbr->key));
		ci->last_ino = inum;
		ci->tot_inos += 1;
		err = ubअगरs_tnc_पढ़ो_node(c, zbr, ci->node);
		अगर (err) अणु
			ubअगरs_err(c, "node read failed, error %d", err);
			वापस err;
		पूर्ण
		अगर (ci->node->nlink == 0)
			/* Must be recorded as an orphan */
			अगर (!dbg_find_check_orphan(&ci->root, inum) &&
			    !dbg_find_orphan(c, inum)) अणु
				ubअगरs_err(c, "missing orphan, ino %lu",
					  (अचिन्हित दीर्घ)inum);
				ci->missing += 1;
			पूर्ण
	पूर्ण
	ci->leaf_cnt += 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dbg_पढ़ो_orphans(काष्ठा check_info *ci, काष्ठा ubअगरs_scan_leb *sleb)
अणु
	काष्ठा ubअगरs_scan_node *snod;
	काष्ठा ubअगरs_orph_node *orph;
	ino_t inum;
	पूर्णांक i, n, err;

	list_क्रम_each_entry(snod, &sleb->nodes, list) अणु
		cond_resched();
		अगर (snod->type != UBIFS_ORPH_NODE)
			जारी;
		orph = snod->node;
		n = (le32_to_cpu(orph->ch.len) - UBIFS_ORPH_NODE_SZ) >> 3;
		क्रम (i = 0; i < n; i++) अणु
			inum = le64_to_cpu(orph->inos[i]);
			err = dbg_ins_check_orphan(&ci->root, inum);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dbg_scan_orphans(काष्ठा ubअगरs_info *c, काष्ठा check_info *ci)
अणु
	पूर्णांक lnum, err = 0;
	व्योम *buf;

	/* Check no-orphans flag and skip this अगर no orphans */
	अगर (c->no_orphs)
		वापस 0;

	buf = __vदो_स्मृति(c->leb_size, GFP_NOFS);
	अगर (!buf) अणु
		ubअगरs_err(c, "cannot allocate memory to check orphans");
		वापस 0;
	पूर्ण

	क्रम (lnum = c->orph_first; lnum <= c->orph_last; lnum++) अणु
		काष्ठा ubअगरs_scan_leb *sleb;

		sleb = ubअगरs_scan(c, lnum, 0, buf, 0);
		अगर (IS_ERR(sleb)) अणु
			err = PTR_ERR(sleb);
			अवरोध;
		पूर्ण

		err = dbg_पढ़ो_orphans(ci, sleb);
		ubअगरs_scan_destroy(sleb);
		अगर (err)
			अवरोध;
	पूर्ण

	vमुक्त(buf);
	वापस err;
पूर्ण

अटल पूर्णांक dbg_check_orphans(काष्ठा ubअगरs_info *c)
अणु
	काष्ठा check_info ci;
	पूर्णांक err;

	अगर (!dbg_is_chk_orph(c))
		वापस 0;

	ci.last_ino = 0;
	ci.tot_inos = 0;
	ci.missing  = 0;
	ci.leaf_cnt = 0;
	ci.root = RB_ROOT;
	ci.node = kदो_स्मृति(UBIFS_MAX_INO_NODE_SZ, GFP_NOFS);
	अगर (!ci.node) अणु
		ubअगरs_err(c, "out of memory");
		वापस -ENOMEM;
	पूर्ण

	err = dbg_scan_orphans(c, &ci);
	अगर (err)
		जाओ out;

	err = dbg_walk_index(c, &dbg_orphan_check, शून्य, &ci);
	अगर (err) अणु
		ubअगरs_err(c, "cannot scan TNC, error %d", err);
		जाओ out;
	पूर्ण

	अगर (ci.missing) अणु
		ubअगरs_err(c, "%lu missing orphan(s)", ci.missing);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	dbg_cmt("last inode number is %lu", ci.last_ino);
	dbg_cmt("total number of inodes is %lu", ci.tot_inos);
	dbg_cmt("total number of leaf nodes is %llu", ci.leaf_cnt);

out:
	dbg_मुक्त_check_tree(&ci.root);
	kमुक्त(ci.node);
	वापस err;
पूर्ण
