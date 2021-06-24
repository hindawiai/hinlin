<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018 Facebook */

#समावेश <मानककोष.स>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/bpf.h>
#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

#समावेश <bpf/bpf_endian.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "test_select_reuseport_common.h"

पूर्णांक _version SEC("version") = 1;

#अगर_अघोषित दुरत्व
#घोषणा दुरत्व(TYPE, MEMBER) ((माप_प्रकार) &((TYPE *)0)->MEMBER)
#पूर्ण_अगर

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
	__uपूर्णांक(max_entries, 1);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण outer_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, NR_RESULTS);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण result_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, पूर्णांक);
पूर्ण पंचांगp_index_ovr_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण linum_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, काष्ठा data_check);
पूर्ण data_check_map SEC(".maps");

#घोषणा GOTO_DONE(_result) (अणु			\
	result = (_result);			\
	linum = __LINE__;			\
	जाओ करोne;				\
पूर्ण)

SEC("sk_reuseport")
पूर्णांक _select_by_skb_data(काष्ठा sk_reuseport_md *reuse_md)
अणु
	__u32 linum, index = 0, flags = 0, index_zero = 0;
	__u32 *result_cnt, *linum_value;
	काष्ठा data_check data_check = अणुपूर्ण;
	काष्ठा cmd *cmd, cmd_copy;
	व्योम *data, *data_end;
	व्योम *reuseport_array;
	क्रमागत result result;
	पूर्णांक *index_ovr;
	पूर्णांक err;

	data = reuse_md->data;
	data_end = reuse_md->data_end;
	data_check.len = reuse_md->len;
	data_check.eth_protocol = reuse_md->eth_protocol;
	data_check.ip_protocol = reuse_md->ip_protocol;
	data_check.hash = reuse_md->hash;
	data_check.bind_inany = reuse_md->bind_inany;
	अगर (data_check.eth_protocol == bpf_htons(ETH_P_IP)) अणु
		अगर (bpf_skb_load_bytes_relative(reuse_md,
						दुरत्व(काष्ठा iphdr, saddr),
						data_check.skb_addrs, 8,
						BPF_HDR_START_NET))
			GOTO_DONE(DROP_MISC);
	पूर्ण अन्यथा अणु
		अगर (bpf_skb_load_bytes_relative(reuse_md,
						दुरत्व(काष्ठा ipv6hdr, saddr),
						data_check.skb_addrs, 32,
						BPF_HDR_START_NET))
			GOTO_DONE(DROP_MISC);
	पूर्ण

	/*
	 * The ip_protocol could be a compile समय decision
	 * अगर the bpf_prog.o is dedicated to either TCP or
	 * UDP.
	 *
	 * Otherwise, reuse_md->ip_protocol or
	 * the protocol field in the iphdr can be used.
	 */
	अगर (data_check.ip_protocol == IPPROTO_TCP) अणु
		काष्ठा tcphdr *th = data;

		अगर (th + 1 > data_end)
			GOTO_DONE(DROP_MISC);

		data_check.skb_ports[0] = th->source;
		data_check.skb_ports[1] = th->dest;

		अगर (th->fin)
			/* The connection is being torn करोwn at the end of a
			 * test. It can't contain a cmd, so वापस early.
			 */
			वापस SK_PASS;

		अगर ((th->करोff << 2) + माप(*cmd) > data_check.len)
			GOTO_DONE(DROP_ERR_SKB_DATA);
		अगर (bpf_skb_load_bytes(reuse_md, th->करोff << 2, &cmd_copy,
				       माप(cmd_copy)))
			GOTO_DONE(DROP_MISC);
		cmd = &cmd_copy;
	पूर्ण अन्यथा अगर (data_check.ip_protocol == IPPROTO_UDP) अणु
		काष्ठा udphdr *uh = data;

		अगर (uh + 1 > data_end)
			GOTO_DONE(DROP_MISC);

		data_check.skb_ports[0] = uh->source;
		data_check.skb_ports[1] = uh->dest;

		अगर (माप(काष्ठा udphdr) + माप(*cmd) > data_check.len)
			GOTO_DONE(DROP_ERR_SKB_DATA);
		अगर (data + माप(काष्ठा udphdr) + माप(*cmd) > data_end) अणु
			अगर (bpf_skb_load_bytes(reuse_md, माप(काष्ठा udphdr),
					       &cmd_copy, माप(cmd_copy)))
				GOTO_DONE(DROP_MISC);
			cmd = &cmd_copy;
		पूर्ण अन्यथा अणु
			cmd = data + माप(काष्ठा udphdr);
		पूर्ण
	पूर्ण अन्यथा अणु
		GOTO_DONE(DROP_MISC);
	पूर्ण

	reuseport_array = bpf_map_lookup_elem(&outer_map, &index_zero);
	अगर (!reuseport_array)
		GOTO_DONE(DROP_ERR_INNER_MAP);

	index = cmd->reuseport_index;
	index_ovr = bpf_map_lookup_elem(&पंचांगp_index_ovr_map, &index_zero);
	अगर (!index_ovr)
		GOTO_DONE(DROP_MISC);

	अगर (*index_ovr != -1) अणु
		index = *index_ovr;
		*index_ovr = -1;
	पूर्ण
	err = bpf_sk_select_reuseport(reuse_md, reuseport_array, &index,
				      flags);
	अगर (!err)
		GOTO_DONE(PASS);

	अगर (cmd->pass_on_failure)
		GOTO_DONE(PASS_ERR_SK_SELECT_REUSEPORT);
	अन्यथा
		GOTO_DONE(DROP_ERR_SK_SELECT_REUSEPORT);

करोne:
	result_cnt = bpf_map_lookup_elem(&result_map, &result);
	अगर (!result_cnt)
		वापस SK_DROP;

	bpf_map_update_elem(&linum_map, &index_zero, &linum, BPF_ANY);
	bpf_map_update_elem(&data_check_map, &index_zero, &data_check, BPF_ANY);

	(*result_cnt)++;
	वापस result < PASS ? SK_DROP : SK_PASS;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
