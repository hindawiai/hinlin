<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace_hwlat.c - A simple Hardware Latency detector.
 *
 * Use this tracer to detect large प्रणाली latencies induced by the behavior of
 * certain underlying प्रणाली hardware or firmware, independent of Linux itself.
 * The code was developed originally to detect the presence of SMIs on Intel
 * and AMD प्रणालीs, although there is no dependency upon x86 herein.
 *
 * The classical example usage of this tracer is in detecting the presence of
 * SMIs or System Management Interrupts on Intel and AMD प्रणालीs. An SMI is a
 * somewhat special क्रमm of hardware पूर्णांकerrupt spawned from earlier CPU debug
 * modes in which the (BIOS/EFI/etc.) firmware arranges क्रम the South Bridge
 * LPC (or other device) to generate a special पूर्णांकerrupt under certain
 * circumstances, क्रम example, upon expiration of a special SMI समयr device,
 * due to certain बाह्यal thermal पढ़ोings, on certain I/O address accesses,
 * and other situations. An SMI hits a special CPU pin, triggers a special
 * SMI mode (complete with special memory map), and the OS is unaware.
 *
 * Although certain hardware-inducing latencies are necessary (क्रम example,
 * a modern प्रणाली often requires an SMI handler क्रम correct thermal control
 * and remote management) they can wreak havoc upon any OS-level perक्रमmance
 * guarantees toward low-latency, especially when the OS is not even made
 * aware of the presence of these पूर्णांकerrupts. For this reason, we need a
 * somewhat brute क्रमce mechanism to detect these पूर्णांकerrupts. In this हाल,
 * we करो it by hogging all of the CPU(s) क्रम configurable समयr पूर्णांकervals,
 * sampling the built-in CPU समयr, looking क्रम discontiguous पढ़ोings.
 *
 * WARNING: This implementation necessarily पूर्णांकroduces latencies. Thereक्रमe,
 *          you should NEVER use this tracer जबतक running in a production
 *          environment requiring any kind of low-latency perक्रमmance
 *          guarantee(s).
 *
 * Copyright (C) 2008-2009 Jon Masters, Red Hat, Inc. <jcm@redhat.com>
 * Copyright (C) 2013-2016 Steven Rostedt, Red Hat, Inc. <srostedt@redhat.com>
 *
 * Includes useful feedback from Clark Williams <clark@redhat.com>
 *
 */
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/tracefs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश "trace.h"

अटल काष्ठा trace_array	*hwlat_trace;

#घोषणा U64STR_SIZE		22			/* 20 digits max */

#घोषणा BANNER			"hwlat_detector: "
#घोषणा DEFAULT_SAMPLE_WINDOW	1000000			/* 1s */
#घोषणा DEFAULT_SAMPLE_WIDTH	500000			/* 0.5s */
#घोषणा DEFAULT_LAT_THRESHOLD	10			/* 10us */

/* sampling thपढ़ो*/
अटल काष्ठा task_काष्ठा *hwlat_kthपढ़ो;

अटल काष्ठा dentry *hwlat_sample_width;	/* sample width us */
अटल काष्ठा dentry *hwlat_sample_winकरोw;	/* sample winकरोw us */

/* Save the previous tracing_thresh value */
अटल अचिन्हित दीर्घ save_tracing_thresh;

/* NMI बारtamp counters */
अटल u64 nmi_ts_start;
अटल u64 nmi_total_ts;
अटल पूर्णांक nmi_count;
अटल पूर्णांक nmi_cpu;

/* Tells NMIs to call back to the hwlat tracer to record बारtamps */
bool trace_hwlat_callback_enabled;

/* If the user changed threshold, remember it */
अटल u64 last_tracing_thresh = DEFAULT_LAT_THRESHOLD * NSEC_PER_USEC;

/* Inभागidual latency samples are stored here when detected. */
काष्ठा hwlat_sample अणु
	u64			seqnum;		/* unique sequence */
	u64			duration;	/* delta */
	u64			outer_duration;	/* delta (outer loop) */
	u64			nmi_total_ts;	/* Total समय spent in NMIs */
	काष्ठा बारpec64	बारtamp;	/* wall समय */
	पूर्णांक			nmi_count;	/* # NMIs during this sample */
	पूर्णांक			count;		/* # of iterations over thresh */
पूर्ण;

/* keep the global state somewhere. */
अटल काष्ठा hwlat_data अणु

	काष्ठा mutex lock;		/* protect changes */

	u64	count;			/* total since reset */

	u64	sample_winकरोw;		/* total sampling winकरोw (on+off) */
	u64	sample_width;		/* active sampling portion of winकरोw */

