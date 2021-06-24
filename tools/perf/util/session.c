<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश <api/fs/fs.h>

#समावेश <byteswap.h>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sys/mman.h>
#समावेश <perf/cpumap.h>

#समावेश "map_symbol.h"
#समावेश "branch.h"
#समावेश "debug.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "memswap.h"
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश "session.h"
#समावेश "tool.h"
#समावेश "perf_regs.h"
#समावेश "asm/bug.h"
#समावेश "auxtrace.h"
#समावेश "thread.h"
#समावेश "thread-stack.h"
#समावेश "sample-raw.h"
#समावेश "stat.h"
#समावेश "tsc.h"
#समावेश "ui/progress.h"
#समावेश "../perf.h"
#समावेश "arch/common.h"
#समावेश "units.h"
#समावेश <पूर्णांकernal/lib.h>

#अगर_घोषित HAVE_ZSTD_SUPPORT
अटल पूर्णांक perf_session__process_compressed_event(काष्ठा perf_session *session,
						  जोड़ perf_event *event, u64 file_offset)
अणु
	व्योम *src;
	माप_प्रकार decomp_size, src_size;
	u64 decomp_last_rem = 0;
	माप_प्रकार mmap_len, decomp_len = session->header.env.comp_mmap_len;
	काष्ठा decomp *decomp, *decomp_last = session->decomp_last;

	अगर (decomp_last) अणु
		decomp_last_rem = decomp_last->size - decomp_last->head;
		decomp_len += decomp_last_rem;
	पूर्ण

	mmap_len = माप(काष्ठा decomp) + decomp_len;
	decomp = mmap(शून्य, mmap_len, PROT_READ|PROT_WRITE,
		      MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	अगर (decomp == MAP_FAILED) अणु
		pr_err("Couldn't allocate memory for decompression\n");
		वापस -1;
	पूर्ण

	decomp->file_pos = file_offset;
	decomp->mmap_len = mmap_len;
	decomp->head = 0;

	अगर (decomp_last_rem) अणु
		स_नकल(decomp->data, &(decomp_last->data[decomp_last->head]), decomp_last_rem);
		decomp->size = decomp_last_rem;
	पूर्ण

	src = (व्योम *)event + माप(काष्ठा perf_record_compressed);
	src_size = event->pack.header.size - माप(काष्ठा perf_record_compressed);

	decomp_size = zstd_decompress_stream(&(session->zstd_data), src, src_size,
				&(decomp->data[decomp_last_rem]), decomp_len - decomp_last_rem);
	अगर (!decomp_size) अणु
		munmap(decomp, mmap_len);
		pr_err("Couldn't decompress data\n");
		वापस -1;
	पूर्ण

	decomp->size += decomp_size;

	अगर (session->decomp == शून्य) अणु
		session->decomp = decomp;
		session->decomp_last = decomp;
	पूर्ण अन्यथा अणु
		session->decomp_last->next = decomp;
		session->decomp_last = decomp;
	पूर्ण

	pr_debug("decomp (B): %zd to %zd\n", src_size, decomp_size);

	वापस 0;
पूर्ण
#अन्यथा /* !HAVE_ZSTD_SUPPORT */
#घोषणा perf_session__process_compressed_event perf_session__process_compressed_event_stub
#पूर्ण_अगर

अटल पूर्णांक perf_session__deliver_event(काष्ठा perf_session *session,
				       जोड़ perf_event *event,
				       काष्ठा perf_tool *tool,
				       u64 file_offset);

अटल पूर्णांक perf_session__खोलो(काष्ठा perf_session *session)
अणु
	काष्ठा perf_data *data = session->data;

	अगर (perf_session__पढ़ो_header(session) < 0) अणु
		pr_err("incompatible file format (rerun with -v to learn more)\n");
		वापस -1;
	पूर्ण

	अगर (perf_data__is_pipe(data))
		वापस 0;

	अगर (perf_header__has_feat(&session->header, HEADER_STAT))
		वापस 0;

	अगर (!evlist__valid_sample_type(session->evlist)) अणु
		pr_err("non matching sample_type\n");
		वापस -1;
	पूर्ण

	अगर (!evlist__valid_sample_id_all(session->evlist)) अणु
		pr_err("non matching sample_id_all\n");
		वापस -1;
	पूर्ण

	अगर (!evlist__valid_पढ़ो_क्रमmat(session->evlist)) अणु
		pr_err("non matching read_format\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम perf_session__set_id_hdr_size(काष्ठा perf_session *session)
अणु
	u16 id_hdr_size = evlist__id_hdr_size(session->evlist);

	machines__set_id_hdr_size(&session->machines, id_hdr_size);
पूर्ण

पूर्णांक perf_session__create_kernel_maps(काष्ठा perf_session *session)
अणु
	पूर्णांक ret = machine__create_kernel_maps(&session->machines.host);

	अगर (ret >= 0)
		ret = machines__create_guest_kernel_maps(&session->machines);
	वापस ret;
पूर्ण

अटल व्योम perf_session__destroy_kernel_maps(काष्ठा perf_session *session)
अणु
	machines__destroy_kernel_maps(&session->machines);
पूर्ण

अटल bool perf_session__has_comm_exec(काष्ठा perf_session *session)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(session->evlist, evsel) अणु
		अगर (evsel->core.attr.comm_exec)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम perf_session__set_comm_exec(काष्ठा perf_session *session)
अणु
	bool comm_exec = perf_session__has_comm_exec(session);

	machines__set_comm_exec(&session->machines, comm_exec);
पूर्ण

अटल पूर्णांक ordered_events__deliver_event(काष्ठा ordered_events *oe,
					 काष्ठा ordered_event *event)
अणु
	काष्ठा perf_session *session = container_of(oe, काष्ठा perf_session,
						    ordered_events);

	वापस perf_session__deliver_event(session, event->event,
					   session->tool, event->file_offset);
पूर्ण

काष्ठा perf_session *perf_session__new(काष्ठा perf_data *data,
				       bool repipe, काष्ठा perf_tool *tool)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा perf_session *session = zalloc(माप(*session));

	अगर (!session)
		जाओ out;

	session->repipe = repipe;
	session->tool   = tool;
	INIT_LIST_HEAD(&session->auxtrace_index);
	machines__init(&session->machines);
	ordered_events__init(&session->ordered_events,
			     ordered_events__deliver_event, शून्य);

	perf_env__init(&session->header.env);
	अगर (data) अणु
		ret = perf_data__खोलो(data);
		अगर (ret < 0)
			जाओ out_delete;

		session->data = data;

		अगर (perf_data__is_पढ़ो(data)) अणु
			ret = perf_session__खोलो(session);
			अगर (ret < 0)
				जाओ out_delete;

			/*
			 * set session attributes that are present in perf.data
			 * but not in pipe-mode.
			 */
			अगर (!data->is_pipe) अणु
				perf_session__set_id_hdr_size(session);
				perf_session__set_comm_exec(session);
			पूर्ण

			evlist__init_trace_event_sample_raw(session->evlist);

			/* Open the directory data. */
			अगर (data->is_dir) अणु
				ret = perf_data__खोलो_dir(data);
				अगर (ret)
					जाओ out_delete;
			पूर्ण

			अगर (!symbol_conf.kallsyms_name &&
			    !symbol_conf.vmlinux_name)
				symbol_conf.kallsyms_name = perf_data__kallsyms_name(data);
		पूर्ण
	पूर्ण अन्यथा  अणु
		session->machines.host.env = &perf_env;
	पूर्ण

	session->machines.host.single_address_space =
		perf_env__single_address_space(session->machines.host.env);

	अगर (!data || perf_data__is_ग_लिखो(data)) अणु
		/*
		 * In O_RDONLY mode this will be perक्रमmed when पढ़ोing the
		 * kernel MMAP event, in perf_event__process_mmap().
		 */
		अगर (perf_session__create_kernel_maps(session) < 0)
			pr_warning("Cannot read kernel map\n");
	पूर्ण

	/*
	 * In pipe-mode, evlist is empty until PERF_RECORD_HEADER_ATTR is
	 * processed, so evlist__sample_id_all is not meaningful here.
	 */
	अगर ((!data || !data->is_pipe) && tool && tool->ordering_requires_बारtamps &&
	    tool->ordered_events && !evlist__sample_id_all(session->evlist)) अणु
		dump_म_लिखो("WARNING: No sample_id_all support, falling back to unordered processing\n");
		tool->ordered_events = false;
	पूर्ण

	वापस session;

 out_delete:
	perf_session__delete(session);
 out:
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम perf_session__delete_thपढ़ोs(काष्ठा perf_session *session)
अणु
	machine__delete_thपढ़ोs(&session->machines.host);
पूर्ण

अटल व्योम perf_session__release_decomp_events(काष्ठा perf_session *session)
अणु
	काष्ठा decomp *next, *decomp;
	माप_प्रकार mmap_len;
	next = session->decomp;
	करो अणु
		decomp = next;
		अगर (decomp == शून्य)
			अवरोध;
		next = decomp->next;
		mmap_len = decomp->mmap_len;
		munmap(decomp, mmap_len);
	पूर्ण जबतक (1);
पूर्ण

व्योम perf_session__delete(काष्ठा perf_session *session)
अणु
	अगर (session == शून्य)
		वापस;
	auxtrace__मुक्त(session);
	auxtrace_index__मुक्त(&session->auxtrace_index);
	perf_session__destroy_kernel_maps(session);
	perf_session__delete_thपढ़ोs(session);
	perf_session__release_decomp_events(session);
	perf_env__निकास(&session->header.env);
	machines__निकास(&session->machines);
	अगर (session->data)
		perf_data__बंद(session->data);
	मुक्त(session);
पूर्ण

अटल पूर्णांक process_event_synth_tracing_data_stub(काष्ठा perf_session *session
						 __maybe_unused,
						 जोड़ perf_event *event
						 __maybe_unused)
अणु
	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक process_event_synth_attr_stub(काष्ठा perf_tool *tool __maybe_unused,
					 जोड़ perf_event *event __maybe_unused,
					 काष्ठा evlist **pevlist
					 __maybe_unused)
अणु
	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक process_event_synth_event_update_stub(काष्ठा perf_tool *tool __maybe_unused,
						 जोड़ perf_event *event __maybe_unused,
						 काष्ठा evlist **pevlist
						 __maybe_unused)
अणु
	अगर (dump_trace)
		perf_event__ख_लिखो_event_update(event, मानक_निकास);

	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक process_event_sample_stub(काष्ठा perf_tool *tool __maybe_unused,
				     जोड़ perf_event *event __maybe_unused,
				     काष्ठा perf_sample *sample __maybe_unused,
				     काष्ठा evsel *evsel __maybe_unused,
				     काष्ठा machine *machine __maybe_unused)
अणु
	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक process_event_stub(काष्ठा perf_tool *tool __maybe_unused,
			      जोड़ perf_event *event __maybe_unused,
			      काष्ठा perf_sample *sample __maybe_unused,
			      काष्ठा machine *machine __maybe_unused)
अणु
	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक process_finished_round_stub(काष्ठा perf_tool *tool __maybe_unused,
				       जोड़ perf_event *event __maybe_unused,
				       काष्ठा ordered_events *oe __maybe_unused)
अणु
	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक process_finished_round(काष्ठा perf_tool *tool,
				  जोड़ perf_event *event,
				  काष्ठा ordered_events *oe);

अटल पूर्णांक skipn(पूर्णांक fd, off_t n)
अणु
	अक्षर buf[4096];
	sमाप_प्रकार ret;

	जबतक (n > 0) अणु
		ret = पढ़ो(fd, buf, min(n, (off_t)माप(buf)));
		अगर (ret <= 0)
			वापस ret;
		n -= ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल s64 process_event_auxtrace_stub(काष्ठा perf_session *session __maybe_unused,
				       जोड़ perf_event *event)
अणु
	dump_म_लिखो(": unhandled!\n");
	अगर (perf_data__is_pipe(session->data))
		skipn(perf_data__fd(session->data), event->auxtrace.size);
	वापस event->auxtrace.size;
पूर्ण

अटल पूर्णांक process_event_op2_stub(काष्ठा perf_session *session __maybe_unused,
				  जोड़ perf_event *event __maybe_unused)
अणु
	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण


अटल
पूर्णांक process_event_thपढ़ो_map_stub(काष्ठा perf_session *session __maybe_unused,
				  जोड़ perf_event *event __maybe_unused)
अणु
	अगर (dump_trace)
		perf_event__ख_लिखो_thपढ़ो_map(event, मानक_निकास);

	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण

अटल
पूर्णांक process_event_cpu_map_stub(काष्ठा perf_session *session __maybe_unused,
			       जोड़ perf_event *event __maybe_unused)
अणु
	अगर (dump_trace)
		perf_event__ख_लिखो_cpu_map(event, मानक_निकास);

	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण

अटल
पूर्णांक process_event_stat_config_stub(काष्ठा perf_session *session __maybe_unused,
				   जोड़ perf_event *event __maybe_unused)
अणु
	अगर (dump_trace)
		perf_event__ख_लिखो_stat_config(event, मानक_निकास);

	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक process_stat_stub(काष्ठा perf_session *perf_session __maybe_unused,
			     जोड़ perf_event *event)
अणु
	अगर (dump_trace)
		perf_event__ख_लिखो_stat(event, मानक_निकास);

	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक process_stat_round_stub(काष्ठा perf_session *perf_session __maybe_unused,
				   जोड़ perf_event *event)
अणु
	अगर (dump_trace)
		perf_event__ख_लिखो_stat_round(event, मानक_निकास);

	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक process_event_समय_conv_stub(काष्ठा perf_session *perf_session __maybe_unused,
					जोड़ perf_event *event)
अणु
	अगर (dump_trace)
		perf_event__ख_लिखो_समय_conv(event, मानक_निकास);

	dump_म_लिखो(": unhandled!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक perf_session__process_compressed_event_stub(काष्ठा perf_session *session __maybe_unused,
						       जोड़ perf_event *event __maybe_unused,
						       u64 file_offset __maybe_unused)
अणु
       dump_म_लिखो(": unhandled!\n");
       वापस 0;
पूर्ण

व्योम perf_tool__fill_शेषs(काष्ठा perf_tool *tool)
अणु
	अगर (tool->sample == शून्य)
		tool->sample = process_event_sample_stub;
	अगर (tool->mmap == शून्य)
		tool->mmap = process_event_stub;
	अगर (tool->mmap2 == शून्य)
		tool->mmap2 = process_event_stub;
	अगर (tool->comm == शून्य)
		tool->comm = process_event_stub;
	अगर (tool->namespaces == शून्य)
		tool->namespaces = process_event_stub;
	अगर (tool->cgroup == शून्य)
		tool->cgroup = process_event_stub;
	अगर (tool->विभाजन == शून्य)
		tool->विभाजन = process_event_stub;
	अगर (tool->निकास == शून्य)
		tool->निकास = process_event_stub;
	अगर (tool->lost == शून्य)
		tool->lost = perf_event__process_lost;
	अगर (tool->lost_samples == शून्य)
		tool->lost_samples = perf_event__process_lost_samples;
	अगर (tool->aux == शून्य)
		tool->aux = perf_event__process_aux;
	अगर (tool->itrace_start == शून्य)
		tool->itrace_start = perf_event__process_itrace_start;
	अगर (tool->context_चयन == शून्य)
		tool->context_चयन = perf_event__process_चयन;
	अगर (tool->ksymbol == शून्य)
		tool->ksymbol = perf_event__process_ksymbol;
	अगर (tool->bpf == शून्य)
		tool->bpf = perf_event__process_bpf;
	अगर (tool->text_poke == शून्य)
		tool->text_poke = perf_event__process_text_poke;
	अगर (tool->पढ़ो == शून्य)
		tool->पढ़ो = process_event_sample_stub;
	अगर (tool->throttle == शून्य)
		tool->throttle = process_event_stub;
	अगर (tool->unthrottle == शून्य)
		tool->unthrottle = process_event_stub;
	अगर (tool->attr == शून्य)
		tool->attr = process_event_synth_attr_stub;
	अगर (tool->event_update == शून्य)
		tool->event_update = process_event_synth_event_update_stub;
	अगर (tool->tracing_data == शून्य)
		tool->tracing_data = process_event_synth_tracing_data_stub;
	अगर (tool->build_id == शून्य)
		tool->build_id = process_event_op2_stub;
	अगर (tool->finished_round == शून्य) अणु
		अगर (tool->ordered_events)
			tool->finished_round = process_finished_round;
		अन्यथा
			tool->finished_round = process_finished_round_stub;
	पूर्ण
	अगर (tool->id_index == शून्य)
		tool->id_index = process_event_op2_stub;
	अगर (tool->auxtrace_info == शून्य)
		tool->auxtrace_info = process_event_op2_stub;
	अगर (tool->auxtrace == शून्य)
		tool->auxtrace = process_event_auxtrace_stub;
	अगर (tool->auxtrace_error == शून्य)
		tool->auxtrace_error = process_event_op2_stub;
	अगर (tool->thपढ़ो_map == शून्य)
		tool->thपढ़ो_map = process_event_thपढ़ो_map_stub;
	अगर (tool->cpu_map == शून्य)
		tool->cpu_map = process_event_cpu_map_stub;
	अगर (tool->stat_config == शून्य)
		tool->stat_config = process_event_stat_config_stub;
	अगर (tool->stat == शून्य)
		tool->stat = process_stat_stub;
	अगर (tool->stat_round == शून्य)
		tool->stat_round = process_stat_round_stub;
	अगर (tool->समय_conv == शून्य)
		tool->समय_conv = process_event_समय_conv_stub;
	अगर (tool->feature == शून्य)
		tool->feature = process_event_op2_stub;
	अगर (tool->compressed == शून्य)
		tool->compressed = perf_session__process_compressed_event;
पूर्ण

अटल व्योम swap_sample_id_all(जोड़ perf_event *event, व्योम *data)
अणु
	व्योम *end = (व्योम *) event + event->header.size;
	पूर्णांक size = end - data;

	BUG_ON(size % माप(u64));
	mem_bswap_64(data, size);
पूर्ण

अटल व्योम perf_event__all64_swap(जोड़ perf_event *event,
				   bool sample_id_all __maybe_unused)
अणु
	काष्ठा perf_event_header *hdr = &event->header;
	mem_bswap_64(hdr + 1, event->header.size - माप(*hdr));
पूर्ण

अटल व्योम perf_event__comm_swap(जोड़ perf_event *event, bool sample_id_all)
अणु
	event->comm.pid = bswap_32(event->comm.pid);
	event->comm.tid = bswap_32(event->comm.tid);

	अगर (sample_id_all) अणु
		व्योम *data = &event->comm.comm;

		data += PERF_ALIGN(म_माप(data) + 1, माप(u64));
		swap_sample_id_all(event, data);
	पूर्ण
पूर्ण

अटल व्योम perf_event__mmap_swap(जोड़ perf_event *event,
				  bool sample_id_all)
अणु
	event->mmap.pid	  = bswap_32(event->mmap.pid);
	event->mmap.tid	  = bswap_32(event->mmap.tid);
	event->mmap.start = bswap_64(event->mmap.start);
	event->mmap.len	  = bswap_64(event->mmap.len);
	event->mmap.pgoff = bswap_64(event->mmap.pgoff);

	अगर (sample_id_all) अणु
		व्योम *data = &event->mmap.filename;

		data += PERF_ALIGN(म_माप(data) + 1, माप(u64));
		swap_sample_id_all(event, data);
	पूर्ण
पूर्ण

अटल व्योम perf_event__mmap2_swap(जोड़ perf_event *event,
				  bool sample_id_all)
अणु
	event->mmap2.pid   = bswap_32(event->mmap2.pid);
	event->mmap2.tid   = bswap_32(event->mmap2.tid);
	event->mmap2.start = bswap_64(event->mmap2.start);
	event->mmap2.len   = bswap_64(event->mmap2.len);
	event->mmap2.pgoff = bswap_64(event->mmap2.pgoff);

	अगर (!(event->header.misc & PERF_RECORD_MISC_MMAP_BUILD_ID)) अणु
		event->mmap2.maj   = bswap_32(event->mmap2.maj);
		event->mmap2.min   = bswap_32(event->mmap2.min);
		event->mmap2.ino   = bswap_64(event->mmap2.ino);
		event->mmap2.ino_generation = bswap_64(event->mmap2.ino_generation);
	पूर्ण

	अगर (sample_id_all) अणु
		व्योम *data = &event->mmap2.filename;

		data += PERF_ALIGN(म_माप(data) + 1, माप(u64));
		swap_sample_id_all(event, data);
	पूर्ण
पूर्ण
अटल व्योम perf_event__task_swap(जोड़ perf_event *event, bool sample_id_all)
अणु
	event->विभाजन.pid	 = bswap_32(event->विभाजन.pid);
	event->विभाजन.tid	 = bswap_32(event->विभाजन.tid);
	event->विभाजन.ppid = bswap_32(event->विभाजन.ppid);
	event->विभाजन.ptid = bswap_32(event->विभाजन.ptid);
	event->विभाजन.समय = bswap_64(event->विभाजन.समय);

	अगर (sample_id_all)
		swap_sample_id_all(event, &event->विभाजन + 1);
पूर्ण

अटल व्योम perf_event__पढ़ो_swap(जोड़ perf_event *event, bool sample_id_all)
अणु
	event->पढ़ो.pid		 = bswap_32(event->पढ़ो.pid);
	event->पढ़ो.tid		 = bswap_32(event->पढ़ो.tid);
	event->पढ़ो.value	 = bswap_64(event->पढ़ो.value);
	event->पढ़ो.समय_enabled = bswap_64(event->पढ़ो.समय_enabled);
	event->पढ़ो.समय_running = bswap_64(event->पढ़ो.समय_running);
	event->पढ़ो.id		 = bswap_64(event->पढ़ो.id);

	अगर (sample_id_all)
		swap_sample_id_all(event, &event->पढ़ो + 1);
पूर्ण

अटल व्योम perf_event__aux_swap(जोड़ perf_event *event, bool sample_id_all)
अणु
	event->aux.aux_offset = bswap_64(event->aux.aux_offset);
	event->aux.aux_size   = bswap_64(event->aux.aux_size);
	event->aux.flags      = bswap_64(event->aux.flags);

	अगर (sample_id_all)
		swap_sample_id_all(event, &event->aux + 1);
पूर्ण

अटल व्योम perf_event__itrace_start_swap(जोड़ perf_event *event,
					  bool sample_id_all)
अणु
	event->itrace_start.pid	 = bswap_32(event->itrace_start.pid);
	event->itrace_start.tid	 = bswap_32(event->itrace_start.tid);

	अगर (sample_id_all)
		swap_sample_id_all(event, &event->itrace_start + 1);
पूर्ण

अटल व्योम perf_event__चयन_swap(जोड़ perf_event *event, bool sample_id_all)
अणु
	अगर (event->header.type == PERF_RECORD_SWITCH_CPU_WIDE) अणु
		event->context_चयन.next_prev_pid =
				bswap_32(event->context_चयन.next_prev_pid);
		event->context_चयन.next_prev_tid =
				bswap_32(event->context_चयन.next_prev_tid);
	पूर्ण

	अगर (sample_id_all)
		swap_sample_id_all(event, &event->context_चयन + 1);
पूर्ण

अटल व्योम perf_event__text_poke_swap(जोड़ perf_event *event, bool sample_id_all)
अणु
	event->text_poke.addr    = bswap_64(event->text_poke.addr);
	event->text_poke.old_len = bswap_16(event->text_poke.old_len);
	event->text_poke.new_len = bswap_16(event->text_poke.new_len);

	अगर (sample_id_all) अणु
		माप_प्रकार len = माप(event->text_poke.old_len) +
			     माप(event->text_poke.new_len) +
			     event->text_poke.old_len +
			     event->text_poke.new_len;
		व्योम *data = &event->text_poke.old_len;

		data += PERF_ALIGN(len, माप(u64));
		swap_sample_id_all(event, data);
	पूर्ण
पूर्ण

अटल व्योम perf_event__throttle_swap(जोड़ perf_event *event,
				      bool sample_id_all)
अणु
	event->throttle.समय	  = bswap_64(event->throttle.समय);
	event->throttle.id	  = bswap_64(event->throttle.id);
	event->throttle.stream_id = bswap_64(event->throttle.stream_id);

	अगर (sample_id_all)
		swap_sample_id_all(event, &event->throttle + 1);
पूर्ण

अटल व्योम perf_event__namespaces_swap(जोड़ perf_event *event,
					bool sample_id_all)
अणु
	u64 i;

	event->namespaces.pid		= bswap_32(event->namespaces.pid);
	event->namespaces.tid		= bswap_32(event->namespaces.tid);
	event->namespaces.nr_namespaces	= bswap_64(event->namespaces.nr_namespaces);

	क्रम (i = 0; i < event->namespaces.nr_namespaces; i++) अणु
		काष्ठा perf_ns_link_info *ns = &event->namespaces.link_info[i];

		ns->dev = bswap_64(ns->dev);
		ns->ino = bswap_64(ns->ino);
	पूर्ण

	अगर (sample_id_all)
		swap_sample_id_all(event, &event->namespaces.link_info[i]);
पूर्ण

अटल व्योम perf_event__cgroup_swap(जोड़ perf_event *event, bool sample_id_all)
अणु
	event->cgroup.id = bswap_64(event->cgroup.id);

	अगर (sample_id_all) अणु
		व्योम *data = &event->cgroup.path;

		data += PERF_ALIGN(म_माप(data) + 1, माप(u64));
		swap_sample_id_all(event, data);
	पूर्ण
पूर्ण

अटल u8 revbyte(u8 b)
अणु
	पूर्णांक rev = (b >> 4) | ((b & 0xf) << 4);
	rev = ((rev & 0xcc) >> 2) | ((rev & 0x33) << 2);
	rev = ((rev & 0xaa) >> 1) | ((rev & 0x55) << 1);
	वापस (u8) rev;
पूर्ण

/*
 * XXX this is hack in attempt to carry flags bitfield
 * through endian village. ABI says:
 *
 * Bit-fields are allocated from right to left (least to most signअगरicant)
 * on little-endian implementations and from left to right (most to least
 * signअगरicant) on big-endian implementations.
 *
 * The above seems to be byte specअगरic, so we need to reverse each
 * byte of the bitfield. 'Internet' also says this might be implementation
 * specअगरic and we probably need proper fix and carry perf_event_attr
 * bitfield flags in separate data file FEAT_ section. Thought this seems
 * to work क्रम now.
 */
अटल व्योम swap_bitfield(u8 *p, अचिन्हित len)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < len; i++) अणु
		*p = revbyte(*p);
		p++;
	पूर्ण
पूर्ण

/* exported क्रम swapping attributes in file header */
व्योम perf_event__attr_swap(काष्ठा perf_event_attr *attr)
अणु
	attr->type		= bswap_32(attr->type);
	attr->size		= bswap_32(attr->size);

#घोषणा bswap_safe(f, n) 					\
	(attr->size > (दुरत्व(काष्ठा perf_event_attr, f) + 	\
		       माप(attr->f) * (n)))
#घोषणा bswap_field(f, sz) 			\
करो अणु 						\
	अगर (bswap_safe(f, 0))			\
		attr->f = bswap_##sz(attr->f);	\
पूर्ण जबतक(0)
#घोषणा bswap_field_16(f) bswap_field(f, 16)
#घोषणा bswap_field_32(f) bswap_field(f, 32)
#घोषणा bswap_field_64(f) bswap_field(f, 64)

	bswap_field_64(config);
	bswap_field_64(sample_period);
	bswap_field_64(sample_type);
	bswap_field_64(पढ़ो_क्रमmat);
	bswap_field_32(wakeup_events);
	bswap_field_32(bp_type);
	bswap_field_64(bp_addr);
	bswap_field_64(bp_len);
	bswap_field_64(branch_sample_type);
	bswap_field_64(sample_regs_user);
	bswap_field_32(sample_stack_user);
	bswap_field_32(aux_watermark);
	bswap_field_16(sample_max_stack);
	bswap_field_32(aux_sample_size);

	/*
	 * After पढ़ो_क्रमmat are bitfields. Check पढ़ो_क्रमmat because
	 * we are unable to use दुरत्व on bitfield.
	 */
	अगर (bswap_safe(पढ़ो_क्रमmat, 1))
		swap_bitfield((u8 *) (&attr->पढ़ो_क्रमmat + 1),
			      माप(u64));
#अघोषित bswap_field_64
#अघोषित bswap_field_32
#अघोषित bswap_field
#अघोषित bswap_safe
पूर्ण

अटल व्योम perf_event__hdr_attr_swap(जोड़ perf_event *event,
				      bool sample_id_all __maybe_unused)
अणु
	माप_प्रकार size;

	perf_event__attr_swap(&event->attr.attr);

	size = event->header.size;
	size -= (व्योम *)&event->attr.id - (व्योम *)event;
	mem_bswap_64(event->attr.id, size);
पूर्ण

अटल व्योम perf_event__event_update_swap(जोड़ perf_event *event,
					  bool sample_id_all __maybe_unused)
अणु
	event->event_update.type = bswap_64(event->event_update.type);
	event->event_update.id   = bswap_64(event->event_update.id);
पूर्ण

अटल व्योम perf_event__event_type_swap(जोड़ perf_event *event,
					bool sample_id_all __maybe_unused)
अणु
	event->event_type.event_type.event_id =
		bswap_64(event->event_type.event_type.event_id);
पूर्ण

अटल व्योम perf_event__tracing_data_swap(जोड़ perf_event *event,
					  bool sample_id_all __maybe_unused)
अणु
	event->tracing_data.size = bswap_32(event->tracing_data.size);
पूर्ण

अटल व्योम perf_event__auxtrace_info_swap(जोड़ perf_event *event,
					   bool sample_id_all __maybe_unused)
अणु
	माप_प्रकार size;

	event->auxtrace_info.type = bswap_32(event->auxtrace_info.type);

	size = event->header.size;
	size -= (व्योम *)&event->auxtrace_info.priv - (व्योम *)event;
	mem_bswap_64(event->auxtrace_info.priv, size);
पूर्ण

अटल व्योम perf_event__auxtrace_swap(जोड़ perf_event *event,
				      bool sample_id_all __maybe_unused)
अणु
	event->auxtrace.size      = bswap_64(event->auxtrace.size);
	event->auxtrace.offset    = bswap_64(event->auxtrace.offset);
	event->auxtrace.reference = bswap_64(event->auxtrace.reference);
	event->auxtrace.idx       = bswap_32(event->auxtrace.idx);
	event->auxtrace.tid       = bswap_32(event->auxtrace.tid);
	event->auxtrace.cpu       = bswap_32(event->auxtrace.cpu);
पूर्ण

अटल व्योम perf_event__auxtrace_error_swap(जोड़ perf_event *event,
					    bool sample_id_all __maybe_unused)
अणु
	event->auxtrace_error.type = bswap_32(event->auxtrace_error.type);
	event->auxtrace_error.code = bswap_32(event->auxtrace_error.code);
	event->auxtrace_error.cpu  = bswap_32(event->auxtrace_error.cpu);
	event->auxtrace_error.pid  = bswap_32(event->auxtrace_error.pid);
	event->auxtrace_error.tid  = bswap_32(event->auxtrace_error.tid);
	event->auxtrace_error.fmt  = bswap_32(event->auxtrace_error.fmt);
	event->auxtrace_error.ip   = bswap_64(event->auxtrace_error.ip);
	अगर (event->auxtrace_error.fmt)
		event->auxtrace_error.समय = bswap_64(event->auxtrace_error.समय);
पूर्ण

अटल व्योम perf_event__thपढ़ो_map_swap(जोड़ perf_event *event,
					bool sample_id_all __maybe_unused)
अणु
	अचिन्हित i;

	event->thपढ़ो_map.nr = bswap_64(event->thपढ़ो_map.nr);

	क्रम (i = 0; i < event->thपढ़ो_map.nr; i++)
		event->thपढ़ो_map.entries[i].pid = bswap_64(event->thपढ़ो_map.entries[i].pid);
पूर्ण

अटल व्योम perf_event__cpu_map_swap(जोड़ perf_event *event,
				     bool sample_id_all __maybe_unused)
अणु
	काष्ठा perf_record_cpu_map_data *data = &event->cpu_map.data;
	काष्ठा cpu_map_entries *cpus;
	काष्ठा perf_record_record_cpu_map *mask;
	अचिन्हित i;

	data->type = bswap_16(data->type);

	चयन (data->type) अणु
	हाल PERF_CPU_MAP__CPUS:
		cpus = (काष्ठा cpu_map_entries *)data->data;

		cpus->nr = bswap_16(cpus->nr);

		क्रम (i = 0; i < cpus->nr; i++)
			cpus->cpu[i] = bswap_16(cpus->cpu[i]);
		अवरोध;
	हाल PERF_CPU_MAP__MASK:
		mask = (काष्ठा perf_record_record_cpu_map *)data->data;

		mask->nr = bswap_16(mask->nr);
		mask->दीर्घ_size = bswap_16(mask->दीर्घ_size);

		चयन (mask->दीर्घ_size) अणु
		हाल 4: mem_bswap_32(&mask->mask, mask->nr); अवरोध;
		हाल 8: mem_bswap_64(&mask->mask, mask->nr); अवरोध;
		शेष:
			pr_err("cpu_map swap: unsupported long size\n");
		पूर्ण
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम perf_event__stat_config_swap(जोड़ perf_event *event,
					 bool sample_id_all __maybe_unused)
अणु
	u64 size;

	size  = bswap_64(event->stat_config.nr) * माप(event->stat_config.data[0]);
	size += 1; /* nr item itself */
	mem_bswap_64(&event->stat_config.nr, size);
पूर्ण

अटल व्योम perf_event__stat_swap(जोड़ perf_event *event,
				  bool sample_id_all __maybe_unused)
अणु
	event->stat.id     = bswap_64(event->stat.id);
	event->stat.thपढ़ो = bswap_32(event->stat.thपढ़ो);
	event->stat.cpu    = bswap_32(event->stat.cpu);
	event->stat.val    = bswap_64(event->stat.val);
	event->stat.ena    = bswap_64(event->stat.ena);
	event->stat.run    = bswap_64(event->stat.run);
पूर्ण

अटल व्योम perf_event__stat_round_swap(जोड़ perf_event *event,
					bool sample_id_all __maybe_unused)
अणु
	event->stat_round.type = bswap_64(event->stat_round.type);
	event->stat_round.समय = bswap_64(event->stat_round.समय);
पूर्ण

अटल व्योम perf_event__समय_conv_swap(जोड़ perf_event *event,
				       bool sample_id_all __maybe_unused)
अणु
	event->समय_conv.समय_shअगरt = bswap_64(event->समय_conv.समय_shअगरt);
	event->समय_conv.समय_mult  = bswap_64(event->समय_conv.समय_mult);
	event->समय_conv.समय_zero  = bswap_64(event->समय_conv.समय_zero);

	अगर (event_contains(event->समय_conv, समय_cycles)) अणु
		event->समय_conv.समय_cycles = bswap_64(event->समय_conv.समय_cycles);
		event->समय_conv.समय_mask = bswap_64(event->समय_conv.समय_mask);
	पूर्ण
पूर्ण

प्रकार व्योम (*perf_event__swap_op)(जोड़ perf_event *event,
				    bool sample_id_all);

अटल perf_event__swap_op perf_event__swap_ops[] = अणु
	[PERF_RECORD_MMAP]		  = perf_event__mmap_swap,
	[PERF_RECORD_MMAP2]		  = perf_event__mmap2_swap,
	[PERF_RECORD_COMM]		  = perf_event__comm_swap,
	[PERF_RECORD_FORK]		  = perf_event__task_swap,
	[PERF_RECORD_EXIT]		  = perf_event__task_swap,
	[PERF_RECORD_LOST]		  = perf_event__all64_swap,
	[PERF_RECORD_READ]		  = perf_event__पढ़ो_swap,
	[PERF_RECORD_THROTTLE]		  = perf_event__throttle_swap,
	[PERF_RECORD_UNTHROTTLE]	  = perf_event__throttle_swap,
	[PERF_RECORD_SAMPLE]		  = perf_event__all64_swap,
	[PERF_RECORD_AUX]		  = perf_event__aux_swap,
	[PERF_RECORD_ITRACE_START]	  = perf_event__itrace_start_swap,
	[PERF_RECORD_LOST_SAMPLES]	  = perf_event__all64_swap,
	[PERF_RECORD_SWITCH]		  = perf_event__चयन_swap,
	[PERF_RECORD_SWITCH_CPU_WIDE]	  = perf_event__चयन_swap,
	[PERF_RECORD_NAMESPACES]	  = perf_event__namespaces_swap,
	[PERF_RECORD_CGROUP]		  = perf_event__cgroup_swap,
	[PERF_RECORD_TEXT_POKE]		  = perf_event__text_poke_swap,
	[PERF_RECORD_HEADER_ATTR]	  = perf_event__hdr_attr_swap,
	[PERF_RECORD_HEADER_EVENT_TYPE]	  = perf_event__event_type_swap,
	[PERF_RECORD_HEADER_TRACING_DATA] = perf_event__tracing_data_swap,
	[PERF_RECORD_HEADER_BUILD_ID]	  = शून्य,
	[PERF_RECORD_ID_INDEX]		  = perf_event__all64_swap,
	[PERF_RECORD_AUXTRACE_INFO]	  = perf_event__auxtrace_info_swap,
	[PERF_RECORD_AUXTRACE]		  = perf_event__auxtrace_swap,
	[PERF_RECORD_AUXTRACE_ERROR]	  = perf_event__auxtrace_error_swap,
	[PERF_RECORD_THREAD_MAP]	  = perf_event__thपढ़ो_map_swap,
	[PERF_RECORD_CPU_MAP]		  = perf_event__cpu_map_swap,
	[PERF_RECORD_STAT_CONFIG]	  = perf_event__stat_config_swap,
	[PERF_RECORD_STAT]		  = perf_event__stat_swap,
	[PERF_RECORD_STAT_ROUND]	  = perf_event__stat_round_swap,
	[PERF_RECORD_EVENT_UPDATE]	  = perf_event__event_update_swap,
	[PERF_RECORD_TIME_CONV]		  = perf_event__समय_conv_swap,
	[PERF_RECORD_HEADER_MAX]	  = शून्य,
पूर्ण;

/*
 * When perf record finishes a pass on every buffers, it records this pseuकरो
 * event.
 * We record the max बारtamp t found in the pass n.
 * Assuming these बारtamps are monotonic across cpus, we know that अगर
 * a buffer still has events with बारtamps below t, they will be all
 * available and then पढ़ो in the pass n + 1.
 * Hence when we start to पढ़ो the pass n + 2, we can safely flush every
 * events with बारtamps below t.
 *
 *    ============ PASS n =================
 *       CPU 0         |   CPU 1
 *                     |
 *    cnt1 बारtamps  |   cnt2 बारtamps
 *          1          |         2
 *          2          |         3
 *          -          |         4  <--- max recorded
 *
 *    ============ PASS n + 1 ==============
 *       CPU 0         |   CPU 1
 *                     |
 *    cnt1 बारtamps  |   cnt2 बारtamps
 *          3          |         5
 *          4          |         6
 *          5          |         7 <---- max recorded
 *
 *      Flush every events below बारtamp 4
 *
 *    ============ PASS n + 2 ==============
 *       CPU 0         |   CPU 1
 *                     |
 *    cnt1 बारtamps  |   cnt2 बारtamps
 *          6          |         8
 *          7          |         9
 *          -          |         10
 *
 *      Flush every events below बारtamp 7
 *      etc...
 */
अटल पूर्णांक process_finished_round(काष्ठा perf_tool *tool __maybe_unused,
				  जोड़ perf_event *event __maybe_unused,
				  काष्ठा ordered_events *oe)
अणु
	अगर (dump_trace)
		ख_लिखो(मानक_निकास, "\n");
	वापस ordered_events__flush(oe, OE_FLUSH__ROUND);
पूर्ण

पूर्णांक perf_session__queue_event(काष्ठा perf_session *s, जोड़ perf_event *event,
			      u64 बारtamp, u64 file_offset)
अणु
	वापस ordered_events__queue(&s->ordered_events, event, बारtamp, file_offset);
पूर्ण

अटल व्योम callchain__lbr_callstack_म_लिखो(काष्ठा perf_sample *sample)
अणु
	काष्ठा ip_callchain *callchain = sample->callchain;
	काष्ठा branch_stack *lbr_stack = sample->branch_stack;
	काष्ठा branch_entry *entries = perf_sample__branch_entries(sample);
	u64 kernel_callchain_nr = callchain->nr;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < kernel_callchain_nr; i++) अणु
		अगर (callchain->ips[i] == PERF_CONTEXT_USER)
			अवरोध;
	पूर्ण

	अगर ((i != kernel_callchain_nr) && lbr_stack->nr) अणु
		u64 total_nr;
		/*
		 * LBR callstack can only get user call chain,
		 * i is kernel call chain number,
		 * 1 is PERF_CONTEXT_USER.
		 *
		 * The user call chain is stored in LBR रेजिस्टरs.
		 * LBR are pair रेजिस्टरs. The caller is stored
		 * in "from" रेजिस्टर, जबतक the callee is stored
		 * in "to" रेजिस्टर.
		 * For example, there is a call stack
		 * "A"->"B"->"C"->"D".
		 * The LBR रेजिस्टरs will be recorded like
		 * "C"->"D", "B"->"C", "A"->"B".
		 * So only the first "to" रेजिस्टर and all "from"
		 * रेजिस्टरs are needed to स्थिरruct the whole stack.
		 */
		total_nr = i + 1 + lbr_stack->nr + 1;
		kernel_callchain_nr = i + 1;

		म_लिखो("... LBR call chain: nr:%" PRIu64 "\n", total_nr);

		क्रम (i = 0; i < kernel_callchain_nr; i++)
			म_लिखो("..... %2d: %016" PRIx64 "\n",
			       i, callchain->ips[i]);

		म_लिखो("..... %2d: %016" PRIx64 "\n",
		       (पूर्णांक)(kernel_callchain_nr), entries[0].to);
		क्रम (i = 0; i < lbr_stack->nr; i++)
			म_लिखो("..... %2d: %016" PRIx64 "\n",
			       (पूर्णांक)(i + kernel_callchain_nr + 1), entries[i].from);
	पूर्ण
