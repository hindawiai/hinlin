<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ufs/ufs_dir.c
 *
 * Copyright (C) 1996
 * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)
 * Laboratory क्रम Computer Science Research Computing Facility
 * Rutgers, The State University of New Jersey
 *
 * swab support by Francois-Rene Rideau <fare@tunes.org> 19970406
 *
 * 4.4BSD (FreeBSD) support added on February 1st 1998 by
 * Niels Kristian Bech Jensen <nkbj@image.dk> partially based
 * on code by Martin von Loewis <martin@mira.isdn.cs.tu-berlin.de>.
 *
 * Migration to usage of "page cache" on May 2006 by
 * Evgeniy Dushistov <dushistov@mail.ru> based on ext2 code base.
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/swap.h>
#समावेश <linux/iversion.h>

#समावेश "ufs_fs.h"
#समावेश "ufs.h"
#समावेश "swab.h"
#समावेश "util.h"

/*
 * NOTE! unlike म_भेदन, ufs_match वापसs 1 क्रम success, 0 क्रम failure.
 *
 * len <= UFS_MAXNAMLEN and de != शून्य are guaranteed by caller.
 */
अटल अंतरभूत पूर्णांक ufs_match(काष्ठा super_block *sb, पूर्णांक len,
		स्थिर अचिन्हित अक्षर *name, काष्ठा ufs_dir_entry *de)
अणु
	अगर (len != ufs_get_de_namlen(sb, de))
		वापस 0;
	अगर (!de->d_ino)
		वापस 0;
	वापस !स_भेद(name, de->d_name, len);
पूर्ण

अटल पूर्णांक ufs_commit_chunk(काष्ठा page *page, loff_t pos, अचिन्हित len)
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
	अगर (IS_सूचीSYNC(dir))
		err = ग_लिखो_one_page(page);
	अन्यथा
		unlock_page(page);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम ufs_put_page(काष्ठा page *page)
अणु
	kunmap(page);
	put_page(page);
पूर्ण

ino_t ufs_inode_by_name(काष्ठा inode *dir, स्थिर काष्ठा qstr *qstr)
अणु
	ino_t res = 0;
	काष्ठा ufs_dir_entry *de;
	काष्ठा page *page;
	
	de = ufs_find_entry(dir, qstr, &page);
	अगर (de) अणु
		res = fs32_to_cpu(dir->i_sb, de->d_ino);
		ufs_put_page(page);
	पूर्ण
	वापस res;
पूर्ण


/* Releases the page */
व्योम ufs_set_link(काष्ठा inode *dir, काष्ठा ufs_dir_entry *de,
		  काष्ठा page *page, काष्ठा inode *inode,
		  bool update_बार)
अणु
	loff_t pos = page_offset(page) +
			(अक्षर *) de - (अक्षर *) page_address(page);
	अचिन्हित len = fs16_to_cpu(dir->i_sb, de->d_reclen);
	पूर्णांक err;

	lock_page(page);
	err = ufs_prepare_chunk(page, pos, len);
	BUG_ON(err);

	de->d_ino = cpu_to_fs32(dir->i_sb, inode->i_ino);
	ufs_set_de_type(dir->i_sb, de, inode->i_mode);

	err = ufs_commit_chunk(page, pos, len);
	ufs_put_page(page);
	अगर (update_बार)
		dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	mark_inode_dirty(dir);
पूर्ण


