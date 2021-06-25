<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mm/fadvise.c
 *
 * Copyright (C) 2002, Linus Torvalds
 *
 * 11Jan2003	Andrew Morton
 *		Initial version.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/fadvise.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/swap.h>

#समावेश <यंत्र/unistd.h>

#समावेश "internal.h"

/*
 * POSIX_FADV_WILLNEED could set PG_Referenced, and POSIX_FADV_NOREUSE could
 * deactivate the pages and clear PG_Referenced.
 */

पूर्णांक generic_fadvise(काष्ठा file *file, loff_t offset, loff_t len, पूर्णांक advice)
अणु
	काष्ठा inode *inode;
	काष्ठा address_space *mapping;
	काष्ठा backing_dev_info *bdi;
	loff_t endbyte;			/* inclusive */
	pgoff_t start_index;
	pgoff_t end_index;
	अचिन्हित दीर्घ nrpages;

	inode = file_inode(file);
	अगर (S_ISFIFO(inode->i_mode))
		वापस -ESPIPE;

	mapping = file->f_mapping;
	अगर (!mapping || len < 0)
		वापस -EINVAL;

	bdi = inode_to_bdi(mapping->host);

	अगर (IS_DAX(inode) || (bdi == &noop_backing_dev_info)) अणु
		चयन (advice) अणु
		हाल POSIX_FADV_NORMAL:
		हाल POSIX_FADV_RANDOM:
		हाल POSIX_FADV_SEQUENTIAL:
		हाल POSIX_FADV_WILLNEED:
		हाल POSIX_FADV_NOREUSE:
		हाल POSIX_FADV_DONTNEED:
			/* no bad वापस value, but ignore advice */
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * Careful about overflows. Len == 0 means "as much as possible".  Use
	 * अचिन्हित math because चिन्हित overflows are undefined and UBSan
	 * complains.
	 */
	endbyte = (u64)offset + (u64)len;
	अगर (!len || endbyte < len)
		endbyte = -1;
	अन्यथा
		endbyte--;		/* inclusive */

	चयन (advice) अणु
	हाल POSIX_FADV_NORMAL:
		file->f_ra.ra_pages = bdi->ra_pages;
		spin_lock(&file->f_lock);
		file->f_mode &= ~FMODE_RANDOM;
		spin_unlock(&file->f_lock);
		अवरोध;
	हाल POSIX_FADV_RANDOM:
		spin_lock(&file->f_lock);
		file->f_mode |= FMODE_RANDOM;
		spin_unlock(&file->f_lock);
		अवरोध;
	हाल POSIX_FADV_SEQUENTIAL:
		file->f_ra.ra_pages = bdi->ra_pages * 2;
		spin_lock(&file->f_lock);
		file->f_mode &= ~FMODE_RANDOM;
		spin_unlock(&file->f_lock);
		अवरोध;
	हाल POSIX_FADV_WILLNEED:
		/* First and last PARTIAL page! */
		start_index = offset >> PAGE_SHIFT;
		end_index = endbyte >> PAGE_SHIFT;

		/* Careful about overflow on the "+1" */
		nrpages = end_index - start_index + 1;
		अगर (!nrpages)
			nrpages = ~0UL;

		क्रमce_page_cache_पढ़ोahead(mapping, file, start_index, nrpages);
		अवरोध;
	हाल POSIX_FADV_NOREUSE:
		अवरोध;
	हाल POSIX_FADV_DONTNEED:
		अगर (!inode_ग_लिखो_congested(mapping->host))
			__filemap_fdataग_लिखो_range(mapping, offset, endbyte,
						   WB_SYNC_NONE);

		/*
		 * First and last FULL page! Partial pages are deliberately
		 * preserved on the expectation that it is better to preserve
		 * needed memory than to discard unneeded memory.
		 */
		start_index = (offset+(PAGE_SIZE-1)) >> PAGE_SHIFT;
		end_index = (endbyte >> PAGE_SHIFT);
		/*
		 * The page at end_index will be inclusively discarded according
		 * by invalidate_mapping_pages(), so subtracting 1 from
		 * end_index means we will skip the last page.  But अगर endbyte
		 * is page aligned or is at the end of file, we should not skip
		 * that page - discarding the last page is safe enough.
		 */
		अगर ((endbyte & ~PAGE_MASK) != ~PAGE_MASK &&
				endbyte != inode->i_size - 1) अणु
			/* First page is tricky as 0 - 1 = -1, but pgoff_t
			 * is अचिन्हित, so the end_index >= start_index
			 * check below would be true and we'll discard the whole
			 * file cache which is not what was asked.
			 */
			अगर (end_index == 0)
				अवरोध;

			end_index--;
		पूर्ण

		अगर (end_index >= start_index) अणु
			अचिन्हित दीर्घ nr_pagevec = 0;

			/*
			 * It's common to FADV_DONTNEED right after
			 * the पढ़ो or ग_लिखो that instantiates the
			 * pages, in which हाल there will be some
			 * sitting on the local LRU cache. Try to
			 * aव्योम the expensive remote drain and the
			 * second cache tree walk below by flushing
			 * them out right away.
			 */
			lru_add_drain();

			invalidate_mapping_pagevec(mapping,
						start_index, end_index,
						&nr_pagevec);

			/*
			 * If fewer pages were invalidated than expected then
			 * it is possible that some of the pages were on
			 * a per-cpu pagevec क्रम a remote CPU. Drain all
			 * pagevecs and try again.
			 */
			अगर (nr_pagevec) अणु
				lru_add_drain_all();
				invalidate_mapping_pages(mapping, start_index,
						end_index);
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(generic_fadvise);

पूर्णांक vfs_fadvise(काष्ठा file *file, loff_t offset, loff_t len, पूर्णांक advice)
अणु
	अगर (file->f_op->fadvise)
		वापस file->f_op->fadvise(file, offset, len, advice);

	वापस generic_fadvise(file, offset, len, advice);
पूर्ण
EXPORT_SYMBOL(vfs_fadvise);

#अगर_घोषित CONFIG_ADVISE_SYSCALLS

पूर्णांक ksys_fadvise64_64(पूर्णांक fd, loff_t offset, loff_t len, पूर्णांक advice)
अणु
	काष्ठा fd f = fdget(fd);
	पूर्णांक ret;

	अगर (!f.file)
		वापस -EBADF;

	ret = vfs_fadvise(f.file, offset, len, advice);

	fdput(f);
	वापस ret;
पूर्ण

SYSCALL_DEFINE4(fadvise64_64, पूर्णांक, fd, loff_t, offset, loff_t, len, पूर्णांक, advice)
अणु
	वापस ksys_fadvise64_64(fd, offset, len, advice);
पूर्ण

#अगर_घोषित __ARCH_WANT_SYS_FADVISE64

SYSCALL_DEFINE4(fadvise64, पूर्णांक, fd, loff_t, offset, माप_प्रकार, len, पूर्णांक, advice)
अणु
	वापस ksys_fadvise64_64(fd, offset, len, advice);
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर
