<शैली गुरु>
/*
 * debugfs ops क्रम process ASIDs
 *
 *  Copyright (C) 2000, 2001  Paolo Alberelli
 *  Copyright (C) 2003 - 2008  Paul Mundt
 *  Copyright (C) 2003, 2004  Riअक्षरd Curnow
 *
 * Provides a debugfs file that lists out the ASIDs currently associated
 * with the processes.
 *
 * In the SH-5 हाल, अगर the DM.PC रेजिस्टर is examined through the debug
 * link, this shows ASID + PC. To make use of this, the PID->ASID
 * relationship needs to be known. This is primarily क्रम debugging.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmu_context.h>

अटल पूर्णांक asids_debugfs_show(काष्ठा seq_file *file, व्योम *iter)
अणु
	काष्ठा task_काष्ठा *p;

	पढ़ो_lock(&tasklist_lock);

	क्रम_each_process(p) अणु
		पूर्णांक pid = p->pid;

		अगर (unlikely(!pid))
			जारी;

		अगर (p->mm)
			seq_म_लिखो(file, "%5d : %04lx\n", pid,
				   cpu_asid(smp_processor_id(), p->mm));
	पूर्ण

	पढ़ो_unlock(&tasklist_lock);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(asids_debugfs);

अटल पूर्णांक __init asids_debugfs_init(व्योम)
अणु
	debugfs_create_file("asids", S_IRUSR, arch_debugfs_dir, शून्य,
			    &asids_debugfs_fops);
	वापस 0;
पूर्ण
device_initcall(asids_debugfs_init);
