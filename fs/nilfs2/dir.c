<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * dir.c - NILFS directory entry operations
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Modअगरied क्रम NILFS by Amagai Yoshiji.
 */
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

#समावेश <linux/pagemap.h>
#समावेश "nilfs.h"
#समावेश "page.h"

अटल अंतरभूत अचिन्हित पूर्णांक nilfs_rec_len_from_disk(__le16 dlen)
अणु
	अचिन्हित पूर्णांक len = le16_to_cpu(dlen);

#अगर (PAGE_SIZE >= 65536)
	अगर (len == NILFS_MAX_REC_LEN)
		वापस 1 << 16;
#पूर्ण_अगर
	वापस len;
पूर्ण

अटल अंतरभूत __le16 nilfs_rec_len_to_disk(अचिन्हित पूर्णांक len)
अणु
#अगर (PAGE_SIZE >= 65536)
	अगर (len == (1 << 16))
		वापस cpu_to_le16(NILFS_MAX_REC_LEN);

	BUG_ON(len > (1 << 16));
#पूर्ण_अगर
	वापस cpu_to_le16(len);
पूर्ण

/*
 * nilfs uses block-sized chunks. Arguably, sector-sized ones would be
 * more robust, but we have what we have
 */
अटल अंतरभूत अचिन्हित पूर्णांक nilfs_chunk_size(काष्ठा inode *inode)
अणु
	वापस inode->i_sb->s_blocksize;
पूर्ण

अटल अंतरभूत व्योम nilfs_put_page(काष्ठा page *page)
अणु
	kunmap(page);
	put_page(page);
पूर्ण

/*
 * Return the offset पूर्णांकo page `page_nr' of the last valid
 * byte in that page, plus one.
 */
अटल अचिन्हित पूर्णांक nilfs_last_byte(काष्ठा inode *inode, अचिन्हित दीर्घ page_nr)
अणु
	अचिन्हित पूर्णांक last_byte = inode->i_size;

	last_byte -= page_nr << PAGE_SHIFT;
	अगर (last_byte > PAGE_SIZE)
		last_byte = PAGE_SIZE;
	वापस last_byte;
पूर्ण

अटल पूर्णांक nilfs_prepare_chunk(काष्ठा page *page, अचिन्हित पूर्णांक from,
			       अचिन्हित पूर्णांक to)
अणु
	loff_t pos = page_offset(page) + from;

	वापस __block_ग_लिखो_begin(page, pos, to - from, nilfs_get_block);
पूर्ण

