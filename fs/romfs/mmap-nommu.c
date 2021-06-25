<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* NOMMU mmap support क्रम RomFS on MTD devices
 *
 * Copyright तऊ 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/mm.h>
#समावेश <linux/mtd/super.h>
#समावेश "internal.h"

/*
 * try to determine where a shared mapping can be made
 * - only supported क्रम NOMMU at the moment (MMU can't doesn't copy निजी
 *   mappings)
 * - attempts to map through to the underlying MTD device
 */
अटल अचिन्हित दीर्घ romfs_get_unmapped_area(काष्ठा file *file,
					     अचिन्हित दीर्घ addr,
					     अचिन्हित दीर्घ len,
					     अचिन्हित दीर्घ pgoff,
					     अचिन्हित दीर्घ flags)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा mtd_info *mtd = inode->i_sb->s_mtd;
	अचिन्हित दीर्घ isize, offset, maxpages, lpages;
	पूर्णांक ret;

	अगर (!mtd)
		वापस (अचिन्हित दीर्घ) -ENOSYS;

	/* the mapping mustn't extend beyond the खातापूर्ण */
	lpages = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	isize = i_size_पढ़ो(inode);
	offset = pgoff << PAGE_SHIFT;

	maxpages = (isize + PAGE_SIZE - 1) >> PAGE_SHIFT;
	अगर ((pgoff >= maxpages) || (maxpages - pgoff < lpages))
		वापस (अचिन्हित दीर्घ) -EINVAL;

	अगर (addr != 0)
		वापस (अचिन्हित दीर्घ) -EINVAL;

	अगर (len > mtd->size || pgoff >= (mtd->size >> PAGE_SHIFT))
		वापस (अचिन्हित दीर्घ) -EINVAL;

	offset += ROMFS_I(inode)->i_dataoffset;
	अगर (offset >= mtd->size)
		वापस (अचिन्हित दीर्घ) -EINVAL;
	/* the mapping mustn't extend beyond the खातापूर्ण */
	अगर ((offset + len) > mtd->size)
		len = mtd->size - offset;

	ret = mtd_get_unmapped_area(mtd, len, offset, flags);
	अगर (ret == -EOPNOTSUPP)
		ret = -ENOSYS;
	वापस (अचिन्हित दीर्घ) ret;
पूर्ण

/*
 * permit a R/O mapping to be made directly through onto an MTD device अगर
 * possible
 */
अटल पूर्णांक romfs_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma->vm_flags & (VM_SHARED | VM_MAYSHARE) ? 0 : -ENOSYS;
पूर्ण

अटल अचिन्हित romfs_mmap_capabilities(काष्ठा file *file)
अणु
	काष्ठा mtd_info *mtd = file_inode(file)->i_sb->s_mtd;

	अगर (!mtd)
		वापस NOMMU_MAP_COPY;
	वापस mtd_mmap_capabilities(mtd);
पूर्ण

स्थिर काष्ठा file_operations romfs_ro_fops = अणु
	.llseek			= generic_file_llseek,
	.पढ़ो_iter		= generic_file_पढ़ो_iter,
	.splice_पढ़ो		= generic_file_splice_पढ़ो,
	.mmap			= romfs_mmap,
	.get_unmapped_area	= romfs_get_unmapped_area,
	.mmap_capabilities	= romfs_mmap_capabilities,
पूर्ण;
