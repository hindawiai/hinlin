<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2017-2018 Covalent IO, Inc. http://covalent.io */
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/in.h>
#समावेश <linux/udp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/pkt_cls.h>
#समावेश <sys/socket.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

/* Sockmap sample program connects a client and a backend together
 * using cgroups.
 *
 *    client:X <---> frontend:80 client:X <---> backend:80
 *
 * For simplicity we hard code values here and bind 1:1. The hard
 * coded values are part of the setup in sockmap.sh script that
 * is associated with this BPF program.
 *
 * The bpf_prपूर्णांकk is verbose and prपूर्णांकs inक्रमmation as connections
 * are established and verdicts are decided.
 */

काष्ठा अणु
	__uपूर्णांक(type, TEST_MAP_TYPE);
	__uपूर्णांक(max_entries, 20);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण sock_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, TEST_MAP_TYPE);
	__uपूर्णांक(max_entries, 20);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण sock_map_txmsg SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, TEST_MAP_TYPE);
	__uपूर्णांक(max_entries, 20);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण sock_map_redir SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sock_apply_bytes SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sock_cork_bytes SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 6);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sock_bytes SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sock_redir_flags SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 3);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sock_skb_opts SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, TEST_MAP_TYPE);
	__uपूर्णांक(max_entries, 20);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण tls_sock_map SEC(".maps");

