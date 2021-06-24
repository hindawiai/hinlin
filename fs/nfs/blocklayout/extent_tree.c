<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014-2016 Christoph Hellwig.
 */

#समावेश <linux/vदो_स्मृति.h>

#समावेश "blocklayout.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PNFS_LD

अटल अंतरभूत काष्ठा pnfs_block_extent *
ext_node(काष्ठा rb_node *node)
अणु
	वापस rb_entry(node, काष्ठा pnfs_block_extent, be_node);
पूर्ण

अटल काष्ठा pnfs_block_extent *
ext_tree_first(काष्ठा rb_root *root)
अणु
	काष्ठा rb_node *node = rb_first(root);
	वापस node ? ext_node(node) : शून्य;
पूर्ण

अटल काष्ठा pnfs_block_extent *
ext_tree_prev(काष्ठा pnfs_block_extent *be)
अणु
	काष्ठा rb_node *node = rb_prev(&be->be_node);
	वापस node ? ext_node(node) : शून्य;
पूर्ण

अटल काष्ठा pnfs_block_extent *
ext_tree_next(काष्ठा pnfs_block_extent *be)
अणु
	काष्ठा rb_node *node = rb_next(&be->be_node);
	वापस node ? ext_node(node) : शून्य;
पूर्ण

अटल अंतरभूत sector_t
ext_f_end(काष्ठा pnfs_block_extent *be)
अणु
	वापस be->be_f_offset + be->be_length;
पूर्ण

अटल काष्ठा pnfs_block_extent *
__ext_tree_search(काष्ठा rb_root *root, sector_t start)
अणु
	काष्ठा rb_node *node = root->rb_node;
	काष्ठा pnfs_block_extent *be = शून्य;

	जबतक (node) अणु
		be = ext_node(node);
		अगर (start < be->be_f_offset)
			node = node->rb_left;
		अन्यथा अगर (start >= ext_f_end(be))
			node = node->rb_right;
		अन्यथा
			वापस be;
	पूर्ण

	अगर (be) अणु
		अगर (start < be->be_f_offset)
			वापस be;

		अगर (start >= ext_f_end(be))
			वापस ext_tree_next(be);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool
ext_can_merge(काष्ठा pnfs_block_extent *be1, काष्ठा pnfs_block_extent *be2)
अणु
	अगर (be1->be_state != be2->be_state)
		वापस false;
	अगर (be1->be_device != be2->be_device)
		वापस false;

	अगर (be1->be_f_offset + be1->be_length != be2->be_f_offset)
		वापस false;

	अगर (be1->be_state != PNFS_BLOCK_NONE_DATA &&
	    (be1->be_v_offset + be1->be_length != be2->be_v_offset))
		वापस false;

	अगर (be1->be_state == PNFS_BLOCK_INVALID_DATA &&
	    be1->be_tag != be2->be_tag)
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा pnfs_block_extent *
ext_try_to_merge_left(काष्ठा rb_root *root, काष्ठा pnfs_block_extent *be)
अणु
	काष्ठा pnfs_block_extent *left = ext_tree_prev(be);

	अगर (left && ext_can_merge(left, be)) अणु
		left->be_length += be->be_length;
		rb_erase(&be->be_node, root);
		nfs4_put_deviceid_node(be->be_device);
		kमुक्त(be);
		वापस left;
	पूर्ण

	वापस be;
पूर्ण

अटल काष्ठा pnfs_block_extent *
ext_try_to_merge_right(काष्ठा rb_root *root, काष्ठा pnfs_block_extent *be)
अणु
	काष्ठा pnfs_block_extent *right = ext_tree_next(be);

	अगर (right && ext_can_merge(be, right)) अणु
		be->be_length += right->be_length;
		rb_erase(&right->be_node, root);
		nfs4_put_deviceid_node(right->be_device);
		kमुक्त(right);
	पूर्ण

	वापस be;
पूर्ण

अटल व्योम __ext_put_deviceids(काष्ठा list_head *head)
अणु
	काष्ठा pnfs_block_extent *be, *पंचांगp;

	list_क्रम_each_entry_safe(be, पंचांगp, head, be_list) अणु
		nfs4_put_deviceid_node(be->be_device);
		kमुक्त(be);
	पूर्ण
पूर्ण

अटल व्योम
__ext_tree_insert(काष्ठा rb_root *root,
		काष्ठा pnfs_block_extent *new, bool merge_ok)
