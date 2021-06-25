<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/nfs/symlink.c
 *
 *  Copyright (C) 1992  Rick Sladkey
 *
 *  Optimization changes Copyright (C) 1994 Florian La Roche
 *
 *  Jun 7 1999, cache symlink lookups in the page cache.  -DaveM
 *
 *  nfs symlink handling code
 */

#समावेश <linux/समय.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs2.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>

/* Symlink caching in the page cache is even more simplistic
 * and straight-क्रमward than सूची_पढ़ो caching.
 */

अटल पूर्णांक nfs_symlink_filler(व्योम *data, काष्ठा page *page)
अणु
	काष्ठा inode *inode = data;
	पूर्णांक error;

	error = NFS_PROTO(inode)->पढ़ोlink(inode, page, 0, PAGE_SIZE);
	अगर (error < 0)
		जाओ error;
	SetPageUptodate(page);
	unlock_page(page);
	वापस 0;

error:
	SetPageError(page);
	unlock_page(page);
	वापस -EIO;
पूर्ण

अटल स्थिर अक्षर *nfs_get_link(काष्ठा dentry *dentry,
				काष्ठा inode *inode,
				काष्ठा delayed_call *करोne)
अणु
	काष्ठा page *page;
	व्योम *err;

	अगर (!dentry) अणु
		err = ERR_PTR(nfs_revalidate_mapping_rcu(inode));
		अगर (err)
			वापस err;
		page = find_get_page(inode->i_mapping, 0);
		अगर (!page)
			वापस ERR_PTR(-ECHILD);
		अगर (!PageUptodate(page)) अणु
			put_page(page);
			वापस ERR_PTR(-ECHILD);
		पूर्ण
	पूर्ण अन्यथा अणु
		err = ERR_PTR(nfs_revalidate_mapping(inode, inode->i_mapping));
		अगर (err)
			वापस err;
		page = पढ़ो_cache_page(&inode->i_data, 0, nfs_symlink_filler,
				inode);
		अगर (IS_ERR(page))
			वापस ERR_CAST(page);
	पूर्ण
	set_delayed_call(करोne, page_put_link, page);
	वापस page_address(page);
पूर्ण

/*
 * symlinks can't करो much...
 */
स्थिर काष्ठा inode_operations nfs_symlink_inode_operations = अणु
	.get_link	= nfs_get_link,
	.getattr	= nfs_getattr,
	.setattr	= nfs_setattr,
पूर्ण;
