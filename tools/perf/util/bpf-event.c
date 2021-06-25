<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <bpf/bpf.h>
#समावेश <bpf/btf.h>
#समावेश <bpf/libbpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <पूर्णांकernal/lib.h>
#समावेश <symbol/kallsyms.h>
#समावेश "bpf-event.h"
#समावेश "debug.h"
#समावेश "dso.h"
#समावेश "symbol.h"
#समावेश "machine.h"
#समावेश "env.h"
#समावेश "session.h"
#समावेश "map.h"
#समावेश "evlist.h"
#समावेश "record.h"
#समावेश "util/synthetic-events.h"

#घोषणा ptr_to_u64(ptr)    ((__u64)(अचिन्हित दीर्घ)(ptr))

अटल पूर्णांक snम_लिखो_hex(अक्षर *buf, माप_प्रकार size, अचिन्हित अक्षर *data, माप_प्रकार len)
अणु
	पूर्णांक ret = 0;
	माप_प्रकार i;

	क्रम (i = 0; i < len; i++)
		ret += snम_लिखो(buf + ret, size - ret, "%02x", data[i]);
	वापस ret;
पूर्ण

अटल पूर्णांक machine__process_bpf_event_load(काष्ठा machine *machine,
					   जोड़ perf_event *event,
					   काष्ठा perf_sample *sample __maybe_unused)
अणु
	काष्ठा bpf_prog_info_linear *info_linear;
	काष्ठा bpf_prog_info_node *info_node;
	काष्ठा perf_env *env = machine->env;
	पूर्णांक id = event->bpf.id;
	अचिन्हित पूर्णांक i;

	/* perf-record, no need to handle bpf-event */
	अगर (env == शून्य)
		वापस 0;

	info_node = perf_env__find_bpf_prog_info(env, id);
	अगर (!info_node)
		वापस 0;
	info_linear = info_node->info_linear;

	क्रम (i = 0; i < info_linear->info.nr_jited_ksyms; i++) अणु
		u64 *addrs = (u64 *)(uपूर्णांकptr_t)(info_linear->info.jited_ksyms);
		u64 addr = addrs[i];
		काष्ठा map *map = maps__find(&machine->kmaps, addr);

		अगर (map) अणु
			map->dso->binary_type = DSO_BINARY_TYPE__BPF_PROG_INFO;
			map->dso->bpf_prog.id = id;
			map->dso->bpf_prog.sub_id = i;
			map->dso->bpf_prog.env = env;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक machine__process_bpf(काष्ठा machine *machine, जोड़ perf_event *event,
			 काष्ठा perf_sample *sample)
अणु
	अगर (dump_trace)
		perf_event__ख_लिखो_bpf(event, मानक_निकास);

	चयन (event->bpf.type) अणु
	हाल PERF_BPF_EVENT_PROG_LOAD:
		वापस machine__process_bpf_event_load(machine, event, sample);

	हाल PERF_BPF_EVENT_PROG_UNLOAD:
		/*
		 * Do not मुक्त bpf_prog_info and btf of the program here,
		 * as annotation still need them. They will be मुक्तd at
		 * the end of the session.
		 */
		अवरोध;
	शेष:
		pr_debug("unexpected bpf event type of %d\n", event->bpf.type);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक perf_env__fetch_btf(काष्ठा perf_env *env,
			       u32 btf_id,
			       काष्ठा btf *btf)
अणु
	काष्ठा btf_node *node;
	u32 data_size;
	स्थिर व्योम *data;

	data = btf__get_raw_data(btf, &data_size);

	node = दो_स्मृति(data_size + माप(काष्ठा btf_node));
	अगर (!node)
		वापस -1;

	node->id = btf_id;
	node->data_size = data_size;
	स_नकल(node->data, data, data_size);

	perf_env__insert_btf(env, node);
	वापस 0;
पूर्ण

अटल पूर्णांक synthesize_bpf_prog_name(अक्षर *buf, पूर्णांक size,
				    काष्ठा bpf_prog_info *info,
				    काष्ठा btf *btf,
				    u32 sub_id)
