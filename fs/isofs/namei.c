<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/isofs/namei.c
 *
 *  (C) 1992  Eric Youngdale Modअगरied क्रम ISO 9660 fileप्रणाली.
 *
 *  (C) 1991  Linus Torvalds - minix fileप्रणाली
 */

#समावेश <linux/gfp.h>
#समावेश "isofs.h"

/*
 * ok, we cannot use म_भेदन, as the name is not in our data space.
 * Thus we'll have to use isofs_match. No big problem. Match also makes
 * some sanity tests.
 */
अटल पूर्णांक
isofs_cmp(काष्ठा dentry *dentry, स्थिर अक्षर *compare, पूर्णांक dlen)
अणु
	काष्ठा qstr qstr;
	qstr.name = compare;
	qstr.len = dlen;
	अगर (likely(!dentry->d_op))
		वापस dentry->d_name.len != dlen || स_भेद(dentry->d_name.name, compare, dlen);
	वापस dentry->d_op->d_compare(शून्य, dentry->d_name.len, dentry->d_name.name, &qstr);
पूर्ण

/*
 *	isofs_find_entry()
 *
 * finds an entry in the specअगरied directory with the wanted name. It
 * वापसs the inode number of the found entry, or 0 on error.
 */
अटल अचिन्हित दीर्घ
isofs_find_entry(काष्ठा inode *dir, काष्ठा dentry *dentry,
	अचिन्हित दीर्घ *block_rv, अचिन्हित दीर्घ *offset_rv,
	अक्षर *क्षणिकe, काष्ठा iso_directory_record *पंचांगpde)
अणु
	अचिन्हित दीर्घ bufsize = ISOFS_BUFFER_SIZE(dir);
	अचिन्हित अक्षर bufbits = ISOFS_BUFFER_BITS(dir);
	अचिन्हित दीर्घ block, f_pos, offset, block_saved, offset_saved;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा isofs_sb_info *sbi = ISOFS_SB(dir->i_sb);

	अगर (!ISOFS_I(dir)->i_first_extent)
		वापस 0;

	f_pos = 0;
	offset = 0;
	block = 0;

	जबतक (f_pos < dir->i_size) अणु
		काष्ठा iso_directory_record *de;
		पूर्णांक de_len, match, i, dlen;
		अक्षर *dpnt;

		अगर (!bh) अणु
			bh = isofs_bपढ़ो(dir, block);
			अगर (!bh)
				वापस 0;
		पूर्ण

		de = (काष्ठा iso_directory_record *) (bh->b_data + offset);

		de_len = *(अचिन्हित अक्षर *) de;
		अगर (!de_len) अणु
			brअन्यथा(bh);
			bh = शून्य;
			f_pos = (f_pos + ISOFS_BLOCK_SIZE) & ~(ISOFS_BLOCK_SIZE - 1);
			block = f_pos >> bufbits;
			offset = 0;
			जारी;
		पूर्ण

		block_saved = bh->b_blocknr;
		offset_saved = offset;
		offset += de_len;
		f_pos += de_len;

		/* Make sure we have a full directory entry */
		अगर (offset >= bufsize) अणु
			पूर्णांक slop = bufsize - offset + de_len;
			स_नकल(पंचांगpde, de, slop);
			offset &= bufsize - 1;
			block++;
			brअन्यथा(bh);
			bh = शून्य;
			अगर (offset) अणु
				bh = isofs_bपढ़ो(dir, block);
				अगर (!bh)
					वापस 0;
				स_नकल((व्योम *) पंचांगpde + slop, bh->b_data, offset);
			पूर्ण
			de = पंचांगpde;
		पूर्ण

		dlen = de->name_len[0];
		dpnt = de->name;
		/* Basic sanity check, whether name करोesn't exceed dir entry */
		अगर (de_len < dlen + माप(काष्ठा iso_directory_record)) अणु
			prपूर्णांकk(KERN_NOTICE "iso9660: Corrupted directory entry"
			       " in block %lu of inode %lu\n", block,
			       dir->i_ino);
			brअन्यथा(bh);
			वापस 0;
		पूर्ण

		अगर (sbi->s_rock &&
		    ((i = get_rock_ridge_filename(de, क्षणिकe, dir)))) अणु
			dlen = i;	/* possibly -1 */
			dpnt = क्षणिकe;
#अगर_घोषित CONFIG_JOLIET
		पूर्ण अन्यथा अगर (sbi->s_joliet_level) अणु
			dlen = get_joliet_filename(de, क्षणिकe, dir);
			dpnt = क्षणिकe;
#पूर्ण_अगर
		पूर्ण अन्यथा अगर (sbi->s_mapping == 'a') अणु
			dlen = get_acorn_filename(de, क्षणिकe, dir);
			dpnt = क्षणिकe;
		पूर्ण अन्यथा अगर (sbi->s_mapping == 'n') अणु
			dlen = isofs_name_translate(de, क्षणिकe, dir);
			dpnt = क्षणिकe;
		पूर्ण

		/*
		 * Skip hidden or associated files unless hide or showassoc,
		 * respectively, is set
		 */
		match = 0;
		अगर (dlen > 0 &&
			(!sbi->s_hide ||
				(!(de->flags[-sbi->s_high_sierra] & 1))) &&
			(sbi->s_showassoc ||
				(!(de->flags[-sbi->s_high_sierra] & 4)))) अणु
			अगर (dpnt && (dlen > 1 || dpnt[0] > 1))
				match = (isofs_cmp(dentry, dpnt, dlen) == 0);
		पूर्ण
		अगर (match) अणु
			isofs_normalize_block_and_offset(de,
							 &block_saved,
							 &offset_saved);
			*block_rv = block_saved;
			*offset_rv = offset_saved;
			brअन्यथा(bh);
			वापस 1;
		पूर्ण
	पूर्ण
	brअन्यथा(bh);
	वापस 0;
पूर्ण

काष्ठा dentry *isofs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक found;
	अचिन्हित दीर्घ block;
	अचिन्हित दीर्घ offset;
	काष्ठा inode *inode;
	काष्ठा page *page;

	page = alloc_page(GFP_USER);
	अगर (!page)
		वापस ERR_PTR(-ENOMEM);

	found = isofs_find_entry(dir, dentry,
				&block, &offset,
				page_address(page),
				1024 + page_address(page));
	__मुक्त_page(page);

	inode = found ? isofs_iget(dir->i_sb, block, offset) : शून्य;

	वापस d_splice_alias(inode, dentry);
पूर्ण
