<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/version.h>
#समावेश <linux/ptrace.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

/*
 * The CPU number, cstate number and pstate number are based
 * on 96boards Hikey with octa CA53 CPUs.
 *
 * Every CPU have three idle states क्रम cstate:
 *   WFI, CPU_OFF, CLUSTER_OFF
 *
 * Every CPU have 5 operating poपूर्णांकs:
 *   208MHz, 432MHz, 729MHz, 960MHz, 1200MHz
 *
 * This code is based on these assumption and other platक्रमms
 * need to adjust these definitions.
 */
#घोषणा MAX_CPU			8
#घोषणा MAX_PSTATE_ENTRIES	5
#घोषणा MAX_CSTATE_ENTRIES	3

अटल पूर्णांक cpu_opps[] = अणु 208000, 432000, 729000, 960000, 1200000 पूर्ण;

/*
 * my_map काष्ठाure is used to record cstate and pstate index and
 * बारtamp (Idx, Ts), when new event incoming we need to update
 * combination क्रम new state index and बारtamp (Idx`, Ts`).
 *
 * Based on (Idx, Ts) and (Idx`, Ts`) we can calculate the समय
 * पूर्णांकerval क्रम the previous state: Duration(Idx) = Ts` - Ts.
 *
 * Every CPU has one below array क्रम recording state index and
 * बारtamp, and record क्रम cstate and pstate saperately:
 *
 * +--------------------------+
 * | cstate बारtamp         |
 * +--------------------------+
 * | cstate index             |
 * +--------------------------+
 * | pstate बारtamp         |
 * +--------------------------+
 * | pstate index             |
 * +--------------------------+
 */
#घोषणा MAP_OFF_CSTATE_TIME	0
#घोषणा MAP_OFF_CSTATE_IDX	1
#घोषणा MAP_OFF_PSTATE_TIME	2
#घोषणा MAP_OFF_PSTATE_IDX	3
#घोषणा MAP_OFF_NUM		4

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, u64);
	__uपूर्णांक(max_entries, MAX_CPU * MAP_OFF_NUM);
पूर्ण my_map SEC(".maps");

/* cstate_duration records duration समय क्रम every idle state per CPU */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, u64);
	__uपूर्णांक(max_entries, MAX_CPU * MAX_CSTATE_ENTRIES);
पूर्ण cstate_duration SEC(".maps");

/* pstate_duration records duration समय क्रम every operating poपूर्णांक per CPU */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, u64);
	__uपूर्णांक(max_entries, MAX_CPU * MAX_PSTATE_ENTRIES);
पूर्ण pstate_duration SEC(".maps");

/*
 * The trace events क्रम cpu_idle and cpu_frequency are taken from:
 * /sys/kernel/debug/tracing/events/घातer/cpu_idle/क्रमmat
 * /sys/kernel/debug/tracing/events/घातer/cpu_frequency/क्रमmat
 *
 * These two events have same क्रमmat, so define one common काष्ठाure.
 */
काष्ठा cpu_args अणु
	u64 pad;
	u32 state;
	u32 cpu_id;
पूर्ण;

/* calculate pstate index, वापसs MAX_PSTATE_ENTRIES क्रम failure */
अटल u32 find_cpu_pstate_idx(u32 frequency)
अणु
	u32 i;

	क्रम (i = 0; i < माप(cpu_opps) / माप(u32); i++) अणु
		अगर (frequency == cpu_opps[i])
			वापस i;
	पूर्ण

	वापस i;
पूर्ण