पूर्ण

अटल व्योम callchain__म_लिखो(काष्ठा evsel *evsel,
			      काष्ठा perf_sample *sample)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ip_callchain *callchain = sample->callchain;

	अगर (evsel__has_branch_callstack(evsel))
		callchain__lbr_callstack_म_लिखो(sample);

	म_लिखो("... FP chain: nr:%" PRIu64 "\n", callchain->nr);

	क्रम (i = 0; i < callchain->nr; i++)
		म_लिखो("..... %2d: %016" PRIx64 "\n",
		       i, callchain->ips[i]);
पूर्ण

अटल व्योम branch_stack__म_लिखो(काष्ठा perf_sample *sample, bool callstack)
अणु
	काष्ठा branch_entry *entries = perf_sample__branch_entries(sample);
	uपूर्णांक64_t i;

	म_लिखो("%s: nr:%" PRIu64 "\n",
		!callstack ? "... branch stack" : "... branch callstack",
		sample->branch_stack->nr);

	क्रम (i = 0; i < sample->branch_stack->nr; i++) अणु
		काष्ठा branch_entry *e = &entries[i];

		अगर (!callstack) अणु
			म_लिखो("..... %2"PRIu64": %016" PRIx64 " -> %016" PRIx64 " %hu cycles %s%s%s%s %x\n",
				i, e->from, e->to,
				(अचिन्हित लघु)e->flags.cycles,
				e->flags.mispred ? "M" : " ",
				e->flags.predicted ? "P" : " ",
				e->flags.पात ? "A" : " ",
				e->flags.in_tx ? "T" : " ",
				(अचिन्हित)e->flags.reserved);
		पूर्ण अन्यथा अणु
			म_लिखो("..... %2"PRIu64": %016" PRIx64 "\n",
				i, i > 0 ? e->from : e->to);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम regs_dump__म_लिखो(u64 mask, u64 *regs)
