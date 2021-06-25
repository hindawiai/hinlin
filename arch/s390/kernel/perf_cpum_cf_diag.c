<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Perक्रमmance event support क्रम s390x - CPU-measurement Counter Sets
 *
 *  Copyright IBM Corp. 2019, 2021
 *  Author(s): Hendrik Brueckner <brueckner@linux.ibm.com>
 *	       Thomas Richer <पंचांगricht@linux.ibm.com>
 */
#घोषणा KMSG_COMPONENT	"cpum_cf_diag"
#घोषणा pr_fmt(fmt)	KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/percpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/processor.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mutex.h>

#समावेश <यंत्र/ctl_reg.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/cpu_mcf.h>
#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/debug.h>

#समावेश <यंत्र/hwctrset.h>

#घोषणा	CF_DIAG_CTRSET_DEF		0xfeef	/* Counter set header mark */
						/* पूर्णांकerval in seconds */
अटल अचिन्हित पूर्णांक cf_diag_cpu_speed;
अटल debug_info_t *cf_diag_dbg;

काष्ठा cf_diag_csd अणु			/* Counter set data per CPU */
	माप_प्रकार used;			/* Bytes used in data/start */
	अचिन्हित अक्षर start[PAGE_SIZE];	/* Counter set at event start */
	अचिन्हित अक्षर data[PAGE_SIZE];	/* Counter set at event delete */
	अचिन्हित पूर्णांक sets;		/* # Counter set saved in data */
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा cf_diag_csd, cf_diag_csd);

/* Counter sets are stored as data stream in a page sized memory buffer and
 * exported to user space via raw data attached to the event sample data.
 * Each counter set starts with an eight byte header consisting of:
 * - a two byte eye catcher (0xfeef)
 * - a one byte counter set number
 * - a two byte counter set size (indicates the number of counters in this set)
 * - a three byte reserved value (must be zero) to make the header the same
 *   size as a counter value.
 * All counter values are eight byte in size.
 *
 * All counter sets are followed by a 64 byte trailer.
 * The trailer consists of a:
 * - flag field indicating valid fields when corresponding bit set
 * - the counter facility first and second version number
 * - the CPU speed अगर nonzero
 * - the समय stamp the counter sets have been collected
 * - the समय of day (TOD) base value
 * - the machine type.
 *
 * The counter sets are saved when the process is prepared to be executed on a
 * CPU and saved again when the process is going to be हटाओd from a CPU.
 * The dअगरference of both counter sets are calculated and stored in the event
 * sample data area.
 */

काष्ठा cf_ctrset_entry अणु	/* CPU-M CF counter set entry (8 byte) */
	अचिन्हित पूर्णांक def:16;	/* 0-15  Data Entry Format */
	अचिन्हित पूर्णांक set:16;	/* 16-31 Counter set identअगरier */
	अचिन्हित पूर्णांक ctr:16;	/* 32-47 Number of stored counters */
	अचिन्हित पूर्णांक res1:16;	/* 48-63 Reserved */
पूर्ण;

काष्ठा cf_trailer_entry अणु	/* CPU-M CF_DIAG trailer (64 byte) */
	/* 0 - 7 */
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक घड़ी_base:1;	/* TOD घड़ी base set */
			अचिन्हित पूर्णांक speed:1;		/* CPU speed set */
			/* Measurement alerts */
			अचिन्हित पूर्णांक mtda:1;	/* Loss of MT ctr. data alert */
			अचिन्हित पूर्णांक caca:1;	/* Counter auth. change alert */
			अचिन्हित पूर्णांक lcda:1;	/* Loss of counter data alert */
		पूर्ण;
		अचिन्हित दीर्घ flags;	/* 0-63    All indicators */
	पूर्ण;
	/* 8 - 15 */
	अचिन्हित पूर्णांक cfvn:16;			/* 64-79   Ctr First Version */
	अचिन्हित पूर्णांक csvn:16;			/* 80-95   Ctr Second Version */
	अचिन्हित पूर्णांक cpu_speed:32;		/* 96-127  CPU speed */
	/* 16 - 23 */
	अचिन्हित दीर्घ बारtamp;		/* 128-191 Timestamp (TOD) */
	/* 24 - 55 */
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ progusage1;
			अचिन्हित दीर्घ progusage2;
			अचिन्हित दीर्घ progusage3;
			अचिन्हित दीर्घ tod_base;
		पूर्ण;
		अचिन्हित दीर्घ progusage[4];
	पूर्ण;
	/* 56 - 63 */
	अचिन्हित पूर्णांक mach_type:16;		/* Machine type */
	अचिन्हित पूर्णांक res1:16;			/* Reserved */
	अचिन्हित पूर्णांक res2:32;			/* Reserved */
पूर्ण;

/* Create the trailer data at the end of a page. */
अटल व्योम cf_diag_trailer(काष्ठा cf_trailer_entry *te)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	काष्ठा cpuid cpuid;

	te->cfvn = cpuhw->info.cfvn;		/* Counter version numbers */
	te->csvn = cpuhw->info.csvn;

	get_cpu_id(&cpuid);			/* Machine type */
	te->mach_type = cpuid.machine;
	te->cpu_speed = cf_diag_cpu_speed;
	अगर (te->cpu_speed)
		te->speed = 1;
	te->घड़ी_base = 1;			/* Save घड़ी base */
	te->tod_base = tod_घड़ी_base.tod;
	te->बारtamp = get_tod_घड़ी_fast();
पूर्ण

/*
 * Change the CPUMF state to active.
 * Enable and activate the CPU-counter sets according
 * to the per-cpu control state.
 */