अणु
	u8 (*prog_tags)[BPF_TAG_SIZE] = (व्योम *)(uपूर्णांकptr_t)(info->prog_tags);
	व्योम *func_infos = (व्योम *)(uपूर्णांकptr_t)(info->func_info);
	u32 sub_prog_cnt = info->nr_jited_ksyms;
	स्थिर काष्ठा bpf_func_info *finfo;
	स्थिर अक्षर *लघु_name = शून्य;
	स्थिर काष्ठा btf_type *t;
	पूर्णांक name_len;

	name_len = snम_लिखो(buf, size, "bpf_prog_");
	name_len += snम_लिखो_hex(buf + name_len, size - name_len,
				 prog_tags[sub_id], BPF_TAG_SIZE);
	अगर (btf) अणु
		finfo = func_infos + sub_id * info->func_info_rec_size;
		t = btf__type_by_id(btf, finfo->type_id);
		लघु_name = btf__name_by_offset(btf, t->name_off);
	पूर्ण अन्यथा अगर (sub_id == 0 && sub_prog_cnt == 1) अणु
		/* no subprog */
		अगर (info->name[0])
			लघु_name = info->name;
	पूर्ण अन्यथा
		लघु_name = "F";
	अगर (लघु_name)
		name_len += snम_लिखो(buf + name_len, size - name_len,
				     "_%s", लघु_name);
	वापस name_len;
पूर्ण

/*
 * Synthesize PERF_RECORD_KSYMBOL and PERF_RECORD_BPF_EVENT क्रम one bpf
 * program. One PERF_RECORD_BPF_EVENT is generated क्रम the program. And
 * one PERF_RECORD_KSYMBOL is generated क्रम each sub program.
 *
 * Returns:
 *    0 क्रम success;
 *   -1 क्रम failures;
 *   -2 क्रम lack of kernel support.
 */
अटल पूर्णांक perf_event__synthesize_one_bpf_prog(काष्ठा perf_session *session,
					       perf_event__handler_t process,
					       काष्ठा machine *machine,
					       पूर्णांक fd,
					       जोड़ perf_event *event,
					       काष्ठा record_opts *opts)