पूर्ण hwlat_data = अणु
	.sample_winकरोw		= DEFAULT_SAMPLE_WINDOW,
	.sample_width		= DEFAULT_SAMPLE_WIDTH,
पूर्ण;

अटल व्योम trace_hwlat_sample(काष्ठा hwlat_sample *sample)
अणु
	काष्ठा trace_array *tr = hwlat_trace;
	काष्ठा trace_event_call *call = &event_hwlat;
	काष्ठा trace_buffer *buffer = tr->array_buffer.buffer;
	काष्ठा ring_buffer_event *event;
	काष्ठा hwlat_entry *entry;

	event = trace_buffer_lock_reserve(buffer, TRACE_HWLAT, माप(*entry),
					  tracing_gen_ctx());
	अगर (!event)
		वापस;
	entry	= ring_buffer_event_data(event);
	entry->seqnum			= sample->seqnum;
	entry->duration			= sample->duration;
	entry->outer_duration		= sample->outer_duration;
	entry->बारtamp		= sample->बारtamp;
	entry->nmi_total_ts		= sample->nmi_total_ts;
	entry->nmi_count		= sample->nmi_count;
	entry->count			= sample->count;

	अगर (!call_filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit_nostack(buffer, event);
पूर्ण

/* Macros to encapsulate the समय capturing infraकाष्ठाure */
#घोषणा समय_प्रकारype	u64
#घोषणा समय_get()	trace_घड़ी_local()
#घोषणा समय_प्रकारo_us(x)	भाग_u64(x, 1000)
#घोषणा समय_sub(a, b)	((a) - (b))
#घोषणा init_समय(a, b)	(a = b)
#घोषणा समय_u64(a)	a

व्योम trace_hwlat_callback(bool enter)
अणु
	अगर (smp_processor_id() != nmi_cpu)
		वापस;

	/*
	 * Currently trace_घड़ी_local() calls sched_घड़ी() and the
	 * generic version is not NMI safe.
	 */
	अगर (!IS_ENABLED(CONFIG_GENERIC_SCHED_CLOCK)) अणु
		अगर (enter)
			nmi_ts_start = समय_get();
		अन्यथा
			nmi_total_ts += समय_get() - nmi_ts_start;
	पूर्ण

	अगर (enter)
		nmi_count++;
पूर्ण

/**
 * get_sample - sample the CPU TSC and look क्रम likely hardware latencies
 *
 * Used to repeatedly capture the CPU TSC (or similar), looking क्रम potential
 * hardware-induced latency. Called with पूर्णांकerrupts disabled and with
 * hwlat_data.lock held.
 */
अटल पूर्णांक get_sample(व्योम)
अणु
	काष्ठा trace_array *tr = hwlat_trace;
	काष्ठा hwlat_sample s;
	समय_प्रकारype start, t1, t2, last_t2;
	s64 dअगरf, outer_dअगरf, total, last_total = 0;
	u64 sample = 0;
	u64 thresh = tracing_thresh;
	u64 outer_sample = 0;
	पूर्णांक ret = -1;
	अचिन्हित पूर्णांक count = 0;

	करो_भाग(thresh, NSEC_PER_USEC); /* modअगरies पूर्णांकerval value */

	nmi_cpu = smp_processor_id();
	nmi_total_ts = 0;
	nmi_count = 0;
	/* Make sure NMIs see this first */
	barrier();

	trace_hwlat_callback_enabled = true;

	init_समय(last_t2, 0);
	start = समय_get(); /* start बारtamp */
	outer_dअगरf = 0;

	करो अणु

		t1 = समय_get();	/* we'll look क्रम a discontinuity */
		t2 = समय_get();

		अगर (समय_u64(last_t2)) अणु
			/* Check the delta from outer loop (t2 to next t1) */
			outer_dअगरf = समय_प्रकारo_us(समय_sub(t1, last_t2));
			/* This shouldn't happen */
			अगर (outer_dअगरf < 0) अणु
				pr_err(BANNER "time running backwards\n");
				जाओ out;
			पूर्ण
			अगर (outer_dअगरf > outer_sample)
				outer_sample = outer_dअगरf;
		पूर्ण
		last_t2 = t2;

		total = समय_प्रकारo_us(समय_sub(t2, start)); /* sample width */

		/* Check क्रम possible overflows */
		अगर (total < last_total) अणु
			pr_err("Time total overflowed\n");
			अवरोध;
		पूर्ण
		last_total = total;

		/* This checks the inner loop (t1 to t2) */
		dअगरf = समय_प्रकारo_us(समय_sub(t2, t1));     /* current dअगरf */

		अगर (dअगरf > thresh || outer_dअगरf > thresh) अणु
			अगर (!count)
				kसमय_get_real_ts64(&s.बारtamp);
			count++;
		पूर्ण

		/* This shouldn't happen */
		अगर (dअगरf < 0) अणु
			pr_err(BANNER "time running backwards\n");
			जाओ out;
		पूर्ण

		अगर (dअगरf > sample)
			sample = dअगरf; /* only want highest value */

	पूर्ण जबतक (total <= hwlat_data.sample_width);

	barrier(); /* finish the above in the view क्रम NMIs */
	trace_hwlat_callback_enabled = false;
	barrier(); /* Make sure nmi_total_ts is no दीर्घer updated */

	ret = 0;

	/* If we exceed the threshold value, we have found a hardware latency */
	अगर (sample > thresh || outer_sample > thresh) अणु
		u64 latency;

		ret = 1;

		/* We पढ़ो in microseconds */
		अगर (nmi_total_ts)
			करो_भाग(nmi_total_ts, NSEC_PER_USEC);

		hwlat_data.count++;
		s.seqnum = hwlat_data.count;
		s.duration = sample;
		s.outer_duration = outer_sample;
		s.nmi_total_ts = nmi_total_ts;
		s.nmi_count = nmi_count;
		s.count = count;
		trace_hwlat_sample(&s);

		latency = max(sample, outer_sample);

		/* Keep a running maximum ever recorded hardware latency */
		अगर (latency > tr->max_latency) अणु
			tr->max_latency = latency;
			latency_fsnotअगरy(tr);
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल काष्ठा cpumask save_cpumask;
अटल bool disable_migrate;

अटल व्योम move_to_next_cpu(व्योम)
अणु
	काष्ठा cpumask *current_mask = &save_cpumask;
	काष्ठा trace_array *tr = hwlat_trace;
	पूर्णांक next_cpu;

	अगर (disable_migrate)
		वापस;
	/*
	 * If क्रम some reason the user modअगरies the CPU affinity
	 * of this thपढ़ो, then stop migrating क्रम the duration
	 * of the current test.
	 */
	अगर (!cpumask_equal(current_mask, current->cpus_ptr))
		जाओ disable;

	get_online_cpus();
	cpumask_and(current_mask, cpu_online_mask, tr->tracing_cpumask);
	next_cpu = cpumask_next(smp_processor_id(), current_mask);
	put_online_cpus();

	अगर (next_cpu >= nr_cpu_ids)
		next_cpu = cpumask_first(current_mask);

	अगर (next_cpu >= nr_cpu_ids) /* Shouldn't happen! */
		जाओ disable;

	cpumask_clear(current_mask);
	cpumask_set_cpu(next_cpu, current_mask);

	sched_setaffinity(0, current_mask);
	वापस;

 disable:
	disable_migrate = true;
पूर्ण

/*
 * kthपढ़ो_fn - The CPU समय sampling/hardware latency detection kernel thपढ़ो
 *
 * Used to periodically sample the CPU TSC via a call to get_sample. We
 * disable पूर्णांकerrupts, which करोes (पूर्णांकentionally) पूर्णांकroduce latency since we
 * need to ensure nothing अन्यथा might be running (and thus preempting).
 * Obviously this should never be used in production environments.
 *
 * Executes one loop पूर्णांकeraction on each CPU in tracing_cpumask sysfs file.
 */
अटल पूर्णांक kthपढ़ो_fn(व्योम *data)
अणु
	u64 पूर्णांकerval;

	जबतक (!kthपढ़ो_should_stop()) अणु

		move_to_next_cpu();

		local_irq_disable();
		get_sample();
		local_irq_enable();

		mutex_lock(&hwlat_data.lock);
		पूर्णांकerval = hwlat_data.sample_winकरोw - hwlat_data.sample_width;
		mutex_unlock(&hwlat_data.lock);

		करो_भाग(पूर्णांकerval, USEC_PER_MSEC); /* modअगरies पूर्णांकerval value */

		/* Always sleep क्रम at least 1ms */
		अगर (पूर्णांकerval < 1)
			पूर्णांकerval = 1;

		अगर (msleep_पूर्णांकerruptible(पूर्णांकerval))
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * start_kthपढ़ो - Kick off the hardware latency sampling/detector kthपढ़ो
 *
 * This starts the kernel thपढ़ो that will sit and sample the CPU बारtamp
 * counter (TSC or similar) and look क्रम potential hardware latencies.
 */
अटल पूर्णांक start_kthपढ़ो(काष्ठा trace_array *tr)
अणु
	काष्ठा cpumask *current_mask = &save_cpumask;
	काष्ठा task_काष्ठा *kthपढ़ो;
	पूर्णांक next_cpu;

	अगर (hwlat_kthपढ़ो)
		वापस 0;

	/* Just pick the first CPU on first iteration */
	get_online_cpus();
	cpumask_and(current_mask, cpu_online_mask, tr->tracing_cpumask);
	put_online_cpus();
	next_cpu = cpumask_first(current_mask);

	kthपढ़ो = kthपढ़ो_create(kthपढ़ो_fn, शून्य, "hwlatd");
	अगर (IS_ERR(kthपढ़ो)) अणु
		pr_err(BANNER "could not start sampling thread\n");
		वापस -ENOMEM;
	पूर्ण

	cpumask_clear(current_mask);
	cpumask_set_cpu(next_cpu, current_mask);
	sched_setaffinity(kthपढ़ो->pid, current_mask);

	hwlat_kthपढ़ो = kthपढ़ो;
	wake_up_process(kthपढ़ो);

	वापस 0;
पूर्ण

/**
 * stop_kthपढ़ो - Inक्रमm the hardware latency sampling/detector kthपढ़ो to stop
 *
 * This kicks the running hardware latency sampling/detector kernel thपढ़ो and
 * tells it to stop sampling now. Use this on unload and at प्रणाली shutकरोwn.
 */
अटल व्योम stop_kthपढ़ो(व्योम)
अणु
	अगर (!hwlat_kthपढ़ो)
		वापस;
	kthपढ़ो_stop(hwlat_kthपढ़ो);
	hwlat_kthपढ़ो = शून्य;
पूर्ण

/*
 * hwlat_पढ़ो - Wrapper पढ़ो function क्रम पढ़ोing both winकरोw and width
 * @filp: The active खोलो file काष्ठाure
 * @ubuf: The userspace provided buffer to पढ़ो value पूर्णांकo
 * @cnt: The maximum number of bytes to पढ़ो
 * @ppos: The current "file" position
 *
 * This function provides a generic पढ़ो implementation क्रम the global state
 * "hwlat_data" काष्ठाure fileप्रणाली entries.
 */
अटल sमाप_प्रकार hwlat_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
			  माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर buf[U64STR_SIZE];
	u64 *entry = filp->निजी_data;
	u64 val;
	पूर्णांक len;

	अगर (!entry)
		वापस -EFAULT;

	अगर (cnt > माप(buf))
		cnt = माप(buf);

	val = *entry;

	len = snम_लिखो(buf, माप(buf), "%llu\n", val);

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, len);
पूर्ण