अटल व्योम cf_diag_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	पूर्णांक err;

	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s pmu %p cpu %d flags %#x state %#llx\n",
			    __func__, pmu, smp_processor_id(), cpuhw->flags,
			    cpuhw->state);
	अगर (cpuhw->flags & PMU_F_ENABLED)
		वापस;

	err = lcctl(cpuhw->state);
	अगर (err) अणु
		pr_err("Enabling the performance measuring unit "
		       "failed with rc=%x\n", err);
		वापस;
	पूर्ण
	cpuhw->flags |= PMU_F_ENABLED;
पूर्ण

/*
 * Change the CPUMF state to inactive.
 * Disable and enable (inactive) the CPU-counter sets according
 * to the per-cpu control state.
 */
अटल व्योम cf_diag_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	u64 inactive;
	पूर्णांक err;

	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s pmu %p cpu %d flags %#x state %#llx\n",
			    __func__, pmu, smp_processor_id(), cpuhw->flags,
			    cpuhw->state);
	अगर (!(cpuhw->flags & PMU_F_ENABLED))
		वापस;

	inactive = cpuhw->state & ~((1 << CPUMF_LCCTL_ENABLE_SHIFT) - 1);
	err = lcctl(inactive);
	अगर (err) अणु
		pr_err("Disabling the performance measuring unit "
		       "failed with rc=%x\n", err);
		वापस;
	पूर्ण
	cpuhw->flags &= ~PMU_F_ENABLED;
पूर्ण

/* Number of perf events counting hardware events */
अटल atomic_t cf_diag_events = ATOMIC_INIT(0);
/* Used to aव्योम races in calling reserve/release_cpumf_hardware */
अटल DEFINE_MUTEX(cf_diag_reserve_mutex);

/* Release the PMU अगर event is the last perf event */
अटल व्योम cf_diag_perf_event_destroy(काष्ठा perf_event *event)
अणु
	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s event %p cpu %d cf_diag_events %d\n",
			    __func__, event, smp_processor_id(),
			    atomic_पढ़ो(&cf_diag_events));
	अगर (atomic_dec_वापस(&cf_diag_events) == 0)
		__kernel_cpumcf_end();
पूर्ण

अटल पूर्णांक get_authctrsets(व्योम)
अणु
	काष्ठा cpu_cf_events *cpuhw;
	अचिन्हित दीर्घ auth = 0;
	क्रमागत cpumf_ctr_set i;

	cpuhw = &get_cpu_var(cpu_cf_events);
	क्रम (i = CPUMF_CTR_SET_BASIC; i < CPUMF_CTR_SET_MAX; ++i) अणु
		अगर (cpuhw->info.auth_ctl & cpumf_ctr_ctl[i])
			auth |= cpumf_ctr_ctl[i];
	पूर्ण
	put_cpu_var(cpu_cf_events);
	वापस auth;
पूर्ण

/* Setup the event. Test क्रम authorized counter sets and only include counter
 * sets which are authorized at the समय of the setup. Including unauthorized
 * counter sets result in specअगरication exception (and panic).
 */
अटल पूर्णांक __hw_perf_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	पूर्णांक err = 0;

	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s event %p cpu %d\n", __func__,
			    event, event->cpu);

	event->hw.config = attr->config;

	/* Add all authorized counter sets to config_base. The
	 * the hardware init function is either called per-cpu or just once
	 * क्रम all CPUS (event->cpu == -1).  This depends on the whether
	 * counting is started क्रम all CPUs or on a per workload base where
	 * the perf event moves from one CPU to another CPU.
	 * Checking the authorization on any CPU is fine as the hardware
	 * applies the same authorization settings to all CPUs.
	 */
	event->hw.config_base = get_authctrsets();

	/* No authorized counter sets, nothing to count/sample */
	अगर (!event->hw.config_base) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* Set sample_period to indicate sampling */
	event->hw.sample_period = attr->sample_period;
	local64_set(&event->hw.period_left, event->hw.sample_period);
	event->hw.last_period  = event->hw.sample_period;
out:
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s err %d config_base %#lx\n",
			    __func__, err, event->hw.config_base);
	वापस err;
पूर्ण

/* Return 0 अगर the CPU-measurement counter facility is currently मुक्त
 * and an error otherwise.
 */
अटल पूर्णांक cf_diag_perf_event_inuse(व्योम)
अणु
	पूर्णांक err = 0;

	अगर (!atomic_inc_not_zero(&cf_diag_events)) अणु
		mutex_lock(&cf_diag_reserve_mutex);
		अगर (atomic_पढ़ो(&cf_diag_events) == 0 &&
		    __kernel_cpumcf_begin())
			err = -EBUSY;
		अन्यथा
			err = atomic_inc_वापस(&cf_diag_events);
		mutex_unlock(&cf_diag_reserve_mutex);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cf_diag_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	पूर्णांक err = -ENOENT;

	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s event %p cpu %d config %#llx type:%u "
			    "sample_type %#llx cf_diag_events %d\n", __func__,
			    event, event->cpu, attr->config, event->pmu->type,
			    attr->sample_type, atomic_पढ़ो(&cf_diag_events));

	अगर (event->attr.config != PERF_EVENT_CPUM_CF_DIAG ||
	    event->attr.type != event->pmu->type)
		जाओ out;

	/* Raw events are used to access counters directly,
	 * hence करो not permit excludes.
	 * This event is usesless without PERF_SAMPLE_RAW to वापस counter set
	 * values as raw data.
	 */
	अगर (attr->exclude_kernel || attr->exclude_user || attr->exclude_hv ||
	    !(attr->sample_type & (PERF_SAMPLE_CPU | PERF_SAMPLE_RAW))) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/* Initialize क्रम using the CPU-measurement counter facility */
	err = cf_diag_perf_event_inuse();
	अगर (err < 0)
		जाओ out;
	event->destroy = cf_diag_perf_event_destroy;

	err = __hw_perf_event_init(event);
	अगर (unlikely(err))
		event->destroy(event);
