<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/समय.स>

अटल पूर्णांक loadavg_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ avnrun[3];

	get_avenrun(avnrun, FIXED_1/200, 0);

	seq_म_लिखो(m, "%lu.%02lu %lu.%02lu %lu.%02lu %ld/%d %d\n",
		LOAD_INT(avnrun[0]), LOAD_FRAC(avnrun[0]),
		LOAD_INT(avnrun[1]), LOAD_FRAC(avnrun[1]),
		LOAD_INT(avnrun[2]), LOAD_FRAC(avnrun[2]),
		nr_running(), nr_thपढ़ोs,
		idr_get_cursor(&task_active_pid_ns(current)->idr) - 1);
	वापस 0;
पूर्ण

अटल पूर्णांक __init proc_loadavg_init(व्योम)
अणु
	proc_create_single("loadavg", 0, शून्य, loadavg_proc_show);
	वापस 0;
पूर्ण
fs_initcall(proc_loadavg_init);
