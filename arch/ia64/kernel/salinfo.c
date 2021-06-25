<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * salinfo.c
 *
 * Creates entries in /proc/sal क्रम various प्रणाली features.
 *
 * Copyright (c) 2003, 2006 Silicon Graphics, Inc.  All rights reserved.
 * Copyright (c) 2003 Hewlett-Packard Co
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 *
 * 10/30/2001	jbarnes@sgi.com		copied much of Stephane's palinfo
 *					code to create this file
 * Oct 23 2003	kaos@sgi.com
 *   Replace IPI with set_cpus_allowed() to पढ़ो a record from the required cpu.
 *   Redesign salinfo log processing to separate पूर्णांकerrupt and user space
 *   contexts.
 *   Cache the record across multi-block पढ़ोs from user space.
 *   Support > 64 cpus.
 *   Delete module_निकास and MOD_INC/DEC_COUNT, salinfo cannot be a module.
 *
 * Jan 28 2004	kaos@sgi.com
 *   Periodically check क्रम outstanding MCA or INIT records.
 *
 * Dec  5 2004	kaos@sgi.com
 *   Standardize which records are cleared स्वतःmatically.
 *
 * Aug 18 2005	kaos@sgi.com
 *   mca.c may not pass a buffer, a शून्य buffer just indicates that a new
 *   record is available in SAL.
 *   Replace some NR_CPUS by cpus_online, क्रम hotplug cpu.
 *
 * Jan  5 2006        kaos@sgi.com
 *   Handle hotplug cpus coming online.
 *   Handle hotplug cpus going offline जबतक they still have outstanding records.
 *   Use the cpu_* macros consistently.
 *   Replace the counting semaphore with a mutex and a test अगर the cpumask is non-empty.
 *   Modअगरy the locking to make the test क्रम "work to do" an atomic operation.
 */

#समावेश <linux/capability.h>
#समावेश <linux/cpu.h>
#समावेश <linux/types.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/module.h>
#समावेश <linux/smp.h>
#समावेश <linux/समयr.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/semaphore.h>

#समावेश <यंत्र/sal.h>
#समावेश <linux/uaccess.h>

MODULE_AUTHOR("Jesse Barnes <jbarnes@sgi.com>");
MODULE_DESCRIPTION("/proc interface to IA-64 SAL features");
MODULE_LICENSE("GPL");

प्रकार काष्ठा अणु
	स्थिर अक्षर		*name;		/* name of the proc entry */
	अचिन्हित दीर्घ           feature;        /* feature bit */
	काष्ठा proc_dir_entry	*entry;		/* रेजिस्टरed entry (removal) */
पूर्ण salinfo_entry_t;

/*
 * List अणुname,featureपूर्ण pairs क्रम every entry in /proc/sal/<feature>
 * that this module exports
 */
अटल स्थिर salinfo_entry_t salinfo_entries[]=अणु
	अणु "bus_lock",           IA64_SAL_PLATFORM_FEATURE_BUS_LOCK, पूर्ण,
	अणु "irq_redirection",	IA64_SAL_PLATFORM_FEATURE_IRQ_REसूची_HINT, पूर्ण,
	अणु "ipi_redirection",	IA64_SAL_PLATFORM_FEATURE_IPI_REसूची_HINT, पूर्ण,
	अणु "itc_drift",		IA64_SAL_PLATFORM_FEATURE_ITC_DRIFT, पूर्ण,
पूर्ण;

#घोषणा NR_SALINFO_ENTRIES ARRAY_SIZE(salinfo_entries)

अटल अक्षर *salinfo_log_name[] = अणु
	"mca",
	"init",
	"cmc",
	"cpe",
पूर्ण;

अटल काष्ठा proc_dir_entry *salinfo_proc_entries[
	ARRAY_SIZE(salinfo_entries) +			/* /proc/sal/bus_lock */
	ARRAY_SIZE(salinfo_log_name) +			/* /proc/sal/अणुmca,...पूर्ण */
	(2 * ARRAY_SIZE(salinfo_log_name)) +		/* /proc/sal/mca/अणुevent,dataपूर्ण */
	1];						/* /proc/sal */

/* Some records we get ourselves, some are accessed as saved data in buffers
 * that are owned by mca.c.
 */
काष्ठा salinfo_data_saved अणु
	u8*			buffer;
	u64			size;
	u64			id;
	पूर्णांक			cpu;
