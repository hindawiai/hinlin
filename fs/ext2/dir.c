<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext2/dir.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/dir.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  ext2 directory handling functions
 *
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 *
 * All code that works with directory layout had been चयनed to pagecache
 * and moved here. AV
 */

#समावेश "ext2.h"
#समावेश <linux/buffer_head.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/iversion.h>

प्रकार काष्ठा ext2_dir_entry_2 ext2_dirent;

/*
 * Tests against MAX_REC_LEN etc were put in place क्रम 64k block
 * sizes; अगर that is not possible on this arch, we can skip
 * those tests and speed things up.
 */
अटल अंतरभूत अचिन्हित ext2_rec_len_from_disk(__le16 dlen)
अणु
	अचिन्हित len = le16_to_cpu(dlen);

#अगर (PAGE_SIZE >= 65536)
	अगर (len == EXT2_MAX_REC_LEN)
		वापस 1 << 16;
#पूर्ण_अगर
	वापस len;
पूर्ण

अटल अंतरभूत __le16 ext2_rec_len_to_disk(अचिन्हित len)
अणु
#अगर (PAGE_SIZE >= 65536)
	अगर (len == (1 << 16))
		वापस cpu_to_le16(EXT2_MAX_REC_LEN);
	अन्यथा
		BUG_ON(len > (1 << 16));
#पूर्ण_अगर
	वापस cpu_to_le16(len);
पूर्ण

/*
 * ext2 uses block-sized chunks. Arguably, sector-sized ones would be
 * more robust, but we have what we have
 */
अटल अंतरभूत अचिन्हित ext2_chunk_size(काष्ठा inode *inode)
अणु
	वापस inode->i_sb->s_blocksize;
पूर्ण

/*
 * Return the offset पूर्णांकo page `page_nr' of the last valid
 * byte in that page, plus one.
 */
अटल अचिन्हित
ext2_last_byte(काष्ठा inode *inode, अचिन्हित दीर्घ page_nr)
अणु
	अचिन्हित last_byte = inode->i_size;

	last_byte -= page_nr << PAGE_SHIFT;
	अगर (last_byte > PAGE_SIZE)
		last_byte = PAGE_SIZE;
	वापस last_byte;
पूर्ण

अटल पूर्णांक ext2_commit_chunk(काष्ठा page *page, loff_t pos, अचिन्हित len)
अणु
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा inode *dir = mapping->host;
	पूर्णांक err = 0;

	inode_inc_iversion(dir);
	block_ग_लिखो_end(शून्य, mapping, pos, len, len, page, शून्य);

	अगर (pos+len > dir->i_size) अणु
		i_size_ग_लिखो(dir, pos+len);
		mark_inode_dirty(dir);
	पूर्ण

	अगर (IS_सूचीSYNC(dir)) अणु
		err = ग_लिखो_one_page(page);
		अगर (!err)
			err = sync_inode_metadata(dir, 1);
	पूर्ण अन्यथा अणु
		unlock_page(page);
	पूर्ण

	वापस err;
पूर्ण

