<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Data gathering module क्रम Linux-VM Monitor Stream, Stage 1.
 * Collects misc. OS related data (CPU utilization, running processes).
 *
 * Copyright IBM Corp. 2003, 2006
 *
 * Author: Gerald Schaefer <gerald.schaefer@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT	"appldata"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <यंत्र/appldata.h>
#समावेश <यंत्र/smp.h>

#समावेश "appldata.h"

/*
 * OS data
 *
 * This is accessed as binary data by z/VM. If changes to it can't be aव्योमed,
 * the काष्ठाure version (product ID, see appldata_base.c) needs to be changed
 * as well and all करोcumentation and z/VM applications using it must be
 * updated.
 */
काष्ठा appldata_os_per_cpu अणु
	u32 per_cpu_user;	/* समयr ticks spent in user mode   */
	u32 per_cpu_nice;	/* ... spent with modअगरied priority */
	u32 per_cpu_प्रणाली;	/* ... spent in kernel mode         */
	u32 per_cpu_idle;	/* ... spent in idle mode           */

	/* New in 2.6 */
	u32 per_cpu_irq;	/* ... spent in पूर्णांकerrupts          */
	u32 per_cpu_softirq;	/* ... spent in softirqs            */
	u32 per_cpu_ioरुको;	/* ... spent जबतक रुकोing क्रम I/O  */

	/* New in modअगरication level 01 */
	u32 per_cpu_steal;	/* ... stolen by hypervisor	    */
	u32 cpu_id;		/* number of this CPU		    */
पूर्ण __attribute__((packed));

काष्ठा appldata_os_data अणु
	u64 बारtamp;
	u32 sync_count_1;	/* after VM collected the record data, */
	u32 sync_count_2;	/* sync_count_1 and sync_count_2 should be the
				   same. If not, the record has been updated on
				   the Linux side जबतक VM was collecting the
				   (possibly corrupt) data */

	u32 nr_cpus;		/* number of (भव) CPUs        */
	u32 per_cpu_size;	/* size of the per-cpu data काष्ठा */
	u32 cpu_offset;		/* offset of the first per-cpu data काष्ठा */

	u32 nr_running;		/* number of runnable thपढ़ोs      */
	u32 nr_thपढ़ोs;		/* number of thपढ़ोs               */
	u32 avenrun[3];		/* average nr. of running processes during */
				/* the last 1, 5 and 15 minutes */

	/* New in 2.6 */
	u32 nr_ioरुको;		/* number of blocked thपढ़ोs
				   (रुकोing क्रम I/O)               */

	/* per cpu data */
	काष्ठा appldata_os_per_cpu os_cpu[];
पूर्ण __attribute__((packed));

अटल काष्ठा appldata_os_data *appldata_os_data;

अटल काष्ठा appldata_ops ops = अणु
	.name	   = "os",
	.record_nr = APPLDATA_RECORD_OS_ID,
	.owner	   = THIS_MODULE,
	.mod_lvl   = अणु0xF0, 0xF1पूर्ण,		/* EBCDIC "01" */
पूर्ण;


/*
 * appldata_get_os_data()
 *
 * gather OS data
 */
