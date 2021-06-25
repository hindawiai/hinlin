<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#समावेश <linux/security.h>
#समावेश "xattr.h"

काष्ठा xattr_iter अणु
	काष्ठा super_block *sb;
	काष्ठा page *page;
	व्योम *kaddr;

	erofs_blk_t blkaddr;
	अचिन्हित पूर्णांक ofs;
पूर्ण;

अटल अंतरभूत व्योम xattr_iter_end(काष्ठा xattr_iter *it, bool atomic)
अणु
	/* the only user of kunmap() is 'init_inode_xattrs' */
	अगर (!atomic)
		kunmap(it->page);
	अन्यथा
		kunmap_atomic(it->kaddr);

	unlock_page(it->page);
	put_page(it->page);
पूर्ण

अटल अंतरभूत व्योम xattr_iter_end_final(काष्ठा xattr_iter *it)
अणु
	अगर (!it->page)
		वापस;

	xattr_iter_end(it, true);
पूर्ण

अटल पूर्णांक init_inode_xattrs(काष्ठा inode *inode)
अणु
	काष्ठा erofs_inode *स्थिर vi = EROFS_I(inode);
	काष्ठा xattr_iter it;
	अचिन्हित पूर्णांक i;
	काष्ठा erofs_xattr_ibody_header *ih;
	काष्ठा super_block *sb;
	काष्ठा erofs_sb_info *sbi;
	bool atomic_map;
	पूर्णांक ret = 0;

	/* the most हाल is that xattrs of this inode are initialized. */
	अगर (test_bit(EROFS_I_EA_INITED_BIT, &vi->flags)) अणु
		/*
		 * paired with smp_mb() at the end of the function to ensure
		 * fields will only be observed after the bit is set.
		 */
		smp_mb();
		वापस 0;
	पूर्ण

	अगर (रुको_on_bit_lock(&vi->flags, EROFS_I_BL_XATTR_BIT, TASK_KILLABLE))
		वापस -ERESTARTSYS;

	/* someone has initialized xattrs क्रम us? */
	अगर (test_bit(EROFS_I_EA_INITED_BIT, &vi->flags))
		जाओ out_unlock;

	/*
	 * bypass all xattr operations अगर ->xattr_isize is not greater than
	 * माप(काष्ठा erofs_xattr_ibody_header), in detail:
	 * 1) it is not enough to contain erofs_xattr_ibody_header then
	 *    ->xattr_isize should be 0 (it means no xattr);
	 * 2) it is just to contain erofs_xattr_ibody_header, which is on-disk
	 *    undefined right now (maybe use later with some new sb feature).
	 */
	अगर (vi->xattr_isize == माप(काष्ठा erofs_xattr_ibody_header)) अणु
		erofs_err(inode->i_sb,
			  "xattr_isize %d of nid %llu is not supported yet",
			  vi->xattr_isize, vi->nid);
		ret = -EOPNOTSUPP;
		जाओ out_unlock;
	पूर्ण अन्यथा अगर (vi->xattr_isize < माप(काष्ठा erofs_xattr_ibody_header)) अणु
		अगर (vi->xattr_isize) अणु
			erofs_err(inode->i_sb,
				  "bogus xattr ibody @ nid %llu", vi->nid);
			DBG_BUGON(1);
			ret = -EFSCORRUPTED;
			जाओ out_unlock;	/* xattr ondisk layout error */
		पूर्ण
		ret = -ENOATTR;
		जाओ out_unlock;
	पूर्ण

	sb = inode->i_sb;
	sbi = EROFS_SB(sb);
	it.blkaddr = erofs_blknr(iloc(sbi, vi->nid) + vi->inode_isize);
	it.ofs = erofs_blkoff(iloc(sbi, vi->nid) + vi->inode_isize);

	it.page = erofs_get_meta_page(sb, it.blkaddr);
	अगर (IS_ERR(it.page)) अणु
		ret = PTR_ERR(it.page);
		जाओ out_unlock;
	पूर्ण

	/* पढ़ो in shared xattr array (non-atomic, see kदो_स्मृति below) */
	it.kaddr = kmap(it.page);
	atomic_map = false;

	ih = (काष्ठा erofs_xattr_ibody_header *)(it.kaddr + it.ofs);

	vi->xattr_shared_count = ih->h_shared_count;
	vi->xattr_shared_xattrs = kदो_स्मृति_array(vi->xattr_shared_count,
						माप(uपूर्णांक), GFP_KERNEL);
	अगर (!vi->xattr_shared_xattrs) अणु
		xattr_iter_end(&it, atomic_map);
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	/* let's skip ibody header */
	it.ofs += माप(काष्ठा erofs_xattr_ibody_header);

	क्रम (i = 0; i < vi->xattr_shared_count; ++i) अणु
		अगर (it.ofs >= EROFS_BLKSIZ) अणु
			/* cannot be unaligned */
			DBG_BUGON(it.ofs != EROFS_BLKSIZ);
			xattr_iter_end(&it, atomic_map);

			it.page = erofs_get_meta_page(sb, ++it.blkaddr);
			अगर (IS_ERR(it.page)) अणु
				kमुक्त(vi->xattr_shared_xattrs);
				vi->xattr_shared_xattrs = शून्य;
				ret = PTR_ERR(it.page);
				जाओ out_unlock;
			पूर्ण

			it.kaddr = kmap_atomic(it.page);
			atomic_map = true;
			it.ofs = 0;
		पूर्ण
		vi->xattr_shared_xattrs[i] =
			le32_to_cpu(*(__le32 *)(it.kaddr + it.ofs));
		it.ofs += माप(__le32);
	पूर्ण
	xattr_iter_end(&it, atomic_map);

	/* paired with smp_mb() at the beginning of the function. */
	smp_mb();
	set_bit(EROFS_I_EA_INITED_BIT, &vi->flags);

