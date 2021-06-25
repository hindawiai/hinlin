<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/affs/symlink.c
 *
 *  1995  Hans-Joachim Widmaier - Modअगरied क्रम affs.
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  affs symlink handling code
 */

#समावेश "affs.h"

अटल पूर्णांक affs_symlink_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा inode *inode = page->mapping->host;
	अक्षर *link = page_address(page);
	काष्ठा slink_front *lf;
	पूर्णांक			 i, j;
	अक्षर			 c;
	अक्षर			 lc;

	pr_debug("get_link(ino=%lu)\n", inode->i_ino);

	bh = affs_bपढ़ो(inode->i_sb, inode->i_ino);
	अगर (!bh)
		जाओ fail;
	i  = 0;
	j  = 0;
	lf = (काष्ठा slink_front *)bh->b_data;
	lc = 0;

	अगर (म_अक्षर(lf->symname,':')) अणु	/* Handle assign or volume name */
		काष्ठा affs_sb_info *sbi = AFFS_SB(inode->i_sb);
		अक्षर *pf;
		spin_lock(&sbi->symlink_lock);
		pf = sbi->s_prefix ? sbi->s_prefix : "/";
		जबतक (i < 1023 && (c = pf[i]))
			link[i++] = c;
		spin_unlock(&sbi->symlink_lock);
		जबतक (i < 1023 && lf->symname[j] != ':')
			link[i++] = lf->symname[j++];
		अगर (i < 1023)
			link[i++] = '/';
		j++;
		lc = '/';
	पूर्ण
	जबतक (i < 1023 && (c = lf->symname[j])) अणु
		अगर (c == '/' && lc == '/' && i < 1020) अणु	/* parent dir */
			link[i++] = '.';
			link[i++] = '.';
		पूर्ण
		link[i++] = c;
		lc = c;
		j++;
	पूर्ण
	link[i] = '\0';
	affs_brअन्यथा(bh);
	SetPageUptodate(page);
	unlock_page(page);
	वापस 0;
fail:
	SetPageError(page);
	unlock_page(page);
	वापस -EIO;
पूर्ण

स्थिर काष्ठा address_space_operations affs_symlink_aops = अणु
	.पढ़ोpage	= affs_symlink_पढ़ोpage,
पूर्ण;

स्थिर काष्ठा inode_operations affs_symlink_inode_operations = अणु
	.get_link	= page_get_link,
	.setattr	= affs_notअगरy_change,
पूर्ण;
