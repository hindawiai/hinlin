<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (c) 2012 Taobao.
 * Written by Tao Ma <boyu.mt@taobao.com>
 */

#समावेश <linux/iomap.h>
#समावेश <linux/fiemap.h>
#समावेश <linux/iversion.h>

#समावेश "ext4_jbd2.h"
#समावेश "ext4.h"
#समावेश "xattr.h"
#समावेश "truncate.h"

#घोषणा EXT4_XATTR_SYSTEM_DATA	"data"
#घोषणा EXT4_MIN_INLINE_DATA_SIZE	((माप(__le32) * EXT4_N_BLOCKS))
#घोषणा EXT4_INLINE_DOTDOT_OFFSET	2
#घोषणा EXT4_INLINE_DOTDOT_SIZE		4

अटल पूर्णांक ext4_get_अंतरभूत_size(काष्ठा inode *inode)
अणु
	अगर (EXT4_I(inode)->i_अंतरभूत_off)
		वापस EXT4_I(inode)->i_अंतरभूत_size;

	वापस 0;
पूर्ण

अटल पूर्णांक get_max_अंतरभूत_xattr_value_size(काष्ठा inode *inode,
					   काष्ठा ext4_iloc *iloc)
अणु
	काष्ठा ext4_xattr_ibody_header *header;
	काष्ठा ext4_xattr_entry *entry;
	काष्ठा ext4_inode *raw_inode;
	पूर्णांक मुक्त, min_offs;

	min_offs = EXT4_SB(inode->i_sb)->s_inode_size -
			EXT4_GOOD_OLD_INODE_SIZE -
			EXT4_I(inode)->i_extra_isize -
			माप(काष्ठा ext4_xattr_ibody_header);

	/*
	 * We need to subtract another माप(__u32) since an in-inode xattr
	 * needs an empty 4 bytes to indicate the gap between the xattr entry
	 * and the name/value pair.
	 */
	अगर (!ext4_test_inode_state(inode, EXT4_STATE_XATTR))
		वापस EXT4_XATTR_SIZE(min_offs -
			EXT4_XATTR_LEN(म_माप(EXT4_XATTR_SYSTEM_DATA)) -
			EXT4_XATTR_ROUND - माप(__u32));

	raw_inode = ext4_raw_inode(iloc);
	header = IHDR(inode, raw_inode);
	entry = IFIRST(header);

	/* Compute min_offs. */
	क्रम (; !IS_LAST_ENTRY(entry); entry = EXT4_XATTR_NEXT(entry)) अणु
		अगर (!entry->e_value_inum && entry->e_value_size) अणु
			माप_प्रकार offs = le16_to_cpu(entry->e_value_offs);
			अगर (offs < min_offs)
				min_offs = offs;
		पूर्ण
	पूर्ण
	मुक्त = min_offs -
		((व्योम *)entry - (व्योम *)IFIRST(header)) - माप(__u32);

	अगर (EXT4_I(inode)->i_अंतरभूत_off) अणु
		entry = (काष्ठा ext4_xattr_entry *)
			((व्योम *)raw_inode + EXT4_I(inode)->i_अंतरभूत_off);

		मुक्त += EXT4_XATTR_SIZE(le32_to_cpu(entry->e_value_size));
		जाओ out;
	पूर्ण

	मुक्त -= EXT4_XATTR_LEN(म_माप(EXT4_XATTR_SYSTEM_DATA));

	अगर (मुक्त > EXT4_XATTR_ROUND)
		मुक्त = EXT4_XATTR_SIZE(मुक्त - EXT4_XATTR_ROUND);
	अन्यथा
		मुक्त = 0;

out:
	वापस मुक्त;
पूर्ण

/*
 * Get the maximum size we now can store in an inode.
 * If we can't find the space for a xattr entry, don't use the space
 * of the extents since we have no space to indicate the अंतरभूत data.
 */
पूर्णांक ext4_get_max_अंतरभूत_size(काष्ठा inode *inode)
अणु
	पूर्णांक error, max_अंतरभूत_size;
	काष्ठा ext4_iloc iloc;

	अगर (EXT4_I(inode)->i_extra_isize == 0)
		वापस 0;

	error = ext4_get_inode_loc(inode, &iloc);
	अगर (error) अणु
		ext4_error_inode_err(inode, __func__, __LINE__, 0, -error,
				     "can't get inode location %lu",
				     inode->i_ino);
		वापस 0;
	पूर्ण

	करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);
	max_अंतरभूत_size = get_max_अंतरभूत_xattr_value_size(inode, &iloc);
	up_पढ़ो(&EXT4_I(inode)->xattr_sem);

	brअन्यथा(iloc.bh);

	अगर (!max_अंतरभूत_size)
		वापस 0;

	वापस max_अंतरभूत_size + EXT4_MIN_INLINE_DATA_SIZE;
पूर्ण

/*
 * this function करोes not take xattr_sem, which is OK because it is
 * currently only used in a code path coming क्रमm ext4_iget, beक्रमe
 * the new inode has been unlocked
 */
पूर्णांक ext4_find_अंतरभूत_data_nolock(काष्ठा inode *inode)
अणु
	काष्ठा ext4_xattr_ibody_find is = अणु
		.s = अणु .not_found = -ENODATA, पूर्ण,
	पूर्ण;
	काष्ठा ext4_xattr_info i = अणु
		.name_index = EXT4_XATTR_INDEX_SYSTEM,
		.name = EXT4_XATTR_SYSTEM_DATA,
	पूर्ण;
	पूर्णांक error;

	अगर (EXT4_I(inode)->i_extra_isize == 0)
		वापस 0;

	error = ext4_get_inode_loc(inode, &is.iloc);
	अगर (error)
		वापस error;

	error = ext4_xattr_ibody_find(inode, &i, &is);
	अगर (error)
		जाओ out;

	अगर (!is.s.not_found) अणु
		अगर (is.s.here->e_value_inum) अणु
			EXT4_ERROR_INODE(inode, "inline data xattr refers "
					 "to an external xattr inode");
			error = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
		EXT4_I(inode)->i_अंतरभूत_off = (u16)((व्योम *)is.s.here -
					(व्योम *)ext4_raw_inode(&is.iloc));
		EXT4_I(inode)->i_अंतरभूत_size = EXT4_MIN_INLINE_DATA_SIZE +
				le32_to_cpu(is.s.here->e_value_size);
		ext4_set_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
	पूर्ण
out:
	brअन्यथा(is.iloc.bh);
	वापस error;
पूर्ण

अटल पूर्णांक ext4_पढ़ो_अंतरभूत_data(काष्ठा inode *inode, व्योम *buffer,
				 अचिन्हित पूर्णांक len,
				 काष्ठा ext4_iloc *iloc)
अणु
	काष्ठा ext4_xattr_entry *entry;
	काष्ठा ext4_xattr_ibody_header *header;
	पूर्णांक cp_len = 0;
	काष्ठा ext4_inode *raw_inode;

	अगर (!len)
		वापस 0;

	BUG_ON(len > EXT4_I(inode)->i_अंतरभूत_size);

	cp_len = len < EXT4_MIN_INLINE_DATA_SIZE ?
			len : EXT4_MIN_INLINE_DATA_SIZE;

	raw_inode = ext4_raw_inode(iloc);
	स_नकल(buffer, (व्योम *)(raw_inode->i_block), cp_len);

	len -= cp_len;
	buffer += cp_len;

	अगर (!len)
		जाओ out;

	header = IHDR(inode, raw_inode);
	entry = (काष्ठा ext4_xattr_entry *)((व्योम *)raw_inode +
					    EXT4_I(inode)->i_अंतरभूत_off);
	len = min_t(अचिन्हित पूर्णांक, len,
		    (अचिन्हित पूर्णांक)le32_to_cpu(entry->e_value_size));

	स_नकल(buffer,
	       (व्योम *)IFIRST(header) + le16_to_cpu(entry->e_value_offs), len);
	cp_len += len;

out:
	वापस cp_len;
पूर्ण

/*
 * ग_लिखो the buffer to the अंतरभूत inode.
 * If 'create' is set, we don't need to करो the extra copy in the xattr
 * value since it is alपढ़ोy handled by ext4_xattr_ibody_अंतरभूत_set.
 * That saves us one स_नकल.
 */