out:
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s err %d\n", __func__, err);
	वापस err;
पूर्ण

अटल व्योम cf_diag_पढ़ो(काष्ठा perf_event *event)
अणु
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s event %p\n", __func__, event);
पूर्ण

/* Calculate memory needed to store all counter sets together with header and
 * trailer data. This is independend of the counter set authorization which
 * can vary depending on the configuration.
 */
अटल माप_प्रकार cf_diag_ctrset_maxsize(काष्ठा cpumf_ctr_info *info)
अणु
	माप_प्रकार max_size = माप(काष्ठा cf_trailer_entry);
	क्रमागत cpumf_ctr_set i;

	क्रम (i = CPUMF_CTR_SET_BASIC; i < CPUMF_CTR_SET_MAX; ++i) अणु
		माप_प्रकार size = cpum_cf_ctrset_size(i, info);

		अगर (size)
			max_size += size * माप(u64) +
				    माप(काष्ठा cf_ctrset_entry);
	पूर्ण
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s max_size %zu\n", __func__,
			    max_size);

	वापस max_size;
पूर्ण

/* Read a counter set. The counter set number determines which counter set and
 * the CPUM-CF first and second version number determine the number of
 * available counters in this counter set.
 * Each counter set starts with header containing the counter set number and
 * the number of 8 byte counters.
 *
 * The functions वापसs the number of bytes occupied by this counter set
 * including the header.
 * If there is no counter in the counter set, this counter set is useless and
 * zero is वापसed on this हाल.
 */
अटल माप_प्रकार cf_diag_अ_लोtrset(काष्ठा cf_ctrset_entry *ctrdata, पूर्णांक ctrset,
				माप_प्रकार room)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	माप_प्रकार ctrset_size, need = 0;
	पूर्णांक rc = 3;				/* Assume ग_लिखो failure */

	ctrdata->def = CF_DIAG_CTRSET_DEF;
	ctrdata->set = ctrset;
	ctrdata->res1 = 0;
	ctrset_size = cpum_cf_ctrset_size(ctrset, &cpuhw->info);

	अगर (ctrset_size) अणु			/* Save data */
		need = ctrset_size * माप(u64) + माप(*ctrdata);
		अगर (need <= room)
			rc = ctr_stccपंचांग(ctrset, ctrset_size,
					(u64 *)(ctrdata + 1));
		अगर (rc != 3)
			ctrdata->ctr = ctrset_size;
		अन्यथा
			need = 0;
	पूर्ण

	debug_प्र_लिखो_event(cf_diag_dbg, 6,
			    "%s ctrset %d ctrset_size %zu cfvn %d csvn %d"
			    " need %zd rc %d\n",
			    __func__, ctrset, ctrset_size, cpuhw->info.cfvn,
			    cpuhw->info.csvn, need, rc);
	वापस need;
पूर्ण

/* Read out all counter sets and save them in the provided data buffer.
 * The last 64 byte host an artअगरicial trailer entry.
 */
अटल माप_प्रकार cf_diag_अ_लोtr(व्योम *data, माप_प्रकार sz, अचिन्हित दीर्घ auth)
अणु
	काष्ठा cf_trailer_entry *trailer;
	माप_प्रकार offset = 0, करोne;
	पूर्णांक i;

	स_रखो(data, 0, sz);
	sz -= माप(*trailer);			/* Always room क्रम trailer */
	क्रम (i = CPUMF_CTR_SET_BASIC; i < CPUMF_CTR_SET_MAX; ++i) अणु
		काष्ठा cf_ctrset_entry *ctrdata = data + offset;

		अगर (!(auth & cpumf_ctr_ctl[i]))
			जारी;	/* Counter set not authorized */

		करोne = cf_diag_अ_लोtrset(ctrdata, i, sz - offset);
		offset += करोne;
		debug_प्र_लिखो_event(cf_diag_dbg, 6,
				    "%s ctrset %d offset %zu done %zu\n",
				     __func__, i, offset, करोne);
	पूर्ण
	trailer = data + offset;
	cf_diag_trailer(trailer);
	वापस offset + माप(*trailer);
पूर्ण

/* Calculate the dअगरference क्रम each counter in a counter set. */
अटल व्योम cf_diag_dअगरfctrset(u64 *pstart, u64 *pstop, पूर्णांक counters)
अणु
	क्रम (; --counters >= 0; ++pstart, ++pstop)
		अगर (*pstop >= *pstart)
			*pstop -= *pstart;
		अन्यथा
			*pstop = *pstart - *pstop;
पूर्ण

/* Scan the counter sets and calculate the dअगरference of each counter
 * in each set. The result is the increment of each counter during the
 * period the counter set has been activated.
 *
 * Return true on success.
 */
अटल पूर्णांक cf_diag_dअगरfctr(काष्ठा cf_diag_csd *csd, अचिन्हित दीर्घ auth)
अणु
	काष्ठा cf_trailer_entry *trailer_start, *trailer_stop;
	काष्ठा cf_ctrset_entry *ctrstart, *ctrstop;
	माप_प्रकार offset = 0;

	auth &= (1 << CPUMF_LCCTL_ENABLE_SHIFT) - 1;
	करो अणु
		ctrstart = (काष्ठा cf_ctrset_entry *)(csd->start + offset);
		ctrstop = (काष्ठा cf_ctrset_entry *)(csd->data + offset);

		अगर (स_भेद(ctrstop, ctrstart, माप(*ctrstop))) अणु
			pr_err("cpum_cf_diag counter set compare error "
				"in set %i\n", ctrstart->set);
			वापस 0;
		पूर्ण
		auth &= ~cpumf_ctr_ctl[ctrstart->set];
		अगर (ctrstart->def == CF_DIAG_CTRSET_DEF) अणु
			cf_diag_dअगरfctrset((u64 *)(ctrstart + 1),
					  (u64 *)(ctrstop + 1), ctrstart->ctr);
			offset += ctrstart->ctr * माप(u64) +
				  माप(*ctrstart);
		पूर्ण
		debug_प्र_लिखो_event(cf_diag_dbg, 6,
				    "%s set %d ctr %d offset %zu auth %lx\n",
				    __func__, ctrstart->set, ctrstart->ctr,
				    offset, auth);
	पूर्ण जबतक (ctrstart->def && auth);

	/* Save समय_stamp from start of event in stop's trailer */
	trailer_start = (काष्ठा cf_trailer_entry *)(csd->start + offset);
	trailer_stop = (काष्ठा cf_trailer_entry *)(csd->data + offset);
	trailer_stop->progusage[0] = trailer_start->बारtamp;

	वापस 1;
