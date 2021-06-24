<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित _PERF_BPF_H
#घोषणा _PERF_BPF_H

#समावेश <uapi/linux/bpf.h>

/*
 * A helper काष्ठाure used by eBPF C program to describe map attributes to
 * elf_bpf loader, taken from tools/testing/selftests/bpf/bpf_helpers.h:
 */
काष्ठा bpf_map अणु
        अचिन्हित पूर्णांक type;
        अचिन्हित पूर्णांक key_size;
        अचिन्हित पूर्णांक value_size;
        अचिन्हित पूर्णांक max_entries;
        अचिन्हित पूर्णांक map_flags;
        अचिन्हित पूर्णांक inner_map_idx;
        अचिन्हित पूर्णांक numa_node;
पूर्ण;

#घोषणा bpf_map(name, _type, type_key, type_val, _max_entries)	\
काष्ठा bpf_map SEC("maps") name = अणु				\
	.type	     = BPF_MAP_TYPE_##_type,			\
	.key_size    = माप(type_key),			\
	.value_size  = माप(type_val),			\
	.max_entries = _max_entries,				\
पूर्ण;								\
काष्ठा ____btf_map_##name अणु					\
	type_key key;						\
	type_val value;                                 	\
पूर्ण;								\
काष्ठा ____btf_map_##name __attribute__((section(".maps." #name), used)) \
	____btf_map_##name = अणु पूर्ण

/*
 * FIXME: this should receive .max_entries as a parameter, as careful
 *	  tuning of these limits is needed to aव्योम hitting limits that
 *	  prevents other BPF स्थिरructs, such as tracepoपूर्णांक handlers,
 *	  to get installed, with cryptic messages from libbpf, etc.
 *	  For the current need, 'perf trace --filter-pids', 64 should
 *	  be good enough, but this surely needs to be revisited.
 */
#घोषणा pid_map(name, value_type) bpf_map(name, HASH, pid_t, value_type, 64)

अटल पूर्णांक (*bpf_map_update_elem)(काष्ठा bpf_map *map, व्योम *key, व्योम *value, u64 flags) = (व्योम *)BPF_FUNC_map_update_elem;
अटल व्योम *(*bpf_map_lookup_elem)(काष्ठा bpf_map *map, व्योम *key) = (व्योम *)BPF_FUNC_map_lookup_elem;

अटल व्योम (*bpf_tail_call)(व्योम *ctx, व्योम *map, पूर्णांक index) = (व्योम *)BPF_FUNC_tail_call;

#घोषणा SEC(NAME) __attribute__((section(NAME),  used))

#घोषणा probe(function, vars) \
	SEC(#function "=" #function " " #vars) function

#घोषणा syscall_enter(name) \
	SEC("syscalls:sys_enter_" #name) syscall_enter_ ## name

#घोषणा syscall_निकास(name) \
	SEC("syscalls:sys_exit_" #name) syscall_निकास_ ## name

#घोषणा license(name) \
अक्षर _license[] SEC("license") = #name; \
पूर्णांक _version SEC("version") = LINUX_VERSION_CODE;

अटल पूर्णांक (*probe_पढ़ो)(व्योम *dst, पूर्णांक size, स्थिर व्योम *unsafe_addr) = (व्योम *)BPF_FUNC_probe_पढ़ो;
अटल पूर्णांक (*probe_पढ़ो_str)(व्योम *dst, पूर्णांक size, स्थिर व्योम *unsafe_addr) = (व्योम *)BPF_FUNC_probe_पढ़ो_str;

अटल पूर्णांक (*perf_event_output)(व्योम *, काष्ठा bpf_map *, पूर्णांक, व्योम *, अचिन्हित दीर्घ) = (व्योम *)BPF_FUNC_perf_event_output;

#पूर्ण_अगर /* _PERF_BPF_H */