अटल व्योम ext4_ग_लिखो_अंतरभूत_data(काष्ठा inode *inode, काष्ठा ext4_iloc *iloc,
				   व्योम *buffer, loff_t pos, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ext4_xattr_entry *entry;
	काष्ठा ext4_xattr_ibody_header *header;
	काष्ठा ext4_inode *raw_inode;
	पूर्णांक cp_len = 0;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस;

	BUG_ON(!EXT4_I(inode)->i_अंतरभूत_off);
	BUG_ON(pos + len > EXT4_I(inode)->i_अंतरभूत_size);

	raw_inode = ext4_raw_inode(iloc);
	buffer += pos;

	अगर (pos < EXT4_MIN_INLINE_DATA_SIZE) अणु
		cp_len = pos + len > EXT4_MIN_INLINE_DATA_SIZE ?
			 EXT4_MIN_INLINE_DATA_SIZE - pos : len;
		स_नकल((व्योम *)raw_inode->i_block + pos, buffer, cp_len);

		len -= cp_len;
		buffer += cp_len;
		pos += cp_len;
	पूर्ण

	अगर (!len)
		वापस;

	pos -= EXT4_MIN_INLINE_DATA_SIZE;
	header = IHDR(inode, raw_inode);
	entry = (काष्ठा ext4_xattr_entry *)((व्योम *)raw_inode +
					    EXT4_I(inode)->i_अंतरभूत_off);

	स_नकल((व्योम *)IFIRST(header) + le16_to_cpu(entry->e_value_offs) + pos,
	       buffer, len);
पूर्ण

अटल पूर्णांक ext4_create_अंतरभूत_data(handle_t *handle,
				   काष्ठा inode *inode, अचिन्हित len)
अणु
	पूर्णांक error;
	व्योम *value = शून्य;
	काष्ठा ext4_xattr_ibody_find is = अणु
		.s = अणु .not_found = -ENODATA, पूर्ण,
	पूर्ण;
	काष्ठा ext4_xattr_info i = अणु
		.name_index = EXT4_XATTR_INDEX_SYSTEM,
		.name = EXT4_XATTR_SYSTEM_DATA,
	पूर्ण;

	error = ext4_get_inode_loc(inode, &is.iloc);
	अगर (error)
		वापस error;

	BUFFER_TRACE(is.iloc.bh, "get_write_access");
	error = ext4_journal_get_ग_लिखो_access(handle, is.iloc.bh);
	अगर (error)
		जाओ out;

	अगर (len > EXT4_MIN_INLINE_DATA_SIZE) अणु
		value = EXT4_ZERO_XATTR_VALUE;
		len -= EXT4_MIN_INLINE_DATA_SIZE;
	पूर्ण अन्यथा अणु
		value = "";
		len = 0;
	पूर्ण

	/* Insert the xttr entry. */
	i.value = value;
	i.value_len = len;

	error = ext4_xattr_ibody_find(inode, &i, &is);
	अगर (error)
		जाओ out;

	BUG_ON(!is.s.not_found);

	error = ext4_xattr_ibody_अंतरभूत_set(handle, inode, &i, &is);
	अगर (error) अणु
		अगर (error == -ENOSPC)
			ext4_clear_inode_state(inode,
					       EXT4_STATE_MAY_INLINE_DATA);
		जाओ out;
	पूर्ण

	स_रखो((व्योम *)ext4_raw_inode(&is.iloc)->i_block,
		0, EXT4_MIN_INLINE_DATA_SIZE);

	EXT4_I(inode)->i_अंतरभूत_off = (u16)((व्योम *)is.s.here -
				      (व्योम *)ext4_raw_inode(&is.iloc));
	EXT4_I(inode)->i_अंतरभूत_size = len + EXT4_MIN_INLINE_DATA_SIZE;
	ext4_clear_inode_flag(inode, EXT4_INODE_EXTENTS);
	ext4_set_inode_flag(inode, EXT4_INODE_INLINE_DATA);
	get_bh(is.iloc.bh);
	error = ext4_mark_iloc_dirty(handle, inode, &is.iloc);

out:
	brअन्यथा(is.iloc.bh);
	वापस error;
पूर्ण

अटल पूर्णांक ext4_update_अंतरभूत_data(handle_t *handle, काष्ठा inode *inode,
				   अचिन्हित पूर्णांक len)
अणु
	पूर्णांक error;
	व्योम *value = शून्य;
	काष्ठा ext4_xattr_ibody_find is = अणु
		.s = अणु .not_found = -ENODATA, पूर्ण,
	पूर्ण;
	काष्ठा ext4_xattr_info i = अणु
		.name_index = EXT4_XATTR_INDEX_SYSTEM,
		.name = EXT4_XATTR_SYSTEM_DATA,
	पूर्ण;

	/* If the old space is ok, ग_लिखो the data directly. */
	अगर (len <= EXT4_I(inode)->i_अंतरभूत_size)
		वापस 0;

	error = ext4_get_inode_loc(inode, &is.iloc);
	अगर (error)
		वापस error;

	error = ext4_xattr_ibody_find(inode, &i, &is);
	अगर (error)
		जाओ out;

	BUG_ON(is.s.not_found);

	len -= EXT4_MIN_INLINE_DATA_SIZE;
	value = kzalloc(len, GFP_NOFS);
	अगर (!value) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	error = ext4_xattr_ibody_get(inode, i.name_index, i.name,
				     value, len);
	अगर (error == -ENODATA)
		जाओ out;

	BUFFER_TRACE(is.iloc.bh, "get_write_access");
	error = ext4_journal_get_ग_लिखो_access(handle, is.iloc.bh);
	अगर (error)
		जाओ out;

	/* Update the xattr entry. */
	i.value = value;
	i.value_len = len;

	error = ext4_xattr_ibody_अंतरभूत_set(handle, inode, &i, &is);
	अगर (error)
		जाओ out;

	EXT4_I(inode)->i_अंतरभूत_off = (u16)((व्योम *)is.s.here -
				      (व्योम *)ext4_raw_inode(&is.iloc));
	EXT4_I(inode)->i_अंतरभूत_size = EXT4_MIN_INLINE_DATA_SIZE +
				le32_to_cpu(is.s.here->e_value_size);
	ext4_set_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
	get_bh(is.iloc.bh);
	error = ext4_mark_iloc_dirty(handle, inode, &is.iloc);

out:
	kमुक्त(value);
	brअन्यथा(is.iloc.bh);
	वापस error;
पूर्ण

अटल पूर्णांक ext4_prepare_अंतरभूत_data(handle_t *handle, काष्ठा inode *inode,
				    अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret, size, no_expand;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	अगर (!ext4_test_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA))
		वापस -ENOSPC;

	size = ext4_get_max_अंतरभूत_size(inode);
	अगर (size < len)
		वापस -ENOSPC;

	ext4_ग_लिखो_lock_xattr(inode, &no_expand);

	अगर (ei->i_अंतरभूत_off)
		ret = ext4_update_अंतरभूत_data(handle, inode, len);
	अन्यथा
		ret = ext4_create_अंतरभूत_data(handle, inode, len);

	ext4_ग_लिखो_unlock_xattr(inode, &no_expand);
	वापस ret;
पूर्ण

अटल पूर्णांक ext4_destroy_अंतरभूत_data_nolock(handle_t *handle,
					   काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_xattr_ibody_find is = अणु
		.s = अणु .not_found = 0, पूर्ण,
	पूर्ण;
	काष्ठा ext4_xattr_info i = अणु
		.name_index = EXT4_XATTR_INDEX_SYSTEM,
		.name = EXT4_XATTR_SYSTEM_DATA,
		.value = शून्य,
		.value_len = 0,
	पूर्ण;
	पूर्णांक error;

	अगर (!ei->i_अंतरभूत_off)
		वापस 0;

	error = ext4_get_inode_loc(inode, &is.iloc);
	अगर (error)
		वापस error;

	error = ext4_xattr_ibody_find(inode, &i, &is);
	अगर (error)
		जाओ out;

	BUFFER_TRACE(is.iloc.bh, "get_write_access");
	error = ext4_journal_get_ग_लिखो_access(handle, is.iloc.bh);
	अगर (error)
		जाओ out;

	error = ext4_xattr_ibody_अंतरभूत_set(handle, inode, &i, &is);
	अगर (error)
		जाओ out;

	स_रखो((व्योम *)ext4_raw_inode(&is.iloc)->i_block,
		0, EXT4_MIN_INLINE_DATA_SIZE);
	स_रखो(ei->i_data, 0, EXT4_MIN_INLINE_DATA_SIZE);

	अगर (ext4_has_feature_extents(inode->i_sb)) अणु
		अगर (S_ISसूची(inode->i_mode) ||
		    S_ISREG(inode->i_mode) || S_ISLNK(inode->i_mode)) अणु
			ext4_set_inode_flag(inode, EXT4_INODE_EXTENTS);
			ext4_ext_tree_init(handle, inode);
		पूर्ण
	पूर्ण
	ext4_clear_inode_flag(inode, EXT4_INODE_INLINE_DATA);

	get_bh(is.iloc.bh);
	error = ext4_mark_iloc_dirty(handle, inode, &is.iloc);

	EXT4_I(inode)->i_अंतरभूत_off = 0;
	EXT4_I(inode)->i_अंतरभूत_size = 0;
	ext4_clear_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
out:
	brअन्यथा(is.iloc.bh);
	अगर (error == -ENODATA)
		error = 0;
	वापस error;
पूर्ण

अटल पूर्णांक ext4_पढ़ो_अंतरभूत_page(काष्ठा inode *inode, काष्ठा page *page)
अणु
	व्योम *kaddr;
	पूर्णांक ret = 0;
	माप_प्रकार len;
	काष्ठा ext4_iloc iloc;

	BUG_ON(!PageLocked(page));
	BUG_ON(!ext4_has_अंतरभूत_data(inode));
	BUG_ON(page->index);

	अगर (!EXT4_I(inode)->i_अंतरभूत_off) अणु
		ext4_warning(inode->i_sb, "inode %lu doesn't have inline data.",
			     inode->i_ino);
		जाओ out;
	पूर्ण

	ret = ext4_get_inode_loc(inode, &iloc);
	अगर (ret)
		जाओ out;

	len = min_t(माप_प्रकार, ext4_get_अंतरभूत_size(inode), i_size_पढ़ो(inode));
	kaddr = kmap_atomic(page);
	ret = ext4_पढ़ो_अंतरभूत_data(inode, kaddr, len, &iloc);
	flush_dcache_page(page);
	kunmap_atomic(kaddr);
	zero_user_segment(page, len, PAGE_SIZE);
	SetPageUptodate(page);
	brअन्यथा(iloc.bh);

out:
	वापस ret;
पूर्ण

पूर्णांक ext4_पढ़ोpage_अंतरभूत(काष्ठा inode *inode, काष्ठा page *page)
अणु
	पूर्णांक ret = 0;

	करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);
	अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		up_पढ़ो(&EXT4_I(inode)->xattr_sem);
		वापस -EAGAIN;
	पूर्ण

	/*
	 * Current अंतरभूत data can only exist in the 1st page,
	 * So क्रम all the other pages, just set them uptodate.
	 */
	अगर (!page->index)
		ret = ext4_पढ़ो_अंतरभूत_page(inode, page);
	अन्यथा अगर (!PageUptodate(page)) अणु
		zero_user_segment(page, 0, PAGE_SIZE);
		SetPageUptodate(page);
	पूर्ण

	up_पढ़ो(&EXT4_I(inode)->xattr_sem);

	unlock_page(page);
	वापस ret >= 0 ? 0 : ret;
पूर्ण

अटल पूर्णांक ext4_convert_अंतरभूत_data_to_extent(काष्ठा address_space *mapping,
					      काष्ठा inode *inode,
					      अचिन्हित flags)
अणु
	पूर्णांक ret, needed_blocks, no_expand;
	handle_t *handle = शून्य;
	पूर्णांक retries = 0, sem_held = 0;
	काष्ठा page *page = शून्य;
	अचिन्हित from, to;
	काष्ठा ext4_iloc iloc;

	अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		/*
		 * clear the flag so that no new ग_लिखो
		 * will trap here again.
		 */
		ext4_clear_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
		वापस 0;
	पूर्ण

	needed_blocks = ext4_ग_लिखोpage_trans_blocks(inode);

	ret = ext4_get_inode_loc(inode, &iloc);
	अगर (ret)
		वापस ret;

retry:
	handle = ext4_journal_start(inode, EXT4_HT_WRITE_PAGE, needed_blocks);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		handle = शून्य;
		जाओ out;
	पूर्ण

	/* We cannot recurse पूर्णांकo the fileप्रणाली as the transaction is alपढ़ोy
	 * started */
	flags |= AOP_FLAG_NOFS;

	page = grab_cache_page_ग_लिखो_begin(mapping, 0, flags);
	अगर (!page) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ext4_ग_लिखो_lock_xattr(inode, &no_expand);
	sem_held = 1;
	/* If some one has alपढ़ोy करोne this क्रम us, just निकास. */
	अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	from = 0;
	to = ext4_get_अंतरभूत_size(inode);
	अगर (!PageUptodate(page)) अणु
		ret = ext4_पढ़ो_अंतरभूत_page(inode, page);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = ext4_destroy_अंतरभूत_data_nolock(handle, inode);
	अगर (ret)
		जाओ out;

	अगर (ext4_should_dioपढ़ो_nolock(inode)) अणु
		ret = __block_ग_लिखो_begin(page, from, to,
					  ext4_get_block_unwritten);
	पूर्ण अन्यथा
		ret = __block_ग_लिखो_begin(page, from, to, ext4_get_block);

	अगर (!ret && ext4_should_journal_data(inode)) अणु
		ret = ext4_walk_page_buffers(handle, page_buffers(page),
					     from, to, शून्य,
					     करो_journal_get_ग_लिखो_access);
	पूर्ण

	अगर (ret) अणु
		unlock_page(page);
		put_page(page);
		page = शून्य;
		ext4_orphan_add(handle, inode);
		ext4_ग_लिखो_unlock_xattr(inode, &no_expand);
		sem_held = 0;
		ext4_journal_stop(handle);
		handle = शून्य;
		ext4_truncate_failed_ग_लिखो(inode);
		/*
		 * If truncate failed early the inode might
		 * still be on the orphan list; we need to
		 * make sure the inode is हटाओd from the
		 * orphan list in that हाल.
		 */
		अगर (inode->i_nlink)
			ext4_orphan_del(शून्य, inode);
	पूर्ण

	अगर (ret == -ENOSPC && ext4_should_retry_alloc(inode->i_sb, &retries))
		जाओ retry;

	अगर (page)
		block_commit_ग_लिखो(page, from, to);
out:
	अगर (page) अणु
		unlock_page(page);
		put_page(page);
	पूर्ण
	अगर (sem_held)
		ext4_ग_लिखो_unlock_xattr(inode, &no_expand);
	अगर (handle)
		ext4_journal_stop(handle);
	brअन्यथा(iloc.bh);
	वापस ret;
पूर्ण

/*
 * Try to ग_लिखो data in the inode.
 * If the inode has अंतरभूत data, check whether the new ग_लिखो can be
 * in the inode also. If not, create the page the handle, move the data
 * to the page make it update and let the later codes create extent क्रम it.
 */
पूर्णांक ext4_try_to_ग_लिखो_अंतरभूत_data(काष्ठा address_space *mapping,
				  काष्ठा inode *inode,
				  loff_t pos, अचिन्हित len,
				  अचिन्हित flags,
				  काष्ठा page **pagep)
अणु
	पूर्णांक ret;
	handle_t *handle;
	काष्ठा page *page;
	काष्ठा ext4_iloc iloc;

	अगर (pos + len > ext4_get_max_अंतरभूत_size(inode))
		जाओ convert;

	ret = ext4_get_inode_loc(inode, &iloc);
	अगर (ret)
		वापस ret;

	/*
	 * The possible ग_लिखो could happen in the inode,
	 * so try to reserve the space in inode first.
	 */
	handle = ext4_journal_start(inode, EXT4_HT_INODE, 1);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		handle = शून्य;
		जाओ out;
	पूर्ण

	ret = ext4_prepare_अंतरभूत_data(handle, inode, pos + len);
	अगर (ret && ret != -ENOSPC)
		जाओ out;

	/* We करोn't have space in अंतरभूत inode, so convert it to extent. */
	अगर (ret == -ENOSPC) अणु
		ext4_journal_stop(handle);
		brअन्यथा(iloc.bh);
		जाओ convert;
	पूर्ण

	ret = ext4_journal_get_ग_लिखो_access(handle, iloc.bh);
	अगर (ret)
		जाओ out;

	flags |= AOP_FLAG_NOFS;

	page = grab_cache_page_ग_लिखो_begin(mapping, 0, flags);
	अगर (!page) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	*pagep = page;
	करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);
	अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		ret = 0;
		unlock_page(page);
		put_page(page);
		जाओ out_up_पढ़ो;
	पूर्ण

	अगर (!PageUptodate(page)) अणु
		ret = ext4_पढ़ो_अंतरभूत_page(inode, page);
		अगर (ret < 0) अणु
			unlock_page(page);
			put_page(page);
			जाओ out_up_पढ़ो;
		पूर्ण
	पूर्ण

	ret = 1;
	handle = शून्य;
