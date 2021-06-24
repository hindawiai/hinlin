<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/crc32.h>
#समावेश <linux/jffs2.h>
#समावेश "nodelist.h"

अटल पूर्णांक jffs2_ग_लिखो_end(काष्ठा file *filp, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *pg, व्योम *fsdata);
अटल पूर्णांक jffs2_ग_लिखो_begin(काष्ठा file *filp, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata);
अटल पूर्णांक jffs2_पढ़ोpage (काष्ठा file *filp, काष्ठा page *pg);

पूर्णांक jffs2_fsync(काष्ठा file *filp, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा inode *inode = filp->f_mapping->host;
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	पूर्णांक ret;

	ret = file_ग_लिखो_and_रुको_range(filp, start, end);
	अगर (ret)
		वापस ret;

	inode_lock(inode);
	/* Trigger GC to flush any pending ग_लिखोs क्रम this inode */
	jffs2_flush_wbuf_gc(c, inode->i_ino);
	inode_unlock(inode);

	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations jffs2_file_operations =
अणु
	.llseek =	generic_file_llseek,
	.खोलो =		generic_file_खोलो,
 	.पढ़ो_iter =	generic_file_पढ़ो_iter,
 	.ग_लिखो_iter =	generic_file_ग_लिखो_iter,
	.unlocked_ioctl=jffs2_ioctl,
	.mmap =		generic_file_पढ़ोonly_mmap,
	.fsync =	jffs2_fsync,
	.splice_पढ़ो =	generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
पूर्ण;

/* jffs2_file_inode_operations */

स्थिर काष्ठा inode_operations jffs2_file_inode_operations =
अणु
	.get_acl =	jffs2_get_acl,
	.set_acl =	jffs2_set_acl,
	.setattr =	jffs2_setattr,
	.listxattr =	jffs2_listxattr,
पूर्ण;

स्थिर काष्ठा address_space_operations jffs2_file_address_operations =
अणु
	.पढ़ोpage =	jffs2_पढ़ोpage,
	.ग_लिखो_begin =	jffs2_ग_लिखो_begin,
	.ग_लिखो_end =	jffs2_ग_लिखो_end,
पूर्ण;

अटल पूर्णांक jffs2_करो_पढ़ोpage_nolock (काष्ठा inode *inode, काष्ठा page *pg)
अणु
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	अचिन्हित अक्षर *pg_buf;
	पूर्णांक ret;

	jffs2_dbg(2, "%s(): ino #%lu, page at offset 0x%lx\n",
		  __func__, inode->i_ino, pg->index << PAGE_SHIFT);

	BUG_ON(!PageLocked(pg));

	pg_buf = kmap(pg);
	/* FIXME: Can kmap fail? */

	ret = jffs2_पढ़ो_inode_range(c, f, pg_buf, pg->index << PAGE_SHIFT,
				     PAGE_SIZE);

	अगर (ret) अणु
		ClearPageUptodate(pg);
		SetPageError(pg);
	पूर्ण अन्यथा अणु
		SetPageUptodate(pg);
		ClearPageError(pg);
	पूर्ण

	flush_dcache_page(pg);
	kunmap(pg);

	jffs2_dbg(2, "readpage finished\n");
	वापस ret;
पूर्ण

पूर्णांक jffs2_करो_पढ़ोpage_unlock(व्योम *data, काष्ठा page *pg)
अणु
	पूर्णांक ret = jffs2_करो_पढ़ोpage_nolock(data, pg);
	unlock_page(pg);
	वापस ret;
पूर्ण


अटल पूर्णांक jffs2_पढ़ोpage (काष्ठा file *filp, काष्ठा page *pg)
अणु
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(pg->mapping->host);
	पूर्णांक ret;

	mutex_lock(&f->sem);
	ret = jffs2_करो_पढ़ोpage_unlock(pg->mapping->host, pg);
	mutex_unlock(&f->sem);
	वापस ret;
पूर्ण

अटल पूर्णांक jffs2_ग_लिखो_begin(काष्ठा file *filp, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	काष्ठा page *pg;
	काष्ठा inode *inode = mapping->host;
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	pgoff_t index = pos >> PAGE_SHIFT;
	uपूर्णांक32_t pageofs = index << PAGE_SHIFT;
	पूर्णांक ret = 0;

	pg = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!pg)
		वापस -ENOMEM;
	*pagep = pg;

	jffs2_dbg(1, "%s()\n", __func__);

	अगर (pageofs > inode->i_size) अणु
		/* Make new hole frag from old खातापूर्ण to new page */
		काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
		काष्ठा jffs2_raw_inode ri;
		काष्ठा jffs2_full_dnode *fn;
		uपूर्णांक32_t alloc_len;

		jffs2_dbg(1, "Writing new hole frag 0x%x-0x%x between current EOF and new page\n",
			  (अचिन्हित पूर्णांक)inode->i_size, pageofs);

		ret = jffs2_reserve_space(c, माप(ri), &alloc_len,
					  ALLOC_NORMAL, JFFS2_SUMMARY_INODE_SIZE);
		अगर (ret)
			जाओ out_page;

		mutex_lock(&f->sem);
		स_रखो(&ri, 0, माप(ri));

		ri.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
		ri.nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
		ri.totlen = cpu_to_je32(माप(ri));
		ri.hdr_crc = cpu_to_je32(crc32(0, &ri, माप(काष्ठा jffs2_unknown_node)-4));

		ri.ino = cpu_to_je32(f->inocache->ino);
		ri.version = cpu_to_je32(++f->highest_version);
		ri.mode = cpu_to_jemode(inode->i_mode);
		ri.uid = cpu_to_je16(i_uid_पढ़ो(inode));
		ri.gid = cpu_to_je16(i_gid_पढ़ो(inode));
		ri.isize = cpu_to_je32(max((uपूर्णांक32_t)inode->i_size, pageofs));
		ri.aसमय = ri.स_समय = ri.mसमय = cpu_to_je32(JFFS2_NOW());
		ri.offset = cpu_to_je32(inode->i_size);
		ri.dsize = cpu_to_je32(pageofs - inode->i_size);
		ri.csize = cpu_to_je32(0);
		ri.compr = JFFS2_COMPR_ZERO;
		ri.node_crc = cpu_to_je32(crc32(0, &ri, माप(ri)-8));
		ri.data_crc = cpu_to_je32(0);

		fn = jffs2_ग_लिखो_dnode(c, f, &ri, शून्य, 0, ALLOC_NORMAL);

		अगर (IS_ERR(fn)) अणु
			ret = PTR_ERR(fn);
			jffs2_complete_reservation(c);
			mutex_unlock(&f->sem);
			जाओ out_page;
		पूर्ण
		ret = jffs2_add_full_dnode_to_inode(c, f, fn);
		अगर (f->metadata) अणु
			jffs2_mark_node_obsolete(c, f->metadata->raw);
			jffs2_मुक्त_full_dnode(f->metadata);
			f->metadata = शून्य;
		पूर्ण
		अगर (ret) अणु
			jffs2_dbg(1, "Eep. add_full_dnode_to_inode() failed in write_begin, returned %d\n",
				  ret);
			jffs2_mark_node_obsolete(c, fn->raw);
			jffs2_मुक्त_full_dnode(fn);
			jffs2_complete_reservation(c);
			mutex_unlock(&f->sem);
			जाओ out_page;
		पूर्ण
		jffs2_complete_reservation(c);
		inode->i_size = pageofs;
		mutex_unlock(&f->sem);
	पूर्ण

	/*
	 * Read in the page अगर it wasn't alपढ़ोy present. Cannot optimize away
	 * the whole page ग_लिखो हाल until jffs2_ग_लिखो_end can handle the
	 * हाल of a लघु-copy.
	 */
	अगर (!PageUptodate(pg)) अणु
		mutex_lock(&f->sem);
		ret = jffs2_करो_पढ़ोpage_nolock(inode, pg);
		mutex_unlock(&f->sem);
		अगर (ret)
			जाओ out_page;
	पूर्ण
	jffs2_dbg(1, "end write_begin(). pg->flags %lx\n", pg->flags);
	वापस ret;

out_page:
	unlock_page(pg);
	put_page(pg);
	वापस ret;
पूर्ण

अटल पूर्णांक jffs2_ग_लिखो_end(काष्ठा file *filp, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *pg, व्योम *fsdata)
अणु
	/* Actually commit the ग_लिखो from the page cache page we're looking at.
	 * For now, we ग_लिखो the full page out each समय. It sucks, but it's simple
	 */
	काष्ठा inode *inode = mapping->host;
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	काष्ठा jffs2_raw_inode *ri;
	अचिन्हित start = pos & (PAGE_SIZE - 1);
	अचिन्हित end = start + copied;
	अचिन्हित aligned_start = start & ~3;
	पूर्णांक ret = 0;
	uपूर्णांक32_t writtenlen = 0;

	jffs2_dbg(1, "%s(): ino #%lu, page at 0x%lx, range %d-%d, flags %lx\n",
		  __func__, inode->i_ino, pg->index << PAGE_SHIFT,
		  start, end, pg->flags);

	/* We need to aव्योम deadlock with page_cache_पढ़ो() in
	   jffs2_garbage_collect_pass(). So the page must be
	   up to date to prevent page_cache_पढ़ो() from trying
	   to re-lock it. */
	BUG_ON(!PageUptodate(pg));

	अगर (end == PAGE_SIZE) अणु
		/* When writing out the end of a page, ग_लिखो out the
		   _whole_ page. This helps to reduce the number of
		   nodes in files which have many लघु ग_लिखोs, like
		   syslog files. */
		aligned_start = 0;
	पूर्ण

	ri = jffs2_alloc_raw_inode();

	अगर (!ri) अणु
		jffs2_dbg(1, "%s(): Allocation of raw inode failed\n",
			  __func__);
		unlock_page(pg);
		put_page(pg);
		वापस -ENOMEM;
	पूर्ण

	/* Set the fields that the generic jffs2_ग_लिखो_inode_range() code can't find */
	ri->ino = cpu_to_je32(inode->i_ino);
	ri->mode = cpu_to_jemode(inode->i_mode);
	ri->uid = cpu_to_je16(i_uid_पढ़ो(inode));
	ri->gid = cpu_to_je16(i_gid_पढ़ो(inode));
	ri->isize = cpu_to_je32((uपूर्णांक32_t)inode->i_size);
	ri->aसमय = ri->स_समय = ri->mसमय = cpu_to_je32(JFFS2_NOW());

	/* In 2.4, it was alपढ़ोy kmapped by generic_file_ग_लिखो(). Doesn't
	   hurt to करो it again. The alternative is अगरdefs, which are ugly. */
	kmap(pg);

	ret = jffs2_ग_लिखो_inode_range(c, f, ri, page_address(pg) + aligned_start,
				      (pg->index << PAGE_SHIFT) + aligned_start,
				      end - aligned_start, &writtenlen);

	kunmap(pg);

	अगर (ret) अणु
		/* There was an error writing. */
		SetPageError(pg);
	पूर्ण

	/* Adjust writtenlen क्रम the padding we did, so we करोn't confuse our caller */
	writtenlen -= min(writtenlen, (start - aligned_start));

	अगर (writtenlen) अणु
		अगर (inode->i_size < pos + writtenlen) अणु
			inode->i_size = pos + writtenlen;
			inode->i_blocks = (inode->i_size + 511) >> 9;

			inode->i_स_समय = inode->i_mसमय = ITIME(je32_to_cpu(ri->स_समय));
		पूर्ण
	पूर्ण

	jffs2_मुक्त_raw_inode(ri);

	अगर (start+writtenlen < end) अणु
		/* generic_file_ग_लिखो has written more to the page cache than we've
		   actually written to the medium. Mark the page !Uptodate so that
		   it माला_लो reपढ़ो */
		jffs2_dbg(1, "%s(): Not all bytes written. Marking page !uptodate\n",
			__func__);
		SetPageError(pg);
		ClearPageUptodate(pg);
	पूर्ण

	jffs2_dbg(1, "%s() returning %d\n",
		  __func__, writtenlen > 0 ? writtenlen : ret);
	unlock_page(pg);
	put_page(pg);
	वापस writtenlen > 0 ? writtenlen : ret;
पूर्ण