अणु
	काष्ठा rb_node **p = &root->rb_node, *parent = शून्य;
	काष्ठा pnfs_block_extent *be;

	जबतक (*p) अणु
		parent = *p;
		be = ext_node(parent);

		अगर (new->be_f_offset < be->be_f_offset) अणु
			अगर (merge_ok && ext_can_merge(new, be)) अणु
				be->be_f_offset = new->be_f_offset;
				अगर (be->be_state != PNFS_BLOCK_NONE_DATA)
					be->be_v_offset = new->be_v_offset;
				be->be_length += new->be_length;
				be = ext_try_to_merge_left(root, be);
				जाओ मुक्त_new;
			पूर्ण
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (new->be_f_offset >= ext_f_end(be)) अणु
			अगर (merge_ok && ext_can_merge(be, new)) अणु
				be->be_length += new->be_length;
				be = ext_try_to_merge_right(root, be);
				जाओ मुक्त_new;
			पूर्ण
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			BUG();
		पूर्ण
	पूर्ण

	rb_link_node(&new->be_node, parent, p);
	rb_insert_color(&new->be_node, root);
	वापस;
मुक्त_new:
	nfs4_put_deviceid_node(new->be_device);
	kमुक्त(new);
पूर्ण

अटल पूर्णांक
__ext_tree_हटाओ(काष्ठा rb_root *root,
		sector_t start, sector_t end, काष्ठा list_head *पंचांगp)
अणु
	काष्ठा pnfs_block_extent *be;
	sector_t len1 = 0, len2 = 0;
	sector_t orig_v_offset;
	sector_t orig_len;

	be = __ext_tree_search(root, start);
	अगर (!be)
		वापस 0;
	अगर (be->be_f_offset >= end)
		वापस 0;

	orig_v_offset = be->be_v_offset;
	orig_len = be->be_length;

	अगर (start > be->be_f_offset)
		len1 = start - be->be_f_offset;
	अगर (ext_f_end(be) > end)
		len2 = ext_f_end(be) - end;

	अगर (len2 > 0) अणु
		अगर (len1 > 0) अणु
			काष्ठा pnfs_block_extent *new;

			new = kzalloc(माप(*new), GFP_ATOMIC);
			अगर (!new)
				वापस -ENOMEM;

			be->be_length = len1;

			new->be_f_offset = end;
			अगर (be->be_state != PNFS_BLOCK_NONE_DATA) अणु
				new->be_v_offset =
					orig_v_offset + orig_len - len2;
			पूर्ण
			new->be_length = len2;
			new->be_state = be->be_state;
			new->be_tag = be->be_tag;
			new->be_device = nfs4_get_deviceid(be->be_device);

			__ext_tree_insert(root, new, true);
		पूर्ण अन्यथा अणु
			be->be_f_offset = end;
			अगर (be->be_state != PNFS_BLOCK_NONE_DATA) अणु
				be->be_v_offset =
					orig_v_offset + orig_len - len2;
			पूर्ण
			be->be_length = len2;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (len1 > 0) अणु
			be->be_length = len1;
			be = ext_tree_next(be);
		पूर्ण

		जबतक (be && ext_f_end(be) <= end) अणु
			काष्ठा pnfs_block_extent *next = ext_tree_next(be);

			rb_erase(&be->be_node, root);
			list_add_tail(&be->be_list, पंचांगp);
			be = next;
		पूर्ण

		अगर (be && be->be_f_offset < end) अणु
			len1 = ext_f_end(be) - end;
			be->be_f_offset = end;
			अगर (be->be_state != PNFS_BLOCK_NONE_DATA)
				be->be_v_offset += be->be_length - len1;
			be->be_length = len1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
