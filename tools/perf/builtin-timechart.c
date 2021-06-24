<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * builtin-समयअक्षरt.c - make an svg समयअक्षरt of प्रणाली activity
 *
 * (C) Copyright 2009 Intel Corporation
 *
 * Authors:
 *     Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 */

#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>

#समावेश "builtin.h"
#समावेश "util/color.h"
#समावेश <linux/list.h>
#समावेश "util/evlist.h" // क्रम काष्ठा evsel_str_handler
#समावेश "util/evsel.h"
#समावेश <linux/kernel.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/समय64.h>
#समावेश <linux/zभाग.स>
#समावेश "util/symbol.h"
#समावेश "util/thread.h"
#समावेश "util/callchain.h"

#समावेश "perf.h"
#समावेश "util/header.h"
#समावेश <subcmd/pager.h>
#समावेश <subcmd/parse-options.h>
#समावेश "util/parse-events.h"
#समावेश "util/event.h"
#समावेश "util/session.h"
#समावेश "util/svghelper.h"
#समावेश "util/tool.h"
#समावेश "util/data.h"
#समावेश "util/debug.h"
#समावेश <linux/err.h>

#अगर_घोषित LACKS_OPEN_MEMSTREAM_PROTOTYPE
खाता *खोलो_memstream(अक्षर **ptr, माप_प्रकार *sizeloc);
#पूर्ण_अगर

#घोषणा SUPPORT_OLD_POWER_EVENTS 1
#घोषणा PWR_EVENT_EXIT -1

काष्ठा per_pid;
काष्ठा घातer_event;
काष्ठा wake_event;

काष्ठा समयअक्षरt अणु
	काष्ठा perf_tool	tool;
	काष्ठा per_pid		*all_data;
	काष्ठा घातer_event	*घातer_events;
	काष्ठा wake_event	*wake_events;
	पूर्णांक			proc_num;
	अचिन्हित पूर्णांक		numcpus;
	u64			min_freq,	/* Lowest CPU frequency seen */
				max_freq,	/* Highest CPU frequency seen */
				turbo_frequency,
				first_समय, last_समय;
	bool			घातer_only,
				tasks_only,
				with_backtrace,
				topology;
	bool			क्रमce;
	/* IO related settings */
	bool			io_only,
				skip_eagain;
	u64			io_events;
	u64			min_समय,
				merge_dist;
पूर्ण;

काष्ठा per_pidcomm;
काष्ठा cpu_sample;
काष्ठा io_sample;

/*
 * Dataकाष्ठाure layout:
 * We keep an list of "pid"s, matching the kernels notion of a task काष्ठा.
 * Each "pid" entry, has a list of "comm"s.
 *	this is because we want to track dअगरferent programs dअगरferent, जबतक
 *	exec will reuse the original pid (by design).
 * Each comm has a list of samples that will be used to draw
 * final graph.
 */

काष्ठा per_pid अणु
	काष्ठा per_pid *next;

	पूर्णांक		pid;
	पूर्णांक		ppid;

	u64		start_समय;
	u64		end_समय;
	u64		total_समय;
	u64		total_bytes;
	पूर्णांक		display;

	काष्ठा per_pidcomm *all;
	काष्ठा per_pidcomm *current;
पूर्ण;


काष्ठा per_pidcomm अणु
	काष्ठा per_pidcomm *next;

	u64		start_समय;
	u64		end_समय;
	u64		total_समय;
	u64		max_bytes;
	u64		total_bytes;

	पूर्णांक		Y;
	पूर्णांक		display;

	दीर्घ		state;
	u64		state_since;

	अक्षर		*comm;

	काष्ठा cpu_sample *samples;
	काष्ठा io_sample  *io_samples;
पूर्ण;

काष्ठा sample_wrapper अणु
	काष्ठा sample_wrapper *next;

	u64		बारtamp;
	अचिन्हित अक्षर	data[];
पूर्ण;

#घोषणा TYPE_NONE	0
#घोषणा TYPE_RUNNING	1
#घोषणा TYPE_WAITING	2
#घोषणा TYPE_BLOCKED	3

काष्ठा cpu_sample अणु
	काष्ठा cpu_sample *next;

	u64 start_समय;
	u64 end_समय;
	पूर्णांक type;
	पूर्णांक cpu;
	स्थिर अक्षर *backtrace;
पूर्ण;

क्रमागत अणु
	IOTYPE_READ,
	IOTYPE_WRITE,
	IOTYPE_SYNC,
	IOTYPE_TX,
	IOTYPE_RX,
	IOTYPE_POLL,
पूर्ण;

काष्ठा io_sample अणु
	काष्ठा io_sample *next;

	u64 start_समय;
	u64 end_समय;
	u64 bytes;
	पूर्णांक type;
	पूर्णांक fd;
	पूर्णांक err;
	पूर्णांक merges;
पूर्ण;

#घोषणा CSTATE 1
#घोषणा PSTATE 2

काष्ठा घातer_event अणु
	काष्ठा घातer_event *next;
	पूर्णांक type;
	पूर्णांक state;
	u64 start_समय;
	u64 end_समय;
	पूर्णांक cpu;
पूर्ण;

काष्ठा wake_event अणु
	काष्ठा wake_event *next;
	पूर्णांक waker;
	पूर्णांक wakee;
	u64 समय;
	स्थिर अक्षर *backtrace;
पूर्ण;

काष्ठा process_filter अणु
	अक्षर			*name;
	पूर्णांक			pid;
	काष्ठा process_filter	*next;
पूर्ण;

अटल काष्ठा process_filter *process_filter;


अटल काष्ठा per_pid *find_create_pid(काष्ठा समयअक्षरt *tअक्षरt, पूर्णांक pid)
अणु
	काष्ठा per_pid *cursor = tअक्षरt->all_data;

	जबतक (cursor) अणु
		अगर (cursor->pid == pid)
			वापस cursor;
		cursor = cursor->next;
	पूर्ण
	cursor = zalloc(माप(*cursor));
	निश्चित(cursor != शून्य);
	cursor->pid = pid;
	cursor->next = tअक्षरt->all_data;
	tअक्षरt->all_data = cursor;
	वापस cursor;
पूर्ण

अटल व्योम pid_set_comm(काष्ठा समयअक्षरt *tअक्षरt, पूर्णांक pid, अक्षर *comm)
अणु
	काष्ठा per_pid *p;
	काष्ठा per_pidcomm *c;
	p = find_create_pid(tअक्षरt, pid);
	c = p->all;
	जबतक (c) अणु
		अगर (c->comm && म_भेद(c->comm, comm) == 0) अणु
			p->current = c;
			वापस;
		पूर्ण
		अगर (!c->comm) अणु
			c->comm = strdup(comm);
			p->current = c;
			वापस;
		पूर्ण
		c = c->next;
	पूर्ण
	c = zalloc(माप(*c));
	निश्चित(c != शून्य);
	c->comm = strdup(comm);
	p->current = c;
	c->next = p->all;
	p->all = c;
पूर्ण

अटल व्योम pid_विभाजन(काष्ठा समयअक्षरt *tअक्षरt, पूर्णांक pid, पूर्णांक ppid, u64 बारtamp)
अणु
	काष्ठा per_pid *p, *pp;
	p = find_create_pid(tअक्षरt, pid);
	pp = find_create_pid(tअक्षरt, ppid);
	p->ppid = ppid;
	अगर (pp->current && pp->current->comm && !p->current)
		pid_set_comm(tअक्षरt, pid, pp->current->comm);

	p->start_समय = बारtamp;
	अगर (p->current && !p->current->start_समय) अणु
		p->current->start_समय = बारtamp;
		p->current->state_since = बारtamp;
	पूर्ण
पूर्ण

अटल व्योम pid_निकास(काष्ठा समयअक्षरt *tअक्षरt, पूर्णांक pid, u64 बारtamp)
अणु
	काष्ठा per_pid *p;
	p = find_create_pid(tअक्षरt, pid);
	p->end_समय = बारtamp;
	अगर (p->current)
		p->current->end_समय = बारtamp;
पूर्ण

अटल व्योम pid_put_sample(काष्ठा समयअक्षरt *tअक्षरt, पूर्णांक pid, पूर्णांक type,
			   अचिन्हित पूर्णांक cpu, u64 start, u64 end,
			   स्थिर अक्षर *backtrace)
अणु
	काष्ठा per_pid *p;
	काष्ठा per_pidcomm *c;
	काष्ठा cpu_sample *sample;

	p = find_create_pid(tअक्षरt, pid);
	c = p->current;
	अगर (!c) अणु
		c = zalloc(माप(*c));
		निश्चित(c != शून्य);
		p->current = c;
		c->next = p->all;
		p->all = c;
	पूर्ण

	sample = zalloc(माप(*sample));
	निश्चित(sample != शून्य);
	sample->start_समय = start;
	sample->end_समय = end;
	sample->type = type;
	sample->next = c->samples;
	sample->cpu = cpu;
	sample->backtrace = backtrace;
	c->samples = sample;

	अगर (sample->type == TYPE_RUNNING && end > start && start > 0) अणु
		c->total_समय += (end-start);
		p->total_समय += (end-start);
	पूर्ण

	अगर (c->start_समय == 0 || c->start_समय > start)
		c->start_समय = start;
	अगर (p->start_समय == 0 || p->start_समय > start)
		p->start_समय = start;
