<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

/* Permit pretty deep stack traces */
#घोषणा MAX_STACK_RAWTP 100
काष्ठा stack_trace_t अणु
	पूर्णांक pid;
	पूर्णांक kern_stack_size;
	पूर्णांक user_stack_size;
	पूर्णांक user_stack_buildid_size;
	__u64 kern_stack[MAX_STACK_RAWTP];
	__u64 user_stack[MAX_STACK_RAWTP];
	काष्ठा bpf_stack_build_id user_stack_buildid[MAX_STACK_RAWTP];
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(max_entries, 2);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण perfmap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, काष्ठा stack_trace_t);
पूर्ण stackdata_map SEC(".maps");

/* Allocate per-cpu space twice the needed. For the code below
 *   usize = bpf_get_stack(ctx, raw_data, max_len, BPF_F_USER_STACK);
 *   अगर (usize < 0)
 *     वापस 0;
 *   ksize = bpf_get_stack(ctx, raw_data + usize, max_len - usize, 0);
 *
 * If we have value_size = MAX_STACK_RAWTP * माप(__u64),
 * verअगरier will complain that access "raw_data + usize"
 * with size "max_len - usize" may be out of bound.
 * The maximum "raw_data + usize" is "raw_data + max_len"
 * and the maximum "max_len - usize" is "max_len", verअगरier
 * concludes that the maximum buffer access range is
 * "raw_data[0...max_len * 2 - 1]" and hence reject the program.
 *
 * Doubling the to-be-used max buffer size can fix this verअगरier
 * issue and aव्योम complicated C programming massaging.
 * This is an acceptable workaround since there is one entry here.
 */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64[2 * MAX_STACK_RAWTP]);
पूर्ण rawdata_map SEC(".maps");

SEC("raw_tracepoint/sys_enter")
पूर्णांक bpf_prog1(व्योम *ctx)
अणु
	पूर्णांक max_len, max_buildid_len, total_size;
	काष्ठा stack_trace_t *data;
	दीर्घ usize, ksize;
	व्योम *raw_data;
	__u32 key = 0;

	data = bpf_map_lookup_elem(&stackdata_map, &key);
	अगर (!data)
		वापस 0;

	max_len = MAX_STACK_RAWTP * माप(__u64);
	max_buildid_len = MAX_STACK_RAWTP * माप(काष्ठा bpf_stack_build_id);
	data->pid = bpf_get_current_pid_tgid();
	data->kern_stack_size = bpf_get_stack(ctx, data->kern_stack,
					      max_len, 0);
	data->user_stack_size = bpf_get_stack(ctx, data->user_stack, max_len,
					    BPF_F_USER_STACK);
	data->user_stack_buildid_size = bpf_get_stack(
		ctx, data->user_stack_buildid, max_buildid_len,
		BPF_F_USER_STACK | BPF_F_USER_BUILD_ID);
	bpf_perf_event_output(ctx, &perfmap, 0, data, माप(*data));

	/* ग_लिखो both kernel and user stacks to the same buffer */
	raw_data = bpf_map_lookup_elem(&rawdata_map, &key);
	अगर (!raw_data)
		वापस 0;

	usize = bpf_get_stack(ctx, raw_data, max_len, BPF_F_USER_STACK);
	अगर (usize < 0)
		वापस 0;

	ksize = bpf_get_stack(ctx, raw_data + usize, max_len - usize, 0);
	अगर (ksize < 0)
		वापस 0;

	total_size = usize + ksize;
	अगर (total_size > 0 && total_size <= max_len)
		bpf_perf_event_output(ctx, &perfmap, 0, raw_data, total_size);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