अटल bool ext2_check_page(काष्ठा page *page, पूर्णांक quiet)
अणु
	काष्ठा inode *dir = page->mapping->host;
	काष्ठा super_block *sb = dir->i_sb;
	अचिन्हित chunk_size = ext2_chunk_size(dir);
	अक्षर *kaddr = page_address(page);
	u32 max_inumber = le32_to_cpu(EXT2_SB(sb)->s_es->s_inodes_count);
	अचिन्हित offs, rec_len;
	अचिन्हित limit = PAGE_SIZE;
	ext2_dirent *p;
	अक्षर *error;

	अगर ((dir->i_size >> PAGE_SHIFT) == page->index) अणु
		limit = dir->i_size & ~PAGE_MASK;
		अगर (limit & (chunk_size - 1))
			जाओ Ebadsize;
		अगर (!limit)
			जाओ out;
	पूर्ण
	क्रम (offs = 0; offs <= limit - EXT2_सूची_REC_LEN(1); offs += rec_len) अणु
		p = (ext2_dirent *)(kaddr + offs);
		rec_len = ext2_rec_len_from_disk(p->rec_len);

		अगर (unlikely(rec_len < EXT2_सूची_REC_LEN(1)))
			जाओ Eलघु;
		अगर (unlikely(rec_len & 3))
			जाओ Ealign;
		अगर (unlikely(rec_len < EXT2_सूची_REC_LEN(p->name_len)))
			जाओ Enamelen;
		अगर (unlikely(((offs + rec_len - 1) ^ offs) & ~(chunk_size-1)))
			जाओ Espan;
		अगर (unlikely(le32_to_cpu(p->inode) > max_inumber))
			जाओ Einumber;
	पूर्ण
	अगर (offs != limit)
		जाओ Eend;
out:
	SetPageChecked(page);
	वापस true;

	/* Too bad, we had an error */

Ebadsize:
	अगर (!quiet)
		ext2_error(sb, __func__,
			"size of directory #%lu is not a multiple "
			"of chunk size", dir->i_ino);
	जाओ fail;
Eलघु:
	error = "rec_len is smaller than minimal";
	जाओ bad_entry;
Ealign:
	error = "unaligned directory entry";
	जाओ bad_entry;
Enamelen:
	error = "rec_len is too small for name_len";
	जाओ bad_entry;
Espan:
	error = "directory entry across blocks";
	जाओ bad_entry;
Einumber:
	error = "inode out of bounds";
bad_entry:
	अगर (!quiet)
		ext2_error(sb, __func__, "bad entry in directory #%lu: : %s - "
			"offset=%lu, inode=%lu, rec_len=%d, name_len=%d",
			dir->i_ino, error, (page->index<<PAGE_SHIFT)+offs,
			(अचिन्हित दीर्घ) le32_to_cpu(p->inode),
			rec_len, p->name_len);
	जाओ fail;
Eend:
	अगर (!quiet) अणु
		p = (ext2_dirent *)(kaddr + offs);
		ext2_error(sb, "ext2_check_page",
			"entry in directory #%lu spans the page boundary"
			"offset=%lu, inode=%lu",
			dir->i_ino, (page->index<<PAGE_SHIFT)+offs,
			(अचिन्हित दीर्घ) le32_to_cpu(p->inode));
	पूर्ण
fail:
	SetPageError(page);
	वापस false;
पूर्ण

/*
 * Calls to ext2_get_page()/ext2_put_page() must be nested according to the
 * rules करोcumented in kmap_local_page()/kunmap_local().
 *
 * NOTE: ext2_find_entry() and ext2_करोtकरोt() act as a call to ext2_get_page()
 * and should be treated as a call to ext2_get_page() क्रम nesting purposes.
 */
अटल काष्ठा page * ext2_get_page(काष्ठा inode *dir, अचिन्हित दीर्घ n,
				   पूर्णांक quiet, व्योम **page_addr)
अणु
	काष्ठा address_space *mapping = dir->i_mapping;
	काष्ठा page *page = पढ़ो_mapping_page(mapping, n, शून्य);
	अगर (!IS_ERR(page)) अणु
		*page_addr = kmap_local_page(page);
		अगर (unlikely(!PageChecked(page))) अणु
			अगर (PageError(page) || !ext2_check_page(page, quiet))
				जाओ fail;
		पूर्ण
	पूर्ण
	वापस page;

fail:
	ext2_put_page(page, *page_addr);
	वापस ERR_PTR(-EIO);
पूर्ण

/*
 * NOTE! unlike म_भेदन, ext2_match वापसs 1 क्रम success, 0 क्रम failure.
 *
 * len <= EXT2_NAME_LEN and de != शून्य are guaranteed by caller.
 */