out_unlock:
	clear_and_wake_up_bit(EROFS_I_BL_XATTR_BIT, &vi->flags);
	वापस ret;
पूर्ण

/*
 * the general idea क्रम these वापस values is
 * अगर    0 is वापसed, go on processing the current xattr;
 *       1 (> 0) is वापसed, skip this round to process the next xattr;
 *    -err (< 0) is वापसed, an error (maybe ENOXATTR) occurred
 *                            and need to be handled
 */
काष्ठा xattr_iter_handlers अणु
	पूर्णांक (*entry)(काष्ठा xattr_iter *_it, काष्ठा erofs_xattr_entry *entry);
	पूर्णांक (*name)(काष्ठा xattr_iter *_it, अचिन्हित पूर्णांक processed, अक्षर *buf,
		    अचिन्हित पूर्णांक len);
	पूर्णांक (*alloc_buffer)(काष्ठा xattr_iter *_it, अचिन्हित पूर्णांक value_sz);
	व्योम (*value)(काष्ठा xattr_iter *_it, अचिन्हित पूर्णांक processed, अक्षर *buf,
		      अचिन्हित पूर्णांक len);
पूर्ण;

अटल अंतरभूत पूर्णांक xattr_iter_fixup(काष्ठा xattr_iter *it)
अणु
	अगर (it->ofs < EROFS_BLKSIZ)
		वापस 0;

	xattr_iter_end(it, true);

	it->blkaddr += erofs_blknr(it->ofs);

	it->page = erofs_get_meta_page(it->sb, it->blkaddr);
	अगर (IS_ERR(it->page)) अणु
		पूर्णांक err = PTR_ERR(it->page);

		it->page = शून्य;
		वापस err;
	पूर्ण

	it->kaddr = kmap_atomic(it->page);
	it->ofs = erofs_blkoff(it->ofs);
	वापस 0;
पूर्ण

अटल पूर्णांक अंतरभूत_xattr_iter_begin(काष्ठा xattr_iter *it,
				   काष्ठा inode *inode)
अणु
	काष्ठा erofs_inode *स्थिर vi = EROFS_I(inode);
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_SB(inode->i_sb);
	अचिन्हित पूर्णांक xattr_header_sz, अंतरभूत_xattr_ofs;

	xattr_header_sz = अंतरभूतxattr_header_size(inode);
	अगर (xattr_header_sz >= vi->xattr_isize) अणु
		DBG_BUGON(xattr_header_sz > vi->xattr_isize);
		वापस -ENOATTR;
	पूर्ण

	अंतरभूत_xattr_ofs = vi->inode_isize + xattr_header_sz;

	it->blkaddr = erofs_blknr(iloc(sbi, vi->nid) + अंतरभूत_xattr_ofs);
	it->ofs = erofs_blkoff(iloc(sbi, vi->nid) + अंतरभूत_xattr_ofs);

	it->page = erofs_get_meta_page(inode->i_sb, it->blkaddr);
	अगर (IS_ERR(it->page))
		वापस PTR_ERR(it->page);

	it->kaddr = kmap_atomic(it->page);
	वापस vi->xattr_isize - xattr_header_sz;