out_up_पढ़ो:
	up_पढ़ो(&EXT4_I(inode)->xattr_sem);
out:
	अगर (handle && (ret != 1))
		ext4_journal_stop(handle);
	brअन्यथा(iloc.bh);
	वापस ret;
convert:
	वापस ext4_convert_अंतरभूत_data_to_extent(mapping,
						  inode, flags);
पूर्ण

पूर्णांक ext4_ग_लिखो_अंतरभूत_data_end(काष्ठा inode *inode, loff_t pos, अचिन्हित len,
			       अचिन्हित copied, काष्ठा page *page)
अणु
	पूर्णांक ret, no_expand;
	व्योम *kaddr;
	काष्ठा ext4_iloc iloc;

	अगर (unlikely(copied < len)) अणु
		अगर (!PageUptodate(page)) अणु
			copied = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ext4_get_inode_loc(inode, &iloc);
	अगर (ret) अणु
		ext4_std_error(inode->i_sb, ret);
		copied = 0;
		जाओ out;
	पूर्ण

	ext4_ग_लिखो_lock_xattr(inode, &no_expand);
	BUG_ON(!ext4_has_अंतरभूत_data(inode));

	kaddr = kmap_atomic(page);
	ext4_ग_लिखो_अंतरभूत_data(inode, &iloc, kaddr, pos, len);
	kunmap_atomic(kaddr);
	SetPageUptodate(page);
	/* clear page dirty so that ग_लिखोpages wouldn't work क्रम us. */
	ClearPageDirty(page);

	ext4_ग_लिखो_unlock_xattr(inode, &no_expand);
	brअन्यथा(iloc.bh);
	mark_inode_dirty(inode);
out:
	वापस copied;
पूर्ण

काष्ठा buffer_head *
ext4_journalled_ग_लिखो_अंतरभूत_data(काष्ठा inode *inode,
				  अचिन्हित len,
				  काष्ठा page *page)
अणु
	पूर्णांक ret, no_expand;
	व्योम *kaddr;
	काष्ठा ext4_iloc iloc;

	ret = ext4_get_inode_loc(inode, &iloc);
	अगर (ret) अणु
		ext4_std_error(inode->i_sb, ret);
		वापस शून्य;
	पूर्ण

	ext4_ग_लिखो_lock_xattr(inode, &no_expand);
	kaddr = kmap_atomic(page);
	ext4_ग_लिखो_अंतरभूत_data(inode, &iloc, kaddr, 0, len);
	kunmap_atomic(kaddr);
	ext4_ग_लिखो_unlock_xattr(inode, &no_expand);

	वापस iloc.bh;
पूर्ण

/*
 * Try to make the page cache and handle पढ़ोy क्रम the अंतरभूत data हाल.
 * We can call this function in 2 हालs:
 * 1. The inode is created and the first ग_लिखो exceeds अंतरभूत size. We can
 *    clear the inode state safely.
 * 2. The inode has अंतरभूत data, then we need to पढ़ो the data, make it
 *    update and dirty so that ext4_da_ग_लिखोpages can handle it. We करोn't
 *    need to start the journal since the file's metadata isn't changed now.
 */