अटल अंतरभूत पूर्णांक ext2_match (पूर्णांक len, स्थिर अक्षर * स्थिर name,
					काष्ठा ext2_dir_entry_2 * de)
अणु
	अगर (len != de->name_len)
		वापस 0;
	अगर (!de->inode)
		वापस 0;
	वापस !स_भेद(name, de->name, len);
पूर्ण

/*
 * p is at least 6 bytes beक्रमe the end of page
 */
अटल अंतरभूत ext2_dirent *ext2_next_entry(ext2_dirent *p)
अणु
	वापस (ext2_dirent *)((अक्षर *)p +
			ext2_rec_len_from_disk(p->rec_len));
पूर्ण

अटल अंतरभूत अचिन्हित 
ext2_validate_entry(अक्षर *base, अचिन्हित offset, अचिन्हित mask)
अणु
	ext2_dirent *de = (ext2_dirent*)(base + offset);
	ext2_dirent *p = (ext2_dirent*)(base + (offset&mask));
	जबतक ((अक्षर*)p < (अक्षर*)de) अणु
		अगर (p->rec_len == 0)
			अवरोध;
		p = ext2_next_entry(p);
	पूर्ण
	वापस (अक्षर *)p - base;
पूर्ण

अटल अंतरभूत व्योम ext2_set_de_type(ext2_dirent *de, काष्ठा inode *inode)
अणु
	अगर (EXT2_HAS_INCOMPAT_FEATURE(inode->i_sb, EXT2_FEATURE_INCOMPAT_खाताTYPE))
		de->file_type = fs_umode_to_ftype(inode->i_mode);
	अन्यथा
		de->file_type = 0;
पूर्ण

अटल पूर्णांक
ext2_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	loff_t pos = ctx->pos;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;
	अचिन्हित पूर्णांक offset = pos & ~PAGE_MASK;
	अचिन्हित दीर्घ n = pos >> PAGE_SHIFT;
	अचिन्हित दीर्घ npages = dir_pages(inode);
	अचिन्हित chunk_mask = ~(ext2_chunk_size(inode)-1);
	bool need_revalidate = !inode_eq_iversion(inode, file->f_version);
	bool has_filetype;

	अगर (pos > inode->i_size - EXT2_सूची_REC_LEN(1))
		वापस 0;

	has_filetype =
		EXT2_HAS_INCOMPAT_FEATURE(sb, EXT2_FEATURE_INCOMPAT_खाताTYPE);

	क्रम ( ; n < npages; n++, offset = 0) अणु
		अक्षर *kaddr, *limit;
		ext2_dirent *de;
		काष्ठा page *page = ext2_get_page(inode, n, 0, (व्योम **)&kaddr);

		अगर (IS_ERR(page)) अणु
			ext2_error(sb, __func__,
				   "bad page in #%lu",
				   inode->i_ino);
			ctx->pos += PAGE_SIZE - offset;
			वापस PTR_ERR(page);
		पूर्ण
		अगर (unlikely(need_revalidate)) अणु
			अगर (offset) अणु
				offset = ext2_validate_entry(kaddr, offset, chunk_mask);
				ctx->pos = (n<<PAGE_SHIFT) + offset;
			पूर्ण
			file->f_version = inode_query_iversion(inode);
			need_revalidate = false;
		पूर्ण
		de = (ext2_dirent *)(kaddr+offset);
		limit = kaddr + ext2_last_byte(inode, n) - EXT2_सूची_REC_LEN(1);
		क्रम ( ;(अक्षर*)de <= limit; de = ext2_next_entry(de)) अणु
			अगर (de->rec_len == 0) अणु
				ext2_error(sb, __func__,
					"zero-length directory entry");
				ext2_put_page(page, kaddr);
				वापस -EIO;
			पूर्ण
			अगर (de->inode) अणु
				अचिन्हित अक्षर d_type = DT_UNKNOWN;

				अगर (has_filetype)
					d_type = fs_ftype_to_dtype(de->file_type);

				अगर (!dir_emit(ctx, de->name, de->name_len,
						le32_to_cpu(de->inode),
						d_type)) अणु
					ext2_put_page(page, kaddr);
					वापस 0;
				पूर्ण
			पूर्ण
			ctx->pos += ext2_rec_len_from_disk(de->rec_len);
		पूर्ण
		ext2_put_page(page, kaddr);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	ext2_find_entry()
 *
 * finds an entry in the specअगरied directory with the wanted name. It
 * वापसs the page in which the entry was found (as a parameter - res_page),
 * and the entry itself. Page is वापसed mapped and unlocked.
 * Entry is guaranteed to be valid.
 *
 * On Success ext2_put_page() should be called on *res_page.
 *
 * NOTE: Calls to ext2_get_page()/ext2_put_page() must be nested according to
 * the rules करोcumented in kmap_local_page()/kunmap_local().
 *
 * ext2_find_entry() and ext2_करोtकरोt() act as a call to ext2_get_page() and
 * should be treated as a call to ext2_get_page() क्रम nesting purposes.
 */