अणु
	अचिन्हित rid, i = 0;

	क्रम_each_set_bit(rid, (अचिन्हित दीर्घ *) &mask, माप(mask) * 8) अणु
		u64 val = regs[i++];

		म_लिखो(".... %-5s 0x%016" PRIx64 "\n",
		       perf_reg_name(rid), val);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *regs_abi[] = अणु
	[PERF_SAMPLE_REGS_ABI_NONE] = "none",
	[PERF_SAMPLE_REGS_ABI_32] = "32-bit",
	[PERF_SAMPLE_REGS_ABI_64] = "64-bit",
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *regs_dump_abi(काष्ठा regs_dump *d)
अणु
	अगर (d->abi > PERF_SAMPLE_REGS_ABI_64)
		वापस "unknown";

	वापस regs_abi[d->abi];
पूर्ण

अटल व्योम regs__म_लिखो(स्थिर अक्षर *type, काष्ठा regs_dump *regs)
अणु
	u64 mask = regs->mask;

	म_लिखो("... %s regs: mask 0x%" PRIx64 " ABI %s\n",
	       type,
	       mask,
	       regs_dump_abi(regs));

	regs_dump__म_लिखो(mask, regs->regs);
पूर्ण

अटल व्योम regs_user__म_लिखो(काष्ठा perf_sample *sample)
अणु
	काष्ठा regs_dump *user_regs = &sample->user_regs;

	अगर (user_regs->regs)
		regs__म_लिखो("user", user_regs);
