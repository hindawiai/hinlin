<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>

#समावेश <bpf/bpf_helpers.h>

काष्ठा S अणु
	पूर्णांक v;
पूर्ण;

अटल अस्थिर काष्ठा S global_variable;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 7);
	__type(key, __u32);
	__type(value, पूर्णांक);
पूर्ण values SEC(".maps");

अटल व्योम save_value(__u32 index, पूर्णांक value)
अणु
	bpf_map_update_elem(&values, &index, &value, 0);
पूर्ण

__noअंतरभूत पूर्णांक foo(__u32 index, काष्ठा S *s)
अणु
	अगर (s) अणु
		save_value(index, s->v);
		वापस ++s->v;
	पूर्ण

	save_value(index, 0);

	वापस 1;
पूर्ण

__noअंतरभूत पूर्णांक bar(__u32 index, अस्थिर काष्ठा S *s)
अणु
	अगर (s) अणु
		save_value(index, s->v);
		वापस ++s->v;
	पूर्ण

	save_value(index, 0);

	वापस 1;
पूर्ण

__noअंतरभूत पूर्णांक baz(काष्ठा S **s)
अणु
	अगर (s)
		*s = 0;

	वापस 0;
पूर्ण

SEC("cgroup_skb/ingress")
पूर्णांक test_cls(काष्ठा __sk_buff *skb)
अणु
	__u32 index = 0;

	अणु
		स्थिर पूर्णांक v = foo(index++, 0);

		save_value(index++, v);
	पूर्ण

	अणु
		काष्ठा S s = अणु .v = 100 पूर्ण;

		foo(index++, &s);
		save_value(index++, s.v);
	पूर्ण

	अणु
		global_variable.v = 42;
		bar(index++, &global_variable);
		save_value(index++, global_variable.v);
	पूर्ण

	अणु
		काष्ठा S v, *p = &v;

		baz(&p);
		save_value(index++, !p);
	पूर्ण

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