अटल व्योम appldata_get_os_data(व्योम *data)
अणु
	पूर्णांक i, j, rc;
	काष्ठा appldata_os_data *os_data;
	अचिन्हित पूर्णांक new_size;

	os_data = data;
	os_data->sync_count_1++;

	os_data->nr_thपढ़ोs = nr_thपढ़ोs;
	os_data->nr_running = nr_running();
	os_data->nr_ioरुको  = nr_ioरुको();
	os_data->avenrun[0] = avenrun[0] + (FIXED_1/200);
	os_data->avenrun[1] = avenrun[1] + (FIXED_1/200);
	os_data->avenrun[2] = avenrun[2] + (FIXED_1/200);

	j = 0;
	क्रम_each_online_cpu(i) अणु
		os_data->os_cpu[j].per_cpu_user =
			nsecs_to_jअगरfies(kcpustat_cpu(i).cpustat[CPUTIME_USER]);
		os_data->os_cpu[j].per_cpu_nice =
			nsecs_to_jअगरfies(kcpustat_cpu(i).cpustat[CPUTIME_NICE]);
		os_data->os_cpu[j].per_cpu_प्रणाली =
			nsecs_to_jअगरfies(kcpustat_cpu(i).cpustat[CPUTIME_SYSTEM]);
		os_data->os_cpu[j].per_cpu_idle =
			nsecs_to_jअगरfies(kcpustat_cpu(i).cpustat[CPUTIME_IDLE]);
		os_data->os_cpu[j].per_cpu_irq =
			nsecs_to_jअगरfies(kcpustat_cpu(i).cpustat[CPUTIME_IRQ]);
		os_data->os_cpu[j].per_cpu_softirq =
			nsecs_to_jअगरfies(kcpustat_cpu(i).cpustat[CPUTIME_SOFTIRQ]);
		os_data->os_cpu[j].per_cpu_ioरुको =
			nsecs_to_jअगरfies(kcpustat_cpu(i).cpustat[CPUTIME_IOWAIT]);
		os_data->os_cpu[j].per_cpu_steal =
			nsecs_to_jअगरfies(kcpustat_cpu(i).cpustat[CPUTIME_STEAL]);
		os_data->os_cpu[j].cpu_id = i;
		j++;
	पूर्ण

	os_data->nr_cpus = j;

	new_size = काष्ठा_size(os_data, os_cpu, os_data->nr_cpus);
	अगर (ops.size != new_size) अणु
		अगर (ops.active) अणु
			rc = appldata_diag(APPLDATA_RECORD_OS_ID,
					   APPLDATA_START_INTERVAL_REC,
					   (अचिन्हित दीर्घ) ops.data, new_size,
					   ops.mod_lvl);
			अगर (rc != 0)
				pr_err("Starting a new OS data collection "
				       "failed with rc=%d\n", rc);

			rc = appldata_diag(APPLDATA_RECORD_OS_ID,
					   APPLDATA_STOP_REC,
					   (अचिन्हित दीर्घ) ops.data, ops.size,
					   ops.mod_lvl);
			अगर (rc != 0)
				pr_err("Stopping a faulty OS data "
				       "collection failed with rc=%d\n", rc);
		पूर्ण
		ops.size = new_size;
	पूर्ण
	os_data->बारtamp = get_tod_घड़ी();
	os_data->sync_count_2++;
पूर्ण


/*
 * appldata_os_init()
 *
 * init data, रेजिस्टर ops
 */
अटल पूर्णांक __init appldata_os_init(व्योम)
अणु
	पूर्णांक rc, max_size;

	max_size = काष्ठा_size(appldata_os_data, os_cpu, num_possible_cpus());
	अगर (max_size > APPLDATA_MAX_REC_SIZE) अणु
		pr_err("Maximum OS record size %i exceeds the maximum "
		       "record size %i\n", max_size, APPLDATA_MAX_REC_SIZE);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	appldata_os_data = kzalloc(max_size, GFP_KERNEL | GFP_DMA);
	अगर (appldata_os_data == शून्य) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	appldata_os_data->per_cpu_size = माप(काष्ठा appldata_os_per_cpu);
	appldata_os_data->cpu_offset   = दुरत्व(काष्ठा appldata_os_data,
							os_cpu);

	ops.data = appldata_os_data;
	ops.callback  = &appldata_get_os_data;
	rc = appldata_रेजिस्टर_ops(&ops);
	अगर (rc != 0)
		kमुक्त(appldata_os_data);
out:
	वापस rc;
पूर्ण

/*
 * appldata_os_निकास()
 *
 * unरेजिस्टर ops
 */
अटल व्योम __निकास appldata_os_निकास(व्योम)
अणु
	appldata_unरेजिस्टर_ops(&ops);
	kमुक्त(appldata_os_data);
पूर्ण


module_init(appldata_os_init);
module_निकास(appldata_os_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gerald Schaefer");
MODULE_DESCRIPTION("Linux-VM Monitor Stream, OS statistics");
