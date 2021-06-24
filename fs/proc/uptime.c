<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/समय.स>
#समावेश <linux/समय_namespace.h>
#समावेश <linux/kernel_स्थिति.स>

अटल पूर्णांक upसमय_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा बारpec64 upसमय;
	काष्ठा बारpec64 idle;
	u64 nsec;
	u32 rem;
	पूर्णांक i;

	nsec = 0;
	क्रम_each_possible_cpu(i)
		nsec += (__क्रमce u64) kcpustat_cpu(i).cpustat[CPUTIME_IDLE];

	kसमय_get_bootसमय_प्रकारs64(&upसमय);
	समयns_add_bootसमय(&upसमय);

	idle.tv_sec = भाग_u64_rem(nsec, NSEC_PER_SEC, &rem);
	idle.tv_nsec = rem;
	seq_म_लिखो(m, "%lu.%02lu %lu.%02lu\n",
			(अचिन्हित दीर्घ) upसमय.tv_sec,
			(upसमय.tv_nsec / (NSEC_PER_SEC / 100)),
			(अचिन्हित दीर्घ) idle.tv_sec,
			(idle.tv_nsec / (NSEC_PER_SEC / 100)));
	वापस 0;
पूर्ण

अटल पूर्णांक __init proc_upसमय_init(व्योम)
अणु
	proc_create_single("uptime", 0, शून्य, upसमय_proc_show);
	वापस 0;
पूर्ण
fs_initcall(proc_upसमय_init);