पूर्ण

/* Create perf event sample with the counter sets as raw data.	The sample
 * is then pushed to the event subप्रणाली and the function checks क्रम
 * possible event overflows. If an event overflow occurs, the PMU is
 * stopped.
 *
 * Return non-zero अगर an event overflow occurred.
 */
अटल पूर्णांक cf_diag_push_sample(काष्ठा perf_event *event,
			       काष्ठा cf_diag_csd *csd)
अणु
	काष्ठा perf_sample_data data;
	काष्ठा perf_raw_record raw;
	काष्ठा pt_regs regs;
	पूर्णांक overflow;

	/* Setup perf sample */
	perf_sample_data_init(&data, 0, event->hw.last_period);
	स_रखो(&regs, 0, माप(regs));
	स_रखो(&raw, 0, माप(raw));

	अगर (event->attr.sample_type & PERF_SAMPLE_CPU)
		data.cpu_entry.cpu = event->cpu;
	अगर (event->attr.sample_type & PERF_SAMPLE_RAW) अणु
		raw.frag.size = csd->used;
		raw.frag.data = csd->data;
		raw.size = csd->used;
		data.raw = &raw;
	पूर्ण

	overflow = perf_event_overflow(event, &data, &regs);
	debug_प्र_लिखो_event(cf_diag_dbg, 6,
			    "%s event %p cpu %d sample_type %#llx raw %d "
			    "ov %d\n", __func__, event, event->cpu,
			    event->attr.sample_type, raw.size, overflow);
	अगर (overflow)
		event->pmu->stop(event, 0);

	perf_event_update_userpage(event);
	वापस overflow;
पूर्ण

अटल व्योम cf_diag_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	काष्ठा cf_diag_csd *csd = this_cpu_ptr(&cf_diag_csd);
	काष्ठा hw_perf_event *hwc = &event->hw;

	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s event %p cpu %d flags %#x hwc-state %#x\n",
			    __func__, event, event->cpu, flags, hwc->state);
	अगर (WARN_ON_ONCE(!(hwc->state & PERF_HES_STOPPED)))
		वापस;

	/* (Re-)enable and activate all counter sets */
	lcctl(0);		/* Reset counter sets */
	hwc->state = 0;
	ctr_set_multiple_enable(&cpuhw->state, hwc->config_base);
	lcctl(cpuhw->state);	/* Enable counter sets */
	csd->used = cf_diag_अ_लोtr(csd->start, माप(csd->start),
				   event->hw.config_base);
	ctr_set_multiple_start(&cpuhw->state, hwc->config_base);
	/* Function cf_diag_enable() starts the counter sets. */
पूर्ण

अटल व्योम cf_diag_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	काष्ठा cf_diag_csd *csd = this_cpu_ptr(&cf_diag_csd);
	काष्ठा hw_perf_event *hwc = &event->hw;

	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s event %p cpu %d flags %#x hwc-state %#x\n",
			    __func__, event, event->cpu, flags, hwc->state);

	/* Deactivate all counter sets */
	ctr_set_multiple_stop(&cpuhw->state, hwc->config_base);
	local64_inc(&event->count);
	csd->used = cf_diag_अ_लोtr(csd->data, माप(csd->data),
				   event->hw.config_base);
	अगर (cf_diag_dअगरfctr(csd, event->hw.config_base))
		cf_diag_push_sample(event, csd);
	hwc->state |= PERF_HES_STOPPED;
पूर्ण

अटल पूर्णांक cf_diag_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	पूर्णांक err = 0;

	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s event %p cpu %d flags %#x cpuhw %p\n",
			    __func__, event, event->cpu, flags, cpuhw);

	अगर (cpuhw->flags & PMU_F_IN_USE) अणु
		err = -EAGAIN;
		जाओ out;
	पूर्ण

	event->hw.state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	cpuhw->flags |= PMU_F_IN_USE;
	अगर (flags & PERF_EF_START)
		cf_diag_start(event, PERF_EF_RELOAD);
out:
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s err %d\n", __func__, err);
	वापस err;
पूर्ण

अटल व्योम cf_diag_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);

	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s event %p cpu %d flags %#x\n",
			   __func__, event, event->cpu, flags);

	cf_diag_stop(event, PERF_EF_UPDATE);
	ctr_set_multiple_stop(&cpuhw->state, event->hw.config_base);
	ctr_set_multiple_disable(&cpuhw->state, event->hw.config_base);
	cpuhw->flags &= ~PMU_F_IN_USE;
पूर्ण

/* Default counter set events and क्रमmat attribute groups */

CPUMF_EVENT_ATTR(CF_DIAG, CF_DIAG, PERF_EVENT_CPUM_CF_DIAG);

अटल काष्ठा attribute *cf_diag_events_attr[] = अणु
	CPUMF_EVENT_PTR(CF_DIAG, CF_DIAG),
	शून्य,
पूर्ण;

