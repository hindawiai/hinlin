<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 *
 * Refactored from builtin-top.c, see that files क्रम further copyright notes.
 */

#समावेश "event.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "parse-events.h"
#समावेश "symbol.h"
#समावेश "top.h"
#समावेश "../perf.h"
#समावेश <पूर्णांकtypes.h>

#घोषणा SNPRINTF(buf, size, fmt, args...) \
(अणु \
	माप_प्रकार r = snम_लिखो(buf, size, fmt, ## args); \
	r > size ?  size : r; \
पूर्ण)

माप_प्रकार perf_top__header_snम_लिखो(काष्ठा perf_top *top, अक्षर *bf, माप_प्रकार size)
अणु
	भग्न samples_per_sec;
	भग्न ksamples_per_sec;
	भग्न esamples_percent;
	काष्ठा record_opts *opts = &top->record_opts;
	काष्ठा target *target = &opts->target;
	माप_प्रकार ret = 0;

	अगर (top->samples) अणु
		samples_per_sec = top->samples / top->delay_secs;
		ksamples_per_sec = top->kernel_samples / top->delay_secs;
		esamples_percent = (100.0 * top->exact_samples) / top->samples;
	पूर्ण अन्यथा अणु
		samples_per_sec = ksamples_per_sec = esamples_percent = 0.0;
	पूर्ण

	अगर (!perf_guest) अणु
		भग्न ksamples_percent = 0.0;

		अगर (samples_per_sec)
			ksamples_percent = (100.0 * ksamples_per_sec) /
							samples_per_sec;
		ret = SNPRINTF(bf, size,
			       "   PerfTop:%8.0f irqs/sec  kernel:%4.1f%%"
			       "  exact: %4.1f%% lost: %" PRIu64 "/%" PRIu64 " drop: %" PRIu64 "/%" PRIu64 " [",
			       samples_per_sec, ksamples_percent, esamples_percent,
			       top->lost, top->lost_total, top->drop, top->drop_total);
	पूर्ण अन्यथा अणु
		भग्न us_samples_per_sec = top->us_samples / top->delay_secs;
		भग्न guest_kernel_samples_per_sec = top->guest_kernel_samples / top->delay_secs;
		भग्न guest_us_samples_per_sec = top->guest_us_samples / top->delay_secs;

		ret = SNPRINTF(bf, size,
			       "   PerfTop:%8.0f irqs/sec  kernel:%4.1f%% us:%4.1f%%"
			       " guest kernel:%4.1f%% guest us:%4.1f%%"
			       " exact: %4.1f%% [", samples_per_sec,
			       100.0 - (100.0 * ((samples_per_sec - ksamples_per_sec) /
						 samples_per_sec)),
			       100.0 - (100.0 * ((samples_per_sec - us_samples_per_sec) /
						 samples_per_sec)),
			       100.0 - (100.0 * ((samples_per_sec -
						  guest_kernel_samples_per_sec) /
						 samples_per_sec)),
			       100.0 - (100.0 * ((samples_per_sec -
						  guest_us_samples_per_sec) /
						 samples_per_sec)),
			       esamples_percent);
	पूर्ण

	अगर (top->evlist->core.nr_entries == 1) अणु
		काष्ठा evsel *first = evlist__first(top->evlist);
		ret += SNPRINTF(bf + ret, size - ret, "%" PRIu64 "%s ",
				(uपूर्णांक64_t)first->core.attr.sample_period,
				opts->freq ? "Hz" : "");
	पूर्ण

	ret += SNPRINTF(bf + ret, size - ret, "%s", evsel__name(top->sym_evsel));

	ret += SNPRINTF(bf + ret, size - ret, "], ");

	अगर (target->pid)
		ret += SNPRINTF(bf + ret, size - ret, " (target_pid: %s",
				target->pid);
	अन्यथा अगर (target->tid)
		ret += SNPRINTF(bf + ret, size - ret, " (target_tid: %s",
				target->tid);
	अन्यथा अगर (target->uid_str != शून्य)
		ret += SNPRINTF(bf + ret, size - ret, " (uid: %s",
				target->uid_str);
	अन्यथा
		ret += SNPRINTF(bf + ret, size - ret, " (all");

	अगर (target->cpu_list)
		ret += SNPRINTF(bf + ret, size - ret, ", CPU%s: %s)",
				top->evlist->core.cpus->nr > 1 ? "s" : "",
				target->cpu_list);
	अन्यथा अणु
		अगर (target->tid)
			ret += SNPRINTF(bf + ret, size - ret, ")");
		अन्यथा
			ret += SNPRINTF(bf + ret, size - ret, ", %d CPU%s)",
					top->evlist->core.cpus->nr,
					top->evlist->core.cpus->nr > 1 ? "s" : "");
	पूर्ण

	perf_top__reset_sample_counters(top);
	वापस ret;
पूर्ण

व्योम perf_top__reset_sample_counters(काष्ठा perf_top *top)
अणु
	top->samples = top->us_samples = top->kernel_samples =
	top->exact_samples = top->guest_kernel_samples =
	top->guest_us_samples = top->lost = top->drop = 0;
पूर्ण