/**
 * hwlat_width_ग_लिखो - Write function क्रम "width" entry
 * @filp: The active खोलो file काष्ठाure
 * @ubuf: The user buffer that contains the value to ग_लिखो
 * @cnt: The maximum number of bytes to ग_लिखो to "file"
 * @ppos: The current position in @file
 *
 * This function provides a ग_लिखो implementation क्रम the "width" पूर्णांकerface
 * to the hardware latency detector. It can be used to configure
 * क्रम how many us of the total winकरोw us we will actively sample क्रम any
 * hardware-induced latency periods. Obviously, it is not possible to
 * sample स्थिरantly and have the प्रणाली respond to a sample पढ़ोer, or,
 * worse, without having the प्रणाली appear to have gone out to lunch. It
 * is enक्रमced that width is less that the total winकरोw size.
 */
अटल sमाप_प्रकार
hwlat_width_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		  माप_प्रकार cnt, loff_t *ppos)
अणु
	u64 val;
	पूर्णांक err;

	err = kम_से_अदीर्घl_from_user(ubuf, cnt, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&hwlat_data.lock);
	अगर (val < hwlat_data.sample_winकरोw)
		hwlat_data.sample_width = val;
	अन्यथा
		err = -EINVAL;
	mutex_unlock(&hwlat_data.lock);

	अगर (err)
		वापस err;

	वापस cnt;