PMU_FORMAT_ATTR(event, "config:0-63");

अटल काष्ठा attribute *cf_diag_क्रमmat_attr[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cf_diag_events_group = अणु
	.name = "events",
	.attrs = cf_diag_events_attr,
पूर्ण;
अटल काष्ठा attribute_group cf_diag_क्रमmat_group = अणु
	.name = "format",
	.attrs = cf_diag_क्रमmat_attr,
पूर्ण;
अटल स्थिर काष्ठा attribute_group *cf_diag_attr_groups[] = अणु
	&cf_diag_events_group,
	&cf_diag_क्रमmat_group,
	शून्य,
पूर्ण;

/* Perक्रमmance monitoring unit क्रम s390x */
अटल काष्ठा pmu cf_diag = अणु
	.task_ctx_nr  = perf_sw_context,
	.pmu_enable   = cf_diag_enable,
	.pmu_disable  = cf_diag_disable,
	.event_init   = cf_diag_event_init,
	.add	      = cf_diag_add,
	.del	      = cf_diag_del,
	.start	      = cf_diag_start,
	.stop	      = cf_diag_stop,
	.पढ़ो	      = cf_diag_पढ़ो,

	.attr_groups  = cf_diag_attr_groups
पूर्ण;

/* Get the CPU speed, try sampling facility first and CPU attributes second. */
अटल व्योम cf_diag_get_cpu_speed(व्योम)
अणु
	अगर (cpum_sf_avail()) अणु			/* Sampling facility first */
		काष्ठा hws_qsi_info_block si;

		स_रखो(&si, 0, माप(si));
		अगर (!qsi(&si)) अणु
			cf_diag_cpu_speed = si.cpu_speed;
			वापस;
		पूर्ण
	पूर्ण

	अगर (test_facility(34)) अणु		/* CPU speed extract अटल part */
		अचिन्हित दीर्घ mhz = __ecag(ECAG_CPU_ATTRIBUTE, 0);

		अगर (mhz != -1UL)
			cf_diag_cpu_speed = mhz & 0xffffffff;
	पूर्ण
पूर्ण

/* Code to create device and file I/O operations */
अटल atomic_t ctrset_खोलोcnt = ATOMIC_INIT(0);	/* Excl. access */

अटल पूर्णांक cf_diag_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक err = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (atomic_xchg(&ctrset_खोलोcnt, 1))
		वापस -EBUSY;

	/* Aव्योम concurrent access with perf_event_खोलो() प्रणाली call */
	mutex_lock(&cf_diag_reserve_mutex);
	अगर (atomic_पढ़ो(&cf_diag_events) || __kernel_cpumcf_begin())
		err = -EBUSY;
	mutex_unlock(&cf_diag_reserve_mutex);
	अगर (err) अणु
		atomic_set(&ctrset_खोलोcnt, 0);
		वापस err;
	पूर्ण
	file->निजी_data = शून्य;
	debug_प्र_लिखो_event(cf_diag_dbg, 2, "%s\n", __func__);
	/* nonseekable_खोलो() never fails */
	वापस nonseekable_खोलो(inode, file);
पूर्ण

/* Variables क्रम ioctl() पूर्णांकerface support */
अटल DEFINE_MUTEX(cf_diag_ctrset_mutex);
अटल काष्ठा cf_diag_ctrset अणु
	अचिन्हित दीर्घ ctrset;		/* Bit mask of counter set to पढ़ो */
	cpumask_t mask;			/* CPU mask to पढ़ो from */
पूर्ण cf_diag_ctrset;

अटल व्योम cf_diag_ctrset_clear(व्योम)
अणु
	cpumask_clear(&cf_diag_ctrset.mask);
	cf_diag_ctrset.ctrset = 0;
पूर्ण

अटल व्योम cf_diag_release_cpu(व्योम *p)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);

	debug_प्र_लिखो_event(cf_diag_dbg, 3, "%s cpu %d\n", __func__,
			    smp_processor_id());
	lcctl(0);		/* Reset counter sets */
	cpuhw->state = 0;	/* Save state in CPU hardware state */
पूर्ण

/* Release function is also called when application माला_लो terminated without
 * करोing a proper ioctl(..., S390_HWCTR_STOP, ...) command.
 * Since only one application is allowed to खोलो the device, simple stop all
 * CPU counter sets.
 */
अटल पूर्णांक cf_diag_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	on_each_cpu(cf_diag_release_cpu, शून्य, 1);
	cf_diag_ctrset_clear();
	atomic_set(&ctrset_खोलोcnt, 0);
	__kernel_cpumcf_end();
	debug_प्र_लिखो_event(cf_diag_dbg, 2, "%s\n", __func__);
	वापस 0;
पूर्ण

काष्ठा cf_diag_call_on_cpu_parm अणु	/* Parm काष्ठा क्रम smp_call_on_cpu */
	अचिन्हित पूर्णांक sets;		/* Counter set bit mask */
	atomic_t cpus_ack;		/* # CPUs successfully executed func */
पूर्ण;