पूर्ण

#घोषणा MAX_CPUS 4096

अटल u64 cpus_cstate_start_बार[MAX_CPUS];
अटल पूर्णांक cpus_cstate_state[MAX_CPUS];
अटल u64 cpus_pstate_start_बार[MAX_CPUS];
अटल u64 cpus_pstate_state[MAX_CPUS];

अटल पूर्णांक process_comm_event(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample __maybe_unused,
			      काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा समयअक्षरt *tअक्षरt = container_of(tool, काष्ठा समयअक्षरt, tool);
	pid_set_comm(tअक्षरt, event->comm.tid, event->comm.comm);
	वापस 0;
पूर्ण

अटल पूर्णांक process_विभाजन_event(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample __maybe_unused,
			      काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा समयअक्षरt *tअक्षरt = container_of(tool, काष्ठा समयअक्षरt, tool);
	pid_विभाजन(tअक्षरt, event->विभाजन.pid, event->विभाजन.ppid, event->विभाजन.समय);
	वापस 0;
पूर्ण

अटल पूर्णांक process_निकास_event(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample __maybe_unused,
			      काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा समयअक्षरt *tअक्षरt = container_of(tool, काष्ठा समयअक्षरt, tool);
	pid_निकास(tअक्षरt, event->विभाजन.pid, event->विभाजन.समय);
	वापस 0;
पूर्ण

#अगर_घोषित SUPPORT_OLD_POWER_EVENTS
अटल पूर्णांक use_old_घातer_events;
#पूर्ण_अगर

अटल व्योम c_state_start(पूर्णांक cpu, u64 बारtamp, पूर्णांक state)
अणु
	cpus_cstate_start_बार[cpu] = बारtamp;
	cpus_cstate_state[cpu] = state;
पूर्ण

अटल व्योम c_state_end(काष्ठा समयअक्षरt *tअक्षरt, पूर्णांक cpu, u64 बारtamp)
अणु
	काष्ठा घातer_event *pwr = zalloc(माप(*pwr));

	अगर (!pwr)
		वापस;

	pwr->state = cpus_cstate_state[cpu];
	pwr->start_समय = cpus_cstate_start_बार[cpu];
	pwr->end_समय = बारtamp;
	pwr->cpu = cpu;
	pwr->type = CSTATE;
	pwr->next = tअक्षरt->घातer_events;

	tअक्षरt->घातer_events = pwr;
पूर्ण

अटल व्योम p_state_change(काष्ठा समयअक्षरt *tअक्षरt, पूर्णांक cpu, u64 बारtamp, u64 new_freq)
अणु
	काष्ठा घातer_event *pwr;

	अगर (new_freq > 8000000) /* detect invalid data */
		वापस;

	pwr = zalloc(माप(*pwr));
	अगर (!pwr)
		वापस;

	pwr->state = cpus_pstate_state[cpu];
	pwr->start_समय = cpus_pstate_start_बार[cpu];
	pwr->end_समय = बारtamp;
	pwr->cpu = cpu;
	pwr->type = PSTATE;
	pwr->next = tअक्षरt->घातer_events;

	अगर (!pwr->start_समय)
		pwr->start_समय = tअक्षरt->first_समय;

	tअक्षरt->घातer_events = pwr;

	cpus_pstate_state[cpu] = new_freq;
	cpus_pstate_start_बार[cpu] = बारtamp;

	अगर ((u64)new_freq > tअक्षरt->max_freq)
		tअक्षरt->max_freq = new_freq;

	अगर (new_freq < tअक्षरt->min_freq || tअक्षरt->min_freq == 0)
		tअक्षरt->min_freq = new_freq;

	अगर (new_freq == tअक्षरt->max_freq - 1000)
		tअक्षरt->turbo_frequency = tअक्षरt->max_freq;
पूर्ण

अटल व्योम sched_wakeup(काष्ठा समयअक्षरt *tअक्षरt, पूर्णांक cpu, u64 बारtamp,
			 पूर्णांक waker, पूर्णांक wakee, u8 flags, स्थिर अक्षर *backtrace)
अणु
	काष्ठा per_pid *p;
	काष्ठा wake_event *we = zalloc(माप(*we));

	अगर (!we)
		वापस;

	we->समय = बारtamp;
	we->waker = waker;
	we->backtrace = backtrace;

	अगर ((flags & TRACE_FLAG_HARसूचीQ) || (flags & TRACE_FLAG_SOFTIRQ))
		we->waker = -1;

	we->wakee = wakee;
	we->next = tअक्षरt->wake_events;
	tअक्षरt->wake_events = we;
	p = find_create_pid(tअक्षरt, we->wakee);

	अगर (p && p->current && p->current->state == TYPE_NONE) अणु
		p->current->state_since = बारtamp;
		p->current->state = TYPE_WAITING;
	पूर्ण
	अगर (p && p->current && p->current->state == TYPE_BLOCKED) अणु
		pid_put_sample(tअक्षरt, p->pid, p->current->state, cpu,
			       p->current->state_since, बारtamp, शून्य);
		p->current->state_since = बारtamp;
		p->current->state = TYPE_WAITING;
	पूर्ण
पूर्ण

अटल व्योम sched_चयन(काष्ठा समयअक्षरt *tअक्षरt, पूर्णांक cpu, u64 बारtamp,
			 पूर्णांक prev_pid, पूर्णांक next_pid, u64 prev_state,
			 स्थिर अक्षर *backtrace)
अणु
	काष्ठा per_pid *p = शून्य, *prev_p;

	prev_p = find_create_pid(tअक्षरt, prev_pid);

	p = find_create_pid(tअक्षरt, next_pid);

	अगर (prev_p->current && prev_p->current->state != TYPE_NONE)
		pid_put_sample(tअक्षरt, prev_pid, TYPE_RUNNING, cpu,
			       prev_p->current->state_since, बारtamp,
			       backtrace);
	अगर (p && p->current) अणु
		अगर (p->current->state != TYPE_NONE)
			pid_put_sample(tअक्षरt, next_pid, p->current->state, cpu,
				       p->current->state_since, बारtamp,
				       backtrace);

		p->current->state_since = बारtamp;
		p->current->state = TYPE_RUNNING;
	पूर्ण

	अगर (prev_p->current) अणु
		prev_p->current->state = TYPE_NONE;
		prev_p->current->state_since = बारtamp;
		अगर (prev_state & 2)
			prev_p->current->state = TYPE_BLOCKED;
		अगर (prev_state == 0)
			prev_p->current->state = TYPE_WAITING;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *cat_backtrace(जोड़ perf_event *event,
				 काष्ठा perf_sample *sample,
				 काष्ठा machine *machine)
अणु
	काष्ठा addr_location al;
	अचिन्हित पूर्णांक i;
	अक्षर *p = शून्य;
	माप_प्रकार p_len;
	u8 cpumode = PERF_RECORD_MISC_USER;
	काष्ठा addr_location tal;
	काष्ठा ip_callchain *chain = sample->callchain;
	खाता *f = खोलो_memstream(&p, &p_len);

	अगर (!f) अणु
		लिखो_त्रुटि("open_memstream error");
		वापस शून्य;
	पूर्ण

	अगर (!chain)
		जाओ निकास;

	अगर (machine__resolve(machine, &al, sample) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "problem processing %d event, skipping it.\n",
			event->header.type);
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < chain->nr; i++) अणु
		u64 ip;

		अगर (callchain_param.order == ORDER_CALLEE)
			ip = chain->ips[i];
		अन्यथा
			ip = chain->ips[chain->nr - i - 1];

		अगर (ip >= PERF_CONTEXT_MAX) अणु
			चयन (ip) अणु
			हाल PERF_CONTEXT_HV:
				cpumode = PERF_RECORD_MISC_HYPERVISOR;
				अवरोध;
			हाल PERF_CONTEXT_KERNEL:
				cpumode = PERF_RECORD_MISC_KERNEL;
				अवरोध;
			हाल PERF_CONTEXT_USER:
				cpumode = PERF_RECORD_MISC_USER;
				अवरोध;
			शेष:
				pr_debug("invalid callchain context: "
					 "%"PRId64"\n", (s64) ip);

				/*
				 * It seems the callchain is corrupted.
				 * Discard all.
				 */
				zमुक्त(&p);
				जाओ निकास_put;
			पूर्ण
			जारी;
		पूर्ण

		tal.filtered = 0;
		अगर (thपढ़ो__find_symbol(al.thपढ़ो, cpumode, ip, &tal))
			ख_लिखो(f, "..... %016" PRIx64 " %s\n", ip, tal.sym->name);
		अन्यथा
			ख_लिखो(f, "..... %016" PRIx64 "\n", ip);
	पूर्ण
निकास_put:
	addr_location__put(&al);
निकास:
	ख_बंद(f);

	वापस p;
पूर्ण

प्रकार पूर्णांक (*tracepoपूर्णांक_handler)(काष्ठा समयअक्षरt *tअक्षरt,
				  काष्ठा evsel *evsel,
				  काष्ठा perf_sample *sample,
				  स्थिर अक्षर *backtrace);

अटल पूर्णांक process_sample_event(काष्ठा perf_tool *tool,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel,
				काष्ठा machine *machine)
अणु
	काष्ठा समयअक्षरt *tअक्षरt = container_of(tool, काष्ठा समयअक्षरt, tool);

	अगर (evsel->core.attr.sample_type & PERF_SAMPLE_TIME) अणु
		अगर (!tअक्षरt->first_समय || tअक्षरt->first_समय > sample->समय)
			tअक्षरt->first_समय = sample->समय;
		अगर (tअक्षरt->last_समय < sample->समय)
			tअक्षरt->last_समय = sample->समय;
	पूर्ण

	अगर (evsel->handler != शून्य) अणु
		tracepoपूर्णांक_handler f = evsel->handler;
		वापस f(tअक्षरt, evsel, sample,
			 cat_backtrace(event, sample, machine));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
process_sample_cpu_idle(काष्ठा समयअक्षरt *tअक्षरt __maybe_unused,
			काष्ठा evsel *evsel,
			काष्ठा perf_sample *sample,
			स्थिर अक्षर *backtrace __maybe_unused)
अणु
	u32 state  = evsel__पूर्णांकval(evsel, sample, "state");
	u32 cpu_id = evsel__पूर्णांकval(evsel, sample, "cpu_id");

	अगर (state == (u32)PWR_EVENT_EXIT)
		c_state_end(tअक्षरt, cpu_id, sample->समय);
	अन्यथा
		c_state_start(cpu_id, sample->समय, state);
	वापस 0;
पूर्ण

अटल पूर्णांक
process_sample_cpu_frequency(काष्ठा समयअक्षरt *tअक्षरt,
			     काष्ठा evsel *evsel,
			     काष्ठा perf_sample *sample,
			     स्थिर अक्षर *backtrace __maybe_unused)
अणु
	u32 state  = evsel__पूर्णांकval(evsel, sample, "state");
	u32 cpu_id = evsel__पूर्णांकval(evsel, sample, "cpu_id");

	p_state_change(tअक्षरt, cpu_id, sample->समय, state);
	वापस 0;
पूर्ण

अटल पूर्णांक
process_sample_sched_wakeup(काष्ठा समयअक्षरt *tअक्षरt,
			    काष्ठा evsel *evsel,
			    काष्ठा perf_sample *sample,
			    स्थिर अक्षर *backtrace)
अणु
	u8 flags  = evsel__पूर्णांकval(evsel, sample, "common_flags");
	पूर्णांक waker = evsel__पूर्णांकval(evsel, sample, "common_pid");
	पूर्णांक wakee = evsel__पूर्णांकval(evsel, sample, "pid");

	sched_wakeup(tअक्षरt, sample->cpu, sample->समय, waker, wakee, flags, backtrace);
	वापस 0;
पूर्ण

अटल पूर्णांक
process_sample_sched_चयन(काष्ठा समयअक्षरt *tअक्षरt,
			    काष्ठा evsel *evsel,
			    काष्ठा perf_sample *sample,
			    स्थिर अक्षर *backtrace)
अणु
	पूर्णांक prev_pid   = evsel__पूर्णांकval(evsel, sample, "prev_pid");
	पूर्णांक next_pid   = evsel__पूर्णांकval(evsel, sample, "next_pid");
	u64 prev_state = evsel__पूर्णांकval(evsel, sample, "prev_state");

	sched_चयन(tअक्षरt, sample->cpu, sample->समय, prev_pid, next_pid,
		     prev_state, backtrace);
	वापस 0;
पूर्ण

#अगर_घोषित SUPPORT_OLD_POWER_EVENTS
अटल पूर्णांक
process_sample_घातer_start(काष्ठा समयअक्षरt *tअक्षरt __maybe_unused,
			   काष्ठा evsel *evsel,
			   काष्ठा perf_sample *sample,
			   स्थिर अक्षर *backtrace __maybe_unused)
अणु
	u64 cpu_id = evsel__पूर्णांकval(evsel, sample, "cpu_id");
	u64 value  = evsel__पूर्णांकval(evsel, sample, "value");

	c_state_start(cpu_id, sample->समय, value);
	वापस 0;
पूर्ण

अटल पूर्णांक
process_sample_घातer_end(काष्ठा समयअक्षरt *tअक्षरt,
			 काष्ठा evsel *evsel __maybe_unused,
			 काष्ठा perf_sample *sample,
			 स्थिर अक्षर *backtrace __maybe_unused)
अणु
	c_state_end(tअक्षरt, sample->cpu, sample->समय);
	वापस 0;
पूर्ण

अटल पूर्णांक
process_sample_घातer_frequency(काष्ठा समयअक्षरt *tअक्षरt,
			       काष्ठा evsel *evsel,
			       काष्ठा perf_sample *sample,
			       स्थिर अक्षर *backtrace __maybe_unused)
अणु
	u64 cpu_id = evsel__पूर्णांकval(evsel, sample, "cpu_id");
	u64 value  = evsel__पूर्णांकval(evsel, sample, "value");

	p_state_change(tअक्षरt, cpu_id, sample->समय, value);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* SUPPORT_OLD_POWER_EVENTS */

/*
 * After the last sample we need to wrap up the current C/P state
 * and बंद out each CPU क्रम these.
 */
अटल व्योम end_sample_processing(काष्ठा समयअक्षरt *tअक्षरt)
अणु
	u64 cpu;
	काष्ठा घातer_event *pwr;

	क्रम (cpu = 0; cpu <= tअक्षरt->numcpus; cpu++) अणु
		/* C state */
#अगर 0
		pwr = zalloc(माप(*pwr));
		अगर (!pwr)
			वापस;

		pwr->state = cpus_cstate_state[cpu];
		pwr->start_समय = cpus_cstate_start_बार[cpu];
		pwr->end_समय = tअक्षरt->last_समय;
		pwr->cpu = cpu;
		pwr->type = CSTATE;
		pwr->next = tअक्षरt->घातer_events;

		tअक्षरt->घातer_events = pwr;
#पूर्ण_अगर
		/* P state */

		pwr = zalloc(माप(*pwr));
		अगर (!pwr)
			वापस;

		pwr->state = cpus_pstate_state[cpu];
		pwr->start_समय = cpus_pstate_start_बार[cpu];
		pwr->end_समय = tअक्षरt->last_समय;
		pwr->cpu = cpu;
		pwr->type = PSTATE;
		pwr->next = tअक्षरt->घातer_events;

		अगर (!pwr->start_समय)
			pwr->start_समय = tअक्षरt->first_समय;
		अगर (!pwr->state)
			pwr->state = tअक्षरt->min_freq;
		tअक्षरt->घातer_events = pwr;
	पूर्ण
पूर्ण

अटल पूर्णांक pid_begin_io_sample(काष्ठा समयअक्षरt *tअक्षरt, पूर्णांक pid, पूर्णांक type,
			       u64 start, पूर्णांक fd)
अणु
	काष्ठा per_pid *p = find_create_pid(tअक्षरt, pid);
	काष्ठा per_pidcomm *c = p->current;
	काष्ठा io_sample *sample;
	काष्ठा io_sample *prev;

	अगर (!c) अणु
		c = zalloc(माप(*c));
		अगर (!c)
			वापस -ENOMEM;
		p->current = c;
		c->next = p->all;
		p->all = c;
	पूर्ण

	prev = c->io_samples;

	अगर (prev && prev->start_समय && !prev->end_समय) अणु
		pr_warning("Skip invalid start event: "
			   "previous event already started!\n");

		/* हटाओ previous event that has been started,
		 * we are not sure we will ever get an end क्रम it */
		c->io_samples = prev->next;
		मुक्त(prev);
		वापस 0;
	पूर्ण

	sample = zalloc(माप(*sample));
	अगर (!sample)
		वापस -ENOMEM;
	sample->start_समय = start;
	sample->type = type;
	sample->fd = fd;
	sample->next = c->io_samples;
	c->io_samples = sample;

	अगर (c->start_समय == 0 || c->start_समय > start)
		c->start_समय = start;

	वापस 0;
पूर्ण

अटल पूर्णांक pid_end_io_sample(काष्ठा समयअक्षरt *tअक्षरt, पूर्णांक pid, पूर्णांक type,
			     u64 end, दीर्घ ret)
अणु
	काष्ठा per_pid *p = find_create_pid(tअक्षरt, pid);
	काष्ठा per_pidcomm *c = p->current;
	काष्ठा io_sample *sample, *prev;

	अगर (!c) अणु
		pr_warning("Invalid pidcomm!\n");
		वापस -1;
	पूर्ण

	sample = c->io_samples;

	अगर (!sample) /* skip partially captured events */
		वापस 0;

	अगर (sample->end_समय) अणु
		pr_warning("Skip invalid end event: "
			   "previous event already ended!\n");
		वापस 0;
	पूर्ण

	अगर (sample->type != type) अणु
		pr_warning("Skip invalid end event: invalid event type!\n");
		वापस 0;
	पूर्ण

	sample->end_समय = end;
	prev = sample->next;

	/* we want to be able to see small and fast transfers, so make them
	 * at least min_समय दीर्घ, but करोn't overlap them */
	अगर (sample->end_समय - sample->start_समय < tअक्षरt->min_समय)
		sample->end_समय = sample->start_समय + tअक्षरt->min_समय;
	अगर (prev && sample->start_समय < prev->end_समय) अणु
		अगर (prev->err) /* try to make errors more visible */
			sample->start_समय = prev->end_समय;
		अन्यथा
			prev->end_समय = sample->start_समय;
	पूर्ण

	अगर (ret < 0) अणु
		sample->err = ret;
	पूर्ण अन्यथा अगर (type == IOTYPE_READ || type == IOTYPE_WRITE ||
		   type == IOTYPE_TX || type == IOTYPE_RX) अणु

		अगर ((u64)ret > c->max_bytes)
			c->max_bytes = ret;

		c->total_bytes += ret;
		p->total_bytes += ret;
		sample->bytes = ret;
	पूर्ण

	/* merge two requests to make svg smaller and render-मित्रly */
	अगर (prev &&
	    prev->type == sample->type &&
	    prev->err == sample->err &&
	    prev->fd == sample->fd &&
	    prev->end_समय + tअक्षरt->merge_dist >= sample->start_समय) अणु

		sample->bytes += prev->bytes;
		sample->merges += prev->merges + 1;

		sample->start_समय = prev->start_समय;
		sample->next = prev->next;
		मुक्त(prev);

		अगर (!sample->err && sample->bytes > c->max_bytes)
			c->max_bytes = sample->bytes;
	पूर्ण

	tअक्षरt->io_events++;

	वापस 0;
पूर्ण

अटल पूर्णांक
process_enter_पढ़ो(काष्ठा समयअक्षरt *tअक्षरt,
		   काष्ठा evsel *evsel,
		   काष्ठा perf_sample *sample)
अणु
	दीर्घ fd = evsel__पूर्णांकval(evsel, sample, "fd");
	वापस pid_begin_io_sample(tअक्षरt, sample->tid, IOTYPE_READ,
				   sample->समय, fd);
पूर्ण

अटल पूर्णांक
process_निकास_पढ़ो(काष्ठा समयअक्षरt *tअक्षरt,
		  काष्ठा evsel *evsel,
		  काष्ठा perf_sample *sample)
अणु
	दीर्घ ret = evsel__पूर्णांकval(evsel, sample, "ret");
	वापस pid_end_io_sample(tअक्षरt, sample->tid, IOTYPE_READ,
				 sample->समय, ret);
पूर्ण

अटल पूर्णांक
process_enter_ग_लिखो(काष्ठा समयअक्षरt *tअक्षरt,
		    काष्ठा evsel *evsel,
		    काष्ठा perf_sample *sample)
अणु
	दीर्घ fd = evsel__पूर्णांकval(evsel, sample, "fd");
	वापस pid_begin_io_sample(tअक्षरt, sample->tid, IOTYPE_WRITE,
				   sample->समय, fd);
पूर्ण

अटल पूर्णांक
process_निकास_ग_लिखो(काष्ठा समयअक्षरt *tअक्षरt,
		   काष्ठा evsel *evsel,
		   काष्ठा perf_sample *sample)
अणु
	दीर्घ ret = evsel__पूर्णांकval(evsel, sample, "ret");
	वापस pid_end_io_sample(tअक्षरt, sample->tid, IOTYPE_WRITE,
				 sample->समय, ret);
पूर्ण

अटल पूर्णांक
process_enter_sync(काष्ठा समयअक्षरt *tअक्षरt,
		   काष्ठा evsel *evsel,
		   काष्ठा perf_sample *sample)
अणु
	दीर्घ fd = evsel__पूर्णांकval(evsel, sample, "fd");
	वापस pid_begin_io_sample(tअक्षरt, sample->tid, IOTYPE_SYNC,
				   sample->समय, fd);
पूर्ण

अटल पूर्णांक
process_निकास_sync(काष्ठा समयअक्षरt *tअक्षरt,
		  काष्ठा evsel *evsel,
		  काष्ठा perf_sample *sample)
अणु
	दीर्घ ret = evsel__पूर्णांकval(evsel, sample, "ret");
	वापस pid_end_io_sample(tअक्षरt, sample->tid, IOTYPE_SYNC,
				 sample->समय, ret);
पूर्ण

अटल पूर्णांक
process_enter_tx(काष्ठा समयअक्षरt *tअक्षरt,
		 काष्ठा evsel *evsel,
		 काष्ठा perf_sample *sample)
अणु
	दीर्घ fd = evsel__पूर्णांकval(evsel, sample, "fd");
	वापस pid_begin_io_sample(tअक्षरt, sample->tid, IOTYPE_TX,
				   sample->समय, fd);
पूर्ण

अटल पूर्णांक
process_निकास_tx(काष्ठा समयअक्षरt *tअक्षरt,
		काष्ठा evsel *evsel,
		काष्ठा perf_sample *sample)
अणु
	दीर्घ ret = evsel__पूर्णांकval(evsel, sample, "ret");
	वापस pid_end_io_sample(tअक्षरt, sample->tid, IOTYPE_TX,
				 sample->समय, ret);
पूर्ण

अटल पूर्णांक
process_enter_rx(काष्ठा समयअक्षरt *tअक्षरt,
		 काष्ठा evsel *evsel,
		 काष्ठा perf_sample *sample)
अणु
	दीर्घ fd = evsel__पूर्णांकval(evsel, sample, "fd");
	वापस pid_begin_io_sample(tअक्षरt, sample->tid, IOTYPE_RX,
				   sample->समय, fd);
पूर्ण

अटल पूर्णांक
process_निकास_rx(काष्ठा समयअक्षरt *tअक्षरt,
		काष्ठा evsel *evsel,
		काष्ठा perf_sample *sample)
अणु
	दीर्घ ret = evsel__पूर्णांकval(evsel, sample, "ret");
	वापस pid_end_io_sample(tअक्षरt, sample->tid, IOTYPE_RX,
				 sample->समय, ret);
पूर्ण

अटल पूर्णांक
process_enter_poll(काष्ठा समयअक्षरt *tअक्षरt,
		   काष्ठा evsel *evsel,
		   काष्ठा perf_sample *sample)
अणु
	दीर्घ fd = evsel__पूर्णांकval(evsel, sample, "fd");
	वापस pid_begin_io_sample(tअक्षरt, sample->tid, IOTYPE_POLL,
				   sample->समय, fd);
पूर्ण

अटल पूर्णांक
process_निकास_poll(काष्ठा समयअक्षरt *tअक्षरt,
		  काष्ठा evsel *evsel,
		  काष्ठा perf_sample *sample)
अणु
	दीर्घ ret = evsel__पूर्णांकval(evsel, sample, "ret");
	वापस pid_end_io_sample(tअक्षरt, sample->tid, IOTYPE_POLL,
				 sample->समय, ret);
पूर्ण

/*
 * Sort the pid dataकाष्ठाure
 */
अटल व्योम sort_pids(काष्ठा समयअक्षरt *tअक्षरt)
अणु
	काष्ठा per_pid *new_list, *p, *cursor, *prev;
	/* sort by ppid first, then by pid, lowest to highest */

	new_list = शून्य;

	जबतक (tअक्षरt->all_data) अणु
		p = tअक्षरt->all_data;
		tअक्षरt->all_data = p->next;
		p->next = शून्य;

		अगर (new_list == शून्य) अणु
			new_list = p;
			p->next = शून्य;
			जारी;
		पूर्ण
		prev = शून्य;
		cursor = new_list;
		जबतक (cursor) अणु
			अगर (cursor->ppid > p->ppid ||
				(cursor->ppid == p->ppid && cursor->pid > p->pid)) अणु
				/* must insert beक्रमe */
				अगर (prev) अणु
					p->next = prev->next;
					prev->next = p;
					cursor = शून्य;
					जारी;
				पूर्ण अन्यथा अणु
					p->next = new_list;
					new_list = p;
					cursor = शून्य;
					जारी;
				पूर्ण
			पूर्ण

			prev = cursor;
			cursor = cursor->next;
			अगर (!cursor)
				prev->next = p;
		पूर्ण
	पूर्ण
	tअक्षरt->all_data = new_list;
पूर्ण


अटल व्योम draw_c_p_states(काष्ठा समयअक्षरt *tअक्षरt)
अणु
	काष्ठा घातer_event *pwr;
	pwr = tअक्षरt->घातer_events;

	/*
	 * two pass drawing so that the P state bars are on top of the C state blocks
	 */
	जबतक (pwr) अणु
		अगर (pwr->type == CSTATE)
			svg_cstate(pwr->cpu, pwr->start_समय, pwr->end_समय, pwr->state);
		pwr = pwr->next;
	पूर्ण

	pwr = tअक्षरt->घातer_events;
	जबतक (pwr) अणु
		अगर (pwr->type == PSTATE) अणु
			अगर (!pwr->state)
				pwr->state = tअक्षरt->min_freq;
			svg_pstate(pwr->cpu, pwr->start_समय, pwr->end_समय, pwr->state);
		पूर्ण
		pwr = pwr->next;
	पूर्ण
पूर्ण

अटल व्योम draw_wakeups(काष्ठा समयअक्षरt *tअक्षरt)
अणु
	काष्ठा wake_event *we;
	काष्ठा per_pid *p;
	काष्ठा per_pidcomm *c;

	we = tअक्षरt->wake_events;
	जबतक (we) अणु
		पूर्णांक from = 0, to = 0;
		अक्षर *task_from = शून्य, *task_to = शून्य;

		/* locate the column of the waker and wakee */
		p = tअक्षरt->all_data;
		जबतक (p) अणु
			अगर (p->pid == we->waker || p->pid == we->wakee) अणु
				c = p->all;
				जबतक (c) अणु
					अगर (c->Y && c->start_समय <= we->समय && c->end_समय >= we->समय) अणु
						अगर (p->pid == we->waker && !from) अणु
							from = c->Y;
							task_from = strdup(c->comm);
						पूर्ण
						अगर (p->pid == we->wakee && !to) अणु
							to = c->Y;
							task_to = strdup(c->comm);
						पूर्ण
					पूर्ण
					c = c->next;
				पूर्ण
				c = p->all;
				जबतक (c) अणु
					अगर (p->pid == we->waker && !from) अणु
						from = c->Y;
						task_from = strdup(c->comm);
					पूर्ण
					अगर (p->pid == we->wakee && !to) अणु
						to = c->Y;
						task_to = strdup(c->comm);
					पूर्ण
					c = c->next;
				पूर्ण
			पूर्ण
			p = p->next;
		पूर्ण

		अगर (!task_from) अणु
			task_from = दो_स्मृति(40);
			प्र_लिखो(task_from, "[%i]", we->waker);
		पूर्ण
		अगर (!task_to) अणु
			task_to = दो_स्मृति(40);
			प्र_लिखो(task_to, "[%i]", we->wakee);
		पूर्ण

		अगर (we->waker == -1)
			svg_पूर्णांकerrupt(we->समय, to, we->backtrace);
		अन्यथा अगर (from && to && असल(from - to) == 1)
			svg_wakeline(we->समय, from, to, we->backtrace);
		अन्यथा
			svg_partial_wakeline(we->समय, from, task_from, to,
					     task_to, we->backtrace);
		we = we->next;

		मुक्त(task_from);
		मुक्त(task_to);
	पूर्ण
पूर्ण

अटल व्योम draw_cpu_usage(काष्ठा समयअक्षरt *tअक्षरt)
अणु
	काष्ठा per_pid *p;
	काष्ठा per_pidcomm *c;
	काष्ठा cpu_sample *sample;
	p = tअक्षरt->all_data;
	जबतक (p) अणु
		c = p->all;
		जबतक (c) अणु
			sample = c->samples;
			जबतक (sample) अणु
				अगर (sample->type == TYPE_RUNNING) अणु
					svg_process(sample->cpu,
						    sample->start_समय,
						    sample->end_समय,
						    p->pid,
						    c->comm,
						    sample->backtrace);
				पूर्ण

				sample = sample->next;
			पूर्ण
			c = c->next;
		पूर्ण
		p = p->next;
	पूर्ण
पूर्ण

अटल व्योम draw_io_bars(काष्ठा समयअक्षरt *tअक्षरt)
अणु
	स्थिर अक्षर *suf;
	द्विगुन bytes;
	अक्षर comm[256];
	काष्ठा per_pid *p;
	काष्ठा per_pidcomm *c;
	काष्ठा io_sample *sample;
	पूर्णांक Y = 1;

	p = tअक्षरt->all_data;
	जबतक (p) अणु
		c = p->all;
		जबतक (c) अणु
			अगर (!c->display) अणु
				c->Y = 0;
				c = c->next;
				जारी;
			पूर्ण

			svg_box(Y, c->start_समय, c->end_समय, "process3");
			sample = c->io_samples;
			क्रम (sample = c->io_samples; sample; sample = sample->next) अणु
				द्विगुन h = (द्विगुन)sample->bytes / c->max_bytes;

				अगर (tअक्षरt->skip_eagain &&
				    sample->err == -EAGAIN)
					जारी;

				अगर (sample->err)
					h = 1;

				अगर (sample->type == IOTYPE_SYNC)
					svg_fbox(Y,
						sample->start_समय,
						sample->end_समय,
						1,
						sample->err ? "error" : "sync",
						sample->fd,
						sample->err,
						sample->merges);
				अन्यथा अगर (sample->type == IOTYPE_POLL)
					svg_fbox(Y,
						sample->start_समय,
						sample->end_समय,
						1,
						sample->err ? "error" : "poll",
						sample->fd,
						sample->err,
						sample->merges);
				अन्यथा अगर (sample->type == IOTYPE_READ)
					svg_ubox(Y,
						sample->start_समय,
						sample->end_समय,
						h,
						sample->err ? "error" : "disk",
						sample->fd,
						sample->err,
						sample->merges);
				अन्यथा अगर (sample->type == IOTYPE_WRITE)
					svg_lbox(Y,
						sample->start_समय,
						sample->end_समय,
						h,
						sample->err ? "error" : "disk",
						sample->fd,
						sample->err,
						sample->merges);
				अन्यथा अगर (sample->type == IOTYPE_RX)
					svg_ubox(Y,
						sample->start_समय,
						sample->end_समय,
						h,
						sample->err ? "error" : "net",
						sample->fd,
						sample->err,
						sample->merges);
				अन्यथा अगर (sample->type == IOTYPE_TX)
					svg_lbox(Y,
						sample->start_समय,
						sample->end_समय,
						h,
						sample->err ? "error" : "net",
						sample->fd,
						sample->err,
						sample->merges);
			पूर्ण

			suf = "";
			bytes = c->total_bytes;
			अगर (bytes > 1024) अणु
				bytes = bytes / 1024;
				suf = "K";
			पूर्ण
			अगर (bytes > 1024) अणु
				bytes = bytes / 1024;
				suf = "M";
			पूर्ण
			अगर (bytes > 1024) अणु
				bytes = bytes / 1024;
				suf = "G";
			पूर्ण


			प्र_लिखो(comm, "%s:%i (%3.1f %sbytes)", c->comm ?: "", p->pid, bytes, suf);
			svg_text(Y, c->start_समय, comm);

			c->Y = Y;
			Y++;
			c = c->next;
		पूर्ण
		p = p->next;
	पूर्ण
पूर्ण

अटल व्योम draw_process_bars(काष्ठा समयअक्षरt *tअक्षरt)
अणु
	काष्ठा per_pid *p;
	काष्ठा per_pidcomm *c;
	काष्ठा cpu_sample *sample;
	पूर्णांक Y = 0;

	Y = 2 * tअक्षरt->numcpus + 2;

	p = tअक्षरt->all_data;
	जबतक (p) अणु
		c = p->all;
		जबतक (c) अणु
			अगर (!c->display) अणु
				c->Y = 0;
				c = c->next;
				जारी;
			पूर्ण

			svg_box(Y, c->start_समय, c->end_समय, "process");
			sample = c->samples;
			जबतक (sample) अणु
				अगर (sample->type == TYPE_RUNNING)
					svg_running(Y, sample->cpu,
						    sample->start_समय,
						    sample->end_समय,
						    sample->backtrace);
				अगर (sample->type == TYPE_BLOCKED)
					svg_blocked(Y, sample->cpu,
						    sample->start_समय,
						    sample->end_समय,
						    sample->backtrace);
				अगर (sample->type == TYPE_WAITING)
					svg_रुकोing(Y, sample->cpu,
						    sample->start_समय,
						    sample->end_समय,
						    sample->backtrace);
				sample = sample->next;
			पूर्ण

			अगर (c->comm) अणु
				अक्षर comm[256];
				अगर (c->total_समय > 5000000000) /* 5 seconds */
					प्र_लिखो(comm, "%s:%i (%2.2fs)", c->comm, p->pid, c->total_समय / (द्विगुन)NSEC_PER_SEC);
				अन्यथा
					प्र_लिखो(comm, "%s:%i (%3.1fms)", c->comm, p->pid, c->total_समय / (द्विगुन)NSEC_PER_MSEC);

				svg_text(Y, c->start_समय, comm);
			पूर्ण
			c->Y = Y;
			Y++;
			c = c->next;
		पूर्ण
		p = p->next;
	पूर्ण
पूर्ण

अटल व्योम add_process_filter(स्थिर अक्षर *string)
अणु
	पूर्णांक pid = म_से_अदीर्घl(string, शून्य, 10);
	काष्ठा process_filter *filt = दो_स्मृति(माप(*filt));

	अगर (!filt)
		वापस;

	filt->name = strdup(string);
	filt->pid  = pid;
	filt->next = process_filter;

	process_filter = filt;
पूर्ण

अटल पूर्णांक passes_filter(काष्ठा per_pid *p, काष्ठा per_pidcomm *c)
अणु
	काष्ठा process_filter *filt;
	अगर (!process_filter)
		वापस 1;

	filt = process_filter;
	जबतक (filt) अणु
		अगर (filt->pid && p->pid == filt->pid)
			वापस 1;
		अगर (म_भेद(filt->name, c->comm) == 0)
			वापस 1;
		filt = filt->next;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक determine_display_tasks_filtered(काष्ठा समयअक्षरt *tअक्षरt)
अणु
	काष्ठा per_pid *p;
	काष्ठा per_pidcomm *c;
	पूर्णांक count = 0;

	p = tअक्षरt->all_data;
	जबतक (p) अणु
		p->display = 0;
		अगर (p->start_समय == 1)
			p->start_समय = tअक्षरt->first_समय;

		/* no निकास marker, task kept running to the end */
		अगर (p->end_समय == 0)
			p->end_समय = tअक्षरt->last_समय;

		c = p->all;

		जबतक (c) अणु
			c->display = 0;

			अगर (c->start_समय == 1)
				c->start_समय = tअक्षरt->first_समय;

			अगर (passes_filter(p, c)) अणु
				c->display = 1;
				p->display = 1;
				count++;
			पूर्ण

			अगर (c->end_समय == 0)
				c->end_समय = tअक्षरt->last_समय;

			c = c->next;
		पूर्ण
		p = p->next;
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक determine_display_tasks(काष्ठा समयअक्षरt *tअक्षरt, u64 threshold)
अणु
	काष्ठा per_pid *p;
	काष्ठा per_pidcomm *c;
	पूर्णांक count = 0;

	p = tअक्षरt->all_data;
	जबतक (p) अणु
		p->display = 0;
		अगर (p->start_समय == 1)
			p->start_समय = tअक्षरt->first_समय;

		/* no निकास marker, task kept running to the end */
		अगर (p->end_समय == 0)
			p->end_समय = tअक्षरt->last_समय;
		अगर (p->total_समय >= threshold)
			p->display = 1;

		c = p->all;

		जबतक (c) अणु
			c->display = 0;

			अगर (c->start_समय == 1)
				c->start_समय = tअक्षरt->first_समय;

			अगर (c->total_समय >= threshold) अणु
				c->display = 1;
				count++;
			पूर्ण

			अगर (c->end_समय == 0)
				c->end_समय = tअक्षरt->last_समय;

			c = c->next;
		पूर्ण
		p = p->next;
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक determine_display_io_tasks(काष्ठा समयअक्षरt *समयअक्षरt, u64 threshold)
अणु
	काष्ठा per_pid *p;
	काष्ठा per_pidcomm *c;
	पूर्णांक count = 0;

	p = समयअक्षरt->all_data;
	जबतक (p) अणु
		/* no निकास marker, task kept running to the end */
		अगर (p->end_समय == 0)
			p->end_समय = समयअक्षरt->last_समय;

		c = p->all;

		जबतक (c) अणु
			c->display = 0;

			अगर (c->total_bytes >= threshold) अणु
				c->display = 1;
				count++;
			पूर्ण

			अगर (c->end_समय == 0)
				c->end_समय = समयअक्षरt->last_समय;

			c = c->next;
		पूर्ण
		p = p->next;
	पूर्ण
	वापस count;
पूर्ण

#घोषणा BYTES_THRESH (1 * 1024 * 1024)
#घोषणा TIME_THRESH 10000000

अटल व्योम ग_लिखो_svg_file(काष्ठा समयअक्षरt *tअक्षरt, स्थिर अक्षर *filename)
अणु
	u64 i;
	पूर्णांक count;
	पूर्णांक thresh = tअक्षरt->io_events ? BYTES_THRESH : TIME_THRESH;

	अगर (tअक्षरt->घातer_only)
		tअक्षरt->proc_num = 0;

	/* We'd like to show at least proc_num tasks;
	 * be less picky अगर we have fewer */
	करो अणु
		अगर (process_filter)
			count = determine_display_tasks_filtered(tअक्षरt);
		अन्यथा अगर (tअक्षरt->io_events)
			count = determine_display_io_tasks(tअक्षरt, thresh);
		अन्यथा
			count = determine_display_tasks(tअक्षरt, thresh);
		thresh /= 10;
	पूर्ण जबतक (!process_filter && thresh && count < tअक्षरt->proc_num);

	अगर (!tअक्षरt->proc_num)
		count = 0;

	अगर (tअक्षरt->io_events) अणु
		खोलो_svg(filename, 0, count, tअक्षरt->first_समय, tअक्षरt->last_समय);

		svg_समय_grid(0.5);
		svg_io_legenda();

		draw_io_bars(tअक्षरt);
	पूर्ण अन्यथा अणु
		खोलो_svg(filename, tअक्षरt->numcpus, count, tअक्षरt->first_समय, tअक्षरt->last_समय);

		svg_समय_grid(0);

		svg_legenda();

		क्रम (i = 0; i < tअक्षरt->numcpus; i++)
			svg_cpu_box(i, tअक्षरt->max_freq, tअक्षरt->turbo_frequency);

		draw_cpu_usage(tअक्षरt);
		अगर (tअक्षरt->proc_num)
			draw_process_bars(tअक्षरt);
		अगर (!tअक्षरt->tasks_only)
			draw_c_p_states(tअक्षरt);
		अगर (tअक्षरt->proc_num)
			draw_wakeups(tअक्षरt);
	पूर्ण

	svg_बंद();
पूर्ण

अटल पूर्णांक process_header(काष्ठा perf_file_section *section __maybe_unused,
			  काष्ठा perf_header *ph,
			  पूर्णांक feat,
			  पूर्णांक fd __maybe_unused,
			  व्योम *data)
अणु
	काष्ठा समयअक्षरt *tअक्षरt = data;

	चयन (feat) अणु
	हाल HEADER_NRCPUS:
		tअक्षरt->numcpus = ph->env.nr_cpus_avail;
		अवरोध;

	हाल HEADER_CPU_TOPOLOGY:
		अगर (!tअक्षरt->topology)
			अवरोध;

		अगर (svg_build_topology_map(&ph->env))
			ख_लिखो(मानक_त्रुटि, "problem building topology\n");
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __cmd_समयअक्षरt(काष्ठा समयअक्षरt *tअक्षरt, स्थिर अक्षर *output_name)
अणु
	स्थिर काष्ठा evsel_str_handler घातer_tracepoपूर्णांकs[] = अणु
		अणु "power:cpu_idle",		process_sample_cpu_idle पूर्ण,
		अणु "power:cpu_frequency",	process_sample_cpu_frequency पूर्ण,
		अणु "sched:sched_wakeup",		process_sample_sched_wakeup पूर्ण,
		अणु "sched:sched_switch",		process_sample_sched_चयन पूर्ण,
#अगर_घोषित SUPPORT_OLD_POWER_EVENTS
		अणु "power:power_start",		process_sample_घातer_start पूर्ण,
		अणु "power:power_end",		process_sample_घातer_end पूर्ण,
		अणु "power:power_frequency",	process_sample_घातer_frequency पूर्ण,
#पूर्ण_अगर

		अणु "syscalls:sys_enter_read",		process_enter_पढ़ो पूर्ण,
		अणु "syscalls:sys_enter_pread64",		process_enter_पढ़ो पूर्ण,
		अणु "syscalls:sys_enter_readv",		process_enter_पढ़ो पूर्ण,
		अणु "syscalls:sys_enter_preadv",		process_enter_पढ़ो पूर्ण,
		अणु "syscalls:sys_enter_write",		process_enter_ग_लिखो पूर्ण,
		अणु "syscalls:sys_enter_pwrite64",	process_enter_ग_लिखो पूर्ण,
		अणु "syscalls:sys_enter_writev",		process_enter_ग_लिखो पूर्ण,
		अणु "syscalls:sys_enter_pwritev",		process_enter_ग_लिखो पूर्ण,
		अणु "syscalls:sys_enter_sync",		process_enter_sync पूर्ण,
		अणु "syscalls:sys_enter_sync_file_range",	process_enter_sync पूर्ण,
		अणु "syscalls:sys_enter_fsync",		process_enter_sync पूर्ण,
		अणु "syscalls:sys_enter_msync",		process_enter_sync पूर्ण,
		अणु "syscalls:sys_enter_recvfrom",	process_enter_rx पूर्ण,
		अणु "syscalls:sys_enter_recvmmsg",	process_enter_rx पूर्ण,
		अणु "syscalls:sys_enter_recvmsg",		process_enter_rx पूर्ण,
		अणु "syscalls:sys_enter_sendto",		process_enter_tx पूर्ण,
		अणु "syscalls:sys_enter_sendmsg",		process_enter_tx पूर्ण,
		अणु "syscalls:sys_enter_sendmmsg",	process_enter_tx पूर्ण,
		अणु "syscalls:sys_enter_epoll_pwait",	process_enter_poll पूर्ण,
		अणु "syscalls:sys_enter_epoll_wait",	process_enter_poll पूर्ण,
		अणु "syscalls:sys_enter_poll",		process_enter_poll पूर्ण,
		अणु "syscalls:sys_enter_ppoll",		process_enter_poll पूर्ण,
		अणु "syscalls:sys_enter_pselect6",	process_enter_poll पूर्ण,
		अणु "syscalls:sys_enter_select",		process_enter_poll पूर्ण,

		अणु "syscalls:sys_exit_read",		process_निकास_पढ़ो पूर्ण,
		अणु "syscalls:sys_exit_pread64",		process_निकास_पढ़ो पूर्ण,
		अणु "syscalls:sys_exit_readv",		process_निकास_पढ़ो पूर्ण,
		अणु "syscalls:sys_exit_preadv",		process_निकास_पढ़ो पूर्ण,
		अणु "syscalls:sys_exit_write",		process_निकास_ग_लिखो पूर्ण,
		अणु "syscalls:sys_exit_pwrite64",		process_निकास_ग_लिखो पूर्ण,
		अणु "syscalls:sys_exit_writev",		process_निकास_ग_लिखो पूर्ण,
		अणु "syscalls:sys_exit_pwritev",		process_निकास_ग_लिखो पूर्ण,
		अणु "syscalls:sys_exit_sync",		process_निकास_sync पूर्ण,
		अणु "syscalls:sys_exit_sync_file_range",	process_निकास_sync पूर्ण,
		अणु "syscalls:sys_exit_fsync",		process_निकास_sync पूर्ण,
		अणु "syscalls:sys_exit_msync",		process_निकास_sync पूर्ण,
		अणु "syscalls:sys_exit_recvfrom",		process_निकास_rx पूर्ण,
		अणु "syscalls:sys_exit_recvmmsg",		process_निकास_rx पूर्ण,
		अणु "syscalls:sys_exit_recvmsg",		process_निकास_rx पूर्ण,
		अणु "syscalls:sys_exit_sendto",		process_निकास_tx पूर्ण,
		अणु "syscalls:sys_exit_sendmsg",		process_निकास_tx पूर्ण,
		अणु "syscalls:sys_exit_sendmmsg",		process_निकास_tx पूर्ण,
		अणु "syscalls:sys_exit_epoll_pwait",	process_निकास_poll पूर्ण,
		अणु "syscalls:sys_exit_epoll_wait",	process_निकास_poll पूर्ण,
		अणु "syscalls:sys_exit_poll",		process_निकास_poll पूर्ण,
		अणु "syscalls:sys_exit_ppoll",		process_निकास_poll पूर्ण,
		अणु "syscalls:sys_exit_pselect6",		process_निकास_poll पूर्ण,
		अणु "syscalls:sys_exit_select",		process_निकास_poll पूर्ण,
	पूर्ण;
	काष्ठा perf_data data = अणु
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.क्रमce = tअक्षरt->क्रमce,
	पूर्ण;

	काष्ठा perf_session *session = perf_session__new(&data, false,
							 &tअक्षरt->tool);
	पूर्णांक ret = -EINVAL;

	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	symbol__init(&session->header.env);

	(व्योम)perf_header__process_sections(&session->header,
					    perf_data__fd(session->data),
					    tअक्षरt,
					    process_header);

	अगर (!perf_session__has_traces(session, "timechart record"))
		जाओ out_delete;

	अगर (perf_session__set_tracepoपूर्णांकs_handlers(session,
						   घातer_tracepoपूर्णांकs)) अणु
		pr_err("Initializing session tracepoint handlers failed\n");
		जाओ out_delete;
	पूर्ण

	ret = perf_session__process_events(session);
	अगर (ret)
		जाओ out_delete;

	end_sample_processing(tअक्षरt);

	sort_pids(tअक्षरt);

	ग_लिखो_svg_file(tअक्षरt, output_name);

	pr_info("Written %2.1f seconds of trace to %s.\n",
		(tअक्षरt->last_समय - tअक्षरt->first_समय) / (द्विगुन)NSEC_PER_SEC, output_name);
out_delete:
	perf_session__delete(session);
	वापस ret;
पूर्ण

अटल पूर्णांक समयअक्षरt__io_record(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अचिन्हित पूर्णांक rec_argc, i;
	स्थिर अक्षर **rec_argv;
	स्थिर अक्षर **p;
	अक्षर *filter = शून्य;

	स्थिर अक्षर * स्थिर common_args[] = अणु
		"record", "-a", "-R", "-c", "1",
	पूर्ण;
	अचिन्हित पूर्णांक common_args_nr = ARRAY_SIZE(common_args);

	स्थिर अक्षर * स्थिर disk_events[] = अणु
		"syscalls:sys_enter_read",
		"syscalls:sys_enter_pread64",
		"syscalls:sys_enter_readv",
		"syscalls:sys_enter_preadv",
		"syscalls:sys_enter_write",
		"syscalls:sys_enter_pwrite64",
		"syscalls:sys_enter_writev",
		"syscalls:sys_enter_pwritev",
		"syscalls:sys_enter_sync",
		"syscalls:sys_enter_sync_file_range",
		"syscalls:sys_enter_fsync",
		"syscalls:sys_enter_msync",

		"syscalls:sys_exit_read",
		"syscalls:sys_exit_pread64",
		"syscalls:sys_exit_readv",
		"syscalls:sys_exit_preadv",
		"syscalls:sys_exit_write",
		"syscalls:sys_exit_pwrite64",
		"syscalls:sys_exit_writev",
		"syscalls:sys_exit_pwritev",
		"syscalls:sys_exit_sync",
		"syscalls:sys_exit_sync_file_range",
		"syscalls:sys_exit_fsync",
		"syscalls:sys_exit_msync",
	पूर्ण;
	अचिन्हित पूर्णांक disk_events_nr = ARRAY_SIZE(disk_events);

	स्थिर अक्षर * स्थिर net_events[] = अणु
		"syscalls:sys_enter_recvfrom",
		"syscalls:sys_enter_recvmmsg",
		"syscalls:sys_enter_recvmsg",
		"syscalls:sys_enter_sendto",
		"syscalls:sys_enter_sendmsg",
		"syscalls:sys_enter_sendmmsg",

		"syscalls:sys_exit_recvfrom",
		"syscalls:sys_exit_recvmmsg",
		"syscalls:sys_exit_recvmsg",
		"syscalls:sys_exit_sendto",
		"syscalls:sys_exit_sendmsg",
		"syscalls:sys_exit_sendmmsg",
	पूर्ण;
	अचिन्हित पूर्णांक net_events_nr = ARRAY_SIZE(net_events);

	स्थिर अक्षर * स्थिर poll_events[] = अणु
		"syscalls:sys_enter_epoll_pwait",
		"syscalls:sys_enter_epoll_wait",
		"syscalls:sys_enter_poll",
		"syscalls:sys_enter_ppoll",
		"syscalls:sys_enter_pselect6",
		"syscalls:sys_enter_select",

		"syscalls:sys_exit_epoll_pwait",
		"syscalls:sys_exit_epoll_wait",
		"syscalls:sys_exit_poll",
		"syscalls:sys_exit_ppoll",
		"syscalls:sys_exit_pselect6",
		"syscalls:sys_exit_select",
	पूर्ण;
	अचिन्हित पूर्णांक poll_events_nr = ARRAY_SIZE(poll_events);

	rec_argc = common_args_nr +
		disk_events_nr * 4 +
		net_events_nr * 4 +
		poll_events_nr * 4 +
		argc;
	rec_argv = सुस्मृति(rec_argc + 1, माप(अक्षर *));

	अगर (rec_argv == शून्य)
		वापस -ENOMEM;

	अगर (aप्र_लिखो(&filter, "common_pid != %d", getpid()) < 0) अणु
		मुक्त(rec_argv);
		वापस -ENOMEM;
	पूर्ण

	p = rec_argv;
	क्रम (i = 0; i < common_args_nr; i++)
		*p++ = strdup(common_args[i]);

	क्रम (i = 0; i < disk_events_nr; i++) अणु
		अगर (!is_valid_tracepoपूर्णांक(disk_events[i])) अणु
			rec_argc -= 4;
			जारी;
		पूर्ण

		*p++ = "-e";
		*p++ = strdup(disk_events[i]);
		*p++ = "--filter";
		*p++ = filter;
	पूर्ण
	क्रम (i = 0; i < net_events_nr; i++) अणु
		अगर (!is_valid_tracepoपूर्णांक(net_events[i])) अणु
			rec_argc -= 4;
			जारी;
		पूर्ण

		*p++ = "-e";
		*p++ = strdup(net_events[i]);
		*p++ = "--filter";
		*p++ = filter;
	पूर्ण
	क्रम (i = 0; i < poll_events_nr; i++) अणु
		अगर (!is_valid_tracepoपूर्णांक(poll_events[i])) अणु
			rec_argc -= 4;
			जारी;
		पूर्ण

		*p++ = "-e";
		*p++ = strdup(poll_events[i]);
		*p++ = "--filter";
		*p++ = filter;
	पूर्ण

	क्रम (i = 0; i < (अचिन्हित पूर्णांक)argc; i++)
		*p++ = argv[i];

	वापस cmd_record(rec_argc, rec_argv);
पूर्ण


अटल पूर्णांक समयअक्षरt__record(काष्ठा समयअक्षरt *tअक्षरt, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अचिन्हित पूर्णांक rec_argc, i, j;
	स्थिर अक्षर **rec_argv;
	स्थिर अक्षर **p;
	अचिन्हित पूर्णांक record_elems;

	स्थिर अक्षर * स्थिर common_args[] = अणु
		"record", "-a", "-R", "-c", "1",
	पूर्ण;
	अचिन्हित पूर्णांक common_args_nr = ARRAY_SIZE(common_args);

	स्थिर अक्षर * स्थिर backtrace_args[] = अणु
		"-g",
	पूर्ण;
	अचिन्हित पूर्णांक backtrace_args_no = ARRAY_SIZE(backtrace_args);

	स्थिर अक्षर * स्थिर घातer_args[] = अणु
		"-e", "power:cpu_frequency",
		"-e", "power:cpu_idle",
	पूर्ण;
	अचिन्हित पूर्णांक घातer_args_nr = ARRAY_SIZE(घातer_args);

	स्थिर अक्षर * स्थिर old_घातer_args[] = अणु
#अगर_घोषित SUPPORT_OLD_POWER_EVENTS
		"-e", "power:power_start",
		"-e", "power:power_end",
		"-e", "power:power_frequency",
#पूर्ण_अगर
	पूर्ण;
	अचिन्हित पूर्णांक old_घातer_args_nr = ARRAY_SIZE(old_घातer_args);

	स्थिर अक्षर * स्थिर tasks_args[] = अणु
		"-e", "sched:sched_wakeup",
		"-e", "sched:sched_switch",
	पूर्ण;
	अचिन्हित पूर्णांक tasks_args_nr = ARRAY_SIZE(tasks_args);

#अगर_घोषित SUPPORT_OLD_POWER_EVENTS
	अगर (!is_valid_tracepoपूर्णांक("power:cpu_idle") &&
	    is_valid_tracepoपूर्णांक("power:power_start")) अणु
		use_old_घातer_events = 1;
		घातer_args_nr = 0;
	पूर्ण अन्यथा अणु
		old_घातer_args_nr = 0;
	पूर्ण
#पूर्ण_अगर

	अगर (tअक्षरt->घातer_only)
		tasks_args_nr = 0;

	अगर (tअक्षरt->tasks_only) अणु
		घातer_args_nr = 0;
		old_घातer_args_nr = 0;
	पूर्ण

	अगर (!tअक्षरt->with_backtrace)
		backtrace_args_no = 0;

	record_elems = common_args_nr + tasks_args_nr +
		घातer_args_nr + old_घातer_args_nr + backtrace_args_no;

	rec_argc = record_elems + argc;
	rec_argv = सुस्मृति(rec_argc + 1, माप(अक्षर *));

	अगर (rec_argv == शून्य)
		वापस -ENOMEM;

	p = rec_argv;
	क्रम (i = 0; i < common_args_nr; i++)
		*p++ = strdup(common_args[i]);

	क्रम (i = 0; i < backtrace_args_no; i++)
		*p++ = strdup(backtrace_args[i]);

	क्रम (i = 0; i < tasks_args_nr; i++)
		*p++ = strdup(tasks_args[i]);

	क्रम (i = 0; i < घातer_args_nr; i++)
		*p++ = strdup(घातer_args[i]);

	क्रम (i = 0; i < old_घातer_args_nr; i++)
		*p++ = strdup(old_घातer_args[i]);

	क्रम (j = 0; j < (अचिन्हित पूर्णांक)argc; j++)
		*p++ = argv[j];

	वापस cmd_record(rec_argc, rec_argv);
पूर्ण

अटल पूर्णांक
parse_process(स्थिर काष्ठा option *opt __maybe_unused, स्थिर अक्षर *arg,
	      पूर्णांक __maybe_unused unset)
अणु
	अगर (arg)
		add_process_filter(arg);
	वापस 0;
पूर्ण

अटल पूर्णांक
parse_highlight(स्थिर काष्ठा option *opt __maybe_unused, स्थिर अक्षर *arg,
		पूर्णांक __maybe_unused unset)
अणु
	अचिन्हित दीर्घ duration = म_से_अदीर्घ(arg, शून्य, 0);

	अगर (svg_highlight || svg_highlight_name)
		वापस -1;

	अगर (duration)
		svg_highlight = duration;
	अन्यथा
		svg_highlight_name = strdup(arg);

	वापस 0;
पूर्ण

अटल पूर्णांक
parse_समय(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg, पूर्णांक __maybe_unused unset)
अणु
	अक्षर unit = 'n';
	u64 *value = opt->value;

	अगर (माला_पूछो(arg, "%" PRIu64 "%cs", value, &unit) > 0) अणु
		चयन (unit) अणु
		हाल 'm':
			*value *= NSEC_PER_MSEC;
			अवरोध;
		हाल 'u':
			*value *= NSEC_PER_USEC;
			अवरोध;
		हाल 'n':
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cmd_समयअक्षरt(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा समयअक्षरt tअक्षरt = अणु
		.tool = अणु
			.comm		 = process_comm_event,
			.विभाजन		 = process_विभाजन_event,
			.निकास		 = process_निकास_event,
			.sample		 = process_sample_event,
			.ordered_events	 = true,
		पूर्ण,
		.proc_num = 15,
		.min_समय = NSEC_PER_MSEC,
		.merge_dist = 1000,
	पूर्ण;
	स्थिर अक्षर *output_name = "output.svg";
	स्थिर काष्ठा option समयअक्षरt_common_options[] = अणु
	OPT_BOOLEAN('P', "power-only", &tअक्षरt.घातer_only, "output power data only"),
	OPT_BOOLEAN('T', "tasks-only", &tअक्षरt.tasks_only, "output processes data only"),
	OPT_END()
	पूर्ण;
	स्थिर काष्ठा option समयअक्षरt_options[] = अणु
	OPT_STRING('i', "input", &input_name, "file", "input file name"),
	OPT_STRING('o', "output", &output_name, "file", "output file name"),
	OPT_INTEGER('w', "width", &svg_page_width, "page width"),
	OPT_CALLBACK(0, "highlight", शून्य, "duration or task name",
		      "highlight tasks. Pass duration in ns or process name.",
		       parse_highlight),
	OPT_CALLBACK('p', "process", शून्य, "process",
		      "process selector. Pass a pid or process name.",
		       parse_process),
	OPT_CALLBACK(0, "symfs", शून्य, "directory",
		     "Look for files with symbols relative to this directory",
		     symbol__config_symfs),
	OPT_INTEGER('n', "proc-num", &tअक्षरt.proc_num,
		    "min. number of tasks to print"),
	OPT_BOOLEAN('t', "topology", &tअक्षरt.topology,
		    "sort CPUs according to topology"),
	OPT_BOOLEAN(0, "io-skip-eagain", &tअक्षरt.skip_eagain,
		    "skip EAGAIN errors"),
	OPT_CALLBACK(0, "io-min-time", &tअक्षरt.min_समय, "time",
		     "all IO faster than min-time will visually appear longer",
		     parse_समय),
	OPT_CALLBACK(0, "io-merge-dist", &tअक्षरt.merge_dist, "time",
		     "merge events that are merge-dist us apart",
		     parse_समय),
	OPT_BOOLEAN('f', "force", &tchart.force, "don't complain, करो it"),
	OPT_PARENT(समयअक्षरt_common_options),
	पूर्ण;
	स्थिर अक्षर * स्थिर समयअक्षरt_subcommands[] = अणु "record", शून्य पूर्ण;
	स्थिर अक्षर *समयअक्षरt_usage[] = अणु
		"perf timechart [<options>] {record}",
		शून्य
	पूर्ण;
	स्थिर काष्ठा option समयअक्षरt_record_options[] = अणु
	OPT_BOOLEAN('I', "io-only", &tअक्षरt.io_only,
		    "record only IO data"),
	OPT_BOOLEAN('g', "callchain", &tअक्षरt.with_backtrace, "record callchain"),
	OPT_PARENT(समयअक्षरt_common_options),
	पूर्ण;
	स्थिर अक्षर * स्थिर समयअक्षरt_record_usage[] = अणु
		"perf timechart record [<options>]",
		शून्य
	पूर्ण;
	argc = parse_options_subcommand(argc, argv, समयअक्षरt_options, समयअक्षरt_subcommands,
			समयअक्षरt_usage, PARSE_OPT_STOP_AT_NON_OPTION);

	अगर (tअक्षरt.घातer_only && tअक्षरt.tasks_only) अणु
		pr_err("-P and -T options cannot be used at the same time.\n");
		वापस -1;
	पूर्ण

	अगर (argc && !म_भेदन(argv[0], "rec", 3)) अणु
		argc = parse_options(argc, argv, समयअक्षरt_record_options,
				     समयअक्षरt_record_usage,
				     PARSE_OPT_STOP_AT_NON_OPTION);

		अगर (tअक्षरt.घातer_only && tअक्षरt.tasks_only) अणु
			pr_err("-P and -T options cannot be used at the same time.\n");
			वापस -1;
		पूर्ण

		अगर (tअक्षरt.io_only)
			वापस समयअक्षरt__io_record(argc, argv);
		अन्यथा
			वापस समयअक्षरt__record(&tअक्षरt, argc, argv);
	पूर्ण अन्यथा अगर (argc)
		usage_with_options(समयअक्षरt_usage, समयअक्षरt_options);

	setup_pager();

	वापस __cmd_समयअक्षरt(&tअक्षरt, output_name);
पूर्ण
