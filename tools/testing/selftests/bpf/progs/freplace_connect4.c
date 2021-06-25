<शैली गुरु>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ipv6.h>
#समावेश <linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <sys/socket.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

SEC("freplace/do_bind")
पूर्णांक new_करो_bind(काष्ठा bpf_sock_addr *ctx)
अणु
  काष्ठा sockaddr_in sa = अणुपूर्ण;

  bpf_bind(ctx, (काष्ठा sockaddr *)&sa, माप(sa));
  वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
