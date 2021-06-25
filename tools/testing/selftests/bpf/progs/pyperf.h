<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश <linux/sched.h>
#समावेश <linux/ptrace.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा FUNCTION_NAME_LEN 64
#घोषणा खाता_NAME_LEN 128
#घोषणा TASK_COMM_LEN 16

प्रकार काष्ठा अणु
	पूर्णांक PyThपढ़ोState_frame;
	पूर्णांक PyThपढ़ोState_thपढ़ो;
	पूर्णांक PyFrameObject_back;
	पूर्णांक PyFrameObject_code;
	पूर्णांक PyFrameObject_lineno;
	पूर्णांक PyCodeObject_filename;
	पूर्णांक PyCodeObject_name;
	पूर्णांक String_data;
	पूर्णांक String_size;
पूर्ण OffsetConfig;

प्रकार काष्ठा अणु
	uपूर्णांकptr_t current_state_addr;
	uपूर्णांकptr_t tls_key_addr;
	OffsetConfig offsets;
	bool use_tls;
पूर्ण PidData;

प्रकार काष्ठा अणु
	uपूर्णांक32_t success;
पूर्ण Stats;

प्रकार काष्ठा अणु
	अक्षर name[FUNCTION_NAME_LEN];
	अक्षर file[खाता_NAME_LEN];
पूर्ण Symbol;

प्रकार काष्ठा अणु
	uपूर्णांक32_t pid;
	uपूर्णांक32_t tid;
	अक्षर comm[TASK_COMM_LEN];
	पूर्णांक32_t kernel_stack_id;
	पूर्णांक32_t user_stack_id;
	bool thपढ़ो_current;
	bool pthपढ़ो_match;
	bool stack_complete;
	पूर्णांक16_t stack_len;
	पूर्णांक32_t stack[STACK_MAX_LEN];

	पूर्णांक has_meta;
	पूर्णांक metadata;
	अक्षर dummy_safeguard;
पूर्ण Event;


प्रकार पूर्णांक pid_t;

प्रकार काष्ठा अणु
	व्योम* f_back; // PyFrameObject.f_back, previous frame
	व्योम* f_code; // PyFrameObject.f_code, poपूर्णांकer to PyCodeObject
	व्योम* co_filename; // PyCodeObject.co_filename
	व्योम* co_name; // PyCodeObject.co_name
पूर्ण FrameData;

#अगर_घोषित SUBPROGS
__noअंतरभूत
#अन्यथा
__always_अंतरभूत
#पूर्ण_अगर
अटल व्योम *get_thपढ़ो_state(व्योम *tls_base, PidData *pidData)
अणु
	व्योम* thपढ़ो_state;
	पूर्णांक key;

	bpf_probe_पढ़ो_user(&key, माप(key), (व्योम*)(दीर्घ)pidData->tls_key_addr);
	bpf_probe_पढ़ो_user(&thपढ़ो_state, माप(thपढ़ो_state),
			    tls_base + 0x310 + key * 0x10 + 0x08);
	वापस thपढ़ो_state;
पूर्ण

अटल __always_अंतरभूत bool get_frame_data(व्योम *frame_ptr, PidData *pidData,
					   FrameData *frame, Symbol *symbol)
अणु
	// पढ़ो data from PyFrameObject
	bpf_probe_पढ़ो_user(&frame->f_back,
			    माप(frame->f_back),
			    frame_ptr + pidData->offsets.PyFrameObject_back);
	bpf_probe_पढ़ो_user(&frame->f_code,
			    माप(frame->f_code),
			    frame_ptr + pidData->offsets.PyFrameObject_code);

	// पढ़ो data from PyCodeObject
	अगर (!frame->f_code)
		वापस false;
	bpf_probe_पढ़ो_user(&frame->co_filename,
			    माप(frame->co_filename),
			    frame->f_code + pidData->offsets.PyCodeObject_filename);
	bpf_probe_पढ़ो_user(&frame->co_name,
			    माप(frame->co_name),
			    frame->f_code + pidData->offsets.PyCodeObject_name);
	// पढ़ो actual names पूर्णांकo symbol
	अगर (frame->co_filename)
		bpf_probe_पढ़ो_user_str(&symbol->file,
					माप(symbol->file),
					frame->co_filename +
					pidData->offsets.String_data);
	अगर (frame->co_name)
		bpf_probe_पढ़ो_user_str(&symbol->name,
					माप(symbol->name),
					frame->co_name +
					pidData->offsets.String_data);
	वापस true;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, PidData);
पूर्ण pidmap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, Event);
पूर्ण evenपंचांगap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, Symbol);
	__type(value, पूर्णांक);
पूर्ण symbolmap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, Stats);
पूर्ण statsmap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(max_entries, 32);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण perfmap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_STACK_TRACE);
	__uपूर्णांक(max_entries, 1000);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(दीर्घ दीर्घ) * 127);
पूर्ण stackmap SEC(".maps");