SEC("tracepoint/power/cpu_idle")
पूर्णांक bpf_prog1(काष्ठा cpu_args *ctx)
अणु
	u64 *cts, *pts, *cstate, *pstate, prev_state, cur_ts, delta;
	u32 key, cpu, pstate_idx;
	u64 *val;

	अगर (ctx->cpu_id > MAX_CPU)
		वापस 0;

	cpu = ctx->cpu_id;

	key = cpu * MAP_OFF_NUM + MAP_OFF_CSTATE_TIME;
	cts = bpf_map_lookup_elem(&my_map, &key);
	अगर (!cts)
		वापस 0;

	key = cpu * MAP_OFF_NUM + MAP_OFF_CSTATE_IDX;
	cstate = bpf_map_lookup_elem(&my_map, &key);
	अगर (!cstate)
		वापस 0;

	key = cpu * MAP_OFF_NUM + MAP_OFF_PSTATE_TIME;
	pts = bpf_map_lookup_elem(&my_map, &key);
	अगर (!pts)
		वापस 0;

	key = cpu * MAP_OFF_NUM + MAP_OFF_PSTATE_IDX;
	pstate = bpf_map_lookup_elem(&my_map, &key);
	अगर (!pstate)
		वापस 0;

	prev_state = *cstate;
	*cstate = ctx->state;

	अगर (!*cts) अणु
		*cts = bpf_kसमय_get_ns();
		वापस 0;
	पूर्ण

	cur_ts = bpf_kसमय_get_ns();
	delta = cur_ts - *cts;
	*cts = cur_ts;

	/*
	 * When state करोesn't equal to (u32)-1, the cpu will enter
	 * one idle state; क्रम this हाल we need to record पूर्णांकerval
	 * क्रम the pstate.
	 *
	 *                 OPP2
	 *            +---------------------+
	 *     OPP1   |                     |
	 *   ---------+                     |
	 *                                  |  Idle state
	 *                                  +---------------
	 *
	 *            |<- pstate duration ->|
	 *            ^                     ^
	 *           pts                  cur_ts
	 */
	अगर (ctx->state != (u32)-1) अणु

		/* record pstate after have first cpu_frequency event */
		अगर (!*pts)
			वापस 0;

		delta = cur_ts - *pts;

		pstate_idx = find_cpu_pstate_idx(*pstate);
		अगर (pstate_idx >= MAX_PSTATE_ENTRIES)
			वापस 0;

		key = cpu * MAX_PSTATE_ENTRIES + pstate_idx;
		val = bpf_map_lookup_elem(&pstate_duration, &key);
		अगर (val)
			__sync_fetch_and_add((दीर्घ *)val, delta);

	/*
	 * When state equal to (u32)-1, the cpu just निकासs from one
	 * specअगरic idle state; क्रम this हाल we need to record
	 * पूर्णांकerval क्रम the pstate.
	 *
	 *       OPP2
	 *   -----------+
	 *              |                          OPP1
	 *              |                     +-----------
	 *              |     Idle state      |
	 *              +---------------------+
	 *
	 *              |<- cstate duration ->|
	 *              ^                     ^
	 *             cts                  cur_ts
	 */
	पूर्ण अन्यथा अणु

		key = cpu * MAX_CSTATE_ENTRIES + prev_state;
		val = bpf_map_lookup_elem(&cstate_duration, &key);
		अगर (val)
			__sync_fetch_and_add((दीर्घ *)val, delta);
	पूर्ण

	/* Update बारtamp क्रम pstate as new start समय */
	अगर (*pts)
		*pts = cur_ts;

	वापस 0;
पूर्ण

SEC("tracepoint/power/cpu_frequency")
पूर्णांक bpf_prog2(काष्ठा cpu_args *ctx)
अणु
	u64 *pts, *cstate, *pstate, prev_state, cur_ts, delta;
	u32 key, cpu, pstate_idx;
	u64 *val;

	cpu = ctx->cpu_id;

	key = cpu * MAP_OFF_NUM + MAP_OFF_PSTATE_TIME;
	pts = bpf_map_lookup_elem(&my_map, &key);
	अगर (!pts)
		वापस 0;

	key = cpu * MAP_OFF_NUM + MAP_OFF_PSTATE_IDX;
	pstate = bpf_map_lookup_elem(&my_map, &key);
	अगर (!pstate)
		वापस 0;

	key = cpu * MAP_OFF_NUM + MAP_OFF_CSTATE_IDX;
	cstate = bpf_map_lookup_elem(&my_map, &key);
	अगर (!cstate)
		वापस 0;

	prev_state = *pstate;
	*pstate = ctx->state;

	अगर (!*pts) अणु
		*pts = bpf_kसमय_get_ns();
		वापस 0;
	पूर्ण

	cur_ts = bpf_kसमय_get_ns();
	delta = cur_ts - *pts;
	*pts = cur_ts;

	/* When CPU is in idle, bail out to skip pstate statistics */
	अगर (*cstate != (u32)(-1))
		वापस 0;

	/*
	 * The cpu changes to another dअगरferent OPP (in below diagram
	 * change frequency from OPP3 to OPP1), need recording पूर्णांकerval
	 * क्रम previous frequency OPP3 and update बारtamp as start
	 * समय क्रम new frequency OPP1.
	 *
	 *                 OPP3
	 *            +---------------------+
	 *     OPP2   |                     |
	 *   ---------+                     |
	 *                                  |    OPP1
	 *                                  +---------------
	 *
	 *            |<- pstate duration ->|
	 *            ^                     ^
	 *           pts                  cur_ts
	 */
	pstate_idx = find_cpu_pstate_idx(*pstate);
	अगर (pstate_idx >= MAX_PSTATE_ENTRIES)
		वापस 0;

	key = cpu * MAX_PSTATE_ENTRIES + pstate_idx;
	val = bpf_map_lookup_elem(&pstate_duration, &key);
	अगर (val)
		__sync_fetch_and_add((दीर्घ *)val, delta);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
