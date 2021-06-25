<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 *
 * Communication to userspace based on kernel/prपूर्णांकk.c
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/poll.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cpu.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/topology.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/nvram.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/topology.h>


अटल DEFINE_SPINLOCK(rtasd_log_lock);

अटल DECLARE_WAIT_QUEUE_HEAD(rtas_log_रुको);

अटल अक्षर *rtas_log_buf;
अटल अचिन्हित दीर्घ rtas_log_start;
अटल अचिन्हित दीर्घ rtas_log_size;

अटल पूर्णांक surveillance_समयout = -1;

अटल अचिन्हित पूर्णांक rtas_error_log_max;
अटल अचिन्हित पूर्णांक rtas_error_log_buffer_max;

/* RTAS service tokens */
अटल अचिन्हित पूर्णांक event_scan;
अटल अचिन्हित पूर्णांक rtas_event_scan_rate;

अटल bool full_rtas_msgs;

/* Stop logging to nvram after first fatal error */
अटल पूर्णांक logging_enabled; /* Until we initialize everything,
                             * make sure we करोn't try logging
                             * anything */
अटल पूर्णांक error_log_cnt;

/*
 * Since we use 32 bit RTAS, the physical address of this must be below
 * 4G or अन्यथा bad things happen. Allocate this in the kernel data and
 * make it big enough.
 */
अटल अचिन्हित अक्षर logdata[RTAS_ERROR_LOG_MAX];

अटल अक्षर *rtas_type[] = अणु
	"Unknown", "Retry", "TCE Error", "Internal Device Failure",
	"Timeout", "Data Parity", "Address Parity", "Cache Parity",
	"Address Invalid", "ECC Uncorrected", "ECC Corrupted",
पूर्ण;

अटल अक्षर *rtas_event_type(पूर्णांक type)
अणु
	अगर ((type > 0) && (type < 11))
		वापस rtas_type[type];

	चयन (type) अणु
		हाल RTAS_TYPE_EPOW:
			वापस "EPOW";
		हाल RTAS_TYPE_PLATFORM:
			वापस "Platform Error";
		हाल RTAS_TYPE_IO:
			वापस "I/O Event";
		हाल RTAS_TYPE_INFO:
			वापस "Platform Information Event";
		हाल RTAS_TYPE_DEALLOC:
			वापस "Resource Deallocation Event";
		हाल RTAS_TYPE_DUMP:
			वापस "Dump Notification Event";
		हाल RTAS_TYPE_PRRN:
			वापस "Platform Resource Reassignment Event";
		हाल RTAS_TYPE_HOTPLUG:
			वापस "Hotplug Event";
	पूर्ण

	वापस rtas_type[0];
पूर्ण

/* To see this info, grep RTAS /var/log/messages and each entry
 * will be collected together with obvious begin/end.
 * There will be a unique identअगरier on the begin and end lines.
 * This will persist across reboots.
 *
 * क्रमmat of error logs वापसed from RTAS:
 * bytes	(size)	: contents
 * --------------------------------------------------------
 * 0-7		(8)	: rtas_error_log
 * 8-47		(40)	: extended info
 * 48-51	(4)	: venकरोr id
 * 52-1023 (venकरोr specअगरic) : location code and debug data
 */
