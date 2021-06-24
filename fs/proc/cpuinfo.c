<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/cpufreq.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>

__weak व्योम arch_freq_prepare_all(व्योम)
अणु
पूर्ण

बाह्य स्थिर काष्ठा seq_operations cpuinfo_op;
अटल पूर्णांक cpuinfo_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	arch_freq_prepare_all();
	वापस seq_खोलो(file, &cpuinfo_op);
पूर्ण

अटल स्थिर काष्ठा proc_ops cpuinfo_proc_ops = अणु
	.proc_flags	= PROC_ENTRY_PERMANENT,
	.proc_खोलो	= cpuinfo_खोलो,
	.proc_पढ़ो_iter	= seq_पढ़ो_iter,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release,
पूर्ण;

अटल पूर्णांक __init proc_cpuinfo_init(व्योम)
अणु
	proc_create("cpuinfo", 0, शून्य, &cpuinfo_proc_ops);
	वापस 0;
पूर्ण
fs_initcall(proc_cpuinfo_init);