#अगर_घोषित GLOBAL_FUNC
__noअंतरभूत
#या_अगर defined(SUBPROGS)
अटल __noअंतरभूत
#अन्यथा
अटल __always_अंतरभूत
#पूर्ण_अगर
पूर्णांक __on_event(काष्ठा bpf_raw_tracepoपूर्णांक_args *ctx)
अणु
	uपूर्णांक64_t pid_tgid = bpf_get_current_pid_tgid();
	pid_t pid = (pid_t)(pid_tgid >> 32);
	PidData* pidData = bpf_map_lookup_elem(&pidmap, &pid);
	अगर (!pidData)
		वापस 0;

	पूर्णांक zero = 0;
	Event* event = bpf_map_lookup_elem(&evenपंचांगap, &zero);
	अगर (!event)
		वापस 0;

	event->pid = pid;

	event->tid = (pid_t)pid_tgid;
	bpf_get_current_comm(&event->comm, माप(event->comm));

	event->user_stack_id = bpf_get_stackid(ctx, &stackmap, BPF_F_USER_STACK);
	event->kernel_stack_id = bpf_get_stackid(ctx, &stackmap, 0);

	व्योम* thपढ़ो_state_current = (व्योम*)0;
	bpf_probe_पढ़ो_user(&thपढ़ो_state_current,
			    माप(thपढ़ो_state_current),
			    (व्योम*)(दीर्घ)pidData->current_state_addr);

	काष्ठा task_काष्ठा* task = (काष्ठा task_काष्ठा*)bpf_get_current_task();
	व्योम* tls_base = (व्योम*)task;

	व्योम* thपढ़ो_state = pidData->use_tls ? get_thपढ़ो_state(tls_base, pidData)
		: thपढ़ो_state_current;
	event->thपढ़ो_current = thपढ़ो_state == thपढ़ो_state_current;

	अगर (pidData->use_tls) अणु
		uपूर्णांक64_t pthपढ़ो_created;
		uपूर्णांक64_t pthपढ़ो_self;
		bpf_probe_पढ़ो_user(&pthपढ़ो_self, माप(pthपढ़ो_self),
				    tls_base + 0x10);

		bpf_probe_पढ़ो_user(&pthपढ़ो_created,
				    माप(pthपढ़ो_created),
				    thपढ़ो_state +
				    pidData->offsets.PyThपढ़ोState_thपढ़ो);
		event->pthपढ़ो_match = pthपढ़ो_created == pthपढ़ो_self;
	पूर्ण अन्यथा अणु
		event->pthपढ़ो_match = 1;
	पूर्ण

	अगर (event->pthपढ़ो_match || !pidData->use_tls) अणु
		व्योम* frame_ptr;
		FrameData frame;
		Symbol sym = अणुपूर्ण;
		पूर्णांक cur_cpu = bpf_get_smp_processor_id();

		bpf_probe_पढ़ो_user(&frame_ptr,
				    माप(frame_ptr),
				    thपढ़ो_state +
				    pidData->offsets.PyThपढ़ोState_frame);

		पूर्णांक32_t* symbol_counter = bpf_map_lookup_elem(&symbolmap, &sym);
		अगर (symbol_counter == शून्य)
			वापस 0;
#अगर_घोषित NO_UNROLL
#आशय clang loop unroll(disable)
#अन्यथा
#आशय clang loop unroll(full)
#पूर्ण_अगर
		/* Unwind python stack */
		क्रम (पूर्णांक i = 0; i < STACK_MAX_LEN; ++i) अणु
			अगर (frame_ptr && get_frame_data(frame_ptr, pidData, &frame, &sym)) अणु
				पूर्णांक32_t new_symbol_id = *symbol_counter * 64 + cur_cpu;
				पूर्णांक32_t *symbol_id = bpf_map_lookup_elem(&symbolmap, &sym);
				अगर (!symbol_id) अणु
					bpf_map_update_elem(&symbolmap, &sym, &zero, 0);
					symbol_id = bpf_map_lookup_elem(&symbolmap, &sym);
					अगर (!symbol_id)
						वापस 0;
				पूर्ण
				अगर (*symbol_id == new_symbol_id)
					(*symbol_counter)++;
				event->stack[i] = *symbol_id;
				event->stack_len = i + 1;
				frame_ptr = frame.f_back;
			पूर्ण
		पूर्ण
		event->stack_complete = frame_ptr == शून्य;
	पूर्ण अन्यथा अणु
		event->stack_complete = 1;
	पूर्ण

	Stats* stats = bpf_map_lookup_elem(&statsmap, &zero);
	अगर (stats)
		stats->success++;

	event->has_meta = 0;
	bpf_perf_event_output(ctx, &perfmap, 0, event, दुरत्व(Event, metadata));
	वापस 0;
पूर्ण

SEC("raw_tracepoint/kfree_skb")
पूर्णांक on_event(काष्ठा bpf_raw_tracepoपूर्णांक_args* ctx)
अणु
	पूर्णांक i, ret = 0;
	ret |= __on_event(ctx);
	ret |= __on_event(ctx);
	ret |= __on_event(ctx);
	ret |= __on_event(ctx);
	ret |= __on_event(ctx);
	वापस ret;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
