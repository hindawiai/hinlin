<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा S अणु
	पूर्णांक x;
पूर्ण;

काष्ठा C अणु
	पूर्णांक x;
	पूर्णांक y;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, काष्ठा S);
पूर्ण map SEC(".maps");

क्रमागत E अणु
	E_ITEM
पूर्ण;

अटल पूर्णांक global_data_x = 100;
अटल पूर्णांक अस्थिर global_data_y = 500;

__noअंतरभूत पूर्णांक foo(स्थिर काष्ठा S *s)
अणु
	अगर (s)
		वापस bpf_get_pअक्रमom_u32() < s->x;

	वापस 0;
पूर्ण

__noअंतरभूत पूर्णांक bar(पूर्णांक *x)
अणु
	अगर (x)
		*x &= bpf_get_pअक्रमom_u32();

	वापस 0;
पूर्ण
__noअंतरभूत पूर्णांक baz(अस्थिर पूर्णांक *x)
अणु
	अगर (x)
		*x &= bpf_get_pअक्रमom_u32();

	वापस 0;
पूर्ण

__noअंतरभूत पूर्णांक qux(क्रमागत E *e)
अणु
	अगर (e)
		वापस *e;

	वापस 0;
पूर्ण

__noअंतरभूत पूर्णांक quux(पूर्णांक (*arr)[10])
अणु
	अगर (arr)
		वापस (*arr)[9];

	वापस 0;
पूर्ण

__noअंतरभूत पूर्णांक quuz(पूर्णांक **p)
अणु
	अगर (p)
		*p = शून्य;

	वापस 0;
पूर्ण

SEC("cgroup_skb/ingress")
पूर्णांक test_cls(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक result = 0;

	अणु
		स्थिर काष्ठा S s = अणु.x = skb->len पूर्ण;

		result |= foo(&s);
	पूर्ण

	अणु
		स्थिर __u32 key = 1;
		स्थिर काष्ठा S *s = bpf_map_lookup_elem(&map, &key);

		result |= foo(s);
	पूर्ण

	अणु
		स्थिर काष्ठा C c = अणु.x = skb->len, .y = skb->family पूर्ण;

		result |= foo((स्थिर काष्ठा S *)&c);
	पूर्ण

	अणु
		result |= foo(शून्य);
	पूर्ण

	अणु
		bar(&result);
		bar(&global_data_x);
	पूर्ण

	अणु
		result |= baz(&global_data_y);
	पूर्ण

	अणु
		क्रमागत E e = E_ITEM;

		result |= qux(&e);
	पूर्ण

	अणु
		पूर्णांक array[10] = अणु0पूर्ण;

		result |= quux(&array);
	पूर्ण

	अणु
		पूर्णांक *p;

		result |= quuz(&p);
	पूर्ण

	वापस result ? 1 : 0;
पूर्ण