अटल पूर्णांक ext4_da_convert_अंतरभूत_data_to_extent(काष्ठा address_space *mapping,
						 काष्ठा inode *inode,
						 अचिन्हित flags,
						 व्योम **fsdata)
अणु
	पूर्णांक ret = 0, अंतरभूत_size;
	काष्ठा page *page;

	page = grab_cache_page_ग_लिखो_begin(mapping, 0, flags);
	अगर (!page)
		वापस -ENOMEM;

	करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);
	अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		ext4_clear_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
		जाओ out;
	पूर्ण

	अंतरभूत_size = ext4_get_अंतरभूत_size(inode);

	अगर (!PageUptodate(page)) अणु
		ret = ext4_पढ़ो_अंतरभूत_page(inode, page);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = __block_ग_लिखो_begin(page, 0, अंतरभूत_size,
				  ext4_da_get_block_prep);
	अगर (ret) अणु
		up_पढ़ो(&EXT4_I(inode)->xattr_sem);
		unlock_page(page);
		put_page(page);
		ext4_truncate_failed_ग_लिखो(inode);
		वापस ret;
	पूर्ण

	SetPageDirty(page);
	SetPageUptodate(page);
	ext4_clear_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
	*fsdata = (व्योम *)CONVERT_INLINE_DATA;

out:
	up_पढ़ो(&EXT4_I(inode)->xattr_sem);
	अगर (page) अणु
		unlock_page(page);
		put_page(page);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Prepare the ग_लिखो क्रम the अंतरभूत data.
 * If the data can be written पूर्णांकo the inode, we just पढ़ो
 * the page and make it uptodate, and start the journal.
 * Otherwise पढ़ो the page, makes it dirty so that it can be
 * handle in ग_लिखोpages(the i_disksize update is left to the
 * normal ext4_da_ग_लिखो_end).
 */
पूर्णांक ext4_da_ग_लिखो_अंतरभूत_data_begin(काष्ठा address_space *mapping,
				    काष्ठा inode *inode,
				    loff_t pos, अचिन्हित len,
				    अचिन्हित flags,
				    काष्ठा page **pagep,
				    व्योम **fsdata)
अणु
	पूर्णांक ret, अंतरभूत_size;
	handle_t *handle;
	काष्ठा page *page;
	काष्ठा ext4_iloc iloc;
	पूर्णांक retries = 0;

	ret = ext4_get_inode_loc(inode, &iloc);
	अगर (ret)
		वापस ret;

retry_journal:
	handle = ext4_journal_start(inode, EXT4_HT_INODE, 1);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		जाओ out;
	पूर्ण

	अंतरभूत_size = ext4_get_max_अंतरभूत_size(inode);

	ret = -ENOSPC;
	अगर (अंतरभूत_size >= pos + len) अणु
		ret = ext4_prepare_अंतरभूत_data(handle, inode, pos + len);
		अगर (ret && ret != -ENOSPC)
			जाओ out_journal;
	पूर्ण

	/*
	 * We cannot recurse पूर्णांकo the fileप्रणाली as the transaction
	 * is alपढ़ोy started.
	 */
	flags |= AOP_FLAG_NOFS;

	अगर (ret == -ENOSPC) अणु
		ext4_journal_stop(handle);
		ret = ext4_da_convert_अंतरभूत_data_to_extent(mapping,
							    inode,
							    flags,
							    fsdata);
		अगर (ret == -ENOSPC &&
		    ext4_should_retry_alloc(inode->i_sb, &retries))
			जाओ retry_journal;
		जाओ out;
	पूर्ण

	page = grab_cache_page_ग_लिखो_begin(mapping, 0, flags);
	अगर (!page) अणु
		ret = -ENOMEM;
		जाओ out_journal;
	पूर्ण

	करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);
	अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		ret = 0;
		जाओ out_release_page;
	पूर्ण

	अगर (!PageUptodate(page)) अणु
		ret = ext4_पढ़ो_अंतरभूत_page(inode, page);
		अगर (ret < 0)
			जाओ out_release_page;
	पूर्ण
	ret = ext4_journal_get_ग_लिखो_access(handle, iloc.bh);
	अगर (ret)
		जाओ out_release_page;

	up_पढ़ो(&EXT4_I(inode)->xattr_sem);
	*pagep = page;
	brअन्यथा(iloc.bh);
	वापस 1;
out_release_page:
	up_पढ़ो(&EXT4_I(inode)->xattr_sem);
	unlock_page(page);
	put_page(page);
out_journal:
	ext4_journal_stop(handle);
out:
	brअन्यथा(iloc.bh);
	वापस ret;
पूर्ण

पूर्णांक ext4_da_ग_लिखो_अंतरभूत_data_end(काष्ठा inode *inode, loff_t pos,
				  अचिन्हित len, अचिन्हित copied,
				  काष्ठा page *page)
अणु
	पूर्णांक ret;

	ret = ext4_ग_लिखो_अंतरभूत_data_end(inode, pos, len, copied, page);
	अगर (ret < 0) अणु
		unlock_page(page);
		put_page(page);
		वापस ret;
	पूर्ण
	copied = ret;

	/*
	 * No need to use i_size_पढ़ो() here, the i_size
	 * cannot change under us because we hold i_mutex.
	 *
	 * But it's important to update i_size जबतक still holding page lock:
	 * page ग_लिखोout could otherwise come in and zero beyond i_size.
	 */
	अगर (pos+copied > inode->i_size)
		i_size_ग_लिखो(inode, pos+copied);
	unlock_page(page);
	put_page(page);

	/*
	 * Don't mark the inode dirty under page lock. First, it unnecessarily
	 * makes the holding समय of page lock दीर्घer. Second, it क्रमces lock
	 * ordering of page lock and transaction start क्रम journaling
	 * fileप्रणालीs.
	 */
	mark_inode_dirty(inode);

	वापस copied;
पूर्ण

#अगर_घोषित INLINE_सूची_DEBUG
व्योम ext4_show_अंतरभूत_dir(काष्ठा inode *dir, काष्ठा buffer_head *bh,
			  व्योम *अंतरभूत_start, पूर्णांक अंतरभूत_size)
अणु
	पूर्णांक offset;
	अचिन्हित लघु de_len;
	काष्ठा ext4_dir_entry_2 *de = अंतरभूत_start;
	व्योम *dlimit = अंतरभूत_start + अंतरभूत_size;

	trace_prपूर्णांकk("inode %lu\n", dir->i_ino);
	offset = 0;
	जबतक ((व्योम *)de < dlimit) अणु
		de_len = ext4_rec_len_from_disk(de->rec_len, अंतरभूत_size);
		trace_prपूर्णांकk("de: off %u rlen %u name %.*s nlen %u ino %u\n",
			     offset, de_len, de->name_len, de->name,
			     de->name_len, le32_to_cpu(de->inode));
		अगर (ext4_check_dir_entry(dir, शून्य, de, bh,
					 अंतरभूत_start, अंतरभूत_size, offset))
			BUG();

		offset += de_len;
		de = (काष्ठा ext4_dir_entry_2 *) ((अक्षर *) de + de_len);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा ext4_show_अंतरभूत_dir(dir, bh, अंतरभूत_start, अंतरभूत_size)
#पूर्ण_अगर

/*
 * Add a new entry पूर्णांकo a अंतरभूत dir.
 * It will वापस -ENOSPC अगर no space is available, and -EIO
 * and -EEXIST अगर directory entry alपढ़ोy exists.
 */
अटल पूर्णांक ext4_add_dirent_to_अंतरभूत(handle_t *handle,
				     काष्ठा ext4_filename *fname,
				     काष्ठा inode *dir,
				     काष्ठा inode *inode,
				     काष्ठा ext4_iloc *iloc,
				     व्योम *अंतरभूत_start, पूर्णांक अंतरभूत_size)
अणु
	पूर्णांक		err;
	काष्ठा ext4_dir_entry_2 *de;

	err = ext4_find_dest_de(dir, inode, iloc->bh, अंतरभूत_start,
				अंतरभूत_size, fname, &de);
	अगर (err)
		वापस err;

	BUFFER_TRACE(iloc->bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, iloc->bh);
	अगर (err)
		वापस err;
	ext4_insert_dentry(dir, inode, de, अंतरभूत_size, fname);

	ext4_show_अंतरभूत_dir(dir, iloc->bh, अंतरभूत_start, अंतरभूत_size);

	/*
	 * XXX shouldn't update any बार until successful
	 * completion of syscall, but too many callers depend
	 * on this.
	 *
	 * XXX similarly, too many callers depend on
	 * ext4_new_inode() setting the बार, but error
	 * recovery deletes the inode, so the worst that can
	 * happen is that the बार are slightly out of date
	 * and/or dअगरferent from the directory change समय.
	 */
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	ext4_update_dx_flag(dir);
	inode_inc_iversion(dir);
	वापस 1;
पूर्ण

अटल व्योम *ext4_get_अंतरभूत_xattr_pos(काष्ठा inode *inode,
				       काष्ठा ext4_iloc *iloc)
अणु
	काष्ठा ext4_xattr_entry *entry;
	काष्ठा ext4_xattr_ibody_header *header;

	BUG_ON(!EXT4_I(inode)->i_अंतरभूत_off);

	header = IHDR(inode, ext4_raw_inode(iloc));
	entry = (काष्ठा ext4_xattr_entry *)((व्योम *)ext4_raw_inode(iloc) +
					    EXT4_I(inode)->i_अंतरभूत_off);

	वापस (व्योम *)IFIRST(header) + le16_to_cpu(entry->e_value_offs);