ext_tree_insert(काष्ठा pnfs_block_layout *bl, काष्ठा pnfs_block_extent *new)
अणु
	काष्ठा pnfs_block_extent *be;
	काष्ठा rb_root *root;
	पूर्णांक err = 0;

	चयन (new->be_state) अणु
	हाल PNFS_BLOCK_READWRITE_DATA:
	हाल PNFS_BLOCK_INVALID_DATA:
		root = &bl->bl_ext_rw;
		अवरोध;
	हाल PNFS_BLOCK_READ_DATA:
	हाल PNFS_BLOCK_NONE_DATA:
		root = &bl->bl_ext_ro;
		अवरोध;
	शेष:
		dprपूर्णांकk("invalid extent type\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock(&bl->bl_ext_lock);
retry:
	be = __ext_tree_search(root, new->be_f_offset);
	अगर (!be || be->be_f_offset >= ext_f_end(new)) अणु
		__ext_tree_insert(root, new, true);
	पूर्ण अन्यथा अगर (new->be_f_offset >= be->be_f_offset) अणु
		अगर (ext_f_end(new) <= ext_f_end(be)) अणु
			nfs4_put_deviceid_node(new->be_device);
			kमुक्त(new);
		पूर्ण अन्यथा अणु
			sector_t new_len = ext_f_end(new) - ext_f_end(be);
			sector_t dअगरf = new->be_length - new_len;

			new->be_f_offset += dअगरf;
			new->be_v_offset += dअगरf;
			new->be_length = new_len;
			जाओ retry;
		पूर्ण
	पूर्ण अन्यथा अगर (ext_f_end(new) <= ext_f_end(be)) अणु
		new->be_length = be->be_f_offset - new->be_f_offset;
		__ext_tree_insert(root, new, true);
	पूर्ण अन्यथा अणु
		काष्ठा pnfs_block_extent *split;
		sector_t new_len = ext_f_end(new) - ext_f_end(be);
		sector_t dअगरf = new->be_length - new_len;

		split = kmemdup(new, माप(*new), GFP_ATOMIC);
		अगर (!split) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		split->be_length = be->be_f_offset - split->be_f_offset;
		split->be_device = nfs4_get_deviceid(new->be_device);
		__ext_tree_insert(root, split, true);

		new->be_f_offset += dअगरf;
		new->be_v_offset += dअगरf;
		new->be_length = new_len;
		जाओ retry;
	पूर्ण
out:
	spin_unlock(&bl->bl_ext_lock);
	वापस err;
पूर्ण

अटल bool
__ext_tree_lookup(काष्ठा rb_root *root, sector_t isect,
		काष्ठा pnfs_block_extent *ret)
अणु
	काष्ठा rb_node *node;
	काष्ठा pnfs_block_extent *be;

	node = root->rb_node;
	जबतक (node) अणु
		be = ext_node(node);
		अगर (isect < be->be_f_offset)
			node = node->rb_left;
		अन्यथा अगर (isect >= ext_f_end(be))
			node = node->rb_right;
		अन्यथा अणु
			*ret = *be;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

bool
ext_tree_lookup(काष्ठा pnfs_block_layout *bl, sector_t isect,
	    काष्ठा pnfs_block_extent *ret, bool rw)
अणु
	bool found = false;

	spin_lock(&bl->bl_ext_lock);
	अगर (!rw)
		found = __ext_tree_lookup(&bl->bl_ext_ro, isect, ret);
	अगर (!found)
		found = __ext_tree_lookup(&bl->bl_ext_rw, isect, ret);
	spin_unlock(&bl->bl_ext_lock);

	वापस found;
पूर्ण

पूर्णांक ext_tree_हटाओ(काष्ठा pnfs_block_layout *bl, bool rw,
		sector_t start, sector_t end)
अणु
	पूर्णांक err, err2;
	LIST_HEAD(पंचांगp);

	spin_lock(&bl->bl_ext_lock);
	err = __ext_tree_हटाओ(&bl->bl_ext_ro, start, end, &पंचांगp);
	अगर (rw) अणु
		err2 = __ext_tree_हटाओ(&bl->bl_ext_rw, start, end, &पंचांगp);
		अगर (!err)
			err = err2;
	पूर्ण
	spin_unlock(&bl->bl_ext_lock);

	__ext_put_deviceids(&पंचांगp);
	वापस err;
पूर्ण

अटल पूर्णांक
ext_tree_split(काष्ठा rb_root *root, काष्ठा pnfs_block_extent *be,
		sector_t split)
अणु
	काष्ठा pnfs_block_extent *new;
	sector_t orig_len = be->be_length;

	new = kzalloc(माप(*new), GFP_ATOMIC);
	अगर (!new)
		वापस -ENOMEM;

	be->be_length = split - be->be_f_offset;

	new->be_f_offset = split;
	अगर (be->be_state != PNFS_BLOCK_NONE_DATA)
		new->be_v_offset = be->be_v_offset + be->be_length;
	new->be_length = orig_len - be->be_length;
	new->be_state = be->be_state;
	new->be_tag = be->be_tag;
	new->be_device = nfs4_get_deviceid(be->be_device);

	__ext_tree_insert(root, new, false);
	वापस 0;
पूर्ण

पूर्णांक
ext_tree_mark_written(काष्ठा pnfs_block_layout *bl, sector_t start,
		sector_t len, u64 lwb)
अणु
	काष्ठा rb_root *root = &bl->bl_ext_rw;
	sector_t end = start + len;
	काष्ठा pnfs_block_extent *be;
	पूर्णांक err = 0;
	LIST_HEAD(पंचांगp);

	spin_lock(&bl->bl_ext_lock);
	/*
	 * First हटाओ all COW extents or holes from written to range.
	 */
	err = __ext_tree_हटाओ(&bl->bl_ext_ro, start, end, &पंचांगp);
	अगर (err)
		जाओ out;

	/*
	 * Then mark all invalid extents in the range as written to.
	 */
	क्रम (be = __ext_tree_search(root, start); be; be = ext_tree_next(be)) अणु
		अगर (be->be_f_offset >= end)
			अवरोध;

		अगर (be->be_state != PNFS_BLOCK_INVALID_DATA || be->be_tag)
			जारी;

		अगर (be->be_f_offset < start) अणु
			काष्ठा pnfs_block_extent *left = ext_tree_prev(be);

			अगर (left && ext_can_merge(left, be)) अणु
				sector_t dअगरf = start - be->be_f_offset;

				left->be_length += dअगरf;

				be->be_f_offset += dअगरf;
				be->be_v_offset += dअगरf;
				be->be_length -= dअगरf;
			पूर्ण अन्यथा अणु
				err = ext_tree_split(root, be, start);
				अगर (err)
					जाओ out;
			पूर्ण
		पूर्ण

		अगर (ext_f_end(be) > end) अणु
			काष्ठा pnfs_block_extent *right = ext_tree_next(be);

			अगर (right && ext_can_merge(be, right)) अणु
				sector_t dअगरf = end - be->be_f_offset;

				be->be_length -= dअगरf;

				right->be_f_offset -= dअगरf;
				right->be_v_offset -= dअगरf;
				right->be_length += dअगरf;
			पूर्ण अन्यथा अणु
				err = ext_tree_split(root, be, end);
				अगर (err)
					जाओ out;
			पूर्ण
		पूर्ण

		अगर (be->be_f_offset >= start && ext_f_end(be) <= end) अणु
			be->be_tag = EXTENT_WRITTEN;
			be = ext_try_to_merge_left(root, be);
			be = ext_try_to_merge_right(root, be);
		पूर्ण
	पूर्ण
out:
	अगर (bl->bl_lwb < lwb)
		bl->bl_lwb = lwb;
	spin_unlock(&bl->bl_ext_lock);

	__ext_put_deviceids(&पंचांगp);
	वापस err;
पूर्ण

अटल माप_प्रकार ext_tree_layoutupdate_size(काष्ठा pnfs_block_layout *bl, माप_प्रकार count)
अणु
	अगर (bl->bl_scsi_layout)
		वापस माप(__be32) + PNFS_SCSI_RANGE_SIZE * count;
	अन्यथा
		वापस माप(__be32) + PNFS_BLOCK_EXTENT_SIZE * count;
पूर्ण

अटल व्योम ext_tree_मुक्त_commitdata(काष्ठा nfs4_layoutcommit_args *arg,
		माप_प्रकार buffer_size)
अणु
	अगर (arg->layoutupdate_pages != &arg->layoutupdate_page) अणु
		पूर्णांक nr_pages = DIV_ROUND_UP(buffer_size, PAGE_SIZE), i;

		क्रम (i = 0; i < nr_pages; i++)
			put_page(arg->layoutupdate_pages[i]);
		vमुक्त(arg->start_p);
		kमुक्त(arg->layoutupdate_pages);
	पूर्ण अन्यथा अणु
		put_page(arg->layoutupdate_page);
	पूर्ण
पूर्ण

अटल __be32 *encode_block_extent(काष्ठा pnfs_block_extent *be, __be32 *p)
अणु
	p = xdr_encode_opaque_fixed(p, be->be_device->deviceid.data,
			NFS4_DEVICEID4_SIZE);
	p = xdr_encode_hyper(p, be->be_f_offset << SECTOR_SHIFT);
	p = xdr_encode_hyper(p, be->be_length << SECTOR_SHIFT);
	p = xdr_encode_hyper(p, 0LL);
	*p++ = cpu_to_be32(PNFS_BLOCK_READWRITE_DATA);
	वापस p;
पूर्ण

अटल __be32 *encode_scsi_range(काष्ठा pnfs_block_extent *be, __be32 *p)
अणु
	p = xdr_encode_hyper(p, be->be_f_offset << SECTOR_SHIFT);
	वापस xdr_encode_hyper(p, be->be_length << SECTOR_SHIFT);
पूर्ण

अटल पूर्णांक ext_tree_encode_commit(काष्ठा pnfs_block_layout *bl, __be32 *p,
		माप_प्रकार buffer_size, माप_प्रकार *count, __u64 *lastbyte)
अणु
	काष्ठा pnfs_block_extent *be;
	पूर्णांक ret = 0;

	spin_lock(&bl->bl_ext_lock);
	क्रम (be = ext_tree_first(&bl->bl_ext_rw); be; be = ext_tree_next(be)) अणु
		अगर (be->be_state != PNFS_BLOCK_INVALID_DATA ||
		    be->be_tag != EXTENT_WRITTEN)
			जारी;

		(*count)++;
		अगर (ext_tree_layoutupdate_size(bl, *count) > buffer_size) अणु
			/* keep counting.. */
			ret = -ENOSPC;
			जारी;
		पूर्ण

		अगर (bl->bl_scsi_layout)
			p = encode_scsi_range(be, p);
		अन्यथा
			p = encode_block_extent(be, p);
		be->be_tag = EXTENT_COMMITTING;
	पूर्ण
	*lastbyte = bl->bl_lwb - 1;
	bl->bl_lwb = 0;
	spin_unlock(&bl->bl_ext_lock);

	वापस ret;
पूर्ण

पूर्णांक
ext_tree_prepare_commit(काष्ठा nfs4_layoutcommit_args *arg)
अणु
	काष्ठा pnfs_block_layout *bl = BLK_LO2EXT(NFS_I(arg->inode)->layout);
	माप_प्रकार count = 0, buffer_size = PAGE_SIZE;
	__be32 *start_p;
	पूर्णांक ret;

	dprपूर्णांकk("%s enter\n", __func__);

	arg->layoutupdate_page = alloc_page(GFP_NOFS);
	अगर (!arg->layoutupdate_page)
		वापस -ENOMEM;
	start_p = page_address(arg->layoutupdate_page);
	arg->layoutupdate_pages = &arg->layoutupdate_page;

retry:
	ret = ext_tree_encode_commit(bl, start_p + 1, buffer_size, &count, &arg->lastbytewritten);
	अगर (unlikely(ret)) अणु
		ext_tree_मुक्त_commitdata(arg, buffer_size);

		buffer_size = ext_tree_layoutupdate_size(bl, count);
		count = 0;

		arg->layoutupdate_pages =
			kसुस्मृति(DIV_ROUND_UP(buffer_size, PAGE_SIZE),
				माप(काष्ठा page *), GFP_NOFS);
		अगर (!arg->layoutupdate_pages)
			वापस -ENOMEM;

		start_p = __vदो_स्मृति(buffer_size, GFP_NOFS);
		अगर (!start_p) अणु
			kमुक्त(arg->layoutupdate_pages);
			वापस -ENOMEM;
		पूर्ण

		जाओ retry;
	पूर्ण

	*start_p = cpu_to_be32(count);
	arg->layoutupdate_len = ext_tree_layoutupdate_size(bl, count);

	अगर (unlikely(arg->layoutupdate_pages != &arg->layoutupdate_page)) अणु
		व्योम *p = start_p, *end = p + arg->layoutupdate_len;
		काष्ठा page *page = शून्य;
		पूर्णांक i = 0;

		arg->start_p = start_p;
		क्रम ( ; p < end; p += PAGE_SIZE) अणु
			page = vदो_स्मृति_to_page(p);
			arg->layoutupdate_pages[i++] = page;
			get_page(page);
		पूर्ण
	पूर्ण

	dprपूर्णांकk("%s found %zu ranges\n", __func__, count);
	वापस 0;
पूर्ण

व्योम
ext_tree_mark_committed(काष्ठा nfs4_layoutcommit_args *arg, पूर्णांक status)
अणु
	काष्ठा pnfs_block_layout *bl = BLK_LO2EXT(NFS_I(arg->inode)->layout);
	काष्ठा rb_root *root = &bl->bl_ext_rw;
	काष्ठा pnfs_block_extent *be;

	dprपूर्णांकk("%s status %d\n", __func__, status);

	ext_tree_मुक्त_commitdata(arg, arg->layoutupdate_len);

	spin_lock(&bl->bl_ext_lock);
	क्रम (be = ext_tree_first(root); be; be = ext_tree_next(be)) अणु
		अगर (be->be_state != PNFS_BLOCK_INVALID_DATA ||
		    be->be_tag != EXTENT_COMMITTING)
			जारी;

		अगर (status) अणु
			/*
			 * Mark as written and try again.
			 *
			 * XXX: some real error handling here wouldn't hurt..
			 */
			be->be_tag = EXTENT_WRITTEN;
		पूर्ण अन्यथा अणु
			be->be_state = PNFS_BLOCK_READWRITE_DATA;
			be->be_tag = 0;
		पूर्ण

		be = ext_try_to_merge_left(root, be);
		be = ext_try_to_merge_right(root, be);
	पूर्ण
	spin_unlock(&bl->bl_ext_lock);
पूर्ण