अटल bool ufs_check_page(काष्ठा page *page)
अणु
	काष्ठा inode *dir = page->mapping->host;
	काष्ठा super_block *sb = dir->i_sb;
	अक्षर *kaddr = page_address(page);
	अचिन्हित offs, rec_len;
	अचिन्हित limit = PAGE_SIZE;
	स्थिर अचिन्हित chunk_mask = UFS_SB(sb)->s_uspi->s_dirblksize - 1;
	काष्ठा ufs_dir_entry *p;
	अक्षर *error;

	अगर ((dir->i_size >> PAGE_SHIFT) == page->index) अणु
		limit = dir->i_size & ~PAGE_MASK;
		अगर (limit & chunk_mask)
			जाओ Ebadsize;
		अगर (!limit)
			जाओ out;
	पूर्ण
	क्रम (offs = 0; offs <= limit - UFS_सूची_REC_LEN(1); offs += rec_len) अणु
		p = (काष्ठा ufs_dir_entry *)(kaddr + offs);
		rec_len = fs16_to_cpu(sb, p->d_reclen);

		अगर (rec_len < UFS_सूची_REC_LEN(1))
			जाओ Eलघु;
		अगर (rec_len & 3)
			जाओ Ealign;
		अगर (rec_len < UFS_सूची_REC_LEN(ufs_get_de_namlen(sb, p)))
			जाओ Enamelen;
		अगर (((offs + rec_len - 1) ^ offs) & ~chunk_mask)
			जाओ Espan;
		अगर (fs32_to_cpu(sb, p->d_ino) > (UFS_SB(sb)->s_uspi->s_ipg *
						  UFS_SB(sb)->s_uspi->s_ncg))
			जाओ Einumber;
	पूर्ण
	अगर (offs != limit)
		जाओ Eend;
out:
	SetPageChecked(page);
	वापस true;

	/* Too bad, we had an error */

Ebadsize:
	ufs_error(sb, "ufs_check_page",
		  "size of directory #%lu is not a multiple of chunk size",
		  dir->i_ino
	);
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
	ufs_error (sb, "ufs_check_page", "bad entry in directory #%lu: %s - "
		   "offset=%lu, rec_len=%d, name_len=%d",
		   dir->i_ino, error, (page->index<<PAGE_SHIFT)+offs,
		   rec_len, ufs_get_de_namlen(sb, p));
	जाओ fail;
Eend:
	p = (काष्ठा ufs_dir_entry *)(kaddr + offs);
	ufs_error(sb, __func__,
		   "entry in directory #%lu spans the page boundary"
		   "offset=%lu",
		   dir->i_ino, (page->index<<PAGE_SHIFT)+offs);
fail:
	SetPageError(page);
	वापस false;
पूर्ण

अटल काष्ठा page *ufs_get_page(काष्ठा inode *dir, अचिन्हित दीर्घ n)
अणु
	काष्ठा address_space *mapping = dir->i_mapping;
	काष्ठा page *page = पढ़ो_mapping_page(mapping, n, शून्य);
	अगर (!IS_ERR(page)) अणु
		kmap(page);
		अगर (unlikely(!PageChecked(page))) अणु
			अगर (PageError(page) || !ufs_check_page(page))
				जाओ fail;
		पूर्ण
	पूर्ण
	वापस page;

fail:
	ufs_put_page(page);
	वापस ERR_PTR(-EIO);
पूर्ण

/*
 * Return the offset पूर्णांकo page `page_nr' of the last valid
 * byte in that page, plus one.
 */
अटल अचिन्हित
ufs_last_byte(काष्ठा inode *inode, अचिन्हित दीर्घ page_nr)
अणु
	अचिन्हित last_byte = inode->i_size;

	last_byte -= page_nr << PAGE_SHIFT;
	अगर (last_byte > PAGE_SIZE)
		last_byte = PAGE_SIZE;
	वापस last_byte;
पूर्ण

अटल अंतरभूत काष्ठा ufs_dir_entry *
ufs_next_entry(काष्ठा super_block *sb, काष्ठा ufs_dir_entry *p)
अणु
	वापस (काष्ठा ufs_dir_entry *)((अक्षर *)p +
					fs16_to_cpu(sb, p->d_reclen));
पूर्ण