SEC("sk_skb1")
पूर्णांक bpf_prog1(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक *f, two = 2;

	f = bpf_map_lookup_elem(&sock_skb_opts, &two);
	अगर (f && *f) अणु
		वापस *f;
	पूर्ण
	वापस skb->len;
पूर्ण

SEC("sk_skb2")
पूर्णांक bpf_prog2(काष्ठा __sk_buff *skb)
अणु
	__u32 lport = skb->local_port;
	__u32 rport = skb->remote_port;
	पूर्णांक len, *f, ret, zero = 0;
	__u64 flags = 0;

	अगर (lport == 10000)
		ret = 10;
	अन्यथा
		ret = 1;

	len = (__u32)skb->data_end - (__u32)skb->data;
	f = bpf_map_lookup_elem(&sock_skb_opts, &zero);
	अगर (f && *f) अणु
		ret = 3;
		flags = *f;
	पूर्ण

#अगर_घोषित SOCKMAP
	वापस bpf_sk_redirect_map(skb, &sock_map, ret, flags);
#अन्यथा
	वापस bpf_sk_redirect_hash(skb, &sock_map, &ret, flags);
#पूर्ण_अगर

पूर्ण

अटल अंतरभूत व्योम bpf_ग_लिखो_pass(काष्ठा __sk_buff *skb, पूर्णांक offset)
अणु
	पूर्णांक err = bpf_skb_pull_data(skb, 6 + offset);
	व्योम *data_end;
	अक्षर *c;

	अगर (err)
		वापस;

	c = (अक्षर *)(दीर्घ)skb->data;
	data_end = (व्योम *)(दीर्घ)skb->data_end;

	अगर (c + 5 + offset < data_end)
		स_नकल(c + offset, "PASS", 4);
पूर्ण

SEC("sk_skb3")
पूर्णांक bpf_prog3(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक err, *f, ret = SK_PASS;
	स्थिर पूर्णांक one = 1;

	f = bpf_map_lookup_elem(&sock_skb_opts, &one);
	अगर (f && *f) अणु
		__u64 flags = 0;

		ret = 0;
		flags = *f;

		err = bpf_skb_adjust_room(skb, -13, 0, 0);
		अगर (err)
			वापस SK_DROP;
		err = bpf_skb_adjust_room(skb, 4, 0, 0);
		अगर (err)
			वापस SK_DROP;
		bpf_ग_लिखो_pass(skb, 0);
#अगर_घोषित SOCKMAP
		वापस bpf_sk_redirect_map(skb, &tls_sock_map, ret, flags);
#अन्यथा
		वापस bpf_sk_redirect_hash(skb, &tls_sock_map, &ret, flags);
#पूर्ण_अगर
	पूर्ण
	f = bpf_map_lookup_elem(&sock_skb_opts, &one);
	अगर (f && *f)
		ret = SK_DROP;
	err = bpf_skb_adjust_room(skb, 4, 0, 0);
	अगर (err)
		वापस SK_DROP;
	bpf_ग_लिखो_pass(skb, 13);
tls_out:
	वापस ret;
पूर्ण

SEC("sockops")
पूर्णांक bpf_sockmap(काष्ठा bpf_sock_ops *skops)
अणु
	__u32 lport, rport;
	पूर्णांक op, err = 0, index, key, ret;


	op = (पूर्णांक) skops->op;

	चयन (op) अणु
	हाल BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
		lport = skops->local_port;
		rport = skops->remote_port;

		अगर (lport == 10000) अणु
			ret = 1;
#अगर_घोषित SOCKMAP
			err = bpf_sock_map_update(skops, &sock_map, &ret,
						  BPF_NOEXIST);
#अन्यथा
			err = bpf_sock_hash_update(skops, &sock_map, &ret,
						   BPF_NOEXIST);
#पूर्ण_अगर
		पूर्ण
		अवरोध;
	हाल BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB:
		lport = skops->local_port;
		rport = skops->remote_port;

		अगर (bpf_ntohl(rport) == 10001) अणु
			ret = 10;
#अगर_घोषित SOCKMAP
			err = bpf_sock_map_update(skops, &sock_map, &ret,
						  BPF_NOEXIST);
#अन्यथा
			err = bpf_sock_hash_update(skops, &sock_map, &ret,
						   BPF_NOEXIST);
#पूर्ण_अगर
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

SEC("sk_msg1")
पूर्णांक bpf_prog4(काष्ठा sk_msg_md *msg)
अणु
	पूर्णांक *bytes, zero = 0, one = 1, two = 2, three = 3, four = 4, five = 5;
	पूर्णांक *start, *end, *start_push, *end_push, *start_pop, *pop;

	bytes = bpf_map_lookup_elem(&sock_apply_bytes, &zero);
	अगर (bytes)
		bpf_msg_apply_bytes(msg, *bytes);
	bytes = bpf_map_lookup_elem(&sock_cork_bytes, &zero);
	अगर (bytes)
		bpf_msg_cork_bytes(msg, *bytes);
	start = bpf_map_lookup_elem(&sock_bytes, &zero);
	end = bpf_map_lookup_elem(&sock_bytes, &one);
	अगर (start && end)
		bpf_msg_pull_data(msg, *start, *end, 0);
	start_push = bpf_map_lookup_elem(&sock_bytes, &two);
	end_push = bpf_map_lookup_elem(&sock_bytes, &three);
	अगर (start_push && end_push)
		bpf_msg_push_data(msg, *start_push, *end_push, 0);
	start_pop = bpf_map_lookup_elem(&sock_bytes, &four);
	pop = bpf_map_lookup_elem(&sock_bytes, &five);
	अगर (start_pop && pop)
		bpf_msg_pop_data(msg, *start_pop, *pop, 0);
	वापस SK_PASS;
पूर्ण

SEC("sk_msg2")
पूर्णांक bpf_prog6(काष्ठा sk_msg_md *msg)
अणु
	पूर्णांक zero = 0, one = 1, two = 2, three = 3, four = 4, five = 5, key = 0;
	पूर्णांक *bytes, *start, *end, *start_push, *end_push, *start_pop, *pop, *f;
	__u64 flags = 0;

	bytes = bpf_map_lookup_elem(&sock_apply_bytes, &zero);
	अगर (bytes)
		bpf_msg_apply_bytes(msg, *bytes);
	bytes = bpf_map_lookup_elem(&sock_cork_bytes, &zero);
	अगर (bytes)
		bpf_msg_cork_bytes(msg, *bytes);

	start = bpf_map_lookup_elem(&sock_bytes, &zero);
	end = bpf_map_lookup_elem(&sock_bytes, &one);
	अगर (start && end)
		bpf_msg_pull_data(msg, *start, *end, 0);

	start_push = bpf_map_lookup_elem(&sock_bytes, &two);
	end_push = bpf_map_lookup_elem(&sock_bytes, &three);
	अगर (start_push && end_push)
		bpf_msg_push_data(msg, *start_push, *end_push, 0);

	start_pop = bpf_map_lookup_elem(&sock_bytes, &four);
	pop = bpf_map_lookup_elem(&sock_bytes, &five);
	अगर (start_pop && pop)
		bpf_msg_pop_data(msg, *start_pop, *pop, 0);

	f = bpf_map_lookup_elem(&sock_redir_flags, &zero);
	अगर (f && *f) अणु
		key = 2;
		flags = *f;
	पूर्ण
#अगर_घोषित SOCKMAP
	वापस bpf_msg_redirect_map(msg, &sock_map_redir, key, flags);
#अन्यथा
	वापस bpf_msg_redirect_hash(msg, &sock_map_redir, &key, flags);
#पूर्ण_अगर
पूर्ण

SEC("sk_msg3")
पूर्णांक bpf_prog8(काष्ठा sk_msg_md *msg)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ) msg->data_end;
	व्योम *data = (व्योम *)(दीर्घ) msg->data;
	पूर्णांक ret = 0, *bytes, zero = 0;

	bytes = bpf_map_lookup_elem(&sock_apply_bytes, &zero);
	अगर (bytes) अणु
		ret = bpf_msg_apply_bytes(msg, *bytes);
		अगर (ret)
			वापस SK_DROP;
	पूर्ण अन्यथा अणु
		वापस SK_DROP;
	पूर्ण
	वापस SK_PASS;
पूर्ण
SEC("sk_msg4")
पूर्णांक bpf_prog9(काष्ठा sk_msg_md *msg)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ) msg->data_end;
	व्योम *data = (व्योम *)(दीर्घ) msg->data;
	पूर्णांक ret = 0, *bytes, zero = 0;

	bytes = bpf_map_lookup_elem(&sock_cork_bytes, &zero);
	अगर (bytes) अणु
		अगर (((__u64)data_end - (__u64)data) >= *bytes)
			वापस SK_PASS;
		ret = bpf_msg_cork_bytes(msg, *bytes);
		अगर (ret)
			वापस SK_DROP;
	पूर्ण
	वापस SK_PASS;
