<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * builtin-inject.c
 *
 * Builtin inject command: Examine the live mode (मानक_निवेश) event stream
 * and repipe it to मानक_निकास जबतक optionally injecting additional
 * events पूर्णांकo it.
 */
#समावेश "builtin.h"

#समावेश "util/color.h"
#समावेश "util/dso.h"
#समावेश "util/vdso.h"
#समावेश "util/evlist.h"
#समावेश "util/evsel.h"
#समावेश "util/map.h"
#समावेश "util/session.h"
#समावेश "util/tool.h"
#समावेश "util/debug.h"
#समावेश "util/build-id.h"
#समावेश "util/data.h"
#समावेश "util/auxtrace.h"
#समावेश "util/jit.h"
#समावेश "util/symbol.h"
#समावेश "util/synthetic-events.h"
#समावेश "util/thread.h"
#समावेश "util/namespaces.h"

#समावेश <linux/err.h>
#समावेश <subcmd/parse-options.h>
#समावेश <uapi/linux/mman.h> /* To get things like MAP_HUGETLB even on older libc headers */

#समावेश <linux/list.h>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>

काष्ठा perf_inject अणु
	काष्ठा perf_tool	tool;
	काष्ठा perf_session	*session;
	bool			build_ids;
	bool			build_id_all;
	bool			sched_stat;
	bool			have_auxtrace;
	bool			strip;
	bool			jit_mode;
	स्थिर अक्षर		*input_name;
	काष्ठा perf_data	output;
	u64			bytes_written;
	u64			aux_id;
	काष्ठा list_head	samples;
	काष्ठा itrace_synth_opts itrace_synth_opts;
	अक्षर			event_copy[PERF_SAMPLE_MAX_SIZE];
पूर्ण;

काष्ठा event_entry अणु
	काष्ठा list_head node;
	u32		 tid;
	जोड़ perf_event event[];
पूर्ण;

अटल पूर्णांक dso__inject_build_id(काष्ठा dso *dso, काष्ठा perf_tool *tool,
				काष्ठा machine *machine, u8 cpumode, u32 flags);

अटल पूर्णांक output_bytes(काष्ठा perf_inject *inject, व्योम *buf, माप_प्रकार sz)
अणु
	sमाप_प्रकार size;

	size = perf_data__ग_लिखो(&inject->output, buf, sz);
	अगर (size < 0)
		वापस -त्रुटि_सं;

	inject->bytes_written += size;
	वापस 0;
पूर्ण

अटल पूर्णांक perf_event__repipe_synth(काष्ठा perf_tool *tool,
				    जोड़ perf_event *event)
अणु
	काष्ठा perf_inject *inject = container_of(tool, काष्ठा perf_inject,
						  tool);

	वापस output_bytes(inject, event, event->header.size);
पूर्ण

अटल पूर्णांक perf_event__repipe_oe_synth(काष्ठा perf_tool *tool,
				       जोड़ perf_event *event,
				       काष्ठा ordered_events *oe __maybe_unused)
अणु
	वापस perf_event__repipe_synth(tool, event);
पूर्ण

#अगर_घोषित HAVE_JITDUMP
अटल पूर्णांक perf_event__drop_oe(काष्ठा perf_tool *tool __maybe_unused,
			       जोड़ perf_event *event __maybe_unused,
			       काष्ठा ordered_events *oe __maybe_unused)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक perf_event__repipe_op2_synth(काष्ठा perf_session *session,
					जोड़ perf_event *event)
अणु
	वापस perf_event__repipe_synth(session->tool, event);
पूर्ण

अटल पूर्णांक perf_event__repipe_op4_synth(काष्ठा perf_session *session,
					जोड़ perf_event *event,
					u64 data __maybe_unused)
अणु
	वापस perf_event__repipe_synth(session->tool, event);
पूर्ण

अटल पूर्णांक perf_event__repipe_attr(काष्ठा perf_tool *tool,
				   जोड़ perf_event *event,
				   काष्ठा evlist **pevlist)
अणु
	काष्ठा perf_inject *inject = container_of(tool, काष्ठा perf_inject,
						  tool);
	पूर्णांक ret;

	ret = perf_event__process_attr(tool, event, pevlist);
	अगर (ret)
		वापस ret;

	अगर (!inject->output.is_pipe)
		वापस 0;

	वापस perf_event__repipe_synth(tool, event);
