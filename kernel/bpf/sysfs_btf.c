<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Provide kernel BTF inक्रमmation क्रम पूर्णांकrospection and use by eBPF tools.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/kobject.h>
#समावेश <linux/init.h>
#समावेश <linux/sysfs.h>

/* See scripts/link-vmlinux.sh, gen_btf() func क्रम details */
बाह्य अक्षर __weak __start_BTF[];
बाह्य अक्षर __weak __stop_BTF[];

अटल sमाप_प्रकार
btf_vmlinux_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
		 काष्ठा bin_attribute *bin_attr,
		 अक्षर *buf, loff_t off, माप_प्रकार len)
अणु
	स_नकल(buf, __start_BTF + off, len);
	वापस len;
पूर्ण

अटल काष्ठा bin_attribute bin_attr_btf_vmlinux __ro_after_init = अणु
	.attr = अणु .name = "vmlinux", .mode = 0444, पूर्ण,
	.पढ़ो = btf_vmlinux_पढ़ो,
पूर्ण;

काष्ठा kobject *btf_kobj;

अटल पूर्णांक __init btf_vmlinux_init(व्योम)
अणु
	bin_attr_btf_vmlinux.size = __stop_BTF - __start_BTF;

	अगर (!__start_BTF || bin_attr_btf_vmlinux.size == 0)
		वापस 0;

	btf_kobj = kobject_create_and_add("btf", kernel_kobj);
	अगर (!btf_kobj)
		वापस -ENOMEM;

	वापस sysfs_create_bin_file(btf_kobj, &bin_attr_btf_vmlinux);
पूर्ण

subsys_initcall(btf_vmlinux_init);
