<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  xenfs.c - a fileप्रणाली क्रम passing info between the a करोमुख्य and
 *  the hypervisor.
 *
 * 2008-10-07  Alex Zeffertt    Replaced /proc/xen/xenbus with xenfs fileप्रणाली
 *                              and /proc/xen compatibility mount poपूर्णांक.
 *                              Turned xenfs पूर्णांकo a loadable module.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/magic.h>

#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>

#समावेश "xenfs.h"
#समावेश "../privcmd.h"

#समावेश <यंत्र/xen/hypervisor.h>

MODULE_DESCRIPTION("Xen filesystem");
MODULE_LICENSE("GPL");

अटल sमाप_प्रकार capabilities_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार size, loff_t *off)
अणु
	अक्षर *पंचांगp = "";

	अगर (xen_initial_करोमुख्य())
		पंचांगp = "control_d\n";

	वापस simple_पढ़ो_from_buffer(buf, size, off, पंचांगp, म_माप(पंचांगp));
पूर्ण

अटल स्थिर काष्ठा file_operations capabilities_file_ops = अणु
	.पढ़ो = capabilities_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक xenfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	अटल स्थिर काष्ठा tree_descr xenfs_files[] = अणु
		[2] = अणु "xenbus", &xen_xenbus_fops, S_IRUSR|S_IWUSR पूर्ण,
		अणु "capabilities", &capabilities_file_ops, S_IRUGO पूर्ण,
		अणु "privcmd", &xen_privcmd_fops, S_IRUSR|S_IWUSR पूर्ण,
		अणु""पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा tree_descr xenfs_init_files[] = अणु
		[2] = अणु "xenbus", &xen_xenbus_fops, S_IRUSR|S_IWUSR पूर्ण,
		अणु "capabilities", &capabilities_file_ops, S_IRUGO पूर्ण,
		अणु "privcmd", &xen_privcmd_fops, S_IRUSR|S_IWUSR पूर्ण,
		अणु "xsd_kva", &xsd_kva_file_ops, S_IRUSR|S_IWUSRपूर्ण,
		अणु "xsd_port", &xsd_port_file_ops, S_IRUSR|S_IWUSRपूर्ण,
#अगर_घोषित CONFIG_XEN_SYMS
		अणु "xensyms", &xensyms_ops, S_IRUSRपूर्ण,
#पूर्ण_अगर
		अणु""पूर्ण,
	पूर्ण;

	वापस simple_fill_super(sb, XENFS_SUPER_MAGIC,
			xen_initial_करोमुख्य() ? xenfs_init_files : xenfs_files);
पूर्ण

अटल पूर्णांक xenfs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, xenfs_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations xenfs_context_ops = अणु
	.get_tree	= xenfs_get_tree,
पूर्ण;

अटल पूर्णांक xenfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &xenfs_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type xenfs_type = अणु
	.owner =	THIS_MODULE,
	.name =		"xenfs",
	.init_fs_context = xenfs_init_fs_context,
	.समाप्त_sb =	समाप्त_litter_super,
पूर्ण;
MODULE_ALIAS_FS("xenfs");

अटल पूर्णांक __init xenfs_init(व्योम)
अणु
	अगर (xen_करोमुख्य())
		वापस रेजिस्टर_fileप्रणाली(&xenfs_type);

	वापस 0;
पूर्ण

अटल व्योम __निकास xenfs_निकास(व्योम)
अणु
	अगर (xen_करोमुख्य())
		unरेजिस्टर_fileप्रणाली(&xenfs_type);
पूर्ण

module_init(xenfs_init);
module_निकास(xenfs_निकास);

