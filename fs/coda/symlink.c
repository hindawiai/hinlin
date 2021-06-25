<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Symlink inode operations क्रम Coda fileप्रणाली
 * Original version: (C) 1996 P. Braam and M. Callahan
 * Rewritten क्रम Linux 2.1. (C) 1997 Carnegie Mellon University
 * 
 * Carnegie Mellon encourages users to contribute improvements to
 * the Coda project. Contact Peter Braam (coda@cs.cmu.edu).
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pagemap.h>

#समावेश <linux/coda.h>
#समावेश "coda_psdev.h"
#समावेश "coda_linux.h"

अटल पूर्णांक coda_symlink_filler(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	पूर्णांक error;
	काष्ठा coda_inode_info *cii;
	अचिन्हित पूर्णांक len = PAGE_SIZE;
	अक्षर *p = page_address(page);

	cii = ITOC(inode);

	error = venus_पढ़ोlink(inode->i_sb, &cii->c_fid, p, &len);
	अगर (error)
		जाओ fail;
	SetPageUptodate(page);
	unlock_page(page);
	वापस 0;

fail:
	SetPageError(page);
	unlock_page(page);
	वापस error;
पूर्ण

स्थिर काष्ठा address_space_operations coda_symlink_aops = अणु
	.पढ़ोpage	= coda_symlink_filler,
पूर्ण;
