<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * QNX6 file प्रणाली, Linux implementation.
 *
 * Version : 1.0.0
 *
 * History :
 *
 * 01-02-2012 by Kai Bankett (chaosman@ontika.net) : first release.
 * 16-02-2012 pagemap extension by Al Viro
 *
 */

#समावेश "qnx6.h"

अटल अचिन्हित qnx6_lfile_checksum(अक्षर *name, अचिन्हित size)
अणु
	अचिन्हित crc = 0;
	अक्षर *end = name + size;
	जबतक (name < end) अणु
		crc = ((crc >> 1) + *(name++)) ^
			((crc & 0x00000001) ? 0x80000000 : 0);
	पूर्ण
	वापस crc;
पूर्ण

अटल काष्ठा page *qnx6_get_page(काष्ठा inode *dir, अचिन्हित दीर्घ n)
अणु
	काष्ठा address_space *mapping = dir->i_mapping;
	काष्ठा page *page = पढ़ो_mapping_page(mapping, n, शून्य);
	अगर (!IS_ERR(page))
		kmap(page);
	वापस page;
पूर्ण

अटल अचिन्हित last_entry(काष्ठा inode *inode, अचिन्हित दीर्घ page_nr)
अणु
	अचिन्हित दीर्घ last_byte = inode->i_size;
	last_byte -= page_nr << PAGE_SHIFT;
	अगर (last_byte > PAGE_SIZE)
		last_byte = PAGE_SIZE;
	वापस last_byte / QNX6_सूची_ENTRY_SIZE;
पूर्ण

अटल काष्ठा qnx6_दीर्घ_filename *qnx6_दीर्घname(काष्ठा super_block *sb,
					 काष्ठा qnx6_दीर्घ_dir_entry *de,
					 काष्ठा page **p)
अणु
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(sb);
	u32 s = fs32_to_cpu(sbi, de->de_दीर्घ_inode); /* in block units */
	u32 n = s >> (PAGE_SHIFT - sb->s_blocksize_bits); /* in pages */
	/* within page */
	u32 offs = (s << sb->s_blocksize_bits) & ~PAGE_MASK;
	काष्ठा address_space *mapping = sbi->दीर्घfile->i_mapping;
	काष्ठा page *page = पढ़ो_mapping_page(mapping, n, शून्य);
	अगर (IS_ERR(page))
		वापस ERR_CAST(page);
	kmap(*p = page);
	वापस (काष्ठा qnx6_दीर्घ_filename *)(page_address(page) + offs);
पूर्ण

अटल पूर्णांक qnx6_dir_दीर्घfilename(काष्ठा inode *inode,
			काष्ठा qnx6_दीर्घ_dir_entry *de,
			काष्ठा dir_context *ctx,
			अचिन्हित de_inode)
अणु
	काष्ठा qnx6_दीर्घ_filename *lf;
	काष्ठा super_block *s = inode->i_sb;
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(s);
	काष्ठा page *page;
	पूर्णांक lf_size;

	अगर (de->de_size != 0xff) अणु
		/* error - दीर्घ filename entries always have size 0xff
		   in direntry */
		pr_err("invalid direntry size (%i).\n", de->de_size);
		वापस 0;
	पूर्ण
	lf = qnx6_दीर्घname(s, de, &page);
	अगर (IS_ERR(lf)) अणु
		pr_err("Error reading longname\n");
		वापस 0;
	पूर्ण

	lf_size = fs16_to_cpu(sbi, lf->lf_size);

	अगर (lf_size > QNX6_LONG_NAME_MAX) अणु
		pr_debug("file %s\n", lf->lf_fname);
		pr_err("Filename too long (%i)\n", lf_size);
		qnx6_put_page(page);
		वापस 0;
	पूर्ण

	/* calc & validate दीर्घfilename checksum
	   mmi 3g fileप्रणाली करोes not have that checksum */
	अगर (!test_opt(s, MMI_FS) && fs32_to_cpu(sbi, de->de_checksum) !=
			qnx6_lfile_checksum(lf->lf_fname, lf_size))
		pr_info("long filename checksum error.\n");

	pr_debug("qnx6_readdir:%.*s inode:%u\n",
		 lf_size, lf->lf_fname, de_inode);
	अगर (!dir_emit(ctx, lf->lf_fname, lf_size, de_inode, DT_UNKNOWN)) अणु
		qnx6_put_page(page);
		वापस 0;
	पूर्ण

	qnx6_put_page(page);
	/* success */
	वापस 1;
पूर्ण

