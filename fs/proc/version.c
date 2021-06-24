<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/utsname.h>

अटल पूर्णांक version_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, linux_proc_banner,
		utsname()->sysname,
		utsname()->release,
		utsname()->version);
	वापस 0;
पूर्ण

अटल पूर्णांक __init proc_version_init(व्योम)
अणु
	proc_create_single("version", 0, शून्य, version_proc_show);
	वापस 0;
पूर्ण
fs_initcall(proc_version_init);
