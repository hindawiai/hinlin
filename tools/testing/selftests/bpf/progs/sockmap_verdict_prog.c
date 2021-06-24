<शैली गुरु>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

पूर्णांक _version SEC("version") = 1;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKMAP);
	__uपूर्णांक(max_entries, 20);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण sock_map_rx SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKMAP);
	__uपूर्णांक(max_entries, 20);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण sock_map_tx SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKMAP);
	__uपूर्णांक(max_entries, 20);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण sock_map_msg SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 20);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sock_map_अवरोध SEC(".maps");

SEC("sk_skb2")
पूर्णांक bpf_prog2(काष्ठा __sk_buff *skb)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ) skb->data_end;
	व्योम *data = (व्योम *)(दीर्घ) skb->data;
	__u32 lport = skb->local_port;
	__u32 rport = skb->remote_port;
	__u8 *d = data;
	__u8 sk, map;

	अगर (data + 8 > data_end)
		वापस SK_DROP;

	map = d[0];
	sk = d[1];

	d[0] = 0xd;
	d[1] = 0xe;
	d[2] = 0xa;
	d[3] = 0xd;
	d[4] = 0xb;
	d[5] = 0xe;
	d[6] = 0xe;
	d[7] = 0xf;

	अगर (!map)
		वापस bpf_sk_redirect_map(skb, &sock_map_rx, sk, 0);
	वापस bpf_sk_redirect_map(skb, &sock_map_tx, sk, 0);
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