पूर्ण;

/* State transitions.  Actions are :-
 *   Write "read <cpunum>" to the data file.
 *   Write "clear <cpunum>" to the data file.
 *   Write "oemdata <cpunum> <offset> to the data file.
 *   Read from the data file.
 *   Close the data file.
 *
 * Start state is NO_DATA.
 *
 * NO_DATA
 *    ग_लिखो "read <cpunum>" -> NO_DATA or LOG_RECORD.
 *    ग_लिखो "clear <cpunum>" -> NO_DATA or LOG_RECORD.
 *    ग_लिखो "oemdata <cpunum> <offset> -> वापस -EINVAL.
 *    पढ़ो data -> वापस खातापूर्ण.
 *    बंद -> unchanged.  Free record areas.
 *
 * LOG_RECORD
 *    ग_लिखो "read <cpunum>" -> NO_DATA or LOG_RECORD.
 *    ग_लिखो "clear <cpunum>" -> NO_DATA or LOG_RECORD.
 *    ग_लिखो "oemdata <cpunum> <offset> -> क्रमmat the oem data, जाओ OEMDATA.
 *    पढ़ो data -> वापस the INIT/MCA/CMC/CPE record.
 *    बंद -> unchanged.  Keep record areas.
 *
 * OEMDATA
 *    ग_लिखो "read <cpunum>" -> NO_DATA or LOG_RECORD.
 *    ग_लिखो "clear <cpunum>" -> NO_DATA or LOG_RECORD.
 *    ग_लिखो "oemdata <cpunum> <offset> -> क्रमmat the oem data, जाओ OEMDATA.
 *    पढ़ो data -> वापस the क्रमmatted oemdata.
 *    बंद -> unchanged.  Keep record areas.
 *
 * Closing the data file करोes not change the state.  This allows shell scripts
 * to manipulate salinfo data, each shell redirection खोलोs the file, करोes one
 * action then बंदs it again.  The record areas are only मुक्तd at बंद when
 * the state is NO_DATA.
 */
क्रमागत salinfo_state अणु
	STATE_NO_DATA,
	STATE_LOG_RECORD,
	STATE_OEMDATA,
पूर्ण;

काष्ठा salinfo_data अणु
	cpumask_t		cpu_event;	/* which cpus have outstanding events */
	रुको_queue_head_t	पढ़ो_रुको;
	u8			*log_buffer;
	u64			log_size;
	u8			*oemdata;	/* decoded oem data */
	u64			oemdata_size;
	पूर्णांक			खोलो;		/* single-खोलो to prevent races */
	u8			type;
	u8			saved_num;	/* using a saved record? */
	क्रमागत salinfo_state	state :8;	/* processing state */
	u8			padding;
	पूर्णांक			cpu_check;	/* next CPU to check */
	काष्ठा salinfo_data_saved data_saved[5];/* save last 5 records from mca.c, must be < 255 */
पूर्ण;

अटल काष्ठा salinfo_data salinfo_data[ARRAY_SIZE(salinfo_log_name)];

अटल DEFINE_SPINLOCK(data_lock);
अटल DEFINE_SPINLOCK(data_saved_lock);

/** salinfo_platक्रमm_oemdata - optional callback to decode oemdata from an error
 * record.
 * @sect_header: poपूर्णांकer to the start of the section to decode.
 * @oemdata: वापसs vदो_स्मृति area containing the decoded output.
 * @oemdata_size: वापसs length of decoded output (म_माप).
 *
 * Description: If user space asks क्रम oem data to be decoded by the kernel
 * and/or prom and the platक्रमm has set salinfo_platक्रमm_oemdata to the address
 * of a platक्रमm specअगरic routine then call that routine.  salinfo_platक्रमm_oemdata
 * vदो_स्मृति's and क्रमmats its output area, वापसing the address of the text
 * and its म_माप.  Returns 0 क्रम success, -ve क्रम error.  The callback is
 * invoked on the cpu that generated the error record.
 */
पूर्णांक (*salinfo_platक्रमm_oemdata)(स्थिर u8 *sect_header, u8 **oemdata, u64 *oemdata_size);

काष्ठा salinfo_platक्रमm_oemdata_parms अणु
	स्थिर u8 *efi_guid;
	u8 **oemdata;
	u64 *oemdata_size;
