<शैली गुरु>
/*
 *  linux/cluster/ssi/cfs/symlink.c
 *
 *	This program is मुक्त software; you can redistribute it and/or
 *	modअगरy it under the terms of the GNU General Public License as
 *	published by the Free Software Foundation; either version 2 of
 *	the License, or (at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE
 *	or NON INFRINGEMENT.  See the GNU General Public License क्रम more
 *	details.
 *
 * 	You should have received a copy of the GNU General Public License
 * 	aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * 	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *	Questions/Comments/Bugfixes to ssic-linux-devel@lists.sourceक्रमge.net
 *
 *  Copyright (C) 1992  Rick Sladkey
 *
 *  Optimization changes Copyright (C) 1994 Florian La Roche
 *
 *  Jun 7 1999, cache symlink lookups in the page cache.  -DaveM
 *
 *  Portions Copyright (C) 2001 Compaq Computer Corporation
 *
 *  ocfs2 symlink handling code.
 *
 *  Copyright (C) 2004, 2005 Oracle.
 *
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/namei.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "file.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "symlink.h"
#समावेश "xattr.h"

#समावेश "buffer_head_io.h"


अटल पूर्णांक ocfs2_fast_symlink_पढ़ोpage(काष्ठा file *unused, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा buffer_head *bh = शून्य;
	पूर्णांक status = ocfs2_पढ़ो_inode_block(inode, &bh);
	काष्ठा ocfs2_dinode *fe;
	स्थिर अक्षर *link;
	व्योम *kaddr;
	माप_प्रकार len;

	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	fe = (काष्ठा ocfs2_dinode *) bh->b_data;
	link = (अक्षर *) fe->id2.i_symlink;
	/* will be less than a page size */
	len = strnlen(link, ocfs2_fast_symlink_अक्षरs(inode->i_sb));
	kaddr = kmap_atomic(page);
	स_नकल(kaddr, link, len + 1);
	kunmap_atomic(kaddr);
	SetPageUptodate(page);
	unlock_page(page);
	brअन्यथा(bh);
	वापस 0;
पूर्ण

स्थिर काष्ठा address_space_operations ocfs2_fast_symlink_aops = अणु
	.पढ़ोpage		= ocfs2_fast_symlink_पढ़ोpage,
पूर्ण;

स्थिर काष्ठा inode_operations ocfs2_symlink_inode_operations = अणु
	.get_link	= page_get_link,
	.getattr	= ocfs2_getattr,
	.setattr	= ocfs2_setattr,
	.listxattr	= ocfs2_listxattr,
	.fiemap		= ocfs2_fiemap,
पूर्ण;