अटल व्योम prपूर्णांकk_log_rtas(अक्षर *buf, पूर्णांक len)
अणु

	पूर्णांक i,j,n = 0;
	पूर्णांक perline = 16;
	अक्षर buffer[64];
	अक्षर * str = "RTAS event";

	अगर (full_rtas_msgs) अणु
		prपूर्णांकk(RTAS_DEBUG "%d -------- %s begin --------\n",
		       error_log_cnt, str);

		/*
		 * Prपूर्णांक perline bytes on each line, each line will start
		 * with RTAS and a changing number, so syslogd will
		 * prपूर्णांक lines that are otherwise the same.  Separate every
		 * 4 bytes with a space.
		 */
		क्रम (i = 0; i < len; i++) अणु
			j = i % perline;
			अगर (j == 0) अणु
				स_रखो(buffer, 0, माप(buffer));
				n = प्र_लिखो(buffer, "RTAS %d:", i/perline);
			पूर्ण

			अगर ((i % 4) == 0)
				n += प्र_लिखो(buffer+n, " ");

			n += प्र_लिखो(buffer+n, "%02x", (अचिन्हित अक्षर)buf[i]);

			अगर (j == (perline-1))
				prपूर्णांकk(KERN_DEBUG "%s\n", buffer);
		पूर्ण
		अगर ((i % perline) != 0)
			prपूर्णांकk(KERN_DEBUG "%s\n", buffer);

		prपूर्णांकk(RTAS_DEBUG "%d -------- %s end ----------\n",
		       error_log_cnt, str);
	पूर्ण अन्यथा अणु
		काष्ठा rtas_error_log *errlog = (काष्ठा rtas_error_log *)buf;

		prपूर्णांकk(RTAS_DEBUG "event: %d, Type: %s (%d), Severity: %d\n",
		       error_log_cnt,
		       rtas_event_type(rtas_error_type(errlog)),
		       rtas_error_type(errlog),
		       rtas_error_severity(errlog));
	पूर्ण
पूर्ण

अटल पूर्णांक log_rtas_len(अक्षर * buf)
अणु
	पूर्णांक len;
	काष्ठा rtas_error_log *err;
	uपूर्णांक32_t extended_log_length;

	/* rtas fixed header */
	len = 8;
	err = (काष्ठा rtas_error_log *)buf;
	extended_log_length = rtas_error_extended_log_length(err);
	अगर (rtas_error_extended(err) && extended_log_length) अणु

		/* extended header */
		len += extended_log_length;
	पूर्ण

	अगर (rtas_error_log_max == 0)
		rtas_error_log_max = rtas_get_error_log_max();

	अगर (len > rtas_error_log_max)
		len = rtas_error_log_max;

	वापस len;
पूर्ण

/*
 * First ग_लिखो to nvram, अगर fatal error, that is the only
 * place we log the info.  The error will be picked up
 * on the next reboot by rtasd.  If not fatal, run the
 * method क्रम the type of error.  Currently, only RTAS
 * errors have methods implemented, but in the future
 * there might be a need to store data in nvram beक्रमe a
 * call to panic().
 *
 * XXX We ग_लिखो to nvram periodically, to indicate error has
 * been written and sync'd, but there is a possibility
 * that अगर we करोn't shutकरोwn correctly, a duplicate error
 * record will be created on next reboot.
 */
व्योम pSeries_log_error(अक्षर *buf, अचिन्हित पूर्णांक err_type, पूर्णांक fatal)
अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ s;
	पूर्णांक len = 0;

	pr_debug("rtasd: logging event\n");
	अगर (buf == शून्य)
		वापस;

	spin_lock_irqsave(&rtasd_log_lock, s);

	/* get length and increase count */
	चयन (err_type & ERR_TYPE_MASK) अणु
	हाल ERR_TYPE_RTAS_LOG:
		len = log_rtas_len(buf);
		अगर (!(err_type & ERR_FLAG_BOOT))
			error_log_cnt++;
		अवरोध;
	हाल ERR_TYPE_KERNEL_PANIC:
	शेष:
		WARN_ON_ONCE(!irqs_disabled()); /* @@@ DEBUG @@@ */
		spin_unlock_irqrestore(&rtasd_log_lock, s);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_PPC64
	/* Write error to NVRAM */
	अगर (logging_enabled && !(err_type & ERR_FLAG_BOOT))
		nvram_ग_लिखो_error_log(buf, len, err_type, error_log_cnt);