पूर्ण

/* Set the final de to cover the whole block. */
अटल व्योम ext4_update_final_de(व्योम *de_buf, पूर्णांक old_size, पूर्णांक new_size)
अणु
	काष्ठा ext4_dir_entry_2 *de, *prev_de;
	व्योम *limit;
	पूर्णांक de_len;

	de = (काष्ठा ext4_dir_entry_2 *)de_buf;
	अगर (old_size) अणु
		limit = de_buf + old_size;
		करो अणु
			prev_de = de;
			de_len = ext4_rec_len_from_disk(de->rec_len, old_size);
			de_buf += de_len;
			de = (काष्ठा ext4_dir_entry_2 *)de_buf;
		पूर्ण जबतक (de_buf < limit);

		prev_de->rec_len = ext4_rec_len_to_disk(de_len + new_size -
							old_size, new_size);
	पूर्ण अन्यथा अणु
		/* this is just created, so create an empty entry. */
		de->inode = 0;
		de->rec_len = ext4_rec_len_to_disk(new_size, new_size);
	पूर्ण
पूर्ण

अटल पूर्णांक ext4_update_अंतरभूत_dir(handle_t *handle, काष्ठा inode *dir,
				  काष्ठा ext4_iloc *iloc)
अणु
	पूर्णांक ret;
	पूर्णांक old_size = EXT4_I(dir)->i_अंतरभूत_size - EXT4_MIN_INLINE_DATA_SIZE;
	पूर्णांक new_size = get_max_अंतरभूत_xattr_value_size(dir, iloc);

	अगर (new_size - old_size <= ext4_dir_rec_len(1, शून्य))
		वापस -ENOSPC;

	ret = ext4_update_अंतरभूत_data(handle, dir,
				      new_size + EXT4_MIN_INLINE_DATA_SIZE);
	अगर (ret)
		वापस ret;

	ext4_update_final_de(ext4_get_अंतरभूत_xattr_pos(dir, iloc), old_size,
			     EXT4_I(dir)->i_अंतरभूत_size -
						EXT4_MIN_INLINE_DATA_SIZE);
	dir->i_size = EXT4_I(dir)->i_disksize = EXT4_I(dir)->i_अंतरभूत_size;
	वापस 0;
पूर्ण

अटल व्योम ext4_restore_अंतरभूत_data(handle_t *handle, काष्ठा inode *inode,
				     काष्ठा ext4_iloc *iloc,
				     व्योम *buf, पूर्णांक अंतरभूत_size)
अणु
	ext4_create_अंतरभूत_data(handle, inode, अंतरभूत_size);
	ext4_ग_लिखो_अंतरभूत_data(inode, iloc, buf, 0, अंतरभूत_size);
	ext4_set_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
पूर्ण

अटल पूर्णांक ext4_finish_convert_अंतरभूत_dir(handle_t *handle,
					  काष्ठा inode *inode,
					  काष्ठा buffer_head *dir_block,
					  व्योम *buf,
					  पूर्णांक अंतरभूत_size)
अणु
	पूर्णांक err, csum_size = 0, header_size = 0;
	काष्ठा ext4_dir_entry_2 *de;
	व्योम *target = dir_block->b_data;

	/*
	 * First create "." and ".." and then copy the dir inक्रमmation
	 * back to the block.
	 */
	de = (काष्ठा ext4_dir_entry_2 *)target;
	de = ext4_init_करोt_करोtकरोt(inode, de,
		inode->i_sb->s_blocksize, csum_size,
		le32_to_cpu(((काष्ठा ext4_dir_entry_2 *)buf)->inode), 1);
	header_size = (व्योम *)de - target;

	स_नकल((व्योम *)de, buf + EXT4_INLINE_DOTDOT_SIZE,
		अंतरभूत_size - EXT4_INLINE_DOTDOT_SIZE);

	अगर (ext4_has_metadata_csum(inode->i_sb))
		csum_size = माप(काष्ठा ext4_dir_entry_tail);

	inode->i_size = inode->i_sb->s_blocksize;
	i_size_ग_लिखो(inode, inode->i_sb->s_blocksize);
	EXT4_I(inode)->i_disksize = inode->i_sb->s_blocksize;
	ext4_update_final_de(dir_block->b_data,
			अंतरभूत_size - EXT4_INLINE_DOTDOT_SIZE + header_size,
			inode->i_sb->s_blocksize - csum_size);

	अगर (csum_size)
		ext4_initialize_dirent_tail(dir_block,
					    inode->i_sb->s_blocksize);
	set_buffer_uptodate(dir_block);
	err = ext4_handle_dirty_dirblock(handle, inode, dir_block);
	अगर (err)
		वापस err;
	set_buffer_verअगरied(dir_block);
	वापस ext4_mark_inode_dirty(handle, inode);
पूर्ण

अटल पूर्णांक ext4_convert_अंतरभूत_data_nolock(handle_t *handle,
					   काष्ठा inode *inode,
					   काष्ठा ext4_iloc *iloc)
अणु
	पूर्णांक error;
	व्योम *buf = शून्य;
	काष्ठा buffer_head *data_bh = शून्य;
	काष्ठा ext4_map_blocks map;
	पूर्णांक अंतरभूत_size;

	अंतरभूत_size = ext4_get_अंतरभूत_size(inode);
	buf = kदो_स्मृति(अंतरभूत_size, GFP_NOFS);
	अगर (!buf) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	error = ext4_पढ़ो_अंतरभूत_data(inode, buf, अंतरभूत_size, iloc);
	अगर (error < 0)
		जाओ out;

	/*
	 * Make sure the अंतरभूत directory entries pass checks beक्रमe we try to
	 * convert them, so that we aव्योम touching stuff that needs fsck.
	 */
	अगर (S_ISसूची(inode->i_mode)) अणु
		error = ext4_check_all_de(inode, iloc->bh,
					buf + EXT4_INLINE_DOTDOT_SIZE,
					अंतरभूत_size - EXT4_INLINE_DOTDOT_SIZE);
		अगर (error)
			जाओ out;
	पूर्ण

	error = ext4_destroy_अंतरभूत_data_nolock(handle, inode);
	अगर (error)
		जाओ out;

	map.m_lblk = 0;
	map.m_len = 1;
	map.m_flags = 0;
	error = ext4_map_blocks(handle, inode, &map, EXT4_GET_BLOCKS_CREATE);
	अगर (error < 0)
		जाओ out_restore;
	अगर (!(map.m_flags & EXT4_MAP_MAPPED)) अणु
		error = -EIO;
		जाओ out_restore;
	पूर्ण

	data_bh = sb_getblk(inode->i_sb, map.m_pblk);
	अगर (!data_bh) अणु
		error = -ENOMEM;
		जाओ out_restore;
	पूर्ण

	lock_buffer(data_bh);
	error = ext4_journal_get_create_access(handle, data_bh);
	अगर (error) अणु
		unlock_buffer(data_bh);
		error = -EIO;
		जाओ out_restore;
	पूर्ण
	स_रखो(data_bh->b_data, 0, inode->i_sb->s_blocksize);

	अगर (!S_ISसूची(inode->i_mode)) अणु
		स_नकल(data_bh->b_data, buf, अंतरभूत_size);
		set_buffer_uptodate(data_bh);
		error = ext4_handle_dirty_metadata(handle,
						   inode, data_bh);
	पूर्ण अन्यथा अणु
		error = ext4_finish_convert_अंतरभूत_dir(handle, inode, data_bh,
						       buf, अंतरभूत_size);
	पूर्ण

	unlock_buffer(data_bh);
out_restore:
	अगर (error)
		ext4_restore_अंतरभूत_data(handle, inode, iloc, buf, अंतरभूत_size);

out:
	brअन्यथा(data_bh);
	kमुक्त(buf);
	वापस error;
पूर्ण

/*
 * Try to add the new entry to the अंतरभूत data.
 * If succeeds, वापस 0. If not, extended the अंतरभूत dir and copied data to
 * the new created block.
 */
पूर्णांक ext4_try_add_अंतरभूत_entry(handle_t *handle, काष्ठा ext4_filename *fname,
			      काष्ठा inode *dir, काष्ठा inode *inode)
अणु
	पूर्णांक ret, ret2, अंतरभूत_size, no_expand;
	व्योम *अंतरभूत_start;
	काष्ठा ext4_iloc iloc;

	ret = ext4_get_inode_loc(dir, &iloc);
	अगर (ret)
		वापस ret;

	ext4_ग_लिखो_lock_xattr(dir, &no_expand);
	अगर (!ext4_has_अंतरभूत_data(dir))
		जाओ out;

	अंतरभूत_start = (व्योम *)ext4_raw_inode(&iloc)->i_block +
						 EXT4_INLINE_DOTDOT_SIZE;
	अंतरभूत_size = EXT4_MIN_INLINE_DATA_SIZE - EXT4_INLINE_DOTDOT_SIZE;

	ret = ext4_add_dirent_to_अंतरभूत(handle, fname, dir, inode, &iloc,
					अंतरभूत_start, अंतरभूत_size);
	अगर (ret != -ENOSPC)
		जाओ out;

	/* check whether it can be inserted to अंतरभूत xattr space. */
	अंतरभूत_size = EXT4_I(dir)->i_अंतरभूत_size -
			EXT4_MIN_INLINE_DATA_SIZE;
	अगर (!अंतरभूत_size) अणु
		/* Try to use the xattr space.*/
		ret = ext4_update_अंतरभूत_dir(handle, dir, &iloc);
		अगर (ret && ret != -ENOSPC)
			जाओ out;

		अंतरभूत_size = EXT4_I(dir)->i_अंतरभूत_size -
				EXT4_MIN_INLINE_DATA_SIZE;
	पूर्ण

	अगर (अंतरभूत_size) अणु
		अंतरभूत_start = ext4_get_अंतरभूत_xattr_pos(dir, &iloc);

		ret = ext4_add_dirent_to_अंतरभूत(handle, fname, dir,
						inode, &iloc, अंतरभूत_start,
						अंतरभूत_size);

		अगर (ret != -ENOSPC)
			जाओ out;
	पूर्ण

	/*
	 * The अंतरभूत space is filled up, so create a new block क्रम it.
	 * As the extent tree will be created, we have to save the अंतरभूत
	 * dir first.
	 */
	ret = ext4_convert_अंतरभूत_data_nolock(handle, dir, &iloc);

