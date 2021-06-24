<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/xattr.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 *
 * Portions of this code from linux/fs/ext2/xattr.c
 *
 * Copyright (C) 2001-2003 Andreas Gruenbacher <agruen@suse.de>
 *
 * Fix by Harrison Xing <harrison@mountainviewdata.com>.
 * Extended attributes क्रम symlinks and special files added per
 *  suggestion of Luka Renko <luka.renko@hermes.si>.
 * xattr consolidation Copyright (c) 2004 James Morris <jmorris@redhat.com>,
 *  Red Hat Inc.
 */
#समावेश <linux/rwsem.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/security.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश "f2fs.h"
#समावेश "xattr.h"
#समावेश "segment.h"

अटल व्योम *xattr_alloc(काष्ठा f2fs_sb_info *sbi, पूर्णांक size, bool *is_अंतरभूत)
अणु
	अगर (likely(size == sbi->अंतरभूत_xattr_slab_size)) अणु
		*is_अंतरभूत = true;
		वापस kmem_cache_zalloc(sbi->अंतरभूत_xattr_slab, GFP_NOFS);
	पूर्ण
	*is_अंतरभूत = false;
	वापस f2fs_kzalloc(sbi, size, GFP_NOFS);
पूर्ण

अटल व्योम xattr_मुक्त(काष्ठा f2fs_sb_info *sbi, व्योम *xattr_addr,
							bool is_अंतरभूत)
अणु
	अगर (is_अंतरभूत)
		kmem_cache_मुक्त(sbi->अंतरभूत_xattr_slab, xattr_addr);
	अन्यथा
		kमुक्त(xattr_addr);
पूर्ण