काष्ठा ufs_dir_entry *ufs_करोtकरोt(काष्ठा inode *dir, काष्ठा page **p)
अणु
	काष्ठा page *page = ufs_get_page(dir, 0);
	काष्ठा ufs_dir_entry *de = शून्य;

	अगर (!IS_ERR(page)) अणु
		de = ufs_next_entry(dir->i_sb,
				    (काष्ठा ufs_dir_entry *)page_address(page));
		*p = page;
	पूर्ण
	वापस de;
पूर्ण

/*
 *	ufs_find_entry()
 *
 * finds an entry in the specअगरied directory with the wanted name. It
 * वापसs the page in which the entry was found, and the entry itself
 * (as a parameter - res_dir). Page is वापसed mapped and unlocked.
 * Entry is guaranteed to be valid.
 */
काष्ठा ufs_dir_entry *ufs_find_entry(काष्ठा inode *dir, स्थिर काष्ठा qstr *qstr,
				     काष्ठा page **res_page)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	स्थिर अचिन्हित अक्षर *name = qstr->name;
	पूर्णांक namelen = qstr->len;
	अचिन्हित reclen = UFS_सूची_REC_LEN(namelen);
	अचिन्हित दीर्घ start, n;
	अचिन्हित दीर्घ npages = dir_pages(dir);
	काष्ठा page *page = शून्य;
	काष्ठा ufs_inode_info *ui = UFS_I(dir);
	काष्ठा ufs_dir_entry *de;

	UFSD("ENTER, dir_ino %lu, name %s, namlen %u\n", dir->i_ino, name, namelen);

	अगर (npages == 0 || namelen > UFS_MAXNAMLEN)
		जाओ out;

	/* OFFSET_CACHE */
	*res_page = शून्य;

	start = ui->i_dir_start_lookup;

	अगर (start >= npages)
		start = 0;
	n = start;
	करो अणु
		अक्षर *kaddr;
		page = ufs_get_page(dir, n);
		अगर (!IS_ERR(page)) अणु
			kaddr = page_address(page);
			de = (काष्ठा ufs_dir_entry *) kaddr;
			kaddr += ufs_last_byte(dir, n) - reclen;
			जबतक ((अक्षर *) de <= kaddr) अणु
				अगर (ufs_match(sb, namelen, name, de))
					जाओ found;
				de = ufs_next_entry(sb, de);
			पूर्ण
			ufs_put_page(page);
		पूर्ण
		अगर (++n >= npages)
			n = 0;
	पूर्ण जबतक (n != start);
out:
	वापस शून्य;

found:
	*res_page = page;
	ui->i_dir_start_lookup = n;
	वापस de;
पूर्ण

/*
 *	Parent is locked.
 */