out:
	ext4_ग_लिखो_unlock_xattr(dir, &no_expand);
	ret2 = ext4_mark_inode_dirty(handle, dir);
	अगर (unlikely(ret2 && !ret))
		ret = ret2;
	brअन्यथा(iloc.bh);
	वापस ret;
पूर्ण

/*
 * This function fills a red-black tree with inक्रमmation from an
 * अंतरभूतd dir.  It वापसs the number directory entries loaded
 * पूर्णांकo the tree.  If there is an error it is वापसed in err.
 */
पूर्णांक ext4_अंतरभूतdir_to_tree(काष्ठा file *dir_file,
			   काष्ठा inode *dir, ext4_lblk_t block,
			   काष्ठा dx_hash_info *hinfo,
			   __u32 start_hash, __u32 start_minor_hash,
			   पूर्णांक *has_अंतरभूत_data)
अणु
	पूर्णांक err = 0, count = 0;
	अचिन्हित पूर्णांक parent_ino;
	पूर्णांक pos;
	काष्ठा ext4_dir_entry_2 *de;
	काष्ठा inode *inode = file_inode(dir_file);
	पूर्णांक ret, अंतरभूत_size = 0;
	काष्ठा ext4_iloc iloc;
	व्योम *dir_buf = शून्य;
	काष्ठा ext4_dir_entry_2 fake;
	काष्ठा fscrypt_str पंचांगp_str;

	ret = ext4_get_inode_loc(inode, &iloc);
	अगर (ret)
		वापस ret;

	करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);
	अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		up_पढ़ो(&EXT4_I(inode)->xattr_sem);
		*has_अंतरभूत_data = 0;
		जाओ out;
	पूर्ण

	अंतरभूत_size = ext4_get_अंतरभूत_size(inode);
	dir_buf = kदो_स्मृति(अंतरभूत_size, GFP_NOFS);
	अगर (!dir_buf) अणु
		ret = -ENOMEM;
		up_पढ़ो(&EXT4_I(inode)->xattr_sem);
		जाओ out;
	पूर्ण

	ret = ext4_पढ़ो_अंतरभूत_data(inode, dir_buf, अंतरभूत_size, &iloc);
	up_पढ़ो(&EXT4_I(inode)->xattr_sem);
	अगर (ret < 0)
		जाओ out;

	pos = 0;
	parent_ino = le32_to_cpu(((काष्ठा ext4_dir_entry_2 *)dir_buf)->inode);
	जबतक (pos < अंतरभूत_size) अणु
		/*
		 * As अंतरभूतd dir करोesn't store any information about '.' and
		 * only the inode number of '..' is stored, we have to handle
		 * them dअगरferently.
		 */
		अगर (pos == 0) अणु
			fake.inode = cpu_to_le32(inode->i_ino);
			fake.name_len = 1;
			म_नकल(fake.name, ".");
			fake.rec_len = ext4_rec_len_to_disk(
					  ext4_dir_rec_len(fake.name_len, शून्य),
					  अंतरभूत_size);
			ext4_set_de_type(inode->i_sb, &fake, S_IFसूची);
			de = &fake;
			pos = EXT4_INLINE_DOTDOT_OFFSET;
		पूर्ण अन्यथा अगर (pos == EXT4_INLINE_DOTDOT_OFFSET) अणु
			fake.inode = cpu_to_le32(parent_ino);
			fake.name_len = 2;
			म_नकल(fake.name, "..");
			fake.rec_len = ext4_rec_len_to_disk(
					  ext4_dir_rec_len(fake.name_len, शून्य),
					  अंतरभूत_size);
			ext4_set_de_type(inode->i_sb, &fake, S_IFसूची);
			de = &fake;
			pos = EXT4_INLINE_DOTDOT_SIZE;
		पूर्ण अन्यथा अणु
			de = (काष्ठा ext4_dir_entry_2 *)(dir_buf + pos);
			pos += ext4_rec_len_from_disk(de->rec_len, अंतरभूत_size);
			अगर (ext4_check_dir_entry(inode, dir_file, de,
					 iloc.bh, dir_buf,
					 अंतरभूत_size, pos)) अणु
				ret = count;
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (ext4_hash_in_dirent(dir)) अणु
			hinfo->hash = EXT4_सूचीENT_HASH(de);
			hinfo->minor_hash = EXT4_सूचीENT_MINOR_HASH(de);
		पूर्ण अन्यथा अणु
			ext4fs_dirhash(dir, de->name, de->name_len, hinfo);
		पूर्ण
		अगर ((hinfo->hash < start_hash) ||
		    ((hinfo->hash == start_hash) &&
		     (hinfo->minor_hash < start_minor_hash)))
			जारी;
		अगर (de->inode == 0)
			जारी;
		पंचांगp_str.name = de->name;
		पंचांगp_str.len = de->name_len;
		err = ext4_htree_store_dirent(dir_file, hinfo->hash,
					      hinfo->minor_hash, de, &पंचांगp_str);
		अगर (err) अणु
			ret = err;
			जाओ out;
		पूर्ण
		count++;
	पूर्ण
	ret = count;
out:
	kमुक्त(dir_buf);
	brअन्यथा(iloc.bh);
	वापस ret;
पूर्ण

/*
 * So this function is called when the volume is mkfsed with
 * dir_index disabled. In order to keep f_pos persistent
 * after we convert from an अंतरभूतd dir to a blocked based,
 * we just pretend that we are a normal dir and वापस the
 * offset as अगर '.' and '..' really take place.
 *
 */
पूर्णांक ext4_पढ़ो_अंतरभूत_dir(काष्ठा file *file,
			 काष्ठा dir_context *ctx,
			 पूर्णांक *has_अंतरभूत_data)
अणु
	अचिन्हित पूर्णांक offset, parent_ino;
	पूर्णांक i;
	काष्ठा ext4_dir_entry_2 *de;
	काष्ठा super_block *sb;
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक ret, अंतरभूत_size = 0;
	काष्ठा ext4_iloc iloc;
	व्योम *dir_buf = शून्य;
	पूर्णांक करोtकरोt_offset, करोtकरोt_size, extra_offset, extra_size;

	ret = ext4_get_inode_loc(inode, &iloc);
	अगर (ret)
		वापस ret;

	करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);
	अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		up_पढ़ो(&EXT4_I(inode)->xattr_sem);
		*has_अंतरभूत_data = 0;
		जाओ out;
	पूर्ण

	अंतरभूत_size = ext4_get_अंतरभूत_size(inode);
	dir_buf = kदो_स्मृति(अंतरभूत_size, GFP_NOFS);
	अगर (!dir_buf) अणु
		ret = -ENOMEM;
		up_पढ़ो(&EXT4_I(inode)->xattr_sem);
		जाओ out;
	पूर्ण

	ret = ext4_पढ़ो_अंतरभूत_data(inode, dir_buf, अंतरभूत_size, &iloc);
	up_पढ़ो(&EXT4_I(inode)->xattr_sem);
	अगर (ret < 0)
		जाओ out;

	ret = 0;
	sb = inode->i_sb;
	parent_ino = le32_to_cpu(((काष्ठा ext4_dir_entry_2 *)dir_buf)->inode);
	offset = ctx->pos;

	/*
	 * करोtकरोt_offset and करोtकरोt_size is the real offset and
	 * size क्रम ".." and "." अगर the dir is block based जबतक
	 * the real size क्रम them are only EXT4_INLINE_DOTDOT_SIZE.
	 * So we will use extra_offset and extra_size to indicate them
	 * during the अंतरभूत dir iteration.
	 */
	करोtकरोt_offset = ext4_dir_rec_len(1, शून्य);
	करोtकरोt_size = करोtकरोt_offset + ext4_dir_rec_len(2, शून्य);
	extra_offset = करोtकरोt_size - EXT4_INLINE_DOTDOT_SIZE;
	extra_size = extra_offset + अंतरभूत_size;

	/*
	 * If the version has changed since the last call to
	 * सूची_पढ़ो(2), then we might be poपूर्णांकing to an invalid
	 * dirent right now.  Scan from the start of the अंतरभूत
	 * dir to make sure.
	 */
	अगर (!inode_eq_iversion(inode, file->f_version)) अणु
		क्रम (i = 0; i < extra_size && i < offset;) अणु
			/*
			 * "." is with offset 0 and
			 * ".." is करोtकरोt_offset.
			 */
			अगर (!i) अणु
				i = करोtकरोt_offset;
				जारी;
			पूर्ण अन्यथा अगर (i == करोtकरोt_offset) अणु
				i = करोtकरोt_size;
				जारी;
			पूर्ण
			/* क्रम other entry, the real offset in
			 * the buf has to be tuned accordingly.
			 */
			de = (काष्ठा ext4_dir_entry_2 *)
				(dir_buf + i - extra_offset);
			/* It's too expensive to करो a full
			 * dirent test each समय round this
			 * loop, but we करो have to test at
			 * least that it is non-zero.  A
			 * failure will be detected in the
			 * dirent test below. */
			अगर (ext4_rec_len_from_disk(de->rec_len, extra_size)
				< ext4_dir_rec_len(1, शून्य))
				अवरोध;
			i += ext4_rec_len_from_disk(de->rec_len,
						    extra_size);
		पूर्ण
		offset = i;
		ctx->pos = offset;
		file->f_version = inode_query_iversion(inode);
	पूर्ण

	जबतक (ctx->pos < extra_size) अणु
		अगर (ctx->pos == 0) अणु
			अगर (!dir_emit(ctx, ".", 1, inode->i_ino, DT_सूची))
				जाओ out;
			ctx->pos = करोtकरोt_offset;
			जारी;
		पूर्ण

		अगर (ctx->pos == करोtकरोt_offset) अणु
			अगर (!dir_emit(ctx, "..", 2, parent_ino, DT_सूची))
				जाओ out;
			ctx->pos = करोtकरोt_size;
			जारी;
		पूर्ण

		de = (काष्ठा ext4_dir_entry_2 *)
			(dir_buf + ctx->pos - extra_offset);
		अगर (ext4_check_dir_entry(inode, file, de, iloc.bh, dir_buf,
					 extra_size, ctx->pos))
			जाओ out;
		अगर (le32_to_cpu(de->inode)) अणु
			अगर (!dir_emit(ctx, de->name, de->name_len,
				      le32_to_cpu(de->inode),
				      get_dtype(sb, de->file_type)))
				जाओ out;
		पूर्ण
		ctx->pos += ext4_rec_len_from_disk(de->rec_len, extra_size);
	पूर्ण