अणु
	काष्ठा perf_record_ksymbol *ksymbol_event = &event->ksymbol;
	काष्ठा perf_record_bpf_event *bpf_event = &event->bpf;
	काष्ठा bpf_prog_info_linear *info_linear;
	काष्ठा perf_tool *tool = session->tool;
	काष्ठा bpf_prog_info_node *info_node;
	काष्ठा bpf_prog_info *info;
	काष्ठा btf *btf = शून्य;
	काष्ठा perf_env *env;
	u32 sub_prog_cnt, i;
	पूर्णांक err = 0;
	u64 arrays;

	/*
	 * क्रम perf-record and perf-report use header.env;
	 * otherwise, use global perf_env.
	 */
	env = session->data ? &session->header.env : &perf_env;

	arrays = 1UL << BPF_PROG_INFO_JITED_KSYMS;
	arrays |= 1UL << BPF_PROG_INFO_JITED_FUNC_LENS;
	arrays |= 1UL << BPF_PROG_INFO_FUNC_INFO;
	arrays |= 1UL << BPF_PROG_INFO_PROG_TAGS;
	arrays |= 1UL << BPF_PROG_INFO_JITED_INSNS;
	arrays |= 1UL << BPF_PROG_INFO_LINE_INFO;
	arrays |= 1UL << BPF_PROG_INFO_JITED_LINE_INFO;

	info_linear = bpf_program__get_prog_info_linear(fd, arrays);
	अगर (IS_ERR_OR_शून्य(info_linear)) अणु
		info_linear = शून्य;
		pr_debug("%s: failed to get BPF program info. aborting\n", __func__);
		वापस -1;
	पूर्ण

	अगर (info_linear->info_len < दुरत्व(काष्ठा bpf_prog_info, prog_tags)) अणु
		मुक्त(info_linear);
		pr_debug("%s: the kernel is too old, aborting\n", __func__);
		वापस -2;
	पूर्ण

	info = &info_linear->info;
	अगर (!info->jited_ksyms) अणु
		मुक्त(info_linear);
		वापस -1;
	पूर्ण

	/* number of ksyms, func_lengths, and tags should match */
	sub_prog_cnt = info->nr_jited_ksyms;
	अगर (sub_prog_cnt != info->nr_prog_tags ||
	    sub_prog_cnt != info->nr_jited_func_lens) अणु
		मुक्त(info_linear);
		वापस -1;
	पूर्ण

	/* check BTF func info support */
	अगर (info->btf_id && info->nr_func_info && info->func_info_rec_size) अणु
		/* btf func info number should be same as sub_prog_cnt */
		अगर (sub_prog_cnt != info->nr_func_info) अणु
			pr_debug("%s: mismatch in BPF sub program count and BTF function info count, aborting\n", __func__);
			मुक्त(info_linear);
			वापस -1;
		पूर्ण
		अगर (btf__get_from_id(info->btf_id, &btf)) अणु
			pr_debug("%s: failed to get BTF of id %u, aborting\n", __func__, info->btf_id);
			err = -1;
			btf = शून्य;
			जाओ out;
		पूर्ण
		perf_env__fetch_btf(env, info->btf_id, btf);
	पूर्ण

	/* Synthesize PERF_RECORD_KSYMBOL */
	क्रम (i = 0; i < sub_prog_cnt; i++) अणु
		__u32 *prog_lens = (__u32 *)(uपूर्णांकptr_t)(info->jited_func_lens);
		__u64 *prog_addrs = (__u64 *)(uपूर्णांकptr_t)(info->jited_ksyms);
		पूर्णांक name_len;

		*ksymbol_event = (काष्ठा perf_record_ksymbol) अणु
			.header = अणु
				.type = PERF_RECORD_KSYMBOL,
				.size = दुरत्व(काष्ठा perf_record_ksymbol, name),
			पूर्ण,
			.addr = prog_addrs[i],
			.len = prog_lens[i],
			.ksym_type = PERF_RECORD_KSYMBOL_TYPE_BPF,
			.flags = 0,
		पूर्ण;

		name_len = synthesize_bpf_prog_name(ksymbol_event->name,
						    KSYM_NAME_LEN, info, btf, i);
		ksymbol_event->header.size += PERF_ALIGN(name_len + 1,
							 माप(u64));

		स_रखो((व्योम *)event + event->header.size, 0, machine->id_hdr_size);
		event->header.size += machine->id_hdr_size;
		err = perf_tool__process_synth_event(tool, event,
						     machine, process);
	पूर्ण

	अगर (!opts->no_bpf_event) अणु
		/* Synthesize PERF_RECORD_BPF_EVENT */
		*bpf_event = (काष्ठा perf_record_bpf_event) अणु
			.header = अणु
				.type = PERF_RECORD_BPF_EVENT,
				.size = माप(काष्ठा perf_record_bpf_event),
			पूर्ण,
			.type = PERF_BPF_EVENT_PROG_LOAD,
			.flags = 0,
			.id = info->id,
		पूर्ण;
		स_नकल(bpf_event->tag, info->tag, BPF_TAG_SIZE);
		स_रखो((व्योम *)event + event->header.size, 0, machine->id_hdr_size);
		event->header.size += machine->id_hdr_size;

		/* save bpf_prog_info to env */
		info_node = दो_स्मृति(माप(काष्ठा bpf_prog_info_node));
		अगर (!info_node) अणु
			err = -1;
			जाओ out;
		पूर्ण

		info_node->info_linear = info_linear;
		perf_env__insert_bpf_prog_info(env, info_node);
		info_linear = शून्य;

		/*
		 * process after saving bpf_prog_info to env, so that
		 * required inक्रमmation is पढ़ोy क्रम look up
		 */
		err = perf_tool__process_synth_event(tool, event,
						     machine, process);
	पूर्ण

out:
	मुक्त(info_linear);
	मुक्त(btf);
	वापस err ? -1 : 0;
पूर्ण

काष्ठा kallsyms_parse अणु
	जोड़ perf_event	*event;
	perf_event__handler_t	 process;
	काष्ठा machine		*machine;
	काष्ठा perf_tool	*tool;
पूर्ण;

अटल पूर्णांक
process_bpf_image(अक्षर *name, u64 addr, काष्ठा kallsyms_parse *data)
अणु
	काष्ठा machine *machine = data->machine;
	जोड़ perf_event *event = data->event;
	काष्ठा perf_record_ksymbol *ksymbol;
	पूर्णांक len;

	ksymbol = &event->ksymbol;

	*ksymbol = (काष्ठा perf_record_ksymbol) अणु
		.header = अणु
			.type = PERF_RECORD_KSYMBOL,
			.size = दुरत्व(काष्ठा perf_record_ksymbol, name),
		पूर्ण,
		.addr      = addr,
		.len       = page_size,
		.ksym_type = PERF_RECORD_KSYMBOL_TYPE_BPF,
		.flags     = 0,
	पूर्ण;

	len = scnम_लिखो(ksymbol->name, KSYM_NAME_LEN, "%s", name);
	ksymbol->header.size += PERF_ALIGN(len + 1, माप(u64));
	स_रखो((व्योम *) event + event->header.size, 0, machine->id_hdr_size);
	event->header.size += machine->id_hdr_size;

	वापस perf_tool__process_synth_event(data->tool, event, machine,
					      data->process);