पूर्ण

अटल व्योम regs_पूर्णांकr__म_लिखो(काष्ठा perf_sample *sample)
अणु
	काष्ठा regs_dump *पूर्णांकr_regs = &sample->पूर्णांकr_regs;

	अगर (पूर्णांकr_regs->regs)
		regs__म_लिखो("intr", पूर्णांकr_regs);
पूर्ण

अटल व्योम stack_user__म_लिखो(काष्ठा stack_dump *dump)
अणु
	म_लिखो("... ustack: size %" PRIu64 ", offset 0x%x\n",
	       dump->size, dump->offset);
पूर्ण

अटल व्योम evlist__prपूर्णांक_tstamp(काष्ठा evlist *evlist, जोड़ perf_event *event, काष्ठा perf_sample *sample)
अणु
	u64 sample_type = __evlist__combined_sample_type(evlist);

	अगर (event->header.type != PERF_RECORD_SAMPLE &&
	    !evlist__sample_id_all(evlist)) अणु
		ख_माला_दो("-1 -1 ", मानक_निकास);
		वापस;
	पूर्ण

	अगर ((sample_type & PERF_SAMPLE_CPU))
		म_लिखो("%u ", sample->cpu);

	अगर (sample_type & PERF_SAMPLE_TIME)
		म_लिखो("%" PRIu64 " ", sample->समय);