#पूर्ण_अगर /* CONFIG_PPC64 */

	/*
	 * rtas errors can occur during boot, and we करो want to capture
	 * those somewhere, even अगर nvram isn't पढ़ोy (why not?), and even
	 * अगर rtasd isn't पढ़ोy. Put them पूर्णांकo the boot log, at least.
	 */
	अगर ((err_type & ERR_TYPE_MASK) == ERR_TYPE_RTAS_LOG)
		prपूर्णांकk_log_rtas(buf, len);

	/* Check to see अगर we need to or have stopped logging */
	अगर (fatal || !logging_enabled) अणु
		logging_enabled = 0;
		WARN_ON_ONCE(!irqs_disabled()); /* @@@ DEBUG @@@ */
		spin_unlock_irqrestore(&rtasd_log_lock, s);
		वापस;
	पूर्ण

	/* call type specअगरic method क्रम error */
	चयन (err_type & ERR_TYPE_MASK) अणु
	हाल ERR_TYPE_RTAS_LOG:
		offset = rtas_error_log_buffer_max *
			((rtas_log_start+rtas_log_size) & LOG_NUMBER_MASK);

		/* First copy over sequence number */
		स_नकल(&rtas_log_buf[offset], (व्योम *) &error_log_cnt, माप(पूर्णांक));

		/* Second copy over error log data */
		offset += माप(पूर्णांक);
		स_नकल(&rtas_log_buf[offset], buf, len);

		अगर (rtas_log_size < LOG_NUMBER)
			rtas_log_size += 1;
		अन्यथा
			rtas_log_start += 1;

		WARN_ON_ONCE(!irqs_disabled()); /* @@@ DEBUG @@@ */
		spin_unlock_irqrestore(&rtasd_log_lock, s);
		wake_up_पूर्णांकerruptible(&rtas_log_रुको);
		अवरोध;
	हाल ERR_TYPE_KERNEL_PANIC:
	शेष:
		WARN_ON_ONCE(!irqs_disabled()); /* @@@ DEBUG @@@ */
		spin_unlock_irqrestore(&rtasd_log_lock, s);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम handle_rtas_event(स्थिर काष्ठा rtas_error_log *log)
अणु
	अगर (!machine_is(pseries))
		वापस;

	अगर (rtas_error_type(log) == RTAS_TYPE_PRRN)
		pr_info_ratelimited("Platform resource reassignment ignored.\n");
पूर्ण

अटल पूर्णांक rtas_log_खोलो(काष्ठा inode * inode, काष्ठा file * file)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rtas_log_release(काष्ठा inode * inode, काष्ठा file * file)
अणु
	वापस 0;
पूर्ण

/* This will check अगर all events are logged, अगर they are then, we
 * know that we can safely clear the events in NVRAM.
 * Next we'll sit and रुको क्रम something अन्यथा to log.
 */
अटल sमाप_प्रकार rtas_log_पढ़ो(काष्ठा file * file, अक्षर __user * buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक error;
	अक्षर *पंचांगp;
	अचिन्हित दीर्घ s;
	अचिन्हित दीर्घ offset;

	अगर (!buf || count < rtas_error_log_buffer_max)
		वापस -EINVAL;

	count = rtas_error_log_buffer_max;

	अगर (!access_ok(buf, count))
		वापस -EFAULT;

	पंचांगp = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	spin_lock_irqsave(&rtasd_log_lock, s);

	/* अगर it's 0, then we know we got the last one (the one in NVRAM) */
	जबतक (rtas_log_size == 0) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			spin_unlock_irqrestore(&rtasd_log_lock, s);
			error = -EAGAIN;
			जाओ out;
		पूर्ण

		अगर (!logging_enabled) अणु
			spin_unlock_irqrestore(&rtasd_log_lock, s);
			error = -ENODATA;
			जाओ out;
		पूर्ण
#अगर_घोषित CONFIG_PPC64
		nvram_clear_error_log();
#पूर्ण_अगर /* CONFIG_PPC64 */

		spin_unlock_irqrestore(&rtasd_log_lock, s);
		error = रुको_event_पूर्णांकerruptible(rtas_log_रुको, rtas_log_size);
		अगर (error)
			जाओ out;
		spin_lock_irqsave(&rtasd_log_lock, s);
	पूर्ण

	offset = rtas_error_log_buffer_max * (rtas_log_start & LOG_NUMBER_MASK);
	स_नकल(पंचांगp, &rtas_log_buf[offset], count);

	rtas_log_start += 1;
	rtas_log_size -= 1;
	spin_unlock_irqrestore(&rtasd_log_lock, s);

	error = copy_to_user(buf, पंचांगp, count) ? -EFAULT : count;
out:
	kमुक्त(पंचांगp);
	वापस error;
पूर्ण

अटल __poll_t rtas_log_poll(काष्ठा file *file, poll_table * रुको)
अणु
	poll_रुको(file, &rtas_log_रुको, रुको);
	अगर (rtas_log_size)
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proc_ops rtas_log_proc_ops = अणु
	.proc_पढ़ो	= rtas_log_पढ़ो,
	.proc_poll	= rtas_log_poll,
	.proc_खोलो	= rtas_log_खोलो,
	.proc_release	= rtas_log_release,
	.proc_lseek	= noop_llseek,
पूर्ण;

अटल पूर्णांक enable_surveillance(पूर्णांक समयout)
अणु
	पूर्णांक error;

	error = rtas_set_indicator(SURVEILLANCE_TOKEN, 0, समयout);

	अगर (error == 0)
		वापस 0;

	अगर (error == -EINVAL) अणु
		prपूर्णांकk(KERN_DEBUG "rtasd: surveillance not supported\n");
		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_ERR "rtasd: could not update surveillance\n");
	वापस -1;
