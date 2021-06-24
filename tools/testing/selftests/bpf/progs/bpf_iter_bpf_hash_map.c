<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा key_t अणु
	पूर्णांक a;
	पूर्णांक b;
	पूर्णांक c;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 3);
	__type(key, काष्ठा key_t);
	__type(value, __u64);
पूर्ण hashmap1 SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 3);
	__type(key, __u64);
	__type(value, __u64);
पूर्ण hashmap2 SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 3);
	__type(key, काष्ठा key_t);
	__type(value, __u32);
पूर्ण hashmap3 SEC(".maps");

/* will set beक्रमe prog run */
bool in_test_mode = 0;

/* will collect results during prog run */
__u32 key_sum_a = 0, key_sum_b = 0, key_sum_c = 0;
__u64 val_sum = 0;

SEC("iter/bpf_map_elem")
पूर्णांक dump_bpf_hash_map(काष्ठा bpf_iter__bpf_map_elem *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	__u32 seq_num = ctx->meta->seq_num;
	काष्ठा bpf_map *map = ctx->map;
	काष्ठा key_t *key = ctx->key;
	काष्ठा key_t पंचांगp_key;
	__u64 *val = ctx->value;
	__u64 पंचांगp_val = 0;
	पूर्णांक ret;

	अगर (in_test_mode) अणु
		/* test mode is used by selftests to
		 * test functionality of bpf_hash_map iter.
		 *
		 * the above hashmap1 will have correct size
		 * and will be accepted, hashmap2 and hashmap3
		 * should be rejected due to smaller key/value
		 * size.
		 */
		अगर (key == (व्योम *)0 || val == (व्योम *)0)
			वापस 0;

		/* update the value and then delete the <key, value> pair.
		 * it should not impact the existing 'val' which is still
		 * accessible under rcu.
		 */
		__builtin_स_नकल(&पंचांगp_key, key, माप(काष्ठा key_t));
		ret = bpf_map_update_elem(&hashmap1, &पंचांगp_key, &पंचांगp_val, 0);
		अगर (ret)
			वापस 0;
		ret = bpf_map_delete_elem(&hashmap1, &पंचांगp_key);
		अगर (ret)
			वापस 0;

		key_sum_a += key->a;
		key_sum_b += key->b;
		key_sum_c += key->c;
		val_sum += *val;
		वापस 0;
	पूर्ण

	/* non-test mode, the map is prepared with the
	 * below bpftool command sequence:
	 *   bpftool map create /sys/fs/bpf/m1 type hash \
	 *   	key 12 value 8 entries 3 name map1
	 *   bpftool map update id 77 key 0 0 0 1 0 0 0 0 0 0 0 1 \
	 *   	value 0 0 0 1 0 0 0 1
	 *   bpftool map update id 77 key 0 0 0 1 0 0 0 0 0 0 0 2 \
	 *   	value 0 0 0 1 0 0 0 2
	 * The bpftool iter command line:
	 *   bpftool iter pin ./bpf_iter_bpf_hash_map.o /sys/fs/bpf/p1 \
	 *   	map id 77
	 * The below output will be:
	 *   map dump starts
	 *   77: (1000000 0 2000000) (200000001000000)
	 *   77: (1000000 0 1000000) (100000001000000)
	 *   map dump ends
	 */
	अगर (seq_num == 0)
		BPF_SEQ_PRINTF(seq, "map dump starts\n");

	अगर (key == (व्योम *)0 || val == (व्योम *)0) अणु
		BPF_SEQ_PRINTF(seq, "map dump ends\n");
		वापस 0;
	पूर्ण

	BPF_SEQ_PRINTF(seq, "%d: (%x %d %x) (%llx)\n", map->id,
		       key->a, key->b, key->c, *val);

	वापस 0;
पूर्ण
