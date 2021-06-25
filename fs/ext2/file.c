<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext2/file.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/file.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  ext2 fs regular file handling primitives
 *
 *  64-bit file support on 64-bit platक्रमms by Jakub Jelinek
 * 	(jj@sunsite.ms.mff.cuni.cz)
 */

#समावेश <linux/समय.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/dax.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/iomap.h>
#समावेश <linux/uपन.स>
#समावेश "ext2.h"
#समावेश "xattr.h"
#समावेश "acl.h"

#अगर_घोषित CONFIG_FS_DAX
अटल sमाप_प्रकार ext2_dax_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा inode *inode = iocb->ki_filp->f_mapping->host;
	sमाप_प्रकार ret;

	अगर (!iov_iter_count(to))
		वापस 0; /* skip aसमय */

	inode_lock_shared(inode);
	ret = dax_iomap_rw(iocb, to, &ext2_iomap_ops);
	inode_unlock_shared(inode);

	file_accessed(iocb->ki_filp);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ext2_dax_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file->f_mapping->host;
	sमाप_प्रकार ret;

	inode_lock(inode);
	ret = generic_ग_लिखो_checks(iocb, from);
	अगर (ret <= 0)
		जाओ out_unlock;
	ret = file_हटाओ_privs(file);
	अगर (ret)
		जाओ out_unlock;
	ret = file_update_समय(file);
	अगर (ret)
		जाओ out_unlock;

	ret = dax_iomap_rw(iocb, from, &ext2_iomap_ops);
	अगर (ret > 0 && iocb->ki_pos > i_size_पढ़ो(inode)) अणु
		i_size_ग_लिखो(inode, iocb->ki_pos);
		mark_inode_dirty(inode);
	पूर्ण

out_unlock:
	inode_unlock(inode);
	अगर (ret > 0)
		ret = generic_ग_लिखो_sync(iocb, ret);
	वापस ret;
पूर्ण

/*
 * The lock ordering क्रम ext2 DAX fault paths is:
 *
 * mmap_lock (MM)
 *   sb_start_pagefault (vfs, मुक्तze)
 *     ext2_inode_info->dax_sem
 *       address_space->i_mmap_rwsem or page_lock (mutually exclusive in DAX)
 *         ext2_inode_info->truncate_mutex
 *
 * The शेष page_lock and i_size verअगरication करोne by non-DAX fault paths
 * is sufficient because ext2 करोesn't support hole punching.
 */
अटल vm_fault_t ext2_dax_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	काष्ठा ext2_inode_info *ei = EXT2_I(inode);
	vm_fault_t ret;
	bool ग_लिखो = (vmf->flags & FAULT_FLAG_WRITE) &&
		(vmf->vma->vm_flags & VM_SHARED);

	अगर (ग_लिखो) अणु
		sb_start_pagefault(inode->i_sb);
		file_update_समय(vmf->vma->vm_file);
	पूर्ण
	करोwn_पढ़ो(&ei->dax_sem);

	ret = dax_iomap_fault(vmf, PE_SIZE_PTE, शून्य, शून्य, &ext2_iomap_ops);

	up_पढ़ो(&ei->dax_sem);
	अगर (ग_लिखो)
		sb_end_pagefault(inode->i_sb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा ext2_dax_vm_ops = अणु
	.fault		= ext2_dax_fault,
	/*
	 * .huge_fault is not supported क्रम DAX because allocation in ext2
	 * cannot be reliably aligned to huge page sizes and so pmd faults
	 * will always fail and fail back to regular faults.
	 */
	.page_mkग_लिखो	= ext2_dax_fault,
	.pfn_mkग_लिखो	= ext2_dax_fault,
पूर्ण;

अटल पूर्णांक ext2_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!IS_DAX(file_inode(file)))
		वापस generic_file_mmap(file, vma);

	file_accessed(file);
	vma->vm_ops = &ext2_dax_vm_ops;
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ext2_file_mmap	generic_file_mmap
#पूर्ण_अगर

/*
 * Called when filp is released. This happens when all file descriptors
 * क्रम a single काष्ठा file are बंदd. Note that dअगरferent खोलो() calls
 * क्रम the same file yield dअगरferent काष्ठा file काष्ठाures.
 */
अटल पूर्णांक ext2_release_file (काष्ठा inode * inode, काष्ठा file * filp)
अणु
	अगर (filp->f_mode & FMODE_WRITE) अणु
		mutex_lock(&EXT2_I(inode)->truncate_mutex);
		ext2_discard_reservation(inode);
		mutex_unlock(&EXT2_I(inode)->truncate_mutex);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ext2_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	पूर्णांक ret;
	काष्ठा super_block *sb = file->f_mapping->host->i_sb;

	ret = generic_file_fsync(file, start, end, datasync);
	अगर (ret == -EIO)
		/* We करोn't really know where the IO error happened... */
		ext2_error(sb, __func__,
			   "detected IO error when writing metadata buffers");
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ext2_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
#अगर_घोषित CONFIG_FS_DAX
	अगर (IS_DAX(iocb->ki_filp->f_mapping->host))
		वापस ext2_dax_पढ़ो_iter(iocb, to);
#पूर्ण_अगर
	वापस generic_file_पढ़ो_iter(iocb, to);
पूर्ण

अटल sमाप_प्रकार ext2_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
#अगर_घोषित CONFIG_FS_DAX
	अगर (IS_DAX(iocb->ki_filp->f_mapping->host))
		वापस ext2_dax_ग_लिखो_iter(iocb, from);
#पूर्ण_अगर
	वापस generic_file_ग_लिखो_iter(iocb, from);
पूर्ण

स्थिर काष्ठा file_operations ext2_file_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= ext2_file_पढ़ो_iter,
	.ग_लिखो_iter	= ext2_file_ग_लिखो_iter,
	.unlocked_ioctl = ext2_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= ext2_compat_ioctl,
#पूर्ण_अगर
	.mmap		= ext2_file_mmap,
	.खोलो		= dquot_file_खोलो,
	.release	= ext2_release_file,
	.fsync		= ext2_fsync,
	.get_unmapped_area = thp_get_unmapped_area,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
पूर्ण;

स्थिर काष्ठा inode_operations ext2_file_inode_operations = अणु
	.listxattr	= ext2_listxattr,
	.getattr	= ext2_getattr,
	.setattr	= ext2_setattr,
	.get_acl	= ext2_get_acl,
	.set_acl	= ext2_set_acl,
	.fiemap		= ext2_fiemap,
	.fileattr_get	= ext2_fileattr_get,
	.fileattr_set	= ext2_fileattr_set,
पूर्ण;
