<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/minix/dir.c
 *
 *  Copyright (C) 1991, 1992 Linus Torvalds
 *
 *  minix directory handling functions
 *
 *  Updated to fileप्रणाली version 3 by Daniel Aragones
 */

#समावेश "minix.h"
#समावेश <linux/buffer_head.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/swap.h>

प्रकार काष्ठा minix_dir_entry minix_dirent;
प्रकार काष्ठा minix3_dir_entry minix3_dirent;

अटल पूर्णांक minix_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);

स्थिर काष्ठा file_operations minix_dir_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= minix_सूची_पढ़ो,
	.fsync		= generic_file_fsync,
पूर्ण;

अटल अंतरभूत व्योम dir_put_page(काष्ठा page *page)
अणु
	kunmap(page);
	put_page(page);
पूर्ण

/*
 * Return the offset पूर्णांकo page `page_nr' of the last valid
 * byte in that page, plus one.
 */
अटल अचिन्हित
minix_last_byte(काष्ठा inode *inode, अचिन्हित दीर्घ page_nr)
अणु
	अचिन्हित last_byte = PAGE_SIZE;

	अगर (page_nr == (inode->i_size >> PAGE_SHIFT))
		last_byte = inode->i_size & (PAGE_SIZE - 1);
	वापस last_byte;
पूर्ण

अटल पूर्णांक dir_commit_chunk(काष्ठा page *page, loff_t pos, अचिन्हित len)
अणु
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा inode *dir = mapping->host;
	पूर्णांक err = 0;
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

अटल काष्ठा page * dir_get_page(काष्ठा inode *dir, अचिन्हित दीर्घ n)
अणु
	काष्ठा address_space *mapping = dir->i_mapping;
	काष्ठा page *page = पढ़ो_mapping_page(mapping, n, शून्य);
	अगर (!IS_ERR(page))
		kmap(page);
	वापस page;
पूर्ण

अटल अंतरभूत व्योम *minix_next_entry(व्योम *de, काष्ठा minix_sb_info *sbi)
अणु
	वापस (व्योम*)((अक्षर*)de + sbi->s_dirsize);
पूर्ण

अटल पूर्णांक minix_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा minix_sb_info *sbi = minix_sb(sb);
	अचिन्हित chunk_size = sbi->s_dirsize;
	अचिन्हित दीर्घ npages = dir_pages(inode);
	अचिन्हित दीर्घ pos = ctx->pos;
	अचिन्हित offset;
	अचिन्हित दीर्घ n;

	ctx->pos = pos = ALIGN(pos, chunk_size);
	अगर (pos >= inode->i_size)
		वापस 0;

	offset = pos & ~PAGE_MASK;
	n = pos >> PAGE_SHIFT;

	क्रम ( ; n < npages; n++, offset = 0) अणु
		अक्षर *p, *kaddr, *limit;
		काष्ठा page *page = dir_get_page(inode, n);

		अगर (IS_ERR(page))
			जारी;
		kaddr = (अक्षर *)page_address(page);
		p = kaddr+offset;
		limit = kaddr + minix_last_byte(inode, n) - chunk_size;
		क्रम ( ; p <= limit; p = minix_next_entry(p, sbi)) अणु
			स्थिर अक्षर *name;
			__u32 inumber;
			अगर (sbi->s_version == MINIX_V3) अणु
				minix3_dirent *de3 = (minix3_dirent *)p;
				name = de3->name;
				inumber = de3->inode;
	 		पूर्ण अन्यथा अणु
				minix_dirent *de = (minix_dirent *)p;
				name = de->name;
				inumber = de->inode;
			पूर्ण
			अगर (inumber) अणु
				अचिन्हित l = strnlen(name, sbi->s_namelen);
				अगर (!dir_emit(ctx, name, l,
					      inumber, DT_UNKNOWN)) अणु
					dir_put_page(page);
					वापस 0;
				पूर्ण
			पूर्ण
			ctx->pos += chunk_size;
		पूर्ण
		dir_put_page(page);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक namecompare(पूर्णांक len, पूर्णांक maxlen,
	स्थिर अक्षर * name, स्थिर अक्षर * buffer)