पूर्ण

अटल पूर्णांक
kallsyms_process_symbol(व्योम *data, स्थिर अक्षर *_name,
			अक्षर type __maybe_unused, u64 start)
अणु
	अक्षर disp[KSYM_NAME_LEN];
	अक्षर *module, *name;
	अचिन्हित दीर्घ id;
	पूर्णांक err = 0;

	module = म_अक्षर(_name, '\t');
	अगर (!module)
		वापस 0;

	/* We are going after [bpf] module ... */
	अगर (म_भेद(module + 1, "[bpf]"))
		वापस 0;

	name = memdup(_name, (module - _name) + 1);
	अगर (!name)
		वापस -ENOMEM;

	name[module - _name] = 0;

	/* .. and only क्रम trampolines and dispatchers */
	अगर ((माला_पूछो(name, "bpf_trampoline_%lu", &id) == 1) ||
	    (माला_पूछो(name, "bpf_dispatcher_%s", disp) == 1))
		err = process_bpf_image(name, start, data);

	मुक्त(name);
	वापस err;
पूर्ण

पूर्णांक perf_event__synthesize_bpf_events(काष्ठा perf_session *session,
				      perf_event__handler_t process,
				      काष्ठा machine *machine,
				      काष्ठा record_opts *opts)
अणु
	स्थिर अक्षर *kallsyms_filename = "/proc/kallsyms";
	काष्ठा kallsyms_parse arg;
	जोड़ perf_event *event;
	__u32 id = 0;
	पूर्णांक err;
	पूर्णांक fd;

	event = दो_स्मृति(माप(event->bpf) + KSYM_NAME_LEN + machine->id_hdr_size);
	अगर (!event)
		वापस -1;

	/* Synthesize all the bpf programs in प्रणाली. */
	जबतक (true) अणु
		err = bpf_prog_get_next_id(id, &id);
		अगर (err) अणु
			अगर (त्रुटि_सं == ENOENT) अणु
				err = 0;
				अवरोध;
			पूर्ण
			pr_debug("%s: can't get next program: %s%s\n",
				 __func__, म_त्रुटि(त्रुटि_सं),
				 त्रुटि_सं == EINVAL ? " -- kernel too old?" : "");
			/* करोn't report error on old kernel or EPERM  */
			err = (त्रुटि_सं == EINVAL || त्रुटि_सं == EPERM) ? 0 : -1;
			अवरोध;
		पूर्ण
		fd = bpf_prog_get_fd_by_id(id);
		अगर (fd < 0) अणु
			pr_debug("%s: failed to get fd for prog_id %u\n",
				 __func__, id);
			जारी;
		पूर्ण

		err = perf_event__synthesize_one_bpf_prog(session, process,
							  machine, fd,
							  event, opts);
		बंद(fd);
		अगर (err) अणु
			/* करो not वापस error क्रम old kernel */
			अगर (err == -2)
				err = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Synthesize all the bpf images - trampolines/dispatchers. */
	अगर (symbol_conf.kallsyms_name != शून्य)
		kallsyms_filename = symbol_conf.kallsyms_name;

	arg = (काष्ठा kallsyms_parse) अणु
		.event   = event,
		.process = process,
		.machine = machine,
		.tool    = session->tool,
	पूर्ण;

	अगर (kallsyms__parse(kallsyms_filename, &arg, kallsyms_process_symbol)) अणु
		pr_err("%s: failed to synthesize bpf images: %s\n",
		       __func__, म_त्रुटि(त्रुटि_सं));
	पूर्ण

	मुक्त(event);
	वापस err;
पूर्ण