काष्ठा ext2_dir_entry_2 *ext2_find_entry (काष्ठा inode *dir,
			स्थिर काष्ठा qstr *child, काष्ठा page **res_page,
			व्योम **res_page_addr)
अणु
	स्थिर अक्षर *name = child->name;
	पूर्णांक namelen = child->len;
	अचिन्हित reclen = EXT2_सूची_REC_LEN(namelen);
	अचिन्हित दीर्घ start, n;
	अचिन्हित दीर्घ npages = dir_pages(dir);
	काष्ठा page *page = शून्य;
	काष्ठा ext2_inode_info *ei = EXT2_I(dir);
	ext2_dirent * de;
	व्योम *page_addr;

	अगर (npages == 0)
		जाओ out;

	/* OFFSET_CACHE */
	*res_page = शून्य;
	*res_page_addr = शून्य;

	start = ei->i_dir_start_lookup;
	अगर (start >= npages)
		start = 0;
	n = start;
	करो अणु
		अक्षर *kaddr;
		page = ext2_get_page(dir, n, 0, &page_addr);
		अगर (IS_ERR(page))
			वापस ERR_CAST(page);

		kaddr = page_addr;
		de = (ext2_dirent *) kaddr;
		kaddr += ext2_last_byte(dir, n) - reclen;
		जबतक ((अक्षर *) de <= kaddr) अणु
			अगर (de->rec_len == 0) अणु
				ext2_error(dir->i_sb, __func__,
					"zero-length directory entry");
				ext2_put_page(page, page_addr);
				जाओ out;
			पूर्ण
			अगर (ext2_match(namelen, name, de))
				जाओ found;
			de = ext2_next_entry(de);
		पूर्ण
		ext2_put_page(page, page_addr);

		अगर (++n >= npages)
			n = 0;
		/* next page is past the blocks we've got */
		अगर (unlikely(n > (dir->i_blocks >> (PAGE_SHIFT - 9)))) अणु
			ext2_error(dir->i_sb, __func__,
				"dir %lu size %lld exceeds block count %llu",
				dir->i_ino, dir->i_size,
				(अचिन्हित दीर्घ दीर्घ)dir->i_blocks);
			जाओ out;
		पूर्ण
	पूर्ण जबतक (n != start);
out:
	वापस ERR_PTR(-ENOENT);

found:
	*res_page = page;
	*res_page_addr = page_addr;
	ei->i_dir_start_lookup = n;
	वापस de;
पूर्ण

/**
 * Return the '..' directory entry and the page in which the entry was found
 * (as a parameter - p).
 *
 * On Success ext2_put_page() should be called on *p.
 *
 * NOTE: Calls to ext2_get_page()/ext2_put_page() must be nested according to
 * the rules करोcumented in kmap_local_page()/kunmap_local().
 *
 * ext2_find_entry() and ext2_करोtकरोt() act as a call to ext2_get_page() and
 * should be treated as a call to ext2_get_page() क्रम nesting purposes.
 */