पूर्ण;

अटल दीर्घ
salinfo_platक्रमm_oemdata_cpu(व्योम *context)
अणु
	काष्ठा salinfo_platक्रमm_oemdata_parms *parms = context;

	वापस salinfo_platक्रमm_oemdata(parms->efi_guid, parms->oemdata, parms->oemdata_size);
पूर्ण

अटल व्योम
shअगरt1_data_saved (काष्ठा salinfo_data *data, पूर्णांक shअगरt)
अणु
	स_नकल(data->data_saved+shअगरt, data->data_saved+shअगरt+1,
	       (ARRAY_SIZE(data->data_saved) - (shअगरt+1)) * माप(data->data_saved[0]));
	स_रखो(data->data_saved + ARRAY_SIZE(data->data_saved) - 1, 0,
	       माप(data->data_saved[0]));
पूर्ण

/* This routine is invoked in पूर्णांकerrupt context.  Note: mca.c enables
 * पूर्णांकerrupts beक्रमe calling this code क्रम CMC/CPE.  MCA and INIT events are
 * not irq safe, करो not call any routines that use spinlocks, they may deadlock.
 * MCA and INIT records are recorded, a समयr event will look क्रम any
 * outstanding events and wake up the user space code.
 *
 * The buffer passed from mca.c poपूर्णांकs to the output from ia64_log_get. This is
 * a persistent buffer but its contents can change between the पूर्णांकerrupt and
 * when user space processes the record.  Save the record id to identअगरy
 * changes.  If the buffer is शून्य then just update the biपंचांगap.
 */
व्योम
salinfo_log_wakeup(पूर्णांक type, u8 *buffer, u64 size, पूर्णांक irqsafe)
अणु
	काष्ठा salinfo_data *data = salinfo_data + type;
	काष्ठा salinfo_data_saved *data_saved;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक i;
	पूर्णांक saved_size = ARRAY_SIZE(data->data_saved);

	BUG_ON(type >= ARRAY_SIZE(salinfo_log_name));

	अगर (irqsafe)
		spin_lock_irqsave(&data_saved_lock, flags);
	अगर (buffer) अणु
		क्रम (i = 0, data_saved = data->data_saved; i < saved_size; ++i, ++data_saved) अणु
			अगर (!data_saved->buffer)
				अवरोध;
		पूर्ण
		अगर (i == saved_size) अणु
			अगर (!data->saved_num) अणु
				shअगरt1_data_saved(data, 0);
				data_saved = data->data_saved + saved_size - 1;
			पूर्ण अन्यथा
				data_saved = शून्य;
		पूर्ण
		अगर (data_saved) अणु
			data_saved->cpu = smp_processor_id();
			data_saved->id = ((sal_log_record_header_t *)buffer)->id;
			data_saved->size = size;
			data_saved->buffer = buffer;
		पूर्ण
	पूर्ण
	cpumask_set_cpu(smp_processor_id(), &data->cpu_event);
	अगर (irqsafe) अणु
		wake_up_पूर्णांकerruptible(&data->पढ़ो_रुको);
		spin_unlock_irqrestore(&data_saved_lock, flags);
	पूर्ण
पूर्ण

/* Check क्रम outstanding MCA/INIT records every minute (arbitrary) */
#घोषणा SALINFO_TIMER_DELAY (60*HZ)
अटल काष्ठा समयr_list salinfo_समयr;
बाह्य व्योम ia64_mlogbuf_dump(व्योम);

अटल व्योम
salinfo_समयout_check(काष्ठा salinfo_data *data)
अणु
	अगर (!data->खोलो)
		वापस;
	अगर (!cpumask_empty(&data->cpu_event))
		wake_up_पूर्णांकerruptible(&data->पढ़ो_रुको);
पूर्ण

अटल व्योम
salinfo_समयout(काष्ठा समयr_list *unused)
अणु
	ia64_mlogbuf_dump();
	salinfo_समयout_check(salinfo_data + SAL_INFO_TYPE_MCA);
	salinfo_समयout_check(salinfo_data + SAL_INFO_TYPE_INIT);
	salinfo_समयr.expires = jअगरfies + SALINFO_TIMER_DELAY;
	add_समयr(&salinfo_समयr);
पूर्ण

