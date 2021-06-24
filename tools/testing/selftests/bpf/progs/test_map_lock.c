<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश <linux/bpf.h>
#समावेश <linux/version.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा VAR_NUM 16

काष्ठा hmap_elem अणु
	काष्ठा bpf_spin_lock lock;
	पूर्णांक var[VAR_NUM];
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, काष्ठा hmap_elem);
पूर्ण hash_map SEC(".maps");

काष्ठा array_elem अणु
	काष्ठा bpf_spin_lock lock;
	पूर्णांक var[VAR_NUM];
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, काष्ठा array_elem);
पूर्ण array_map SEC(".maps");

SEC("map_lock_demo")
पूर्णांक bpf_map_lock_test(काष्ठा __sk_buff *skb)
अणु
	काष्ठा hmap_elem zero = अणुपूर्ण, *val;
	पूर्णांक rnd = bpf_get_pअक्रमom_u32();
	पूर्णांक key = 0, err = 1, i;
	काष्ठा array_elem *q;

	val = bpf_map_lookup_elem(&hash_map, &key);
	अगर (!val)
		जाओ err;
	/* spin_lock in hash map */
	bpf_spin_lock(&val->lock);
	क्रम (i = 0; i < VAR_NUM; i++)
		val->var[i] = rnd;
	bpf_spin_unlock(&val->lock);

	/* spin_lock in array */
	q = bpf_map_lookup_elem(&array_map, &key);
	अगर (!q)
		जाओ err;
	bpf_spin_lock(&q->lock);
	क्रम (i = 0; i < VAR_NUM; i++)
		q->var[i] = rnd;
	bpf_spin_unlock(&q->lock);
	err = 0;
err:
	वापस err;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