पूर्ण

अटल व्योम करो_event_scan(व्योम)
अणु
	पूर्णांक error;
	करो अणु
		स_रखो(logdata, 0, rtas_error_log_max);
		error = rtas_call(event_scan, 4, 1, शून्य,
				  RTAS_EVENT_SCAN_ALL_EVENTS, 0,
				  __pa(logdata), rtas_error_log_max);
		अगर (error == -1) अणु
			prपूर्णांकk(KERN_ERR "event-scan failed\n");
			अवरोध;
		पूर्ण

		अगर (error == 0) अणु
			अगर (rtas_error_type((काष्ठा rtas_error_log *)logdata) !=
			    RTAS_TYPE_PRRN)
				pSeries_log_error(logdata, ERR_TYPE_RTAS_LOG,
						  0);
			handle_rtas_event((काष्ठा rtas_error_log *)logdata);
		पूर्ण

	पूर्ण जबतक(error == 0);
पूर्ण

अटल व्योम rtas_event_scan(काष्ठा work_काष्ठा *w);
अटल DECLARE_DELAYED_WORK(event_scan_work, rtas_event_scan);

/*
 * Delay should be at least one second since some machines have problems अगर
 * we call event-scan too quickly.
 */
अटल अचिन्हित दीर्घ event_scan_delay = 1*HZ;
अटल पूर्णांक first_pass = 1;

अटल व्योम rtas_event_scan(काष्ठा work_काष्ठा *w)
अणु
	अचिन्हित पूर्णांक cpu;

	करो_event_scan();

	get_online_cpus();

	/* raw_ OK because just using CPU as starting poपूर्णांक. */
	cpu = cpumask_next(raw_smp_processor_id(), cpu_online_mask);
        अगर (cpu >= nr_cpu_ids) अणु
		cpu = cpumask_first(cpu_online_mask);

		अगर (first_pass) अणु
			first_pass = 0;
			event_scan_delay = 30*HZ/rtas_event_scan_rate;

			अगर (surveillance_समयout != -1) अणु
				pr_debug("rtasd: enabling surveillance\n");
				enable_surveillance(surveillance_समयout);
				pr_debug("rtasd: surveillance enabled\n");
			पूर्ण
		पूर्ण
	पूर्ण

	schedule_delayed_work_on(cpu, &event_scan_work,
		__round_jअगरfies_relative(event_scan_delay, cpu));

	put_online_cpus();
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल व्योम retrieve_nvram_error_log(व्योम)
अणु
	अचिन्हित पूर्णांक err_type ;
	पूर्णांक rc ;

	/* See अगर we have any error stored in NVRAM */
	स_रखो(logdata, 0, rtas_error_log_max);
	rc = nvram_पढ़ो_error_log(logdata, rtas_error_log_max,
	                          &err_type, &error_log_cnt);
	/* We can use rtas_log_buf now */
	logging_enabled = 1;
	अगर (!rc) अणु
		अगर (err_type != ERR_FLAG_ALREADY_LOGGED) अणु
			pSeries_log_error(logdata, err_type | ERR_FLAG_BOOT, 0);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा /* CONFIG_PPC64 */