पूर्णांक ufs_add_link(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	स्थिर अचिन्हित अक्षर *name = dentry->d_name.name;
	पूर्णांक namelen = dentry->d_name.len;
	काष्ठा super_block *sb = dir->i_sb;
	अचिन्हित reclen = UFS_सूची_REC_LEN(namelen);
	स्थिर अचिन्हित पूर्णांक chunk_size = UFS_SB(sb)->s_uspi->s_dirblksize;
	अचिन्हित लघु rec_len, name_len;
	काष्ठा page *page = शून्य;
	काष्ठा ufs_dir_entry *de;
	अचिन्हित दीर्घ npages = dir_pages(dir);
	अचिन्हित दीर्घ n;
	अक्षर *kaddr;
	loff_t pos;
	पूर्णांक err;

	UFSD("ENTER, name %s, namelen %u\n", name, namelen);

	/*
	 * We take care of directory expansion in the same loop.
	 * This code plays outside i_size, so it locks the page
	 * to protect that region.
	 */
	क्रम (n = 0; n <= npages; n++) अणु
		अक्षर *dir_end;

		page = ufs_get_page(dir, n);
		err = PTR_ERR(page);
		अगर (IS_ERR(page))
			जाओ out;
		lock_page(page);
		kaddr = page_address(page);
		dir_end = kaddr + ufs_last_byte(dir, n);
		de = (काष्ठा ufs_dir_entry *)kaddr;
		kaddr += PAGE_SIZE - reclen;
		जबतक ((अक्षर *)de <= kaddr) अणु
			अगर ((अक्षर *)de == dir_end) अणु
				/* We hit i_size */
				name_len = 0;
				rec_len = chunk_size;
				de->d_reclen = cpu_to_fs16(sb, chunk_size);
				de->d_ino = 0;
				जाओ got_it;
			पूर्ण
			अगर (de->d_reclen == 0) अणु
				ufs_error(dir->i_sb, __func__,
					  "zero-length directory entry");
				err = -EIO;
				जाओ out_unlock;
			पूर्ण
			err = -EEXIST;
			अगर (ufs_match(sb, namelen, name, de))
				जाओ out_unlock;
			name_len = UFS_सूची_REC_LEN(ufs_get_de_namlen(sb, de));
			rec_len = fs16_to_cpu(sb, de->d_reclen);
			अगर (!de->d_ino && rec_len >= reclen)
				जाओ got_it;
			अगर (rec_len >= name_len + reclen)
				जाओ got_it;
			de = (काष्ठा ufs_dir_entry *) ((अक्षर *) de + rec_len);
		पूर्ण
		unlock_page(page);
		ufs_put_page(page);
	पूर्ण
	BUG();
	वापस -EINVAL;

got_it:
	pos = page_offset(page) +
			(अक्षर*)de - (अक्षर*)page_address(page);
	err = ufs_prepare_chunk(page, pos, rec_len);
	अगर (err)
		जाओ out_unlock;
	अगर (de->d_ino) अणु
		काष्ठा ufs_dir_entry *de1 =
			(काष्ठा ufs_dir_entry *) ((अक्षर *) de + name_len);
		de1->d_reclen = cpu_to_fs16(sb, rec_len - name_len);
		de->d_reclen = cpu_to_fs16(sb, name_len);

		de = de1;
	पूर्ण

	ufs_set_de_namlen(sb, de, namelen);
	स_नकल(de->d_name, name, namelen + 1);
	de->d_ino = cpu_to_fs32(sb, inode->i_ino);
	ufs_set_de_type(sb, de, inode->i_mode);

	err = ufs_commit_chunk(page, pos, rec_len);
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);

	mark_inode_dirty(dir);
	/* OFFSET_CACHE */
out_put:
	ufs_put_page(page);
out:
	वापस err;
out_unlock:
	unlock_page(page);
	जाओ out_put;
पूर्ण

अटल अंतरभूत अचिन्हित
ufs_validate_entry(काष्ठा super_block *sb, अक्षर *base,
		   अचिन्हित offset, अचिन्हित mask)
अणु
	काष्ठा ufs_dir_entry *de = (काष्ठा ufs_dir_entry*)(base + offset);
	काष्ठा ufs_dir_entry *p = (काष्ठा ufs_dir_entry*)(base + (offset&mask));
	जबतक ((अक्षर*)p < (अक्षर*)de)
		p = ufs_next_entry(sb, p);
	वापस (अक्षर *)p - base;
पूर्ण


/*
 * This is blatantly stolen from ext2fs
 */