पूर्ण

अटल व्योम sample_पढ़ो__म_लिखो(काष्ठा perf_sample *sample, u64 पढ़ो_क्रमmat)
अणु
	म_लिखो("... sample_read:\n");

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED)
		म_लिखो("...... time enabled %016" PRIx64 "\n",
		       sample->पढ़ो.समय_enabled);

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING)
		म_लिखो("...... time running %016" PRIx64 "\n",
		       sample->पढ़ो.समय_running);

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP) अणु
		u64 i;

		म_लिखो(".... group nr %" PRIu64 "\n", sample->पढ़ो.group.nr);

		क्रम (i = 0; i < sample->पढ़ो.group.nr; i++) अणु
			काष्ठा sample_पढ़ो_value *value;

			value = &sample->पढ़ो.group.values[i];
			म_लिखो("..... id %016" PRIx64
			       ", value %016" PRIx64 "\n",
			       value->id, value->value);
		पूर्ण
	पूर्ण अन्यथा
		म_लिखो("..... id %016" PRIx64 ", value %016" PRIx64 "\n",
			sample->पढ़ो.one.id, sample->पढ़ो.one.value);
पूर्ण

अटल व्योम dump_event(काष्ठा evlist *evlist, जोड़ perf_event *event,
		       u64 file_offset, काष्ठा perf_sample *sample)
अणु
	अगर (!dump_trace)
		वापस;

	म_लिखो("\n%#" PRIx64 " [%#x]: event: %d\n",
	       file_offset, event->header.size, event->header.type);

	trace_event(event);
	अगर (event->header.type == PERF_RECORD_SAMPLE && evlist->trace_event_sample_raw)
		evlist->trace_event_sample_raw(evlist, event, sample);

	अगर (sample)
		evlist__prपूर्णांक_tstamp(evlist, event, sample);

	म_लिखो("%#" PRIx64 " [%#x]: PERF_RECORD_%s", file_offset,
	       event->header.size, perf_event__name(event->header.type));
पूर्ण

अक्षर *get_page_size_name(u64 size, अक्षर *str)
अणु
	अगर (!size || !unit_number__scnम_लिखो(str, PAGE_SIZE_NAME_LEN, size))
		snम_लिखो(str, PAGE_SIZE_NAME_LEN, "%s", "N/A");

	वापस str;
पूर्ण

अटल व्योम dump_sample(काष्ठा evsel *evsel, जोड़ perf_event *event,
			काष्ठा perf_sample *sample)
अणु
	u64 sample_type;
	अक्षर str[PAGE_SIZE_NAME_LEN];

	अगर (!dump_trace)
		वापस;

	म_लिखो("(IP, 0x%x): %d/%d: %#" PRIx64 " period: %" PRIu64 " addr: %#" PRIx64 "\n",
	       event->header.misc, sample->pid, sample->tid, sample->ip,
	       sample->period, sample->addr);

	sample_type = evsel->core.attr.sample_type;

	अगर (evsel__has_callchain(evsel))
		callchain__म_लिखो(evsel, sample);

	अगर (evsel__has_br_stack(evsel))
		branch_stack__म_लिखो(sample, evsel__has_branch_callstack(evsel));

	अगर (sample_type & PERF_SAMPLE_REGS_USER)
		regs_user__म_लिखो(sample);

	अगर (sample_type & PERF_SAMPLE_REGS_INTR)
		regs_पूर्णांकr__म_लिखो(sample);

	अगर (sample_type & PERF_SAMPLE_STACK_USER)
		stack_user__म_लिखो(&sample->user_stack);

	अगर (sample_type & PERF_SAMPLE_WEIGHT_TYPE) अणु
		म_लिखो("... weight: %" PRIu64 "", sample->weight);
			अगर (sample_type & PERF_SAMPLE_WEIGHT_STRUCT) अणु
				म_लिखो(",0x%"PRIx16"", sample->ins_lat);
				म_लिखो(",0x%"PRIx16"", sample->p_stage_cyc);
			पूर्ण
		म_लिखो("\n");
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_DATA_SRC)
		म_लिखो(" . data_src: 0x%"PRIx64"\n", sample->data_src);

	अगर (sample_type & PERF_SAMPLE_PHYS_ADDR)
		म_लिखो(" .. phys_addr: 0x%"PRIx64"\n", sample->phys_addr);

	अगर (sample_type & PERF_SAMPLE_DATA_PAGE_SIZE)
		म_लिखो(" .. data page size: %s\n", get_page_size_name(sample->data_page_size, str));

	अगर (sample_type & PERF_SAMPLE_CODE_PAGE_SIZE)
		म_लिखो(" .. code page size: %s\n", get_page_size_name(sample->code_page_size, str));

	अगर (sample_type & PERF_SAMPLE_TRANSACTION)
		म_लिखो("... transaction: %" PRIx64 "\n", sample->transaction);

	अगर (sample_type & PERF_SAMPLE_READ)
		sample_पढ़ो__म_लिखो(sample, evsel->core.attr.पढ़ो_क्रमmat);
पूर्ण

अटल व्योम dump_पढ़ो(काष्ठा evsel *evsel, जोड़ perf_event *event)
अणु
	काष्ठा perf_record_पढ़ो *पढ़ो_event = &event->पढ़ो;
	u64 पढ़ो_क्रमmat;

	अगर (!dump_trace)
		वापस;

	म_लिखो(": %d %d %s %" PRI_lu64 "\n", event->पढ़ो.pid, event->पढ़ो.tid,
	       evsel__name(evsel), event->पढ़ो.value);

	अगर (!evsel)
		वापस;

	पढ़ो_क्रमmat = evsel->core.attr.पढ़ो_क्रमmat;

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED)
		म_लिखो("... time enabled : %" PRI_lu64 "\n", पढ़ो_event->समय_enabled);

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING)
		म_लिखो("... time running : %" PRI_lu64 "\n", पढ़ो_event->समय_running);

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_ID)
		म_लिखो("... id           : %" PRI_lu64 "\n", पढ़ो_event->id);
पूर्ण

अटल काष्ठा machine *machines__find_क्रम_cpumode(काष्ठा machines *machines,
					       जोड़ perf_event *event,
					       काष्ठा perf_sample *sample)
अणु
	अगर (perf_guest &&
	    ((sample->cpumode == PERF_RECORD_MISC_GUEST_KERNEL) ||
	     (sample->cpumode == PERF_RECORD_MISC_GUEST_USER))) अणु
		u32 pid;

		अगर (event->header.type == PERF_RECORD_MMAP
		    || event->header.type == PERF_RECORD_MMAP2)
			pid = event->mmap.pid;
		अन्यथा
			pid = sample->pid;

		वापस machines__find_guest(machines, pid);
	पूर्ण

	वापस &machines->host;
पूर्ण

अटल पूर्णांक deliver_sample_value(काष्ठा evlist *evlist,
				काष्ठा perf_tool *tool,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा sample_पढ़ो_value *v,
				काष्ठा machine *machine)
अणु
	काष्ठा perf_sample_id *sid = evlist__id2sid(evlist, v->id);
	काष्ठा evsel *evsel;

	अगर (sid) अणु
		sample->id     = v->id;
		sample->period = v->value - sid->period;
		sid->period    = v->value;
	पूर्ण

	अगर (!sid || sid->evsel == शून्य) अणु
		++evlist->stats.nr_unknown_id;
		वापस 0;
	पूर्ण

	/*
	 * There's no reason to deliver sample
	 * क्रम zero period, bail out.
	 */
	अगर (!sample->period)
		वापस 0;

	evsel = container_of(sid->evsel, काष्ठा evsel, core);
	वापस tool->sample(tool, event, sample, evsel, machine);
पूर्ण

अटल पूर्णांक deliver_sample_group(काष्ठा evlist *evlist,
				काष्ठा perf_tool *tool,
				जोड़  perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा machine *machine)
अणु
	पूर्णांक ret = -EINVAL;
	u64 i;

	क्रम (i = 0; i < sample->पढ़ो.group.nr; i++) अणु
		ret = deliver_sample_value(evlist, tool, event, sample,
					   &sample->पढ़ो.group.values[i],
					   machine);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक evlist__deliver_sample(काष्ठा evlist *evlist, काष्ठा perf_tool *tool,
				  जोड़  perf_event *event, काष्ठा perf_sample *sample,
				  काष्ठा evsel *evsel, काष्ठा machine *machine)
अणु
	/* We know evsel != शून्य. */
	u64 sample_type = evsel->core.attr.sample_type;
	u64 पढ़ो_क्रमmat = evsel->core.attr.पढ़ो_क्रमmat;

	/* Standard sample delivery. */
	अगर (!(sample_type & PERF_SAMPLE_READ))
		वापस tool->sample(tool, event, sample, evsel, machine);

	/* For PERF_SAMPLE_READ we have either single or group mode. */
	अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP)
		वापस deliver_sample_group(evlist, tool, event, sample,
					    machine);
	अन्यथा
		वापस deliver_sample_value(evlist, tool, event, sample,
					    &sample->पढ़ो.one, machine);
पूर्ण

अटल पूर्णांक machines__deliver_event(काष्ठा machines *machines,
				   काष्ठा evlist *evlist,
				   जोड़ perf_event *event,
				   काष्ठा perf_sample *sample,
				   काष्ठा perf_tool *tool, u64 file_offset)