अटल व्योम retrieve_nvram_error_log(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

अटल व्योम start_event_scan(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "RTAS daemon started\n");
	pr_debug("rtasd: will sleep for %d milliseconds\n",
		 (30000 / rtas_event_scan_rate));

	/* Retrieve errors from nvram अगर any */
	retrieve_nvram_error_log();

	schedule_delayed_work_on(cpumask_first(cpu_online_mask),
				 &event_scan_work, event_scan_delay);
पूर्ण

/* Cancel the rtas event scan work */
व्योम rtas_cancel_event_scan(व्योम)
अणु
	cancel_delayed_work_sync(&event_scan_work);
पूर्ण
EXPORT_SYMBOL_GPL(rtas_cancel_event_scan);

अटल पूर्णांक __init rtas_event_scan_init(व्योम)
अणु
	अगर (!machine_is(pseries) && !machine_is(chrp))
		वापस 0;

	/* No RTAS */
	event_scan = rtas_token("event-scan");
	अगर (event_scan == RTAS_UNKNOWN_SERVICE) अणु
		prपूर्णांकk(KERN_INFO "rtasd: No event-scan on system\n");
		वापस -ENODEV;
	पूर्ण

	rtas_event_scan_rate = rtas_token("rtas-event-scan-rate");
	अगर (rtas_event_scan_rate == RTAS_UNKNOWN_SERVICE) अणु
		prपूर्णांकk(KERN_ERR "rtasd: no rtas-event-scan-rate on system\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!rtas_event_scan_rate) अणु
		/* Broken firmware: take a rate of zero to mean करोn't scan */
		prपूर्णांकk(KERN_DEBUG "rtasd: scan rate is 0, not scanning\n");
		वापस 0;
	पूर्ण

	/* Make room क्रम the sequence number */
	rtas_error_log_max = rtas_get_error_log_max();
	rtas_error_log_buffer_max = rtas_error_log_max + माप(पूर्णांक);

	rtas_log_buf = vदो_स्मृति(array_size(LOG_NUMBER,
					  rtas_error_log_buffer_max));
	अगर (!rtas_log_buf) अणु
		prपूर्णांकk(KERN_ERR "rtasd: no memory\n");
		वापस -ENOMEM;
	पूर्ण

	start_event_scan();

	वापस 0;
पूर्ण
arch_initcall(rtas_event_scan_init);

अटल पूर्णांक __init rtas_init(व्योम)
अणु
	काष्ठा proc_dir_entry *entry;

	अगर (!machine_is(pseries) && !machine_is(chrp))
		वापस 0;

	अगर (!rtas_log_buf)
		वापस -ENODEV;

	entry = proc_create("powerpc/rtas/error_log", 0400, शून्य,
			    &rtas_log_proc_ops);
	अगर (!entry)
		prपूर्णांकk(KERN_ERR "Failed to create error_log proc entry\n");

	वापस 0;
पूर्ण
__initcall(rtas_init);

अटल पूर्णांक __init surveillance_setup(अक्षर *str)
अणु
	पूर्णांक i;

	/* We only करो surveillance on pseries */
	अगर (!machine_is(pseries))
		वापस 0;

	अगर (get_option(&str,&i)) अणु
		अगर (i >= 0 && i <= 255)
			surveillance_समयout = i;
	पूर्ण

	वापस 1;
पूर्ण
__setup("surveillance=", surveillance_setup);

अटल पूर्णांक __init rtयंत्रsgs_setup(अक्षर *str)
अणु
	वापस (kstrtobool(str, &full_rtas_msgs) == 0);
पूर्ण
__setup("rtasmsgs=", rtयंत्रsgs_setup);
