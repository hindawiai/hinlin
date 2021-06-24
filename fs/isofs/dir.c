<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/isofs/dir.c
 *
 *  (C) 1992, 1993, 1994  Eric Youngdale Modअगरied क्रम ISO 9660 fileप्रणाली.
 *
 *  (C) 1991  Linus Torvalds - minix fileप्रणाली
 *
 *  Steve Beynon		       : Missing last directory entries fixed
 *  (stephen@askone.demon.co.uk)      : 21st June 1996
 *
 *  isofs directory handling functions
 */
#समावेश <linux/gfp.h>
#समावेश "isofs.h"

पूर्णांक isofs_name_translate(काष्ठा iso_directory_record *de, अक्षर *new, काष्ठा inode *inode)
अणु
	अक्षर * old = de->name;
	पूर्णांक len = de->name_len[0];
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		अचिन्हित अक्षर c = old[i];
		अगर (!c)
			अवरोध;

		अगर (c >= 'A' && c <= 'Z')
			c |= 0x20;	/* lower हाल */

		/* Drop trailing '.;1' (ISO 9660:1988 7.5.1 requires period) */
		अगर (c == '.' && i == len - 3 && old[i + 1] == ';' && old[i + 2] == '1')
			अवरोध;

		/* Drop trailing ';1' */
		अगर (c == ';' && i == len - 2 && old[i + 1] == '1')
			अवरोध;

		/* Convert reमुख्यing ';' to '.' */
		/* Also '/' to '.' (broken Acorn-generated ISO9660 images) */
		अगर (c == ';' || c == '/')
			c = '.';

		new[i] = c;
	पूर्ण
	वापस i;
पूर्ण

/* Acorn extensions written by Matthew Wilcox <willy@infradead.org> 1998 */
पूर्णांक get_acorn_filename(काष्ठा iso_directory_record *de,
			    अक्षर *retname, काष्ठा inode *inode)
अणु
	पूर्णांक std;
	अचिन्हित अक्षर *chr;
	पूर्णांक retnamlen = isofs_name_translate(de, retname, inode);

	अगर (retnamlen == 0)
		वापस 0;
	std = माप(काष्ठा iso_directory_record) + de->name_len[0];
	अगर (std & 1)
		std++;
	अगर (de->length[0] - std != 32)
		वापस retnamlen;
	chr = ((अचिन्हित अक्षर *) de) + std;
	अगर (म_भेदन(chr, "ARCHIMEDES", 10))
		वापस retnamlen;
	अगर ((*retname == '_') && ((chr[19] & 1) == 1))
		*retname = '!';
	अगर (((de->flags[0] & 2) == 0) && (chr[13] == 0xff)
		&& ((chr[12] & 0xf0) == 0xf0)) अणु
		retname[retnamlen] = ',';
		प्र_लिखो(retname+retnamlen+1, "%3.3x",
			((chr[12] & 0xf) << 8) | chr[11]);
		retnamlen += 4;
	पूर्ण
	वापस retnamlen;
पूर्ण

/*
 * This should _really_ be cleaned up some day..
 */
अटल पूर्णांक करो_isofs_सूची_पढ़ो(काष्ठा inode *inode, काष्ठा file *file,
		काष्ठा dir_context *ctx,
		अक्षर *क्षणिकe, काष्ठा iso_directory_record *पंचांगpde)