अटल पूर्णांक qnx6_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *s = inode->i_sb;
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(s);
	loff_t pos = ctx->pos & ~(QNX6_सूची_ENTRY_SIZE - 1);
	अचिन्हित दीर्घ npages = dir_pages(inode);
	अचिन्हित दीर्घ n = pos >> PAGE_SHIFT;
	अचिन्हित start = (pos & ~PAGE_MASK) / QNX6_सूची_ENTRY_SIZE;
	bool करोne = false;

	ctx->pos = pos;
	अगर (ctx->pos >= inode->i_size)
		वापस 0;

	क्रम ( ; !करोne && n < npages; n++, start = 0) अणु
		काष्ठा page *page = qnx6_get_page(inode, n);
		पूर्णांक limit = last_entry(inode, n);
		काष्ठा qnx6_dir_entry *de;
		पूर्णांक i = start;

		अगर (IS_ERR(page)) अणु
			pr_err("%s(): read failed\n", __func__);
			ctx->pos = (n + 1) << PAGE_SHIFT;
			वापस PTR_ERR(page);
		पूर्ण
		de = ((काष्ठा qnx6_dir_entry *)page_address(page)) + start;
		क्रम (; i < limit; i++, de++, ctx->pos += QNX6_सूची_ENTRY_SIZE) अणु
			पूर्णांक size = de->de_size;
			u32 no_inode = fs32_to_cpu(sbi, de->de_inode);

			अगर (!no_inode || !size)
				जारी;

			अगर (size > QNX6_SHORT_NAME_MAX) अणु
				/* दीर्घ filename detected
				   get the filename from दीर्घ filename
				   काष्ठाure / block */
				अगर (!qnx6_dir_दीर्घfilename(inode,
					(काष्ठा qnx6_दीर्घ_dir_entry *)de,
					ctx, no_inode)) अणु
					करोne = true;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				pr_debug("%s():%.*s inode:%u\n",
					 __func__, size, de->de_fname,
					 no_inode);
				अगर (!dir_emit(ctx, de->de_fname, size,
				      no_inode, DT_UNKNOWN)) अणु
					करोne = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		qnx6_put_page(page);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * check अगर the दीर्घ filename is correct.
 */
अटल अचिन्हित qnx6_दीर्घ_match(पूर्णांक len, स्थिर अक्षर *name,
			काष्ठा qnx6_दीर्घ_dir_entry *de, काष्ठा inode *dir)
अणु
	काष्ठा super_block *s = dir->i_sb;
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(s);
	काष्ठा page *page;
	पूर्णांक thislen;
	काष्ठा qnx6_दीर्घ_filename *lf = qnx6_दीर्घname(s, de, &page);

	अगर (IS_ERR(lf))
		वापस 0;

	thislen = fs16_to_cpu(sbi, lf->lf_size);
	अगर (len != thislen) अणु
		qnx6_put_page(page);
		वापस 0;
	पूर्ण
	अगर (स_भेद(name, lf->lf_fname, len) == 0) अणु
		qnx6_put_page(page);
		वापस fs32_to_cpu(sbi, de->de_inode);
	पूर्ण
	qnx6_put_page(page);
	वापस 0;
पूर्ण

/*
 * check अगर the filename is correct.
 */
अटल अचिन्हित qnx6_match(काष्ठा super_block *s, पूर्णांक len, स्थिर अक्षर *name,
			काष्ठा qnx6_dir_entry *de)
अणु
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(s);
	अगर (स_भेद(name, de->de_fname, len) == 0)
		वापस fs32_to_cpu(sbi, de->de_inode);
	वापस 0;
पूर्ण


अचिन्हित qnx6_find_entry(पूर्णांक len, काष्ठा inode *dir, स्थिर अक्षर *name,
			 काष्ठा page **res_page)
अणु
	काष्ठा super_block *s = dir->i_sb;
	काष्ठा qnx6_inode_info *ei = QNX6_I(dir);
	काष्ठा page *page = शून्य;
	अचिन्हित दीर्घ start, n;
	अचिन्हित दीर्घ npages = dir_pages(dir);
	अचिन्हित ino;
	काष्ठा qnx6_dir_entry *de;
	काष्ठा qnx6_दीर्घ_dir_entry *lde;

	*res_page = शून्य;

	अगर (npages == 0)
		वापस 0;
	start = ei->i_dir_start_lookup;
	अगर (start >= npages)
		start = 0;
	n = start;

	करो अणु
		page = qnx6_get_page(dir, n);
		अगर (!IS_ERR(page)) अणु
			पूर्णांक limit = last_entry(dir, n);
			पूर्णांक i;

			de = (काष्ठा qnx6_dir_entry *)page_address(page);
			क्रम (i = 0; i < limit; i++, de++) अणु
				अगर (len <= QNX6_SHORT_NAME_MAX) अणु
					/* लघु filename */
					अगर (len != de->de_size)
						जारी;
					ino = qnx6_match(s, len, name, de);
					अगर (ino)
						जाओ found;
				पूर्ण अन्यथा अगर (de->de_size == 0xff) अणु
					/* deal with दीर्घ filename */
					lde = (काष्ठा qnx6_दीर्घ_dir_entry *)de;
					ino = qnx6_दीर्घ_match(len,
								name, lde, dir);
					अगर (ino)
						जाओ found;
				पूर्ण अन्यथा
					pr_err("undefined filename size in inode.\n");
			पूर्ण
			qnx6_put_page(page);
		पूर्ण

		अगर (++n >= npages)
			n = 0;
	पूर्ण जबतक (n != start);
	वापस 0;

found:
	*res_page = page;
	ei->i_dir_start_lookup = n;
	वापस ino;
पूर्ण

स्थिर काष्ठा file_operations qnx6_dir_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= qnx6_सूची_पढ़ो,
	.fsync		= generic_file_fsync,
पूर्ण;

स्थिर काष्ठा inode_operations qnx6_dir_inode_operations = अणु
	.lookup		= qnx6_lookup,
पूर्ण;