अटल पूर्णांक
salinfo_event_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
salinfo_event_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा salinfo_data *data = PDE_DATA(file_inode(file));
	अक्षर cmd[32];
	माप_प्रकार size;
	पूर्णांक i, n, cpu = -1;

retry:
	अगर (cpumask_empty(&data->cpu_event)) अणु
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		अगर (रुको_event_पूर्णांकerruptible(data->पढ़ो_रुको,
					     !cpumask_empty(&data->cpu_event)))
			वापस -EINTR;
	पूर्ण

	n = data->cpu_check;
	क्रम (i = 0; i < nr_cpu_ids; i++) अणु
		अगर (cpumask_test_cpu(n, &data->cpu_event)) अणु
			अगर (!cpu_online(n)) अणु
				cpumask_clear_cpu(n, &data->cpu_event);
				जारी;
			पूर्ण
			cpu = n;
			अवरोध;
		पूर्ण
		अगर (++n == nr_cpu_ids)
			n = 0;
	पूर्ण

	अगर (cpu == -1)
		जाओ retry;

	ia64_mlogbuf_dump();

	/* क्रम next पढ़ो, start checking at next CPU */
	data->cpu_check = cpu;
	अगर (++data->cpu_check == nr_cpu_ids)
		data->cpu_check = 0;

	snम_लिखो(cmd, माप(cmd), "read %d\n", cpu);

	size = म_माप(cmd);
	अगर (size > count)
		size = count;
	अगर (copy_to_user(buffer, cmd, size))
		वापस -EFAULT;

	वापस size;
पूर्ण

अटल स्थिर काष्ठा proc_ops salinfo_event_proc_ops = अणु
	.proc_खोलो	= salinfo_event_खोलो,
	.proc_पढ़ो	= salinfo_event_पढ़ो,
	.proc_lseek	= noop_llseek,
पूर्ण;

अटल पूर्णांक
salinfo_log_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा salinfo_data *data = PDE_DATA(inode);

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	spin_lock(&data_lock);
	अगर (data->खोलो) अणु
		spin_unlock(&data_lock);
		वापस -EBUSY;
	पूर्ण
	data->खोलो = 1;
	spin_unlock(&data_lock);

	अगर (data->state == STATE_NO_DATA &&
	    !(data->log_buffer = vदो_स्मृति(ia64_sal_get_state_info_size(data->type)))) अणु
		data->खोलो = 0;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
salinfo_log_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा salinfo_data *data = PDE_DATA(inode);

	अगर (data->state == STATE_NO_DATA) अणु
		vमुक्त(data->log_buffer);
		vमुक्त(data->oemdata);
		data->log_buffer = शून्य;
		data->oemdata = शून्य;
	पूर्ण
	spin_lock(&data_lock);
	data->खोलो = 0;
	spin_unlock(&data_lock);
	वापस 0;
पूर्ण

अटल दीर्घ
salinfo_log_पढ़ो_cpu(व्योम *context)
अणु
	काष्ठा salinfo_data *data = context;
	sal_log_record_header_t *rh;
	data->log_size = ia64_sal_get_state_info(data->type, (u64 *) data->log_buffer);
	rh = (sal_log_record_header_t *)(data->log_buffer);
	/* Clear corrected errors as they are पढ़ो from SAL */
	अगर (rh->severity == sal_log_severity_corrected)
		ia64_sal_clear_state_info(data->type);
	वापस 0;
पूर्ण

अटल व्योम
salinfo_log_new_पढ़ो(पूर्णांक cpu, काष्ठा salinfo_data *data)
अणु
	काष्ठा salinfo_data_saved *data_saved;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक saved_size = ARRAY_SIZE(data->data_saved);

	data->saved_num = 0;
	spin_lock_irqsave(&data_saved_lock, flags);
retry:
	क्रम (i = 0, data_saved = data->data_saved; i < saved_size; ++i, ++data_saved) अणु
		अगर (data_saved->buffer && data_saved->cpu == cpu) अणु
			sal_log_record_header_t *rh = (sal_log_record_header_t *)(data_saved->buffer);
			data->log_size = data_saved->size;
			स_नकल(data->log_buffer, rh, data->log_size);
			barrier();	/* id check must not be moved */
			अगर (rh->id == data_saved->id) अणु
				data->saved_num = i+1;
				अवरोध;
			पूर्ण
			/* saved record changed by mca.c since पूर्णांकerrupt, discard it */
			shअगरt1_data_saved(data, i);
			जाओ retry;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&data_saved_lock, flags);

	अगर (!data->saved_num)
		work_on_cpu_safe(cpu, salinfo_log_पढ़ो_cpu, data);
	अगर (!data->log_size) अणु
		data->state = STATE_NO_DATA;
		cpumask_clear_cpu(cpu, &data->cpu_event);
	पूर्ण अन्यथा अणु
		data->state = STATE_LOG_RECORD;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