अटल पूर्णांक
ufs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	loff_t pos = ctx->pos;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;
	अचिन्हित पूर्णांक offset = pos & ~PAGE_MASK;
	अचिन्हित दीर्घ n = pos >> PAGE_SHIFT;
	अचिन्हित दीर्घ npages = dir_pages(inode);
	अचिन्हित chunk_mask = ~(UFS_SB(sb)->s_uspi->s_dirblksize - 1);
	bool need_revalidate = !inode_eq_iversion(inode, file->f_version);
	अचिन्हित flags = UFS_SB(sb)->s_flags;

	UFSD("BEGIN\n");

	अगर (pos > inode->i_size - UFS_सूची_REC_LEN(1))
		वापस 0;

	क्रम ( ; n < npages; n++, offset = 0) अणु
		अक्षर *kaddr, *limit;
		काष्ठा ufs_dir_entry *de;

		काष्ठा page *page = ufs_get_page(inode, n);

		अगर (IS_ERR(page)) अणु
			ufs_error(sb, __func__,
				  "bad page in #%lu",
				  inode->i_ino);
			ctx->pos += PAGE_SIZE - offset;
			वापस -EIO;
		पूर्ण
		kaddr = page_address(page);
		अगर (unlikely(need_revalidate)) अणु
			अगर (offset) अणु
				offset = ufs_validate_entry(sb, kaddr, offset, chunk_mask);
				ctx->pos = (n<<PAGE_SHIFT) + offset;
			पूर्ण
			file->f_version = inode_query_iversion(inode);
			need_revalidate = false;
		पूर्ण
		de = (काष्ठा ufs_dir_entry *)(kaddr+offset);
		limit = kaddr + ufs_last_byte(inode, n) - UFS_सूची_REC_LEN(1);
		क्रम ( ;(अक्षर*)de <= limit; de = ufs_next_entry(sb, de)) अणु
			अगर (de->d_ino) अणु
				अचिन्हित अक्षर d_type = DT_UNKNOWN;

				UFSD("filldir(%s,%u)\n", de->d_name,
				      fs32_to_cpu(sb, de->d_ino));
				UFSD("namlen %u\n", ufs_get_de_namlen(sb, de));

				अगर ((flags & UFS_DE_MASK) == UFS_DE_44BSD)
					d_type = de->d_u.d_44.d_type;

				अगर (!dir_emit(ctx, de->d_name,
					       ufs_get_de_namlen(sb, de),
					       fs32_to_cpu(sb, de->d_ino),
					       d_type)) अणु
					ufs_put_page(page);
					वापस 0;
				पूर्ण
			पूर्ण
			ctx->pos += fs16_to_cpu(sb, de->d_reclen);
		पूर्ण
		ufs_put_page(page);
	पूर्ण
	वापस 0;
पूर्ण


/*
 * ufs_delete_entry deletes a directory entry by merging it with the
 * previous entry.
 */
पूर्णांक ufs_delete_entry(काष्ठा inode *inode, काष्ठा ufs_dir_entry *dir,
		     काष्ठा page * page)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	अक्षर *kaddr = page_address(page);
	अचिन्हित from = ((अक्षर*)dir - kaddr) & ~(UFS_SB(sb)->s_uspi->s_dirblksize - 1);
	अचिन्हित to = ((अक्षर*)dir - kaddr) + fs16_to_cpu(sb, dir->d_reclen);
	loff_t pos;
	काष्ठा ufs_dir_entry *pde = शून्य;
	काष्ठा ufs_dir_entry *de = (काष्ठा ufs_dir_entry *) (kaddr + from);
	पूर्णांक err;

	UFSD("ENTER\n");

	UFSD("ino %u, reclen %u, namlen %u, name %s\n",
	      fs32_to_cpu(sb, de->d_ino),
	      fs16_to_cpu(sb, de->d_reclen),
	      ufs_get_de_namlen(sb, de), de->d_name);

	जबतक ((अक्षर*)de < (अक्षर*)dir) अणु
		अगर (de->d_reclen == 0) अणु
			ufs_error(inode->i_sb, __func__,
				  "zero-length directory entry");
			err = -EIO;
			जाओ out;
		पूर्ण
		pde = de;
		de = ufs_next_entry(sb, de);
	पूर्ण
	अगर (pde)
		from = (अक्षर*)pde - (अक्षर*)page_address(page);

	pos = page_offset(page) + from;
	lock_page(page);
	err = ufs_prepare_chunk(page, pos, to - from);
	BUG_ON(err);
	अगर (pde)
		pde->d_reclen = cpu_to_fs16(sb, to - from);
	dir->d_ino = 0;
	err = ufs_commit_chunk(page, pos, to - from);
	inode->i_स_समय = inode->i_mसमय = current_समय(inode);
	mark_inode_dirty(inode);