अटल पूर्णांक cf_diag_all_copy(अचिन्हित दीर्घ arg, cpumask_t *mask)
अणु
	काष्ठा s390_ctrset_पढ़ो __user *ctrset_पढ़ो;
	अचिन्हित पूर्णांक cpu, cpus, rc;
	व्योम __user *uptr;

	ctrset_पढ़ो = (काष्ठा s390_ctrset_पढ़ो __user *)arg;
	uptr = ctrset_पढ़ो->data;
	क्रम_each_cpu(cpu, mask) अणु
		काष्ठा cf_diag_csd *csd = per_cpu_ptr(&cf_diag_csd, cpu);
		काष्ठा s390_ctrset_cpudata __user *ctrset_cpudata;

		ctrset_cpudata = uptr;
		debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s cpu %d used %zd\n",
				    __func__, cpu, csd->used);
		rc  = put_user(cpu, &ctrset_cpudata->cpu_nr);
		rc |= put_user(csd->sets, &ctrset_cpudata->no_sets);
		rc |= copy_to_user(ctrset_cpudata->data, csd->data, csd->used);
		अगर (rc)
			वापस -EFAULT;
		uptr += माप(काष्ठा s390_ctrset_cpudata) + csd->used;
		cond_resched();
	पूर्ण
	cpus = cpumask_weight(mask);
	अगर (put_user(cpus, &ctrset_पढ़ो->no_cpus))
		वापस -EFAULT;
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s copied %ld\n",
			    __func__, uptr - (व्योम __user *)ctrset_पढ़ो->data);
	वापस 0;
पूर्ण

अटल माप_प्रकार cf_diag_cpuset_पढ़ो(काष्ठा s390_ctrset_setdata *p, पूर्णांक ctrset,
				  पूर्णांक ctrset_size, माप_प्रकार room)
अणु
	माप_प्रकार need = 0;
	पूर्णांक rc = -1;

	need = माप(*p) + माप(u64) * ctrset_size;
	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s room %zd need %zd set %#x set_size %d\n",
			    __func__, room, need, ctrset, ctrset_size);
	अगर (need <= room) अणु
		p->set = cpumf_ctr_ctl[ctrset];
		p->no_cnts = ctrset_size;
		rc = ctr_stccपंचांग(ctrset, ctrset_size, (u64 *)p->cv);
		अगर (rc == 3)		/* Nothing stored */
			need = 0;
	पूर्ण
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s need %zd rc %d\n", __func__,
			    need, rc);
	वापस need;
पूर्ण

/* Read all counter sets. Since the perf_event_खोलो() प्रणाली call with
 * event cpum_cf_diag/.../ is blocked when this पूर्णांकerface is active, reuse
 * the perf_event_खोलो() data buffer to store the counter sets.
 */
अटल व्योम cf_diag_cpu_पढ़ो(व्योम *parm)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	काष्ठा cf_diag_csd *csd = this_cpu_ptr(&cf_diag_csd);
	काष्ठा cf_diag_call_on_cpu_parm *p = parm;
	पूर्णांक set, set_size;
	माप_प्रकार space;

	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s new %#x flags %#x state %#llx\n",
			    __func__, p->sets, cpuhw->flags,
			    cpuhw->state);
	/* No data saved yet */
	csd->used = 0;
	csd->sets = 0;
	स_रखो(csd->data, 0, माप(csd->data));

	/* Scan the counter sets */
	क्रम (set = CPUMF_CTR_SET_BASIC; set < CPUMF_CTR_SET_MAX; ++set) अणु
		काष्ठा s390_ctrset_setdata *sp = (व्योम *)csd->data + csd->used;

		अगर (!(p->sets & cpumf_ctr_ctl[set]))
			जारी;	/* Counter set not in list */
		set_size = cpum_cf_ctrset_size(set, &cpuhw->info);
		space = माप(csd->data) - csd->used;
		space = cf_diag_cpuset_पढ़ो(sp, set, set_size, space);
		अगर (space) अणु
			csd->used += space;
			csd->sets += 1;
		पूर्ण
		debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s sp %px space %zd\n",
				    __func__, sp, space);
	पूर्ण
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s sets %d used %zd\n", __func__,
			    csd->sets, csd->used);
पूर्ण

अटल पूर्णांक cf_diag_all_पढ़ो(अचिन्हित दीर्घ arg)
अणु
	काष्ठा cf_diag_call_on_cpu_parm p;
	cpumask_var_t mask;
	पूर्णांक rc;

	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s\n", __func__);
	अगर (!alloc_cpumask_var(&mask, GFP_KERNEL))
		वापस -ENOMEM;

	p.sets = cf_diag_ctrset.ctrset;
	cpumask_and(mask, &cf_diag_ctrset.mask, cpu_online_mask);
	on_each_cpu_mask(mask, cf_diag_cpu_पढ़ो, &p, 1);
	rc = cf_diag_all_copy(arg, mask);
	मुक्त_cpumask_var(mask);
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s rc %d\n", __func__, rc);
	वापस rc;
पूर्ण

/* Stop all counter sets via ioctl पूर्णांकerface */
अटल व्योम cf_diag_ioctl_off(व्योम *parm)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	काष्ठा cf_diag_call_on_cpu_parm *p = parm;
	पूर्णांक rc;

	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s new %#x flags %#x state %#llx\n",
			    __func__, p->sets, cpuhw->flags,
			    cpuhw->state);

	ctr_set_multiple_disable(&cpuhw->state, p->sets);
	ctr_set_multiple_stop(&cpuhw->state, p->sets);
	rc = lcctl(cpuhw->state);		/* Stop counter sets */
	अगर (!cpuhw->state)
		cpuhw->flags &= ~PMU_F_IN_USE;
	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s rc %d flags %#x state %#llx\n", __func__,
			     rc, cpuhw->flags, cpuhw->state);
पूर्ण

/* Start counter sets on particular CPU */
अटल व्योम cf_diag_ioctl_on(व्योम *parm)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	काष्ठा cf_diag_call_on_cpu_parm *p = parm;
	पूर्णांक rc;

	debug_प्र_लिखो_event(cf_diag_dbg, 5,
			    "%s new %#x flags %#x state %#llx\n",
			    __func__, p->sets, cpuhw->flags,
			    cpuhw->state);

	अगर (!(cpuhw->flags & PMU_F_IN_USE))
		cpuhw->state = 0;
	cpuhw->flags |= PMU_F_IN_USE;
	rc = lcctl(cpuhw->state);		/* Reset unused counter sets */
	ctr_set_multiple_enable(&cpuhw->state, p->sets);
	ctr_set_multiple_start(&cpuhw->state, p->sets);
	rc |= lcctl(cpuhw->state);		/* Start counter sets */
	अगर (!rc)
		atomic_inc(&p->cpus_ack);
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s rc %d state %#llx\n",
			    __func__, rc, cpuhw->state);