अणु
	अगर (len < maxlen && buffer[len])
		वापस 0;
	वापस !स_भेद(name, buffer, len);
पूर्ण

/*
 *	minix_find_entry()
 *
 * finds an entry in the specअगरied directory with the wanted name. It
 * वापसs the cache buffer in which the entry was found, and the entry
 * itself (as a parameter - res_dir). It करोes NOT पढ़ो the inode of the
 * entry - you'll have to करो that yourself अगर you want to.
 */
minix_dirent *minix_find_entry(काष्ठा dentry *dentry, काष्ठा page **res_page)
अणु
	स्थिर अक्षर * name = dentry->d_name.name;
	पूर्णांक namelen = dentry->d_name.len;
	काष्ठा inode * dir = d_inode(dentry->d_parent);
	काष्ठा super_block * sb = dir->i_sb;
	काष्ठा minix_sb_info * sbi = minix_sb(sb);
	अचिन्हित दीर्घ n;
	अचिन्हित दीर्घ npages = dir_pages(dir);
	काष्ठा page *page = शून्य;
	अक्षर *p;

	अक्षर *namx;
	__u32 inumber;
	*res_page = शून्य;

	क्रम (n = 0; n < npages; n++) अणु
		अक्षर *kaddr, *limit;

		page = dir_get_page(dir, n);
		अगर (IS_ERR(page))
			जारी;

		kaddr = (अक्षर*)page_address(page);
		limit = kaddr + minix_last_byte(dir, n) - sbi->s_dirsize;
		क्रम (p = kaddr; p <= limit; p = minix_next_entry(p, sbi)) अणु
			अगर (sbi->s_version == MINIX_V3) अणु
				minix3_dirent *de3 = (minix3_dirent *)p;
				namx = de3->name;
				inumber = de3->inode;
 			पूर्ण अन्यथा अणु
				minix_dirent *de = (minix_dirent *)p;
				namx = de->name;
				inumber = de->inode;
			पूर्ण
			अगर (!inumber)
				जारी;
			अगर (namecompare(namelen, sbi->s_namelen, name, namx))
				जाओ found;
		पूर्ण
		dir_put_page(page);
	पूर्ण
	वापस शून्य;

found:
	*res_page = page;
	वापस (minix_dirent *)p;
पूर्ण

