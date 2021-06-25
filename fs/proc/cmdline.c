<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>

अटल पूर्णांक cmdline_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_माला_दो(m, saved_command_line);
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल पूर्णांक __init proc_cmdline_init(व्योम)
अणु
	proc_create_single("cmdline", 0, शून्य, cmdline_proc_show);
	वापस 0;
पूर्ण
fs_initcall(proc_cmdline_init);