पूर्ण

अटल पूर्णांक cf_diag_all_stop(व्योम)
अणु
	काष्ठा cf_diag_call_on_cpu_parm p = अणु
		.sets = cf_diag_ctrset.ctrset,
	पूर्ण;
	cpumask_var_t mask;

	अगर (!alloc_cpumask_var(&mask, GFP_KERNEL))
		वापस -ENOMEM;
	cpumask_and(mask, &cf_diag_ctrset.mask, cpu_online_mask);
	on_each_cpu_mask(mask, cf_diag_ioctl_off, &p, 1);
	मुक्त_cpumask_var(mask);
	वापस 0;
पूर्ण

अटल पूर्णांक cf_diag_all_start(व्योम)
अणु
	काष्ठा cf_diag_call_on_cpu_parm p = अणु
		.sets = cf_diag_ctrset.ctrset,
		.cpus_ack = ATOMIC_INIT(0),
	पूर्ण;
	cpumask_var_t mask;
	पूर्णांक rc = 0;

	अगर (!alloc_cpumask_var(&mask, GFP_KERNEL))
		वापस -ENOMEM;
	cpumask_and(mask, &cf_diag_ctrset.mask, cpu_online_mask);
	on_each_cpu_mask(mask, cf_diag_ioctl_on, &p, 1);
	अगर (atomic_पढ़ो(&p.cpus_ack) != cpumask_weight(mask)) अणु
		on_each_cpu_mask(mask, cf_diag_ioctl_off, &p, 1);
		rc = -EIO;
	पूर्ण
	मुक्त_cpumask_var(mask);
	वापस rc;
पूर्ण

/* Return the maximum required space क्रम all possible CPUs in हाल one
 * CPU will be onlined during the START, READ, STOP cycles.
 * To find out the size of the counter sets, any one CPU will करो. They
 * all have the same counter sets.
 */
अटल माप_प्रकार cf_diag_needspace(अचिन्हित पूर्णांक sets)
अणु
	काष्ठा cpu_cf_events *cpuhw = get_cpu_ptr(&cpu_cf_events);
	माप_प्रकार bytes = 0;
	पूर्णांक i;

	क्रम (i = CPUMF_CTR_SET_BASIC; i < CPUMF_CTR_SET_MAX; ++i) अणु
		अगर (!(sets & cpumf_ctr_ctl[i]))
			जारी;
		bytes += cpum_cf_ctrset_size(i, &cpuhw->info) * माप(u64) +
			 माप(((काष्ठा s390_ctrset_setdata *)0)->set) +
			 माप(((काष्ठा s390_ctrset_setdata *)0)->no_cnts);
	पूर्ण
	bytes = माप(((काष्ठा s390_ctrset_पढ़ो *)0)->no_cpus) + nr_cpu_ids *
		(bytes + माप(((काष्ठा s390_ctrset_cpudata *)0)->cpu_nr) +
		     माप(((काष्ठा s390_ctrset_cpudata *)0)->no_sets));
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s bytes %ld\n", __func__,
			    bytes);
	put_cpu_ptr(&cpu_cf_events);
	वापस bytes;
पूर्ण

