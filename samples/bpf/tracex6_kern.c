<शैली गुरु>
#समावेश <linux/ptrace.h>
#समावेश <linux/version.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(u32));
	__uपूर्णांक(max_entries, 64);
पूर्ण counters SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, पूर्णांक);
	__type(value, u64);
	__uपूर्णांक(max_entries, 64);
पूर्ण values SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, पूर्णांक);
	__type(value, काष्ठा bpf_perf_event_value);
	__uपूर्णांक(max_entries, 64);
पूर्ण values2 SEC(".maps");

SEC("kprobe/htab_map_get_next_key")
पूर्णांक bpf_prog1(काष्ठा pt_regs *ctx)
अणु
	u32 key = bpf_get_smp_processor_id();
	u64 count, *val;
	s64 error;

	count = bpf_perf_event_पढ़ो(&counters, key);
	error = (s64)count;
	अगर (error <= -2 && error >= -22)
		वापस 0;

	val = bpf_map_lookup_elem(&values, &key);
	अगर (val)
		*val = count;
	अन्यथा
		bpf_map_update_elem(&values, &key, &count, BPF_NOEXIST);

	वापस 0;
पूर्ण

SEC("kprobe/htab_map_lookup_elem")
पूर्णांक bpf_prog2(काष्ठा pt_regs *ctx)
अणु
	u32 key = bpf_get_smp_processor_id();
	काष्ठा bpf_perf_event_value *val, buf;
	पूर्णांक error;

	error = bpf_perf_event_पढ़ो_value(&counters, key, &buf, माप(buf));
	अगर (error)
		वापस 0;

	val = bpf_map_lookup_elem(&values2, &key);
	अगर (val)
		*val = buf;
	अन्यथा
		bpf_map_update_elem(&values2, &key, &buf, BPF_NOEXIST);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
