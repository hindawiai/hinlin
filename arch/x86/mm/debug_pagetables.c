<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/debugfs.h>
#समावेश <linux/efi.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pgtable.h>

अटल पूर्णांक ptdump_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ptdump_walk_pgd_level_debugfs(m, &init_mm, false);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ptdump);

अटल पूर्णांक ptdump_curknl_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अगर (current->mm->pgd)
		ptdump_walk_pgd_level_debugfs(m, current->mm, false);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ptdump_curknl);

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
अटल पूर्णांक ptdump_curusr_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अगर (current->mm->pgd)
		ptdump_walk_pgd_level_debugfs(m, current->mm, true);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ptdump_curusr);
#पूर्ण_अगर

#अगर defined(CONFIG_EFI) && defined(CONFIG_X86_64)
अटल पूर्णांक ptdump_efi_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अगर (efi_mm.pgd)
		ptdump_walk_pgd_level_debugfs(m, &efi_mm, false);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ptdump_efi);
#पूर्ण_अगर

अटल काष्ठा dentry *dir;

अटल पूर्णांक __init pt_dump_debug_init(व्योम)
अणु
	dir = debugfs_create_dir("page_tables", शून्य);

	debugfs_create_file("kernel", 0400, dir, शून्य, &ptdump_fops);
	debugfs_create_file("current_kernel", 0400, dir, शून्य,
			    &ptdump_curknl_fops);

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
	debugfs_create_file("current_user", 0400, dir, शून्य,
			    &ptdump_curusr_fops);
#पूर्ण_अगर
#अगर defined(CONFIG_EFI) && defined(CONFIG_X86_64)
	debugfs_create_file("efi", 0400, dir, शून्य, &ptdump_efi_fops);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __निकास pt_dump_debug_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(dir);
पूर्ण

module_init(pt_dump_debug_init);
module_निकास(pt_dump_debug_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arjan van de Ven <arjan@linux.intel.com>");
MODULE_DESCRIPTION("Kernel debugging helper that dumps pagetables");
