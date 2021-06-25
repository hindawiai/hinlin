<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Provide kernel headers useful to build tracing programs
 * such as क्रम running eBPF tracing tools.
 *
 * (Borrowed code from kernel/configs.c)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/kobject.h>
#समावेश <linux/init.h>

/*
 * Define kernel_headers_data and kernel_headers_data_end, within which the
 * compressed kernel headers are stored. The file is first compressed with xz.
 */

यंत्र (
"	.pushsection .rodata, \"a\"		\n"
"	.global kernel_headers_data		\n"
"kernel_headers_data:				\n"
"	.incbin \"kernel/kheaders_data.tar.xz\"	\n"
"	.global kernel_headers_data_end		\n"
"kernel_headers_data_end:			\n"
"	.popsection				\n"
);

बाह्य अक्षर kernel_headers_data;
बाह्य अक्षर kernel_headers_data_end;

अटल sमाप_प्रकार
ikheaders_पढ़ो(काष्ठा file *file,  काष्ठा kobject *kobj,
	       काष्ठा bin_attribute *bin_attr,
	       अक्षर *buf, loff_t off, माप_प्रकार len)
अणु
	स_नकल(buf, &kernel_headers_data + off, len);
	वापस len;
पूर्ण

अटल काष्ठा bin_attribute kheaders_attr __ro_after_init = अणु
	.attr = अणु
		.name = "kheaders.tar.xz",
		.mode = 0444,
	पूर्ण,
	.पढ़ो = &ikheaders_पढ़ो,
पूर्ण;

अटल पूर्णांक __init ikheaders_init(व्योम)
अणु
	kheaders_attr.size = (&kernel_headers_data_end -
			      &kernel_headers_data);
	वापस sysfs_create_bin_file(kernel_kobj, &kheaders_attr);
पूर्ण

अटल व्योम __निकास ikheaders_cleanup(व्योम)
अणु
	sysfs_हटाओ_bin_file(kernel_kobj, &kheaders_attr);
पूर्ण

module_init(ikheaders_init);
module_निकास(ikheaders_cleanup);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Joel Fernandes");
MODULE_DESCRIPTION("Echo the kernel header artifacts used to build the kernel");