पूर्ण

SEC("sk_msg5")
पूर्णांक bpf_prog10(काष्ठा sk_msg_md *msg)
अणु
	पूर्णांक *bytes, *start, *end, *start_push, *end_push, *start_pop, *pop;
	पूर्णांक zero = 0, one = 1, two = 2, three = 3, four = 4, five = 5;

	bytes = bpf_map_lookup_elem(&sock_apply_bytes, &zero);
	अगर (bytes)
		bpf_msg_apply_bytes(msg, *bytes);
	bytes = bpf_map_lookup_elem(&sock_cork_bytes, &zero);
	अगर (bytes)
		bpf_msg_cork_bytes(msg, *bytes);
	start = bpf_map_lookup_elem(&sock_bytes, &zero);
	end = bpf_map_lookup_elem(&sock_bytes, &one);
	अगर (start && end)
		bpf_msg_pull_data(msg, *start, *end, 0);
	start_push = bpf_map_lookup_elem(&sock_bytes, &two);
	end_push = bpf_map_lookup_elem(&sock_bytes, &three);
	अगर (start_push && end_push)
		bpf_msg_push_data(msg, *start_push, *end_push, 0);
	start_pop = bpf_map_lookup_elem(&sock_bytes, &four);
	pop = bpf_map_lookup_elem(&sock_bytes, &five);
	अगर (start_pop && pop)
		bpf_msg_pop_data(msg, *start_pop, *pop, 0);
	वापस SK_DROP;
पूर्ण

पूर्णांक _version SEC("version") = 1;
अक्षर _license[] SEC("license") = "GPL";