पूर्ण

/*
 * Regardless of success or failure, `xattr_क्रमeach' will end up with
 * `ofs' poपूर्णांकing to the next xattr item rather than an arbitrary position.
 */
अटल पूर्णांक xattr_क्रमeach(काष्ठा xattr_iter *it,
			 स्थिर काष्ठा xattr_iter_handlers *op,
			 अचिन्हित पूर्णांक *tlimit)
अणु
	काष्ठा erofs_xattr_entry entry;
	अचिन्हित पूर्णांक value_sz, processed, slice;
	पूर्णांक err;

	/* 0. fixup blkaddr, ofs, ipage */
	err = xattr_iter_fixup(it);
	अगर (err)
		वापस err;

	/*
	 * 1. पढ़ो xattr entry to the memory,
	 *    since we करो EROFS_XATTR_ALIGN
	 *    thereक्रमe entry should be in the page
	 */
	entry = *(काष्ठा erofs_xattr_entry *)(it->kaddr + it->ofs);
	अगर (tlimit) अणु
		अचिन्हित पूर्णांक entry_sz = erofs_xattr_entry_size(&entry);

		/* xattr on-disk corruption: xattr entry beyond xattr_isize */
		अगर (*tlimit < entry_sz) अणु
			DBG_BUGON(1);
			वापस -EFSCORRUPTED;
		पूर्ण
		*tlimit -= entry_sz;
	पूर्ण

	it->ofs += माप(काष्ठा erofs_xattr_entry);
	value_sz = le16_to_cpu(entry.e_value_size);

	/* handle entry */
	err = op->entry(it, &entry);
	अगर (err) अणु
		it->ofs += entry.e_name_len + value_sz;
		जाओ out;
	पूर्ण

	/* 2. handle xattr name (ofs will finally be at the end of name) */
	processed = 0;

	जबतक (processed < entry.e_name_len) अणु
		अगर (it->ofs >= EROFS_BLKSIZ) अणु
			DBG_BUGON(it->ofs > EROFS_BLKSIZ);

			err = xattr_iter_fixup(it);
			अगर (err)
				जाओ out;
			it->ofs = 0;
		पूर्ण

		slice = min_t(अचिन्हित पूर्णांक, PAGE_SIZE - it->ofs,
			      entry.e_name_len - processed);

		/* handle name */
		err = op->name(it, processed, it->kaddr + it->ofs, slice);
		अगर (err) अणु
			it->ofs += entry.e_name_len - processed + value_sz;
			जाओ out;
		पूर्ण

		it->ofs += slice;
		processed += slice;
	पूर्ण

	/* 3. handle xattr value */
	processed = 0;

	अगर (op->alloc_buffer) अणु
		err = op->alloc_buffer(it, value_sz);
		अगर (err) अणु
			it->ofs += value_sz;
			जाओ out;
		पूर्ण
	पूर्ण

	जबतक (processed < value_sz) अणु
		अगर (it->ofs >= EROFS_BLKSIZ) अणु
			DBG_BUGON(it->ofs > EROFS_BLKSIZ);

			err = xattr_iter_fixup(it);
			अगर (err)
				जाओ out;
			it->ofs = 0;
		पूर्ण

		slice = min_t(अचिन्हित पूर्णांक, PAGE_SIZE - it->ofs,
			      value_sz - processed);
		op->value(it, processed, it->kaddr + it->ofs, slice);
		it->ofs += slice;
		processed += slice;
	पूर्ण

out:
	/* xattrs should be 4-byte aligned (on-disk स्थिरraपूर्णांक) */
	it->ofs = EROFS_XATTR_ALIGN(it->ofs);
	वापस err < 0 ? err : 0;
पूर्ण

काष्ठा getxattr_iter अणु
	काष्ठा xattr_iter it;

	अक्षर *buffer;
	पूर्णांक buffer_size, index;
	काष्ठा qstr name;
पूर्ण;

अटल पूर्णांक xattr_entrymatch(काष्ठा xattr_iter *_it,
			    काष्ठा erofs_xattr_entry *entry)
अणु
	काष्ठा getxattr_iter *it = container_of(_it, काष्ठा getxattr_iter, it);

	वापस (it->index != entry->e_name_index ||
		it->name.len != entry->e_name_len) ? -ENOATTR : 0;
