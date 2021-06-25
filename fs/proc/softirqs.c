<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>

/*
 * /proc/softirqs  ... display the number of softirqs
 */
अटल पूर्णांक show_softirqs(काष्ठा seq_file *p, व्योम *v)
अणु
	पूर्णांक i, j;

	seq_माला_दो(p, "                    ");
	क्रम_each_possible_cpu(i)
		seq_म_लिखो(p, "CPU%-8d", i);
	seq_अ_दो(p, '\n');

	क्रम (i = 0; i < NR_SOFTIRQS; i++) अणु
		seq_म_लिखो(p, "%12s:", softirq_to_name[i]);
		क्रम_each_possible_cpu(j)
			seq_म_लिखो(p, " %10u", kstat_softirqs_cpu(i, j));
		seq_अ_दो(p, '\n');
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init proc_softirqs_init(व्योम)
अणु
	proc_create_single("softirqs", 0, शून्य, show_softirqs);
	वापस 0;
पूर्ण
fs_initcall(proc_softirqs_init);