अणु
	काष्ठा evsel *evsel;
	काष्ठा machine *machine;

	dump_event(evlist, event, file_offset, sample);

	evsel = evlist__id2evsel(evlist, sample->id);

	machine = machines__find_क्रम_cpumode(machines, event, sample);

	चयन (event->header.type) अणु
	हाल PERF_RECORD_SAMPLE:
		अगर (evsel == शून्य) अणु
			++evlist->stats.nr_unknown_id;
			वापस 0;
		पूर्ण
		dump_sample(evsel, event, sample);
		अगर (machine == शून्य) अणु
			++evlist->stats.nr_unprocessable_samples;
			वापस 0;
		पूर्ण
		वापस evlist__deliver_sample(evlist, tool, event, sample, evsel, machine);
	हाल PERF_RECORD_MMAP:
		वापस tool->mmap(tool, event, sample, machine);
	हाल PERF_RECORD_MMAP2:
		अगर (event->header.misc & PERF_RECORD_MISC_PROC_MAP_PARSE_TIMEOUT)
			++evlist->stats.nr_proc_map_समयout;
		वापस tool->mmap2(tool, event, sample, machine);
	हाल PERF_RECORD_COMM:
		वापस tool->comm(tool, event, sample, machine);
	हाल PERF_RECORD_NAMESPACES:
		वापस tool->namespaces(tool, event, sample, machine);
	हाल PERF_RECORD_CGROUP:
		वापस tool->cgroup(tool, event, sample, machine);
	हाल PERF_RECORD_FORK:
		वापस tool->विभाजन(tool, event, sample, machine);
	हाल PERF_RECORD_EXIT:
		वापस tool->निकास(tool, event, sample, machine);
	हाल PERF_RECORD_LOST:
		अगर (tool->lost == perf_event__process_lost)
			evlist->stats.total_lost += event->lost.lost;
		वापस tool->lost(tool, event, sample, machine);
	हाल PERF_RECORD_LOST_SAMPLES:
		अगर (tool->lost_samples == perf_event__process_lost_samples)
			evlist->stats.total_lost_samples += event->lost_samples.lost;
		वापस tool->lost_samples(tool, event, sample, machine);
	हाल PERF_RECORD_READ:
		dump_पढ़ो(evsel, event);
		वापस tool->पढ़ो(tool, event, sample, evsel, machine);
	हाल PERF_RECORD_THROTTLE:
		वापस tool->throttle(tool, event, sample, machine);
	हाल PERF_RECORD_UNTHROTTLE:
		वापस tool->unthrottle(tool, event, sample, machine);
	हाल PERF_RECORD_AUX:
		अगर (tool->aux == perf_event__process_aux) अणु
			अगर (event->aux.flags & PERF_AUX_FLAG_TRUNCATED)
				evlist->stats.total_aux_lost += 1;
			अगर (event->aux.flags & PERF_AUX_FLAG_PARTIAL)
				evlist->stats.total_aux_partial += 1;
		पूर्ण
		वापस tool->aux(tool, event, sample, machine);
	हाल PERF_RECORD_ITRACE_START:
		वापस tool->itrace_start(tool, event, sample, machine);
	हाल PERF_RECORD_SWITCH:
	हाल PERF_RECORD_SWITCH_CPU_WIDE:
		वापस tool->context_चयन(tool, event, sample, machine);
	हाल PERF_RECORD_KSYMBOL:
		वापस tool->ksymbol(tool, event, sample, machine);
	हाल PERF_RECORD_BPF_EVENT:
		वापस tool->bpf(tool, event, sample, machine);
	हाल PERF_RECORD_TEXT_POKE:
		वापस tool->text_poke(tool, event, sample, machine);
	शेष:
		++evlist->stats.nr_unknown_events;
		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक perf_session__deliver_event(काष्ठा perf_session *session,
				       जोड़ perf_event *event,
				       काष्ठा perf_tool *tool,
				       u64 file_offset)
