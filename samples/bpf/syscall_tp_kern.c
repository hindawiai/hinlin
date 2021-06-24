<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017 Facebook
 */
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा syscalls_enter_खोलो_args अणु
	अचिन्हित दीर्घ दीर्घ unused;
	दीर्घ syscall_nr;
	दीर्घ filename_ptr;
	दीर्घ flags;
	दीर्घ mode;
पूर्ण;

काष्ठा syscalls_निकास_खोलो_args अणु
	अचिन्हित दीर्घ दीर्घ unused;
	दीर्घ syscall_nr;
	दीर्घ ret;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, u32);
	__uपूर्णांक(max_entries, 1);
पूर्ण enter_खोलो_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, u32);
	__uपूर्णांक(max_entries, 1);
पूर्ण निकास_खोलो_map SEC(".maps");

अटल __always_अंतरभूत व्योम count(व्योम *map)
अणु
	u32 key = 0;
	u32 *value, init_val = 1;

	value = bpf_map_lookup_elem(map, &key);
	अगर (value)
		*value += 1;
	अन्यथा
		bpf_map_update_elem(map, &key, &init_val, BPF_NOEXIST);
पूर्ण

SEC("tracepoint/syscalls/sys_enter_open")
पूर्णांक trace_enter_खोलो(काष्ठा syscalls_enter_खोलो_args *ctx)
अणु
	count(&enter_खोलो_map);
	वापस 0;
पूर्ण

SEC("tracepoint/syscalls/sys_enter_openat")
पूर्णांक trace_enter_खोलो_at(काष्ठा syscalls_enter_खोलो_args *ctx)
अणु
	count(&enter_खोलो_map);
	वापस 0;
पूर्ण

SEC("tracepoint/syscalls/sys_exit_open")
पूर्णांक trace_enter_निकास(काष्ठा syscalls_निकास_खोलो_args *ctx)
अणु
	count(&निकास_खोलो_map);
	वापस 0;
पूर्ण

SEC("tracepoint/syscalls/sys_exit_openat")
पूर्णांक trace_enter_निकास_at(काष्ठा syscalls_निकास_खोलो_args *ctx)
अणु
	count(&निकास_खोलो_map);
	वापस 0;
पूर्ण
