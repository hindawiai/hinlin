<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* nommu.c: mmu-less memory info files
 *
 * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/mman.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/smp.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/भाग64.h>
#समावेश "internal.h"

/*
 * display a single region to a sequenced file
 */
अटल पूर्णांक nommu_region_show(काष्ठा seq_file *m, काष्ठा vm_region *region)
अणु
	अचिन्हित दीर्घ ino = 0;
	काष्ठा file *file;
	dev_t dev = 0;
	पूर्णांक flags;

	flags = region->vm_flags;
	file = region->vm_file;

	अगर (file) अणु
		काष्ठा inode *inode = file_inode(region->vm_file);
		dev = inode->i_sb->s_dev;
		ino = inode->i_ino;
	पूर्ण

	seq_setwidth(m, 25 + माप(व्योम *) * 6 - 1);
	seq_म_लिखो(m,
		   "%08lx-%08lx %c%c%c%c %08llx %02x:%02x %lu ",
		   region->vm_start,
		   region->vm_end,
		   flags & VM_READ ? 'r' : '-',
		   flags & VM_WRITE ? 'w' : '-',
		   flags & VM_EXEC ? 'x' : '-',
		   flags & VM_MAYSHARE ? flags & VM_SHARED ? 'S' : 's' : 'p',
		   ((loff_t)region->vm_pgoff) << PAGE_SHIFT,
		   MAJOR(dev), MINOR(dev), ino);

	अगर (file) अणु
		seq_pad(m, ' ');
		seq_file_path(m, file, "");
	पूर्ण

	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

/*
 * display a list of all the REGIONs the kernel knows about
 * - nommu kernels have a single flat list
 */
अटल पूर्णांक nommu_region_list_show(काष्ठा seq_file *m, व्योम *_p)
अणु
	काष्ठा rb_node *p = _p;

	वापस nommu_region_show(m, rb_entry(p, काष्ठा vm_region, vm_rb));
पूर्ण

अटल व्योम *nommu_region_list_start(काष्ठा seq_file *m, loff_t *_pos)
अणु
	काष्ठा rb_node *p;
	loff_t pos = *_pos;

	करोwn_पढ़ो(&nommu_region_sem);

	क्रम (p = rb_first(&nommu_region_tree); p; p = rb_next(p))
		अगर (pos-- == 0)
			वापस p;
	वापस शून्य;
पूर्ण

अटल व्योम nommu_region_list_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	up_पढ़ो(&nommu_region_sem);
पूर्ण

अटल व्योम *nommu_region_list_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस rb_next((काष्ठा rb_node *) v);
पूर्ण

अटल स्थिर काष्ठा seq_operations proc_nommu_region_list_seqop = अणु
	.start	= nommu_region_list_start,
	.next	= nommu_region_list_next,
	.stop	= nommu_region_list_stop,
	.show	= nommu_region_list_show
पूर्ण;

अटल पूर्णांक __init proc_nommu_init(व्योम)
अणु
	proc_create_seq("maps", S_IRUGO, शून्य, &proc_nommu_region_list_seqop);
	वापस 0;
पूर्ण

fs_initcall(proc_nommu_init);