पूर्णांक minix_add_link(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	स्थिर अक्षर * name = dentry->d_name.name;
	पूर्णांक namelen = dentry->d_name.len;
	काष्ठा super_block * sb = dir->i_sb;
	काष्ठा minix_sb_info * sbi = minix_sb(sb);
	काष्ठा page *page = शून्य;
	अचिन्हित दीर्घ npages = dir_pages(dir);
	अचिन्हित दीर्घ n;
	अक्षर *kaddr, *p;
	minix_dirent *de;
	minix3_dirent *de3;
	loff_t pos;
	पूर्णांक err;
	अक्षर *namx = शून्य;
	__u32 inumber;

	/*
	 * We take care of directory expansion in the same loop
	 * This code plays outside i_size, so it locks the page
	 * to protect that region.
	 */
	क्रम (n = 0; n <= npages; n++) अणु
		अक्षर *limit, *dir_end;

		page = dir_get_page(dir, n);
		err = PTR_ERR(page);
		अगर (IS_ERR(page))
			जाओ out;
		lock_page(page);
		kaddr = (अक्षर*)page_address(page);
		dir_end = kaddr + minix_last_byte(dir, n);
		limit = kaddr + PAGE_SIZE - sbi->s_dirsize;
		क्रम (p = kaddr; p <= limit; p = minix_next_entry(p, sbi)) अणु
			de = (minix_dirent *)p;
			de3 = (minix3_dirent *)p;
			अगर (sbi->s_version == MINIX_V3) अणु
				namx = de3->name;
				inumber = de3->inode;
		 	पूर्ण अन्यथा अणु
  				namx = de->name;
				inumber = de->inode;
			पूर्ण
			अगर (p == dir_end) अणु
				/* We hit i_size */
				अगर (sbi->s_version == MINIX_V3)
					de3->inode = 0;
		 		अन्यथा
					de->inode = 0;
				जाओ got_it;
			पूर्ण
			अगर (!inumber)
				जाओ got_it;
			err = -EEXIST;
			अगर (namecompare(namelen, sbi->s_namelen, name, namx))
				जाओ out_unlock;
		पूर्ण
		unlock_page(page);
		dir_put_page(page);
	पूर्ण
	BUG();
	वापस -EINVAL;

got_it:
	pos = page_offset(page) + p - (अक्षर *)page_address(page);
	err = minix_prepare_chunk(page, pos, sbi->s_dirsize);
	अगर (err)
		जाओ out_unlock;
	स_नकल (namx, name, namelen);
	अगर (sbi->s_version == MINIX_V3) अणु
		स_रखो (namx + namelen, 0, sbi->s_dirsize - namelen - 4);
		de3->inode = inode->i_ino;
	पूर्ण अन्यथा अणु
		स_रखो (namx + namelen, 0, sbi->s_dirsize - namelen - 2);
		de->inode = inode->i_ino;
	पूर्ण
	err = dir_commit_chunk(page, pos, sbi->s_dirsize);
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	mark_inode_dirty(dir);
out_put:
	dir_put_page(page);
out:
	वापस err;
out_unlock:
	unlock_page(page);
	जाओ out_put;
पूर्ण

पूर्णांक minix_delete_entry(काष्ठा minix_dir_entry *de, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	अक्षर *kaddr = page_address(page);
	loff_t pos = page_offset(page) + (अक्षर*)de - kaddr;
	काष्ठा minix_sb_info *sbi = minix_sb(inode->i_sb);
	अचिन्हित len = sbi->s_dirsize;
	पूर्णांक err;

	lock_page(page);
	err = minix_prepare_chunk(page, pos, len);
	अगर (err == 0) अणु
		अगर (sbi->s_version == MINIX_V3)
			((minix3_dirent *) de)->inode = 0;
		अन्यथा
			de->inode = 0;
		err = dir_commit_chunk(page, pos, len);
	पूर्ण अन्यथा अणु
		unlock_page(page);
	पूर्ण
	dir_put_page(page);
	inode->i_स_समय = inode->i_mसमय = current_समय(inode);
	mark_inode_dirty(inode);
	वापस err;
पूर्ण

पूर्णांक minix_make_empty(काष्ठा inode *inode, काष्ठा inode *dir)
अणु
	काष्ठा page *page = grab_cache_page(inode->i_mapping, 0);
	काष्ठा minix_sb_info *sbi = minix_sb(inode->i_sb);
	अक्षर *kaddr;
	पूर्णांक err;

	अगर (!page)
		वापस -ENOMEM;
	err = minix_prepare_chunk(page, 0, 2 * sbi->s_dirsize);
	अगर (err) अणु
		unlock_page(page);
		जाओ fail;
	पूर्ण

	kaddr = kmap_atomic(page);
	स_रखो(kaddr, 0, PAGE_SIZE);

	अगर (sbi->s_version == MINIX_V3) अणु
		minix3_dirent *de3 = (minix3_dirent *)kaddr;

		de3->inode = inode->i_ino;
		म_नकल(de3->name, ".");
		de3 = minix_next_entry(de3, sbi);
		de3->inode = dir->i_ino;
		म_नकल(de3->name, "..");
	पूर्ण अन्यथा अणु
		minix_dirent *de = (minix_dirent *)kaddr;

		de->inode = inode->i_ino;
		म_नकल(de->name, ".");
		de = minix_next_entry(de, sbi);
		de->inode = dir->i_ino;
		म_नकल(de->name, "..");
	पूर्ण
	kunmap_atomic(kaddr);

	err = dir_commit_chunk(page, 0, 2 * sbi->s_dirsize);
fail:
	put_page(page);
	वापस err;
पूर्ण

/*
 * routine to check that the specअगरied directory is empty (क्रम सूची_हटाओ)
 */
पूर्णांक minix_empty_dir(काष्ठा inode * inode)
अणु
	काष्ठा page *page = शून्य;
	अचिन्हित दीर्घ i, npages = dir_pages(inode);
	काष्ठा minix_sb_info *sbi = minix_sb(inode->i_sb);
	अक्षर *name;
	__u32 inumber;

	क्रम (i = 0; i < npages; i++) अणु
		अक्षर *p, *kaddr, *limit;

		page = dir_get_page(inode, i);
		अगर (IS_ERR(page))
			जारी;

		kaddr = (अक्षर *)page_address(page);
		limit = kaddr + minix_last_byte(inode, i) - sbi->s_dirsize;
		क्रम (p = kaddr; p <= limit; p = minix_next_entry(p, sbi)) अणु
			अगर (sbi->s_version == MINIX_V3) अणु
				minix3_dirent *de3 = (minix3_dirent *)p;
				name = de3->name;
				inumber = de3->inode;
			पूर्ण अन्यथा अणु
				minix_dirent *de = (minix_dirent *)p;
				name = de->name;
				inumber = de->inode;
			पूर्ण

			अगर (inumber != 0) अणु
				/* check क्रम . and .. */
				अगर (name[0] != '.')
					जाओ not_empty;
				अगर (!name[1]) अणु
					अगर (inumber != inode->i_ino)
						जाओ not_empty;
				पूर्ण अन्यथा अगर (name[1] != '.')
					जाओ not_empty;
				अन्यथा अगर (name[2])
					जाओ not_empty;
			पूर्ण
		पूर्ण
		dir_put_page(page);
	पूर्ण
	वापस 1;

not_empty:
	dir_put_page(page);
	वापस 0;
पूर्ण

/* Releases the page */
व्योम minix_set_link(काष्ठा minix_dir_entry *de, काष्ठा page *page,
	काष्ठा inode *inode)
अणु
	काष्ठा inode *dir = page->mapping->host;
	काष्ठा minix_sb_info *sbi = minix_sb(dir->i_sb);
	loff_t pos = page_offset(page) +
			(अक्षर *)de-(अक्षर*)page_address(page);
	पूर्णांक err;

	lock_page(page);

	err = minix_prepare_chunk(page, pos, sbi->s_dirsize);
	अगर (err == 0) अणु
		अगर (sbi->s_version == MINIX_V3)
			((minix3_dirent *) de)->inode = inode->i_ino;
		अन्यथा
			de->inode = inode->i_ino;
		err = dir_commit_chunk(page, pos, sbi->s_dirsize);
	पूर्ण अन्यथा अणु
		unlock_page(page);
	पूर्ण
	dir_put_page(page);
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	mark_inode_dirty(dir);
पूर्ण

काष्ठा minix_dir_entry * minix_करोtकरोt (काष्ठा inode *dir, काष्ठा page **p)
अणु
	काष्ठा page *page = dir_get_page(dir, 0);
	काष्ठा minix_sb_info *sbi = minix_sb(dir->i_sb);
	काष्ठा minix_dir_entry *de = शून्य;

	अगर (!IS_ERR(page)) अणु
		de = minix_next_entry(page_address(page), sbi);
		*p = page;
	पूर्ण
	वापस de;
पूर्ण

ino_t minix_inode_by_name(काष्ठा dentry *dentry)
अणु
	काष्ठा page *page;
	काष्ठा minix_dir_entry *de = minix_find_entry(dentry, &page);
	ino_t res = 0;

	अगर (de) अणु
		काष्ठा address_space *mapping = page->mapping;
		काष्ठा inode *inode = mapping->host;
		काष्ठा minix_sb_info *sbi = minix_sb(inode->i_sb);

		अगर (sbi->s_version == MINIX_V3)
			res = ((minix3_dirent *) de)->inode;
		अन्यथा
			res = de->inode;
		dir_put_page(page);
	पूर्ण
	वापस res;
पूर्ण
