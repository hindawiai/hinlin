<शैली गुरु>
/* file-mmu.c: ramfs MMU-based file operations
 *
 * Resizable simple ram fileप्रणाली क्रम Linux.
 *
 * Copyright (C) 2000 Linus Torvalds.
 *               2000 Transmeta Corp.
 *
 * Usage limits added by David Gibson, Linuxcare Australia.
 * This file is released under the GPL.
 */

/*
 * NOTE! This fileप्रणाली is probably most useful
 * not as a real fileप्रणाली, but as an example of
 * how भव fileप्रणालीs can be written.
 *
 * It करोesn't get much simpler than this. Consider
 * that this file implements the full semantics of
 * a POSIX-compliant पढ़ो-ग_लिखो fileप्रणाली.
 *
 * Note in particular how the fileप्रणाली करोes not
 * need to implement any data काष्ठाures of its own
 * to keep track of the भव data: using the VFS
 * caches is sufficient.
 */

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/ramfs.h>
#समावेश <linux/sched.h>

#समावेश "internal.h"

अटल अचिन्हित दीर्घ ramfs_mmu_get_unmapped_area(काष्ठा file *file,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
		अचिन्हित दीर्घ flags)
अणु
	वापस current->mm->get_unmapped_area(file, addr, len, pgoff, flags);
पूर्ण

स्थिर काष्ठा file_operations ramfs_file_operations = अणु
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.mmap		= generic_file_mmap,
	.fsync		= noop_fsync,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.llseek		= generic_file_llseek,
	.get_unmapped_area	= ramfs_mmu_get_unmapped_area,
पूर्ण;

स्थिर काष्ठा inode_operations ramfs_file_inode_operations = अणु
	.setattr	= simple_setattr,
	.getattr	= simple_getattr,
पूर्ण;