अटल पूर्णांक f2fs_xattr_generic_get(स्थिर काष्ठा xattr_handler *handler,
		काष्ठा dentry *unused, काष्ठा inode *inode,
		स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(inode->i_sb);

	चयन (handler->flags) अणु
	हाल F2FS_XATTR_INDEX_USER:
		अगर (!test_opt(sbi, XATTR_USER))
			वापस -EOPNOTSUPP;
		अवरोध;
	हाल F2FS_XATTR_INDEX_TRUSTED:
	हाल F2FS_XATTR_INDEX_SECURITY:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस f2fs_getxattr(inode, handler->flags, name,
			     buffer, size, शून्य);
पूर्ण

अटल पूर्णांक f2fs_xattr_generic_set(स्थिर काष्ठा xattr_handler *handler,
		काष्ठा user_namespace *mnt_userns,
		काष्ठा dentry *unused, काष्ठा inode *inode,
		स्थिर अक्षर *name, स्थिर व्योम *value,
		माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(inode->i_sb);

	चयन (handler->flags) अणु
	हाल F2FS_XATTR_INDEX_USER:
		अगर (!test_opt(sbi, XATTR_USER))
			वापस -EOPNOTSUPP;
		अवरोध;
	हाल F2FS_XATTR_INDEX_TRUSTED:
	हाल F2FS_XATTR_INDEX_SECURITY:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस f2fs_setxattr(inode, handler->flags, name,
					value, size, शून्य, flags);
पूर्ण

अटल bool f2fs_xattr_user_list(काष्ठा dentry *dentry)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(dentry->d_sb);

	वापस test_opt(sbi, XATTR_USER);
पूर्ण

अटल bool f2fs_xattr_trusted_list(काष्ठा dentry *dentry)
अणु
	वापस capable(CAP_SYS_ADMIN);
पूर्ण

अटल पूर्णांक f2fs_xattr_advise_get(स्थिर काष्ठा xattr_handler *handler,
		काष्ठा dentry *unused, काष्ठा inode *inode,
		स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	अगर (buffer)
		*((अक्षर *)buffer) = F2FS_I(inode)->i_advise;
	वापस माप(अक्षर);
पूर्ण

अटल पूर्णांक f2fs_xattr_advise_set(स्थिर काष्ठा xattr_handler *handler,
		काष्ठा user_namespace *mnt_userns,
		काष्ठा dentry *unused, काष्ठा inode *inode,
		स्थिर अक्षर *name, स्थिर व्योम *value,
		माप_प्रकार size, पूर्णांक flags)
अणु
	अचिन्हित अक्षर old_advise = F2FS_I(inode)->i_advise;
	अचिन्हित अक्षर new_advise;

	अगर (!inode_owner_or_capable(&init_user_ns, inode))
		वापस -EPERM;
	अगर (value == शून्य)
		वापस -EINVAL;

	new_advise = *(अक्षर *)value;
	अगर (new_advise & ~FADVISE_MODIFIABLE_BITS)
		वापस -EINVAL;

	new_advise = new_advise & FADVISE_MODIFIABLE_BITS;
	new_advise |= old_advise & ~FADVISE_MODIFIABLE_BITS;

	F2FS_I(inode)->i_advise = new_advise;
	f2fs_mark_inode_dirty_sync(inode, true);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_SECURITY
अटल पूर्णांक f2fs_initxattrs(काष्ठा inode *inode, स्थिर काष्ठा xattr *xattr_array,
		व्योम *page)
अणु
	स्थिर काष्ठा xattr *xattr;
	पूर्णांक err = 0;

	क्रम (xattr = xattr_array; xattr->name != शून्य; xattr++) अणु
		err = f2fs_setxattr(inode, F2FS_XATTR_INDEX_SECURITY,
				xattr->name, xattr->value,
				xattr->value_len, (काष्ठा page *)page, 0);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक f2fs_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
				स्थिर काष्ठा qstr *qstr, काष्ठा page *ipage)
अणु
	वापस security_inode_init_security(inode, dir, qstr,
				&f2fs_initxattrs, ipage);
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा xattr_handler f2fs_xattr_user_handler = अणु
	.prefix	= XATTR_USER_PREFIX,
	.flags	= F2FS_XATTR_INDEX_USER,
	.list	= f2fs_xattr_user_list,
	.get	= f2fs_xattr_generic_get,
	.set	= f2fs_xattr_generic_set,
पूर्ण;

स्थिर काष्ठा xattr_handler f2fs_xattr_trusted_handler = अणु
	.prefix	= XATTR_TRUSTED_PREFIX,
	.flags	= F2FS_XATTR_INDEX_TRUSTED,
	.list	= f2fs_xattr_trusted_list,
	.get	= f2fs_xattr_generic_get,
	.set	= f2fs_xattr_generic_set,
पूर्ण;

स्थिर काष्ठा xattr_handler f2fs_xattr_advise_handler = अणु
	.name	= F2FS_SYSTEM_ADVISE_NAME,
	.flags	= F2FS_XATTR_INDEX_ADVISE,
	.get	= f2fs_xattr_advise_get,
	.set	= f2fs_xattr_advise_set,
पूर्ण;

स्थिर काष्ठा xattr_handler f2fs_xattr_security_handler = अणु
	.prefix	= XATTR_SECURITY_PREFIX,
	.flags	= F2FS_XATTR_INDEX_SECURITY,
	.get	= f2fs_xattr_generic_get,
	.set	= f2fs_xattr_generic_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler *f2fs_xattr_handler_map[] = अणु
	[F2FS_XATTR_INDEX_USER] = &f2fs_xattr_user_handler,
#अगर_घोषित CONFIG_F2FS_FS_POSIX_ACL
	[F2FS_XATTR_INDEX_POSIX_ACL_ACCESS] = &posix_acl_access_xattr_handler,
	[F2FS_XATTR_INDEX_POSIX_ACL_DEFAULT] = &posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	[F2FS_XATTR_INDEX_TRUSTED] = &f2fs_xattr_trusted_handler,
#अगर_घोषित CONFIG_F2FS_FS_SECURITY
	[F2FS_XATTR_INDEX_SECURITY] = &f2fs_xattr_security_handler,
#पूर्ण_अगर
	[F2FS_XATTR_INDEX_ADVISE] = &f2fs_xattr_advise_handler,
पूर्ण;

स्थिर काष्ठा xattr_handler *f2fs_xattr_handlers[] = अणु
	&f2fs_xattr_user_handler,
#अगर_घोषित CONFIG_F2FS_FS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	&f2fs_xattr_trusted_handler,
#अगर_घोषित CONFIG_F2FS_FS_SECURITY
	&f2fs_xattr_security_handler,
#पूर्ण_अगर
	&f2fs_xattr_advise_handler,
	शून्य,
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा xattr_handler *f2fs_xattr_handler(पूर्णांक index)
अणु
	स्थिर काष्ठा xattr_handler *handler = शून्य;

	अगर (index > 0 && index < ARRAY_SIZE(f2fs_xattr_handler_map))
		handler = f2fs_xattr_handler_map[index];
	वापस handler;
पूर्ण

अटल काष्ठा f2fs_xattr_entry *__find_xattr(व्योम *base_addr,
				व्योम *last_base_addr, पूर्णांक index,
				माप_प्रकार len, स्थिर अक्षर *name)
अणु
	काष्ठा f2fs_xattr_entry *entry;

	list_क्रम_each_xattr(entry, base_addr) अणु
		अगर ((व्योम *)(entry) + माप(__u32) > last_base_addr ||
			(व्योम *)XATTR_NEXT_ENTRY(entry) > last_base_addr)
			वापस शून्य;

		अगर (entry->e_name_index != index)
			जारी;
		अगर (entry->e_name_len != len)
			जारी;
		अगर (!स_भेद(entry->e_name, name, len))
			अवरोध;
	पूर्ण
	वापस entry;
पूर्ण

अटल काष्ठा f2fs_xattr_entry *__find_अंतरभूत_xattr(काष्ठा inode *inode,
				व्योम *base_addr, व्योम **last_addr, पूर्णांक index,
				माप_प्रकार len, स्थिर अक्षर *name)
अणु
	काष्ठा f2fs_xattr_entry *entry;
	अचिन्हित पूर्णांक अंतरभूत_size = अंतरभूत_xattr_size(inode);
	व्योम *max_addr = base_addr + अंतरभूत_size;

	list_क्रम_each_xattr(entry, base_addr) अणु
		अगर ((व्योम *)entry + माप(__u32) > max_addr ||
			(व्योम *)XATTR_NEXT_ENTRY(entry) > max_addr) अणु
			*last_addr = entry;
			वापस शून्य;
		पूर्ण
		अगर (entry->e_name_index != index)
			जारी;
		अगर (entry->e_name_len != len)
			जारी;
		अगर (!स_भेद(entry->e_name, name, len))
			अवरोध;
	पूर्ण

	/* अंतरभूत xattr header or entry across max अंतरभूत xattr size */
	अगर (IS_XATTR_LAST_ENTRY(entry) &&
		(व्योम *)entry + माप(__u32) > max_addr) अणु
		*last_addr = entry;
		वापस शून्य;
	पूर्ण
	वापस entry;
पूर्ण

अटल पूर्णांक पढ़ो_अंतरभूत_xattr(काष्ठा inode *inode, काष्ठा page *ipage,
							व्योम *txattr_addr)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	अचिन्हित पूर्णांक अंतरभूत_size = अंतरभूत_xattr_size(inode);
	काष्ठा page *page = शून्य;
	व्योम *अंतरभूत_addr;

	अगर (ipage) अणु
		अंतरभूत_addr = अंतरभूत_xattr_addr(inode, ipage);
	पूर्ण अन्यथा अणु
		page = f2fs_get_node_page(sbi, inode->i_ino);
		अगर (IS_ERR(page))
			वापस PTR_ERR(page);

		अंतरभूत_addr = अंतरभूत_xattr_addr(inode, page);
	पूर्ण
	स_नकल(txattr_addr, अंतरभूत_addr, अंतरभूत_size);
	f2fs_put_page(page, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_xattr_block(काष्ठा inode *inode, व्योम *txattr_addr)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	nid_t xnid = F2FS_I(inode)->i_xattr_nid;
	अचिन्हित पूर्णांक अंतरभूत_size = अंतरभूत_xattr_size(inode);
	काष्ठा page *xpage;
	व्योम *xattr_addr;

	/* The inode alपढ़ोy has an extended attribute block. */
	xpage = f2fs_get_node_page(sbi, xnid);
	अगर (IS_ERR(xpage))
		वापस PTR_ERR(xpage);

	xattr_addr = page_address(xpage);
	स_नकल(txattr_addr + अंतरभूत_size, xattr_addr, VALID_XATTR_BLOCK_SIZE);
	f2fs_put_page(xpage, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक lookup_all_xattrs(काष्ठा inode *inode, काष्ठा page *ipage,
				अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक len,
				स्थिर अक्षर *name, काष्ठा f2fs_xattr_entry **xe,
				व्योम **base_addr, पूर्णांक *base_size,
				bool *is_अंतरभूत)
अणु
	व्योम *cur_addr, *txattr_addr, *last_txattr_addr;
	व्योम *last_addr = शून्य;
	nid_t xnid = F2FS_I(inode)->i_xattr_nid;
	अचिन्हित पूर्णांक अंतरभूत_size = अंतरभूत_xattr_size(inode);
	पूर्णांक err;

	अगर (!xnid && !अंतरभूत_size)
		वापस -ENODATA;

	*base_size = XATTR_SIZE(inode) + XATTR_PADDING_SIZE;
	txattr_addr = xattr_alloc(F2FS_I_SB(inode), *base_size, is_अंतरभूत);
	अगर (!txattr_addr)
		वापस -ENOMEM;

	last_txattr_addr = (व्योम *)txattr_addr + XATTR_SIZE(inode);

	/* पढ़ो from अंतरभूत xattr */
	अगर (अंतरभूत_size) अणु
		err = पढ़ो_अंतरभूत_xattr(inode, ipage, txattr_addr);
		अगर (err)
			जाओ out;

		*xe = __find_अंतरभूत_xattr(inode, txattr_addr, &last_addr,
						index, len, name);
		अगर (*xe) अणु
			*base_size = अंतरभूत_size;
			जाओ check;
		पूर्ण
	पूर्ण

	/* पढ़ो from xattr node block */
	अगर (xnid) अणु
		err = पढ़ो_xattr_block(inode, txattr_addr);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (last_addr)
		cur_addr = XATTR_HDR(last_addr) - 1;
	अन्यथा
		cur_addr = txattr_addr;

	*xe = __find_xattr(cur_addr, last_txattr_addr, index, len, name);
	अगर (!*xe) अणु
		f2fs_err(F2FS_I_SB(inode), "inode (%lu) has corrupted xattr",
								inode->i_ino);
		set_sbi_flag(F2FS_I_SB(inode), SBI_NEED_FSCK);
		err = -EFSCORRUPTED;
		जाओ out;
	पूर्ण
check:
	अगर (IS_XATTR_LAST_ENTRY(*xe)) अणु
		err = -ENODATA;
		जाओ out;
	पूर्ण

	*base_addr = txattr_addr;
	वापस 0;
out:
	xattr_मुक्त(F2FS_I_SB(inode), txattr_addr, *is_अंतरभूत);
	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_all_xattrs(काष्ठा inode *inode, काष्ठा page *ipage,
							व्योम **base_addr)
अणु
	काष्ठा f2fs_xattr_header *header;
	nid_t xnid = F2FS_I(inode)->i_xattr_nid;
	अचिन्हित पूर्णांक size = VALID_XATTR_BLOCK_SIZE;
	अचिन्हित पूर्णांक अंतरभूत_size = अंतरभूत_xattr_size(inode);
	व्योम *txattr_addr;
	पूर्णांक err;

	txattr_addr = f2fs_kzalloc(F2FS_I_SB(inode),
			अंतरभूत_size + size + XATTR_PADDING_SIZE, GFP_NOFS);
	अगर (!txattr_addr)
		वापस -ENOMEM;

	/* पढ़ो from अंतरभूत xattr */
	अगर (अंतरभूत_size) अणु
		err = पढ़ो_अंतरभूत_xattr(inode, ipage, txattr_addr);
		अगर (err)
			जाओ fail;
	पूर्ण

	/* पढ़ो from xattr node block */
	अगर (xnid) अणु
		err = पढ़ो_xattr_block(inode, txattr_addr);
		अगर (err)
			जाओ fail;
	पूर्ण

	header = XATTR_HDR(txattr_addr);

	/* never been allocated xattrs */
	अगर (le32_to_cpu(header->h_magic) != F2FS_XATTR_MAGIC) अणु
		header->h_magic = cpu_to_le32(F2FS_XATTR_MAGIC);
		header->h_refcount = cpu_to_le32(1);
	पूर्ण
	*base_addr = txattr_addr;
	वापस 0;
fail:
	kमुक्त(txattr_addr);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ग_लिखो_all_xattrs(काष्ठा inode *inode, __u32 hsize,
				व्योम *txattr_addr, काष्ठा page *ipage)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	माप_प्रकार अंतरभूत_size = अंतरभूत_xattr_size(inode);
	काष्ठा page *in_page = शून्य;
	व्योम *xattr_addr;
	व्योम *अंतरभूत_addr = शून्य;
	काष्ठा page *xpage;
	nid_t new_nid = 0;
	पूर्णांक err = 0;

	अगर (hsize > अंतरभूत_size && !F2FS_I(inode)->i_xattr_nid)
		अगर (!f2fs_alloc_nid(sbi, &new_nid))
			वापस -ENOSPC;

	/* ग_लिखो to अंतरभूत xattr */
	अगर (अंतरभूत_size) अणु
		अगर (ipage) अणु
			अंतरभूत_addr = अंतरभूत_xattr_addr(inode, ipage);
		पूर्ण अन्यथा अणु
			in_page = f2fs_get_node_page(sbi, inode->i_ino);
			अगर (IS_ERR(in_page)) अणु
				f2fs_alloc_nid_failed(sbi, new_nid);
				वापस PTR_ERR(in_page);
			पूर्ण
			अंतरभूत_addr = अंतरभूत_xattr_addr(inode, in_page);
		पूर्ण

		f2fs_रुको_on_page_ग_लिखोback(ipage ? ipage : in_page,
							NODE, true, true);
		/* no need to use xattr node block */
		अगर (hsize <= अंतरभूत_size) अणु
			err = f2fs_truncate_xattr_node(inode);
			f2fs_alloc_nid_failed(sbi, new_nid);
			अगर (err) अणु
				f2fs_put_page(in_page, 1);
				वापस err;
			पूर्ण
			स_नकल(अंतरभूत_addr, txattr_addr, अंतरभूत_size);
			set_page_dirty(ipage ? ipage : in_page);
			जाओ in_page_out;
		पूर्ण
	पूर्ण

	/* ग_लिखो to xattr node block */
	अगर (F2FS_I(inode)->i_xattr_nid) अणु
		xpage = f2fs_get_node_page(sbi, F2FS_I(inode)->i_xattr_nid);
		अगर (IS_ERR(xpage)) अणु
			err = PTR_ERR(xpage);
			f2fs_alloc_nid_failed(sbi, new_nid);
			जाओ in_page_out;
		पूर्ण
		f2fs_bug_on(sbi, new_nid);
		f2fs_रुको_on_page_ग_लिखोback(xpage, NODE, true, true);
	पूर्ण अन्यथा अणु
		काष्ठा dnode_of_data dn;

		set_new_dnode(&dn, inode, शून्य, शून्य, new_nid);
		xpage = f2fs_new_node_page(&dn, XATTR_NODE_OFFSET);
		अगर (IS_ERR(xpage)) अणु
			err = PTR_ERR(xpage);
			f2fs_alloc_nid_failed(sbi, new_nid);
			जाओ in_page_out;
		पूर्ण
		f2fs_alloc_nid_करोne(sbi, new_nid);
	पूर्ण
	xattr_addr = page_address(xpage);

	अगर (अंतरभूत_size)
		स_नकल(अंतरभूत_addr, txattr_addr, अंतरभूत_size);
	स_नकल(xattr_addr, txattr_addr + अंतरभूत_size, VALID_XATTR_BLOCK_SIZE);

	अगर (अंतरभूत_size)
		set_page_dirty(ipage ? ipage : in_page);
	set_page_dirty(xpage);

	f2fs_put_page(xpage, 1);
in_page_out:
	f2fs_put_page(in_page, 1);
	वापस err;
पूर्ण

पूर्णांक f2fs_getxattr(काष्ठा inode *inode, पूर्णांक index, स्थिर अक्षर *name,
		व्योम *buffer, माप_प्रकार buffer_size, काष्ठा page *ipage)
अणु
	काष्ठा f2fs_xattr_entry *entry = शून्य;
	पूर्णांक error;
	अचिन्हित पूर्णांक size, len;
	व्योम *base_addr = शून्य;
	पूर्णांक base_size;
	bool is_अंतरभूत;

	अगर (name == शून्य)
		वापस -EINVAL;

	len = म_माप(name);
	अगर (len > F2FS_NAME_LEN)
		वापस -दुस्फल;

	करोwn_पढ़ो(&F2FS_I(inode)->i_xattr_sem);
	error = lookup_all_xattrs(inode, ipage, index, len, name,
				&entry, &base_addr, &base_size, &is_अंतरभूत);
	up_पढ़ो(&F2FS_I(inode)->i_xattr_sem);
	अगर (error)
		वापस error;

	size = le16_to_cpu(entry->e_value_size);

	अगर (buffer && size > buffer_size) अणु
		error = -दुस्फल;
		जाओ out;
	पूर्ण

	अगर (buffer) अणु
		अक्षर *pval = entry->e_name + entry->e_name_len;

		अगर (base_size - (pval - (अक्षर *)base_addr) < size) अणु
			error = -दुस्फल;
			जाओ out;
		पूर्ण
		स_नकल(buffer, pval, size);
	पूर्ण
	error = size;
out:
	xattr_मुक्त(F2FS_I_SB(inode), base_addr, is_अंतरभूत);
	वापस error;
पूर्ण

sमाप_प्रकार f2fs_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा f2fs_xattr_entry *entry;
	व्योम *base_addr, *last_base_addr;
	पूर्णांक error;
	माप_प्रकार rest = buffer_size;

	करोwn_पढ़ो(&F2FS_I(inode)->i_xattr_sem);
	error = पढ़ो_all_xattrs(inode, शून्य, &base_addr);
	up_पढ़ो(&F2FS_I(inode)->i_xattr_sem);
	अगर (error)
		वापस error;

	last_base_addr = (व्योम *)base_addr + XATTR_SIZE(inode);

	list_क्रम_each_xattr(entry, base_addr) अणु
		स्थिर काष्ठा xattr_handler *handler =
			f2fs_xattr_handler(entry->e_name_index);
		स्थिर अक्षर *prefix;
		माप_प्रकार prefix_len;
		माप_प्रकार size;

		अगर ((व्योम *)(entry) + माप(__u32) > last_base_addr ||
			(व्योम *)XATTR_NEXT_ENTRY(entry) > last_base_addr) अणु
			f2fs_err(F2FS_I_SB(inode), "inode (%lu) has corrupted xattr",
						inode->i_ino);
			set_sbi_flag(F2FS_I_SB(inode), SBI_NEED_FSCK);
			error = -EFSCORRUPTED;
			जाओ cleanup;
		पूर्ण

		अगर (!handler || (handler->list && !handler->list(dentry)))
			जारी;

		prefix = xattr_prefix(handler);
		prefix_len = म_माप(prefix);
		size = prefix_len + entry->e_name_len + 1;
		अगर (buffer) अणु
			अगर (size > rest) अणु
				error = -दुस्फल;
				जाओ cleanup;
			पूर्ण
			स_नकल(buffer, prefix, prefix_len);
			buffer += prefix_len;
			स_नकल(buffer, entry->e_name, entry->e_name_len);
			buffer += entry->e_name_len;
			*buffer++ = 0;
		पूर्ण
		rest -= size;
	पूर्ण
	error = buffer_size - rest;
cleanup:
	kमुक्त(base_addr);
	वापस error;
पूर्ण

अटल bool f2fs_xattr_value_same(काष्ठा f2fs_xattr_entry *entry,
					स्थिर व्योम *value, माप_प्रकार size)
अणु
	व्योम *pval = entry->e_name + entry->e_name_len;

	वापस (le16_to_cpu(entry->e_value_size) == size) &&
					!स_भेद(pval, value, size);
पूर्ण

अटल पूर्णांक __f2fs_setxattr(काष्ठा inode *inode, पूर्णांक index,
			स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size,
			काष्ठा page *ipage, पूर्णांक flags)
अणु
	काष्ठा f2fs_xattr_entry *here, *last;
	व्योम *base_addr, *last_base_addr;
	पूर्णांक found, newsize;
	माप_प्रकार len;
	__u32 new_hsize;
	पूर्णांक error;

	अगर (name == शून्य)
		वापस -EINVAL;

	अगर (value == शून्य)
		size = 0;

	len = म_माप(name);

	अगर (len > F2FS_NAME_LEN)
		वापस -दुस्फल;

	अगर (size > MAX_VALUE_LEN(inode))
		वापस -E2BIG;

	error = पढ़ो_all_xattrs(inode, ipage, &base_addr);
	अगर (error)
		वापस error;

	last_base_addr = (व्योम *)base_addr + XATTR_SIZE(inode);

	/* find entry with wanted name. */
	here = __find_xattr(base_addr, last_base_addr, index, len, name);
	अगर (!here) अणु
		f2fs_err(F2FS_I_SB(inode), "inode (%lu) has corrupted xattr",
								inode->i_ino);
		set_sbi_flag(F2FS_I_SB(inode), SBI_NEED_FSCK);
		error = -EFSCORRUPTED;
		जाओ निकास;
	पूर्ण

	found = IS_XATTR_LAST_ENTRY(here) ? 0 : 1;

	अगर (found) अणु
		अगर ((flags & XATTR_CREATE)) अणु
			error = -EEXIST;
			जाओ निकास;
		पूर्ण

		अगर (value && f2fs_xattr_value_same(here, value, size))
			जाओ same;
	पूर्ण अन्यथा अगर ((flags & XATTR_REPLACE)) अणु
		error = -ENODATA;
		जाओ निकास;
	पूर्ण

	last = here;
	जबतक (!IS_XATTR_LAST_ENTRY(last))
		last = XATTR_NEXT_ENTRY(last);

	newsize = XATTR_ALIGN(माप(काष्ठा f2fs_xattr_entry) + len + size);

	/* 1. Check space */
	अगर (value) अणु
		पूर्णांक मुक्त;
		/*
		 * If value is शून्य, it is हटाओ operation.
		 * In हाल of update operation, we calculate मुक्त.
		 */
		मुक्त = MIN_OFFSET(inode) - ((अक्षर *)last - (अक्षर *)base_addr);
		अगर (found)
			मुक्त = मुक्त + ENTRY_SIZE(here);

		अगर (unlikely(मुक्त < newsize)) अणु
			error = -E2BIG;
			जाओ निकास;
		पूर्ण
	पूर्ण

	/* 2. Remove old entry */
	अगर (found) अणु
		/*
		 * If entry is found, हटाओ old entry.
		 * If not found, हटाओ operation is not needed.
		 */
		काष्ठा f2fs_xattr_entry *next = XATTR_NEXT_ENTRY(here);
		पूर्णांक oldsize = ENTRY_SIZE(here);

		स_हटाओ(here, next, (अक्षर *)last - (अक्षर *)next);
		last = (काष्ठा f2fs_xattr_entry *)((अक्षर *)last - oldsize);
		स_रखो(last, 0, oldsize);
	पूर्ण

	new_hsize = (अक्षर *)last - (अक्षर *)base_addr;

	/* 3. Write new entry */
	अगर (value) अणु
		अक्षर *pval;
		/*
		 * Beक्रमe we come here, old entry is हटाओd.
		 * We just ग_लिखो new entry.
		 */
		last->e_name_index = index;
		last->e_name_len = len;
		स_नकल(last->e_name, name, len);
		pval = last->e_name + len;
		स_नकल(pval, value, size);
		last->e_value_size = cpu_to_le16(size);
		new_hsize += newsize;
	पूर्ण

	error = ग_लिखो_all_xattrs(inode, new_hsize, base_addr, ipage);
	अगर (error)
		जाओ निकास;

	अगर (index == F2FS_XATTR_INDEX_ENCRYPTION &&
			!म_भेद(name, F2FS_XATTR_NAME_ENCRYPTION_CONTEXT))
		f2fs_set_encrypted_inode(inode);
	f2fs_mark_inode_dirty_sync(inode, true);
	अगर (!error && S_ISसूची(inode->i_mode))
		set_sbi_flag(F2FS_I_SB(inode), SBI_NEED_CP);

same:
	अगर (is_inode_flag_set(inode, FI_ACL_MODE)) अणु
		inode->i_mode = F2FS_I(inode)->i_acl_mode;
		inode->i_स_समय = current_समय(inode);
		clear_inode_flag(inode, FI_ACL_MODE);
	पूर्ण

निकास:
	kमुक्त(base_addr);
	वापस error;
पूर्ण

पूर्णांक f2fs_setxattr(काष्ठा inode *inode, पूर्णांक index, स्थिर अक्षर *name,
				स्थिर व्योम *value, माप_प्रकार size,
				काष्ठा page *ipage, पूर्णांक flags)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	पूर्णांक err;

	अगर (unlikely(f2fs_cp_error(sbi)))
		वापस -EIO;
	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi))
		वापस -ENOSPC;

	err = dquot_initialize(inode);
	अगर (err)
		वापस err;

	/* this हाल is only from f2fs_init_inode_metadata */
	अगर (ipage)
		वापस __f2fs_setxattr(inode, index, name, value,
						size, ipage, flags);
	f2fs_balance_fs(sbi, true);

	f2fs_lock_op(sbi);
	करोwn_ग_लिखो(&F2FS_I(inode)->i_xattr_sem);
	err = __f2fs_setxattr(inode, index, name, value, size, ipage, flags);
	up_ग_लिखो(&F2FS_I(inode)->i_xattr_sem);
	f2fs_unlock_op(sbi);

	f2fs_update_समय(sbi, REQ_TIME);
	वापस err;
पूर्ण

पूर्णांक f2fs_init_xattr_caches(काष्ठा f2fs_sb_info *sbi)
अणु
	dev_t dev = sbi->sb->s_bdev->bd_dev;
	अक्षर slab_name[32];

	प्र_लिखो(slab_name, "f2fs_xattr_entry-%u:%u", MAJOR(dev), MINOR(dev));

	sbi->अंतरभूत_xattr_slab_size = F2FS_OPTION(sbi).अंतरभूत_xattr_size *
					माप(__le32) + XATTR_PADDING_SIZE;

	sbi->अंतरभूत_xattr_slab = f2fs_kmem_cache_create(slab_name,
					sbi->अंतरभूत_xattr_slab_size);
	अगर (!sbi->अंतरभूत_xattr_slab)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम f2fs_destroy_xattr_caches(काष्ठा f2fs_sb_info *sbi)
अणु
	kmem_cache_destroy(sbi->अंतरभूत_xattr_slab);
पूर्ण