अणु
	काष्ठा perf_sample sample;
	पूर्णांक ret = evlist__parse_sample(session->evlist, event, &sample);

	अगर (ret) अणु
		pr_err("Can't parse sample, err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = auxtrace__process_event(session, event, &sample, tool);
	अगर (ret < 0)
		वापस ret;
	अगर (ret > 0)
		वापस 0;

	ret = machines__deliver_event(&session->machines, session->evlist,
				      event, &sample, tool, file_offset);

	अगर (dump_trace && sample.aux_sample.size)
		auxtrace__dump_auxtrace_sample(session, &sample);

	वापस ret;
पूर्ण

अटल s64 perf_session__process_user_event(काष्ठा perf_session *session,
					    जोड़ perf_event *event,
					    u64 file_offset)
अणु
	काष्ठा ordered_events *oe = &session->ordered_events;
	काष्ठा perf_tool *tool = session->tool;
	काष्ठा perf_sample sample = अणु .समय = 0, पूर्ण;
	पूर्णांक fd = perf_data__fd(session->data);
	पूर्णांक err;

	अगर (event->header.type != PERF_RECORD_COMPRESSED ||
	    tool->compressed == perf_session__process_compressed_event_stub)
		dump_event(session->evlist, event, file_offset, &sample);

	/* These events are processed right away */
	चयन (event->header.type) अणु
	हाल PERF_RECORD_HEADER_ATTR:
		err = tool->attr(tool, event, &session->evlist);
		अगर (err == 0) अणु
			perf_session__set_id_hdr_size(session);
			perf_session__set_comm_exec(session);
		पूर्ण
		वापस err;
	हाल PERF_RECORD_EVENT_UPDATE:
		वापस tool->event_update(tool, event, &session->evlist);
	हाल PERF_RECORD_HEADER_EVENT_TYPE:
		/*
		 * Deprecated, but we need to handle it क्रम sake
		 * of old data files create in pipe mode.
		 */
		वापस 0;
	हाल PERF_RECORD_HEADER_TRACING_DATA:
		/*
		 * Setup क्रम पढ़ोing amidst mmap, but only when we
		 * are in 'file' mode. The 'pipe' fd is in proper
		 * place alपढ़ोy.
		 */
		अगर (!perf_data__is_pipe(session->data))
			lseek(fd, file_offset, शुरू_से);
		वापस tool->tracing_data(session, event);
	हाल PERF_RECORD_HEADER_BUILD_ID:
		वापस tool->build_id(session, event);
	हाल PERF_RECORD_FINISHED_ROUND:
		वापस tool->finished_round(tool, event, oe);
	हाल PERF_RECORD_ID_INDEX:
		वापस tool->id_index(session, event);
	हाल PERF_RECORD_AUXTRACE_INFO:
		वापस tool->auxtrace_info(session, event);
	हाल PERF_RECORD_AUXTRACE:
		/* setup क्रम पढ़ोing amidst mmap */
		lseek(fd, file_offset + event->header.size, शुरू_से);
		वापस tool->auxtrace(session, event);
	हाल PERF_RECORD_AUXTRACE_ERROR:
		perf_session__auxtrace_error_inc(session, event);
		वापस tool->auxtrace_error(session, event);
	हाल PERF_RECORD_THREAD_MAP:
		वापस tool->thपढ़ो_map(session, event);
	हाल PERF_RECORD_CPU_MAP:
		वापस tool->cpu_map(session, event);
	हाल PERF_RECORD_STAT_CONFIG:
		वापस tool->stat_config(session, event);
	हाल PERF_RECORD_STAT:
		वापस tool->stat(session, event);
	हाल PERF_RECORD_STAT_ROUND:
		वापस tool->stat_round(session, event);
	हाल PERF_RECORD_TIME_CONV:
		session->समय_conv = event->समय_conv;
		वापस tool->समय_conv(session, event);
	हाल PERF_RECORD_HEADER_FEATURE:
		वापस tool->feature(session, event);
	हाल PERF_RECORD_COMPRESSED:
		err = tool->compressed(session, event, file_offset);
		अगर (err)
			dump_event(session->evlist, event, file_offset, &sample);
		वापस err;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक perf_session__deliver_synth_event(काष्ठा perf_session *session,
				      जोड़ perf_event *event,
				      काष्ठा perf_sample *sample)
अणु
	काष्ठा evlist *evlist = session->evlist;
	काष्ठा perf_tool *tool = session->tool;

	events_stats__inc(&evlist->stats, event->header.type);

	अगर (event->header.type >= PERF_RECORD_USER_TYPE_START)
		वापस perf_session__process_user_event(session, event, 0);

	वापस machines__deliver_event(&session->machines, evlist, event, sample, tool, 0);
पूर्ण

अटल व्योम event_swap(जोड़ perf_event *event, bool sample_id_all)
अणु
	perf_event__swap_op swap;

	swap = perf_event__swap_ops[event->header.type];
	अगर (swap)
		swap(event, sample_id_all);
पूर्ण

पूर्णांक perf_session__peek_event(काष्ठा perf_session *session, off_t file_offset,
			     व्योम *buf, माप_प्रकार buf_sz,
			     जोड़ perf_event **event_ptr,
			     काष्ठा perf_sample *sample)
अणु
	जोड़ perf_event *event;
	माप_प्रकार hdr_sz, rest;
	पूर्णांक fd;

	अगर (session->one_mmap && !session->header.needs_swap) अणु
		event = file_offset - session->one_mmap_offset +
			session->one_mmap_addr;
		जाओ out_parse_sample;
	पूर्ण

	अगर (perf_data__is_pipe(session->data))
		वापस -1;

	fd = perf_data__fd(session->data);
	hdr_sz = माप(काष्ठा perf_event_header);

	अगर (buf_sz < hdr_sz)
		वापस -1;

	अगर (lseek(fd, file_offset, शुरू_से) == (off_t)-1 ||
	    पढ़ोn(fd, buf, hdr_sz) != (sमाप_प्रकार)hdr_sz)
		वापस -1;

	event = (जोड़ perf_event *)buf;

	अगर (session->header.needs_swap)
		perf_event_header__bswap(&event->header);

	अगर (event->header.size < hdr_sz || event->header.size > buf_sz)
		वापस -1;

	buf += hdr_sz;
	rest = event->header.size - hdr_sz;

	अगर (पढ़ोn(fd, buf, rest) != (sमाप_प्रकार)rest)
		वापस -1;

	अगर (session->header.needs_swap)
		event_swap(event, evlist__sample_id_all(session->evlist));

out_parse_sample:

	अगर (sample && event->header.type < PERF_RECORD_USER_TYPE_START &&
	    evlist__parse_sample(session->evlist, event, sample))
		वापस -1;

	*event_ptr = event;

	वापस 0;
पूर्ण

पूर्णांक perf_session__peek_events(काष्ठा perf_session *session, u64 offset,
			      u64 size, peek_events_cb_t cb, व्योम *data)
अणु
	u64 max_offset = offset + size;
	अक्षर buf[PERF_SAMPLE_MAX_SIZE];
	जोड़ perf_event *event;
	पूर्णांक err;

	करो अणु
		err = perf_session__peek_event(session, offset, buf,
					       PERF_SAMPLE_MAX_SIZE, &event,
					       शून्य);
		अगर (err)
			वापस err;

		err = cb(session, event, offset, data);
		अगर (err)
			वापस err;

		offset += event->header.size;
		अगर (event->header.type == PERF_RECORD_AUXTRACE)
			offset += event->auxtrace.size;

	पूर्ण जबतक (offset < max_offset);

	वापस err;
पूर्ण

अटल s64 perf_session__process_event(काष्ठा perf_session *session,
				       जोड़ perf_event *event, u64 file_offset)
अणु
	काष्ठा evlist *evlist = session->evlist;
	काष्ठा perf_tool *tool = session->tool;
	पूर्णांक ret;

	अगर (session->header.needs_swap)
		event_swap(event, evlist__sample_id_all(evlist));

	अगर (event->header.type >= PERF_RECORD_HEADER_MAX)
		वापस -EINVAL;

	events_stats__inc(&evlist->stats, event->header.type);

	अगर (event->header.type >= PERF_RECORD_USER_TYPE_START)
		वापस perf_session__process_user_event(session, event, file_offset);

	अगर (tool->ordered_events) अणु
		u64 बारtamp = -1ULL;

		ret = evlist__parse_sample_बारtamp(evlist, event, &बारtamp);
		अगर (ret && ret != -1)
			वापस ret;

		ret = perf_session__queue_event(session, event, बारtamp, file_offset);
		अगर (ret != -ETIME)
			वापस ret;
	पूर्ण

	वापस perf_session__deliver_event(session, event, tool, file_offset);
पूर्ण

व्योम perf_event_header__bswap(काष्ठा perf_event_header *hdr)
अणु
	hdr->type = bswap_32(hdr->type);
	hdr->misc = bswap_16(hdr->misc);
	hdr->size = bswap_16(hdr->size);
पूर्ण

काष्ठा thपढ़ो *perf_session__findnew(काष्ठा perf_session *session, pid_t pid)
अणु
	वापस machine__findnew_thपढ़ो(&session->machines.host, -1, pid);
पूर्ण

पूर्णांक perf_session__रेजिस्टर_idle_thपढ़ो(काष्ठा perf_session *session)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__idle_thपढ़ो(&session->machines.host);

	/* machine__idle_thपढ़ो() got the thपढ़ो, so put it */
	thपढ़ो__put(thपढ़ो);
	वापस thपढ़ो ? 0 : -1;
पूर्ण

अटल व्योम
perf_session__warn_order(स्थिर काष्ठा perf_session *session)
अणु
	स्थिर काष्ठा ordered_events *oe = &session->ordered_events;
	काष्ठा evsel *evsel;
	bool should_warn = true;

	evlist__क्रम_each_entry(session->evlist, evsel) अणु
		अगर (evsel->core.attr.ग_लिखो_backward)
			should_warn = false;
	पूर्ण

	अगर (!should_warn)
		वापस;
	अगर (oe->nr_unordered_events != 0)
		ui__warning("%u out of order events recorded.\n", oe->nr_unordered_events);
पूर्ण

अटल व्योम perf_session__warn_about_errors(स्थिर काष्ठा perf_session *session)
अणु
	स्थिर काष्ठा events_stats *stats = &session->evlist->stats;

	अगर (session->tool->lost == perf_event__process_lost &&
	    stats->nr_events[PERF_RECORD_LOST] != 0) अणु
		ui__warning("Processed %d events and lost %d chunks!\n\n"
			    "Check IO/CPU overload!\n\n",
			    stats->nr_events[0],
			    stats->nr_events[PERF_RECORD_LOST]);
	पूर्ण

	अगर (session->tool->lost_samples == perf_event__process_lost_samples) अणु
		द्विगुन drop_rate;

		drop_rate = (द्विगुन)stats->total_lost_samples /
			    (द्विगुन) (stats->nr_events[PERF_RECORD_SAMPLE] + stats->total_lost_samples);
		अगर (drop_rate > 0.05) अणु
			ui__warning("Processed %" PRIu64 " samples and lost %3.2f%%!\n\n",
				    stats->nr_events[PERF_RECORD_SAMPLE] + stats->total_lost_samples,
				    drop_rate * 100.0);
		पूर्ण
	पूर्ण

	अगर (session->tool->aux == perf_event__process_aux &&
	    stats->total_aux_lost != 0) अणु
		ui__warning("AUX data lost %" PRIu64 " times out of %u!\n\n",
			    stats->total_aux_lost,
			    stats->nr_events[PERF_RECORD_AUX]);
	पूर्ण

	अगर (session->tool->aux == perf_event__process_aux &&
	    stats->total_aux_partial != 0) अणु
		bool vmm_exclusive = false;

		(व्योम)sysfs__पढ़ो_bool("module/kvm_intel/parameters/vmm_exclusive",
		                       &vmm_exclusive);

		ui__warning("AUX data had gaps in it %" PRIu64 " times out of %u!\n\n"
		            "Are you running a KVM guest in the background?%s\n\n",
			    stats->total_aux_partial,
			    stats->nr_events[PERF_RECORD_AUX],
			    vmm_exclusive ?
			    "\nReloading kvm_intel module with vmm_exclusive=0\n"
			    "will reduce the gaps to only guest's timeslices." :
			    "");
	पूर्ण

	अगर (stats->nr_unknown_events != 0) अणु
		ui__warning("Found %u unknown events!\n\n"
			    "Is this an older tool processing a perf.data "
			    "file generated by a more recent tool?\n\n"
			    "If that is not the case, consider "
			    "reporting to linux-kernel@vger.kernel.org.\n\n",
			    stats->nr_unknown_events);
	पूर्ण

	अगर (stats->nr_unknown_id != 0) अणु
		ui__warning("%u samples with id not present in the header\n",
			    stats->nr_unknown_id);
	पूर्ण

	अगर (stats->nr_invalid_chains != 0) अणु
		ui__warning("Found invalid callchains!\n\n"
			    "%u out of %u events were discarded for this reason.\n\n"
			    "Consider reporting to linux-kernel@vger.kernel.org.\n\n",
			    stats->nr_invalid_chains,
			    stats->nr_events[PERF_RECORD_SAMPLE]);
	पूर्ण

	अगर (stats->nr_unprocessable_samples != 0) अणु
		ui__warning("%u unprocessable samples recorded.\n"
			    "Do you have a KVM guest running and not using 'perf kvm'?\n",
			    stats->nr_unprocessable_samples);
	पूर्ण

	perf_session__warn_order(session);

	events_stats__auxtrace_error_warn(stats);

	अगर (stats->nr_proc_map_समयout != 0) अणु
		ui__warning("%d map information files for pre-existing threads were\n"
			    "not processed, if there are samples for addresses they\n"
			    "will not be resolved, you may find out which are these\n"
			    "threads by running with -v and redirecting the output\n"
			    "to a file.\n"
			    "The time limit to process proc map is too short?\n"
			    "Increase it by --proc-map-timeout\n",
			    stats->nr_proc_map_समयout);
	पूर्ण
पूर्ण

अटल पूर्णांक perf_session__flush_thपढ़ो_stack(काष्ठा thपढ़ो *thपढ़ो,
					    व्योम *p __maybe_unused)
अणु
	वापस thपढ़ो_stack__flush(thपढ़ो);
पूर्ण

अटल पूर्णांक perf_session__flush_thपढ़ो_stacks(काष्ठा perf_session *session)
अणु
	वापस machines__क्रम_each_thपढ़ो(&session->machines,
					 perf_session__flush_thपढ़ो_stack,
					 शून्य);
पूर्ण

अस्थिर पूर्णांक session_करोne;

अटल पूर्णांक __perf_session__process_decomp_events(काष्ठा perf_session *session);

अटल पूर्णांक __perf_session__process_pipe_events(काष्ठा perf_session *session)
अणु
	काष्ठा ordered_events *oe = &session->ordered_events;
	काष्ठा perf_tool *tool = session->tool;
	जोड़ perf_event *event;
	uपूर्णांक32_t size, cur_size = 0;
	व्योम *buf = शून्य;
	s64 skip = 0;
	u64 head;
	sमाप_प्रकार err;
	व्योम *p;

	perf_tool__fill_शेषs(tool);

	head = 0;
	cur_size = माप(जोड़ perf_event);

	buf = दो_स्मृति(cur_size);
	अगर (!buf)
		वापस -त्रुटि_सं;
	ordered_events__set_copy_on_queue(oe, true);
more:
	event = buf;
	err = perf_data__पढ़ो(session->data, event,
			      माप(काष्ठा perf_event_header));
	अगर (err <= 0) अणु
		अगर (err == 0)
			जाओ करोne;

		pr_err("failed to read event header\n");
		जाओ out_err;
	पूर्ण

	अगर (session->header.needs_swap)
		perf_event_header__bswap(&event->header);

	size = event->header.size;
	अगर (size < माप(काष्ठा perf_event_header)) अणु
		pr_err("bad event header size\n");
		जाओ out_err;
	पूर्ण

	अगर (size > cur_size) अणु
		व्योम *new = पुनः_स्मृति(buf, size);
		अगर (!new) अणु
			pr_err("failed to allocate memory to read event\n");
			जाओ out_err;
		पूर्ण
		buf = new;
		cur_size = size;
		event = buf;
	पूर्ण
	p = event;
	p += माप(काष्ठा perf_event_header);

	अगर (size - माप(काष्ठा perf_event_header)) अणु
		err = perf_data__पढ़ो(session->data, p,
				      size - माप(काष्ठा perf_event_header));
		अगर (err <= 0) अणु
			अगर (err == 0) अणु
				pr_err("unexpected end of event stream\n");
				जाओ करोne;
			पूर्ण

			pr_err("failed to read event data\n");
			जाओ out_err;
		पूर्ण
	पूर्ण

	अगर ((skip = perf_session__process_event(session, event, head)) < 0) अणु
		pr_err("%#" PRIx64 " [%#x]: failed to process type: %d\n",
		       head, event->header.size, event->header.type);
		err = -EINVAL;
		जाओ out_err;
	पूर्ण

	head += size;

	अगर (skip > 0)
		head += skip;

	err = __perf_session__process_decomp_events(session);
	अगर (err)
		जाओ out_err;

	अगर (!session_करोne())
		जाओ more;
करोne:
	/* करो the final flush क्रम ordered samples */
	err = ordered_events__flush(oe, OE_FLUSH__FINAL);
	अगर (err)
		जाओ out_err;
	err = auxtrace__flush_events(session, tool);
	अगर (err)
		जाओ out_err;
	err = perf_session__flush_thपढ़ो_stacks(session);
out_err:
	मुक्त(buf);
	अगर (!tool->no_warn)
		perf_session__warn_about_errors(session);
	ordered_events__मुक्त(&session->ordered_events);
	auxtrace__मुक्त_events(session);
	वापस err;
पूर्ण

अटल जोड़ perf_event *
prefetch_event(अक्षर *buf, u64 head, माप_प्रकार mmap_size,
	       bool needs_swap, जोड़ perf_event *error)
अणु
	जोड़ perf_event *event;

	/*
	 * Ensure we have enough space reमुख्यing to पढ़ो
	 * the size of the event in the headers.
	 */
	अगर (head + माप(event->header) > mmap_size)
		वापस शून्य;

	event = (जोड़ perf_event *)(buf + head);
	अगर (needs_swap)
		perf_event_header__bswap(&event->header);

	अगर (head + event->header.size <= mmap_size)
		वापस event;

	/* We're not fetching the event so swap back again */
	अगर (needs_swap)
		perf_event_header__bswap(&event->header);

	pr_debug("%s: head=%#" PRIx64 " event->header_size=%#x, mmap_size=%#zx:"
		 " fuzzed or compressed perf.data?\n",__func__, head, event->header.size, mmap_size);

	वापस error;
पूर्ण

अटल जोड़ perf_event *
fetch_mmaped_event(u64 head, माप_प्रकार mmap_size, अक्षर *buf, bool needs_swap)
अणु
	वापस prefetch_event(buf, head, mmap_size, needs_swap, ERR_PTR(-EINVAL));
पूर्ण

अटल जोड़ perf_event *
fetch_decomp_event(u64 head, माप_प्रकार mmap_size, अक्षर *buf, bool needs_swap)
अणु
	वापस prefetch_event(buf, head, mmap_size, needs_swap, शून्य);
पूर्ण

अटल पूर्णांक __perf_session__process_decomp_events(काष्ठा perf_session *session)
अणु
	s64 skip;
	u64 size, file_pos = 0;
	काष्ठा decomp *decomp = session->decomp_last;

	अगर (!decomp)
		वापस 0;

	जबतक (decomp->head < decomp->size && !session_करोne()) अणु
		जोड़ perf_event *event = fetch_decomp_event(decomp->head, decomp->size, decomp->data,
							     session->header.needs_swap);

		अगर (!event)
			अवरोध;

		size = event->header.size;

		अगर (size < माप(काष्ठा perf_event_header) ||
		    (skip = perf_session__process_event(session, event, file_pos)) < 0) अणु
			pr_err("%#" PRIx64 " [%#x]: failed to process type: %d\n",
				decomp->file_pos + decomp->head, event->header.size, event->header.type);
			वापस -EINVAL;
		पूर्ण

		अगर (skip)
			size += skip;

		decomp->head += size;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * On 64bit we can mmap the data file in one go. No need क्रम tiny mmap
 * slices. On 32bit we use 32MB.
 */
#अगर BITS_PER_LONG == 64
#घोषणा MMAP_SIZE ULदीर्घ_उच्च
#घोषणा NUM_MMAPS 1
#अन्यथा
#घोषणा MMAP_SIZE (32 * 1024 * 1024ULL)
#घोषणा NUM_MMAPS 128
#पूर्ण_अगर

काष्ठा पढ़ोer;

प्रकार s64 (*पढ़ोer_cb_t)(काष्ठा perf_session *session,
			   जोड़ perf_event *event,
			   u64 file_offset);

काष्ठा पढ़ोer अणु
	पूर्णांक		 fd;
	u64		 data_size;
	u64		 data_offset;
	पढ़ोer_cb_t	 process;
पूर्ण;

अटल पूर्णांक
पढ़ोer__process_events(काष्ठा पढ़ोer *rd, काष्ठा perf_session *session,
		       काष्ठा ui_progress *prog)
अणु
	u64 data_size = rd->data_size;
	u64 head, page_offset, file_offset, file_pos, size;
	पूर्णांक err = 0, mmap_prot, mmap_flags, map_idx = 0;
	माप_प्रकार	mmap_size;
	अक्षर *buf, *mmaps[NUM_MMAPS];
	जोड़ perf_event *event;
	s64 skip;

	page_offset = page_size * (rd->data_offset / page_size);
	file_offset = page_offset;
	head = rd->data_offset - page_offset;

	ui_progress__init_size(prog, data_size, "Processing events...");

	data_size += rd->data_offset;

	mmap_size = MMAP_SIZE;
	अगर (mmap_size > data_size) अणु
		mmap_size = data_size;
		session->one_mmap = true;
	पूर्ण

	स_रखो(mmaps, 0, माप(mmaps));

	mmap_prot  = PROT_READ;
	mmap_flags = MAP_SHARED;

	अगर (session->header.needs_swap) अणु
		mmap_prot  |= PROT_WRITE;
		mmap_flags = MAP_PRIVATE;
	पूर्ण
remap:
	buf = mmap(शून्य, mmap_size, mmap_prot, mmap_flags, rd->fd,
		   file_offset);
	अगर (buf == MAP_FAILED) अणु
		pr_err("failed to mmap file\n");
		err = -त्रुटि_सं;
		जाओ out;
	पूर्ण
	mmaps[map_idx] = buf;
	map_idx = (map_idx + 1) & (ARRAY_SIZE(mmaps) - 1);
	file_pos = file_offset + head;
	अगर (session->one_mmap) अणु
		session->one_mmap_addr = buf;
		session->one_mmap_offset = file_offset;
	पूर्ण

more:
	event = fetch_mmaped_event(head, mmap_size, buf, session->header.needs_swap);
	अगर (IS_ERR(event))
		वापस PTR_ERR(event);

	अगर (!event) अणु
		अगर (mmaps[map_idx]) अणु
			munmap(mmaps[map_idx], mmap_size);
			mmaps[map_idx] = शून्य;
		पूर्ण

		page_offset = page_size * (head / page_size);
		file_offset += page_offset;
		head -= page_offset;
		जाओ remap;
	पूर्ण

	size = event->header.size;

	skip = -EINVAL;

	अगर (size < माप(काष्ठा perf_event_header) ||
	    (skip = rd->process(session, event, file_pos)) < 0) अणु
		pr_err("%#" PRIx64 " [%#x]: failed to process type: %d [%s]\n",
		       file_offset + head, event->header.size,
		       event->header.type, म_त्रुटि(-skip));
		err = skip;
		जाओ out;
	पूर्ण

	अगर (skip)
		size += skip;

	head += size;
	file_pos += size;

	err = __perf_session__process_decomp_events(session);
	अगर (err)
		जाओ out;

	ui_progress__update(prog, size);

	अगर (session_करोne())
		जाओ out;

	अगर (file_pos < data_size)
		जाओ more;

out:
	वापस err;
पूर्ण

अटल s64 process_simple(काष्ठा perf_session *session,
			  जोड़ perf_event *event,
			  u64 file_offset)
अणु
	वापस perf_session__process_event(session, event, file_offset);
पूर्ण

अटल पूर्णांक __perf_session__process_events(काष्ठा perf_session *session)
अणु
	काष्ठा पढ़ोer rd = अणु
		.fd		= perf_data__fd(session->data),
		.data_size	= session->header.data_size,
		.data_offset	= session->header.data_offset,
		.process	= process_simple,
	पूर्ण;
	काष्ठा ordered_events *oe = &session->ordered_events;
	काष्ठा perf_tool *tool = session->tool;
	काष्ठा ui_progress prog;
	पूर्णांक err;

	perf_tool__fill_शेषs(tool);

	अगर (rd.data_size == 0)
		वापस -1;

	ui_progress__init_size(&prog, rd.data_size, "Processing events...");

	err = पढ़ोer__process_events(&rd, session, &prog);
	अगर (err)
		जाओ out_err;
	/* करो the final flush क्रम ordered samples */
	err = ordered_events__flush(oe, OE_FLUSH__FINAL);
	अगर (err)
		जाओ out_err;
	err = auxtrace__flush_events(session, tool);
	अगर (err)
		जाओ out_err;
	err = perf_session__flush_thपढ़ो_stacks(session);
out_err:
	ui_progress__finish();
	अगर (!tool->no_warn)
		perf_session__warn_about_errors(session);
	/*
	 * We may चयनing perf.data output, make ordered_events
	 * reusable.
	 */
	ordered_events__reinit(&session->ordered_events);
	auxtrace__मुक्त_events(session);
	session->one_mmap = false;
	वापस err;
पूर्ण

पूर्णांक perf_session__process_events(काष्ठा perf_session *session)
अणु
	अगर (perf_session__रेजिस्टर_idle_thपढ़ो(session) < 0)
		वापस -ENOMEM;

	अगर (perf_data__is_pipe(session->data))
		वापस __perf_session__process_pipe_events(session);

	वापस __perf_session__process_events(session);
पूर्ण

bool perf_session__has_traces(काष्ठा perf_session *session, स्थिर अक्षर *msg)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(session->evlist, evsel) अणु
		अगर (evsel->core.attr.type == PERF_TYPE_TRACEPOINT)
			वापस true;
	पूर्ण

	pr_err("No trace sample to read. Did you call 'perf %s'?\n", msg);
	वापस false;
पूर्ण

पूर्णांक map__set_kallsyms_ref_reloc_sym(काष्ठा map *map, स्थिर अक्षर *symbol_name, u64 addr)
अणु
	अक्षर *bracket;
	काष्ठा ref_reloc_sym *ref;
	काष्ठा kmap *kmap;

	ref = zalloc(माप(काष्ठा ref_reloc_sym));
	अगर (ref == शून्य)
		वापस -ENOMEM;

	ref->name = strdup(symbol_name);
	अगर (ref->name == शून्य) अणु
		मुक्त(ref);
		वापस -ENOMEM;
	पूर्ण

	bracket = म_अक्षर(ref->name, ']');
	अगर (bracket)
		*bracket = '\0';

	ref->addr = addr;

	kmap = map__kmap(map);
	अगर (kmap)
		kmap->ref_reloc_sym = ref;

	वापस 0;
पूर्ण

माप_प्रकार perf_session__ख_लिखो_dsos(काष्ठा perf_session *session, खाता *fp)
अणु
	वापस machines__ख_लिखो_dsos(&session->machines, fp);
पूर्ण

माप_प्रकार perf_session__ख_लिखो_dsos_buildid(काष्ठा perf_session *session, खाता *fp,
					  bool (skip)(काष्ठा dso *dso, पूर्णांक parm), पूर्णांक parm)
अणु
	वापस machines__ख_लिखो_dsos_buildid(&session->machines, fp, skip, parm);
पूर्ण

माप_प्रकार perf_session__ख_लिखो_nr_events(काष्ठा perf_session *session, खाता *fp,
				       bool skip_empty)
अणु
	माप_प्रकार ret;
	स्थिर अक्षर *msg = "";

	अगर (perf_header__has_feat(&session->header, HEADER_AUXTRACE))
		msg = " (excludes AUX area (e.g. instruction trace) decoded / synthesized events)";

	ret = ख_लिखो(fp, "\nAggregated stats:%s\n", msg);

	ret += events_stats__ख_लिखो(&session->evlist->stats, fp, skip_empty);
	वापस ret;
पूर्ण

माप_प्रकार perf_session__ख_लिखो(काष्ठा perf_session *session, खाता *fp)
अणु
	/*
	 * FIXME: Here we have to actually prपूर्णांक all the machines in this
	 * session, not just the host...
	 */
	वापस machine__ख_लिखो(&session->machines.host, fp);
पूर्ण

काष्ठा evsel *perf_session__find_first_evtype(काष्ठा perf_session *session,
					      अचिन्हित पूर्णांक type)
अणु
	काष्ठा evsel *pos;

	evlist__क्रम_each_entry(session->evlist, pos) अणु
		अगर (pos->core.attr.type == type)
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक perf_session__cpu_biपंचांगap(काष्ठा perf_session *session,
			     स्थिर अक्षर *cpu_list, अचिन्हित दीर्घ *cpu_biपंचांगap)
अणु
	पूर्णांक i, err = -1;
	काष्ठा perf_cpu_map *map;
	पूर्णांक nr_cpus = min(session->header.env.nr_cpus_avail, MAX_NR_CPUS);

	क्रम (i = 0; i < PERF_TYPE_MAX; ++i) अणु
		काष्ठा evsel *evsel;

		evsel = perf_session__find_first_evtype(session, i);
		अगर (!evsel)
			जारी;

		अगर (!(evsel->core.attr.sample_type & PERF_SAMPLE_CPU)) अणु
			pr_err("File does not contain CPU events. "
			       "Remove -C option to proceed.\n");
			वापस -1;
		पूर्ण
	पूर्ण

	map = perf_cpu_map__new(cpu_list);
	अगर (map == शून्य) अणु
		pr_err("Invalid cpu_list\n");
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < map->nr; i++) अणु
		पूर्णांक cpu = map->map[i];

		अगर (cpu >= nr_cpus) अणु
			pr_err("Requested CPU %d too large. "
			       "Consider raising MAX_NR_CPUS\n", cpu);
			जाओ out_delete_map;
		पूर्ण

		set_bit(cpu, cpu_biपंचांगap);
	पूर्ण

	err = 0;

