<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/sysv/dir.c
 *
 *  minix/dir.c
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  coh/dir.c
 *  Copyright (C) 1993  Pascal Haible, Bruno Haible
 *
 *  sysv/dir.c
 *  Copyright (C) 1993  Bruno Haible
 *
 *  SystemV/Coherent directory handling functions
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/swap.h>
#समावेश "sysv.h"

अटल पूर्णांक sysv_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);

स्थिर काष्ठा file_operations sysv_dir_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= sysv_सूची_पढ़ो,
	.fsync		= generic_file_fsync,
पूर्ण;

अटल अंतरभूत व्योम dir_put_page(काष्ठा page *page)
अणु
	kunmap(page);
	put_page(page);
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

अटल पूर्णांक sysv_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	अचिन्हित दीर्घ pos = ctx->pos;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;
	अचिन्हित दीर्घ npages = dir_pages(inode);
	अचिन्हित offset;
	अचिन्हित दीर्घ n;

	ctx->pos = pos = (pos + SYSV_सूचीSIZE-1) & ~(SYSV_सूचीSIZE-1);
	अगर (pos >= inode->i_size)
		वापस 0;

	offset = pos & ~PAGE_MASK;
	n = pos >> PAGE_SHIFT;

	क्रम ( ; n < npages; n++, offset = 0) अणु
		अक्षर *kaddr, *limit;
		काष्ठा sysv_dir_entry *de;
		काष्ठा page *page = dir_get_page(inode, n);

		अगर (IS_ERR(page))
			जारी;
		kaddr = (अक्षर *)page_address(page);
		de = (काष्ठा sysv_dir_entry *)(kaddr+offset);
		limit = kaddr + PAGE_SIZE - SYSV_सूचीSIZE;
		क्रम ( ;(अक्षर*)de <= limit; de++, ctx->pos += माप(*de)) अणु
			अक्षर *name = de->name;

			अगर (!de->inode)
				जारी;

			अगर (!dir_emit(ctx, name, strnlen(name,SYSV_NAMELEN),
					fs16_to_cpu(SYSV_SB(sb), de->inode),
					DT_UNKNOWN)) अणु
				dir_put_page(page);
				वापस 0;
			पूर्ण
		पूर्ण
		dir_put_page(page);
	पूर्ण
	वापस 0;
पूर्ण

/* compare strings: name[0..len-1] (not zero-terminated) and
 * buffer[0..] (filled with zeroes up to buffer[0..maxlen-1])
 */
अटल अंतरभूत पूर्णांक namecompare(पूर्णांक len, पूर्णांक maxlen,
	स्थिर अक्षर * name, स्थिर अक्षर * buffer)
अणु
	अगर (len < maxlen && buffer[len])
		वापस 0;
	वापस !स_भेद(name, buffer, len);
पूर्ण

/*
 *	sysv_find_entry()
 *
 * finds an entry in the specअगरied directory with the wanted name. It
 * वापसs the cache buffer in which the entry was found, and the entry
 * itself (as a parameter - res_dir). It करोes NOT पढ़ो the inode of the
 * entry - you'll have to करो that yourself अगर you want to.
 */
काष्ठा sysv_dir_entry *sysv_find_entry(काष्ठा dentry *dentry, काष्ठा page **res_page)
अणु
	स्थिर अक्षर * name = dentry->d_name.name;
	पूर्णांक namelen = dentry->d_name.len;
	काष्ठा inode * dir = d_inode(dentry->d_parent);
	अचिन्हित दीर्घ start, n;
	अचिन्हित दीर्घ npages = dir_pages(dir);
	काष्ठा page *page = शून्य;
	काष्ठा sysv_dir_entry *de;

	*res_page = शून्य;

	start = SYSV_I(dir)->i_dir_start_lookup;
	अगर (start >= npages)
		start = 0;
	n = start;

	करो अणु
		अक्षर *kaddr;
		page = dir_get_page(dir, n);
		अगर (!IS_ERR(page)) अणु
			kaddr = (अक्षर*)page_address(page);
			de = (काष्ठा sysv_dir_entry *) kaddr;
			kaddr += PAGE_SIZE - SYSV_सूचीSIZE;
			क्रम ( ; (अक्षर *) de <= kaddr ; de++) अणु
				अगर (!de->inode)
					जारी;
				अगर (namecompare(namelen, SYSV_NAMELEN,
							name, de->name))
					जाओ found;
			पूर्ण
			dir_put_page(page);
		पूर्ण

		अगर (++n >= npages)
			n = 0;
	पूर्ण जबतक (n != start);

	वापस शून्य;

found:
	SYSV_I(dir)->i_dir_start_lookup = n;
	*res_page = page;
	वापस de;
पूर्ण

पूर्णांक sysv_add_link(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	स्थिर अक्षर * name = dentry->d_name.name;
	पूर्णांक namelen = dentry->d_name.len;
	काष्ठा page *page = शून्य;
	काष्ठा sysv_dir_entry * de;
	अचिन्हित दीर्घ npages = dir_pages(dir);
	अचिन्हित दीर्घ n;
	अक्षर *kaddr;
	loff_t pos;
	पूर्णांक err;

	/* We take care of directory expansion in the same loop */
	क्रम (n = 0; n <= npages; n++) अणु
		page = dir_get_page(dir, n);
		err = PTR_ERR(page);
		अगर (IS_ERR(page))
			जाओ out;
		kaddr = (अक्षर*)page_address(page);
		de = (काष्ठा sysv_dir_entry *)kaddr;
		kaddr += PAGE_SIZE - SYSV_सूचीSIZE;
		जबतक ((अक्षर *)de <= kaddr) अणु
			अगर (!de->inode)
				जाओ got_it;
			err = -EEXIST;
			अगर (namecompare(namelen, SYSV_NAMELEN, name, de->name)) 
				जाओ out_page;
			de++;
		पूर्ण
		dir_put_page(page);
	पूर्ण
	BUG();
	वापस -EINVAL;

got_it:
	pos = page_offset(page) +
			(अक्षर*)de - (अक्षर*)page_address(page);
	lock_page(page);
	err = sysv_prepare_chunk(page, pos, SYSV_सूचीSIZE);
	अगर (err)
		जाओ out_unlock;
	स_नकल (de->name, name, namelen);
	स_रखो (de->name + namelen, 0, SYSV_सूचीSIZE - namelen - 2);
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), inode->i_ino);
	err = dir_commit_chunk(page, pos, SYSV_सूचीSIZE);
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	mark_inode_dirty(dir);
out_page:
	dir_put_page(page);