काष्ठा ext2_dir_entry_2 *ext2_करोtकरोt(काष्ठा inode *dir, काष्ठा page **p,
				     व्योम **pa)
अणु
	व्योम *page_addr;
	काष्ठा page *page = ext2_get_page(dir, 0, 0, &page_addr);
	ext2_dirent *de = शून्य;

	अगर (!IS_ERR(page)) अणु
		de = ext2_next_entry((ext2_dirent *) page_addr);
		*p = page;
		*pa = page_addr;
	पूर्ण
	वापस de;
पूर्ण

पूर्णांक ext2_inode_by_name(काष्ठा inode *dir, स्थिर काष्ठा qstr *child, ino_t *ino)
अणु
	काष्ठा ext2_dir_entry_2 *de;
	काष्ठा page *page;
	व्योम *page_addr;
	
	de = ext2_find_entry(dir, child, &page, &page_addr);
	अगर (IS_ERR(de))
		वापस PTR_ERR(de);

	*ino = le32_to_cpu(de->inode);
	ext2_put_page(page, page_addr);
	वापस 0;
पूर्ण

अटल पूर्णांक ext2_prepare_chunk(काष्ठा page *page, loff_t pos, अचिन्हित len)
अणु
	वापस __block_ग_लिखो_begin(page, pos, len, ext2_get_block);
पूर्ण

व्योम ext2_set_link(काष्ठा inode *dir, काष्ठा ext2_dir_entry_2 *de,
		   काष्ठा page *page, व्योम *page_addr, काष्ठा inode *inode,
		   पूर्णांक update_बार)
अणु
	loff_t pos = page_offset(page) +
			(अक्षर *) de - (अक्षर *) page_addr;
	अचिन्हित len = ext2_rec_len_from_disk(de->rec_len);
	पूर्णांक err;

	lock_page(page);
	err = ext2_prepare_chunk(page, pos, len);
	BUG_ON(err);
	de->inode = cpu_to_le32(inode->i_ino);
	ext2_set_de_type(de, inode);
	err = ext2_commit_chunk(page, pos, len);
	अगर (update_बार)
		dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	EXT2_I(dir)->i_flags &= ~EXT2_BTREE_FL;
	mark_inode_dirty(dir);
पूर्ण

/*
 *	Parent is locked.
 */