अटल व्योम perf_env__add_bpf_info(काष्ठा perf_env *env, u32 id)
अणु
	काष्ठा bpf_prog_info_linear *info_linear;
	काष्ठा bpf_prog_info_node *info_node;
	काष्ठा btf *btf = शून्य;
	u64 arrays;
	u32 btf_id;
	पूर्णांक fd;

	fd = bpf_prog_get_fd_by_id(id);
	अगर (fd < 0)
		वापस;

	arrays = 1UL << BPF_PROG_INFO_JITED_KSYMS;
	arrays |= 1UL << BPF_PROG_INFO_JITED_FUNC_LENS;
	arrays |= 1UL << BPF_PROG_INFO_FUNC_INFO;
	arrays |= 1UL << BPF_PROG_INFO_PROG_TAGS;
	arrays |= 1UL << BPF_PROG_INFO_JITED_INSNS;
	arrays |= 1UL << BPF_PROG_INFO_LINE_INFO;
	arrays |= 1UL << BPF_PROG_INFO_JITED_LINE_INFO;

	info_linear = bpf_program__get_prog_info_linear(fd, arrays);
	अगर (IS_ERR_OR_शून्य(info_linear)) अणु
		pr_debug("%s: failed to get BPF program info. aborting\n", __func__);
		जाओ out;
	पूर्ण

	btf_id = info_linear->info.btf_id;

	info_node = दो_स्मृति(माप(काष्ठा bpf_prog_info_node));
	अगर (info_node) अणु
		info_node->info_linear = info_linear;
		perf_env__insert_bpf_prog_info(env, info_node);
	पूर्ण अन्यथा
		मुक्त(info_linear);

	अगर (btf_id == 0)
		जाओ out;

	अगर (btf__get_from_id(btf_id, &btf)) अणु
		pr_debug("%s: failed to get BTF of id %u, aborting\n",
			 __func__, btf_id);
		जाओ out;
	पूर्ण
	perf_env__fetch_btf(env, btf_id, btf);

out:
	मुक्त(btf);
	बंद(fd);
पूर्ण

अटल पूर्णांक bpf_event__sb_cb(जोड़ perf_event *event, व्योम *data)
अणु
	काष्ठा perf_env *env = data;

	अगर (event->header.type != PERF_RECORD_BPF_EVENT)
		वापस -1;

	चयन (event->bpf.type) अणु
	हाल PERF_BPF_EVENT_PROG_LOAD:
		perf_env__add_bpf_info(env, event->bpf.id);

	हाल PERF_BPF_EVENT_PROG_UNLOAD:
		/*
		 * Do not मुक्त bpf_prog_info and btf of the program here,
		 * as annotation still need them. They will be मुक्तd at
		 * the end of the session.
		 */
		अवरोध;
	शेष:
		pr_debug("unexpected bpf event type of %d\n", event->bpf.type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक evlist__add_bpf_sb_event(काष्ठा evlist *evlist, काष्ठा perf_env *env)
अणु
	काष्ठा perf_event_attr attr = अणु
		.type	          = PERF_TYPE_SOFTWARE,
		.config           = PERF_COUNT_SW_DUMMY,
		.sample_id_all    = 1,
		.watermark        = 1,
		.bpf_event        = 1,
		.size	   = माप(attr), /* to capture ABI version */
	पूर्ण;

	/*
	 * Older gcc versions करोn't support designated initializers, like above,
	 * क्रम unnamed जोड़ members, such as the following:
	 */
	attr.wakeup_watermark = 1;

	वापस evlist__add_sb_event(evlist, &attr, bpf_event__sb_cb, env);
पूर्ण

व्योम bpf_event__prपूर्णांक_bpf_prog_info(काष्ठा bpf_prog_info *info,
				    काष्ठा perf_env *env,
				    खाता *fp)
अणु
	__u32 *prog_lens = (__u32 *)(uपूर्णांकptr_t)(info->jited_func_lens);
	__u64 *prog_addrs = (__u64 *)(uपूर्णांकptr_t)(info->jited_ksyms);
	अक्षर name[KSYM_NAME_LEN];
	काष्ठा btf *btf = शून्य;
	u32 sub_prog_cnt, i;

	sub_prog_cnt = info->nr_jited_ksyms;
	अगर (sub_prog_cnt != info->nr_prog_tags ||
	    sub_prog_cnt != info->nr_jited_func_lens)
		वापस;

	अगर (info->btf_id) अणु
		काष्ठा btf_node *node;

		node = perf_env__find_btf(env, info->btf_id);
		अगर (node)
			btf = btf__new((__u8 *)(node->data),
				       node->data_size);
	पूर्ण

	अगर (sub_prog_cnt == 1) अणु
		synthesize_bpf_prog_name(name, KSYM_NAME_LEN, info, btf, 0);
		ख_लिखो(fp, "# bpf_prog_info %u: %s addr 0x%llx size %u\n",
			info->id, name, prog_addrs[0], prog_lens[0]);
		वापस;
	पूर्ण

	ख_लिखो(fp, "# bpf_prog_info %u:\n", info->id);
	क्रम (i = 0; i < sub_prog_cnt; i++) अणु
		synthesize_bpf_prog_name(name, KSYM_NAME_LEN, info, btf, i);

		ख_लिखो(fp, "# \tsub_prog %u: %s addr 0x%llx size %u\n",
			i, name, prog_addrs[i], prog_lens[i]);
	पूर्ण
पूर्ण