पूर्ण

अटल पूर्णांक perf_event__repipe_event_update(काष्ठा perf_tool *tool,
					   जोड़ perf_event *event,
					   काष्ठा evlist **pevlist __maybe_unused)
अणु
	वापस perf_event__repipe_synth(tool, event);
पूर्ण

#अगर_घोषित HAVE_AUXTRACE_SUPPORT

अटल पूर्णांक copy_bytes(काष्ठा perf_inject *inject, पूर्णांक fd, off_t size)
अणु
	अक्षर buf[4096];
	sमाप_प्रकार ssz;
	पूर्णांक ret;

	जबतक (size > 0) अणु
		ssz = पढ़ो(fd, buf, min(size, (off_t)माप(buf)));
		अगर (ssz < 0)
			वापस -त्रुटि_सं;
		ret = output_bytes(inject, buf, ssz);
		अगर (ret)
			वापस ret;
		size -= ssz;
	पूर्ण

	वापस 0;
पूर्ण

अटल s64 perf_event__repipe_auxtrace(काष्ठा perf_session *session,
				       जोड़ perf_event *event)
अणु
	काष्ठा perf_tool *tool = session->tool;
	काष्ठा perf_inject *inject = container_of(tool, काष्ठा perf_inject,
						  tool);
	पूर्णांक ret;

	inject->have_auxtrace = true;

	अगर (!inject->output.is_pipe) अणु
		off_t offset;

		offset = lseek(inject->output.file.fd, 0, प्रस्तुत_से);
		अगर (offset == -1)
			वापस -त्रुटि_सं;
		ret = auxtrace_index__auxtrace_event(&session->auxtrace_index,
						     event, offset);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (perf_data__is_pipe(session->data) || !session->one_mmap) अणु
		ret = output_bytes(inject, event, event->header.size);
		अगर (ret < 0)
			वापस ret;
		ret = copy_bytes(inject, perf_data__fd(session->data),
				 event->auxtrace.size);
	पूर्ण अन्यथा अणु
		ret = output_bytes(inject, event,
				   event->header.size + event->auxtrace.size);
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	वापस event->auxtrace.size;
पूर्ण

#अन्यथा

अटल s64
perf_event__repipe_auxtrace(काष्ठा perf_session *session __maybe_unused,
			    जोड़ perf_event *event __maybe_unused)
अणु
	pr_err("AUX area tracing not supported\n");
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक perf_event__repipe(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample __maybe_unused,
			      काष्ठा machine *machine __maybe_unused)
अणु
	वापस perf_event__repipe_synth(tool, event);
पूर्ण

