<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

__u32 map1_id = 0, map2_id = 0;
__u32 map1_accessed = 0, map2_accessed = 0;
__u64 map1_seqnum = 0, map2_seqnum1 = 0, map2_seqnum2 = 0;

अटल अस्थिर स्थिर __u32 prपूर्णांक_len;
अटल अस्थिर स्थिर __u32 ret1;

SEC("iter/bpf_map")
पूर्णांक dump_bpf_map(काष्ठा bpf_iter__bpf_map *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	काष्ठा bpf_map *map = ctx->map;
	__u64 seq_num;
	पूर्णांक i, ret = 0;

	अगर (map == (व्योम *)0)
		वापस 0;

	/* only dump map1_id and map2_id */
	अगर (map->id != map1_id && map->id != map2_id)
		वापस 0;

	seq_num = ctx->meta->seq_num;
	अगर (map->id == map1_id) अणु
		map1_seqnum = seq_num;
		map1_accessed++;
	पूर्ण

	अगर (map->id == map2_id) अणु
		अगर (map2_accessed == 0) अणु
			map2_seqnum1 = seq_num;
			अगर (ret1)
				ret = 1;
		पूर्ण अन्यथा अणु
			map2_seqnum2 = seq_num;
		पूर्ण
		map2_accessed++;
	पूर्ण

	/* fill seq_file buffer */
	क्रम (i = 0; i < prपूर्णांक_len; i++)
		bpf_seq_ग_लिखो(seq, &seq_num, माप(seq_num));

	वापस ret;
पूर्ण