out_delete_map:
	perf_cpu_map__put(map);
	वापस err;
पूर्ण

व्योम perf_session__ख_लिखो_info(काष्ठा perf_session *session, खाता *fp,
				bool full)
अणु
	अगर (session == शून्य || fp == शून्य)
		वापस;

	ख_लिखो(fp, "# ========\n");
	perf_header__ख_लिखो_info(session, fp, full);
	ख_लिखो(fp, "# ========\n#\n");
पूर्ण

पूर्णांक perf_event__process_id_index(काष्ठा perf_session *session,
				 जोड़ perf_event *event)
अणु
	काष्ठा evlist *evlist = session->evlist;
	काष्ठा perf_record_id_index *ie = &event->id_index;
	माप_प्रकार i, nr, max_nr;

	max_nr = (ie->header.size - माप(काष्ठा perf_record_id_index)) /
		 माप(काष्ठा id_index_entry);
	nr = ie->nr;
	अगर (nr > max_nr)
		वापस -EINVAL;

	अगर (dump_trace)
		ख_लिखो(मानक_निकास, " nr: %zu\n", nr);

	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा id_index_entry *e = &ie->entries[i];
		काष्ठा perf_sample_id *sid;

		अगर (dump_trace) अणु
			ख_लिखो(मानक_निकास,	" ... id: %"PRI_lu64, e->id);
			ख_लिखो(मानक_निकास,	"  idx: %"PRI_lu64, e->idx);
			ख_लिखो(मानक_निकास,	"  cpu: %"PRI_ld64, e->cpu);
			ख_लिखो(मानक_निकास,	"  tid: %"PRI_ld64"\n", e->tid);
		पूर्ण

		sid = evlist__id2sid(evlist, e->id);
		अगर (!sid)
			वापस -ENOENT;
		sid->idx = e->idx;
		sid->cpu = e->cpu;
		sid->tid = e->tid;
	पूर्ण
	वापस 0;
पूर्ण