अटल पूर्णांक perf_event__drop(काष्ठा perf_tool *tool __maybe_unused,
			    जोड़ perf_event *event __maybe_unused,
			    काष्ठा perf_sample *sample __maybe_unused,
			    काष्ठा machine *machine __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक perf_event__drop_aux(काष्ठा perf_tool *tool,
				जोड़ perf_event *event __maybe_unused,
				काष्ठा perf_sample *sample,
				काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा perf_inject *inject = container_of(tool, काष्ठा perf_inject, tool);

	अगर (!inject->aux_id)
		inject->aux_id = sample->id;

	वापस 0;
पूर्ण

अटल जोड़ perf_event *
perf_inject__cut_auxtrace_sample(काष्ठा perf_inject *inject,
				 जोड़ perf_event *event,
				 काष्ठा perf_sample *sample)
अणु
	माप_प्रकार sz1 = sample->aux_sample.data - (व्योम *)event;
	माप_प्रकार sz2 = event->header.size - sample->aux_sample.size - sz1;
	जोड़ perf_event *ev = (जोड़ perf_event *)inject->event_copy;

	अगर (sz1 > event->header.size || sz2 > event->header.size ||
	    sz1 + sz2 > event->header.size ||
	    sz1 < माप(काष्ठा perf_event_header) + माप(u64))
		वापस event;

	स_नकल(ev, event, sz1);
	स_नकल((व्योम *)ev + sz1, (व्योम *)event + event->header.size - sz2, sz2);
	ev->header.size = sz1 + sz2;
	((u64 *)((व्योम *)ev + sz1))[-1] = 0;

	वापस ev;
पूर्ण

प्रकार पूर्णांक (*inject_handler)(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample,
			      काष्ठा evsel *evsel,
			      काष्ठा machine *machine);

अटल पूर्णांक perf_event__repipe_sample(काष्ठा perf_tool *tool,
				     जोड़ perf_event *event,
				     काष्ठा perf_sample *sample,
				     काष्ठा evsel *evsel,
				     काष्ठा machine *machine)
अणु
	काष्ठा perf_inject *inject = container_of(tool, काष्ठा perf_inject,
						  tool);

	अगर (evsel && evsel->handler) अणु
		inject_handler f = evsel->handler;
		वापस f(tool, event, sample, evsel, machine);
	पूर्ण

	build_id__mark_dso_hit(tool, event, sample, evsel, machine);

	अगर (inject->itrace_synth_opts.set && sample->aux_sample.size)
		event = perf_inject__cut_auxtrace_sample(inject, event, sample);

	वापस perf_event__repipe_synth(tool, event);
पूर्ण

अटल पूर्णांक perf_event__repipe_mmap(काष्ठा perf_tool *tool,
				   जोड़ perf_event *event,
				   काष्ठा perf_sample *sample,
				   काष्ठा machine *machine)
अणु
	पूर्णांक err;

	err = perf_event__process_mmap(tool, event, sample, machine);
	perf_event__repipe(tool, event, sample, machine);

	वापस err;
पूर्ण

#अगर_घोषित HAVE_JITDUMP
अटल पूर्णांक perf_event__jit_repipe_mmap(काष्ठा perf_tool *tool,
				       जोड़ perf_event *event,
				       काष्ठा perf_sample *sample,
				       काष्ठा machine *machine)
अणु
	काष्ठा perf_inject *inject = container_of(tool, काष्ठा perf_inject, tool);
	u64 n = 0;
	पूर्णांक ret;

	/*
	 * अगर jit marker, then inject jit mmaps and generate ELF images
	 */
	ret = jit_process(inject->session, &inject->output, machine,
			  event->mmap.filename, event->mmap.pid, event->mmap.tid, &n);
	अगर (ret < 0)
		वापस ret;
	अगर (ret) अणु
		inject->bytes_written += n;
		वापस 0;
	पूर्ण
	वापस perf_event__repipe_mmap(tool, event, sample, machine);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा dso *findnew_dso(पूर्णांक pid, पूर्णांक tid, स्थिर अक्षर *filename,
			       काष्ठा dso_id *id, काष्ठा machine *machine)
अणु
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा nsinfo *nsi = शून्य;
	काष्ठा nsinfo *nnsi;
	काष्ठा dso *dso;
	bool vdso;

	thपढ़ो = machine__findnew_thपढ़ो(machine, pid, tid);
	अगर (thपढ़ो == शून्य) अणु
		pr_err("cannot find or create a task %d/%d.\n", tid, pid);
		वापस शून्य;
	पूर्ण

	vdso = is_vdso_map(filename);
	nsi = nsinfo__get(thपढ़ो->nsinfo);

	अगर (vdso) अणु
		/* The vdso maps are always on the host and not the
		 * container.  Ensure that we करोn't use setns to look
		 * them up.
		 */
		nnsi = nsinfo__copy(nsi);
		अगर (nnsi) अणु
			nsinfo__put(nsi);
			nnsi->need_setns = false;
			nsi = nnsi;
		पूर्ण
		dso = machine__findnew_vdso(machine, thपढ़ो);
	पूर्ण अन्यथा अणु
		dso = machine__findnew_dso_id(machine, filename, id);
	पूर्ण

	अगर (dso)
		dso->nsinfo = nsi;
	अन्यथा
		nsinfo__put(nsi);

	thपढ़ो__put(thपढ़ो);
	वापस dso;
पूर्ण

अटल पूर्णांक perf_event__repipe_buildid_mmap(काष्ठा perf_tool *tool,
					   जोड़ perf_event *event,
					   काष्ठा perf_sample *sample,
					   काष्ठा machine *machine)
अणु
	काष्ठा dso *dso;

	dso = findnew_dso(event->mmap.pid, event->mmap.tid,
			  event->mmap.filename, शून्य, machine);

	अगर (dso && !dso->hit) अणु
		dso->hit = 1;
		dso__inject_build_id(dso, tool, machine, sample->cpumode, 0);
		dso__put(dso);
	पूर्ण

	वापस perf_event__repipe(tool, event, sample, machine);
पूर्ण

अटल पूर्णांक perf_event__repipe_mmap2(काष्ठा perf_tool *tool,
				   जोड़ perf_event *event,
				   काष्ठा perf_sample *sample,
				   काष्ठा machine *machine)
अणु
	पूर्णांक err;

	err = perf_event__process_mmap2(tool, event, sample, machine);
	perf_event__repipe(tool, event, sample, machine);

	वापस err;
पूर्ण

#अगर_घोषित HAVE_JITDUMP
अटल पूर्णांक perf_event__jit_repipe_mmap2(काष्ठा perf_tool *tool,
					जोड़ perf_event *event,
					काष्ठा perf_sample *sample,
					काष्ठा machine *machine)
अणु
	काष्ठा perf_inject *inject = container_of(tool, काष्ठा perf_inject, tool);
	u64 n = 0;
	पूर्णांक ret;

	/*
	 * अगर jit marker, then inject jit mmaps and generate ELF images
	 */
	ret = jit_process(inject->session, &inject->output, machine,
			  event->mmap2.filename, event->mmap2.pid, event->mmap2.tid, &n);
	अगर (ret < 0)
		वापस ret;
	अगर (ret) अणु
		inject->bytes_written += n;
		वापस 0;
	पूर्ण
	वापस perf_event__repipe_mmap2(tool, event, sample, machine);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक perf_event__repipe_buildid_mmap2(काष्ठा perf_tool *tool,
					    जोड़ perf_event *event,
					    काष्ठा perf_sample *sample,
					    काष्ठा machine *machine)
अणु
	काष्ठा dso_id dso_id = अणु
		.maj = event->mmap2.maj,
		.min = event->mmap2.min,
		.ino = event->mmap2.ino,
		.ino_generation = event->mmap2.ino_generation,
	पूर्ण;
	काष्ठा dso *dso;

	dso = findnew_dso(event->mmap2.pid, event->mmap2.tid,
			  event->mmap2.filename, &dso_id, machine);

	अगर (dso && !dso->hit) अणु
		dso->hit = 1;
		dso__inject_build_id(dso, tool, machine, sample->cpumode,
				     event->mmap2.flags);
		dso__put(dso);
	पूर्ण

	perf_event__repipe(tool, event, sample, machine);

	वापस 0;
पूर्ण

अटल पूर्णांक perf_event__repipe_विभाजन(काष्ठा perf_tool *tool,
				   जोड़ perf_event *event,
				   काष्ठा perf_sample *sample,
				   काष्ठा machine *machine)
अणु
	पूर्णांक err;

	err = perf_event__process_विभाजन(tool, event, sample, machine);
	perf_event__repipe(tool, event, sample, machine);

	वापस err;
पूर्ण

अटल पूर्णांक perf_event__repipe_comm(काष्ठा perf_tool *tool,
				   जोड़ perf_event *event,
				   काष्ठा perf_sample *sample,
				   काष्ठा machine *machine)
अणु
	पूर्णांक err;

	err = perf_event__process_comm(tool, event, sample, machine);
	perf_event__repipe(tool, event, sample, machine);

	वापस err;
पूर्ण

अटल पूर्णांक perf_event__repipe_namespaces(काष्ठा perf_tool *tool,
					 जोड़ perf_event *event,
					 काष्ठा perf_sample *sample,
					 काष्ठा machine *machine)
अणु
	पूर्णांक err = perf_event__process_namespaces(tool, event, sample, machine);

	perf_event__repipe(tool, event, sample, machine);

	वापस err;
पूर्ण

अटल पूर्णांक perf_event__repipe_निकास(काष्ठा perf_tool *tool,
				   जोड़ perf_event *event,
				   काष्ठा perf_sample *sample,
				   काष्ठा machine *machine)
अणु
	पूर्णांक err;

	err = perf_event__process_निकास(tool, event, sample, machine);
	perf_event__repipe(tool, event, sample, machine);

	वापस err;
पूर्ण

अटल पूर्णांक perf_event__repipe_tracing_data(काष्ठा perf_session *session,
					   जोड़ perf_event *event)
अणु
	पूर्णांक err;

	perf_event__repipe_synth(session->tool, event);
	err = perf_event__process_tracing_data(session, event);

	वापस err;
पूर्ण

अटल पूर्णांक dso__पढ़ो_build_id(काष्ठा dso *dso)
अणु
	काष्ठा nscookie nsc;

	अगर (dso->has_build_id)
		वापस 0;

	nsinfo__mountns_enter(dso->nsinfo, &nsc);
	अगर (filename__पढ़ो_build_id(dso->दीर्घ_name, &dso->bid) > 0)
		dso->has_build_id = true;
	nsinfo__mountns_निकास(&nsc);

	वापस dso->has_build_id ? 0 : -1;
पूर्ण

अटल पूर्णांक dso__inject_build_id(काष्ठा dso *dso, काष्ठा perf_tool *tool,
				काष्ठा machine *machine, u8 cpumode, u32 flags)
अणु
	पूर्णांक err;

	अगर (is_anon_memory(dso->दीर्घ_name) || flags & MAP_HUGETLB)
		वापस 0;
	अगर (is_no_dso_memory(dso->दीर्घ_name))
		वापस 0;

	अगर (dso__पढ़ो_build_id(dso) < 0) अणु
		pr_debug("no build_id found for %s\n", dso->दीर्घ_name);
		वापस -1;
	पूर्ण

	err = perf_event__synthesize_build_id(tool, dso, cpumode,
					      perf_event__repipe, machine);
	अगर (err) अणु
		pr_err("Can't synthesize build_id event for %s\n", dso->दीर्घ_name);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_event__inject_buildid(काष्ठा perf_tool *tool, जोड़ perf_event *event,
			       काष्ठा perf_sample *sample,
			       काष्ठा evsel *evsel __maybe_unused,
			       काष्ठा machine *machine)
अणु
	काष्ठा addr_location al;
	काष्ठा thपढ़ो *thपढ़ो;

	thपढ़ो = machine__findnew_thपढ़ो(machine, sample->pid, sample->tid);
	अगर (thपढ़ो == शून्य) अणु
		pr_err("problem processing %d event, skipping it.\n",
		       event->header.type);
		जाओ repipe;
	पूर्ण

	अगर (thपढ़ो__find_map(thपढ़ो, sample->cpumode, sample->ip, &al)) अणु
		अगर (!al.map->dso->hit) अणु
			al.map->dso->hit = 1;
			dso__inject_build_id(al.map->dso, tool, machine,
					     sample->cpumode, al.map->flags);
		पूर्ण
	पूर्ण

	thपढ़ो__put(thपढ़ो);
repipe:
	perf_event__repipe(tool, event, sample, machine);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_inject__sched_process_निकास(काष्ठा perf_tool *tool,
					   जोड़ perf_event *event __maybe_unused,
					   काष्ठा perf_sample *sample,
					   काष्ठा evsel *evsel __maybe_unused,
					   काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा perf_inject *inject = container_of(tool, काष्ठा perf_inject, tool);
	काष्ठा event_entry *ent;

	list_क्रम_each_entry(ent, &inject->samples, node) अणु
		अगर (sample->tid == ent->tid) अणु
			list_del_init(&ent->node);
			मुक्त(ent);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक perf_inject__sched_चयन(काष्ठा perf_tool *tool,
				     जोड़ perf_event *event,
				     काष्ठा perf_sample *sample,
				     काष्ठा evsel *evsel,
				     काष्ठा machine *machine)
अणु
	काष्ठा perf_inject *inject = container_of(tool, काष्ठा perf_inject, tool);
	काष्ठा event_entry *ent;

	perf_inject__sched_process_निकास(tool, event, sample, evsel, machine);

	ent = दो_स्मृति(event->header.size + माप(काष्ठा event_entry));
	अगर (ent == शून्य) अणु
		color_ख_लिखो(मानक_त्रुटि, PERF_COLOR_RED,
			     "Not enough memory to process sched switch event!");
		वापस -1;
	पूर्ण

	ent->tid = sample->tid;
	स_नकल(&ent->event, event, event->header.size);
	list_add(&ent->node, &inject->samples);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_inject__sched_stat(काष्ठा perf_tool *tool,
				   जोड़ perf_event *event __maybe_unused,
				   काष्ठा perf_sample *sample,
				   काष्ठा evsel *evsel,
				   काष्ठा machine *machine)
अणु
	काष्ठा event_entry *ent;
	जोड़ perf_event *event_sw;
	काष्ठा perf_sample sample_sw;
	काष्ठा perf_inject *inject = container_of(tool, काष्ठा perf_inject, tool);
	u32 pid = evsel__पूर्णांकval(evsel, sample, "pid");

	list_क्रम_each_entry(ent, &inject->samples, node) अणु
		अगर (pid == ent->tid)
			जाओ found;
	पूर्ण

	वापस 0;
found:
	event_sw = &ent->event[0];
	evsel__parse_sample(evsel, event_sw, &sample_sw);

	sample_sw.period = sample->period;
	sample_sw.समय	 = sample->समय;
	perf_event__synthesize_sample(event_sw, evsel->core.attr.sample_type,
				      evsel->core.attr.पढ़ो_क्रमmat, &sample_sw);
	build_id__mark_dso_hit(tool, event_sw, &sample_sw, evsel, machine);
	वापस perf_event__repipe(tool, event_sw, &sample_sw, machine);
पूर्ण

अटल व्योम sig_handler(पूर्णांक sig __maybe_unused)
अणु
	session_करोne = 1;
पूर्ण

अटल पूर्णांक evsel__check_stype(काष्ठा evsel *evsel, u64 sample_type, स्थिर अक्षर *sample_msg)
अणु
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	स्थिर अक्षर *name = evsel__name(evsel);

	अगर (!(attr->sample_type & sample_type)) अणु
		pr_err("Samples for %s event do not have %s attribute set.",
			name, sample_msg);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक drop_sample(काष्ठा perf_tool *tool __maybe_unused,
		       जोड़ perf_event *event __maybe_unused,
		       काष्ठा perf_sample *sample __maybe_unused,
		       काष्ठा evsel *evsel __maybe_unused,
		       काष्ठा machine *machine __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल व्योम strip_init(काष्ठा perf_inject *inject)
अणु
	काष्ठा evlist *evlist = inject->session->evlist;
	काष्ठा evsel *evsel;

	inject->tool.context_चयन = perf_event__drop;

	evlist__क्रम_each_entry(evlist, evsel)
		evsel->handler = drop_sample;
पूर्ण

अटल पूर्णांक __cmd_inject(काष्ठा perf_inject *inject)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा perf_session *session = inject->session;
	काष्ठा perf_data *data_out = &inject->output;
	पूर्णांक fd = perf_data__fd(data_out);
	u64 output_data_offset;

	संकेत(संक_विघ्न, sig_handler);

	अगर (inject->build_ids || inject->sched_stat ||
	    inject->itrace_synth_opts.set || inject->build_id_all) अणु
		inject->tool.mmap	  = perf_event__repipe_mmap;
		inject->tool.mmap2	  = perf_event__repipe_mmap2;
		inject->tool.विभाजन	  = perf_event__repipe_विभाजन;
		inject->tool.tracing_data = perf_event__repipe_tracing_data;
	पूर्ण

	output_data_offset = session->header.data_offset;

	अगर (inject->build_id_all) अणु
		inject->tool.mmap	  = perf_event__repipe_buildid_mmap;
		inject->tool.mmap2	  = perf_event__repipe_buildid_mmap2;
	पूर्ण अन्यथा अगर (inject->build_ids) अणु
		inject->tool.sample = perf_event__inject_buildid;
	पूर्ण अन्यथा अगर (inject->sched_stat) अणु
		काष्ठा evsel *evsel;

		evlist__क्रम_each_entry(session->evlist, evsel) अणु
			स्थिर अक्षर *name = evsel__name(evsel);

			अगर (!म_भेद(name, "sched:sched_switch")) अणु
				अगर (evsel__check_stype(evsel, PERF_SAMPLE_TID, "TID"))
					वापस -EINVAL;

				evsel->handler = perf_inject__sched_चयन;
			पूर्ण अन्यथा अगर (!म_भेद(name, "sched:sched_process_exit"))
				evsel->handler = perf_inject__sched_process_निकास;
			अन्यथा अगर (!म_भेदन(name, "sched:sched_stat_", 17))
				evsel->handler = perf_inject__sched_stat;
		पूर्ण
	पूर्ण अन्यथा अगर (inject->itrace_synth_opts.set) अणु
		session->itrace_synth_opts = &inject->itrace_synth_opts;
		inject->itrace_synth_opts.inject = true;
		inject->tool.comm	    = perf_event__repipe_comm;
		inject->tool.namespaces	    = perf_event__repipe_namespaces;
		inject->tool.निकास	    = perf_event__repipe_निकास;
		inject->tool.id_index	    = perf_event__process_id_index;
		inject->tool.auxtrace_info  = perf_event__process_auxtrace_info;
		inject->tool.auxtrace	    = perf_event__process_auxtrace;
		inject->tool.aux	    = perf_event__drop_aux;
		inject->tool.itrace_start   = perf_event__drop_aux,
		inject->tool.ordered_events = true;
		inject->tool.ordering_requires_बारtamps = true;
		/* Allow space in the header क्रम new attributes */
		output_data_offset = 4096;
		अगर (inject->strip)
			strip_init(inject);
	पूर्ण

	अगर (!inject->itrace_synth_opts.set)
		auxtrace_index__मुक्त(&session->auxtrace_index);

	अगर (!data_out->is_pipe)
		lseek(fd, output_data_offset, शुरू_से);

	ret = perf_session__process_events(session);
	अगर (ret)
		वापस ret;

	अगर (!data_out->is_pipe) अणु
		अगर (inject->build_ids)
			perf_header__set_feat(&session->header,
					      HEADER_BUILD_ID);
		/*
		 * Keep all buildids when there is unprocessed AUX data because
		 * it is not known which ones the AUX trace hits.
		 */
		अगर (perf_header__has_feat(&session->header, HEADER_BUILD_ID) &&
		    inject->have_auxtrace && !inject->itrace_synth_opts.set)
			dsos__hit_all(session);
		/*
		 * The AUX areas have been हटाओd and replaced with
		 * synthesized hardware events, so clear the feature flag.
		 */
		अगर (inject->itrace_synth_opts.set) अणु
			perf_header__clear_feat(&session->header,
						HEADER_AUXTRACE);
			अगर (inject->itrace_synth_opts.last_branch ||
			    inject->itrace_synth_opts.add_last_branch)
				perf_header__set_feat(&session->header,
						      HEADER_BRANCH_STACK);
		पूर्ण
		session->header.data_offset = output_data_offset;
		session->header.data_size = inject->bytes_written;
		perf_session__ग_लिखो_header(session, session->evlist, fd, true);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक cmd_inject(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा perf_inject inject = अणु
		.tool = अणु
			.sample		= perf_event__repipe_sample,
			.पढ़ो		= perf_event__repipe_sample,
			.mmap		= perf_event__repipe,
			.mmap2		= perf_event__repipe,
			.comm		= perf_event__repipe,
			.namespaces	= perf_event__repipe,
			.cgroup		= perf_event__repipe,
			.विभाजन		= perf_event__repipe,
			.निकास		= perf_event__repipe,
			.lost		= perf_event__repipe,
			.lost_samples	= perf_event__repipe,
			.aux		= perf_event__repipe,
			.itrace_start	= perf_event__repipe,
			.context_चयन	= perf_event__repipe,
			.throttle	= perf_event__repipe,
			.unthrottle	= perf_event__repipe,
			.ksymbol	= perf_event__repipe,
			.bpf		= perf_event__repipe,
			.text_poke	= perf_event__repipe,
			.attr		= perf_event__repipe_attr,
			.event_update	= perf_event__repipe_event_update,
			.tracing_data	= perf_event__repipe_op2_synth,
			.finished_round	= perf_event__repipe_oe_synth,
			.build_id	= perf_event__repipe_op2_synth,
			.id_index	= perf_event__repipe_op2_synth,
			.auxtrace_info	= perf_event__repipe_op2_synth,
			.auxtrace_error	= perf_event__repipe_op2_synth,
			.समय_conv	= perf_event__repipe_op2_synth,
			.thपढ़ो_map	= perf_event__repipe_op2_synth,
			.cpu_map	= perf_event__repipe_op2_synth,
			.stat_config	= perf_event__repipe_op2_synth,
			.stat		= perf_event__repipe_op2_synth,
			.stat_round	= perf_event__repipe_op2_synth,
			.feature	= perf_event__repipe_op2_synth,
			.compressed	= perf_event__repipe_op4_synth,
			.auxtrace	= perf_event__repipe_auxtrace,
		पूर्ण,
		.input_name  = "-",
		.samples = LIST_HEAD_INIT(inject.samples),
		.output = अणु
			.path = "-",
			.mode = PERF_DATA_MODE_WRITE,
			.use_stdio = true,
		पूर्ण,
	पूर्ण;
	काष्ठा perf_data data = अणु
		.mode = PERF_DATA_MODE_READ,
		.use_stdio = true,
	पूर्ण;
	पूर्णांक ret;

	काष्ठा option options[] = अणु
		OPT_BOOLEAN('b', "build-ids", &inject.build_ids,
			    "Inject build-ids into the output stream"),
		OPT_BOOLEAN(0, "buildid-all", &inject.build_id_all,
			    "Inject build-ids of all DSOs into the output stream"),
		OPT_STRING('i', "input", &inject.input_name, "file",
			   "input file name"),
		OPT_STRING('o', "output", &inject.output.path, "file",
			   "output file name"),
		OPT_BOOLEAN('s', "sched-stat", &inject.sched_stat,
			    "Merge sched-stat and sched-switch for getting events "
			    "where and how long tasks slept"),
#अगर_घोषित HAVE_JITDUMP
		OPT_BOOLEAN('j', "jit", &inject.jit_mode, "merge jitdump files into perf.data file"),
#पूर्ण_अगर
		OPT_INCR('v', "verbose", &verbose,
			 "be more verbose (show build ids, etc)"),
		OPT_STRING(0, "kallsyms", &symbol_conf.kallsyms_name, "file",
			   "kallsyms pathname"),
		OPT_BOOLEAN('f', "force", &data.force, "don't complain, करो it"),
		OPT_CALLBACK_OPTARG(0, "itrace", &inject.itrace_synth_opts,
				    शून्य, "opts", "Instruction Tracing options\n"
				    ITRACE_HELP,
				    itrace_parse_synth_opts),
		OPT_BOOLEAN(0, "strip", &inject.strip,
			    "strip non-synthesized events (use with --itrace)"),
		OPT_END()
	पूर्ण;
	स्थिर अक्षर * स्थिर inject_usage[] = अणु
		"perf inject [<options>]",
		शून्य
	पूर्ण;
#अगर_अघोषित HAVE_JITDUMP
	set_option_nobuild(options, 'j', "jit", "NO_LIBELF=1", true);
#पूर्ण_अगर
	argc = parse_options(argc, argv, options, inject_usage, 0);

	/*
	 * Any (unrecognized) arguments left?
	 */
	अगर (argc)
		usage_with_options(inject_usage, options);

	अगर (inject.strip && !inject.itrace_synth_opts.set) अणु
		pr_err("--strip option requires --itrace option\n");
		वापस -1;
	पूर्ण

	अगर (perf_data__खोलो(&inject.output)) अणु
		लिखो_त्रुटि("failed to create output file");
		वापस -1;
	पूर्ण

	data.path = inject.input_name;
	inject.session = perf_session__new(&data, inject.output.is_pipe, &inject.tool);
	अगर (IS_ERR(inject.session))
		वापस PTR_ERR(inject.session);

	अगर (zstd_init(&(inject.session->zstd_data), 0) < 0)
		pr_warning("Decompression initialization failed.\n");

	अगर (inject.build_ids && !inject.build_id_all) अणु
		/*
		 * to make sure the mmap records are ordered correctly
		 * and so that the correct especially due to jitted code
		 * mmaps. We cannot generate the buildid hit list and
		 * inject the jit mmaps at the same समय क्रम now.
		 */
		inject.tool.ordered_events = true;
		inject.tool.ordering_requires_बारtamps = true;
	पूर्ण

	अगर (inject.sched_stat) अणु
		inject.tool.ordered_events = true;
	पूर्ण

#अगर_घोषित HAVE_JITDUMP
	अगर (inject.jit_mode) अणु
		inject.tool.mmap2	   = perf_event__jit_repipe_mmap2;
		inject.tool.mmap	   = perf_event__jit_repipe_mmap;
		inject.tool.ordered_events = true;
		inject.tool.ordering_requires_बारtamps = true;
		/*
		 * JIT MMAP injection injects all MMAP events in one go, so it
		 * करोes not obey finished_round semantics.
		 */
		inject.tool.finished_round = perf_event__drop_oe;
	पूर्ण
#पूर्ण_अगर
	ret = symbol__init(&inject.session->header.env);
	अगर (ret < 0)
		जाओ out_delete;

	ret = __cmd_inject(&inject);

out_delete:
	zstd_fini(&(inject.session->zstd_data));
	perf_session__delete(inject.session);
	वापस ret;
पूर्ण