salinfo_log_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा salinfo_data *data = PDE_DATA(file_inode(file));
	u8 *buf;
	u64 bufsize;

	अगर (data->state == STATE_LOG_RECORD) अणु
		buf = data->log_buffer;
		bufsize = data->log_size;
	पूर्ण अन्यथा अगर (data->state == STATE_OEMDATA) अणु
		buf = data->oemdata;
		bufsize = data->oemdata_size;
	पूर्ण अन्यथा अणु
		buf = शून्य;
		bufsize = 0;
	पूर्ण
	वापस simple_पढ़ो_from_buffer(buffer, count, ppos, buf, bufsize);
पूर्ण

अटल दीर्घ
salinfo_log_clear_cpu(व्योम *context)
अणु
	काष्ठा salinfo_data *data = context;

	ia64_sal_clear_state_info(data->type);
	वापस 0;
पूर्ण

अटल पूर्णांक
salinfo_log_clear(काष्ठा salinfo_data *data, पूर्णांक cpu)
अणु
	sal_log_record_header_t *rh;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&data_saved_lock, flags);
	data->state = STATE_NO_DATA;
	अगर (!cpumask_test_cpu(cpu, &data->cpu_event)) अणु
		spin_unlock_irqrestore(&data_saved_lock, flags);
		वापस 0;
	पूर्ण
	cpumask_clear_cpu(cpu, &data->cpu_event);
	अगर (data->saved_num) अणु
		shअगरt1_data_saved(data, data->saved_num - 1);
		data->saved_num = 0;
	पूर्ण
	spin_unlock_irqrestore(&data_saved_lock, flags);
	rh = (sal_log_record_header_t *)(data->log_buffer);
	/* Corrected errors have alपढ़ोy been cleared from SAL */
	अगर (rh->severity != sal_log_severity_corrected)
		work_on_cpu_safe(cpu, salinfo_log_clear_cpu, data);
	/* clearing a record may make a new record visible */
	salinfo_log_new_पढ़ो(cpu, data);
	अगर (data->state == STATE_LOG_RECORD) अणु
		spin_lock_irqsave(&data_saved_lock, flags);
		cpumask_set_cpu(cpu, &data->cpu_event);
		wake_up_पूर्णांकerruptible(&data->पढ़ो_रुको);
		spin_unlock_irqrestore(&data_saved_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
salinfo_log_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा salinfo_data *data = PDE_DATA(file_inode(file));
	अक्षर cmd[32];
	माप_प्रकार size;
	u32 offset;
	पूर्णांक cpu;

	size = माप(cmd);
	अगर (count < size)
		size = count;
	अगर (copy_from_user(cmd, buffer, size))
		वापस -EFAULT;

	अगर (माला_पूछो(cmd, "read %d", &cpu) == 1) अणु
		salinfo_log_new_पढ़ो(cpu, data);
	पूर्ण अन्यथा अगर (माला_पूछो(cmd, "clear %d", &cpu) == 1) अणु
		पूर्णांक ret;
		अगर ((ret = salinfo_log_clear(data, cpu)))
			count = ret;
	पूर्ण अन्यथा अगर (माला_पूछो(cmd, "oemdata %d %d", &cpu, &offset) == 2) अणु
		अगर (data->state != STATE_LOG_RECORD && data->state != STATE_OEMDATA)
			वापस -EINVAL;
		अगर (offset > data->log_size - माप(efi_guid_t))
			वापस -EINVAL;
		data->state = STATE_OEMDATA;
		अगर (salinfo_platक्रमm_oemdata) अणु
			काष्ठा salinfo_platक्रमm_oemdata_parms parms = अणु
				.efi_guid = data->log_buffer + offset,
				.oemdata = &data->oemdata,
				.oemdata_size = &data->oemdata_size
			पूर्ण;
			count = work_on_cpu_safe(cpu, salinfo_platक्रमm_oemdata_cpu,
						 &parms);
		पूर्ण अन्यथा
			data->oemdata_size = 0;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops salinfo_data_proc_ops = अणु
	.proc_खोलो	= salinfo_log_खोलो,
	.proc_release	= salinfo_log_release,
	.proc_पढ़ो	= salinfo_log_पढ़ो,
	.proc_ग_लिखो	= salinfo_log_ग_लिखो,
	.proc_lseek	= शेष_llseek,
पूर्ण;

अटल पूर्णांक salinfo_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक i, end = ARRAY_SIZE(salinfo_data);
	काष्ठा salinfo_data *data;

	spin_lock_irq(&data_saved_lock);
	क्रम (i = 0, data = salinfo_data; i < end; ++i, ++data) अणु
		cpumask_set_cpu(cpu, &data->cpu_event);
		wake_up_पूर्णांकerruptible(&data->पढ़ो_रुको);
	पूर्ण
	spin_unlock_irq(&data_saved_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक salinfo_cpu_pre_करोwn(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक i, end = ARRAY_SIZE(salinfo_data);
	काष्ठा salinfo_data *data;

	spin_lock_irq(&data_saved_lock);
	क्रम (i = 0, data = salinfo_data; i < end; ++i, ++data) अणु
		काष्ठा salinfo_data_saved *data_saved;
		पूर्णांक j = ARRAY_SIZE(data->data_saved) - 1;

		क्रम (data_saved = data->data_saved + j; j >= 0;
		     --j, --data_saved) अणु
			अगर (data_saved->buffer && data_saved->cpu == cpu)
				shअगरt1_data_saved(data, j);
		पूर्ण
		cpumask_clear_cpu(cpu, &data->cpu_event);
	पूर्ण
	spin_unlock_irq(&data_saved_lock);
	वापस 0;
पूर्ण

/*
 * 'data' contains an integer that corresponds to the feature we're
 * testing
 */
अटल पूर्णांक proc_salinfo_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ data = (अचिन्हित दीर्घ)v;
	seq_माला_दो(m, (sal_platक्रमm_features & data) ? "1\n" : "0\n");
	वापस 0;
पूर्ण

अटल पूर्णांक __init
salinfo_init(व्योम)
अणु
	काष्ठा proc_dir_entry *salinfo_dir; /* /proc/sal dir entry */
	काष्ठा proc_dir_entry **sdir = salinfo_proc_entries; /* keeps track of every entry */
	काष्ठा proc_dir_entry *dir, *entry;
	काष्ठा salinfo_data *data;
	पूर्णांक i;

	salinfo_dir = proc_सूची_गढ़ो("sal", शून्य);
	अगर (!salinfo_dir)
		वापस 0;

	क्रम (i=0; i < NR_SALINFO_ENTRIES; i++) अणु
		/* pass the feature bit in question as misc data */
		*sdir++ = proc_create_single_data(salinfo_entries[i].name, 0,
				salinfo_dir, proc_salinfo_show,
				(व्योम *)salinfo_entries[i].feature);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(salinfo_log_name); i++) अणु
		data = salinfo_data + i;
		data->type = i;
		init_रुकोqueue_head(&data->पढ़ो_रुको);
		dir = proc_सूची_गढ़ो(salinfo_log_name[i], salinfo_dir);
		अगर (!dir)
			जारी;

		entry = proc_create_data("event", S_IRUSR, dir,
					 &salinfo_event_proc_ops, data);
		अगर (!entry)
			जारी;
		*sdir++ = entry;

		entry = proc_create_data("data", S_IRUSR | S_IWUSR, dir,
					 &salinfo_data_proc_ops, data);
		अगर (!entry)
			जारी;
		*sdir++ = entry;

		*sdir++ = dir;
	पूर्ण

	*sdir++ = salinfo_dir;

	समयr_setup(&salinfo_समयr, salinfo_समयout, 0);
	salinfo_समयr.expires = jअगरfies + SALINFO_TIMER_DELAY;
	add_समयr(&salinfo_समयr);

	i = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "ia64/salinfo:online",
			      salinfo_cpu_online, salinfo_cpu_pre_करोwn);
	WARN_ON(i < 0);
	वापस 0;
पूर्ण

module_init(salinfo_init);
