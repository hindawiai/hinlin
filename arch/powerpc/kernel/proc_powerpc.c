<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001 Mike Corrigan & Dave Engebretsen IBM Corporation
 */

#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/rtas.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/prom.h>

#अगर_घोषित CONFIG_PPC64

अटल loff_t page_map_seek(काष्ठा file *file, loff_t off, पूर्णांक whence)
अणु
	वापस fixed_size_llseek(file, off, whence, PAGE_SIZE);
पूर्ण

अटल sमाप_प्रकार page_map_पढ़ो( काष्ठा file *file, अक्षर __user *buf, माप_प्रकार nbytes,
			      loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(buf, nbytes, ppos,
			PDE_DATA(file_inode(file)), PAGE_SIZE);
पूर्ण

अटल पूर्णांक page_map_mmap( काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma )
अणु
	अगर ((vma->vm_end - vma->vm_start) > PAGE_SIZE)
		वापस -EINVAL;

	remap_pfn_range(vma, vma->vm_start,
			__pa(PDE_DATA(file_inode(file))) >> PAGE_SHIFT,
			PAGE_SIZE, vma->vm_page_prot);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proc_ops page_map_proc_ops = अणु
	.proc_lseek	= page_map_seek,
	.proc_पढ़ो	= page_map_पढ़ो,
	.proc_mmap	= page_map_mmap,
पूर्ण;


अटल पूर्णांक __init proc_ppc64_init(व्योम)
अणु
	काष्ठा proc_dir_entry *pde;

	pde = proc_create_data("powerpc/systemcfg", S_IFREG | 0444, शून्य,
			       &page_map_proc_ops, vdso_data);
	अगर (!pde)
		वापस 1;
	proc_set_size(pde, PAGE_SIZE);

	वापस 0;
पूर्ण
__initcall(proc_ppc64_init);

#पूर्ण_अगर /* CONFIG_PPC64 */

/*
 * Create the ppc64 and ppc64/rtas directories early. This allows us to
 * assume that they have been previously created in drivers.
 */
अटल पूर्णांक __init proc_ppc64_create(व्योम)
अणु
	काष्ठा proc_dir_entry *root;

	root = proc_सूची_गढ़ो("powerpc", शून्य);
	अगर (!root)
		वापस 1;

#अगर_घोषित CONFIG_PPC64
	अगर (!proc_symlink("ppc64", शून्य, "powerpc"))
		pr_err("Failed to create link /proc/ppc64 -> /proc/powerpc\n");
#पूर्ण_अगर

	अगर (!of_find_node_by_path("/rtas"))
		वापस 0;

	अगर (!proc_सूची_गढ़ो("rtas", root))
		वापस 1;

	अगर (!proc_symlink("rtas", शून्य, "powerpc/rtas"))
		वापस 1;

	वापस 0;
पूर्ण
core_initcall(proc_ppc64_create);