पूर्णांक ext2_add_link (काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	स्थिर अक्षर *name = dentry->d_name.name;
	पूर्णांक namelen = dentry->d_name.len;
	अचिन्हित chunk_size = ext2_chunk_size(dir);
	अचिन्हित reclen = EXT2_सूची_REC_LEN(namelen);
	अचिन्हित लघु rec_len, name_len;
	काष्ठा page *page = शून्य;
	व्योम *page_addr = शून्य;
	ext2_dirent * de;
	अचिन्हित दीर्घ npages = dir_pages(dir);
	अचिन्हित दीर्घ n;
	loff_t pos;
	पूर्णांक err;

	/*
	 * We take care of directory expansion in the same loop.
	 * This code plays outside i_size, so it locks the page
	 * to protect that region.
	 */
	क्रम (n = 0; n <= npages; n++) अणु
		अक्षर *kaddr;
		अक्षर *dir_end;

		page = ext2_get_page(dir, n, 0, &page_addr);
		err = PTR_ERR(page);
		अगर (IS_ERR(page))
			जाओ out;
		lock_page(page);
		kaddr = page_addr;
		dir_end = kaddr + ext2_last_byte(dir, n);
		de = (ext2_dirent *)kaddr;
		kaddr += PAGE_SIZE - reclen;
		जबतक ((अक्षर *)de <= kaddr) अणु
			अगर ((अक्षर *)de == dir_end) अणु
				/* We hit i_size */
				name_len = 0;
				rec_len = chunk_size;
				de->rec_len = ext2_rec_len_to_disk(chunk_size);
				de->inode = 0;
				जाओ got_it;
			पूर्ण
			अगर (de->rec_len == 0) अणु
				ext2_error(dir->i_sb, __func__,
					"zero-length directory entry");
				err = -EIO;
				जाओ out_unlock;
			पूर्ण
			err = -EEXIST;
			अगर (ext2_match (namelen, name, de))
				जाओ out_unlock;
			name_len = EXT2_सूची_REC_LEN(de->name_len);
			rec_len = ext2_rec_len_from_disk(de->rec_len);
			अगर (!de->inode && rec_len >= reclen)
				जाओ got_it;
			अगर (rec_len >= name_len + reclen)
				जाओ got_it;
			de = (ext2_dirent *) ((अक्षर *) de + rec_len);
		पूर्ण
		unlock_page(page);
		ext2_put_page(page, page_addr);
	पूर्ण
	BUG();
	वापस -EINVAL;

got_it:
	pos = page_offset(page) +
		(अक्षर *)de - (अक्षर *)page_addr;
	err = ext2_prepare_chunk(page, pos, rec_len);
	अगर (err)
		जाओ out_unlock;
	अगर (de->inode) अणु
		ext2_dirent *de1 = (ext2_dirent *) ((अक्षर *) de + name_len);
		de1->rec_len = ext2_rec_len_to_disk(rec_len - name_len);
		de->rec_len = ext2_rec_len_to_disk(name_len);
		de = de1;
	पूर्ण
	de->name_len = namelen;
	स_नकल(de->name, name, namelen);
	de->inode = cpu_to_le32(inode->i_ino);
	ext2_set_de_type (de, inode);
	err = ext2_commit_chunk(page, pos, rec_len);
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	EXT2_I(dir)->i_flags &= ~EXT2_BTREE_FL;
	mark_inode_dirty(dir);
	/* OFFSET_CACHE */
out_put:
	ext2_put_page(page, page_addr);
out:
	वापस err;
out_unlock:
	unlock_page(page);
	जाओ out_put;
पूर्ण

/*
 * ext2_delete_entry deletes a directory entry by merging it with the
 * previous entry. Page is up-to-date.
 */
पूर्णांक ext2_delete_entry (काष्ठा ext2_dir_entry_2 * dir, काष्ठा page * page )
अणु
	काष्ठा inode *inode = page->mapping->host;
	अक्षर *kaddr = page_address(page);
	अचिन्हित from = ((अक्षर*)dir - kaddr) & ~(ext2_chunk_size(inode)-1);
	अचिन्हित to = ((अक्षर *)dir - kaddr) +
				ext2_rec_len_from_disk(dir->rec_len);
	loff_t pos;
	ext2_dirent * pde = शून्य;
	ext2_dirent * de = (ext2_dirent *) (kaddr + from);
	पूर्णांक err;

	जबतक ((अक्षर*)de < (अक्षर*)dir) अणु
		अगर (de->rec_len == 0) अणु
			ext2_error(inode->i_sb, __func__,
				"zero-length directory entry");
			err = -EIO;
			जाओ out;
		पूर्ण
		pde = de;
		de = ext2_next_entry(de);
	पूर्ण
	अगर (pde)
		from = (अक्षर*)pde - (अक्षर*)page_address(page);
	pos = page_offset(page) + from;
	lock_page(page);
	err = ext2_prepare_chunk(page, pos, to - from);
	BUG_ON(err);
	अगर (pde)
		pde->rec_len = ext2_rec_len_to_disk(to - from);
	dir->inode = 0;
	err = ext2_commit_chunk(page, pos, to - from);
	inode->i_स_समय = inode->i_mसमय = current_समय(inode);
	EXT2_I(inode)->i_flags &= ~EXT2_BTREE_FL;
	mark_inode_dirty(inode);
out:
	वापस err;
पूर्ण

/*
 * Set the first fragment of directory.
 */
पूर्णांक ext2_make_empty(काष्ठा inode *inode, काष्ठा inode *parent)
अणु
	काष्ठा page *page = grab_cache_page(inode->i_mapping, 0);
	अचिन्हित chunk_size = ext2_chunk_size(inode);
	काष्ठा ext2_dir_entry_2 * de;
	पूर्णांक err;
	व्योम *kaddr;

	अगर (!page)
		वापस -ENOMEM;

	err = ext2_prepare_chunk(page, 0, chunk_size);
	अगर (err) अणु
		unlock_page(page);
		जाओ fail;
	पूर्ण
	kaddr = kmap_atomic(page);
	स_रखो(kaddr, 0, chunk_size);
	de = (काष्ठा ext2_dir_entry_2 *)kaddr;
	de->name_len = 1;
	de->rec_len = ext2_rec_len_to_disk(EXT2_सूची_REC_LEN(1));
	स_नकल (de->name, ".\0\0", 4);
	de->inode = cpu_to_le32(inode->i_ino);
	ext2_set_de_type (de, inode);

	de = (काष्ठा ext2_dir_entry_2 *)(kaddr + EXT2_सूची_REC_LEN(1));
	de->name_len = 2;
	de->rec_len = ext2_rec_len_to_disk(chunk_size - EXT2_सूची_REC_LEN(1));
	de->inode = cpu_to_le32(parent->i_ino);
	स_नकल (de->name, "..\0", 4);
	ext2_set_de_type (de, inode);
	kunmap_atomic(kaddr);
	err = ext2_commit_chunk(page, 0, chunk_size);
fail:
	put_page(page);
	वापस err;
पूर्ण

/*
 * routine to check that the specअगरied directory is empty (क्रम सूची_हटाओ)
 */
पूर्णांक ext2_empty_dir (काष्ठा inode * inode)
अणु
	व्योम *page_addr = शून्य;
	काष्ठा page *page = शून्य;
	अचिन्हित दीर्घ i, npages = dir_pages(inode);
	पूर्णांक dir_has_error = 0;

	क्रम (i = 0; i < npages; i++) अणु
		अक्षर *kaddr;
		ext2_dirent * de;
		page = ext2_get_page(inode, i, dir_has_error, &page_addr);

		अगर (IS_ERR(page)) अणु
			dir_has_error = 1;
			जारी;
		पूर्ण

		kaddr = page_addr;
		de = (ext2_dirent *)kaddr;
		kaddr += ext2_last_byte(inode, i) - EXT2_सूची_REC_LEN(1);

		जबतक ((अक्षर *)de <= kaddr) अणु
			अगर (de->rec_len == 0) अणु
				ext2_error(inode->i_sb, __func__,
					"zero-length directory entry");
				prपूर्णांकk("kaddr=%p, de=%p\n", kaddr, de);
				जाओ not_empty;
			पूर्ण
			अगर (de->inode != 0) अणु
				/* check क्रम . and .. */
				अगर (de->name[0] != '.')
					जाओ not_empty;
				अगर (de->name_len > 2)
					जाओ not_empty;
				अगर (de->name_len < 2) अणु
					अगर (de->inode !=
					    cpu_to_le32(inode->i_ino))
						जाओ not_empty;
				पूर्ण अन्यथा अगर (de->name[1] != '.')
					जाओ not_empty;
			पूर्ण
			de = ext2_next_entry(de);
		पूर्ण
		ext2_put_page(page, page_addr);
	पूर्ण
	वापस 1;

not_empty:
	ext2_put_page(page, page_addr);
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations ext2_dir_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= ext2_सूची_पढ़ो,
	.unlocked_ioctl = ext2_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= ext2_compat_ioctl,
#पूर्ण_अगर
	.fsync		= ext2_fsync,
पूर्ण;
