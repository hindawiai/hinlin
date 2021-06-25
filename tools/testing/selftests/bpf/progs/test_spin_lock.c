<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश <linux/bpf.h>
#समावेश <linux/version.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा hmap_elem अणु
	अस्थिर पूर्णांक cnt;
	काष्ठा bpf_spin_lock lock;
	पूर्णांक test_padding;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, काष्ठा hmap_elem);
पूर्ण hmap SEC(".maps");

काष्ठा cls_elem अणु
	काष्ठा bpf_spin_lock lock;
	अस्थिर पूर्णांक cnt;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_CGROUP_STORAGE);
	__type(key, काष्ठा bpf_cgroup_storage_key);
	__type(value, काष्ठा cls_elem);
पूर्ण cls_map SEC(".maps");

काष्ठा bpf_vqueue अणु
	काष्ठा bpf_spin_lock lock;
	/* 4 byte hole */
	अचिन्हित दीर्घ दीर्घ lastसमय;
	पूर्णांक credit;
	अचिन्हित पूर्णांक rate;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, काष्ठा bpf_vqueue);
पूर्ण vqueue SEC(".maps");

#घोषणा CREDIT_PER_NS(delta, rate) (((delta) * rate) >> 20)

SEC("spin_lock_demo")
पूर्णांक bpf_sping_lock_test(काष्ठा __sk_buff *skb)
अणु
	अस्थिर पूर्णांक credit = 0, max_credit = 100, pkt_len = 64;
	काष्ठा hmap_elem zero = अणुपूर्ण, *val;
	अचिन्हित दीर्घ दीर्घ curसमय;
	काष्ठा bpf_vqueue *q;
	काष्ठा cls_elem *cls;
	पूर्णांक key = 0;
	पूर्णांक err = 0;

	val = bpf_map_lookup_elem(&hmap, &key);
	अगर (!val) अणु
		bpf_map_update_elem(&hmap, &key, &zero, 0);
		val = bpf_map_lookup_elem(&hmap, &key);
		अगर (!val) अणु
			err = 1;
			जाओ err;
		पूर्ण
	पूर्ण
	/* spin_lock in hash map run समय test */
	bpf_spin_lock(&val->lock);
	अगर (val->cnt)
		val->cnt--;
	अन्यथा
		val->cnt++;
	अगर (val->cnt != 0 && val->cnt != 1)
		err = 1;
	bpf_spin_unlock(&val->lock);

	/* spin_lock in array. भव queue demo */
	q = bpf_map_lookup_elem(&vqueue, &key);
	अगर (!q)
		जाओ err;
	curसमय = bpf_kसमय_get_ns();
	bpf_spin_lock(&q->lock);
	q->credit += CREDIT_PER_NS(curसमय - q->lastसमय, q->rate);
	q->lastसमय = curसमय;
	अगर (q->credit > max_credit)
		q->credit = max_credit;
	q->credit -= pkt_len;
	credit = q->credit;
	bpf_spin_unlock(&q->lock);

	/* spin_lock in cgroup local storage */
	cls = bpf_get_local_storage(&cls_map, 0);
	bpf_spin_lock(&cls->lock);
	cls->cnt++;
	bpf_spin_unlock(&cls->lock);

err:
	वापस err;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