अटल दीर्घ cf_diag_ioctl_पढ़ो(अचिन्हित दीर्घ arg)
अणु
	काष्ठा s390_ctrset_पढ़ो पढ़ो;
	पूर्णांक ret = 0;

	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s\n", __func__);
	अगर (copy_from_user(&पढ़ो, (अक्षर __user *)arg, माप(पढ़ो)))
		वापस -EFAULT;
	ret = cf_diag_all_पढ़ो(arg);
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s ret %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल दीर्घ cf_diag_ioctl_stop(व्योम)
अणु
	पूर्णांक ret;

	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s\n", __func__);
	ret = cf_diag_all_stop();
	cf_diag_ctrset_clear();
	debug_प्र_लिखो_event(cf_diag_dbg, 5, "%s ret %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल दीर्घ cf_diag_ioctl_start(अचिन्हित दीर्घ arg)
अणु
	काष्ठा s390_ctrset_start __user *ustart;
	काष्ठा s390_ctrset_start start;
	व्योम __user *umask;
	अचिन्हित पूर्णांक len;
	पूर्णांक ret = 0;
	माप_प्रकार need;

	अगर (cf_diag_ctrset.ctrset)
		वापस -EBUSY;
	ustart = (काष्ठा s390_ctrset_start __user *)arg;
	अगर (copy_from_user(&start, ustart, माप(start)))
		वापस -EFAULT;
	अगर (start.version != S390_HWCTR_START_VERSION)
		वापस -EINVAL;
	अगर (start.counter_sets & ~(cpumf_ctr_ctl[CPUMF_CTR_SET_BASIC] |
				   cpumf_ctr_ctl[CPUMF_CTR_SET_USER] |
				   cpumf_ctr_ctl[CPUMF_CTR_SET_CRYPTO] |
				   cpumf_ctr_ctl[CPUMF_CTR_SET_EXT] |
				   cpumf_ctr_ctl[CPUMF_CTR_SET_MT_DIAG]))
		वापस -EINVAL;		/* Invalid counter set */
	अगर (!start.counter_sets)
		वापस -EINVAL;		/* No counter set at all? */
	cpumask_clear(&cf_diag_ctrset.mask);
	len = min_t(u64, start.cpumask_len, cpumask_size());
	umask = (व्योम __user *)start.cpumask;
	अगर (copy_from_user(&cf_diag_ctrset.mask, umask, len))
		वापस -EFAULT;
	अगर (cpumask_empty(&cf_diag_ctrset.mask))
		वापस -EINVAL;
	need = cf_diag_needspace(start.counter_sets);
	अगर (put_user(need, &ustart->data_bytes))
		ret = -EFAULT;
	अगर (ret)
		जाओ out;
	cf_diag_ctrset.ctrset = start.counter_sets;
	ret = cf_diag_all_start();
out:
	अगर (ret)
		cf_diag_ctrset_clear();
	debug_प्र_लिखो_event(cf_diag_dbg, 2, "%s sets %#lx need %ld ret %d\n",
			    __func__, cf_diag_ctrset.ctrset, need, ret);
	वापस ret;
पूर्ण

अटल दीर्घ cf_diag_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	debug_प्र_लिखो_event(cf_diag_dbg, 2, "%s cmd %#x arg %lx\n", __func__,
			    cmd, arg);
	get_online_cpus();
	mutex_lock(&cf_diag_ctrset_mutex);
	चयन (cmd) अणु
	हाल S390_HWCTR_START:
		ret = cf_diag_ioctl_start(arg);
		अवरोध;
	हाल S390_HWCTR_STOP:
		ret = cf_diag_ioctl_stop();
		अवरोध;
	हाल S390_HWCTR_READ:
		ret = cf_diag_ioctl_पढ़ो(arg);
		अवरोध;
	शेष:
		ret = -ENOTTY;
		अवरोध;
	पूर्ण
	mutex_unlock(&cf_diag_ctrset_mutex);
	put_online_cpus();
	debug_प्र_लिखो_event(cf_diag_dbg, 2, "%s ret %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations cf_diag_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = cf_diag_खोलो,
	.release = cf_diag_release,
	.unlocked_ioctl	= cf_diag_ioctl,
	.compat_ioctl = cf_diag_ioctl,
	.llseek = no_llseek
पूर्ण;

अटल काष्ठा miscdevice cf_diag_dev = अणु
	.name	= S390_HWCTR_DEVICE,
	.minor	= MISC_DYNAMIC_MINOR,
	.fops	= &cf_diag_fops,
पूर्ण;

अटल पूर्णांक cf_diag_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cf_diag_call_on_cpu_parm p;

	mutex_lock(&cf_diag_ctrset_mutex);
	अगर (!cf_diag_ctrset.ctrset)
		जाओ out;
	p.sets = cf_diag_ctrset.ctrset;
	cf_diag_ioctl_on(&p);
out:
	mutex_unlock(&cf_diag_ctrset_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक cf_diag_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cf_diag_call_on_cpu_parm p;

	mutex_lock(&cf_diag_ctrset_mutex);
	अगर (!cf_diag_ctrset.ctrset)
		जाओ out;
	p.sets = cf_diag_ctrset.ctrset;
	cf_diag_ioctl_off(&p);
out:
	mutex_unlock(&cf_diag_ctrset_mutex);
	वापस 0;
पूर्ण

/* Initialize the counter set PMU to generate complete counter set data as
 * event raw data. This relies on the CPU Measurement Counter Facility device
 * alपढ़ोy being loaded and initialized.
 */
अटल पूर्णांक __init cf_diag_init(व्योम)
अणु
	काष्ठा cpumf_ctr_info info;
	माप_प्रकार need;
	पूर्णांक rc;

	अगर (!kernel_cpumcf_avail() || !stccm_avail() || qctri(&info))
		वापस -ENODEV;
	cf_diag_get_cpu_speed();

	/* Make sure the counter set data fits पूर्णांकo predefined buffer. */
	need = cf_diag_ctrset_maxsize(&info);
	अगर (need > माप(((काष्ठा cf_diag_csd *)0)->start)) अणु
		pr_err("Insufficient memory for PMU(cpum_cf_diag) need=%zu\n",
		       need);
		वापस -ENOMEM;
	पूर्ण

	rc = misc_रेजिस्टर(&cf_diag_dev);
	अगर (rc) अणु
		pr_err("Registration of /dev/" S390_HWCTR_DEVICE
		       "failed rc=%d\n", rc);
		जाओ out;
	पूर्ण

	/* Setup s390dbf facility */
	cf_diag_dbg = debug_रेजिस्टर(KMSG_COMPONENT, 2, 1, 128);
	अगर (!cf_diag_dbg) अणु
		pr_err("Registration of s390dbf(cpum_cf_diag) failed\n");
		rc = -ENOMEM;
		जाओ out_dbf;
	पूर्ण
	debug_रेजिस्टर_view(cf_diag_dbg, &debug_प्र_लिखो_view);

	rc = perf_pmu_रेजिस्टर(&cf_diag, "cpum_cf_diag", -1);
	अगर (rc) अणु
		pr_err("Registration of PMU(cpum_cf_diag) failed with rc=%i\n",
		       rc);
		जाओ out_perf;
	पूर्ण
	rc = cpuhp_setup_state_nocalls(CPUHP_AP_PERF_S390_CFD_ONLINE,
				       "perf/s390/cfd:online",
				       cf_diag_online_cpu, cf_diag_offline_cpu);
	अगर (!rc)
		जाओ out;

	pr_err("Registration of CPUHP_AP_PERF_S390_CFD_ONLINE failed rc=%i\n",
	       rc);
	perf_pmu_unरेजिस्टर(&cf_diag);
out_perf:
	debug_unरेजिस्टर_view(cf_diag_dbg, &debug_प्र_लिखो_view);
	debug_unरेजिस्टर(cf_diag_dbg);
out_dbf:
	misc_deरेजिस्टर(&cf_diag_dev);
out:
	वापस rc;
पूर्ण
device_initcall(cf_diag_init);