out:
	kमुक्त(dir_buf);
	brअन्यथा(iloc.bh);
	वापस ret;
पूर्ण

काष्ठा buffer_head *ext4_get_first_अंतरभूत_block(काष्ठा inode *inode,
					काष्ठा ext4_dir_entry_2 **parent_de,
					पूर्णांक *retval)
अणु
	काष्ठा ext4_iloc iloc;

	*retval = ext4_get_inode_loc(inode, &iloc);
	अगर (*retval)
		वापस शून्य;

	*parent_de = (काष्ठा ext4_dir_entry_2 *)ext4_raw_inode(&iloc)->i_block;

	वापस iloc.bh;
पूर्ण

/*
 * Try to create the अंतरभूत data क्रम the new dir.
 * If it succeeds, वापस 0, otherwise वापस the error.
 * In हाल of ENOSPC, the caller should create the normal disk layout dir.
 */
पूर्णांक ext4_try_create_अंतरभूत_dir(handle_t *handle, काष्ठा inode *parent,
			       काष्ठा inode *inode)
अणु
	पूर्णांक ret, अंतरभूत_size = EXT4_MIN_INLINE_DATA_SIZE;
	काष्ठा ext4_iloc iloc;
	काष्ठा ext4_dir_entry_2 *de;

	ret = ext4_get_inode_loc(inode, &iloc);
	अगर (ret)
		वापस ret;

	ret = ext4_prepare_अंतरभूत_data(handle, inode, अंतरभूत_size);
	अगर (ret)
		जाओ out;

	/*
	 * For अंतरभूत dir, we only save the inode inक्रमmation क्रम the ".."
	 * and create a fake dentry to cover the left space.
	 */
	de = (काष्ठा ext4_dir_entry_2 *)ext4_raw_inode(&iloc)->i_block;
	de->inode = cpu_to_le32(parent->i_ino);
	de = (काष्ठा ext4_dir_entry_2 *)((व्योम *)de + EXT4_INLINE_DOTDOT_SIZE);
	de->inode = 0;
	de->rec_len = ext4_rec_len_to_disk(
				अंतरभूत_size - EXT4_INLINE_DOTDOT_SIZE,
				अंतरभूत_size);
	set_nlink(inode, 2);
	inode->i_size = EXT4_I(inode)->i_disksize = अंतरभूत_size;
out:
	brअन्यथा(iloc.bh);
	वापस ret;
पूर्ण

काष्ठा buffer_head *ext4_find_अंतरभूत_entry(काष्ठा inode *dir,
					काष्ठा ext4_filename *fname,
					काष्ठा ext4_dir_entry_2 **res_dir,
					पूर्णांक *has_अंतरभूत_data)
अणु
	पूर्णांक ret;
	काष्ठा ext4_iloc iloc;
	व्योम *अंतरभूत_start;
	पूर्णांक अंतरभूत_size;

	अगर (ext4_get_inode_loc(dir, &iloc))
		वापस शून्य;

	करोwn_पढ़ो(&EXT4_I(dir)->xattr_sem);
	अगर (!ext4_has_अंतरभूत_data(dir)) अणु
		*has_अंतरभूत_data = 0;
		जाओ out;
	पूर्ण

	अंतरभूत_start = (व्योम *)ext4_raw_inode(&iloc)->i_block +
						EXT4_INLINE_DOTDOT_SIZE;
	अंतरभूत_size = EXT4_MIN_INLINE_DATA_SIZE - EXT4_INLINE_DOTDOT_SIZE;
	ret = ext4_search_dir(iloc.bh, अंतरभूत_start, अंतरभूत_size,
			      dir, fname, 0, res_dir);
	अगर (ret == 1)
		जाओ out_find;
	अगर (ret < 0)
		जाओ out;

	अगर (ext4_get_अंतरभूत_size(dir) == EXT4_MIN_INLINE_DATA_SIZE)
		जाओ out;

	अंतरभूत_start = ext4_get_अंतरभूत_xattr_pos(dir, &iloc);
	अंतरभूत_size = ext4_get_अंतरभूत_size(dir) - EXT4_MIN_INLINE_DATA_SIZE;

	ret = ext4_search_dir(iloc.bh, अंतरभूत_start, अंतरभूत_size,
			      dir, fname, 0, res_dir);
	अगर (ret == 1)
		जाओ out_find;

out:
	brअन्यथा(iloc.bh);
	iloc.bh = शून्य;
out_find:
	up_पढ़ो(&EXT4_I(dir)->xattr_sem);
	वापस iloc.bh;
पूर्ण

पूर्णांक ext4_delete_अंतरभूत_entry(handle_t *handle,
			     काष्ठा inode *dir,
			     काष्ठा ext4_dir_entry_2 *de_del,
			     काष्ठा buffer_head *bh,
			     पूर्णांक *has_अंतरभूत_data)
अणु
	पूर्णांक err, अंतरभूत_size, no_expand;
	काष्ठा ext4_iloc iloc;
	व्योम *अंतरभूत_start;

	err = ext4_get_inode_loc(dir, &iloc);
	अगर (err)
		वापस err;

	ext4_ग_लिखो_lock_xattr(dir, &no_expand);
	अगर (!ext4_has_अंतरभूत_data(dir)) अणु
		*has_अंतरभूत_data = 0;
		जाओ out;
	पूर्ण

	अगर ((व्योम *)de_del - ((व्योम *)ext4_raw_inode(&iloc)->i_block) <
		EXT4_MIN_INLINE_DATA_SIZE) अणु
		अंतरभूत_start = (व्योम *)ext4_raw_inode(&iloc)->i_block +
					EXT4_INLINE_DOTDOT_SIZE;
		अंतरभूत_size = EXT4_MIN_INLINE_DATA_SIZE -
				EXT4_INLINE_DOTDOT_SIZE;
	पूर्ण अन्यथा अणु
		अंतरभूत_start = ext4_get_अंतरभूत_xattr_pos(dir, &iloc);
		अंतरभूत_size = ext4_get_अंतरभूत_size(dir) -
				EXT4_MIN_INLINE_DATA_SIZE;
	पूर्ण

	BUFFER_TRACE(bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, bh);
	अगर (err)
		जाओ out;

	err = ext4_generic_delete_entry(dir, de_del, bh,
					अंतरभूत_start, अंतरभूत_size, 0);
	अगर (err)
		जाओ out;

	ext4_show_अंतरभूत_dir(dir, iloc.bh, अंतरभूत_start, अंतरभूत_size);
out:
	ext4_ग_लिखो_unlock_xattr(dir, &no_expand);
	अगर (likely(err == 0))
		err = ext4_mark_inode_dirty(handle, dir);
	brअन्यथा(iloc.bh);
	अगर (err != -ENOENT)
		ext4_std_error(dir->i_sb, err);
	वापस err;
पूर्ण

/*
 * Get the अंतरभूत dentry at offset.
 */
अटल अंतरभूत काष्ठा ext4_dir_entry_2 *
ext4_get_अंतरभूत_entry(काष्ठा inode *inode,
		      काष्ठा ext4_iloc *iloc,
		      अचिन्हित पूर्णांक offset,
		      व्योम **अंतरभूत_start,
		      पूर्णांक *अंतरभूत_size)
अणु
	व्योम *अंतरभूत_pos;

	BUG_ON(offset > ext4_get_अंतरभूत_size(inode));

	अगर (offset < EXT4_MIN_INLINE_DATA_SIZE) अणु
		अंतरभूत_pos = (व्योम *)ext4_raw_inode(iloc)->i_block;
		*अंतरभूत_size = EXT4_MIN_INLINE_DATA_SIZE;
	पूर्ण अन्यथा अणु
		अंतरभूत_pos = ext4_get_अंतरभूत_xattr_pos(inode, iloc);
		offset -= EXT4_MIN_INLINE_DATA_SIZE;
		*अंतरभूत_size = ext4_get_अंतरभूत_size(inode) -
				EXT4_MIN_INLINE_DATA_SIZE;
	पूर्ण

	अगर (अंतरभूत_start)
		*अंतरभूत_start = अंतरभूत_pos;
	वापस (काष्ठा ext4_dir_entry_2 *)(अंतरभूत_pos + offset);