पूर्ण

/**
 * hwlat_winकरोw_ग_लिखो - Write function क्रम "window" entry
 * @filp: The active खोलो file काष्ठाure
 * @ubuf: The user buffer that contains the value to ग_लिखो
 * @cnt: The maximum number of bytes to ग_लिखो to "file"
 * @ppos: The current position in @file
 *
 * This function provides a ग_लिखो implementation क्रम the "window" पूर्णांकerface
 * to the hardware latency detector. The winकरोw is the total समय
 * in us that will be considered one sample period. Conceptually, winकरोws
 * occur back-to-back and contain a sample width period during which
 * actual sampling occurs. Can be used to ग_लिखो a new total winकरोw size. It
 * is enक्रमced that any value written must be greater than the sample width
 * size, or an error results.
 */
अटल sमाप_प्रकार
hwlat_winकरोw_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		   माप_प्रकार cnt, loff_t *ppos)
अणु
	u64 val;
	पूर्णांक err;

	err = kम_से_अदीर्घl_from_user(ubuf, cnt, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&hwlat_data.lock);
	अगर (hwlat_data.sample_width < val)
		hwlat_data.sample_winकरोw = val;
	अन्यथा
		err = -EINVAL;
	mutex_unlock(&hwlat_data.lock);

	अगर (err)
		वापस err;

	वापस cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations width_fops = अणु
	.खोलो		= tracing_खोलो_generic,
	.पढ़ो		= hwlat_पढ़ो,
	.ग_लिखो		= hwlat_width_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations winकरोw_fops = अणु
	.खोलो		= tracing_खोलो_generic,
	.पढ़ो		= hwlat_पढ़ो,
	.ग_लिखो		= hwlat_winकरोw_ग_लिखो,
