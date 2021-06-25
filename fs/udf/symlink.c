<शैली गुरु>
/*
 * symlink.c
 *
 * PURPOSE
 *	Symlink handling routines क्रम the OSTA-UDF(पंचांग) fileप्रणाली.
 *
 * COPYRIGHT
 *	This file is distributed under the terms of the GNU General Public
 *	License (GPL). Copies of the GPL can be obtained from:
 *		ftp://prep.ai.mit.edu/pub/gnu/GPL
 *	Each contributing author retains all rights to their own work.
 *
 *  (C) 1998-2001 Ben Fennema
 *  (C) 1999 Stelias Computing Inc
 *
 * HISTORY
 *
 *  04/16/99 blf  Created.
 *
 */

#समावेश "udfdecl.h"
#समावेश <linux/uaccess.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/pagemap.h>
#समावेश "udf_i.h"

अटल पूर्णांक udf_pc_to_अक्षर(काष्ठा super_block *sb, अचिन्हित अक्षर *from,
			  पूर्णांक fromlen, अचिन्हित अक्षर *to, पूर्णांक tolen)
अणु
	काष्ठा pathComponent *pc;
	पूर्णांक elen = 0;
	पूर्णांक comp_len;
	अचिन्हित अक्षर *p = to;

	/* Reserve one byte क्रम terminating \0 */
	tolen--;
	जबतक (elen < fromlen) अणु
		pc = (काष्ठा pathComponent *)(from + elen);
		elen += माप(काष्ठा pathComponent);
		चयन (pc->componentType) अणु
		हाल 1:
			/*
			 * Symlink poपूर्णांकs to some place which should be agreed
 			 * upon between originator and receiver of the media. Ignore.
			 */
			अगर (pc->lengthComponentIdent > 0) अणु
				elen += pc->lengthComponentIdent;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल 2:
			अगर (tolen == 0)
				वापस -ENAMETOOLONG;
			p = to;
			*p++ = '/';
			tolen--;
			अवरोध;
		हाल 3:
			अगर (tolen < 3)
				वापस -ENAMETOOLONG;
			स_नकल(p, "../", 3);
			p += 3;
			tolen -= 3;
			अवरोध;
		हाल 4:
			अगर (tolen < 2)
				वापस -ENAMETOOLONG;
			स_नकल(p, "./", 2);
			p += 2;
			tolen -= 2;
			/* that would be . - just ignore */
			अवरोध;
		हाल 5:
			elen += pc->lengthComponentIdent;
			अगर (elen > fromlen)
				वापस -EIO;
			comp_len = udf_get_filename(sb, pc->componentIdent,
						    pc->lengthComponentIdent,
						    p, tolen);
			अगर (comp_len < 0)
				वापस comp_len;

			p += comp_len;
			tolen -= comp_len;
			अगर (tolen == 0)
				वापस -ENAMETOOLONG;
			*p++ = '/';
			tolen--;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (p > to + 1)
		p[-1] = '\0';
	अन्यथा
		p[0] = '\0';
	वापस 0;
पूर्ण

अटल पूर्णांक udf_symlink_filler(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा buffer_head *bh = शून्य;
	अचिन्हित अक्षर *symlink;
	पूर्णांक err;
	अचिन्हित अक्षर *p = page_address(page);
	काष्ठा udf_inode_info *iinfo;
	uपूर्णांक32_t pos;

	/* We करोn't support symlinks दीर्घer than one block */
	अगर (inode->i_size > inode->i_sb->s_blocksize) अणु
		err = -ENAMETOOLONG;
		जाओ out_unmap;
	पूर्ण

	iinfo = UDF_I(inode);
	pos = udf_block_map(inode, 0);

	करोwn_पढ़ो(&iinfo->i_data_sem);
	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) अणु
		symlink = iinfo->i_data + iinfo->i_lenEAttr;
	पूर्ण अन्यथा अणु
		bh = sb_bपढ़ो(inode->i_sb, pos);

		अगर (!bh) अणु
			err = -EIO;
			जाओ out_unlock_inode;
		पूर्ण

		symlink = bh->b_data;
	पूर्ण

	err = udf_pc_to_अक्षर(inode->i_sb, symlink, inode->i_size, p, PAGE_SIZE);
	brअन्यथा(bh);
	अगर (err)
		जाओ out_unlock_inode;

	up_पढ़ो(&iinfo->i_data_sem);
	SetPageUptodate(page);
	unlock_page(page);
	वापस 0;

out_unlock_inode:
	up_पढ़ो(&iinfo->i_data_sem);
	SetPageError(page);
out_unmap:
	unlock_page(page);
	वापस err;
पूर्ण

अटल पूर्णांक udf_symlink_getattr(काष्ठा user_namespace *mnt_userns,
			       स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			       u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा inode *inode = d_backing_inode(dentry);
	काष्ठा page *page;

	generic_fillattr(&init_user_ns, inode, stat);
	page = पढ़ो_mapping_page(inode->i_mapping, 0, शून्य);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page);
	/*
	 * UDF uses non-trivial encoding of symlinks so i_size करोes not match
	 * number of अक्षरacters reported by पढ़ोlink(2) which apparently some
	 * applications expect. Also POSIX says that "The value वापसed in the
	 * st_size field shall be the length of the contents of the symbolic
	 * link, and shall not count a trailing null अगर one is present." So
	 * let's report the length of string वापसed by पढ़ोlink(2) क्रम
	 * st_size.
	 */
	stat->size = म_माप(page_address(page));
	put_page(page);

	वापस 0;
पूर्ण

/*
 * symlinks can't करो much...
 */
स्थिर काष्ठा address_space_operations udf_symlink_aops = अणु
	.पढ़ोpage		= udf_symlink_filler,
पूर्ण;

स्थिर काष्ठा inode_operations udf_symlink_inode_operations = अणु
	.get_link	= page_get_link,
	.getattr	= udf_symlink_getattr,
पूर्ण;