पूर्ण

bool empty_अंतरभूत_dir(काष्ठा inode *dir, पूर्णांक *has_अंतरभूत_data)
अणु
	पूर्णांक err, अंतरभूत_size;
	काष्ठा ext4_iloc iloc;
	माप_प्रकार अंतरभूत_len;
	व्योम *अंतरभूत_pos;
	अचिन्हित पूर्णांक offset;
	काष्ठा ext4_dir_entry_2 *de;
	bool ret = true;

	err = ext4_get_inode_loc(dir, &iloc);
	अगर (err) अणु
		EXT4_ERROR_INODE_ERR(dir, -err,
				     "error %d getting inode %lu block",
				     err, dir->i_ino);
		वापस true;
	पूर्ण

	करोwn_पढ़ो(&EXT4_I(dir)->xattr_sem);
	अगर (!ext4_has_अंतरभूत_data(dir)) अणु
		*has_अंतरभूत_data = 0;
		जाओ out;
	पूर्ण

	de = (काष्ठा ext4_dir_entry_2 *)ext4_raw_inode(&iloc)->i_block;
	अगर (!le32_to_cpu(de->inode)) अणु
		ext4_warning(dir->i_sb,
			     "bad inline directory (dir #%lu) - no `..'",
			     dir->i_ino);
		ret = true;
		जाओ out;
	पूर्ण

	अंतरभूत_len = ext4_get_अंतरभूत_size(dir);
	offset = EXT4_INLINE_DOTDOT_SIZE;
	जबतक (offset < अंतरभूत_len) अणु
		de = ext4_get_अंतरभूत_entry(dir, &iloc, offset,
					   &अंतरभूत_pos, &अंतरभूत_size);
		अगर (ext4_check_dir_entry(dir, शून्य, de,
					 iloc.bh, अंतरभूत_pos,
					 अंतरभूत_size, offset)) अणु
			ext4_warning(dir->i_sb,
				     "bad inline directory (dir #%lu) - "
				     "inode %u, rec_len %u, name_len %d"
				     "inline size %d",
				     dir->i_ino, le32_to_cpu(de->inode),
				     le16_to_cpu(de->rec_len), de->name_len,
				     अंतरभूत_size);
			ret = true;
			जाओ out;
		पूर्ण
		अगर (le32_to_cpu(de->inode)) अणु
			ret = false;
			जाओ out;
		पूर्ण
		offset += ext4_rec_len_from_disk(de->rec_len, अंतरभूत_size);
	पूर्ण

out:
	up_पढ़ो(&EXT4_I(dir)->xattr_sem);
	brअन्यथा(iloc.bh);
	वापस ret;
पूर्ण

पूर्णांक ext4_destroy_अंतरभूत_data(handle_t *handle, काष्ठा inode *inode)
अणु
	पूर्णांक ret, no_expand;

	ext4_ग_लिखो_lock_xattr(inode, &no_expand);
	ret = ext4_destroy_अंतरभूत_data_nolock(handle, inode);
	ext4_ग_लिखो_unlock_xattr(inode, &no_expand);

	वापस ret;
पूर्ण

पूर्णांक ext4_अंतरभूत_data_iomap(काष्ठा inode *inode, काष्ठा iomap *iomap)
अणु
	__u64 addr;
	पूर्णांक error = -EAGAIN;
	काष्ठा ext4_iloc iloc;

	करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);
	अगर (!ext4_has_अंतरभूत_data(inode))
		जाओ out;

	error = ext4_get_inode_loc(inode, &iloc);
	अगर (error)
		जाओ out;

	addr = (__u64)iloc.bh->b_blocknr << inode->i_sb->s_blocksize_bits;
	addr += (अक्षर *)ext4_raw_inode(&iloc) - iloc.bh->b_data;
	addr += दुरत्व(काष्ठा ext4_inode, i_block);

	brअन्यथा(iloc.bh);

	iomap->addr = addr;
	iomap->offset = 0;
	iomap->length = min_t(loff_t, ext4_get_अंतरभूत_size(inode),
			      i_size_पढ़ो(inode));
	iomap->type = IOMAP_INLINE;
	iomap->flags = 0;

out:
	up_पढ़ो(&EXT4_I(inode)->xattr_sem);
	वापस error;
पूर्ण

पूर्णांक ext4_अंतरभूत_data_truncate(काष्ठा inode *inode, पूर्णांक *has_अंतरभूत)
अणु
	handle_t *handle;
	पूर्णांक अंतरभूत_size, value_len, needed_blocks, no_expand, err = 0;
	माप_प्रकार i_size;
	व्योम *value = शून्य;
	काष्ठा ext4_xattr_ibody_find is = अणु
		.s = अणु .not_found = -ENODATA, पूर्ण,
	पूर्ण;
	काष्ठा ext4_xattr_info i = अणु
		.name_index = EXT4_XATTR_INDEX_SYSTEM,
		.name = EXT4_XATTR_SYSTEM_DATA,
	पूर्ण;


	needed_blocks = ext4_ग_लिखोpage_trans_blocks(inode);
	handle = ext4_journal_start(inode, EXT4_HT_INODE, needed_blocks);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	ext4_ग_लिखो_lock_xattr(inode, &no_expand);
	अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		ext4_ग_लिखो_unlock_xattr(inode, &no_expand);
		*has_अंतरभूत = 0;
		ext4_journal_stop(handle);
		वापस 0;
	पूर्ण

	अगर ((err = ext4_orphan_add(handle, inode)) != 0)
		जाओ out;

	अगर ((err = ext4_get_inode_loc(inode, &is.iloc)) != 0)
		जाओ out;

	करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	i_size = inode->i_size;
	अंतरभूत_size = ext4_get_अंतरभूत_size(inode);
	EXT4_I(inode)->i_disksize = i_size;

	अगर (i_size < अंतरभूत_size) अणु
		/* Clear the content in the xattr space. */
		अगर (अंतरभूत_size > EXT4_MIN_INLINE_DATA_SIZE) अणु
			अगर ((err = ext4_xattr_ibody_find(inode, &i, &is)) != 0)
				जाओ out_error;

			BUG_ON(is.s.not_found);

			value_len = le32_to_cpu(is.s.here->e_value_size);
			value = kदो_स्मृति(value_len, GFP_NOFS);
			अगर (!value) अणु
				err = -ENOMEM;
				जाओ out_error;
			पूर्ण

			err = ext4_xattr_ibody_get(inode, i.name_index,
						   i.name, value, value_len);
			अगर (err <= 0)
				जाओ out_error;

			i.value = value;
			i.value_len = i_size > EXT4_MIN_INLINE_DATA_SIZE ?
					i_size - EXT4_MIN_INLINE_DATA_SIZE : 0;
			err = ext4_xattr_ibody_अंतरभूत_set(handle, inode,
							  &i, &is);
			अगर (err)
				जाओ out_error;
		पूर्ण

		/* Clear the content within i_blocks. */
		अगर (i_size < EXT4_MIN_INLINE_DATA_SIZE) अणु
			व्योम *p = (व्योम *) ext4_raw_inode(&is.iloc)->i_block;
			स_रखो(p + i_size, 0,
			       EXT4_MIN_INLINE_DATA_SIZE - i_size);
		पूर्ण

		EXT4_I(inode)->i_अंतरभूत_size = i_size <
					EXT4_MIN_INLINE_DATA_SIZE ?
					EXT4_MIN_INLINE_DATA_SIZE : i_size;
	पूर्ण

out_error:
	up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
out:
	brअन्यथा(is.iloc.bh);
	ext4_ग_लिखो_unlock_xattr(inode, &no_expand);
	kमुक्त(value);
	अगर (inode->i_nlink)
		ext4_orphan_del(handle, inode);

	अगर (err == 0) अणु
		inode->i_mसमय = inode->i_स_समय = current_समय(inode);
		err = ext4_mark_inode_dirty(handle, inode);
		अगर (IS_SYNC(inode))
			ext4_handle_sync(handle);
	पूर्ण
	ext4_journal_stop(handle);
	वापस err;
पूर्ण

पूर्णांक ext4_convert_अंतरभूत_data(काष्ठा inode *inode)
अणु
	पूर्णांक error, needed_blocks, no_expand;
	handle_t *handle;
	काष्ठा ext4_iloc iloc;

	अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		ext4_clear_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
		वापस 0;
	पूर्ण

	needed_blocks = ext4_ग_लिखोpage_trans_blocks(inode);

	iloc.bh = शून्य;
	error = ext4_get_inode_loc(inode, &iloc);
	अगर (error)
		वापस error;

	handle = ext4_journal_start(inode, EXT4_HT_WRITE_PAGE, needed_blocks);
	अगर (IS_ERR(handle)) अणु
		error = PTR_ERR(handle);
		जाओ out_मुक्त;
	पूर्ण

	ext4_ग_लिखो_lock_xattr(inode, &no_expand);
	अगर (ext4_has_अंतरभूत_data(inode))
		error = ext4_convert_अंतरभूत_data_nolock(handle, inode, &iloc);
	ext4_ग_लिखो_unlock_xattr(inode, &no_expand);
	ext4_journal_stop(handle);
out_मुक्त:
	brअन्यथा(iloc.bh);
	वापस error;
पूर्ण