अटल व्योम nilfs_commit_chunk(काष्ठा page *page,
			       काष्ठा address_space *mapping,
			       अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
	काष्ठा inode *dir = mapping->host;
	loff_t pos = page_offset(page) + from;
	अचिन्हित पूर्णांक len = to - from;
	अचिन्हित पूर्णांक nr_dirty, copied;
	पूर्णांक err;

	nr_dirty = nilfs_page_count_clean_buffers(page, from, to);
	copied = block_ग_लिखो_end(शून्य, mapping, pos, len, len, page, शून्य);
	अगर (pos + copied > dir->i_size)
		i_size_ग_लिखो(dir, pos + copied);
	अगर (IS_सूचीSYNC(dir))
		nilfs_set_transaction_flag(NILFS_TI_SYNC);
	err = nilfs_set_file_dirty(dir, nr_dirty);
	WARN_ON(err); /* करो not happen */
	unlock_page(page);
पूर्ण

अटल bool nilfs_check_page(काष्ठा page *page)
अणु
	काष्ठा inode *dir = page->mapping->host;
	काष्ठा super_block *sb = dir->i_sb;
	अचिन्हित पूर्णांक chunk_size = nilfs_chunk_size(dir);
	अक्षर *kaddr = page_address(page);
	अचिन्हित पूर्णांक offs, rec_len;
	अचिन्हित पूर्णांक limit = PAGE_SIZE;
	काष्ठा nilfs_dir_entry *p;
	अक्षर *error;

	अगर ((dir->i_size >> PAGE_SHIFT) == page->index) अणु
		limit = dir->i_size & ~PAGE_MASK;
		अगर (limit & (chunk_size - 1))
			जाओ Ebadsize;
		अगर (!limit)
			जाओ out;
	पूर्ण
	क्रम (offs = 0; offs <= limit - NILFS_सूची_REC_LEN(1); offs += rec_len) अणु
		p = (काष्ठा nilfs_dir_entry *)(kaddr + offs);
		rec_len = nilfs_rec_len_from_disk(p->rec_len);

		अगर (rec_len < NILFS_सूची_REC_LEN(1))
			जाओ Eलघु;
		अगर (rec_len & 3)
			जाओ Ealign;
		अगर (rec_len < NILFS_सूची_REC_LEN(p->name_len))
			जाओ Enamelen;
		अगर (((offs + rec_len - 1) ^ offs) & ~(chunk_size-1))
			जाओ Espan;
	पूर्ण
	अगर (offs != limit)
		जाओ Eend;
out:
	SetPageChecked(page);
	वापस true;

	/* Too bad, we had an error */

Ebadsize:
	nilfs_error(sb,
		    "size of directory #%lu is not a multiple of chunk size",
		    dir->i_ino);
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
bad_entry:
	nilfs_error(sb,
		    "bad entry in directory #%lu: %s - offset=%lu, inode=%lu, rec_len=%d, name_len=%d",
		    dir->i_ino, error, (page->index << PAGE_SHIFT) + offs,
		    (अचिन्हित दीर्घ)le64_to_cpu(p->inode),
		    rec_len, p->name_len);
	जाओ fail;
Eend:
	p = (काष्ठा nilfs_dir_entry *)(kaddr + offs);
	nilfs_error(sb,
		    "entry in directory #%lu spans the page boundary offset=%lu, inode=%lu",
		    dir->i_ino, (page->index << PAGE_SHIFT) + offs,
		    (अचिन्हित दीर्घ)le64_to_cpu(p->inode));
fail:
	SetPageError(page);
	वापस false;
पूर्ण

अटल काष्ठा page *nilfs_get_page(काष्ठा inode *dir, अचिन्हित दीर्घ n)
अणु
	काष्ठा address_space *mapping = dir->i_mapping;
	काष्ठा page *page = पढ़ो_mapping_page(mapping, n, शून्य);

	अगर (!IS_ERR(page)) अणु
		kmap(page);
		अगर (unlikely(!PageChecked(page))) अणु
			अगर (PageError(page) || !nilfs_check_page(page))
				जाओ fail;
		पूर्ण
	पूर्ण
	वापस page;

fail:
	nilfs_put_page(page);
	वापस ERR_PTR(-EIO);
पूर्ण

/*
 * NOTE! unlike म_भेदन, nilfs_match वापसs 1 क्रम success, 0 क्रम failure.
 *
 * len <= NILFS_NAME_LEN and de != शून्य are guaranteed by caller.
 */
अटल पूर्णांक
nilfs_match(पूर्णांक len, स्थिर अचिन्हित अक्षर *name, काष्ठा nilfs_dir_entry *de)
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
अटल काष्ठा nilfs_dir_entry *nilfs_next_entry(काष्ठा nilfs_dir_entry *p)
अणु
	वापस (काष्ठा nilfs_dir_entry *)((अक्षर *)p +
					  nilfs_rec_len_from_disk(p->rec_len));
पूर्ण

अटल अचिन्हित अक्षर
nilfs_filetype_table[NILFS_FT_MAX] = अणु
	[NILFS_FT_UNKNOWN]	= DT_UNKNOWN,
	[NILFS_FT_REG_खाता]	= DT_REG,
	[NILFS_FT_सूची]		= DT_सूची,
	[NILFS_FT_CHRDEV]	= DT_CHR,
	[NILFS_FT_BLKDEV]	= DT_BLK,
	[NILFS_FT_FIFO]		= DT_FIFO,
	[NILFS_FT_SOCK]		= DT_SOCK,
	[NILFS_FT_SYMLINK]	= DT_LNK,
पूर्ण;

#घोषणा S_SHIFT 12
अटल अचिन्हित अक्षर
nilfs_type_by_mode[S_IFMT >> S_SHIFT] = अणु
	[S_IFREG >> S_SHIFT]	= NILFS_FT_REG_खाता,
	[S_IFसूची >> S_SHIFT]	= NILFS_FT_सूची,
	[S_IFCHR >> S_SHIFT]	= NILFS_FT_CHRDEV,
	[S_IFBLK >> S_SHIFT]	= NILFS_FT_BLKDEV,
	[S_IFIFO >> S_SHIFT]	= NILFS_FT_FIFO,
	[S_IFSOCK >> S_SHIFT]	= NILFS_FT_SOCK,
	[S_IFLNK >> S_SHIFT]	= NILFS_FT_SYMLINK,
पूर्ण;

अटल व्योम nilfs_set_de_type(काष्ठा nilfs_dir_entry *de, काष्ठा inode *inode)
अणु
	umode_t mode = inode->i_mode;

	de->file_type = nilfs_type_by_mode[(mode & S_IFMT)>>S_SHIFT];
पूर्ण

अटल पूर्णांक nilfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	loff_t pos = ctx->pos;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;
	अचिन्हित पूर्णांक offset = pos & ~PAGE_MASK;
	अचिन्हित दीर्घ n = pos >> PAGE_SHIFT;
	अचिन्हित दीर्घ npages = dir_pages(inode);

	अगर (pos > inode->i_size - NILFS_सूची_REC_LEN(1))
		वापस 0;

	क्रम ( ; n < npages; n++, offset = 0) अणु
		अक्षर *kaddr, *limit;
		काष्ठा nilfs_dir_entry *de;
		काष्ठा page *page = nilfs_get_page(inode, n);

		अगर (IS_ERR(page)) अणु
			nilfs_error(sb, "bad page in #%lu", inode->i_ino);
			ctx->pos += PAGE_SIZE - offset;
			वापस -EIO;
		पूर्ण
		kaddr = page_address(page);
		de = (काष्ठा nilfs_dir_entry *)(kaddr + offset);
		limit = kaddr + nilfs_last_byte(inode, n) -
			NILFS_सूची_REC_LEN(1);
		क्रम ( ; (अक्षर *)de <= limit; de = nilfs_next_entry(de)) अणु
			अगर (de->rec_len == 0) अणु
				nilfs_error(sb, "zero-length directory entry");
				nilfs_put_page(page);
				वापस -EIO;
			पूर्ण
			अगर (de->inode) अणु
				अचिन्हित अक्षर t;

				अगर (de->file_type < NILFS_FT_MAX)
					t = nilfs_filetype_table[de->file_type];
				अन्यथा
					t = DT_UNKNOWN;

				अगर (!dir_emit(ctx, de->name, de->name_len,
						le64_to_cpu(de->inode), t)) अणु
					nilfs_put_page(page);
					वापस 0;
				पूर्ण
			पूर्ण
			ctx->pos += nilfs_rec_len_from_disk(de->rec_len);
		पूर्ण
		nilfs_put_page(page);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	nilfs_find_entry()
 *
 * finds an entry in the specअगरied directory with the wanted name. It
 * वापसs the page in which the entry was found, and the entry itself
 * (as a parameter - res_dir). Page is वापसed mapped and unlocked.
 * Entry is guaranteed to be valid.
 */
काष्ठा nilfs_dir_entry *
nilfs_find_entry(काष्ठा inode *dir, स्थिर काष्ठा qstr *qstr,
		 काष्ठा page **res_page)
अणु
	स्थिर अचिन्हित अक्षर *name = qstr->name;
	पूर्णांक namelen = qstr->len;
	अचिन्हित पूर्णांक reclen = NILFS_सूची_REC_LEN(namelen);
	अचिन्हित दीर्घ start, n;
	अचिन्हित दीर्घ npages = dir_pages(dir);
	काष्ठा page *page = शून्य;
	काष्ठा nilfs_inode_info *ei = NILFS_I(dir);
	काष्ठा nilfs_dir_entry *de;

	अगर (npages == 0)
		जाओ out;

	/* OFFSET_CACHE */
	*res_page = शून्य;

	start = ei->i_dir_start_lookup;
	अगर (start >= npages)
		start = 0;
	n = start;
	करो अणु
		अक्षर *kaddr;

		page = nilfs_get_page(dir, n);
		अगर (!IS_ERR(page)) अणु
			kaddr = page_address(page);
			de = (काष्ठा nilfs_dir_entry *)kaddr;
			kaddr += nilfs_last_byte(dir, n) - reclen;
			जबतक ((अक्षर *) de <= kaddr) अणु
				अगर (de->rec_len == 0) अणु
					nilfs_error(dir->i_sb,
						"zero-length directory entry");
					nilfs_put_page(page);
					जाओ out;
				पूर्ण
				अगर (nilfs_match(namelen, name, de))
					जाओ found;
				de = nilfs_next_entry(de);
			पूर्ण
			nilfs_put_page(page);
		पूर्ण
		अगर (++n >= npages)
			n = 0;
		/* next page is past the blocks we've got */
		अगर (unlikely(n > (dir->i_blocks >> (PAGE_SHIFT - 9)))) अणु
			nilfs_error(dir->i_sb,
			       "dir %lu size %lld exceeds block count %llu",
			       dir->i_ino, dir->i_size,
			       (अचिन्हित दीर्घ दीर्घ)dir->i_blocks);
			जाओ out;
		पूर्ण
	पूर्ण जबतक (n != start);
out:
	वापस शून्य;

found:
	*res_page = page;
	ei->i_dir_start_lookup = n;
	वापस de;
पूर्ण

काष्ठा nilfs_dir_entry *nilfs_करोtकरोt(काष्ठा inode *dir, काष्ठा page **p)
अणु
	काष्ठा page *page = nilfs_get_page(dir, 0);
	काष्ठा nilfs_dir_entry *de = शून्य;

	अगर (!IS_ERR(page)) अणु
		de = nilfs_next_entry(
			(काष्ठा nilfs_dir_entry *)page_address(page));
		*p = page;
	पूर्ण
	वापस de;
पूर्ण

ino_t nilfs_inode_by_name(काष्ठा inode *dir, स्थिर काष्ठा qstr *qstr)
अणु
	ino_t res = 0;
	काष्ठा nilfs_dir_entry *de;
	काष्ठा page *page;

	de = nilfs_find_entry(dir, qstr, &page);
	अगर (de) अणु
		res = le64_to_cpu(de->inode);
		kunmap(page);
		put_page(page);
	पूर्ण
	वापस res;
पूर्ण

/* Releases the page */
व्योम nilfs_set_link(काष्ठा inode *dir, काष्ठा nilfs_dir_entry *de,
		    काष्ठा page *page, काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक from = (अक्षर *)de - (अक्षर *)page_address(page);
	अचिन्हित पूर्णांक to = from + nilfs_rec_len_from_disk(de->rec_len);
	काष्ठा address_space *mapping = page->mapping;
	पूर्णांक err;

	lock_page(page);
	err = nilfs_prepare_chunk(page, from, to);
	BUG_ON(err);
	de->inode = cpu_to_le64(inode->i_ino);
	nilfs_set_de_type(de, inode);
	nilfs_commit_chunk(page, mapping, from, to);
	nilfs_put_page(page);
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
पूर्ण

/*
 *	Parent is locked.
 */
पूर्णांक nilfs_add_link(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	स्थिर अचिन्हित अक्षर *name = dentry->d_name.name;
	पूर्णांक namelen = dentry->d_name.len;
	अचिन्हित पूर्णांक chunk_size = nilfs_chunk_size(dir);
	अचिन्हित पूर्णांक reclen = NILFS_सूची_REC_LEN(namelen);
	अचिन्हित लघु rec_len, name_len;
	काष्ठा page *page = शून्य;
	काष्ठा nilfs_dir_entry *de;
	अचिन्हित दीर्घ npages = dir_pages(dir);
	अचिन्हित दीर्घ n;
	अक्षर *kaddr;
	अचिन्हित पूर्णांक from, to;
	पूर्णांक err;

	/*
	 * We take care of directory expansion in the same loop.
	 * This code plays outside i_size, so it locks the page
	 * to protect that region.
	 */
	क्रम (n = 0; n <= npages; n++) अणु
		अक्षर *dir_end;

		page = nilfs_get_page(dir, n);
		err = PTR_ERR(page);
		अगर (IS_ERR(page))
			जाओ out;
		lock_page(page);
		kaddr = page_address(page);
		dir_end = kaddr + nilfs_last_byte(dir, n);
		de = (काष्ठा nilfs_dir_entry *)kaddr;
		kaddr += PAGE_SIZE - reclen;
		जबतक ((अक्षर *)de <= kaddr) अणु
			अगर ((अक्षर *)de == dir_end) अणु
				/* We hit i_size */
				name_len = 0;
				rec_len = chunk_size;
				de->rec_len = nilfs_rec_len_to_disk(chunk_size);
				de->inode = 0;
				जाओ got_it;
			पूर्ण
			अगर (de->rec_len == 0) अणु
				nilfs_error(dir->i_sb,
					    "zero-length directory entry");
				err = -EIO;
				जाओ out_unlock;
			पूर्ण
			err = -EEXIST;
			अगर (nilfs_match(namelen, name, de))
				जाओ out_unlock;
			name_len = NILFS_सूची_REC_LEN(de->name_len);
			rec_len = nilfs_rec_len_from_disk(de->rec_len);
			अगर (!de->inode && rec_len >= reclen)
				जाओ got_it;
			अगर (rec_len >= name_len + reclen)
				जाओ got_it;
			de = (काष्ठा nilfs_dir_entry *)((अक्षर *)de + rec_len);
		पूर्ण
		unlock_page(page);
		nilfs_put_page(page);
	पूर्ण
	BUG();
	वापस -EINVAL;

got_it:
	from = (अक्षर *)de - (अक्षर *)page_address(page);
	to = from + rec_len;
	err = nilfs_prepare_chunk(page, from, to);
	अगर (err)
		जाओ out_unlock;
	अगर (de->inode) अणु
		काष्ठा nilfs_dir_entry *de1;

		de1 = (काष्ठा nilfs_dir_entry *)((अक्षर *)de + name_len);
		de1->rec_len = nilfs_rec_len_to_disk(rec_len - name_len);
		de->rec_len = nilfs_rec_len_to_disk(name_len);
		de = de1;
	पूर्ण
	de->name_len = namelen;
	स_नकल(de->name, name, namelen);
	de->inode = cpu_to_le64(inode->i_ino);
	nilfs_set_de_type(de, inode);
	nilfs_commit_chunk(page, page->mapping, from, to);
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	nilfs_mark_inode_dirty(dir);
	/* OFFSET_CACHE */
out_put:
	nilfs_put_page(page);
out:
	वापस err;
out_unlock:
	unlock_page(page);
	जाओ out_put;
पूर्ण

/*
 * nilfs_delete_entry deletes a directory entry by merging it with the
 * previous entry. Page is up-to-date. Releases the page.
 */
पूर्णांक nilfs_delete_entry(काष्ठा nilfs_dir_entry *dir, काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा inode *inode = mapping->host;
	अक्षर *kaddr = page_address(page);
	अचिन्हित पूर्णांक from, to;
	काष्ठा nilfs_dir_entry *de, *pde = शून्य;
	पूर्णांक err;

	from = ((अक्षर *)dir - kaddr) & ~(nilfs_chunk_size(inode) - 1);
	to = ((अक्षर *)dir - kaddr) + nilfs_rec_len_from_disk(dir->rec_len);
	de = (काष्ठा nilfs_dir_entry *)(kaddr + from);

	जबतक ((अक्षर *)de < (अक्षर *)dir) अणु
		अगर (de->rec_len == 0) अणु
			nilfs_error(inode->i_sb,
				    "zero-length directory entry");
			err = -EIO;
			जाओ out;
		पूर्ण
		pde = de;
		de = nilfs_next_entry(de);
	पूर्ण
	अगर (pde)
		from = (अक्षर *)pde - (अक्षर *)page_address(page);
	lock_page(page);
	err = nilfs_prepare_chunk(page, from, to);
	BUG_ON(err);
	अगर (pde)
		pde->rec_len = nilfs_rec_len_to_disk(to - from);
	dir->inode = 0;
	nilfs_commit_chunk(page, mapping, from, to);
	inode->i_स_समय = inode->i_mसमय = current_समय(inode);
out:
	nilfs_put_page(page);
	वापस err;
पूर्ण

/*
 * Set the first fragment of directory.
 */
पूर्णांक nilfs_make_empty(काष्ठा inode *inode, काष्ठा inode *parent)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page = grab_cache_page(mapping, 0);
	अचिन्हित पूर्णांक chunk_size = nilfs_chunk_size(inode);
	काष्ठा nilfs_dir_entry *de;
	पूर्णांक err;
	व्योम *kaddr;

	अगर (!page)
		वापस -ENOMEM;

	err = nilfs_prepare_chunk(page, 0, chunk_size);
	अगर (unlikely(err)) अणु
		unlock_page(page);
		जाओ fail;
	पूर्ण
	kaddr = kmap_atomic(page);
	स_रखो(kaddr, 0, chunk_size);
	de = (काष्ठा nilfs_dir_entry *)kaddr;
	de->name_len = 1;
	de->rec_len = nilfs_rec_len_to_disk(NILFS_सूची_REC_LEN(1));
	स_नकल(de->name, ".\0\0", 4);
	de->inode = cpu_to_le64(inode->i_ino);
	nilfs_set_de_type(de, inode);

	de = (काष्ठा nilfs_dir_entry *)(kaddr + NILFS_सूची_REC_LEN(1));
	de->name_len = 2;
	de->rec_len = nilfs_rec_len_to_disk(chunk_size - NILFS_सूची_REC_LEN(1));
	de->inode = cpu_to_le64(parent->i_ino);
	स_नकल(de->name, "..\0", 4);
	nilfs_set_de_type(de, inode);
	kunmap_atomic(kaddr);
	nilfs_commit_chunk(page, mapping, 0, chunk_size);
fail:
	put_page(page);
	वापस err;
पूर्ण

/*
 * routine to check that the specअगरied directory is empty (क्रम सूची_हटाओ)
 */
पूर्णांक nilfs_empty_dir(काष्ठा inode *inode)
अणु
	काष्ठा page *page = शून्य;
	अचिन्हित दीर्घ i, npages = dir_pages(inode);

	क्रम (i = 0; i < npages; i++) अणु
		अक्षर *kaddr;
		काष्ठा nilfs_dir_entry *de;

		page = nilfs_get_page(inode, i);
		अगर (IS_ERR(page))
			जारी;

		kaddr = page_address(page);
		de = (काष्ठा nilfs_dir_entry *)kaddr;
		kaddr += nilfs_last_byte(inode, i) - NILFS_सूची_REC_LEN(1);

		जबतक ((अक्षर *)de <= kaddr) अणु
			अगर (de->rec_len == 0) अणु
				nilfs_error(inode->i_sb,
					    "zero-length directory entry (kaddr=%p, de=%p)",
					    kaddr, de);
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
					    cpu_to_le64(inode->i_ino))
						जाओ not_empty;
				पूर्ण अन्यथा अगर (de->name[1] != '.')
					जाओ not_empty;
			पूर्ण
			de = nilfs_next_entry(de);
		पूर्ण
		nilfs_put_page(page);
	पूर्ण
	वापस 1;

not_empty:
	nilfs_put_page(page);
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations nilfs_dir_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= nilfs_सूची_पढ़ो,
	.unlocked_ioctl	= nilfs_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= nilfs_compat_ioctl,
#पूर्ण_अगर	/* CONFIG_COMPAT */
	.fsync		= nilfs_sync_file,

पूर्ण;
