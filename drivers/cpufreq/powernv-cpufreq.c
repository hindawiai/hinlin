<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * POWERNV cpufreq driver क्रम the IBM POWER processors
 *
 * (C) Copyright IBM 2014
 *
 * Author: Vaidyanathan Srinivasan <svaidy at linux.vnet.ibm.com>
 */

#घोषणा pr_fmt(fmt)	"powernv-cpufreq: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/smp.h>
#समावेश <linux/of.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/hashtable.h>
#समावेश <trace/events/घातer.h>

#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/smp.h> /* Required क्रम cpu_sibling_mask() in UP configs */
#समावेश <यंत्र/opal.h>
#समावेश <linux/समयr.h>

#घोषणा POWERNV_MAX_PSTATES_ORDER  8
#घोषणा POWERNV_MAX_PSTATES	(1UL << (POWERNV_MAX_PSTATES_ORDER))
#घोषणा PMSR_PSAFE_ENABLE	(1UL << 30)
#घोषणा PMSR_SPR_EM_DISABLE	(1UL << 31)
#घोषणा MAX_PSTATE_SHIFT	32
#घोषणा LPSTATE_SHIFT		48
#घोषणा GPSTATE_SHIFT		56

#घोषणा MAX_RAMP_DOWN_TIME				5120
/*
 * On an idle प्रणाली we want the global pstate to ramp-करोwn from max value to
 * min over a span of ~5 secs. Also we want it to initially ramp-करोwn slowly and
 * then ramp-करोwn rapidly later on.
 *
 * This gives a percentage rampकरोwn क्रम समय elapsed in milliseconds.
 * ramp_करोwn_percentage = ((ms * ms) >> 18)
 *			~= 3.8 * (sec * sec)
 *
 * At 0 ms	ramp_करोwn_percent = 0
 * At 5120 ms	ramp_करोwn_percent = 100
 */
#घोषणा ramp_करोwn_percent(समय)		((समय * समय) >> 18)

/* Interval after which the समयr is queued to bring करोwn global pstate */
#घोषणा GPSTATE_TIMER_INTERVAL				2000

/**
 * काष्ठा global_pstate_info -	Per policy data काष्ठाure to मुख्यtain history of
 *				global pstates
 * @highest_lpstate_idx:	The local pstate index from which we are
 *				ramping करोwn
 * @elapsed_समय:		Time in ms spent in ramping करोwn from
 *				highest_lpstate_idx
 * @last_sampled_समय:		Time from boot in ms when global pstates were
 *				last set
 * @last_lpstate_idx:		Last set value of local pstate and global
 * @last_gpstate_idx:		pstate in terms of cpufreq table index
 * @समयr:			Is used क्रम ramping करोwn अगर cpu goes idle क्रम
 *				a दीर्घ समय with global pstate held high
 * @gpstate_lock:		A spinlock to मुख्यtain synchronization between
 *				routines called by the समयr handler and
 *				governer's target_index calls
 * @policy:			Associated CPUFreq policy
 */
काष्ठा global_pstate_info अणु
	पूर्णांक highest_lpstate_idx;
	अचिन्हित पूर्णांक elapsed_समय;
	अचिन्हित पूर्णांक last_sampled_समय;
	पूर्णांक last_lpstate_idx;
	पूर्णांक last_gpstate_idx;
	spinlock_t gpstate_lock;
	काष्ठा समयr_list समयr;
	काष्ठा cpufreq_policy *policy;
पूर्ण;

अटल काष्ठा cpufreq_frequency_table घातernv_freqs[POWERNV_MAX_PSTATES+1];

अटल DEFINE_HASHTABLE(pstate_revmap, POWERNV_MAX_PSTATES_ORDER);
/**
 * काष्ठा pstate_idx_revmap_data: Entry in the hashmap pstate_revmap
 *				  indexed by a function of pstate id.
 *
 * @pstate_id: pstate id क्रम this entry.
 *
 * @cpufreq_table_idx: Index पूर्णांकo the घातernv_freqs
 *		       cpufreq_frequency_table क्रम frequency
 *		       corresponding to pstate_id.
 *
 * @hentry: hlist_node that hooks this entry पूर्णांकo the pstate_revmap
 *	    hashtable
 */
काष्ठा pstate_idx_revmap_data अणु
	u8 pstate_id;
	अचिन्हित पूर्णांक cpufreq_table_idx;
	काष्ठा hlist_node hentry;
पूर्ण;

अटल bool rebooting, throttled, occ_reset;

अटल स्थिर अक्षर * स्थिर throttle_reason[] = अणु
	"No throttling",
	"Power Cap",
	"Processor Over Temperature",
	"Power Supply Failure",
	"Over Current",
	"OCC Reset"
पूर्ण;

क्रमागत throttle_reason_type अणु
	NO_THROTTLE = 0,
	POWERCAP,
	CPU_OVERTEMP,
	POWER_SUPPLY_FAILURE,
	OVERCURRENT,
	OCC_RESET_THROTTLE,
	OCC_MAX_REASON
पूर्ण;

अटल काष्ठा chip अणु
	अचिन्हित पूर्णांक id;
	bool throttled;
	bool restore;
	u8 throttle_reason;
	cpumask_t mask;
	काष्ठा work_काष्ठा throttle;
	पूर्णांक throttle_turbo;
	पूर्णांक throttle_sub_turbo;
	पूर्णांक reason[OCC_MAX_REASON];
पूर्ण *chips;

अटल पूर्णांक nr_chips;
अटल DEFINE_PER_CPU(काष्ठा chip *, chip_info);

