<शैली गुरु>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

पूर्णांक _version SEC("version") = 1;

SEC("sk_skb1")
पूर्णांक bpf_prog1(काष्ठा __sk_buff *skb)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ) skb->data_end;
	व्योम *data = (व्योम *)(दीर्घ) skb->data;
	__u32 lport = skb->local_port;
	__u32 rport = skb->remote_port;
	__u8 *d = data;
	पूर्णांक err;

	अगर (data + 10 > data_end) अणु
		err = bpf_skb_pull_data(skb, 10);
		अगर (err)
			वापस SK_DROP;

		data_end = (व्योम *)(दीर्घ)skb->data_end;
		data = (व्योम *)(दीर्घ)skb->data;
		अगर (data + 10 > data_end)
			वापस SK_DROP;
	पूर्ण

	/* This ग_लिखो/पढ़ो is a bit poपूर्णांकless but tests the verअगरier and
	 * strparser handler क्रम पढ़ो/ग_लिखो pkt data and access पूर्णांकo sk
	 * fields.
	 */
	d = data;
	d[7] = 1;
	वापस skb->len;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