out:
	ufs_put_page(page);
	UFSD("EXIT\n");
	वापस err;
पूर्ण

पूर्णांक ufs_make_empty(काष्ठा inode * inode, काष्ठा inode *dir)
अणु
	काष्ठा super_block * sb = dir->i_sb;
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page = grab_cache_page(mapping, 0);
	स्थिर अचिन्हित पूर्णांक chunk_size = UFS_SB(sb)->s_uspi->s_dirblksize;
	काष्ठा ufs_dir_entry * de;
	अक्षर *base;
	पूर्णांक err;

	अगर (!page)
		वापस -ENOMEM;

	err = ufs_prepare_chunk(page, 0, chunk_size);
	अगर (err) अणु
		unlock_page(page);
		जाओ fail;
	पूर्ण

	kmap(page);
	base = (अक्षर*)page_address(page);
	स_रखो(base, 0, PAGE_SIZE);

	de = (काष्ठा ufs_dir_entry *) base;

	de->d_ino = cpu_to_fs32(sb, inode->i_ino);
	ufs_set_de_type(sb, de, inode->i_mode);
	ufs_set_de_namlen(sb, de, 1);
	de->d_reclen = cpu_to_fs16(sb, UFS_सूची_REC_LEN(1));
	म_नकल (de->d_name, ".");
	de = (काष्ठा ufs_dir_entry *)
		((अक्षर *)de + fs16_to_cpu(sb, de->d_reclen));
	de->d_ino = cpu_to_fs32(sb, dir->i_ino);
	ufs_set_de_type(sb, de, dir->i_mode);
	de->d_reclen = cpu_to_fs16(sb, chunk_size - UFS_सूची_REC_LEN(1));
	ufs_set_de_namlen(sb, de, 2);
	म_नकल (de->d_name, "..");
	kunmap(page);

	err = ufs_commit_chunk(page, 0, chunk_size);
fail:
	put_page(page);
	वापस err;
पूर्ण

/*
 * routine to check that the specअगरied directory is empty (क्रम सूची_हटाओ)
 */
पूर्णांक ufs_empty_dir(काष्ठा inode * inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा page *page = शून्य;
	अचिन्हित दीर्घ i, npages = dir_pages(inode);

	क्रम (i = 0; i < npages; i++) अणु
		अक्षर *kaddr;
		काष्ठा ufs_dir_entry *de;
		page = ufs_get_page(inode, i);

		अगर (IS_ERR(page))
			जारी;

		kaddr = page_address(page);
		de = (काष्ठा ufs_dir_entry *)kaddr;
		kaddr += ufs_last_byte(inode, i) - UFS_सूची_REC_LEN(1);

		जबतक ((अक्षर *)de <= kaddr) अणु
			अगर (de->d_reclen == 0) अणु
				ufs_error(inode->i_sb, __func__,
					"zero-length directory entry: "
					"kaddr=%p, de=%p\n", kaddr, de);
				जाओ not_empty;
			पूर्ण
			अगर (de->d_ino) अणु
				u16 namelen=ufs_get_de_namlen(sb, de);
				/* check क्रम . and .. */
				अगर (de->d_name[0] != '.')
					जाओ not_empty;
				अगर (namelen > 2)
					जाओ not_empty;
				अगर (namelen < 2) अणु
					अगर (inode->i_ino !=
					    fs32_to_cpu(sb, de->d_ino))
						जाओ not_empty;
				पूर्ण अन्यथा अगर (de->d_name[1] != '.')
					जाओ not_empty;
			पूर्ण
			de = ufs_next_entry(sb, de);
		पूर्ण
		ufs_put_page(page);
	पूर्ण
	वापस 1;

not_empty:
	ufs_put_page(page);
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations ufs_dir_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= ufs_सूची_पढ़ो,
	.fsync		= generic_file_fsync,
	.llseek		= generic_file_llseek,
पूर्ण;