/*
 * Note:
 * The set of pstates consists of contiguous पूर्णांकegers.
 * घातernv_pstate_info stores the index of the frequency table क्रम
 * max, min and nominal frequencies. It also stores number of
 * available frequencies.
 *
 * घातernv_pstate_info.nominal indicates the index to the highest
 * non-turbo frequency.
 */
अटल काष्ठा घातernv_pstate_info अणु
	अचिन्हित पूर्णांक min;
	अचिन्हित पूर्णांक max;
	अचिन्हित पूर्णांक nominal;
	अचिन्हित पूर्णांक nr_pstates;
	bool wof_enabled;
पूर्ण घातernv_pstate_info;

अटल अंतरभूत u8 extract_pstate(u64 pmsr_val, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस ((pmsr_val >> shअगरt) & 0xFF);
पूर्ण

#घोषणा extract_local_pstate(x) extract_pstate(x, LPSTATE_SHIFT)
#घोषणा extract_global_pstate(x) extract_pstate(x, GPSTATE_SHIFT)
#घोषणा extract_max_pstate(x)  extract_pstate(x, MAX_PSTATE_SHIFT)

/* Use following functions क्रम conversions between pstate_id and index */

/*
 * idx_to_pstate : Returns the pstate id corresponding to the
 *		   frequency in the cpufreq frequency table
 *		   घातernv_freqs indexed by @i.
 *
 *		   If @i is out of bound, this will वापस the pstate
 *		   corresponding to the nominal frequency.
 */
अटल अंतरभूत u8 idx_to_pstate(अचिन्हित पूर्णांक i)
अणु
	अगर (unlikely(i >= घातernv_pstate_info.nr_pstates)) अणु
		pr_warn_once("idx_to_pstate: index %u is out of bound\n", i);
		वापस घातernv_freqs[घातernv_pstate_info.nominal].driver_data;
	पूर्ण

	वापस घातernv_freqs[i].driver_data;
पूर्ण

/*
 * pstate_to_idx : Returns the index in the cpufreq frequencytable
 *		   घातernv_freqs क्रम the frequency whose corresponding
 *		   pstate id is @pstate.
 *
 *		   If no frequency corresponding to @pstate is found,
 *		   this will वापस the index of the nominal
 *		   frequency.
 */
अटल अचिन्हित पूर्णांक pstate_to_idx(u8 pstate)
अणु
	अचिन्हित पूर्णांक key = pstate % POWERNV_MAX_PSTATES;
	काष्ठा pstate_idx_revmap_data *revmap_data;

	hash_क्रम_each_possible(pstate_revmap, revmap_data, hentry, key) अणु
		अगर (revmap_data->pstate_id == pstate)
			वापस revmap_data->cpufreq_table_idx;
	पूर्ण

	pr_warn_once("pstate_to_idx: pstate 0x%x not found\n", pstate);
	वापस घातernv_pstate_info.nominal;
पूर्ण

अटल अंतरभूत व्योम reset_gpstates(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा global_pstate_info *gpstates = policy->driver_data;

	gpstates->highest_lpstate_idx = 0;
	gpstates->elapsed_समय = 0;
	gpstates->last_sampled_समय = 0;
	gpstates->last_lpstate_idx = 0;
	gpstates->last_gpstate_idx = 0;
पूर्ण

/*
 * Initialize the freq table based on data obtained
 * from the firmware passed via device-tree
 */
अटल पूर्णांक init_घातernv_pstates(व्योम)
अणु
	काष्ठा device_node *घातer_mgt;
	पूर्णांक i, nr_pstates = 0;
	स्थिर __be32 *pstate_ids, *pstate_freqs;
	u32 len_ids, len_freqs;
	u32 pstate_min, pstate_max, pstate_nominal;
	u32 pstate_turbo, pstate_ultra_turbo;
	पूर्णांक rc = -ENODEV;

	घातer_mgt = of_find_node_by_path("/ibm,opal/power-mgt");
	अगर (!घातer_mgt) अणु
		pr_warn("power-mgt node not found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_property_पढ़ो_u32(घातer_mgt, "ibm,pstate-min", &pstate_min)) अणु
		pr_warn("ibm,pstate-min node not found\n");
		जाओ out;
	पूर्ण

	अगर (of_property_पढ़ो_u32(घातer_mgt, "ibm,pstate-max", &pstate_max)) अणु
		pr_warn("ibm,pstate-max node not found\n");
		जाओ out;
	पूर्ण

	अगर (of_property_पढ़ो_u32(घातer_mgt, "ibm,pstate-nominal",
				 &pstate_nominal)) अणु
		pr_warn("ibm,pstate-nominal not found\n");
		जाओ out;
	पूर्ण

	अगर (of_property_पढ़ो_u32(घातer_mgt, "ibm,pstate-ultra-turbo",
				 &pstate_ultra_turbo)) अणु
		घातernv_pstate_info.wof_enabled = false;
		जाओ next;
	पूर्ण

	अगर (of_property_पढ़ो_u32(घातer_mgt, "ibm,pstate-turbo",
				 &pstate_turbo)) अणु
		घातernv_pstate_info.wof_enabled = false;
		जाओ next;
	पूर्ण

	अगर (pstate_turbo == pstate_ultra_turbo)
		घातernv_pstate_info.wof_enabled = false;
	अन्यथा
		घातernv_pstate_info.wof_enabled = true;

next:
	pr_info("cpufreq pstate min 0x%x nominal 0x%x max 0x%x\n", pstate_min,
		pstate_nominal, pstate_max);
	pr_info("Workload Optimized Frequency is %s in the platform\n",
		(घातernv_pstate_info.wof_enabled) ? "enabled" : "disabled");

	pstate_ids = of_get_property(घातer_mgt, "ibm,pstate-ids", &len_ids);
	अगर (!pstate_ids) अणु
		pr_warn("ibm,pstate-ids not found\n");
		जाओ out;
	पूर्ण

	pstate_freqs = of_get_property(घातer_mgt, "ibm,pstate-frequencies-mhz",
				      &len_freqs);
	अगर (!pstate_freqs) अणु
		pr_warn("ibm,pstate-frequencies-mhz not found\n");
		जाओ out;
	पूर्ण

	अगर (len_ids != len_freqs) अणु
		pr_warn("Entries in ibm,pstate-ids and "
			"ibm,pstate-frequencies-mhz does not match\n");
	पूर्ण

	nr_pstates = min(len_ids, len_freqs) / माप(u32);
	अगर (!nr_pstates) अणु
		pr_warn("No PStates found\n");
		जाओ out;
	पूर्ण

	घातernv_pstate_info.nr_pstates = nr_pstates;
	pr_debug("NR PStates %d\n", nr_pstates);

	क्रम (i = 0; i < nr_pstates; i++) अणु
		u32 id = be32_to_cpu(pstate_ids[i]);
		u32 freq = be32_to_cpu(pstate_freqs[i]);
		काष्ठा pstate_idx_revmap_data *revmap_data;
		अचिन्हित पूर्णांक key;

		pr_debug("PState id %d freq %d MHz\n", id, freq);
		घातernv_freqs[i].frequency = freq * 1000; /* kHz */
		घातernv_freqs[i].driver_data = id & 0xFF;

		revmap_data = kदो_स्मृति(माप(*revmap_data), GFP_KERNEL);
		अगर (!revmap_data) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		revmap_data->pstate_id = id & 0xFF;
		revmap_data->cpufreq_table_idx = i;
		key = (revmap_data->pstate_id) % POWERNV_MAX_PSTATES;
		hash_add(pstate_revmap, &revmap_data->hentry, key);

		अगर (id == pstate_max)
			घातernv_pstate_info.max = i;
		अगर (id == pstate_nominal)
			घातernv_pstate_info.nominal = i;
		अगर (id == pstate_min)
			घातernv_pstate_info.min = i;

		अगर (घातernv_pstate_info.wof_enabled && id == pstate_turbo) अणु
			पूर्णांक j;

			क्रम (j = i - 1; j >= (पूर्णांक)घातernv_pstate_info.max; j--)
				घातernv_freqs[j].flags = CPUFREQ_BOOST_FREQ;
		पूर्ण
	पूर्ण

	/* End of list marker entry */
	घातernv_freqs[i].frequency = CPUFREQ_TABLE_END;

	of_node_put(घातer_mgt);
	वापस 0;
out:
	of_node_put(घातer_mgt);
	वापस rc;
पूर्ण

/* Returns the CPU frequency corresponding to the pstate_id. */
अटल अचिन्हित पूर्णांक pstate_id_to_freq(u8 pstate_id)
अणु
	पूर्णांक i;

	i = pstate_to_idx(pstate_id);
	अगर (i >= घातernv_pstate_info.nr_pstates || i < 0) अणु
		pr_warn("PState id 0x%x outside of PState table, reporting nominal id 0x%x instead\n",
			pstate_id, idx_to_pstate(घातernv_pstate_info.nominal));
		i = घातernv_pstate_info.nominal;
	पूर्ण

	वापस घातernv_freqs[i].frequency;
पूर्ण

/*
 * cpuinfo_nominal_freq_show - Show the nominal CPU frequency as indicated by
 * the firmware
 */
अटल sमाप_प्रकार cpuinfo_nominal_freq_show(काष्ठा cpufreq_policy *policy,
					अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n",
		घातernv_freqs[घातernv_pstate_info.nominal].frequency);
पूर्ण

अटल काष्ठा freq_attr cpufreq_freq_attr_cpuinfo_nominal_freq =
	__ATTR_RO(cpuinfo_nominal_freq);

#घोषणा SCALING_BOOST_FREQS_ATTR_INDEX		2

अटल काष्ठा freq_attr *घातernv_cpu_freq_attr[] = अणु
	&cpufreq_freq_attr_scaling_available_freqs,
	&cpufreq_freq_attr_cpuinfo_nominal_freq,
	&cpufreq_freq_attr_scaling_boost_freqs,
	शून्य,
पूर्ण;

#घोषणा throttle_attr(name, member)					\
अटल sमाप_प्रकार name##_show(काष्ठा cpufreq_policy *policy, अक्षर *buf)	\
अणु									\
	काष्ठा chip *chip = per_cpu(chip_info, policy->cpu);		\
									\
	वापस प्र_लिखो(buf, "%u\n", chip->member);			\
पूर्ण									\
									\
अटल काष्ठा freq_attr throttle_attr_##name = __ATTR_RO(name)		\

throttle_attr(unthrottle, reason[NO_THROTTLE]);
throttle_attr(घातercap, reason[POWERCAP]);
throttle_attr(overtemp, reason[CPU_OVERTEMP]);
throttle_attr(supply_fault, reason[POWER_SUPPLY_FAILURE]);
throttle_attr(overcurrent, reason[OVERCURRENT]);
throttle_attr(occ_reset, reason[OCC_RESET_THROTTLE]);
throttle_attr(turbo_stat, throttle_turbo);
throttle_attr(sub_turbo_stat, throttle_sub_turbo);

अटल काष्ठा attribute *throttle_attrs[] = अणु
	&throttle_attr_unthrottle.attr,
	&throttle_attr_घातercap.attr,
	&throttle_attr_overtemp.attr,
	&throttle_attr_supply_fault.attr,
	&throttle_attr_overcurrent.attr,
	&throttle_attr_occ_reset.attr,
	&throttle_attr_turbo_stat.attr,
	&throttle_attr_sub_turbo_stat.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group throttle_attr_grp = अणु
	.name	= "throttle_stats",
	.attrs	= throttle_attrs,
पूर्ण;

/* Helper routines */

/* Access helpers to घातer mgt SPR */

अटल अंतरभूत अचिन्हित दीर्घ get_pmspr(अचिन्हित दीर्घ sprn)
अणु
	चयन (sprn) अणु
	हाल SPRN_PMCR:
		वापस mfspr(SPRN_PMCR);

	हाल SPRN_PMICR:
		वापस mfspr(SPRN_PMICR);

	हाल SPRN_PMSR:
		वापस mfspr(SPRN_PMSR);
	पूर्ण
	BUG();
पूर्ण

अटल अंतरभूत व्योम set_pmspr(अचिन्हित दीर्घ sprn, अचिन्हित दीर्घ val)
अणु
	चयन (sprn) अणु
	हाल SPRN_PMCR:
		mtspr(SPRN_PMCR, val);
		वापस;

	हाल SPRN_PMICR:
		mtspr(SPRN_PMICR, val);
		वापस;
	पूर्ण
	BUG();
पूर्ण

/*
 * Use objects of this type to query/update
 * pstates on a remote CPU via smp_call_function.
 */
काष्ठा घातernv_smp_call_data अणु
	अचिन्हित पूर्णांक freq;
	u8 pstate_id;
	u8 gpstate_id;
पूर्ण;

/*
 * घातernv_पढ़ो_cpu_freq: Reads the current frequency on this CPU.
 *
 * Called via smp_call_function.
 *
 * Note: The caller of the smp_call_function should pass an argument of
 * the type 'struct powernv_smp_call_data *' aदीर्घ with this function.
 *
 * The current frequency on this CPU will be वापसed via
 * ((काष्ठा घातernv_smp_call_data *)arg)->freq;
 */
अटल व्योम घातernv_पढ़ो_cpu_freq(व्योम *arg)
अणु
	अचिन्हित दीर्घ pmspr_val;
	काष्ठा घातernv_smp_call_data *freq_data = arg;

	pmspr_val = get_pmspr(SPRN_PMSR);
	freq_data->pstate_id = extract_local_pstate(pmspr_val);
	freq_data->freq = pstate_id_to_freq(freq_data->pstate_id);

	pr_debug("cpu %d pmsr %016lX pstate_id 0x%x frequency %d kHz\n",
		 raw_smp_processor_id(), pmspr_val, freq_data->pstate_id,
		 freq_data->freq);
पूर्ण

/*
 * घातernv_cpufreq_get: Returns the CPU frequency as reported by the
 * firmware क्रम CPU 'cpu'. This value is reported through the sysfs
 * file cpuinfo_cur_freq.
 */
अटल अचिन्हित पूर्णांक घातernv_cpufreq_get(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घातernv_smp_call_data freq_data;

	smp_call_function_any(cpu_sibling_mask(cpu), घातernv_पढ़ो_cpu_freq,
			&freq_data, 1);

	वापस freq_data.freq;
पूर्ण

/*
 * set_pstate: Sets the pstate on this CPU.
 *
 * This is called via an smp_call_function.
 *
 * The caller must ensure that freq_data is of the type
 * (काष्ठा घातernv_smp_call_data *) and the pstate_id which needs to be set
 * on this CPU should be present in freq_data->pstate_id.
 */
अटल व्योम set_pstate(व्योम *data)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा घातernv_smp_call_data *freq_data = data;
	अचिन्हित दीर्घ pstate_ul = freq_data->pstate_id;
	अचिन्हित दीर्घ gpstate_ul = freq_data->gpstate_id;

	val = get_pmspr(SPRN_PMCR);
	val = val & 0x0000FFFFFFFFFFFFULL;

	pstate_ul = pstate_ul & 0xFF;
	gpstate_ul = gpstate_ul & 0xFF;

	/* Set both global(bits 56..63) and local(bits 48..55) PStates */
	val = val | (gpstate_ul << 56) | (pstate_ul << 48);

	pr_debug("Setting cpu %d pmcr to %016lX\n",
			raw_smp_processor_id(), val);
	set_pmspr(SPRN_PMCR, val);
पूर्ण

/*
 * get_nominal_index: Returns the index corresponding to the nominal
 * pstate in the cpufreq table
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_nominal_index(व्योम)
अणु
	वापस घातernv_pstate_info.nominal;
पूर्ण

अटल व्योम घातernv_cpufreq_throttle_check(व्योम *data)
अणु
	काष्ठा chip *chip;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ pmsr;
	u8 pmsr_pmax;
	अचिन्हित पूर्णांक pmsr_pmax_idx;

	pmsr = get_pmspr(SPRN_PMSR);
	chip = this_cpu_पढ़ो(chip_info);

	/* Check क्रम Pmax Capping */
	pmsr_pmax = extract_max_pstate(pmsr);
	pmsr_pmax_idx = pstate_to_idx(pmsr_pmax);
	अगर (pmsr_pmax_idx != घातernv_pstate_info.max) अणु
		अगर (chip->throttled)
			जाओ next;
		chip->throttled = true;
		अगर (pmsr_pmax_idx > घातernv_pstate_info.nominal) अणु
			pr_warn_once("CPU %d on Chip %u has Pmax(0x%x) reduced below that of nominal frequency(0x%x)\n",
				     cpu, chip->id, pmsr_pmax,
				     idx_to_pstate(घातernv_pstate_info.nominal));
			chip->throttle_sub_turbo++;
		पूर्ण अन्यथा अणु
			chip->throttle_turbo++;
		पूर्ण
		trace_घातernv_throttle(chip->id,
				      throttle_reason[chip->throttle_reason],
				      pmsr_pmax);
	पूर्ण अन्यथा अगर (chip->throttled) अणु
		chip->throttled = false;
		trace_घातernv_throttle(chip->id,
				      throttle_reason[chip->throttle_reason],
				      pmsr_pmax);
	पूर्ण

	/* Check अगर Psafe_mode_active is set in PMSR. */
next:
	अगर (pmsr & PMSR_PSAFE_ENABLE) अणु
		throttled = true;
		pr_info("Pstate set to safe frequency\n");
	पूर्ण

	/* Check अगर SPR_EM_DISABLE is set in PMSR */
	अगर (pmsr & PMSR_SPR_EM_DISABLE) अणु
		throttled = true;
		pr_info("Frequency Control disabled from OS\n");
	पूर्ण

	अगर (throttled) अणु
		pr_info("PMSR = %16lx\n", pmsr);
		pr_warn("CPU Frequency could be throttled\n");
	पूर्ण
पूर्ण

/**
 * calc_global_pstate - Calculate global pstate
 * @elapsed_समय:		Elapsed समय in milliseconds
 * @local_pstate_idx:		New local pstate
 * @highest_lpstate_idx:	pstate from which its ramping करोwn
 *
 * Finds the appropriate global pstate based on the pstate from which its
 * ramping करोwn and the समय elapsed in ramping करोwn. It follows a quadratic
 * equation which ensures that it reaches ramping करोwn to pmin in 5sec.
 */
अटल अंतरभूत पूर्णांक calc_global_pstate(अचिन्हित पूर्णांक elapsed_समय,
				     पूर्णांक highest_lpstate_idx,
				     पूर्णांक local_pstate_idx)
अणु
	पूर्णांक index_dअगरf;

	/*
	 * Using ramp_करोwn_percent we get the percentage of rampकरोwn
	 * that we are expecting to be dropping. Dअगरference between
	 * highest_lpstate_idx and घातernv_pstate_info.min will give a असलolute
	 * number of how many pstates we will drop eventually by the end of
	 * 5 seconds, then just scale it get the number pstates to be dropped.
	 */
	index_dअगरf =  ((पूर्णांक)ramp_करोwn_percent(elapsed_समय) *
			(घातernv_pstate_info.min - highest_lpstate_idx)) / 100;

	/* Ensure that global pstate is >= to local pstate */
	अगर (highest_lpstate_idx + index_dअगरf >= local_pstate_idx)
		वापस local_pstate_idx;
	अन्यथा
		वापस highest_lpstate_idx + index_dअगरf;
पूर्ण

अटल अंतरभूत व्योम  queue_gpstate_समयr(काष्ठा global_pstate_info *gpstates)
अणु
	अचिन्हित पूर्णांक समयr_पूर्णांकerval;

	/*
	 * Setting up समयr to fire after GPSTATE_TIMER_INTERVAL ms, But
	 * अगर it exceeds MAX_RAMP_DOWN_TIME ms क्रम ramp करोwn समय.
	 * Set समयr such that it fires exactly at MAX_RAMP_DOWN_TIME
	 * seconds of ramp करोwn समय.
	 */
	अगर ((gpstates->elapsed_समय + GPSTATE_TIMER_INTERVAL)
	     > MAX_RAMP_DOWN_TIME)
		समयr_पूर्णांकerval = MAX_RAMP_DOWN_TIME - gpstates->elapsed_समय;
	अन्यथा
		समयr_पूर्णांकerval = GPSTATE_TIMER_INTERVAL;

	mod_समयr(&gpstates->समयr, jअगरfies + msecs_to_jअगरfies(समयr_पूर्णांकerval));
पूर्ण

/**
 * gpstate_समयr_handler
 *
 * @t: Timer context used to fetch global pstate info काष्ठा
 *
 * This handler brings करोwn the global pstate बंदr to the local pstate
 * according quadratic equation. Queues a new समयr अगर it is still not equal
 * to local pstate
 */
अटल व्योम gpstate_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा global_pstate_info *gpstates = from_समयr(gpstates, t, समयr);
	काष्ठा cpufreq_policy *policy = gpstates->policy;
	पूर्णांक gpstate_idx, lpstate_idx;
	अचिन्हित दीर्घ val;
	अचिन्हित पूर्णांक समय_dअगरf = jअगरfies_to_msecs(jअगरfies)
					- gpstates->last_sampled_समय;
	काष्ठा घातernv_smp_call_data freq_data;

	अगर (!spin_trylock(&gpstates->gpstate_lock))
		वापस;
	/*
	 * If the समयr has migrated to the dअगरferent cpu then bring
	 * it back to one of the policy->cpus
	 */
	अगर (!cpumask_test_cpu(raw_smp_processor_id(), policy->cpus)) अणु
		gpstates->समयr.expires = jअगरfies + msecs_to_jअगरfies(1);
		add_समयr_on(&gpstates->समयr, cpumask_first(policy->cpus));
		spin_unlock(&gpstates->gpstate_lock);
		वापस;
	पूर्ण

	/*
	 * If PMCR was last updated was using fast_swtich then
	 * We may have wrong in gpstate->last_lpstate_idx
	 * value. Hence, पढ़ो from PMCR to get correct data.
	 */
	val = get_pmspr(SPRN_PMCR);
	freq_data.gpstate_id = extract_global_pstate(val);
	freq_data.pstate_id = extract_local_pstate(val);
	अगर (freq_data.gpstate_id  == freq_data.pstate_id) अणु
		reset_gpstates(policy);
		spin_unlock(&gpstates->gpstate_lock);
		वापस;
	पूर्ण

	gpstates->last_sampled_समय += समय_dअगरf;
	gpstates->elapsed_समय += समय_dअगरf;

	अगर (gpstates->elapsed_समय > MAX_RAMP_DOWN_TIME) अणु
		gpstate_idx = pstate_to_idx(freq_data.pstate_id);
		lpstate_idx = gpstate_idx;
		reset_gpstates(policy);
		gpstates->highest_lpstate_idx = gpstate_idx;
	पूर्ण अन्यथा अणु
		lpstate_idx = pstate_to_idx(freq_data.pstate_id);
		gpstate_idx = calc_global_pstate(gpstates->elapsed_समय,
						 gpstates->highest_lpstate_idx,
						 lpstate_idx);
	पूर्ण
	freq_data.gpstate_id = idx_to_pstate(gpstate_idx);
	gpstates->last_gpstate_idx = gpstate_idx;
	gpstates->last_lpstate_idx = lpstate_idx;
	/*
	 * If local pstate is equal to global pstate, rampकरोwn is over
	 * So समयr is not required to be queued.
	 */
	अगर (gpstate_idx != gpstates->last_lpstate_idx)
		queue_gpstate_समयr(gpstates);

	set_pstate(&freq_data);
	spin_unlock(&gpstates->gpstate_lock);
पूर्ण

/*
 * घातernv_cpufreq_target_index: Sets the frequency corresponding to
 * the cpufreq table entry indexed by new_index on the cpus in the
 * mask policy->cpus
 */
अटल पूर्णांक घातernv_cpufreq_target_index(काष्ठा cpufreq_policy *policy,
					अचिन्हित पूर्णांक new_index)
अणु
	काष्ठा घातernv_smp_call_data freq_data;
	अचिन्हित पूर्णांक cur_msec, gpstate_idx;
	काष्ठा global_pstate_info *gpstates = policy->driver_data;

	अगर (unlikely(rebooting) && new_index != get_nominal_index())
		वापस 0;

	अगर (!throttled) अणु
		/* we करोn't want to be preempted जबतक
		 * checking अगर the CPU frequency has been throttled
		 */
		preempt_disable();
		घातernv_cpufreq_throttle_check(शून्य);
		preempt_enable();
	पूर्ण

	cur_msec = jअगरfies_to_msecs(get_jअगरfies_64());

	freq_data.pstate_id = idx_to_pstate(new_index);
	अगर (!gpstates) अणु
		freq_data.gpstate_id = freq_data.pstate_id;
		जाओ no_gpstate;
	पूर्ण

	spin_lock(&gpstates->gpstate_lock);

	अगर (!gpstates->last_sampled_समय) अणु
		gpstate_idx = new_index;
		gpstates->highest_lpstate_idx = new_index;
		जाओ gpstates_करोne;
	पूर्ण

	अगर (gpstates->last_gpstate_idx < new_index) अणु
		gpstates->elapsed_समय += cur_msec -
						 gpstates->last_sampled_समय;

		/*
		 * If its has been ramping करोwn क्रम more than MAX_RAMP_DOWN_TIME
		 * we should be resetting all global pstate related data. Set it
		 * equal to local pstate to start fresh.
		 */
		अगर (gpstates->elapsed_समय > MAX_RAMP_DOWN_TIME) अणु
			reset_gpstates(policy);
			gpstates->highest_lpstate_idx = new_index;
			gpstate_idx = new_index;
		पूर्ण अन्यथा अणु
		/* Elaspsed_समय is less than 5 seconds, जारी to rampकरोwn */
			gpstate_idx = calc_global_pstate(gpstates->elapsed_समय,
							 gpstates->highest_lpstate_idx,
							 new_index);
		पूर्ण
	पूर्ण अन्यथा अणु
		reset_gpstates(policy);
		gpstates->highest_lpstate_idx = new_index;
		gpstate_idx = new_index;
	पूर्ण

	/*
	 * If local pstate is equal to global pstate, rampकरोwn is over
	 * So समयr is not required to be queued.
	 */
	अगर (gpstate_idx != new_index)
		queue_gpstate_समयr(gpstates);
	अन्यथा
		del_समयr_sync(&gpstates->समयr);

gpstates_करोne:
	freq_data.gpstate_id = idx_to_pstate(gpstate_idx);
	gpstates->last_sampled_समय = cur_msec;
	gpstates->last_gpstate_idx = gpstate_idx;
	gpstates->last_lpstate_idx = new_index;

	spin_unlock(&gpstates->gpstate_lock);

no_gpstate:
	/*
	 * Use smp_call_function to send IPI and execute the
	 * mtspr on target CPU.  We could करो that without IPI
	 * अगर current CPU is within policy->cpus (core)
	 */
	smp_call_function_any(policy->cpus, set_pstate, &freq_data, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक घातernv_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक base, i;
	काष्ठा kernfs_node *kn;
	काष्ठा global_pstate_info *gpstates;

	base = cpu_first_thपढ़ो_sibling(policy->cpu);

	क्रम (i = 0; i < thपढ़ोs_per_core; i++)
		cpumask_set_cpu(base + i, policy->cpus);

	kn = kernfs_find_and_get(policy->kobj.sd, throttle_attr_grp.name);
	अगर (!kn) अणु
		पूर्णांक ret;

		ret = sysfs_create_group(&policy->kobj, &throttle_attr_grp);
		अगर (ret) अणु
			pr_info("Failed to create throttle stats directory for cpu %d\n",
				policy->cpu);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		kernfs_put(kn);
	पूर्ण

	policy->freq_table = घातernv_freqs;
	policy->fast_चयन_possible = true;

	अगर (pvr_version_is(PVR_POWER9))
		वापस 0;

	/* Initialise Gpstate ramp-करोwn समयr only on POWER8 */
	gpstates =  kzalloc(माप(*gpstates), GFP_KERNEL);
	अगर (!gpstates)
		वापस -ENOMEM;

	policy->driver_data = gpstates;

	/* initialize समयr */
	gpstates->policy = policy;
	समयr_setup(&gpstates->समयr, gpstate_समयr_handler,
		    TIMER_PINNED | TIMER_DEFERRABLE);
	gpstates->समयr.expires = jअगरfies +
				msecs_to_jअगरfies(GPSTATE_TIMER_INTERVAL);
	spin_lock_init(&gpstates->gpstate_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक घातernv_cpufreq_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	/* समयr is deleted in cpufreq_cpu_stop() */
	kमुक्त(policy->driver_data);

	वापस 0;
पूर्ण

अटल पूर्णांक घातernv_cpufreq_reboot_notअगरier(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ action, व्योम *unused)
अणु
	पूर्णांक cpu;
	काष्ठा cpufreq_policy *cpu_policy;

	rebooting = true;
	क्रम_each_online_cpu(cpu) अणु
		cpu_policy = cpufreq_cpu_get(cpu);
		अगर (!cpu_policy)
			जारी;
		घातernv_cpufreq_target_index(cpu_policy, get_nominal_index());
		cpufreq_cpu_put(cpu_policy);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block घातernv_cpufreq_reboot_nb = अणु
	.notअगरier_call = घातernv_cpufreq_reboot_notअगरier,
पूर्ण;

अटल व्योम घातernv_cpufreq_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा chip *chip = container_of(work, काष्ठा chip, throttle);
	काष्ठा cpufreq_policy *policy;
	अचिन्हित पूर्णांक cpu;
	cpumask_t mask;

	get_online_cpus();
	cpumask_and(&mask, &chip->mask, cpu_online_mask);
	smp_call_function_any(&mask,
			      घातernv_cpufreq_throttle_check, शून्य, 0);

	अगर (!chip->restore)
		जाओ out;

	chip->restore = false;
	क्रम_each_cpu(cpu, &mask) अणु
		पूर्णांक index;

		policy = cpufreq_cpu_get(cpu);
		अगर (!policy)
			जारी;
		index = cpufreq_table_find_index_c(policy, policy->cur);
		घातernv_cpufreq_target_index(policy, index);
		cpumask_andnot(&mask, &mask, policy->cpus);
		cpufreq_cpu_put(policy);
	पूर्ण
out:
	put_online_cpus();
पूर्ण

अटल पूर्णांक घातernv_cpufreq_occ_msg(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ msg_type, व्योम *_msg)
अणु
	काष्ठा opal_msg *msg = _msg;
	काष्ठा opal_occ_msg omsg;
	पूर्णांक i;

	अगर (msg_type != OPAL_MSG_OCC)
		वापस 0;

	omsg.type = be64_to_cpu(msg->params[0]);

	चयन (omsg.type) अणु
	हाल OCC_RESET:
		occ_reset = true;
		pr_info("OCC (On Chip Controller - enforces hard thermal/power limits) Resetting\n");
		/*
		 * घातernv_cpufreq_throttle_check() is called in
		 * target() callback which can detect the throttle state
		 * क्रम governors like ondemand.
		 * But अटल governors will not call target() often thus
		 * report throttling here.
		 */
		अगर (!throttled) अणु
			throttled = true;
			pr_warn("CPU frequency is throttled for duration\n");
		पूर्ण

		अवरोध;
	हाल OCC_LOAD:
		pr_info("OCC Loading, CPU frequency is throttled until OCC is started\n");
		अवरोध;
	हाल OCC_THROTTLE:
		omsg.chip = be64_to_cpu(msg->params[1]);
		omsg.throttle_status = be64_to_cpu(msg->params[2]);

		अगर (occ_reset) अणु
			occ_reset = false;
			throttled = false;
			pr_info("OCC Active, CPU frequency is no longer throttled\n");

			क्रम (i = 0; i < nr_chips; i++) अणु
				chips[i].restore = true;
				schedule_work(&chips[i].throttle);
			पूर्ण

			वापस 0;
		पूर्ण

		क्रम (i = 0; i < nr_chips; i++)
			अगर (chips[i].id == omsg.chip)
				अवरोध;

		अगर (omsg.throttle_status >= 0 &&
		    omsg.throttle_status <= OCC_MAX_THROTTLE_STATUS) अणु
			chips[i].throttle_reason = omsg.throttle_status;
			chips[i].reason[omsg.throttle_status]++;
		पूर्ण

		अगर (!omsg.throttle_status)
			chips[i].restore = true;

		schedule_work(&chips[i].throttle);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block घातernv_cpufreq_opal_nb = अणु
	.notअगरier_call	= घातernv_cpufreq_occ_msg,
	.next		= शून्य,
	.priority	= 0,
पूर्ण;

अटल व्योम घातernv_cpufreq_stop_cpu(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा घातernv_smp_call_data freq_data;
	काष्ठा global_pstate_info *gpstates = policy->driver_data;

	freq_data.pstate_id = idx_to_pstate(घातernv_pstate_info.min);
	freq_data.gpstate_id = idx_to_pstate(घातernv_pstate_info.min);
	smp_call_function_single(policy->cpu, set_pstate, &freq_data, 1);
	अगर (gpstates)
		del_समयr_sync(&gpstates->समयr);
पूर्ण

अटल अचिन्हित पूर्णांक घातernv_fast_चयन(काष्ठा cpufreq_policy *policy,
					अचिन्हित पूर्णांक target_freq)
अणु
	पूर्णांक index;
	काष्ठा घातernv_smp_call_data freq_data;

	index = cpufreq_table_find_index_dl(policy, target_freq);
	freq_data.pstate_id = घातernv_freqs[index].driver_data;
	freq_data.gpstate_id = घातernv_freqs[index].driver_data;
	set_pstate(&freq_data);

	वापस घातernv_freqs[index].frequency;
पूर्ण

अटल काष्ठा cpufreq_driver घातernv_cpufreq_driver = अणु
	.name		= "powernv-cpufreq",
	.flags		= CPUFREQ_CONST_LOOPS,
	.init		= घातernv_cpufreq_cpu_init,
	.निकास		= घातernv_cpufreq_cpu_निकास,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= घातernv_cpufreq_target_index,
	.fast_चयन	= घातernv_fast_चयन,
	.get		= घातernv_cpufreq_get,
	.stop_cpu	= घातernv_cpufreq_stop_cpu,
	.attr		= घातernv_cpu_freq_attr,
पूर्ण;

अटल पूर्णांक init_chip_info(व्योम)
अणु
	अचिन्हित पूर्णांक *chip;
	अचिन्हित पूर्णांक cpu, i;
	अचिन्हित पूर्णांक prev_chip_id = अच_पूर्णांक_उच्च;
	पूर्णांक ret = 0;

	chip = kसुस्मृति(num_possible_cpus(), माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(cpu) अणु
		अचिन्हित पूर्णांक id = cpu_to_chip_id(cpu);

		अगर (prev_chip_id != id) अणु
			prev_chip_id = id;
			chip[nr_chips++] = id;
		पूर्ण
	पूर्ण

	chips = kसुस्मृति(nr_chips, माप(काष्ठा chip), GFP_KERNEL);
	अगर (!chips) अणु
		ret = -ENOMEM;
		जाओ मुक्त_and_वापस;
	पूर्ण

	क्रम (i = 0; i < nr_chips; i++) अणु
		chips[i].id = chip[i];
		cpumask_copy(&chips[i].mask, cpumask_of_node(chip[i]));
		INIT_WORK(&chips[i].throttle, घातernv_cpufreq_work_fn);
		क्रम_each_cpu(cpu, &chips[i].mask)
			per_cpu(chip_info, cpu) =  &chips[i];
	पूर्ण

मुक्त_and_वापस:
	kमुक्त(chip);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम clean_chip_info(व्योम)
अणु
	पूर्णांक i;

	/* flush any pending work items */
	अगर (chips)
		क्रम (i = 0; i < nr_chips; i++)
			cancel_work_sync(&chips[i].throttle);
	kमुक्त(chips);
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_all_notअगरiers(व्योम)
अणु
	opal_message_notअगरier_unरेजिस्टर(OPAL_MSG_OCC,
					 &घातernv_cpufreq_opal_nb);
	unरेजिस्टर_reboot_notअगरier(&घातernv_cpufreq_reboot_nb);
पूर्ण

अटल पूर्णांक __init घातernv_cpufreq_init(व्योम)
अणु
	पूर्णांक rc = 0;

	/* Don't probe on pseries (guest) platक्रमms */
	अगर (!firmware_has_feature(FW_FEATURE_OPAL))
		वापस -ENODEV;

	/* Discover pstates from device tree and init */
	rc = init_घातernv_pstates();
	अगर (rc)
		जाओ out;

	/* Populate chip info */
	rc = init_chip_info();
	अगर (rc)
		जाओ out;

	अगर (घातernv_pstate_info.wof_enabled)
		घातernv_cpufreq_driver.boost_enabled = true;
	अन्यथा
		घातernv_cpu_freq_attr[SCALING_BOOST_FREQS_ATTR_INDEX] = शून्य;

	rc = cpufreq_रेजिस्टर_driver(&घातernv_cpufreq_driver);
	अगर (rc) अणु
		pr_info("Failed to register the cpufreq driver (%d)\n", rc);
		जाओ cleanup;
	पूर्ण

	अगर (घातernv_pstate_info.wof_enabled)
		cpufreq_enable_boost_support();

	रेजिस्टर_reboot_notअगरier(&घातernv_cpufreq_reboot_nb);
	opal_message_notअगरier_रेजिस्टर(OPAL_MSG_OCC, &घातernv_cpufreq_opal_nb);

	वापस 0;
cleanup:
	clean_chip_info();
out:
	pr_info("Platform driver disabled. System does not support PState control\n");
	वापस rc;
पूर्ण
module_init(घातernv_cpufreq_init);

अटल व्योम __निकास घातernv_cpufreq_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&घातernv_cpufreq_driver);
	unरेजिस्टर_all_notअगरiers();
	clean_chip_info();
पूर्ण
module_निकास(घातernv_cpufreq_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vaidyanathan Srinivasan <svaidy at linux.vnet.ibm.com>");
