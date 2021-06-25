<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * kernel/configs.c
 * Echo the kernel .config file used to build the kernel
 *
 * Copyright (C) 2002 Khalid Aziz <khalid_aziz@hp.com>
 * Copyright (C) 2002 Randy Dunlap <rdunlap@xenoसमय.net>
 * Copyright (C) 2002 Al Stone <ahs3@fc.hp.com>
 * Copyright (C) 2002 Hewlett-Packard Company
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/uaccess.h>

/*
 * "IKCFG_ST" and "IKCFG_ED" are used to extract the config data from
 * a binary kernel image or a module. See scripts/extract-ikconfig.
 */
यंत्र (
"	.pushsection .rodata, \"a\"		\n"
"	.ascii \"IKCFG_ST\"			\n"
"	.global kernel_config_data		\n"
"kernel_config_data:				\n"
"	.incbin \"kernel/config_data.gz\"	\n"
"	.global kernel_config_data_end		\n"
"kernel_config_data_end:			\n"
"	.ascii \"IKCFG_ED\"			\n"
"	.popsection				\n"
);

#अगर_घोषित CONFIG_IKCONFIG_PROC

बाह्य अक्षर kernel_config_data;
बाह्य अक्षर kernel_config_data_end;

अटल sमाप_प्रकार
ikconfig_पढ़ो_current(काष्ठा file *file, अक्षर __user *buf,
		      माप_प्रकार len, loff_t * offset)
अणु
	वापस simple_पढ़ो_from_buffer(buf, len, offset,
				       &kernel_config_data,
				       &kernel_config_data_end -
				       &kernel_config_data);
पूर्ण

अटल स्थिर काष्ठा proc_ops config_gz_proc_ops = अणु
	.proc_पढ़ो	= ikconfig_पढ़ो_current,
	.proc_lseek	= शेष_llseek,
पूर्ण;

अटल पूर्णांक __init ikconfig_init(व्योम)
अणु
	काष्ठा proc_dir_entry *entry;

	/* create the current config file */
	entry = proc_create("config.gz", S_IFREG | S_IRUGO, शून्य,
			    &config_gz_proc_ops);
	अगर (!entry)
		वापस -ENOMEM;

	proc_set_size(entry, &kernel_config_data_end - &kernel_config_data);

	वापस 0;
पूर्ण

अटल व्योम __निकास ikconfig_cleanup(व्योम)
अणु
	हटाओ_proc_entry("config.gz", शून्य);
पूर्ण

module_init(ikconfig_init);
module_निकास(ikconfig_cleanup);

#पूर्ण_अगर /* CONFIG_IKCONFIG_PROC */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Randy Dunlap");
MODULE_DESCRIPTION("Echo the kernel .config file used to build the kernel");