पूर्ण;

/**
 * init_tracefs - A function to initialize the tracefs पूर्णांकerface files
 *
 * This function creates entries in tracefs क्रम "hwlat_detector".
 * It creates the hwlat_detector directory in the tracing directory,
 * and within that directory is the count, width and winकरोw files to
 * change and view those values.
 */
अटल पूर्णांक init_tracefs(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा dentry *top_dir;

	ret = tracing_init_dentry();
	अगर (ret)
		वापस -ENOMEM;

	top_dir = tracefs_create_dir("hwlat_detector", शून्य);
	अगर (!top_dir)
		वापस -ENOMEM;

	hwlat_sample_winकरोw = tracefs_create_file("window", 0640,
						  top_dir,
						  &hwlat_data.sample_winकरोw,
						  &winकरोw_fops);
	अगर (!hwlat_sample_winकरोw)
		जाओ err;

	hwlat_sample_width = tracefs_create_file("width", 0644,
						 top_dir,
						 &hwlat_data.sample_width,
						 &width_fops);
	अगर (!hwlat_sample_width)
		जाओ err;

	वापस 0;

 err:
	tracefs_हटाओ(top_dir);
	वापस -ENOMEM;
पूर्ण

अटल व्योम hwlat_tracer_start(काष्ठा trace_array *tr)
अणु
	पूर्णांक err;

	err = start_kthपढ़ो(tr);
	अगर (err)
		pr_err(BANNER "Cannot start hwlat kthread\n");
पूर्ण

अटल व्योम hwlat_tracer_stop(काष्ठा trace_array *tr)
अणु
	stop_kthपढ़ो();
पूर्ण

अटल bool hwlat_busy;

अटल पूर्णांक hwlat_tracer_init(काष्ठा trace_array *tr)
अणु
	/* Only allow one instance to enable this */
	अगर (hwlat_busy)
		वापस -EBUSY;

	hwlat_trace = tr;

	disable_migrate = false;
	hwlat_data.count = 0;
	tr->max_latency = 0;
	save_tracing_thresh = tracing_thresh;

	/* tracing_thresh is in nsecs, we speak in usecs */
	अगर (!tracing_thresh)
		tracing_thresh = last_tracing_thresh;

	अगर (tracer_tracing_is_on(tr))
		hwlat_tracer_start(tr);

	hwlat_busy = true;

	वापस 0;
पूर्ण

अटल व्योम hwlat_tracer_reset(काष्ठा trace_array *tr)
अणु
	stop_kthपढ़ो();

	/* the tracing threshold is अटल between runs */
	last_tracing_thresh = tracing_thresh;

	tracing_thresh = save_tracing_thresh;
	hwlat_busy = false;
पूर्ण

अटल काष्ठा tracer hwlat_tracer __पढ़ो_mostly =
अणु
	.name		= "hwlat",
	.init		= hwlat_tracer_init,
	.reset		= hwlat_tracer_reset,
	.start		= hwlat_tracer_start,
	.stop		= hwlat_tracer_stop,
	.allow_instances = true,
पूर्ण;

__init अटल पूर्णांक init_hwlat_tracer(व्योम)
अणु
	पूर्णांक ret;

	mutex_init(&hwlat_data.lock);

	ret = रेजिस्टर_tracer(&hwlat_tracer);
	अगर (ret)
		वापस ret;

	init_tracefs();

	वापस 0;
पूर्ण
late_initcall(init_hwlat_tracer);