पूर्ण

अटल पूर्णांक xattr_namematch(काष्ठा xattr_iter *_it,
			   अचिन्हित पूर्णांक processed, अक्षर *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा getxattr_iter *it = container_of(_it, काष्ठा getxattr_iter, it);

	वापस स_भेद(buf, it->name.name + processed, len) ? -ENOATTR : 0;
पूर्ण

अटल पूर्णांक xattr_checkbuffer(काष्ठा xattr_iter *_it,
			     अचिन्हित पूर्णांक value_sz)
अणु
	काष्ठा getxattr_iter *it = container_of(_it, काष्ठा getxattr_iter, it);
	पूर्णांक err = it->buffer_size < value_sz ? -दुस्फल : 0;

	it->buffer_size = value_sz;
	वापस !it->buffer ? 1 : err;
पूर्ण

अटल व्योम xattr_copyvalue(काष्ठा xattr_iter *_it,
			    अचिन्हित पूर्णांक processed,
			    अक्षर *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा getxattr_iter *it = container_of(_it, काष्ठा getxattr_iter, it);

	स_नकल(it->buffer + processed, buf, len);
पूर्ण

अटल स्थिर काष्ठा xattr_iter_handlers find_xattr_handlers = अणु
	.entry = xattr_entrymatch,
	.name = xattr_namematch,
	.alloc_buffer = xattr_checkbuffer,
	.value = xattr_copyvalue
पूर्ण;

अटल पूर्णांक अंतरभूत_getxattr(काष्ठा inode *inode, काष्ठा getxattr_iter *it)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reमुख्यing;

	ret = अंतरभूत_xattr_iter_begin(&it->it, inode);
	अगर (ret < 0)
		वापस ret;

	reमुख्यing = ret;
	जबतक (reमुख्यing) अणु
		ret = xattr_क्रमeach(&it->it, &find_xattr_handlers, &reमुख्यing);
		अगर (ret != -ENOATTR)
			अवरोध;
	पूर्ण
	xattr_iter_end_final(&it->it);

	वापस ret ? ret : it->buffer_size;
पूर्ण

अटल पूर्णांक shared_getxattr(काष्ठा inode *inode, काष्ठा getxattr_iter *it)
अणु
	काष्ठा erofs_inode *स्थिर vi = EROFS_I(inode);
	काष्ठा super_block *स्थिर sb = inode->i_sb;
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_SB(sb);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = -ENOATTR;

	क्रम (i = 0; i < vi->xattr_shared_count; ++i) अणु
		erofs_blk_t blkaddr =
			xattrblock_addr(sbi, vi->xattr_shared_xattrs[i]);

		it->it.ofs = xattrblock_offset(sbi, vi->xattr_shared_xattrs[i]);

		अगर (!i || blkaddr != it->it.blkaddr) अणु
			अगर (i)
				xattr_iter_end(&it->it, true);

			it->it.page = erofs_get_meta_page(sb, blkaddr);
			अगर (IS_ERR(it->it.page))
				वापस PTR_ERR(it->it.page);

			it->it.kaddr = kmap_atomic(it->it.page);
			it->it.blkaddr = blkaddr;
		पूर्ण

		ret = xattr_क्रमeach(&it->it, &find_xattr_handlers, शून्य);
		अगर (ret != -ENOATTR)
			अवरोध;
	पूर्ण
	अगर (vi->xattr_shared_count)
		xattr_iter_end_final(&it->it);

	वापस ret ? ret : it->buffer_size;
पूर्ण

अटल bool erofs_xattr_user_list(काष्ठा dentry *dentry)
अणु
	वापस test_opt(&EROFS_SB(dentry->d_sb)->ctx, XATTR_USER);
पूर्ण

अटल bool erofs_xattr_trusted_list(काष्ठा dentry *dentry)
अणु
	वापस capable(CAP_SYS_ADMIN);
पूर्ण

पूर्णांक erofs_getxattr(काष्ठा inode *inode, पूर्णांक index,
		   स्थिर अक्षर *name,
		   व्योम *buffer, माप_प्रकार buffer_size)
अणु
	पूर्णांक ret;
	काष्ठा getxattr_iter it;

	अगर (!name)
		वापस -EINVAL;

	ret = init_inode_xattrs(inode);
	अगर (ret)
		वापस ret;

	it.index = index;

	it.name.len = म_माप(name);
	अगर (it.name.len > EROFS_NAME_LEN)
		वापस -दुस्फल;
	it.name.name = name;

	it.buffer = buffer;
	it.buffer_size = buffer_size;

	it.it.sb = inode->i_sb;
	ret = अंतरभूत_getxattr(inode, &it);
	अगर (ret == -ENOATTR)
		ret = shared_getxattr(inode, &it);
	वापस ret;
पूर्ण

अटल पूर्णांक erofs_xattr_generic_get(स्थिर काष्ठा xattr_handler *handler,
				   काष्ठा dentry *unused, काष्ठा inode *inode,
				   स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_I_SB(inode);

	चयन (handler->flags) अणु
	हाल EROFS_XATTR_INDEX_USER:
		अगर (!test_opt(&sbi->ctx, XATTR_USER))
			वापस -EOPNOTSUPP;
		अवरोध;
	हाल EROFS_XATTR_INDEX_TRUSTED:
		अवरोध;
	हाल EROFS_XATTR_INDEX_SECURITY:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस erofs_getxattr(inode, handler->flags, name, buffer, size);
पूर्ण

स्थिर काष्ठा xattr_handler erofs_xattr_user_handler = अणु
	.prefix	= XATTR_USER_PREFIX,
	.flags	= EROFS_XATTR_INDEX_USER,
	.list	= erofs_xattr_user_list,
	.get	= erofs_xattr_generic_get,
पूर्ण;

स्थिर काष्ठा xattr_handler erofs_xattr_trusted_handler = अणु
	.prefix	= XATTR_TRUSTED_PREFIX,
	.flags	= EROFS_XATTR_INDEX_TRUSTED,
	.list	= erofs_xattr_trusted_list,
	.get	= erofs_xattr_generic_get,
पूर्ण;

#अगर_घोषित CONFIG_EROFS_FS_SECURITY
स्थिर काष्ठा xattr_handler __maybe_unused erofs_xattr_security_handler = अणु
	.prefix	= XATTR_SECURITY_PREFIX,
	.flags	= EROFS_XATTR_INDEX_SECURITY,
	.get	= erofs_xattr_generic_get,
पूर्ण;
#पूर्ण_अगर

स्थिर काष्ठा xattr_handler *erofs_xattr_handlers[] = अणु
	&erofs_xattr_user_handler,
#अगर_घोषित CONFIG_EROFS_FS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	&erofs_xattr_trusted_handler,
#अगर_घोषित CONFIG_EROFS_FS_SECURITY
	&erofs_xattr_security_handler,
#पूर्ण_अगर
	शून्य,
पूर्ण;

काष्ठा listxattr_iter अणु
	काष्ठा xattr_iter it;

	काष्ठा dentry *dentry;
	अक्षर *buffer;
	पूर्णांक buffer_size, buffer_ofs;
पूर्ण;

अटल पूर्णांक xattr_entrylist(काष्ठा xattr_iter *_it,
			   काष्ठा erofs_xattr_entry *entry)
अणु
	काष्ठा listxattr_iter *it =
		container_of(_it, काष्ठा listxattr_iter, it);
	अचिन्हित पूर्णांक prefix_len;
	स्थिर अक्षर *prefix;

	स्थिर काष्ठा xattr_handler *h =
		erofs_xattr_handler(entry->e_name_index);

	अगर (!h || (h->list && !h->list(it->dentry)))
		वापस 1;

	prefix = xattr_prefix(h);
	prefix_len = म_माप(prefix);

	अगर (!it->buffer) अणु
		it->buffer_ofs += prefix_len + entry->e_name_len + 1;
		वापस 1;
	पूर्ण

	अगर (it->buffer_ofs + prefix_len
		+ entry->e_name_len + 1 > it->buffer_size)
		वापस -दुस्फल;

	स_नकल(it->buffer + it->buffer_ofs, prefix, prefix_len);
	it->buffer_ofs += prefix_len;
	वापस 0;
पूर्ण

अटल पूर्णांक xattr_namelist(काष्ठा xattr_iter *_it,
			  अचिन्हित पूर्णांक processed, अक्षर *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा listxattr_iter *it =
		container_of(_it, काष्ठा listxattr_iter, it);

	स_नकल(it->buffer + it->buffer_ofs, buf, len);
	it->buffer_ofs += len;
	वापस 0;
पूर्ण

अटल पूर्णांक xattr_skipvalue(काष्ठा xattr_iter *_it,
			   अचिन्हित पूर्णांक value_sz)
अणु
	काष्ठा listxattr_iter *it =
		container_of(_it, काष्ठा listxattr_iter, it);

	it->buffer[it->buffer_ofs++] = '\0';
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा xattr_iter_handlers list_xattr_handlers = अणु
	.entry = xattr_entrylist,
	.name = xattr_namelist,
	.alloc_buffer = xattr_skipvalue,
	.value = शून्य
पूर्ण;

अटल पूर्णांक अंतरभूत_listxattr(काष्ठा listxattr_iter *it)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reमुख्यing;

	ret = अंतरभूत_xattr_iter_begin(&it->it, d_inode(it->dentry));
	अगर (ret < 0)
		वापस ret;

	reमुख्यing = ret;
	जबतक (reमुख्यing) अणु
		ret = xattr_क्रमeach(&it->it, &list_xattr_handlers, &reमुख्यing);
		अगर (ret)
			अवरोध;
	पूर्ण
	xattr_iter_end_final(&it->it);
	वापस ret ? ret : it->buffer_ofs;
पूर्ण

अटल पूर्णांक shared_listxattr(काष्ठा listxattr_iter *it)
अणु
	काष्ठा inode *स्थिर inode = d_inode(it->dentry);
	काष्ठा erofs_inode *स्थिर vi = EROFS_I(inode);
	काष्ठा super_block *स्थिर sb = inode->i_sb;
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_SB(sb);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < vi->xattr_shared_count; ++i) अणु
		erofs_blk_t blkaddr =
			xattrblock_addr(sbi, vi->xattr_shared_xattrs[i]);

		it->it.ofs = xattrblock_offset(sbi, vi->xattr_shared_xattrs[i]);
		अगर (!i || blkaddr != it->it.blkaddr) अणु
			अगर (i)
				xattr_iter_end(&it->it, true);

			it->it.page = erofs_get_meta_page(sb, blkaddr);
			अगर (IS_ERR(it->it.page))
				वापस PTR_ERR(it->it.page);

			it->it.kaddr = kmap_atomic(it->it.page);
			it->it.blkaddr = blkaddr;
		पूर्ण

		ret = xattr_क्रमeach(&it->it, &list_xattr_handlers, शून्य);
		अगर (ret)
			अवरोध;
	पूर्ण
	अगर (vi->xattr_shared_count)
		xattr_iter_end_final(&it->it);

	वापस ret ? ret : it->buffer_ofs;
पूर्ण

sमाप_प्रकार erofs_listxattr(काष्ठा dentry *dentry,
			अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	पूर्णांक ret;
	काष्ठा listxattr_iter it;

	ret = init_inode_xattrs(d_inode(dentry));
	अगर (ret == -ENOATTR)
		वापस 0;
	अगर (ret)
		वापस ret;

	it.dentry = dentry;
	it.buffer = buffer;
	it.buffer_size = buffer_size;
	it.buffer_ofs = 0;

	it.it.sb = dentry->d_sb;

	ret = अंतरभूत_listxattr(&it);
	अगर (ret < 0 && ret != -ENOATTR)
		वापस ret;
	वापस shared_listxattr(&it);
पूर्ण

#अगर_घोषित CONFIG_EROFS_FS_POSIX_ACL
काष्ठा posix_acl *erofs_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा posix_acl *acl;
	पूर्णांक prefix, rc;
	अक्षर *value = शून्य;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		prefix = EROFS_XATTR_INDEX_POSIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		prefix = EROFS_XATTR_INDEX_POSIX_ACL_DEFAULT;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	rc = erofs_getxattr(inode, prefix, "", शून्य, 0);
	अगर (rc > 0) अणु
		value = kदो_स्मृति(rc, GFP_KERNEL);
		अगर (!value)
			वापस ERR_PTR(-ENOMEM);
		rc = erofs_getxattr(inode, prefix, "", value, rc);
	पूर्ण

	अगर (rc == -ENOATTR)
		acl = शून्य;
	अन्यथा अगर (rc < 0)
		acl = ERR_PTR(rc);
	अन्यथा
		acl = posix_acl_from_xattr(&init_user_ns, value, rc);
	kमुक्त(value);
	वापस acl;
पूर्ण
#पूर्ण_अगर