out:
	वापस err;
out_unlock:
	unlock_page(page);
	जाओ out_page;
पूर्ण

पूर्णांक sysv_delete_entry(काष्ठा sysv_dir_entry *de, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	अक्षर *kaddr = (अक्षर*)page_address(page);
	loff_t pos = page_offset(page) + (अक्षर *)de - kaddr;
	पूर्णांक err;

	lock_page(page);
	err = sysv_prepare_chunk(page, pos, SYSV_सूचीSIZE);
	BUG_ON(err);
	de->inode = 0;
	err = dir_commit_chunk(page, pos, SYSV_सूचीSIZE);
	dir_put_page(page);
	inode->i_स_समय = inode->i_mसमय = current_समय(inode);
	mark_inode_dirty(inode);
	वापस err;
पूर्ण

पूर्णांक sysv_make_empty(काष्ठा inode *inode, काष्ठा inode *dir)
अणु
	काष्ठा page *page = grab_cache_page(inode->i_mapping, 0);
	काष्ठा sysv_dir_entry * de;
	अक्षर *base;
	पूर्णांक err;

	अगर (!page)
		वापस -ENOMEM;
	err = sysv_prepare_chunk(page, 0, 2 * SYSV_सूचीSIZE);
	अगर (err) अणु
		unlock_page(page);
		जाओ fail;
	पूर्ण
	kmap(page);

	base = (अक्षर*)page_address(page);
	स_रखो(base, 0, PAGE_SIZE);

	de = (काष्ठा sysv_dir_entry *) base;
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), inode->i_ino);
	म_नकल(de->name,".");
	de++;
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), dir->i_ino);
	म_नकल(de->name,"..");

	kunmap(page);
	err = dir_commit_chunk(page, 0, 2 * SYSV_सूचीSIZE);
fail:
	put_page(page);
	वापस err;
पूर्ण

/*
 * routine to check that the specअगरied directory is empty (क्रम सूची_हटाओ)
 */
पूर्णांक sysv_empty_dir(काष्ठा inode * inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा page *page = शून्य;
	अचिन्हित दीर्घ i, npages = dir_pages(inode);

	क्रम (i = 0; i < npages; i++) अणु
		अक्षर *kaddr;
		काष्ठा sysv_dir_entry * de;
		page = dir_get_page(inode, i);

		अगर (IS_ERR(page))
			जारी;

		kaddr = (अक्षर *)page_address(page);
		de = (काष्ठा sysv_dir_entry *)kaddr;
		kaddr += PAGE_SIZE-SYSV_सूचीSIZE;

		क्रम ( ;(अक्षर *)de <= kaddr; de++) अणु
			अगर (!de->inode)
				जारी;
			/* check क्रम . and .. */
			अगर (de->name[0] != '.')
				जाओ not_empty;
			अगर (!de->name[1]) अणु
				अगर (de->inode == cpu_to_fs16(SYSV_SB(sb),
							inode->i_ino))
					जारी;
				जाओ not_empty;
			पूर्ण
			अगर (de->name[1] != '.' || de->name[2])
				जाओ not_empty;
		पूर्ण
		dir_put_page(page);
	पूर्ण
	वापस 1;

not_empty:
	dir_put_page(page);
	वापस 0;
पूर्ण

/* Releases the page */
व्योम sysv_set_link(काष्ठा sysv_dir_entry *de, काष्ठा page *page,
	काष्ठा inode *inode)
अणु
	काष्ठा inode *dir = page->mapping->host;
	loff_t pos = page_offset(page) +
			(अक्षर *)de-(अक्षर*)page_address(page);
	पूर्णांक err;

	lock_page(page);
	err = sysv_prepare_chunk(page, pos, SYSV_सूचीSIZE);
	BUG_ON(err);
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), inode->i_ino);
	err = dir_commit_chunk(page, pos, SYSV_सूचीSIZE);
	dir_put_page(page);
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	mark_inode_dirty(dir);
पूर्ण

काष्ठा sysv_dir_entry * sysv_करोtकरोt (काष्ठा inode *dir, काष्ठा page **p)
अणु
	काष्ठा page *page = dir_get_page(dir, 0);
	काष्ठा sysv_dir_entry *de = शून्य;

	अगर (!IS_ERR(page)) अणु
		de = (काष्ठा sysv_dir_entry*) page_address(page) + 1;
		*p = page;
	पूर्ण
	वापस de;
पूर्ण

ino_t sysv_inode_by_name(काष्ठा dentry *dentry)
अणु
	काष्ठा page *page;
	काष्ठा sysv_dir_entry *de = sysv_find_entry (dentry, &page);
	ino_t res = 0;
	
	अगर (de) अणु
		res = fs16_to_cpu(SYSV_SB(dentry->d_sb), de->inode);
		dir_put_page(page);
	पूर्ण
	वापस res;
पूर्ण