अणु
	अचिन्हित दीर्घ bufsize = ISOFS_BUFFER_SIZE(inode);
	अचिन्हित अक्षर bufbits = ISOFS_BUFFER_BITS(inode);
	अचिन्हित दीर्घ block, offset, block_saved, offset_saved;
	अचिन्हित दीर्घ inode_number = 0;	/* Quiet GCC */
	काष्ठा buffer_head *bh = शून्य;
	पूर्णांक len;
	पूर्णांक map;
	पूर्णांक first_de = 1;
	अक्षर *p = शून्य;		/* Quiet GCC */
	काष्ठा iso_directory_record *de;
	काष्ठा isofs_sb_info *sbi = ISOFS_SB(inode->i_sb);

	offset = ctx->pos & (bufsize - 1);
	block = ctx->pos >> bufbits;

	जबतक (ctx->pos < inode->i_size) अणु
		पूर्णांक de_len;

		अगर (!bh) अणु
			bh = isofs_bपढ़ो(inode, block);
			अगर (!bh)
				वापस 0;
		पूर्ण

		de = (काष्ठा iso_directory_record *) (bh->b_data + offset);

		de_len = *(अचिन्हित अक्षर *)de;

		/*
		 * If the length byte is zero, we should move on to the next
		 * CDROM sector.  If we are at the end of the directory, we
		 * kick out of the जबतक loop.
		 */

		अगर (de_len == 0) अणु
			brअन्यथा(bh);
			bh = शून्य;
			ctx->pos = (ctx->pos + ISOFS_BLOCK_SIZE) & ~(ISOFS_BLOCK_SIZE - 1);
			block = ctx->pos >> bufbits;
			offset = 0;
			जारी;
		पूर्ण

		block_saved = block;
		offset_saved = offset;
		offset += de_len;

		/* Make sure we have a full directory entry */
		अगर (offset >= bufsize) अणु
			पूर्णांक slop = bufsize - offset + de_len;
			स_नकल(पंचांगpde, de, slop);
			offset &= bufsize - 1;
			block++;
			brअन्यथा(bh);
			bh = शून्य;
			अगर (offset) अणु
				bh = isofs_bपढ़ो(inode, block);
				अगर (!bh)
					वापस 0;
				स_नकल((व्योम *) पंचांगpde + slop, bh->b_data, offset);
			पूर्ण
			de = पंचांगpde;
		पूर्ण
		/* Basic sanity check, whether name करोesn't exceed dir entry */
		अगर (de_len < de->name_len[0] +
					माप(काष्ठा iso_directory_record)) अणु
			prपूर्णांकk(KERN_NOTICE "iso9660: Corrupted directory entry"
			       " in block %lu of inode %lu\n", block,
			       inode->i_ino);
			brअन्यथा(bh);
			वापस -EIO;
		पूर्ण

		अगर (first_de) अणु
			isofs_normalize_block_and_offset(de,
							&block_saved,
							&offset_saved);
			inode_number = isofs_get_ino(block_saved,
							offset_saved, bufbits);
		पूर्ण

		अगर (de->flags[-sbi->s_high_sierra] & 0x80) अणु
			first_de = 0;
			ctx->pos += de_len;
			जारी;
		पूर्ण
		first_de = 1;

		/* Handle the हाल of the '.' directory */
		अगर (de->name_len[0] == 1 && de->name[0] == 0) अणु
			अगर (!dir_emit_करोt(file, ctx))
				अवरोध;
			ctx->pos += de_len;
			जारी;
		पूर्ण

		len = 0;

		/* Handle the हाल of the '..' directory */
		अगर (de->name_len[0] == 1 && de->name[0] == 1) अणु
			अगर (!dir_emit_करोtकरोt(file, ctx))
				अवरोध;
			ctx->pos += de_len;
			जारी;
		पूर्ण

		/* Handle everything अन्यथा.  Do name translation अगर there
		   is no Rock Ridge NM field. */

		/*
		 * Do not report hidden files अगर so inकाष्ठाed, or associated
		 * files unless inकाष्ठाed to करो so
		 */
		अगर ((sbi->s_hide && (de->flags[-sbi->s_high_sierra] & 1)) ||
		    (!sbi->s_showassoc &&
				(de->flags[-sbi->s_high_sierra] & 4))) अणु
			ctx->pos += de_len;
			जारी;
		पूर्ण

		map = 1;
		अगर (sbi->s_rock) अणु
			len = get_rock_ridge_filename(de, क्षणिकe, inode);
			अगर (len != 0) अणु		/* may be -1 */
				p = क्षणिकe;
				map = 0;
			पूर्ण
		पूर्ण
		अगर (map) अणु
#अगर_घोषित CONFIG_JOLIET
			अगर (sbi->s_joliet_level) अणु
				len = get_joliet_filename(de, क्षणिकe, inode);
				p = क्षणिकe;
			पूर्ण अन्यथा
#पूर्ण_अगर
			अगर (sbi->s_mapping == 'a') अणु
				len = get_acorn_filename(de, क्षणिकe, inode);
				p = क्षणिकe;
			पूर्ण अन्यथा
			अगर (sbi->s_mapping == 'n') अणु
				len = isofs_name_translate(de, क्षणिकe, inode);
				p = क्षणिकe;
			पूर्ण अन्यथा अणु
				p = de->name;
				len = de->name_len[0];
			पूर्ण
		पूर्ण
		अगर (len > 0) अणु
			अगर (!dir_emit(ctx, p, len, inode_number, DT_UNKNOWN))
				अवरोध;
		पूर्ण
		ctx->pos += de_len;

		जारी;
	पूर्ण
	अगर (bh)
		brअन्यथा(bh);
	वापस 0;
पूर्ण

/*
 * Handle allocation of temporary space क्रम name translation and
 * handling split directory entries.. The real work is करोne by
 * "do_isofs_readdir()".
 */
अटल पूर्णांक isofs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	पूर्णांक result;
	अक्षर *क्षणिकe;
	काष्ठा iso_directory_record *पंचांगpde;
	काष्ठा inode *inode = file_inode(file);

	क्षणिकe = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (क्षणिकe == शून्य)
		वापस -ENOMEM;

	पंचांगpde = (काष्ठा iso_directory_record *) (क्षणिकe+1024);

	result = करो_isofs_सूची_पढ़ो(inode, file, ctx, क्षणिकe, पंचांगpde);

	मुक्त_page((अचिन्हित दीर्घ) क्षणिकe);
	वापस result;
पूर्ण

स्थिर काष्ठा file_operations isofs_dir_operations =
अणु
	.llseek = generic_file_llseek,
	.पढ़ो = generic_पढ़ो_dir,
	.iterate_shared = isofs_सूची_पढ़ो,
पूर्ण;

/*
 * directories can handle most operations...
 */
स्थिर काष्ठा inode_operations isofs_dir_inode_operations =
अणु
	.lookup = isofs_lookup,
पूर्ण;


